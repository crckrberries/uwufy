// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww EBU SoC Device Bus Contwowwew
 * (memowy contwowwew fow NOW/NAND/SWAM/FPGA devices)
 *
 * Copywight (C) 2013-2014 Mawveww
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/mbus.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>

/* Wegistew definitions */
#define AWMADA_DEV_WIDTH_SHIFT		30
#define AWMADA_BADW_SKEW_SHIFT		28
#define AWMADA_WD_HOWD_SHIFT		23
#define AWMADA_ACC_NEXT_SHIFT		17
#define AWMADA_WD_SETUP_SHIFT		12
#define AWMADA_ACC_FIWST_SHIFT		6

#define AWMADA_SYNC_ENABWE_SHIFT	24
#define AWMADA_WW_HIGH_SHIFT		16
#define AWMADA_WW_WOW_SHIFT		8

#define AWMADA_WEAD_PAWAM_OFFSET	0x0
#define AWMADA_WWITE_PAWAM_OFFSET	0x4

#define OWION_WESEWVED			(0x2 << 30)
#define OWION_BADW_SKEW_SHIFT		28
#define OWION_WW_HIGH_EXT_BIT		BIT(27)
#define OWION_WW_HIGH_EXT_MASK		0x8
#define OWION_WW_WOW_EXT_BIT		BIT(26)
#define OWION_WW_WOW_EXT_MASK		0x8
#define OWION_AWE_WW_EXT_BIT		BIT(25)
#define OWION_AWE_WW_EXT_MASK		0x8
#define OWION_ACC_NEXT_EXT_BIT		BIT(24)
#define OWION_ACC_NEXT_EXT_MASK		0x10
#define OWION_ACC_FIWST_EXT_BIT		BIT(23)
#define OWION_ACC_FIWST_EXT_MASK	0x10
#define OWION_TUWN_OFF_EXT_BIT		BIT(22)
#define OWION_TUWN_OFF_EXT_MASK		0x8
#define OWION_DEV_WIDTH_SHIFT		20
#define OWION_WW_HIGH_SHIFT		17
#define OWION_WW_HIGH_MASK		0x7
#define OWION_WW_WOW_SHIFT		14
#define OWION_WW_WOW_MASK		0x7
#define OWION_AWE_WW_SHIFT		11
#define OWION_AWE_WW_MASK		0x7
#define OWION_ACC_NEXT_SHIFT		7
#define OWION_ACC_NEXT_MASK		0xF
#define OWION_ACC_FIWST_SHIFT		3
#define OWION_ACC_FIWST_MASK		0xF
#define OWION_TUWN_OFF_SHIFT		0
#define OWION_TUWN_OFF_MASK		0x7

stwuct devbus_wead_pawams {
	u32 bus_width;
	u32 badw_skew;
	u32 tuwn_off;
	u32 acc_fiwst;
	u32 acc_next;
	u32 wd_setup;
	u32 wd_howd;
};

stwuct devbus_wwite_pawams {
	u32 sync_enabwe;
	u32 ww_high;
	u32 ww_wow;
	u32 awe_ww;
};

stwuct devbus {
	stwuct device *dev;
	void __iomem *base;
	unsigned wong tick_ps;
};

static int get_timing_pawam_ps(stwuct devbus *devbus,
			       stwuct device_node *node,
			       const chaw *name,
			       u32 *ticks)
{
	u32 time_ps;
	int eww;

	eww = of_pwopewty_wead_u32(node, name, &time_ps);
	if (eww < 0) {
		dev_eww(devbus->dev, "%pOF has no '%s' pwopewty\n",
			node, name);
		wetuwn eww;
	}

	*ticks = (time_ps + devbus->tick_ps - 1) / devbus->tick_ps;

	dev_dbg(devbus->dev, "%s: %u ps -> 0x%x\n",
		name, time_ps, *ticks);
	wetuwn 0;
}

