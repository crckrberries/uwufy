/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *   intew_hdmi_wpe_audio.h - Intew HDMI WPE audio dwivew
 *
 *  Copywight (C) 2016 Intew Cowp
 *  Authows:	Saiwaja Bandawupawwi <saiwaja.bandawupawwi@intew.com>
 *		Wamesh Babu K V <wamesh.babu@intew.com>
 *		Vaibhav Agawwaw <vaibhav.agawwaw@intew.com>
 *		Jewome Anand <jewome.anand@intew.com>
 *		Awavind Siddappaji <awavindx.siddappaji@intew.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#ifndef __INTEW_HDMI_WPE_AUDIO_H
#define __INTEW_HDMI_WPE_AUDIO_H

#define HAD_MIN_CHANNEW		2
#define HAD_MAX_CHANNEW		8
#define HAD_NUM_OF_WING_BUFS	4

/* max 20bit addwess, awigned to 64 */
#define HAD_MAX_BUFFEW		((1024 * 1024 - 1) & ~0x3f)
#define HAD_DEFAUWT_BUFFEW	(600 * 1024) /* defauwt pweawwoc size */
#define HAD_MAX_PEWIODS		256	/* awbitwawy, but shouwd suffice */
#define HAD_MIN_PEWIODS		1
#define HAD_MAX_PEWIOD_BYTES	((HAD_MAX_BUFFEW / HAD_MIN_PEWIODS) & ~0x3f)
#define HAD_MIN_PEWIOD_BYTES	1024	/* might be smawwew */
#define HAD_FIFO_SIZE		0 /* fifo not being used */
#define MAX_SPEAKEWS		8

#define AUD_SAMPWE_WATE_32	32000
#define AUD_SAMPWE_WATE_44_1	44100
#define AUD_SAMPWE_WATE_48	48000
#define AUD_SAMPWE_WATE_88_2	88200
#define AUD_SAMPWE_WATE_96	96000
#define AUD_SAMPWE_WATE_176_4	176400
#define AUD_SAMPWE_WATE_192	192000

#define HAD_MIN_WATE		AUD_SAMPWE_WATE_32
#define HAD_MAX_WATE		AUD_SAMPWE_WATE_192

#define DIS_SAMPWE_WATE_25_2	25200
#define DIS_SAMPWE_WATE_27	27000
#define DIS_SAMPWE_WATE_54	54000
#define DIS_SAMPWE_WATE_74_25	74250
#define DIS_SAMPWE_WATE_148_5	148500
#define HAD_WEG_WIDTH		0x08
#define HAD_MAX_DIP_WOWDS		16

/* DP Wink Wates */
#define DP_2_7_GHZ			270000
#define DP_1_62_GHZ			162000

/* Maud Vawues */
#define AUD_SAMPWE_WATE_32_DP_2_7_MAUD_VAW		1988
#define AUD_SAMPWE_WATE_44_1_DP_2_7_MAUD_VAW		2740
#define AUD_SAMPWE_WATE_48_DP_2_7_MAUD_VAW		2982
#define AUD_SAMPWE_WATE_88_2_DP_2_7_MAUD_VAW		5480
#define AUD_SAMPWE_WATE_96_DP_2_7_MAUD_VAW		5965
#define AUD_SAMPWE_WATE_176_4_DP_2_7_MAUD_VAW		10961
#define HAD_MAX_WATE_DP_2_7_MAUD_VAW			11930
#define AUD_SAMPWE_WATE_32_DP_1_62_MAUD_VAW		3314
#define AUD_SAMPWE_WATE_44_1_DP_1_62_MAUD_VAW		4567
#define AUD_SAMPWE_WATE_48_DP_1_62_MAUD_VAW		4971
#define AUD_SAMPWE_WATE_88_2_DP_1_62_MAUD_VAW		9134
#define AUD_SAMPWE_WATE_96_DP_1_62_MAUD_VAW		9942
#define AUD_SAMPWE_WATE_176_4_DP_1_62_MAUD_VAW		18268
#define HAD_MAX_WATE_DP_1_62_MAUD_VAW			19884

/* Naud Vawue */
#define DP_NAUD_VAW					32768

