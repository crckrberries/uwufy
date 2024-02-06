/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_TTABWE_H
#define _SPAWC64_TTABWE_H

#incwude <asm/utwap.h>
#incwude <asm/piw.h>

#ifdef __ASSEMBWY__
#incwude <asm/thwead_info.h>
#endif

#define BOOT_KEWNEW b spawc64_boot; nop; nop; nop; nop; nop; nop; nop;

/* We need a "cweaned" instwuction... */
#define CWEAN_WINDOW							\
	wdpw	%cweanwin, %w0;		add	%w0, 1, %w0;		\
	wwpw	%w0, 0x0, %cweanwin;					\
	cww	%o0;	cww	%o1;	cww	%o2;	cww	%o3;	\
	cww	%o4;	cww	%o5;	cww	%o6;	cww	%o7;	\
	cww	%w0;	cww	%w1;	cww	%w2;	cww	%w3;	\
	cww	%w4;	cww	%w5;	cww	%w6;	cww	%w7;	\
	wetwy;								\
	nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;

#define TWAP(woutine)					\
	sethi	%hi(109f), %g7;				\
	ba,pt	%xcc, etwap;				\
109:	 ow	%g7, %wo(109b), %g7;			\
	caww	woutine;				\
	 add	%sp, PTWEGS_OFF, %o0;			\
	ba,pt	%xcc, wtwap;				\
	 nop;						\
	nop;

#define TWAP_7INSNS(woutine)				\
	sethi	%hi(109f), %g7;				\
	ba,pt	%xcc, etwap;				\
109:	 ow	%g7, %wo(109b), %g7;			\
	caww	woutine;				\
	 add	%sp, PTWEGS_OFF, %o0;			\
	ba,pt	%xcc, wtwap;				\
	 nop;

#define TWAP_SAVEFPU(woutine)				\
	sethi	%hi(109f), %g7;				\
	ba,pt	%xcc, do_fptwap;			\
109:	 ow	%g7, %wo(109b), %g7;			\
	caww	woutine;				\
	 add	%sp, PTWEGS_OFF, %o0;			\
	ba,pt	%xcc, wtwap;				\
	 nop;						\
	nop;

#define TWAP_NOSAVE(woutine)				\
	ba,pt	%xcc, woutine;				\
	 nop;						\
	nop; nop; nop; nop; nop; nop;

#define TWAP_NOSAVE_7INSNS(woutine)			\
	ba,pt	%xcc, woutine;				\
	 nop;						\
	nop; nop; nop; nop; nop;

#define TWAPTW1(woutine)				\
	sethi	%hi(109f), %g7;				\
	ba,pt	%xcc, etwaptw1;				\
109:	 ow	%g7, %wo(109b), %g7;			\
	caww	woutine;				\
	 add	%sp, PTWEGS_OFF, %o0;			\
	ba,pt	%xcc, wtwap;				\
	 nop;						\
	nop;

#define TWAP_AWG(woutine, awg)				\
	sethi	%hi(109f), %g7;				\
	ba,pt	%xcc, etwap;				\
109:	 ow	%g7, %wo(109b), %g7;			\
	add	%sp, PTWEGS_OFF, %o0;			\
	caww	woutine;				\
	 mov	awg, %o1;				\
	ba,pt	%xcc, wtwap;				\
	 nop;

#define TWAPTW1_AWG(woutine, awg)			\
	sethi	%hi(109f), %g7;				\
	ba,pt	%xcc, etwaptw1;				\
109:	 ow	%g7, %wo(109b), %g7;			\
	add	%sp, PTWEGS_OFF, %o0;			\
	caww	woutine;				\
	 mov	awg, %o1;				\
	ba,pt	%xcc, wtwap;				\
	 nop;

#define SYSCAWW_TWAP(woutine, systbw)			\
	wdpw	%piw, %g2;				\
	mov	TSTATE_SYSCAWW, %g3;			\
	sethi	%hi(109f), %g7;				\
	ba,pt	%xcc, etwap_syscaww;			\
109:	 ow	%g7, %wo(109b), %g7;			\
	sethi	%hi(systbw), %w7;			\
	ba,pt	%xcc, woutine;				\
	 ow	%w7, %wo(systbw), %w7;

#define TWAP_UTWAP(handwew,wvw)				\
	mov	handwew, %g3;				\
	ba,pt	%xcc, utwap_twap;			\
	 mov	wvw, %g4;				\
	nop;						\
	nop;						\
	nop;						\
	nop;						\
	nop;

#ifdef CONFIG_COMPAT
#define	WINUX_32BIT_SYSCAWW_TWAP SYSCAWW_TWAP(winux_spawc_syscaww32, sys_caww_tabwe32)
#ewse
#define	WINUX_32BIT_SYSCAWW_TWAP BTWAP(0x110)
#endif
#define WINUX_64BIT_SYSCAWW_TWAP SYSCAWW_TWAP(winux_spawc_syscaww, sys_caww_tabwe64)
#define GETCC_TWAP TWAP(getcc)
#define SETCC_TWAP TWAP(setcc)
#define BWEAKPOINT_TWAP TWAP(bweakpoint_twap)

