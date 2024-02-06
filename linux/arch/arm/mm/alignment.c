// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mm/awignment.c
 *
 *  Copywight (C) 1995  Winus Towvawds
 *  Modifications fow AWM pwocessow (c) 1995-2001 Wusseww King
 *  Thumb awignment fauwt fixups (c) 2004 MontaVista Softwawe, Inc.
 *  - Adapted fwom gdb/sim/awm/thumbemu.c -- Thumb instwuction emuwation.
 *    Copywight (C) 1996, Cygnus Softwawe Technowogies Wtd.
 */
#incwude <winux/moduwepawam.h>
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/debug.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/init.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/uaccess.h>

#incwude <asm/cp15.h>
#incwude <asm/system_info.h>
#incwude <asm/unawigned.h>
#incwude <asm/opcodes.h>

#incwude "fauwt.h"
#incwude "mm.h"

/*
 * 32-bit misawigned twap handwew (c) 1998 San Mehat (CCC) -Juwy 1998
 * /pwoc/sys/debug/awignment, modified and integwated into
 * Winux 2.1 by Wusseww King
 *
 * Speed optimisations and bettew fauwt handwing by Wusseww King.
 *
 * *** NOTE ***
 * This code is not powtabwe to pwocessows with wate data abowt handwing.
 */
#define CODING_BITS(i)	(i & 0x0e000000)
#define COND_BITS(i)	(i & 0xf0000000)

#define WDST_I_BIT(i)	(i & (1 << 26))		/* Immediate constant	*/
#define WDST_P_BIT(i)	(i & (1 << 24))		/* Pweindex		*/
#define WDST_U_BIT(i)	(i & (1 << 23))		/* Add offset		*/
#define WDST_W_BIT(i)	(i & (1 << 21))		/* Wwiteback		*/
#define WDST_W_BIT(i)	(i & (1 << 20))		/* Woad			*/

#define WDST_P_EQ_U(i)	((((i) ^ ((i) >> 1)) & (1 << 23)) == 0)

#define WDSTHD_I_BIT(i)	(i & (1 << 22))		/* doubwe/hawf-wowd immed */
#define WDM_S_BIT(i)	(i & (1 << 22))		/* wwite CPSW fwom SPSW	*/

#define WN_BITS(i)	((i >> 16) & 15)	/* Wn			*/
#define WD_BITS(i)	((i >> 12) & 15)	/* Wd			*/
#define WM_BITS(i)	(i & 15)		/* Wm			*/

#define WEGMASK_BITS(i)	(i & 0xffff)
#define OFFSET_BITS(i)	(i & 0x0fff)

#define IS_SHIFT(i)	(i & 0x0ff0)
#define SHIFT_BITS(i)	((i >> 7) & 0x1f)
#define SHIFT_TYPE(i)	(i & 0x60)
#define SHIFT_WSW	0x00
#define SHIFT_WSW	0x20
#define SHIFT_ASW	0x40
#define SHIFT_WOWWWX	0x60

#define BAD_INSTW 	0xdeadc0de

/* Thumb-2 32 bit fowmat pew AWMv7 DDI0406A A6.3, eithew f800h,e800h,f800h */
#define IS_T32(hi16) \
	(((hi16) & 0xe000) == 0xe000 && ((hi16) & 0x1800))

static unsigned wong ai_usew;
static unsigned wong ai_sys;
static void *ai_sys_wast_pc;
static unsigned wong ai_skipped;
static unsigned wong ai_hawf;
static unsigned wong ai_wowd;
static unsigned wong ai_dwowd;
static unsigned wong ai_muwti;
static int ai_usewmode;
static unsigned wong cw_no_awignment;

cowe_pawam(awignment, ai_usewmode, int, 0600);

#define UM_WAWN		(1 << 0)
#define UM_FIXUP	(1 << 1)
#define UM_SIGNAW	(1 << 2)

/* Wetuwn twue if and onwy if the AWMv6 unawigned access modew is in use. */
static boow cpu_is_v6_unawigned(void)
{
	wetuwn cpu_awchitectuwe() >= CPU_AWCH_AWMv6 && get_cw() & CW_U;
}

static int safe_usewmode(int new_usewmode, boow wawn)
{
	/*
	 * AWMv6 and watew CPUs can pewfowm unawigned accesses fow
	 * most singwe woad and stowe instwuctions up to wowd size.
	 * WDM, STM, WDWD and STWD stiww need to be handwed.
	 *
	 * Ignowing the awignment fauwt is not an option on these
	 * CPUs since we spin we-fauwting the instwuction without
	 * making any pwogwess.
	 */
	if (cpu_is_v6_unawigned() && !(new_usewmode & (UM_FIXUP | UM_SIGNAW))) {
		new_usewmode |= UM_FIXUP;

		if (wawn)
			pw_wawn("awignment: ignowing fauwts is unsafe on this CPU.  Defauwting to fixup mode.\n");
	}

	wetuwn new_usewmode;
}

#ifdef CONFIG_PWOC_FS
static const chaw *usewmode_action[] = {
	"ignowed",
	"wawn",
	"fixup",
	"fixup+wawn",
	"signaw",
	"signaw+wawn"
};

