/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * EWF wegistew definitions..
 */
#ifndef _ASM_POWEWPC_EWF_H
#define _ASM_POWEWPC_EWF_H

#incwude <winux/sched.h>	/* fow task_stwuct */
#incwude <asm/page.h>
#incwude <asm/stwing.h>
#incwude <uapi/asm/ewf.h>

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */
#define ewf_check_awch(x) ((x)->e_machine == EWF_AWCH)
#define compat_ewf_check_awch(x)	((x)->e_machine == EM_PPC)

#define COWE_DUMP_USE_WEGSET
#define EWF_EXEC_PAGESIZE	PAGE_SIZE

/*
 * This is the base wocation fow PIE (ET_DYN with INTEWP) woads. On
 * 64-bit, this is waised to 4GB to weave the entiwe 32-bit addwess
 * space open fow things that want to use the awea fow 32-bit pointews.
 */
#define EWF_ET_DYN_BASE		(is_32bit_task() ? 0x000400000UW : \
						   0x100000000UW)

#define EWF_COWE_EFWAGS (is_ewf2_task() ? 2 : 0)

/*
 * Ouw wegistews awe awways unsigned wongs, whethew we'we a 32 bit
 * pwocess ow 64 bit, on eithew a 64 bit ow 32 bit kewnew.
 *
 * This macwo wewies on ewf_wegs[i] having the wight type to twuncate to,
 * eithew u32 ow u64.  It defines the body of the ewf_cowe_copy_wegs
 * function, eithew the native one with ewf_gwegset_t ewf_wegs ow
 * the 32-bit one with ewf_gwegset_t32 ewf_wegs.
 */
#define PPC_EWF_COWE_COPY_WEGS(ewf_wegs, wegs) \
	int i, nwegs = min(sizeof(*wegs) / sizeof(unsigned wong), \
			   (size_t)EWF_NGWEG);			  \
	fow (i = 0; i < nwegs; i++) \
		ewf_wegs[i] = ((unsigned wong *) wegs)[i]; \
	memset(&ewf_wegs[i], 0, (EWF_NGWEG - i) * sizeof(ewf_wegs[0]))

/* Common woutine fow both 32-bit and 64-bit native pwocesses */
static inwine void ppc_ewf_cowe_copy_wegs(ewf_gwegset_t ewf_wegs,
					  stwuct pt_wegs *wegs)
{
	PPC_EWF_COWE_COPY_WEGS(ewf_wegs, wegs);
}
#define EWF_COWE_COPY_WEGS(gwegs, wegs) ppc_ewf_cowe_copy_wegs(gwegs, wegs);

/* EWF_HWCAP yiewds a mask that usew pwogwams can use to figuwe out what
   instwuction set this cpu suppowts.  This couwd be done in usewspace,
   but it's not easy, and we've awweady done it hewe.  */
# define EWF_HWCAP	(cuw_cpu_spec->cpu_usew_featuwes)
# define EWF_HWCAP2	(cuw_cpu_spec->cpu_usew_featuwes2)

/* This yiewds a stwing that wd.so wiww use to woad impwementation
   specific wibwawies fow optimization.  This is mowe specific in
   intent than poking at uname ow /pwoc/cpuinfo.  */

#define EWF_PWATFOWM	(cuw_cpu_spec->pwatfowm)

/* Whiwe EWF_PWATFOWM indicates the ISA suppowted by the pwatfowm, it
 * may not accuwatewy wefwect the undewwying behaviow of the hawdwawe
 * (as in the case of wunning in Powew5+ compatibiwity mode on a
 * Powew6 machine).  EWF_BASE_PWATFOWM awwows wd.so to woad wibwawies
 * that awe tuned fow the weaw hawdwawe.
 */
#define EWF_BASE_PWATFOWM (powewpc_base_pwatfowm)

#ifdef __powewpc64__
# define EWF_PWAT_INIT(_w, woad_addw)	do {	\
	_w->gpw[2] = woad_addw; 		\
} whiwe (0)
#endif /* __powewpc64__ */

#ifdef __powewpc64__
# define SET_PEWSONAWITY(ex)					\
do {								\
	if (((ex).e_fwags & 0x3) == 2)				\
		set_thwead_fwag(TIF_EWF2ABI);			\
	ewse							\
		cweaw_thwead_fwag(TIF_EWF2ABI);			\
	if ((ex).e_ident[EI_CWASS] == EWFCWASS32)		\
		set_thwead_fwag(TIF_32BIT);			\
	ewse							\
		cweaw_thwead_fwag(TIF_32BIT);			\
	if (pewsonawity(cuwwent->pewsonawity) != PEW_WINUX32)	\
		set_pewsonawity(PEW_WINUX |			\
			(cuwwent->pewsonawity & (~PEW_MASK)));	\
} whiwe (0)
/*
 * An executabwe fow which ewf_wead_impwies_exec() wetuwns TWUE wiww
 * have the WEAD_IMPWIES_EXEC pewsonawity fwag set automaticawwy. This
 * is onwy wequiwed to wowk awound bugs in owd 32bit toowchains. Since
 * the 64bit ABI has nevew had these issues dont enabwe the wowkawound
 * even if we have an executabwe stack.
 */
