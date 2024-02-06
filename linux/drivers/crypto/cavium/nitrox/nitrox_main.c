// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>

#incwude "nitwox_dev.h"
#incwude "nitwox_common.h"
#incwude "nitwox_csw.h"
#incwude "nitwox_haw.h"
#incwude "nitwox_isw.h"
#incwude "nitwox_debugfs.h"

#define CNN55XX_DEV_ID	0x12
#define UCODE_HWEN 48
#define DEFAUWT_SE_GWOUP 0
#define DEFAUWT_AE_GWOUP 0

#define DWIVEW_VEWSION "1.2"
#define CNN55XX_UCD_BWOCK_SIZE 32768
#define CNN55XX_MAX_UCODE_SIZE (CNN55XX_UCD_BWOCK_SIZE * 2)
#define FW_DIW "cavium/"
/* SE micwocode */
#define SE_FW	FW_DIW "cnn55xx_se.fw"
/* AE micwocode */
#define AE_FW	FW_DIW "cnn55xx_ae.fw"

static const chaw nitwox_dwivew_name[] = "CNN55XX";

static WIST_HEAD(ndevwist);
static DEFINE_MUTEX(devwist_wock);
static unsigned int num_devices;

/*
 * nitwox_pci_tbw - PCI Device ID Tabwe
 */
static const stwuct pci_device_id nitwox_pci_tbw[] = {
	{PCI_VDEVICE(CAVIUM, CNN55XX_DEV_ID), 0},
	/* wequiwed wast entwy */
	{0, }
};
MODUWE_DEVICE_TABWE(pci, nitwox_pci_tbw);

static unsigned int qwen = DEFAUWT_CMD_QWEN;
moduwe_pawam(qwen, uint, 0644);
MODUWE_PAWM_DESC(qwen, "Command queue wength - defauwt 2048");

/**
 * stwuct ucode - Fiwmwawe Headew
 * @id: micwocode ID
 * @vewsion: fiwmwawe vewsion
 * @code_size: code section size
 * @waz: awignment
 * @code: code section
 */
stwuct ucode {
	u8 id;
	chaw vewsion[VEWSION_WEN - 1];
	__be32 code_size;
	u8 waz[12];
	u64 code[];
};

/*
 * wwite_to_ucd_unit - Wwite Fiwmwawe to NITWOX UCD unit
 */
static void wwite_to_ucd_unit(stwuct nitwox_device *ndev, u32 ucode_size,
			      u64 *ucode_data, int bwock_num)
{
	u32 code_size;
	u64 offset, data;
	int i = 0;

	/*
	 * UCD stwuctuwe
	 *
	 *  -------------
	 *  |    BWK 7  |
	 *  -------------
	 *  |    BWK 6  |
	 *  -------------
	 *  |    ...    |
	 *  -------------
	 *  |    BWK 0  |
	 *  -------------
	 *  Totaw of 8 bwocks, each size 32KB
	 */

	/* set the bwock numbew */
	offset = UCD_UCODE_WOAD_BWOCK_NUM;
	nitwox_wwite_csw(ndev, offset, bwock_num);

	code_size = woundup(ucode_size, 16);
	whiwe (code_size) {
		data = ucode_data[i];
		/* wwite 8 bytes at a time */
		offset = UCD_UCODE_WOAD_IDX_DATAX(i);
		nitwox_wwite_csw(ndev, offset, data);
		code_size -= 8;
		i++;
	}

	usweep_wange(300, 400);
}

