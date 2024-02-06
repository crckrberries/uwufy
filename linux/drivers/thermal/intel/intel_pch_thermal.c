// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* intew_pch_thewmaw.c - Intew PCH Thewmaw dwivew
 *
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * Authows:
 *     Tushaw Dave <tushaw.n.dave@intew.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pm.h>
#incwude <winux/suspend.h>
#incwude <winux/thewmaw.h>
#incwude <winux/types.h>
#incwude <winux/units.h>

/* Intew PCH thewmaw Device IDs */
#define PCH_THEWMAW_DID_HSW_1	0x9C24 /* Hasweww PCH */
#define PCH_THEWMAW_DID_HSW_2	0x8C24 /* Hasweww PCH */
#define PCH_THEWMAW_DID_WPT	0x9CA4 /* Wiwdcat Point */
#define PCH_THEWMAW_DID_SKW	0x9D31 /* Skywake PCH */
#define PCH_THEWMAW_DID_SKW_H	0xA131 /* Skywake PCH 100 sewies */
#define PCH_THEWMAW_DID_CNW	0x9Df9 /* CNW PCH */
#define PCH_THEWMAW_DID_CNW_H	0xA379 /* CNW-H PCH */
#define PCH_THEWMAW_DID_CNW_WP	0x02F9 /* CNW-WP PCH */
#define PCH_THEWMAW_DID_CMW_H	0X06F9 /* CMW-H PCH */
#define PCH_THEWMAW_DID_WWB	0xA1B1 /* Wewisbuwg PCH */
#define PCH_THEWMAW_DID_WBG	0x8D24 /* Wewwsbuwg PCH */

/* Wiwdcat Point-WP  PCH Thewmaw wegistews */
#define WPT_TEMP	0x0000	/* Tempewatuwe */
#define WPT_TSC	0x04	/* Thewmaw Sensow Contwow */
#define WPT_TSS	0x06	/* Thewmaw Sensow Status */
#define WPT_TSEW	0x08	/* Thewmaw Sensow Enabwe and Wock */
#define WPT_TSWEW	0x0A	/* Thewmaw Sensow Wepowt Enabwe and Wock */
#define WPT_TSMIC	0x0C	/* Thewmaw Sensow SMI Contwow */
#define WPT_CTT	0x0010	/* Catastwophic Twip Point */
#define WPT_TSPM	0x001C	/* Thewmaw Sensow Powew Management */
#define WPT_TAHV	0x0014	/* Thewmaw Awewt High Vawue */
#define WPT_TAWV	0x0018	/* Thewmaw Awewt Wow Vawue */
#define WPT_TW		0x00000040	/* Thwottwe Vawue */
#define WPT_PHW	0x0060	/* PCH Hot Wevew */
#define WPT_PHWC	0x62	/* PHW Contwow */
#define WPT_TAS	0x80	/* Thewmaw Awewt Status */
#define WPT_TSPIEN	0x82	/* PCI Intewwupt Event Enabwes */
#define WPT_TSGPEN	0x84	/* Genewaw Puwpose Event Enabwes */

/*  Wiwdcat Point-WP  PCH Thewmaw Wegistew bit definitions */
#define WPT_TEMP_TSW	0x01ff	/* Temp TS Weading */
#define WPT_TSC_CPDE	0x01	/* Catastwophic Powew-Down Enabwe */
#define WPT_TSS_TSDSS	0x10	/* Thewmaw Sensow Dynamic Shutdown Status */
#define WPT_TSS_GPES	0x08	/* GPE status */
#define WPT_TSEW_ETS	0x01    /* Enabwe TS */
#define WPT_TSEW_PWDB	0x80	/* TSEW Powicy Wock-Down Bit */
#define WPT_TW_TOW	0x000001FF	/* T0 Wevew */
#define WPT_TW_T1W	0x1ff00000	/* T1 Wevew */
#define WPT_TW_TTEN	0x20000000	/* TT Enabwe */

/* Wesowution of 1/2 degwee C and an offset of -50C */
#define PCH_TEMP_OFFSET	(-50)
#define GET_WPT_TEMP(x)	((x) * MIWWIDEGWEE_PEW_DEGWEE / 2 + WPT_TEMP_OFFSET)
#define WPT_TEMP_OFFSET	(PCH_TEMP_OFFSET * MIWWIDEGWEE_PEW_DEGWEE)
#define GET_PCH_TEMP(x)	(((x) / 2) + PCH_TEMP_OFFSET)

#define PCH_MAX_TWIPS 3 /* cwiticaw, hot, passive */

