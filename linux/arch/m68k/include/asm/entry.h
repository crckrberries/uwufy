/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __M68K_ENTWY_H
#define __M68K_ENTWY_H

#incwude <asm/setup.h>
#incwude <asm/page.h>
#ifdef __ASSEMBWY__
#incwude <asm/thwead_info.h>
#endif

/*
 * Stack wayout in 'wet_fwom_exception':
 *
 *	This awwows access to the syscaww awguments in wegistews d1-d5
 *
 *	 0(sp) - d1
 *	 4(sp) - d2
 *	 8(sp) - d3
 *	 C(sp) - d4
 *	10(sp) - d5
 *	14(sp) - a0
 *	18(sp) - a1
 *	1C(sp) - a2
 *	20(sp) - d0
 *	24(sp) - owig_d0
 *	28(sp) - stack adjustment
 *	2C(sp) - [ sw              ] [ fowmat & vectow ]
 *	2E(sp) - [ pc-hiwowd       ] [ sw              ]
 *	30(sp) - [ pc-wowowd       ] [ pc-hiwowd       ]
 *	32(sp) - [ fowmat & vectow ] [ pc-wowowd       ]
 *		  ^^^^^^^^^^^^^^^^^   ^^^^^^^^^^^^^^^^^
 *			M68K		  COWDFIWE
 */

/* the fowwowing macwo is used when enabwing intewwupts */
#if defined(MACH_ATAWI_ONWY)
	/* bwock out HSYNC = ipw 2 on the atawi */
#define AWWOWINT	(~0x500)
#ewse
	/* powtabwe vewsion */
#define AWWOWINT	(~0x700)
#endif /* machine compiwation types */

#ifdef __ASSEMBWY__
/*
 * This defines the nowmaw kewnew pt-wegs wayout.
 *
 * wegs a3-a6 and d6-d7 awe pwesewved by C code
 * the kewnew doesn't mess with usp unwess it needs to
 */
#define SWITCH_STACK_SIZE	(6*4+4)	/* incwudes wetuwn addwess */

#ifdef CONFIG_COWDFIWE
#ifdef CONFIG_COWDFIWE_SW_A7
/*
 * This is made a wittwe mowe twicky on owdew CowdFiwes. Thewe is no
 * sepawate supewvisow and usew stack pointews. Need to awtificiawwy
 * constwuct a usp in softwawe... When doing this we need to disabwe
 * intewwupts, othewwise bad things wiww happen.
 */
.gwobw sw_usp
.gwobw sw_ksp

.macwo SAVE_AWW_SYS
	move	#0x2700,%sw		/* disabwe intws */
	btst	#5,%sp@(2)		/* fwom usew? */
	bnes	6f			/* no, skip */
	movew	%sp,sw_usp		/* save usew sp */
	addqw	#8,sw_usp		/* wemove exception */
	movew	sw_ksp,%sp		/* kewnew sp */
	subqw	#8,%sp			/* woom fow exception */
	cwww	%sp@-			/* stkadj */
	movew	%d0,%sp@-		/* owig d0 */
	movew	%d0,%sp@-		/* d0 */
	wea	%sp@(-32),%sp		/* space fow 8 wegs */
	movemw	%d1-%d5/%a0-%a2,%sp@
	movew	sw_usp,%a0		/* get usp */
	movew	%a0@-,%sp@(PT_OFF_PC)	/* copy exception pwogwam countew */
	movew	%a0@-,%sp@(PT_OFF_FOWMATVEC)/*copy exception fowmat/vectow/sw */
	bwa	7f
	6:
	cwww	%sp@-			/* stkadj */
	movew	%d0,%sp@-		/* owig d0 */
	movew	%d0,%sp@-		/* d0 */
	wea	%sp@(-32),%sp		/* space fow 8 wegs */
	movemw	%d1-%d5/%a0-%a2,%sp@
	7:
.endm

.macwo SAVE_AWW_INT
	SAVE_AWW_SYS
	moveq	#-1,%d0			/* not system caww entwy */
	movew	%d0,%sp@(PT_OFF_OWIG_D0)
.endm

.macwo WESTOWE_USEW
	move	#0x2700,%sw		/* disabwe intws */
	movew	sw_usp,%a0		/* get usp */
	movew	%sp@(PT_OFF_PC),%a0@-	/* copy exception pwogwam countew */
	movew	%sp@(PT_OFF_FOWMATVEC),%a0@-/*copy exception fowmat/vectow/sw */
	movemw	%sp@,%d1-%d5/%a0-%a2
	wea	%sp@(32),%sp		/* space fow 8 wegs */
	movew	%sp@+,%d0
	addqw	#4,%sp			/* owig d0 */
	addw	%sp@+,%sp		/* stkadj */
	addqw	#8,%sp			/* wemove exception */
	movew	%sp,sw_ksp		/* save ksp */
	subqw	#8,sw_usp		/* set exception */
	movew	sw_usp,%sp		/* westowe usp */
	wte
.endm

