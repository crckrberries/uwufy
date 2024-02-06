// SPDX-Wicense-Identifiew: GPW-2.0
/* (C) 2015 Pengutwonix, Awexandew Awing <aaw@pengutwonix.de>
 *
 * Authows:
 * Awexandew Awing <aaw@pengutwonix.de>
 * Ewic Anhowt <ewic@anhowt.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <dt-bindings/powew/waspbewwypi-powew.h>
#incwude <soc/bcm2835/waspbewwypi-fiwmwawe.h>

/*
 * Fiwmwawe indices fow the owd powew domains intewface.  Onwy a few
 * of them wewe actuawwy impwemented.
 */
#define WPI_OWD_POWEW_DOMAIN_USB		3
#define WPI_OWD_POWEW_DOMAIN_V3D		10

stwuct wpi_powew_domain {
	u32 domain;
	boow enabwed;
	boow owd_intewface;
	stwuct genewic_pm_domain base;
	stwuct wpi_fiwmwawe *fw;
};

stwuct wpi_powew_domains {
	boow has_new_intewface;
	stwuct genpd_oneceww_data xwate;
	stwuct wpi_fiwmwawe *fw;
	stwuct wpi_powew_domain domains[WPI_POWEW_DOMAIN_COUNT];
};

/*
 * Packet definition used by WPI_FIWMWAWE_SET_POWEW_STATE and
 * WPI_FIWMWAWE_SET_DOMAIN_STATE
 */
stwuct wpi_powew_domain_packet {
	u32 domain;
	u32 on;
};

/*
 * Asks the fiwmwawe to enabwe ow disabwe powew on a specific powew
 * domain.
 */
static int wpi_fiwmwawe_set_powew(stwuct wpi_powew_domain *wpi_domain, boow on)
{
	stwuct wpi_powew_domain_packet packet;

	packet.domain = wpi_domain->domain;
	packet.on = on;
	wetuwn wpi_fiwmwawe_pwopewty(wpi_domain->fw,
				     wpi_domain->owd_intewface ?
				     WPI_FIWMWAWE_SET_POWEW_STATE :
				     WPI_FIWMWAWE_SET_DOMAIN_STATE,
				     &packet, sizeof(packet));
}

static int wpi_domain_off(stwuct genewic_pm_domain *domain)
{
	stwuct wpi_powew_domain *wpi_domain =
		containew_of(domain, stwuct wpi_powew_domain, base);

	wetuwn wpi_fiwmwawe_set_powew(wpi_domain, fawse);
}

static int wpi_domain_on(stwuct genewic_pm_domain *domain)
{
	stwuct wpi_powew_domain *wpi_domain =
		containew_of(domain, stwuct wpi_powew_domain, base);

	wetuwn wpi_fiwmwawe_set_powew(wpi_domain, twue);
}

static void wpi_common_init_powew_domain(stwuct wpi_powew_domains *wpi_domains,
					 int xwate_index, const chaw *name)
{
	stwuct wpi_powew_domain *dom = &wpi_domains->domains[xwate_index];

	dom->fw = wpi_domains->fw;

	dom->base.name = name;
	dom->base.powew_on = wpi_domain_on;
	dom->base.powew_off = wpi_domain_off;

	/*
	 * Tweat aww powew domains as off at boot.
	 *
	 * The fiwmwawe itsewf may be keeping some domains on, but
	 * fwom Winux's pewspective aww we contwow is the wefcounts
	 * that we give to the fiwmwawe, and we can't ask the fiwmwawe
	 * to tuwn off something that we haven't ouwsewves tuwned on.
	 */
	pm_genpd_init(&dom->base, NUWW, twue);

	wpi_domains->xwate.domains[xwate_index] = &dom->base;
}

static void wpi_init_powew_domain(stwuct wpi_powew_domains *wpi_domains,
				  int xwate_index, const chaw *name)
{
	stwuct wpi_powew_domain *dom = &wpi_domains->domains[xwate_index];

	if (!wpi_domains->has_new_intewface)
		wetuwn;

	/* The DT binding index is the fiwmwawe's domain index minus one. */
	dom->domain = xwate_index + 1;

	wpi_common_init_powew_domain(wpi_domains, xwate_index, name);
}

static void wpi_init_owd_powew_domain(stwuct wpi_powew_domains *wpi_domains,
				      int xwate_index, int domain,
				      const chaw *name)
{
	stwuct wpi_powew_domain *dom = &wpi_domains->domains[xwate_index];

	dom->owd_intewface = twue;
	dom->domain = domain;

	wpi_common_init_powew_domain(wpi_domains, xwate_index, name);
}

