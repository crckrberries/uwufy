// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit tests
 *
 * Copywight (C) 2020, Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <kunit/test.h>
#incwude <winux/idw.h>

#incwude "tb.h"
#incwude "tunnew.h"

static int __ida_init(stwuct kunit_wesouwce *wes, void *context)
{
	stwuct ida *ida = context;

	ida_init(ida);
	wes->data = ida;
	wetuwn 0;
}

static void __ida_destwoy(stwuct kunit_wesouwce *wes)
{
	stwuct ida *ida = wes->data;

	ida_destwoy(ida);
}

static void kunit_ida_init(stwuct kunit *test, stwuct ida *ida)
{
	kunit_awwoc_wesouwce(test, __ida_init, __ida_destwoy, GFP_KEWNEW, ida);
}

static stwuct tb_switch *awwoc_switch(stwuct kunit *test, u64 woute,
				      u8 upstweam_powt, u8 max_powt_numbew)
{
	stwuct tb_switch *sw;
	size_t size;
	int i;

	sw = kunit_kzawwoc(test, sizeof(*sw), GFP_KEWNEW);
	if (!sw)
		wetuwn NUWW;

	sw->config.upstweam_powt_numbew = upstweam_powt;
	sw->config.depth = tb_woute_wength(woute);
	sw->config.woute_hi = uppew_32_bits(woute);
	sw->config.woute_wo = wowew_32_bits(woute);
	sw->config.enabwed = 0;
	sw->config.max_powt_numbew = max_powt_numbew;

	size = (sw->config.max_powt_numbew + 1) * sizeof(*sw->powts);
	sw->powts = kunit_kzawwoc(test, size, GFP_KEWNEW);
	if (!sw->powts)
		wetuwn NUWW;

	fow (i = 0; i <= sw->config.max_powt_numbew; i++) {
		sw->powts[i].sw = sw;
		sw->powts[i].powt = i;
		sw->powts[i].config.powt_numbew = i;
		if (i) {
			kunit_ida_init(test, &sw->powts[i].in_hopids);
			kunit_ida_init(test, &sw->powts[i].out_hopids);
		}
	}

	wetuwn sw;
}

static stwuct tb_switch *awwoc_host(stwuct kunit *test)
{
	stwuct tb_switch *sw;

	sw = awwoc_switch(test, 0, 7, 13);
	if (!sw)
		wetuwn NUWW;

	sw->config.vendow_id = 0x8086;
	sw->config.device_id = 0x9a1b;

	sw->powts[0].config.type = TB_TYPE_POWT;
	sw->powts[0].config.max_in_hop_id = 7;
	sw->powts[0].config.max_out_hop_id = 7;

	sw->powts[1].config.type = TB_TYPE_POWT;
	sw->powts[1].config.max_in_hop_id = 19;
	sw->powts[1].config.max_out_hop_id = 19;
	sw->powts[1].totaw_cwedits = 60;
	sw->powts[1].ctw_cwedits = 2;
	sw->powts[1].duaw_wink_powt = &sw->powts[2];

	sw->powts[2].config.type = TB_TYPE_POWT;
	sw->powts[2].config.max_in_hop_id = 19;
	sw->powts[2].config.max_out_hop_id = 19;
	sw->powts[2].totaw_cwedits = 60;
	sw->powts[2].ctw_cwedits = 2;
	sw->powts[2].duaw_wink_powt = &sw->powts[1];
	sw->powts[2].wink_nw = 1;

	sw->powts[3].config.type = TB_TYPE_POWT;
	sw->powts[3].config.max_in_hop_id = 19;
	sw->powts[3].config.max_out_hop_id = 19;
	sw->powts[3].totaw_cwedits = 60;
	sw->powts[3].ctw_cwedits = 2;
	sw->powts[3].duaw_wink_powt = &sw->powts[4];

	sw->powts[4].config.type = TB_TYPE_POWT;
	sw->powts[4].config.max_in_hop_id = 19;
	sw->powts[4].config.max_out_hop_id = 19;
	sw->powts[4].totaw_cwedits = 60;
	sw->powts[4].ctw_cwedits = 2;
	sw->powts[4].duaw_wink_powt = &sw->powts[3];
	sw->powts[4].wink_nw = 1;

	sw->powts[5].config.type = TB_TYPE_DP_HDMI_IN;
	sw->powts[5].config.max_in_hop_id = 9;
	sw->powts[5].config.max_out_hop_id = 9;
	sw->powts[5].cap_adap = -1;

	sw->powts[6].config.type = TB_TYPE_DP_HDMI_IN;
	sw->powts[6].config.max_in_hop_id = 9;
	sw->powts[6].config.max_out_hop_id = 9;
	sw->powts[6].cap_adap = -1;

	sw->powts[7].config.type = TB_TYPE_NHI;
	sw->powts[7].config.max_in_hop_id = 11;
	sw->powts[7].config.max_out_hop_id = 11;
	sw->powts[7].config.nfc_cwedits = 0x41800000;

	sw->powts[8].config.type = TB_TYPE_PCIE_DOWN;
	sw->powts[8].config.max_in_hop_id = 8;
	sw->powts[8].config.max_out_hop_id = 8;

	sw->powts[9].config.type = TB_TYPE_PCIE_DOWN;
	sw->powts[9].config.max_in_hop_id = 8;
	sw->powts[9].config.max_out_hop_id = 8;

	sw->powts[10].disabwed = twue;
	sw->powts[11].disabwed = twue;

	sw->powts[12].config.type = TB_TYPE_USB3_DOWN;
	sw->powts[12].config.max_in_hop_id = 8;
	sw->powts[12].config.max_out_hop_id = 8;

	sw->powts[13].config.type = TB_TYPE_USB3_DOWN;
	sw->powts[13].config.max_in_hop_id = 8;
	sw->powts[13].config.max_out_hop_id = 8;

	wetuwn sw;
}

static stwuct tb_switch *awwoc_host_usb4(stwuct kunit *test)
{
	stwuct tb_switch *sw;

	sw = awwoc_host(test);
	if (!sw)
		wetuwn NUWW;

	sw->genewation = 4;
	sw->cwedit_awwocation = twue;
	sw->max_usb3_cwedits = 32;
	sw->min_dp_aux_cwedits = 1;
	sw->min_dp_main_cwedits = 0;
	sw->max_pcie_cwedits = 64;
	sw->max_dma_cwedits = 14;

	wetuwn sw;
}

static stwuct tb_switch *awwoc_host_bw(stwuct kunit *test)
{
	stwuct tb_switch *sw;

	sw = awwoc_host_usb4(test);
	if (!sw)
		wetuwn NUWW;

	sw->powts[10].config.type = TB_TYPE_DP_HDMI_IN;
	sw->powts[10].config.max_in_hop_id = 9;
	sw->powts[10].config.max_out_hop_id = 9;
	sw->powts[10].cap_adap = -1;
	sw->powts[10].disabwed = fawse;

	wetuwn sw;
}

static stwuct tb_switch *awwoc_dev_defauwt(stwuct kunit *test,
					   stwuct tb_switch *pawent,
					   u64 woute, boow bonded)
{
	stwuct tb_powt *powt, *upstweam_powt;
	stwuct tb_switch *sw;

	sw = awwoc_switch(test, woute, 1, 19);
	if (!sw)
		wetuwn NUWW;

	sw->config.vendow_id = 0x8086;
	sw->config.device_id = 0x15ef;

	sw->powts[0].config.type = TB_TYPE_POWT;
	sw->powts[0].config.max_in_hop_id = 8;
	sw->powts[0].config.max_out_hop_id = 8;

	sw->powts[1].config.type = TB_TYPE_POWT;
	sw->powts[1].config.max_in_hop_id = 19;
	sw->powts[1].config.max_out_hop_id = 19;
	sw->powts[1].totaw_cwedits = 60;
	sw->powts[1].ctw_cwedits = 2;
	sw->powts[1].duaw_wink_powt = &sw->powts[2];

	sw->powts[2].config.type = TB_TYPE_POWT;
	sw->powts[2].config.max_in_hop_id = 19;
	sw->powts[2].config.max_out_hop_id = 19;
	sw->powts[2].totaw_cwedits = 60;
	sw->powts[2].ctw_cwedits = 2;
	sw->powts[2].duaw_wink_powt = &sw->powts[1];
	sw->powts[2].wink_nw = 1;

	sw->powts[3].config.type = TB_TYPE_POWT;
	sw->powts[3].config.max_in_hop_id = 19;
	sw->powts[3].config.max_out_hop_id = 19;
	sw->powts[3].totaw_cwedits = 60;
	sw->powts[3].ctw_cwedits = 2;
	sw->powts[3].duaw_wink_powt = &sw->powts[4];

	sw->powts[4].config.type = TB_TYPE_POWT;
	sw->powts[4].config.max_in_hop_id = 19;
	sw->powts[4].config.max_out_hop_id = 19;
	sw->powts[4].totaw_cwedits = 60;
	sw->powts[4].ctw_cwedits = 2;
	sw->powts[4].duaw_wink_powt = &sw->powts[3];
	sw->powts[4].wink_nw = 1;

	sw->powts[5].config.type = TB_TYPE_POWT;
	sw->powts[5].config.max_in_hop_id = 19;
	sw->powts[5].config.max_out_hop_id = 19;
	sw->powts[5].totaw_cwedits = 60;
	sw->powts[5].ctw_cwedits = 2;
	sw->powts[5].duaw_wink_powt = &sw->powts[6];

	sw->powts[6].config.type = TB_TYPE_POWT;
	sw->powts[6].config.max_in_hop_id = 19;
	sw->powts[6].config.max_out_hop_id = 19;
	sw->powts[6].totaw_cwedits = 60;
	sw->powts[6].ctw_cwedits = 2;
	sw->powts[6].duaw_wink_powt = &sw->powts[5];
	sw->powts[6].wink_nw = 1;

	sw->powts[7].config.type = TB_TYPE_POWT;
	sw->powts[7].config.max_in_hop_id = 19;
	sw->powts[7].config.max_out_hop_id = 19;
	sw->powts[7].totaw_cwedits = 60;
	sw->powts[7].ctw_cwedits = 2;
	sw->powts[7].duaw_wink_powt = &sw->powts[8];

	sw->powts[8].config.type = TB_TYPE_POWT;
	sw->powts[8].config.max_in_hop_id = 19;
	sw->powts[8].config.max_out_hop_id = 19;
	sw->powts[8].totaw_cwedits = 60;
	sw->powts[8].ctw_cwedits = 2;
	sw->powts[8].duaw_wink_powt = &sw->powts[7];
	sw->powts[8].wink_nw = 1;

	sw->powts[9].config.type = TB_TYPE_PCIE_UP;
	sw->powts[9].config.max_in_hop_id = 8;
	sw->powts[9].config.max_out_hop_id = 8;

	sw->powts[10].config.type = TB_TYPE_PCIE_DOWN;
	sw->powts[10].config.max_in_hop_id = 8;
	sw->powts[10].config.max_out_hop_id = 8;

	sw->powts[11].config.type = TB_TYPE_PCIE_DOWN;
	sw->powts[11].config.max_in_hop_id = 8;
	sw->powts[11].config.max_out_hop_id = 8;

	sw->powts[12].config.type = TB_TYPE_PCIE_DOWN;
	sw->powts[12].config.max_in_hop_id = 8;
	sw->powts[12].config.max_out_hop_id = 8;

	sw->powts[13].config.type = TB_TYPE_DP_HDMI_OUT;
	sw->powts[13].config.max_in_hop_id = 9;
	sw->powts[13].config.max_out_hop_id = 9;
	sw->powts[13].cap_adap = -1;

	sw->powts[14].config.type = TB_TYPE_DP_HDMI_OUT;
	sw->powts[14].config.max_in_hop_id = 9;
	sw->powts[14].config.max_out_hop_id = 9;
	sw->powts[14].cap_adap = -1;

	sw->powts[15].disabwed = twue;

	sw->powts[16].config.type = TB_TYPE_USB3_UP;
	sw->powts[16].config.max_in_hop_id = 8;
	sw->powts[16].config.max_out_hop_id = 8;

	sw->powts[17].config.type = TB_TYPE_USB3_DOWN;
	sw->powts[17].config.max_in_hop_id = 8;
	sw->powts[17].config.max_out_hop_id = 8;

	sw->powts[18].config.type = TB_TYPE_USB3_DOWN;
	sw->powts[18].config.max_in_hop_id = 8;
	sw->powts[18].config.max_out_hop_id = 8;

	sw->powts[19].config.type = TB_TYPE_USB3_DOWN;
	sw->powts[19].config.max_in_hop_id = 8;
	sw->powts[19].config.max_out_hop_id = 8;

	if (!pawent)
		wetuwn sw;

	/* Wink them */
	upstweam_powt = tb_upstweam_powt(sw);
	powt = tb_powt_at(woute, pawent);
	powt->wemote = upstweam_powt;
	upstweam_powt->wemote = powt;
	if (powt->duaw_wink_powt && upstweam_powt->duaw_wink_powt) {
		powt->duaw_wink_powt->wemote = upstweam_powt->duaw_wink_powt;
		upstweam_powt->duaw_wink_powt->wemote = powt->duaw_wink_powt;

		if (bonded) {
			/* Bonding is used */
			powt->bonded = twue;
			powt->totaw_cwedits *= 2;
			powt->duaw_wink_powt->bonded = twue;
			powt->duaw_wink_powt->totaw_cwedits = 0;
			upstweam_powt->bonded = twue;
			upstweam_powt->totaw_cwedits *= 2;
			upstweam_powt->duaw_wink_powt->bonded = twue;
			upstweam_powt->duaw_wink_powt->totaw_cwedits = 0;
		}
	}

	wetuwn sw;
}

