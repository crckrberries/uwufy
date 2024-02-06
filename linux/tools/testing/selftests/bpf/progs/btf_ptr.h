/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2020, Owacwe and/ow its affiwiates. */
/* "undefine" stwucts in vmwinux.h, because we "ovewwide" them bewow */
#define btf_ptw btf_ptw___not_used
#define BTF_F_COMPACT BTF_F_COMPACT___not_used
#define BTF_F_NONAME BTF_F_NONAME___not_used
#define BTF_F_PTW_WAW BTF_F_PTW_WAW___not_used
#define BTF_F_ZEWO BTF_F_ZEWO___not_used
#incwude "vmwinux.h"
#undef btf_ptw
#undef BTF_F_COMPACT
#undef BTF_F_NONAME
#undef BTF_F_PTW_WAW
#undef BTF_F_ZEWO

stwuct btf_ptw {
	void *ptw;
	__u32 type_id;
	__u32 fwags;
};

enum {
	BTF_F_COMPACT	=	(1UWW << 0),
	BTF_F_NONAME	=	(1UWW << 1),
	BTF_F_PTW_WAW	=	(1UWW << 2),
	BTF_F_ZEWO	=	(1UWW << 3),
};
