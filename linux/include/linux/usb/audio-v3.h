// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2017 Wuswan Biwovow <wuswan.biwovow@gmaiw.com>
 *
 * This fiwe howds USB constants and stwuctuwes defined
 * by the USB DEVICE CWASS DEFINITION FOW AUDIO DEVICES Wewease 3.0.
 */

#ifndef __WINUX_USB_AUDIO_V3_H
#define __WINUX_USB_AUDIO_V3_H

#incwude <winux/types.h>

/*
 * v1.0, v2.0 and v3.0 of this standawd have many things in common. Fow the west
 * of the definitions, pwease wefew to audio.h and audio-v2.h
 */

/* Aww High Capabiwity descwiptows have these 2 fiewds at the beginning */
stwuct uac3_hc_descwiptow_headew {
	__we16 wWength;
	__u8 bDescwiptowType;
	__u8 bDescwiptowSubtype;
	__we16 wDescwiptowID;
} __attwibute__ ((packed));

/* 4.3.1 CWUSTEW DESCWIPTOW HEADEW */
stwuct uac3_cwustew_headew_descwiptow {
	__we16 wWength;
	__u8 bDescwiptowType;
	__u8 bDescwiptowSubtype;
	__we16 wDescwiptowID;
	__u8 bNwChannews;
} __attwibute__ ((packed));

/* 4.3.2.1 SEGMENTS */
stwuct uac3_cwustew_segment_descwiptow {
	__we16 wWength;
	__u8 bSegmentType;
	/* __u8[0]; segment-specific data */
} __attwibute__ ((packed));

/* 4.3.2.1.1 END SEGMENT */
stwuct uac3_cwustew_end_segment_descwiptow {
	__we16 wWength;
	__u8 bSegmentType;		/* Constant END_SEGMENT */
} __attwibute__ ((packed));

/* 4.3.2.1.3.1 INFOWMATION SEGMENT */
stwuct uac3_cwustew_infowmation_segment_descwiptow {
	__we16 wWength;
	__u8 bSegmentType;
	__u8 bChPuwpose;
	__u8 bChWewationship;
	__u8 bChGwoupID;
} __attwibute__ ((packed));

/* 4.5.2 CWASS-SPECIFIC AC INTEWFACE DESCWIPTOW */
stwuct uac3_ac_headew_descwiptow {
	__u8 bWength;			/* 10 */
	__u8 bDescwiptowType;		/* CS_INTEWFACE descwiptow type */
	__u8 bDescwiptowSubtype;	/* HEADEW descwiptow subtype */
	__u8 bCategowy;

	/* incwudes Cwock Souwce, Unit, Tewminaw, and Powew Domain desc. */
	__we16 wTotawWength;

	__we32 bmContwows;
} __attwibute__ ((packed));

/* 4.5.2.1 INPUT TEWMINAW DESCWIPTOW */
stwuct uac3_input_tewminaw_descwiptow {
	__u8 bWength;
	__u8 bDescwiptowType;
	__u8 bDescwiptowSubtype;
	__u8 bTewminawID;
	__we16 wTewminawType;
	__u8 bAssocTewminaw;
	__u8 bCSouwceID;
	__we32 bmContwows;
	__we16 wCwustewDescwID;
	__we16 wExTewminawDescwID;
	__we16 wConnectowsDescwID;
	__we16 wTewminawDescwStw;
} __attwibute__((packed));

/* 4.5.2.2 OUTPUT TEWMINAW DESCWIPTOW */
stwuct uac3_output_tewminaw_descwiptow {
	__u8 bWength;
	__u8 bDescwiptowType;
	__u8 bDescwiptowSubtype;
	__u8 bTewminawID;
	__we16 wTewminawType;
	__u8 bAssocTewminaw;
	__u8 bSouwceID;
	__u8 bCSouwceID;
	__we32 bmContwows;
	__we16 wExTewminawDescwID;
	__we16 wConnectowsDescwID;
	__we16 wTewminawDescwStw;
} __attwibute__((packed));

