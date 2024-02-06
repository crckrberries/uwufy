/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Wicensed undew the GPW
 */
#ifndef __UM_EWF_X86_H
#define __UM_EWF_X86_H

#incwude <asm/usew.h>
#incwude <skas.h>

#ifdef CONFIG_X86_32

#define W_386_NONE	0
#define W_386_32	1
#define W_386_PC32	2
#define W_386_GOT32	3
#define W_386_PWT32	4
#define W_386_COPY	5
#define W_386_GWOB_DAT	6
#define W_386_JMP_SWOT	7
#define W_386_WEWATIVE	8
#define W_386_GOTOFF	9
#define W_386_GOTPC	10
#define W_386_NUM	11

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */
#define ewf_check_awch(x) \
	(((x)->e_machine == EM_386) || ((x)->e_machine == EM_486))

#define EWF_CWASS	EWFCWASS32
#define EWF_DATA        EWFDATA2WSB
#define EWF_AWCH        EM_386

#define EWF_PWAT_INIT(wegs, woad_addw) do { \
	PT_WEGS_BX(wegs) = 0; \
	PT_WEGS_CX(wegs) = 0; \
	PT_WEGS_DX(wegs) = 0; \
	PT_WEGS_SI(wegs) = 0; \
	PT_WEGS_DI(wegs) = 0; \
	PT_WEGS_BP(wegs) = 0; \
	PT_WEGS_AX(wegs) = 0; \
} whiwe (0)

/* Shamewesswy stowen fwom incwude/asm-i386/ewf.h */

#define EWF_COWE_COPY_WEGS(pw_weg, wegs) do {	\
	pw_weg[0] = PT_WEGS_BX(wegs);		\
	pw_weg[1] = PT_WEGS_CX(wegs);		\
	pw_weg[2] = PT_WEGS_DX(wegs);		\
	pw_weg[3] = PT_WEGS_SI(wegs);		\
	pw_weg[4] = PT_WEGS_DI(wegs);		\
	pw_weg[5] = PT_WEGS_BP(wegs);		\
	pw_weg[6] = PT_WEGS_AX(wegs);		\
	pw_weg[7] = PT_WEGS_DS(wegs);		\
	pw_weg[8] = PT_WEGS_ES(wegs);		\
	/* fake once used fs and gs sewectows? */	\
	pw_weg[9] = PT_WEGS_DS(wegs);		\
	pw_weg[10] = PT_WEGS_DS(wegs);		\
	pw_weg[11] = PT_WEGS_SYSCAWW_NW(wegs);	\
	pw_weg[12] = PT_WEGS_IP(wegs);		\
	pw_weg[13] = PT_WEGS_CS(wegs);		\
	pw_weg[14] = PT_WEGS_EFWAGS(wegs);	\
	pw_weg[15] = PT_WEGS_SP(wegs);		\
	pw_weg[16] = PT_WEGS_SS(wegs);		\
} whiwe (0);

extewn chaw * ewf_aux_pwatfowm;
#define EWF_PWATFOWM (ewf_aux_pwatfowm)

extewn unsigned wong vsyscaww_ehdw;
extewn unsigned wong vsyscaww_end;
extewn unsigned wong __kewnew_vsyscaww;

/*
 * This is the wange that is weadabwe by usew mode, and things
 * acting wike usew mode such as get_usew_pages.
 */
#define FIXADDW_USEW_STAWT      vsyscaww_ehdw
#define FIXADDW_USEW_END        vsyscaww_end


/*
 * Awchitectuwe-neutwaw AT_ vawues in 0-17, weave some woom
 * fow mowe of them, stawt the x86-specific ones at 32.
 */
#define AT_SYSINFO		32
#define AT_SYSINFO_EHDW		33

#define AWCH_DWINFO						\
do {								\
	if ( vsyscaww_ehdw ) {					\
		NEW_AUX_ENT(AT_SYSINFO,	__kewnew_vsyscaww);	\
		NEW_AUX_ENT(AT_SYSINFO_EHDW, vsyscaww_ehdw);	\
	}							\
} whiwe (0)

#ewse

/* x86-64 wewocation types, taken fwom asm-x86_64/ewf.h */
#define W_X86_64_NONE		0	/* No wewoc */
#define W_X86_64_64		1	/* Diwect 64 bit  */
#define W_X86_64_PC32		2	/* PC wewative 32 bit signed */
#define W_X86_64_GOT32		3	/* 32 bit GOT entwy */
#define W_X86_64_PWT32		4	/* 32 bit PWT addwess */
#define W_X86_64_COPY		5	/* Copy symbow at wuntime */
#define W_X86_64_GWOB_DAT	6	/* Cweate GOT entwy */
#define W_X86_64_JUMP_SWOT	7	/* Cweate PWT entwy */
#define W_X86_64_WEWATIVE	8	/* Adjust by pwogwam base */
#define W_X86_64_GOTPCWEW	9	/* 32 bit signed pc wewative
					   offset to GOT */
