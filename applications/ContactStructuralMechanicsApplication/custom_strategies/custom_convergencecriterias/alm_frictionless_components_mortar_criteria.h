// KRATOS  ___|  |                   |                   |
//       \___ \  __|  __| |   |  __| __| |   |  __| _` | |
//             | |   |    |   | (    |   |   | |   (   | |
//       _____/ \__|_|   \__,_|\___|\__|\__,_|_|  \__,_|_| MECHANICS
//
//  License:             BSD License
//                                       license: StructuralMechanicsApplication/license.txt
//
//  Main authors:    Vicente Mataix Ferrandiz
//

#if !defined(KRATOS_ALM_FRICTIONLESS_COMPONENTS_MORTAR_CRITERIA_H)
#define  KRATOS_ALM_FRICTIONLESS_COMPONENTS_MORTAR_CRITERIA_H

/* System includes */

/* External includes */

/* Project includes */
#include "utilities/table_stream_utility.h"
#include "custom_strategies/custom_convergencecriterias/base_mortar_criteria.h"
#include "utilities/color_utilities.h"

namespace Kratos
{
///@addtogroup ContactStructuralMechanicsApplication
///@{
    
///@name Kratos Globals
///@{

///@}
///@name Type Definitions
///@{

///@}
///@name  Enum's
///@{

///@}
///@name  Functions
///@{

///@}
///@name Kratos Classes
///@{

/**
 * @class ALMFrictionlessComponentsMortarConvergenceCriteria 
 * @ingroup ContactStructuralMechanicsApplication 
 * @brief Custom convergence criteria for the mortar condition for frictionless case with components
 * @author Vicente Mataix Ferrandiz
 */
template<class TSparseSpace, class TDenseSpace>
class ALMFrictionlessComponentsMortarConvergenceCriteria 
    : public  BaseMortarConvergenceCriteria< TSparseSpace, TDenseSpace >
{
public:
    ///@name Type Definitions
    ///@{

    KRATOS_CLASS_POINTER_DEFINITION( ALMFrictionlessComponentsMortarConvergenceCriteria );

    typedef ConvergenceCriteria< TSparseSpace, TDenseSpace > ConvergenceCriteriaBaseType;
    
    typedef BaseMortarConvergenceCriteria< TSparseSpace, TDenseSpace >          BaseType;

    typedef TSparseSpace                                                 SparseSpaceType;

    typedef typename BaseType::TDataType                                       TDataType;

    typedef typename BaseType::DofsArrayType                               DofsArrayType;

    typedef typename BaseType::TSystemMatrixType                       TSystemMatrixType;

    typedef typename BaseType::TSystemVectorType                       TSystemVectorType;
    
    typedef ModelPart::ConditionsContainerType                       ConditionsArrayType;
    
    typedef ModelPart::NodesContainerType                                 NodesArrayType;
    
    typedef TableStreamUtility::Pointer                          TablePrinterPointerType;
    
    typedef std::size_t                                                        IndexType;

    ///@}
    ///@name Life Cycle
    ///@{
    
    /// Default constructors
    ALMFrictionlessComponentsMortarConvergenceCriteria(        
        TablePrinterPointerType pTable = nullptr,
        const bool PrintingOutput = false,
        const bool GiDIODebug = false
        ) : BaseMortarConvergenceCriteria< TSparseSpace, TDenseSpace >(GiDIODebug),
        mpTable(pTable),
        mPrintingOutput(PrintingOutput),
        mTableIsInitialized(false)
    {
    }

    ///Copy constructor 
    ALMFrictionlessComponentsMortarConvergenceCriteria( ALMFrictionlessComponentsMortarConvergenceCriteria const& rOther )
      :BaseType(rOther)
      ,mpTable(rOther.mpTable)
      ,mPrintingOutput(rOther.mPrintingOutput)
      ,mTableIsInitialized(rOther.mTableIsInitialized)
    {
    }

    /// Destructor
    ~ALMFrictionlessComponentsMortarConvergenceCriteria() override = default;

    ///@}
    ///@name Operators
    ///@{
    
    /**
     * @brief Criterias that need to be called before getting the solution
     * @param rModelPart Reference to the ModelPart containing the contact problem.
     * @param rDofSet Reference to the container of the problem's degrees of freedom (stored by the BuilderAndSolver)
     * @param A System matrix (unused)
     * @param Dx Vector of results (variations on nodal variables)
     * @param b RHS vector (residual)
     * @return true if convergence is achieved, false otherwise
     */
    
    bool PreCriteria(
        ModelPart& rModelPart,
        DofsArrayType& rDofSet,
        const TSystemMatrixType& A,
        const TSystemVectorType& Dx,
        const TSystemVectorType& b
        ) override
    {
        BaseType::PreCriteria(rModelPart, rDofSet, A, Dx, b);
        
        return true;
    }
    
    /**
     * @brief Compute relative and absolute error.
     * @param rModelPart Reference to the ModelPart containing the contact problem.
     * @param rDofSet Reference to the container of the problem's degrees of freedom (stored by the BuilderAndSolver)
     * @param A System matrix (unused)
     * @param Dx Vector of results (variations on nodal variables)
     * @param b RHS vector (residual)
     * @return true if convergence is achieved, false otherwise
     */

    bool PostCriteria(
        ModelPart& rModelPart,
        DofsArrayType& rDofSet,
        const TSystemMatrixType& A,
        const TSystemVectorType& Dx,
        const TSystemVectorType& b
        ) override
    {
        // We call the base class
        BaseType::PostCriteria(rModelPart, rDofSet, A, Dx, b);
        
        // Defining the convergence
        IndexType is_converged = 0;
        
//         const double epsilon = rModelPart.GetProcessInfo()[INITIAL_PENALTY]; 
        const double scale_factor = rModelPart.GetProcessInfo()[SCALE_FACTOR];
        
        NodesArrayType& nodes_array = rModelPart.GetSubModelPart("Contact").Nodes();

        #pragma omp parallel for reduction(+:is_converged)
        for(int i = 0; i < static_cast<int>(nodes_array.size()); ++i) {
            auto it_node = nodes_array.begin() + i;
            
            const double epsilon = it_node->GetValue(INITIAL_PENALTY); 
            
            const array_1d<double,3>& lagrange_multiplier = it_node->FastGetSolutionStepValue(VECTOR_LAGRANGE_MULTIPLIER);
            const array_1d<double,3>& nodal_normal = it_node->FastGetSolutionStepValue(NORMAL);
            const double normal_lagrange_multiplier = inner_prod(nodal_normal, lagrange_multiplier);
            
            const double augmented_normal_pressure = scale_factor * normal_lagrange_multiplier + epsilon * it_node->FastGetSolutionStepValue(WEIGHTED_GAP);     
            
            it_node->SetValue(AUGMENTED_NORMAL_CONTACT_PRESSURE, augmented_normal_pressure); // NOTE: This value is purely for debugging interest (to see the "effective" pressure)
            
            if (augmented_normal_pressure < 0.0) { // NOTE: This could be conflictive (< or <=)
                if (it_node->Is(ACTIVE) == false ) {
                    it_node->Set(ACTIVE, true);
                    is_converged += 1;
                }
            } else {
                if (it_node->Is(ACTIVE) == true ) {
                    it_node->Set(ACTIVE, false);
                    is_converged += 1;
                }
            }
        }
        
        // We save to the process info if the active set has converged
        const bool active_set_converged = (is_converged == 0 ? true : false);
        rModelPart.GetProcessInfo()[ACTIVE_SET_CONVERGED] = active_set_converged;
        
        if (rModelPart.GetCommunicator().MyPID() == 0 && this->GetEchoLevel() > 0) {
            if (mpTable != nullptr) {
                auto& table = mpTable->GetTable();
                if (active_set_converged) {
                    if (mPrintingOutput == false)
                        table << BOLDFONT(FGRN("       Achieved"));
                    else
                        table << "Achieved";
                } else {
                    if (mPrintingOutput == false)
                        table << BOLDFONT(FRED("   Not achieved"));
                    else
                        table << "Not achieved";
                }
            } else {
                if (active_set_converged) {
                    if (mPrintingOutput == false)
                        std::cout << BOLDFONT("\tActive set") << " convergence is " << BOLDFONT(FGRN("achieved")) << std::endl;
                    else
                        std::cout << "\tActive set convergence is achieved" << std::endl;
                } else {
                    if (mPrintingOutput == false)
                        std::cout << BOLDFONT("\tActive set") << " convergence is " << BOLDFONT(FRED("not achieved")) << std::endl;
                    else
                        std::cout << "\tActive set convergence is not achieved" << std::endl;
                }
            }
        }
        
        return active_set_converged;
    }
    
    /**
     * @brief This function initialize the convergence criteria
     * @param rModelPart The model part of interest
     */ 
    
    void Initialize(ModelPart& rModelPart) override
    {
        ConvergenceCriteriaBaseType::mConvergenceCriteriaIsInitialized = true;
        
        if (mpTable != nullptr && mTableIsInitialized == false) {
            auto& table = mpTable->GetTable();
            table.AddColumn("ACTIVE SET CONV", 15);
            mTableIsInitialized = true;
        }
    }
    
    ///@}
    ///@name Operations
    ///@{

    ///@}
    ///@name Acces
    ///@{

    ///@}
    ///@name Inquiry
    ///@{

    ///@}
    ///@name Friends
    ///@{

protected:
    
    ///@name Protected static Member Variables
    ///@{

    ///@}
    ///@name Protected member Variables
    ///@{

    ///@}
    ///@name Protected Operators
    ///@{

    ///@}
    ///@name Protected Operations
    ///@{
    
    ///@}
    ///@name Protected  Access
    ///@{

    ///@}
    ///@name Protected Inquiry
    ///@{

    ///@}
    ///@name Protected LifeCycle
    ///@{
    ///@}

private:
    ///@name Static Member Variables
    ///@{
    
    ///@}
    ///@name Member Variables
    ///@{
    
    TablePrinterPointerType mpTable; /// Pointer to the fancy table 
    bool mPrintingOutput;            //// If the colors and bold are printed
    bool mTableIsInitialized;        /// If the table is already initialized
    
    ///@}
    ///@name Private Operators
    ///@{

    ///@}
    ///@name Private Operations
    ///@{

    ///@}
    ///@name Private  Access
    ///@{

    ///@}
    ///@name Serialization
    ///@{

    ///@name Private Inquiry
    ///@{
    ///@}

    ///@name Unaccessible methods
    ///@{
    ///@}

}; // Class ALMFrictionlessComponentsMortarConvergenceCriteria 

///@name Explicit Specializations
///@{

}  // namespace Kratos 

#endif /* KRATOS_ALM_FRICTIONLESS_COMPONENTS_MORTAR_CRITERIA_H  defined */
