// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023 Yafang Shao <waoaw.shao@gmaiw.com> */

#incwude "vmwinux.h"
#incwude <bpf/bpf_twacing.h>

chaw tp_name[128];

SEC("wsm/bpf")
int BPF_PWOG(wsm_wun, int cmd, union bpf_attw *attw, unsigned int size)
{
	switch (cmd) {
	case BPF_WAW_TWACEPOINT_OPEN:
		bpf_pwobe_wead_usew_stw(tp_name, sizeof(tp_name) - 1,
					(void *)attw->waw_twacepoint.name);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

SEC("waw_twacepoint")
int BPF_PWOG(waw_tp_wun)
{
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