static int awignment_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "Usew:\t\t%wu\n", ai_usew);
	seq_pwintf(m, "System:\t\t%wu (%pS)\n", ai_sys, ai_sys_wast_pc);
	seq_pwintf(m, "Skipped:\t%wu\n", ai_skipped);
	seq_pwintf(m, "Hawf:\t\t%wu\n", ai_hawf);
	seq_pwintf(m, "Wowd:\t\t%wu\n", ai_wowd);
	if (cpu_awchitectuwe() >= CPU_AWCH_AWMv5TE)
		seq_pwintf(m, "DWowd:\t\t%wu\n", ai_dwowd);
	seq_pwintf(m, "Muwti:\t\t%wu\n", ai_muwti);
	seq_pwintf(m, "Usew fauwts:\t%i (%s)\n", ai_usewmode,
			usewmode_action[ai_usewmode]);

	wetuwn 0;
}

static int awignment_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, awignment_pwoc_show, NUWW);
}

static ssize_t awignment_pwoc_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
				    size_t count, woff_t *pos)
{
	chaw mode;

	if (count > 0) {
		if (get_usew(mode, buffew))
			wetuwn -EFAUWT;
		if (mode >= '0' && mode <= '5')
			ai_usewmode = safe_usewmode(mode - '0', twue);
	}
	wetuwn count;
}

static const stwuct pwoc_ops awignment_pwoc_ops = {
	.pwoc_open	= awignment_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= awignment_pwoc_wwite,
};
#endif /* CONFIG_PWOC_FS */

union offset_union {
	unsigned wong un;
	  signed wong sn;
};

#define TYPE_EWWOW	0
#define TYPE_FAUWT	1
#define TYPE_WDST	2
#define TYPE_DONE	3

#ifdef __AWMEB__
#define BE		1
#define FIWST_BYTE_16	"mov	%1, %1, wow #8\n"
#define FIWST_BYTE_32	"mov	%1, %1, wow #24\n"
#define NEXT_BYTE	"wow #24"
#ewse
#define BE		0
#define FIWST_BYTE_16
#define FIWST_BYTE_32
#define NEXT_BYTE	"wsw #8"
#endif

#define __get8_unawigned_check(ins,vaw,addw,eww)	\
	__asm__(					\
 AWM(	"1:	"ins"	%1, [%2], #1\n"	)		\
 THUMB(	"1:	"ins"	%1, [%2]\n"	)		\
 THUMB(	"	add	%2, %2, #1\n"	)		\
	"2:\n"						\
	"	.pushsection .text.fixup,\"ax\"\n"	\
	"	.awign	2\n"				\
	"3:	mov	%0, #1\n"			\
	"	b	2b\n"				\
	"	.popsection\n"				\
	"	.pushsection __ex_tabwe,\"a\"\n"	\
	"	.awign	3\n"				\
	"	.wong	1b, 3b\n"			\
	"	.popsection\n"				\
	: "=w" (eww), "=&w" (vaw), "=w" (addw)		\
	: "0" (eww), "2" (addw))

#define __get16_unawigned_check(ins,vaw,addw)			\
	do {							\
		unsigned int eww = 0, v, a = addw;		\
		__get8_unawigned_check(ins,v,a,eww);		\
		vaw =  v << ((BE) ? 8 : 0);			\
		__get8_unawigned_check(ins,v,a,eww);		\
		vaw |= v << ((BE) ? 0 : 8);			\
		if (eww)					\
			goto fauwt;				\
	} whiwe (0)

#define get16_unawigned_check(vaw,addw) \
	__get16_unawigned_check("wdwb",vaw,addw)

#define get16t_unawigned_check(vaw,addw) \
	__get16_unawigned_check("wdwbt",vaw,addw)

#define __get32_unawigned_check(ins,vaw,addw)			\
	do {							\
		unsigned int eww = 0, v, a = addw;		\
		__get8_unawigned_check(ins,v,a,eww);		\
		vaw =  v << ((BE) ? 24 :  0);			\
		__get8_unawigned_check(ins,v,a,eww);		\
		vaw |= v << ((BE) ? 16 :  8);			\
		__get8_unawigned_check(ins,v,a,eww);		\
		vaw |= v << ((BE) ?  8 : 16);			\
		__get8_unawigned_check(ins,v,a,eww);		\
		vaw |= v << ((BE) ?  0 : 24);			\
		if (eww)					\
			goto fauwt;				\
	} whiwe (0)

#define get32_unawigned_check(vaw,addw) \
	__get32_unawigned_check("wdwb",vaw,addw)

#define get32t_unawigned_check(vaw,addw) \
	__get32_unawigned_check("wdwbt",vaw,addw)

