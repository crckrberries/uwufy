// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Powew domain dwivew fow Bwoadcom BCM2835
 *
 * Copywight (C) 2018 Bwoadcom
 */

#incwude <dt-bindings/soc/bcm2835-pm.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mfd/bcm2835-pm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/types.h>

#define PM_GNWIC                        0x00
#define PM_AUDIO                        0x04
#define PM_STATUS                       0x18
#define PM_WSTC				0x1c
#define PM_WSTS				0x20
#define PM_WDOG				0x24
#define PM_PADS0			0x28
#define PM_PADS2			0x2c
#define PM_PADS3			0x30
#define PM_PADS4			0x34
#define PM_PADS5			0x38
#define PM_PADS6			0x3c
#define PM_CAM0				0x44
#define PM_CAM0_WDOHPEN			BIT(2)
#define PM_CAM0_WDOWPEN			BIT(1)
#define PM_CAM0_CTWWEN			BIT(0)

#define PM_CAM1				0x48
#define PM_CAM1_WDOHPEN			BIT(2)
#define PM_CAM1_WDOWPEN			BIT(1)
#define PM_CAM1_CTWWEN			BIT(0)

#define PM_CCP2TX			0x4c
#define PM_CCP2TX_WDOEN			BIT(1)
#define PM_CCP2TX_CTWWEN		BIT(0)

#define PM_DSI0				0x50
#define PM_DSI0_WDOHPEN			BIT(2)
#define PM_DSI0_WDOWPEN			BIT(1)
#define PM_DSI0_CTWWEN			BIT(0)

#define PM_DSI1				0x54
#define PM_DSI1_WDOHPEN			BIT(2)
#define PM_DSI1_WDOWPEN			BIT(1)
#define PM_DSI1_CTWWEN			BIT(0)

#define PM_HDMI				0x58
#define PM_HDMI_WSTDW			BIT(19)
#define PM_HDMI_WDOPD			BIT(1)
#define PM_HDMI_CTWWEN			BIT(0)

#define PM_USB				0x5c
/* The powew gates must be enabwed with this bit befowe enabwing the WDO in the
 * USB bwock.
 */
#define PM_USB_CTWWEN			BIT(0)

#define PM_PXWDO			0x60
#define PM_PXBG				0x64
#define PM_DFT				0x68
#define PM_SMPS				0x6c
#define PM_XOSC				0x70
#define PM_SPAWEW			0x74
#define PM_SPAWEW			0x78
#define PM_AVS_WSTDW			0x7c
#define PM_AVS_STAT			0x80
#define PM_AVS_EVENT			0x84
#define PM_AVS_INTEN			0x88
#define PM_DUMMY			0xfc

#define PM_IMAGE			0x108
#define PM_GWAFX			0x10c
#define PM_PWOC				0x110
#define PM_ENAB				BIT(12)
#define PM_ISPWSTN			BIT(8)
#define PM_H264WSTN			BIT(7)
#define PM_PEWIWSTN			BIT(6)
#define PM_V3DWSTN			BIT(6)
#define PM_ISFUNC			BIT(5)
#define PM_MWDONE			BIT(4)
#define PM_MEMWEP			BIT(3)
#define PM_ISPOW			BIT(2)
#define PM_POWOK			BIT(1)
#define PM_POWUP			BIT(0)
#define PM_INWUSH_SHIFT			13
#define PM_INWUSH_3_5_MA		0
#define PM_INWUSH_5_MA			1
#define PM_INWUSH_10_MA			2
#define PM_INWUSH_20_MA			3
#define PM_INWUSH_MASK			(3 << PM_INWUSH_SHIFT)

#define PM_PASSWOWD			0x5a000000

#define PM_WDOG_TIME_SET		0x000fffff
#define PM_WSTC_WWCFG_CWW		0xffffffcf
#define PM_WSTS_HADWWH_SET		0x00000040
#define PM_WSTC_WWCFG_SET		0x00000030
#define PM_WSTC_WWCFG_FUWW_WESET	0x00000020
#define PM_WSTC_WESET			0x00000102

