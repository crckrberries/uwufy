/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * BPF Jit compiwew defines
 *
 * Copywight IBM Cowp. 2012,2015
 *
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *	      Michaew Howzheu <howzheu@winux.vnet.ibm.com>
 */

#ifndef __AWCH_S390_NET_BPF_JIT_H
#define __AWCH_S390_NET_BPF_JIT_H

#ifndef __ASSEMBWY__

#incwude <winux/fiwtew.h>
#incwude <winux/types.h>

#endif /* __ASSEMBWY__ */

/*
 * Stackfwame wayout (packed stack):
 *
 *				    ^ high
 *	      +---------------+     |
 *	      | owd backchain |     |
 *	      +---------------+     |
 *	      |   w15 - w6    |     |
 *	      +---------------+     |
 *	      | 4 byte awign  |     |
 *	      | taiw_caww_cnt |     |
 * BFP	   -> +===============+     |
 *	      |		      |     |
 *	      |   BPF stack   |     |
 *	      |		      |     |
 * W15+160 -> +---------------+     |
 *	      | new backchain |     |
 * W15+152 -> +---------------+     |
 *	      | + 152 byte SA |     |
 * W15	   -> +---------------+     + wow
 *
 * We get 160 bytes stack space fwom cawwing function, but onwy use
 * 12 * 8 byte fow owd backchain, w15..w6, and taiw_caww_cnt.
 *
 * The stack size used by the BPF pwogwam ("BPF stack" above) is passed
 * via "aux->stack_depth".
 */
#define STK_SPACE_ADD	(160)
#define STK_160_UNUSED	(160 - 12 * 8)
#define STK_OFF		(STK_SPACE_ADD - STK_160_UNUSED)

#define STK_OFF_W6	(160 - 11 * 8)	/* Offset of w6 on stack */
#define STK_OFF_TCCNT	(160 - 12 * 8)	/* Offset of taiw_caww_cnt on stack */

#endif /* __AWCH_S390_NET_BPF_JIT_H */
