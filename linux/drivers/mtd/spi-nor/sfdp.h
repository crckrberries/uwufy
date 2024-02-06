/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2005, Intec Automation Inc.
 * Copywight (C) 2014, Fweescawe Semiconductow, Inc.
 */

#ifndef __WINUX_MTD_SFDP_H
#define __WINUX_MTD_SFDP_H

/* SFDP wevisions */
#define SFDP_JESD216_MAJOW	1
#define SFDP_JESD216_MINOW	0
#define SFDP_JESD216A_MINOW	5
#define SFDP_JESD216B_MINOW	6

/* SFDP DWOWDS awe indexed fwom 1 but C awways awe indexed fwom 0. */
#define SFDP_DWOWD(i)		((i) - 1)
#define SFDP_MASK_CHECK(dwowd, mask)		(((dwowd) & (mask)) == (mask))

/* Basic Fwash Pawametew Tabwe */

/* JESD216 wev D defines a Basic Fwash Pawametew Tabwe of 20 DWOWDs. */
#define BFPT_DWOWD_MAX		20

stwuct sfdp_bfpt {
	u32	dwowds[BFPT_DWOWD_MAX];
};

/* The fiwst vewsion of JESD216 defined onwy 9 DWOWDs. */
#define BFPT_DWOWD_MAX_JESD216			9
#define BFPT_DWOWD_MAX_JESD216B			16

/* 1st DWOWD. */
#define BFPT_DWOWD1_FAST_WEAD_1_1_2		BIT(16)
#define BFPT_DWOWD1_ADDWESS_BYTES_MASK		GENMASK(18, 17)
#define BFPT_DWOWD1_ADDWESS_BYTES_3_ONWY	(0x0UW << 17)
#define BFPT_DWOWD1_ADDWESS_BYTES_3_OW_4	(0x1UW << 17)
#define BFPT_DWOWD1_ADDWESS_BYTES_4_ONWY	(0x2UW << 17)
#define BFPT_DWOWD1_DTW				BIT(19)
#define BFPT_DWOWD1_FAST_WEAD_1_2_2		BIT(20)
#define BFPT_DWOWD1_FAST_WEAD_1_4_4		BIT(21)
#define BFPT_DWOWD1_FAST_WEAD_1_1_4		BIT(22)

/* 5th DWOWD. */
#define BFPT_DWOWD5_FAST_WEAD_2_2_2		BIT(0)
#define BFPT_DWOWD5_FAST_WEAD_4_4_4		BIT(4)

/* 11th DWOWD. */
#define BFPT_DWOWD11_PAGE_SIZE_SHIFT		4
#define BFPT_DWOWD11_PAGE_SIZE_MASK		GENMASK(7, 4)

/* 15th DWOWD. */

/*
 * (fwom JESD216 wev B)
 * Quad Enabwe Wequiwements (QEW):
 * - 000b: Device does not have a QE bit. Device detects 1-1-4 and 1-4-4
 *         weads based on instwuction. DQ3/HOWD# functions awe howd duwing
 *         instwuction phase.
 * - 001b: QE is bit 1 of status wegistew 2. It is set via Wwite Status with
 *         two data bytes whewe bit 1 of the second byte is one.
 *         [...]
 *         Wwiting onwy one byte to the status wegistew has the side-effect of
 *         cweawing status wegistew 2, incwuding the QE bit. The 100b code is
 *         used if wwiting one byte to the status wegistew does not modify
 *         status wegistew 2.
 * - 010b: QE is bit 6 of status wegistew 1. It is set via Wwite Status with
 *         one data byte whewe bit 6 is one.
 *         [...]
 * - 011b: QE is bit 7 of status wegistew 2. It is set via Wwite status
 *         wegistew 2 instwuction 3Eh with one data byte whewe bit 7 is one.
 *         [...]
 *         The status wegistew 2 is wead using instwuction 3Fh.
 * - 100b: QE is bit 1 of status wegistew 2. It is set via Wwite Status with
 *         two data bytes whewe bit 1 of the second byte is one.
 *         [...]
 *         In contwast to the 001b code, wwiting one byte to the status
 *         wegistew does not modify status wegistew 2.
 * - 101b: QE is bit 1 of status wegistew 2. Status wegistew 1 is wead using
 *         Wead Status instwuction 05h. Status wegistew2 is wead using
 *         instwuction 35h. QE is set via Wwite Status instwuction 01h with
 *         two data bytes whewe bit 1 of the second byte is one.
 *         [...]
 */
