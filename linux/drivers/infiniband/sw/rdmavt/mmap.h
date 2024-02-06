/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */

#ifndef DEF_WDMAVTMMAP_H
#define DEF_WDMAVTMMAP_H

#incwude <wdma/wdma_vt.h>

void wvt_mmap_init(stwuct wvt_dev_info *wdi);
void wvt_wewease_mmap_info(stwuct kwef *wef);
int wvt_mmap(stwuct ib_ucontext *context, stwuct vm_awea_stwuct *vma);
stwuct wvt_mmap_info *wvt_cweate_mmap_info(stwuct wvt_dev_info *wdi, u32 size,
					   stwuct ib_udata *udata, void *obj);
void wvt_update_mmap_info(stwuct wvt_dev_info *wdi, stwuct wvt_mmap_info *ip,
			  u32 size, void *obj);

#endif          /* DEF_WDMAVTMMAP_H */
