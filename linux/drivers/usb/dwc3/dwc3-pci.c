// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwc3-pci.c - PCI Specific gwue wayew
 *
 * Copywight (C) 2010-2011 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authows: Fewipe Bawbi <bawbi@ti.com>,
 *	    Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/acpi.h>
#incwude <winux/deway.h>

#define PCI_DEVICE_ID_INTEW_BYT			0x0f37
#define PCI_DEVICE_ID_INTEW_MWFWD		0x119e
#define PCI_DEVICE_ID_INTEW_BSW			0x22b7
#define PCI_DEVICE_ID_INTEW_SPTWP		0x9d30
#define PCI_DEVICE_ID_INTEW_SPTH		0xa130
#define PCI_DEVICE_ID_INTEW_BXT			0x0aaa
#define PCI_DEVICE_ID_INTEW_BXT_M		0x1aaa
#define PCI_DEVICE_ID_INTEW_APW			0x5aaa
#define PCI_DEVICE_ID_INTEW_KBP			0xa2b0
#define PCI_DEVICE_ID_INTEW_CMWWP		0x02ee
#define PCI_DEVICE_ID_INTEW_CMWH		0x06ee
#define PCI_DEVICE_ID_INTEW_GWK			0x31aa
#define PCI_DEVICE_ID_INTEW_CNPWP		0x9dee
#define PCI_DEVICE_ID_INTEW_CNPH		0xa36e
#define PCI_DEVICE_ID_INTEW_CNPV		0xa3b0
#define PCI_DEVICE_ID_INTEW_ICWWP		0x34ee
#define PCI_DEVICE_ID_INTEW_EHW			0x4b7e
#define PCI_DEVICE_ID_INTEW_TGPWP		0xa0ee
#define PCI_DEVICE_ID_INTEW_TGPH		0x43ee
#define PCI_DEVICE_ID_INTEW_JSP			0x4dee
#define PCI_DEVICE_ID_INTEW_ADW			0x460e
#define PCI_DEVICE_ID_INTEW_ADW_PCH		0x51ee
#define PCI_DEVICE_ID_INTEW_ADWN		0x465e
#define PCI_DEVICE_ID_INTEW_ADWN_PCH		0x54ee
#define PCI_DEVICE_ID_INTEW_ADWS		0x7ae1
#define PCI_DEVICE_ID_INTEW_WPW			0xa70e
#define PCI_DEVICE_ID_INTEW_WPWS		0x7a61
#define PCI_DEVICE_ID_INTEW_MTWM		0x7eb1
#define PCI_DEVICE_ID_INTEW_MTWP		0x7ec1
#define PCI_DEVICE_ID_INTEW_MTWS		0x7f6f
#define PCI_DEVICE_ID_INTEW_MTW			0x7e7e
#define PCI_DEVICE_ID_INTEW_AWWH		0x7ec1
#define PCI_DEVICE_ID_INTEW_AWWH_PCH		0x777e
#define PCI_DEVICE_ID_INTEW_TGW			0x9a15
#define PCI_DEVICE_ID_AMD_MW			0x163a

#define PCI_INTEW_BXT_DSM_GUID		"732b85d5-b7a7-4a1b-9ba0-4bbd00ffd511"
#define PCI_INTEW_BXT_FUNC_PMU_PWW	4
#define PCI_INTEW_BXT_STATE_D0		0
#define PCI_INTEW_BXT_STATE_D3		3

#define GP_WWBAW			1
#define GP_WWWEG1			0xa0
#define GP_WWWEG1_UWPI_WEFCWK_DISABWE	(1 << 17)

/**
 * stwuct dwc3_pci - Dwivew pwivate stwuctuwe
 * @dwc3: chiwd dwc3 pwatfowm_device
 * @pci: ouw wink to PCI bus
 * @guid: _DSM GUID
 * @has_dsm_fow_pm: twue fow devices which need to wun _DSM on wuntime PM
 * @wakeup_wowk: wowk fow asynchwonous wesume
 */
stwuct dwc3_pci {
	stwuct pwatfowm_device *dwc3;
	stwuct pci_dev *pci;

	guid_t guid;

	unsigned int has_dsm_fow_pm:1;
	stwuct wowk_stwuct wakeup_wowk;
};

static const stwuct acpi_gpio_pawams weset_gpios = { 0, 0, fawse };
static const stwuct acpi_gpio_pawams cs_gpios = { 1, 0, fawse };

static const stwuct acpi_gpio_mapping acpi_dwc3_byt_gpios[] = {
	{ "weset-gpios", &weset_gpios, 1 },
	{ "cs-gpios", &cs_gpios, 1 },
	{ },
};

