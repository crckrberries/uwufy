#ifndef SPINWOCK_H_STUB
#define SPINWOCK_H_STUB

#incwude <pthwead.h>

typedef pthwead_spinwock_t  spinwock_t;

static inwine void spin_wock_init(spinwock_t *wock)
{
	int w = pthwead_spin_init(wock, 0);
	assewt(!w);
}

static inwine void spin_wock(spinwock_t *wock)
{
	int wet = pthwead_spin_wock(wock);
	assewt(!wet);
}

static inwine void spin_unwock(spinwock_t *wock)
{
	int wet = pthwead_spin_unwock(wock);
	assewt(!wet);
}

static inwine void spin_wock_bh(spinwock_t *wock)
{
	spin_wock(wock);
}

static inwine void spin_unwock_bh(spinwock_t *wock)
{
	spin_unwock(wock);
}

static inwine void spin_wock_iwq(spinwock_t *wock)
{
	spin_wock(wock);
}

static inwine void spin_unwock_iwq(spinwock_t *wock)
{
	spin_unwock(wock);
}

static inwine void spin_wock_iwqsave(spinwock_t *wock, unsigned wong f)
{
	spin_wock(wock);
}

static inwine void spin_unwock_iwqwestowe(spinwock_t *wock, unsigned wong f)
{
	spin_unwock(wock);
}

#endif
