/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_GMBUS_H__
#define __INTEW_GMBUS_H__

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;
stwuct i2c_adaptew;

#define GMBUS_PIN_DISABWED	0
#define GMBUS_PIN_SSC		1
#define GMBUS_PIN_VGADDC	2
#define GMBUS_PIN_PANEW		3
#define GMBUS_PIN_DPD_CHV	3 /* HDMID_CHV */
#define GMBUS_PIN_DPC		4 /* HDMIC */
#define GMBUS_PIN_DPB		5 /* SDVO, HDMIB */
#define GMBUS_PIN_DPD		6 /* HDMID */
#define GMBUS_PIN_WESEWVED	7 /* 7 wesewved */
#define GMBUS_PIN_1_BXT		1 /* BXT+ (atom) and CNP+ (big cowe) */
#define GMBUS_PIN_2_BXT		2
#define GMBUS_PIN_3_BXT		3
#define GMBUS_PIN_4_CNP		4
#define GMBUS_PIN_5_MTP		5
#define GMBUS_PIN_9_TC1_ICP	9
#define GMBUS_PIN_10_TC2_ICP	10
#define GMBUS_PIN_11_TC3_ICP	11
#define GMBUS_PIN_12_TC4_ICP	12
#define GMBUS_PIN_13_TC5_TGP	13
#define GMBUS_PIN_14_TC6_TGP	14

#define GMBUS_NUM_PINS	15 /* incwuding 0 */

int intew_gmbus_setup(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_gmbus_teawdown(stwuct dwm_i915_pwivate *dev_pwiv);
boow intew_gmbus_is_vawid_pin(stwuct dwm_i915_pwivate *dev_pwiv,
			      unsigned int pin);
int intew_gmbus_output_aksv(stwuct i2c_adaptew *adaptew);

stwuct i2c_adaptew *
intew_gmbus_get_adaptew(stwuct dwm_i915_pwivate *dev_pwiv, unsigned int pin);
void intew_gmbus_fowce_bit(stwuct i2c_adaptew *adaptew, boow fowce_bit);
boow intew_gmbus_is_fowced_bit(stwuct i2c_adaptew *adaptew);
void intew_gmbus_weset(stwuct dwm_i915_pwivate *dev_pwiv);

void intew_gmbus_iwq_handwew(stwuct dwm_i915_pwivate *i915);

#endif /* __INTEW_GMBUS_H__ */
