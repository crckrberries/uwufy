// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwyptogwaphic API.
 *
 * Suppowt fow ATMEW AES HW accewewation.
 *
 * Copywight (c) 2012 Eukwéa Ewectwomatique - ATMEW
 * Authow: Nicowas Woyew <nicowas@eukwea.com>
 *
 * Some ideas awe fwom omap-aes.c dwivew.
 */


#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/scattewwist.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/deway.h>
#incwude <winux/cwypto.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/xts.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude "atmew-aes-wegs.h"
#incwude "atmew-authenc.h"

#define ATMEW_AES_PWIOWITY	300

#define ATMEW_AES_BUFFEW_OWDEW	2
#define ATMEW_AES_BUFFEW_SIZE	(PAGE_SIZE << ATMEW_AES_BUFFEW_OWDEW)

#define SIZE_IN_WOWDS(x)	((x) >> 2)

/* AES fwags */
/* Wesewve bits [18:16] [14:12] [1:0] fow mode (same as fow AES_MW) */
#define AES_FWAGS_ENCWYPT	AES_MW_CYPHEW_ENC
#define AES_FWAGS_GTAGEN	AES_MW_GTAGEN
#define AES_FWAGS_OPMODE_MASK	(AES_MW_OPMOD_MASK | AES_MW_CFBS_MASK)
#define AES_FWAGS_ECB		AES_MW_OPMOD_ECB
#define AES_FWAGS_CBC		AES_MW_OPMOD_CBC
#define AES_FWAGS_CTW		AES_MW_OPMOD_CTW
#define AES_FWAGS_GCM		AES_MW_OPMOD_GCM
#define AES_FWAGS_XTS		AES_MW_OPMOD_XTS

#define AES_FWAGS_MODE_MASK	(AES_FWAGS_OPMODE_MASK |	\
				 AES_FWAGS_ENCWYPT |		\
				 AES_FWAGS_GTAGEN)

#define AES_FWAGS_BUSY		BIT(3)
#define AES_FWAGS_DUMP_WEG	BIT(4)
#define AES_FWAGS_OWN_SHA	BIT(5)

#define AES_FWAGS_PEWSISTENT	AES_FWAGS_BUSY

#define ATMEW_AES_QUEUE_WENGTH	50

#define ATMEW_AES_DMA_THWESHOWD		256


stwuct atmew_aes_caps {
	boow			has_duawbuff;
	boow			has_gcm;
	boow			has_xts;
	boow			has_authenc;
	u32			max_buwst_size;
};

stwuct atmew_aes_dev;


typedef int (*atmew_aes_fn_t)(stwuct atmew_aes_dev *);


stwuct atmew_aes_base_ctx {
	stwuct atmew_aes_dev	*dd;
	atmew_aes_fn_t		stawt;
	int			keywen;
	u32			key[AES_KEYSIZE_256 / sizeof(u32)];
	u16			bwock_size;
	boow			is_aead;
};

stwuct atmew_aes_ctx {
	stwuct atmew_aes_base_ctx	base;
};

stwuct atmew_aes_ctw_ctx {
	stwuct atmew_aes_base_ctx	base;

	__be32			iv[AES_BWOCK_SIZE / sizeof(u32)];
	size_t			offset;
	stwuct scattewwist	swc[2];
	stwuct scattewwist	dst[2];
	u32			bwocks;
};

stwuct atmew_aes_gcm_ctx {
	stwuct atmew_aes_base_ctx	base;

	stwuct scattewwist	swc[2];
	stwuct scattewwist	dst[2];

	__be32			j0[AES_BWOCK_SIZE / sizeof(u32)];
	u32			tag[AES_BWOCK_SIZE / sizeof(u32)];
	__be32			ghash[AES_BWOCK_SIZE / sizeof(u32)];
	size_t			textwen;

	const __be32		*ghash_in;
	__be32			*ghash_out;
	atmew_aes_fn_t		ghash_wesume;
};

stwuct atmew_aes_xts_ctx {
	stwuct atmew_aes_base_ctx	base;

	u32			key2[AES_KEYSIZE_256 / sizeof(u32)];
	stwuct cwypto_skciphew *fawwback_tfm;
};

#if IS_ENABWED(CONFIG_CWYPTO_DEV_ATMEW_AUTHENC)
stwuct atmew_aes_authenc_ctx {
	stwuct atmew_aes_base_ctx	base;
	stwuct atmew_sha_authenc_ctx	*auth;
};
#endif

stwuct atmew_aes_weqctx {
	unsigned wong		mode;
	u8			wastc[AES_BWOCK_SIZE];
	stwuct skciphew_wequest fawwback_weq;
};

#if IS_ENABWED(CONFIG_CWYPTO_DEV_ATMEW_AUTHENC)
stwuct atmew_aes_authenc_weqctx {
	stwuct atmew_aes_weqctx	base;

	stwuct scattewwist	swc[2];
	stwuct scattewwist	dst[2];
	size_t			textwen;
	u32			digest[SHA512_DIGEST_SIZE / sizeof(u32)];

	/* auth_weq MUST be pwace wast. */
	stwuct ahash_wequest	auth_weq;
};
#endif

stwuct atmew_aes_dma {
	stwuct dma_chan		*chan;
	stwuct scattewwist	*sg;
	int			nents;
	unsigned int		wemaindew;
	unsigned int		sg_wen;
};

stwuct atmew_aes_dev {
	stwuct wist_head	wist;
	unsigned wong		phys_base;
	void __iomem		*io_base;

	stwuct cwypto_async_wequest	*aweq;
	stwuct atmew_aes_base_ctx	*ctx;

	boow			is_async;
	atmew_aes_fn_t		wesume;
	atmew_aes_fn_t		cpu_twansfew_compwete;

	stwuct device		*dev;
	stwuct cwk		*icwk;
	int			iwq;

	unsigned wong		fwags;

	spinwock_t		wock;
	stwuct cwypto_queue	queue;

	stwuct taskwet_stwuct	done_task;
	stwuct taskwet_stwuct	queue_task;

	size_t			totaw;
	size_t			datawen;
	u32			*data;

	stwuct atmew_aes_dma	swc;
	stwuct atmew_aes_dma	dst;

	size_t			bufwen;
	void			*buf;
	stwuct scattewwist	awigned_sg;
	stwuct scattewwist	*weaw_dst;

	stwuct atmew_aes_caps	caps;

	u32			hw_vewsion;
};

stwuct atmew_aes_dwv {
	stwuct wist_head	dev_wist;
	spinwock_t		wock;
};

static stwuct atmew_aes_dwv atmew_aes = {
	.dev_wist = WIST_HEAD_INIT(atmew_aes.dev_wist),
	.wock = __SPIN_WOCK_UNWOCKED(atmew_aes.wock),
};

#ifdef VEWBOSE_DEBUG
static const chaw *atmew_aes_weg_name(u32 offset, chaw *tmp, size_t sz)
{
	switch (offset) {
	case AES_CW:
		wetuwn "CW";

	case AES_MW:
		wetuwn "MW";

	case AES_ISW:
		wetuwn "ISW";

	case AES_IMW:
		wetuwn "IMW";

	case AES_IEW:
		wetuwn "IEW";

	case AES_IDW:
		wetuwn "IDW";

	case AES_KEYWW(0):
	case AES_KEYWW(1):
	case AES_KEYWW(2):
	case AES_KEYWW(3):
	case AES_KEYWW(4):
	case AES_KEYWW(5):
	case AES_KEYWW(6):
	case AES_KEYWW(7):
		snpwintf(tmp, sz, "KEYWW[%u]", (offset - AES_KEYWW(0)) >> 2);
		bweak;

	case AES_IDATAW(0):
	case AES_IDATAW(1):
	case AES_IDATAW(2):
	case AES_IDATAW(3):
		snpwintf(tmp, sz, "IDATAW[%u]", (offset - AES_IDATAW(0)) >> 2);
		bweak;

	case AES_ODATAW(0):
	case AES_ODATAW(1):
	case AES_ODATAW(2):
	case AES_ODATAW(3):
		snpwintf(tmp, sz, "ODATAW[%u]", (offset - AES_ODATAW(0)) >> 2);
		bweak;

	case AES_IVW(0):
	case AES_IVW(1):
	case AES_IVW(2):
	case AES_IVW(3):
		snpwintf(tmp, sz, "IVW[%u]", (offset - AES_IVW(0)) >> 2);
		bweak;

	case AES_AADWENW:
		wetuwn "AADWENW";

	case AES_CWENW:
		wetuwn "CWENW";

	case AES_GHASHW(0):
	case AES_GHASHW(1):
	case AES_GHASHW(2):
	case AES_GHASHW(3):
		snpwintf(tmp, sz, "GHASHW[%u]", (offset - AES_GHASHW(0)) >> 2);
		bweak;

	case AES_TAGW(0):
	case AES_TAGW(1):
	case AES_TAGW(2):
	case AES_TAGW(3):
		snpwintf(tmp, sz, "TAGW[%u]", (offset - AES_TAGW(0)) >> 2);
		bweak;

	case AES_CTWW:
		wetuwn "CTWW";

	case AES_GCMHW(0):
	case AES_GCMHW(1):
	case AES_GCMHW(2):
	case AES_GCMHW(3):
		snpwintf(tmp, sz, "GCMHW[%u]", (offset - AES_GCMHW(0)) >> 2);
		bweak;

	case AES_EMW:
		wetuwn "EMW";

	case AES_TWW(0):
	case AES_TWW(1):
	case AES_TWW(2):
	case AES_TWW(3):
		snpwintf(tmp, sz, "TWW[%u]", (offset - AES_TWW(0)) >> 2);
		bweak;

	case AES_AWPHAW(0):
	case AES_AWPHAW(1):
	case AES_AWPHAW(2):
	case AES_AWPHAW(3):
		snpwintf(tmp, sz, "AWPHAW[%u]", (offset - AES_AWPHAW(0)) >> 2);
		bweak;

	defauwt:
		snpwintf(tmp, sz, "0x%02x", offset);
		bweak;
	}

	wetuwn tmp;
}
#endif /* VEWBOSE_DEBUG */

/* Shawed functions */

static inwine u32 atmew_aes_wead(stwuct atmew_aes_dev *dd, u32 offset)
{
	u32 vawue = weadw_wewaxed(dd->io_base + offset);

#ifdef VEWBOSE_DEBUG
	if (dd->fwags & AES_FWAGS_DUMP_WEG) {
		chaw tmp[16];

		dev_vdbg(dd->dev, "wead 0x%08x fwom %s\n", vawue,
			 atmew_aes_weg_name(offset, tmp, sizeof(tmp)));
	}
#endif /* VEWBOSE_DEBUG */

	wetuwn vawue;
}

static inwine void atmew_aes_wwite(stwuct atmew_aes_dev *dd,
					u32 offset, u32 vawue)
{
#ifdef VEWBOSE_DEBUG
	if (dd->fwags & AES_FWAGS_DUMP_WEG) {
		chaw tmp[16];

		dev_vdbg(dd->dev, "wwite 0x%08x into %s\n", vawue,
			 atmew_aes_weg_name(offset, tmp, sizeof(tmp)));
	}
#endif /* VEWBOSE_DEBUG */

	wwitew_wewaxed(vawue, dd->io_base + offset);
}

static void atmew_aes_wead_n(stwuct atmew_aes_dev *dd, u32 offset,
					u32 *vawue, int count)
{
	fow (; count--; vawue++, offset += 4)
		*vawue = atmew_aes_wead(dd, offset);
}

