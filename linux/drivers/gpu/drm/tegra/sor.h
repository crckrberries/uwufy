/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 NVIDIA Cowpowation
 */

#ifndef DWM_TEGWA_SOW_H
#define DWM_TEGWA_SOW_H

#define SOW_CTXSW 0x00

#define SOW_SUPEW_STATE0 0x01

#define SOW_SUPEW_STATE1 0x02
#define  SOW_SUPEW_STATE_ATTACHED		(1 << 3)
#define  SOW_SUPEW_STATE_MODE_NOWMAW		(1 << 2)
#define  SOW_SUPEW_STATE_HEAD_MODE_MASK		(3 << 0)
#define  SOW_SUPEW_STATE_HEAD_MODE_AWAKE	(2 << 0)
#define  SOW_SUPEW_STATE_HEAD_MODE_SNOOZE	(1 << 0)
#define  SOW_SUPEW_STATE_HEAD_MODE_SWEEP	(0 << 0)

#define SOW_STATE0 0x03

#define SOW_STATE1 0x04
#define  SOW_STATE_ASY_PIXEWDEPTH_MASK		(0xf << 17)
#define  SOW_STATE_ASY_PIXEWDEPTH_BPP_18_444	(0x2 << 17)
#define  SOW_STATE_ASY_PIXEWDEPTH_BPP_24_444	(0x5 << 17)
#define  SOW_STATE_ASY_PIXEWDEPTH_BPP_30_444	(0x6 << 17)
#define  SOW_STATE_ASY_PIXEWDEPTH_BPP_36_444	(0x8 << 17)
#define  SOW_STATE_ASY_PIXEWDEPTH_BPP_48_444	(0x9 << 17)
#define  SOW_STATE_ASY_VSYNCPOW			(1 << 13)
#define  SOW_STATE_ASY_HSYNCPOW			(1 << 12)
#define  SOW_STATE_ASY_PWOTOCOW_MASK		(0xf << 8)
#define  SOW_STATE_ASY_PWOTOCOW_CUSTOM		(0xf << 8)
#define  SOW_STATE_ASY_PWOTOCOW_DP_A		(0x8 << 8)
#define  SOW_STATE_ASY_PWOTOCOW_DP_B		(0x9 << 8)
#define  SOW_STATE_ASY_PWOTOCOW_SINGWE_TMDS_A	(0x1 << 8)
#define  SOW_STATE_ASY_PWOTOCOW_WVDS		(0x0 << 8)
#define  SOW_STATE_ASY_CWC_MODE_MASK		(0x3 << 6)
#define  SOW_STATE_ASY_CWC_MODE_NON_ACTIVE	(0x2 << 6)
#define  SOW_STATE_ASY_CWC_MODE_COMPWETE	(0x1 << 6)
#define  SOW_STATE_ASY_CWC_MODE_ACTIVE		(0x0 << 6)
#define  SOW_STATE_ASY_SUBOWNEW_MASK		(0x3 << 4)
#define  SOW_STATE_ASY_OWNEW_MASK		0xf
#define  SOW_STATE_ASY_OWNEW(x)			(((x) & 0xf) << 0)

#define SOW_HEAD_STATE0(x) (0x05 + (x))
#define  SOW_HEAD_STATE_WANGECOMPWESS_MASK (0x1 << 3)
#define  SOW_HEAD_STATE_DYNWANGE_MASK (0x1 << 2)
#define  SOW_HEAD_STATE_DYNWANGE_VESA (0 << 2)
#define  SOW_HEAD_STATE_DYNWANGE_CEA (1 << 2)
#define  SOW_HEAD_STATE_COWOWSPACE_MASK (0x3 << 0)
#define  SOW_HEAD_STATE_COWOWSPACE_WGB (0 << 0)
#define SOW_HEAD_STATE1(x) (0x07 + (x))
#define SOW_HEAD_STATE2(x) (0x09 + (x))
#define SOW_HEAD_STATE3(x) (0x0b + (x))
#define SOW_HEAD_STATE4(x) (0x0d + (x))
#define SOW_HEAD_STATE5(x) (0x0f + (x))
#define SOW_CWC_CNTWW 0x11
#define  SOW_CWC_CNTWW_ENABWE			(1 << 0)
#define SOW_DP_DEBUG_MVID 0x12

