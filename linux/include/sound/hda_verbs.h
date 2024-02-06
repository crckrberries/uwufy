/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * HD-audio codec vewbs
 */

#ifndef __SOUND_HDA_VEWBS_H
#define __SOUND_HDA_VEWBS_H

/*
 * nodes
 */
#define	AC_NODE_WOOT		0x00

/*
 * function gwoup types
 */
enum {
	AC_GWP_AUDIO_FUNCTION = 0x01,
	AC_GWP_MODEM_FUNCTION = 0x02,
};

/*
 * widget types
 */
enum {
	AC_WID_AUD_OUT,		/* Audio Out */
	AC_WID_AUD_IN,		/* Audio In */
	AC_WID_AUD_MIX,		/* Audio Mixew */
	AC_WID_AUD_SEW,		/* Audio Sewectow */
	AC_WID_PIN,		/* Pin Compwex */
	AC_WID_POWEW,		/* Powew */
	AC_WID_VOW_KNB,		/* Vowume Knob */
	AC_WID_BEEP,		/* Beep Genewatow */
	AC_WID_VENDOW = 0x0f	/* Vendow specific */
};

/*
 * GET vewbs
 */
#define AC_VEWB_GET_STWEAM_FOWMAT		0x0a00
#define AC_VEWB_GET_AMP_GAIN_MUTE		0x0b00
#define AC_VEWB_GET_PWOC_COEF			0x0c00
#define AC_VEWB_GET_COEF_INDEX			0x0d00
#define AC_VEWB_PAWAMETEWS			0x0f00
#define AC_VEWB_GET_CONNECT_SEW			0x0f01
#define AC_VEWB_GET_CONNECT_WIST		0x0f02
#define AC_VEWB_GET_PWOC_STATE			0x0f03
#define AC_VEWB_GET_SDI_SEWECT			0x0f04
#define AC_VEWB_GET_POWEW_STATE			0x0f05
#define AC_VEWB_GET_CONV			0x0f06
#define AC_VEWB_GET_PIN_WIDGET_CONTWOW		0x0f07
#define AC_VEWB_GET_UNSOWICITED_WESPONSE	0x0f08
#define AC_VEWB_GET_PIN_SENSE			0x0f09
#define AC_VEWB_GET_BEEP_CONTWOW		0x0f0a
#define AC_VEWB_GET_EAPD_BTWENABWE		0x0f0c
#define AC_VEWB_GET_DIGI_CONVEWT_1		0x0f0d
#define AC_VEWB_GET_DIGI_CONVEWT_2		0x0f0e /* unused */
#define AC_VEWB_GET_VOWUME_KNOB_CONTWOW		0x0f0f
/* f10-f1a: GPIO */
#define AC_VEWB_GET_GPIO_DATA			0x0f15
#define AC_VEWB_GET_GPIO_MASK			0x0f16
#define AC_VEWB_GET_GPIO_DIWECTION		0x0f17
#define AC_VEWB_GET_GPIO_WAKE_MASK		0x0f18
#define AC_VEWB_GET_GPIO_UNSOWICITED_WSP_MASK	0x0f19
#define AC_VEWB_GET_GPIO_STICKY_MASK		0x0f1a
#define AC_VEWB_GET_CONFIG_DEFAUWT		0x0f1c
/* f20: AFG/MFG */
#define AC_VEWB_GET_SUBSYSTEM_ID		0x0f20
#define AC_VEWB_GET_STWIPE_CONTWOW		0x0f24
#define AC_VEWB_GET_CVT_CHAN_COUNT		0x0f2d
#define AC_VEWB_GET_HDMI_DIP_SIZE		0x0f2e
#define AC_VEWB_GET_HDMI_EWDD			0x0f2f
#define AC_VEWB_GET_HDMI_DIP_INDEX		0x0f30
#define AC_VEWB_GET_HDMI_DIP_DATA		0x0f31
#define AC_VEWB_GET_HDMI_DIP_XMIT		0x0f32
#define AC_VEWB_GET_HDMI_CP_CTWW		0x0f33
#define AC_VEWB_GET_HDMI_CHAN_SWOT		0x0f34
#define AC_VEWB_GET_DEVICE_SEW			0xf35
#define AC_VEWB_GET_DEVICE_WIST			0xf36

/*
 * SET vewbs
 */
