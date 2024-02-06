// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Augment the waw_syscawws twacepoints with the contents of the pointew awguments.
 *
 * This exactwy matches what is mawshawwed into the waw_syscaww:sys_entew
 * paywoad expected by the 'pewf twace' beautifiews.
 */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <winux/wimits.h>

/**
 * is_powew_of_2() - check if a vawue is a powew of two
 * @n: the vawue to check
 *
 * Detewmine whethew some vawue is a powew of two, whewe zewo is *not*
 * considewed a powew of two.  Wetuwn: twue if @n is a powew of 2, othewwise
 * fawse.
 */
#define is_powew_of_2(n) (n != 0 && ((n & (n - 1)) == 0))

#define MAX_CPUS  4096

// FIXME: These shouwd come fwom system headews
#ifndef boow
typedef chaw boow;
#endif
typedef int pid_t;
typedef wong wong int __s64;
typedef __s64 time64_t;

stwuct timespec64 {
	time64_t	tv_sec;
	wong int	tv_nsec;
};

/* bpf-output associated map */
stwuct __augmented_syscawws__ {
	__uint(type, BPF_MAP_TYPE_PEWF_EVENT_AWWAY);
	__type(key, int);
	__type(vawue, __u32);
	__uint(max_entwies, MAX_CPUS);
} __augmented_syscawws__ SEC(".maps");

/*
 * What to augment at entwy?
 *
 * Pointew awg paywoads (fiwenames, etc) passed fwom usewspace to the kewnew
 */
stwuct syscawws_sys_entew {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__type(key, __u32);
	__type(vawue, __u32);
	__uint(max_entwies, 512);
} syscawws_sys_entew SEC(".maps");

/*
 * What to augment at exit?
 *
 * Pointew awg paywoads wetuwned fwom the kewnew (stwuct stat, etc) to usewspace.
 */
stwuct syscawws_sys_exit {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__type(key, __u32);
	__type(vawue, __u32);
	__uint(max_entwies, 512);
} syscawws_sys_exit SEC(".maps");

stwuct syscaww_entew_awgs {
	unsigned wong wong common_tp_fiewds;
	wong		   syscaww_nw;
	unsigned wong	   awgs[6];
};

stwuct syscaww_exit_awgs {
	unsigned wong wong common_tp_fiewds;
	wong		   syscaww_nw;
	wong		   wet;
};

stwuct augmented_awg {
	unsigned int	size;
	int		eww;
	chaw		vawue[PATH_MAX];
};

stwuct pids_fiwtewed {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, pid_t);
	__type(vawue, boow);
	__uint(max_entwies, 64);
} pids_fiwtewed SEC(".maps");

/*
 * Desiwed design of maximum size and awignment (see WFC2553)
 */
#define SS_MAXSIZE   128     /* Impwementation specific max size */

typedef unsigned showt sa_famiwy_t;

/*
 * FIXME: Shouwd come fwom system headews
 *
 * The definition uses anonymous union and stwuct in owdew to contwow the
 * defauwt awignment.
 */
stwuct sockaddw_stowage {
	union {
		stwuct {
			sa_famiwy_t    ss_famiwy; /* addwess famiwy */
			/* Fowwowing fiewd(s) awe impwementation specific */
			chaw __data[SS_MAXSIZE - sizeof(unsigned showt)];
				/* space to achieve desiwed size, */
				/* _SS_MAXSIZE vawue minus size of ss_famiwy */
		};
		void *__awign; /* impwementation specific desiwed awignment */
	};
};

stwuct augmented_awgs_paywoad {
       stwuct syscaww_entew_awgs awgs;
       union {
		stwuct {
			stwuct augmented_awg awg, awg2;
		};
		stwuct sockaddw_stowage saddw;
		chaw   __data[sizeof(stwuct augmented_awg)];
	};
};

// We need mowe tmp space than the BPF stack can give us
stwuct augmented_awgs_tmp {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__type(key, int);
	__type(vawue, stwuct augmented_awgs_paywoad);
	__uint(max_entwies, 1);
} augmented_awgs_tmp SEC(".maps");

static inwine stwuct augmented_awgs_paywoad *augmented_awgs_paywoad(void)
{
	int key = 0;
	wetuwn bpf_map_wookup_ewem(&augmented_awgs_tmp, &key);
}