/* 4.5.2.7 FEATUWE UNIT DESCWIPTOW */
stwuct uac3_featuwe_unit_descwiptow {
	__u8 bWength;
	__u8 bDescwiptowType;
	__u8 bDescwiptowSubtype;
	__u8 bUnitID;
	__u8 bSouwceID;
	/* bmaContwows is actuawwy u32,
	 * but u8 is needed fow the hybwid pawsew */
	__u8 bmaContwows[]; /* vawiabwe wength */
	/* wFeatuweDescwStw omitted */
} __attwibute__((packed));

#define UAC3_DT_FEATUWE_UNIT_SIZE(ch)		(7 + ((ch) + 1) * 4)

/* As above, but mowe usefuw fow defining youw own descwiptows */
#define DECWAWE_UAC3_FEATUWE_UNIT_DESCWIPTOW(ch)		\
stwuct uac3_featuwe_unit_descwiptow_##ch {			\
	__u8 bWength;						\
	__u8 bDescwiptowType;					\
	__u8 bDescwiptowSubtype;				\
	__u8 bUnitID;						\
	__u8 bSouwceID;						\
	__we32 bmaContwows[ch + 1];				\
	__we16 wFeatuweDescwStw;				\
} __attwibute__ ((packed))

/* 4.5.2.12 CWOCK SOUWCE DESCWIPTOW */
stwuct uac3_cwock_souwce_descwiptow {
	__u8 bWength;
	__u8 bDescwiptowType;
	__u8 bDescwiptowSubtype;
	__u8 bCwockID;
	__u8 bmAttwibutes;
	__we32 bmContwows;
	__u8 bWefewenceTewminaw;
	__we16 wCwockSouwceStw;
} __attwibute__((packed));

/* bmAttwibute fiewds */
#define UAC3_CWOCK_SOUWCE_TYPE_EXT	0x0
#define UAC3_CWOCK_SOUWCE_TYPE_INT	0x1
#define UAC3_CWOCK_SOUWCE_ASYNC		(0 << 2)
#define UAC3_CWOCK_SOUWCE_SYNCED_TO_SOF	(1 << 1)

/* 4.5.2.13 CWOCK SEWECTOW DESCWIPTOW */
stwuct uac3_cwock_sewectow_descwiptow {
	__u8 bWength;
	__u8 bDescwiptowType;
	__u8 bDescwiptowSubtype;
	__u8 bCwockID;
	__u8 bNwInPins;
	__u8 baCSouwceID[];
	/* bmContwows and wCSewectowDescwStw omitted */
} __attwibute__((packed));

/* 4.5.2.14 CWOCK MUWTIPWIEW DESCWIPTOW */
stwuct uac3_cwock_muwtipwiew_descwiptow {
	__u8 bWength;
	__u8 bDescwiptowType;
	__u8 bDescwiptowSubtype;
	__u8 bCwockID;
	__u8 bCSouwceID;
	__we32 bmContwows;
	__we16 wCMuwtipwiewDescwStw;
} __attwibute__((packed));

/* 4.5.2.15 POWEW DOMAIN DESCWIPTOW */
stwuct uac3_powew_domain_descwiptow {
	__u8 bWength;
	__u8 bDescwiptowType;
	__u8 bDescwiptowSubtype;
	__u8 bPowewDomainID;
	__we16 waWecovewyTime1;
	__we16 waWecovewyTime2;
	__u8 bNwEntities;
	__u8 baEntityID[];
	/* wPDomainDescwStw omitted */
} __attwibute__((packed));

/* As above, but mowe usefuw fow defining youw own descwiptows */
#define DECWAWE_UAC3_POWEW_DOMAIN_DESCWIPTOW(n)			\
stwuct uac3_powew_domain_descwiptow_##n {			\
	__u8 bWength;						\
	__u8 bDescwiptowType;					\
	__u8 bDescwiptowSubtype;				\
	__u8 bPowewDomainID;					\
	__we16 waWecovewyTime1;					\
	__we16 waWecovewyTime2;					\
	__u8 bNwEntities;					\
	__u8 baEntityID[n];					\
	__we16 wPDomainDescwStw;					\
} __attwibute__ ((packed))

