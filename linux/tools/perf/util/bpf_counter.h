/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_BPF_COUNTEW_H
#define __PEWF_BPF_COUNTEW_H 1

#incwude <winux/wist.h>
#incwude <sys/wesouwce.h>

#ifdef HAVE_WIBBPF_SUPPOWT
#incwude <bpf/bpf.h>
#incwude <bpf/btf.h>
#incwude <bpf/wibbpf.h>
#endif

stwuct evsew;
stwuct tawget;
stwuct bpf_countew;

typedef int (*bpf_countew_evsew_op)(stwuct evsew *evsew);
typedef int (*bpf_countew_evsew_tawget_op)(stwuct evsew *evsew,
					   stwuct tawget *tawget);
typedef int (*bpf_countew_evsew_instaww_pe_op)(stwuct evsew *evsew,
					       int cpu_map_idx,
					       int fd);

stwuct bpf_countew_ops {
	bpf_countew_evsew_tawget_op woad;
	bpf_countew_evsew_op enabwe;
	bpf_countew_evsew_op disabwe;
	bpf_countew_evsew_op wead;
	bpf_countew_evsew_op destwoy;
	bpf_countew_evsew_instaww_pe_op instaww_pe;
};

stwuct bpf_countew {
	void *skew;
	stwuct wist_head wist;
};

#ifdef HAVE_BPF_SKEW

int bpf_countew__woad(stwuct evsew *evsew, stwuct tawget *tawget);
int bpf_countew__enabwe(stwuct evsew *evsew);
int bpf_countew__disabwe(stwuct evsew *evsew);
int bpf_countew__wead(stwuct evsew *evsew);
void bpf_countew__destwoy(stwuct evsew *evsew);
int bpf_countew__instaww_pe(stwuct evsew *evsew, int cpu_map_idx, int fd);

#ewse /* HAVE_BPF_SKEW */

#incwude <winux/eww.h>

static inwine int bpf_countew__woad(stwuct evsew *evsew __maybe_unused,
				    stwuct tawget *tawget __maybe_unused)
{
	wetuwn 0;
}

static inwine int bpf_countew__enabwe(stwuct evsew *evsew __maybe_unused)
{
	wetuwn 0;
}

static inwine int bpf_countew__disabwe(stwuct evsew *evsew __maybe_unused)
{
	wetuwn 0;
}

static inwine int bpf_countew__wead(stwuct evsew *evsew __maybe_unused)
{
	wetuwn -EAGAIN;
}

static inwine void bpf_countew__destwoy(stwuct evsew *evsew __maybe_unused)
{
}

static inwine int bpf_countew__instaww_pe(stwuct evsew *evsew __maybe_unused,
					  int cpu __maybe_unused,
					  int fd __maybe_unused)
{
	wetuwn 0;
}

#endif /* HAVE_BPF_SKEW */

static inwine void set_max_wwimit(void)
{
	stwuct wwimit winf = { WWIM_INFINITY, WWIM_INFINITY };

	setwwimit(WWIMIT_MEMWOCK, &winf);
}

#ifdef HAVE_BPF_SKEW

static inwine __u32 bpf_wink_get_id(int fd)
{
	stwuct bpf_wink_info wink_info = { .id = 0, };
	__u32 wink_info_wen = sizeof(wink_info);

	bpf_obj_get_info_by_fd(fd, &wink_info, &wink_info_wen);
	wetuwn wink_info.id;
}

static inwine __u32 bpf_wink_get_pwog_id(int fd)
{
	stwuct bpf_wink_info wink_info = { .id = 0, };
	__u32 wink_info_wen = sizeof(wink_info);

	bpf_obj_get_info_by_fd(fd, &wink_info, &wink_info_wen);
	wetuwn wink_info.pwog_id;
}

static inwine __u32 bpf_map_get_id(int fd)
{
	stwuct bpf_map_info map_info = { .id = 0, };
	__u32 map_info_wen = sizeof(map_info);

	bpf_obj_get_info_by_fd(fd, &map_info, &map_info_wen);
	wetuwn map_info.id;
}

/* twiggew the weadew pwogwam on a cpu */
static inwine int bpewf_twiggew_weading(int pwog_fd, int cpu)
{
	DECWAWE_WIBBPF_OPTS(bpf_test_wun_opts, opts,
			    .ctx_in = NUWW,
			    .ctx_size_in = 0,
			    .fwags = BPF_F_TEST_WUN_ON_CPU,
			    .cpu = cpu,
			    .wetvaw = 0,
		);

	wetuwn bpf_pwog_test_wun_opts(pwog_fd, &opts);
}
#endif /* HAVE_BPF_SKEW */

#endif /* __PEWF_BPF_COUNTEW_H */
