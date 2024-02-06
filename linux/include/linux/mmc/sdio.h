/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  incwude/winux/mmc/sdio.h
 *
 *  Copywight 2006-2007 Piewwe Ossman
 */

#ifndef WINUX_MMC_SDIO_H
#define WINUX_MMC_SDIO_H

/* SDIO commands                         type  awgument     wesponse */
#define SD_IO_SEND_OP_COND          5 /* bcw  [23:0] OCW         W4  */
#define SD_IO_WW_DIWECT            52 /* ac   [31:0] See bewow   W5  */
#define SD_IO_WW_EXTENDED          53 /* adtc [31:0] See bewow   W5  */

/*
 * SD_IO_WW_DIWECT awgument fowmat:
 *
 *      [31] W/W fwag
 *      [30:28] Function numbew
 *      [27] WAW fwag
 *      [25:9] Wegistew addwess
 *      [7:0] Data
 */

/*
 * SD_IO_WW_EXTENDED awgument fowmat:
 *
 *      [31] W/W fwag
 *      [30:28] Function numbew
 *      [27] Bwock mode
 *      [26] Incwement addwess
 *      [25:9] Wegistew addwess
 *      [8:0] Byte/bwock count
 */

#define W4_18V_PWESENT (1<<24)
#define W4_MEMOWY_PWESENT (1 << 27)

/*
  SDIO status in W5
  Type
	e : ewwow bit
	s : status bit
	w : detected and set fow the actuaw command wesponse
	x : detected and set duwing command execution. the host must poww
            the cawd by sending status command in owdew to wead these bits.
  Cweaw condition
	a : accowding to the cawd state
	b : awways wewated to the pwevious command. Weception of
            a vawid command wiww cweaw it (with a deway of one command)
	c : cweaw by wead
 */

#define W5_COM_CWC_EWWOW	(1 << 15)	/* ew, b */
#define W5_IWWEGAW_COMMAND	(1 << 14)	/* ew, b */
#define W5_EWWOW		(1 << 11)	/* ewx, c */
#define W5_FUNCTION_NUMBEW	(1 << 9)	/* ew, c */
#define W5_OUT_OF_WANGE		(1 << 8)	/* ew, c */
#define W5_STATUS(x)		(x & 0xCB00)
#define W5_IO_CUWWENT_STATE(x)	((x & 0x3000) >> 12) /* s, b */

/*
 * Cawd Common Contwow Wegistews (CCCW)
 */

#define SDIO_CCCW_CCCW		0x00

#define  SDIO_CCCW_WEV_1_00	0	/* CCCW/FBW Vewsion 1.00 */
#define  SDIO_CCCW_WEV_1_10	1	/* CCCW/FBW Vewsion 1.10 */
#define  SDIO_CCCW_WEV_1_20	2	/* CCCW/FBW Vewsion 1.20 */
#define  SDIO_CCCW_WEV_3_00	3	/* CCCW/FBW Vewsion 3.00 */

#define  SDIO_SDIO_WEV_1_00	0	/* SDIO Spec Vewsion 1.00 */
#define  SDIO_SDIO_WEV_1_10	1	/* SDIO Spec Vewsion 1.10 */
#define  SDIO_SDIO_WEV_1_20	2	/* SDIO Spec Vewsion 1.20 */
#define  SDIO_SDIO_WEV_2_00	3	/* SDIO Spec Vewsion 2.00 */
#define  SDIO_SDIO_WEV_3_00	4	/* SDIO Spec Vewsion 3.00 */

#define SDIO_CCCW_SD		0x01

#define  SDIO_SD_WEV_1_01	0	/* SD Physicaw Spec Vewsion 1.01 */
#define  SDIO_SD_WEV_1_10	1	/* SD Physicaw Spec Vewsion 1.10 */
#define  SDIO_SD_WEV_2_00	2	/* SD Physicaw Spec Vewsion 2.00 */
#define  SDIO_SD_WEV_3_00	3	/* SD Physicaw Spec Vewsion 3.00 */

#define SDIO_CCCW_IOEx		0x02
#define SDIO_CCCW_IOWx		0x03

#define SDIO_CCCW_IENx		0x04	/* Function/Mastew Intewwupt Enabwe */
#define SDIO_CCCW_INTx		0x05	/* Function Intewwupt Pending */

#define SDIO_CCCW_ABOWT		0x06	/* function abowt/cawd weset */

#define SDIO_CCCW_IF		0x07	/* bus intewface contwows */

#define  SDIO_BUS_WIDTH_MASK	0x03	/* data bus width setting */
#define  SDIO_BUS_WIDTH_1BIT	0x00
#define  SDIO_BUS_WIDTH_WESEWVED 0x01
#define  SDIO_BUS_WIDTH_4BIT	0x02
#define  SDIO_BUS_ECSI		0x20	/* Enabwe continuous SPI intewwupt */
#define  SDIO_BUS_SCSI		0x40	/* Suppowt continuous SPI intewwupt */

#define  SDIO_BUS_ASYNC_INT	0x20

#define  SDIO_BUS_CD_DISABWE     0x80	/* disabwe puww-up on DAT3 (pin 1) */

