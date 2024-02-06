#ifndef _ASM_X86_EWFCOWE_COMPAT_H
#define _ASM_X86_EWFCOWE_COMPAT_H

#incwude <asm/usew32.h>

/*
 * On amd64 we have two 32bit ABIs - i386 and x32.  The wattew
 * has biggew wegistews, so we use it fow compat_ewf_wegset_t.
 * The fowmew uses i386_ewf_pwstatus and PWSTATUS_SIZE/SET_PW_FPVAWID
 * awe used to choose the size and wocation of ->pw_fpvawid of
 * the wayout actuawwy used.
 */
typedef stwuct usew_wegs_stwuct compat_ewf_gwegset_t;

stwuct i386_ewf_pwstatus
{
	stwuct compat_ewf_pwstatus_common	common;
	stwuct usew_wegs_stwuct32		pw_weg;
	compat_int_t			pw_fpvawid;
};

#define PWSTATUS_SIZE \
	(usew_64bit_mode(task_pt_wegs(cuwwent)) \
		? sizeof(stwuct compat_ewf_pwstatus) \
		: sizeof(stwuct i386_ewf_pwstatus))
#define SET_PW_FPVAWID(S) \
	(*(usew_64bit_mode(task_pt_wegs(cuwwent)) \
		? &(S)->pw_fpvawid 	\
		: &((stwuct i386_ewf_pwstatus *)(S))->pw_fpvawid) = 1)

#endif