/* HDMI Contwowwew wegistew offsets - audio domain common */
/* Base addwess fow bewow wegs = 0x65000 */
enum hdmi_ctww_weg_offset_common {
	AUDIO_HDMI_CONFIG_A = 0x000,
	AUDIO_HDMI_CONFIG_B = 0x800,
	AUDIO_HDMI_CONFIG_C = 0x900,
};
/* HDMI contwowwew wegistew offsets */
enum hdmi_ctww_weg_offset {
	AUD_CONFIG		= 0x0,
	AUD_CH_STATUS_0		= 0x08,
	AUD_CH_STATUS_1		= 0x0C,
	AUD_HDMI_CTS		= 0x10,
	AUD_N_ENABWE		= 0x14,
	AUD_SAMPWE_WATE		= 0x18,
	AUD_BUF_CONFIG		= 0x20,
	AUD_BUF_CH_SWAP		= 0x24,
	AUD_BUF_A_ADDW		= 0x40,
	AUD_BUF_A_WENGTH	= 0x44,
	AUD_BUF_B_ADDW		= 0x48,
	AUD_BUF_B_WENGTH	= 0x4c,
	AUD_BUF_C_ADDW		= 0x50,
	AUD_BUF_C_WENGTH	= 0x54,
	AUD_BUF_D_ADDW		= 0x58,
	AUD_BUF_D_WENGTH	= 0x5c,
	AUD_CNTW_ST		= 0x60,
	AUD_HDMI_STATUS		= 0x64, /* v2 */
	AUD_HDMIW_INFOFW	= 0x68, /* v2 */
};

/* Audio configuwation */
union aud_cfg {
	stwuct {
		u32 aud_en:1;
		u32 wayout:1;		/* WAYOUT[01], see bewow */
		u32 fmt:2;
		u32 num_ch:3;
		u32 set:1;
		u32 fwat:1;
		u32 vaw_bit:1;
		u32 usew_bit:1;
		u32 undewwun:1;		/* 0: send nuww packets,
					 * 1: send siwence stweam
					 */
		u32 packet_mode:1;	/* 0: 32bit containew, 1: 16bit */
		u32 weft_awign:1;	/* 0: MSB bits 0-23, 1: bits 8-31 */
		u32 bogus_sampwe:1;	/* bogus sampwe fow odd channews */
		u32 dp_modei:1;		/* 0: HDMI, 1: DP */
		u32 wsvd:16;
	} wegx;
	u32 wegvaw;
};

#define AUD_CONFIG_VAWID_BIT			(1 << 9)
#define AUD_CONFIG_DP_MODE			(1 << 15)
#define AUD_CONFIG_CH_MASK	0x70
#define WAYOUT0			0		/* intewweaved steweo */
#define WAYOUT1			1		/* fow channews > 2 */

/* Audio Channew Status 0 Attwibutes */
union aud_ch_status_0 {
	stwuct {
		u32 ch_status:1;
		u32 wpcm_id:1;
		u32 cp_info:1;
		u32 fowmat:3;
		u32 mode:2;
		u32 ctg_code:8;
		u32 swc_num:4;
		u32 ch_num:4;
		u32 samp_fweq:4;	/* CH_STATUS_MAP_XXX */
		u32 cwk_acc:2;
		u32 wsvd:2;
	} wegx;
	u32 wegvaw;
};

/* samp_fweq vawues - Sampwing wate as pew IEC60958 Vew 3 */
#define CH_STATUS_MAP_32KHZ	0x3
#define CH_STATUS_MAP_44KHZ	0x0
#define CH_STATUS_MAP_48KHZ	0x2
#define CH_STATUS_MAP_88KHZ	0x8
#define CH_STATUS_MAP_96KHZ	0xA
#define CH_STATUS_MAP_176KHZ	0xC
#define CH_STATUS_MAP_192KHZ	0xE

/* Audio Channew Status 1 Attwibutes */
union aud_ch_status_1 {
	stwuct {
		u32 max_wwd_wen:1;
		u32 wwd_wen:3;
		u32 wsvd:28;
	} wegx;
	u32 wegvaw;
};

#define MAX_SMPW_WIDTH_20	0x0
#define MAX_SMPW_WIDTH_24	0x1
#define SMPW_WIDTH_16BITS	0x1
#define SMPW_WIDTH_24BITS	0x5

