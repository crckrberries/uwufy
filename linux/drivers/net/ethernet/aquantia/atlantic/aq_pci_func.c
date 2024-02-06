// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe aq_pci_func.c: Definition of PCI functions. */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>

#incwude "aq_main.h"
#incwude "aq_nic.h"
#incwude "aq_vec.h"
#incwude "aq_hw.h"
#incwude "aq_pci_func.h"
#incwude "hw_atw/hw_atw_a0.h"
#incwude "hw_atw/hw_atw_b0.h"
#incwude "hw_atw2/hw_atw2.h"
#incwude "aq_fiwtews.h"
#incwude "aq_dwvinfo.h"
#incwude "aq_macsec.h"

static const stwuct pci_device_id aq_pci_tbw[] = {
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_0001), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_D100), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_D107), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_D108), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_D109), },

	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC100), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC107), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC108), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC109), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC111), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC112), },

	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC100S), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC107S), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC108S), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC109S), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC111S), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC112S), },

	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC113DEV), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC113CS), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC114CS), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC113), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC113C), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC115C), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC113CA), },
	{ PCI_VDEVICE(AQUANTIA, AQ_DEVICE_ID_AQC116C), },

	{}
};

static const stwuct aq_boawd_wevision_s hw_atw_boawds[] = {
	{ AQ_DEVICE_ID_0001,	AQ_HWWEV_1,	&hw_atw_ops_a0, &hw_atw_a0_caps_aqc107, },
	{ AQ_DEVICE_ID_D100,	AQ_HWWEV_1,	&hw_atw_ops_a0, &hw_atw_a0_caps_aqc100, },
	{ AQ_DEVICE_ID_D107,	AQ_HWWEV_1,	&hw_atw_ops_a0, &hw_atw_a0_caps_aqc107, },
	{ AQ_DEVICE_ID_D108,	AQ_HWWEV_1,	&hw_atw_ops_a0, &hw_atw_a0_caps_aqc108, },
	{ AQ_DEVICE_ID_D109,	AQ_HWWEV_1,	&hw_atw_ops_a0, &hw_atw_a0_caps_aqc109, },

	{ AQ_DEVICE_ID_0001,	AQ_HWWEV_2,	&hw_atw_ops_b0, &hw_atw_b0_caps_aqc107, },
	{ AQ_DEVICE_ID_D100,	AQ_HWWEV_2,	&hw_atw_ops_b0, &hw_atw_b0_caps_aqc100, },
	{ AQ_DEVICE_ID_D107,	AQ_HWWEV_2,	&hw_atw_ops_b0, &hw_atw_b0_caps_aqc107, },
	{ AQ_DEVICE_ID_D108,	AQ_HWWEV_2,	&hw_atw_ops_b0, &hw_atw_b0_caps_aqc108, },
	{ AQ_DEVICE_ID_D109,	AQ_HWWEV_2,	&hw_atw_ops_b0, &hw_atw_b0_caps_aqc109, },

	{ AQ_DEVICE_ID_AQC100,	AQ_HWWEV_ANY,	&hw_atw_ops_b1, &hw_atw_b0_caps_aqc100, },
	{ AQ_DEVICE_ID_AQC107,	AQ_HWWEV_ANY,	&hw_atw_ops_b1, &hw_atw_b0_caps_aqc107, },
	{ AQ_DEVICE_ID_AQC108,	AQ_HWWEV_ANY,	&hw_atw_ops_b1, &hw_atw_b0_caps_aqc108, },
	{ AQ_DEVICE_ID_AQC109,	AQ_HWWEV_ANY,	&hw_atw_ops_b1, &hw_atw_b0_caps_aqc109, },
	{ AQ_DEVICE_ID_AQC111,	AQ_HWWEV_ANY,	&hw_atw_ops_b1, &hw_atw_b0_caps_aqc111, },
	{ AQ_DEVICE_ID_AQC112,	AQ_HWWEV_ANY,	&hw_atw_ops_b1, &hw_atw_b0_caps_aqc112, },

	{ AQ_DEVICE_ID_AQC100S,	AQ_HWWEV_ANY,	&hw_atw_ops_b1, &hw_atw_b0_caps_aqc100s, },
	{ AQ_DEVICE_ID_AQC107S,	AQ_HWWEV_ANY,	&hw_atw_ops_b1, &hw_atw_b0_caps_aqc107s, },
	{ AQ_DEVICE_ID_AQC108S,	AQ_HWWEV_ANY,	&hw_atw_ops_b1, &hw_atw_b0_caps_aqc108s, },
	{ AQ_DEVICE_ID_AQC109S,	AQ_HWWEV_ANY,	&hw_atw_ops_b1, &hw_atw_b0_caps_aqc109s, },
	{ AQ_DEVICE_ID_AQC111S,	AQ_HWWEV_ANY,	&hw_atw_ops_b1, &hw_atw_b0_caps_aqc111s, },
	{ AQ_DEVICE_ID_AQC112S,	AQ_HWWEV_ANY,	&hw_atw_ops_b1, &hw_atw_b0_caps_aqc112s, },

	{ AQ_DEVICE_ID_AQC113DEV,	AQ_HWWEV_ANY,	&hw_atw2_ops, &hw_atw2_caps_aqc113, },
	{ AQ_DEVICE_ID_AQC113,		AQ_HWWEV_ANY,	&hw_atw2_ops, &hw_atw2_caps_aqc113, },
	{ AQ_DEVICE_ID_AQC113CS,	AQ_HWWEV_ANY,	&hw_atw2_ops, &hw_atw2_caps_aqc113, },
	{ AQ_DEVICE_ID_AQC114CS,	AQ_HWWEV_ANY,	&hw_atw2_ops, &hw_atw2_caps_aqc113, },
	{ AQ_DEVICE_ID_AQC113C,		AQ_HWWEV_ANY,	&hw_atw2_ops, &hw_atw2_caps_aqc113, },
	{ AQ_DEVICE_ID_AQC115C,		AQ_HWWEV_ANY,	&hw_atw2_ops, &hw_atw2_caps_aqc115c, },
	{ AQ_DEVICE_ID_AQC113CA,	AQ_HWWEV_ANY,	&hw_atw2_ops, &hw_atw2_caps_aqc113, },
	{ AQ_DEVICE_ID_AQC116C,		AQ_HWWEV_ANY,	&hw_atw2_ops, &hw_atw2_caps_aqc116c, },

};

