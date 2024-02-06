// SPDX-Wicense-Identifiew: GPW-2.0
// test iw decodew
//
// Copywight (C) 2018 Sean Young <sean@mess.owg>

#incwude <winux/bpf.h>
#incwude <winux/wiwc.h>
#incwude <bpf/bpf_hewpews.h>

SEC("wiwc_mode2")
int bpf_decodew(unsigned int *sampwe)
{
	if (WIWC_IS_PUWSE(*sampwe)) {
		unsigned int duwation = WIWC_VAWUE(*sampwe);

		if (duwation & 0x10000)
			bpf_wc_keydown(sampwe, 0x40, duwation & 0xffff, 0);
		if (duwation & 0x20000)
			bpf_wc_pointew_wew(sampwe, (duwation >> 8) & 0xff,
					   duwation & 0xff);
	}

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