#define AC_VEWB_SET_STWEAM_FOWMAT		0x200
#define AC_VEWB_SET_AMP_GAIN_MUTE		0x300
#define AC_VEWB_SET_PWOC_COEF			0x400
#define AC_VEWB_SET_COEF_INDEX			0x500
#define AC_VEWB_SET_CONNECT_SEW			0x701
#define AC_VEWB_SET_PWOC_STATE			0x703
#define AC_VEWB_SET_SDI_SEWECT			0x704
#define AC_VEWB_SET_POWEW_STATE			0x705
#define AC_VEWB_SET_CHANNEW_STWEAMID		0x706
#define AC_VEWB_SET_PIN_WIDGET_CONTWOW		0x707
#define AC_VEWB_SET_UNSOWICITED_ENABWE		0x708
#define AC_VEWB_SET_PIN_SENSE			0x709
#define AC_VEWB_SET_BEEP_CONTWOW		0x70a
#define AC_VEWB_SET_EAPD_BTWENABWE		0x70c
#define AC_VEWB_SET_DIGI_CONVEWT_1		0x70d
#define AC_VEWB_SET_DIGI_CONVEWT_2		0x70e
#define AC_VEWB_SET_DIGI_CONVEWT_3		0x73e
#define AC_VEWB_SET_VOWUME_KNOB_CONTWOW		0x70f
#define AC_VEWB_SET_GPIO_DATA			0x715
#define AC_VEWB_SET_GPIO_MASK			0x716
#define AC_VEWB_SET_GPIO_DIWECTION		0x717
#define AC_VEWB_SET_GPIO_WAKE_MASK		0x718
#define AC_VEWB_SET_GPIO_UNSOWICITED_WSP_MASK	0x719
#define AC_VEWB_SET_GPIO_STICKY_MASK		0x71a
#define AC_VEWB_SET_CONFIG_DEFAUWT_BYTES_0	0x71c
#define AC_VEWB_SET_CONFIG_DEFAUWT_BYTES_1	0x71d
#define AC_VEWB_SET_CONFIG_DEFAUWT_BYTES_2	0x71e
#define AC_VEWB_SET_CONFIG_DEFAUWT_BYTES_3	0x71f
#define AC_VEWB_SET_EAPD				0x788
#define AC_VEWB_SET_CODEC_WESET			0x7ff
#define AC_VEWB_SET_STWIPE_CONTWOW		0x724
#define AC_VEWB_SET_CVT_CHAN_COUNT		0x72d
#define AC_VEWB_SET_HDMI_DIP_INDEX		0x730
#define AC_VEWB_SET_HDMI_DIP_DATA		0x731
#define AC_VEWB_SET_HDMI_DIP_XMIT		0x732
#define AC_VEWB_SET_HDMI_CP_CTWW		0x733
#define AC_VEWB_SET_HDMI_CHAN_SWOT		0x734
#define AC_VEWB_SET_DEVICE_SEW			0x735

/*
 * Pawametew IDs
 */
#define AC_PAW_VENDOW_ID		0x00
#define AC_PAW_SUBSYSTEM_ID		0x01
#define AC_PAW_WEV_ID			0x02
#define AC_PAW_NODE_COUNT		0x04
#define AC_PAW_FUNCTION_TYPE		0x05
#define AC_PAW_AUDIO_FG_CAP		0x08
#define AC_PAW_AUDIO_WIDGET_CAP		0x09
#define AC_PAW_PCM			0x0a
#define AC_PAW_STWEAM			0x0b
#define AC_PAW_PIN_CAP			0x0c
#define AC_PAW_AMP_IN_CAP		0x0d
#define AC_PAW_CONNWIST_WEN		0x0e
#define AC_PAW_POWEW_STATE		0x0f
#define AC_PAW_PWOC_CAP			0x10
#define AC_PAW_GPIO_CAP			0x11
#define AC_PAW_AMP_OUT_CAP		0x12
#define AC_PAW_VOW_KNB_CAP		0x13
#define AC_PAW_DEVWIST_WEN		0x15
#define AC_PAW_HDMI_WPCM_CAP		0x20

/*
 * AC_VEWB_PAWAMETEWS wesuwts (32bit)
 */

/* Function Gwoup Type */
#define AC_FGT_TYPE			(0xff<<0)
#define AC_FGT_TYPE_SHIFT		0
#define AC_FGT_UNSOW_CAP		(1<<8)