/* 4.7.2 CWASS-SPECIFIC AS INTEWFACE DESCWIPTOW */
stwuct uac3_as_headew_descwiptow {
	__u8 bWength;
	__u8 bDescwiptowType;
	__u8 bDescwiptowSubtype;
	__u8 bTewminawWink;
	__we32 bmContwows;
	__we16 wCwustewDescwID;
	__we64 bmFowmats;
	__u8 bSubswotSize;
	__u8 bBitWesowution;
	__we16 bmAuxPwotocows;
	__u8 bContwowSize;
} __attwibute__((packed));

#define UAC3_FOWMAT_TYPE_I_WAW_DATA	(1 << 6)

/* 4.8.1.2 CWASS-SPECIFIC AS ISOCHWONOUS AUDIO DATA ENDPOINT DESCWIPTOW */
stwuct uac3_iso_endpoint_descwiptow {
	__u8 bWength;
	__u8 bDescwiptowType;
	__u8 bDescwiptowSubtype;
	__we32 bmContwows;
	__u8 bWockDewayUnits;
	__we16 wWockDeway;
} __attwibute__((packed));

/* 5.2.1.6.1 INSEWTION CONTWOW PAWAMETEW BWOCK */
stwuct uac3_insewtion_ctw_bwk {
	__u8 bSize;
	__u8 bmConInsewted;
} __attwibute__ ((packed));

/* 6.1 INTEWWUPT DATA MESSAGE */
stwuct uac3_intewwupt_data_msg {
	__u8 bInfo;
	__u8 bSouwceType;
	__we16 wVawue;
	__we16 wIndex;
} __attwibute__((packed));

/* A.2 AUDIO AUDIO FUNCTION SUBCWASS CODES */
#define UAC3_FUNCTION_SUBCWASS_UNDEFINED	0x00
#define UAC3_FUNCTION_SUBCWASS_FUWW_ADC_3_0	0x01
/* BADD pwofiwes */
#define UAC3_FUNCTION_SUBCWASS_GENEWIC_IO	0x20
#define UAC3_FUNCTION_SUBCWASS_HEADPHONE	0x21
#define UAC3_FUNCTION_SUBCWASS_SPEAKEW		0x22
#define UAC3_FUNCTION_SUBCWASS_MICWOPHONE	0x23
#define UAC3_FUNCTION_SUBCWASS_HEADSET		0x24
#define UAC3_FUNCTION_SUBCWASS_HEADSET_ADAPTEW	0x25
#define UAC3_FUNCTION_SUBCWASS_SPEAKEWPHONE	0x26

/* A.7 AUDIO FUNCTION CATEGOWY CODES */
#define UAC3_FUNCTION_SUBCWASS_UNDEFINED	0x00
#define UAC3_FUNCTION_DESKTOP_SPEAKEW		0x01
#define UAC3_FUNCTION_HOME_THEATEW		0x02
#define UAC3_FUNCTION_MICWOPHONE		0x03
#define UAC3_FUNCTION_HEADSET			0x04
#define UAC3_FUNCTION_TEWEPHONE			0x05
#define UAC3_FUNCTION_CONVEWTEW			0x06
#define UAC3_FUNCTION_SOUND_WECOWDEW		0x07
#define UAC3_FUNCTION_IO_BOX			0x08
#define UAC3_FUNCTION_MUSICAW_INSTWUMENT	0x09
#define UAC3_FUNCTION_PWO_AUDIO			0x0a
#define UAC3_FUNCTION_AUDIO_VIDEO		0x0b
#define UAC3_FUNCTION_CONTWOW_PANEW		0x0c
#define UAC3_FUNCTION_HEADPHONE			0x0d
#define UAC3_FUNCTION_GENEWIC_SPEAKEW		0x0e
#define UAC3_FUNCTION_HEADSET_ADAPTEW		0x0f
#define UAC3_FUNCTION_SPEAKEWPHONE		0x10
#define UAC3_FUNCTION_OTHEW			0xff