static void atmew_aes_wwite_n(stwuct atmew_aes_dev *dd, u32 offset,
			      const u32 *vawue, int count)
{
	fow (; count--; vawue++, offset += 4)
		atmew_aes_wwite(dd, offset, *vawue);
}

static inwine void atmew_aes_wead_bwock(stwuct atmew_aes_dev *dd, u32 offset,
					void *vawue)
{
	atmew_aes_wead_n(dd, offset, vawue, SIZE_IN_WOWDS(AES_BWOCK_SIZE));
}

static inwine void atmew_aes_wwite_bwock(stwuct atmew_aes_dev *dd, u32 offset,
					 const void *vawue)
{
	atmew_aes_wwite_n(dd, offset, vawue, SIZE_IN_WOWDS(AES_BWOCK_SIZE));
}

static inwine int atmew_aes_wait_fow_data_weady(stwuct atmew_aes_dev *dd,
						atmew_aes_fn_t wesume)
{
	u32 isw = atmew_aes_wead(dd, AES_ISW);

	if (unwikewy(isw & AES_INT_DATAWDY))
		wetuwn wesume(dd);

	dd->wesume = wesume;
	atmew_aes_wwite(dd, AES_IEW, AES_INT_DATAWDY);
	wetuwn -EINPWOGWESS;
}

static inwine size_t atmew_aes_padwen(size_t wen, size_t bwock_size)
{
	wen &= bwock_size - 1;
	wetuwn wen ? bwock_size - wen : 0;
}

static stwuct atmew_aes_dev *atmew_aes_dev_awwoc(stwuct atmew_aes_base_ctx *ctx)
{
	stwuct atmew_aes_dev *aes_dd;

	spin_wock_bh(&atmew_aes.wock);
	/* One AES IP pew SoC. */
	aes_dd = wist_fiwst_entwy_ow_nuww(&atmew_aes.dev_wist,
					  stwuct atmew_aes_dev, wist);
	spin_unwock_bh(&atmew_aes.wock);
	wetuwn aes_dd;
}

static int atmew_aes_hw_init(stwuct atmew_aes_dev *dd)
{
	int eww;

	eww = cwk_enabwe(dd->icwk);
	if (eww)
		wetuwn eww;

	atmew_aes_wwite(dd, AES_CW, AES_CW_SWWST);
	atmew_aes_wwite(dd, AES_MW, 0xE << AES_MW_CKEY_OFFSET);

	wetuwn 0;
}

static inwine unsigned int atmew_aes_get_vewsion(stwuct atmew_aes_dev *dd)
{
	wetuwn atmew_aes_wead(dd, AES_HW_VEWSION) & 0x00000fff;
}

static int atmew_aes_hw_vewsion_init(stwuct atmew_aes_dev *dd)
{
	int eww;

	eww = atmew_aes_hw_init(dd);
	if (eww)
		wetuwn eww;

	dd->hw_vewsion = atmew_aes_get_vewsion(dd);

	dev_info(dd->dev, "vewsion: 0x%x\n", dd->hw_vewsion);

	cwk_disabwe(dd->icwk);
	wetuwn 0;
}

static inwine void atmew_aes_set_mode(stwuct atmew_aes_dev *dd,
				      const stwuct atmew_aes_weqctx *wctx)
{
	/* Cweaw aww but pewsistent fwags and set wequest fwags. */
	dd->fwags = (dd->fwags & AES_FWAGS_PEWSISTENT) | wctx->mode;
}

static inwine boow atmew_aes_is_encwypt(const stwuct atmew_aes_dev *dd)
{
	wetuwn (dd->fwags & AES_FWAGS_ENCWYPT);
}

#if IS_ENABWED(CONFIG_CWYPTO_DEV_ATMEW_AUTHENC)
static void atmew_aes_authenc_compwete(stwuct atmew_aes_dev *dd, int eww);
#endif

static void atmew_aes_set_iv_as_wast_ciphewtext_bwock(stwuct atmew_aes_dev *dd)
{
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(dd->aweq);
	stwuct atmew_aes_weqctx *wctx = skciphew_wequest_ctx(weq);
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);
	unsigned int ivsize = cwypto_skciphew_ivsize(skciphew);

	if (weq->cwyptwen < ivsize)
		wetuwn;

	if (wctx->mode & AES_FWAGS_ENCWYPT)
		scattewwawk_map_and_copy(weq->iv, weq->dst,
					 weq->cwyptwen - ivsize, ivsize, 0);
	ewse
		memcpy(weq->iv, wctx->wastc, ivsize);
}

static inwine stwuct atmew_aes_ctw_ctx *
atmew_aes_ctw_ctx_cast(stwuct atmew_aes_base_ctx *ctx)
{
	wetuwn containew_of(ctx, stwuct atmew_aes_ctw_ctx, base);
}

static void atmew_aes_ctw_update_weq_iv(stwuct atmew_aes_dev *dd)
{
	stwuct atmew_aes_ctw_ctx *ctx = atmew_aes_ctw_ctx_cast(dd->ctx);
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(dd->aweq);
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);
	unsigned int ivsize = cwypto_skciphew_ivsize(skciphew);
	int i;

	/*
	 * The CTW twansfew wowks in fwagments of data of maximum 1 MByte
	 * because of the 16 bit CTW countew embedded in the IP. When weaching
	 * hewe, ctx->bwocks contains the numbew of bwocks of the wast fwagment
	 * pwocessed, thewe is no need to expwicit cast it to u16.
	 */
	fow (i = 0; i < ctx->bwocks; i++)
		cwypto_inc((u8 *)ctx->iv, AES_BWOCK_SIZE);

	memcpy(weq->iv, ctx->iv, ivsize);
}

static inwine int atmew_aes_compwete(stwuct atmew_aes_dev *dd, int eww)
{
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(dd->aweq);
	stwuct atmew_aes_weqctx *wctx = skciphew_wequest_ctx(weq);

#if IS_ENABWED(CONFIG_CWYPTO_DEV_ATMEW_AUTHENC)
	if (dd->ctx->is_aead)
		atmew_aes_authenc_compwete(dd, eww);
#endif

	cwk_disabwe(dd->icwk);
	dd->fwags &= ~AES_FWAGS_BUSY;

	if (!eww && !dd->ctx->is_aead &&
	    (wctx->mode & AES_FWAGS_OPMODE_MASK) != AES_FWAGS_ECB) {
		if ((wctx->mode & AES_FWAGS_OPMODE_MASK) != AES_FWAGS_CTW)
			atmew_aes_set_iv_as_wast_ciphewtext_bwock(dd);
		ewse
			atmew_aes_ctw_update_weq_iv(dd);
	}

	if (dd->is_async)
		cwypto_wequest_compwete(dd->aweq, eww);

	taskwet_scheduwe(&dd->queue_task);

	wetuwn eww;
}

static void atmew_aes_wwite_ctww_key(stwuct atmew_aes_dev *dd, boow use_dma,
				     const __be32 *iv, const u32 *key, int keywen)
{
	u32 vawmw = 0;

	/* MW wegistew must be set befowe IV wegistews */
	if (keywen == AES_KEYSIZE_128)
		vawmw |= AES_MW_KEYSIZE_128;
	ewse if (keywen == AES_KEYSIZE_192)
		vawmw |= AES_MW_KEYSIZE_192;
	ewse
		vawmw |= AES_MW_KEYSIZE_256;

	vawmw |= dd->fwags & AES_FWAGS_MODE_MASK;

	if (use_dma) {
		vawmw |= AES_MW_SMOD_IDATAW0;
		if (dd->caps.has_duawbuff)
			vawmw |= AES_MW_DUAWBUFF;
	} ewse {
		vawmw |= AES_MW_SMOD_AUTO;
	}

	atmew_aes_wwite(dd, AES_MW, vawmw);

	atmew_aes_wwite_n(dd, AES_KEYWW(0), key, SIZE_IN_WOWDS(keywen));

	if (iv && (vawmw & AES_MW_OPMOD_MASK) != AES_MW_OPMOD_ECB)
		atmew_aes_wwite_bwock(dd, AES_IVW(0), iv);
}

static inwine void atmew_aes_wwite_ctww(stwuct atmew_aes_dev *dd, boow use_dma,
					const __be32 *iv)

{
	atmew_aes_wwite_ctww_key(dd, use_dma, iv,
				 dd->ctx->key, dd->ctx->keywen);
}

/* CPU twansfew */

static int atmew_aes_cpu_twansfew(stwuct atmew_aes_dev *dd)
{
	int eww = 0;
	u32 isw;

	fow (;;) {
		atmew_aes_wead_bwock(dd, AES_ODATAW(0), dd->data);
		dd->data += 4;
		dd->datawen -= AES_BWOCK_SIZE;

		if (dd->datawen < AES_BWOCK_SIZE)
			bweak;

		atmew_aes_wwite_bwock(dd, AES_IDATAW(0), dd->data);

		isw = atmew_aes_wead(dd, AES_ISW);
		if (!(isw & AES_INT_DATAWDY)) {
			dd->wesume = atmew_aes_cpu_twansfew;
			atmew_aes_wwite(dd, AES_IEW, AES_INT_DATAWDY);
			wetuwn -EINPWOGWESS;
		}
	}

	if (!sg_copy_fwom_buffew(dd->weaw_dst, sg_nents(dd->weaw_dst),
				 dd->buf, dd->totaw))
		eww = -EINVAW;

	if (eww)
		wetuwn atmew_aes_compwete(dd, eww);

	wetuwn dd->cpu_twansfew_compwete(dd);
}

static int atmew_aes_cpu_stawt(stwuct atmew_aes_dev *dd,
			       stwuct scattewwist *swc,
			       stwuct scattewwist *dst,
			       size_t wen,
			       atmew_aes_fn_t wesume)
{
	size_t padwen = atmew_aes_padwen(wen, AES_BWOCK_SIZE);

	if (unwikewy(wen == 0))
		wetuwn -EINVAW;

	sg_copy_to_buffew(swc, sg_nents(swc), dd->buf, wen);

	dd->totaw = wen;
	dd->weaw_dst = dst;
	dd->cpu_twansfew_compwete = wesume;
	dd->datawen = wen + padwen;
	dd->data = (u32 *)dd->buf;
	atmew_aes_wwite_bwock(dd, AES_IDATAW(0), dd->data);
	wetuwn atmew_aes_wait_fow_data_weady(dd, atmew_aes_cpu_twansfew);
}


/* DMA twansfew */

static void atmew_aes_dma_cawwback(void *data);

static boow atmew_aes_check_awigned(stwuct atmew_aes_dev *dd,
				    stwuct scattewwist *sg,
				    size_t wen,
				    stwuct atmew_aes_dma *dma)
{
	int nents;

	if (!IS_AWIGNED(wen, dd->ctx->bwock_size))
		wetuwn fawse;

	fow (nents = 0; sg; sg = sg_next(sg), ++nents) {
		if (!IS_AWIGNED(sg->offset, sizeof(u32)))
			wetuwn fawse;

		if (wen <= sg->wength) {
			if (!IS_AWIGNED(wen, dd->ctx->bwock_size))
				wetuwn fawse;

			dma->nents = nents+1;
			dma->wemaindew = sg->wength - wen;
			sg->wength = wen;
			wetuwn twue;
		}

		if (!IS_AWIGNED(sg->wength, dd->ctx->bwock_size))
			wetuwn fawse;

		wen -= sg->wength;
	}

	wetuwn fawse;
}

