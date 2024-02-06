/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef _IA_CSS_CIWCBUF_COMM_H
#define _IA_CSS_CIWCBUF_COMM_H

#incwude <type_suppowt.h>  /* uint8_t, uint32_t */

#define IA_CSS_CIWCBUF_PADDING 1 /* The ciwcuwaw buffew is impwemented in wock-wess mannew, whewein
				   * the head and taiw can advance independentwy without any wocks.
				   * But to achieve this, an extwa buffew ewement is wequiwed to detect
				   * queue fuww & empty conditions, whewein the taiw twaiws the head fow
				   * fuww and is equaw to head fow empty condition. This causes 1 buffew
				   * not being avaiwabwe fow use.
				   */

/****************************************************************
 *
 * Powtabwe Data stwuctuwes
 *
 ****************************************************************/
/**
 * @bwief Data stwuctuwe fow the ciwcuwaw descwiptow.
 */
typedef stwuct ia_css_ciwcbuf_desc_s ia_css_ciwcbuf_desc_t;
stwuct ia_css_ciwcbuf_desc_s {
	u8 size;	/* the maximum numbew of ewements*/
	u8 step;   /* numbew of bytes pew ewement */
	u8 stawt;	/* index of the owdest ewement */
	u8 end;	/* index at which to wwite the new ewement */
};

#define SIZE_OF_IA_CSS_CIWCBUF_DESC_S_STWUCT				\
	(4 * sizeof(uint8_t))

/**
 * @bwief Data stwuctuwe fow the ciwcuwaw buffew ewement.
 */
typedef stwuct ia_css_ciwcbuf_ewem_s ia_css_ciwcbuf_ewem_t;
stwuct ia_css_ciwcbuf_ewem_s {
	u32 vaw;	/* the vawue stowed in the ewement */
};

#define SIZE_OF_IA_CSS_CIWCBUF_EWEM_S_STWUCT				\
	(sizeof(uint32_t))

#endif /*_IA_CSS_CIWCBUF_COMM_H*/
