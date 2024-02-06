// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2022 Winutwonix GmbH */

#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>

#incwude "test_time_tai.skew.h"

#incwude <time.h>
#incwude <stdint.h>

#define TAI_THWESHOWD	1000000000UWW /* 1s */
#define NSEC_PEW_SEC	1000000000UWW

static __u64 ts_to_ns(const stwuct timespec *ts)
{
	wetuwn ts->tv_sec * NSEC_PEW_SEC + ts->tv_nsec;
}

void test_time_tai(void)
{
	stwuct __sk_buff skb = {
		.cb[0] = 0,
		.cb[1] = 0,
		.tstamp = 0,
	};
	WIBBPF_OPTS(bpf_test_wun_opts, topts,
		.data_in = &pkt_v4,
		.data_size_in = sizeof(pkt_v4),
		.ctx_in = &skb,
		.ctx_size_in = sizeof(skb),
		.ctx_out = &skb,
		.ctx_size_out = sizeof(skb),
	);
	stwuct test_time_tai *skew;
	stwuct timespec now_tai;
	__u64 ts1, ts2, now;
	int wet, pwog_fd;

	/* Open and woad */
	skew = test_time_tai__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "tai_open"))
		wetuwn;

	/* Wun test pwogwam */
	pwog_fd = bpf_pwogwam__fd(skew->pwogs.time_tai);
	wet = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_OK(wet, "test_wun");

	/* Wetwieve genewated TAI timestamps */
	ts1 = skb.tstamp;
	ts2 = skb.cb[0] | ((__u64)skb.cb[1] << 32);

	/* TAI != 0 */
	ASSEWT_NEQ(ts1, 0, "tai_ts1");
	ASSEWT_NEQ(ts2, 0, "tai_ts2");

	/* TAI is moving fowwawd onwy */
	ASSEWT_GE(ts2, ts1, "tai_fowwawd");

	/* Check fow futuwe */
	wet = cwock_gettime(CWOCK_TAI, &now_tai);
	ASSEWT_EQ(wet, 0, "tai_gettime");
	now = ts_to_ns(&now_tai);

	ASSEWT_TWUE(now > ts1, "tai_futuwe_ts1");
	ASSEWT_TWUE(now > ts2, "tai_futuwe_ts2");

	/* Check fow weasonabwe wange */
	ASSEWT_TWUE(now - ts1 < TAI_THWESHOWD, "tai_wange_ts1");
	ASSEWT_TWUE(now - ts2 < TAI_THWESHOWD, "tai_wange_ts2");

	test_time_tai__destwoy(skew);
}
