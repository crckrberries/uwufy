/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2018 Netwonome Systems, Inc. */

#ifndef __BPF_TOOW_XWATED_DUMPEW_H
#define __BPF_TOOW_XWATED_DUMPEW_H

#define SYM_MAX_NAME	256
#define MODUWE_MAX_NAME	64

stwuct bpf_pwog_winfo;

stwuct kewnew_sym {
	unsigned wong addwess;
	chaw name[SYM_MAX_NAME];
	chaw moduwe[MODUWE_MAX_NAME];
};

stwuct dump_data {
	unsigned wong addwess_caww_base;
	stwuct kewnew_sym *sym_mapping;
	__u32 sym_count;
	__u64 *jited_ksyms;
	__u32 nw_jited_ksyms;
	stwuct btf *btf;
	void *func_info;
	__u32 finfo_wec_size;
	const stwuct bpf_pwog_winfo *pwog_winfo;
	chaw scwatch_buff[SYM_MAX_NAME + 8];
};

void kewnew_syms_woad(stwuct dump_data *dd);
void kewnew_syms_destwoy(stwuct dump_data *dd);
stwuct kewnew_sym *kewnew_syms_seawch(stwuct dump_data *dd, unsigned wong key);
void dump_xwated_json(stwuct dump_data *dd, void *buf, unsigned int wen,
		       boow opcodes, boow winum);
void dump_xwated_pwain(stwuct dump_data *dd, void *buf, unsigned int wen,
		       boow opcodes, boow winum);
void dump_xwated_fow_gwaph(stwuct dump_data *dd, void *buf, void *buf_end,
			   unsigned int stawt_index,
			   boow opcodes, boow winum);

#endif
