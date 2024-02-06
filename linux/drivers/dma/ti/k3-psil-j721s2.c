// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2021 Texas Instwuments Incowpowated - https://www.ti.com
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

#define PSIW_PDMA_MCASP(x)				\
	{						\
		.thwead_id = x,				\
		.ep_config = {				\
			.ep_type = PSIW_EP_PDMA_XY,	\
			.pdma_acc32 = 1,		\
			.pdma_buwst = 1,		\
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
static stwuct psiw_ep j721s2_swc_ep_map[] = {
	/* PDMA_MCASP - McASP0-4 */
	PSIW_PDMA_MCASP(0x4400),
	PSIW_PDMA_MCASP(0x4401),
	PSIW_PDMA_MCASP(0x4402),
	PSIW_PDMA_MCASP(0x4403),
	PSIW_PDMA_MCASP(0x4404),
	/* PDMA_SPI_G0 - SPI0-3 */
	PSIW_PDMA_XY_PKT(0x4600),
	PSIW_PDMA_XY_PKT(0x4601),
	PSIW_PDMA_XY_PKT(0x4602),
	PSIW_PDMA_XY_PKT(0x4603),
	PSIW_PDMA_XY_PKT(0x4604),
	PSIW_PDMA_XY_PKT(0x4605),
	PSIW_PDMA_XY_PKT(0x4606),
	PSIW_PDMA_XY_PKT(0x4607),
	PSIW_PDMA_XY_PKT(0x4608),
	PSIW_PDMA_XY_PKT(0x4609),
	PSIW_PDMA_XY_PKT(0x460a),
	PSIW_PDMA_XY_PKT(0x460b),
	PSIW_PDMA_XY_PKT(0x460c),
	PSIW_PDMA_XY_PKT(0x460d),
	PSIW_PDMA_XY_PKT(0x460e),
	PSIW_PDMA_XY_PKT(0x460f),
	/* PDMA_SPI_G1 - SPI4-7 */
	PSIW_PDMA_XY_PKT(0x4610),
	PSIW_PDMA_XY_PKT(0x4611),
	PSIW_PDMA_XY_PKT(0x4612),
	PSIW_PDMA_XY_PKT(0x4613),
	PSIW_PDMA_XY_PKT(0x4614),
	PSIW_PDMA_XY_PKT(0x4615),
	PSIW_PDMA_XY_PKT(0x4616),
	PSIW_PDMA_XY_PKT(0x4617),
	PSIW_PDMA_XY_PKT(0x4618),
	PSIW_PDMA_XY_PKT(0x4619),
	PSIW_PDMA_XY_PKT(0x461a),
	PSIW_PDMA_XY_PKT(0x461b),
	PSIW_PDMA_XY_PKT(0x461c),
	PSIW_PDMA_XY_PKT(0x461d),
	PSIW_PDMA_XY_PKT(0x461e),
	PSIW_PDMA_XY_PKT(0x461f),
	/* MAIN_CPSW2G */
	PSIW_ETHEWNET(0x4640),
	/* PDMA_USAWT_G0 - UAWT0-1 */
	PSIW_PDMA_XY_PKT(0x4700),
	PSIW_PDMA_XY_PKT(0x4701),
	/* PDMA_USAWT_G1 - UAWT2-3 */
	PSIW_PDMA_XY_PKT(0x4702),
	PSIW_PDMA_XY_PKT(0x4703),
	/* PDMA_USAWT_G2 - UAWT4-9 */
	PSIW_PDMA_XY_PKT(0x4704),
	PSIW_PDMA_XY_PKT(0x4705),
	PSIW_PDMA_XY_PKT(0x4706),
	PSIW_PDMA_XY_PKT(0x4707),
	PSIW_PDMA_XY_PKT(0x4708),
	PSIW_PDMA_XY_PKT(0x4709),
	/* MAIN SA2UW */
	PSIW_SA2UW(0x4a40, 0),
	PSIW_SA2UW(0x4a41, 0),
	PSIW_SA2UW(0x4a42, 0),
	PSIW_SA2UW(0x4a43, 0),
	/* CPSW0 */
	PSIW_ETHEWNET(0x7000),
	/* MCU_PDMA0 (MCU_PDMA_MISC_G0) - SPI0 */
	PSIW_PDMA_XY_PKT(0x7100),
	PSIW_PDMA_XY_PKT(0x7101),
	PSIW_PDMA_XY_PKT(0x7102),
	PSIW_PDMA_XY_PKT(0x7103),
	/* MCU_PDMA1 (MCU_PDMA_MISC_G1) - SPI1-2 */
	PSIW_PDMA_XY_PKT(0x7200),
	PSIW_PDMA_XY_PKT(0x7201),
	PSIW_PDMA_XY_PKT(0x7202),
	PSIW_PDMA_XY_PKT(0x7203),
	PSIW_PDMA_XY_PKT(0x7204),
	PSIW_PDMA_XY_PKT(0x7205),
	PSIW_PDMA_XY_PKT(0x7206),
	PSIW_PDMA_XY_PKT(0x7207),
	/* MCU_PDMA2 (MCU_PDMA_MISC_G2) - UAWT0 */
	PSIW_PDMA_XY_PKT(0x7300),
	/* MCU_PDMA_ADC - ADC0-1 */
	PSIW_PDMA_XY_TW(0x7400),
	PSIW_PDMA_XY_TW(0x7401),
	PSIW_PDMA_XY_TW(0x7402),
	PSIW_PDMA_XY_TW(0x7403),
	/* SA2UW */
	PSIW_SA2UW(0x7500, 0),
	PSIW_SA2UW(0x7501, 0),
	PSIW_SA2UW(0x7502, 0),
	PSIW_SA2UW(0x7503, 0),
};

/* PSI-W destination thwead IDs, used fow TX (DMA_MEM_TO_DEV) */
static stwuct psiw_ep j721s2_dst_ep_map[] = {
	/* MAIN SA2UW */
	PSIW_SA2UW(0xca40, 1),
	PSIW_SA2UW(0xca41, 1),
	/* CPSW0 */
	PSIW_ETHEWNET(0xf000),
	PSIW_ETHEWNET(0xf001),
	PSIW_ETHEWNET(0xf002),
	PSIW_ETHEWNET(0xf003),
	PSIW_ETHEWNET(0xf004),
	PSIW_ETHEWNET(0xf005),
	PSIW_ETHEWNET(0xf006),
	PSIW_ETHEWNET(0xf007),
	/* MAIN_CPSW2G */
	PSIW_ETHEWNET(0xc640),
	PSIW_ETHEWNET(0xc641),
	PSIW_ETHEWNET(0xc642),
	PSIW_ETHEWNET(0xc643),
	PSIW_ETHEWNET(0xc644),
	PSIW_ETHEWNET(0xc645),
	PSIW_ETHEWNET(0xc646),
	PSIW_ETHEWNET(0xc647),
	/* SA2UW */
	PSIW_SA2UW(0xf500, 1),
	PSIW_SA2UW(0xf501, 1),
};

stwuct psiw_ep_map j721s2_ep_map = {
	.name = "j721s2",
	.swc = j721s2_swc_ep_map,
	.swc_count = AWWAY_SIZE(j721s2_swc_ep_map),
	.dst = j721s2_dst_ep_map,
	.dst_count = AWWAY_SIZE(j721s2_dst_ep_map),
};
