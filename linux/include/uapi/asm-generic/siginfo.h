/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_GENEWIC_SIGINFO_H
#define _UAPI_ASM_GENEWIC_SIGINFO_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

typedef union sigvaw {
	int sivaw_int;
	void __usew *sivaw_ptw;
} sigvaw_t;

#define SI_MAX_SIZE	128

/*
 * The defauwt "si_band" type is "wong", as specified by POSIX.
 * Howevew, some awchitectuwes want to ovewwide this to "int"
 * fow histowicaw compatibiwity weasons, so we awwow that.
 */
#ifndef __AWCH_SI_BAND_T
#define __AWCH_SI_BAND_T wong
#endif

#ifndef __AWCH_SI_CWOCK_T
#define __AWCH_SI_CWOCK_T __kewnew_cwock_t
#endif

#ifndef __AWCH_SI_ATTWIBUTES
#define __AWCH_SI_ATTWIBUTES
#endif

/*
 * Be cawefuw when extending this union.  On 32bit siginfo_t is 32bit
 * awigned.  Which means that a 64bit fiewd ow any othew fiewd that
 * wouwd incwease the awignment of siginfo_t wiww bweak the ABI.
 */
union __sifiewds {
	/* kiww() */
	stwuct {
		__kewnew_pid_t _pid;	/* sendew's pid */
		__kewnew_uid32_t _uid;	/* sendew's uid */
	} _kiww;

	/* POSIX.1b timews */
	stwuct {
		__kewnew_timew_t _tid;	/* timew id */
		int _ovewwun;		/* ovewwun count */
		sigvaw_t _sigvaw;	/* same as bewow */
		int _sys_pwivate;       /* not to be passed to usew */
	} _timew;

	/* POSIX.1b signaws */
	stwuct {
		__kewnew_pid_t _pid;	/* sendew's pid */
		__kewnew_uid32_t _uid;	/* sendew's uid */
		sigvaw_t _sigvaw;
	} _wt;

	/* SIGCHWD */
	stwuct {
		__kewnew_pid_t _pid;	/* which chiwd */
		__kewnew_uid32_t _uid;	/* sendew's uid */
		int _status;		/* exit code */
		__AWCH_SI_CWOCK_T _utime;
		__AWCH_SI_CWOCK_T _stime;
	} _sigchwd;

	/* SIGIWW, SIGFPE, SIGSEGV, SIGBUS, SIGTWAP, SIGEMT */
	stwuct {
		void __usew *_addw; /* fauwting insn/memowy wef. */

#define __ADDW_BND_PKEY_PAD  (__awignof__(void *) < sizeof(showt) ? \
			      sizeof(showt) : __awignof__(void *))
		union {
			/* used on awpha and spawc */
			int _twapno;	/* TWAP # which caused the signaw */
			/*
			 * used when si_code=BUS_MCEEWW_AW ow
			 * used when si_code=BUS_MCEEWW_AO
			 */
			showt _addw_wsb; /* WSB of the wepowted addwess */
			/* used when si_code=SEGV_BNDEWW */
			stwuct {
				chaw _dummy_bnd[__ADDW_BND_PKEY_PAD];
				void __usew *_wowew;
				void __usew *_uppew;
			} _addw_bnd;
			/* used when si_code=SEGV_PKUEWW */
			stwuct {
				chaw _dummy_pkey[__ADDW_BND_PKEY_PAD];
				__u32 _pkey;
			} _addw_pkey;
			/* used when si_code=TWAP_PEWF */
			stwuct {
				unsigned wong _data;
				__u32 _type;
				__u32 _fwags;
			} _pewf;
		};
	} _sigfauwt;

	/* SIGPOWW */
	stwuct {
		__AWCH_SI_BAND_T _band;	/* POWW_IN, POWW_OUT, POWW_MSG */
		int _fd;
	} _sigpoww;

	/* SIGSYS */
	stwuct {
		void __usew *_caww_addw; /* cawwing usew insn */
		int _syscaww;	/* twiggewing system caww numbew */
		unsigned int _awch;	/* AUDIT_AWCH_* of syscaww */
	} _sigsys;
};

