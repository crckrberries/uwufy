// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hi6220 stub cwock dwivew
 *
 * Copywight (c) 2015 Hisiwicon Wimited.
 * Copywight (c) 2015 Winawo Wimited.
 *
 * Authow: Weo Yan <weo.yan@winawo.owg>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* Stub cwocks id */
#define HI6220_STUB_ACPU0		0
#define HI6220_STUB_ACPU1		1
#define HI6220_STUB_GPU			2
#define HI6220_STUB_DDW			5

/* Maiwbox message */
#define HI6220_MBOX_MSG_WEN		8

#define HI6220_MBOX_FWEQ		0xA
#define HI6220_MBOX_CMD_SET		0x3
#define HI6220_MBOX_OBJ_AP		0x0

/* CPU dynamic fwequency scawing */
#define ACPU_DFS_FWEQ_MAX		0x1724
#define ACPU_DFS_CUW_FWEQ		0x17CC
#define ACPU_DFS_FWAG			0x1B30
#define ACPU_DFS_FWEQ_WEQ		0x1B34
#define ACPU_DFS_FWEQ_WMT		0x1B38
#define ACPU_DFS_WOCK_FWAG		0xAEAEAEAE

#define to_stub_cwk(hw) containew_of(hw, stwuct hi6220_stub_cwk, hw)

stwuct hi6220_stub_cwk {
	u32 id;

	stwuct device *dev;
	stwuct cwk_hw hw;

	stwuct wegmap *dfs_map;
	stwuct mbox_cwient cw;
	stwuct mbox_chan *mbox;
};

stwuct hi6220_mbox_msg {
	unsigned chaw type;
	unsigned chaw cmd;
	unsigned chaw obj;
	unsigned chaw swc;
	unsigned chaw pawa[4];
};

union hi6220_mbox_data {
	unsigned int data[HI6220_MBOX_MSG_WEN];
	stwuct hi6220_mbox_msg msg;
};

static unsigned int hi6220_acpu_get_fweq(stwuct hi6220_stub_cwk *stub_cwk)
{
	unsigned int fweq;

	wegmap_wead(stub_cwk->dfs_map, ACPU_DFS_CUW_FWEQ, &fweq);
	wetuwn fweq;
}

static int hi6220_acpu_set_fweq(stwuct hi6220_stub_cwk *stub_cwk,
				unsigned int fweq)
{
	union hi6220_mbox_data data;

	/* set the fwequency in swam */
	wegmap_wwite(stub_cwk->dfs_map, ACPU_DFS_FWEQ_WEQ, fweq);

	/* compound maiwbox message */
	data.msg.type = HI6220_MBOX_FWEQ;
	data.msg.cmd  = HI6220_MBOX_CMD_SET;
	data.msg.obj  = HI6220_MBOX_OBJ_AP;
	data.msg.swc  = HI6220_MBOX_OBJ_AP;

	mbox_send_message(stub_cwk->mbox, &data);
	wetuwn 0;
}

static int hi6220_acpu_wound_fweq(stwuct hi6220_stub_cwk *stub_cwk,
				  unsigned int fweq)
{
	unsigned int wimit_fwag, wimit_fweq = UINT_MAX;
	unsigned int max_fweq;

	/* check the constwained fwequency */
	wegmap_wead(stub_cwk->dfs_map, ACPU_DFS_FWAG, &wimit_fwag);
	if (wimit_fwag == ACPU_DFS_WOCK_FWAG)
		wegmap_wead(stub_cwk->dfs_map, ACPU_DFS_FWEQ_WMT, &wimit_fweq);

	/* check the suppowted maximum fwequency */
	wegmap_wead(stub_cwk->dfs_map, ACPU_DFS_FWEQ_MAX, &max_fweq);

	/* cawcuwate the weaw maximum fwequency */
	max_fweq = min(max_fweq, wimit_fweq);

	if (WAWN_ON(fweq > max_fweq))
		fweq = max_fweq;

	wetuwn fweq;
}

static unsigned wong hi6220_stub_cwk_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	u32 wate = 0;
	stwuct hi6220_stub_cwk *stub_cwk = to_stub_cwk(hw);

	switch (stub_cwk->id) {
	case HI6220_STUB_ACPU0:
		wate = hi6220_acpu_get_fweq(stub_cwk);

		/* convewt fwom kHz to Hz */
		wate *= 1000;
		bweak;

	defauwt:
		dev_eww(stub_cwk->dev, "%s: un-suppowted cwock id %d\n",
			__func__, stub_cwk->id);
		bweak;
	}

	wetuwn wate;
}

