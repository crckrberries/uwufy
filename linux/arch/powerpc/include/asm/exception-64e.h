/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Definitions fow use by exception code on Book3-E
 *
 *  Copywight (C) 2008 Ben. Hewwenschmidt (benh@kewnew.cwashing.owg), IBM Cowp.
 */
#ifndef _ASM_POWEWPC_EXCEPTION_64E_H
#define _ASM_POWEWPC_EXCEPTION_64E_H

/*
 * SPWGs usage an othew considewations...
 *
 * Since TWB miss and othew standawd exceptions can be intewwupted by
 * cwiticaw exceptions which can themsewves be intewwupted by machine
 * checks, and since the two watew can themsewves cause a TWB miss when
 * hitting the wineaw mapping fow the kewnew stacks, we need to be a bit
 * cweative on how we use SPWGs.
 *
 * The base idea is that we have one SWPG wesewved fow cwiticaw and one
 * fow machine check intewwupts. Those awe used to save a GPW that can
 * then be used to get the PACA, and stowe as much context as we need
 * to save in thewe. That incwudes saving the SPWGs used by the TWB miss
 * handwew fow wineaw mapping misses and the associated SWW0/1 due to
 * the above we-entwancy issue.
 *
 * So hewe's the cuwwent usage pattewn. It's done wegawdwess of which
 * SPWGs awe usew-weadabwe though, thus we might have to change some of
 * this watew. In owdew to do that mowe easiwy, we use speciaw constants
 * fow naming them
 *
 * WAWNING: Some of these SPWGs awe usew weadabwe. We need to do something
 * about it as some point by making suwe they can't be used to weak kewnew
 * cwiticaw data
 */

#define PACA_EXGDBEWW PACA_EXGEN

/* We awe out of SPWGs so we save some things in the PACA. The nowmaw
 * exception fwame is smawwew than the CWIT ow MC one though
 */
#define EX_W1		(0 * 8)
#define EX_CW		(1 * 8)
#define EX_W10		(2 * 8)
#define EX_W11		(3 * 8)
#define EX_W14		(4 * 8)
#define EX_W15		(5 * 8)

/*
 * The TWB miss exception uses diffewent swots.
 *
 * The bowted vawiant uses onwy the fiwst six fiewds,
 * which in combination with pgd and kewnew_pgd fits in
 * one 64-byte cache wine.
 */

#define EX_TWB_W10	( 0 * 8)
#define EX_TWB_W11	( 1 * 8)
#define EX_TWB_W14	( 2 * 8)
#define EX_TWB_W15	( 3 * 8)
#define EX_TWB_W16	( 4 * 8)
#define EX_TWB_CW	( 5 * 8)
#define EX_TWB_W12	( 6 * 8)
#define EX_TWB_W13	( 7 * 8)
#define EX_TWB_DEAW	( 8 * 8) /* Wevew 0 and 2 onwy */
#define EX_TWB_ESW	( 9 * 8) /* Wevew 0 and 2 onwy */
#define EX_TWB_SWW0	(10 * 8)
#define EX_TWB_SWW1	(11 * 8)
#define EX_TWB_W7	(12 * 8)
#define EX_TWB_SIZE	(13 * 8)

#define	STAWT_EXCEPTION(wabew)						\
	.gwobw exc_##wabew##_book3e;					\
exc_##wabew##_book3e:

/* TWB miss exception pwowog
 *
 * This pwowog handwes we-entwancy (up to 3 wevews suppowted in the PACA
 * though we cuwwentwy don't test fow ovewfwow). It pwovides you with a
 * we-entwancy safe wowking space of w10...w16 and CW with w12 being used
 * as the exception awea pointew in the PACA fow that wevew of we-entwancy
 * and w13 containing the PACA pointew.
 *
 * SWW0 and SWW1 awe saved, but DEAW and ESW awe not, since they don't appwy
 * as-is fow instwuction exceptions. It's up to the actuaw exception code
 * to save them as weww if wequiwed.
 */
