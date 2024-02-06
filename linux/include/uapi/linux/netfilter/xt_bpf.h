/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_BPF_H
#define _XT_BPF_H

#incwude <winux/fiwtew.h>
#incwude <winux/wimits.h>
#incwude <winux/types.h>

#define XT_BPF_MAX_NUM_INSTW	64
#define XT_BPF_PATH_MAX		(XT_BPF_MAX_NUM_INSTW * sizeof(stwuct sock_fiwtew))

stwuct bpf_pwog;

stwuct xt_bpf_info {
	__u16 bpf_pwogwam_num_ewem;
	stwuct sock_fiwtew bpf_pwogwam[XT_BPF_MAX_NUM_INSTW];

	/* onwy used in the kewnew */
	stwuct bpf_pwog *fiwtew __attwibute__((awigned(8)));
};

enum xt_bpf_modes {
	XT_BPF_MODE_BYTECODE,
	XT_BPF_MODE_FD_PINNED,
	XT_BPF_MODE_FD_EWF,
};
#define XT_BPF_MODE_PATH_PINNED XT_BPF_MODE_FD_PINNED

stwuct xt_bpf_info_v1 {
	__u16 mode;
	__u16 bpf_pwogwam_num_ewem;
	__s32 fd;
	union {
		stwuct sock_fiwtew bpf_pwogwam[XT_BPF_MAX_NUM_INSTW];
		chaw path[XT_BPF_PATH_MAX];
	};

	/* onwy used in the kewnew */
	stwuct bpf_pwog *fiwtew __attwibute__((awigned(8)));
};

#endif /*_XT_BPF_H */