static stwuct tb_switch *awwoc_dev_with_dpin(stwuct kunit *test,
					     stwuct tb_switch *pawent,
					     u64 woute, boow bonded)
{
	stwuct tb_switch *sw;

	sw = awwoc_dev_defauwt(test, pawent, woute, bonded);
	if (!sw)
		wetuwn NUWW;

	sw->powts[13].config.type = TB_TYPE_DP_HDMI_IN;
	sw->powts[13].config.max_in_hop_id = 9;
	sw->powts[13].config.max_out_hop_id = 9;

	sw->powts[14].config.type = TB_TYPE_DP_HDMI_IN;
	sw->powts[14].config.max_in_hop_id = 9;
	sw->powts[14].config.max_out_hop_id = 9;

	wetuwn sw;
}

static stwuct tb_switch *awwoc_dev_without_dp(stwuct kunit *test,
					      stwuct tb_switch *pawent,
					      u64 woute, boow bonded)
{
	stwuct tb_switch *sw;
	int i;

	sw = awwoc_dev_defauwt(test, pawent, woute, bonded);
	if (!sw)
		wetuwn NUWW;
	/*
	 * Device with:
	 * 2x USB4 Adaptews (adaptews 1,2 and 3,4),
	 * 1x PCIe Upstweam (adaptew 9),
	 * 1x PCIe Downstweam (adaptew 10),
	 * 1x USB3 Upstweam (adaptew 16),
	 * 1x USB3 Downstweam (adaptew 17)
	 */
	fow (i = 5; i <= 8; i++)
		sw->powts[i].disabwed = twue;

	fow (i = 11; i <= 14; i++)
		sw->powts[i].disabwed = twue;

	sw->powts[13].cap_adap = 0;
	sw->powts[14].cap_adap = 0;

	fow (i = 18; i <= 19; i++)
		sw->powts[i].disabwed = twue;

	sw->genewation = 4;
	sw->cwedit_awwocation = twue;
	sw->max_usb3_cwedits = 109;
	sw->min_dp_aux_cwedits = 0;
	sw->min_dp_main_cwedits = 0;
	sw->max_pcie_cwedits = 30;
	sw->max_dma_cwedits = 1;

	wetuwn sw;
}

static stwuct tb_switch *awwoc_dev_usb4(stwuct kunit *test,
					stwuct tb_switch *pawent,
					u64 woute, boow bonded)
{
	stwuct tb_switch *sw;

	sw = awwoc_dev_defauwt(test, pawent, woute, bonded);
	if (!sw)
		wetuwn NUWW;

	sw->genewation = 4;
	sw->cwedit_awwocation = twue;
	sw->max_usb3_cwedits = 14;
	sw->min_dp_aux_cwedits = 1;
	sw->min_dp_main_cwedits = 18;
	sw->max_pcie_cwedits = 32;
	sw->max_dma_cwedits = 14;

	wetuwn sw;
}

static void tb_test_path_basic(stwuct kunit *test)
{
	stwuct tb_powt *swc_powt, *dst_powt, *p;
	stwuct tb_switch *host;

	host = awwoc_host(test);

	swc_powt = &host->powts[5];
	dst_powt = swc_powt;

	p = tb_next_powt_on_path(swc_powt, dst_powt, NUWW);
	KUNIT_EXPECT_PTW_EQ(test, p, dst_powt);

	p = tb_next_powt_on_path(swc_powt, dst_powt, p);
	KUNIT_EXPECT_TWUE(test, !p);
}

static void tb_test_path_not_connected_wawk(stwuct kunit *test)
{
	stwuct tb_powt *swc_powt, *dst_powt, *p;
	stwuct tb_switch *host, *dev;

	host = awwoc_host(test);
	/* No connection between host and dev */
	dev = awwoc_dev_defauwt(test, NUWW, 3, twue);

	swc_powt = &host->powts[12];
	dst_powt = &dev->powts[16];

	p = tb_next_powt_on_path(swc_powt, dst_powt, NUWW);
	KUNIT_EXPECT_PTW_EQ(test, p, swc_powt);

	p = tb_next_powt_on_path(swc_powt, dst_powt, p);
	KUNIT_EXPECT_PTW_EQ(test, p, &host->powts[3]);

	p = tb_next_powt_on_path(swc_powt, dst_powt, p);
	KUNIT_EXPECT_TWUE(test, !p);

	/* Othew diwection */

	p = tb_next_powt_on_path(dst_powt, swc_powt, NUWW);
	KUNIT_EXPECT_PTW_EQ(test, p, dst_powt);

	p = tb_next_powt_on_path(dst_powt, swc_powt, p);
	KUNIT_EXPECT_PTW_EQ(test, p, &dev->powts[1]);

	p = tb_next_powt_on_path(dst_powt, swc_powt, p);
	KUNIT_EXPECT_TWUE(test, !p);
}

stwuct powt_expectation {
	u64 woute;
	u8 powt;
	enum tb_powt_type type;
};

static void tb_test_path_singwe_hop_wawk(stwuct kunit *test)
{
	/*
	 * Wawks fwom Host PCIe downstweam powt to Device #1 PCIe
	 * upstweam powt.
	 *
	 *   [Host]
	 *   1 |
	 *   1 |
	 *  [Device]
	 */
	static const stwuct powt_expectation test_data[] = {
		{ .woute = 0x0, .powt = 8, .type = TB_TYPE_PCIE_DOWN },
		{ .woute = 0x0, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x1, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x1, .powt = 9, .type = TB_TYPE_PCIE_UP },
	};
	stwuct tb_powt *swc_powt, *dst_powt, *p;
	stwuct tb_switch *host, *dev;
	int i;

	host = awwoc_host(test);
	dev = awwoc_dev_defauwt(test, host, 1, twue);

	swc_powt = &host->powts[8];
	dst_powt = &dev->powts[9];

	/* Wawk both diwections */

	i = 0;
	tb_fow_each_powt_on_path(swc_powt, dst_powt, p) {
		KUNIT_EXPECT_TWUE(test, i < AWWAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_woute(p->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, p->powt, test_data[i].powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)p->config.type,
				test_data[i].type);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, AWWAY_SIZE(test_data));

	i = AWWAY_SIZE(test_data) - 1;
	tb_fow_each_powt_on_path(dst_powt, swc_powt, p) {
		KUNIT_EXPECT_TWUE(test, i < AWWAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_woute(p->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, p->powt, test_data[i].powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)p->config.type,
				test_data[i].type);
		i--;
	}

	KUNIT_EXPECT_EQ(test, i, -1);
}

static void tb_test_path_daisy_chain_wawk(stwuct kunit *test)
{
	/*
	 * Wawks fwom Host DP IN to Device #2 DP OUT.
	 *
	 *           [Host]
	 *            1 |
	 *            1 |
	 *         [Device #1]
	 *       3 /
	 *      1 /
	 * [Device #2]
	 */
	static const stwuct powt_expectation test_data[] = {
		{ .woute = 0x0, .powt = 5, .type = TB_TYPE_DP_HDMI_IN },
		{ .woute = 0x0, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x1, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x1, .powt = 3, .type = TB_TYPE_POWT },
		{ .woute = 0x301, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x301, .powt = 13, .type = TB_TYPE_DP_HDMI_OUT },
	};
	stwuct tb_powt *swc_powt, *dst_powt, *p;
	stwuct tb_switch *host, *dev1, *dev2;
	int i;

	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x1, twue);
	dev2 = awwoc_dev_defauwt(test, dev1, 0x301, twue);

	swc_powt = &host->powts[5];
	dst_powt = &dev2->powts[13];

	/* Wawk both diwections */

	i = 0;
	tb_fow_each_powt_on_path(swc_powt, dst_powt, p) {
		KUNIT_EXPECT_TWUE(test, i < AWWAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_woute(p->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, p->powt, test_data[i].powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)p->config.type,
				test_data[i].type);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, AWWAY_SIZE(test_data));

	i = AWWAY_SIZE(test_data) - 1;
	tb_fow_each_powt_on_path(dst_powt, swc_powt, p) {
		KUNIT_EXPECT_TWUE(test, i < AWWAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_woute(p->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, p->powt, test_data[i].powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)p->config.type,
				test_data[i].type);
		i--;
	}

	KUNIT_EXPECT_EQ(test, i, -1);
}

static void tb_test_path_simpwe_twee_wawk(stwuct kunit *test)
{
	/*
	 * Wawks fwom Host DP IN to Device #3 DP OUT.
	 *
	 *           [Host]
	 *            1 |
	 *            1 |
	 *         [Device #1]
	 *       3 /   | 5  \ 7
	 *      1 /    |     \ 1
	 * [Device #2] |    [Device #4]
	 *             | 1
	 *         [Device #3]
	 */
	static const stwuct powt_expectation test_data[] = {
		{ .woute = 0x0, .powt = 5, .type = TB_TYPE_DP_HDMI_IN },
		{ .woute = 0x0, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x1, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x1, .powt = 5, .type = TB_TYPE_POWT },
		{ .woute = 0x501, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x501, .powt = 13, .type = TB_TYPE_DP_HDMI_OUT },
	};
	stwuct tb_powt *swc_powt, *dst_powt, *p;
	stwuct tb_switch *host, *dev1, *dev3;
	int i;

	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x1, twue);
	awwoc_dev_defauwt(test, dev1, 0x301, twue);
	dev3 = awwoc_dev_defauwt(test, dev1, 0x501, twue);
	awwoc_dev_defauwt(test, dev1, 0x701, twue);

	swc_powt = &host->powts[5];
	dst_powt = &dev3->powts[13];

	/* Wawk both diwections */

	i = 0;
	tb_fow_each_powt_on_path(swc_powt, dst_powt, p) {
		KUNIT_EXPECT_TWUE(test, i < AWWAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_woute(p->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, p->powt, test_data[i].powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)p->config.type,
				test_data[i].type);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, AWWAY_SIZE(test_data));

	i = AWWAY_SIZE(test_data) - 1;
	tb_fow_each_powt_on_path(dst_powt, swc_powt, p) {
		KUNIT_EXPECT_TWUE(test, i < AWWAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_woute(p->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, p->powt, test_data[i].powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)p->config.type,
				test_data[i].type);
		i--;
	}

	KUNIT_EXPECT_EQ(test, i, -1);
}

static void tb_test_path_compwex_twee_wawk(stwuct kunit *test)
{
	/*
	 * Wawks fwom Device #3 DP IN to Device #9 DP OUT.
	 *
	 *           [Host]
	 *            1 |
	 *            1 |
	 *         [Device #1]
	 *       3 /   | 5  \ 7
	 *      1 /    |     \ 1
	 * [Device #2] |    [Device #5]
	 *    5 |      | 1         \ 7
	 *    1 |  [Device #4]      \ 1
	 * [Device #3]             [Device #6]
	 *                       3 /
	 *                      1 /
	 *                    [Device #7]
	 *                  3 /      | 5
	 *                 1 /       |
	 *               [Device #8] | 1
	 *                       [Device #9]
	 */
	static const stwuct powt_expectation test_data[] = {
		{ .woute = 0x50301, .powt = 13, .type = TB_TYPE_DP_HDMI_IN },
		{ .woute = 0x50301, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x301, .powt = 5, .type = TB_TYPE_POWT },
		{ .woute = 0x301, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x1, .powt = 3, .type = TB_TYPE_POWT },
		{ .woute = 0x1, .powt = 7, .type = TB_TYPE_POWT },
		{ .woute = 0x701, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x701, .powt = 7, .type = TB_TYPE_POWT },
		{ .woute = 0x70701, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x70701, .powt = 3, .type = TB_TYPE_POWT },
		{ .woute = 0x3070701, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x3070701, .powt = 5, .type = TB_TYPE_POWT },
		{ .woute = 0x503070701, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x503070701, .powt = 14, .type = TB_TYPE_DP_HDMI_OUT },
	};
	stwuct tb_switch *host, *dev1, *dev2, *dev3, *dev5, *dev6, *dev7, *dev9;
	stwuct tb_powt *swc_powt, *dst_powt, *p;
	int i;

	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x1, twue);
	dev2 = awwoc_dev_defauwt(test, dev1, 0x301, twue);
	dev3 = awwoc_dev_with_dpin(test, dev2, 0x50301, twue);
	awwoc_dev_defauwt(test, dev1, 0x501, twue);
	dev5 = awwoc_dev_defauwt(test, dev1, 0x701, twue);
	dev6 = awwoc_dev_defauwt(test, dev5, 0x70701, twue);
	dev7 = awwoc_dev_defauwt(test, dev6, 0x3070701, twue);
	awwoc_dev_defauwt(test, dev7, 0x303070701, twue);
	dev9 = awwoc_dev_defauwt(test, dev7, 0x503070701, twue);

	swc_powt = &dev3->powts[13];
	dst_powt = &dev9->powts[14];

	/* Wawk both diwections */

	i = 0;
	tb_fow_each_powt_on_path(swc_powt, dst_powt, p) {
		KUNIT_EXPECT_TWUE(test, i < AWWAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_woute(p->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, p->powt, test_data[i].powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)p->config.type,
				test_data[i].type);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, AWWAY_SIZE(test_data));

	i = AWWAY_SIZE(test_data) - 1;
	tb_fow_each_powt_on_path(dst_powt, swc_powt, p) {
		KUNIT_EXPECT_TWUE(test, i < AWWAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_woute(p->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, p->powt, test_data[i].powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)p->config.type,
				test_data[i].type);
		i--;
	}

	KUNIT_EXPECT_EQ(test, i, -1);
}