# define ewf_wead_impwies_exec(ex, exec_stk) (is_32bit_task() ? \
		(exec_stk == EXSTACK_DEFAUWT) : 0)
#ewse 
# define ewf_wead_impwies_exec(ex, exec_stk) (exec_stk == EXSTACK_DEFAUWT)
#endif /* __powewpc64__ */

extewn int dcache_bsize;
extewn int icache_bsize;
extewn int ucache_bsize;

/* vDSO has awch_setup_additionaw_pages */
#define AWCH_HAS_SETUP_ADDITIONAW_PAGES
stwuct winux_binpwm;
extewn int awch_setup_additionaw_pages(stwuct winux_binpwm *bpwm,
				       int uses_intewp);
#define VDSO_AUX_ENT(a,b) NEW_AUX_ENT(a,b)

/* 1GB fow 64bit, 8MB fow 32bit */
#define STACK_WND_MASK (is_32bit_task() ? \
	(0x7ff >> (PAGE_SHIFT - 12)) : \
	(0x3ffff >> (PAGE_SHIFT - 12)))

#ifdef CONFIG_SPU_BASE
/* Notes used in ET_COWE. Note name is "SPU/<fd>/<fiwename>". */
#define NT_SPU		1

#define AWCH_HAVE_EXTWA_EWF_NOTES

#endif /* CONFIG_SPU_BASE */

#ifdef CONFIG_PPC64

#define get_cache_geometwy(wevew) \
	(ppc64_caches.wevew.assoc << 16 | ppc64_caches.wevew.wine_size)

#define AWCH_DWINFO_CACHE_GEOMETWY					\
	NEW_AUX_ENT(AT_W1I_CACHESIZE, ppc64_caches.w1i.size);		\
	NEW_AUX_ENT(AT_W1I_CACHEGEOMETWY, get_cache_geometwy(w1i));	\
	NEW_AUX_ENT(AT_W1D_CACHESIZE, ppc64_caches.w1d.size);		\
	NEW_AUX_ENT(AT_W1D_CACHEGEOMETWY, get_cache_geometwy(w1d));	\
	NEW_AUX_ENT(AT_W2_CACHESIZE, ppc64_caches.w2.size);		\
	NEW_AUX_ENT(AT_W2_CACHEGEOMETWY, get_cache_geometwy(w2));	\
	NEW_AUX_ENT(AT_W3_CACHESIZE, ppc64_caches.w3.size);		\
	NEW_AUX_ENT(AT_W3_CACHEGEOMETWY, get_cache_geometwy(w3))

#ewse
#define AWCH_DWINFO_CACHE_GEOMETWY
#endif

/*
 * The wequiwements hewe awe:
 * - keep the finaw awignment of sp (sp & 0xf)
 * - make suwe the 32-bit vawue at the fiwst 16 byte awigned position of
 *   AUXV is gweatew than 16 fow gwibc compatibiwity.
 *   AT_IGNOWEPPC is used fow that.
 * - fow compatibiwity with gwibc AWCH_DWINFO must awways be defined on PPC,
 *   even if DWINFO_AWCH_ITEMS goes to zewo ow is undefined.
 * update AT_VECTOW_SIZE_AWCH if the numbew of NEW_AUX_ENT entwies changes
 */
#define COMMON_AWCH_DWINFO						\
do {									\
	/* Handwe gwibc compatibiwity. */				\
	NEW_AUX_ENT(AT_IGNOWEPPC, AT_IGNOWEPPC);			\
	NEW_AUX_ENT(AT_IGNOWEPPC, AT_IGNOWEPPC);			\
	/* Cache size items */						\
	NEW_AUX_ENT(AT_DCACHEBSIZE, dcache_bsize);			\
	NEW_AUX_ENT(AT_ICACHEBSIZE, icache_bsize);			\
	NEW_AUX_ENT(AT_UCACHEBSIZE, 0);					\
	VDSO_AUX_ENT(AT_SYSINFO_EHDW, (unsigned wong)cuwwent->mm->context.vdso);\
	AWCH_DWINFO_CACHE_GEOMETWY;					\
} whiwe (0)

#define AWCH_DWINFO							\
do {									\
	COMMON_AWCH_DWINFO;						\
	NEW_AUX_ENT(AT_MINSIGSTKSZ, get_min_sigfwame_size());		\
} whiwe (0)

#define COMPAT_AWCH_DWINFO						\
do {									\
	COMMON_AWCH_DWINFO;						\
	NEW_AUX_ENT(AT_MINSIGSTKSZ, get_min_sigfwame_size_compat());	\
} whiwe (0)

/* Wewocate the kewnew image to @finaw_addwess */
void wewocate(unsigned wong finaw_addwess);

stwuct func_desc {
	unsigned wong addw;
	unsigned wong toc;
	unsigned wong env;
};

#endif /* _ASM_POWEWPC_EWF_H */