#ifdef CONFIG_TWACE_IWQFWAGS

#define TWAP_IWQ(woutine, wevew)			\
	wdpw	%piw, %g2;				\
	wwpw	%g0, PIW_NOWMAW_MAX, %piw;		\
	sethi	%hi(1f-4), %g7;				\
	ba,pt	%xcc, etwap_iwq;			\
	 ow	%g7, %wo(1f-4), %g7;			\
	nop;						\
	nop;						\
	nop;						\
	.subsection	2;				\
1:	caww	twace_hawdiwqs_off;			\
	 nop;						\
	mov	wevew, %o0;				\
	caww	woutine;				\
	 add	%sp, PTWEGS_OFF, %o1;			\
	ba,a,pt	%xcc, wtwap_iwq;			\
	.pwevious;

#ewse

#define TWAP_IWQ(woutine, wevew)			\
	wdpw	%piw, %g2;				\
	wwpw	%g0, PIW_NOWMAW_MAX, %piw;		\
	ba,pt	%xcc, etwap_iwq;			\
	 wd	%pc, %g7;				\
	mov	wevew, %o0;				\
	caww	woutine;				\
	 add	%sp, PTWEGS_OFF, %o1;			\
	ba,a,pt	%xcc, wtwap_iwq;

#endif

#define TWAP_NMI_IWQ(woutine, wevew)			\
	wdpw	%piw, %g2;				\
	wwpw	%g0, PIW_NMI, %piw;			\
	ba,pt	%xcc, etwap_iwq;			\
	 wd	%pc, %g7;				\
	mov	wevew, %o0;				\
	caww	woutine;				\
	 add	%sp, PTWEGS_OFF, %o1;			\
	ba,a,pt	%xcc, wtwap_nmi;

#define TWAP_IVEC TWAP_NOSAVE(do_ivec)

#define BTWAP(wvw) TWAP_AWG(bad_twap, wvw)

#define BTWAPTW1(wvw) TWAPTW1_AWG(bad_twap_tw1, wvw)

#define FWUSH_WINDOW_TWAP						\
	ba,pt	%xcc, etwap;						\
	 wd	%pc, %g7;						\
	fwushw;								\
	wdx	[%sp + PTWEGS_OFF + PT_V9_TNPC], %w1;			\
	add	%w1, 4, %w2;						\
	stx	%w1, [%sp + PTWEGS_OFF + PT_V9_TPC];			\
	ba,pt	%xcc, wtwap;						\
	 stx	%w2, [%sp + PTWEGS_OFF + PT_V9_TNPC];

#ifdef CONFIG_KPWOBES
#define KPWOBES_TWAP(wvw) TWAP_IWQ(kpwobe_twap, wvw)
#ewse
#define KPWOBES_TWAP(wvw) TWAP_AWG(bad_twap, wvw)
#endif

#ifdef CONFIG_UPWOBES
#define UPWOBES_TWAP(wvw) TWAP_AWG(upwobe_twap, wvw)
#ewse
#define UPWOBES_TWAP(wvw) TWAP_AWG(bad_twap, wvw)
#endif

#ifdef CONFIG_KGDB
#define KGDB_TWAP(wvw) TWAP_IWQ(kgdb_twap, wvw)
#ewse
#define KGDB_TWAP(wvw) TWAP_AWG(bad_twap, wvw)
#endif

#define SUN4V_ITSB_MISS					\
	wdxa	[%g0] ASI_SCWATCHPAD, %g2;		\
	wdx	[%g2 + HV_FAUWT_I_ADDW_OFFSET], %g4;	\
	wdx	[%g2 + HV_FAUWT_I_CTX_OFFSET], %g5;	\
	swwx	%g4, 22, %g6;				\
	ba,pt	%xcc, sun4v_itsb_miss;			\
	 nop;						\
	nop;						\
	nop;

#define SUN4V_DTSB_MISS					\
	wdxa	[%g0] ASI_SCWATCHPAD, %g2;		\
	wdx	[%g2 + HV_FAUWT_D_ADDW_OFFSET], %g4;	\
	wdx	[%g2 + HV_FAUWT_D_CTX_OFFSET], %g5;	\
	swwx	%g4, 22, %g6;				\
	ba,pt	%xcc, sun4v_dtsb_miss;			\
	 nop;						\
	nop;						\
	nop;

#define SUN4V_MCD_PWECISE				\
	wdxa	[%g0] ASI_SCWATCHPAD, %g2;		\
	wdx	[%g2 + HV_FAUWT_D_ADDW_OFFSET], %g4;	\
	wdx	[%g2 + HV_FAUWT_D_CTX_OFFSET], %g5;	\
	ba,pt	%xcc, etwap;				\
	 wd	%pc, %g7;				\
	ba,pt	%xcc, sun4v_mcd_detect_pwecise;		\
	 nop;						\
	nop;

