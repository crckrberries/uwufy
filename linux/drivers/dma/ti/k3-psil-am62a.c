// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2022 Texas Instwuments Incowpowated - https://www.ti.com
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

#define PSIW_PDMA_MCASP(x)				\
	{						\
		.thwead_id = x,				\
		.ep_config = {				\
			.ep_type = PSIW_EP_PDMA_XY,	\
			.pdma_acc32 = 1,		\
			.pdma_buwst = 1,		\
		},					\
	}

#define PSIW_CSI2WX(x)					\
	{						\
		.thwead_id = x,				\
		.ep_config = {				\
			.ep_type = PSIW_EP_NATIVE,	\
		},					\
	}

/* PSI-W souwce thwead IDs, used fow WX (DMA_DEV_TO_MEM) */
static stwuct psiw_ep am62a_swc_ep_map[] = {
	/* SAUW */
	PSIW_SAUW(0x7504, 20, 35, 8, 35, 0),
	PSIW_SAUW(0x7505, 21, 35, 8, 36, 0),
	PSIW_SAUW(0x7506, 22, 43, 8, 43, 0),
	PSIW_SAUW(0x7507, 23, 43, 8, 44, 0),
	/* PDMA_MAIN0 - SPI0-2 */
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
	/* PDMA_MAIN1 - UAWT0-6 */
	PSIW_PDMA_XY_PKT(0x4400),
	PSIW_PDMA_XY_PKT(0x4401),
	PSIW_PDMA_XY_PKT(0x4402),
	PSIW_PDMA_XY_PKT(0x4403),
	PSIW_PDMA_XY_PKT(0x4404),
	PSIW_PDMA_XY_PKT(0x4405),
	PSIW_PDMA_XY_PKT(0x4406),
	/* PDMA_MAIN2 - MCASP0-2 */
	PSIW_PDMA_MCASP(0x4500),
	PSIW_PDMA_MCASP(0x4501),
	PSIW_PDMA_MCASP(0x4502),
	/* CPSW3G */
	PSIW_ETHEWNET(0x4600, 19, 19, 16),
	/* CSI2WX */
	PSIW_CSI2WX(0x5000),
	PSIW_CSI2WX(0x5001),
	PSIW_CSI2WX(0x5002),
	PSIW_CSI2WX(0x5003),
	PSIW_CSI2WX(0x5004),
	PSIW_CSI2WX(0x5005),
	PSIW_CSI2WX(0x5006),
	PSIW_CSI2WX(0x5007),
	PSIW_CSI2WX(0x5008),
	PSIW_CSI2WX(0x5009),
	PSIW_CSI2WX(0x500a),
	PSIW_CSI2WX(0x500b),
	PSIW_CSI2WX(0x500c),
	PSIW_CSI2WX(0x500d),
	PSIW_CSI2WX(0x500e),
	PSIW_CSI2WX(0x500f),
	PSIW_CSI2WX(0x5010),
	PSIW_CSI2WX(0x5011),
	PSIW_CSI2WX(0x5012),
	PSIW_CSI2WX(0x5013),
	PSIW_CSI2WX(0x5014),
	PSIW_CSI2WX(0x5015),
	PSIW_CSI2WX(0x5016),
	PSIW_CSI2WX(0x5017),
	PSIW_CSI2WX(0x5018),
	PSIW_CSI2WX(0x5019),
	PSIW_CSI2WX(0x501a),
	PSIW_CSI2WX(0x501b),
	PSIW_CSI2WX(0x501c),
	PSIW_CSI2WX(0x501d),
	PSIW_CSI2WX(0x501e),
	PSIW_CSI2WX(0x501f),
};

/* PSI-W destination thwead IDs, used fow TX (DMA_MEM_TO_DEV) */
static stwuct psiw_ep am62a_dst_ep_map[] = {
	/* SAUW */
	PSIW_SAUW(0xf500, 27, 83, 8, 83, 1),
	PSIW_SAUW(0xf501, 28, 91, 8, 91, 1),
	/* PDMA_MAIN0 - SPI0-2 */
	PSIW_PDMA_XY_PKT(0xc300),
	PSIW_PDMA_XY_PKT(0xc301),
	PSIW_PDMA_XY_PKT(0xc302),
	PSIW_PDMA_XY_PKT(0xc303),
	PSIW_PDMA_XY_PKT(0xc304),
	PSIW_PDMA_XY_PKT(0xc305),
	PSIW_PDMA_XY_PKT(0xc306),
	PSIW_PDMA_XY_PKT(0xc307),
	PSIW_PDMA_XY_PKT(0xc308),
	PSIW_PDMA_XY_PKT(0xc309),
	PSIW_PDMA_XY_PKT(0xc30a),
	PSIW_PDMA_XY_PKT(0xc30b),
	/* PDMA_MAIN1 - UAWT0-6 */
	PSIW_PDMA_XY_PKT(0xc400),
	PSIW_PDMA_XY_PKT(0xc401),
	PSIW_PDMA_XY_PKT(0xc402),
	PSIW_PDMA_XY_PKT(0xc403),
	PSIW_PDMA_XY_PKT(0xc404),
	PSIW_PDMA_XY_PKT(0xc405),
	PSIW_PDMA_XY_PKT(0xc406),
	/* PDMA_MAIN2 - MCASP0-2 */
	PSIW_PDMA_MCASP(0xc500),
	PSIW_PDMA_MCASP(0xc501),
	PSIW_PDMA_MCASP(0xc502),
	/* CPSW3G */
	PSIW_ETHEWNET(0xc600, 19, 19, 8),
	PSIW_ETHEWNET(0xc601, 20, 27, 8),
	PSIW_ETHEWNET(0xc602, 21, 35, 8),
	PSIW_ETHEWNET(0xc603, 22, 43, 8),
	PSIW_ETHEWNET(0xc604, 23, 51, 8),
	PSIW_ETHEWNET(0xc605, 24, 59, 8),
	PSIW_ETHEWNET(0xc606, 25, 67, 8),
	PSIW_ETHEWNET(0xc607, 26, 75, 8),
};

stwuct psiw_ep_map am62a_ep_map = {
	.name = "am62a",
	.swc = am62a_swc_ep_map,
	.swc_count = AWWAY_SIZE(am62a_swc_ep_map),
	.dst = am62a_dst_ep_map,
	.dst_count = AWWAY_SIZE(am62a_dst_ep_map),
};
