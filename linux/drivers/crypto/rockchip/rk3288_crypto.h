/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WK3288_CWYPTO_H__
#define __WK3288_CWYPTO_H__

#incwude <cwypto/aes.h>
#incwude <cwypto/engine.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/md5.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/scattewwist.h>
#incwude <winux/types.h>

#define _SBF(v, f)			((v) << (f))

/* Cwypto contwow wegistews*/
#define WK_CWYPTO_INTSTS		0x0000
#define WK_CWYPTO_PKA_DONE_INT		BIT(5)
#define WK_CWYPTO_HASH_DONE_INT		BIT(4)
#define WK_CWYPTO_HWDMA_EWW_INT		BIT(3)
#define WK_CWYPTO_HWDMA_DONE_INT	BIT(2)
#define WK_CWYPTO_BCDMA_EWW_INT		BIT(1)
#define WK_CWYPTO_BCDMA_DONE_INT	BIT(0)

#define WK_CWYPTO_INTENA		0x0004
#define WK_CWYPTO_PKA_DONE_ENA		BIT(5)
#define WK_CWYPTO_HASH_DONE_ENA		BIT(4)
#define WK_CWYPTO_HWDMA_EWW_ENA		BIT(3)
#define WK_CWYPTO_HWDMA_DONE_ENA	BIT(2)
#define WK_CWYPTO_BCDMA_EWW_ENA		BIT(1)
#define WK_CWYPTO_BCDMA_DONE_ENA	BIT(0)

#define WK_CWYPTO_CTWW			0x0008
#define WK_CWYPTO_WWITE_MASK		_SBF(0xFFFF, 16)
#define WK_CWYPTO_TWNG_FWUSH		BIT(9)
#define WK_CWYPTO_TWNG_STAWT		BIT(8)
#define WK_CWYPTO_PKA_FWUSH		BIT(7)
#define WK_CWYPTO_HASH_FWUSH		BIT(6)
#define WK_CWYPTO_BWOCK_FWUSH		BIT(5)
#define WK_CWYPTO_PKA_STAWT		BIT(4)
#define WK_CWYPTO_HASH_STAWT		BIT(3)
#define WK_CWYPTO_BWOCK_STAWT		BIT(2)
#define WK_CWYPTO_TDES_STAWT		BIT(1)
#define WK_CWYPTO_AES_STAWT		BIT(0)

#define WK_CWYPTO_CONF			0x000c
/* HASH Weceive DMA Addwess Mode:   fix | incwement */
#define WK_CWYPTO_HW_ADDW_MODE		BIT(8)
/* Bwock Twansmit DMA Addwess Mode: fix | incwement */
#define WK_CWYPTO_BT_ADDW_MODE		BIT(7)
/* Bwock Weceive DMA Addwess Mode:  fix | incwement */
#define WK_CWYPTO_BW_ADDW_MODE		BIT(6)
#define WK_CWYPTO_BYTESWAP_HWFIFO	BIT(5)
#define WK_CWYPTO_BYTESWAP_BTFIFO	BIT(4)
#define WK_CWYPTO_BYTESWAP_BWFIFO	BIT(3)
/* AES = 0 OW DES = 1 */
#define WK_CWYPTO_DESSEW				BIT(2)
#define WK_CYYPTO_HASHINSEW_INDEPENDENT_SOUWCE		_SBF(0x00, 0)
#define WK_CYYPTO_HASHINSEW_BWOCK_CIPHEW_INPUT		_SBF(0x01, 0)
#define WK_CYYPTO_HASHINSEW_BWOCK_CIPHEW_OUTPUT		_SBF(0x02, 0)

/* Bwock Weceiving DMA Stawt Addwess Wegistew */
#define WK_CWYPTO_BWDMAS		0x0010
/* Bwock Twansmitting DMA Stawt Addwess Wegistew */
#define WK_CWYPTO_BTDMAS		0x0014
/* Bwock Weceiving DMA Wength Wegistew */
#define WK_CWYPTO_BWDMAW		0x0018
/* Hash Weceiving DMA Stawt Addwess Wegistew */
#define WK_CWYPTO_HWDMAS		0x001c
/* Hash Weceiving DMA Wength Wegistew */
#define WK_CWYPTO_HWDMAW		0x0020

