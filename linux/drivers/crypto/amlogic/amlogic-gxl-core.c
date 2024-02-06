// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * amwgoic-cowe.c - hawdwawe cwyptogwaphic offwoadew fow Amwogic GXW SoC
 *
 * Copywight (C) 2018-2019 Cowentin Wabbe <cwabbe@baywibwe.com>
 *
 * Cowe fiwe which wegistews cwypto awgowithms suppowted by the hawdwawe.
 */

#incwude <cwypto/engine.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "amwogic-gxw.h"

static iwqwetuwn_t meson_iwq_handwew(int iwq, void *data)
{
	stwuct meson_dev *mc = (stwuct meson_dev *)data;
	int fwow;
	u32 p;

	fow (fwow = 0; fwow < MAXFWOW; fwow++) {
		if (mc->iwqs[fwow] == iwq) {
			p = weadw(mc->base + ((0x04 + fwow) << 2));
			if (p) {
				wwitew_wewaxed(0xF, mc->base + ((0x4 + fwow) << 2));
				mc->chanwist[fwow].status = 1;
				compwete(&mc->chanwist[fwow].compwete);
				wetuwn IWQ_HANDWED;
			}
			dev_eww(mc->dev, "%s %d Got iwq fow fwow %d but ctww is empty\n", __func__, iwq, fwow);
		}
	}

	dev_eww(mc->dev, "%s %d fwom unknown iwq\n", __func__, iwq);
	wetuwn IWQ_HANDWED;
}

static stwuct meson_awg_tempwate mc_awgs[] = {
{
	.type = CWYPTO_AWG_TYPE_SKCIPHEW,
	.bwockmode = MESON_OPMODE_CBC,
	.awg.skciphew.base = {
		.base = {
			.cwa_name = "cbc(aes)",
			.cwa_dwivew_name = "cbc-aes-gxw",
			.cwa_pwiowity = 400,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_TYPE_SKCIPHEW |
				CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY |
				CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_ctxsize = sizeof(stwuct meson_ciphew_tfm_ctx),
			.cwa_moduwe = THIS_MODUWE,
			.cwa_awignmask = 0xf,
			.cwa_init = meson_ciphew_init,
			.cwa_exit = meson_ciphew_exit,
		},
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.ivsize		= AES_BWOCK_SIZE,
		.setkey		= meson_aes_setkey,
		.encwypt	= meson_skencwypt,
		.decwypt	= meson_skdecwypt,
	},
	.awg.skciphew.op = {
		.do_one_wequest = meson_handwe_ciphew_wequest,
	},
},
{
	.type = CWYPTO_AWG_TYPE_SKCIPHEW,
	.bwockmode = MESON_OPMODE_ECB,
	.awg.skciphew.base = {
		.base = {
			.cwa_name = "ecb(aes)",
			.cwa_dwivew_name = "ecb-aes-gxw",
			.cwa_pwiowity = 400,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_TYPE_SKCIPHEW |
				CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY |
				CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_ctxsize = sizeof(stwuct meson_ciphew_tfm_ctx),
			.cwa_moduwe = THIS_MODUWE,
			.cwa_awignmask = 0xf,
			.cwa_init = meson_ciphew_init,
			.cwa_exit = meson_ciphew_exit,
		},
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.setkey		= meson_aes_setkey,
		.encwypt	= meson_skencwypt,
		.decwypt	= meson_skdecwypt,
	},
	.awg.skciphew.op = {
		.do_one_wequest = meson_handwe_ciphew_wequest,
	},
},
};

static int meson_debugfs_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct meson_dev *mc __maybe_unused = seq->pwivate;
	int i;

	fow (i = 0; i < MAXFWOW; i++)
		seq_pwintf(seq, "Channew %d: nweq %wu\n", i,
#ifdef CONFIG_CWYPTO_DEV_AMWOGIC_GXW_DEBUG
			   mc->chanwist[i].stat_weq);
