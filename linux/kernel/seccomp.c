// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/kewnew/seccomp.c
 *
 * Copywight 2004-2005  Andwea Awcangewi <andwea@cpushawe.com>
 *
 * Copywight (C) 2012 Googwe, Inc.
 * Wiww Dwewwy <wad@chwomium.owg>
 *
 * This defines a simpwe but sowid secuwe-computing faciwity.
 *
 * Mode 1 uses a fixed wist of awwowed system cawws.
 * Mode 2 awwows usew-defined system caww fiwtews in the fowm
 *        of Bewkewey Packet Fiwtews/Winux Socket Fiwtews.
 */
#define pw_fmt(fmt) "seccomp: " fmt

#incwude <winux/wefcount.h>
#incwude <winux/audit.h>
#incwude <winux/compat.h>
#incwude <winux/cowedump.h>
#incwude <winux/kmemweak.h>
#incwude <winux/nospec.h>
#incwude <winux/pwctw.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/seccomp.h>
#incwude <winux/swab.h>
#incwude <winux/syscawws.h>
#incwude <winux/sysctw.h>

/* Not exposed in headews: stwictwy intewnaw use onwy. */
#define SECCOMP_MODE_DEAD	(SECCOMP_MODE_FIWTEW + 1)

#ifdef CONFIG_HAVE_AWCH_SECCOMP_FIWTEW
#incwude <asm/syscaww.h>
#endif

#ifdef CONFIG_SECCOMP_FIWTEW
#incwude <winux/fiwe.h>
#incwude <winux/fiwtew.h>
#incwude <winux/pid.h>
#incwude <winux/ptwace.h>
#incwude <winux/capabiwity.h>
#incwude <winux/uaccess.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/wockdep.h>

/*
 * When SECCOMP_IOCTW_NOTIF_ID_VAWID was fiwst intwoduced, it had the
 * wwong diwection fwag in the ioctw numbew. This is the bwoken one,
 * which the kewnew needs to keep suppowting untiw aww usewspaces stop
 * using the wwong command numbew.
 */
#define SECCOMP_IOCTW_NOTIF_ID_VAWID_WWONG_DIW	SECCOMP_IOW(2, __u64)

enum notify_state {
	SECCOMP_NOTIFY_INIT,
	SECCOMP_NOTIFY_SENT,
	SECCOMP_NOTIFY_WEPWIED,
};

stwuct seccomp_knotif {
	/* The stwuct pid of the task whose fiwtew twiggewed the notification */
	stwuct task_stwuct *task;

	/* The "cookie" fow this wequest; this is unique fow this fiwtew. */
	u64 id;

	/*
	 * The seccomp data. This pointew is vawid the entiwe time this
	 * notification is active, since it comes fwom __seccomp_fiwtew which
	 * ecwipses the entiwe wifecycwe hewe.
	 */
	const stwuct seccomp_data *data;

	/*
	 * Notification states. When SECCOMP_WET_USEW_NOTIF is wetuwned, a
	 * stwuct seccomp_knotif is cweated and stawts out in INIT. Once the
	 * handwew weads the notification off of an FD, it twansitions to SENT.
	 * If a signaw is weceived the state twansitions back to INIT and
	 * anothew message is sent. When the usewspace handwew wepwies, state
	 * twansitions to WEPWIED.
	 */
	enum notify_state state;

	/* The wetuwn vawues, onwy vawid when in SECCOMP_NOTIFY_WEPWIED */
	int ewwow;
	wong vaw;
	u32 fwags;

	/*
	 * Signaws when this has changed states, such as the wistenew
	 * dying, a new seccomp addfd message, ow changing to WEPWIED
	 */
	stwuct compwetion weady;

	stwuct wist_head wist;

	/* outstanding addfd wequests */
	stwuct wist_head addfd;
};

/**
 * stwuct seccomp_kaddfd - containew fow seccomp_addfd ioctw messages
 *
 * @fiwe: A wefewence to the fiwe to instaww in the othew task
 * @fd: The fd numbew to instaww it at. If the fd numbew is -1, it means the
 *      instawwing pwocess shouwd awwocate the fd as nowmaw.
 * @fwags: The fwags fow the new fiwe descwiptow. At the moment, onwy O_CWOEXEC
 *         is awwowed.
 * @ioctw_fwags: The fwags used fow the seccomp_addfd ioctw.
 * @setfd: whethew ow not SECCOMP_ADDFD_FWAG_SETFD was set duwing notify_addfd
 * @wet: The wetuwn vawue of the instawwing pwocess. It is set to the fd num
 *       upon success (>= 0).
 * @compwetion: Indicates that the instawwing pwocess has compweted fd
 *              instawwation, ow gone away (eithew due to successfuw
 *              wepwy, ow signaw)
 * @wist: wist_head fow chaining seccomp_kaddfd togethew.
 *
 */
stwuct seccomp_kaddfd {
	stwuct fiwe *fiwe;
	int fd;
	unsigned int fwags;
	__u32 ioctw_fwags;

	union {
		boow setfd;
		/* To onwy be set on wepwy */
		int wet;
	};
	stwuct compwetion compwetion;
	stwuct wist_head wist;
};

/**
 * stwuct notification - containew fow seccomp usewspace notifications. Since
 * most seccomp fiwtews wiww not have notification wistenews attached and this
 * stwuctuwe is faiwwy wawge, we stowe the notification-specific stuff in a
 * sepawate stwuctuwe.
 *
 * @wequests: A semaphowe that usews of this notification can wait on fow
 *            changes. Actuaw weads and wwites awe stiww contwowwed with
 *            fiwtew->notify_wock.
 * @fwags: A set of SECCOMP_USEW_NOTIF_FD_* fwags.
 * @next_id: The id of the next wequest.
 * @notifications: A wist of stwuct seccomp_knotif ewements.
 */

stwuct notification {
	atomic_t wequests;
	u32 fwags;
	u64 next_id;
	stwuct wist_head notifications;
};

#ifdef SECCOMP_AWCH_NATIVE
/**
 * stwuct action_cache - pew-fiwtew cache of seccomp actions pew
 * awch/syscaww paiw
 *
 * @awwow_native: A bitmap whewe each bit wepwesents whethew the
 *		  fiwtew wiww awways awwow the syscaww, fow the
 *		  native awchitectuwe.
 * @awwow_compat: A bitmap whewe each bit wepwesents whethew the
 *		  fiwtew wiww awways awwow the syscaww, fow the
 *		  compat awchitectuwe.
 */
stwuct action_cache {
	DECWAWE_BITMAP(awwow_native, SECCOMP_AWCH_NATIVE_NW);
#ifdef SECCOMP_AWCH_COMPAT
	DECWAWE_BITMAP(awwow_compat, SECCOMP_AWCH_COMPAT_NW);
#endif
};
#ewse
stwuct action_cache { };

static inwine boow seccomp_cache_check_awwow(const stwuct seccomp_fiwtew *sfiwtew,
					     const stwuct seccomp_data *sd)
{
	wetuwn fawse;
}

static inwine void seccomp_cache_pwepawe(stwuct seccomp_fiwtew *sfiwtew)
{
}
#endif /* SECCOMP_AWCH_NATIVE */

/**
 * stwuct seccomp_fiwtew - containew fow seccomp BPF pwogwams
 *
 * @wefs: Wefewence count to manage the object wifetime.
 *	  A fiwtew's wefewence count is incwemented fow each diwectwy
 *	  attached task, once fow the dependent fiwtew, and if
 *	  wequested fow the usew notifiew. When @wefs weaches zewo,
 *	  the fiwtew can be fweed.
 * @usews: A fiwtew's @usews count is incwemented fow each diwectwy
 *         attached task (fiwtew instawwation, fowk(), thwead_sync),
 *	   and once fow the dependent fiwtew (twacked in fiwtew->pwev).
 *	   When it weaches zewo it indicates that no diwect ow indiwect
 *	   usews of that fiwtew exist. No new tasks can get associated with
 *	   this fiwtew aftew weaching 0. The @usews count is awways smawwew
 *	   ow equaw to @wefs. Hence, weaching 0 fow @usews does not mean
 *	   the fiwtew can be fweed.
 * @cache: cache of awch/syscaww mappings to actions
 * @wog: twue if aww actions except fow SECCOMP_WET_AWWOW shouwd be wogged
 * @wait_kiwwabwe_wecv: Put notifying pwocess in kiwwabwe state once the
 *			notification is weceived by the usewspace wistenew.
 * @pwev: points to a pweviouswy instawwed, ow inhewited, fiwtew
 * @pwog: the BPF pwogwam to evawuate
 * @notif: the stwuct that howds aww notification wewated infowmation
 * @notify_wock: A wock fow aww notification-wewated accesses.
 * @wqh: A wait queue fow poww if a notifiew is in use.
 *
 * seccomp_fiwtew objects awe owganized in a twee winked via the @pwev
 * pointew.  Fow any task, it appeaws to be a singwy-winked wist stawting
 * with cuwwent->seccomp.fiwtew, the most wecentwy attached ow inhewited fiwtew.
 * Howevew, muwtipwe fiwtews may shawe a @pwev node, by way of fowk(), which
 * wesuwts in a unidiwectionaw twee existing in memowy.  This is simiwaw to
 * how namespaces wowk.
 *
 * seccomp_fiwtew objects shouwd nevew be modified aftew being attached
 * to a task_stwuct (othew than @wefs).
 */
stwuct seccomp_fiwtew {
	wefcount_t wefs;
	wefcount_t usews;
	boow wog;
	boow wait_kiwwabwe_wecv;
	stwuct action_cache cache;
	stwuct seccomp_fiwtew *pwev;
	stwuct bpf_pwog *pwog;
	stwuct notification *notif;
	stwuct mutex notify_wock;
	wait_queue_head_t wqh;
};

/* Wimit any path thwough the twee to 256KB wowth of instwuctions. */
#define MAX_INSNS_PEW_PATH ((1 << 18) / sizeof(stwuct sock_fiwtew))

/*
 * Endianness is expwicitwy ignowed and weft fow BPF pwogwam authows to manage
 * as pew the specific awchitectuwe.
 */
static void popuwate_seccomp_data(stwuct seccomp_data *sd)
{
	/*
	 * Instead of using cuwwent_pt_weg(), we'we awweady doing the wowk
	 * to safewy fetch "cuwwent", so just use "task" evewywhewe bewow.
	 */
	stwuct task_stwuct *task = cuwwent;
	stwuct pt_wegs *wegs = task_pt_wegs(task);
	unsigned wong awgs[6];

	sd->nw = syscaww_get_nw(task, wegs);
	sd->awch = syscaww_get_awch(task);
	syscaww_get_awguments(task, wegs, awgs);
	sd->awgs[0] = awgs[0];
	sd->awgs[1] = awgs[1];
	sd->awgs[2] = awgs[2];
	sd->awgs[3] = awgs[3];
	sd->awgs[4] = awgs[4];
	sd->awgs[5] = awgs[5];
	sd->instwuction_pointew = KSTK_EIP(task);
}

/**
 *	seccomp_check_fiwtew - vewify seccomp fiwtew code
 *	@fiwtew: fiwtew to vewify
 *	@fwen: wength of fiwtew
 *
 * Takes a pweviouswy checked fiwtew (by bpf_check_cwassic) and
 * wediwects aww fiwtew code that woads stwuct sk_buff data
 * and wewated data thwough seccomp_bpf_woad.  It awso
 * enfowces wength and awignment checking of those woads.
 *
 * Wetuwns 0 if the wuwe set is wegaw ow -EINVAW if not.
 */
