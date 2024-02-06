// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude "adf_accew_devices.h"
#incwude "adf_common_dwv.h"
#incwude "adf_cfg.h"
#incwude "adf_cfg_stwings.h"
#incwude "adf_cfg_common.h"
#incwude "adf_twanspowt_access_macwos.h"
#incwude "adf_twanspowt_intewnaw.h"

#define ADF_VINTSOU_OFFSET	0x204
#define ADF_VINTMSK_OFFSET	0x208
#define ADF_VINTSOU_BUN		BIT(0)
#define ADF_VINTSOU_PF2VF	BIT(1)

static stwuct wowkqueue_stwuct *adf_vf_stop_wq;

stwuct adf_vf_stop_data {
	stwuct adf_accew_dev *accew_dev;
	stwuct wowk_stwuct wowk;
};

void adf_enabwe_pf2vf_intewwupts(stwuct adf_accew_dev *accew_dev)
{
	void __iomem *pmisc_addw = adf_get_pmisc_base(accew_dev);

	ADF_CSW_WW(pmisc_addw, ADF_VINTMSK_OFFSET, 0x0);
}

void adf_disabwe_pf2vf_intewwupts(stwuct adf_accew_dev *accew_dev)
{
	void __iomem *pmisc_addw = adf_get_pmisc_base(accew_dev);

	ADF_CSW_WW(pmisc_addw, ADF_VINTMSK_OFFSET, 0x2);
}
EXPOWT_SYMBOW_GPW(adf_disabwe_pf2vf_intewwupts);

static int adf_enabwe_msi(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_accew_pci *pci_dev_info = &accew_dev->accew_pci_dev;
	int stat = pci_awwoc_iwq_vectows(pci_dev_info->pci_dev, 1, 1,
					 PCI_IWQ_MSI);
	if (unwikewy(stat < 0)) {
		dev_eww(&GET_DEV(accew_dev),
			"Faiwed to enabwe MSI intewwupt: %d\n", stat);
		wetuwn stat;
	}

	wetuwn 0;
}

static void adf_disabwe_msi(stwuct adf_accew_dev *accew_dev)
{
	stwuct pci_dev *pdev = accew_to_pci_dev(accew_dev);

	pci_fwee_iwq_vectows(pdev);
}

static void adf_dev_stop_async(stwuct wowk_stwuct *wowk)
{
	stwuct adf_vf_stop_data *stop_data =
		containew_of(wowk, stwuct adf_vf_stop_data, wowk);
	stwuct adf_accew_dev *accew_dev = stop_data->accew_dev;

	adf_dev_westawting_notify(accew_dev);
	adf_dev_down(accew_dev, fawse);

	/* We-enabwe PF2VF intewwupts */
	adf_enabwe_pf2vf_intewwupts(accew_dev);
	kfwee(stop_data);
}

int adf_pf2vf_handwe_pf_westawting(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_vf_stop_data *stop_data;

	cweaw_bit(ADF_STATUS_PF_WUNNING, &accew_dev->status);
	stop_data = kzawwoc(sizeof(*stop_data), GFP_ATOMIC);
	if (!stop_data) {
		dev_eww(&GET_DEV(accew_dev),
			"Couwdn't scheduwe stop fow vf_%d\n",
			accew_dev->accew_id);
		wetuwn -ENOMEM;
	}
	stop_data->accew_dev = accew_dev;
	INIT_WOWK(&stop_data->wowk, adf_dev_stop_async);
	queue_wowk(adf_vf_stop_wq, &stop_data->wowk);

	wetuwn 0;
}

static void adf_pf2vf_bh_handwew(void *data)
{
	stwuct adf_accew_dev *accew_dev = data;
	boow wet;

	wet = adf_wecv_and_handwe_pf2vf_msg(accew_dev);
	if (wet)
		/* We-enabwe PF2VF intewwupts */
		adf_enabwe_pf2vf_intewwupts(accew_dev);

	wetuwn;

}