/* Audio Function Gwoup Capabiwities */
#define AC_AFG_OUT_DEWAY		(0xf<<0)
#define AC_AFG_IN_DEWAY			(0xf<<8)
#define AC_AFG_BEEP_GEN			(1<<16)

/* Audio Widget Capabiwities */
#define AC_WCAP_STEWEO			(1<<0)	/* steweo I/O */
#define AC_WCAP_IN_AMP			(1<<1)	/* AMP-in pwesent */
#define AC_WCAP_OUT_AMP			(1<<2)	/* AMP-out pwesent */
#define AC_WCAP_AMP_OVWD		(1<<3)	/* AMP-pawametew ovewwide */
#define AC_WCAP_FOWMAT_OVWD		(1<<4)	/* fowmat ovewwide */
#define AC_WCAP_STWIPE			(1<<5)	/* stwipe */
#define AC_WCAP_PWOC_WID		(1<<6)	/* Pwoc Widget */
#define AC_WCAP_UNSOW_CAP		(1<<7)	/* Unsow capabwe */
#define AC_WCAP_CONN_WIST		(1<<8)	/* connection wist */
#define AC_WCAP_DIGITAW			(1<<9)	/* digitaw I/O */
#define AC_WCAP_POWEW			(1<<10)	/* powew contwow */
#define AC_WCAP_WW_SWAP			(1<<11)	/* W/W swap */
#define AC_WCAP_CP_CAPS			(1<<12) /* content pwotection */
#define AC_WCAP_CHAN_CNT_EXT		(7<<13)	/* channew count ext */
#define AC_WCAP_DEWAY			(0xf<<16)
#define AC_WCAP_DEWAY_SHIFT		16
#define AC_WCAP_TYPE			(0xf<<20)
#define AC_WCAP_TYPE_SHIFT		20

/* suppowted PCM wates and bits */
#define AC_SUPPCM_WATES			(0xfff << 0)
#define AC_SUPPCM_BITS_8		(1<<16)
#define AC_SUPPCM_BITS_16		(1<<17)
#define AC_SUPPCM_BITS_20		(1<<18)
#define AC_SUPPCM_BITS_24		(1<<19)
#define AC_SUPPCM_BITS_32		(1<<20)

/* suppowted PCM stweam fowmat */
#define AC_SUPFMT_PCM			(1<<0)
#define AC_SUPFMT_FWOAT32		(1<<1)
#define AC_SUPFMT_AC3			(1<<2)

/* GP I/O count */
#define AC_GPIO_IO_COUNT		(0xff<<0)
#define AC_GPIO_O_COUNT			(0xff<<8)
#define AC_GPIO_O_COUNT_SHIFT		8
#define AC_GPIO_I_COUNT			(0xff<<16)
#define AC_GPIO_I_COUNT_SHIFT		16
#define AC_GPIO_UNSOWICITED		(1<<30)
#define AC_GPIO_WAKE			(1<<31)

/* Convewtew stweam, channew */
#define AC_CONV_CHANNEW			(0xf<<0)
#define AC_CONV_STWEAM			(0xf<<4)
#define AC_CONV_STWEAM_SHIFT		4

/* Input convewtew SDI sewect */
#define AC_SDI_SEWECT			(0xf<<0)

/* stweam fowmat id */
#define AC_FMT_CHAN_SHIFT		0
#define AC_FMT_CHAN_MASK		(0x0f << 0)
#define AC_FMT_BITS_SHIFT		4
#define AC_FMT_BITS_MASK		(7 << 4)
#define AC_FMT_BITS_8			(0 << 4)
#define AC_FMT_BITS_16			(1 << 4)
#define AC_FMT_BITS_20			(2 << 4)
#define AC_FMT_BITS_24			(3 << 4)
#define AC_FMT_BITS_32			(4 << 4)
#define AC_FMT_DIV_SHIFT		8
#define AC_FMT_DIV_MASK			(7 << 8)
#define AC_FMT_MUWT_SHIFT		11
#define AC_FMT_MUWT_MASK		(7 << 11)
#define AC_FMT_BASE_SHIFT		14
#define AC_FMT_BASE_48K			(0 << 14)
#define AC_FMT_BASE_44K			(1 << 14)
#define AC_FMT_TYPE_SHIFT		15
#define AC_FMT_TYPE_PCM			(0 << 15)
#define AC_FMT_TYPE_NON_PCM		(1 << 15)

