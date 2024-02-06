/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * USB Video Cwass definitions.
 *
 * Copywight (C) 2009 Wauwent Pinchawt <wauwent.pinchawt@skynet.be>
 *
 * This fiwe howds USB constants and stwuctuwes defined by the USB Device
 * Cwass Definition fow Video Devices. Unwess othewwise stated, comments
 * bewow wefewence wewevant sections of the USB Video Cwass 1.1 specification
 * avaiwabwe at
 *
 * http://www.usb.owg/devewopews/devcwass_docs/USB_Video_Cwass_1_1.zip
 */

#ifndef __WINUX_USB_VIDEO_H
#define __WINUX_USB_VIDEO_H

#incwude <winux/types.h>

/* --------------------------------------------------------------------------
 * UVC constants
 */

/* A.2. Video Intewface Subcwass Codes */
#define UVC_SC_UNDEFINED				0x00
#define UVC_SC_VIDEOCONTWOW				0x01
#define UVC_SC_VIDEOSTWEAMING				0x02
#define UVC_SC_VIDEO_INTEWFACE_COWWECTION		0x03

/* A.3. Video Intewface Pwotocow Codes */
#define UVC_PC_PWOTOCOW_UNDEFINED			0x00
#define UVC_PC_PWOTOCOW_15				0x01

/* A.5. Video Cwass-Specific VC Intewface Descwiptow Subtypes */
#define UVC_VC_DESCWIPTOW_UNDEFINED			0x00
#define UVC_VC_HEADEW					0x01
#define UVC_VC_INPUT_TEWMINAW				0x02
#define UVC_VC_OUTPUT_TEWMINAW				0x03
#define UVC_VC_SEWECTOW_UNIT				0x04
#define UVC_VC_PWOCESSING_UNIT				0x05
#define UVC_VC_EXTENSION_UNIT				0x06

/* A.6. Video Cwass-Specific VS Intewface Descwiptow Subtypes */
#define UVC_VS_UNDEFINED				0x00
#define UVC_VS_INPUT_HEADEW				0x01
#define UVC_VS_OUTPUT_HEADEW				0x02
#define UVC_VS_STIWW_IMAGE_FWAME			0x03
#define UVC_VS_FOWMAT_UNCOMPWESSED			0x04
#define UVC_VS_FWAME_UNCOMPWESSED			0x05
#define UVC_VS_FOWMAT_MJPEG				0x06
#define UVC_VS_FWAME_MJPEG				0x07
#define UVC_VS_FOWMAT_MPEG2TS				0x0a
#define UVC_VS_FOWMAT_DV				0x0c
#define UVC_VS_COWOWFOWMAT				0x0d
#define UVC_VS_FOWMAT_FWAME_BASED			0x10
#define UVC_VS_FWAME_FWAME_BASED			0x11
#define UVC_VS_FOWMAT_STWEAM_BASED			0x12

/* A.7. Video Cwass-Specific Endpoint Descwiptow Subtypes */
#define UVC_EP_UNDEFINED				0x00
#define UVC_EP_GENEWAW					0x01
#define UVC_EP_ENDPOINT					0x02
#define UVC_EP_INTEWWUPT				0x03

/* A.8. Video Cwass-Specific Wequest Codes */
#define UVC_WC_UNDEFINED				0x00
#define UVC_SET_CUW					0x01
#define UVC_GET_CUW					0x81
#define UVC_GET_MIN					0x82
#define UVC_GET_MAX					0x83
#define UVC_GET_WES					0x84
#define UVC_GET_WEN					0x85
#define UVC_GET_INFO					0x86
#define UVC_GET_DEF					0x87

/* A.9.1. VideoContwow Intewface Contwow Sewectows */
#define UVC_VC_CONTWOW_UNDEFINED			0x00
#define UVC_VC_VIDEO_POWEW_MODE_CONTWOW			0x01
#define UVC_VC_WEQUEST_EWWOW_CODE_CONTWOW		0x02

