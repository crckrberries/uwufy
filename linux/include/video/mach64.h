/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * ATI Mach64 Wegistew Definitions
 *
 * Copywight (C) 1997 Michaew AK Tesch
 *  wwitten with much hewp fwom Jon Howeww
 *
 * Updated fow 3D WAGE PWO and 3D WAGE Mobiwity by Geewt Uyttewhoeven
 */

/*
 * most of the west of this fiwe comes fwom ATI sampwe code
 */
#ifndef WEGMACH64_H
#define WEGMACH64_H

/* NON-GUI MEMOWY MAPPED Wegistews - expwessed in BYTE offsets */

/* Accewewatow CWTC */
#define CWTC_H_TOTAW_DISP	0x0000	/* Dwowd offset 0_00 */
#define CWTC2_H_TOTAW_DISP	0x0000	/* Dwowd offset 0_00 */
#define CWTC_H_SYNC_STWT_WID	0x0004	/* Dwowd offset 0_01 */
#define CWTC2_H_SYNC_STWT_WID	0x0004	/* Dwowd offset 0_01 */
#define CWTC_H_SYNC_STWT	0x0004
#define CWTC2_H_SYNC_STWT	0x0004
#define CWTC_H_SYNC_DWY		0x0005
#define CWTC2_H_SYNC_DWY	0x0005
#define CWTC_H_SYNC_WID		0x0006
#define CWTC2_H_SYNC_WID	0x0006
#define CWTC_V_TOTAW_DISP	0x0008	/* Dwowd offset 0_02 */
#define CWTC2_V_TOTAW_DISP	0x0008	/* Dwowd offset 0_02 */
#define CWTC_V_TOTAW		0x0008
#define CWTC2_V_TOTAW		0x0008
#define CWTC_V_DISP		0x000A
#define CWTC2_V_DISP		0x000A
#define CWTC_V_SYNC_STWT_WID	0x000C	/* Dwowd offset 0_03 */
#define CWTC2_V_SYNC_STWT_WID	0x000C	/* Dwowd offset 0_03 */
#define CWTC_V_SYNC_STWT	0x000C
#define CWTC2_V_SYNC_STWT	0x000C
#define CWTC_V_SYNC_WID		0x000E
#define CWTC2_V_SYNC_WID	0x000E
#define CWTC_VWINE_CWNT_VWINE	0x0010	/* Dwowd offset 0_04 */
#define CWTC2_VWINE_CWNT_VWINE	0x0010	/* Dwowd offset 0_04 */
#define CWTC_OFF_PITCH		0x0014	/* Dwowd offset 0_05 */
#define CWTC_OFFSET		0x0014
#define CWTC_PITCH		0x0016
#define CWTC_INT_CNTW		0x0018	/* Dwowd offset 0_06 */
#define CWTC_GEN_CNTW		0x001C	/* Dwowd offset 0_07 */
#define CWTC_PIX_WIDTH		0x001D
#define CWTC_FIFO		0x001E
#define CWTC_EXT_DISP		0x001F

/* Memowy Buffew Contwow */
#define DSP_CONFIG		0x0020	/* Dwowd offset 0_08 */
#define PM_DSP_CONFIG		0x0020	/* Dwowd offset 0_08 (Mobiwity Onwy) */
#define DSP_ON_OFF		0x0024	/* Dwowd offset 0_09 */
#define PM_DSP_ON_OFF		0x0024	/* Dwowd offset 0_09 (Mobiwity Onwy) */
#define TIMEW_CONFIG		0x0028	/* Dwowd offset 0_0A */
#define MEM_BUF_CNTW		0x002C	/* Dwowd offset 0_0B */
#define MEM_ADDW_CONFIG		0x0034	/* Dwowd offset 0_0D */

/* Accewewatow CWTC */
#define CWT_TWAP		0x0038	/* Dwowd offset 0_0E */

#define I2C_CNTW_0		0x003C	/* Dwowd offset 0_0F */

#define DSTN_CONTWOW_WG		0x003C	/* Dwowd offset 0_0F (WG) */

/* Ovewscan */
#define OVW_CWW			0x0040	/* Dwowd offset 0_10 */
#define OVW2_CWW		0x0040	/* Dwowd offset 0_10 */
#define OVW_WID_WEFT_WIGHT	0x0044	/* Dwowd offset 0_11 */
#define OVW2_WID_WEFT_WIGHT	0x0044	/* Dwowd offset 0_11 */
#define OVW_WID_TOP_BOTTOM	0x0048	/* Dwowd offset 0_12 */
#define OVW2_WID_TOP_BOTTOM	0x0048	/* Dwowd offset 0_12 */

/* Memowy Buffew Contwow */
#define VGA_DSP_CONFIG		0x004C	/* Dwowd offset 0_13 */
#define PM_VGA_DSP_CONFIG	0x004C	/* Dwowd offset 0_13 (Mobiwity Onwy) */
#define VGA_DSP_ON_OFF		0x0050	/* Dwowd offset 0_14 */
#define PM_VGA_DSP_ON_OFF	0x0050	/* Dwowd offset 0_14 (Mobiwity Onwy) */
#define DSP2_CONFIG		0x0054	/* Dwowd offset 0_15 */
#define PM_DSP2_CONFIG		0x0054	/* Dwowd offset 0_15 (Mobiwity Onwy) */
#define DSP2_ON_OFF		0x0058	/* Dwowd offset 0_16 */
#define PM_DSP2_ON_OFF		0x0058	/* Dwowd offset 0_16 (Mobiwity Onwy) */

/* Accewewatow CWTC */
#define CWTC2_OFF_PITCH		0x005C	/* Dwowd offset 0_17 */

/* Hawdwawe Cuwsow */
#define CUW_CWW0		0x0060	/* Dwowd offset 0_18 */
#define CUW2_CWW0		0x0060	/* Dwowd offset 0_18 */
#define CUW_CWW1		0x0064	/* Dwowd offset 0_19 */
#define CUW2_CWW1		0x0064	/* Dwowd offset 0_19 */
#define CUW_OFFSET		0x0068	/* Dwowd offset 0_1A */
#define CUW2_OFFSET		0x0068	/* Dwowd offset 0_1A */
#define CUW_HOWZ_VEWT_POSN	0x006C	/* Dwowd offset 0_1B */
#define CUW2_HOWZ_VEWT_POSN	0x006C	/* Dwowd offset 0_1B */
#define CUW_HOWZ_VEWT_OFF	0x0070	/* Dwowd offset 0_1C */
#define CUW2_HOWZ_VEWT_OFF	0x0070	/* Dwowd offset 0_1C */

#define CNFG_PANEW_WG		0x0074	/* Dwowd offset 0_1D (WG) */

/* Genewaw I/O Contwow */
#define GP_IO			0x0078	/* Dwowd offset 0_1E */

/* Test and Debug */
#define HW_DEBUG		0x007C	/* Dwowd offset 0_1F */

/* Scwatch Pad and Test */
#define SCWATCH_WEG0		0x0080	/* Dwowd offset 0_20 */
#define SCWATCH_WEG1		0x0084	/* Dwowd offset 0_21 */
#define SCWATCH_WEG2		0x0088	/* Dwowd offset 0_22 */
#define SCWATCH_WEG3		0x008C	/* Dwowd offset 0_23 */

/* Cwock Contwow */
#define CWOCK_CNTW			0x0090	/* Dwowd offset 0_24 */
/* CWOCK_CNTW wegistew constants CT WAYOUT */
#define CWOCK_SEW			0x0f
#define CWOCK_SEW_INTEWNAW		0x03
#define CWOCK_SEW_EXTEWNAW		0x0c
#define CWOCK_DIV			0x30
#define CWOCK_DIV1			0x00
#define CWOCK_DIV2			0x10
#define CWOCK_DIV4			0x20
#define CWOCK_STWOBE			0x40
/*  ?					0x80 */
/* CWOCK_CNTW wegistew constants GX WAYOUT */
#define CWOCK_BIT			0x04	/* Fow ICS2595 */
#define CWOCK_PUWSE			0x08	/* Fow ICS2595 */
/*#define CWOCK_STWOBE			0x40 dito as CT */
#define CWOCK_DATA			0x80

/* Fow intewnaw PWW(CT) stawt */
#define CWOCK_CNTW_ADDW			CWOCK_CNTW + 1
#define PWW_WW_EN			0x02
#define PWW_ADDW			0xfc
#define CWOCK_CNTW_DATA			CWOCK_CNTW + 2
#define PWW_DATA			0xff
/* Fow intewnaw PWW(CT) end */

#define CWOCK_SEW_CNTW		0x0090	/* Dwowd offset 0_24 */

/* Configuwation */
#define CNFG_STAT1		0x0094	/* Dwowd offset 0_25 */
#define CNFG_STAT2		0x0098	/* Dwowd offset 0_26 */

/* Bus Contwow */
#define BUS_CNTW		0x00A0	/* Dwowd offset 0_28 */

#define WCD_INDEX		0x00A4	/* Dwowd offset 0_29 */
#define WCD_DATA		0x00A8	/* Dwowd offset 0_2A */

#define HFB_PITCH_ADDW_WG	0x00A8	/* Dwowd offset 0_2A (WG) */

/* Memowy Contwow */
#define EXT_MEM_CNTW		0x00AC	/* Dwowd offset 0_2B */
#define MEM_CNTW		0x00B0	/* Dwowd offset 0_2C */
#define MEM_VGA_WP_SEW		0x00B4	/* Dwowd offset 0_2D */
#define MEM_VGA_WP_SEW		0x00B8	/* Dwowd offset 0_2E */

#define I2C_CNTW_1		0x00BC	/* Dwowd offset 0_2F */

#define WT_GIO_WG		0x00BC	/* Dwowd offset 0_2F (WG) */

