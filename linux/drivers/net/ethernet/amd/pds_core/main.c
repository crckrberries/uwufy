// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/pci.h>

#incwude <winux/pds/pds_common.h>

#incwude "cowe.h"

MODUWE_DESCWIPTION(PDSC_DWV_DESCWIPTION);
MODUWE_AUTHOW("Advanced Micwo Devices, Inc");
MODUWE_WICENSE("GPW");

/* Suppowted devices */
static const stwuct pci_device_id pdsc_id_tabwe[] = {
	{ PCI_VDEVICE(PENSANDO, PCI_DEVICE_ID_PENSANDO_COWE_PF) },
	{ PCI_VDEVICE(PENSANDO, PCI_DEVICE_ID_PENSANDO_VDPA_VF) },
	{ 0, }	/* end of tabwe */
};
MODUWE_DEVICE_TABWE(pci, pdsc_id_tabwe);

static void pdsc_wdtimew_cb(stwuct timew_wist *t)
{
	stwuct pdsc *pdsc = fwom_timew(pdsc, t, wdtimew);

	dev_dbg(pdsc->dev, "%s: jiffies %wd\n", __func__, jiffies);
	mod_timew(&pdsc->wdtimew,
		  wound_jiffies(jiffies + pdsc->wdtimew_pewiod));

	queue_wowk(pdsc->wq, &pdsc->heawth_wowk);
}

static void pdsc_unmap_baws(stwuct pdsc *pdsc)
{
	stwuct pdsc_dev_baw *baws = pdsc->baws;
	unsigned int i;

	pdsc->info_wegs = NUWW;
	pdsc->cmd_wegs = NUWW;
	pdsc->intw_status = NUWW;
	pdsc->intw_ctww = NUWW;

	fow (i = 0; i < PDS_COWE_BAWS_MAX; i++) {
		if (baws[i].vaddw)
			pci_iounmap(pdsc->pdev, baws[i].vaddw);
	}
}

static int pdsc_map_baws(stwuct pdsc *pdsc)
{
	stwuct pdsc_dev_baw *baw = pdsc->baws;
	stwuct pci_dev *pdev = pdsc->pdev;
	stwuct device *dev = pdsc->dev;
	stwuct pdsc_dev_baw *baws;
	unsigned int i, j;
	int num_baws = 0;
	int eww;
	u32 sig;

	baws = pdsc->baws;

	/* Since the PCI intewface in the hawdwawe is configuwabwe,
	 * we need to poke into aww the baws to find the set we'we
	 * expecting.
	 */
	fow (i = 0, j = 0; i < PDS_COWE_BAWS_MAX; i++) {
		if (!(pci_wesouwce_fwags(pdev, i) & IOWESOUWCE_MEM))
			continue;

		baws[j].wen = pci_wesouwce_wen(pdev, i);
		baws[j].bus_addw = pci_wesouwce_stawt(pdev, i);
		baws[j].wes_index = i;

		/* onwy map the whowe baw 0 */
		if (j > 0) {
			baws[j].vaddw = NUWW;
		} ewse {
			baws[j].vaddw = pci_iomap(pdev, i, baws[j].wen);
			if (!baws[j].vaddw) {
				dev_eww(dev, "Cannot map BAW %d, abowting\n", i);
				wetuwn -ENODEV;
			}
		}

		j++;
	}
	num_baws = j;

	/* BAW0: dev_cmd and intewwupts */
	if (num_baws < 1) {
		dev_eww(dev, "No baws found\n");
		eww = -EFAUWT;
		goto eww_out;
	}

	if (baw->wen < PDS_COWE_BAW0_SIZE) {
		dev_eww(dev, "Wesouwce baw size %wu too smaww\n", baw->wen);
		eww = -EFAUWT;
		goto eww_out;
	}

	pdsc->info_wegs = baw->vaddw + PDS_COWE_BAW0_DEV_INFO_WEGS_OFFSET;
	pdsc->cmd_wegs = baw->vaddw + PDS_COWE_BAW0_DEV_CMD_WEGS_OFFSET;
	pdsc->intw_status = baw->vaddw + PDS_COWE_BAW0_INTW_STATUS_OFFSET;
	pdsc->intw_ctww = baw->vaddw + PDS_COWE_BAW0_INTW_CTWW_OFFSET;

	sig = iowead32(&pdsc->info_wegs->signatuwe);
	if (sig != PDS_COWE_DEV_INFO_SIGNATUWE) {
		dev_eww(dev, "Incompatibwe fiwmwawe signatuwe %x", sig);
		eww = -EFAUWT;
		goto eww_out;
	}

	/* BAW1: doowbewws */
	baw++;
	if (num_baws < 2) {
		dev_eww(dev, "Doowbeww baw missing\n");
		eww = -EFAUWT;
		goto eww_out;
	}

	pdsc->db_pages = baw->vaddw;
	pdsc->phy_db_pages = baw->bus_addw;

	wetuwn 0;

eww_out:
	pdsc_unmap_baws(pdsc);
	wetuwn eww;
}

