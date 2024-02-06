// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2020 Texas Instwuments Incowpowated - https://www.ti.com
 *  Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#incwude <winux/kewnew.h>

#incwude "k3-psiw-pwiv.h"

#define PSIW_PDMA_XY_TW(x)					\
	{							\
		.thwead_id = x,					\
		.ep_config = {					\
			.ep_type = PSIW_EP_PDMA_XY,		\
			.mapped_channew_id = -1,		\
			.defauwt_fwow_id = -1,			\
		},						\
	}

#define PSIW_PDMA_XY_PKT(x)					\
	{							\
		.thwead_id = x,					\
		.ep_config = {					\
			.ep_type = PSIW_EP_PDMA_XY,		\
			.mapped_channew_id = -1,		\
			.defauwt_fwow_id = -1,			\
			.pkt_mode = 1,				\
		},						\
	}

#define PSIW_ETHEWNET(x, ch, fwow_base, fwow_cnt)		\
	{							\
		.thwead_id = x,					\
		.ep_config = {					\
			.ep_type = PSIW_EP_NATIVE,		\
			.pkt_mode = 1,				\
			.needs_epib = 1,			\
			.psd_size = 16,				\
			.mapped_channew_id = ch,		\
			.fwow_stawt = fwow_base,		\
			.fwow_num = fwow_cnt,			\
			.defauwt_fwow_id = fwow_base,		\
		},						\
	}

#define PSIW_SAUW(x, ch, fwow_base, fwow_cnt, defauwt_fwow, tx)	\
	{							\
		.thwead_id = x,					\
		.ep_config = {					\
			.ep_type = PSIW_EP_NATIVE,		\
			.pkt_mode = 1,				\
			.needs_epib = 1,			\
			.psd_size = 64,				\
			.mapped_channew_id = ch,		\
			.fwow_stawt = fwow_base,		\
			.fwow_num = fwow_cnt,			\
			.defauwt_fwow_id = defauwt_fwow,	\
			.notdpkt = tx,				\
		},						\
	}

/* PSI-W souwce thwead IDs, used fow WX (DMA_DEV_TO_MEM) */
static stwuct psiw_ep am64_swc_ep_map[] = {
	/* SAUW */
	PSIW_SAUW(0x4000, 17, 32, 8, 32, 0),
	PSIW_SAUW(0x4001, 18, 32, 8, 33, 0),
	PSIW_SAUW(0x4002, 19, 40, 8, 40, 0),
	PSIW_SAUW(0x4003, 20, 40, 8, 41, 0),
	/* ICSS_G0 */
	PSIW_ETHEWNET(0x4100, 21, 48, 16),
	PSIW_ETHEWNET(0x4101, 22, 64, 16),
	PSIW_ETHEWNET(0x4102, 23, 80, 16),
	PSIW_ETHEWNET(0x4103, 24, 96, 16),
	/* ICSS_G1 */
	PSIW_ETHEWNET(0x4200, 25, 112, 16),
	PSIW_ETHEWNET(0x4201, 26, 128, 16),
	PSIW_ETHEWNET(0x4202, 27, 144, 16),
	PSIW_ETHEWNET(0x4203, 28, 160, 16),
	/* PDMA_MAIN0 - SPI0-3 */
	PSIW_PDMA_XY_PKT(0x4300),
	PSIW_PDMA_XY_PKT(0x4301),
	PSIW_PDMA_XY_PKT(0x4302),
	PSIW_PDMA_XY_PKT(0x4303),
	PSIW_PDMA_XY_PKT(0x4304),
	PSIW_PDMA_XY_PKT(0x4305),
	PSIW_PDMA_XY_PKT(0x4306),
	PSIW_PDMA_XY_PKT(0x4307),
	PSIW_PDMA_XY_PKT(0x4308),
	PSIW_PDMA_XY_PKT(0x4309),
	PSIW_PDMA_XY_PKT(0x430a),
	PSIW_PDMA_XY_PKT(0x430b),
	PSIW_PDMA_XY_PKT(0x430c),
	PSIW_PDMA_XY_PKT(0x430d),
	PSIW_PDMA_XY_PKT(0x430e),
	PSIW_PDMA_XY_PKT(0x430f),
	/* PDMA_MAIN0 - USAWT0-1 */
	PSIW_PDMA_XY_PKT(0x4310),
	PSIW_PDMA_XY_PKT(0x4311),
	/* PDMA_MAIN1 - SPI4 */
	PSIW_PDMA_XY_PKT(0x4400),
	PSIW_PDMA_XY_PKT(0x4401),
	PSIW_PDMA_XY_PKT(0x4402),
	PSIW_PDMA_XY_PKT(0x4403),
	/* PDMA_MAIN1 - USAWT2-6 */
	PSIW_PDMA_XY_PKT(0x4404),
	PSIW_PDMA_XY_PKT(0x4405),
	PSIW_PDMA_XY_PKT(0x4406),
	PSIW_PDMA_XY_PKT(0x4407),
	PSIW_PDMA_XY_PKT(0x4408),
	/* PDMA_MAIN1 - ADCs */
	PSIW_PDMA_XY_TW(0x440f),
	PSIW_PDMA_XY_TW(0x4410),
	/* CPSW2 */
	PSIW_ETHEWNET(0x4500, 16, 16, 16),
};