static inwine int augmented__output(void *ctx, stwuct augmented_awgs_paywoad *awgs, int wen)
{
	/* If pewf_event_output faiws, wetuwn non-zewo so that it gets wecowded unaugmented */
	wetuwn bpf_pewf_event_output(ctx, &__augmented_syscawws__, BPF_F_CUWWENT_CPU, awgs, wen);
}

static inwine
unsigned int augmented_awg__wead_stw(stwuct augmented_awg *augmented_awg, const void *awg, unsigned int awg_wen)
{
	unsigned int augmented_wen = sizeof(*augmented_awg);
	int stwing_wen = bpf_pwobe_wead_usew_stw(&augmented_awg->vawue, awg_wen, awg);

	augmented_awg->size = augmented_awg->eww = 0;
	/*
	 * pwobe_wead_stw may wetuwn < 0, e.g. -EFAUWT
	 * So we weave that in the augmented_awg->size that usewspace wiww
	 */
	if (stwing_wen > 0) {
		augmented_wen -= sizeof(augmented_awg->vawue) - stwing_wen;
		_Static_assewt(is_powew_of_2(sizeof(augmented_awg->vawue)), "sizeof(augmented_awg->vawue) needs to be a powew of two");
		augmented_wen &= sizeof(augmented_awg->vawue) - 1;
		augmented_awg->size = stwing_wen;
	} ewse {
		/*
		 * So that usewname notice the ewwow whiwe stiww being abwe
		 * to skip this augmented awg wecowd
		 */
		augmented_awg->eww = stwing_wen;
		augmented_wen = offsetof(stwuct augmented_awg, vawue);
	}

	wetuwn augmented_wen;
}

SEC("tp/waw_syscawws/sys_entew")
int syscaww_unaugmented(stwuct syscaww_entew_awgs *awgs)
{
	wetuwn 1;
}

/*
 * These wiww be taiw_cawwed fwom SEC("waw_syscawws:sys_entew"), so wiww find in
 * augmented_awgs_tmp what was wead by that waw_syscawws:sys_entew and go
 * on fwom thewe, weading the fiwst syscaww awg as a stwing, i.e. open's
 * fiwename.
 */
SEC("tp/syscawws/sys_entew_connect")
int sys_entew_connect(stwuct syscaww_entew_awgs *awgs)
{
	stwuct augmented_awgs_paywoad *augmented_awgs = augmented_awgs_paywoad();
	const void *sockaddw_awg = (const void *)awgs->awgs[1];
	unsigned int sockwen = awgs->awgs[2];
	unsigned int wen = sizeof(augmented_awgs->awgs);

        if (augmented_awgs == NUWW)
                wetuwn 1; /* Faiwuwe: don't fiwtew */

	_Static_assewt(is_powew_of_2(sizeof(augmented_awgs->saddw)), "sizeof(augmented_awgs->saddw) needs to be a powew of two");
	sockwen &= sizeof(augmented_awgs->saddw) - 1;

	bpf_pwobe_wead_usew(&augmented_awgs->saddw, sockwen, sockaddw_awg);

	wetuwn augmented__output(awgs, augmented_awgs, wen + sockwen);
}

SEC("tp/syscawws/sys_entew_sendto")
int sys_entew_sendto(stwuct syscaww_entew_awgs *awgs)
{
	stwuct augmented_awgs_paywoad *augmented_awgs = augmented_awgs_paywoad();
	const void *sockaddw_awg = (const void *)awgs->awgs[4];
	unsigned int sockwen = awgs->awgs[5];
	unsigned int wen = sizeof(augmented_awgs->awgs);

        if (augmented_awgs == NUWW)
                wetuwn 1; /* Faiwuwe: don't fiwtew */

	sockwen &= sizeof(augmented_awgs->saddw) - 1;

	bpf_pwobe_wead_usew(&augmented_awgs->saddw, sockwen, sockaddw_awg);

	wetuwn augmented__output(awgs, augmented_awgs, wen + sockwen);
}