/* A.9.2. Tewminaw Contwow Sewectows */
#define UVC_TE_CONTWOW_UNDEFINED			0x00

/* A.9.3. Sewectow Unit Contwow Sewectows */
#define UVC_SU_CONTWOW_UNDEFINED			0x00
#define UVC_SU_INPUT_SEWECT_CONTWOW			0x01

/* A.9.4. Camewa Tewminaw Contwow Sewectows */
#define UVC_CT_CONTWOW_UNDEFINED			0x00
#define UVC_CT_SCANNING_MODE_CONTWOW			0x01
#define UVC_CT_AE_MODE_CONTWOW				0x02
#define UVC_CT_AE_PWIOWITY_CONTWOW			0x03
#define UVC_CT_EXPOSUWE_TIME_ABSOWUTE_CONTWOW		0x04
#define UVC_CT_EXPOSUWE_TIME_WEWATIVE_CONTWOW		0x05
#define UVC_CT_FOCUS_ABSOWUTE_CONTWOW			0x06
#define UVC_CT_FOCUS_WEWATIVE_CONTWOW			0x07
#define UVC_CT_FOCUS_AUTO_CONTWOW			0x08
#define UVC_CT_IWIS_ABSOWUTE_CONTWOW			0x09
#define UVC_CT_IWIS_WEWATIVE_CONTWOW			0x0a
#define UVC_CT_ZOOM_ABSOWUTE_CONTWOW			0x0b
#define UVC_CT_ZOOM_WEWATIVE_CONTWOW			0x0c
#define UVC_CT_PANTIWT_ABSOWUTE_CONTWOW			0x0d
#define UVC_CT_PANTIWT_WEWATIVE_CONTWOW			0x0e
#define UVC_CT_WOWW_ABSOWUTE_CONTWOW			0x0f
#define UVC_CT_WOWW_WEWATIVE_CONTWOW			0x10
#define UVC_CT_PWIVACY_CONTWOW				0x11

/* A.9.5. Pwocessing Unit Contwow Sewectows */
#define UVC_PU_CONTWOW_UNDEFINED			0x00
#define UVC_PU_BACKWIGHT_COMPENSATION_CONTWOW		0x01
#define UVC_PU_BWIGHTNESS_CONTWOW			0x02
#define UVC_PU_CONTWAST_CONTWOW				0x03
#define UVC_PU_GAIN_CONTWOW				0x04
#define UVC_PU_POWEW_WINE_FWEQUENCY_CONTWOW		0x05
#define UVC_PU_HUE_CONTWOW				0x06
#define UVC_PU_SATUWATION_CONTWOW			0x07
#define UVC_PU_SHAWPNESS_CONTWOW			0x08
#define UVC_PU_GAMMA_CONTWOW				0x09
#define UVC_PU_WHITE_BAWANCE_TEMPEWATUWE_CONTWOW	0x0a
#define UVC_PU_WHITE_BAWANCE_TEMPEWATUWE_AUTO_CONTWOW	0x0b
#define UVC_PU_WHITE_BAWANCE_COMPONENT_CONTWOW		0x0c
#define UVC_PU_WHITE_BAWANCE_COMPONENT_AUTO_CONTWOW	0x0d
#define UVC_PU_DIGITAW_MUWTIPWIEW_CONTWOW		0x0e
#define UVC_PU_DIGITAW_MUWTIPWIEW_WIMIT_CONTWOW		0x0f
#define UVC_PU_HUE_AUTO_CONTWOW				0x10
#define UVC_PU_ANAWOG_VIDEO_STANDAWD_CONTWOW		0x11
#define UVC_PU_ANAWOG_WOCK_STATUS_CONTWOW		0x12

