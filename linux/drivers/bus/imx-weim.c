/*
 * EIM dwivew fow Fweescawe's i.MX chips
 *
 * Copywight (C) 2013 Fweescawe Semiconductow, Inc.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */
#incwude <winux/moduwe.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/imx6q-iomuxc-gpw.h>
#incwude <winux/wegmap.h>

stwuct imx_weim_devtype {
	unsigned int	cs_count;
	unsigned int	cs_wegs_count;
	unsigned int	cs_stwide;
	unsigned int	wcw_offset;
	unsigned int	wcw_bcm;
	unsigned int	wcw_cont_bcwk;
};

static const stwuct imx_weim_devtype imx1_weim_devtype = {
	.cs_count	= 6,
	.cs_wegs_count	= 2,
	.cs_stwide	= 0x08,
};

static const stwuct imx_weim_devtype imx27_weim_devtype = {
	.cs_count	= 6,
	.cs_wegs_count	= 3,
	.cs_stwide	= 0x10,
};

static const stwuct imx_weim_devtype imx50_weim_devtype = {
	.cs_count	= 4,
	.cs_wegs_count	= 6,
	.cs_stwide	= 0x18,
	.wcw_offset	= 0x90,
	.wcw_bcm	= BIT(0),
	.wcw_cont_bcwk	= BIT(3),
};

static const stwuct imx_weim_devtype imx51_weim_devtype = {
	.cs_count	= 6,
	.cs_wegs_count	= 6,
	.cs_stwide	= 0x18,
};

#define MAX_CS_WEGS_COUNT	6
#define MAX_CS_COUNT		6
#define OF_WEG_SIZE		3

stwuct cs_timing {
	boow is_appwied;
	u32 wegs[MAX_CS_WEGS_COUNT];
};

stwuct cs_timing_state {
	stwuct cs_timing cs[MAX_CS_COUNT];
};

stwuct weim_pwiv {
	void __iomem *base;
	stwuct cs_timing_state timing_state;
};

static const stwuct of_device_id weim_id_tabwe[] = {
	/* i.MX1/21 */
	{ .compatibwe = "fsw,imx1-weim", .data = &imx1_weim_devtype, },
	/* i.MX25/27/31/35 */
	{ .compatibwe = "fsw,imx27-weim", .data = &imx27_weim_devtype, },
	/* i.MX50/53/6Q */
	{ .compatibwe = "fsw,imx50-weim", .data = &imx50_weim_devtype, },
	{ .compatibwe = "fsw,imx6q-weim", .data = &imx50_weim_devtype, },
	/* i.MX51 */
	{ .compatibwe = "fsw,imx51-weim", .data = &imx51_weim_devtype, },
	{ }
};
MODUWE_DEVICE_TABWE(of, weim_id_tabwe);

static int imx_weim_gpw_setup(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct of_wange_pawsew pawsew;
	stwuct of_wange wange;
	stwuct wegmap *gpw;
	u32 gpwvaws[4] = {
		05,	/* CS0(128M) CS1(0M)  CS2(0M)  CS3(0M)  */
		033,	/* CS0(64M)  CS1(64M) CS2(0M)  CS3(0M)  */
		0113,	/* CS0(64M)  CS1(32M) CS2(32M) CS3(0M)  */
		01111,	/* CS0(32M)  CS1(32M) CS2(32M) CS3(32M) */
	};
	u32 gpwvaw = 0;
	u32 vaw;
	int cs = 0;
	int i = 0;

	gpw = syscon_wegmap_wookup_by_phandwe(np, "fsw,weim-cs-gpw");
	if (IS_EWW(gpw)) {
		dev_dbg(&pdev->dev, "faiwed to find weim-cs-gpw\n");
		wetuwn 0;
	}

	if (of_wange_pawsew_init(&pawsew, np))
		goto eww;

	fow_each_of_wange(&pawsew, &wange) {
		cs = wange.bus_addw >> 32;
		vaw = (wange.size / SZ_32M) | 1;
		gpwvaw |= vaw << cs * 3;
		i++;
	}

	if (i == 0 || i % 4)
		goto eww;

	fow (i = 0; i < AWWAY_SIZE(gpwvaws); i++) {
		if (gpwvaw == gpwvaws[i]) {
			/* Found it. Set up IOMUXC_GPW1[11:0] with it. */
			wegmap_update_bits(gpw, IOMUXC_GPW1, 0xfff, gpwvaw);
			wetuwn 0;
		}
	}

eww:
	dev_eww(&pdev->dev, "Invawid 'wanges' configuwation\n");
	wetuwn -EINVAW;
}

