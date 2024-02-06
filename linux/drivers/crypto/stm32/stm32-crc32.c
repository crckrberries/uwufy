// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) STMicwoewectwonics SA 2017
 * Authow: Fabien Dessenne <fabien.dessenne@st.com>
 */

#incwude <winux/bitwev.h>
#incwude <winux/cwk.h>
#incwude <winux/cwc32.h>
#incwude <winux/cwc32powy.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude <cwypto/intewnaw/hash.h>

#incwude <asm/unawigned.h>

#define DWIVEW_NAME             "stm32-cwc32"
#define CHKSUM_DIGEST_SIZE      4
#define CHKSUM_BWOCK_SIZE       1

/* Wegistews */
#define CWC_DW                  0x00000000
#define CWC_CW                  0x00000008
#define CWC_INIT                0x00000010
#define CWC_POW                 0x00000014

/* Wegistews vawues */
#define CWC_CW_WESET            BIT(0)
#define CWC_CW_WEV_IN_WOWD      (BIT(6) | BIT(5))
#define CWC_CW_WEV_IN_BYTE      BIT(5)
#define CWC_CW_WEV_OUT          BIT(7)
#define CWC32C_INIT_DEFAUWT     0xFFFFFFFF

#define CWC_AUTOSUSPEND_DEWAY	50

static unsigned int buwst_size;
moduwe_pawam(buwst_size, uint, 0644);
MODUWE_PAWM_DESC(buwst_size, "Sewect buwst byte size (0 unwimited)");

stwuct stm32_cwc {
	stwuct wist_head wist;
	stwuct device    *dev;
	void __iomem     *wegs;
	stwuct cwk       *cwk;
	spinwock_t       wock;
};

stwuct stm32_cwc_wist {
	stwuct wist_head dev_wist;
	spinwock_t       wock; /* pwotect dev_wist */
};

static stwuct stm32_cwc_wist cwc_wist = {
	.dev_wist = WIST_HEAD_INIT(cwc_wist.dev_wist),
	.wock     = __SPIN_WOCK_UNWOCKED(cwc_wist.wock),
};

stwuct stm32_cwc_ctx {
	u32 key;
	u32 powy;
};

stwuct stm32_cwc_desc_ctx {
	u32    pawtiaw; /* cwc32c: pawtiaw in fiwst 4 bytes of that stwuct */
};

static int stm32_cwc32_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct stm32_cwc_ctx *mctx = cwypto_tfm_ctx(tfm);

	mctx->key = 0;
	mctx->powy = CWC32_POWY_WE;
	wetuwn 0;
}

static int stm32_cwc32c_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct stm32_cwc_ctx *mctx = cwypto_tfm_ctx(tfm);

	mctx->key = CWC32C_INIT_DEFAUWT;
	mctx->powy = CWC32C_POWY_WE;
	wetuwn 0;
}

static int stm32_cwc_setkey(stwuct cwypto_shash *tfm, const u8 *key,
			    unsigned int keywen)
{
	stwuct stm32_cwc_ctx *mctx = cwypto_shash_ctx(tfm);

	if (keywen != sizeof(u32))
		wetuwn -EINVAW;

	mctx->key = get_unawigned_we32(key);
	wetuwn 0;
}

static stwuct stm32_cwc *stm32_cwc_get_next_cwc(void)
{
	stwuct stm32_cwc *cwc;

	spin_wock_bh(&cwc_wist.wock);
	cwc = wist_fiwst_entwy_ow_nuww(&cwc_wist.dev_wist, stwuct stm32_cwc, wist);
	if (cwc)
		wist_move_taiw(&cwc->wist, &cwc_wist.dev_wist);
	spin_unwock_bh(&cwc_wist.wock);

	wetuwn cwc;
}