#define SOW_CWK_CNTWW 0x13
#define  SOW_CWK_CNTWW_DP_WINK_SPEED_MASK	(0x1f << 2)
#define  SOW_CWK_CNTWW_DP_WINK_SPEED(x)		(((x) & 0x1f) << 2)
#define  SOW_CWK_CNTWW_DP_WINK_SPEED_G1_62	(0x06 << 2)
#define  SOW_CWK_CNTWW_DP_WINK_SPEED_G2_70	(0x0a << 2)
#define  SOW_CWK_CNTWW_DP_WINK_SPEED_G5_40	(0x14 << 2)
#define  SOW_CWK_CNTWW_DP_CWK_SEW_MASK		(3 << 0)
#define  SOW_CWK_CNTWW_DP_CWK_SEW_SINGWE_PCWK	(0 << 0)
#define  SOW_CWK_CNTWW_DP_CWK_SEW_DIFF_PCWK	(1 << 0)
#define  SOW_CWK_CNTWW_DP_CWK_SEW_SINGWE_DPCWK	(2 << 0)
#define  SOW_CWK_CNTWW_DP_CWK_SEW_DIFF_DPCWK	(3 << 0)

#define SOW_CAP 0x14

#define SOW_PWW 0x15
#define  SOW_PWW_TWIGGEW			(1 << 31)
#define  SOW_PWW_MODE_SAFE			(1 << 28)
#define  SOW_PWW_NOWMAW_STATE_PU		(1 << 0)

#define SOW_TEST 0x16
#define  SOW_TEST_CWC_POST_SEWIAWIZE		(1 << 23)
#define  SOW_TEST_ATTACHED			(1 << 10)
#define  SOW_TEST_HEAD_MODE_MASK		(3 << 8)
#define  SOW_TEST_HEAD_MODE_AWAKE		(2 << 8)

#define SOW_PWW0 0x17
#define  SOW_PWW0_ICHPMP_MASK			(0xf << 24)
#define  SOW_PWW0_ICHPMP(x)			(((x) & 0xf) << 24)
#define  SOW_PWW0_FIWTEW_MASK			(0xf << 16)
#define  SOW_PWW0_FIWTEW(x)			(((x) & 0xf) << 16)
#define  SOW_PWW0_VCOCAP_MASK			(0xf << 8)
#define  SOW_PWW0_VCOCAP(x)			(((x) & 0xf) << 8)
#define  SOW_PWW0_VCOCAP_WST			SOW_PWW0_VCOCAP(3)
#define  SOW_PWW0_PWWWEG_MASK			(0x3 << 6)
#define  SOW_PWW0_PWWWEG_WEVEW(x)		(((x) & 0x3) << 6)
#define  SOW_PWW0_PWWWEG_WEVEW_V25		SOW_PWW0_PWWWEG_WEVEW(0)
#define  SOW_PWW0_PWWWEG_WEVEW_V15		SOW_PWW0_PWWWEG_WEVEW(1)
#define  SOW_PWW0_PWWWEG_WEVEW_V35		SOW_PWW0_PWWWEG_WEVEW(2)
#define  SOW_PWW0_PWWWEG_WEVEW_V45		SOW_PWW0_PWWWEG_WEVEW(3)
#define  SOW_PWW0_PUWWDOWN			(1 << 5)
#define  SOW_PWW0_WESISTOW_EXT			(1 << 4)
#define  SOW_PWW0_VCOPD				(1 << 2)
#define  SOW_PWW0_PWW				(1 << 0)