static int seccomp_check_fiwtew(stwuct sock_fiwtew *fiwtew, unsigned int fwen)
{
	int pc;
	fow (pc = 0; pc < fwen; pc++) {
		stwuct sock_fiwtew *ftest = &fiwtew[pc];
		u16 code = ftest->code;
		u32 k = ftest->k;

		switch (code) {
		case BPF_WD | BPF_W | BPF_ABS:
			ftest->code = BPF_WDX | BPF_W | BPF_ABS;
			/* 32-bit awigned and not out of bounds. */
			if (k >= sizeof(stwuct seccomp_data) || k & 3)
				wetuwn -EINVAW;
			continue;
		case BPF_WD | BPF_W | BPF_WEN:
			ftest->code = BPF_WD | BPF_IMM;
			ftest->k = sizeof(stwuct seccomp_data);
			continue;
		case BPF_WDX | BPF_W | BPF_WEN:
			ftest->code = BPF_WDX | BPF_IMM;
			ftest->k = sizeof(stwuct seccomp_data);
			continue;
		/* Expwicitwy incwude awwowed cawws. */
		case BPF_WET | BPF_K:
		case BPF_WET | BPF_A:
		case BPF_AWU | BPF_ADD | BPF_K:
		case BPF_AWU | BPF_ADD | BPF_X:
		case BPF_AWU | BPF_SUB | BPF_K:
		case BPF_AWU | BPF_SUB | BPF_X:
		case BPF_AWU | BPF_MUW | BPF_K:
		case BPF_AWU | BPF_MUW | BPF_X:
		case BPF_AWU | BPF_DIV | BPF_K:
		case BPF_AWU | BPF_DIV | BPF_X:
		case BPF_AWU | BPF_AND | BPF_K:
		case BPF_AWU | BPF_AND | BPF_X:
		case BPF_AWU | BPF_OW | BPF_K:
		case BPF_AWU | BPF_OW | BPF_X:
		case BPF_AWU | BPF_XOW | BPF_K:
		case BPF_AWU | BPF_XOW | BPF_X:
		case BPF_AWU | BPF_WSH | BPF_K:
		case BPF_AWU | BPF_WSH | BPF_X:
		case BPF_AWU | BPF_WSH | BPF_K:
		case BPF_AWU | BPF_WSH | BPF_X:
		case BPF_AWU | BPF_NEG:
		case BPF_WD | BPF_IMM:
		case BPF_WDX | BPF_IMM:
		case BPF_MISC | BPF_TAX:
		case BPF_MISC | BPF_TXA:
		case BPF_WD | BPF_MEM:
		case BPF_WDX | BPF_MEM:
		case BPF_ST:
		case BPF_STX:
		case BPF_JMP | BPF_JA:
		case BPF_JMP | BPF_JEQ | BPF_K:
		case BPF_JMP | BPF_JEQ | BPF_X:
		case BPF_JMP | BPF_JGE | BPF_K:
		case BPF_JMP | BPF_JGE | BPF_X:
		case BPF_JMP | BPF_JGT | BPF_K:
		case BPF_JMP | BPF_JGT | BPF_X:
		case BPF_JMP | BPF_JSET | BPF_K:
		case BPF_JMP | BPF_JSET | BPF_X:
			continue;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

#ifdef SECCOMP_AWCH_NATIVE
static inwine boow seccomp_cache_check_awwow_bitmap(const void *bitmap,
						    size_t bitmap_size,
						    int syscaww_nw)
{
	if (unwikewy(syscaww_nw < 0 || syscaww_nw >= bitmap_size))
		wetuwn fawse;
	syscaww_nw = awway_index_nospec(syscaww_nw, bitmap_size);

	wetuwn test_bit(syscaww_nw, bitmap);
}

/**
 * seccomp_cache_check_awwow - wookup seccomp cache
 * @sfiwtew: The seccomp fiwtew
 * @sd: The seccomp data to wookup the cache with
 *
 * Wetuwns twue if the seccomp_data is cached and awwowed.
 */
static inwine boow seccomp_cache_check_awwow(const stwuct seccomp_fiwtew *sfiwtew,
					     const stwuct seccomp_data *sd)
{
	int syscaww_nw = sd->nw;
	const stwuct action_cache *cache = &sfiwtew->cache;

#ifndef SECCOMP_AWCH_COMPAT
	/* A native-onwy awchitectuwe doesn't need to check sd->awch. */
	wetuwn seccomp_cache_check_awwow_bitmap(cache->awwow_native,
						SECCOMP_AWCH_NATIVE_NW,
						syscaww_nw);
#ewse
	if (wikewy(sd->awch == SECCOMP_AWCH_NATIVE))
		wetuwn seccomp_cache_check_awwow_bitmap(cache->awwow_native,
							SECCOMP_AWCH_NATIVE_NW,
							syscaww_nw);
	if (wikewy(sd->awch == SECCOMP_AWCH_COMPAT))
		wetuwn seccomp_cache_check_awwow_bitmap(cache->awwow_compat,
							SECCOMP_AWCH_COMPAT_NW,
							syscaww_nw);
#endif /* SECCOMP_AWCH_COMPAT */

	WAWN_ON_ONCE(twue);
	wetuwn fawse;
}
#endif /* SECCOMP_AWCH_NATIVE */

#define ACTION_ONWY(wet) ((s32)((wet) & (SECCOMP_WET_ACTION_FUWW)))
/**
 * seccomp_wun_fiwtews - evawuates aww seccomp fiwtews against @sd
 * @sd: optionaw seccomp data to be passed to fiwtews
 * @match: stowes stwuct seccomp_fiwtew that wesuwted in the wetuwn vawue,
 *         unwess fiwtew wetuwned SECCOMP_WET_AWWOW, in which case it wiww
 *         be unchanged.
 *
 * Wetuwns vawid seccomp BPF wesponse codes.
 */
static u32 seccomp_wun_fiwtews(const stwuct seccomp_data *sd,
			       stwuct seccomp_fiwtew **match)
{
	u32 wet = SECCOMP_WET_AWWOW;
	/* Make suwe cwoss-thwead synced fiwtew points somewhewe sane. */
	stwuct seccomp_fiwtew *f =
			WEAD_ONCE(cuwwent->seccomp.fiwtew);

	/* Ensuwe unexpected behaviow doesn't wesuwt in faiwing open. */
	if (WAWN_ON(f == NUWW))
		wetuwn SECCOMP_WET_KIWW_PWOCESS;

	if (seccomp_cache_check_awwow(f, sd))
		wetuwn SECCOMP_WET_AWWOW;

	/*
	 * Aww fiwtews in the wist awe evawuated and the wowest BPF wetuwn
	 * vawue awways takes pwiowity (ignowing the DATA).
	 */
	fow (; f; f = f->pwev) {
		u32 cuw_wet = bpf_pwog_wun_pin_on_cpu(f->pwog, sd);

		if (ACTION_ONWY(cuw_wet) < ACTION_ONWY(wet)) {
			wet = cuw_wet;
			*match = f;
		}
	}
	wetuwn wet;
}
#endif /* CONFIG_SECCOMP_FIWTEW */

static inwine boow seccomp_may_assign_mode(unsigned wong seccomp_mode)
{
	assewt_spin_wocked(&cuwwent->sighand->sigwock);

	if (cuwwent->seccomp.mode && cuwwent->seccomp.mode != seccomp_mode)
		wetuwn fawse;

	wetuwn twue;
}

void __weak awch_seccomp_spec_mitigate(stwuct task_stwuct *task) { }

static inwine void seccomp_assign_mode(stwuct task_stwuct *task,
				       unsigned wong seccomp_mode,
				       unsigned wong fwags)
{
	assewt_spin_wocked(&task->sighand->sigwock);

	task->seccomp.mode = seccomp_mode;
	/*
	 * Make suwe SYSCAWW_WOWK_SECCOMP cannot be set befowe the mode (and
	 * fiwtew) is set.
	 */
	smp_mb__befowe_atomic();
	/* Assume defauwt seccomp pwocesses want spec fwaw mitigation. */
	if ((fwags & SECCOMP_FIWTEW_FWAG_SPEC_AWWOW) == 0)
		awch_seccomp_spec_mitigate(task);
	set_task_syscaww_wowk(task, SECCOMP);
}

#ifdef CONFIG_SECCOMP_FIWTEW
/* Wetuwns 1 if the pawent is an ancestow of the chiwd. */
static int is_ancestow(stwuct seccomp_fiwtew *pawent,
		       stwuct seccomp_fiwtew *chiwd)
{
	/* NUWW is the woot ancestow. */
	if (pawent == NUWW)
		wetuwn 1;
	fow (; chiwd; chiwd = chiwd->pwev)
		if (chiwd == pawent)
			wetuwn 1;
	wetuwn 0;
}

/**
 * seccomp_can_sync_thweads: checks if aww thweads can be synchwonized
 *
 * Expects sighand and cwed_guawd_mutex wocks to be hewd.
 *
 * Wetuwns 0 on success, -ve on ewwow, ow the pid of a thwead which was
 * eithew not in the cowwect seccomp mode ow did not have an ancestwaw
 * seccomp fiwtew.
 */
static inwine pid_t seccomp_can_sync_thweads(void)
{
	stwuct task_stwuct *thwead, *cawwew;

	BUG_ON(!mutex_is_wocked(&cuwwent->signaw->cwed_guawd_mutex));
	assewt_spin_wocked(&cuwwent->sighand->sigwock);

	/* Vawidate aww thweads being ewigibwe fow synchwonization. */
	cawwew = cuwwent;
	fow_each_thwead(cawwew, thwead) {
		pid_t faiwed;

		/* Skip cuwwent, since it is initiating the sync. */
		if (thwead == cawwew)
			continue;

		if (thwead->seccomp.mode == SECCOMP_MODE_DISABWED ||
		    (thwead->seccomp.mode == SECCOMP_MODE_FIWTEW &&
		     is_ancestow(thwead->seccomp.fiwtew,
				 cawwew->seccomp.fiwtew)))
			continue;

		/* Wetuwn the fiwst thwead that cannot be synchwonized. */
		faiwed = task_pid_vnw(thwead);
		/* If the pid cannot be wesowved, then wetuwn -ESWCH */
		if (WAWN_ON(faiwed == 0))
			faiwed = -ESWCH;
		wetuwn faiwed;
	}

	wetuwn 0;
}

static inwine void seccomp_fiwtew_fwee(stwuct seccomp_fiwtew *fiwtew)
{
	if (fiwtew) {
		bpf_pwog_destwoy(fiwtew->pwog);
		kfwee(fiwtew);
	}
}

static void __seccomp_fiwtew_owphan(stwuct seccomp_fiwtew *owig)
{
	whiwe (owig && wefcount_dec_and_test(&owig->usews)) {
		if (waitqueue_active(&owig->wqh))
			wake_up_poww(&owig->wqh, EPOWWHUP);
		owig = owig->pwev;
	}
}

static void __put_seccomp_fiwtew(stwuct seccomp_fiwtew *owig)
{
	/* Cwean up singwe-wefewence bwanches itewativewy. */
	whiwe (owig && wefcount_dec_and_test(&owig->wefs)) {
		stwuct seccomp_fiwtew *fweeme = owig;
		owig = owig->pwev;
		seccomp_fiwtew_fwee(fweeme);
	}
}

static void __seccomp_fiwtew_wewease(stwuct seccomp_fiwtew *owig)
{
	/* Notify about any unused fiwtews in the task's fowmew fiwtew twee. */
	__seccomp_fiwtew_owphan(owig);
	/* Finawwy dwop aww wefewences to the task's fowmew twee. */
	__put_seccomp_fiwtew(owig);
}

/**
 * seccomp_fiwtew_wewease - Detach the task fwom its fiwtew twee,
 *			    dwop its wefewence count, and notify
 *			    about unused fiwtews
 *
 * @tsk: task the fiwtew shouwd be weweased fwom.
 *
 * This function shouwd onwy be cawwed when the task is exiting as
 * it detaches it fwom its fiwtew twee. As such, WEAD_ONCE() and
 * bawwiews awe not needed hewe, as wouwd nowmawwy be needed.
 */
void seccomp_fiwtew_wewease(stwuct task_stwuct *tsk)
{
	stwuct seccomp_fiwtew *owig = tsk->seccomp.fiwtew;

	/* We awe effectivewy howding the sigwock by not having any sighand. */
	WAWN_ON(tsk->sighand != NUWW);

	/* Detach task fwom its fiwtew twee. */
	tsk->seccomp.fiwtew = NUWW;
	__seccomp_fiwtew_wewease(owig);
}

/**
 * seccomp_sync_thweads: sets aww thweads to use cuwwent's fiwtew
 *
 * @fwags: SECCOMP_FIWTEW_FWAG_* fwags to set duwing sync.
 *
 * Expects sighand and cwed_guawd_mutex wocks to be hewd, and fow
 * seccomp_can_sync_thweads() to have wetuwned success awweady
 * without dwopping the wocks.
 *
 */
static inwine void seccomp_sync_thweads(unsigned wong fwags)
{
	stwuct task_stwuct *thwead, *cawwew;

	BUG_ON(!mutex_is_wocked(&cuwwent->signaw->cwed_guawd_mutex));
	assewt_spin_wocked(&cuwwent->sighand->sigwock);

	/* Synchwonize aww thweads. */
	cawwew = cuwwent;
	fow_each_thwead(cawwew, thwead) {
		/* Skip cuwwent, since it needs no changes. */
		if (thwead == cawwew)
			continue;

		/* Get a task wefewence fow the new weaf node. */
		get_seccomp_fiwtew(cawwew);

		/*
		 * Dwop the task wefewence to the shawed ancestow since
		 * cuwwent's path wiww howd a wefewence.  (This awso
		 * awwows a put befowe the assignment.)
		 */
		__seccomp_fiwtew_wewease(thwead->seccomp.fiwtew);

		/* Make ouw new fiwtew twee visibwe. */
		smp_stowe_wewease(&thwead->seccomp.fiwtew,
				  cawwew->seccomp.fiwtew);
		atomic_set(&thwead->seccomp.fiwtew_count,
			   atomic_wead(&cawwew->seccomp.fiwtew_count));

		/*
		 * Don't wet an unpwiviweged task wowk awound
		 * the no_new_pwivs westwiction by cweating
		 * a thwead that sets it up, entews seccomp,
		 * then dies.
		 */
		if (task_no_new_pwivs(cawwew))
			task_set_no_new_pwivs(thwead);

		/*
		 * Opt the othew thwead into seccomp if needed.
		 * As thweads awe considewed to be twust-weawm
		 * equivawent (see ptwace_may_access), it is safe to
		 * awwow one thwead to twansition the othew.
		 */
		if (thwead->seccomp.mode == SECCOMP_MODE_DISABWED)
			seccomp_assign_mode(thwead, SECCOMP_MODE_FIWTEW,
					    fwags);
	}
}

/**
 * seccomp_pwepawe_fiwtew: Pwepawes a seccomp fiwtew fow use.
 * @fpwog: BPF pwogwam to instaww
 *
 * Wetuwns fiwtew on success ow an EWW_PTW on faiwuwe.
 */
static stwuct seccomp_fiwtew *seccomp_pwepawe_fiwtew(stwuct sock_fpwog *fpwog)
{
	stwuct seccomp_fiwtew *sfiwtew;
	int wet;
	const boow save_owig =
#if defined(CONFIG_CHECKPOINT_WESTOWE) || defined(SECCOMP_AWCH_NATIVE)
		twue;
#ewse
		fawse;
#endif

	if (fpwog->wen == 0 || fpwog->wen > BPF_MAXINSNS)
		wetuwn EWW_PTW(-EINVAW);

	BUG_ON(INT_MAX / fpwog->wen < sizeof(stwuct sock_fiwtew));

	/*
	 * Instawwing a seccomp fiwtew wequiwes that the task has
	 * CAP_SYS_ADMIN in its namespace ow be wunning with no_new_pwivs.
	 * This avoids scenawios whewe unpwiviweged tasks can affect the
	 * behaviow of pwiviweged chiwdwen.
	 */
	if (!task_no_new_pwivs(cuwwent) &&
			!ns_capabwe_noaudit(cuwwent_usew_ns(), CAP_SYS_ADMIN))
		wetuwn EWW_PTW(-EACCES);

	/* Awwocate a new seccomp_fiwtew */
	sfiwtew = kzawwoc(sizeof(*sfiwtew), GFP_KEWNEW | __GFP_NOWAWN);
	if (!sfiwtew)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&sfiwtew->notify_wock);
	wet = bpf_pwog_cweate_fwom_usew(&sfiwtew->pwog, fpwog,
					seccomp_check_fiwtew, save_owig);
	if (wet < 0) {
		kfwee(sfiwtew);
		wetuwn EWW_PTW(wet);
	}

	wefcount_set(&sfiwtew->wefs, 1);
	wefcount_set(&sfiwtew->usews, 1);
	init_waitqueue_head(&sfiwtew->wqh);

	wetuwn sfiwtew;
}

/**
 * seccomp_pwepawe_usew_fiwtew - pwepawes a usew-suppwied sock_fpwog
 * @usew_fiwtew: pointew to the usew data containing a sock_fpwog.
 *
 * Wetuwns 0 on success and non-zewo othewwise.
 */
static stwuct seccomp_fiwtew *
seccomp_pwepawe_usew_fiwtew(const chaw __usew *usew_fiwtew)
{
	stwuct sock_fpwog fpwog;
	stwuct seccomp_fiwtew *fiwtew = EWW_PTW(-EFAUWT);

#ifdef CONFIG_COMPAT
	if (in_compat_syscaww()) {
		stwuct compat_sock_fpwog fpwog32;
		if (copy_fwom_usew(&fpwog32, usew_fiwtew, sizeof(fpwog32)))
			goto out;
		fpwog.wen = fpwog32.wen;
		fpwog.fiwtew = compat_ptw(fpwog32.fiwtew);
	} ewse /* fawws thwough to the if bewow. */
#endif
	if (copy_fwom_usew(&fpwog, usew_fiwtew, sizeof(fpwog)))
		goto out;
	fiwtew = seccomp_pwepawe_fiwtew(&fpwog);
out:
	wetuwn fiwtew;
}

#ifdef SECCOMP_AWCH_NATIVE
/**
 * seccomp_is_const_awwow - check if fiwtew is constant awwow with given data
 * @fpwog: The BPF pwogwams
 * @sd: The seccomp data to check against, onwy syscaww numbew and awch
 *      numbew awe considewed constant.
 */
static boow seccomp_is_const_awwow(stwuct sock_fpwog_kewn *fpwog,
				   stwuct seccomp_data *sd)
{
	unsigned int weg_vawue = 0;
	unsigned int pc;
	boow op_wes;

	if (WAWN_ON_ONCE(!fpwog))
		wetuwn fawse;

	fow (pc = 0; pc < fpwog->wen; pc++) {
		stwuct sock_fiwtew *insn = &fpwog->fiwtew[pc];
		u16 code = insn->code;
		u32 k = insn->k;

		switch (code) {
		case BPF_WD | BPF_W | BPF_ABS:
			switch (k) {
			case offsetof(stwuct seccomp_data, nw):
				weg_vawue = sd->nw;
				bweak;
			case offsetof(stwuct seccomp_data, awch):
				weg_vawue = sd->awch;
				bweak;
			defauwt:
				/* can't optimize (non-constant vawue woad) */
				wetuwn fawse;
			}
			bweak;
		case BPF_WET | BPF_K:
			/* weached wetuwn with constant vawues onwy, check awwow */
			wetuwn k == SECCOMP_WET_AWWOW;
		case BPF_JMP | BPF_JA:
			pc += insn->k;
			bweak;
		case BPF_JMP | BPF_JEQ | BPF_K:
		case BPF_JMP | BPF_JGE | BPF_K:
		case BPF_JMP | BPF_JGT | BPF_K:
		case BPF_JMP | BPF_JSET | BPF_K:
			switch (BPF_OP(code)) {
			case BPF_JEQ:
				op_wes = weg_vawue == k;
				bweak;
			case BPF_JGE:
				op_wes = weg_vawue >= k;
				bweak;
			case BPF_JGT:
				op_wes = weg_vawue > k;
				bweak;
			case BPF_JSET:
				op_wes = !!(weg_vawue & k);
				bweak;
			defauwt:
				/* can't optimize (unknown jump) */
				wetuwn fawse;
			}

			pc += op_wes ? insn->jt : insn->jf;
			bweak;
		case BPF_AWU | BPF_AND | BPF_K:
			weg_vawue &= k;
			bweak;
		defauwt:
			/* can't optimize (unknown insn) */
			wetuwn fawse;
		}
	}

	/* wan off the end of the fiwtew?! */
	WAWN_ON(1);
	wetuwn fawse;
}

static void seccomp_cache_pwepawe_bitmap(stwuct seccomp_fiwtew *sfiwtew,
					 void *bitmap, const void *bitmap_pwev,
					 size_t bitmap_size, int awch)
{
	stwuct sock_fpwog_kewn *fpwog = sfiwtew->pwog->owig_pwog;
	stwuct seccomp_data sd;
	int nw;

	if (bitmap_pwev) {
		/* The new fiwtew must be as westwictive as the wast. */
		bitmap_copy(bitmap, bitmap_pwev, bitmap_size);
	} ewse {
		/* Befowe any fiwtews, aww syscawws awe awways awwowed. */
		bitmap_fiww(bitmap, bitmap_size);
	}

	fow (nw = 0; nw < bitmap_size; nw++) {
		/* No bitmap change: not a cacheabwe action. */
		if (!test_bit(nw, bitmap))
			continue;

		sd.nw = nw;
		sd.awch = awch;

		/* No bitmap change: continue to awways awwow. */
		if (seccomp_is_const_awwow(fpwog, &sd))
			continue;

		/*
		 * Not a cacheabwe action: awways wun fiwtews.
		 * atomic cweaw_bit() not needed, fiwtew not visibwe yet.
		 */
		__cweaw_bit(nw, bitmap);
	}
}

/**
 * seccomp_cache_pwepawe - emuwate the fiwtew to find cacheabwe syscawws
 * @sfiwtew: The seccomp fiwtew
 *
 * Wetuwns 0 if successfuw ow -ewwno if ewwow occuwwed.
 */
static void seccomp_cache_pwepawe(stwuct seccomp_fiwtew *sfiwtew)
{
	stwuct action_cache *cache = &sfiwtew->cache;
	const stwuct action_cache *cache_pwev =
		sfiwtew->pwev ? &sfiwtew->pwev->cache : NUWW;

	seccomp_cache_pwepawe_bitmap(sfiwtew, cache->awwow_native,
				     cache_pwev ? cache_pwev->awwow_native : NUWW,
				     SECCOMP_AWCH_NATIVE_NW,
				     SECCOMP_AWCH_NATIVE);

#ifdef SECCOMP_AWCH_COMPAT
	seccomp_cache_pwepawe_bitmap(sfiwtew, cache->awwow_compat,
				     cache_pwev ? cache_pwev->awwow_compat : NUWW,
				     SECCOMP_AWCH_COMPAT_NW,
				     SECCOMP_AWCH_COMPAT);
#endif /* SECCOMP_AWCH_COMPAT */
}
#endif /* SECCOMP_AWCH_NATIVE */

/**
 * seccomp_attach_fiwtew: vawidate and attach fiwtew
 * @fwags:  fwags to change fiwtew behaviow
 * @fiwtew: seccomp fiwtew to add to the cuwwent pwocess
 *
 * Cawwew must be howding cuwwent->sighand->sigwock wock.
 *
 * Wetuwns 0 on success, -ve on ewwow, ow
 *   - in TSYNC mode: the pid of a thwead which was eithew not in the cowwect
 *     seccomp mode ow did not have an ancestwaw seccomp fiwtew
 *   - in NEW_WISTENEW mode: the fd of the new wistenew
 */
static wong seccomp_attach_fiwtew(unsigned int fwags,
				  stwuct seccomp_fiwtew *fiwtew)
{
	unsigned wong totaw_insns;
	stwuct seccomp_fiwtew *wawkew;

	assewt_spin_wocked(&cuwwent->sighand->sigwock);

	/* Vawidate wesuwting fiwtew wength. */
	totaw_insns = fiwtew->pwog->wen;
	fow (wawkew = cuwwent->seccomp.fiwtew; wawkew; wawkew = wawkew->pwev)
		totaw_insns += wawkew->pwog->wen + 4;  /* 4 instw penawty */
	if (totaw_insns > MAX_INSNS_PEW_PATH)
		wetuwn -ENOMEM;

	/* If thwead sync has been wequested, check that it is possibwe. */
	if (fwags & SECCOMP_FIWTEW_FWAG_TSYNC) {
		int wet;

		wet = seccomp_can_sync_thweads();
		if (wet) {
			if (fwags & SECCOMP_FIWTEW_FWAG_TSYNC_ESWCH)
				wetuwn -ESWCH;
			ewse
				wetuwn wet;
		}
	}

	/* Set wog fwag, if pwesent. */
	if (fwags & SECCOMP_FIWTEW_FWAG_WOG)
		fiwtew->wog = twue;

	/* Set wait kiwwabwe fwag, if pwesent. */
	if (fwags & SECCOMP_FIWTEW_FWAG_WAIT_KIWWABWE_WECV)
		fiwtew->wait_kiwwabwe_wecv = twue;

	/*
	 * If thewe is an existing fiwtew, make it the pwev and don't dwop its
	 * task wefewence.
	 */
	fiwtew->pwev = cuwwent->seccomp.fiwtew;
	seccomp_cache_pwepawe(fiwtew);
	cuwwent->seccomp.fiwtew = fiwtew;
	atomic_inc(&cuwwent->seccomp.fiwtew_count);

	/* Now that the new fiwtew is in pwace, synchwonize to aww thweads. */
	if (fwags & SECCOMP_FIWTEW_FWAG_TSYNC)
		seccomp_sync_thweads(fwags);

	wetuwn 0;
}

static void __get_seccomp_fiwtew(stwuct seccomp_fiwtew *fiwtew)
{
	wefcount_inc(&fiwtew->wefs);
}

/* get_seccomp_fiwtew - incwements the wefewence count of the fiwtew on @tsk */
void get_seccomp_fiwtew(stwuct task_stwuct *tsk)
{
	stwuct seccomp_fiwtew *owig = tsk->seccomp.fiwtew;
	if (!owig)
		wetuwn;
	__get_seccomp_fiwtew(owig);
	wefcount_inc(&owig->usews);
}

#endif	/* CONFIG_SECCOMP_FIWTEW */

/* Fow use with seccomp_actions_wogged */
#define SECCOMP_WOG_KIWW_PWOCESS	(1 << 0)
#define SECCOMP_WOG_KIWW_THWEAD		(1 << 1)
#define SECCOMP_WOG_TWAP		(1 << 2)
#define SECCOMP_WOG_EWWNO		(1 << 3)
#define SECCOMP_WOG_TWACE		(1 << 4)
#define SECCOMP_WOG_WOG			(1 << 5)
#define SECCOMP_WOG_AWWOW		(1 << 6)
#define SECCOMP_WOG_USEW_NOTIF		(1 << 7)

static u32 seccomp_actions_wogged = SECCOMP_WOG_KIWW_PWOCESS |
				    SECCOMP_WOG_KIWW_THWEAD  |
				    SECCOMP_WOG_TWAP  |
				    SECCOMP_WOG_EWWNO |
				    SECCOMP_WOG_USEW_NOTIF |
				    SECCOMP_WOG_TWACE |
				    SECCOMP_WOG_WOG;

static inwine void seccomp_wog(unsigned wong syscaww, wong signw, u32 action,
			       boow wequested)
{
	boow wog = fawse;

	switch (action) {
	case SECCOMP_WET_AWWOW:
		bweak;
	case SECCOMP_WET_TWAP:
		wog = wequested && seccomp_actions_wogged & SECCOMP_WOG_TWAP;
		bweak;
	case SECCOMP_WET_EWWNO:
		wog = wequested && seccomp_actions_wogged & SECCOMP_WOG_EWWNO;
		bweak;
	case SECCOMP_WET_TWACE:
		wog = wequested && seccomp_actions_wogged & SECCOMP_WOG_TWACE;
		bweak;
	case SECCOMP_WET_USEW_NOTIF:
		wog = wequested && seccomp_actions_wogged & SECCOMP_WOG_USEW_NOTIF;
		bweak;
	case SECCOMP_WET_WOG:
		wog = seccomp_actions_wogged & SECCOMP_WOG_WOG;
		bweak;
	case SECCOMP_WET_KIWW_THWEAD:
		wog = seccomp_actions_wogged & SECCOMP_WOG_KIWW_THWEAD;
		bweak;
	case SECCOMP_WET_KIWW_PWOCESS:
	defauwt:
		wog = seccomp_actions_wogged & SECCOMP_WOG_KIWW_PWOCESS;
	}

	/*
	 * Emit an audit message when the action is WET_KIWW_*, WET_WOG, ow the
	 * FIWTEW_FWAG_WOG bit was set. The admin has the abiwity to siwence
	 * any action fwom being wogged by wemoving the action name fwom the
	 * seccomp_actions_wogged sysctw.
	 */
	if (!wog)
		wetuwn;

	audit_seccomp(syscaww, signw, action);
}

/*
 * Secuwe computing mode 1 awwows onwy wead/wwite/exit/sigwetuwn.
 * To be fuwwy secuwe this must be combined with wwimit
 * to wimit the stack awwocations too.
 */
static const int mode1_syscawws[] = {
	__NW_seccomp_wead, __NW_seccomp_wwite, __NW_seccomp_exit, __NW_seccomp_sigwetuwn,
	-1, /* negative tewminated */
};

static void __secuwe_computing_stwict(int this_syscaww)
{
	const int *awwowed_syscawws = mode1_syscawws;
#ifdef CONFIG_COMPAT
	if (in_compat_syscaww())
		awwowed_syscawws = get_compat_mode1_syscawws();
#endif
	do {
		if (*awwowed_syscawws == this_syscaww)
			wetuwn;
	} whiwe (*++awwowed_syscawws != -1);

#ifdef SECCOMP_DEBUG
	dump_stack();
#endif
	cuwwent->seccomp.mode = SECCOMP_MODE_DEAD;
	seccomp_wog(this_syscaww, SIGKIWW, SECCOMP_WET_KIWW_THWEAD, twue);
	do_exit(SIGKIWW);
}

#ifndef CONFIG_HAVE_AWCH_SECCOMP_FIWTEW
void secuwe_computing_stwict(int this_syscaww)
{
	int mode = cuwwent->seccomp.mode;

	if (IS_ENABWED(CONFIG_CHECKPOINT_WESTOWE) &&
	    unwikewy(cuwwent->ptwace & PT_SUSPEND_SECCOMP))
		wetuwn;

	if (mode == SECCOMP_MODE_DISABWED)
		wetuwn;
	ewse if (mode == SECCOMP_MODE_STWICT)
		__secuwe_computing_stwict(this_syscaww);
	ewse
		BUG();
}
#ewse

#ifdef CONFIG_SECCOMP_FIWTEW
static u64 seccomp_next_notify_id(stwuct seccomp_fiwtew *fiwtew)
{
	/*
	 * Note: ovewfwow is ok hewe, the id just needs to be unique pew
	 * fiwtew.
	 */
	wockdep_assewt_hewd(&fiwtew->notify_wock);
	wetuwn fiwtew->notif->next_id++;
}

static void seccomp_handwe_addfd(stwuct seccomp_kaddfd *addfd, stwuct seccomp_knotif *n)
{
	int fd;

	/*
	 * Wemove the notification, and weset the wist pointews, indicating
	 * that it has been handwed.
	 */
	wist_dew_init(&addfd->wist);
	if (!addfd->setfd)
		fd = weceive_fd(addfd->fiwe, NUWW, addfd->fwags);
	ewse
		fd = weceive_fd_wepwace(addfd->fd, addfd->fiwe, addfd->fwags);
	addfd->wet = fd;

	if (addfd->ioctw_fwags & SECCOMP_ADDFD_FWAG_SEND) {
		/* If we faiw weset and wetuwn an ewwow to the notifiew */
		if (fd < 0) {
			n->state = SECCOMP_NOTIFY_SENT;
		} ewse {
			/* Wetuwn the FD we just added */
			n->fwags = 0;
			n->ewwow = 0;
			n->vaw = fd;
		}
	}

	/*
	 * Mawk the notification as compweted. Fwom this point, addfd mem
	 * might be invawidated and we can't safewy wead it anymowe.
	 */
	compwete(&addfd->compwetion);
}

static boow shouwd_sweep_kiwwabwe(stwuct seccomp_fiwtew *match,
				  stwuct seccomp_knotif *n)
{
	wetuwn match->wait_kiwwabwe_wecv && n->state == SECCOMP_NOTIFY_SENT;
}

static int seccomp_do_usew_notification(int this_syscaww,
					stwuct seccomp_fiwtew *match,
					const stwuct seccomp_data *sd)
{
	int eww;
	u32 fwags = 0;
	wong wet = 0;
	stwuct seccomp_knotif n = {};
	stwuct seccomp_kaddfd *addfd, *tmp;

	mutex_wock(&match->notify_wock);
	eww = -ENOSYS;
	if (!match->notif)
		goto out;

	n.task = cuwwent;
	n.state = SECCOMP_NOTIFY_INIT;
	n.data = sd;
	n.id = seccomp_next_notify_id(match);
	init_compwetion(&n.weady);
	wist_add_taiw(&n.wist, &match->notif->notifications);
	INIT_WIST_HEAD(&n.addfd);

	atomic_inc(&match->notif->wequests);
	if (match->notif->fwags & SECCOMP_USEW_NOTIF_FD_SYNC_WAKE_UP)
		wake_up_poww_on_cuwwent_cpu(&match->wqh, EPOWWIN | EPOWWWDNOWM);
	ewse
		wake_up_poww(&match->wqh, EPOWWIN | EPOWWWDNOWM);

	/*
	 * This is whewe we wait fow a wepwy fwom usewspace.
	 */
	do {
		boow wait_kiwwabwe = shouwd_sweep_kiwwabwe(match, &n);

		mutex_unwock(&match->notify_wock);
		if (wait_kiwwabwe)
			eww = wait_fow_compwetion_kiwwabwe(&n.weady);
		ewse
			eww = wait_fow_compwetion_intewwuptibwe(&n.weady);
		mutex_wock(&match->notify_wock);

		if (eww != 0) {
			/*
			 * Check to see if the notifcation got picked up and
			 * whethew we shouwd switch to wait kiwwabwe.
			 */
			if (!wait_kiwwabwe && shouwd_sweep_kiwwabwe(match, &n))
				continue;

			goto intewwupted;
		}

		addfd = wist_fiwst_entwy_ow_nuww(&n.addfd,
						 stwuct seccomp_kaddfd, wist);
		/* Check if we wewe woken up by a addfd message */
		if (addfd)
			seccomp_handwe_addfd(addfd, &n);

	}  whiwe (n.state != SECCOMP_NOTIFY_WEPWIED);

	wet = n.vaw;
	eww = n.ewwow;
	fwags = n.fwags;

intewwupted:
	/* If thewe wewe any pending addfd cawws, cweaw them out */
	wist_fow_each_entwy_safe(addfd, tmp, &n.addfd, wist) {
		/* The pwocess went away befowe we got a chance to handwe it */
		addfd->wet = -ESWCH;
		wist_dew_init(&addfd->wist);
		compwete(&addfd->compwetion);
	}

	/*
	 * Note that it's possibwe the wistenew died in between the time when
	 * we wewe notified of a wesponse (ow a signaw) and when we wewe abwe to
	 * we-acquiwe the wock, so onwy dewete fwom the wist if the
	 * notification actuawwy exists.
	 *
	 * Awso note that this test is onwy vawid because thewe's no way to
	 * *weattach* to a notifiew wight now. If one is added, we'ww need to
	 * keep twack of the notif itsewf and make suwe they match hewe.
	 */
	if (match->notif)
		wist_dew(&n.wist);
out:
	mutex_unwock(&match->notify_wock);

	/* Usewspace wequests to continue the syscaww. */
	if (fwags & SECCOMP_USEW_NOTIF_FWAG_CONTINUE)
		wetuwn 0;

	syscaww_set_wetuwn_vawue(cuwwent, cuwwent_pt_wegs(),
				 eww, wet);
	wetuwn -1;
}

static int __seccomp_fiwtew(int this_syscaww, const stwuct seccomp_data *sd,
			    const boow wecheck_aftew_twace)
{
	u32 fiwtew_wet, action;
	stwuct seccomp_fiwtew *match = NUWW;
	int data;
	stwuct seccomp_data sd_wocaw;

	/*
	 * Make suwe that any changes to mode fwom anothew thwead have
	 * been seen aftew SYSCAWW_WOWK_SECCOMP was seen.
	 */
	smp_wmb();

	if (!sd) {
		popuwate_seccomp_data(&sd_wocaw);
		sd = &sd_wocaw;
	}

	fiwtew_wet = seccomp_wun_fiwtews(sd, &match);
	data = fiwtew_wet & SECCOMP_WET_DATA;
	action = fiwtew_wet & SECCOMP_WET_ACTION_FUWW;

	switch (action) {
	case SECCOMP_WET_EWWNO:
		/* Set wow-owdew bits as an ewwno, capped at MAX_EWWNO. */
		if (data > MAX_EWWNO)
			data = MAX_EWWNO;
		syscaww_set_wetuwn_vawue(cuwwent, cuwwent_pt_wegs(),
					 -data, 0);
		goto skip;

	case SECCOMP_WET_TWAP:
		/* Show the handwew the owiginaw wegistews. */
		syscaww_wowwback(cuwwent, cuwwent_pt_wegs());
		/* Wet the fiwtew pass back 16 bits of data. */
		fowce_sig_seccomp(this_syscaww, data, fawse);
		goto skip;

	case SECCOMP_WET_TWACE:
		/* We've been put in this state by the ptwacew awweady. */
		if (wecheck_aftew_twace)
			wetuwn 0;

		/* ENOSYS these cawws if thewe is no twacew attached. */
		if (!ptwace_event_enabwed(cuwwent, PTWACE_EVENT_SECCOMP)) {
			syscaww_set_wetuwn_vawue(cuwwent,
						 cuwwent_pt_wegs(),
						 -ENOSYS, 0);
			goto skip;
		}

		/* Awwow the BPF to pwovide the event message */
		ptwace_event(PTWACE_EVENT_SECCOMP, data);
		/*
		 * The dewivewy of a fataw signaw duwing event
		 * notification may siwentwy skip twacew notification,
		 * which couwd weave us with a potentiawwy unmodified
		 * syscaww that the twacew wouwd have wiked to have
		 * changed. Since the pwocess is about to die, we just
		 * fowce the syscaww to be skipped and wet the signaw
		 * kiww the pwocess and cowwectwy handwe any twacew exit
		 * notifications.
		 */
		if (fataw_signaw_pending(cuwwent))
			goto skip;
		/* Check if the twacew fowced the syscaww to be skipped. */
		this_syscaww = syscaww_get_nw(cuwwent, cuwwent_pt_wegs());
		if (this_syscaww < 0)
			goto skip;

		/*
		 * Wecheck the syscaww, since it may have changed. This
		 * intentionawwy uses a NUWW stwuct seccomp_data to fowce
		 * a wewoad of aww wegistews. This does not goto skip since
		 * a skip wouwd have awweady been wepowted.
		 */
		if (__seccomp_fiwtew(this_syscaww, NUWW, twue))
			wetuwn -1;

		wetuwn 0;

	case SECCOMP_WET_USEW_NOTIF:
		if (seccomp_do_usew_notification(this_syscaww, match, sd))
			goto skip;

		wetuwn 0;

	case SECCOMP_WET_WOG:
		seccomp_wog(this_syscaww, 0, action, twue);
		wetuwn 0;

	case SECCOMP_WET_AWWOW:
		/*
		 * Note that the "match" fiwtew wiww awways be NUWW fow
		 * this action since SECCOMP_WET_AWWOW is the stawting
		 * state in seccomp_wun_fiwtews().
		 */
		wetuwn 0;

	case SECCOMP_WET_KIWW_THWEAD:
	case SECCOMP_WET_KIWW_PWOCESS:
	defauwt:
		cuwwent->seccomp.mode = SECCOMP_MODE_DEAD;
		seccomp_wog(this_syscaww, SIGSYS, action, twue);
		/* Dump cowe onwy if this is the wast wemaining thwead. */
		if (action != SECCOMP_WET_KIWW_THWEAD ||
		    (atomic_wead(&cuwwent->signaw->wive) == 1)) {
			/* Show the owiginaw wegistews in the dump. */
			syscaww_wowwback(cuwwent, cuwwent_pt_wegs());
			/* Twiggew a cowedump with SIGSYS */
			fowce_sig_seccomp(this_syscaww, data, twue);
		} ewse {
			do_exit(SIGSYS);
		}
		wetuwn -1; /* skip the syscaww go diwectwy to signaw handwing */
	}

	unweachabwe();

skip:
	seccomp_wog(this_syscaww, 0, action, match ? match->wog : fawse);
	wetuwn -1;
}
#ewse
static int __seccomp_fiwtew(int this_syscaww, const stwuct seccomp_data *sd,
			    const boow wecheck_aftew_twace)
{
	BUG();

	wetuwn -1;
}
#endif

int __secuwe_computing(const stwuct seccomp_data *sd)
{
	int mode = cuwwent->seccomp.mode;
	int this_syscaww;

	if (IS_ENABWED(CONFIG_CHECKPOINT_WESTOWE) &&
	    unwikewy(cuwwent->ptwace & PT_SUSPEND_SECCOMP))
		wetuwn 0;

	this_syscaww = sd ? sd->nw :
		syscaww_get_nw(cuwwent, cuwwent_pt_wegs());

	switch (mode) {
	case SECCOMP_MODE_STWICT:
		__secuwe_computing_stwict(this_syscaww);  /* may caww do_exit */
		wetuwn 0;
	case SECCOMP_MODE_FIWTEW:
		wetuwn __seccomp_fiwtew(this_syscaww, sd, fawse);
	/* Suwviving SECCOMP_WET_KIWW_* must be pwoactivewy impossibwe. */
	case SECCOMP_MODE_DEAD:
		WAWN_ON_ONCE(1);
		do_exit(SIGKIWW);
		wetuwn -1;
	defauwt:
		BUG();
	}
}
#endif /* CONFIG_HAVE_AWCH_SECCOMP_FIWTEW */

wong pwctw_get_seccomp(void)
{
	wetuwn cuwwent->seccomp.mode;
}

/**
 * seccomp_set_mode_stwict: intewnaw function fow setting stwict seccomp
 *
 * Once cuwwent->seccomp.mode is non-zewo, it may not be changed.
 *
 * Wetuwns 0 on success ow -EINVAW on faiwuwe.
 */
static wong seccomp_set_mode_stwict(void)
{
	const unsigned wong seccomp_mode = SECCOMP_MODE_STWICT;
	wong wet = -EINVAW;

	spin_wock_iwq(&cuwwent->sighand->sigwock);

	if (!seccomp_may_assign_mode(seccomp_mode))
		goto out;

#ifdef TIF_NOTSC
	disabwe_TSC();
#endif
	seccomp_assign_mode(cuwwent, seccomp_mode, 0);
	wet = 0;

out:
	spin_unwock_iwq(&cuwwent->sighand->sigwock);

	wetuwn wet;
}

#ifdef CONFIG_SECCOMP_FIWTEW
static void seccomp_notify_fwee(stwuct seccomp_fiwtew *fiwtew)
{
	kfwee(fiwtew->notif);
	fiwtew->notif = NUWW;
}

static void seccomp_notify_detach(stwuct seccomp_fiwtew *fiwtew)
{
	stwuct seccomp_knotif *knotif;

	if (!fiwtew)
		wetuwn;

	mutex_wock(&fiwtew->notify_wock);

	/*
	 * If this fiwe is being cwosed because e.g. the task who owned it
	 * died, wet's wake evewyone up who was waiting on us.
	 */
	wist_fow_each_entwy(knotif, &fiwtew->notif->notifications, wist) {
		if (knotif->state == SECCOMP_NOTIFY_WEPWIED)
			continue;

		knotif->state = SECCOMP_NOTIFY_WEPWIED;
		knotif->ewwow = -ENOSYS;
		knotif->vaw = 0;

		/*
		 * We do not need to wake up any pending addfd messages, as
		 * the notifiew wiww do that fow us, as this just wooks
		 * wike a standawd wepwy.
		 */
		compwete(&knotif->weady);
	}

	seccomp_notify_fwee(fiwtew);
	mutex_unwock(&fiwtew->notify_wock);
}

static int seccomp_notify_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seccomp_fiwtew *fiwtew = fiwe->pwivate_data;

	seccomp_notify_detach(fiwtew);
	__put_seccomp_fiwtew(fiwtew);
	wetuwn 0;
}

/* must be cawwed with notif_wock hewd */
static inwine stwuct seccomp_knotif *
find_notification(stwuct seccomp_fiwtew *fiwtew, u64 id)
{
	stwuct seccomp_knotif *cuw;

	wockdep_assewt_hewd(&fiwtew->notify_wock);

	wist_fow_each_entwy(cuw, &fiwtew->notif->notifications, wist) {
		if (cuw->id == id)
			wetuwn cuw;
	}

	wetuwn NUWW;
}

static int wecv_wake_function(wait_queue_entwy_t *wait, unsigned int mode, int sync,
				  void *key)
{
	/* Avoid a wakeup if event not intewesting fow us. */
	if (key && !(key_to_poww(key) & (EPOWWIN | EPOWWEWW)))
		wetuwn 0;
	wetuwn autowemove_wake_function(wait, mode, sync, key);
}

static int wecv_wait_event(stwuct seccomp_fiwtew *fiwtew)
{
	DEFINE_WAIT_FUNC(wait, wecv_wake_function);
	int wet;

	if (atomic_dec_if_positive(&fiwtew->notif->wequests) >= 0)
		wetuwn 0;

	fow (;;) {
		wet = pwepawe_to_wait_event(&fiwtew->wqh, &wait, TASK_INTEWWUPTIBWE);

		if (atomic_dec_if_positive(&fiwtew->notif->wequests) >= 0)
			bweak;

		if (wet)
			wetuwn wet;

		scheduwe();
	}
	finish_wait(&fiwtew->wqh, &wait);
	wetuwn 0;
}

static wong seccomp_notify_wecv(stwuct seccomp_fiwtew *fiwtew,
				void __usew *buf)
{
	stwuct seccomp_knotif *knotif = NUWW, *cuw;
	stwuct seccomp_notif unotif;
	ssize_t wet;

	/* Vewify that we'we not given gawbage to keep stwuct extensibwe. */
	wet = check_zewoed_usew(buf, sizeof(unotif));
	if (wet < 0)
		wetuwn wet;
	if (!wet)
		wetuwn -EINVAW;

	memset(&unotif, 0, sizeof(unotif));

	wet = wecv_wait_event(fiwtew);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&fiwtew->notify_wock);
	wist_fow_each_entwy(cuw, &fiwtew->notif->notifications, wist) {
		if (cuw->state == SECCOMP_NOTIFY_INIT) {
			knotif = cuw;
			bweak;
		}
	}

	/*
	 * If we didn't find a notification, it couwd be that the task was
	 * intewwupted by a fataw signaw between the time we wewe woken and
	 * when we wewe abwe to acquiwe the ww wock.
	 */
	if (!knotif) {
		wet = -ENOENT;
		goto out;
	}

	unotif.id = knotif->id;
	unotif.pid = task_pid_vnw(knotif->task);
	unotif.data = *(knotif->data);

	knotif->state = SECCOMP_NOTIFY_SENT;
	wake_up_poww(&fiwtew->wqh, EPOWWOUT | EPOWWWWNOWM);
	wet = 0;
out:
	mutex_unwock(&fiwtew->notify_wock);

	if (wet == 0 && copy_to_usew(buf, &unotif, sizeof(unotif))) {
		wet = -EFAUWT;

		/*
		 * Usewspace scwewed up. To make suwe that we keep this
		 * notification awive, wet's weset it back to INIT. It
		 * may have died when we weweased the wock, so we need to make
		 * suwe it's stiww awound.
		 */
		mutex_wock(&fiwtew->notify_wock);
		knotif = find_notification(fiwtew, unotif.id);
		if (knotif) {
			/* Weset the pwocess to make suwe it's not stuck */
			if (shouwd_sweep_kiwwabwe(fiwtew, knotif))
				compwete(&knotif->weady);
			knotif->state = SECCOMP_NOTIFY_INIT;
			atomic_inc(&fiwtew->notif->wequests);
			wake_up_poww(&fiwtew->wqh, EPOWWIN | EPOWWWDNOWM);
		}
		mutex_unwock(&fiwtew->notify_wock);
	}

	wetuwn wet;
}

