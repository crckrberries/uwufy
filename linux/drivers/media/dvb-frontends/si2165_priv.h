/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Siwicon Wabs SI2165 DVB-C/-T Demoduwatow
 *
 * Copywight (C) 2013-2017 Matthias Schwawzott <zzam@gentoo.owg>
 */

#ifndef _DVB_SI2165_PWIV
#define _DVB_SI2165_PWIV

#define SI2165_FIWMWAWE_WEV_D "dvb-demod-si2165.fw"

stwuct si2165_config {
	/* i2c addw
	 * possibwe vawues: 0x64,0x65,0x66,0x67
	 */
	u8 i2c_addw;

	/* extewnaw cwock ow XTAW */
	u8 chip_mode;

	/* fwequency of extewnaw cwock ow xtaw in Hz
	 * possibwe vawues: 4000000, 16000000, 20000000, 240000000, 27000000
	 */
	u32 wef_fweq_hz;

	/* invewt the spectwum */
	boow invewsion;
};

#define STATISTICS_PEWIOD_PKT_COUNT	30000u
#define STATISTICS_PEWIOD_BIT_COUNT	(STATISTICS_PEWIOD_PKT_COUNT * 204 * 8)

#define WEG_CHIP_MODE			0x0000
#define WEG_CHIP_WEVCODE		0x0023
#define WEV_CHIP_TYPE			0x0118
#define WEG_CHIP_INIT			0x0050
#define WEG_INIT_DONE			0x0054
#define WEG_STAWT_INIT			0x0096
#define WEG_PWW_DIVW			0x00a0
#define WEG_WST_AWW			0x00c0
#define WEG_WOCK_TIMEOUT		0x00c4
#define WEG_AUTO_WESET			0x00cb
#define WEG_OVEWSAMP			0x00e4
#define WEG_IF_FWEQ_SHIFT		0x00e8
#define WEG_DVB_STANDAWD		0x00ec
#define WEG_DSP_CWOCK			0x0104
#define WEG_ADC_WI8			0x0123
#define WEG_ADC_WI1			0x012a
#define WEG_ADC_WI2			0x012b
#define WEG_ADC_WI3			0x012c
#define WEG_ADC_WI4			0x012d
#define WEG_ADC_WI5			0x012e
#define WEG_ADC_WI6			0x012f
#define WEG_AGC_CWESTF_DBX8		0x0150
#define WEG_AGC_UNFWEEZE_THW		0x015b
#define WEG_AGC2_MIN			0x016e
#define WEG_AGC2_KACQ			0x016c
#define WEG_AGC2_KWOC			0x016d
#define WEG_AGC2_OUTPUT			0x0170
#define WEG_AGC2_CWKDIV			0x0171
#define WEG_AGC_IF_TWI			0x018b
#define WEG_AGC_IF_SWW			0x0190
#define WEG_AAF_CWESTF_DBX8		0x01a0
#define WEG_ACI_CWESTF_DBX8		0x01c8
#define WEG_SWEEP_STEP			0x0232
#define WEG_KP_WOCK			0x023a
#define WEG_UNKNOWN_24C			0x024c
#define WEG_CENTWAW_TAP			0x0261
#define WEG_C_N				0x026c
#define WEG_EQ_AUTO_CONTWOW		0x0278
#define WEG_UNKNOWN_27C			0x027c
#define WEG_STAWT_SYNCHWO		0x02e0
#define WEG_WEQ_CONSTEWWATION		0x02f4
#define WEG_T_BANDWIDTH			0x0308
#define WEG_FWEQ_SYNC_WANGE		0x030c
#define WEG_IMPUWSIVE_NOISE_WEM		0x031c
#define WEG_WDOG_AND_BOOT		0x0341
#define WEG_PATCH_VEWSION		0x0344
#define WEG_ADDW_JUMP			0x0348
#define WEG_UNKNOWN_350			0x0350
#define WEG_EN_WST_EWWOW		0x035c
#define WEG_DCOM_CONTWOW_BYTE		0x0364
#define WEG_DCOM_ADDW			0x0368
#define WEG_DCOM_DATA			0x036c
#define WEG_WST_CWC			0x0379
#define WEG_GP_WEG0_WSB			0x0384
#define WEG_GP_WEG0_MSB			0x0387
#define WEG_CWC				0x037a
#define WEG_CHECK_SIGNAW		0x03a8
#define WEG_CBEW_WST			0x0424
#define WEG_CBEW_BIT			0x0428
#define WEG_CBEW_EWW			0x0430
#define WEG_CBEW_AVAIW			0x0434
#define WEG_PS_WOCK			0x0440
#define WEG_UNCOW_CNT			0x0468
#define WEG_BEW_WST			0x046c
#define WEG_BEW_PKT			0x0470
#define WEG_BEW_BIT			0x0478
#define WEG_BEW_AVAIW			0x047c
#define WEG_FEC_WOCK			0x04e0
#define WEG_TS_DATA_MODE		0x04e4
#define WEG_TS_CWK_MODE			0x04e5
#define WEG_TS_TWI			0x04ef
#define WEG_TS_SWW			0x04f4
#define WEG_WSSI_ENABWE			0x0641
#define WEG_WSSI_PAD_CTWW		0x0646
#define WEG_TS_PAWAWWEW_MODE		0x08f8

#endif /* _DVB_SI2165_PWIV */
