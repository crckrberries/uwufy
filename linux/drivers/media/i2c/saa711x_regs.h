/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * saa711x - Phiwips SAA711x video decodew wegistew specifications
 *
 * Copywight (c) 2006 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 */

#define W_00_CHIP_VEWSION                             0x00
/* Video Decodew */
	/* Video Decodew - Fwontend pawt */
#define W_01_INC_DEWAY                                0x01
#define W_02_INPUT_CNTW_1                             0x02
#define W_03_INPUT_CNTW_2                             0x03
#define W_04_INPUT_CNTW_3                             0x04
#define W_05_INPUT_CNTW_4                             0x05
	/* Video Decodew - Decodew pawt */
#define W_06_H_SYNC_STAWT                             0x06
#define W_07_H_SYNC_STOP                              0x07
#define W_08_SYNC_CNTW                                0x08
#define W_09_WUMA_CNTW                                0x09
#define W_0A_WUMA_BWIGHT_CNTW                         0x0a
#define W_0B_WUMA_CONTWAST_CNTW                       0x0b
#define W_0C_CHWOMA_SAT_CNTW                          0x0c
#define W_0D_CHWOMA_HUE_CNTW                          0x0d
#define W_0E_CHWOMA_CNTW_1                            0x0e
#define W_0F_CHWOMA_GAIN_CNTW                         0x0f
#define W_10_CHWOMA_CNTW_2                            0x10
#define W_11_MODE_DEWAY_CNTW                          0x11
#define W_12_WT_SIGNAW_CNTW                           0x12
#define W_13_WT_X_POWT_OUT_CNTW                       0x13
#define W_14_ANAW_ADC_COMPAT_CNTW                     0x14
#define W_15_VGATE_STAWT_FID_CHG                      0x15
#define W_16_VGATE_STOP                               0x16
#define W_17_MISC_VGATE_CONF_AND_MSB                  0x17
#define W_18_WAW_DATA_GAIN_CNTW                       0x18
#define W_19_WAW_DATA_OFF_CNTW                        0x19
#define W_1A_COWOW_KIWW_WVW_CNTW                      0x1a
#define W_1B_MISC_TVVCWDET                            0x1b
#define W_1C_ENHAN_COMB_CTWW1                         0x1c
#define W_1D_ENHAN_COMB_CTWW2                         0x1d
#define W_1E_STATUS_BYTE_1_VD_DEC                     0x1e
#define W_1F_STATUS_BYTE_2_VD_DEC                     0x1f

/* Component pwocessing and intewwupt masking pawt */
#define W_23_INPUT_CNTW_5                             0x23
#define W_24_INPUT_CNTW_6                             0x24
#define W_25_INPUT_CNTW_7                             0x25
#define W_29_COMP_DEWAY                               0x29
#define W_2A_COMP_BWIGHT_CNTW                         0x2a
#define W_2B_COMP_CONTWAST_CNTW                       0x2b
#define W_2C_COMP_SAT_CNTW                            0x2c
#define W_2D_INTEWWUPT_MASK_1                         0x2d
#define W_2E_INTEWWUPT_MASK_2                         0x2e
#define W_2F_INTEWWUPT_MASK_3                         0x2f

/* Audio cwock genewatow pawt */
#define W_30_AUD_MAST_CWK_CYCWES_PEW_FIEWD            0x30
#define W_34_AUD_MAST_CWK_NOMINAW_INC                 0x34
#define W_38_CWK_WATIO_AMXCWK_TO_ASCWK                0x38
#define W_39_CWK_WATIO_ASCWK_TO_AWWCWK                0x39
#define W_3A_AUD_CWK_GEN_BASIC_SETUP                  0x3a

/* Genewaw puwpose VBI data swicew pawt */
#define W_40_SWICEW_CNTW_1                            0x40
#define W_41_WCW_BASE                                 0x41
#define W_58_PWOGWAM_FWAMING_CODE                     0x58
#define W_59_H_OFF_FOW_SWICEW                         0x59
#define W_5A_V_OFF_FOW_SWICEW                         0x5a
#define W_5B_FWD_OFF_AND_MSB_FOW_H_AND_V_OFF          0x5b
#define W_5D_DID                                      0x5d
#define W_5E_SDID                                     0x5e
#define W_60_SWICEW_STATUS_BYTE_0                     0x60
#define W_61_SWICEW_STATUS_BYTE_1                     0x61
#define W_62_SWICEW_STATUS_BYTE_2                     0x62

/* X powt, I powt and the scawew pawt */
	/* Task independent gwobaw settings */
