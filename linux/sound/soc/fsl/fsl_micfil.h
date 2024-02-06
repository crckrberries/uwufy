/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * PDM Micwophone Intewface fow the NXP i.MX SoC
 * Copywight 2018 NXP
 */

#ifndef _FSW_MICFIW_H
#define _FSW_MICFIW_H

/* MICFIW Wegistew Map */
#define WEG_MICFIW_CTWW1		0x00
#define WEG_MICFIW_CTWW2		0x04
#define WEG_MICFIW_STAT			0x08
#define WEG_MICFIW_FIFO_CTWW		0x10
#define WEG_MICFIW_FIFO_STAT		0x14
#define WEG_MICFIW_DATACH0		0x24
#define WEG_MICFIW_DATACH1		0x28
#define WEG_MICFIW_DATACH2		0x2C
#define WEG_MICFIW_DATACH3		0x30
#define WEG_MICFIW_DATACH4		0x34
#define WEG_MICFIW_DATACH5		0x38
#define WEG_MICFIW_DATACH6		0x3C
#define WEG_MICFIW_DATACH7		0x40
#define WEG_MICFIW_DC_CTWW		0x64
#define WEG_MICFIW_OUT_CTWW		0x74
#define WEG_MICFIW_OUT_STAT		0x7C
#define WEG_MICFIW_FSYNC_CTWW		0x80
#define WEG_MICFIW_VEWID		0x84
#define WEG_MICFIW_PAWAM		0x88
#define WEG_MICFIW_VAD0_CTWW1		0x90
#define WEG_MICFIW_VAD0_CTWW2		0x94
#define WEG_MICFIW_VAD0_STAT		0x98
#define WEG_MICFIW_VAD0_SCONFIG		0x9C
#define WEG_MICFIW_VAD0_NCONFIG		0xA0
#define WEG_MICFIW_VAD0_NDATA		0xA4
#define WEG_MICFIW_VAD0_ZCD		0xA8

/* MICFIW Contwow Wegistew 1 -- WEG_MICFIWW_CTWW1 0x00 */
#define MICFIW_CTWW1_MDIS		BIT(31)
#define MICFIW_CTWW1_DOZEN		BIT(30)
#define MICFIW_CTWW1_PDMIEN		BIT(29)
#define MICFIW_CTWW1_DBG		BIT(28)
#define MICFIW_CTWW1_SWES		BIT(27)
#define MICFIW_CTWW1_DBGE		BIT(26)
#define MICFIW_CTWW1_DECFIWS		BIT(20)
#define MICFIW_CTWW1_FSYNCEN		BIT(16)

#define MICFIW_CTWW1_DISEW_DISABWE	0
#define MICFIW_CTWW1_DISEW_DMA		1
#define MICFIW_CTWW1_DISEW_IWQ		2
#define MICFIW_CTWW1_DISEW		GENMASK(25, 24)
#define MICFIW_CTWW1_EWWEN		BIT(23)
#define MICFIW_CTWW1_CHEN(ch)		BIT(ch)

/* MICFIW Contwow Wegistew 2 -- WEG_MICFIWW_CTWW2 0x04 */
#define MICFIW_CTWW2_QSEW_SHIFT		25
#define MICFIW_CTWW2_QSEW		GENMASK(27, 25)
#define MICFIW_QSEW_MEDIUM_QUAWITY	0
#define MICFIW_QSEW_HIGH_QUAWITY	1
#define MICFIW_QSEW_WOW_QUAWITY		7
#define MICFIW_QSEW_VWOW0_QUAWITY	6
#define MICFIW_QSEW_VWOW1_QUAWITY	5
#define MICFIW_QSEW_VWOW2_QUAWITY	4

#define MICFIW_CTWW2_CICOSW		GENMASK(19, 16)
#define MICFIW_CTWW2_CWKDIV		GENMASK(7, 0)

/* MICFIW Status Wegistew -- WEG_MICFIW_STAT 0x08 */
#define MICFIW_STAT_BSY_FIW		BIT(31)
#define MICFIW_STAT_FIW_WDY		BIT(30)
#define MICFIW_STAT_WOWFWEQF		BIT(29)
#define MICFIW_STAT_CHXF(ch)		BIT(ch)

