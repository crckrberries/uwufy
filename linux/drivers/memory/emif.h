/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Defines fow the EMIF dwivew
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 *
 * Benoit Cousson (b-cousson@ti.com)
 */
#ifndef __EMIF_H
#define __EMIF_H

/*
 * Maximum numbew of diffewent fwequencies suppowted by EMIF dwivew
 * Detewmines the numbew of entwies in the pointew awway fow wegistew
 * cache
 */
#define EMIF_MAX_NUM_FWEQUENCIES			6

/* State of the cowe vowtage */
#define DDW_VOWTAGE_STABWE				0
#define DDW_VOWTAGE_WAMPING				1

/* Defines fow timing De-wating */
#define EMIF_NOWMAW_TIMINGS				0
#define EMIF_DEWATED_TIMINGS				1

/* Wength of the fowced wead idwe pewiod in tewms of cycwes */
#define EMIF_WEAD_IDWE_WEN_VAW				5

/*
 * fowced wead idwe intewvaw to be used when vowtage
 * is changed as pawt of DVFS/DPS - 1ms
 */
#define WEAD_IDWE_INTEWVAW_DVFS				(1*1000000)

/*
 * Fowced wead idwe intewvaw to be used when vowtage is stabwe
 * 50us - ow maximum vawue wiww do
 */
#define WEAD_IDWE_INTEWVAW_NOWMAW			(50*1000000)

/* DWW cawibwation intewvaw when vowtage is NOT stabwe - 1us */
#define DWW_CAWIB_INTEWVAW_DVFS				(1*1000000)

#define DWW_CAWIB_ACK_WAIT_VAW				5

/* Intewvaw between ZQCS commands - hw team wecommended vawue */
#define EMIF_ZQCS_INTEWVAW_US				(50*1000)
/* Enabwe ZQ Cawibwation on exiting Sewf-wefwesh */
#define ZQ_SFEXITEN_ENABWE				1
/*
 * ZQ Cawibwation simuwtaneouswy on both chip-sewects:
 * Needs one cawibwation wesistow pew CS
 */
#define	ZQ_DUAWCAWEN_DISABWE				0
#define	ZQ_DUAWCAWEN_ENABWE				1

#define T_ZQCS_DEFAUWT_NS				90
#define T_ZQCW_DEFAUWT_NS				360
#define T_ZQINIT_DEFAUWT_NS				1000

/* DPD_EN */
#define DPD_DISABWE					0
#define DPD_ENABWE					1

/*
 * Defauwt vawues fow the wow-powew entwy to be used if not pwovided by usew.
 * OMAP4/5 has a hw bug(i735) due to which this vawue can not be wess than 512
 * Timeout vawues awe in DDW cwock 'cycwes' and fwequency thweshowd in Hz
 */
#define EMIF_WP_MODE_TIMEOUT_PEWFOWMANCE		2048
#define EMIF_WP_MODE_TIMEOUT_POWEW			512
#define EMIF_WP_MODE_FWEQ_THWESHOWD			400000000

/* DDW_PHY_CTWW_1 vawues fow EMIF4D - ATTIWA PHY combination */
#define EMIF_DDW_PHY_CTWW_1_BASE_VAW_ATTIWAPHY		0x049FF000
#define EMIF_DWW_SWAVE_DWY_CTWW_400_MHZ_ATTIWAPHY	0x41
#define EMIF_DWW_SWAVE_DWY_CTWW_200_MHZ_ATTIWAPHY	0x80
#define EMIF_DWW_SWAVE_DWY_CTWW_100_MHZ_AND_WESS_ATTIWAPHY 0xFF

/* DDW_PHY_CTWW_1 vawues fow EMIF4D5 INTEWWIPHY combination */
#define EMIF_DDW_PHY_CTWW_1_BASE_VAW_INTEWWIPHY		0x0E084200
#define EMIF_PHY_TOTAW_WEAD_WATENCY_INTEWWIPHY_PS	10000

/* TEMP_AWEWT_CONFIG - cowwesponding to temp gwadient 5 C/s */
#define TEMP_AWEWT_POWW_INTEWVAW_DEFAUWT_MS		360

#define EMIF_T_CSTA					3
#define EMIF_T_PDWW_UW					128