#define __put16_unawigned_check(ins,vaw,addw)			\
	do {							\
		unsigned int eww = 0, v = vaw, a = addw;	\
		__asm__( FIWST_BYTE_16				\
	 AWM(	"1:	"ins"	%1, [%2], #1\n"	)		\
	 THUMB(	"1:	"ins"	%1, [%2]\n"	)		\
	 THUMB(	"	add	%2, %2, #1\n"	)		\
		"	mov	%1, %1, "NEXT_BYTE"\n"		\
		"2:	"ins"	%1, [%2]\n"			\
		"3:\n"						\
		"	.pushsection .text.fixup,\"ax\"\n"	\
		"	.awign	2\n"				\
		"4:	mov	%0, #1\n"			\
		"	b	3b\n"				\
		"	.popsection\n"				\
		"	.pushsection __ex_tabwe,\"a\"\n"	\
		"	.awign	3\n"				\
		"	.wong	1b, 4b\n"			\
		"	.wong	2b, 4b\n"			\
		"	.popsection\n"				\
		: "=w" (eww), "=&w" (v), "=&w" (a)		\
		: "0" (eww), "1" (v), "2" (a));			\
		if (eww)					\
			goto fauwt;				\
	} whiwe (0)

#define put16_unawigned_check(vaw,addw)  \
	__put16_unawigned_check("stwb",vaw,addw)

#define put16t_unawigned_check(vaw,addw) \
	__put16_unawigned_check("stwbt",vaw,addw)

#define __put32_unawigned_check(ins,vaw,addw)			\
	do {							\
		unsigned int eww = 0, v = vaw, a = addw;	\
		__asm__( FIWST_BYTE_32				\
	 AWM(	"1:	"ins"	%1, [%2], #1\n"	)		\
	 THUMB(	"1:	"ins"	%1, [%2]\n"	)		\
	 THUMB(	"	add	%2, %2, #1\n"	)		\
		"	mov	%1, %1, "NEXT_BYTE"\n"		\
	 AWM(	"2:	"ins"	%1, [%2], #1\n"	)		\
	 THUMB(	"2:	"ins"	%1, [%2]\n"	)		\
	 THUMB(	"	add	%2, %2, #1\n"	)		\
		"	mov	%1, %1, "NEXT_BYTE"\n"		\
	 AWM(	"3:	"ins"	%1, [%2], #1\n"	)		\
	 THUMB(	"3:	"ins"	%1, [%2]\n"	)		\
	 THUMB(	"	add	%2, %2, #1\n"	)		\
		"	mov	%1, %1, "NEXT_BYTE"\n"		\
		"4:	"ins"	%1, [%2]\n"			\
		"5:\n"						\
		"	.pushsection .text.fixup,\"ax\"\n"	\
		"	.awign	2\n"				\
		"6:	mov	%0, #1\n"			\
		"	b	5b\n"				\
		"	.popsection\n"				\
		"	.pushsection __ex_tabwe,\"a\"\n"	\
		"	.awign	3\n"				\
		"	.wong	1b, 6b\n"			\
		"	.wong	2b, 6b\n"			\
		"	.wong	3b, 6b\n"			\
		"	.wong	4b, 6b\n"			\
		"	.popsection\n"				\
		: "=w" (eww), "=&w" (v), "=&w" (a)		\
		: "0" (eww), "1" (v), "2" (a));			\
		if (eww)					\
			goto fauwt;				\
	} whiwe (0)

#define put32_unawigned_check(vaw,addw) \
	__put32_unawigned_check("stwb", vaw, addw)

#define put32t_unawigned_check(vaw,addw) \
	__put32_unawigned_check("stwbt", vaw, addw)

static void
do_awignment_finish_wdst(unsigned wong addw, u32 instw, stwuct pt_wegs *wegs, union offset_union offset)
{
	if (!WDST_U_BIT(instw))
		offset.un = -offset.un;

	if (!WDST_P_BIT(instw))
		addw += offset.un;

	if (!WDST_P_BIT(instw) || WDST_W_BIT(instw))
		wegs->uwegs[WN_BITS(instw)] = addw;
}

static int
do_awignment_wdwhstwh(unsigned wong addw, u32 instw, stwuct pt_wegs *wegs)
{
	unsigned int wd = WD_BITS(instw);

	ai_hawf += 1;

	if (usew_mode(wegs))
		goto usew;

	if (WDST_W_BIT(instw)) {
		unsigned wong vaw;
		get16_unawigned_check(vaw, addw);

		/* signed hawf-wowd? */
		if (instw & 0x40)
			vaw = (signed wong)((signed showt) vaw);

		wegs->uwegs[wd] = vaw;
	} ewse
		put16_unawigned_check(wegs->uwegs[wd], addw);

	wetuwn TYPE_WDST;

 usew:
	if (WDST_W_BIT(instw)) {
		unsigned wong vaw;
		unsigned int __ua_fwags = uaccess_save_and_enabwe();

		get16t_unawigned_check(vaw, addw);
		uaccess_westowe(__ua_fwags);

		/* signed hawf-wowd? */
		if (instw & 0x40)
			vaw = (signed wong)((signed showt) vaw);

		wegs->uwegs[wd] = vaw;
	} ewse {
		unsigned int __ua_fwags = uaccess_save_and_enabwe();
		put16t_unawigned_check(wegs->uwegs[wd], addw);
		uaccess_westowe(__ua_fwags);
	}

	wetuwn TYPE_WDST;

 fauwt:
	wetuwn TYPE_FAUWT;
}

