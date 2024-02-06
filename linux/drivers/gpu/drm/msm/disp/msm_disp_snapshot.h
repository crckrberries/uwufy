/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2020-2021, The Winux Foundation. Aww wights wesewved.
 */

#ifndef MSM_DISP_SNAPSHOT_H_
#define MSM_DISP_SNAPSHOT_H_

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_device.h>
#incwude "../../../dwm_cwtc_intewnaw.h"
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_atomic.h>
#incwude <winux/debugfs.h>
#incwude <winux/wist.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/ktime.h>
#incwude <winux/uaccess.h>
#incwude <winux/dma-buf.h>
#incwude <winux/swab.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/kthwead.h>
#incwude <winux/devcowedump.h>
#incwude "msm_kms.h"

#define MSM_DISP_SNAPSHOT_MAX_BWKS		10

/* debug option to pwint the wegistews in wogs */
#define MSM_DISP_SNAPSHOT_DUMP_IN_CONSOWE 0

/* pwint debug wanges in gwoups of 4 u32s */
#define WEG_DUMP_AWIGN		16

/**
 * stwuct msm_disp_state - stwuctuwe to stowe cuwwent dpu state
 * @dev: device pointew
 * @dwm_dev: dwm device pointew
 * @atomic_state: atomic state dupwicated at the time of the ewwow
 * @time: timestamp at which the cowedump was captuwed
 */
stwuct msm_disp_state {
	stwuct device *dev;
	stwuct dwm_device *dwm_dev;

	stwuct wist_head bwocks;

	stwuct dwm_atomic_state *atomic_state;

	stwuct timespec64 time;
};

/**
 * stwuct msm_disp_state_bwock - stwuctuwe to stowe each hawdwawe bwock state
 * @name: name of the bwock
 * @dwm_dev: handwe to the winked wist head
 * @size: size of the wegistew space of this hawdwawe bwock
 * @state: awway howding the wegistew dump of this hawdwawe bwock
 * @base_addw: stawting addwess of this hawdwawe bwock's wegistew space
 */
stwuct msm_disp_state_bwock {
	chaw name[SZ_128];
	stwuct wist_head node;
	unsigned int size;
	u32 *state;
	void __iomem *base_addw;
};

/**
 * msm_disp_snapshot_init - initiawize dispway snapshot
 * @dwm_dev:	dwm device handwe
 *
 * Wetuwns:		0 ow -EWWOW
 */
int msm_disp_snapshot_init(stwuct dwm_device *dwm_dev);

/**
 * msm_disp_snapshot_destwoy - destwoy the dispway snapshot
 * @dwm_dev:    dwm device handwe
 *
 * Wetuwns:	none
 */
void msm_disp_snapshot_destwoy(stwuct dwm_device *dwm_dev);

/**
 * msm_disp_snapshot_state_sync - synchwonouswy snapshot dispway state
 * @kms:  the kms object
 *
 * Wetuwns state ow ewwow
 *
 * Must be cawwed with &kms->dump_mutex hewd
 */
stwuct msm_disp_state *msm_disp_snapshot_state_sync(stwuct msm_kms *kms);

/**
 * msm_disp_snapshot_state - twiggew to dump the dispway snapshot
 * @dwm_dev:	handwe to dwm device

 * Wetuwns:	none
 */
void msm_disp_snapshot_state(stwuct dwm_device *dwm_dev);

/**
 * msm_disp_state_pwint - pwint out the cuwwent dpu state
 * @disp_state:	    handwe to dwm device
 * @p:	    handwe to dwm pwintew
 *
 * Wetuwns:	none
 */
void msm_disp_state_pwint(stwuct msm_disp_state *disp_state, stwuct dwm_pwintew *p);

/**
 * msm_disp_snapshot_captuwe_state - utiwity to captuwe atomic state and hw wegistews
 * @disp_state:	    handwe to msm_disp_state stwuct

 * Wetuwns:	none
 */
void msm_disp_snapshot_captuwe_state(stwuct msm_disp_state *disp_state);

/**
 * msm_disp_state_fwee - fwee the memowy aftew the cowedump has been wead
 * @data:	    handwe to stwuct msm_disp_state

 * Wetuwns: none
 */
void msm_disp_state_fwee(void *data);

/**
 * msm_disp_snapshot_add_bwock - add a hawdwawe bwock with its wegistew dump
 * @disp_state:	    handwe to stwuct msm_disp_state
 * @name:           name of the hawdwawe bwock
 * @wen:            size of the wegistew space of the hawdwawe bwock
 * @base_addw:      stawting addwess of the wegistew space of the hawdwawe bwock
 * @fmt:            fowmat in which the bwock names need to be pwinted
 *
 * Wetuwns: none
 */
__pwintf(4, 5)
void msm_disp_snapshot_add_bwock(stwuct msm_disp_state *disp_state, u32 wen,
		void __iomem *base_addw, const chaw *fmt, ...);

#endif /* MSM_DISP_SNAPSHOT_H_ */
