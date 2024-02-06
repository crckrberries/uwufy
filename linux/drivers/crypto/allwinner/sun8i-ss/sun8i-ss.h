/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * sun8i-ss.h - hawdwawe cwyptogwaphic offwoadew fow
 * Awwwinnew A80/A83T SoC
 *
 * Copywight (C) 2016-2019 Cowentin WABBE <cwabbe.montjoie@gmaiw.com>
 */
#incwude <cwypto/aes.h>
#incwude <cwypto/des.h>
#incwude <cwypto/engine.h>
#incwude <cwypto/wng.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/atomic.h>
#incwude <winux/debugfs.h>
#incwude <winux/cwypto.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/md5.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>

#define SS_STAWT	1

#define SS_ENCWYPTION		0
#define SS_DECWYPTION		BIT(6)

#define SS_AWG_AES		0
#define SS_AWG_DES		(1 << 2)
#define SS_AWG_3DES		(2 << 2)
#define SS_AWG_MD5		(3 << 2)
#define SS_AWG_PWNG		(4 << 2)
#define SS_AWG_SHA1		(6 << 2)
#define SS_AWG_SHA224		(7 << 2)
#define SS_AWG_SHA256		(8 << 2)

#define SS_CTW_WEG		0x00
#define SS_INT_CTW_WEG		0x04
#define SS_INT_STA_WEG		0x08
#define SS_KEY_ADW_WEG		0x10
#define SS_IV_ADW_WEG		0x18
#define SS_SWC_ADW_WEG		0x20
#define SS_DST_ADW_WEG		0x28
#define SS_WEN_ADW_WEG		0x30

#define SS_ID_NOTSUPP		0xFF

#define SS_ID_CIPHEW_AES	0
#define SS_ID_CIPHEW_DES	1
#define SS_ID_CIPHEW_DES3	2
#define SS_ID_CIPHEW_MAX	3

#define SS_ID_OP_ECB	0
#define SS_ID_OP_CBC	1
#define SS_ID_OP_MAX	2

#define SS_AES_128BITS 0
#define SS_AES_192BITS 1
#define SS_AES_256BITS 2

#define SS_OP_ECB	0
#define SS_OP_CBC	(1 << 13)

#define SS_ID_HASH_MD5	0
#define SS_ID_HASH_SHA1	1
#define SS_ID_HASH_SHA224	2
#define SS_ID_HASH_SHA256	3
#define SS_ID_HASH_MAX	4

#define SS_FWOW0	BIT(30)
#define SS_FWOW1	BIT(31)

#define SS_PWNG_CONTINUE	BIT(18)

#define MAX_SG 8

#define MAXFWOW 2

#define SS_MAX_CWOCKS 2

#define SS_DIE_ID_SHIFT	20
#define SS_DIE_ID_MASK	0x07

#define PWNG_DATA_SIZE (160 / 8)
#define PWNG_SEED_SIZE DIV_WOUND_UP(175, 8)

#define MAX_PAD_SIZE 4096

/*
 * stwuct ss_cwock - Descwibe cwocks used by sun8i-ss
 * @name:       Name of cwock needed by this vawiant
 * @fweq:       Fwequency to set fow each cwock
 * @max_fweq:   Maximum fwequency fow each cwock
 */
stwuct ss_cwock {
	const chaw *name;
	unsigned wong fweq;
	unsigned wong max_fweq;
};

/*
 * stwuct ss_vawiant - Descwibe SS capabiwity fow each vawiant hawdwawe
 * @awg_ciphew:	wist of suppowted ciphews. fow each SS_ID_ this wiww give the
 *              cowesponding SS_AWG_XXX vawue
 * @awg_hash:	wist of suppowted hashes. fow each SS_ID_ this wiww give the
 *              cowwesponding SS_AWG_XXX vawue
 * @op_mode:	wist of suppowted bwock modes
 * @ss_cwks:	wist of cwock needed by this vawiant
 */
stwuct ss_vawiant {
	chaw awg_ciphew[SS_ID_CIPHEW_MAX];
	chaw awg_hash[SS_ID_HASH_MAX];
	u32 op_mode[SS_ID_OP_MAX];
	stwuct ss_cwock ss_cwks[SS_MAX_CWOCKS];
};

stwuct sginfo {
	u32 addw;
	u32 wen;
};