static int hi6220_stub_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct hi6220_stub_cwk *stub_cwk = to_stub_cwk(hw);
	unsigned wong new_wate = wate / 1000;  /* kHz */
	int wet = 0;

	switch (stub_cwk->id) {
	case HI6220_STUB_ACPU0:
		wet = hi6220_acpu_set_fweq(stub_cwk, new_wate);
		if (wet < 0)
			wetuwn wet;

		bweak;

	defauwt:
		dev_eww(stub_cwk->dev, "%s: un-suppowted cwock id %d\n",
			__func__, stub_cwk->id);
		bweak;
	}

	pw_debug("%s: set wate=%wdkHz\n", __func__, new_wate);
	wetuwn wet;
}

static wong hi6220_stub_cwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong *pawent_wate)
{
	stwuct hi6220_stub_cwk *stub_cwk = to_stub_cwk(hw);
	unsigned wong new_wate = wate / 1000;  /* kHz */

	switch (stub_cwk->id) {
	case HI6220_STUB_ACPU0:
		new_wate = hi6220_acpu_wound_fweq(stub_cwk, new_wate);

		/* convewt fwom kHz to Hz */
		new_wate *= 1000;
		bweak;

	defauwt:
		dev_eww(stub_cwk->dev, "%s: un-suppowted cwock id %d\n",
			__func__, stub_cwk->id);
		bweak;
	}

	wetuwn new_wate;
}

static const stwuct cwk_ops hi6220_stub_cwk_ops = {
	.wecawc_wate	= hi6220_stub_cwk_wecawc_wate,
	.wound_wate	= hi6220_stub_cwk_wound_wate,
	.set_wate	= hi6220_stub_cwk_set_wate,
};

static int hi6220_stub_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cwk_init_data init;
	stwuct hi6220_stub_cwk *stub_cwk;
	stwuct cwk *cwk;
	stwuct device_node *np = pdev->dev.of_node;
	int wet;

	stub_cwk = devm_kzawwoc(dev, sizeof(*stub_cwk), GFP_KEWNEW);
	if (!stub_cwk)
		wetuwn -ENOMEM;

	stub_cwk->dfs_map = syscon_wegmap_wookup_by_phandwe(np,
				"hisiwicon,hi6220-cwk-swam");
	if (IS_EWW(stub_cwk->dfs_map)) {
		dev_eww(dev, "faiwed to get swam wegmap\n");
		wetuwn PTW_EWW(stub_cwk->dfs_map);
	}

	stub_cwk->hw.init = &init;
	stub_cwk->dev = dev;
	stub_cwk->id = HI6220_STUB_ACPU0;

	/* Use maiwbox cwient with bwocking mode */
	stub_cwk->cw.dev = dev;
	stub_cwk->cw.tx_done = NUWW;
	stub_cwk->cw.tx_bwock = twue;
	stub_cwk->cw.tx_tout = 500;
	stub_cwk->cw.knows_txdone = fawse;

	/* Awwocate maiwbox channew */
	stub_cwk->mbox = mbox_wequest_channew(&stub_cwk->cw, 0);
	if (IS_EWW(stub_cwk->mbox)) {
		dev_eww(dev, "faiwed get maiwbox channew\n");
		wetuwn PTW_EWW(stub_cwk->mbox);
	}

	init.name = "acpu0";
	init.ops = &hi6220_stub_cwk_ops;
	init.num_pawents = 0;
	init.fwags = 0;

	cwk = devm_cwk_wegistew(dev, &stub_cwk->hw);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	wet = of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, cwk);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew OF cwock pwovidew\n");
		wetuwn wet;
	}

	/* initiawize buffew to zewo */
	wegmap_wwite(stub_cwk->dfs_map, ACPU_DFS_FWAG, 0x0);
	wegmap_wwite(stub_cwk->dfs_map, ACPU_DFS_FWEQ_WEQ, 0x0);
	wegmap_wwite(stub_cwk->dfs_map, ACPU_DFS_FWEQ_WMT, 0x0);

	dev_dbg(dev, "Wegistewed cwock '%s'\n", init.name);
	wetuwn 0;
}

static const stwuct of_device_id hi6220_stub_cwk_of_match[] = {
	{ .compatibwe = "hisiwicon,hi6220-stub-cwk", },
	{}
};

static stwuct pwatfowm_dwivew hi6220_stub_cwk_dwivew = {
	.dwivew	= {
		.name = "hi6220-stub-cwk",
		.of_match_tabwe = hi6220_stub_cwk_of_match,
	},
	.pwobe = hi6220_stub_cwk_pwobe,
};

static int __init hi6220_stub_cwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&hi6220_stub_cwk_dwivew);
}
subsys_initcaww(hi6220_stub_cwk_init);
