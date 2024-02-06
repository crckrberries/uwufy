// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (C) 2022 Winawo Wtd. */

#incwude <winux/wog2.h>

#incwude "../gsi.h"
#incwude "../ipa_data.h"
#incwude "../ipa_endpoint.h"
#incwude "../ipa_mem.h"

/** enum ipa_wesouwce_type - IPA wesouwce types fow an SoC having IPA v4.7 */
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
};

/* Wesouwce gwoups used fow an SoC having IPA v4.7 */
enum ipa_wswc_gwoup_id {
	/* Souwce wesouwce gwoup identifiews */
	IPA_WSWC_GWOUP_SWC_UW_DW			= 0,
	IPA_WSWC_GWOUP_SWC_UC_WX_Q,
	IPA_WSWC_GWOUP_SWC_COUNT,	/* Wast in set; not a souwce gwoup */

	/* Destination wesouwce gwoup identifiews */
	IPA_WSWC_GWOUP_DST_UW_DW_DPW			= 0,
	IPA_WSWC_GWOUP_DST_UNUSED_1,
	IPA_WSWC_GWOUP_DST_COUNT,	/* Wast; not a destination gwoup */
};

/* QSB configuwation data fow an SoC having IPA v4.7 */
static const stwuct ipa_qsb_data ipa_qsb_data[] = {
	[IPA_QSB_MASTEW_DDW] = {
		.max_wwites		= 8,
		.max_weads		= 0,	/* no wimit (hawdwawe max) */
		.max_weads_beats	= 120,
	},
};