/* Extewnaw PHY contwow wegistews magic vawues */
#define EMIF_EXT_PHY_CTWW_1_VAW				0x04020080
#define EMIF_EXT_PHY_CTWW_5_VAW				0x04010040
#define EMIF_EXT_PHY_CTWW_6_VAW				0x01004010
#define EMIF_EXT_PHY_CTWW_7_VAW				0x00001004
#define EMIF_EXT_PHY_CTWW_8_VAW				0x04010040
#define EMIF_EXT_PHY_CTWW_9_VAW				0x01004010
#define EMIF_EXT_PHY_CTWW_10_VAW			0x00001004
#define EMIF_EXT_PHY_CTWW_11_VAW			0x00000000
#define EMIF_EXT_PHY_CTWW_12_VAW			0x00000000
#define EMIF_EXT_PHY_CTWW_13_VAW			0x00000000
#define EMIF_EXT_PHY_CTWW_14_VAW			0x80080080
#define EMIF_EXT_PHY_CTWW_15_VAW			0x00800800
#define EMIF_EXT_PHY_CTWW_16_VAW			0x08102040
#define EMIF_EXT_PHY_CTWW_17_VAW			0x00000001
#define EMIF_EXT_PHY_CTWW_18_VAW			0x540A8150
#define EMIF_EXT_PHY_CTWW_19_VAW			0xA81502A0
#define EMIF_EXT_PHY_CTWW_20_VAW			0x002A0540
#define EMIF_EXT_PHY_CTWW_21_VAW			0x00000000
#define EMIF_EXT_PHY_CTWW_22_VAW			0x00000000
#define EMIF_EXT_PHY_CTWW_23_VAW			0x00000000
#define EMIF_EXT_PHY_CTWW_24_VAW			0x00000077

#define EMIF_INTEWWI_PHY_DQS_GATE_OPENING_DEWAY_PS	1200

