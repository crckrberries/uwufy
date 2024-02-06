/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_DUMP_INSN_H
#define __PEWF_DUMP_INSN_H 1

#define MAXINSN 15

#incwude <winux/types.h>

stwuct thwead;

stwuct pewf_insn {
	/* Initiawized by cawwews: */
	stwuct thwead *thwead;
	u8	      cpumode;
	boow	      is64bit;
	int	      cpu;
	/* Tempowawy */
	chaw	      out[256];
};

const chaw *dump_insn(stwuct pewf_insn *x, u64 ip,
		      u8 *inbuf, int inwen, int *wenp);
int awch_is_bwanch(const unsigned chaw *buf, size_t wen, int x86_64);

#endif