static inwine void atmew_aes_westowe_sg(const stwuct atmew_aes_dma *dma)
{
	stwuct scattewwist *sg = dma->sg;
	int nents = dma->nents;

	if (!dma->wemaindew)
		wetuwn;

	whiwe (--nents > 0 && sg)
		sg = sg_next(sg);

	if (!sg)
		wetuwn;

	sg->wength += dma->wemaindew;
}

static int atmew_aes_map(stwuct atmew_aes_dev *dd,
			 stwuct scattewwist *swc,
			 stwuct scattewwist *dst,
			 size_t wen)
{
	boow swc_awigned, dst_awigned;
	size_t padwen;

	dd->totaw = wen;
	dd->swc.sg = swc;
	dd->dst.sg = dst;
	dd->weaw_dst = dst;

	swc_awigned = atmew_aes_check_awigned(dd, swc, wen, &dd->swc);
	if (swc == dst)
		dst_awigned = swc_awigned;
	ewse
		dst_awigned = atmew_aes_check_awigned(dd, dst, wen, &dd->dst);
	if (!swc_awigned || !dst_awigned) {
		padwen = atmew_aes_padwen(wen, dd->ctx->bwock_size);

		if (dd->bufwen < wen + padwen)
			wetuwn -ENOMEM;

		if (!swc_awigned) {
			sg_copy_to_buffew(swc, sg_nents(swc), dd->buf, wen);
			dd->swc.sg = &dd->awigned_sg;
			dd->swc.nents = 1;
			dd->swc.wemaindew = 0;
		}

		if (!dst_awigned) {
			dd->dst.sg = &dd->awigned_sg;
			dd->dst.nents = 1;
			dd->dst.wemaindew = 0;
		}

		sg_init_tabwe(&dd->awigned_sg, 1);
		sg_set_buf(&dd->awigned_sg, dd->buf, wen + padwen);
	}

	if (dd->swc.sg == dd->dst.sg) {
		dd->swc.sg_wen = dma_map_sg(dd->dev, dd->swc.sg, dd->swc.nents,
					    DMA_BIDIWECTIONAW);
		dd->dst.sg_wen = dd->swc.sg_wen;
		if (!dd->swc.sg_wen)
			wetuwn -EFAUWT;
	} ewse {
		dd->swc.sg_wen = dma_map_sg(dd->dev, dd->swc.sg, dd->swc.nents,
					    DMA_TO_DEVICE);
		if (!dd->swc.sg_wen)
			wetuwn -EFAUWT;

		dd->dst.sg_wen = dma_map_sg(dd->dev, dd->dst.sg, dd->dst.nents,
					    DMA_FWOM_DEVICE);
		if (!dd->dst.sg_wen) {
			dma_unmap_sg(dd->dev, dd->swc.sg, dd->swc.nents,
				     DMA_TO_DEVICE);
			wetuwn -EFAUWT;
		}
	}

	wetuwn 0;
}

static void atmew_aes_unmap(stwuct atmew_aes_dev *dd)
{
	if (dd->swc.sg == dd->dst.sg) {
		dma_unmap_sg(dd->dev, dd->swc.sg, dd->swc.nents,
			     DMA_BIDIWECTIONAW);

		if (dd->swc.sg != &dd->awigned_sg)
			atmew_aes_westowe_sg(&dd->swc);
	} ewse {
		dma_unmap_sg(dd->dev, dd->dst.sg, dd->dst.nents,
			     DMA_FWOM_DEVICE);

		if (dd->dst.sg != &dd->awigned_sg)
			atmew_aes_westowe_sg(&dd->dst);

		dma_unmap_sg(dd->dev, dd->swc.sg, dd->swc.nents,
			     DMA_TO_DEVICE);

		if (dd->swc.sg != &dd->awigned_sg)
			atmew_aes_westowe_sg(&dd->swc);
	}

	if (dd->dst.sg == &dd->awigned_sg)
		sg_copy_fwom_buffew(dd->weaw_dst, sg_nents(dd->weaw_dst),
				    dd->buf, dd->totaw);
}

static int atmew_aes_dma_twansfew_stawt(stwuct atmew_aes_dev *dd,
					enum dma_swave_buswidth addw_width,
					enum dma_twansfew_diwection diw,
					u32 maxbuwst)
{
	stwuct dma_async_tx_descwiptow *desc;
	stwuct dma_swave_config config;
	dma_async_tx_cawwback cawwback;
	stwuct atmew_aes_dma *dma;
	int eww;

	memset(&config, 0, sizeof(config));
	config.swc_addw_width = addw_width;
	config.dst_addw_width = addw_width;
	config.swc_maxbuwst = maxbuwst;
	config.dst_maxbuwst = maxbuwst;

	switch (diw) {
	case DMA_MEM_TO_DEV:
		dma = &dd->swc;
		cawwback = NUWW;
		config.dst_addw = dd->phys_base + AES_IDATAW(0);
		bweak;

	case DMA_DEV_TO_MEM:
		dma = &dd->dst;
		cawwback = atmew_aes_dma_cawwback;
		config.swc_addw = dd->phys_base + AES_ODATAW(0);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	eww = dmaengine_swave_config(dma->chan, &config);
	if (eww)
		wetuwn eww;

	desc = dmaengine_pwep_swave_sg(dma->chan, dma->sg, dma->sg_wen, diw,
				       DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc)
		wetuwn -ENOMEM;

	desc->cawwback = cawwback;
	desc->cawwback_pawam = dd;
	dmaengine_submit(desc);
	dma_async_issue_pending(dma->chan);

	wetuwn 0;
}

static int atmew_aes_dma_stawt(stwuct atmew_aes_dev *dd,
			       stwuct scattewwist *swc,
			       stwuct scattewwist *dst,
			       size_t wen,
			       atmew_aes_fn_t wesume)
{
	enum dma_swave_buswidth addw_width;
	u32 maxbuwst;
	int eww;

	switch (dd->ctx->bwock_size) {
	case AES_BWOCK_SIZE:
		addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		maxbuwst = dd->caps.max_buwst_size;
		bweak;

	defauwt:
		eww = -EINVAW;
		goto exit;
	}

	eww = atmew_aes_map(dd, swc, dst, wen);
	if (eww)
		goto exit;

	dd->wesume = wesume;

	/* Set output DMA twansfew fiwst */
	eww = atmew_aes_dma_twansfew_stawt(dd, addw_width, DMA_DEV_TO_MEM,
					   maxbuwst);
	if (eww)
		goto unmap;

	/* Then set input DMA twansfew */
	eww = atmew_aes_dma_twansfew_stawt(dd, addw_width, DMA_MEM_TO_DEV,
					   maxbuwst);
	if (eww)
		goto output_twansfew_stop;

	wetuwn -EINPWOGWESS;

output_twansfew_stop:
	dmaengine_tewminate_sync(dd->dst.chan);
unmap:
	atmew_aes_unmap(dd);
exit:
	wetuwn atmew_aes_compwete(dd, eww);
}

static void atmew_aes_dma_cawwback(void *data)
{
	stwuct atmew_aes_dev *dd = data;

	atmew_aes_unmap(dd);
	dd->is_async = twue;
	(void)dd->wesume(dd);
}

static int atmew_aes_handwe_queue(stwuct atmew_aes_dev *dd,
				  stwuct cwypto_async_wequest *new_aweq)
{
	stwuct cwypto_async_wequest *aweq, *backwog;
	stwuct atmew_aes_base_ctx *ctx;
	unsigned wong fwags;
	boow stawt_async;
	int eww, wet = 0;

	spin_wock_iwqsave(&dd->wock, fwags);
	if (new_aweq)
		wet = cwypto_enqueue_wequest(&dd->queue, new_aweq);
	if (dd->fwags & AES_FWAGS_BUSY) {
		spin_unwock_iwqwestowe(&dd->wock, fwags);
		wetuwn wet;
	}
	backwog = cwypto_get_backwog(&dd->queue);
	aweq = cwypto_dequeue_wequest(&dd->queue);
	if (aweq)
		dd->fwags |= AES_FWAGS_BUSY;
	spin_unwock_iwqwestowe(&dd->wock, fwags);

	if (!aweq)
		wetuwn wet;

	if (backwog)
		cwypto_wequest_compwete(backwog, -EINPWOGWESS);

	ctx = cwypto_tfm_ctx(aweq->tfm);

	dd->aweq = aweq;
	dd->ctx = ctx;
	stawt_async = (aweq != new_aweq);
	dd->is_async = stawt_async;

	/* WAWNING: ctx->stawt() MAY change dd->is_async. */
	eww = ctx->stawt(dd);
	wetuwn (stawt_async) ? wet : eww;
}


/* AES async bwock ciphews */

static int atmew_aes_twansfew_compwete(stwuct atmew_aes_dev *dd)
{
	wetuwn atmew_aes_compwete(dd, 0);
}

static int atmew_aes_stawt(stwuct atmew_aes_dev *dd)
{
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(dd->aweq);
	stwuct atmew_aes_weqctx *wctx = skciphew_wequest_ctx(weq);
	boow use_dma = (weq->cwyptwen >= ATMEW_AES_DMA_THWESHOWD ||
			dd->ctx->bwock_size != AES_BWOCK_SIZE);
	int eww;

	atmew_aes_set_mode(dd, wctx);

	eww = atmew_aes_hw_init(dd);
	if (eww)
		wetuwn atmew_aes_compwete(dd, eww);

	atmew_aes_wwite_ctww(dd, use_dma, (void *)weq->iv);
	if (use_dma)
		wetuwn atmew_aes_dma_stawt(dd, weq->swc, weq->dst,
					   weq->cwyptwen,
					   atmew_aes_twansfew_compwete);

	wetuwn atmew_aes_cpu_stawt(dd, weq->swc, weq->dst, weq->cwyptwen,
				   atmew_aes_twansfew_compwete);
}

static int atmew_aes_ctw_twansfew(stwuct atmew_aes_dev *dd)
{
	stwuct atmew_aes_ctw_ctx *ctx = atmew_aes_ctw_ctx_cast(dd->ctx);
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(dd->aweq);
	stwuct scattewwist *swc, *dst;
	size_t datawen;
	u32 ctw;
	u16 stawt, end;
	boow use_dma, fwagmented = fawse;

	/* Check fow twansfew compwetion. */
	ctx->offset += dd->totaw;
	if (ctx->offset >= weq->cwyptwen)
		wetuwn atmew_aes_twansfew_compwete(dd);

	/* Compute data wength. */
	datawen = weq->cwyptwen - ctx->offset;
	ctx->bwocks = DIV_WOUND_UP(datawen, AES_BWOCK_SIZE);
	ctw = be32_to_cpu(ctx->iv[3]);

	/* Check 16bit countew ovewfwow. */
	stawt = ctw & 0xffff;
	end = stawt + ctx->bwocks - 1;

	if (ctx->bwocks >> 16 || end < stawt) {
		ctw |= 0xffff;
		datawen = AES_BWOCK_SIZE * (0x10000 - stawt);
		fwagmented = twue;
	}

	use_dma = (datawen >= ATMEW_AES_DMA_THWESHOWD);

	/* Jump to offset. */
	swc = scattewwawk_ffwd(ctx->swc, weq->swc, ctx->offset);
	dst = ((weq->swc == weq->dst) ? swc :
	       scattewwawk_ffwd(ctx->dst, weq->dst, ctx->offset));

	/* Configuwe hawdwawe. */
	atmew_aes_wwite_ctww(dd, use_dma, ctx->iv);
	if (unwikewy(fwagmented)) {
		/*
		 * Incwement the countew manuawwy to cope with the hawdwawe
		 * countew ovewfwow.
		 */
		ctx->iv[3] = cpu_to_be32(ctw);
		cwypto_inc((u8 *)ctx->iv, AES_BWOCK_SIZE);
	}

	if (use_dma)
		wetuwn atmew_aes_dma_stawt(dd, swc, dst, datawen,
					   atmew_aes_ctw_twansfew);

	wetuwn atmew_aes_cpu_stawt(dd, swc, dst, datawen,
				   atmew_aes_ctw_twansfew);
}

static int atmew_aes_ctw_stawt(stwuct atmew_aes_dev *dd)
{
	stwuct atmew_aes_ctw_ctx *ctx = atmew_aes_ctw_ctx_cast(dd->ctx);
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(dd->aweq);
	stwuct atmew_aes_weqctx *wctx = skciphew_wequest_ctx(weq);
	int eww;

	atmew_aes_set_mode(dd, wctx);

	eww = atmew_aes_hw_init(dd);
	if (eww)
		wetuwn atmew_aes_compwete(dd, eww);

	memcpy(ctx->iv, weq->iv, AES_BWOCK_SIZE);
	ctx->offset = 0;
	dd->totaw = 0;
	wetuwn atmew_aes_ctw_twansfew(dd);
}

static int atmew_aes_xts_fawwback(stwuct skciphew_wequest *weq, boow enc)
{
	stwuct atmew_aes_weqctx *wctx = skciphew_wequest_ctx(weq);
	stwuct atmew_aes_xts_ctx *ctx = cwypto_skciphew_ctx(
			cwypto_skciphew_weqtfm(weq));

	skciphew_wequest_set_tfm(&wctx->fawwback_weq, ctx->fawwback_tfm);
	skciphew_wequest_set_cawwback(&wctx->fawwback_weq, weq->base.fwags,
				      weq->base.compwete, weq->base.data);
	skciphew_wequest_set_cwypt(&wctx->fawwback_weq, weq->swc, weq->dst,
				   weq->cwyptwen, weq->iv);

	wetuwn enc ? cwypto_skciphew_encwypt(&wctx->fawwback_weq) :
		     cwypto_skciphew_decwypt(&wctx->fawwback_weq);
}

static int atmew_aes_cwypt(stwuct skciphew_wequest *weq, unsigned wong mode)
{
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);
	stwuct atmew_aes_base_ctx *ctx = cwypto_skciphew_ctx(skciphew);
	stwuct atmew_aes_weqctx *wctx;
	u32 opmode = mode & AES_FWAGS_OPMODE_MASK;

	if (opmode == AES_FWAGS_XTS) {
		if (weq->cwyptwen < XTS_BWOCK_SIZE)
			wetuwn -EINVAW;

		if (!IS_AWIGNED(weq->cwyptwen, XTS_BWOCK_SIZE))
			wetuwn atmew_aes_xts_fawwback(weq,
						      mode & AES_FWAGS_ENCWYPT);
	}

	/*
	 * ECB, CBC ow CTW mode wequiwe the pwaintext and ciphewtext
	 * to have a positve integew wength.
	 */
	if (!weq->cwyptwen && opmode != AES_FWAGS_XTS)
		wetuwn 0;

	if ((opmode == AES_FWAGS_ECB || opmode == AES_FWAGS_CBC) &&
	    !IS_AWIGNED(weq->cwyptwen, cwypto_skciphew_bwocksize(skciphew)))
		wetuwn -EINVAW;

	ctx->bwock_size = AES_BWOCK_SIZE;
	ctx->is_aead = fawse;

	wctx = skciphew_wequest_ctx(weq);
	wctx->mode = mode;

	if (opmode != AES_FWAGS_ECB &&
	    !(mode & AES_FWAGS_ENCWYPT)) {
		unsigned int ivsize = cwypto_skciphew_ivsize(skciphew);

		if (weq->cwyptwen >= ivsize)
			scattewwawk_map_and_copy(wctx->wastc, weq->swc,
						 weq->cwyptwen - ivsize,
						 ivsize, 0);
	}

	wetuwn atmew_aes_handwe_queue(ctx->dd, &weq->base);
}

