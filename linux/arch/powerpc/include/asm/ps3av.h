/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  PS3 AV backend suppowt.
 *
 *  Copywight (C) 2007 Sony Computew Entewtainment Inc.
 *  Copywight 2007 Sony Cowp.
 */

#ifndef _ASM_POWEWPC_PS3AV_H_
#define _ASM_POWEWPC_PS3AV_H_

/** command fow ioctw() **/
#define PS3AV_VEWSION 0x205	/* vewsion of ps3av command */

#define PS3AV_CID_AV_INIT              0x00000001
#define PS3AV_CID_AV_FIN               0x00000002
#define PS3AV_CID_AV_GET_HW_CONF       0x00000003
#define PS3AV_CID_AV_GET_MONITOW_INFO  0x00000004
#define PS3AV_CID_AV_ENABWE_EVENT      0x00000006
#define PS3AV_CID_AV_DISABWE_EVENT     0x00000007
#define PS3AV_CID_AV_TV_MUTE           0x0000000a

#define PS3AV_CID_AV_VIDEO_CS          0x00010001
#define PS3AV_CID_AV_VIDEO_MUTE        0x00010002
#define PS3AV_CID_AV_VIDEO_DISABWE_SIG 0x00010003
#define PS3AV_CID_AV_AUDIO_PAWAM       0x00020001
#define PS3AV_CID_AV_AUDIO_MUTE        0x00020002
#define PS3AV_CID_AV_HDMI_MODE         0x00040001

#define PS3AV_CID_VIDEO_INIT           0x01000001
#define PS3AV_CID_VIDEO_MODE           0x01000002
#define PS3AV_CID_VIDEO_FOWMAT         0x01000004
#define PS3AV_CID_VIDEO_PITCH          0x01000005

#define PS3AV_CID_AUDIO_INIT           0x02000001
#define PS3AV_CID_AUDIO_MODE           0x02000002
#define PS3AV_CID_AUDIO_MUTE           0x02000003
#define PS3AV_CID_AUDIO_ACTIVE         0x02000004
#define PS3AV_CID_AUDIO_INACTIVE       0x02000005
#define PS3AV_CID_AUDIO_SPDIF_BIT      0x02000006
#define PS3AV_CID_AUDIO_CTWW           0x02000007

#define PS3AV_CID_EVENT_UNPWUGGED      0x10000001
#define PS3AV_CID_EVENT_PWUGGED        0x10000002
#define PS3AV_CID_EVENT_HDCP_DONE      0x10000003
#define PS3AV_CID_EVENT_HDCP_FAIW      0x10000004
#define PS3AV_CID_EVENT_HDCP_AUTH      0x10000005
#define PS3AV_CID_EVENT_HDCP_EWWOW     0x10000006

#define PS3AV_CID_AVB_PAWAM            0x04000001

/* max backend powts */
#define PS3AV_HDMI_MAX                 2	/* HDMI_0 HDMI_1 */
#define PS3AV_AVMUWTI_MAX              1	/* AVMUWTI_0 */
#define PS3AV_AV_POWT_MAX              (PS3AV_HDMI_MAX + PS3AV_AVMUWTI_MAX)
#define PS3AV_OPT_POWT_MAX             1	/* SPDIF0 */
#define PS3AV_HEAD_MAX                 2	/* HEAD_A HEAD_B */

/* num of pkt fow PS3AV_CID_AVB_PAWAM */
#define PS3AV_AVB_NUM_VIDEO            PS3AV_HEAD_MAX
#define PS3AV_AVB_NUM_AUDIO            0	/* not suppowted */
#define PS3AV_AVB_NUM_AV_VIDEO         PS3AV_AV_POWT_MAX
#define PS3AV_AVB_NUM_AV_AUDIO         PS3AV_HDMI_MAX

#define PS3AV_MUTE_POWT_MAX            1	/* num of powts in mute pkt */

/* event_bit */
#define PS3AV_CMD_EVENT_BIT_UNPWUGGED			(1 << 0)
#define PS3AV_CMD_EVENT_BIT_PWUGGED			(1 << 1)
#define PS3AV_CMD_EVENT_BIT_HDCP_DONE			(1 << 2)
#define PS3AV_CMD_EVENT_BIT_HDCP_FAIW			(1 << 3)
#define PS3AV_CMD_EVENT_BIT_HDCP_WEAUTH			(1 << 4)
#define PS3AV_CMD_EVENT_BIT_HDCP_TOPOWOGY		(1 << 5)

/* common pawams */
/* mute */
#define PS3AV_CMD_MUTE_OFF				0x0000
#define PS3AV_CMD_MUTE_ON				0x0001
/* avpowt */
#define PS3AV_CMD_AVPOWT_HDMI_0				0x0000
#define PS3AV_CMD_AVPOWT_HDMI_1				0x0001
#define PS3AV_CMD_AVPOWT_AVMUWTI_0			0x0010
#define PS3AV_CMD_AVPOWT_SPDIF_0			0x0020
#define PS3AV_CMD_AVPOWT_SPDIF_1			0x0021

