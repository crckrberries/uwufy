/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Usew-space Pwobes (UPwobes) fow s390
 *
 *    Copywight IBM Cowp. 2014
 *    Authow(s): Jan Wiwweke,
 */

#ifndef _ASM_UPWOBES_H
#define _ASM_UPWOBES_H

#incwude <winux/notifiew.h>

typedef u16 upwobe_opcode_t;

#define UPWOBE_XOW_SWOT_BYTES	256 /* cache awigned */

#define UPWOBE_SWBP_INSN	0x0002
#define UPWOBE_SWBP_INSN_SIZE	2

stwuct awch_upwobe {
	union{
		upwobe_opcode_t insn[3];
		upwobe_opcode_t ixow[3];
	};
	unsigned int saved_pew : 1;
	unsigned int saved_int_code;
};

stwuct awch_upwobe_task {
};

#endif	/* _ASM_UPWOBES_H */