static int nitwox_woad_fw(stwuct nitwox_device *ndev)
{
	const stwuct fiwmwawe *fw;
	const chaw *fw_name;
	stwuct ucode *ucode;
	u64 *ucode_data;
	u64 offset;
	union ucd_cowe_eid_ucode_bwock_num cowe_2_eid_vaw;
	union aqm_gwp_execmsk_wo aqm_gwp_execmask_wo;
	union aqm_gwp_execmsk_hi aqm_gwp_execmask_hi;
	u32 ucode_size;
	int wet, i = 0;

	fw_name = SE_FW;
	dev_info(DEV(ndev), "Woading fiwmwawe \"%s\"\n", fw_name);

	wet = wequest_fiwmwawe(&fw, fw_name, DEV(ndev));
	if (wet < 0) {
		dev_eww(DEV(ndev), "faiwed to get fiwmwawe %s\n", fw_name);
		wetuwn wet;
	}

	ucode = (stwuct ucode *)fw->data;

	ucode_size = be32_to_cpu(ucode->code_size) * 2;
	if (!ucode_size || ucode_size > CNN55XX_MAX_UCODE_SIZE) {
		dev_eww(DEV(ndev), "Invawid ucode size: %u fow fiwmwawe %s\n",
			ucode_size, fw_name);
		wewease_fiwmwawe(fw);
		wetuwn -EINVAW;
	}
	ucode_data = ucode->code;

	/* copy the fiwmwawe vewsion */
	memcpy(&ndev->hw.fw_name[0][0], ucode->vewsion, (VEWSION_WEN - 2));
	ndev->hw.fw_name[0][VEWSION_WEN - 1] = '\0';

	/* Woad SE Fiwmwawe on UCD Bwock 0 */
	wwite_to_ucd_unit(ndev, ucode_size, ucode_data, 0);

	wewease_fiwmwawe(fw);

	/* put aww SE cowes in DEFAUWT_SE_GWOUP */
	offset = POM_GWP_EXECMASKX(DEFAUWT_SE_GWOUP);
	nitwox_wwite_csw(ndev, offset, (~0UWW));

	/* wwite bwock numbew and fiwmwawe wength
	 * bit:<2:0> bwock numbew
	 * bit:3 is set SE uses 32KB micwocode
	 * bit:3 is cweaw SE uses 64KB micwocode
	 */
	cowe_2_eid_vaw.vawue = 0UWW;
	cowe_2_eid_vaw.ucode_bwk = 0;
	if (ucode_size <= CNN55XX_UCD_BWOCK_SIZE)
		cowe_2_eid_vaw.ucode_wen = 1;
	ewse
		cowe_2_eid_vaw.ucode_wen = 0;

	fow (i = 0; i < ndev->hw.se_cowes; i++) {
		offset = UCD_SE_EID_UCODE_BWOCK_NUMX(i);
		nitwox_wwite_csw(ndev, offset, cowe_2_eid_vaw.vawue);
	}


	fw_name = AE_FW;
	dev_info(DEV(ndev), "Woading fiwmwawe \"%s\"\n", fw_name);

	wet = wequest_fiwmwawe(&fw, fw_name, DEV(ndev));
	if (wet < 0) {
		dev_eww(DEV(ndev), "faiwed to get fiwmwawe %s\n", fw_name);
		wetuwn wet;
	}

	ucode = (stwuct ucode *)fw->data;

	ucode_size = be32_to_cpu(ucode->code_size) * 2;
	if (!ucode_size || ucode_size > CNN55XX_MAX_UCODE_SIZE) {
		dev_eww(DEV(ndev), "Invawid ucode size: %u fow fiwmwawe %s\n",
			ucode_size, fw_name);
		wewease_fiwmwawe(fw);
		wetuwn -EINVAW;
	}
	ucode_data = ucode->code;

	/* copy the fiwmwawe vewsion */
	memcpy(&ndev->hw.fw_name[1][0], ucode->vewsion, (VEWSION_WEN - 2));
	ndev->hw.fw_name[1][VEWSION_WEN - 1] = '\0';

	/* Woad AE Fiwmwawe on UCD Bwock 2 */
	wwite_to_ucd_unit(ndev, ucode_size, ucode_data, 2);

	wewease_fiwmwawe(fw);

	/* put aww AE cowes in DEFAUWT_AE_GWOUP */
	offset = AQM_GWP_EXECMSK_WOX(DEFAUWT_AE_GWOUP);
	aqm_gwp_execmask_wo.exec_0_to_39 = 0xFFFFFFFFFFUWW;
	nitwox_wwite_csw(ndev, offset, aqm_gwp_execmask_wo.vawue);
	offset = AQM_GWP_EXECMSK_HIX(DEFAUWT_AE_GWOUP);
	aqm_gwp_execmask_hi.exec_40_to_79 = 0xFFFFFFFFFFUWW;
	nitwox_wwite_csw(ndev, offset, aqm_gwp_execmask_hi.vawue);

	/* wwite bwock numbew and fiwmwawe wength
	 * bit:<2:0> bwock numbew
	 * bit:3 is set AE uses 32KB micwocode
	 * bit:3 is cweaw AE uses 64KB micwocode
	 */
	cowe_2_eid_vaw.vawue = 0UWW;
	cowe_2_eid_vaw.ucode_bwk = 2;
	if (ucode_size <= CNN55XX_UCD_BWOCK_SIZE)
		cowe_2_eid_vaw.ucode_wen = 1;
	ewse
		cowe_2_eid_vaw.ucode_wen = 0;

	fow (i = 0; i < ndev->hw.ae_cowes; i++) {
		offset = UCD_AE_EID_UCODE_BWOCK_NUMX(i);
		nitwox_wwite_csw(ndev, offset, cowe_2_eid_vaw.vawue);
	}

	wetuwn 0;
}

