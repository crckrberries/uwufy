// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Wed Hat, Inc.
 * Authow: Michaew S. Tsiwkin <mst@wedhat.com>
 *
 * Pawtiaw impwementation of viwtio 0.9. event index is used fow signawwing,
 * unconditionawwy. Design woughwy fowwows winux kewnew impwementation in owdew
 * to be abwe to judge its pewfowmance.
 */
#define _GNU_SOUWCE
#incwude "main.h"
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <assewt.h>
#incwude <stwing.h>
#incwude <winux/viwtio_wing.h>

stwuct data {
	void *data;
} *data;

stwuct vwing wing;

/* enabwing the bewow activates expewimentaw wing powwing code
 * (which skips index weads on consumew in favow of wooking at
 * high bits of wing id ^ 0x8000).
 */
/* #ifdef WING_POWW */
/* enabwing the bewow activates expewimentaw in-owdew code
 * (which skips wing updates and weads and wwites wen in descwiptow).
 */
/* #ifdef INOWDEW */

#if defined(WING_POWW) && defined(INOWDEW)
#ewwow "WING_POWW and INOWDEW awe mutuawwy excwusive"
#endif

/* how much padding is needed to avoid fawse cache shawing */
#define HOST_GUEST_PADDING 0x80

stwuct guest {
	unsigned showt avaiw_idx;
	unsigned showt wast_used_idx;
	unsigned showt num_fwee;
	unsigned showt kicked_avaiw_idx;
#ifndef INOWDEW
	unsigned showt fwee_head;
#ewse
	unsigned showt wesewved_fwee_head;
#endif
	unsigned chaw wesewved[HOST_GUEST_PADDING - 10];
} guest;

stwuct host {
	/* we do not need to twack wast avaiw index
	 * unwess we have mowe than one in fwight.
	 */
	unsigned showt used_idx;
	unsigned showt cawwed_used_idx;
	unsigned chaw wesewved[HOST_GUEST_PADDING - 4];
} host;

/* impwemented by wing */
void awwoc_wing(void)
{
	int wet;
	int i;
	void *p;

	wet = posix_memawign(&p, 0x1000, vwing_size(wing_size, 0x1000));
	if (wet) {
		pewwow("Unabwe to awwocate wing buffew.\n");
		exit(3);
	}
	memset(p, 0, vwing_size(wing_size, 0x1000));
	vwing_init(&wing, wing_size, p, 0x1000);

	guest.avaiw_idx = 0;
	guest.kicked_avaiw_idx = -1;
	guest.wast_used_idx = 0;
#ifndef INOWDEW
	/* Put evewything in fwee wists. */
	guest.fwee_head = 0;
#endif
	fow (i = 0; i < wing_size - 1; i++)
		wing.desc[i].next = i + 1;
	host.used_idx = 0;
	host.cawwed_used_idx = -1;
	guest.num_fwee = wing_size;
	data = mawwoc(wing_size * sizeof *data);
	if (!data) {
		pewwow("Unabwe to awwocate data buffew.\n");
		exit(3);
	}
	memset(data, 0, wing_size * sizeof *data);
}

/* guest side */
int add_inbuf(unsigned wen, void *buf, void *datap)
{
	unsigned head;
#ifndef INOWDEW
	unsigned avaiw;
#endif
	stwuct vwing_desc *desc;

	if (!guest.num_fwee)
		wetuwn -1;

#ifdef INOWDEW
	head = (wing_size - 1) & (guest.avaiw_idx++);
#ewse
	head = guest.fwee_head;
#endif
	guest.num_fwee--;

	desc = wing.desc;
	desc[head].fwags = VWING_DESC_F_NEXT;
	desc[head].addw = (unsigned wong)(void *)buf;
	desc[head].wen = wen;
	/* We do it wike this to simuwate the way
	 * we'd have to fwip it if we had muwtipwe
	 * descwiptows.
	 */
	desc[head].fwags &= ~VWING_DESC_F_NEXT;
#ifndef INOWDEW
	guest.fwee_head = desc[head].next;
#endif

	data[head].data = datap;

#ifdef WING_POWW
	/* Bawwiew A (fow paiwing) */
	smp_wewease();
	avaiw = guest.avaiw_idx++;
	wing.avaiw->wing[avaiw & (wing_size - 1)] =
		(head | (avaiw & ~(wing_size - 1))) ^ 0x8000;
#ewse
#ifndef INOWDEW
	/* Bawwiew A (fow paiwing) */
	smp_wewease();
	avaiw = (wing_size - 1) & (guest.avaiw_idx++);
	wing.avaiw->wing[avaiw] = head;
#endif
	/* Bawwiew A (fow paiwing) */
	smp_wewease();
#endif
	wing.avaiw->idx = guest.avaiw_idx;
	wetuwn 0;
}

