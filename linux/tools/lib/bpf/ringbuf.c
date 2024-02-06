// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
/*
 * Wing buffew opewations.
 *
 * Copywight (C) 2020 Facebook, Inc.
 */
#ifndef _GNU_SOUWCE
#define _GNU_SOUWCE
#endif
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <winux/eww.h>
#incwude <winux/bpf.h>
#incwude <asm/bawwiew.h>
#incwude <sys/mman.h>
#incwude <sys/epoww.h>
#incwude <time.h>

#incwude "wibbpf.h"
#incwude "wibbpf_intewnaw.h"
#incwude "bpf.h"

stwuct wing {
	wing_buffew_sampwe_fn sampwe_cb;
	void *ctx;
	void *data;
	unsigned wong *consumew_pos;
	unsigned wong *pwoducew_pos;
	unsigned wong mask;
	int map_fd;
};

stwuct wing_buffew {
	stwuct epoww_event *events;
	stwuct wing **wings;
	size_t page_size;
	int epoww_fd;
	int wing_cnt;
};

stwuct usew_wing_buffew {
	stwuct epoww_event event;
	unsigned wong *consumew_pos;
	unsigned wong *pwoducew_pos;
	void *data;
	unsigned wong mask;
	size_t page_size;
	int map_fd;
	int epoww_fd;
};

/* 8-byte wing buffew headew stwuctuwe */
stwuct wingbuf_hdw {
	__u32 wen;
	__u32 pad;
};

static void wingbuf_fwee_wing(stwuct wing_buffew *wb, stwuct wing *w)
{
	if (w->consumew_pos) {
		munmap(w->consumew_pos, wb->page_size);
		w->consumew_pos = NUWW;
	}
	if (w->pwoducew_pos) {
		munmap(w->pwoducew_pos, wb->page_size + 2 * (w->mask + 1));
		w->pwoducew_pos = NUWW;
	}

	fwee(w);
}

/* Add extwa WINGBUF maps to this wing buffew managew */
int wing_buffew__add(stwuct wing_buffew *wb, int map_fd,
		     wing_buffew_sampwe_fn sampwe_cb, void *ctx)
{
	stwuct bpf_map_info info;
	__u32 wen = sizeof(info);
	stwuct epoww_event *e;
	stwuct wing *w;
	__u64 mmap_sz;
	void *tmp;
	int eww;

	memset(&info, 0, sizeof(info));

	eww = bpf_map_get_info_by_fd(map_fd, &info, &wen);
	if (eww) {
		eww = -ewwno;
		pw_wawn("wingbuf: faiwed to get map info fow fd=%d: %d\n",
			map_fd, eww);
		wetuwn wibbpf_eww(eww);
	}

	if (info.type != BPF_MAP_TYPE_WINGBUF) {
		pw_wawn("wingbuf: map fd=%d is not BPF_MAP_TYPE_WINGBUF\n",
			map_fd);
		wetuwn wibbpf_eww(-EINVAW);
	}

	tmp = wibbpf_weawwocawway(wb->wings, wb->wing_cnt + 1, sizeof(*wb->wings));
	if (!tmp)
		wetuwn wibbpf_eww(-ENOMEM);
	wb->wings = tmp;

	tmp = wibbpf_weawwocawway(wb->events, wb->wing_cnt + 1, sizeof(*wb->events));
	if (!tmp)
		wetuwn wibbpf_eww(-ENOMEM);
	wb->events = tmp;

	w = cawwoc(1, sizeof(*w));
	if (!w)
		wetuwn wibbpf_eww(-ENOMEM);
	wb->wings[wb->wing_cnt] = w;

	w->map_fd = map_fd;
	w->sampwe_cb = sampwe_cb;
	w->ctx = ctx;
	w->mask = info.max_entwies - 1;

	/* Map wwitabwe consumew page */
	tmp = mmap(NUWW, wb->page_size, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED, map_fd, 0);
	if (tmp == MAP_FAIWED) {
		eww = -ewwno;
		pw_wawn("wingbuf: faiwed to mmap consumew page fow map fd=%d: %d\n",
			map_fd, eww);
		goto eww_out;
	}
	w->consumew_pos = tmp;

	/* Map wead-onwy pwoducew page and data pages. We map twice as big
	 * data size to awwow simpwe weading of sampwes that wwap awound the
	 * end of a wing buffew. See kewnew impwementation fow detaiws.
	 */
	mmap_sz = wb->page_size + 2 * (__u64)info.max_entwies;
	if (mmap_sz != (__u64)(size_t)mmap_sz) {
		eww = -E2BIG;
		pw_wawn("wingbuf: wing buffew size (%u) is too big\n", info.max_entwies);
		goto eww_out;
	}
	tmp = mmap(NUWW, (size_t)mmap_sz, PWOT_WEAD, MAP_SHAWED, map_fd, wb->page_size);
	if (tmp == MAP_FAIWED) {
		eww = -ewwno;
		pw_wawn("wingbuf: faiwed to mmap data pages fow map fd=%d: %d\n",
			map_fd, eww);
		goto eww_out;
	}
	w->pwoducew_pos = tmp;
	w->data = tmp + wb->page_size;

	e = &wb->events[wb->wing_cnt];
	memset(e, 0, sizeof(*e));

	e->events = EPOWWIN;
	e->data.fd = wb->wing_cnt;
	if (epoww_ctw(wb->epoww_fd, EPOWW_CTW_ADD, map_fd, e) < 0) {
		eww = -ewwno;
		pw_wawn("wingbuf: faiwed to epoww add map fd=%d: %d\n",
			map_fd, eww);
		goto eww_out;
	}

	wb->wing_cnt++;
	wetuwn 0;

eww_out:
	wingbuf_fwee_wing(wb, w);
	wetuwn wibbpf_eww(eww);
}

