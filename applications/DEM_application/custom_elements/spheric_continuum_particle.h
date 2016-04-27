//
// Author: Miquel Santasusana msantasusana@cimne.upc.edu
//

#if !defined(KRATOS_SPHERIC_CONTINUUM_PARTICLE_H_INCLUDED )
#define  KRATOS_SPHERIC_CONTINUUM_PARTICLE_H_INCLUDED

// System includes
#include <string>
#include <iostream> 

// Project includes
#include "includes/define.h"
#include "spheric_particle.h"
#include "Particle_Contact_Element.h"
#include "../custom_constitutive/DEM_continuum_constitutive_law.h"
#include "containers/vector_component_adaptor.h"

namespace Kratos
{
    class SphericContinuumParticle : public SphericParticle
    {
    public:
      
        /// Pointer definition of SphericContinuumParticle
        KRATOS_CLASS_POINTER_DEFINITION(SphericContinuumParticle);

        typedef WeakPointerVector<Element> ParticleWeakVectorType;
        typedef ParticleWeakVectorType::ptr_iterator ParticleWeakIteratorType_ptr;
        typedef WeakPointerVector<Element >::iterator ParticleWeakIteratorType;

        /// Default constructor
        SphericContinuumParticle(IndexType NewId, GeometryType::Pointer pGeometry);
        SphericContinuumParticle(IndexType NewId, NodesArrayType const& ThisNodes);
        SphericContinuumParticle(IndexType NewId, GeometryType::Pointer pGeometry, PropertiesType::Pointer pProperties);
      
        Element::Pointer Create(IndexType NewId, NodesArrayType const& ThisNodes, PropertiesType::Pointer pProperties) const;
         
        /// Destructor
        virtual ~SphericContinuumParticle();
               
        void SearchSkinParticles(ProcessInfo& r_process_info);
        void SetInitialSphereContacts(ProcessInfo& r_process_info);
        void SetInitialFemContacts();
        void CreateContinuumConstitutiveLaws();
        void FinalizeSolutionStep(ProcessInfo& r_process_info);     
        void Calculate(const Variable<double>& rVariable, double& Output, const ProcessInfo& r_process_info);

        void ReorderAndRecoverInitialPositionsAndFilter(std::vector<SphericParticle*>& mTempNeighbourElements);
        void ReorderFEMneighbours();
        
        //virtual void ComputeNewRigidFaceNeighboursHistoricalData();

        virtual double CalculateLocalMaxPeriod(const bool has_mpi, const ProcessInfo& r_process_info);
        virtual double CalculateMaxSearchDistance(const bool has_mpi, const ProcessInfo& r_process_info);
        virtual void CalculateMeanContactArea(const bool has_mpi, const ProcessInfo& r_process_info);      
        virtual void CalculateOnContactElements(size_t i_neighbour_count, double LocalElasticContactForce[3], 
                                                double contact_sigma, double contact_tau, double failure_criterion_state, double acumulated_damage, int time_steps);
           
        virtual void ContactAreaWeighting();
        virtual double GetInitialDelta(int index);

        /// Turn back information as a string
        virtual std::string Info() const
        {
            std::stringstream buffer;
            buffer << "SphericCosntinuumParticle" ;
            return buffer.str();
        }
      
        /// Print information about this object
        virtual void PrintInfo(std::ostream& rOStream) const {rOStream << "SphericContinuumParticle";}

        /// Print object's data
        virtual void PrintData(std::ostream& rOStream) const {}

        //member variables DEM_CONTINUUM
        int mContinuumGroup;
        std::vector<ParticleContactElement*> mBondElements;
        std::vector<int> mIniNeighbourIds;
        std::vector<int> mIniNeighbourFailureId;
        std::vector<double> mIniNeighbourDelta;

        
        unsigned int mContinuumInitialNeighborsSize;
        unsigned int mInitialNeighborsSize;
        std::vector<Kratos::DEMContinuumConstitutiveLaw::Pointer> mContinuumConstitutiveLawArray;

    protected:

        SphericContinuumParticle();
        
        virtual void CustomInitialize();

        virtual double GetInitialDeltaWithFEM(int index);              
        virtual void ComputeBallToBallContactForce(array_1d<double, 3>& rElasticForce,
                                                   array_1d<double, 3>& rContactForce, 
                                                   array_1d<double, 3>& InitialRotaMoment, 
                                                   ProcessInfo& r_process_info, 
                                                   const double dt,
                                                   const bool multi_stage_RHS) final;         

        virtual void AddContributionToRepresentativeVolume(const double distance,
                                                    const double radius_sum,
                                                    const double contact_area);

        double*                        mSkinSphere; 
        std::vector<double>         mContIniNeighArea;        
        std::vector<int>            mFemIniNeighbourIds;
        std::vector<double>         mFemIniNeighbourDelta;                        


    private:

        friend class Serializer;

        virtual void save(Serializer& rSerializer) const
        {
            KRATOS_SERIALIZE_SAVE_BASE_CLASS(rSerializer, SphericParticle );
            //rSerializer.save("mContinuumGroup",mContinuumGroup);
            //rSerializer.save("mIniNeighbourIds",mIniNeighbourIds);
            //rSerializer.save("mSymmStressTensor",mSymmStressTensor);
        }

        virtual void load(Serializer& rSerializer)
        {
            KRATOS_SERIALIZE_LOAD_BASE_CLASS(rSerializer, SphericParticle );
            //rSerializer.load("mContinuumGroup",mContinuumGroup);
            //rSerializer.load("mIniNeighbourIds",mIniNeighbourIds);
            //rSerializer.load("mSymmStressTensor",mSymmStressTensor);
            mContinuumGroup = this->GetGeometry()[0].FastGetSolutionStepValue(COHESIVE_GROUP);  
        }
            
        /* Assignment operator
        SphericContinuumParticle& operator=(SphericContinuumParticle const& rOther) { return *this; }
        Copy constructor
        SphericContinuumParticle(SphericContinuumParticle const& rOther) { *this = rOther; }
        */

    }; // Class SphericContinuumParticle 
        
    /// input stream function
    inline std::istream& operator >> (std::istream& rIStream, SphericContinuumParticle& rThis) {return rIStream;}

    /// output stream function
    inline std::ostream& operator << (std::ostream& rOStream, const SphericContinuumParticle& rThis) {
        rThis.PrintInfo(rOStream);
        rOStream << std::endl;
        rThis.PrintData(rOStream);
        return rOStream;
    }
} // namespace Kratos

#endif // KRATOS_SPHERIC_CONTINUUM_PARTICLE_H_INCLUDED defined 


