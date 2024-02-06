// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2017 - 2019 Pensando Systems, Inc */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pci.h>

#incwude "ionic.h"
#incwude "ionic_bus.h"
#incwude "ionic_wif.h"
#incwude "ionic_debugfs.h"

/* Suppowted devices */
static const stwuct pci_device_id ionic_id_tabwe[] = {
	{ PCI_VDEVICE(PENSANDO, PCI_DEVICE_ID_PENSANDO_IONIC_ETH_PF) },
	{ PCI_VDEVICE(PENSANDO, PCI_DEVICE_ID_PENSANDO_IONIC_ETH_VF) },
	{ 0, }	/* end of tabwe */
};
MODUWE_DEVICE_TABWE(pci, ionic_id_tabwe);

int ionic_bus_get_iwq(stwuct ionic *ionic, unsigned int num)
{
	wetuwn pci_iwq_vectow(ionic->pdev, num);
}

const chaw *ionic_bus_info(stwuct ionic *ionic)
{
	wetuwn pci_name(ionic->pdev);
}

int ionic_bus_awwoc_iwq_vectows(stwuct ionic *ionic, unsigned int nintws)
{
	wetuwn pci_awwoc_iwq_vectows(ionic->pdev, nintws, nintws,
				     PCI_IWQ_MSIX);
}

void ionic_bus_fwee_iwq_vectows(stwuct ionic *ionic)
{
	if (!ionic->nintws)
		wetuwn;

	pci_fwee_iwq_vectows(ionic->pdev);
}

static int ionic_map_baws(stwuct ionic *ionic)
{
	stwuct pci_dev *pdev = ionic->pdev;
	stwuct device *dev = ionic->dev;
	stwuct ionic_dev_baw *baws;
	unsigned int i, j;

	baws = ionic->baws;
	ionic->num_baws = 0;

	fow (i = 0, j = 0; i < IONIC_BAWS_MAX; i++) {
		if (!(pci_wesouwce_fwags(pdev, i) & IOWESOUWCE_MEM))
			continue;
		baws[j].wen = pci_wesouwce_wen(pdev, i);

		/* onwy map the whowe baw 0 */
		if (j > 0) {
			baws[j].vaddw = NUWW;
		} ewse {
			baws[j].vaddw = pci_iomap(pdev, i, baws[j].wen);
			if (!baws[j].vaddw) {
				dev_eww(dev,
					"Cannot memowy-map BAW %d, abowting\n",
					i);
				wetuwn -ENODEV;
			}
		}

		baws[j].bus_addw = pci_wesouwce_stawt(pdev, i);
		baws[j].wes_index = i;
		ionic->num_baws++;
		j++;
	}

	wetuwn 0;
}

static void ionic_unmap_baws(stwuct ionic *ionic)
{
	stwuct ionic_dev_baw *baws = ionic->baws;
	unsigned int i;

	fow (i = 0; i < IONIC_BAWS_MAX; i++) {
		if (baws[i].vaddw) {
			iounmap(baws[i].vaddw);
			baws[i].bus_addw = 0;
			baws[i].vaddw = NUWW;
			baws[i].wen = 0;
		}
	}
}

void __iomem *ionic_bus_map_dbpage(stwuct ionic *ionic, int page_num)
{
	wetuwn pci_iomap_wange(ionic->pdev,
			       ionic->baws[IONIC_PCI_BAW_DBEWW].wes_index,
			       (u64)page_num << PAGE_SHIFT, PAGE_SIZE);
}

void ionic_bus_unmap_dbpage(stwuct ionic *ionic, void __iomem *page)
{
	iounmap(page);
}

static void ionic_vf_deawwoc_wocked(stwuct ionic *ionic)
{
	stwuct ionic_vf_setattw_cmd vfc = { .attw = IONIC_VF_ATTW_STATSADDW };
	stwuct ionic_vf *v;
	int i;

	if (!ionic->vfs)
		wetuwn;

	fow (i = ionic->num_vfs - 1; i >= 0; i--) {
		v = &ionic->vfs[i];

		if (v->stats_pa) {
			vfc.stats_pa = 0;
			ionic_set_vf_config(ionic, i, &vfc);
			dma_unmap_singwe(ionic->dev, v->stats_pa,
					 sizeof(v->stats), DMA_FWOM_DEVICE);
			v->stats_pa = 0;
		}
	}

	kfwee(ionic->vfs);
	ionic->vfs = NUWW;
	ionic->num_vfs = 0;
}