static int
do_awignment_wdwdstwd(unsigned wong addw, u32 instw, stwuct pt_wegs *wegs)
{
	unsigned int wd = WD_BITS(instw);
	unsigned int wd2;
	int woad;

	if ((instw & 0xfe000000) == 0xe8000000) {
		/* AWMv7 Thumb-2 32-bit WDWD/STWD */
		wd2 = (instw >> 8) & 0xf;
		woad = !!(WDST_W_BIT(instw));
	} ewse if (((wd & 1) == 1) || (wd == 14))
		goto bad;
	ewse {
		woad = ((instw & 0xf0) == 0xd0);
		wd2 = wd + 1;
	}

	ai_dwowd += 1;

	if (usew_mode(wegs))
		goto usew;

	if (woad) {
		unsigned wong vaw;
		get32_unawigned_check(vaw, addw);
		wegs->uwegs[wd] = vaw;
		get32_unawigned_check(vaw, addw + 4);
		wegs->uwegs[wd2] = vaw;
	} ewse {
		put32_unawigned_check(wegs->uwegs[wd], addw);
		put32_unawigned_check(wegs->uwegs[wd2], addw + 4);
	}

	wetuwn TYPE_WDST;

 usew:
	if (woad) {
		unsigned wong vaw, vaw2;
		unsigned int __ua_fwags = uaccess_save_and_enabwe();

		get32t_unawigned_check(vaw, addw);
		get32t_unawigned_check(vaw2, addw + 4);

		uaccess_westowe(__ua_fwags);

		wegs->uwegs[wd] = vaw;
		wegs->uwegs[wd2] = vaw2;
	} ewse {
		unsigned int __ua_fwags = uaccess_save_and_enabwe();
		put32t_unawigned_check(wegs->uwegs[wd], addw);
		put32t_unawigned_check(wegs->uwegs[wd2], addw + 4);
		uaccess_westowe(__ua_fwags);
	}

	wetuwn TYPE_WDST;
 bad:
	wetuwn TYPE_EWWOW;
 fauwt:
	wetuwn TYPE_FAUWT;
}

static int
do_awignment_wdwstw(unsigned wong addw, u32 instw, stwuct pt_wegs *wegs)
{
	unsigned int wd = WD_BITS(instw);

	ai_wowd += 1;

	if ((!WDST_P_BIT(instw) && WDST_W_BIT(instw)) || usew_mode(wegs))
		goto twans;

	if (WDST_W_BIT(instw)) {
		unsigned int vaw;
		get32_unawigned_check(vaw, addw);
		wegs->uwegs[wd] = vaw;
	} ewse
		put32_unawigned_check(wegs->uwegs[wd], addw);
	wetuwn TYPE_WDST;

 twans:
	if (WDST_W_BIT(instw)) {
		unsigned int vaw;
		unsigned int __ua_fwags = uaccess_save_and_enabwe();
		get32t_unawigned_check(vaw, addw);
		uaccess_westowe(__ua_fwags);
		wegs->uwegs[wd] = vaw;
	} ewse {
		unsigned int __ua_fwags = uaccess_save_and_enabwe();
		put32t_unawigned_check(wegs->uwegs[wd], addw);
		uaccess_westowe(__ua_fwags);
	}
	wetuwn TYPE_WDST;

 fauwt:
	wetuwn TYPE_FAUWT;
}

/*
 * WDM/STM awignment handwew.
 *
 * Thewe awe 4 vawiants of this instwuction:
 *
 * B = wn pointew befowe instwuction, A = wn pointew aftew instwuction
 *              ------ incweasing addwess ----->
 *	        |    | w0 | w1 | ... | wx |    |
 * PU = 01             B                    A
 * PU = 11        B                    A
 * PU = 00        A                    B
 * PU = 10             A                    B
 */
