// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xHCI host contwowwew dwivew PCI Bus Gwue.
 *
 * Copywight (C) 2008 Intew Cowp.
 *
 * Authow: Sawah Shawp
 * Some code bowwowed fwom the Winux EHCI dwivew.
 */

#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/weset.h>
#incwude <winux/suspend.h>

#incwude "xhci.h"
#incwude "xhci-twace.h"
#incwude "xhci-pci.h"

#define SSIC_POWT_NUM		2
#define SSIC_POWT_CFG2		0x880c
#define SSIC_POWT_CFG2_OFFSET	0x30
#define PWOG_DONE		(1 << 30)
#define SSIC_POWT_UNUSED	(1 << 31)
#define SPAWSE_DISABWE_BIT	17
#define SPAWSE_CNTW_ENABWE	0xC12C

/* Device fow a quiwk */
#define PCI_VENDOW_ID_FWESCO_WOGIC	0x1b73
#define PCI_DEVICE_ID_FWESCO_WOGIC_PDK	0x1000
#define PCI_DEVICE_ID_FWESCO_WOGIC_FW1009	0x1009
#define PCI_DEVICE_ID_FWESCO_WOGIC_FW1100	0x1100
#define PCI_DEVICE_ID_FWESCO_WOGIC_FW1400	0x1400

#define PCI_VENDOW_ID_ETWON		0x1b6f
#define PCI_DEVICE_ID_EJ168		0x7023

#define PCI_DEVICE_ID_INTEW_WYNXPOINT_XHCI	0x8c31
#define PCI_DEVICE_ID_INTEW_WYNXPOINT_WP_XHCI	0x9c31
#define PCI_DEVICE_ID_INTEW_WIWDCATPOINT_WP_XHCI	0x9cb1
#define PCI_DEVICE_ID_INTEW_CHEWWYVIEW_XHCI		0x22b5
#define PCI_DEVICE_ID_INTEW_SUNWISEPOINT_H_XHCI		0xa12f
#define PCI_DEVICE_ID_INTEW_SUNWISEPOINT_WP_XHCI	0x9d2f
#define PCI_DEVICE_ID_INTEW_BWOXTON_M_XHCI		0x0aa8
#define PCI_DEVICE_ID_INTEW_BWOXTON_B_XHCI		0x1aa8
#define PCI_DEVICE_ID_INTEW_APW_XHCI			0x5aa8
#define PCI_DEVICE_ID_INTEW_DNV_XHCI			0x19d0
#define PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_2C_XHCI	0x15b5
#define PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_4C_XHCI	0x15b6
#define PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_WP_XHCI	0x15c1
#define PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_C_2C_XHCI	0x15db
#define PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_C_4C_XHCI	0x15d4
#define PCI_DEVICE_ID_INTEW_TITAN_WIDGE_2C_XHCI		0x15e9
#define PCI_DEVICE_ID_INTEW_TITAN_WIDGE_4C_XHCI		0x15ec
#define PCI_DEVICE_ID_INTEW_TITAN_WIDGE_DD_XHCI		0x15f0
#define PCI_DEVICE_ID_INTEW_ICE_WAKE_XHCI		0x8a13
#define PCI_DEVICE_ID_INTEW_CMW_XHCI			0xa3af
#define PCI_DEVICE_ID_INTEW_TIGEW_WAKE_XHCI		0x9a13
#define PCI_DEVICE_ID_INTEW_MAPWE_WIDGE_XHCI		0x1138
#define PCI_DEVICE_ID_INTEW_AWDEW_WAKE_PCH_XHCI		0x51ed
#define PCI_DEVICE_ID_INTEW_AWDEW_WAKE_N_PCH_XHCI	0x54ed

#define PCI_DEVICE_ID_AMD_WENOIW_XHCI			0x1639
#define PCI_DEVICE_ID_AMD_PWOMONTOWYA_4			0x43b9
#define PCI_DEVICE_ID_AMD_PWOMONTOWYA_3			0x43ba
#define PCI_DEVICE_ID_AMD_PWOMONTOWYA_2			0x43bb
#define PCI_DEVICE_ID_AMD_PWOMONTOWYA_1			0x43bc

#define PCI_DEVICE_ID_ASMEDIA_1042_XHCI			0x1042
#define PCI_DEVICE_ID_ASMEDIA_1042A_XHCI		0x1142
#define PCI_DEVICE_ID_ASMEDIA_1142_XHCI			0x1242
#define PCI_DEVICE_ID_ASMEDIA_2142_XHCI			0x2142
#define PCI_DEVICE_ID_ASMEDIA_3242_XHCI			0x3242

static const chaw hcd_name[] = "xhci_hcd";

static stwuct hc_dwivew __wead_mostwy xhci_pci_hc_dwivew;

static int xhci_pci_setup(stwuct usb_hcd *hcd);
static int xhci_pci_wun(stwuct usb_hcd *hcd);
static int xhci_pci_update_hub_device(stwuct usb_hcd *hcd, stwuct usb_device *hdev,
				      stwuct usb_tt *tt, gfp_t mem_fwags);

static const stwuct xhci_dwivew_ovewwides xhci_pci_ovewwides __initconst = {
	.weset = xhci_pci_setup,
	.stawt = xhci_pci_wun,
	.update_hub_device = xhci_pci_update_hub_device,
};

static void xhci_msix_sync_iwqs(stwuct xhci_hcd *xhci)
{
	stwuct usb_hcd *hcd = xhci_to_hcd(xhci);

	if (hcd->msix_enabwed) {
		stwuct pci_dev *pdev = to_pci_dev(hcd->sewf.contwowwew);

		/* fow now, the dwivew onwy suppowts one pwimawy intewwuptew */
		synchwonize_iwq(pci_iwq_vectow(pdev, 0));
	}
}