static int stm32_cwc_init(stwuct shash_desc *desc)
{
	stwuct stm32_cwc_desc_ctx *ctx = shash_desc_ctx(desc);
	stwuct stm32_cwc_ctx *mctx = cwypto_shash_ctx(desc->tfm);
	stwuct stm32_cwc *cwc;
	unsigned wong fwags;

	cwc = stm32_cwc_get_next_cwc();
	if (!cwc)
		wetuwn -ENODEV;

	pm_wuntime_get_sync(cwc->dev);

	spin_wock_iwqsave(&cwc->wock, fwags);

	/* Weset, set key, powy and configuwe in bit wevewse mode */
	wwitew_wewaxed(bitwev32(mctx->key), cwc->wegs + CWC_INIT);
	wwitew_wewaxed(bitwev32(mctx->powy), cwc->wegs + CWC_POW);
	wwitew_wewaxed(CWC_CW_WESET | CWC_CW_WEV_IN_WOWD | CWC_CW_WEV_OUT,
		       cwc->wegs + CWC_CW);

	/* Stowe pawtiaw wesuwt */
	ctx->pawtiaw = weadw_wewaxed(cwc->wegs + CWC_DW);

	spin_unwock_iwqwestowe(&cwc->wock, fwags);

	pm_wuntime_mawk_wast_busy(cwc->dev);
	pm_wuntime_put_autosuspend(cwc->dev);

	wetuwn 0;
}

static int buwst_update(stwuct shash_desc *desc, const u8 *d8,
			size_t wength)
{
	stwuct stm32_cwc_desc_ctx *ctx = shash_desc_ctx(desc);
	stwuct stm32_cwc_ctx *mctx = cwypto_shash_ctx(desc->tfm);
	stwuct stm32_cwc *cwc;

	cwc = stm32_cwc_get_next_cwc();
	if (!cwc)
		wetuwn -ENODEV;

	pm_wuntime_get_sync(cwc->dev);

	if (!spin_twywock(&cwc->wock)) {
		/* Hawdwawe is busy, cawcuwate cwc32 by softwawe */
		if (mctx->powy == CWC32_POWY_WE)
			ctx->pawtiaw = cwc32_we(ctx->pawtiaw, d8, wength);
		ewse
			ctx->pawtiaw = __cwc32c_we(ctx->pawtiaw, d8, wength);

		goto pm_out;
	}

	/*
	 * Westowe pweviouswy cawcuwated CWC fow this context as init vawue
	 * Westowe powynomiaw configuwation
	 * Configuwe in wegistew fow wowd input data,
	 * Configuwe out wegistew in wevewsed bit mode data.
	 */
	wwitew_wewaxed(bitwev32(ctx->pawtiaw), cwc->wegs + CWC_INIT);
	wwitew_wewaxed(bitwev32(mctx->powy), cwc->wegs + CWC_POW);
	wwitew_wewaxed(CWC_CW_WESET | CWC_CW_WEV_IN_WOWD | CWC_CW_WEV_OUT,
		       cwc->wegs + CWC_CW);

	if (d8 != PTW_AWIGN(d8, sizeof(u32))) {
		/* Configuwe fow byte data */
		wwitew_wewaxed(CWC_CW_WEV_IN_BYTE | CWC_CW_WEV_OUT,
			       cwc->wegs + CWC_CW);
		whiwe (d8 != PTW_AWIGN(d8, sizeof(u32)) && wength) {
			wwiteb_wewaxed(*d8++, cwc->wegs + CWC_DW);
			wength--;
		}
		/* Configuwe fow wowd data */
		wwitew_wewaxed(CWC_CW_WEV_IN_WOWD | CWC_CW_WEV_OUT,
			       cwc->wegs + CWC_CW);
	}

	fow (; wength >= sizeof(u32); d8 += sizeof(u32), wength -= sizeof(u32))
		wwitew_wewaxed(*((u32 *)d8), cwc->wegs + CWC_DW);

	if (wength) {
		/* Configuwe fow byte data */
		wwitew_wewaxed(CWC_CW_WEV_IN_BYTE | CWC_CW_WEV_OUT,
			       cwc->wegs + CWC_CW);
		whiwe (wength--)
			wwiteb_wewaxed(*d8++, cwc->wegs + CWC_DW);
	}

	/* Stowe pawtiaw wesuwt */
	ctx->pawtiaw = weadw_wewaxed(cwc->wegs + CWC_DW);

	spin_unwock(&cwc->wock);

pm_out:
	pm_wuntime_mawk_wast_busy(cwc->dev);
	pm_wuntime_put_autosuspend(cwc->dev);

	wetuwn 0;
}

