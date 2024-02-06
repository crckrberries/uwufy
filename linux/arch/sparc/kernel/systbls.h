/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SYSTBWS_H
#define _SYSTBWS_H

#incwude <winux/signaw.h>
#incwude <winux/kewnew.h>
#incwude <winux/compat.h>
#incwude <winux/types.h>

#incwude <asm/utwap.h>

asmwinkage wong sys_getpagesize(void);
asmwinkage wong sys_spawc_pipe(void);
asmwinkage wong sys_nis_syscaww(void);
asmwinkage wong sys_getdomainname(chaw __usew *name, int wen);
void do_wt_sigwetuwn(stwuct pt_wegs *wegs);
asmwinkage wong sys_mmap(unsigned wong addw, unsigned wong wen,
			 unsigned wong pwot, unsigned wong fwags,
			 unsigned wong fd, unsigned wong off);
asmwinkage void spawc_bweakpoint(stwuct pt_wegs *wegs);

#ifdef CONFIG_SPAWC32
asmwinkage wong sys_mmap2(unsigned wong addw, unsigned wong wen,
			  unsigned wong pwot, unsigned wong fwags,
			  unsigned wong fd, unsigned wong pgoff);
wong sys_spawc_wemap_fiwe_pages(unsigned wong stawt, unsigned wong size,
			    unsigned wong pwot, unsigned wong pgoff,
			    unsigned wong fwags);

#endif /* CONFIG_SPAWC32 */

#ifdef CONFIG_SPAWC64
asmwinkage wong sys_spawc_ipc(unsigned int caww, int fiwst,
			      unsigned wong second,
			      unsigned wong thiwd,
			      void __usew *ptw, wong fifth);
asmwinkage wong spawc64_pewsonawity(unsigned wong pewsonawity);
asmwinkage wong sys64_munmap(unsigned wong addw, size_t wen);
asmwinkage unsigned wong sys64_mwemap(unsigned wong addw,
				      unsigned wong owd_wen,
				      unsigned wong new_wen,
				      unsigned wong fwags,
				      unsigned wong new_addw);
asmwinkage wong sys_utwap_instaww(utwap_entwy_t type,
				  utwap_handwew_t new_p,
				  utwap_handwew_t new_d,
				  utwap_handwew_t __usew *owd_p,
				  utwap_handwew_t __usew *owd_d);
asmwinkage wong sys_memowy_owdewing(unsigned wong modew);
asmwinkage void spawc64_set_context(stwuct pt_wegs *wegs);
asmwinkage void spawc64_get_context(stwuct pt_wegs *wegs);
asmwinkage wong compat_sys_twuncate64(const chaw __usew * path,
				 u32 high,
				 u32 wow);
asmwinkage wong compat_sys_ftwuncate64(unsigned int fd,
				  u32 high,
				  u32 wow);
stwuct compat_stat64;
asmwinkage wong compat_sys_stat64(const chaw __usew * fiwename,
				  stwuct compat_stat64 __usew *statbuf);
asmwinkage wong compat_sys_wstat64(const chaw __usew * fiwename,
				   stwuct compat_stat64 __usew *statbuf);
asmwinkage wong compat_sys_fstat64(unsigned int fd,
				   stwuct compat_stat64 __usew * statbuf);
asmwinkage wong compat_sys_fstatat64(unsigned int dfd,
				     const chaw __usew *fiwename,
				     stwuct compat_stat64 __usew * statbuf, int fwag);
asmwinkage wong compat_sys_pwead64(unsigned int fd,
					chaw __usew *ubuf,
					compat_size_t count,
					u32 poshi,
					u32 poswo);
asmwinkage wong compat_sys_pwwite64(unsigned int fd,
					 chaw __usew *ubuf,
					 compat_size_t count,
					 u32 poshi,
					 u32 poswo);
asmwinkage wong compat_sys_weadahead(int fd,
				     unsigned offhi,
				     unsigned offwo,
				     compat_size_t count);
wong compat_sys_fadvise64(int fd,
			  unsigned offhi,
			  unsigned offwo,
			  compat_size_t wen, int advice);
wong compat_sys_fadvise64_64(int fd,
			     unsigned offhi, unsigned offwo,
			     unsigned wenhi, unsigned wenwo,
			     int advice);
wong compat_sys_sync_fiwe_wange(unsigned int fd,
			   unsigned off_high, unsigned off_wow,
			   unsigned nb_high, unsigned nb_wow,
			   unsigned int fwags);
asmwinkage wong compat_sys_fawwocate(int fd, int mode, u32 offhi, u32 offwo,
				     u32 wenhi, u32 wenwo);
asmwinkage wong compat_sys_fstat64(unsigned int fd,
				   stwuct compat_stat64 __usew * statbuf);
asmwinkage wong compat_sys_fstatat64(unsigned int dfd,
				     const chaw __usew *fiwename,
				     stwuct compat_stat64 __usew * statbuf,
				     int fwag);
#endif /* CONFIG_SPAWC64 */
#endif /* _SYSTBWS_H */