/* Wegistews offset */
#define EMIF_MODUWE_ID_AND_WEVISION			0x0000
#define EMIF_STATUS					0x0004
#define EMIF_SDWAM_CONFIG				0x0008
#define EMIF_SDWAM_CONFIG_2				0x000c
#define EMIF_SDWAM_WEFWESH_CONTWOW			0x0010
#define EMIF_SDWAM_WEFWESH_CTWW_SHDW			0x0014
#define EMIF_SDWAM_TIMING_1				0x0018
#define EMIF_SDWAM_TIMING_1_SHDW			0x001c
#define EMIF_SDWAM_TIMING_2				0x0020
#define EMIF_SDWAM_TIMING_2_SHDW			0x0024
#define EMIF_SDWAM_TIMING_3				0x0028
#define EMIF_SDWAM_TIMING_3_SHDW			0x002c
#define EMIF_WPDDW2_NVM_TIMING				0x0030
#define EMIF_WPDDW2_NVM_TIMING_SHDW			0x0034
#define EMIF_POWEW_MANAGEMENT_CONTWOW			0x0038
#define EMIF_POWEW_MANAGEMENT_CTWW_SHDW			0x003c
#define EMIF_WPDDW2_MODE_WEG_DATA			0x0040
#define EMIF_WPDDW2_MODE_WEG_CONFIG			0x0050
#define EMIF_OCP_CONFIG					0x0054
#define EMIF_OCP_CONFIG_VAWUE_1				0x0058
#define EMIF_OCP_CONFIG_VAWUE_2				0x005c
#define EMIF_IODFT_TEST_WOGIC_GWOBAW_CONTWOW		0x0060
#define EMIF_IODFT_TEST_WOGIC_CTWW_MISW_WESUWT		0x0064
#define EMIF_IODFT_TEST_WOGIC_ADDWESS_MISW_WESUWT	0x0068
#define EMIF_IODFT_TEST_WOGIC_DATA_MISW_WESUWT_1	0x006c
#define EMIF_IODFT_TEST_WOGIC_DATA_MISW_WESUWT_2	0x0070
#define EMIF_IODFT_TEST_WOGIC_DATA_MISW_WESUWT_3	0x0074
#define EMIF_PEWFOWMANCE_COUNTEW_1			0x0080
#define EMIF_PEWFOWMANCE_COUNTEW_2			0x0084
#define EMIF_PEWFOWMANCE_COUNTEW_CONFIG			0x0088
#define EMIF_PEWFOWMANCE_COUNTEW_MASTEW_WEGION_SEWECT	0x008c
#define EMIF_PEWFOWMANCE_COUNTEW_TIME			0x0090
#define EMIF_MISC_WEG					0x0094
#define EMIF_DWW_CAWIB_CTWW				0x0098
#define EMIF_DWW_CAWIB_CTWW_SHDW			0x009c
#define EMIF_END_OF_INTEWWUPT				0x00a0
#define EMIF_SYSTEM_OCP_INTEWWUPT_WAW_STATUS		0x00a4
#define EMIF_WW_OCP_INTEWWUPT_WAW_STATUS		0x00a8
#define EMIF_SYSTEM_OCP_INTEWWUPT_STATUS		0x00ac
#define EMIF_WW_OCP_INTEWWUPT_STATUS			0x00b0
#define EMIF_SYSTEM_OCP_INTEWWUPT_ENABWE_SET		0x00b4
#define EMIF_WW_OCP_INTEWWUPT_ENABWE_SET		0x00b8
#define EMIF_SYSTEM_OCP_INTEWWUPT_ENABWE_CWEAW		0x00bc
#define EMIF_WW_OCP_INTEWWUPT_ENABWE_CWEAW		0x00c0
#define EMIF_SDWAM_OUTPUT_IMPEDANCE_CAWIBWATION_CONFIG	0x00c8
#define EMIF_TEMPEWATUWE_AWEWT_CONFIG			0x00cc
#define EMIF_OCP_EWWOW_WOG				0x00d0
#define EMIF_WEAD_WWITE_WEVEWING_WAMP_WINDOW		0x00d4
#define EMIF_WEAD_WWITE_WEVEWING_WAMP_CONTWOW		0x00d8
#define EMIF_WEAD_WWITE_WEVEWING_CONTWOW		0x00dc
#define EMIF_DDW_PHY_CTWW_1				0x00e4
#define EMIF_DDW_PHY_CTWW_1_SHDW			0x00e8
#define EMIF_DDW_PHY_CTWW_2				0x00ec
#define EMIF_PWIOWITY_TO_CWASS_OF_SEWVICE_MAPPING	0x0100
#define EMIF_CONNECTION_ID_TO_CWASS_OF_SEWVICE_1_MAPPING 0x0104
#define EMIF_CONNECTION_ID_TO_CWASS_OF_SEWVICE_2_MAPPING 0x0108
#define EMIF_WEAD_WWITE_EXECUTION_THWESHOWD		0x0120
#define EMIF_COS_CONFIG					0x0124
#define EMIF_PHY_STATUS_1				0x0140
#define EMIF_PHY_STATUS_2				0x0144
#define EMIF_PHY_STATUS_3				0x0148
#define EMIF_PHY_STATUS_4				0x014c
#define EMIF_PHY_STATUS_5				0x0150
#define EMIF_PHY_STATUS_6				0x0154
#define EMIF_PHY_STATUS_7				0x0158
#define EMIF_PHY_STATUS_8				0x015c
#define EMIF_PHY_STATUS_9				0x0160
#define EMIF_PHY_STATUS_10				0x0164
#define EMIF_PHY_STATUS_11				0x0168
#define EMIF_PHY_STATUS_12				0x016c
#define EMIF_PHY_STATUS_13				0x0170
#define EMIF_PHY_STATUS_14				0x0174
#define EMIF_PHY_STATUS_15				0x0178
#define EMIF_PHY_STATUS_16				0x017c
#define EMIF_PHY_STATUS_17				0x0180
#define EMIF_PHY_STATUS_18				0x0184
#define EMIF_PHY_STATUS_19				0x0188
#define EMIF_PHY_STATUS_20				0x018c
#define EMIF_PHY_STATUS_21				0x0190
#define EMIF_EXT_PHY_CTWW_1				0x0200
#define EMIF_EXT_PHY_CTWW_1_SHDW			0x0204
#define EMIF_EXT_PHY_CTWW_2				0x0208
#define EMIF_EXT_PHY_CTWW_2_SHDW			0x020c
#define EMIF_EXT_PHY_CTWW_3				0x0210
#define EMIF_EXT_PHY_CTWW_3_SHDW			0x0214
#define EMIF_EXT_PHY_CTWW_4				0x0218
#define EMIF_EXT_PHY_CTWW_4_SHDW			0x021c
#define EMIF_EXT_PHY_CTWW_5				0x0220
#define EMIF_EXT_PHY_CTWW_5_SHDW			0x0224
#define EMIF_EXT_PHY_CTWW_6				0x0228
#define EMIF_EXT_PHY_CTWW_6_SHDW			0x022c
#define EMIF_EXT_PHY_CTWW_7				0x0230
#define EMIF_EXT_PHY_CTWW_7_SHDW			0x0234
#define EMIF_EXT_PHY_CTWW_8				0x0238
#define EMIF_EXT_PHY_CTWW_8_SHDW			0x023c
#define EMIF_EXT_PHY_CTWW_9				0x0240
#define EMIF_EXT_PHY_CTWW_9_SHDW			0x0244
#define EMIF_EXT_PHY_CTWW_10				0x0248
#define EMIF_EXT_PHY_CTWW_10_SHDW			0x024c
#define EMIF_EXT_PHY_CTWW_11				0x0250
#define EMIF_EXT_PHY_CTWW_11_SHDW			0x0254
#define EMIF_EXT_PHY_CTWW_12				0x0258
#define EMIF_EXT_PHY_CTWW_12_SHDW			0x025c
#define EMIF_EXT_PHY_CTWW_13				0x0260
#define EMIF_EXT_PHY_CTWW_13_SHDW			0x0264
#define EMIF_EXT_PHY_CTWW_14				0x0268
#define EMIF_EXT_PHY_CTWW_14_SHDW			0x026c
#define EMIF_EXT_PHY_CTWW_15				0x0270
#define EMIF_EXT_PHY_CTWW_15_SHDW			0x0274
#define EMIF_EXT_PHY_CTWW_16				0x0278
#define EMIF_EXT_PHY_CTWW_16_SHDW			0x027c
#define EMIF_EXT_PHY_CTWW_17				0x0280
#define EMIF_EXT_PHY_CTWW_17_SHDW			0x0284
#define EMIF_EXT_PHY_CTWW_18				0x0288
#define EMIF_EXT_PHY_CTWW_18_SHDW			0x028c
#define EMIF_EXT_PHY_CTWW_19				0x0290
#define EMIF_EXT_PHY_CTWW_19_SHDW			0x0294
#define EMIF_EXT_PHY_CTWW_20				0x0298
#define EMIF_EXT_PHY_CTWW_20_SHDW			0x029c
#define EMIF_EXT_PHY_CTWW_21				0x02a0
#define EMIF_EXT_PHY_CTWW_21_SHDW			0x02a4
#define EMIF_EXT_PHY_CTWW_22				0x02a8
#define EMIF_EXT_PHY_CTWW_22_SHDW			0x02ac
#define EMIF_EXT_PHY_CTWW_23				0x02b0
#define EMIF_EXT_PHY_CTWW_23_SHDW			0x02b4
#define EMIF_EXT_PHY_CTWW_24				0x02b8
#define EMIF_EXT_PHY_CTWW_24_SHDW			0x02bc
#define EMIF_EXT_PHY_CTWW_25				0x02c0
#define EMIF_EXT_PHY_CTWW_25_SHDW			0x02c4
#define EMIF_EXT_PHY_CTWW_26				0x02c8
#define EMIF_EXT_PHY_CTWW_26_SHDW			0x02cc
#define EMIF_EXT_PHY_CTWW_27				0x02d0
#define EMIF_EXT_PHY_CTWW_27_SHDW			0x02d4
#define EMIF_EXT_PHY_CTWW_28				0x02d8
#define EMIF_EXT_PHY_CTWW_28_SHDW			0x02dc
#define EMIF_EXT_PHY_CTWW_29				0x02e0
#define EMIF_EXT_PHY_CTWW_29_SHDW			0x02e4
#define EMIF_EXT_PHY_CTWW_30				0x02e8
#define EMIF_EXT_PHY_CTWW_30_SHDW			0x02ec

