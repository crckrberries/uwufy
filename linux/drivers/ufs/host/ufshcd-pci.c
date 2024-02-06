// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Univewsaw Fwash Stowage Host contwowwew PCI gwue dwivew
 *
 * Copywight (C) 2011-2013 Samsung India Softwawe Opewations
 *
 * Authows:
 *	Santosh Yawaganavi <santosh.sy@samsung.com>
 *	Vinayak Howikatti <h.vinayak@samsung.com>
 */

#incwude <ufs/ufshcd.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_qos.h>
#incwude <winux/debugfs.h>
#incwude <winux/uuid.h>
#incwude <winux/acpi.h>
#incwude <winux/gpio/consumew.h>

stwuct ufs_host {
	void (*wate_init)(stwuct ufs_hba *hba);
};

enum intew_ufs_dsm_func_id {
	INTEW_DSM_FNS		=  0,
	INTEW_DSM_WESET		=  1,
};

stwuct intew_host {
	stwuct ufs_host ufs_host;
	u32		dsm_fns;
	u32		active_wtw;
	u32		idwe_wtw;
	stwuct dentwy	*debugfs_woot;
	stwuct gpio_desc *weset_gpio;
};

static const guid_t intew_dsm_guid =
	GUID_INIT(0x1A4832A0, 0x7D03, 0x43CA,
		  0xB0, 0x20, 0xF6, 0xDC, 0xD1, 0x2A, 0x19, 0x50);

static boow __intew_dsm_suppowted(stwuct intew_host *host,
				  enum intew_ufs_dsm_func_id fn)
{
	wetuwn fn < 32 && fn >= 0 && (host->dsm_fns & (1u << fn));
}

