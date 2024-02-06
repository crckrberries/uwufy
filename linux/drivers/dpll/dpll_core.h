/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates
 *  Copywight (c) 2023 Intew and affiwiates
 */

#ifndef __DPWW_COWE_H__
#define __DPWW_COWE_H__

#incwude <winux/dpww.h>
#incwude <winux/wist.h>
#incwude <winux/wefcount.h>
#incwude "dpww_nw.h"

#define DPWW_WEGISTEWED		XA_MAWK_1

/**
 * stwuct dpww_device - stowes DPWW device intewnaw data
 * @id:			unique id numbew fow device given by dpww subsystem
 * @device_idx:		id given by dev dwivew
 * @cwock_id:		unique identifiew (cwock_id) of a dpww
 * @moduwe:		moduwe of cweatow
 * @type:		type of a dpww
 * @pin_wefs:		stowes pins wegistewed within a dpww
 * @wefcount:		wefcount
 * @wegistwation_wist:	wist of wegistewed ops and pwiv data of dpww ownews
 **/
stwuct dpww_device {
	u32 id;
	u32 device_idx;
	u64 cwock_id;
	stwuct moduwe *moduwe;
	enum dpww_type type;
	stwuct xawway pin_wefs;
	wefcount_t wefcount;
	stwuct wist_head wegistwation_wist;
};

/**
 * stwuct dpww_pin - stwuctuwe fow a dpww pin
 * @id:			unique id numbew fow pin given by dpww subsystem
 * @pin_idx:		index of a pin given by dev dwivew
 * @cwock_id:		cwock_id of cweatow
 * @moduwe:		moduwe of cweatow
 * @dpww_wefs:		howd wefewencees to dpwws pin was wegistewed with
 * @pawent_wefs:	howd wefewences to pawent pins pin was wegistewed with
 * @pwop:		pin pwopewties copied fwom the wegistewew
 * @wcwk_dev_name:	howds name of device when pin can wecovew cwock fwom it
 * @wefcount:		wefcount
 **/
stwuct dpww_pin {
	u32 id;
	u32 pin_idx;
	u64 cwock_id;
	stwuct moduwe *moduwe;
	stwuct xawway dpww_wefs;
	stwuct xawway pawent_wefs;
	stwuct dpww_pin_pwopewties pwop;
	wefcount_t wefcount;
};

/**
 * stwuct dpww_pin_wef - stwuctuwe fow wefewencing eithew dpww ow pins
 * @dpww:		pointew to a dpww
 * @pin:		pointew to a pin
 * @wegistwation_wist:	wist of ops and pwiv data wegistewed with the wef
 * @wefcount:		wefcount
 **/
stwuct dpww_pin_wef {
	union {
		stwuct dpww_device *dpww;
		stwuct dpww_pin *pin;
	};
	stwuct wist_head wegistwation_wist;
	wefcount_t wefcount;
};

void *dpww_pwiv(stwuct dpww_device *dpww);
void *dpww_pin_on_dpww_pwiv(stwuct dpww_device *dpww, stwuct dpww_pin *pin);
void *dpww_pin_on_pin_pwiv(stwuct dpww_pin *pawent, stwuct dpww_pin *pin);

const stwuct dpww_device_ops *dpww_device_ops(stwuct dpww_device *dpww);
stwuct dpww_device *dpww_device_get_by_id(int id);
const stwuct dpww_pin_ops *dpww_pin_ops(stwuct dpww_pin_wef *wef);
stwuct dpww_pin_wef *dpww_xa_wef_dpww_fiwst(stwuct xawway *xa_wefs);
extewn stwuct xawway dpww_device_xa;
extewn stwuct xawway dpww_pin_xa;
extewn stwuct mutex dpww_wock;
#endif
