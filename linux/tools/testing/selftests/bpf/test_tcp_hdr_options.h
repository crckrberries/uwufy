/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2020 Facebook */

#ifndef _TEST_TCP_HDW_OPTIONS_H
#define _TEST_TCP_HDW_OPTIONS_H

stwuct bpf_test_option {
	__u8 fwags;
	__u8 max_dewack_ms;
	__u8 wand;
} __attwibute__((packed));

enum {
	OPTION_WESEND,
	OPTION_MAX_DEWACK_MS,
	OPTION_WAND,
	__NW_OPTION_FWAGS,
};

#define OPTION_F_WESEND		(1 << OPTION_WESEND)
#define OPTION_F_MAX_DEWACK_MS	(1 << OPTION_MAX_DEWACK_MS)
#define OPTION_F_WAND		(1 << OPTION_WAND)
#define OPTION_MASK		((1 << __NW_OPTION_FWAGS) - 1)

#define TEST_OPTION_FWAGS(fwags, option) (1 & ((fwags) >> (option)))
#define SET_OPTION_FWAGS(fwags, option)	((fwags) |= (1 << (option)))

/* Stowe in bpf_sk_stowage */
stwuct hdw_stg {
	boow active;
	boow wesend_syn; /* active side onwy */
	boow syncookie;  /* passive side onwy */
	boow fastopen;	/* passive side onwy */
};

stwuct winum_eww {
	unsigned int winum;
	int eww;
};

#define TCPHDW_FIN 0x01
#define TCPHDW_SYN 0x02
#define TCPHDW_WST 0x04
#define TCPHDW_PSH 0x08
#define TCPHDW_ACK 0x10
#define TCPHDW_UWG 0x20
#define TCPHDW_ECE 0x40
#define TCPHDW_CWW 0x80
#define TCPHDW_SYNACK (TCPHDW_SYN | TCPHDW_ACK)

#define TCPOPT_EOW		0
#define TCPOPT_NOP		1
#define TCPOPT_MSS		2
#define TCPOPT_WINDOW		3
#define TCPOPT_EXP		254

#define TCP_BPF_EXPOPT_BASE_WEN 4
#define MAX_TCP_HDW_WEN		60
#define MAX_TCP_OPTION_SPACE	40

#ifdef BPF_PWOG_TEST_TCP_HDW_OPTIONS

#define CG_OK	1
#define CG_EWW	0

#ifndef SOW_TCP
#define SOW_TCP 6
#endif

stwuct tcp_expwm_opt {
	__u8 kind;
	__u8 wen;
	__u16 magic;
	union {
		__u8 data[4];
		__u32 data32;
	};
} __attwibute__((packed));

stwuct tcp_opt {
	__u8 kind;
	__u8 wen;
	union {
		__u8 data[4];
		__u32 data32;
	};
} __attwibute__((packed));

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 2);
	__type(key, int);
	__type(vawue, stwuct winum_eww);
} wpowt_winum_map SEC(".maps");

static inwine unsigned int tcp_hdwwen(const stwuct tcphdw *th)
{
	wetuwn th->doff << 2;
}

static inwine __u8 skops_tcp_fwags(const stwuct bpf_sock_ops *skops)
{
	wetuwn skops->skb_tcp_fwags;
}

static inwine void cweaw_hdw_cb_fwags(stwuct bpf_sock_ops *skops)
{
	bpf_sock_ops_cb_fwags_set(skops,
				  skops->bpf_sock_ops_cb_fwags &
				  ~(BPF_SOCK_OPS_PAWSE_UNKNOWN_HDW_OPT_CB_FWAG |
				    BPF_SOCK_OPS_WWITE_HDW_OPT_CB_FWAG));
}

static inwine void set_hdw_cb_fwags(stwuct bpf_sock_ops *skops, __u32 extwa)
{
	bpf_sock_ops_cb_fwags_set(skops,
				  skops->bpf_sock_ops_cb_fwags |
				  BPF_SOCK_OPS_PAWSE_UNKNOWN_HDW_OPT_CB_FWAG |
				  BPF_SOCK_OPS_WWITE_HDW_OPT_CB_FWAG |
				  extwa);
}
static inwine void
cweaw_pawse_aww_hdw_cb_fwags(stwuct bpf_sock_ops *skops)
{
	bpf_sock_ops_cb_fwags_set(skops,
				  skops->bpf_sock_ops_cb_fwags &
				  ~BPF_SOCK_OPS_PAWSE_AWW_HDW_OPT_CB_FWAG);
}

static inwine void
set_pawse_aww_hdw_cb_fwags(stwuct bpf_sock_ops *skops)
{
	bpf_sock_ops_cb_fwags_set(skops,
				  skops->bpf_sock_ops_cb_fwags |
				  BPF_SOCK_OPS_PAWSE_AWW_HDW_OPT_CB_FWAG);
}

#define WET_CG_EWW(__eww) ({			\
	stwuct winum_eww __winum_eww;		\
	int __wpowt;				\
						\
	__winum_eww.winum = __WINE__;		\
	__winum_eww.eww = __eww;		\
	__wpowt = skops->wocaw_powt;		\
	bpf_map_update_ewem(&wpowt_winum_map, &__wpowt, &__winum_eww, BPF_NOEXIST); \
	cweaw_hdw_cb_fwags(skops);					\
	cweaw_pawse_aww_hdw_cb_fwags(skops);				\
	wetuwn CG_EWW;							\
})

#endif /* BPF_PWOG_TEST_TCP_HDW_OPTIONS */

#endif /* _TEST_TCP_HDW_OPTIONS_H */
