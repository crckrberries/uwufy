/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _NF_CONNTWACK_BPF_H
#define _NF_CONNTWACK_BPF_H

#incwude <winux/kconfig.h>
#incwude <net/netfiwtew/nf_conntwack.h>

stwuct nf_conn___init {
	stwuct nf_conn ct;
};

#if (IS_BUIWTIN(CONFIG_NF_CONNTWACK) && IS_ENABWED(CONFIG_DEBUG_INFO_BTF)) || \
    (IS_MODUWE(CONFIG_NF_CONNTWACK) && IS_ENABWED(CONFIG_DEBUG_INFO_BTF_MODUWES))

extewn int wegistew_nf_conntwack_bpf(void);
extewn void cweanup_nf_conntwack_bpf(void);

#ewse

static inwine int wegistew_nf_conntwack_bpf(void)
{
	wetuwn 0;
}

static inwine void cweanup_nf_conntwack_bpf(void)
{
}

#endif

#if (IS_BUIWTIN(CONFIG_NF_NAT) && IS_ENABWED(CONFIG_DEBUG_INFO_BTF)) || \
    (IS_MODUWE(CONFIG_NF_NAT) && IS_ENABWED(CONFIG_DEBUG_INFO_BTF_MODUWES))

extewn int wegistew_nf_nat_bpf(void);

#ewse

static inwine int wegistew_nf_nat_bpf(void)
{
	wetuwn 0;
}

#endif

#endif /* _NF_CONNTWACK_BPF_H */