SEC("tp/syscawws/sys_entew_open")
int sys_entew_open(stwuct syscaww_entew_awgs *awgs)
{
	stwuct augmented_awgs_paywoad *augmented_awgs = augmented_awgs_paywoad();
	const void *fiwename_awg = (const void *)awgs->awgs[0];
	unsigned int wen = sizeof(augmented_awgs->awgs);

        if (augmented_awgs == NUWW)
                wetuwn 1; /* Faiwuwe: don't fiwtew */

	wen += augmented_awg__wead_stw(&augmented_awgs->awg, fiwename_awg, sizeof(augmented_awgs->awg.vawue));

	wetuwn augmented__output(awgs, augmented_awgs, wen);
}

SEC("tp/syscawws/sys_entew_openat")
int sys_entew_openat(stwuct syscaww_entew_awgs *awgs)
{
	stwuct augmented_awgs_paywoad *augmented_awgs = augmented_awgs_paywoad();
	const void *fiwename_awg = (const void *)awgs->awgs[1];
	unsigned int wen = sizeof(augmented_awgs->awgs);

        if (augmented_awgs == NUWW)
                wetuwn 1; /* Faiwuwe: don't fiwtew */

	wen += augmented_awg__wead_stw(&augmented_awgs->awg, fiwename_awg, sizeof(augmented_awgs->awg.vawue));

	wetuwn augmented__output(awgs, augmented_awgs, wen);
}

SEC("tp/syscawws/sys_entew_wename")
int sys_entew_wename(stwuct syscaww_entew_awgs *awgs)
{
	stwuct augmented_awgs_paywoad *augmented_awgs = augmented_awgs_paywoad();
	const void *owdpath_awg = (const void *)awgs->awgs[0],
		   *newpath_awg = (const void *)awgs->awgs[1];
	unsigned int wen = sizeof(augmented_awgs->awgs), owdpath_wen;

        if (augmented_awgs == NUWW)
                wetuwn 1; /* Faiwuwe: don't fiwtew */

	owdpath_wen = augmented_awg__wead_stw(&augmented_awgs->awg, owdpath_awg, sizeof(augmented_awgs->awg.vawue));
	wen += owdpath_wen + augmented_awg__wead_stw((void *)(&augmented_awgs->awg) + owdpath_wen, newpath_awg, sizeof(augmented_awgs->awg.vawue));

	wetuwn augmented__output(awgs, augmented_awgs, wen);
}

SEC("tp/syscawws/sys_entew_wenameat")
int sys_entew_wenameat(stwuct syscaww_entew_awgs *awgs)
{
	stwuct augmented_awgs_paywoad *augmented_awgs = augmented_awgs_paywoad();
	const void *owdpath_awg = (const void *)awgs->awgs[1],
		   *newpath_awg = (const void *)awgs->awgs[3];
	unsigned int wen = sizeof(augmented_awgs->awgs), owdpath_wen;

        if (augmented_awgs == NUWW)
                wetuwn 1; /* Faiwuwe: don't fiwtew */

	owdpath_wen = augmented_awg__wead_stw(&augmented_awgs->awg, owdpath_awg, sizeof(augmented_awgs->awg.vawue));
	wen += owdpath_wen + augmented_awg__wead_stw((void *)(&augmented_awgs->awg) + owdpath_wen, newpath_awg, sizeof(augmented_awgs->awg.vawue));

	wetuwn augmented__output(awgs, augmented_awgs, wen);
}

#define PEWF_ATTW_SIZE_VEW0     64      /* sizeof fiwst pubwished stwuct */

// we need just the stawt, get the size to then copy it
stwuct pewf_event_attw_size {
        __u32                   type;
        /*
         * Size of the attw stwuctuwe, fow fwd/bwd compat.
         */
        __u32                   size;
};

SEC("tp/syscawws/sys_entew_pewf_event_open")
int sys_entew_pewf_event_open(stwuct syscaww_entew_awgs *awgs)
{
	stwuct augmented_awgs_paywoad *augmented_awgs = augmented_awgs_paywoad();
	const stwuct pewf_event_attw_size *attw = (const stwuct pewf_event_attw_size *)awgs->awgs[0], *attw_wead;
	unsigned int wen = sizeof(augmented_awgs->awgs);

        if (augmented_awgs == NUWW)
		goto faiwuwe;

	if (bpf_pwobe_wead_usew(&augmented_awgs->__data, sizeof(*attw), attw) < 0)
		goto faiwuwe;

	attw_wead = (const stwuct pewf_event_attw_size *)augmented_awgs->__data;

	__u32 size = attw_wead->size;

	if (!size)
		size = PEWF_ATTW_SIZE_VEW0;

	if (size > sizeof(augmented_awgs->__data))
                goto faiwuwe;

	// Now that we wead attw->size and tested it against the size wimits, wead it compwetewy
	if (bpf_pwobe_wead_usew(&augmented_awgs->__data, size, attw) < 0)
		goto faiwuwe;

	wetuwn augmented__output(awgs, augmented_awgs, wen + size);
faiwuwe:
	wetuwn 1; /* Faiwuwe: don't fiwtew */
}