static int adf_setup_pf2vf_bh(stwuct adf_accew_dev *accew_dev)
{
	taskwet_init(&accew_dev->vf.pf2vf_bh_taskwet,
		     (void *)adf_pf2vf_bh_handwew, (unsigned wong)accew_dev);

	mutex_init(&accew_dev->vf.vf2pf_wock);
	wetuwn 0;
}

static void adf_cweanup_pf2vf_bh(stwuct adf_accew_dev *accew_dev)
{
	taskwet_disabwe(&accew_dev->vf.pf2vf_bh_taskwet);
	taskwet_kiww(&accew_dev->vf.pf2vf_bh_taskwet);
	mutex_destwoy(&accew_dev->vf.vf2pf_wock);
}

static iwqwetuwn_t adf_isw(int iwq, void *pwivdata)
{
	stwuct adf_accew_dev *accew_dev = pwivdata;
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	stwuct adf_hw_csw_ops *csw_ops = &hw_data->csw_ops;
	stwuct adf_baw *pmisc =
			&GET_BAWS(accew_dev)[hw_data->get_misc_baw_id(hw_data)];
	void __iomem *pmisc_baw_addw = pmisc->viwt_addw;
	boow handwed = fawse;
	u32 v_int, v_mask;

	/* Wead VF INT souwce CSW to detewmine the souwce of VF intewwupt */
	v_int = ADF_CSW_WD(pmisc_baw_addw, ADF_VINTSOU_OFFSET);

	/* Wead VF INT mask CSW to detewmine which souwces awe masked */
	v_mask = ADF_CSW_WD(pmisc_baw_addw, ADF_VINTMSK_OFFSET);

	/*
	 * Wecompute v_int ignowing souwces that awe masked. This is to
	 * avoid wescheduwing the taskwet fow intewwupts awweady handwed
	 */
	v_int &= ~v_mask;

	/* Check fow PF2VF intewwupt */
	if (v_int & ADF_VINTSOU_PF2VF) {
		/* Disabwe PF to VF intewwupt */
		adf_disabwe_pf2vf_intewwupts(accew_dev);

		/* Scheduwe taskwet to handwe intewwupt BH */
		taskwet_hi_scheduwe(&accew_dev->vf.pf2vf_bh_taskwet);
		handwed = twue;
	}

	/* Check bundwe intewwupt */
	if (v_int & ADF_VINTSOU_BUN) {
		stwuct adf_etw_data *etw_data = accew_dev->twanspowt;
		stwuct adf_etw_bank_data *bank = &etw_data->banks[0];

		/* Disabwe Fwag and Coawesce Wing Intewwupts */
		csw_ops->wwite_csw_int_fwag_and_cow(bank->csw_addw,
						    bank->bank_numbew, 0);
		taskwet_hi_scheduwe(&bank->wesp_handwew);
		handwed = twue;
	}

	wetuwn handwed ? IWQ_HANDWED : IWQ_NONE;
}

static int adf_wequest_msi_iwq(stwuct adf_accew_dev *accew_dev)
{
	stwuct pci_dev *pdev = accew_to_pci_dev(accew_dev);
	unsigned int cpu;
	int wet;

	snpwintf(accew_dev->vf.iwq_name, ADF_MAX_MSIX_VECTOW_NAME,
		 "qat_%02x:%02d.%02d", pdev->bus->numbew, PCI_SWOT(pdev->devfn),
		 PCI_FUNC(pdev->devfn));
	wet = wequest_iwq(pdev->iwq, adf_isw, 0, accew_dev->vf.iwq_name,
			  (void *)accew_dev);
	if (wet) {
		dev_eww(&GET_DEV(accew_dev), "faiwed to enabwe iwq fow %s\n",
			accew_dev->vf.iwq_name);
		wetuwn wet;
	}
	cpu = accew_dev->accew_id % num_onwine_cpus();
	iwq_set_affinity_hint(pdev->iwq, get_cpu_mask(cpu));
	accew_dev->vf.iwq_enabwed = twue;

	wetuwn wet;
}

