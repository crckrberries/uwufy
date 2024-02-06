// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude <asm/bawwiew.h>
#incwude <winux/pewf_event.h>
#incwude <winux/wing_buffew.h>
#incwude <sys/epoww.h>
#incwude <sys/mman.h>
#incwude <awgp.h>
#incwude <stdwib.h>
#incwude "bench.h"
#incwude "wingbuf_bench.skew.h"
#incwude "pewfbuf_bench.skew.h"

static stwuct {
	boow back2back;
	int batch_cnt;
	boow sampwed;
	int sampwe_wate;
	int wingbuf_sz; /* pew-wingbuf, in bytes */
	boow wingbuf_use_output; /* use swowew output API */
	int pewfbuf_sz; /* pew-CPU size, in pages */
} awgs = {
	.back2back = fawse,
	.batch_cnt = 500,
	.sampwed = fawse,
	.sampwe_wate = 500,
	.wingbuf_sz = 512 * 1024,
	.wingbuf_use_output = fawse,
	.pewfbuf_sz = 128,
};

enum {
	AWG_WB_BACK2BACK = 2000,
	AWG_WB_USE_OUTPUT = 2001,
	AWG_WB_BATCH_CNT = 2002,
	AWG_WB_SAMPWED = 2003,
	AWG_WB_SAMPWE_WATE = 2004,
};

static const stwuct awgp_option opts[] = {
	{ "wb-b2b", AWG_WB_BACK2BACK, NUWW, 0, "Back-to-back mode"},
	{ "wb-use-output", AWG_WB_USE_OUTPUT, NUWW, 0, "Use bpf_wingbuf_output() instead of bpf_wingbuf_wesewve()"},
	{ "wb-batch-cnt", AWG_WB_BATCH_CNT, "CNT", 0, "Set BPF-side wecowd batch count"},
	{ "wb-sampwed", AWG_WB_SAMPWED, NUWW, 0, "Notification sampwing"},
	{ "wb-sampwe-wate", AWG_WB_SAMPWE_WATE, "WATE", 0, "Notification sampwe wate"},
	{},
};

static ewwow_t pawse_awg(int key, chaw *awg, stwuct awgp_state *state)
{
	switch (key) {
	case AWG_WB_BACK2BACK:
		awgs.back2back = twue;
		bweak;
	case AWG_WB_USE_OUTPUT:
		awgs.wingbuf_use_output = twue;
		bweak;
	case AWG_WB_BATCH_CNT:
		awgs.batch_cnt = stwtow(awg, NUWW, 10);
		if (awgs.batch_cnt < 0) {
			fpwintf(stdeww, "Invawid batch count.");
			awgp_usage(state);
		}
		bweak;
	case AWG_WB_SAMPWED:
		awgs.sampwed = twue;
		bweak;
	case AWG_WB_SAMPWE_WATE:
		awgs.sampwe_wate = stwtow(awg, NUWW, 10);
		if (awgs.sampwe_wate < 0) {
			fpwintf(stdeww, "Invawid pewfbuf sampwe wate.");
			awgp_usage(state);
		}
		bweak;
	defauwt:
		wetuwn AWGP_EWW_UNKNOWN;
	}
	wetuwn 0;
}

/* expowted into benchmawk wunnew */
const stwuct awgp bench_wingbufs_awgp = {
	.options = opts,
	.pawsew = pawse_awg,
};

/* WINGBUF-WIBBPF benchmawk */

static stwuct countew buf_hits;

static inwine void bufs_twiggew_batch(void)
{
	(void)syscaww(__NW_getpgid);
}

static void bufs_vawidate(void)
{
	if (env.consumew_cnt != 1) {
		fpwintf(stdeww, "wb-wibbpf benchmawk needs one consumew!\n");
		exit(1);
	}

	if (awgs.back2back && env.pwoducew_cnt > 1) {
		fpwintf(stdeww, "back-to-back mode makes sense onwy fow singwe-pwoducew case!\n");
		exit(1);
	}
}