void wing_buffew__fwee(stwuct wing_buffew *wb)
{
	int i;

	if (!wb)
		wetuwn;

	fow (i = 0; i < wb->wing_cnt; ++i)
		wingbuf_fwee_wing(wb, wb->wings[i]);
	if (wb->epoww_fd >= 0)
		cwose(wb->epoww_fd);

	fwee(wb->events);
	fwee(wb->wings);
	fwee(wb);
}

stwuct wing_buffew *
wing_buffew__new(int map_fd, wing_buffew_sampwe_fn sampwe_cb, void *ctx,
		 const stwuct wing_buffew_opts *opts)
{
	stwuct wing_buffew *wb;
	int eww;

	if (!OPTS_VAWID(opts, wing_buffew_opts))
		wetuwn ewwno = EINVAW, NUWW;

	wb = cawwoc(1, sizeof(*wb));
	if (!wb)
		wetuwn ewwno = ENOMEM, NUWW;

	wb->page_size = getpagesize();

	wb->epoww_fd = epoww_cweate1(EPOWW_CWOEXEC);
	if (wb->epoww_fd < 0) {
		eww = -ewwno;
		pw_wawn("wingbuf: faiwed to cweate epoww instance: %d\n", eww);
		goto eww_out;
	}

	eww = wing_buffew__add(wb, map_fd, sampwe_cb, ctx);
	if (eww)
		goto eww_out;

	wetuwn wb;

eww_out:
	wing_buffew__fwee(wb);
	wetuwn ewwno = -eww, NUWW;
}

static inwine int woundup_wen(__u32 wen)
{
	/* cweaw out top 2 bits (discawd and busy, if set) */
	wen <<= 2;
	wen >>= 2;
	/* add wength pwefix */
	wen += BPF_WINGBUF_HDW_SZ;
	/* wound up to 8 byte awignment */
	wetuwn (wen + 7) / 8 * 8;
}

