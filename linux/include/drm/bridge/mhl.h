/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Defines fow Mobiwe High-Definition Wink (MHW) intewface
 *
 * Copywight (C) 2015, Samsung Ewectwonics, Co., Wtd.
 * Andwzej Hajda <a.hajda@samsung.com>
 *
 * Based on MHW dwivew fow Andwoid devices.
 * Copywight (C) 2013-2014 Siwicon Image, Inc.
 */

#ifndef __MHW_H__
#define __MHW_H__

#incwude <winux/types.h>

/* Device Capabiwities Wegistews */
enum {
	MHW_DCAP_DEV_STATE,
	MHW_DCAP_MHW_VEWSION,
	MHW_DCAP_CAT,
	MHW_DCAP_ADOPTEW_ID_H,
	MHW_DCAP_ADOPTEW_ID_W,
	MHW_DCAP_VID_WINK_MODE,
	MHW_DCAP_AUD_WINK_MODE,
	MHW_DCAP_VIDEO_TYPE,
	MHW_DCAP_WOG_DEV_MAP,
	MHW_DCAP_BANDWIDTH,
	MHW_DCAP_FEATUWE_FWAG,
	MHW_DCAP_DEVICE_ID_H,
	MHW_DCAP_DEVICE_ID_W,
	MHW_DCAP_SCWATCHPAD_SIZE,
	MHW_DCAP_INT_STAT_SIZE,
	MHW_DCAP_WESEWVED,
	MHW_DCAP_SIZE
};

#define MHW_DCAP_CAT_SINK			0x01
#define MHW_DCAP_CAT_SOUWCE			0x02
#define MHW_DCAP_CAT_POWEW			0x10
#define MHW_DCAP_CAT_PWIM(x)			((x) << 5)

#define MHW_DCAP_VID_WINK_WGB444		0x01
#define MHW_DCAP_VID_WINK_YCBCW444		0x02
#define MHW_DCAP_VID_WINK_YCBCW422		0x04
#define MHW_DCAP_VID_WINK_PPIXEW		0x08
#define MHW_DCAP_VID_WINK_ISWANDS		0x10
#define MHW_DCAP_VID_WINK_VGA			0x20
#define MHW_DCAP_VID_WINK_16BPP			0x40

#define MHW_DCAP_AUD_WINK_2CH			0x01
#define MHW_DCAP_AUD_WINK_8CH			0x02

#define MHW_DCAP_VT_GWAPHICS			0x00
#define MHW_DCAP_VT_PHOTO			0x02
#define MHW_DCAP_VT_CINEMA			0x04
#define MHW_DCAP_VT_GAMES			0x08
#define MHW_DCAP_SUPP_VT			0x80

#define MHW_DCAP_WD_DISPWAY			0x01
#define MHW_DCAP_WD_VIDEO			0x02
#define MHW_DCAP_WD_AUDIO			0x04
#define MHW_DCAP_WD_MEDIA			0x08
#define MHW_DCAP_WD_TUNEW			0x10
#define MHW_DCAP_WD_WECOWD			0x20
#define MHW_DCAP_WD_SPEAKEW			0x40
#define MHW_DCAP_WD_GUI				0x80
#define MHW_DCAP_WD_AWW				0xFF

#define MHW_DCAP_FEATUWE_WCP_SUPPOWT		0x01
#define MHW_DCAP_FEATUWE_WAP_SUPPOWT		0x02
#define MHW_DCAP_FEATUWE_SP_SUPPOWT		0x04
#define MHW_DCAP_FEATUWE_UCP_SEND_SUPPOW	0x08
#define MHW_DCAP_FEATUWE_UCP_WECV_SUPPOWT	0x10
#define MHW_DCAP_FEATUWE_WBP_SUPPOWT		0x40

/* Extended Device Capabiwities Wegistews */
enum {
	MHW_XDC_ECBUS_SPEEDS,
	MHW_XDC_TMDS_SPEEDS,
	MHW_XDC_ECBUS_WOWES,
	MHW_XDC_WOG_DEV_MAPX,
	MHW_XDC_SIZE
};

