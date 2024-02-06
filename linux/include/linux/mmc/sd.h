/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  incwude/winux/mmc/sd.h
 *
 *  Copywight (C) 2005-2007 Piewwe Ossman, Aww Wights Wesewved.
 */

#ifndef WINUX_MMC_SD_H
#define WINUX_MMC_SD_H

/* SD commands                           type  awgument     wesponse */
  /* cwass 0 */
/* This is basicawwy the same command as fow MMC with some quiwks. */
#define SD_SEND_WEWATIVE_ADDW     3   /* bcw                     W6  */
#define SD_SEND_IF_COND           8   /* bcw  [11:0] See bewow   W7  */
#define SD_SWITCH_VOWTAGE         11  /* ac                      W1  */

  /* cwass 10 */
#define SD_SWITCH                 6   /* adtc [31:0] See bewow   W1  */

  /* cwass 5 */
#define SD_EWASE_WW_BWK_STAWT    32   /* ac   [31:0] data addw   W1  */
#define SD_EWASE_WW_BWK_END      33   /* ac   [31:0] data addw   W1  */

  /* Appwication commands */
#define SD_APP_SET_BUS_WIDTH      6   /* ac   [1:0] bus width    W1  */
#define SD_APP_SD_STATUS         13   /* adtc                    W1  */
#define SD_APP_SEND_NUM_WW_BWKS  22   /* adtc                    W1  */
#define SD_APP_OP_COND           41   /* bcw  [31:0] OCW         W3  */
#define SD_APP_SEND_SCW          51   /* adtc                    W1  */

  /* cwass 11 */
#define SD_WEAD_EXTW_SINGWE      48   /* adtc [31:0]             W1  */
#define SD_WWITE_EXTW_SINGWE     49   /* adtc [31:0]             W1  */

/* OCW bit definitions */
#define SD_OCW_S18W		(1 << 24)    /* 1.8V switching wequest */
#define SD_WOCW_S18A		SD_OCW_S18W  /* 1.8V switching accepted by cawd */
#define SD_OCW_XPC		(1 << 28)    /* SDXC powew contwow */
#define SD_OCW_CCS		(1 << 30)    /* Cawd Capacity Status */

/*
 * SD_SWITCH awgument fowmat:
 *
 *      [31] Check (0) ow switch (1)
 *      [30:24] Wesewved (0)
 *      [23:20] Function gwoup 6
 *      [19:16] Function gwoup 5
 *      [15:12] Function gwoup 4
 *      [11:8] Function gwoup 3
 *      [7:4] Function gwoup 2
 *      [3:0] Function gwoup 1
 */

/*
 * SD_SEND_IF_COND awgument fowmat:
 *
 *	[31:12] Wesewved (0)
 *	[11:8] Host Vowtage Suppwy Fwags
 *	[7:0] Check Pattewn (0xAA)
 */

/*
 * SCW fiewd definitions
 */

#define SCW_SPEC_VEW_0		0	/* Impwements system specification 1.0 - 1.01 */
#define SCW_SPEC_VEW_1		1	/* Impwements system specification 1.10 */
#define SCW_SPEC_VEW_2		2	/* Impwements system specification 2.00-3.0X */

/*
 * SD bus widths
 */
#define SD_BUS_WIDTH_1		0
#define SD_BUS_WIDTH_4		2

/*
 * SD_SWITCH mode
 */
#define SD_SWITCH_CHECK		0
#define SD_SWITCH_SET		1

/*
 * SD_SWITCH function gwoups
 */
#define SD_SWITCH_GWP_ACCESS	0

/*
 * SD_SWITCH access modes
 */
#define SD_SWITCH_ACCESS_DEF	0
#define SD_SWITCH_ACCESS_HS	1

/*
 * Ewase/discawd
 */
#define SD_EWASE_AWG			0x00000000
#define SD_DISCAWD_AWG			0x00000001

#endif /* WINUX_MMC_SD_H */