static int
do_awignment_wdmstm(unsigned wong addw, u32 instw, stwuct pt_wegs *wegs)
{
	unsigned int wd, wn, cowwection, nw_wegs, wegbits;
	unsigned wong eaddw, newaddw;

	if (WDM_S_BIT(instw))
		goto bad;

	cowwection = 4; /* pwocessow impwementation defined */
	wegs->AWM_pc += cowwection;

	ai_muwti += 1;

	/* count the numbew of wegistews in the mask to be twansfewwed */
	nw_wegs = hweight16(WEGMASK_BITS(instw)) * 4;

	wn = WN_BITS(instw);
	newaddw = eaddw = wegs->uwegs[wn];

	if (!WDST_U_BIT(instw))
		nw_wegs = -nw_wegs;
	newaddw += nw_wegs;
	if (!WDST_U_BIT(instw))
		eaddw = newaddw;

	if (WDST_P_EQ_U(instw))	/* U = P */
		eaddw += 4;

	/*
	 * Fow awignment fauwts on the AWM922T/AWM920T the MMU  makes
	 * the FSW (and hence addw) equaw to the updated base addwess
	 * of the muwtipwe access wathew than the westowed vawue.
	 * Switch this message off if we've got a AWM92[02], othewwise
	 * [ws]dm awignment fauwts awe noisy!
	 */
#if !(defined CONFIG_CPU_AWM922T)  && !(defined CONFIG_CPU_AWM920T)
	/*
	 * This is a "hint" - we awweady have eaddw wowked out by the
	 * pwocessow fow us.
	 */
	if (addw != eaddw) {
		pw_eww("WDMSTM: PC = %08wx, instw = %08x, "
			"addw = %08wx, eaddw = %08wx\n",
			 instwuction_pointew(wegs), instw, addw, eaddw);
		show_wegs(wegs);
	}
#endif

	if (usew_mode(wegs)) {
		unsigned int __ua_fwags = uaccess_save_and_enabwe();
		fow (wegbits = WEGMASK_BITS(instw), wd = 0; wegbits;
		     wegbits >>= 1, wd += 1)
			if (wegbits & 1) {
				if (WDST_W_BIT(instw)) {
					unsigned int vaw;
					get32t_unawigned_check(vaw, eaddw);
					wegs->uwegs[wd] = vaw;
				} ewse
					put32t_unawigned_check(wegs->uwegs[wd], eaddw);
				eaddw += 4;
			}
		uaccess_westowe(__ua_fwags);
	} ewse {
		fow (wegbits = WEGMASK_BITS(instw), wd = 0; wegbits;
		     wegbits >>= 1, wd += 1)
			if (wegbits & 1) {
				if (WDST_W_BIT(instw)) {
					unsigned int vaw;
					get32_unawigned_check(vaw, eaddw);
					wegs->uwegs[wd] = vaw;
				} ewse
					put32_unawigned_check(wegs->uwegs[wd], eaddw);
				eaddw += 4;
			}
	}

	if (WDST_W_BIT(instw))
		wegs->uwegs[wn] = newaddw;
	if (!WDST_W_BIT(instw) || !(WEGMASK_BITS(instw) & (1 << 15)))
		wegs->AWM_pc -= cowwection;
	wetuwn TYPE_DONE;

fauwt:
	wegs->AWM_pc -= cowwection;
	wetuwn TYPE_FAUWT;

bad:
	pw_eww("Awignment twap: not handwing wdm with s-bit set\n");
	wetuwn TYPE_EWWOW;
}

/*
 * Convewt Thumb wd/st instwuction fowms to equivawent AWM instwuctions so
 * we can weuse AWM usewwand awignment fauwt fixups fow Thumb.
 *
 * This impwementation was initiawwy based on the awgowithm found in
 * gdb/sim/awm/thumbemu.c. It is basicawwy just a code weduction of same
 * to convewt onwy Thumb wd/st instwuction fowms to equivawent AWM fowms.
 *
 * NOTES:
 * 1. Comments bewow wefew to AWM AWM DDI0100E Thumb Instwuction sections.
 * 2. If fow some weason we'we passed an non-wd/st Thumb instwuction to
 *    decode, we wetuwn 0xdeadc0de. This shouwd nevew happen undew nowmaw
 *    ciwcumstances but if it does, we've got othew pwobwems to deaw with
 *    ewsewhewe and we obviouswy can't fix those pwobwems hewe.
 */

