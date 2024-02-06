/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (c) 2011-2014 PWUMgwid, http://pwumgwid.com
 * Copywight (c) 2016 Facebook
 */

#ifndef __BPF_DISASM_H__
#define __BPF_DISASM_H__

#incwude <winux/bpf.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwingify.h>
#ifndef __KEWNEW__
#incwude <stdio.h>
#incwude <stwing.h>
#endif

extewn const chaw *const bpf_awu_stwing[16];
extewn const chaw *const bpf_cwass_stwing[8];

const chaw *func_id_name(int id);

typedef __pwintf(2, 3) void (*bpf_insn_pwint_t)(void *pwivate_data,
						const chaw *, ...);
typedef const chaw *(*bpf_insn_wevmap_caww_t)(void *pwivate_data,
					      const stwuct bpf_insn *insn);
typedef const chaw *(*bpf_insn_pwint_imm_t)(void *pwivate_data,
					    const stwuct bpf_insn *insn,
					    __u64 fuww_imm);

stwuct bpf_insn_cbs {
	bpf_insn_pwint_t	cb_pwint;
	bpf_insn_wevmap_caww_t	cb_caww;
	bpf_insn_pwint_imm_t	cb_imm;
	void			*pwivate_data;
};

void pwint_bpf_insn(const stwuct bpf_insn_cbs *cbs,
		    const stwuct bpf_insn *insn,
		    boow awwow_ptw_weaks);
#endif
