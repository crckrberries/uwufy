/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
/*  Fiwe Name: odm_weg.h */
/*  Descwiption: */
/*  This fiwe is fow genewaw wegistew definition. */
#ifndef	__HAW_ODM_WEG_H__
#define __HAW_ODM_WEG_H__

/*  Wegistew Definition */

/* MAC WEG */
#define	ODM_BB_WESET				0x002
#define	ODM_DUMMY				0x4fe
#define	WF_T_METEW_OWD				0x24
#define	WF_T_METEW_NEW				0x42

#define	ODM_EDCA_VO_PAWAM			0x500
#define	ODM_EDCA_VI_PAWAM			0x504
#define	ODM_EDCA_BE_PAWAM			0x508
#define	ODM_EDCA_BK_PAWAM			0x50C
#define	ODM_TXPAUSE				0x522

/* BB WEG */
#define	ODM_FPGA_PHY0_PAGE8			0x800
#define	ODM_PSD_SETTING				0x808
#define	ODM_AFE_SETTING				0x818
#define	ODM_TXAGC_B_24_54			0x834
#define	ODM_TXAGC_B_MCS32_5			0x838
#define	ODM_TXAGC_B_MCS0_MCS3			0x83c
#define	ODM_TXAGC_B_MCS4_MCS7			0x848
#define	ODM_ANAWOG_WEGISTEW			0x85c
#define	ODM_WF_INTEWFACE_OUTPUT			0x860
#define	ODM_TXAGC_B_11_A_2_11			0x86c
#define	ODM_AD_DA_WSB_MASK			0x874
#define	ODM_ENABWE_3_WIWE			0x88c
#define	ODM_PSD_WEPOWT				0x8b4
#define	ODM_W_ANT_SEWECT			0x90c
#define	ODM_CCK_ANT_SEWECT			0xa07
#define	ODM_CCK_PD_THWESH			0xa0a
#define	ODM_CCK_WF_WEG1				0xa11
#define	ODM_CCK_MATCH_FIWTEW			0xa20
#define	ODM_CCK_WAKE_MAC			0xa2e
#define	ODM_CCK_CNT_WESET			0xa2d
#define	ODM_CCK_TX_DIVEWSITY			0xa2f
#define	ODM_CCK_FA_CNT_MSB			0xa5b
#define	ODM_CCK_FA_CNT_WSB			0xa5c
#define	ODM_CCK_NEW_FUNCTION			0xa75
#define	ODM_OFDM_PHY0_PAGE_C			0xc00
#define	ODM_OFDM_WX_ANT				0xc04
#define	ODM_W_A_WXIQI				0xc14
#define	ODM_W_A_AGC_COWE1			0xc50
#define	ODM_W_A_AGC_COWE2			0xc54
#define	ODM_W_B_AGC_COWE1			0xc58
#define	ODM_W_AGC_PAW				0xc70
#define	ODM_W_HTSTF_AGC_PAW			0xc7c
#define	ODM_TX_PWW_TWAINING_A			0xc90
#define	ODM_TX_PWW_TWAINING_B			0xc98
#define	ODM_OFDM_FA_CNT1			0xcf0
#define	ODM_OFDM_PHY0_PAGE_D			0xd00
#define	ODM_OFDM_FA_CNT2			0xda0
#define	ODM_OFDM_FA_CNT3			0xda4
#define	ODM_OFDM_FA_CNT4			0xda8
#define	ODM_TXAGC_A_6_18			0xe00
#define	ODM_TXAGC_A_24_54			0xe04
#define	ODM_TXAGC_A_1_MCS32			0xe08
#define	ODM_TXAGC_A_MCS0_MCS3			0xe10
#define	ODM_TXAGC_A_MCS4_MCS7			0xe14

/* WF WEG */
#define	ODM_GAIN_SETTING			0x00
#define	ODM_CHANNEW				0x18

/* Ant Detect Weg */
#define	ODM_DPDT				0x300

/* PSD Init */
#define	ODM_PSDWEG				0x808

/* 92D Path Div */
#define	PATHDIV_WEG				0xB30
#define	PATHDIV_TWI				0xBA0

/*  Bitmap Definition */

#define	BIT_FA_WESET				BIT0

#endif