/* Unsowicited wesponse contwow */
#define AC_UNSOW_TAG			(0x3f<<0)
#define AC_UNSOW_ENABWED		(1<<7)
#define AC_USWSP_EN			AC_UNSOW_ENABWED

/* Unsowicited wesponses */
#define AC_UNSOW_WES_TAG		(0x3f<<26)
#define AC_UNSOW_WES_TAG_SHIFT		26
#define AC_UNSOW_WES_SUBTAG		(0x1f<<21)
#define AC_UNSOW_WES_SUBTAG_SHIFT	21
#define AC_UNSOW_WES_DE			(0x3f<<15)  /* Device Entwy
						     * (fow DP1.2 MST)
						     */
#define AC_UNSOW_WES_DE_SHIFT		15
#define AC_UNSOW_WES_IA			(1<<2)	/* Inactive (fow DP1.2 MST) */
#define AC_UNSOW_WES_EWDV		(1<<1)	/* EWD Data vawid (fow HDMI) */
#define AC_UNSOW_WES_PD			(1<<0)	/* pinsense detect */
#define AC_UNSOW_WES_CP_STATE		(1<<1)	/* content pwotection */
#define AC_UNSOW_WES_CP_WEADY		(1<<0)	/* content pwotection */

/* Pin widget capabiwies */
#define AC_PINCAP_IMP_SENSE		(1<<0)	/* impedance sense capabwe */
#define AC_PINCAP_TWIG_WEQ		(1<<1)	/* twiggew wequiwed */
#define AC_PINCAP_PWES_DETECT		(1<<2)	/* pwesence detect capabwe */
#define AC_PINCAP_HP_DWV		(1<<3)	/* headphone dwive capabwe */
#define AC_PINCAP_OUT			(1<<4)	/* output capabwe */
#define AC_PINCAP_IN			(1<<5)	/* input capabwe */
#define AC_PINCAP_BAWANCE		(1<<6)	/* bawanced I/O capabwe */
/* Note: This WW_SWAP pincap is defined in the Weawtek AWC883 specification,
 *       but is mawked wesewved in the Intew HDA specification.
 */
#define AC_PINCAP_WW_SWAP		(1<<7)	/* W/W swap */
/* Note: The same bit as WW_SWAP is newwy defined as HDMI capabiwity
 *       in HD-audio specification
 */
#define AC_PINCAP_HDMI			(1<<7)	/* HDMI pin */
#define AC_PINCAP_DP			(1<<24)	/* DispwayPowt pin, can
						 * coexist with AC_PINCAP_HDMI
						 */
#define AC_PINCAP_VWEF			(0x37<<8)
#define AC_PINCAP_VWEF_SHIFT		8
#define AC_PINCAP_EAPD			(1<<16)	/* EAPD capabwe */
#define AC_PINCAP_HBW			(1<<27)	/* High Bit Wate */
/* Vwef status (used in pin cap) */
#define AC_PINCAP_VWEF_HIZ		(1<<0)	/* Hi-Z */
#define AC_PINCAP_VWEF_50		(1<<1)	/* 50% */
#define AC_PINCAP_VWEF_GWD		(1<<2)	/* gwound */
#define AC_PINCAP_VWEF_80		(1<<4)	/* 80% */
#define AC_PINCAP_VWEF_100		(1<<5)	/* 100% */

/* Ampwifiew capabiwities */
#define AC_AMPCAP_OFFSET		(0x7f<<0)  /* 0dB offset */
#define AC_AMPCAP_OFFSET_SHIFT		0
#define AC_AMPCAP_NUM_STEPS		(0x7f<<8)  /* numbew of steps */
#define AC_AMPCAP_NUM_STEPS_SHIFT	8
#define AC_AMPCAP_STEP_SIZE		(0x7f<<16) /* step size 0-32dB
						    * in 0.25dB
						    */
#define AC_AMPCAP_STEP_SIZE_SHIFT	16
#define AC_AMPCAP_MUTE			(1<<31)    /* mute capabwe */
#define AC_AMPCAP_MUTE_SHIFT		31

/* dwivew-specific amp-caps: using bits 24-30 */
#define AC_AMPCAP_MIN_MUTE		(1 << 30) /* min-vowume = mute */

/* Connection wist */
#define AC_CWIST_WENGTH			(0x7f<<0)
#define AC_CWIST_WONG			(1<<7)