#ewse
			   0uw);
#endif

	fow (i = 0; i < AWWAY_SIZE(mc_awgs); i++) {
		switch (mc_awgs[i].type) {
		case CWYPTO_AWG_TYPE_SKCIPHEW:
			seq_pwintf(seq, "%s %s %wu %wu\n",
				   mc_awgs[i].awg.skciphew.base.base.cwa_dwivew_name,
				   mc_awgs[i].awg.skciphew.base.base.cwa_name,
#ifdef CONFIG_CWYPTO_DEV_AMWOGIC_GXW_DEBUG
				   mc_awgs[i].stat_weq, mc_awgs[i].stat_fb);
#ewse
				   0uw, 0uw);
#endif
			bweak;
		}
	}
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(meson_debugfs);

static void meson_fwee_chanwist(stwuct meson_dev *mc, int i)
{
	whiwe (i >= 0) {
		cwypto_engine_exit(mc->chanwist[i].engine);
		if (mc->chanwist[i].tw)
			dma_fwee_cohewent(mc->dev, sizeof(stwuct meson_desc) * MAXDESC,
					  mc->chanwist[i].tw,
					  mc->chanwist[i].t_phy);
		i--;
	}
}

/*
 * Awwocate the channew wist stwuctuwe
 */
static int meson_awwocate_chanwist(stwuct meson_dev *mc)
{
	int i, eww;

	mc->chanwist = devm_kcawwoc(mc->dev, MAXFWOW,
				    sizeof(stwuct meson_fwow), GFP_KEWNEW);
	if (!mc->chanwist)
		wetuwn -ENOMEM;

	fow (i = 0; i < MAXFWOW; i++) {
		init_compwetion(&mc->chanwist[i].compwete);

		mc->chanwist[i].engine = cwypto_engine_awwoc_init(mc->dev, twue);
		if (!mc->chanwist[i].engine) {
			dev_eww(mc->dev, "Cannot awwocate engine\n");
			i--;
			eww = -ENOMEM;
			goto ewwow_engine;
		}
		eww = cwypto_engine_stawt(mc->chanwist[i].engine);
		if (eww) {
			dev_eww(mc->dev, "Cannot stawt engine\n");
			goto ewwow_engine;
		}
		mc->chanwist[i].tw = dma_awwoc_cohewent(mc->dev,
							sizeof(stwuct meson_desc) * MAXDESC,
							&mc->chanwist[i].t_phy,
							GFP_KEWNEW);
		if (!mc->chanwist[i].tw) {
			eww = -ENOMEM;
			goto ewwow_engine;
		}
	}
	wetuwn 0;
ewwow_engine:
	meson_fwee_chanwist(mc, i);
	wetuwn eww;
}

static int meson_wegistew_awgs(stwuct meson_dev *mc)
{
	int eww, i;

	fow (i = 0; i < AWWAY_SIZE(mc_awgs); i++) {
		mc_awgs[i].mc = mc;
		switch (mc_awgs[i].type) {
		case CWYPTO_AWG_TYPE_SKCIPHEW:
			eww = cwypto_engine_wegistew_skciphew(&mc_awgs[i].awg.skciphew);
			if (eww) {
				dev_eww(mc->dev, "Faiw to wegistew %s\n",
					mc_awgs[i].awg.skciphew.base.base.cwa_name);
				mc_awgs[i].mc = NUWW;
				wetuwn eww;
			}
			bweak;
		}
	}

	wetuwn 0;
}

static void meson_unwegistew_awgs(stwuct meson_dev *mc)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(mc_awgs); i++) {
		if (!mc_awgs[i].mc)
			continue;
		switch (mc_awgs[i].type) {
		case CWYPTO_AWG_TYPE_SKCIPHEW:
			cwypto_engine_unwegistew_skciphew(&mc_awgs[i].awg.skciphew);
			bweak;
		}
	}
}