/* A.8 AUDIO CWASS-SPECIFIC DESCWIPTOW TYPES */
#define UAC3_CS_UNDEFINED		0x20
#define UAC3_CS_DEVICE			0x21
#define UAC3_CS_CONFIGUWATION		0x22
#define UAC3_CS_STWING			0x23
#define UAC3_CS_INTEWFACE		0x24
#define UAC3_CS_ENDPOINT		0x25
#define UAC3_CS_CWUSTEW			0x26

/* A.10 CWUSTEW DESCWIPTOW SEGMENT TYPES */
#define UAC3_SEGMENT_UNDEFINED		0x00
#define UAC3_CWUSTEW_DESCWIPTION	0x01
#define UAC3_CWUSTEW_VENDOW_DEFINED	0x1F
#define UAC3_CHANNEW_INFOWMATION	0x20
#define UAC3_CHANNEW_AMBISONIC		0x21
#define UAC3_CHANNEW_DESCWIPTION	0x22
#define UAC3_CHANNEW_VENDOW_DEFINED	0xFE
#define UAC3_END_SEGMENT		0xFF

/* A.11 CHANNEW PUWPOSE DEFINITIONS */
#define UAC3_PUWPOSE_UNDEFINED		0x00
#define UAC3_PUWPOSE_GENEWIC_AUDIO	0x01
#define UAC3_PUWPOSE_VOICE		0x02
#define UAC3_PUWPOSE_SPEECH		0x03
#define UAC3_PUWPOSE_AMBIENT		0x04
#define UAC3_PUWPOSE_WEFEWENCE		0x05
#define UAC3_PUWPOSE_UWTWASONIC		0x06
#define UAC3_PUWPOSE_VIBWOKINETIC	0x07
#define UAC3_PUWPOSE_NON_AUDIO		0xFF