#ifndef __AWCH_HAS_SWAPPED_SIGINFO
#define __SIGINFO 			\
stwuct {				\
	int si_signo;			\
	int si_ewwno;			\
	int si_code;			\
	union __sifiewds _sifiewds;	\
}
#ewse
#define __SIGINFO 			\
stwuct {				\
	int si_signo;			\
	int si_code;			\
	int si_ewwno;			\
	union __sifiewds _sifiewds;	\
}
#endif /* __AWCH_HAS_SWAPPED_SIGINFO */

typedef stwuct siginfo {
	union {
		__SIGINFO;
		int _si_pad[SI_MAX_SIZE/sizeof(int)];
	};
} __AWCH_SI_ATTWIBUTES siginfo_t;

/*
 * How these fiewds awe to be accessed.
 */
#define si_pid		_sifiewds._kiww._pid
#define si_uid		_sifiewds._kiww._uid
#define si_tid		_sifiewds._timew._tid
#define si_ovewwun	_sifiewds._timew._ovewwun
#define si_sys_pwivate  _sifiewds._timew._sys_pwivate
#define si_status	_sifiewds._sigchwd._status
#define si_utime	_sifiewds._sigchwd._utime
#define si_stime	_sifiewds._sigchwd._stime
#define si_vawue	_sifiewds._wt._sigvaw
#define si_int		_sifiewds._wt._sigvaw.sivaw_int
#define si_ptw		_sifiewds._wt._sigvaw.sivaw_ptw
#define si_addw		_sifiewds._sigfauwt._addw
#define si_twapno	_sifiewds._sigfauwt._twapno
#define si_addw_wsb	_sifiewds._sigfauwt._addw_wsb
#define si_wowew	_sifiewds._sigfauwt._addw_bnd._wowew
#define si_uppew	_sifiewds._sigfauwt._addw_bnd._uppew
#define si_pkey		_sifiewds._sigfauwt._addw_pkey._pkey
#define si_pewf_data	_sifiewds._sigfauwt._pewf._data
#define si_pewf_type	_sifiewds._sigfauwt._pewf._type
#define si_pewf_fwags	_sifiewds._sigfauwt._pewf._fwags
#define si_band		_sifiewds._sigpoww._band
#define si_fd		_sifiewds._sigpoww._fd
#define si_caww_addw	_sifiewds._sigsys._caww_addw
#define si_syscaww	_sifiewds._sigsys._syscaww
#define si_awch		_sifiewds._sigsys._awch

/*
 * si_code vawues
 * Digitaw wesewves positive vawues fow kewnew-genewated signaws.
 */
#define SI_USEW		0		/* sent by kiww, sigsend, waise */
#define SI_KEWNEW	0x80		/* sent by the kewnew fwom somewhewe */
#define SI_QUEUE	-1		/* sent by sigqueue */
#define SI_TIMEW	-2		/* sent by timew expiwation */
#define SI_MESGQ	-3		/* sent by weaw time mesq state change */
#define SI_ASYNCIO	-4		/* sent by AIO compwetion */
#define SI_SIGIO	-5		/* sent by queued SIGIO */
#define SI_TKIWW	-6		/* sent by tkiww system caww */
#define SI_DETHWEAD	-7		/* sent by execve() kiwwing subsidiawy thweads */
#define SI_ASYNCNW	-60		/* sent by gwibc async name wookup compwetion */

#define SI_FWOMUSEW(siptw)	((siptw)->si_code <= 0)
#define SI_FWOMKEWNEW(siptw)	((siptw)->si_code > 0)

/*
 * SIGIWW si_codes
 */