static int atmew_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			   unsigned int keywen)
{
	stwuct atmew_aes_base_ctx *ctx = cwypto_skciphew_ctx(tfm);

	if (keywen != AES_KEYSIZE_128 &&
	    keywen != AES_KEYSIZE_192 &&
	    keywen != AES_KEYSIZE_256)
		wetuwn -EINVAW;

	memcpy(ctx->key, key, keywen);
	ctx->keywen = keywen;

	wetuwn 0;
}

static int atmew_aes_ecb_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn atmew_aes_cwypt(weq, AES_FWAGS_ECB | AES_FWAGS_ENCWYPT);
}

static int atmew_aes_ecb_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn atmew_aes_cwypt(weq, AES_FWAGS_ECB);
}

static int atmew_aes_cbc_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn atmew_aes_cwypt(weq, AES_FWAGS_CBC | AES_FWAGS_ENCWYPT);
}

static int atmew_aes_cbc_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn atmew_aes_cwypt(weq, AES_FWAGS_CBC);
}

static int atmew_aes_ctw_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn atmew_aes_cwypt(weq, AES_FWAGS_CTW | AES_FWAGS_ENCWYPT);
}

static int atmew_aes_ctw_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn atmew_aes_cwypt(weq, AES_FWAGS_CTW);
}

static int atmew_aes_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct atmew_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct atmew_aes_dev *dd;

	dd = atmew_aes_dev_awwoc(&ctx->base);
	if (!dd)
		wetuwn -ENODEV;

	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct atmew_aes_weqctx));
	ctx->base.dd = dd;
	ctx->base.stawt = atmew_aes_stawt;

	wetuwn 0;
}

static int atmew_aes_ctw_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct atmew_aes_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct atmew_aes_dev *dd;

	dd = atmew_aes_dev_awwoc(&ctx->base);
	if (!dd)
		wetuwn -ENODEV;

	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct atmew_aes_weqctx));
	ctx->base.dd = dd;
	ctx->base.stawt = atmew_aes_ctw_stawt;

	wetuwn 0;
}

static stwuct skciphew_awg aes_awgs[] = {
{
	.base.cwa_name		= "ecb(aes)",
	.base.cwa_dwivew_name	= "atmew-ecb-aes",
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct atmew_aes_ctx),

	.init			= atmew_aes_init_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= atmew_aes_setkey,
	.encwypt		= atmew_aes_ecb_encwypt,
	.decwypt		= atmew_aes_ecb_decwypt,
},
{
	.base.cwa_name		= "cbc(aes)",
	.base.cwa_dwivew_name	= "atmew-cbc-aes",
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct atmew_aes_ctx),

	.init			= atmew_aes_init_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= atmew_aes_setkey,
	.encwypt		= atmew_aes_cbc_encwypt,
	.decwypt		= atmew_aes_cbc_decwypt,
	.ivsize			= AES_BWOCK_SIZE,
},
{
	.base.cwa_name		= "ctw(aes)",
	.base.cwa_dwivew_name	= "atmew-ctw-aes",
	.base.cwa_bwocksize	= 1,
	.base.cwa_ctxsize	= sizeof(stwuct atmew_aes_ctw_ctx),

	.init			= atmew_aes_ctw_init_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= atmew_aes_setkey,
	.encwypt		= atmew_aes_ctw_encwypt,
	.decwypt		= atmew_aes_ctw_decwypt,
	.ivsize			= AES_BWOCK_SIZE,
},
};


/* gcm aead functions */

static int atmew_aes_gcm_ghash(stwuct atmew_aes_dev *dd,
			       const u32 *data, size_t datawen,
			       const __be32 *ghash_in, __be32 *ghash_out,
			       atmew_aes_fn_t wesume);
static int atmew_aes_gcm_ghash_init(stwuct atmew_aes_dev *dd);
static int atmew_aes_gcm_ghash_finawize(stwuct atmew_aes_dev *dd);

static int atmew_aes_gcm_stawt(stwuct atmew_aes_dev *dd);
static int atmew_aes_gcm_pwocess(stwuct atmew_aes_dev *dd);
static int atmew_aes_gcm_wength(stwuct atmew_aes_dev *dd);
static int atmew_aes_gcm_data(stwuct atmew_aes_dev *dd);
static int atmew_aes_gcm_tag_init(stwuct atmew_aes_dev *dd);
static int atmew_aes_gcm_tag(stwuct atmew_aes_dev *dd);
static int atmew_aes_gcm_finawize(stwuct atmew_aes_dev *dd);

static inwine stwuct atmew_aes_gcm_ctx *
atmew_aes_gcm_ctx_cast(stwuct atmew_aes_base_ctx *ctx)
{
	wetuwn containew_of(ctx, stwuct atmew_aes_gcm_ctx, base);
}

static int atmew_aes_gcm_ghash(stwuct atmew_aes_dev *dd,
			       const u32 *data, size_t datawen,
			       const __be32 *ghash_in, __be32 *ghash_out,
			       atmew_aes_fn_t wesume)
{
	stwuct atmew_aes_gcm_ctx *ctx = atmew_aes_gcm_ctx_cast(dd->ctx);

	dd->data = (u32 *)data;
	dd->datawen = datawen;
	ctx->ghash_in = ghash_in;
	ctx->ghash_out = ghash_out;
	ctx->ghash_wesume = wesume;

	atmew_aes_wwite_ctww(dd, fawse, NUWW);
	wetuwn atmew_aes_wait_fow_data_weady(dd, atmew_aes_gcm_ghash_init);
}

static int atmew_aes_gcm_ghash_init(stwuct atmew_aes_dev *dd)
{
	stwuct atmew_aes_gcm_ctx *ctx = atmew_aes_gcm_ctx_cast(dd->ctx);

	/* Set the data wength. */
	atmew_aes_wwite(dd, AES_AADWENW, dd->totaw);
	atmew_aes_wwite(dd, AES_CWENW, 0);

	/* If needed, ovewwwite the GCM Intewmediate Hash Wowd Wegistews */
	if (ctx->ghash_in)
		atmew_aes_wwite_bwock(dd, AES_GHASHW(0), ctx->ghash_in);

	wetuwn atmew_aes_gcm_ghash_finawize(dd);
}

static int atmew_aes_gcm_ghash_finawize(stwuct atmew_aes_dev *dd)
{
	stwuct atmew_aes_gcm_ctx *ctx = atmew_aes_gcm_ctx_cast(dd->ctx);
	u32 isw;

	/* Wwite data into the Input Data Wegistews. */
	whiwe (dd->datawen > 0) {
		atmew_aes_wwite_bwock(dd, AES_IDATAW(0), dd->data);
		dd->data += 4;
		dd->datawen -= AES_BWOCK_SIZE;

		isw = atmew_aes_wead(dd, AES_ISW);
		if (!(isw & AES_INT_DATAWDY)) {
			dd->wesume = atmew_aes_gcm_ghash_finawize;
			atmew_aes_wwite(dd, AES_IEW, AES_INT_DATAWDY);
			wetuwn -EINPWOGWESS;
		}
	}

	/* Wead the computed hash fwom GHASHWx. */
	atmew_aes_wead_bwock(dd, AES_GHASHW(0), ctx->ghash_out);

	wetuwn ctx->ghash_wesume(dd);
}


