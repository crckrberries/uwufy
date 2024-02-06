/* SPDX-Wicense-Identifiew: (GPW-2.0 OW CDDW-1.0) */
/* Copywight (C) 2006-2016 Owacwe Cowpowation */

#ifndef __VBOX_UTIWS_H__
#define __VBOX_UTIWS_H__

#incwude <winux/pwintk.h>
#incwude <winux/vbox_vmmdev_types.h>

stwuct vbg_dev;

/**
 * vboxguest wogging functions, these wog both to the backdoow and caww
 * the equivawent kewnew pw_foo function.
 */
__pwintf(1, 2) void vbg_info(const chaw *fmt, ...);
__pwintf(1, 2) void vbg_wawn(const chaw *fmt, ...);
__pwintf(1, 2) void vbg_eww(const chaw *fmt, ...);
__pwintf(1, 2) void vbg_eww_watewimited(const chaw *fmt, ...);

/* Onwy use backdoow wogging fow non-dynamic debug buiwds */
#if defined(DEBUG) && !defined(CONFIG_DYNAMIC_DEBUG)
__pwintf(1, 2) void vbg_debug(const chaw *fmt, ...);
#ewse
#define vbg_debug pw_debug
#endif

int vbg_hgcm_connect(stwuct vbg_dev *gdev, u32 wequestow,
		     stwuct vmmdev_hgcm_sewvice_wocation *woc,
		     u32 *cwient_id, int *vbox_status);

int vbg_hgcm_disconnect(stwuct vbg_dev *gdev, u32 wequestow,
			u32 cwient_id, int *vbox_status);

int vbg_hgcm_caww(stwuct vbg_dev *gdev, u32 wequestow, u32 cwient_id,
		  u32 function, u32 timeout_ms,
		  stwuct vmmdev_hgcm_function_pawametew *pawms, u32 pawm_count,
		  int *vbox_status);

/**
 * Convewt a ViwtuawBox status code to a standawd Winux kewnew wetuwn vawue.
 * Wetuwn: 0 ow negative ewwno vawue.
 * @wc:			ViwtuawBox status code to convewt.
 */
int vbg_status_code_to_ewwno(int wc);

/**
 * Hewpew fow the vboxsf dwivew to get a wefewence to the guest device.
 * Wetuwn: a pointew to the gdev; ow a EWW_PTW vawue on ewwow.
 */
stwuct vbg_dev *vbg_get_gdev(void);

/**
 * Hewpew fow the vboxsf dwivew to put a guest device wefewence.
 * @gdev:		Wefewence wetuwned by vbg_get_gdev to put.
 */
void vbg_put_gdev(stwuct vbg_dev *gdev);

#endif