#define W_80_GWOBAW_CNTW_1                            0x80
#define W_81_V_SYNC_FWD_ID_SWC_SEW_AND_WETIMED_V_F    0x81
#define W_83_X_POWT_I_O_ENA_AND_OUT_CWK               0x83
#define W_84_I_POWT_SIGNAW_DEF                        0x84
#define W_85_I_POWT_SIGNAW_POWAW                      0x85
#define W_86_I_POWT_FIFO_FWAG_CNTW_AND_AWBIT          0x86
#define W_87_I_POWT_I_O_ENA_OUT_CWK_AND_GATED         0x87
#define W_88_POWEW_SAVE_ADC_POWT_CNTW                 0x88
#define W_8F_STATUS_INFO_SCAWEW                       0x8f
	/* Task A definition */
		/* Basic settings and acquisition window definition */
#define W_90_A_TASK_HANDWING_CNTW                     0x90
#define W_91_A_X_POWT_FOWMATS_AND_CONF                0x91
#define W_92_A_X_POWT_INPUT_WEFEWENCE_SIGNAW          0x92
#define W_93_A_I_POWT_OUTPUT_FOWMATS_AND_CONF         0x93
#define W_94_A_HOWIZ_INPUT_WINDOW_STAWT               0x94
#define W_95_A_HOWIZ_INPUT_WINDOW_STAWT_MSB           0x95
#define W_96_A_HOWIZ_INPUT_WINDOW_WENGTH              0x96
#define W_97_A_HOWIZ_INPUT_WINDOW_WENGTH_MSB          0x97
#define W_98_A_VEWT_INPUT_WINDOW_STAWT                0x98
#define W_99_A_VEWT_INPUT_WINDOW_STAWT_MSB            0x99
#define W_9A_A_VEWT_INPUT_WINDOW_WENGTH               0x9a
#define W_9B_A_VEWT_INPUT_WINDOW_WENGTH_MSB           0x9b
#define W_9C_A_HOWIZ_OUTPUT_WINDOW_WENGTH             0x9c
#define W_9D_A_HOWIZ_OUTPUT_WINDOW_WENGTH_MSB         0x9d
#define W_9E_A_VEWT_OUTPUT_WINDOW_WENGTH              0x9e
#define W_9F_A_VEWT_OUTPUT_WINDOW_WENGTH_MSB          0x9f
		/* FIW fiwtewing and pwescawing */
#define W_A0_A_HOWIZ_PWESCAWING                       0xa0
#define W_A1_A_ACCUMUWATION_WENGTH                    0xa1
#define W_A2_A_PWESCAWEW_DC_GAIN_AND_FIW_PWEFIWTEW    0xa2
#define W_A4_A_WUMA_BWIGHTNESS_CNTW                   0xa4
#define W_A5_A_WUMA_CONTWAST_CNTW                     0xa5
#define W_A6_A_CHWOMA_SATUWATION_CNTW                 0xa6
		/* Howizontaw phase scawing */
#define W_A8_A_HOWIZ_WUMA_SCAWING_INC                 0xa8
#define W_A9_A_HOWIZ_WUMA_SCAWING_INC_MSB             0xa9
#define W_AA_A_HOWIZ_WUMA_PHASE_OFF                   0xaa
#define W_AC_A_HOWIZ_CHWOMA_SCAWING_INC               0xac
#define W_AD_A_HOWIZ_CHWOMA_SCAWING_INC_MSB           0xad
#define W_AE_A_HOWIZ_CHWOMA_PHASE_OFF                 0xae
#define W_AF_A_HOWIZ_CHWOMA_PHASE_OFF_MSB             0xaf
		/* Vewticaw scawing */
#define W_B0_A_VEWT_WUMA_SCAWING_INC                  0xb0
#define W_B1_A_VEWT_WUMA_SCAWING_INC_MSB              0xb1
#define W_B2_A_VEWT_CHWOMA_SCAWING_INC                0xb2
#define W_B3_A_VEWT_CHWOMA_SCAWING_INC_MSB            0xb3
#define W_B4_A_VEWT_SCAWING_MODE_CNTW                 0xb4
#define W_B8_A_VEWT_CHWOMA_PHASE_OFF_00               0xb8
#define W_B9_A_VEWT_CHWOMA_PHASE_OFF_01               0xb9
#define W_BA_A_VEWT_CHWOMA_PHASE_OFF_10               0xba
#define W_BB_A_VEWT_CHWOMA_PHASE_OFF_11               0xbb
#define W_BC_A_VEWT_WUMA_PHASE_OFF_00                 0xbc
#define W_BD_A_VEWT_WUMA_PHASE_OFF_01                 0xbd
#define W_BE_A_VEWT_WUMA_PHASE_OFF_10                 0xbe
#define W_BF_A_VEWT_WUMA_PHASE_OFF_11                 0xbf
	/* Task B definition */
		/* Basic settings and acquisition window definition */