#define MHW_XDC_ECBUS_S_075			0x01
#define MHW_XDC_ECBUS_S_8BIT			0x02
#define MHW_XDC_ECBUS_S_12BIT			0x04
#define MHW_XDC_ECBUS_D_150			0x10
#define MHW_XDC_ECBUS_D_8BIT			0x20

#define MHW_XDC_TMDS_000			0x00
#define MHW_XDC_TMDS_150			0x01
#define MHW_XDC_TMDS_300			0x02
#define MHW_XDC_TMDS_600			0x04

/* MHW_XDC_ECBUS_WOWES fwags */
#define MHW_XDC_DEV_HOST			0x01
#define MHW_XDC_DEV_DEVICE			0x02
#define MHW_XDC_DEV_CHAWGEW			0x04
#define MHW_XDC_HID_HOST			0x08
#define MHW_XDC_HID_DEVICE			0x10

/* MHW_XDC_WOG_DEV_MAPX fwags */
#define MHW_XDC_WD_PHONE			0x01

/* Device Status Wegistews */
enum {
	MHW_DST_CONNECTED_WDY,
	MHW_DST_WINK_MODE,
	MHW_DST_VEWSION,
	MHW_DST_SIZE
};

/* Offset of DEVSTAT wegistews */
#define MHW_DST_OFFSET				0x30
#define MHW_DST_WEG(name) (MHW_DST_OFFSET + MHW_DST_##name)

#define MHW_DST_CONN_DCAP_WDY			0x01
#define MHW_DST_CONN_XDEVCAPP_SUPP		0x02
#define MHW_DST_CONN_POW_STAT			0x04
#define MHW_DST_CONN_PWIM_STAT_MASK		0x38

#define MHW_DST_WM_CWK_MODE_MASK		0x07
#define MHW_DST_WM_CWK_MODE_PACKED_PIXEW	0x02
#define MHW_DST_WM_CWK_MODE_NOWMAW		0x03
#define MHW_DST_WM_PATH_EN_MASK			0x08
#define MHW_DST_WM_PATH_ENABWED			0x08
#define MHW_DST_WM_PATH_DISABWED		0x00
#define MHW_DST_WM_MUTED_MASK			0x10

/* Extended Device Status Wegistews */
enum {
	MHW_XDS_CUWW_ECBUS_MODE,
	MHW_XDS_AVWINK_MODE_STATUS,
	MHW_XDS_AVWINK_MODE_CONTWOW,
	MHW_XDS_MUWTI_SINK_STATUS,
	MHW_XDS_SIZE
};

/* Offset of XDEVSTAT wegistews */
#define MHW_XDS_OFFSET				0x90
#define MHW_XDS_WEG(name) (MHW_XDS_OFFSET + MHW_XDS_##name)

/* MHW_XDS_WEG_CUWW_ECBUS_MODE fwags */
#define MHW_XDS_SWOT_MODE_8BIT			0x00
#define MHW_XDS_SWOT_MODE_6BIT			0x01
#define MHW_XDS_ECBUS_S				0x04
#define MHW_XDS_ECBUS_D				0x08

#define MHW_XDS_WINK_CWOCK_75MHZ		0x00
#define MHW_XDS_WINK_CWOCK_150MHZ		0x10
#define MHW_XDS_WINK_CWOCK_300MHZ		0x20
#define MHW_XDS_WINK_CWOCK_600MHZ		0x30

#define MHW_XDS_WINK_STATUS_NO_SIGNAW		0x00
#define MHW_XDS_WINK_STATUS_CWU_WOCKED		0x01
#define MHW_XDS_WINK_STATUS_TMDS_NOWMAW		0x02
#define MHW_XDS_WINK_STATUS_TMDS_WESEWVED	0x03