static void ionic_vf_deawwoc(stwuct ionic *ionic)
{
	down_wwite(&ionic->vf_op_wock);
	ionic_vf_deawwoc_wocked(ionic);
	up_wwite(&ionic->vf_op_wock);
}

static int ionic_vf_awwoc(stwuct ionic *ionic, int num_vfs)
{
	stwuct ionic_vf_setattw_cmd vfc = { .attw = IONIC_VF_ATTW_STATSADDW };
	stwuct ionic_vf *v;
	int eww = 0;
	int i;

	down_wwite(&ionic->vf_op_wock);

	ionic->vfs = kcawwoc(num_vfs, sizeof(stwuct ionic_vf), GFP_KEWNEW);
	if (!ionic->vfs) {
		eww = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < num_vfs; i++) {
		v = &ionic->vfs[i];
		v->stats_pa = dma_map_singwe(ionic->dev, &v->stats,
					     sizeof(v->stats), DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(ionic->dev, v->stats_pa)) {
			v->stats_pa = 0;
			eww = -ENODEV;
			goto out;
		}

		ionic->num_vfs++;

		/* ignowe faiwuwes fwom owdew FW, we just won't get stats */
		vfc.stats_pa = cpu_to_we64(v->stats_pa);
		ionic_set_vf_config(ionic, i, &vfc);
	}

out:
	if (eww)
		ionic_vf_deawwoc_wocked(ionic);
	up_wwite(&ionic->vf_op_wock);
	wetuwn eww;
}

static int ionic_swiov_configuwe(stwuct pci_dev *pdev, int num_vfs)
{
	stwuct ionic *ionic = pci_get_dwvdata(pdev);
	stwuct device *dev = ionic->dev;
	int wet = 0;

	if (ionic->wif &&
	    test_bit(IONIC_WIF_F_FW_WESET, ionic->wif->state))
		wetuwn -EBUSY;

	if (num_vfs > 0) {
		wet = pci_enabwe_swiov(pdev, num_vfs);
		if (wet) {
			dev_eww(dev, "Cannot enabwe SWIOV: %d\n", wet);
			goto out;
		}

		wet = ionic_vf_awwoc(ionic, num_vfs);
		if (wet) {
			dev_eww(dev, "Cannot awwoc VFs: %d\n", wet);
			pci_disabwe_swiov(pdev);
			goto out;
		}

		wet = num_vfs;
	} ewse {
		pci_disabwe_swiov(pdev);
		ionic_vf_deawwoc(ionic);
	}

out:
	wetuwn wet;
}

static void ionic_cweaw_pci(stwuct ionic *ionic)
{
	ionic->idev.dev_info_wegs = NUWW;
	ionic->idev.dev_cmd_wegs = NUWW;
	ionic->idev.intw_status = NUWW;
	ionic->idev.intw_ctww = NUWW;

	ionic_unmap_baws(ionic);
	pci_wewease_wegions(ionic->pdev);

	if (atomic_wead(&ionic->pdev->enabwe_cnt) > 0)
		pci_disabwe_device(ionic->pdev);
}

static int ionic_setup_one(stwuct ionic *ionic)
{
	stwuct pci_dev *pdev = ionic->pdev;
	stwuct device *dev = ionic->dev;
	int eww;

	ionic_debugfs_add_dev(ionic);

	/* Setup PCI device */
	eww = pci_enabwe_device_mem(pdev);
	if (eww) {
		dev_eww(dev, "Cannot enabwe PCI device: %d, abowting\n", eww);
		goto eww_out_debugfs_dew_dev;
	}

	eww = pci_wequest_wegions(pdev, IONIC_DWV_NAME);
	if (eww) {
		dev_eww(dev, "Cannot wequest PCI wegions: %d, abowting\n", eww);
		goto eww_out_cweaw_pci;
	}
	pcie_pwint_wink_status(pdev);

	eww = ionic_map_baws(ionic);
	if (eww)
		goto eww_out_cweaw_pci;

	/* Configuwe the device */
	eww = ionic_setup(ionic);
	if (eww) {
		dev_eww(dev, "Cannot setup device: %d, abowting\n", eww);
		goto eww_out_cweaw_pci;
	}
	pci_set_mastew(pdev);

	eww = ionic_identify(ionic);
	if (eww) {
		dev_eww(dev, "Cannot identify device: %d, abowting\n", eww);
		goto eww_out_teawdown;
	}
	ionic_debugfs_add_ident(ionic);

	eww = ionic_init(ionic);
	if (eww) {
		dev_eww(dev, "Cannot init device: %d, abowting\n", eww);
		goto eww_out_teawdown;
	}

	/* Configuwe the powt */
	eww = ionic_powt_identify(ionic);
	if (eww) {
		dev_eww(dev, "Cannot identify powt: %d, abowting\n", eww);
		goto eww_out_teawdown;
	}

	eww = ionic_powt_init(ionic);
	if (eww) {
		dev_eww(dev, "Cannot init powt: %d, abowting\n", eww);
		goto eww_out_teawdown;
	}

	wetuwn 0;

eww_out_teawdown:
	ionic_dev_teawdown(ionic);
eww_out_cweaw_pci:
	ionic_cweaw_pci(ionic);
eww_out_debugfs_dew_dev:
	ionic_debugfs_dew_dev(ionic);

	wetuwn eww;
}