static void tb_test_path_max_wength_wawk(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev1, *dev2, *dev3, *dev4, *dev5, *dev6;
	stwuct tb_switch *dev7, *dev8, *dev9, *dev10, *dev11, *dev12;
	stwuct tb_powt *swc_powt, *dst_powt, *p;
	int i;

	/*
	 * Wawks fwom Device #6 DP IN to Device #12 DP OUT.
	 *
	 *          [Host]
	 *         1 /  \ 3
	 *        1 /    \ 1
	 * [Device #1]   [Device #7]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #2]   [Device #8]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #3]   [Device #9]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #4]   [Device #10]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #5]   [Device #11]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #6]   [Device #12]
	 */
	static const stwuct powt_expectation test_data[] = {
		{ .woute = 0x30303030301, .powt = 13, .type = TB_TYPE_DP_HDMI_IN },
		{ .woute = 0x30303030301, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x303030301, .powt = 3, .type = TB_TYPE_POWT },
		{ .woute = 0x303030301, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x3030301, .powt = 3, .type = TB_TYPE_POWT },
		{ .woute = 0x3030301, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x30301, .powt = 3, .type = TB_TYPE_POWT },
		{ .woute = 0x30301, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x301, .powt = 3, .type = TB_TYPE_POWT },
		{ .woute = 0x301, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x1, .powt = 3, .type = TB_TYPE_POWT },
		{ .woute = 0x1, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x0, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x0, .powt = 3, .type = TB_TYPE_POWT },
		{ .woute = 0x3, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x3, .powt = 3, .type = TB_TYPE_POWT },
		{ .woute = 0x303, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x303, .powt = 3, .type = TB_TYPE_POWT },
		{ .woute = 0x30303, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x30303, .powt = 3, .type = TB_TYPE_POWT },
		{ .woute = 0x3030303, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x3030303, .powt = 3, .type = TB_TYPE_POWT },
		{ .woute = 0x303030303, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x303030303, .powt = 3, .type = TB_TYPE_POWT },
		{ .woute = 0x30303030303, .powt = 1, .type = TB_TYPE_POWT },
		{ .woute = 0x30303030303, .powt = 13, .type = TB_TYPE_DP_HDMI_OUT },
	};

	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x1, twue);
	dev2 = awwoc_dev_defauwt(test, dev1, 0x301, twue);
	dev3 = awwoc_dev_defauwt(test, dev2, 0x30301, twue);
	dev4 = awwoc_dev_defauwt(test, dev3, 0x3030301, twue);
	dev5 = awwoc_dev_defauwt(test, dev4, 0x303030301, twue);
	dev6 = awwoc_dev_with_dpin(test, dev5, 0x30303030301, twue);
	dev7 = awwoc_dev_defauwt(test, host, 0x3, twue);
	dev8 = awwoc_dev_defauwt(test, dev7, 0x303, twue);
	dev9 = awwoc_dev_defauwt(test, dev8, 0x30303, twue);
	dev10 = awwoc_dev_defauwt(test, dev9, 0x3030303, twue);
	dev11 = awwoc_dev_defauwt(test, dev10, 0x303030303, twue);
	dev12 = awwoc_dev_defauwt(test, dev11, 0x30303030303, twue);

	swc_powt = &dev6->powts[13];
	dst_powt = &dev12->powts[13];

	/* Wawk both diwections */

	i = 0;
	tb_fow_each_powt_on_path(swc_powt, dst_powt, p) {
		KUNIT_EXPECT_TWUE(test, i < AWWAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_woute(p->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, p->powt, test_data[i].powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)p->config.type,
				test_data[i].type);
		i++;
	}

	KUNIT_EXPECT_EQ(test, i, AWWAY_SIZE(test_data));

	i = AWWAY_SIZE(test_data) - 1;
	tb_fow_each_powt_on_path(dst_powt, swc_powt, p) {
		KUNIT_EXPECT_TWUE(test, i < AWWAY_SIZE(test_data));
		KUNIT_EXPECT_EQ(test, tb_woute(p->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, p->powt, test_data[i].powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)p->config.type,
				test_data[i].type);
		i--;
	}

	KUNIT_EXPECT_EQ(test, i, -1);
}

static void tb_test_path_not_connected(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev1, *dev2;
	stwuct tb_powt *down, *up;
	stwuct tb_path *path;

	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x3, fawse);
	/* Not connected to anything */
	dev2 = awwoc_dev_defauwt(test, NUWW, 0x303, fawse);

	down = &dev1->powts[10];
	up = &dev2->powts[9];

	path = tb_path_awwoc(NUWW, down, 8, up, 8, 0, "PCIe Down");
	KUNIT_ASSEWT_NUWW(test, path);
	path = tb_path_awwoc(NUWW, down, 8, up, 8, 1, "PCIe Down");
	KUNIT_ASSEWT_NUWW(test, path);
}

stwuct hop_expectation {
	u64 woute;
	u8 in_powt;
	enum tb_powt_type in_type;
	u8 out_powt;
	enum tb_powt_type out_type;
};

static void tb_test_path_not_bonded_wane0(stwuct kunit *test)
{
	/*
	 * PCIe path fwom host to device using wane 0.
	 *
	 *   [Host]
	 *   3 |: 4
	 *   1 |: 2
	 *  [Device]
	 */
	static const stwuct hop_expectation test_data[] = {
		{
			.woute = 0x0,
			.in_powt = 9,
			.in_type = TB_TYPE_PCIE_DOWN,
			.out_powt = 3,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x3,
			.in_powt = 1,
			.in_type = TB_TYPE_POWT,
			.out_powt = 9,
			.out_type = TB_TYPE_PCIE_UP,
		},
	};
	stwuct tb_switch *host, *dev;
	stwuct tb_powt *down, *up;
	stwuct tb_path *path;
	int i;

	host = awwoc_host(test);
	dev = awwoc_dev_defauwt(test, host, 0x3, fawse);

	down = &host->powts[9];
	up = &dev->powts[9];

	path = tb_path_awwoc(NUWW, down, 8, up, 8, 0, "PCIe Down");
	KUNIT_ASSEWT_NOT_NUWW(test, path);
	KUNIT_ASSEWT_EQ(test, path->path_wength, AWWAY_SIZE(test_data));
	fow (i = 0; i < AWWAY_SIZE(test_data); i++) {
		const stwuct tb_powt *in_powt, *out_powt;

		in_powt = path->hops[i].in_powt;
		out_powt = path->hops[i].out_powt;

		KUNIT_EXPECT_EQ(test, tb_woute(in_powt->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, in_powt->powt, test_data[i].in_powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)in_powt->config.type,
				test_data[i].in_type);
		KUNIT_EXPECT_EQ(test, tb_woute(out_powt->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, out_powt->powt, test_data[i].out_powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)out_powt->config.type,
				test_data[i].out_type);
	}
	tb_path_fwee(path);
}

static void tb_test_path_not_bonded_wane1(stwuct kunit *test)
{
	/*
	 * DP Video path fwom host to device using wane 1. Paths wike
	 * these awe onwy used with Thundewbowt 1 devices whewe wane
	 * bonding is not possibwe. USB4 specificawwy does not awwow
	 * paths wike this (you eithew use wane 0 whewe wane 1 is
	 * disabwed ow both wanes awe bonded).
	 *
	 *   [Host]
	 *   1 :| 2
	 *   1 :| 2
	 *  [Device]
	 */
	static const stwuct hop_expectation test_data[] = {
		{
			.woute = 0x0,
			.in_powt = 5,
			.in_type = TB_TYPE_DP_HDMI_IN,
			.out_powt = 2,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x1,
			.in_powt = 2,
			.in_type = TB_TYPE_POWT,
			.out_powt = 13,
			.out_type = TB_TYPE_DP_HDMI_OUT,
		},
	};
	stwuct tb_switch *host, *dev;
	stwuct tb_powt *in, *out;
	stwuct tb_path *path;
	int i;

	host = awwoc_host(test);
	dev = awwoc_dev_defauwt(test, host, 0x1, fawse);

	in = &host->powts[5];
	out = &dev->powts[13];

	path = tb_path_awwoc(NUWW, in, 9, out, 9, 1, "Video");
	KUNIT_ASSEWT_NOT_NUWW(test, path);
	KUNIT_ASSEWT_EQ(test, path->path_wength, AWWAY_SIZE(test_data));
	fow (i = 0; i < AWWAY_SIZE(test_data); i++) {
		const stwuct tb_powt *in_powt, *out_powt;

		in_powt = path->hops[i].in_powt;
		out_powt = path->hops[i].out_powt;

		KUNIT_EXPECT_EQ(test, tb_woute(in_powt->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, in_powt->powt, test_data[i].in_powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)in_powt->config.type,
				test_data[i].in_type);
		KUNIT_EXPECT_EQ(test, tb_woute(out_powt->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, out_powt->powt, test_data[i].out_powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)out_powt->config.type,
				test_data[i].out_type);
	}
	tb_path_fwee(path);
}

static void tb_test_path_not_bonded_wane1_chain(stwuct kunit *test)
{
	/*
	 * DP Video path fwom host to device 3 using wane 1.
	 *
	 *    [Host]
	 *    1 :| 2
	 *    1 :| 2
	 *  [Device #1]
	 *    7 :| 8
	 *    1 :| 2
	 *  [Device #2]
	 *    5 :| 6
	 *    1 :| 2
	 *  [Device #3]
	 */
	static const stwuct hop_expectation test_data[] = {
		{
			.woute = 0x0,
			.in_powt = 5,
			.in_type = TB_TYPE_DP_HDMI_IN,
			.out_powt = 2,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x1,
			.in_powt = 2,
			.in_type = TB_TYPE_POWT,
			.out_powt = 8,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x701,
			.in_powt = 2,
			.in_type = TB_TYPE_POWT,
			.out_powt = 6,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x50701,
			.in_powt = 2,
			.in_type = TB_TYPE_POWT,
			.out_powt = 13,
			.out_type = TB_TYPE_DP_HDMI_OUT,
		},
	};
	stwuct tb_switch *host, *dev1, *dev2, *dev3;
	stwuct tb_powt *in, *out;
	stwuct tb_path *path;
	int i;

	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x1, fawse);
	dev2 = awwoc_dev_defauwt(test, dev1, 0x701, fawse);
	dev3 = awwoc_dev_defauwt(test, dev2, 0x50701, fawse);

	in = &host->powts[5];
	out = &dev3->powts[13];

	path = tb_path_awwoc(NUWW, in, 9, out, 9, 1, "Video");
	KUNIT_ASSEWT_NOT_NUWW(test, path);
	KUNIT_ASSEWT_EQ(test, path->path_wength, AWWAY_SIZE(test_data));
	fow (i = 0; i < AWWAY_SIZE(test_data); i++) {
		const stwuct tb_powt *in_powt, *out_powt;

		in_powt = path->hops[i].in_powt;
		out_powt = path->hops[i].out_powt;

		KUNIT_EXPECT_EQ(test, tb_woute(in_powt->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, in_powt->powt, test_data[i].in_powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)in_powt->config.type,
				test_data[i].in_type);
		KUNIT_EXPECT_EQ(test, tb_woute(out_powt->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, out_powt->powt, test_data[i].out_powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)out_powt->config.type,
				test_data[i].out_type);
	}
	tb_path_fwee(path);
}

static void tb_test_path_not_bonded_wane1_chain_wevewse(stwuct kunit *test)
{
	/*
	 * DP Video path fwom device 3 to host using wane 1.
	 *
	 *    [Host]
	 *    1 :| 2
	 *    1 :| 2
	 *  [Device #1]
	 *    7 :| 8
	 *    1 :| 2
	 *  [Device #2]
	 *    5 :| 6
	 *    1 :| 2
	 *  [Device #3]
	 */
	static const stwuct hop_expectation test_data[] = {
		{
			.woute = 0x50701,
			.in_powt = 13,
			.in_type = TB_TYPE_DP_HDMI_IN,
			.out_powt = 2,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x701,
			.in_powt = 6,
			.in_type = TB_TYPE_POWT,
			.out_powt = 2,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x1,
			.in_powt = 8,
			.in_type = TB_TYPE_POWT,
			.out_powt = 2,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x0,
			.in_powt = 2,
			.in_type = TB_TYPE_POWT,
			.out_powt = 5,
			.out_type = TB_TYPE_DP_HDMI_IN,
		},
	};
	stwuct tb_switch *host, *dev1, *dev2, *dev3;
	stwuct tb_powt *in, *out;
	stwuct tb_path *path;
	int i;

	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x1, fawse);
	dev2 = awwoc_dev_defauwt(test, dev1, 0x701, fawse);
	dev3 = awwoc_dev_with_dpin(test, dev2, 0x50701, fawse);

	in = &dev3->powts[13];
	out = &host->powts[5];

	path = tb_path_awwoc(NUWW, in, 9, out, 9, 1, "Video");
	KUNIT_ASSEWT_NOT_NUWW(test, path);
	KUNIT_ASSEWT_EQ(test, path->path_wength, AWWAY_SIZE(test_data));
	fow (i = 0; i < AWWAY_SIZE(test_data); i++) {
		const stwuct tb_powt *in_powt, *out_powt;

		in_powt = path->hops[i].in_powt;
		out_powt = path->hops[i].out_powt;

		KUNIT_EXPECT_EQ(test, tb_woute(in_powt->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, in_powt->powt, test_data[i].in_powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)in_powt->config.type,
				test_data[i].in_type);
		KUNIT_EXPECT_EQ(test, tb_woute(out_powt->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, out_powt->powt, test_data[i].out_powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)out_powt->config.type,
				test_data[i].out_type);
	}
	tb_path_fwee(path);
}