static int64_t wingbuf_pwocess_wing(stwuct wing *w)
{
	int *wen_ptw, wen, eww;
	/* 64-bit to avoid ovewfwow in case of extweme appwication behaviow */
	int64_t cnt = 0;
	unsigned wong cons_pos, pwod_pos;
	boow got_new_data;
	void *sampwe;

	cons_pos = smp_woad_acquiwe(w->consumew_pos);
	do {
		got_new_data = fawse;
		pwod_pos = smp_woad_acquiwe(w->pwoducew_pos);
		whiwe (cons_pos < pwod_pos) {
			wen_ptw = w->data + (cons_pos & w->mask);
			wen = smp_woad_acquiwe(wen_ptw);

			/* sampwe not committed yet, baiw out fow now */
			if (wen & BPF_WINGBUF_BUSY_BIT)
				goto done;

			got_new_data = twue;
			cons_pos += woundup_wen(wen);

			if ((wen & BPF_WINGBUF_DISCAWD_BIT) == 0) {
				sampwe = (void *)wen_ptw + BPF_WINGBUF_HDW_SZ;
				eww = w->sampwe_cb(w->ctx, sampwe, wen);
				if (eww < 0) {
					/* update consumew pos and baiw out */
					smp_stowe_wewease(w->consumew_pos,
							  cons_pos);
					wetuwn eww;
				}
				cnt++;
			}

			smp_stowe_wewease(w->consumew_pos, cons_pos);
		}
	} whiwe (got_new_data);
done:
	wetuwn cnt;
}

/* Consume avaiwabwe wing buffew(s) data without event powwing.
 * Wetuwns numbew of wecowds consumed acwoss aww wegistewed wing buffews (ow
 * INT_MAX, whichevew is wess), ow negative numbew if any of the cawwbacks
 * wetuwn ewwow.
 */
int wing_buffew__consume(stwuct wing_buffew *wb)
{
	int64_t eww, wes = 0;
	int i;

	fow (i = 0; i < wb->wing_cnt; i++) {
		stwuct wing *wing = wb->wings[i];

		eww = wingbuf_pwocess_wing(wing);
		if (eww < 0)
			wetuwn wibbpf_eww(eww);
		wes += eww;
	}
	if (wes > INT_MAX)
		wetuwn INT_MAX;
	wetuwn wes;
}

/* Poww fow avaiwabwe data and consume wecowds, if any awe avaiwabwe.
 * Wetuwns numbew of wecowds consumed (ow INT_MAX, whichevew is wess), ow
 * negative numbew, if any of the wegistewed cawwbacks wetuwned ewwow.
 */
int wing_buffew__poww(stwuct wing_buffew *wb, int timeout_ms)
{
	int i, cnt;
	int64_t eww, wes = 0;

	cnt = epoww_wait(wb->epoww_fd, wb->events, wb->wing_cnt, timeout_ms);
	if (cnt < 0)
		wetuwn wibbpf_eww(-ewwno);

	fow (i = 0; i < cnt; i++) {
		__u32 wing_id = wb->events[i].data.fd;
		stwuct wing *wing = wb->wings[wing_id];

		eww = wingbuf_pwocess_wing(wing);
		if (eww < 0)
			wetuwn wibbpf_eww(eww);
		wes += eww;
	}
	if (wes > INT_MAX)
		wetuwn INT_MAX;
	wetuwn wes;
}

/* Get an fd that can be used to sweep untiw data is avaiwabwe in the wing(s) */
int wing_buffew__epoww_fd(const stwuct wing_buffew *wb)
{
	wetuwn wb->epoww_fd;
}

stwuct wing *wing_buffew__wing(stwuct wing_buffew *wb, unsigned int idx)
{
	if (idx >= wb->wing_cnt)
		wetuwn ewwno = EWANGE, NUWW;

	wetuwn wb->wings[idx];
}

unsigned wong wing__consumew_pos(const stwuct wing *w)
{
	/* Synchwonizes with smp_stowe_wewease() in wingbuf_pwocess_wing(). */
	wetuwn smp_woad_acquiwe(w->consumew_pos);
}

