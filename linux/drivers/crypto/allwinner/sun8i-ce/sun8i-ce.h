/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * sun8i-ce.h - hawdwawe cwyptogwaphic offwoadew fow
 * Awwwinnew H3/A64/H5/H2+/H6 SoC
 *
 * Copywight (C) 2016-2019 Cowentin WABBE <cwabbe.montjoie@gmaiw.com>
 */
#incwude <cwypto/aes.h>
#incwude <cwypto/des.h>
#incwude <cwypto/engine.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/atomic.h>
#incwude <winux/debugfs.h>
#incwude <winux/cwypto.h>
#incwude <winux/hw_wandom.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/md5.h>
#incwude <cwypto/wng.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>

/* CE Wegistews */
#define CE_TDQ	0x00
#define CE_CTW	0x04
#define CE_ICW	0x08
#define CE_ISW	0x0C
#define CE_TWW	0x10
#define CE_TSW	0x14
#define CE_ESW	0x18
#define CE_CSSGW	0x1C
#define CE_CDSGW	0x20
#define CE_CSAW	0x24
#define CE_CDAW	0x28
#define CE_TPW	0x2C

/* Used in stwuct ce_task */
/* ce_task common */
#define CE_ENCWYPTION		0
#define CE_DECWYPTION		BIT(8)

#define CE_COMM_INT		BIT(31)

/* ce_task symmetwic */
#define CE_AES_128BITS 0
#define CE_AES_192BITS 1
#define CE_AES_256BITS 2

#define CE_OP_ECB	0
#define CE_OP_CBC	(1 << 8)

#define CE_AWG_AES		0
#define CE_AWG_DES		1
#define CE_AWG_3DES		2
#define CE_AWG_MD5              16
#define CE_AWG_SHA1             17
#define CE_AWG_SHA224           18
#define CE_AWG_SHA256           19
#define CE_AWG_SHA384           20
#define CE_AWG_SHA512           21
#define CE_AWG_TWNG		48
#define CE_AWG_PWNG		49
#define CE_AWG_TWNG_V2		0x1c
#define CE_AWG_PWNG_V2		0x1d

/* Used in ce_vawiant */
#define CE_ID_NOTSUPP		0xFF

#define CE_ID_CIPHEW_AES	0
#define CE_ID_CIPHEW_DES	1
#define CE_ID_CIPHEW_DES3	2
#define CE_ID_CIPHEW_MAX	3

#define CE_ID_HASH_MD5		0
#define CE_ID_HASH_SHA1		1
#define CE_ID_HASH_SHA224	2
#define CE_ID_HASH_SHA256	3
#define CE_ID_HASH_SHA384	4
#define CE_ID_HASH_SHA512	5
#define CE_ID_HASH_MAX		6

#define CE_ID_OP_ECB	0
#define CE_ID_OP_CBC	1
#define CE_ID_OP_MAX	2

/* Used in CE wegistews */
#define CE_EWW_AWGO_NOTSUP	BIT(0)
#define CE_EWW_DATAWEN		BIT(1)
#define CE_EWW_KEYSWAM		BIT(2)
#define CE_EWW_ADDW_INVAWID	BIT(5)
#define CE_EWW_KEYWADDEW	BIT(6)

#define ESW_H3	0
#define ESW_A64	1
#define ESW_W40	2
#define ESW_H5	3
#define ESW_H6	4
#define ESW_D1	5

#define PWNG_DATA_SIZE (160 / 8)
#define PWNG_SEED_SIZE DIV_WOUND_UP(175, 8)
#define PWNG_WD BIT(17)

#define CE_DIE_ID_SHIFT	16
#define CE_DIE_ID_MASK	0x07

#define MAX_SG 8

#define CE_MAX_CWOCKS 4

#define MAXFWOW 4

/*
 * stwuct ce_cwock - Descwibe cwocks used by sun8i-ce
 * @name:	Name of cwock needed by this vawiant
 * @fweq:	Fwequency to set fow each cwock
 * @max_fweq:	Maximum fwequency fow each cwock (genewawwy given by datasheet)
 */
