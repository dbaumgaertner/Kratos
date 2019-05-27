from __future__ import print_function, absolute_import, division  # makes KratosMultiphysics backward compatible with python 2.6 and 2.7
import KratosMultiphysics

def GetDefaultInputParameters():

    default_settings = KratosMultiphysics.Parameters("""
        {
            "do_print_results_option"          : true,
            "Dimension"                        : 3,
            "PeriodicDomainOption"             : false,
            "BoundingBoxOption"                : false,
            "AutomaticBoundingBoxOption"       : false,
            "BoundingBoxEnlargementFactor"     : 1.0,
            "BoundingBoxStartTime"             : 0.0,
            "BoundingBoxStopTime"              : 1000.0,
            "BoundingBoxMaxX"                  : 10.0,
            "BoundingBoxMaxY"                  : 10.0,
            "BoundingBoxMaxZ"                  : 10.0,
            "BoundingBoxMinX"                  : -10.0,
            "BoundingBoxMinY"                  : -10.0,
            "BoundingBoxMinZ"                  : -10.0,
            "dem_inlet_option"                 : true,
            "GravityX"                         : 0.0,
            "GravityY"                         : 0.0,
            "GravityZ"                         : -9.81,

            "EnergyCalculationOption"          : false,
            "PotentialEnergyReferencePointX"   : 0.0,
            "PotentialEnergyReferencePointY"   : 0.0,
            "PotentialEnergyReferencePointZ"   : 0.0,

            "VelocityTrapOption"               : false,
            "VelocityTrapMaxX"                 : 0.0,
            "VelocityTrapMaxY"                 : 0.0,
            "VelocityTrapMaxZ"                 : 0.0,
            "VelocityTrapMinX"                 : 0.0,
            "VelocityTrapMinY"                 : 0.0,
            "VelocityTrapMinZ"                 : 0.0,
            "RotationOption"                   : true,
            "CleanIndentationsOption"          : false,
            "RemoveBallsInEmbeddedOption"      : false,
            "solver_settings" :{
                "strategy"                 : "deprecated_key.invalid_strategy",
                "RemoveBallsInitiallyTouchingWalls": false,
                "do_search_neighbours": true
            },
            "echo_level"                  : 1,
            "problem_data"     : {
                "problem_name"  : "dummy_name.Provide_a_real_one",
                "parallel_type" : "OpenMP",
                "echo_level"    : 1,
                "start_time"    : 0.0,
                "end_time"      : 1
            },
            "_json_output_process"  : [{
            "python_module" : "json_output_process",
            "kratos_module" : "KratosMultiphysics",
            "process_name"  : "JsonOutputProcess",
            "Parameters"    : {
                "output_variables"     : ["DISPLACEMENT_X","DISPLACEMENT_Y"],
                "output_file_name"     : "candelier_results.json",
                "model_part_name"      : "CandelierDEM",
                "time_frequency"       : 1
            }
            }],
            "print_output_process" : [{
            "python_module"   : "from_json_check_result_process",
            "kratos_module"   : "KratosMultiphysics",
            "process_name"    : "FromJsonCheckResultProcess",
            "Parameters"      : {
                "check_variables"      : ["DISPLACEMENT_X","DISPLACEMENT_Y"],
                "input_file_name"      : "candelier_errors.json",
                "model_part_name"      : "SpheresPart",
                "time_frequency"       : 1
            }
            }],
            "DeltaOption"                      : "Absolute",
            "SearchTolerance"                  : 0.0,
            "search_tolerance_against_walls"   : 0.0,
            "CoordinationNumber"               : 10,
            "AmplifiedSearchRadiusExtension"   : 0.0,
            "MaxAmplificationRatioOfSearchRadius" : 10,
            "ModelDataInfo"                    : false,
            "VirtualMassCoefficient"           : 1.0,
            "RollingFrictionOption"            : false,
            "ComputeStressTensorOption"        : false,
            "GlobalDamping"                    : 0.0,
            "PoissonEffectOption"              : true,
            "ShearStrainParallelToBondOption"  : true,
            "DontSearchUntilFailure"           : false,
            "ContactMeshOption"                : false,
            "MaxNumberOfIntactBondsToConsiderASphereBroken" : 0,
            "OutputFileType"                   : "Binary",
            "Multifile"                        : "multiple_files",
            "TestType"                         : "None",
            "ElementType"                      : "SphericPartDEMElement3D",

            "TranslationalIntegrationScheme"   : "Symplectic_Euler",
            "RotationalIntegrationScheme"      : "Direct_Integration",
            "AutomaticTimestep"                : false,
            "DeltaTimeSafetyFactor"            : 1.0,
            "MaxTimeStep"                      : 5e-5,
            "FinalTime"                        : 0.05,
            "ControlTime"                      : 4.0,
            "NeighbourSearchFrequency"         : 50,
            "virtual_sea_surface_settings"     : {
                "print_sea_surface"            : false,
                "PostVirtualSeaSurfaceX1"      : 0.0,
                "PostVirtualSeaSurfaceY1"      : 0.0,
                "PostVirtualSeaSurfaceX2"      : 0.0,
                "PostVirtualSeaSurfaceY2"      : 0.0,
                "PostVirtualSeaSurfaceX3"      : 0.0,
                "PostVirtualSeaSurfaceY3"      : 0.0,
                "PostVirtualSeaSurfaceX4"      : 0.0,
                "PostVirtualSeaSurfaceY4"      : 0.0
            },
            "output_processes"                 :{},

            "ConfinementPressure"              : 0.0,
            "LoadingVelocity"                  : -0.10,
            "MeshType"                         : "1",
            "MeshPath"                         : "0",
            "SpecimenLength"                   : 0.3,
            "SpecimenDiameter"                 : 0.15,
            "MeasuringSurface"                 : 0.01767145867644375,

            "GraphExportFreq"                  : 1e-3,
            "VelTrapGraphExportFreq"           : 1e-3,
            "OutputTimeStep"                   : 1e-2,
            "PostBoundingBox"                  : false,
            "PostDisplacement"                 : false,
            "PostVelocity"                     : true,
            "PostTotalForces"                  : false,
            "PostRigidElementForces"           : false,
            "PostSkinSphere"                   : false,
            "PostGluedSphere"                  : false,
            "PostPoissonRatio"                 : false,
            "PostRadius"                       : false,
            "PostAngularVelocity"              : false,
            "PostParticleMoment"               : false,
            "PostEulerAngles"                  : false,
            "PostRollingResistanceMoment"      : false,
            "PostCharacteristicLength"         : false,
            "PostElasticForces"                : false,
            "PostContactForces"                : false,
            "PostTangentialElasticForces"      : false,
            "PostShearStress"                  : false,
            "PostReactions"                    : false,
            "PostPressure"                     : false,
            "PostNonDimensionalVolumeWear"     : false,
            "PostNodalArea"                    : false,
            "PostStressStrainOption"           : false,
            "PostContactSigma"                 : false,
            "PostContactTau"                   : false,
            "PostLocalContactForce"            : false,
            "PostFailureCriterionState"        : false,
            "PostContactFailureId"             : false,
            "PostMeanContactArea"              : false,
            "PostRHS"                          : false,
            "PostDampForces"                   : false,
            "PostAppliedForces"                : false,
            "PostGroupId"                      : false,
            "PostExportId"                     : false,
            "PostNormalImpactVelocity"         : false,
            "PostTangentialImpactVelocity"     : false,
            "PostFaceNormalImpactVelocity"     : false,
            "PostFaceTangentialImpactVelocity" : false,
            "post_vtk_option"                  : false,

            "IntegrationScheme"                : "deprecated_key_since_6_december_2017",
            "LoadingVelocityTop"               : 0.0,
            "LoadingVelocityBot"               : 0.0,

            "problem_name" : "dummy_name.Provide_a_real_one",
            "processes" : {}
            }""")

    return default_settings
