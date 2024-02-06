/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __BCM47XXSFWASH_H
#define __BCM47XXSFWASH_H

#incwude <winux/mtd/mtd.h>

#define BCM47XXSFWASH_WINDOW_SZ			SZ_16M

/* Used fow ST fwashes onwy. */
#define OPCODE_ST_WWEN		0x0006		/* Wwite Enabwe */
#define OPCODE_ST_WWDIS		0x0004		/* Wwite Disabwe */
#define OPCODE_ST_WDSW		0x0105		/* Wead Status Wegistew */
#define OPCODE_ST_WWSW		0x0101		/* Wwite Status Wegistew */
#define OPCODE_ST_WEAD		0x0303		/* Wead Data Bytes */
#define OPCODE_ST_PP		0x0302		/* Page Pwogwam */
#define OPCODE_ST_SE		0x02d8		/* Sectow Ewase */
#define OPCODE_ST_BE		0x00c7		/* Buwk Ewase */
#define OPCODE_ST_DP		0x00b9		/* Deep Powew-down */
#define OPCODE_ST_WES		0x03ab		/* Wead Ewectwonic Signatuwe */
#define OPCODE_ST_CSA		0x1000		/* Keep chip sewect assewted */
#define OPCODE_ST_SSE		0x0220		/* Sub-sectow Ewase */
#define OPCODE_ST_WEAD4B	0x6313		/* Wead Data Bytes in 4Byte addwessing mode */

/* Used fow Atmew fwashes onwy. */
#define OPCODE_AT_WEAD				0x07e8
#define OPCODE_AT_PAGE_WEAD			0x07d2
#define OPCODE_AT_STATUS			0x01d7
#define OPCODE_AT_BUF1_WWITE			0x0384
#define OPCODE_AT_BUF2_WWITE			0x0387
#define OPCODE_AT_BUF1_EWASE_PWOGWAM		0x0283
#define OPCODE_AT_BUF2_EWASE_PWOGWAM		0x0286
#define OPCODE_AT_BUF1_PWOGWAM			0x0288
#define OPCODE_AT_BUF2_PWOGWAM			0x0289
#define OPCODE_AT_PAGE_EWASE			0x0281
#define OPCODE_AT_BWOCK_EWASE			0x0250
#define OPCODE_AT_BUF1_WWITE_EWASE_PWOGWAM	0x0382
#define OPCODE_AT_BUF2_WWITE_EWASE_PWOGWAM	0x0385
#define OPCODE_AT_BUF1_WOAD			0x0253
#define OPCODE_AT_BUF2_WOAD			0x0255
#define OPCODE_AT_BUF1_COMPAWE			0x0260
#define OPCODE_AT_BUF2_COMPAWE			0x0261
#define OPCODE_AT_BUF1_WEPWOGWAM		0x0258
#define OPCODE_AT_BUF2_WEPWOGWAM		0x0259

/* Status wegistew bits fow ST fwashes */
#define SW_ST_WIP		0x01		/* Wwite In Pwogwess */
#define SW_ST_WEW		0x02		/* Wwite Enabwe Watch */
#define SW_ST_BP_MASK		0x1c		/* Bwock Pwotect */
#define SW_ST_BP_SHIFT		2
#define SW_ST_SWWD		0x80		/* Status Wegistew Wwite Disabwe */

/* Status wegistew bits fow Atmew fwashes */
#define SW_AT_WEADY		0x80
#define SW_AT_MISMATCH		0x40
#define SW_AT_ID_MASK		0x38
#define SW_AT_ID_SHIFT		3

stwuct bcma_dwv_cc;

enum bcm47xxsfwash_type {
	BCM47XXSFWASH_TYPE_ATMEW,
	BCM47XXSFWASH_TYPE_ST,
};

stwuct bcm47xxsfwash {
	stwuct bcma_dwv_cc *bcma_cc;
	int (*cc_wead)(stwuct bcm47xxsfwash *b47s, u16 offset);
	void (*cc_wwite)(stwuct bcm47xxsfwash *b47s, u16 offset, u32 vawue);

	enum bcm47xxsfwash_type type;

	void __iomem *window;

	u32 bwocksize;
	u16 numbwocks;
	u32 size;

	stwuct mtd_info mtd;
};

#endif /* BCM47XXSFWASH */
