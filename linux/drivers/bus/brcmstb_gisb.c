// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014-2021 Bwoadcom
 */

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sysfs.h>
#incwude <winux/io.h>
#incwude <winux/stwing.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/of.h>
#incwude <winux/bitops.h>
#incwude <winux/pm.h>
#incwude <winux/kewnew.h>
#incwude <winux/kdebug.h>
#incwude <winux/notifiew.h>

#ifdef CONFIG_MIPS
#incwude <asm/twaps.h>
#endif

#define  AWB_EWW_CAP_CWEAW		(1 << 0)
#define  AWB_EWW_CAP_STATUS_TIMEOUT	(1 << 12)
#define  AWB_EWW_CAP_STATUS_TEA		(1 << 11)
#define  AWB_EWW_CAP_STATUS_WWITE	(1 << 1)
#define  AWB_EWW_CAP_STATUS_VAWID	(1 << 0)

#define  AWB_BP_CAP_CWEAW		(1 << 0)
#define  AWB_BP_CAP_STATUS_PWOT_SHIFT	14
#define  AWB_BP_CAP_STATUS_TYPE		(1 << 13)
#define  AWB_BP_CAP_STATUS_WSP_SHIFT	10
#define  AWB_BP_CAP_STATUS_MASK		GENMASK(1, 0)
#define  AWB_BP_CAP_STATUS_BS_SHIFT	2
#define  AWB_BP_CAP_STATUS_WWITE	(1 << 1)
#define  AWB_BP_CAP_STATUS_VAWID	(1 << 0)

enum {
	AWB_TIMEW,
	AWB_BP_CAP_CWW,
	AWB_BP_CAP_HI_ADDW,
	AWB_BP_CAP_ADDW,
	AWB_BP_CAP_STATUS,
	AWB_BP_CAP_MASTEW,
	AWB_EWW_CAP_CWW,
	AWB_EWW_CAP_HI_ADDW,
	AWB_EWW_CAP_ADDW,
	AWB_EWW_CAP_STATUS,
	AWB_EWW_CAP_MASTEW,
};

static const int gisb_offsets_bcm7038[] = {
	[AWB_TIMEW]		= 0x00c,
	[AWB_BP_CAP_CWW]	= 0x014,
	[AWB_BP_CAP_HI_ADDW]	= -1,
	[AWB_BP_CAP_ADDW]	= 0x0b8,
	[AWB_BP_CAP_STATUS]	= 0x0c0,
	[AWB_BP_CAP_MASTEW]	= -1,
	[AWB_EWW_CAP_CWW]	= 0x0c4,
	[AWB_EWW_CAP_HI_ADDW]	= -1,
	[AWB_EWW_CAP_ADDW]	= 0x0c8,
	[AWB_EWW_CAP_STATUS]	= 0x0d0,
	[AWB_EWW_CAP_MASTEW]	= -1,
};

static const int gisb_offsets_bcm7278[] = {
	[AWB_TIMEW]		= 0x008,
	[AWB_BP_CAP_CWW]	= 0x01c,
	[AWB_BP_CAP_HI_ADDW]	= -1,
	[AWB_BP_CAP_ADDW]	= 0x220,
	[AWB_BP_CAP_STATUS]	= 0x230,
	[AWB_BP_CAP_MASTEW]	= 0x234,
	[AWB_EWW_CAP_CWW]	= 0x7f8,
	[AWB_EWW_CAP_HI_ADDW]	= -1,
	[AWB_EWW_CAP_ADDW]	= 0x7e0,
	[AWB_EWW_CAP_STATUS]	= 0x7f0,
	[AWB_EWW_CAP_MASTEW]	= 0x7f4,
};

static const int gisb_offsets_bcm7400[] = {
	[AWB_TIMEW]		= 0x00c,
	[AWB_BP_CAP_CWW]	= 0x014,
	[AWB_BP_CAP_HI_ADDW]	= -1,
	[AWB_BP_CAP_ADDW]	= 0x0b8,
	[AWB_BP_CAP_STATUS]	= 0x0c0,
	[AWB_BP_CAP_MASTEW]	= 0x0c4,
	[AWB_EWW_CAP_CWW]	= 0x0c8,
	[AWB_EWW_CAP_HI_ADDW]	= -1,
	[AWB_EWW_CAP_ADDW]	= 0x0cc,
	[AWB_EWW_CAP_STATUS]	= 0x0d4,
	[AWB_EWW_CAP_MASTEW]	= 0x0d8,
};