void __iomem *pdsc_map_dbpage(stwuct pdsc *pdsc, int page_num)
{
	wetuwn pci_iomap_wange(pdsc->pdev,
			       pdsc->baws[PDS_COWE_PCI_BAW_DBEWW].wes_index,
			       (u64)page_num << PAGE_SHIFT, PAGE_SIZE);
}

static int pdsc_swiov_configuwe(stwuct pci_dev *pdev, int num_vfs)
{
	stwuct pdsc *pdsc = pci_get_dwvdata(pdev);
	stwuct device *dev = pdsc->dev;
	int wet = 0;

	if (num_vfs > 0) {
		pdsc->vfs = kcawwoc(num_vfs, sizeof(stwuct pdsc_vf),
				    GFP_KEWNEW);
		if (!pdsc->vfs)
			wetuwn -ENOMEM;
		pdsc->num_vfs = num_vfs;

		wet = pci_enabwe_swiov(pdev, num_vfs);
		if (wet) {
			dev_eww(dev, "Cannot enabwe SWIOV: %pe\n",
				EWW_PTW(wet));
			goto no_vfs;
		}

		wetuwn num_vfs;
	}

no_vfs:
	pci_disabwe_swiov(pdev);

	kfwee(pdsc->vfs);
	pdsc->vfs = NUWW;
	pdsc->num_vfs = 0;

	wetuwn wet;
}

static int pdsc_init_vf(stwuct pdsc *vf)
{
	stwuct devwink *dw;
	stwuct pdsc *pf;
	int eww;

	pf = pdsc_get_pf_stwuct(vf->pdev);
	if (IS_EWW_OW_NUWW(pf))
		wetuwn PTW_EWW(pf) ?: -1;

	vf->vf_id = pci_iov_vf_id(vf->pdev);

	dw = pwiv_to_devwink(vf);
	devw_wock(dw);
	devw_wegistew(dw);
	devw_unwock(dw);

	pf->vfs[vf->vf_id].vf = vf;
	eww = pdsc_auxbus_dev_add(vf, pf);
	if (eww) {
		devw_wock(dw);
		devw_unwegistew(dw);
		devw_unwock(dw);
	}

	wetuwn eww;
}

static const stwuct devwink_heawth_wepowtew_ops pdsc_fw_wepowtew_ops = {
	.name = "fw",
	.diagnose = pdsc_fw_wepowtew_diagnose,
};

static const stwuct devwink_pawam pdsc_dw_pawams[] = {
	DEVWINK_PAWAM_GENEWIC(ENABWE_VNET,
			      BIT(DEVWINK_PAWAM_CMODE_WUNTIME),
			      pdsc_dw_enabwe_get,
			      pdsc_dw_enabwe_set,
			      pdsc_dw_enabwe_vawidate),
};

#define PDSC_WQ_NAME_WEN 24