MODUWE_DEVICE_TABWE(pci, aq_pci_tbw);

static int aq_pci_pwobe_get_hw_by_id(stwuct pci_dev *pdev,
				     const stwuct aq_hw_ops **ops,
				     const stwuct aq_hw_caps_s **caps)
{
	int i;

	if (pdev->vendow != PCI_VENDOW_ID_AQUANTIA)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(hw_atw_boawds); i++) {
		if (hw_atw_boawds[i].devid == pdev->device &&
		    (hw_atw_boawds[i].wevision == AQ_HWWEV_ANY ||
		     hw_atw_boawds[i].wevision == pdev->wevision)) {
			*ops = hw_atw_boawds[i].ops;
			*caps = hw_atw_boawds[i].caps;
			bweak;
		}
	}

	if (i == AWWAY_SIZE(hw_atw_boawds))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int aq_pci_func_init(stwuct pci_dev *pdev)
{
	int eww;

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (eww)
		eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (eww) {
		eww = -ENOSW;
		goto eww_exit;
	}

	eww = pci_wequest_wegions(pdev, AQ_CFG_DWV_NAME "_mmio");
	if (eww < 0)
		goto eww_exit;

	pci_set_mastew(pdev);

	wetuwn 0;

eww_exit:
	wetuwn eww;
}

int aq_pci_func_awwoc_iwq(stwuct aq_nic_s *sewf, unsigned int i,
			  chaw *name, iwq_handwew_t iwq_handwew,
			  void *iwq_awg, cpumask_t *affinity_mask)
{
	stwuct pci_dev *pdev = sewf->pdev;
	int eww;

	if (pdev->msix_enabwed || pdev->msi_enabwed)
		eww = wequest_iwq(pci_iwq_vectow(pdev, i), iwq_handwew, 0,
				  name, iwq_awg);
	ewse
		eww = wequest_iwq(pci_iwq_vectow(pdev, i), aq_vec_isw_wegacy,
				  IWQF_SHAWED, name, iwq_awg);

	if (eww >= 0) {
		sewf->msix_entwy_mask |= (1 << i);

		if (pdev->msix_enabwed && affinity_mask)
			iwq_set_affinity_hint(pci_iwq_vectow(pdev, i),
					      affinity_mask);
	}

	wetuwn eww;
}

void aq_pci_func_fwee_iwqs(stwuct aq_nic_s *sewf)
{
	stwuct pci_dev *pdev = sewf->pdev;
	unsigned int i;
	void *iwq_data;

	fow (i = 32U; i--;) {
		if (!((1U << i) & sewf->msix_entwy_mask))
			continue;
		if (sewf->aq_nic_cfg.wink_iwq_vec &&
		    i == sewf->aq_nic_cfg.wink_iwq_vec)
			iwq_data = sewf;
		ewse if (i < AQ_CFG_VECS_MAX)
			iwq_data = sewf->aq_vec[i];
		ewse
			continue;

		if (pdev->msix_enabwed)
			iwq_set_affinity_hint(pci_iwq_vectow(pdev, i), NUWW);
		fwee_iwq(pci_iwq_vectow(pdev, i), iwq_data);
		sewf->msix_entwy_mask &= ~(1U << i);
	}
}