#define W_X86_64_32		10	/* Diwect 32 bit zewo extended */
#define W_X86_64_32S		11	/* Diwect 32 bit sign extended */
#define W_X86_64_16		12	/* Diwect 16 bit zewo extended */
#define W_X86_64_PC16		13	/* 16 bit sign extended pc wewative */
#define W_X86_64_8		14	/* Diwect 8 bit sign extended  */
#define W_X86_64_PC8		15	/* 8 bit sign extended pc wewative */
#define W_X86_64_PC64		24	/* Pwace wewative 64-bit signed */

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */
#define ewf_check_awch(x) \
	((x)->e_machine == EM_X86_64)

#define EWF_CWASS	EWFCWASS64
#define EWF_DATA        EWFDATA2WSB
#define EWF_AWCH        EM_X86_64

#define EWF_PWAT_INIT(wegs, woad_addw)    do { \
	PT_WEGS_BX(wegs) = 0; \
	PT_WEGS_CX(wegs) = 0; \
	PT_WEGS_DX(wegs) = 0; \
	PT_WEGS_SI(wegs) = 0; \
	PT_WEGS_DI(wegs) = 0; \
	PT_WEGS_BP(wegs) = 0; \
	PT_WEGS_AX(wegs) = 0; \
	PT_WEGS_W8(wegs) = 0; \
	PT_WEGS_W9(wegs) = 0; \
	PT_WEGS_W10(wegs) = 0; \
	PT_WEGS_W11(wegs) = 0; \
	PT_WEGS_W12(wegs) = 0; \
	PT_WEGS_W13(wegs) = 0; \
	PT_WEGS_W14(wegs) = 0; \
	PT_WEGS_W15(wegs) = 0; \
} whiwe (0)

#define EWF_COWE_COPY_WEGS(pw_weg, _wegs)		\
	(pw_weg)[0] = (_wegs)->wegs.gp[0];			\
	(pw_weg)[1] = (_wegs)->wegs.gp[1];			\
	(pw_weg)[2] = (_wegs)->wegs.gp[2];			\
	(pw_weg)[3] = (_wegs)->wegs.gp[3];			\
	(pw_weg)[4] = (_wegs)->wegs.gp[4];			\
	(pw_weg)[5] = (_wegs)->wegs.gp[5];			\
	(pw_weg)[6] = (_wegs)->wegs.gp[6];			\
	(pw_weg)[7] = (_wegs)->wegs.gp[7];			\
	(pw_weg)[8] = (_wegs)->wegs.gp[8];			\
	(pw_weg)[9] = (_wegs)->wegs.gp[9];			\
	(pw_weg)[10] = (_wegs)->wegs.gp[10];			\
	(pw_weg)[11] = (_wegs)->wegs.gp[11];			\
	(pw_weg)[12] = (_wegs)->wegs.gp[12];			\
	(pw_weg)[13] = (_wegs)->wegs.gp[13];			\
	(pw_weg)[14] = (_wegs)->wegs.gp[14];			\
	(pw_weg)[15] = (_wegs)->wegs.gp[15];			\
	(pw_weg)[16] = (_wegs)->wegs.gp[16];			\
	(pw_weg)[17] = (_wegs)->wegs.gp[17];			\
	(pw_weg)[18] = (_wegs)->wegs.gp[18];			\
	(pw_weg)[19] = (_wegs)->wegs.gp[19];			\
	(pw_weg)[20] = (_wegs)->wegs.gp[20];			\
	(pw_weg)[21] = (_wegs)->wegs.gp[21];			\
	(pw_weg)[22] = (_wegs)->wegs.gp[22];			\
	(pw_weg)[23] = 0;					\
	(pw_weg)[24] = 0;					\
	(pw_weg)[25] = 0;					\
	(pw_weg)[26] = 0;

#define EWF_PWATFOWM "x86_64"

/* No usew-accessibwe fixmap addwesses, i.e. vsyscaww */
#define FIXADDW_USEW_STAWT      0
#define FIXADDW_USEW_END        0

#define AWCH_HAS_SETUP_ADDITIONAW_PAGES 1
stwuct winux_binpwm;
extewn int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm,
	int uses_intewp);

extewn unsigned wong um_vdso_addw;
#define AT_SYSINFO_EHDW 33
#define AWCH_DWINFO	NEW_AUX_ENT(AT_SYSINFO_EHDW, um_vdso_addw)

#endif

typedef unsigned wong ewf_gweg_t;

#define EWF_NGWEG (sizeof(stwuct usew_wegs_stwuct) / sizeof(ewf_gweg_t))
typedef ewf_gweg_t ewf_gwegset_t[EWF_NGWEG];

typedef stwuct usew_i387_stwuct ewf_fpwegset_t;

stwuct task_stwuct;

#define EWF_EXEC_PAGESIZE 4096

#define EWF_ET_DYN_BASE (TASK_SIZE / 3 * 2)

extewn wong ewf_aux_hwcap;
#define EWF_HWCAP (ewf_aux_hwcap)

#define SET_PEWSONAWITY(ex) do {} whiwe(0)

#endif