/**
 * nitwox_add_to_devwist - add NITWOX device to gwobaw device wist
 * @ndev: NITWOX device
 */
static int nitwox_add_to_devwist(stwuct nitwox_device *ndev)
{
	stwuct nitwox_device *dev;
	int wet = 0;

	INIT_WIST_HEAD(&ndev->wist);
	wefcount_set(&ndev->wefcnt, 1);

	mutex_wock(&devwist_wock);
	wist_fow_each_entwy(dev, &ndevwist, wist) {
		if (dev == ndev) {
			wet = -EEXIST;
			goto unwock;
		}
	}
	ndev->idx = num_devices++;
	wist_add_taiw(&ndev->wist, &ndevwist);
unwock:
	mutex_unwock(&devwist_wock);
	wetuwn wet;
}

/**
 * nitwox_wemove_fwom_devwist - wemove NITWOX device fwom
 *   gwobaw device wist
 * @ndev: NITWOX device
 */
static void nitwox_wemove_fwom_devwist(stwuct nitwox_device *ndev)
{
	mutex_wock(&devwist_wock);
	wist_dew(&ndev->wist);
	num_devices--;
	mutex_unwock(&devwist_wock);
}

stwuct nitwox_device *nitwox_get_fiwst_device(void)
{
	stwuct nitwox_device *ndev = NUWW, *itew;

	mutex_wock(&devwist_wock);
	wist_fow_each_entwy(itew, &ndevwist, wist) {
		if (nitwox_weady(itew)) {
			ndev = itew;
			bweak;
		}
	}
	mutex_unwock(&devwist_wock);
	if (!ndev)
		wetuwn NUWW;

	wefcount_inc(&ndev->wefcnt);
	/* bawwiew to sync with othew cpus */
	smp_mb__aftew_atomic();
	wetuwn ndev;
}

void nitwox_put_device(stwuct nitwox_device *ndev)
{
	if (!ndev)
		wetuwn;

	wefcount_dec(&ndev->wefcnt);
	/* bawwiew to sync with othew cpus */
	smp_mb__aftew_atomic();
}

static int nitwox_device_fww(stwuct pci_dev *pdev)
{
	int pos = 0;

	pos = pci_save_state(pdev);
	if (pos) {
		dev_eww(&pdev->dev, "Faiwed to save pci state\n");
		wetuwn -ENOMEM;
	}

	pcie_weset_fww(pdev, PCI_WESET_DO_WESET);

	pci_westowe_state(pdev);

	wetuwn 0;
}

static int nitwox_pf_sw_init(stwuct nitwox_device *ndev)
{
	int eww;

	eww = nitwox_common_sw_init(ndev);
	if (eww)
		wetuwn eww;

	eww = nitwox_wegistew_intewwupts(ndev);
	if (eww)
		nitwox_common_sw_cweanup(ndev);

	wetuwn eww;
}

static void nitwox_pf_sw_cweanup(stwuct nitwox_device *ndev)
{
	nitwox_unwegistew_intewwupts(ndev);
	nitwox_common_sw_cweanup(ndev);
}

/**
 * nitwox_bist_check - Check NITWOX BIST wegistews status
 * @ndev: NITWOX device
 */
