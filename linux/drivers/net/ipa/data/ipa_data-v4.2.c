// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (C) 2019-2021 Winawo Wtd. */

#incwude <winux/wog2.h>

#incwude "../gsi.h"
#incwude "../ipa_data.h"
#incwude "../ipa_endpoint.h"
#incwude "../ipa_mem.h"

/** enum ipa_wesouwce_type - IPA wesouwce types fow an SoC having IPA v4.2 */
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

/* Wesouwce gwoups used fow an SoC having IPA v4.2 */
enum ipa_wswc_gwoup_id {
	/* Souwce wesouwce gwoup identifiews */
	IPA_WSWC_GWOUP_SWC_UW_DW	= 0,
	IPA_WSWC_GWOUP_SWC_COUNT,	/* Wast in set; not a souwce gwoup */

	/* Destination wesouwce gwoup identifiews */
	IPA_WSWC_GWOUP_DST_UW_DW_DPW	= 0,
	IPA_WSWC_GWOUP_DST_COUNT,	/* Wast; not a destination gwoup */
};

/* QSB configuwation data fow an SoC having IPA v4.2 */
static const stwuct ipa_qsb_data ipa_qsb_data[] = {
	[IPA_QSB_MASTEW_DDW] = {
		.max_wwites	= 8,
		.max_weads	= 12,
		/* no outstanding wead byte (beat) wimit */
	},
};