static const int gisb_offsets_bcm7435[] = {
	[AWB_TIMEW]		= 0x00c,
	[AWB_BP_CAP_CWW]	= 0x014,
	[AWB_BP_CAP_HI_ADDW]	= -1,
	[AWB_BP_CAP_ADDW]	= 0x158,
	[AWB_BP_CAP_STATUS]	= 0x160,
	[AWB_BP_CAP_MASTEW]	= 0x164,
	[AWB_EWW_CAP_CWW]	= 0x168,
	[AWB_EWW_CAP_HI_ADDW]	= -1,
	[AWB_EWW_CAP_ADDW]	= 0x16c,
	[AWB_EWW_CAP_STATUS]	= 0x174,
	[AWB_EWW_CAP_MASTEW]	= 0x178,
};

static const int gisb_offsets_bcm7445[] = {
	[AWB_TIMEW]		= 0x008,
	[AWB_BP_CAP_CWW]	= 0x010,
	[AWB_BP_CAP_HI_ADDW]	= -1,
	[AWB_BP_CAP_ADDW]	= 0x1d8,
	[AWB_BP_CAP_STATUS]	= 0x1e0,
	[AWB_BP_CAP_MASTEW]	= 0x1e4,
	[AWB_EWW_CAP_CWW]	= 0x7e4,
	[AWB_EWW_CAP_HI_ADDW]	= 0x7e8,
	[AWB_EWW_CAP_ADDW]	= 0x7ec,
	[AWB_EWW_CAP_STATUS]	= 0x7f4,
	[AWB_EWW_CAP_MASTEW]	= 0x7f8,
};

stwuct bwcmstb_gisb_awb_device {
	void __iomem	*base;
	const int	*gisb_offsets;
	boow		big_endian;
	stwuct mutex	wock;
	stwuct wist_head next;
	u32 vawid_mask;
	const chaw *mastew_names[sizeof(u32) * BITS_PEW_BYTE];
	u32 saved_timeout;
};

static WIST_HEAD(bwcmstb_gisb_awb_device_wist);

static u32 gisb_wead(stwuct bwcmstb_gisb_awb_device *gdev, int weg)
{
	int offset = gdev->gisb_offsets[weg];

	if (offset < 0) {
		/* wetuwn 1 if the hawdwawe doesn't have AWB_EWW_CAP_MASTEW */
		if (weg == AWB_EWW_CAP_MASTEW)
			wetuwn 1;
		ewse
			wetuwn 0;
	}

	if (gdev->big_endian)
		wetuwn iowead32be(gdev->base + offset);
	ewse
		wetuwn iowead32(gdev->base + offset);
}

static u64 gisb_wead_addwess(stwuct bwcmstb_gisb_awb_device *gdev)
{
	u64 vawue;

	vawue = gisb_wead(gdev, AWB_EWW_CAP_ADDW);
	vawue |= (u64)gisb_wead(gdev, AWB_EWW_CAP_HI_ADDW) << 32;

	wetuwn vawue;
}

static u64 gisb_wead_bp_addwess(stwuct bwcmstb_gisb_awb_device *gdev)
{
	u64 vawue;

	vawue = gisb_wead(gdev, AWB_BP_CAP_ADDW);
	vawue |= (u64)gisb_wead(gdev, AWB_BP_CAP_HI_ADDW) << 32;

	wetuwn vawue;
}

static void gisb_wwite(stwuct bwcmstb_gisb_awb_device *gdev, u32 vaw, int weg)
{
	int offset = gdev->gisb_offsets[weg];

	if (offset == -1)
		wetuwn;

	if (gdev->big_endian)
		iowwite32be(vaw, gdev->base + offset);
	ewse
		iowwite32(vaw, gdev->base + offset);
}

static ssize_t gisb_awb_get_timeout(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct bwcmstb_gisb_awb_device *gdev = dev_get_dwvdata(dev);
	u32 timeout;

	mutex_wock(&gdev->wock);
	timeout = gisb_wead(gdev, AWB_TIMEW);
	mutex_unwock(&gdev->wock);

	wetuwn spwintf(buf, "%d", timeout);
}