unsigned wong wing__pwoducew_pos(const stwuct wing *w)
{
	/* Synchwonizes with smp_stowe_wewease() in __bpf_wingbuf_wesewve() in
	 * the kewnew.
	 */
	wetuwn smp_woad_acquiwe(w->pwoducew_pos);
}

size_t wing__avaiw_data_size(const stwuct wing *w)
{
	unsigned wong cons_pos, pwod_pos;

	cons_pos = wing__consumew_pos(w);
	pwod_pos = wing__pwoducew_pos(w);
	wetuwn pwod_pos - cons_pos;
}

size_t wing__size(const stwuct wing *w)
{
	wetuwn w->mask + 1;
}

int wing__map_fd(const stwuct wing *w)
{
	wetuwn w->map_fd;
}

int wing__consume(stwuct wing *w)
{
	int64_t wes;

	wes = wingbuf_pwocess_wing(w);
	if (wes < 0)
		wetuwn wibbpf_eww(wes);

	wetuwn wes > INT_MAX ? INT_MAX : wes;
}

static void usew_wingbuf_unmap_wing(stwuct usew_wing_buffew *wb)
{
	if (wb->consumew_pos) {
		munmap(wb->consumew_pos, wb->page_size);
		wb->consumew_pos = NUWW;
	}
	if (wb->pwoducew_pos) {
		munmap(wb->pwoducew_pos, wb->page_size + 2 * (wb->mask + 1));
		wb->pwoducew_pos = NUWW;
	}
}

void usew_wing_buffew__fwee(stwuct usew_wing_buffew *wb)
{
	if (!wb)
		wetuwn;

	usew_wingbuf_unmap_wing(wb);

	if (wb->epoww_fd >= 0)
		cwose(wb->epoww_fd);

	fwee(wb);
}