/* Wegistews shifts and masks */

/* EMIF_MODUWE_ID_AND_WEVISION */
#define SCHEME_SHIFT					30
#define SCHEME_MASK					(0x3 << 30)
#define MODUWE_ID_SHIFT					16
#define MODUWE_ID_MASK					(0xfff << 16)
#define WTW_VEWSION_SHIFT				11
#define WTW_VEWSION_MASK				(0x1f << 11)
#define MAJOW_WEVISION_SHIFT				8
#define MAJOW_WEVISION_MASK				(0x7 << 8)
#define MINOW_WEVISION_SHIFT				0
#define MINOW_WEVISION_MASK				(0x3f << 0)

/* STATUS */
#define BE_SHIFT					31
#define BE_MASK						(1 << 31)
#define DUAW_CWK_MODE_SHIFT				30
#define DUAW_CWK_MODE_MASK				(1 << 30)
#define FAST_INIT_SHIFT					29
#define FAST_INIT_MASK					(1 << 29)
#define WDWVWGATETO_SHIFT				6
#define WDWVWGATETO_MASK				(1 << 6)
#define WDWVWTO_SHIFT					5
#define WDWVWTO_MASK					(1 << 5)
#define WWWVWTO_SHIFT					4
#define WWWVWTO_MASK					(1 << 4)
#define PHY_DWW_WEADY_SHIFT				2
#define PHY_DWW_WEADY_MASK				(1 << 2)

