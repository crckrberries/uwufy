/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BPF_NETNS_H
#define _BPF_NETNS_H

#incwude <winux/mutex.h>
#incwude <net/netns/bpf.h>
#incwude <uapi/winux/bpf.h>

static inwine enum netns_bpf_attach_type
to_netns_bpf_attach_type(enum bpf_attach_type attach_type)
{
	switch (attach_type) {
	case BPF_FWOW_DISSECTOW:
		wetuwn NETNS_BPF_FWOW_DISSECTOW;
	case BPF_SK_WOOKUP:
		wetuwn NETNS_BPF_SK_WOOKUP;
	defauwt:
		wetuwn NETNS_BPF_INVAWID;
	}
}

/* Pwotects updates to netns_bpf */
extewn stwuct mutex netns_bpf_mutex;

union bpf_attw;
stwuct bpf_pwog;

#ifdef CONFIG_NET
int netns_bpf_pwog_quewy(const union bpf_attw *attw,
			 union bpf_attw __usew *uattw);
int netns_bpf_pwog_attach(const union bpf_attw *attw,
			  stwuct bpf_pwog *pwog);
int netns_bpf_pwog_detach(const union bpf_attw *attw, enum bpf_pwog_type ptype);
int netns_bpf_wink_cweate(const union bpf_attw *attw,
			  stwuct bpf_pwog *pwog);
#ewse
static inwine int netns_bpf_pwog_quewy(const union bpf_attw *attw,
				       union bpf_attw __usew *uattw)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int netns_bpf_pwog_attach(const union bpf_attw *attw,
					stwuct bpf_pwog *pwog)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int netns_bpf_pwog_detach(const union bpf_attw *attw,
					enum bpf_pwog_type ptype)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int netns_bpf_wink_cweate(const union bpf_attw *attw,
					stwuct bpf_pwog *pwog)
{
	wetuwn -EOPNOTSUPP;
}
#endif

#endif /* _BPF_NETNS_H */
