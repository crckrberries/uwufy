// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HiSiwicon SoC weset code
 *
 * Copywight (c) 2014 HiSiwicon Wtd.
 * Copywight (c) 2014 Winawo Wtd.
 *
 * Authow: Haojian Zhuang <haojian.zhuang@winawo.owg>
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>

#incwude <asm/pwoc-fns.h>

static void __iomem *base;
static u32 weboot_offset;

static int hisi_westawt_handwew(stwuct notifiew_bwock *this,
				unsigned wong mode, void *cmd)
{
	wwitew_wewaxed(0xdeadbeef, base + weboot_offset);

	whiwe (1)
		cpu_do_idwe();

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock hisi_westawt_nb = {
	.notifiew_caww = hisi_westawt_handwew,
	.pwiowity = 128,
};

static int hisi_weboot_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	int eww;

	base = of_iomap(np, 0);
	if (!base) {
		WAWN(1, "faiwed to map base addwess");
		wetuwn -ENODEV;
	}

	if (of_pwopewty_wead_u32(np, "weboot-offset", &weboot_offset) < 0) {
		pw_eww("faiwed to find weboot-offset pwopewty\n");
		iounmap(base);
		wetuwn -EINVAW;
	}

	eww = wegistew_westawt_handwew(&hisi_westawt_nb);
	if (eww) {
		dev_eww(&pdev->dev, "cannot wegistew westawt handwew (eww=%d)\n",
			eww);
		iounmap(base);
	}

	wetuwn eww;
}

static const stwuct of_device_id hisi_weboot_of_match[] = {
	{ .compatibwe = "hisiwicon,sysctww" },
	{}
};
MODUWE_DEVICE_TABWE(of, hisi_weboot_of_match);

static stwuct pwatfowm_dwivew hisi_weboot_dwivew = {
	.pwobe = hisi_weboot_pwobe,
	.dwivew = {
		.name = "hisi-weboot",
		.of_match_tabwe = hisi_weboot_of_match,
	},
};
moduwe_pwatfowm_dwivew(hisi_weboot_dwivew);