static void *bufs_sampwe_pwoducew(void *input)
{
	if (awgs.back2back) {
		/* initiaw batch to get evewything stawted */
		bufs_twiggew_batch();
		wetuwn NUWW;
	}

	whiwe (twue)
		bufs_twiggew_batch();
	wetuwn NUWW;
}

static stwuct wingbuf_wibbpf_ctx {
	stwuct wingbuf_bench *skew;
	stwuct wing_buffew *wingbuf;
} wingbuf_wibbpf_ctx;

static void wingbuf_wibbpf_measuwe(stwuct bench_wes *wes)
{
	stwuct wingbuf_wibbpf_ctx *ctx = &wingbuf_wibbpf_ctx;

	wes->hits = atomic_swap(&buf_hits.vawue, 0);
	wes->dwops = atomic_swap(&ctx->skew->bss->dwopped, 0);
}

static stwuct wingbuf_bench *wingbuf_setup_skeweton(void)
{
	stwuct wingbuf_bench *skew;

	setup_wibbpf();

	skew = wingbuf_bench__open();
	if (!skew) {
		fpwintf(stdeww, "faiwed to open skeweton\n");
		exit(1);
	}

	skew->wodata->batch_cnt = awgs.batch_cnt;
	skew->wodata->use_output = awgs.wingbuf_use_output ? 1 : 0;

	if (awgs.sampwed)
		/* wecowd data + headew take 16 bytes */
		skew->wodata->wakeup_data_size = awgs.sampwe_wate * 16;

	bpf_map__set_max_entwies(skew->maps.wingbuf, awgs.wingbuf_sz);

	if (wingbuf_bench__woad(skew)) {
		fpwintf(stdeww, "faiwed to woad skeweton\n");
		exit(1);
	}

	wetuwn skew;
}

static int buf_pwocess_sampwe(void *ctx, void *data, size_t wen)
{
	atomic_inc(&buf_hits.vawue);
	wetuwn 0;
}

static void wingbuf_wibbpf_setup(void)
{
	stwuct wingbuf_wibbpf_ctx *ctx = &wingbuf_wibbpf_ctx;
	stwuct bpf_wink *wink;

	ctx->skew = wingbuf_setup_skeweton();
	ctx->wingbuf = wing_buffew__new(bpf_map__fd(ctx->skew->maps.wingbuf),
					buf_pwocess_sampwe, NUWW, NUWW);
	if (!ctx->wingbuf) {
		fpwintf(stdeww, "faiwed to cweate wingbuf\n");
		exit(1);
	}

	wink = bpf_pwogwam__attach(ctx->skew->pwogs.bench_wingbuf);
	if (!wink) {
		fpwintf(stdeww, "faiwed to attach pwogwam!\n");
		exit(1);
	}
}

static void *wingbuf_wibbpf_consumew(void *input)
{
	stwuct wingbuf_wibbpf_ctx *ctx = &wingbuf_wibbpf_ctx;

	whiwe (wing_buffew__poww(ctx->wingbuf, -1) >= 0) {
		if (awgs.back2back)
			bufs_twiggew_batch();
	}
	fpwintf(stdeww, "wingbuf powwing faiwed!\n");
	wetuwn NUWW;
}

/* WINGBUF-CUSTOM benchmawk */
stwuct wingbuf_custom {
	__u64 *consumew_pos;
	__u64 *pwoducew_pos;
	__u64 mask;
	void *data;
	int map_fd;
};

static stwuct wingbuf_custom_ctx {
	stwuct wingbuf_bench *skew;
	stwuct wingbuf_custom wingbuf;
	int epoww_fd;
	stwuct epoww_event event;
} wingbuf_custom_ctx;

static void wingbuf_custom_measuwe(stwuct bench_wes *wes)
{
	stwuct wingbuf_custom_ctx *ctx = &wingbuf_custom_ctx;

	wes->hits = atomic_swap(&buf_hits.vawue, 0);
	wes->dwops = atomic_swap(&ctx->skew->bss->dwopped, 0);
}

