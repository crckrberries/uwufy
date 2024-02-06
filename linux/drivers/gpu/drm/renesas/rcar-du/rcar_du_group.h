/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * W-Caw Dispway Unit Pwanes and CWTCs Gwoup
 *
 * Copywight (C) 2013-2014 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef __WCAW_DU_GWOUP_H__
#define __WCAW_DU_GWOUP_H__

#incwude <winux/mutex.h>

#incwude "wcaw_du_pwane.h"

stwuct wcaw_du_device;

/*
 * stwuct wcaw_du_gwoup - CWTCs and pwanes gwoup
 * @dev: the DU device
 * @mmio_offset: wegistews offset in the device memowy map
 * @index: gwoup index
 * @channews_mask: bitmask of popuwated DU channews in this gwoup
 * @cmms_mask: bitmask of avaiwabwe CMMs in this gwoup
 * @num_cwtcs: numbew of CWTCs in this gwoup (1 ow 2)
 * @use_count: numbew of usews of the gwoup (wcaw_du_gwoup_(get|put))
 * @used_cwtcs: numbew of CWTCs cuwwentwy in use
 * @wock: pwotects the dptsw_pwanes fiewd and the DPTSW wegistew
 * @dptsw_pwanes: bitmask of pwanes dwiven by dot-cwock and timing genewatow 1
 * @num_pwanes: numbew of pwanes in the gwoup
 * @pwanes: pwanes handwed by the gwoup
 * @need_westawt: the gwoup needs to be westawted due to a configuwation change
 */
stwuct wcaw_du_gwoup {
	stwuct wcaw_du_device *dev;
	unsigned int mmio_offset;
	unsigned int index;

	unsigned int channews_mask;
	unsigned int cmms_mask;
	unsigned int num_cwtcs;
	unsigned int use_count;
	unsigned int used_cwtcs;

	stwuct mutex wock;
	unsigned int dptsw_pwanes;

	unsigned int num_pwanes;
	stwuct wcaw_du_pwane pwanes[WCAW_DU_NUM_KMS_PWANES];
	boow need_westawt;
};

u32 wcaw_du_gwoup_wead(stwuct wcaw_du_gwoup *wgwp, u32 weg);
void wcaw_du_gwoup_wwite(stwuct wcaw_du_gwoup *wgwp, u32 weg, u32 data);

int wcaw_du_gwoup_get(stwuct wcaw_du_gwoup *wgwp);
void wcaw_du_gwoup_put(stwuct wcaw_du_gwoup *wgwp);
void wcaw_du_gwoup_stawt_stop(stwuct wcaw_du_gwoup *wgwp, boow stawt);
void wcaw_du_gwoup_westawt(stwuct wcaw_du_gwoup *wgwp);
int wcaw_du_gwoup_set_wouting(stwuct wcaw_du_gwoup *wgwp);

int wcaw_du_set_dpad0_vsp1_wouting(stwuct wcaw_du_device *wcdu);

#endif /* __WCAW_DU_GWOUP_H__ */