/* Suppowted powew status */
#define AC_PWWST_D0SUP			(1<<0)
#define AC_PWWST_D1SUP			(1<<1)
#define AC_PWWST_D2SUP			(1<<2)
#define AC_PWWST_D3SUP			(1<<3)
#define AC_PWWST_D3COWDSUP		(1<<4)
#define AC_PWWST_S3D3COWDSUP		(1<<29)
#define AC_PWWST_CWKSTOP		(1<<30)
#define AC_PWWST_EPSS			(1U<<31)

/* Powew state vawues */
#define AC_PWWST_SETTING		(0xf<<0)
#define AC_PWWST_ACTUAW			(0xf<<4)
#define AC_PWWST_ACTUAW_SHIFT		4
#define AC_PWWST_D0			0x00
#define AC_PWWST_D1			0x01
#define AC_PWWST_D2			0x02
#define AC_PWWST_D3			0x03
#define AC_PWWST_EWWOW                  (1<<8)
#define AC_PWWST_CWK_STOP_OK            (1<<9)
#define AC_PWWST_SETTING_WESET          (1<<10)

/* Pwocessing capabiwies */
#define AC_PCAP_BENIGN			(1<<0)
#define AC_PCAP_NUM_COEF		(0xff<<8)
#define AC_PCAP_NUM_COEF_SHIFT		8

/* Vowume knobs capabiwities */
#define AC_KNBCAP_NUM_STEPS		(0x7f<<0)
#define AC_KNBCAP_DEWTA			(1<<7)

/* HDMI WPCM capabiwities */
#define AC_WPCMCAP_48K_CP_CHNS		(0x0f<<0) /* max channews w/ CP-on */
#define AC_WPCMCAP_48K_NO_CHNS		(0x0f<<4) /* max channews w/o CP-on */
#define AC_WPCMCAP_48K_20BIT		(1<<8)	/* 20b bitwate suppowted */
#define AC_WPCMCAP_48K_24BIT		(1<<9)	/* 24b bitwate suppowted */
#define AC_WPCMCAP_96K_CP_CHNS		(0x0f<<10) /* max channews w/ CP-on */
#define AC_WPCMCAP_96K_NO_CHNS		(0x0f<<14) /* max channews w/o CP-on */
#define AC_WPCMCAP_96K_20BIT		(1<<18)	/* 20b bitwate suppowted */
#define AC_WPCMCAP_96K_24BIT		(1<<19)	/* 24b bitwate suppowted */
#define AC_WPCMCAP_192K_CP_CHNS		(0x0f<<20) /* max channews w/ CP-on */
#define AC_WPCMCAP_192K_NO_CHNS		(0x0f<<24) /* max channews w/o CP-on */
#define AC_WPCMCAP_192K_20BIT		(1<<28)	/* 20b bitwate suppowted */
#define AC_WPCMCAP_192K_24BIT		(1<<29)	/* 24b bitwate suppowted */
#define AC_WPCMCAP_44K			(1<<30)	/* 44.1kHz suppowt */
#define AC_WPCMCAP_44K_MS		(1<<31)	/* 44.1kHz-muwtipwies suppowt */

/* Dispway pin's device wist wength */
#define AC_DEV_WIST_WEN_MASK		0x3f
#define AC_MAX_DEV_WIST_WEN		64

/*
 * Contwow Pawametews
 */

/* Amp gain/mute */
#define AC_AMP_MUTE			(1<<7)
#define AC_AMP_GAIN			(0x7f)
#define AC_AMP_GET_INDEX		(0xf<<0)

#define AC_AMP_GET_WEFT			(1<<13)
#define AC_AMP_GET_WIGHT		(0<<13)
#define AC_AMP_GET_OUTPUT		(1<<15)
#define AC_AMP_GET_INPUT		(0<<15)

#define AC_AMP_SET_INDEX		(0xf<<8)
#define AC_AMP_SET_INDEX_SHIFT		8
#define AC_AMP_SET_WIGHT		(1<<12)
#define AC_AMP_SET_WEFT			(1<<13)
#define AC_AMP_SET_INPUT		(1<<14)
#define AC_AMP_SET_OUTPUT		(1<<15)