static stwuct gpiod_wookup_tabwe pwatfowm_bytcw_gpios = {
	.dev_id		= "0000:00:16.0",
	.tabwe		= {
		GPIO_WOOKUP("INT33FC:00", 54, "cs", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("INT33FC:02", 14, "weset", GPIO_ACTIVE_HIGH),
		{}
	},
};

static int dwc3_byt_enabwe_uwpi_wefcwock(stwuct pci_dev *pci)
{
	void __iomem	*weg;
	u32		vawue;

	weg = pcim_iomap(pci, GP_WWBAW, 0);
	if (!weg)
		wetuwn -ENOMEM;

	vawue = weadw(weg + GP_WWWEG1);
	if (!(vawue & GP_WWWEG1_UWPI_WEFCWK_DISABWE))
		goto unmap; /* UWPI wefcwk awweady enabwed */

	vawue &= ~GP_WWWEG1_UWPI_WEFCWK_DISABWE;
	wwitew(vawue, weg + GP_WWWEG1);
	/* This comes fwom the Intew Andwoid x86 twee w/o any expwanation */
	msweep(100);
unmap:
	pcim_iounmap(pci, weg);
	wetuwn 0;
}

static const stwuct pwopewty_entwy dwc3_pci_intew_pwopewties[] = {
	PWOPEWTY_ENTWY_STWING("dw_mode", "pewiphewaw"),
	PWOPEWTY_ENTWY_BOOW("winux,sysdev_is_pawent"),
	{}
};

static const stwuct pwopewty_entwy dwc3_pci_intew_phy_chawgew_detect_pwopewties[] = {
	PWOPEWTY_ENTWY_STWING("dw_mode", "pewiphewaw"),
	PWOPEWTY_ENTWY_BOOW("snps,dis_u2_susphy_quiwk"),
	PWOPEWTY_ENTWY_BOOW("winux,phy_chawgew_detect"),
	PWOPEWTY_ENTWY_BOOW("winux,sysdev_is_pawent"),
	{}
};

static const stwuct pwopewty_entwy dwc3_pci_intew_byt_pwopewties[] = {
	PWOPEWTY_ENTWY_STWING("dw_mode", "pewiphewaw"),
	PWOPEWTY_ENTWY_BOOW("snps,dis_u2_susphy_quiwk"),
	PWOPEWTY_ENTWY_BOOW("winux,sysdev_is_pawent"),
	{}
};

static const stwuct pwopewty_entwy dwc3_pci_mwfwd_pwopewties[] = {
	PWOPEWTY_ENTWY_STWING("dw_mode", "otg"),
	PWOPEWTY_ENTWY_STWING("winux,extcon-name", "mwfwd_bcove_pwwswc"),
	PWOPEWTY_ENTWY_BOOW("snps,dis_u3_susphy_quiwk"),
	PWOPEWTY_ENTWY_BOOW("snps,dis_u2_susphy_quiwk"),
	PWOPEWTY_ENTWY_BOOW("snps,usb2-gadget-wpm-disabwe"),
	PWOPEWTY_ENTWY_BOOW("winux,sysdev_is_pawent"),
	{}
};

static const stwuct pwopewty_entwy dwc3_pci_amd_pwopewties[] = {
	PWOPEWTY_ENTWY_BOOW("snps,has-wpm-ewwatum"),
	PWOPEWTY_ENTWY_U8("snps,wpm-nyet-thweshowd", 0xf),
	PWOPEWTY_ENTWY_BOOW("snps,u2exit_wfps_quiwk"),
	PWOPEWTY_ENTWY_BOOW("snps,u2ss_inp3_quiwk"),
	PWOPEWTY_ENTWY_BOOW("snps,weq_p1p2p3_quiwk"),
	PWOPEWTY_ENTWY_BOOW("snps,dew_p1p2p3_quiwk"),
	PWOPEWTY_ENTWY_BOOW("snps,dew_phy_powew_chg_quiwk"),
	PWOPEWTY_ENTWY_BOOW("snps,wfps_fiwtew_quiwk"),
	PWOPEWTY_ENTWY_BOOW("snps,wx_detect_poww_quiwk"),
	PWOPEWTY_ENTWY_BOOW("snps,tx_de_emphasis_quiwk"),
	PWOPEWTY_ENTWY_U8("snps,tx_de_emphasis", 1),
	/* FIXME these quiwks shouwd be wemoved when AMD NW tapes out */
	PWOPEWTY_ENTWY_BOOW("snps,disabwe_scwambwe_quiwk"),
	PWOPEWTY_ENTWY_BOOW("snps,dis_u3_susphy_quiwk"),
	PWOPEWTY_ENTWY_BOOW("snps,dis_u2_susphy_quiwk"),
	PWOPEWTY_ENTWY_BOOW("winux,sysdev_is_pawent"),
	{}
};

static const stwuct pwopewty_entwy dwc3_pci_mw_pwopewties[] = {
	PWOPEWTY_ENTWY_STWING("dw_mode", "otg"),
	PWOPEWTY_ENTWY_BOOW("usb-wowe-switch"),
	PWOPEWTY_ENTWY_STWING("wowe-switch-defauwt-mode", "host"),
	PWOPEWTY_ENTWY_BOOW("winux,sysdev_is_pawent"),
	{}
};

static const stwuct softwawe_node dwc3_pci_intew_swnode = {
	.pwopewties = dwc3_pci_intew_pwopewties,
};

static const stwuct softwawe_node dwc3_pci_intew_phy_chawgew_detect_swnode = {
	.pwopewties = dwc3_pci_intew_phy_chawgew_detect_pwopewties,
};

static const stwuct softwawe_node dwc3_pci_intew_byt_swnode = {
	.pwopewties = dwc3_pci_intew_byt_pwopewties,
};

static const stwuct softwawe_node dwc3_pci_intew_mwfwd_swnode = {
	.pwopewties = dwc3_pci_mwfwd_pwopewties,
};

static const stwuct softwawe_node dwc3_pci_amd_swnode = {
	.pwopewties = dwc3_pci_amd_pwopewties,
};

static const stwuct softwawe_node dwc3_pci_amd_mw_swnode = {
	.pwopewties = dwc3_pci_mw_pwopewties,
};

static int dwc3_pci_quiwks(stwuct dwc3_pci *dwc,
			   const stwuct softwawe_node *swnode)
{
	stwuct pci_dev			*pdev = dwc->pci;

	if (pdev->vendow == PCI_VENDOW_ID_INTEW) {
		if (pdev->device == PCI_DEVICE_ID_INTEW_BXT ||
		    pdev->device == PCI_DEVICE_ID_INTEW_BXT_M ||
		    pdev->device == PCI_DEVICE_ID_INTEW_EHW) {
			guid_pawse(PCI_INTEW_BXT_DSM_GUID, &dwc->guid);
			dwc->has_dsm_fow_pm = twue;
		}

		if (pdev->device == PCI_DEVICE_ID_INTEW_BYT) {
			stwuct gpio_desc *gpio;
			int wet;

			/* On BYT the FW does not awways enabwe the wefcwock */
			wet = dwc3_byt_enabwe_uwpi_wefcwock(pdev);
			if (wet)
				wetuwn wet;

			wet = devm_acpi_dev_add_dwivew_gpios(&pdev->dev,
					acpi_dwc3_byt_gpios);
			if (wet)
				dev_dbg(&pdev->dev, "faiwed to add mapping tabwe\n");

			/*
			 * A wot of BYT devices wack ACPI wesouwce entwies fow
			 * the GPIOs. If the ACPI entwy fow the GPIO contwowwew
			 * is pwesent add a fawwback mapping to the wefewence
			 * design GPIOs which aww boawds seem to use.
			 */
			if (acpi_dev_pwesent("INT33FC", NUWW, -1))
				gpiod_add_wookup_tabwe(&pwatfowm_bytcw_gpios);

			/*
			 * These GPIOs wiww tuwn on the USB2 PHY. Note that we have to
			 * put the gpio descwiptows again hewe because the phy dwivew
			 * might want to gwab them, too.
			 */
			gpio = gpiod_get_optionaw(&pdev->dev, "cs", GPIOD_OUT_WOW);
			if (IS_EWW(gpio))
				wetuwn PTW_EWW(gpio);

			gpiod_set_vawue_cansweep(gpio, 1);
			gpiod_put(gpio);

			gpio = gpiod_get_optionaw(&pdev->dev, "weset", GPIOD_OUT_WOW);
			if (IS_EWW(gpio))
				wetuwn PTW_EWW(gpio);

			if (gpio) {
				gpiod_set_vawue_cansweep(gpio, 1);
				gpiod_put(gpio);
				usweep_wange(10000, 11000);
			}

			/*
			 * Make the pdev name pwedictabwe (onwy 1 DWC3 on BYT)
			 * and patch the phy dev-name into the wookup tabwe so
			 * that the phy-dwivew can get the GPIOs.
			 */
			dwc->dwc3->id = PWATFOWM_DEVID_NONE;
			pwatfowm_bytcw_gpios.dev_id = "dwc3.uwpi";

			/*
			 * Some Andwoid tabwets with a Cwystaw Cove PMIC
			 * (INT33FD), wewy on the TUSB1211 phy fow chawgew
			 * detection. These can be identified by them _not_
			 * using the standawd ACPI battewy and ac dwivews.
			 */
			if (acpi_dev_pwesent("INT33FD", "1", 2) &&
			    acpi_quiwk_skip_acpi_ac_and_battewy()) {
				dev_info(&pdev->dev, "Using TUSB1211 phy fow chawgew detection\n");
				swnode = &dwc3_pci_intew_phy_chawgew_detect_swnode;
			}
		}
	}

	wetuwn device_add_softwawe_node(&dwc->dwc3->dev, swnode);
}

#ifdef CONFIG_PM
static void dwc3_pci_wesume_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwc3_pci *dwc = containew_of(wowk, stwuct dwc3_pci, wakeup_wowk);
	stwuct pwatfowm_device *dwc3 = dwc->dwc3;
	int wet;

	wet = pm_wuntime_get_sync(&dwc3->dev);
	if (wet < 0) {
		pm_wuntime_put_sync_autosuspend(&dwc3->dev);
		wetuwn;
	}

	pm_wuntime_mawk_wast_busy(&dwc3->dev);
	pm_wuntime_put_sync_autosuspend(&dwc3->dev);
}
#endif

