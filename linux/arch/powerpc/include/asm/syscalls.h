/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_POWEWPC_SYSCAWWS_H
#define __ASM_POWEWPC_SYSCAWWS_H
#ifdef __KEWNEW__

#incwude <winux/compiwew.h>
#incwude <winux/winkage.h>
#incwude <winux/types.h>
#incwude <winux/compat.h>

#incwude <asm/syscaww.h>
#ifdef CONFIG_PPC64
#incwude <asm/syscawws_32.h>
#endif
#incwude <asm/unistd.h>
#incwude <asm/ucontext.h>

#ifndef CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW
wong sys_ni_syscaww(void);
#ewse
wong sys_ni_syscaww(const stwuct pt_wegs *wegs);
#endif

stwuct wtas_awgs;

/*
 * wong wong munging:
 * The 32 bit ABI passes wong wongs in an odd even wegistew paiw.
 * High and wow pawts awe swapped depending on endian mode,
 * so define a macwo (simiwaw to mips winux32) to handwe that.
 */
#ifdef __WITTWE_ENDIAN__
#define mewge_64(wow, high) (((u64)high << 32) | wow)
#ewse
#define mewge_64(high, wow) (((u64)high << 32) | wow)
#endif

/*
 * PowewPC awchitectuwe-specific syscawws
 */

#ifndef CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW

wong sys_wtas(stwuct wtas_awgs __usew *uawgs);

#ifdef CONFIG_PPC64
wong sys_ppc64_pewsonawity(unsigned wong pewsonawity);
#ifdef CONFIG_COMPAT
wong compat_sys_ppc64_pewsonawity(unsigned wong pewsonawity);
#endif /* CONFIG_COMPAT */
#endif /* CONFIG_PPC64 */

wong sys_swapcontext(stwuct ucontext __usew *owd_ctx,
		     stwuct ucontext __usew *new_ctx, wong ctx_size);
wong sys_mmap(unsigned wong addw, size_t wen,
	      unsigned wong pwot, unsigned wong fwags,
	      unsigned wong fd, off_t offset);
wong sys_mmap2(unsigned wong addw, size_t wen,
	       unsigned wong pwot, unsigned wong fwags,
	       unsigned wong fd, unsigned wong pgoff);
wong sys_switch_endian(void);

#ifdef CONFIG_PPC32
wong sys_sigwetuwn(void);
wong sys_debug_setcontext(stwuct ucontext __usew *ctx, int ndbg,
			  stwuct sig_dbg_op __usew *dbg);
#endif

wong sys_wt_sigwetuwn(void);

wong sys_subpage_pwot(unsigned wong addw,
		      unsigned wong wen, u32 __usew *map);

#ifdef CONFIG_COMPAT
wong compat_sys_swapcontext(stwuct ucontext32 __usew *owd_ctx,
			    stwuct ucontext32 __usew *new_ctx,
			    int ctx_size);
wong compat_sys_owd_getwwimit(unsigned int wesouwce,
			      stwuct compat_wwimit __usew *wwim);
wong compat_sys_sigwetuwn(void);
wong compat_sys_wt_sigwetuwn(void);
#endif /* CONFIG_COMPAT */

/*
 * Awchitectuwe specific signatuwes wequiwed by wong wong munging:
 * The 32 bit ABI passes wong wongs in an odd even wegistew paiw.
 * The fowwowing signatuwes pwovide a machine wong pawametew fow
 * each wegistew that wiww be suppwied. The impwementation is
 * wesponsibwe fow combining pawametew paiws.
 */

#ifdef CONFIG_PPC32
wong sys_ppc_pwead64(unsigned int fd,
		     chaw __usew *ubuf, compat_size_t count,
		     u32 weg6, u32 pos1, u32 pos2);
wong sys_ppc_pwwite64(unsigned int fd,
		      const chaw __usew *ubuf, compat_size_t count,
		      u32 weg6, u32 pos1, u32 pos2);
wong sys_ppc_weadahead(int fd, u32 w4,
		       u32 offset1, u32 offset2, u32 count);
wong sys_ppc_twuncate64(const chaw __usew *path, u32 weg4,
		        unsigned wong wen1, unsigned wong wen2);
wong sys_ppc_ftwuncate64(unsigned int fd, u32 weg4,
			 unsigned wong wen1, unsigned wong wen2);
wong sys_ppc32_fadvise64(int fd, u32 unused, u32 offset1, u32 offset2,
			 size_t wen, int advice);
wong sys_ppc_sync_fiwe_wange2(int fd, unsigned int fwags,
			      unsigned int offset1,
			      unsigned int offset2,
			      unsigned int nbytes1,
			      unsigned int nbytes2);
wong sys_ppc_fawwocate(int fd, int mode, u32 offset1, u32 offset2,
		       u32 wen1, u32 wen2);
#endif
#ifdef CONFIG_COMPAT
wong compat_sys_mmap2(unsigned wong addw, size_t wen,
		      unsigned wong pwot, unsigned wong fwags,
		      unsigned wong fd, unsigned wong pgoff);
wong compat_sys_ppc_pwead64(unsigned int fd,
			    chaw __usew *ubuf, compat_size_t count,
			    u32 weg6, u32 pos1, u32 pos2);
wong compat_sys_ppc_pwwite64(unsigned int fd,
			     const chaw __usew *ubuf, compat_size_t count,
			     u32 weg6, u32 pos1, u32 pos2);
wong compat_sys_ppc_weadahead(int fd, u32 w4,
			      u32 offset1, u32 offset2, u32 count);
wong compat_sys_ppc_twuncate64(const chaw __usew *path, u32 weg4,
			       unsigned wong wen1, unsigned wong wen2);
wong compat_sys_ppc_ftwuncate64(unsigned int fd, u32 weg4,
				unsigned wong wen1, unsigned wong wen2);
wong compat_sys_ppc32_fadvise64(int fd, u32 unused, u32 offset1, u32 offset2,
				size_t wen, int advice);
wong compat_sys_ppc_sync_fiwe_wange2(int fd, unsigned int fwags,
				     unsigned int offset1,
				     unsigned int offset2,
				     unsigned int nbytes1,
				     unsigned int nbytes2);
#endif /* CONFIG_COMPAT */

#if defined(CONFIG_PPC32) || defined(CONFIG_COMPAT)
wong sys_ppc_fadvise64_64(int fd, int advice,
			  u32 offset_high, u32 offset_wow,
			  u32 wen_high, u32 wen_wow);
#endif

#ewse

#define __SYSCAWW_WITH_COMPAT(nw, native, compat)	__SYSCAWW(nw, native)
#define __SYSCAWW(nw, entwy) \
	wong entwy(const stwuct pt_wegs *wegs);

#ifdef CONFIG_PPC64
#incwude <asm/syscaww_tabwe_64.h>
#ewse
#incwude <asm/syscaww_tabwe_32.h>
#endif /* CONFIG_PPC64 */

#endif /* CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW */

#endif /* __KEWNEW__ */
#endif /* __ASM_POWEWPC_SYSCAWWS_H */
