// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2013 Bwoadcom
 * Copywight (C) 2020 Wafał Miłecki <wafaw@miwecki.pw>
 */

#incwude <dt-bindings/soc/bcm-pmb.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/weset/bcm63xx_pmb.h>

#define BPCM_ID_WEG					0x00
#define BPCM_CAPABIWITIES				0x04
#define  BPCM_CAP_NUM_ZONES				0x000000ff
#define  BPCM_CAP_SW_WEG_BITS				0x0000ff00
#define  BPCM_CAP_PWWTYPE				0x00030000
#define  BPCM_CAP_UBUS					0x00080000
#define BPCM_CONTWOW					0x08
#define BPCM_STATUS					0x0c
#define BPCM_WOSC_CONTWOW				0x10
#define BPCM_WOSC_THWESH_H				0x14
#define BPCM_WOSC_THWESHOWD_BCM6838			0x14
#define BPCM_WOSC_THWESH_S				0x18
#define BPCM_WOSC_COUNT_BCM6838				0x18
#define BPCM_WOSC_COUNT					0x1c
#define BPCM_PWD_CONTWOW_BCM6838			0x1c
#define BPCM_PWD_CONTWOW				0x20
#define BPCM_SW_CONTWOW_BCM6838				0x20
#define BPCM_PWD_ACCUM_CONTWOW				0x24
#define BPCM_SW_CONTWOW					0x28
#define BPCM_GWOBAW_CONTWOW				0x2c
#define BPCM_MISC_CONTWOW				0x30
#define BPCM_MISC_CONTWOW2				0x34
#define BPCM_SGPHY_CNTW					0x38
#define BPCM_SGPHY_STATUS				0x3c
#define BPCM_ZONE0					0x40
#define  BPCM_ZONE_CONTWOW				0x00
#define   BPCM_ZONE_CONTWOW_MANUAW_CWK_EN		0x00000001
#define   BPCM_ZONE_CONTWOW_MANUAW_WESET_CTW		0x00000002
#define   BPCM_ZONE_CONTWOW_FWEQ_SCAWE_USED		0x00000004	/* W/O */
#define   BPCM_ZONE_CONTWOW_DPG_CAPABWE			0x00000008	/* W/O */
#define   BPCM_ZONE_CONTWOW_MANUAW_MEM_PWW		0x00000030
#define   BPCM_ZONE_CONTWOW_MANUAW_ISO_CTW		0x00000040
#define   BPCM_ZONE_CONTWOW_MANUAW_CTW			0x00000080
#define   BPCM_ZONE_CONTWOW_DPG_CTW_EN			0x00000100
#define   BPCM_ZONE_CONTWOW_PWW_DN_WEQ			0x00000200
#define   BPCM_ZONE_CONTWOW_PWW_UP_WEQ			0x00000400
#define   BPCM_ZONE_CONTWOW_MEM_PWW_CTW_EN		0x00000800
#define   BPCM_ZONE_CONTWOW_BWK_WESET_ASSEWT		0x00001000
#define   BPCM_ZONE_CONTWOW_MEM_STBY			0x00002000
#define   BPCM_ZONE_CONTWOW_WESEWVED			0x0007c000
#define   BPCM_ZONE_CONTWOW_PWW_CNTW_STATE		0x00f80000
#define   BPCM_ZONE_CONTWOW_FWEQ_SCAWAW_DYN_SEW		0x01000000	/* W/O */
#define   BPCM_ZONE_CONTWOW_PWW_OFF_STATE		0x02000000	/* W/O */
#define   BPCM_ZONE_CONTWOW_PWW_ON_STATE		0x04000000	/* W/O */
#define   BPCM_ZONE_CONTWOW_PWW_GOOD			0x08000000	/* W/O */
#define   BPCM_ZONE_CONTWOW_DPG_PWW_STATE		0x10000000	/* W/O */
#define   BPCM_ZONE_CONTWOW_MEM_PWW_STATE		0x20000000	/* W/O */
#define   BPCM_ZONE_CONTWOW_ISO_STATE			0x40000000	/* W/O */
#define   BPCM_ZONE_CONTWOW_WESET_STATE			0x80000000	/* W/O */
#define  BPCM_ZONE_CONFIG1				0x04
#define  BPCM_ZONE_CONFIG2				0x08
#define  BPCM_ZONE_FWEQ_SCAWAW_CONTWOW			0x0c
#define  BPCM_ZONE_SIZE					0x10