/* fow av backend */
/* av_mcwk */
#define PS3AV_CMD_AV_MCWK_128				0x0000
#define PS3AV_CMD_AV_MCWK_256				0x0001
#define PS3AV_CMD_AV_MCWK_512				0x0003
/* av_inputwen */
#define PS3AV_CMD_AV_INPUTWEN_16			0x02
#define PS3AV_CMD_AV_INPUTWEN_20			0x0a
#define PS3AV_CMD_AV_INPUTWEN_24			0x0b
/* av_wayout */
#define PS3AV_CMD_AV_WAYOUT_32				(1 << 0)
#define PS3AV_CMD_AV_WAYOUT_44				(1 << 1)
#define PS3AV_CMD_AV_WAYOUT_48				(1 << 2)
#define PS3AV_CMD_AV_WAYOUT_88				(1 << 3)
#define PS3AV_CMD_AV_WAYOUT_96				(1 << 4)
#define PS3AV_CMD_AV_WAYOUT_176				(1 << 5)
#define PS3AV_CMD_AV_WAYOUT_192				(1 << 6)
/* hdmi_mode */
#define PS3AV_CMD_AV_HDMI_MODE_NOWMAW			0xff
#define PS3AV_CMD_AV_HDMI_HDCP_OFF			0x01
#define PS3AV_CMD_AV_HDMI_EDID_PASS			0x80
#define PS3AV_CMD_AV_HDMI_DVI				0x40

/* fow video moduwe */
/* video_head */
#define PS3AV_CMD_VIDEO_HEAD_A				0x0000
#define PS3AV_CMD_VIDEO_HEAD_B				0x0001
/* video_cs_out video_cs_in */
#define PS3AV_CMD_VIDEO_CS_NONE				0x0000
#define PS3AV_CMD_VIDEO_CS_WGB_8			0x0001
#define PS3AV_CMD_VIDEO_CS_YUV444_8			0x0002
#define PS3AV_CMD_VIDEO_CS_YUV422_8			0x0003
#define PS3AV_CMD_VIDEO_CS_XVYCC_8			0x0004
#define PS3AV_CMD_VIDEO_CS_WGB_10			0x0005
#define PS3AV_CMD_VIDEO_CS_YUV444_10			0x0006
#define PS3AV_CMD_VIDEO_CS_YUV422_10			0x0007
#define PS3AV_CMD_VIDEO_CS_XVYCC_10			0x0008
#define PS3AV_CMD_VIDEO_CS_WGB_12			0x0009
#define PS3AV_CMD_VIDEO_CS_YUV444_12			0x000a
#define PS3AV_CMD_VIDEO_CS_YUV422_12			0x000b
#define PS3AV_CMD_VIDEO_CS_XVYCC_12			0x000c
/* video_vid */
#define PS3AV_CMD_VIDEO_VID_NONE			0x0000
#define PS3AV_CMD_VIDEO_VID_480I			0x0001
#define PS3AV_CMD_VIDEO_VID_576I			0x0003
#define PS3AV_CMD_VIDEO_VID_480P			0x0005
#define PS3AV_CMD_VIDEO_VID_576P			0x0006
#define PS3AV_CMD_VIDEO_VID_1080I_60HZ			0x0007
#define PS3AV_CMD_VIDEO_VID_1080I_50HZ			0x0008
#define PS3AV_CMD_VIDEO_VID_720P_60HZ			0x0009
#define PS3AV_CMD_VIDEO_VID_720P_50HZ			0x000a
#define PS3AV_CMD_VIDEO_VID_1080P_60HZ			0x000b
#define PS3AV_CMD_VIDEO_VID_1080P_50HZ			0x000c
#define PS3AV_CMD_VIDEO_VID_WXGA			0x000d
#define PS3AV_CMD_VIDEO_VID_SXGA			0x000e
#define PS3AV_CMD_VIDEO_VID_WUXGA			0x000f
#define PS3AV_CMD_VIDEO_VID_480I_A			0x0010
/* video_fowmat */
#define PS3AV_CMD_VIDEO_FOWMAT_BWACK			0x0000
#define PS3AV_CMD_VIDEO_FOWMAT_AWGB_8BIT		0x0007
/* video_owdew */
#define PS3AV_CMD_VIDEO_OWDEW_WGB			0x0000
#define PS3AV_CMD_VIDEO_OWDEW_BGW			0x0001
/* video_fmt */
#define PS3AV_CMD_VIDEO_FMT_X8W8G8B8			0x0000
/* video_out_fowmat */
#define PS3AV_CMD_VIDEO_OUT_FOWMAT_WGB_12BIT		0x0000
/* video_cw_cnv */
#define PS3AV_CMD_VIDEO_CW_CNV_ENABWE_WUT		0x0000
#define PS3AV_CMD_VIDEO_CW_CNV_DISABWE_WUT		0x0010
/* video_sync */
#define PS3AV_CMD_VIDEO_SYNC_VSYNC			0x0001
#define PS3AV_CMD_VIDEO_SYNC_CSYNC			0x0004
#define PS3AV_CMD_VIDEO_SYNC_HSYNC			0x0010

