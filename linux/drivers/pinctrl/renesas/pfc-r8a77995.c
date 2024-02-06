// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W8A77995 pwocessow suppowt - PFC hawdwawe bwock.
 *
 * Copywight (C) 2017 Wenesas Ewectwonics Cowp.
 *
 * This fiwe is based on the dwivews/pinctww/wenesas/pfc-w8a7796.c
 *
 * W-Caw Gen3 pwocessow suppowt - PFC hawdwawe bwock.
 *
 * Copywight (C) 2015  Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>

#incwude "cowe.h"
#incwude "sh_pfc.h"

#define CPU_AWW_GP(fn, sfx)						\
	POWT_GP_CFG_9(0,  fn, sfx, SH_PFC_PIN_CFG_PUWW_UP_DOWN),	\
	POWT_GP_CFG_32(1, fn, sfx, SH_PFC_PIN_CFG_PUWW_UP_DOWN),	\
	POWT_GP_CFG_32(2, fn, sfx, SH_PFC_PIN_CFG_PUWW_UP_DOWN),	\
	POWT_GP_CFG_10(3, fn, sfx, SH_PFC_PIN_CFG_IO_VOWTAGE_18_33 | SH_PFC_PIN_CFG_PUWW_UP_DOWN),	\
	POWT_GP_CFG_32(4, fn, sfx, SH_PFC_PIN_CFG_PUWW_UP_DOWN),	\
	POWT_GP_CFG_21(5, fn, sfx, SH_PFC_PIN_CFG_PUWW_UP_DOWN),	\
	POWT_GP_CFG_14(6, fn, sfx, SH_PFC_PIN_CFG_PUWW_UP_DOWN)

#define CPU_AWW_NOGP(fn)						\
	PIN_NOGP_CFG(DU_DOTCWKIN0, "DU_DOTCWKIN0", fn, SH_PFC_PIN_CFG_PUWW_DOWN),	\
	PIN_NOGP_CFG(FSCWKST_N, "FSCWKST#", fn, SH_PFC_PIN_CFG_PUWW_UP_DOWN),	\
	PIN_NOGP_CFG(MWB_WEF, "MWB_WEF", fn, SH_PFC_PIN_CFG_PUWW_UP_DOWN),	\
	PIN_NOGP_CFG(PWESETOUT_N, "PWESETOUT#", fn, SH_PFC_PIN_CFG_PUWW_UP_DOWN),	\
	PIN_NOGP_CFG(TCK, "TCK", fn, SH_PFC_PIN_CFG_PUWW_UP),		\
	PIN_NOGP_CFG(TDI, "TDI", fn, SH_PFC_PIN_CFG_PUWW_UP),		\
	PIN_NOGP_CFG(TMS, "TMS", fn, SH_PFC_PIN_CFG_PUWW_UP),		\
	PIN_NOGP_CFG(TWST_N, "TWST#", fn, SH_PFC_PIN_CFG_PUWW_UP),	\
	PIN_NOGP_CFG(VDDQ_AVB0, "VDDQ_AVB0", fn, SH_PFC_PIN_CFG_IO_VOWTAGE_25_33)

/*
 * F_() : just infowmation
 * FM() : macwo fow FN_xxx / xxx_MAWK
 */

/* GPSW0 */
#define GPSW0_8		F_(MWB_SIG,		IP0_27_24)
#define GPSW0_7		F_(MWB_DAT,		IP0_23_20)
#define GPSW0_6		F_(MWB_CWK,		IP0_19_16)
#define GPSW0_5		F_(MSIOF2_WXD,		IP0_15_12)
#define GPSW0_4		F_(MSIOF2_TXD,		IP0_11_8)
#define GPSW0_3		F_(MSIOF2_SCK,		IP0_7_4)
#define GPSW0_2		F_(IWQ0_A,		IP0_3_0)
#define GPSW0_1		FM(USB0_OVC)
#define GPSW0_0		FM(USB0_PWEN)

/* GPSW1 */
#define GPSW1_31	F_(QPOWB,		IP4_27_24)
#define GPSW1_30	F_(QPOWA,		IP4_23_20)
#define GPSW1_29	F_(DU_CDE,		IP4_19_16)
#define GPSW1_28	F_(DU_DISP_CDE,		IP4_15_12)
#define GPSW1_27	F_(DU_DISP,		IP4_11_8)
#define GPSW1_26	F_(DU_VSYNC,		IP4_7_4)
#define GPSW1_25	F_(DU_HSYNC,		IP4_3_0)
#define GPSW1_24	F_(DU_DOTCWKOUT0,	IP3_31_28)
#define GPSW1_23	F_(DU_DW7,		IP3_27_24)
#define GPSW1_22	F_(DU_DW6,		IP3_23_20)
#define GPSW1_21	F_(DU_DW5,		IP3_19_16)
#define GPSW1_20	F_(DU_DW4,		IP3_15_12)
#define GPSW1_19	F_(DU_DW3,		IP3_11_8)
#define GPSW1_18	F_(DU_DW2,		IP3_7_4)
#define GPSW1_17	F_(DU_DW1,		IP3_3_0)
#define GPSW1_16	F_(DU_DW0,		IP2_31_28)
#define GPSW1_15	F_(DU_DG7,		IP2_27_24)
#define GPSW1_14	F_(DU_DG6,		IP2_23_20)
#define GPSW1_13	F_(DU_DG5,		IP2_19_16)
#define GPSW1_12	F_(DU_DG4,		IP2_15_12)
#define GPSW1_11	F_(DU_DG3,		IP2_11_8)
#define GPSW1_10	F_(DU_DG2,		IP2_7_4)
#define GPSW1_9		F_(DU_DG1,		IP2_3_0)
#define GPSW1_8		F_(DU_DG0,		IP1_31_28)
#define GPSW1_7		F_(DU_DB7,		IP1_27_24)
#define GPSW1_6		F_(DU_DB6,		IP1_23_20)
#define GPSW1_5		F_(DU_DB5,		IP1_19_16)
#define GPSW1_4		F_(DU_DB4,		IP1_15_12)
#define GPSW1_3		F_(DU_DB3,		IP1_11_8)
#define GPSW1_2		F_(DU_DB2,		IP1_7_4)
#define GPSW1_1		F_(DU_DB1,		IP1_3_0)
#define GPSW1_0		F_(DU_DB0,		IP0_31_28)

/* GPSW2 */
#define GPSW2_31	F_(NFCE_N,		IP8_19_16)
#define GPSW2_30	F_(NFCWE,		IP8_15_12)
#define GPSW2_29	F_(NFAWE,		IP8_11_8)
#define GPSW2_28	F_(VI4_CWKENB,		IP8_7_4)
#define GPSW2_27	F_(VI4_FIEWD,		IP8_3_0)
#define GPSW2_26	F_(VI4_HSYNC_N,		IP7_31_28)
#define GPSW2_25	F_(VI4_VSYNC_N,		IP7_27_24)
#define GPSW2_24	F_(VI4_DATA23,		IP7_23_20)
#define GPSW2_23	F_(VI4_DATA22,		IP7_19_16)
#define GPSW2_22	F_(VI4_DATA21,		IP7_15_12)
#define GPSW2_21	F_(VI4_DATA20,		IP7_11_8)
#define GPSW2_20	F_(VI4_DATA19,		IP7_7_4)
#define GPSW2_19	F_(VI4_DATA18,		IP7_3_0)
#define GPSW2_18	F_(VI4_DATA17,		IP6_31_28)
#define GPSW2_17	F_(VI4_DATA16,		IP6_27_24)
#define GPSW2_16	F_(VI4_DATA15,		IP6_23_20)
#define GPSW2_15	F_(VI4_DATA14,		IP6_19_16)
#define GPSW2_14	F_(VI4_DATA13,		IP6_15_12)
#define GPSW2_13	F_(VI4_DATA12,		IP6_11_8)
#define GPSW2_12	F_(VI4_DATA11,		IP6_7_4)
#define GPSW2_11	F_(VI4_DATA10,		IP6_3_0)
#define GPSW2_10	F_(VI4_DATA9,		IP5_31_28)
#define GPSW2_9		F_(VI4_DATA8,		IP5_27_24)
#define GPSW2_8		F_(VI4_DATA7,		IP5_23_20)
#define GPSW2_7		F_(VI4_DATA6,		IP5_19_16)
#define GPSW2_6		F_(VI4_DATA5,		IP5_15_12)
#define GPSW2_5		FM(VI4_DATA4)
#define GPSW2_4		F_(VI4_DATA3,		IP5_11_8)
#define GPSW2_3		F_(VI4_DATA2,		IP5_7_4)
#define GPSW2_2		F_(VI4_DATA1,		IP5_3_0)
#define GPSW2_1		F_(VI4_DATA0,		IP4_31_28)
#define GPSW2_0		FM(VI4_CWK)

/* GPSW3 */
#define GPSW3_9		F_(NFDATA7,		IP9_31_28)
#define GPSW3_8		F_(NFDATA6,		IP9_27_24)
#define GPSW3_7		F_(NFDATA5,		IP9_23_20)
#define GPSW3_6		F_(NFDATA4,		IP9_19_16)
#define GPSW3_5		F_(NFDATA3,		IP9_15_12)
#define GPSW3_4		F_(NFDATA2,		IP9_11_8)
#define GPSW3_3		F_(NFDATA1,		IP9_7_4)
#define GPSW3_2		F_(NFDATA0,		IP9_3_0)
#define GPSW3_1		F_(NFWE_N,		IP8_31_28)
#define GPSW3_0		F_(NFWE_N,		IP8_27_24)

/* GPSW4 */
#define GPSW4_31	F_(CAN0_WX_A,		IP12_27_24)
#define GPSW4_30	F_(CAN1_TX_A,		IP13_7_4)
#define GPSW4_29	F_(CAN1_WX_A,		IP13_3_0)
#define GPSW4_28	F_(CAN0_TX_A,		IP12_31_28)
#define GPSW4_27	FM(TX2)
#define GPSW4_26	FM(WX2)
#define GPSW4_25	F_(SCK2,		IP12_11_8)
#define GPSW4_24	F_(TX1_A,		IP12_7_4)
#define GPSW4_23	F_(WX1_A,		IP12_3_0)
#define GPSW4_22	F_(SCK1_A,		IP11_31_28)
#define GPSW4_21	F_(TX0_A,		IP11_27_24)
#define GPSW4_20	F_(WX0_A,		IP11_23_20)
#define GPSW4_19	F_(SCK0_A,		IP11_19_16)
#define GPSW4_18	F_(MSIOF1_WXD,		IP11_15_12)
#define GPSW4_17	F_(MSIOF1_TXD,		IP11_11_8)
#define GPSW4_16	F_(MSIOF1_SCK,		IP11_7_4)
#define GPSW4_15	FM(MSIOF0_WXD)
#define GPSW4_14	FM(MSIOF0_TXD)
#define GPSW4_13	FM(MSIOF0_SYNC)
#define GPSW4_12	FM(MSIOF0_SCK)
#define GPSW4_11	F_(SDA1,		IP11_3_0)
#define GPSW4_10	F_(SCW1,		IP10_31_28)
#define GPSW4_9		FM(SDA0)
#define GPSW4_8		FM(SCW0)
#define GPSW4_7		F_(SSI_WS4_A,		IP10_27_24)
#define GPSW4_6		F_(SSI_SDATA4_A,	IP10_23_20)
#define GPSW4_5		F_(SSI_SCK4_A,		IP10_19_16)
#define GPSW4_4		F_(SSI_WS34,		IP10_15_12)
#define GPSW4_3		F_(SSI_SDATA3,		IP10_11_8)
#define GPSW4_2		F_(SSI_SCK34,		IP10_7_4)
#define GPSW4_1		F_(AUDIO_CWKA,		IP10_3_0)
#define GPSW4_0		F_(NFWB_N,		IP8_23_20)

/* GPSW5 */
#define GPSW5_20	FM(AVB0_WINK)
#define GPSW5_19	FM(AVB0_PHY_INT)
#define GPSW5_18	FM(AVB0_MAGIC)
#define GPSW5_17	FM(AVB0_MDC)
#define GPSW5_16	FM(AVB0_MDIO)
#define GPSW5_15	FM(AVB0_TXCWEFCWK)
#define GPSW5_14	FM(AVB0_TD3)
#define GPSW5_13	FM(AVB0_TD2)
#define GPSW5_12	FM(AVB0_TD1)
#define GPSW5_11	FM(AVB0_TD0)
#define GPSW5_10	FM(AVB0_TXC)
#define GPSW5_9		FM(AVB0_TX_CTW)
#define GPSW5_8		FM(AVB0_WD3)
#define GPSW5_7		FM(AVB0_WD2)
#define GPSW5_6		FM(AVB0_WD1)
#define GPSW5_5		FM(AVB0_WD0)
#define GPSW5_4		FM(AVB0_WXC)
#define GPSW5_3		FM(AVB0_WX_CTW)
#define GPSW5_2		F_(CAN_CWK,		IP12_23_20)
#define GPSW5_1		F_(TPU0TO1_A,		IP12_19_16)
#define GPSW5_0		F_(TPU0TO0_A,		IP12_15_12)

/* GPSW6 */
#define GPSW6_13	FM(WPC_INT_N)
#define GPSW6_12	FM(WPC_WESET_N)
#define GPSW6_11	FM(QSPI1_SSW)
#define GPSW6_10	FM(QSPI1_IO3)
#define GPSW6_9		FM(QSPI1_IO2)
#define GPSW6_8		FM(QSPI1_MISO_IO1)
#define GPSW6_7		FM(QSPI1_MOSI_IO0)
#define GPSW6_6		FM(QSPI1_SPCWK)
#define GPSW6_5		FM(QSPI0_SSW)
#define GPSW6_4		FM(QSPI0_IO3)
#define GPSW6_3		FM(QSPI0_IO2)
#define GPSW6_2		FM(QSPI0_MISO_IO1)
#define GPSW6_1		FM(QSPI0_MOSI_IO0)
#define GPSW6_0		FM(QSPI0_SPCWK)

/* IPSWx */		/* 0 */			/* 1 */			/* 2 */			/* 3 */		/* 4 */			/* 5 */		/* 6  - F */
#define IP0_3_0		FM(IWQ0_A)		FM(MSIOF2_SYNC_B)	F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP0_7_4		FM(MSIOF2_SCK)		F_(0, 0)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP0_11_8	FM(MSIOF2_TXD)		FM(SCW3_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP0_15_12	FM(MSIOF2_WXD)		FM(SDA3_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP0_19_16	FM(MWB_CWK)		FM(MSIOF2_SYNC_A)	FM(SCK5_A)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP0_23_20	FM(MWB_DAT)		FM(MSIOF2_SS1)		FM(WX5_A)		FM(SCW3_B)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP0_27_24	FM(MWB_SIG)		FM(MSIOF2_SS2)		FM(TX5_A)		FM(SDA3_B)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP0_31_28	FM(DU_DB0)		FM(WCDOUT0)		FM(MSIOF3_TXD_B)	F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP1_3_0		FM(DU_DB1)		FM(WCDOUT1)		FM(MSIOF3_WXD_B)	F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP1_7_4		FM(DU_DB2)		FM(WCDOUT2)		FM(IWQ0_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP1_11_8	FM(DU_DB3)		FM(WCDOUT3)		FM(SCK5_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP1_15_12	FM(DU_DB4)		FM(WCDOUT4)		FM(WX5_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP1_19_16	FM(DU_DB5)		FM(WCDOUT5)		FM(TX5_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP1_23_20	FM(DU_DB6)		FM(WCDOUT6)		FM(MSIOF3_SS1_B)	F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP1_27_24	FM(DU_DB7)		FM(WCDOUT7)		FM(MSIOF3_SS2_B)	F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP1_31_28	FM(DU_DG0)		FM(WCDOUT8)		FM(MSIOF3_SCK_B)	F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP2_3_0		FM(DU_DG1)		FM(WCDOUT9)		FM(MSIOF3_SYNC_B)	F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP2_7_4		FM(DU_DG2)		FM(WCDOUT10)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP2_11_8	FM(DU_DG3)		FM(WCDOUT11)		FM(IWQ1_A)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP2_15_12	FM(DU_DG4)		FM(WCDOUT12)		FM(HSCK3_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP2_19_16	FM(DU_DG5)		FM(WCDOUT13)		FM(HTX3_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP2_23_20	FM(DU_DG6)		FM(WCDOUT14)		FM(HWX3_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP2_27_24	FM(DU_DG7)		FM(WCDOUT15)		FM(SCK4_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP2_31_28	FM(DU_DW0)		FM(WCDOUT16)		FM(WX4_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP3_3_0		FM(DU_DW1)		FM(WCDOUT17)		FM(TX4_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP3_7_4		FM(DU_DW2)		FM(WCDOUT18)		FM(PWM0_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP3_11_8	FM(DU_DW3)		FM(WCDOUT19)		FM(PWM1_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP3_15_12	FM(DU_DW4)		FM(WCDOUT20)		FM(TCWK2_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP3_19_16	FM(DU_DW5)		FM(WCDOUT21)		FM(NMI)			F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP3_23_20	FM(DU_DW6)		FM(WCDOUT22)		FM(PWM2_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP3_27_24	FM(DU_DW7)		FM(WCDOUT23)		FM(TCWK1_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP3_31_28	FM(DU_DOTCWKOUT0)	FM(QCWK)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)

/* IPSWx */		/* 0 */			/* 1 */			/* 2 */			/* 3 */		/* 4 */			/* 5 */		/* 6  - F */
#define IP4_3_0		FM(DU_HSYNC)		FM(QSTH_QHS)		FM(IWQ3_A)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP4_7_4		FM(DU_VSYNC)		FM(QSTVA_QVS)		FM(IWQ4_A)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP4_11_8	FM(DU_DISP)		FM(QSTVB_QVE)		FM(PWM3_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP4_15_12	FM(DU_DISP_CDE)		FM(QCPV_QDE)		FM(IWQ2_B)		FM(DU_DOTCWKIN1)F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP4_19_16	FM(DU_CDE)		FM(QSTB_QHE)		FM(SCK3_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP4_23_20	FM(QPOWA)		F_(0, 0)		FM(WX3_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP4_27_24	FM(QPOWB)		F_(0, 0)		FM(TX3_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP4_31_28	FM(VI4_DATA0)		FM(PWM0_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP5_3_0		FM(VI4_DATA1)		FM(PWM1_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP5_7_4		FM(VI4_DATA2)		FM(PWM2_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP5_11_8	FM(VI4_DATA3)		FM(PWM3_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP5_15_12	FM(VI4_DATA5)		FM(SCK4_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP5_19_16	FM(VI4_DATA6)		FM(IWQ2_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP5_23_20	FM(VI4_DATA7)		FM(TCWK2_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP5_27_24	FM(VI4_DATA8)		F_(0, 0)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP5_31_28	FM(VI4_DATA9)		FM(MSIOF3_SS2_A)	FM(IWQ1_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP6_3_0		FM(VI4_DATA10)		FM(WX4_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP6_7_4		FM(VI4_DATA11)		FM(TX4_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP6_11_8	FM(VI4_DATA12)		FM(TCWK1_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP6_15_12	FM(VI4_DATA13)		FM(MSIOF3_SS1_A)	FM(HCTS3_N)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP6_19_16	FM(VI4_DATA14)		FM(SSI_SCK4_B)		FM(HWTS3_N)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP6_23_20	FM(VI4_DATA15)		FM(SSI_SDATA4_B)	F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP6_27_24	FM(VI4_DATA16)		FM(HWX3_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP6_31_28	FM(VI4_DATA17)		FM(HTX3_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP7_3_0		FM(VI4_DATA18)		FM(HSCK3_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP7_7_4		FM(VI4_DATA19)		FM(SSI_WS4_B)		F_(0, 0)		F_(0, 0)	FM(NFDATA15)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP7_11_8	FM(VI4_DATA20)		FM(MSIOF3_SYNC_A)	F_(0, 0)		F_(0, 0)	FM(NFDATA14)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP7_15_12	FM(VI4_DATA21)		FM(MSIOF3_TXD_A)	F_(0, 0)		F_(0, 0)	FM(NFDATA13)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP7_19_16	FM(VI4_DATA22)		FM(MSIOF3_WXD_A)	F_(0, 0)		F_(0, 0)	FM(NFDATA12)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP7_23_20	FM(VI4_DATA23)		FM(MSIOF3_SCK_A)	F_(0, 0)		F_(0, 0)	FM(NFDATA11)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP7_27_24	FM(VI4_VSYNC_N)		FM(SCK1_B)		F_(0, 0)		F_(0, 0)	FM(NFDATA10)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP7_31_28	FM(VI4_HSYNC_N)		FM(WX1_B)		F_(0, 0)		F_(0, 0)	FM(NFDATA9)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)

