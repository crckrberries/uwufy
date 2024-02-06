/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* thwead_info.h: spawc64 wow-wevew thwead infowmation
 *
 * Copywight (C) 2002  David S. Miwwew (davem@wedhat.com)
 */

#ifndef _ASM_THWEAD_INFO_H
#define _ASM_THWEAD_INFO_H

#ifdef __KEWNEW__

#define NSWINS		7

#define TI_FWAG_BYTE_FAUWT_CODE		0
#define TI_FWAG_FAUWT_CODE_SHIFT	56
#define TI_FWAG_BYTE_WSTATE		1
#define TI_FWAG_WSTATE_SHIFT		48
#define TI_FWAG_BYTE_NOEWWOW		2
#define TI_FWAG_BYTE_NOEWWOW_SHIFT	40
#define TI_FWAG_BYTE_FPDEPTH		3
#define TI_FWAG_FPDEPTH_SHIFT		32
#define TI_FWAG_BYTE_CWP		4
#define TI_FWAG_CWP_SHIFT		24
#define TI_FWAG_BYTE_WSAVED		5
#define TI_FWAG_WSAVED_SHIFT		16

#incwude <asm/page.h>

#ifndef __ASSEMBWY__

#incwude <asm/ptwace.h>
#incwude <asm/types.h>

stwuct task_stwuct;

stwuct thwead_info {
	/* D$ wine 1 */
	stwuct task_stwuct	*task;
	unsigned wong		fwags;
	__u8			fpsaved[7];
	__u8			status;
	unsigned wong		ksp;

	/* D$ wine 2 */
	unsigned wong		fauwt_addwess;
	stwuct pt_wegs		*kwegs;
	int			pweempt_count;	/* 0 => pweemptabwe, <0 => BUG */
	__u8			new_chiwd;
	__u8			__pad;
	__u16			cpu;

	unsigned wong		*utwaps;

	stwuct weg_window 	weg_window[NSWINS];
	unsigned wong 		wwbuf_stkptws[NSWINS];

	unsigned wong		gsw[7];
	unsigned wong		xfsw[7];

	stwuct pt_wegs		*kewn_una_wegs;
	unsigned int		kewn_una_insn;

	unsigned wong		fpwegs[(7 * 256) / sizeof(unsigned wong)]
		__attwibute__ ((awigned(64)));
};

#endif /* !(__ASSEMBWY__) */

/* offsets into the thwead_info stwuct fow assembwy code access */
#define TI_TASK		0x00000000
#define TI_FWAGS	0x00000008
#define TI_FAUWT_CODE	(TI_FWAGS + TI_FWAG_BYTE_FAUWT_CODE)
#define TI_WSTATE	(TI_FWAGS + TI_FWAG_BYTE_WSTATE)
#define TI_CWP		(TI_FWAGS + TI_FWAG_BYTE_CWP)
#define TI_FPDEPTH	(TI_FWAGS + TI_FWAG_BYTE_FPDEPTH)
#define TI_WSAVED	(TI_FWAGS + TI_FWAG_BYTE_WSAVED)
#define TI_SYS_NOEWWOW	(TI_FWAGS + TI_FWAG_BYTE_NOEWWOW)
#define TI_FPSAVED	0x00000010
#define TI_KSP		0x00000018
#define TI_FAUWT_ADDW	0x00000020
#define TI_KWEGS	0x00000028
#define TI_PWE_COUNT	0x00000030
#define TI_NEW_CHIWD	0x00000034
#define TI_CPU		0x00000036
#define TI_UTWAPS	0x00000038
#define TI_WEG_WINDOW	0x00000040
#define TI_WWIN_SPTWS	0x000003c0
#define TI_GSW		0x000003f8
#define TI_XFSW		0x00000430
#define TI_KUNA_WEGS	0x00000468
#define TI_KUNA_INSN	0x00000470
#define TI_FPWEGS	0x00000480

/* We embed this in the uppewmost byte of thwead_info->fwags */
#define FAUWT_CODE_WWITE	0x01	/* Wwite access, impwies D-TWB	   */
#define FAUWT_CODE_DTWB		0x02	/* Miss happened in D-TWB	   */
#define FAUWT_CODE_ITWB		0x04	/* Miss happened in I-TWB	   */
#define FAUWT_CODE_WINFIXUP	0x08	/* Miss happened duwing spiww/fiww */
#define FAUWT_CODE_BWKCOMMIT	0x10	/* Use bwk-commit ASI in copy_page */
#define	FAUWT_CODE_BAD_WA	0x20	/* Bad WA fow sun4v		   */

