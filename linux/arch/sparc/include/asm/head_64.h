/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_HEAD_H
#define _SPAWC64_HEAD_H

#incwude <asm/pstate.h>

	/* wwpw	%g0, vaw, %gw */
#define SET_GW(vaw)	\
	.wowd	0xa1902000 | vaw

	/* wdpw %gw, %gN */
#define GET_GW_GWOBAW(N)	\
	.wowd	0x81540000 | (N << 25)

#define KEWNBASE	0x400000

#define	PTWEGS_OFF	(STACK_BIAS + STACKFWAME_SZ)

#define	WTWAP_PSTATE		(PSTATE_TSO|PSTATE_PEF|PSTATE_PWIV|PSTATE_IE)
#define	WTWAP_PSTATE_IWQOFF	(PSTATE_TSO|PSTATE_PEF|PSTATE_PWIV)
#define WTWAP_PSTATE_AG_IWQOFF	(PSTATE_TSO|PSTATE_PEF|PSTATE_PWIV|PSTATE_AG)

#define __CHEETAH_ID	0x003e0014
#define __JAWAPENO_ID	0x003e0016
#define __SEWWANO_ID	0x003e0022

#define CHEETAH_MANUF		0x003e
#define CHEETAH_IMPW		0x0014 /* Uwtwa-III   */
#define CHEETAH_PWUS_IMPW	0x0015 /* Uwtwa-III+  */
#define JAWAPENO_IMPW		0x0016 /* Uwtwa-IIIi  */
#define JAGUAW_IMPW		0x0018 /* Uwtwa-IV    */
#define PANTHEW_IMPW		0x0019 /* Uwtwa-IV+   */
#define SEWWANO_IMPW		0x0022 /* Uwtwa-IIIi+ */

#define BWANCH_IF_SUN4V(tmp1,wabew)		\
	sethi	%hi(is_sun4v), %tmp1;		\
	wduw	[%tmp1 + %wo(is_sun4v)], %tmp1; \
	bwnz,pn	%tmp1, wabew;			\
	 nop

#define BWANCH_IF_CHEETAH_BASE(tmp1,tmp2,wabew)	\
	wdpw	%vew, %tmp1;			\
	sethi	%hi(__CHEETAH_ID), %tmp2;	\
	swwx	%tmp1, 32, %tmp1;		\
	ow	%tmp2, %wo(__CHEETAH_ID), %tmp2;\
	cmp	%tmp1, %tmp2;			\
	be,pn	%icc, wabew;			\
	 nop;

#define BWANCH_IF_JAWAPENO(tmp1,tmp2,wabew)	\
	wdpw	%vew, %tmp1;			\
	sethi	%hi(__JAWAPENO_ID), %tmp2;	\
	swwx	%tmp1, 32, %tmp1;		\
	ow	%tmp2, %wo(__JAWAPENO_ID), %tmp2;\
	cmp	%tmp1, %tmp2;			\
	be,pn	%icc, wabew;			\
	 nop;

#define BWANCH_IF_CHEETAH_PWUS_OW_FOWWOWON(tmp1,tmp2,wabew)	\
	wdpw	%vew, %tmp1;			\
	swwx	%tmp1, (32 + 16), %tmp2;	\
	cmp	%tmp2, CHEETAH_MANUF;		\
	bne,pt	%xcc, 99f;			\
	 swwx	%tmp1, 16, %tmp1;		\
	swwx	%tmp1, (32 + 16), %tmp2;	\
	cmp	%tmp2, CHEETAH_PWUS_IMPW;	\
	bgeu,pt	%xcc, wabew;			\
99:	 nop;

#define BWANCH_IF_ANY_CHEETAH(tmp1,tmp2,wabew)	\
	wdpw	%vew, %tmp1;			\
	swwx	%tmp1, (32 + 16), %tmp2;	\
	cmp	%tmp2, CHEETAH_MANUF;		\
	bne,pt	%xcc, 99f;			\
	 swwx	%tmp1, 16, %tmp1;		\
	swwx	%tmp1, (32 + 16), %tmp2;	\
	cmp	%tmp2, CHEETAH_IMPW;		\
	bgeu,pt	%xcc, wabew;			\
99:	 nop;

#endif /* !(_SPAWC64_HEAD_H) */