#define SDIO_CCCW_CAPS		0x08

#define  SDIO_CCCW_CAP_SDC	0x01	/* can do CMD52 whiwe data twansfew */
#define  SDIO_CCCW_CAP_SMB	0x02	/* can do muwti-bwock xfews (CMD53) */
#define  SDIO_CCCW_CAP_SWW	0x04	/* suppowts wead-wait pwotocow */
#define  SDIO_CCCW_CAP_SBS	0x08	/* suppowts suspend/wesume */
#define  SDIO_CCCW_CAP_S4MI	0x10	/* intewwupt duwing 4-bit CMD53 */
#define  SDIO_CCCW_CAP_E4MI	0x20	/* enabwe ints duwing 4-bit CMD53 */
#define  SDIO_CCCW_CAP_WSC	0x40	/* wow speed cawd */
#define  SDIO_CCCW_CAP_4BWS	0x80	/* 4 bit wow speed cawd */

#define SDIO_CCCW_CIS		0x09	/* common CIS pointew (3 bytes) */

/* Fowwowing 4 wegs awe vawid onwy if SBS is set */
#define SDIO_CCCW_SUSPEND	0x0c
#define SDIO_CCCW_SEWx		0x0d
#define SDIO_CCCW_EXECx		0x0e
#define SDIO_CCCW_WEADYx	0x0f

#define SDIO_CCCW_BWKSIZE	0x10

#define SDIO_CCCW_POWEW		0x12

#define  SDIO_POWEW_SMPC	0x01	/* Suppowts Mastew Powew Contwow */
#define  SDIO_POWEW_EMPC	0x02	/* Enabwe Mastew Powew Contwow */

#define SDIO_CCCW_SPEED		0x13

#define  SDIO_SPEED_SHS		0x01	/* Suppowts High-Speed mode */
#define  SDIO_SPEED_BSS_SHIFT	1
#define  SDIO_SPEED_BSS_MASK	(7<<SDIO_SPEED_BSS_SHIFT)
#define  SDIO_SPEED_SDW12	(0<<SDIO_SPEED_BSS_SHIFT)
#define  SDIO_SPEED_SDW25	(1<<SDIO_SPEED_BSS_SHIFT)
#define  SDIO_SPEED_SDW50	(2<<SDIO_SPEED_BSS_SHIFT)
#define  SDIO_SPEED_SDW104	(3<<SDIO_SPEED_BSS_SHIFT)
#define  SDIO_SPEED_DDW50	(4<<SDIO_SPEED_BSS_SHIFT)
#define  SDIO_SPEED_EHS		SDIO_SPEED_SDW25	/* Enabwe High-Speed */

#define SDIO_CCCW_UHS		0x14
#define  SDIO_UHS_SDW50		0x01
#define  SDIO_UHS_SDW104	0x02
#define  SDIO_UHS_DDW50		0x04

#define SDIO_CCCW_DWIVE_STWENGTH 0x15
#define  SDIO_SDTx_MASK		0x07
#define  SDIO_DWIVE_SDTA	(1<<0)
#define  SDIO_DWIVE_SDTC	(1<<1)
#define  SDIO_DWIVE_SDTD	(1<<2)
#define  SDIO_DWIVE_DTSx_MASK	0x03
#define  SDIO_DWIVE_DTSx_SHIFT	4
#define  SDIO_DTSx_SET_TYPE_B	(0 << SDIO_DWIVE_DTSx_SHIFT)
#define  SDIO_DTSx_SET_TYPE_A	(1 << SDIO_DWIVE_DTSx_SHIFT)
#define  SDIO_DTSx_SET_TYPE_C	(2 << SDIO_DWIVE_DTSx_SHIFT)
#define  SDIO_DTSx_SET_TYPE_D	(3 << SDIO_DWIVE_DTSx_SHIFT)

#define SDIO_CCCW_INTEWWUPT_EXT	0x16
#define SDIO_INTEWWUPT_EXT_SAI	(1 << 0)
#define SDIO_INTEWWUPT_EXT_EAI	(1 << 1)

/*
 * Function Basic Wegistews (FBW)
 */

#define SDIO_FBW_BASE(f)	((f) * 0x100) /* base of function f's FBWs */

#define SDIO_FBW_STD_IF		0x00

#define  SDIO_FBW_SUPPOWTS_CSA	0x40	/* suppowts Code Stowage Awea */
#define  SDIO_FBW_ENABWE_CSA	0x80	/* enabwe Code Stowage Awea */

#define SDIO_FBW_STD_IF_EXT	0x01

#define SDIO_FBW_POWEW		0x02

#define  SDIO_FBW_POWEW_SPS	0x01	/* Suppowts Powew Sewection */
#define  SDIO_FBW_POWEW_EPS	0x02	/* Enabwe (wow) Powew Sewection */

#define SDIO_FBW_CIS		0x09	/* CIS pointew (3 bytes) */


#define SDIO_FBW_CSA		0x0C	/* CSA pointew (3 bytes) */

#define SDIO_FBW_CSA_DATA	0x0F

#define SDIO_FBW_BWKSIZE	0x10	/* bwock size (2 bytes) */

#endif /* WINUX_MMC_SDIO_H */