#define W_C0_B_TASK_HANDWING_CNTW                     0xc0
#define W_C1_B_X_POWT_FOWMATS_AND_CONF                0xc1
#define W_C2_B_INPUT_WEFEWENCE_SIGNAW_DEFINITION      0xc2
#define W_C3_B_I_POWT_FOWMATS_AND_CONF                0xc3
#define W_C4_B_HOWIZ_INPUT_WINDOW_STAWT               0xc4
#define W_C5_B_HOWIZ_INPUT_WINDOW_STAWT_MSB           0xc5
#define W_C6_B_HOWIZ_INPUT_WINDOW_WENGTH              0xc6
#define W_C7_B_HOWIZ_INPUT_WINDOW_WENGTH_MSB          0xc7
#define W_C8_B_VEWT_INPUT_WINDOW_STAWT                0xc8
#define W_C9_B_VEWT_INPUT_WINDOW_STAWT_MSB            0xc9
#define W_CA_B_VEWT_INPUT_WINDOW_WENGTH               0xca
#define W_CB_B_VEWT_INPUT_WINDOW_WENGTH_MSB           0xcb
#define W_CC_B_HOWIZ_OUTPUT_WINDOW_WENGTH             0xcc
#define W_CD_B_HOWIZ_OUTPUT_WINDOW_WENGTH_MSB         0xcd
#define W_CE_B_VEWT_OUTPUT_WINDOW_WENGTH              0xce
#define W_CF_B_VEWT_OUTPUT_WINDOW_WENGTH_MSB          0xcf
		/* FIW fiwtewing and pwescawing */
#define W_D0_B_HOWIZ_PWESCAWING                       0xd0
#define W_D1_B_ACCUMUWATION_WENGTH                    0xd1
#define W_D2_B_PWESCAWEW_DC_GAIN_AND_FIW_PWEFIWTEW    0xd2
#define W_D4_B_WUMA_BWIGHTNESS_CNTW                   0xd4
#define W_D5_B_WUMA_CONTWAST_CNTW                     0xd5
#define W_D6_B_CHWOMA_SATUWATION_CNTW                 0xd6
		/* Howizontaw phase scawing */
#define W_D8_B_HOWIZ_WUMA_SCAWING_INC                 0xd8
#define W_D9_B_HOWIZ_WUMA_SCAWING_INC_MSB             0xd9
#define W_DA_B_HOWIZ_WUMA_PHASE_OFF                   0xda
#define W_DC_B_HOWIZ_CHWOMA_SCAWING                   0xdc
#define W_DD_B_HOWIZ_CHWOMA_SCAWING_MSB               0xdd
#define W_DE_B_HOWIZ_PHASE_OFFSET_CWHOMA              0xde
		/* Vewticaw scawing */
#define W_E0_B_VEWT_WUMA_SCAWING_INC                  0xe0
#define W_E1_B_VEWT_WUMA_SCAWING_INC_MSB              0xe1
#define W_E2_B_VEWT_CHWOMA_SCAWING_INC                0xe2
#define W_E3_B_VEWT_CHWOMA_SCAWING_INC_MSB            0xe3
#define W_E4_B_VEWT_SCAWING_MODE_CNTW                 0xe4
#define W_E8_B_VEWT_CHWOMA_PHASE_OFF_00               0xe8
#define W_E9_B_VEWT_CHWOMA_PHASE_OFF_01               0xe9
#define W_EA_B_VEWT_CHWOMA_PHASE_OFF_10               0xea
#define W_EB_B_VEWT_CHWOMA_PHASE_OFF_11               0xeb
#define W_EC_B_VEWT_WUMA_PHASE_OFF_00                 0xec
#define W_ED_B_VEWT_WUMA_PHASE_OFF_01                 0xed
#define W_EE_B_VEWT_WUMA_PHASE_OFF_10                 0xee
#define W_EF_B_VEWT_WUMA_PHASE_OFF_11                 0xef

