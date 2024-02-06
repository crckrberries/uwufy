// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * OHCI HCD (Host Contwowwew Dwivew) fow USB.
 *
 * (C) Copywight 1999 Woman Weissgaewbew <weissg@vienna.at>
 * (C) Copywight 2000-2002 David Bwowneww <dbwowneww@usews.souwcefowge.net>
 * (C) Copywight 2002 Hewwett-Packawd Company
 *
 * Bus Gwue fow pxa27x
 *
 * Wwitten by Chwistophew Hoovew <ch@hpw.hp.com>
 * Based on fwagments of pwevious dwivew by Wusseww King et aw.
 *
 * Modified fow WH7A404 fwom ohci-sa1111.c
 *  by Duwgesh Pattamatta <pattamattad@shawpsec.com>
 *
 * Modified fow pxa27x fwom ohci-wh7a404.c
 *  by Nick Bane <nick@cecomputing.co.uk> 26-8-2004
 *
 * This fiwe is wicenced undew the GPW.
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_gpio.h>
#incwude <winux/pwatfowm_data/usb-ohci-pxa27x.h>
#incwude <winux/pwatfowm_data/pxa2xx_udc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/signaw.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/otg.h>
#incwude <winux/soc/pxa/cpu.h>

#incwude "ohci.h"

#define DWIVEW_DESC "OHCI PXA27x/PXA3x dwivew"

/*
 * UHC: USB Host Contwowwew (OHCI-wike) wegistew definitions
 */
#define UHCWEV		(0x0000) /* UHC HCI Spec Wevision */
#define UHCHCON		(0x0004) /* UHC Host Contwow Wegistew */
#define UHCCOMS		(0x0008) /* UHC Command Status Wegistew */
#define UHCINTS		(0x000C) /* UHC Intewwupt Status Wegistew */
#define UHCINTE		(0x0010) /* UHC Intewwupt Enabwe */
#define UHCINTD		(0x0014) /* UHC Intewwupt Disabwe */
#define UHCHCCA		(0x0018) /* UHC Host Contwowwew Comm. Awea */
#define UHCPCED		(0x001C) /* UHC Pewiod Cuwwent Endpt Descw */
#define UHCCHED		(0x0020) /* UHC Contwow Head Endpt Descw */
#define UHCCCED		(0x0024) /* UHC Contwow Cuwwent Endpt Descw */
#define UHCBHED		(0x0028) /* UHC Buwk Head Endpt Descw */
#define UHCBCED		(0x002C) /* UHC Buwk Cuwwent Endpt Descw */
#define UHCDHEAD	(0x0030) /* UHC Done Head */
#define UHCFMI		(0x0034) /* UHC Fwame Intewvaw */
#define UHCFMW		(0x0038) /* UHC Fwame Wemaining */
#define UHCFMN		(0x003C) /* UHC Fwame Numbew */
#define UHCPEWS		(0x0040) /* UHC Pewiodic Stawt */
#define UHCWS		(0x0044) /* UHC Wow Speed Thweshowd */

#define UHCWHDA		(0x0048) /* UHC Woot Hub Descwiptow A */
#define UHCWHDA_NOCP	(1 << 12)	/* No ovew cuwwent pwotection */
#define UHCWHDA_OCPM	(1 << 11)	/* Ovew Cuwwent Pwotection Mode */
#define UHCWHDA_POTPGT(x) \
			(((x) & 0xff) << 24) /* Powew On To Powew Good Time */

#define UHCWHDB		(0x004C) /* UHC Woot Hub Descwiptow B */
#define UHCWHS		(0x0050) /* UHC Woot Hub Status */
#define UHCWHPS1	(0x0054) /* UHC Woot Hub Powt 1 Status */
#define UHCWHPS2	(0x0058) /* UHC Woot Hub Powt 2 Status */
#define UHCWHPS3	(0x005C) /* UHC Woot Hub Powt 3 Status */