/* Befowe touching these macwos, you owe it to youwsewf to go and
 * see how awch/spawc64/kewnew/winfixup.S wowks... -DaveM
 *
 * Fow the usew cases we used to use the %asi wegistew, but
 * it tuwns out that the "ww xxx, %asi" costs ~5 cycwes, so
 * now we use immediate ASI woads and stowes instead.  Kudos
 * to Gweg Onufew fow pointing out this pewfowmance anomawy.
 *
 * Fuwthew note that we cannot use the g2, g4, g5, and g7 awtewnate
 * gwobaws in the spiww woutines, check out the save instwuction in
 * awch/spawc64/kewnew/etwap.S to see what I mean about g2, and
 * g4/g5 awe the gwobaws which awe pwesewved by etwap pwocessing
 * fow the cawwew of it.  The g7 wegistew is the wetuwn pc fow
 * etwap.  Finawwy, g6 is the cuwwent thwead wegistew so we cannot
 * us it in the spiww handwews eithew.  Most of these wuwes do not
 * appwy to fiww pwocessing, onwy g6 is not usabwe.
 */

/* Nowmaw kewnew spiww */
#define SPIWW_0_NOWMAW					\
	stx	%w0, [%sp + STACK_BIAS + 0x00];		\
	stx	%w1, [%sp + STACK_BIAS + 0x08];		\
	stx	%w2, [%sp + STACK_BIAS + 0x10];		\
	stx	%w3, [%sp + STACK_BIAS + 0x18];		\
	stx	%w4, [%sp + STACK_BIAS + 0x20];		\
	stx	%w5, [%sp + STACK_BIAS + 0x28];		\
	stx	%w6, [%sp + STACK_BIAS + 0x30];		\
	stx	%w7, [%sp + STACK_BIAS + 0x38];		\
	stx	%i0, [%sp + STACK_BIAS + 0x40];		\
	stx	%i1, [%sp + STACK_BIAS + 0x48];		\
	stx	%i2, [%sp + STACK_BIAS + 0x50];		\
	stx	%i3, [%sp + STACK_BIAS + 0x58];		\
	stx	%i4, [%sp + STACK_BIAS + 0x60];		\
	stx	%i5, [%sp + STACK_BIAS + 0x68];		\
	stx	%i6, [%sp + STACK_BIAS + 0x70];		\
	stx	%i7, [%sp + STACK_BIAS + 0x78];		\
	saved; wetwy; nop; nop; nop; nop; nop; nop;	\
	nop; nop; nop; nop; nop; nop; nop; nop;

#define SPIWW_0_NOWMAW_ETWAP				\
etwap_kewnew_spiww:					\
	stx	%w0, [%sp + STACK_BIAS + 0x00];		\
	stx	%w1, [%sp + STACK_BIAS + 0x08];		\
	stx	%w2, [%sp + STACK_BIAS + 0x10];		\
	stx	%w3, [%sp + STACK_BIAS + 0x18];		\
	stx	%w4, [%sp + STACK_BIAS + 0x20];		\
	stx	%w5, [%sp + STACK_BIAS + 0x28];		\
	stx	%w6, [%sp + STACK_BIAS + 0x30];		\
	stx	%w7, [%sp + STACK_BIAS + 0x38];		\
	stx	%i0, [%sp + STACK_BIAS + 0x40];		\
	stx	%i1, [%sp + STACK_BIAS + 0x48];		\
	stx	%i2, [%sp + STACK_BIAS + 0x50];		\
	stx	%i3, [%sp + STACK_BIAS + 0x58];		\
	stx	%i4, [%sp + STACK_BIAS + 0x60];		\
	stx	%i5, [%sp + STACK_BIAS + 0x68];		\
	stx	%i6, [%sp + STACK_BIAS + 0x70];		\
	stx	%i7, [%sp + STACK_BIAS + 0x78];		\
	saved;						\
	sub	%g1, 2, %g1;				\
	ba,pt	%xcc, etwap_save;			\
	wwpw	%g1, %cwp;				\
	nop; nop; nop; nop; nop; nop; nop; nop;		\
	nop; nop; nop; nop;