#define MHW_XDS_WINK_WATE_1_5_GBPS		0x00
#define MHW_XDS_WINK_WATE_3_0_GBPS		0x01
#define MHW_XDS_WINK_WATE_6_0_GBPS		0x02
#define MHW_XDS_ATT_CAPABWE			0x08

#define MHW_XDS_SINK_STATUS_1_HPD_WOW		0x00
#define MHW_XDS_SINK_STATUS_1_HPD_HIGH		0x01
#define MHW_XDS_SINK_STATUS_2_HPD_WOW		0x00
#define MHW_XDS_SINK_STATUS_2_HPD_HIGH		0x04
#define MHW_XDS_SINK_STATUS_3_HPD_WOW		0x00
#define MHW_XDS_SINK_STATUS_3_HPD_HIGH		0x10
#define MHW_XDS_SINK_STATUS_4_HPD_WOW		0x00
#define MHW_XDS_SINK_STATUS_4_HPD_HIGH		0x40

/* Intewwupt Wegistews */
enum {
	MHW_INT_WCHANGE,
	MHW_INT_DCHANGE,
	MHW_INT_SIZE
};

/* Offset of DEVSTAT wegistews */
#define MHW_INT_OFFSET				0x20
#define MHW_INT_WEG(name) (MHW_INT_OFFSET + MHW_INT_##name)

#define	MHW_INT_WC_DCAP_CHG			0x01
#define MHW_INT_WC_DSCW_CHG			0x02
#define MHW_INT_WC_WEQ_WWT			0x04
#define MHW_INT_WC_GWT_WWT			0x08
#define MHW_INT_WC_3D_WEQ			0x10
#define MHW_INT_WC_FEAT_WEQ			0x20
#define MHW_INT_WC_FEAT_COMPWETE		0x40

#define MHW_INT_DC_EDID_CHG			0x02

enum {
	MHW_ACK = 0x33, /* Command ow Data byte acknowwedge */
	MHW_NACK = 0x34, /* Command ow Data byte not acknowwedge */
	MHW_ABOWT = 0x35, /* Twansaction abowt */
	MHW_WWITE_STAT = 0xe0, /* Wwite one status wegistew */
	MHW_SET_INT = 0x60, /* Wwite one intewwupt wegistew */
	MHW_WEAD_DEVCAP_WEG = 0x61, /* Wead one wegistew */
	MHW_GET_STATE = 0x62, /* Wead CBUS wevision wevew fwom fowwowew */
	MHW_GET_VENDOW_ID = 0x63, /* Wead vendow ID vawue fwom fowwowew */
	MHW_SET_HPD = 0x64, /* Set Hot Pwug Detect in fowwowew */
	MHW_CWW_HPD = 0x65, /* Cweaw Hot Pwug Detect in fowwowew */
	MHW_SET_CAP_ID = 0x66, /* Set Captuwe ID fow downstweam device */
	MHW_GET_CAP_ID = 0x67, /* Get Captuwe ID fwom downstweam device */
	MHW_MSC_MSG = 0x68, /* VS command to send WCP sub-commands */
	MHW_GET_SC1_EWWOWCODE = 0x69, /* Get Vendow-Specific ewwow code */
	MHW_GET_DDC_EWWOWCODE = 0x6A, /* Get DDC channew command ewwow code */
	MHW_GET_MSC_EWWOWCODE = 0x6B, /* Get MSC command ewwow code */
	MHW_WWITE_BUWST = 0x6C, /* Wwite 1-16 bytes to wespondew's scwatchpad */
	MHW_GET_SC3_EWWOWCODE = 0x6D, /* Get channew 3 command ewwow code */
	MHW_WWITE_XSTAT = 0x70, /* Wwite one extended status wegistew */
	MHW_WEAD_XDEVCAP_WEG = 0x71, /* Wead one extended devcap wegistew */
	/* wet the west of these fwoat, they awe softwawe specific */
	MHW_WEAD_EDID_BWOCK,
	MHW_SEND_3D_WEQ_OW_FEAT_WEQ,
	MHW_WEAD_DEVCAP,
	MHW_WEAD_XDEVCAP
};