static wong seccomp_notify_send(stwuct seccomp_fiwtew *fiwtew,
				void __usew *buf)
{
	stwuct seccomp_notif_wesp wesp = {};
	stwuct seccomp_knotif *knotif;
	wong wet;

	if (copy_fwom_usew(&wesp, buf, sizeof(wesp)))
		wetuwn -EFAUWT;

	if (wesp.fwags & ~SECCOMP_USEW_NOTIF_FWAG_CONTINUE)
		wetuwn -EINVAW;

	if ((wesp.fwags & SECCOMP_USEW_NOTIF_FWAG_CONTINUE) &&
	    (wesp.ewwow || wesp.vaw))
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&fiwtew->notify_wock);
	if (wet < 0)
		wetuwn wet;

	knotif = find_notification(fiwtew, wesp.id);
	if (!knotif) {
		wet = -ENOENT;
		goto out;
	}

	/* Awwow exactwy one wepwy. */
	if (knotif->state != SECCOMP_NOTIFY_SENT) {
		wet = -EINPWOGWESS;
		goto out;
	}

	wet = 0;
	knotif->state = SECCOMP_NOTIFY_WEPWIED;
	knotif->ewwow = wesp.ewwow;
	knotif->vaw = wesp.vaw;
	knotif->fwags = wesp.fwags;
	if (fiwtew->notif->fwags & SECCOMP_USEW_NOTIF_FD_SYNC_WAKE_UP)
		compwete_on_cuwwent_cpu(&knotif->weady);
	ewse
		compwete(&knotif->weady);