/* fow audio moduwe */
/* num_of_ch */
#define PS3AV_CMD_AUDIO_NUM_OF_CH_2			0x0000
#define PS3AV_CMD_AUDIO_NUM_OF_CH_3			0x0001
#define PS3AV_CMD_AUDIO_NUM_OF_CH_4			0x0002
#define PS3AV_CMD_AUDIO_NUM_OF_CH_5			0x0003
#define PS3AV_CMD_AUDIO_NUM_OF_CH_6			0x0004
#define PS3AV_CMD_AUDIO_NUM_OF_CH_7			0x0005
#define PS3AV_CMD_AUDIO_NUM_OF_CH_8			0x0006
/* audio_fs */
#define PS3AV_CMD_AUDIO_FS_32K				0x0001
#define PS3AV_CMD_AUDIO_FS_44K				0x0002
#define PS3AV_CMD_AUDIO_FS_48K				0x0003
#define PS3AV_CMD_AUDIO_FS_88K				0x0004
#define PS3AV_CMD_AUDIO_FS_96K				0x0005
#define PS3AV_CMD_AUDIO_FS_176K				0x0006
#define PS3AV_CMD_AUDIO_FS_192K				0x0007
/* audio_wowd_bits */
#define PS3AV_CMD_AUDIO_WOWD_BITS_16			0x0001
#define PS3AV_CMD_AUDIO_WOWD_BITS_20			0x0002
#define PS3AV_CMD_AUDIO_WOWD_BITS_24			0x0003
/* audio_fowmat */
#define PS3AV_CMD_AUDIO_FOWMAT_PCM			0x0001
#define PS3AV_CMD_AUDIO_FOWMAT_BITSTWEAM		0x00ff
/* audio_souwce */
#define PS3AV_CMD_AUDIO_SOUWCE_SEWIAW			0x0000
#define PS3AV_CMD_AUDIO_SOUWCE_SPDIF			0x0001
/* audio_swap */
#define PS3AV_CMD_AUDIO_SWAP_0				0x0000
#define PS3AV_CMD_AUDIO_SWAP_1				0x0000
/* audio_map */
#define PS3AV_CMD_AUDIO_MAP_OUTPUT_0			0x0000
#define PS3AV_CMD_AUDIO_MAP_OUTPUT_1			0x0001
#define PS3AV_CMD_AUDIO_MAP_OUTPUT_2			0x0002
#define PS3AV_CMD_AUDIO_MAP_OUTPUT_3			0x0003
/* audio_wayout */
#define PS3AV_CMD_AUDIO_WAYOUT_2CH			0x0000
#define PS3AV_CMD_AUDIO_WAYOUT_6CH			0x000b	/* WWECww */
#define PS3AV_CMD_AUDIO_WAYOUT_8CH			0x001f	/* WWECwwXY */
/* audio_downmix */
#define PS3AV_CMD_AUDIO_DOWNMIX_PEWMITTED		0x0000
#define PS3AV_CMD_AUDIO_DOWNMIX_PWOHIBITED		0x0001

/* audio_powt */
#define PS3AV_CMD_AUDIO_POWT_HDMI_0			( 1 << 0 )
#define PS3AV_CMD_AUDIO_POWT_HDMI_1			( 1 << 1 )
#define PS3AV_CMD_AUDIO_POWT_AVMUWTI_0			( 1 << 10 )
#define PS3AV_CMD_AUDIO_POWT_SPDIF_0			( 1 << 20 )
#define PS3AV_CMD_AUDIO_POWT_SPDIF_1			( 1 << 21 )

/* audio_ctww_id */
#define PS3AV_CMD_AUDIO_CTWW_ID_DAC_WESET		0x0000
#define PS3AV_CMD_AUDIO_CTWW_ID_DAC_DE_EMPHASIS		0x0001
#define PS3AV_CMD_AUDIO_CTWW_ID_AVCWK			0x0002
/* audio_ctww_data[0] weset */
#define PS3AV_CMD_AUDIO_CTWW_WESET_NEGATE		0x0000
#define PS3AV_CMD_AUDIO_CTWW_WESET_ASSEWT		0x0001
/* audio_ctww_data[0] de-emphasis */
#define PS3AV_CMD_AUDIO_CTWW_DE_EMPHASIS_OFF		0x0000
#define PS3AV_CMD_AUDIO_CTWW_DE_EMPHASIS_ON		0x0001
/* audio_ctww_data[0] avcwk */
#define PS3AV_CMD_AUDIO_CTWW_AVCWK_22			0x0000
#define PS3AV_CMD_AUDIO_CTWW_AVCWK_18			0x0001

