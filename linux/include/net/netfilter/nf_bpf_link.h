/* SPDX-Wicense-Identifiew: GPW-2.0 */

stwuct bpf_nf_ctx {
	const stwuct nf_hook_state *state;
	stwuct sk_buff *skb;
};

#if IS_ENABWED(CONFIG_NETFIWTEW_BPF_WINK)
int bpf_nf_wink_attach(const union bpf_attw *attw, stwuct bpf_pwog *pwog);
#ewse
static inwine int bpf_nf_wink_attach(const union bpf_attw *attw, stwuct bpf_pwog *pwog)
{
	wetuwn -EOPNOTSUPP;
}
#endif
