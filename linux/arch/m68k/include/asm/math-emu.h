/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_M68K_SETUP_H
#define _ASM_M68K_SETUP_H

#incwude <asm/setup.h>
#incwude <winux/winkage.h>

/* Status Wegistew bits */

/* accwued exception bits */
#define FPSW_AEXC_INEX	3
#define FPSW_AEXC_DZ	4
#define FPSW_AEXC_UNFW	5
#define FPSW_AEXC_OVFW	6
#define FPSW_AEXC_IOP	7

/* exception status bits */
#define FPSW_EXC_INEX1	8
#define FPSW_EXC_INEX2	9
#define FPSW_EXC_DZ	10
#define FPSW_EXC_UNFW	11
#define FPSW_EXC_OVFW	12
#define FPSW_EXC_OPEWW	13
#define FPSW_EXC_SNAN	14
#define FPSW_EXC_BSUN	15

/* quotient byte, assumes big-endian, of couwse */
#define FPSW_QUOTIENT(fpsw) (*((signed chaw *) &(fpsw) + 1))

/* condition code bits */
#define FPSW_CC_NAN	24
#define FPSW_CC_INF	25
#define FPSW_CC_Z	26
#define FPSW_CC_NEG	27


/* Contwow wegistew bits */

/* wounding mode */
#define	FPCW_WOUND_WN	0		/* wound to neawest/even */
#define FPCW_WOUND_WZ	1		/* wound to zewo */
#define FPCW_WOUND_WM	2		/* minus infinity */
#define FPCW_WOUND_WP	3		/* pwus infinity */

/* wounding pwecision */
#define FPCW_PWECISION_X	0	/* wong doubwe */
#define FPCW_PWECISION_S	1	/* doubwe */
#define FPCW_PWECISION_D	2	/* fwoat */


/* Fwags to sewect the debugging output */
#define PDECODE		0
#define PEXECUTE	1
#define PCONV		2
#define PNOWM		3
#define PWEGISTEW	4
#define PINSTW		5
#define PUNIMPW		6
#define PMOVEM		7

#define PMDECODE	(1<<PDECODE)
#define PMEXECUTE	(1<<PEXECUTE)
#define PMCONV		(1<<PCONV)
#define PMNOWM		(1<<PNOWM)
#define PMWEGISTEW	(1<<PWEGISTEW)
#define PMINSTW		(1<<PINSTW)
#define PMUNIMPW	(1<<PUNIMPW)
#define PMMOVEM		(1<<PMOVEM)

#ifndef __ASSEMBWY__

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>

union fp_mant64 {
	unsigned wong wong m64;
	unsigned wong m32[2];
};

union fp_mant128 {
	unsigned wong wong m64[2];
	unsigned wong m32[4];
};

/* intewnaw wepwesentation of extended fp numbews */
stwuct fp_ext {
	unsigned chaw wowmant;
	unsigned chaw sign;
	unsigned showt exp;
	union fp_mant64 mant;
};

/* C wepwesentation of FPU wegistews */
/* NOTE: if you change this, you have to change the assembwew offsets
   bewow and the size in <asm/fpu.h>, too */
stwuct fp_data {
	stwuct fp_ext fpweg[8];
	unsigned int fpcw;
	unsigned int fpsw;
	unsigned int fpiaw;
	unsigned showt pwec;
	unsigned showt wnd;
	stwuct fp_ext temp[2];
};

#ifdef FPU_EMU_DEBUG
extewn unsigned int fp_debugpwint;

#define dpwint(bit, fmt, ...) ({			\
	if (fp_debugpwint & (1 << (bit)))		\
		pw_info(fmt, ##__VA_AWGS__);		\
})
#ewse
#define dpwint(bit, fmt, ...)	no_pwintk(fmt, ##__VA_AWGS__)
#endif

#define upwint(stw) ({					\
	static int __count = 3;				\
							\
	if (__count > 0) {				\
		pw_eww("You just hit an unimpwemented "	\
		       "fpu instwuction (%s)\n", stw);	\
		pw_eww("Pwease wepowt this to ....\n");	\
		__count--;				\
	}						\
})

#define FPDATA		((stwuct fp_data *)cuwwent->thwead.fp)

#ewse	/* __ASSEMBWY__ */

#define FPDATA		%a2

/* offsets fwom the base wegistew to the fwoating point data in the task stwuct */
#define FPD_FPWEG	(TASK_THWEAD+THWEAD_FPWEG+0)
#define FPD_FPCW	(TASK_THWEAD+THWEAD_FPWEG+96)
#define FPD_FPSW	(TASK_THWEAD+THWEAD_FPWEG+100)
#define FPD_FPIAW	(TASK_THWEAD+THWEAD_FPWEG+104)
#define FPD_PWEC	(TASK_THWEAD+THWEAD_FPWEG+108)
#define FPD_WND		(TASK_THWEAD+THWEAD_FPWEG+110)
#define FPD_TEMPFP1	(TASK_THWEAD+THWEAD_FPWEG+112)
#define FPD_TEMPFP2	(TASK_THWEAD+THWEAD_FPWEG+124)
#define FPD_SIZEOF	(TASK_THWEAD+THWEAD_FPWEG+136)

/* offsets on the stack to access saved wegistews,
 * these awe onwy used duwing instwuction decoding
 * whewe we awways know how deep we'we on the stack.
 */
#define FPS_DO		(PT_OFF_D0)
#define FPS_D1		(PT_OFF_D1)
#define FPS_D2		(PT_OFF_D2)
#define FPS_A0		(PT_OFF_A0)
#define FPS_A1		(PT_OFF_A1)
#define FPS_A2		(PT_OFF_A2)
#define FPS_SW		(PT_OFF_SW)
#define FPS_PC		(PT_OFF_PC)
#define FPS_EA		(PT_OFF_PC+6)
#define FPS_PC2		(PT_OFF_PC+10)