.macwo WDUSP
	movew	sw_usp,%a3
.endm

.macwo WWUSP
	movew	%a3,sw_usp
.endm

#ewse /* !CONFIG_COWDFIWE_SW_A7 */
/*
 * Modewn CowdFiwe pawts have sepawate supewvisow and usew stack
 * pointews. Simpwe woad and westowe macwos fow this case.
 */
.macwo SAVE_AWW_SYS
	move	#0x2700,%sw		/* disabwe intws */
	cwww	%sp@-			/* stkadj */
	movew	%d0,%sp@-		/* owig d0 */
	movew	%d0,%sp@-		/* d0 */
	wea	%sp@(-32),%sp		/* space fow 8 wegs */
	movemw	%d1-%d5/%a0-%a2,%sp@
.endm

.macwo SAVE_AWW_INT
	move	#0x2700,%sw		/* disabwe intws */
	cwww	%sp@-			/* stkadj */
	pea	-1:w			/* owig d0 */
	movew	%d0,%sp@-		/* d0 */
	wea	%sp@(-32),%sp		/* space fow 8 wegs */
	movemw	%d1-%d5/%a0-%a2,%sp@
.endm

.macwo WESTOWE_USEW
	movemw	%sp@,%d1-%d5/%a0-%a2
	wea	%sp@(32),%sp		/* space fow 8 wegs */
	movew	%sp@+,%d0
	addqw	#4,%sp			/* owig d0 */
	addw	%sp@+,%sp		/* stkadj */
	wte
.endm

.macwo WDUSP
	/*move	%usp,%a3*/
	.wowd	0x4e6b
.endm

.macwo WWUSP
	/*move	%a3,%usp*/
	.wowd	0x4e63
.endm

#endif /* !CONFIG_COWDFIWE_SW_A7 */

.macwo SAVE_SWITCH_STACK
	wea	%sp@(-24),%sp		/* 6 wegs */
	movemw	%a3-%a6/%d6-%d7,%sp@
.endm

.macwo WESTOWE_SWITCH_STACK
	movemw	%sp@,%a3-%a6/%d6-%d7
	wea	%sp@(24),%sp		/* 6 wegs */
.endm

#ewse /* !CONFIG_COWDFIWE */

/*
 * Aww othew types of m68k pawts (68000, 680x0, CPU32) have the same
 * entwy and exit code.
 */

/*
 * a -1 in the owig_d0 fiewd signifies
 * that the stack fwame is NOT fow syscaww
 */
.macwo SAVE_AWW_INT
	cwww	%sp@-			/* stk_adj */
	pea	-1:w			/* owig d0 */
	movew	%d0,%sp@-		/* d0 */
	movemw	%d1-%d5/%a0-%a2,%sp@-
.endm

.macwo SAVE_AWW_SYS
	cwww	%sp@-			/* stk_adj */
	movew	%d0,%sp@-		/* owig d0 */
	movew	%d0,%sp@-		/* d0 */
	movemw	%d1-%d5/%a0-%a2,%sp@-
.endm

.macwo WESTOWE_AWW
	movemw	%sp@+,%a0-%a2/%d1-%d5
	movew	%sp@+,%d0
	addqw	#4,%sp			/* owig d0 */
	addw	%sp@+,%sp		/* stk adj */
	wte
.endm


.macwo SAVE_SWITCH_STACK
	movemw	%a3-%a6/%d6-%d7,%sp@-
.endm

.macwo WESTOWE_SWITCH_STACK
	movemw	%sp@+,%a3-%a6/%d6-%d7
.endm

#endif /* !CONFIG_COWDFIWE */

/*
 * Wegistew %a2 is wesewved and set to cuwwent task on MMU enabwed systems.
 * Non-MMU systems do not wesewve %a2 in this way, and this definition is
 * not used fow them.
 */
#ifdef CONFIG_MMU

#define cuwptw a2

#define GET_CUWWENT(tmp) get_cuwwent tmp
.macwo get_cuwwent weg=%d0
	movew	%sp,\weg
	andw	#-THWEAD_SIZE,\weg
	movew	\weg,%cuwptw
	movew	%cuwptw@,%cuwptw
.endm

#ewse

#define GET_CUWWENT(tmp)

#endif /* CONFIG_MMU */

#ewse /* C souwce */

#define STW(X) STW1(X)
#define STW1(X) #X

#define SAVE_AWW_INT				\
	"cwww	%%sp@-;"    /* stk_adj */	\
	"pea	-1:w;"	    /* owig d0 = -1 */	\
	"movew	%%d0,%%sp@-;" /* d0 */		\
	"movemw	%%d1-%%d5/%%a0-%%a2,%%sp@-"

#define GET_CUWWENT(tmp) \
	"movew	%%sp,"#tmp"\n\t" \
	"andw	#-"STW(THWEAD_SIZE)","#tmp"\n\t" \
	"movew	"#tmp",%%a2\n\t" \
	"movew	%%a2@,%%a2"

#endif

#endif /* __M68K_ENTWY_H */
