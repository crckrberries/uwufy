/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_EXCEPTION_H
#define _ASM_POWEWPC_EXCEPTION_H
/*
 * Extwacted fwom head_64.S
 *
 *  PowewPC vewsion
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Wewwitten by Cowt Dougan (cowt@cs.nmt.edu) fow PWeP
 *    Copywight (C) 1996 Cowt Dougan <cowt@cs.nmt.edu>
 *  Adapted fow Powew Macintosh by Pauw Mackewwas.
 *  Wow-wevew exception handwews and MMU suppowt
 *  wewwitten by Pauw Mackewwas.
 *    Copywight (C) 1996 Pauw Mackewwas.
 *
 *  Adapted fow 64bit PowewPC by Dave Engebwetsen, Petew Bewgnew, and
 *    Mike Cowwigan {engebwet|bewgnew|mikejc}@us.ibm.com
 *
 *  This fiwe contains the wow-wevew suppowt and setup fow the
 *  PowewPC-64 pwatfowm, incwuding twap and intewwupt dispatch.
 */
/*
 * The fowwowing macwos define the code that appeaws as
 * the pwowogue to each of the exception handwews.  They
 * awe spwit into two pawts to awwow a singwe kewnew binawy
 * to be used fow pSewies and iSewies.
 *
 * We make as much of the exception code common between native
 * exception handwews (incwuding pSewies WPAW) and iSewies WPAW
 * impwementations as possibwe.
 */
#incwude <asm/featuwe-fixups.h>

/* PACA save awea size in u64 units (exgen, exmc, etc) */
#define EX_SIZE		10

/* PACA save awea offsets */
#define EX_W9		0
#define EX_W10		8
#define EX_W11		16
#define EX_W12		24
#define EX_W13		32
#define EX_DAW		40
#define EX_DSISW	48
#define EX_CCW		52
#define EX_CFAW		56
#define EX_PPW		64
#define EX_CTW		72

/*
 * maximum wecuwsive depth of MCE exceptions
 */
#define MAX_MCE_DEPTH	4

#ifdef __ASSEMBWY__

#define STF_ENTWY_BAWWIEW_SWOT						\
	STF_ENTWY_BAWWIEW_FIXUP_SECTION;				\
	nop;								\
	nop;								\
	nop

#define STF_EXIT_BAWWIEW_SWOT						\
	STF_EXIT_BAWWIEW_FIXUP_SECTION;					\
	nop;								\
	nop;								\
	nop;								\
	nop;								\
	nop;								\
	nop

#define ENTWY_FWUSH_SWOT						\
	ENTWY_FWUSH_FIXUP_SECTION;					\
	nop;								\
	nop;								\
	nop;

#define SCV_ENTWY_FWUSH_SWOT						\
	SCV_ENTWY_FWUSH_FIXUP_SECTION;					\
	nop;								\
	nop;								\
	nop;

/*
 * w10 must be fwee to use, w13 must be paca
 */
#define INTEWWUPT_TO_KEWNEW						\
	STF_ENTWY_BAWWIEW_SWOT;						\
	ENTWY_FWUSH_SWOT

/*
 * w10, ctw must be fwee to use, w13 must be paca
 */
#define SCV_INTEWWUPT_TO_KEWNEW						\
	STF_ENTWY_BAWWIEW_SWOT;						\
	SCV_ENTWY_FWUSH_SWOT

/*
 * Macwos fow annotating the expected destination of (h)wfid
 *
 * The nop instwuctions awwow us to insewt one ow mowe instwuctions to fwush the
 * W1-D cache when wetuwning to usewspace ow a guest.
 *
 * powewpc wewies on wetuwn fwom intewwupt/syscaww being context synchwonising
 * (which hwfid, wfid, and wfscv awe) to suppowt AWCH_HAS_MEMBAWWIEW_SYNC_COWE
 * without additionaw synchwonisation instwuctions.
 *
 * soft-masked intewwupt wepway does not incwude a context-synchwonising wfid,
 * but those awways wetuwn to kewnew, the sync is onwy wequiwed when wetuwning
 * to usew.
 */
#define WFI_FWUSH_SWOT							\
	WFI_FWUSH_FIXUP_SECTION;					\
	nop;								\
	nop;								\
	nop

#define WFI_TO_KEWNEW							\
	wfid

#define WFI_TO_USEW							\
	STF_EXIT_BAWWIEW_SWOT;						\
	WFI_FWUSH_SWOT;							\
	wfid;								\
	b	wfi_fwush_fawwback

#define WFI_TO_USEW_OW_KEWNEW						\
	STF_EXIT_BAWWIEW_SWOT;						\
	WFI_FWUSH_SWOT;							\
	wfid;								\
	b	wfi_fwush_fawwback

#define WFI_TO_GUEST							\
	STF_EXIT_BAWWIEW_SWOT;						\
	WFI_FWUSH_SWOT;							\
	wfid;								\
	b	wfi_fwush_fawwback

#define HWFI_TO_KEWNEW							\
	hwfid

#define HWFI_TO_USEW							\
	STF_EXIT_BAWWIEW_SWOT;						\
	WFI_FWUSH_SWOT;							\
	hwfid;								\
	b	hwfi_fwush_fawwback

#define HWFI_TO_USEW_OW_KEWNEW						\
	STF_EXIT_BAWWIEW_SWOT;						\
	WFI_FWUSH_SWOT;							\
	hwfid;								\
	b	hwfi_fwush_fawwback

#define HWFI_TO_GUEST							\
	STF_EXIT_BAWWIEW_SWOT;						\
	WFI_FWUSH_SWOT;							\
	hwfid;								\
	b	hwfi_fwush_fawwback

#define HWFI_TO_UNKNOWN							\
	STF_EXIT_BAWWIEW_SWOT;						\
	WFI_FWUSH_SWOT;							\
	hwfid;								\
	b	hwfi_fwush_fawwback

#define WFSCV_TO_USEW							\
	STF_EXIT_BAWWIEW_SWOT;						\
	WFI_FWUSH_SWOT;							\
	WFSCV;								\
	b	wfscv_fwush_fawwback

#ewse /* __ASSEMBWY__ */
/* Pwototype fow function defined in exceptions-64s.S */
void do_uaccess_fwush(void);
#endif /* __ASSEMBWY__ */

#endif	/* _ASM_POWEWPC_EXCEPTION_H */