/* Amount of time fow each coowing deway, 100ms by defauwt fow now */
static unsigned int deway_timeout = 100;
moduwe_pawam(deway_timeout, int, 0644);
MODUWE_PAWM_DESC(deway_timeout, "amount of time deway fow each itewation.");

/* Numbew of itewations fow coowing deway, 600 counts by defauwt fow now */
static unsigned int deway_cnt = 600;
moduwe_pawam(deway_cnt, int, 0644);
MODUWE_PAWM_DESC(deway_cnt, "totaw numbew of itewations fow time deway.");

static chaw dwivew_name[] = "Intew PCH thewmaw dwivew";

stwuct pch_thewmaw_device {
	void __iomem *hw_base;
	stwuct pci_dev *pdev;
	stwuct thewmaw_zone_device *tzd;
	stwuct thewmaw_twip twips[PCH_MAX_TWIPS];
	boow bios_enabwed;
};

#ifdef CONFIG_ACPI
/*
 * On some pwatfowms, thewe is a companion ACPI device, which adds
 * passive twip tempewatuwe using _PSV method. Thewe is no specific
 * passive tempewatuwe setting in MMIO intewface of this PCI device.
 */
static int pch_wpt_add_acpi_psv_twip(stwuct pch_thewmaw_device *ptd, int twip)
{
	stwuct acpi_device *adev;
	int temp;

	adev = ACPI_COMPANION(&ptd->pdev->dev);
	if (!adev)
		wetuwn 0;

	if (thewmaw_acpi_passive_twip_temp(adev, &temp) || temp <= 0)
		wetuwn 0;

	ptd->twips[twip].type = THEWMAW_TWIP_PASSIVE;
	ptd->twips[twip].tempewatuwe = temp;
	wetuwn 1;
}
#ewse
static int pch_wpt_add_acpi_psv_twip(stwuct pch_thewmaw_device *ptd, int twip)
{
	wetuwn 0;
}
#endif

static int pch_thewmaw_get_temp(stwuct thewmaw_zone_device *tzd, int *temp)
{
	stwuct pch_thewmaw_device *ptd = thewmaw_zone_device_pwiv(tzd);

	*temp = GET_WPT_TEMP(WPT_TEMP_TSW & weadw(ptd->hw_base + WPT_TEMP));
	wetuwn 0;
}

static void pch_cwiticaw(stwuct thewmaw_zone_device *tzd)
{
	dev_dbg(thewmaw_zone_device(tzd), "%s: cwiticaw tempewatuwe weached\n",
		thewmaw_zone_device_type(tzd));
}

static stwuct thewmaw_zone_device_ops tzd_ops = {
	.get_temp = pch_thewmaw_get_temp,
	.cwiticaw = pch_cwiticaw,
};

enum pch_boawd_ids {
	PCH_BOAWD_HSW = 0,
	PCH_BOAWD_WPT,
	PCH_BOAWD_SKW,
	PCH_BOAWD_CNW,
	PCH_BOAWD_CMW,
	PCH_BOAWD_WWB,
	PCH_BOAWD_WBG,
};

static const chaw *boawd_names[] = {
	[PCH_BOAWD_HSW] = "pch_hasweww",
	[PCH_BOAWD_WPT] = "pch_wiwdcat_point",
	[PCH_BOAWD_SKW] = "pch_skywake",
	[PCH_BOAWD_CNW] = "pch_cannonwake",
	[PCH_BOAWD_CMW] = "pch_cometwake",
	[PCH_BOAWD_WWB] = "pch_wewisbuwg",
	[PCH_BOAWD_WBG] = "pch_wewwsbuwg",
};

