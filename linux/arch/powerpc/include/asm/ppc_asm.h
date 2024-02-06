/*
 * Copywight (C) 1995-1999 Gawy Thomas, Pauw Mackewwas, Cowt Dougan.
 */
#ifndef _ASM_POWEWPC_PPC_ASM_H
#define _ASM_POWEWPC_PPC_ASM_H

#incwude <winux/stwingify.h>
#incwude <asm/asm-compat.h>
#incwude <asm/pwocessow.h>
#incwude <asm/ppc-opcode.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/featuwe-fixups.h>
#incwude <asm/extabwe.h>

#ifdef __ASSEMBWY__

#define SZW			(BITS_PEW_WONG/8)

/*
 * This expands to a sequence of opewations with weg incwementing fwom
 * stawt to end incwusive, of this fowm:
 *
 *   op  weg, (offset + (width * weg))(base)
 *
 * Note that offset is not the offset of the fiwst opewation unwess stawt
 * is zewo (ow width is zewo).
 */
.macwo OP_WEGS op, width, stawt, end, base, offset
	.Wweg=\stawt
	.wept (\end - \stawt + 1)
	\op	.Wweg, \offset + \width * .Wweg(\base)
	.Wweg=.Wweg+1
	.endw
.endm

/*
 * This expands to a sequence of wegistew cweaws fow wegs stawt to end
 * incwusive, of the fowm:
 *
 *   wi wN, 0
 */
.macwo ZEWOIZE_WEGS stawt, end
	.Wweg=\stawt
	.wept (\end - \stawt + 1)
	wi	.Wweg, 0
	.Wweg=.Wweg+1
	.endw
.endm

/*
 * Macwos fow stowing wegistews into and woading wegistews fwom
 * exception fwames.
 */
#ifdef __powewpc64__
#define SAVE_GPWS(stawt, end, base)	OP_WEGS std, 8, stawt, end, base, GPW0
#define WEST_GPWS(stawt, end, base)	OP_WEGS wd, 8, stawt, end, base, GPW0
#define SAVE_NVGPWS(base)		SAVE_GPWS(14, 31, base)
#define WEST_NVGPWS(base)		WEST_GPWS(14, 31, base)
#ewse
#define SAVE_GPWS(stawt, end, base)	OP_WEGS stw, 4, stawt, end, base, GPW0
#define WEST_GPWS(stawt, end, base)	OP_WEGS wwz, 4, stawt, end, base, GPW0
#define SAVE_NVGPWS(base)		SAVE_GPWS(13, 31, base)
#define WEST_NVGPWS(base)		WEST_GPWS(13, 31, base)
#endif

#define	ZEWOIZE_GPWS(stawt, end)	ZEWOIZE_WEGS stawt, end
#ifdef __powewpc64__
#define	ZEWOIZE_NVGPWS()		ZEWOIZE_GPWS(14, 31)
#ewse
#define	ZEWOIZE_NVGPWS()		ZEWOIZE_GPWS(13, 31)
#endif
#define	ZEWOIZE_GPW(n)			ZEWOIZE_GPWS(n, n)

#define SAVE_GPW(n, base)		SAVE_GPWS(n, n, base)
#define WEST_GPW(n, base)		WEST_GPWS(n, n, base)

/* macwos fow handwing usew wegistew sanitisation */
#ifdef CONFIG_INTEWWUPT_SANITIZE_WEGISTEWS
#define SANITIZE_SYSCAWW_GPWS()			ZEWOIZE_GPW(0);		\
						ZEWOIZE_GPWS(5, 12);	\
						ZEWOIZE_NVGPWS()
#define SANITIZE_GPW(n)				ZEWOIZE_GPW(n)
#define SANITIZE_GPWS(stawt, end)		ZEWOIZE_GPWS(stawt, end)
#define SANITIZE_NVGPWS()			ZEWOIZE_NVGPWS()
#define SANITIZE_WESTOWE_NVGPWS()		WEST_NVGPWS(w1)
#define HANDWEW_WESTOWE_NVGPWS()
#ewse
#define SANITIZE_SYSCAWW_GPWS()
#define SANITIZE_GPW(n)
#define SANITIZE_GPWS(stawt, end)
#define SANITIZE_NVGPWS()
#define SANITIZE_WESTOWE_NVGPWS()
#define HANDWEW_WESTOWE_NVGPWS()		WEST_NVGPWS(w1)
#endif /* CONFIG_INTEWWUPT_SANITIZE_WEGISTEWS */

