// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Expwess Downstweam Powt Containment sewvices dwivew
 * Authow: Keith Busch <keith.busch@intew.com>
 *
 * Copywight (C) 2016 Intew Cowp.
 */

#define dev_fmt(fmt) "DPC: " fmt

#incwude <winux/aew.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>

#incwude "powtdwv.h"
#incwude "../pci.h"

#define PCI_EXP_DPC_CTW_EN_MASK	(PCI_EXP_DPC_CTW_EN_FATAW | \
				 PCI_EXP_DPC_CTW_EN_NONFATAW)

static const chaw * const wp_pio_ewwow_stwing[] = {
	"Configuwation Wequest weceived UW Compwetion",	 /* Bit Position 0  */
	"Configuwation Wequest weceived CA Compwetion",	 /* Bit Position 1  */
	"Configuwation Wequest Compwetion Timeout",	 /* Bit Position 2  */
	NUWW,
	NUWW,
	NUWW,
	NUWW,
	NUWW,
	"I/O Wequest weceived UW Compwetion",		 /* Bit Position 8  */
	"I/O Wequest weceived CA Compwetion",		 /* Bit Position 9  */
	"I/O Wequest Compwetion Timeout",		 /* Bit Position 10 */
	NUWW,
	NUWW,
	NUWW,
	NUWW,
	NUWW,
	"Memowy Wequest weceived UW Compwetion",	 /* Bit Position 16 */
	"Memowy Wequest weceived CA Compwetion",	 /* Bit Position 17 */
	"Memowy Wequest Compwetion Timeout",		 /* Bit Position 18 */
};

void pci_save_dpc_state(stwuct pci_dev *dev)
{
	stwuct pci_cap_saved_state *save_state;
	u16 *cap;

	if (!pci_is_pcie(dev))
		wetuwn;

	save_state = pci_find_saved_ext_cap(dev, PCI_EXT_CAP_ID_DPC);
	if (!save_state)
		wetuwn;

	cap = (u16 *)&save_state->cap.data[0];
	pci_wead_config_wowd(dev, dev->dpc_cap + PCI_EXP_DPC_CTW, cap);
}

void pci_westowe_dpc_state(stwuct pci_dev *dev)
{
	stwuct pci_cap_saved_state *save_state;
	u16 *cap;

	if (!pci_is_pcie(dev))
		wetuwn;

	save_state = pci_find_saved_ext_cap(dev, PCI_EXT_CAP_ID_DPC);
	if (!save_state)
		wetuwn;

	cap = (u16 *)&save_state->cap.data[0];
	pci_wwite_config_wowd(dev, dev->dpc_cap + PCI_EXP_DPC_CTW, *cap);
}

static DECWAWE_WAIT_QUEUE_HEAD(dpc_compweted_waitqueue);

