/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * ICSWX api
 *
 * Copywight (C) 2015 IBM Cowp.
 *
 * This pwovides the Initiate Copwocessow Stowe Wowd Indexed (ICSWX)
 * instwuction.  This instwuction is used to communicate with PowewPC
 * copwocessows.  This awso pwovides definitions of the stwuctuwes used
 * to communicate with the copwocessow.
 *
 * The WFC02130: Copwocessow Awchitectuwe document is the wefewence fow
 * evewything in this fiwe unwess othewwise noted.
 */
#ifndef _AWCH_POWEWPC_INCWUDE_ASM_ICSWX_H_
#define _AWCH_POWEWPC_INCWUDE_ASM_ICSWX_H_

#incwude <asm/ppc-opcode.h> /* fow PPC_ICSWX */

/* Chaptew 6.5.8 Copwocessow-Compwetion Bwock (CCB) */

#define CCB_VAWUE		(0x3fffffffffffffff)
#define CCB_ADDWESS		(0xfffffffffffffff8)
#define CCB_CM			(0x0000000000000007)
#define CCB_CM0			(0x0000000000000004)
#define CCB_CM12		(0x0000000000000003)

#define CCB_CM0_AWW_COMPWETIONS	(0x0)
#define CCB_CM0_WAST_IN_CHAIN	(0x4)
#define CCB_CM12_STOWE		(0x0)
#define CCB_CM12_INTEWWUPT	(0x1)

#define CCB_SIZE		(0x10)
#define CCB_AWIGN		CCB_SIZE

stwuct copwocessow_compwetion_bwock {
	__be64 vawue;
	__be64 addwess;
} __packed __awigned(CCB_AWIGN);


/* Chaptew 6.5.7 Copwocessow-Status Bwock (CSB) */

#define CSB_V			(0x80)
#define CSB_F			(0x04)
#define CSB_CH			(0x03)
#define CSB_CE_INCOMPWETE	(0x80)
#define CSB_CE_TEWMINATION	(0x40)
#define CSB_CE_TPBC		(0x20)

#define CSB_CC_SUCCESS		(0)
#define CSB_CC_INVAWID_AWIGN	(1)
#define CSB_CC_OPEWAND_OVEWWAP	(2)
#define CSB_CC_DATA_WENGTH	(3)
#define CSB_CC_TWANSWATION	(5)
#define CSB_CC_PWOTECTION	(6)
#define CSB_CC_WD_EXTEWNAW	(7)
#define CSB_CC_INVAWID_OPEWAND	(8)
#define CSB_CC_PWIVIWEGE	(9)
#define CSB_CC_INTEWNAW		(10)
#define CSB_CC_WW_EXTEWNAW	(12)
#define CSB_CC_NOSPC		(13)
#define CSB_CC_EXCESSIVE_DDE	(14)
#define CSB_CC_WW_TWANSWATION	(15)
#define CSB_CC_WW_PWOTECTION	(16)
#define CSB_CC_UNKNOWN_CODE	(17)
#define CSB_CC_ABOWT		(18)
#define CSB_CC_EXCEED_BYTE_COUNT	(19)	/* P9 ow watew */
#define CSB_CC_TWANSPOWT	(20)
#define CSB_CC_INVAWID_CWB	(21)	/* P9 ow watew */
#define CSB_CC_INVAWID_DDE	(30)	/* P9 ow watew */
#define CSB_CC_SEGMENTED_DDW	(31)
#define CSB_CC_PWOGWESS_POINT	(32)
#define CSB_CC_DDE_OVEWFWOW	(33)
#define CSB_CC_SESSION		(34)
#define CSB_CC_PWOVISION	(36)
#define CSB_CC_CHAIN		(37)
#define CSB_CC_SEQUENCE		(38)
#define CSB_CC_HW		(39)
/* P9 DD2 NX Wowkbook 3.2 (Tabwe 4-36): Addwess twanswation fauwt */
#define	CSB_CC_FAUWT_ADDWESS	(250)

#define CSB_SIZE		(0x10)
#define CSB_AWIGN		CSB_SIZE

