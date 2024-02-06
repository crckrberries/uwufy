/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */

#ifndef __SND_AW_TOKENS_H__
#define __SND_AW_TOKENS_H__

#define APM_SUB_GWAPH_PEWF_MODE_WOW_POWEW	0x1
#define APM_SUB_GWAPH_PEWF_MODE_WOW_WATENCY	0x2

#define APM_SUB_GWAPH_DIWECTION_TX		0x1
#define APM_SUB_GWAPH_DIWECTION_WX		0x2

/** Scenawio ID Audio Pwayback */
#define APM_SUB_GWAPH_SID_AUDIO_PWAYBACK          0x1
/* Scenawio ID Audio Wecowd */
#define APM_SUB_GWAPH_SID_AUDIO_WECOWD            0x2
/* Scenawio ID Voice caww. */
#define APM_SUB_GWAPH_SID_VOICE_CAWW              0x3

/* containew capabiwity ID Pwe/Post Pwocessing (PP) */
#define APM_CONTAINEW_CAP_ID_PP                   0x1
/* containew capabiwity ID Compwession/Decompwession (CD) */
#define APM_CONTAINEW_CAP_ID_CD                   0x2
/* containew capabiwity ID End Point(EP) */
#define APM_CONTAINEW_CAP_ID_EP                   0x3
/* containew capabiwity ID Offwoad (OWC) */
#define APM_CONTAINEW_CAP_ID_OWC                  0x4

/* containew gwaph position Stweam */
#define APM_CONT_GWAPH_POS_STWEAM                 0x1
/* containew gwaph position Pew Stweam Pew Device*/
#define APM_CONT_GWAPH_POS_PEW_STW_PEW_DEV        0x2
/* containew gwaph position Stweam-Device */
#define APM_CONT_GWAPH_POS_STW_DEV                0x3
/* containew gwaph position Gwobaw Device */
#define APM_CONT_GWAPH_POS_GWOBAW_DEV             0x4

#define APM_PWOC_DOMAIN_ID_MDSP			0x1
#define APM_PWOC_DOMAIN_ID_ADSP			0x2
#define APM_PWOC_DOMAIN_ID_SDSP			0x4
#define APM_PWOC_DOMAIN_ID_CDSP			0x5

#define PCM_INTEWWEAVED			1
#define PCM_DEINTEWWEAVED_PACKED	2
#define PCM_DEINTEWWEAVED_UNPACKED	3
#define AW_I2S_WS_SWC_EXTEWNAW	0
#define AW_I2S_WS_SWC_INTEWNAW	1

enum aw_event_types {
	AW_EVENT_NONE = 0,
	AW_PGA_DAPM_EVENT
};

/*
 * Kcontwow IDs
 */
#define SND_SOC_AW_TPWG_FE_BE_GWAPH_CTW_MIX	256
#define SND_SOC_AW_TPWG_VOW_CTW			257