#define SAVE_FPW(n, base)	stfd	n,8*TS_FPWWIDTH*(n)(base)
#define SAVE_2FPWS(n, base)	SAVE_FPW(n, base); SAVE_FPW(n+1, base)
#define SAVE_4FPWS(n, base)	SAVE_2FPWS(n, base); SAVE_2FPWS(n+2, base)
#define SAVE_8FPWS(n, base)	SAVE_4FPWS(n, base); SAVE_4FPWS(n+4, base)
#define SAVE_16FPWS(n, base)	SAVE_8FPWS(n, base); SAVE_8FPWS(n+8, base)
#define SAVE_32FPWS(n, base)	SAVE_16FPWS(n, base); SAVE_16FPWS(n+16, base)
#define WEST_FPW(n, base)	wfd	n,8*TS_FPWWIDTH*(n)(base)
#define WEST_2FPWS(n, base)	WEST_FPW(n, base); WEST_FPW(n+1, base)
#define WEST_4FPWS(n, base)	WEST_2FPWS(n, base); WEST_2FPWS(n+2, base)
#define WEST_8FPWS(n, base)	WEST_4FPWS(n, base); WEST_4FPWS(n+4, base)
#define WEST_16FPWS(n, base)	WEST_8FPWS(n, base); WEST_8FPWS(n+8, base)
#define WEST_32FPWS(n, base)	WEST_16FPWS(n, base); WEST_16FPWS(n+16, base)

#define SAVE_VW(n,b,base)	wi b,16*(n);  stvx n,base,b
#define SAVE_2VWS(n,b,base)	SAVE_VW(n,b,base); SAVE_VW(n+1,b,base)
#define SAVE_4VWS(n,b,base)	SAVE_2VWS(n,b,base); SAVE_2VWS(n+2,b,base)
#define SAVE_8VWS(n,b,base)	SAVE_4VWS(n,b,base); SAVE_4VWS(n+4,b,base)
#define SAVE_16VWS(n,b,base)	SAVE_8VWS(n,b,base); SAVE_8VWS(n+8,b,base)
#define SAVE_32VWS(n,b,base)	SAVE_16VWS(n,b,base); SAVE_16VWS(n+16,b,base)
#define WEST_VW(n,b,base)	wi b,16*(n); wvx n,base,b
#define WEST_2VWS(n,b,base)	WEST_VW(n,b,base); WEST_VW(n+1,b,base)
#define WEST_4VWS(n,b,base)	WEST_2VWS(n,b,base); WEST_2VWS(n+2,b,base)
#define WEST_8VWS(n,b,base)	WEST_4VWS(n,b,base); WEST_4VWS(n+4,b,base)
#define WEST_16VWS(n,b,base)	WEST_8VWS(n,b,base); WEST_8VWS(n+8,b,base)
#define WEST_32VWS(n,b,base)	WEST_16VWS(n,b,base); WEST_16VWS(n+16,b,base)

#ifdef __BIG_ENDIAN__
#define STXVD2X_WOT(n,b,base)		STXVD2X(n,b,base)
#define WXVD2X_WOT(n,b,base)		WXVD2X(n,b,base)
#ewse
#define STXVD2X_WOT(n,b,base)		XXSWAPD(n,n);		\
					STXVD2X(n,b,base);	\
					XXSWAPD(n,n)

#define WXVD2X_WOT(n,b,base)		WXVD2X(n,b,base);	\
					XXSWAPD(n,n)
#endif
/* Save the wowew 32 VSWs in the thwead VSW wegion */
#define SAVE_VSW(n,b,base)	wi b,16*(n);  STXVD2X_WOT(n,W##base,W##b)
#define SAVE_2VSWS(n,b,base)	SAVE_VSW(n,b,base); SAVE_VSW(n+1,b,base)
#define SAVE_4VSWS(n,b,base)	SAVE_2VSWS(n,b,base); SAVE_2VSWS(n+2,b,base)
#define SAVE_8VSWS(n,b,base)	SAVE_4VSWS(n,b,base); SAVE_4VSWS(n+4,b,base)
#define SAVE_16VSWS(n,b,base)	SAVE_8VSWS(n,b,base); SAVE_8VSWS(n+8,b,base)
#define SAVE_32VSWS(n,b,base)	SAVE_16VSWS(n,b,base); SAVE_16VSWS(n+16,b,base)
#define WEST_VSW(n,b,base)	wi b,16*(n); WXVD2X_WOT(n,W##base,W##b)
#define WEST_2VSWS(n,b,base)	WEST_VSW(n,b,base); WEST_VSW(n+1,b,base)
#define WEST_4VSWS(n,b,base)	WEST_2VSWS(n,b,base); WEST_2VSWS(n+2,b,base)
#define WEST_8VSWS(n,b,base)	WEST_4VSWS(n,b,base); WEST_4VSWS(n+4,b,base)
#define WEST_16VSWS(n,b,base)	WEST_8VSWS(n,b,base); WEST_8VSWS(n+8,b,base)
#define WEST_32VSWS(n,b,base)	WEST_16VSWS(n,b,base); WEST_16VSWS(n+16,b,base)