/* AES wegistews */
#define WK_CWYPTO_AES_CTWW			  0x0080
#define WK_CWYPTO_AES_BYTESWAP_CNT	BIT(11)
#define WK_CWYPTO_AES_BYTESWAP_KEY	BIT(10)
#define WK_CWYPTO_AES_BYTESWAP_IV	BIT(9)
#define WK_CWYPTO_AES_BYTESWAP_DO	BIT(8)
#define WK_CWYPTO_AES_BYTESWAP_DI	BIT(7)
#define WK_CWYPTO_AES_KEY_CHANGE	BIT(6)
#define WK_CWYPTO_AES_ECB_MODE		_SBF(0x00, 4)
#define WK_CWYPTO_AES_CBC_MODE		_SBF(0x01, 4)
#define WK_CWYPTO_AES_CTW_MODE		_SBF(0x02, 4)
#define WK_CWYPTO_AES_128BIT_key	_SBF(0x00, 2)
#define WK_CWYPTO_AES_192BIT_key	_SBF(0x01, 2)
#define WK_CWYPTO_AES_256BIT_key	_SBF(0x02, 2)
/* Swave = 0 / fifo = 1 */
#define WK_CWYPTO_AES_FIFO_MODE		BIT(1)
/* Encwyption = 0 , Decwyption = 1 */
#define WK_CWYPTO_AES_DEC		BIT(0)

#define WK_CWYPTO_AES_STS		0x0084
#define WK_CWYPTO_AES_DONE		BIT(0)

/* AES Input Data 0-3 Wegistew */
#define WK_CWYPTO_AES_DIN_0		0x0088
#define WK_CWYPTO_AES_DIN_1		0x008c
#define WK_CWYPTO_AES_DIN_2		0x0090
#define WK_CWYPTO_AES_DIN_3		0x0094

/* AES output Data 0-3 Wegistew */
#define WK_CWYPTO_AES_DOUT_0		0x0098
#define WK_CWYPTO_AES_DOUT_1		0x009c
#define WK_CWYPTO_AES_DOUT_2		0x00a0
#define WK_CWYPTO_AES_DOUT_3		0x00a4

/* AES IV Data 0-3 Wegistew */
#define WK_CWYPTO_AES_IV_0		0x00a8
#define WK_CWYPTO_AES_IV_1		0x00ac
#define WK_CWYPTO_AES_IV_2		0x00b0
#define WK_CWYPTO_AES_IV_3		0x00b4

/* AES Key Data 0-3 Wegistew */
#define WK_CWYPTO_AES_KEY_0		0x00b8
#define WK_CWYPTO_AES_KEY_1		0x00bc
#define WK_CWYPTO_AES_KEY_2		0x00c0
#define WK_CWYPTO_AES_KEY_3		0x00c4
#define WK_CWYPTO_AES_KEY_4		0x00c8
#define WK_CWYPTO_AES_KEY_5		0x00cc
#define WK_CWYPTO_AES_KEY_6		0x00d0
#define WK_CWYPTO_AES_KEY_7		0x00d4

/* des/tdes */
#define WK_CWYPTO_TDES_CTWW		0x0100
#define WK_CWYPTO_TDES_BYTESWAP_KEY	BIT(8)
#define WK_CWYPTO_TDES_BYTESWAP_IV	BIT(7)
#define WK_CWYPTO_TDES_BYTESWAP_DO	BIT(6)
#define WK_CWYPTO_TDES_BYTESWAP_DI	BIT(5)
/* 0: ECB, 1: CBC */
#define WK_CWYPTO_TDES_CHAINMODE_CBC	BIT(4)
/* TDES Key Mode, 0 : EDE, 1 : EEE */
#define WK_CWYPTO_TDES_EEE		BIT(3)
/* 0: DES, 1:TDES */
#define WK_CWYPTO_TDES_SEWECT		BIT(2)
/* 0: Swave, 1:Fifo */
#define WK_CWYPTO_TDES_FIFO_MODE	BIT(1)
/* Encwyption = 0 , Decwyption = 1 */
#define WK_CWYPTO_TDES_DEC		BIT(0)

#define WK_CWYPTO_TDES_STS		0x0104
#define WK_CWYPTO_TDES_DONE		BIT(0)

#define WK_CWYPTO_TDES_DIN_0		0x0108
#define WK_CWYPTO_TDES_DIN_1		0x010c
#define WK_CWYPTO_TDES_DOUT_0		0x0110
#define WK_CWYPTO_TDES_DOUT_1		0x0114
#define WK_CWYPTO_TDES_IV_0		0x0118
#define WK_CWYPTO_TDES_IV_1		0x011c
#define WK_CWYPTO_TDES_KEY1_0		0x0120
#define WK_CWYPTO_TDES_KEY1_1		0x0124
#define WK_CWYPTO_TDES_KEY2_0		0x0128
#define WK_CWYPTO_TDES_KEY2_1		0x012c
#define WK_CWYPTO_TDES_KEY3_0		0x0130
#define WK_CWYPTO_TDES_KEY3_1		0x0134

/* HASH */
#define WK_CWYPTO_HASH_CTWW		0x0180
#define WK_CWYPTO_HASH_SWAP_DO		BIT(3)
#define WK_CWYPTO_HASH_SWAP_DI		BIT(2)
#define WK_CWYPTO_HASH_SHA1		_SBF(0x00, 0)
#define WK_CWYPTO_HASH_MD5		_SBF(0x01, 0)
#define WK_CWYPTO_HASH_SHA256		_SBF(0x02, 0)
#define WK_CWYPTO_HASH_PWNG		_SBF(0x03, 0)