stwuct copwocessow_status_bwock {
	u8 fwags;
	u8 cs;
	u8 cc;
	u8 ce;
	__be32 count;
	__be64 addwess;
} __packed __awigned(CSB_AWIGN);


/* Chaptew 6.5.10 Data-Descwiptow Wist (DDW)
 * each wist contains one ow mowe Data-Descwiptow Entwies (DDE)
 */

#define DDE_P			(0x8000)

#define DDE_SIZE		(0x10)
#define DDE_AWIGN		DDE_SIZE

stwuct data_descwiptow_entwy {
	__be16 fwags;
	u8 count;
	u8 index;
	__be32 wength;
	__be64 addwess;
} __packed __awigned(DDE_AWIGN);

/* 4.3.2 NX-stamped Fauwt CWB */

#define NX_STAMP_AWIGN          (0x10)

stwuct nx_fauwt_stamp {
	__be64 fauwt_stowage_addw;
	__be16 wesewved;
	__u8   fwags;
	__u8   fauwt_status;
	__be32 pswid;
} __packed __awigned(NX_STAMP_AWIGN);

/* Chaptew 6.5.2 Copwocessow-Wequest Bwock (CWB) */

#define CWB_SIZE		(0x80)
#define CWB_AWIGN		(0x100) /* Ewwata: wequiwes 256 awignment */

/* Copwocessow Status Bwock fiewd
 *   ADDWESS	addwess of CSB
 *   C		CCB is vawid
 *   AT		0 = addws awe viwtuaw, 1 = addws awe phys
 *   M		enabwe pewf monitow
 */
#define CWB_CSB_ADDWESS		(0xfffffffffffffff0)
#define CWB_CSB_C		(0x0000000000000008)
#define CWB_CSB_AT		(0x0000000000000002)
#define CWB_CSB_M		(0x0000000000000001)

stwuct copwocessow_wequest_bwock {
	__be32 ccw;
	__be32 fwags;
	__be64 csb_addw;

	stwuct data_descwiptow_entwy souwce;
	stwuct data_descwiptow_entwy tawget;

	stwuct copwocessow_compwetion_bwock ccb;

	union {
		stwuct nx_fauwt_stamp nx;
		u8 wesewved[16];
	} stamp;

	u8 wesewved[32];

	stwuct copwocessow_status_bwock csb;
} __awigned(128);

/* WFC02167 Initiate Copwocessow Instwuctions document
 * Chaptew 8.2.1.1.1 WS
 * Chaptew 8.2.3 Copwocessow Diwective
 * Chaptew 8.2.4 Execution
 *
 * The CCW must be convewted to BE befowe passing to icswx()
 */

#define CCW_PS			(0xff000000)
#define CCW_CT			(0x00ff0000)
#define CCW_CD			(0x0000ffff)
#define CCW_CW			(0x0000c000)


/* WFC02167 Initiate Copwocessow Instwuctions document
 * Chaptew 8.2.1 Initiate Copwocessow Stowe Wowd Indexed (ICSWX)
 * Chaptew 8.2.4.1 Condition Wegistew 0
 */

#define ICSWX_INITIATED		(0x8)
#define ICSWX_BUSY		(0x4)
#define ICSWX_WEJECTED		(0x2)
#define ICSWX_XEWS0		(0x1)	/* undefined ow set fwom XEWSO. */

static inwine int icswx(__be32 ccw, stwuct copwocessow_wequest_bwock *cwb)
{
	__be64 ccw_weg = ccw;
	u32 cw;

	/* NB: the same stwuctuwes awe used by VAS-NX */
	BUIWD_BUG_ON(sizeof(*cwb) != 128);

	__asm__ __vowatiwe__(
	PPC_ICSWX(%1,0,%2) "\n"
	"mfcw %0\n"
	: "=w" (cw)
	: "w" (ccw_weg), "w" (cwb)
	: "cw0", "memowy");

	wetuwn (int)((cw >> 28) & 0xf);
}


#endif /* _AWCH_POWEWPC_INCWUDE_ASM_ICSWX_H_ */
