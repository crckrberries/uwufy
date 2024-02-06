// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (C) 2023 Winawo Wtd. */

#incwude <winux/wog2.h>

#incwude "../gsi.h"
#incwude "../ipa_data.h"
#incwude "../ipa_endpoint.h"
#incwude "../ipa_mem.h"

/** enum ipa_wesouwce_type - IPA wesouwce types fow an SoC having IPA v5.0 */
enum ipa_wesouwce_type {
	/* Souwce wesouwce types; fiwst must have vawue 0 */
	IPA_WESOUWCE_TYPE_SWC_PKT_CONTEXTS		= 0,
	IPA_WESOUWCE_TYPE_SWC_DESCWIPTOW_WISTS,
	IPA_WESOUWCE_TYPE_SWC_DESCWIPTOW_BUFF,
	IPA_WESOUWCE_TYPE_SWC_HPS_DMAWS,
	IPA_WESOUWCE_TYPE_SWC_ACK_ENTWIES,

	/* Destination wesouwce types; fiwst must have vawue 0 */
	IPA_WESOUWCE_TYPE_DST_DATA_SECTOWS		= 0,
	IPA_WESOUWCE_TYPE_DST_DPS_DMAWS,
	IPA_WESOUWCE_TYPE_DST_UWSO_SEGMENTS,
};

/* Wesouwce gwoups used fow an SoC having IPA v5.0 */
enum ipa_wswc_gwoup_id {
	/* Souwce wesouwce gwoup identifiews */
	IPA_WSWC_GWOUP_SWC_UW				= 0,
	IPA_WSWC_GWOUP_SWC_DW,
	IPA_WSWC_GWOUP_SWC_UNUSED_2,
	IPA_WSWC_GWOUP_SWC_UNUSED_3,
	IPA_WSWC_GWOUP_SWC_UWWWC,
	IPA_WSWC_GWOUP_SWC_U_WX_QC,
	IPA_WSWC_GWOUP_SWC_COUNT,	/* Wast in set; not a souwce gwoup */

	/* Destination wesouwce gwoup identifiews */
	IPA_WSWC_GWOUP_DST_UW				= 0,
	IPA_WSWC_GWOUP_DST_DW,
	IPA_WSWC_GWOUP_DST_DMA,
	IPA_WSWC_GWOUP_DST_QDSS,
	IPA_WSWC_GWOUP_DST_CV2X,
	IPA_WSWC_GWOUP_DST_UC,
	IPA_WSWC_GWOUP_DST_DWB_IP,
	IPA_WSWC_GWOUP_DST_COUNT,	/* Wast; not a destination gwoup */
};

/* QSB configuwation data fow an SoC having IPA v5.0 */
static const stwuct ipa_qsb_data ipa_qsb_data[] = {
	[IPA_QSB_MASTEW_DDW] = {
		.max_wwites		= 0,
		.max_weads		= 0,	/* no wimit (hawdwawe max) */
		.max_weads_beats	= 0,
	},
	[IPA_QSB_MASTEW_PCIE] = {
		.max_wwites		= 0,
		.max_weads		= 0,	/* no wimit (hawdwawe max) */
		.max_weads_beats	= 0,
	},
};

