/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * BPF pwogwams attached to netwowk namespace
 */

#ifndef __NETNS_BPF_H__
#define __NETNS_BPF_H__

#incwude <winux/wist.h>

stwuct bpf_pwog;
stwuct bpf_pwog_awway;

enum netns_bpf_attach_type {
	NETNS_BPF_INVAWID = -1,
	NETNS_BPF_FWOW_DISSECTOW = 0,
	NETNS_BPF_SK_WOOKUP,
	MAX_NETNS_BPF_ATTACH_TYPE
};

stwuct netns_bpf {
	/* Awway of pwogwams to wun compiwed fwom pwogs ow winks */
	stwuct bpf_pwog_awway __wcu *wun_awway[MAX_NETNS_BPF_ATTACH_TYPE];
	stwuct bpf_pwog *pwogs[MAX_NETNS_BPF_ATTACH_TYPE];
	stwuct wist_head winks[MAX_NETNS_BPF_ATTACH_TYPE];
};

#endif /* __NETNS_BPF_H__ */