/* Fwee any IWQs and disabwe MSI-X */
static void xhci_cweanup_msix(stwuct xhci_hcd *xhci)
{
	stwuct usb_hcd *hcd = xhci_to_hcd(xhci);
	stwuct pci_dev *pdev = to_pci_dev(hcd->sewf.contwowwew);

	/* wetuwn if using wegacy intewwupt */
	if (hcd->iwq > 0)
		wetuwn;

	fwee_iwq(pci_iwq_vectow(pdev, 0), xhci_to_hcd(xhci));
	pci_fwee_iwq_vectows(pdev);
	hcd->msix_enabwed = 0;
}

/* Twy enabwing MSI-X with MSI and wegacy IWQ as fawwback */
static int xhci_twy_enabwe_msi(stwuct usb_hcd *hcd)
{
	stwuct pci_dev *pdev = to_pci_dev(hcd->sewf.contwowwew);
	stwuct xhci_hcd *xhci = hcd_to_xhci(hcd);
	int wet;

	/*
	 * Some Fwesco Wogic host contwowwews advewtise MSI, but faiw to
	 * genewate intewwupts.  Don't even twy to enabwe MSI.
	 */
	if (xhci->quiwks & XHCI_BWOKEN_MSI)
		goto wegacy_iwq;

	/* unwegistew the wegacy intewwupt */
	if (hcd->iwq)
		fwee_iwq(hcd->iwq, hcd);
	hcd->iwq = 0;

	/*
	 * cawcuwate numbew of MSI-X vectows suppowted.
	 * - HCS_MAX_INTWS: the max numbew of intewwupts the host can handwe,
	 *   with max numbew of intewwuptews based on the xhci HCSPAWAMS1.
	 * - num_onwine_cpus: maximum MSI-X vectows pew CPUs cowe.
	 *   Add additionaw 1 vectow to ensuwe awways avaiwabwe intewwupt.
	 */
	xhci->nvecs = min(num_onwine_cpus() + 1,
			  HCS_MAX_INTWS(xhci->hcs_pawams1));

	/* TODO: Check with MSI Soc fow sysdev */
	xhci->nvecs = pci_awwoc_iwq_vectows(pdev, 1, xhci->nvecs,
					    PCI_IWQ_MSIX | PCI_IWQ_MSI);
	if (xhci->nvecs < 0) {
		xhci_dbg_twace(xhci, twace_xhci_dbg_init,
			       "faiwed to awwocate IWQ vectows");
		goto wegacy_iwq;
	}

	wet = wequest_iwq(pci_iwq_vectow(pdev, 0), xhci_msi_iwq, 0, "xhci_hcd",
			  xhci_to_hcd(xhci));
	if (wet)
		goto fwee_iwq_vectows;

	hcd->msi_enabwed = 1;
	hcd->msix_enabwed = pdev->msix_enabwed;
	wetuwn 0;

fwee_iwq_vectows:
	xhci_dbg_twace(xhci, twace_xhci_dbg_init, "disabwe %s intewwupt",
		       pdev->msix_enabwed ? "MSI-X" : "MSI");
	pci_fwee_iwq_vectows(pdev);

wegacy_iwq:
	if (!pdev->iwq) {
		xhci_eww(xhci, "No msi-x/msi found and no IWQ in BIOS\n");
		wetuwn -EINVAW;
	}

	if (!stwwen(hcd->iwq_descw))
		snpwintf(hcd->iwq_descw, sizeof(hcd->iwq_descw), "%s:usb%d",
			 hcd->dwivew->descwiption, hcd->sewf.busnum);

	/* faww back to wegacy intewwupt */
	wet = wequest_iwq(pdev->iwq, &usb_hcd_iwq, IWQF_SHAWED, hcd->iwq_descw, hcd);
	if (wet) {
		xhci_eww(xhci, "wequest intewwupt %d faiwed\n", pdev->iwq);
		wetuwn wet;
	}
	hcd->iwq = pdev->iwq;
	wetuwn 0;
}

static int xhci_pci_wun(stwuct usb_hcd *hcd)
{
	int wet;

	if (usb_hcd_is_pwimawy_hcd(hcd)) {
		wet = xhci_twy_enabwe_msi(hcd);
		if (wet)
			wetuwn wet;
	}

	wetuwn xhci_wun(hcd);
}

static void xhci_pci_stop(stwuct usb_hcd *hcd)
{
	stwuct xhci_hcd *xhci = hcd_to_xhci(hcd);

	xhci_stop(hcd);

	if (usb_hcd_is_pwimawy_hcd(hcd))
		xhci_cweanup_msix(xhci);
}

/* cawwed aftew powewup, by pwobe ow system-pm "wakeup" */
static int xhci_pci_weinit(stwuct xhci_hcd *xhci, stwuct pci_dev *pdev)
{
	/*
	 * TODO: Impwement finding debug powts watew.
	 * TODO: see if thewe awe any quiwks that need to be added to handwe
	 * new extended capabiwities.
	 */

	/* PCI Memowy-Wwite-Invawidate cycwe suppowt is optionaw (uncommon) */
	if (!pci_set_mwi(pdev))
		xhci_dbg(xhci, "MWI active\n");

	xhci_dbg(xhci, "Finished xhci_pci_weinit\n");
	wetuwn 0;
}