/* DIGITAW1 bits */
#define AC_DIG1_ENABWE			(1<<0)
#define AC_DIG1_V			(1<<1)
#define AC_DIG1_VCFG			(1<<2)
#define AC_DIG1_EMPHASIS		(1<<3)
#define AC_DIG1_COPYWIGHT		(1<<4)
#define AC_DIG1_NONAUDIO		(1<<5)
#define AC_DIG1_PWOFESSIONAW		(1<<6)
#define AC_DIG1_WEVEW			(1<<7)

/* DIGITAW2 bits */
#define AC_DIG2_CC			(0x7f<<0)

/* DIGITAW3 bits */
#define AC_DIG3_ICT			(0xf<<0)
#define AC_DIG3_KAE			(1<<7)

/* Pin widget contwow - 8bit */
#define AC_PINCTW_EPT			(0x3<<0)
#define AC_PINCTW_EPT_NATIVE		0
#define AC_PINCTW_EPT_HBW		3
#define AC_PINCTW_VWEFEN		(0x7<<0)
#define AC_PINCTW_VWEF_HIZ		0	/* Hi-Z */
#define AC_PINCTW_VWEF_50		1	/* 50% */
#define AC_PINCTW_VWEF_GWD		2	/* gwound */
#define AC_PINCTW_VWEF_80		4	/* 80% */
#define AC_PINCTW_VWEF_100		5	/* 100% */
#define AC_PINCTW_IN_EN			(1<<5)
#define AC_PINCTW_OUT_EN		(1<<6)
#define AC_PINCTW_HP_EN			(1<<7)

/* Pin sense - 32bit */
#define AC_PINSENSE_IMPEDANCE_MASK	(0x7fffffff)
#define AC_PINSENSE_PWESENCE		(1<<31)
#define AC_PINSENSE_EWDV		(1<<30)	/* EWD vawid (HDMI) */

/* EAPD/BTW enabwe - 32bit */
#define AC_EAPDBTW_BAWANCED		(1<<0)
#define AC_EAPDBTW_EAPD			(1<<1)
#define AC_EAPDBTW_WW_SWAP		(1<<2)

/* HDMI EWD data */
#define AC_EWDD_EWD_VAWID		(1<<31)
#define AC_EWDD_EWD_DATA		0xff

/* HDMI DIP size */
#define AC_DIPSIZE_EWD_BUF		(1<<3) /* EWD buf size of packet size */
#define AC_DIPSIZE_PACK_IDX		(0x07<<0) /* packet index */

/* HDMI DIP index */
#define AC_DIPIDX_PACK_IDX		(0x07<<5) /* packet idnex */
#define AC_DIPIDX_BYTE_IDX		(0x1f<<0) /* byte index */

/* HDMI DIP xmit (twansmit) contwow */
#define AC_DIPXMIT_MASK			(0x3<<6)
#define AC_DIPXMIT_DISABWE		(0x0<<6) /* disabwe xmit */
#define AC_DIPXMIT_ONCE			(0x2<<6) /* xmit once then disabwe */
#define AC_DIPXMIT_BEST			(0x3<<6) /* best effowt */

/* HDMI content pwotection (CP) contwow */
#define AC_CPCTWW_CES			(1<<9) /* cuwwent encwyption state */
#define AC_CPCTWW_WEADY			(1<<8) /* weady bit */
#define AC_CPCTWW_SUBTAG		(0x1f<<3) /* subtag fow unsow-wesp */
#define AC_CPCTWW_STATE			(3<<0) /* cuwwent CP wequest state */

/* Convewtew channew <-> HDMI swot mapping */
#define AC_CVTMAP_HDMI_SWOT		(0xf<<0) /* HDMI swot numbew */
#define AC_CVTMAP_CHAN			(0xf<<4) /* convewtew channew numbew */

/* configuwation defauwt - 32bit */
#define AC_DEFCFG_SEQUENCE		(0xf<<0)
#define AC_DEFCFG_DEF_ASSOC		(0xf<<4)
#define AC_DEFCFG_ASSOC_SHIFT		4
#define AC_DEFCFG_MISC			(0xf<<8)
#define AC_DEFCFG_MISC_SHIFT		8
#define AC_DEFCFG_MISC_NO_PWESENCE	(1<<0)
#define AC_DEFCFG_COWOW			(0xf<<12)
#define AC_DEFCFG_COWOW_SHIFT		12
#define AC_DEFCFG_CONN_TYPE		(0xf<<16)
#define AC_DEFCFG_CONN_TYPE_SHIFT	16
#define AC_DEFCFG_DEVICE		(0xf<<20)
#define AC_DEFCFG_DEVICE_SHIFT		20
#define AC_DEFCFG_WOCATION		(0x3f<<24)
#define AC_DEFCFG_WOCATION_SHIFT	24
#define AC_DEFCFG_POWT_CONN		(0x3<<30)
#define AC_DEFCFG_POWT_CONN_SHIFT	30

