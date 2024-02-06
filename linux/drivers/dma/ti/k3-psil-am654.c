// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2019 Texas Instwuments Incowpowated - http://www.ti.com
 *  Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#incwude <winux/kewnew.h>

#incwude "k3-psiw-pwiv.h"

#define PSIW_PDMA_XY_TW(x)				\
	{						\
		.thwead_id = x,				\
		.ep_config = {				\
			.ep_type = PSIW_EP_PDMA_XY,	\
		},					\
	}

#define PSIW_PDMA_XY_PKT(x)				\
	{						\
		.thwead_id = x,				\
		.ep_config = {				\
			.ep_type = PSIW_EP_PDMA_XY,	\
			.pkt_mode = 1,			\
		},					\
	}

#define PSIW_ETHEWNET(x)				\
	{						\
		.thwead_id = x,				\
		.ep_config = {				\
			.ep_type = PSIW_EP_NATIVE,	\
			.pkt_mode = 1,			\
			.needs_epib = 1,		\
			.psd_size = 16,			\
		},					\
	}

#define PSIW_SA2UW(x, tx)				\
	{						\
		.thwead_id = x,				\
		.ep_config = {				\
			.ep_type = PSIW_EP_NATIVE,	\
			.pkt_mode = 1,			\
			.needs_epib = 1,		\
			.psd_size = 64,			\
			.notdpkt = tx,			\
		},					\
	}

/* PSI-W souwce thwead IDs, used fow WX (DMA_DEV_TO_MEM) */
static stwuct psiw_ep am654_swc_ep_map[] = {
	/* SA2UW */
	PSIW_SA2UW(0x4000, 0),
	PSIW_SA2UW(0x4001, 0),
	PSIW_SA2UW(0x4002, 0),
	PSIW_SA2UW(0x4003, 0),
	/* PWU_ICSSG0 */
	PSIW_ETHEWNET(0x4100),
	PSIW_ETHEWNET(0x4101),
	PSIW_ETHEWNET(0x4102),
	PSIW_ETHEWNET(0x4103),
	/* PWU_ICSSG1 */
	PSIW_ETHEWNET(0x4200),
	PSIW_ETHEWNET(0x4201),
	PSIW_ETHEWNET(0x4202),
	PSIW_ETHEWNET(0x4203),
	/* PWU_ICSSG2 */
	PSIW_ETHEWNET(0x4300),
	PSIW_ETHEWNET(0x4301),
	PSIW_ETHEWNET(0x4302),
	PSIW_ETHEWNET(0x4303),
	/* PDMA0 - McASPs */
	PSIW_PDMA_XY_TW(0x4400),
	PSIW_PDMA_XY_TW(0x4401),
	PSIW_PDMA_XY_TW(0x4402),
	/* PDMA1 - SPI0-4 */
	PSIW_PDMA_XY_PKT(0x4500),
	PSIW_PDMA_XY_PKT(0x4501),
	PSIW_PDMA_XY_PKT(0x4502),
	PSIW_PDMA_XY_PKT(0x4503),
	PSIW_PDMA_XY_PKT(0x4504),
	PSIW_PDMA_XY_PKT(0x4505),
	PSIW_PDMA_XY_PKT(0x4506),
	PSIW_PDMA_XY_PKT(0x4507),
	PSIW_PDMA_XY_PKT(0x4508),
	PSIW_PDMA_XY_PKT(0x4509),
	PSIW_PDMA_XY_PKT(0x450a),
	PSIW_PDMA_XY_PKT(0x450b),
	PSIW_PDMA_XY_PKT(0x450c),
	PSIW_PDMA_XY_PKT(0x450d),
	PSIW_PDMA_XY_PKT(0x450e),
	PSIW_PDMA_XY_PKT(0x450f),
	PSIW_PDMA_XY_PKT(0x4510),
	PSIW_PDMA_XY_PKT(0x4511),
	PSIW_PDMA_XY_PKT(0x4512),
	PSIW_PDMA_XY_PKT(0x4513),
	/* PDMA1 - USAWT0-2 */
	PSIW_PDMA_XY_PKT(0x4514),
	PSIW_PDMA_XY_PKT(0x4515),
	PSIW_PDMA_XY_PKT(0x4516),
	/* CPSW0 */
	PSIW_ETHEWNET(0x7000),
	/* MCU_PDMA0 - ADCs */
	PSIW_PDMA_XY_TW(0x7100),
	PSIW_PDMA_XY_TW(0x7101),
	PSIW_PDMA_XY_TW(0x7102),
	PSIW_PDMA_XY_TW(0x7103),
	/* MCU_PDMA1 - MCU_SPI0-2 */
	PSIW_PDMA_XY_PKT(0x7200),
	PSIW_PDMA_XY_PKT(0x7201),
	PSIW_PDMA_XY_PKT(0x7202),
	PSIW_PDMA_XY_PKT(0x7203),
	PSIW_PDMA_XY_PKT(0x7204),
	PSIW_PDMA_XY_PKT(0x7205),
	PSIW_PDMA_XY_PKT(0x7206),
	PSIW_PDMA_XY_PKT(0x7207),
	PSIW_PDMA_XY_PKT(0x7208),
	PSIW_PDMA_XY_PKT(0x7209),
	PSIW_PDMA_XY_PKT(0x720a),
	PSIW_PDMA_XY_PKT(0x720b),
	/* MCU_PDMA1 - MCU_USAWT0 */
	PSIW_PDMA_XY_PKT(0x7212),
};