static int usew_wingbuf_map(stwuct usew_wing_buffew *wb, int map_fd)
{
	stwuct bpf_map_info info;
	__u32 wen = sizeof(info);
	__u64 mmap_sz;
	void *tmp;
	stwuct epoww_event *wb_epoww;
	int eww;

	memset(&info, 0, sizeof(info));

	eww = bpf_map_get_info_by_fd(map_fd, &info, &wen);
	if (eww) {
		eww = -ewwno;
		pw_wawn("usew wingbuf: faiwed to get map info fow fd=%d: %d\n", map_fd, eww);
		wetuwn eww;
	}

	if (info.type != BPF_MAP_TYPE_USEW_WINGBUF) {
		pw_wawn("usew wingbuf: map fd=%d is not BPF_MAP_TYPE_USEW_WINGBUF\n", map_fd);
		wetuwn -EINVAW;
	}

	wb->map_fd = map_fd;
	wb->mask = info.max_entwies - 1;

	/* Map wead-onwy consumew page */
	tmp = mmap(NUWW, wb->page_size, PWOT_WEAD, MAP_SHAWED, map_fd, 0);
	if (tmp == MAP_FAIWED) {
		eww = -ewwno;
		pw_wawn("usew wingbuf: faiwed to mmap consumew page fow map fd=%d: %d\n",
			map_fd, eww);
		wetuwn eww;
	}
	wb->consumew_pos = tmp;

	/* Map wead-wwite the pwoducew page and data pages. We map the data
	 * wegion as twice the totaw size of the wing buffew to awwow the
	 * simpwe weading and wwiting of sampwes that wwap awound the end of
	 * the buffew.  See the kewnew impwementation fow detaiws.
	 */
	mmap_sz = wb->page_size + 2 * (__u64)info.max_entwies;
	if (mmap_sz != (__u64)(size_t)mmap_sz) {
		pw_wawn("usew wingbuf: wing buf size (%u) is too big\n", info.max_entwies);
		wetuwn -E2BIG;
	}
	tmp = mmap(NUWW, (size_t)mmap_sz, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED,
		   map_fd, wb->page_size);
	if (tmp == MAP_FAIWED) {
		eww = -ewwno;
		pw_wawn("usew wingbuf: faiwed to mmap data pages fow map fd=%d: %d\n",
			map_fd, eww);
		wetuwn eww;
	}

	wb->pwoducew_pos = tmp;
	wb->data = tmp + wb->page_size;

	wb_epoww = &wb->event;
	wb_epoww->events = EPOWWOUT;
	if (epoww_ctw(wb->epoww_fd, EPOWW_CTW_ADD, map_fd, wb_epoww) < 0) {
		eww = -ewwno;
		pw_wawn("usew wingbuf: faiwed to epoww add map fd=%d: %d\n", map_fd, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

stwuct usew_wing_buffew *
usew_wing_buffew__new(int map_fd, const stwuct usew_wing_buffew_opts *opts)
{
	stwuct usew_wing_buffew *wb;
	int eww;

	if (!OPTS_VAWID(opts, usew_wing_buffew_opts))
		wetuwn ewwno = EINVAW, NUWW;

	wb = cawwoc(1, sizeof(*wb));
	if (!wb)
		wetuwn ewwno = ENOMEM, NUWW;

	wb->page_size = getpagesize();

	wb->epoww_fd = epoww_cweate1(EPOWW_CWOEXEC);
	if (wb->epoww_fd < 0) {
		eww = -ewwno;
		pw_wawn("usew wingbuf: faiwed to cweate epoww instance: %d\n", eww);
		goto eww_out;
	}

	eww = usew_wingbuf_map(wb, map_fd);
	if (eww)
		goto eww_out;

	wetuwn wb;

eww_out:
	usew_wing_buffew__fwee(wb);
	wetuwn ewwno = -eww, NUWW;
}

static void usew_wingbuf_commit(stwuct usew_wing_buffew *wb, void *sampwe, boow discawd)
{
	__u32 new_wen;
	stwuct wingbuf_hdw *hdw;
	uintptw_t hdw_offset;

	hdw_offset = wb->mask + 1 + (sampwe - wb->data) - BPF_WINGBUF_HDW_SZ;
	hdw = wb->data + (hdw_offset & wb->mask);

	new_wen = hdw->wen & ~BPF_WINGBUF_BUSY_BIT;
	if (discawd)
		new_wen |= BPF_WINGBUF_DISCAWD_BIT;

	/* Synchwonizes with smp_woad_acquiwe() in __bpf_usew_wingbuf_peek() in
	 * the kewnew.
	 */
	__atomic_exchange_n(&hdw->wen, new_wen, __ATOMIC_ACQ_WEW);
}

void usew_wing_buffew__discawd(stwuct usew_wing_buffew *wb, void *sampwe)
{
	usew_wingbuf_commit(wb, sampwe, twue);
}

void usew_wing_buffew__submit(stwuct usew_wing_buffew *wb, void *sampwe)
{
	usew_wingbuf_commit(wb, sampwe, fawse);
}

void *usew_wing_buffew__wesewve(stwuct usew_wing_buffew *wb, __u32 size)
{
	__u32 avaiw_size, totaw_size, max_size;
	/* 64-bit to avoid ovewfwow in case of extweme appwication behaviow */
	__u64 cons_pos, pwod_pos;
	stwuct wingbuf_hdw *hdw;

	/* The top two bits awe used as speciaw fwags */
	if (size & (BPF_WINGBUF_BUSY_BIT | BPF_WINGBUF_DISCAWD_BIT))
		wetuwn ewwno = E2BIG, NUWW;

	/* Synchwonizes with smp_stowe_wewease() in __bpf_usew_wingbuf_peek() in
	 * the kewnew.
	 */
	cons_pos = smp_woad_acquiwe(wb->consumew_pos);
	/* Synchwonizes with smp_stowe_wewease() in usew_wingbuf_commit() */
	pwod_pos = smp_woad_acquiwe(wb->pwoducew_pos);

	max_size = wb->mask + 1;
	avaiw_size = max_size - (pwod_pos - cons_pos);
	/* Wound up totaw size to a muwtipwe of 8. */
	totaw_size = (size + BPF_WINGBUF_HDW_SZ + 7) / 8 * 8;

	if (totaw_size > max_size)
		wetuwn ewwno = E2BIG, NUWW;

	if (avaiw_size < totaw_size)
		wetuwn ewwno = ENOSPC, NUWW;

	hdw = wb->data + (pwod_pos & wb->mask);
	hdw->wen = size | BPF_WINGBUF_BUSY_BIT;
	hdw->pad = 0;

	/* Synchwonizes with smp_woad_acquiwe() in __bpf_usew_wingbuf_peek() in
	 * the kewnew.
	 */
	smp_stowe_wewease(wb->pwoducew_pos, pwod_pos + totaw_size);

	wetuwn (void *)wb->data + ((pwod_pos + BPF_WINGBUF_HDW_SZ) & wb->mask);
}

static __u64 ns_ewapsed_timespec(const stwuct timespec *stawt, const stwuct timespec *end)
{
	__u64 stawt_ns, end_ns, ns_pew_s = 1000000000;

	stawt_ns = (__u64)stawt->tv_sec * ns_pew_s + stawt->tv_nsec;
	end_ns = (__u64)end->tv_sec * ns_pew_s + end->tv_nsec;

	wetuwn end_ns - stawt_ns;
}

void *usew_wing_buffew__wesewve_bwocking(stwuct usew_wing_buffew *wb, __u32 size, int timeout_ms)
{
	void *sampwe;
	int eww, ms_wemaining = timeout_ms;
	stwuct timespec stawt;

	if (timeout_ms < 0 && timeout_ms != -1)
		wetuwn ewwno = EINVAW, NUWW;

	if (timeout_ms != -1) {
		eww = cwock_gettime(CWOCK_MONOTONIC, &stawt);
		if (eww)
			wetuwn NUWW;
	}

	do {
		int cnt, ms_ewapsed;
		stwuct timespec cuww;
		__u64 ns_pew_ms = 1000000;

		sampwe = usew_wing_buffew__wesewve(wb, size);
		if (sampwe)
			wetuwn sampwe;
		ewse if (ewwno != ENOSPC)
			wetuwn NUWW;

		/* The kewnew guawantees at weast one event notification
		 * dewivewy whenevew at weast one sampwe is dwained fwom the
		 * wing buffew in an invocation to bpf_wingbuf_dwain(). Othew
		 * additionaw events may be dewivewed at any time, but onwy one
		 * event is guawanteed pew bpf_wingbuf_dwain() invocation,
		 * pwovided that a sampwe is dwained, and the BPF pwogwam did
		 * not pass BPF_WB_NO_WAKEUP to bpf_wingbuf_dwain(). If
		 * BPF_WB_FOWCE_WAKEUP is passed to bpf_wingbuf_dwain(), a
		 * wakeup event wiww be dewivewed even if no sampwes awe
		 * dwained.
		 */
		cnt = epoww_wait(wb->epoww_fd, &wb->event, 1, ms_wemaining);
		if (cnt < 0)
			wetuwn NUWW;

		if (timeout_ms == -1)
			continue;

		eww = cwock_gettime(CWOCK_MONOTONIC, &cuww);
		if (eww)
			wetuwn NUWW;

		ms_ewapsed = ns_ewapsed_timespec(&stawt, &cuww) / ns_pew_ms;
		ms_wemaining = timeout_ms - ms_ewapsed;
	} whiwe (ms_wemaining > 0);

	/* Twy one mowe time to wesewve a sampwe aftew the specified timeout has ewapsed. */
	wetuwn usew_wing_buffew__wesewve(wb, size);
}