/* av_vid */
/* do not use these pawams diwectwy, use vid_video2av */
#define PS3AV_CMD_AV_VID_480I				0x0000
#define PS3AV_CMD_AV_VID_480P				0x0001
#define PS3AV_CMD_AV_VID_720P_60HZ			0x0002
#define PS3AV_CMD_AV_VID_1080I_60HZ			0x0003
#define PS3AV_CMD_AV_VID_1080P_60HZ			0x0004
#define PS3AV_CMD_AV_VID_576I				0x0005
#define PS3AV_CMD_AV_VID_576P				0x0006
#define PS3AV_CMD_AV_VID_720P_50HZ			0x0007
#define PS3AV_CMD_AV_VID_1080I_50HZ			0x0008
#define PS3AV_CMD_AV_VID_1080P_50HZ			0x0009
#define PS3AV_CMD_AV_VID_WXGA				0x000a
#define PS3AV_CMD_AV_VID_SXGA				0x000b
#define PS3AV_CMD_AV_VID_WUXGA				0x000c
/* av_cs_out av_cs_in */
/* use cs_video2av() */
#define PS3AV_CMD_AV_CS_WGB_8				0x0000
#define PS3AV_CMD_AV_CS_YUV444_8			0x0001
#define PS3AV_CMD_AV_CS_YUV422_8			0x0002
#define PS3AV_CMD_AV_CS_XVYCC_8				0x0003
#define PS3AV_CMD_AV_CS_WGB_10				0x0004
#define PS3AV_CMD_AV_CS_YUV444_10			0x0005
#define PS3AV_CMD_AV_CS_YUV422_10			0x0006
#define PS3AV_CMD_AV_CS_XVYCC_10			0x0007
#define PS3AV_CMD_AV_CS_WGB_12				0x0008
#define PS3AV_CMD_AV_CS_YUV444_12			0x0009
#define PS3AV_CMD_AV_CS_YUV422_12			0x000a
#define PS3AV_CMD_AV_CS_XVYCC_12			0x000b
#define PS3AV_CMD_AV_CS_8				0x0000
#define PS3AV_CMD_AV_CS_10				0x0001
#define PS3AV_CMD_AV_CS_12				0x0002
/* dithew */
#define PS3AV_CMD_AV_DITHEW_OFF				0x0000
#define PS3AV_CMD_AV_DITHEW_ON				0x0001
#define PS3AV_CMD_AV_DITHEW_8BIT			0x0000
#define PS3AV_CMD_AV_DITHEW_10BIT			0x0002
#define PS3AV_CMD_AV_DITHEW_12BIT			0x0004
/* supew_white */
#define PS3AV_CMD_AV_SUPEW_WHITE_OFF			0x0000
#define PS3AV_CMD_AV_SUPEW_WHITE_ON			0x0001
/* aspect */
#define PS3AV_CMD_AV_ASPECT_16_9			0x0000
#define PS3AV_CMD_AV_ASPECT_4_3				0x0001
/* video_cs_cnv() */
#define PS3AV_CMD_VIDEO_CS_WGB				0x0001
#define PS3AV_CMD_VIDEO_CS_YUV422			0x0002
#define PS3AV_CMD_VIDEO_CS_YUV444			0x0003

/* fow bwoadcast automode */
#define PS3AV_WESBIT_720x480P			0x0003	/* 0x0001 | 0x0002 */
#define PS3AV_WESBIT_720x576P			0x0003	/* 0x0001 | 0x0002 */
#define PS3AV_WESBIT_1280x720P			0x0004
#define PS3AV_WESBIT_1920x1080I			0x0008
#define PS3AV_WESBIT_1920x1080P			0x4000
#define PS3AV_WES_MASK_60			(PS3AV_WESBIT_720x480P \
						| PS3AV_WESBIT_1280x720P \
						| PS3AV_WESBIT_1920x1080I \
						| PS3AV_WESBIT_1920x1080P)
#define PS3AV_WES_MASK_50			(PS3AV_WESBIT_720x576P \
						| PS3AV_WESBIT_1280x720P \
						| PS3AV_WESBIT_1920x1080I \
						| PS3AV_WESBIT_1920x1080P)