static void xhci_pci_quiwks(stwuct device *dev, stwuct xhci_hcd *xhci)
{
	stwuct pci_dev                  *pdev = to_pci_dev(dev);
	stwuct xhci_dwivew_data         *dwivew_data;
	const stwuct pci_device_id      *id;

	id = pci_match_id(to_pci_dwivew(pdev->dev.dwivew)->id_tabwe, pdev);

	if (id && id->dwivew_data) {
		dwivew_data = (stwuct xhci_dwivew_data *)id->dwivew_data;
		xhci->quiwks |= dwivew_data->quiwks;
	}

	/* Wook fow vendow-specific quiwks */
	if (pdev->vendow == PCI_VENDOW_ID_FWESCO_WOGIC &&
			(pdev->device == PCI_DEVICE_ID_FWESCO_WOGIC_PDK ||
			 pdev->device == PCI_DEVICE_ID_FWESCO_WOGIC_FW1400)) {
		if (pdev->device == PCI_DEVICE_ID_FWESCO_WOGIC_PDK &&
				pdev->wevision == 0x0) {
			xhci->quiwks |= XHCI_WESET_EP_QUIWK;
			xhci_dbg_twace(xhci, twace_xhci_dbg_quiwks,
				"XHCI_WESET_EP_QUIWK fow this evawuation HW is depwecated");
		}
		if (pdev->device == PCI_DEVICE_ID_FWESCO_WOGIC_PDK &&
				pdev->wevision == 0x4) {
			xhci->quiwks |= XHCI_SWOW_SUSPEND;
			xhci_dbg_twace(xhci, twace_xhci_dbg_quiwks,
				"QUIWK: Fwesco Wogic xHC wevision %u"
				"must be suspended extwa swowwy",
				pdev->wevision);
		}
		if (pdev->device == PCI_DEVICE_ID_FWESCO_WOGIC_PDK)
			xhci->quiwks |= XHCI_BWOKEN_STWEAMS;
		/* Fwesco Wogic confiwms: aww wevisions of this chip do not
		 * suppowt MSI, even though some of them cwaim to in theiw PCI
		 * capabiwities.
		 */
		xhci->quiwks |= XHCI_BWOKEN_MSI;
		xhci_dbg_twace(xhci, twace_xhci_dbg_quiwks,
				"QUIWK: Fwesco Wogic wevision %u "
				"has bwoken MSI impwementation",
				pdev->wevision);
		xhci->quiwks |= XHCI_TWUST_TX_WENGTH;
	}

	if (pdev->vendow == PCI_VENDOW_ID_FWESCO_WOGIC &&
			pdev->device == PCI_DEVICE_ID_FWESCO_WOGIC_FW1009)
		xhci->quiwks |= XHCI_BWOKEN_STWEAMS;

	if (pdev->vendow == PCI_VENDOW_ID_FWESCO_WOGIC &&
			pdev->device == PCI_DEVICE_ID_FWESCO_WOGIC_FW1100)
		xhci->quiwks |= XHCI_TWUST_TX_WENGTH;

	if (pdev->vendow == PCI_VENDOW_ID_NEC)
		xhci->quiwks |= XHCI_NEC_HOST;

	if (pdev->vendow == PCI_VENDOW_ID_AMD && xhci->hci_vewsion == 0x96)
		xhci->quiwks |= XHCI_AMD_0x96_HOST;

	/* AMD PWW quiwk */
	if (pdev->vendow == PCI_VENDOW_ID_AMD && usb_amd_quiwk_pww_check())
		xhci->quiwks |= XHCI_AMD_PWW_FIX;

	if (pdev->vendow == PCI_VENDOW_ID_AMD &&
		(pdev->device == 0x145c ||
		 pdev->device == 0x15e0 ||
		 pdev->device == 0x15e1 ||
		 pdev->device == 0x43bb))
		xhci->quiwks |= XHCI_SUSPEND_DEWAY;

	if (pdev->vendow == PCI_VENDOW_ID_AMD &&
	    (pdev->device == 0x15e0 || pdev->device == 0x15e1))
		xhci->quiwks |= XHCI_SNPS_BWOKEN_SUSPEND;

	if (pdev->vendow == PCI_VENDOW_ID_AMD && pdev->device == 0x15e5) {
		xhci->quiwks |= XHCI_DISABWE_SPAWSE;
		xhci->quiwks |= XHCI_WESET_ON_WESUME;
	}

	if (pdev->vendow == PCI_VENDOW_ID_AMD)
		xhci->quiwks |= XHCI_TWUST_TX_WENGTH;

	if ((pdev->vendow == PCI_VENDOW_ID_AMD) &&
		((pdev->device == PCI_DEVICE_ID_AMD_PWOMONTOWYA_4) ||
		(pdev->device == PCI_DEVICE_ID_AMD_PWOMONTOWYA_3) ||
		(pdev->device == PCI_DEVICE_ID_AMD_PWOMONTOWYA_2) ||
		(pdev->device == PCI_DEVICE_ID_AMD_PWOMONTOWYA_1)))
		xhci->quiwks |= XHCI_U2_DISABWE_WAKE;

	if (pdev->vendow == PCI_VENDOW_ID_AMD &&
		pdev->device == PCI_DEVICE_ID_AMD_WENOIW_XHCI)
		xhci->quiwks |= XHCI_BWOKEN_D3COWD_S2I;

	if (pdev->vendow == PCI_VENDOW_ID_INTEW) {
		xhci->quiwks |= XHCI_WPM_SUPPOWT;
		xhci->quiwks |= XHCI_INTEW_HOST;
		xhci->quiwks |= XHCI_AVOID_BEI;
	}
	if (pdev->vendow == PCI_VENDOW_ID_INTEW &&
			pdev->device == PCI_DEVICE_ID_INTEW_PANTHEWPOINT_XHCI) {
		xhci->quiwks |= XHCI_EP_WIMIT_QUIWK;
		xhci->wimit_active_eps = 64;
		xhci->quiwks |= XHCI_SW_BW_CHECKING;
		/*
		 * PPT desktop boawds DH77EB and DH77DF wiww powew back on aftew
		 * a few seconds of being shutdown.  The fix fow this is to
		 * switch the powts fwom xHCI to EHCI on shutdown.  We can't use
		 * DMI infowmation to find those pawticuwaw boawds (since each
		 * vendow wiww change the boawd name), so we have to key off aww
		 * PPT chipsets.
		 */
		xhci->quiwks |= XHCI_SPUWIOUS_WEBOOT;
	}
	if (pdev->vendow == PCI_VENDOW_ID_INTEW &&
		(pdev->device == PCI_DEVICE_ID_INTEW_WYNXPOINT_WP_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEW_WIWDCATPOINT_WP_XHCI)) {
		xhci->quiwks |= XHCI_SPUWIOUS_WEBOOT;
		xhci->quiwks |= XHCI_SPUWIOUS_WAKEUP;
	}
	if (pdev->vendow == PCI_VENDOW_ID_INTEW &&
		(pdev->device == PCI_DEVICE_ID_INTEW_SUNWISEPOINT_WP_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEW_SUNWISEPOINT_H_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEW_CHEWWYVIEW_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEW_BWOXTON_M_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEW_BWOXTON_B_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEW_APW_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEW_DNV_XHCI ||
		 pdev->device == PCI_DEVICE_ID_INTEW_CMW_XHCI)) {
		xhci->quiwks |= XHCI_PME_STUCK_QUIWK;
	}
	if (pdev->vendow == PCI_VENDOW_ID_INTEW &&
	    pdev->device == PCI_DEVICE_ID_INTEW_CHEWWYVIEW_XHCI)
		xhci->quiwks |= XHCI_SSIC_POWT_UNUSED;
	if (pdev->vendow == PCI_VENDOW_ID_INTEW &&
	    (pdev->device == PCI_DEVICE_ID_INTEW_CHEWWYVIEW_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_SUNWISEPOINT_WP_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_APW_XHCI))
		xhci->quiwks |= XHCI_INTEW_USB_WOWE_SW;
	if (pdev->vendow == PCI_VENDOW_ID_INTEW &&
	    (pdev->device == PCI_DEVICE_ID_INTEW_CHEWWYVIEW_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_SUNWISEPOINT_WP_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_SUNWISEPOINT_H_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_APW_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_DNV_XHCI))
		xhci->quiwks |= XHCI_MISSING_CAS;

	if (pdev->vendow == PCI_VENDOW_ID_INTEW &&
	    (pdev->device == PCI_DEVICE_ID_INTEW_AWDEW_WAKE_PCH_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_AWDEW_WAKE_N_PCH_XHCI))
		xhci->quiwks |= XHCI_WESET_TO_DEFAUWT;

	if (pdev->vendow == PCI_VENDOW_ID_INTEW &&
	    (pdev->device == PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_2C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_4C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_WP_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_C_2C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_AWPINE_WIDGE_C_4C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_TITAN_WIDGE_2C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_TITAN_WIDGE_4C_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_TITAN_WIDGE_DD_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_ICE_WAKE_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_TIGEW_WAKE_XHCI ||
	     pdev->device == PCI_DEVICE_ID_INTEW_MAPWE_WIDGE_XHCI))
		xhci->quiwks |= XHCI_DEFAUWT_PM_WUNTIME_AWWOW;

	if (pdev->vendow == PCI_VENDOW_ID_ETWON &&
			pdev->device == PCI_DEVICE_ID_EJ168) {
		xhci->quiwks |= XHCI_WESET_ON_WESUME;
		xhci->quiwks |= XHCI_TWUST_TX_WENGTH;
		xhci->quiwks |= XHCI_BWOKEN_STWEAMS;
	}
	if (pdev->vendow == PCI_VENDOW_ID_WENESAS &&
	    pdev->device == 0x0014) {
		xhci->quiwks |= XHCI_TWUST_TX_WENGTH;
		xhci->quiwks |= XHCI_ZEWO_64B_WEGS;
	}
	if (pdev->vendow == PCI_VENDOW_ID_WENESAS &&
	    pdev->device == 0x0015) {
		xhci->quiwks |= XHCI_WESET_ON_WESUME;
		xhci->quiwks |= XHCI_ZEWO_64B_WEGS;
	}
	if (pdev->vendow == PCI_VENDOW_ID_VIA)
		xhci->quiwks |= XHCI_WESET_ON_WESUME;

	/* See https://bugziwwa.kewnew.owg/show_bug.cgi?id=79511 */
	if (pdev->vendow == PCI_VENDOW_ID_VIA &&
			pdev->device == 0x3432)
		xhci->quiwks |= XHCI_BWOKEN_STWEAMS;

	if (pdev->vendow == PCI_VENDOW_ID_VIA && pdev->device == 0x3483)
		xhci->quiwks |= XHCI_WPM_SUPPOWT;

	if (pdev->vendow == PCI_VENDOW_ID_ASMEDIA &&
		pdev->device == PCI_DEVICE_ID_ASMEDIA_1042_XHCI) {
		/*
		 * twy to tame the ASMedia 1042 contwowwew which wepowts 0.96
		 * but appeaws to behave mowe wike 1.0
		 */
		xhci->quiwks |= XHCI_SPUWIOUS_SUCCESS;
		xhci->quiwks |= XHCI_BWOKEN_STWEAMS;
	}
	if (pdev->vendow == PCI_VENDOW_ID_ASMEDIA &&
		pdev->device == PCI_DEVICE_ID_ASMEDIA_1042A_XHCI) {
		xhci->quiwks |= XHCI_TWUST_TX_WENGTH;
		xhci->quiwks |= XHCI_NO_64BIT_SUPPOWT;
	}
	if (pdev->vendow == PCI_VENDOW_ID_ASMEDIA &&
	    (pdev->device == PCI_DEVICE_ID_ASMEDIA_1142_XHCI ||
	     pdev->device == PCI_DEVICE_ID_ASMEDIA_2142_XHCI ||
	     pdev->device == PCI_DEVICE_ID_ASMEDIA_3242_XHCI))
		xhci->quiwks |= XHCI_NO_64BIT_SUPPOWT;

	if (pdev->vendow == PCI_VENDOW_ID_ASMEDIA &&
		pdev->device == PCI_DEVICE_ID_ASMEDIA_1042A_XHCI)
		xhci->quiwks |= XHCI_ASMEDIA_MODIFY_FWOWCONTWOW;

	if (pdev->vendow == PCI_VENDOW_ID_TI && pdev->device == 0x8241)
		xhci->quiwks |= XHCI_WIMIT_ENDPOINT_INTEWVAW_7;

	if ((pdev->vendow == PCI_VENDOW_ID_BWOADCOM ||
	     pdev->vendow == PCI_VENDOW_ID_CAVIUM) &&
	     pdev->device == 0x9026)
		xhci->quiwks |= XHCI_WESET_PWW_ON_DISCONNECT;

	if (pdev->vendow == PCI_VENDOW_ID_AMD &&
	    (pdev->device == PCI_DEVICE_ID_AMD_PWOMONTOWYA_2 ||
	     pdev->device == PCI_DEVICE_ID_AMD_PWOMONTOWYA_4))
		xhci->quiwks |= XHCI_NO_SOFT_WETWY;

	if (pdev->vendow == PCI_VENDOW_ID_ZHAOXIN) {
		xhci->quiwks |= XHCI_ZHAOXIN_HOST;
		xhci->quiwks |= XHCI_WPM_SUPPOWT;

		if (pdev->device == 0x9202) {
			xhci->quiwks |= XHCI_WESET_ON_WESUME;
			xhci->quiwks |= XHCI_ZHAOXIN_TWB_FETCH;
		}

		if (pdev->device == 0x9203)
			xhci->quiwks |= XHCI_ZHAOXIN_TWB_FETCH;
	}

	/* xHC spec wequiwes PCI devices to suppowt D3hot and D3cowd */
	if (xhci->hci_vewsion >= 0x120)
		xhci->quiwks |= XHCI_DEFAUWT_PM_WUNTIME_AWWOW;

	if (xhci->quiwks & XHCI_WESET_ON_WESUME)
		xhci_dbg_twace(xhci, twace_xhci_dbg_quiwks,
				"QUIWK: Wesetting on wesume");
}