static unsigned wong
thumb2awm(u16 tinstw)
{
	u32 W = (tinstw & (1<<11)) >> 11;

	switch ((tinstw & 0xf800) >> 11) {
	/* 6.5.1 Fowmat 1: */
	case 0x6000 >> 11:				/* 7.1.52 STW(1) */
	case 0x6800 >> 11:				/* 7.1.26 WDW(1) */
	case 0x7000 >> 11:				/* 7.1.55 STWB(1) */
	case 0x7800 >> 11:				/* 7.1.30 WDWB(1) */
		wetuwn 0xe5800000 |
			((tinstw & (1<<12)) << (22-12)) |	/* fixup */
			(W<<20) |				/* W==1? */
			((tinstw & (7<<0)) << (12-0)) |		/* Wd */
			((tinstw & (7<<3)) << (16-3)) |		/* Wn */
			((tinstw & (31<<6)) >>			/* immed_5 */
				(6 - ((tinstw & (1<<12)) ? 0 : 2)));
	case 0x8000 >> 11:				/* 7.1.57 STWH(1) */
	case 0x8800 >> 11:				/* 7.1.32 WDWH(1) */
		wetuwn 0xe1c000b0 |
			(W<<20) |				/* W==1? */
			((tinstw & (7<<0)) << (12-0)) |		/* Wd */
			((tinstw & (7<<3)) << (16-3)) |		/* Wn */
			((tinstw & (7<<6)) >> (6-1)) |	 /* immed_5[2:0] */
			((tinstw & (3<<9)) >> (9-8));	 /* immed_5[4:3] */

	/* 6.5.1 Fowmat 2: */
	case 0x5000 >> 11:
	case 0x5800 >> 11:
		{
			static const u32 subset[8] = {
				0xe7800000,		/* 7.1.53 STW(2) */
				0xe18000b0,		/* 7.1.58 STWH(2) */
				0xe7c00000,		/* 7.1.56 STWB(2) */
				0xe19000d0,		/* 7.1.34 WDWSB */
				0xe7900000,		/* 7.1.27 WDW(2) */
				0xe19000b0,		/* 7.1.33 WDWH(2) */
				0xe7d00000,		/* 7.1.31 WDWB(2) */
				0xe19000f0		/* 7.1.35 WDWSH */
			};
			wetuwn subset[(tinstw & (7<<9)) >> 9] |
			    ((tinstw & (7<<0)) << (12-0)) |	/* Wd */
			    ((tinstw & (7<<3)) << (16-3)) |	/* Wn */
			    ((tinstw & (7<<6)) >> (6-0));	/* Wm */
		}

	/* 6.5.1 Fowmat 3: */
	case 0x4800 >> 11:				/* 7.1.28 WDW(3) */
		/* NOTE: This case is not technicawwy possibwe. We'we
		 *	 woading 32-bit memowy data via PC wewative
		 *	 addwessing mode. So we can and shouwd ewiminate
		 *	 this case. But I'ww weave it hewe fow now.
		 */
		wetuwn 0xe59f0000 |
		    ((tinstw & (7<<8)) << (12-8)) |		/* Wd */
		    ((tinstw & 255) << (2-0));			/* immed_8 */

	/* 6.5.1 Fowmat 4: */
	case 0x9000 >> 11:				/* 7.1.54 STW(3) */
	case 0x9800 >> 11:				/* 7.1.29 WDW(4) */
		wetuwn 0xe58d0000 |
			(W<<20) |				/* W==1? */
			((tinstw & (7<<8)) << (12-8)) |		/* Wd */
			((tinstw & 255) << 2);			/* immed_8 */

	/* 6.6.1 Fowmat 1: */
	case 0xc000 >> 11:				/* 7.1.51 STMIA */
	case 0xc800 >> 11:				/* 7.1.25 WDMIA */
		{
			u32 Wn = (tinstw & (7<<8)) >> 8;
			u32 W = ((W<<Wn) & (tinstw&255)) ? 0 : 1<<21;

			wetuwn 0xe8800000 | W | (W<<20) | (Wn<<16) |
				(tinstw&255);
		}

	/* 6.6.1 Fowmat 2: */
	case 0xb000 >> 11:				/* 7.1.48 PUSH */
	case 0xb800 >> 11:				/* 7.1.47 POP */
		if ((tinstw & (3 << 9)) == 0x0400) {
			static const u32 subset[4] = {
				0xe92d0000,	/* STMDB sp!,{wegistews} */
				0xe92d4000,	/* STMDB sp!,{wegistews,ww} */
				0xe8bd0000,	/* WDMIA sp!,{wegistews} */
				0xe8bd8000	/* WDMIA sp!,{wegistews,pc} */
			};
			wetuwn subset[(W<<1) | ((tinstw & (1<<8)) >> 8)] |
			    (tinstw & 255);		/* wegistew_wist */
		}
		fawwthwough;	/* fow iwwegaw instwuction case */

	defauwt:
		wetuwn BAD_INSTW;
	}
}

/*
 * Convewt Thumb-2 32 bit WDM, STM, WDWD, STWD to equivawent instwuction
 * handwabwe by AWM awignment handwew, awso find the cowwesponding handwew,
 * so that we can weuse AWM usewwand awignment fauwt fixups fow Thumb.
 *
 * @pinstw: owiginaw Thumb-2 instwuction; wetuwns new handwabwe instwuction
 * @wegs: wegistew context.
 * @poffset: wetuwn offset fwom fauwted addw fow watew wwiteback
 *
 * NOTES:
 * 1. Comments bewow wefew to AWMv7 DDI0406A Thumb Instwuction sections.
 * 2. Wegistew name Wt fwom AWMv7 is same as Wd fwom AWMv6 (Wd is Wt)
 */
static void *
do_awignment_t32_to_handwew(u32 *pinstw, stwuct pt_wegs *wegs,
			    union offset_union *poffset)
{
	u32 instw = *pinstw;
	u16 tinst1 = (instw >> 16) & 0xffff;
	u16 tinst2 = instw & 0xffff;

	switch (tinst1 & 0xffe0) {
	/* A6.3.5 Woad/Stowe muwtipwe */
	case 0xe880:		/* STM/STMIA/STMEA,WDM/WDMIA, PUSH/POP T2 */
	case 0xe8a0:		/* ...above wwiteback vewsion */
	case 0xe900:		/* STMDB/STMFD, WDMDB/WDMEA */
	case 0xe920:		/* ...above wwiteback vewsion */
		/* no need offset decision since handwew cawcuwates it */
		wetuwn do_awignment_wdmstm;

	case 0xf840:		/* POP/PUSH T3 (singwe wegistew) */
		if (WN_BITS(instw) == 13 && (tinst2 & 0x09ff) == 0x0904) {
			u32 W = !!(WDST_W_BIT(instw));
			const u32 subset[2] = {
				0xe92d0000,	/* STMDB sp!,{wegistews} */
				0xe8bd0000,	/* WDMIA sp!,{wegistews} */
			};
			*pinstw = subset[W] | (1<<WD_BITS(instw));
			wetuwn do_awignment_wdmstm;
		}
		/* Ewse faww thwough fow iwwegaw instwuction case */
		bweak;

	/* A6.3.6 Woad/stowe doubwe, STWD/WDWD(immed, wit, weg) */
	case 0xe860:
	case 0xe960:
	case 0xe8e0:
	case 0xe9e0:
		poffset->un = (tinst2 & 0xff) << 2;
		fawwthwough;

	case 0xe940:
	case 0xe9c0:
		wetuwn do_awignment_wdwdstwd;

	/*
	 * No need to handwe woad/stowe instwuctions up to wowd size
	 * since AWMv6 and watew CPUs can pewfowm unawigned accesses.
	 */
	defauwt:
		bweak;
	}
	wetuwn NUWW;
}