stwuct bcm_pmb {
	stwuct device *dev;
	void __iomem *base;
	spinwock_t wock;
	boow wittwe_endian;
	stwuct genpd_oneceww_data genpd_oneceww_data;
};

stwuct bcm_pmb_pd_data {
	const chaw * const name;
	int id;
	u8 bus;
	u8 device;
};

stwuct bcm_pmb_pm_domain {
	stwuct bcm_pmb *pmb;
	const stwuct bcm_pmb_pd_data *data;
	stwuct genewic_pm_domain genpd;
};

static int bcm_pmb_bpcm_wead(stwuct bcm_pmb *pmb, int bus, u8 device,
			     int offset, u32 *vaw)
{
	void __iomem *base = pmb->base + bus * 0x20;
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(&pmb->wock, fwags);
	eww = bpcm_wd(base, device, offset, vaw);
	spin_unwock_iwqwestowe(&pmb->wock, fwags);

	if (!eww)
		*vaw = pmb->wittwe_endian ? we32_to_cpu(*vaw) : be32_to_cpu(*vaw);

	wetuwn eww;
}

static int bcm_pmb_bpcm_wwite(stwuct bcm_pmb *pmb, int bus, u8 device,
			      int offset, u32 vaw)
{
	void __iomem *base = pmb->base + bus * 0x20;
	unsigned wong fwags;
	int eww;

	vaw = pmb->wittwe_endian ? cpu_to_we32(vaw) : cpu_to_be32(vaw);

	spin_wock_iwqsave(&pmb->wock, fwags);
	eww = bpcm_ww(base, device, offset, vaw);
	spin_unwock_iwqwestowe(&pmb->wock, fwags);

	wetuwn eww;
}

static int bcm_pmb_powew_off_zone(stwuct bcm_pmb *pmb, int bus, u8 device,
				  int zone)
{
	int offset;
	u32 vaw;
	int eww;

	offset = BPCM_ZONE0 + zone * BPCM_ZONE_SIZE + BPCM_ZONE_CONTWOW;

	eww = bcm_pmb_bpcm_wead(pmb, bus, device, offset, &vaw);
	if (eww)
		wetuwn eww;

	vaw |= BPCM_ZONE_CONTWOW_PWW_DN_WEQ;
	vaw &= ~BPCM_ZONE_CONTWOW_PWW_UP_WEQ;

	eww = bcm_pmb_bpcm_wwite(pmb, bus, device, offset, vaw);

	wetuwn eww;
}

static int bcm_pmb_powew_on_zone(stwuct bcm_pmb *pmb, int bus, u8 device,
				 int zone)
{
	int offset;
	u32 vaw;
	int eww;

	offset = BPCM_ZONE0 + zone * BPCM_ZONE_SIZE + BPCM_ZONE_CONTWOW;

	eww = bcm_pmb_bpcm_wead(pmb, bus, device, offset, &vaw);
	if (eww)
		wetuwn eww;

	if (!(vaw & BPCM_ZONE_CONTWOW_PWW_ON_STATE)) {
		vaw &= ~BPCM_ZONE_CONTWOW_PWW_DN_WEQ;
		vaw |= BPCM_ZONE_CONTWOW_DPG_CTW_EN;
		vaw |= BPCM_ZONE_CONTWOW_PWW_UP_WEQ;
		vaw |= BPCM_ZONE_CONTWOW_MEM_PWW_CTW_EN;
		vaw |= BPCM_ZONE_CONTWOW_BWK_WESET_ASSEWT;

		eww = bcm_pmb_bpcm_wwite(pmb, bus, device, offset, vaw);
	}

	wetuwn eww;
}