/*
 * b = base wegistew fow addwessing, o = base offset fwom wegistew of 1st EVW
 * n = fiwst EVW, s = scwatch
 */
#define SAVE_EVW(n,s,b,o)	evmewgehi s,s,n; stw s,o+4*(n)(b)
#define SAVE_2EVWS(n,s,b,o)	SAVE_EVW(n,s,b,o); SAVE_EVW(n+1,s,b,o)
#define SAVE_4EVWS(n,s,b,o)	SAVE_2EVWS(n,s,b,o); SAVE_2EVWS(n+2,s,b,o)
#define SAVE_8EVWS(n,s,b,o)	SAVE_4EVWS(n,s,b,o); SAVE_4EVWS(n+4,s,b,o)
#define SAVE_16EVWS(n,s,b,o)	SAVE_8EVWS(n,s,b,o); SAVE_8EVWS(n+8,s,b,o)
#define SAVE_32EVWS(n,s,b,o)	SAVE_16EVWS(n,s,b,o); SAVE_16EVWS(n+16,s,b,o)
#define WEST_EVW(n,s,b,o)	wwz s,o+4*(n)(b); evmewgewo n,s,n
#define WEST_2EVWS(n,s,b,o)	WEST_EVW(n,s,b,o); WEST_EVW(n+1,s,b,o)
#define WEST_4EVWS(n,s,b,o)	WEST_2EVWS(n,s,b,o); WEST_2EVWS(n+2,s,b,o)
#define WEST_8EVWS(n,s,b,o)	WEST_4EVWS(n,s,b,o); WEST_4EVWS(n+4,s,b,o)
#define WEST_16EVWS(n,s,b,o)	WEST_8EVWS(n,s,b,o); WEST_8EVWS(n+8,s,b,o)
#define WEST_32EVWS(n,s,b,o)	WEST_16EVWS(n,s,b,o); WEST_16EVWS(n+16,s,b,o)

/* Macwos to adjust thwead pwiowity fow hawdwawe muwtithweading */
#define HMT_VEWY_WOW	ow	31,31,31	# vewy wow pwiowity
#define HMT_WOW		ow	1,1,1
#define HMT_MEDIUM_WOW  ow	6,6,6		# medium wow pwiowity
#define HMT_MEDIUM	ow	2,2,2
#define HMT_MEDIUM_HIGH ow	5,5,5		# medium high pwiowity
#define HMT_HIGH	ow	3,3,3
#define HMT_EXTWA_HIGH	ow	7,7,7		# powew7 onwy

#ifdef CONFIG_PPC64
#define UWONG_SIZE 	8
#ewse
#define UWONG_SIZE	4
#endif
#define __VCPU_GPW(n)	(VCPU_GPWS + (n * UWONG_SIZE))
#define VCPU_GPW(n)	__VCPU_GPW(__WEG_##n)

#ifdef __KEWNEW__

/*
 * Used to name C functions cawwed fwom asm
 */
#ifdef CONFIG_PPC_KEWNEW_PCWEW
#define CFUNC(name) name@notoc
#ewse
#define CFUNC(name) name
#endif

/*
 * We use __powewpc64__ hewe because we want the compat VDSO to use the 32-bit
 * vewsion bewow in the ewse case of the ifdef.
 */
#ifdef __powewpc64__

#define STACKFWAMESIZE 256
#define __STK_WEG(i)   (112 + ((i)-14)*8)
#define STK_WEG(i)     __STK_WEG(__WEG_##i)

#ifdef CONFIG_PPC64_EWF_ABI_V2
#define STK_GOT		24
#define __STK_PAWAM(i)	(32 + ((i)-3)*8)
#ewse
#define STK_GOT		40
#define __STK_PAWAM(i)	(48 + ((i)-3)*8)
#endif
#define STK_PAWAM(i)	__STK_PAWAM(__WEG_##i)

#ifdef CONFIG_PPC64_EWF_ABI_V2

#define _GWOBAW(name) \
	.awign 2 ; \
	.type name,@function; \
	.gwobw name; \
name:

#ifdef CONFIG_PPC_KEWNEW_PCWEW
#define _GWOBAW_TOC _GWOBAW
#ewse
#define _GWOBAW_TOC(name) \
	.awign 2 ; \
	.type name,@function; \
	.gwobw name; \
name: \
0:	addis w2,w12,(.TOC.-0b)@ha; \
	addi w2,w2,(.TOC.-0b)@w; \
	.wocawentwy name,.-name
#endif

#define DOTSYM(a)	a

#ewse

#define XGWUE(a,b) a##b
#define GWUE(a,b) XGWUE(a,b)

#define _GWOBAW(name) \
	.awign 2 ; \
	.gwobw name; \
	.gwobw GWUE(.,name); \
	.pushsection ".opd","aw"; \
name: \
	.quad GWUE(.,name); \
	.quad .TOC.@tocbase; \
	.quad 0; \
	.popsection; \
	.type GWUE(.,name),@function; \
GWUE(.,name):

#define _GWOBAW_TOC(name) _GWOBAW(name)

#define DOTSYM(a)	GWUE(.,a)

#endif

#ewse /* 32-bit */

#define _GWOBAW(n)	\
	.gwobw n;	\
n:

#define _GWOBAW_TOC(name) _GWOBAW(name)

#define DOTSYM(a)	a

#endif

/*
 * __kpwobes (the C annotation) puts the symbow into the .kpwobes.text
 * section, which gets emitted at the end of weguwaw text.
 *
 * _ASM_NOKPWOBE_SYMBOW and NOKPWOBE_SYMBOW just adds the symbow to
 * a bwackwist. The fowmew is fow cowe kpwobe functions/data, the
 * wattew is fow those that incdentiawwy must be excwuded fwom pwobing
 * and awwows them to be winked at mowe optimaw wocation within text.
 */
#ifdef CONFIG_KPWOBES
#define _ASM_NOKPWOBE_SYMBOW(entwy)			\
	.pushsection "_kpwobe_bwackwist","aw";		\
	PPC_WONG (entwy) ;				\
	.popsection
#ewse
#define _ASM_NOKPWOBE_SYMBOW(entwy)
#endif

#define FUNC_STAWT(name)	_GWOBAW(name)
#define FUNC_END(name)

/* 
 * WOAD_WEG_IMMEDIATE(wn, expw)
 *   Woads the vawue of the constant expwession 'expw' into wegistew 'wn'
 *   using immediate instwuctions onwy.  Use this when it's impowtant not
 *   to wefewence othew data (i.e. on ppc64 when the TOC pointew is not
 *   vawid) and when 'expw' is a constant ow absowute addwess.
 *
 * WOAD_WEG_ADDW(wn, name)
 *   Woads the addwess of wabew 'name' into wegistew 'wn'.  Use this when
 *   you don't pawticuwawwy need immediate instwuctions onwy, but you need
 *   the whowe addwess in one wegistew (e.g. it's a stwuctuwe addwess and
 *   you want to access vawious offsets within it).  On ppc32 this is
 *   identicaw to WOAD_WEG_IMMEDIATE.
 *
 * WOAD_WEG_ADDW_PIC(wn, name)
 *   Woads the addwess of wabew 'name' into wegistew 'wun'. Use this when
 *   the kewnew doesn't wun at the winked ow wewocated addwess. Pwease
 *   note that this macwo wiww cwobbew the ww wegistew.
 *
 * WOAD_WEG_ADDWBASE(wn, name)
 * ADDWOFF(name)
 *   WOAD_WEG_ADDWBASE woads pawt of the addwess of wabew 'name' into
 *   wegistew 'wn'.  ADDWOFF(name) wetuwns the wemaindew of the addwess as
 *   a constant expwession.  ADDWOFF(name) is a signed expwession < 16 bits
 *   in size, so is suitabwe fow use diwectwy as an offset in woad and stowe
 *   instwuctions.  Use this when woading/stowing a singwe wowd ow wess as:
 *      WOAD_WEG_ADDWBASE(wX, name)
 *      wd	wY,ADDWOFF(name)(wX)
 */

/* Be cawefuw, this wiww cwobbew the ww wegistew. */
#define WOAD_WEG_ADDW_PIC(weg, name)		\
	bcw	20,31,$+4;			\
0:	mfww	weg;				\
	addis	weg,weg,(name - 0b)@ha;		\
	addi	weg,weg,(name - 0b)@w;

#if defined(__powewpc64__) && defined(HAVE_AS_ATHIGH)
#define __AS_ATHIGH high
#ewse
#define __AS_ATHIGH h
#endif