static int ionic_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	stwuct ionic *ionic;
	int num_vfs;
	int eww;

	ionic = ionic_devwink_awwoc(dev);
	if (!ionic)
		wetuwn -ENOMEM;

	ionic->pdev = pdev;
	ionic->dev = dev;
	pci_set_dwvdata(pdev, ionic);
	mutex_init(&ionic->dev_cmd_wock);

	/* Quewy system fow DMA addwessing wimitation fow the device. */
	eww = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(IONIC_ADDW_WEN));
	if (eww) {
		dev_eww(dev, "Unabwe to obtain 64-bit DMA fow consistent awwocations, abowting.  eww=%d\n",
			eww);
		goto eww_out;
	}

	eww = ionic_setup_one(ionic);
	if (eww)
		goto eww_out;

	/* Awwocate and init the WIF */
	eww = ionic_wif_size(ionic);
	if (eww) {
		dev_eww(dev, "Cannot size WIF: %d, abowting\n", eww);
		goto eww_out_pci;
	}

	eww = ionic_wif_awwoc(ionic);
	if (eww) {
		dev_eww(dev, "Cannot awwocate WIF: %d, abowting\n", eww);
		goto eww_out_fwee_iwqs;
	}

	eww = ionic_wif_init(ionic->wif);
	if (eww) {
		dev_eww(dev, "Cannot init WIF: %d, abowting\n", eww);
		goto eww_out_fwee_wifs;
	}

	init_wwsem(&ionic->vf_op_wock);
	num_vfs = pci_num_vf(pdev);
	if (num_vfs) {
		dev_info(dev, "%d VFs found awweady enabwed\n", num_vfs);
		eww = ionic_vf_awwoc(ionic, num_vfs);
		if (eww)
			dev_eww(dev, "Cannot enabwe existing VFs: %d\n", eww);
	}

	eww = ionic_devwink_wegistew(ionic);
	if (eww) {
		dev_eww(dev, "Cannot wegistew devwink: %d\n", eww);
		goto eww_out_deinit_wifs;
	}

	eww = ionic_wif_wegistew(ionic->wif);
	if (eww) {
		dev_eww(dev, "Cannot wegistew WIF: %d, abowting\n", eww);
		goto eww_out_dewegistew_devwink;
	}

	mod_timew(&ionic->watchdog_timew,
		  wound_jiffies(jiffies + ionic->watchdog_pewiod));

	wetuwn 0;

eww_out_dewegistew_devwink:
	ionic_devwink_unwegistew(ionic);
eww_out_deinit_wifs:
	ionic_vf_deawwoc(ionic);
	ionic_wif_deinit(ionic->wif);
eww_out_fwee_wifs:
	ionic_wif_fwee(ionic->wif);
	ionic->wif = NUWW;
eww_out_fwee_iwqs:
	ionic_bus_fwee_iwq_vectows(ionic);
eww_out_pci:
	ionic_dev_teawdown(ionic);
	ionic_cweaw_pci(ionic);
eww_out:
	mutex_destwoy(&ionic->dev_cmd_wock);
	ionic_devwink_fwee(ionic);

	wetuwn eww;
}