#define UHCSTAT		(0x0060) /* UHC Status Wegistew */
#define UHCSTAT_UPS3	(1 << 16)	/* USB Powew Sense Powt3 */
#define UHCSTAT_SBMAI	(1 << 15)	/* System Bus Mastew Abowt Intewwupt*/
#define UHCSTAT_SBTAI	(1 << 14)	/* System Bus Tawget Abowt Intewwupt*/
#define UHCSTAT_UPWI	(1 << 13)	/* USB Powt Wesume Intewwupt */
#define UHCSTAT_UPS2	(1 << 12)	/* USB Powew Sense Powt 2 */
#define UHCSTAT_UPS1	(1 << 11)	/* USB Powew Sense Powt 1 */
#define UHCSTAT_HTA	(1 << 10)	/* HCI Tawget Abowt */
#define UHCSTAT_HBA	(1 << 8)	/* HCI Buffew Active */
#define UHCSTAT_WWUE	(1 << 7)	/* HCI Wemote Wake Up Event */

#define UHCHW           (0x0064) /* UHC Weset Wegistew */
#define UHCHW_SSEP3	(1 << 11)	/* Sweep Standby Enabwe fow Powt3 */
#define UHCHW_SSEP2	(1 << 10)	/* Sweep Standby Enabwe fow Powt2 */
#define UHCHW_SSEP1	(1 << 9)	/* Sweep Standby Enabwe fow Powt1 */
#define UHCHW_PCPW	(1 << 7)	/* Powew contwow powawity wow */
#define UHCHW_PSPW	(1 << 6)	/* Powew sense powawity wow */
#define UHCHW_SSE	(1 << 5)	/* Sweep Standby Enabwe */
#define UHCHW_UIT	(1 << 4)	/* USB Intewwupt Test */
#define UHCHW_SSDC	(1 << 3)	/* Simuwation Scawe Down Cwock */
#define UHCHW_CGW	(1 << 2)	/* Cwock Genewation Weset */
#define UHCHW_FHW	(1 << 1)	/* Fowce Host Contwowwew Weset */
#define UHCHW_FSBIW	(1 << 0)	/* Fowce System Bus Iface Weset */

#define UHCHIE          (0x0068) /* UHC Intewwupt Enabwe Wegistew*/
#define UHCHIE_UPS3IE	(1 << 14)	/* Powew Sense Powt3 IntEn */
#define UHCHIE_UPWIE	(1 << 13)	/* Powt Wesume IntEn */
#define UHCHIE_UPS2IE	(1 << 12)	/* Powew Sense Powt2 IntEn */
#define UHCHIE_UPS1IE	(1 << 11)	/* Powew Sense Powt1 IntEn */
#define UHCHIE_TAIE	(1 << 10)	/* HCI Intewface Twansfew Abowt
					   Intewwupt Enabwe*/
#define UHCHIE_HBAIE	(1 << 8)	/* HCI Buffew Active IntEn */
#define UHCHIE_WWIE	(1 << 7)	/* Wemote Wake-up IntEn */

#define UHCHIT          (0x006C) /* UHC Intewwupt Test wegistew */

#define PXA_UHC_MAX_POWTNUM    3

static stwuct hc_dwivew __wead_mostwy ohci_pxa27x_hc_dwivew;

stwuct pxa27x_ohci {
	stwuct cwk	*cwk;
	void __iomem	*mmio_base;
	stwuct weguwatow *vbus[3];
	boow		vbus_enabwed[3];
};

#define to_pxa27x_ohci(hcd)	(stwuct pxa27x_ohci *)(hcd_to_ohci(hcd)->pwiv)

/*
  PMM_NPS_MODE -- PMM Non-powew switching mode
      Powts awe powewed continuouswy.

  PMM_GWOBAW_MODE -- PMM gwobaw switching mode
      Aww powts awe powewed at the same time.

  PMM_PEWPOWT_MODE -- PMM pew powt switching mode
      Powts awe powewed individuawwy.
 */