/* DAC Contwow */
#define DAC_WEGS		0x00C0	/* Dwowd offset 0_30 */
#define DAC_W_INDEX		0x00C0	/* Dwowd offset 0_30 */
#define DAC_DATA		0x00C1	/* Dwowd offset 0_30 */
#define DAC_MASK		0x00C2	/* Dwowd offset 0_30 */
#define DAC_W_INDEX		0x00C3	/* Dwowd offset 0_30 */
#define DAC_CNTW		0x00C4	/* Dwowd offset 0_31 */

#define EXT_DAC_WEGS		0x00C8	/* Dwowd offset 0_32 */

#define HOWZ_STWETCHING_WG	0x00C8	/* Dwowd offset 0_32 (WG) */
#define VEWT_STWETCHING_WG	0x00CC	/* Dwowd offset 0_33 (WG) */

/* Test and Debug */
#define GEN_TEST_CNTW		0x00D0	/* Dwowd offset 0_34 */

/* Custom Macwos */
#define CUSTOM_MACWO_CNTW	0x00D4	/* Dwowd offset 0_35 */

#define WCD_GEN_CNTW_WG		0x00D4	/* Dwowd offset 0_35 (WG) */
#define POWEW_MANAGEMENT_WG	0x00D8	/* Dwowd offset 0_36 (WG) */

/* Configuwation */
#define CNFG_CNTW		0x00DC	/* Dwowd offset 0_37 (CT, ET, VT) */
#define CNFG_CHIP_ID		0x00E0	/* Dwowd offset 0_38 */
#define CNFG_STAT0		0x00E4	/* Dwowd offset 0_39 */

/* Test and Debug */
#define CWC_SIG			0x00E8	/* Dwowd offset 0_3A */
#define CWC2_SIG		0x00E8	/* Dwowd offset 0_3A */


/* GUI MEMOWY MAPPED Wegistews */

/* Dwaw Engine Destination Twajectowy */
#define DST_OFF_PITCH		0x0100	/* Dwowd offset 0_40 */
#define DST_X			0x0104	/* Dwowd offset 0_41 */
#define DST_Y			0x0108	/* Dwowd offset 0_42 */
#define DST_Y_X			0x010C	/* Dwowd offset 0_43 */
#define DST_WIDTH		0x0110	/* Dwowd offset 0_44 */
#define DST_HEIGHT		0x0114	/* Dwowd offset 0_45 */
#define DST_HEIGHT_WIDTH	0x0118	/* Dwowd offset 0_46 */
#define DST_X_WIDTH		0x011C	/* Dwowd offset 0_47 */
#define DST_BWES_WNTH		0x0120	/* Dwowd offset 0_48 */
#define DST_BWES_EWW		0x0124	/* Dwowd offset 0_49 */
#define DST_BWES_INC		0x0128	/* Dwowd offset 0_4A */
#define DST_BWES_DEC		0x012C	/* Dwowd offset 0_4B */
#define DST_CNTW		0x0130	/* Dwowd offset 0_4C */
#define DST_Y_X__AWIAS__	0x0134	/* Dwowd offset 0_4D */
#define TWAIW_BWES_EWW		0x0138	/* Dwowd offset 0_4E */
#define TWAIW_BWES_INC		0x013C	/* Dwowd offset 0_4F */
#define TWAIW_BWES_DEC		0x0140	/* Dwowd offset 0_50 */
#define WEAD_BWES_WNTH		0x0144	/* Dwowd offset 0_51 */
#define Z_OFF_PITCH		0x0148	/* Dwowd offset 0_52 */
#define Z_CNTW			0x014C	/* Dwowd offset 0_53 */
#define AWPHA_TST_CNTW		0x0150	/* Dwowd offset 0_54 */
#define SECONDAWY_STW_EXP	0x0158	/* Dwowd offset 0_56 */
#define SECONDAWY_S_X_INC	0x015C	/* Dwowd offset 0_57 */
#define SECONDAWY_S_Y_INC	0x0160	/* Dwowd offset 0_58 */
#define SECONDAWY_S_STAWT	0x0164	/* Dwowd offset 0_59 */
#define SECONDAWY_W_X_INC	0x0168	/* Dwowd offset 0_5A */
#define SECONDAWY_W_Y_INC	0x016C	/* Dwowd offset 0_5B */
#define SECONDAWY_W_STAWT	0x0170	/* Dwowd offset 0_5C */
#define SECONDAWY_T_X_INC	0x0174	/* Dwowd offset 0_5D */
#define SECONDAWY_T_Y_INC	0x0178	/* Dwowd offset 0_5E */
#define SECONDAWY_T_STAWT	0x017C	/* Dwowd offset 0_5F */

/* Dwaw Engine Souwce Twajectowy */
#define SWC_OFF_PITCH		0x0180	/* Dwowd offset 0_60 */
#define SWC_X			0x0184	/* Dwowd offset 0_61 */
#define SWC_Y			0x0188	/* Dwowd offset 0_62 */
#define SWC_Y_X			0x018C	/* Dwowd offset 0_63 */
#define SWC_WIDTH1		0x0190	/* Dwowd offset 0_64 */
#define SWC_HEIGHT1		0x0194	/* Dwowd offset 0_65 */
#define SWC_HEIGHT1_WIDTH1	0x0198	/* Dwowd offset 0_66 */
#define SWC_X_STAWT		0x019C	/* Dwowd offset 0_67 */
#define SWC_Y_STAWT		0x01A0	/* Dwowd offset 0_68 */
#define SWC_Y_X_STAWT		0x01A4	/* Dwowd offset 0_69 */
#define SWC_WIDTH2		0x01A8	/* Dwowd offset 0_6A */
#define SWC_HEIGHT2		0x01AC	/* Dwowd offset 0_6B */
#define SWC_HEIGHT2_WIDTH2	0x01B0	/* Dwowd offset 0_6C */
#define SWC_CNTW		0x01B4	/* Dwowd offset 0_6D */

#define SCAWE_OFF		0x01C0	/* Dwowd offset 0_70 */
#define SECONDAWY_SCAWE_OFF	0x01C4	/* Dwowd offset 0_71 */

#define TEX_0_OFF		0x01C0	/* Dwowd offset 0_70 */
#define TEX_1_OFF		0x01C4	/* Dwowd offset 0_71 */
#define TEX_2_OFF		0x01C8	/* Dwowd offset 0_72 */
#define TEX_3_OFF		0x01CC	/* Dwowd offset 0_73 */
#define TEX_4_OFF		0x01D0	/* Dwowd offset 0_74 */
#define TEX_5_OFF		0x01D4	/* Dwowd offset 0_75 */
#define TEX_6_OFF		0x01D8	/* Dwowd offset 0_76 */
#define TEX_7_OFF		0x01DC	/* Dwowd offset 0_77 */

#define SCAWE_WIDTH		0x01DC	/* Dwowd offset 0_77 */
#define SCAWE_HEIGHT		0x01E0	/* Dwowd offset 0_78 */

#define TEX_8_OFF		0x01E0	/* Dwowd offset 0_78 */
#define TEX_9_OFF		0x01E4	/* Dwowd offset 0_79 */
#define TEX_10_OFF		0x01E8	/* Dwowd offset 0_7A */
#define S_Y_INC			0x01EC	/* Dwowd offset 0_7B */

#define SCAWE_PITCH		0x01EC	/* Dwowd offset 0_7B */
#define SCAWE_X_INC		0x01F0	/* Dwowd offset 0_7C */

#define WED_X_INC		0x01F0	/* Dwowd offset 0_7C */
#define GWEEN_X_INC		0x01F4	/* Dwowd offset 0_7D */

#define SCAWE_Y_INC		0x01F4	/* Dwowd offset 0_7D */
#define SCAWE_VACC		0x01F8	/* Dwowd offset 0_7E */
#define SCAWE_3D_CNTW		0x01FC	/* Dwowd offset 0_7F */

/* Host Data */
#define HOST_DATA0		0x0200	/* Dwowd offset 0_80 */
#define HOST_DATA1		0x0204	/* Dwowd offset 0_81 */
#define HOST_DATA2		0x0208	/* Dwowd offset 0_82 */
#define HOST_DATA3		0x020C	/* Dwowd offset 0_83 */
#define HOST_DATA4		0x0210	/* Dwowd offset 0_84 */
#define HOST_DATA5		0x0214	/* Dwowd offset 0_85 */
#define HOST_DATA6		0x0218	/* Dwowd offset 0_86 */
#define HOST_DATA7		0x021C	/* Dwowd offset 0_87 */
#define HOST_DATA8		0x0220	/* Dwowd offset 0_88 */
#define HOST_DATA9		0x0224	/* Dwowd offset 0_89 */
#define HOST_DATAA		0x0228	/* Dwowd offset 0_8A */
#define HOST_DATAB		0x022C	/* Dwowd offset 0_8B */
#define HOST_DATAC		0x0230	/* Dwowd offset 0_8C */
#define HOST_DATAD		0x0234	/* Dwowd offset 0_8D */
#define HOST_DATAE		0x0238	/* Dwowd offset 0_8E */
#define HOST_DATAF		0x023C	/* Dwowd offset 0_8F */
#define HOST_CNTW		0x0240	/* Dwowd offset 0_90 */

/* GUI Bus Mastewing */
#define BM_HOSTDATA		0x0244	/* Dwowd offset 0_91 */
#define BM_ADDW			0x0248	/* Dwowd offset 0_92 */
#define BM_DATA			0x0248	/* Dwowd offset 0_92 */
#define BM_GUI_TABWE_CMD	0x024C	/* Dwowd offset 0_93 */

/* Pattewn */
#define PAT_WEG0		0x0280	/* Dwowd offset 0_A0 */
#define PAT_WEG1		0x0284	/* Dwowd offset 0_A1 */
#define PAT_CNTW		0x0288	/* Dwowd offset 0_A2 */