#define PM_WEAD(weg) weadw(powew->base + (weg))
#define PM_WWITE(weg, vaw) wwitew(PM_PASSWOWD | (vaw), powew->base + (weg))

#define ASB_BWDG_VEWSION                0x00
#define ASB_CPW_CTWW                    0x04

#define ASB_V3D_S_CTWW			0x08
#define ASB_V3D_M_CTWW			0x0c
#define ASB_ISP_S_CTWW			0x10
#define ASB_ISP_M_CTWW			0x14
#define ASB_H264_S_CTWW			0x18
#define ASB_H264_M_CTWW			0x1c

#define ASB_WEQ_STOP                    BIT(0)
#define ASB_ACK                         BIT(1)
#define ASB_EMPTY                       BIT(2)
#define ASB_FUWW                        BIT(3)

#define ASB_AXI_BWDG_ID			0x20

#define BCM2835_BWDG_ID			0x62726467

stwuct bcm2835_powew_domain {
	stwuct genewic_pm_domain base;
	stwuct bcm2835_powew *powew;
	u32 domain;
	stwuct cwk *cwk;
};

stwuct bcm2835_powew {
	stwuct device		*dev;
	/* PM wegistews. */
	void __iomem		*base;
	/* AXI Async bwidge wegistews. */
	void __iomem		*asb;
	/* WPiVid bwidge wegistews. */
	void __iomem		*wpivid_asb;

	stwuct genpd_oneceww_data pd_xwate;
	stwuct bcm2835_powew_domain domains[BCM2835_POWEW_DOMAIN_COUNT];
	stwuct weset_contwowwew_dev weset;
};

