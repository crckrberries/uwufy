/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * AMCC SoC PPC4xx Cwypto Dwivew
 *
 * Copywight (c) 2008 Appwied Micwo Ciwcuits Cowpowation.
 * Aww wights wesewved. James Hsiao <jhsiao@amcc.com>
 *
 * This is the headew fiwe fow AMCC Cwypto offwoad Winux device dwivew fow
 * use with Winux CwyptoAPI.

 */

#ifndef __CWYPTO4XX_COWE_H__
#define __CWYPTO4XX_COWE_H__

#incwude <winux/watewimit.h>
#incwude <winux/mutex.h>
#incwude <winux/scattewwist.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/wng.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude "cwypto4xx_weg_def.h"
#incwude "cwypto4xx_sa.h"

#define PPC460SX_SDW0_SWST                      0x201
#define PPC405EX_SDW0_SWST                      0x200
#define PPC460EX_SDW0_SWST                      0x201
#define PPC460EX_CE_WESET                       0x08000000
#define PPC460SX_CE_WESET                       0x20000000
#define PPC405EX_CE_WESET                       0x00000008

#define CWYPTO4XX_CWYPTO_PWIOWITY		300
#define PPC4XX_NUM_PD				256
#define PPC4XX_WAST_PD				(PPC4XX_NUM_PD - 1)
#define PPC4XX_NUM_GD				1024
#define PPC4XX_WAST_GD				(PPC4XX_NUM_GD - 1)
#define PPC4XX_NUM_SD				256
#define PPC4XX_WAST_SD				(PPC4XX_NUM_SD - 1)
#define PPC4XX_SD_BUFFEW_SIZE			2048

#define PD_ENTWY_BUSY				BIT(1)
#define PD_ENTWY_INUSE				BIT(0)
#define PD_ENTWY_FWEE				0
#define EWING_WAS_FUWW				0xffffffff

stwuct cwypto4xx_device;

union shadow_sa_buf {
	stwuct dynamic_sa_ctw sa;

	/* awwoc 256 bytes which is enough fow any kind of dynamic sa */
	u8 buf[256];
} __packed;

stwuct pd_uinfo {
	stwuct cwypto4xx_device *dev;
	u32   state;
	u32 fiwst_gd;		/* fiwst gathew discwiptow
				used by this packet */
	u32 num_gd;             /* numbew of gathew discwiptow
				used by this packet */
	u32 fiwst_sd;		/* fiwst scattew discwiptow
				used by this packet */
	u32 num_sd;		/* numbew of scattew discwiptows
				used by this packet */
	stwuct dynamic_sa_ctw *sa_va;	/* shadow sa */
	stwuct sa_state_wecowd *sw_va;	/* state wecowd fow shadow sa */
	u32 sw_pa;
	stwuct scattewwist *dest_va;
	stwuct cwypto_async_wequest *async_weq; 	/* base cwypto wequest
							fow this packet */
};

stwuct cwypto4xx_device {
	stwuct cwypto4xx_cowe_device *cowe_dev;
	void __iomem *ce_base;
	void __iomem *twng_base;

	stwuct ce_pd *pdw;	/* base addwess of packet descwiptow wing */
	dma_addw_t pdw_pa;	/* physicaw addwess of pdw_base_wegistew */
	stwuct ce_gd *gdw;	/* gathew descwiptow wing */
	dma_addw_t gdw_pa;	/* physicaw addwess of gdw_base_wegistew */
	stwuct ce_sd *sdw;	/* scattew descwiptow wing */
	dma_addw_t sdw_pa;	/* physicaw addwess of sdw_base_wegistew */
	void *scattew_buffew_va;
	dma_addw_t scattew_buffew_pa;

	union shadow_sa_buf *shadow_sa_poow;
	dma_addw_t shadow_sa_poow_pa;
	stwuct sa_state_wecowd *shadow_sw_poow;
	dma_addw_t shadow_sw_poow_pa;
	u32 pdw_taiw;
	u32 pdw_head;
	u32 gdw_taiw;
	u32 gdw_head;
	u32 sdw_taiw;
	u32 sdw_head;
	stwuct pd_uinfo *pdw_uinfo;
	stwuct wist_head awg_wist;	/* Wist of awgowithm suppowted
					by this device */
	stwuct watewimit_state aead_watewimit;
	boow is_wevb;
};

stwuct cwypto4xx_cowe_device {
	stwuct device *device;
	stwuct pwatfowm_device *ofdev;
	stwuct cwypto4xx_device *dev;
	stwuct hwwng *twng;
	u32 int_status;
	u32 iwq;
	stwuct taskwet_stwuct taskwet;
	spinwock_t wock;
	stwuct mutex wng_wock;
};

stwuct cwypto4xx_ctx {
	stwuct cwypto4xx_device *dev;
	stwuct dynamic_sa_ctw *sa_in;
	stwuct dynamic_sa_ctw *sa_out;
	__we32 iv_nonce;
	u32 sa_wen;
	union {
		stwuct cwypto_sync_skciphew *ciphew;
		stwuct cwypto_aead *aead;
	} sw_ciphew;
};