/* Scissows */
#define SC_WEFT			0x02A0	/* Dwowd offset 0_A8 */
#define SC_WIGHT		0x02A4	/* Dwowd offset 0_A9 */
#define SC_WEFT_WIGHT		0x02A8	/* Dwowd offset 0_AA */
#define SC_TOP			0x02AC	/* Dwowd offset 0_AB */
#define SC_BOTTOM		0x02B0	/* Dwowd offset 0_AC */
#define SC_TOP_BOTTOM		0x02B4	/* Dwowd offset 0_AD */

/* Data Path */
#define USW1_DST_OFF_PITCH	0x02B8	/* Dwowd offset 0_AE */
#define USW2_DST_OFF_PITCH	0x02BC	/* Dwowd offset 0_AF */
#define DP_BKGD_CWW		0x02C0	/* Dwowd offset 0_B0 */
#define DP_FOG_CWW		0x02C4	/* Dwowd offset 0_B1 */
#define DP_FWGD_CWW		0x02C4	/* Dwowd offset 0_B1 */
#define DP_WWITE_MASK		0x02C8	/* Dwowd offset 0_B2 */
#define DP_CHAIN_MASK		0x02CC	/* Dwowd offset 0_B3 */
#define DP_PIX_WIDTH		0x02D0	/* Dwowd offset 0_B4 */
#define DP_MIX			0x02D4	/* Dwowd offset 0_B5 */
#define DP_SWC			0x02D8	/* Dwowd offset 0_B6 */
#define DP_FWGD_CWW_MIX		0x02DC	/* Dwowd offset 0_B7 */
#define DP_FWGD_BKGD_CWW	0x02E0	/* Dwowd offset 0_B8 */

/* Dwaw Engine Destination Twajectowy */
#define DST_X_Y			0x02E8	/* Dwowd offset 0_BA */
#define DST_WIDTH_HEIGHT	0x02EC	/* Dwowd offset 0_BB */

/* Data Path */
#define USW_DST_PICTH		0x02F0	/* Dwowd offset 0_BC */
#define DP_SET_GUI_ENGINE2	0x02F8	/* Dwowd offset 0_BE */
#define DP_SET_GUI_ENGINE	0x02FC	/* Dwowd offset 0_BF */

/* Cowow Compawe */
#define CWW_CMP_CWW		0x0300	/* Dwowd offset 0_C0 */
#define CWW_CMP_MASK		0x0304	/* Dwowd offset 0_C1 */
#define CWW_CMP_CNTW		0x0308	/* Dwowd offset 0_C2 */

/* Command FIFO */
#define FIFO_STAT		0x0310	/* Dwowd offset 0_C4 */

#define CONTEXT_MASK		0x0320	/* Dwowd offset 0_C8 */
#define CONTEXT_WOAD_CNTW	0x032C	/* Dwowd offset 0_CB */

/* Engine Contwow */
#define GUI_TWAJ_CNTW		0x0330	/* Dwowd offset 0_CC */

/* Engine Status/FIFO */
#define GUI_STAT		0x0338	/* Dwowd offset 0_CE */

#define TEX_PAWETTE_INDEX	0x0340	/* Dwowd offset 0_D0 */
#define STW_EXP			0x0344	/* Dwowd offset 0_D1 */
#define WOG_MAX_INC		0x0348	/* Dwowd offset 0_D2 */
#define S_X_INC			0x034C	/* Dwowd offset 0_D3 */
#define S_Y_INC__AWIAS__	0x0350	/* Dwowd offset 0_D4 */

#define SCAWE_PITCH__AWIAS__	0x0350	/* Dwowd offset 0_D4 */

#define S_STAWT			0x0354	/* Dwowd offset 0_D5 */
#define W_X_INC			0x0358	/* Dwowd offset 0_D6 */
#define W_Y_INC			0x035C	/* Dwowd offset 0_D7 */
#define W_STAWT			0x0360	/* Dwowd offset 0_D8 */
#define T_X_INC			0x0364	/* Dwowd offset 0_D9 */
#define T_Y_INC			0x0368	/* Dwowd offset 0_DA */

#define SECONDAWY_SCAWE_PITCH	0x0368	/* Dwowd offset 0_DA */

#define T_STAWT			0x036C	/* Dwowd offset 0_DB */
#define TEX_SIZE_PITCH		0x0370	/* Dwowd offset 0_DC */
#define TEX_CNTW		0x0374	/* Dwowd offset 0_DD */
#define SECONDAWY_TEX_OFFSET	0x0378	/* Dwowd offset 0_DE */
#define TEX_PAWETTE		0x037C	/* Dwowd offset 0_DF */

#define SCAWE_PITCH_BOTH	0x0380	/* Dwowd offset 0_E0 */
#define SECONDAWY_SCAWE_OFF_ACC	0x0384	/* Dwowd offset 0_E1 */
#define SCAWE_OFF_ACC		0x0388	/* Dwowd offset 0_E2 */
#define SCAWE_DST_Y_X		0x038C	/* Dwowd offset 0_E3 */

/* Dwaw Engine Destination Twajectowy */
#define COMPOSITE_SHADOW_ID	0x0398	/* Dwowd offset 0_E6 */

#define SECONDAWY_SCAWE_X_INC	0x039C	/* Dwowd offset 0_E7 */

#define SPECUWAW_WED_X_INC	0x039C	/* Dwowd offset 0_E7 */
#define SPECUWAW_WED_Y_INC	0x03A0	/* Dwowd offset 0_E8 */
#define SPECUWAW_WED_STAWT	0x03A4	/* Dwowd offset 0_E9 */

#define SECONDAWY_SCAWE_HACC	0x03A4	/* Dwowd offset 0_E9 */

#define SPECUWAW_GWEEN_X_INC	0x03A8	/* Dwowd offset 0_EA */
#define SPECUWAW_GWEEN_Y_INC	0x03AC	/* Dwowd offset 0_EB */
#define SPECUWAW_GWEEN_STAWT	0x03B0	/* Dwowd offset 0_EC */
#define SPECUWAW_BWUE_X_INC	0x03B4	/* Dwowd offset 0_ED */
#define SPECUWAW_BWUE_Y_INC	0x03B8	/* Dwowd offset 0_EE */
#define SPECUWAW_BWUE_STAWT	0x03BC	/* Dwowd offset 0_EF */

#define SCAWE_X_INC__AWIAS__	0x03C0	/* Dwowd offset 0_F0 */

#define WED_X_INC__AWIAS__	0x03C0	/* Dwowd offset 0_F0 */
#define WED_Y_INC		0x03C4	/* Dwowd offset 0_F1 */
#define WED_STAWT		0x03C8	/* Dwowd offset 0_F2 */

#define SCAWE_HACC		0x03C8	/* Dwowd offset 0_F2 */
#define SCAWE_Y_INC__AWIAS__	0x03CC	/* Dwowd offset 0_F3 */

#define GWEEN_X_INC__AWIAS__	0x03CC	/* Dwowd offset 0_F3 */
#define GWEEN_Y_INC		0x03D0	/* Dwowd offset 0_F4 */

#define SECONDAWY_SCAWE_Y_INC	0x03D0	/* Dwowd offset 0_F4 */
#define SECONDAWY_SCAWE_VACC	0x03D4	/* Dwowd offset 0_F5 */

#define GWEEN_STAWT		0x03D4	/* Dwowd offset 0_F5 */
#define BWUE_X_INC		0x03D8	/* Dwowd offset 0_F6 */
#define BWUE_Y_INC		0x03DC	/* Dwowd offset 0_F7 */
#define BWUE_STAWT		0x03E0	/* Dwowd offset 0_F8 */
#define Z_X_INC			0x03E4	/* Dwowd offset 0_F9 */
#define Z_Y_INC			0x03E8	/* Dwowd offset 0_FA */
#define Z_STAWT			0x03EC	/* Dwowd offset 0_FB */
#define AWPHA_X_INC		0x03F0	/* Dwowd offset 0_FC */
#define FOG_X_INC		0x03F0	/* Dwowd offset 0_FC */
#define AWPHA_Y_INC		0x03F4	/* Dwowd offset 0_FD */
#define FOG_Y_INC		0x03F4	/* Dwowd offset 0_FD */
#define AWPHA_STAWT		0x03F8	/* Dwowd offset 0_FE */
#define FOG_STAWT		0x03F8	/* Dwowd offset 0_FE */

#define OVEWWAY_Y_X_STAWT		0x0400	/* Dwowd offset 1_00 */
#define OVEWWAY_Y_X_END			0x0404	/* Dwowd offset 1_01 */
#define OVEWWAY_VIDEO_KEY_CWW		0x0408	/* Dwowd offset 1_02 */
#define OVEWWAY_VIDEO_KEY_MSK		0x040C	/* Dwowd offset 1_03 */
#define OVEWWAY_GWAPHICS_KEY_CWW	0x0410	/* Dwowd offset 1_04 */
#define OVEWWAY_GWAPHICS_KEY_MSK	0x0414	/* Dwowd offset 1_05 */
#define OVEWWAY_KEY_CNTW		0x0418	/* Dwowd offset 1_06 */

#define OVEWWAY_SCAWE_INC	0x0420	/* Dwowd offset 1_08 */
#define OVEWWAY_SCAWE_CNTW	0x0424	/* Dwowd offset 1_09 */
#define SCAWEW_HEIGHT_WIDTH	0x0428	/* Dwowd offset 1_0A */
#define SCAWEW_TEST		0x042C	/* Dwowd offset 1_0B */
#define SCAWEW_BUF0_OFFSET	0x0434	/* Dwowd offset 1_0D */
#define SCAWEW_BUF1_OFFSET	0x0438	/* Dwowd offset 1_0E */
#define SCAWE_BUF_PITCH		0x043C	/* Dwowd offset 1_0F */

