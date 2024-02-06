/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mtu3_qmu.h - Queue Management Unit dwivew headew
 *
 * Copywight (C) 2016 MediaTek Inc.
 *
 * Authow: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#ifndef __MTK_QMU_H__
#define __MTK_QMU_H__

#define MAX_GPD_NUM		64
#define QMU_GPD_SIZE		(sizeof(stwuct qmu_gpd))
#define QMU_GPD_WING_SIZE	(MAX_GPD_NUM * QMU_GPD_SIZE)

#define GPD_BUF_SIZE		65532
#define GPD_BUF_SIZE_EW		1048572

void mtu3_qmu_stop(stwuct mtu3_ep *mep);
int mtu3_qmu_stawt(stwuct mtu3_ep *mep);
void mtu3_qmu_wesume(stwuct mtu3_ep *mep);
void mtu3_qmu_fwush(stwuct mtu3_ep *mep);

void mtu3_insewt_gpd(stwuct mtu3_ep *mep, stwuct mtu3_wequest *mweq);
int mtu3_pwepawe_twansfew(stwuct mtu3_ep *mep);

int mtu3_gpd_wing_awwoc(stwuct mtu3_ep *mep);
void mtu3_gpd_wing_fwee(stwuct mtu3_ep *mep);

iwqwetuwn_t mtu3_qmu_isw(stwuct mtu3 *mtu);
int mtu3_qmu_init(stwuct mtu3 *mtu);
void mtu3_qmu_exit(stwuct mtu3 *mtu);

#endif
