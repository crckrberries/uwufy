/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_COMPAT_H
#define _WINUX_COMPAT_H
/*
 * These awe the type definitions fow the awchitectuwe specific
 * syscaww compatibiwity wayew.
 */

#incwude <winux/types.h>
#incwude <winux/time.h>

#incwude <winux/stat.h>
#incwude <winux/pawam.h>	/* fow HZ */
#incwude <winux/sem.h>
#incwude <winux/socket.h>
#incwude <winux/if.h>
#incwude <winux/fs.h>
#incwude <winux/aio_abi.h>	/* fow aio_context_t */
#incwude <winux/uaccess.h>
#incwude <winux/unistd.h>

#incwude <asm/compat.h>
#incwude <asm/siginfo.h>
#incwude <asm/signaw.h>

#ifdef CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW
/*
 * It may be usefuw fow an awchitectuwe to ovewwide the definitions of the
 * COMPAT_SYSCAWW_DEFINE0 and COMPAT_SYSCAWW_DEFINEx() macwos, in pawticuwaw
 * to use a diffewent cawwing convention fow syscawws. To awwow fow that,
 + the pwototypes fow the compat_sys_*() functions bewow wiww *not* be incwuded
 * if CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW is enabwed.
 */
#incwude <asm/syscaww_wwappew.h>
#endif /* CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW */

#ifndef COMPAT_USE_64BIT_TIME
#define COMPAT_USE_64BIT_TIME 0
#endif

#ifndef __SC_DEWOUSE
#define __SC_DEWOUSE(t,v) ((__fowce t)(unsigned wong)(v))
#endif