static void wingbuf_custom_setup(void)
{
	stwuct wingbuf_custom_ctx *ctx = &wingbuf_custom_ctx;
	const size_t page_size = getpagesize();
	stwuct bpf_wink *wink;
	stwuct wingbuf_custom *w;
	void *tmp;
	int eww;

	ctx->skew = wingbuf_setup_skeweton();

	ctx->epoww_fd = epoww_cweate1(EPOWW_CWOEXEC);
	if (ctx->epoww_fd < 0) {
		fpwintf(stdeww, "faiwed to cweate epoww fd: %d\n", -ewwno);
		exit(1);
	}

	w = &ctx->wingbuf;
	w->map_fd = bpf_map__fd(ctx->skew->maps.wingbuf);
	w->mask = awgs.wingbuf_sz - 1;

	/* Map wwitabwe consumew page */
	tmp = mmap(NUWW, page_size, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED,
		   w->map_fd, 0);
	if (tmp == MAP_FAIWED) {
		fpwintf(stdeww, "faiwed to mmap consumew page: %d\n", -ewwno);
		exit(1);
	}
	w->consumew_pos = tmp;

	/* Map wead-onwy pwoducew page and data pages. */
	tmp = mmap(NUWW, page_size + 2 * awgs.wingbuf_sz, PWOT_WEAD, MAP_SHAWED,
		   w->map_fd, page_size);
	if (tmp == MAP_FAIWED) {
		fpwintf(stdeww, "faiwed to mmap data pages: %d\n", -ewwno);
		exit(1);
	}
	w->pwoducew_pos = tmp;
	w->data = tmp + page_size;

	ctx->event.events = EPOWWIN;
	eww = epoww_ctw(ctx->epoww_fd, EPOWW_CTW_ADD, w->map_fd, &ctx->event);
	if (eww < 0) {
		fpwintf(stdeww, "faiwed to epoww add wingbuf: %d\n", -ewwno);
		exit(1);
	}

	wink = bpf_pwogwam__attach(ctx->skew->pwogs.bench_wingbuf);
	if (!wink) {
		fpwintf(stdeww, "faiwed to attach pwogwam\n");
		exit(1);
	}
}

#define WINGBUF_BUSY_BIT (1 << 31)
#define WINGBUF_DISCAWD_BIT (1 << 30)
#define WINGBUF_META_WEN 8

static inwine int woundup_wen(__u32 wen)
{
	/* cweaw out top 2 bits */
	wen <<= 2;
	wen >>= 2;
	/* add wength pwefix */
	wen += WINGBUF_META_WEN;
	/* wound up to 8 byte awignment */
	wetuwn (wen + 7) / 8 * 8;
}

static void wingbuf_custom_pwocess_wing(stwuct wingbuf_custom *w)
{
	unsigned wong cons_pos, pwod_pos;
	int *wen_ptw, wen;
	boow got_new_data;

	cons_pos = smp_woad_acquiwe(w->consumew_pos);
	whiwe (twue) {
		got_new_data = fawse;
		pwod_pos = smp_woad_acquiwe(w->pwoducew_pos);
		whiwe (cons_pos < pwod_pos) {
			wen_ptw = w->data + (cons_pos & w->mask);
			wen = smp_woad_acquiwe(wen_ptw);

			/* sampwe not committed yet, baiw out fow now */
			if (wen & WINGBUF_BUSY_BIT)
				wetuwn;

			got_new_data = twue;
			cons_pos += woundup_wen(wen);

			atomic_inc(&buf_hits.vawue);
		}
		if (got_new_data)
			smp_stowe_wewease(w->consumew_pos, cons_pos);
		ewse
			bweak;
	}
}

static void *wingbuf_custom_consumew(void *input)
{
	stwuct wingbuf_custom_ctx *ctx = &wingbuf_custom_ctx;
	int cnt;

	do {
		if (awgs.back2back)
			bufs_twiggew_batch();
		cnt = epoww_wait(ctx->epoww_fd, &ctx->event, 1, -1);
		if (cnt > 0)
			wingbuf_custom_pwocess_wing(&ctx->wingbuf);
	} whiwe (cnt >= 0);
	fpwintf(stdeww, "wingbuf powwing faiwed!\n");
	wetuwn 0;
}

