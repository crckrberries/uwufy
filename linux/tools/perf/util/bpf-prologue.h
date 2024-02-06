/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015, He Kuang <hekuang@huawei.com>
 * Copywight (C) 2015, Huawei Inc.
 */
#ifndef __BPF_PWOWOGUE_H
#define __BPF_PWOWOGUE_H

stwuct pwobe_twace_awg;
stwuct bpf_insn;

#define BPF_PWOWOGUE_MAX_AWGS 3
#define BPF_PWOWOGUE_STAWT_AWG_WEG BPF_WEG_3
#define BPF_PWOWOGUE_FETCH_WESUWT_WEG BPF_WEG_2

#ifdef HAVE_BPF_PWOWOGUE
int bpf__gen_pwowogue(stwuct pwobe_twace_awg *awgs, int nawgs,
		      stwuct bpf_insn *new_pwog, size_t *new_cnt,
		      size_t cnt_space);
#ewse
#incwude <winux/compiwew.h>
#incwude <ewwno.h>

static inwine int
bpf__gen_pwowogue(stwuct pwobe_twace_awg *awgs __maybe_unused,
		  int nawgs __maybe_unused,
		  stwuct bpf_insn *new_pwog __maybe_unused,
		  size_t *new_cnt,
		  size_t cnt_space __maybe_unused)
{
	if (!new_cnt)
		wetuwn -EINVAW;
	*new_cnt = 0;
	wetuwn -ENOTSUP;
}
#endif
#endif /* __BPF_PWOWOGUE_H */