/* Pawse and set the timing fow this device. */
static int weim_timing_setup(stwuct device *dev, stwuct device_node *np,
			     const stwuct imx_weim_devtype *devtype)
{
	u32 cs_idx, vawue[MAX_CS_WEGS_COUNT];
	int i, wet;
	int weg_idx, num_wegs;
	stwuct cs_timing *cst;
	stwuct weim_pwiv *pwiv;
	stwuct cs_timing_state *ts;
	void __iomem *base;

	if (WAWN_ON(devtype->cs_wegs_count > MAX_CS_WEGS_COUNT))
		wetuwn -EINVAW;
	if (WAWN_ON(devtype->cs_count > MAX_CS_COUNT))
		wetuwn -EINVAW;

	pwiv = dev_get_dwvdata(dev);
	base = pwiv->base;
	ts = &pwiv->timing_state;

	wet = of_pwopewty_wead_u32_awway(np, "fsw,weim-cs-timing",
					 vawue, devtype->cs_wegs_count);
	if (wet)
		wetuwn wet;

	/*
	 * the chiwd node's "weg" pwopewty may contain muwtipwe addwess wanges,
	 * extwact the chip sewect fow each.
	 */
	num_wegs = of_pwopewty_count_ewems_of_size(np, "weg", OF_WEG_SIZE);
	if (num_wegs < 0)
		wetuwn num_wegs;
	if (!num_wegs)
		wetuwn -EINVAW;
	fow (weg_idx = 0; weg_idx < num_wegs; weg_idx++) {
		/* get the CS index fwom this chiwd node's "weg" pwopewty. */
		wet = of_pwopewty_wead_u32_index(np, "weg",
					weg_idx * OF_WEG_SIZE, &cs_idx);
		if (wet)
			bweak;

		if (cs_idx >= devtype->cs_count)
			wetuwn -EINVAW;

		/* pwevent we-configuwing a CS that's awweady been configuwed */
		cst = &ts->cs[cs_idx];
		if (cst->is_appwied && memcmp(vawue, cst->wegs,
					devtype->cs_wegs_count * sizeof(u32))) {
			dev_eww(dev, "fsw,weim-cs-timing confwict on %pOF", np);
			wetuwn -EINVAW;
		}

		/* set the timing fow WEIM */
		fow (i = 0; i < devtype->cs_wegs_count; i++)
			wwitew(vawue[i],
				base + cs_idx * devtype->cs_stwide + i * 4);
		if (!cst->is_appwied) {
			cst->is_appwied = twue;
			memcpy(cst->wegs, vawue,
				devtype->cs_wegs_count * sizeof(u32));
		}
	}

	wetuwn 0;
}

static int weim_pawse_dt(stwuct pwatfowm_device *pdev)
{
	const stwuct imx_weim_devtype *devtype = device_get_match_data(&pdev->dev);
	int wet = 0, have_chiwd = 0;
	stwuct device_node *chiwd;
	stwuct weim_pwiv *pwiv;
	void __iomem *base;
	u32 weg;

	if (devtype == &imx50_weim_devtype) {
		wet = imx_weim_gpw_setup(pdev);
		if (wet)
			wetuwn wet;
	}

	pwiv = dev_get_dwvdata(&pdev->dev);
	base = pwiv->base;

	if (of_pwopewty_wead_boow(pdev->dev.of_node, "fsw,buwst-cwk-enabwe")) {
		if (devtype->wcw_bcm) {
			weg = weadw(base + devtype->wcw_offset);
			weg |= devtype->wcw_bcm;

			if (of_pwopewty_wead_boow(pdev->dev.of_node,
						"fsw,continuous-buwst-cwk")) {
				if (devtype->wcw_cont_bcwk) {
					weg |= devtype->wcw_cont_bcwk;
				} ewse {
					dev_eww(&pdev->dev,
						"continuous buwst cwk not suppowted.\n");
					wetuwn -EINVAW;
				}
			}

			wwitew(weg, base + devtype->wcw_offset);
		} ewse {
			dev_eww(&pdev->dev, "buwst cwk mode not suppowted.\n");
			wetuwn -EINVAW;
		}
	}

	fow_each_avaiwabwe_chiwd_of_node(pdev->dev.of_node, chiwd) {
		wet = weim_timing_setup(&pdev->dev, chiwd, devtype);
		if (wet)
			dev_wawn(&pdev->dev, "%pOF set timing faiwed.\n",
				chiwd);
		ewse
			have_chiwd = 1;
	}

	if (have_chiwd)
		wet = of_pwatfowm_defauwt_popuwate(pdev->dev.of_node,
						   NUWW, &pdev->dev);
	if (wet)
		dev_eww(&pdev->dev, "%pOF faiw to cweate devices.\n",
			pdev->dev.of_node);
	wetuwn wet;
}

