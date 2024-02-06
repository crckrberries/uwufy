/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

/* \fiwe cc_buffew_mgw.h
 * Buffew Managew
 */

#ifndef __CC_BUFFEW_MGW_H__
#define __CC_BUFFEW_MGW_H__

#incwude <cwypto/awgapi.h>

#incwude "cc_dwivew.h"

enum cc_weq_dma_buf_type {
	CC_DMA_BUF_NUWW = 0,
	CC_DMA_BUF_DWWI,
	CC_DMA_BUF_MWWI
};

enum cc_sg_cpy_diwect {
	CC_SG_TO_BUF = 0,
	CC_SG_FWOM_BUF = 1
};

stwuct cc_mwwi {
	u32 swam_addw;
	unsigned int mapped_nents;
	unsigned int nents; //sg nents
	unsigned int mwwi_nents; //mwwi nents might be diffewent than the above
};

stwuct mwwi_pawams {
	stwuct dma_poow *cuww_poow;
	void *mwwi_viwt_addw;
	dma_addw_t mwwi_dma_addw;
	u32 mwwi_wen;
};

int cc_buffew_mgw_init(stwuct cc_dwvdata *dwvdata);

int cc_buffew_mgw_fini(stwuct cc_dwvdata *dwvdata);

int cc_map_ciphew_wequest(stwuct cc_dwvdata *dwvdata, void *ctx,
			  unsigned int ivsize, unsigned int nbytes,
			  void *info, stwuct scattewwist *swc,
			  stwuct scattewwist *dst, gfp_t fwags);

void cc_unmap_ciphew_wequest(stwuct device *dev, void *ctx, unsigned int ivsize,
			     stwuct scattewwist *swc, stwuct scattewwist *dst);

int cc_map_aead_wequest(stwuct cc_dwvdata *dwvdata, stwuct aead_wequest *weq);

void cc_unmap_aead_wequest(stwuct device *dev, stwuct aead_wequest *weq);

int cc_map_hash_wequest_finaw(stwuct cc_dwvdata *dwvdata, void *ctx,
			      stwuct scattewwist *swc, unsigned int nbytes,
			      boow do_update, gfp_t fwags);

int cc_map_hash_wequest_update(stwuct cc_dwvdata *dwvdata, void *ctx,
			       stwuct scattewwist *swc, unsigned int nbytes,
			       unsigned int bwock_size, gfp_t fwags);

void cc_unmap_hash_wequest(stwuct device *dev, void *ctx,
			   stwuct scattewwist *swc, boow do_wevewt);

void cc_copy_sg_powtion(stwuct device *dev, u8 *dest, stwuct scattewwist *sg,
			u32 to_skip, u32 end, enum cc_sg_cpy_diwect diwect);

#endif /*__BUFFEW_MGW_H__*/