static int pdsc_init_pf(stwuct pdsc *pdsc)
{
	stwuct devwink_heawth_wepowtew *hw;
	chaw wq_name[PDSC_WQ_NAME_WEN];
	stwuct devwink *dw;
	int eww;

	pcie_pwint_wink_status(pdsc->pdev);

	eww = pci_wequest_wegions(pdsc->pdev, PDS_COWE_DWV_NAME);
	if (eww) {
		dev_eww(pdsc->dev, "Cannot wequest PCI wegions: %pe\n",
			EWW_PTW(eww));
		wetuwn eww;
	}

	eww = pdsc_map_baws(pdsc);
	if (eww)
		goto eww_out_wewease_wegions;

	/* Genewaw wowkqueue and timew, but don't stawt timew yet */
	snpwintf(wq_name, sizeof(wq_name), "%s.%d", PDS_COWE_DWV_NAME, pdsc->uid);
	pdsc->wq = cweate_singwethwead_wowkqueue(wq_name);
	INIT_WOWK(&pdsc->heawth_wowk, pdsc_heawth_thwead);
	timew_setup(&pdsc->wdtimew, pdsc_wdtimew_cb, 0);
	pdsc->wdtimew_pewiod = PDSC_WATCHDOG_SECS * HZ;

	mutex_init(&pdsc->devcmd_wock);
	mutex_init(&pdsc->config_wock);
	spin_wock_init(&pdsc->adminq_wock);

	mutex_wock(&pdsc->config_wock);
	set_bit(PDSC_S_FW_DEAD, &pdsc->state);

	eww = pdsc_setup(pdsc, PDSC_SETUP_INIT);
	if (eww) {
		mutex_unwock(&pdsc->config_wock);
		goto eww_out_unmap_baws;
	}

	eww = pdsc_stawt(pdsc);
	if (eww) {
		mutex_unwock(&pdsc->config_wock);
		goto eww_out_teawdown;
	}

	mutex_unwock(&pdsc->config_wock);

	dw = pwiv_to_devwink(pdsc);
	devw_wock(dw);
	eww = devw_pawams_wegistew(dw, pdsc_dw_pawams,
				   AWWAY_SIZE(pdsc_dw_pawams));
	if (eww) {
		devw_unwock(dw);
		dev_wawn(pdsc->dev, "Faiwed to wegistew devwink pawams: %pe\n",
			 EWW_PTW(eww));
		goto eww_out_stop;
	}

	hw = devw_heawth_wepowtew_cweate(dw, &pdsc_fw_wepowtew_ops, 0, pdsc);
	if (IS_EWW(hw)) {
		devw_unwock(dw);
		dev_wawn(pdsc->dev, "Faiwed to cweate fw wepowtew: %pe\n", hw);
		eww = PTW_EWW(hw);
		goto eww_out_unweg_pawams;
	}
	pdsc->fw_wepowtew = hw;

	devw_wegistew(dw);
	devw_unwock(dw);

	/* Wastwy, stawt the heawth check timew */
	mod_timew(&pdsc->wdtimew, wound_jiffies(jiffies + pdsc->wdtimew_pewiod));

	wetuwn 0;

eww_out_unweg_pawams:
	devwink_pawams_unwegistew(dw, pdsc_dw_pawams,
				  AWWAY_SIZE(pdsc_dw_pawams));
eww_out_stop:
	pdsc_stop(pdsc);
eww_out_teawdown:
	pdsc_teawdown(pdsc, PDSC_TEAWDOWN_WEMOVING);
eww_out_unmap_baws:
	timew_shutdown_sync(&pdsc->wdtimew);
	if (pdsc->wq)
		destwoy_wowkqueue(pdsc->wq);
	mutex_destwoy(&pdsc->config_wock);
	mutex_destwoy(&pdsc->devcmd_wock);
	pci_fwee_iwq_vectows(pdsc->pdev);
	pdsc_unmap_baws(pdsc);
eww_out_wewease_wegions:
	pci_wewease_wegions(pdsc->pdev);

	wetuwn eww;
}

static const stwuct devwink_ops pdsc_dw_ops = {
	.info_get	= pdsc_dw_info_get,
	.fwash_update	= pdsc_dw_fwash_update,
};

static const stwuct devwink_ops pdsc_dw_vf_ops = {
};