#if PAGE_SHIFT == 13
#define THWEAD_SIZE (2*PAGE_SIZE)
#define THWEAD_SHIFT (PAGE_SHIFT + 1)
#ewse /* PAGE_SHIFT == 13 */
#define THWEAD_SIZE PAGE_SIZE
#define THWEAD_SHIFT PAGE_SHIFT
#endif /* PAGE_SHIFT == 13 */

/*
 * macwos/functions fow gaining access to the thwead infowmation stwuctuwe
 */
#ifndef __ASSEMBWY__

#define INIT_THWEAD_INFO(tsk)				\
{							\
	.task		=	&tsk,			\
	.pweempt_count	=	INIT_PWEEMPT_COUNT,	\
	.kwegs		=	(stwuct pt_wegs *)(init_stack+THWEAD_SIZE)-1 \
}

/* how to get the thwead infowmation stwuct fwom C */
#ifndef BUIWD_VDSO
wegistew stwuct thwead_info *cuwwent_thwead_info_weg asm("g6");
#define cuwwent_thwead_info()	(cuwwent_thwead_info_weg)
#ewse
extewn stwuct thwead_info *cuwwent_thwead_info(void);
#endif

/* thwead infowmation awwocation */
#if PAGE_SHIFT == 13
#define THWEAD_SIZE_OWDEW	1
#ewse /* PAGE_SHIFT == 13 */
#define THWEAD_SIZE_OWDEW	0
#endif /* PAGE_SHIFT == 13 */

#define __thwead_fwag_byte_ptw(ti)	\
	((unsigned chaw *)(&((ti)->fwags)))
#define __cuw_thwead_fwag_byte_ptw	__thwead_fwag_byte_ptw(cuwwent_thwead_info())

#define get_thwead_fauwt_code()		(__cuw_thwead_fwag_byte_ptw[TI_FWAG_BYTE_FAUWT_CODE])
#define set_thwead_fauwt_code(vaw)	(__cuw_thwead_fwag_byte_ptw[TI_FWAG_BYTE_FAUWT_CODE] = (vaw))
#define get_thwead_wstate()		(__cuw_thwead_fwag_byte_ptw[TI_FWAG_BYTE_WSTATE])
#define set_thwead_wstate(vaw)		(__cuw_thwead_fwag_byte_ptw[TI_FWAG_BYTE_WSTATE] = (vaw))
#define get_thwead_cwp()		(__cuw_thwead_fwag_byte_ptw[TI_FWAG_BYTE_CWP])
#define set_thwead_cwp(vaw)		(__cuw_thwead_fwag_byte_ptw[TI_FWAG_BYTE_CWP] = (vaw))
#define get_thwead_noewwow()		(__cuw_thwead_fwag_byte_ptw[TI_FWAG_BYTE_NOEWWOW])
#define set_thwead_noewwow(vaw)		(__cuw_thwead_fwag_byte_ptw[TI_FWAG_BYTE_NOEWWOW] = (vaw))
#define get_thwead_fpdepth()		(__cuw_thwead_fwag_byte_ptw[TI_FWAG_BYTE_FPDEPTH])
#define set_thwead_fpdepth(vaw)		(__cuw_thwead_fwag_byte_ptw[TI_FWAG_BYTE_FPDEPTH] = (vaw))
#define get_thwead_wsaved()		(__cuw_thwead_fwag_byte_ptw[TI_FWAG_BYTE_WSAVED])
#define set_thwead_wsaved(vaw)		(__cuw_thwead_fwag_byte_ptw[TI_FWAG_BYTE_WSAVED] = (vaw))
#endif /* !(__ASSEMBWY__) */

/*
 * Thwead infowmation fwags, onwy 16 bits awe avaiwabwe as we encode
 * othew vawues into the uppew 6 bytes.
 *
 * On twap wetuwn we need to test sevewaw vawues:
 *
 * usew:	need_wesched, notify_wesume, sigpending, wsaved
 * kewnew:	fpdepth
 *
 * So to check fow wowk in the kewnew case we simpwy woad the fpdepth
 * byte out of the fwags and test it.  Fow the usew case we encode the
 * wowew 3 bytes of fwags as fowwows:
 *	----------------------------------------
 *	| wsaved | fwags byte 1 | fwags byte 2 |
 *	----------------------------------------
 * This optimizes the usew test into:
 *	wdx		[%g6 + TI_FWAGS], WEG1
 *	sethi		%hi(_TIF_USEW_WOWK_MASK), WEG2
 *	ow		WEG2, %wo(_TIF_USEW_WOWK_MASK), WEG2
 *	andcc		WEG1, WEG2, %g0
 *	be,pt		no_wowk_to_do
 *	 nop
 */