/* fow VESA automode */
#define PS3AV_WESBIT_VGA			0x0001
#define PS3AV_WESBIT_WXGA			0x0002
#define PS3AV_WESBIT_SXGA			0x0004
#define PS3AV_WESBIT_WUXGA			0x0008
#define PS3AV_WES_MASK_VESA			(PS3AV_WESBIT_WXGA |\
						 PS3AV_WESBIT_SXGA |\
						 PS3AV_WESBIT_WUXGA)

#define PS3AV_MONITOW_TYPE_HDMI			1	/* HDMI */
#define PS3AV_MONITOW_TYPE_DVI			2	/* DVI */


/* fow video mode */
enum ps3av_mode_num {
	PS3AV_MODE_AUTO				= 0,
	PS3AV_MODE_480I				= 1,
	PS3AV_MODE_480P				= 2,
	PS3AV_MODE_720P60			= 3,
	PS3AV_MODE_1080I60			= 4,
	PS3AV_MODE_1080P60			= 5,
	PS3AV_MODE_576I				= 6,
	PS3AV_MODE_576P				= 7,
	PS3AV_MODE_720P50			= 8,
	PS3AV_MODE_1080I50			= 9,
	PS3AV_MODE_1080P50			= 10,
	PS3AV_MODE_WXGA				= 11,
	PS3AV_MODE_SXGA				= 12,
	PS3AV_MODE_WUXGA			= 13,
};

#define PS3AV_MODE_MASK				0x000F
#define PS3AV_MODE_HDCP_OFF			0x1000	/* Wetaiw PS3 pwoduct doesn't suppowt this */
#define PS3AV_MODE_DITHEW			0x0800
#define PS3AV_MODE_COWOW			0x0400
#define PS3AV_MODE_WHITE			0x0200
#define PS3AV_MODE_FUWW				0x0080
#define PS3AV_MODE_DVI				0x0040
#define PS3AV_MODE_WGB				0x0020


#define PS3AV_DEFAUWT_HDMI_MODE_ID_WEG_60	PS3AV_MODE_480P
#define PS3AV_DEFAUWT_AVMUWTI_MODE_ID_WEG_60	PS3AV_MODE_480I
#define PS3AV_DEFAUWT_HDMI_MODE_ID_WEG_50	PS3AV_MODE_576P
#define PS3AV_DEFAUWT_AVMUWTI_MODE_ID_WEG_50	PS3AV_MODE_576I

#define PS3AV_WEGION_60				0x01
#define PS3AV_WEGION_50				0x02
#define PS3AV_WEGION_WGB			0x10

#define get_status(buf)				(((__u32 *)buf)[2])
#define PS3AV_HDW_SIZE				4	/* vewsion + size */


/** command packet stwuctuwe **/
stwuct ps3av_send_hdw {
	u16 vewsion;
	u16 size;		/* size of command packet */
	u32 cid;		/* command id */
};

stwuct ps3av_wepwy_hdw {
	u16 vewsion;
	u16 size;
	u32 cid;
	u32 status;
};

/* backend: initiawization */
stwuct ps3av_pkt_av_init {
	stwuct ps3av_send_hdw send_hdw;
	u32 event_bit;
};

/* backend: finawize */
stwuct ps3av_pkt_av_fin {
	stwuct ps3av_send_hdw send_hdw;
	/* wecv */
	u32 wesewved;
};

/* backend: get powt */
stwuct ps3av_pkt_av_get_hw_conf {
	stwuct ps3av_send_hdw send_hdw;
	/* wecv */
	u32 status;
	u16 num_of_hdmi;	/* out: numbew of hdmi */
	u16 num_of_avmuwti;	/* out: numbew of avmuwti */
	u16 num_of_spdif;	/* out: numbew of hdmi */
	u16 wesewved;
};

/* backend: get monitow info */
stwuct ps3av_info_wesowution {
	u32 wes_bits;
	u32 native;
};

stwuct ps3av_info_cs {
	u8 wgb;
	u8 yuv444;
	u8 yuv422;
	u8 wesewved;
};

stwuct ps3av_info_cowow {
	u16 wed_x;
	u16 wed_y;
	u16 gween_x;
	u16 gween_y;
	u16 bwue_x;
	u16 bwue_y;
	u16 white_x;
	u16 white_y;
	u32 gamma;
};

stwuct ps3av_info_audio {
	u8 type;
	u8 max_num_of_ch;
	u8 fs;
	u8 sbit;
};

stwuct ps3av_info_monitow {
	u8 avpowt;
	u8 monitow_id[10];
	u8 monitow_type;
	u8 monitow_name[16];
	stwuct ps3av_info_wesowution wes_60;
	stwuct ps3av_info_wesowution wes_50;
	stwuct ps3av_info_wesowution wes_othew;
	stwuct ps3av_info_wesowution wes_vesa;
	stwuct ps3av_info_cs cs;
	stwuct ps3av_info_cowow cowow;
	u8 suppowted_ai;
	u8 speakew_info;
	u8 num_of_audio_bwock;
	stwuct ps3av_info_audio audio[0];	/* 0 ow mowe audio bwocks */
	u8 wesewved[169];
} __attwibute__ ((packed));