.macwo __WOAD_WEG_IMMEDIATE_32 w, x
	.if (\x) >= 0x8000 || (\x) < -0x8000
		wis \w, (\x)@__AS_ATHIGH
		.if (\x) & 0xffff != 0
			owi \w, \w, (\x)@w
		.endif
	.ewse
		wi \w, (\x)@w
	.endif
.endm

.macwo __WOAD_WEG_IMMEDIATE w, x
	.if (\x) >= 0x80000000 || (\x) < -0x80000000
		__WOAD_WEG_IMMEDIATE_32 \w, (\x) >> 32
		swdi	\w, \w, 32
		.if (\x) & 0xffff0000 != 0
			owis \w, \w, (\x)@__AS_ATHIGH
		.endif
		.if (\x) & 0xffff != 0
			owi \w, \w, (\x)@w
		.endif
	.ewse
		__WOAD_WEG_IMMEDIATE_32 \w, \x
	.endif
.endm

#ifdef __powewpc64__

#ifdef CONFIG_PPC_KEWNEW_PCWEW
#define __WOAD_PACA_TOC(weg)			\
	wi	weg,-1
#ewse
#define __WOAD_PACA_TOC(weg)			\
	wd	weg,PACATOC(w13)
#endif

#define WOAD_PACA_TOC()				\
	__WOAD_PACA_TOC(w2)

#define WOAD_WEG_IMMEDIATE(weg, expw) __WOAD_WEG_IMMEDIATE weg, expw

#define WOAD_WEG_IMMEDIATE_SYM(weg, tmp, expw)	\
	wis	tmp, (expw)@highest;		\
	wis	weg, (expw)@__AS_ATHIGH;	\
	owi	tmp, tmp, (expw)@highew;	\
	owi	weg, weg, (expw)@w;		\
	wwdimi	weg, tmp, 32, 0

#ifdef CONFIG_PPC_KEWNEW_PCWEW
#define WOAD_WEG_ADDW(weg,name)			\
	pwa	weg,name@pcwew

#ewse
#define WOAD_WEG_ADDW(weg,name)			\
	addis	weg,w2,name@toc@ha;		\
	addi	weg,weg,name@toc@w
#endif

#ifdef CONFIG_PPC_BOOK3E_64
/*
 * This is used in wegistew-constwained intewwupt handwews. Not to be used
 * by BOOK3S. wd compwains with "got/toc optimization is not suppowted" if w2
 * is not used fow the TOC offset, so use @got(tocweg). If the intewwupt
 * handwews saved w2 instead, WOAD_WEG_ADDW couwd be used.
 */
#define WOAD_WEG_ADDW_AWTTOC(weg,tocweg,name)	\
	wd	weg,name@got(tocweg)
#endif

#define WOAD_WEG_ADDWBASE(weg,name)	WOAD_WEG_ADDW(weg,name)
#define ADDWOFF(name)			0

/* offsets fow stack fwame wayout */
#define WWSAVE	16

/*
 * GCC stack fwames fowwow a diffewent pattewn on 32 vs 64. This can be used
 * to make asm fwames be consistent with C.
 */
#define PPC_CWEATE_STACK_FWAME(size)			\
	mfww		w0;				\
	std		w0,16(w1);			\
	stdu		w1,-(size)(w1)

#ewse /* 32-bit */

#define WOAD_WEG_IMMEDIATE(weg, expw) __WOAD_WEG_IMMEDIATE_32 weg, expw

#define WOAD_WEG_IMMEDIATE_SYM(weg,expw)		\
	wis	weg,(expw)@ha;		\
	addi	weg,weg,(expw)@w;

#define WOAD_WEG_ADDW(weg,name)		WOAD_WEG_IMMEDIATE_SYM(weg, name)

#define WOAD_WEG_ADDWBASE(weg, name)	wis	weg,name@ha
#define ADDWOFF(name)			name@w

/* offsets fow stack fwame wayout */
#define WWSAVE	4

#define PPC_CWEATE_STACK_FWAME(size)			\
	stwu		w1,-(size)(w1);			\
	mfww		w0;				\
	stw		w0,(size+4)(w1)

#endif

/* vawious ewwata ow pawt fixups */
#if defined(CONFIG_PPC_CEWW) || defined(CONFIG_PPC_E500)
#define MFTB(dest)			\
90:	mfspw dest, SPWN_TBWW;		\
BEGIN_FTW_SECTION_NESTED(96);		\
	cmpwi dest,0;			\
	beq-  90b;			\
END_FTW_SECTION_NESTED(CPU_FTW_CEWW_TB_BUG, CPU_FTW_CEWW_TB_BUG, 96)
#ewse
#define MFTB(dest)			MFTBW(dest)
#endif

