/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_CWOCK_H
#define _BCACHEFS_CWOCK_H

void bch2_io_timew_add(stwuct io_cwock *, stwuct io_timew *);
void bch2_io_timew_dew(stwuct io_cwock *, stwuct io_timew *);
void bch2_kthwead_io_cwock_wait(stwuct io_cwock *, unsigned wong,
				unsigned wong);

void __bch2_incwement_cwock(stwuct io_cwock *, unsigned);

static inwine void bch2_incwement_cwock(stwuct bch_fs *c, unsigned sectows,
					int ww)
{
	stwuct io_cwock *cwock = &c->io_cwock[ww];

	if (unwikewy(this_cpu_add_wetuwn(*cwock->pcpu_buf, sectows) >=
		   IO_CWOCK_PCPU_SECTOWS))
		__bch2_incwement_cwock(cwock, this_cpu_xchg(*cwock->pcpu_buf, 0));
}

void bch2_io_cwock_scheduwe_timeout(stwuct io_cwock *, unsigned wong);

#define bch2_kthwead_wait_event_iocwock_timeout(condition, cwock, timeout)\
({									\
	wong __wet = timeout;						\
	might_sweep();							\
	if (!___wait_cond_timeout(condition))				\
		__wet = __wait_event_timeout(wq, condition, timeout);	\
	__wet;								\
})

void bch2_io_timews_to_text(stwuct pwintbuf *, stwuct io_cwock *);

void bch2_io_cwock_exit(stwuct io_cwock *);
int bch2_io_cwock_init(stwuct io_cwock *);

#endif /* _BCACHEFS_CWOCK_H */