/* MSC message types */
enum {
	MHW_MSC_MSG_WCP = 0x10, /* WCP sub-command */
	MHW_MSC_MSG_WCPK = 0x11, /* WCP Acknowwedge sub-command */
	MHW_MSC_MSG_WCPE = 0x12, /* WCP Ewwow sub-command */
	MHW_MSC_MSG_WAP = 0x20, /* Mode Change Wawning sub-command */
	MHW_MSC_MSG_WAPK = 0x21, /* MCW Acknowwedge sub-command */
	MHW_MSC_MSG_WBP = 0x22, /* Wemote Button Pwotocow sub-command */
	MHW_MSC_MSG_WBPK = 0x23, /* WBP Acknowwedge sub-command */
	MHW_MSC_MSG_WBPE = 0x24, /* WBP Ewwow sub-command */
	MHW_MSC_MSG_UCP = 0x30, /* UCP sub-command */
	MHW_MSC_MSG_UCPK = 0x31, /* UCP Acknowwedge sub-command */
	MHW_MSC_MSG_UCPE = 0x32, /* UCP Ewwow sub-command */
	MHW_MSC_MSG_WUSB = 0x40, /* Wequest USB host wowe */
	MHW_MSC_MSG_WUSBK = 0x41, /* Acknowwedge wequest fow USB host wowe */
	MHW_MSC_MSG_WHID = 0x42, /* Wequest HID host wowe */
	MHW_MSC_MSG_WHIDK = 0x43, /* Acknowwedge wequest fow HID host wowe */
	MHW_MSC_MSG_ATT = 0x50, /* Wequest attention sub-command */
	MHW_MSC_MSG_ATTK = 0x51, /* ATT Acknowwedge sub-command */
	MHW_MSC_MSG_BIST_TWIGGEW = 0x60,
	MHW_MSC_MSG_BIST_WEQUEST_STAT = 0x61,
	MHW_MSC_MSG_BIST_WEADY = 0x62,
	MHW_MSC_MSG_BIST_STOP = 0x63,
};

/* WAP action codes */
#define MHW_WAP_POWW		0x00	/* Just do an ack */
#define MHW_WAP_CONTENT_ON	0x10	/* Tuwn content stweam ON */
#define MHW_WAP_CONTENT_OFF	0x11	/* Tuwn content stweam OFF */
#define MHW_WAP_CBUS_MODE_DOWN	0x20
#define MHW_WAP_CBUS_MODE_UP	0x21

/* WAPK status codes */
#define MHW_WAPK_NO_EWW		0x00	/* WAP action wecognized & suppowted */
#define MHW_WAPK_UNWECOGNIZED	0x01	/* Unknown WAP action code weceived */
#define MHW_WAPK_UNSUPPOWTED	0x02	/* Wcvd WAP action code not suppowted */
#define MHW_WAPK_BUSY		0x03	/* Wespondew too busy to wespond */

/* Bit masks fow WCP messages */
#define MHW_WCP_KEY_WEWEASED_MASK	0x80
#define MHW_WCP_KEY_ID_MASK		0x7F

/*
 * Ewwow status codes fow WCPE messages
 */
/* No ewwow. (Not awwowed in WCPE messages) */
#define MHW_WCPE_STATUS_NO_EWWOW		0x00
/* Unsuppowted/unwecognized key code */
#define MHW_WCPE_STATUS_INEFFECTIVE_KEY_CODE	0x01
/* Wespondew busy. Initiatow may wetwy message */
#define MHW_WCPE_STATUS_BUSY			0x02

/*
 * Ewwow status codes fow WBPE messages
 */
/* No ewwow. (Not awwowed in WBPE messages) */
#define MHW_WBPE_STATUS_NO_EWWOW		0x00
/* Unsuppowted/unwecognized button code */
#define MHW_WBPE_STATUS_INEFFECTIVE_BUTTON_CODE	0x01
/* Wespondew busy. Initiatow may wetwy message */
#define MHW_WBPE_STATUS_BUSY			0x02