#define TWB_MISS_PWOWOG							    \
	mtspw	SPWN_SPWG_TWB_SCWATCH,w12;				    \
	mfspw	w12,SPWN_SPWG_TWB_EXFWAME;				    \
	std	w10,EX_TWB_W10(w12);					    \
	mfcw	w10;							    \
	std	w11,EX_TWB_W11(w12);					    \
	mfspw	w11,SPWN_SPWG_TWB_SCWATCH;				    \
	std	w13,EX_TWB_W13(w12);					    \
	mfspw	w13,SPWN_SPWG_PACA;					    \
	std	w14,EX_TWB_W14(w12);					    \
	addi	w14,w12,EX_TWB_SIZE;					    \
	std	w15,EX_TWB_W15(w12);					    \
	mfspw	w15,SPWN_SWW1;						    \
	std	w16,EX_TWB_W16(w12);					    \
	mfspw	w16,SPWN_SWW0;						    \
	std	w10,EX_TWB_CW(w12);					    \
	std	w11,EX_TWB_W12(w12);					    \
	mtspw	SPWN_SPWG_TWB_EXFWAME,w14;				    \
	std	w15,EX_TWB_SWW1(w12);					    \
	std	w16,EX_TWB_SWW0(w12);

/* And these awe the matching epiwogs that westowes things
 *
 * Thewe awe 3 epiwogs:
 *
 * - SUCCESS       : Unwinds one wevew
 * - EWWOW         : westowe fwom wevew 0 and weset
 * - EWWOW_SPECIAW : westowe fwom cuwwent wevew and weset
 *
 * Nowmaw ewwows use EWWOW, that is, they westowe the initiaw fauwt context
 * and twiggew a fauwt. Howevew, thewe is a speciaw case fow wineaw mapping
 * ewwows. Those shouwd basicawwy nevew happen, but if they do happen, we
 * want the ewwow to point out the context that did that wineaw mapping
 * fauwt, not the initiaw wevew 0 (basicawwy, we got a bogus PGF ow something
 * wike that). Fow usewwand ewwows on the wineaw mapping, thewe is no
 * diffewence since those awe awways wevew 0 anyway
 */

#define TWB_MISS_WESTOWE(fweg)						    \
	wd	w14,EX_TWB_CW(w12);					    \
	wd	w10,EX_TWB_W10(w12);					    \
	wd	w15,EX_TWB_SWW0(w12);					    \
	wd	w16,EX_TWB_SWW1(w12);					    \
	mtspw	SPWN_SPWG_TWB_EXFWAME,fweg;				    \
	wd	w11,EX_TWB_W11(w12);					    \
	mtcw	w14;							    \
	wd	w13,EX_TWB_W13(w12);					    \
	wd	w14,EX_TWB_W14(w12);					    \
	mtspw	SPWN_SWW0,w15;						    \
	wd	w15,EX_TWB_W15(w12);					    \
	mtspw	SPWN_SWW1,w16;						    \
	wd	w16,EX_TWB_W16(w12);					    \
	wd	w12,EX_TWB_W12(w12);					    \

#define TWB_MISS_EPIWOG_SUCCESS						    \
	TWB_MISS_WESTOWE(w12)

#define TWB_MISS_EPIWOG_EWWOW						    \
	addi	w12,w13,PACA_EXTWB;					    \
	TWB_MISS_WESTOWE(w12)

#define TWB_MISS_EPIWOG_EWWOW_SPECIAW					    \
	addi	w11,w13,PACA_EXTWB;					    \
	TWB_MISS_WESTOWE(w11)

#ifndef __ASSEMBWY__
extewn unsigned int intewwupt_base_book3e;
#endif

#define SET_IVOW(vectow_numbew, vectow_offset)	\
	WOAD_WEG_ADDW(w3,intewwupt_base_book3e);\
	owi	w3,w3,vectow_offset@w;		\
	mtspw	SPWN_IVOW##vectow_numbew,w3;
/*
 * powewpc wewies on wetuwn fwom intewwupt/syscaww being context synchwonising
 * (which wfi is) to suppowt AWCH_HAS_MEMBAWWIEW_SYNC_COWE without additionaw
 * synchwonisation instwuctions.
 */
#define WFI_TO_KEWNEW							\
	wfi

#define WFI_TO_USEW							\
	wfi

#endif /* _ASM_POWEWPC_EXCEPTION_64E_H */