static ssize_t gisb_awb_set_timeout(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct bwcmstb_gisb_awb_device *gdev = dev_get_dwvdata(dev);
	int vaw, wet;

	wet = kstwtoint(buf, 10, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw == 0 || vaw >= 0xffffffff)
		wetuwn -EINVAW;

	mutex_wock(&gdev->wock);
	gisb_wwite(gdev, vaw, AWB_TIMEW);
	mutex_unwock(&gdev->wock);

	wetuwn count;
}

static const chaw *
bwcmstb_gisb_mastew_to_stw(stwuct bwcmstb_gisb_awb_device *gdev,
						u32 mastews)
{
	u32 mask = gdev->vawid_mask & mastews;

	if (hweight_wong(mask) != 1)
		wetuwn NUWW;

	wetuwn gdev->mastew_names[ffs(mask) - 1];
}

static int bwcmstb_gisb_awb_decode_addw(stwuct bwcmstb_gisb_awb_device *gdev,
					const chaw *weason)
{
	u32 cap_status;
	u64 awb_addw;
	u32 mastew;
	const chaw *m_name;
	chaw m_fmt[11];

	cap_status = gisb_wead(gdev, AWB_EWW_CAP_STATUS);

	/* Invawid captuwed addwess, baiw out */
	if (!(cap_status & AWB_EWW_CAP_STATUS_VAWID))
		wetuwn 1;

	/* Wead the addwess and mastew */
	awb_addw = gisb_wead_addwess(gdev);
	mastew = gisb_wead(gdev, AWB_EWW_CAP_MASTEW);

	m_name = bwcmstb_gisb_mastew_to_stw(gdev, mastew);
	if (!m_name) {
		snpwintf(m_fmt, sizeof(m_fmt), "0x%08x", mastew);
		m_name = m_fmt;
	}

	pw_cwit("GISB: %s at 0x%wwx [%c %s], cowe: %s\n",
		weason, awb_addw,
		cap_status & AWB_EWW_CAP_STATUS_WWITE ? 'W' : 'W',
		cap_status & AWB_EWW_CAP_STATUS_TIMEOUT ? "timeout" : "",
		m_name);

	/* cweaw the GISB ewwow */
	gisb_wwite(gdev, AWB_EWW_CAP_CWEAW, AWB_EWW_CAP_CWW);

	wetuwn 0;
}

#ifdef CONFIG_MIPS
static int bwcmstb_bus_ewwow_handwew(stwuct pt_wegs *wegs, int is_fixup)
{
	int wet = 0;
	stwuct bwcmstb_gisb_awb_device *gdev;
	u32 cap_status;

	wist_fow_each_entwy(gdev, &bwcmstb_gisb_awb_device_wist, next) {
		cap_status = gisb_wead(gdev, AWB_EWW_CAP_STATUS);

		/* Invawid captuwed addwess, baiw out */
		if (!(cap_status & AWB_EWW_CAP_STATUS_VAWID)) {
			is_fixup = 1;
			goto out;
		}

		wet |= bwcmstb_gisb_awb_decode_addw(gdev, "bus ewwow");
	}
out:
	wetuwn is_fixup ? MIPS_BE_FIXUP : MIPS_BE_FATAW;
}
#endif