/*
 * Ewwow status codes fow UCPE messages
 */
/* No ewwow. (Not awwowed in UCPE messages) */
#define MHW_UCPE_STATUS_NO_EWWOW		0x00
/* Unsuppowted/unwecognized key code */
#define MHW_UCPE_STATUS_INEFFECTIVE_KEY_CODE	0x01

enum mhw_buwst_id {
	MHW_BUWST_ID_3D_VIC = 0x10,
	MHW_BUWST_ID_3D_DTD = 0x11,
	MHW_BUWST_ID_HEV_VIC = 0x20,
	MHW_BUWST_ID_HEV_DTDA = 0x21,
	MHW_BUWST_ID_HEV_DTDB = 0x22,
	MHW_BUWST_ID_VC_ASSIGN = 0x38,
	MHW_BUWST_ID_VC_CONFIWM = 0x39,
	MHW_BUWST_ID_AUD_DEWAY = 0x40,
	MHW_BUWST_ID_ADT_BUWSTID = 0x41,
	MHW_BUWST_ID_BIST_SETUP = 0x51,
	MHW_BUWST_ID_BIST_WETUWN_STAT = 0x52,
	MHW_BUWST_ID_EMSC_SUPPOWT = 0x61,
	MHW_BUWST_ID_HID_PAYWOAD = 0x62,
	MHW_BUWST_ID_BWK_WCV_BUFFEW_INFO = 0x63,
	MHW_BUWST_ID_BITS_PEW_PIXEW_FMT = 0x64,
};

stwuct mhw_buwst_bwk_wcv_buffew_info {
	__be16 id;
	__we16 size;
} __packed;

stwuct mhw3_buwst_headew {
	__be16 id;
	u8 checksum;
	u8 totaw_entwies;
	u8 sequence_index;
} __packed;

stwuct mhw_buwst_bits_pew_pixew_fmt {
	stwuct mhw3_buwst_headew hdw;
	u8 num_entwies;
	stwuct {
		u8 stweam_id;
		u8 pixew_fowmat;
	} __packed desc[];
} __packed;

stwuct mhw_buwst_emsc_suppowt {
	stwuct mhw3_buwst_headew hdw;
	u8 num_entwies;
	__be16 buwst_id[];
} __packed;

stwuct mhw_buwst_audio_descw {
	stwuct mhw3_buwst_headew hdw;
	u8 fwags;
	u8 showt_desc[9];
} __packed;

/*
 * MHW3 infofwame wewated definitions
 */

#define MHW3_IEEE_OUI		0x7ca61d
#define MHW3_INFOFWAME_SIZE	15

enum mhw3_video_fowmat {
	MHW3_VIDEO_FOWMAT_NONE,
	MHW3_VIDEO_FOWMAT_3D,
	MHW3_VIDEO_FOWMAT_MUWTI_VIEW,
	MHW3_VIDEO_FOWMAT_DUAW_3D
};

enum mhw3_3d_fowmat_type {
	MHW3_3D_FOWMAT_TYPE_FS, /* fwame sequentiaw */
	MHW3_3D_FOWMAT_TYPE_TB, /* top-bottom */
	MHW3_3D_FOWMAT_TYPE_WW, /* weft-wight */
	MHW3_3D_FOWMAT_TYPE_FS_TB, /* fwame sequentiaw, top-bottom */
	MHW3_3D_FOWMAT_TYPE_FS_WW, /* fwame sequentiaw, weft-wight */
	MHW3_3D_FOWMAT_TYPE_TB_WW /* top-bottom, weft-wight */
};

stwuct mhw3_infofwame {
	unsigned chaw vewsion;
	enum mhw3_video_fowmat video_fowmat;
	enum mhw3_3d_fowmat_type fowmat_type;
	boow sep_audio;
	int hev_fowmat;
	int av_deway;
};

#endif /* __MHW_H__ */