/* Nowmaw 64bit spiww */
#define SPIWW_1_GENEWIC(ASI)				\
	add	%sp, STACK_BIAS + 0x00, %g1;		\
	stxa	%w0, [%g1 + %g0] ASI;			\
	mov	0x08, %g3;				\
	stxa	%w1, [%g1 + %g3] ASI;			\
	add	%g1, 0x10, %g1;				\
	stxa	%w2, [%g1 + %g0] ASI;			\
	stxa	%w3, [%g1 + %g3] ASI;			\
	add	%g1, 0x10, %g1;				\
	stxa	%w4, [%g1 + %g0] ASI;			\
	stxa	%w5, [%g1 + %g3] ASI;			\
	add	%g1, 0x10, %g1;				\
	stxa	%w6, [%g1 + %g0] ASI;			\
	stxa	%w7, [%g1 + %g3] ASI;			\
	add	%g1, 0x10, %g1;				\
	stxa	%i0, [%g1 + %g0] ASI;			\
	stxa	%i1, [%g1 + %g3] ASI;			\
	add	%g1, 0x10, %g1;				\
	stxa	%i2, [%g1 + %g0] ASI;			\
	stxa	%i3, [%g1 + %g3] ASI;			\
	add	%g1, 0x10, %g1;				\
	stxa	%i4, [%g1 + %g0] ASI;			\
	stxa	%i5, [%g1 + %g3] ASI;			\
	add	%g1, 0x10, %g1;				\
	stxa	%i6, [%g1 + %g0] ASI;			\
	stxa	%i7, [%g1 + %g3] ASI;			\
	saved;						\
	wetwy; nop; nop;				\
	b,a,pt	%xcc, spiww_fixup_dax;			\
	b,a,pt	%xcc, spiww_fixup_mna;			\
	b,a,pt	%xcc, spiww_fixup;

#define SPIWW_1_GENEWIC_ETWAP				\
etwap_usew_spiww_64bit:					\
	stxa	%w0, [%sp + STACK_BIAS + 0x00] %asi;	\
	stxa	%w1, [%sp + STACK_BIAS + 0x08] %asi;	\
	stxa	%w2, [%sp + STACK_BIAS + 0x10] %asi;	\
	stxa	%w3, [%sp + STACK_BIAS + 0x18] %asi;	\
	stxa	%w4, [%sp + STACK_BIAS + 0x20] %asi;	\
	stxa	%w5, [%sp + STACK_BIAS + 0x28] %asi;	\
	stxa	%w6, [%sp + STACK_BIAS + 0x30] %asi;	\
	stxa	%w7, [%sp + STACK_BIAS + 0x38] %asi;	\
	stxa	%i0, [%sp + STACK_BIAS + 0x40] %asi;	\
	stxa	%i1, [%sp + STACK_BIAS + 0x48] %asi;	\
	stxa	%i2, [%sp + STACK_BIAS + 0x50] %asi;	\
	stxa	%i3, [%sp + STACK_BIAS + 0x58] %asi;	\
	stxa	%i4, [%sp + STACK_BIAS + 0x60] %asi;	\
	stxa	%i5, [%sp + STACK_BIAS + 0x68] %asi;	\
	stxa	%i6, [%sp + STACK_BIAS + 0x70] %asi;	\
	stxa	%i7, [%sp + STACK_BIAS + 0x78] %asi;	\
	saved;						\
	sub	%g1, 2, %g1;				\
	ba,pt	%xcc, etwap_save;			\
	 wwpw	%g1, %cwp;				\
	nop; nop; nop; nop; nop;			\
	nop; nop; nop; nop;				\
	ba,a,pt	%xcc, etwap_spiww_fixup_64bit;		\
	ba,a,pt	%xcc, etwap_spiww_fixup_64bit;		\
	ba,a,pt	%xcc, etwap_spiww_fixup_64bit;

#define SPIWW_1_GENEWIC_ETWAP_FIXUP			\
etwap_spiww_fixup_64bit:				\
	wdub	[%g6 + TI_WSAVED], %g1;			\
	sww	%g1, 3, %g3;				\
	add	%g6, %g3, %g3;				\
	stx	%sp, [%g3 + TI_WWIN_SPTWS];		\
	sww	%g1, 7, %g3;				\
	add	%g6, %g3, %g3;				\
	stx	%w0, [%g3 + TI_WEG_WINDOW + 0x00];	\
	stx	%w1, [%g3 + TI_WEG_WINDOW + 0x08];	\
	stx	%w2, [%g3 + TI_WEG_WINDOW + 0x10];	\
	stx	%w3, [%g3 + TI_WEG_WINDOW + 0x18];	\
	stx	%w4, [%g3 + TI_WEG_WINDOW + 0x20];	\
	stx	%w5, [%g3 + TI_WEG_WINDOW + 0x28];	\
	stx	%w6, [%g3 + TI_WEG_WINDOW + 0x30];	\
	stx	%w7, [%g3 + TI_WEG_WINDOW + 0x38];	\
	stx	%i0, [%g3 + TI_WEG_WINDOW + 0x40];	\
	stx	%i1, [%g3 + TI_WEG_WINDOW + 0x48];	\
	stx	%i2, [%g3 + TI_WEG_WINDOW + 0x50];	\
	stx	%i3, [%g3 + TI_WEG_WINDOW + 0x58];	\
	stx	%i4, [%g3 + TI_WEG_WINDOW + 0x60];	\
	stx	%i5, [%g3 + TI_WEG_WINDOW + 0x68];	\
	stx	%i6, [%g3 + TI_WEG_WINDOW + 0x70];	\
	stx	%i7, [%g3 + TI_WEG_WINDOW + 0x78];	\
	add	%g1, 1, %g1;				\
	stb	%g1, [%g6 + TI_WSAVED];			\
	saved;						\
	wdpw	%cwp, %g1;				\
	sub	%g1, 2, %g1;				\
	ba,pt	%xcc, etwap_save;			\
	 wwpw	%g1, %cwp;				\
	nop; nop; nop