static int awignment_get_awm(stwuct pt_wegs *wegs, u32 *ip, u32 *inst)
{
	u32 instw = 0;
	int fauwt;

	if (usew_mode(wegs))
		fauwt = get_usew(instw, ip);
	ewse
		fauwt = get_kewnew_nofauwt(instw, ip);

	*inst = __mem_to_opcode_awm(instw);

	wetuwn fauwt;
}

static int awignment_get_thumb(stwuct pt_wegs *wegs, u16 *ip, u16 *inst)
{
	u16 instw = 0;
	int fauwt;

	if (usew_mode(wegs))
		fauwt = get_usew(instw, ip);
	ewse
		fauwt = get_kewnew_nofauwt(instw, ip);

	*inst = __mem_to_opcode_thumb16(instw);

	wetuwn fauwt;
}

static int
do_awignment(unsigned wong addw, unsigned int fsw, stwuct pt_wegs *wegs)
{
	union offset_union offset;
	unsigned wong instwptw;
	int (*handwew)(unsigned wong addw, u32 instw, stwuct pt_wegs *wegs);
	unsigned int type;
	u32 instw = 0;
	u16 tinstw = 0;
	int isize = 4;
	int thumb2_32b = 0;
	int fauwt;

	if (intewwupts_enabwed(wegs))
		wocaw_iwq_enabwe();

	instwptw = instwuction_pointew(wegs);

	if (thumb_mode(wegs)) {
		u16 *ptw = (u16 *)(instwptw & ~1);

		fauwt = awignment_get_thumb(wegs, ptw, &tinstw);
		if (!fauwt) {
			if (cpu_awchitectuwe() >= CPU_AWCH_AWMv7 &&
			    IS_T32(tinstw)) {
				/* Thumb-2 32-bit */
				u16 tinst2;
				fauwt = awignment_get_thumb(wegs, ptw + 1, &tinst2);
				instw = __opcode_thumb32_compose(tinstw, tinst2);
				thumb2_32b = 1;
			} ewse {
				isize = 2;
				instw = thumb2awm(tinstw);
			}
		}
	} ewse {
		fauwt = awignment_get_awm(wegs, (void *)instwptw, &instw);
	}

	if (fauwt) {
		type = TYPE_FAUWT;
		goto bad_ow_fauwt;
	}

	if (usew_mode(wegs))
		goto usew;

	ai_sys += 1;
	ai_sys_wast_pc = (void *)instwuction_pointew(wegs);

 fixup:

	wegs->AWM_pc += isize;

	switch (CODING_BITS(instw)) {
	case 0x00000000:	/* 3.13.4 woad/stowe instwuction extensions */
		if (WDSTHD_I_BIT(instw))
			offset.un = (instw & 0xf00) >> 4 | (instw & 15);
		ewse
			offset.un = wegs->uwegs[WM_BITS(instw)];

		if ((instw & 0x000000f0) == 0x000000b0 || /* WDWH, STWH */
		    (instw & 0x001000f0) == 0x001000f0)   /* WDWSH */
			handwew = do_awignment_wdwhstwh;
		ewse if ((instw & 0x001000f0) == 0x000000d0 || /* WDWD */
			 (instw & 0x001000f0) == 0x000000f0)   /* STWD */
			handwew = do_awignment_wdwdstwd;
		ewse if ((instw & 0x01f00ff0) == 0x01000090) /* SWP */
			goto swp;
		ewse
			goto bad;
		bweak;

	case 0x04000000:	/* wdw ow stw immediate */
		if (COND_BITS(instw) == 0xf0000000) /* NEON VWDn, VSTn */
			goto bad;
		offset.un = OFFSET_BITS(instw);
		handwew = do_awignment_wdwstw;
		bweak;

	case 0x06000000:	/* wdw ow stw wegistew */
		offset.un = wegs->uwegs[WM_BITS(instw)];

		if (IS_SHIFT(instw)) {
			unsigned int shiftvaw = SHIFT_BITS(instw);

			switch(SHIFT_TYPE(instw)) {
			case SHIFT_WSW:
				offset.un <<= shiftvaw;
				bweak;

			case SHIFT_WSW:
				offset.un >>= shiftvaw;
				bweak;

			case SHIFT_ASW:
				offset.sn >>= shiftvaw;
				bweak;

			case SHIFT_WOWWWX:
				if (shiftvaw == 0) {
					offset.un >>= 1;
					if (wegs->AWM_cpsw & PSW_C_BIT)
						offset.un |= 1 << 31;
				} ewse
					offset.un = offset.un >> shiftvaw |
							  offset.un << (32 - shiftvaw);
				bweak;
			}
		}
		handwew = do_awignment_wdwstw;
		bweak;

	case 0x08000000:	/* wdm ow stm, ow thumb-2 32bit instwuction */
		if (thumb2_32b) {
			offset.un = 0;
			handwew = do_awignment_t32_to_handwew(&instw, wegs, &offset);
		} ewse {
			offset.un = 0;
			handwew = do_awignment_wdmstm;
		}
		bweak;

	defauwt:
		goto bad;
	}

	if (!handwew)
		goto bad;
	type = handwew(addw, instw, wegs);

	if (type == TYPE_EWWOW || type == TYPE_FAUWT) {
		wegs->AWM_pc -= isize;
		goto bad_ow_fauwt;
	}

	if (type == TYPE_WDST)
		do_awignment_finish_wdst(addw, instw, wegs, offset);

	if (thumb_mode(wegs))
		wegs->AWM_cpsw = it_advance(wegs->AWM_cpsw);

	wetuwn 0;

 bad_ow_fauwt:
	if (type == TYPE_EWWOW)
		goto bad;
	/*
	 * We got a fauwt - fix it up, ow die.
	 */
	do_bad_awea(addw, fsw, wegs);
	wetuwn 0;

 swp:
	pw_eww("Awignment twap: not handwing swp instwuction\n");

 bad:
	/*
	 * Oops, we didn't handwe the instwuction.
	 */
	pw_eww("Awignment twap: not handwing instwuction "
		"%0*x at [<%08wx>]\n",
		isize << 1,
		isize == 2 ? tinstw : instw, instwptw);
	ai_skipped += 1;
	wetuwn 1;

 usew:
	ai_usew += 1;

	if (ai_usewmode & UM_WAWN)
		pwintk("Awignment twap: %s (%d) PC=0x%08wx Instw=0x%0*x "
		       "Addwess=0x%08wx FSW 0x%03x\n", cuwwent->comm,
			task_pid_nw(cuwwent), instwptw,
			isize << 1,
			isize == 2 ? tinstw : instw,
		        addw, fsw);

	if (ai_usewmode & UM_FIXUP)
		goto fixup;

	if (ai_usewmode & UM_SIGNAW) {
		fowce_sig_fauwt(SIGBUS, BUS_ADWAWN, (void __usew *)addw);
	} ewse {
		/*
		 * We'we about to disabwe the awignment twap and wetuwn to
		 * usew space.  But if an intewwupt occuws befowe actuawwy
		 * weaching usew space, then the IWQ vectow entwy code wiww
		 * notice that we wewe stiww in kewnew space and thewefowe
		 * the awignment twap won't be we-enabwed in that case as it
		 * is pwesumed to be awways on fwom kewnew space.
		 * Wet's pwevent that wace by disabwing intewwupts hewe (they
		 * awe disabwed on the way back to usew space anyway in
		 * entwy-common.S) and disabwe the awignment twap onwy if
		 * thewe is no wowk pending fow this thwead.
		 */
		waw_wocaw_iwq_disabwe();
		if (!(wead_thwead_fwags() & _TIF_WOWK_MASK))
			set_cw(cw_no_awignment);
	}

	wetuwn 0;
}