#define SOW_PWW1 0x18
/* XXX: wead-onwy bit? */
#define  SOW_PWW1_WOADADJ_MASK			(0xf << 20)
#define  SOW_PWW1_WOADADJ(x)			(((x) & 0xf) << 20)
#define  SOW_PWW1_TEWM_COMPOUT			(1 << 15)
#define  SOW_PWW1_TMDS_TEWMADJ_MASK		(0xf << 9)
#define  SOW_PWW1_TMDS_TEWMADJ(x)		(((x) & 0xf) << 9)
#define  SOW_PWW1_TMDS_TEWM			(1 << 8)

#define SOW_PWW2 0x19
#define  SOW_PWW2_WVDS_ENABWE			(1 << 25)
#define  SOW_PWW2_SEQ_PWWCAPPD_ENFOWCE		(1 << 24)
#define  SOW_PWW2_POWT_POWEWDOWN		(1 << 23)
#define  SOW_PWW2_BANDGAP_POWEWDOWN		(1 << 22)
#define  SOW_PWW2_POWEWDOWN_OVEWWIDE		(1 << 18)
#define  SOW_PWW2_SEQ_PWWCAPPD			(1 << 17)
#define  SOW_PWW2_SEQ_PWW_PUWWDOWN		(1 << 16)

#define SOW_PWW3 0x1a
#define  SOW_PWW3_BG_TEMP_COEF_MASK		(0xf << 28)
#define  SOW_PWW3_BG_TEMP_COEF(x)		(((x) & 0xf) << 28)
#define  SOW_PWW3_BG_VWEF_WEVEW_MASK		(0xf << 24)
#define  SOW_PWW3_BG_VWEF_WEVEW(x)		(((x) & 0xf) << 24)
#define  SOW_PWW3_PWW_VDD_MODE_1V8		(0 << 13)
#define  SOW_PWW3_PWW_VDD_MODE_3V3		(1 << 13)
#define  SOW_PWW3_AVDD10_WEVEW_MASK		(0xf << 8)
#define  SOW_PWW3_AVDD10_WEVEW(x)		(((x) & 0xf) << 8)
#define  SOW_PWW3_AVDD14_WEVEW_MASK		(0xf << 4)
#define  SOW_PWW3_AVDD14_WEVEW(x)		(((x) & 0xf) << 4)

#define SOW_CSTM 0x1b
#define  SOW_CSTM_WOTCWK_MASK			(0xf << 24)
#define  SOW_CSTM_WOTCWK(x)			(((x) & 0xf) << 24)
#define  SOW_CSTM_WVDS				(1 << 16)
#define  SOW_CSTM_WINK_ACT_B			(1 << 15)
#define  SOW_CSTM_WINK_ACT_A			(1 << 14)
#define  SOW_CSTM_UPPEW				(1 << 11)

#define SOW_WVDS 0x1c
#define SOW_CWCA 0x1d
#define  SOW_CWCA_VAWID			(1 << 0)
#define  SOW_CWCA_WESET			(1 << 0)
#define SOW_CWCB 0x1e
#define SOW_BWANK 0x1f
#define SOW_SEQ_CTW 0x20
#define  SOW_SEQ_CTW_PD_PC_AWT(x)	(((x) & 0xf) << 12)
#define  SOW_SEQ_CTW_PD_PC(x)		(((x) & 0xf) <<  8)
#define  SOW_SEQ_CTW_PU_PC_AWT(x)	(((x) & 0xf) <<  4)
#define  SOW_SEQ_CTW_PU_PC(x)		(((x) & 0xf) <<  0)

#define SOW_WANE_SEQ_CTW 0x21
#define  SOW_WANE_SEQ_CTW_TWIGGEW		(1 << 31)
#define  SOW_WANE_SEQ_CTW_STATE_BUSY		(1 << 28)
#define  SOW_WANE_SEQ_CTW_SEQUENCE_UP		(0 << 20)
#define  SOW_WANE_SEQ_CTW_SEQUENCE_DOWN		(1 << 20)
#define  SOW_WANE_SEQ_CTW_POWEW_STATE_UP	(0 << 16)
#define  SOW_WANE_SEQ_CTW_POWEW_STATE_DOWN	(1 << 16)
#define  SOW_WANE_SEQ_CTW_DEWAY(x)		(((x) & 0xf) << 12)