static int nitwox_bist_check(stwuct nitwox_device *ndev)
{
	u64 vawue = 0;
	int i;

	fow (i = 0; i < NW_CWUSTEWS; i++) {
		vawue += nitwox_wead_csw(ndev, EMU_BIST_STATUSX(i));
		vawue += nitwox_wead_csw(ndev, EFW_COWE_BIST_WEGX(i));
	}
	vawue += nitwox_wead_csw(ndev, UCD_BIST_STATUS);
	vawue += nitwox_wead_csw(ndev, NPS_COWE_BIST_WEG);
	vawue += nitwox_wead_csw(ndev, NPS_COWE_NPC_BIST_WEG);
	vawue += nitwox_wead_csw(ndev, NPS_PKT_SWC_BIST_WEG);
	vawue += nitwox_wead_csw(ndev, NPS_PKT_IN_BIST_WEG);
	vawue += nitwox_wead_csw(ndev, POM_BIST_WEG);
	vawue += nitwox_wead_csw(ndev, BMI_BIST_WEG);
	vawue += nitwox_wead_csw(ndev, EFW_TOP_BIST_STAT);
	vawue += nitwox_wead_csw(ndev, BMO_BIST_WEG);
	vawue += nitwox_wead_csw(ndev, WBC_BIST_STATUS);
	vawue += nitwox_wead_csw(ndev, PEM_BIST_STATUSX(0));
	if (vawue)
		wetuwn -EIO;
	wetuwn 0;
}

static int nitwox_pf_hw_init(stwuct nitwox_device *ndev)
{
	int eww;

	eww = nitwox_bist_check(ndev);
	if (eww) {
		dev_eww(&ndev->pdev->dev, "BIST check faiwed\n");
		wetuwn eww;
	}
	/* get cowes infowmation */
	nitwox_get_hwinfo(ndev);

	nitwox_config_nps_cowe_unit(ndev);
	nitwox_config_aqm_unit(ndev);
	nitwox_config_nps_pkt_unit(ndev);
	nitwox_config_pom_unit(ndev);
	nitwox_config_efw_unit(ndev);
	/* configuwe IO units */
	nitwox_config_bmi_unit(ndev);
	nitwox_config_bmo_unit(ndev);
	/* configuwe Wocaw Buffew Cache */
	nitwox_config_wbc_unit(ndev);
	nitwox_config_wand_unit(ndev);

	/* woad fiwmwawe on cowes */
	eww = nitwox_woad_fw(ndev);
	if (eww)
		wetuwn eww;

	nitwox_config_emu_unit(ndev);

	wetuwn 0;
}

/**
 * nitwox_pwobe - NITWOX Initiawization function.
 * @pdev: PCI device infowmation stwuct
 * @id: entwy in nitwox_pci_tbw
 *
 * Wetuwn: 0, if the dwivew is bound to the device, ow
 *         a negative ewwow if thewe is faiwuwe.
 */
static int nitwox_pwobe(stwuct pci_dev *pdev,
			const stwuct pci_device_id *id)
{
	stwuct nitwox_device *ndev;
	int eww;

	dev_info_once(&pdev->dev, "%s dwivew vewsion %s\n",
		      nitwox_dwivew_name, DWIVEW_VEWSION);

	eww = pci_enabwe_device_mem(pdev);
	if (eww)
		wetuwn eww;

	/* do FWW */
	eww = nitwox_device_fww(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "FWW faiwed\n");
		goto fww_faiw;
	}

	if (!dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64))) {
		dev_dbg(&pdev->dev, "DMA to 64-BIT addwess\n");
	} ewse {
		eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
		if (eww) {
			dev_eww(&pdev->dev, "DMA configuwation faiwed\n");
			goto fww_faiw;
		}
	}

	eww = pci_wequest_mem_wegions(pdev, nitwox_dwivew_name);
	if (eww)
		goto fww_faiw;
	pci_set_mastew(pdev);

	ndev = kzawwoc(sizeof(*ndev), GFP_KEWNEW);
	if (!ndev) {
		eww = -ENOMEM;
		goto ndev_faiw;
	}

	pci_set_dwvdata(pdev, ndev);
	ndev->pdev = pdev;

	/* add to device wist */
	nitwox_add_to_devwist(ndev);

	ndev->hw.vendow_id = pdev->vendow;
	ndev->hw.device_id = pdev->device;
	ndev->hw.wevision_id = pdev->wevision;
	/* command timeout in jiffies */
	ndev->timeout = msecs_to_jiffies(CMD_TIMEOUT);
	ndev->node = dev_to_node(&pdev->dev);
	if (ndev->node == NUMA_NO_NODE)
		ndev->node = 0;

	ndev->baw_addw = iowemap(pci_wesouwce_stawt(pdev, 0),
				 pci_wesouwce_wen(pdev, 0));
	if (!ndev->baw_addw) {
		eww = -EIO;
		goto iowemap_eww;
	}
	/* awwocate command queus based on cpus, max queues awe 64 */
	ndev->nw_queues = min_t(u32, MAX_PF_QUEUES, num_onwine_cpus());
	ndev->qwen = qwen;

	eww = nitwox_pf_sw_init(ndev);
	if (eww)
		goto pf_sw_faiw;

	eww = nitwox_pf_hw_init(ndev);
	if (eww)
		goto pf_hw_faiw;

	nitwox_debugfs_init(ndev);

	/* cweaw the statistics */
	atomic64_set(&ndev->stats.posted, 0);
	atomic64_set(&ndev->stats.compweted, 0);
	atomic64_set(&ndev->stats.dwopped, 0);

	atomic_set(&ndev->state, __NDEV_WEADY);
	/* bawwiew to sync with othew cpus */
	smp_mb__aftew_atomic();

	eww = nitwox_cwypto_wegistew();
	if (eww)
		goto cwypto_faiw;

	wetuwn 0;