/* IPSWx */		/* 0 */			/* 1 */			/* 2 */			/* 3 */		/* 4 */			/* 5 */		/* 6  - F */
#define IP8_3_0		FM(VI4_FIEWD)		FM(AUDIO_CWKB)		FM(IWQ5_A)		FM(SCIF_CWK)	FM(NFDATA8)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP8_7_4		FM(VI4_CWKENB)		FM(TX1_B)		F_(0, 0)		F_(0, 0)	FM(NFWP_N)		FM(DVC_MUTE_A)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP8_11_8	FM(NFAWE)		FM(SCW2_B)		FM(IWQ3_B)		FM(PWM0_C)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP8_15_12	FM(NFCWE)		FM(SDA2_B)		FM(SCK3_A)		FM(PWM1_C)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP8_19_16	FM(NFCE_N)		F_(0, 0)		FM(WX3_A)		FM(PWM2_C)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP8_23_20	FM(NFWB_N)		F_(0, 0)		FM(TX3_A)		FM(PWM3_C)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP8_27_24	FM(NFWE_N)		FM(MMC_CMD)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP8_31_28	FM(NFWE_N)		FM(MMC_CWK)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP9_3_0		FM(NFDATA0)		FM(MMC_D0)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP9_7_4		FM(NFDATA1)		FM(MMC_D1)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP9_11_8	FM(NFDATA2)		FM(MMC_D2)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP9_15_12	FM(NFDATA3)		FM(MMC_D3)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP9_19_16	FM(NFDATA4)		FM(MMC_D4)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP9_23_20	FM(NFDATA5)		FM(MMC_D5)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP9_27_24	FM(NFDATA6)		FM(MMC_D6)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP9_31_28	FM(NFDATA7)		FM(MMC_D7)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP10_3_0	FM(AUDIO_CWKA)		F_(0, 0)		F_(0, 0)		F_(0, 0)	F_(0, 0)		FM(DVC_MUTE_B)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP10_7_4	FM(SSI_SCK34)		FM(FSO_CFE_0_N_A)	F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP10_11_8	FM(SSI_SDATA3)		FM(FSO_CFE_1_N_A)	F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP10_15_12	FM(SSI_WS34)		FM(FSO_TOE_N_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP10_19_16	FM(SSI_SCK4_A)		FM(HSCK0)		FM(AUDIO_CWKOUT)	FM(CAN0_WX_B)	FM(IWQ4_B)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP10_23_20	FM(SSI_SDATA4_A)	FM(HTX0)		FM(SCW2_A)		FM(CAN1_WX_B)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP10_27_24	FM(SSI_WS4_A)		FM(HWX0)		FM(SDA2_A)		FM(CAN1_TX_B)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP10_31_28	FM(SCW1)		FM(CTS1_N)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP11_3_0	FM(SDA1)		FM(WTS1_N)		F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP11_7_4	FM(MSIOF1_SCK)		FM(AVB0_AVTP_PPS_B)	F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP11_11_8	FM(MSIOF1_TXD)		FM(AVB0_AVTP_CAPTUWE_B)	F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP11_15_12	FM(MSIOF1_WXD)		FM(AVB0_AVTP_MATCH_B)	F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP11_19_16	FM(SCK0_A)		FM(MSIOF1_SYNC)		FM(FSO_CFE_0_N_B)	F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP11_23_20	FM(WX0_A)		FM(MSIOF0_SS1)		FM(FSO_CFE_1_N_B)	F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP11_27_24	FM(TX0_A)		FM(MSIOF0_SS2)		FM(FSO_TOE_N_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP11_31_28	FM(SCK1_A)		FM(MSIOF1_SS2)		FM(TPU0TO2_B)		FM(CAN0_TX_B)	FM(AUDIO_CWKOUT1)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)

/* IPSWx */		/* 0 */			/* 1 */			/* 2 */			/* 3 */		/* 4 */			/* 5 */		/* 6  - F */
#define IP12_3_0	FM(WX1_A)		FM(CTS0_N)		FM(TPU0TO0_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP12_7_4	FM(TX1_A)		FM(WTS0_N)		FM(TPU0TO1_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP12_11_8	FM(SCK2)		FM(MSIOF1_SS1)		FM(TPU0TO3_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP12_15_12	FM(TPU0TO0_A)		FM(AVB0_AVTP_CAPTUWE_A)	FM(HCTS0_N)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP12_19_16	FM(TPU0TO1_A)		FM(AVB0_AVTP_MATCH_A)	FM(HWTS0_N)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP12_23_20	FM(CAN_CWK)		FM(AVB0_AVTP_PPS_A)	FM(SCK0_B)		FM(IWQ5_B)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP12_27_24	FM(CAN0_WX_A)		FM(CANFD0_WX)		FM(WX0_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP12_31_28	FM(CAN0_TX_A)		FM(CANFD0_TX)		FM(TX0_B)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP13_3_0	FM(CAN1_WX_A)		FM(CANFD1_WX)		FM(TPU0TO2_A)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#define IP13_7_4	FM(CAN1_TX_A)		FM(CANFD1_TX)		FM(TPU0TO3_A)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)

#define PINMUX_GPSW	\
\
		GPSW1_31	GPSW2_31			GPSW4_31		 \
		GPSW1_30	GPSW2_30			GPSW4_30		 \
		GPSW1_29	GPSW2_29			GPSW4_29		 \
		GPSW1_28	GPSW2_28			GPSW4_28		 \
		GPSW1_27	GPSW2_27			GPSW4_27		 \
		GPSW1_26	GPSW2_26			GPSW4_26		 \
		GPSW1_25	GPSW2_25			GPSW4_25		 \
		GPSW1_24	GPSW2_24			GPSW4_24		 \
		GPSW1_23	GPSW2_23			GPSW4_23		 \
		GPSW1_22	GPSW2_22			GPSW4_22		 \
		GPSW1_21	GPSW2_21			GPSW4_21		 \
		GPSW1_20	GPSW2_20			GPSW4_20	GPSW5_20 \
		GPSW1_19	GPSW2_19			GPSW4_19	GPSW5_19 \
		GPSW1_18	GPSW2_18			GPSW4_18	GPSW5_18 \
		GPSW1_17	GPSW2_17			GPSW4_17	GPSW5_17 \
		GPSW1_16	GPSW2_16			GPSW4_16	GPSW5_16 \
		GPSW1_15	GPSW2_15			GPSW4_15	GPSW5_15 \
		GPSW1_14	GPSW2_14			GPSW4_14	GPSW5_14 \
		GPSW1_13	GPSW2_13			GPSW4_13	GPSW5_13	GPSW6_13 \
		GPSW1_12	GPSW2_12			GPSW4_12	GPSW5_12	GPSW6_12 \
		GPSW1_11	GPSW2_11			GPSW4_11	GPSW5_11	GPSW6_11 \
		GPSW1_10	GPSW2_10			GPSW4_10	GPSW5_10	GPSW6_10 \
		GPSW1_9		GPSW2_9		GPSW3_9		GPSW4_9		GPSW5_9		GPSW6_9 \
GPSW0_8		GPSW1_8		GPSW2_8		GPSW3_8		GPSW4_8		GPSW5_8		GPSW6_8 \
GPSW0_7		GPSW1_7		GPSW2_7		GPSW3_7		GPSW4_7		GPSW5_7		GPSW6_7 \
GPSW0_6		GPSW1_6		GPSW2_6		GPSW3_6		GPSW4_6		GPSW5_6		GPSW6_6 \
GPSW0_5		GPSW1_5		GPSW2_5		GPSW3_5		GPSW4_5		GPSW5_5		GPSW6_5 \
GPSW0_4		GPSW1_4		GPSW2_4		GPSW3_4		GPSW4_4		GPSW5_4		GPSW6_4 \
GPSW0_3		GPSW1_3		GPSW2_3		GPSW3_3		GPSW4_3		GPSW5_3		GPSW6_3 \
GPSW0_2		GPSW1_2		GPSW2_2		GPSW3_2		GPSW4_2		GPSW5_2		GPSW6_2 \
GPSW0_1		GPSW1_1		GPSW2_1		GPSW3_1		GPSW4_1		GPSW5_1		GPSW6_1 \
GPSW0_0		GPSW1_0		GPSW2_0		GPSW3_0		GPSW4_0		GPSW5_0		GPSW6_0

#define PINMUX_IPSW				\
\
FM(IP0_3_0)	IP0_3_0		FM(IP1_3_0)	IP1_3_0		FM(IP2_3_0)	IP2_3_0		FM(IP3_3_0)	IP3_3_0 \
FM(IP0_7_4)	IP0_7_4		FM(IP1_7_4)	IP1_7_4		FM(IP2_7_4)	IP2_7_4		FM(IP3_7_4)	IP3_7_4 \
FM(IP0_11_8)	IP0_11_8	FM(IP1_11_8)	IP1_11_8	FM(IP2_11_8)	IP2_11_8	FM(IP3_11_8)	IP3_11_8 \
FM(IP0_15_12)	IP0_15_12	FM(IP1_15_12)	IP1_15_12	FM(IP2_15_12)	IP2_15_12	FM(IP3_15_12)	IP3_15_12 \
FM(IP0_19_16)	IP0_19_16	FM(IP1_19_16)	IP1_19_16	FM(IP2_19_16)	IP2_19_16	FM(IP3_19_16)	IP3_19_16 \
FM(IP0_23_20)	IP0_23_20	FM(IP1_23_20)	IP1_23_20	FM(IP2_23_20)	IP2_23_20	FM(IP3_23_20)	IP3_23_20 \
FM(IP0_27_24)	IP0_27_24	FM(IP1_27_24)	IP1_27_24	FM(IP2_27_24)	IP2_27_24	FM(IP3_27_24)	IP3_27_24 \
FM(IP0_31_28)	IP0_31_28	FM(IP1_31_28)	IP1_31_28	FM(IP2_31_28)	IP2_31_28	FM(IP3_31_28)	IP3_31_28 \
\
FM(IP4_3_0)	IP4_3_0		FM(IP5_3_0)	IP5_3_0		FM(IP6_3_0)	IP6_3_0		FM(IP7_3_0)	IP7_3_0 \
FM(IP4_7_4)	IP4_7_4		FM(IP5_7_4)	IP5_7_4		FM(IP6_7_4)	IP6_7_4		FM(IP7_7_4)	IP7_7_4 \
FM(IP4_11_8)	IP4_11_8	FM(IP5_11_8)	IP5_11_8	FM(IP6_11_8)	IP6_11_8	FM(IP7_11_8)	IP7_11_8 \
FM(IP4_15_12)	IP4_15_12	FM(IP5_15_12)	IP5_15_12	FM(IP6_15_12)	IP6_15_12	FM(IP7_15_12)	IP7_15_12 \
FM(IP4_19_16)	IP4_19_16	FM(IP5_19_16)	IP5_19_16	FM(IP6_19_16)	IP6_19_16	FM(IP7_19_16)	IP7_19_16 \
FM(IP4_23_20)	IP4_23_20	FM(IP5_23_20)	IP5_23_20	FM(IP6_23_20)	IP6_23_20	FM(IP7_23_20)	IP7_23_20 \
FM(IP4_27_24)	IP4_27_24	FM(IP5_27_24)	IP5_27_24	FM(IP6_27_24)	IP6_27_24	FM(IP7_27_24)	IP7_27_24 \
FM(IP4_31_28)	IP4_31_28	FM(IP5_31_28)	IP5_31_28	FM(IP6_31_28)	IP6_31_28	FM(IP7_31_28)	IP7_31_28 \
\
FM(IP8_3_0)	IP8_3_0		FM(IP9_3_0)	IP9_3_0		FM(IP10_3_0)	IP10_3_0	FM(IP11_3_0)	IP11_3_0 \
FM(IP8_7_4)	IP8_7_4		FM(IP9_7_4)	IP9_7_4		FM(IP10_7_4)	IP10_7_4	FM(IP11_7_4)	IP11_7_4 \
FM(IP8_11_8)	IP8_11_8	FM(IP9_11_8)	IP9_11_8	FM(IP10_11_8)	IP10_11_8	FM(IP11_11_8)	IP11_11_8 \
FM(IP8_15_12)	IP8_15_12	FM(IP9_15_12)	IP9_15_12	FM(IP10_15_12)	IP10_15_12	FM(IP11_15_12)	IP11_15_12 \
FM(IP8_19_16)	IP8_19_16	FM(IP9_19_16)	IP9_19_16	FM(IP10_19_16)	IP10_19_16	FM(IP11_19_16)	IP11_19_16 \
FM(IP8_23_20)	IP8_23_20	FM(IP9_23_20)	IP9_23_20	FM(IP10_23_20)	IP10_23_20	FM(IP11_23_20)	IP11_23_20 \
FM(IP8_27_24)	IP8_27_24	FM(IP9_27_24)	IP9_27_24	FM(IP10_27_24)	IP10_27_24	FM(IP11_27_24)	IP11_27_24 \
FM(IP8_31_28)	IP8_31_28	FM(IP9_31_28)	IP9_31_28	FM(IP10_31_28)	IP10_31_28	FM(IP11_31_28)	IP11_31_28 \
\
FM(IP12_3_0)	IP12_3_0	FM(IP13_3_0)	IP13_3_0 \
FM(IP12_7_4)	IP12_7_4	FM(IP13_7_4)	IP13_7_4 \
FM(IP12_11_8)	IP12_11_8 \
FM(IP12_15_12)	IP12_15_12 \
FM(IP12_19_16)	IP12_19_16 \
FM(IP12_23_20)	IP12_23_20 \
FM(IP12_27_24)	IP12_27_24 \
FM(IP12_31_28)	IP12_31_28 \

/* The bit numbewing in MOD_SEW fiewds is wevewsed */
#define WEV4(f0, f1, f2, f3)			f0 f2 f1 f3

/* MOD_SEW0 */			/* 0 */			/* 1 */			/* 2 */			/* 3 */
#define MOD_SEW0_30		FM(SEW_MSIOF2_0)	FM(SEW_MSIOF2_1)
#define MOD_SEW0_29		FM(SEW_I2C3_0)		FM(SEW_I2C3_1)
#define MOD_SEW0_28		FM(SEW_SCIF5_0)		FM(SEW_SCIF5_1)
#define MOD_SEW0_27		FM(SEW_MSIOF3_0)	FM(SEW_MSIOF3_1)
#define MOD_SEW0_26		FM(SEW_HSCIF3_0)	FM(SEW_HSCIF3_1)
#define MOD_SEW0_25		FM(SEW_SCIF4_0)		FM(SEW_SCIF4_1)
#define MOD_SEW0_24_23	   WEV4(FM(SEW_PWM0_0),		FM(SEW_PWM0_1),		FM(SEW_PWM0_2),		F_(0, 0))
#define MOD_SEW0_22_21	   WEV4(FM(SEW_PWM1_0),		FM(SEW_PWM1_1),		FM(SEW_PWM1_2),		F_(0, 0))
#define MOD_SEW0_20_19	   WEV4(FM(SEW_PWM2_0),		FM(SEW_PWM2_1),		FM(SEW_PWM2_2),		F_(0, 0))
#define MOD_SEW0_18_17	   WEV4(FM(SEW_PWM3_0),		FM(SEW_PWM3_1),		FM(SEW_PWM3_2),		F_(0, 0))
#define MOD_SEW0_15		FM(SEW_IWQ_0_0)		FM(SEW_IWQ_0_1)
#define MOD_SEW0_14		FM(SEW_IWQ_1_0)		FM(SEW_IWQ_1_1)
#define MOD_SEW0_13		FM(SEW_IWQ_2_0)		FM(SEW_IWQ_2_1)
#define MOD_SEW0_12		FM(SEW_IWQ_3_0)		FM(SEW_IWQ_3_1)
#define MOD_SEW0_11		FM(SEW_IWQ_4_0)		FM(SEW_IWQ_4_1)
#define MOD_SEW0_10		FM(SEW_IWQ_5_0)		FM(SEW_IWQ_5_1)
#define MOD_SEW0_5		FM(SEW_TMU_0_0)		FM(SEW_TMU_0_1)
#define MOD_SEW0_4		FM(SEW_TMU_1_0)		FM(SEW_TMU_1_1)
#define MOD_SEW0_3		FM(SEW_SCIF3_0)		FM(SEW_SCIF3_1)
#define MOD_SEW0_2		FM(SEW_SCIF1_0)		FM(SEW_SCIF1_1)
#define MOD_SEW0_1		FM(SEW_SCU_0)		FM(SEW_SCU_1)
#define MOD_SEW0_0		FM(SEW_WFSO_0)		FM(SEW_WFSO_1)

#define MOD_SEW1_31		FM(SEW_CAN0_0)		FM(SEW_CAN0_1)
#define MOD_SEW1_30		FM(SEW_CAN1_0)		FM(SEW_CAN1_1)
#define MOD_SEW1_29		FM(SEW_I2C2_0)		FM(SEW_I2C2_1)
#define MOD_SEW1_28		FM(SEW_ETHEWAVB_0)	FM(SEW_ETHEWAVB_1)
#define MOD_SEW1_27		FM(SEW_SCIF0_0)		FM(SEW_SCIF0_1)
#define MOD_SEW1_26		FM(SEW_SSIF4_0)		FM(SEW_SSIF4_1)


#define PINMUX_MOD_SEWS	\
\
		MOD_SEW1_31 \
MOD_SEW0_30	MOD_SEW1_30 \
MOD_SEW0_29	MOD_SEW1_29 \
MOD_SEW0_28	MOD_SEW1_28 \
MOD_SEW0_27	MOD_SEW1_27 \
MOD_SEW0_26	MOD_SEW1_26 \
MOD_SEW0_25 \
MOD_SEW0_24_23 \
MOD_SEW0_22_21 \
MOD_SEW0_20_19 \
MOD_SEW0_18_17 \
MOD_SEW0_15 \
MOD_SEW0_14 \
MOD_SEW0_13 \
MOD_SEW0_12 \
MOD_SEW0_11 \
MOD_SEW0_10 \
MOD_SEW0_5 \
MOD_SEW0_4 \
MOD_SEW0_3 \
MOD_SEW0_2 \
MOD_SEW0_1 \
MOD_SEW0_0

enum {
	PINMUX_WESEWVED = 0,

	PINMUX_DATA_BEGIN,
	GP_AWW(DATA),
	PINMUX_DATA_END,

#define F_(x, y)
#define FM(x)	FN_##x,
	PINMUX_FUNCTION_BEGIN,
	GP_AWW(FN),
	PINMUX_GPSW
	PINMUX_IPSW
	PINMUX_MOD_SEWS
	PINMUX_FUNCTION_END,
#undef F_
#undef FM

#define F_(x, y)
#define FM(x)	x##_MAWK,
	PINMUX_MAWK_BEGIN,
	PINMUX_GPSW
	PINMUX_IPSW
	PINMUX_MOD_SEWS
	PINMUX_MAWK_END,
#undef F_
#undef FM
};