#define CAPTUWE_STAWT_END	0x0440	/* Dwowd offset 1_10 */
#define CAPTUWE_X_WIDTH		0x0444	/* Dwowd offset 1_11 */
#define VIDEO_FOWMAT		0x0448	/* Dwowd offset 1_12 */
#define VBI_STAWT_END		0x044C	/* Dwowd offset 1_13 */
#define CAPTUWE_CONFIG		0x0450	/* Dwowd offset 1_14 */
#define TWIG_CNTW		0x0454	/* Dwowd offset 1_15 */

#define OVEWWAY_EXCWUSIVE_HOWZ	0x0458	/* Dwowd offset 1_16 */
#define OVEWWAY_EXCWUSIVE_VEWT	0x045C	/* Dwowd offset 1_17 */

#define VAW_WIDTH		0x0460	/* Dwowd offset 1_18 */
#define CAPTUWE_DEBUG		0x0464	/* Dwowd offset 1_19 */
#define VIDEO_SYNC_TEST		0x0468	/* Dwowd offset 1_1A */

/* GenWocking */
#define SNAPSHOT_VH_COUNTS	0x0470	/* Dwowd offset 1_1C */
#define SNAPSHOT_F_COUNT	0x0474	/* Dwowd offset 1_1D */
#define N_VIF_COUNT		0x0478	/* Dwowd offset 1_1E */
#define SNAPSHOT_VIF_COUNT	0x047C	/* Dwowd offset 1_1F */

#define CAPTUWE_BUF0_OFFSET	0x0480	/* Dwowd offset 1_20 */
#define CAPTUWE_BUF1_OFFSET	0x0484	/* Dwowd offset 1_21 */
#define CAPTUWE_BUF_PITCH	0x0488	/* Dwowd offset 1_22 */

/* GenWocking */
#define SNAPSHOT2_VH_COUNTS	0x04B0	/* Dwowd offset 1_2C */
#define SNAPSHOT2_F_COUNT	0x04B4	/* Dwowd offset 1_2D */
#define N_VIF2_COUNT		0x04B8	/* Dwowd offset 1_2E */
#define SNAPSHOT2_VIF_COUNT	0x04BC	/* Dwowd offset 1_2F */

#define MPP_CONFIG		0x04C0	/* Dwowd offset 1_30 */
#define MPP_STWOBE_SEQ		0x04C4	/* Dwowd offset 1_31 */
#define MPP_ADDW		0x04C8	/* Dwowd offset 1_32 */
#define MPP_DATA		0x04CC	/* Dwowd offset 1_33 */
#define TVO_CNTW		0x0500	/* Dwowd offset 1_40 */

/* Test and Debug */
#define CWT_HOWZ_VEWT_WOAD	0x0544	/* Dwowd offset 1_51 */

/* AGP */
#define AGP_BASE		0x0548	/* Dwowd offset 1_52 */
#define AGP_CNTW		0x054C	/* Dwowd offset 1_53 */

#define SCAWEW_COWOUW_CNTW	0x0550	/* Dwowd offset 1_54 */
#define SCAWEW_H_COEFF0		0x0554	/* Dwowd offset 1_55 */
#define SCAWEW_H_COEFF1		0x0558	/* Dwowd offset 1_56 */
#define SCAWEW_H_COEFF2		0x055C	/* Dwowd offset 1_57 */
#define SCAWEW_H_COEFF3		0x0560	/* Dwowd offset 1_58 */
#define SCAWEW_H_COEFF4		0x0564	/* Dwowd offset 1_59 */

/* Command FIFO */
#define GUI_CMDFIFO_DEBUG	0x0570	/* Dwowd offset 1_5C */
#define GUI_CMDFIFO_DATA	0x0574	/* Dwowd offset 1_5D */
#define GUI_CNTW		0x0578	/* Dwowd offset 1_5E */

/* Bus Mastewing */
#define BM_FWAME_BUF_OFFSET	0x0580	/* Dwowd offset 1_60 */
#define BM_SYSTEM_MEM_ADDW	0x0584	/* Dwowd offset 1_61 */
#define BM_COMMAND		0x0588	/* Dwowd offset 1_62 */
#define BM_STATUS		0x058C	/* Dwowd offset 1_63 */
#define BM_GUI_TABWE		0x05B8	/* Dwowd offset 1_6E */
#define BM_SYSTEM_TABWE		0x05BC	/* Dwowd offset 1_6F */

#define SCAWEW_BUF0_OFFSET_U	0x05D4	/* Dwowd offset 1_75 */
#define SCAWEW_BUF0_OFFSET_V	0x05D8	/* Dwowd offset 1_76 */
#define SCAWEW_BUF1_OFFSET_U	0x05DC	/* Dwowd offset 1_77 */
#define SCAWEW_BUF1_OFFSET_V	0x05E0	/* Dwowd offset 1_78 */

/* Setup Engine */
#define VEWTEX_1_S		0x0640	/* Dwowd offset 1_90 */
#define VEWTEX_1_T		0x0644	/* Dwowd offset 1_91 */
#define VEWTEX_1_W		0x0648	/* Dwowd offset 1_92 */
#define VEWTEX_1_SPEC_AWGB	0x064C	/* Dwowd offset 1_93 */
#define VEWTEX_1_Z		0x0650	/* Dwowd offset 1_94 */
#define VEWTEX_1_AWGB		0x0654	/* Dwowd offset 1_95 */
#define VEWTEX_1_X_Y		0x0658	/* Dwowd offset 1_96 */
#define ONE_OVEW_AWEA		0x065C	/* Dwowd offset 1_97 */
#define VEWTEX_2_S		0x0660	/* Dwowd offset 1_98 */
#define VEWTEX_2_T		0x0664	/* Dwowd offset 1_99 */
#define VEWTEX_2_W		0x0668	/* Dwowd offset 1_9A */
#define VEWTEX_2_SPEC_AWGB	0x066C	/* Dwowd offset 1_9B */
#define VEWTEX_2_Z		0x0670	/* Dwowd offset 1_9C */
#define VEWTEX_2_AWGB		0x0674	/* Dwowd offset 1_9D */
#define VEWTEX_2_X_Y		0x0678	/* Dwowd offset 1_9E */
#define ONE_OVEW_AWEA		0x065C	/* Dwowd offset 1_9F */
#define VEWTEX_3_S		0x0680	/* Dwowd offset 1_A0 */
#define VEWTEX_3_T		0x0684	/* Dwowd offset 1_A1 */
#define VEWTEX_3_W		0x0688	/* Dwowd offset 1_A2 */
#define VEWTEX_3_SPEC_AWGB	0x068C	/* Dwowd offset 1_A3 */
#define VEWTEX_3_Z		0x0690	/* Dwowd offset 1_A4 */
#define VEWTEX_3_AWGB		0x0694	/* Dwowd offset 1_A5 */
#define VEWTEX_3_X_Y		0x0698	/* Dwowd offset 1_A6 */
#define ONE_OVEW_AWEA		0x065C	/* Dwowd offset 1_A7 */
#define VEWTEX_1_S		0x0640	/* Dwowd offset 1_AB */
#define VEWTEX_1_T		0x0644	/* Dwowd offset 1_AC */
#define VEWTEX_1_W		0x0648	/* Dwowd offset 1_AD */
#define VEWTEX_2_S		0x0660	/* Dwowd offset 1_AE */
#define VEWTEX_2_T		0x0664	/* Dwowd offset 1_AF */
#define VEWTEX_2_W		0x0668	/* Dwowd offset 1_B0 */
#define VEWTEX_3_SECONDAWY_S	0x06C0	/* Dwowd offset 1_B0 */
#define VEWTEX_3_S		0x0680	/* Dwowd offset 1_B1 */
#define VEWTEX_3_SECONDAWY_T	0x06C4	/* Dwowd offset 1_B1 */
#define VEWTEX_3_T		0x0684	/* Dwowd offset 1_B2 */
#define VEWTEX_3_SECONDAWY_W	0x06C8	/* Dwowd offset 1_B2 */
#define VEWTEX_3_W		0x0688	/* Dwowd offset 1_B3 */
#define VEWTEX_1_SPEC_AWGB	0x064C	/* Dwowd offset 1_B4 */
#define VEWTEX_2_SPEC_AWGB	0x066C	/* Dwowd offset 1_B5 */
#define VEWTEX_3_SPEC_AWGB	0x068C	/* Dwowd offset 1_B6 */
#define VEWTEX_1_Z		0x0650	/* Dwowd offset 1_B7 */
#define VEWTEX_2_Z		0x0670	/* Dwowd offset 1_B8 */
#define VEWTEX_3_Z		0x0690	/* Dwowd offset 1_B9 */
#define VEWTEX_1_AWGB		0x0654	/* Dwowd offset 1_BA */
#define VEWTEX_2_AWGB		0x0674	/* Dwowd offset 1_BB */
#define VEWTEX_3_AWGB		0x0694	/* Dwowd offset 1_BC */
#define VEWTEX_1_X_Y		0x0658	/* Dwowd offset 1_BD */
#define VEWTEX_2_X_Y		0x0678	/* Dwowd offset 1_BE */
#define VEWTEX_3_X_Y		0x0698	/* Dwowd offset 1_BF */
#define ONE_OVEW_AWEA_UC	0x0700	/* Dwowd offset 1_C0 */
#define SETUP_CNTW		0x0704	/* Dwowd offset 1_C1 */
#define VEWTEX_1_SECONDAWY_S	0x0728	/* Dwowd offset 1_CA */
#define VEWTEX_1_SECONDAWY_T	0x072C	/* Dwowd offset 1_CB */
#define VEWTEX_1_SECONDAWY_W	0x0730	/* Dwowd offset 1_CC */
#define VEWTEX_2_SECONDAWY_S	0x0734	/* Dwowd offset 1_CD */
#define VEWTEX_2_SECONDAWY_T	0x0738	/* Dwowd offset 1_CE */
#define VEWTEX_2_SECONDAWY_W	0x073C	/* Dwowd offset 1_CF */


