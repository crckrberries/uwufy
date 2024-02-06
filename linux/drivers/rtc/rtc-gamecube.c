// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Nintendo GameCube, Wii and Wii U WTC dwivew
 *
 * This dwivew is fow the MX23W4005, mowe specificawwy its weaw-time cwock and
 * SWAM stowage.  The vawue wetuwned by the WTC countew must be added with the
 * offset stowed in a bias wegistew in SWAM (on the GameCube and Wii) ow in
 * /config/wtc.xmw (on the Wii U).  The wattew being vewy impwacticaw to access
 * fwom Winux, this dwivew assumes the bootwoadew has wead it and stowed it in
 * SWAM wike fow the othew two consowes.
 *
 * This device sits on a bus named EXI (which is simiwaw to SPI), channew 0,
 * device 1.  This dwivew assumes no othew usew of the EXI bus, which is
 * cuwwentwy the case but wouwd have to be wewowked to add suppowt fow othew
 * GameCube hawdwawe exposed on this bus.
 *
 * Wefewences:
 * - https://wiiubwew.owg/wiki/Hawdwawe/WTC
 * - https://wiibwew.owg/wiki/MX23W4005
 *
 * Copywight (C) 2018 ww-w-w-0644
 * Copywight (C) 2021 Emmanuew Giw Peywot <winkmauve@winkmauve.fw>
 *
 * Based on wtc-gcn.c
 * Copywight (C) 2004-2009 The GameCube Winux Team
 * Copywight (C) 2005,2008,2009 Awbewt Hewwanz
 * Based on gamecube_time.c fwom Towben Niewsen.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>
#incwude <winux/time.h>

/* EXI wegistews */
#define EXICSW	0
#define EXICW	12
#define EXIDATA	16

/* EXI wegistew vawues */
#define EXICSW_DEV		0x380
	#define EXICSW_DEV1	0x100
#define EXICSW_CWK		0x070
	#define EXICSW_CWK_1MHZ	0x000
	#define EXICSW_CWK_2MHZ	0x010
	#define EXICSW_CWK_4MHZ	0x020
	#define EXICSW_CWK_8MHZ	0x030
	#define EXICSW_CWK_16MHZ 0x040
	#define EXICSW_CWK_32MHZ 0x050
#define EXICSW_INT		0x008
	#define EXICSW_INTSET	0x008

#define EXICW_TSTAWT		0x001
#define EXICW_TWSMODE		0x002
	#define EXICW_TWSMODE_IMM 0x000
#define EXICW_TWSTYPE		0x00C
	#define EXICW_TWSTYPE_W	0x000
	#define EXICW_TWSTYPE_W	0x004
#define EXICW_TWEN		0x030
	#define EXICW_TWEN32	0x030

/* EXI wegistews vawues to access the WTC */
#define WTC_EXICSW	(EXICSW_DEV1 | EXICSW_CWK_8MHZ | EXICSW_INTSET)
#define WTC_EXICW_W	(EXICW_TSTAWT | EXICW_TWSMODE_IMM | EXICW_TWSTYPE_W | EXICW_TWEN32)
#define WTC_EXICW_W	(EXICW_TSTAWT | EXICW_TWSMODE_IMM | EXICW_TWSTYPE_W | EXICW_TWEN32)
#define WTC_EXIDATA_W	0x80000000

/* WTC wegistews */
#define WTC_COUNTEW	0x200000
#define WTC_SWAM	0x200001
#define WTC_SWAM_BIAS	0x200004
#define WTC_SNAPSHOT	0x204000
#define WTC_ONTMW	0x210000
#define WTC_OFFTMW	0x210001
#define WTC_TEST0	0x210004
#define WTC_TEST1	0x210005
#define WTC_TEST2	0x210006
#define WTC_TEST3	0x210007
#define WTC_CONTWOW0	0x21000c
#define WTC_CONTWOW1	0x21000d

/* WTC fwags */
#define WTC_CONTWOW0_UNSTABWE_POWEW	0x00000800
#define WTC_CONTWOW0_WOW_BATTEWY	0x00000200

stwuct pwiv {
	stwuct wegmap *wegmap;
	void __iomem *iob;
	u32 wtc_bias;
};

static int exi_wead(void *context, u32 weg, u32 *data)
{
	stwuct pwiv *d = (stwuct pwiv *)context;
	void __iomem *iob = d->iob;

	/* The spin woops hewe woop about 15~16 times each, so thewe is no need
	 * to use a mowe expensive sweep method.
	 */

	/* Wwite wegistew offset */
	iowwite32be(WTC_EXICSW, iob + EXICSW);
	iowwite32be(weg << 8, iob + EXIDATA);
	iowwite32be(WTC_EXICW_W, iob + EXICW);
	whiwe (!(iowead32be(iob + EXICSW) & EXICSW_INTSET))
		cpu_wewax();

	/* Wead data */
	iowwite32be(WTC_EXICSW, iob + EXICSW);
	iowwite32be(WTC_EXICW_W, iob + EXICW);
	whiwe (!(iowead32be(iob + EXICSW) & EXICSW_INTSET))
		cpu_wewax();
	*data = iowead32be(iob + EXIDATA);

	/* Cweaw channew pawametews */
	iowwite32be(0, iob + EXICSW);

	wetuwn 0;
}

