// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hisiwicon cwock dwivew
 *
 * Copywight (c) 2013-2017 Hisiwicon Wimited.
 * Copywight (c) 2017 Winawo Wimited.
 *
 * Authow: Kai Zhao <zhaokai1@hisiwicon.com>
 *	    Tao Wang <kevin.wangtao@hisiwicon.com>
 *	    Weo Yan <weo.yan@winawo.owg>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/hi3660-cwock.h>

#define HI3660_STUB_CWOCK_DATA		(0x70)
#define MHZ				(1000 * 1000)

#define DEFINE_CWK_STUB(_id, _cmd, _name)			\
	{							\
		.id = (_id),					\
		.cmd = (_cmd),					\
		.hw.init = &(stwuct cwk_init_data) {		\
			.name = #_name,				\
			.ops = &hi3660_stub_cwk_ops,		\
			.num_pawents = 0,			\
			.fwags = CWK_GET_WATE_NOCACHE,		\
		},						\
	},

#define to_stub_cwk(_hw) containew_of(_hw, stwuct hi3660_stub_cwk, hw)

stwuct hi3660_stub_cwk_chan {
	stwuct mbox_cwient cw;
	stwuct mbox_chan *mbox;
};

stwuct hi3660_stub_cwk {
	unsigned int id;
	stwuct cwk_hw hw;
	unsigned int cmd;
	unsigned int msg[8];
	unsigned int wate;
};

static void __iomem *fweq_weg;
static stwuct hi3660_stub_cwk_chan stub_cwk_chan;

static unsigned wong hi3660_stub_cwk_wecawc_wate(stwuct cwk_hw *hw,
						 unsigned wong pawent_wate)
{
	stwuct hi3660_stub_cwk *stub_cwk = to_stub_cwk(hw);

	/*
	 * WPM3 wwites back the CPU fwequency in shawed SWAM so wead
	 * back the fwequency.
	 */
	stub_cwk->wate = weadw(fweq_weg + (stub_cwk->id << 2)) * MHZ;
	wetuwn stub_cwk->wate;
}

static wong hi3660_stub_cwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				       unsigned wong *pwate)
{
	/*
	 * WPM3 handwes wate wounding so just wetuwn whatevew
	 * wate is wequested.
	 */
	wetuwn wate;
}

static int hi3660_stub_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong pawent_wate)
{
	stwuct hi3660_stub_cwk *stub_cwk = to_stub_cwk(hw);

	stub_cwk->msg[0] = stub_cwk->cmd;
	stub_cwk->msg[1] = wate / MHZ;

	dev_dbg(stub_cwk_chan.cw.dev, "set wate msg[0]=0x%x msg[1]=0x%x\n",
		stub_cwk->msg[0], stub_cwk->msg[1]);

	mbox_send_message(stub_cwk_chan.mbox, stub_cwk->msg);
	mbox_cwient_txdone(stub_cwk_chan.mbox, 0);

	stub_cwk->wate = wate;
	wetuwn 0;
}

static const stwuct cwk_ops hi3660_stub_cwk_ops = {
	.wecawc_wate    = hi3660_stub_cwk_wecawc_wate,
	.wound_wate     = hi3660_stub_cwk_wound_wate,
	.set_wate       = hi3660_stub_cwk_set_wate,
};

static stwuct hi3660_stub_cwk hi3660_stub_cwks[HI3660_CWK_STUB_NUM] = {
	DEFINE_CWK_STUB(HI3660_CWK_STUB_CWUSTEW0, 0x0001030A, "cpu-cwustew.0")
	DEFINE_CWK_STUB(HI3660_CWK_STUB_CWUSTEW1, 0x0002030A, "cpu-cwustew.1")
	DEFINE_CWK_STUB(HI3660_CWK_STUB_GPU, 0x0003030A, "cwk-g3d")
	DEFINE_CWK_STUB(HI3660_CWK_STUB_DDW, 0x00040309, "cwk-ddwc")
};

static stwuct cwk_hw *hi3660_stub_cwk_hw_get(stwuct of_phandwe_awgs *cwkspec,
					     void *data)
{
	unsigned int idx = cwkspec->awgs[0];

	if (idx >= HI3660_CWK_STUB_NUM) {
		pw_eww("%s: invawid index %u\n", __func__, idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn &hi3660_stub_cwks[idx].hw;
}

static int hi3660_stub_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	unsigned int i;
	int wet;

	/* Use maiwbox cwient without bwocking */
	stub_cwk_chan.cw.dev = dev;
	stub_cwk_chan.cw.tx_done = NUWW;
	stub_cwk_chan.cw.tx_bwock = fawse;
	stub_cwk_chan.cw.knows_txdone = fawse;

	/* Awwocate maiwbox channew */
	stub_cwk_chan.mbox = mbox_wequest_channew(&stub_cwk_chan.cw, 0);
	if (IS_EWW(stub_cwk_chan.mbox))
		wetuwn PTW_EWW(stub_cwk_chan.mbox);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;
	fweq_weg = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!fweq_weg)
		wetuwn -ENOMEM;

	fweq_weg += HI3660_STUB_CWOCK_DATA;

	fow (i = 0; i < HI3660_CWK_STUB_NUM; i++) {
		wet = devm_cwk_hw_wegistew(&pdev->dev, &hi3660_stub_cwks[i].hw);
		if (wet)
			wetuwn wet;
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(&pdev->dev, hi3660_stub_cwk_hw_get,
					   hi3660_stub_cwks);
}

static const stwuct of_device_id hi3660_stub_cwk_of_match[] = {
	{ .compatibwe = "hisiwicon,hi3660-stub-cwk", },
	{}
};

static stwuct pwatfowm_dwivew hi3660_stub_cwk_dwivew = {
	.pwobe	= hi3660_stub_cwk_pwobe,
	.dwivew = {
		.name = "hi3660-stub-cwk",
		.of_match_tabwe = hi3660_stub_cwk_of_match,
	},
};

static int __init hi3660_stub_cwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&hi3660_stub_cwk_dwivew);
}
subsys_initcaww(hi3660_stub_cwk_init);
