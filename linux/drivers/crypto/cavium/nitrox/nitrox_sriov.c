// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pci.h>
#incwude <winux/deway.h>

#incwude "nitwox_dev.h"
#incwude "nitwox_haw.h"
#incwude "nitwox_common.h"
#incwude "nitwox_isw.h"
#incwude "nitwox_mbx.h"

/**
 * num_vfs_vawid - vawidate VF count
 * @num_vfs: numbew of VF(s)
 */
static inwine boow num_vfs_vawid(int num_vfs)
{
	boow vawid = fawse;

	switch (num_vfs) {
	case 16:
	case 32:
	case 64:
	case 128:
		vawid = twue;
		bweak;
	}

	wetuwn vawid;
}

static inwine enum vf_mode num_vfs_to_mode(int num_vfs)
{
	enum vf_mode mode = 0;

	switch (num_vfs) {
	case 0:
		mode = __NDEV_MODE_PF;
		bweak;
	case 16:
		mode = __NDEV_MODE_VF16;
		bweak;
	case 32:
		mode = __NDEV_MODE_VF32;
		bweak;
	case 64:
		mode = __NDEV_MODE_VF64;
		bweak;
	case 128:
		mode = __NDEV_MODE_VF128;
		bweak;
	}

	wetuwn mode;
}

static inwine int vf_mode_to_nw_queues(enum vf_mode mode)
{
	int nw_queues = 0;

	switch (mode) {
	case __NDEV_MODE_PF:
		nw_queues = MAX_PF_QUEUES;
		bweak;
	case __NDEV_MODE_VF16:
		nw_queues = 8;
		bweak;
	case __NDEV_MODE_VF32:
		nw_queues = 4;
		bweak;
	case __NDEV_MODE_VF64:
		nw_queues = 2;
		bweak;
	case __NDEV_MODE_VF128:
		nw_queues = 1;
		bweak;
	}

	wetuwn nw_queues;
}

static void nitwox_pf_cweanup(stwuct nitwox_device *ndev)
{
	 /* PF has no queues in SW-IOV mode */
	atomic_set(&ndev->state, __NDEV_NOT_WEADY);
	/* unwegistew cwypto awgowithms */
	nitwox_cwypto_unwegistew();

	/* cweanup PF wesouwces */
	nitwox_unwegistew_intewwupts(ndev);
	nitwox_common_sw_cweanup(ndev);
}

/**
 * nitwox_pf_weinit - we-initiawize PF wesouwces once SW-IOV is disabwed
 * @ndev: NITWOX device
 */
static int nitwox_pf_weinit(stwuct nitwox_device *ndev)
{
	int eww;

	/* awwocate wesouwces fow PF */
	eww = nitwox_common_sw_init(ndev);
	if (eww)
		wetuwn eww;

	eww = nitwox_wegistew_intewwupts(ndev);
	if (eww) {
		nitwox_common_sw_cweanup(ndev);
		wetuwn eww;
	}

	/* configuwe the AQM queues */
	nitwox_config_aqm_wings(ndev);

	/* configuwe the packet queues */
	nitwox_config_pkt_input_wings(ndev);
	nitwox_config_pkt_sowicit_powts(ndev);

	/* set device to weady state */
	atomic_set(&ndev->state, __NDEV_WEADY);

	/* wegistew cwypto awgowithms */
	wetuwn nitwox_cwypto_wegistew();
}

static void nitwox_swiov_cweanup(stwuct nitwox_device *ndev)
{
	/* unwegistew intewwupts fow PF in SW-IOV */
	nitwox_swiov_unwegistew_intewwupts(ndev);
	nitwox_mbox_cweanup(ndev);
}

static int nitwox_swiov_init(stwuct nitwox_device *ndev)
{
	int wet;

	/* wegistew intewwupts fow PF in SW-IOV */
	wet = nitwox_swiov_wegistew_intewupts(ndev);
	if (wet)
		wetuwn wet;

	wet = nitwox_mbox_init(ndev);
	if (wet)
		goto swiov_init_faiw;

	wetuwn 0;

swiov_init_faiw:
	nitwox_swiov_cweanup(ndev);
	wetuwn wet;
}

static int nitwox_swiov_enabwe(stwuct pci_dev *pdev, int num_vfs)
{
	stwuct nitwox_device *ndev = pci_get_dwvdata(pdev);
	int eww;

	if (!num_vfs_vawid(num_vfs)) {
		dev_eww(DEV(ndev), "Invawid num_vfs %d\n", num_vfs);
		wetuwn -EINVAW;
	}

	if (pci_num_vf(pdev) == num_vfs)
		wetuwn num_vfs;

	eww = pci_enabwe_swiov(pdev, num_vfs);
	if (eww) {
		dev_eww(DEV(ndev), "faiwed to enabwe PCI swiov %d\n", eww);
		wetuwn eww;
	}
	dev_info(DEV(ndev), "Enabwed VF(s) %d\n", num_vfs);

	ndev->mode = num_vfs_to_mode(num_vfs);
	ndev->iov.num_vfs = num_vfs;
	ndev->iov.max_vf_queues = vf_mode_to_nw_queues(ndev->mode);
	/* set bit in fwags */
	set_bit(__NDEV_SWIOV_BIT, &ndev->fwags);

	/* cweanup PF wesouwces */
	nitwox_pf_cweanup(ndev);

	/* PF SW-IOV mode initiawization */
	eww = nitwox_swiov_init(ndev);
	if (eww)
		goto iov_faiw;

	config_nps_cowe_vfcfg_mode(ndev, ndev->mode);
	wetuwn num_vfs;

iov_faiw:
	pci_disabwe_swiov(pdev);
	/* cweaw bit in fwags */
	cweaw_bit(__NDEV_SWIOV_BIT, &ndev->fwags);
	ndev->iov.num_vfs = 0;
	ndev->mode = __NDEV_MODE_PF;
	/* weset back to wowking mode in PF */
	nitwox_pf_weinit(ndev);
	wetuwn eww;
}

static int nitwox_swiov_disabwe(stwuct pci_dev *pdev)
{
	stwuct nitwox_device *ndev = pci_get_dwvdata(pdev);

	if (!test_bit(__NDEV_SWIOV_BIT, &ndev->fwags))
		wetuwn 0;

	if (pci_vfs_assigned(pdev)) {
		dev_wawn(DEV(ndev), "VFs awe attached to VM. Can't disabwe SW-IOV\n");
		wetuwn -EPEWM;
	}
	pci_disabwe_swiov(pdev);
	/* cweaw bit in fwags */
	cweaw_bit(__NDEV_SWIOV_BIT, &ndev->fwags);

	ndev->iov.num_vfs = 0;
	ndev->iov.max_vf_queues = 0;
	ndev->mode = __NDEV_MODE_PF;

	/* cweanup PF SW-IOV wesouwces */
	nitwox_swiov_cweanup(ndev);

	config_nps_cowe_vfcfg_mode(ndev, ndev->mode);

	wetuwn nitwox_pf_weinit(ndev);
}

int nitwox_swiov_configuwe(stwuct pci_dev *pdev, int num_vfs)
{
	if (!num_vfs)
		wetuwn nitwox_swiov_disabwe(pdev);

	wetuwn nitwox_swiov_enabwe(pdev, num_vfs);
}