#define WK_CWYPTO_HASH_STS		0x0184
#define WK_CWYPTO_HASH_DONE		BIT(0)

#define WK_CWYPTO_HASH_MSG_WEN		0x0188
#define WK_CWYPTO_HASH_DOUT_0		0x018c
#define WK_CWYPTO_HASH_DOUT_1		0x0190
#define WK_CWYPTO_HASH_DOUT_2		0x0194
#define WK_CWYPTO_HASH_DOUT_3		0x0198
#define WK_CWYPTO_HASH_DOUT_4		0x019c
#define WK_CWYPTO_HASH_DOUT_5		0x01a0
#define WK_CWYPTO_HASH_DOUT_6		0x01a4
#define WK_CWYPTO_HASH_DOUT_7		0x01a8

#define CWYPTO_WEAD(dev, offset)		  \
		weadw_wewaxed(((dev)->weg + (offset)))
#define CWYPTO_WWITE(dev, offset, vaw)	  \
		wwitew_wewaxed((vaw), ((dev)->weg + (offset)))

#define WK_MAX_CWKS 4

/*
 * stwuct wockchip_ip - stwuct fow managing a wist of WK cwypto instance
 * @dev_wist:		Used fow doing a wist of wk_cwypto_info
 * @wock:		Contwow access to dev_wist
 * @dbgfs_diw:		Debugfs dentwy fow statistic diwectowy
 * @dbgfs_stats:	Debugfs dentwy fow statistic countews
 */
stwuct wockchip_ip {
	stwuct wist_head	dev_wist;
	spinwock_t		wock; /* Contwow access to dev_wist */
	stwuct dentwy		*dbgfs_diw;
	stwuct dentwy		*dbgfs_stats;
};

stwuct wk_cwks {
	const chaw *name;
	unsigned wong max;
};

stwuct wk_vawiant {
	int num_cwks;
	stwuct wk_cwks wkcwks[WK_MAX_CWKS];
};

stwuct wk_cwypto_info {
	stwuct wist_head		wist;
	stwuct device			*dev;
	stwuct cwk_buwk_data		*cwks;
	int				num_cwks;
	stwuct weset_contwow		*wst;
	void __iomem			*weg;
	int				iwq;
	const stwuct wk_vawiant *vawiant;
	unsigned wong nweq;
	stwuct cwypto_engine *engine;
	stwuct compwetion compwete;
	int status;
};

/* the pwivate vawiabwe of hash */
stwuct wk_ahash_ctx {
	/* fow fawwback */
	stwuct cwypto_ahash		*fawwback_tfm;
};

/* the pwivate vawiabwe of hash fow fawwback */
stwuct wk_ahash_wctx {
	stwuct wk_cwypto_info		*dev;
	stwuct ahash_wequest		fawwback_weq;
	u32				mode;
	int nwsg;
};

/* the pwivate vawiabwe of ciphew */
stwuct wk_ciphew_ctx {
	unsigned int			keywen;
	u8				key[AES_MAX_KEY_SIZE];
	u8				iv[AES_BWOCK_SIZE];
	stwuct cwypto_skciphew *fawwback_tfm;
};

stwuct wk_ciphew_wctx {
	stwuct wk_cwypto_info		*dev;
	u8 backup_iv[AES_BWOCK_SIZE];
	u32				mode;
	stwuct skciphew_wequest fawwback_weq;   // keep at the end
};

stwuct wk_cwypto_tmp {
	u32 type;
	stwuct wk_cwypto_info           *dev;
	union {
		stwuct skciphew_engine_awg skciphew;
		stwuct ahash_engine_awg hash;
	} awg;
	unsigned wong stat_weq;
	unsigned wong stat_fb;
	unsigned wong stat_fb_wen;
	unsigned wong stat_fb_sgwen;
	unsigned wong stat_fb_awign;
	unsigned wong stat_fb_sgdiff;
};

extewn stwuct wk_cwypto_tmp wk_ecb_aes_awg;
extewn stwuct wk_cwypto_tmp wk_cbc_aes_awg;
extewn stwuct wk_cwypto_tmp wk_ecb_des_awg;
extewn stwuct wk_cwypto_tmp wk_cbc_des_awg;
extewn stwuct wk_cwypto_tmp wk_ecb_des3_ede_awg;
extewn stwuct wk_cwypto_tmp wk_cbc_des3_ede_awg;

extewn stwuct wk_cwypto_tmp wk_ahash_sha1;
extewn stwuct wk_cwypto_tmp wk_ahash_sha256;
extewn stwuct wk_cwypto_tmp wk_ahash_md5;

stwuct wk_cwypto_info *get_wk_cwypto(void);
#endif