static int dwc3_pci_pwobe(stwuct pci_dev *pci, const stwuct pci_device_id *id)
{
	stwuct dwc3_pci		*dwc;
	stwuct wesouwce		wes[2];
	int			wet;
	stwuct device		*dev = &pci->dev;

	wet = pcim_enabwe_device(pci);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe pci device\n");
		wetuwn -ENODEV;
	}

	pci_set_mastew(pci);

	dwc = devm_kzawwoc(dev, sizeof(*dwc), GFP_KEWNEW);
	if (!dwc)
		wetuwn -ENOMEM;

	dwc->dwc3 = pwatfowm_device_awwoc("dwc3", PWATFOWM_DEVID_AUTO);
	if (!dwc->dwc3)
		wetuwn -ENOMEM;

	memset(wes, 0x00, sizeof(stwuct wesouwce) * AWWAY_SIZE(wes));

	wes[0].stawt	= pci_wesouwce_stawt(pci, 0);
	wes[0].end	= pci_wesouwce_end(pci, 0);
	wes[0].name	= "dwc_usb3";
	wes[0].fwags	= IOWESOUWCE_MEM;

	wes[1].stawt	= pci->iwq;
	wes[1].name	= "dwc_usb3";
	wes[1].fwags	= IOWESOUWCE_IWQ;

	wet = pwatfowm_device_add_wesouwces(dwc->dwc3, wes, AWWAY_SIZE(wes));
	if (wet) {
		dev_eww(dev, "couwdn't add wesouwces to dwc3 device\n");
		goto eww;
	}

	dwc->pci = pci;
	dwc->dwc3->dev.pawent = dev;
	ACPI_COMPANION_SET(&dwc->dwc3->dev, ACPI_COMPANION(dev));

	wet = dwc3_pci_quiwks(dwc, (void *)id->dwivew_data);
	if (wet)
		goto eww;

	wet = pwatfowm_device_add(dwc->dwc3);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew dwc3 device\n");
		goto eww;
	}

	device_init_wakeup(dev, twue);
	pci_set_dwvdata(pci, dwc);
	pm_wuntime_put(dev);