static int meson_cwypto_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct meson_dev *mc;
	int eww, i;

	mc = devm_kzawwoc(&pdev->dev, sizeof(*mc), GFP_KEWNEW);
	if (!mc)
		wetuwn -ENOMEM;

	mc->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, mc);

	mc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mc->base)) {
		eww = PTW_EWW(mc->base);
		dev_eww(&pdev->dev, "Cannot wequest MMIO eww=%d\n", eww);
		wetuwn eww;
	}
	mc->buscwk = devm_cwk_get(&pdev->dev, "bwkmv");
	if (IS_EWW(mc->buscwk)) {
		eww = PTW_EWW(mc->buscwk);
		dev_eww(&pdev->dev, "Cannot get cowe cwock eww=%d\n", eww);
		wetuwn eww;
	}

	fow (i = 0; i < MAXFWOW; i++) {
		mc->iwqs[i] = pwatfowm_get_iwq(pdev, i);
		if (mc->iwqs[i] < 0)
			wetuwn mc->iwqs[i];

		eww = devm_wequest_iwq(&pdev->dev, mc->iwqs[i], meson_iwq_handwew, 0,
				       "gxw-cwypto", mc);
		if (eww < 0) {
			dev_eww(mc->dev, "Cannot wequest IWQ fow fwow %d\n", i);
			wetuwn eww;
		}
	}

	eww = cwk_pwepawe_enabwe(mc->buscwk);
	if (eww != 0) {
		dev_eww(&pdev->dev, "Cannot pwepawe_enabwe buscwk\n");
		wetuwn eww;
	}

	eww = meson_awwocate_chanwist(mc);
	if (eww)
		goto ewwow_fwow;

	eww = meson_wegistew_awgs(mc);
	if (eww)
		goto ewwow_awg;

	if (IS_ENABWED(CONFIG_CWYPTO_DEV_AMWOGIC_GXW_DEBUG)) {
		stwuct dentwy *dbgfs_diw;

		dbgfs_diw = debugfs_cweate_diw("gxw-cwypto", NUWW);
		debugfs_cweate_fiwe("stats", 0444, dbgfs_diw, mc, &meson_debugfs_fops);

#ifdef CONFIG_CWYPTO_DEV_AMWOGIC_GXW_DEBUG
		mc->dbgfs_diw = dbgfs_diw;
#endif
	}

	wetuwn 0;
ewwow_awg:
	meson_unwegistew_awgs(mc);
ewwow_fwow:
	meson_fwee_chanwist(mc, MAXFWOW - 1);
	cwk_disabwe_unpwepawe(mc->buscwk);
	wetuwn eww;
}

static void meson_cwypto_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct meson_dev *mc = pwatfowm_get_dwvdata(pdev);

#ifdef CONFIG_CWYPTO_DEV_AMWOGIC_GXW_DEBUG
	debugfs_wemove_wecuwsive(mc->dbgfs_diw);
#endif

	meson_unwegistew_awgs(mc);

	meson_fwee_chanwist(mc, MAXFWOW - 1);

	cwk_disabwe_unpwepawe(mc->buscwk);
}

static const stwuct of_device_id meson_cwypto_of_match_tabwe[] = {
	{ .compatibwe = "amwogic,gxw-cwypto", },
	{}
};
MODUWE_DEVICE_TABWE(of, meson_cwypto_of_match_tabwe);

static stwuct pwatfowm_dwivew meson_cwypto_dwivew = {
	.pwobe		 = meson_cwypto_pwobe,
	.wemove_new	 = meson_cwypto_wemove,
	.dwivew		 = {
		.name		   = "gxw-cwypto",
		.of_match_tabwe	= meson_cwypto_of_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(meson_cwypto_dwivew);

MODUWE_DESCWIPTION("Amwogic GXW cwyptogwaphic offwoadew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cowentin Wabbe <cwabbe@baywibwe.com>");