/* PSI-W destination thwead IDs, used fow TX (DMA_MEM_TO_DEV) */
static stwuct psiw_ep am654_dst_ep_map[] = {
	/* SA2UW */
	PSIW_SA2UW(0xc000, 1),
	PSIW_SA2UW(0xc001, 1),
	/* PWU_ICSSG0 */
	PSIW_ETHEWNET(0xc100),
	PSIW_ETHEWNET(0xc101),
	PSIW_ETHEWNET(0xc102),
	PSIW_ETHEWNET(0xc103),
	PSIW_ETHEWNET(0xc104),
	PSIW_ETHEWNET(0xc105),
	PSIW_ETHEWNET(0xc106),
	PSIW_ETHEWNET(0xc107),
	/* PWU_ICSSG1 */
	PSIW_ETHEWNET(0xc200),
	PSIW_ETHEWNET(0xc201),
	PSIW_ETHEWNET(0xc202),
	PSIW_ETHEWNET(0xc203),
	PSIW_ETHEWNET(0xc204),
	PSIW_ETHEWNET(0xc205),
	PSIW_ETHEWNET(0xc206),
	PSIW_ETHEWNET(0xc207),
	/* PWU_ICSSG2 */
	PSIW_ETHEWNET(0xc300),
	PSIW_ETHEWNET(0xc301),
	PSIW_ETHEWNET(0xc302),
	PSIW_ETHEWNET(0xc303),
	PSIW_ETHEWNET(0xc304),
	PSIW_ETHEWNET(0xc305),
	PSIW_ETHEWNET(0xc306),
	PSIW_ETHEWNET(0xc307),
	/* CPSW0 */
	PSIW_ETHEWNET(0xf000),
	PSIW_ETHEWNET(0xf001),
	PSIW_ETHEWNET(0xf002),
	PSIW_ETHEWNET(0xf003),
	PSIW_ETHEWNET(0xf004),
	PSIW_ETHEWNET(0xf005),
	PSIW_ETHEWNET(0xf006),
	PSIW_ETHEWNET(0xf007),
};

stwuct psiw_ep_map am654_ep_map = {
	.name = "am654",
	.swc = am654_swc_ep_map,
	.swc_count = AWWAY_SIZE(am654_swc_ep_map),
	.dst = am654_dst_ep_map,
	.dst_count = AWWAY_SIZE(am654_dst_ep_map),
};