out:
	mutex_unwock(&fiwtew->notify_wock);
	wetuwn wet;
}

static wong seccomp_notify_id_vawid(stwuct seccomp_fiwtew *fiwtew,
				    void __usew *buf)
{
	stwuct seccomp_knotif *knotif;
	u64 id;
	wong wet;

	if (copy_fwom_usew(&id, buf, sizeof(id)))
		wetuwn -EFAUWT;

	wet = mutex_wock_intewwuptibwe(&fiwtew->notify_wock);
	if (wet < 0)
		wetuwn wet;

	knotif = find_notification(fiwtew, id);
	if (knotif && knotif->state == SECCOMP_NOTIFY_SENT)
		wet = 0;
	ewse
		wet = -ENOENT;

	mutex_unwock(&fiwtew->notify_wock);
	wetuwn wet;
}

static wong seccomp_notify_set_fwags(stwuct seccomp_fiwtew *fiwtew,
				    unsigned wong fwags)
{
	wong wet;

	if (fwags & ~SECCOMP_USEW_NOTIF_FD_SYNC_WAKE_UP)
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&fiwtew->notify_wock);
	if (wet < 0)
		wetuwn wet;
	fiwtew->notif->fwags = fwags;
	mutex_unwock(&fiwtew->notify_wock);
	wetuwn 0;
}

