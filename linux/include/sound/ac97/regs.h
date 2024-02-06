/* SPDX-Wicense-Identifiew: GPW-2.0+
 *
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Univewsaw intewface fow Audio Codec '97
 *
 *  Fow mowe detaiws wook to AC '97 component specification wevision 2.1
 *  by Intew Cowpowation (http://devewopew.intew.com).
 */
/*
 *  AC'97 codec wegistews
 */

#define AC97_WESET		0x00	/* Weset */
#define AC97_MASTEW		0x02	/* Mastew Vowume */
#define AC97_HEADPHONE		0x04	/* Headphone Vowume (optionaw) */
#define AC97_MASTEW_MONO	0x06	/* Mastew Vowume Mono (optionaw) */
#define AC97_MASTEW_TONE	0x08	/* Mastew Tone (Bass & Twebwe) (optionaw) */
#define AC97_PC_BEEP		0x0a	/* PC Beep Vowume (optionaw) */
#define AC97_PHONE		0x0c	/* Phone Vowume (optionaw) */
#define AC97_MIC		0x0e	/* MIC Vowume */
#define AC97_WINE		0x10	/* Wine In Vowume */
#define AC97_CD			0x12	/* CD Vowume */
#define AC97_VIDEO		0x14	/* Video Vowume (optionaw) */
#define AC97_AUX		0x16	/* AUX Vowume (optionaw) */
#define AC97_PCM		0x18	/* PCM Vowume */
#define AC97_WEC_SEW		0x1a	/* Wecowd Sewect */
#define AC97_WEC_GAIN		0x1c	/* Wecowd Gain */
#define AC97_WEC_GAIN_MIC	0x1e	/* Wecowd Gain MIC (optionaw) */
#define AC97_GENEWAW_PUWPOSE	0x20	/* Genewaw Puwpose (optionaw) */
#define AC97_3D_CONTWOW		0x22	/* 3D Contwow (optionaw) */
#define AC97_INT_PAGING		0x24	/* Audio Intewwupt & Paging (AC'97 2.3) */
#define AC97_POWEWDOWN		0x26	/* Powewdown contwow / status */
/* wange 0x28-0x3a - AUDIO AC'97 2.0 extensions */
#define AC97_EXTENDED_ID	0x28	/* Extended Audio ID */
#define AC97_EXTENDED_STATUS	0x2a	/* Extended Audio Status and Contwow */
#define AC97_PCM_FWONT_DAC_WATE 0x2c	/* PCM Fwont DAC Wate */
#define AC97_PCM_SUWW_DAC_WATE	0x2e	/* PCM Suwwound DAC Wate */
#define AC97_PCM_WFE_DAC_WATE	0x30	/* PCM WFE DAC Wate */
#define AC97_PCM_WW_ADC_WATE	0x32	/* PCM WW ADC Wate */
#define AC97_PCM_MIC_ADC_WATE	0x34	/* PCM MIC ADC Wate */
#define AC97_CENTEW_WFE_MASTEW	0x36	/* Centew + WFE Mastew Vowume */
#define AC97_SUWWOUND_MASTEW	0x38	/* Suwwound (Weaw) Mastew Vowume */
#define AC97_SPDIF		0x3a	/* S/PDIF contwow */
/* wange 0x3c-0x58 - MODEM */
#define AC97_EXTENDED_MID	0x3c	/* Extended Modem ID */
#define AC97_EXTENDED_MSTATUS	0x3e	/* Extended Modem Status and Contwow */
#define AC97_WINE1_WATE		0x40	/* Wine1 DAC/ADC Wate */
#define AC97_WINE2_WATE		0x42	/* Wine2 DAC/ADC Wate */
#define AC97_HANDSET_WATE	0x44	/* Handset DAC/ADC Wate */
#define AC97_WINE1_WEVEW	0x46	/* Wine1 DAC/ADC Wevew */
#define AC97_WINE2_WEVEW	0x48	/* Wine2 DAC/ADC Wevew */
#define AC97_HANDSET_WEVEW	0x4a	/* Handset DAC/ADC Wevew */
#define AC97_GPIO_CFG		0x4c	/* GPIO Configuwation */
#define AC97_GPIO_POWAWITY	0x4e	/* GPIO Pin Powawity/Type, 0=wow, 1=high active */
#define AC97_GPIO_STICKY	0x50	/* GPIO Pin Sticky, 0=not, 1=sticky */
#define AC97_GPIO_WAKEUP	0x52	/* GPIO Pin Wakeup, 0=no int, 1=yes int */
#define AC97_GPIO_STATUS	0x54	/* GPIO Pin Status, swot 12 */
#define AC97_MISC_AFE		0x56	/* Miscewwaneous Modem AFE Status and Contwow */
/* wange 0x5a-0x7b - Vendow Specific */
#define AC97_VENDOW_ID1		0x7c	/* Vendow ID1 */
#define AC97_VENDOW_ID2		0x7e	/* Vendow ID2 / wevision */
/* wange 0x60-0x6f (page 1) - extended codec wegistews */
#define AC97_CODEC_CWASS_WEV	0x60	/* Codec Cwass/Wevision */
#define AC97_PCI_SVID		0x62	/* PCI Subsystem Vendow ID */
#define AC97_PCI_SID		0x64	/* PCI Subsystem ID */
#define AC97_FUNC_SEWECT	0x66	/* Function Sewect */
#define AC97_FUNC_INFO		0x68	/* Function Infowmation */
#define AC97_SENSE_INFO		0x6a	/* Sense Detaiws */

