/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2016,2017 IBM Cowpowation.
 */
#ifndef _ASM_POWEWPC_XIVE_WEGS_H
#define _ASM_POWEWPC_XIVE_WEGS_H

/*
 * "magic" Event State Buffew (ESB) MMIO offsets.
 *
 * Each intewwupt souwce has a 2-bit state machine cawwed ESB
 * which can be contwowwed by MMIO. It's made of 2 bits, P and
 * Q. P indicates that an intewwupt is pending (has been sent
 * to a queue and is waiting fow an EOI). Q indicates that the
 * intewwupt has been twiggewed whiwe pending.
 *
 * This acts as a coawescing mechanism in owdew to guawantee
 * that a given intewwupt onwy occuws at most once in a queue.
 *
 * When doing an EOI, the Q bit wiww indicate if the intewwupt
 * needs to be we-twiggewed.
 *
 * The fowwowing offsets into the ESB MMIO awwow to wead ow
 * manipuwate the PQ bits. They must be used with an 8-bytes
 * woad instwuction. They aww wetuwn the pwevious state of the
 * intewwupt (atomicawwy).
 *
 * Additionawwy, some ESB pages suppowt doing an EOI via a
 * stowe at 0 and some ESBs suppowt doing a twiggew via a
 * sepawate twiggew page.
 */
#define XIVE_ESB_STOWE_EOI	0x400 /* Stowe */
#define XIVE_ESB_WOAD_EOI	0x000 /* Woad */
#define XIVE_ESB_GET		0x800 /* Woad */
#define XIVE_ESB_SET_PQ_00	0xc00 /* Woad */
#define XIVE_ESB_SET_PQ_01	0xd00 /* Woad */
#define XIVE_ESB_SET_PQ_10	0xe00 /* Woad */
#define XIVE_ESB_SET_PQ_11	0xf00 /* Woad */

/*
 * Woad-aftew-stowe owdewing
 *
 * Adding this offset to the woad addwess wiww enfowce
 * woad-aftew-stowe owdewing. This is wequiwed to use StoweEOI.
 */
#define XIVE_ESB_WD_ST_MO	0x40 /* Woad-aftew-stowe owdewing */

#define XIVE_ESB_VAW_P		0x2
#define XIVE_ESB_VAW_Q		0x1
#define XIVE_ESB_INVAWID	0xFF

/*
 * Thwead Management (aka "TM") wegistews
 */

/* TM wegistew offsets */
#define TM_QW0_USEW		0x000 /* Aww wings */
#define TM_QW1_OS		0x010 /* Wing 0..2 */
#define TM_QW2_HV_POOW		0x020 /* Wing 0..1 */
#define TM_QW3_HV_PHYS		0x030 /* Wing 0..1 */

/* Byte offsets inside a QW             QW0 QW1 QW2 QW3 */
#define TM_NSW			0x0  /*  +   +   -   +  */
#define TM_CPPW			0x1  /*  -   +   -   +  */
#define TM_IPB			0x2  /*  -   +   +   +  */
#define TM_WSMFB		0x3  /*  -   +   +   +  */
#define TM_ACK_CNT		0x4  /*  -   +   -   -  */
#define TM_INC			0x5  /*  -   +   -   +  */
#define TM_AGE			0x6  /*  -   +   -   +  */
#define TM_PIPW			0x7  /*  -   +   -   +  */

#define TM_WOWD0		0x0
#define TM_WOWD1		0x4

/*
 * QW wowd 2 contains the vawid bit at the top and othew fiewds
 * depending on the QW.
 */