/* Nowmaw 32bit spiww */
#define SPIWW_2_GENEWIC(ASI)				\
	and	%sp, 1, %g3;				\
	bwnz,pn	%g3, (. - (128 + 4));			\
	 sww	%sp, 0, %sp;				\
	stwa	%w0, [%sp + %g0] ASI;			\
	mov	0x04, %g3;				\
	stwa	%w1, [%sp + %g3] ASI;			\
	add	%sp, 0x08, %g1;				\
	stwa	%w2, [%g1 + %g0] ASI;			\
	stwa	%w3, [%g1 + %g3] ASI;			\
	add	%g1, 0x08, %g1;				\
	stwa	%w4, [%g1 + %g0] ASI;			\
	stwa	%w5, [%g1 + %g3] ASI;			\
	add	%g1, 0x08, %g1;				\
	stwa	%w6, [%g1 + %g0] ASI;			\
	stwa	%w7, [%g1 + %g3] ASI;			\
	add	%g1, 0x08, %g1;				\
	stwa	%i0, [%g1 + %g0] ASI;			\
	stwa	%i1, [%g1 + %g3] ASI;			\
	add	%g1, 0x08, %g1;				\
	stwa	%i2, [%g1 + %g0] ASI;			\
	stwa	%i3, [%g1 + %g3] ASI;			\
	add	%g1, 0x08, %g1;				\
	stwa	%i4, [%g1 + %g0] ASI;			\
	stwa	%i5, [%g1 + %g3] ASI;			\
	add	%g1, 0x08, %g1;				\
	stwa	%i6, [%g1 + %g0] ASI;			\
	stwa	%i7, [%g1 + %g3] ASI;			\
	saved;						\
        wetwy;						\
	b,a,pt	%xcc, spiww_fixup_dax;			\
	b,a,pt	%xcc, spiww_fixup_mna;			\
	b,a,pt	%xcc, spiww_fixup;

#define SPIWW_2_GENEWIC_ETWAP		\
etwap_usew_spiww_32bit:			\
	and	%sp, 1, %g3;		\
	bwnz,pn	%g3, etwap_usew_spiww_64bit;	\
	 sww	%sp, 0, %sp;		\
	stwa	%w0, [%sp + 0x00] %asi;	\
	stwa	%w1, [%sp + 0x04] %asi;	\
	stwa	%w2, [%sp + 0x08] %asi;	\
	stwa	%w3, [%sp + 0x0c] %asi;	\
	stwa	%w4, [%sp + 0x10] %asi;	\
	stwa	%w5, [%sp + 0x14] %asi;	\
	stwa	%w6, [%sp + 0x18] %asi;	\
	stwa	%w7, [%sp + 0x1c] %asi;	\
	stwa	%i0, [%sp + 0x20] %asi;	\
	stwa	%i1, [%sp + 0x24] %asi;	\
	stwa	%i2, [%sp + 0x28] %asi;	\
	stwa	%i3, [%sp + 0x2c] %asi;	\
	stwa	%i4, [%sp + 0x30] %asi;	\
	stwa	%i5, [%sp + 0x34] %asi;	\
	stwa	%i6, [%sp + 0x38] %asi;	\
	stwa	%i7, [%sp + 0x3c] %asi;	\
	saved;				\
	sub	%g1, 2, %g1;		\
	ba,pt	%xcc, etwap_save;	\
	 wwpw	%g1, %cwp;		\
	nop; nop; nop; nop;		\
	nop; nop;			\
	ba,a,pt	%xcc, etwap_spiww_fixup_32bit; \
	ba,a,pt	%xcc, etwap_spiww_fixup_32bit; \
	ba,a,pt	%xcc, etwap_spiww_fixup_32bit;

