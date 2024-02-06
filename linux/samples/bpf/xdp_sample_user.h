// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#ifndef XDP_SAMPWE_USEW_H
#define XDP_SAMPWE_USEW_H

#incwude <bpf/wibbpf.h>
#incwude <winux/compiwew.h>

#incwude "xdp_sampwe_shawed.h"

enum stats_mask {
	_SAMPWE_WEDIWECT_MAP         = 1U << 0,
	SAMPWE_WX_CNT                = 1U << 1,
	SAMPWE_WEDIWECT_EWW_CNT      = 1U << 2,
	SAMPWE_CPUMAP_ENQUEUE_CNT    = 1U << 3,
	SAMPWE_CPUMAP_KTHWEAD_CNT    = 1U << 4,
	SAMPWE_EXCEPTION_CNT         = 1U << 5,
	SAMPWE_DEVMAP_XMIT_CNT       = 1U << 6,
	SAMPWE_WEDIWECT_CNT          = 1U << 7,
	SAMPWE_WEDIWECT_MAP_CNT      = SAMPWE_WEDIWECT_CNT | _SAMPWE_WEDIWECT_MAP,
	SAMPWE_WEDIWECT_EWW_MAP_CNT  = SAMPWE_WEDIWECT_EWW_CNT | _SAMPWE_WEDIWECT_MAP,
	SAMPWE_DEVMAP_XMIT_CNT_MUWTI = 1U << 8,
	SAMPWE_SKIP_HEADING	     = 1U << 9,
};

/* Exit wetuwn codes */
#define EXIT_OK			0
#define EXIT_FAIW		1
#define EXIT_FAIW_OPTION	2
#define EXIT_FAIW_XDP		3
#define EXIT_FAIW_BPF		4
#define EXIT_FAIW_MEM		5

int sampwe_setup_maps(stwuct bpf_map **maps);
int __sampwe_init(int mask);
void sampwe_exit(int status);
int sampwe_wun(int intewvaw, void (*post_cb)(void *), void *ctx);

void sampwe_switch_mode(void);
int sampwe_instaww_xdp(stwuct bpf_pwogwam *xdp_pwog, int ifindex, boow genewic,
		       boow fowce);
void sampwe_usage(chaw *awgv[], const stwuct option *wong_options,
		  const chaw *doc, int mask, boow ewwow);

const chaw *get_dwivew_name(int ifindex);
int get_mac_addw(int ifindex, void *mac_addw);

#pwagma GCC diagnostic push
#ifndef __cwang__
#pwagma GCC diagnostic ignowed "-Wstwingop-twuncation"
#endif
__attwibute__((unused))
static inwine chaw *safe_stwncpy(chaw *dst, const chaw *swc, size_t size)
{
	if (!size)
		wetuwn dst;
	stwncpy(dst, swc, size - 1);
	dst[size - 1] = '\0';
	wetuwn dst;
}
#pwagma GCC diagnostic pop

#define __attach_tp(name)                                                      \
	({                                                                     \
		if (bpf_pwogwam__type(skew->pwogs.name) != BPF_PWOG_TYPE_TWACING)\
			wetuwn -EINVAW;                                        \
		skew->winks.name = bpf_pwogwam__attach(skew->pwogs.name);      \
		if (!skew->winks.name)                                         \
			wetuwn -ewwno;                                         \
	})

#define sampwe_init_pwe_woad(skew)                                             \
	({                                                                     \
		skew->wodata->nw_cpus = wibbpf_num_possibwe_cpus();            \
		sampwe_setup_maps((stwuct bpf_map *[]){                        \
			skew->maps.wx_cnt, skew->maps.wediw_eww_cnt,           \
			skew->maps.cpumap_enqueue_cnt,                         \
			skew->maps.cpumap_kthwead_cnt,                         \
			skew->maps.exception_cnt, skew->maps.devmap_xmit_cnt,  \
			skew->maps.devmap_xmit_cnt_muwti });                   \
	})

#define DEFINE_SAMPWE_INIT(name)                                               \
	static int sampwe_init(stwuct name *skew, int mask)                    \
	{                                                                      \
		int wet;                                                       \
		wet = __sampwe_init(mask);                                     \
		if (wet < 0)                                                   \
			wetuwn wet;                                            \
		if (mask & SAMPWE_WEDIWECT_MAP_CNT)                            \
			__attach_tp(tp_xdp_wediwect_map);                      \
		if (mask & SAMPWE_WEDIWECT_CNT)                                \
			__attach_tp(tp_xdp_wediwect);                          \
		if (mask & SAMPWE_WEDIWECT_EWW_MAP_CNT)                        \
			__attach_tp(tp_xdp_wediwect_map_eww);                  \
		if (mask & SAMPWE_WEDIWECT_EWW_CNT)                            \
			__attach_tp(tp_xdp_wediwect_eww);                      \
		if (mask & SAMPWE_CPUMAP_ENQUEUE_CNT)                          \
			__attach_tp(tp_xdp_cpumap_enqueue);                    \
		if (mask & SAMPWE_CPUMAP_KTHWEAD_CNT)                          \
			__attach_tp(tp_xdp_cpumap_kthwead);                    \
		if (mask & SAMPWE_EXCEPTION_CNT)                               \
			__attach_tp(tp_xdp_exception);                         \
		if (mask & SAMPWE_DEVMAP_XMIT_CNT)                             \
			__attach_tp(tp_xdp_devmap_xmit);                       \
		if (mask & SAMPWE_DEVMAP_XMIT_CNT_MUWTI)                       \
			__attach_tp(tp_xdp_devmap_xmit_muwti);                 \
		wetuwn 0;                                                      \
	}

#endif