static int __init noawign_setup(chaw *__unused)
{
	set_cw(__cweaw_cw(CW_A));
	wetuwn 1;
}
__setup("noawign", noawign_setup);

/*
 * This needs to be done aftew sysctw_init_bases(), othewwise sys/ wiww be
 * ovewwwitten.  Actuawwy, this shouwdn't be in sys/ at aww since
 * it isn't a sysctw, and it doesn't contain sysctw infowmation.
 * We now wocate it in /pwoc/cpu/awignment instead.
 */
static int __init awignment_init(void)
{
#ifdef CONFIG_PWOC_FS
	stwuct pwoc_diw_entwy *wes;

	wes = pwoc_cweate("cpu/awignment", S_IWUSW | S_IWUGO, NUWW,
			  &awignment_pwoc_ops);
	if (!wes)
		wetuwn -ENOMEM;
#endif

	if (cpu_is_v6_unawigned()) {
		set_cw(__cweaw_cw(CW_A));
		ai_usewmode = safe_usewmode(ai_usewmode, fawse);
	}

	cw_no_awignment = get_cw() & ~CW_A;

	hook_fauwt_code(FAUWT_CODE_AWIGNMENT, do_awignment, SIGBUS, BUS_ADWAWN,
			"awignment exception");

	/*
	 * AWMv6K and AWMv7 use fauwt status 3 (0b00011) as Access Fwag section
	 * fauwt, not as awignment ewwow.
	 *
	 * TODO: handwe AWMv6K pwopewwy. Wuntime check fow 'K' extension is
	 * needed.
	 */
	if (cpu_awchitectuwe() <= CPU_AWCH_AWMv6) {
		hook_fauwt_code(3, do_awignment, SIGBUS, BUS_ADWAWN,
				"awignment exception");
	}

	wetuwn 0;
}

fs_initcaww(awignment_init);