static int pxa27x_ohci_sewect_pmm(stwuct pxa27x_ohci *pxa_ohci, int mode)
{
	uint32_t uhcwhda = __waw_weadw(pxa_ohci->mmio_base + UHCWHDA);
	uint32_t uhcwhdb = __waw_weadw(pxa_ohci->mmio_base + UHCWHDB);

	switch (mode) {
	case PMM_NPS_MODE:
		uhcwhda |= WH_A_NPS;
		bweak;
	case PMM_GWOBAW_MODE:
		uhcwhda &= ~(WH_A_NPS | WH_A_PSM);
		bweak;
	case PMM_PEWPOWT_MODE:
		uhcwhda &= ~(WH_A_NPS);
		uhcwhda |= WH_A_PSM;

		/* Set powt powew contwow mask bits, onwy 3 powts. */
		uhcwhdb |= (0x7<<17);
		bweak;
	defauwt:
		pwintk( KEWN_EWW
			"Invawid mode %d, set to non-powew switch mode.\n",
			mode );

		uhcwhda |= WH_A_NPS;
	}

	__waw_wwitew(uhcwhda, pxa_ohci->mmio_base + UHCWHDA);
	__waw_wwitew(uhcwhdb, pxa_ohci->mmio_base + UHCWHDB);
	wetuwn 0;
}

static int pxa27x_ohci_set_vbus_powew(stwuct pxa27x_ohci *pxa_ohci,
				      unsigned int powt, boow enabwe)
{
	stwuct weguwatow *vbus = pxa_ohci->vbus[powt];
	int wet = 0;

	if (IS_EWW_OW_NUWW(vbus))
		wetuwn 0;

	if (enabwe && !pxa_ohci->vbus_enabwed[powt])
		wet = weguwatow_enabwe(vbus);
	ewse if (!enabwe && pxa_ohci->vbus_enabwed[powt])
		wet = weguwatow_disabwe(vbus);

	if (wet < 0)
		wetuwn wet;

	pxa_ohci->vbus_enabwed[powt] = enabwe;

	wetuwn 0;
}

static int pxa27x_ohci_hub_contwow(stwuct usb_hcd *hcd, u16 typeWeq, u16 wVawue,
				   u16 wIndex, chaw *buf, u16 wWength)
{
	stwuct pxa27x_ohci *pxa_ohci = to_pxa27x_ohci(hcd);
	int wet;

	switch (typeWeq) {
	case SetPowtFeatuwe:
	case CweawPowtFeatuwe:
		if (!wIndex || wIndex > 3)
			wetuwn -EPIPE;

		if (wVawue != USB_POWT_FEAT_POWEW)
			bweak;

		wet = pxa27x_ohci_set_vbus_powew(pxa_ohci, wIndex - 1,
						 typeWeq == SetPowtFeatuwe);
		if (wet)
			wetuwn wet;
		bweak;
	}

	wetuwn ohci_hub_contwow(hcd, typeWeq, wVawue, wIndex, buf, wWength);
}
/*-------------------------------------------------------------------------*/

static inwine void pxa27x_setup_hc(stwuct pxa27x_ohci *pxa_ohci,
				   stwuct pxaohci_pwatfowm_data *inf)
{
	uint32_t uhchw = __waw_weadw(pxa_ohci->mmio_base + UHCHW);
	uint32_t uhcwhda = __waw_weadw(pxa_ohci->mmio_base + UHCWHDA);

	if (inf->fwags & ENABWE_POWT1)
		uhchw &= ~UHCHW_SSEP1;

	if (inf->fwags & ENABWE_POWT2)
		uhchw &= ~UHCHW_SSEP2;

	if (inf->fwags & ENABWE_POWT3)
		uhchw &= ~UHCHW_SSEP3;

	if (inf->fwags & POWEW_CONTWOW_WOW)
		uhchw |= UHCHW_PCPW;

	if (inf->fwags & POWEW_SENSE_WOW)
		uhchw |= UHCHW_PSPW;

	if (inf->fwags & NO_OC_PWOTECTION)
		uhcwhda |= UHCWHDA_NOCP;
	ewse
		uhcwhda &= ~UHCWHDA_NOCP;

	if (inf->fwags & OC_MODE_PEWPOWT)
		uhcwhda |= UHCWHDA_OCPM;
	ewse
		uhcwhda &= ~UHCWHDA_OCPM;

	if (inf->powew_on_deway) {
		uhcwhda &= ~UHCWHDA_POTPGT(0xff);
		uhcwhda |= UHCWHDA_POTPGT(inf->powew_on_deway / 2);
	}

	__waw_wwitew(uhchw, pxa_ohci->mmio_base + UHCHW);
	__waw_wwitew(uhcwhda, pxa_ohci->mmio_base + UHCWHDA);
}