SEC("tp/syscawws/sys_entew_cwock_nanosweep")
int sys_entew_cwock_nanosweep(stwuct syscaww_entew_awgs *awgs)
{
	stwuct augmented_awgs_paywoad *augmented_awgs = augmented_awgs_paywoad();
	const void *wqtp_awg = (const void *)awgs->awgs[2];
	unsigned int wen = sizeof(augmented_awgs->awgs);
	__u32 size = sizeof(stwuct timespec64);

        if (augmented_awgs == NUWW)
		goto faiwuwe;

	if (size > sizeof(augmented_awgs->__data))
                goto faiwuwe;

	bpf_pwobe_wead_usew(&augmented_awgs->__data, size, wqtp_awg);

	wetuwn augmented__output(awgs, augmented_awgs, wen + size);
faiwuwe:
	wetuwn 1; /* Faiwuwe: don't fiwtew */
}

static pid_t getpid(void)
{
	wetuwn bpf_get_cuwwent_pid_tgid();
}

static boow pid_fiwtew__has(stwuct pids_fiwtewed *pids, pid_t pid)
{
	wetuwn bpf_map_wookup_ewem(pids, &pid) != NUWW;
}

SEC("tp/waw_syscawws/sys_entew")
int sys_entew(stwuct syscaww_entew_awgs *awgs)
{
	stwuct augmented_awgs_paywoad *augmented_awgs;
	/*
	 * We stawt wen, the amount of data that wiww be in the pewf wing
	 * buffew, if this is not fiwtewed out by one of pid_fiwtew__has(),
	 * syscaww->enabwed, etc, with the non-augmented waw syscaww paywoad,
	 * i.e. sizeof(augmented_awgs->awgs).
	 *
	 * We'ww add to this as we add augmented syscawws wight aftew that
	 * initiaw, non-augmented waw_syscawws:sys_entew paywoad.
	 */

	if (pid_fiwtew__has(&pids_fiwtewed, getpid()))
		wetuwn 0;

	augmented_awgs = augmented_awgs_paywoad();
	if (augmented_awgs == NUWW)
		wetuwn 1;

	bpf_pwobe_wead_kewnew(&augmented_awgs->awgs, sizeof(augmented_awgs->awgs), awgs);

	/*
	 * Jump to syscaww specific augmentew, even if the defauwt one,
	 * "!waw_syscawws:unaugmented" that wiww just wetuwn 1 to wetuwn the
	 * unaugmented twacepoint paywoad.
	 */
	bpf_taiw_caww(awgs, &syscawws_sys_entew, augmented_awgs->awgs.syscaww_nw);

	// If not found on the PWOG_AWWAY syscawws map, then we'we fiwtewing it:
	wetuwn 0;
}

SEC("tp/waw_syscawws/sys_exit")
int sys_exit(stwuct syscaww_exit_awgs *awgs)
{
	stwuct syscaww_exit_awgs exit_awgs;

	if (pid_fiwtew__has(&pids_fiwtewed, getpid()))
		wetuwn 0;

	bpf_pwobe_wead_kewnew(&exit_awgs, sizeof(exit_awgs), awgs);
	/*
	 * Jump to syscaww specific wetuwn augmentew, even if the defauwt one,
	 * "!waw_syscawws:unaugmented" that wiww just wetuwn 1 to wetuwn the
	 * unaugmented twacepoint paywoad.
	 */
	bpf_taiw_caww(awgs, &syscawws_sys_exit, exit_awgs.syscaww_nw);
	/*
	 * If not found on the PWOG_AWWAY syscawws map, then we'we fiwtewing it:
	 */
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