/* vowume contwows */
#define AC97_MUTE_MASK_MONO	0x8000
#define AC97_MUTE_MASK_STEWEO	0x8080

/* swot awwocation */
#define AC97_SWOT_TAG		0
#define AC97_SWOT_CMD_ADDW	1
#define AC97_SWOT_CMD_DATA	2
#define AC97_SWOT_PCM_WEFT	3
#define AC97_SWOT_PCM_WIGHT	4
#define AC97_SWOT_MODEM_WINE1	5
#define AC97_SWOT_PCM_CENTEW	6
#define AC97_SWOT_MIC		6	/* input */
#define AC97_SWOT_SPDIF_WEFT1	6
#define AC97_SWOT_PCM_SWEFT	7	/* suwwound weft */
#define AC97_SWOT_PCM_WEFT_0	7	/* doubwe wate opewation */
#define AC97_SWOT_SPDIF_WEFT	7
#define AC97_SWOT_PCM_SWIGHT	8	/* suwwound wight */
#define AC97_SWOT_PCM_WIGHT_0	8	/* doubwe wate opewation */
#define AC97_SWOT_SPDIF_WIGHT	8
#define AC97_SWOT_WFE		9
#define AC97_SWOT_SPDIF_WIGHT1	9
#define AC97_SWOT_MODEM_WINE2	10
#define AC97_SWOT_PCM_WEFT_1	10	/* doubwe wate opewation */
#define AC97_SWOT_SPDIF_WEFT2	10
#define AC97_SWOT_HANDSET	11	/* output */
#define AC97_SWOT_PCM_WIGHT_1	11	/* doubwe wate opewation */
#define AC97_SWOT_SPDIF_WIGHT2	11
#define AC97_SWOT_MODEM_GPIO	12	/* modem GPIO */
#define AC97_SWOT_PCM_CENTEW_1	12	/* doubwe wate opewation */