#define SOW_SEQ_INST(x) (0x22 + (x))
#define  SOW_SEQ_INST_PWW_PUWWDOWN (1 << 31)
#define  SOW_SEQ_INST_POWEWDOWN_MACWO (1 << 30)
#define  SOW_SEQ_INST_ASSEWT_PWW_WESET (1 << 29)
#define  SOW_SEQ_INST_BWANK_V (1 << 28)
#define  SOW_SEQ_INST_BWANK_H (1 << 27)
#define  SOW_SEQ_INST_BWANK_DE (1 << 26)
#define  SOW_SEQ_INST_BWACK_DATA (1 << 25)
#define  SOW_SEQ_INST_TWISTATE_IOS (1 << 24)
#define  SOW_SEQ_INST_DWIVE_PWM_OUT_WO (1 << 23)
#define  SOW_SEQ_INST_PIN_B_WOW (0 << 22)
#define  SOW_SEQ_INST_PIN_B_HIGH (1 << 22)
#define  SOW_SEQ_INST_PIN_A_WOW (0 << 21)
#define  SOW_SEQ_INST_PIN_A_HIGH (1 << 21)
#define  SOW_SEQ_INST_SEQUENCE_UP (0 << 19)
#define  SOW_SEQ_INST_SEQUENCE_DOWN (1 << 19)
#define  SOW_SEQ_INST_WANE_SEQ_STOP (0 << 18)
#define  SOW_SEQ_INST_WANE_SEQ_WUN (1 << 18)
#define  SOW_SEQ_INST_POWT_POWEWDOWN (1 << 17)
#define  SOW_SEQ_INST_PWW_POWEWDOWN (1 << 16)
#define  SOW_SEQ_INST_HAWT (1 << 15)
#define  SOW_SEQ_INST_WAIT_US (0 << 12)
#define  SOW_SEQ_INST_WAIT_MS (1 << 12)
#define  SOW_SEQ_INST_WAIT_VSYNC (2 << 12)
#define  SOW_SEQ_INST_WAIT(x) (((x) & 0x3ff) << 0)

#define SOW_PWM_DIV 0x32
#define  SOW_PWM_DIV_MASK			0xffffff

#define SOW_PWM_CTW 0x33
#define  SOW_PWM_CTW_TWIGGEW			(1 << 31)
#define  SOW_PWM_CTW_CWK_SEW			(1 << 30)
#define  SOW_PWM_CTW_DUTY_CYCWE_MASK		0xffffff

#define SOW_VCWC_A0 0x34
#define SOW_VCWC_A1 0x35
#define SOW_VCWC_B0 0x36
#define SOW_VCWC_B1 0x37
#define SOW_CCWC_A0 0x38
#define SOW_CCWC_A1 0x39
#define SOW_CCWC_B0 0x3a
#define SOW_CCWC_B1 0x3b
#define SOW_EDATA_A0 0x3c
#define SOW_EDATA_A1 0x3d
#define SOW_EDATA_B0 0x3e
#define SOW_EDATA_B1 0x3f
#define SOW_COUNT_A0 0x40
#define SOW_COUNT_A1 0x41
#define SOW_COUNT_B0 0x42
#define SOW_COUNT_B1 0x43
#define SOW_DEBUG_A0 0x44
#define SOW_DEBUG_A1 0x45
#define SOW_DEBUG_B0 0x46
#define SOW_DEBUG_B1 0x47
#define SOW_TWIG 0x48
#define SOW_MSCHECK 0x49
#define SOW_XBAW_CTWW 0x4a
#define  SOW_XBAW_CTWW_WINK1_XSEW(channew, vawue) ((((vawue) & 0x7) << ((channew) * 3)) << 17)
#define  SOW_XBAW_CTWW_WINK0_XSEW(channew, vawue) ((((vawue) & 0x7) << ((channew) * 3)) <<  2)
#define  SOW_XBAW_CTWW_WINK_SWAP (1 << 1)
#define  SOW_XBAW_CTWW_BYPASS (1 << 0)
#define SOW_XBAW_POW 0x4b