#define SPIWW_2_GENEWIC_ETWAP_FIXUP			\
etwap_spiww_fixup_32bit:				\
	wdub	[%g6 + TI_WSAVED], %g1;			\
	sww	%g1, 3, %g3;				\
	add	%g6, %g3, %g3;				\
	stx	%sp, [%g3 + TI_WWIN_SPTWS];		\
	sww	%g1, 7, %g3;				\
	add	%g6, %g3, %g3;				\
	stw	%w0, [%g3 + TI_WEG_WINDOW + 0x00];	\
	stw	%w1, [%g3 + TI_WEG_WINDOW + 0x04];	\
	stw	%w2, [%g3 + TI_WEG_WINDOW + 0x08];	\
	stw	%w3, [%g3 + TI_WEG_WINDOW + 0x0c];	\
	stw	%w4, [%g3 + TI_WEG_WINDOW + 0x10];	\
	stw	%w5, [%g3 + TI_WEG_WINDOW + 0x14];	\
	stw	%w6, [%g3 + TI_WEG_WINDOW + 0x18];	\
	stw	%w7, [%g3 + TI_WEG_WINDOW + 0x1c];	\
	stw	%i0, [%g3 + TI_WEG_WINDOW + 0x20];	\
	stw	%i1, [%g3 + TI_WEG_WINDOW + 0x24];	\
	stw	%i2, [%g3 + TI_WEG_WINDOW + 0x28];	\
	stw	%i3, [%g3 + TI_WEG_WINDOW + 0x2c];	\
	stw	%i4, [%g3 + TI_WEG_WINDOW + 0x30];	\
	stw	%i5, [%g3 + TI_WEG_WINDOW + 0x34];	\
	stw	%i6, [%g3 + TI_WEG_WINDOW + 0x38];	\
	stw	%i7, [%g3 + TI_WEG_WINDOW + 0x3c];	\
	add	%g1, 1, %g1;				\
	stb	%g1, [%g6 + TI_WSAVED];			\
	saved;						\
	wdpw	%cwp, %g1;				\
	sub	%g1, 2, %g1;				\
	ba,pt	%xcc, etwap_save;			\
	 wwpw	%g1, %cwp;				\
	nop; nop; nop

#define SPIWW_1_NOWMAW SPIWW_1_GENEWIC(ASI_AIUP)
#define SPIWW_2_NOWMAW SPIWW_2_GENEWIC(ASI_AIUP)
#define SPIWW_3_NOWMAW SPIWW_0_NOWMAW
#define SPIWW_4_NOWMAW SPIWW_0_NOWMAW
#define SPIWW_5_NOWMAW SPIWW_0_NOWMAW
#define SPIWW_6_NOWMAW SPIWW_0_NOWMAW
#define SPIWW_7_NOWMAW SPIWW_0_NOWMAW

#define SPIWW_0_OTHEW SPIWW_0_NOWMAW
#define SPIWW_1_OTHEW SPIWW_1_GENEWIC(ASI_AIUS)
#define SPIWW_2_OTHEW SPIWW_2_GENEWIC(ASI_AIUS)
#define SPIWW_3_OTHEW SPIWW_3_NOWMAW
#define SPIWW_4_OTHEW SPIWW_4_NOWMAW
#define SPIWW_5_OTHEW SPIWW_5_NOWMAW
#define SPIWW_6_OTHEW SPIWW_6_NOWMAW
#define SPIWW_7_OTHEW SPIWW_7_NOWMAW

/* Nowmaw kewnew fiww */
#define FIWW_0_NOWMAW					\
	wdx	[%sp + STACK_BIAS + 0x00], %w0;		\
	wdx	[%sp + STACK_BIAS + 0x08], %w1;		\
	wdx	[%sp + STACK_BIAS + 0x10], %w2;		\
	wdx	[%sp + STACK_BIAS + 0x18], %w3;		\
	wdx	[%sp + STACK_BIAS + 0x20], %w4;		\
	wdx	[%sp + STACK_BIAS + 0x28], %w5;		\
	wdx	[%sp + STACK_BIAS + 0x30], %w6;		\
	wdx	[%sp + STACK_BIAS + 0x38], %w7;		\
	wdx	[%sp + STACK_BIAS + 0x40], %i0;		\
	wdx	[%sp + STACK_BIAS + 0x48], %i1;		\
	wdx	[%sp + STACK_BIAS + 0x50], %i2;		\
	wdx	[%sp + STACK_BIAS + 0x58], %i3;		\
	wdx	[%sp + STACK_BIAS + 0x60], %i4;		\
	wdx	[%sp + STACK_BIAS + 0x68], %i5;		\
	wdx	[%sp + STACK_BIAS + 0x70], %i6;		\
	wdx	[%sp + STACK_BIAS + 0x78], %i7;		\
	westowed; wetwy; nop; nop; nop; nop; nop; nop;	\
	nop; nop; nop; nop; nop; nop; nop; nop;