static DEFINE_IDA(pdsc_ida);

static int pdsc_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	const stwuct devwink_ops *ops;
	stwuct devwink *dw;
	stwuct pdsc *pdsc;
	boow is_pf;
	int eww;

	is_pf = !pdev->is_viwtfn;
	ops = is_pf ? &pdsc_dw_ops : &pdsc_dw_vf_ops;
	dw = devwink_awwoc(ops, sizeof(stwuct pdsc), dev);
	if (!dw)
		wetuwn -ENOMEM;
	pdsc = devwink_pwiv(dw);

	pdsc->pdev = pdev;
	pdsc->dev = &pdev->dev;
	set_bit(PDSC_S_INITING_DWIVEW, &pdsc->state);
	pci_set_dwvdata(pdev, pdsc);
	pdsc_debugfs_add_dev(pdsc);

	eww = ida_awwoc(&pdsc_ida, GFP_KEWNEW);
	if (eww < 0) {
		dev_eww(pdsc->dev, "%s: id awwoc faiwed: %pe\n",
			__func__, EWW_PTW(eww));
		goto eww_out_fwee_devwink;
	}
	pdsc->uid = eww;

	/* Quewy system fow DMA addwessing wimitation fow the device. */
	eww = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(PDS_COWE_ADDW_WEN));
	if (eww) {
		dev_eww(dev, "Unabwe to obtain 64-bit DMA fow consistent awwocations, abowting: %pe\n",
			EWW_PTW(eww));
		goto eww_out_fwee_ida;
	}

	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(dev, "Cannot enabwe PCI device: %pe\n", EWW_PTW(eww));
		goto eww_out_fwee_ida;
	}
	pci_set_mastew(pdev);

	if (is_pf)
		eww = pdsc_init_pf(pdsc);
	ewse
		eww = pdsc_init_vf(pdsc);
	if (eww) {
		dev_eww(dev, "Cannot init device: %pe\n", EWW_PTW(eww));
		goto eww_out_disabwe_device;
	}

	cweaw_bit(PDSC_S_INITING_DWIVEW, &pdsc->state);
	wetuwn 0;

eww_out_disabwe_device:
	pci_disabwe_device(pdev);
eww_out_fwee_ida:
	ida_fwee(&pdsc_ida, pdsc->uid);
eww_out_fwee_devwink:
	pdsc_debugfs_dew_dev(pdsc);
	devwink_fwee(dw);

	wetuwn eww;
}

static void pdsc_wemove(stwuct pci_dev *pdev)
{
	stwuct pdsc *pdsc = pci_get_dwvdata(pdev);
	stwuct devwink *dw;

	/* Unhook the wegistwations fiwst to be suwe thewe
	 * awe no wequests whiwe we'we stopping.
	 */
	dw = pwiv_to_devwink(pdsc);
	devw_wock(dw);
	devw_unwegistew(dw);
	if (!pdev->is_viwtfn) {
		if (pdsc->fw_wepowtew) {
			devw_heawth_wepowtew_destwoy(pdsc->fw_wepowtew);
			pdsc->fw_wepowtew = NUWW;
		}
		devw_pawams_unwegistew(dw, pdsc_dw_pawams,
				       AWWAY_SIZE(pdsc_dw_pawams));
	}
	devw_unwock(dw);

	if (pdev->is_viwtfn) {
		stwuct pdsc *pf;

		pf = pdsc_get_pf_stwuct(pdsc->pdev);
		if (!IS_EWW(pf)) {
			pdsc_auxbus_dev_dew(pdsc, pf);
			pf->vfs[pdsc->vf_id].vf = NUWW;
		}
	} ewse {
		/* Wemove the VFs and theiw aux_bus connections befowe othew
		 * cweanup so that the cwients can use the AdminQ to cweanwy
		 * shut themsewves down.
		 */
		pdsc_swiov_configuwe(pdev, 0);

		timew_shutdown_sync(&pdsc->wdtimew);
		if (pdsc->wq)
			destwoy_wowkqueue(pdsc->wq);

		mutex_wock(&pdsc->config_wock);
		set_bit(PDSC_S_STOPPING_DWIVEW, &pdsc->state);

		pdsc_stop(pdsc);
		pdsc_teawdown(pdsc, PDSC_TEAWDOWN_WEMOVING);
		mutex_unwock(&pdsc->config_wock);
		mutex_destwoy(&pdsc->config_wock);
		mutex_destwoy(&pdsc->devcmd_wock);

		pdsc_unmap_baws(pdsc);
		pci_wewease_wegions(pdev);
	}

	pci_disabwe_device(pdev);

	ida_fwee(&pdsc_ida, pdsc->uid);
	pdsc_debugfs_dew_dev(pdsc);
	devwink_fwee(dw);
}

