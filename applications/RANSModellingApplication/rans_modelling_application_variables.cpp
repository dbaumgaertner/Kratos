//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Suneth Warnakulasuriya (https://github.com/sunethwarna)
//

#include "rans_modelling_application_variables.h"

namespace Kratos
{
KRATOS_CREATE_VARIABLE( double, TURBULENT_KINETIC_ENERGY )
KRATOS_CREATE_VARIABLE( double, TURBULENT_ENERGY_DISSIPATION_RATE )
KRATOS_CREATE_VARIABLE( double, TURBULENT_KINETIC_ENERGY_RATE )
KRATOS_CREATE_VARIABLE( double, TURBULENT_ENERGY_DISSIPATION_RATE_2 )
KRATOS_CREATE_VARIABLE( bool, IS_CO_SOLVING_PROCESS_ACTIVE )
KRATOS_CREATE_VARIABLE( double, RANS_Y_PLUS )
KRATOS_CREATE_VARIABLE( double, RANS_WALL_Y_PLUS )
KRATOS_CREATE_VARIABLE( double, RANS_AUXILIARY_VARIABLE_1 )
KRATOS_CREATE_VARIABLE( double, RANS_AUXILIARY_VARIABLE_2 )
KRATOS_CREATE_VARIABLE( double, WALL_SMOOTHNESS_BETA )
KRATOS_CREATE_VARIABLE( double, WALL_VON_KARMAN )
KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( WALL_VELOCITY )
KRATOS_CREATE_VARIABLE( double, TURBULENCE_RANS_C_MU )
KRATOS_CREATE_VARIABLE( double, TURBULENCE_RANS_C1 )
KRATOS_CREATE_VARIABLE( double, TURBULENCE_RANS_C2 )
KRATOS_CREATE_VARIABLE( double, TURBULENT_VISCOSITY_MIN )
KRATOS_CREATE_VARIABLE( double, TURBULENT_VISCOSITY_MAX )
KRATOS_CREATE_VARIABLE( double, TURBULENT_KINETIC_ENERGY_SIGMA )
KRATOS_CREATE_VARIABLE( double, TURBULENT_ENERGY_DISSIPATION_RATE_SIGMA )

KRATOS_CREATE_VARIABLE(std::vector<Process::Pointer>, RANS_AUXILIARY_PROCESS_LIST)
KRATOS_CREATE_VARIABLE(Element::WeakPointer, PARENT_ELEMENT)
KRATOS_CREATE_VARIABLE(int, NUMBER_OF_NEIGHBOUR_CONDITIONS)

// Adjoint variables
KRATOS_CREATE_VARIABLE( Matrix, RANS_Y_PLUS_VELOCITY_DERIVATIVES )
KRATOS_CREATE_VARIABLE( Matrix, RANS_VELOCITY_PRESSURE_PARTIAL_DERIVATIVE )
KRATOS_CREATE_VARIABLE( Matrix, RANS_PRESSURE_PARTIAL_DERIVATIVE )
KRATOS_CREATE_VARIABLE( Matrix, RANS_TURBULENT_KINETIC_ENERGY_PARTIAL_DERIVATIVE )
KRATOS_CREATE_VARIABLE( Matrix, RANS_TURBULENT_ENERGY_DISSIPATION_RATE_PARTIAL_DERIVATIVE )
KRATOS_CREATE_VARIABLE( Matrix, RANS_ACCELERATION_PARTIAL_DERIVATIVE )
KRATOS_CREATE_VARIABLE( Matrix, RANS_TURBULENT_KINETIC_ENERGY_RATE_PARTIAL_DERIVATIVE )
KRATOS_CREATE_VARIABLE( Matrix, RANS_TURBULENT_ENERGY_DISSIPATION_RATE_2_PARTIAL_DERIVATIVE )

KRATOS_CREATE_VARIABLE( double, RANS_SCALAR_1_ADJOINT_1 )
KRATOS_CREATE_VARIABLE( double, RANS_SCALAR_1_ADJOINT_2 )
KRATOS_CREATE_VARIABLE( double, RANS_SCALAR_1_ADJOINT_3 )
KRATOS_CREATE_VARIABLE( double, RANS_AUX_ADJOINT_SCALAR_1 )

KRATOS_CREATE_VARIABLE( double, RANS_SCALAR_2_ADJOINT_1 )
KRATOS_CREATE_VARIABLE( double, RANS_SCALAR_2_ADJOINT_2 )
KRATOS_CREATE_VARIABLE( double, RANS_SCALAR_2_ADJOINT_3 )
KRATOS_CREATE_VARIABLE( double, RANS_AUX_ADJOINT_SCALAR_2 )

}