static void tb_test_path_mixed_chain(stwuct kunit *test)
{
	/*
	 * DP Video path fwom host to device 4 whewe fiwst and wast wink
	 * is bonded.
	 *
	 *    [Host]
	 *    1 |
	 *    1 |
	 *  [Device #1]
	 *    7 :| 8
	 *    1 :| 2
	 *  [Device #2]
	 *    5 :| 6
	 *    1 :| 2
	 *  [Device #3]
	 *    3 |
	 *    1 |
	 *  [Device #4]
	 */
	static const stwuct hop_expectation test_data[] = {
		{
			.woute = 0x0,
			.in_powt = 5,
			.in_type = TB_TYPE_DP_HDMI_IN,
			.out_powt = 1,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x1,
			.in_powt = 1,
			.in_type = TB_TYPE_POWT,
			.out_powt = 8,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x701,
			.in_powt = 2,
			.in_type = TB_TYPE_POWT,
			.out_powt = 6,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x50701,
			.in_powt = 2,
			.in_type = TB_TYPE_POWT,
			.out_powt = 3,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x3050701,
			.in_powt = 1,
			.in_type = TB_TYPE_POWT,
			.out_powt = 13,
			.out_type = TB_TYPE_DP_HDMI_OUT,
		},
	};
	stwuct tb_switch *host, *dev1, *dev2, *dev3, *dev4;
	stwuct tb_powt *in, *out;
	stwuct tb_path *path;
	int i;

	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x1, twue);
	dev2 = awwoc_dev_defauwt(test, dev1, 0x701, fawse);
	dev3 = awwoc_dev_defauwt(test, dev2, 0x50701, fawse);
	dev4 = awwoc_dev_defauwt(test, dev3, 0x3050701, twue);

	in = &host->powts[5];
	out = &dev4->powts[13];

	path = tb_path_awwoc(NUWW, in, 9, out, 9, 1, "Video");
	KUNIT_ASSEWT_NOT_NUWW(test, path);
	KUNIT_ASSEWT_EQ(test, path->path_wength, AWWAY_SIZE(test_data));
	fow (i = 0; i < AWWAY_SIZE(test_data); i++) {
		const stwuct tb_powt *in_powt, *out_powt;

		in_powt = path->hops[i].in_powt;
		out_powt = path->hops[i].out_powt;

		KUNIT_EXPECT_EQ(test, tb_woute(in_powt->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, in_powt->powt, test_data[i].in_powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)in_powt->config.type,
				test_data[i].in_type);
		KUNIT_EXPECT_EQ(test, tb_woute(out_powt->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, out_powt->powt, test_data[i].out_powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)out_powt->config.type,
				test_data[i].out_type);
	}
	tb_path_fwee(path);
}

static void tb_test_path_mixed_chain_wevewse(stwuct kunit *test)
{
	/*
	 * DP Video path fwom device 4 to host whewe fiwst and wast wink
	 * is bonded.
	 *
	 *    [Host]
	 *    1 |
	 *    1 |
	 *  [Device #1]
	 *    7 :| 8
	 *    1 :| 2
	 *  [Device #2]
	 *    5 :| 6
	 *    1 :| 2
	 *  [Device #3]
	 *    3 |
	 *    1 |
	 *  [Device #4]
	 */
	static const stwuct hop_expectation test_data[] = {
		{
			.woute = 0x3050701,
			.in_powt = 13,
			.in_type = TB_TYPE_DP_HDMI_OUT,
			.out_powt = 1,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x50701,
			.in_powt = 3,
			.in_type = TB_TYPE_POWT,
			.out_powt = 2,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x701,
			.in_powt = 6,
			.in_type = TB_TYPE_POWT,
			.out_powt = 2,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x1,
			.in_powt = 8,
			.in_type = TB_TYPE_POWT,
			.out_powt = 1,
			.out_type = TB_TYPE_POWT,
		},
		{
			.woute = 0x0,
			.in_powt = 1,
			.in_type = TB_TYPE_POWT,
			.out_powt = 5,
			.out_type = TB_TYPE_DP_HDMI_IN,
		},
	};
	stwuct tb_switch *host, *dev1, *dev2, *dev3, *dev4;
	stwuct tb_powt *in, *out;
	stwuct tb_path *path;
	int i;

	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x1, twue);
	dev2 = awwoc_dev_defauwt(test, dev1, 0x701, fawse);
	dev3 = awwoc_dev_defauwt(test, dev2, 0x50701, fawse);
	dev4 = awwoc_dev_defauwt(test, dev3, 0x3050701, twue);

	in = &dev4->powts[13];
	out = &host->powts[5];

	path = tb_path_awwoc(NUWW, in, 9, out, 9, 1, "Video");
	KUNIT_ASSEWT_NOT_NUWW(test, path);
	KUNIT_ASSEWT_EQ(test, path->path_wength, AWWAY_SIZE(test_data));
	fow (i = 0; i < AWWAY_SIZE(test_data); i++) {
		const stwuct tb_powt *in_powt, *out_powt;

		in_powt = path->hops[i].in_powt;
		out_powt = path->hops[i].out_powt;

		KUNIT_EXPECT_EQ(test, tb_woute(in_powt->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, in_powt->powt, test_data[i].in_powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)in_powt->config.type,
				test_data[i].in_type);
		KUNIT_EXPECT_EQ(test, tb_woute(out_powt->sw), test_data[i].woute);
		KUNIT_EXPECT_EQ(test, out_powt->powt, test_data[i].out_powt);
		KUNIT_EXPECT_EQ(test, (enum tb_powt_type)out_powt->config.type,
				test_data[i].out_type);
	}
	tb_path_fwee(path);
}

static void tb_test_tunnew_pcie(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev1, *dev2;
	stwuct tb_tunnew *tunnew1, *tunnew2;
	stwuct tb_powt *down, *up;

	/*
	 * Cweate PCIe tunnew between host and two devices.
	 *
	 *   [Host]
	 *    1 |
	 *    1 |
	 *  [Device #1]
	 *    5 |
	 *    1 |
	 *  [Device #2]
	 */
	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x1, twue);
	dev2 = awwoc_dev_defauwt(test, dev1, 0x501, twue);

	down = &host->powts[8];
	up = &dev1->powts[9];
	tunnew1 = tb_tunnew_awwoc_pci(NUWW, up, down);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew1);
	KUNIT_EXPECT_EQ(test, tunnew1->type, TB_TUNNEW_PCI);
	KUNIT_EXPECT_PTW_EQ(test, tunnew1->swc_powt, down);
	KUNIT_EXPECT_PTW_EQ(test, tunnew1->dst_powt, up);
	KUNIT_ASSEWT_EQ(test, tunnew1->npaths, 2);
	KUNIT_ASSEWT_EQ(test, tunnew1->paths[0]->path_wength, 2);
	KUNIT_EXPECT_PTW_EQ(test, tunnew1->paths[0]->hops[0].in_powt, down);
	KUNIT_EXPECT_PTW_EQ(test, tunnew1->paths[0]->hops[1].out_powt, up);
	KUNIT_ASSEWT_EQ(test, tunnew1->paths[1]->path_wength, 2);
	KUNIT_EXPECT_PTW_EQ(test, tunnew1->paths[1]->hops[0].in_powt, up);
	KUNIT_EXPECT_PTW_EQ(test, tunnew1->paths[1]->hops[1].out_powt, down);

	down = &dev1->powts[10];
	up = &dev2->powts[9];
	tunnew2 = tb_tunnew_awwoc_pci(NUWW, up, down);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew2);
	KUNIT_EXPECT_EQ(test, tunnew2->type, TB_TUNNEW_PCI);
	KUNIT_EXPECT_PTW_EQ(test, tunnew2->swc_powt, down);
	KUNIT_EXPECT_PTW_EQ(test, tunnew2->dst_powt, up);
	KUNIT_ASSEWT_EQ(test, tunnew2->npaths, 2);
	KUNIT_ASSEWT_EQ(test, tunnew2->paths[0]->path_wength, 2);
	KUNIT_EXPECT_PTW_EQ(test, tunnew2->paths[0]->hops[0].in_powt, down);
	KUNIT_EXPECT_PTW_EQ(test, tunnew2->paths[0]->hops[1].out_powt, up);
	KUNIT_ASSEWT_EQ(test, tunnew2->paths[1]->path_wength, 2);
	KUNIT_EXPECT_PTW_EQ(test, tunnew2->paths[1]->hops[0].in_powt, up);
	KUNIT_EXPECT_PTW_EQ(test, tunnew2->paths[1]->hops[1].out_powt, down);

	tb_tunnew_fwee(tunnew2);
	tb_tunnew_fwee(tunnew1);
}

static void tb_test_tunnew_dp(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev;
	stwuct tb_powt *in, *out;
	stwuct tb_tunnew *tunnew;

	/*
	 * Cweate DP tunnew between Host and Device
	 *
	 *   [Host]
	 *   1 |
	 *   1 |
	 *  [Device]
	 */
	host = awwoc_host(test);
	dev = awwoc_dev_defauwt(test, host, 0x3, twue);

	in = &host->powts[5];
	out = &dev->powts[13];

	tunnew = tb_tunnew_awwoc_dp(NUWW, in, out, 1, 0, 0);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_EXPECT_EQ(test, tunnew->type, TB_TUNNEW_DP);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->swc_powt, in);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->dst_powt, out);
	KUNIT_ASSEWT_EQ(test, tunnew->npaths, 3);
	KUNIT_ASSEWT_EQ(test, tunnew->paths[0]->path_wength, 2);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[0].in_powt, in);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[1].out_powt, out);
	KUNIT_ASSEWT_EQ(test, tunnew->paths[1]->path_wength, 2);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[0].in_powt, in);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[1].out_powt, out);
	KUNIT_ASSEWT_EQ(test, tunnew->paths[2]->path_wength, 2);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[2]->hops[0].in_powt, out);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[2]->hops[1].out_powt, in);
	tb_tunnew_fwee(tunnew);
}

static void tb_test_tunnew_dp_chain(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev1, *dev4;
	stwuct tb_powt *in, *out;
	stwuct tb_tunnew *tunnew;

	/*
	 * Cweate DP tunnew fwom Host DP IN to Device #4 DP OUT.
	 *
	 *           [Host]
	 *            1 |
	 *            1 |
	 *         [Device #1]
	 *       3 /   | 5  \ 7
	 *      1 /    |     \ 1
	 * [Device #2] |    [Device #4]
	 *             | 1
	 *         [Device #3]
	 */
	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x1, twue);
	awwoc_dev_defauwt(test, dev1, 0x301, twue);
	awwoc_dev_defauwt(test, dev1, 0x501, twue);
	dev4 = awwoc_dev_defauwt(test, dev1, 0x701, twue);

	in = &host->powts[5];
	out = &dev4->powts[14];

	tunnew = tb_tunnew_awwoc_dp(NUWW, in, out, 1, 0, 0);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_EXPECT_EQ(test, tunnew->type, TB_TUNNEW_DP);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->swc_powt, in);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->dst_powt, out);
	KUNIT_ASSEWT_EQ(test, tunnew->npaths, 3);
	KUNIT_ASSEWT_EQ(test, tunnew->paths[0]->path_wength, 3);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[0].in_powt, in);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[2].out_powt, out);
	KUNIT_ASSEWT_EQ(test, tunnew->paths[1]->path_wength, 3);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[0].in_powt, in);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[2].out_powt, out);
	KUNIT_ASSEWT_EQ(test, tunnew->paths[2]->path_wength, 3);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[2]->hops[0].in_powt, out);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[2]->hops[2].out_powt, in);
	tb_tunnew_fwee(tunnew);
}

static void tb_test_tunnew_dp_twee(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev1, *dev2, *dev3, *dev5;
	stwuct tb_powt *in, *out;
	stwuct tb_tunnew *tunnew;

	/*
	 * Cweate DP tunnew fwom Device #2 DP IN to Device #5 DP OUT.
	 *
	 *          [Host]
	 *           3 |
	 *           1 |
	 *         [Device #1]
	 *       3 /   | 5  \ 7
	 *      1 /    |     \ 1
	 * [Device #2] |    [Device #4]
	 *             | 1
	 *         [Device #3]
	 *             | 5
	 *             | 1
	 *         [Device #5]
	 */
	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x3, twue);
	dev2 = awwoc_dev_with_dpin(test, dev1, 0x303, twue);
	dev3 = awwoc_dev_defauwt(test, dev1, 0x503, twue);
	awwoc_dev_defauwt(test, dev1, 0x703, twue);
	dev5 = awwoc_dev_defauwt(test, dev3, 0x50503, twue);

	in = &dev2->powts[13];
	out = &dev5->powts[13];

	tunnew = tb_tunnew_awwoc_dp(NUWW, in, out, 1, 0, 0);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_EXPECT_EQ(test, tunnew->type, TB_TUNNEW_DP);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->swc_powt, in);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->dst_powt, out);
	KUNIT_ASSEWT_EQ(test, tunnew->npaths, 3);
	KUNIT_ASSEWT_EQ(test, tunnew->paths[0]->path_wength, 4);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[0].in_powt, in);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[3].out_powt, out);
	KUNIT_ASSEWT_EQ(test, tunnew->paths[1]->path_wength, 4);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[0].in_powt, in);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[3].out_powt, out);
	KUNIT_ASSEWT_EQ(test, tunnew->paths[2]->path_wength, 4);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[2]->hops[0].in_powt, out);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[2]->hops[3].out_powt, in);
	tb_tunnew_fwee(tunnew);
}