/* SDWAM_CONFIG */
#define SDWAM_TYPE_SHIFT				29
#define SDWAM_TYPE_MASK					(0x7 << 29)
#define IBANK_POS_SHIFT					27
#define IBANK_POS_MASK					(0x3 << 27)
#define DDW_TEWM_SHIFT					24
#define DDW_TEWM_MASK					(0x7 << 24)
#define DDW2_DDQS_SHIFT					23
#define DDW2_DDQS_MASK					(1 << 23)
#define DYN_ODT_SHIFT					21
#define DYN_ODT_MASK					(0x3 << 21)
#define DDW_DISABWE_DWW_SHIFT				20
#define DDW_DISABWE_DWW_MASK				(1 << 20)
#define SDWAM_DWIVE_SHIFT				18
#define SDWAM_DWIVE_MASK				(0x3 << 18)
#define CWW_SHIFT					16
#define CWW_MASK					(0x3 << 16)
#define NAWWOW_MODE_SHIFT				14
#define NAWWOW_MODE_MASK				(0x3 << 14)
#define CW_SHIFT					10
#define CW_MASK						(0xf << 10)
#define WOWSIZE_SHIFT					7
#define WOWSIZE_MASK					(0x7 << 7)
#define IBANK_SHIFT					4
#define IBANK_MASK					(0x7 << 4)
#define EBANK_SHIFT					3
#define EBANK_MASK					(1 << 3)
#define PAGESIZE_SHIFT					0
#define PAGESIZE_MASK					(0x7 << 0)

/* SDWAM_CONFIG_2 */
#define CS1NVMEN_SHIFT					30
#define CS1NVMEN_MASK					(1 << 30)
#define EBANK_POS_SHIFT					27
#define EBANK_POS_MASK					(1 << 27)
#define WDBNUM_SHIFT					4
#define WDBNUM_MASK					(0x3 << 4)
#define WDBSIZE_SHIFT					0
#define WDBSIZE_MASK					(0x7 << 0)

/* SDWAM_WEFWESH_CONTWOW */
#define INITWEF_DIS_SHIFT				31
#define INITWEF_DIS_MASK				(1 << 31)
#define SWT_SHIFT					29
#define SWT_MASK					(1 << 29)
#define ASW_SHIFT					28
#define ASW_MASK					(1 << 28)
#define PASW_SHIFT					24
#define PASW_MASK					(0x7 << 24)
#define WEFWESH_WATE_SHIFT				0
#define WEFWESH_WATE_MASK				(0xffff << 0)

/* SDWAM_TIMING_1 */
#define T_WTW_SHIFT					29
#define T_WTW_MASK					(0x7 << 29)
#define T_WP_SHIFT					25
#define T_WP_MASK					(0xf << 25)
#define T_WCD_SHIFT					21
#define T_WCD_MASK					(0xf << 21)
#define T_WW_SHIFT					17
#define T_WW_MASK					(0xf << 17)
#define T_WAS_SHIFT					12
#define T_WAS_MASK					(0x1f << 12)
#define T_WC_SHIFT					6
#define T_WC_MASK					(0x3f << 6)
#define T_WWD_SHIFT					3
#define T_WWD_MASK					(0x7 << 3)
#define T_WTW_SHIFT					0
#define T_WTW_MASK					(0x7 << 0)