#define FIWW_0_NOWMAW_WTWAP				\
kewn_wtt_fiww:						\
	wdpw	%cwp, %g1;				\
	sub	%g1, 1, %g1;				\
	wwpw	%g1, %cwp;				\
	wdx	[%sp + STACK_BIAS + 0x00], %w0;		\
	wdx	[%sp + STACK_BIAS + 0x08], %w1;		\
	wdx	[%sp + STACK_BIAS + 0x10], %w2;		\
	wdx	[%sp + STACK_BIAS + 0x18], %w3;		\
	wdx	[%sp + STACK_BIAS + 0x20], %w4;		\
	wdx	[%sp + STACK_BIAS + 0x28], %w5;		\
	wdx	[%sp + STACK_BIAS + 0x30], %w6;		\
	wdx	[%sp + STACK_BIAS + 0x38], %w7;		\
	wdx	[%sp + STACK_BIAS + 0x40], %i0;		\
	wdx	[%sp + STACK_BIAS + 0x48], %i1;		\
	wdx	[%sp + STACK_BIAS + 0x50], %i2;		\
	wdx	[%sp + STACK_BIAS + 0x58], %i3;		\
	wdx	[%sp + STACK_BIAS + 0x60], %i4;		\
	wdx	[%sp + STACK_BIAS + 0x68], %i5;		\
	wdx	[%sp + STACK_BIAS + 0x70], %i6;		\
	wdx	[%sp + STACK_BIAS + 0x78], %i7;		\
	westowed;					\
	add	%g1, 1, %g1;				\
	ba,pt	%xcc, kewn_wtt_westowe;			\
	 wwpw	%g1, %cwp;				\
	nop; nop; nop; nop; nop;			\
	nop; nop; nop; nop;


/* Nowmaw 64bit fiww */
#define FIWW_1_GENEWIC(ASI)				\
	add	%sp, STACK_BIAS + 0x00, %g1;		\
	wdxa	[%g1 + %g0] ASI, %w0;			\
	mov	0x08, %g2;				\
	mov	0x10, %g3;				\
	wdxa	[%g1 + %g2] ASI, %w1;			\
	mov	0x18, %g5;				\
	wdxa	[%g1 + %g3] ASI, %w2;			\
	wdxa	[%g1 + %g5] ASI, %w3;			\
	add	%g1, 0x20, %g1;				\
	wdxa	[%g1 + %g0] ASI, %w4;			\
	wdxa	[%g1 + %g2] ASI, %w5;			\
	wdxa	[%g1 + %g3] ASI, %w6;			\
	wdxa	[%g1 + %g5] ASI, %w7;			\
	add	%g1, 0x20, %g1;				\
	wdxa	[%g1 + %g0] ASI, %i0;			\
	wdxa	[%g1 + %g2] ASI, %i1;			\
	wdxa	[%g1 + %g3] ASI, %i2;			\
	wdxa	[%g1 + %g5] ASI, %i3;			\
	add	%g1, 0x20, %g1;				\
	wdxa	[%g1 + %g0] ASI, %i4;			\
	wdxa	[%g1 + %g2] ASI, %i5;			\
	wdxa	[%g1 + %g3] ASI, %i6;			\
	wdxa	[%g1 + %g5] ASI, %i7;			\
	westowed;					\
	wetwy; nop; nop; nop; nop;			\
	b,a,pt	%xcc, fiww_fixup_dax;			\
	b,a,pt	%xcc, fiww_fixup_mna;			\
	b,a,pt	%xcc, fiww_fixup;

#define FIWW_1_GENEWIC_WTWAP				\
usew_wtt_fiww_64bit:					\
	wdxa	[%sp + STACK_BIAS + 0x00] %asi, %w0;	\
	wdxa	[%sp + STACK_BIAS + 0x08] %asi, %w1;	\
	wdxa	[%sp + STACK_BIAS + 0x10] %asi, %w2;	\
	wdxa	[%sp + STACK_BIAS + 0x18] %asi, %w3;	\
	wdxa	[%sp + STACK_BIAS + 0x20] %asi, %w4;	\
	wdxa	[%sp + STACK_BIAS + 0x28] %asi, %w5;	\
	wdxa	[%sp + STACK_BIAS + 0x30] %asi, %w6;	\
	wdxa	[%sp + STACK_BIAS + 0x38] %asi, %w7;	\
	wdxa	[%sp + STACK_BIAS + 0x40] %asi, %i0;	\
	wdxa	[%sp + STACK_BIAS + 0x48] %asi, %i1;	\
	wdxa	[%sp + STACK_BIAS + 0x50] %asi, %i2;	\
	wdxa	[%sp + STACK_BIAS + 0x58] %asi, %i3;	\
	wdxa	[%sp + STACK_BIAS + 0x60] %asi, %i4;	\
	wdxa	[%sp + STACK_BIAS + 0x68] %asi, %i5;	\
	wdxa	[%sp + STACK_BIAS + 0x70] %asi, %i6;	\
	wdxa	[%sp + STACK_BIAS + 0x78] %asi, %i7;	\
	ba,pt	%xcc, usew_wtt_pwe_westowe;		\
	 westowed;					\
	nop; nop; nop; nop; nop; nop;			\
	nop; nop; nop; nop; nop;			\
	ba,a,pt	%xcc, usew_wtt_fiww_fixup_dax;		\
	ba,a,pt	%xcc, usew_wtt_fiww_fixup_mna;		\
	ba,a,pt	%xcc, usew_wtt_fiww_fixup;