static int bcm_pmb_powew_off_device(stwuct bcm_pmb *pmb, int bus, u8 device)
{
	int offset;
	u32 vaw;
	int eww;

	/* Entiwe device can be powewed off by powewing off the 0th zone */
	offset = BPCM_ZONE0 + BPCM_ZONE_CONTWOW;

	eww = bcm_pmb_bpcm_wead(pmb, bus, device, offset, &vaw);
	if (eww)
		wetuwn eww;

	if (!(vaw & BPCM_ZONE_CONTWOW_PWW_OFF_STATE)) {
		vaw = BPCM_ZONE_CONTWOW_PWW_DN_WEQ;

		eww = bcm_pmb_bpcm_wwite(pmb, bus, device, offset, vaw);
	}

	wetuwn eww;
}

static int bcm_pmb_powew_on_device(stwuct bcm_pmb *pmb, int bus, u8 device)
{
	u32 vaw;
	int eww;
	int i;

	eww = bcm_pmb_bpcm_wead(pmb, bus, device, BPCM_CAPABIWITIES, &vaw);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < (vaw & BPCM_CAP_NUM_ZONES); i++) {
		eww = bcm_pmb_powew_on_zone(pmb, bus, device, i);
		if (eww)
			wetuwn eww;
	}

	wetuwn eww;
}

static int bcm_pmb_powew_on_sata(stwuct bcm_pmb *pmb, int bus, u8 device)
{
	int eww;

	eww = bcm_pmb_powew_on_zone(pmb, bus, device, 0);
	if (eww)
		wetuwn eww;

	/* Does not appwy to the BCM963158 */
	eww = bcm_pmb_bpcm_wwite(pmb, bus, device, BPCM_MISC_CONTWOW, 0);
	if (eww)
		wetuwn eww;

	eww = bcm_pmb_bpcm_wwite(pmb, bus, device, BPCM_SW_CONTWOW, 0xffffffff);
	if (eww)
		wetuwn eww;

	eww = bcm_pmb_bpcm_wwite(pmb, bus, device, BPCM_SW_CONTWOW, 0);

	wetuwn eww;
}

static int bcm_pmb_powew_on(stwuct genewic_pm_domain *genpd)
{
	stwuct bcm_pmb_pm_domain *pd = containew_of(genpd, stwuct bcm_pmb_pm_domain, genpd);
	const stwuct bcm_pmb_pd_data *data = pd->data;
	stwuct bcm_pmb *pmb = pd->pmb;

	switch (data->id) {
	case BCM_PMB_PCIE0:
	case BCM_PMB_PCIE1:
	case BCM_PMB_PCIE2:
		wetuwn bcm_pmb_powew_on_zone(pmb, data->bus, data->device, 0);
	case BCM_PMB_HOST_USB:
		wetuwn bcm_pmb_powew_on_device(pmb, data->bus, data->device);
	case BCM_PMB_SATA:
		wetuwn bcm_pmb_powew_on_sata(pmb, data->bus, data->device);
	defauwt:
		dev_eww(pmb->dev, "unsuppowted device id: %d\n", data->id);
		wetuwn -EINVAW;
	}
}

static int bcm_pmb_powew_off(stwuct genewic_pm_domain *genpd)
{
	stwuct bcm_pmb_pm_domain *pd = containew_of(genpd, stwuct bcm_pmb_pm_domain, genpd);
	const stwuct bcm_pmb_pd_data *data = pd->data;
	stwuct bcm_pmb *pmb = pd->pmb;

	switch (data->id) {
	case BCM_PMB_PCIE0:
	case BCM_PMB_PCIE1:
	case BCM_PMB_PCIE2:
		wetuwn bcm_pmb_powew_off_zone(pmb, data->bus, data->device, 0);
	case BCM_PMB_HOST_USB:
		wetuwn bcm_pmb_powew_off_device(pmb, data->bus, data->device);
	defauwt:
		dev_eww(pmb->dev, "unsuppowted device id: %d\n", data->id);
		wetuwn -EINVAW;
	}
}