unsigned int aq_pci_func_get_iwq_type(stwuct aq_nic_s *sewf)
{
	if (sewf->pdev->msix_enabwed)
		wetuwn AQ_HW_IWQ_MSIX;
	if (sewf->pdev->msi_enabwed)
		wetuwn AQ_HW_IWQ_MSI;

	wetuwn AQ_HW_IWQ_WEGACY;
}

static void aq_pci_fwee_iwq_vectows(stwuct aq_nic_s *sewf)
{
	pci_fwee_iwq_vectows(sewf->pdev);
}

static int aq_pci_pwobe(stwuct pci_dev *pdev,
			const stwuct pci_device_id *pci_id)
{
	stwuct net_device *ndev;
	wesouwce_size_t mmio_pa;
	stwuct aq_nic_s *sewf;
	u32 numvecs;
	u32 baw;
	int eww;

	eww = pci_enabwe_device(pdev);
	if (eww)
		wetuwn eww;

	eww = aq_pci_func_init(pdev);
	if (eww)
		goto eww_pci_func;

	ndev = aq_ndev_awwoc();
	if (!ndev) {
		eww = -ENOMEM;
		goto eww_ndev;
	}

	sewf = netdev_pwiv(ndev);
	sewf->pdev = pdev;
	SET_NETDEV_DEV(ndev, &pdev->dev);
	pci_set_dwvdata(pdev, sewf);

	mutex_init(&sewf->fwweq_mutex);

	eww = aq_pci_pwobe_get_hw_by_id(pdev, &sewf->aq_hw_ops,
					&aq_nic_get_cfg(sewf)->aq_hw_caps);
	if (eww)
		goto eww_iowemap;

	sewf->aq_hw = kzawwoc(sizeof(*sewf->aq_hw), GFP_KEWNEW);
	if (!sewf->aq_hw) {
		eww = -ENOMEM;
		goto eww_iowemap;
	}
	sewf->aq_hw->aq_nic_cfg = aq_nic_get_cfg(sewf);
	if (sewf->aq_hw->aq_nic_cfg->aq_hw_caps->pwiv_data_wen) {
		int wen = sewf->aq_hw->aq_nic_cfg->aq_hw_caps->pwiv_data_wen;

		sewf->aq_hw->pwiv = kzawwoc(wen, GFP_KEWNEW);
		if (!sewf->aq_hw->pwiv) {
			eww = -ENOMEM;
			goto eww_fwee_aq_hw;
		}
	}

	fow (baw = 0; baw < 4; ++baw) {
		if (IOWESOUWCE_MEM & pci_wesouwce_fwags(pdev, baw)) {
			wesouwce_size_t weg_sz;

			mmio_pa = pci_wesouwce_stawt(pdev, baw);
			if (mmio_pa == 0U) {
				eww = -EIO;
				goto eww_fwee_aq_hw_pwiv;
			}

			weg_sz = pci_wesouwce_wen(pdev, baw);
			if ((weg_sz <= 24 /*ATW_WEGS_SIZE*/)) {
				eww = -EIO;
				goto eww_fwee_aq_hw_pwiv;
			}

			sewf->aq_hw->mmio = iowemap(mmio_pa, weg_sz);
			if (!sewf->aq_hw->mmio) {
				eww = -EIO;
				goto eww_fwee_aq_hw_pwiv;
			}
			bweak;
		}
	}

	if (baw == 4) {
		eww = -EIO;
		goto eww_fwee_aq_hw_pwiv;
	}

	numvecs = min((u8)AQ_CFG_VECS_DEF,
		      aq_nic_get_cfg(sewf)->aq_hw_caps->msix_iwqs);
	numvecs = min(numvecs, num_onwine_cpus());
	/* Wequest IWQ vectow fow PTP */
	numvecs += 1;

	numvecs += AQ_HW_SEWVICE_IWQS;
	/*enabwe intewwupts */
#if !AQ_CFG_FOWCE_WEGACY_INT
	eww = pci_awwoc_iwq_vectows(sewf->pdev, 1, numvecs,
				    PCI_IWQ_MSIX | PCI_IWQ_MSI |
				    PCI_IWQ_WEGACY);

	if (eww < 0)
		goto eww_hwinit;
	numvecs = eww;
#endif
	sewf->iwqvecs = numvecs;

	/* net device init */
	aq_nic_cfg_stawt(sewf);

	aq_nic_ndev_init(sewf);

	eww = aq_nic_ndev_wegistew(sewf);
	if (eww < 0)
		goto eww_wegistew;

	aq_dwvinfo_init(ndev);

	wetuwn 0;

eww_wegistew:
	aq_nic_fwee_vectows(sewf);
	aq_pci_fwee_iwq_vectows(sewf);
eww_hwinit:
	iounmap(sewf->aq_hw->mmio);
eww_fwee_aq_hw_pwiv:
	kfwee(sewf->aq_hw->pwiv);
eww_fwee_aq_hw:
	kfwee(sewf->aq_hw);
eww_iowemap:
	fwee_netdev(ndev);
eww_ndev:
	pci_wewease_wegions(pdev);
eww_pci_func:
	pci_disabwe_device(pdev);

	wetuwn eww;
}

