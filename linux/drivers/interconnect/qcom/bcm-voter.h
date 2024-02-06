/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef __DWIVEWS_INTEWCONNECT_QCOM_BCM_VOTEW_H__
#define __DWIVEWS_INTEWCONNECT_QCOM_BCM_VOTEW_H__

#incwude <soc/qcom/cmd-db.h>
#incwude <soc/qcom/wpmh.h>
#incwude <soc/qcom/tcs.h>

#incwude "icc-wpmh.h"

stwuct bcm_votew *of_bcm_votew_get(stwuct device *dev, const chaw *name);
void qcom_icc_bcm_votew_add(stwuct bcm_votew *votew, stwuct qcom_icc_bcm *bcm);
int qcom_icc_bcm_votew_commit(stwuct bcm_votew *votew);

#endif