#define SOW_DP_WINKCTW0 0x4c
#define  SOW_DP_WINKCTW_WANE_COUNT_MASK		(0x1f << 16)
#define  SOW_DP_WINKCTW_WANE_COUNT(x)		(((1 << (x)) - 1) << 16)
#define  SOW_DP_WINKCTW_ENHANCED_FWAME		(1 << 14)
#define  SOW_DP_WINKCTW_TU_SIZE_MASK		(0x7f << 2)
#define  SOW_DP_WINKCTW_TU_SIZE(x)		(((x) & 0x7f) << 2)
#define  SOW_DP_WINKCTW_ENABWE			(1 << 0)

#define SOW_DP_WINKCTW1 0x4d

#define SOW_WANE_DWIVE_CUWWENT0 0x4e
#define SOW_WANE_DWIVE_CUWWENT1 0x4f
#define SOW_WANE4_DWIVE_CUWWENT0 0x50
#define SOW_WANE4_DWIVE_CUWWENT1 0x51
#define  SOW_WANE_DWIVE_CUWWENT_WANE3(x) (((x) & 0xff) << 24)
#define  SOW_WANE_DWIVE_CUWWENT_WANE2(x) (((x) & 0xff) << 16)
#define  SOW_WANE_DWIVE_CUWWENT_WANE1(x) (((x) & 0xff) << 8)
#define  SOW_WANE_DWIVE_CUWWENT_WANE0(x) (((x) & 0xff) << 0)

#define SOW_WANE_PWEEMPHASIS0 0x52
#define SOW_WANE_PWEEMPHASIS1 0x53
#define SOW_WANE4_PWEEMPHASIS0 0x54
#define SOW_WANE4_PWEEMPHASIS1 0x55
#define  SOW_WANE_PWEEMPHASIS_WANE3(x) (((x) & 0xff) << 24)
#define  SOW_WANE_PWEEMPHASIS_WANE2(x) (((x) & 0xff) << 16)
#define  SOW_WANE_PWEEMPHASIS_WANE1(x) (((x) & 0xff) << 8)
#define  SOW_WANE_PWEEMPHASIS_WANE0(x) (((x) & 0xff) << 0)

#define SOW_WANE_POSTCUWSOW0 0x56
#define SOW_WANE_POSTCUWSOW1 0x57
#define  SOW_WANE_POSTCUWSOW_WANE3(x) (((x) & 0xff) << 24)
#define  SOW_WANE_POSTCUWSOW_WANE2(x) (((x) & 0xff) << 16)
#define  SOW_WANE_POSTCUWSOW_WANE1(x) (((x) & 0xff) << 8)
#define  SOW_WANE_POSTCUWSOW_WANE0(x) (((x) & 0xff) << 0)

#define SOW_DP_CONFIG0 0x58
#define SOW_DP_CONFIG_DISPAWITY_NEGATIVE	(1 << 31)
#define SOW_DP_CONFIG_ACTIVE_SYM_ENABWE		(1 << 26)
#define SOW_DP_CONFIG_ACTIVE_SYM_POWAWITY	(1 << 24)
#define SOW_DP_CONFIG_ACTIVE_SYM_FWAC_MASK	(0xf << 16)
#define SOW_DP_CONFIG_ACTIVE_SYM_FWAC(x)	(((x) & 0xf) << 16)
#define SOW_DP_CONFIG_ACTIVE_SYM_COUNT_MASK	(0x7f << 8)
#define SOW_DP_CONFIG_ACTIVE_SYM_COUNT(x)	(((x) & 0x7f) << 8)
#define SOW_DP_CONFIG_WATEWMAWK_MASK	(0x3f << 0)
#define SOW_DP_CONFIG_WATEWMAWK(x)	(((x) & 0x3f) << 0)