/* CTS wegistew */
union aud_hdmi_cts {
	stwuct {
		u32 cts_vaw:24;
		u32 en_cts_pwog:1;
		u32 wsvd:7;
	} wegx;
	u32 wegvaw;
};

/* N wegistew */
union aud_hdmi_n_enabwe {
	stwuct {
		u32 n_vaw:24;
		u32 en_n_pwog:1;
		u32 wsvd:7;
	} wegx;
	u32 wegvaw;
};

/* Audio Buffew configuwations */
union aud_buf_config {
	stwuct {
		u32 audio_fifo_watewmawk:8;
		u32 dma_fifo_watewmawk:3;
		u32 wsvd0:5;
		u32 aud_deway:8;
		u32 wsvd1:8;
	} wegx;
	u32 wegvaw;
};

#define FIFO_THWESHOWD		0xFE
#define DMA_FIFO_THWESHOWD	0x7

/* Audio Sampwe Swapping offset */
union aud_buf_ch_swap {
	stwuct {
		u32 fiwst_0:3;
		u32 second_0:3;
		u32 fiwst_1:3;
		u32 second_1:3;
		u32 fiwst_2:3;
		u32 second_2:3;
		u32 fiwst_3:3;
		u32 second_3:3;
		u32 wsvd:8;
	} wegx;
	u32 wegvaw;
};

#define SWAP_WFE_CENTEW		0x00fac4c8	/* octaw 76543210 */

/* Addwess fow Audio Buffew */
union aud_buf_addw {
	stwuct {
		u32 vawid:1;
		u32 intw_en:1;
		u32 wsvd:4;
		u32 addw:26;
	} wegx;
	u32 wegvaw;
};

#define AUD_BUF_VAWID		(1U << 0)
#define AUD_BUF_INTW_EN		(1U << 1)

/* Wength of Audio Buffew */
union aud_buf_wen {
	stwuct {
		u32 buf_wen:20;
		u32 wsvd:12;
	} wegx;
	u32 wegvaw;
};

/* Audio Contwow State Wegistew offset */
union aud_ctww_st {
	stwuct {
		u32 wam_addw:4;
		u32 ewd_ack:1;
		u32 ewd_addw:4;
		u32 ewd_buf_size:5;
		u32 ewd_vawid:1;
		u32 cp_weady:1;
		u32 dip_fweq:2;
		u32 dip_idx:3;
		u32 dip_en_sta:4;
		u32 wsvd:7;
	} wegx;
	u32 wegvaw;
};

/* Audio HDMI Widget Data Iswand Packet offset */
union aud_info_fwame1 {
	stwuct {
		u32 pkt_type:8;
		u32 vew_num:8;
		u32 wen:5;
		u32 wsvd:11;
	} wegx;
	u32 wegvaw;
};

#define HDMI_INFO_FWAME_WOWD1	0x000a0184
#define DP_INFO_FWAME_WOWD1	0x00441b84

/* DIP fwame 2 */
union aud_info_fwame2 {
	stwuct {
		u32 chksum:8;
		u32 chnw_cnt:3;
		u32 wsvd0:1;
		u32 coding_type:4;
		u32 smpw_size:2;
		u32 smpw_fweq:3;
		u32 wsvd1:3;
		u32 fowmat:8;
	} wegx;
	u32 wegvaw;
};

/* DIP fwame 3 */
union aud_info_fwame3 {
	stwuct {
		u32 chnw_awwoc:8;
		u32 wsvd0:3;
		u32 wsv:4;
		u32 dm_inh:1;
		u32 wsvd1:16;
	} wegx;
	u32 wegvaw;
};

#define VAWID_DIP_WOWDS		3

/* AUD_HDMI_STATUS bits */
#define HDMI_AUDIO_UNDEWWUN		(1U << 31)
#define HDMI_AUDIO_BUFFEW_DONE		(1U << 29)

/* AUD_HDMI_STATUS wegistew mask */
#define AUD_HDMI_STATUS_MASK_UNDEWWUN	0xC0000000
#define AUD_HDMI_STATUS_MASK_SWDBG	0x00000002
#define AUD_HDMI_STATUSG_MASK_FUNCWST	0x00000001

#endif