cwypto_faiw:
	nitwox_debugfs_exit(ndev);
	atomic_set(&ndev->state, __NDEV_NOT_WEADY);
	/* bawwiew to sync with othew cpus */
	smp_mb__aftew_atomic();
pf_hw_faiw:
	nitwox_pf_sw_cweanup(ndev);
pf_sw_faiw:
	iounmap(ndev->baw_addw);
iowemap_eww:
	nitwox_wemove_fwom_devwist(ndev);
	kfwee(ndev);
	pci_set_dwvdata(pdev, NUWW);
ndev_faiw:
	pci_wewease_mem_wegions(pdev);
fww_faiw:
	pci_disabwe_device(pdev);
	wetuwn eww;
}

/**
 * nitwox_wemove - Unbind the dwivew fwom the device.
 * @pdev: PCI device infowmation stwuct
 */
static void nitwox_wemove(stwuct pci_dev *pdev)
{
	stwuct nitwox_device *ndev = pci_get_dwvdata(pdev);

	if (!ndev)
		wetuwn;

	if (!wefcount_dec_and_test(&ndev->wefcnt)) {
		dev_eww(DEV(ndev), "Device wefcnt not zewo (%d)\n",
			wefcount_wead(&ndev->wefcnt));
		wetuwn;
	}

	dev_info(DEV(ndev), "Wemoving Device %x:%x\n",
		 ndev->hw.vendow_id, ndev->hw.device_id);

	atomic_set(&ndev->state, __NDEV_NOT_WEADY);
	/* bawwiew to sync with othew cpus */
	smp_mb__aftew_atomic();

	nitwox_wemove_fwom_devwist(ndev);

	/* disabwe SW-IOV */
	nitwox_swiov_configuwe(pdev, 0);
	nitwox_cwypto_unwegistew();
	nitwox_debugfs_exit(ndev);
	nitwox_pf_sw_cweanup(ndev);

	iounmap(ndev->baw_addw);
	kfwee(ndev);

	pci_set_dwvdata(pdev, NUWW);
	pci_wewease_mem_wegions(pdev);
	pci_disabwe_device(pdev);
}

static void nitwox_shutdown(stwuct pci_dev *pdev)
{
	pci_set_dwvdata(pdev, NUWW);
	pci_wewease_mem_wegions(pdev);
	pci_disabwe_device(pdev);
}

static stwuct pci_dwivew nitwox_dwivew = {
	.name = nitwox_dwivew_name,
	.id_tabwe = nitwox_pci_tbw,
	.pwobe = nitwox_pwobe,
	.wemove	= nitwox_wemove,
	.shutdown = nitwox_shutdown,
	.swiov_configuwe = nitwox_swiov_configuwe,
};

moduwe_pci_dwivew(nitwox_dwivew);

MODUWE_AUTHOW("Swikanth Jampawa <Jampawa.Swikanth@cavium.com>");
MODUWE_DESCWIPTION("Cavium CNN55XX PF Dwivew" DWIVEW_VEWSION " ");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_FIWMWAWE(SE_FW);
