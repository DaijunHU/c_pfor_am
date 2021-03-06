// Nicolo Grilli
// Daijun Hu 
// National University of Singapore
// 1 Novembre 2020

#pragma once

#include "FiniteStrainCrystalPlasticity.h"

/**
 * FiniteStrainCrystalPlasticityDislo uses the multiplicative decomposition of deformation gradient
 * and solves the PK2 stress residual equation at the intermediate configuration to evolve the material state.
 * The internal variables are updated using an interative predictor-corrector algorithm.
 * Backward Euler integration rule is used for the rate equations.
 * Temperature dependence of the CRSS.
 * Dislocation based model.
 * Calculation of the dislocation velocity depending on resolved shear stress.
 */
class FiniteStrainCrystalPlasticityDislo : public FiniteStrainCrystalPlasticity
{
public:
  static InputParameters validParams();

  FiniteStrainCrystalPlasticityDislo(const InputParameters & parameters);

protected:
  /**
   * This function calculates stress residual.
   */
  virtual void calcResidual( RankTwoTensor &resid );
  
  // Critical resolved shear stress decreases exponentially with temperature
  // A + B exp(- C * (T - 293.0))
  virtual void TempDependCRSS();
  
  /**
  * This function updates the slip increments.
  * And derivative of slip w.r.t. resolved shear stress.
  */
  virtual void getSlipIncrements();
  
  /**
  * This function
  * stores the dislocation velocity value
  * to couple with dislocation transport
  */
  virtual void getDisloVelocity();

  /**
  * This function
  * stores the dislocation velocity direction
  * to couple with dislocation transport
  */
  virtual void OutputSlipDirection();

  const VariableValue & _temp;
  
  const VariableValue & _rho_edge_pos_1;
  const VariableValue & _rho_edge_neg_1;
  const VariableValue & _rho_edge_pos_2;
  const VariableValue & _rho_edge_neg_2;
  const VariableValue & _rho_edge_pos_3;
  const VariableValue & _rho_edge_neg_3;
  const VariableValue & _rho_edge_pos_4;
  const VariableValue & _rho_edge_neg_4;
  const VariableValue & _rho_edge_pos_5;
  const VariableValue & _rho_edge_neg_5;
  const VariableValue & _rho_edge_pos_6;
  const VariableValue & _rho_edge_neg_6;
  const VariableValue & _rho_edge_pos_7;
  const VariableValue & _rho_edge_neg_7;
  const VariableValue & _rho_edge_pos_8;
  const VariableValue & _rho_edge_neg_8;
  const VariableValue & _rho_edge_pos_9;
  const VariableValue & _rho_edge_neg_9;
  const VariableValue & _rho_edge_pos_10;
  const VariableValue & _rho_edge_neg_10;
  const VariableValue & _rho_edge_pos_11;
  const VariableValue & _rho_edge_neg_11;
  const VariableValue & _rho_edge_pos_12;
  const VariableValue & _rho_edge_neg_12;
  
  const Real _thermal_expansion;
  const Real _reference_temperature;

  const Real _dCRSS_dT_A;
  const Real _dCRSS_dT_B;
  const Real _dCRSS_dT_C;
  const Real _dislo_mobility;
  const Real _burgers_vector_mag;
  
  // critical resolved shear stress
  // exponentially decreased with temperature
  std::vector<Real> _gssT;
  
  // Rotated slip direction to couple with dislocation transport
  // to indicate dislocation velocity direction for all slip systems
  MaterialProperty<std::vector<Real>> & _slip_direction;
  
  // Slip increment for output
  MaterialProperty<std::vector<Real>> & _slip_incr_out;
  
  // Dislocation velocity
  MaterialProperty<std::vector<Real>> & _dislo_velocity;
  
  // Derivative of the dislocation velocity with respect to the RSS
  // on the same slip system
  MaterialProperty<std::vector<Real>> & _ddislo_velocity_dtau;

};


