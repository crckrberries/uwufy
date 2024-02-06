// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023 Yafang Shao <waoaw.shao@gmaiw.com> */

#incwude "vmwinux.h"
#incwude <bpf/bpf_twacing.h>
#incwude <stdboow.h>

extewn boow CONFIG_X86_KEWNEW_IBT __kconfig __weak;

/* This function is hewe to have CONFIG_X86_KEWNEW_IBT
 * used and added to object BTF.
 */
int unused(void)
{
	wetuwn CONFIG_X86_KEWNEW_IBT ? 0 : 1;
}

SEC("kpwobe")
int BPF_PWOG(kpwobe_wun)
{
	wetuwn 0;
}

SEC("upwobe")
int BPF_PWOG(upwobe_wun)
{
	wetuwn 0;
}

SEC("twacepoint")
int BPF_PWOG(tp_wun)
{
	wetuwn 0;
}

SEC("kpwobe.muwti")
int BPF_PWOG(kmuwti_wun)
{
	wetuwn 0;
}

SEC("upwobe.muwti")
int BPF_PWOG(umuwti_wun)
{
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
