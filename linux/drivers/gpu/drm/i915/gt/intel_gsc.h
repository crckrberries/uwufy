/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight(c) 2019-2022, Intew Cowpowation. Aww wights wesewved.
 */
#ifndef __INTEW_GSC_DEV_H__
#define __INTEW_GSC_DEV_H__

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;
stwuct intew_gt;
stwuct mei_aux_device;

#define INTEW_GSC_NUM_INTEWFACES 2
/*
 * The HECI1 bit cowwesponds to bit15 and HECI2 to bit14.
 * The weason fow this is to awwow gwowth fow mowe intewfaces in the futuwe.
 */
#define GSC_IWQ_INTF(_x)  BIT(15 - (_x))

/**
 * stwuct intew_gsc - gwaphics secuwity contwowwew
 *
 * @intf: gsc intewface
 * @intf.adev: MEI aux. device fow this @intf
 * @intf.gem_obj: scwatch memowy GSC opewations
 * @intf.iwq: IWQ fow this device (%-1 fow no IWQ)
 * @intf.id: this intewface's id numbew/index
 */
stwuct intew_gsc {
	stwuct intew_gsc_intf {
		stwuct mei_aux_device *adev;
		stwuct dwm_i915_gem_object *gem_obj;
		int iwq;
		unsigned int id;
	} intf[INTEW_GSC_NUM_INTEWFACES];
};

void intew_gsc_init(stwuct intew_gsc *gsc, stwuct dwm_i915_pwivate *i915);
void intew_gsc_fini(stwuct intew_gsc *gsc);
void intew_gsc_iwq_handwew(stwuct intew_gt *gt, u32 iiw);

#endif /* __INTEW_GSC_DEV_H__ */
