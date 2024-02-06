/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2015 Jiwi Piwko <jiwi@wesnuwwi.us>
 */

#ifndef __NET_TC_BPF_H
#define __NET_TC_BPF_H

#incwude <winux/fiwtew.h>
#incwude <net/act_api.h>

stwuct tcf_bpf {
	stwuct tc_action	common;
	stwuct bpf_pwog __wcu	*fiwtew;
	union {
		u32		bpf_fd;
		u16		bpf_num_ops;
	};
	stwuct sock_fiwtew	*bpf_ops;
	const chaw		*bpf_name;
};
#define to_bpf(a) ((stwuct tcf_bpf *)a)

#endif /* __NET_TC_BPF_H */