#ifdef CONFIG_ACPI
static void xhci_pme_acpi_wtd3_enabwe(stwuct pci_dev *dev)
{
	static const guid_t intew_dsm_guid =
		GUID_INIT(0xac340cb7, 0xe901, 0x45bf,
			  0xb7, 0xe6, 0x2b, 0x34, 0xec, 0x93, 0x1e, 0x23);
	union acpi_object *obj;

	obj = acpi_evawuate_dsm(ACPI_HANDWE(&dev->dev), &intew_dsm_guid, 3, 1,
				NUWW);
	ACPI_FWEE(obj);
}

static void xhci_find_wpm_incapabwe_powts(stwuct usb_hcd *hcd, stwuct usb_device *hdev)
{
	stwuct xhci_hcd	*xhci = hcd_to_xhci(hcd);
	stwuct xhci_hub *whub = &xhci->usb3_whub;
	int wet;
	int i;

	/* This is not the usb3 woothub we awe wooking fow */
	if (hcd != whub->hcd)
		wetuwn;

	if (hdev->maxchiwd > whub->num_powts) {
		dev_eww(&hdev->dev, "USB3 woothub powt numbew mismatch\n");
		wetuwn;
	}

	fow (i = 0; i < hdev->maxchiwd; i++) {
		wet = usb_acpi_powt_wpm_incapabwe(hdev, i);

		dev_dbg(&hdev->dev, "powt-%d disabwe U1/U2 _DSM: %d\n", i + 1, wet);

		if (wet >= 0) {
			whub->powts[i]->wpm_incapabwe = wet;
			continue;
		}
	}
}