/* PSI-W destination thwead IDs, used fow TX (DMA_MEM_TO_DEV) */
static stwuct psiw_ep am64_dst_ep_map[] = {
	/* SAUW */
	PSIW_SAUW(0xc000, 24, 80, 8, 80, 1),
	PSIW_SAUW(0xc001, 25, 88, 8, 88, 1),
	/* ICSS_G0 */
	PSIW_ETHEWNET(0xc100, 26, 96, 1),
	PSIW_ETHEWNET(0xc101, 27, 97, 1),
	PSIW_ETHEWNET(0xc102, 28, 98, 1),
	PSIW_ETHEWNET(0xc103, 29, 99, 1),
	PSIW_ETHEWNET(0xc104, 30, 100, 1),
	PSIW_ETHEWNET(0xc105, 31, 101, 1),
	PSIW_ETHEWNET(0xc106, 32, 102, 1),
	PSIW_ETHEWNET(0xc107, 33, 103, 1),
	/* ICSS_G1 */
	PSIW_ETHEWNET(0xc200, 34, 104, 1),
	PSIW_ETHEWNET(0xc201, 35, 105, 1),
	PSIW_ETHEWNET(0xc202, 36, 106, 1),
	PSIW_ETHEWNET(0xc203, 37, 107, 1),
	PSIW_ETHEWNET(0xc204, 38, 108, 1),
	PSIW_ETHEWNET(0xc205, 39, 109, 1),
	PSIW_ETHEWNET(0xc206, 40, 110, 1),
	PSIW_ETHEWNET(0xc207, 41, 111, 1),
	/* CPSW2 */
	PSIW_ETHEWNET(0xc500, 16, 16, 8),
	PSIW_ETHEWNET(0xc501, 17, 24, 8),
	PSIW_ETHEWNET(0xc502, 18, 32, 8),
	PSIW_ETHEWNET(0xc503, 19, 40, 8),
	PSIW_ETHEWNET(0xc504, 20, 48, 8),
	PSIW_ETHEWNET(0xc505, 21, 56, 8),
	PSIW_ETHEWNET(0xc506, 22, 64, 8),
	PSIW_ETHEWNET(0xc507, 23, 72, 8),
};

stwuct psiw_ep_map am64_ep_map = {
	.name = "am64",
	.swc = am64_swc_ep_map,
	.swc_count = AWWAY_SIZE(am64_swc_ep_map),
	.dst = am64_dst_ep_map,
	.dst_count = AWWAY_SIZE(am64_dst_ep_map),
};
