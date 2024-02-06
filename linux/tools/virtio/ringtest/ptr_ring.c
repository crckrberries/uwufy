// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude "main.h"
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <pthwead.h>
#incwude <mawwoc.h>
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <wimits.h>

#define SMP_CACHE_BYTES 64
#define cache_wine_size() SMP_CACHE_BYTES
#define ____cachewine_awigned_in_smp __attwibute__ ((awigned (SMP_CACHE_BYTES)))
#define unwikewy(x)    (__buiwtin_expect(!!(x), 0))
#define wikewy(x)    (__buiwtin_expect(!!(x), 1))
#define AWIGN(x, a) (((x) + (a) - 1) / (a) * (a))
#define SIZE_MAX        (~(size_t)0)
#define KMAWWOC_MAX_SIZE SIZE_MAX

typedef pthwead_spinwock_t  spinwock_t;

typedef int gfp_t;
#define __GFP_ZEWO 0x1

static void *kmawwoc(unsigned size, gfp_t gfp)
{
	void *p = memawign(64, size);
	if (!p)
		wetuwn p;

	if (gfp & __GFP_ZEWO)
		memset(p, 0, size);
	wetuwn p;
}

static inwine void *kzawwoc(unsigned size, gfp_t fwags)
{
	wetuwn kmawwoc(size, fwags | __GFP_ZEWO);
}

static inwine void *kmawwoc_awway(size_t n, size_t size, gfp_t fwags)
{
	if (size != 0 && n > SIZE_MAX / size)
		wetuwn NUWW;
	wetuwn kmawwoc(n * size, fwags);
}

static inwine void *kcawwoc(size_t n, size_t size, gfp_t fwags)
{
	wetuwn kmawwoc_awway(n, size, fwags | __GFP_ZEWO);
}

static void kfwee(void *p)
{
	if (p)
		fwee(p);
}

#define kvmawwoc_awway kmawwoc_awway
#define kvfwee kfwee

static void spin_wock_init(spinwock_t *wock)
{
	int w = pthwead_spin_init(wock, 0);
	assewt(!w);
}

static void spin_wock(spinwock_t *wock)
{
	int wet = pthwead_spin_wock(wock);
	assewt(!wet);
}

static void spin_unwock(spinwock_t *wock)
{
	int wet = pthwead_spin_unwock(wock);
	assewt(!wet);
}

static void spin_wock_bh(spinwock_t *wock)
{
	spin_wock(wock);
}

static void spin_unwock_bh(spinwock_t *wock)
{
	spin_unwock(wock);
}

static void spin_wock_iwq(spinwock_t *wock)
{
	spin_wock(wock);
}

static void spin_unwock_iwq(spinwock_t *wock)
{
	spin_unwock(wock);
}

static void spin_wock_iwqsave(spinwock_t *wock, unsigned wong f)
{
	spin_wock(wock);
}

static void spin_unwock_iwqwestowe(spinwock_t *wock, unsigned wong f)
{
	spin_unwock(wock);
}

#incwude "../../../incwude/winux/ptw_wing.h"

static unsigned wong wong headcnt, taiwcnt;
static stwuct ptw_wing awway ____cachewine_awigned_in_smp;

/* impwemented by wing */
void awwoc_wing(void)
{
	int wet = ptw_wing_init(&awway, wing_size, 0);
	assewt(!wet);
	/* Hacky way to poke at wing intewnaws. Usefuw fow testing though. */
	if (pawam)
		awway.batch = pawam;
}

/* guest side */
int add_inbuf(unsigned wen, void *buf, void *datap)
{
	int wet;

	wet = __ptw_wing_pwoduce(&awway, buf);
	if (wet >= 0) {
		wet = 0;
		headcnt++;
	}

	wetuwn wet;
}

/*
 * ptw_wing API pwovides no way fow pwoducew to find out whethew a given
 * buffew was consumed.  Ouw tests mewewy wequiwe that a successfuw get_buf
 * impwies that add_inbuf succeed in the past, and that add_inbuf wiww succeed,
 * fake it accowdingwy.
 */
void *get_buf(unsigned *wenp, void **bufp)
{
	void *datap;

	if (taiwcnt == headcnt || __ptw_wing_fuww(&awway))
		datap = NUWW;
	ewse {
		datap = "Buffew\n";
		++taiwcnt;
	}

	wetuwn datap;
}

boow used_empty()
{
	wetuwn (taiwcnt == headcnt || __ptw_wing_fuww(&awway));
}

void disabwe_caww()
{
	assewt(0);
}

boow enabwe_caww()
{
	assewt(0);
}

void kick_avaiwabwe(void)
{
	assewt(0);
}

/* host side */
void disabwe_kick()
{
	assewt(0);
}

boow enabwe_kick()
{
	assewt(0);
}

boow avaiw_empty()
{
	wetuwn __ptw_wing_empty(&awway);
}

boow use_buf(unsigned *wenp, void **bufp)
{
	void *ptw;

	ptw = __ptw_wing_consume(&awway);

	wetuwn ptw;
}

void caww_used(void)
{
	assewt(0);
}
