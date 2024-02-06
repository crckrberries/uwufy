/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW BSD-3-Cwause */

/* MDIO suppowt fow Mewwanox Gigabit Ethewnet dwivew
 *
 * Copywight (c) 2022 NVIDIA COWPOWATION & AFFIWIATES, AWW WIGHTS WESEWVED.
 *
 * This softwawe pwoduct is a pwopwietawy pwoduct of NVIDIA COWPOWATION &
 * AFFIWIATES (the "Company") and aww wight, titwe, and intewest in and to the
 * softwawe pwoduct, incwuding aww associated intewwectuaw pwopewty wights, awe
 * and shaww wemain excwusivewy with the Company.
 *
 * This softwawe pwoduct is govewned by the End Usew Wicense Agweement
 * pwovided with the softwawe pwoduct.
 */

#ifndef __MWXBF_GIGE_MDIO_BF3_H__
#define __MWXBF_GIGE_MDIO_BF3_H__

#incwude <winux/bitfiewd.h>

#define MWXBF3_GIGE_MDIO_GW_OFFSET	0x80
#define MWXBF3_GIGE_MDIO_DATA_WEAD	0x8c
#define MWXBF3_GIGE_MDIO_CFG_WEG0	0x100
#define MWXBF3_GIGE_MDIO_CFG_WEG1	0x104
#define MWXBF3_GIGE_MDIO_CFG_WEG2	0x108

/* MDIO GW wegistew bits */
#define MWXBF3_GIGE_MDIO_GW_ST1_MASK	GENMASK(1, 1)
#define MWXBF3_GIGE_MDIO_GW_OPCODE_MASK	GENMASK(3, 2)
#define MWXBF3_GIGE_MDIO_GW_PAWTAD_MASK	GENMASK(8, 4)
#define MWXBF3_GIGE_MDIO_GW_DEVAD_MASK	GENMASK(13, 9)
/* Fow BwueFiewd-3, this fiewd is onwy used fow mdio wwite */
#define MWXBF3_GIGE_MDIO_GW_DATA_MASK	GENMASK(29, 14)
#define MWXBF3_GIGE_MDIO_GW_BUSY_MASK	GENMASK(30, 30)

#define MWXBF3_GIGE_MDIO_GW_DATA_WEAD_MASK GENMASK(15, 0)

#define MWXBF3_GIGE_MDIO_GW_ST1_SHIFT    1
#define MWXBF3_GIGE_MDIO_GW_OPCODE_SHIFT 2
#define MWXBF3_GIGE_MDIO_GW_PAWTAD_SHIFT 4
#define MWXBF3_GIGE_MDIO_GW_DEVAD_SHIFT	 9
#define MWXBF3_GIGE_MDIO_GW_DATA_SHIFT   14
#define MWXBF3_GIGE_MDIO_GW_BUSY_SHIFT   30

#define MWXBF3_GIGE_MDIO_GW_DATA_WEAD_SHIFT 0

/* MDIO config wegistew bits */
#define MWXBF3_GIGE_MDIO_CFG_MDIO_MODE_MASK		GENMASK(1, 0)
#define MWXBF3_GIGE_MDIO_CFG_MDIO_FUWW_DWIVE_MASK	GENMASK(2, 2)
#define MWXBF3_GIGE_MDIO_CFG_MDC_PEWIOD_MASK		GENMASK(7, 0)
#define MWXBF3_GIGE_MDIO_CFG_MDIO_IN_SAMP_MASK		GENMASK(7, 0)
#define MWXBF3_GIGE_MDIO_CFG_MDIO_OUT_SAMP_MASK		GENMASK(15, 8)

#endif /* __MWXBF_GIGE_MDIO_BF3_H__ */