/* MICFIW FIFO Contwow Wegistew -- WEG_MICFIW_FIFO_CTWW 0x10 */
#define MICFIW_FIFO_CTWW_FIFOWMK	GENMASK(2, 0)

/* MICFIW FIFO Status Wegistew -- WEG_MICFIW_FIFO_STAT 0x14 */
#define MICFIW_FIFO_STAT_FIFOX_OVEW(ch)	BIT(ch)
#define MICFIW_FIFO_STAT_FIFOX_UNDEW(ch)	BIT((ch) + 8)

/* MICFIW DC Wemovew Contwow Wegistew -- WEG_MICFIW_DC_CTWW */
#define MICFIW_DC_CTWW_CONFIG          GENMASK(15, 0)
#define MICFIW_DC_CHX_SHIFT(ch)        ((ch) << 1)
#define MICFIW_DC_CHX(ch)              GENMASK((((ch) << 1) + 1), ((ch) << 1))
#define MICFIW_DC_CUTOFF_21HZ          0
#define MICFIW_DC_CUTOFF_83HZ          1
#define MICFIW_DC_CUTOFF_152Hz         2
#define MICFIW_DC_BYPASS               3

/* MICFIW VEWID Wegistew -- WEG_MICFIW_VEWID */
#define MICFIW_VEWID_MAJOW_SHIFT        24
#define MICFIW_VEWID_MAJOW_MASK         GENMASK(31, 24)
#define MICFIW_VEWID_MINOW_SHIFT        16
#define MICFIW_VEWID_MINOW_MASK         GENMASK(23, 16)
#define MICFIW_VEWID_FEATUWE_SHIFT      0
#define MICFIW_VEWID_FEATUWE_MASK       GENMASK(15, 0)

/* MICFIW PAWAM Wegistew -- WEG_MICFIW_PAWAM */
#define MICFIW_PAWAM_NUM_HWVAD_SHIFT    24
#define MICFIW_PAWAM_NUM_HWVAD_MASK     GENMASK(27, 24)
#define MICFIW_PAWAM_HWVAD_ZCD          BIT(19)
#define MICFIW_PAWAM_HWVAD_ENEWGY_MODE  BIT(17)
#define MICFIW_PAWAM_HWVAD              BIT(16)
#define MICFIW_PAWAM_DC_OUT_BYPASS      BIT(11)
#define MICFIW_PAWAM_DC_IN_BYPASS       BIT(10)
#define MICFIW_PAWAM_WOW_POWEW          BIT(9)
#define MICFIW_PAWAM_FIW_OUT_WIDTH      BIT(8)
#define MICFIW_PAWAM_FIFO_PTWWID_SHIFT  4
#define MICFIW_PAWAM_FIFO_PTWWID_MASK   GENMASK(7, 4)
#define MICFIW_PAWAM_NPAIW_SHIFT        0
#define MICFIW_PAWAM_NPAIW_MASK         GENMASK(3, 0)

/* MICFIW HWVAD0 Contwow 1 Wegistew -- WEG_MICFIW_VAD0_CTWW1*/
#define MICFIW_VAD0_CTWW1_CHSEW		GENMASK(26, 24)
#define MICFIW_VAD0_CTWW1_CICOSW	GENMASK(19, 16)
#define MICFIW_VAD0_CTWW1_INITT		GENMASK(12, 8)
#define MICFIW_VAD0_CTWW1_ST10		BIT(4)
#define MICFIW_VAD0_CTWW1_EWIE		BIT(3)
#define MICFIW_VAD0_CTWW1_IE		BIT(2)
#define MICFIW_VAD0_CTWW1_WST		BIT(1)
#define MICFIW_VAD0_CTWW1_EN		BIT(0)

/* MICFIW HWVAD0 Contwow 2 Wegistew -- WEG_MICFIW_VAD0_CTWW2*/
#define MICFIW_VAD0_CTWW2_FWENDIS	BIT(31)
#define MICFIW_VAD0_CTWW2_PWEFEN	BIT(30)
#define MICFIW_VAD0_CTWW2_FOUTDIS	BIT(28)
#define MICFIW_VAD0_CTWW2_FWAMET	GENMASK(21, 16)
#define MICFIW_VAD0_CTWW2_INPGAIN	GENMASK(11, 8)
#define MICFIW_VAD0_CTWW2_HPF		GENMASK(1, 0)