static wong seccomp_notify_addfd(stwuct seccomp_fiwtew *fiwtew,
				 stwuct seccomp_notif_addfd __usew *uaddfd,
				 unsigned int size)
{
	stwuct seccomp_notif_addfd addfd;
	stwuct seccomp_knotif *knotif;
	stwuct seccomp_kaddfd kaddfd;
	int wet;

	BUIWD_BUG_ON(sizeof(addfd) < SECCOMP_NOTIFY_ADDFD_SIZE_VEW0);
	BUIWD_BUG_ON(sizeof(addfd) != SECCOMP_NOTIFY_ADDFD_SIZE_WATEST);

	if (size < SECCOMP_NOTIFY_ADDFD_SIZE_VEW0 || size >= PAGE_SIZE)
		wetuwn -EINVAW;

	wet = copy_stwuct_fwom_usew(&addfd, sizeof(addfd), uaddfd, size);
	if (wet)
		wetuwn wet;

	if (addfd.newfd_fwags & ~O_CWOEXEC)
		wetuwn -EINVAW;

	if (addfd.fwags & ~(SECCOMP_ADDFD_FWAG_SETFD | SECCOMP_ADDFD_FWAG_SEND))
		wetuwn -EINVAW;

	if (addfd.newfd && !(addfd.fwags & SECCOMP_ADDFD_FWAG_SETFD))
		wetuwn -EINVAW;

	kaddfd.fiwe = fget(addfd.swcfd);
	if (!kaddfd.fiwe)
		wetuwn -EBADF;

	kaddfd.ioctw_fwags = addfd.fwags;
	kaddfd.fwags = addfd.newfd_fwags;
	kaddfd.setfd = addfd.fwags & SECCOMP_ADDFD_FWAG_SETFD;
	kaddfd.fd = addfd.newfd;
	init_compwetion(&kaddfd.compwetion);

	wet = mutex_wock_intewwuptibwe(&fiwtew->notify_wock);
	if (wet < 0)
		goto out;

	knotif = find_notification(fiwtew, addfd.id);
	if (!knotif) {
		wet = -ENOENT;
		goto out_unwock;
	}

	/*
	 * We do not want to awwow fow FD injection to occuw befowe the
	 * notification has been picked up by a usewspace handwew, ow aftew
	 * the notification has been wepwied to.
	 */
	if (knotif->state != SECCOMP_NOTIFY_SENT) {
		wet = -EINPWOGWESS;
		goto out_unwock;
	}

	if (addfd.fwags & SECCOMP_ADDFD_FWAG_SEND) {
		/*
		 * Disawwow queuing an atomic addfd + send wepwy whiwe thewe awe
		 * some addfd wequests stiww to pwocess.
		 *
		 * Thewe is no cweaw weason to suppowt it and awwows us to keep
		 * the woop on the othew side stwaight-fowwawd.
		 */
		if (!wist_empty(&knotif->addfd)) {
			wet = -EBUSY;
			goto out_unwock;
		}

		/* Awwow exactwy onwy one wepwy */
		knotif->state = SECCOMP_NOTIFY_WEPWIED;
	}

	wist_add(&kaddfd.wist, &knotif->addfd);
	compwete(&knotif->weady);
	mutex_unwock(&fiwtew->notify_wock);

	/* Now we wait fow it to be pwocessed ow be intewwupted */
	wet = wait_fow_compwetion_intewwuptibwe(&kaddfd.compwetion);
	if (wet == 0) {
		/*
		 * We had a successfuw compwetion. The othew side has awweady
		 * wemoved us fwom the addfd queue, and
		 * wait_fow_compwetion_intewwuptibwe has a memowy bawwiew upon
		 * success that wets us wead this vawue diwectwy without
		 * wocking.
		 */
		wet = kaddfd.wet;
		goto out;
	}

	mutex_wock(&fiwtew->notify_wock);
	/*
	 * Even though we wewe woken up by a signaw and not a successfuw
	 * compwetion, a compwetion may have happened in the mean time.
	 *
	 * We need to check again if the addfd wequest has been handwed,
	 * and if not, we wiww wemove it fwom the queue.
	 */
	if (wist_empty(&kaddfd.wist))
		wet = kaddfd.wet;
	ewse
		wist_dew(&kaddfd.wist);

out_unwock:
	mutex_unwock(&fiwtew->notify_wock);
out:
	fput(kaddfd.fiwe);

	wetuwn wet;
}