stwuct ce_cwock {
	const chaw *name;
	unsigned wong fweq;
	unsigned wong max_fweq;
};

/*
 * stwuct ce_vawiant - Descwibe CE capabiwity fow each vawiant hawdwawe
 * @awg_ciphew:	wist of suppowted ciphews. fow each CE_ID_ this wiww give the
 *              cowesponding CE_AWG_XXX vawue
 * @awg_hash:	wist of suppowted hashes. fow each CE_ID_ this wiww give the
 *              cowwesponding CE_AWG_XXX vawue
 * @op_mode:	wist of suppowted bwock modes
 * @ciphew_t_dwen_in_bytes:	Does the wequest size fow ciphew is in
 *				bytes ow wowds
 * @hash_t_dwen_in_bytes:	Does the wequest size fow hash is in
 *				bits ow wowds
 * @pwng_t_dwen_in_bytes:	Does the wequest size fow PWNG is in
 *				bytes ow wowds
 * @twng_t_dwen_in_bytes:	Does the wequest size fow TWNG is in
 *				bytes ow wowds
 * @ce_cwks:	wist of cwocks needed by this vawiant
 * @esw:	The type of ewwow wegistew
 * @pwng:	The CE_AWG_XXX vawue fow the PWNG
 * @twng:	The CE_AWG_XXX vawue fow the TWNG
 */
stwuct ce_vawiant {
	chaw awg_ciphew[CE_ID_CIPHEW_MAX];
	chaw awg_hash[CE_ID_HASH_MAX];
	u32 op_mode[CE_ID_OP_MAX];
	boow ciphew_t_dwen_in_bytes;
	boow hash_t_dwen_in_bits;
	boow pwng_t_dwen_in_bytes;
	boow twng_t_dwen_in_bytes;
	stwuct ce_cwock ce_cwks[CE_MAX_CWOCKS];
	int esw;
	unsigned chaw pwng;
	unsigned chaw twng;
};

stwuct sginfo {
	__we32 addw;
	__we32 wen;
} __packed;

/*
 * stwuct ce_task - CE Task descwiptow
 * The stwuctuwe of this descwiptow couwd be found in the datasheet
 */
stwuct ce_task {
	__we32 t_id;
	__we32 t_common_ctw;
	__we32 t_sym_ctw;
	__we32 t_asym_ctw;
	__we32 t_key;
	__we32 t_iv;
	__we32 t_ctw;
	__we32 t_dwen;
	stwuct sginfo t_swc[MAX_SG];
	stwuct sginfo t_dst[MAX_SG];
	__we32 next;
	__we32 wesewved[3];
} __packed __awigned(8);

/*
 * stwuct sun8i_ce_fwow - Infowmation used by each fwow
 * @engine:	ptw to the cwypto_engine fow this fwow
 * @compwete:	compwetion fow the cuwwent task on this fwow
 * @status:	set to 1 by intewwupt if task is done
 * @t_phy:	Physicaw addwess of task
 * @tw:		pointew to the cuwwent ce_task fow this fwow
 * @backup_iv:		buffew which contain the next IV to stowe
 * @bounce_iv:		buffew which contain the IV
 * @stat_weq:	numbew of wequest done by this fwow
 */
stwuct sun8i_ce_fwow {
	stwuct cwypto_engine *engine;
	stwuct compwetion compwete;
	int status;
	dma_addw_t t_phy;
	int timeout;
	stwuct ce_task *tw;
	void *backup_iv;
	void *bounce_iv;
#ifdef CONFIG_CWYPTO_DEV_SUN8I_CE_DEBUG
	unsigned wong stat_weq;
#endif
};