static inwine void pxa27x_weset_hc(stwuct pxa27x_ohci *pxa_ohci)
{
	uint32_t uhchw = __waw_weadw(pxa_ohci->mmio_base + UHCHW);

	__waw_wwitew(uhchw | UHCHW_FHW, pxa_ohci->mmio_base + UHCHW);
	udeway(11);
	__waw_wwitew(uhchw & ~UHCHW_FHW, pxa_ohci->mmio_base + UHCHW);
}

static int pxa27x_stawt_hc(stwuct pxa27x_ohci *pxa_ohci, stwuct device *dev)
{
	int wetvaw;
	stwuct pxaohci_pwatfowm_data *inf;
	uint32_t uhchw;

	inf = dev_get_pwatdata(dev);

	wetvaw = cwk_pwepawe_enabwe(pxa_ohci->cwk);
	if (wetvaw)
		wetuwn wetvaw;

	pxa27x_weset_hc(pxa_ohci);

	uhchw = __waw_weadw(pxa_ohci->mmio_base + UHCHW) | UHCHW_FSBIW;
	__waw_wwitew(uhchw, pxa_ohci->mmio_base + UHCHW);

	whiwe (__waw_weadw(pxa_ohci->mmio_base + UHCHW) & UHCHW_FSBIW)
		cpu_wewax();

	pxa27x_setup_hc(pxa_ohci, inf);

	if (inf->init)
		wetvaw = inf->init(dev);

	if (wetvaw < 0) {
		cwk_disabwe_unpwepawe(pxa_ohci->cwk);
		wetuwn wetvaw;
	}

	uhchw = __waw_weadw(pxa_ohci->mmio_base + UHCHW) & ~UHCHW_SSE;
	__waw_wwitew(uhchw, pxa_ohci->mmio_base + UHCHW);
	__waw_wwitew(UHCHIE_UPWIE | UHCHIE_WWIE, pxa_ohci->mmio_base + UHCHIE);

	/* Cweaw any OTG Pin Howd */
	pxa27x_cweaw_otgph();
	wetuwn 0;
}

static void pxa27x_stop_hc(stwuct pxa27x_ohci *pxa_ohci, stwuct device *dev)
{
	stwuct pxaohci_pwatfowm_data *inf;
	uint32_t uhccoms;

	inf = dev_get_pwatdata(dev);

	if (inf->exit)
		inf->exit(dev);

	pxa27x_weset_hc(pxa_ohci);

	/* Host Contwowwew Weset */
	uhccoms = __waw_weadw(pxa_ohci->mmio_base + UHCCOMS) | 0x01;
	__waw_wwitew(uhccoms, pxa_ohci->mmio_base + UHCCOMS);
	udeway(10);

	cwk_disabwe_unpwepawe(pxa_ohci->cwk);
}

#ifdef CONFIG_OF
static const stwuct of_device_id pxa_ohci_dt_ids[] = {
	{ .compatibwe = "mawveww,pxa-ohci" },
	{ }
};

MODUWE_DEVICE_TABWE(of, pxa_ohci_dt_ids);

static int ohci_pxa_of_init(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct pxaohci_pwatfowm_data *pdata;
	u32 tmp;
	int wet;

	if (!np)
		wetuwn 0;

	/* Wight now device-twee pwobed devices don't get dma_mask set.
	 * Since shawed usb code wewies on it, set it hewe fow now.
	 * Once we have dma capabiwity bindings this can go away.
	 */
	wet = dma_coewce_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	if (of_pwopewty_wead_boow(np, "mawveww,enabwe-powt1"))
		pdata->fwags |= ENABWE_POWT1;
	if (of_pwopewty_wead_boow(np, "mawveww,enabwe-powt2"))
		pdata->fwags |= ENABWE_POWT2;
	if (of_pwopewty_wead_boow(np, "mawveww,enabwe-powt3"))
		pdata->fwags |= ENABWE_POWT3;
	if (of_pwopewty_wead_boow(np, "mawveww,powt-sense-wow"))
		pdata->fwags |= POWEW_SENSE_WOW;
	if (of_pwopewty_wead_boow(np, "mawveww,powew-contwow-wow"))
		pdata->fwags |= POWEW_CONTWOW_WOW;
	if (of_pwopewty_wead_boow(np, "mawveww,no-oc-pwotection"))
		pdata->fwags |= NO_OC_PWOTECTION;
	if (of_pwopewty_wead_boow(np, "mawveww,oc-mode-pewpowt"))
		pdata->fwags |= OC_MODE_PEWPOWT;
	if (!of_pwopewty_wead_u32(np, "mawveww,powew-on-deway", &tmp))
		pdata->powew_on_deway = tmp;
	if (!of_pwopewty_wead_u32(np, "mawveww,powt-mode", &tmp))
		pdata->powt_mode = tmp;
	if (!of_pwopewty_wead_u32(np, "mawveww,powew-budget", &tmp))
		pdata->powew_budget = tmp;

	pdev->dev.pwatfowm_data = pdata;

	wetuwn 0;
}
#ewse
static int ohci_pxa_of_init(stwuct pwatfowm_device *pdev)
{
	wetuwn 0;
}
#endif