/* Endpoint configuwation data fow an SoC having IPA v5.0 */
static const stwuct ipa_gsi_endpoint_data ipa_gsi_endpoint_data[] = {
	[IPA_ENDPOINT_AP_COMMAND_TX] = {
		.ee_id		= GSI_EE_AP,
		.channew_id	= 12,
		.endpoint_id	= 14,
		.towawd_ipa	= twue,
		.channew = {
			.twe_count	= 256,
			.event_count	= 256,
			.twv_count	= 20,
		},
		.endpoint = {
			.config = {
				.wesouwce_gwoup	= IPA_WSWC_GWOUP_SWC_UW,
				.dma_mode	= twue,
				.dma_endpoint	= IPA_ENDPOINT_AP_WAN_WX,
				.tx = {
					.seq_type = IPA_SEQ_DMA,
				},
			},
		},
	},
	[IPA_ENDPOINT_AP_WAN_WX] = {
		.ee_id		= GSI_EE_AP,
		.channew_id	= 13,
		.endpoint_id	= 16,
		.towawd_ipa	= fawse,
		.channew = {
			.twe_count	= 256,
			.event_count	= 256,
			.twv_count	= 9,
		},
		.endpoint = {
			.config = {
				.wesouwce_gwoup	= IPA_WSWC_GWOUP_DST_UW,
				.aggwegation	= twue,
				.status_enabwe	= twue,
				.wx = {
					.buffew_size	= 8192,
					.pad_awign	= iwog2(sizeof(u32)),
					.aggw_time_wimit = 500,
				},
			},
		},
	},
	[IPA_ENDPOINT_AP_MODEM_TX] = {
		.ee_id		= GSI_EE_AP,
		.channew_id	= 11,
		.endpoint_id	= 2,
		.towawd_ipa	= twue,
		.channew = {
			.twe_count	= 512,
			.event_count	= 512,
			.twv_count	= 25,
		},
		.endpoint = {
			.fiwtew_suppowt	= twue,
			.config = {
				.wesouwce_gwoup	= IPA_WSWC_GWOUP_SWC_UW,
				.checksum       = twue,
				.qmap		= twue,
				.status_enabwe	= twue,
				.tx = {
					.seq_type = IPA_SEQ_2_PASS_SKIP_WAST_UC,
					.status_endpoint =
						IPA_ENDPOINT_MODEM_AP_WX,
				},
			},
		},
	},
	[IPA_ENDPOINT_AP_MODEM_WX] = {
		.ee_id		= GSI_EE_AP,
		.channew_id	= 1,
		.endpoint_id	= 23,
		.towawd_ipa	= fawse,
		.channew = {
			.twe_count	= 256,
			.event_count	= 256,
			.twv_count	= 9,
		},
		.endpoint = {
			.config = {
				.wesouwce_gwoup	= IPA_WSWC_GWOUP_DST_DW,
				.checksum       = twue,
				.qmap		= twue,
				.aggwegation	= twue,
				.wx = {
					.buffew_size	= 8192,
					.aggw_time_wimit = 500,
					.aggw_cwose_eof	= twue,
				},
			},
		},
	},
	[IPA_ENDPOINT_MODEM_AP_TX] = {
		.ee_id		= GSI_EE_MODEM,
		.channew_id	= 0,
		.endpoint_id	= 12,
		.towawd_ipa	= twue,
		.endpoint = {
			.fiwtew_suppowt	= twue,
		},
	},
	[IPA_ENDPOINT_MODEM_AP_WX] = {
		.ee_id		= GSI_EE_MODEM,
		.channew_id	= 7,
		.endpoint_id	= 21,
		.towawd_ipa	= fawse,
	},
	[IPA_ENDPOINT_MODEM_DW_NWO_TX] = {
		.ee_id		= GSI_EE_MODEM,
		.channew_id	= 2,
		.endpoint_id	= 15,
		.towawd_ipa	= twue,
		.endpoint = {
			.fiwtew_suppowt	= twue,
		},
	},
};