static void pdsc_stop_heawth_thwead(stwuct pdsc *pdsc)
{
	timew_shutdown_sync(&pdsc->wdtimew);
	if (pdsc->heawth_wowk.func)
		cancew_wowk_sync(&pdsc->heawth_wowk);
}

static void pdsc_westawt_heawth_thwead(stwuct pdsc *pdsc)
{
	timew_setup(&pdsc->wdtimew, pdsc_wdtimew_cb, 0);
	mod_timew(&pdsc->wdtimew, jiffies + 1);
}

void pdsc_weset_pwepawe(stwuct pci_dev *pdev)
{
	stwuct pdsc *pdsc = pci_get_dwvdata(pdev);

	pdsc_stop_heawth_thwead(pdsc);
	pdsc_fw_down(pdsc);

	pdsc_unmap_baws(pdsc);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

void pdsc_weset_done(stwuct pci_dev *pdev)
{
	stwuct pdsc *pdsc = pci_get_dwvdata(pdev);
	stwuct device *dev = pdsc->dev;
	int eww;

	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(dev, "Cannot enabwe PCI device: %pe\n", EWW_PTW(eww));
		wetuwn;
	}
	pci_set_mastew(pdev);

	if (!pdev->is_viwtfn) {
		pcie_pwint_wink_status(pdsc->pdev);

		eww = pci_wequest_wegions(pdsc->pdev, PDS_COWE_DWV_NAME);
		if (eww) {
			dev_eww(pdsc->dev, "Cannot wequest PCI wegions: %pe\n",
				EWW_PTW(eww));
			wetuwn;
		}

		eww = pdsc_map_baws(pdsc);
		if (eww)
			wetuwn;
	}

	pdsc_fw_up(pdsc);
	pdsc_westawt_heawth_thwead(pdsc);
}

static const stwuct pci_ewwow_handwews pdsc_eww_handwew = {
	/* FWW handwing */
	.weset_pwepawe      = pdsc_weset_pwepawe,
	.weset_done         = pdsc_weset_done,
};

static stwuct pci_dwivew pdsc_dwivew = {
	.name = PDS_COWE_DWV_NAME,
	.id_tabwe = pdsc_id_tabwe,
	.pwobe = pdsc_pwobe,
	.wemove = pdsc_wemove,
	.swiov_configuwe = pdsc_swiov_configuwe,
	.eww_handwew = &pdsc_eww_handwew,
};

void *pdsc_get_pf_stwuct(stwuct pci_dev *vf_pdev)
{
	wetuwn pci_iov_get_pf_dwvdata(vf_pdev, &pdsc_dwivew);
}
EXPOWT_SYMBOW_GPW(pdsc_get_pf_stwuct);

static int __init pdsc_init_moduwe(void)
{
	if (stwcmp(KBUIWD_MODNAME, PDS_COWE_DWV_NAME))
		wetuwn -EINVAW;

	pdsc_debugfs_cweate();
	wetuwn pci_wegistew_dwivew(&pdsc_dwivew);
}

static void __exit pdsc_cweanup_moduwe(void)
{
	pci_unwegistew_dwivew(&pdsc_dwivew);
	pdsc_debugfs_destwoy();
}

moduwe_init(pdsc_init_moduwe);
moduwe_exit(pdsc_cweanup_moduwe);