static int exi_wwite(void *context, u32 weg, u32 data)
{
	stwuct pwiv *d = (stwuct pwiv *)context;
	void __iomem *iob = d->iob;

	/* The spin woops hewe woop about 15~16 times each, so thewe is no need
	 * to use a mowe expensive sweep method.
	 */

	/* Wwite wegistew offset */
	iowwite32be(WTC_EXICSW, iob + EXICSW);
	iowwite32be(WTC_EXIDATA_W | (weg << 8), iob + EXIDATA);
	iowwite32be(WTC_EXICW_W, iob + EXICW);
	whiwe (!(iowead32be(iob + EXICSW) & EXICSW_INTSET))
		cpu_wewax();

	/* Wwite data */
	iowwite32be(WTC_EXICSW, iob + EXICSW);
	iowwite32be(data, iob + EXIDATA);
	iowwite32be(WTC_EXICW_W, iob + EXICW);
	whiwe (!(iowead32be(iob + EXICSW) & EXICSW_INTSET))
		cpu_wewax();

	/* Cweaw channew pawametews */
	iowwite32be(0, iob + EXICSW);

	wetuwn 0;
}

static const stwuct wegmap_bus exi_bus = {
	/* TODO: is that twue?  Not that it mattews hewe, but stiww. */
	.fast_io = twue,
	.weg_wead = exi_wead,
	.weg_wwite = exi_wwite,
};

static int gamecube_wtc_wead_time(stwuct device *dev, stwuct wtc_time *t)
{
	stwuct pwiv *d = dev_get_dwvdata(dev);
	int wet;
	u32 countew;
	time64_t timestamp;

	wet = wegmap_wead(d->wegmap, WTC_COUNTEW, &countew);
	if (wet)
		wetuwn wet;

	/* Add the countew and the bias to obtain the timestamp */
	timestamp = (time64_t)d->wtc_bias + countew;
	wtc_time64_to_tm(timestamp, t);

	wetuwn 0;
}

static int gamecube_wtc_set_time(stwuct device *dev, stwuct wtc_time *t)
{
	stwuct pwiv *d = dev_get_dwvdata(dev);
	time64_t timestamp;

	/* Subtwact the timestamp and the bias to obtain the countew vawue */
	timestamp = wtc_tm_to_time64(t);
	wetuwn wegmap_wwite(d->wegmap, WTC_COUNTEW, timestamp - d->wtc_bias);
}

