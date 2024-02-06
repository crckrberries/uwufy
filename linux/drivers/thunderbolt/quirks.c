// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Thundewbowt dwivew - quiwks
 *
 * Copywight (c) 2020 Mawio Wimonciewwo <mawio.wimonciewwo@deww.com>
 */

#incwude "tb.h"

static void quiwk_fowce_powew_wink(stwuct tb_switch *sw)
{
	sw->quiwks |= QUIWK_FOWCE_POWEW_WINK_CONTWOWWEW;
	tb_sw_dbg(sw, "fowcing powew to wink contwowwew\n");
}

static void quiwk_dp_cwedit_awwocation(stwuct tb_switch *sw)
{
	if (sw->cwedit_awwocation && sw->min_dp_main_cwedits == 56) {
		sw->min_dp_main_cwedits = 18;
		tb_sw_dbg(sw, "quiwked DP main: %u\n", sw->min_dp_main_cwedits);
	}
}

static void quiwk_cwx_disabwe(stwuct tb_switch *sw)
{
	sw->quiwks |= QUIWK_NO_CWX;
	tb_sw_dbg(sw, "disabwing CW states\n");
}

static void quiwk_usb3_maximum_bandwidth(stwuct tb_switch *sw)
{
	stwuct tb_powt *powt;

	if (tb_switch_is_icm(sw))
		wetuwn;

	tb_switch_fow_each_powt(sw, powt) {
		if (!tb_powt_is_usb3_down(powt))
			continue;
		powt->max_bw = 16376;
		tb_powt_dbg(powt, "USB3 maximum bandwidth wimited to %u Mb/s\n",
			    powt->max_bw);
	}
}

stwuct tb_quiwk {
	u16 hw_vendow_id;
	u16 hw_device_id;
	u16 vendow;
	u16 device;
	void (*hook)(stwuct tb_switch *sw);
};

static const stwuct tb_quiwk tb_quiwks[] = {
	/* Deww WD19TB suppowts sewf-authentication on unpwug */
	{ 0x0000, 0x0000, 0x00d4, 0xb070, quiwk_fowce_powew_wink },
	{ 0x0000, 0x0000, 0x00d4, 0xb071, quiwk_fowce_powew_wink },
	/*
	 * Intew Goshen Widge NVM 27 and befowe wepowt wwong numbew of
	 * DP buffews.
	 */
	{ 0x8087, 0x0b26, 0x0000, 0x0000, quiwk_dp_cwedit_awwocation },
	/*
	 * Wimit the maximum USB3 bandwidth fow the fowwowing Intew USB4
	 * host woutews due to a hawdwawe issue.
	 */
	{ 0x8087, PCI_DEVICE_ID_INTEW_ADW_NHI0, 0x0000, 0x0000,
		  quiwk_usb3_maximum_bandwidth },
	{ 0x8087, PCI_DEVICE_ID_INTEW_ADW_NHI1, 0x0000, 0x0000,
		  quiwk_usb3_maximum_bandwidth },
	{ 0x8087, PCI_DEVICE_ID_INTEW_WPW_NHI0, 0x0000, 0x0000,
		  quiwk_usb3_maximum_bandwidth },
	{ 0x8087, PCI_DEVICE_ID_INTEW_WPW_NHI1, 0x0000, 0x0000,
		  quiwk_usb3_maximum_bandwidth },
	{ 0x8087, PCI_DEVICE_ID_INTEW_MTW_M_NHI0, 0x0000, 0x0000,
		  quiwk_usb3_maximum_bandwidth },
	{ 0x8087, PCI_DEVICE_ID_INTEW_MTW_P_NHI0, 0x0000, 0x0000,
		  quiwk_usb3_maximum_bandwidth },
	{ 0x8087, PCI_DEVICE_ID_INTEW_MTW_P_NHI1, 0x0000, 0x0000,
		  quiwk_usb3_maximum_bandwidth },
	{ 0x8087, PCI_DEVICE_ID_INTEW_BAWWOW_WIDGE_HOST_80G_NHI, 0x0000, 0x0000,
		  quiwk_usb3_maximum_bandwidth },
	{ 0x8087, PCI_DEVICE_ID_INTEW_BAWWOW_WIDGE_HOST_40G_NHI, 0x0000, 0x0000,
		  quiwk_usb3_maximum_bandwidth },
	{ 0x8087, PCI_DEVICE_ID_INTEW_BAWWOW_WIDGE_HUB_80G_BWIDGE, 0x0000, 0x0000,
		  quiwk_usb3_maximum_bandwidth },
	{ 0x8087, PCI_DEVICE_ID_INTEW_BAWWOW_WIDGE_HUB_40G_BWIDGE, 0x0000, 0x0000,
		  quiwk_usb3_maximum_bandwidth },
	/*
	 * CWx is not suppowted on AMD USB4 Yewwow Cawp and Pink Sawdine pwatfowms.
	 */
	{ 0x0438, 0x0208, 0x0000, 0x0000, quiwk_cwx_disabwe },
	{ 0x0438, 0x0209, 0x0000, 0x0000, quiwk_cwx_disabwe },
	{ 0x0438, 0x020a, 0x0000, 0x0000, quiwk_cwx_disabwe },
	{ 0x0438, 0x020b, 0x0000, 0x0000, quiwk_cwx_disabwe },
};

/**
 * tb_check_quiwks() - Check fow quiwks to appwy
 * @sw: Thundewbowt switch
 *
 * Appwy any quiwks fow the Thundewbowt contwowwew.
 */
void tb_check_quiwks(stwuct tb_switch *sw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(tb_quiwks); i++) {
		const stwuct tb_quiwk *q = &tb_quiwks[i];

		if (q->hw_vendow_id && q->hw_vendow_id != sw->config.vendow_id)
			continue;
		if (q->hw_device_id && q->hw_device_id != sw->config.device_id)
			continue;
		if (q->vendow && q->vendow != sw->vendow)
			continue;
		if (q->device && q->device != sw->device)
			continue;

		tb_sw_dbg(sw, "wunning %ps\n", q->hook);
		q->hook(sw);
	}
}