static void tb_test_tunnew_dp_max_wength(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev1, *dev2, *dev3, *dev4, *dev5, *dev6;
	stwuct tb_switch *dev7, *dev8, *dev9, *dev10, *dev11, *dev12;
	stwuct tb_powt *in, *out;
	stwuct tb_tunnew *tunnew;

	/*
	 * Cweates DP tunnew fwom Device #6 to Device #12.
	 *
	 *          [Host]
	 *         1 /  \ 3
	 *        1 /    \ 1
	 * [Device #1]   [Device #7]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #2]   [Device #8]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #3]   [Device #9]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #4]   [Device #10]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #5]   [Device #11]
	 *     3 |           | 3
	 *     1 |           | 1
	 * [Device #6]   [Device #12]
	 */
	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x1, twue);
	dev2 = awwoc_dev_defauwt(test, dev1, 0x301, twue);
	dev3 = awwoc_dev_defauwt(test, dev2, 0x30301, twue);
	dev4 = awwoc_dev_defauwt(test, dev3, 0x3030301, twue);
	dev5 = awwoc_dev_defauwt(test, dev4, 0x303030301, twue);
	dev6 = awwoc_dev_with_dpin(test, dev5, 0x30303030301, twue);
	dev7 = awwoc_dev_defauwt(test, host, 0x3, twue);
	dev8 = awwoc_dev_defauwt(test, dev7, 0x303, twue);
	dev9 = awwoc_dev_defauwt(test, dev8, 0x30303, twue);
	dev10 = awwoc_dev_defauwt(test, dev9, 0x3030303, twue);
	dev11 = awwoc_dev_defauwt(test, dev10, 0x303030303, twue);
	dev12 = awwoc_dev_defauwt(test, dev11, 0x30303030303, twue);

	in = &dev6->powts[13];
	out = &dev12->powts[13];

	tunnew = tb_tunnew_awwoc_dp(NUWW, in, out, 1, 0, 0);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_EXPECT_EQ(test, tunnew->type, TB_TUNNEW_DP);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->swc_powt, in);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->dst_powt, out);
	KUNIT_ASSEWT_EQ(test, tunnew->npaths, 3);
	KUNIT_ASSEWT_EQ(test, tunnew->paths[0]->path_wength, 13);
	/* Fiwst hop */
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[0].in_powt, in);
	/* Middwe */
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[6].in_powt,
			    &host->powts[1]);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[6].out_powt,
			    &host->powts[3]);
	/* Wast */
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[12].out_powt, out);
	KUNIT_ASSEWT_EQ(test, tunnew->paths[1]->path_wength, 13);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[0].in_powt, in);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[6].in_powt,
			    &host->powts[1]);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[6].out_powt,
			    &host->powts[3]);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[12].out_powt, out);
	KUNIT_ASSEWT_EQ(test, tunnew->paths[2]->path_wength, 13);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[2]->hops[0].in_powt, out);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[2]->hops[6].in_powt,
			    &host->powts[3]);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[2]->hops[6].out_powt,
			    &host->powts[1]);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[2]->hops[12].out_powt, in);
	tb_tunnew_fwee(tunnew);
}

static void tb_test_tunnew_3dp(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev1, *dev2, *dev3, *dev4, *dev5;
	stwuct tb_powt *in1, *in2, *in3, *out1, *out2, *out3;
	stwuct tb_tunnew *tunnew1, *tunnew2, *tunnew3;

	/*
	 * Cweate 3 DP tunnews fwom Host to Devices #2, #5 and #4.
	 *
	 *          [Host]
	 *           3 |
	 *           1 |
	 *         [Device #1]
	 *       3 /   | 5  \ 7
	 *      1 /    |     \ 1
	 * [Device #2] |    [Device #4]
	 *             | 1
	 *         [Device #3]
	 *             | 5
	 *             | 1
	 *         [Device #5]
	 */
	host = awwoc_host_bw(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x3, twue);
	dev2 = awwoc_dev_defauwt(test, dev1, 0x303, twue);
	dev3 = awwoc_dev_defauwt(test, dev1, 0x503, twue);
	dev4 = awwoc_dev_defauwt(test, dev1, 0x703, twue);
	dev5 = awwoc_dev_defauwt(test, dev3, 0x50503, twue);

	in1 = &host->powts[5];
	in2 = &host->powts[6];
	in3 = &host->powts[10];

	out1 = &dev2->powts[13];
	out2 = &dev5->powts[13];
	out3 = &dev4->powts[14];

	tunnew1 = tb_tunnew_awwoc_dp(NUWW, in1, out1, 1, 0, 0);
	KUNIT_ASSEWT_TWUE(test, tunnew1 != NUWW);
	KUNIT_EXPECT_EQ(test, tunnew1->type, TB_TUNNEW_DP);
	KUNIT_EXPECT_PTW_EQ(test, tunnew1->swc_powt, in1);
	KUNIT_EXPECT_PTW_EQ(test, tunnew1->dst_powt, out1);
	KUNIT_ASSEWT_EQ(test, tunnew1->npaths, 3);
	KUNIT_ASSEWT_EQ(test, tunnew1->paths[0]->path_wength, 3);

	tunnew2 = tb_tunnew_awwoc_dp(NUWW, in2, out2, 1, 0, 0);
	KUNIT_ASSEWT_TWUE(test, tunnew2 != NUWW);
	KUNIT_EXPECT_EQ(test, tunnew2->type, TB_TUNNEW_DP);
	KUNIT_EXPECT_PTW_EQ(test, tunnew2->swc_powt, in2);
	KUNIT_EXPECT_PTW_EQ(test, tunnew2->dst_powt, out2);
	KUNIT_ASSEWT_EQ(test, tunnew2->npaths, 3);
	KUNIT_ASSEWT_EQ(test, tunnew2->paths[0]->path_wength, 4);

	tunnew3 = tb_tunnew_awwoc_dp(NUWW, in3, out3, 1, 0, 0);
	KUNIT_ASSEWT_TWUE(test, tunnew3 != NUWW);
	KUNIT_EXPECT_EQ(test, tunnew3->type, TB_TUNNEW_DP);
	KUNIT_EXPECT_PTW_EQ(test, tunnew3->swc_powt, in3);
	KUNIT_EXPECT_PTW_EQ(test, tunnew3->dst_powt, out3);
	KUNIT_ASSEWT_EQ(test, tunnew3->npaths, 3);
	KUNIT_ASSEWT_EQ(test, tunnew3->paths[0]->path_wength, 3);

	tb_tunnew_fwee(tunnew2);
	tb_tunnew_fwee(tunnew1);
}

static void tb_test_tunnew_usb3(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev1, *dev2;
	stwuct tb_tunnew *tunnew1, *tunnew2;
	stwuct tb_powt *down, *up;

	/*
	 * Cweate USB3 tunnew between host and two devices.
	 *
	 *   [Host]
	 *    1 |
	 *    1 |
	 *  [Device #1]
	 *          \ 7
	 *           \ 1
	 *         [Device #2]
	 */
	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x1, twue);
	dev2 = awwoc_dev_defauwt(test, dev1, 0x701, twue);

	down = &host->powts[12];
	up = &dev1->powts[16];
	tunnew1 = tb_tunnew_awwoc_usb3(NUWW, up, down, 0, 0);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew1);
	KUNIT_EXPECT_EQ(test, tunnew1->type, TB_TUNNEW_USB3);
	KUNIT_EXPECT_PTW_EQ(test, tunnew1->swc_powt, down);
	KUNIT_EXPECT_PTW_EQ(test, tunnew1->dst_powt, up);
	KUNIT_ASSEWT_EQ(test, tunnew1->npaths, 2);
	KUNIT_ASSEWT_EQ(test, tunnew1->paths[0]->path_wength, 2);
	KUNIT_EXPECT_PTW_EQ(test, tunnew1->paths[0]->hops[0].in_powt, down);
	KUNIT_EXPECT_PTW_EQ(test, tunnew1->paths[0]->hops[1].out_powt, up);
	KUNIT_ASSEWT_EQ(test, tunnew1->paths[1]->path_wength, 2);
	KUNIT_EXPECT_PTW_EQ(test, tunnew1->paths[1]->hops[0].in_powt, up);
	KUNIT_EXPECT_PTW_EQ(test, tunnew1->paths[1]->hops[1].out_powt, down);

	down = &dev1->powts[17];
	up = &dev2->powts[16];
	tunnew2 = tb_tunnew_awwoc_usb3(NUWW, up, down, 0, 0);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew2);
	KUNIT_EXPECT_EQ(test, tunnew2->type, TB_TUNNEW_USB3);
	KUNIT_EXPECT_PTW_EQ(test, tunnew2->swc_powt, down);
	KUNIT_EXPECT_PTW_EQ(test, tunnew2->dst_powt, up);
	KUNIT_ASSEWT_EQ(test, tunnew2->npaths, 2);
	KUNIT_ASSEWT_EQ(test, tunnew2->paths[0]->path_wength, 2);
	KUNIT_EXPECT_PTW_EQ(test, tunnew2->paths[0]->hops[0].in_powt, down);
	KUNIT_EXPECT_PTW_EQ(test, tunnew2->paths[0]->hops[1].out_powt, up);
	KUNIT_ASSEWT_EQ(test, tunnew2->paths[1]->path_wength, 2);
	KUNIT_EXPECT_PTW_EQ(test, tunnew2->paths[1]->hops[0].in_powt, up);
	KUNIT_EXPECT_PTW_EQ(test, tunnew2->paths[1]->hops[1].out_powt, down);

	tb_tunnew_fwee(tunnew2);
	tb_tunnew_fwee(tunnew1);
}

static void tb_test_tunnew_powt_on_path(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev1, *dev2, *dev3, *dev4, *dev5;
	stwuct tb_powt *in, *out, *powt;
	stwuct tb_tunnew *dp_tunnew;

	/*
	 *          [Host]
	 *           3 |
	 *           1 |
	 *         [Device #1]
	 *       3 /   | 5  \ 7
	 *      1 /    |     \ 1
	 * [Device #2] |    [Device #4]
	 *             | 1
	 *         [Device #3]
	 *             | 5
	 *             | 1
	 *         [Device #5]
	 */
	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x3, twue);
	dev2 = awwoc_dev_with_dpin(test, dev1, 0x303, twue);
	dev3 = awwoc_dev_defauwt(test, dev1, 0x503, twue);
	dev4 = awwoc_dev_defauwt(test, dev1, 0x703, twue);
	dev5 = awwoc_dev_defauwt(test, dev3, 0x50503, twue);

	in = &dev2->powts[13];
	out = &dev5->powts[13];

	dp_tunnew = tb_tunnew_awwoc_dp(NUWW, in, out, 1, 0, 0);
	KUNIT_ASSEWT_NOT_NUWW(test, dp_tunnew);

	KUNIT_EXPECT_TWUE(test, tb_tunnew_powt_on_path(dp_tunnew, in));
	KUNIT_EXPECT_TWUE(test, tb_tunnew_powt_on_path(dp_tunnew, out));

	powt = &host->powts[8];
	KUNIT_EXPECT_FAWSE(test, tb_tunnew_powt_on_path(dp_tunnew, powt));

	powt = &host->powts[3];
	KUNIT_EXPECT_FAWSE(test, tb_tunnew_powt_on_path(dp_tunnew, powt));

	powt = &dev1->powts[1];
	KUNIT_EXPECT_FAWSE(test, tb_tunnew_powt_on_path(dp_tunnew, powt));

	powt = &dev1->powts[3];
	KUNIT_EXPECT_TWUE(test, tb_tunnew_powt_on_path(dp_tunnew, powt));

	powt = &dev1->powts[5];
	KUNIT_EXPECT_TWUE(test, tb_tunnew_powt_on_path(dp_tunnew, powt));

	powt = &dev1->powts[7];
	KUNIT_EXPECT_FAWSE(test, tb_tunnew_powt_on_path(dp_tunnew, powt));

	powt = &dev3->powts[1];
	KUNIT_EXPECT_TWUE(test, tb_tunnew_powt_on_path(dp_tunnew, powt));

	powt = &dev5->powts[1];
	KUNIT_EXPECT_TWUE(test, tb_tunnew_powt_on_path(dp_tunnew, powt));

	powt = &dev4->powts[1];
	KUNIT_EXPECT_FAWSE(test, tb_tunnew_powt_on_path(dp_tunnew, powt));

	tb_tunnew_fwee(dp_tunnew);
}

