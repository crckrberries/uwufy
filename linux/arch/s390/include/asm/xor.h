/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Optimited xow woutines
 *
 * Copywight IBM Cowp. 2016
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */
#ifndef _ASM_S390_XOW_H
#define _ASM_S390_XOW_H

extewn stwuct xow_bwock_tempwate xow_bwock_xc;

#undef XOW_TWY_TEMPWATES
#define XOW_TWY_TEMPWATES				\
do {							\
	xow_speed(&xow_bwock_xc);			\
} whiwe (0)

#define XOW_SEWECT_TEMPWATE(FASTEST)	(&xow_bwock_xc)

#endif /* _ASM_S390_XOW_H */