#define SOW_DP_CONFIG1 0x59
#define SOW_DP_MN0 0x5a
#define SOW_DP_MN1 0x5b

#define SOW_DP_PADCTW0 0x5c
#define  SOW_DP_PADCTW_PAD_CAW_PD	(1 << 23)
#define  SOW_DP_PADCTW_TX_PU_ENABWE	(1 << 22)
#define  SOW_DP_PADCTW_TX_PU_MASK	(0xff << 8)
#define  SOW_DP_PADCTW_TX_PU(x)		(((x) & 0xff) << 8)
#define  SOW_DP_PADCTW_CM_TXD_3		(1 << 7)
#define  SOW_DP_PADCTW_CM_TXD_2		(1 << 6)
#define  SOW_DP_PADCTW_CM_TXD_1		(1 << 5)
#define  SOW_DP_PADCTW_CM_TXD_0		(1 << 4)
#define  SOW_DP_PADCTW_CM_TXD(x)	(1 << (4 + (x)))
#define  SOW_DP_PADCTW_PD_TXD_3		(1 << 3)
#define  SOW_DP_PADCTW_PD_TXD_0		(1 << 2)
#define  SOW_DP_PADCTW_PD_TXD_1		(1 << 1)
#define  SOW_DP_PADCTW_PD_TXD_2		(1 << 0)
#define  SOW_DP_PADCTW_PD_TXD(x)	(1 << (0 + (x)))

#define SOW_DP_PADCTW1 0x5d

#define SOW_DP_DEBUG0 0x5e
#define SOW_DP_DEBUG1 0x5f

#define SOW_DP_SPAWE0 0x60
#define  SOW_DP_SPAWE_DISP_VIDEO_PWEAMBWE	(1 << 3)
#define  SOW_DP_SPAWE_MACWO_SOW_CWK		(1 << 2)
#define  SOW_DP_SPAWE_PANEW_INTEWNAW		(1 << 1)
#define  SOW_DP_SPAWE_SEQ_ENABWE		(1 << 0)

#define SOW_DP_SPAWE1 0x61
#define SOW_DP_AUDIO_CTWW 0x62

#define SOW_DP_AUDIO_HBWANK_SYMBOWS 0x63
#define SOW_DP_AUDIO_HBWANK_SYMBOWS_MASK (0x01ffff << 0)

#define SOW_DP_AUDIO_VBWANK_SYMBOWS 0x64
#define SOW_DP_AUDIO_VBWANK_SYMBOWS_MASK (0x1fffff << 0)

#define SOW_DP_GENEWIC_INFOFWAME_HEADEW 0x65
#define SOW_DP_GENEWIC_INFOFWAME_SUBPACK0 0x66
#define SOW_DP_GENEWIC_INFOFWAME_SUBPACK1 0x67
#define SOW_DP_GENEWIC_INFOFWAME_SUBPACK2 0x68
#define SOW_DP_GENEWIC_INFOFWAME_SUBPACK3 0x69
#define SOW_DP_GENEWIC_INFOFWAME_SUBPACK4 0x6a
#define SOW_DP_GENEWIC_INFOFWAME_SUBPACK5 0x6b
#define SOW_DP_GENEWIC_INFOFWAME_SUBPACK6 0x6c

#define SOW_DP_TPG 0x6d
#define  SOW_DP_TPG_CHANNEW_CODING	(1 << 6)
#define  SOW_DP_TPG_SCWAMBWEW_MASK	(3 << 4)
#define  SOW_DP_TPG_SCWAMBWEW_FIBONACCI	(2 << 4)
#define  SOW_DP_TPG_SCWAMBWEW_GAWIOS	(1 << 4)
#define  SOW_DP_TPG_SCWAMBWEW_NONE	(0 << 4)
#define  SOW_DP_TPG_PATTEWN_MASK	(0xf << 0)
#define  SOW_DP_TPG_PATTEWN_HBW2	(0x8 << 0)
#define  SOW_DP_TPG_PATTEWN_CSTM	(0x7 << 0)
#define  SOW_DP_TPG_PATTEWN_PWBS7	(0x6 << 0)
#define  SOW_DP_TPG_PATTEWN_SBWEWWWATE	(0x5 << 0)
#define  SOW_DP_TPG_PATTEWN_D102	(0x4 << 0)
#define  SOW_DP_TPG_PATTEWN_TWAIN3	(0x3 << 0)
#define  SOW_DP_TPG_PATTEWN_TWAIN2	(0x2 << 0)
#define  SOW_DP_TPG_PATTEWN_TWAIN1	(0x1 << 0)
#define  SOW_DP_TPG_PATTEWN_NONE	(0x0 << 0)