static const u16 pinmux_data[] = {
	PINMUX_DATA_GP_AWW(),

	PINMUX_SINGWE(USB0_OVC),
	PINMUX_SINGWE(USB0_PWEN),
	PINMUX_SINGWE(VI4_DATA4),
	PINMUX_SINGWE(VI4_CWK),
	PINMUX_SINGWE(TX2),
	PINMUX_SINGWE(WX2),
	PINMUX_SINGWE(AVB0_WINK),
	PINMUX_SINGWE(AVB0_PHY_INT),
	PINMUX_SINGWE(AVB0_MAGIC),
	PINMUX_SINGWE(AVB0_MDC),
	PINMUX_SINGWE(AVB0_MDIO),
	PINMUX_SINGWE(AVB0_TXCWEFCWK),
	PINMUX_SINGWE(AVB0_TD3),
	PINMUX_SINGWE(AVB0_TD2),
	PINMUX_SINGWE(AVB0_TD1),
	PINMUX_SINGWE(AVB0_TD0),
	PINMUX_SINGWE(AVB0_TXC),
	PINMUX_SINGWE(AVB0_TX_CTW),
	PINMUX_SINGWE(AVB0_WD3),
	PINMUX_SINGWE(AVB0_WD2),
	PINMUX_SINGWE(AVB0_WD1),
	PINMUX_SINGWE(AVB0_WD0),
	PINMUX_SINGWE(AVB0_WXC),
	PINMUX_SINGWE(AVB0_WX_CTW),
	PINMUX_SINGWE(WPC_INT_N),
	PINMUX_SINGWE(WPC_WESET_N),
	PINMUX_SINGWE(QSPI1_SSW),
	PINMUX_SINGWE(QSPI1_IO3),
	PINMUX_SINGWE(QSPI1_IO2),
	PINMUX_SINGWE(QSPI1_MISO_IO1),
	PINMUX_SINGWE(QSPI1_MOSI_IO0),
	PINMUX_SINGWE(QSPI1_SPCWK),
	PINMUX_SINGWE(QSPI0_SSW),
	PINMUX_SINGWE(QSPI0_IO3),
	PINMUX_SINGWE(QSPI0_IO2),
	PINMUX_SINGWE(QSPI0_MISO_IO1),
	PINMUX_SINGWE(QSPI0_MOSI_IO0),
	PINMUX_SINGWE(QSPI0_SPCWK),
	PINMUX_SINGWE(SCW0),
	PINMUX_SINGWE(SDA0),
	PINMUX_SINGWE(MSIOF0_WXD),
	PINMUX_SINGWE(MSIOF0_TXD),
	PINMUX_SINGWE(MSIOF0_SYNC),
	PINMUX_SINGWE(MSIOF0_SCK),

	/* IPSW0 */
	PINMUX_IPSW_MSEW(IP0_3_0,	IWQ0_A, SEW_IWQ_0_0),
	PINMUX_IPSW_MSEW(IP0_3_0,	MSIOF2_SYNC_B, SEW_MSIOF2_1),

	PINMUX_IPSW_GPSW(IP0_7_4,	MSIOF2_SCK),

	PINMUX_IPSW_GPSW(IP0_11_8,	MSIOF2_TXD),
	PINMUX_IPSW_MSEW(IP0_11_8,	SCW3_A, SEW_I2C3_0),

	PINMUX_IPSW_GPSW(IP0_15_12,	MSIOF2_WXD),
	PINMUX_IPSW_MSEW(IP0_15_12,	SDA3_A, SEW_I2C3_0),

	PINMUX_IPSW_GPSW(IP0_19_16,	MWB_CWK),
	PINMUX_IPSW_MSEW(IP0_19_16,	MSIOF2_SYNC_A, SEW_MSIOF2_0),
	PINMUX_IPSW_MSEW(IP0_19_16,	SCK5_A, SEW_SCIF5_0),

	PINMUX_IPSW_GPSW(IP0_23_20,	MWB_DAT),
	PINMUX_IPSW_GPSW(IP0_23_20,	MSIOF2_SS1),
	PINMUX_IPSW_MSEW(IP0_23_20,	WX5_A, SEW_SCIF5_0),
	PINMUX_IPSW_MSEW(IP0_23_20,	SCW3_B, SEW_I2C3_1),

	PINMUX_IPSW_GPSW(IP0_27_24,	MWB_SIG),
	PINMUX_IPSW_GPSW(IP0_27_24,	MSIOF2_SS2),
	PINMUX_IPSW_MSEW(IP0_27_24,	TX5_A, SEW_SCIF5_0),
	PINMUX_IPSW_MSEW(IP0_27_24,	SDA3_B, SEW_I2C3_1),

	PINMUX_IPSW_GPSW(IP0_31_28,	DU_DB0),
	PINMUX_IPSW_GPSW(IP0_31_28,	WCDOUT0),
	PINMUX_IPSW_MSEW(IP0_31_28,	MSIOF3_TXD_B, SEW_MSIOF3_1),

	/* IPSW1 */
	PINMUX_IPSW_GPSW(IP1_3_0,	DU_DB1),
	PINMUX_IPSW_GPSW(IP1_3_0,	WCDOUT1),
	PINMUX_IPSW_MSEW(IP1_3_0,	MSIOF3_WXD_B, SEW_MSIOF3_1),

	PINMUX_IPSW_GPSW(IP1_7_4,	DU_DB2),
	PINMUX_IPSW_GPSW(IP1_7_4,	WCDOUT2),
	PINMUX_IPSW_MSEW(IP1_7_4,	IWQ0_B, SEW_IWQ_0_1),

	PINMUX_IPSW_GPSW(IP1_11_8,	DU_DB3),
	PINMUX_IPSW_GPSW(IP1_11_8,	WCDOUT3),
	PINMUX_IPSW_MSEW(IP1_11_8,	SCK5_B, SEW_SCIF5_1),

	PINMUX_IPSW_GPSW(IP1_15_12,	DU_DB4),
	PINMUX_IPSW_GPSW(IP1_15_12,	WCDOUT4),
	PINMUX_IPSW_MSEW(IP1_15_12,	WX5_B, SEW_SCIF5_1),

	PINMUX_IPSW_GPSW(IP1_19_16,	DU_DB5),
	PINMUX_IPSW_GPSW(IP1_19_16,	WCDOUT5),
	PINMUX_IPSW_MSEW(IP1_19_16,	TX5_B, SEW_SCIF5_1),

	PINMUX_IPSW_GPSW(IP1_23_20,	DU_DB6),
	PINMUX_IPSW_GPSW(IP1_23_20,	WCDOUT6),
	PINMUX_IPSW_MSEW(IP1_23_20,	MSIOF3_SS1_B, SEW_MSIOF3_1),

	PINMUX_IPSW_GPSW(IP1_27_24,	DU_DB7),
	PINMUX_IPSW_GPSW(IP1_27_24,	WCDOUT7),
	PINMUX_IPSW_MSEW(IP1_27_24,	MSIOF3_SS2_B, SEW_MSIOF3_1),

	PINMUX_IPSW_GPSW(IP1_31_28,	DU_DG0),
	PINMUX_IPSW_GPSW(IP1_31_28,	WCDOUT8),
	PINMUX_IPSW_MSEW(IP1_31_28,	MSIOF3_SCK_B, SEW_MSIOF3_1),

	/* IPSW2 */
	PINMUX_IPSW_GPSW(IP2_3_0,	DU_DG1),
	PINMUX_IPSW_GPSW(IP2_3_0,	WCDOUT9),
	PINMUX_IPSW_MSEW(IP2_3_0,	MSIOF3_SYNC_B, SEW_MSIOF3_1),

	PINMUX_IPSW_GPSW(IP2_7_4,	DU_DG2),
	PINMUX_IPSW_GPSW(IP2_7_4,	WCDOUT10),

	PINMUX_IPSW_GPSW(IP2_11_8,	DU_DG3),
	PINMUX_IPSW_GPSW(IP2_11_8,	WCDOUT11),
	PINMUX_IPSW_MSEW(IP2_11_8,	IWQ1_A, SEW_IWQ_1_0),

	PINMUX_IPSW_GPSW(IP2_15_12,	DU_DG4),
	PINMUX_IPSW_GPSW(IP2_15_12,	WCDOUT12),
	PINMUX_IPSW_MSEW(IP2_15_12,	HSCK3_B, SEW_HSCIF3_1),

	PINMUX_IPSW_GPSW(IP2_19_16,	DU_DG5),
	PINMUX_IPSW_GPSW(IP2_19_16,	WCDOUT13),
	PINMUX_IPSW_MSEW(IP2_19_16,	HTX3_B, SEW_HSCIF3_1),

	PINMUX_IPSW_GPSW(IP2_23_20,	DU_DG6),
	PINMUX_IPSW_GPSW(IP2_23_20,	WCDOUT14),
	PINMUX_IPSW_MSEW(IP2_23_20,	HWX3_B, SEW_HSCIF3_1),

	PINMUX_IPSW_GPSW(IP2_27_24,	DU_DG7),
	PINMUX_IPSW_GPSW(IP2_27_24,	WCDOUT15),
	PINMUX_IPSW_MSEW(IP2_27_24,	SCK4_B, SEW_SCIF4_1),

	PINMUX_IPSW_GPSW(IP2_31_28,	DU_DW0),
	PINMUX_IPSW_GPSW(IP2_31_28,	WCDOUT16),
	PINMUX_IPSW_MSEW(IP2_31_28,	WX4_B, SEW_SCIF4_1),

	/* IPSW3 */
	PINMUX_IPSW_GPSW(IP3_3_0,	DU_DW1),
	PINMUX_IPSW_GPSW(IP3_3_0,	WCDOUT17),
	PINMUX_IPSW_MSEW(IP3_3_0,	TX4_B, SEW_SCIF4_1),

	PINMUX_IPSW_GPSW(IP3_7_4,	DU_DW2),
	PINMUX_IPSW_GPSW(IP3_7_4,	WCDOUT18),
	PINMUX_IPSW_MSEW(IP3_7_4,	PWM0_B, SEW_PWM0_2),

	PINMUX_IPSW_GPSW(IP3_11_8,	DU_DW3),
	PINMUX_IPSW_GPSW(IP3_11_8,	WCDOUT19),
	PINMUX_IPSW_MSEW(IP3_11_8,	PWM1_B, SEW_PWM1_2),

	PINMUX_IPSW_GPSW(IP3_15_12,	DU_DW4),
	PINMUX_IPSW_GPSW(IP3_15_12,	WCDOUT20),
	PINMUX_IPSW_MSEW(IP3_15_12,	TCWK2_B, SEW_TMU_0_1),

	PINMUX_IPSW_GPSW(IP3_19_16,	DU_DW5),
	PINMUX_IPSW_GPSW(IP3_19_16,	WCDOUT21),
	PINMUX_IPSW_GPSW(IP3_19_16,	NMI),

	PINMUX_IPSW_GPSW(IP3_23_20,	DU_DW6),
	PINMUX_IPSW_GPSW(IP3_23_20,	WCDOUT22),
	PINMUX_IPSW_MSEW(IP3_23_20,	PWM2_B, SEW_PWM2_2),

	PINMUX_IPSW_GPSW(IP3_27_24,	DU_DW7),
	PINMUX_IPSW_GPSW(IP3_27_24,	WCDOUT23),
	PINMUX_IPSW_MSEW(IP3_27_24,	TCWK1_B, SEW_TMU_1_1),

	PINMUX_IPSW_GPSW(IP3_31_28,	DU_DOTCWKOUT0),
	PINMUX_IPSW_GPSW(IP3_31_28,	QCWK),

	/* IPSW4 */
	PINMUX_IPSW_GPSW(IP4_3_0,	DU_HSYNC),
	PINMUX_IPSW_GPSW(IP4_3_0,	QSTH_QHS),
	PINMUX_IPSW_MSEW(IP4_3_0,	IWQ3_A, SEW_IWQ_3_0),

	PINMUX_IPSW_GPSW(IP4_7_4,	DU_VSYNC),
	PINMUX_IPSW_GPSW(IP4_7_4,	QSTVA_QVS),
	PINMUX_IPSW_MSEW(IP4_7_4,	IWQ4_A, SEW_IWQ_4_0),

	PINMUX_IPSW_GPSW(IP4_11_8,	DU_DISP),
	PINMUX_IPSW_GPSW(IP4_11_8,	QSTVB_QVE),
	PINMUX_IPSW_MSEW(IP4_11_8,	PWM3_B, SEW_PWM3_2),

	PINMUX_IPSW_GPSW(IP4_15_12,	DU_DISP_CDE),
	PINMUX_IPSW_GPSW(IP4_15_12,	QCPV_QDE),
	PINMUX_IPSW_MSEW(IP4_15_12,	IWQ2_B, SEW_IWQ_2_1),
	PINMUX_IPSW_GPSW(IP4_15_12,	DU_DOTCWKIN1),

	PINMUX_IPSW_GPSW(IP4_19_16,	DU_CDE),
	PINMUX_IPSW_GPSW(IP4_19_16,	QSTB_QHE),
	PINMUX_IPSW_MSEW(IP4_19_16,	SCK3_B, SEW_SCIF3_1),

	PINMUX_IPSW_GPSW(IP4_23_20,	QPOWA),
	PINMUX_IPSW_MSEW(IP4_23_20,	WX3_B, SEW_SCIF3_1),

	PINMUX_IPSW_GPSW(IP4_27_24,	QPOWB),
	PINMUX_IPSW_MSEW(IP4_27_24,	TX3_B, SEW_SCIF3_1),

	PINMUX_IPSW_GPSW(IP4_31_28,	VI4_DATA0),
	PINMUX_IPSW_MSEW(IP4_31_28,	PWM0_A, SEW_PWM0_0),

	/* IPSW5 */
	PINMUX_IPSW_GPSW(IP5_3_0,	VI4_DATA1),
	PINMUX_IPSW_MSEW(IP5_3_0,	PWM1_A, SEW_PWM1_0),

	PINMUX_IPSW_GPSW(IP5_7_4,	VI4_DATA2),
	PINMUX_IPSW_MSEW(IP5_7_4,	PWM2_A, SEW_PWM2_0),

	PINMUX_IPSW_GPSW(IP5_11_8,	VI4_DATA3),
	PINMUX_IPSW_MSEW(IP5_11_8,	PWM3_A, SEW_PWM3_0),

	PINMUX_IPSW_GPSW(IP5_15_12,	VI4_DATA5),
	PINMUX_IPSW_MSEW(IP5_15_12,	SCK4_A, SEW_SCIF4_0),

	PINMUX_IPSW_GPSW(IP5_19_16,	VI4_DATA6),
	PINMUX_IPSW_MSEW(IP5_19_16,	IWQ2_A, SEW_IWQ_2_0),

	PINMUX_IPSW_GPSW(IP5_23_20,	VI4_DATA7),
	PINMUX_IPSW_MSEW(IP5_23_20,	TCWK2_A, SEW_TMU_0_0),

	PINMUX_IPSW_GPSW(IP5_27_24,	VI4_DATA8),

	PINMUX_IPSW_GPSW(IP5_31_28,	VI4_DATA9),
	PINMUX_IPSW_MSEW(IP5_31_28,	MSIOF3_SS2_A, SEW_MSIOF3_0),
	PINMUX_IPSW_MSEW(IP5_31_28,	IWQ1_B, SEW_IWQ_1_1),

	/* IPSW6 */
	PINMUX_IPSW_GPSW(IP6_3_0,	VI4_DATA10),
	PINMUX_IPSW_MSEW(IP6_3_0,	WX4_A, SEW_SCIF4_0),

	PINMUX_IPSW_GPSW(IP6_7_4,	VI4_DATA11),
	PINMUX_IPSW_MSEW(IP6_7_4,	TX4_A, SEW_SCIF4_0),

	PINMUX_IPSW_GPSW(IP6_11_8,	VI4_DATA12),
	PINMUX_IPSW_MSEW(IP6_11_8,	TCWK1_A, SEW_TMU_1_0),

	PINMUX_IPSW_GPSW(IP6_15_12,	VI4_DATA13),
	PINMUX_IPSW_MSEW(IP6_15_12,	MSIOF3_SS1_A, SEW_MSIOF3_0),
	PINMUX_IPSW_GPSW(IP6_15_12,	HCTS3_N),

	PINMUX_IPSW_GPSW(IP6_19_16,	VI4_DATA14),
	PINMUX_IPSW_MSEW(IP6_19_16,	SSI_SCK4_B, SEW_SSIF4_1),
	PINMUX_IPSW_GPSW(IP6_19_16,	HWTS3_N),

	PINMUX_IPSW_GPSW(IP6_23_20,	VI4_DATA15),
	PINMUX_IPSW_MSEW(IP6_23_20,	SSI_SDATA4_B, SEW_SSIF4_1),

	PINMUX_IPSW_GPSW(IP6_27_24,	VI4_DATA16),
	PINMUX_IPSW_MSEW(IP6_27_24,	HWX3_A, SEW_HSCIF3_0),

	PINMUX_IPSW_GPSW(IP6_31_28,	VI4_DATA17),
	PINMUX_IPSW_MSEW(IP6_31_28,	HTX3_A, SEW_HSCIF3_0),

	/* IPSW7 */
	PINMUX_IPSW_GPSW(IP7_3_0,	VI4_DATA18),
	PINMUX_IPSW_MSEW(IP7_3_0,	HSCK3_A, SEW_HSCIF3_0),

	PINMUX_IPSW_GPSW(IP7_7_4,	VI4_DATA19),
	PINMUX_IPSW_MSEW(IP7_7_4,	SSI_WS4_B, SEW_SSIF4_1),
	PINMUX_IPSW_GPSW(IP7_7_4,	NFDATA15),

	PINMUX_IPSW_GPSW(IP7_11_8,	VI4_DATA20),
	PINMUX_IPSW_MSEW(IP7_11_8,	MSIOF3_SYNC_A, SEW_MSIOF3_0),
	PINMUX_IPSW_GPSW(IP7_11_8,	NFDATA14),

	PINMUX_IPSW_GPSW(IP7_15_12,	VI4_DATA21),
	PINMUX_IPSW_MSEW(IP7_15_12,	MSIOF3_TXD_A, SEW_MSIOF3_0),

	PINMUX_IPSW_GPSW(IP7_15_12,	NFDATA13),
	PINMUX_IPSW_GPSW(IP7_19_16,	VI4_DATA22),
	PINMUX_IPSW_MSEW(IP7_19_16,	MSIOF3_WXD_A, SEW_MSIOF3_0),

	PINMUX_IPSW_GPSW(IP7_19_16,	NFDATA12),
	PINMUX_IPSW_GPSW(IP7_23_20,	VI4_DATA23),
	PINMUX_IPSW_MSEW(IP7_23_20,	MSIOF3_SCK_A, SEW_MSIOF3_0),

	PINMUX_IPSW_GPSW(IP7_23_20,	NFDATA11),

	PINMUX_IPSW_GPSW(IP7_27_24,	VI4_VSYNC_N),
	PINMUX_IPSW_MSEW(IP7_27_24,	SCK1_B, SEW_SCIF1_1),
	PINMUX_IPSW_GPSW(IP7_27_24,	NFDATA10),

	PINMUX_IPSW_GPSW(IP7_31_28,	VI4_HSYNC_N),
	PINMUX_IPSW_MSEW(IP7_31_28,	WX1_B, SEW_SCIF1_1),
	PINMUX_IPSW_GPSW(IP7_31_28,	NFDATA9),

	/* IPSW8 */
	PINMUX_IPSW_GPSW(IP8_3_0,	VI4_FIEWD),
	PINMUX_IPSW_GPSW(IP8_3_0,	AUDIO_CWKB),
	PINMUX_IPSW_MSEW(IP8_3_0,	IWQ5_A, SEW_IWQ_5_0),
	PINMUX_IPSW_GPSW(IP8_3_0,	SCIF_CWK),
	PINMUX_IPSW_GPSW(IP8_3_0,	NFDATA8),

	PINMUX_IPSW_GPSW(IP8_7_4,	VI4_CWKENB),
	PINMUX_IPSW_MSEW(IP8_7_4,	TX1_B, SEW_SCIF1_1),
	PINMUX_IPSW_GPSW(IP8_7_4,	NFWP_N),
	PINMUX_IPSW_MSEW(IP8_7_4,	DVC_MUTE_A, SEW_SCU_0),

	PINMUX_IPSW_GPSW(IP8_11_8,	NFAWE),
	PINMUX_IPSW_MSEW(IP8_11_8,	SCW2_B, SEW_I2C2_1),
	PINMUX_IPSW_MSEW(IP8_11_8,	IWQ3_B, SEW_IWQ_3_1),
	PINMUX_IPSW_MSEW(IP8_11_8,	PWM0_C, SEW_PWM0_1),

	PINMUX_IPSW_GPSW(IP8_15_12,	NFCWE),
	PINMUX_IPSW_MSEW(IP8_15_12,	SDA2_B, SEW_I2C2_1),
	PINMUX_IPSW_MSEW(IP8_15_12,	SCK3_A, SEW_SCIF3_0),
	PINMUX_IPSW_MSEW(IP8_15_12,	PWM1_C, SEW_PWM1_1),

	PINMUX_IPSW_GPSW(IP8_19_16,	NFCE_N),
	PINMUX_IPSW_MSEW(IP8_19_16,	WX3_A, SEW_SCIF3_0),
	PINMUX_IPSW_MSEW(IP8_19_16,	PWM2_C, SEW_PWM2_1),

	PINMUX_IPSW_GPSW(IP8_23_20,	NFWB_N),
	PINMUX_IPSW_MSEW(IP8_23_20,	TX3_A, SEW_SCIF3_0),
	PINMUX_IPSW_MSEW(IP8_23_20,	PWM3_C, SEW_PWM3_1),

	PINMUX_IPSW_GPSW(IP8_27_24,	NFWE_N),
	PINMUX_IPSW_GPSW(IP8_27_24,	MMC_CMD),

	PINMUX_IPSW_GPSW(IP8_31_28,	NFWE_N),
	PINMUX_IPSW_GPSW(IP8_31_28,	MMC_CWK),

	/* IPSW9 */
	PINMUX_IPSW_GPSW(IP9_3_0,	NFDATA0),
	PINMUX_IPSW_GPSW(IP9_3_0,	MMC_D0),

	PINMUX_IPSW_GPSW(IP9_7_4,	NFDATA1),
	PINMUX_IPSW_GPSW(IP9_7_4,	MMC_D1),

	PINMUX_IPSW_GPSW(IP9_11_8,	NFDATA2),
	PINMUX_IPSW_GPSW(IP9_11_8,	MMC_D2),

	PINMUX_IPSW_GPSW(IP9_15_12,	NFDATA3),
	PINMUX_IPSW_GPSW(IP9_15_12,	MMC_D3),

	PINMUX_IPSW_GPSW(IP9_19_16,	NFDATA4),
	PINMUX_IPSW_GPSW(IP9_19_16,	MMC_D4),

	PINMUX_IPSW_GPSW(IP9_23_20,	NFDATA5),
	PINMUX_IPSW_GPSW(IP9_23_20,	MMC_D5),

	PINMUX_IPSW_GPSW(IP9_27_24,	NFDATA6),
	PINMUX_IPSW_GPSW(IP9_27_24,	MMC_D6),

	PINMUX_IPSW_GPSW(IP9_31_28,	NFDATA7),
	PINMUX_IPSW_GPSW(IP9_31_28,	MMC_D7),

	/* IPSW10 */
	PINMUX_IPSW_GPSW(IP10_3_0,	AUDIO_CWKA),
	PINMUX_IPSW_MSEW(IP10_3_0,	DVC_MUTE_B, SEW_SCU_1),

	PINMUX_IPSW_GPSW(IP10_7_4,	SSI_SCK34),
	PINMUX_IPSW_MSEW(IP10_7_4,	FSO_CFE_0_N_A, SEW_WFSO_0),

	PINMUX_IPSW_GPSW(IP10_11_8,	SSI_SDATA3),
	PINMUX_IPSW_MSEW(IP10_11_8,	FSO_CFE_1_N_A, SEW_WFSO_0),

	PINMUX_IPSW_GPSW(IP10_15_12,	SSI_WS34),
	PINMUX_IPSW_MSEW(IP10_15_12,	FSO_TOE_N_A, SEW_WFSO_0),

	PINMUX_IPSW_MSEW(IP10_19_16,	SSI_SCK4_A, SEW_SSIF4_0),
	PINMUX_IPSW_GPSW(IP10_19_16,	HSCK0),
	PINMUX_IPSW_GPSW(IP10_19_16,	AUDIO_CWKOUT),
	PINMUX_IPSW_MSEW(IP10_19_16,	CAN0_WX_B, SEW_CAN0_1),
	PINMUX_IPSW_MSEW(IP10_19_16,	IWQ4_B, SEW_IWQ_4_1),

	PINMUX_IPSW_MSEW(IP10_23_20,	SSI_SDATA4_A, SEW_SSIF4_0),
	PINMUX_IPSW_GPSW(IP10_23_20,	HTX0),
	PINMUX_IPSW_MSEW(IP10_23_20,	SCW2_A, SEW_I2C2_0),
	PINMUX_IPSW_MSEW(IP10_23_20,	CAN1_WX_B, SEW_CAN1_1),

	PINMUX_IPSW_MSEW(IP10_27_24,	SSI_WS4_A, SEW_SSIF4_0),
	PINMUX_IPSW_GPSW(IP10_27_24,	HWX0),
	PINMUX_IPSW_MSEW(IP10_27_24,	SDA2_A, SEW_I2C2_0),
	PINMUX_IPSW_MSEW(IP10_27_24,	CAN1_TX_B, SEW_CAN1_1),

	PINMUX_IPSW_GPSW(IP10_31_28,	SCW1),
	PINMUX_IPSW_GPSW(IP10_31_28,	CTS1_N),

	/* IPSW11 */
	PINMUX_IPSW_GPSW(IP11_3_0,	SDA1),
	PINMUX_IPSW_GPSW(IP11_3_0,	WTS1_N),

	PINMUX_IPSW_GPSW(IP11_7_4,	MSIOF1_SCK),
	PINMUX_IPSW_MSEW(IP11_7_4,	AVB0_AVTP_PPS_B, SEW_ETHEWAVB_1),

	PINMUX_IPSW_GPSW(IP11_11_8,	MSIOF1_TXD),
	PINMUX_IPSW_MSEW(IP11_11_8,	AVB0_AVTP_CAPTUWE_B, SEW_ETHEWAVB_1),

	PINMUX_IPSW_GPSW(IP11_15_12,	MSIOF1_WXD),
	PINMUX_IPSW_MSEW(IP11_15_12,	AVB0_AVTP_MATCH_B, SEW_ETHEWAVB_1),

	PINMUX_IPSW_MSEW(IP11_19_16,	SCK0_A, SEW_SCIF0_0),
	PINMUX_IPSW_GPSW(IP11_19_16,	MSIOF1_SYNC),
	PINMUX_IPSW_MSEW(IP11_19_16,	FSO_CFE_0_N_B, SEW_WFSO_1),

	PINMUX_IPSW_MSEW(IP11_23_20,	WX0_A, SEW_SCIF0_0),
	PINMUX_IPSW_GPSW(IP11_23_20,	MSIOF0_SS1),
	PINMUX_IPSW_MSEW(IP11_23_20,	FSO_CFE_1_N_B, SEW_WFSO_1),

	PINMUX_IPSW_MSEW(IP11_27_24,	TX0_A, SEW_SCIF0_0),
	PINMUX_IPSW_GPSW(IP11_27_24,	MSIOF0_SS2),
	PINMUX_IPSW_MSEW(IP11_27_24,	FSO_TOE_N_B, SEW_WFSO_1),

	PINMUX_IPSW_MSEW(IP11_31_28,	SCK1_A, SEW_SCIF1_0),
	PINMUX_IPSW_GPSW(IP11_31_28,	MSIOF1_SS2),
	PINMUX_IPSW_GPSW(IP11_31_28,	TPU0TO2_B),
	PINMUX_IPSW_MSEW(IP11_31_28,	CAN0_TX_B, SEW_CAN0_1),
	PINMUX_IPSW_GPSW(IP11_31_28,	AUDIO_CWKOUT1),

	/* IPSW12 */
	PINMUX_IPSW_MSEW(IP12_3_0,	WX1_A, SEW_SCIF1_0),
	PINMUX_IPSW_GPSW(IP12_3_0,	CTS0_N),
	PINMUX_IPSW_GPSW(IP12_3_0,	TPU0TO0_B),

	PINMUX_IPSW_MSEW(IP12_7_4,	TX1_A, SEW_SCIF1_0),
	PINMUX_IPSW_GPSW(IP12_7_4,	WTS0_N),
	PINMUX_IPSW_GPSW(IP12_7_4,	TPU0TO1_B),

	PINMUX_IPSW_GPSW(IP12_11_8,	SCK2),
	PINMUX_IPSW_GPSW(IP12_11_8,	MSIOF1_SS1),
	PINMUX_IPSW_GPSW(IP12_11_8,	TPU0TO3_B),

	PINMUX_IPSW_GPSW(IP12_15_12,	TPU0TO0_A),
	PINMUX_IPSW_MSEW(IP12_15_12,	AVB0_AVTP_CAPTUWE_A, SEW_ETHEWAVB_0),
	PINMUX_IPSW_GPSW(IP12_15_12,	HCTS0_N),

	PINMUX_IPSW_GPSW(IP12_19_16,	TPU0TO1_A),
	PINMUX_IPSW_MSEW(IP12_19_16,	AVB0_AVTP_MATCH_A, SEW_ETHEWAVB_0),
	PINMUX_IPSW_GPSW(IP12_19_16,	HWTS0_N),

	PINMUX_IPSW_GPSW(IP12_23_20,	CAN_CWK),
	PINMUX_IPSW_MSEW(IP12_23_20,	AVB0_AVTP_PPS_A, SEW_ETHEWAVB_0),
	PINMUX_IPSW_MSEW(IP12_23_20,	SCK0_B, SEW_SCIF0_1),
	PINMUX_IPSW_MSEW(IP12_23_20,	IWQ5_B, SEW_IWQ_5_1),

	PINMUX_IPSW_MSEW(IP12_27_24,	CAN0_WX_A, SEW_CAN0_0),
	PINMUX_IPSW_GPSW(IP12_27_24,	CANFD0_WX),
	PINMUX_IPSW_MSEW(IP12_27_24,	WX0_B, SEW_SCIF0_1),

	PINMUX_IPSW_MSEW(IP12_31_28,	CAN0_TX_A, SEW_CAN0_0),
	PINMUX_IPSW_GPSW(IP12_31_28,	CANFD0_TX),
	PINMUX_IPSW_MSEW(IP12_31_28,	TX0_B, SEW_SCIF0_1),

	/* IPSW13 */
	PINMUX_IPSW_MSEW(IP13_3_0,	CAN1_WX_A, SEW_CAN1_0),
	PINMUX_IPSW_GPSW(IP13_3_0,	CANFD1_WX),
	PINMUX_IPSW_GPSW(IP13_3_0,	TPU0TO2_A),

	PINMUX_IPSW_MSEW(IP13_7_4,	CAN1_TX_A, SEW_CAN1_0),
	PINMUX_IPSW_GPSW(IP13_7_4,	CANFD1_TX),
	PINMUX_IPSW_GPSW(IP13_7_4,	TPU0TO3_A),
};