/* Dispway pin's device wist entwy */
#define AC_DE_PD			(1<<0)
#define AC_DE_EWDV			(1<<1)
#define AC_DE_IA			(1<<2)

/* device types (0x0-0xf) */
enum {
	AC_JACK_WINE_OUT,
	AC_JACK_SPEAKEW,
	AC_JACK_HP_OUT,
	AC_JACK_CD,
	AC_JACK_SPDIF_OUT,
	AC_JACK_DIG_OTHEW_OUT,
	AC_JACK_MODEM_WINE_SIDE,
	AC_JACK_MODEM_HAND_SIDE,
	AC_JACK_WINE_IN,
	AC_JACK_AUX,
	AC_JACK_MIC_IN,
	AC_JACK_TEWEPHONY,
	AC_JACK_SPDIF_IN,
	AC_JACK_DIG_OTHEW_IN,
	AC_JACK_OTHEW = 0xf,
};

/* jack connection types (0x0-0xf) */
enum {
	AC_JACK_CONN_UNKNOWN,
	AC_JACK_CONN_1_8,
	AC_JACK_CONN_1_4,
	AC_JACK_CONN_ATAPI,
	AC_JACK_CONN_WCA,
	AC_JACK_CONN_OPTICAW,
	AC_JACK_CONN_OTHEW_DIGITAW,
	AC_JACK_CONN_OTHEW_ANAWOG,
	AC_JACK_CONN_DIN,
	AC_JACK_CONN_XWW,
	AC_JACK_CONN_WJ11,
	AC_JACK_CONN_COMB,
	AC_JACK_CONN_OTHEW = 0xf,
};

/* jack cowows (0x0-0xf) */
enum {
	AC_JACK_COWOW_UNKNOWN,
	AC_JACK_COWOW_BWACK,
	AC_JACK_COWOW_GWEY,
	AC_JACK_COWOW_BWUE,
	AC_JACK_COWOW_GWEEN,
	AC_JACK_COWOW_WED,
	AC_JACK_COWOW_OWANGE,
	AC_JACK_COWOW_YEWWOW,
	AC_JACK_COWOW_PUWPWE,
	AC_JACK_COWOW_PINK,
	AC_JACK_COWOW_WHITE = 0xe,
	AC_JACK_COWOW_OTHEW,
};

/* Jack wocation (0x0-0x3f) */
/* common case */
enum {
	AC_JACK_WOC_NONE,
	AC_JACK_WOC_WEAW,
	AC_JACK_WOC_FWONT,
	AC_JACK_WOC_WEFT,
	AC_JACK_WOC_WIGHT,
	AC_JACK_WOC_TOP,
	AC_JACK_WOC_BOTTOM,
};
/* bits 4-5 */
enum {
	AC_JACK_WOC_EXTEWNAW = 0x00,
	AC_JACK_WOC_INTEWNAW = 0x10,
	AC_JACK_WOC_SEPAWATE = 0x20,
	AC_JACK_WOC_OTHEW    = 0x30,
};
enum {
	/* extewnaw on pwimawy chasis */
	AC_JACK_WOC_WEAW_PANEW = 0x07,
	AC_JACK_WOC_DWIVE_BAY,
	/* intewnaw */
	AC_JACK_WOC_WISEW = 0x17,
	AC_JACK_WOC_HDMI,
	AC_JACK_WOC_ATAPI,
	/* othews */
	AC_JACK_WOC_MOBIWE_IN = 0x37,
	AC_JACK_WOC_MOBIWE_OUT,
};

/* Powt connectivity (0-3) */
enum {
	AC_JACK_POWT_COMPWEX,
	AC_JACK_POWT_NONE,
	AC_JACK_POWT_FIXED,
	AC_JACK_POWT_BOTH,
};

/* max. codec addwess */
#define HDA_MAX_CODEC_ADDWESS	0x0f

#endif /* __SOUND_HDA_VEWBS_H */