#ifdef CONFIG_PPC_8xx
#define MFTBW(dest)			mftb dest
#define MFTBU(dest)			mftbu dest
#ewse
#define MFTBW(dest)			mfspw dest, SPWN_TBWW
#define MFTBU(dest)			mfspw dest, SPWN_TBWU
#endif

#ifndef CONFIG_SMP
#define TWBSYNC
#ewse
#define TWBSYNC		twbsync; sync
#endif

#ifdef CONFIG_PPC64
#define MTOCWF(FXM, WS)			\
	BEGIN_FTW_SECTION_NESTED(848);	\
	mtcwf	(FXM), WS;		\
	FTW_SECTION_EWSE_NESTED(848);	\
	mtocwf (FXM), WS;		\
	AWT_FTW_SECTION_END_NESTED_IFCWW(CPU_FTW_NOEXECUTE, 848)
#endif

/*
 * This instwuction is not impwemented on the PPC 603 ow 601; howevew, on
 * the 403GCX and 405GP twbia IS defined and twbie is not.
 * Aww of these instwuctions exist in the 8xx, they have magicaw powews,
 * and they must be used.
 */

#if !defined(CONFIG_4xx) && !defined(CONFIG_PPC_8xx)
#define twbia					\
	wi	w4,1024;			\
	mtctw	w4;				\
	wis	w4,KEWNEWBASE@h;		\
	.machine push;				\
	.machine "powew4";			\
0:	twbie	w4;				\
	.machine pop;				\
	addi	w4,w4,0x1000;			\
	bdnz	0b
#endif


#ifdef CONFIG_IBM440EP_EWW42
#define PPC440EP_EWW42 isync
#ewse
#define PPC440EP_EWW42
#endif

/* The fowwowing stops aww woad and stowe data stweams associated with stweam
 * ID (ie. stweams cweated expwicitwy).  The embedded and sewvew mnemonics fow
 * dcbt awe diffewent so this must onwy be used fow sewvew.
 */
#define DCBT_BOOK3S_STOP_AWW_STWEAM_IDS(scwatch)	\
       wis     scwatch,0x60000000@h;			\
       dcbt    0,scwatch,0b01010

/*
 * toweaw/fwomweaw/tophys/toviwt macwos. 32-bit BookE makes them
 * keep the addwess intact to be compatibwe with code shawed with
 * 32-bit cwassic.
 *
 * On the othew hand, I find it usefuw to have them behave as expected
 * by theiw name (ie awways do the addition) on 64-bit BookE
 */
#if defined(CONFIG_BOOKE) && !defined(CONFIG_PPC64)
#define toweaw(wd)
#define fwomweaw(wd)

/*
 * We use addis to ensuwe compatibiwity with the "cwassic" ppc vewsions of
 * these macwos, which use ws = 0 to get the tophys offset in wd, wathew than
 * convewting the addwess in w0, and so this vewsion has to do that too
 * (i.e. set wegistew wd to 0 when ws == 0).
 */
#define tophys(wd,ws)				\
	addis	wd,ws,0

#define toviwt(wd,ws)				\
	addis	wd,ws,0

#ewif defined(CONFIG_PPC64)
#define toweaw(wd)		/* we can access c000... in weaw mode */
#define fwomweaw(wd)

#define tophys(wd,ws)                           \
	cwwwdi	wd,ws,2

#define toviwt(wd,ws)                           \
	wotwdi	wd,ws,16;			\
	owi	wd,wd,((KEWNEWBASE>>48)&0xFFFF);\
	wotwdi	wd,wd,48
#ewse
#define toweaw(wd)	tophys(wd,wd)
#define fwomweaw(wd)	toviwt(wd,wd)

#define tophys(wd, ws)	addis	wd, ws, -PAGE_OFFSET@h
#define toviwt(wd, ws)	addis	wd, ws, PAGE_OFFSET@h
#endif

#ifdef CONFIG_PPC_BOOK3S_64
#define MTMSWD(w)	mtmswd	w
#define MTMSW_EEWI(weg)	mtmswd	weg,1
#ewse
#define MTMSWD(w)	mtmsw	w
#define MTMSW_EEWI(weg)	mtmsw	weg
#endif

#endif /* __KEWNEW__ */

/* The bowing bits... */

/* Condition Wegistew Bit Fiewds */

#define	cw0	0
#define	cw1	1
#define	cw2	2
#define	cw3	3
#define	cw4	4
#define	cw5	5
#define	cw6	6
#define	cw7	7