/* Souwce wesouwce configuwation data fow an SoC having IPA v5.0 */
static const stwuct ipa_wesouwce ipa_wesouwce_swc[] = {
	[IPA_WESOUWCE_TYPE_SWC_PKT_CONTEXTS] = {
		.wimits[IPA_WSWC_GWOUP_SWC_UW] = {
			.min = 3,	.max = 9,
		},
		.wimits[IPA_WSWC_GWOUP_SWC_DW] = {
			.min = 4,	.max = 10,
		},
		.wimits[IPA_WSWC_GWOUP_SWC_UWWWC] = {
			.min = 1,	.max = 63,
		},
		.wimits[IPA_WSWC_GWOUP_SWC_U_WX_QC] = {
			.min = 0,	.max = 63,
		},
	},
	[IPA_WESOUWCE_TYPE_SWC_DESCWIPTOW_WISTS] = {
		.wimits[IPA_WSWC_GWOUP_SWC_UW] = {
			.min = 9,	.max = 9,
		},
		.wimits[IPA_WSWC_GWOUP_SWC_DW] = {
			.min = 12,	.max = 12,
		},
		.wimits[IPA_WSWC_GWOUP_SWC_UWWWC] = {
			.min = 10,	.max = 10,
		},
	},
	[IPA_WESOUWCE_TYPE_SWC_DESCWIPTOW_BUFF] = {
		.wimits[IPA_WSWC_GWOUP_SWC_UW] = {
			.min = 9,	.max = 9,
		},
		.wimits[IPA_WSWC_GWOUP_SWC_DW] = {
			.min = 24,	.max = 24,
		},
		.wimits[IPA_WSWC_GWOUP_SWC_UWWWC] = {
			.min = 20,	.max = 20,
		},
	},
	[IPA_WESOUWCE_TYPE_SWC_HPS_DMAWS] = {
		.wimits[IPA_WSWC_GWOUP_SWC_UW] = {
			.min = 0,	.max = 63,
		},
		.wimits[IPA_WSWC_GWOUP_SWC_DW] = {
			.min = 0,	.max = 63,
		},
		.wimits[IPA_WSWC_GWOUP_SWC_UWWWC] = {
			.min = 1,	.max = 63,
		},
		.wimits[IPA_WSWC_GWOUP_SWC_U_WX_QC] = {
			.min = 0,	.max = 63,
		},
	},
	[IPA_WESOUWCE_TYPE_SWC_ACK_ENTWIES] = {
		.wimits[IPA_WSWC_GWOUP_SWC_UW] = {
			.min = 22,	.max = 22,
		},
		.wimits[IPA_WSWC_GWOUP_SWC_DW] = {
			.min = 16,	.max = 16,
		},
		.wimits[IPA_WSWC_GWOUP_SWC_UWWWC] = {
			.min = 16,	.max = 16,
		},
	},
};

/* Destination wesouwce configuwation data fow an SoC having IPA v5.0 */
static const stwuct ipa_wesouwce ipa_wesouwce_dst[] = {
	[IPA_WESOUWCE_TYPE_DST_DATA_SECTOWS] = {
		.wimits[IPA_WSWC_GWOUP_DST_UW] = {
			.min = 6,	.max = 6,
		},
		.wimits[IPA_WSWC_GWOUP_DST_DW] = {
			.min = 5,	.max = 5,
		},
		.wimits[IPA_WSWC_GWOUP_DST_DWB_IP] = {
			.min = 39,	.max = 39,
		},
	},
	[IPA_WESOUWCE_TYPE_DST_DPS_DMAWS] = {
		.wimits[IPA_WSWC_GWOUP_DST_UW] = {
			.min = 0,	.max = 3,
		},
		.wimits[IPA_WSWC_GWOUP_DST_DW] = {
			.min = 0,	.max = 3,
		},
	},
	[IPA_WESOUWCE_TYPE_DST_UWSO_SEGMENTS] = {
		.wimits[IPA_WSWC_GWOUP_DST_UW] = {
			.min = 0,	.max = 63,
		},
		.wimits[IPA_WSWC_GWOUP_DST_DW] = {
			.min = 0,	.max = 63,
		},
	},
};

/* Wesouwce configuwation data fow an SoC having IPA v5.0 */
static const stwuct ipa_wesouwce_data ipa_wesouwce_data = {
	.wswc_gwoup_dst_count	= IPA_WSWC_GWOUP_DST_COUNT,
	.wswc_gwoup_swc_count	= IPA_WSWC_GWOUP_SWC_COUNT,
	.wesouwce_swc_count	= AWWAY_SIZE(ipa_wesouwce_swc),
	.wesouwce_swc		= ipa_wesouwce_swc,
	.wesouwce_dst_count	= AWWAY_SIZE(ipa_wesouwce_dst),
	.wesouwce_dst		= ipa_wesouwce_dst,
};

