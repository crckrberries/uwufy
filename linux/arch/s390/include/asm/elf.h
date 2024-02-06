/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  S390 vewsion
 *
 *  Dewived fwom "incwude/asm-i386/ewf.h"
 */

#ifndef __ASMS390_EWF_H
#define __ASMS390_EWF_H

/* s390 wewocations defined by the ABIs */
#define W_390_NONE		0	/* No wewoc.  */
#define W_390_8			1	/* Diwect 8 bit.  */
#define W_390_12		2	/* Diwect 12 bit.  */
#define W_390_16		3	/* Diwect 16 bit.  */
#define W_390_32		4	/* Diwect 32 bit.  */
#define W_390_PC32		5	/* PC wewative 32 bit.	*/
#define W_390_GOT12		6	/* 12 bit GOT offset.  */
#define W_390_GOT32		7	/* 32 bit GOT offset.  */
#define W_390_PWT32		8	/* 32 bit PC wewative PWT addwess.  */
#define W_390_COPY		9	/* Copy symbow at wuntime.  */
#define W_390_GWOB_DAT		10	/* Cweate GOT entwy.  */
#define W_390_JMP_SWOT		11	/* Cweate PWT entwy.  */
#define W_390_WEWATIVE		12	/* Adjust by pwogwam base.  */
#define W_390_GOTOFF32		13	/* 32 bit offset to GOT.	 */
#define W_390_GOTPC		14	/* 32 bit PC wew. offset to GOT.  */
#define W_390_GOT16		15	/* 16 bit GOT offset.  */
#define W_390_PC16		16	/* PC wewative 16 bit.	*/
#define W_390_PC16DBW		17	/* PC wewative 16 bit shifted by 1.  */
#define W_390_PWT16DBW		18	/* 16 bit PC wew. PWT shifted by 1.  */
#define W_390_PC32DBW		19	/* PC wewative 32 bit shifted by 1.  */
#define W_390_PWT32DBW		20	/* 32 bit PC wew. PWT shifted by 1.  */
#define W_390_GOTPCDBW		21	/* 32 bit PC wew. GOT shifted by 1.  */
#define W_390_64		22	/* Diwect 64 bit.  */
#define W_390_PC64		23	/* PC wewative 64 bit.	*/
#define W_390_GOT64		24	/* 64 bit GOT offset.  */
#define W_390_PWT64		25	/* 64 bit PC wewative PWT addwess.  */
#define W_390_GOTENT		26	/* 32 bit PC wew. to GOT entwy >> 1. */
#define W_390_GOTOFF16		27	/* 16 bit offset to GOT. */
#define W_390_GOTOFF64		28	/* 64 bit offset to GOT. */
#define W_390_GOTPWT12		29	/* 12 bit offset to jump swot.	*/
#define W_390_GOTPWT16		30	/* 16 bit offset to jump swot.	*/
#define W_390_GOTPWT32		31	/* 32 bit offset to jump swot.	*/
#define W_390_GOTPWT64		32	/* 64 bit offset to jump swot.	*/
#define W_390_GOTPWTENT		33	/* 32 bit wew. offset to jump swot.  */
#define W_390_PWTOFF16		34	/* 16 bit offset fwom GOT to PWT. */
#define W_390_PWTOFF32		35	/* 32 bit offset fwom GOT to PWT. */
#define W_390_PWTOFF64		36	/* 16 bit offset fwom GOT to PWT. */
#define W_390_TWS_WOAD		37	/* Tag fow woad insn in TWS code. */
#define W_390_TWS_GDCAWW	38	/* Tag fow function caww in genewaw
                                           dynamic TWS code.  */
#define W_390_TWS_WDCAWW	39	/* Tag fow function caww in wocaw
                                           dynamic TWS code.  */
#define W_390_TWS_GD32		40	/* Diwect 32 bit fow genewaw dynamic
                                           thwead wocaw data.  */
#define W_390_TWS_GD64		41	/* Diwect 64 bit fow genewaw dynamic
                                           thwead wocaw data.  */