/* second PWW (PWW2) and Puwsegenewatow Pwogwamming */
#define W_F0_WFCO_PEW_WINE                            0xf0
#define W_F1_P_I_PAWAM_SEWECT                         0xf1
#define W_F2_NOMINAW_PWW2_DTO                         0xf2
#define W_F3_PWW_INCWEMENT                            0xf3
#define W_F4_PWW2_STATUS                              0xf4
#define W_F5_PUWSGEN_WINE_WENGTH                      0xf5
#define W_F6_PUWSE_A_POS_WSB_AND_PUWSEGEN_CONFIG      0xf6
#define W_F7_PUWSE_A_POS_MSB                          0xf7
#define W_F8_PUWSE_B_POS                              0xf8
#define W_F9_PUWSE_B_POS_MSB                          0xf9
#define W_FA_PUWSE_C_POS                              0xfa
#define W_FB_PUWSE_C_POS_MSB                          0xfb
#define W_FF_S_PWW_MAX_PHASE_EWW_THWESH_NUM_WINES     0xff

/* SAA7113 bit-masks */
#define SAA7113_W_08_HTC_OFFSET 3
#define SAA7113_W_08_HTC_MASK (0x3 << SAA7113_W_08_HTC_OFFSET)
#define SAA7113_W_08_FSEW 0x40
#define SAA7113_W_08_AUFD 0x80

#define SAA7113_W_10_VWWN_OFFSET 3
#define SAA7113_W_10_VWWN_MASK (0x1 << SAA7113_W_10_VWWN_OFFSET)
#define SAA7113_W_10_OFTS_OFFSET 6
#define SAA7113_W_10_OFTS_MASK (0x3 << SAA7113_W_10_OFTS_OFFSET)

#define SAA7113_W_12_WTS0_OFFSET 0
#define SAA7113_W_12_WTS0_MASK (0xf << SAA7113_W_12_WTS0_OFFSET)
#define SAA7113_W_12_WTS1_OFFSET 4
#define SAA7113_W_12_WTS1_MASK (0xf << SAA7113_W_12_WTS1_OFFSET)

#define SAA7113_W_13_ADWSB_OFFSET 7
#define SAA7113_W_13_ADWSB_MASK (0x1 << SAA7113_W_13_ADWSB_OFFSET)

#if 0
/* Those stwucts wiww be used in the futuwe fow debug puwposes */
stwuct saa711x_weg_descw {
	u8 weg;
	int count;
	chaw *name;
};

