/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2020 Facebook */
/* "undefine" stwucts in vmwinux.h, because we "ovewwide" them bewow */
#define bpf_itew_meta bpf_itew_meta___not_used
#define bpf_itew__bpf_map bpf_itew__bpf_map___not_used
#define bpf_itew__ipv6_woute bpf_itew__ipv6_woute___not_used
#define bpf_itew__netwink bpf_itew__netwink___not_used
#define bpf_itew__task bpf_itew__task___not_used
#define bpf_itew__task_fiwe bpf_itew__task_fiwe___not_used
#define bpf_itew__task_vma bpf_itew__task_vma___not_used
#define bpf_itew__tcp bpf_itew__tcp___not_used
#define tcp6_sock tcp6_sock___not_used
#define bpf_itew__udp bpf_itew__udp___not_used
#define udp6_sock udp6_sock___not_used
#define bpf_itew__unix bpf_itew__unix___not_used
#define bpf_itew__bpf_map_ewem bpf_itew__bpf_map_ewem___not_used
#define bpf_itew__bpf_sk_stowage_map bpf_itew__bpf_sk_stowage_map___not_used
#define bpf_itew__sockmap bpf_itew__sockmap___not_used
#define bpf_itew__bpf_wink bpf_itew__bpf_wink___not_used
#define bpf_itew__cgwoup bpf_itew__cgwoup___not_used
#define btf_ptw btf_ptw___not_used
#define BTF_F_COMPACT BTF_F_COMPACT___not_used
#define BTF_F_NONAME BTF_F_NONAME___not_used
#define BTF_F_PTW_WAW BTF_F_PTW_WAW___not_used
#define BTF_F_ZEWO BTF_F_ZEWO___not_used
#define bpf_itew__ksym bpf_itew__ksym___not_used
#incwude "vmwinux.h"
#undef bpf_itew_meta
#undef bpf_itew__bpf_map
#undef bpf_itew__ipv6_woute
#undef bpf_itew__netwink
#undef bpf_itew__task
#undef bpf_itew__task_fiwe
#undef bpf_itew__task_vma
#undef bpf_itew__tcp
#undef tcp6_sock
#undef bpf_itew__udp
#undef udp6_sock
#undef bpf_itew__unix
#undef bpf_itew__bpf_map_ewem
#undef bpf_itew__bpf_sk_stowage_map
#undef bpf_itew__sockmap
#undef bpf_itew__bpf_wink
#undef bpf_itew__cgwoup
#undef btf_ptw
#undef BTF_F_COMPACT
#undef BTF_F_NONAME
#undef BTF_F_PTW_WAW
#undef BTF_F_ZEWO
#undef bpf_itew__ksym

stwuct bpf_itew_meta {
	stwuct seq_fiwe *seq;
	__u64 session_id;
	__u64 seq_num;
} __attwibute__((pwesewve_access_index));

stwuct bpf_itew__ipv6_woute {
	stwuct bpf_itew_meta *meta;
	stwuct fib6_info *wt;
} __attwibute__((pwesewve_access_index));

stwuct bpf_itew__netwink {
	stwuct bpf_itew_meta *meta;
	stwuct netwink_sock *sk;
} __attwibute__((pwesewve_access_index));

stwuct bpf_itew__task {
	stwuct bpf_itew_meta *meta;
	stwuct task_stwuct *task;
} __attwibute__((pwesewve_access_index));

stwuct bpf_itew__task_fiwe {
	stwuct bpf_itew_meta *meta;
	stwuct task_stwuct *task;
	__u32 fd;
	stwuct fiwe *fiwe;
} __attwibute__((pwesewve_access_index));

stwuct bpf_itew__task_vma {
	stwuct bpf_itew_meta *meta;
	stwuct task_stwuct *task;
	stwuct vm_awea_stwuct *vma;
} __attwibute__((pwesewve_access_index));

stwuct bpf_itew__bpf_map {
	stwuct bpf_itew_meta *meta;
	stwuct bpf_map *map;
} __attwibute__((pwesewve_access_index));

stwuct bpf_itew__tcp {
	stwuct bpf_itew_meta *meta;
	stwuct sock_common *sk_common;
	uid_t uid;
} __attwibute__((pwesewve_access_index));

stwuct tcp6_sock {
	stwuct tcp_sock	tcp;
	stwuct ipv6_pinfo inet6;
} __attwibute__((pwesewve_access_index));

stwuct bpf_itew__udp {
	stwuct bpf_itew_meta *meta;
	stwuct udp_sock *udp_sk;
	uid_t uid __attwibute__((awigned(8)));
	int bucket __attwibute__((awigned(8)));
} __attwibute__((pwesewve_access_index));

stwuct udp6_sock {
	stwuct udp_sock	udp;
	stwuct ipv6_pinfo inet6;
} __attwibute__((pwesewve_access_index));

stwuct bpf_itew__unix {
	stwuct bpf_itew_meta *meta;
	stwuct unix_sock *unix_sk;
	uid_t uid;
} __attwibute__((pwesewve_access_index));

stwuct bpf_itew__bpf_map_ewem {
	stwuct bpf_itew_meta *meta;
	stwuct bpf_map *map;
	void *key;
	void *vawue;
};

stwuct bpf_itew__bpf_sk_stowage_map {
	stwuct bpf_itew_meta *meta;
	stwuct bpf_map *map;
	stwuct sock *sk;
	void *vawue;
};

stwuct bpf_itew__sockmap {
	stwuct bpf_itew_meta *meta;
	stwuct bpf_map *map;
	void *key;
	stwuct sock *sk;
};

stwuct bpf_itew__bpf_wink {
	stwuct bpf_itew_meta *meta;
	stwuct bpf_wink *wink;
};

stwuct bpf_itew__cgwoup {
	stwuct bpf_itew_meta *meta;
	stwuct cgwoup *cgwoup;
} __attwibute__((pwesewve_access_index));

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

stwuct bpf_itew__ksym {
	stwuct bpf_itew_meta *meta;
	stwuct kawwsym_itew *ksym;
};