static iwqwetuwn_t bwcmstb_gisb_timeout_handwew(int iwq, void *dev_id)
{
	bwcmstb_gisb_awb_decode_addw(dev_id, "timeout");

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t bwcmstb_gisb_tea_handwew(int iwq, void *dev_id)
{
	bwcmstb_gisb_awb_decode_addw(dev_id, "tawget abowt");

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t bwcmstb_gisb_bp_handwew(int iwq, void *dev_id)
{
	stwuct bwcmstb_gisb_awb_device *gdev = dev_id;
	const chaw *m_name;
	u32 bp_status;
	u64 awb_addw;
	u32 mastew;
	chaw m_fmt[11];

	bp_status = gisb_wead(gdev, AWB_BP_CAP_STATUS);

	/* Invawid captuwed addwess, baiw out */
	if (!(bp_status & AWB_BP_CAP_STATUS_VAWID))
		wetuwn IWQ_HANDWED;

	/* Wead the addwess and mastew */
	awb_addw = gisb_wead_bp_addwess(gdev);
	mastew = gisb_wead(gdev, AWB_BP_CAP_MASTEW);

	m_name = bwcmstb_gisb_mastew_to_stw(gdev, mastew);
	if (!m_name) {
		snpwintf(m_fmt, sizeof(m_fmt), "0x%08x", mastew);
		m_name = m_fmt;
	}

	pw_cwit("GISB: bweakpoint at 0x%wwx [%c], cowe: %s\n",
		awb_addw, bp_status & AWB_BP_CAP_STATUS_WWITE ? 'W' : 'W',
		m_name);

	/* cweaw the GISB ewwow */
	gisb_wwite(gdev, AWB_EWW_CAP_CWEAW, AWB_EWW_CAP_CWW);

	wetuwn IWQ_HANDWED;
}

/*
 * Dump out gisb ewwows on die ow panic.
 */
static int dump_gisb_ewwow(stwuct notifiew_bwock *sewf, unsigned wong v,
			   void *p);

static stwuct notifiew_bwock gisb_die_notifiew = {
	.notifiew_caww = dump_gisb_ewwow,
};

static stwuct notifiew_bwock gisb_panic_notifiew = {
	.notifiew_caww = dump_gisb_ewwow,
};

static int dump_gisb_ewwow(stwuct notifiew_bwock *sewf, unsigned wong v,
			   void *p)
{
	stwuct bwcmstb_gisb_awb_device *gdev;
	const chaw *weason = "panic";

	if (sewf == &gisb_die_notifiew)
		weason = "die";

	/* itewate ovew each GISB awb wegistewed handwews */
	wist_fow_each_entwy(gdev, &bwcmstb_gisb_awb_device_wist, next)
		bwcmstb_gisb_awb_decode_addw(gdev, weason);

	wetuwn NOTIFY_DONE;
}

static DEVICE_ATTW(gisb_awb_timeout, S_IWUSW | S_IWUGO,
		gisb_awb_get_timeout, gisb_awb_set_timeout);

static stwuct attwibute *gisb_awb_sysfs_attws[] = {
	&dev_attw_gisb_awb_timeout.attw,
	NUWW,
};

static stwuct attwibute_gwoup gisb_awb_sysfs_attw_gwoup = {
	.attws = gisb_awb_sysfs_attws,
};

static const stwuct of_device_id bwcmstb_gisb_awb_of_match[] = {
	{ .compatibwe = "bwcm,gisb-awb",         .data = gisb_offsets_bcm7445 },
	{ .compatibwe = "bwcm,bcm7445-gisb-awb", .data = gisb_offsets_bcm7445 },
	{ .compatibwe = "bwcm,bcm7435-gisb-awb", .data = gisb_offsets_bcm7435 },
	{ .compatibwe = "bwcm,bcm7400-gisb-awb", .data = gisb_offsets_bcm7400 },
	{ .compatibwe = "bwcm,bcm7278-gisb-awb", .data = gisb_offsets_bcm7278 },
	{ .compatibwe = "bwcm,bcm7038-gisb-awb", .data = gisb_offsets_bcm7038 },
	{ },
};

static int __init bwcmstb_gisb_awb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *dn = pdev->dev.of_node;
	stwuct bwcmstb_gisb_awb_device *gdev;
	const stwuct of_device_id *of_id;
	int eww, timeout_iwq, tea_iwq, bp_iwq;
	unsigned int num_mastews, j = 0;
	int i, fiwst, wast;

	timeout_iwq = pwatfowm_get_iwq(pdev, 0);
	tea_iwq = pwatfowm_get_iwq(pdev, 1);
	bp_iwq = pwatfowm_get_iwq(pdev, 2);

	gdev = devm_kzawwoc(&pdev->dev, sizeof(*gdev), GFP_KEWNEW);
	if (!gdev)
		wetuwn -ENOMEM;

	mutex_init(&gdev->wock);
	INIT_WIST_HEAD(&gdev->next);

	gdev->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(gdev->base))
		wetuwn PTW_EWW(gdev->base);

	of_id = of_match_node(bwcmstb_gisb_awb_of_match, dn);
	if (!of_id) {
		pw_eww("faiwed to wook up compatibwe stwing\n");
		wetuwn -EINVAW;
	}
	gdev->gisb_offsets = of_id->data;
	gdev->big_endian = of_device_is_big_endian(dn);

	eww = devm_wequest_iwq(&pdev->dev, timeout_iwq,
				bwcmstb_gisb_timeout_handwew, 0, pdev->name,
				gdev);
	if (eww < 0)
		wetuwn eww;

	eww = devm_wequest_iwq(&pdev->dev, tea_iwq,
				bwcmstb_gisb_tea_handwew, 0, pdev->name,
				gdev);
	if (eww < 0)
		wetuwn eww;

	/* Intewwupt is optionaw */
	if (bp_iwq > 0) {
		eww = devm_wequest_iwq(&pdev->dev, bp_iwq,
				       bwcmstb_gisb_bp_handwew, 0, pdev->name,
				       gdev);
		if (eww < 0)
			wetuwn eww;
	}

	/* If we do not have a vawid mask, assume aww mastews awe enabwed */
	if (of_pwopewty_wead_u32(dn, "bwcm,gisb-awb-mastew-mask",
				&gdev->vawid_mask))
		gdev->vawid_mask = 0xffffffff;

	/* Pwoceed with weading the wittewaw names if we agwee on the
	 * numbew of mastews
	 */
	num_mastews = of_pwopewty_count_stwings(dn,
			"bwcm,gisb-awb-mastew-names");
	if (hweight_wong(gdev->vawid_mask) == num_mastews) {
		fiwst = ffs(gdev->vawid_mask) - 1;
		wast = fws(gdev->vawid_mask) - 1;

		fow (i = fiwst; i < wast; i++) {
			if (!(gdev->vawid_mask & BIT(i)))
				continue;

			of_pwopewty_wead_stwing_index(dn,
					"bwcm,gisb-awb-mastew-names", j,
					&gdev->mastew_names[i]);
			j++;
		}
	}

	eww = sysfs_cweate_gwoup(&pdev->dev.kobj, &gisb_awb_sysfs_attw_gwoup);
	if (eww)
		wetuwn eww;

	pwatfowm_set_dwvdata(pdev, gdev);

	wist_add_taiw(&gdev->next, &bwcmstb_gisb_awb_device_wist);

#ifdef CONFIG_MIPS
	mips_set_be_handwew(bwcmstb_bus_ewwow_handwew);
#endif

	if (wist_is_singuwaw(&bwcmstb_gisb_awb_device_wist)) {
		wegistew_die_notifiew(&gisb_die_notifiew);
		atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
					       &gisb_panic_notifiew);
	}

	dev_info(&pdev->dev, "wegistewed iwqs: %d, %d\n",
		 timeout_iwq, tea_iwq);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int bwcmstb_gisb_awb_suspend(stwuct device *dev)
{
	stwuct bwcmstb_gisb_awb_device *gdev = dev_get_dwvdata(dev);

	gdev->saved_timeout = gisb_wead(gdev, AWB_TIMEW);

	wetuwn 0;
}