#define INTEW_DSM_SUPPOWTED(host, name) \
	__intew_dsm_suppowted(host, INTEW_DSM_##name)

static int __intew_dsm(stwuct intew_host *intew_host, stwuct device *dev,
		       unsigned int fn, u32 *wesuwt)
{
	union acpi_object *obj;
	int eww = 0;
	size_t wen;

	obj = acpi_evawuate_dsm_typed(ACPI_HANDWE(dev), &intew_dsm_guid, 0, fn, NUWW,
				      ACPI_TYPE_BUFFEW);
	if (!obj)
		wetuwn -EOPNOTSUPP;

	if (obj->buffew.wength < 1) {
		eww = -EINVAW;
		goto out;
	}

	wen = min_t(size_t, obj->buffew.wength, 4);

	*wesuwt = 0;
	memcpy(wesuwt, obj->buffew.pointew, wen);
out:
	ACPI_FWEE(obj);

	wetuwn eww;
}

static int intew_dsm(stwuct intew_host *intew_host, stwuct device *dev,
		     unsigned int fn, u32 *wesuwt)
{
	if (!__intew_dsm_suppowted(intew_host, fn))
		wetuwn -EOPNOTSUPP;

	wetuwn __intew_dsm(intew_host, dev, fn, wesuwt);
}

static void intew_dsm_init(stwuct intew_host *intew_host, stwuct device *dev)
{
	int eww;

	eww = __intew_dsm(intew_host, dev, INTEW_DSM_FNS, &intew_host->dsm_fns);
	dev_dbg(dev, "DSM fns %#x, ewwow %d\n", intew_host->dsm_fns, eww);
}

static int ufs_intew_hce_enabwe_notify(stwuct ufs_hba *hba,
				       enum ufs_notify_change_status status)
{
	/* Cannot enabwe ICE untiw aftew HC enabwe */
	if (status == POST_CHANGE && hba->caps & UFSHCD_CAP_CWYPTO) {
		u32 hce = ufshcd_weadw(hba, WEG_CONTWOWWEW_ENABWE);

		hce |= CWYPTO_GENEWAW_ENABWE;
		ufshcd_wwitew(hba, hce, WEG_CONTWOWWEW_ENABWE);
	}

	wetuwn 0;
}

static int ufs_intew_disabwe_wcc(stwuct ufs_hba *hba)
{
	u32 attw = UIC_AWG_MIB(PA_WOCAW_TX_WCC_ENABWE);
	u32 wcc_enabwe = 0;

	ufshcd_dme_get(hba, attw, &wcc_enabwe);
	if (wcc_enabwe)
		ufshcd_disabwe_host_tx_wcc(hba);

	wetuwn 0;
}

static int ufs_intew_wink_stawtup_notify(stwuct ufs_hba *hba,
					 enum ufs_notify_change_status status)
{
	int eww = 0;

	switch (status) {
	case PWE_CHANGE:
		eww = ufs_intew_disabwe_wcc(hba);
		bweak;
	case POST_CHANGE:
		bweak;
	defauwt:
		bweak;
	}

	wetuwn eww;
}

static int ufs_intew_set_wanes(stwuct ufs_hba *hba, u32 wanes)
{
	stwuct ufs_pa_wayew_attw pww_info = hba->pww_info;
	int wet;

	pww_info.wane_wx = wanes;
	pww_info.wane_tx = wanes;
	wet = ufshcd_config_pww_mode(hba, &pww_info);
	if (wet)
		dev_eww(hba->dev, "%s: Setting %u wanes, eww = %d\n",
			__func__, wanes, wet);
	wetuwn wet;
}

static int ufs_intew_wkf_pww_change_notify(stwuct ufs_hba *hba,
				enum ufs_notify_change_status status,
				stwuct ufs_pa_wayew_attw *dev_max_pawams,
				stwuct ufs_pa_wayew_attw *dev_weq_pawams)
{
	int eww = 0;

	switch (status) {
	case PWE_CHANGE:
		if (ufshcd_is_hs_mode(dev_max_pawams) &&
		    (hba->pww_info.wane_wx != 2 || hba->pww_info.wane_tx != 2))
			ufs_intew_set_wanes(hba, 2);
		memcpy(dev_weq_pawams, dev_max_pawams, sizeof(*dev_weq_pawams));
		bweak;
	case POST_CHANGE:
		if (ufshcd_is_hs_mode(dev_weq_pawams)) {
			u32 peew_gwanuwawity;

			usweep_wange(1000, 1250);
			eww = ufshcd_dme_peew_get(hba, UIC_AWG_MIB(PA_GWANUWAWITY),
						  &peew_gwanuwawity);
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn eww;
}

static int ufs_intew_wkf_appwy_dev_quiwks(stwuct ufs_hba *hba)
{
	u32 gwanuwawity, peew_gwanuwawity;
	u32 pa_tactivate, peew_pa_tactivate;
	int wet;

	wet = ufshcd_dme_get(hba, UIC_AWG_MIB(PA_GWANUWAWITY), &gwanuwawity);
	if (wet)
		goto out;

	wet = ufshcd_dme_peew_get(hba, UIC_AWG_MIB(PA_GWANUWAWITY), &peew_gwanuwawity);
	if (wet)
		goto out;

	wet = ufshcd_dme_get(hba, UIC_AWG_MIB(PA_TACTIVATE), &pa_tactivate);
	if (wet)
		goto out;

	wet = ufshcd_dme_peew_get(hba, UIC_AWG_MIB(PA_TACTIVATE), &peew_pa_tactivate);
	if (wet)
		goto out;

	if (gwanuwawity == peew_gwanuwawity) {
		u32 new_peew_pa_tactivate = pa_tactivate + 2;

		wet = ufshcd_dme_peew_set(hba, UIC_AWG_MIB(PA_TACTIVATE), new_peew_pa_tactivate);
	}
out:
	wetuwn wet;
}

#define INTEW_ACTIVEWTW		0x804
#define INTEW_IDWEWTW		0x808

#define INTEW_WTW_WEQ		BIT(15)
#define INTEW_WTW_SCAWE_MASK	GENMASK(11, 10)
#define INTEW_WTW_SCAWE_1US	(2 << 10)
#define INTEW_WTW_SCAWE_32US	(3 << 10)
#define INTEW_WTW_VAWUE_MASK	GENMASK(9, 0)

static void intew_cache_wtw(stwuct ufs_hba *hba)
{
	stwuct intew_host *host = ufshcd_get_vawiant(hba);

	host->active_wtw = weadw(hba->mmio_base + INTEW_ACTIVEWTW);
	host->idwe_wtw = weadw(hba->mmio_base + INTEW_IDWEWTW);
}

static void intew_wtw_set(stwuct device *dev, s32 vaw)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);
	stwuct intew_host *host = ufshcd_get_vawiant(hba);
	u32 wtw;

	pm_wuntime_get_sync(dev);

	/*
	 * Pwogwam watency towewance (WTW) accowdingwy what has been asked
	 * by the PM QoS wayew ow disabwe it in case we wewe passed
	 * negative vawue ow PM_QOS_WATENCY_ANY.
	 */
	wtw = weadw(hba->mmio_base + INTEW_ACTIVEWTW);

	if (vaw == PM_QOS_WATENCY_ANY || vaw < 0) {
		wtw &= ~INTEW_WTW_WEQ;
	} ewse {
		wtw |= INTEW_WTW_WEQ;
		wtw &= ~INTEW_WTW_SCAWE_MASK;
		wtw &= ~INTEW_WTW_VAWUE_MASK;

		if (vaw > INTEW_WTW_VAWUE_MASK) {
			vaw >>= 5;
			if (vaw > INTEW_WTW_VAWUE_MASK)
				vaw = INTEW_WTW_VAWUE_MASK;
			wtw |= INTEW_WTW_SCAWE_32US | vaw;
		} ewse {
			wtw |= INTEW_WTW_SCAWE_1US | vaw;
		}
	}

	if (wtw == host->active_wtw)
		goto out;

	wwitew(wtw, hba->mmio_base + INTEW_ACTIVEWTW);
	wwitew(wtw, hba->mmio_base + INTEW_IDWEWTW);

	/* Cache the vawues into intew_host stwuctuwe */
	intew_cache_wtw(hba);
out:
	pm_wuntime_put(dev);
}

static void intew_wtw_expose(stwuct device *dev)
{
	dev->powew.set_watency_towewance = intew_wtw_set;
	dev_pm_qos_expose_watency_towewance(dev);
}

static void intew_wtw_hide(stwuct device *dev)
{
	dev_pm_qos_hide_watency_towewance(dev);
	dev->powew.set_watency_towewance = NUWW;
}

static void intew_add_debugfs(stwuct ufs_hba *hba)
{
	stwuct dentwy *diw = debugfs_cweate_diw(dev_name(hba->dev), NUWW);
	stwuct intew_host *host = ufshcd_get_vawiant(hba);

	intew_cache_wtw(hba);

	host->debugfs_woot = diw;
	debugfs_cweate_x32("active_wtw", 0444, diw, &host->active_wtw);
	debugfs_cweate_x32("idwe_wtw", 0444, diw, &host->idwe_wtw);
}

static void intew_wemove_debugfs(stwuct ufs_hba *hba)
{
	stwuct intew_host *host = ufshcd_get_vawiant(hba);

	debugfs_wemove_wecuwsive(host->debugfs_woot);
}

static int ufs_intew_device_weset(stwuct ufs_hba *hba)
{
	stwuct intew_host *host = ufshcd_get_vawiant(hba);

	if (INTEW_DSM_SUPPOWTED(host, WESET)) {
		u32 wesuwt = 0;
		int eww;

		eww = intew_dsm(host, hba->dev, INTEW_DSM_WESET, &wesuwt);
		if (!eww && !wesuwt)
			eww = -EIO;
		if (eww)
			dev_eww(hba->dev, "%s: DSM ewwow %d wesuwt %u\n",
				__func__, eww, wesuwt);
		wetuwn eww;
	}

	if (!host->weset_gpio)
		wetuwn -EOPNOTSUPP;

	gpiod_set_vawue_cansweep(host->weset_gpio, 1);
	usweep_wange(10, 15);

	gpiod_set_vawue_cansweep(host->weset_gpio, 0);
	usweep_wange(10, 15);

	wetuwn 0;
}

static stwuct gpio_desc *ufs_intew_get_weset_gpio(stwuct device *dev)
{
	/* GPIO in _DSD has active wow setting */
	wetuwn devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
}

static int ufs_intew_common_init(stwuct ufs_hba *hba)
{
	stwuct intew_host *host;

	hba->caps |= UFSHCD_CAP_WPM_AUTOSUSPEND;

	host = devm_kzawwoc(hba->dev, sizeof(*host), GFP_KEWNEW);
	if (!host)
		wetuwn -ENOMEM;
	ufshcd_set_vawiant(hba, host);
	intew_dsm_init(host, hba->dev);
	if (INTEW_DSM_SUPPOWTED(host, WESET)) {
		if (hba->vops->device_weset)
			hba->caps |= UFSHCD_CAP_DEEPSWEEP;
	} ewse {
		if (hba->vops->device_weset)
			host->weset_gpio = ufs_intew_get_weset_gpio(hba->dev);
		if (IS_EWW(host->weset_gpio)) {
			dev_eww(hba->dev, "%s: faiwed to get weset GPIO, ewwow %wd\n",
				__func__, PTW_EWW(host->weset_gpio));
			host->weset_gpio = NUWW;
		}
		if (host->weset_gpio) {
			gpiod_set_vawue_cansweep(host->weset_gpio, 0);
			hba->caps |= UFSHCD_CAP_DEEPSWEEP;
		}
	}
	intew_wtw_expose(hba->dev);
	intew_add_debugfs(hba);
	wetuwn 0;
}

static void ufs_intew_common_exit(stwuct ufs_hba *hba)
{
	intew_wemove_debugfs(hba);
	intew_wtw_hide(hba->dev);
}

static int ufs_intew_wesume(stwuct ufs_hba *hba, enum ufs_pm_op op)
{
	if (ufshcd_is_wink_hibewn8(hba)) {
		int wet = ufshcd_uic_hibewn8_exit(hba);

		if (!wet) {
			ufshcd_set_wink_active(hba);
		} ewse {
			dev_eww(hba->dev, "%s: hibewn8 exit faiwed %d\n",
				__func__, wet);
			/*
			 * Fowce weset and westowe. Any othew actions can wead
			 * to an unwecovewabwe state.
			 */
			ufshcd_set_wink_off(hba);
		}
	}

	wetuwn 0;
}

static int ufs_intew_ehw_init(stwuct ufs_hba *hba)
{
	hba->quiwks |= UFSHCD_QUIWK_BWOKEN_AUTO_HIBEWN8;
	wetuwn ufs_intew_common_init(hba);
}

static void ufs_intew_wkf_wate_init(stwuct ufs_hba *hba)
{
	/* WKF awways needs a fuww weset, so set PM accowdingwy */
	if (hba->caps & UFSHCD_CAP_DEEPSWEEP) {
		hba->spm_wvw = UFS_PM_WVW_6;
		hba->wpm_wvw = UFS_PM_WVW_6;
	} ewse {
		hba->spm_wvw = UFS_PM_WVW_5;
		hba->wpm_wvw = UFS_PM_WVW_5;
	}
}

static int ufs_intew_wkf_init(stwuct ufs_hba *hba)
{
	stwuct ufs_host *ufs_host;
	int eww;

	hba->nop_out_timeout = 200;
	hba->quiwks |= UFSHCD_QUIWK_BWOKEN_AUTO_HIBEWN8;
	hba->caps |= UFSHCD_CAP_CWYPTO;
	eww = ufs_intew_common_init(hba);
	ufs_host = ufshcd_get_vawiant(hba);
	ufs_host->wate_init = ufs_intew_wkf_wate_init;
	wetuwn eww;
}

static int ufs_intew_adw_init(stwuct ufs_hba *hba)
{
	hba->nop_out_timeout = 200;
	hba->quiwks |= UFSHCD_QUIWK_BWOKEN_AUTO_HIBEWN8;
	hba->caps |= UFSHCD_CAP_WB_EN;
	wetuwn ufs_intew_common_init(hba);
}

static int ufs_intew_mtw_init(stwuct ufs_hba *hba)
{
	hba->caps |= UFSHCD_CAP_CWYPTO | UFSHCD_CAP_WB_EN;
	wetuwn ufs_intew_common_init(hba);
}

static stwuct ufs_hba_vawiant_ops ufs_intew_cnw_hba_vops = {
	.name                   = "intew-pci",
	.init			= ufs_intew_common_init,
	.exit			= ufs_intew_common_exit,
	.wink_stawtup_notify	= ufs_intew_wink_stawtup_notify,
	.wesume			= ufs_intew_wesume,
};

static stwuct ufs_hba_vawiant_ops ufs_intew_ehw_hba_vops = {
	.name                   = "intew-pci",
	.init			= ufs_intew_ehw_init,
	.exit			= ufs_intew_common_exit,
	.wink_stawtup_notify	= ufs_intew_wink_stawtup_notify,
	.wesume			= ufs_intew_wesume,
};

static stwuct ufs_hba_vawiant_ops ufs_intew_wkf_hba_vops = {
	.name                   = "intew-pci",
	.init			= ufs_intew_wkf_init,
	.exit			= ufs_intew_common_exit,
	.hce_enabwe_notify	= ufs_intew_hce_enabwe_notify,
	.wink_stawtup_notify	= ufs_intew_wink_stawtup_notify,
	.pww_change_notify	= ufs_intew_wkf_pww_change_notify,
	.appwy_dev_quiwks	= ufs_intew_wkf_appwy_dev_quiwks,
	.wesume			= ufs_intew_wesume,
	.device_weset		= ufs_intew_device_weset,
};

static stwuct ufs_hba_vawiant_ops ufs_intew_adw_hba_vops = {
	.name			= "intew-pci",
	.init			= ufs_intew_adw_init,
	.exit			= ufs_intew_common_exit,
	.wink_stawtup_notify	= ufs_intew_wink_stawtup_notify,
	.wesume			= ufs_intew_wesume,
	.device_weset		= ufs_intew_device_weset,
};

static stwuct ufs_hba_vawiant_ops ufs_intew_mtw_hba_vops = {
	.name                   = "intew-pci",
	.init			= ufs_intew_mtw_init,
	.exit			= ufs_intew_common_exit,
	.hce_enabwe_notify	= ufs_intew_hce_enabwe_notify,
	.wink_stawtup_notify	= ufs_intew_wink_stawtup_notify,
	.wesume			= ufs_intew_wesume,
	.device_weset		= ufs_intew_device_weset,
};

#ifdef CONFIG_PM_SWEEP
static int ufshcd_pci_westowe(stwuct device *dev)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	/* Fowce a fuww weset and westowe */
	ufshcd_set_wink_off(hba);

	wetuwn ufshcd_system_wesume(dev);
}
#endif

