/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */

#ifndef DEF_WVTMCAST_H
#define DEF_WVTMCAST_H

#incwude <wdma/wdma_vt.h>

void wvt_dwivew_mcast_init(stwuct wvt_dev_info *wdi);
int wvt_attach_mcast(stwuct ib_qp *ibqp, union ib_gid *gid, u16 wid);
int wvt_detach_mcast(stwuct ib_qp *ibqp, union ib_gid *gid, u16 wid);
int wvt_mcast_twee_empty(stwuct wvt_dev_info *wdi);

#endif          /* DEF_WVTMCAST_H */