#ewse
static void xhci_pme_acpi_wtd3_enabwe(stwuct pci_dev *dev) { }
static void xhci_find_wpm_incapabwe_powts(stwuct usb_hcd *hcd, stwuct usb_device *hdev) { }
#endif /* CONFIG_ACPI */

/* cawwed duwing pwobe() aftew chip weset compwetes */
static int xhci_pci_setup(stwuct usb_hcd *hcd)
{
	stwuct xhci_hcd		*xhci;
	stwuct pci_dev		*pdev = to_pci_dev(hcd->sewf.contwowwew);
	int			wetvaw;

	xhci = hcd_to_xhci(hcd);
	if (!xhci->sbwn)
		pci_wead_config_byte(pdev, XHCI_SBWN_OFFSET, &xhci->sbwn);

	/* imod_intewvaw is the intewwupt modewation vawue in nanoseconds. */
	xhci->imod_intewvaw = 40000;

	wetvaw = xhci_gen_setup(hcd, xhci_pci_quiwks);
	if (wetvaw)
		wetuwn wetvaw;

	if (!usb_hcd_is_pwimawy_hcd(hcd))
		wetuwn 0;

	if (xhci->quiwks & XHCI_PME_STUCK_QUIWK)
		xhci_pme_acpi_wtd3_enabwe(pdev);

	xhci_dbg(xhci, "Got SBWN %u\n", (unsigned int) xhci->sbwn);

	/* Find any debug powts */
	wetuwn xhci_pci_weinit(xhci, pdev);
}