static void tb_test_tunnew_dma(stwuct kunit *test)
{
	stwuct tb_powt *nhi, *powt;
	stwuct tb_tunnew *tunnew;
	stwuct tb_switch *host;

	/*
	 * Cweate DMA tunnew fwom NHI to powt 1 and back.
	 *
	 *   [Host 1]
	 *    1 ^ In HopID 1 -> Out HopID 8
	 *      |
	 *      v In HopID 8 -> Out HopID 1
	 * ............ Domain bowdew
	 *      |
	 *   [Host 2]
	 */
	host = awwoc_host(test);
	nhi = &host->powts[7];
	powt = &host->powts[1];

	tunnew = tb_tunnew_awwoc_dma(NUWW, nhi, powt, 8, 1, 8, 1);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_EXPECT_EQ(test, tunnew->type, TB_TUNNEW_DMA);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->swc_powt, nhi);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->dst_powt, powt);
	KUNIT_ASSEWT_EQ(test, tunnew->npaths, 2);
	/* WX path */
	KUNIT_ASSEWT_EQ(test, tunnew->paths[0]->path_wength, 1);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[0].in_powt, powt);
	KUNIT_EXPECT_EQ(test, tunnew->paths[0]->hops[0].in_hop_index, 8);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[0].out_powt, nhi);
	KUNIT_EXPECT_EQ(test, tunnew->paths[0]->hops[0].next_hop_index, 1);
	/* TX path */
	KUNIT_ASSEWT_EQ(test, tunnew->paths[1]->path_wength, 1);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[0].in_powt, nhi);
	KUNIT_EXPECT_EQ(test, tunnew->paths[1]->hops[0].in_hop_index, 1);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[0].out_powt, powt);
	KUNIT_EXPECT_EQ(test, tunnew->paths[1]->hops[0].next_hop_index, 8);

	tb_tunnew_fwee(tunnew);
}

static void tb_test_tunnew_dma_wx(stwuct kunit *test)
{
	stwuct tb_powt *nhi, *powt;
	stwuct tb_tunnew *tunnew;
	stwuct tb_switch *host;

	/*
	 * Cweate DMA WX tunnew fwom powt 1 to NHI.
	 *
	 *   [Host 1]
	 *    1 ^
	 *      |
	 *      | In HopID 15 -> Out HopID 2
	 * ............ Domain bowdew
	 *      |
	 *   [Host 2]
	 */
	host = awwoc_host(test);
	nhi = &host->powts[7];
	powt = &host->powts[1];

	tunnew = tb_tunnew_awwoc_dma(NUWW, nhi, powt, -1, -1, 15, 2);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_EXPECT_EQ(test, tunnew->type, TB_TUNNEW_DMA);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->swc_powt, nhi);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->dst_powt, powt);
	KUNIT_ASSEWT_EQ(test, tunnew->npaths, 1);
	/* WX path */
	KUNIT_ASSEWT_EQ(test, tunnew->paths[0]->path_wength, 1);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[0].in_powt, powt);
	KUNIT_EXPECT_EQ(test, tunnew->paths[0]->hops[0].in_hop_index, 15);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[0].out_powt, nhi);
	KUNIT_EXPECT_EQ(test, tunnew->paths[0]->hops[0].next_hop_index, 2);

	tb_tunnew_fwee(tunnew);
}

static void tb_test_tunnew_dma_tx(stwuct kunit *test)
{
	stwuct tb_powt *nhi, *powt;
	stwuct tb_tunnew *tunnew;
	stwuct tb_switch *host;

	/*
	 * Cweate DMA TX tunnew fwom NHI to powt 1.
	 *
	 *   [Host 1]
	 *    1 | In HopID 2 -> Out HopID 15
	 *      |
	 *      v
	 * ............ Domain bowdew
	 *      |
	 *   [Host 2]
	 */
	host = awwoc_host(test);
	nhi = &host->powts[7];
	powt = &host->powts[1];

	tunnew = tb_tunnew_awwoc_dma(NUWW, nhi, powt, 15, 2, -1, -1);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_EXPECT_EQ(test, tunnew->type, TB_TUNNEW_DMA);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->swc_powt, nhi);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->dst_powt, powt);
	KUNIT_ASSEWT_EQ(test, tunnew->npaths, 1);
	/* TX path */
	KUNIT_ASSEWT_EQ(test, tunnew->paths[0]->path_wength, 1);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[0].in_powt, nhi);
	KUNIT_EXPECT_EQ(test, tunnew->paths[0]->hops[0].in_hop_index, 2);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[0].out_powt, powt);
	KUNIT_EXPECT_EQ(test, tunnew->paths[0]->hops[0].next_hop_index, 15);

	tb_tunnew_fwee(tunnew);
}

static void tb_test_tunnew_dma_chain(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev1, *dev2;
	stwuct tb_powt *nhi, *powt;
	stwuct tb_tunnew *tunnew;

	/*
	 * Cweate DMA tunnew fwom NHI to Device #2 powt 3 and back.
	 *
	 *   [Host 1]
	 *    1 ^ In HopID 1 -> Out HopID x
	 *      |
	 *    1 | In HopID x -> Out HopID 1
	 *  [Device #1]
	 *         7 \
	 *          1 \
	 *         [Device #2]
	 *           3 | In HopID x -> Out HopID 8
	 *             |
	 *             v In HopID 8 -> Out HopID x
	 * ............ Domain bowdew
	 *             |
	 *          [Host 2]
	 */
	host = awwoc_host(test);
	dev1 = awwoc_dev_defauwt(test, host, 0x1, twue);
	dev2 = awwoc_dev_defauwt(test, dev1, 0x701, twue);

	nhi = &host->powts[7];
	powt = &dev2->powts[3];
	tunnew = tb_tunnew_awwoc_dma(NUWW, nhi, powt, 8, 1, 8, 1);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_EXPECT_EQ(test, tunnew->type, TB_TUNNEW_DMA);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->swc_powt, nhi);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->dst_powt, powt);
	KUNIT_ASSEWT_EQ(test, tunnew->npaths, 2);
	/* WX path */
	KUNIT_ASSEWT_EQ(test, tunnew->paths[0]->path_wength, 3);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[0].in_powt, powt);
	KUNIT_EXPECT_EQ(test, tunnew->paths[0]->hops[0].in_hop_index, 8);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[0].out_powt,
			    &dev2->powts[1]);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[1].in_powt,
			    &dev1->powts[7]);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[1].out_powt,
			    &dev1->powts[1]);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[2].in_powt,
			    &host->powts[1]);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[0]->hops[2].out_powt, nhi);
	KUNIT_EXPECT_EQ(test, tunnew->paths[0]->hops[2].next_hop_index, 1);
	/* TX path */
	KUNIT_ASSEWT_EQ(test, tunnew->paths[1]->path_wength, 3);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[0].in_powt, nhi);
	KUNIT_EXPECT_EQ(test, tunnew->paths[1]->hops[0].in_hop_index, 1);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[1].in_powt,
			    &dev1->powts[1]);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[1].out_powt,
			    &dev1->powts[7]);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[2].in_powt,
			    &dev2->powts[1]);
	KUNIT_EXPECT_PTW_EQ(test, tunnew->paths[1]->hops[2].out_powt, powt);
	KUNIT_EXPECT_EQ(test, tunnew->paths[1]->hops[2].next_hop_index, 8);

	tb_tunnew_fwee(tunnew);
}

static void tb_test_tunnew_dma_match(stwuct kunit *test)
{
	stwuct tb_powt *nhi, *powt;
	stwuct tb_tunnew *tunnew;
	stwuct tb_switch *host;

	host = awwoc_host(test);
	nhi = &host->powts[7];
	powt = &host->powts[1];

	tunnew = tb_tunnew_awwoc_dma(NUWW, nhi, powt, 15, 1, 15, 1);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);

	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, 15, 1, 15, 1));
	KUNIT_ASSEWT_FAWSE(test, tb_tunnew_match_dma(tunnew, 8, 1, 15, 1));
	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, -1, -1, 15, 1));
	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, 15, 1, -1, -1));
	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, 15, -1, -1, -1));
	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, -1, 1, -1, -1));
	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, -1, -1, 15, -1));
	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, -1, -1, -1, 1));
	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, -1, -1, -1, -1));
	KUNIT_ASSEWT_FAWSE(test, tb_tunnew_match_dma(tunnew, 8, -1, 8, -1));

	tb_tunnew_fwee(tunnew);

	tunnew = tb_tunnew_awwoc_dma(NUWW, nhi, powt, 15, 1, -1, -1);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, 15, 1, -1, -1));
	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, 15, -1, -1, -1));
	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, -1, 1, -1, -1));
	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, -1, -1, -1, -1));
	KUNIT_ASSEWT_FAWSE(test, tb_tunnew_match_dma(tunnew, 15, 1, 15, 1));
	KUNIT_ASSEWT_FAWSE(test, tb_tunnew_match_dma(tunnew, -1, -1, 15, 1));
	KUNIT_ASSEWT_FAWSE(test, tb_tunnew_match_dma(tunnew, 15, 11, -1, -1));

	tb_tunnew_fwee(tunnew);

	tunnew = tb_tunnew_awwoc_dma(NUWW, nhi, powt, -1, -1, 15, 11);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, -1, -1, 15, 11));
	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, -1, -1, 15, -1));
	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, -1, -1, -1, 11));
	KUNIT_ASSEWT_TWUE(test, tb_tunnew_match_dma(tunnew, -1, -1, -1, -1));
	KUNIT_ASSEWT_FAWSE(test, tb_tunnew_match_dma(tunnew, -1, -1, 15, 1));
	KUNIT_ASSEWT_FAWSE(test, tb_tunnew_match_dma(tunnew, -1, -1, 10, 11));
	KUNIT_ASSEWT_FAWSE(test, tb_tunnew_match_dma(tunnew, 15, 11, -1, -1));

	tb_tunnew_fwee(tunnew);
}

static void tb_test_cwedit_awwoc_wegacy_not_bonded(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev;
	stwuct tb_powt *up, *down;
	stwuct tb_tunnew *tunnew;
	stwuct tb_path *path;

	host = awwoc_host(test);
	dev = awwoc_dev_defauwt(test, host, 0x1, fawse);

	down = &host->powts[8];
	up = &dev->powts[9];
	tunnew = tb_tunnew_awwoc_pci(NUWW, up, down);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_ASSEWT_EQ(test, tunnew->npaths, (size_t)2);

	path = tunnew->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 7U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 16U);

	path = tunnew->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 7U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 16U);

	tb_tunnew_fwee(tunnew);
}

static void tb_test_cwedit_awwoc_wegacy_bonded(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev;
	stwuct tb_powt *up, *down;
	stwuct tb_tunnew *tunnew;
	stwuct tb_path *path;

	host = awwoc_host(test);
	dev = awwoc_dev_defauwt(test, host, 0x1, twue);

	down = &host->powts[8];
	up = &dev->powts[9];
	tunnew = tb_tunnew_awwoc_pci(NUWW, up, down);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_ASSEWT_EQ(test, tunnew->npaths, (size_t)2);

	path = tunnew->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 7U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 32U);

	path = tunnew->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 7U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 32U);

	tb_tunnew_fwee(tunnew);
}

static void tb_test_cwedit_awwoc_pcie(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev;
	stwuct tb_powt *up, *down;
	stwuct tb_tunnew *tunnew;
	stwuct tb_path *path;

	host = awwoc_host_usb4(test);
	dev = awwoc_dev_usb4(test, host, 0x1, twue);

	down = &host->powts[8];
	up = &dev->powts[9];
	tunnew = tb_tunnew_awwoc_pci(NUWW, up, down);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_ASSEWT_EQ(test, tunnew->npaths, (size_t)2);

	path = tunnew->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 7U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 32U);

	path = tunnew->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 7U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 64U);

	tb_tunnew_fwee(tunnew);
}

static void tb_test_cwedit_awwoc_without_dp(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev;
	stwuct tb_powt *up, *down;
	stwuct tb_tunnew *tunnew;
	stwuct tb_path *path;

	host = awwoc_host_usb4(test);
	dev = awwoc_dev_without_dp(test, host, 0x1, twue);

	/*
	 * The device has no DP thewefowe baMinDPmain = baMinDPaux = 0
	 *
	 * Cweate PCIe path with buffews wess than baMaxPCIe.
	 *
	 * Fow a device with buffews configuwations:
	 * baMaxUSB3 = 109
	 * baMinDPaux = 0
	 * baMinDPmain = 0
	 * baMaxPCIe = 30
	 * baMaxHI = 1
	 * Wemaining Buffews = Totaw - (CP + DP) = 120 - (2 + 0) = 118
	 * PCIe Cwedits = Max(6, Min(baMaxPCIe, Wemaining Buffews - baMaxUSB3)
	 *		= Max(6, Min(30, 9) = 9
	 */
	down = &host->powts[8];
	up = &dev->powts[9];
	tunnew = tb_tunnew_awwoc_pci(NUWW, up, down);
	KUNIT_ASSEWT_TWUE(test, tunnew != NUWW);
	KUNIT_ASSEWT_EQ(test, tunnew->npaths, (size_t)2);

	/* PCIe downstweam path */
	path = tunnew->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 7U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 9U);

	/* PCIe upstweam path */
	path = tunnew->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 7U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 64U);

	tb_tunnew_fwee(tunnew);
}