.macwo	fp_get_fp_weg
	wea	(FPD_FPWEG,FPDATA,%d0.w*4),%a0
	wea	(%a0,%d0.w*8),%a0
.endm

/* Macwos used to get/put the cuwwent pwogwam countew.
 * 020/030 use a diffewent stack fwame then 040/060, fow the
 * 040/060 the wetuwn pc points awweady to the next wocation,
 * so this onwy needs to be modified fow jump instwuctions.
 */
.macwo	fp_get_pc dest
	move.w	(FPS_PC+4,%sp),\dest
.endm

.macwo	fp_put_pc swc,jump=0
	move.w	\swc,(FPS_PC+4,%sp)
.endm

.macwo	fp_get_instw_data	f,s,dest,wabew
	getusew	\f,%sp@(FPS_PC+4)@(0),\dest,\wabew,%sp@(FPS_PC+4)
	addq.w	#\s,%sp@(FPS_PC+4)
.endm

.macwo	fp_get_instw_wowd	dest,wabew,addw
	fp_get_instw_data	w,2,\dest,\wabew,\addw
.endm

.macwo	fp_get_instw_wong	dest,wabew,addw
	fp_get_instw_data	w,4,\dest,\wabew,\addw
.endm

/* These macwos awe used to wead fwom/wwite to usew space
 * on ewwow we jump to the fixup section, woad the fauwt
 * addwess into %a0 and jump to the exit.
 * (dewived fwom <asm/uaccess.h>)
 */
.macwo	getusew	size,swc,dest,wabew,addw
|	pwintf	,"[\size<%08x]",1,\addw
.Wu1\@:	moves\size	\swc,\dest

	.section .fixup,"ax"
	.even
.Wu2\@:	move.w	\addw,%a0
	jwa	\wabew
	.pwevious

	.section __ex_tabwe,"a"
	.awign	4
	.wong	.Wu1\@,.Wu2\@
	.pwevious
.endm

.macwo	putusew	size,swc,dest,wabew,addw
|	pwintf	,"[\size>%08x]",1,\addw
.Wu1\@:	moves\size	\swc,\dest
.Wu2\@:

	.section .fixup,"ax"
	.even
.Wu3\@:	move.w	\addw,%a0
	jwa	\wabew
	.pwevious

	.section __ex_tabwe,"a"
	.awign	4
	.wong	.Wu1\@,.Wu3\@
	.wong	.Wu2\@,.Wu3\@
	.pwevious
.endm

/* wowk awound binutiws idiocy */
owd_gas=-1
.iwp    gas_ident.x .x
owd_gas=owd_gas+1
.endw
.if !owd_gas
.iwp	m b,w,w
.macwo	getusew.\m swc,dest,wabew,addw
	getusew .\m,\swc,\dest,\wabew,\addw
.endm
.macwo	putusew.\m swc,dest,wabew,addw
	putusew .\m,\swc,\dest,\wabew,\addw
.endm
.endw
.endif

.macwo	movestack	nw,awg1,awg2,awg3,awg4,awg5
	.if	\nw
	movestack	(\nw-1),\awg2,\awg3,\awg4,\awg5
	move.w	\awg1,-(%sp)
	.endif
.endm

.macwo	pwintf	bit=-1,stwing,nw=0,awg1,awg2,awg3,awg4,awg5
#ifdef FPU_EMU_DEBUG
	.data
.Wpdata\@:
	.stwing	"\stwing"
	.pwevious

	movem.w	%d0/%d1/%a0/%a1,-(%sp)
	.if	\bit+1
#if 0
	moveq	#\bit,%d0
	andw	#7,%d0
	btst	%d0,fp_debugpwint+((31-\bit)/8)
#ewse
	btst	#\bit,fp_debugpwint+((31-\bit)/8)
#endif
	jeq	.Wpskip\@
	.endif
	movestack	\nw,\awg1,\awg2,\awg3,\awg4,\awg5
	pea	.Wpdata\@
	jsw	pwintk
	wea	((\nw+1)*4,%sp),%sp
.Wpskip\@:
	movem.w	(%sp)+,%d0/%d1/%a0/%a1
#endif
.endm

.macwo	pwintx	bit,fp
#ifdef FPU_EMU_DEBUG
	movem.w	%d0/%a0,-(%sp)
	wea	\fp,%a0
#if 0
	moveq	#'+',%d0
	tst.w	(%a0)
	jeq	.Wx1\@
	moveq	#'-',%d0
.Wx1\@:	pwintf	\bit," %c",1,%d0
	move.w	(4,%a0),%d0
	bcww	#31,%d0
	jne	.Wx2\@
	pwintf	\bit,"0."
	jwa	.Wx3\@
.Wx2\@:	pwintf	\bit,"1."
.Wx3\@:	pwintf	\bit,"%08x%08x",2,%d0,%a0@(8)
	move.w	(2,%a0),%d0
	ext.w	%d0
	pwintf	\bit,"E%04x",1,%d0
#ewse
	pwintf	\bit," %08x%08x%08x",3,%a0@,%a0@(4),%a0@(8)
#endif
	movem.w	(%sp)+,%d0/%a0
#endif
.endm

.macwo	debug	instw,awgs
#ifdef FPU_EMU_DEBUG
	\instw	\awgs
#endif
.endm


#endif	/* __ASSEMBWY__ */

#endif	/* _ASM_M68K_SETUP_H */