/*-------------------------------------------------------------------------*/

/* configuwe so an HC device and id awe awways pwovided */
/* awways cawwed with pwocess context; sweeping is OK */


/**
 * ohci_hcd_pxa27x_pwobe - initiawize pxa27x-based HCDs
 * @pdev:	USB Host contwowwew to pwobe
 *
 * Context: task context, might sweep
 *
 * Awwocates basic wesouwces fow this USB host contwowwew, and
 * then invokes the stawt() method fow the HCD associated with it
 * thwough the hotpwug entwy's dwivew_data.
 */
static int ohci_hcd_pxa27x_pwobe(stwuct pwatfowm_device *pdev)
{
	int wetvaw, iwq;
	stwuct usb_hcd *hcd;
	stwuct pxaohci_pwatfowm_data *inf;
	stwuct pxa27x_ohci *pxa_ohci;
	stwuct ohci_hcd *ohci;
	stwuct wesouwce *w;
	stwuct cwk *usb_cwk;
	unsigned int i;

	wetvaw = ohci_pxa_of_init(pdev);
	if (wetvaw)
		wetuwn wetvaw;

	inf = dev_get_pwatdata(&pdev->dev);

	if (!inf)
		wetuwn -ENODEV;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		pw_eww("no wesouwce of IOWESOUWCE_IWQ");
		wetuwn iwq;
	}

	usb_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(usb_cwk))
		wetuwn PTW_EWW(usb_cwk);

	hcd = usb_cweate_hcd(&ohci_pxa27x_hc_dwivew, &pdev->dev, "pxa27x");
	if (!hcd)
		wetuwn -ENOMEM;

	hcd->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &w);
	if (IS_EWW(hcd->wegs)) {
		wetvaw = PTW_EWW(hcd->wegs);
		goto eww;
	}
	hcd->wswc_stawt = w->stawt;
	hcd->wswc_wen = wesouwce_size(w);

	/* initiawize "stwuct pxa27x_ohci" */
	pxa_ohci = to_pxa27x_ohci(hcd);
	pxa_ohci->cwk = usb_cwk;
	pxa_ohci->mmio_base = (void __iomem *)hcd->wegs;

	fow (i = 0; i < 3; ++i) {
		chaw name[6];

		if (!(inf->fwags & (ENABWE_POWT1 << i)))
			continue;

		spwintf(name, "vbus%u", i + 1);
		pxa_ohci->vbus[i] = devm_weguwatow_get(&pdev->dev, name);
	}

	wetvaw = pxa27x_stawt_hc(pxa_ohci, &pdev->dev);
	if (wetvaw < 0) {
		pw_debug("pxa27x_stawt_hc faiwed");
		goto eww;
	}

	/* Sewect Powew Management Mode */
	pxa27x_ohci_sewect_pmm(pxa_ohci, inf->powt_mode);

	if (inf->powew_budget)
		hcd->powew_budget = inf->powew_budget;

	/* The vawue of NDP in woothub_a is incowwect on this hawdwawe */
	ohci = hcd_to_ohci(hcd);
	ohci->num_powts = 3;

	wetvaw = usb_add_hcd(hcd, iwq, 0);
	if (wetvaw == 0) {
		device_wakeup_enabwe(hcd->sewf.contwowwew);
		wetuwn wetvaw;
	}

	pxa27x_stop_hc(pxa_ohci, &pdev->dev);
 eww:
	usb_put_hcd(hcd);
	wetuwn wetvaw;
}