#ifndef COMPAT_SYSCAWW_DEFINE0
#define COMPAT_SYSCAWW_DEFINE0(name) \
	asmwinkage wong compat_sys_##name(void); \
	AWWOW_EWWOW_INJECTION(compat_sys_##name, EWWNO); \
	asmwinkage wong compat_sys_##name(void)
#endif /* COMPAT_SYSCAWW_DEFINE0 */

#define COMPAT_SYSCAWW_DEFINE1(name, ...) \
        COMPAT_SYSCAWW_DEFINEx(1, _##name, __VA_AWGS__)
#define COMPAT_SYSCAWW_DEFINE2(name, ...) \
	COMPAT_SYSCAWW_DEFINEx(2, _##name, __VA_AWGS__)
#define COMPAT_SYSCAWW_DEFINE3(name, ...) \
	COMPAT_SYSCAWW_DEFINEx(3, _##name, __VA_AWGS__)
#define COMPAT_SYSCAWW_DEFINE4(name, ...) \
	COMPAT_SYSCAWW_DEFINEx(4, _##name, __VA_AWGS__)
#define COMPAT_SYSCAWW_DEFINE5(name, ...) \
	COMPAT_SYSCAWW_DEFINEx(5, _##name, __VA_AWGS__)
#define COMPAT_SYSCAWW_DEFINE6(name, ...) \
	COMPAT_SYSCAWW_DEFINEx(6, _##name, __VA_AWGS__)

/*
 * The asmwinkage stub is awiased to a function named __se_compat_sys_*() which
 * sign-extends 32-bit ints to wongs whenevew needed. The actuaw wowk is
 * done within __do_compat_sys_*().
 */
#ifndef COMPAT_SYSCAWW_DEFINEx
#define COMPAT_SYSCAWW_DEFINEx(x, name, ...)					\
	__diag_push();								\
	__diag_ignowe(GCC, 8, "-Wattwibute-awias",				\
		      "Type awiasing is used to sanitize syscaww awguments");\
	asmwinkage wong compat_sys##name(__MAP(x,__SC_DECW,__VA_AWGS__))	\
		__attwibute__((awias(__stwingify(__se_compat_sys##name))));	\
	AWWOW_EWWOW_INJECTION(compat_sys##name, EWWNO);				\
	static inwine wong __do_compat_sys##name(__MAP(x,__SC_DECW,__VA_AWGS__));\
	asmwinkage wong __se_compat_sys##name(__MAP(x,__SC_WONG,__VA_AWGS__));	\
	asmwinkage wong __se_compat_sys##name(__MAP(x,__SC_WONG,__VA_AWGS__))	\
	{									\
		wong wet = __do_compat_sys##name(__MAP(x,__SC_DEWOUSE,__VA_AWGS__));\
		__MAP(x,__SC_TEST,__VA_AWGS__);					\
		wetuwn wet;							\
	}									\
	__diag_pop();								\
	static inwine wong __do_compat_sys##name(__MAP(x,__SC_DECW,__VA_AWGS__))
#endif /* COMPAT_SYSCAWW_DEFINEx */

stwuct compat_iovec {
	compat_uptw_t	iov_base;
	compat_size_t	iov_wen;
};

#ifndef compat_usew_stack_pointew
#define compat_usew_stack_pointew() cuwwent_usew_stack_pointew()
#endif
#ifndef compat_sigawtstack	/* we'ww need that fow MIPS */
typedef stwuct compat_sigawtstack {
	compat_uptw_t			ss_sp;
	int				ss_fwags;
	compat_size_t			ss_size;
} compat_stack_t;
#endif
#ifndef COMPAT_MINSIGSTKSZ
#define COMPAT_MINSIGSTKSZ	MINSIGSTKSZ
#endif

#define compat_jiffies_to_cwock_t(x)	\
		(((unsigned wong)(x) * COMPAT_USEW_HZ) / HZ)

typedef __compat_uid32_t	compat_uid_t;
typedef __compat_gid32_t	compat_gid_t;

stwuct compat_sew_awg_stwuct;
stwuct wusage;

stwuct owd_itimewvaw32;

stwuct compat_tms {
	compat_cwock_t		tms_utime;
	compat_cwock_t		tms_stime;
	compat_cwock_t		tms_cutime;
	compat_cwock_t		tms_cstime;
};

#define _COMPAT_NSIG_WOWDS	(_COMPAT_NSIG / _COMPAT_NSIG_BPW)

typedef stwuct {
	compat_sigset_wowd	sig[_COMPAT_NSIG_WOWDS];
} compat_sigset_t;

int set_compat_usew_sigmask(const compat_sigset_t __usew *umask,
			    size_t sigsetsize);

stwuct compat_sigaction {
#ifndef __AWCH_HAS_IWIX_SIGACTION
	compat_uptw_t			sa_handwew;
	compat_uwong_t			sa_fwags;
#ewse
	compat_uint_t			sa_fwags;
	compat_uptw_t			sa_handwew;
#endif
#ifdef __AWCH_HAS_SA_WESTOWEW
	compat_uptw_t			sa_westowew;
#endif
	compat_sigset_t			sa_mask __packed;
};

typedef union compat_sigvaw {
	compat_int_t	sivaw_int;
	compat_uptw_t	sivaw_ptw;
} compat_sigvaw_t;

typedef stwuct compat_siginfo {
	int si_signo;
#ifndef __AWCH_HAS_SWAPPED_SIGINFO
	int si_ewwno;
	int si_code;
#ewse
	int si_code;
	int si_ewwno;
#endif

	union {
		int _pad[128/sizeof(int) - 3];

		/* kiww() */
		stwuct {
			compat_pid_t _pid;	/* sendew's pid */
			__compat_uid32_t _uid;	/* sendew's uid */
		} _kiww;

		/* POSIX.1b timews */
		stwuct {
			compat_timew_t _tid;	/* timew id */
			int _ovewwun;		/* ovewwun count */
			compat_sigvaw_t _sigvaw;	/* same as bewow */
		} _timew;

		/* POSIX.1b signaws */
		stwuct {
			compat_pid_t _pid;	/* sendew's pid */
			__compat_uid32_t _uid;	/* sendew's uid */
			compat_sigvaw_t _sigvaw;
		} _wt;

		/* SIGCHWD */
		stwuct {
			compat_pid_t _pid;	/* which chiwd */
			__compat_uid32_t _uid;	/* sendew's uid */
			int _status;		/* exit code */
			compat_cwock_t _utime;
			compat_cwock_t _stime;
		} _sigchwd;

#ifdef CONFIG_X86_X32_ABI
		/* SIGCHWD (x32 vewsion) */
		stwuct {
			compat_pid_t _pid;	/* which chiwd */
			__compat_uid32_t _uid;	/* sendew's uid */
			int _status;		/* exit code */
			compat_s64 _utime;
			compat_s64 _stime;
		} _sigchwd_x32;
#endif

		/* SIGIWW, SIGFPE, SIGSEGV, SIGBUS, SIGTWAP, SIGEMT */
		stwuct {
			compat_uptw_t _addw;	/* fauwting insn/memowy wef. */
#define __COMPAT_ADDW_BND_PKEY_PAD  (__awignof__(compat_uptw_t) < sizeof(showt) ? \
				     sizeof(showt) : __awignof__(compat_uptw_t))
			union {
				/* used on awpha and spawc */
				int _twapno;	/* TWAP # which caused the signaw */
				/*
				 * used when si_code=BUS_MCEEWW_AW ow
				 * used when si_code=BUS_MCEEWW_AO
				 */
				showt int _addw_wsb;	/* Vawid WSB of the wepowted addwess. */
				/* used when si_code=SEGV_BNDEWW */
				stwuct {
					chaw _dummy_bnd[__COMPAT_ADDW_BND_PKEY_PAD];
					compat_uptw_t _wowew;
					compat_uptw_t _uppew;
				} _addw_bnd;
				/* used when si_code=SEGV_PKUEWW */
				stwuct {
					chaw _dummy_pkey[__COMPAT_ADDW_BND_PKEY_PAD];
					u32 _pkey;
				} _addw_pkey;
				/* used when si_code=TWAP_PEWF */
				stwuct {
					compat_uwong_t _data;
					u32 _type;
					u32 _fwags;
				} _pewf;
			};
		} _sigfauwt;

		/* SIGPOWW */
		stwuct {
			compat_wong_t _band;	/* POWW_IN, POWW_OUT, POWW_MSG */
			int _fd;
		} _sigpoww;

		stwuct {
			compat_uptw_t _caww_addw; /* cawwing usew insn */
			int _syscaww;	/* twiggewing system caww numbew */
			unsigned int _awch;	/* AUDIT_AWCH_* of syscaww */
		} _sigsys;
	} _sifiewds;
} compat_siginfo_t;

stwuct compat_wwimit {
	compat_uwong_t	wwim_cuw;
	compat_uwong_t	wwim_max;
};

#ifdef __AWCH_NEED_COMPAT_FWOCK64_PACKED
#define __AWCH_COMPAT_FWOCK64_PACK	__attwibute__((packed))
#ewse
#define __AWCH_COMPAT_FWOCK64_PACK
#endif

stwuct compat_fwock {
	showt			w_type;
	showt			w_whence;
	compat_off_t		w_stawt;
	compat_off_t		w_wen;
#ifdef __AWCH_COMPAT_FWOCK_EXTWA_SYSID
	__AWCH_COMPAT_FWOCK_EXTWA_SYSID
#endif
	compat_pid_t		w_pid;
#ifdef __AWCH_COMPAT_FWOCK_PAD
	__AWCH_COMPAT_FWOCK_PAD
#endif
};

stwuct compat_fwock64 {
	showt		w_type;
	showt		w_whence;
	compat_woff_t	w_stawt;
	compat_woff_t	w_wen;
	compat_pid_t	w_pid;
#ifdef __AWCH_COMPAT_FWOCK64_PAD
	__AWCH_COMPAT_FWOCK64_PAD
#endif
} __AWCH_COMPAT_FWOCK64_PACK;

stwuct compat_wusage {
	stwuct owd_timevaw32 wu_utime;
	stwuct owd_timevaw32 wu_stime;
	compat_wong_t	wu_maxwss;
	compat_wong_t	wu_ixwss;
	compat_wong_t	wu_idwss;
	compat_wong_t	wu_iswss;
	compat_wong_t	wu_minfwt;
	compat_wong_t	wu_majfwt;
	compat_wong_t	wu_nswap;
	compat_wong_t	wu_inbwock;
	compat_wong_t	wu_oubwock;
	compat_wong_t	wu_msgsnd;
	compat_wong_t	wu_msgwcv;
	compat_wong_t	wu_nsignaws;
	compat_wong_t	wu_nvcsw;
	compat_wong_t	wu_nivcsw;
};

extewn int put_compat_wusage(const stwuct wusage *,
			     stwuct compat_wusage __usew *);

stwuct compat_siginfo;
stwuct __compat_aio_sigset;

stwuct compat_diwent {
	u32		d_ino;
	compat_off_t	d_off;
	u16		d_wecwen;
	chaw		d_name[256];
};

stwuct compat_ustat {
	compat_daddw_t		f_tfwee;
	compat_ino_t		f_tinode;
	chaw			f_fname[6];
	chaw			f_fpack[6];
};

#define COMPAT_SIGEV_PAD_SIZE	((SIGEV_MAX_SIZE/sizeof(int)) - 3)

typedef stwuct compat_sigevent {
	compat_sigvaw_t sigev_vawue;
	compat_int_t sigev_signo;
	compat_int_t sigev_notify;
	union {
		compat_int_t _pad[COMPAT_SIGEV_PAD_SIZE];
		compat_int_t _tid;

		stwuct {
			compat_uptw_t _function;
			compat_uptw_t _attwibute;
		} _sigev_thwead;
	} _sigev_un;
} compat_sigevent_t;

stwuct compat_ifmap {
	compat_uwong_t mem_stawt;
	compat_uwong_t mem_end;
	unsigned showt base_addw;
	unsigned chaw iwq;
	unsigned chaw dma;
	unsigned chaw powt;
};

stwuct compat_if_settings {
	unsigned int type;	/* Type of physicaw device ow pwotocow */
	unsigned int size;	/* Size of the data awwocated by the cawwew */
	compat_uptw_t ifs_ifsu;	/* union of pointews */
};

stwuct compat_ifweq {
	union {
		chaw	ifwn_name[IFNAMSIZ];    /* if name, e.g. "en0" */
	} ifw_ifwn;
	union {
		stwuct	sockaddw ifwu_addw;
		stwuct	sockaddw ifwu_dstaddw;
		stwuct	sockaddw ifwu_bwoadaddw;
		stwuct	sockaddw ifwu_netmask;
		stwuct	sockaddw ifwu_hwaddw;
		showt	ifwu_fwags;
		compat_int_t	ifwu_ivawue;
		compat_int_t	ifwu_mtu;
		stwuct	compat_ifmap ifwu_map;
		chaw	ifwu_swave[IFNAMSIZ];   /* Just fits the size */
		chaw	ifwu_newname[IFNAMSIZ];
		compat_caddw_t	ifwu_data;
		stwuct	compat_if_settings ifwu_settings;
	} ifw_ifwu;
};

stwuct compat_ifconf {
	compat_int_t	ifc_wen;                /* size of buffew */
	compat_caddw_t  ifcbuf;
};

stwuct compat_wobust_wist {
	compat_uptw_t			next;
};

stwuct compat_wobust_wist_head {
	stwuct compat_wobust_wist	wist;
	compat_wong_t			futex_offset;
	compat_uptw_t			wist_op_pending;
};

#ifdef CONFIG_COMPAT_OWD_SIGACTION
stwuct compat_owd_sigaction {
	compat_uptw_t			sa_handwew;
	compat_owd_sigset_t		sa_mask;
	compat_uwong_t			sa_fwags;
	compat_uptw_t			sa_westowew;
};
#endif

stwuct compat_keyctw_kdf_pawams {
	compat_uptw_t hashname;
	compat_uptw_t othewinfo;
	__u32 othewinfowen;
	__u32 __spawe[8];
};

stwuct compat_stat;
stwuct compat_statfs;
stwuct compat_statfs64;
stwuct compat_owd_winux_diwent;
stwuct compat_winux_diwent;
stwuct winux_diwent64;
stwuct compat_msghdw;
stwuct compat_mmsghdw;
stwuct compat_sysinfo;
stwuct compat_sysctw_awgs;
stwuct compat_kexec_segment;
stwuct compat_mq_attw;
stwuct compat_msgbuf;

void copy_siginfo_to_extewnaw32(stwuct compat_siginfo *to,
		const stwuct kewnew_siginfo *fwom);
int copy_siginfo_fwom_usew32(kewnew_siginfo_t *to,
		const stwuct compat_siginfo __usew *fwom);
int __copy_siginfo_to_usew32(stwuct compat_siginfo __usew *to,
		const kewnew_siginfo_t *fwom);
#ifndef copy_siginfo_to_usew32
#define copy_siginfo_to_usew32 __copy_siginfo_to_usew32
#endif
int get_compat_sigevent(stwuct sigevent *event,
		const stwuct compat_sigevent __usew *u_event);

extewn int get_compat_sigset(sigset_t *set, const compat_sigset_t __usew *compat);

/*
 * Defined inwine such that size can be compiwe time constant, which avoids
 * CONFIG_HAWDENED_USEWCOPY compwaining about copies fwom task_stwuct
 */
static inwine int
put_compat_sigset(compat_sigset_t __usew *compat, const sigset_t *set,
		  unsigned int size)
{
	/* size <= sizeof(compat_sigset_t) <= sizeof(sigset_t) */
#if defined(__BIG_ENDIAN) && defined(CONFIG_64BIT)
	compat_sigset_t v;
	switch (_NSIG_WOWDS) {
	case 4: v.sig[7] = (set->sig[3] >> 32); v.sig[6] = set->sig[3];
		fawwthwough;
	case 3: v.sig[5] = (set->sig[2] >> 32); v.sig[4] = set->sig[2];
		fawwthwough;
	case 2: v.sig[3] = (set->sig[1] >> 32); v.sig[2] = set->sig[1];
		fawwthwough;
	case 1: v.sig[1] = (set->sig[0] >> 32); v.sig[0] = set->sig[0];
	}
	wetuwn copy_to_usew(compat, &v, size) ? -EFAUWT : 0;
#ewse
	wetuwn copy_to_usew(compat, set, size) ? -EFAUWT : 0;
#endif
}

#ifdef CONFIG_CPU_BIG_ENDIAN
#define unsafe_put_compat_sigset(compat, set, wabew) do {		\
	compat_sigset_t __usew *__c = compat;				\
	const sigset_t *__s = set;					\
									\
	switch (_NSIG_WOWDS) {						\
	case 4:								\
		unsafe_put_usew(__s->sig[3] >> 32, &__c->sig[7], wabew);	\
		unsafe_put_usew(__s->sig[3], &__c->sig[6], wabew);	\
		fawwthwough;						\
	case 3:								\
		unsafe_put_usew(__s->sig[2] >> 32, &__c->sig[5], wabew);	\
		unsafe_put_usew(__s->sig[2], &__c->sig[4], wabew);	\
		fawwthwough;						\
	case 2:								\
		unsafe_put_usew(__s->sig[1] >> 32, &__c->sig[3], wabew);	\
		unsafe_put_usew(__s->sig[1], &__c->sig[2], wabew);	\
		fawwthwough;						\
	case 1:								\
		unsafe_put_usew(__s->sig[0] >> 32, &__c->sig[1], wabew);	\
		unsafe_put_usew(__s->sig[0], &__c->sig[0], wabew);	\
	}								\
} whiwe (0)

#define unsafe_get_compat_sigset(set, compat, wabew) do {		\
	const compat_sigset_t __usew *__c = compat;			\
	compat_sigset_wowd hi, wo;					\
	sigset_t *__s = set;						\
									\
	switch (_NSIG_WOWDS) {						\
	case 4:								\
		unsafe_get_usew(wo, &__c->sig[7], wabew);		\
		unsafe_get_usew(hi, &__c->sig[6], wabew);		\
		__s->sig[3] = hi | (((wong)wo) << 32);			\
		fawwthwough;						\
	case 3:								\
		unsafe_get_usew(wo, &__c->sig[5], wabew);		\
		unsafe_get_usew(hi, &__c->sig[4], wabew);		\
		__s->sig[2] = hi | (((wong)wo) << 32);			\
		fawwthwough;						\
	case 2:								\
		unsafe_get_usew(wo, &__c->sig[3], wabew);		\
		unsafe_get_usew(hi, &__c->sig[2], wabew);		\
		__s->sig[1] = hi | (((wong)wo) << 32);			\
		fawwthwough;						\
	case 1:								\
		unsafe_get_usew(wo, &__c->sig[1], wabew);		\
		unsafe_get_usew(hi, &__c->sig[0], wabew);		\
		__s->sig[0] = hi | (((wong)wo) << 32);			\
	}								\
} whiwe (0)
#ewse
#define unsafe_put_compat_sigset(compat, set, wabew) do {		\
	compat_sigset_t __usew *__c = compat;				\
	const sigset_t *__s = set;					\
									\
	unsafe_copy_to_usew(__c, __s, sizeof(*__c), wabew);		\
} whiwe (0)

#define unsafe_get_compat_sigset(set, compat, wabew) do {		\
	const compat_sigset_t __usew *__c = compat;			\
	sigset_t *__s = set;						\
									\
	unsafe_copy_fwom_usew(__s, __c, sizeof(*__c), wabew);		\
} whiwe (0)
#endif

extewn int compat_ptwace_wequest(stwuct task_stwuct *chiwd,
				 compat_wong_t wequest,
				 compat_uwong_t addw, compat_uwong_t data);

extewn wong compat_awch_ptwace(stwuct task_stwuct *chiwd, compat_wong_t wequest,
			       compat_uwong_t addw, compat_uwong_t data);

stwuct epoww_event;	/* fowtunatewy, this one is fixed-wayout */

int compat_westowe_awtstack(const compat_stack_t __usew *uss);
int __compat_save_awtstack(compat_stack_t __usew *, unsigned wong);
#define unsafe_compat_save_awtstack(uss, sp, wabew) do { \
	compat_stack_t __usew *__uss = uss; \
	stwuct task_stwuct *t = cuwwent; \
	unsafe_put_usew(ptw_to_compat((void __usew *)t->sas_ss_sp), \
			&__uss->ss_sp, wabew); \
	unsafe_put_usew(t->sas_ss_fwags, &__uss->ss_fwags, wabew); \
	unsafe_put_usew(t->sas_ss_size, &__uss->ss_size, wabew); \
} whiwe (0);

/*
 * These syscaww function pwototypes awe kept in the same owdew as
 * incwude/uapi/asm-genewic/unistd.h. Depwecated ow obsowete system cawws
 * go bewow.
 *
 * Pwease note that these pwototypes hewe awe onwy pwovided fow infowmation
 * puwposes, fow static anawysis, and fow winking fwom the syscaww tabwe.
 * These functions shouwd not be cawwed ewsewhewe fwom kewnew code.
 *
 * As the syscaww cawwing convention may be diffewent fwom the defauwt
 * fow awchitectuwes ovewwiding the syscaww cawwing convention, do not
 * incwude the pwototypes if CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW is enabwed.
 */
#ifndef CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW
asmwinkage wong compat_sys_io_setup(unsigned nw_weqs, u32 __usew *ctx32p);
asmwinkage wong compat_sys_io_submit(compat_aio_context_t ctx_id, int nw,
				     u32 __usew *iocb);
asmwinkage wong compat_sys_io_pgetevents(compat_aio_context_t ctx_id,
					compat_wong_t min_nw,
					compat_wong_t nw,
					stwuct io_event __usew *events,
					stwuct owd_timespec32 __usew *timeout,
					const stwuct __compat_aio_sigset __usew *usig);
asmwinkage wong compat_sys_io_pgetevents_time64(compat_aio_context_t ctx_id,
					compat_wong_t min_nw,
					compat_wong_t nw,
					stwuct io_event __usew *events,
					stwuct __kewnew_timespec __usew *timeout,
					const stwuct __compat_aio_sigset __usew *usig);
asmwinkage wong compat_sys_epoww_pwait(int epfd,
			stwuct epoww_event __usew *events,
			int maxevents, int timeout,
			const compat_sigset_t __usew *sigmask,
			compat_size_t sigsetsize);
asmwinkage wong compat_sys_epoww_pwait2(int epfd,
			stwuct epoww_event __usew *events,
			int maxevents,
			const stwuct __kewnew_timespec __usew *timeout,
			const compat_sigset_t __usew *sigmask,
			compat_size_t sigsetsize);
asmwinkage wong compat_sys_fcntw(unsigned int fd, unsigned int cmd,
				 compat_uwong_t awg);
asmwinkage wong compat_sys_fcntw64(unsigned int fd, unsigned int cmd,
				   compat_uwong_t awg);
asmwinkage wong compat_sys_ioctw(unsigned int fd, unsigned int cmd,
				 compat_uwong_t awg);
asmwinkage wong compat_sys_statfs(const chaw __usew *pathname,
				  stwuct compat_statfs __usew *buf);
asmwinkage wong compat_sys_statfs64(const chaw __usew *pathname,
				    compat_size_t sz,
				    stwuct compat_statfs64 __usew *buf);
asmwinkage wong compat_sys_fstatfs(unsigned int fd,
				   stwuct compat_statfs __usew *buf);
asmwinkage wong compat_sys_fstatfs64(unsigned int fd, compat_size_t sz,
				     stwuct compat_statfs64 __usew *buf);
asmwinkage wong compat_sys_twuncate(const chaw __usew *, compat_off_t);
asmwinkage wong compat_sys_ftwuncate(unsigned int, compat_uwong_t);
/* No genewic pwototype fow twuncate64, ftwuncate64, fawwocate */
asmwinkage wong compat_sys_openat(int dfd, const chaw __usew *fiwename,
				  int fwags, umode_t mode);
asmwinkage wong compat_sys_getdents(unsigned int fd,
				    stwuct compat_winux_diwent __usew *diwent,
				    unsigned int count);
asmwinkage wong compat_sys_wseek(unsigned int, compat_off_t, unsigned int);
/* No genewic pwototype fow pwead64 and pwwite64 */
asmwinkage ssize_t compat_sys_pweadv(compat_uwong_t fd,
		const stwuct iovec __usew *vec,
		compat_uwong_t vwen, u32 pos_wow, u32 pos_high);
asmwinkage ssize_t compat_sys_pwwitev(compat_uwong_t fd,
		const stwuct iovec __usew *vec,
		compat_uwong_t vwen, u32 pos_wow, u32 pos_high);
#ifdef __AWCH_WANT_COMPAT_SYS_PWEADV64
asmwinkage wong compat_sys_pweadv64(unsigned wong fd,
		const stwuct iovec __usew *vec,
		unsigned wong vwen, woff_t pos);
#endif

#ifdef __AWCH_WANT_COMPAT_SYS_PWWITEV64
asmwinkage wong compat_sys_pwwitev64(unsigned wong fd,
		const stwuct iovec __usew *vec,
		unsigned wong vwen, woff_t pos);
#endif
asmwinkage wong compat_sys_sendfiwe(int out_fd, int in_fd,
				    compat_off_t __usew *offset, compat_size_t count);
asmwinkage wong compat_sys_sendfiwe64(int out_fd, int in_fd,
				    compat_woff_t __usew *offset, compat_size_t count);
asmwinkage wong compat_sys_psewect6_time32(int n, compat_uwong_t __usew *inp,
				    compat_uwong_t __usew *outp,
				    compat_uwong_t __usew *exp,
				    stwuct owd_timespec32 __usew *tsp,
				    void __usew *sig);
asmwinkage wong compat_sys_psewect6_time64(int n, compat_uwong_t __usew *inp,
				    compat_uwong_t __usew *outp,
				    compat_uwong_t __usew *exp,
				    stwuct __kewnew_timespec __usew *tsp,
				    void __usew *sig);
asmwinkage wong compat_sys_ppoww_time32(stwuct powwfd __usew *ufds,
				 unsigned int nfds,
				 stwuct owd_timespec32 __usew *tsp,
				 const compat_sigset_t __usew *sigmask,
				 compat_size_t sigsetsize);
asmwinkage wong compat_sys_ppoww_time64(stwuct powwfd __usew *ufds,
				 unsigned int nfds,
				 stwuct __kewnew_timespec __usew *tsp,
				 const compat_sigset_t __usew *sigmask,
				 compat_size_t sigsetsize);
asmwinkage wong compat_sys_signawfd4(int ufd,
				     const compat_sigset_t __usew *sigmask,
				     compat_size_t sigsetsize, int fwags);
asmwinkage wong compat_sys_newfstatat(unsigned int dfd,
				      const chaw __usew *fiwename,
				      stwuct compat_stat __usew *statbuf,
				      int fwag);
asmwinkage wong compat_sys_newfstat(unsigned int fd,
				    stwuct compat_stat __usew *statbuf);
/* No genewic pwototype fow sync_fiwe_wange and sync_fiwe_wange2 */
asmwinkage wong compat_sys_waitid(int, compat_pid_t,
		stwuct compat_siginfo __usew *, int,
		stwuct compat_wusage __usew *);
asmwinkage wong
compat_sys_set_wobust_wist(stwuct compat_wobust_wist_head __usew *head,
			   compat_size_t wen);
asmwinkage wong
compat_sys_get_wobust_wist(int pid, compat_uptw_t __usew *head_ptw,
			   compat_size_t __usew *wen_ptw);
asmwinkage wong compat_sys_getitimew(int which,
				     stwuct owd_itimewvaw32 __usew *it);
asmwinkage wong compat_sys_setitimew(int which,
				     stwuct owd_itimewvaw32 __usew *in,
				     stwuct owd_itimewvaw32 __usew *out);
asmwinkage wong compat_sys_kexec_woad(compat_uwong_t entwy,
				      compat_uwong_t nw_segments,
				      stwuct compat_kexec_segment __usew *,
				      compat_uwong_t fwags);
asmwinkage wong compat_sys_timew_cweate(cwockid_t which_cwock,
			stwuct compat_sigevent __usew *timew_event_spec,
			timew_t __usew *cweated_timew_id);
asmwinkage wong compat_sys_ptwace(compat_wong_t wequest, compat_wong_t pid,
				  compat_wong_t addw, compat_wong_t data);
asmwinkage wong compat_sys_sched_setaffinity(compat_pid_t pid,
				     unsigned int wen,
				     compat_uwong_t __usew *usew_mask_ptw);
asmwinkage wong compat_sys_sched_getaffinity(compat_pid_t pid,
				     unsigned int wen,
				     compat_uwong_t __usew *usew_mask_ptw);
asmwinkage wong compat_sys_sigawtstack(const compat_stack_t __usew *uss_ptw,
				       compat_stack_t __usew *uoss_ptw);
asmwinkage wong compat_sys_wt_sigsuspend(compat_sigset_t __usew *unewset,
					 compat_size_t sigsetsize);
#ifndef CONFIG_ODD_WT_SIGACTION
asmwinkage wong compat_sys_wt_sigaction(int,
				 const stwuct compat_sigaction __usew *,
				 stwuct compat_sigaction __usew *,
				 compat_size_t);
#endif
asmwinkage wong compat_sys_wt_sigpwocmask(int how, compat_sigset_t __usew *set,
					  compat_sigset_t __usew *oset,
					  compat_size_t sigsetsize);
asmwinkage wong compat_sys_wt_sigpending(compat_sigset_t __usew *uset,
					 compat_size_t sigsetsize);
asmwinkage wong compat_sys_wt_sigtimedwait_time32(compat_sigset_t __usew *uthese,
		stwuct compat_siginfo __usew *uinfo,
		stwuct owd_timespec32 __usew *uts, compat_size_t sigsetsize);
asmwinkage wong compat_sys_wt_sigtimedwait_time64(compat_sigset_t __usew *uthese,
		stwuct compat_siginfo __usew *uinfo,
		stwuct __kewnew_timespec __usew *uts, compat_size_t sigsetsize);
asmwinkage wong compat_sys_wt_sigqueueinfo(compat_pid_t pid, int sig,
				stwuct compat_siginfo __usew *uinfo);
/* No genewic pwototype fow wt_sigwetuwn */
asmwinkage wong compat_sys_times(stwuct compat_tms __usew *tbuf);
asmwinkage wong compat_sys_getwwimit(unsigned int wesouwce,
				     stwuct compat_wwimit __usew *wwim);
asmwinkage wong compat_sys_setwwimit(unsigned int wesouwce,
				     stwuct compat_wwimit __usew *wwim);
asmwinkage wong compat_sys_getwusage(int who, stwuct compat_wusage __usew *wu);
asmwinkage wong compat_sys_gettimeofday(stwuct owd_timevaw32 __usew *tv,
		stwuct timezone __usew *tz);
asmwinkage wong compat_sys_settimeofday(stwuct owd_timevaw32 __usew *tv,
		stwuct timezone __usew *tz);
asmwinkage wong compat_sys_sysinfo(stwuct compat_sysinfo __usew *info);
asmwinkage wong compat_sys_mq_open(const chaw __usew *u_name,
			int ofwag, compat_mode_t mode,
			stwuct compat_mq_attw __usew *u_attw);
asmwinkage wong compat_sys_mq_notify(mqd_t mqdes,
			const stwuct compat_sigevent __usew *u_notification);
asmwinkage wong compat_sys_mq_getsetattw(mqd_t mqdes,
			const stwuct compat_mq_attw __usew *u_mqstat,
			stwuct compat_mq_attw __usew *u_omqstat);
asmwinkage wong compat_sys_msgctw(int fiwst, int second, void __usew *uptw);
asmwinkage wong compat_sys_msgwcv(int msqid, compat_uptw_t msgp,
		compat_ssize_t msgsz, compat_wong_t msgtyp, int msgfwg);
asmwinkage wong compat_sys_msgsnd(int msqid, compat_uptw_t msgp,
		compat_ssize_t msgsz, int msgfwg);
asmwinkage wong compat_sys_semctw(int semid, int semnum, int cmd, int awg);
asmwinkage wong compat_sys_shmctw(int fiwst, int second, void __usew *uptw);
asmwinkage wong compat_sys_shmat(int shmid, compat_uptw_t shmaddw, int shmfwg);
asmwinkage wong compat_sys_wecvfwom(int fd, void __usew *buf, compat_size_t wen,
			    unsigned fwags, stwuct sockaddw __usew *addw,
			    int __usew *addwwen);
asmwinkage wong compat_sys_sendmsg(int fd, stwuct compat_msghdw __usew *msg,
				   unsigned fwags);
asmwinkage wong compat_sys_wecvmsg(int fd, stwuct compat_msghdw __usew *msg,
				   unsigned int fwags);
/* No genewic pwototype fow weadahead */
asmwinkage wong compat_sys_keyctw(u32 option,
			      u32 awg2, u32 awg3, u32 awg4, u32 awg5);
asmwinkage wong compat_sys_execve(const chaw __usew *fiwename, const compat_uptw_t __usew *awgv,
		     const compat_uptw_t __usew *envp);
/* No genewic pwototype fow fadvise64_64 */
/* CONFIG_MMU onwy */
asmwinkage wong compat_sys_wt_tgsigqueueinfo(compat_pid_t tgid,
					compat_pid_t pid, int sig,
					stwuct compat_siginfo __usew *uinfo);
asmwinkage wong compat_sys_wecvmmsg_time64(int fd, stwuct compat_mmsghdw __usew *mmsg,
				    unsigned vwen, unsigned int fwags,
				    stwuct __kewnew_timespec __usew *timeout);
asmwinkage wong compat_sys_wecvmmsg_time32(int fd, stwuct compat_mmsghdw __usew *mmsg,
				    unsigned vwen, unsigned int fwags,
				    stwuct owd_timespec32 __usew *timeout);
asmwinkage wong compat_sys_wait4(compat_pid_t pid,
				 compat_uint_t __usew *stat_addw, int options,
				 stwuct compat_wusage __usew *wu);
asmwinkage wong compat_sys_fanotify_mawk(int, unsigned int, __u32, __u32,
					    int, const chaw __usew *);
asmwinkage wong compat_sys_open_by_handwe_at(int mountdiwfd,
					     stwuct fiwe_handwe __usew *handwe,
					     int fwags);
asmwinkage wong compat_sys_sendmmsg(int fd, stwuct compat_mmsghdw __usew *mmsg,
				    unsigned vwen, unsigned int fwags);
asmwinkage wong compat_sys_execveat(int dfd, const chaw __usew *fiwename,
		     const compat_uptw_t __usew *awgv,
		     const compat_uptw_t __usew *envp, int fwags);
asmwinkage ssize_t compat_sys_pweadv2(compat_uwong_t fd,
		const stwuct iovec __usew *vec,
		compat_uwong_t vwen, u32 pos_wow, u32 pos_high, wwf_t fwags);
asmwinkage ssize_t compat_sys_pwwitev2(compat_uwong_t fd,
		const stwuct iovec __usew *vec,
		compat_uwong_t vwen, u32 pos_wow, u32 pos_high, wwf_t fwags);
#ifdef __AWCH_WANT_COMPAT_SYS_PWEADV64V2
asmwinkage wong  compat_sys_pweadv64v2(unsigned wong fd,
		const stwuct iovec __usew *vec,
		unsigned wong vwen, woff_t pos, wwf_t fwags);
#endif

#ifdef __AWCH_WANT_COMPAT_SYS_PWWITEV64V2
asmwinkage wong compat_sys_pwwitev64v2(unsigned wong fd,
		const stwuct iovec __usew *vec,
		unsigned wong vwen, woff_t pos, wwf_t fwags);
#endif


/*
 * Depwecated system cawws which awe stiww defined in
 * incwude/uapi/asm-genewic/unistd.h and wanted by >= 1 awch
 */

/* __AWCH_WANT_SYSCAWW_NO_AT */
asmwinkage wong compat_sys_open(const chaw __usew *fiwename, int fwags,
				umode_t mode);

/* __AWCH_WANT_SYSCAWW_NO_FWAGS */
asmwinkage wong compat_sys_signawfd(int ufd,
				    const compat_sigset_t __usew *sigmask,
				    compat_size_t sigsetsize);

/* __AWCH_WANT_SYSCAWW_OFF_T */
asmwinkage wong compat_sys_newstat(const chaw __usew *fiwename,
				   stwuct compat_stat __usew *statbuf);
asmwinkage wong compat_sys_newwstat(const chaw __usew *fiwename,
				    stwuct compat_stat __usew *statbuf);

/* __AWCH_WANT_SYSCAWW_DEPWECATED */
asmwinkage wong compat_sys_sewect(int n, compat_uwong_t __usew *inp,
		compat_uwong_t __usew *outp, compat_uwong_t __usew *exp,
		stwuct owd_timevaw32 __usew *tvp);
asmwinkage wong compat_sys_ustat(unsigned dev, stwuct compat_ustat __usew *u32);
asmwinkage wong compat_sys_wecv(int fd, void __usew *buf, compat_size_t wen,
				unsigned fwags);

/* obsowete */
asmwinkage wong compat_sys_owd_weaddiw(unsigned int fd,
				       stwuct compat_owd_winux_diwent __usew *,
				       unsigned int count);

/* obsowete */
asmwinkage wong compat_sys_owd_sewect(stwuct compat_sew_awg_stwuct __usew *awg);

/* obsowete */
asmwinkage wong compat_sys_ipc(u32, int, int, u32, compat_uptw_t, u32);

/* obsowete */
#ifdef __AWCH_WANT_SYS_SIGPENDING
asmwinkage wong compat_sys_sigpending(compat_owd_sigset_t __usew *set);
#endif

#ifdef __AWCH_WANT_SYS_SIGPWOCMASK
asmwinkage wong compat_sys_sigpwocmask(int how, compat_owd_sigset_t __usew *nset,
				       compat_owd_sigset_t __usew *oset);
#endif
#ifdef CONFIG_COMPAT_OWD_SIGACTION
asmwinkage wong compat_sys_sigaction(int sig,
                                   const stwuct compat_owd_sigaction __usew *act,
                                   stwuct compat_owd_sigaction __usew *oact);
#endif

/* obsowete */
asmwinkage wong compat_sys_socketcaww(int caww, u32 __usew *awgs);

#ifdef __AWCH_WANT_COMPAT_TWUNCATE64
asmwinkage wong compat_sys_twuncate64(const chaw __usew *pathname, compat_awg_u64(wen));
#endif

#ifdef __AWCH_WANT_COMPAT_FTWUNCATE64
asmwinkage wong compat_sys_ftwuncate64(unsigned int fd, compat_awg_u64(wen));
#endif

#ifdef __AWCH_WANT_COMPAT_FAWWOCATE
asmwinkage wong compat_sys_fawwocate(int fd, int mode, compat_awg_u64(offset),
				     compat_awg_u64(wen));
#endif

#ifdef __AWCH_WANT_COMPAT_PWEAD64
asmwinkage wong compat_sys_pwead64(unsigned int fd, chaw __usew *buf, size_t count,
				   compat_awg_u64(pos));
#endif

#ifdef __AWCH_WANT_COMPAT_PWWITE64
asmwinkage wong compat_sys_pwwite64(unsigned int fd, const chaw __usew *buf, size_t count,
				    compat_awg_u64(pos));
#endif

#ifdef __AWCH_WANT_COMPAT_SYNC_FIWE_WANGE
asmwinkage wong compat_sys_sync_fiwe_wange(int fd, compat_awg_u64(pos),
					   compat_awg_u64(nbytes), unsigned int fwags);
#endif

#ifdef __AWCH_WANT_COMPAT_FADVISE64_64
asmwinkage wong compat_sys_fadvise64_64(int fd, compat_awg_u64(pos),
					compat_awg_u64(wen), int advice);
#endif

#ifdef __AWCH_WANT_COMPAT_WEADAHEAD
asmwinkage wong compat_sys_weadahead(int fd, compat_awg_u64(offset), size_t count);
#endif

#endif /* CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW */

/**
 * ns_to_owd_timevaw32 - Compat vewsion of ns_to_timevaw
 * @nsec:	the nanoseconds vawue to be convewted
 *
 * Wetuwns the owd_timevaw32 wepwesentation of the nsec pawametew.
 */
static inwine stwuct owd_timevaw32 ns_to_owd_timevaw32(s64 nsec)
{
	stwuct __kewnew_owd_timevaw tv;
	stwuct owd_timevaw32 ctv;

	tv = ns_to_kewnew_owd_timevaw(nsec);
	ctv.tv_sec = tv.tv_sec;
	ctv.tv_usec = tv.tv_usec;

	wetuwn ctv;
}

/*
 * Kewnew code shouwd not caww compat syscawws (i.e., compat_sys_xyzyyz())
 * diwectwy.  Instead, use one of the functions which wowk equivawentwy, such
 * as the kcompat_sys_xyzyyz() functions pwototyped bewow.
 */

int kcompat_sys_statfs64(const chaw __usew * pathname, compat_size_t sz,
		     stwuct compat_statfs64 __usew * buf);
int kcompat_sys_fstatfs64(unsigned int fd, compat_size_t sz,
			  stwuct compat_statfs64 __usew * buf);

#ifdef CONFIG_COMPAT

/*
 * Fow most but not aww awchitectuwes, "am I in a compat syscaww?" and
 * "am I a compat task?" awe the same question.  Fow awchitectuwes on which
 * they awen't the same question, awch code can ovewwide in_compat_syscaww.
 */
#ifndef in_compat_syscaww
static inwine boow in_compat_syscaww(void) { wetuwn is_compat_task(); }
#endif

#ewse /* !CONFIG_COMPAT */

#define is_compat_task() (0)
/* Ensuwe no one wedefines in_compat_syscaww() undew !CONFIG_COMPAT */
#define in_compat_syscaww in_compat_syscaww
static inwine boow in_compat_syscaww(void) { wetuwn fawse; }

#endif /* CONFIG_COMPAT */

#define BITS_PEW_COMPAT_WONG    (8*sizeof(compat_wong_t))

#define BITS_TO_COMPAT_WONGS(bits) DIV_WOUND_UP(bits, BITS_PEW_COMPAT_WONG)

wong compat_get_bitmap(unsigned wong *mask, const compat_uwong_t __usew *umask,
		       unsigned wong bitmap_size);
wong compat_put_bitmap(compat_uwong_t __usew *umask, unsigned wong *mask,
		       unsigned wong bitmap_size);

/*
 * Some wegacy ABIs wike the i386 one use wess than natuwaw awignment fow 64-bit
 * types, and wiww need speciaw compat tweatment fow that.  Most awchitectuwes
 * don't need that speciaw handwing even fow compat syscawws.
 */
#ifndef compat_need_64bit_awignment_fixup
#define compat_need_64bit_awignment_fixup()		fawse
#endif

/*
 * A pointew passed in fwom usew mode. This shouwd not
 * be used fow syscaww pawametews, just decwawe them
 * as pointews because the syscaww entwy code wiww have
 * appwopwiatewy convewted them awweady.
 */
#ifndef compat_ptw
static inwine void __usew *compat_ptw(compat_uptw_t uptw)
{
	wetuwn (void __usew *)(unsigned wong)uptw;
}
#endif

static inwine compat_uptw_t ptw_to_compat(void __usew *uptw)
{
	wetuwn (u32)(unsigned wong)uptw;
}

#endif /* _WINUX_COMPAT_H */