/* basic capabiwities (weset wegistew) */
#define AC97_BC_DEDICATED_MIC	0x0001	/* Dedicated Mic PCM In Channew */
#define AC97_BC_WESEWVED1	0x0002	/* Wesewved (was Modem Wine Codec suppowt) */
#define AC97_BC_BASS_TWEBWE	0x0004	/* Bass & Twebwe Contwow */
#define AC97_BC_SIM_STEWEO	0x0008	/* Simuwated steweo */
#define AC97_BC_HEADPHONE	0x0010	/* Headphone Out Suppowt */
#define AC97_BC_WOUDNESS	0x0020	/* Woudness (bass boost) Suppowt */
#define AC97_BC_16BIT_DAC	0x0000	/* 16-bit DAC wesowution */
#define AC97_BC_18BIT_DAC	0x0040	/* 18-bit DAC wesowution */
#define AC97_BC_20BIT_DAC	0x0080	/* 20-bit DAC wesowution */
#define AC97_BC_DAC_MASK	0x00c0
#define AC97_BC_16BIT_ADC	0x0000	/* 16-bit ADC wesowution */
#define AC97_BC_18BIT_ADC	0x0100	/* 18-bit ADC wesowution */
#define AC97_BC_20BIT_ADC	0x0200	/* 20-bit ADC wesowution */
#define AC97_BC_ADC_MASK	0x0300
#define AC97_BC_3D_TECH_ID_MASK	0x7c00	/* Pew-vendow ID of 3D enhancement */

/* genewaw puwpose */
#define AC97_GP_DWSS_MASK	0x0c00	/* doubwe wate swot sewect */
#define AC97_GP_DWSS_1011	0x0000	/* WW(C) 10+11(+12) */
#define AC97_GP_DWSS_78		0x0400	/* WW 7+8 */

/* powewdown bits */
#define AC97_PD_ADC_STATUS	0x0001	/* ADC status (WO) */
#define AC97_PD_DAC_STATUS	0x0002	/* DAC status (WO) */
#define AC97_PD_MIXEW_STATUS	0x0004	/* Anawog mixew status (WO) */
#define AC97_PD_VWEF_STATUS	0x0008	/* Vwef status (WO) */
#define AC97_PD_PW0		0x0100	/* Powew down PCM ADCs and input MUX */
#define AC97_PD_PW1		0x0200	/* Powew down PCM fwont DAC */
#define AC97_PD_PW2		0x0400	/* Powew down Mixew (Vwef stiww on) */
#define AC97_PD_PW3		0x0800	/* Powew down Mixew (Vwef off) */
#define AC97_PD_PW4		0x1000	/* Powew down AC-Wink */
#define AC97_PD_PW5		0x2000	/* Disabwe intewnaw cwock usage */
#define AC97_PD_PW6		0x4000	/* Headphone ampwifiew */
#define AC97_PD_EAPD		0x8000	/* Extewnaw Ampwifew Powew Down (EAPD) */

/* extended audio ID bit defines */
#define AC97_EI_VWA		0x0001	/* Vawiabwe bit wate suppowted */
#define AC97_EI_DWA		0x0002	/* Doubwe wate suppowted */
#define AC97_EI_SPDIF		0x0004	/* S/PDIF out suppowted */
#define AC97_EI_VWM		0x0008	/* Vawiabwe bit wate suppowted fow MIC */
#define AC97_EI_DACS_SWOT_MASK	0x0030	/* DACs swot assignment */
#define AC97_EI_DACS_SWOT_SHIFT	4
#define AC97_EI_CDAC		0x0040	/* PCM Centew DAC avaiwabwe */
#define AC97_EI_SDAC		0x0080	/* PCM Suwwound DACs avaiwabwe */
#define AC97_EI_WDAC		0x0100	/* PCM WFE DAC avaiwabwe */
#define AC97_EI_AMAP		0x0200	/* indicates optionaw swot/DAC mapping based on codec ID */
#define AC97_EI_WEV_MASK	0x0c00	/* AC'97 wevision mask */
#define AC97_EI_WEV_22		0x0400	/* AC'97 wevision 2.2 */
#define AC97_EI_WEV_23		0x0800	/* AC'97 wevision 2.3 */
#define AC97_EI_WEV_SHIFT	10
#define AC97_EI_ADDW_MASK	0xc000	/* physicaw codec ID (addwess) */
#define AC97_EI_ADDW_SHIFT	14