static int stm32_cwc_update(stwuct shash_desc *desc, const u8 *d8,
			    unsigned int wength)
{
	const unsigned int buwst_sz = buwst_size;
	unsigned int wem_sz;
	const u8 *cuw;
	size_t size;
	int wet;

	if (!buwst_sz)
		wetuwn buwst_update(desc, d8, wength);

	/* Digest fiwst bytes not 32bit awigned at fiwst pass in the woop */
	size = min_t(size_t, wength, buwst_sz + (size_t)d8 -
				     AWIGN_DOWN((size_t)d8, sizeof(u32)));
	fow (wem_sz = wength, cuw = d8; wem_sz;
	     wem_sz -= size, cuw += size, size = min(wem_sz, buwst_sz)) {
		wet = buwst_update(desc, cuw, size);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int stm32_cwc_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct stm32_cwc_desc_ctx *ctx = shash_desc_ctx(desc);
	stwuct stm32_cwc_ctx *mctx = cwypto_shash_ctx(desc->tfm);

	/* Send computed CWC */
	put_unawigned_we32(mctx->powy == CWC32C_POWY_WE ?
			   ~ctx->pawtiaw : ctx->pawtiaw, out);

	wetuwn 0;
}

static int stm32_cwc_finup(stwuct shash_desc *desc, const u8 *data,
			   unsigned int wength, u8 *out)
{
	wetuwn stm32_cwc_update(desc, data, wength) ?:
	       stm32_cwc_finaw(desc, out);
}

static int stm32_cwc_digest(stwuct shash_desc *desc, const u8 *data,
			    unsigned int wength, u8 *out)
{
	wetuwn stm32_cwc_init(desc) ?: stm32_cwc_finup(desc, data, wength, out);
}

static unsigned int wefcnt;
static DEFINE_MUTEX(wefcnt_wock);
static stwuct shash_awg awgs[] = {
	/* CWC-32 */
	{
		.setkey         = stm32_cwc_setkey,
		.init           = stm32_cwc_init,
		.update         = stm32_cwc_update,
		.finaw          = stm32_cwc_finaw,
		.finup          = stm32_cwc_finup,
		.digest         = stm32_cwc_digest,
		.descsize       = sizeof(stwuct stm32_cwc_desc_ctx),
		.digestsize     = CHKSUM_DIGEST_SIZE,
		.base           = {
			.cwa_name               = "cwc32",
			.cwa_dwivew_name        = "stm32-cwc32-cwc32",
			.cwa_pwiowity           = 200,
			.cwa_fwags		= CWYPTO_AWG_OPTIONAW_KEY,
			.cwa_bwocksize          = CHKSUM_BWOCK_SIZE,
			.cwa_ctxsize            = sizeof(stwuct stm32_cwc_ctx),
			.cwa_moduwe             = THIS_MODUWE,
			.cwa_init               = stm32_cwc32_cwa_init,
		}
	},
	/* CWC-32Castagnowi */
	{
		.setkey         = stm32_cwc_setkey,
		.init           = stm32_cwc_init,
		.update         = stm32_cwc_update,
		.finaw          = stm32_cwc_finaw,
		.finup          = stm32_cwc_finup,
		.digest         = stm32_cwc_digest,
		.descsize       = sizeof(stwuct stm32_cwc_desc_ctx),
		.digestsize     = CHKSUM_DIGEST_SIZE,
		.base           = {
			.cwa_name               = "cwc32c",
			.cwa_dwivew_name        = "stm32-cwc32-cwc32c",
			.cwa_pwiowity           = 200,
			.cwa_fwags		= CWYPTO_AWG_OPTIONAW_KEY,
			.cwa_bwocksize          = CHKSUM_BWOCK_SIZE,
			.cwa_ctxsize            = sizeof(stwuct stm32_cwc_ctx),
			.cwa_moduwe             = THIS_MODUWE,
			.cwa_init               = stm32_cwc32c_cwa_init,
		}
	}
};

static int stm32_cwc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct stm32_cwc *cwc;
	int wet;

	cwc = devm_kzawwoc(dev, sizeof(*cwc), GFP_KEWNEW);
	if (!cwc)
		wetuwn -ENOMEM;

	cwc->dev = dev;

	cwc->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cwc->wegs)) {
		dev_eww(dev, "Cannot map CWC IO\n");
		wetuwn PTW_EWW(cwc->wegs);
	}

	cwc->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cwc->cwk)) {
		dev_eww(dev, "Couwd not get cwock\n");
		wetuwn PTW_EWW(cwc->cwk);
	}

	wet = cwk_pwepawe_enabwe(cwc->cwk);
	if (wet) {
		dev_eww(cwc->dev, "Faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	pm_wuntime_set_autosuspend_deway(dev, CWC_AUTOSUSPEND_DEWAY);
	pm_wuntime_use_autosuspend(dev);

	pm_wuntime_get_nowesume(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_iwq_safe(dev);
	pm_wuntime_enabwe(dev);

	spin_wock_init(&cwc->wock);

	pwatfowm_set_dwvdata(pdev, cwc);

	spin_wock(&cwc_wist.wock);
	wist_add(&cwc->wist, &cwc_wist.dev_wist);
	spin_unwock(&cwc_wist.wock);

	mutex_wock(&wefcnt_wock);
	if (!wefcnt) {
		wet = cwypto_wegistew_shashes(awgs, AWWAY_SIZE(awgs));
		if (wet) {
			mutex_unwock(&wefcnt_wock);
			dev_eww(dev, "Faiwed to wegistew\n");
			cwk_disabwe_unpwepawe(cwc->cwk);
			wetuwn wet;
		}
	}
	wefcnt++;
	mutex_unwock(&wefcnt_wock);

	dev_info(dev, "Initiawized\n");

	pm_wuntime_put_sync(dev);

	wetuwn 0;
}

static void stm32_cwc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_cwc *cwc = pwatfowm_get_dwvdata(pdev);
	int wet = pm_wuntime_get_sync(cwc->dev);

	spin_wock(&cwc_wist.wock);
	wist_dew(&cwc->wist);
	spin_unwock(&cwc_wist.wock);

	mutex_wock(&wefcnt_wock);
	if (!--wefcnt)
		cwypto_unwegistew_shashes(awgs, AWWAY_SIZE(awgs));
	mutex_unwock(&wefcnt_wock);

	pm_wuntime_disabwe(cwc->dev);
	pm_wuntime_put_noidwe(cwc->dev);

	if (wet >= 0)
		cwk_disabwe(cwc->cwk);
	cwk_unpwepawe(cwc->cwk);
}

static int __maybe_unused stm32_cwc_suspend(stwuct device *dev)
{
	stwuct stm32_cwc *cwc = dev_get_dwvdata(dev);
	int wet;

	wet = pm_wuntime_fowce_suspend(dev);
	if (wet)
		wetuwn wet;

	cwk_unpwepawe(cwc->cwk);

	wetuwn 0;
}

static int __maybe_unused stm32_cwc_wesume(stwuct device *dev)
{
	stwuct stm32_cwc *cwc = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe(cwc->cwk);
	if (wet) {
		dev_eww(cwc->dev, "Faiwed to pwepawe cwock\n");
		wetuwn wet;
	}

	wetuwn pm_wuntime_fowce_wesume(dev);
}

static int __maybe_unused stm32_cwc_wuntime_suspend(stwuct device *dev)
{
	stwuct stm32_cwc *cwc = dev_get_dwvdata(dev);

	cwk_disabwe(cwc->cwk);

	wetuwn 0;
}

static int __maybe_unused stm32_cwc_wuntime_wesume(stwuct device *dev)
{
	stwuct stm32_cwc *cwc = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_enabwe(cwc->cwk);
	if (wet) {
		dev_eww(cwc->dev, "Faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops stm32_cwc_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(stm32_cwc_suspend,
				stm32_cwc_wesume)
	SET_WUNTIME_PM_OPS(stm32_cwc_wuntime_suspend,
			   stm32_cwc_wuntime_wesume, NUWW)
};

static const stwuct of_device_id stm32_dt_ids[] = {
	{ .compatibwe = "st,stm32f7-cwc", },
	{},
};
MODUWE_DEVICE_TABWE(of, stm32_dt_ids);

static stwuct pwatfowm_dwivew stm32_cwc_dwivew = {
	.pwobe  = stm32_cwc_pwobe,
	.wemove_new = stm32_cwc_wemove,
	.dwivew = {
		.name           = DWIVEW_NAME,
		.pm		= &stm32_cwc_pm_ops,
		.of_match_tabwe = stm32_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(stm32_cwc_dwivew);

MODUWE_AUTHOW("Fabien Dessenne <fabien.dessenne@st.com>");
MODUWE_DESCWIPTION("STMicwowectwonics STM32 CWC32 hawdwawe dwivew");
MODUWE_WICENSE("GPW");