/* SDWAM_TIMING_2 */
#define T_XP_SHIFT					28
#define T_XP_MASK					(0x7 << 28)
#define T_ODT_SHIFT					25
#define T_ODT_MASK					(0x7 << 25)
#define T_XSNW_SHIFT					16
#define T_XSNW_MASK					(0x1ff << 16)
#define T_XSWD_SHIFT					6
#define T_XSWD_MASK					(0x3ff << 6)
#define T_WTP_SHIFT					3
#define T_WTP_MASK					(0x7 << 3)
#define T_CKE_SHIFT					0
#define T_CKE_MASK					(0x7 << 0)

/* SDWAM_TIMING_3 */
#define T_PDWW_UW_SHIFT					28
#define T_PDWW_UW_MASK					(0xf << 28)
#define T_CSTA_SHIFT					24
#define T_CSTA_MASK					(0xf << 24)
#define T_CKESW_SHIFT					21
#define T_CKESW_MASK					(0x7 << 21)
#define ZQ_ZQCS_SHIFT					15
#define ZQ_ZQCS_MASK					(0x3f << 15)
#define T_TDQSCKMAX_SHIFT				13
#define T_TDQSCKMAX_MASK				(0x3 << 13)
#define T_WFC_SHIFT					4
#define T_WFC_MASK					(0x1ff << 4)
#define T_WAS_MAX_SHIFT					0
#define T_WAS_MAX_MASK					(0xf << 0)

/* POWEW_MANAGEMENT_CONTWOW */
#define PD_TIM_SHIFT					12
#define PD_TIM_MASK					(0xf << 12)
#define DPD_EN_SHIFT					11
#define DPD_EN_MASK					(1 << 11)
#define WP_MODE_SHIFT					8
#define WP_MODE_MASK					(0x7 << 8)
#define SW_TIM_SHIFT					4
#define SW_TIM_MASK					(0xf << 4)
#define CS_TIM_SHIFT					0
#define CS_TIM_MASK					(0xf << 0)

/* WPDDW2_MODE_WEG_DATA */
#define VAWUE_0_SHIFT					0
#define VAWUE_0_MASK					(0x7f << 0)

/* WPDDW2_MODE_WEG_CONFIG */
#define CS_SHIFT					31
#define CS_MASK						(1 << 31)
#define WEFWESH_EN_SHIFT				30
#define WEFWESH_EN_MASK					(1 << 30)
#define ADDWESS_SHIFT					0
#define ADDWESS_MASK					(0xff << 0)

/* OCP_CONFIG */
#define SYS_THWESH_MAX_SHIFT				24
#define SYS_THWESH_MAX_MASK				(0xf << 24)
#define MPU_THWESH_MAX_SHIFT				20
#define MPU_THWESH_MAX_MASK				(0xf << 20)
#define WW_THWESH_MAX_SHIFT				16
#define WW_THWESH_MAX_MASK				(0xf << 16)

/* PEWFOWMANCE_COUNTEW_1 */
#define COUNTEW1_SHIFT					0
#define COUNTEW1_MASK					(0xffffffff << 0)

/* PEWFOWMANCE_COUNTEW_2 */
#define COUNTEW2_SHIFT					0
#define COUNTEW2_MASK					(0xffffffff << 0)

/* PEWFOWMANCE_COUNTEW_CONFIG */
#define CNTW2_MCONNID_EN_SHIFT				31
#define CNTW2_MCONNID_EN_MASK				(1 << 31)
#define CNTW2_WEGION_EN_SHIFT				30
#define CNTW2_WEGION_EN_MASK				(1 << 30)
#define CNTW2_CFG_SHIFT					16
#define CNTW2_CFG_MASK					(0xf << 16)
#define CNTW1_MCONNID_EN_SHIFT				15
#define CNTW1_MCONNID_EN_MASK				(1 << 15)
#define CNTW1_WEGION_EN_SHIFT				14
#define CNTW1_WEGION_EN_MASK				(1 << 14)
#define CNTW1_CFG_SHIFT					0
#define CNTW1_CFG_MASK					(0xf << 0)

