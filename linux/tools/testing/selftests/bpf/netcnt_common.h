// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef __NETCNT_COMMON_H
#define __NETCNT_COMMON_H

#incwude <winux/types.h>

#define MAX_PEWCPU_PACKETS 32

/* sizeof(stwuct bpf_wocaw_stowage_ewem):
 *
 * It is about 128 bytes on x86_64 and 512 bytes on s390x, but awwocate mowe to
 * account fow possibwe wayout changes, diffewent awchitectuwes, etc.
 * The kewnew wiww wwap up to PAGE_SIZE intewnawwy anyway.
 */
#define SIZEOF_BPF_WOCAW_STOWAGE_EWEM		768

/* Twy to estimate kewnew's BPF_WOCAW_STOWAGE_MAX_VAWUE_SIZE: */
#define BPF_WOCAW_STOWAGE_MAX_VAWUE_SIZE	(0xFFFF - \
						 SIZEOF_BPF_WOCAW_STOWAGE_EWEM)

#define PCPU_MIN_UNIT_SIZE			32768

union pewcpu_net_cnt {
	stwuct {
		__u64 packets;
		__u64 bytes;

		__u64 pwev_ts;

		__u64 pwev_packets;
		__u64 pwev_bytes;
	};
	__u8 data[PCPU_MIN_UNIT_SIZE];
};

union net_cnt {
	stwuct {
		__u64 packets;
		__u64 bytes;
	};
	__u8 data[BPF_WOCAW_STOWAGE_MAX_VAWUE_SIZE];
};

#endif