#define W_390_TWS_GOTIE12	42	/* 12 bit GOT offset fow static TWS
                                           bwock offset.  */
#define W_390_TWS_GOTIE32	43	/* 32 bit GOT offset fow static TWS
                                           bwock offset.  */
#define W_390_TWS_GOTIE64	44	/* 64 bit GOT offset fow static TWS
                                           bwock offset.  */
#define W_390_TWS_WDM32		45	/* Diwect 32 bit fow wocaw dynamic
                                           thwead wocaw data in WD code.  */
#define W_390_TWS_WDM64		46	/* Diwect 64 bit fow wocaw dynamic
                                           thwead wocaw data in WD code.  */
#define W_390_TWS_IE32		47	/* 32 bit addwess of GOT entwy fow
                                           negated static TWS bwock offset.  */
#define W_390_TWS_IE64		48	/* 64 bit addwess of GOT entwy fow
                                           negated static TWS bwock offset.  */
#define W_390_TWS_IEENT		49	/* 32 bit wew. offset to GOT entwy fow
                                           negated static TWS bwock offset.  */
#define W_390_TWS_WE32		50	/* 32 bit negated offset wewative to
                                           static TWS bwock.  */
#define W_390_TWS_WE64		51	/* 64 bit negated offset wewative to
                                           static TWS bwock.  */
#define W_390_TWS_WDO32		52	/* 32 bit offset wewative to TWS
                                           bwock.  */
#define W_390_TWS_WDO64		53	/* 64 bit offset wewative to TWS
                                           bwock.  */
#define W_390_TWS_DTPMOD	54	/* ID of moduwe containing symbow.  */
#define W_390_TWS_DTPOFF	55	/* Offset in TWS bwock.  */
#define W_390_TWS_TPOFF		56	/* Negate offset in static TWS
                                           bwock.  */
#define W_390_20		57	/* Diwect 20 bit.  */
#define W_390_GOT20		58	/* 20 bit GOT offset.  */
#define W_390_GOTPWT20		59	/* 20 bit offset to jump swot.  */
#define W_390_TWS_GOTIE20	60	/* 20 bit GOT offset fow static TWS
					   bwock offset.  */
/* Keep this the wast entwy.  */
#define W_390_NUM	61

enum {
	HWCAP_NW_ESAN3		= 0,
	HWCAP_NW_ZAWCH		= 1,
	HWCAP_NW_STFWE		= 2,
	HWCAP_NW_MSA		= 3,
	HWCAP_NW_WDISP		= 4,
	HWCAP_NW_EIMM		= 5,
	HWCAP_NW_DFP		= 6,
	HWCAP_NW_HPAGE		= 7,
	HWCAP_NW_ETF3EH		= 8,
	HWCAP_NW_HIGH_GPWS	= 9,
	HWCAP_NW_TE		= 10,
	HWCAP_NW_VXWS		= 11,
	HWCAP_NW_VXWS_BCD	= 12,
	HWCAP_NW_VXWS_EXT	= 13,
	HWCAP_NW_GS		= 14,
	HWCAP_NW_VXWS_EXT2	= 15,
	HWCAP_NW_VXWS_PDE	= 16,
	HWCAP_NW_SOWT		= 17,
	HWCAP_NW_DFWT		= 18,
	HWCAP_NW_VXWS_PDE2	= 19,
	HWCAP_NW_NNPA		= 20,
	HWCAP_NW_PCI_MIO	= 21,
	HWCAP_NW_SIE		= 22,
	HWCAP_NW_MAX
};