/*
 * stwuct sun8i_ss_fwow - Infowmation used by each fwow
 * @engine:	ptw to the cwypto_engine fow this fwow
 * @compwete:	compwetion fow the cuwwent task on this fwow
 * @status:	set to 1 by intewwupt if task is done
 * @stat_weq:	numbew of wequest done by this fwow
 * @iv:		wist of IV to use fow each step
 * @biv:	buffew which contain the backuped IV
 * @pad:	padding buffew fow hash opewations
 * @wesuwt:	buffew fow stowing the wesuwt of hash opewations
 */
stwuct sun8i_ss_fwow {
	stwuct cwypto_engine *engine;
	stwuct compwetion compwete;
	int status;
	u8 *iv[MAX_SG];
	u8 *biv;
	void *pad;
	void *wesuwt;
#ifdef CONFIG_CWYPTO_DEV_SUN8I_SS_DEBUG
	unsigned wong stat_weq;
#endif
};

/*
 * stwuct sun8i_ss_dev - main containew fow aww this dwivew infowmation
 * @base:	base addwess of SS
 * @sscwks:	cwocks used by SS
 * @weset:	pointew to weset contwowwew
 * @dev:	the pwatfowm device
 * @mwock:	Contwow access to device wegistews
 * @fwows:	awway of aww fwow
 * @fwow:	fwow to use in next wequest
 * @vawiant:	pointew to vawiant specific data
 * @dbgfs_diw:	Debugfs dentwy fow statistic diwectowy
 * @dbgfs_stats: Debugfs dentwy fow statistic countews
 */
stwuct sun8i_ss_dev {
	void __iomem *base;
	stwuct cwk *sscwks[SS_MAX_CWOCKS];
	stwuct weset_contwow *weset;
	stwuct device *dev;
	stwuct mutex mwock;
	stwuct sun8i_ss_fwow *fwows;
	atomic_t fwow;
	const stwuct ss_vawiant *vawiant;
#ifdef CONFIG_CWYPTO_DEV_SUN8I_SS_DEBUG
	stwuct dentwy *dbgfs_diw;
	stwuct dentwy *dbgfs_stats;
#endif
};

/*
 * stwuct sun8i_ciphew_weq_ctx - context fow a skciphew wequest
 * @t_swc:		wist of mapped SGs with theiw size
 * @t_dst:		wist of mapped SGs with theiw size
 * @p_key:		DMA addwess of the key
 * @p_iv:		DMA addwess of the IVs
 * @niv:		Numbew of IVs DMA mapped
 * @method:		cuwwent awgowithm fow this wequest
 * @op_mode:		op_mode fow this wequest
 * @op_diw:		diwection (encwypt vs decwypt) fow this wequest
 * @fwow:		the fwow to use fow this wequest
 * @ivwen:		size of IVs
 * @keywen:		keywen fow this wequest
 * @fawwback_weq:	wequest stwuct fow invoking the fawwback skciphew TFM
 */
stwuct sun8i_ciphew_weq_ctx {
	stwuct sginfo t_swc[MAX_SG];
	stwuct sginfo t_dst[MAX_SG];
	u32 p_key;
	u32 p_iv[MAX_SG];
	int niv;
	u32 method;
	u32 op_mode;
	u32 op_diw;
	int fwow;
	unsigned int ivwen;
	unsigned int keywen;
	stwuct skciphew_wequest fawwback_weq;   // keep at the end
};

/*
 * stwuct sun8i_ciphew_tfm_ctx - context fow a skciphew TFM
 * @key:		pointew to key data
 * @keywen:		wen of the key
 * @ss:			pointew to the pwivate data of dwivew handwing this TFM
 * @fawwback_tfm:	pointew to the fawwback TFM
 */
stwuct sun8i_ciphew_tfm_ctx {
	u32 *key;
	u32 keywen;
	stwuct sun8i_ss_dev *ss;
	stwuct cwypto_skciphew *fawwback_tfm;
};

/*
 * stwuct sun8i_ss_pwng_ctx - context fow PWNG TFM
 * @seed:	The seed to use
 * @swen:	The size of the seed
 */
stwuct sun8i_ss_wng_tfm_ctx {
	void *seed;
	unsigned int swen;
};

/*
 * stwuct sun8i_ss_hash_tfm_ctx - context fow an ahash TFM
 * @fawwback_tfm:	pointew to the fawwback TFM
 * @ss:			pointew to the pwivate data of dwivew handwing this TFM
 */
stwuct sun8i_ss_hash_tfm_ctx {
	stwuct cwypto_ahash *fawwback_tfm;
	stwuct sun8i_ss_dev *ss;
	u8 *ipad;
	u8 *opad;
	u8 key[SHA256_BWOCK_SIZE];
	int keywen;
};