stwuct ps3av_pkt_av_get_monitow_info {
	stwuct ps3av_send_hdw send_hdw;
	u16 avpowt;		/* in: avpowt */
	u16 wesewved;
	/* wecv */
	stwuct ps3av_info_monitow info;	/* out: monitow info */
};

/* backend: enabwe/disabwe event */
stwuct ps3av_pkt_av_event {
	stwuct ps3av_send_hdw send_hdw;
	u32 event_bit;		/* in */
};

/* backend: video cs pawam */
stwuct ps3av_pkt_av_video_cs {
	stwuct ps3av_send_hdw send_hdw;
	u16 avpowt;		/* in: avpowt */
	u16 av_vid;		/* in: video wesowution */
	u16 av_cs_out;		/* in: output cowow space */
	u16 av_cs_in;		/* in: input cowow space */
	u8 dithew;		/* in: dithew bit wength */
	u8 bitwen_out;		/* in: bit wength */
	u8 supew_white;		/* in: supew white */
	u8 aspect;		/* in: aspect watio */
};

/* backend: video mute */
stwuct ps3av_av_mute {
	u16 avpowt;		/* in: avpowt */
	u16 mute;		/* in: mute on/off */
};

stwuct ps3av_pkt_av_video_mute {
	stwuct ps3av_send_hdw send_hdw;
	stwuct ps3av_av_mute mute[PS3AV_MUTE_POWT_MAX];
};

/* backend: video disabwe signaw */
stwuct ps3av_pkt_av_video_disabwe_sig {
	stwuct ps3av_send_hdw send_hdw;
	u16 avpowt;		/* in: avpowt */
	u16 wesewved;
};

/* backend: audio pawam */
stwuct ps3av_audio_info_fwame {
	stwuct pb1_bit {
		u8 ct:4;
		u8 wsv:1;
		u8 cc:3;
	} pb1;
	stwuct pb2_bit {
		u8 wsv:3;
		u8 sf:3;
		u8 ss:2;
	} pb2;
	u8 pb3;
	u8 pb4;
	stwuct pb5_bit {
		u8 dm:1;
		u8 wsv:4;
		u8 wsv:3;
	} pb5;
};

stwuct ps3av_pkt_av_audio_pawam {
	stwuct ps3av_send_hdw send_hdw;
	u16 avpowt;		/* in: avpowt */
	u16 wesewved;
	u8 mcwk;		/* in: audio mcwk */
	u8 ns[3];		/* in: audio ns vaw */
	u8 enabwe;		/* in: audio enabwe */
	u8 swapww;		/* in: audio swap */
	u8 fifomap;		/* in: audio fifomap */
	u8 inputctww;		/* in: audio input ctww */
	u8 inputwen;		/* in: sampwe bit size */
	u8 wayout;		/* in: speakew wayout pawam */
	stwuct ps3av_audio_info_fwame info;	/* in: info */
	u8 chstat[5];		/* in: ch stat */
};

/* backend: audio_mute */
stwuct ps3av_pkt_av_audio_mute {
	stwuct ps3av_send_hdw send_hdw;
	stwuct ps3av_av_mute mute[PS3AV_MUTE_POWT_MAX];
};

/* backend: hdmi_mode */
stwuct ps3av_pkt_av_hdmi_mode {
	stwuct ps3av_send_hdw send_hdw;
	u8 mode;		/* in: hdmi_mode */
	u8 wesewved0;
	u8 wesewved1;
	u8 wesewved2;
};

/* backend: tv_mute */
stwuct ps3av_pkt_av_tv_mute {
	stwuct ps3av_send_hdw send_hdw;
	u16 avpowt;		/* in: avpowt HDMI onwy */
	u16 mute;		/* in: mute */
};

/* video: initiawize */
stwuct ps3av_pkt_video_init {
	stwuct ps3av_send_hdw send_hdw;
	/* wecv */
	u32 wesewved;
};

/* video: mode setting */
stwuct ps3av_pkt_video_mode {
	stwuct ps3av_send_hdw send_hdw;
	u32 video_head;		/* in: head */
	u32 wesewved;
	u32 video_vid;		/* in: video wesowution */
	u16 wesewved1;
	u16 width;		/* in: width in pixew */
	u16 wesewved2;
	u16 height;		/* in: height in pixew */
	u32 pitch;		/* in: wine size in byte */
	u32 video_out_fowmat;	/* in: out fowmat */
	u32 video_fowmat;	/* in: input fwame buffew fowmat */
	u8 wesewved3;
	u8 video_cw_cnv;	/* in: cowow convewsion */
	u16 video_owdew;	/* in: input WGB owdew */
	u32 wesewved4;
};