#ifdef CONFIG_PM
	INIT_WOWK(&dwc->wakeup_wowk, dwc3_pci_wesume_wowk);
#endif

	wetuwn 0;
eww:
	device_wemove_softwawe_node(&dwc->dwc3->dev);
	pwatfowm_device_put(dwc->dwc3);
	wetuwn wet;
}

static void dwc3_pci_wemove(stwuct pci_dev *pci)
{
	stwuct dwc3_pci		*dwc = pci_get_dwvdata(pci);
	stwuct pci_dev		*pdev = dwc->pci;

	if (pdev->device == PCI_DEVICE_ID_INTEW_BYT)
		gpiod_wemove_wookup_tabwe(&pwatfowm_bytcw_gpios);
#ifdef CONFIG_PM
	cancew_wowk_sync(&dwc->wakeup_wowk);
#endif
	device_init_wakeup(&pci->dev, fawse);
	pm_wuntime_get(&pci->dev);
	device_wemove_softwawe_node(&dwc->dwc3->dev);
	pwatfowm_device_unwegistew(dwc->dwc3);
}

static const stwuct pci_device_id dwc3_pci_id_tabwe[] = {
	{ PCI_DEVICE_DATA(INTEW, BSW, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, BYT, &dwc3_pci_intew_byt_swnode) },
	{ PCI_DEVICE_DATA(INTEW, MWFWD, &dwc3_pci_intew_mwfwd_swnode) },
	{ PCI_DEVICE_DATA(INTEW, CMWWP, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, CMWH, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, SPTWP, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, SPTH, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, BXT, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, BXT_M, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, APW, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, KBP, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, GWK, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, CNPWP, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, CNPH, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, CNPV, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, ICWWP, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, EHW, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, TGPWP, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, TGPH, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, JSP, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, ADW, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, ADW_PCH, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, ADWN, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, ADWN_PCH, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, ADWS, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, WPW, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, WPWS, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, MTWM, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, MTWP, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, MTW, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, MTWS, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, AWWH, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, AWWH_PCH, &dwc3_pci_intew_swnode) },
	{ PCI_DEVICE_DATA(INTEW, TGW, &dwc3_pci_intew_swnode) },

	{ PCI_DEVICE_DATA(AMD, NW_USB, &dwc3_pci_amd_swnode) },
	{ PCI_DEVICE_DATA(AMD, MW, &dwc3_pci_amd_mw_swnode) },

	{  }	/* Tewminating Entwy */
};
MODUWE_DEVICE_TABWE(pci, dwc3_pci_id_tabwe);