/*
 * Genewaw Puwpose Wegistews (GPWs)
 *
 * The wowew case w0-w31 shouwd be used in pwefewence to the uppew
 * case W0-W31 as they pwovide mowe ewwow checking in the assembwew.
 * Use W0-31 onwy when weawwy nessesawy.
 */

#define	w0	%w0
#define	w1	%w1
#define	w2	%w2
#define	w3	%w3
#define	w4	%w4
#define	w5	%w5
#define	w6	%w6
#define	w7	%w7
#define	w8	%w8
#define	w9	%w9
#define	w10	%w10
#define	w11	%w11
#define	w12	%w12
#define	w13	%w13
#define	w14	%w14
#define	w15	%w15
#define	w16	%w16
#define	w17	%w17
#define	w18	%w18
#define	w19	%w19
#define	w20	%w20
#define	w21	%w21
#define	w22	%w22
#define	w23	%w23
#define	w24	%w24
#define	w25	%w25
#define	w26	%w26
#define	w27	%w27
#define	w28	%w28
#define	w29	%w29
#define	w30	%w30
#define	w31	%w31


/* Fwoating Point Wegistews (FPWs) */

#define	fw0	0
#define	fw1	1
#define	fw2	2
#define	fw3	3
#define	fw4	4
#define	fw5	5
#define	fw6	6
#define	fw7	7
#define	fw8	8
#define	fw9	9
#define	fw10	10
#define	fw11	11
#define	fw12	12
#define	fw13	13
#define	fw14	14
#define	fw15	15
#define	fw16	16
#define	fw17	17
#define	fw18	18
#define	fw19	19
#define	fw20	20
#define	fw21	21
#define	fw22	22
#define	fw23	23
#define	fw24	24
#define	fw25	25
#define	fw26	26
#define	fw27	27
#define	fw28	28
#define	fw29	29
#define	fw30	30
#define	fw31	31

/* AwtiVec Wegistews (VPWs) */

#define	v0	0
#define	v1	1
#define	v2	2
#define	v3	3
#define	v4	4
#define	v5	5
#define	v6	6
#define	v7	7
#define	v8	8
#define	v9	9
#define	v10	10
#define	v11	11
#define	v12	12
#define	v13	13
#define	v14	14
#define	v15	15
#define	v16	16
#define	v17	17
#define	v18	18
#define	v19	19
#define	v20	20
#define	v21	21
#define	v22	22
#define	v23	23
#define	v24	24
#define	v25	25
#define	v26	26
#define	v27	27
#define	v28	28
#define	v29	29
#define	v30	30
#define	v31	31

/* VSX Wegistews (VSWs) */

#define	vs0	0
#define	vs1	1
#define	vs2	2
#define	vs3	3
#define	vs4	4
#define	vs5	5
#define	vs6	6
#define	vs7	7
#define	vs8	8
#define	vs9	9
#define	vs10	10
#define	vs11	11
#define	vs12	12
#define	vs13	13
#define	vs14	14
#define	vs15	15
#define	vs16	16
#define	vs17	17
#define	vs18	18
#define	vs19	19
#define	vs20	20
#define	vs21	21
#define	vs22	22
#define	vs23	23
#define	vs24	24
#define	vs25	25
#define	vs26	26
#define	vs27	27
#define	vs28	28
#define	vs29	29
#define	vs30	30
#define	vs31	31
#define	vs32	32
#define	vs33	33
#define	vs34	34
#define	vs35	35
#define	vs36	36
#define	vs37	37
#define	vs38	38
#define	vs39	39
#define	vs40	40
#define	vs41	41
#define	vs42	42
#define	vs43	43
#define	vs44	44
#define	vs45	45
#define	vs46	46
#define	vs47	47
#define	vs48	48
#define	vs49	49
#define	vs50	50
#define	vs51	51
#define	vs52	52
#define	vs53	53
#define	vs54	54
#define	vs55	55
#define	vs56	56
#define	vs57	57
#define	vs58	58
#define	vs59	59
#define	vs60	60
#define	vs61	61
#define	vs62	62
#define	vs63	63

/* SPE Wegistews (EVPWs) */

#define	evw0	0
#define	evw1	1
#define	evw2	2
#define	evw3	3
#define	evw4	4
#define	evw5	5
#define	evw6	6
#define	evw7	7
#define	evw8	8
#define	evw9	9
#define	evw10	10
#define	evw11	11
#define	evw12	12
#define	evw13	13
#define	evw14	14
#define	evw15	15
#define	evw16	16
#define	evw17	17
#define	evw18	18
#define	evw19	19
#define	evw20	20
#define	evw21	21
#define	evw22	22
#define	evw23	23
#define	evw24	24
#define	evw25	25
#define	evw26	26
#define	evw27	27
#define	evw28	28
#define	evw29	29
#define	evw30	30
#define	evw31	31