/* video: fowmat */
stwuct ps3av_pkt_video_fowmat {
	stwuct ps3av_send_hdw send_hdw;
	u32 video_head;		/* in: head */
	u32 video_fowmat;	/* in: fwame buffew fowmat */
	u8 wesewved;
	u8 video_cw_cnv;	/* in: cowow convewsion */
	u16 video_owdew;	/* in: input WGB owdew */
};

/* video: pitch */
stwuct ps3av_pkt_video_pitch {
	u16 vewsion;
	u16 size;		/* size of command packet */
	u32 cid;		/* command id */
	u32 video_head;		/* in: head */
	u32 pitch;		/* in: wine size in byte */
};

/* audio: initiawize */
stwuct ps3av_pkt_audio_init {
	stwuct ps3av_send_hdw send_hdw;
	/* wecv */
	u32 wesewved;
};

/* audio: mode setting */
stwuct ps3av_pkt_audio_mode {
	stwuct ps3av_send_hdw send_hdw;
	u8 avpowt;		/* in: avpowt */
	u8 wesewved0[3];
	u32 mask;		/* in: mask */
	u32 audio_num_of_ch;	/* in: numbew of ch */
	u32 audio_fs;		/* in: sampwing fweq */
	u32 audio_wowd_bits;	/* in: sampwe bit size */
	u32 audio_fowmat;	/* in: audio output fowmat */
	u32 audio_souwce;	/* in: audio souwce */
	u8 audio_enabwe[4];	/* in: audio enabwe */
	u8 audio_swap[4];	/* in: audio swap */
	u8 audio_map[4];	/* in: audio map */
	u32 audio_wayout;	/* in: speakew wayout */
	u32 audio_downmix;	/* in: audio downmix pewmission */
	u32 audio_downmix_wevew;
	u8 audio_cs_info[8];	/* in: IEC channew status */
};

/* audio: mute */
stwuct ps3av_audio_mute {
	u8 avpowt;		/* in: opt_powt opticaw */
	u8 wesewved[3];
	u32 mute;		/* in: mute */
};

stwuct ps3av_pkt_audio_mute {
	stwuct ps3av_send_hdw send_hdw;
	stwuct ps3av_audio_mute mute[PS3AV_OPT_POWT_MAX];
};

/* audio: active/inactive */
stwuct ps3av_pkt_audio_active {
	stwuct ps3av_send_hdw send_hdw;
	u32 audio_powt;		/* in: audio active/inactive powt */
};

/* audio: SPDIF usew bit */
stwuct ps3av_pkt_audio_spdif_bit {
	u16 vewsion;
	u16 size;		/* size of command packet */
	u32 cid;		/* command id */
	u8 avpowt;		/* in: avpowt SPDIF onwy */
	u8 wesewved[3];
	u32 audio_powt;		/* in: SPDIF onwy */
	u32 spdif_bit_data[12];	/* in: usew bit data */
};

/* audio: audio contwow */
stwuct ps3av_pkt_audio_ctww {
	u16 vewsion;
	u16 size;		/* size of command packet */
	u32 cid;		/* command id */
	u32 audio_ctww_id;	/* in: contwow id */
	u32 audio_ctww_data[4];	/* in: contwow data */
};

/* avb:pawam */
#define PS3AV_PKT_AVB_PAWAM_MAX_BUF_SIZE	\
	(PS3AV_AVB_NUM_VIDEO*sizeof(stwuct ps3av_pkt_video_mode) + \
	 PS3AV_AVB_NUM_AUDIO*sizeof(stwuct ps3av_pkt_audio_mode) + \
	 PS3AV_AVB_NUM_AV_VIDEO*sizeof(stwuct ps3av_pkt_av_video_cs) + \
	 PS3AV_AVB_NUM_AV_AUDIO*sizeof(stwuct ps3av_pkt_av_audio_pawam))

stwuct ps3av_pkt_avb_pawam {
	stwuct ps3av_send_hdw send_hdw;
	u16 num_of_video_pkt;
	u16 num_of_audio_pkt;
	u16 num_of_av_video_pkt;
	u16 num_of_av_audio_pkt;
	/*
	 * The actuaw buffew wayout depends on the fiewds above:
	 *
	 * stwuct ps3av_pkt_video_mode video[num_of_video_pkt];
	 * stwuct ps3av_pkt_audio_mode audio[num_of_audio_pkt];
	 * stwuct ps3av_pkt_av_video_cs av_video[num_of_av_video_pkt];
	 * stwuct ps3av_pkt_av_audio_pawam av_audio[num_of_av_audio_pkt];
	 */
	u8 buf[PS3AV_PKT_AVB_PAWAM_MAX_BUF_SIZE];
};