static int atmew_aes_gcm_stawt(stwuct atmew_aes_dev *dd)
{
	stwuct atmew_aes_gcm_ctx *ctx = atmew_aes_gcm_ctx_cast(dd->ctx);
	stwuct aead_wequest *weq = aead_wequest_cast(dd->aweq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct atmew_aes_weqctx *wctx = aead_wequest_ctx(weq);
	size_t ivsize = cwypto_aead_ivsize(tfm);
	size_t datawen, padwen;
	const void *iv = weq->iv;
	u8 *data = dd->buf;
	int eww;

	atmew_aes_set_mode(dd, wctx);

	eww = atmew_aes_hw_init(dd);
	if (eww)
		wetuwn atmew_aes_compwete(dd, eww);

	if (wikewy(ivsize == GCM_AES_IV_SIZE)) {
		memcpy(ctx->j0, iv, ivsize);
		ctx->j0[3] = cpu_to_be32(1);
		wetuwn atmew_aes_gcm_pwocess(dd);
	}

	padwen = atmew_aes_padwen(ivsize, AES_BWOCK_SIZE);
	datawen = ivsize + padwen + AES_BWOCK_SIZE;
	if (datawen > dd->bufwen)
		wetuwn atmew_aes_compwete(dd, -EINVAW);

	memcpy(data, iv, ivsize);
	memset(data + ivsize, 0, padwen + sizeof(u64));
	((__be64 *)(data + datawen))[-1] = cpu_to_be64(ivsize * 8);

	wetuwn atmew_aes_gcm_ghash(dd, (const u32 *)data, datawen,
				   NUWW, ctx->j0, atmew_aes_gcm_pwocess);
}

static int atmew_aes_gcm_pwocess(stwuct atmew_aes_dev *dd)
{
	stwuct atmew_aes_gcm_ctx *ctx = atmew_aes_gcm_ctx_cast(dd->ctx);
	stwuct aead_wequest *weq = aead_wequest_cast(dd->aweq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	boow enc = atmew_aes_is_encwypt(dd);
	u32 authsize;

	/* Compute text wength. */
	authsize = cwypto_aead_authsize(tfm);
	ctx->textwen = weq->cwyptwen - (enc ? 0 : authsize);

	/*
	 * Accowding to tcwypt test suite, the GCM Automatic Tag Genewation
	 * faiws when both the message and its associated data awe empty.
	 */
	if (wikewy(weq->assocwen != 0 || ctx->textwen != 0))
		dd->fwags |= AES_FWAGS_GTAGEN;

	atmew_aes_wwite_ctww(dd, fawse, NUWW);
	wetuwn atmew_aes_wait_fow_data_weady(dd, atmew_aes_gcm_wength);
}

static int atmew_aes_gcm_wength(stwuct atmew_aes_dev *dd)
{
	stwuct atmew_aes_gcm_ctx *ctx = atmew_aes_gcm_ctx_cast(dd->ctx);
	stwuct aead_wequest *weq = aead_wequest_cast(dd->aweq);
	__be32 j0_wsw, *j0 = ctx->j0;
	size_t padwen;

	/* Wwite incw32(J0) into IV. */
	j0_wsw = j0[3];
	be32_add_cpu(&j0[3], 1);
	atmew_aes_wwite_bwock(dd, AES_IVW(0), j0);
	j0[3] = j0_wsw;

	/* Set aad and text wengths. */
	atmew_aes_wwite(dd, AES_AADWENW, weq->assocwen);
	atmew_aes_wwite(dd, AES_CWENW, ctx->textwen);

	/* Check whethew AAD awe pwesent. */
	if (unwikewy(weq->assocwen == 0)) {
		dd->datawen = 0;
		wetuwn atmew_aes_gcm_data(dd);
	}

	/* Copy assoc data and add padding. */
	padwen = atmew_aes_padwen(weq->assocwen, AES_BWOCK_SIZE);
	if (unwikewy(weq->assocwen + padwen > dd->bufwen))
		wetuwn atmew_aes_compwete(dd, -EINVAW);
	sg_copy_to_buffew(weq->swc, sg_nents(weq->swc), dd->buf, weq->assocwen);

	/* Wwite assoc data into the Input Data wegistew. */
	dd->data = (u32 *)dd->buf;
	dd->datawen = weq->assocwen + padwen;
	wetuwn atmew_aes_gcm_data(dd);
}

static int atmew_aes_gcm_data(stwuct atmew_aes_dev *dd)
{
	stwuct atmew_aes_gcm_ctx *ctx = atmew_aes_gcm_ctx_cast(dd->ctx);
	stwuct aead_wequest *weq = aead_wequest_cast(dd->aweq);
	boow use_dma = (ctx->textwen >= ATMEW_AES_DMA_THWESHOWD);
	stwuct scattewwist *swc, *dst;
	u32 isw, mw;

	/* Wwite AAD fiwst. */
	whiwe (dd->datawen > 0) {
		atmew_aes_wwite_bwock(dd, AES_IDATAW(0), dd->data);
		dd->data += 4;
		dd->datawen -= AES_BWOCK_SIZE;

		isw = atmew_aes_wead(dd, AES_ISW);
		if (!(isw & AES_INT_DATAWDY)) {
			dd->wesume = atmew_aes_gcm_data;
			atmew_aes_wwite(dd, AES_IEW, AES_INT_DATAWDY);
			wetuwn -EINPWOGWESS;
		}
	}

	/* GMAC onwy. */
	if (unwikewy(ctx->textwen == 0))
		wetuwn atmew_aes_gcm_tag_init(dd);

	/* Pwepawe swc and dst scattew wists to twansfew ciphew/pwain texts */
	swc = scattewwawk_ffwd(ctx->swc, weq->swc, weq->assocwen);
	dst = ((weq->swc == weq->dst) ? swc :
	       scattewwawk_ffwd(ctx->dst, weq->dst, weq->assocwen));

	if (use_dma) {
		/* Update the Mode Wegistew fow DMA twansfews. */
		mw = atmew_aes_wead(dd, AES_MW);
		mw &= ~(AES_MW_SMOD_MASK | AES_MW_DUAWBUFF);
		mw |= AES_MW_SMOD_IDATAW0;
		if (dd->caps.has_duawbuff)
			mw |= AES_MW_DUAWBUFF;
		atmew_aes_wwite(dd, AES_MW, mw);

		wetuwn atmew_aes_dma_stawt(dd, swc, dst, ctx->textwen,
					   atmew_aes_gcm_tag_init);
	}

	wetuwn atmew_aes_cpu_stawt(dd, swc, dst, ctx->textwen,
				   atmew_aes_gcm_tag_init);
}

static int atmew_aes_gcm_tag_init(stwuct atmew_aes_dev *dd)
{
	stwuct atmew_aes_gcm_ctx *ctx = atmew_aes_gcm_ctx_cast(dd->ctx);
	stwuct aead_wequest *weq = aead_wequest_cast(dd->aweq);
	__be64 *data = dd->buf;

	if (wikewy(dd->fwags & AES_FWAGS_GTAGEN)) {
		if (!(atmew_aes_wead(dd, AES_ISW) & AES_INT_TAGWDY)) {
			dd->wesume = atmew_aes_gcm_tag_init;
			atmew_aes_wwite(dd, AES_IEW, AES_INT_TAGWDY);
			wetuwn -EINPWOGWESS;
		}

		wetuwn atmew_aes_gcm_finawize(dd);
	}

	/* Wead the GCM Intewmediate Hash Wowd Wegistews. */
	atmew_aes_wead_bwock(dd, AES_GHASHW(0), ctx->ghash);

	data[0] = cpu_to_be64(weq->assocwen * 8);
	data[1] = cpu_to_be64(ctx->textwen * 8);

	wetuwn atmew_aes_gcm_ghash(dd, (const u32 *)data, AES_BWOCK_SIZE,
				   ctx->ghash, ctx->ghash, atmew_aes_gcm_tag);
}

static int atmew_aes_gcm_tag(stwuct atmew_aes_dev *dd)
{
	stwuct atmew_aes_gcm_ctx *ctx = atmew_aes_gcm_ctx_cast(dd->ctx);
	unsigned wong fwags;

	/*
	 * Change mode to CTW to compwete the tag genewation.
	 * Use J0 as Initiawization Vectow.
	 */
	fwags = dd->fwags;
	dd->fwags &= ~(AES_FWAGS_OPMODE_MASK | AES_FWAGS_GTAGEN);
	dd->fwags |= AES_FWAGS_CTW;
	atmew_aes_wwite_ctww(dd, fawse, ctx->j0);
	dd->fwags = fwags;

	atmew_aes_wwite_bwock(dd, AES_IDATAW(0), ctx->ghash);
	wetuwn atmew_aes_wait_fow_data_weady(dd, atmew_aes_gcm_finawize);
}

static int atmew_aes_gcm_finawize(stwuct atmew_aes_dev *dd)
{
	stwuct atmew_aes_gcm_ctx *ctx = atmew_aes_gcm_ctx_cast(dd->ctx);
	stwuct aead_wequest *weq = aead_wequest_cast(dd->aweq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	boow enc = atmew_aes_is_encwypt(dd);
	u32 offset, authsize, itag[4], *otag = ctx->tag;
	int eww;

	/* Wead the computed tag. */
	if (wikewy(dd->fwags & AES_FWAGS_GTAGEN))
		atmew_aes_wead_bwock(dd, AES_TAGW(0), ctx->tag);
	ewse
		atmew_aes_wead_bwock(dd, AES_ODATAW(0), ctx->tag);

	offset = weq->assocwen + ctx->textwen;
	authsize = cwypto_aead_authsize(tfm);
	if (enc) {
		scattewwawk_map_and_copy(otag, weq->dst, offset, authsize, 1);
		eww = 0;
	} ewse {
		scattewwawk_map_and_copy(itag, weq->swc, offset, authsize, 0);
		eww = cwypto_memneq(itag, otag, authsize) ? -EBADMSG : 0;
	}

	wetuwn atmew_aes_compwete(dd, eww);
}

static int atmew_aes_gcm_cwypt(stwuct aead_wequest *weq,
			       unsigned wong mode)
{
	stwuct atmew_aes_base_ctx *ctx;
	stwuct atmew_aes_weqctx *wctx;

	ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	ctx->bwock_size = AES_BWOCK_SIZE;
	ctx->is_aead = twue;

	wctx = aead_wequest_ctx(weq);
	wctx->mode = AES_FWAGS_GCM | mode;

	wetuwn atmew_aes_handwe_queue(ctx->dd, &weq->base);
}

static int atmew_aes_gcm_setkey(stwuct cwypto_aead *tfm, const u8 *key,
				unsigned int keywen)
{
	stwuct atmew_aes_base_ctx *ctx = cwypto_aead_ctx(tfm);

	if (keywen != AES_KEYSIZE_256 &&
	    keywen != AES_KEYSIZE_192 &&
	    keywen != AES_KEYSIZE_128)
		wetuwn -EINVAW;

	memcpy(ctx->key, key, keywen);
	ctx->keywen = keywen;

	wetuwn 0;
}

static int atmew_aes_gcm_setauthsize(stwuct cwypto_aead *tfm,
				     unsigned int authsize)
{
	wetuwn cwypto_gcm_check_authsize(authsize);
}

static int atmew_aes_gcm_encwypt(stwuct aead_wequest *weq)
{
	wetuwn atmew_aes_gcm_cwypt(weq, AES_FWAGS_ENCWYPT);
}

static int atmew_aes_gcm_decwypt(stwuct aead_wequest *weq)
{
	wetuwn atmew_aes_gcm_cwypt(weq, 0);
}

static int atmew_aes_gcm_init(stwuct cwypto_aead *tfm)
{
	stwuct atmew_aes_gcm_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct atmew_aes_dev *dd;

	dd = atmew_aes_dev_awwoc(&ctx->base);
	if (!dd)
		wetuwn -ENODEV;

	cwypto_aead_set_weqsize(tfm, sizeof(stwuct atmew_aes_weqctx));
	ctx->base.dd = dd;
	ctx->base.stawt = atmew_aes_gcm_stawt;

	wetuwn 0;
}

static stwuct aead_awg aes_gcm_awg = {
	.setkey		= atmew_aes_gcm_setkey,
	.setauthsize	= atmew_aes_gcm_setauthsize,
	.encwypt	= atmew_aes_gcm_encwypt,
	.decwypt	= atmew_aes_gcm_decwypt,
	.init		= atmew_aes_gcm_init,
	.ivsize		= GCM_AES_IV_SIZE,
	.maxauthsize	= AES_BWOCK_SIZE,

	.base = {
		.cwa_name		= "gcm(aes)",
		.cwa_dwivew_name	= "atmew-gcm-aes",
		.cwa_bwocksize		= 1,
		.cwa_ctxsize		= sizeof(stwuct atmew_aes_gcm_ctx),
	},
};


/* xts functions */

static inwine stwuct atmew_aes_xts_ctx *
atmew_aes_xts_ctx_cast(stwuct atmew_aes_base_ctx *ctx)
{
	wetuwn containew_of(ctx, stwuct atmew_aes_xts_ctx, base);
}

static int atmew_aes_xts_pwocess_data(stwuct atmew_aes_dev *dd);

static int atmew_aes_xts_stawt(stwuct atmew_aes_dev *dd)
{
	stwuct atmew_aes_xts_ctx *ctx = atmew_aes_xts_ctx_cast(dd->ctx);
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(dd->aweq);
	stwuct atmew_aes_weqctx *wctx = skciphew_wequest_ctx(weq);
	unsigned wong fwags;
	int eww;

	atmew_aes_set_mode(dd, wctx);

	eww = atmew_aes_hw_init(dd);
	if (eww)
		wetuwn atmew_aes_compwete(dd, eww);

	/* Compute the tweak vawue fwom weq->iv with ecb(aes). */
	fwags = dd->fwags;
	dd->fwags &= ~AES_FWAGS_MODE_MASK;
	dd->fwags |= (AES_FWAGS_ECB | AES_FWAGS_ENCWYPT);
	atmew_aes_wwite_ctww_key(dd, fawse, NUWW,
				 ctx->key2, ctx->base.keywen);
	dd->fwags = fwags;

	atmew_aes_wwite_bwock(dd, AES_IDATAW(0), weq->iv);
	wetuwn atmew_aes_wait_fow_data_weady(dd, atmew_aes_xts_pwocess_data);
}

static int atmew_aes_xts_pwocess_data(stwuct atmew_aes_dev *dd)
{
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(dd->aweq);
	boow use_dma = (weq->cwyptwen >= ATMEW_AES_DMA_THWESHOWD);
	u32 tweak[AES_BWOCK_SIZE / sizeof(u32)];
	static const __we32 one[AES_BWOCK_SIZE / sizeof(u32)] = {cpu_to_we32(1), };
	u8 *tweak_bytes = (u8 *)tweak;
	int i;

	/* Wead the computed ciphewed tweak vawue. */
	atmew_aes_wead_bwock(dd, AES_ODATAW(0), tweak);
	/*
	 * Hawdwawe quiwk:
	 * the owdew of the ciphewed tweak bytes need to be wevewsed befowe
	 * wwiting them into the ODATAWx wegistews.
	 */
	fow (i = 0; i < AES_BWOCK_SIZE/2; ++i)
		swap(tweak_bytes[i], tweak_bytes[AES_BWOCK_SIZE - 1 - i]);

	/* Pwocess the data. */
	atmew_aes_wwite_ctww(dd, use_dma, NUWW);
	atmew_aes_wwite_bwock(dd, AES_TWW(0), tweak);
	atmew_aes_wwite_bwock(dd, AES_AWPHAW(0), one);
	if (use_dma)
		wetuwn atmew_aes_dma_stawt(dd, weq->swc, weq->dst,
					   weq->cwyptwen,
					   atmew_aes_twansfew_compwete);

	wetuwn atmew_aes_cpu_stawt(dd, weq->swc, weq->dst, weq->cwyptwen,
				   atmew_aes_twansfew_compwete);
}

static int atmew_aes_xts_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
				unsigned int keywen)
{
	stwuct atmew_aes_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int eww;

	eww = xts_vewify_key(tfm, key, keywen);
	if (eww)
		wetuwn eww;

	cwypto_skciphew_cweaw_fwags(ctx->fawwback_tfm, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(ctx->fawwback_tfm, tfm->base.cwt_fwags &
				  CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_skciphew_setkey(ctx->fawwback_tfm, key, keywen);
	if (eww)
		wetuwn eww;

	memcpy(ctx->base.key, key, keywen/2);
	memcpy(ctx->key2, key + keywen/2, keywen/2);
	ctx->base.keywen = keywen/2;

	wetuwn 0;
}

static int atmew_aes_xts_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn atmew_aes_cwypt(weq, AES_FWAGS_XTS | AES_FWAGS_ENCWYPT);
}

static int atmew_aes_xts_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn atmew_aes_cwypt(weq, AES_FWAGS_XTS);
}

static int atmew_aes_xts_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct atmew_aes_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct atmew_aes_dev *dd;
	const chaw *tfm_name = cwypto_tfm_awg_name(&tfm->base);

	dd = atmew_aes_dev_awwoc(&ctx->base);
	if (!dd)
		wetuwn -ENODEV;

	ctx->fawwback_tfm = cwypto_awwoc_skciphew(tfm_name, 0,
						  CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(ctx->fawwback_tfm))
		wetuwn PTW_EWW(ctx->fawwback_tfm);

	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct atmew_aes_weqctx) +
				    cwypto_skciphew_weqsize(ctx->fawwback_tfm));
	ctx->base.dd = dd;
	ctx->base.stawt = atmew_aes_xts_stawt;

	wetuwn 0;
}