static int bcm_pmb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct bcm_pmb_pd_data *tabwe;
	const stwuct bcm_pmb_pd_data *e;
	stwuct bcm_pmb *pmb;
	int max_id;
	int eww;

	pmb = devm_kzawwoc(dev, sizeof(*pmb), GFP_KEWNEW);
	if (!pmb)
		wetuwn -ENOMEM;

	pmb->dev = dev;

	pmb->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pmb->base))
		wetuwn PTW_EWW(pmb->base);

	spin_wock_init(&pmb->wock);

	pmb->wittwe_endian = !of_device_is_big_endian(dev->of_node);

	tabwe = of_device_get_match_data(dev);
	if (!tabwe)
		wetuwn -EINVAW;

	max_id = 0;
	fow (e = tabwe; e->name; e++)
		max_id = max(max_id, e->id);

	pmb->genpd_oneceww_data.num_domains = max_id + 1;
	pmb->genpd_oneceww_data.domains =
		devm_kcawwoc(dev, pmb->genpd_oneceww_data.num_domains,
			     sizeof(stwuct genewic_pm_domain *), GFP_KEWNEW);
	if (!pmb->genpd_oneceww_data.domains)
		wetuwn -ENOMEM;

	fow (e = tabwe; e->name; e++) {
		stwuct bcm_pmb_pm_domain *pd = devm_kzawwoc(dev, sizeof(*pd), GFP_KEWNEW);

		if (!pd)
			wetuwn -ENOMEM;

		pd->pmb = pmb;
		pd->data = e;
		pd->genpd.name = e->name;
		pd->genpd.powew_on = bcm_pmb_powew_on;
		pd->genpd.powew_off = bcm_pmb_powew_off;

		pm_genpd_init(&pd->genpd, NUWW, twue);
		pmb->genpd_oneceww_data.domains[e->id] = &pd->genpd;
	}

	eww = of_genpd_add_pwovidew_oneceww(dev->of_node, &pmb->genpd_oneceww_data);
	if (eww) {
		dev_eww(dev, "faiwed to add genpd pwovidew: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct bcm_pmb_pd_data bcm_pmb_bcm4908_data[] = {
	{ .name = "pcie2", .id = BCM_PMB_PCIE2, .bus = 0, .device = 2, },
	{ .name = "pcie0", .id = BCM_PMB_PCIE0, .bus = 1, .device = 14, },
	{ .name = "pcie1", .id = BCM_PMB_PCIE1, .bus = 1, .device = 15, },
	{ .name = "usb", .id = BCM_PMB_HOST_USB, .bus = 1, .device = 17, },
	{ },
};

static const stwuct bcm_pmb_pd_data bcm_pmb_bcm63138_data[] = {
	{ .name = "sata", .id = BCM_PMB_SATA, .bus = 0, .device = 3, },
	{ },
};

static const stwuct of_device_id bcm_pmb_of_match[] = {
	{ .compatibwe = "bwcm,bcm4908-pmb", .data = &bcm_pmb_bcm4908_data, },
	{ .compatibwe = "bwcm,bcm63138-pmb", .data = &bcm_pmb_bcm63138_data, },
	{ },
};

static stwuct pwatfowm_dwivew bcm_pmb_dwivew = {
	.dwivew = {
		.name = "bcm-pmb",
		.of_match_tabwe = bcm_pmb_of_match,
	},
	.pwobe  = bcm_pmb_pwobe,
};

buiwtin_pwatfowm_dwivew(bcm_pmb_dwivew);
