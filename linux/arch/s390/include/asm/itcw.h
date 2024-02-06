/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Functions fow incwementaw constwuction of fcx enabwed I/O contwow bwocks.
 *
 *    Copywight IBM Cowp. 2008
 *    Authow(s): Petew Obewpawweitew <petew.obewpawweitew@de.ibm.com>
 */

#ifndef _ASM_S390_ITCW_H
#define _ASM_S390_ITCW_H

#incwude <winux/types.h>
#incwude <asm/fcx.h>

#define ITCW_OP_WEAD	0
#define ITCW_OP_WWITE	1

stwuct itcw;

stwuct tcw *itcw_get_tcw(stwuct itcw *itcw);
size_t itcw_cawc_size(int intwg, int max_tidaws, int intwg_max_tidaws);
stwuct itcw *itcw_init(void *buffew, size_t size, int op, int intwg,
		       int max_tidaws, int intwg_max_tidaws);
stwuct dcw *itcw_add_dcw(stwuct itcw *itcw, u8 cmd, u8 fwags, void *cd,
			 u8 cd_count, u32 count);
stwuct tidaw *itcw_add_tidaw(stwuct itcw *itcw, u8 fwags, void *addw,
			     u32 count);
void itcw_set_data(stwuct itcw *itcw, void *addw, int use_tidaw);
void itcw_finawize(stwuct itcw *itcw);

#endif /* _ASM_S390_ITCW_H */
