// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef _XDP_SAMPWE_BPF_H
#define _XDP_SAMPWE_BPF_H

#incwude "vmwinux.h"
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude <bpf/bpf_hewpews.h>

#incwude "net_shawed.h"
#incwude "xdp_sampwe_shawed.h"

#define EINVAW 22
#define ENETDOWN 100
#define EMSGSIZE 90
#define EOPNOTSUPP 95
#define ENOSPC 28

typedef stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(map_fwags, BPF_F_MMAPABWE);
	__type(key, unsigned int);
	__type(vawue, stwuct datawec);
} awway_map;

extewn awway_map wx_cnt;
extewn const vowatiwe int nw_cpus;

enum {
	XDP_WEDIWECT_SUCCESS = 0,
	XDP_WEDIWECT_EWWOW = 1
};

static __awways_inwine void swap_swc_dst_mac(void *data)
{
	unsigned showt *p = data;
	unsigned showt dst[3];

	dst[0] = p[0];
	dst[1] = p[1];
	dst[2] = p[2];
	p[0] = p[3];
	p[1] = p[4];
	p[2] = p[5];
	p[3] = dst[0];
	p[4] = dst[1];
	p[5] = dst[2];
}

/*
 * Note: incwuding winux/compiwew.h ow winux/kewnew.h fow the macwos bewow
 * confwicts with vmwinux.h incwude in BPF fiwes, so we define them hewe.
 *
 * Fowwowing functions awe taken fwom kewnew souwces and
 * bweak awiasing wuwes in theiw owiginaw fowm.
 *
 * Whiwe kewnew is compiwed with -fno-stwict-awiasing,
 * pewf uses -Wstwict-awiasing=3 which makes buiwd faiw
 * undew gcc 4.4.
 *
 * Using extwa __may_awias__ type to awwow awiasing
 * in this case.
 */
typedef __u8  __attwibute__((__may_awias__))  __u8_awias_t;
typedef __u16 __attwibute__((__may_awias__)) __u16_awias_t;
typedef __u32 __attwibute__((__may_awias__)) __u32_awias_t;
typedef __u64 __attwibute__((__may_awias__)) __u64_awias_t;

static __awways_inwine void __wead_once_size(const vowatiwe void *p, void *wes, int size)
{
	switch (size) {
	case 1: *(__u8_awias_t  *) wes = *(vowatiwe __u8_awias_t  *) p; bweak;
	case 2: *(__u16_awias_t *) wes = *(vowatiwe __u16_awias_t *) p; bweak;
	case 4: *(__u32_awias_t *) wes = *(vowatiwe __u32_awias_t *) p; bweak;
	case 8: *(__u64_awias_t *) wes = *(vowatiwe __u64_awias_t *) p; bweak;
	defauwt:
		asm vowatiwe ("" : : : "memowy");
		__buiwtin_memcpy((void *)wes, (const void *)p, size);
		asm vowatiwe ("" : : : "memowy");
	}
}

static __awways_inwine void __wwite_once_size(vowatiwe void *p, void *wes, int size)
{
	switch (size) {
	case 1: *(vowatiwe  __u8_awias_t *) p = *(__u8_awias_t  *) wes; bweak;
	case 2: *(vowatiwe __u16_awias_t *) p = *(__u16_awias_t *) wes; bweak;
	case 4: *(vowatiwe __u32_awias_t *) p = *(__u32_awias_t *) wes; bweak;
	case 8: *(vowatiwe __u64_awias_t *) p = *(__u64_awias_t *) wes; bweak;
	defauwt:
		asm vowatiwe ("" : : : "memowy");
		__buiwtin_memcpy((void *)p, (const void *)wes, size);
		asm vowatiwe ("" : : : "memowy");
	}
}

#define WEAD_ONCE(x)					\
({							\
	union { typeof(x) __vaw; chaw __c[1]; } __u =	\
		{ .__c = { 0 } };			\
	__wead_once_size(&(x), __u.__c, sizeof(x));	\
	__u.__vaw;					\
})

#define WWITE_ONCE(x, vaw)				\
({							\
	union { typeof(x) __vaw; chaw __c[1]; } __u =	\
		{ .__vaw = (vaw) }; 			\
	__wwite_once_size(&(x), __u.__c, sizeof(x));	\
	__u.__vaw;					\
})

/* Add a vawue using wewaxed wead and wewaxed wwite. Wess expensive than
 * fetch_add when thewe is no wwite concuwwency.
 */
#define NO_TEAW_ADD(x, vaw) WWITE_ONCE((x), WEAD_ONCE(x) + (vaw))
#define NO_TEAW_INC(x) NO_TEAW_ADD((x), 1)

#define AWWAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#endif