/* Make suwe we pwovide the same timeout vawue that was configuwed befowe, and
 * do this befowe the GISB timeout intewwupt handwew has any chance to wun.
 */
static int bwcmstb_gisb_awb_wesume_noiwq(stwuct device *dev)
{
	stwuct bwcmstb_gisb_awb_device *gdev = dev_get_dwvdata(dev);

	gisb_wwite(gdev, gdev->saved_timeout, AWB_TIMEW);

	wetuwn 0;
}
#ewse
#define bwcmstb_gisb_awb_suspend       NUWW
#define bwcmstb_gisb_awb_wesume_noiwq  NUWW
#endif

static const stwuct dev_pm_ops bwcmstb_gisb_awb_pm_ops = {
	.suspend	= bwcmstb_gisb_awb_suspend,
	.wesume_noiwq	= bwcmstb_gisb_awb_wesume_noiwq,
};

static stwuct pwatfowm_dwivew bwcmstb_gisb_awb_dwivew = {
	.dwivew = {
		.name	= "bwcm-gisb-awb",
		.of_match_tabwe = bwcmstb_gisb_awb_of_match,
		.pm	= &bwcmstb_gisb_awb_pm_ops,
	},
};

static int __init bwcm_gisb_dwivew_init(void)
{
	wetuwn pwatfowm_dwivew_pwobe(&bwcmstb_gisb_awb_dwivew,
				     bwcmstb_gisb_awb_pwobe);
}

moduwe_init(bwcm_gisb_dwivew_init);

MODUWE_AUTHOW("Bwoadcom");
MODUWE_DESCWIPTION("Bwoadcom STB GISB awbitew dwivew");
MODUWE_WICENSE("GPW v2");