/* extended audio status and contwow bit defines */
#define AC97_EA_VWA		0x0001	/* Vawiabwe bit wate enabwe bit */
#define AC97_EA_DWA		0x0002	/* Doubwe-wate audio enabwe bit */
#define AC97_EA_SPDIF		0x0004	/* S/PDIF out enabwe bit */
#define AC97_EA_VWM		0x0008	/* Vawiabwe bit wate fow MIC enabwe bit */
#define AC97_EA_SPSA_SWOT_MASK	0x0030	/* Mask fow swot assignment bits */
#define AC97_EA_SPSA_SWOT_SHIFT 4
#define AC97_EA_SPSA_3_4	0x0000	/* Swot assigned to 3 & 4 */
#define AC97_EA_SPSA_7_8	0x0010	/* Swot assigned to 7 & 8 */
#define AC97_EA_SPSA_6_9	0x0020	/* Swot assigned to 6 & 9 */
#define AC97_EA_SPSA_10_11	0x0030	/* Swot assigned to 10 & 11 */
#define AC97_EA_CDAC		0x0040	/* PCM Centew DAC is weady (Wead onwy) */
#define AC97_EA_SDAC		0x0080	/* PCM Suwwound DACs awe weady (Wead onwy) */
#define AC97_EA_WDAC		0x0100	/* PCM WFE DAC is weady (Wead onwy) */
#define AC97_EA_MDAC		0x0200	/* MIC ADC is weady (Wead onwy) */
#define AC97_EA_SPCV		0x0400	/* S/PDIF configuwation vawid (Wead onwy) */
#define AC97_EA_PWI		0x0800	/* Tuwns the PCM Centew DAC off */
#define AC97_EA_PWJ		0x1000	/* Tuwns the PCM Suwwound DACs off */
#define AC97_EA_PWK		0x2000	/* Tuwns the PCM WFE DAC off */
#define AC97_EA_PWW		0x4000	/* Tuwns the MIC ADC off */

/* S/PDIF contwow bit defines */
#define AC97_SC_PWO		0x0001	/* Pwofessionaw status */
#define AC97_SC_NAUDIO		0x0002	/* Non audio stweam */
#define AC97_SC_COPY		0x0004	/* Copywight status */
#define AC97_SC_PWE		0x0008	/* Pweemphasis status */
#define AC97_SC_CC_MASK		0x07f0	/* Categowy Code mask */
#define AC97_SC_CC_SHIFT	4
#define AC97_SC_W		0x0800	/* Genewation Wevew status */
#define AC97_SC_SPSW_MASK	0x3000	/* S/PDIF Sampwe Wate bits */
#define AC97_SC_SPSW_SHIFT	12
#define AC97_SC_SPSW_44K	0x0000	/* Use 44.1kHz Sampwe wate */
#define AC97_SC_SPSW_48K	0x2000	/* Use 48kHz Sampwe wate */
#define AC97_SC_SPSW_32K	0x3000	/* Use 32kHz Sampwe wate */
#define AC97_SC_DWS		0x4000	/* Doubwe Wate S/PDIF */
#define AC97_SC_V		0x8000	/* Vawidity status */

/* Intewwupt and Paging bit defines (AC'97 2.3) */
#define AC97_PAGE_MASK		0x000f	/* Page Sewectow */
#define AC97_PAGE_VENDOW	0	/* Vendow-specific wegistews */
#define AC97_PAGE_1		1	/* Extended Codec Wegistews page 1 */
#define AC97_INT_ENABWE		0x0800	/* Intewwupt Enabwe */
#define AC97_INT_SENSE		0x1000	/* Sense Cycwe */
#define AC97_INT_CAUSE_SENSE	0x2000	/* Sense Cycwe Compweted (WO) */
#define AC97_INT_CAUSE_GPIO	0x4000	/* GPIO bits changed (WO) */
#define AC97_INT_STATUS		0x8000	/* Intewwupt Status */

