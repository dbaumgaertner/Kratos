//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main author:    Michael Andre, https://github.com/msandre
//

#if !defined(KRATOS_HDF5_MODEL_PART_IO_H_INCLUDED)
#define KRATOS_HDF5_MODEL_PART_IO_H_INCLUDED

// System includes
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

// External includes

// Project includes
#include "includes/define.h"
#include "includes/kratos_parameters.h"
#include "utilities/openmp_utils.h"
#include "includes/io.h"

// Application includes
#include "custom_io/hdf5_file.h"

namespace Kratos
{
///@addtogroup HDF5Application
///@{

/// A class for serial IO of a model part in HDF5.
class HDF5ModelPartIO : public IO
{
public:
    ///@name Type Definitions
    ///@{

    /// Pointer definition
    KRATOS_CLASS_POINTER_DEFINITION(HDF5ModelPartIO);

    ///@}
    ///@name Life Cycle
    ///@{

    /// Constructor.
    HDF5ModelPartIO(Parameters& rParams, HDF5File::Pointer pFile);

    ///@}
    ///@name Operations
    ///@{
    bool ReadNodes(NodesContainerType& rNodes) override;

    std::size_t ReadNodesNumber() override;

    void WriteNodes(NodesContainerType const& rNodes) override;

    void ReadElements(NodesContainerType& rNodes,
                      PropertiesContainerType& rProperties,
                      ElementsContainerType& rElements) override;

    std::size_t ReadElementsConnectivities(ConnectivitiesContainerType& rElementsConnectivities) override;

    void WriteElements(ElementsContainerType const& rElements) override;

    void ReadConditions(NodesContainerType& rNodes,
                        PropertiesContainerType& rProperties,
                        ConditionsContainerType& rConditions) override;

    void WriteConditions(ConditionsContainerType const& rConditions) override;

    std::size_t ReadConditionsConnectivities(ConnectivitiesContainerType& rConditionsConnectivities) override;

    void ReadInitialValues(ModelPart& rModelPart) override;

    void ReadInitialValues(NodesContainerType& rNodes,
                           ElementsContainerType& rElements,
                           ConditionsContainerType& rConditions) override;

    void ReadModelPart(ModelPart& rModelPart) override;

    void WriteModelPart(ModelPart& rModelPart) override;

    ///@}

protected:
    ///@name Protected Operations
    ///@{

    HDF5File& GetFile() const;

    virtual void Check();

    ///@}

private:
    ///@name Member Variables
    ///@{

    HDF5File::Pointer mpFile;
    std::vector<unsigned> mCurrentFillPosition;
    std::vector<std::string> mElementNames;
    std::vector<const Element*> mElementPointers;
    std::vector<std::string> mConditionNames;
    std::vector<const Condition*> mConditionPointers;

    ///@}

    ///@name Private Operations
    ///@{

    inline unsigned FindIndexOfMatchingReferenceElement(Element const& rElement)
    {
        const int thread_id = OpenMPUtils::ThisThread();
        unsigned& r_i = mCurrentFillPosition[thread_id];
        // Check the most recent element type.
        if (typeid(rElement) == typeid(*mElementPointers[r_i]))
            return r_i; // Element type didn't change.
        
        // Search for the new element type.
        for (r_i = 0; r_i < mElementPointers.size(); ++r_i)
            if (typeid(rElement) == typeid(*mElementPointers[r_i]))
                return r_i;

        KRATOS_ERROR << "The element's type (" << typeid(rElement).name()
                     << ") was not found." << std::endl;
    }

    inline unsigned FindIndexOfMatchingReferenceCondition(Condition const& rCondition)
    {
        const int thread_id = OpenMPUtils::ThisThread();
        unsigned& r_i = mCurrentFillPosition[thread_id];
        // Check the most recent condition type.
        if (typeid(rCondition) == typeid(*mConditionPointers[r_i]))
            return r_i; // condition type didn't change.
        
        // Search for the new condition type.
        for (r_i = 0; r_i < mConditionPointers.size(); ++r_i)
            if (typeid(rCondition) == typeid(*mConditionPointers[r_i]))
                return r_i;

        KRATOS_ERROR << "The condition's type (" << typeid(rCondition).name()
                     << ") was not found." << std::endl;
    }

    void WriteUniformElements(ElementsContainerType const& rElements);

    void WriteMixedElements(ElementsContainerType const& rElements);

    void WriteUniformConditions(ConditionsContainerType const& rConditions);

    void WriteMixedConditions(ConditionsContainerType const& rConditions);

    ///@}
};

///@} addtogroup
} // namespace Kratos.

#endif // KRATOS_HDF5_MODEL_PART_IO_H_INCLUDED defined