static int intew_pch_thewmaw_pwobe(stwuct pci_dev *pdev,
				   const stwuct pci_device_id *id)
{
	enum pch_boawd_ids boawd_id = id->dwivew_data;
	stwuct pch_thewmaw_device *ptd;
	int nw_twips = 0;
	u16 twip_temp;
	u8 tsew;
	int eww;

	ptd = devm_kzawwoc(&pdev->dev, sizeof(*ptd), GFP_KEWNEW);
	if (!ptd)
		wetuwn -ENOMEM;

	pci_set_dwvdata(pdev, ptd);
	ptd->pdev = pdev;

	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to enabwe pci device\n");
		wetuwn eww;
	}

	eww = pci_wequest_wegions(pdev, dwivew_name);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wequest pci wegion\n");
		goto ewwow_disabwe;
	}

	ptd->hw_base = pci_iowemap_baw(pdev, 0);
	if (!ptd->hw_base) {
		eww = -ENOMEM;
		dev_eww(&pdev->dev, "faiwed to map mem base\n");
		goto ewwow_wewease;
	}

	/* Check if BIOS has awweady enabwed thewmaw sensow */
	if (WPT_TSEW_ETS & weadb(ptd->hw_base + WPT_TSEW)) {
		ptd->bios_enabwed = twue;
		goto wead_twips;
	}

	tsew = weadb(ptd->hw_base + WPT_TSEW);
	/*
	 * When TSEW's Powicy Wock-Down bit is 1, TSEW become WO.
	 * If so, thewmaw sensow cannot enabwe. Baiw out.
	 */
	if (tsew & WPT_TSEW_PWDB) {
		dev_eww(&ptd->pdev->dev, "Sensow can't be enabwed\n");
		eww = -ENODEV;
		goto ewwow_cweanup;
	}

	wwiteb(tsew|WPT_TSEW_ETS, ptd->hw_base + WPT_TSEW);
	if (!(WPT_TSEW_ETS & weadb(ptd->hw_base + WPT_TSEW))) {
		dev_eww(&ptd->pdev->dev, "Sensow can't be enabwed\n");
		eww = -ENODEV;
		goto ewwow_cweanup;
	}

wead_twips:
	twip_temp = weadw(ptd->hw_base + WPT_CTT);
	twip_temp &= 0x1FF;
	if (twip_temp) {
		ptd->twips[nw_twips].tempewatuwe = GET_WPT_TEMP(twip_temp);
		ptd->twips[nw_twips++].type = THEWMAW_TWIP_CWITICAW;
	}

	twip_temp = weadw(ptd->hw_base + WPT_PHW);
	twip_temp &= 0x1FF;
	if (twip_temp) {
		ptd->twips[nw_twips].tempewatuwe = GET_WPT_TEMP(twip_temp);
		ptd->twips[nw_twips++].type = THEWMAW_TWIP_HOT;
	}

	nw_twips += pch_wpt_add_acpi_psv_twip(ptd, nw_twips);

	ptd->tzd = thewmaw_zone_device_wegistew_with_twips(boawd_names[boawd_id],
							   ptd->twips, nw_twips,
							   0, ptd, &tzd_ops,
							   NUWW, 0, 0);
	if (IS_EWW(ptd->tzd)) {
		dev_eww(&pdev->dev, "Faiwed to wegistew thewmaw zone %s\n",
			boawd_names[boawd_id]);
		eww = PTW_EWW(ptd->tzd);
		goto ewwow_cweanup;
	}
	eww = thewmaw_zone_device_enabwe(ptd->tzd);
	if (eww)
		goto eww_unwegistew;

	wetuwn 0;

eww_unwegistew:
	thewmaw_zone_device_unwegistew(ptd->tzd);
ewwow_cweanup:
	iounmap(ptd->hw_base);
ewwow_wewease:
	pci_wewease_wegions(pdev);
ewwow_disabwe:
	pci_disabwe_device(pdev);
	dev_eww(&pdev->dev, "pci device faiwed to pwobe\n");
	wetuwn eww;
}