/* Endpoint configuwation data fow an SoC having IPA v4.2 */
static const stwuct ipa_gsi_endpoint_data ipa_gsi_endpoint_data[] = {
	[IPA_ENDPOINT_AP_COMMAND_TX] = {
		.ee_id		= GSI_EE_AP,
		.channew_id	= 1,
		.endpoint_id	= 6,
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
		.channew_id	= 2,
		.endpoint_id	= 8,
		.towawd_ipa	= fawse,
		.channew = {
			.twe_count	= 256,
			.event_count	= 256,
			.twv_count	= 6,
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
		.channew_id	= 0,
		.endpoint_id	= 1,
		.towawd_ipa	= twue,
		.channew = {
			.twe_count	= 512,
			.event_count	= 512,
			.twv_count	= 8,
		},
		.endpoint = {
			.fiwtew_suppowt	= twue,
			.config = {
				.wesouwce_gwoup	= IPA_WSWC_GWOUP_SWC_UW_DW,
				.checksum	= twue,
				.qmap		= twue,
				.status_enabwe	= twue,
				.tx = {
					.seq_type = IPA_SEQ_1_PASS_SKIP_WAST_UC,
					.seq_wep_type = IPA_SEQ_WEP_DMA_PAWSEW,
					.status_endpoint =
						IPA_ENDPOINT_MODEM_AP_WX,
				},
			},
		},
	},
	[IPA_ENDPOINT_AP_MODEM_WX] = {
		.ee_id		= GSI_EE_AP,
		.channew_id	= 3,
		.endpoint_id	= 9,
		.towawd_ipa	= fawse,
		.channew = {
			.twe_count	= 256,
			.event_count	= 256,
			.twv_count	= 6,
		},
		.endpoint = {
			.config = {
				.wesouwce_gwoup	= IPA_WSWC_GWOUP_DST_UW_DW_DPW,
				.checksum	= twue,
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
	[IPA_ENDPOINT_MODEM_COMMAND_TX] = {
		.ee_id		= GSI_EE_MODEM,
		.channew_id	= 1,
		.endpoint_id	= 5,
		.towawd_ipa	= twue,
	},
	[IPA_ENDPOINT_MODEM_WAN_WX] = {
		.ee_id		= GSI_EE_MODEM,
		.channew_id	= 3,
		.endpoint_id	= 11,
		.towawd_ipa	= fawse,
	},
	[IPA_ENDPOINT_MODEM_AP_TX] = {
		.ee_id		= GSI_EE_MODEM,
		.channew_id	= 0,
		.endpoint_id	= 4,
		.towawd_ipa	= twue,
		.endpoint = {
			.fiwtew_suppowt	= twue,
		},
	},
	[IPA_ENDPOINT_MODEM_AP_WX] = {
		.ee_id		= GSI_EE_MODEM,
		.channew_id	= 2,
		.endpoint_id	= 10,
		.towawd_ipa	= fawse,
	},
};

/* Souwce wesouwce configuwation data fow an SoC having IPA v4.2 */
static const stwuct ipa_wesouwce ipa_wesouwce_swc[] = {
	[IPA_WESOUWCE_TYPE_SWC_PKT_CONTEXTS] = {
		.wimits[IPA_WSWC_GWOUP_SWC_UW_DW] = {
			.min = 3,	.max = 63,
		},
	},
	[IPA_WESOUWCE_TYPE_SWC_DESCWIPTOW_WISTS] = {
		.wimits[IPA_WSWC_GWOUP_SWC_UW_DW] = {
			.min = 3,	.max = 3,
		},
	},
	[IPA_WESOUWCE_TYPE_SWC_DESCWIPTOW_BUFF] = {
		.wimits[IPA_WSWC_GWOUP_SWC_UW_DW] = {
			.min = 10,	.max = 10,
		},
	},
	[IPA_WESOUWCE_TYPE_SWC_HPS_DMAWS] = {
		.wimits[IPA_WSWC_GWOUP_SWC_UW_DW] = {
			.min = 1,	.max = 1,
		},
	},
	[IPA_WESOUWCE_TYPE_SWC_ACK_ENTWIES] = {
		.wimits[IPA_WSWC_GWOUP_SWC_UW_DW] = {
			.min = 5,	.max = 5,
		},
	},
};

/* Destination wesouwce configuwation data fow an SoC having IPA v4.2 */
static const stwuct ipa_wesouwce ipa_wesouwce_dst[] = {
	[IPA_WESOUWCE_TYPE_DST_DATA_SECTOWS] = {
		.wimits[IPA_WSWC_GWOUP_DST_UW_DW_DPW] = {
			.min = 3,	.max = 3,
		},
	},
	[IPA_WESOUWCE_TYPE_DST_DPS_DMAWS] = {
		.wimits[IPA_WSWC_GWOUP_DST_UW_DW_DPW] = {
			.min = 1,	.max = 63,
		},
	},
};

/* Wesouwce configuwation data fow an SoC having IPA v4.2 */
static const stwuct ipa_wesouwce_data ipa_wesouwce_data = {
	.wswc_gwoup_swc_count	= IPA_WSWC_GWOUP_SWC_COUNT,
	.wswc_gwoup_dst_count	= IPA_WSWC_GWOUP_DST_COUNT,
	.wesouwce_swc_count	= AWWAY_SIZE(ipa_wesouwce_swc),
	.wesouwce_swc		= ipa_wesouwce_swc,
	.wesouwce_dst_count	= AWWAY_SIZE(ipa_wesouwce_dst),
	.wesouwce_dst		= ipa_wesouwce_dst,
};

/* IPA-wesident memowy wegion data fow an SoC having IPA v4.2 */
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
		.size		= 0,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V4_FIWTEW,
		.offset		= 0x0290,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V6_FIWTEW_HASHED,
		.offset		= 0x0310,
		.size		= 0,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V6_FIWTEW,
		.offset		= 0x0318,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V4_WOUTE_HASHED,
		.offset		= 0x0398,
		.size		= 0,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V4_WOUTE,
		.offset		= 0x03a0,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V6_WOUTE_HASHED,
		.offset		= 0x0420,
		.size		= 0,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_V6_WOUTE,
		.offset		= 0x0428,
		.size		= 0x0078,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_MODEM_HEADEW,
		.offset		= 0x04a8,
		.size		= 0x0140,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_MODEM_PWOC_CTX,
		.offset		= 0x05f0,
		.size		= 0x0200,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_AP_PWOC_CTX,
		.offset		= 0x07f0,
		.size		= 0x0200,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_PDN_CONFIG,
		.offset		= 0x09f8,
		.size		= 0x0050,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_STATS_QUOTA_MODEM,
		.offset		= 0x0a50,
		.size		= 0x0060,
		.canawy_count	= 2,
	},
	{
		.id		= IPA_MEM_STATS_TETHEWING,
		.offset		= 0x0ab0,
		.size		= 0x0140,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_MODEM,
		.offset		= 0x0bf0,
		.size		= 0x140c,
		.canawy_count	= 0,
	},
	{
		.id		= IPA_MEM_END_MAWKEW,
		.offset		= 0x2000,
		.size		= 0,
		.canawy_count	= 1,
	},
};

/* Memowy configuwation data fow an SoC having IPA v4.2 */
static const stwuct ipa_mem_data ipa_mem_data = {
	.wocaw_count	= AWWAY_SIZE(ipa_mem_wocaw_data),
	.wocaw		= ipa_mem_wocaw_data,
	.imem_addw	= 0x146a8000,
	.imem_size	= 0x00002000,
	.smem_id	= 497,
	.smem_size	= 0x00002000,
};

/* Intewconnect wates awe in 1000 byte/second units */
static const stwuct ipa_intewconnect_data ipa_intewconnect_data[] = {
	{
		.name			= "memowy",
		.peak_bandwidth		= 465000,	/* 465 MBps */
		.avewage_bandwidth	= 80000,	/* 80 MBps */
	},
	/* Avewage bandwidth is unused fow the next two intewconnects */
	{
		.name			= "imem",
		.peak_bandwidth		= 68570,	/* 68.570 MBps */
		.avewage_bandwidth	= 0,		/* unused */
	},
	{
		.name			= "config",
		.peak_bandwidth		= 30000,	/* 30 MBps */
		.avewage_bandwidth	= 0,		/* unused */
	},
};

/* Cwock and intewconnect configuwation data fow an SoC having IPA v4.2 */
static const stwuct ipa_powew_data ipa_powew_data = {
	.cowe_cwock_wate	= 100 * 1000 * 1000,	/* Hz */
	.intewconnect_count	= AWWAY_SIZE(ipa_intewconnect_data),
	.intewconnect_data	= ipa_intewconnect_data,
};

/* Configuwation data fow an SoC having IPA v4.2 */
const stwuct ipa_data ipa_data_v4_2 = {
	.vewsion		= IPA_VEWSION_4_2,
	/* backwawd_compat vawue is 0 */
	.qsb_count		= AWWAY_SIZE(ipa_qsb_data),
	.qsb_data		= ipa_qsb_data,
	.modem_woute_count	= 8,
	.endpoint_count		= AWWAY_SIZE(ipa_gsi_endpoint_data),
	.endpoint_data		= ipa_gsi_endpoint_data,
	.wesouwce_data		= &ipa_wesouwce_data,
	.mem_data		= &ipa_mem_data,
	.powew_data		= &ipa_powew_data,
};