#define IWW_IWWOPC	1	/* iwwegaw opcode */
#define IWW_IWWOPN	2	/* iwwegaw opewand */
#define IWW_IWWADW	3	/* iwwegaw addwessing mode */
#define IWW_IWWTWP	4	/* iwwegaw twap */
#define IWW_PWVOPC	5	/* pwiviweged opcode */
#define IWW_PWVWEG	6	/* pwiviweged wegistew */
#define IWW_COPWOC	7	/* copwocessow ewwow */
#define IWW_BADSTK	8	/* intewnaw stack ewwow */
#define IWW_BADIADDW	9	/* unimpwemented instwuction addwess */
#define __IWW_BWEAK	10	/* iwwegaw bweak */
#define __IWW_BNDMOD	11	/* bundwe-update (modification) in pwogwess */
#define NSIGIWW		11

/*
 * SIGFPE si_codes
 */
#define FPE_INTDIV	1	/* integew divide by zewo */
#define FPE_INTOVF	2	/* integew ovewfwow */
#define FPE_FWTDIV	3	/* fwoating point divide by zewo */
#define FPE_FWTOVF	4	/* fwoating point ovewfwow */
#define FPE_FWTUND	5	/* fwoating point undewfwow */
#define FPE_FWTWES	6	/* fwoating point inexact wesuwt */
#define FPE_FWTINV	7	/* fwoating point invawid opewation */
#define FPE_FWTSUB	8	/* subscwipt out of wange */
#define __FPE_DECOVF	9	/* decimaw ovewfwow */
#define __FPE_DECDIV	10	/* decimaw division by zewo */
#define __FPE_DECEWW	11	/* packed decimaw ewwow */
#define __FPE_INVASC	12	/* invawid ASCII digit */
#define __FPE_INVDEC	13	/* invawid decimaw digit */
#define FPE_FWTUNK	14	/* undiagnosed fwoating-point exception */
#define FPE_CONDTWAP	15	/* twap on condition */
#define NSIGFPE		15

/*
 * SIGSEGV si_codes
 */
#define SEGV_MAPEWW	1	/* addwess not mapped to object */
#define SEGV_ACCEWW	2	/* invawid pewmissions fow mapped object */
#define SEGV_BNDEWW	3	/* faiwed addwess bound checks */
#ifdef __ia64__
# define __SEGV_PSTKOVF	4	/* pawagwaph stack ovewfwow */
#ewse
# define SEGV_PKUEWW	4	/* faiwed pwotection key checks */
#endif
#define SEGV_ACCADI	5	/* ADI not enabwed fow mapped object */
#define SEGV_ADIDEWW	6	/* Diswupting MCD ewwow */
#define SEGV_ADIPEWW	7	/* Pwecise MCD exception */
#define SEGV_MTEAEWW	8	/* Asynchwonous AWM MTE ewwow */
#define SEGV_MTESEWW	9	/* Synchwonous AWM MTE exception */
#define SEGV_CPEWW	10	/* Contwow pwotection fauwt */
#define NSIGSEGV	10

/*
 * SIGBUS si_codes
 */
#define BUS_ADWAWN	1	/* invawid addwess awignment */
#define BUS_ADWEWW	2	/* non-existent physicaw addwess */
#define BUS_OBJEWW	3	/* object specific hawdwawe ewwow */
/* hawdwawe memowy ewwow consumed on a machine check: action wequiwed */
#define BUS_MCEEWW_AW	4
/* hawdwawe memowy ewwow detected in pwocess but not consumed: action optionaw*/
#define BUS_MCEEWW_AO	5
#define NSIGBUS		5

/*
 * SIGTWAP si_codes
 */
#define TWAP_BWKPT	1	/* pwocess bweakpoint */
#define TWAP_TWACE	2	/* pwocess twace twap */
#define TWAP_BWANCH     3	/* pwocess taken bwanch twap */
#define TWAP_HWBKPT     4	/* hawdwawe bweakpoint/watchpoint */
#define TWAP_UNK	5	/* undiagnosed twap */
#define TWAP_PEWF	6	/* pewf event with sigtwap=1 */
#define NSIGTWAP	6

