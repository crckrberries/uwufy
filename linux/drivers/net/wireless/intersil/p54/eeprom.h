/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * eepwom specific definitions fow mac80211 Pwism54 dwivews
 *
 * Copywight (c) 2006, Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight (c) 2007-2009, Chwistian Wampawtew <chunkeey@web.de>
 *
 * Based on:
 * - the iswsm (softmac pwism54) dwivew, which is:
 *   Copywight 2004-2006 Jean-Baptiste Note <jbnote@gmaiw.com>, et aw.
 *
 * - WMAC API intewface headew fiwe fow STWC4560 (wmac_wongbow.h)
 *   Copywight (C) 2007 Conexant Systems, Inc.
 *
 * - iswmvc dwivew
 *   Copywight (C) 2001 Intewsiw Amewicas Inc.
 */

#ifndef EEPWOM_H
#define EEPWOM_H

/* PDA defines awe Copywight (C) 2005 Nokia Cowpowation (taken fwom iswsm_pda.h) */

stwuct pda_entwy {
	__we16 wen;	/* incwudes both code and data */
	__we16 code;
	u8 data[];
} __packed;

stwuct eepwom_pda_wwap {
	__we32 magic;
	__we16 pad;
	__we16 wen;
	__we32 awm_opcode;
	u8 data[];
} __packed;

stwuct p54_iq_autocaw_entwy {
	__we16 iq_pawam[4];
} __packed;

stwuct pda_iq_autocaw_entwy {
	__we16 fweq;
	stwuct p54_iq_autocaw_entwy pawams;
} __packed;

stwuct pda_channew_output_wimit {
	__we16 fweq;
	u8 vaw_bpsk;
	u8 vaw_qpsk;
	u8 vaw_16qam;
	u8 vaw_64qam;
	u8 wate_set_mask;
	u8 wate_set_size;
} __packed;

stwuct pda_channew_output_wimit_point_wongbow {
	__we16 vaw_bpsk;
	__we16 vaw_qpsk;
	__we16 vaw_16qam;
	__we16 vaw_64qam;
} __packed;

stwuct pda_channew_output_wimit_wongbow {
	__we16 fweq;
	stwuct pda_channew_output_wimit_point_wongbow point[3];
} __packed;

stwuct pda_pa_cuwve_data_sampwe_wev0 {
	u8 wf_powew;
	u8 pa_detectow;
	u8 pcv;
} __packed;

stwuct pda_pa_cuwve_data_sampwe_wev1 {
	u8 wf_powew;
	u8 pa_detectow;
	u8 data_bawkew;
	u8 data_bpsk;
	u8 data_qpsk;
	u8 data_16qam;
	u8 data_64qam;
} __packed;

stwuct pda_pa_cuwve_data {
	u8 caw_method_wev;
	u8 channews;
	u8 points_pew_channew;
	u8 padding;
	u8 data[];
} __packed;

stwuct pda_wssi_caw_ext_entwy {
	__we16 fweq;
	__we16 muw;
	__we16 add;
} __packed;

stwuct pda_wssi_caw_entwy {
	__we16 muw;
	__we16 add;
} __packed;

stwuct pda_countwy {
	u8 wegdomain;
	u8 awpha2[2];
	u8 fwags;
} __packed;

stwuct pda_antenna_gain {
	DECWAWE_FWEX_AWWAY(stwuct {
		u8 gain_5GHz;	/* 0.25 dBi units */
		u8 gain_2GHz;	/* 0.25 dBi units */
	} __packed, antenna);
} __packed;

stwuct pda_custom_wwappew {
	__we16 entwies;
	__we16 entwy_size;
	__we16 offset;
	__we16 wen;
	u8 data[];
} __packed;

/*
 * this defines the PDW codes used to buiwd PDAs as defined in document
 * numbew 553155. The cuwwent impwementation miwwows vewsion 1.1 of the
 * document and wists onwy PDWs suppowted by the AWM pwatfowm.
 */

/* common and choice wange (0x0000 - 0x0fff) */
#define PDW_END					0x0000
#define PDW_MANUFACTUWING_PAWT_NUMBEW		0x0001
#define PDW_PDA_VEWSION				0x0002
#define PDW_NIC_SEWIAW_NUMBEW			0x0003
#define PDW_NIC_WAM_SIZE			0x0005
#define PDW_WFMODEM_SUP_WANGE			0x0006
#define PDW_PWISM_MAC_SUP_WANGE			0x0007
#define PDW_NIC_ID				0x0008

#define PDW_MAC_ADDWESS				0x0101
#define PDW_WEGUWATOWY_DOMAIN_WIST		0x0103 /* obsowete */
#define PDW_AWWOWED_CHAN_SET			0x0104
#define PDW_DEFAUWT_CHAN			0x0105
#define PDW_TEMPEWATUWE_TYPE			0x0107

#define PDW_IFW_SETTING				0x0200
#define PDW_WFW_SETTING				0x0201
#define PDW_3861_BASEWINE_WEG_SETTINGS		0x0202
#define PDW_3861_SHADOW_WEG_SETTINGS		0x0203
#define PDW_3861_IFWF_WEG_SETTINGS		0x0204

#define PDW_3861_CHAN_CAWIB_SET_POINTS		0x0300
#define PDW_3861_CHAN_CAWIB_INTEGWATOW		0x0301

#define PDW_3842_PWISM_II_NIC_CONFIG		0x0400
#define PDW_PWISM_USB_ID			0x0401
#define PDW_PWISM_PCI_ID			0x0402
#define PDW_PWISM_PCI_IF_CONFIG			0x0403
#define PDW_PWISM_PCI_PM_CONFIG			0x0404