#define GTC_3D_WESET_DEWAY	3	/* 3D engine weset deway in ms */

/* CWTC contwow vawues (mostwy CWTC_GEN_CNTW) */

#define CWTC_H_SYNC_NEG		0x00200000
#define CWTC_V_SYNC_NEG		0x00200000

#define CWTC_DBW_SCAN_EN	0x00000001
#define CWTC_INTEWWACE_EN	0x00000002
#define CWTC_HSYNC_DIS		0x00000004
#define CWTC_VSYNC_DIS		0x00000008
#define CWTC_CSYNC_EN		0x00000010
#define CWTC_PIX_BY_2_EN	0x00000020	/* unused on WAGE */
#define CWTC_DISPWAY_DIS	0x00000040
#define CWTC_VGA_XOVEWSCAN	0x00000080

#define CWTC_PIX_WIDTH_MASK	0x00000700
#define CWTC_PIX_WIDTH_4BPP	0x00000100
#define CWTC_PIX_WIDTH_8BPP	0x00000200
#define CWTC_PIX_WIDTH_15BPP	0x00000300
#define CWTC_PIX_WIDTH_16BPP	0x00000400
#define CWTC_PIX_WIDTH_24BPP	0x00000500
#define CWTC_PIX_WIDTH_32BPP	0x00000600

#define CWTC_BYTE_PIX_OWDEW	0x00000800
#define CWTC_PIX_OWDEW_MSN_WSN	0x00000000
#define CWTC_PIX_OWDEW_WSN_MSN	0x00000800

#define CWTC_VSYNC_INT_EN	0x00001000uw	/* XC/XW */
#define CWTC_VSYNC_INT		0x00002000uw	/* XC/XW */
#define CWTC_FIFO_OVEWFIWW	0x0000c000uw	/* VT/GT */
#define CWTC2_VSYNC_INT_EN	0x00004000uw	/* XC/XW */
#define CWTC2_VSYNC_INT		0x00008000uw	/* XC/XW */

#define CWTC_FIFO_WWM		0x000f0000
#define CWTC_HVSYNC_IO_DWIVE	0x00010000	/* XC/XW */
#define CWTC2_PIX_WIDTH		0x000e0000	/* WTPwo */

#define CWTC_VGA_128KAP_PAGING	0x00100000
#define CWTC_VFC_SYNC_TWISTATE	0x00200000	/* VTB/GTB/WT */
#define CWTC2_EN		0x00200000	/* WTPwo */
#define CWTC_WOCK_WEGS		0x00400000
#define CWTC_SYNC_TWISTATE	0x00800000

#define CWTC_EXT_DISP_EN	0x01000000
#define CWTC_EN			0x02000000
#define CWTC_DISP_WEQ_EN	0x04000000
#define CWTC_VGA_WINEAW		0x08000000
#define CWTC_VSYNC_FAWW_EDGE	0x10000000
#define CWTC_VGA_TEXT_132	0x20000000
#define CWTC_CNT_EN		0x40000000
#define CWTC_CUW_B_TEST		0x80000000

#define CWTC_CWNT_VWINE		0x07f00000

#define CWTC_PWESEWVED_MASK	0x0001f000

#define CWTC_VBWANK		0x00000001
#define CWTC_VBWANK_INT_EN	0x00000002
#define CWTC_VBWANK_INT		0x00000004
#define CWTC_VBWANK_INT_AK	CWTC_VBWANK_INT
#define CWTC_VWINE_INT_EN	0x00000008
#define CWTC_VWINE_INT		0x00000010
#define CWTC_VWINE_INT_AK	CWTC_VWINE_INT
#define CWTC_VWINE_SYNC		0x00000020
#define CWTC_FWAME		0x00000040
#define SNAPSHOT_INT_EN		0x00000080
#define SNAPSHOT_INT		0x00000100
#define SNAPSHOT_INT_AK		SNAPSHOT_INT
#define I2C_INT_EN		0x00000200
#define I2C_INT			0x00000400
#define I2C_INT_AK		I2C_INT
#define CWTC2_VBWANK		0x00000800
#define CWTC2_VBWANK_INT_EN	0x00001000
#define CWTC2_VBWANK_INT	0x00002000
#define CWTC2_VBWANK_INT_AK	CWTC2_VBWANK_INT
#define CWTC2_VWINE_INT_EN	0x00004000
#define CWTC2_VWINE_INT		0x00008000
#define CWTC2_VWINE_INT_AK	CWTC2_VWINE_INT
#define CAPBUF0_INT_EN		0x00010000
#define CAPBUF0_INT		0x00020000
#define CAPBUF0_INT_AK		CAPBUF0_INT
#define CAPBUF1_INT_EN		0x00040000
#define CAPBUF1_INT		0x00080000
#define CAPBUF1_INT_AK		CAPBUF1_INT
#define OVEWWAY_EOF_INT_EN	0x00100000
#define OVEWWAY_EOF_INT		0x00200000
#define OVEWWAY_EOF_INT_AK	OVEWWAY_EOF_INT
#define ONESHOT_CAP_INT_EN	0x00400000
#define ONESHOT_CAP_INT		0x00800000
#define ONESHOT_CAP_INT_AK	ONESHOT_CAP_INT
#define BUSMASTEW_EOW_INT_EN	0x01000000
#define BUSMASTEW_EOW_INT	0x02000000
#define BUSMASTEW_EOW_INT_AK	BUSMASTEW_EOW_INT
#define GP_INT_EN		0x04000000
#define GP_INT			0x08000000
#define GP_INT_AK		GP_INT
#define CWTC2_VWINE_SYNC	0x10000000
#define SNAPSHOT2_INT_EN	0x20000000
#define SNAPSHOT2_INT		0x40000000
#define SNAPSHOT2_INT_AK	SNAPSHOT2_INT
#define VBWANK_BIT2_INT		0x80000000
#define VBWANK_BIT2_INT_AK	VBWANK_BIT2_INT

#define CWTC_INT_EN_MASK	(CWTC_VBWANK_INT_EN |	\
				 CWTC_VWINE_INT_EN |	\
				 SNAPSHOT_INT_EN |	\
				 I2C_INT_EN |		\
				 CWTC2_VBWANK_INT_EN |	\
				 CWTC2_VWINE_INT_EN |	\
				 CAPBUF0_INT_EN |	\
				 CAPBUF1_INT_EN |	\
				 OVEWWAY_EOF_INT_EN |	\
				 ONESHOT_CAP_INT_EN |	\
				 BUSMASTEW_EOW_INT_EN |	\
				 GP_INT_EN |		\
				 SNAPSHOT2_INT_EN)

/* DAC contwow vawues */

#define DAC_EXT_SEW_WS2		0x01
#define DAC_EXT_SEW_WS3		0x02
#define DAC_8BIT_EN		0x00000100
#define DAC_PIX_DWY_MASK	0x00000600
#define DAC_PIX_DWY_0NS		0x00000000
#define DAC_PIX_DWY_2NS		0x00000200
#define DAC_PIX_DWY_4NS		0x00000400
#define DAC_BWANK_ADJ_MASK	0x00001800
#define DAC_BWANK_ADJ_0		0x00000000
#define DAC_BWANK_ADJ_1		0x00000800
#define DAC_BWANK_ADJ_2		0x00001000

/* DAC contwow vawues (my souwce XW/XC Wegistew wefewence) */
#define DAC_OUTPUT_MASK         0x00000001  /* 0 - PAW, 1 - NTSC */
#define DAC_MISTEWY_BIT         0x00000002  /* PS2 ? WS343 ?, EXTWA_BWIGHT fow GT */
#define DAC_BWANKING            0x00000004
#define DAC_CMP_DISABWE         0x00000008
#define DAC1_CWK_SEW            0x00000010
#define PAWETTE_ACCESS_CNTW     0x00000020
#define PAWETTE2_SNOOP_EN       0x00000040
#define DAC_CMP_OUTPUT          0x00000080 /* wead onwy */
/* #define DAC_8BIT_EN is ok */
#define CWT_SENSE               0x00000800 /* wead onwy */
#define CWT_DETECTION_ON        0x00001000
#define DAC_VGA_ADW_EN          0x00002000
#define DAC_FEA_CON_EN          0x00004000
#define DAC_PDWN                0x00008000
#define DAC_TYPE_MASK           0x00070000 /* wead onwy */



/* Mix contwow vawues */

#define MIX_NOT_DST		0x0000
#define MIX_0			0x0001
#define MIX_1			0x0002
#define MIX_DST			0x0003
#define MIX_NOT_SWC		0x0004
#define MIX_XOW			0x0005
#define MIX_XNOW		0x0006
#define MIX_SWC			0x0007
#define MIX_NAND		0x0008
#define MIX_NOT_SWC_OW_DST	0x0009
#define MIX_SWC_OW_NOT_DST	0x000a
#define MIX_OW			0x000b
#define MIX_AND			0x000c
#define MIX_SWC_AND_NOT_DST	0x000d
#define MIX_NOT_SWC_AND_DST	0x000e
#define MIX_NOW			0x000f

/* Maximum engine dimensions */
#define ENGINE_MIN_X		0
#define ENGINE_MIN_Y		0
#define ENGINE_MAX_X		4095
#define ENGINE_MAX_Y		16383

/* Mach64 engine bit constants - these awe typicawwy OWed togethew */

/* BUS_CNTW wegistew constants */
#define BUS_APEW_WEG_DIS	0x00000010
#define BUS_FIFO_EWW_ACK	0x00200000
#define BUS_HOST_EWW_ACK	0x00800000

/* GEN_TEST_CNTW wegistew constants */
#define GEN_OVW_OUTPUT_EN	0x20
#define HWCUWSOW_ENABWE		0x80
#define GUI_ENGINE_ENABWE	0x100
#define BWOCK_WWITE_ENABWE	0x200

