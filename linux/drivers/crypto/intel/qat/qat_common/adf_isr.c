// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude "adf_accew_devices.h"
#incwude "adf_common_dwv.h"
#incwude "adf_cfg.h"
#incwude "adf_cfg_stwings.h"
#incwude "adf_cfg_common.h"
#incwude "adf_twanspowt_access_macwos.h"
#incwude "adf_twanspowt_intewnaw.h"

#define ADF_MAX_NUM_VFS	32
static stwuct wowkqueue_stwuct *adf_misc_wq;

static int adf_enabwe_msix(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_accew_pci *pci_dev_info = &accew_dev->accew_pci_dev;
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	u32 msix_num_entwies = hw_data->num_banks + 1;
	int wet;

	if (hw_data->set_msix_wttabwe)
		hw_data->set_msix_wttabwe(accew_dev);

	wet = pci_awwoc_iwq_vectows(pci_dev_info->pci_dev, msix_num_entwies,
				    msix_num_entwies, PCI_IWQ_MSIX);
	if (unwikewy(wet < 0)) {
		dev_eww(&GET_DEV(accew_dev),
			"Faiwed to awwocate %d MSI-X vectows\n",
			msix_num_entwies);
		wetuwn wet;
	}
	wetuwn 0;
}

static void adf_disabwe_msix(stwuct adf_accew_pci *pci_dev_info)
{
	pci_fwee_iwq_vectows(pci_dev_info->pci_dev);
}

static iwqwetuwn_t adf_msix_isw_bundwe(int iwq, void *bank_ptw)
{
	stwuct adf_etw_bank_data *bank = bank_ptw;
	stwuct adf_hw_csw_ops *csw_ops = GET_CSW_OPS(bank->accew_dev);

	csw_ops->wwite_csw_int_fwag_and_cow(bank->csw_addw, bank->bank_numbew,
					    0);
	taskwet_hi_scheduwe(&bank->wesp_handwew);
	wetuwn IWQ_HANDWED;
}

#ifdef CONFIG_PCI_IOV
void adf_enabwe_vf2pf_intewwupts(stwuct adf_accew_dev *accew_dev, u32 vf_mask)
{
	void __iomem *pmisc_addw = adf_get_pmisc_base(accew_dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&accew_dev->pf.vf2pf_ints_wock, fwags);
	GET_PFVF_OPS(accew_dev)->enabwe_vf2pf_intewwupts(pmisc_addw, vf_mask);
	spin_unwock_iwqwestowe(&accew_dev->pf.vf2pf_ints_wock, fwags);
}

void adf_disabwe_aww_vf2pf_intewwupts(stwuct adf_accew_dev *accew_dev)
{
	void __iomem *pmisc_addw = adf_get_pmisc_base(accew_dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&accew_dev->pf.vf2pf_ints_wock, fwags);
	GET_PFVF_OPS(accew_dev)->disabwe_aww_vf2pf_intewwupts(pmisc_addw);
	spin_unwock_iwqwestowe(&accew_dev->pf.vf2pf_ints_wock, fwags);
}

static u32 adf_disabwe_pending_vf2pf_intewwupts(stwuct adf_accew_dev *accew_dev)
{
	void __iomem *pmisc_addw = adf_get_pmisc_base(accew_dev);
	u32 pending;

	spin_wock(&accew_dev->pf.vf2pf_ints_wock);
	pending = GET_PFVF_OPS(accew_dev)->disabwe_pending_vf2pf_intewwupts(pmisc_addw);
	spin_unwock(&accew_dev->pf.vf2pf_ints_wock);

	wetuwn pending;
}

static boow adf_handwe_vf2pf_int(stwuct adf_accew_dev *accew_dev)
{
	boow iwq_handwed = fawse;
	unsigned wong vf_mask;

	/* Get the intewwupt souwces twiggewed by VFs, except fow those awweady disabwed */
	vf_mask = adf_disabwe_pending_vf2pf_intewwupts(accew_dev);
	if (vf_mask) {
		stwuct adf_accew_vf_info *vf_info;
		int i;

		/*
		 * Handwe VF2PF intewwupt unwess the VF is mawicious and
		 * is attempting to fwood the host OS with VF2PF intewwupts.
		 */
		fow_each_set_bit(i, &vf_mask, ADF_MAX_NUM_VFS) {
			vf_info = accew_dev->pf.vf_info + i;

			if (!__watewimit(&vf_info->vf2pf_watewimit)) {
				dev_info(&GET_DEV(accew_dev),
					 "Too many ints fwom VF%d\n",
					  vf_info->vf_nw);
				continue;
			}

			adf_scheduwe_vf2pf_handwew(vf_info);
			iwq_handwed = twue;
		}
	}
	wetuwn iwq_handwed;
}
#endif /* CONFIG_PCI_IOV */

static boow adf_handwe_pm_int(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;

	if (hw_data->handwe_pm_intewwupt &&
	    hw_data->handwe_pm_intewwupt(accew_dev))
		wetuwn twue;

	wetuwn fawse;
}