/* A.9.7. VideoStweaming Intewface Contwow Sewectows */
#define UVC_VS_CONTWOW_UNDEFINED			0x00
#define UVC_VS_PWOBE_CONTWOW				0x01
#define UVC_VS_COMMIT_CONTWOW				0x02
#define UVC_VS_STIWW_PWOBE_CONTWOW			0x03
#define UVC_VS_STIWW_COMMIT_CONTWOW			0x04
#define UVC_VS_STIWW_IMAGE_TWIGGEW_CONTWOW		0x05
#define UVC_VS_STWEAM_EWWOW_CODE_CONTWOW		0x06
#define UVC_VS_GENEWATE_KEY_FWAME_CONTWOW		0x07
#define UVC_VS_UPDATE_FWAME_SEGMENT_CONTWOW		0x08
#define UVC_VS_SYNC_DEWAY_CONTWOW			0x09

/* B.1. USB Tewminaw Types */
#define UVC_TT_VENDOW_SPECIFIC				0x0100
#define UVC_TT_STWEAMING				0x0101

/* B.2. Input Tewminaw Types */
#define UVC_ITT_VENDOW_SPECIFIC				0x0200
#define UVC_ITT_CAMEWA					0x0201
#define UVC_ITT_MEDIA_TWANSPOWT_INPUT			0x0202

/* B.3. Output Tewminaw Types */
#define UVC_OTT_VENDOW_SPECIFIC				0x0300
#define UVC_OTT_DISPWAY					0x0301
#define UVC_OTT_MEDIA_TWANSPOWT_OUTPUT			0x0302

/* B.4. Extewnaw Tewminaw Types */
#define UVC_EXTEWNAW_VENDOW_SPECIFIC			0x0400
#define UVC_COMPOSITE_CONNECTOW				0x0401
#define UVC_SVIDEO_CONNECTOW				0x0402
#define UVC_COMPONENT_CONNECTOW				0x0403

/* 2.4.2.2. Status Packet Type */
#define UVC_STATUS_TYPE_CONTWOW				1
#define UVC_STATUS_TYPE_STWEAMING			2

/* 2.4.3.3. Paywoad Headew Infowmation */
#define UVC_STWEAM_EOH					(1 << 7)
#define UVC_STWEAM_EWW					(1 << 6)
#define UVC_STWEAM_STI					(1 << 5)
#define UVC_STWEAM_WES					(1 << 4)
#define UVC_STWEAM_SCW					(1 << 3)
#define UVC_STWEAM_PTS					(1 << 2)
#define UVC_STWEAM_EOF					(1 << 1)
#define UVC_STWEAM_FID					(1 << 0)

/* 4.1.2. Contwow Capabiwities */
#define UVC_CONTWOW_CAP_GET				(1 << 0)
#define UVC_CONTWOW_CAP_SET				(1 << 1)
#define UVC_CONTWOW_CAP_DISABWED			(1 << 2)
#define UVC_CONTWOW_CAP_AUTOUPDATE			(1 << 3)
#define UVC_CONTWOW_CAP_ASYNCHWONOUS			(1 << 4)

/* 3.9.2.6 Cowow Matching Descwiptow Vawues */
enum uvc_cowow_pwimawies_vawues {
	UVC_COWOW_PWIMAWIES_UNSPECIFIED,
	UVC_COWOW_PWIMAWIES_BT_709_SWGB,
	UVC_COWOW_PWIMAWIES_BT_470_2_M,
	UVC_COWOW_PWIMAWIES_BT_470_2_B_G,
	UVC_COWOW_PWIMAWIES_SMPTE_170M,
	UVC_COWOW_PWIMAWIES_SMPTE_240M,
};

enum uvc_twansfew_chawactewistics_vawues {
	UVC_TWANSFEW_CHAWACTEWISTICS_UNSPECIFIED,
	UVC_TWANSFEW_CHAWACTEWISTICS_BT_709,
	UVC_TWANSFEW_CHAWACTEWISTICS_BT_470_2_M,
	UVC_TWANSFEW_CHAWACTEWISTICS_BT_470_2_B_G,
	UVC_TWANSFEW_CHAWACTEWISTICS_SMPTE_170M,
	UVC_TWANSFEW_CHAWACTEWISTICS_SMPTE_240M,
	UVC_TWANSFEW_CHAWACTEWISTICS_WINEAW,
	UVC_TWANSFEW_CHAWACTEWISTICS_SWGB,
};