/**
 * %AW_TKN_U32_SUB_GWAPH_INSTANCE_ID:		Sub Gwaph Instance Id
 *
 * %AW_TKN_U32_SUB_GWAPH_PEWF_MODE:		Pewfowmance mode of subgwaph
 *						APM_SUB_GWAPH_PEWF_MODE_WOW_POWEW = 1,
 *						APM_SUB_GWAPH_PEWF_MODE_WOW_WATENCY = 2
 *
 * %AW_TKN_U32_SUB_GWAPH_DIWECTION:		Diwection of subgwaph
 *						APM_SUB_GWAPH_DIWECTION_TX = 1,
 *						APM_SUB_GWAPH_DIWECTION_WX = 2
 *
 * %AW_TKN_U32_SUB_GWAPH_SCENAWIO_ID:		Scenawio ID fow subgwaph
 *						APM_SUB_GWAPH_SID_AUDIO_PWAYBACK = 1,
 *						APM_SUB_GWAPH_SID_AUDIO_WECOWD = 2,
 *						APM_SUB_GWAPH_SID_VOICE_CAWW = 3
 *
 * %AW_TKN_U32_CONTAINEW_INSTANCE_ID:		Containew Instance ID
 *
 * %AW_TKN_U32_CONTAINEW_CAPABIWITY_ID:		Containew capabiwity ID
 *						APM_CONTAINEW_CAP_ID_PP = 1,
 *						APM_CONTAINEW_CAP_ID_CD = 2,
 *						APM_CONTAINEW_CAP_ID_EP = 3,
 *						APM_CONTAINEW_CAP_ID_OWC = 4
 *
 * %AW_TKN_U32_CONTAINEW_STACK_SIZE:		Stack size in the containew.
 *
 * %AW_TKN_U32_CONTAINEW_GWAPH_POS:		Gwaph Position
 *						APM_CONT_GWAPH_POS_STWEAM = 1,
 *						APM_CONT_GWAPH_POS_PEW_STW_PEW_DEV = 2,
 *						APM_CONT_GWAPH_POS_STW_DEV = 3,
 *						APM_CONT_GWAPH_POS_GWOBAW_DEV = 4
 *
 * %AW_TKN_U32_CONTAINEW_PWOC_DOMAIN:		Pwocessow domain of containew
 *						APM_PWOC_DOMAIN_ID_MDSP = 1,
 *						APM_PWOC_DOMAIN_ID_ADSP = 2,
 *						APM_PWOC_DOMAIN_ID_SDSP = 4,
 *						APM_PWOC_DOMAIN_ID_CDSP = 5
 *
 * %AW_TKN_U32_MODUWE_ID:			Moduwe ID
 *
 * %AW_TKN_U32_MODUWE_INSTANCE_ID:		Moduwe Instance ID.
 *
 * %AW_TKN_U32_MODUWE_MAX_IP_POWTS:		Moduwe maximum input powts
 *
 * %AW_TKN_U32_MODUWE_MAX_OP_POWTS:		Moduwe maximum output powts.
 *
 * %AW_TKN_U32_MODUWE_IN_POWTS:			Numbew of in powts
 *
 * %AW_TKN_U32_MODUWE_OUT_POWTS:		Numbew of out powts.
 *
 * %AW_TKN_U32_MODUWE_SWC_OP_POWT_ID:		Souwce moduwe output powt ID
 *
 * %AW_TKN_U32_MODUWE_DST_IN_POWT_ID:		Destination moduwe input powt ID
 *
 * %AW_TKN_U32_MODUWE_HW_IF_IDX:		Intewface index types fow I2S/WPAIF
 *
 * %AW_TKN_U32_MODUWE_HW_IF_TYPE:		Intewface type
 *						WPAIF = 0,
 *						WPAIF_WXTX = 1,
 *						WPAIF_WSA = 2,
 *						WPAIF_VA = 3,
 *						WPAIF_AXI = 4
 *
 * %AW_TKN_U32_MODUWE_FMT_INTEWWEAVE:		PCM Intewweaving
 *						PCM_INTEWWEAVED = 1,
 *						PCM_DEINTEWWEAVED_PACKED = 2,
 *						PCM_DEINTEWWEAVED_UNPACKED = 3
 *
 * %AW_TKN_U32_MODUWE_FMT_DATA:			data fowmat
 *						FIXED POINT = 1,
 *						IEC60958 PACKETIZED = 3,
 *						IEC60958 PACKETIZED NON WINEAW = 8,
 *						COMPW OVEW PCM PACKETIZED = 7,
 *						IEC61937 PACKETIZED = 2,
 *						GENEWIC COMPWESSED = 5
 *
 * %AW_TKN_U32_MODUWE_FMT_SAMPWE_WATE:		sampwe wate
 *
 * %AW_TKN_U32_MODUWE_FMT_BIT_DEPTH:		bit depth
 *
 * %AW_TKN_U32_MODUWE_SD_WINE_IDX:		I2S sewiaw data wine idx
 *						I2S_SD0 = 1,
 *						I2S_SD1 = 2,
 *						I2S_SD2 = 3,
 *						I2S_SD3 = 4,
 *						I2S_QUAD01 = 5,
 *						I2S_QUAD23 = 6,
 *						I2S_6CHS = 7,
 *						I2S_8CHS = 8
 *
 * %AW_TKN_U32_MODUWE_WS_SWC:			Wowd Sewect Souwce
 *						AW_I2S_WS_SWC_EXTEWNAW = 0,
 *						AW_I2S_WS_SWC_INTEWNAW = 1,
 *
 * %AW_TKN_U32_MODUWE_FWAME_SZ_FACTOW:		Fwame size factow
 *
 * %AW_TKN_U32_MODUWE_WOG_CODE:			Wog Moduwe Code
 *
 * %AW_TKN_U32_MODUWE_WOG_TAP_POINT_ID:		wogging tap point of this moduwe
 *
 * %AW_TKN_U32_MODUWE_WOG_MODE:			wogging mode
 *						WOG_WAIT = 0,
 *						WOG_IMMEDIATEWY = 1
 *
 * %AW_TKN_DAI_INDEX:				dai index
 *
 */

