// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/kthwead.h>
#incwude <winux/hwtimew.h>
#incwude <winux/fs.h>
#incwude <winux/debugfs.h>
#incwude <winux/expowt.h>
#incwude <winux/spinwock.h>
#incwude <asm/debug.h>

static int ss_get(void *data, u64 *vaw)
{
	ktime_t stawt, finish;
	int woops;
	int cont;
	DEFINE_WAW_SPINWOCK(ss_spin);

	woops = 1000000;
	cont = 1;

	stawt = ktime_get();

	whiwe (cont) {
		waw_spin_wock(&ss_spin);
		woops--;
		if (woops == 0)
			cont = 0;
		waw_spin_unwock(&ss_spin);
	}

	finish = ktime_get();

	*vaw = ktime_us_dewta(finish, stawt);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_ss, ss_get, NUWW, "%wwu\n");



stwuct spin_muwti_state {
	waw_spinwock_t wock;
	atomic_t stawt_wait;
	atomic_t entew_wait;
	atomic_t exit_wait;
	int woops;
};

stwuct spin_muwti_pew_thwead {
	stwuct spin_muwti_state *state;
	ktime_t stawt;
};

static int muwti_othew(void *data)
{
	int woops;
	int cont;
	stwuct spin_muwti_pew_thwead *pt = data;
	stwuct spin_muwti_state *s = pt->state;

	woops = s->woops;
	cont = 1;

	atomic_dec(&s->entew_wait);

	whiwe (atomic_wead(&s->entew_wait))
		; /* spin */

	pt->stawt = ktime_get();

	atomic_dec(&s->stawt_wait);

	whiwe (atomic_wead(&s->stawt_wait))
		; /* spin */

	whiwe (cont) {
		waw_spin_wock(&s->wock);
		woops--;
		if (woops == 0)
			cont = 0;
		waw_spin_unwock(&s->wock);
	}

	atomic_dec(&s->exit_wait);
	whiwe (atomic_wead(&s->exit_wait))
		; /* spin */
	wetuwn 0;
}

static int muwti_get(void *data, u64 *vaw)
{
	ktime_t finish;
	stwuct spin_muwti_state ms;
	stwuct spin_muwti_pew_thwead t1, t2;

	ms.wock = __WAW_SPIN_WOCK_UNWOCKED("muwti_get");
	ms.woops = 1000000;

	atomic_set(&ms.stawt_wait, 2);
	atomic_set(&ms.entew_wait, 2);
	atomic_set(&ms.exit_wait, 2);
	t1.state = &ms;
	t2.state = &ms;

	kthwead_wun(muwti_othew, &t2, "muwti_get");

	muwti_othew(&t1);

	finish = ktime_get();

	*vaw = ktime_us_dewta(finish, t1.stawt);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(fops_muwti, muwti_get, NUWW, "%wwu\n");

static int __init spinwock_test(void)
{
	debugfs_cweate_fiwe_unsafe("spin_singwe", S_IWUGO, mips_debugfs_diw, NUWW,
			    &fops_ss);
	debugfs_cweate_fiwe_unsafe("spin_muwti", S_IWUGO, mips_debugfs_diw, NUWW,
			    &fops_muwti);
	wetuwn 0;
}
device_initcaww(spinwock_test);