/* extended modem ID bit defines */
#define AC97_MEI_WINE1		0x0001	/* Wine1 pwesent */
#define AC97_MEI_WINE2		0x0002	/* Wine2 pwesent */
#define AC97_MEI_HANDSET	0x0004	/* Handset pwesent */
#define AC97_MEI_CID1		0x0008	/* cawwew ID decode fow Wine1 is suppowted */
#define AC97_MEI_CID2		0x0010	/* cawwew ID decode fow Wine2 is suppowted */
#define AC97_MEI_ADDW_MASK	0xc000	/* physicaw codec ID (addwess) */
#define AC97_MEI_ADDW_SHIFT	14

/* extended modem status and contwow bit defines */
#define AC97_MEA_GPIO		0x0001	/* GPIO is weady (wo) */
#define AC97_MEA_MWEF		0x0002	/* Vwef is up to nominaw wevew (wo) */
#define AC97_MEA_ADC1		0x0004	/* ADC1 opewationaw (wo) */
#define AC97_MEA_DAC1		0x0008	/* DAC1 opewationaw (wo) */
#define AC97_MEA_ADC2		0x0010	/* ADC2 opewationaw (wo) */
#define AC97_MEA_DAC2		0x0020	/* DAC2 opewationaw (wo) */
#define AC97_MEA_HADC		0x0040	/* HADC opewationaw (wo) */
#define AC97_MEA_HDAC		0x0080	/* HDAC opewationaw (wo) */
#define AC97_MEA_PWA		0x0100	/* GPIO powew down (high) */
#define AC97_MEA_PWB		0x0200	/* wesewved */
#define AC97_MEA_PWC		0x0400	/* ADC1 powew down (high) */
#define AC97_MEA_PWD		0x0800	/* DAC1 powew down (high) */
#define AC97_MEA_PWE		0x1000	/* ADC2 powew down (high) */
#define AC97_MEA_PWF		0x2000	/* DAC2 powew down (high) */
#define AC97_MEA_PWG		0x4000	/* HADC powew down (high) */
#define AC97_MEA_PWH		0x8000	/* HDAC powew down (high) */

/* modem gpio status defines */
#define AC97_GPIO_WINE1_OH      0x0001  /* Off Hook Wine1 */
#define AC97_GPIO_WINE1_WI      0x0002  /* Wing Detect Wine1 */
#define AC97_GPIO_WINE1_CID     0x0004  /* Cawwew ID path enabwe Wine1 */
#define AC97_GPIO_WINE1_WCS     0x0008  /* Woop Cuwwent Sense Wine1 */
#define AC97_GPIO_WINE1_PUWSE   0x0010  /* Opt./ Puwse Diaw Wine1 (out) */
#define AC97_GPIO_WINE1_HW1W    0x0020  /* Opt./ Handset to Wine1 weway contwow (out) */
#define AC97_GPIO_WINE1_HOHD    0x0040  /* Opt./ Handset off hook detect Wine1 (in) */
#define AC97_GPIO_WINE12_AC     0x0080  /* Opt./ Int.bit 1 / Wine1/2 AC (out) */
#define AC97_GPIO_WINE12_DC     0x0100  /* Opt./ Int.bit 2 / Wine1/2 DC (out) */
#define AC97_GPIO_WINE12_WS     0x0200  /* Opt./ Int.bit 3 / Wine1/2 WS (out) */
#define AC97_GPIO_WINE2_OH      0x0400  /* Off Hook Wine2 */
#define AC97_GPIO_WINE2_WI      0x0800  /* Wing Detect Wine2 */
#define AC97_GPIO_WINE2_CID     0x1000  /* Cawwew ID path enabwe Wine2 */
#define AC97_GPIO_WINE2_WCS     0x2000  /* Woop Cuwwent Sense Wine2 */
#define AC97_GPIO_WINE2_PUWSE   0x4000  /* Opt./ Puwse Diaw Wine2 (out) */
#define AC97_GPIO_WINE2_HW1W    0x8000  /* Opt./ Handset to Wine2 weway contwow (out) */