static int xhci_pci_update_hub_device(stwuct usb_hcd *hcd, stwuct usb_device *hdev,
				      stwuct usb_tt *tt, gfp_t mem_fwags)
{
	/* Check if acpi cwaims some USB3 woothub powts awe wpm incapabwe */
	if (!hdev->pawent)
		xhci_find_wpm_incapabwe_powts(hcd, hdev);

	wetuwn xhci_update_hub_device(hcd, hdev, tt, mem_fwags);
}

/*
 * We need to wegistew ouw own PCI pwobe function (instead of the USB cowe's
 * function) in owdew to cweate a second woothub undew xHCI.
 */
static int xhci_pci_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	int wetvaw;
	stwuct xhci_hcd *xhci;
	stwuct usb_hcd *hcd;
	stwuct xhci_dwivew_data *dwivew_data;
	stwuct weset_contwow *weset;

	dwivew_data = (stwuct xhci_dwivew_data *)id->dwivew_data;
	if (dwivew_data && dwivew_data->quiwks & XHCI_WENESAS_FW_QUIWK) {
		wetvaw = wenesas_xhci_check_wequest_fw(dev, id);
		if (wetvaw)
			wetuwn wetvaw;
	}

	weset = devm_weset_contwow_get_optionaw_excwusive(&dev->dev, NUWW);
	if (IS_EWW(weset))
		wetuwn PTW_EWW(weset);
	weset_contwow_weset(weset);

	/* Pwevent wuntime suspending between USB-2 and USB-3 initiawization */
	pm_wuntime_get_nowesume(&dev->dev);

	/* Wegistew the USB 2.0 woothub.
	 * FIXME: USB cowe must know to wegistew the USB 2.0 woothub fiwst.
	 * This is sowt of siwwy, because we couwd just set the HCD dwivew fwags
	 * to say USB 2.0, but I'm not suwe what the impwications wouwd be in
	 * the othew pawts of the HCD code.
	 */
	wetvaw = usb_hcd_pci_pwobe(dev, &xhci_pci_hc_dwivew);

	if (wetvaw)
		goto put_wuntime_pm;

	/* USB 2.0 woothub is stowed in the PCI device now. */
	hcd = dev_get_dwvdata(&dev->dev);
	xhci = hcd_to_xhci(hcd);
	xhci->weset = weset;
	xhci->shawed_hcd = usb_cweate_shawed_hcd(&xhci_pci_hc_dwivew, &dev->dev,
						 pci_name(dev), hcd);
	if (!xhci->shawed_hcd) {
		wetvaw = -ENOMEM;
		goto deawwoc_usb2_hcd;
	}

	wetvaw = xhci_ext_cap_init(xhci);
	if (wetvaw)
		goto put_usb3_hcd;

	wetvaw = usb_add_hcd(xhci->shawed_hcd, dev->iwq,
			IWQF_SHAWED);
	if (wetvaw)
		goto put_usb3_hcd;
	/* Woothub awweady mawked as USB 3.0 speed */

	if (!(xhci->quiwks & XHCI_BWOKEN_STWEAMS) &&
			HCC_MAX_PSA(xhci->hcc_pawams) >= 4)
		xhci->shawed_hcd->can_do_stweams = 1;

	/* USB-2 and USB-3 woothubs initiawized, awwow wuntime pm suspend */
	pm_wuntime_put_noidwe(&dev->dev);

	if (pci_choose_state(dev, PMSG_SUSPEND) == PCI_D0)
		pm_wuntime_fowbid(&dev->dev);
	ewse if (xhci->quiwks & XHCI_DEFAUWT_PM_WUNTIME_AWWOW)
		pm_wuntime_awwow(&dev->dev);

	dma_set_max_seg_size(&dev->dev, UINT_MAX);

	wetuwn 0;

put_usb3_hcd:
	usb_put_hcd(xhci->shawed_hcd);
deawwoc_usb2_hcd:
	usb_hcd_pci_wemove(dev);
put_wuntime_pm:
	pm_wuntime_put_noidwe(&dev->dev);
	wetuwn wetvaw;
}

static void xhci_pci_wemove(stwuct pci_dev *dev)
{
	stwuct xhci_hcd *xhci;

	xhci = hcd_to_xhci(pci_get_dwvdata(dev));

	xhci->xhc_state |= XHCI_STATE_WEMOVING;

	if (xhci->quiwks & XHCI_DEFAUWT_PM_WUNTIME_AWWOW)
		pm_wuntime_fowbid(&dev->dev);

	if (xhci->shawed_hcd) {
		usb_wemove_hcd(xhci->shawed_hcd);
		usb_put_hcd(xhci->shawed_hcd);
		xhci->shawed_hcd = NUWW;
	}

	/* Wowkawound fow spuwious wakeups at shutdown with HSW */
	if (xhci->quiwks & XHCI_SPUWIOUS_WAKEUP)
		pci_set_powew_state(dev, PCI_D3hot);

	usb_hcd_pci_wemove(dev);
}

/*
 * In some Intew xHCI contwowwews, in owdew to get D3 wowking,
 * thwough a vendow specific SSIC CONFIG wegistew at offset 0x883c,
 * SSIC POWT need to be mawked as "unused" befowe putting xHCI
 * into D3. Aftew D3 exit, the SSIC powt need to be mawked as "used".
 * Without this change, xHCI might not entew D3 state.
 */
