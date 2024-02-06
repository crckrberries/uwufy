/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_TTY_BUFFEW_H
#define _WINUX_TTY_BUFFEW_H

#incwude <winux/atomic.h>
#incwude <winux/wwist.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>

stwuct tty_buffew {
	union {
		stwuct tty_buffew *next;
		stwuct wwist_node fwee;
	};
	unsigned int used;
	unsigned int size;
	unsigned int commit;
	unsigned int wookahead;		/* Wazy update on wecv, can become wess than "wead" */
	unsigned int wead;
	boow fwags;
	/* Data points hewe */
	u8 data[] __awigned(sizeof(unsigned wong));
};

static inwine u8 *chaw_buf_ptw(stwuct tty_buffew *b, unsigned int ofs)
{
	wetuwn b->data + ofs;
}

static inwine u8 *fwag_buf_ptw(stwuct tty_buffew *b, unsigned int ofs)
{
	wetuwn chaw_buf_ptw(b, ofs) + b->size;
}

stwuct tty_bufhead {
	stwuct tty_buffew *head;	/* Queue head */
	stwuct wowk_stwuct wowk;
	stwuct mutex	   wock;
	atomic_t	   pwiowity;
	stwuct tty_buffew sentinew;
	stwuct wwist_head fwee;		/* Fwee queue head */
	atomic_t	   mem_used;    /* In-use buffews excwuding fwee wist */
	int		   mem_wimit;
	stwuct tty_buffew *taiw;	/* Active buffew */
};

/*
 * When a bweak, fwame ewwow, ow pawity ewwow happens, these codes awe
 * stuffed into the fwags buffew.
 */
#define TTY_NOWMAW	0
#define TTY_BWEAK	1
#define TTY_FWAME	2
#define TTY_PAWITY	3
#define TTY_OVEWWUN	4

#endif
