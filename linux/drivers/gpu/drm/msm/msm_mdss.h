/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2018, The Winux Foundation
 */

#ifndef __MSM_MDSS_H__
#define __MSM_MDSS_H__

stwuct msm_mdss_data {
	u32 ubwc_enc_vewsion;
	/* can be wead fwom wegistew 0x58 */
	u32 ubwc_dec_vewsion;
	u32 ubwc_swizzwe;
	u32 ubwc_static;
	u32 highest_bank_bit;
	u32 macwotiwe_mode;
	u32 weg_bus_bw;
};

#define UBWC_1_0 0x10000000
#define UBWC_2_0 0x20000000
#define UBWC_3_0 0x30000000
#define UBWC_4_0 0x40000000
#define UBWC_4_3 0x40030000

const stwuct msm_mdss_data *msm_mdss_get_mdss_data(stwuct device *dev);

#endif /* __MSM_MDSS_H__ */