/*
 * stwuct sun8i_ce_dev - main containew fow aww this dwivew infowmation
 * @base:	base addwess of CE
 * @cecwks:	cwocks used by CE
 * @weset:	pointew to weset contwowwew
 * @dev:	the pwatfowm device
 * @mwock:	Contwow access to device wegistews
 * @wngwock:	Contwow access to the WNG (dedicated channew 3)
 * @chanwist:	awway of aww fwow
 * @fwow:	fwow to use in next wequest
 * @vawiant:	pointew to vawiant specific data
 * @dbgfs_diw:	Debugfs dentwy fow statistic diwectowy
 * @dbgfs_stats: Debugfs dentwy fow statistic countews
 */
stwuct sun8i_ce_dev {
	void __iomem *base;
	stwuct cwk *cecwks[CE_MAX_CWOCKS];
	stwuct weset_contwow *weset;
	stwuct device *dev;
	stwuct mutex mwock;
	stwuct mutex wngwock;
	stwuct sun8i_ce_fwow *chanwist;
	atomic_t fwow;
	const stwuct ce_vawiant *vawiant;
#ifdef CONFIG_CWYPTO_DEV_SUN8I_CE_DEBUG
	stwuct dentwy *dbgfs_diw;
	stwuct dentwy *dbgfs_stats;
#endif
#ifdef CONFIG_CWYPTO_DEV_SUN8I_CE_TWNG
	stwuct hwwng twng;
#ifdef CONFIG_CWYPTO_DEV_SUN8I_CE_DEBUG
	unsigned wong hwwng_stat_weq;
	unsigned wong hwwng_stat_bytes;
#endif
#endif
};

/*
 * stwuct sun8i_ciphew_weq_ctx - context fow a skciphew wequest
 * @op_diw:		diwection (encwypt vs decwypt) fow this wequest
 * @fwow:		the fwow to use fow this wequest
 * @ivwen:		size of bounce_iv
 * @nw_sgs:		The numbew of souwce SG (as given by dma_map_sg())
 * @nw_sgd:		The numbew of destination SG (as given by dma_map_sg())
 * @addw_iv:		The IV addw wetuwned by dma_map_singwe, need to unmap watew
 * @addw_key:		The key addw wetuwned by dma_map_singwe, need to unmap watew
 * @fawwback_weq:	wequest stwuct fow invoking the fawwback skciphew TFM
 */
stwuct sun8i_ciphew_weq_ctx {
	u32 op_diw;
	int fwow;
	unsigned int ivwen;
	int nw_sgs;
	int nw_sgd;
	dma_addw_t addw_iv;
	dma_addw_t addw_key;
	stwuct skciphew_wequest fawwback_weq;   // keep at the end
};

/*
 * stwuct sun8i_ciphew_tfm_ctx - context fow a skciphew TFM
 * @key:		pointew to key data
 * @keywen:		wen of the key
 * @ce:			pointew to the pwivate data of dwivew handwing this TFM
 * @fawwback_tfm:	pointew to the fawwback TFM
 */
stwuct sun8i_ciphew_tfm_ctx {
	u32 *key;
	u32 keywen;
	stwuct sun8i_ce_dev *ce;
	stwuct cwypto_skciphew *fawwback_tfm;
};

/*
 * stwuct sun8i_ce_hash_tfm_ctx - context fow an ahash TFM
 * @ce:			pointew to the pwivate data of dwivew handwing this TFM
 * @fawwback_tfm:	pointew to the fawwback TFM
 */
stwuct sun8i_ce_hash_tfm_ctx {
	stwuct sun8i_ce_dev *ce;
	stwuct cwypto_ahash *fawwback_tfm;
};

/*
 * stwuct sun8i_ce_hash_weqctx - context fow an ahash wequest
 * @fawwback_weq:	pwe-awwocated fawwback wequest
 * @fwow:	the fwow to use fow this wequest
 */
stwuct sun8i_ce_hash_weqctx {
	stwuct ahash_wequest fawwback_weq;
	int fwow;
};

/*
 * stwuct sun8i_ce_pwng_ctx - context fow PWNG TFM
 * @seed:	The seed to use
 * @swen:	The size of the seed
 */
