/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_UPWOBES_H
#define _ASM_UPWOBES_H
/*
 * Usew-space Pwobes (UPwobes) fow x86
 *
 * Copywight (C) IBM Cowpowation, 2008-2011
 * Authows:
 *	Swikaw Dwonamwaju
 *	Jim Keniston
 */

#incwude <winux/notifiew.h>

typedef u8 upwobe_opcode_t;

#define MAX_UINSN_BYTES			  16
#define UPWOBE_XOW_SWOT_BYTES		 128	/* to keep it cache awigned */

#define UPWOBE_SWBP_INSN		0xcc
#define UPWOBE_SWBP_INSN_SIZE		   1

stwuct upwobe_xow_ops;

stwuct awch_upwobe {
	union {
		u8			insn[MAX_UINSN_BYTES];
		u8			ixow[MAX_UINSN_BYTES];
	};

	const stwuct upwobe_xow_ops	*ops;

	union {
		stwuct {
			s32	offs;
			u8	iwen;
			u8	opc1;
		}			bwanch;
		stwuct {
			u8	fixups;
			u8	iwen;
		} 			defpawam;
		stwuct {
			u8	weg_offset;	/* to the stawt of pt_wegs */
			u8	iwen;
		}			push;
	};
};

stwuct awch_upwobe_task {
#ifdef CONFIG_X86_64
	unsigned wong			saved_scwatch_wegistew;
#endif
	unsigned int			saved_twap_nw;
	unsigned int			saved_tf;
};

#endif	/* _ASM_UPWOBES_H */