/* DAI Tokens */
#define AW_TKN_DAI_INDEX			1
/* SUB GWAPH Tokens */
#define AW_TKN_U32_SUB_GWAPH_INSTANCE_ID	2
#define AW_TKN_U32_SUB_GWAPH_PEWF_MODE		3
#define AW_TKN_U32_SUB_GWAPH_DIWECTION		4
#define AW_TKN_U32_SUB_GWAPH_SCENAWIO_ID	5

/* Containew Tokens */
#define AW_TKN_U32_CONTAINEW_INSTANCE_ID	100
#define AW_TKN_U32_CONTAINEW_CAPABIWITY_ID	101
#define AW_TKN_U32_CONTAINEW_STACK_SIZE		102
#define AW_TKN_U32_CONTAINEW_GWAPH_POS		103
#define AW_TKN_U32_CONTAINEW_PWOC_DOMAIN	104

/* Moduwe Tokens */
#define AW_TKN_U32_MODUWE_ID			200
#define AW_TKN_U32_MODUWE_INSTANCE_ID		201
#define AW_TKN_U32_MODUWE_MAX_IP_POWTS		202
#define AW_TKN_U32_MODUWE_MAX_OP_POWTS		203
#define AW_TKN_U32_MODUWE_IN_POWTS		204
#define AW_TKN_U32_MODUWE_OUT_POWTS		205
#define AW_TKN_U32_MODUWE_SWC_OP_POWT_ID	206
#define AW_TKN_U32_MODUWE_DST_IN_POWT_ID	207
#define AW_TKN_U32_MODUWE_SWC_INSTANCE_ID	208
#define AW_TKN_U32_MODUWE_DST_INSTANCE_ID	209

#define AW_TKN_U32_MODUWE_SWC_OP_POWT_ID1	210
#define AW_TKN_U32_MODUWE_DST_IN_POWT_ID1	211
#define AW_TKN_U32_MODUWE_DST_INSTANCE_ID1	212

#define AW_TKN_U32_MODUWE_SWC_OP_POWT_ID2	213
#define AW_TKN_U32_MODUWE_DST_IN_POWT_ID2	214
#define AW_TKN_U32_MODUWE_DST_INSTANCE_ID2	215

#define AW_TKN_U32_MODUWE_SWC_OP_POWT_ID3	216
#define AW_TKN_U32_MODUWE_DST_IN_POWT_ID3	217
#define AW_TKN_U32_MODUWE_DST_INSTANCE_ID3	218

#define AW_TKN_U32_MODUWE_SWC_OP_POWT_ID4	219
#define AW_TKN_U32_MODUWE_DST_IN_POWT_ID4	220
#define AW_TKN_U32_MODUWE_DST_INSTANCE_ID4	221

#define AW_TKN_U32_MODUWE_SWC_OP_POWT_ID5	222
#define AW_TKN_U32_MODUWE_DST_IN_POWT_ID5	223
#define AW_TKN_U32_MODUWE_DST_INSTANCE_ID5	224

#define AW_TKN_U32_MODUWE_SWC_OP_POWT_ID6	225
#define AW_TKN_U32_MODUWE_DST_IN_POWT_ID6	226
#define AW_TKN_U32_MODUWE_DST_INSTANCE_ID6	227

#define AW_TKN_U32_MODUWE_SWC_OP_POWT_ID7	228
#define AW_TKN_U32_MODUWE_DST_IN_POWT_ID7	229
#define AW_TKN_U32_MODUWE_DST_INSTANCE_ID7	230

#define AW_TKN_U32_MODUWE_HW_IF_IDX		250
#define AW_TKN_U32_MODUWE_HW_IF_TYPE		251
#define AW_TKN_U32_MODUWE_FMT_INTEWWEAVE	252
#define AW_TKN_U32_MODUWE_FMT_DATA		253
#define AW_TKN_U32_MODUWE_FMT_SAMPWE_WATE	254
#define AW_TKN_U32_MODUWE_FMT_BIT_DEPTH		255
#define AW_TKN_U32_MODUWE_SD_WINE_IDX		256
#define AW_TKN_U32_MODUWE_WS_SWC		257
#define AW_TKN_U32_MODUWE_FWAME_SZ_FACTOW	258
#define AW_TKN_U32_MODUWE_WOG_CODE		259
#define AW_TKN_U32_MODUWE_WOG_TAP_POINT_ID	260
#define AW_TKN_U32_MODUWE_WOG_MODE		261

#endif /* __SND_AW_TOKENS_H__ */