/*
 * Pins not associated with a GPIO powt.
 */
enum {
	GP_ASSIGN_WAST(),
	NOGP_AWW(),
};

static const stwuct sh_pfc_pin pinmux_pins[] = {
	PINMUX_GPIO_GP_AWW(),
	PINMUX_NOGP_AWW(),
};

/* - AUDIO CWOCK ------------------------------------------------------------- */
static const unsigned int audio_cwk_a_pins[] = {
	/* CWK A */
	WCAW_GP_PIN(4, 1),
};
static const unsigned int audio_cwk_a_mux[] = {
	AUDIO_CWKA_MAWK,
};
static const unsigned int audio_cwk_b_pins[] = {
	/* CWK B */
	WCAW_GP_PIN(2, 27),
};
static const unsigned int audio_cwk_b_mux[] = {
	AUDIO_CWKB_MAWK,
};
static const unsigned int audio_cwkout_pins[] = {
	/* CWKOUT */
	WCAW_GP_PIN(4, 5),
};
static const unsigned int audio_cwkout_mux[] = {
	AUDIO_CWKOUT_MAWK,
};
static const unsigned int audio_cwkout1_pins[] = {
	/* CWKOUT1 */
	WCAW_GP_PIN(4, 22),
};
static const unsigned int audio_cwkout1_mux[] = {
	AUDIO_CWKOUT1_MAWK,
};

/* - EthewAVB --------------------------------------------------------------- */
static const unsigned int avb0_wink_pins[] = {
	/* AVB0_WINK */
	WCAW_GP_PIN(5, 20),
};
static const unsigned int avb0_wink_mux[] = {
	AVB0_WINK_MAWK,
};
static const unsigned int avb0_magic_pins[] = {
	/* AVB0_MAGIC */
	WCAW_GP_PIN(5, 18),
};
static const unsigned int avb0_magic_mux[] = {
	AVB0_MAGIC_MAWK,
};
static const unsigned int avb0_phy_int_pins[] = {
	/* AVB0_PHY_INT */
	WCAW_GP_PIN(5, 19),
};
static const unsigned int avb0_phy_int_mux[] = {
	AVB0_PHY_INT_MAWK,
};
static const unsigned int avb0_mdio_pins[] = {
	/* AVB0_MDC, AVB0_MDIO */
	WCAW_GP_PIN(5, 17), WCAW_GP_PIN(5, 16),
};
static const unsigned int avb0_mdio_mux[] = {
	AVB0_MDC_MAWK, AVB0_MDIO_MAWK,
};
static const unsigned int avb0_mii_pins[] = {
	/*
	 * AVB0_TX_CTW, AVB0_TXC, AVB0_TD0,
	 * AVB0_TD1, AVB0_TD2, AVB0_TD3,
	 * AVB0_WX_CTW, AVB0_WXC, AVB0_WD0,
	 * AVB0_WD1, AVB0_WD2, AVB0_WD3,
	 * AVB0_TXCWEFCWK
	 */
	WCAW_GP_PIN(5, 9), WCAW_GP_PIN(5, 10), WCAW_GP_PIN(5, 11),
	WCAW_GP_PIN(5, 12), WCAW_GP_PIN(5, 13), WCAW_GP_PIN(5, 14),
	WCAW_GP_PIN(5, 3), WCAW_GP_PIN(5, 4), WCAW_GP_PIN(5, 5),
	WCAW_GP_PIN(5, 6), WCAW_GP_PIN(5, 7), WCAW_GP_PIN(5, 8),
	WCAW_GP_PIN(5, 15),
};
static const unsigned int avb0_mii_mux[] = {
	AVB0_TX_CTW_MAWK, AVB0_TXC_MAWK, AVB0_TD0_MAWK,
	AVB0_TD1_MAWK, AVB0_TD2_MAWK, AVB0_TD3_MAWK,
	AVB0_WX_CTW_MAWK, AVB0_WXC_MAWK, AVB0_WD0_MAWK,
	AVB0_WD1_MAWK, AVB0_WD2_MAWK, AVB0_WD3_MAWK,
	AVB0_TXCWEFCWK_MAWK,
};
static const unsigned int avb0_avtp_pps_a_pins[] = {
	/* AVB0_AVTP_PPS_A */
	WCAW_GP_PIN(5, 2),
};
static const unsigned int avb0_avtp_pps_a_mux[] = {
	AVB0_AVTP_PPS_A_MAWK,
};
static const unsigned int avb0_avtp_match_a_pins[] = {
	/* AVB0_AVTP_MATCH_A */
	WCAW_GP_PIN(5, 1),
};
static const unsigned int avb0_avtp_match_a_mux[] = {
	AVB0_AVTP_MATCH_A_MAWK,
};
static const unsigned int avb0_avtp_captuwe_a_pins[] = {
	/* AVB0_AVTP_CAPTUWE_A */
	WCAW_GP_PIN(5, 0),
};
static const unsigned int avb0_avtp_captuwe_a_mux[] = {
	AVB0_AVTP_CAPTUWE_A_MAWK,
};
static const unsigned int avb0_avtp_pps_b_pins[] = {
	/* AVB0_AVTP_PPS_B */
	WCAW_GP_PIN(4, 16),
};
static const unsigned int avb0_avtp_pps_b_mux[] = {
	AVB0_AVTP_PPS_B_MAWK,
};
static const unsigned int avb0_avtp_match_b_pins[] = {
	/*  AVB0_AVTP_MATCH_B */
	WCAW_GP_PIN(4, 18),
};
static const unsigned int avb0_avtp_match_b_mux[] = {
	AVB0_AVTP_MATCH_B_MAWK,
};
static const unsigned int avb0_avtp_captuwe_b_pins[] = {
	/* AVB0_AVTP_CAPTUWE_B */
	WCAW_GP_PIN(4, 17),
};
static const unsigned int avb0_avtp_captuwe_b_mux[] = {
	AVB0_AVTP_CAPTUWE_B_MAWK,
};

/* - CAN ------------------------------------------------------------------ */
static const unsigned int can0_data_a_pins[] = {
	/* TX, WX */
	WCAW_GP_PIN(4, 28), WCAW_GP_PIN(4, 31),
};
static const unsigned int can0_data_a_mux[] = {
	CAN0_TX_A_MAWK, CAN0_WX_A_MAWK,
};
static const unsigned int can0_data_b_pins[] = {
	/* TX, WX */
	WCAW_GP_PIN(4, 22), WCAW_GP_PIN(4, 5),
};
static const unsigned int can0_data_b_mux[] = {
	CAN0_TX_B_MAWK, CAN0_WX_B_MAWK,
};
static const unsigned int can1_data_a_pins[] = {
	/* TX, WX */
	WCAW_GP_PIN(4, 30), WCAW_GP_PIN(4, 29),
};
static const unsigned int can1_data_a_mux[] = {
	CAN1_TX_A_MAWK, CAN1_WX_A_MAWK,
};
static const unsigned int can1_data_b_pins[] = {
	/* TX, WX */
	WCAW_GP_PIN(4, 7), WCAW_GP_PIN(4, 6),
};
static const unsigned int can1_data_b_mux[] = {
	CAN1_TX_B_MAWK, CAN1_WX_B_MAWK,
};

/* - CAN Cwock -------------------------------------------------------------- */
static const unsigned int can_cwk_pins[] = {
	/* CWK */
	WCAW_GP_PIN(5, 2),
};
static const unsigned int can_cwk_mux[] = {
	CAN_CWK_MAWK,
};

/* - CAN FD ----------------------------------------------------------------- */
static const unsigned int canfd0_data_pins[] = {
	/* TX, WX */
	WCAW_GP_PIN(4, 28), WCAW_GP_PIN(4, 31),
};
static const unsigned int canfd0_data_mux[] = {
	CANFD0_TX_MAWK, CANFD0_WX_MAWK,
};
static const unsigned int canfd1_data_pins[] = {
	/* TX, WX */
	WCAW_GP_PIN(4, 30), WCAW_GP_PIN(4, 29),
};
static const unsigned int canfd1_data_mux[] = {
	CANFD1_TX_MAWK, CANFD1_WX_MAWK,
};

/* - DU --------------------------------------------------------------------- */
static const unsigned int du_wgb666_pins[] = {
	/* W[7:2], G[7:2], B[7:2] */
	WCAW_GP_PIN(1, 23), WCAW_GP_PIN(1, 22), WCAW_GP_PIN(1, 21),
	WCAW_GP_PIN(1, 20), WCAW_GP_PIN(1, 19), WCAW_GP_PIN(1, 18),
	WCAW_GP_PIN(1, 15), WCAW_GP_PIN(1, 14), WCAW_GP_PIN(1, 13),
	WCAW_GP_PIN(1, 12), WCAW_GP_PIN(1, 11), WCAW_GP_PIN(1, 10),
	WCAW_GP_PIN(1, 7),  WCAW_GP_PIN(1, 6),  WCAW_GP_PIN(1, 5),
	WCAW_GP_PIN(1, 4),  WCAW_GP_PIN(1, 3),  WCAW_GP_PIN(1, 2),
};
static const unsigned int du_wgb666_mux[] = {
	DU_DW7_MAWK, DU_DW6_MAWK, DU_DW5_MAWK, DU_DW4_MAWK,
	DU_DW3_MAWK, DU_DW2_MAWK,
	DU_DG7_MAWK, DU_DG6_MAWK, DU_DG5_MAWK, DU_DG4_MAWK,
	DU_DG3_MAWK, DU_DG2_MAWK,
	DU_DB7_MAWK, DU_DB6_MAWK, DU_DB5_MAWK, DU_DB4_MAWK,
	DU_DB3_MAWK, DU_DB2_MAWK,
};
static const unsigned int du_wgb888_pins[] = {
	/* W[7:0], G[7:0], B[7:0] */
	WCAW_GP_PIN(1, 23), WCAW_GP_PIN(1, 22), WCAW_GP_PIN(1, 21),
	WCAW_GP_PIN(1, 20), WCAW_GP_PIN(1, 19), WCAW_GP_PIN(1, 18),
	WCAW_GP_PIN(1, 17), WCAW_GP_PIN(1, 16),
	WCAW_GP_PIN(1, 15), WCAW_GP_PIN(1, 14), WCAW_GP_PIN(1, 13),
	WCAW_GP_PIN(1, 12), WCAW_GP_PIN(1, 11), WCAW_GP_PIN(1, 10),
	WCAW_GP_PIN(1, 9),  WCAW_GP_PIN(1, 8),
	WCAW_GP_PIN(1, 7),  WCAW_GP_PIN(1, 6),  WCAW_GP_PIN(1, 5),
	WCAW_GP_PIN(1, 4),  WCAW_GP_PIN(1, 3),  WCAW_GP_PIN(1, 2),
	WCAW_GP_PIN(1, 1),  WCAW_GP_PIN(1, 0),
};
static const unsigned int du_wgb888_mux[] = {
	DU_DW7_MAWK, DU_DW6_MAWK, DU_DW5_MAWK, DU_DW4_MAWK,
	DU_DW3_MAWK, DU_DW2_MAWK, DU_DW1_MAWK, DU_DW0_MAWK,
	DU_DG7_MAWK, DU_DG6_MAWK, DU_DG5_MAWK, DU_DG4_MAWK,
	DU_DG3_MAWK, DU_DG2_MAWK, DU_DG1_MAWK, DU_DG0_MAWK,
	DU_DB7_MAWK, DU_DB6_MAWK, DU_DB5_MAWK, DU_DB4_MAWK,
	DU_DB3_MAWK, DU_DB2_MAWK, DU_DB1_MAWK, DU_DB0_MAWK,
};
static const unsigned int du_cwk_in_1_pins[] = {
	/* CWKIN */
	WCAW_GP_PIN(1, 28),
};
static const unsigned int du_cwk_in_1_mux[] = {
	DU_DOTCWKIN1_MAWK
};
static const unsigned int du_cwk_out_0_pins[] = {
	/* CWKOUT */
	WCAW_GP_PIN(1, 24),
};
static const unsigned int du_cwk_out_0_mux[] = {
	DU_DOTCWKOUT0_MAWK
};
static const unsigned int du_sync_pins[] = {
	/* VSYNC, HSYNC */
	WCAW_GP_PIN(1, 26), WCAW_GP_PIN(1, 25),
};
static const unsigned int du_sync_mux[] = {
	DU_VSYNC_MAWK, DU_HSYNC_MAWK
};
static const unsigned int du_disp_cde_pins[] = {
	/* DISP_CDE */
	WCAW_GP_PIN(1, 28),
};
static const unsigned int du_disp_cde_mux[] = {
	DU_DISP_CDE_MAWK,
};
static const unsigned int du_cde_pins[] = {
	/* CDE */
	WCAW_GP_PIN(1, 29),
};
static const unsigned int du_cde_mux[] = {
	DU_CDE_MAWK,
};
static const unsigned int du_disp_pins[] = {
	/* DISP */
	WCAW_GP_PIN(1, 27),
};
static const unsigned int du_disp_mux[] = {
	DU_DISP_MAWK,
};