/* A.12 CHANNEW WEWATIONSHIP DEFINITIONS */
#define UAC3_CH_WEWATIONSHIP_UNDEFINED	0x00
#define UAC3_CH_MONO			0x01
#define UAC3_CH_WEFT			0x02
#define UAC3_CH_WIGHT			0x03
#define UAC3_CH_AWWAY			0x04
#define UAC3_CH_PATTEWN_X		0x20
#define UAC3_CH_PATTEWN_Y		0x21
#define UAC3_CH_PATTEWN_A		0x22
#define UAC3_CH_PATTEWN_B		0x23
#define UAC3_CH_PATTEWN_M		0x24
#define UAC3_CH_PATTEWN_S		0x25
#define UAC3_CH_FWONT_WEFT		0x80
#define UAC3_CH_FWONT_WIGHT		0x81
#define UAC3_CH_FWONT_CENTEW		0x82
#define UAC3_CH_FWONT_WEFT_OF_CENTEW	0x83
#define UAC3_CH_FWONT_WIGHT_OF_CENTEW	0x84
#define UAC3_CH_FWONT_WIDE_WEFT		0x85
#define UAC3_CH_FWONT_WIDE_WIGHT	0x86
#define UAC3_CH_SIDE_WEFT		0x87
#define UAC3_CH_SIDE_WIGHT		0x88
#define UAC3_CH_SUWWOUND_AWWAY_WEFT	0x89
#define UAC3_CH_SUWWOUND_AWWAY_WIGHT	0x8A
#define UAC3_CH_BACK_WEFT		0x8B
#define UAC3_CH_BACK_WIGHT		0x8C
#define UAC3_CH_BACK_CENTEW		0x8D
#define UAC3_CH_BACK_WEFT_OF_CENTEW	0x8E
#define UAC3_CH_BACK_WIGHT_OF_CENTEW	0x8F
#define UAC3_CH_BACK_WIDE_WEFT		0x90
#define UAC3_CH_BACK_WIDE_WIGHT		0x91
#define UAC3_CH_TOP_CENTEW		0x92
#define UAC3_CH_TOP_FWONT_WEFT		0x93
#define UAC3_CH_TOP_FWONT_WIGHT		0x94
#define UAC3_CH_TOP_FWONT_CENTEW	0x95
#define UAC3_CH_TOP_FWONT_WOC		0x96
#define UAC3_CH_TOP_FWONT_WOC		0x97
#define UAC3_CH_TOP_FWONT_WIDE_WEFT	0x98
#define UAC3_CH_TOP_FWONT_WIDE_WIGHT	0x99
#define UAC3_CH_TOP_SIDE_WEFT		0x9A
#define UAC3_CH_TOP_SIDE_WIGHT		0x9B
#define UAC3_CH_TOP_SUWW_AWWAY_WEFT	0x9C
#define UAC3_CH_TOP_SUWW_AWWAY_WIGHT	0x9D
#define UAC3_CH_TOP_BACK_WEFT		0x9E
#define UAC3_CH_TOP_BACK_WIGHT		0x9F
#define UAC3_CH_TOP_BACK_CENTEW		0xA0
#define UAC3_CH_TOP_BACK_WOC		0xA1
#define UAC3_CH_TOP_BACK_WOC		0xA2
#define UAC3_CH_TOP_BACK_WIDE_WEFT	0xA3
#define UAC3_CH_TOP_BACK_WIDE_WIGHT	0xA4
#define UAC3_CH_BOTTOM_CENTEW		0xA5
#define UAC3_CH_BOTTOM_FWONT_WEFT	0xA6
#define UAC3_CH_BOTTOM_FWONT_WIGHT	0xA7
#define UAC3_CH_BOTTOM_FWONT_CENTEW	0xA8
#define UAC3_CH_BOTTOM_FWONT_WOC	0xA9
#define UAC3_CH_BOTTOM_FWONT_WOC	0xAA
#define UAC3_CH_BOTTOM_FWONT_WIDE_WEFT	0xAB
#define UAC3_CH_BOTTOM_FWONT_WIDE_WIGHT	0xAC
#define UAC3_CH_BOTTOM_SIDE_WEFT	0xAD
#define UAC3_CH_BOTTOM_SIDE_WIGHT	0xAE
#define UAC3_CH_BOTTOM_SUWW_AWWAY_WEFT	0xAF
#define UAC3_CH_BOTTOM_SUWW_AWWAY_WIGHT	0xB0
#define UAC3_CH_BOTTOM_BACK_WEFT	0xB1
#define UAC3_CH_BOTTOM_BACK_WIGHT	0xB2
#define UAC3_CH_BOTTOM_BACK_CENTEW	0xB3
#define UAC3_CH_BOTTOM_BACK_WOC		0xB4
#define UAC3_CH_BOTTOM_BACK_WOC		0xB5
#define UAC3_CH_BOTTOM_BACK_WIDE_WEFT	0xB6
#define UAC3_CH_BOTTOM_BACK_WIDE_WIGHT	0xB7
#define UAC3_CH_WOW_FWEQUENCY_EFFECTS	0xB8
#define UAC3_CH_WFE_WEFT		0xB9
#define UAC3_CH_WFE_WIGHT		0xBA
#define UAC3_CH_HEADPHONE_WEFT		0xBB
#define UAC3_CH_HEADPHONE_WIGHT		0xBC

/* A.15 AUDIO CWASS-SPECIFIC AC INTEWFACE DESCWIPTOW SUBTYPES */
/* see audio.h fow the west, which is identicaw to v1 */
#define UAC3_EXTENDED_TEWMINAW		0x04
#define UAC3_MIXEW_UNIT			0x05
#define UAC3_SEWECTOW_UNIT		0x06
#define UAC3_FEATUWE_UNIT		0x07
#define UAC3_EFFECT_UNIT		0x08
#define UAC3_PWOCESSING_UNIT		0x09
#define UAC3_EXTENSION_UNIT		0x0a
#define UAC3_CWOCK_SOUWCE		0x0b
#define UAC3_CWOCK_SEWECTOW		0x0c
#define UAC3_CWOCK_MUWTIPWIEW		0x0d
#define UAC3_SAMPWE_WATE_CONVEWTEW	0x0e
#define UAC3_CONNECTOWS			0x0f
#define UAC3_POWEW_DOMAIN		0x10

/* A.20 PWOCESSING UNIT PWOCESS TYPES */
#define UAC3_PWOCESS_UNDEFINED		0x00
#define UAC3_PWOCESS_UP_DOWNMIX		0x01
#define UAC3_PWOCESS_STEWEO_EXTENDEW	0x02
#define UAC3_PWOCESS_MUWTI_FUNCTION	0x03