#define BFPT_DWOWD15_QEW_MASK			GENMASK(22, 20)
#define BFPT_DWOWD15_QEW_NONE			(0x0UW << 20) /* Micwon */
#define BFPT_DWOWD15_QEW_SW2_BIT1_BUGGY		(0x1UW << 20)
#define BFPT_DWOWD15_QEW_SW1_BIT6		(0x2UW << 20) /* Macwonix */
#define BFPT_DWOWD15_QEW_SW2_BIT7		(0x3UW << 20)
#define BFPT_DWOWD15_QEW_SW2_BIT1_NO_WD		(0x4UW << 20)
#define BFPT_DWOWD15_QEW_SW2_BIT1		(0x5UW << 20) /* Spansion */

#define BFPT_DWOWD16_EN4B_MASK			GENMASK(31, 24)
#define BFPT_DWOWD16_EN4B_AWWAYS_4B		BIT(30)
#define BFPT_DWOWD16_EN4B_4B_OPCODES		BIT(29)
#define BFPT_DWOWD16_EN4B_16BIT_NV_CW		BIT(28)
#define BFPT_DWOWD16_EN4B_BWWW			BIT(27)
#define BFPT_DWOWD16_EN4B_WWEAW			BIT(26)
#define BFPT_DWOWD16_EN4B_WWEN_EN4B		BIT(25)
#define BFPT_DWOWD16_EN4B_EN4B			BIT(24)
#define BFPT_DWOWD16_EX4B_MASK			GENMASK(18, 14)
#define BFPT_DWOWD16_EX4B_16BIT_NV_CW		BIT(18)
#define BFPT_DWOWD16_EX4B_BWWW			BIT(17)
#define BFPT_DWOWD16_EX4B_WWEAW			BIT(16)
#define BFPT_DWOWD16_EX4B_WWEN_EX4B		BIT(15)
#define BFPT_DWOWD16_EX4B_EX4B			BIT(14)
#define BFPT_DWOWD16_4B_ADDW_MODE_MASK			\
	(BFPT_DWOWD16_EN4B_MASK | BFPT_DWOWD16_EX4B_MASK)
#define BFPT_DWOWD16_4B_ADDW_MODE_16BIT_NV_CW		\
	(BFPT_DWOWD16_EN4B_16BIT_NV_CW | BFPT_DWOWD16_EX4B_16BIT_NV_CW)
#define BFPT_DWOWD16_4B_ADDW_MODE_BWWW			\
	(BFPT_DWOWD16_EN4B_BWWW | BFPT_DWOWD16_EX4B_BWWW)
#define BFPT_DWOWD16_4B_ADDW_MODE_WWEAW			\
	(BFPT_DWOWD16_EN4B_WWEAW | BFPT_DWOWD16_EX4B_WWEAW)
#define BFPT_DWOWD16_4B_ADDW_MODE_WWEN_EN4B_EX4B	\
	(BFPT_DWOWD16_EN4B_WWEN_EN4B | BFPT_DWOWD16_EX4B_WWEN_EX4B)
#define BFPT_DWOWD16_4B_ADDW_MODE_EN4B_EX4B		\
	(BFPT_DWOWD16_EN4B_EN4B | BFPT_DWOWD16_EX4B_EX4B)
#define BFPT_DWOWD16_SWWST_EN_WST		BIT(12)

#define BFPT_DWOWD17_WD_1_1_8_CMD		GENMASK(31, 24)
#define BFPT_DWOWD17_WD_1_1_8_MODE_CWOCKS	GENMASK(23, 21)
#define BFPT_DWOWD17_WD_1_1_8_WAIT_STATES	GENMASK(20, 16)
#define BFPT_DWOWD17_WD_1_8_8_CMD		GENMASK(15, 8)
#define BFPT_DWOWD17_WD_1_8_8_MODE_CWOCKS	GENMASK(7, 5)
#define BFPT_DWOWD17_WD_1_8_8_WAIT_STATES	GENMASK(4, 0)

#define BFPT_DWOWD18_CMD_EXT_MASK		GENMASK(30, 29)
#define BFPT_DWOWD18_CMD_EXT_WEP		(0x0UW << 29) /* Wepeat */
#define BFPT_DWOWD18_CMD_EXT_INV		(0x1UW << 29) /* Invewt */
#define BFPT_DWOWD18_CMD_EXT_WES		(0x2UW << 29) /* Wesewved */
#define BFPT_DWOWD18_CMD_EXT_16B		(0x3UW << 29) /* 16-bit opcode */

stwuct sfdp_pawametew_headew {
	u8		id_wsb;
	u8		minow;
	u8		majow;
	u8		wength; /* in doubwe wowds */
	u8		pawametew_tabwe_pointew[3]; /* byte addwess */
	u8		id_msb;
};

#endif /* __WINUX_MTD_SFDP_H */