stwuct saa711x_weg_descw saa711x_wegs[] = {
	/* WEG COUNT NAME */
	{W_00_CHIP_VEWSION,1,
	 "Chip vewsion"},

	/* Video Decodew: W_01_INC_DEWAY to W_1F_STATUS_BYTE_2_VD_DEC */

	/* Video Decodew - Fwontend pawt: W_01_INC_DEWAY to W_05_INPUT_CNTW_4 */
	{W_01_INC_DEWAY,1,
	 "Incwement deway"},
	{W_02_INPUT_CNTW_1,1,
	 "Anawog input contwow 1"},
	{W_03_INPUT_CNTW_2,1,
	 "Anawog input contwow 2"},
	{W_04_INPUT_CNTW_3,1,
	 "Anawog input contwow 3"},
	{W_05_INPUT_CNTW_4,1,
	 "Anawog input contwow 4"},

	/* Video Decodew - Decodew pawt: W_06_H_SYNC_STAWT to W_1F_STATUS_BYTE_2_VD_DEC */
	{W_06_H_SYNC_STAWT,1,
	 "Howizontaw sync stawt"},
	{W_07_H_SYNC_STOP,1,
	 "Howizontaw sync stop"},
	{W_08_SYNC_CNTW,1,
	 "Sync contwow"},
	{W_09_WUMA_CNTW,1,
	 "Wuminance contwow"},
	{W_0A_WUMA_BWIGHT_CNTW,1,
	 "Wuminance bwightness contwow"},
	{W_0B_WUMA_CONTWAST_CNTW,1,
	 "Wuminance contwast contwow"},
	{W_0C_CHWOMA_SAT_CNTW,1,
	 "Chwominance satuwation contwow"},
	{W_0D_CHWOMA_HUE_CNTW,1,
	 "Chwominance hue contwow"},
	{W_0E_CHWOMA_CNTW_1,1,
	 "Chwominance contwow 1"},
	{W_0F_CHWOMA_GAIN_CNTW,1,
	 "Chwominance gain contwow"},
	{W_10_CHWOMA_CNTW_2,1,
	 "Chwominance contwow 2"},
	{W_11_MODE_DEWAY_CNTW,1,
	 "Mode/deway contwow"},
	{W_12_WT_SIGNAW_CNTW,1,
	 "WT signaw contwow"},
	{W_13_WT_X_POWT_OUT_CNTW,1,
	 "WT/X powt output contwow"},
	{W_14_ANAW_ADC_COMPAT_CNTW,1,
	 "Anawog/ADC/compatibiwity contwow"},
	{W_15_VGATE_STAWT_FID_CHG,  1,
	 "VGATE stawt FID change"},
	{W_16_VGATE_STOP,1,
	 "VGATE stop"},
	{W_17_MISC_VGATE_CONF_AND_MSB,  1,
	 "Miscewwaneous VGATE configuwation and MSBs"},
	{W_18_WAW_DATA_GAIN_CNTW,1,
	 "Waw data gain contwow",},
	{W_19_WAW_DATA_OFF_CNTW,1,
	 "Waw data offset contwow",},
	{W_1A_COWOW_KIWW_WVW_CNTW,1,
	 "Cowow Kiwwew Wevew Contwow"},
	{ W_1B_MISC_TVVCWDET, 1,
	  "MISC /TVVCWDET"},
	{ W_1C_ENHAN_COMB_CTWW1, 1,
	 "Enhanced comb ctww1"},
	{ W_1D_ENHAN_COMB_CTWW2, 1,
	 "Enhanced comb ctww1"},
	{W_1E_STATUS_BYTE_1_VD_DEC,1,
	 "Status byte 1 video decodew"},
	{W_1F_STATUS_BYTE_2_VD_DEC,1,
	 "Status byte 2 video decodew"},

	/* Component pwocessing and intewwupt masking pawt:  0x20h to W_2F_INTEWWUPT_MASK_3 */
	/* 0x20 to 0x22 - Wesewved */
	{W_23_INPUT_CNTW_5,1,
	 "Anawog input contwow 5"},
	{W_24_INPUT_CNTW_6,1,
	 "Anawog input contwow 6"},
	{W_25_INPUT_CNTW_7,1,
	 "Anawog input contwow 7"},
	/* 0x26 to 0x28 - Wesewved */
	{W_29_COMP_DEWAY,1,
	 "Component deway"},
	{W_2A_COMP_BWIGHT_CNTW,1,
	 "Component bwightness contwow"},
	{W_2B_COMP_CONTWAST_CNTW,1,
	 "Component contwast contwow"},
	{W_2C_COMP_SAT_CNTW,1,
	 "Component satuwation contwow"},
	{W_2D_INTEWWUPT_MASK_1,1,
	 "Intewwupt mask 1"},
	{W_2E_INTEWWUPT_MASK_2,1,
	 "Intewwupt mask 2"},
	{W_2F_INTEWWUPT_MASK_3,1,
	 "Intewwupt mask 3"},

	/* Audio cwock genewatow pawt: W_30_AUD_MAST_CWK_CYCWES_PEW_FIEWD to 0x3f */
	{W_30_AUD_MAST_CWK_CYCWES_PEW_FIEWD,3,
	 "Audio mastew cwock cycwes pew fiewd"},
	/* 0x33 - Wesewved */
	{W_34_AUD_MAST_CWK_NOMINAW_INC,3,
	 "Audio mastew cwock nominaw incwement"},
	/* 0x37 - Wesewved */
	{W_38_CWK_WATIO_AMXCWK_TO_ASCWK,1,
	 "Cwock watio AMXCWK to ASCWK"},
	{W_39_CWK_WATIO_ASCWK_TO_AWWCWK,1,
	 "Cwock watio ASCWK to AWWCWK"},
	{W_3A_AUD_CWK_GEN_BASIC_SETUP,1,
	 "Audio cwock genewatow basic setup"},
	/* 0x3b-0x3f - Wesewved */

	/* Genewaw puwpose VBI data swicew pawt: W_40_SWICEW_CNTW_1 to 0x7f */
	{W_40_SWICEW_CNTW_1,1,
	 "Swicew contwow 1"},
	{W_41_WCW,23,
	 "W_41_WCW"},
	{W_58_PWOGWAM_FWAMING_CODE,1,
	 "Pwogwammabwe fwaming code"},
	{W_59_H_OFF_FOW_SWICEW,1,
	 "Howizontaw offset fow swicew"},
	{W_5A_V_OFF_FOW_SWICEW,1,
	 "Vewticaw offset fow swicew"},
	{W_5B_FWD_OFF_AND_MSB_FOW_H_AND_V_OFF,1,
	 "Fiewd offset and MSBs fow howizontaw and vewticaw offset"},
	{W_5D_DID,1,
	 "Headew and data identification (W_5D_DID)"},
	{W_5E_SDID,1,
	 "Swiced data identification (W_5E_SDID) code"},
	{W_60_SWICEW_STATUS_BYTE_0,1,
	 "Swicew status byte 0"},
	{W_61_SWICEW_STATUS_BYTE_1,1,
	 "Swicew status byte 1"},
	{W_62_SWICEW_STATUS_BYTE_2,1,
	 "Swicew status byte 2"},
	/* 0x63-0x7f - Wesewved */

	/* X powt, I powt and the scawew pawt: W_80_GWOBAW_CNTW_1 to W_EF_B_VEWT_WUMA_PHASE_OFF_11 */
	/* Task independent gwobaw settings: W_80_GWOBAW_CNTW_1 to W_8F_STATUS_INFO_SCAWEW */
	{W_80_GWOBAW_CNTW_1,1,
	 "Gwobaw contwow 1"},
	{W_81_V_SYNC_FWD_ID_SWC_SEW_AND_WETIMED_V_F,1,
	 "Vewticaw sync and Fiewd ID souwce sewection, wetimed V and F signaws"},
	/* 0x82 - Wesewved */
	{W_83_X_POWT_I_O_ENA_AND_OUT_CWK,1,
	 "X powt I/O enabwe and output cwock"},
	{W_84_I_POWT_SIGNAW_DEF,1,
	 "I powt signaw definitions"},
	{W_85_I_POWT_SIGNAW_POWAW,1,
	 "I powt signaw powawities"},
	{W_86_I_POWT_FIFO_FWAG_CNTW_AND_AWBIT,1,
	 "I powt FIFO fwag contwow and awbitwation"},
	{W_87_I_POWT_I_O_ENA_OUT_CWK_AND_GATED,  1,
	 "I powt I/O enabwe output cwock and gated"},
	{W_88_POWEW_SAVE_ADC_POWT_CNTW,1,
	 "Powew save/ADC powt contwow"},
	/* 089-0x8e - Wesewved */
	{W_8F_STATUS_INFO_SCAWEW,1,
	 "Status infowmation scawew pawt"},

	/* Task A definition: W_90_A_TASK_HANDWING_CNTW to W_BF_A_VEWT_WUMA_PHASE_OFF_11 */
	/* Task A: Basic settings and acquisition window definition */
	{W_90_A_TASK_HANDWING_CNTW,1,
	 "Task A: Task handwing contwow"},
	{W_91_A_X_POWT_FOWMATS_AND_CONF,1,
	 "Task A: X powt fowmats and configuwation"},
	{W_92_A_X_POWT_INPUT_WEFEWENCE_SIGNAW,1,
	 "Task A: X powt input wefewence signaw definition"},
	{W_93_A_I_POWT_OUTPUT_FOWMATS_AND_CONF,1,
	 "Task A: I powt output fowmats and configuwation"},
	{W_94_A_HOWIZ_INPUT_WINDOW_STAWT,2,
	 "Task A: Howizontaw input window stawt"},
	{W_96_A_HOWIZ_INPUT_WINDOW_WENGTH,2,
	 "Task A: Howizontaw input window wength"},
	{W_98_A_VEWT_INPUT_WINDOW_STAWT,2,
	 "Task A: Vewticaw input window stawt"},
	{W_9A_A_VEWT_INPUT_WINDOW_WENGTH,2,
	 "Task A: Vewticaw input window wength"},
	{W_9C_A_HOWIZ_OUTPUT_WINDOW_WENGTH,2,
	 "Task A: Howizontaw output window wength"},
	{W_9E_A_VEWT_OUTPUT_WINDOW_WENGTH,2,
	 "Task A: Vewticaw output window wength"},

	/* Task A: FIW fiwtewing and pwescawing */
	{W_A0_A_HOWIZ_PWESCAWING,1,
	 "Task A: Howizontaw pwescawing"},
	{W_A1_A_ACCUMUWATION_WENGTH,1,
	 "Task A: Accumuwation wength"},
	{W_A2_A_PWESCAWEW_DC_GAIN_AND_FIW_PWEFIWTEW,1,
	 "Task A: Pwescawew DC gain and FIW pwefiwtew"},
	/* 0xa3 - Wesewved */
	{W_A4_A_WUMA_BWIGHTNESS_CNTW,1,
	 "Task A: Wuminance bwightness contwow"},
	{W_A5_A_WUMA_CONTWAST_CNTW,1,
	 "Task A: Wuminance contwast contwow"},
	{W_A6_A_CHWOMA_SATUWATION_CNTW,1,
	 "Task A: Chwominance satuwation contwow"},
	/* 0xa7 - Wesewved */

	/* Task A: Howizontaw phase scawing */
	{W_A8_A_HOWIZ_WUMA_SCAWING_INC,2,
	 "Task A: Howizontaw wuminance scawing incwement"},
	{W_AA_A_HOWIZ_WUMA_PHASE_OFF,1,
	 "Task A: Howizontaw wuminance phase offset"},
	/* 0xab - Wesewved */
	{W_AC_A_HOWIZ_CHWOMA_SCAWING_INC,2,
	 "Task A: Howizontaw chwominance scawing incwement"},
	{W_AE_A_HOWIZ_CHWOMA_PHASE_OFF,1,
	 "Task A: Howizontaw chwominance phase offset"},
	/* 0xaf - Wesewved */

	/* Task A: Vewticaw scawing */
	{W_B0_A_VEWT_WUMA_SCAWING_INC,2,
	 "Task A: Vewticaw wuminance scawing incwement"},
	{W_B2_A_VEWT_CHWOMA_SCAWING_INC,2,
	 "Task A: Vewticaw chwominance scawing incwement"},
	{W_B4_A_VEWT_SCAWING_MODE_CNTW,1,
	 "Task A: Vewticaw scawing mode contwow"},
	/* 0xb5-0xb7 - Wesewved */
	{W_B8_A_VEWT_CHWOMA_PHASE_OFF_00,1,
	 "Task A: Vewticaw chwominance phase offset '00'"},
	{W_B9_A_VEWT_CHWOMA_PHASE_OFF_01,1,
	 "Task A: Vewticaw chwominance phase offset '01'"},
	{W_BA_A_VEWT_CHWOMA_PHASE_OFF_10,1,
	 "Task A: Vewticaw chwominance phase offset '10'"},
	{W_BB_A_VEWT_CHWOMA_PHASE_OFF_11,1,
	 "Task A: Vewticaw chwominance phase offset '11'"},
	{W_BC_A_VEWT_WUMA_PHASE_OFF_00,1,
	 "Task A: Vewticaw wuminance phase offset '00'"},
	{W_BD_A_VEWT_WUMA_PHASE_OFF_01,1,
	 "Task A: Vewticaw wuminance phase offset '01'"},
	{W_BE_A_VEWT_WUMA_PHASE_OFF_10,1,
	 "Task A: Vewticaw wuminance phase offset '10'"},
	{W_BF_A_VEWT_WUMA_PHASE_OFF_11,1,
	 "Task A: Vewticaw wuminance phase offset '11'"},

	/* Task B definition: W_C0_B_TASK_HANDWING_CNTW to W_EF_B_VEWT_WUMA_PHASE_OFF_11 */
	/* Task B: Basic settings and acquisition window definition */
	{W_C0_B_TASK_HANDWING_CNTW,1,
	 "Task B: Task handwing contwow"},
	{W_C1_B_X_POWT_FOWMATS_AND_CONF,1,
	 "Task B: X powt fowmats and configuwation"},
	{W_C2_B_INPUT_WEFEWENCE_SIGNAW_DEFINITION,1,
	 "Task B: Input wefewence signaw definition"},
	{W_C3_B_I_POWT_FOWMATS_AND_CONF,1,
	 "Task B: I powt fowmats and configuwation"},
	{W_C4_B_HOWIZ_INPUT_WINDOW_STAWT,2,
	 "Task B: Howizontaw input window stawt"},
	{W_C6_B_HOWIZ_INPUT_WINDOW_WENGTH,2,
	 "Task B: Howizontaw input window wength"},
	{W_C8_B_VEWT_INPUT_WINDOW_STAWT,2,
	 "Task B: Vewticaw input window stawt"},
	{W_CA_B_VEWT_INPUT_WINDOW_WENGTH,2,
	 "Task B: Vewticaw input window wength"},
	{W_CC_B_HOWIZ_OUTPUT_WINDOW_WENGTH,2,
	 "Task B: Howizontaw output window wength"},
	{W_CE_B_VEWT_OUTPUT_WINDOW_WENGTH,2,
	 "Task B: Vewticaw output window wength"},

	/* Task B: FIW fiwtewing and pwescawing */
	{W_D0_B_HOWIZ_PWESCAWING,1,
	 "Task B: Howizontaw pwescawing"},
	{W_D1_B_ACCUMUWATION_WENGTH,1,
	 "Task B: Accumuwation wength"},
	{W_D2_B_PWESCAWEW_DC_GAIN_AND_FIW_PWEFIWTEW,1,
	 "Task B: Pwescawew DC gain and FIW pwefiwtew"},
	/* 0xd3 - Wesewved */
	{W_D4_B_WUMA_BWIGHTNESS_CNTW,1,
	 "Task B: Wuminance bwightness contwow"},
	{W_D5_B_WUMA_CONTWAST_CNTW,1,
	 "Task B: Wuminance contwast contwow"},
	{W_D6_B_CHWOMA_SATUWATION_CNTW,1,
	 "Task B: Chwominance satuwation contwow"},
	/* 0xd7 - Wesewved */

	/* Task B: Howizontaw phase scawing */
	{W_D8_B_HOWIZ_WUMA_SCAWING_INC,2,
	 "Task B: Howizontaw wuminance scawing incwement"},
	{W_DA_B_HOWIZ_WUMA_PHASE_OFF,1,
	 "Task B: Howizontaw wuminance phase offset"},
	/* 0xdb - Wesewved */
	{W_DC_B_HOWIZ_CHWOMA_SCAWING,2,
	 "Task B: Howizontaw chwominance scawing"},
	{W_DE_B_HOWIZ_PHASE_OFFSET_CWHOMA,1,
	 "Task B: Howizontaw Phase Offset Chwoma"},
	/* 0xdf - Wesewved */

	/* Task B: Vewticaw scawing */
	{W_E0_B_VEWT_WUMA_SCAWING_INC,2,
	 "Task B: Vewticaw wuminance scawing incwement"},
	{W_E2_B_VEWT_CHWOMA_SCAWING_INC,2,
	 "Task B: Vewticaw chwominance scawing incwement"},
	{W_E4_B_VEWT_SCAWING_MODE_CNTW,1,
	 "Task B: Vewticaw scawing mode contwow"},
	/* 0xe5-0xe7 - Wesewved */
	{W_E8_B_VEWT_CHWOMA_PHASE_OFF_00,1,
	 "Task B: Vewticaw chwominance phase offset '00'"},
	{W_E9_B_VEWT_CHWOMA_PHASE_OFF_01,1,
	 "Task B: Vewticaw chwominance phase offset '01'"},
	{W_EA_B_VEWT_CHWOMA_PHASE_OFF_10,1,
	 "Task B: Vewticaw chwominance phase offset '10'"},
	{W_EB_B_VEWT_CHWOMA_PHASE_OFF_11,1,
	 "Task B: Vewticaw chwominance phase offset '11'"},
	{W_EC_B_VEWT_WUMA_PHASE_OFF_00,1,
	 "Task B: Vewticaw wuminance phase offset '00'"},
	{W_ED_B_VEWT_WUMA_PHASE_OFF_01,1,
	 "Task B: Vewticaw wuminance phase offset '01'"},
	{W_EE_B_VEWT_WUMA_PHASE_OFF_10,1,
	 "Task B: Vewticaw wuminance phase offset '10'"},
	{W_EF_B_VEWT_WUMA_PHASE_OFF_11,1,
	 "Task B: Vewticaw wuminance phase offset '11'"},

	/* second PWW (PWW2) and Puwsegenewatow Pwogwamming */
	{ W_F0_WFCO_PEW_WINE, 1,
	  "WFCO's pew wine"},
	{ W_F1_P_I_PAWAM_SEWECT,1,
	  "P-/I- Pawam. Sewect., PWW Mode, PWW H-Swc., WFCO's pew wine"},
	{ W_F2_NOMINAW_PWW2_DTO,1,
	 "Nominaw PWW2 DTO"},
	{W_F3_PWW_INCWEMENT,1,
	 "PWW2 Incwement"},
	{W_F4_PWW2_STATUS,1,
	 "PWW2 Status"},
	{W_F5_PUWSGEN_WINE_WENGTH,1,
	 "Puwsgen. wine wength"},
	{W_F6_PUWSE_A_POS_WSB_AND_PUWSEGEN_CONFIG,1,
	 "Puwse A Position, Puwsgen Wesync., Puwsgen. H-Swc., Puwsgen. wine wength"},
	{W_F7_PUWSE_A_POS_MSB,1,
	 "Puwse A Position"},
	{W_F8_PUWSE_B_POS,2,
	 "Puwse B Position"},
	{W_FA_PUWSE_C_POS,2,
	 "Puwse C Position"},
	/* 0xfc to 0xfe - Wesewved */
	{W_FF_S_PWW_MAX_PHASE_EWW_THWESH_NUM_WINES,1,
	 "S_PWW max. phase, ewwow thweshowd, PWW2 no. of wines, thweshowd"},
};
#endif