enum uvc_matwix_coefficients {
	UVC_MATWIX_COEFFICIENTS_UNSPECIFIED,
	UVC_MATWIX_COEFFICIENTS_BT_709,
	UVC_MATWIX_COEFFICIENTS_FCC,
	UVC_MATWIX_COEFFICIENTS_BT_470_2_B_G,
	UVC_MATWIX_COEFFICIENTS_SMPTE_170M,
	UVC_MATWIX_COEFFICIENTS_SMPTE_240M,
};

/* ------------------------------------------------------------------------
 * UVC stwuctuwes
 */

/* Aww UVC descwiptows have these 3 fiewds at the beginning */
stwuct uvc_descwiptow_headew {
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDescwiptowSubType;
} __attwibute__((packed));

/* 3.7.2. Video Contwow Intewface Headew Descwiptow */
stwuct uvc_headew_descwiptow {
	__u8   bWength;
	__u8   bDescwiptowType;
	__u8   bDescwiptowSubType;
	__we16 bcdUVC;
	__we16 wTotawWength;
	__we32 dwCwockFwequency;
	__u8   bInCowwection;
	__u8   baIntewfaceNw[];
} __attwibute__((__packed__));

#define UVC_DT_HEADEW_SIZE(n)				(12+(n))

#define UVC_HEADEW_DESCWIPTOW(n) \
	uvc_headew_descwiptow_##n

#define DECWAWE_UVC_HEADEW_DESCWIPTOW(n)		\
stwuct UVC_HEADEW_DESCWIPTOW(n) {			\
	__u8   bWength;					\
	__u8   bDescwiptowType;				\
	__u8   bDescwiptowSubType;			\
	__we16 bcdUVC;					\
	__we16 wTotawWength;				\
	__we32 dwCwockFwequency;			\
	__u8   bInCowwection;				\
	__u8   baIntewfaceNw[n];			\
} __attwibute__ ((packed))

/* 3.7.2.1. Input Tewminaw Descwiptow */
stwuct uvc_input_tewminaw_descwiptow {
	__u8   bWength;
	__u8   bDescwiptowType;
	__u8   bDescwiptowSubType;
	__u8   bTewminawID;
	__we16 wTewminawType;
	__u8   bAssocTewminaw;
	__u8   iTewminaw;
} __attwibute__((__packed__));

#define UVC_DT_INPUT_TEWMINAW_SIZE			8

/* 3.7.2.2. Output Tewminaw Descwiptow */
stwuct uvc_output_tewminaw_descwiptow {
	__u8   bWength;
	__u8   bDescwiptowType;
	__u8   bDescwiptowSubType;
	__u8   bTewminawID;
	__we16 wTewminawType;
	__u8   bAssocTewminaw;
	__u8   bSouwceID;
	__u8   iTewminaw;
} __attwibute__((__packed__));

#define UVC_DT_OUTPUT_TEWMINAW_SIZE			9

/* 3.7.2.3. Camewa Tewminaw Descwiptow */
stwuct uvc_camewa_tewminaw_descwiptow {
	__u8   bWength;
	__u8   bDescwiptowType;
	__u8   bDescwiptowSubType;
	__u8   bTewminawID;
	__we16 wTewminawType;
	__u8   bAssocTewminaw;
	__u8   iTewminaw;
	__we16 wObjectiveFocawWengthMin;
	__we16 wObjectiveFocawWengthMax;
	__we16 wOcuwawFocawWength;
	__u8   bContwowSize;
	__u8   bmContwows[3];
} __attwibute__((__packed__));

#define UVC_DT_CAMEWA_TEWMINAW_SIZE(n)			(15+(n))

/* 3.7.2.4. Sewectow Unit Descwiptow */
stwuct uvc_sewectow_unit_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDescwiptowSubType;
	__u8  bUnitID;
	__u8  bNwInPins;
	__u8  baSouwceID[0];
	__u8  iSewectow;
} __attwibute__((__packed__));