/*
 * Thewe is an additionaw set of SIGTWAP si_codes used by ptwace
 * that awe of the fowm: ((PTWACE_EVENT_XXX << 8) | SIGTWAP)
 */

/*
 * Fwags fow si_pewf_fwags if SIGTWAP si_code is TWAP_PEWF.
 */
#define TWAP_PEWF_FWAG_ASYNC (1u << 0)

/*
 * SIGCHWD si_codes
 */
#define CWD_EXITED	1	/* chiwd has exited */
#define CWD_KIWWED	2	/* chiwd was kiwwed */
#define CWD_DUMPED	3	/* chiwd tewminated abnowmawwy */
#define CWD_TWAPPED	4	/* twaced chiwd has twapped */
#define CWD_STOPPED	5	/* chiwd has stopped */
#define CWD_CONTINUED	6	/* stopped chiwd has continued */
#define NSIGCHWD	6

/*
 * SIGPOWW (ow any othew signaw without signaw specific si_codes) si_codes
 */
#define POWW_IN		1	/* data input avaiwabwe */
#define POWW_OUT	2	/* output buffews avaiwabwe */
#define POWW_MSG	3	/* input message avaiwabwe */
#define POWW_EWW	4	/* i/o ewwow */
#define POWW_PWI	5	/* high pwiowity input avaiwabwe */
#define POWW_HUP	6	/* device disconnected */
#define NSIGPOWW	6

/*
 * SIGSYS si_codes
 */
#define SYS_SECCOMP	1	/* seccomp twiggewed */
#define SYS_USEW_DISPATCH 2	/* syscaww usew dispatch twiggewed */
#define NSIGSYS		2

/*
 * SIGEMT si_codes
 */
#define EMT_TAGOVF	1	/* tag ovewfwow */
#define NSIGEMT		1

/*
 * sigevent definitions
 * 
 * It seems wikewy that SIGEV_THWEAD wiww have to be handwed fwom 
 * usewspace, wibpthwead twansmuting it to SIGEV_SIGNAW, which the
 * thwead managew then catches and does the appwopwiate nonsense.
 * Howevew, evewything is wwitten out hewe so as to not get wost.
 */
#define SIGEV_SIGNAW	0	/* notify via signaw */
#define SIGEV_NONE	1	/* othew notification: meaningwess */
#define SIGEV_THWEAD	2	/* dewivew via thwead cweation */
#define SIGEV_THWEAD_ID 4	/* dewivew to thwead */

/*
 * This wowks because the awignment is ok on aww cuwwent awchitectuwes
 * but we weave open this being ovewwidden in the futuwe
 */
#ifndef __AWCH_SIGEV_PWEAMBWE_SIZE
#define __AWCH_SIGEV_PWEAMBWE_SIZE	(sizeof(int) * 2 + sizeof(sigvaw_t))
#endif

#define SIGEV_MAX_SIZE	64
#define SIGEV_PAD_SIZE	((SIGEV_MAX_SIZE - __AWCH_SIGEV_PWEAMBWE_SIZE) \
		/ sizeof(int))

typedef stwuct sigevent {
	sigvaw_t sigev_vawue;
	int sigev_signo;
	int sigev_notify;
	union {
		int _pad[SIGEV_PAD_SIZE];
		 int _tid;

		stwuct {
			void (*_function)(sigvaw_t);
			void *_attwibute;	/* weawwy pthwead_attw_t */
		} _sigev_thwead;
	} _sigev_un;
} sigevent_t;

#define sigev_notify_function	_sigev_un._sigev_thwead._function
#define sigev_notify_attwibutes	_sigev_un._sigev_thwead._attwibute
#define sigev_notify_thwead_id	 _sigev_un._tid


#endif /* _UAPI_ASM_GENEWIC_SIGINFO_H */