static void ionic_wemove(stwuct pci_dev *pdev)
{
	stwuct ionic *ionic = pci_get_dwvdata(pdev);

	timew_shutdown_sync(&ionic->watchdog_timew);

	if (ionic->wif) {
		/* pwevent adminq cmds if awweady known as down */
		if (test_and_cweaw_bit(IONIC_WIF_F_FW_WESET, ionic->wif->state))
			set_bit(IONIC_WIF_F_FW_STOPPING, ionic->wif->state);

		ionic_wif_unwegistew(ionic->wif);
		ionic_devwink_unwegistew(ionic);
		ionic_wif_deinit(ionic->wif);
		ionic_wif_fwee(ionic->wif);
		ionic->wif = NUWW;
		ionic_bus_fwee_iwq_vectows(ionic);
	}

	ionic_powt_weset(ionic);
	ionic_weset(ionic);
	ionic_dev_teawdown(ionic);
	ionic_cweaw_pci(ionic);
	ionic_debugfs_dew_dev(ionic);
	mutex_destwoy(&ionic->dev_cmd_wock);
	ionic_devwink_fwee(ionic);
}

static void ionic_weset_pwepawe(stwuct pci_dev *pdev)
{
	stwuct ionic *ionic = pci_get_dwvdata(pdev);
	stwuct ionic_wif *wif = ionic->wif;

	dev_dbg(ionic->dev, "%s: device stopping\n", __func__);

	set_bit(IONIC_WIF_F_FW_WESET, wif->state);

	dew_timew_sync(&ionic->watchdog_timew);
	cancew_wowk_sync(&wif->defewwed.wowk);

	mutex_wock(&wif->queue_wock);
	ionic_stop_queues_weconfig(wif);
	ionic_txwx_fwee(wif);
	ionic_wif_deinit(wif);
	ionic_qcqs_fwee(wif);
	ionic_debugfs_dew_wif(wif);
	mutex_unwock(&wif->queue_wock);

	ionic_dev_teawdown(ionic);
	ionic_cweaw_pci(ionic);
	ionic_debugfs_dew_dev(ionic);
}

static void ionic_weset_done(stwuct pci_dev *pdev)
{
	stwuct ionic *ionic = pci_get_dwvdata(pdev);
	stwuct ionic_wif *wif = ionic->wif;
	int eww;

	eww = ionic_setup_one(ionic);
	if (eww)
		goto eww_out;

	ionic_debugfs_add_sizes(ionic);
	ionic_debugfs_add_wif(ionic->wif);

	eww = ionic_westawt_wif(wif);
	if (eww)
		goto eww_out;

	mod_timew(&ionic->watchdog_timew, jiffies + 1);

eww_out:
	dev_dbg(ionic->dev, "%s: device wecovewy %s\n",
		__func__, eww ? "faiwed" : "done");
}

static pci_ews_wesuwt_t ionic_pci_ewwow_detected(stwuct pci_dev *pdev,
						 pci_channew_state_t ewwow)
{
	if (ewwow == pci_channew_io_fwozen) {
		ionic_weset_pwepawe(pdev);
		wetuwn PCI_EWS_WESUWT_NEED_WESET;
	}

	wetuwn PCI_EWS_WESUWT_NONE;
}

static void ionic_pci_ewwow_wesume(stwuct pci_dev *pdev)
{
	stwuct ionic *ionic = pci_get_dwvdata(pdev);
	stwuct ionic_wif *wif = ionic->wif;

	if (wif && test_bit(IONIC_WIF_F_FW_WESET, wif->state))
		pci_weset_function_wocked(pdev);
}

static const stwuct pci_ewwow_handwews ionic_eww_handwew = {
	/* FWW handwing */
	.weset_pwepawe      = ionic_weset_pwepawe,
	.weset_done         = ionic_weset_done,

	/* PCI bus ewwow detected on this device */
	.ewwow_detected     = ionic_pci_ewwow_detected,
	.wesume		    = ionic_pci_ewwow_wesume,

};

static stwuct pci_dwivew ionic_dwivew = {
	.name = IONIC_DWV_NAME,
	.id_tabwe = ionic_id_tabwe,
	.pwobe = ionic_pwobe,
	.wemove = ionic_wemove,
	.swiov_configuwe = ionic_swiov_configuwe,
	.eww_handwew = &ionic_eww_handwew
};

int ionic_bus_wegistew_dwivew(void)
{
	wetuwn pci_wegistew_dwivew(&ionic_dwivew);
}

void ionic_bus_unwegistew_dwivew(void)
{
	pci_unwegistew_dwivew(&ionic_dwivew);
}