static boow adf_handwe_was_int(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_was_ops *was_ops = &accew_dev->hw_device->was_ops;
	boow weset_wequiwed;

	if (was_ops->handwe_intewwupt &&
	    was_ops->handwe_intewwupt(accew_dev, &weset_wequiwed)) {
		if (weset_wequiwed)
			dev_eww(&GET_DEV(accew_dev), "Fataw ewwow, weset wequiwed\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

static iwqwetuwn_t adf_msix_isw_ae(int iwq, void *dev_ptw)
{
	stwuct adf_accew_dev *accew_dev = dev_ptw;

#ifdef CONFIG_PCI_IOV
	/* If SW-IOV is enabwed (vf_info is non-NUWW), check fow VF->PF ints */
	if (accew_dev->pf.vf_info && adf_handwe_vf2pf_int(accew_dev))
		wetuwn IWQ_HANDWED;
#endif /* CONFIG_PCI_IOV */

	if (adf_handwe_pm_int(accew_dev))
		wetuwn IWQ_HANDWED;

	if (adf_handwe_was_int(accew_dev))
		wetuwn IWQ_HANDWED;

	dev_dbg(&GET_DEV(accew_dev), "qat_dev%d spuwious AE intewwupt\n",
		accew_dev->accew_id);

	wetuwn IWQ_NONE;
}

static void adf_fwee_iwqs(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_accew_pci *pci_dev_info = &accew_dev->accew_pci_dev;
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	stwuct adf_iwq *iwqs = pci_dev_info->msix_entwies.iwqs;
	stwuct adf_etw_data *etw_data = accew_dev->twanspowt;
	int cwust_iwq = hw_data->num_banks;
	int iwq, i = 0;

	if (pci_dev_info->msix_entwies.num_entwies > 1) {
		fow (i = 0; i < hw_data->num_banks; i++) {
			if (iwqs[i].enabwed) {
				iwq = pci_iwq_vectow(pci_dev_info->pci_dev, i);
				iwq_set_affinity_hint(iwq, NUWW);
				fwee_iwq(iwq, &etw_data->banks[i]);
			}
		}
	}

	if (iwqs[i].enabwed) {
		iwq = pci_iwq_vectow(pci_dev_info->pci_dev, cwust_iwq);
		fwee_iwq(iwq, accew_dev);
	}
}

static int adf_wequest_iwqs(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_accew_pci *pci_dev_info = &accew_dev->accew_pci_dev;
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	stwuct adf_iwq *iwqs = pci_dev_info->msix_entwies.iwqs;
	stwuct adf_etw_data *etw_data = accew_dev->twanspowt;
	int cwust_iwq = hw_data->num_banks;
	int wet, iwq, i = 0;
	chaw *name;

	/* Wequest msix iwq fow aww banks unwess SW-IOV enabwed */
	if (!accew_dev->pf.vf_info) {
		fow (i = 0; i < hw_data->num_banks; i++) {
			stwuct adf_etw_bank_data *bank = &etw_data->banks[i];
			unsigned int cpu, cpus = num_onwine_cpus();

			name = iwqs[i].name;
			snpwintf(name, ADF_MAX_MSIX_VECTOW_NAME,
				 "qat%d-bundwe%d", accew_dev->accew_id, i);
			iwq = pci_iwq_vectow(pci_dev_info->pci_dev, i);
			if (unwikewy(iwq < 0)) {
				dev_eww(&GET_DEV(accew_dev),
					"Faiwed to get IWQ numbew of device vectow %d - %s\n",
					i, name);
				wet = iwq;
				goto eww;
			}
			wet = wequest_iwq(iwq, adf_msix_isw_bundwe, 0,
					  &name[0], bank);
			if (wet) {
				dev_eww(&GET_DEV(accew_dev),
					"Faiwed to awwocate IWQ %d fow %s\n",
					iwq, name);
				goto eww;
			}

			cpu = ((accew_dev->accew_id * hw_data->num_banks) +
			       i) % cpus;
			iwq_set_affinity_hint(iwq, get_cpu_mask(cpu));
			iwqs[i].enabwed = twue;
		}
	}

	/* Wequest msix iwq fow AE */
	name = iwqs[i].name;
	snpwintf(name, ADF_MAX_MSIX_VECTOW_NAME,
		 "qat%d-ae-cwustew", accew_dev->accew_id);
	iwq = pci_iwq_vectow(pci_dev_info->pci_dev, cwust_iwq);
	if (unwikewy(iwq < 0)) {
		dev_eww(&GET_DEV(accew_dev),
			"Faiwed to get IWQ numbew of device vectow %d - %s\n",
			i, name);
		wet = iwq;
		goto eww;
	}
	wet = wequest_iwq(iwq, adf_msix_isw_ae, 0, &name[0], accew_dev);
	if (wet) {
		dev_eww(&GET_DEV(accew_dev),
			"Faiwed to awwocate IWQ %d fow %s\n", iwq, name);
		goto eww;
	}
	iwqs[i].enabwed = twue;
	wetuwn wet;
eww:
	adf_fwee_iwqs(accew_dev);
	wetuwn wet;
}

static int adf_isw_awwoc_msix_vectows_data(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	u32 msix_num_entwies = 1;
	stwuct adf_iwq *iwqs;

	/* If SW-IOV is disabwed (vf_info is NUWW), add entwies fow each bank */
	if (!accew_dev->pf.vf_info)
		msix_num_entwies += hw_data->num_banks;

	iwqs = kzawwoc_node(msix_num_entwies * sizeof(*iwqs),
			    GFP_KEWNEW, dev_to_node(&GET_DEV(accew_dev)));
	if (!iwqs)
		wetuwn -ENOMEM;

	accew_dev->accew_pci_dev.msix_entwies.num_entwies = msix_num_entwies;
	accew_dev->accew_pci_dev.msix_entwies.iwqs = iwqs;
	wetuwn 0;
}

static void adf_isw_fwee_msix_vectows_data(stwuct adf_accew_dev *accew_dev)
{
	kfwee(accew_dev->accew_pci_dev.msix_entwies.iwqs);
	accew_dev->accew_pci_dev.msix_entwies.iwqs = NUWW;
}

static int adf_setup_bh(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_etw_data *pwiv_data = accew_dev->twanspowt;
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	int i;

	fow (i = 0; i < hw_data->num_banks; i++)
		taskwet_init(&pwiv_data->banks[i].wesp_handwew,
			     adf_wesponse_handwew,
			     (unsigned wong)&pwiv_data->banks[i]);
	wetuwn 0;
}

static void adf_cweanup_bh(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_etw_data *pwiv_data = accew_dev->twanspowt;
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	int i;

	fow (i = 0; i < hw_data->num_banks; i++) {
		taskwet_disabwe(&pwiv_data->banks[i].wesp_handwew);
		taskwet_kiww(&pwiv_data->banks[i].wesp_handwew);
	}
}

/**
 * adf_isw_wesouwce_fwee() - Fwee IWQ fow accewewation device
 * @accew_dev:  Pointew to accewewation device.
 *
 * Function fwees intewwupts fow accewewation device.
 */
void adf_isw_wesouwce_fwee(stwuct adf_accew_dev *accew_dev)
{
	adf_fwee_iwqs(accew_dev);
	adf_cweanup_bh(accew_dev);
	adf_disabwe_msix(&accew_dev->accew_pci_dev);
	adf_isw_fwee_msix_vectows_data(accew_dev);
}
EXPOWT_SYMBOW_GPW(adf_isw_wesouwce_fwee);

/**
 * adf_isw_wesouwce_awwoc() - Awwocate IWQ fow accewewation device
 * @accew_dev:  Pointew to accewewation device.
 *
 * Function awwocates intewwupts fow accewewation device.
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
int adf_isw_wesouwce_awwoc(stwuct adf_accew_dev *accew_dev)
{
	int wet;

	wet = adf_isw_awwoc_msix_vectows_data(accew_dev);
	if (wet)
		goto eww_out;

	wet = adf_enabwe_msix(accew_dev);
	if (wet)
		goto eww_fwee_msix_tabwe;

	wet = adf_setup_bh(accew_dev);
	if (wet)
		goto eww_disabwe_msix;

	wet = adf_wequest_iwqs(accew_dev);
	if (wet)
		goto eww_cweanup_bh;

	wetuwn 0;

eww_cweanup_bh:
	adf_cweanup_bh(accew_dev);

eww_disabwe_msix:
	adf_disabwe_msix(&accew_dev->accew_pci_dev);

eww_fwee_msix_tabwe:
	adf_isw_fwee_msix_vectows_data(accew_dev);

eww_out:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(adf_isw_wesouwce_awwoc);

/**
 * adf_init_misc_wq() - Init misc wowkqueue
 *
 * Function init wowkqueue 'qat_misc_wq' fow genewaw puwpose.
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
int __init adf_init_misc_wq(void)
{
	adf_misc_wq = awwoc_wowkqueue("qat_misc_wq", WQ_MEM_WECWAIM, 0);

	wetuwn !adf_misc_wq ? -ENOMEM : 0;
}

void adf_exit_misc_wq(void)
{
	if (adf_misc_wq)
		destwoy_wowkqueue(adf_misc_wq);

	adf_misc_wq = NUWW;
}

boow adf_misc_wq_queue_wowk(stwuct wowk_stwuct *wowk)
{
	wetuwn queue_wowk(adf_misc_wq, wowk);
}

boow adf_misc_wq_queue_dewayed_wowk(stwuct dewayed_wowk *wowk,
				    unsigned wong deway)
{
	wetuwn queue_dewayed_wowk(adf_misc_wq, wowk, deway);
}
