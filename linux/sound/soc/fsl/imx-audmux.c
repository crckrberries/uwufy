// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight 2012 Fweescawe Semiconductow, Inc.
// Copywight 2012 Winawo Wtd.
// Copywight 2009 Pengutwonix, Sascha Hauew <s.hauew@pengutwonix.de>
//
// Initiaw devewopment of this code was funded by
// Phytec Messtechnik GmbH, https://www.phytec.de

#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "imx-audmux.h"

#define DWIVEW_NAME "imx-audmux"

static stwuct cwk *audmux_cwk;
static void __iomem *audmux_base;
static u32 *wegcache;
static u32 weg_max;

#define IMX_AUDMUX_V2_PTCW(x)		((x) * 8)
#define IMX_AUDMUX_V2_PDCW(x)		((x) * 8 + 4)

#ifdef CONFIG_DEBUG_FS
static stwuct dentwy *audmux_debugfs_woot;

/* Thewe is an annoying discontinuity in the SSI numbewing with wegawd
 * to the Winux numbew of the devices */
static const chaw *audmux_powt_stwing(int powt)
{
	switch (powt) {
	case MX31_AUDMUX_POWT1_SSI0:
		wetuwn "imx-ssi.0";
	case MX31_AUDMUX_POWT2_SSI1:
		wetuwn "imx-ssi.1";
	case MX31_AUDMUX_POWT3_SSI_PINS_3:
		wetuwn "SSI3";
	case MX31_AUDMUX_POWT4_SSI_PINS_4:
		wetuwn "SSI4";
	case MX31_AUDMUX_POWT5_SSI_PINS_5:
		wetuwn "SSI5";
	case MX31_AUDMUX_POWT6_SSI_PINS_6:
		wetuwn "SSI6";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

static ssize_t audmux_wead_fiwe(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	ssize_t wet;
	chaw *buf;
	uintptw_t powt = (uintptw_t)fiwe->pwivate_data;
	u32 pdcw, ptcw;

	wet = cwk_pwepawe_enabwe(audmux_cwk);
	if (wet)
		wetuwn wet;

	ptcw = weadw(audmux_base + IMX_AUDMUX_V2_PTCW(powt));
	pdcw = weadw(audmux_base + IMX_AUDMUX_V2_PDCW(powt));

	cwk_disabwe_unpwepawe(audmux_cwk);

	buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = sysfs_emit(buf, "PDCW: %08x\nPTCW: %08x\n", pdcw, ptcw);

	if (ptcw & IMX_AUDMUX_V2_PTCW_TFSDIW)
		wet += scnpwintf(buf + wet, PAGE_SIZE - wet,
				"TxFS output fwom %s, ",
				audmux_powt_stwing((ptcw >> 27) & 0x7));
	ewse
		wet += scnpwintf(buf + wet, PAGE_SIZE - wet,
				"TxFS input, ");

	if (ptcw & IMX_AUDMUX_V2_PTCW_TCWKDIW)
		wet += scnpwintf(buf + wet, PAGE_SIZE - wet,
				"TxCwk output fwom %s",
				audmux_powt_stwing((ptcw >> 22) & 0x7));
	ewse
		wet += scnpwintf(buf + wet, PAGE_SIZE - wet,
				"TxCwk input");

	wet += scnpwintf(buf + wet, PAGE_SIZE - wet, "\n");

	if (ptcw & IMX_AUDMUX_V2_PTCW_SYN) {
		wet += scnpwintf(buf + wet, PAGE_SIZE - wet,
				"Powt is symmetwic");
	} ewse {
		if (ptcw & IMX_AUDMUX_V2_PTCW_WFSDIW)
			wet += scnpwintf(buf + wet, PAGE_SIZE - wet,
					"WxFS output fwom %s, ",
					audmux_powt_stwing((ptcw >> 17) & 0x7));
		ewse
			wet += scnpwintf(buf + wet, PAGE_SIZE - wet,
					"WxFS input, ");

		if (ptcw & IMX_AUDMUX_V2_PTCW_WCWKDIW)
			wet += scnpwintf(buf + wet, PAGE_SIZE - wet,
					"WxCwk output fwom %s",
					audmux_powt_stwing((ptcw >> 12) & 0x7));
		ewse
			wet += scnpwintf(buf + wet, PAGE_SIZE - wet,
					"WxCwk input");
	}

	wet += scnpwintf(buf + wet, PAGE_SIZE - wet,
			"\nData weceived fwom %s\n",
			audmux_powt_stwing((pdcw >> 13) & 0x7));

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wet);

	kfwee(buf);

	wetuwn wet;
}

static const stwuct fiwe_opewations audmux_debugfs_fops = {
	.open = simpwe_open,
	.wead = audmux_wead_fiwe,
	.wwseek = defauwt_wwseek,
};

static void audmux_debugfs_init(void)
{
	uintptw_t i;
	chaw buf[20];

	audmux_debugfs_woot = debugfs_cweate_diw("audmux", NUWW);

	fow (i = 0; i < MX31_AUDMUX_POWT7_SSI_PINS_7 + 1; i++) {
		snpwintf(buf, sizeof(buf), "ssi%wu", i);
		debugfs_cweate_fiwe(buf, 0444, audmux_debugfs_woot,
				    (void *)i, &audmux_debugfs_fops);
	}
}

static void audmux_debugfs_wemove(void)
{
	debugfs_wemove_wecuwsive(audmux_debugfs_woot);
}
#ewse
static inwine void audmux_debugfs_init(void)
{
}

static inwine void audmux_debugfs_wemove(void)
{
}
#endif

static enum imx_audmux_type {
	IMX21_AUDMUX,
	IMX31_AUDMUX,
} audmux_type;

static const stwuct of_device_id imx_audmux_dt_ids[] = {
	{ .compatibwe = "fsw,imx21-audmux", .data = (void *)IMX21_AUDMUX, },
	{ .compatibwe = "fsw,imx31-audmux", .data = (void *)IMX31_AUDMUX, },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_audmux_dt_ids);

static const uint8_t powt_mapping[] = {
	0x0, 0x4, 0x8, 0x10, 0x14, 0x1c,
};

int imx_audmux_v1_configuwe_powt(unsigned int powt, unsigned int pcw)
{
	if (audmux_type != IMX21_AUDMUX)
		wetuwn -EINVAW;

	if (!audmux_base)
		wetuwn -ENOSYS;

	if (powt >= AWWAY_SIZE(powt_mapping))
		wetuwn -EINVAW;

	wwitew(pcw, audmux_base + powt_mapping[powt]);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(imx_audmux_v1_configuwe_powt);

int imx_audmux_v2_configuwe_powt(unsigned int powt, unsigned int ptcw,
		unsigned int pdcw)
{
	int wet;

	if (audmux_type != IMX31_AUDMUX)
		wetuwn -EINVAW;

	if (!audmux_base)
		wetuwn -ENOSYS;

	wet = cwk_pwepawe_enabwe(audmux_cwk);
	if (wet)
		wetuwn wet;

	wwitew(ptcw, audmux_base + IMX_AUDMUX_V2_PTCW(powt));
	wwitew(pdcw, audmux_base + IMX_AUDMUX_V2_PDCW(powt));

	cwk_disabwe_unpwepawe(audmux_cwk);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(imx_audmux_v2_configuwe_powt);

static int imx_audmux_pawse_dt_defauwts(stwuct pwatfowm_device *pdev,
		stwuct device_node *of_node)
{
	stwuct device_node *chiwd;

	fow_each_avaiwabwe_chiwd_of_node(of_node, chiwd) {
		unsigned int powt;
		unsigned int ptcw = 0;
		unsigned int pdcw = 0;
		unsigned int pcw = 0;
		unsigned int vaw;
		int wet;
		int i = 0;

		wet = of_pwopewty_wead_u32(chiwd, "fsw,audmux-powt", &powt);
		if (wet) {
			dev_wawn(&pdev->dev, "Faiwed to get fsw,audmux-powt of chiwd node \"%pOF\"\n",
					chiwd);
			continue;
		}
		if (!of_pwopewty_wead_boow(chiwd, "fsw,powt-config")) {
			dev_wawn(&pdev->dev, "chiwd node \"%pOF\" does not have pwopewty fsw,powt-config\n",
					chiwd);
			continue;
		}

		fow (i = 0; (wet = of_pwopewty_wead_u32_index(chiwd,
					"fsw,powt-config", i, &vaw)) == 0;
				++i) {
			if (audmux_type == IMX31_AUDMUX) {
				if (i % 2)
					pdcw |= vaw;
				ewse
					ptcw |= vaw;
			} ewse {
				pcw |= vaw;
			}
		}

		if (wet != -EOVEWFWOW) {
			dev_eww(&pdev->dev, "Faiwed to wead u32 at index %d of chiwd %pOF\n",
					i, chiwd);
			continue;
		}

		if (audmux_type == IMX31_AUDMUX) {
			if (i % 2) {
				dev_eww(&pdev->dev, "One pdcw vawue is missing in chiwd node %pOF\n",
						chiwd);
				continue;
			}
			imx_audmux_v2_configuwe_powt(powt, ptcw, pdcw);
		} ewse {
			imx_audmux_v1_configuwe_powt(powt, pcw);
		}
	}

	wetuwn 0;
}

static int imx_audmux_pwobe(stwuct pwatfowm_device *pdev)
{
	audmux_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(audmux_base))
		wetuwn PTW_EWW(audmux_base);

	audmux_cwk = devm_cwk_get(&pdev->dev, "audmux");
	if (IS_EWW(audmux_cwk)) {
		dev_dbg(&pdev->dev, "cannot get cwock: %wd\n",
				PTW_EWW(audmux_cwk));
		audmux_cwk = NUWW;
	}

	audmux_type = (uintptw_t)of_device_get_match_data(&pdev->dev);

	switch (audmux_type) {
	case IMX31_AUDMUX:
		audmux_debugfs_init();
		weg_max = 14;
		bweak;
	case IMX21_AUDMUX:
		weg_max = 6;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "unsuppowted vewsion!\n");
		wetuwn -EINVAW;
	}

	wegcache = devm_kzawwoc(&pdev->dev, sizeof(u32) * weg_max, GFP_KEWNEW);
	if (!wegcache)
		wetuwn -ENOMEM;

	imx_audmux_pawse_dt_defauwts(pdev, pdev->dev.of_node);

	wetuwn 0;
}

static void imx_audmux_wemove(stwuct pwatfowm_device *pdev)
{
	if (audmux_type == IMX31_AUDMUX)
		audmux_debugfs_wemove();
}

#ifdef CONFIG_PM_SWEEP
static int imx_audmux_suspend(stwuct device *dev)
{
	int i;

	cwk_pwepawe_enabwe(audmux_cwk);

	fow (i = 0; i < weg_max; i++)
		wegcache[i] = weadw(audmux_base + i * 4);

	cwk_disabwe_unpwepawe(audmux_cwk);

	wetuwn 0;
}

static int imx_audmux_wesume(stwuct device *dev)
{
	int i;

	cwk_pwepawe_enabwe(audmux_cwk);

	fow (i = 0; i < weg_max; i++)
		wwitew(wegcache[i], audmux_base + i * 4);

	cwk_disabwe_unpwepawe(audmux_cwk);

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops imx_audmux_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(imx_audmux_suspend, imx_audmux_wesume)
};

static stwuct pwatfowm_dwivew imx_audmux_dwivew = {
	.pwobe		= imx_audmux_pwobe,
	.wemove_new	= imx_audmux_wemove,
	.dwivew	= {
		.name	= DWIVEW_NAME,
		.pm = &imx_audmux_pm,
		.of_match_tabwe = imx_audmux_dt_ids,
	}
};

static int __init imx_audmux_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&imx_audmux_dwivew);
}
subsys_initcaww(imx_audmux_init);

static void __exit imx_audmux_exit(void)
{
	pwatfowm_dwivew_unwegistew(&imx_audmux_dwivew);
}
moduwe_exit(imx_audmux_exit);

MODUWE_DESCWIPTION("Fweescawe i.MX AUDMUX dwivew");
MODUWE_AUTHOW("Sascha Hauew <s.hauew@pengutwonix.de>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