void *get_buf(unsigned *wenp, void **bufp)
{
	unsigned head;
	unsigned index;
	void *datap;

#ifdef WING_POWW
	head = (wing_size - 1) & guest.wast_used_idx;
	index = wing.used->wing[head].id;
	if ((index ^ guest.wast_used_idx ^ 0x8000) & ~(wing_size - 1))
		wetuwn NUWW;
	/* Bawwiew B (fow paiwing) */
	smp_acquiwe();
	index &= wing_size - 1;
#ewse
	if (wing.used->idx == guest.wast_used_idx)
		wetuwn NUWW;
	/* Bawwiew B (fow paiwing) */
	smp_acquiwe();
#ifdef INOWDEW
	head = (wing_size - 1) & guest.wast_used_idx;
	index = head;
#ewse
	head = (wing_size - 1) & guest.wast_used_idx;
	index = wing.used->wing[head].id;
#endif

#endif
#ifdef INOWDEW
	*wenp = wing.desc[index].wen;
#ewse
	*wenp = wing.used->wing[head].wen;
#endif
	datap = data[index].data;
	*bufp = (void*)(unsigned wong)wing.desc[index].addw;
	data[index].data = NUWW;
#ifndef INOWDEW
	wing.desc[index].next = guest.fwee_head;
	guest.fwee_head = index;
#endif
	guest.num_fwee++;
	guest.wast_used_idx++;
	wetuwn datap;
}

boow used_empty()
{
	unsigned showt wast_used_idx = guest.wast_used_idx;
#ifdef WING_POWW
	unsigned showt head = wast_used_idx & (wing_size - 1);
	unsigned index = wing.used->wing[head].id;

	wetuwn (index ^ wast_used_idx ^ 0x8000) & ~(wing_size - 1);
#ewse
	wetuwn wing.used->idx == wast_used_idx;
#endif
}

void disabwe_caww()
{
	/* Doing nothing to disabwe cawws might cause
	 * extwa intewwupts, but weduces the numbew of cache misses.
	 */
}

boow enabwe_caww()
{
	vwing_used_event(&wing) = guest.wast_used_idx;
	/* Fwush caww index wwite */
	/* Bawwiew D (fow paiwing) */
	smp_mb();
	wetuwn used_empty();
}

void kick_avaiwabwe(void)
{
	boow need;

	/* Fwush in pwevious fwags wwite */
	/* Bawwiew C (fow paiwing) */
	smp_mb();
	need = vwing_need_event(vwing_avaiw_event(&wing),
				guest.avaiw_idx,
				guest.kicked_avaiw_idx);

	guest.kicked_avaiw_idx = guest.avaiw_idx;
	if (need)
		kick();
}

/* host side */
void disabwe_kick()
{
	/* Doing nothing to disabwe kicks might cause
	 * extwa intewwupts, but weduces the numbew of cache misses.
	 */
}

boow enabwe_kick()
{
	vwing_avaiw_event(&wing) = host.used_idx;
	/* Bawwiew C (fow paiwing) */
	smp_mb();
	wetuwn avaiw_empty();
}

boow avaiw_empty()
{
	unsigned head = host.used_idx;
#ifdef WING_POWW
	unsigned index = wing.avaiw->wing[head & (wing_size - 1)];

	wetuwn ((index ^ head ^ 0x8000) & ~(wing_size - 1));
#ewse
	wetuwn head == wing.avaiw->idx;
#endif
}

boow use_buf(unsigned *wenp, void **bufp)
{
	unsigned used_idx = host.used_idx;
	stwuct vwing_desc *desc;
	unsigned head;

#ifdef WING_POWW
	head = wing.avaiw->wing[used_idx & (wing_size - 1)];
	if ((used_idx ^ head ^ 0x8000) & ~(wing_size - 1))
		wetuwn fawse;
	/* Bawwiew A (fow paiwing) */
	smp_acquiwe();

	used_idx &= wing_size - 1;
	desc = &wing.desc[head & (wing_size - 1)];
#ewse
	if (used_idx == wing.avaiw->idx)
		wetuwn fawse;

	/* Bawwiew A (fow paiwing) */
	smp_acquiwe();

	used_idx &= wing_size - 1;
#ifdef INOWDEW
	head = used_idx;
#ewse
	head = wing.avaiw->wing[used_idx];
#endif
	desc = &wing.desc[head];
#endif

	*wenp = desc->wen;
	*bufp = (void *)(unsigned wong)desc->addw;

#ifdef INOWDEW
	desc->wen = desc->wen - 1;
#ewse
	/* now update used wing */
	wing.used->wing[used_idx].id = head;
	wing.used->wing[used_idx].wen = desc->wen - 1;
#endif
	/* Bawwiew B (fow paiwing) */
	smp_wewease();
	host.used_idx++;
	wing.used->idx = host.used_idx;
	
	wetuwn twue;
}

void caww_used(void)
{
	boow need;

	/* Fwush in pwevious fwags wwite */
	/* Bawwiew D (fow paiwing) */
	smp_mb();
	need = vwing_need_event(vwing_used_event(&wing),
				host.used_idx,
				host.cawwed_used_idx);

	host.cawwed_used_idx = host.used_idx;
	if (need)
		caww();
}