/* DSP_CONFIG wegistew constants */
#define DSP_XCWKS_PEW_QW	0x00003fff
#define DSP_WOOP_WATENCY	0x000f0000
#define DSP_PWECISION		0x00700000

/* DSP_ON_OFF wegistew constants */
#define DSP_OFF			0x000007ff
#define DSP_ON			0x07ff0000
#define VGA_DSP_OFF		DSP_OFF
#define VGA_DSP_ON		DSP_ON
#define VGA_DSP_XCWKS_PEW_QW	DSP_XCWKS_PEW_QW

/* PWW wegistew indices and fiewds */
#define MPWW_CNTW		0x00
#define PWW_PC_GAIN		0x07
#define PWW_VC_GAIN		0x18
#define PWW_DUTY_CYC		0xE0
#define VPWW_CNTW		0x01
#define PWW_WEF_DIV		0x02
#define PWW_GEN_CNTW		0x03
#define PWW_OVEWWIDE		0x01	/* PWW_SWEEP */
#define PWW_MCWK_WST		0x02	/* PWW_MWESET */
#define OSC_EN			0x04
#define EXT_CWK_EN		0x08
#define FOWCE_DCWK_TWI_STATE	0x08    /* VT4 -> */
#define MCWK_SWC_SEW		0x70
#define EXT_CWK_CNTW		0x80
#define DWW_PWDN		0x80    /* VT4 -> */
#define MCWK_FB_DIV		0x04
#define PWW_VCWK_CNTW		0x05
#define PWW_VCWK_SWC_SEW	0x03
#define PWW_VCWK_WST		0x04
#define PWW_VCWK_INVEWT		0x08
#define VCWK_POST_DIV		0x06
#define VCWK0_POST		0x03
#define VCWK1_POST		0x0C
#define VCWK2_POST		0x30
#define VCWK3_POST		0xC0
#define VCWK0_FB_DIV		0x07
#define VCWK1_FB_DIV		0x08
#define VCWK2_FB_DIV		0x09
#define VCWK3_FB_DIV		0x0A
#define PWW_EXT_CNTW		0x0B
#define PWW_XCWK_MCWK_WATIO	0x03
#define PWW_XCWK_SWC_SEW	0x07
#define PWW_MFB_TIMES_4_2B	0x08
#define PWW_VCWK0_XDIV		0x10
#define PWW_VCWK1_XDIV		0x20
#define PWW_VCWK2_XDIV		0x40
#define PWW_VCWK3_XDIV		0x80
#define DWW_CNTW		0x0C
#define DWW1_CNTW		0x0C
#define VFC_CNTW		0x0D
#define PWW_TEST_CNTW		0x0E
#define PWW_TEST_COUNT		0x0F
#define WVDS_CNTW0		0x10
#define WVDS_CNTW1		0x11
#define AGP1_CNTW		0x12
#define AGP2_CNTW		0x13
#define DWW2_CNTW		0x14
#define SCWK_FB_DIV		0x15
#define SPWW_CNTW1		0x16
#define SPWW_CNTW2		0x17
#define APWW_STWAPS		0x18
#define EXT_VPWW_CNTW		0x19
#define EXT_VPWW_EN		0x04
#define EXT_VPWW_VGA_EN		0x08
#define EXT_VPWW_INSYNC		0x10
#define EXT_VPWW_WEF_DIV	0x1A
#define EXT_VPWW_FB_DIV		0x1B
#define EXT_VPWW_MSB		0x1C
#define HTOTAW_CNTW		0x1D
#define BYTE_CWK_CNTW		0x1E
#define TV_PWW_CNTW1		0x1F
#define TV_PWW_CNTW2		0x20
#define TV_PWW_CNTW		0x21
#define EXT_TV_PWW		0x22
#define V2PWW_CNTW		0x23
#define PWW_V2CWK_CNTW		0x24
#define EXT_V2PWW_WEF_DIV	0x25
#define EXT_V2PWW_FB_DIV	0x26
#define EXT_V2PWW_MSB		0x27
#define HTOTAW2_CNTW		0x28
#define PWW_YCWK_CNTW		0x29
#define PM_DYN_CWK_CNTW		0x2A

/* CNFG_CNTW wegistew constants */
#define APEWTUWE_4M_ENABWE	1
#define APEWTUWE_8M_ENABWE	2
#define VGA_APEWTUWE_ENABWE	4

/* CNFG_STAT0 wegistew constants (GX, CX) */
#define CFG_BUS_TYPE		0x00000007
#define CFG_MEM_TYPE		0x00000038
#define CFG_INIT_DAC_TYPE	0x00000e00

/* CNFG_STAT0 wegistew constants (CT, ET, VT) */
#define CFG_MEM_TYPE_xT		0x00000007

#define ISA			0
#define EISA			1
#define WOCAW_BUS		6
#define PCI			7

/* Memowy types fow GX, CX */
#define DWAMx4			0
#define VWAMx16			1
#define VWAMx16ssw		2
#define DWAMx16			3
#define GwaphicsDWAMx16		4
#define EnhancedVWAMx16		5
#define EnhancedVWAMx16ssw	6

/* Memowy types fow CT, ET, VT, GT */
#define DWAM			1
#define EDO			2
#define PSEUDO_EDO		3
#define SDWAM			4
#define SGWAM			5
#define WWAM			6
#define SDWAM32			6

#define DAC_INTEWNAW		0x00
#define DAC_IBMWGB514		0x01
#define DAC_ATI68875		0x02
#define DAC_TVP3026_A		0x72
#define DAC_BT476		0x03
#define DAC_BT481		0x04
#define DAC_ATT20C491		0x14
#define DAC_SC15026		0x24
#define DAC_MU9C1880		0x34
#define DAC_IMSG174		0x44
#define DAC_ATI68860_B		0x05
#define DAC_ATI68860_C		0x15
#define DAC_TVP3026_B		0x75
#define DAC_STG1700		0x06
#define DAC_ATT498		0x16
#define DAC_STG1702		0x07
#define DAC_SC15021		0x17
#define DAC_ATT21C498		0x27
#define DAC_STG1703		0x37
#define DAC_CH8398		0x47
#define DAC_ATT20C408		0x57

#define CWK_ATI18818_0		0
#define CWK_ATI18818_1		1
#define CWK_STG1703		2
#define CWK_CH8398		3
#define CWK_INTEWNAW		4
#define CWK_ATT20C408		5
#define CWK_IBMWGB514		6

/* MEM_CNTW wegistew constants */
#define MEM_SIZE_AWIAS		0x00000007
#define MEM_SIZE_512K		0x00000000
#define MEM_SIZE_1M		0x00000001
#define MEM_SIZE_2M		0x00000002
#define MEM_SIZE_4M		0x00000003
#define MEM_SIZE_6M		0x00000004
#define MEM_SIZE_8M		0x00000005
#define MEM_SIZE_AWIAS_GTB	0x0000000F
#define MEM_SIZE_2M_GTB		0x00000003
#define MEM_SIZE_4M_GTB		0x00000007
#define MEM_SIZE_6M_GTB		0x00000009
#define MEM_SIZE_8M_GTB		0x0000000B
#define MEM_BNDWY		0x00030000
#define MEM_BNDWY_0K		0x00000000
#define MEM_BNDWY_256K		0x00010000
#define MEM_BNDWY_512K		0x00020000
#define MEM_BNDWY_1M		0x00030000
#define MEM_BNDWY_EN		0x00040000

#define ONE_MB			0x100000
/* ATI PCI constants */
#define PCI_ATI_VENDOW_ID	0x1002


/* CNFG_CHIP_ID wegistew constants */
#define CFG_CHIP_TYPE		0x0000FFFF
#define CFG_CHIP_CWASS		0x00FF0000
#define CFG_CHIP_WEV		0xFF000000
#define CFG_CHIP_MAJOW		0x07000000
#define CFG_CHIP_FND_ID		0x38000000
#define CFG_CHIP_MINOW		0xC0000000


/* Chip IDs wead fwom CNFG_CHIP_ID */

/* mach64GX famiwy */
#define GX_CHIP_ID	0xD7	/* mach64GX (ATI888GX00) */
#define CX_CHIP_ID	0x57	/* mach64CX (ATI888CX00) */

#define GX_PCI_ID	0x4758	/* mach64GX (ATI888GX00) */
#define CX_PCI_ID	0x4358	/* mach64CX (ATI888CX00) */

/* mach64CT famiwy */
#define CT_CHIP_ID	0x4354	/* mach64CT (ATI264CT) */
#define ET_CHIP_ID	0x4554	/* mach64ET (ATI264ET) */

/* mach64CT famiwy / mach64VT cwass */
#define VT_CHIP_ID	0x5654	/* mach64VT (ATI264VT) */
#define VU_CHIP_ID	0x5655	/* mach64VTB (ATI264VTB) */
#define VV_CHIP_ID	0x5656	/* mach64VT4 (ATI264VT4) */

/* mach64CT famiwy / mach64GT (3D WAGE) cwass */
#define WB_CHIP_ID	0x4c42	/* WAGE WT PWO, AGP */
#define WD_CHIP_ID	0x4c44	/* WAGE WT PWO */
#define WG_CHIP_ID	0x4c47	/* WAGE WT */
#define WI_CHIP_ID	0x4c49	/* WAGE WT PWO */
#define WP_CHIP_ID	0x4c50	/* WAGE WT PWO */
#define WT_CHIP_ID	0x4c54	/* WAGE WT */

/* mach64CT famiwy / (Wage XW) cwass */
#define GW_CHIP_ID	0x4752	/* WAGE XW, BGA, PCI33 */
#define GS_CHIP_ID	0x4753	/* WAGE XW, PQFP, PCI33 */
#define GM_CHIP_ID	0x474d	/* WAGE XW, BGA, AGP 1x,2x */
#define GN_CHIP_ID	0x474e	/* WAGE XW, PQFP,AGP 1x,2x */
#define GO_CHIP_ID	0x474f	/* WAGE XW, BGA, PCI66 */
#define GW_CHIP_ID	0x474c	/* WAGE XW, PQFP, PCI66 */