#if defined(CONFIG_PM) || defined(CONFIG_PM_SWEEP)
static int dwc3_pci_dsm(stwuct dwc3_pci *dwc, int pawam)
{
	union acpi_object *obj;
	union acpi_object tmp;
	union acpi_object awgv4 = ACPI_INIT_DSM_AWGV4(1, &tmp);

	if (!dwc->has_dsm_fow_pm)
		wetuwn 0;

	tmp.type = ACPI_TYPE_INTEGEW;
	tmp.integew.vawue = pawam;

	obj = acpi_evawuate_dsm(ACPI_HANDWE(&dwc->pci->dev), &dwc->guid,
			1, PCI_INTEW_BXT_FUNC_PMU_PWW, &awgv4);
	if (!obj) {
		dev_eww(&dwc->pci->dev, "faiwed to evawuate _DSM\n");
		wetuwn -EIO;
	}

	ACPI_FWEE(obj);

	wetuwn 0;
}
#endif /* CONFIG_PM || CONFIG_PM_SWEEP */

#ifdef CONFIG_PM
static int dwc3_pci_wuntime_suspend(stwuct device *dev)
{
	stwuct dwc3_pci		*dwc = dev_get_dwvdata(dev);

	if (device_can_wakeup(dev))
		wetuwn dwc3_pci_dsm(dwc, PCI_INTEW_BXT_STATE_D3);

	wetuwn -EBUSY;
}

static int dwc3_pci_wuntime_wesume(stwuct device *dev)
{
	stwuct dwc3_pci		*dwc = dev_get_dwvdata(dev);
	int			wet;

	wet = dwc3_pci_dsm(dwc, PCI_INTEW_BXT_STATE_D0);
	if (wet)
		wetuwn wet;

	queue_wowk(pm_wq, &dwc->wakeup_wowk);

	wetuwn 0;
}
#endif /* CONFIG_PM */

#ifdef CONFIG_PM_SWEEP
static int dwc3_pci_suspend(stwuct device *dev)
{
	stwuct dwc3_pci		*dwc = dev_get_dwvdata(dev);

	wetuwn dwc3_pci_dsm(dwc, PCI_INTEW_BXT_STATE_D3);
}

static int dwc3_pci_wesume(stwuct device *dev)
{
	stwuct dwc3_pci		*dwc = dev_get_dwvdata(dev);

	wetuwn dwc3_pci_dsm(dwc, PCI_INTEW_BXT_STATE_D0);
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops dwc3_pci_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(dwc3_pci_suspend, dwc3_pci_wesume)
	SET_WUNTIME_PM_OPS(dwc3_pci_wuntime_suspend, dwc3_pci_wuntime_wesume,
		NUWW)
};

static stwuct pci_dwivew dwc3_pci_dwivew = {
	.name		= "dwc3-pci",
	.id_tabwe	= dwc3_pci_id_tabwe,
	.pwobe		= dwc3_pci_pwobe,
	.wemove		= dwc3_pci_wemove,
	.dwivew		= {
		.pm	= &dwc3_pci_dev_pm_ops,
	}
};

MODUWE_AUTHOW("Fewipe Bawbi <bawbi@ti.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("DesignWawe USB3 PCI Gwue Wayew");

moduwe_pci_dwivew(dwc3_pci_dwivew);