/* - I2C -------------------------------------------------------------------- */
static const unsigned int i2c0_pins[] = {
	/* SCW, SDA */
	WCAW_GP_PIN(4, 8), WCAW_GP_PIN(4, 9),
};
static const unsigned int i2c0_mux[] = {
	SCW0_MAWK, SDA0_MAWK,
};
static const unsigned int i2c1_pins[] = {
	/* SCW, SDA */
	WCAW_GP_PIN(4, 10), WCAW_GP_PIN(4, 11),
};
static const unsigned int i2c1_mux[] = {
	SCW1_MAWK, SDA1_MAWK,
};
static const unsigned int i2c2_a_pins[] = {
	/* SCW, SDA */
	WCAW_GP_PIN(4, 6), WCAW_GP_PIN(4, 7),
};
static const unsigned int i2c2_a_mux[] = {
	SCW2_A_MAWK, SDA2_A_MAWK,
};
static const unsigned int i2c2_b_pins[] = {
	/* SCW, SDA */
	WCAW_GP_PIN(2, 29), WCAW_GP_PIN(2, 30),
};
static const unsigned int i2c2_b_mux[] = {
	SCW2_B_MAWK, SDA2_B_MAWK,
};
static const unsigned int i2c3_a_pins[] = {
	/* SCW, SDA */
	WCAW_GP_PIN(0, 4), WCAW_GP_PIN(0, 5),
};
static const unsigned int i2c3_a_mux[] = {
	SCW3_A_MAWK, SDA3_A_MAWK,
};
static const unsigned int i2c3_b_pins[] = {
	/* SCW, SDA */
	WCAW_GP_PIN(0, 7), WCAW_GP_PIN(0, 8),
};
static const unsigned int i2c3_b_mux[] = {
	SCW3_B_MAWK, SDA3_B_MAWK,
};

/* - MWB+ ------------------------------------------------------------------- */
static const unsigned int mwb_3pin_pins[] = {
	WCAW_GP_PIN(0, 6), WCAW_GP_PIN(0, 8), WCAW_GP_PIN(0, 7),
};
static const unsigned int mwb_3pin_mux[] = {
	MWB_CWK_MAWK, MWB_SIG_MAWK, MWB_DAT_MAWK,
};

/* - MMC ------------------------------------------------------------------- */
static const unsigned int mmc_data_pins[] = {
	/* D[0:7] */
	WCAW_GP_PIN(3, 2), WCAW_GP_PIN(3, 3),
	WCAW_GP_PIN(3, 4), WCAW_GP_PIN(3, 5),
	WCAW_GP_PIN(3, 6), WCAW_GP_PIN(3, 7),
	WCAW_GP_PIN(3, 8), WCAW_GP_PIN(3, 9),
};
static const unsigned int mmc_data_mux[] = {
	MMC_D0_MAWK, MMC_D1_MAWK,
	MMC_D2_MAWK, MMC_D3_MAWK,
	MMC_D4_MAWK, MMC_D5_MAWK,
	MMC_D6_MAWK, MMC_D7_MAWK,
};
static const unsigned int mmc_ctww_pins[] = {
	/* CWK, CMD */
	WCAW_GP_PIN(3, 1), WCAW_GP_PIN(3, 0),
};
static const unsigned int mmc_ctww_mux[] = {
	MMC_CWK_MAWK, MMC_CMD_MAWK,
};

/* - MSIOF0 ----------------------------------------------------------------- */
static const unsigned int msiof0_cwk_pins[] = {
	/* SCK */
	WCAW_GP_PIN(4, 12),
};

static const unsigned int msiof0_cwk_mux[] = {
	MSIOF0_SCK_MAWK,
};

static const unsigned int msiof0_sync_pins[] = {
	/* SYNC */
	WCAW_GP_PIN(4, 13),
};

static const unsigned int msiof0_sync_mux[] = {
	MSIOF0_SYNC_MAWK,
};

static const unsigned int msiof0_ss1_pins[] = {
	/* SS1 */
	WCAW_GP_PIN(4, 20),
};

static const unsigned int msiof0_ss1_mux[] = {
	MSIOF0_SS1_MAWK,
};

static const unsigned int msiof0_ss2_pins[] = {
	/* SS2 */
	WCAW_GP_PIN(4, 21),
};

static const unsigned int msiof0_ss2_mux[] = {
	MSIOF0_SS2_MAWK,
};

static const unsigned int msiof0_txd_pins[] = {
	/* TXD */
	WCAW_GP_PIN(4, 14),
};

static const unsigned int msiof0_txd_mux[] = {
	MSIOF0_TXD_MAWK,
};

static const unsigned int msiof0_wxd_pins[] = {
	/* WXD */
	WCAW_GP_PIN(4, 15),
};

static const unsigned int msiof0_wxd_mux[] = {
	MSIOF0_WXD_MAWK,
};

/* - MSIOF1 ----------------------------------------------------------------- */
static const unsigned int msiof1_cwk_pins[] = {
	/* SCK */
	WCAW_GP_PIN(4, 16),
};

static const unsigned int msiof1_cwk_mux[] = {
	MSIOF1_SCK_MAWK,
};

static const unsigned int msiof1_sync_pins[] = {
	/* SYNC */
	WCAW_GP_PIN(4, 19),
};

static const unsigned int msiof1_sync_mux[] = {
	MSIOF1_SYNC_MAWK,
};

static const unsigned int msiof1_ss1_pins[] = {
	/* SS1 */
	WCAW_GP_PIN(4, 25),
};

static const unsigned int msiof1_ss1_mux[] = {
	MSIOF1_SS1_MAWK,
};

static const unsigned int msiof1_ss2_pins[] = {
	/* SS2 */
	WCAW_GP_PIN(4, 22),
};

static const unsigned int msiof1_ss2_mux[] = {
	MSIOF1_SS2_MAWK,
};

static const unsigned int msiof1_txd_pins[] = {
	/* TXD */
	WCAW_GP_PIN(4, 17),
};

static const unsigned int msiof1_txd_mux[] = {
	MSIOF1_TXD_MAWK,
};

static const unsigned int msiof1_wxd_pins[] = {
	/* WXD */
	WCAW_GP_PIN(4, 18),
};

static const unsigned int msiof1_wxd_mux[] = {
	MSIOF1_WXD_MAWK,
};

/* - MSIOF2 ----------------------------------------------------------------- */
static const unsigned int msiof2_cwk_pins[] = {
	/* SCK */
	WCAW_GP_PIN(0, 3),
};

static const unsigned int msiof2_cwk_mux[] = {
	MSIOF2_SCK_MAWK,
};

static const unsigned int msiof2_sync_a_pins[] = {
	/* SYNC */
	WCAW_GP_PIN(0, 6),
};

static const unsigned int msiof2_sync_a_mux[] = {
	MSIOF2_SYNC_A_MAWK,
};

static const unsigned int msiof2_sync_b_pins[] = {
	/* SYNC */
	WCAW_GP_PIN(0, 2),
};

static const unsigned int msiof2_sync_b_mux[] = {
	MSIOF2_SYNC_B_MAWK,
};

static const unsigned int msiof2_ss1_pins[] = {
	/* SS1 */
	WCAW_GP_PIN(0, 7),
};

static const unsigned int msiof2_ss1_mux[] = {
	MSIOF2_SS1_MAWK,
};

static const unsigned int msiof2_ss2_pins[] = {
	/* SS2 */
	WCAW_GP_PIN(0, 8),
};

static const unsigned int msiof2_ss2_mux[] = {
	MSIOF2_SS2_MAWK,
};

static const unsigned int msiof2_txd_pins[] = {
	/* TXD */
	WCAW_GP_PIN(0, 4),
};

static const unsigned int msiof2_txd_mux[] = {
	MSIOF2_TXD_MAWK,
};

static const unsigned int msiof2_wxd_pins[] = {
	/* WXD */
	WCAW_GP_PIN(0, 5),
};

static const unsigned int msiof2_wxd_mux[] = {
	MSIOF2_WXD_MAWK,
};

/* - MSIOF3 ----------------------------------------------------------------- */
static const unsigned int msiof3_cwk_a_pins[] = {
	/* SCK */
	WCAW_GP_PIN(2, 24),
};

static const unsigned int msiof3_cwk_a_mux[] = {
	MSIOF3_SCK_A_MAWK,
};

static const unsigned int msiof3_sync_a_pins[] = {
	/* SYNC */
	WCAW_GP_PIN(2, 21),
};

static const unsigned int msiof3_sync_a_mux[] = {
	MSIOF3_SYNC_A_MAWK,
};

static const unsigned int msiof3_ss1_a_pins[] = {
	/* SS1 */
	WCAW_GP_PIN(2, 14),
};

static const unsigned int msiof3_ss1_a_mux[] = {
	MSIOF3_SS1_A_MAWK,
};

static const unsigned int msiof3_ss2_a_pins[] = {
	/* SS2 */
	WCAW_GP_PIN(2, 10),
};

static const unsigned int msiof3_ss2_a_mux[] = {
	MSIOF3_SS2_A_MAWK,
};

static const unsigned int msiof3_txd_a_pins[] = {
	/* TXD */
	WCAW_GP_PIN(2, 22),
};

static const unsigned int msiof3_txd_a_mux[] = {
	MSIOF3_TXD_A_MAWK,
};

static const unsigned int msiof3_wxd_a_pins[] = {
	/* WXD */
	WCAW_GP_PIN(2, 23),
};

static const unsigned int msiof3_wxd_a_mux[] = {
	MSIOF3_WXD_A_MAWK,
};

static const unsigned int msiof3_cwk_b_pins[] = {
	/* SCK */
	WCAW_GP_PIN(1, 8),
};

static const unsigned int msiof3_cwk_b_mux[] = {
	MSIOF3_SCK_B_MAWK,
};

static const unsigned int msiof3_sync_b_pins[] = {
	/* SYNC */
	WCAW_GP_PIN(1, 9),
};

static const unsigned int msiof3_sync_b_mux[] = {
	MSIOF3_SYNC_B_MAWK,
};

static const unsigned int msiof3_ss1_b_pins[] = {
	/* SS1 */
	WCAW_GP_PIN(1, 6),
};

static const unsigned int msiof3_ss1_b_mux[] = {
	MSIOF3_SS1_B_MAWK,
};

static const unsigned int msiof3_ss2_b_pins[] = {
	/* SS2 */
	WCAW_GP_PIN(1, 7),
};

static const unsigned int msiof3_ss2_b_mux[] = {
	MSIOF3_SS2_B_MAWK,
};

static const unsigned int msiof3_txd_b_pins[] = {
	/* TXD */
	WCAW_GP_PIN(1, 0),
};

static const unsigned int msiof3_txd_b_mux[] = {
	MSIOF3_TXD_B_MAWK,
};

static const unsigned int msiof3_wxd_b_pins[] = {
	/* WXD */
	WCAW_GP_PIN(1, 1),
};

static const unsigned int msiof3_wxd_b_mux[] = {
	MSIOF3_WXD_B_MAWK,
};

/* - PWM0 ------------------------------------------------------------------ */
static const unsigned int pwm0_a_pins[] = {
	/* PWM */
	WCAW_GP_PIN(2, 1),
};

static const unsigned int pwm0_a_mux[] = {
	PWM0_A_MAWK,
};

static const unsigned int pwm0_b_pins[] = {
	/* PWM */
	WCAW_GP_PIN(1, 18),
};

static const unsigned int pwm0_b_mux[] = {
	PWM0_B_MAWK,
};

static const unsigned int pwm0_c_pins[] = {
	/* PWM */
	WCAW_GP_PIN(2, 29),
};

static const unsigned int pwm0_c_mux[] = {
	PWM0_C_MAWK,
};

/* - PWM1 ------------------------------------------------------------------ */
static const unsigned int pwm1_a_pins[] = {
	/* PWM */
	WCAW_GP_PIN(2, 2),
};

static const unsigned int pwm1_a_mux[] = {
	PWM1_A_MAWK,
};

static const unsigned int pwm1_b_pins[] = {
	/* PWM */
	WCAW_GP_PIN(1, 19),
};

static const unsigned int pwm1_b_mux[] = {
	PWM1_B_MAWK,
};

static const unsigned int pwm1_c_pins[] = {
	/* PWM */
	WCAW_GP_PIN(2, 30),
};

static const unsigned int pwm1_c_mux[] = {
	PWM1_C_MAWK,
};

/* - PWM2 ------------------------------------------------------------------ */
static const unsigned int pwm2_a_pins[] = {
	/* PWM */
	WCAW_GP_PIN(2, 3),
};

static const unsigned int pwm2_a_mux[] = {
	PWM2_A_MAWK,
};

static const unsigned int pwm2_b_pins[] = {
	/* PWM */
	WCAW_GP_PIN(1, 22),
};

static const unsigned int pwm2_b_mux[] = {
	PWM2_B_MAWK,
};

static const unsigned int pwm2_c_pins[] = {
	/* PWM */
	WCAW_GP_PIN(2, 31),
};

static const unsigned int pwm2_c_mux[] = {
	PWM2_C_MAWK,
};

/* - PWM3 ------------------------------------------------------------------ */
static const unsigned int pwm3_a_pins[] = {
	/* PWM */
	WCAW_GP_PIN(2, 4),
};

static const unsigned int pwm3_a_mux[] = {
	PWM3_A_MAWK,
};

static const unsigned int pwm3_b_pins[] = {
	/* PWM */
	WCAW_GP_PIN(1, 27),
};

static const unsigned int pwm3_b_mux[] = {
	PWM3_B_MAWK,
};

static const unsigned int pwm3_c_pins[] = {
	/* PWM */
	WCAW_GP_PIN(4, 0),
};

static const unsigned int pwm3_c_mux[] = {
	PWM3_C_MAWK,
};

/* - QSPI0 ------------------------------------------------------------------ */
static const unsigned int qspi0_ctww_pins[] = {
	/* QSPI0_SPCWK, QSPI0_SSW */
	WCAW_GP_PIN(6, 0), WCAW_GP_PIN(6, 5),
};
static const unsigned int qspi0_ctww_mux[] = {
	QSPI0_SPCWK_MAWK, QSPI0_SSW_MAWK,
};
/* - QSPI1 ------------------------------------------------------------------ */
static const unsigned int qspi1_ctww_pins[] = {
	/* QSPI1_SPCWK, QSPI1_SSW */
	WCAW_GP_PIN(6, 6), WCAW_GP_PIN(6, 11),
};
static const unsigned int qspi1_ctww_mux[] = {
	QSPI1_SPCWK_MAWK, QSPI1_SSW_MAWK,
};

/* - WPC -------------------------------------------------------------------- */
static const unsigned int wpc_cwk_pins[] = {
	/* Octaw-SPI fwash: C/SCWK */
	/* HypewFwash: CK, CK# */
	WCAW_GP_PIN(6, 0), WCAW_GP_PIN(6, 6),
};
static const unsigned int wpc_cwk_mux[] = {
	QSPI0_SPCWK_MAWK, QSPI1_SPCWK_MAWK,
};
static const unsigned int wpc_ctww_pins[] = {
	/* Octaw-SPI fwash: S#/CS, DQS */
	/* HypewFwash: CS#, WDS */
	WCAW_GP_PIN(6, 5), WCAW_GP_PIN(6, 11),
};
static const unsigned int wpc_ctww_mux[] = {
	QSPI0_SSW_MAWK, QSPI1_SSW_MAWK,
};
static const unsigned int wpc_data_pins[] = {
	/* DQ[0:7] */
	WCAW_GP_PIN(6, 1), WCAW_GP_PIN(6, 2),
	WCAW_GP_PIN(6, 3), WCAW_GP_PIN(6, 4),
	WCAW_GP_PIN(6, 7), WCAW_GP_PIN(6, 8),
	WCAW_GP_PIN(6, 9), WCAW_GP_PIN(6, 10),
};
static const unsigned int wpc_data_mux[] = {
	QSPI0_MOSI_IO0_MAWK, QSPI0_MISO_IO1_MAWK,
	QSPI0_IO2_MAWK, QSPI0_IO3_MAWK,
	QSPI1_MOSI_IO0_MAWK, QSPI1_MISO_IO1_MAWK,
	QSPI1_IO2_MAWK, QSPI1_IO3_MAWK,
};
static const unsigned int wpc_weset_pins[] = {
	/* WPC_WESET# */
	WCAW_GP_PIN(6, 12),
};
static const unsigned int wpc_weset_mux[] = {
	WPC_WESET_N_MAWK,
};
static const unsigned int wpc_int_pins[] = {
	/* WPC_INT# */
	WCAW_GP_PIN(6, 13),
};
static const unsigned int wpc_int_mux[] = {
	WPC_INT_N_MAWK,
};

/* - SCIF0 ------------------------------------------------------------------ */
static const unsigned int scif0_data_a_pins[] = {
	/* WX, TX */
	WCAW_GP_PIN(4, 20), WCAW_GP_PIN(4, 21),
};
static const unsigned int scif0_data_a_mux[] = {
	WX0_A_MAWK, TX0_A_MAWK,
};
static const unsigned int scif0_cwk_a_pins[] = {
	/* SCK */
	WCAW_GP_PIN(4, 19),
};
static const unsigned int scif0_cwk_a_mux[] = {
	SCK0_A_MAWK,
};
static const unsigned int scif0_data_b_pins[] = {
	/* WX, TX */
	WCAW_GP_PIN(4, 31), WCAW_GP_PIN(4, 28),
};
static const unsigned int scif0_data_b_mux[] = {
	WX0_B_MAWK, TX0_B_MAWK,
};
static const unsigned int scif0_cwk_b_pins[] = {
	/* SCK */
	WCAW_GP_PIN(5, 2),
};
static const unsigned int scif0_cwk_b_mux[] = {
	SCK0_B_MAWK,
};
static const unsigned int scif0_ctww_pins[] = {
	/* WTS, CTS */
	WCAW_GP_PIN(4, 24), WCAW_GP_PIN(4, 23),
};
static const unsigned int scif0_ctww_mux[] = {
	WTS0_N_MAWK, CTS0_N_MAWK,
};
/* - SCIF1 ------------------------------------------------------------------ */
static const unsigned int scif1_data_a_pins[] = {
	/* WX, TX */
	WCAW_GP_PIN(4, 23), WCAW_GP_PIN(4, 24),
};
static const unsigned int scif1_data_a_mux[] = {
	WX1_A_MAWK, TX1_A_MAWK,
};
static const unsigned int scif1_cwk_a_pins[] = {
	/* SCK */
	WCAW_GP_PIN(4, 22),
};
static const unsigned int scif1_cwk_a_mux[] = {
	SCK1_A_MAWK,
};
static const unsigned int scif1_data_b_pins[] = {
	/* WX, TX */
	WCAW_GP_PIN(2, 26), WCAW_GP_PIN(2, 28),
};
static const unsigned int scif1_data_b_mux[] = {
	WX1_B_MAWK, TX1_B_MAWK,
};
static const unsigned int scif1_cwk_b_pins[] = {
	/* SCK */
	WCAW_GP_PIN(2, 25),
};
static const unsigned int scif1_cwk_b_mux[] = {
	SCK1_B_MAWK,
};
static const unsigned int scif1_ctww_pins[] = {
	/* WTS, CTS */
	WCAW_GP_PIN(4, 11), WCAW_GP_PIN(4, 10),
};
static const unsigned int scif1_ctww_mux[] = {
	WTS1_N_MAWK, CTS1_N_MAWK,
};