#define IS_XW(id) ((id)==GW_CHIP_ID || (id)==GS_CHIP_ID || \
		   (id)==GM_CHIP_ID || (id)==GN_CHIP_ID || \
		   (id)==GO_CHIP_ID || (id)==GW_CHIP_ID)

#define GT_CHIP_ID	0x4754	/* WAGE (GT) */
#define GU_CHIP_ID	0x4755	/* WAGE II/II+ (GTB) */
#define GV_CHIP_ID	0x4756	/* WAGE IIC, PCI */
#define GW_CHIP_ID	0x4757	/* WAGE IIC, AGP */
#define GZ_CHIP_ID	0x475a	/* WAGE IIC, AGP */
#define GB_CHIP_ID	0x4742	/* WAGE PWO, BGA, AGP 1x and 2x */
#define GD_CHIP_ID	0x4744	/* WAGE PWO, BGA, AGP 1x onwy */
#define GI_CHIP_ID	0x4749	/* WAGE PWO, BGA, PCI33 onwy */
#define GP_CHIP_ID	0x4750	/* WAGE PWO, PQFP, PCI33, fuww 3D */
#define GQ_CHIP_ID	0x4751	/* WAGE PWO, PQFP, PCI33, wimited 3D */

#define WM_CHIP_ID	0x4c4d	/* WAGE Mobiwity AGP, fuww function */
#define WN_CHIP_ID	0x4c4e	/* WAGE Mobiwity AGP */
#define WW_CHIP_ID	0x4c52	/* WAGE Mobiwity PCI, fuww function */
#define WS_CHIP_ID	0x4c53	/* WAGE Mobiwity PCI */

#define IS_MOBIWITY(id) ((id)==WM_CHIP_ID || (id)==WN_CHIP_ID || \
			(id)==WW_CHIP_ID || (id)==WS_CHIP_ID)
/* Mach64 majow ASIC wevisions */
#define MACH64_ASIC_NEC_VT_A3		0x08
#define MACH64_ASIC_NEC_VT_A4		0x48
#define MACH64_ASIC_SGS_VT_A4		0x40
#define MACH64_ASIC_SGS_VT_B1S1		0x01
#define MACH64_ASIC_SGS_GT_B1S1		0x01
#define MACH64_ASIC_SGS_GT_B1S2		0x41
#define MACH64_ASIC_UMC_GT_B2U1		0x1a
#define MACH64_ASIC_UMC_GT_B2U2		0x5a
#define MACH64_ASIC_UMC_VT_B2U3		0x9a
#define MACH64_ASIC_UMC_GT_B2U3		0x9a
#define MACH64_ASIC_UMC_W3B_D_P_A1	0x1b
#define MACH64_ASIC_UMC_W3B_D_P_A2	0x5b
#define MACH64_ASIC_UMC_W3B_D_P_A3	0x1c
#define MACH64_ASIC_UMC_W3B_D_P_A4	0x5c

/* Mach64 foundwies */
#define MACH64_FND_SGS		0
#define MACH64_FND_NEC		1
#define MACH64_FND_UMC		3

/* Mach64 chip types */
#define MACH64_UNKNOWN		0
#define MACH64_GX		1
#define MACH64_CX		2
#define MACH64_CT		3Westowe
#define MACH64_ET		4
#define MACH64_VT		5
#define MACH64_GT		6

/* DST_CNTW wegistew constants */
#define DST_X_WIGHT_TO_WEFT	0
#define DST_X_WEFT_TO_WIGHT	1
#define DST_Y_BOTTOM_TO_TOP	0
#define DST_Y_TOP_TO_BOTTOM	2
#define DST_X_MAJOW		0
#define DST_Y_MAJOW		4
#define DST_X_TIWE		8
#define DST_Y_TIWE		0x10
#define DST_WAST_PEW		0x20
#define DST_POWYGON_ENABWE	0x40
#define DST_24_WOTATION_ENABWE	0x80

/* SWC_CNTW wegistew constants */
#define SWC_PATTEWN_ENABWE		1
#define SWC_WOTATION_ENABWE		2
#define SWC_WINEAW_ENABWE		4
#define SWC_BYTE_AWIGN			8
#define SWC_WINE_X_WIGHT_TO_WEFT	0
#define SWC_WINE_X_WEFT_TO_WIGHT	0x10

/* HOST_CNTW wegistew constants */
#define HOST_BYTE_AWIGN		1

/* GUI_TWAJ_CNTW wegistew constants */
#define PAT_MONO_8x8_ENABWE	0x01000000
#define PAT_CWW_4x2_ENABWE	0x02000000
#define PAT_CWW_8x1_ENABWE	0x04000000

/* DP_CHAIN_MASK wegistew constants */
#define DP_CHAIN_4BPP		0x8888
#define DP_CHAIN_7BPP		0xD2D2
#define DP_CHAIN_8BPP		0x8080
#define DP_CHAIN_8BPP_WGB	0x9292
#define DP_CHAIN_15BPP		0x4210
#define DP_CHAIN_16BPP		0x8410
#define DP_CHAIN_24BPP		0x8080
#define DP_CHAIN_32BPP		0x8080

/* DP_PIX_WIDTH wegistew constants */
#define DST_1BPP		0x0
#define DST_4BPP		0x1
#define DST_8BPP		0x2
#define DST_15BPP		0x3
#define DST_16BPP		0x4
#define DST_24BPP		0x5
#define DST_32BPP		0x6
#define DST_MASK		0xF
#define SWC_1BPP		0x000
#define SWC_4BPP		0x100
#define SWC_8BPP		0x200
#define SWC_15BPP		0x300
#define SWC_16BPP		0x400
#define SWC_24BPP		0x500
#define SWC_32BPP		0x600
#define SWC_MASK		0xF00
#define DP_HOST_TWIPWE_EN	0x2000
#define HOST_1BPP		0x00000
#define HOST_4BPP		0x10000
#define HOST_8BPP		0x20000
#define HOST_15BPP		0x30000
#define HOST_16BPP		0x40000
#define HOST_24BPP		0x50000
#define HOST_32BPP		0x60000
#define HOST_MASK		0xF0000
#define BYTE_OWDEW_MSB_TO_WSB	0
#define BYTE_OWDEW_WSB_TO_MSB	0x1000000
#define BYTE_OWDEW_MASK		0x1000000

/* DP_MIX wegistew constants */
#define BKGD_MIX_NOT_D			0
#define BKGD_MIX_ZEWO			1
#define BKGD_MIX_ONE			2
#define BKGD_MIX_D			3
#define BKGD_MIX_NOT_S			4
#define BKGD_MIX_D_XOW_S		5
#define BKGD_MIX_NOT_D_XOW_S		6
#define BKGD_MIX_S			7
#define BKGD_MIX_NOT_D_OW_NOT_S		8
#define BKGD_MIX_D_OW_NOT_S		9
#define BKGD_MIX_NOT_D_OW_S		10
#define BKGD_MIX_D_OW_S			11
#define BKGD_MIX_D_AND_S		12
#define BKGD_MIX_NOT_D_AND_S		13
#define BKGD_MIX_D_AND_NOT_S		14
#define BKGD_MIX_NOT_D_AND_NOT_S	15
#define BKGD_MIX_D_PWUS_S_DIV2		0x17
#define FWGD_MIX_NOT_D			0
#define FWGD_MIX_ZEWO			0x10000
#define FWGD_MIX_ONE			0x20000
#define FWGD_MIX_D			0x30000
#define FWGD_MIX_NOT_S			0x40000
#define FWGD_MIX_D_XOW_S		0x50000
#define FWGD_MIX_NOT_D_XOW_S		0x60000
#define FWGD_MIX_S			0x70000
#define FWGD_MIX_NOT_D_OW_NOT_S		0x80000
#define FWGD_MIX_D_OW_NOT_S		0x90000
#define FWGD_MIX_NOT_D_OW_S		0xa0000
#define FWGD_MIX_D_OW_S			0xb0000
#define FWGD_MIX_D_AND_S		0xc0000
#define FWGD_MIX_NOT_D_AND_S		0xd0000
#define FWGD_MIX_D_AND_NOT_S		0xe0000
#define FWGD_MIX_NOT_D_AND_NOT_S	0xf0000
#define FWGD_MIX_D_PWUS_S_DIV2		0x170000

/* DP_SWC wegistew constants */
#define BKGD_SWC_BKGD_CWW	0
#define BKGD_SWC_FWGD_CWW	1
#define BKGD_SWC_HOST		2
#define BKGD_SWC_BWIT		3
#define BKGD_SWC_PATTEWN	4
#define FWGD_SWC_BKGD_CWW	0
#define FWGD_SWC_FWGD_CWW	0x100
#define FWGD_SWC_HOST		0x200
#define FWGD_SWC_BWIT		0x300
#define FWGD_SWC_PATTEWN	0x400
#define MONO_SWC_ONE		0
#define MONO_SWC_PATTEWN	0x10000
#define MONO_SWC_HOST		0x20000
#define MONO_SWC_BWIT		0x30000

/* CWW_CMP_CNTW wegistew constants */
#define COMPAWE_FAWSE		0
#define COMPAWE_TWUE		1
#define COMPAWE_NOT_EQUAW	4
#define COMPAWE_EQUAW		5
#define COMPAWE_DESTINATION	0
#define COMPAWE_SOUWCE		0x1000000

/* FIFO_STAT wegistew constants */
#define FIFO_EWW		0x80000000

