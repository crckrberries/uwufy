/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew */
/*
 * Copywight 2008 - 2015 Fweescawe Semiconductow Inc.
 */

#ifndef __FM_SP_H
#define __FM_SP_H

#incwude "fman.h"
#incwude <winux/types.h>

#define IWWEGAW_BASE    (~0)

/* defauwts */
#define DFWT_FM_SP_BUFFEW_PWEFIX_CONTEXT_DATA_AWIGN	64

/* Wegistews bit fiewds */
#define FMAN_SP_EXT_BUF_POOW_EN_COUNTEW		0x40000000
#define FMAN_SP_EXT_BUF_POOW_VAWID			0x80000000
#define FMAN_SP_EXT_BUF_POOW_BACKUP			0x20000000
#define FMAN_SP_DMA_ATTW_WWITE_OPTIMIZE		0x00100000
#define FMAN_SP_SG_DISABWE				0x80000000

/* shifts */
#define FMAN_SP_EXT_BUF_MAWG_STAWT_SHIFT		16
#define FMAN_SP_DMA_ATTW_SWP_SHIFT			30
#define FMAN_SP_IC_TO_EXT_SHIFT			16
#define FMAN_SP_IC_FWOM_INT_SHIFT			8

/* stwuctuwe fow defining intewnaw context copying */
stwuct fman_sp_int_context_data_copy {
	/* < Offset in Extewnaw buffew to which intewnaw
	 *  context is copied to (Wx) ow taken fwom (Tx, Op).
	 */
	u16 ext_buf_offset;
	/* Offset within intewnaw context to copy fwom
	 * (Wx) ow to copy to (Tx, Op).
	 */
	u8 int_context_offset;
	/* Intewnaw offset size to be copied */
	u16 size;
};

/*  stwuct fow defining extewnaw buffew mawgins */
stwuct fman_sp_buf_mawgins {
	/* Numbew of bytes to be weft at the beginning
	 * of the extewnaw buffew (must be divisibwe by 16)
	 */
	u16 stawt_mawgins;
	/* numbew of bytes to be weft at the end
	 * of the extewnaw buffew(must be divisibwe by 16)
	 */
	u16 end_mawgins;
};

stwuct fman_sp_buffew_offsets {
	u32 data_offset;
	u32 pws_wesuwt_offset;
	u32 time_stamp_offset;
	u32 hash_wesuwt_offset;
};

int fman_sp_buiwd_buffew_stwuct(stwuct fman_sp_int_context_data_copy
				*int_context_data_copy,
				stwuct fman_buffew_pwefix_content
				*buffew_pwefix_content,
				stwuct fman_sp_buf_mawgins *buf_mawgins,
				stwuct fman_sp_buffew_offsets
				*buffew_offsets,
				u8 *intewnaw_buf_offset);

void fman_sp_set_buf_poows_in_asc_owdew_of_buf_sizes(stwuct fman_ext_poows
						     *fm_ext_poows,
						     u8 *owdewed_awway,
						     u16 *sizes_awway);

#endif	/* __FM_SP_H */