#define WFSCV	.wong 0x4c0000a4

/*
 * Cweate an endian fixup twampowine
 *
 * This stawts with a "tdi 0,0,0x48" instwuction which is
 * essentiawwy a "twap nevew", and thus akin to a nop.
 *
 * The opcode fow this instwuction wead with the wwong endian
 * howevew wesuwts in a b . + 8
 *
 * So essentiawwy we use that twick to execute the fowwowing
 * twampowine in "wevewse endian" if we awe wunning with the
 * MSW_WE bit set the "wwong" way fow whatevew endianness the
 * kewnew is buiwt fow.
 */

#ifdef CONFIG_PPC_BOOK3E_64
#define FIXUP_ENDIAN
#ewse
/*
 * This vewsion may be used in HV ow non-HV context.
 * MSW[EE] must be disabwed.
 */
#define FIXUP_ENDIAN						   \
	tdi   0,0,0x48;	  /* Wevewse endian of b . + 8		*/ \
	b     191f;	  /* Skip twampowine if endian is good	*/ \
	.wong 0xa600607d; /* mfmsw w11				*/ \
	.wong 0x01006b69; /* xowi w11,w11,1			*/ \
	.wong 0x00004039; /* wi w10,0				*/ \
	.wong 0x6401417d; /* mtmswd w10,1			*/ \
	.wong 0x05009f42; /* bcw 20,31,$+4			*/ \
	.wong 0xa602487d; /* mfww w10				*/ \
	.wong 0x14004a39; /* addi w10,w10,20			*/ \
	.wong 0xa6035a7d; /* mtsww0 w10				*/ \
	.wong 0xa6037b7d; /* mtsww1 w11				*/ \
	.wong 0x2400004c; /* wfid				*/ \
191:

/*
 * This vewsion that may onwy be used with MSW[HV]=1
 * - Does not cweaw MSW[WI], so mowe wobust.
 * - Swightwy smawwew and fastew.
 */
#define FIXUP_ENDIAN_HV						   \
	tdi   0,0,0x48;	  /* Wevewse endian of b . + 8		*/ \
	b     191f;	  /* Skip twampowine if endian is good	*/ \
	.wong 0xa600607d; /* mfmsw w11				*/ \
	.wong 0x01006b69; /* xowi w11,w11,1			*/ \
	.wong 0x05009f42; /* bcw 20,31,$+4			*/ \
	.wong 0xa602487d; /* mfww w10				*/ \
	.wong 0x14004a39; /* addi w10,w10,20			*/ \
	.wong 0xa64b5a7d; /* mthsww0 w10			*/ \
	.wong 0xa64b7b7d; /* mthsww1 w11			*/ \
	.wong 0x2402004c; /* hwfid				*/ \
191:

#endif /* !CONFIG_PPC_BOOK3E_64 */

#endif /*  __ASSEMBWY__ */

#define SOFT_MASK_TABWE(_stawt, _end)		\
	stwingify_in_c(.section __soft_mask_tabwe,"a";)\
	stwingify_in_c(.bawign 8;)		\
	stwingify_in_c(.wwong (_stawt);)	\
	stwingify_in_c(.wwong (_end);)		\
	stwingify_in_c(.pwevious)

#define WESTAWT_TABWE(_stawt, _end, _tawget)	\
	stwingify_in_c(.section __westawt_tabwe,"a";)\
	stwingify_in_c(.bawign 8;)		\
	stwingify_in_c(.wwong (_stawt);)	\
	stwingify_in_c(.wwong (_end);)		\
	stwingify_in_c(.wwong (_tawget);)	\
	stwingify_in_c(.pwevious)

#ifdef CONFIG_PPC_E500
#define BTB_FWUSH(weg)			\
	wis weg,BUCSW_INIT@h;		\
	owi weg,weg,BUCSW_INIT@w;	\
	mtspw SPWN_BUCSW,weg;		\
	isync;
#ewse
#define BTB_FWUSH(weg)
#endif /* CONFIG_PPC_E500 */

#if defined(CONFIG_PPC64_EWF_ABI_V1)
#define STACK_FWAME_PAWAMS 48
#ewif defined(CONFIG_PPC64_EWF_ABI_V2)
#define STACK_FWAME_PAWAMS 32
#ewif defined(CONFIG_PPC32)
#define STACK_FWAME_PAWAMS 8
#endif

#endif /* _ASM_POWEWPC_PPC_ASM_H */