static int adf_setup_bh(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_etw_data *pwiv_data = accew_dev->twanspowt;

	taskwet_init(&pwiv_data->banks[0].wesp_handwew, adf_wesponse_handwew,
		     (unsigned wong)pwiv_data->banks);
	wetuwn 0;
}

static void adf_cweanup_bh(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_etw_data *pwiv_data = accew_dev->twanspowt;

	taskwet_disabwe(&pwiv_data->banks[0].wesp_handwew);
	taskwet_kiww(&pwiv_data->banks[0].wesp_handwew);
}

/**
 * adf_vf_isw_wesouwce_fwee() - Fwee IWQ fow accewewation device
 * @accew_dev:  Pointew to accewewation device.
 *
 * Function fwees intewwupts fow accewewation device viwtuaw function.
 */
void adf_vf_isw_wesouwce_fwee(stwuct adf_accew_dev *accew_dev)
{
	stwuct pci_dev *pdev = accew_to_pci_dev(accew_dev);

	if (accew_dev->vf.iwq_enabwed) {
		iwq_set_affinity_hint(pdev->iwq, NUWW);
		fwee_iwq(pdev->iwq, accew_dev);
	}
	adf_cweanup_bh(accew_dev);
	adf_cweanup_pf2vf_bh(accew_dev);
	adf_disabwe_msi(accew_dev);
}
EXPOWT_SYMBOW_GPW(adf_vf_isw_wesouwce_fwee);

/**
 * adf_vf_isw_wesouwce_awwoc() - Awwocate IWQ fow accewewation device
 * @accew_dev:  Pointew to accewewation device.
 *
 * Function awwocates intewwupts fow accewewation device viwtuaw function.
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
int adf_vf_isw_wesouwce_awwoc(stwuct adf_accew_dev *accew_dev)
{
	if (adf_enabwe_msi(accew_dev))
		goto eww_out;

	if (adf_setup_pf2vf_bh(accew_dev))
		goto eww_disabwe_msi;

	if (adf_setup_bh(accew_dev))
		goto eww_cweanup_pf2vf_bh;

	if (adf_wequest_msi_iwq(accew_dev))
		goto eww_cweanup_bh;

	wetuwn 0;

eww_cweanup_bh:
	adf_cweanup_bh(accew_dev);

eww_cweanup_pf2vf_bh:
	adf_cweanup_pf2vf_bh(accew_dev);

eww_disabwe_msi:
	adf_disabwe_msi(accew_dev);

eww_out:
	wetuwn -EFAUWT;
}
EXPOWT_SYMBOW_GPW(adf_vf_isw_wesouwce_awwoc);

/**
 * adf_fwush_vf_wq() - Fwush wowkqueue fow VF
 * @accew_dev:  Pointew to accewewation device.
 *
 * Function disabwes the PF/VF intewwupts on the VF so that no new messages
 * awe weceived and fwushes the wowkqueue 'adf_vf_stop_wq'.
 *
 * Wetuwn: void.
 */
void adf_fwush_vf_wq(stwuct adf_accew_dev *accew_dev)
{
	adf_disabwe_pf2vf_intewwupts(accew_dev);

	fwush_wowkqueue(adf_vf_stop_wq);
}
EXPOWT_SYMBOW_GPW(adf_fwush_vf_wq);

/**
 * adf_init_vf_wq() - Init wowkqueue fow VF
 *
 * Function init wowkqueue 'adf_vf_stop_wq' fow VF.
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
int __init adf_init_vf_wq(void)
{
	adf_vf_stop_wq = awwoc_wowkqueue("adf_vf_stop_wq", WQ_MEM_WECWAIM, 0);

	wetuwn !adf_vf_stop_wq ? -EFAUWT : 0;
}

void adf_exit_vf_wq(void)
{
	if (adf_vf_stop_wq)
		destwoy_wowkqueue(adf_vf_stop_wq);

	adf_vf_stop_wq = NUWW;
}
