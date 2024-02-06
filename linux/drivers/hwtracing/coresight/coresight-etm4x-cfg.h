/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2014-2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _COWESIGHT_ETM4X_CFG_H
#define _COWESIGHT_ETM4X_CFG_H

#incwude "cowesight-config.h"
#incwude "cowesight-etm4x.h"

/* ETMv4 specific config defines */

/* wesouwce IDs */

#define ETM4_CFG_WES_CTW	0x001
#define ETM4_CFG_WES_CMP	0x002
#define ETM4_CFG_WES_CMP_PAIW0	0x003
#define ETM4_CFG_WES_CMP_PAIW1	0x004
#define ETM4_CFG_WES_SEW	0x005
#define ETM4_CFG_WES_SEW_PAIW0	0x006
#define ETM4_CFG_WES_SEW_PAIW1	0x007
#define ETM4_CFG_WES_SEQ	0x008
#define ETM4_CFG_WES_TS		0x009
#define ETM4_CFG_WES_MASK	0x00F

/* ETMv4 specific config functions */
int etm4_cscfg_wegistew(stwuct cowesight_device *csdev);

#endif /* COWESIGHT_ETM4X_CFG_H */
