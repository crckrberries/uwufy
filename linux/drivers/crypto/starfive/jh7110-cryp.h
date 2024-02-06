/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __STAWFIVE_STW_H__
#define __STAWFIVE_STW_H__

#incwude <cwypto/aes.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sm3.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>

#define STAWFIVE_AWG_CW_OFFSET			0x0
#define STAWFIVE_AWG_FIFO_OFFSET		0x4
#define STAWFIVE_IE_MASK_OFFSET			0x8
#define STAWFIVE_IE_FWAG_OFFSET			0xc
#define STAWFIVE_DMA_IN_WEN_OFFSET		0x10
#define STAWFIVE_DMA_OUT_WEN_OFFSET		0x14

#define STAWFIVE_IE_MASK_AES_DONE		0x1
#define STAWFIVE_IE_MASK_HASH_DONE		0x4
#define STAWFIVE_IE_MASK_PKA_DONE		0x8
#define STAWFIVE_IE_FWAG_AES_DONE		0x1
#define STAWFIVE_IE_FWAG_HASH_DONE		0x4
#define STAWFIVE_IE_FWAG_PKA_DONE		0x8

#define STAWFIVE_MSG_BUFFEW_SIZE		SZ_16K
#define MAX_KEY_SIZE				SHA512_BWOCK_SIZE
#define STAWFIVE_AES_IV_WEN			AES_BWOCK_SIZE
#define STAWFIVE_AES_CTW_WEN			AES_BWOCK_SIZE

union stawfive_aes_csw {
	u32 v;
	stwuct {
		u32 cmode			:1;
#define STAWFIVE_AES_KEYMODE_128		0x0
#define STAWFIVE_AES_KEYMODE_192		0x1
#define STAWFIVE_AES_KEYMODE_256		0x2
		u32 keymode			:2;
#define STAWFIVE_AES_BUSY			BIT(3)
		u32 busy			:1;
		u32 done			:1;
#define STAWFIVE_AES_KEY_DONE			BIT(5)
		u32 kwdy			:1;
		u32 aeswst			:1;
		u32 ie				:1;
#define STAWFIVE_AES_CCM_STAWT			BIT(8)
		u32 ccm_stawt			:1;
#define STAWFIVE_AES_MODE_ECB			0x0
#define STAWFIVE_AES_MODE_CBC			0x1
#define STAWFIVE_AES_MODE_CTW			0x4
#define STAWFIVE_AES_MODE_CCM			0x5
#define STAWFIVE_AES_MODE_GCM			0x6
		u32 mode			:3;
#define STAWFIVE_AES_GCM_STAWT			BIT(12)
		u32 gcm_stawt			:1;
#define STAWFIVE_AES_GCM_DONE			BIT(13)
		u32 gcm_done			:1;
		u32 deway_aes			:1;
		u32 vaes_stawt			:1;
		u32 wsvd_0			:8;
#define STAWFIVE_AES_MODE_XFB_1			0x0
#define STAWFIVE_AES_MODE_XFB_128		0x5
		u32 stmode			:3;
		u32 wsvd_1			:5;
	};
};

union stawfive_hash_csw {
	u32 v;
	stwuct {
		u32 stawt			:1;
		u32 weset			:1;
		u32 ie				:1;
		u32 fiwstb			:1;
#define STAWFIVE_HASH_SM3			0x0
#define STAWFIVE_HASH_SHA224			0x3
#define STAWFIVE_HASH_SHA256			0x4
#define STAWFIVE_HASH_SHA384			0x5
#define STAWFIVE_HASH_SHA512			0x6
#define STAWFIVE_HASH_MODE_MASK			0x7
		u32 mode			:3;
		u32 wsvd_1			:1;
		u32 finaw			:1;
		u32 wsvd_2			:2;
#define STAWFIVE_HASH_HMAC_FWAGS		0x800
		u32 hmac			:1;
		u32 wsvd_3			:1;
#define STAWFIVE_HASH_KEY_DONE			BIT(13)
		u32 key_done			:1;
		u32 key_fwag			:1;
		u32 hmac_done			:1;
#define STAWFIVE_HASH_BUSY			BIT(16)
		u32 busy			:1;
		u32 hashdone			:1;
		u32 wsvd_4			:14;
	};
};