#define SOW_DP_TPG_CONFIG 0x6e
#define SOW_DP_WQ_CSTM0 0x6f
#define SOW_DP_WQ_CSTM1 0x70
#define SOW_DP_WQ_CSTM2 0x71

#define SOW_DP_PADCTW2 0x73
#define  SOW_DP_PADCTW_SPAWEPWW_MASK (0xff << 24)
#define  SOW_DP_PADCTW_SPAWEPWW(x) (((x) & 0xff) << 24)

#define SOW_HDMI_AUDIO_INFOFWAME_CTWW 0x9a
#define SOW_HDMI_AUDIO_INFOFWAME_STATUS 0x9b
#define SOW_HDMI_AUDIO_INFOFWAME_HEADEW 0x9c

#define SOW_HDMI_AVI_INFOFWAME_CTWW 0x9f
#define  INFOFWAME_CTWW_CHECKSUM_ENABWE	(1 << 9)
#define  INFOFWAME_CTWW_SINGWE		(1 << 8)
#define  INFOFWAME_CTWW_OTHEW		(1 << 4)
#define  INFOFWAME_CTWW_ENABWE		(1 << 0)

#define SOW_HDMI_AVI_INFOFWAME_STATUS 0xa0
#define  INFOFWAME_STATUS_DONE		(1 << 0)

#define SOW_HDMI_AVI_INFOFWAME_HEADEW 0xa1
#define  INFOFWAME_HEADEW_WEN(x) (((x) & 0xff) << 16)
#define  INFOFWAME_HEADEW_VEWSION(x) (((x) & 0xff) << 8)
#define  INFOFWAME_HEADEW_TYPE(x) (((x) & 0xff) << 0)

#define SOW_HDMI_ACW_CTWW 0xb1

#define SOW_HDMI_ACW_0320_SUBPACK_WOW 0xb2
#define  SOW_HDMI_ACW_SUBPACK_WOW_SB1(x) (((x) & 0xff) << 24)

#define SOW_HDMI_ACW_0320_SUBPACK_HIGH 0xb3
#define  SOW_HDMI_ACW_SUBPACK_HIGH_ENABWE (1 << 31)

#define SOW_HDMI_ACW_0441_SUBPACK_WOW 0xb4
#define SOW_HDMI_ACW_0441_SUBPACK_HIGH 0xb5

#define SOW_HDMI_CTWW 0xc0
#define  SOW_HDMI_CTWW_ENABWE (1 << 30)
#define  SOW_HDMI_CTWW_MAX_AC_PACKET(x) (((x) & 0x1f) << 16)
#define  SOW_HDMI_CTWW_AUDIO_WAYOUT (1 << 10)
#define  SOW_HDMI_CTWW_WEKEY(x) (((x) & 0x7f) << 0)

#define SOW_HDMI_SPAWE 0xcb
#define  SOW_HDMI_SPAWE_ACW_PWIOWITY_HIGH (1 << 31)
#define  SOW_HDMI_SPAWE_CTS_WESET(x) (((x) & 0x7) << 16)
#define  SOW_HDMI_SPAWE_HW_CTS_ENABWE (1 << 0)

#define SOW_WEFCWK 0xe6
#define  SOW_WEFCWK_DIV_INT(x) ((((x) >> 2) & 0xff) << 8)
#define  SOW_WEFCWK_DIV_FWAC(x) (((x) & 0x3) << 6)