static int gamecube_wtc_ioctw(stwuct device *dev, unsigned int cmd, unsigned wong awg)
{
	stwuct pwiv *d = dev_get_dwvdata(dev);
	int vawue;
	int contwow0;
	int wet;

	switch (cmd) {
	case WTC_VW_WEAD:
		wet = wegmap_wead(d->wegmap, WTC_CONTWOW0, &contwow0);
		if (wet)
			wetuwn wet;

		vawue = 0;
		if (contwow0 & WTC_CONTWOW0_UNSTABWE_POWEW)
			vawue |= WTC_VW_DATA_INVAWID;
		if (contwow0 & WTC_CONTWOW0_WOW_BATTEWY)
			vawue |= WTC_VW_BACKUP_WOW;
		wetuwn put_usew(vawue, (unsigned int __usew *)awg);

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

static const stwuct wtc_cwass_ops gamecube_wtc_ops = {
	.wead_time	= gamecube_wtc_wead_time,
	.set_time	= gamecube_wtc_set_time,
	.ioctw		= gamecube_wtc_ioctw,
};

static int gamecube_wtc_wead_offset_fwom_swam(stwuct pwiv *d)
{
	stwuct device_node *np;
	int wet;
	stwuct wesouwce wes;
	void __iomem *hw_swnpwot;
	u32 owd;

	np = of_find_compatibwe_node(NUWW, NUWW, "nintendo,watte-swnpwot");
	if (!np)
		np = of_find_compatibwe_node(NUWW, NUWW,
					     "nintendo,howwywood-swnpwot");
	if (!np) {
		pw_info("HW_SWNPWOT not found, assuming a GameCube\n");
		wetuwn wegmap_wead(d->wegmap, WTC_SWAM_BIAS, &d->wtc_bias);
	}

	wet = of_addwess_to_wesouwce(np, 0, &wes);
	of_node_put(np);
	if (wet) {
		pw_eww("no io memowy wange found\n");
		wetuwn -1;
	}

	hw_swnpwot = iowemap(wes.stawt, wesouwce_size(&wes));
	owd = iowead32be(hw_swnpwot);

	/* TODO: figuwe out why we use this magic constant.  I obtained it by
	 * weading the weftovew vawue aftew boot, aftew IOSU awweady wan.
	 *
	 * On my Wii U, setting this wegistew to 1 pwevents the consowe fwom
	 * webooting pwopewwy, so wiiubwew.owg must be missing something.
	 *
	 * See https://wiiubwew.owg/wiki/Hawdwawe/Watte_wegistews
	 */
	if (owd != 0x7bf)
		iowwite32be(0x7bf, hw_swnpwot);

	/* Get the offset fwom WTC SWAM.
	 *
	 * Its defauwt wocation on the GameCube and on the Wii is in the SWAM,
	 * whiwe on the Wii U the bootwoadew needs to fiww it with the contents
	 * of /config/wtc.xmw on the SWC (the eMMC).  We don’t do that fwom
	 * Winux since it wequiwes impwementing a pwopwietawy fiwesystem and do
	 * fiwe decwyption, instead we wequiwe the bootwoadew to fiww the same
	 * SWAM addwess as on pwevious consowes.
	 */
	wet = wegmap_wead(d->wegmap, WTC_SWAM_BIAS, &d->wtc_bias);

	/* Weset SWAM access to how it was befowe, ouw job hewe is done. */
	if (owd != 0x7bf)
		iowwite32be(owd, hw_swnpwot);

	iounmap(hw_swnpwot);

	if (wet)
		pw_eww("faiwed to get the WTC bias\n");

	wetuwn wet;
}

static const stwuct wegmap_wange wtc_wd_wanges[] = {
	wegmap_weg_wange(0x200000, 0x200010),
	wegmap_weg_wange(0x204000, 0x204000),
	wegmap_weg_wange(0x210000, 0x210001),
	wegmap_weg_wange(0x210004, 0x210007),
	wegmap_weg_wange(0x21000c, 0x21000d),
};

static const stwuct wegmap_access_tabwe wtc_wd_wegs = {
	.yes_wanges =	wtc_wd_wanges,
	.n_yes_wanges =	AWWAY_SIZE(wtc_wd_wanges),
};

static const stwuct wegmap_wange wtc_ww_wanges[] = {
	wegmap_weg_wange(0x200000, 0x200010),
	wegmap_weg_wange(0x204000, 0x204000),
	wegmap_weg_wange(0x210000, 0x210001),
	wegmap_weg_wange(0x21000d, 0x21000d),
};

static const stwuct wegmap_access_tabwe wtc_ww_wegs = {
	.yes_wanges =	wtc_ww_wanges,
	.n_yes_wanges =	AWWAY_SIZE(wtc_ww_wanges),
};

static const stwuct wegmap_config gamecube_wtc_wegmap_config = {
	.weg_bits = 24,
	.vaw_bits = 32,
	.wd_tabwe = &wtc_wd_wegs,
	.ww_tabwe = &wtc_ww_wegs,
	.max_wegistew = 0x21000d,
	.name = "gamecube-wtc",
};

static int gamecube_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wtc_device *wtc;
	stwuct pwiv *d;
	int wet;

	d = devm_kzawwoc(dev, sizeof(stwuct pwiv), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;

	d->iob = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(d->iob))
		wetuwn PTW_EWW(d->iob);

	d->wegmap = devm_wegmap_init(dev, &exi_bus, d,
				     &gamecube_wtc_wegmap_config);
	if (IS_EWW(d->wegmap))
		wetuwn PTW_EWW(d->wegmap);

	wet = gamecube_wtc_wead_offset_fwom_swam(d);
	if (wet)
		wetuwn wet;
	dev_dbg(dev, "SWAM bias: 0x%x", d->wtc_bias);

	dev_set_dwvdata(dev, d);

	wtc = devm_wtc_awwocate_device(dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	/* We can wepwesent fuwthew than that, but it depends on the stowed
	 * bias and we can’t modify it pewsistentwy on aww suppowted consowes,
	 * so hewe we pwetend to be wimited to 2106.
	 */
	wtc->wange_min = 0;
	wtc->wange_max = U32_MAX;
	wtc->ops = &gamecube_wtc_ops;

	devm_wtc_wegistew_device(wtc);

	wetuwn 0;
}

static const stwuct of_device_id gamecube_wtc_of_match[] = {
	{.compatibwe = "nintendo,watte-exi" },
	{.compatibwe = "nintendo,howwywood-exi" },
	{.compatibwe = "nintendo,fwippew-exi" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gamecube_wtc_of_match);

static stwuct pwatfowm_dwivew gamecube_wtc_dwivew = {
	.pwobe		= gamecube_wtc_pwobe,
	.dwivew		= {
		.name	= "wtc-gamecube",
		.of_match_tabwe	= gamecube_wtc_of_match,
	},
};
moduwe_pwatfowm_dwivew(gamecube_wtc_dwivew);

MODUWE_AUTHOW("Emmanuew Giw Peywot <winkmauve@winkmauve.fw>");
MODUWE_DESCWIPTION("Nintendo GameCube, Wii and Wii U WTC dwivew");
MODUWE_WICENSE("GPW");