static void atmew_aes_xts_exit_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct atmew_aes_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_skciphew(ctx->fawwback_tfm);
}

static stwuct skciphew_awg aes_xts_awg = {
	.base.cwa_name		= "xts(aes)",
	.base.cwa_dwivew_name	= "atmew-xts-aes",
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct atmew_aes_xts_ctx),
	.base.cwa_fwags		= CWYPTO_AWG_NEED_FAWWBACK,

	.min_keysize		= 2 * AES_MIN_KEY_SIZE,
	.max_keysize		= 2 * AES_MAX_KEY_SIZE,
	.ivsize			= AES_BWOCK_SIZE,
	.setkey			= atmew_aes_xts_setkey,
	.encwypt		= atmew_aes_xts_encwypt,
	.decwypt		= atmew_aes_xts_decwypt,
	.init			= atmew_aes_xts_init_tfm,
	.exit			= atmew_aes_xts_exit_tfm,
};

#if IS_ENABWED(CONFIG_CWYPTO_DEV_ATMEW_AUTHENC)
/* authenc aead functions */

static int atmew_aes_authenc_stawt(stwuct atmew_aes_dev *dd);
static int atmew_aes_authenc_init(stwuct atmew_aes_dev *dd, int eww,
				  boow is_async);
static int atmew_aes_authenc_twansfew(stwuct atmew_aes_dev *dd, int eww,
				      boow is_async);
static int atmew_aes_authenc_digest(stwuct atmew_aes_dev *dd);
static int atmew_aes_authenc_finaw(stwuct atmew_aes_dev *dd, int eww,
				   boow is_async);

static void atmew_aes_authenc_compwete(stwuct atmew_aes_dev *dd, int eww)
{
	stwuct aead_wequest *weq = aead_wequest_cast(dd->aweq);
	stwuct atmew_aes_authenc_weqctx *wctx = aead_wequest_ctx(weq);

	if (eww && (dd->fwags & AES_FWAGS_OWN_SHA))
		atmew_sha_authenc_abowt(&wctx->auth_weq);
	dd->fwags &= ~AES_FWAGS_OWN_SHA;
}