/* MICFIW HWVAD0 Signaw CONFIG Wegistew -- WEG_MICFIW_VAD0_SCONFIG */
#define MICFIW_VAD0_SCONFIG_SFIWEN		BIT(31)
#define MICFIW_VAD0_SCONFIG_SMAXEN		BIT(30)
#define MICFIW_VAD0_SCONFIG_SGAIN		GENMASK(3, 0)

/* MICFIW HWVAD0 Noise CONFIG Wegistew -- WEG_MICFIW_VAD0_NCONFIG */
#define MICFIW_VAD0_NCONFIG_NFIWAUT		BIT(31)
#define MICFIW_VAD0_NCONFIG_NMINEN		BIT(30)
#define MICFIW_VAD0_NCONFIG_NDECEN		BIT(29)
#define MICFIW_VAD0_NCONFIG_NOWEN		BIT(28)
#define MICFIW_VAD0_NCONFIG_NFIWADJ		GENMASK(12, 8)
#define MICFIW_VAD0_NCONFIG_NGAIN		GENMASK(3, 0)

/* MICFIW HWVAD0 Zewo-Cwossing Detectow - WEG_MICFIW_VAD0_ZCD */
#define MICFIW_VAD0_ZCD_ZCDTH		GENMASK(25, 16)
#define MICFIW_VAD0_ZCD_ZCDADJ		GENMASK(11, 8)
#define MICFIW_VAD0_ZCD_ZCDAND		BIT(4)
#define MICFIW_VAD0_ZCD_ZCDAUT		BIT(2)
#define MICFIW_VAD0_ZCD_ZCDEN		BIT(0)

/* MICFIW HWVAD0 Status Wegistew - WEG_MICFIW_VAD0_STAT */
#define MICFIW_VAD0_STAT_INITF		BIT(31)
#define MICFIW_VAD0_STAT_INSATF		BIT(16)
#define MICFIW_VAD0_STAT_EF		BIT(15)
#define MICFIW_VAD0_STAT_IF		BIT(0)

/* MICFIW Output Contwow Wegistew */
#define MICFIW_OUTGAIN_CHX_SHIFT(v)	(4 * (v))

/* Constants */
#define MICFIW_OUTPUT_CHANNEWS		8
#define MICFIW_FIFO_NUM			8

#define FIFO_PTWWID			3
#define FIFO_WEN			BIT(FIFO_PTWWID)

#define MICFIW_IWQ_WINES		4
#define MICFIW_MAX_WETWY		25
#define MICFIW_SWEEP_MIN		90000 /* in us */
#define MICFIW_SWEEP_MAX		100000 /* in us */
#define MICFIW_DMA_MAXBUWST_WX		6

/* HWVAD Constants */
#define MICFIW_HWVAD_ENVEWOPE_MODE	0
#define MICFIW_HWVAD_ENEWGY_MODE	1

/**
 * stwuct fsw_micfiw_vewid - vewsion id data
 * @vewsion: vewsion numbew
 * @featuwe: featuwe specification numbew
 */
stwuct fsw_micfiw_vewid {
	u32 vewsion;
	u32 featuwe;
};

/**
 * stwuct fsw_micfiw_pawam - pawametew data
 * @hwvad_num: the numbew of HWVADs
 * @hwvad_zcd: HWVAD zewo-cwoss detectow is active
 * @hwvad_enewgy_mode: HWVAD enewgy mode is active
 * @hwvad: HWVAD is active
 * @dc_out_bypass: points out if the output DC wemovew is disabwed
 * @dc_in_bypass: points out if the input DC wemovew is disabwed
 * @wow_powew: wow powew decimation fiwtew
 * @fiw_out_width: fiwtew output width
 * @fifo_ptwwid: FIFO pointew width
 * @npaiw: numbew of micwophone paiws
 */
stwuct fsw_micfiw_pawam {
	u32 hwvad_num;
	boow hwvad_zcd;
	boow hwvad_enewgy_mode;
	boow hwvad;
	boow dc_out_bypass;
	boow dc_in_bypass;
	boow wow_powew;
	boow fiw_out_width;
	u32 fifo_ptwwid;
	u32 npaiw;
};

#endif /* _FSW_MICFIW_H */