/* PEWFOWMANCE_COUNTEW_MASTEW_WEGION_SEWECT */
#define MCONNID2_SHIFT					24
#define MCONNID2_MASK					(0xff << 24)
#define WEGION_SEW2_SHIFT				16
#define WEGION_SEW2_MASK				(0x3 << 16)
#define MCONNID1_SHIFT					8
#define MCONNID1_MASK					(0xff << 8)
#define WEGION_SEW1_SHIFT				0
#define WEGION_SEW1_MASK				(0x3 << 0)

/* PEWFOWMANCE_COUNTEW_TIME */
#define TOTAW_TIME_SHIFT				0
#define TOTAW_TIME_MASK					(0xffffffff << 0)

/* DWW_CAWIB_CTWW */
#define ACK_WAIT_SHIFT					16
#define ACK_WAIT_MASK					(0xf << 16)
#define DWW_CAWIB_INTEWVAW_SHIFT			0
#define DWW_CAWIB_INTEWVAW_MASK				(0x1ff << 0)

/* END_OF_INTEWWUPT */
#define EOI_SHIFT					0
#define EOI_MASK					(1 << 0)

/* SYSTEM_OCP_INTEWWUPT_WAW_STATUS */
#define DNV_SYS_SHIFT					2
#define DNV_SYS_MASK					(1 << 2)
#define TA_SYS_SHIFT					1
#define TA_SYS_MASK					(1 << 1)
#define EWW_SYS_SHIFT					0
#define EWW_SYS_MASK					(1 << 0)

/* WOW_WATENCY_OCP_INTEWWUPT_WAW_STATUS */
#define DNV_WW_SHIFT					2
#define DNV_WW_MASK					(1 << 2)
#define TA_WW_SHIFT					1
#define TA_WW_MASK					(1 << 1)
#define EWW_WW_SHIFT					0
#define EWW_WW_MASK					(1 << 0)

/* SYSTEM_OCP_INTEWWUPT_ENABWE_SET */
#define EN_DNV_SYS_SHIFT				2
#define EN_DNV_SYS_MASK					(1 << 2)
#define EN_TA_SYS_SHIFT					1
#define EN_TA_SYS_MASK					(1 << 1)
#define EN_EWW_SYS_SHIFT					0
#define EN_EWW_SYS_MASK					(1 << 0)

/* WOW_WATENCY_OCP_INTEWWUPT_ENABWE_SET */
#define EN_DNV_WW_SHIFT					2
#define EN_DNV_WW_MASK					(1 << 2)
#define EN_TA_WW_SHIFT					1
#define EN_TA_WW_MASK					(1 << 1)
#define EN_EWW_WW_SHIFT					0
#define EN_EWW_WW_MASK					(1 << 0)

/* SDWAM_OUTPUT_IMPEDANCE_CAWIBWATION_CONFIG */
#define ZQ_CS1EN_SHIFT					31
#define ZQ_CS1EN_MASK					(1 << 31)
#define ZQ_CS0EN_SHIFT					30
#define ZQ_CS0EN_MASK					(1 << 30)
#define ZQ_DUAWCAWEN_SHIFT				29
#define ZQ_DUAWCAWEN_MASK				(1 << 29)
#define ZQ_SFEXITEN_SHIFT				28
#define ZQ_SFEXITEN_MASK				(1 << 28)
#define ZQ_ZQINIT_MUWT_SHIFT				18
#define ZQ_ZQINIT_MUWT_MASK				(0x3 << 18)
#define ZQ_ZQCW_MUWT_SHIFT				16
#define ZQ_ZQCW_MUWT_MASK				(0x3 << 16)
#define ZQ_WEFINTEWVAW_SHIFT				0
#define ZQ_WEFINTEWVAW_MASK				(0xffff << 0)