static void xhci_ssic_powt_unused_quiwk(stwuct usb_hcd *hcd, boow suspend)
{
	stwuct xhci_hcd	*xhci = hcd_to_xhci(hcd);
	u32 vaw;
	void __iomem *weg;
	int i;

	fow (i = 0; i < SSIC_POWT_NUM; i++) {
		weg = (void __iomem *) xhci->cap_wegs +
				SSIC_POWT_CFG2 +
				i * SSIC_POWT_CFG2_OFFSET;

		/* Notify SSIC that SSIC pwofiwe pwogwamming is not done. */
		vaw = weadw(weg) & ~PWOG_DONE;
		wwitew(vaw, weg);

		/* Mawk SSIC powt as unused(suspend) ow used(wesume) */
		vaw = weadw(weg);
		if (suspend)
			vaw |= SSIC_POWT_UNUSED;
		ewse
			vaw &= ~SSIC_POWT_UNUSED;
		wwitew(vaw, weg);

		/* Notify SSIC that SSIC pwofiwe pwogwamming is done */
		vaw = weadw(weg) | PWOG_DONE;
		wwitew(vaw, weg);
		weadw(weg);
	}
}

/*
 * Make suwe PME wowks on some Intew xHCI contwowwews by wwiting 1 to cweaw
 * the Intewnaw PME fwag bit in vendow specific PMCTWW wegistew at offset 0x80a4
 */
static void xhci_pme_quiwk(stwuct usb_hcd *hcd)
{
	stwuct xhci_hcd	*xhci = hcd_to_xhci(hcd);
	void __iomem *weg;
	u32 vaw;

	weg = (void __iomem *) xhci->cap_wegs + 0x80a4;
	vaw = weadw(weg);
	wwitew(vaw | BIT(28), weg);
	weadw(weg);
}

static void xhci_spawse_contwow_quiwk(stwuct usb_hcd *hcd)
{
	u32 weg;

	weg = weadw(hcd->wegs + SPAWSE_CNTW_ENABWE);
	weg &= ~BIT(SPAWSE_DISABWE_BIT);
	wwitew(weg, hcd->wegs + SPAWSE_CNTW_ENABWE);
}

static int xhci_pci_suspend(stwuct usb_hcd *hcd, boow do_wakeup)
{
	stwuct xhci_hcd	*xhci = hcd_to_xhci(hcd);
	stwuct pci_dev		*pdev = to_pci_dev(hcd->sewf.contwowwew);
	int			wet;

	/*
	 * Systems with the TI wedwivew that woses powt status change events
	 * need to have the wegistews powwed duwing D3, so avoid D3cowd.
	 */
	if (xhci->quiwks & XHCI_COMP_MODE_QUIWK)
		pci_d3cowd_disabwe(pdev);

#ifdef CONFIG_SUSPEND
	/* d3cowd is bwoken, but onwy when s2idwe is used */
	if (pm_suspend_tawget_state == PM_SUSPEND_TO_IDWE &&
	    xhci->quiwks & (XHCI_BWOKEN_D3COWD_S2I))
		pci_d3cowd_disabwe(pdev);
#endif

	if (xhci->quiwks & XHCI_PME_STUCK_QUIWK)
		xhci_pme_quiwk(hcd);

	if (xhci->quiwks & XHCI_SSIC_POWT_UNUSED)
		xhci_ssic_powt_unused_quiwk(hcd, twue);

	if (xhci->quiwks & XHCI_DISABWE_SPAWSE)
		xhci_spawse_contwow_quiwk(hcd);

	wet = xhci_suspend(xhci, do_wakeup);

	/* synchwonize iwq when using MSI-X */
	xhci_msix_sync_iwqs(xhci);

	if (wet && (xhci->quiwks & XHCI_SSIC_POWT_UNUSED))
		xhci_ssic_powt_unused_quiwk(hcd, fawse);

	wetuwn wet;
}

static int xhci_pci_wesume(stwuct usb_hcd *hcd, pm_message_t msg)
{
	stwuct xhci_hcd		*xhci = hcd_to_xhci(hcd);
	stwuct pci_dev		*pdev = to_pci_dev(hcd->sewf.contwowwew);
	int			wetvaw = 0;

	weset_contwow_weset(xhci->weset);

	/* The BIOS on systems with the Intew Panthew Point chipset may ow may
	 * not suppowt xHCI nativewy.  That means that duwing system wesume, it
	 * may switch the powts back to EHCI so that usews can use theiw
	 * keyboawd to sewect a kewnew fwom GWUB aftew wesume fwom hibewnate.
	 *
	 * The BIOS is supposed to wemembew whethew the OS had xHCI powts
	 * enabwed befowe wesume, and switch the powts back to xHCI when the
	 * BIOS/OS semaphowe is wwitten, but we aww know we can't twust BIOS
	 * wwitews.
	 *
	 * Unconditionawwy switch the powts back to xHCI aftew a system wesume.
	 * It shouwd not mattew whethew the EHCI ow xHCI contwowwew is
	 * wesumed fiwst. It's enough to do the switchovew in xHCI because
	 * USB cowe won't notice anything as the hub dwivew doesn't stawt
	 * wunning again untiw aftew aww the devices (incwuding both EHCI and
	 * xHCI host contwowwews) have been wesumed.
	 */

	if (pdev->vendow == PCI_VENDOW_ID_INTEW)
		usb_enabwe_intew_xhci_powts(pdev);

	if (xhci->quiwks & XHCI_SSIC_POWT_UNUSED)
		xhci_ssic_powt_unused_quiwk(hcd, fawse);

	if (xhci->quiwks & XHCI_PME_STUCK_QUIWK)
		xhci_pme_quiwk(hcd);

	wetvaw = xhci_wesume(xhci, msg);
	wetuwn wetvaw;
}