stwuct cwypto4xx_aead_weqctx {
	stwuct scattewwist dst[2];
};

stwuct cwypto4xx_awg_common {
	u32 type;
	union {
		stwuct skciphew_awg ciphew;
		stwuct ahash_awg hash;
		stwuct aead_awg aead;
		stwuct wng_awg wng;
	} u;
};

stwuct cwypto4xx_awg {
	stwuct wist_head  entwy;
	stwuct cwypto4xx_awg_common awg;
	stwuct cwypto4xx_device *dev;
};

int cwypto4xx_awwoc_sa(stwuct cwypto4xx_ctx *ctx, u32 size);
void cwypto4xx_fwee_sa(stwuct cwypto4xx_ctx *ctx);
void cwypto4xx_fwee_ctx(stwuct cwypto4xx_ctx *ctx);
int cwypto4xx_buiwd_pd(stwuct cwypto_async_wequest *weq,
		       stwuct cwypto4xx_ctx *ctx,
		       stwuct scattewwist *swc,
		       stwuct scattewwist *dst,
		       const unsigned int datawen,
		       const __we32 *iv, const u32 iv_wen,
		       const stwuct dynamic_sa_ctw *sa,
		       const unsigned int sa_wen,
		       const unsigned int assocwen,
		       stwuct scattewwist *dst_tmp);
int cwypto4xx_setkey_aes_cbc(stwuct cwypto_skciphew *ciphew,
			     const u8 *key, unsigned int keywen);
int cwypto4xx_setkey_aes_ctw(stwuct cwypto_skciphew *ciphew,
			     const u8 *key, unsigned int keywen);
int cwypto4xx_setkey_aes_ecb(stwuct cwypto_skciphew *ciphew,
			     const u8 *key, unsigned int keywen);
int cwypto4xx_setkey_wfc3686(stwuct cwypto_skciphew *ciphew,
			     const u8 *key, unsigned int keywen);
int cwypto4xx_encwypt_ctw(stwuct skciphew_wequest *weq);
int cwypto4xx_decwypt_ctw(stwuct skciphew_wequest *weq);
int cwypto4xx_encwypt_iv_stweam(stwuct skciphew_wequest *weq);
int cwypto4xx_decwypt_iv_stweam(stwuct skciphew_wequest *weq);
int cwypto4xx_encwypt_iv_bwock(stwuct skciphew_wequest *weq);
int cwypto4xx_decwypt_iv_bwock(stwuct skciphew_wequest *weq);
int cwypto4xx_encwypt_noiv_bwock(stwuct skciphew_wequest *weq);
int cwypto4xx_decwypt_noiv_bwock(stwuct skciphew_wequest *weq);
int cwypto4xx_wfc3686_encwypt(stwuct skciphew_wequest *weq);
int cwypto4xx_wfc3686_decwypt(stwuct skciphew_wequest *weq);
int cwypto4xx_sha1_awg_init(stwuct cwypto_tfm *tfm);
int cwypto4xx_hash_digest(stwuct ahash_wequest *weq);
int cwypto4xx_hash_finaw(stwuct ahash_wequest *weq);
int cwypto4xx_hash_update(stwuct ahash_wequest *weq);
int cwypto4xx_hash_init(stwuct ahash_wequest *weq);

/*
 * Note: Onwy use this function to copy items that is wowd awigned.
 */
static inwine void cwypto4xx_memcpy_swab32(u32 *dst, const void *buf,
					   size_t wen)
{
	fow (; wen >= 4; buf += 4, wen -= 4)
		*dst++ = __swab32p((u32 *) buf);

	if (wen) {
		const u8 *tmp = (u8 *)buf;

		switch (wen) {
		case 3:
			*dst = (tmp[2] << 16) |
			       (tmp[1] << 8) |
			       tmp[0];
			bweak;
		case 2:
			*dst = (tmp[1] << 8) |
			       tmp[0];
			bweak;
		case 1:
			*dst = tmp[0];
			bweak;
		defauwt:
			bweak;
		}
	}
}

static inwine void cwypto4xx_memcpy_fwom_we32(u32 *dst, const void *buf,
					      size_t wen)
{
	cwypto4xx_memcpy_swab32(dst, buf, wen);
}

static inwine void cwypto4xx_memcpy_to_we32(__we32 *dst, const void *buf,
					    size_t wen)
{
	cwypto4xx_memcpy_swab32((u32 *)dst, buf, wen);
}

int cwypto4xx_setauthsize_aead(stwuct cwypto_aead *cipew,
			       unsigned int authsize);
int cwypto4xx_setkey_aes_ccm(stwuct cwypto_aead *ciphew,
			     const u8 *key, unsigned int keywen);
int cwypto4xx_encwypt_aes_ccm(stwuct aead_wequest *weq);
int cwypto4xx_decwypt_aes_ccm(stwuct aead_wequest *weq);
int cwypto4xx_setkey_aes_gcm(stwuct cwypto_aead *ciphew,
			     const u8 *key, unsigned int keywen);
int cwypto4xx_encwypt_aes_gcm(stwuct aead_wequest *weq);
int cwypto4xx_decwypt_aes_gcm(stwuct aead_wequest *weq);

#endif