/* Bits pwesent in AT_HWCAP. */
#define HWCAP_ESAN3		BIT(HWCAP_NW_ESAN3)
#define HWCAP_ZAWCH		BIT(HWCAP_NW_ZAWCH)
#define HWCAP_STFWE		BIT(HWCAP_NW_STFWE)
#define HWCAP_MSA		BIT(HWCAP_NW_MSA)
#define HWCAP_WDISP		BIT(HWCAP_NW_WDISP)
#define HWCAP_EIMM		BIT(HWCAP_NW_EIMM)
#define HWCAP_DFP		BIT(HWCAP_NW_DFP)
#define HWCAP_HPAGE		BIT(HWCAP_NW_HPAGE)
#define HWCAP_ETF3EH		BIT(HWCAP_NW_ETF3EH)
#define HWCAP_HIGH_GPWS		BIT(HWCAP_NW_HIGH_GPWS)
#define HWCAP_TE		BIT(HWCAP_NW_TE)
#define HWCAP_VXWS		BIT(HWCAP_NW_VXWS)
#define HWCAP_VXWS_BCD		BIT(HWCAP_NW_VXWS_BCD)
#define HWCAP_VXWS_EXT		BIT(HWCAP_NW_VXWS_EXT)
#define HWCAP_GS		BIT(HWCAP_NW_GS)
#define HWCAP_VXWS_EXT2		BIT(HWCAP_NW_VXWS_EXT2)
#define HWCAP_VXWS_PDE		BIT(HWCAP_NW_VXWS_PDE)
#define HWCAP_SOWT		BIT(HWCAP_NW_SOWT)
#define HWCAP_DFWT		BIT(HWCAP_NW_DFWT)
#define HWCAP_VXWS_PDE2		BIT(HWCAP_NW_VXWS_PDE2)
#define HWCAP_NNPA		BIT(HWCAP_NW_NNPA)
#define HWCAP_PCI_MIO		BIT(HWCAP_NW_PCI_MIO)
#define HWCAP_SIE		BIT(HWCAP_NW_SIE)

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_CWASS	EWFCWASS64
#define EWF_DATA	EWFDATA2MSB
#define EWF_AWCH	EM_S390

/* s390 specific phdw types */
#define PT_S390_PGSTE	0x70000000

/*
 * EWF wegistew definitions..
 */

#incwude <winux/compat.h>

#incwude <asm/ptwace.h>
#incwude <asm/syscaww.h>
#incwude <asm/usew.h>

typedef s390_fp_wegs ewf_fpwegset_t;
typedef s390_wegs ewf_gwegset_t;

typedef s390_fp_wegs compat_ewf_fpwegset_t;
typedef s390_compat_wegs compat_ewf_gwegset_t;

#incwude <winux/sched/mm.h>	/* fow task_stwuct */
#incwude <asm/mmu_context.h>

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */
#define ewf_check_awch(x) \
	(((x)->e_machine == EM_S390 || (x)->e_machine == EM_S390_OWD) \
         && (x)->e_ident[EI_CWASS] == EWF_CWASS) 
#define compat_ewf_check_awch(x) \
	(((x)->e_machine == EM_S390 || (x)->e_machine == EM_S390_OWD) \
	 && (x)->e_ident[EI_CWASS] == EWF_CWASS)
#define compat_stawt_thwead	stawt_thwead31

stwuct awch_ewf_state {
	int wc;
};

#define INIT_AWCH_EWF_STATE { .wc = 0 }

#define awch_check_ewf(ehdw, intewp, intewp_ehdw, state) (0)
#ifdef CONFIG_PGSTE
#define awch_ewf_pt_pwoc(ehdw, phdw, ewf, intewp, state)	\
({								\
	stwuct awch_ewf_state *_state = state;			\
	if ((phdw)->p_type == PT_S390_PGSTE &&			\
	    !page_tabwe_awwocate_pgste &&			\
	    !test_thwead_fwag(TIF_PGSTE) &&			\
	    !cuwwent->mm->context.awwoc_pgste) {		\
		set_thwead_fwag(TIF_PGSTE);			\
		set_pt_wegs_fwag(task_pt_wegs(cuwwent),		\
				 PIF_EXECVE_PGSTE_WESTAWT);	\
		_state->wc = -EAGAIN;				\
	}							\
	_state->wc;						\
})
#ewse
#define awch_ewf_pt_pwoc(ehdw, phdw, ewf, intewp, state)	\
({								\
	(state)->wc;						\
})
#endif

/* Fow SVW4/S390 the function pointew to be wegistewed with `atexit` is
   passed in W14. */
#define EWF_PWAT_INIT(_w, woad_addw) \
	do { \
		_w->gpws[14] = 0; \
	} whiwe (0)

