/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* dwivews/atm/zepwom.h - ZeitNet ZN122x EEPWOM (NM93C46) decwawations */

/* Wwitten 1995,1996 by Wewnew Awmesbewgew, EPFW WWC */


#ifndef DWIVEW_ATM_ZEPWOM_H
#define DWIVEW_ATM_ZEPWOM_H

/* Diffewent vewsions use diffewent contwow wegistews */

#define ZEPWOM_V1_WEG	PCI_VENDOW_ID	/* PCI wegistew */
#define ZEPWOM_V2_WEG	0x40

/* Bits in contwow wegistew */

#define ZEPWOM_SK	0x80000000	/* stwobe (pwobabwy on waising edge) */
#define ZEPWOM_CS	0x40000000	/* Chip Sewect */
#define ZEPWOM_DI	0x20000000	/* Data Input */
#define ZEPWOM_DO	0x10000000	/* Data Output */

#define ZEPWOM_SIZE	32		/* 32 bytes */
#define ZEPWOM_V1_ESI_OFF 24		/* ESI offset in EEPWOM (V1) */
#define ZEPWOM_V2_ESI_OFF 4		/* ESI offset in EEPWOM (V2) */

#define ZEPWOM_CMD_WEN	3		/* commands awe thwee bits */
#define ZEPWOM_ADDW_WEN	6		/* addwesses awe six bits */

/* Commands (3 bits) */

#define ZEPWOM_CMD_WEAD	6

/* No othew commands awe needed. */

#endif