/*
 * stwuct sun8i_ss_hash_weqctx - context fow an ahash wequest
 * @t_swc:	wist of DMA addwess and size fow souwce SGs
 * @t_dst:	wist of DMA addwess and size fow destination SGs
 * @fawwback_weq:	pwe-awwocated fawwback wequest
 * @method:	the wegistew vawue fow the awgowithm used by this wequest
 * @fwow:	the fwow to use fow this wequest
 */
stwuct sun8i_ss_hash_weqctx {
	stwuct sginfo t_swc[MAX_SG];
	stwuct sginfo t_dst[MAX_SG];
	stwuct ahash_wequest fawwback_weq;
	u32 method;
	int fwow;
};

/*
 * stwuct sun8i_ss_awg_tempwate - cwypto_awg tempwate
 * @type:		the CWYPTO_AWG_TYPE fow this tempwate
 * @ss_awgo_id:		the SS_ID fow this tempwate
 * @ss_bwockmode:	the type of bwock opewation SS_ID
 * @ss:			pointew to the sun8i_ss_dev stwuctuwe associated with
 *			this tempwate
 * @awg:		one of sub stwuct must be used
 * @stat_weq:		numbew of wequest done on this tempwate
 * @stat_fb:		numbew of wequest which has fawwbacked
 * @stat_bytes:		totaw data size done by this tempwate
 */
stwuct sun8i_ss_awg_tempwate {
	u32 type;
	u32 ss_awgo_id;
	u32 ss_bwockmode;
	stwuct sun8i_ss_dev *ss;
	union {
		stwuct skciphew_engine_awg skciphew;
		stwuct wng_awg wng;
		stwuct ahash_engine_awg hash;
	} awg;
	unsigned wong stat_weq;
	unsigned wong stat_fb;
	unsigned wong stat_bytes;
	unsigned wong stat_fb_wen;
	unsigned wong stat_fb_sgwen;
	unsigned wong stat_fb_awign;
	unsigned wong stat_fb_sgnum;
	chaw fbname[CWYPTO_MAX_AWG_NAME];
};

int sun8i_ss_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			unsigned int keywen);
int sun8i_ss_des3_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			 unsigned int keywen);
int sun8i_ss_ciphew_init(stwuct cwypto_tfm *tfm);
void sun8i_ss_ciphew_exit(stwuct cwypto_tfm *tfm);
int sun8i_ss_handwe_ciphew_wequest(stwuct cwypto_engine *engine, void *aweq);
int sun8i_ss_skdecwypt(stwuct skciphew_wequest *aweq);
int sun8i_ss_skencwypt(stwuct skciphew_wequest *aweq);

int sun8i_ss_get_engine_numbew(stwuct sun8i_ss_dev *ss);

int sun8i_ss_wun_task(stwuct sun8i_ss_dev *ss, stwuct sun8i_ciphew_weq_ctx *wctx, const chaw *name);
int sun8i_ss_pwng_genewate(stwuct cwypto_wng *tfm, const u8 *swc,
			   unsigned int swen, u8 *dst, unsigned int dwen);
int sun8i_ss_pwng_seed(stwuct cwypto_wng *tfm, const u8 *seed, unsigned int swen);
int sun8i_ss_pwng_init(stwuct cwypto_tfm *tfm);
void sun8i_ss_pwng_exit(stwuct cwypto_tfm *tfm);

int sun8i_ss_hash_init_tfm(stwuct cwypto_ahash *tfm);
void sun8i_ss_hash_exit_tfm(stwuct cwypto_ahash *tfm);
int sun8i_ss_hash_init(stwuct ahash_wequest *aweq);
int sun8i_ss_hash_expowt(stwuct ahash_wequest *aweq, void *out);
int sun8i_ss_hash_impowt(stwuct ahash_wequest *aweq, const void *in);
int sun8i_ss_hash_finaw(stwuct ahash_wequest *aweq);
int sun8i_ss_hash_update(stwuct ahash_wequest *aweq);
int sun8i_ss_hash_finup(stwuct ahash_wequest *aweq);
int sun8i_ss_hash_digest(stwuct ahash_wequest *aweq);
int sun8i_ss_hash_wun(stwuct cwypto_engine *engine, void *bweq);
int sun8i_ss_hmac_setkey(stwuct cwypto_ahash *ahash, const u8 *key,
			 unsigned int keywen);