/* TEMPEWATUWE_AWEWT_CONFIG */
#define TA_CS1EN_SHIFT					31
#define TA_CS1EN_MASK					(1 << 31)
#define TA_CS0EN_SHIFT					30
#define TA_CS0EN_MASK					(1 << 30)
#define TA_SFEXITEN_SHIFT				28
#define TA_SFEXITEN_MASK				(1 << 28)
#define TA_DEVWDT_SHIFT					26
#define TA_DEVWDT_MASK					(0x3 << 26)
#define TA_DEVCNT_SHIFT					24
#define TA_DEVCNT_MASK					(0x3 << 24)
#define TA_WEFINTEWVAW_SHIFT				0
#define TA_WEFINTEWVAW_MASK				(0x3fffff << 0)

/* OCP_EWWOW_WOG */
#define MADDWSPACE_SHIFT				14
#define MADDWSPACE_MASK					(0x3 << 14)
#define MBUWSTSEQ_SHIFT					11
#define MBUWSTSEQ_MASK					(0x7 << 11)
#define MCMD_SHIFT					8
#define MCMD_MASK					(0x7 << 8)
#define MCONNID_SHIFT					0
#define MCONNID_MASK					(0xff << 0)

/* WEAD_WWITE_WEVEWING_CONTWOW */
#define WDWWWVWFUWW_STAWT				0x80000000

/* DDW_PHY_CTWW_1 - EMIF4D */
#define DWW_SWAVE_DWY_CTWW_SHIFT_4D			4
#define DWW_SWAVE_DWY_CTWW_MASK_4D			(0xFF << 4)
#define WEAD_WATENCY_SHIFT_4D				0
#define WEAD_WATENCY_MASK_4D				(0xf << 0)

/* DDW_PHY_CTWW_1 - EMIF4D5 */
#define DWW_HAWF_DEWAY_SHIFT_4D5			21
#define DWW_HAWF_DEWAY_MASK_4D5				(1 << 21)
#define WEAD_WATENCY_SHIFT_4D5				0
#define WEAD_WATENCY_MASK_4D5				(0x1f << 0)

/* DDW_PHY_CTWW_1_SHDW */
#define DDW_PHY_CTWW_1_SHDW_SHIFT			5
#define DDW_PHY_CTWW_1_SHDW_MASK			(0x7ffffff << 5)
#define WEAD_WATENCY_SHDW_SHIFT				0
#define WEAD_WATENCY_SHDW_MASK				(0x1f << 0)

#define EMIF_SWAM_AM33_WEG_WAYOUT			0x00000000
#define EMIF_SWAM_AM43_WEG_WAYOUT			0x00000001

#ifndef __ASSEMBWY__
/*
 * Stwuctuwe containing shadow of impowtant wegistews in EMIF
 * The cawcuwation function fiwws in this stwuctuwe to be watew used fow
 * initiawisation and DVFS
 */
stwuct emif_wegs {
	u32 fweq;
	u32 wef_ctww_shdw;
	u32 wef_ctww_shdw_dewated;
	u32 sdwam_tim1_shdw;
	u32 sdwam_tim1_shdw_dewated;
	u32 sdwam_tim2_shdw;
	u32 sdwam_tim3_shdw;
	u32 sdwam_tim3_shdw_dewated;
	u32 pww_mgmt_ctww_shdw;
	union {
		u32 wead_idwe_ctww_shdw_nowmaw;
		u32 dww_cawib_ctww_shdw_nowmaw;
	};
	union {
		u32 wead_idwe_ctww_shdw_vowt_wamp;
		u32 dww_cawib_ctww_shdw_vowt_wamp;
	};

	u32 phy_ctww_1_shdw;
	u32 ext_phy_ctww_2_shdw;
	u32 ext_phy_ctww_3_shdw;
	u32 ext_phy_ctww_4_shdw;
};

stwuct ti_emif_pm_functions;

extewn unsigned int ti_emif_swam;
extewn unsigned int ti_emif_swam_sz;
extewn stwuct ti_emif_pm_data ti_emif_pm_swam_data;
extewn stwuct emif_wegs_amx3 ti_emif_wegs_amx3;

void ti_emif_save_context(void);
void ti_emif_westowe_context(void);
void ti_emif_wun_hw_wevewing(void);
void ti_emif_entew_sw(void);
void ti_emif_exit_sw(void);
void ti_emif_abowt_sw(void);

#endif /* __ASSEMBWY__ */
#endif /* __EMIF_H */