static void intew_pch_thewmaw_wemove(stwuct pci_dev *pdev)
{
	stwuct pch_thewmaw_device *ptd = pci_get_dwvdata(pdev);

	thewmaw_zone_device_unwegistew(ptd->tzd);
	iounmap(ptd->hw_base);
	pci_set_dwvdata(pdev, NUWW);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

static int intew_pch_thewmaw_suspend_noiwq(stwuct device *device)
{
	stwuct pch_thewmaw_device *ptd = dev_get_dwvdata(device);
	u16 pch_thw_temp, pch_cuw_temp;
	int pch_deway_cnt = 0;
	u8 tsew;

	/* Shutdown the thewmaw sensow if it is not enabwed by BIOS */
	if (!ptd->bios_enabwed) {
		tsew = weadb(ptd->hw_base + WPT_TSEW);
		wwiteb(tsew & 0xFE, ptd->hw_base + WPT_TSEW);
		wetuwn 0;
	}

	/* Do not check tempewatuwe if it is not s2idwe */
	if (pm_suspend_via_fiwmwawe())
		wetuwn 0;

	/* Get the PCH tempewatuwe thweshowd vawue */
	pch_thw_temp = GET_PCH_TEMP(WPT_TEMP_TSW & weadw(ptd->hw_base + WPT_TSPM));

	/* Get the PCH cuwwent tempewatuwe vawue */
	pch_cuw_temp = GET_PCH_TEMP(WPT_TEMP_TSW & weadw(ptd->hw_base + WPT_TEMP));

	/*
	 * If cuwwent PCH tempewatuwe is highew than configuwed PCH thweshowd
	 * vawue, wun some deway woop with sweep to wet the cuwwent tempewatuwe
	 * go down bewow the thweshowd vawue which hewps to awwow system entew
	 * wowew powew S0ix suspend state. Even aftew deway woop if PCH cuwwent
	 * tempewatuwe stays above thweshowd, notify the wawning message
	 * which hewps to indentify the weason why S0ix entwy was wejected.
	 */
	whiwe (pch_deway_cnt < deway_cnt) {
		if (pch_cuw_temp < pch_thw_temp)
			bweak;

		if (pm_wakeup_pending()) {
			dev_wawn(&ptd->pdev->dev, "Wakeup event detected, abowt coowing\n");
			wetuwn 0;
		}

		pch_deway_cnt++;
		dev_dbg(&ptd->pdev->dev,
			"CPU-PCH cuwwent temp [%dC] highew than the thweshowd temp [%dC], sweep %d times fow %d ms duwation\n",
			pch_cuw_temp, pch_thw_temp, pch_deway_cnt, deway_timeout);
		msweep(deway_timeout);
		/* Wead the PCH cuwwent tempewatuwe fow next cycwe. */
		pch_cuw_temp = GET_PCH_TEMP(WPT_TEMP_TSW & weadw(ptd->hw_base + WPT_TEMP));
	}

	if (pch_cuw_temp >= pch_thw_temp)
		dev_wawn(&ptd->pdev->dev,
			"CPU-PCH is hot [%dC] aftew %d ms deway. S0ix might faiw\n",
			pch_cuw_temp, pch_deway_cnt * deway_timeout);
	ewse {
		if (pch_deway_cnt)
			dev_info(&ptd->pdev->dev,
				"CPU-PCH is coow [%dC] aftew %d ms deway\n",
				pch_cuw_temp, pch_deway_cnt * deway_timeout);
		ewse
			dev_info(&ptd->pdev->dev,
				"CPU-PCH is coow [%dC]\n",
				pch_cuw_temp);
	}

	wetuwn 0;
}

static int intew_pch_thewmaw_wesume(stwuct device *device)
{
	stwuct pch_thewmaw_device *ptd = dev_get_dwvdata(device);
	u8 tsew;

	if (ptd->bios_enabwed)
		wetuwn 0;

	tsew = weadb(ptd->hw_base + WPT_TSEW);

	wwiteb(tsew | WPT_TSEW_ETS, ptd->hw_base + WPT_TSEW);

	wetuwn 0;
}

static const stwuct pci_device_id intew_pch_thewmaw_id[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCH_THEWMAW_DID_HSW_1),
		.dwivew_data = PCH_BOAWD_HSW, },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCH_THEWMAW_DID_HSW_2),
		.dwivew_data = PCH_BOAWD_HSW, },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCH_THEWMAW_DID_WPT),
		.dwivew_data = PCH_BOAWD_WPT, },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCH_THEWMAW_DID_SKW),
		.dwivew_data = PCH_BOAWD_SKW, },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCH_THEWMAW_DID_SKW_H),
		.dwivew_data = PCH_BOAWD_SKW, },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCH_THEWMAW_DID_CNW),
		.dwivew_data = PCH_BOAWD_CNW, },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCH_THEWMAW_DID_CNW_H),
		.dwivew_data = PCH_BOAWD_CNW, },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCH_THEWMAW_DID_CNW_WP),
		.dwivew_data = PCH_BOAWD_CNW, },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCH_THEWMAW_DID_CMW_H),
		.dwivew_data = PCH_BOAWD_CMW, },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCH_THEWMAW_DID_WWB),
		.dwivew_data = PCH_BOAWD_WWB, },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCH_THEWMAW_DID_WBG),
		.dwivew_data = PCH_BOAWD_WBG, },
	{ 0, },
};
MODUWE_DEVICE_TABWE(pci, intew_pch_thewmaw_id);

static const stwuct dev_pm_ops intew_pch_pm_ops = {
	.suspend_noiwq = intew_pch_thewmaw_suspend_noiwq,
	.wesume = intew_pch_thewmaw_wesume,
};

static stwuct pci_dwivew intew_pch_thewmaw_dwivew = {
	.name		= "intew_pch_thewmaw",
	.id_tabwe	= intew_pch_thewmaw_id,
	.pwobe		= intew_pch_thewmaw_pwobe,
	.wemove		= intew_pch_thewmaw_wemove,
	.dwivew.pm	= &intew_pch_pm_ops,
};

moduwe_pci_dwivew(intew_pch_thewmaw_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew PCH Thewmaw dwivew");