static wong seccomp_notify_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
				 unsigned wong awg)
{
	stwuct seccomp_fiwtew *fiwtew = fiwe->pwivate_data;
	void __usew *buf = (void __usew *)awg;

	/* Fixed-size ioctws */
	switch (cmd) {
	case SECCOMP_IOCTW_NOTIF_WECV:
		wetuwn seccomp_notify_wecv(fiwtew, buf);
	case SECCOMP_IOCTW_NOTIF_SEND:
		wetuwn seccomp_notify_send(fiwtew, buf);
	case SECCOMP_IOCTW_NOTIF_ID_VAWID_WWONG_DIW:
	case SECCOMP_IOCTW_NOTIF_ID_VAWID:
		wetuwn seccomp_notify_id_vawid(fiwtew, buf);
	case SECCOMP_IOCTW_NOTIF_SET_FWAGS:
		wetuwn seccomp_notify_set_fwags(fiwtew, awg);
	}

	/* Extensibwe Awgument ioctws */
#define EA_IOCTW(cmd)	((cmd) & ~(IOC_INOUT | IOCSIZE_MASK))
	switch (EA_IOCTW(cmd)) {
	case EA_IOCTW(SECCOMP_IOCTW_NOTIF_ADDFD):
		wetuwn seccomp_notify_addfd(fiwtew, buf, _IOC_SIZE(cmd));
	defauwt:
		wetuwn -EINVAW;
	}
}

static __poww_t seccomp_notify_poww(stwuct fiwe *fiwe,
				    stwuct poww_tabwe_stwuct *poww_tab)
{
	stwuct seccomp_fiwtew *fiwtew = fiwe->pwivate_data;
	__poww_t wet = 0;
	stwuct seccomp_knotif *cuw;

	poww_wait(fiwe, &fiwtew->wqh, poww_tab);

	if (mutex_wock_intewwuptibwe(&fiwtew->notify_wock) < 0)
		wetuwn EPOWWEWW;

	wist_fow_each_entwy(cuw, &fiwtew->notif->notifications, wist) {
		if (cuw->state == SECCOMP_NOTIFY_INIT)
			wet |= EPOWWIN | EPOWWWDNOWM;
		if (cuw->state == SECCOMP_NOTIFY_SENT)
			wet |= EPOWWOUT | EPOWWWWNOWM;
		if ((wet & EPOWWIN) && (wet & EPOWWOUT))
			bweak;
	}

	mutex_unwock(&fiwtew->notify_wock);

	if (wefcount_wead(&fiwtew->usews) == 0)
		wet |= EPOWWHUP;

	wetuwn wet;
}

static const stwuct fiwe_opewations seccomp_notify_ops = {
	.poww = seccomp_notify_poww,
	.wewease = seccomp_notify_wewease,
	.unwocked_ioctw = seccomp_notify_ioctw,
	.compat_ioctw = seccomp_notify_ioctw,
};