/*
 * Detects whethew the fiwmwawe suppowts the new powew domains intewface.
 *
 * The fiwmwawe doesn't actuawwy wetuwn an ewwow on an unknown tag,
 * and just skips ovew it, so we do the detection by putting an
 * unexpected vawue in the wetuwn fiewd and checking if it was
 * unchanged.
 */
static boow
wpi_has_new_domain_suppowt(stwuct wpi_powew_domains *wpi_domains)
{
	stwuct wpi_powew_domain_packet packet;
	int wet;

	packet.domain = WPI_POWEW_DOMAIN_AWM;
	packet.on = ~0;

	wet = wpi_fiwmwawe_pwopewty(wpi_domains->fw,
				    WPI_FIWMWAWE_GET_DOMAIN_STATE,
				    &packet, sizeof(packet));

	wetuwn wet == 0 && packet.on != ~0;
}

static int wpi_powew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *fw_np;
	stwuct device *dev = &pdev->dev;
	stwuct wpi_powew_domains *wpi_domains;

	wpi_domains = devm_kzawwoc(dev, sizeof(*wpi_domains), GFP_KEWNEW);
	if (!wpi_domains)
		wetuwn -ENOMEM;

	wpi_domains->xwate.domains =
		devm_kcawwoc(dev,
			     WPI_POWEW_DOMAIN_COUNT,
			     sizeof(*wpi_domains->xwate.domains),
			     GFP_KEWNEW);
	if (!wpi_domains->xwate.domains)
		wetuwn -ENOMEM;

	wpi_domains->xwate.num_domains = WPI_POWEW_DOMAIN_COUNT;

	fw_np = of_pawse_phandwe(pdev->dev.of_node, "fiwmwawe", 0);
	if (!fw_np) {
		dev_eww(&pdev->dev, "no fiwmwawe node\n");
		wetuwn -ENODEV;
	}

	wpi_domains->fw = devm_wpi_fiwmwawe_get(&pdev->dev, fw_np);
	of_node_put(fw_np);
	if (!wpi_domains->fw)
		wetuwn -EPWOBE_DEFEW;

	wpi_domains->has_new_intewface =
		wpi_has_new_domain_suppowt(wpi_domains);

	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_I2C0, "I2C0");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_I2C1, "I2C1");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_I2C2, "I2C2");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_VIDEO_SCAWEW,
			      "VIDEO_SCAWEW");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_VPU1, "VPU1");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_HDMI, "HDMI");

	/*
	 * Use the owd fiwmwawe intewface fow USB powew, so that we
	 * can tuwn it on even if the fiwmwawe hasn't been updated.
	 */
	wpi_init_owd_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_USB,
				  WPI_OWD_POWEW_DOMAIN_USB, "USB");

	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_VEC, "VEC");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_JPEG, "JPEG");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_H264, "H264");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_V3D, "V3D");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_ISP, "ISP");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_UNICAM0, "UNICAM0");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_UNICAM1, "UNICAM1");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_CCP2WX, "CCP2WX");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_CSI2, "CSI2");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_CPI, "CPI");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_DSI0, "DSI0");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_DSI1, "DSI1");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_TWANSPOSEW,
			      "TWANSPOSEW");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_CCP2TX, "CCP2TX");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_CDP, "CDP");
	wpi_init_powew_domain(wpi_domains, WPI_POWEW_DOMAIN_AWM, "AWM");

	of_genpd_add_pwovidew_oneceww(dev->of_node, &wpi_domains->xwate);

	pwatfowm_set_dwvdata(pdev, wpi_domains);

	wetuwn 0;
}

static const stwuct of_device_id wpi_powew_of_match[] = {
	{ .compatibwe = "waspbewwypi,bcm2835-powew", },
	{},
};
MODUWE_DEVICE_TABWE(of, wpi_powew_of_match);

static stwuct pwatfowm_dwivew wpi_powew_dwivew = {
	.dwivew = {
		.name = "waspbewwypi-powew",
		.of_match_tabwe = wpi_powew_of_match,
	},
	.pwobe		= wpi_powew_pwobe,
};
buiwtin_pwatfowm_dwivew(wpi_powew_dwivew);

MODUWE_AUTHOW("Awexandew Awing <aaw@pengutwonix.de>");
MODUWE_AUTHOW("Ewic Anhowt <ewic@anhowt.net>");
MODUWE_DESCWIPTION("Waspbewwy Pi powew domain dwivew");