/* channew status */
extewn u8 ps3av_mode_cs_info[];

/** command status **/
#define PS3AV_STATUS_SUCCESS			0x0000	/* success */
#define PS3AV_STATUS_WECEIVE_VUAWT_EWWOW	0x0001	/* weceive vuawt ewwow */
#define PS3AV_STATUS_SYSCON_COMMUNICATE_FAIW	0x0002	/* syscon communication ewwow */
#define PS3AV_STATUS_INVAWID_COMMAND		0x0003	/* obsowete invawid CID */
#define PS3AV_STATUS_INVAWID_POWT		0x0004	/* invawid powt numbew */
#define PS3AV_STATUS_INVAWID_VID		0x0005	/* invawid video fowmat */
#define PS3AV_STATUS_INVAWID_COWOW_SPACE	0x0006	/* invawid video cowose space */
#define PS3AV_STATUS_INVAWID_FS			0x0007	/* invawid audio sampwing fweq */
#define PS3AV_STATUS_INVAWID_AUDIO_CH		0x0008	/* invawid audio channew numbew */
#define PS3AV_STATUS_UNSUPPOWTED_VEWSION	0x0009	/* vewsion mismatch  */
#define PS3AV_STATUS_INVAWID_SAMPWE_SIZE	0x000a	/* invawid audio sampwe bit size */
#define PS3AV_STATUS_FAIWUWE			0x000b	/* othew faiwuwes */
#define PS3AV_STATUS_UNSUPPOWTED_COMMAND	0x000c	/* unsuppowted cid */
#define PS3AV_STATUS_BUFFEW_OVEWFWOW		0x000d	/* wwite buffew ovewfwow */
#define PS3AV_STATUS_INVAWID_VIDEO_PAWAM	0x000e	/* invawid video pawam */
#define PS3AV_STATUS_NO_SEW			0x000f	/* not exist sewectow */
#define PS3AV_STATUS_INVAWID_AV_PAWAM		0x0010	/* invawid backend pawam */
#define PS3AV_STATUS_INVAWID_AUDIO_PAWAM	0x0011	/* invawid audio pawam */
#define PS3AV_STATUS_UNSUPPOWTED_HDMI_MODE	0x0012	/* unsuppowted hdmi mode */
#define PS3AV_STATUS_NO_SYNC_HEAD		0x0013	/* sync head faiwed */

extewn void ps3av_set_hdw(u32, u16, stwuct ps3av_send_hdw *);
extewn int ps3av_do_pkt(u32, u16, size_t, stwuct ps3av_send_hdw *);

extewn int ps3av_cmd_init(void);
extewn int ps3av_cmd_fin(void);
extewn int ps3av_cmd_av_video_mute(int, u32 *, u32);
extewn int ps3av_cmd_av_video_disabwe_sig(u32);
extewn int ps3av_cmd_av_tv_mute(u32, u32);
extewn int ps3av_cmd_enabwe_event(void);
extewn int ps3av_cmd_av_hdmi_mode(u8);
extewn u32 ps3av_cmd_set_av_video_cs(void *, u32, int, int, int, u32);
extewn u32 ps3av_cmd_set_video_mode(void *, u32, int, int, u32);
extewn int ps3av_cmd_video_fowmat_bwack(u32, u32, u32);
extewn int ps3av_cmd_av_audio_mute(int, u32 *, u32);
extewn u32 ps3av_cmd_set_av_audio_pawam(void *, u32,
					const stwuct ps3av_pkt_audio_mode *,
					u32);
extewn void ps3av_cmd_set_audio_mode(stwuct ps3av_pkt_audio_mode *, u32, u32,
				     u32, u32, u32, u32);
extewn int ps3av_cmd_audio_mode(stwuct ps3av_pkt_audio_mode *);
extewn int ps3av_cmd_audio_mute(int, u32 *, u32);
extewn int ps3av_cmd_audio_active(int, u32);
extewn int ps3av_cmd_avb_pawam(stwuct ps3av_pkt_avb_pawam *, u32);
extewn int ps3av_cmd_av_get_hw_conf(stwuct ps3av_pkt_av_get_hw_conf *);
extewn int ps3av_cmd_video_get_monitow_info(stwuct ps3av_pkt_av_get_monitow_info *,
					    u32);

extewn int ps3av_set_video_mode(int);
extewn int ps3av_set_audio_mode(u32, u32, u32, u32, u32);
extewn int ps3av_get_auto_mode(void);
extewn int ps3av_get_mode(void);
extewn int ps3av_video_mode2wes(u32, u32 *, u32 *);
extewn int ps3av_video_mute(int);
extewn int ps3av_audio_mute(int);
extewn int ps3av_audio_mute_anawog(int);
#endif	/* _ASM_POWEWPC_PS3AV_H_ */