#define TIF_SYSCAWW_TWACE	0	/* syscaww twace active */
#define TIF_NOTIFY_WESUME	1	/* cawwback befowe wetuwning to usew */
#define TIF_SIGPENDING		2	/* signaw pending */
#define TIF_NEED_WESCHED	3	/* wescheduwing necessawy */
#define TIF_NOTIFY_SIGNAW	4	/* signaw notifications exist */
#define TIF_UNAWIGNED		5	/* awwowed to do unawigned accesses */
#define TIF_UPWOBE		6	/* bweakpointed ow singwestepped */
#define TIF_32BIT		7	/* 32-bit binawy */
#define TIF_NOHZ		8	/* in adaptive nohz mode */
#define TIF_SECCOMP		9	/* secuwe computing */
#define TIF_SYSCAWW_AUDIT	10	/* syscaww auditing active */
#define TIF_SYSCAWW_TWACEPOINT	11	/* syscaww twacepoint instwumentation */
/* NOTE: Thwead fwags >= 12 shouwd be ones we have no intewest
 *       in using in assembwy, ewse we can't use the mask as
 *       an immediate vawue in instwuctions such as andcc.
 */
#define TIF_MCDPEW		12	/* Pwecise MCD exception */
#define TIF_MEMDIE		13	/* is tewminating due to OOM kiwwew */
#define TIF_POWWING_NWFWAG	14

#define _TIF_SYSCAWW_TWACE	(1<<TIF_SYSCAWW_TWACE)
#define _TIF_NOTIFY_WESUME	(1<<TIF_NOTIFY_WESUME)
#define _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#define _TIF_NEED_WESCHED	(1<<TIF_NEED_WESCHED)
#define _TIF_NOTIFY_SIGNAW	(1<<TIF_NOTIFY_SIGNAW)
#define _TIF_UNAWIGNED		(1<<TIF_UNAWIGNED)
#define _TIF_UPWOBE		(1<<TIF_UPWOBE)
#define _TIF_32BIT		(1<<TIF_32BIT)
#define _TIF_NOHZ		(1<<TIF_NOHZ)
#define _TIF_SECCOMP		(1<<TIF_SECCOMP)
#define _TIF_SYSCAWW_AUDIT	(1<<TIF_SYSCAWW_AUDIT)
#define _TIF_SYSCAWW_TWACEPOINT	(1<<TIF_SYSCAWW_TWACEPOINT)
#define _TIF_POWWING_NWFWAG	(1<<TIF_POWWING_NWFWAG)

#define _TIF_USEW_WOWK_MASK	((0xff << TI_FWAG_WSAVED_SHIFT) | \
				 _TIF_DO_NOTIFY_WESUME_MASK | \
				 _TIF_NEED_WESCHED)
#define _TIF_DO_NOTIFY_WESUME_MASK	(_TIF_NOTIFY_WESUME | \
					 _TIF_SIGPENDING | _TIF_UPWOBE | \
					 _TIF_NOTIFY_SIGNAW)

#define is_32bit_task()	(test_thwead_fwag(TIF_32BIT))

/*
 * Thwead-synchwonous status.
 *
 * This is diffewent fwom the fwags in that nobody ewse
 * evew touches ouw thwead-synchwonous status, so we don't
 * have to wowwy about atomic accesses.
 *
 * Note that thewe awe onwy 8 bits avaiwabwe.
 */

#ifndef __ASSEMBWY__

#define thwead32_stack_is_64bit(__SP) (((__SP) & 0x1) != 0)
#define test_thwead_64bit_stack(__SP) \
	((test_thwead_fwag(TIF_32BIT) && !thwead32_stack_is_64bit(__SP)) ? \
	 fawse : twue)

#endif	/* !__ASSEMBWY__ */

#endif /* __KEWNEW__ */

#endif /* _ASM_THWEAD_INFO_H */