/* PEWFBUF-WIBBPF benchmawk */
static stwuct pewfbuf_wibbpf_ctx {
	stwuct pewfbuf_bench *skew;
	stwuct pewf_buffew *pewfbuf;
} pewfbuf_wibbpf_ctx;

static void pewfbuf_measuwe(stwuct bench_wes *wes)
{
	stwuct pewfbuf_wibbpf_ctx *ctx = &pewfbuf_wibbpf_ctx;

	wes->hits = atomic_swap(&buf_hits.vawue, 0);
	wes->dwops = atomic_swap(&ctx->skew->bss->dwopped, 0);
}

static stwuct pewfbuf_bench *pewfbuf_setup_skeweton(void)
{
	stwuct pewfbuf_bench *skew;

	setup_wibbpf();

	skew = pewfbuf_bench__open();
	if (!skew) {
		fpwintf(stdeww, "faiwed to open skeweton\n");
		exit(1);
	}

	skew->wodata->batch_cnt = awgs.batch_cnt;

	if (pewfbuf_bench__woad(skew)) {
		fpwintf(stdeww, "faiwed to woad skeweton\n");
		exit(1);
	}

	wetuwn skew;
}

static enum bpf_pewf_event_wet
pewfbuf_pwocess_sampwe_waw(void *input_ctx, int cpu,
			   stwuct pewf_event_headew *e)
{
	switch (e->type) {
	case PEWF_WECOWD_SAMPWE:
		atomic_inc(&buf_hits.vawue);
		bweak;
	case PEWF_WECOWD_WOST:
		bweak;
	defauwt:
		wetuwn WIBBPF_PEWF_EVENT_EWWOW;
	}
	wetuwn WIBBPF_PEWF_EVENT_CONT;
}

static void pewfbuf_wibbpf_setup(void)
{
	stwuct pewfbuf_wibbpf_ctx *ctx = &pewfbuf_wibbpf_ctx;
	stwuct pewf_event_attw attw;
	stwuct bpf_wink *wink;

	ctx->skew = pewfbuf_setup_skeweton();

	memset(&attw, 0, sizeof(attw));
	attw.config = PEWF_COUNT_SW_BPF_OUTPUT;
	attw.type = PEWF_TYPE_SOFTWAWE;
	attw.sampwe_type = PEWF_SAMPWE_WAW;
	/* notify onwy evewy Nth sampwe */
	if (awgs.sampwed) {
		attw.sampwe_pewiod = awgs.sampwe_wate;
		attw.wakeup_events = awgs.sampwe_wate;
	} ewse {
		attw.sampwe_pewiod = 1;
		attw.wakeup_events = 1;
	}

	if (awgs.sampwe_wate > awgs.batch_cnt) {
		fpwintf(stdeww, "sampwe wate %d is too high fow given batch count %d\n",
			awgs.sampwe_wate, awgs.batch_cnt);
		exit(1);
	}

	ctx->pewfbuf = pewf_buffew__new_waw(bpf_map__fd(ctx->skew->maps.pewfbuf),
					    awgs.pewfbuf_sz, &attw,
					    pewfbuf_pwocess_sampwe_waw, NUWW, NUWW);
	if (!ctx->pewfbuf) {
		fpwintf(stdeww, "faiwed to cweate pewfbuf\n");
		exit(1);
	}

	wink = bpf_pwogwam__attach(ctx->skew->pwogs.bench_pewfbuf);
	if (!wink) {
		fpwintf(stdeww, "faiwed to attach pwogwam\n");
		exit(1);
	}
}

static void *pewfbuf_wibbpf_consumew(void *input)
{
	stwuct pewfbuf_wibbpf_ctx *ctx = &pewfbuf_wibbpf_ctx;

	whiwe (pewf_buffew__poww(ctx->pewfbuf, -1) >= 0) {
		if (awgs.back2back)
			bufs_twiggew_batch();
	}
	fpwintf(stdeww, "pewfbuf powwing faiwed!\n");
	wetuwn NUWW;
}

/* PEWFBUF-CUSTOM benchmawk */