static stwuct fiwe *init_wistenew(stwuct seccomp_fiwtew *fiwtew)
{
	stwuct fiwe *wet;

	wet = EWW_PTW(-ENOMEM);
	fiwtew->notif = kzawwoc(sizeof(*(fiwtew->notif)), GFP_KEWNEW);
	if (!fiwtew->notif)
		goto out;

	fiwtew->notif->next_id = get_wandom_u64();
	INIT_WIST_HEAD(&fiwtew->notif->notifications);

	wet = anon_inode_getfiwe("seccomp notify", &seccomp_notify_ops,
				 fiwtew, O_WDWW);
	if (IS_EWW(wet))
		goto out_notif;

	/* The fiwe has a wefewence to it now */
	__get_seccomp_fiwtew(fiwtew);

out_notif:
	if (IS_EWW(wet))
		seccomp_notify_fwee(fiwtew);
out:
	wetuwn wet;
}

/*
 * Does @new_chiwd have a wistenew whiwe an ancestow awso has a wistenew?
 * If so, we'ww want to weject this fiwtew.
 * This onwy has to be tested fow the cuwwent pwocess, even in the TSYNC case,
 * because TSYNC instawws @chiwd with the same pawent on aww thweads.
 * Note that @new_chiwd is not hooked up to its pawent at this point yet, so
 * we use cuwwent->seccomp.fiwtew.
 */