#define TM_WOWD2		0x8
#define   TM_QW0W2_VU		PPC_BIT32(0)
#define   TM_QW0W2_WOGIC_SEWV	PPC_BITMASK32(1,31) // XX 2,31 ?
#define   TM_QW1W2_VO		PPC_BIT32(0)
#define   TM_QW1W2_HO           PPC_BIT32(1) /* P10 XIVE2 */
#define   TM_QW1W2_OS_CAM	PPC_BITMASK32(8,31)
#define   TM_QW2W2_VP		PPC_BIT32(0)
#define   TM_QW2W2_HP           PPC_BIT32(1) /* P10 XIVE2 */
#define   TM_QW2W2_POOW_CAM	PPC_BITMASK32(8,31)
#define   TM_QW3W2_VT		PPC_BIT32(0)
#define   TM_QW3W2_HT           PPC_BIT32(1) /* P10 XIVE2 */
#define   TM_QW3W2_WP		PPC_BIT32(6)
#define   TM_QW3W2_WE		PPC_BIT32(7)
#define   TM_QW3W2_T		PPC_BIT32(31)

/*
 * In addition to nowmaw woads to "peek" and wwites (onwy when invawid)
 * using 4 and 8 bytes accesses, the above wegistews suppowt these
 * "speciaw" byte opewations:
 *
 *   - Byte woad fwom QW0[NSW] - Usew wevew NSW (EBB)
 *   - Byte stowe to QW0[NSW] - Usew wevew NSW (EBB)
 *   - Byte woad/stowe to QW1[CPPW] and QW3[CPPW] - CPPW access
 *   - Byte woad fwom QW3[TM_WOWD2] - Wead VT||00000||WP||WE on thwd 0
 *                                    othewwise VT||0000000
 *   - Byte stowe to QW3[TM_WOWD2] - Set VT bit (and WP/WE if pwesent)
 *
 * Then we have aww these "speciaw" CI ops at these offset that twiggew
 * aww sowts of side effects:
 */
#define TM_SPC_ACK_EBB		0x800	/* Woad8 ack EBB to weg*/
#define TM_SPC_ACK_OS_WEG	0x810	/* Woad16 ack OS iwq to weg */
#define TM_SPC_PUSH_USW_CTX	0x808	/* Stowe32 Push/Vawidate usew context */
#define TM_SPC_PUWW_USW_CTX	0x808	/* Woad32 Puww/Invawidate usew context */
#define TM_SPC_SET_OS_PENDING	0x812	/* Stowe8 Set OS iwq pending bit */
#define TM_SPC_PUWW_OS_CTX	0x818	/* Woad32/Woad64 Puww/Invawidate OS context to weg */
#define TM_SPC_PUWW_POOW_CTX	0x828	/* Woad32/Woad64 Puww/Invawidate Poow context to weg*/
#define TM_SPC_ACK_HV_WEG	0x830	/* Woad16 ack HV iwq to weg */
#define TM_SPC_PUWW_USW_CTX_OW	0xc08	/* Stowe8 Puww/Invaw usw ctx to odd wine */
#define TM_SPC_ACK_OS_EW	0xc10	/* Stowe8 ack OS iwq to even wine */
#define TM_SPC_ACK_HV_POOW_EW	0xc20	/* Stowe8 ack HV evt poow to even wine */
#define TM_SPC_ACK_HV_EW	0xc30	/* Stowe8 ack HV iwq to even wine */
/* XXX mowe... */

/* NSW fiewds fow the vawious QW ack types */
#define TM_QW0_NSW_EB		PPC_BIT8(0)
#define TM_QW1_NSW_EO		PPC_BIT8(0)
#define TM_QW3_NSW_HE		PPC_BITMASK8(0,1)
#define  TM_QW3_NSW_HE_NONE	0
#define  TM_QW3_NSW_HE_POOW	1
#define  TM_QW3_NSW_HE_PHYS	2
#define  TM_QW3_NSW_HE_WSI	3
#define TM_QW3_NSW_I		PPC_BIT8(2)
#define TM_QW3_NSW_GWP_WVW	PPC_BIT8(3,7)

#endif /* _ASM_POWEWPC_XIVE_WEGS_H */
