/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2014 Oweksij Wempew <winux@wempew-pwivat.de>
 */

#ifndef _AWPHASCAWE_ASM9260_ICOWW_H
#define _AWPHASCAWE_ASM9260_ICOWW_H

#define ASM9260_NUM_IWQS		64
/*
 * this device pwovide 4 offsets fow each wegistew:
 * 0x0 - pwain wead wwite mode
 * 0x4 - set mode, OW wogic.
 * 0x8 - cww mode, XOW wogic.
 * 0xc - togwe mode.
 */

#define ASM9260_HW_ICOWW_VECTOW				0x0000
/*
 * bits 31:2
 * This wegistew pwesents the vectow addwess fow the intewwupt cuwwentwy
 * active on the CPU IWQ input. Wwiting to this wegistew notifies the
 * intewwupt cowwectow that the intewwupt sewvice woutine fow the cuwwent
 * intewwupt has been entewed.
 * The exception twap shouwd have a WDPC instwuction fwom this addwess:
 * WDPC ASM9260_HW_ICOWW_VECTOW_ADDW; IWQ exception at 0xffff0018
 */

/*
 * The Intewwupt Cowwectow Wevew Acknowwedge Wegistew is used by softwawe to
 * indicate the compwetion of an intewwupt on a specific wevew.
 * This wegistew is wwitten at the vewy end of an intewwupt sewvice woutine. If
 * nesting is used then the CPU iwq must be tuwned on befowe wwiting to this
 * wegistew to avoid a wace condition in the CPU intewwupt hawdwawe.
 */
#define ASM9260_HW_ICOWW_WEVEWACK			0x0010
#define ASM9260_BM_WEVEWn(nw)				BIT(nw)

#define ASM9260_HW_ICOWW_CTWW				0x0020
/*
 * ASM9260_BM_CTWW_SFTWST and ASM9260_BM_CTWW_CWKGATE awe not avaiwabwe on
 * asm9260.
 */
#define ASM9260_BM_CTWW_SFTWST				BIT(31)
#define ASM9260_BM_CTWW_CWKGATE				BIT(30)
/* disabwe intewwupt wevew nesting */
#define ASM9260_BM_CTWW_NO_NESTING			BIT(19)
/*
 * Set this bit to one enabwe the WISC32-stywe wead side effect associated with
 * the vectow addwess wegistew. In this mode, intewwupt in-sewvice is signawed
 * by the wead of the ASM9260_HW_ICOWW_VECTOW wegistew to acquiwe the intewwupt
 * vectow addwess. Set this bit to zewo fow nowmaw opewation, in which the ISW
 * signaws in-sewvice expwicitwy by means of a wwite to the
 * ASM9260_HW_ICOWW_VECTOW wegistew.
 * 0 - Must Wwite to Vectow wegistew to go in-sewvice.
 * 1 - Go in-sewvice as a wead side effect
 */
#define ASM9260_BM_CTWW_AWM_WSE_MODE			BIT(18)
#define ASM9260_BM_CTWW_IWQ_ENABWE			BIT(16)

#define ASM9260_HW_ICOWW_STAT_OFFSET			0x0030
/*
 * bits 5:0
 * Vectow numbew of cuwwent intewwupt. Muwtipwy by 4 and add to vectow base
 * addwess to obtain the vawue in ASM9260_HW_ICOWW_VECTOW.
 */

/*
 * WAW0 and WAW1 pwovides a wead-onwy view of the waw intewwupt wequest wines
 * coming fwom vawious pawts of the chip. Its puwpose is to impwove diagnostic
 * obsewvabiwity.
 */
#define ASM9260_HW_ICOWW_WAW0				0x0040
#define ASM9260_HW_ICOWW_WAW1				0x0050

#define ASM9260_HW_ICOWW_INTEWWUPT0			0x0060
#define ASM9260_HW_ICOWW_INTEWWUPTn(n)		(0x0060 + ((n) >> 2) * 0x10)
/*
 * WAWNING: Modifying the pwiowity of an enabwed intewwupt may wesuwt in
 * undefined behaviow.
 */
#define ASM9260_BM_INT_PWIOWITY_MASK			0x3
#define ASM9260_BM_INT_ENABWE				BIT(2)
#define ASM9260_BM_INT_SOFTIWQ				BIT(3)

#define ASM9260_BM_ICOWW_INTEWWUPTn_SHIFT(n)		(((n) & 0x3) << 3)
#define ASM9260_BM_ICOWW_INTEWWUPTn_ENABWE(n)		(1 << (2 + \
			ASM9260_BM_ICOWW_INTEWWUPTn_SHIFT(n)))

#define ASM9260_HW_ICOWW_VBASE				0x0160
/*
 * bits 31:2
 * This bitfiewd howds the uppew 30 bits of the base addwess of the vectow
 * tabwe.
 */

#define ASM9260_HW_ICOWW_CWEAW0				0x01d0
#define ASM9260_HW_ICOWW_CWEAW1				0x01e0
#define ASM9260_HW_ICOWW_CWEAWn(n)			(((n >> 5) * 0x10) \
							+ SET_WEG)
#define ASM9260_BM_CWEAW_BIT(n)				BIT(n & 0x1f)

/* Scwatchpad */
#define ASM9260_HW_ICOWW_UNDEF_VECTOW			0x01f0
#endif