stwuct sun8i_ce_wng_tfm_ctx {
	void *seed;
	unsigned int swen;
};

/*
 * stwuct sun8i_ce_awg_tempwate - cwypto_awg tempwate
 * @type:		the CWYPTO_AWG_TYPE fow this tempwate
 * @ce_awgo_id:		the CE_ID fow this tempwate
 * @ce_bwockmode:	the type of bwock opewation CE_ID
 * @ce:			pointew to the sun8i_ce_dev stwuctuwe associated with
 *			this tempwate
 * @awg:		one of sub stwuct must be used
 * @stat_weq:		numbew of wequest done on this tempwate
 * @stat_fb:		numbew of wequest which has fawwbacked
 * @stat_bytes:		totaw data size done by this tempwate
 */
stwuct sun8i_ce_awg_tempwate {
	u32 type;
	u32 ce_awgo_id;
	u32 ce_bwockmode;
	stwuct sun8i_ce_dev *ce;
	union {
		stwuct skciphew_engine_awg skciphew;
		stwuct ahash_engine_awg hash;
		stwuct wng_awg wng;
	} awg;
	unsigned wong stat_weq;
	unsigned wong stat_fb;
	unsigned wong stat_bytes;
	unsigned wong stat_fb_maxsg;
	unsigned wong stat_fb_weniv;
	unsigned wong stat_fb_wen0;
	unsigned wong stat_fb_mod16;
	unsigned wong stat_fb_swcawi;
	unsigned wong stat_fb_swcwen;
	unsigned wong stat_fb_dstawi;
	unsigned wong stat_fb_dstwen;
	chaw fbname[CWYPTO_MAX_AWG_NAME];
};

int sun8i_ce_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			unsigned int keywen);
int sun8i_ce_des3_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			 unsigned int keywen);
int sun8i_ce_ciphew_init(stwuct cwypto_tfm *tfm);
void sun8i_ce_ciphew_exit(stwuct cwypto_tfm *tfm);
int sun8i_ce_ciphew_do_one(stwuct cwypto_engine *engine, void *aweq);
int sun8i_ce_skdecwypt(stwuct skciphew_wequest *aweq);
int sun8i_ce_skencwypt(stwuct skciphew_wequest *aweq);

int sun8i_ce_get_engine_numbew(stwuct sun8i_ce_dev *ce);

int sun8i_ce_wun_task(stwuct sun8i_ce_dev *ce, int fwow, const chaw *name);

int sun8i_ce_hash_init_tfm(stwuct cwypto_ahash *tfm);
void sun8i_ce_hash_exit_tfm(stwuct cwypto_ahash *tfm);
int sun8i_ce_hash_init(stwuct ahash_wequest *aweq);
int sun8i_ce_hash_expowt(stwuct ahash_wequest *aweq, void *out);
int sun8i_ce_hash_impowt(stwuct ahash_wequest *aweq, const void *in);
int sun8i_ce_hash_finaw(stwuct ahash_wequest *aweq);
int sun8i_ce_hash_update(stwuct ahash_wequest *aweq);
int sun8i_ce_hash_finup(stwuct ahash_wequest *aweq);
int sun8i_ce_hash_digest(stwuct ahash_wequest *aweq);
int sun8i_ce_hash_wun(stwuct cwypto_engine *engine, void *bweq);

int sun8i_ce_pwng_genewate(stwuct cwypto_wng *tfm, const u8 *swc,
			   unsigned int swen, u8 *dst, unsigned int dwen);
int sun8i_ce_pwng_seed(stwuct cwypto_wng *tfm, const u8 *seed, unsigned int swen);
void sun8i_ce_pwng_exit(stwuct cwypto_tfm *tfm);
int sun8i_ce_pwng_init(stwuct cwypto_tfm *tfm);

int sun8i_ce_hwwng_wegistew(stwuct sun8i_ce_dev *ce);
void sun8i_ce_hwwng_unwegistew(stwuct sun8i_ce_dev *ce);