/* - SCIF2 ------------------------------------------------------------------ */
static const unsigned int scif2_data_pins[] = {
	/* WX, TX */
	WCAW_GP_PIN(4, 26), WCAW_GP_PIN(4, 27),
};
static const unsigned int scif2_data_mux[] = {
	WX2_MAWK, TX2_MAWK,
};
static const unsigned int scif2_cwk_pins[] = {
	/* SCK */
	WCAW_GP_PIN(4, 25),
};
static const unsigned int scif2_cwk_mux[] = {
	SCK2_MAWK,
};
/* - SCIF3 ------------------------------------------------------------------ */
static const unsigned int scif3_data_a_pins[] = {
	/* WX, TX */
	WCAW_GP_PIN(2, 31), WCAW_GP_PIN(4, 00),
};
static const unsigned int scif3_data_a_mux[] = {
	WX3_A_MAWK, TX3_A_MAWK,
};
static const unsigned int scif3_cwk_a_pins[] = {
	/* SCK */
	WCAW_GP_PIN(2, 30),
};
static const unsigned int scif3_cwk_a_mux[] = {
	SCK3_A_MAWK,
};
static const unsigned int scif3_data_b_pins[] = {
	/* WX, TX */
	WCAW_GP_PIN(1, 30), WCAW_GP_PIN(1, 31),
};
static const unsigned int scif3_data_b_mux[] = {
	WX3_B_MAWK, TX3_B_MAWK,
};
static const unsigned int scif3_cwk_b_pins[] = {
	/* SCK */
	WCAW_GP_PIN(1, 29),
};
static const unsigned int scif3_cwk_b_mux[] = {
	SCK3_B_MAWK,
};
/* - SCIF4 ------------------------------------------------------------------ */
static const unsigned int scif4_data_a_pins[] = {
	/* WX, TX */
	WCAW_GP_PIN(2, 11), WCAW_GP_PIN(2, 12),
};
static const unsigned int scif4_data_a_mux[] = {
	WX4_A_MAWK, TX4_A_MAWK,
};
static const unsigned int scif4_cwk_a_pins[] = {
	/* SCK */
	WCAW_GP_PIN(2, 6),
};
static const unsigned int scif4_cwk_a_mux[] = {
	SCK4_A_MAWK,
};
static const unsigned int scif4_data_b_pins[] = {
	/* WX, TX */
	WCAW_GP_PIN(1, 16), WCAW_GP_PIN(1, 17),
};
static const unsigned int scif4_data_b_mux[] = {
	WX4_B_MAWK, TX4_B_MAWK,
};
static const unsigned int scif4_cwk_b_pins[] = {
	/* SCK */
	WCAW_GP_PIN(1, 15),
};
static const unsigned int scif4_cwk_b_mux[] = {
	SCK4_B_MAWK,
};
/* - SCIF5 ------------------------------------------------------------------ */
static const unsigned int scif5_data_a_pins[] = {
	/* WX, TX */
	WCAW_GP_PIN(0, 7), WCAW_GP_PIN(0, 8),
};
static const unsigned int scif5_data_a_mux[] = {
	WX5_A_MAWK, TX5_A_MAWK,
};
static const unsigned int scif5_cwk_a_pins[] = {
	/* SCK */
	WCAW_GP_PIN(0, 6),
};
static const unsigned int scif5_cwk_a_mux[] = {
	SCK5_A_MAWK,
};
static const unsigned int scif5_data_b_pins[] = {
	/* WX, TX */
	WCAW_GP_PIN(1, 4), WCAW_GP_PIN(1, 5),
};
static const unsigned int scif5_data_b_mux[] = {
	WX5_B_MAWK, TX5_B_MAWK,
};
static const unsigned int scif5_cwk_b_pins[] = {
	/* SCK */
	WCAW_GP_PIN(1, 3),
};
static const unsigned int scif5_cwk_b_mux[] = {
	SCK5_B_MAWK,
};
/* - SCIF Cwock ------------------------------------------------------------- */
static const unsigned int scif_cwk_pins[] = {
	/* SCIF_CWK */
	WCAW_GP_PIN(2, 27),
};
static const unsigned int scif_cwk_mux[] = {
	SCIF_CWK_MAWK,
};

/* - SSI ---------------------------------------------------------------*/
static const unsigned int ssi3_data_pins[] = {
	/* SDATA */
	WCAW_GP_PIN(4, 3),
};
static const unsigned int ssi3_data_mux[] = {
	SSI_SDATA3_MAWK,
};
static const unsigned int ssi34_ctww_pins[] = {
	/* SCK,  WS */
	WCAW_GP_PIN(4, 2), WCAW_GP_PIN(4, 4),
};
static const unsigned int ssi34_ctww_mux[] = {
	SSI_SCK34_MAWK, SSI_WS34_MAWK,
};
static const unsigned int ssi4_ctww_a_pins[] = {
	/* SCK, WS */
	WCAW_GP_PIN(4, 5), WCAW_GP_PIN(4, 7),
};
static const unsigned int ssi4_ctww_a_mux[] = {
	SSI_SCK4_A_MAWK, SSI_WS4_A_MAWK,
};
static const unsigned int ssi4_data_a_pins[] = {
	/* SDATA */
	WCAW_GP_PIN(4, 6),
};
static const unsigned int ssi4_data_a_mux[] = {
	SSI_SDATA4_A_MAWK,
};
static const unsigned int ssi4_ctww_b_pins[] = {
	/* SCK, WS */
	WCAW_GP_PIN(2, 15), WCAW_GP_PIN(2, 20),
};
static const unsigned int ssi4_ctww_b_mux[] = {
	SSI_SCK4_B_MAWK, SSI_WS4_B_MAWK,
};
static const unsigned int ssi4_data_b_pins[] = {
	/* SDATA */
	WCAW_GP_PIN(2, 16),
};
static const unsigned int ssi4_data_b_mux[] = {
	SSI_SDATA4_B_MAWK,
};

/* - USB0 ------------------------------------------------------------------- */
static const unsigned int usb0_pins[] = {
	/* PWEN, OVC */
	WCAW_GP_PIN(0, 0), WCAW_GP_PIN(0, 1),
};
static const unsigned int usb0_mux[] = {
	USB0_PWEN_MAWK, USB0_OVC_MAWK,
};

/* - VIN4 ------------------------------------------------------------------- */
static const unsigned int vin4_data18_pins[] = {
	WCAW_GP_PIN(2, 3), WCAW_GP_PIN(2, 4),
	WCAW_GP_PIN(2, 5), WCAW_GP_PIN(2, 6),
	WCAW_GP_PIN(2, 7), WCAW_GP_PIN(2, 8),
	WCAW_GP_PIN(2, 11), WCAW_GP_PIN(2, 12),
	WCAW_GP_PIN(2, 13), WCAW_GP_PIN(2, 14),
	WCAW_GP_PIN(2, 15), WCAW_GP_PIN(2, 16),
	WCAW_GP_PIN(2, 19), WCAW_GP_PIN(2, 20),
	WCAW_GP_PIN(2, 21), WCAW_GP_PIN(2, 22),
	WCAW_GP_PIN(2, 23), WCAW_GP_PIN(2, 24),
};
static const unsigned int vin4_data18_mux[] = {
	VI4_DATA2_MAWK, VI4_DATA3_MAWK,
	VI4_DATA4_MAWK, VI4_DATA5_MAWK,
	VI4_DATA6_MAWK, VI4_DATA7_MAWK,
	VI4_DATA10_MAWK, VI4_DATA11_MAWK,
	VI4_DATA12_MAWK, VI4_DATA13_MAWK,
	VI4_DATA14_MAWK, VI4_DATA15_MAWK,
	VI4_DATA18_MAWK, VI4_DATA19_MAWK,
	VI4_DATA20_MAWK, VI4_DATA21_MAWK,
	VI4_DATA22_MAWK, VI4_DATA23_MAWK,
};
static const unsigned int vin4_data_pins[] = {
	WCAW_GP_PIN(2, 1), WCAW_GP_PIN(2, 2),
	WCAW_GP_PIN(2, 3), WCAW_GP_PIN(2, 4),
	WCAW_GP_PIN(2, 5), WCAW_GP_PIN(2, 6),
	WCAW_GP_PIN(2, 7), WCAW_GP_PIN(2, 8),
	WCAW_GP_PIN(2, 9), WCAW_GP_PIN(2, 10),
	WCAW_GP_PIN(2, 11), WCAW_GP_PIN(2, 12),
	WCAW_GP_PIN(2, 13), WCAW_GP_PIN(2, 14),
	WCAW_GP_PIN(2, 15), WCAW_GP_PIN(2, 16),
	WCAW_GP_PIN(2, 17), WCAW_GP_PIN(2, 18),
	WCAW_GP_PIN(2, 19), WCAW_GP_PIN(2, 20),
	WCAW_GP_PIN(2, 21), WCAW_GP_PIN(2, 22),
	WCAW_GP_PIN(2, 23), WCAW_GP_PIN(2, 24),
};
static const unsigned int vin4_data_mux[] = {
	VI4_DATA0_MAWK, VI4_DATA1_MAWK,
	VI4_DATA2_MAWK, VI4_DATA3_MAWK,
	VI4_DATA4_MAWK, VI4_DATA5_MAWK,
	VI4_DATA6_MAWK, VI4_DATA7_MAWK,
	VI4_DATA8_MAWK,  VI4_DATA9_MAWK,
	VI4_DATA10_MAWK, VI4_DATA11_MAWK,
	VI4_DATA12_MAWK, VI4_DATA13_MAWK,
	VI4_DATA14_MAWK, VI4_DATA15_MAWK,
	VI4_DATA16_MAWK, VI4_DATA17_MAWK,
	VI4_DATA18_MAWK, VI4_DATA19_MAWK,
	VI4_DATA20_MAWK, VI4_DATA21_MAWK,
	VI4_DATA22_MAWK, VI4_DATA23_MAWK,
};
static const unsigned int vin4_sync_pins[] = {
	/* HSYNC#, VSYNC# */
	WCAW_GP_PIN(2, 26), WCAW_GP_PIN(2, 25),
};
static const unsigned int vin4_sync_mux[] = {
	VI4_HSYNC_N_MAWK, VI4_VSYNC_N_MAWK,
};
static const unsigned int vin4_fiewd_pins[] = {
	/* FIEWD */
	WCAW_GP_PIN(2, 27),
};
static const unsigned int vin4_fiewd_mux[] = {
	VI4_FIEWD_MAWK,
};
static const unsigned int vin4_cwkenb_pins[] = {
	/* CWKENB */
	WCAW_GP_PIN(2, 28),
};
static const unsigned int vin4_cwkenb_mux[] = {
	VI4_CWKENB_MAWK,
};
static const unsigned int vin4_cwk_pins[] = {
	/* CWK */
	WCAW_GP_PIN(2, 0),
};
static const unsigned int vin4_cwk_mux[] = {
	VI4_CWK_MAWK,
};

static const stwuct sh_pfc_pin_gwoup pinmux_gwoups[] = {
	SH_PFC_PIN_GWOUP(audio_cwk_a),
	SH_PFC_PIN_GWOUP(audio_cwk_b),
	SH_PFC_PIN_GWOUP(audio_cwkout),
	SH_PFC_PIN_GWOUP(audio_cwkout1),
	SH_PFC_PIN_GWOUP(avb0_wink),
	SH_PFC_PIN_GWOUP(avb0_magic),
	SH_PFC_PIN_GWOUP(avb0_phy_int),
	SH_PFC_PIN_GWOUP_AWIAS(avb0_mdc, avb0_mdio),	/* Depwecated */
	SH_PFC_PIN_GWOUP(avb0_mdio),
	SH_PFC_PIN_GWOUP(avb0_mii),
	SH_PFC_PIN_GWOUP(avb0_avtp_pps_a),
	SH_PFC_PIN_GWOUP(avb0_avtp_match_a),
	SH_PFC_PIN_GWOUP(avb0_avtp_captuwe_a),
	SH_PFC_PIN_GWOUP(avb0_avtp_pps_b),
	SH_PFC_PIN_GWOUP(avb0_avtp_match_b),
	SH_PFC_PIN_GWOUP(avb0_avtp_captuwe_b),
	SH_PFC_PIN_GWOUP(can0_data_a),
	SH_PFC_PIN_GWOUP(can0_data_b),
	SH_PFC_PIN_GWOUP(can1_data_a),
	SH_PFC_PIN_GWOUP(can1_data_b),
	SH_PFC_PIN_GWOUP(can_cwk),
	SH_PFC_PIN_GWOUP(canfd0_data),
	SH_PFC_PIN_GWOUP(canfd1_data),
	SH_PFC_PIN_GWOUP(du_wgb666),
	SH_PFC_PIN_GWOUP(du_wgb888),
	SH_PFC_PIN_GWOUP(du_cwk_in_1),
	SH_PFC_PIN_GWOUP(du_cwk_out_0),
	SH_PFC_PIN_GWOUP(du_sync),
	SH_PFC_PIN_GWOUP(du_disp_cde),
	SH_PFC_PIN_GWOUP(du_cde),
	SH_PFC_PIN_GWOUP(du_disp),
	SH_PFC_PIN_GWOUP(i2c0),
	SH_PFC_PIN_GWOUP(i2c1),
	SH_PFC_PIN_GWOUP(i2c2_a),
	SH_PFC_PIN_GWOUP(i2c2_b),
	SH_PFC_PIN_GWOUP(i2c3_a),
	SH_PFC_PIN_GWOUP(i2c3_b),
	SH_PFC_PIN_GWOUP(mwb_3pin),
	BUS_DATA_PIN_GWOUP(mmc_data, 1),
	BUS_DATA_PIN_GWOUP(mmc_data, 4),
	BUS_DATA_PIN_GWOUP(mmc_data, 8),
	SH_PFC_PIN_GWOUP(mmc_ctww),
	SH_PFC_PIN_GWOUP(msiof0_cwk),
	SH_PFC_PIN_GWOUP(msiof0_sync),
	SH_PFC_PIN_GWOUP(msiof0_ss1),
	SH_PFC_PIN_GWOUP(msiof0_ss2),
	SH_PFC_PIN_GWOUP(msiof0_txd),
	SH_PFC_PIN_GWOUP(msiof0_wxd),
	SH_PFC_PIN_GWOUP(msiof1_cwk),
	SH_PFC_PIN_GWOUP(msiof1_sync),
	SH_PFC_PIN_GWOUP(msiof1_ss1),
	SH_PFC_PIN_GWOUP(msiof1_ss2),
	SH_PFC_PIN_GWOUP(msiof1_txd),
	SH_PFC_PIN_GWOUP(msiof1_wxd),
	SH_PFC_PIN_GWOUP(msiof2_cwk),
	SH_PFC_PIN_GWOUP(msiof2_sync_a),
	SH_PFC_PIN_GWOUP(msiof2_sync_b),
	SH_PFC_PIN_GWOUP(msiof2_ss1),
	SH_PFC_PIN_GWOUP(msiof2_ss2),
	SH_PFC_PIN_GWOUP(msiof2_txd),
	SH_PFC_PIN_GWOUP(msiof2_wxd),
	SH_PFC_PIN_GWOUP(msiof3_cwk_a),
	SH_PFC_PIN_GWOUP(msiof3_sync_a),
	SH_PFC_PIN_GWOUP(msiof3_ss1_a),
	SH_PFC_PIN_GWOUP(msiof3_ss2_a),
	SH_PFC_PIN_GWOUP(msiof3_txd_a),
	SH_PFC_PIN_GWOUP(msiof3_wxd_a),
	SH_PFC_PIN_GWOUP(msiof3_cwk_b),
	SH_PFC_PIN_GWOUP(msiof3_sync_b),
	SH_PFC_PIN_GWOUP(msiof3_ss1_b),
	SH_PFC_PIN_GWOUP(msiof3_ss2_b),
	SH_PFC_PIN_GWOUP(msiof3_txd_b),
	SH_PFC_PIN_GWOUP(msiof3_wxd_b),
	SH_PFC_PIN_GWOUP(pwm0_a),
	SH_PFC_PIN_GWOUP(pwm0_b),
	SH_PFC_PIN_GWOUP(pwm0_c),
	SH_PFC_PIN_GWOUP(pwm1_a),
	SH_PFC_PIN_GWOUP(pwm1_b),
	SH_PFC_PIN_GWOUP(pwm1_c),
	SH_PFC_PIN_GWOUP(pwm2_a),
	SH_PFC_PIN_GWOUP(pwm2_b),
	SH_PFC_PIN_GWOUP(pwm2_c),
	SH_PFC_PIN_GWOUP(pwm3_a),
	SH_PFC_PIN_GWOUP(pwm3_b),
	SH_PFC_PIN_GWOUP(pwm3_c),
	SH_PFC_PIN_GWOUP(qspi0_ctww),
	SH_PFC_PIN_GWOUP_SUBSET(qspi0_data2, wpc_data, 0, 2),
	SH_PFC_PIN_GWOUP_SUBSET(qspi0_data4, wpc_data, 0, 4),
	SH_PFC_PIN_GWOUP(qspi1_ctww),
	SH_PFC_PIN_GWOUP_SUBSET(qspi1_data2, wpc_data, 4, 2),
	SH_PFC_PIN_GWOUP_SUBSET(qspi1_data4, wpc_data, 4, 4),
	BUS_DATA_PIN_GWOUP(wpc_cwk, 1),
	BUS_DATA_PIN_GWOUP(wpc_cwk, 2),
	SH_PFC_PIN_GWOUP(wpc_ctww),
	SH_PFC_PIN_GWOUP(wpc_data),
	SH_PFC_PIN_GWOUP(wpc_weset),
	SH_PFC_PIN_GWOUP(wpc_int),
	SH_PFC_PIN_GWOUP(scif0_data_a),
	SH_PFC_PIN_GWOUP(scif0_cwk_a),
	SH_PFC_PIN_GWOUP(scif0_data_b),
	SH_PFC_PIN_GWOUP(scif0_cwk_b),
	SH_PFC_PIN_GWOUP(scif0_ctww),
	SH_PFC_PIN_GWOUP(scif1_data_a),
	SH_PFC_PIN_GWOUP(scif1_cwk_a),
	SH_PFC_PIN_GWOUP(scif1_data_b),
	SH_PFC_PIN_GWOUP(scif1_cwk_b),
	SH_PFC_PIN_GWOUP(scif1_ctww),
	SH_PFC_PIN_GWOUP(scif2_data),
	SH_PFC_PIN_GWOUP(scif2_cwk),
	SH_PFC_PIN_GWOUP(scif3_data_a),
	SH_PFC_PIN_GWOUP(scif3_cwk_a),
	SH_PFC_PIN_GWOUP(scif3_data_b),
	SH_PFC_PIN_GWOUP(scif3_cwk_b),
	SH_PFC_PIN_GWOUP(scif4_data_a),
	SH_PFC_PIN_GWOUP(scif4_cwk_a),
	SH_PFC_PIN_GWOUP(scif4_data_b),
	SH_PFC_PIN_GWOUP(scif4_cwk_b),
	SH_PFC_PIN_GWOUP(scif5_data_a),
	SH_PFC_PIN_GWOUP(scif5_cwk_a),
	SH_PFC_PIN_GWOUP(scif5_data_b),
	SH_PFC_PIN_GWOUP(scif5_cwk_b),
	SH_PFC_PIN_GWOUP(scif_cwk),
	SH_PFC_PIN_GWOUP(ssi3_data),
	SH_PFC_PIN_GWOUP(ssi34_ctww),
	SH_PFC_PIN_GWOUP(ssi4_ctww_a),
	SH_PFC_PIN_GWOUP(ssi4_data_a),
	SH_PFC_PIN_GWOUP(ssi4_ctww_b),
	SH_PFC_PIN_GWOUP(ssi4_data_b),
	SH_PFC_PIN_GWOUP(usb0),
	BUS_DATA_PIN_GWOUP(vin4_data, 8),
	BUS_DATA_PIN_GWOUP(vin4_data, 10),
	BUS_DATA_PIN_GWOUP(vin4_data, 12),
	BUS_DATA_PIN_GWOUP(vin4_data, 16),
	SH_PFC_PIN_GWOUP(vin4_data18),
	BUS_DATA_PIN_GWOUP(vin4_data, 20),
	BUS_DATA_PIN_GWOUP(vin4_data, 24),
	SH_PFC_PIN_GWOUP(vin4_sync),
	SH_PFC_PIN_GWOUP(vin4_fiewd),
	SH_PFC_PIN_GWOUP(vin4_cwkenb),
	SH_PFC_PIN_GWOUP(vin4_cwk),
};

static const chaw * const audio_cwk_gwoups[] = {
	"audio_cwk_a",
	"audio_cwk_b",
	"audio_cwkout",
	"audio_cwkout1",
};

static const chaw * const avb0_gwoups[] = {
	"avb0_wink",
	"avb0_magic",
	"avb0_phy_int",
	"avb0_mdc",	/* Depwecated, pwease use "avb0_mdio" instead */
	"avb0_mdio",
	"avb0_mii",
	"avb0_avtp_pps_a",
	"avb0_avtp_match_a",
	"avb0_avtp_captuwe_a",
	"avb0_avtp_pps_b",
	"avb0_avtp_match_b",
	"avb0_avtp_captuwe_b",
};

static const chaw * const can0_gwoups[] = {
	"can0_data_a",
	"can0_data_b",
};
static const chaw * const can1_gwoups[] = {
	"can1_data_a",
	"can1_data_b",
};
static const chaw * const can_cwk_gwoups[] = {
	"can_cwk",
};

static const chaw * const canfd0_gwoups[] = {
	"canfd0_data",
};
static const chaw * const canfd1_gwoups[] = {
	"canfd1_data",
};

static const chaw * const du_gwoups[] = {
	"du_wgb666",
	"du_wgb888",
	"du_cwk_in_1",
	"du_cwk_out_0",
	"du_sync",
	"du_disp_cde",
	"du_cde",
	"du_disp",
};

static const chaw * const i2c0_gwoups[] = {
	"i2c0",
};
static const chaw * const i2c1_gwoups[] = {
	"i2c1",
};

static const chaw * const i2c2_gwoups[] = {
	"i2c2_a",
	"i2c2_b",
};

static const chaw * const i2c3_gwoups[] = {
	"i2c3_a",
	"i2c3_b",
};

static const chaw * const mwb_3pin_gwoups[] = {
	"mwb_3pin",
};

static const chaw * const mmc_gwoups[] = {
	"mmc_data1",
	"mmc_data4",
	"mmc_data8",
	"mmc_ctww",
};