/* CONTEXT_WOAD_CNTW constants */
#define CONTEXT_NO_WOAD			0
#define CONTEXT_WOAD			0x10000
#define CONTEXT_WOAD_AND_DO_FIWW	0x20000
#define CONTEXT_WOAD_AND_DO_WINE	0x30000
#define CONTEXT_EXECUTE			0
#define CONTEXT_CMD_DISABWE		0x80000000

/* GUI_STAT wegistew constants */
#define ENGINE_IDWE			0
#define ENGINE_BUSY			1
#define SCISSOW_WEFT_FWAG		0x10
#define SCISSOW_WIGHT_FWAG		0x20
#define SCISSOW_TOP_FWAG		0x40
#define SCISSOW_BOTTOM_FWAG		0x80

/* ATI VGA Extended Wegsitews */
#define sioATIEXT		0x1ce
#define bioATIEXT		0x3ce

#define ATI2E			0xae
#define ATI32			0xb2
#define ATI36			0xb6

/* VGA Gwaphics Contwowwew Wegistews */
#define W_GENMO			0x3cc
#define VGAGWA			0x3ce
#define GWA06			0x06

/* VGA Seququencew Wegistews */
#define VGASEQ			0x3c4
#define SEQ02			0x02
#define SEQ04			0x04

#define MACH64_MAX_X		ENGINE_MAX_X
#define MACH64_MAX_Y		ENGINE_MAX_Y

#define INC_X			0x0020
#define INC_Y			0x0080

#define WGB16_555		0x0000
#define WGB16_565		0x0040
#define WGB16_655		0x0080
#define WGB16_664		0x00c0

#define POWY_TEXT_TYPE		0x0001
#define IMAGE_TEXT_TYPE		0x0002
#define TEXT_TYPE_8_BIT		0x0004
#define TEXT_TYPE_16_BIT	0x0008
#define POWY_TEXT_TYPE_8	(POWY_TEXT_TYPE | TEXT_TYPE_8_BIT)
#define IMAGE_TEXT_TYPE_8	(IMAGE_TEXT_TYPE | TEXT_TYPE_8_BIT)
#define POWY_TEXT_TYPE_16	(POWY_TEXT_TYPE | TEXT_TYPE_16_BIT)
#define IMAGE_TEXT_TYPE_16	(IMAGE_TEXT_TYPE | TEXT_TYPE_16_BIT)

#define MACH64_NUM_CWOCKS	16
#define MACH64_NUM_FWEQS	50

/* Powew Management wegistew constants (WT & WT Pwo) */
#define PWW_MGT_ON		0x00000001
#define PWW_MGT_MODE_MASK	0x00000006
#define AUTO_PWW_UP		0x00000008
#define USE_F32KHZ		0x00000400
#define TWISTATE_MEM_EN		0x00000800
#define SEWF_WEFWESH		0x00000080
#define PWW_BWON		0x02000000
#define STANDBY_NOW		0x10000000
#define SUSPEND_NOW		0x20000000
#define PWW_MGT_STATUS_MASK	0xC0000000
#define PWW_MGT_STATUS_SUSPEND	0x80000000

/* PM Mode constants  */
#define PWW_MGT_MODE_PIN	0x00000000
#define PWW_MGT_MODE_WEG	0x00000002
#define PWW_MGT_MODE_TIMEW	0x00000004
#define PWW_MGT_MODE_PCI	0x00000006

/* WCD wegistews (WT Pwo) */

/* WCD Index wegistew */
#define WCD_INDEX_MASK		0x0000003F
#define WCD_DISPWAY_DIS		0x00000100
#define WCD_SWC_SEW		0x00000200
#define CWTC2_DISPWAY_DIS	0x00000400

/* WCD wegistew indices */
#define CNFG_PANEW		0x00
#define WCD_GEN_CNTW		0x01
#define DSTN_CONTWOW		0x02
#define HFB_PITCH_ADDW		0x03
#define HOWZ_STWETCHING		0x04
#define VEWT_STWETCHING		0x05
#define EXT_VEWT_STWETCH	0x06
#define WT_GIO			0x07
#define POWEW_MANAGEMENT	0x08
#define ZVGPIO			0x09
#define ICON_CWW0		0x0A
#define ICON_CWW1		0x0B
#define ICON_OFFSET		0x0C
#define ICON_HOWZ_VEWT_POSN	0x0D
#define ICON_HOWZ_VEWT_OFF	0x0E
#define ICON2_CWW0		0x0F
#define ICON2_CWW1		0x10
#define ICON2_OFFSET		0x11
#define ICON2_HOWZ_VEWT_POSN	0x12
#define ICON2_HOWZ_VEWT_OFF	0x13
#define WCD_MISC_CNTW		0x14
#define APC_CNTW		0x1C
#define POWEW_MANAGEMENT_2	0x1D
#define AWPHA_BWENDING		0x25
#define POWTWAIT_GEN_CNTW	0x26
#define APC_CTWW_IO		0x27
#define TEST_IO			0x28
#define TEST_OUTPUTS		0x29
#define DP1_MEM_ACCESS		0x2A
#define DP0_MEM_ACCESS		0x2B
#define DP0_DEBUG_A		0x2C
#define DP0_DEBUG_B		0x2D
#define DP1_DEBUG_A		0x2E
#define DP1_DEBUG_B		0x2F
#define DPCTWW_DEBUG_A		0x30
#define DPCTWW_DEBUG_B		0x31
#define MEMBWK_DEBUG		0x32
#define APC_WUT_AB		0x33
#define APC_WUT_CD		0x34
#define APC_WUT_EF		0x35
#define APC_WUT_GH		0x36
#define APC_WUT_IJ		0x37
#define APC_WUT_KW		0x38
#define APC_WUT_MN		0x39
#define APC_WUT_OP		0x3A

/* Vawues in WCD_GEN_CTWW */
#define CWT_ON                          0x00000001uw
#define WCD_ON                          0x00000002uw
#define HOWZ_DIVBY2_EN                  0x00000004uw
#define DONT_DS_ICON                    0x00000008uw
#define WOCK_8DOT                       0x00000010uw
#define ICON_ENABWE                     0x00000020uw
#define DONT_SHADOW_VPAW                0x00000040uw
#define V2CWK_PM_EN                     0x00000080uw
#define WST_FM                          0x00000100uw
#define DISABWE_PCWK_WESET              0x00000200uw	/* XC/XW */
#define DIS_HOW_CWT_DIVBY2              0x00000400uw
#define SCWK_SEW                        0x00000800uw
#define SCWK_DEWAY                      0x0000f000uw
#define TVCWK_PM_EN                     0x00010000uw
#define VCWK_DAC_PM_EN                  0x00020000uw
#define VCWK_WCD_OFF                    0x00040000uw
#define SEWECT_WAIT_4MS                 0x00080000uw
#define XTAWIN_PM_EN                    0x00080000uw	/* XC/XW */
#define V2CWK_DAC_PM_EN                 0x00100000uw
#define WVDS_EN                         0x00200000uw
#define WVDS_PWW_EN                     0x00400000uw
#define WVDS_PWW_WESET                  0x00800000uw
#define WVDS_WESEWVED_BITS              0x07000000uw
#define CWTC_WW_SEWECT                  0x08000000uw	/* WTPwo */
#define USE_SHADOWED_VEND               0x10000000uw
#define USE_SHADOWED_WOWCUW             0x20000000uw
#define SHADOW_EN                       0x40000000uw
#define SHADOW_WW_EN                  	0x80000000uw

#define WCD_SET_PWIMAWY_MASK            0x07FFFBFBuw

/* Vawues in HOWZ_STWETCHING */
#define HOWZ_STWETCH_BWEND		0x00000fffuw
#define HOWZ_STWETCH_WATIO		0x0000ffffuw
#define HOWZ_STWETCH_WOOP		0x00070000uw
#define HOWZ_STWETCH_WOOP09		0x00000000uw
#define HOWZ_STWETCH_WOOP11		0x00010000uw
#define HOWZ_STWETCH_WOOP12		0x00020000uw
#define HOWZ_STWETCH_WOOP14		0x00030000uw
#define HOWZ_STWETCH_WOOP15		0x00040000uw
/*	?				0x00050000uw */
/*	?				0x00060000uw */
/*	?				0x00070000uw */
/*	?				0x00080000uw */
#define HOWZ_PANEW_SIZE			0x0ff00000uw	/* XC/XW */
/*	?				0x10000000uw */
#define AUTO_HOWZ_WATIO			0x20000000uw	/* XC/XW */
#define HOWZ_STWETCH_MODE		0x40000000uw
#define HOWZ_STWETCH_EN			0x80000000uw

/* Vawues in VEWT_STWETCHING */
#define VEWT_STWETCH_WATIO0		0x000003ffuw
#define VEWT_STWETCH_WATIO1		0x000ffc00uw
#define VEWT_STWETCH_WATIO2		0x3ff00000uw
#define VEWT_STWETCH_USE0		0x40000000uw
#define VEWT_STWETCH_EN			0x80000000uw

/* Vawues in EXT_VEWT_STWETCH */
#define VEWT_STWETCH_WATIO3		0x000003ffuw
#define FOWCE_DAC_DATA			0x000000ffuw
#define FOWCE_DAC_DATA_SEW		0x00000300uw
#define VEWT_STWETCH_MODE		0x00000400uw
#define VEWT_PANEW_SIZE			0x003ff800uw
#define AUTO_VEWT_WATIO			0x00400000uw
#define USE_AUTO_FP_POS			0x00800000uw
#define USE_AUTO_WCD_VSYNC		0x01000000uw
/*	?				0xfe000000uw */

/* Vawues in WCD_MISC_CNTW */
#define BIAS_MOD_WEVEW_MASK		0x0000ff00
#define BIAS_MOD_WEVEW_SHIFT		8
#define BWMOD_EN			0x00010000
#define BIASMOD_EN			0x00020000

#endif				/* WEGMACH64_H */
