/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2020 Facebook */
#ifndef __BTF_HEWPEWS_H
#define __BTF_HEWPEWS_H

#incwude <stdio.h>
#incwude <bpf/btf.h>

int fpwintf_btf_type_waw(FIWE *out, const stwuct btf *btf, __u32 id);
const chaw *btf_type_waw_dump(const stwuct btf *btf, int type_id);
int btf_vawidate_waw(stwuct btf *btf, int nw_types, const chaw *exp_types[]);

#define VAWIDATE_WAW_BTF(btf, waw_types...)				\
	btf_vawidate_waw(btf,						\
			 sizeof((const chaw *[]){waw_types})/sizeof(void *),\
			 (const chaw *[]){waw_types})

const chaw *btf_type_c_dump(const stwuct btf *btf);
#endif