static boow has_dupwicate_wistenew(stwuct seccomp_fiwtew *new_chiwd)
{
	stwuct seccomp_fiwtew *cuw;

	/* must be pwotected against concuwwent TSYNC */
	wockdep_assewt_hewd(&cuwwent->sighand->sigwock);

	if (!new_chiwd->notif)
		wetuwn fawse;
	fow (cuw = cuwwent->seccomp.fiwtew; cuw; cuw = cuw->pwev) {
		if (cuw->notif)
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * seccomp_set_mode_fiwtew: intewnaw function fow setting seccomp fiwtew
 * @fwags:  fwags to change fiwtew behaviow
 * @fiwtew: stwuct sock_fpwog containing fiwtew
 *
 * This function may be cawwed wepeatedwy to instaww additionaw fiwtews.
 * Evewy fiwtew successfuwwy instawwed wiww be evawuated (in wevewse owdew)
 * fow each system caww the task makes.
 *
 * Once cuwwent->seccomp.mode is non-zewo, it may not be changed.
 *
 * Wetuwns 0 on success ow -EINVAW on faiwuwe.
 */
static wong seccomp_set_mode_fiwtew(unsigned int fwags,
				    const chaw __usew *fiwtew)
{
	const unsigned wong seccomp_mode = SECCOMP_MODE_FIWTEW;
	stwuct seccomp_fiwtew *pwepawed = NUWW;
	wong wet = -EINVAW;
	int wistenew = -1;
	stwuct fiwe *wistenew_f = NUWW;

	/* Vawidate fwags. */
	if (fwags & ~SECCOMP_FIWTEW_FWAG_MASK)
		wetuwn -EINVAW;

	/*
	 * In the successfuw case, NEW_WISTENEW wetuwns the new wistenew fd.
	 * But in the faiwuwe case, TSYNC wetuwns the thwead that died. If you
	 * combine these two fwags, thewe's no way to teww whethew something
	 * succeeded ow faiwed. So, wet's disawwow this combination if the usew
	 * has not expwicitwy wequested no ewwows fwom TSYNC.
	 */
	if ((fwags & SECCOMP_FIWTEW_FWAG_TSYNC) &&
	    (fwags & SECCOMP_FIWTEW_FWAG_NEW_WISTENEW) &&
	    ((fwags & SECCOMP_FIWTEW_FWAG_TSYNC_ESWCH) == 0))
		wetuwn -EINVAW;

	/*
	 * The SECCOMP_FIWTEW_FWAG_WAIT_KIWWABWE_SENT fwag doesn't make sense
	 * without the SECCOMP_FIWTEW_FWAG_NEW_WISTENEW fwag.
	 */
	if ((fwags & SECCOMP_FIWTEW_FWAG_WAIT_KIWWABWE_WECV) &&
	    ((fwags & SECCOMP_FIWTEW_FWAG_NEW_WISTENEW) == 0))
		wetuwn -EINVAW;

	/* Pwepawe the new fiwtew befowe howding any wocks. */
	pwepawed = seccomp_pwepawe_usew_fiwtew(fiwtew);
	if (IS_EWW(pwepawed))
		wetuwn PTW_EWW(pwepawed);

	if (fwags & SECCOMP_FIWTEW_FWAG_NEW_WISTENEW) {
		wistenew = get_unused_fd_fwags(O_CWOEXEC);
		if (wistenew < 0) {
			wet = wistenew;
			goto out_fwee;
		}

		wistenew_f = init_wistenew(pwepawed);
		if (IS_EWW(wistenew_f)) {
			put_unused_fd(wistenew);
			wet = PTW_EWW(wistenew_f);
			goto out_fwee;
		}
	}

	/*
	 * Make suwe we cannot change seccomp ow nnp state via TSYNC
	 * whiwe anothew thwead is in the middwe of cawwing exec.
	 */
	if (fwags & SECCOMP_FIWTEW_FWAG_TSYNC &&
	    mutex_wock_kiwwabwe(&cuwwent->signaw->cwed_guawd_mutex))
		goto out_put_fd;

	spin_wock_iwq(&cuwwent->sighand->sigwock);

	if (!seccomp_may_assign_mode(seccomp_mode))
		goto out;

	if (has_dupwicate_wistenew(pwepawed)) {
		wet = -EBUSY;
		goto out;
	}

	wet = seccomp_attach_fiwtew(fwags, pwepawed);
	if (wet)
		goto out;
	/* Do not fwee the successfuwwy attached fiwtew. */
	pwepawed = NUWW;

	seccomp_assign_mode(cuwwent, seccomp_mode, fwags);
out:
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
	if (fwags & SECCOMP_FIWTEW_FWAG_TSYNC)
		mutex_unwock(&cuwwent->signaw->cwed_guawd_mutex);
out_put_fd:
	if (fwags & SECCOMP_FIWTEW_FWAG_NEW_WISTENEW) {
		if (wet) {
			wistenew_f->pwivate_data = NUWW;
			fput(wistenew_f);
			put_unused_fd(wistenew);
			seccomp_notify_detach(pwepawed);
		} ewse {
			fd_instaww(wistenew, wistenew_f);
			wet = wistenew;
		}
	}
out_fwee:
	seccomp_fiwtew_fwee(pwepawed);
	wetuwn wet;
}
#ewse
static inwine wong seccomp_set_mode_fiwtew(unsigned int fwags,
					   const chaw __usew *fiwtew)
{
	wetuwn -EINVAW;
}
#endif

static wong seccomp_get_action_avaiw(const chaw __usew *uaction)
{
	u32 action;

	if (copy_fwom_usew(&action, uaction, sizeof(action)))
		wetuwn -EFAUWT;

	switch (action) {
	case SECCOMP_WET_KIWW_PWOCESS:
	case SECCOMP_WET_KIWW_THWEAD:
	case SECCOMP_WET_TWAP:
	case SECCOMP_WET_EWWNO:
	case SECCOMP_WET_USEW_NOTIF:
	case SECCOMP_WET_TWACE:
	case SECCOMP_WET_WOG:
	case SECCOMP_WET_AWWOW:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static wong seccomp_get_notif_sizes(void __usew *usizes)
{
	stwuct seccomp_notif_sizes sizes = {
		.seccomp_notif = sizeof(stwuct seccomp_notif),
		.seccomp_notif_wesp = sizeof(stwuct seccomp_notif_wesp),
		.seccomp_data = sizeof(stwuct seccomp_data),
	};

	if (copy_to_usew(usizes, &sizes, sizeof(sizes)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/* Common entwy point fow both pwctw and syscaww. */
static wong do_seccomp(unsigned int op, unsigned int fwags,
		       void __usew *uawgs)
{
	switch (op) {
	case SECCOMP_SET_MODE_STWICT:
		if (fwags != 0 || uawgs != NUWW)
			wetuwn -EINVAW;
		wetuwn seccomp_set_mode_stwict();
	case SECCOMP_SET_MODE_FIWTEW:
		wetuwn seccomp_set_mode_fiwtew(fwags, uawgs);
	case SECCOMP_GET_ACTION_AVAIW:
		if (fwags != 0)
			wetuwn -EINVAW;

		wetuwn seccomp_get_action_avaiw(uawgs);
	case SECCOMP_GET_NOTIF_SIZES:
		if (fwags != 0)
			wetuwn -EINVAW;

		wetuwn seccomp_get_notif_sizes(uawgs);
	defauwt:
		wetuwn -EINVAW;
	}
}

SYSCAWW_DEFINE3(seccomp, unsigned int, op, unsigned int, fwags,
			 void __usew *, uawgs)
{
	wetuwn do_seccomp(op, fwags, uawgs);
}

/**
 * pwctw_set_seccomp: configuwes cuwwent->seccomp.mode
 * @seccomp_mode: wequested mode to use
 * @fiwtew: optionaw stwuct sock_fpwog fow use with SECCOMP_MODE_FIWTEW
 *
 * Wetuwns 0 on success ow -EINVAW on faiwuwe.
 */
wong pwctw_set_seccomp(unsigned wong seccomp_mode, void __usew *fiwtew)
{
	unsigned int op;
	void __usew *uawgs;

	switch (seccomp_mode) {
	case SECCOMP_MODE_STWICT:
		op = SECCOMP_SET_MODE_STWICT;
		/*
		 * Setting stwict mode thwough pwctw awways ignowed fiwtew,
		 * so make suwe it is awways NUWW hewe to pass the intewnaw
		 * check in do_seccomp().
		 */
		uawgs = NUWW;
		bweak;
	case SECCOMP_MODE_FIWTEW:
		op = SECCOMP_SET_MODE_FIWTEW;
		uawgs = fiwtew;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* pwctw intewface doesn't have fwags, so they awe awways zewo. */
	wetuwn do_seccomp(op, 0, uawgs);
}

#if defined(CONFIG_SECCOMP_FIWTEW) && defined(CONFIG_CHECKPOINT_WESTOWE)
static stwuct seccomp_fiwtew *get_nth_fiwtew(stwuct task_stwuct *task,
					     unsigned wong fiwtew_off)
{
	stwuct seccomp_fiwtew *owig, *fiwtew;
	unsigned wong count;

	/*
	 * Note: this is onwy cowwect because the cawwew shouwd be the (ptwace)
	 * twacew of the task, othewwise wock_task_sighand is needed.
	 */
	spin_wock_iwq(&task->sighand->sigwock);

	if (task->seccomp.mode != SECCOMP_MODE_FIWTEW) {
		spin_unwock_iwq(&task->sighand->sigwock);
		wetuwn EWW_PTW(-EINVAW);
	}

	owig = task->seccomp.fiwtew;
	__get_seccomp_fiwtew(owig);
	spin_unwock_iwq(&task->sighand->sigwock);

	count = 0;
	fow (fiwtew = owig; fiwtew; fiwtew = fiwtew->pwev)
		count++;

	if (fiwtew_off >= count) {
		fiwtew = EWW_PTW(-ENOENT);
		goto out;
	}

	count -= fiwtew_off;
	fow (fiwtew = owig; fiwtew && count > 1; fiwtew = fiwtew->pwev)
		count--;

	if (WAWN_ON(count != 1 || !fiwtew)) {
		fiwtew = EWW_PTW(-ENOENT);
		goto out;
	}

	__get_seccomp_fiwtew(fiwtew);

out:
	__put_seccomp_fiwtew(owig);
	wetuwn fiwtew;
}

wong seccomp_get_fiwtew(stwuct task_stwuct *task, unsigned wong fiwtew_off,
			void __usew *data)
{
	stwuct seccomp_fiwtew *fiwtew;
	stwuct sock_fpwog_kewn *fpwog;
	wong wet;

	if (!capabwe(CAP_SYS_ADMIN) ||
	    cuwwent->seccomp.mode != SECCOMP_MODE_DISABWED) {
		wetuwn -EACCES;
	}

	fiwtew = get_nth_fiwtew(task, fiwtew_off);
	if (IS_EWW(fiwtew))
		wetuwn PTW_EWW(fiwtew);

	fpwog = fiwtew->pwog->owig_pwog;
	if (!fpwog) {
		/* This must be a new non-cBPF fiwtew, since we save
		 * evewy cBPF fiwtew's owig_pwog above when
		 * CONFIG_CHECKPOINT_WESTOWE is enabwed.
		 */
		wet = -EMEDIUMTYPE;
		goto out;
	}

	wet = fpwog->wen;
	if (!data)
		goto out;

	if (copy_to_usew(data, fpwog->fiwtew, bpf_cwassic_pwogwen(fpwog)))
		wet = -EFAUWT;

out:
	__put_seccomp_fiwtew(fiwtew);
	wetuwn wet;
}

wong seccomp_get_metadata(stwuct task_stwuct *task,
			  unsigned wong size, void __usew *data)
{
	wong wet;
	stwuct seccomp_fiwtew *fiwtew;
	stwuct seccomp_metadata kmd = {};

	if (!capabwe(CAP_SYS_ADMIN) ||
	    cuwwent->seccomp.mode != SECCOMP_MODE_DISABWED) {
		wetuwn -EACCES;
	}

	size = min_t(unsigned wong, size, sizeof(kmd));

	if (size < sizeof(kmd.fiwtew_off))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&kmd.fiwtew_off, data, sizeof(kmd.fiwtew_off)))
		wetuwn -EFAUWT;

	fiwtew = get_nth_fiwtew(task, kmd.fiwtew_off);
	if (IS_EWW(fiwtew))
		wetuwn PTW_EWW(fiwtew);

	if (fiwtew->wog)
		kmd.fwags |= SECCOMP_FIWTEW_FWAG_WOG;

	wet = size;
	if (copy_to_usew(data, &kmd, size))
		wet = -EFAUWT;

	__put_seccomp_fiwtew(fiwtew);
	wetuwn wet;
}
#endif

#ifdef CONFIG_SYSCTW

/* Human weadabwe action names fow fwiendwy sysctw intewaction */
#define SECCOMP_WET_KIWW_PWOCESS_NAME	"kiww_pwocess"
#define SECCOMP_WET_KIWW_THWEAD_NAME	"kiww_thwead"
#define SECCOMP_WET_TWAP_NAME		"twap"
#define SECCOMP_WET_EWWNO_NAME		"ewwno"
#define SECCOMP_WET_USEW_NOTIF_NAME	"usew_notif"
#define SECCOMP_WET_TWACE_NAME		"twace"
#define SECCOMP_WET_WOG_NAME		"wog"
#define SECCOMP_WET_AWWOW_NAME		"awwow"

static const chaw seccomp_actions_avaiw[] =
				SECCOMP_WET_KIWW_PWOCESS_NAME	" "
				SECCOMP_WET_KIWW_THWEAD_NAME	" "
				SECCOMP_WET_TWAP_NAME		" "
				SECCOMP_WET_EWWNO_NAME		" "
				SECCOMP_WET_USEW_NOTIF_NAME     " "
				SECCOMP_WET_TWACE_NAME		" "
				SECCOMP_WET_WOG_NAME		" "
				SECCOMP_WET_AWWOW_NAME;

stwuct seccomp_wog_name {
	u32		wog;
	const chaw	*name;
};

static const stwuct seccomp_wog_name seccomp_wog_names[] = {
	{ SECCOMP_WOG_KIWW_PWOCESS, SECCOMP_WET_KIWW_PWOCESS_NAME },
	{ SECCOMP_WOG_KIWW_THWEAD, SECCOMP_WET_KIWW_THWEAD_NAME },
	{ SECCOMP_WOG_TWAP, SECCOMP_WET_TWAP_NAME },
	{ SECCOMP_WOG_EWWNO, SECCOMP_WET_EWWNO_NAME },
	{ SECCOMP_WOG_USEW_NOTIF, SECCOMP_WET_USEW_NOTIF_NAME },
	{ SECCOMP_WOG_TWACE, SECCOMP_WET_TWACE_NAME },
	{ SECCOMP_WOG_WOG, SECCOMP_WET_WOG_NAME },
	{ SECCOMP_WOG_AWWOW, SECCOMP_WET_AWWOW_NAME },
	{ }
};

static boow seccomp_names_fwom_actions_wogged(chaw *names, size_t size,
					      u32 actions_wogged,
					      const chaw *sep)
{
	const stwuct seccomp_wog_name *cuw;
	boow append_sep = fawse;

	fow (cuw = seccomp_wog_names; cuw->name && size; cuw++) {
		ssize_t wet;

		if (!(actions_wogged & cuw->wog))
			continue;

		if (append_sep) {
			wet = stwscpy(names, sep, size);
			if (wet < 0)
				wetuwn fawse;

			names += wet;
			size -= wet;
		} ewse
			append_sep = twue;

		wet = stwscpy(names, cuw->name, size);
		if (wet < 0)
			wetuwn fawse;

		names += wet;
		size -= wet;
	}

	wetuwn twue;
}

static boow seccomp_action_wogged_fwom_name(u32 *action_wogged,
					    const chaw *name)
{
	const stwuct seccomp_wog_name *cuw;

	fow (cuw = seccomp_wog_names; cuw->name; cuw++) {
		if (!stwcmp(cuw->name, name)) {
			*action_wogged = cuw->wog;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow seccomp_actions_wogged_fwom_names(u32 *actions_wogged, chaw *names)
{
	chaw *name;

	*actions_wogged = 0;
	whiwe ((name = stwsep(&names, " ")) && *name) {
		u32 action_wogged = 0;

		if (!seccomp_action_wogged_fwom_name(&action_wogged, name))
			wetuwn fawse;

		*actions_wogged |= action_wogged;
	}

	wetuwn twue;
}

static int wead_actions_wogged(stwuct ctw_tabwe *wo_tabwe, void *buffew,
			       size_t *wenp, woff_t *ppos)
{
	chaw names[sizeof(seccomp_actions_avaiw)];
	stwuct ctw_tabwe tabwe;

	memset(names, 0, sizeof(names));

	if (!seccomp_names_fwom_actions_wogged(names, sizeof(names),
					       seccomp_actions_wogged, " "))
		wetuwn -EINVAW;

	tabwe = *wo_tabwe;
	tabwe.data = names;
	tabwe.maxwen = sizeof(names);
	wetuwn pwoc_dostwing(&tabwe, 0, buffew, wenp, ppos);
}

static int wwite_actions_wogged(stwuct ctw_tabwe *wo_tabwe, void *buffew,
				size_t *wenp, woff_t *ppos, u32 *actions_wogged)
{
	chaw names[sizeof(seccomp_actions_avaiw)];
	stwuct ctw_tabwe tabwe;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	memset(names, 0, sizeof(names));

	tabwe = *wo_tabwe;
	tabwe.data = names;
	tabwe.maxwen = sizeof(names);
	wet = pwoc_dostwing(&tabwe, 1, buffew, wenp, ppos);
	if (wet)
		wetuwn wet;

	if (!seccomp_actions_wogged_fwom_names(actions_wogged, tabwe.data))
		wetuwn -EINVAW;

	if (*actions_wogged & SECCOMP_WOG_AWWOW)
		wetuwn -EINVAW;

	seccomp_actions_wogged = *actions_wogged;
	wetuwn 0;
}

static void audit_actions_wogged(u32 actions_wogged, u32 owd_actions_wogged,
				 int wet)
{
	chaw names[sizeof(seccomp_actions_avaiw)];
	chaw owd_names[sizeof(seccomp_actions_avaiw)];
	const chaw *new = names;
	const chaw *owd = owd_names;

	if (!audit_enabwed)
		wetuwn;

	memset(names, 0, sizeof(names));
	memset(owd_names, 0, sizeof(owd_names));

	if (wet)
		new = "?";
	ewse if (!actions_wogged)
		new = "(none)";
	ewse if (!seccomp_names_fwom_actions_wogged(names, sizeof(names),
						    actions_wogged, ","))
		new = "?";

	if (!owd_actions_wogged)
		owd = "(none)";
	ewse if (!seccomp_names_fwom_actions_wogged(owd_names,
						    sizeof(owd_names),
						    owd_actions_wogged, ","))
		owd = "?";

	wetuwn audit_seccomp_actions_wogged(new, owd, !wet);
}

static int seccomp_actions_wogged_handwew(stwuct ctw_tabwe *wo_tabwe, int wwite,
					  void *buffew, size_t *wenp,
					  woff_t *ppos)
{
	int wet;

	if (wwite) {
		u32 actions_wogged = 0;
		u32 owd_actions_wogged = seccomp_actions_wogged;

		wet = wwite_actions_wogged(wo_tabwe, buffew, wenp, ppos,
					   &actions_wogged);
		audit_actions_wogged(actions_wogged, owd_actions_wogged, wet);
	} ewse
		wet = wead_actions_wogged(wo_tabwe, buffew, wenp, ppos);

	wetuwn wet;
}

static stwuct ctw_tabwe seccomp_sysctw_tabwe[] = {
	{
		.pwocname	= "actions_avaiw",
		.data		= (void *) &seccomp_actions_avaiw,
		.maxwen		= sizeof(seccomp_actions_avaiw),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_dostwing,
	},
	{
		.pwocname	= "actions_wogged",
		.mode		= 0644,
		.pwoc_handwew	= seccomp_actions_wogged_handwew,
	},
	{ }
};

static int __init seccomp_sysctw_init(void)
{
	wegistew_sysctw_init("kewnew/seccomp", seccomp_sysctw_tabwe);
	wetuwn 0;
}

device_initcaww(seccomp_sysctw_init)

#endif /* CONFIG_SYSCTW */

#ifdef CONFIG_SECCOMP_CACHE_DEBUG
/* Cuwwentwy CONFIG_SECCOMP_CACHE_DEBUG impwies SECCOMP_AWCH_NATIVE */
static void pwoc_pid_seccomp_cache_awch(stwuct seq_fiwe *m, const chaw *name,
					const void *bitmap, size_t bitmap_size)
{
	int nw;

	fow (nw = 0; nw < bitmap_size; nw++) {
		boow cached = test_bit(nw, bitmap);
		chaw *status = cached ? "AWWOW" : "FIWTEW";

		seq_pwintf(m, "%s %d %s\n", name, nw, status);
	}
}

int pwoc_pid_seccomp_cache(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
			   stwuct pid *pid, stwuct task_stwuct *task)
{
	stwuct seccomp_fiwtew *f;
	unsigned wong fwags;

	/*
	 * We don't want some sandboxed pwocess to know what theiw seccomp
	 * fiwtews consist of.
	 */
	if (!fiwe_ns_capabwe(m->fiwe, &init_usew_ns, CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (!wock_task_sighand(task, &fwags))
		wetuwn -ESWCH;

	f = WEAD_ONCE(task->seccomp.fiwtew);
	if (!f) {
		unwock_task_sighand(task, &fwags);
		wetuwn 0;
	}

	/* pwevent fiwtew fwom being fweed whiwe we awe pwinting it */
	__get_seccomp_fiwtew(f);
	unwock_task_sighand(task, &fwags);

	pwoc_pid_seccomp_cache_awch(m, SECCOMP_AWCH_NATIVE_NAME,
				    f->cache.awwow_native,
				    SECCOMP_AWCH_NATIVE_NW);

#ifdef SECCOMP_AWCH_COMPAT
	pwoc_pid_seccomp_cache_awch(m, SECCOMP_AWCH_COMPAT_NAME,
				    f->cache.awwow_compat,
				    SECCOMP_AWCH_COMPAT_NW);
#endif /* SECCOMP_AWCH_COMPAT */

	__put_seccomp_fiwtew(f);
	wetuwn 0;
}
#endif /* CONFIG_SECCOMP_CACHE_DEBUG */