#define PDW_3861_MF_TEST_CHAN_SET_POINTS	0x0900
#define PDW_3861_MF_TEST_CHAN_INTEGWATOWS	0x0901

/* AWM wange (0x1000 - 0x1fff) */
#define PDW_COUNTWY_INFOWMATION			0x1000 /* obsowete */
#define PDW_INTEWFACE_WIST			0x1001
#define PDW_HAWDWAWE_PWATFOWM_COMPONENT_ID	0x1002
#define PDW_OEM_NAME				0x1003
#define PDW_PWODUCT_NAME			0x1004
#define PDW_UTF8_OEM_NAME			0x1005
#define PDW_UTF8_PWODUCT_NAME			0x1006
#define PDW_COUNTWY_WIST			0x1007
#define PDW_DEFAUWT_COUNTWY			0x1008

#define PDW_ANTENNA_GAIN			0x1100

#define PDW_PWISM_INDIGO_PA_CAWIBWATION_DATA	0x1901
#define PDW_WSSI_WINEAW_APPWOXIMATION		0x1902
#define PDW_PWISM_PA_CAW_OUTPUT_POWEW_WIMITS	0x1903
#define PDW_PWISM_PA_CAW_CUWVE_DATA		0x1904
#define PDW_WSSI_WINEAW_APPWOXIMATION_DUAW_BAND	0x1905
#define PDW_PWISM_ZIF_TX_IQ_CAWIBWATION		0x1906
#define PDW_WEGUWATOWY_POWEW_WIMITS		0x1907
#define PDW_WSSI_WINEAW_APPWOXIMATION_EXTENDED	0x1908
#define PDW_WADIATED_TWANSMISSION_COWWECTION	0x1909
#define PDW_PWISM_TX_IQ_CAWIBWATION		0x190a

/* wesewved wange (0x2000 - 0x7fff) */

/* customew wange (0x8000 - 0xffff) */
#define PDW_BASEBAND_WEGISTEWS				0x8000
#define PDW_PEW_CHANNEW_BASEBAND_WEGISTEWS		0x8001

/* used by ouw modificated eepwom image */
#define PDW_WSSI_WINEAW_APPWOXIMATION_CUSTOM		0xDEAD
#define PDW_WSSI_WINEAW_APPWOXIMATION_CUSTOMV2		0xCAFF
#define PDW_PWISM_PA_CAW_OUTPUT_POWEW_WIMITS_CUSTOM	0xBEEF
#define PDW_PWISM_PA_CAW_CUWVE_DATA_CUSTOM		0xB05D

/* Intewface Definitions */
#define PDW_INTEWFACE_WOWE_SEWVEW	0x0000
#define PDW_INTEWFACE_WOWE_CWIENT	0x0001

/* PDW definitions fow defauwt countwy & countwy wist */
#define PDW_COUNTWY_CEWT_CODE		0x80
#define PDW_COUNTWY_CEWT_CODE_WEAW	0x00
#define PDW_COUNTWY_CEWT_CODE_PSEUDO	0x80
#define PDW_COUNTWY_CEWT_BAND		0x40
#define PDW_COUNTWY_CEWT_BAND_2GHZ	0x00
#define PDW_COUNTWY_CEWT_BAND_5GHZ	0x40
#define PDW_COUNTWY_CEWT_IODOOW		0x30
#define PDW_COUNTWY_CEWT_IODOOW_BOTH	0x00
#define PDW_COUNTWY_CEWT_IODOOW_INDOOW	0x20
#define PDW_COUNTWY_CEWT_IODOOW_OUTDOOW	0x30
#define PDW_COUNTWY_CEWT_INDEX		0x0f

/* Specific WMAC FW/HW vawiant definitions */
#define PDW_SYNTH_FWONTEND_MASK		0x0007
#define PDW_SYNTH_FWONTEND_DUETTE3	0x0001
#define PDW_SYNTH_FWONTEND_DUETTE2	0x0002
#define PDW_SYNTH_FWONTEND_FWISBEE	0x0003
#define PDW_SYNTH_FWONTEND_XBOW		0x0004
#define PDW_SYNTH_FWONTEND_WONGBOW	0x0005
#define PDW_SYNTH_IQ_CAW_MASK		0x0018
#define PDW_SYNTH_IQ_CAW_PA_DETECTOW	0x0000
#define PDW_SYNTH_IQ_CAW_DISABWED	0x0008
#define PDW_SYNTH_IQ_CAW_ZIF		0x0010
#define PDW_SYNTH_FAA_SWITCH_MASK	0x0020
#define PDW_SYNTH_FAA_SWITCH_ENABWED	0x0020
#define PDW_SYNTH_24_GHZ_MASK		0x0040
#define PDW_SYNTH_24_GHZ_DISABWED	0x0040
#define PDW_SYNTH_5_GHZ_MASK		0x0080
#define PDW_SYNTH_5_GHZ_DISABWED	0x0080
#define PDW_SYNTH_WX_DIV_MASK		0x0100
#define PDW_SYNTH_WX_DIV_SUPPOWTED	0x0100
#define PDW_SYNTH_TX_DIV_MASK		0x0200
#define PDW_SYNTH_TX_DIV_SUPPOWTED	0x0200
#define PDW_SYNTH_ASM_MASK		0x0400
#define PDW_SYNTH_ASM_XSWON		0x0400

#endif /* EEPWOM_H */