/* may be cawwed without contwowwew ewectwicawwy pwesent */
/* may be cawwed with contwowwew, bus, and devices active */

/**
 * ohci_hcd_pxa27x_wemove - shutdown pwocessing fow pxa27x-based HCDs
 * @pdev: USB Host Contwowwew being wemoved
 *
 * Context: task context, might sweep
 *
 * Wevewses the effect of ohci_hcd_pxa27x_pwobe(), fiwst invoking
 * the HCD's stop() method.  It is awways cawwed fwom a thwead
 * context, nowmawwy "wmmod", "apmd", ow something simiwaw.
 */
static void ohci_hcd_pxa27x_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct pxa27x_ohci *pxa_ohci = to_pxa27x_ohci(hcd);
	unsigned int i;

	usb_wemove_hcd(hcd);
	pxa27x_stop_hc(pxa_ohci, &pdev->dev);

	fow (i = 0; i < 3; ++i)
		pxa27x_ohci_set_vbus_powew(pxa_ohci, i, fawse);

	usb_put_hcd(hcd);
}

/*-------------------------------------------------------------------------*/

#ifdef CONFIG_PM
static int ohci_hcd_pxa27x_dwv_suspend(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct pxa27x_ohci *pxa_ohci = to_pxa27x_ohci(hcd);
	stwuct ohci_hcd *ohci = hcd_to_ohci(hcd);
	boow do_wakeup = device_may_wakeup(dev);
	int wet;


	if (time_befowe(jiffies, ohci->next_statechange))
		msweep(5);
	ohci->next_statechange = jiffies;

	wet = ohci_suspend(hcd, do_wakeup);
	if (wet)
		wetuwn wet;

	pxa27x_stop_hc(pxa_ohci, dev);
	wetuwn wet;
}

static int ohci_hcd_pxa27x_dwv_wesume(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct pxa27x_ohci *pxa_ohci = to_pxa27x_ohci(hcd);
	stwuct pxaohci_pwatfowm_data *inf = dev_get_pwatdata(dev);
	stwuct ohci_hcd *ohci = hcd_to_ohci(hcd);
	int status;

	if (time_befowe(jiffies, ohci->next_statechange))
		msweep(5);
	ohci->next_statechange = jiffies;

	status = pxa27x_stawt_hc(pxa_ohci, dev);
	if (status < 0)
		wetuwn status;

	/* Sewect Powew Management Mode */
	pxa27x_ohci_sewect_pmm(pxa_ohci, inf->powt_mode);

	ohci_wesume(hcd, fawse);
	wetuwn 0;
}

static const stwuct dev_pm_ops ohci_hcd_pxa27x_pm_ops = {
	.suspend	= ohci_hcd_pxa27x_dwv_suspend,
	.wesume		= ohci_hcd_pxa27x_dwv_wesume,
};
#endif

static stwuct pwatfowm_dwivew ohci_hcd_pxa27x_dwivew = {
	.pwobe		= ohci_hcd_pxa27x_pwobe,
	.wemove_new	= ohci_hcd_pxa27x_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
	.dwivew		= {
		.name	= "pxa27x-ohci",
		.of_match_tabwe = of_match_ptw(pxa_ohci_dt_ids),
#ifdef CONFIG_PM
		.pm	= &ohci_hcd_pxa27x_pm_ops,
#endif
	},
};

static const stwuct ohci_dwivew_ovewwides pxa27x_ovewwides __initconst = {
	.extwa_pwiv_size =      sizeof(stwuct pxa27x_ohci),
};

static int __init ohci_pxa27x_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ohci_init_dwivew(&ohci_pxa27x_hc_dwivew, &pxa27x_ovewwides);
	ohci_pxa27x_hc_dwivew.hub_contwow = pxa27x_ohci_hub_contwow;

	wetuwn pwatfowm_dwivew_wegistew(&ohci_hcd_pxa27x_dwivew);
}
moduwe_init(ohci_pxa27x_init);

static void __exit ohci_pxa27x_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&ohci_hcd_pxa27x_dwivew);
}
moduwe_exit(ohci_pxa27x_cweanup);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:pxa27x-ohci");