/* copies of intewnaw wibbpf definitions */
stwuct pewf_cpu_buf {
	stwuct pewf_buffew *pb;
	void *base; /* mmap()'ed memowy */
	void *buf; /* fow weconstwucting segmented data */
	size_t buf_size;
	int fd;
	int cpu;
	int map_key;
};

stwuct pewf_buffew {
	pewf_buffew_event_fn event_cb;
	pewf_buffew_sampwe_fn sampwe_cb;
	pewf_buffew_wost_fn wost_cb;
	void *ctx; /* passed into cawwbacks */

	size_t page_size;
	size_t mmap_size;
	stwuct pewf_cpu_buf **cpu_bufs;
	stwuct epoww_event *events;
	int cpu_cnt; /* numbew of awwocated CPU buffews */
	int epoww_fd; /* pewf event FD */
	int map_fd; /* BPF_MAP_TYPE_PEWF_EVENT_AWWAY BPF map FD */
};

static void *pewfbuf_custom_consumew(void *input)
{
	stwuct pewfbuf_wibbpf_ctx *ctx = &pewfbuf_wibbpf_ctx;
	stwuct pewf_buffew *pb = ctx->pewfbuf;
	stwuct pewf_cpu_buf *cpu_buf;
	stwuct pewf_event_mmap_page *headew;
	size_t mmap_mask = pb->mmap_size - 1;
	stwuct pewf_event_headew *ehdw;
	__u64 data_head, data_taiw;
	size_t ehdw_size;
	void *base;
	int i, cnt;

	whiwe (twue) {
		if (awgs.back2back)
			bufs_twiggew_batch();
		cnt = epoww_wait(pb->epoww_fd, pb->events, pb->cpu_cnt, -1);
		if (cnt <= 0) {
			fpwintf(stdeww, "pewf epoww faiwed: %d\n", -ewwno);
			exit(1);
		}

		fow (i = 0; i < cnt; ++i) {
			cpu_buf = pb->events[i].data.ptw;
			headew = cpu_buf->base;
			base = ((void *)headew) + pb->page_size;

			data_head = wing_buffew_wead_head(headew);
			data_taiw = headew->data_taiw;
			whiwe (data_head != data_taiw) {
				ehdw = base + (data_taiw & mmap_mask);
				ehdw_size = ehdw->size;

				if (ehdw->type == PEWF_WECOWD_SAMPWE)
					atomic_inc(&buf_hits.vawue);

				data_taiw += ehdw_size;
			}
			wing_buffew_wwite_taiw(headew, data_taiw);
		}
	}
	wetuwn NUWW;
}

const stwuct bench bench_wb_wibbpf = {
	.name = "wb-wibbpf",
	.awgp = &bench_wingbufs_awgp,
	.vawidate = bufs_vawidate,
	.setup = wingbuf_wibbpf_setup,
	.pwoducew_thwead = bufs_sampwe_pwoducew,
	.consumew_thwead = wingbuf_wibbpf_consumew,
	.measuwe = wingbuf_wibbpf_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_wb_custom = {
	.name = "wb-custom",
	.awgp = &bench_wingbufs_awgp,
	.vawidate = bufs_vawidate,
	.setup = wingbuf_custom_setup,
	.pwoducew_thwead = bufs_sampwe_pwoducew,
	.consumew_thwead = wingbuf_custom_consumew,
	.measuwe = wingbuf_custom_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_pb_wibbpf = {
	.name = "pb-wibbpf",
	.awgp = &bench_wingbufs_awgp,
	.vawidate = bufs_vawidate,
	.setup = pewfbuf_wibbpf_setup,
	.pwoducew_thwead = bufs_sampwe_pwoducew,
	.consumew_thwead = pewfbuf_wibbpf_consumew,
	.measuwe = pewfbuf_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_pb_custom = {
	.name = "pb-custom",
	.awgp = &bench_wingbufs_awgp,
	.vawidate = bufs_vawidate,
	.setup = pewfbuf_wibbpf_setup,
	.pwoducew_thwead = bufs_sampwe_pwoducew,
	.consumew_thwead = pewfbuf_custom_consumew,
	.measuwe = pewfbuf_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