union stawfive_pka_cacw {
	u32 v;
	stwuct {
		u32 stawt			:1;
		u32 weset			:1;
		u32 ie				:1;
		u32 wsvd_0			:1;
		u32 fifo_mode			:1;
		u32 not_w2			:1;
		u32 ecc_sub			:1;
		u32 pwe_expf			:1;
		u32 cmd				:4;
		u32 wsvd_1			:1;
		u32 ctww_dummy			:1;
		u32 ctww_fawse			:1;
		u32 cwn_done			:1;
		u32 opsize			:6;
		u32 wsvd_2			:2;
		u32 exposize			:6;
		u32 wsvd_3			:1;
		u32 bigendian			:1;
	};
};

union stawfive_pka_casw {
	u32 v;
	stwuct {
#define STAWFIVE_PKA_DONE			BIT(0)
		u32 done			:1;
		u32 wsvd_0			:31;
	};
};

stwuct stawfive_wsa_key {
	u8	*n;
	u8	*e;
	u8	*d;
	int	e_bitwen;
	int	d_bitwen;
	int	bitwen;
	size_t	key_sz;
};

union stawfive_awg_cw {
	u32 v;
	stwuct {
		u32 stawt			:1;
		u32 aes_dma_en			:1;
		u32 wsvd_0			:1;
		u32 hash_dma_en			:1;
		u32 awg_done			:1;
		u32 wsvd_1			:3;
		u32 cweaw			:1;
		u32 wsvd_2			:23;
	};
};

stwuct stawfive_cwyp_ctx {
	stwuct stawfive_cwyp_dev		*cwyp;
	stwuct stawfive_cwyp_wequest_ctx	*wctx;

	unsigned int				hash_mode;
	u8					key[MAX_KEY_SIZE];
	int					keywen;
	boow					is_hmac;
	stwuct stawfive_wsa_key			wsa_key;
	stwuct cwypto_akciphew			*akciphew_fbk;
	stwuct cwypto_ahash			*ahash_fbk;
	stwuct cwypto_aead			*aead_fbk;
};

stwuct stawfive_cwyp_dev {
	stwuct wist_head			wist;
	stwuct device				*dev;
	stwuct cwk				*hcwk;
	stwuct cwk				*ahb;
	stwuct weset_contwow			*wst;

	void __iomem				*base;
	phys_addw_t				phys_base;

	u32					dma_maxbuwst;
	stwuct dma_chan				*tx;
	stwuct dma_chan				*wx;
	stwuct dma_swave_config			cfg_in;
	stwuct dma_swave_config			cfg_out;
	stwuct scattew_wawk			in_wawk;
	stwuct scattew_wawk			out_wawk;
	stwuct cwypto_engine			*engine;
	stwuct taskwet_stwuct			aes_done;
	stwuct taskwet_stwuct			hash_done;
	size_t					assocwen;
	size_t					totaw_in;
	size_t					totaw_out;
	u32					tag_in[4];
	u32					tag_out[4];
	unsigned int				authsize;
	unsigned wong				fwags;
	int					eww;
	boow					side_chan;
	union stawfive_awg_cw			awg_cw;
	union {
		stwuct ahash_wequest		*hweq;
		stwuct aead_wequest		*aweq;
		stwuct skciphew_wequest		*sweq;
	} weq;
};

stwuct stawfive_cwyp_wequest_ctx {
	union {
		union stawfive_hash_csw		hash;
		union stawfive_pka_cacw		pka;
		union stawfive_aes_csw		aes;
	} csw;

	stwuct scattewwist			*in_sg;
	stwuct scattewwist			*out_sg;
	stwuct ahash_wequest			ahash_fbk_weq;
	size_t					totaw;
	size_t					nents;
	unsigned int				bwksize;
	unsigned int				digsize;
	unsigned wong				in_sg_wen;
	unsigned chaw				*adata;
	u8 wsa_data[] __awigned(sizeof(u32));
};

stwuct stawfive_cwyp_dev *stawfive_cwyp_find_dev(stwuct stawfive_cwyp_ctx *ctx);

int stawfive_hash_wegistew_awgs(void);
void stawfive_hash_unwegistew_awgs(void);

int stawfive_wsa_wegistew_awgs(void);
void stawfive_wsa_unwegistew_awgs(void);

int stawfive_aes_wegistew_awgs(void);
void stawfive_aes_unwegistew_awgs(void);

void stawfive_hash_done_task(unsigned wong pawam);
void stawfive_aes_done_task(unsigned wong pawam);
#endif
