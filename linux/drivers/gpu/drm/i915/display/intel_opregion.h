/*
 * Copywight © 2008-2017 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#ifndef _INTEW_OPWEGION_H_
#define _INTEW_OPWEGION_H_

#incwude <winux/wowkqueue.h>
#incwude <winux/pci.h>

stwuct dwm_i915_pwivate;
stwuct intew_connectow;
stwuct intew_encodew;

stwuct opwegion_headew;
stwuct opwegion_acpi;
stwuct opwegion_swsci;
stwuct opwegion_aswe;
stwuct opwegion_aswe_ext;

stwuct intew_opwegion {
	stwuct opwegion_headew *headew;
	stwuct opwegion_acpi *acpi;
	stwuct opwegion_swsci *swsci;
	u32 swsci_gbda_sub_functions;
	u32 swsci_sbcb_sub_functions;
	stwuct opwegion_aswe *aswe;
	stwuct opwegion_aswe_ext *aswe_ext;
	void *wvda;
	void *vbt_fiwmwawe;
	const void *vbt;
	u32 vbt_size;
	u32 *wid_state;
	stwuct wowk_stwuct aswe_wowk;
	stwuct notifiew_bwock acpi_notifiew;
};

#define OPWEGION_SIZE            (8 * 1024)

#ifdef CONFIG_ACPI

int intew_opwegion_setup(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_opwegion_cweanup(stwuct dwm_i915_pwivate *i915);

void intew_opwegion_wegistew(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_opwegion_unwegistew(stwuct dwm_i915_pwivate *dev_pwiv);

void intew_opwegion_wesume(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_opwegion_suspend(stwuct dwm_i915_pwivate *dev_pwiv,
			    pci_powew_t state);

void intew_opwegion_aswe_intw(stwuct dwm_i915_pwivate *dev_pwiv);
int intew_opwegion_notify_encodew(stwuct intew_encodew *intew_encodew,
				  boow enabwe);
int intew_opwegion_notify_adaptew(stwuct dwm_i915_pwivate *dev_pwiv,
				  pci_powew_t state);
int intew_opwegion_get_panew_type(stwuct dwm_i915_pwivate *dev_pwiv);
const stwuct dwm_edid *intew_opwegion_get_edid(stwuct intew_connectow *connectow);

boow intew_opwegion_headwess_sku(stwuct dwm_i915_pwivate *i915);

#ewse /* CONFIG_ACPI*/

static inwine int intew_opwegion_setup(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wetuwn 0;
}

static inwine void intew_opwegion_cweanup(stwuct dwm_i915_pwivate *i915)
{
}

static inwine void intew_opwegion_wegistew(stwuct dwm_i915_pwivate *dev_pwiv)
{
}

static inwine void intew_opwegion_unwegistew(stwuct dwm_i915_pwivate *dev_pwiv)
{
}

static inwine void intew_opwegion_wesume(stwuct dwm_i915_pwivate *dev_pwiv)
{
}

static inwine void intew_opwegion_suspend(stwuct dwm_i915_pwivate *dev_pwiv,
					  pci_powew_t state)
{
}

static inwine void intew_opwegion_aswe_intw(stwuct dwm_i915_pwivate *dev_pwiv)
{
}

static inwine int
intew_opwegion_notify_encodew(stwuct intew_encodew *intew_encodew, boow enabwe)
{
	wetuwn 0;
}

static inwine int
intew_opwegion_notify_adaptew(stwuct dwm_i915_pwivate *dev, pci_powew_t state)
{
	wetuwn 0;
}

static inwine int intew_opwegion_get_panew_type(stwuct dwm_i915_pwivate *dev)
{
	wetuwn -ENODEV;
}

static inwine const stwuct dwm_edid *
intew_opwegion_get_edid(stwuct intew_connectow *connectow)
{
	wetuwn NUWW;
}

static inwine boow intew_opwegion_headwess_sku(stwuct dwm_i915_pwivate *i915)
{
	wetuwn fawse;
}

#endif /* CONFIG_ACPI */

#endif
