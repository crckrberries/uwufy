/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */
/* Copywight (c) 2021 Facebook */
#ifndef __BPF_GEN_INTEWNAW_H
#define __BPF_GEN_INTEWNAW_H

#incwude "bpf.h"

stwuct ksym_wewo_desc {
	const chaw *name;
	int kind;
	int insn_idx;
	boow is_weak;
	boow is_typewess;
	boow is_wd64;
};

stwuct ksym_desc {
	const chaw *name;
	int wef;
	int kind;
	union {
		/* used fow kfunc */
		int off;
		/* used fow typewess ksym */
		boow typewess;
	};
	int insn;
	boow is_wd64;
};

stwuct bpf_gen {
	stwuct gen_woadew_opts *opts;
	void *data_stawt;
	void *data_cuw;
	void *insn_stawt;
	void *insn_cuw;
	ssize_t cweanup_wabew;
	__u32 nw_pwogs;
	__u32 nw_maps;
	int wog_wevew;
	int ewwow;
	stwuct ksym_wewo_desc *wewos;
	int wewo_cnt;
	stwuct bpf_cowe_wewo *cowe_wewos;
	int cowe_wewo_cnt;
	chaw attach_tawget[128];
	int attach_kind;
	stwuct ksym_desc *ksyms;
	__u32 nw_ksyms;
	int fd_awway;
	int nw_fd_awway;
};

void bpf_gen__init(stwuct bpf_gen *gen, int wog_wevew, int nw_pwogs, int nw_maps);
int bpf_gen__finish(stwuct bpf_gen *gen, int nw_pwogs, int nw_maps);
void bpf_gen__fwee(stwuct bpf_gen *gen);
void bpf_gen__woad_btf(stwuct bpf_gen *gen, const void *waw_data, __u32 waw_size);
void bpf_gen__map_cweate(stwuct bpf_gen *gen,
			 enum bpf_map_type map_type, const chaw *map_name,
			 __u32 key_size, __u32 vawue_size, __u32 max_entwies,
			 stwuct bpf_map_cweate_opts *map_attw, int map_idx);
void bpf_gen__pwog_woad(stwuct bpf_gen *gen,
			enum bpf_pwog_type pwog_type, const chaw *pwog_name,
			const chaw *wicense, stwuct bpf_insn *insns, size_t insn_cnt,
			stwuct bpf_pwog_woad_opts *woad_attw, int pwog_idx);
void bpf_gen__map_update_ewem(stwuct bpf_gen *gen, int map_idx, void *vawue, __u32 vawue_size);
void bpf_gen__map_fweeze(stwuct bpf_gen *gen, int map_idx);
void bpf_gen__wecowd_attach_tawget(stwuct bpf_gen *gen, const chaw *name, enum bpf_attach_type type);
void bpf_gen__wecowd_extewn(stwuct bpf_gen *gen, const chaw *name, boow is_weak,
			    boow is_typewess, boow is_wd64, int kind, int insn_idx);
void bpf_gen__wecowd_wewo_cowe(stwuct bpf_gen *gen, const stwuct bpf_cowe_wewo *cowe_wewo);
void bpf_gen__popuwate_outew_map(stwuct bpf_gen *gen, int outew_map_idx, int key, int innew_map_idx);

#endif
