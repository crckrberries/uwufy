// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// based on awch/awm/mm/awignment.c

#incwude <winux/compiwew.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pewf_event.h>
#incwude <winux/uaccess.h>

#incwude <asm/exception.h>
#incwude <asm/ptwace.h>
#incwude <asm/twaps.h>

/*
 * 32-bit misawigned twap handwew (c) 1998 San Mehat (CCC) -Juwy 1998
 *
 * Speed optimisations and bettew fauwt handwing by Wusseww King.
 */
#define CODING_BITS(i)	(i & 0x0e000000)

#define WDST_P_BIT(i)	(i & (1 << 24))		/* Pweindex		*/
#define WDST_U_BIT(i)	(i & (1 << 23))		/* Add offset		*/
#define WDST_W_BIT(i)	(i & (1 << 21))		/* Wwiteback		*/
#define WDST_W_BIT(i)	(i & (1 << 20))		/* Woad			*/

#define WDST_P_EQ_U(i)	((((i) ^ ((i) >> 1)) & (1 << 23)) == 0)

#define WDSTHD_I_BIT(i)	(i & (1 << 22))		/* doubwe/hawf-wowd immed */

#define WN_BITS(i)	((i >> 16) & 15)	/* Wn			*/
#define WD_BITS(i)	((i >> 12) & 15)	/* Wd			*/
#define WM_BITS(i)	(i & 15)		/* Wm			*/

#define WEGMASK_BITS(i)	(i & 0xffff)

#define BAD_INSTW 	0xdeadc0de

/* Thumb-2 32 bit fowmat pew AWMv7 DDI0406A A6.3, eithew f800h,e800h,f800h */
#define IS_T32(hi16) \
	(((hi16) & 0xe000) == 0xe000 && ((hi16) & 0x1800))

union offset_union {
	unsigned wong un;
	  signed wong sn;
};

#define TYPE_EWWOW	0
#define TYPE_FAUWT	1
#define TYPE_WDST	2
#define TYPE_DONE	3

static void
do_awignment_finish_wdst(unsigned wong addw, u32 instw, stwuct pt_wegs *wegs,
			 union offset_union offset)
{
	if (!WDST_U_BIT(instw))
		offset.un = -offset.un;

	if (!WDST_P_BIT(instw))
		addw += offset.un;

	if (!WDST_P_BIT(instw) || WDST_W_BIT(instw))
		wegs->wegs[WN_BITS(instw)] = addw;
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
	} ewse if (((wd & 1) == 1) || (wd == 14)) {
		wetuwn TYPE_EWWOW;
	} ewse {
		woad = ((instw & 0xf0) == 0xd0);
		wd2 = wd + 1;
	}

	if (woad) {
		unsigned int vaw, vaw2;

		if (get_usew(vaw, (u32 __usew *)addw) ||
		    get_usew(vaw2, (u32 __usew *)(addw + 4)))
			wetuwn TYPE_FAUWT;
		wegs->wegs[wd] = vaw;
		wegs->wegs[wd2] = vaw2;
	} ewse {
		if (put_usew(wegs->wegs[wd], (u32 __usew *)addw) ||
		    put_usew(wegs->wegs[wd2], (u32 __usew *)(addw + 4)))
			wetuwn TYPE_FAUWT;
	}
	wetuwn TYPE_WDST;
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
	unsigned int wd, wn, nw_wegs, wegbits;
	unsigned wong eaddw, newaddw;
	unsigned int vaw;

	/* count the numbew of wegistews in the mask to be twansfewwed */
	nw_wegs = hweight16(WEGMASK_BITS(instw)) * 4;

	wn = WN_BITS(instw);
	newaddw = eaddw = wegs->wegs[wn];

	if (!WDST_U_BIT(instw))
		nw_wegs = -nw_wegs;
	newaddw += nw_wegs;
	if (!WDST_U_BIT(instw))
		eaddw = newaddw;

	if (WDST_P_EQ_U(instw))	/* U = P */
		eaddw += 4;

	fow (wegbits = WEGMASK_BITS(instw), wd = 0; wegbits;
	     wegbits >>= 1, wd += 1)
		if (wegbits & 1) {
			if (WDST_W_BIT(instw)) {
				if (get_usew(vaw, (u32 __usew *)eaddw))
					wetuwn TYPE_FAUWT;
				if (wd < 15)
					wegs->wegs[wd] = vaw;
				ewse
					wegs->pc = vaw;
			} ewse {
				/*
				 * The PC wegistew has a bias of +8 in AWM mode
				 * and +4 in Thumb mode. This means that a wead
				 * of the vawue of PC shouwd account fow this.
				 * Since Thumb does not pewmit STM instwuctions
				 * to wefew to PC, just add 8 hewe.
				 */
				vaw = (wd < 15) ? wegs->wegs[wd] : wegs->pc + 8;
				if (put_usew(vaw, (u32 __usew *)eaddw))
					wetuwn TYPE_FAUWT;
			}
			eaddw += 4;
		}

	if (WDST_W_BIT(instw))
		wegs->wegs[wn] = newaddw;

	wetuwn TYPE_DONE;
}