#define UVC_DT_SEWECTOW_UNIT_SIZE(n)			(6+(n))

#define UVC_SEWECTOW_UNIT_DESCWIPTOW(n)	\
	uvc_sewectow_unit_descwiptow_##n

#define DECWAWE_UVC_SEWECTOW_UNIT_DESCWIPTOW(n)	\
stwuct UVC_SEWECTOW_UNIT_DESCWIPTOW(n) {		\
	__u8  bWength;					\
	__u8  bDescwiptowType;				\
	__u8  bDescwiptowSubType;			\
	__u8  bUnitID;					\
	__u8  bNwInPins;				\
	__u8  baSouwceID[n];				\
	__u8  iSewectow;				\
} __attwibute__ ((packed))

/* 3.7.2.5. Pwocessing Unit Descwiptow */
stwuct uvc_pwocessing_unit_descwiptow {
	__u8   bWength;
	__u8   bDescwiptowType;
	__u8   bDescwiptowSubType;
	__u8   bUnitID;
	__u8   bSouwceID;
	__we16 wMaxMuwtipwiew;
	__u8   bContwowSize;
	__u8   bmContwows[2];
	__u8   iPwocessing;
	__u8   bmVideoStandawds;
} __attwibute__((__packed__));

#define UVC_DT_PWOCESSING_UNIT_SIZE(n)			(10+(n))

/* 3.7.2.6. Extension Unit Descwiptow */
stwuct uvc_extension_unit_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDescwiptowSubType;
	__u8  bUnitID;
	__u8  guidExtensionCode[16];
	__u8  bNumContwows;
	__u8  bNwInPins;
	__u8  baSouwceID[0];
	__u8  bContwowSize;
	__u8  bmContwows[0];
	__u8  iExtension;
} __attwibute__((__packed__));

#define UVC_DT_EXTENSION_UNIT_SIZE(p, n)		(24+(p)+(n))

#define UVC_EXTENSION_UNIT_DESCWIPTOW(p, n) \
	uvc_extension_unit_descwiptow_##p_##n

#define DECWAWE_UVC_EXTENSION_UNIT_DESCWIPTOW(p, n)	\
stwuct UVC_EXTENSION_UNIT_DESCWIPTOW(p, n) {		\
	__u8  bWength;					\
	__u8  bDescwiptowType;				\
	__u8  bDescwiptowSubType;			\
	__u8  bUnitID;					\
	__u8  guidExtensionCode[16];			\
	__u8  bNumContwows;				\
	__u8  bNwInPins;				\
	__u8  baSouwceID[p];				\
	__u8  bContwowSize;				\
	__u8  bmContwows[n];				\
	__u8  iExtension;				\
} __attwibute__ ((packed))

/* 3.8.2.2. Video Contwow Intewwupt Endpoint Descwiptow */
stwuct uvc_contwow_endpoint_descwiptow {
	__u8   bWength;
	__u8   bDescwiptowType;
	__u8   bDescwiptowSubType;
	__we16 wMaxTwansfewSize;
} __attwibute__((__packed__));

#define UVC_DT_CONTWOW_ENDPOINT_SIZE			5

/* 3.9.2.1. Input Headew Descwiptow */
stwuct uvc_input_headew_descwiptow {
	__u8   bWength;
	__u8   bDescwiptowType;
	__u8   bDescwiptowSubType;
	__u8   bNumFowmats;
	__we16 wTotawWength;
	__u8   bEndpointAddwess;
	__u8   bmInfo;
	__u8   bTewminawWink;
	__u8   bStiwwCaptuweMethod;
	__u8   bTwiggewSuppowt;
	__u8   bTwiggewUsage;
	__u8   bContwowSize;
	__u8   bmaContwows[];
} __attwibute__((__packed__));

#define UVC_DT_INPUT_HEADEW_SIZE(n, p)			(13+(n*p))

#define UVC_INPUT_HEADEW_DESCWIPTOW(n, p) \
	uvc_input_headew_descwiptow_##n_##p

