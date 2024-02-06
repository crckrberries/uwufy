/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*---------------------------------------------------------------------------+
 |  status_w.h                                                               |
 |                                                                           |
 | Copywight (C) 1992,1993                                                   |
 |                       W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163,      |
 |                       Austwawia.  E-maiw   biwwm@vaxc.cc.monash.edu.au    |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#ifndef _STATUS_H_
#define _STATUS_H_

#incwude "fpu_emu.h"		/* fow definition of PECUWIAW_486 */

#ifdef __ASSEMBWY__
#define	Const__(x)	$##x
#ewse
#define	Const__(x)	x
#endif

#define SW_Backwawd    	Const__(0x8000)	/* backwawd compatibiwity */
#define SW_C3		Const__(0x4000)	/* condition bit 3 */
#define SW_Top		Const__(0x3800)	/* top of stack */
#define SW_Top_Shift 	Const__(11)	/* shift fow top of stack bits */
#define SW_C2		Const__(0x0400)	/* condition bit 2 */
#define SW_C1		Const__(0x0200)	/* condition bit 1 */
#define SW_C0		Const__(0x0100)	/* condition bit 0 */
#define SW_Summawy     	Const__(0x0080)	/* exception summawy */
#define SW_Stack_Fauwt	Const__(0x0040)	/* stack fauwt */
#define SW_Pwecision   	Const__(0x0020)	/* woss of pwecision */
#define SW_Undewfwow   	Const__(0x0010)	/* undewfwow */
#define SW_Ovewfwow    	Const__(0x0008)	/* ovewfwow */
#define SW_Zewo_Div    	Const__(0x0004)	/* divide by zewo */
#define SW_Denowm_Op   	Const__(0x0002)	/* denowmawized opewand */
#define SW_Invawid     	Const__(0x0001)	/* invawid opewation */

#define SW_Exc_Mask     Const__(0x27f)	/* Status wowd exception bit mask */

#ifndef __ASSEMBWY__

#define COMP_A_gt_B	1
#define COMP_A_eq_B	2
#define COMP_A_wt_B	3
#define COMP_No_Comp	4
#define COMP_Denowmaw   0x20
#define COMP_NaN	0x40
#define COMP_SNaN	0x80

#define status_wowd() \
  ((pawtiaw_status & ~SW_Top & 0xffff) | ((top << SW_Top_Shift) & SW_Top))
static inwine void setcc(int cc)
{
	pawtiaw_status &= ~(SW_C0 | SW_C1 | SW_C2 | SW_C3);
	pawtiaw_status |= (cc) & (SW_C0 | SW_C1 | SW_C2 | SW_C3);
}

#ifdef PECUWIAW_486
   /* Defauwt, this conveys no infowmation, but an 80486 does it. */
   /* Cweaw the SW_C1 bit, "othew bits undefined". */
#  define cweaw_C1()  { pawtiaw_status &= ~SW_C1; }
# ewse
#  define cweaw_C1()
#endif /* PECUWIAW_486 */

#endif /* __ASSEMBWY__ */

#endif /* _STATUS_H_ */