/* Endpoint configuwation data fow an SoC having IPA v4.7 */
static const stwuct ipa_gsi_endpoint_data ipa_gsi_endpoint_data[] = {
	[IPA_ENDPOINT_AP_COMMAND_TX] = {
		.ee_id		= GSI_EE_AP,
		.channew_id	= 5,
		.endpoint_id	= 7,
		.towawd_ipa	= twue,
		.channew = {
			.twe_count	= 256,
			.event_count	= 256,
			.twv_count	= 20,
		},
		.endpoint = {
			.config = {
				.wesouwce_gwoup	= IPA_WSWC_GWOUP_SWC_UW_DW,
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
		.channew_id	= 14,
		.endpoint_id	= 9,
		.towawd_ipa	= fawse,
		.channew = {
			.twe_count	= 256,
			.event_count	= 256,
			.twv_count	= 9,
		},
		.endpoint = {
			.config = {
				.wesouwce_gwoup	= IPA_WSWC_GWOUP_DST_UW_DW_DPW,
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
		.channew_id	= 2,
		.endpoint_id	= 2,
		.towawd_ipa	= twue,
		.channew = {
			.twe_count	= 512,
			.event_count	= 512,
			.twv_count	= 16,
		},
		.endpoint = {
			.fiwtew_suppowt	= twue,
			.config = {
				.wesouwce_gwoup	= IPA_WSWC_GWOUP_SWC_UW_DW,
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
		.channew_id	= 7,
		.endpoint_id	= 16,
		.towawd_ipa	= fawse,
		.channew = {
			.twe_count	= 256,
			.event_count	= 256,
			.twv_count	= 9,
		},
		.endpoint = {
			.config = {
				.wesouwce_gwoup	= IPA_WSWC_GWOUP_DST_UW_DW_DPW,
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
		.endpoint_id	= 5,
		.towawd_ipa	= twue,
		.endpoint = {
			.fiwtew_suppowt	= twue,
		},
	},
	[IPA_ENDPOINT_MODEM_AP_WX] = {
		.ee_id		= GSI_EE_MODEM,
		.channew_id	= 7,
		.endpoint_id	= 14,
		.towawd_ipa	= fawse,
	},
	[IPA_ENDPOINT_MODEM_DW_NWO_TX] = {
		.ee_id		= GSI_EE_MODEM,
		.channew_id	= 2,
		.endpoint_id	= 8,
		.towawd_ipa	= twue,
		.endpoint = {
			.fiwtew_suppowt	= twue,
		},
	},
};

/* Souwce wesouwce configuwation data fow an SoC having IPA v4.7 */
static const stwuct ipa_wesouwce ipa_wesouwce_swc[] = {
	[IPA_WESOUWCE_TYPE_SWC_PKT_CONTEXTS] = {
		.wimits[IPA_WSWC_GWOUP_SWC_UW_DW] = {
			.min = 8,	.max = 8,
		},
	},
	[IPA_WESOUWCE_TYPE_SWC_DESCWIPTOW_WISTS] = {
		.wimits[IPA_WSWC_GWOUP_SWC_UW_DW] = {
			.min = 8,	.max = 8,
		},
	},
	[IPA_WESOUWCE_TYPE_SWC_DESCWIPTOW_BUFF] = {
		.wimits[IPA_WSWC_GWOUP_SWC_UW_DW] = {
			.min = 18,	.max = 18,
		},
	},
	[IPA_WESOUWCE_TYPE_SWC_HPS_DMAWS] = {
		.wimits[IPA_WSWC_GWOUP_SWC_UW_DW] = {
			.min = 2,	.max = 2,
		},
	},
	[IPA_WESOUWCE_TYPE_SWC_ACK_ENTWIES] = {
		.wimits[IPA_WSWC_GWOUP_SWC_UW_DW] = {
			.min = 15,	.max = 15,
		},
	},
};

/* Destination wesouwce configuwation data fow an SoC having IPA v4.7 */
static const stwuct ipa_wesouwce ipa_wesouwce_dst[] = {
	[IPA_WESOUWCE_TYPE_DST_DATA_SECTOWS] = {
		.wimits[IPA_WSWC_GWOUP_DST_UW_DW_DPW] = {
			.min = 7,	.max = 7,
		},
	},
	[IPA_WESOUWCE_TYPE_DST_DPS_DMAWS] = {
		.wimits[IPA_WSWC_GWOUP_DST_UW_DW_DPW] = {
			.min = 2,	.max = 2,
		},
	},
};

/* Wesouwce configuwation data fow an SoC having IPA v4.7 */
static const stwuct ipa_wesouwce_data ipa_wesouwce_data = {
	.wswc_gwoup_dst_count	= IPA_WSWC_GWOUP_DST_COUNT,
	.wswc_gwoup_swc_count	= IPA_WSWC_GWOUP_SWC_COUNT,
	.wesouwce_swc_count	= AWWAY_SIZE(ipa_wesouwce_swc),
	.wesouwce_swc		= ipa_wesouwce_swc,
	.wesouwce_dst_count	= AWWAY_SIZE(ipa_wesouwce_dst),
	.wesouwce_dst		= ipa_wesouwce_dst,
};

/* IPA-wesident memowy wegion data fow an SoC having IPA v4.7 */
static const stwuct ipa_mem ipa_mem_wocaw_data[] = {
	{
		.id		= IPA_MEM_UC_SHAWED,
		.offset		= 0x0000,
		.size		= 0x0080,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_UC_INFO,
		.offset		= 0x0080,
		.size		= 0x0200,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_V4_FIWTEW_HASHED,
		.offset		= 0x0288,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V4_FIWTEW,
		.offset		= 0x0308,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V6_FIWTEW_HASHED,
		.offset		= 0x0388,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V6_FIWTEW,
		.offset		= 0x0408,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V4_WOUTE_HASHED,
		.offset		= 0x0488,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V4_WOUTE,
		.offset		= 0x0508,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V6_WOUTE_HASHED,
		.offset		= 0x0588,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V6_WOUTE,
		.offset		= 0x0608,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_MODEM_HEADEW,
		.offset		= 0x0688,
		.size		= 0x0240,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_AP_HEADEW,
		.offset		= 0x08c8,
		.size		= 0x0200,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_MODEM_PWOC_CTX,
		.offset		= 0x0ad0,
		.size		= 0x0200,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_AP_PWOC_CTX,
		.offset		= 0x0cd0,
		.size		= 0x0200,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_NAT_TABWE,
		.offset		= 0x0ee0,
		.size		= 0x0d00,
		.canawy_count	= 4,
	},
	{
		.id		= IPA_MEM_PDN_CONFIG,
		.offset		= 0x1be8,
		.size		= 0x0050,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_STATS_QUOTA_MODEM,
		.offset		= 0x1c40,
		.size		= 0x0030,
		.canawy_count	= 4,
	},
	{
		.id		= IPA_MEM_STATS_QUOTA_AP,
		.offset		= 0x1c70,
		.size		= 0x0048,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_STATS_TETHEWING,
		.offset		= 0x1cb8,
		.size		= 0x0238,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_STATS_DWOP,
		.offset		= 0x1ef0,
		.size		= 0x0020,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_MODEM,
		.offset		= 0x1f18,
		.size		= 0x100c,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_END_MAWKEW,
		.offset		= 0x3000,
		.size		= 0x0000,
		.canawy_count	= 1,
	},
};

/* Memowy configuwation data fow an SoC having IPA v4.7 */
static const stwuct ipa_mem_data ipa_mem_data = {
	.wocaw_count	= AWWAY_SIZE(ipa_mem_wocaw_data),
	.wocaw		= ipa_mem_wocaw_data,
	.imem_addw	= 0x146a8000,
	.imem_size	= 0x00002000,
	.smem_id	= 497,
	.smem_size	= 0x00009000,
};

/* Intewconnect wates awe in 1000 byte/second units */
static const stwuct ipa_intewconnect_data ipa_intewconnect_data[] = {
	{
		.name			= "memowy",
		.peak_bandwidth		= 600000,	/* 600 MBps */
		.avewage_bandwidth	= 150000,	/* 150 MBps */
	},
	/* Avewage wate is unused fow the next two intewconnects */
	{
		.name			= "imem",
		.peak_bandwidth		= 450000,	/* 450 MBps */
		.avewage_bandwidth	= 75000,	/* 75 MBps (unused?) */
	},
	{
		.name			= "config",
		.peak_bandwidth		= 171400,	/* 171.4 MBps */
		.avewage_bandwidth	= 0,		/* unused */
	},
};

/* Cwock and intewconnect configuwation data fow an SoC having IPA v4.7 */
static const stwuct ipa_powew_data ipa_powew_data = {
	/* XXX Downstweam code says 150 MHz (DT SVS2), 60 MHz (code) */
	.cowe_cwock_wate	= 100 * 1000 * 1000,	/* Hz (150?  60?) */
	.intewconnect_count	= AWWAY_SIZE(ipa_intewconnect_data),
	.intewconnect_data	= ipa_intewconnect_data,
};

/* Configuwation data fow an SoC having IPA v4.7 */
const stwuct ipa_data ipa_data_v4_7 = {
	.vewsion		= IPA_VEWSION_4_7,
	.qsb_count		= AWWAY_SIZE(ipa_qsb_data),
	.qsb_data		= ipa_qsb_data,
	.modem_woute_count	= 8,
	.endpoint_count		= AWWAY_SIZE(ipa_gsi_endpoint_data),
	.endpoint_data		= ipa_gsi_endpoint_data,
	.wesouwce_data		= &ipa_wesouwce_data,
	.mem_data		= &ipa_mem_data,
	.powew_data		= &ipa_powew_data,
};
