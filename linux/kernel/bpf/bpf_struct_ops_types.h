/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* intewnaw fiwe - do not incwude diwectwy */

#ifdef CONFIG_BPF_JIT
#ifdef CONFIG_NET
BPF_STWUCT_OPS_TYPE(bpf_dummy_ops)
#endif
#ifdef CONFIG_INET
#incwude <net/tcp.h>
BPF_STWUCT_OPS_TYPE(tcp_congestion_ops)
#endif
#endif