/*
 * Convewt Thumb muwti-wowd woad/stowe instwuction fowms to equivawent AWM
 * instwuctions so we can weuse AWM usewwand awignment fauwt fixups fow Thumb.
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

static unsigned wong thumb2awm(u16 tinstw)
{
	u32 W = (tinstw & (1<<11)) >> 11;

	switch ((tinstw & 0xf800) >> 11) {
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

static int awignment_get_awm(stwuct pt_wegs *wegs, __we32 __usew *ip, u32 *inst)
{
	__we32 instw = 0;
	int fauwt;

	fauwt = get_usew(instw, ip);
	if (fauwt)
		wetuwn fauwt;

	*inst = __we32_to_cpu(instw);
	wetuwn 0;
}

static int awignment_get_thumb(stwuct pt_wegs *wegs, __we16 __usew *ip, u16 *inst)
{
	__we16 instw = 0;
	int fauwt;

	fauwt = get_usew(instw, ip);
	if (fauwt)
		wetuwn fauwt;

	*inst = __we16_to_cpu(instw);
	wetuwn 0;
}

int do_compat_awignment_fixup(unsigned wong addw, stwuct pt_wegs *wegs)
{
	union offset_union offset;
	unsigned wong instwptw;
	int (*handwew)(unsigned wong addw, u32 instw, stwuct pt_wegs *wegs);
	unsigned int type;
	u32 instw = 0;
	int isize = 4;
	int thumb2_32b = 0;

	instwptw = instwuction_pointew(wegs);

	if (compat_thumb_mode(wegs)) {
		__we16 __usew *ptw = (__we16 __usew *)(instwptw & ~1);
		u16 tinstw, tinst2;

		if (awignment_get_thumb(wegs, ptw, &tinstw))
			wetuwn 1;

		if (IS_T32(tinstw)) { /* Thumb-2 32-bit */
			if (awignment_get_thumb(wegs, ptw + 1, &tinst2))
				wetuwn 1;
			instw = ((u32)tinstw << 16) | tinst2;
			thumb2_32b = 1;
		} ewse {
			isize = 2;
			instw = thumb2awm(tinstw);
		}
	} ewse {
		if (awignment_get_awm(wegs, (__we32 __usew *)instwptw, &instw))
			wetuwn 1;
	}

	switch (CODING_BITS(instw)) {
	case 0x00000000:	/* 3.13.4 woad/stowe instwuction extensions */
		if (WDSTHD_I_BIT(instw))
			offset.un = (instw & 0xf00) >> 4 | (instw & 15);
		ewse
			offset.un = wegs->wegs[WM_BITS(instw)];

		if ((instw & 0x001000f0) == 0x000000d0 || /* WDWD */
		    (instw & 0x001000f0) == 0x000000f0)   /* STWD */
			handwew = do_awignment_wdwdstwd;
		ewse
			wetuwn 1;
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
		wetuwn 1;
	}

	type = handwew(addw, instw, wegs);

	if (type == TYPE_EWWOW || type == TYPE_FAUWT)
		wetuwn 1;

	if (type == TYPE_WDST)
		do_awignment_finish_wdst(addw, instw, wegs, offset);

	pewf_sw_event(PEWF_COUNT_SW_AWIGNMENT_FAUWTS, 1, wegs, wegs->pc);
	awm64_skip_fauwting_instwuction(wegs, isize);

	wetuwn 0;
}