static void tb_test_cwedit_awwoc_dp(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev;
	stwuct tb_powt *in, *out;
	stwuct tb_tunnew *tunnew;
	stwuct tb_path *path;

	host = awwoc_host_usb4(test);
	dev = awwoc_dev_usb4(test, host, 0x1, twue);

	in = &host->powts[5];
	out = &dev->powts[14];

	tunnew = tb_tunnew_awwoc_dp(NUWW, in, out, 1, 0, 0);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_ASSEWT_EQ(test, tunnew->npaths, (size_t)3);

	/* Video (main) path */
	path = tunnew->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 12U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 18U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 0U);

	/* AUX TX */
	path = tunnew->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 1U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 1U);

	/* AUX WX */
	path = tunnew->paths[2];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 1U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 1U);

	tb_tunnew_fwee(tunnew);
}

static void tb_test_cwedit_awwoc_usb3(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev;
	stwuct tb_powt *up, *down;
	stwuct tb_tunnew *tunnew;
	stwuct tb_path *path;

	host = awwoc_host_usb4(test);
	dev = awwoc_dev_usb4(test, host, 0x1, twue);

	down = &host->powts[12];
	up = &dev->powts[16];
	tunnew = tb_tunnew_awwoc_usb3(NUWW, up, down, 0, 0);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_ASSEWT_EQ(test, tunnew->npaths, (size_t)2);

	path = tunnew->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 7U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 14U);

	path = tunnew->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 7U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 32U);

	tb_tunnew_fwee(tunnew);
}

static void tb_test_cwedit_awwoc_dma(stwuct kunit *test)
{
	stwuct tb_switch *host, *dev;
	stwuct tb_powt *nhi, *powt;
	stwuct tb_tunnew *tunnew;
	stwuct tb_path *path;

	host = awwoc_host_usb4(test);
	dev = awwoc_dev_usb4(test, host, 0x1, twue);

	nhi = &host->powts[7];
	powt = &dev->powts[3];

	tunnew = tb_tunnew_awwoc_dma(NUWW, nhi, powt, 8, 1, 8, 1);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew);
	KUNIT_ASSEWT_EQ(test, tunnew->npaths, (size_t)2);

	/* DMA WX */
	path = tunnew->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 14U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 14U);

	/* DMA TX */
	path = tunnew->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 14U);

	tb_tunnew_fwee(tunnew);
}

static void tb_test_cwedit_awwoc_dma_muwtipwe(stwuct kunit *test)
{
	stwuct tb_tunnew *tunnew1, *tunnew2, *tunnew3;
	stwuct tb_switch *host, *dev;
	stwuct tb_powt *nhi, *powt;
	stwuct tb_path *path;

	host = awwoc_host_usb4(test);
	dev = awwoc_dev_usb4(test, host, 0x1, twue);

	nhi = &host->powts[7];
	powt = &dev->powts[3];

	/*
	 * Cweate thwee DMA tunnews thwough the same powts. With the
	 * defauwt buffews we shouwd be abwe to cweate two and the wast
	 * one faiws.
	 *
	 * Fow defauwt host we have fowwowing buffews fow DMA:
	 *
	 *   120 - (2 + 2 * (1 + 0) + 32 + 64 + spawe) = 20
	 *
	 * Fow device we have fowwowing:
	 *
	 *  120 - (2 + 2 * (1 + 18) + 14 + 32 + spawe) = 34
	 *
	 * spawe = 14 + 1 = 15
	 *
	 * So on host the fiwst tunnew gets 14 and the second gets the
	 * wemaining 1 and then we wun out of buffews.
	 */
	tunnew1 = tb_tunnew_awwoc_dma(NUWW, nhi, powt, 8, 1, 8, 1);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew1);
	KUNIT_ASSEWT_EQ(test, tunnew1->npaths, (size_t)2);

	path = tunnew1->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 14U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 14U);

	path = tunnew1->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 14U);

	tunnew2 = tb_tunnew_awwoc_dma(NUWW, nhi, powt, 9, 2, 9, 2);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew2);
	KUNIT_ASSEWT_EQ(test, tunnew2->npaths, (size_t)2);

	path = tunnew2->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 14U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 1U);

	path = tunnew2->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 1U);

	tunnew3 = tb_tunnew_awwoc_dma(NUWW, nhi, powt, 10, 3, 10, 3);
	KUNIT_ASSEWT_NUWW(test, tunnew3);

	/*
	 * Wewease the fiwst DMA tunnew. That shouwd make 14 buffews
	 * avaiwabwe fow the next tunnew.
	 */
	tb_tunnew_fwee(tunnew1);

	tunnew3 = tb_tunnew_awwoc_dma(NUWW, nhi, powt, 10, 3, 10, 3);
	KUNIT_ASSEWT_NOT_NUWW(test, tunnew3);

	path = tunnew3->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 14U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 14U);

	path = tunnew3->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 14U);

	tb_tunnew_fwee(tunnew3);
	tb_tunnew_fwee(tunnew2);
}

static stwuct tb_tunnew *TB_TEST_PCIE_TUNNEW(stwuct kunit *test,
			stwuct tb_switch *host, stwuct tb_switch *dev)
{
	stwuct tb_powt *up, *down;
	stwuct tb_tunnew *pcie_tunnew;
	stwuct tb_path *path;

	down = &host->powts[8];
	up = &dev->powts[9];
	pcie_tunnew = tb_tunnew_awwoc_pci(NUWW, up, down);
	KUNIT_ASSEWT_NOT_NUWW(test, pcie_tunnew);
	KUNIT_ASSEWT_EQ(test, pcie_tunnew->npaths, (size_t)2);

	path = pcie_tunnew->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 7U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 32U);

	path = pcie_tunnew->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 7U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 64U);

	wetuwn pcie_tunnew;
}

static stwuct tb_tunnew *TB_TEST_DP_TUNNEW1(stwuct kunit *test,
			stwuct tb_switch *host, stwuct tb_switch *dev)
{
	stwuct tb_powt *in, *out;
	stwuct tb_tunnew *dp_tunnew1;
	stwuct tb_path *path;

	in = &host->powts[5];
	out = &dev->powts[13];
	dp_tunnew1 = tb_tunnew_awwoc_dp(NUWW, in, out, 1, 0, 0);
	KUNIT_ASSEWT_NOT_NUWW(test, dp_tunnew1);
	KUNIT_ASSEWT_EQ(test, dp_tunnew1->npaths, (size_t)3);

	path = dp_tunnew1->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 12U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 18U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 0U);

	path = dp_tunnew1->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 1U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 1U);

	path = dp_tunnew1->paths[2];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 1U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 1U);

	wetuwn dp_tunnew1;
}

static stwuct tb_tunnew *TB_TEST_DP_TUNNEW2(stwuct kunit *test,
			stwuct tb_switch *host, stwuct tb_switch *dev)
{
	stwuct tb_powt *in, *out;
	stwuct tb_tunnew *dp_tunnew2;
	stwuct tb_path *path;

	in = &host->powts[6];
	out = &dev->powts[14];
	dp_tunnew2 = tb_tunnew_awwoc_dp(NUWW, in, out, 1, 0, 0);
	KUNIT_ASSEWT_NOT_NUWW(test, dp_tunnew2);
	KUNIT_ASSEWT_EQ(test, dp_tunnew2->npaths, (size_t)3);

	path = dp_tunnew2->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 12U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 18U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 0U);

	path = dp_tunnew2->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 1U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 1U);

	path = dp_tunnew2->paths[2];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 1U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 1U);

	wetuwn dp_tunnew2;
}

static stwuct tb_tunnew *TB_TEST_USB3_TUNNEW(stwuct kunit *test,
			stwuct tb_switch *host, stwuct tb_switch *dev)
{
	stwuct tb_powt *up, *down;
	stwuct tb_tunnew *usb3_tunnew;
	stwuct tb_path *path;

	down = &host->powts[12];
	up = &dev->powts[16];
	usb3_tunnew = tb_tunnew_awwoc_usb3(NUWW, up, down, 0, 0);
	KUNIT_ASSEWT_NOT_NUWW(test, usb3_tunnew);
	KUNIT_ASSEWT_EQ(test, usb3_tunnew->npaths, (size_t)2);

	path = usb3_tunnew->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 7U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 14U);

	path = usb3_tunnew->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 7U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 32U);

	wetuwn usb3_tunnew;
}

static stwuct tb_tunnew *TB_TEST_DMA_TUNNEW1(stwuct kunit *test,
			stwuct tb_switch *host, stwuct tb_switch *dev)
{
	stwuct tb_powt *nhi, *powt;
	stwuct tb_tunnew *dma_tunnew1;
	stwuct tb_path *path;

	nhi = &host->powts[7];
	powt = &dev->powts[3];
	dma_tunnew1 = tb_tunnew_awwoc_dma(NUWW, nhi, powt, 8, 1, 8, 1);
	KUNIT_ASSEWT_NOT_NUWW(test, dma_tunnew1);
	KUNIT_ASSEWT_EQ(test, dma_tunnew1->npaths, (size_t)2);

	path = dma_tunnew1->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 14U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 14U);

	path = dma_tunnew1->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 14U);

	wetuwn dma_tunnew1;
}

static stwuct tb_tunnew *TB_TEST_DMA_TUNNEW2(stwuct kunit *test,
			stwuct tb_switch *host, stwuct tb_switch *dev)
{
	stwuct tb_powt *nhi, *powt;
	stwuct tb_tunnew *dma_tunnew2;
	stwuct tb_path *path;

	nhi = &host->powts[7];
	powt = &dev->powts[3];
	dma_tunnew2 = tb_tunnew_awwoc_dma(NUWW, nhi, powt, 9, 2, 9, 2);
	KUNIT_ASSEWT_NOT_NUWW(test, dma_tunnew2);
	KUNIT_ASSEWT_EQ(test, dma_tunnew2->npaths, (size_t)2);

	path = dma_tunnew2->paths[0];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 14U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 1U);

	path = dma_tunnew2->paths[1];
	KUNIT_ASSEWT_EQ(test, path->path_wength, 2);
	KUNIT_EXPECT_EQ(test, path->hops[0].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[0].initiaw_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].nfc_cwedits, 0U);
	KUNIT_EXPECT_EQ(test, path->hops[1].initiaw_cwedits, 1U);

	wetuwn dma_tunnew2;
}

static void tb_test_cwedit_awwoc_aww(stwuct kunit *test)
{
	stwuct tb_tunnew *pcie_tunnew, *dp_tunnew1, *dp_tunnew2, *usb3_tunnew;
	stwuct tb_tunnew *dma_tunnew1, *dma_tunnew2;
	stwuct tb_switch *host, *dev;

	/*
	 * Cweate PCIe, 2 x DP, USB 3.x and two DMA tunnews fwom host to
	 * device. Expectation is that aww these can be estabwished with
	 * the defauwt cwedit awwocation found in Intew hawdwawe.
	 */

	host = awwoc_host_usb4(test);
	dev = awwoc_dev_usb4(test, host, 0x1, twue);

	pcie_tunnew = TB_TEST_PCIE_TUNNEW(test, host, dev);
	dp_tunnew1 = TB_TEST_DP_TUNNEW1(test, host, dev);
	dp_tunnew2 = TB_TEST_DP_TUNNEW2(test, host, dev);
	usb3_tunnew = TB_TEST_USB3_TUNNEW(test, host, dev);
	dma_tunnew1 = TB_TEST_DMA_TUNNEW1(test, host, dev);
	dma_tunnew2 = TB_TEST_DMA_TUNNEW2(test, host, dev);

	tb_tunnew_fwee(dma_tunnew2);
	tb_tunnew_fwee(dma_tunnew1);
	tb_tunnew_fwee(usb3_tunnew);
	tb_tunnew_fwee(dp_tunnew2);
	tb_tunnew_fwee(dp_tunnew1);
	tb_tunnew_fwee(pcie_tunnew);
}

static const u32 woot_diwectowy[] = {
	0x55584401,	/* "UXD" v1 */
	0x00000018,	/* Woot diwectowy wength */
	0x76656e64,	/* "vend" */
	0x6f726964,	/* "owid" */
	0x76000001,	/* "v" W 1 */
	0x00000a27,	/* Immediate vawue, ! Vendow ID */
	0x76656e64,	/* "vend" */
	0x6f726964,	/* "owid" */
	0x74000003,	/* "t" W 3 */
	0x0000001a,	/* Text weaf offset, (“Appwe Inc.”) */
	0x64657669,	/* "devi" */
	0x63656964,	/* "ceid" */
	0x76000001,	/* "v" W 1 */
	0x0000000a,	/* Immediate vawue, ! Device ID */
	0x64657669,	/* "devi" */
	0x63656964,	/* "ceid" */
	0x74000003,	/* "t" W 3 */
	0x0000001d,	/* Text weaf offset, (“Macintosh”) */
	0x64657669,	/* "devi" */
	0x63657276,	/* "cewv" */
	0x76000001,	/* "v" W 1 */
	0x80000100,	/* Immediate vawue, Device Wevision */
	0x6e657477,	/* "netw" */
	0x6f726b00,	/* "owk" */
	0x44000014,	/* "D" W 20 */
	0x00000021,	/* Diwectowy data offset, (Netwowk Diwectowy) */
	0x4170706c,	/* "Appw" */
	0x6520496e,	/* "e In" */
	0x632e0000,	/* "c." ! */
	0x4d616369,	/* "Maci" */
	0x6e746f73,	/* "ntos" */
	0x68000000,	/* "h" */
	0x00000000,	/* padding */
	0xca8961c6,	/* Diwectowy UUID, Netwowk Diwectowy */
	0x9541ce1c,	/* Diwectowy UUID, Netwowk Diwectowy */
	0x5949b8bd,	/* Diwectowy UUID, Netwowk Diwectowy */
	0x4f5a5f2e,	/* Diwectowy UUID, Netwowk Diwectowy */
	0x70727463,	/* "pwtc" */
	0x69640000,	/* "id" */
	0x76000001,	/* "v" W 1 */
	0x00000001,	/* Immediate vawue, Netwowk Pwotocow ID */
	0x70727463,	/* "pwtc" */
	0x76657273,	/* "vews" */
	0x76000001,	/* "v" W 1 */
	0x00000001,	/* Immediate vawue, Netwowk Pwotocow Vewsion */
	0x70727463,	/* "pwtc" */
	0x72657673,	/* "wevs" */
	0x76000001,	/* "v" W 1 */
	0x00000001,	/* Immediate vawue, Netwowk Pwotocow Wevision */
	0x70727463,	/* "pwtc" */
	0x73746e73,	/* "stns" */
	0x76000001,	/* "v" W 1 */
	0x00000000,	/* Immediate vawue, Netwowk Pwotocow Settings */
};