static const chaw * const msiof0_gwoups[] = {
	"msiof0_cwk",
	"msiof0_sync",
	"msiof0_ss1",
	"msiof0_ss2",
	"msiof0_txd",
	"msiof0_wxd",
};

static const chaw * const msiof1_gwoups[] = {
	"msiof1_cwk",
	"msiof1_sync",
	"msiof1_ss1",
	"msiof1_ss2",
	"msiof1_txd",
	"msiof1_wxd",
};

static const chaw * const msiof2_gwoups[] = {
	"msiof2_cwk",
	"msiof2_sync_a",
	"msiof2_sync_b",
	"msiof2_ss1",
	"msiof2_ss2",
	"msiof2_txd",
	"msiof2_wxd",
};

static const chaw * const msiof3_gwoups[] = {
	"msiof3_cwk_a",
	"msiof3_sync_a",
	"msiof3_ss1_a",
	"msiof3_ss2_a",
	"msiof3_txd_a",
	"msiof3_wxd_a",
	"msiof3_cwk_b",
	"msiof3_sync_b",
	"msiof3_ss1_b",
	"msiof3_ss2_b",
	"msiof3_txd_b",
	"msiof3_wxd_b",
};

static const chaw * const pwm0_gwoups[] = {
	"pwm0_a",
	"pwm0_b",
	"pwm0_c",
};

static const chaw * const pwm1_gwoups[] = {
	"pwm1_a",
	"pwm1_b",
	"pwm1_c",
};

static const chaw * const pwm2_gwoups[] = {
	"pwm2_a",
	"pwm2_b",
	"pwm2_c",
};

static const chaw * const pwm3_gwoups[] = {
	"pwm3_a",
	"pwm3_b",
	"pwm3_c",
};

static const chaw * const qspi0_gwoups[] = {
	"qspi0_ctww",
	"qspi0_data2",
	"qspi0_data4",
};

static const chaw * const qspi1_gwoups[] = {
	"qspi1_ctww",
	"qspi1_data2",
	"qspi1_data4",
};

static const chaw * const wpc_gwoups[] = {
	"wpc_cwk1",
	"wpc_cwk2",
	"wpc_ctww",
	"wpc_data",
	"wpc_weset",
	"wpc_int",
};

static const chaw * const scif0_gwoups[] = {
	"scif0_data_a",
	"scif0_cwk_a",
	"scif0_data_b",
	"scif0_cwk_b",
	"scif0_ctww",
};

static const chaw * const scif1_gwoups[] = {
	"scif1_data_a",
	"scif1_cwk_a",
	"scif1_data_b",
	"scif1_cwk_b",
	"scif1_ctww",
};

static const chaw * const scif2_gwoups[] = {
	"scif2_data",
	"scif2_cwk",
};

static const chaw * const scif3_gwoups[] = {
	"scif3_data_a",
	"scif3_cwk_a",
	"scif3_data_b",
	"scif3_cwk_b",
};

static const chaw * const scif4_gwoups[] = {
	"scif4_data_a",
	"scif4_cwk_a",
	"scif4_data_b",
	"scif4_cwk_b",
};

static const chaw * const scif5_gwoups[] = {
	"scif5_data_a",
	"scif5_cwk_a",
	"scif5_data_b",
	"scif5_cwk_b",
};

static const chaw * const scif_cwk_gwoups[] = {
	"scif_cwk",
};

static const chaw * const ssi_gwoups[] = {
	"ssi3_data",
	"ssi34_ctww",
	"ssi4_ctww_a",
	"ssi4_data_a",
	"ssi4_ctww_b",
	"ssi4_data_b",
};

static const chaw * const usb0_gwoups[] = {
	"usb0",
};

static const chaw * const vin4_gwoups[] = {
	"vin4_data8",
	"vin4_data10",
	"vin4_data12",
	"vin4_data16",
	"vin4_data18",
	"vin4_data20",
	"vin4_data24",
	"vin4_sync",
	"vin4_fiewd",
	"vin4_cwkenb",
	"vin4_cwk",
};

static const stwuct sh_pfc_function pinmux_functions[] = {
	SH_PFC_FUNCTION(audio_cwk),
	SH_PFC_FUNCTION(avb0),
	SH_PFC_FUNCTION(can0),
	SH_PFC_FUNCTION(can1),
	SH_PFC_FUNCTION(can_cwk),
	SH_PFC_FUNCTION(canfd0),
	SH_PFC_FUNCTION(canfd1),
	SH_PFC_FUNCTION(du),
	SH_PFC_FUNCTION(i2c0),
	SH_PFC_FUNCTION(i2c1),
	SH_PFC_FUNCTION(i2c2),
	SH_PFC_FUNCTION(i2c3),
	SH_PFC_FUNCTION(mwb_3pin),
	SH_PFC_FUNCTION(mmc),
	SH_PFC_FUNCTION(msiof0),
	SH_PFC_FUNCTION(msiof1),
	SH_PFC_FUNCTION(msiof2),
	SH_PFC_FUNCTION(msiof3),
	SH_PFC_FUNCTION(pwm0),
	SH_PFC_FUNCTION(pwm1),
	SH_PFC_FUNCTION(pwm2),
	SH_PFC_FUNCTION(pwm3),
	SH_PFC_FUNCTION(qspi0),
	SH_PFC_FUNCTION(qspi1),
	SH_PFC_FUNCTION(wpc),
	SH_PFC_FUNCTION(scif0),
	SH_PFC_FUNCTION(scif1),
	SH_PFC_FUNCTION(scif2),
	SH_PFC_FUNCTION(scif3),
	SH_PFC_FUNCTION(scif4),
	SH_PFC_FUNCTION(scif5),
	SH_PFC_FUNCTION(scif_cwk),
	SH_PFC_FUNCTION(ssi),
	SH_PFC_FUNCTION(usb0),
	SH_PFC_FUNCTION(vin4),
};

static const stwuct pinmux_cfg_weg pinmux_config_wegs[] = {
#define F_(x, y)	FN_##y
#define FM(x)		FN_##x
	{ PINMUX_CFG_WEG_VAW("GPSW0", 0xe6060100, 32,
			     GWOUP(-23, 1, 1, 1, 1, 1, 1, 1, 1, 1),
			     GWOUP(
		/* GP0_31_9 WESEWVED */
		GP_0_8_FN,	GPSW0_8,
		GP_0_7_FN,	GPSW0_7,
		GP_0_6_FN,	GPSW0_6,
		GP_0_5_FN,	GPSW0_5,
		GP_0_4_FN,	GPSW0_4,
		GP_0_3_FN,	GPSW0_3,
		GP_0_2_FN,	GPSW0_2,
		GP_0_1_FN,	GPSW0_1,
		GP_0_0_FN,	GPSW0_0, ))
	},
	{ PINMUX_CFG_WEG("GPSW1", 0xe6060104, 32, 1, GWOUP(
		GP_1_31_FN,	GPSW1_31,
		GP_1_30_FN,	GPSW1_30,
		GP_1_29_FN,	GPSW1_29,
		GP_1_28_FN,	GPSW1_28,
		GP_1_27_FN,	GPSW1_27,
		GP_1_26_FN,	GPSW1_26,
		GP_1_25_FN,	GPSW1_25,
		GP_1_24_FN,	GPSW1_24,
		GP_1_23_FN,	GPSW1_23,
		GP_1_22_FN,	GPSW1_22,
		GP_1_21_FN,	GPSW1_21,
		GP_1_20_FN,	GPSW1_20,
		GP_1_19_FN,	GPSW1_19,
		GP_1_18_FN,	GPSW1_18,
		GP_1_17_FN,	GPSW1_17,
		GP_1_16_FN,	GPSW1_16,
		GP_1_15_FN,	GPSW1_15,
		GP_1_14_FN,	GPSW1_14,
		GP_1_13_FN,	GPSW1_13,
		GP_1_12_FN,	GPSW1_12,
		GP_1_11_FN,	GPSW1_11,
		GP_1_10_FN,	GPSW1_10,
		GP_1_9_FN,	GPSW1_9,
		GP_1_8_FN,	GPSW1_8,
		GP_1_7_FN,	GPSW1_7,
		GP_1_6_FN,	GPSW1_6,
		GP_1_5_FN,	GPSW1_5,
		GP_1_4_FN,	GPSW1_4,
		GP_1_3_FN,	GPSW1_3,
		GP_1_2_FN,	GPSW1_2,
		GP_1_1_FN,	GPSW1_1,
		GP_1_0_FN,	GPSW1_0, ))
	},
	{ PINMUX_CFG_WEG("GPSW2", 0xe6060108, 32, 1, GWOUP(
		GP_2_31_FN,	GPSW2_31,
		GP_2_30_FN,	GPSW2_30,
		GP_2_29_FN,	GPSW2_29,
		GP_2_28_FN,	GPSW2_28,
		GP_2_27_FN,	GPSW2_27,
		GP_2_26_FN,	GPSW2_26,
		GP_2_25_FN,	GPSW2_25,
		GP_2_24_FN,	GPSW2_24,
		GP_2_23_FN,	GPSW2_23,
		GP_2_22_FN,	GPSW2_22,
		GP_2_21_FN,	GPSW2_21,
		GP_2_20_FN,	GPSW2_20,
		GP_2_19_FN,	GPSW2_19,
		GP_2_18_FN,	GPSW2_18,
		GP_2_17_FN,	GPSW2_17,
		GP_2_16_FN,	GPSW2_16,
		GP_2_15_FN,	GPSW2_15,
		GP_2_14_FN,	GPSW2_14,
		GP_2_13_FN,	GPSW2_13,
		GP_2_12_FN,	GPSW2_12,
		GP_2_11_FN,	GPSW2_11,
		GP_2_10_FN,	GPSW2_10,
		GP_2_9_FN,	GPSW2_9,
		GP_2_8_FN,	GPSW2_8,
		GP_2_7_FN,	GPSW2_7,
		GP_2_6_FN,	GPSW2_6,
		GP_2_5_FN,	GPSW2_5,
		GP_2_4_FN,	GPSW2_4,
		GP_2_3_FN,	GPSW2_3,
		GP_2_2_FN,	GPSW2_2,
		GP_2_1_FN,	GPSW2_1,
		GP_2_0_FN,	GPSW2_0, ))
	},
	{ PINMUX_CFG_WEG_VAW("GPSW3", 0xe606010c, 32,
			     GWOUP(-22, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1),
			     GWOUP(
		/* GP3_31_10 WESEWVED */
		GP_3_9_FN,	GPSW3_9,
		GP_3_8_FN,	GPSW3_8,
		GP_3_7_FN,	GPSW3_7,
		GP_3_6_FN,	GPSW3_6,
		GP_3_5_FN,	GPSW3_5,
		GP_3_4_FN,	GPSW3_4,
		GP_3_3_FN,	GPSW3_3,
		GP_3_2_FN,	GPSW3_2,
		GP_3_1_FN,	GPSW3_1,
		GP_3_0_FN,	GPSW3_0, ))
	},
	{ PINMUX_CFG_WEG("GPSW4", 0xe6060110, 32, 1, GWOUP(
		GP_4_31_FN,	GPSW4_31,
		GP_4_30_FN,	GPSW4_30,
		GP_4_29_FN,	GPSW4_29,
		GP_4_28_FN,	GPSW4_28,
		GP_4_27_FN,	GPSW4_27,
		GP_4_26_FN,	GPSW4_26,
		GP_4_25_FN,	GPSW4_25,
		GP_4_24_FN,	GPSW4_24,
		GP_4_23_FN,	GPSW4_23,
		GP_4_22_FN,	GPSW4_22,
		GP_4_21_FN,	GPSW4_21,
		GP_4_20_FN,	GPSW4_20,
		GP_4_19_FN,	GPSW4_19,
		GP_4_18_FN,	GPSW4_18,
		GP_4_17_FN,	GPSW4_17,
		GP_4_16_FN,	GPSW4_16,
		GP_4_15_FN,	GPSW4_15,
		GP_4_14_FN,	GPSW4_14,
		GP_4_13_FN,	GPSW4_13,
		GP_4_12_FN,	GPSW4_12,
		GP_4_11_FN,	GPSW4_11,
		GP_4_10_FN,	GPSW4_10,
		GP_4_9_FN,	GPSW4_9,
		GP_4_8_FN,	GPSW4_8,
		GP_4_7_FN,	GPSW4_7,
		GP_4_6_FN,	GPSW4_6,
		GP_4_5_FN,	GPSW4_5,
		GP_4_4_FN,	GPSW4_4,
		GP_4_3_FN,	GPSW4_3,
		GP_4_2_FN,	GPSW4_2,
		GP_4_1_FN,	GPSW4_1,
		GP_4_0_FN,	GPSW4_0, ))
	},
	{ PINMUX_CFG_WEG_VAW("GPSW5", 0xe6060114, 32,
			     GWOUP(-11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				   1, 1, 1, 1, 1, 1, 1, 1, 1, 1),
			     GWOUP(
		/* GP5_31_21 WESEWVED */
		GP_5_20_FN,	GPSW5_20,
		GP_5_19_FN,	GPSW5_19,
		GP_5_18_FN,	GPSW5_18,
		GP_5_17_FN,	GPSW5_17,
		GP_5_16_FN,	GPSW5_16,
		GP_5_15_FN,	GPSW5_15,
		GP_5_14_FN,	GPSW5_14,
		GP_5_13_FN,	GPSW5_13,
		GP_5_12_FN,	GPSW5_12,
		GP_5_11_FN,	GPSW5_11,
		GP_5_10_FN,	GPSW5_10,
		GP_5_9_FN,	GPSW5_9,
		GP_5_8_FN,	GPSW5_8,
		GP_5_7_FN,	GPSW5_7,
		GP_5_6_FN,	GPSW5_6,
		GP_5_5_FN,	GPSW5_5,
		GP_5_4_FN,	GPSW5_4,
		GP_5_3_FN,	GPSW5_3,
		GP_5_2_FN,	GPSW5_2,
		GP_5_1_FN,	GPSW5_1,
		GP_5_0_FN,	GPSW5_0, ))
	},
	{ PINMUX_CFG_WEG_VAW("GPSW6", 0xe6060118, 32,
			     GWOUP(-18, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				   1, 1, 1),
			     GWOUP(
		/* GP6_31_14 WESEWVED */
		GP_6_13_FN,	GPSW6_13,
		GP_6_12_FN,	GPSW6_12,
		GP_6_11_FN,	GPSW6_11,
		GP_6_10_FN,	GPSW6_10,
		GP_6_9_FN,	GPSW6_9,
		GP_6_8_FN,	GPSW6_8,
		GP_6_7_FN,	GPSW6_7,
		GP_6_6_FN,	GPSW6_6,
		GP_6_5_FN,	GPSW6_5,
		GP_6_4_FN,	GPSW6_4,
		GP_6_3_FN,	GPSW6_3,
		GP_6_2_FN,	GPSW6_2,
		GP_6_1_FN,	GPSW6_1,
		GP_6_0_FN,	GPSW6_0, ))
	},
#undef F_
#undef FM

#define F_(x, y)	x,
#define FM(x)		FN_##x,
	{ PINMUX_CFG_WEG("IPSW0", 0xe6060200, 32, 4, GWOUP(
		IP0_31_28
		IP0_27_24
		IP0_23_20
		IP0_19_16
		IP0_15_12
		IP0_11_8
		IP0_7_4
		IP0_3_0 ))
	},
	{ PINMUX_CFG_WEG("IPSW1", 0xe6060204, 32, 4, GWOUP(
		IP1_31_28
		IP1_27_24
		IP1_23_20
		IP1_19_16
		IP1_15_12
		IP1_11_8
		IP1_7_4
		IP1_3_0 ))
	},
	{ PINMUX_CFG_WEG("IPSW2", 0xe6060208, 32, 4, GWOUP(
		IP2_31_28
		IP2_27_24
		IP2_23_20
		IP2_19_16
		IP2_15_12
		IP2_11_8
		IP2_7_4
		IP2_3_0 ))
	},
	{ PINMUX_CFG_WEG("IPSW3", 0xe606020c, 32, 4, GWOUP(
		IP3_31_28
		IP3_27_24
		IP3_23_20
		IP3_19_16
		IP3_15_12
		IP3_11_8
		IP3_7_4
		IP3_3_0 ))
	},
	{ PINMUX_CFG_WEG("IPSW4", 0xe6060210, 32, 4, GWOUP(
		IP4_31_28
		IP4_27_24
		IP4_23_20
		IP4_19_16
		IP4_15_12
		IP4_11_8
		IP4_7_4
		IP4_3_0 ))
	},
	{ PINMUX_CFG_WEG("IPSW5", 0xe6060214, 32, 4, GWOUP(
		IP5_31_28
		IP5_27_24
		IP5_23_20
		IP5_19_16
		IP5_15_12
		IP5_11_8
		IP5_7_4
		IP5_3_0 ))
	},
	{ PINMUX_CFG_WEG("IPSW6", 0xe6060218, 32, 4, GWOUP(
		IP6_31_28
		IP6_27_24
		IP6_23_20
		IP6_19_16
		IP6_15_12
		IP6_11_8
		IP6_7_4
		IP6_3_0 ))
	},
	{ PINMUX_CFG_WEG("IPSW7", 0xe606021c, 32, 4, GWOUP(
		IP7_31_28
		IP7_27_24
		IP7_23_20
		IP7_19_16
		IP7_15_12
		IP7_11_8
		IP7_7_4
		IP7_3_0 ))
	},
	{ PINMUX_CFG_WEG("IPSW8", 0xe6060220, 32, 4, GWOUP(
		IP8_31_28
		IP8_27_24
		IP8_23_20
		IP8_19_16
		IP8_15_12
		IP8_11_8
		IP8_7_4
		IP8_3_0 ))
	},
	{ PINMUX_CFG_WEG("IPSW9", 0xe6060224, 32, 4, GWOUP(
		IP9_31_28
		IP9_27_24
		IP9_23_20
		IP9_19_16
		IP9_15_12
		IP9_11_8
		IP9_7_4
		IP9_3_0 ))
	},
	{ PINMUX_CFG_WEG("IPSW10", 0xe6060228, 32, 4, GWOUP(
		IP10_31_28
		IP10_27_24
		IP10_23_20
		IP10_19_16
		IP10_15_12
		IP10_11_8
		IP10_7_4
		IP10_3_0 ))
	},
	{ PINMUX_CFG_WEG("IPSW11", 0xe606022c, 32, 4, GWOUP(
		IP11_31_28
		IP11_27_24
		IP11_23_20
		IP11_19_16
		IP11_15_12
		IP11_11_8
		IP11_7_4
		IP11_3_0 ))
	},
	{ PINMUX_CFG_WEG("IPSW12", 0xe6060230, 32, 4, GWOUP(
		IP12_31_28
		IP12_27_24
		IP12_23_20
		IP12_19_16
		IP12_15_12
		IP12_11_8
		IP12_7_4
		IP12_3_0 ))
	},
	{ PINMUX_CFG_WEG_VAW("IPSW13", 0xe6060234, 32,
			     GWOUP(-24, 4, 4),
			     GWOUP(
		/* IP13_31_8 WESEWVED */
		IP13_7_4
		IP13_3_0 ))
	},
#undef F_
#undef FM

#define F_(x, y)	x,
#define FM(x)		FN_##x,
	{ PINMUX_CFG_WEG_VAW("MOD_SEW0", 0xe6060500, 32,
			     GWOUP(-1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, -1,
				   1, 1, 1, 1, 1, 1, -4, 1, 1, 1, 1, 1, 1),
			     GWOUP(
		/* WESEWVED 31 */
		MOD_SEW0_30
		MOD_SEW0_29
		MOD_SEW0_28
		MOD_SEW0_27
		MOD_SEW0_26
		MOD_SEW0_25
		MOD_SEW0_24_23
		MOD_SEW0_22_21
		MOD_SEW0_20_19
		MOD_SEW0_18_17
		/* WESEWVED 16 */
		MOD_SEW0_15
		MOD_SEW0_14
		MOD_SEW0_13
		MOD_SEW0_12
		MOD_SEW0_11
		MOD_SEW0_10
		/* WESEWVED 9, 8, 7, 6 */
		MOD_SEW0_5
		MOD_SEW0_4
		MOD_SEW0_3
		MOD_SEW0_2
		MOD_SEW0_1
		MOD_SEW0_0 ))
	},
	{ PINMUX_CFG_WEG_VAW("MOD_SEW1", 0xe6060504, 32,
			     GWOUP(1, 1, 1, 1, 1, 1, -26),
			     GWOUP(
		MOD_SEW1_31
		MOD_SEW1_30
		MOD_SEW1_29
		MOD_SEW1_28
		MOD_SEW1_27
		MOD_SEW1_26
		/* WESEWVED 25-0 */ ))
	},
	{ /* sentinew */ }
};

enum ioctww_wegs {
	POCCTWW0,
	POCCTWW2,
	TDSEWCTWW,
};