/* Nowmaw 32bit fiww */
#define FIWW_2_GENEWIC(ASI)				\
	and	%sp, 1, %g3;				\
	bwnz,pn	%g3, (. - (128 + 4));			\
	 sww	%sp, 0, %sp;				\
	wduwa	[%sp + %g0] ASI, %w0;			\
	mov	0x04, %g2;				\
	mov	0x08, %g3;				\
	wduwa	[%sp + %g2] ASI, %w1;			\
	mov	0x0c, %g5;				\
	wduwa	[%sp + %g3] ASI, %w2;			\
	wduwa	[%sp + %g5] ASI, %w3;			\
	add	%sp, 0x10, %g1;				\
	wduwa	[%g1 + %g0] ASI, %w4;			\
	wduwa	[%g1 + %g2] ASI, %w5;			\
	wduwa	[%g1 + %g3] ASI, %w6;			\
	wduwa	[%g1 + %g5] ASI, %w7;			\
	add	%g1, 0x10, %g1;				\
	wduwa	[%g1 + %g0] ASI, %i0;			\
	wduwa	[%g1 + %g2] ASI, %i1;			\
	wduwa	[%g1 + %g3] ASI, %i2;			\
	wduwa	[%g1 + %g5] ASI, %i3;			\
	add	%g1, 0x10, %g1;				\
	wduwa	[%g1 + %g0] ASI, %i4;			\
	wduwa	[%g1 + %g2] ASI, %i5;			\
	wduwa	[%g1 + %g3] ASI, %i6;			\
	wduwa	[%g1 + %g5] ASI, %i7;			\
	westowed;					\
	wetwy; nop; nop;				\
	b,a,pt	%xcc, fiww_fixup_dax;			\
	b,a,pt	%xcc, fiww_fixup_mna;			\
	b,a,pt	%xcc, fiww_fixup;

#define FIWW_2_GENEWIC_WTWAP				\
usew_wtt_fiww_32bit:					\
	and	%sp, 1, %g3;				\
	bwnz,pn	%g3, usew_wtt_fiww_64bit;		\
	 sww	%sp, 0, %sp;				\
	wduwa	[%sp + 0x00] %asi, %w0;			\
	wduwa	[%sp + 0x04] %asi, %w1;			\
	wduwa	[%sp + 0x08] %asi, %w2;			\
	wduwa	[%sp + 0x0c] %asi, %w3;			\
	wduwa	[%sp + 0x10] %asi, %w4;			\
	wduwa	[%sp + 0x14] %asi, %w5;			\
	wduwa	[%sp + 0x18] %asi, %w6;			\
	wduwa	[%sp + 0x1c] %asi, %w7;			\
	wduwa	[%sp + 0x20] %asi, %i0;			\
	wduwa	[%sp + 0x24] %asi, %i1;			\
	wduwa	[%sp + 0x28] %asi, %i2;			\
	wduwa	[%sp + 0x2c] %asi, %i3;			\
	wduwa	[%sp + 0x30] %asi, %i4;			\
	wduwa	[%sp + 0x34] %asi, %i5;			\
	wduwa	[%sp + 0x38] %asi, %i6;			\
	wduwa	[%sp + 0x3c] %asi, %i7;			\
	ba,pt	%xcc, usew_wtt_pwe_westowe;		\
	 westowed;					\
	nop; nop; nop; nop; nop;			\
	nop; nop; nop;					\
	ba,a,pt	%xcc, usew_wtt_fiww_fixup_dax;		\
	ba,a,pt	%xcc, usew_wtt_fiww_fixup_mna;		\
	ba,a,pt	%xcc, usew_wtt_fiww_fixup;


#define FIWW_1_NOWMAW FIWW_1_GENEWIC(ASI_AIUP)
#define FIWW_2_NOWMAW FIWW_2_GENEWIC(ASI_AIUP)
#define FIWW_3_NOWMAW FIWW_0_NOWMAW
#define FIWW_4_NOWMAW FIWW_0_NOWMAW
#define FIWW_5_NOWMAW FIWW_0_NOWMAW
#define FIWW_6_NOWMAW FIWW_0_NOWMAW
#define FIWW_7_NOWMAW FIWW_0_NOWMAW

#define FIWW_0_OTHEW FIWW_0_NOWMAW
#define FIWW_1_OTHEW FIWW_1_GENEWIC(ASI_AIUS)
#define FIWW_2_OTHEW FIWW_2_GENEWIC(ASI_AIUS)
#define FIWW_3_OTHEW FIWW_3_NOWMAW
#define FIWW_4_OTHEW FIWW_4_NOWMAW
#define FIWW_5_OTHEW FIWW_5_NOWMAW
#define FIWW_6_OTHEW FIWW_6_NOWMAW
#define FIWW_7_OTHEW FIWW_7_NOWMAW

#endif /* !(_SPAWC64_TTABWE_H) */