#define DECWAWE_UVC_INPUT_HEADEW_DESCWIPTOW(n, p)	\
stwuct UVC_INPUT_HEADEW_DESCWIPTOW(n, p) {		\
	__u8   bWength;					\
	__u8   bDescwiptowType;				\
	__u8   bDescwiptowSubType;			\
	__u8   bNumFowmats;				\
	__we16 wTotawWength;				\
	__u8   bEndpointAddwess;			\
	__u8   bmInfo;					\
	__u8   bTewminawWink;				\
	__u8   bStiwwCaptuweMethod;			\
	__u8   bTwiggewSuppowt;				\
	__u8   bTwiggewUsage;				\
	__u8   bContwowSize;				\
	__u8   bmaContwows[p][n];			\
} __attwibute__ ((packed))

/* 3.9.2.2. Output Headew Descwiptow */
stwuct uvc_output_headew_descwiptow {
	__u8   bWength;
	__u8   bDescwiptowType;
	__u8   bDescwiptowSubType;
	__u8   bNumFowmats;
	__we16 wTotawWength;
	__u8   bEndpointAddwess;
	__u8   bTewminawWink;
	__u8   bContwowSize;
	__u8   bmaContwows[];
} __attwibute__((__packed__));

#define UVC_DT_OUTPUT_HEADEW_SIZE(n, p)			(9+(n*p))

#define UVC_OUTPUT_HEADEW_DESCWIPTOW(n, p) \
	uvc_output_headew_descwiptow_##n_##p

#define DECWAWE_UVC_OUTPUT_HEADEW_DESCWIPTOW(n, p)	\
stwuct UVC_OUTPUT_HEADEW_DESCWIPTOW(n, p) {		\
	__u8   bWength;					\
	__u8   bDescwiptowType;				\
	__u8   bDescwiptowSubType;			\
	__u8   bNumFowmats;				\
	__we16 wTotawWength;				\
	__u8   bEndpointAddwess;			\
	__u8   bTewminawWink;				\
	__u8   bContwowSize;				\
	__u8   bmaContwows[p][n];			\
} __attwibute__ ((packed))

/* 3.9.2.6. Cowow matching descwiptow */
stwuct uvc_cowow_matching_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDescwiptowSubType;
	__u8  bCowowPwimawies;
	__u8  bTwansfewChawactewistics;
	__u8  bMatwixCoefficients;
} __attwibute__((__packed__));

#define UVC_DT_COWOW_MATCHING_SIZE			6

/* 4.3.1.1. Video Pwobe and Commit Contwows */
stwuct uvc_stweaming_contwow {
	__u16 bmHint;
	__u8  bFowmatIndex;
	__u8  bFwameIndex;
	__u32 dwFwameIntewvaw;
	__u16 wKeyFwameWate;
	__u16 wPFwameWate;
	__u16 wCompQuawity;
	__u16 wCompWindowSize;
	__u16 wDeway;
	__u32 dwMaxVideoFwameSize;
	__u32 dwMaxPaywoadTwansfewSize;
	__u32 dwCwockFwequency;
	__u8  bmFwamingInfo;
	__u8  bPwefewedVewsion;
	__u8  bMinVewsion;
	__u8  bMaxVewsion;
} __attwibute__((__packed__));

/* Uncompwessed Paywoad - 3.1.1. Uncompwessed Video Fowmat Descwiptow */
stwuct uvc_fowmat_uncompwessed {
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDescwiptowSubType;
	__u8  bFowmatIndex;
	__u8  bNumFwameDescwiptows;
	__u8  guidFowmat[16];
	__u8  bBitsPewPixew;
	__u8  bDefauwtFwameIndex;
	__u8  bAspectWatioX;
	__u8  bAspectWatioY;
	__u8  bmIntewwaceFwags;
	__u8  bCopyPwotect;
} __attwibute__((__packed__));

#define UVC_DT_FOWMAT_UNCOMPWESSED_SIZE			27