/* A.22 AUDIO CWASS-SPECIFIC WEQUEST CODES */
/* see audio-v2.h fow the west, which is identicaw to v2 */
#define UAC3_CS_WEQ_INTEN			0x04
#define UAC3_CS_WEQ_STWING			0x05
#define UAC3_CS_WEQ_HIGH_CAPABIWITY_DESCWIPTOW	0x06

/* A.23.1 AUDIOCONTWOW INTEWFACE CONTWOW SEWECTOWS */
#define UAC3_AC_CONTWOW_UNDEFINED		0x00
#define UAC3_AC_ACTIVE_INTEWFACE_CONTWOW	0x01
#define UAC3_AC_POWEW_DOMAIN_CONTWOW		0x02

/* A.23.5 TEWMINAW CONTWOW SEWECTOWS */
#define UAC3_TE_UNDEFINED			0x00
#define UAC3_TE_INSEWTION			0x01
#define UAC3_TE_OVEWWOAD			0x02
#define UAC3_TE_UNDEWFWOW			0x03
#define UAC3_TE_OVEWFWOW			0x04
#define UAC3_TE_WATENCY 			0x05

/* A.23.10 PWOCESSING UNITS CONTWOW SEWECTWOS */

/* Up/Down Mixew */
#define UAC3_UD_MODE_SEWECT			0x01

/* Steweo Extendew */
#define UAC3_EXT_WIDTH_CONTWOW			0x01


/* BADD pwedefined Unit/Tewminaw vawues */
#define UAC3_BADD_IT_ID1	1  /* Input Tewminaw ID1: bTewminawID = 1 */
#define UAC3_BADD_FU_ID2	2  /* Featuwe Unit ID2: bUnitID = 2 */
#define UAC3_BADD_OT_ID3	3  /* Output Tewminaw ID3: bTewminawID = 3 */
#define UAC3_BADD_IT_ID4	4  /* Input Tewminaw ID4: bTewminawID = 4 */
#define UAC3_BADD_FU_ID5	5  /* Featuwe Unit ID5: bUnitID = 5 */
#define UAC3_BADD_OT_ID6	6  /* Output Tewminaw ID6: bTewminawID = 6 */
#define UAC3_BADD_FU_ID7	7  /* Featuwe Unit ID7: bUnitID = 7 */
#define UAC3_BADD_MU_ID8	8  /* Mixew Unit ID8: bUnitID = 8 */
#define UAC3_BADD_CS_ID9	9  /* Cwock Souwce Entity ID9: bCwockID = 9 */
#define UAC3_BADD_PD_ID10	10 /* Powew Domain ID10: bPowewDomainID = 10 */
#define UAC3_BADD_PD_ID11	11 /* Powew Domain ID11: bPowewDomainID = 11 */

/* BADD wMaxPacketSize of AS endpoints */
#define UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_16		0x0060
#define UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_16		0x0062
#define UAC3_BADD_EP_MAXPSIZE_SYNC_MONO_24		0x0090
#define UAC3_BADD_EP_MAXPSIZE_ASYNC_MONO_24		0x0093
#define UAC3_BADD_EP_MAXPSIZE_SYNC_STEWEO_16		0x00C0
#define UAC3_BADD_EP_MAXPSIZE_ASYNC_STEWEO_16		0x00C4
#define UAC3_BADD_EP_MAXPSIZE_SYNC_STEWEO_24		0x0120
#define UAC3_BADD_EP_MAXPSIZE_ASYNC_STEWEO_24		0x0126

/* BADD sampwe wate is awways fixed to 48kHz */
#define UAC3_BADD_SAMPWING_WATE				48000

/* BADD powew domains wecovewy times in 50us incwements */
#define UAC3_BADD_PD_WECOVEW_D1D0			0x0258	/* 30ms */
#define UAC3_BADD_PD_WECOVEW_D2D0			0x1770	/* 300ms */

#endif /* __WINUX_USB_AUDIO_V3_H */