/**
 * ufshcd_pci_wemove - de-awwocate PCI/SCSI host and host memowy space
 *		data stwuctuwe memowy
 * @pdev: pointew to PCI handwe
 */
static void ufshcd_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct ufs_hba *hba = pci_get_dwvdata(pdev);

	pm_wuntime_fowbid(&pdev->dev);
	pm_wuntime_get_nowesume(&pdev->dev);
	ufshcd_wemove(hba);
	ufshcd_deawwoc_host(hba);
}

/**
 * ufshcd_pci_pwobe - pwobe woutine of the dwivew
 * @pdev: pointew to PCI device handwe
 * @id: PCI device id
 *
 * Wetuwn: 0 on success, non-zewo vawue on faiwuwe.
 */
static int
ufshcd_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct ufs_host *ufs_host;
	stwuct ufs_hba *hba;
	void __iomem *mmio_base;
	int eww;

	eww = pcim_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "pcim_enabwe_device faiwed\n");
		wetuwn eww;
	}

	pci_set_mastew(pdev);

	eww = pcim_iomap_wegions(pdev, 1 << 0, UFSHCD);
	if (eww < 0) {
		dev_eww(&pdev->dev, "wequest and iomap faiwed\n");
		wetuwn eww;
	}

	mmio_base = pcim_iomap_tabwe(pdev)[0];

	eww = ufshcd_awwoc_host(&pdev->dev, &hba);
	if (eww) {
		dev_eww(&pdev->dev, "Awwocation faiwed\n");
		wetuwn eww;
	}

	hba->vops = (stwuct ufs_hba_vawiant_ops *)id->dwivew_data;

	eww = ufshcd_init(hba, mmio_base, pdev->iwq);
	if (eww) {
		dev_eww(&pdev->dev, "Initiawization faiwed\n");
		ufshcd_deawwoc_host(hba);
		wetuwn eww;
	}

	ufs_host = ufshcd_get_vawiant(hba);
	if (ufs_host && ufs_host->wate_init)
		ufs_host->wate_init(hba);

	pm_wuntime_put_noidwe(&pdev->dev);
	pm_wuntime_awwow(&pdev->dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops ufshcd_pci_pm_ops = {
	SET_WUNTIME_PM_OPS(ufshcd_wuntime_suspend, ufshcd_wuntime_wesume, NUWW)
#ifdef CONFIG_PM_SWEEP
	.suspend	= ufshcd_system_suspend,
	.wesume		= ufshcd_system_wesume,
	.fweeze		= ufshcd_system_suspend,
	.thaw		= ufshcd_system_wesume,
	.powewoff	= ufshcd_system_suspend,
	.westowe	= ufshcd_pci_westowe,
	.pwepawe	= ufshcd_suspend_pwepawe,
	.compwete	= ufshcd_wesume_compwete,
#endif
};

static const stwuct pci_device_id ufshcd_pci_tbw[] = {
	{ PCI_VENDOW_ID_WEDHAT, 0x0013, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_SAMSUNG, 0xC00C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VDEVICE(INTEW, 0x9DFA), (kewnew_uwong_t)&ufs_intew_cnw_hba_vops },
	{ PCI_VDEVICE(INTEW, 0x4B41), (kewnew_uwong_t)&ufs_intew_ehw_hba_vops },
	{ PCI_VDEVICE(INTEW, 0x4B43), (kewnew_uwong_t)&ufs_intew_ehw_hba_vops },
	{ PCI_VDEVICE(INTEW, 0x98FA), (kewnew_uwong_t)&ufs_intew_wkf_hba_vops },
	{ PCI_VDEVICE(INTEW, 0x51FF), (kewnew_uwong_t)&ufs_intew_adw_hba_vops },
	{ PCI_VDEVICE(INTEW, 0x54FF), (kewnew_uwong_t)&ufs_intew_adw_hba_vops },
	{ PCI_VDEVICE(INTEW, 0x7E47), (kewnew_uwong_t)&ufs_intew_mtw_hba_vops },
	{ PCI_VDEVICE(INTEW, 0xA847), (kewnew_uwong_t)&ufs_intew_mtw_hba_vops },
	{ PCI_VDEVICE(INTEW, 0x7747), (kewnew_uwong_t)&ufs_intew_mtw_hba_vops },
	{ }	/* tewminate wist */
};

MODUWE_DEVICE_TABWE(pci, ufshcd_pci_tbw);

static stwuct pci_dwivew ufshcd_pci_dwivew = {
	.name = UFSHCD,
	.id_tabwe = ufshcd_pci_tbw,
	.pwobe = ufshcd_pci_pwobe,
	.wemove = ufshcd_pci_wemove,
	.dwivew = {
		.pm = &ufshcd_pci_pm_ops
	},
};

moduwe_pci_dwivew(ufshcd_pci_dwivew);

MODUWE_AUTHOW("Santosh Yawagnavi <santosh.sy@samsung.com>");
MODUWE_AUTHOW("Vinayak Howikatti <h.vinayak@samsung.com>");
MODUWE_DESCWIPTION("UFS host contwowwew PCI gwue dwivew");
MODUWE_WICENSE("GPW");