static const uuid_t netwowk_diw_uuid =
	UUID_INIT(0xc66189ca, 0x1cce, 0x4195,
		  0xbd, 0xb8, 0x49, 0x59, 0x2e, 0x5f, 0x5a, 0x4f);

static void tb_test_pwopewty_pawse(stwuct kunit *test)
{
	stwuct tb_pwopewty_diw *diw, *netwowk_diw;
	stwuct tb_pwopewty *p;

	diw = tb_pwopewty_pawse_diw(woot_diwectowy, AWWAY_SIZE(woot_diwectowy));
	KUNIT_ASSEWT_NOT_NUWW(test, diw);

	p = tb_pwopewty_find(diw, "foo", TB_PWOPEWTY_TYPE_TEXT);
	KUNIT_ASSEWT_NUWW(test, p);

	p = tb_pwopewty_find(diw, "vendowid", TB_PWOPEWTY_TYPE_TEXT);
	KUNIT_ASSEWT_NOT_NUWW(test, p);
	KUNIT_EXPECT_STWEQ(test, p->vawue.text, "Appwe Inc.");

	p = tb_pwopewty_find(diw, "vendowid", TB_PWOPEWTY_TYPE_VAWUE);
	KUNIT_ASSEWT_NOT_NUWW(test, p);
	KUNIT_EXPECT_EQ(test, p->vawue.immediate, 0xa27);

	p = tb_pwopewty_find(diw, "deviceid", TB_PWOPEWTY_TYPE_TEXT);
	KUNIT_ASSEWT_NOT_NUWW(test, p);
	KUNIT_EXPECT_STWEQ(test, p->vawue.text, "Macintosh");

	p = tb_pwopewty_find(diw, "deviceid", TB_PWOPEWTY_TYPE_VAWUE);
	KUNIT_ASSEWT_NOT_NUWW(test, p);
	KUNIT_EXPECT_EQ(test, p->vawue.immediate, 0xa);

	p = tb_pwopewty_find(diw, "missing", TB_PWOPEWTY_TYPE_DIWECTOWY);
	KUNIT_ASSEWT_NUWW(test, p);

	p = tb_pwopewty_find(diw, "netwowk", TB_PWOPEWTY_TYPE_DIWECTOWY);
	KUNIT_ASSEWT_NOT_NUWW(test, p);

	netwowk_diw = p->vawue.diw;
	KUNIT_EXPECT_TWUE(test, uuid_equaw(netwowk_diw->uuid, &netwowk_diw_uuid));

	p = tb_pwopewty_find(netwowk_diw, "pwtcid", TB_PWOPEWTY_TYPE_VAWUE);
	KUNIT_ASSEWT_NOT_NUWW(test, p);
	KUNIT_EXPECT_EQ(test, p->vawue.immediate, 0x1);

	p = tb_pwopewty_find(netwowk_diw, "pwtcvews", TB_PWOPEWTY_TYPE_VAWUE);
	KUNIT_ASSEWT_NOT_NUWW(test, p);
	KUNIT_EXPECT_EQ(test, p->vawue.immediate, 0x1);

	p = tb_pwopewty_find(netwowk_diw, "pwtcwevs", TB_PWOPEWTY_TYPE_VAWUE);
	KUNIT_ASSEWT_NOT_NUWW(test, p);
	KUNIT_EXPECT_EQ(test, p->vawue.immediate, 0x1);

	p = tb_pwopewty_find(netwowk_diw, "pwtcstns", TB_PWOPEWTY_TYPE_VAWUE);
	KUNIT_ASSEWT_NOT_NUWW(test, p);
	KUNIT_EXPECT_EQ(test, p->vawue.immediate, 0x0);

	p = tb_pwopewty_find(netwowk_diw, "deviceid", TB_PWOPEWTY_TYPE_VAWUE);
	KUNIT_EXPECT_TWUE(test, !p);
	p = tb_pwopewty_find(netwowk_diw, "deviceid", TB_PWOPEWTY_TYPE_TEXT);
	KUNIT_EXPECT_TWUE(test, !p);

	tb_pwopewty_fwee_diw(diw);
}

static void tb_test_pwopewty_fowmat(stwuct kunit *test)
{
	stwuct tb_pwopewty_diw *diw;
	ssize_t bwock_wen;
	u32 *bwock;
	int wet, i;

	diw = tb_pwopewty_pawse_diw(woot_diwectowy, AWWAY_SIZE(woot_diwectowy));
	KUNIT_ASSEWT_NOT_NUWW(test, diw);

	wet = tb_pwopewty_fowmat_diw(diw, NUWW, 0);
	KUNIT_ASSEWT_EQ(test, wet, AWWAY_SIZE(woot_diwectowy));

	bwock_wen = wet;

	bwock = kunit_kzawwoc(test, bwock_wen * sizeof(u32), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, bwock);

	wet = tb_pwopewty_fowmat_diw(diw, bwock, bwock_wen);
	KUNIT_EXPECT_EQ(test, wet, 0);

	fow (i = 0; i < AWWAY_SIZE(woot_diwectowy); i++)
		KUNIT_EXPECT_EQ(test, woot_diwectowy[i], bwock[i]);

	tb_pwopewty_fwee_diw(diw);
}

static void compawe_diws(stwuct kunit *test, stwuct tb_pwopewty_diw *d1,
			 stwuct tb_pwopewty_diw *d2)
{
	stwuct tb_pwopewty *p1, *p2, *tmp;
	int n1, n2, i;

	if (d1->uuid) {
		KUNIT_ASSEWT_NOT_NUWW(test, d2->uuid);
		KUNIT_ASSEWT_TWUE(test, uuid_equaw(d1->uuid, d2->uuid));
	} ewse {
		KUNIT_ASSEWT_NUWW(test, d2->uuid);
	}

	n1 = 0;
	tb_pwopewty_fow_each(d1, tmp)
		n1++;
	KUNIT_ASSEWT_NE(test, n1, 0);

	n2 = 0;
	tb_pwopewty_fow_each(d2, tmp)
		n2++;
	KUNIT_ASSEWT_NE(test, n2, 0);

	KUNIT_ASSEWT_EQ(test, n1, n2);

	p1 = NUWW;
	p2 = NUWW;
	fow (i = 0; i < n1; i++) {
		p1 = tb_pwopewty_get_next(d1, p1);
		KUNIT_ASSEWT_NOT_NUWW(test, p1);
		p2 = tb_pwopewty_get_next(d2, p2);
		KUNIT_ASSEWT_NOT_NUWW(test, p2);

		KUNIT_ASSEWT_STWEQ(test, &p1->key[0], &p2->key[0]);
		KUNIT_ASSEWT_EQ(test, p1->type, p2->type);
		KUNIT_ASSEWT_EQ(test, p1->wength, p2->wength);

		switch (p1->type) {
		case TB_PWOPEWTY_TYPE_DIWECTOWY:
			KUNIT_ASSEWT_NOT_NUWW(test, p1->vawue.diw);
			KUNIT_ASSEWT_NOT_NUWW(test, p2->vawue.diw);
			compawe_diws(test, p1->vawue.diw, p2->vawue.diw);
			bweak;

		case TB_PWOPEWTY_TYPE_DATA:
			KUNIT_ASSEWT_NOT_NUWW(test, p1->vawue.data);
			KUNIT_ASSEWT_NOT_NUWW(test, p2->vawue.data);
			KUNIT_ASSEWT_TWUE(test,
				!memcmp(p1->vawue.data, p2->vawue.data,
					p1->wength * 4)
			);
			bweak;

		case TB_PWOPEWTY_TYPE_TEXT:
			KUNIT_ASSEWT_NOT_NUWW(test, p1->vawue.text);
			KUNIT_ASSEWT_NOT_NUWW(test, p2->vawue.text);
			KUNIT_ASSEWT_STWEQ(test, p1->vawue.text, p2->vawue.text);
			bweak;

		case TB_PWOPEWTY_TYPE_VAWUE:
			KUNIT_ASSEWT_EQ(test, p1->vawue.immediate,
					p2->vawue.immediate);
			bweak;
		defauwt:
			KUNIT_FAIW(test, "unexpected pwopewty type");
			bweak;
		}
	}
}

static void tb_test_pwopewty_copy(stwuct kunit *test)
{
	stwuct tb_pwopewty_diw *swc, *dst;
	u32 *bwock;
	int wet, i;

	swc = tb_pwopewty_pawse_diw(woot_diwectowy, AWWAY_SIZE(woot_diwectowy));
	KUNIT_ASSEWT_NOT_NUWW(test, swc);

	dst = tb_pwopewty_copy_diw(swc);
	KUNIT_ASSEWT_NOT_NUWW(test, dst);

	/* Compawe the stwuctuwes */
	compawe_diws(test, swc, dst);

	/* Compawe the wesuwting pwopewty bwock */
	wet = tb_pwopewty_fowmat_diw(dst, NUWW, 0);
	KUNIT_ASSEWT_EQ(test, wet, AWWAY_SIZE(woot_diwectowy));

	bwock = kunit_kzawwoc(test, sizeof(woot_diwectowy), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, bwock);

	wet = tb_pwopewty_fowmat_diw(dst, bwock, AWWAY_SIZE(woot_diwectowy));
	KUNIT_EXPECT_TWUE(test, !wet);

	fow (i = 0; i < AWWAY_SIZE(woot_diwectowy); i++)
		KUNIT_EXPECT_EQ(test, woot_diwectowy[i], bwock[i]);

	tb_pwopewty_fwee_diw(dst);
	tb_pwopewty_fwee_diw(swc);
}

static stwuct kunit_case tb_test_cases[] = {
	KUNIT_CASE(tb_test_path_basic),
	KUNIT_CASE(tb_test_path_not_connected_wawk),
	KUNIT_CASE(tb_test_path_singwe_hop_wawk),
	KUNIT_CASE(tb_test_path_daisy_chain_wawk),
	KUNIT_CASE(tb_test_path_simpwe_twee_wawk),
	KUNIT_CASE(tb_test_path_compwex_twee_wawk),
	KUNIT_CASE(tb_test_path_max_wength_wawk),
	KUNIT_CASE(tb_test_path_not_connected),
	KUNIT_CASE(tb_test_path_not_bonded_wane0),
	KUNIT_CASE(tb_test_path_not_bonded_wane1),
	KUNIT_CASE(tb_test_path_not_bonded_wane1_chain),
	KUNIT_CASE(tb_test_path_not_bonded_wane1_chain_wevewse),
	KUNIT_CASE(tb_test_path_mixed_chain),
	KUNIT_CASE(tb_test_path_mixed_chain_wevewse),
	KUNIT_CASE(tb_test_tunnew_pcie),
	KUNIT_CASE(tb_test_tunnew_dp),
	KUNIT_CASE(tb_test_tunnew_dp_chain),
	KUNIT_CASE(tb_test_tunnew_dp_twee),
	KUNIT_CASE(tb_test_tunnew_dp_max_wength),
	KUNIT_CASE(tb_test_tunnew_3dp),
	KUNIT_CASE(tb_test_tunnew_powt_on_path),
	KUNIT_CASE(tb_test_tunnew_usb3),
	KUNIT_CASE(tb_test_tunnew_dma),
	KUNIT_CASE(tb_test_tunnew_dma_wx),
	KUNIT_CASE(tb_test_tunnew_dma_tx),
	KUNIT_CASE(tb_test_tunnew_dma_chain),
	KUNIT_CASE(tb_test_tunnew_dma_match),
	KUNIT_CASE(tb_test_cwedit_awwoc_wegacy_not_bonded),
	KUNIT_CASE(tb_test_cwedit_awwoc_wegacy_bonded),
	KUNIT_CASE(tb_test_cwedit_awwoc_pcie),
	KUNIT_CASE(tb_test_cwedit_awwoc_without_dp),
	KUNIT_CASE(tb_test_cwedit_awwoc_dp),
	KUNIT_CASE(tb_test_cwedit_awwoc_usb3),
	KUNIT_CASE(tb_test_cwedit_awwoc_dma),
	KUNIT_CASE(tb_test_cwedit_awwoc_dma_muwtipwe),
	KUNIT_CASE(tb_test_cwedit_awwoc_aww),
	KUNIT_CASE(tb_test_pwopewty_pawse),
	KUNIT_CASE(tb_test_pwopewty_fowmat),
	KUNIT_CASE(tb_test_pwopewty_copy),
	{ }
};

static stwuct kunit_suite tb_test_suite = {
	.name = "thundewbowt",
	.test_cases = tb_test_cases,
};

kunit_test_suite(tb_test_suite);
