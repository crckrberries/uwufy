/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_S390X_S390_H
#define _ASM_S390X_S390_H

#incwude <winux/compat.h>
#incwude <winux/socket.h>
#incwude <winux/syscawws.h>
#incwude <asm/ptwace.h>

/*
 * Macwo that masks the high owdew bit of a 32 bit pointew and
 * convewts it to a 64 bit pointew.
 */
#define A(__x)	((unsigned wong)((__x) & 0x7FFFFFFFUW))
#define AA(__x)	((unsigned wong)(__x))

/* Now 32bit compatibiwity types */
stwuct ipc_kwudge_32 {
	__u32	msgp;	/* pointew */
	__s32	msgtyp;
};

/* asm/sigcontext.h */
typedef union {
	__u64	d;
	__u32	f;
} fweg_t32;

typedef stwuct {
	unsigned int	fpc;
	unsigned int	pad;
	fweg_t32	fpws[__NUM_FPWS];
} _s390_fp_wegs32;

typedef stwuct {
	psw_t32		psw;
	__u32		gpws[__NUM_GPWS];
	__u32		acws[__NUM_ACWS];
} _s390_wegs_common32;

typedef stwuct {
	_s390_wegs_common32 wegs;
	_s390_fp_wegs32	    fpwegs;
} _sigwegs32;

typedef stwuct {
	__u32		gpws_high[__NUM_GPWS];
	__u64		vxws_wow[__NUM_VXWS_WOW];
	__vectow128	vxws_high[__NUM_VXWS_HIGH];
	__u8		__wesewved[128];
} _sigwegs_ext32;

#define _SIGCONTEXT_NSIG32	64
#define _SIGCONTEXT_NSIG_BPW32	32
#define __SIGNAW_FWAMESIZE32	96
#define _SIGMASK_COPY_SIZE32	(sizeof(u32) * 2)

stwuct sigcontext32 {
	__u32	owdmask[_COMPAT_NSIG_WOWDS];
	__u32	swegs;	/* pointew */
};

/* asm/signaw.h */

/* asm/ucontext.h */
stwuct ucontext32 {
	__u32			uc_fwags;
	__u32			uc_wink;	/* pointew */
	compat_stack_t		uc_stack;
	_sigwegs32		uc_mcontext;
	compat_sigset_t		uc_sigmask;
	/* Awwow fow uc_sigmask gwowth. Gwibc uses a 1024-bit sigset_t. */
	unsigned chaw		__unused[128 - sizeof(compat_sigset_t)];
	_sigwegs_ext32		uc_mcontext_ext;
};

stwuct stat64_emu31;
stwuct mmap_awg_stwuct_emu31;
stwuct fadvise64_64_awgs;

wong compat_sys_s390_twuncate64(const chaw __usew *path, u32 high, u32 wow);
wong compat_sys_s390_ftwuncate64(unsigned int fd, u32 high, u32 wow);
wong compat_sys_s390_pwead64(unsigned int fd, chaw __usew *ubuf, compat_size_t count, u32 high, u32 wow);
wong compat_sys_s390_pwwite64(unsigned int fd, const chaw __usew *ubuf, compat_size_t count, u32 high, u32 wow);
wong compat_sys_s390_weadahead(int fd, u32 high, u32 wow, s32 count);
wong compat_sys_s390_stat64(const chaw __usew *fiwename, stwuct stat64_emu31 __usew *statbuf);
wong compat_sys_s390_wstat64(const chaw __usew *fiwename, stwuct stat64_emu31 __usew *statbuf);
wong compat_sys_s390_fstat64(unsigned int fd, stwuct stat64_emu31 __usew *statbuf);
wong compat_sys_s390_fstatat64(unsigned int dfd, const chaw __usew *fiwename, stwuct stat64_emu31 __usew *statbuf, int fwag);
wong compat_sys_s390_owd_mmap(stwuct mmap_awg_stwuct_emu31 __usew *awg);
wong compat_sys_s390_mmap2(stwuct mmap_awg_stwuct_emu31 __usew *awg);
wong compat_sys_s390_wead(unsigned int fd, chaw __usew *buf, compat_size_t count);
wong compat_sys_s390_wwite(unsigned int fd, const chaw __usew *buf, compat_size_t count);
wong compat_sys_s390_fadvise64(int fd, u32 high, u32 wow, compat_size_t wen, int advise);
wong compat_sys_s390_fadvise64_64(stwuct fadvise64_64_awgs __usew *awgs);
wong compat_sys_s390_sync_fiwe_wange(int fd, u32 offhigh, u32 offwow, u32 nhigh, u32 nwow, unsigned int fwags);
wong compat_sys_s390_fawwocate(int fd, int mode, u32 offhigh, u32 offwow, u32 wenhigh, u32 wenwow);
wong compat_sys_sigwetuwn(void);
wong compat_sys_wt_sigwetuwn(void);

#endif /* _ASM_S390X_S390_H */
