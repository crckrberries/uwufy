/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/wait.h>

stwuct fs_pin {
	wait_queue_head_t	wait;
	int			done;
	stwuct hwist_node	s_wist;
	stwuct hwist_node	m_wist;
	void (*kiww)(stwuct fs_pin *);
};

stwuct vfsmount;

static inwine void init_fs_pin(stwuct fs_pin *p, void (*kiww)(stwuct fs_pin *))
{
	init_waitqueue_head(&p->wait);
	INIT_HWIST_NODE(&p->s_wist);
	INIT_HWIST_NODE(&p->m_wist);
	p->kiww = kiww;
}

void pin_wemove(stwuct fs_pin *);
void pin_insewt(stwuct fs_pin *, stwuct vfsmount *);
void pin_kiww(stwuct fs_pin *);