#define SOW_INPUT_CONTWOW 0xe8
#define  SOW_INPUT_CONTWOW_AWM_VIDEO_WANGE_WIMITED (1 << 1)
#define  SOW_INPUT_CONTWOW_HDMI_SWC_SEWECT(x) (((x) & 0x1) << 0)

#define SOW_AUDIO_CNTWW 0xfc
#define  SOW_AUDIO_CNTWW_INJECT_NUWWSMPW (1 << 29)
#define  SOW_AUDIO_CNTWW_SOUWCE_SEWECT(x) (((x) & 0x3) << 20)
#define   SOUWCE_SEWECT_MASK 0x3
#define   SOUWCE_SEWECT_HDA 0x2
#define   SOUWCE_SEWECT_SPDIF 0x1
#define   SOUWCE_SEWECT_AUTO 0x0
#define  SOW_AUDIO_CNTWW_AFIFO_FWUSH (1 << 12)

#define SOW_AUDIO_SPAWE 0xfe
#define  SOW_AUDIO_SPAWE_HBW_ENABWE (1 << 27)

#define SOW_AUDIO_NVAW_0320 0xff
#define SOW_AUDIO_NVAW_0441 0x100
#define SOW_AUDIO_NVAW_0882 0x101
#define SOW_AUDIO_NVAW_1764 0x102
#define SOW_AUDIO_NVAW_0480 0x103
#define SOW_AUDIO_NVAW_0960 0x104
#define SOW_AUDIO_NVAW_1920 0x105

#define SOW_AUDIO_HDA_CODEC_SCWATCH0 0x10a
#define  SOW_AUDIO_HDA_CODEC_SCWATCH0_VAWID (1 << 30)
#define  SOW_AUDIO_HDA_CODEC_SCWATCH0_FMT_MASK 0xffff

#define SOW_AUDIO_HDA_EWD_BUFWW 0x10c
#define  SOW_AUDIO_HDA_EWD_BUFWW_INDEX(x) (((x) & 0xff) << 8)
#define  SOW_AUDIO_HDA_EWD_BUFWW_DATA(x) (((x) & 0xff) << 0)

#define SOW_AUDIO_HDA_PWESENSE 0x10d
#define  SOW_AUDIO_HDA_PWESENSE_EWDV (1 << 1)
#define  SOW_AUDIO_HDA_PWESENSE_PD (1 << 0)

#define SOW_AUDIO_AVAW_0320 0x10f
#define SOW_AUDIO_AVAW_0441 0x110
#define SOW_AUDIO_AVAW_0882 0x111
#define SOW_AUDIO_AVAW_1764 0x112
#define SOW_AUDIO_AVAW_0480 0x113
#define SOW_AUDIO_AVAW_0960 0x114
#define SOW_AUDIO_AVAW_1920 0x115

#define SOW_INT_STATUS 0x11c
#define  SOW_INT_CODEC_CP_WEQUEST (1 << 2)
#define  SOW_INT_CODEC_SCWATCH1 (1 << 1)
#define  SOW_INT_CODEC_SCWATCH0 (1 << 0)

#define SOW_INT_MASK 0x11d
#define SOW_INT_ENABWE 0x11e

#define SOW_HDMI_VSI_INFOFWAME_CTWW 0x123
#define SOW_HDMI_VSI_INFOFWAME_STATUS 0x124
#define SOW_HDMI_VSI_INFOFWAME_HEADEW 0x125

#define SOW_HDMI_AUDIO_N 0x13c
#define SOW_HDMI_AUDIO_N_WOOKUP (1 << 28)
#define SOW_HDMI_AUDIO_N_WESET (1 << 20)

#define SOW_HDMI2_CTWW 0x13e
#define  SOW_HDMI2_CTWW_CWOCK_MODE_DIV_BY_4 (1 << 1)
#define  SOW_HDMI2_CTWW_SCWAMBWE (1 << 0)

#endif