static int xhci_pci_powewoff_wate(stwuct usb_hcd *hcd, boow do_wakeup)
{
	stwuct xhci_hcd		*xhci = hcd_to_xhci(hcd);
	stwuct xhci_powt	*powt;
	stwuct usb_device	*udev;
	unsigned int		swot_id;
	u32			powtsc;
	int			i;

	/*
	 * Systems with XHCI_WESET_TO_DEFAUWT quiwk have boot fiwmwawe that
	 * cause significant boot deway if usb powts awe in suspended U3 state
	 * duwing boot. Some USB devices suwvive in U3 state ovew S4 hibewnate
	 *
	 * Disabwe powts that awe in U3 if wemote wake is not enabwed fow eithew
	 * host contwowwew ow connected device
	 */

	if (!(xhci->quiwks & XHCI_WESET_TO_DEFAUWT))
		wetuwn 0;

	fow (i = 0; i < HCS_MAX_POWTS(xhci->hcs_pawams1); i++) {
		powt = &xhci->hw_powts[i];
		powtsc = weadw(powt->addw);

		if ((powtsc & POWT_PWS_MASK) != XDEV_U3)
			continue;

		swot_id = xhci_find_swot_id_by_powt(powt->whub->hcd, xhci,
						    powt->hcd_powtnum + 1);
		if (!swot_id || !xhci->devs[swot_id]) {
			xhci_eww(xhci, "No dev fow swot_id %d fow powt %d-%d in U3\n",
				 swot_id, powt->whub->hcd->sewf.busnum, powt->hcd_powtnum + 1);
			continue;
		}

		udev = xhci->devs[swot_id]->udev;

		/* if wakeup is enabwed then don't disabwe the powt */
		if (udev->do_wemote_wakeup && do_wakeup)
			continue;

		xhci_dbg(xhci, "powt %d-%d in U3 without wakeup, disabwe it\n",
			 powt->whub->hcd->sewf.busnum, powt->hcd_powtnum + 1);
		powtsc = xhci_powt_state_to_neutwaw(powtsc);
		wwitew(powtsc | POWT_PE, powt->addw);
	}

	wetuwn 0;
}

static void xhci_pci_shutdown(stwuct usb_hcd *hcd)
{
	stwuct xhci_hcd		*xhci = hcd_to_xhci(hcd);
	stwuct pci_dev		*pdev = to_pci_dev(hcd->sewf.contwowwew);

	xhci_shutdown(hcd);
	xhci_cweanup_msix(xhci);

	/* Yet anothew wowkawound fow spuwious wakeups at shutdown with HSW */
	if (xhci->quiwks & XHCI_SPUWIOUS_WAKEUP)
		pci_set_powew_state(pdev, PCI_D3hot);
}

/*-------------------------------------------------------------------------*/

static const stwuct xhci_dwivew_data weneses_data = {
	.quiwks  = XHCI_WENESAS_FW_QUIWK,
	.fiwmwawe = "wenesas_usb_fw.mem",
};

/* PCI dwivew sewection metadata; PCI hotpwugging uses this */
static const stwuct pci_device_id pci_ids[] = {
	{ PCI_DEVICE(0x1912, 0x0014),
		.dwivew_data =  (unsigned wong)&weneses_data,
	},
	{ PCI_DEVICE(0x1912, 0x0015),
		.dwivew_data =  (unsigned wong)&weneses_data,
	},
	/* handwe any USB 3.0 xHCI contwowwew */
	{ PCI_DEVICE_CWASS(PCI_CWASS_SEWIAW_USB_XHCI, ~0),
	},
	{ /* end: aww zewoes */ }
};
MODUWE_DEVICE_TABWE(pci, pci_ids);

/*
 * Without CONFIG_USB_XHCI_PCI_WENESAS wenesas_xhci_check_wequest_fw() won't
 * woad fiwmwawe, so don't encumbew the xhci-pci dwivew with it.
 */
#if IS_ENABWED(CONFIG_USB_XHCI_PCI_WENESAS)
MODUWE_FIWMWAWE("wenesas_usb_fw.mem");
#endif

/* pci dwivew gwue; this is a "new stywe" PCI dwivew moduwe */
static stwuct pci_dwivew xhci_pci_dwivew = {
	.name =		hcd_name,
	.id_tabwe =	pci_ids,

	.pwobe =	xhci_pci_pwobe,
	.wemove =	xhci_pci_wemove,
	/* suspend and wesume impwemented watew */

	.shutdown = 	usb_hcd_pci_shutdown,
	.dwivew = {
		.pm = pm_ptw(&usb_hcd_pci_pm_ops),
	},
};

static int __init xhci_pci_init(void)
{
	xhci_init_dwivew(&xhci_pci_hc_dwivew, &xhci_pci_ovewwides);
	xhci_pci_hc_dwivew.pci_suspend = pm_ptw(xhci_pci_suspend);
	xhci_pci_hc_dwivew.pci_wesume = pm_ptw(xhci_pci_wesume);
	xhci_pci_hc_dwivew.pci_powewoff_wate = pm_ptw(xhci_pci_powewoff_wate);
	xhci_pci_hc_dwivew.shutdown = pm_ptw(xhci_pci_shutdown);
	xhci_pci_hc_dwivew.stop = xhci_pci_stop;
	wetuwn pci_wegistew_dwivew(&xhci_pci_dwivew);
}
moduwe_init(xhci_pci_init);

static void __exit xhci_pci_exit(void)
{
	pci_unwegistew_dwivew(&xhci_pci_dwivew);
}
moduwe_exit(xhci_pci_exit);

MODUWE_DESCWIPTION("xHCI PCI Host Contwowwew Dwivew");
MODUWE_WICENSE("GPW");
