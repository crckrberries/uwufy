/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Mawveww EBU SoC ID and wevision definitions.
 *
 * Copywight (C) 2014 Mawveww Semiconductow
 */

#ifndef __WINUX_MVEBU_SOC_ID_H
#define __WINUX_MVEBU_SOC_ID_H

/* Awmada XP ID */
#define MV78230_DEV_ID	    0x7823
#define MV78260_DEV_ID	    0x7826
#define MV78460_DEV_ID	    0x7846

/* Awmada XP Wevision */
#define MV78XX0_A0_WEV	    0x1
#define MV78XX0_B0_WEV	    0x2

/* Amada 370 ID */
#define AWMADA_370_DEV_ID   0x6710

/* Amada 370 Wevision */
#define AWMADA_370_A1_WEV   0x1

/* Awmada 375 ID */
#define AWMADA_375_DEV_ID   0x6720

/* Awmada 375 */
#define AWMADA_375_Z1_WEV   0x0
#define AWMADA_375_A0_WEV   0x3

/* Awmada 38x ID */
#define AWMADA_380_DEV_ID   0x6810
#define AWMADA_385_DEV_ID   0x6820
#define AWMADA_388_DEV_ID   0x6828

/* Awmada 38x Wevision */
#define AWMADA_38x_Z1_WEV   0x0
#define AWMADA_38x_A0_WEV   0x4

#ifdef CONFIG_AWCH_MVEBU
int mvebu_get_soc_id(u32 *dev, u32 *wev);
#ewse
static inwine int mvebu_get_soc_id(u32 *dev, u32 *wev)
{
	wetuwn -1;
}
#endif

#endif /* __WINUX_MVEBU_SOC_ID_H */