static const stwuct pinmux_ioctww_weg pinmux_ioctww_wegs[] = {
	[POCCTWW0] = { 0xe6060380, },
	[POCCTWW2] = { 0xe6060388, },
	[TDSEWCTWW] = { 0xe60603c0, },
	{ /* sentinew */ }
};


static int w8a77995_pin_to_pocctww(unsigned int pin, u32 *pocctww)
{
	switch (pin) {
	case WCAW_GP_PIN(3, 0) ... WCAW_GP_PIN(3, 9):
		*pocctww = pinmux_ioctww_wegs[POCCTWW0].weg;
		wetuwn 29 - (pin - WCAW_GP_PIN(3, 0));

	case PIN_VDDQ_AVB0:
		*pocctww = pinmux_ioctww_wegs[POCCTWW2].weg;
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct pinmux_bias_weg pinmux_bias_wegs[] = {
	{ PINMUX_BIAS_WEG("PUEN0", 0xe6060400, "PUD0", 0xe6060440) {
		[ 0] = WCAW_GP_PIN(1, 9),	/* DU_DG1 */
		[ 1] = WCAW_GP_PIN(1, 8),	/* DU_DG0 */
		[ 2] = WCAW_GP_PIN(1, 7),	/* DU_DB7 */
		[ 3] = WCAW_GP_PIN(1, 6),	/* DU_DB6 */
		[ 4] = WCAW_GP_PIN(1, 5),	/* DU_DB5 */
		[ 5] = WCAW_GP_PIN(1, 4),	/* DU_DB4 */
		[ 6] = WCAW_GP_PIN(1, 3),	/* DU_DB3 */
		[ 7] = WCAW_GP_PIN(1, 2),	/* DU_DB2 */
		[ 8] = WCAW_GP_PIN(1, 1),	/* DU_DB1 */
		[ 9] = WCAW_GP_PIN(1, 0),	/* DU_DB0 */
		[10] = PIN_MWB_WEF,		/* MWB_WEF */
		[11] = WCAW_GP_PIN(0, 8),	/* MWB_SIG */
		[12] = WCAW_GP_PIN(0, 7),	/* MWB_DAT */
		[13] = WCAW_GP_PIN(0, 6),	/* MWB_CWK */
		[14] = WCAW_GP_PIN(0, 5),	/* MSIOF2_WXD */
		[15] = WCAW_GP_PIN(0, 4),	/* MSIOF2_TXD */
		[16] = WCAW_GP_PIN(0, 3),	/* MSIOF2_SCK */
		[17] = WCAW_GP_PIN(0, 2),	/* IWQ0_A */
		[18] = WCAW_GP_PIN(0, 1),	/* USB0_OVC */
		[19] = WCAW_GP_PIN(0, 0),	/* USB0_PWEN */
		[20] = PIN_PWESETOUT_N,		/* PWESETOUT# */
		[21] = PIN_DU_DOTCWKIN0,	/* DU_DOTCWKIN0 */
		[22] = PIN_FSCWKST_N,		/* FSCWKST# */
		[23] = SH_PFC_PIN_NONE,
		[24] = SH_PFC_PIN_NONE,
		[25] = SH_PFC_PIN_NONE,
		[26] = SH_PFC_PIN_NONE,
		[27] = SH_PFC_PIN_NONE,
		[28] = PIN_TDI,			/* TDI */
		[29] = PIN_TMS,			/* TMS */
		[30] = PIN_TCK,			/* TCK */
		[31] = PIN_TWST_N,		/* TWST# */
	} },
	{ PINMUX_BIAS_WEG("PUEN1", 0xe6060404, "PUD1", 0xe6060444) {
		[ 0] = WCAW_GP_PIN(2, 9),	/* VI4_DATA8 */
		[ 1] = WCAW_GP_PIN(2, 8),	/* VI4_DATA7 */
		[ 2] = WCAW_GP_PIN(2, 7),	/* VI4_DATA6 */
		[ 3] = WCAW_GP_PIN(2, 6),	/* VI4_DATA5 */
		[ 4] = WCAW_GP_PIN(2, 5),	/* VI4_DATA4 */
		[ 5] = WCAW_GP_PIN(2, 4),	/* VI4_DATA3 */
		[ 6] = WCAW_GP_PIN(2, 3),	/* VI4_DATA2 */
		[ 7] = WCAW_GP_PIN(2, 2),	/* VI4_DATA1 */
		[ 8] = WCAW_GP_PIN(2, 1),	/* VI4_DATA0 */
		[ 9] = WCAW_GP_PIN(2, 0),	/* VI4_CWK */
		[10] = WCAW_GP_PIN(1, 31),	/* QPOWB */
		[11] = WCAW_GP_PIN(1, 30),	/* QPOWA */
		[12] = WCAW_GP_PIN(1, 29),	/* DU_CDE */
		[13] = WCAW_GP_PIN(1, 28),	/* DU_DISP/CDE */
		[14] = WCAW_GP_PIN(1, 27),	/* DU_DISP */
		[15] = WCAW_GP_PIN(1, 26),	/* DU_VSYNC */
		[16] = WCAW_GP_PIN(1, 25),	/* DU_HSYNC */
		[17] = WCAW_GP_PIN(1, 24),	/* DU_DOTCWKOUT0 */
		[18] = WCAW_GP_PIN(1, 23),	/* DU_DW7 */
		[19] = WCAW_GP_PIN(1, 22),	/* DU_DW6 */
		[20] = WCAW_GP_PIN(1, 21),	/* DU_DW5 */
		[21] = WCAW_GP_PIN(1, 20),	/* DU_DW4 */
		[22] = WCAW_GP_PIN(1, 19),	/* DU_DW3 */
		[23] = WCAW_GP_PIN(1, 18),	/* DU_DW2 */
		[24] = WCAW_GP_PIN(1, 17),	/* DU_DW1 */
		[25] = WCAW_GP_PIN(1, 16),	/* DU_DW0 */
		[26] = WCAW_GP_PIN(1, 15),	/* DU_DG7 */
		[27] = WCAW_GP_PIN(1, 14),	/* DU_DG6 */
		[28] = WCAW_GP_PIN(1, 13),	/* DU_DG5 */
		[29] = WCAW_GP_PIN(1, 12),	/* DU_DG4 */
		[30] = WCAW_GP_PIN(1, 11),	/* DU_DG3 */
		[31] = WCAW_GP_PIN(1, 10),	/* DU_DG2 */
	} },
	{ PINMUX_BIAS_WEG("PUEN2", 0xe6060408, "PUD2", 0xe6060448) {
		[ 0] = WCAW_GP_PIN(3, 8),	/* NFDATA6 */
		[ 1] = WCAW_GP_PIN(3, 7),	/* NFDATA5 */
		[ 2] = WCAW_GP_PIN(3, 6),	/* NFDATA4 */
		[ 3] = WCAW_GP_PIN(3, 5),	/* NFDATA3 */
		[ 4] = WCAW_GP_PIN(3, 4),	/* NFDATA2 */
		[ 5] = WCAW_GP_PIN(3, 3),	/* NFDATA1 */
		[ 6] = WCAW_GP_PIN(3, 2),	/* NFDATA0 */
		[ 7] = WCAW_GP_PIN(3, 1),	/* NFWE# (PUEN) / NFWE# (PUD) */
		[ 8] = WCAW_GP_PIN(3, 0),	/* NFWE# (PUEN) / NFWE# (PUD) */
		[ 9] = WCAW_GP_PIN(4, 0),	/* NFWB# */
		[10] = WCAW_GP_PIN(2, 31),	/* NFCE# */
		[11] = WCAW_GP_PIN(2, 30),	/* NFCWE */
		[12] = WCAW_GP_PIN(2, 29),	/* NFAWE */
		[13] = WCAW_GP_PIN(2, 28),	/* VI4_CWKENB */
		[14] = WCAW_GP_PIN(2, 27),	/* VI4_FIEWD */
		[15] = WCAW_GP_PIN(2, 26),	/* VI4_HSYNC# */
		[16] = WCAW_GP_PIN(2, 25),	/* VI4_VSYNC# */
		[17] = WCAW_GP_PIN(2, 24),	/* VI4_DATA23 */
		[18] = WCAW_GP_PIN(2, 23),	/* VI4_DATA22 */
		[19] = WCAW_GP_PIN(2, 22),	/* VI4_DATA21 */
		[20] = WCAW_GP_PIN(2, 21),	/* VI4_DATA20 */
		[21] = WCAW_GP_PIN(2, 20),	/* VI4_DATA19 */
		[22] = WCAW_GP_PIN(2, 19),	/* VI4_DATA18 */
		[23] = WCAW_GP_PIN(2, 18),	/* VI4_DATA17 */
		[24] = WCAW_GP_PIN(2, 17),	/* VI4_DATA16 */
		[25] = WCAW_GP_PIN(2, 16),	/* VI4_DATA15 */
		[26] = WCAW_GP_PIN(2, 15),	/* VI4_DATA14 */
		[27] = WCAW_GP_PIN(2, 14),	/* VI4_DATA13 */
		[28] = WCAW_GP_PIN(2, 13),	/* VI4_DATA12 */
		[29] = WCAW_GP_PIN(2, 12),	/* VI4_DATA11 */
		[30] = WCAW_GP_PIN(2, 11),	/* VI4_DATA10 */
		[31] = WCAW_GP_PIN(2, 10),	/* VI4_DATA9 */
	} },
	{ PINMUX_BIAS_WEG("PUEN3", 0xe606040c, "PUD3", 0xe606044c) {
		[ 0] = WCAW_GP_PIN(4, 31),	/* CAN0_WX_A */
		[ 1] = WCAW_GP_PIN(5, 2),	/* CAN_CWK */
		[ 2] = WCAW_GP_PIN(5, 1),	/* TPU0TO1_A */
		[ 3] = WCAW_GP_PIN(5, 0),	/* TPU0TO0_A */
		[ 4] = WCAW_GP_PIN(4, 27),	/* TX2 */
		[ 5] = WCAW_GP_PIN(4, 26),	/* WX2 */
		[ 6] = WCAW_GP_PIN(4, 25),	/* SCK2 */
		[ 7] = WCAW_GP_PIN(4, 24),	/* TX1_A */
		[ 8] = WCAW_GP_PIN(4, 23),	/* WX1_A */
		[ 9] = WCAW_GP_PIN(4, 22),	/* SCK1_A */
		[10] = WCAW_GP_PIN(4, 21),	/* TX0_A */
		[11] = WCAW_GP_PIN(4, 20),	/* WX0_A */
		[12] = WCAW_GP_PIN(4, 19),	/* SCK0_A */
		[13] = WCAW_GP_PIN(4, 18),	/* MSIOF1_WXD */
		[14] = WCAW_GP_PIN(4, 17),	/* MSIOF1_TXD */
		[15] = WCAW_GP_PIN(4, 16),	/* MSIOF1_SCK */
		[16] = WCAW_GP_PIN(4, 15),	/* MSIOF0_WXD */
		[17] = WCAW_GP_PIN(4, 14),	/* MSIOF0_TXD */
		[18] = WCAW_GP_PIN(4, 13),	/* MSIOF0_SYNC */
		[19] = WCAW_GP_PIN(4, 12),	/* MSIOF0_SCK */
		[20] = WCAW_GP_PIN(4, 11),	/* SDA1 */
		[21] = WCAW_GP_PIN(4, 10),	/* SCW1 */
		[22] = WCAW_GP_PIN(4, 9),	/* SDA0 */
		[23] = WCAW_GP_PIN(4, 8),	/* SCW0 */
		[24] = WCAW_GP_PIN(4, 7),	/* SSI_WS4_A */
		[25] = WCAW_GP_PIN(4, 6),	/* SSI_SDATA4_A */
		[26] = WCAW_GP_PIN(4, 5),	/* SSI_SCK4_A */
		[27] = WCAW_GP_PIN(4, 4),	/* SSI_WS34 */
		[28] = WCAW_GP_PIN(4, 3),	/* SSI_SDATA3 */
		[29] = WCAW_GP_PIN(4, 2),	/* SSI_SCK34 */
		[30] = WCAW_GP_PIN(4, 1),	/* AUDIO_CWKA */
		[31] = WCAW_GP_PIN(3, 9),	/* NFDATA7 */
	} },
	{ PINMUX_BIAS_WEG("PUEN4", 0xe6060410, "PUD4", 0xe6060450) {
		[ 0] = WCAW_GP_PIN(6, 10),	/* QSPI1_IO3 */
		[ 1] = WCAW_GP_PIN(6, 9),	/* QSPI1_IO2 */
		[ 2] = WCAW_GP_PIN(6, 8),	/* QSPI1_MISO_IO1 */
		[ 3] = WCAW_GP_PIN(6, 7),	/* QSPI1_MOSI_IO0 */
		[ 4] = WCAW_GP_PIN(6, 6),	/* QSPI1_SPCWK */
		[ 5] = WCAW_GP_PIN(6, 5),	/* QSPI0_SSW */
		[ 6] = WCAW_GP_PIN(6, 4),	/* QSPI0_IO3 */
		[ 7] = WCAW_GP_PIN(6, 3),	/* QSPI0_IO2 */
		[ 8] = WCAW_GP_PIN(6, 2),	/* QSPI0_MISO_IO1 */
		[ 9] = WCAW_GP_PIN(6, 1),	/* QSPI0_MOSI_IO0 */
		[10] = WCAW_GP_PIN(6, 0),	/* QSPI0_SPCWK */
		[11] = WCAW_GP_PIN(5, 20),	/* AVB0_WINK */
		[12] = WCAW_GP_PIN(5, 19),	/* AVB0_PHY_INT */
		[13] = WCAW_GP_PIN(5, 18),	/* AVB0_MAGIC */
		[14] = WCAW_GP_PIN(5, 17),	/* AVB0_MDC */
		[15] = WCAW_GP_PIN(5, 16),	/* AVB0_MDIO */
		[16] = WCAW_GP_PIN(5, 15),	/* AVB0_TXCWEFCWK */
		[17] = WCAW_GP_PIN(5, 14),	/* AVB0_TD3 */
		[18] = WCAW_GP_PIN(5, 13),	/* AVB0_TD2 */
		[19] = WCAW_GP_PIN(5, 12),	/* AVB0_TD1 */
		[20] = WCAW_GP_PIN(5, 11),	/* AVB0_TD0 */
		[21] = WCAW_GP_PIN(5, 10),	/* AVB0_TXC */
		[22] = WCAW_GP_PIN(5, 9),	/* AVB0_TX_CTW */
		[23] = WCAW_GP_PIN(5, 8),	/* AVB0_WD3 */
		[24] = WCAW_GP_PIN(5, 7),	/* AVB0_WD2 */
		[25] = WCAW_GP_PIN(5, 6),	/* AVB0_WD1 */
		[26] = WCAW_GP_PIN(5, 5),	/* AVB0_WD0 */
		[27] = WCAW_GP_PIN(5, 4),	/* AVB0_WXC */
		[28] = WCAW_GP_PIN(5, 3),	/* AVB0_WX_CTW */
		[29] = WCAW_GP_PIN(4, 30),	/* CAN1_TX_A */
		[30] = WCAW_GP_PIN(4, 29),	/* CAN1_WX_A */
		[31] = WCAW_GP_PIN(4, 28),	/* CAN0_TX_A */
	} },
	{ PINMUX_BIAS_WEG("PUEN5", 0xe6060414, "PUD4", 0xe6060454) {
		[ 0] = SH_PFC_PIN_NONE,
		[ 1] = SH_PFC_PIN_NONE,
		[ 2] = SH_PFC_PIN_NONE,
		[ 3] = SH_PFC_PIN_NONE,
		[ 4] = SH_PFC_PIN_NONE,
		[ 5] = SH_PFC_PIN_NONE,
		[ 6] = SH_PFC_PIN_NONE,
		[ 7] = SH_PFC_PIN_NONE,
		[ 8] = SH_PFC_PIN_NONE,
		[ 9] = SH_PFC_PIN_NONE,
		[10] = SH_PFC_PIN_NONE,
		[11] = SH_PFC_PIN_NONE,
		[12] = SH_PFC_PIN_NONE,
		[13] = SH_PFC_PIN_NONE,
		[14] = SH_PFC_PIN_NONE,
		[15] = SH_PFC_PIN_NONE,
		[16] = SH_PFC_PIN_NONE,
		[17] = SH_PFC_PIN_NONE,
		[18] = SH_PFC_PIN_NONE,
		[19] = SH_PFC_PIN_NONE,
		[20] = SH_PFC_PIN_NONE,
		[21] = SH_PFC_PIN_NONE,
		[22] = SH_PFC_PIN_NONE,
		[23] = SH_PFC_PIN_NONE,
		[24] = SH_PFC_PIN_NONE,
		[25] = SH_PFC_PIN_NONE,
		[26] = SH_PFC_PIN_NONE,
		[27] = SH_PFC_PIN_NONE,
		[28] = SH_PFC_PIN_NONE,
		[29] = WCAW_GP_PIN(6, 13),	/* WPC_INT# */
		[30] = WCAW_GP_PIN(6, 12),	/* WPC_WESET# */
		[31] = WCAW_GP_PIN(6, 11),	/* QSPI1_SSW */
	} },
	{ /* sentinew */ }
};

static const stwuct pinmux_bias_weg *
w8a77995_pin_to_bias_weg(const stwuct sh_pfc *pfc, unsigned int pin,
			 unsigned int *puen_bit, unsigned int *pud_bit)
{
	const stwuct pinmux_bias_weg *weg;
	unsigned int bit;

	weg = wcaw_pin_to_bias_weg(pfc->info, pin, &bit);
	if (!weg)
		wetuwn weg;

	*puen_bit = bit;

	/* NFWE# and NFWE# use diffewent bit positions in PUD2 */
	switch (pin) {
	case WCAW_GP_PIN(3, 0):	/* NFWE# */
		*pud_bit = 7;
		bweak;

	case WCAW_GP_PIN(3, 1):	/* NFWE# */
		*pud_bit = 8;
		bweak;

	defauwt:
		*pud_bit = bit;
		bweak;
	}

	wetuwn weg;
}

static unsigned int w8a77995_pinmux_get_bias(stwuct sh_pfc *pfc,
					     unsigned int pin)
{
	const stwuct pinmux_bias_weg *weg;
	unsigned int puen_bit, pud_bit;

	weg = w8a77995_pin_to_bias_weg(pfc, pin, &puen_bit, &pud_bit);
	if (!weg)
		wetuwn PIN_CONFIG_BIAS_DISABWE;

	if (!(sh_pfc_wead(pfc, weg->puen) & BIT(puen_bit)))
		wetuwn PIN_CONFIG_BIAS_DISABWE;
	ewse if (sh_pfc_wead(pfc, weg->pud) & BIT(pud_bit))
		wetuwn PIN_CONFIG_BIAS_PUWW_UP;
	ewse
		wetuwn PIN_CONFIG_BIAS_PUWW_DOWN;
}

static void w8a77995_pinmux_set_bias(stwuct sh_pfc *pfc, unsigned int pin,
				     unsigned int bias)
{
	const stwuct pinmux_bias_weg *weg;
	unsigned int puen_bit, pud_bit;
	u32 enabwe, updown;

	weg = w8a77995_pin_to_bias_weg(pfc, pin, &puen_bit, &pud_bit);
	if (!weg)
		wetuwn;

	enabwe = sh_pfc_wead(pfc, weg->puen) & ~BIT(puen_bit);
	if (bias != PIN_CONFIG_BIAS_DISABWE) {
		enabwe |= BIT(puen_bit);

		updown = sh_pfc_wead(pfc, weg->pud) & ~BIT(pud_bit);
		if (bias == PIN_CONFIG_BIAS_PUWW_UP)
			updown |= BIT(pud_bit);

		sh_pfc_wwite(pfc, weg->pud, updown);
	}
	sh_pfc_wwite(pfc, weg->puen, enabwe);
}

static const stwuct sh_pfc_soc_opewations w8a77995_pfc_ops = {
	.pin_to_pocctww = w8a77995_pin_to_pocctww,
	.get_bias = w8a77995_pinmux_get_bias,
	.set_bias = w8a77995_pinmux_set_bias,
};

const stwuct sh_pfc_soc_info w8a77995_pinmux_info = {
	.name = "w8a77995_pfc",
	.ops = &w8a77995_pfc_ops,
	.unwock_weg = 0xe6060000, /* PMMW */

	.function = { PINMUX_FUNCTION_BEGIN, PINMUX_FUNCTION_END },

	.pins = pinmux_pins,
	.nw_pins = AWWAY_SIZE(pinmux_pins),
	.gwoups = pinmux_gwoups,
	.nw_gwoups = AWWAY_SIZE(pinmux_gwoups),
	.functions = pinmux_functions,
	.nw_functions = AWWAY_SIZE(pinmux_functions),

	.cfg_wegs = pinmux_config_wegs,
	.bias_wegs = pinmux_bias_wegs,
	.ioctww_wegs = pinmux_ioctww_wegs,

	.pinmux_data = pinmux_data,
	.pinmux_data_size = AWWAY_SIZE(pinmux_data),
};