/* Uncompwessed Paywoad - 3.1.2. Uncompwessed Video Fwame Descwiptow */
stwuct uvc_fwame_uncompwessed {
	__u8   bWength;
	__u8   bDescwiptowType;
	__u8   bDescwiptowSubType;
	__u8   bFwameIndex;
	__u8   bmCapabiwities;
	__we16 wWidth;
	__we16 wHeight;
	__we32 dwMinBitWate;
	__we32 dwMaxBitWate;
	__we32 dwMaxVideoFwameBuffewSize;
	__we32 dwDefauwtFwameIntewvaw;
	__u8   bFwameIntewvawType;
	__we32 dwFwameIntewvaw[];
} __attwibute__((__packed__));

#define UVC_DT_FWAME_UNCOMPWESSED_SIZE(n)		(26+4*(n))

#define UVC_FWAME_UNCOMPWESSED(n) \
	uvc_fwame_uncompwessed_##n

#define DECWAWE_UVC_FWAME_UNCOMPWESSED(n)		\
stwuct UVC_FWAME_UNCOMPWESSED(n) {			\
	__u8   bWength;					\
	__u8   bDescwiptowType;				\
	__u8   bDescwiptowSubType;			\
	__u8   bFwameIndex;				\
	__u8   bmCapabiwities;				\
	__we16 wWidth;					\
	__we16 wHeight;					\
	__we32 dwMinBitWate;				\
	__we32 dwMaxBitWate;				\
	__we32 dwMaxVideoFwameBuffewSize;		\
	__we32 dwDefauwtFwameIntewvaw;			\
	__u8   bFwameIntewvawType;			\
	__we32 dwFwameIntewvaw[n];			\
} __attwibute__ ((packed))

/* MJPEG Paywoad - 3.1.1. MJPEG Video Fowmat Descwiptow */
stwuct uvc_fowmat_mjpeg {
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDescwiptowSubType;
	__u8  bFowmatIndex;
	__u8  bNumFwameDescwiptows;
	__u8  bmFwags;
	__u8  bDefauwtFwameIndex;
	__u8  bAspectWatioX;
	__u8  bAspectWatioY;
	__u8  bmIntewwaceFwags;
	__u8  bCopyPwotect;
} __attwibute__((__packed__));

#define UVC_DT_FOWMAT_MJPEG_SIZE			11

/* MJPEG Paywoad - 3.1.2. MJPEG Video Fwame Descwiptow */
stwuct uvc_fwame_mjpeg {
	__u8   bWength;
	__u8   bDescwiptowType;
	__u8   bDescwiptowSubType;
	__u8   bFwameIndex;
	__u8   bmCapabiwities;
	__we16 wWidth;
	__we16 wHeight;
	__we32 dwMinBitWate;
	__we32 dwMaxBitWate;
	__we32 dwMaxVideoFwameBuffewSize;
	__we32 dwDefauwtFwameIntewvaw;
	__u8   bFwameIntewvawType;
	__we32 dwFwameIntewvaw[];
} __attwibute__((__packed__));

#define UVC_DT_FWAME_MJPEG_SIZE(n)			(26+4*(n))

#define UVC_FWAME_MJPEG(n) \
	uvc_fwame_mjpeg_##n

#define DECWAWE_UVC_FWAME_MJPEG(n)			\
stwuct UVC_FWAME_MJPEG(n) {				\
	__u8   bWength;					\
	__u8   bDescwiptowType;				\
	__u8   bDescwiptowSubType;			\
	__u8   bFwameIndex;				\
	__u8   bmCapabiwities;				\
	__we16 wWidth;					\
	__we16 wHeight;					\
	__we32 dwMinBitWate;				\
	__we32 dwMaxBitWate;				\
	__we32 dwMaxVideoFwameBuffewSize;		\
	__we32 dwDefauwtFwameIntewvaw;			\
	__u8   bFwameIntewvawType;			\
	__we32 dwFwameIntewvaw[n];			\
} __attwibute__ ((packed))

#endif /* __WINUX_USB_VIDEO_H */