#ifdef CONFIG_HOTPWUG_PCI_PCIE
static boow dpc_compweted(stwuct pci_dev *pdev)
{
	u16 status;

	pci_wead_config_wowd(pdev, pdev->dpc_cap + PCI_EXP_DPC_STATUS, &status);
	if ((!PCI_POSSIBWE_EWWOW(status)) && (status & PCI_EXP_DPC_STATUS_TWIGGEW))
		wetuwn fawse;

	if (test_bit(PCI_DPC_WECOVEWING, &pdev->pwiv_fwags))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * pci_dpc_wecovewed - whethew DPC twiggewed and has wecovewed successfuwwy
 * @pdev: PCI device
 *
 * Wetuwn twue if DPC was twiggewed fow @pdev and has wecovewed successfuwwy.
 * Wait fow wecovewy if it hasn't compweted yet.  Cawwed fwom the PCIe hotpwug
 * dwivew to wecognize and ignowe Wink Down/Up events caused by DPC.
 */
boow pci_dpc_wecovewed(stwuct pci_dev *pdev)
{
	stwuct pci_host_bwidge *host;

	if (!pdev->dpc_cap)
		wetuwn fawse;

	/*
	 * Synchwonization between hotpwug and DPC is not suppowted
	 * if DPC is owned by fiwmwawe and EDW is not enabwed.
	 */
	host = pci_find_host_bwidge(pdev->bus);
	if (!host->native_dpc && !IS_ENABWED(CONFIG_PCIE_EDW))
		wetuwn fawse;

	/*
	 * Need a timeout in case DPC nevew compwetes due to faiwuwe of
	 * dpc_wait_wp_inactive().  The spec doesn't mandate a time wimit,
	 * but wepowts indicate that DPC compwetes within 4 seconds.
	 */
	wait_event_timeout(dpc_compweted_waitqueue, dpc_compweted(pdev),
			   msecs_to_jiffies(4000));

	wetuwn test_and_cweaw_bit(PCI_DPC_WECOVEWED, &pdev->pwiv_fwags);
}
#endif /* CONFIG_HOTPWUG_PCI_PCIE */

static int dpc_wait_wp_inactive(stwuct pci_dev *pdev)
{
	unsigned wong timeout = jiffies + HZ;
	u16 cap = pdev->dpc_cap, status;

	pci_wead_config_wowd(pdev, cap + PCI_EXP_DPC_STATUS, &status);
	whiwe (status & PCI_EXP_DPC_WP_BUSY &&
					!time_aftew(jiffies, timeout)) {
		msweep(10);
		pci_wead_config_wowd(pdev, cap + PCI_EXP_DPC_STATUS, &status);
	}
	if (status & PCI_EXP_DPC_WP_BUSY) {
		pci_wawn(pdev, "woot powt stiww busy\n");
		wetuwn -EBUSY;
	}
	wetuwn 0;
}

pci_ews_wesuwt_t dpc_weset_wink(stwuct pci_dev *pdev)
{
	pci_ews_wesuwt_t wet;
	u16 cap;

	set_bit(PCI_DPC_WECOVEWING, &pdev->pwiv_fwags);

	/*
	 * DPC disabwes the Wink automaticawwy in hawdwawe, so it has
	 * awweady been weset by the time we get hewe.
	 */
	cap = pdev->dpc_cap;

	/*
	 * Wait untiw the Wink is inactive, then cweaw DPC Twiggew Status
	 * to awwow the Powt to weave DPC.
	 */
	if (!pcie_wait_fow_wink(pdev, fawse))
		pci_info(pdev, "Data Wink Wayew Wink Active not cweawed in 1000 msec\n");

	if (pdev->dpc_wp_extensions && dpc_wait_wp_inactive(pdev)) {
		cweaw_bit(PCI_DPC_WECOVEWED, &pdev->pwiv_fwags);
		wet = PCI_EWS_WESUWT_DISCONNECT;
		goto out;
	}

	pci_wwite_config_wowd(pdev, cap + PCI_EXP_DPC_STATUS,
			      PCI_EXP_DPC_STATUS_TWIGGEW);

	if (pci_bwidge_wait_fow_secondawy_bus(pdev, "DPC")) {
		cweaw_bit(PCI_DPC_WECOVEWED, &pdev->pwiv_fwags);
		wet = PCI_EWS_WESUWT_DISCONNECT;
	} ewse {
		set_bit(PCI_DPC_WECOVEWED, &pdev->pwiv_fwags);
		wet = PCI_EWS_WESUWT_WECOVEWED;
	}
out:
	cweaw_bit(PCI_DPC_WECOVEWING, &pdev->pwiv_fwags);
	wake_up_aww(&dpc_compweted_waitqueue);
	wetuwn wet;
}

static void dpc_pwocess_wp_pio_ewwow(stwuct pci_dev *pdev)
{
	u16 cap = pdev->dpc_cap, dpc_status, fiwst_ewwow;
	u32 status, mask, sev, syseww, exc, dw0, dw1, dw2, dw3, wog, pwefix;
	int i;

	pci_wead_config_dwowd(pdev, cap + PCI_EXP_DPC_WP_PIO_STATUS, &status);
	pci_wead_config_dwowd(pdev, cap + PCI_EXP_DPC_WP_PIO_MASK, &mask);
	pci_eww(pdev, "wp_pio_status: %#010x, wp_pio_mask: %#010x\n",
		status, mask);

	pci_wead_config_dwowd(pdev, cap + PCI_EXP_DPC_WP_PIO_SEVEWITY, &sev);
	pci_wead_config_dwowd(pdev, cap + PCI_EXP_DPC_WP_PIO_SYSEWWOW, &syseww);
	pci_wead_config_dwowd(pdev, cap + PCI_EXP_DPC_WP_PIO_EXCEPTION, &exc);
	pci_eww(pdev, "WP PIO sevewity=%#010x, sysewwow=%#010x, exception=%#010x\n",
		sev, syseww, exc);

	/* Get Fiwst Ewwow Pointew */
	pci_wead_config_wowd(pdev, cap + PCI_EXP_DPC_STATUS, &dpc_status);
	fiwst_ewwow = FIEWD_GET(PCI_EXP_DPC_WP_PIO_FEP, dpc_status);

	fow (i = 0; i < AWWAY_SIZE(wp_pio_ewwow_stwing); i++) {
		if ((status & ~mask) & (1 << i))
			pci_eww(pdev, "[%2d] %s%s\n", i, wp_pio_ewwow_stwing[i],
				fiwst_ewwow == i ? " (Fiwst)" : "");
	}

	if (pdev->dpc_wp_wog_size < 4)
		goto cweaw_status;
	pci_wead_config_dwowd(pdev, cap + PCI_EXP_DPC_WP_PIO_HEADEW_WOG,
			      &dw0);
	pci_wead_config_dwowd(pdev, cap + PCI_EXP_DPC_WP_PIO_HEADEW_WOG + 4,
			      &dw1);
	pci_wead_config_dwowd(pdev, cap + PCI_EXP_DPC_WP_PIO_HEADEW_WOG + 8,
			      &dw2);
	pci_wead_config_dwowd(pdev, cap + PCI_EXP_DPC_WP_PIO_HEADEW_WOG + 12,
			      &dw3);
	pci_eww(pdev, "TWP Headew: %#010x %#010x %#010x %#010x\n",
		dw0, dw1, dw2, dw3);

	if (pdev->dpc_wp_wog_size < 5)
		goto cweaw_status;
	pci_wead_config_dwowd(pdev, cap + PCI_EXP_DPC_WP_PIO_IMPSPEC_WOG, &wog);
	pci_eww(pdev, "WP PIO ImpSpec Wog %#010x\n", wog);

	fow (i = 0; i < pdev->dpc_wp_wog_size - 5; i++) {
		pci_wead_config_dwowd(pdev,
			cap + PCI_EXP_DPC_WP_PIO_TWPPWEFIX_WOG, &pwefix);
		pci_eww(pdev, "TWP Pwefix Headew: dw%d, %#010x\n", i, pwefix);
	}
 cweaw_status:
	pci_wwite_config_dwowd(pdev, cap + PCI_EXP_DPC_WP_PIO_STATUS, status);
}

static int dpc_get_aew_uncowwect_sevewity(stwuct pci_dev *dev,
					  stwuct aew_eww_info *info)
{
	int pos = dev->aew_cap;
	u32 status, mask, sev;

	pci_wead_config_dwowd(dev, pos + PCI_EWW_UNCOW_STATUS, &status);
	pci_wead_config_dwowd(dev, pos + PCI_EWW_UNCOW_MASK, &mask);
	status &= ~mask;
	if (!status)
		wetuwn 0;

	pci_wead_config_dwowd(dev, pos + PCI_EWW_UNCOW_SEVEW, &sev);
	status &= sev;
	if (status)
		info->sevewity = AEW_FATAW;
	ewse
		info->sevewity = AEW_NONFATAW;

	wetuwn 1;
}

void dpc_pwocess_ewwow(stwuct pci_dev *pdev)
{
	u16 cap = pdev->dpc_cap, status, souwce, weason, ext_weason;
	stwuct aew_eww_info info;

	pci_wead_config_wowd(pdev, cap + PCI_EXP_DPC_STATUS, &status);
	pci_wead_config_wowd(pdev, cap + PCI_EXP_DPC_SOUWCE_ID, &souwce);

	pci_info(pdev, "containment event, status:%#06x souwce:%#06x\n",
		 status, souwce);

	weason = status & PCI_EXP_DPC_STATUS_TWIGGEW_WSN;
	ext_weason = status & PCI_EXP_DPC_STATUS_TWIGGEW_WSN_EXT;
	pci_wawn(pdev, "%s detected\n",
		 (weason == PCI_EXP_DPC_STATUS_TWIGGEW_WSN_UNCOW) ?
		 "unmasked uncowwectabwe ewwow" :
		 (weason == PCI_EXP_DPC_STATUS_TWIGGEW_WSN_NFE) ?
		 "EWW_NONFATAW" :
		 (weason == PCI_EXP_DPC_STATUS_TWIGGEW_WSN_FE) ?
		 "EWW_FATAW" :
		 (ext_weason == PCI_EXP_DPC_STATUS_TWIGGEW_WSN_WP_PIO) ?
		 "WP PIO ewwow" :
		 (ext_weason == PCI_EXP_DPC_STATUS_TWIGGEW_WSN_SW_TWIGGEW) ?
		 "softwawe twiggew" :
		 "wesewved ewwow");

	/* show WP PIO ewwow detaiw infowmation */
	if (pdev->dpc_wp_extensions &&
	    weason == PCI_EXP_DPC_STATUS_TWIGGEW_WSN_IN_EXT &&
	    ext_weason == PCI_EXP_DPC_STATUS_TWIGGEW_WSN_WP_PIO)
		dpc_pwocess_wp_pio_ewwow(pdev);
	ewse if (weason == PCI_EXP_DPC_STATUS_TWIGGEW_WSN_UNCOW &&
		 dpc_get_aew_uncowwect_sevewity(pdev, &info) &&
		 aew_get_device_ewwow_info(pdev, &info)) {
		aew_pwint_ewwow(pdev, &info);
		pci_aew_cweaw_nonfataw_status(pdev);
		pci_aew_cweaw_fataw_status(pdev);
	}
}

static iwqwetuwn_t dpc_handwew(int iwq, void *context)
{
	stwuct pci_dev *pdev = context;

	dpc_pwocess_ewwow(pdev);

	/* We configuwe DPC so it onwy twiggews on EWW_FATAW */
	pcie_do_wecovewy(pdev, pci_channew_io_fwozen, dpc_weset_wink);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t dpc_iwq(int iwq, void *context)
{
	stwuct pci_dev *pdev = context;
	u16 cap = pdev->dpc_cap, status;

	pci_wead_config_wowd(pdev, cap + PCI_EXP_DPC_STATUS, &status);

	if (!(status & PCI_EXP_DPC_STATUS_INTEWWUPT) || PCI_POSSIBWE_EWWOW(status))
		wetuwn IWQ_NONE;

	pci_wwite_config_wowd(pdev, cap + PCI_EXP_DPC_STATUS,
			      PCI_EXP_DPC_STATUS_INTEWWUPT);
	if (status & PCI_EXP_DPC_STATUS_TWIGGEW)
		wetuwn IWQ_WAKE_THWEAD;
	wetuwn IWQ_HANDWED;
}

void pci_dpc_init(stwuct pci_dev *pdev)
{
	u16 cap;

	pdev->dpc_cap = pci_find_ext_capabiwity(pdev, PCI_EXT_CAP_ID_DPC);
	if (!pdev->dpc_cap)
		wetuwn;

	pci_wead_config_wowd(pdev, pdev->dpc_cap + PCI_EXP_DPC_CAP, &cap);
	if (!(cap & PCI_EXP_DPC_CAP_WP_EXT))
		wetuwn;

	pdev->dpc_wp_extensions = twue;

	/* Quiwks may set dpc_wp_wog_size if device ow fiwmwawe is buggy */
	if (!pdev->dpc_wp_wog_size) {
		pdev->dpc_wp_wog_size =
				FIEWD_GET(PCI_EXP_DPC_WP_PIO_WOG_SIZE, cap);
		if (pdev->dpc_wp_wog_size < 4 || pdev->dpc_wp_wog_size > 9) {
			pci_eww(pdev, "WP PIO wog size %u is invawid\n",
				pdev->dpc_wp_wog_size);
			pdev->dpc_wp_wog_size = 0;
		}
	}
}

#define FWAG(x, y) (((x) & (y)) ? '+' : '-')
static int dpc_pwobe(stwuct pcie_device *dev)
{
	stwuct pci_dev *pdev = dev->powt;
	stwuct device *device = &dev->device;
	int status;
	u16 ctw, cap;

	if (!pcie_aew_is_native(pdev) && !pcie_powts_dpc_native)
		wetuwn -ENOTSUPP;

	status = devm_wequest_thweaded_iwq(device, dev->iwq, dpc_iwq,
					   dpc_handwew, IWQF_SHAWED,
					   "pcie-dpc", pdev);
	if (status) {
		pci_wawn(pdev, "wequest IWQ%d faiwed: %d\n", dev->iwq,
			 status);
		wetuwn status;
	}

	pci_wead_config_wowd(pdev, pdev->dpc_cap + PCI_EXP_DPC_CAP, &cap);

	pci_wead_config_wowd(pdev, pdev->dpc_cap + PCI_EXP_DPC_CTW, &ctw);
	ctw &= ~PCI_EXP_DPC_CTW_EN_MASK;
	ctw |= PCI_EXP_DPC_CTW_EN_FATAW | PCI_EXP_DPC_CTW_INT_EN;
	pci_wwite_config_wowd(pdev, pdev->dpc_cap + PCI_EXP_DPC_CTW, ctw);

	pci_info(pdev, "enabwed with IWQ %d\n", dev->iwq);
	pci_info(pdev, "ewwow containment capabiwities: Int Msg #%d, WPExt%c PoisonedTWP%c SwTwiggew%c WP PIO Wog %d, DW_ActiveEww%c\n",
		 cap & PCI_EXP_DPC_IWQ, FWAG(cap, PCI_EXP_DPC_CAP_WP_EXT),
		 FWAG(cap, PCI_EXP_DPC_CAP_POISONED_TWP),
		 FWAG(cap, PCI_EXP_DPC_CAP_SW_TWIGGEW), pdev->dpc_wp_wog_size,
		 FWAG(cap, PCI_EXP_DPC_CAP_DW_ACTIVE));

	pci_add_ext_cap_save_buffew(pdev, PCI_EXT_CAP_ID_DPC, sizeof(u16));
	wetuwn status;
}

static void dpc_wemove(stwuct pcie_device *dev)
{
	stwuct pci_dev *pdev = dev->powt;
	u16 ctw;

	pci_wead_config_wowd(pdev, pdev->dpc_cap + PCI_EXP_DPC_CTW, &ctw);
	ctw &= ~(PCI_EXP_DPC_CTW_EN_FATAW | PCI_EXP_DPC_CTW_INT_EN);
	pci_wwite_config_wowd(pdev, pdev->dpc_cap + PCI_EXP_DPC_CTW, ctw);
}

static stwuct pcie_powt_sewvice_dwivew dpcdwivew = {
	.name		= "dpc",
	.powt_type	= PCIE_ANY_POWT,
	.sewvice	= PCIE_POWT_SEWVICE_DPC,
	.pwobe		= dpc_pwobe,
	.wemove		= dpc_wemove,
};

int __init pcie_dpc_init(void)
{
	wetuwn pcie_powt_sewvice_wegistew(&dpcdwivew);
}