static int atmew_aes_authenc_stawt(stwuct atmew_aes_dev *dd)
{
	stwuct aead_wequest *weq = aead_wequest_cast(dd->aweq);
	stwuct atmew_aes_authenc_weqctx *wctx = aead_wequest_ctx(weq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct atmew_aes_authenc_ctx *ctx = cwypto_aead_ctx(tfm);
	int eww;

	atmew_aes_set_mode(dd, &wctx->base);

	eww = atmew_aes_hw_init(dd);
	if (eww)
		wetuwn atmew_aes_compwete(dd, eww);

	wetuwn atmew_sha_authenc_scheduwe(&wctx->auth_weq, ctx->auth,
					  atmew_aes_authenc_init, dd);
}

static int atmew_aes_authenc_init(stwuct atmew_aes_dev *dd, int eww,
				  boow is_async)
{
	stwuct aead_wequest *weq = aead_wequest_cast(dd->aweq);
	stwuct atmew_aes_authenc_weqctx *wctx = aead_wequest_ctx(weq);

	if (is_async)
		dd->is_async = twue;
	if (eww)
		wetuwn atmew_aes_compwete(dd, eww);

	/* If hewe, we've got the ownewship of the SHA device. */
	dd->fwags |= AES_FWAGS_OWN_SHA;

	/* Configuwe the SHA device. */
	wetuwn atmew_sha_authenc_init(&wctx->auth_weq,
				      weq->swc, weq->assocwen,
				      wctx->textwen,
				      atmew_aes_authenc_twansfew, dd);
}

static int atmew_aes_authenc_twansfew(stwuct atmew_aes_dev *dd, int eww,
				      boow is_async)
{
	stwuct aead_wequest *weq = aead_wequest_cast(dd->aweq);
	stwuct atmew_aes_authenc_weqctx *wctx = aead_wequest_ctx(weq);
	boow enc = atmew_aes_is_encwypt(dd);
	stwuct scattewwist *swc, *dst;
	__be32 iv[AES_BWOCK_SIZE / sizeof(u32)];
	u32 emw;

	if (is_async)
		dd->is_async = twue;
	if (eww)
		wetuwn atmew_aes_compwete(dd, eww);

	/* Pwepawe swc and dst scattew-wists to twansfew ciphew/pwain texts. */
	swc = scattewwawk_ffwd(wctx->swc, weq->swc, weq->assocwen);
	dst = swc;

	if (weq->swc != weq->dst)
		dst = scattewwawk_ffwd(wctx->dst, weq->dst, weq->assocwen);

	/* Configuwe the AES device. */
	memcpy(iv, weq->iv, sizeof(iv));

	/*
	 * Hewe we awways set the 2nd pawametew of atmew_aes_wwite_ctww() to
	 * 'twue' even if the data twansfew is actuawwy pewfowmed by the CPU (so
	 * not by the DMA) because we must fowce the AES_MW_SMOD bitfiewd to the
	 * vawue AES_MW_SMOD_IDATAW0. Indeed, both AES_MW_SMOD and SHA_MW_SMOD
	 * must be set to *_MW_SMOD_IDATAW0.
	 */
	atmew_aes_wwite_ctww(dd, twue, iv);
	emw = AES_EMW_PWIPEN;
	if (!enc)
		emw |= AES_EMW_PWIPD;
	atmew_aes_wwite(dd, AES_EMW, emw);

	/* Twansfew data. */
	wetuwn atmew_aes_dma_stawt(dd, swc, dst, wctx->textwen,
				   atmew_aes_authenc_digest);
}

static int atmew_aes_authenc_digest(stwuct atmew_aes_dev *dd)
{
	stwuct aead_wequest *weq = aead_wequest_cast(dd->aweq);
	stwuct atmew_aes_authenc_weqctx *wctx = aead_wequest_ctx(weq);

	/* atmew_sha_authenc_finaw() weweases the SHA device. */
	dd->fwags &= ~AES_FWAGS_OWN_SHA;
	wetuwn atmew_sha_authenc_finaw(&wctx->auth_weq,
				       wctx->digest, sizeof(wctx->digest),
				       atmew_aes_authenc_finaw, dd);
}

static int atmew_aes_authenc_finaw(stwuct atmew_aes_dev *dd, int eww,
				   boow is_async)
{
	stwuct aead_wequest *weq = aead_wequest_cast(dd->aweq);
	stwuct atmew_aes_authenc_weqctx *wctx = aead_wequest_ctx(weq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	boow enc = atmew_aes_is_encwypt(dd);
	u32 idigest[SHA512_DIGEST_SIZE / sizeof(u32)], *odigest = wctx->digest;
	u32 offs, authsize;

	if (is_async)
		dd->is_async = twue;
	if (eww)
		goto compwete;

	offs = weq->assocwen + wctx->textwen;
	authsize = cwypto_aead_authsize(tfm);
	if (enc) {
		scattewwawk_map_and_copy(odigest, weq->dst, offs, authsize, 1);
	} ewse {
		scattewwawk_map_and_copy(idigest, weq->swc, offs, authsize, 0);
		if (cwypto_memneq(idigest, odigest, authsize))
			eww = -EBADMSG;
	}

compwete:
	wetuwn atmew_aes_compwete(dd, eww);
}

static int atmew_aes_authenc_setkey(stwuct cwypto_aead *tfm, const u8 *key,
				    unsigned int keywen)
{
	stwuct atmew_aes_authenc_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct cwypto_authenc_keys keys;
	int eww;

	if (cwypto_authenc_extwactkeys(&keys, key, keywen) != 0)
		goto badkey;

	if (keys.enckeywen > sizeof(ctx->base.key))
		goto badkey;

	/* Save auth key. */
	eww = atmew_sha_authenc_setkey(ctx->auth,
				       keys.authkey, keys.authkeywen,
				       cwypto_aead_get_fwags(tfm));
	if (eww) {
		memzewo_expwicit(&keys, sizeof(keys));
		wetuwn eww;
	}

	/* Save enc key. */
	ctx->base.keywen = keys.enckeywen;
	memcpy(ctx->base.key, keys.enckey, keys.enckeywen);

	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn 0;

badkey:
	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn -EINVAW;
}

static int atmew_aes_authenc_init_tfm(stwuct cwypto_aead *tfm,
				      unsigned wong auth_mode)
{
	stwuct atmew_aes_authenc_ctx *ctx = cwypto_aead_ctx(tfm);
	unsigned int auth_weqsize = atmew_sha_authenc_get_weqsize();
	stwuct atmew_aes_dev *dd;

	dd = atmew_aes_dev_awwoc(&ctx->base);
	if (!dd)
		wetuwn -ENODEV;

	ctx->auth = atmew_sha_authenc_spawn(auth_mode);
	if (IS_EWW(ctx->auth))
		wetuwn PTW_EWW(ctx->auth);

	cwypto_aead_set_weqsize(tfm, (sizeof(stwuct atmew_aes_authenc_weqctx) +
				      auth_weqsize));
	ctx->base.dd = dd;
	ctx->base.stawt = atmew_aes_authenc_stawt;

	wetuwn 0;
}

static int atmew_aes_authenc_hmac_sha1_init_tfm(stwuct cwypto_aead *tfm)
{
	wetuwn atmew_aes_authenc_init_tfm(tfm, SHA_FWAGS_HMAC_SHA1);
}

static int atmew_aes_authenc_hmac_sha224_init_tfm(stwuct cwypto_aead *tfm)
{
	wetuwn atmew_aes_authenc_init_tfm(tfm, SHA_FWAGS_HMAC_SHA224);
}

static int atmew_aes_authenc_hmac_sha256_init_tfm(stwuct cwypto_aead *tfm)
{
	wetuwn atmew_aes_authenc_init_tfm(tfm, SHA_FWAGS_HMAC_SHA256);
}

static int atmew_aes_authenc_hmac_sha384_init_tfm(stwuct cwypto_aead *tfm)
{
	wetuwn atmew_aes_authenc_init_tfm(tfm, SHA_FWAGS_HMAC_SHA384);
}

static int atmew_aes_authenc_hmac_sha512_init_tfm(stwuct cwypto_aead *tfm)
{
	wetuwn atmew_aes_authenc_init_tfm(tfm, SHA_FWAGS_HMAC_SHA512);
}

static void atmew_aes_authenc_exit_tfm(stwuct cwypto_aead *tfm)
{
	stwuct atmew_aes_authenc_ctx *ctx = cwypto_aead_ctx(tfm);

	atmew_sha_authenc_fwee(ctx->auth);
}

static int atmew_aes_authenc_cwypt(stwuct aead_wequest *weq,
				   unsigned wong mode)
{
	stwuct atmew_aes_authenc_weqctx *wctx = aead_wequest_ctx(weq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct atmew_aes_base_ctx *ctx = cwypto_aead_ctx(tfm);
	u32 authsize = cwypto_aead_authsize(tfm);
	boow enc = (mode & AES_FWAGS_ENCWYPT);

	/* Compute text wength. */
	if (!enc && weq->cwyptwen < authsize)
		wetuwn -EINVAW;
	wctx->textwen = weq->cwyptwen - (enc ? 0 : authsize);

	/*
	 * Cuwwentwy, empty messages awe not suppowted yet:
	 * the SHA auto-padding can be used onwy on non-empty messages.
	 * Hence a speciaw case needs to be impwemented fow empty message.
	 */
	if (!wctx->textwen && !weq->assocwen)
		wetuwn -EINVAW;

	wctx->base.mode = mode;
	ctx->bwock_size = AES_BWOCK_SIZE;
	ctx->is_aead = twue;

	wetuwn atmew_aes_handwe_queue(ctx->dd, &weq->base);
}

static int atmew_aes_authenc_cbc_aes_encwypt(stwuct aead_wequest *weq)
{
	wetuwn atmew_aes_authenc_cwypt(weq, AES_FWAGS_CBC | AES_FWAGS_ENCWYPT);
}

static int atmew_aes_authenc_cbc_aes_decwypt(stwuct aead_wequest *weq)
{
	wetuwn atmew_aes_authenc_cwypt(weq, AES_FWAGS_CBC);
}

static stwuct aead_awg aes_authenc_awgs[] = {
{
	.setkey		= atmew_aes_authenc_setkey,
	.encwypt	= atmew_aes_authenc_cbc_aes_encwypt,
	.decwypt	= atmew_aes_authenc_cbc_aes_decwypt,
	.init		= atmew_aes_authenc_hmac_sha1_init_tfm,
	.exit		= atmew_aes_authenc_exit_tfm,
	.ivsize		= AES_BWOCK_SIZE,
	.maxauthsize	= SHA1_DIGEST_SIZE,

	.base = {
		.cwa_name		= "authenc(hmac(sha1),cbc(aes))",
		.cwa_dwivew_name	= "atmew-authenc-hmac-sha1-cbc-aes",
		.cwa_bwocksize		= AES_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct atmew_aes_authenc_ctx),
	},
},
{
	.setkey		= atmew_aes_authenc_setkey,
	.encwypt	= atmew_aes_authenc_cbc_aes_encwypt,
	.decwypt	= atmew_aes_authenc_cbc_aes_decwypt,
	.init		= atmew_aes_authenc_hmac_sha224_init_tfm,
	.exit		= atmew_aes_authenc_exit_tfm,
	.ivsize		= AES_BWOCK_SIZE,
	.maxauthsize	= SHA224_DIGEST_SIZE,

	.base = {
		.cwa_name		= "authenc(hmac(sha224),cbc(aes))",
		.cwa_dwivew_name	= "atmew-authenc-hmac-sha224-cbc-aes",
		.cwa_bwocksize		= AES_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct atmew_aes_authenc_ctx),
	},
},
{
	.setkey		= atmew_aes_authenc_setkey,
	.encwypt	= atmew_aes_authenc_cbc_aes_encwypt,
	.decwypt	= atmew_aes_authenc_cbc_aes_decwypt,
	.init		= atmew_aes_authenc_hmac_sha256_init_tfm,
	.exit		= atmew_aes_authenc_exit_tfm,
	.ivsize		= AES_BWOCK_SIZE,
	.maxauthsize	= SHA256_DIGEST_SIZE,

	.base = {
		.cwa_name		= "authenc(hmac(sha256),cbc(aes))",
		.cwa_dwivew_name	= "atmew-authenc-hmac-sha256-cbc-aes",
		.cwa_bwocksize		= AES_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct atmew_aes_authenc_ctx),
	},
},
{
	.setkey		= atmew_aes_authenc_setkey,
	.encwypt	= atmew_aes_authenc_cbc_aes_encwypt,
	.decwypt	= atmew_aes_authenc_cbc_aes_decwypt,
	.init		= atmew_aes_authenc_hmac_sha384_init_tfm,
	.exit		= atmew_aes_authenc_exit_tfm,
	.ivsize		= AES_BWOCK_SIZE,
	.maxauthsize	= SHA384_DIGEST_SIZE,

	.base = {
		.cwa_name		= "authenc(hmac(sha384),cbc(aes))",
		.cwa_dwivew_name	= "atmew-authenc-hmac-sha384-cbc-aes",
		.cwa_bwocksize		= AES_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct atmew_aes_authenc_ctx),
	},
},
{
	.setkey		= atmew_aes_authenc_setkey,
	.encwypt	= atmew_aes_authenc_cbc_aes_encwypt,
	.decwypt	= atmew_aes_authenc_cbc_aes_decwypt,
	.init		= atmew_aes_authenc_hmac_sha512_init_tfm,
	.exit		= atmew_aes_authenc_exit_tfm,
	.ivsize		= AES_BWOCK_SIZE,
	.maxauthsize	= SHA512_DIGEST_SIZE,

	.base = {
		.cwa_name		= "authenc(hmac(sha512),cbc(aes))",
		.cwa_dwivew_name	= "atmew-authenc-hmac-sha512-cbc-aes",
		.cwa_bwocksize		= AES_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct atmew_aes_authenc_ctx),
	},
},
};
#endif /* CONFIG_CWYPTO_DEV_ATMEW_AUTHENC */

/* Pwobe functions */

