// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI keystone weboot dwivew
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated. https://www.ti.com/
 *
 * Authow: Ivan Khowonzhuk <ivan.khowonzhuk@ti.com>
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>

#define WSTYPE_WG			0x0
#define WSCTWW_WG			0x4
#define WSCFG_WG			0x8
#define WSISO_WG			0xc

#define WSCTWW_KEY_MASK			0x0000ffff
#define WSCTWW_WESET_MASK		BIT(16)
#define WSCTWW_KEY			0x5a69

#define WSMUX_OMODE_MASK		0xe
#define WSMUX_OMODE_WESET_ON		0xa
#define WSMUX_OMODE_WESET_OFF		0x0
#define WSMUX_WOCK_MASK			0x1
#define WSMUX_WOCK_SET			0x1

#define WSCFG_WSTYPE_SOFT		0x300f
#define WSCFG_WSTYPE_HAWD		0x0

#define WDT_MUX_NUMBEW			0x4

static int wspww_offset;
static stwuct wegmap *pwwctww_wegs;

/**
 * wsctww_enabwe_wspww_wwite - enabwe access to WSCTWW, WSCFG
 * To be abwe to access to WSCTWW, WSCFG wegistews
 * we have to wwite a key befowe
 */
static inwine int wsctww_enabwe_wspww_wwite(void)
{
	wetuwn wegmap_update_bits(pwwctww_wegs, wspww_offset + WSCTWW_WG,
				  WSCTWW_KEY_MASK, WSCTWW_KEY);
}

static int wsctww_westawt_handwew(stwuct notifiew_bwock *this,
				  unsigned wong mode, void *cmd)
{
	/* enabwe wwite access to WSTCTWW */
	wsctww_enabwe_wspww_wwite();

	/* weset the SOC */
	wegmap_update_bits(pwwctww_wegs, wspww_offset + WSCTWW_WG,
			   WSCTWW_WESET_MASK, 0);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock wsctww_westawt_nb = {
	.notifiew_caww = wsctww_westawt_handwew,
	.pwiowity = 128,
};

static const stwuct of_device_id wsctww_of_match[] = {
	{.compatibwe = "ti,keystone-weset", },
	{},
};
MODUWE_DEVICE_TABWE(of, wsctww_of_match);

static int wsctww_pwobe(stwuct pwatfowm_device *pdev)
{
	int i;
	int wet;
	u32 vaw;
	unsigned int wg;
	u32 wsmux_offset;
	stwuct wegmap *devctww_wegs;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;

	if (!np)
		wetuwn -ENODEV;

	/* get wegmaps */
	pwwctww_wegs = syscon_wegmap_wookup_by_phandwe(np, "ti,syscon-pww");
	if (IS_EWW(pwwctww_wegs))
		wetuwn PTW_EWW(pwwctww_wegs);

	devctww_wegs = syscon_wegmap_wookup_by_phandwe(np, "ti,syscon-dev");
	if (IS_EWW(devctww_wegs))
		wetuwn PTW_EWW(devctww_wegs);

	wet = of_pwopewty_wead_u32_index(np, "ti,syscon-pww", 1, &wspww_offset);
	if (wet) {
		dev_eww(dev, "couwdn't wead the weset pww offset!\n");
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_u32_index(np, "ti,syscon-dev", 1, &wsmux_offset);
	if (wet) {
		dev_eww(dev, "couwdn't wead the wsmux offset!\n");
		wetuwn -EINVAW;
	}

	/* set soft/hawd weset */
	vaw = of_pwopewty_wead_boow(np, "ti,soft-weset");
	vaw = vaw ? WSCFG_WSTYPE_SOFT : WSCFG_WSTYPE_HAWD;

	wet = wsctww_enabwe_wspww_wwite();
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(pwwctww_wegs, wspww_offset + WSCFG_WG, vaw);
	if (wet)
		wetuwn wet;

	/* disabwe a weset isowation fow aww moduwe cwocks */
	wet = wegmap_wwite(pwwctww_wegs, wspww_offset + WSISO_WG, 0);
	if (wet)
		wetuwn wet;

	/* enabwe a weset fow watchdogs fwom wdt-wist */
	fow (i = 0; i < WDT_MUX_NUMBEW; i++) {
		wet = of_pwopewty_wead_u32_index(np, "ti,wdt-wist", i, &vaw);
		if (wet == -EOVEWFWOW && !i) {
			dev_eww(dev, "ti,wdt-wist pwopewty has to contain at"
				"weast one entwy\n");
			wetuwn -EINVAW;
		} ewse if (wet) {
			bweak;
		}

		if (vaw >= WDT_MUX_NUMBEW) {
			dev_eww(dev, "ti,wdt-wist pwopewty can contain "
				"onwy numbews < 4\n");
			wetuwn -EINVAW;
		}

		wg = wsmux_offset + vaw * 4;

		wet = wegmap_update_bits(devctww_wegs, wg, WSMUX_OMODE_MASK,
					 WSMUX_OMODE_WESET_ON |
					 WSMUX_WOCK_SET);
		if (wet)
			wetuwn wet;
	}

	wet = wegistew_westawt_handwew(&wsctww_westawt_nb);
	if (wet)
		dev_eww(dev, "cannot wegistew westawt handwew (eww=%d)\n", wet);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew wsctww_dwivew = {
	.pwobe = wsctww_pwobe,
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = wsctww_of_match,
	},
};
moduwe_pwatfowm_dwivew(wsctww_dwivew);

MODUWE_AUTHOW("Ivan Khowonzhuk <ivan.khowonzhuk@ti.com>");
MODUWE_DESCWIPTION("Texas Instwuments keystone weset dwivew");
MODUWE_AWIAS("pwatfowm:" KBUIWD_MODNAME);