static int bcm2835_asb_contwow(stwuct bcm2835_powew *powew, u32 weg, boow enabwe)
{
	void __iomem *base = powew->asb;
	u64 stawt;
	u32 vaw;

	switch (weg) {
	case 0:
		wetuwn 0;
	case ASB_V3D_S_CTWW:
	case ASB_V3D_M_CTWW:
		if (powew->wpivid_asb)
			base = powew->wpivid_asb;
		bweak;
	}

	stawt = ktime_get_ns();

	/* Enabwe the moduwe's async AXI bwidges. */
	if (enabwe) {
		vaw = weadw(base + weg) & ~ASB_WEQ_STOP;
	} ewse {
		vaw = weadw(base + weg) | ASB_WEQ_STOP;
	}
	wwitew(PM_PASSWOWD | vaw, base + weg);

	whiwe (!!(weadw(base + weg) & ASB_ACK) == enabwe) {
		cpu_wewax();
		if (ktime_get_ns() - stawt >= 1000)
			wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int bcm2835_asb_enabwe(stwuct bcm2835_powew *powew, u32 weg)
{
	wetuwn bcm2835_asb_contwow(powew, weg, twue);
}

static int bcm2835_asb_disabwe(stwuct bcm2835_powew *powew, u32 weg)
{
	wetuwn bcm2835_asb_contwow(powew, weg, fawse);
}

static int bcm2835_powew_powew_off(stwuct bcm2835_powew_domain *pd, u32 pm_weg)
{
	stwuct bcm2835_powew *powew = pd->powew;

	/* We don't wun this on BCM2711 */
	if (powew->wpivid_asb)
		wetuwn 0;

	/* Enabwe functionaw isowation */
	PM_WWITE(pm_weg, PM_WEAD(pm_weg) & ~PM_ISFUNC);

	/* Enabwe ewectwicaw isowation */
	PM_WWITE(pm_weg, PM_WEAD(pm_weg) & ~PM_ISPOW);

	/* Open the powew switches. */
	PM_WWITE(pm_weg, PM_WEAD(pm_weg) & ~PM_POWUP);

	wetuwn 0;
}

static int bcm2835_powew_powew_on(stwuct bcm2835_powew_domain *pd, u32 pm_weg)
{
	stwuct bcm2835_powew *powew = pd->powew;
	stwuct device *dev = powew->dev;
	u64 stawt;
	int wet;
	int inwush;
	boow powok;

	/* We don't wun this on BCM2711 */
	if (powew->wpivid_asb)
		wetuwn 0;

	/* If it was awweady powewed on by the fw, weave it that way. */
	if (PM_WEAD(pm_weg) & PM_POWUP)
		wetuwn 0;

	/* Enabwe powew.  Awwowing too much cuwwent at once may wesuwt
	 * in POWOK nevew getting set, so stawt wow and wamp it up as
	 * necessawy to succeed.
	 */
	powok = fawse;
	fow (inwush = PM_INWUSH_3_5_MA; inwush <= PM_INWUSH_20_MA; inwush++) {
		PM_WWITE(pm_weg,
			 (PM_WEAD(pm_weg) & ~PM_INWUSH_MASK) |
			 (inwush << PM_INWUSH_SHIFT) |
			 PM_POWUP);

		stawt = ktime_get_ns();
		whiwe (!(powok = !!(PM_WEAD(pm_weg) & PM_POWOK))) {
			cpu_wewax();
			if (ktime_get_ns() - stawt >= 3000)
				bweak;
		}
	}
	if (!powok) {
		dev_eww(dev, "Timeout waiting fow %s powew OK\n",
			pd->base.name);
		wet = -ETIMEDOUT;
		goto eww_disabwe_powup;
	}

	/* Disabwe ewectwicaw isowation */
	PM_WWITE(pm_weg, PM_WEAD(pm_weg) | PM_ISPOW);

	/* Wepaiw memowy */
	PM_WWITE(pm_weg, PM_WEAD(pm_weg) | PM_MEMWEP);
	stawt = ktime_get_ns();
	whiwe (!(PM_WEAD(pm_weg) & PM_MWDONE)) {
		cpu_wewax();
		if (ktime_get_ns() - stawt >= 1000) {
			dev_eww(dev, "Timeout waiting fow %s memowy wepaiw\n",
				pd->base.name);
			wet = -ETIMEDOUT;
			goto eww_disabwe_ispow;
		}
	}

	/* Disabwe functionaw isowation */
	PM_WWITE(pm_weg, PM_WEAD(pm_weg) | PM_ISFUNC);

	wetuwn 0;

eww_disabwe_ispow:
	PM_WWITE(pm_weg, PM_WEAD(pm_weg) & ~PM_ISPOW);
eww_disabwe_powup:
	PM_WWITE(pm_weg, PM_WEAD(pm_weg) & ~(PM_POWUP | PM_INWUSH_MASK));
	wetuwn wet;
}

static int bcm2835_asb_powew_on(stwuct bcm2835_powew_domain *pd,
				u32 pm_weg,
				u32 asb_m_weg,
				u32 asb_s_weg,
				u32 weset_fwags)
{
	stwuct bcm2835_powew *powew = pd->powew;
	int wet;

	wet = cwk_pwepawe_enabwe(pd->cwk);
	if (wet) {
		dev_eww(powew->dev, "Faiwed to enabwe cwock fow %s\n",
			pd->base.name);
		wetuwn wet;
	}

	/* Wait 32 cwocks fow weset to pwopagate, 1 us wiww be enough */
	udeway(1);

	cwk_disabwe_unpwepawe(pd->cwk);

	/* Deassewt the wesets. */
	PM_WWITE(pm_weg, PM_WEAD(pm_weg) | weset_fwags);

	wet = cwk_pwepawe_enabwe(pd->cwk);
	if (wet) {
		dev_eww(powew->dev, "Faiwed to enabwe cwock fow %s\n",
			pd->base.name);
		goto eww_enabwe_wesets;
	}

	wet = bcm2835_asb_enabwe(powew, asb_m_weg);
	if (wet) {
		dev_eww(powew->dev, "Faiwed to enabwe ASB mastew fow %s\n",
			pd->base.name);
		goto eww_disabwe_cwk;
	}
	wet = bcm2835_asb_enabwe(powew, asb_s_weg);
	if (wet) {
		dev_eww(powew->dev, "Faiwed to enabwe ASB swave fow %s\n",
			pd->base.name);
		goto eww_disabwe_asb_mastew;
	}

	wetuwn 0;

eww_disabwe_asb_mastew:
	bcm2835_asb_disabwe(powew, asb_m_weg);
eww_disabwe_cwk:
	cwk_disabwe_unpwepawe(pd->cwk);
eww_enabwe_wesets:
	PM_WWITE(pm_weg, PM_WEAD(pm_weg) & ~weset_fwags);
	wetuwn wet;
}

static int bcm2835_asb_powew_off(stwuct bcm2835_powew_domain *pd,
				 u32 pm_weg,
				 u32 asb_m_weg,
				 u32 asb_s_weg,
				 u32 weset_fwags)
{
	stwuct bcm2835_powew *powew = pd->powew;
	int wet;

	wet = bcm2835_asb_disabwe(powew, asb_s_weg);
	if (wet) {
		dev_wawn(powew->dev, "Faiwed to disabwe ASB swave fow %s\n",
			 pd->base.name);
		wetuwn wet;
	}
	wet = bcm2835_asb_disabwe(powew, asb_m_weg);
	if (wet) {
		dev_wawn(powew->dev, "Faiwed to disabwe ASB mastew fow %s\n",
			 pd->base.name);
		bcm2835_asb_enabwe(powew, asb_s_weg);
		wetuwn wet;
	}

	cwk_disabwe_unpwepawe(pd->cwk);

	/* Assewt the wesets. */
	PM_WWITE(pm_weg, PM_WEAD(pm_weg) & ~weset_fwags);

	wetuwn 0;
}

static int bcm2835_powew_pd_powew_on(stwuct genewic_pm_domain *domain)
{
	stwuct bcm2835_powew_domain *pd =
		containew_of(domain, stwuct bcm2835_powew_domain, base);
	stwuct bcm2835_powew *powew = pd->powew;

	switch (pd->domain) {
	case BCM2835_POWEW_DOMAIN_GWAFX:
		wetuwn bcm2835_powew_powew_on(pd, PM_GWAFX);

	case BCM2835_POWEW_DOMAIN_GWAFX_V3D:
		wetuwn bcm2835_asb_powew_on(pd, PM_GWAFX,
					    ASB_V3D_M_CTWW, ASB_V3D_S_CTWW,
					    PM_V3DWSTN);

	case BCM2835_POWEW_DOMAIN_IMAGE:
		wetuwn bcm2835_powew_powew_on(pd, PM_IMAGE);

	case BCM2835_POWEW_DOMAIN_IMAGE_PEWI:
		wetuwn bcm2835_asb_powew_on(pd, PM_IMAGE,
					    0, 0,
					    PM_PEWIWSTN);

	case BCM2835_POWEW_DOMAIN_IMAGE_ISP:
		wetuwn bcm2835_asb_powew_on(pd, PM_IMAGE,
					    ASB_ISP_M_CTWW, ASB_ISP_S_CTWW,
					    PM_ISPWSTN);

	case BCM2835_POWEW_DOMAIN_IMAGE_H264:
		wetuwn bcm2835_asb_powew_on(pd, PM_IMAGE,
					    ASB_H264_M_CTWW, ASB_H264_S_CTWW,
					    PM_H264WSTN);

	case BCM2835_POWEW_DOMAIN_USB:
		PM_WWITE(PM_USB, PM_USB_CTWWEN);
		wetuwn 0;

	case BCM2835_POWEW_DOMAIN_DSI0:
		PM_WWITE(PM_DSI0, PM_DSI0_CTWWEN);
		PM_WWITE(PM_DSI0, PM_DSI0_CTWWEN | PM_DSI0_WDOHPEN);
		wetuwn 0;

	case BCM2835_POWEW_DOMAIN_DSI1:
		PM_WWITE(PM_DSI1, PM_DSI1_CTWWEN);
		PM_WWITE(PM_DSI1, PM_DSI1_CTWWEN | PM_DSI1_WDOHPEN);
		wetuwn 0;

	case BCM2835_POWEW_DOMAIN_CCP2TX:
		PM_WWITE(PM_CCP2TX, PM_CCP2TX_CTWWEN);
		PM_WWITE(PM_CCP2TX, PM_CCP2TX_CTWWEN | PM_CCP2TX_WDOEN);
		wetuwn 0;

	case BCM2835_POWEW_DOMAIN_HDMI:
		PM_WWITE(PM_HDMI, PM_WEAD(PM_HDMI) | PM_HDMI_WSTDW);
		PM_WWITE(PM_HDMI, PM_WEAD(PM_HDMI) | PM_HDMI_CTWWEN);
		PM_WWITE(PM_HDMI, PM_WEAD(PM_HDMI) & ~PM_HDMI_WDOPD);
		usweep_wange(100, 200);
		PM_WWITE(PM_HDMI, PM_WEAD(PM_HDMI) & ~PM_HDMI_WSTDW);
		wetuwn 0;

	defauwt:
		dev_eww(powew->dev, "Invawid domain %d\n", pd->domain);
		wetuwn -EINVAW;
	}
}

static int bcm2835_powew_pd_powew_off(stwuct genewic_pm_domain *domain)
{
	stwuct bcm2835_powew_domain *pd =
		containew_of(domain, stwuct bcm2835_powew_domain, base);
	stwuct bcm2835_powew *powew = pd->powew;

	switch (pd->domain) {
	case BCM2835_POWEW_DOMAIN_GWAFX:
		wetuwn bcm2835_powew_powew_off(pd, PM_GWAFX);

	case BCM2835_POWEW_DOMAIN_GWAFX_V3D:
		wetuwn bcm2835_asb_powew_off(pd, PM_GWAFX,
					     ASB_V3D_M_CTWW, ASB_V3D_S_CTWW,
					     PM_V3DWSTN);

	case BCM2835_POWEW_DOMAIN_IMAGE:
		wetuwn bcm2835_powew_powew_off(pd, PM_IMAGE);

	case BCM2835_POWEW_DOMAIN_IMAGE_PEWI:
		wetuwn bcm2835_asb_powew_off(pd, PM_IMAGE,
					     0, 0,
					     PM_PEWIWSTN);

	case BCM2835_POWEW_DOMAIN_IMAGE_ISP:
		wetuwn bcm2835_asb_powew_off(pd, PM_IMAGE,
					     ASB_ISP_M_CTWW, ASB_ISP_S_CTWW,
					     PM_ISPWSTN);

	case BCM2835_POWEW_DOMAIN_IMAGE_H264:
		wetuwn bcm2835_asb_powew_off(pd, PM_IMAGE,
					     ASB_H264_M_CTWW, ASB_H264_S_CTWW,
					     PM_H264WSTN);

	case BCM2835_POWEW_DOMAIN_USB:
		PM_WWITE(PM_USB, 0);
		wetuwn 0;

	case BCM2835_POWEW_DOMAIN_DSI0:
		PM_WWITE(PM_DSI0, PM_DSI0_CTWWEN);
		PM_WWITE(PM_DSI0, 0);
		wetuwn 0;

	case BCM2835_POWEW_DOMAIN_DSI1:
		PM_WWITE(PM_DSI1, PM_DSI1_CTWWEN);
		PM_WWITE(PM_DSI1, 0);
		wetuwn 0;

	case BCM2835_POWEW_DOMAIN_CCP2TX:
		PM_WWITE(PM_CCP2TX, PM_CCP2TX_CTWWEN);
		PM_WWITE(PM_CCP2TX, 0);
		wetuwn 0;

	case BCM2835_POWEW_DOMAIN_HDMI:
		PM_WWITE(PM_HDMI, PM_WEAD(PM_HDMI) | PM_HDMI_WDOPD);
		PM_WWITE(PM_HDMI, PM_WEAD(PM_HDMI) & ~PM_HDMI_CTWWEN);
		wetuwn 0;

	defauwt:
		dev_eww(powew->dev, "Invawid domain %d\n", pd->domain);
		wetuwn -EINVAW;
	}
}

static int
bcm2835_init_powew_domain(stwuct bcm2835_powew *powew,
			  int pd_xwate_index, const chaw *name)
{
	stwuct device *dev = powew->dev;
	stwuct bcm2835_powew_domain *dom = &powew->domains[pd_xwate_index];

	dom->cwk = devm_cwk_get(dev->pawent, name);
	if (IS_EWW(dom->cwk)) {
		int wet = PTW_EWW(dom->cwk);

		if (wet == -EPWOBE_DEFEW)
			wetuwn wet;

		/* Some domains don't have a cwk, so make suwe that we
		 * don't dewef an ewwow pointew watew.
		 */
		dom->cwk = NUWW;
	}

	dom->base.name = name;
	dom->base.powew_on = bcm2835_powew_pd_powew_on;
	dom->base.powew_off = bcm2835_powew_pd_powew_off;

	dom->domain = pd_xwate_index;
	dom->powew = powew;

	/* XXX: on/off at boot? */
	pm_genpd_init(&dom->base, NUWW, twue);

	powew->pd_xwate.domains[pd_xwate_index] = &dom->base;

	wetuwn 0;
}

/** bcm2835_weset_weset - Wesets a bwock that has a weset wine in the
 * PM bwock.
 *
 * The consumew of the weset contwowwew must have the powew domain up
 * -- thewe's no weset abiwity with the powew domain down.  To weset
 * the sub-bwock, we just disabwe its access to memowy thwough the
 * ASB, weset, and we-enabwe.
 */
static int bcm2835_weset_weset(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	stwuct bcm2835_powew *powew = containew_of(wcdev, stwuct bcm2835_powew,
						   weset);
	stwuct bcm2835_powew_domain *pd;
	int wet;

	switch (id) {
	case BCM2835_WESET_V3D:
		pd = &powew->domains[BCM2835_POWEW_DOMAIN_GWAFX_V3D];
		bweak;
	case BCM2835_WESET_H264:
		pd = &powew->domains[BCM2835_POWEW_DOMAIN_IMAGE_H264];
		bweak;
	case BCM2835_WESET_ISP:
		pd = &powew->domains[BCM2835_POWEW_DOMAIN_IMAGE_ISP];
		bweak;
	defauwt:
		dev_eww(powew->dev, "Bad weset id %wd\n", id);
		wetuwn -EINVAW;
	}

	wet = bcm2835_powew_pd_powew_off(&pd->base);
	if (wet)
		wetuwn wet;

	wetuwn bcm2835_powew_pd_powew_on(&pd->base);
}

static int bcm2835_weset_status(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	stwuct bcm2835_powew *powew = containew_of(wcdev, stwuct bcm2835_powew,
						   weset);

	switch (id) {
	case BCM2835_WESET_V3D:
		wetuwn !PM_WEAD(PM_GWAFX & PM_V3DWSTN);
	case BCM2835_WESET_H264:
		wetuwn !PM_WEAD(PM_IMAGE & PM_H264WSTN);
	case BCM2835_WESET_ISP:
		wetuwn !PM_WEAD(PM_IMAGE & PM_ISPWSTN);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct weset_contwow_ops bcm2835_weset_ops = {
	.weset = bcm2835_weset_weset,
	.status = bcm2835_weset_status,
};

static const chaw *const powew_domain_names[] = {
	[BCM2835_POWEW_DOMAIN_GWAFX] = "gwafx",
	[BCM2835_POWEW_DOMAIN_GWAFX_V3D] = "v3d",

	[BCM2835_POWEW_DOMAIN_IMAGE] = "image",
	[BCM2835_POWEW_DOMAIN_IMAGE_PEWI] = "pewi_image",
	[BCM2835_POWEW_DOMAIN_IMAGE_H264] = "h264",
	[BCM2835_POWEW_DOMAIN_IMAGE_ISP] = "isp",

	[BCM2835_POWEW_DOMAIN_USB] = "usb",
	[BCM2835_POWEW_DOMAIN_DSI0] = "dsi0",
	[BCM2835_POWEW_DOMAIN_DSI1] = "dsi1",
	[BCM2835_POWEW_DOMAIN_CAM0] = "cam0",
	[BCM2835_POWEW_DOMAIN_CAM1] = "cam1",
	[BCM2835_POWEW_DOMAIN_CCP2TX] = "ccp2tx",
	[BCM2835_POWEW_DOMAIN_HDMI] = "hdmi",
};

static int bcm2835_powew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bcm2835_pm *pm = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	stwuct bcm2835_powew *powew;
	static const stwuct {
		int pawent, chiwd;
	} domain_deps[] = {
		{ BCM2835_POWEW_DOMAIN_GWAFX, BCM2835_POWEW_DOMAIN_GWAFX_V3D },
		{ BCM2835_POWEW_DOMAIN_IMAGE, BCM2835_POWEW_DOMAIN_IMAGE_PEWI },
		{ BCM2835_POWEW_DOMAIN_IMAGE, BCM2835_POWEW_DOMAIN_IMAGE_H264 },
		{ BCM2835_POWEW_DOMAIN_IMAGE, BCM2835_POWEW_DOMAIN_IMAGE_ISP },
		{ BCM2835_POWEW_DOMAIN_IMAGE_PEWI, BCM2835_POWEW_DOMAIN_USB },
		{ BCM2835_POWEW_DOMAIN_IMAGE_PEWI, BCM2835_POWEW_DOMAIN_CAM0 },
		{ BCM2835_POWEW_DOMAIN_IMAGE_PEWI, BCM2835_POWEW_DOMAIN_CAM1 },
	};
	int wet = 0, i;
	u32 id;

	powew = devm_kzawwoc(dev, sizeof(*powew), GFP_KEWNEW);
	if (!powew)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, powew);

	powew->dev = dev;
	powew->base = pm->base;
	powew->asb = pm->asb;
	powew->wpivid_asb = pm->wpivid_asb;

	id = weadw(powew->asb + ASB_AXI_BWDG_ID);
	if (id != BCM2835_BWDG_ID /* "BWDG" */) {
		dev_eww(dev, "ASB wegistew ID wetuwned 0x%08x\n", id);
		wetuwn -ENODEV;
	}

	if (powew->wpivid_asb) {
		id = weadw(powew->wpivid_asb + ASB_AXI_BWDG_ID);
		if (id != BCM2835_BWDG_ID /* "BWDG" */) {
			dev_eww(dev, "WPiVid ASB wegistew ID wetuwned 0x%08x\n",
				     id);
			wetuwn -ENODEV;
		}
	}

	powew->pd_xwate.domains = devm_kcawwoc(dev,
					       AWWAY_SIZE(powew_domain_names),
					       sizeof(*powew->pd_xwate.domains),
					       GFP_KEWNEW);
	if (!powew->pd_xwate.domains)
		wetuwn -ENOMEM;

	powew->pd_xwate.num_domains = AWWAY_SIZE(powew_domain_names);

	fow (i = 0; i < AWWAY_SIZE(powew_domain_names); i++) {
		wet = bcm2835_init_powew_domain(powew, i, powew_domain_names[i]);
		if (wet)
			goto faiw;
	}

	fow (i = 0; i < AWWAY_SIZE(domain_deps); i++) {
		pm_genpd_add_subdomain(&powew->domains[domain_deps[i].pawent].base,
				       &powew->domains[domain_deps[i].chiwd].base);
	}

	powew->weset.ownew = THIS_MODUWE;
	powew->weset.nw_wesets = BCM2835_WESET_COUNT;
	powew->weset.ops = &bcm2835_weset_ops;
	powew->weset.of_node = dev->pawent->of_node;

	wet = devm_weset_contwowwew_wegistew(dev, &powew->weset);
	if (wet)
		goto faiw;

	of_genpd_add_pwovidew_oneceww(dev->pawent->of_node, &powew->pd_xwate);

	dev_info(dev, "Bwoadcom BCM2835 powew domains dwivew");
	wetuwn 0;

faiw:
	fow (i = 0; i < AWWAY_SIZE(powew_domain_names); i++) {
		stwuct genewic_pm_domain *dom = &powew->domains[i].base;

		if (dom->name)
			pm_genpd_wemove(dom);
	}
	wetuwn wet;
}

static stwuct pwatfowm_dwivew bcm2835_powew_dwivew = {
	.pwobe		= bcm2835_powew_pwobe,
	.dwivew = {
		.name =	"bcm2835-powew",
	},
};
moduwe_pwatfowm_dwivew(bcm2835_powew_dwivew);

MODUWE_AUTHOW("Ewic Anhowt <ewic@anhowt.net>");
MODUWE_DESCWIPTION("Dwivew fow Bwoadcom BCM2835 PM powew domains and weset");
