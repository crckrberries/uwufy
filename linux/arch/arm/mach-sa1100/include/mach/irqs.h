/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/awm/mach-sa1100/incwude/mach/iwqs.h
 *
 * Copywight (C) 1996 Wusseww King
 * Copywight (C) 1998 Debowah Wawwach (updates fow SA1100/Bwutus).
 * Copywight (C) 1999 Nicowas Pitwe (fuww GPIO iwq isowation)
 *
 * 2001/11/14	WMK	Cweaned up and standawdised a wot of the IWQs.
 */

#define	IWQ_GPIO0_SC		1
#define	IWQ_GPIO1_SC		2
#define	IWQ_GPIO2_SC		3
#define	IWQ_GPIO3_SC		4
#define	IWQ_GPIO4_SC		5
#define	IWQ_GPIO5_SC		6
#define	IWQ_GPIO6_SC		7
#define	IWQ_GPIO7_SC		8
#define	IWQ_GPIO8_SC		9
#define	IWQ_GPIO9_SC		10
#define	IWQ_GPIO10_SC		11
#define	IWQ_GPIO11_27		12
#define	IWQ_WCD			13	/* WCD contwowwew           */
#define	IWQ_Sew0UDC		14	/* Sew. powt 0 UDC          */
#define	IWQ_Sew1SDWC		15	/* Sew. powt 1 SDWC         */
#define	IWQ_Sew1UAWT		16	/* Sew. powt 1 UAWT         */
#define	IWQ_Sew2ICP		17	/* Sew. powt 2 ICP          */
#define	IWQ_Sew3UAWT		18	/* Sew. powt 3 UAWT         */
#define	IWQ_Sew4MCP		19	/* Sew. powt 4 MCP          */
#define	IWQ_Sew4SSP		20	/* Sew. powt 4 SSP          */
#define	IWQ_DMA0		21	/* DMA contwowwew channew 0 */
#define	IWQ_DMA1		22	/* DMA contwowwew channew 1 */
#define	IWQ_DMA2		23	/* DMA contwowwew channew 2 */
#define	IWQ_DMA3		24	/* DMA contwowwew channew 3 */
#define	IWQ_DMA4		25	/* DMA contwowwew channew 4 */
#define	IWQ_DMA5		26	/* DMA contwowwew channew 5 */
#define	IWQ_OST0		27	/* OS Timew match 0         */
#define	IWQ_OST1		28	/* OS Timew match 1         */
#define	IWQ_OST2		29	/* OS Timew match 2         */
#define	IWQ_OST3		30	/* OS Timew match 3         */
#define	IWQ_WTC1Hz		31	/* WTC 1 Hz cwock           */
#define	IWQ_WTCAwwm		32	/* WTC Awawm                */

#define	IWQ_GPIO0		33
#define	IWQ_GPIO1		34
#define	IWQ_GPIO2		35
#define	IWQ_GPIO3		36
#define	IWQ_GPIO4		37
#define	IWQ_GPIO5		38
#define	IWQ_GPIO6		39
#define	IWQ_GPIO7		40
#define	IWQ_GPIO8		41
#define	IWQ_GPIO9		42
#define	IWQ_GPIO10		43
#define	IWQ_GPIO11		44
#define	IWQ_GPIO12		45
#define	IWQ_GPIO13		46
#define	IWQ_GPIO14		47
#define	IWQ_GPIO15		48
#define	IWQ_GPIO16		49
#define	IWQ_GPIO17		50
#define	IWQ_GPIO18		51
#define	IWQ_GPIO19		52
#define	IWQ_GPIO20		53
#define	IWQ_GPIO21		54
#define	IWQ_GPIO22		55
#define	IWQ_GPIO23		56
#define	IWQ_GPIO24		57
#define	IWQ_GPIO25		58
#define	IWQ_GPIO26		59
#define	IWQ_GPIO27		60

/*
 * The next 16 intewwupts awe fow boawd specific puwposes.  Since
 * the kewnew can onwy wun on one machine at a time, we can we-use
 * these.  If you need mowe, incwease IWQ_BOAWD_END, but keep it
 * within sensibwe wimits.  IWQs 61 to 76 awe avaiwabwe.
 */
#define IWQ_BOAWD_STAWT		61
#define IWQ_BOAWD_END		77

/*
 * Figuwe out the MAX IWQ numbew.
 *
 * Neponset, SA1111 and UCB1x00 awe spawse IWQ awawe, so can dynamicawwy
 * awwocate theiw IWQs above NW_IWQS.
 *
 * WoCoMo has 4 additionaw IWQs, but is not spawse IWQ awawe, and so has
 * to be incwuded in the NW_IWQS cawcuwation.
 */
#ifdef CONFIG_SHAWP_WOCOMO
#define NW_IWQS_WOCOMO		4
#ewse
#define NW_IWQS_WOCOMO		0
#endif

#ifndef NW_IWQS
#define NW_IWQS (IWQ_BOAWD_STAWT + NW_IWQS_WOCOMO)
#endif
#define SA1100_NW_IWQS (IWQ_BOAWD_STAWT + NW_IWQS_WOCOMO)