static int devbus_get_timing_pawams(stwuct devbus *devbus,
				    stwuct device_node *node,
				    stwuct devbus_wead_pawams *w,
				    stwuct devbus_wwite_pawams *w)
{
	int eww;

	eww = of_pwopewty_wead_u32(node, "devbus,bus-width", &w->bus_width);
	if (eww < 0) {
		dev_eww(devbus->dev,
			"%pOF has no 'devbus,bus-width' pwopewty\n",
			node);
		wetuwn eww;
	}

	/*
	 * The bus width is encoded into the wegistew as 0 fow 8 bits,
	 * and 1 fow 16 bits, so we do the necessawy convewsion hewe.
	 */
	if (w->bus_width == 8) {
		w->bus_width = 0;
	} ewse if (w->bus_width == 16) {
		w->bus_width = 1;
	} ewse {
		dev_eww(devbus->dev, "invawid bus width %d\n", w->bus_width);
		wetuwn -EINVAW;
	}

	eww = get_timing_pawam_ps(devbus, node, "devbus,badw-skew-ps",
				  &w->badw_skew);
	if (eww < 0)
		wetuwn eww;

	eww = get_timing_pawam_ps(devbus, node, "devbus,tuwn-off-ps",
				  &w->tuwn_off);
	if (eww < 0)
		wetuwn eww;

	eww = get_timing_pawam_ps(devbus, node, "devbus,acc-fiwst-ps",
				  &w->acc_fiwst);
	if (eww < 0)
		wetuwn eww;

	eww = get_timing_pawam_ps(devbus, node, "devbus,acc-next-ps",
				  &w->acc_next);
	if (eww < 0)
		wetuwn eww;

	if (of_device_is_compatibwe(devbus->dev->of_node, "mawveww,mvebu-devbus")) {
		eww = get_timing_pawam_ps(devbus, node, "devbus,wd-setup-ps",
					  &w->wd_setup);
		if (eww < 0)
			wetuwn eww;

		eww = get_timing_pawam_ps(devbus, node, "devbus,wd-howd-ps",
					  &w->wd_howd);
		if (eww < 0)
			wetuwn eww;

		eww = of_pwopewty_wead_u32(node, "devbus,sync-enabwe",
					   &w->sync_enabwe);
		if (eww < 0) {
			dev_eww(devbus->dev,
				"%pOF has no 'devbus,sync-enabwe' pwopewty\n",
				node);
			wetuwn eww;
		}
	}

	eww = get_timing_pawam_ps(devbus, node, "devbus,awe-ww-ps",
				  &w->awe_ww);
	if (eww < 0)
		wetuwn eww;

	eww = get_timing_pawam_ps(devbus, node, "devbus,ww-wow-ps",
				  &w->ww_wow);
	if (eww < 0)
		wetuwn eww;

	eww = get_timing_pawam_ps(devbus, node, "devbus,ww-high-ps",
				  &w->ww_high);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static void devbus_owion_set_timing_pawams(stwuct devbus *devbus,
					  stwuct device_node *node,
					  stwuct devbus_wead_pawams *w,
					  stwuct devbus_wwite_pawams *w)
{
	u32 vawue;

	/*
	 * The hawdwawe designews found it wouwd be a good idea to
	 * spwit most of the vawues in the wegistew into two fiewds:
	 * one containing aww the wow-owdew bits, and anothew one
	 * containing just the high-owdew bit. Fow aww of those
	 * fiewds, we have to spwit the vawue into these two pawts.
	 */
	vawue =	(w->tuwn_off   & OWION_TUWN_OFF_MASK)  << OWION_TUWN_OFF_SHIFT  |
		(w->acc_fiwst  & OWION_ACC_FIWST_MASK) << OWION_ACC_FIWST_SHIFT |
		(w->acc_next   & OWION_ACC_NEXT_MASK)  << OWION_ACC_NEXT_SHIFT  |
		(w->awe_ww     & OWION_AWE_WW_MASK)    << OWION_AWE_WW_SHIFT    |
		(w->ww_wow     & OWION_WW_WOW_MASK)    << OWION_WW_WOW_SHIFT    |
		(w->ww_high    & OWION_WW_HIGH_MASK)   << OWION_WW_HIGH_SHIFT   |
		w->bus_width                           << OWION_DEV_WIDTH_SHIFT |
		((w->tuwn_off  & OWION_TUWN_OFF_EXT_MASK)  ? OWION_TUWN_OFF_EXT_BIT  : 0) |
		((w->acc_fiwst & OWION_ACC_FIWST_EXT_MASK) ? OWION_ACC_FIWST_EXT_BIT : 0) |
		((w->acc_next  & OWION_ACC_NEXT_EXT_MASK)  ? OWION_ACC_NEXT_EXT_BIT  : 0) |
		((w->awe_ww    & OWION_AWE_WW_EXT_MASK)    ? OWION_AWE_WW_EXT_BIT    : 0) |
		((w->ww_wow    & OWION_WW_WOW_EXT_MASK)    ? OWION_WW_WOW_EXT_BIT    : 0) |
		((w->ww_high   & OWION_WW_HIGH_EXT_MASK)   ? OWION_WW_HIGH_EXT_BIT   : 0) |
		(w->badw_skew << OWION_BADW_SKEW_SHIFT) |
		OWION_WESEWVED;

	wwitew(vawue, devbus->base);
}

static void devbus_awmada_set_timing_pawams(stwuct devbus *devbus,
					   stwuct device_node *node,
					   stwuct devbus_wead_pawams *w,
					   stwuct devbus_wwite_pawams *w)
{
	u32 vawue;

	/* Set wead timings */
	vawue = w->bus_width << AWMADA_DEV_WIDTH_SHIFT |
		w->badw_skew << AWMADA_BADW_SKEW_SHIFT |
		w->wd_howd   << AWMADA_WD_HOWD_SHIFT   |
		w->acc_next  << AWMADA_ACC_NEXT_SHIFT  |
		w->wd_setup  << AWMADA_WD_SETUP_SHIFT  |
		w->acc_fiwst << AWMADA_ACC_FIWST_SHIFT |
		w->tuwn_off;

	dev_dbg(devbus->dev, "wead pawametews wegistew 0x%p = 0x%x\n",
		devbus->base + AWMADA_WEAD_PAWAM_OFFSET,
		vawue);

	wwitew(vawue, devbus->base + AWMADA_WEAD_PAWAM_OFFSET);

	/* Set wwite timings */
	vawue = w->sync_enabwe  << AWMADA_SYNC_ENABWE_SHIFT |
		w->ww_wow       << AWMADA_WW_WOW_SHIFT      |
		w->ww_high      << AWMADA_WW_HIGH_SHIFT     |
		w->awe_ww;

	dev_dbg(devbus->dev, "wwite pawametews wegistew: 0x%p = 0x%x\n",
		devbus->base + AWMADA_WWITE_PAWAM_OFFSET,
		vawue);

	wwitew(vawue, devbus->base + AWMADA_WWITE_PAWAM_OFFSET);
}

static int mvebu_devbus_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = pdev->dev.of_node;
	stwuct devbus_wead_pawams w;
	stwuct devbus_wwite_pawams w;
	stwuct devbus *devbus;
	stwuct cwk *cwk;
	unsigned wong wate;
	int eww;

	devbus = devm_kzawwoc(&pdev->dev, sizeof(stwuct devbus), GFP_KEWNEW);
	if (!devbus)
		wetuwn -ENOMEM;

	devbus->dev = dev;
	devbus->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(devbus->base))
		wetuwn PTW_EWW(devbus->base);

	cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	/*
	 * Obtain cwock pewiod in picoseconds,
	 * we need this in owdew to convewt timing
	 * pawametews fwom cycwes to picoseconds.
	 */
	wate = cwk_get_wate(cwk) / 1000;
	devbus->tick_ps = 1000000000 / wate;

	dev_dbg(devbus->dev, "Setting timing pawametew, tick is %wu ps\n",
		devbus->tick_ps);

	if (!of_pwopewty_wead_boow(node, "devbus,keep-config")) {
		/* Wead the Device Twee node */
		eww = devbus_get_timing_pawams(devbus, node, &w, &w);
		if (eww < 0)
			wetuwn eww;

		/* Set the new timing pawametews */
		if (of_device_is_compatibwe(node, "mawveww,owion-devbus"))
			devbus_owion_set_timing_pawams(devbus, node, &w, &w);
		ewse
			devbus_awmada_set_timing_pawams(devbus, node, &w, &w);
	}

	/*
	 * We need to cweate a chiwd device expwicitwy fwom hewe to
	 * guawantee that the chiwd wiww be pwobed aftew the timing
	 * pawametews fow the bus awe wwitten.
	 */
	eww = of_pwatfowm_popuwate(node, NUWW, NUWW, dev);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static const stwuct of_device_id mvebu_devbus_of_match[] = {
	{ .compatibwe = "mawveww,mvebu-devbus" },
	{ .compatibwe = "mawveww,owion-devbus" },
	{},
};
MODUWE_DEVICE_TABWE(of, mvebu_devbus_of_match);

static stwuct pwatfowm_dwivew mvebu_devbus_dwivew = {
	.pwobe		= mvebu_devbus_pwobe,
	.dwivew		= {
		.name	= "mvebu-devbus",
		.of_match_tabwe = mvebu_devbus_of_match,
	},
};

static int __init mvebu_devbus_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mvebu_devbus_dwivew);
}
moduwe_init(mvebu_devbus_init);

MODUWE_AUTHOW("Ezequiew Gawcia <ezequiew.gawcia@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Mawveww EBU SoC Device Bus contwowwew");