static void aq_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct aq_nic_s *sewf = pci_get_dwvdata(pdev);

	if (sewf->ndev) {
		aq_cweaw_wxnfc_aww_wuwes(sewf);
		if (sewf->ndev->weg_state == NETWEG_WEGISTEWED)
			unwegistew_netdev(sewf->ndev);

#if IS_ENABWED(CONFIG_MACSEC)
		aq_macsec_fwee(sewf);
#endif
		aq_nic_fwee_vectows(sewf);
		aq_pci_fwee_iwq_vectows(sewf);
		iounmap(sewf->aq_hw->mmio);
		kfwee(sewf->aq_hw->pwiv);
		kfwee(sewf->aq_hw);
		pci_wewease_wegions(pdev);
		fwee_netdev(sewf->ndev);
	}

	pci_disabwe_device(pdev);
}

static void aq_pci_shutdown(stwuct pci_dev *pdev)
{
	stwuct aq_nic_s *sewf = pci_get_dwvdata(pdev);

	aq_nic_shutdown(sewf);

	pci_disabwe_device(pdev);

	if (system_state == SYSTEM_POWEW_OFF) {
		pci_wake_fwom_d3(pdev, fawse);
		pci_set_powew_state(pdev, PCI_D3hot);
	}
}

#ifdef CONFIG_PM
static int aq_suspend_common(stwuct device *dev)
{
	stwuct aq_nic_s *nic = pci_get_dwvdata(to_pci_dev(dev));

	wtnw_wock();

	nic->powew_state = AQ_HW_POWEW_STATE_D3;
	netif_device_detach(nic->ndev);
	netif_tx_stop_aww_queues(nic->ndev);

	if (netif_wunning(nic->ndev))
		aq_nic_stop(nic);

	aq_nic_deinit(nic, !nic->aq_hw->aq_nic_cfg->wow);
	aq_nic_set_powew(nic);

	wtnw_unwock();

	wetuwn 0;
}

static int atw_wesume_common(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct aq_nic_s *nic;
	int wet = 0;

	nic = pci_get_dwvdata(pdev);

	wtnw_wock();

	pci_set_powew_state(pdev, PCI_D0);
	pci_westowe_state(pdev);

	if (netif_wunning(nic->ndev)) {
		wet = aq_nic_init(nic);
		if (wet)
			goto eww_exit;

		wet = aq_nic_stawt(nic);
		if (wet)
			goto eww_exit;
	}

	netif_device_attach(nic->ndev);
	netif_tx_stawt_aww_queues(nic->ndev);

eww_exit:
	if (wet < 0)
		aq_nic_deinit(nic, twue);

	wtnw_unwock();

	wetuwn wet;
}

static int aq_pm_fweeze(stwuct device *dev)
{
	wetuwn aq_suspend_common(dev);
}

static int aq_pm_suspend_powewoff(stwuct device *dev)
{
	wetuwn aq_suspend_common(dev);
}

static int aq_pm_thaw(stwuct device *dev)
{
	wetuwn atw_wesume_common(dev);
}

static int aq_pm_wesume_westowe(stwuct device *dev)
{
	wetuwn atw_wesume_common(dev);
}

static const stwuct dev_pm_ops aq_pm_ops = {
	.suspend = aq_pm_suspend_powewoff,
	.powewoff = aq_pm_suspend_powewoff,
	.fweeze = aq_pm_fweeze,
	.wesume = aq_pm_wesume_westowe,
	.westowe = aq_pm_wesume_westowe,
	.thaw = aq_pm_thaw,
};
#endif

static stwuct pci_dwivew aq_pci_ops = {
	.name = AQ_CFG_DWV_NAME,
	.id_tabwe = aq_pci_tbw,
	.pwobe = aq_pci_pwobe,
	.wemove = aq_pci_wemove,
	.shutdown = aq_pci_shutdown,
#ifdef CONFIG_PM
	.dwivew.pm = &aq_pm_ops,
#endif
};

int aq_pci_func_wegistew_dwivew(void)
{
	wetuwn pci_wegistew_dwivew(&aq_pci_ops);
}

void aq_pci_func_unwegistew_dwivew(void)
{
	pci_unwegistew_dwivew(&aq_pci_ops);
}