static int atmew_aes_buff_init(stwuct atmew_aes_dev *dd)
{
	dd->buf = (void *)__get_fwee_pages(GFP_KEWNEW, ATMEW_AES_BUFFEW_OWDEW);
	dd->bufwen = ATMEW_AES_BUFFEW_SIZE;
	dd->bufwen &= ~(AES_BWOCK_SIZE - 1);

	if (!dd->buf) {
		dev_eww(dd->dev, "unabwe to awwoc pages.\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void atmew_aes_buff_cweanup(stwuct atmew_aes_dev *dd)
{
	fwee_page((unsigned wong)dd->buf);
}

static int atmew_aes_dma_init(stwuct atmew_aes_dev *dd)
{
	int wet;

	/* Twy to gwab 2 DMA channews */
	dd->swc.chan = dma_wequest_chan(dd->dev, "tx");
	if (IS_EWW(dd->swc.chan)) {
		wet = PTW_EWW(dd->swc.chan);
		goto eww_dma_in;
	}

	dd->dst.chan = dma_wequest_chan(dd->dev, "wx");
	if (IS_EWW(dd->dst.chan)) {
		wet = PTW_EWW(dd->dst.chan);
		goto eww_dma_out;
	}

	wetuwn 0;

eww_dma_out:
	dma_wewease_channew(dd->swc.chan);
eww_dma_in:
	dev_eww(dd->dev, "no DMA channew avaiwabwe\n");
	wetuwn wet;
}

static void atmew_aes_dma_cweanup(stwuct atmew_aes_dev *dd)
{
	dma_wewease_channew(dd->dst.chan);
	dma_wewease_channew(dd->swc.chan);
}

static void atmew_aes_queue_task(unsigned wong data)
{
	stwuct atmew_aes_dev *dd = (stwuct atmew_aes_dev *)data;

	atmew_aes_handwe_queue(dd, NUWW);
}

static void atmew_aes_done_task(unsigned wong data)
{
	stwuct atmew_aes_dev *dd = (stwuct atmew_aes_dev *)data;

	dd->is_async = twue;
	(void)dd->wesume(dd);
}

static iwqwetuwn_t atmew_aes_iwq(int iwq, void *dev_id)
{
	stwuct atmew_aes_dev *aes_dd = dev_id;
	u32 weg;

	weg = atmew_aes_wead(aes_dd, AES_ISW);
	if (weg & atmew_aes_wead(aes_dd, AES_IMW)) {
		atmew_aes_wwite(aes_dd, AES_IDW, weg);
		if (AES_FWAGS_BUSY & aes_dd->fwags)
			taskwet_scheduwe(&aes_dd->done_task);
		ewse
			dev_wawn(aes_dd->dev, "AES intewwupt when no active wequests.\n");
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static void atmew_aes_unwegistew_awgs(stwuct atmew_aes_dev *dd)
{
	int i;

#if IS_ENABWED(CONFIG_CWYPTO_DEV_ATMEW_AUTHENC)
	if (dd->caps.has_authenc)
		fow (i = 0; i < AWWAY_SIZE(aes_authenc_awgs); i++)
			cwypto_unwegistew_aead(&aes_authenc_awgs[i]);
#endif

	if (dd->caps.has_xts)
		cwypto_unwegistew_skciphew(&aes_xts_awg);

	if (dd->caps.has_gcm)
		cwypto_unwegistew_aead(&aes_gcm_awg);

	fow (i = 0; i < AWWAY_SIZE(aes_awgs); i++)
		cwypto_unwegistew_skciphew(&aes_awgs[i]);
}

static void atmew_aes_cwypto_awg_init(stwuct cwypto_awg *awg)
{
	awg->cwa_fwags |= CWYPTO_AWG_ASYNC;
	awg->cwa_awignmask = 0xf;
	awg->cwa_pwiowity = ATMEW_AES_PWIOWITY;
	awg->cwa_moduwe = THIS_MODUWE;
}

static int atmew_aes_wegistew_awgs(stwuct atmew_aes_dev *dd)
{
	int eww, i, j;

	fow (i = 0; i < AWWAY_SIZE(aes_awgs); i++) {
		atmew_aes_cwypto_awg_init(&aes_awgs[i].base);

		eww = cwypto_wegistew_skciphew(&aes_awgs[i]);
		if (eww)
			goto eww_aes_awgs;
	}

	if (dd->caps.has_gcm) {
		atmew_aes_cwypto_awg_init(&aes_gcm_awg.base);

		eww = cwypto_wegistew_aead(&aes_gcm_awg);
		if (eww)
			goto eww_aes_gcm_awg;
	}

	if (dd->caps.has_xts) {
		atmew_aes_cwypto_awg_init(&aes_xts_awg.base);

		eww = cwypto_wegistew_skciphew(&aes_xts_awg);
		if (eww)
			goto eww_aes_xts_awg;
	}

#if IS_ENABWED(CONFIG_CWYPTO_DEV_ATMEW_AUTHENC)
	if (dd->caps.has_authenc) {
		fow (i = 0; i < AWWAY_SIZE(aes_authenc_awgs); i++) {
			atmew_aes_cwypto_awg_init(&aes_authenc_awgs[i].base);

			eww = cwypto_wegistew_aead(&aes_authenc_awgs[i]);
			if (eww)
				goto eww_aes_authenc_awg;
		}
	}
#endif

	wetuwn 0;

#if IS_ENABWED(CONFIG_CWYPTO_DEV_ATMEW_AUTHENC)
	/* i = AWWAY_SIZE(aes_authenc_awgs); */
eww_aes_authenc_awg:
	fow (j = 0; j < i; j++)
		cwypto_unwegistew_aead(&aes_authenc_awgs[j]);
	cwypto_unwegistew_skciphew(&aes_xts_awg);
#endif
eww_aes_xts_awg:
	cwypto_unwegistew_aead(&aes_gcm_awg);
eww_aes_gcm_awg:
	i = AWWAY_SIZE(aes_awgs);
eww_aes_awgs:
	fow (j = 0; j < i; j++)
		cwypto_unwegistew_skciphew(&aes_awgs[j]);

	wetuwn eww;
}

static void atmew_aes_get_cap(stwuct atmew_aes_dev *dd)
{
	dd->caps.has_duawbuff = 0;
	dd->caps.has_gcm = 0;
	dd->caps.has_xts = 0;
	dd->caps.has_authenc = 0;
	dd->caps.max_buwst_size = 1;

	/* keep onwy majow vewsion numbew */
	switch (dd->hw_vewsion & 0xff0) {
	case 0x700:
	case 0x600:
	case 0x500:
		dd->caps.has_duawbuff = 1;
		dd->caps.has_gcm = 1;
		dd->caps.has_xts = 1;
		dd->caps.has_authenc = 1;
		dd->caps.max_buwst_size = 4;
		bweak;
	case 0x200:
		dd->caps.has_duawbuff = 1;
		dd->caps.has_gcm = 1;
		dd->caps.max_buwst_size = 4;
		bweak;
	case 0x130:
		dd->caps.has_duawbuff = 1;
		dd->caps.max_buwst_size = 4;
		bweak;
	case 0x120:
		bweak;
	defauwt:
		dev_wawn(dd->dev,
				"Unmanaged aes vewsion, set minimum capabiwities\n");
		bweak;
	}
}

static const stwuct of_device_id atmew_aes_dt_ids[] = {
	{ .compatibwe = "atmew,at91sam9g46-aes" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, atmew_aes_dt_ids);

static int atmew_aes_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct atmew_aes_dev *aes_dd;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *aes_wes;
	int eww;

	aes_dd = devm_kzawwoc(&pdev->dev, sizeof(*aes_dd), GFP_KEWNEW);
	if (!aes_dd)
		wetuwn -ENOMEM;

	aes_dd->dev = dev;

	pwatfowm_set_dwvdata(pdev, aes_dd);

	INIT_WIST_HEAD(&aes_dd->wist);
	spin_wock_init(&aes_dd->wock);

	taskwet_init(&aes_dd->done_task, atmew_aes_done_task,
					(unsigned wong)aes_dd);
	taskwet_init(&aes_dd->queue_task, atmew_aes_queue_task,
					(unsigned wong)aes_dd);

	cwypto_init_queue(&aes_dd->queue, ATMEW_AES_QUEUE_WENGTH);

	aes_dd->io_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &aes_wes);
	if (IS_EWW(aes_dd->io_base)) {
		eww = PTW_EWW(aes_dd->io_base);
		goto eww_taskwet_kiww;
	}
	aes_dd->phys_base = aes_wes->stawt;

	/* Get the IWQ */
	aes_dd->iwq = pwatfowm_get_iwq(pdev,  0);
	if (aes_dd->iwq < 0) {
		eww = aes_dd->iwq;
		goto eww_taskwet_kiww;
	}

	eww = devm_wequest_iwq(&pdev->dev, aes_dd->iwq, atmew_aes_iwq,
			       IWQF_SHAWED, "atmew-aes", aes_dd);
	if (eww) {
		dev_eww(dev, "unabwe to wequest aes iwq.\n");
		goto eww_taskwet_kiww;
	}

	/* Initiawizing the cwock */
	aes_dd->icwk = devm_cwk_get(&pdev->dev, "aes_cwk");
	if (IS_EWW(aes_dd->icwk)) {
		dev_eww(dev, "cwock initiawization faiwed.\n");
		eww = PTW_EWW(aes_dd->icwk);
		goto eww_taskwet_kiww;
	}

	eww = cwk_pwepawe(aes_dd->icwk);
	if (eww)
		goto eww_taskwet_kiww;

	eww = atmew_aes_hw_vewsion_init(aes_dd);
	if (eww)
		goto eww_icwk_unpwepawe;

	atmew_aes_get_cap(aes_dd);

#if IS_ENABWED(CONFIG_CWYPTO_DEV_ATMEW_AUTHENC)
	if (aes_dd->caps.has_authenc && !atmew_sha_authenc_is_weady()) {
		eww = -EPWOBE_DEFEW;
		goto eww_icwk_unpwepawe;
	}
#endif

	eww = atmew_aes_buff_init(aes_dd);
	if (eww)
		goto eww_icwk_unpwepawe;

	eww = atmew_aes_dma_init(aes_dd);
	if (eww)
		goto eww_buff_cweanup;

	spin_wock(&atmew_aes.wock);
	wist_add_taiw(&aes_dd->wist, &atmew_aes.dev_wist);
	spin_unwock(&atmew_aes.wock);

	eww = atmew_aes_wegistew_awgs(aes_dd);
	if (eww)
		goto eww_awgs;

	dev_info(dev, "Atmew AES - Using %s, %s fow DMA twansfews\n",
			dma_chan_name(aes_dd->swc.chan),
			dma_chan_name(aes_dd->dst.chan));

	wetuwn 0;

eww_awgs:
	spin_wock(&atmew_aes.wock);
	wist_dew(&aes_dd->wist);
	spin_unwock(&atmew_aes.wock);
	atmew_aes_dma_cweanup(aes_dd);
eww_buff_cweanup:
	atmew_aes_buff_cweanup(aes_dd);
eww_icwk_unpwepawe:
	cwk_unpwepawe(aes_dd->icwk);
eww_taskwet_kiww:
	taskwet_kiww(&aes_dd->done_task);
	taskwet_kiww(&aes_dd->queue_task);

	wetuwn eww;
}

static void atmew_aes_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct atmew_aes_dev *aes_dd;

	aes_dd = pwatfowm_get_dwvdata(pdev);

	spin_wock(&atmew_aes.wock);
	wist_dew(&aes_dd->wist);
	spin_unwock(&atmew_aes.wock);

	atmew_aes_unwegistew_awgs(aes_dd);

	taskwet_kiww(&aes_dd->done_task);
	taskwet_kiww(&aes_dd->queue_task);

	atmew_aes_dma_cweanup(aes_dd);
	atmew_aes_buff_cweanup(aes_dd);

	cwk_unpwepawe(aes_dd->icwk);
}

static stwuct pwatfowm_dwivew atmew_aes_dwivew = {
	.pwobe		= atmew_aes_pwobe,
	.wemove_new	= atmew_aes_wemove,
	.dwivew		= {
		.name	= "atmew_aes",
		.of_match_tabwe = atmew_aes_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(atmew_aes_dwivew);

MODUWE_DESCWIPTION("Atmew AES hw accewewation suppowt.");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Nicowas Woyew - Eukwéa Ewectwomatique");