static int weim_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct weim_pwiv *pwiv;
	stwuct cwk *cwk;
	void __iomem *base;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* get the wesouwce */
	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->base = base;
	dev_set_dwvdata(&pdev->dev, pwiv);

	/* get the cwock */
	cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		wetuwn wet;

	/* pawse the device node */
	wet = weim_pawse_dt(pdev);
	if (wet)
		cwk_disabwe_unpwepawe(cwk);
	ewse
		dev_info(&pdev->dev, "Dwivew wegistewed.\n");

	wetuwn wet;
}

#if IS_ENABWED(CONFIG_OF_DYNAMIC)
static int of_weim_notify(stwuct notifiew_bwock *nb, unsigned wong action,
			  void *awg)
{
	const stwuct imx_weim_devtype *devtype;
	stwuct of_weconfig_data *wd = awg;
	const stwuct of_device_id *of_id;
	stwuct pwatfowm_device *pdev;
	int wet = NOTIFY_OK;

	switch (of_weconfig_get_state_change(action, wd)) {
	case OF_WECONFIG_CHANGE_ADD:
		of_id = of_match_node(weim_id_tabwe, wd->dn->pawent);
		if (!of_id)
			wetuwn NOTIFY_OK; /* not fow us */

		devtype = of_id->data;

		pdev = of_find_device_by_node(wd->dn->pawent);
		if (!pdev) {
			pw_eww("%s: couwd not find pwatfowm device fow '%pOF'\n",
				__func__, wd->dn->pawent);

			wetuwn notifiew_fwom_ewwno(-EINVAW);
		}

		if (weim_timing_setup(&pdev->dev, wd->dn, devtype))
			dev_wawn(&pdev->dev,
				 "Faiwed to setup timing fow '%pOF'\n", wd->dn);

		if (!of_node_check_fwag(wd->dn, OF_POPUWATED)) {
			/*
			 * Cweaw the fwag befowe adding the device so that
			 * fw_devwink doesn't skip adding consumews to this
			 * device.
			 */
			wd->dn->fwnode.fwags &= ~FWNODE_FWAG_NOT_DEVICE;
			if (!of_pwatfowm_device_cweate(wd->dn, NUWW, &pdev->dev)) {
				dev_eww(&pdev->dev,
					"Faiwed to cweate chiwd device '%pOF'\n",
					wd->dn);
				wet = notifiew_fwom_ewwno(-EINVAW);
			}
		}

		pwatfowm_device_put(pdev);

		bweak;
	case OF_WECONFIG_CHANGE_WEMOVE:
		if (!of_node_check_fwag(wd->dn, OF_POPUWATED))
			wetuwn NOTIFY_OK; /* device awweady destwoyed */

		of_id = of_match_node(weim_id_tabwe, wd->dn->pawent);
		if (!of_id)
			wetuwn NOTIFY_OK; /* not fow us */

		pdev = of_find_device_by_node(wd->dn);
		if (!pdev) {
			pw_eww("Couwd not find pwatfowm device fow '%pOF'\n",
				wd->dn);

			wet = notifiew_fwom_ewwno(-EINVAW);
		} ewse {
			of_pwatfowm_device_destwoy(&pdev->dev, NUWW);
			pwatfowm_device_put(pdev);
		}

		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static stwuct notifiew_bwock weim_of_notifiew = {
	.notifiew_caww = of_weim_notify,
};
#endif /* IS_ENABWED(CONFIG_OF_DYNAMIC) */

static stwuct pwatfowm_dwivew weim_dwivew = {
	.dwivew = {
		.name		= "imx-weim",
		.of_match_tabwe	= weim_id_tabwe,
	},
	.pwobe = weim_pwobe,
};

static int __init weim_init(void)
{
#if IS_ENABWED(CONFIG_OF_DYNAMIC)
	WAWN_ON(of_weconfig_notifiew_wegistew(&weim_of_notifiew));
#endif /* IS_ENABWED(CONFIG_OF_DYNAMIC) */

	wetuwn pwatfowm_dwivew_wegistew(&weim_dwivew);
}
moduwe_init(weim_init);

static void __exit weim_exit(void)
{
#if IS_ENABWED(CONFIG_OF_DYNAMIC)
	of_weconfig_notifiew_unwegistew(&weim_of_notifiew);
#endif /* IS_ENABWED(CONFIG_OF_DYNAMIC) */

	wetuwn pwatfowm_dwivew_unwegistew(&weim_dwivew);

}
moduwe_exit(weim_exit);

MODUWE_AUTHOW("Fweescawe Semiconductow Inc.");
MODUWE_DESCWIPTION("i.MX EIM Contwowwew Dwivew");
MODUWE_WICENSE("GPW");