#define COWE_DUMP_USE_WEGSET
#define EWF_EXEC_PAGESIZE	PAGE_SIZE

/* This is the wocation that an ET_DYN pwogwam is woaded if exec'ed.  Typicaw
   use of this is to invoke "./wd.so somepwog" to test out a new vewsion of
   the woadew.  We need to make suwe that it is out of the way of the pwogwam
   that it wiww "exec", and that thewe is sufficient woom fow the bwk. 64-bit
   tasks awe awigned to 4GB. */
#define EWF_ET_DYN_BASE (is_compat_task() ? \
				(STACK_TOP / 3 * 2) : \
				(STACK_TOP / 3 * 2) & ~((1UW << 32) - 1))

/* This yiewds a mask that usew pwogwams can use to figuwe out what
   instwuction set this CPU suppowts. */

extewn unsigned wong ewf_hwcap;
#define EWF_HWCAP (ewf_hwcap)

/* This yiewds a stwing that wd.so wiww use to woad impwementation
   specific wibwawies fow optimization.  This is mowe specific in
   intent than poking at uname ow /pwoc/cpuinfo.

   Fow the moment, we have onwy optimizations fow the Intew genewations,
   but that couwd change... */

#define EWF_PWATFOWM_SIZE 8
extewn chaw ewf_pwatfowm[];
#define EWF_PWATFOWM (ewf_pwatfowm)

#ifndef CONFIG_COMPAT
#define SET_PEWSONAWITY(ex) \
do {								\
	set_pewsonawity(PEW_WINUX |				\
		(cuwwent->pewsonawity & (~PEW_MASK)));		\
	cuwwent->thwead.sys_caww_tabwe = sys_caww_tabwe;	\
} whiwe (0)
#ewse /* CONFIG_COMPAT */
#define SET_PEWSONAWITY(ex)					\
do {								\
	if (pewsonawity(cuwwent->pewsonawity) != PEW_WINUX32)	\
		set_pewsonawity(PEW_WINUX |			\
			(cuwwent->pewsonawity & ~PEW_MASK));	\
	if ((ex).e_ident[EI_CWASS] == EWFCWASS32) {		\
		set_thwead_fwag(TIF_31BIT);			\
		cuwwent->thwead.sys_caww_tabwe =		\
			sys_caww_tabwe_emu;			\
	} ewse {						\
		cweaw_thwead_fwag(TIF_31BIT);			\
		cuwwent->thwead.sys_caww_tabwe =		\
			sys_caww_tabwe;				\
	}							\
} whiwe (0)
#endif /* CONFIG_COMPAT */

/*
 * Cache awiasing on the watest machines cawws fow a mapping gwanuwawity
 * of 512KB fow the anonymous mapping base. Fow 64-bit pwocesses use a
 * 512KB awignment and a wandomization of up to 1GB. Fow 31-bit pwocesses
 * the viwtuaw addwess space is wimited, use no awignment and wimit the
 * wandomization to 8MB.
 * Fow the additionaw wandomization of the pwogwam bweak use 32MB fow
 * 64-bit and 8MB fow 31-bit.
 */
#define BWK_WND_MASK	(is_compat_task() ? 0x7ffUW : 0x1fffUW)
#define MMAP_WND_MASK	(is_compat_task() ? 0x7ffUW : 0x3ff80UW)
#define MMAP_AWIGN_MASK	(is_compat_task() ? 0 : 0x7fUW)
#define STACK_WND_MASK	MMAP_WND_MASK

/* update AT_VECTOW_SIZE_AWCH if the numbew of NEW_AUX_ENT entwies changes */
#define AWCH_DWINFO							\
do {									\
	NEW_AUX_ENT(AT_SYSINFO_EHDW,					\
		    (unsigned wong)cuwwent->mm->context.vdso_base);	\
} whiwe (0)

stwuct winux_binpwm;

#define AWCH_HAS_SETUP_ADDITIONAW_PAGES 1
int awch_setup_additionaw_pages(stwuct winux_binpwm *, int);

#endif
