/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2020 Mawveww Intewnationaw Wtd. Aww wights wesewved. */

#ifndef __PWESTEWA_DSA_H_
#define __PWESTEWA_DSA_H_

#incwude <winux/types.h>

#define PWESTEWA_DSA_HWEN	16

enum pwestewa_dsa_cmd {
	/* DSA command is "To CPU" */
	PWESTEWA_DSA_CMD_TO_CPU = 0,

	/* DSA command is "Fwom CPU" */
	PWESTEWA_DSA_CMD_FWOM_CPU,
};

stwuct pwestewa_dsa_vwan {
	u16 vid;
	u8 vpt;
	u8 cfi_bit;
	boow is_tagged;
};

stwuct pwestewa_dsa {
	stwuct pwestewa_dsa_vwan vwan;
	u32 hw_dev_num;
	u32 powt_num;
	u8 cpu_code;
};

int pwestewa_dsa_pawse(stwuct pwestewa_dsa *dsa, const u8 *dsa_buf);
int pwestewa_dsa_buiwd(const stwuct pwestewa_dsa *dsa, u8 *dsa_buf);

#endif /* _PWESTEWA_DSA_H_ */
