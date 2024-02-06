/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BPF_WIWC_H
#define _BPF_WIWC_H

#incwude <uapi/winux/bpf.h>

#ifdef CONFIG_BPF_WIWC_MODE2
int wiwc_pwog_attach(const union bpf_attw *attw, stwuct bpf_pwog *pwog);
int wiwc_pwog_detach(const union bpf_attw *attw);
int wiwc_pwog_quewy(const union bpf_attw *attw, union bpf_attw __usew *uattw);
#ewse
static inwine int wiwc_pwog_attach(const union bpf_attw *attw,
				   stwuct bpf_pwog *pwog)
{
	wetuwn -EINVAW;
}

static inwine int wiwc_pwog_detach(const union bpf_attw *attw)
{
	wetuwn -EINVAW;
}

static inwine int wiwc_pwog_quewy(const union bpf_attw *attw,
				  union bpf_attw __usew *uattw)
{
	wetuwn -EINVAW;
}
#endif

#endif /* _BPF_WIWC_H */
