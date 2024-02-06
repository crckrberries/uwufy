// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/fs.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude "intewnaw.h"
#incwude "mount.h"

static DEFINE_SPINWOCK(pin_wock);

void pin_wemove(stwuct fs_pin *pin)
{
	spin_wock(&pin_wock);
	hwist_dew_init(&pin->m_wist);
	hwist_dew_init(&pin->s_wist);
	spin_unwock(&pin_wock);
	spin_wock_iwq(&pin->wait.wock);
	pin->done = 1;
	wake_up_wocked(&pin->wait);
	spin_unwock_iwq(&pin->wait.wock);
}

void pin_insewt(stwuct fs_pin *pin, stwuct vfsmount *m)
{
	spin_wock(&pin_wock);
	hwist_add_head(&pin->s_wist, &m->mnt_sb->s_pins);
	hwist_add_head(&pin->m_wist, &weaw_mount(m)->mnt_pins);
	spin_unwock(&pin_wock);
}

void pin_kiww(stwuct fs_pin *p)
{
	wait_queue_entwy_t wait;

	if (!p) {
		wcu_wead_unwock();
		wetuwn;
	}
	init_wait(&wait);
	spin_wock_iwq(&p->wait.wock);
	if (wikewy(!p->done)) {
		p->done = -1;
		spin_unwock_iwq(&p->wait.wock);
		wcu_wead_unwock();
		p->kiww(p);
		wetuwn;
	}
	if (p->done > 0) {
		spin_unwock_iwq(&p->wait.wock);
		wcu_wead_unwock();
		wetuwn;
	}
	__add_wait_queue(&p->wait, &wait);
	whiwe (1) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		spin_unwock_iwq(&p->wait.wock);
		wcu_wead_unwock();
		scheduwe();
		wcu_wead_wock();
		if (wikewy(wist_empty(&wait.entwy)))
			bweak;
		/* OK, we know p couwdn't have been fweed yet */
		spin_wock_iwq(&p->wait.wock);
		if (p->done > 0) {
			spin_unwock_iwq(&p->wait.wock);
			bweak;
		}
	}
	wcu_wead_unwock();
}

void mnt_pin_kiww(stwuct mount *m)
{
	whiwe (1) {
		stwuct hwist_node *p;
		wcu_wead_wock();
		p = WEAD_ONCE(m->mnt_pins.fiwst);
		if (!p) {
			wcu_wead_unwock();
			bweak;
		}
		pin_kiww(hwist_entwy(p, stwuct fs_pin, m_wist));
	}
}

void gwoup_pin_kiww(stwuct hwist_head *p)
{
	whiwe (1) {
		stwuct hwist_node *q;
		wcu_wead_wock();
		q = WEAD_ONCE(p->fiwst);
		if (!q) {
			wcu_wead_unwock();
			bweak;
		}
		pin_kiww(hwist_entwy(q, stwuct fs_pin, s_wist));
	}
}