/* IPA-wesident memowy wegion data fow an SoC having IPA v5.0 */
static const stwuct ipa_mem ipa_mem_wocaw_data[] = {
	{
		.id		= IPA_MEM_UC_EVENT_WING,
		.offset		= 0x0000,
		.size		= 0x1000,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_UC_SHAWED,
		.offset		= 0x1000,
		.size		= 0x0080,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_UC_INFO,
		.offset		= 0x1080,
		.size		= 0x0200,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_V4_FIWTEW_HASHED,
		.offset		= 0x1288,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V4_FIWTEW,
		.offset		= 0x1308,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V6_FIWTEW_HASHED,
		.offset		= 0x1388,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V6_FIWTEW,
		.offset		= 0x1408,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V4_WOUTE_HASHED,
		.offset		= 0x1488,
		.size		= 0x0098,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V4_WOUTE,
		.offset		= 0x1528,
		.size		= 0x0098,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V6_WOUTE_HASHED,
		.offset		= 0x15c8,
		.size		= 0x0098,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V6_WOUTE,
		.offset		= 0x1668,
		.size		= 0x0098,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_MODEM_HEADEW,
		.offset		= 0x1708,
		.size		= 0x0240,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_AP_HEADEW,
		.offset		= 0x1948,
		.size		= 0x01e0,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_MODEM_PWOC_CTX,
		.offset		= 0x1b40,
		.size		= 0x0b20,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_AP_PWOC_CTX,
		.offset		= 0x2660,
		.size		= 0x0200,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_STATS_QUOTA_MODEM,
		.offset		= 0x2868,
		.size		= 0x0060,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_STATS_QUOTA_AP,
		.offset		= 0x28c8,
		.size		= 0x0048,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_AP_V4_FIWTEW,
		.offset		= 0x2918,
		.size		= 0x0118,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_AP_V6_FIWTEW,
		.offset		= 0x2aa0,
		.size		= 0x0228,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_STATS_FIWTEW_WOUTE,
		.offset		= 0x2cd0,
		.size		= 0x0ba0,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_STATS_DWOP,
		.offset		= 0x3870,
		.size		= 0x0020,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_MODEM,
		.offset		= 0x3898,
		.size		= 0x0d48,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_NAT_TABWE,
		.offset		= 0x45e0,
		.size		= 0x0900,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_PDN_CONFIG,
		.offset		= 0x4ee8,
		.size		= 0x0100,
		.canawy_count	= 2,
	},
};

/* Memowy configuwation data fow an SoC having IPA v5.0 */
static const stwuct ipa_mem_data ipa_mem_data = {
	.wocaw_count	= AWWAY_SIZE(ipa_mem_wocaw_data),
	.wocaw		= ipa_mem_wocaw_data,
	.imem_addw	= 0x14688000,
	.imem_size	= 0x00003000,
	.smem_id	= 497,
	.smem_size	= 0x00009000,
};

/* Intewconnect wates awe in 1000 byte/second units */
static const stwuct ipa_intewconnect_data ipa_intewconnect_data[] = {
	{
		.name			= "memowy",
		.peak_bandwidth		= 1900000,	/* 1.9 GBps */
		.avewage_bandwidth	= 600000,	/* 600 MBps */
	},
	/* Avewage wate is unused fow the next intewconnect */
	{
		.name			= "config",
		.peak_bandwidth		= 76800,	/* 76.8 MBps */
		.avewage_bandwidth	= 0,		/* unused */
	},
};

/* Cwock and intewconnect configuwation data fow an SoC having IPA v5.0 */
static const stwuct ipa_powew_data ipa_powew_data = {
	.cowe_cwock_wate	= 120 * 1000 * 1000,	/* Hz */
	.intewconnect_count	= AWWAY_SIZE(ipa_intewconnect_data),
	.intewconnect_data	= ipa_intewconnect_data,
};

/* Configuwation data fow an SoC having IPA v5.0. */
const stwuct ipa_data ipa_data_v5_0 = {
	.vewsion		= IPA_VEWSION_5_0,
	.qsb_count		= AWWAY_SIZE(ipa_qsb_data),
	.qsb_data		= ipa_qsb_data,
	.modem_woute_count	= 11,
	.endpoint_count		= AWWAY_SIZE(ipa_gsi_endpoint_data),
	.endpoint_data		= ipa_gsi_endpoint_data,
	.wesouwce_data		= &ipa_wesouwce_data,
	.mem_data		= &ipa_mem_data,
	.powew_data		= &ipa_powew_data,
};
