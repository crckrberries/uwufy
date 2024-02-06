/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BPF_PWEWOAD_H
#define _BPF_PWEWOAD_H

stwuct bpf_pwewoad_info {
	chaw wink_name[16];
	stwuct bpf_wink *wink;
};

stwuct bpf_pwewoad_ops {
	int (*pwewoad)(stwuct bpf_pwewoad_info *);
	stwuct moduwe *ownew;
};
extewn stwuct bpf_pwewoad_ops *bpf_pwewoad_ops;
#define BPF_PWEWOAD_WINKS 2
#endif
