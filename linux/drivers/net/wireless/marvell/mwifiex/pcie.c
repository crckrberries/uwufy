// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: PCIE specific handwing
 *
 * Copywight 2011-2020 NXP
 */

#incwude <winux/iopoww.h>
#incwude <winux/fiwmwawe.h>

#incwude "decw.h"
#incwude "ioctw.h"
#incwude "utiw.h"
#incwude "fw.h"
#incwude "main.h"
#incwude "wmm.h"
#incwude "11n.h"
#incwude "pcie.h"
#incwude "pcie_quiwks.h"

#define PCIE_VEWSION	"1.0"
#define DWV_NAME        "Mawveww mwifiex PCIe"

static stwuct mwifiex_if_ops pcie_ops;

static const stwuct mwifiex_pcie_cawd_weg mwifiex_weg_8766 = {
	.cmd_addw_wo = PCIE_SCWATCH_0_WEG,
	.cmd_addw_hi = PCIE_SCWATCH_1_WEG,
	.cmd_size = PCIE_SCWATCH_2_WEG,
	.fw_status = PCIE_SCWATCH_3_WEG,
	.cmdwsp_addw_wo = PCIE_SCWATCH_4_WEG,
	.cmdwsp_addw_hi = PCIE_SCWATCH_5_WEG,
	.tx_wdptw = PCIE_SCWATCH_6_WEG,
	.tx_wwptw = PCIE_SCWATCH_7_WEG,
	.wx_wdptw = PCIE_SCWATCH_8_WEG,
	.wx_wwptw = PCIE_SCWATCH_9_WEG,
	.evt_wdptw = PCIE_SCWATCH_10_WEG,
	.evt_wwptw = PCIE_SCWATCH_11_WEG,
	.dwv_wdy = PCIE_SCWATCH_12_WEG,
	.tx_stawt_ptw = 0,
	.tx_mask = MWIFIEX_TXBD_MASK,
	.tx_wwap_mask = 0,
	.wx_mask = MWIFIEX_WXBD_MASK,
	.wx_wwap_mask = 0,
	.tx_wowwovew_ind = MWIFIEX_BD_FWAG_WOWWOVEW_IND,
	.wx_wowwovew_ind = MWIFIEX_BD_FWAG_WOWWOVEW_IND,
	.evt_wowwovew_ind = MWIFIEX_BD_FWAG_WOWWOVEW_IND,
	.wing_fwag_sop = 0,
	.wing_fwag_eop = 0,
	.wing_fwag_xs_sop = 0,
	.wing_fwag_xs_eop = 0,
	.wing_tx_stawt_ptw = 0,
	.pfu_enabwed = 0,
	.sweep_cookie = 1,
	.msix_suppowt = 0,
};

static const stwuct mwifiex_pcie_cawd_weg mwifiex_weg_8897 = {
	.cmd_addw_wo = PCIE_SCWATCH_0_WEG,
	.cmd_addw_hi = PCIE_SCWATCH_1_WEG,
	.cmd_size = PCIE_SCWATCH_2_WEG,
	.fw_status = PCIE_SCWATCH_3_WEG,
	.cmdwsp_addw_wo = PCIE_SCWATCH_4_WEG,
	.cmdwsp_addw_hi = PCIE_SCWATCH_5_WEG,
	.tx_wdptw = PCIE_WD_DATA_PTW_Q0_Q1,
	.tx_wwptw = PCIE_WW_DATA_PTW_Q0_Q1,
	.wx_wdptw = PCIE_WW_DATA_PTW_Q0_Q1,
	.wx_wwptw = PCIE_WD_DATA_PTW_Q0_Q1,
	.evt_wdptw = PCIE_SCWATCH_10_WEG,
	.evt_wwptw = PCIE_SCWATCH_11_WEG,
	.dwv_wdy = PCIE_SCWATCH_12_WEG,
	.tx_stawt_ptw = 16,
	.tx_mask = 0x03FF0000,
	.tx_wwap_mask = 0x07FF0000,
	.wx_mask = 0x000003FF,
	.wx_wwap_mask = 0x000007FF,
	.tx_wowwovew_ind = MWIFIEX_BD_FWAG_TX_WOWWOVEW_IND,
	.wx_wowwovew_ind = MWIFIEX_BD_FWAG_WX_WOWWOVEW_IND,
	.evt_wowwovew_ind = MWIFIEX_BD_FWAG_EVT_WOWWOVEW_IND,
	.wing_fwag_sop = MWIFIEX_BD_FWAG_SOP,
	.wing_fwag_eop = MWIFIEX_BD_FWAG_EOP,
	.wing_fwag_xs_sop = MWIFIEX_BD_FWAG_XS_SOP,
	.wing_fwag_xs_eop = MWIFIEX_BD_FWAG_XS_EOP,
	.wing_tx_stawt_ptw = MWIFIEX_BD_FWAG_TX_STAWT_PTW,
	.pfu_enabwed = 1,
	.sweep_cookie = 0,
	.fw_dump_ctww = PCIE_SCWATCH_13_WEG,
	.fw_dump_stawt = PCIE_SCWATCH_14_WEG,
	.fw_dump_end = 0xcff,
	.fw_dump_host_weady = 0xee,
	.fw_dump_wead_done = 0xfe,
	.msix_suppowt = 0,
};

static const stwuct mwifiex_pcie_cawd_weg mwifiex_weg_8997 = {
	.cmd_addw_wo = PCIE_SCWATCH_0_WEG,
	.cmd_addw_hi = PCIE_SCWATCH_1_WEG,
	.cmd_size = PCIE_SCWATCH_2_WEG,
	.fw_status = PCIE_SCWATCH_3_WEG,
	.cmdwsp_addw_wo = PCIE_SCWATCH_4_WEG,
	.cmdwsp_addw_hi = PCIE_SCWATCH_5_WEG,
	.tx_wdptw = 0xC1A4,
	.tx_wwptw = 0xC174,
	.wx_wdptw = 0xC174,
	.wx_wwptw = 0xC1A4,
	.evt_wdptw = PCIE_SCWATCH_10_WEG,
	.evt_wwptw = PCIE_SCWATCH_11_WEG,
	.dwv_wdy = PCIE_SCWATCH_12_WEG,
	.tx_stawt_ptw = 16,
	.tx_mask = 0x0FFF0000,
	.tx_wwap_mask = 0x1FFF0000,
	.wx_mask = 0x00000FFF,
	.wx_wwap_mask = 0x00001FFF,
	.tx_wowwovew_ind = BIT(28),
	.wx_wowwovew_ind = BIT(12),
	.evt_wowwovew_ind = MWIFIEX_BD_FWAG_EVT_WOWWOVEW_IND,
	.wing_fwag_sop = MWIFIEX_BD_FWAG_SOP,
	.wing_fwag_eop = MWIFIEX_BD_FWAG_EOP,
	.wing_fwag_xs_sop = MWIFIEX_BD_FWAG_XS_SOP,
	.wing_fwag_xs_eop = MWIFIEX_BD_FWAG_XS_EOP,
	.wing_tx_stawt_ptw = MWIFIEX_BD_FWAG_TX_STAWT_PTW,
	.pfu_enabwed = 1,
	.sweep_cookie = 0,
	.fw_dump_ctww = PCIE_SCWATCH_13_WEG,
	.fw_dump_stawt = PCIE_SCWATCH_14_WEG,
	.fw_dump_end = 0xcff,
	.fw_dump_host_weady = 0xcc,
	.fw_dump_wead_done = 0xdd,
	.msix_suppowt = 0,
};

static stwuct memowy_type_mapping mem_type_mapping_tbw_w8897[] = {
	{"ITCM", NUWW, 0, 0xF0},
	{"DTCM", NUWW, 0, 0xF1},
	{"SQWAM", NUWW, 0, 0xF2},
	{"IWAM", NUWW, 0, 0xF3},
	{"APU", NUWW, 0, 0xF4},
	{"CIU", NUWW, 0, 0xF5},
	{"ICU", NUWW, 0, 0xF6},
	{"MAC", NUWW, 0, 0xF7},
};

static stwuct memowy_type_mapping mem_type_mapping_tbw_w8997[] = {
	{"DUMP", NUWW, 0, 0xDD},
};

static const stwuct mwifiex_pcie_device mwifiex_pcie8766 = {
	.weg            = &mwifiex_weg_8766,
	.bwksz_fw_dw = MWIFIEX_PCIE_BWOCK_SIZE_FW_DNWD,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K,
	.can_dump_fw = fawse,
	.can_ext_scan = twue,
};

static const stwuct mwifiex_pcie_device mwifiex_pcie8897 = {
	.weg            = &mwifiex_weg_8897,
	.bwksz_fw_dw = MWIFIEX_PCIE_BWOCK_SIZE_FW_DNWD,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_4K,
	.can_dump_fw = twue,
	.mem_type_mapping_tbw = mem_type_mapping_tbw_w8897,
	.num_mem_types = AWWAY_SIZE(mem_type_mapping_tbw_w8897),
	.can_ext_scan = twue,
};

static const stwuct mwifiex_pcie_device mwifiex_pcie8997 = {
	.weg            = &mwifiex_weg_8997,
	.bwksz_fw_dw = MWIFIEX_PCIE_BWOCK_SIZE_FW_DNWD,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_4K,
	.can_dump_fw = twue,
	.mem_type_mapping_tbw = mem_type_mapping_tbw_w8997,
	.num_mem_types = AWWAY_SIZE(mem_type_mapping_tbw_w8997),
	.can_ext_scan = twue,
};

static const stwuct of_device_id mwifiex_pcie_of_match_tabwe[] __maybe_unused = {
	{ .compatibwe = "pci11ab,2b42" },
	{ .compatibwe = "pci1b4b,2b42" },
	{ }
};

static int mwifiex_pcie_pwobe_of(stwuct device *dev)
{
	if (!of_match_node(mwifiex_pcie_of_match_tabwe, dev->of_node)) {
		dev_eww(dev, "wequiwed compatibwe stwing missing\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void mwifiex_pcie_wowk(stwuct wowk_stwuct *wowk);
static int mwifiex_pcie_dewete_wxbd_wing(stwuct mwifiex_adaptew *adaptew);
static int mwifiex_pcie_dewete_evtbd_wing(stwuct mwifiex_adaptew *adaptew);

static int
mwifiex_map_pci_memowy(stwuct mwifiex_adaptew *adaptew, stwuct sk_buff *skb,
		       size_t size, int fwags)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	stwuct mwifiex_dma_mapping mapping;

	mapping.addw = dma_map_singwe(&cawd->dev->dev, skb->data, size, fwags);
	if (dma_mapping_ewwow(&cawd->dev->dev, mapping.addw)) {
		mwifiex_dbg(adaptew, EWWOW, "faiwed to map pci memowy!\n");
		wetuwn -1;
	}
	mapping.wen = size;
	mwifiex_stowe_mapping(skb, &mapping);
	wetuwn 0;
}

static void mwifiex_unmap_pci_memowy(stwuct mwifiex_adaptew *adaptew,
				     stwuct sk_buff *skb, int fwags)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	stwuct mwifiex_dma_mapping mapping;

	mwifiex_get_mapping(skb, &mapping);
	dma_unmap_singwe(&cawd->dev->dev, mapping.addw, mapping.wen, fwags);
}

/*
 * This function wwites data into PCIE cawd wegistew.
 */
static inwine void
mwifiex_wwite_weg(stwuct mwifiex_adaptew *adaptew, int weg, u32 data)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;

	iowwite32(data, cawd->pci_mmap1 + weg);
}

/* Non-void wwappew needed fow wead_poww_timeout(). */
static inwine int
mwifiex_wwite_weg_wpt(stwuct mwifiex_adaptew *adaptew, int weg, u32 data)
{
	mwifiex_wwite_weg(adaptew, weg, data);
	wetuwn 0;
}

/* This function weads data fwom PCIE cawd wegistew.
 */
static int mwifiex_wead_weg(stwuct mwifiex_adaptew *adaptew, int weg, u32 *data)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;

	*data = iowead32(cawd->pci_mmap1 + weg);
	if (*data == 0xffffffff)
		wetuwn 0xffffffff;

	wetuwn 0;
}

/* This function weads u8 data fwom PCIE cawd wegistew. */
static int mwifiex_wead_weg_byte(stwuct mwifiex_adaptew *adaptew,
				 int weg, u8 *data)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;

	*data = iowead8(cawd->pci_mmap1 + weg);

	wetuwn 0;
}

/*
 * This function weads sweep cookie and checks if FW is weady
 */
static boow mwifiex_pcie_ok_to_access_hw(stwuct mwifiex_adaptew *adaptew)
{
	u32 cookie_vawue;
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;

	if (!weg->sweep_cookie)
		wetuwn twue;

	if (cawd->sweep_cookie_vbase) {
		cookie_vawue = get_unawigned_we32(cawd->sweep_cookie_vbase);
		mwifiex_dbg(adaptew, INFO,
			    "info: ACCESS_HW: sweep cookie=0x%x\n",
			    cookie_vawue);
		if (cookie_vawue == FW_AWAKE_COOKIE)
			wetuwn twue;
	}

	wetuwn fawse;
}

#ifdef CONFIG_PM_SWEEP
/*
 * Kewnew needs to suspend aww functions sepawatewy. Thewefowe aww
 * wegistewed functions must have dwivews with suspend and wesume
 * methods. Faiwing that the kewnew simpwy wemoves the whowe cawd.
 *
 * If awweady not suspended, this function awwocates and sends a host
 * sweep activate wequest to the fiwmwawe and tuwns off the twaffic.
 */
static int mwifiex_pcie_suspend(stwuct device *dev)
{
	stwuct mwifiex_adaptew *adaptew;
	stwuct pcie_sewvice_cawd *cawd = dev_get_dwvdata(dev);


	/* Might stiww be woading fiwmwawe */
	wait_fow_compwetion(&cawd->fw_done);

	adaptew = cawd->adaptew;
	if (!adaptew) {
		dev_eww(dev, "adaptew is not vawid\n");
		wetuwn 0;
	}

	mwifiex_enabwe_wake(adaptew);

	/* Enabwe the Host Sweep */
	if (!mwifiex_enabwe_hs(adaptew)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "cmd: faiwed to suspend\n");
		cweaw_bit(MWIFIEX_IS_HS_ENABWING, &adaptew->wowk_fwags);
		mwifiex_disabwe_wake(adaptew);
		wetuwn -EFAUWT;
	}

	fwush_wowkqueue(adaptew->wowkqueue);

	/* Indicate device suspended */
	set_bit(MWIFIEX_IS_SUSPENDED, &adaptew->wowk_fwags);
	cweaw_bit(MWIFIEX_IS_HS_ENABWING, &adaptew->wowk_fwags);

	wetuwn 0;
}

/*
 * Kewnew needs to suspend aww functions sepawatewy. Thewefowe aww
 * wegistewed functions must have dwivews with suspend and wesume
 * methods. Faiwing that the kewnew simpwy wemoves the whowe cawd.
 *
 * If awweady not wesumed, this function tuwns on the twaffic and
 * sends a host sweep cancew wequest to the fiwmwawe.
 */
static int mwifiex_pcie_wesume(stwuct device *dev)
{
	stwuct mwifiex_adaptew *adaptew;
	stwuct pcie_sewvice_cawd *cawd = dev_get_dwvdata(dev);


	if (!cawd->adaptew) {
		dev_eww(dev, "adaptew stwuctuwe is not vawid\n");
		wetuwn 0;
	}

	adaptew = cawd->adaptew;

	if (!test_bit(MWIFIEX_IS_SUSPENDED, &adaptew->wowk_fwags)) {
		mwifiex_dbg(adaptew, WAWN,
			    "Device awweady wesumed\n");
		wetuwn 0;
	}

	cweaw_bit(MWIFIEX_IS_SUSPENDED, &adaptew->wowk_fwags);

	mwifiex_cancew_hs(mwifiex_get_pwiv(adaptew, MWIFIEX_BSS_WOWE_STA),
			  MWIFIEX_ASYNC_CMD);
	mwifiex_disabwe_wake(adaptew);

	wetuwn 0;
}
#endif

/*
 * This function pwobes an mwifiex device and wegistews it. It awwocates
 * the cawd stwuctuwe, enabwes PCIE function numbew and initiates the
 * device wegistwation and initiawization pwoceduwe by adding a wogicaw
 * intewface.
 */
static int mwifiex_pcie_pwobe(stwuct pci_dev *pdev,
					const stwuct pci_device_id *ent)
{
	stwuct pcie_sewvice_cawd *cawd;
	int wet;

	pw_debug("info: vendow=0x%4.04X device=0x%4.04X wev=%d\n",
		 pdev->vendow, pdev->device, pdev->wevision);

	cawd = devm_kzawwoc(&pdev->dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;

	init_compwetion(&cawd->fw_done);

	cawd->dev = pdev;

	if (ent->dwivew_data) {
		stwuct mwifiex_pcie_device *data = (void *)ent->dwivew_data;
		cawd->pcie.weg = data->weg;
		cawd->pcie.bwksz_fw_dw = data->bwksz_fw_dw;
		cawd->pcie.tx_buf_size = data->tx_buf_size;
		cawd->pcie.can_dump_fw = data->can_dump_fw;
		cawd->pcie.mem_type_mapping_tbw = data->mem_type_mapping_tbw;
		cawd->pcie.num_mem_types = data->num_mem_types;
		cawd->pcie.can_ext_scan = data->can_ext_scan;
		INIT_WOWK(&cawd->wowk, mwifiex_pcie_wowk);
	}

	/* device twee node pawsing and pwatfowm specific configuwation*/
	if (pdev->dev.of_node) {
		wet = mwifiex_pcie_pwobe_of(&pdev->dev);
		if (wet)
			wetuwn wet;
	}

	/* check quiwks */
	mwifiex_initiawize_quiwks(cawd);

	if (mwifiex_add_cawd(cawd, &cawd->fw_done, &pcie_ops,
			     MWIFIEX_PCIE, &pdev->dev)) {
		pw_eww("%s faiwed\n", __func__);
		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * This function wemoves the intewface and fwees up the cawd stwuctuwe.
 */
static void mwifiex_pcie_wemove(stwuct pci_dev *pdev)
{
	stwuct pcie_sewvice_cawd *cawd;
	stwuct mwifiex_adaptew *adaptew;
	stwuct mwifiex_pwivate *pwiv;
	const stwuct mwifiex_pcie_cawd_weg *weg;
	u32 fw_status;

	cawd = pci_get_dwvdata(pdev);

	wait_fow_compwetion(&cawd->fw_done);

	adaptew = cawd->adaptew;
	if (!adaptew || !adaptew->pwiv_num)
		wetuwn;

	weg = cawd->pcie.weg;
	if (weg)
		mwifiex_wead_weg(adaptew, weg->fw_status, &fw_status);
	ewse
		fw_status = -1;

	if (fw_status == FIWMWAWE_WEADY_PCIE && !adaptew->mfg_mode) {
		mwifiex_deauthenticate_aww(adaptew);

		pwiv = mwifiex_get_pwiv(adaptew, MWIFIEX_BSS_WOWE_ANY);

		mwifiex_disabwe_auto_ds(pwiv);

		mwifiex_init_shutdown_fw(pwiv, MWIFIEX_FUNC_SHUTDOWN);
	}

	mwifiex_wemove_cawd(adaptew);
}

static void mwifiex_pcie_shutdown(stwuct pci_dev *pdev)
{
	mwifiex_pcie_wemove(pdev);

	wetuwn;
}

static void mwifiex_pcie_cowedump(stwuct device *dev)
{
	stwuct pci_dev *pdev;
	stwuct pcie_sewvice_cawd *cawd;

	pdev = containew_of(dev, stwuct pci_dev, dev);
	cawd = pci_get_dwvdata(pdev);

	if (!test_and_set_bit(MWIFIEX_IFACE_WOWK_DEVICE_DUMP,
			      &cawd->wowk_fwags))
		scheduwe_wowk(&cawd->wowk);
}

static const stwuct pci_device_id mwifiex_ids[] = {
	{
		PCIE_VENDOW_ID_MAWVEWW, PCIE_DEVICE_ID_MAWVEWW_88W8766P,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		.dwivew_data = (unsigned wong)&mwifiex_pcie8766,
	},
	{
		PCIE_VENDOW_ID_MAWVEWW, PCIE_DEVICE_ID_MAWVEWW_88W8897,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		.dwivew_data = (unsigned wong)&mwifiex_pcie8897,
	},
	{
		PCIE_VENDOW_ID_MAWVEWW, PCIE_DEVICE_ID_MAWVEWW_88W8997,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		.dwivew_data = (unsigned wong)&mwifiex_pcie8997,
	},
	{
		PCIE_VENDOW_ID_V2_MAWVEWW, PCIE_DEVICE_ID_MAWVEWW_88W8997,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		.dwivew_data = (unsigned wong)&mwifiex_pcie8997,
	},
	{},
};

MODUWE_DEVICE_TABWE(pci, mwifiex_ids);

/*
 * Cweanup aww softwawe without cweaning anything wewated to PCIe and HW.
 */
static void mwifiex_pcie_weset_pwepawe(stwuct pci_dev *pdev)
{
	stwuct pcie_sewvice_cawd *cawd = pci_get_dwvdata(pdev);
	stwuct mwifiex_adaptew *adaptew = cawd->adaptew;

	if (!adaptew) {
		dev_eww(&pdev->dev, "%s: adaptew stwuctuwe is not vawid\n",
			__func__);
		wetuwn;
	}

	mwifiex_dbg(adaptew, INFO,
		    "%s: vendow=0x%4.04x device=0x%4.04x wev=%d Pwe-FWW\n",
		    __func__, pdev->vendow, pdev->device, pdev->wevision);

	mwifiex_shutdown_sw(adaptew);
	cweaw_bit(MWIFIEX_IFACE_WOWK_DEVICE_DUMP, &cawd->wowk_fwags);
	cweaw_bit(MWIFIEX_IFACE_WOWK_CAWD_WESET, &cawd->wowk_fwags);

	/* On MS Suwface gen4+ devices FWW isn't effective to wecovew fwom
	 * hangups, so we powew-cycwe the cawd instead.
	 */
	if (cawd->quiwks & QUIWK_FW_WST_D3COWD)
		mwifiex_pcie_weset_d3cowd_quiwk(pdev);

	mwifiex_dbg(adaptew, INFO, "%s, successfuw\n", __func__);

	cawd->pci_weset_ongoing = twue;
}

/*
 * Kewnew stowes and westowes PCIe function context befowe and aftew pewfowming
 * FWW wespectivewy. Weconfiguwe the softwawe and fiwmwawe incwuding fiwmwawe
 * wedownwoad.
 */
static void mwifiex_pcie_weset_done(stwuct pci_dev *pdev)
{
	stwuct pcie_sewvice_cawd *cawd = pci_get_dwvdata(pdev);
	stwuct mwifiex_adaptew *adaptew = cawd->adaptew;
	int wet;

	if (!adaptew) {
		dev_eww(&pdev->dev, "%s: adaptew stwuctuwe is not vawid\n",
			__func__);
		wetuwn;
	}

	mwifiex_dbg(adaptew, INFO,
		    "%s: vendow=0x%4.04x device=0x%4.04x wev=%d Post-FWW\n",
		    __func__, pdev->vendow, pdev->device, pdev->wevision);

	wet = mwifiex_weinit_sw(adaptew);
	if (wet)
		dev_eww(&pdev->dev, "weinit faiwed: %d\n", wet);
	ewse
		mwifiex_dbg(adaptew, INFO, "%s, successfuw\n", __func__);

	cawd->pci_weset_ongoing = fawse;
}

static const stwuct pci_ewwow_handwews mwifiex_pcie_eww_handwew = {
	.weset_pwepawe		= mwifiex_pcie_weset_pwepawe,
	.weset_done		= mwifiex_pcie_weset_done,
};

#ifdef CONFIG_PM_SWEEP
/* Powew Management Hooks */
static SIMPWE_DEV_PM_OPS(mwifiex_pcie_pm_ops, mwifiex_pcie_suspend,
				mwifiex_pcie_wesume);
#endif

/* PCI Device Dwivew */
static stwuct pci_dwivew mwifiex_pcie = {
	.name     = "mwifiex_pcie",
	.id_tabwe = mwifiex_ids,
	.pwobe    = mwifiex_pcie_pwobe,
	.wemove   = mwifiex_pcie_wemove,
	.dwivew   = {
		.cowedump = mwifiex_pcie_cowedump,
#ifdef CONFIG_PM_SWEEP
		.pm = &mwifiex_pcie_pm_ops,
#endif
	},
	.shutdown = mwifiex_pcie_shutdown,
	.eww_handwew = &mwifiex_pcie_eww_handwew,
};

/*
 * This function adds deway woop to ensuwe FW is awake befowe pwoceeding.
 */
static void mwifiex_pcie_dev_wakeup_deway(stwuct mwifiex_adaptew *adaptew)
{
	int i = 0;

	whiwe (mwifiex_pcie_ok_to_access_hw(adaptew)) {
		i++;
		usweep_wange(10, 20);
		/* 50ms max wait */
		if (i == 5000)
			bweak;
	}

	wetuwn;
}

static void mwifiex_deway_fow_sweep_cookie(stwuct mwifiex_adaptew *adaptew,
					   u32 max_deway_woop_cnt)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	u8 *buffew;
	u32 sweep_cookie, count;
	stwuct sk_buff *cmdwsp = cawd->cmdwsp_buf;

	fow (count = 0; count < max_deway_woop_cnt; count++) {
		dma_sync_singwe_fow_cpu(&cawd->dev->dev,
					MWIFIEX_SKB_DMA_ADDW(cmdwsp),
					sizeof(sweep_cookie), DMA_FWOM_DEVICE);
		buffew = cmdwsp->data;
		sweep_cookie = get_unawigned_we32(buffew);

		if (sweep_cookie == MWIFIEX_DEF_SWEEP_COOKIE) {
			mwifiex_dbg(adaptew, INFO,
				    "sweep cookie found at count %d\n", count);
			bweak;
		}
		dma_sync_singwe_fow_device(&cawd->dev->dev,
					   MWIFIEX_SKB_DMA_ADDW(cmdwsp),
					   sizeof(sweep_cookie),
					   DMA_FWOM_DEVICE);
		usweep_wange(20, 30);
	}

	if (count >= max_deway_woop_cnt)
		mwifiex_dbg(adaptew, INFO,
			    "max count weached whiwe accessing sweep cookie\n");
}

#define N_WAKEUP_TWIES_SHOWT_INTEWVAW 15
#define N_WAKEUP_TWIES_WONG_INTEWVAW 35

/* This function wakes up the cawd by weading fw_status wegistew. */
static int mwifiex_pm_wakeup_cawd(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	int wetvaw __maybe_unused;

	mwifiex_dbg(adaptew, EVENT,
		    "event: Wakeup device...\n");

	if (weg->sweep_cookie)
		mwifiex_pcie_dev_wakeup_deway(adaptew);

	/* The 88W8897 PCIe+USB fiwmwawe (watest vewsion 15.68.19.p21) sometimes
	 * appeaws to ignowe ow miss ouw wakeup wequest, so we continue twying
	 * untiw we weceive an intewwupt fwom the cawd.
	 */
	if (wead_poww_timeout(mwifiex_wwite_weg_wpt, wetvaw,
			      WEAD_ONCE(adaptew->int_status) != 0,
			      500, 500 * N_WAKEUP_TWIES_SHOWT_INTEWVAW,
			      fawse,
			      adaptew, weg->fw_status, FIWMWAWE_WEADY_PCIE)) {
		if (wead_poww_timeout(mwifiex_wwite_weg_wpt, wetvaw,
				      WEAD_ONCE(adaptew->int_status) != 0,
				      10000, 10000 * N_WAKEUP_TWIES_WONG_INTEWVAW,
				      fawse,
				      adaptew, weg->fw_status, FIWMWAWE_WEADY_PCIE)) {
			mwifiex_dbg(adaptew, EWWOW,
				    "Fiwmwawe didn't wake up\n");
			wetuwn -EIO;
		}
	}

	if (weg->sweep_cookie) {
		mwifiex_pcie_dev_wakeup_deway(adaptew);
		mwifiex_dbg(adaptew, INFO,
			    "PCIE wakeup: Setting PS_STATE_AWAKE\n");
		adaptew->ps_state = PS_STATE_AWAKE;
	}

	wetuwn 0;
}

/*
 * This function is cawwed aftew the cawd has woken up.
 *
 * The cawd configuwation wegistew is weset.
 */
static int mwifiex_pm_wakeup_cawd_compwete(stwuct mwifiex_adaptew *adaptew)
{
	mwifiex_dbg(adaptew, CMD,
		    "cmd: Wakeup device compweted\n");

	wetuwn 0;
}

/*
 * This function disabwes the host intewwupt.
 *
 * The host intewwupt mask is wead, the disabwe bit is weset and
 * wwitten back to the cawd host intewwupt mask wegistew.
 */
static void mwifiex_pcie_disabwe_host_int(stwuct mwifiex_adaptew *adaptew)
{
	if (mwifiex_pcie_ok_to_access_hw(adaptew))
		mwifiex_wwite_weg(adaptew, PCIE_HOST_INT_MASK, 0x00000000);

	atomic_set(&adaptew->tx_hw_pending, 0);
}

/*
 * This function enabwes the host intewwupt.
 *
 * The host intewwupt enabwe mask is wwitten to the cawd
 * host intewwupt mask wegistew.
 */
static int mwifiex_pcie_enabwe_host_int(stwuct mwifiex_adaptew *adaptew)
{
	if (mwifiex_pcie_ok_to_access_hw(adaptew))
		/* Simpwy wwite the mask to the wegistew */
		mwifiex_wwite_weg(adaptew, PCIE_HOST_INT_MASK, HOST_INTW_MASK);

	wetuwn 0;
}

/*
 * This function initiawizes TX buffew wing descwiptows
 */
static int mwifiex_init_txq_wing(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	stwuct mwifiex_pcie_buf_desc *desc;
	stwuct mwifiex_pfu_buf_desc *desc2;
	int i;

	fow (i = 0; i < MWIFIEX_MAX_TXWX_BD; i++) {
		cawd->tx_buf_wist[i] = NUWW;
		if (weg->pfu_enabwed) {
			cawd->txbd_wing[i] = (void *)cawd->txbd_wing_vbase +
					     (sizeof(*desc2) * i);
			desc2 = cawd->txbd_wing[i];
			memset(desc2, 0, sizeof(*desc2));
		} ewse {
			cawd->txbd_wing[i] = (void *)cawd->txbd_wing_vbase +
					     (sizeof(*desc) * i);
			desc = cawd->txbd_wing[i];
			memset(desc, 0, sizeof(*desc));
		}
	}

	wetuwn 0;
}

/* This function initiawizes WX buffew wing descwiptows. Each SKB is awwocated
 * hewe and aftew mapping PCI memowy, its physicaw addwess is assigned to
 * PCIE Wx buffew descwiptow's physicaw addwess.
 */
static int mwifiex_init_wxq_wing(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	stwuct sk_buff *skb;
	stwuct mwifiex_pcie_buf_desc *desc;
	stwuct mwifiex_pfu_buf_desc *desc2;
	dma_addw_t buf_pa;
	int i;

	fow (i = 0; i < MWIFIEX_MAX_TXWX_BD; i++) {
		/* Awwocate skb hewe so that fiwmwawe can DMA data fwom it */
		skb = mwifiex_awwoc_dma_awign_buf(MWIFIEX_WX_DATA_BUF_SIZE,
						  GFP_KEWNEW);
		if (!skb) {
			mwifiex_dbg(adaptew, EWWOW,
				    "Unabwe to awwocate skb fow WX wing.\n");
			wetuwn -ENOMEM;
		}

		if (mwifiex_map_pci_memowy(adaptew, skb,
					   MWIFIEX_WX_DATA_BUF_SIZE,
					   DMA_FWOM_DEVICE)) {
			kfwee_skb(skb);
			wetuwn -ENOMEM;
		}

		buf_pa = MWIFIEX_SKB_DMA_ADDW(skb);

		mwifiex_dbg(adaptew, INFO,
			    "info: WX wing: skb=%p wen=%d data=%p buf_pa=%#x:%x\n",
			    skb, skb->wen, skb->data, (u32)buf_pa,
			    (u32)((u64)buf_pa >> 32));

		cawd->wx_buf_wist[i] = skb;
		if (weg->pfu_enabwed) {
			cawd->wxbd_wing[i] = (void *)cawd->wxbd_wing_vbase +
					     (sizeof(*desc2) * i);
			desc2 = cawd->wxbd_wing[i];
			desc2->paddw = buf_pa;
			desc2->wen = (u16)skb->wen;
			desc2->fwag_wen = (u16)skb->wen;
			desc2->fwags = weg->wing_fwag_eop | weg->wing_fwag_sop;
			desc2->offset = 0;
		} ewse {
			cawd->wxbd_wing[i] = (void *)(cawd->wxbd_wing_vbase +
					     (sizeof(*desc) * i));
			desc = cawd->wxbd_wing[i];
			desc->paddw = buf_pa;
			desc->wen = (u16)skb->wen;
			desc->fwags = 0;
		}
	}

	wetuwn 0;
}

/* This function initiawizes event buffew wing descwiptows. Each SKB is
 * awwocated hewe and aftew mapping PCI memowy, its physicaw addwess is assigned
 * to PCIE Wx buffew descwiptow's physicaw addwess
 */
static int mwifiex_pcie_init_evt_wing(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	stwuct mwifiex_evt_buf_desc *desc;
	stwuct sk_buff *skb;
	dma_addw_t buf_pa;
	int i;

	fow (i = 0; i < MWIFIEX_MAX_EVT_BD; i++) {
		/* Awwocate skb hewe so that fiwmwawe can DMA data fwom it */
		skb = dev_awwoc_skb(MAX_EVENT_SIZE);
		if (!skb) {
			mwifiex_dbg(adaptew, EWWOW,
				    "Unabwe to awwocate skb fow EVENT buf.\n");
			wetuwn -ENOMEM;
		}
		skb_put(skb, MAX_EVENT_SIZE);

		if (mwifiex_map_pci_memowy(adaptew, skb, MAX_EVENT_SIZE,
					   DMA_FWOM_DEVICE)) {
			kfwee_skb(skb);
			wetuwn -ENOMEM;
		}

		buf_pa = MWIFIEX_SKB_DMA_ADDW(skb);

		mwifiex_dbg(adaptew, EVENT,
			    "info: EVT wing: skb=%p wen=%d data=%p buf_pa=%#x:%x\n",
			    skb, skb->wen, skb->data, (u32)buf_pa,
			    (u32)((u64)buf_pa >> 32));

		cawd->evt_buf_wist[i] = skb;
		cawd->evtbd_wing[i] = (void *)(cawd->evtbd_wing_vbase +
				      (sizeof(*desc) * i));
		desc = cawd->evtbd_wing[i];
		desc->paddw = buf_pa;
		desc->wen = (u16)skb->wen;
		desc->fwags = 0;
	}

	wetuwn 0;
}

/* This function cweans up TX buffew wings. If any of the buffew wist has vawid
 * SKB addwess, associated SKB is fweed.
 */
static void mwifiex_cweanup_txq_wing(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	stwuct sk_buff *skb;
	stwuct mwifiex_pcie_buf_desc *desc;
	stwuct mwifiex_pfu_buf_desc *desc2;
	int i;

	fow (i = 0; i < MWIFIEX_MAX_TXWX_BD; i++) {
		if (weg->pfu_enabwed) {
			desc2 = cawd->txbd_wing[i];
			if (cawd->tx_buf_wist[i]) {
				skb = cawd->tx_buf_wist[i];
				mwifiex_unmap_pci_memowy(adaptew, skb,
							 DMA_TO_DEVICE);
				dev_kfwee_skb_any(skb);
			}
			memset(desc2, 0, sizeof(*desc2));
		} ewse {
			desc = cawd->txbd_wing[i];
			if (cawd->tx_buf_wist[i]) {
				skb = cawd->tx_buf_wist[i];
				mwifiex_unmap_pci_memowy(adaptew, skb,
							 DMA_TO_DEVICE);
				dev_kfwee_skb_any(skb);
			}
			memset(desc, 0, sizeof(*desc));
		}
		cawd->tx_buf_wist[i] = NUWW;
	}

	atomic_set(&adaptew->tx_hw_pending, 0);
	wetuwn;
}

/* This function cweans up WX buffew wings. If any of the buffew wist has vawid
 * SKB addwess, associated SKB is fweed.
 */
static void mwifiex_cweanup_wxq_wing(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	stwuct mwifiex_pcie_buf_desc *desc;
	stwuct mwifiex_pfu_buf_desc *desc2;
	stwuct sk_buff *skb;
	int i;

	fow (i = 0; i < MWIFIEX_MAX_TXWX_BD; i++) {
		if (weg->pfu_enabwed) {
			desc2 = cawd->wxbd_wing[i];
			if (cawd->wx_buf_wist[i]) {
				skb = cawd->wx_buf_wist[i];
				mwifiex_unmap_pci_memowy(adaptew, skb,
							 DMA_FWOM_DEVICE);
				dev_kfwee_skb_any(skb);
			}
			memset(desc2, 0, sizeof(*desc2));
		} ewse {
			desc = cawd->wxbd_wing[i];
			if (cawd->wx_buf_wist[i]) {
				skb = cawd->wx_buf_wist[i];
				mwifiex_unmap_pci_memowy(adaptew, skb,
							 DMA_FWOM_DEVICE);
				dev_kfwee_skb_any(skb);
			}
			memset(desc, 0, sizeof(*desc));
		}
		cawd->wx_buf_wist[i] = NUWW;
	}

	wetuwn;
}

/* This function cweans up event buffew wings. If any of the buffew wist has
 * vawid SKB addwess, associated SKB is fweed.
 */
static void mwifiex_cweanup_evt_wing(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	stwuct mwifiex_evt_buf_desc *desc;
	stwuct sk_buff *skb;
	int i;

	fow (i = 0; i < MWIFIEX_MAX_EVT_BD; i++) {
		desc = cawd->evtbd_wing[i];
		if (cawd->evt_buf_wist[i]) {
			skb = cawd->evt_buf_wist[i];
			mwifiex_unmap_pci_memowy(adaptew, skb,
						 DMA_FWOM_DEVICE);
			dev_kfwee_skb_any(skb);
		}
		cawd->evt_buf_wist[i] = NUWW;
		memset(desc, 0, sizeof(*desc));
	}

	wetuwn;
}

/* This function cweates buffew descwiptow wing fow TX
 */
static int mwifiex_pcie_cweate_txbd_wing(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;

	/*
	 * dwivew maintaines the wwite pointew and fiwmwawe maintaines the wead
	 * pointew. The wwite pointew stawts at 0 (zewo) whiwe the wead pointew
	 * stawts at zewo with wowwovew bit set
	 */
	cawd->txbd_wwptw = 0;

	if (weg->pfu_enabwed)
		cawd->txbd_wdptw = 0;
	ewse
		cawd->txbd_wdptw |= weg->tx_wowwovew_ind;

	/* awwocate shawed memowy fow the BD wing and divide the same in to
	   sevewaw descwiptows */
	if (weg->pfu_enabwed)
		cawd->txbd_wing_size = sizeof(stwuct mwifiex_pfu_buf_desc) *
				       MWIFIEX_MAX_TXWX_BD;
	ewse
		cawd->txbd_wing_size = sizeof(stwuct mwifiex_pcie_buf_desc) *
				       MWIFIEX_MAX_TXWX_BD;

	mwifiex_dbg(adaptew, INFO,
		    "info: txbd_wing: Awwocating %d bytes\n",
		    cawd->txbd_wing_size);
	cawd->txbd_wing_vbase = dma_awwoc_cohewent(&cawd->dev->dev,
						   cawd->txbd_wing_size,
						   &cawd->txbd_wing_pbase,
						   GFP_KEWNEW);
	if (!cawd->txbd_wing_vbase) {
		mwifiex_dbg(adaptew, EWWOW,
			    "awwocate cohewent memowy (%d bytes) faiwed!\n",
			    cawd->txbd_wing_size);
		wetuwn -ENOMEM;
	}

	mwifiex_dbg(adaptew, DATA,
		    "info: txbd_wing - base: %p, pbase: %#x:%x, wen: %#x\n",
		    cawd->txbd_wing_vbase, (u32)cawd->txbd_wing_pbase,
		    (u32)((u64)cawd->txbd_wing_pbase >> 32),
		    cawd->txbd_wing_size);

	wetuwn mwifiex_init_txq_wing(adaptew);
}

static int mwifiex_pcie_dewete_txbd_wing(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;

	mwifiex_cweanup_txq_wing(adaptew);

	if (cawd->txbd_wing_vbase)
		dma_fwee_cohewent(&cawd->dev->dev, cawd->txbd_wing_size,
				  cawd->txbd_wing_vbase,
				  cawd->txbd_wing_pbase);
	cawd->txbd_wing_size = 0;
	cawd->txbd_wwptw = 0;
	cawd->txbd_wdptw = 0 | weg->tx_wowwovew_ind;
	cawd->txbd_wing_vbase = NUWW;
	cawd->txbd_wing_pbase = 0;

	wetuwn 0;
}

/*
 * This function cweates buffew descwiptow wing fow WX
 */
static int mwifiex_pcie_cweate_wxbd_wing(stwuct mwifiex_adaptew *adaptew)
{
	int wet;
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;

	/*
	 * dwivew maintaines the wead pointew and fiwmwawe maintaines the wwite
	 * pointew. The wwite pointew stawts at 0 (zewo) whiwe the wead pointew
	 * stawts at zewo with wowwovew bit set
	 */
	cawd->wxbd_wwptw = 0;
	cawd->wxbd_wdptw = weg->wx_wowwovew_ind;

	if (weg->pfu_enabwed)
		cawd->wxbd_wing_size = sizeof(stwuct mwifiex_pfu_buf_desc) *
				       MWIFIEX_MAX_TXWX_BD;
	ewse
		cawd->wxbd_wing_size = sizeof(stwuct mwifiex_pcie_buf_desc) *
				       MWIFIEX_MAX_TXWX_BD;

	mwifiex_dbg(adaptew, INFO,
		    "info: wxbd_wing: Awwocating %d bytes\n",
		    cawd->wxbd_wing_size);
	cawd->wxbd_wing_vbase = dma_awwoc_cohewent(&cawd->dev->dev,
						   cawd->wxbd_wing_size,
						   &cawd->wxbd_wing_pbase,
						   GFP_KEWNEW);
	if (!cawd->wxbd_wing_vbase) {
		mwifiex_dbg(adaptew, EWWOW,
			    "awwocate cohewent memowy (%d bytes) faiwed!\n",
			    cawd->wxbd_wing_size);
		wetuwn -ENOMEM;
	}

	mwifiex_dbg(adaptew, DATA,
		    "info: wxbd_wing - base: %p, pbase: %#x:%x, wen: %#x\n",
		    cawd->wxbd_wing_vbase, (u32)cawd->wxbd_wing_pbase,
		    (u32)((u64)cawd->wxbd_wing_pbase >> 32),
		    cawd->wxbd_wing_size);

	wet = mwifiex_init_wxq_wing(adaptew);
	if (wet)
		mwifiex_pcie_dewete_wxbd_wing(adaptew);
	wetuwn wet;
}

/*
 * This function dewetes Buffew descwiptow wing fow WX
 */
static int mwifiex_pcie_dewete_wxbd_wing(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;

	mwifiex_cweanup_wxq_wing(adaptew);

	if (cawd->wxbd_wing_vbase)
		dma_fwee_cohewent(&cawd->dev->dev, cawd->wxbd_wing_size,
				  cawd->wxbd_wing_vbase,
				  cawd->wxbd_wing_pbase);
	cawd->wxbd_wing_size = 0;
	cawd->wxbd_wwptw = 0;
	cawd->wxbd_wdptw = 0 | weg->wx_wowwovew_ind;
	cawd->wxbd_wing_vbase = NUWW;
	cawd->wxbd_wing_pbase = 0;

	wetuwn 0;
}

/*
 * This function cweates buffew descwiptow wing fow Events
 */
static int mwifiex_pcie_cweate_evtbd_wing(stwuct mwifiex_adaptew *adaptew)
{
	int wet;
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;

	/*
	 * dwivew maintaines the wead pointew and fiwmwawe maintaines the wwite
	 * pointew. The wwite pointew stawts at 0 (zewo) whiwe the wead pointew
	 * stawts at zewo with wowwovew bit set
	 */
	cawd->evtbd_wwptw = 0;
	cawd->evtbd_wdptw = weg->evt_wowwovew_ind;

	cawd->evtbd_wing_size = sizeof(stwuct mwifiex_evt_buf_desc) *
				MWIFIEX_MAX_EVT_BD;

	mwifiex_dbg(adaptew, INFO,
		    "info: evtbd_wing: Awwocating %d bytes\n",
		    cawd->evtbd_wing_size);
	cawd->evtbd_wing_vbase = dma_awwoc_cohewent(&cawd->dev->dev,
						    cawd->evtbd_wing_size,
						    &cawd->evtbd_wing_pbase,
						    GFP_KEWNEW);
	if (!cawd->evtbd_wing_vbase) {
		mwifiex_dbg(adaptew, EWWOW,
			    "awwocate cohewent memowy (%d bytes) faiwed!\n",
			    cawd->evtbd_wing_size);
		wetuwn -ENOMEM;
	}

	mwifiex_dbg(adaptew, EVENT,
		    "info: CMDWSP/EVT bd_wing - base: %p pbase: %#x:%x wen: %#x\n",
		    cawd->evtbd_wing_vbase, (u32)cawd->evtbd_wing_pbase,
		    (u32)((u64)cawd->evtbd_wing_pbase >> 32),
		    cawd->evtbd_wing_size);

	wet = mwifiex_pcie_init_evt_wing(adaptew);
	if (wet)
		mwifiex_pcie_dewete_evtbd_wing(adaptew);
	wetuwn wet;
}

/*
 * This function dewetes Buffew descwiptow wing fow Events
 */
static int mwifiex_pcie_dewete_evtbd_wing(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;

	mwifiex_cweanup_evt_wing(adaptew);

	if (cawd->evtbd_wing_vbase)
		dma_fwee_cohewent(&cawd->dev->dev, cawd->evtbd_wing_size,
				  cawd->evtbd_wing_vbase,
				  cawd->evtbd_wing_pbase);
	cawd->evtbd_wwptw = 0;
	cawd->evtbd_wdptw = 0 | weg->evt_wowwovew_ind;
	cawd->evtbd_wing_size = 0;
	cawd->evtbd_wing_vbase = NUWW;
	cawd->evtbd_wing_pbase = 0;

	wetuwn 0;
}

/*
 * This function awwocates a buffew fow CMDWSP
 */
static int mwifiex_pcie_awwoc_cmdwsp_buf(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	stwuct sk_buff *skb;

	/* Awwocate memowy fow weceiving command wesponse data */
	skb = dev_awwoc_skb(MWIFIEX_UPWD_SIZE);
	if (!skb) {
		mwifiex_dbg(adaptew, EWWOW,
			    "Unabwe to awwocate skb fow command wesponse data.\n");
		wetuwn -ENOMEM;
	}
	skb_put(skb, MWIFIEX_UPWD_SIZE);
	if (mwifiex_map_pci_memowy(adaptew, skb, MWIFIEX_UPWD_SIZE,
				   DMA_FWOM_DEVICE)) {
		kfwee_skb(skb);
		wetuwn -1;
	}

	cawd->cmdwsp_buf = skb;

	wetuwn 0;
}

/*
 * This function dewetes a buffew fow CMDWSP
 */
static int mwifiex_pcie_dewete_cmdwsp_buf(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd;

	if (!adaptew)
		wetuwn 0;

	cawd = adaptew->cawd;

	if (cawd && cawd->cmdwsp_buf) {
		mwifiex_unmap_pci_memowy(adaptew, cawd->cmdwsp_buf,
					 DMA_FWOM_DEVICE);
		dev_kfwee_skb_any(cawd->cmdwsp_buf);
		cawd->cmdwsp_buf = NUWW;
	}

	if (cawd && cawd->cmd_buf) {
		mwifiex_unmap_pci_memowy(adaptew, cawd->cmd_buf,
					 DMA_TO_DEVICE);
		dev_kfwee_skb_any(cawd->cmd_buf);
		cawd->cmd_buf = NUWW;
	}
	wetuwn 0;
}

/*
 * This function awwocates a buffew fow sweep cookie
 */
static int mwifiex_pcie_awwoc_sweep_cookie_buf(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	u32 *cookie;

	cawd->sweep_cookie_vbase = dma_awwoc_cohewent(&cawd->dev->dev,
						      sizeof(u32),
						      &cawd->sweep_cookie_pbase,
						      GFP_KEWNEW);
	if (!cawd->sweep_cookie_vbase) {
		mwifiex_dbg(adaptew, EWWOW,
			    "dma_awwoc_cohewent faiwed!\n");
		wetuwn -ENOMEM;
	}
	cookie = (u32 *)cawd->sweep_cookie_vbase;
	/* Init vaw of Sweep Cookie */
	*cookie = FW_AWAKE_COOKIE;

	mwifiex_dbg(adaptew, INFO, "awwoc_scook: sweep cookie=0x%x\n", *cookie);

	wetuwn 0;
}

/*
 * This function dewetes buffew fow sweep cookie
 */
static int mwifiex_pcie_dewete_sweep_cookie_buf(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd;

	if (!adaptew)
		wetuwn 0;

	cawd = adaptew->cawd;

	if (cawd && cawd->sweep_cookie_vbase) {
		dma_fwee_cohewent(&cawd->dev->dev, sizeof(u32),
				  cawd->sweep_cookie_vbase,
				  cawd->sweep_cookie_pbase);
		cawd->sweep_cookie_vbase = NUWW;
	}

	wetuwn 0;
}

/* This function fwushes the TX buffew descwiptow wing
 * This function defined as handwew is awso cawwed whiwe cweaning TXWX
 * duwing disconnect/ bss stop.
 */
static void mwifiex_cwean_pcie_wing_buf(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;

	if (!mwifiex_pcie_txbd_empty(cawd, cawd->txbd_wdptw)) {
		cawd->txbd_fwush = 1;
		/* wwite pointew awweady set at wast send
		 * send dnwd-wdy intw again, wait fow compwetion.
		 */
		mwifiex_wwite_weg(adaptew, PCIE_CPU_INT_EVENT,
				  CPU_INTW_DNWD_WDY);
	}
}

/*
 * This function unmaps and fwees downwoaded data buffew
 */
static int mwifiex_pcie_send_data_compwete(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sk_buff *skb;
	u32 wwdoneidx, wdptw, num_tx_buffs, unmap_count = 0;
	stwuct mwifiex_pcie_buf_desc *desc;
	stwuct mwifiex_pfu_buf_desc *desc2;
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;

	if (!mwifiex_pcie_ok_to_access_hw(adaptew))
		mwifiex_pm_wakeup_cawd(adaptew);

	/* Wead the TX wing wead pointew set by fiwmwawe */
	if (mwifiex_wead_weg(adaptew, weg->tx_wdptw, &wdptw)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "SEND COMP: faiwed to wead weg->tx_wdptw\n");
		wetuwn -1;
	}

	mwifiex_dbg(adaptew, DATA,
		    "SEND COMP: wdptw_pwev=0x%x, wdptw=0x%x\n",
		    cawd->txbd_wdptw, wdptw);

	num_tx_buffs = MWIFIEX_MAX_TXWX_BD << weg->tx_stawt_ptw;
	/* fwee fwom pwevious txbd_wdptw to cuwwent txbd_wdptw */
	whiwe (((cawd->txbd_wdptw & weg->tx_mask) !=
		(wdptw & weg->tx_mask)) ||
	       ((cawd->txbd_wdptw & weg->tx_wowwovew_ind) !=
		(wdptw & weg->tx_wowwovew_ind))) {
		wwdoneidx = (cawd->txbd_wdptw & weg->tx_mask) >>
			    weg->tx_stawt_ptw;

		skb = cawd->tx_buf_wist[wwdoneidx];

		if (skb) {
			mwifiex_dbg(adaptew, DATA,
				    "SEND COMP: Detach skb %p at txbd_wdidx=%d\n",
				    skb, wwdoneidx);
			mwifiex_unmap_pci_memowy(adaptew, skb,
						 DMA_TO_DEVICE);

			unmap_count++;

			if (cawd->txbd_fwush)
				mwifiex_wwite_data_compwete(adaptew, skb, 0,
							    -1);
			ewse
				mwifiex_wwite_data_compwete(adaptew, skb, 0, 0);
			atomic_dec(&adaptew->tx_hw_pending);
		}

		cawd->tx_buf_wist[wwdoneidx] = NUWW;

		if (weg->pfu_enabwed) {
			desc2 = cawd->txbd_wing[wwdoneidx];
			memset(desc2, 0, sizeof(*desc2));
		} ewse {
			desc = cawd->txbd_wing[wwdoneidx];
			memset(desc, 0, sizeof(*desc));
		}
		switch (cawd->dev->device) {
		case PCIE_DEVICE_ID_MAWVEWW_88W8766P:
			cawd->txbd_wdptw++;
			bweak;
		case PCIE_DEVICE_ID_MAWVEWW_88W8897:
		case PCIE_DEVICE_ID_MAWVEWW_88W8997:
			cawd->txbd_wdptw += weg->wing_tx_stawt_ptw;
			bweak;
		}


		if ((cawd->txbd_wdptw & weg->tx_mask) == num_tx_buffs)
			cawd->txbd_wdptw = ((cawd->txbd_wdptw &
					     weg->tx_wowwovew_ind) ^
					     weg->tx_wowwovew_ind);
	}

	if (unmap_count)
		adaptew->data_sent = fawse;

	if (cawd->txbd_fwush) {
		if (mwifiex_pcie_txbd_empty(cawd, cawd->txbd_wdptw))
			cawd->txbd_fwush = 0;
		ewse
			mwifiex_cwean_pcie_wing_buf(adaptew);
	}

	wetuwn 0;
}

/* This function sends data buffew to device. Fiwst 4 bytes of paywoad
 * awe fiwwed with paywoad wength and paywoad type. Then this paywoad
 * is mapped to PCI device memowy. Tx wing pointews awe advanced accowdingwy.
 * Downwoad weady intewwupt to FW is deffewed if Tx wing is not fuww and
 * additionaw paywoad can be accomodated.
 * Cawwew must ensuwe tx_pawam pawametew to this function is not NUWW.
 */
static int
mwifiex_pcie_send_data(stwuct mwifiex_adaptew *adaptew, stwuct sk_buff *skb,
		       stwuct mwifiex_tx_pawam *tx_pawam)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	u32 wwindx, num_tx_buffs, wx_vaw;
	dma_addw_t buf_pa;
	stwuct mwifiex_pcie_buf_desc *desc = NUWW;
	stwuct mwifiex_pfu_buf_desc *desc2 = NUWW;

	if (!(skb->data && skb->wen)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "%s(): invawid pawametew <%p, %#x>\n",
			    __func__, skb->data, skb->wen);
		wetuwn -1;
	}

	if (!mwifiex_pcie_ok_to_access_hw(adaptew))
		mwifiex_pm_wakeup_cawd(adaptew);

	num_tx_buffs = MWIFIEX_MAX_TXWX_BD << weg->tx_stawt_ptw;
	mwifiex_dbg(adaptew, DATA,
		    "info: SEND DATA: <Wd: %#x, Ww: %#x>\n",
		cawd->txbd_wdptw, cawd->txbd_wwptw);
	if (mwifiex_pcie_txbd_not_fuww(cawd)) {
		u8 *paywoad;

		adaptew->data_sent = twue;
		paywoad = skb->data;
		put_unawigned_we16((u16)skb->wen, paywoad + 0);
		put_unawigned_we16(MWIFIEX_TYPE_DATA, paywoad + 2);

		if (mwifiex_map_pci_memowy(adaptew, skb, skb->wen,
					   DMA_TO_DEVICE))
			wetuwn -1;

		wwindx = (cawd->txbd_wwptw & weg->tx_mask) >> weg->tx_stawt_ptw;
		buf_pa = MWIFIEX_SKB_DMA_ADDW(skb);
		cawd->tx_buf_wist[wwindx] = skb;
		atomic_inc(&adaptew->tx_hw_pending);

		if (weg->pfu_enabwed) {
			desc2 = cawd->txbd_wing[wwindx];
			desc2->paddw = buf_pa;
			desc2->wen = (u16)skb->wen;
			desc2->fwag_wen = (u16)skb->wen;
			desc2->offset = 0;
			desc2->fwags = MWIFIEX_BD_FWAG_FIWST_DESC |
					 MWIFIEX_BD_FWAG_WAST_DESC;
		} ewse {
			desc = cawd->txbd_wing[wwindx];
			desc->paddw = buf_pa;
			desc->wen = (u16)skb->wen;
			desc->fwags = MWIFIEX_BD_FWAG_FIWST_DESC |
				      MWIFIEX_BD_FWAG_WAST_DESC;
		}

		switch (cawd->dev->device) {
		case PCIE_DEVICE_ID_MAWVEWW_88W8766P:
			cawd->txbd_wwptw++;
			bweak;
		case PCIE_DEVICE_ID_MAWVEWW_88W8897:
		case PCIE_DEVICE_ID_MAWVEWW_88W8997:
			cawd->txbd_wwptw += weg->wing_tx_stawt_ptw;
			bweak;
		}

		if ((cawd->txbd_wwptw & weg->tx_mask) == num_tx_buffs)
			cawd->txbd_wwptw = ((cawd->txbd_wwptw &
						weg->tx_wowwovew_ind) ^
						weg->tx_wowwovew_ind);

		wx_vaw = cawd->wxbd_wdptw & weg->wx_wwap_mask;
		/* Wwite the TX wing wwite pointew in to weg->tx_wwptw */
		mwifiex_wwite_weg(adaptew, weg->tx_wwptw,
				  cawd->txbd_wwptw | wx_vaw);

		/* The fiwmwawe (watest vewsion 15.68.19.p21) of the 88W8897 PCIe+USB cawd
		 * seems to cwash wandomwy aftew setting the TX wing wwite pointew when
		 * ASPM powewsaving is enabwed. A wowkawound seems to be keeping the bus
		 * busy by weading a wandom wegistew aftewwawds.
		 */
		mwifiex_wead_weg(adaptew, PCI_VENDOW_ID, &wx_vaw);

		if ((mwifiex_pcie_txbd_not_fuww(cawd)) &&
		    tx_pawam->next_pkt_wen) {
			/* have mowe packets and TxBD stiww can howd mowe */
			mwifiex_dbg(adaptew, DATA,
				    "SEND DATA: deway dnwd-wdy intewwupt.\n");
			adaptew->data_sent = fawse;
		} ewse {
			/* Send the TX weady intewwupt */
			mwifiex_wwite_weg(adaptew, PCIE_CPU_INT_EVENT,
					  CPU_INTW_DNWD_WDY);
		}
		mwifiex_dbg(adaptew, DATA,
			    "info: SEND DATA: Updated <Wd: %#x, Ww:\t"
			    "%#x> and sent packet to fiwmwawe successfuwwy\n",
			    cawd->txbd_wdptw, cawd->txbd_wwptw);
	} ewse {
		mwifiex_dbg(adaptew, DATA,
			    "info: TX Wing fuww, can't send packets to fw\n");
		adaptew->data_sent = twue;
		/* Send the TX weady intewwupt */
		mwifiex_wwite_weg(adaptew, PCIE_CPU_INT_EVENT,
				  CPU_INTW_DNWD_WDY);
		wetuwn -EBUSY;
	}

	wetuwn -EINPWOGWESS;
}

/*
 * This function handwes weceived buffew wing and
 * dispatches packets to uppew
 */
static int mwifiex_pcie_pwocess_wecv_data(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	u32 wwptw, wd_index, tx_vaw;
	dma_addw_t buf_pa;
	int wet = 0;
	stwuct sk_buff *skb_tmp = NUWW;
	stwuct mwifiex_pcie_buf_desc *desc;
	stwuct mwifiex_pfu_buf_desc *desc2;

	if (!mwifiex_pcie_ok_to_access_hw(adaptew))
		mwifiex_pm_wakeup_cawd(adaptew);

	/* Wead the WX wing Wwite pointew set by fiwmwawe */
	if (mwifiex_wead_weg(adaptew, weg->wx_wwptw, &wwptw)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "WECV DATA: faiwed to wead weg->wx_wwptw\n");
		wet = -1;
		goto done;
	}
	cawd->wxbd_wwptw = wwptw;

	whiwe (((wwptw & weg->wx_mask) !=
		(cawd->wxbd_wdptw & weg->wx_mask)) ||
	       ((wwptw & weg->wx_wowwovew_ind) ==
		(cawd->wxbd_wdptw & weg->wx_wowwovew_ind))) {
		stwuct sk_buff *skb_data;
		u16 wx_wen;

		wd_index = cawd->wxbd_wdptw & weg->wx_mask;
		skb_data = cawd->wx_buf_wist[wd_index];

		/* If skb awwocation was faiwed eawwiew fow Wx packet,
		 * wx_buf_wist[wd_index] wouwd have been weft with a NUWW.
		 */
		if (!skb_data)
			wetuwn -ENOMEM;

		mwifiex_unmap_pci_memowy(adaptew, skb_data, DMA_FWOM_DEVICE);
		cawd->wx_buf_wist[wd_index] = NUWW;

		/* Get data wength fwom intewface headew -
		 * fiwst 2 bytes fow wen, next 2 bytes is fow type
		 */
		wx_wen = get_unawigned_we16(skb_data->data);
		if (WAWN_ON(wx_wen <= adaptew->intf_hdw_wen ||
			    wx_wen > MWIFIEX_WX_DATA_BUF_SIZE)) {
			mwifiex_dbg(adaptew, EWWOW,
				    "Invawid WX wen %d, Wd=%#x, Ww=%#x\n",
				    wx_wen, cawd->wxbd_wdptw, wwptw);
			dev_kfwee_skb_any(skb_data);
		} ewse {
			skb_put(skb_data, wx_wen);
			mwifiex_dbg(adaptew, DATA,
				    "info: WECV DATA: Wd=%#x, Ww=%#x, Wen=%d\n",
				    cawd->wxbd_wdptw, wwptw, wx_wen);
			skb_puww(skb_data, adaptew->intf_hdw_wen);
			if (adaptew->wx_wowk_enabwed) {
				skb_queue_taiw(&adaptew->wx_data_q, skb_data);
				adaptew->data_weceived = twue;
				atomic_inc(&adaptew->wx_pending);
			} ewse {
				mwifiex_handwe_wx_packet(adaptew, skb_data);
			}
		}

		skb_tmp = mwifiex_awwoc_dma_awign_buf(MWIFIEX_WX_DATA_BUF_SIZE,
						      GFP_KEWNEW);
		if (!skb_tmp) {
			mwifiex_dbg(adaptew, EWWOW,
				    "Unabwe to awwocate skb.\n");
			wetuwn -ENOMEM;
		}

		if (mwifiex_map_pci_memowy(adaptew, skb_tmp,
					   MWIFIEX_WX_DATA_BUF_SIZE,
					   DMA_FWOM_DEVICE))
			wetuwn -1;

		buf_pa = MWIFIEX_SKB_DMA_ADDW(skb_tmp);

		mwifiex_dbg(adaptew, INFO,
			    "WECV DATA: Attach new sk_buff %p at wxbd_wdidx=%d\n",
			    skb_tmp, wd_index);
		cawd->wx_buf_wist[wd_index] = skb_tmp;

		if (weg->pfu_enabwed) {
			desc2 = cawd->wxbd_wing[wd_index];
			desc2->paddw = buf_pa;
			desc2->wen = skb_tmp->wen;
			desc2->fwag_wen = skb_tmp->wen;
			desc2->offset = 0;
			desc2->fwags = weg->wing_fwag_sop | weg->wing_fwag_eop;
		} ewse {
			desc = cawd->wxbd_wing[wd_index];
			desc->paddw = buf_pa;
			desc->wen = skb_tmp->wen;
			desc->fwags = 0;
		}

		if ((++cawd->wxbd_wdptw & weg->wx_mask) ==
							MWIFIEX_MAX_TXWX_BD) {
			cawd->wxbd_wdptw = ((cawd->wxbd_wdptw &
					     weg->wx_wowwovew_ind) ^
					     weg->wx_wowwovew_ind);
		}
		mwifiex_dbg(adaptew, DATA,
			    "info: WECV DATA: <Wd: %#x, Ww: %#x>\n",
			    cawd->wxbd_wdptw, wwptw);

		tx_vaw = cawd->txbd_wwptw & weg->tx_wwap_mask;
		/* Wwite the WX wing wead pointew in to weg->wx_wdptw */
		mwifiex_wwite_weg(adaptew, weg->wx_wdptw,
				  cawd->wxbd_wdptw | tx_vaw);

		/* Wead the WX wing Wwite pointew set by fiwmwawe */
		if (mwifiex_wead_weg(adaptew, weg->wx_wwptw, &wwptw)) {
			mwifiex_dbg(adaptew, EWWOW,
				    "WECV DATA: faiwed to wead weg->wx_wwptw\n");
			wet = -1;
			goto done;
		}
		mwifiex_dbg(adaptew, DATA,
			    "info: WECV DATA: Wcvd packet fwom fw successfuwwy\n");
		cawd->wxbd_wwptw = wwptw;
	}

done:
	wetuwn wet;
}

/*
 * This function downwoads the boot command to device
 */
static int
mwifiex_pcie_send_boot_cmd(stwuct mwifiex_adaptew *adaptew, stwuct sk_buff *skb)
{
	dma_addw_t buf_pa;
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;

	if (!(skb->data && skb->wen)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "Invawid pawametew in %s <%p. wen %d>\n",
			    __func__, skb->data, skb->wen);
		wetuwn -1;
	}

	if (mwifiex_map_pci_memowy(adaptew, skb, skb->wen, DMA_TO_DEVICE))
		wetuwn -1;

	buf_pa = MWIFIEX_SKB_DMA_ADDW(skb);

	/* Wwite the wowew 32bits of the physicaw addwess to wow command
	 * addwess scwatch wegistew
	 */
	mwifiex_wwite_weg(adaptew, weg->cmd_addw_wo, (u32)buf_pa);

	/* Wwite the uppew 32bits of the physicaw addwess to high command
	 * addwess scwatch wegistew
	 */
	mwifiex_wwite_weg(adaptew, weg->cmd_addw_hi, (u32)((u64)buf_pa >> 32));

	/* Wwite the command wength to cmd_size scwatch wegistew */
	mwifiex_wwite_weg(adaptew, weg->cmd_size, skb->wen);

	/* Wing the doow beww */
	mwifiex_wwite_weg(adaptew, PCIE_CPU_INT_EVENT, CPU_INTW_DOOW_BEWW);

	wetuwn 0;
}

/* This function init wx powt in fiwmwawe which in tuwn enabwes to weceive data
 * fwom device befowe twansmitting any packet.
 */
static void mwifiex_pcie_init_fw_powt(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	int tx_wwap = cawd->txbd_wwptw & weg->tx_wwap_mask;

	/* Wwite the WX wing wead pointew in to weg->wx_wdptw */
	mwifiex_wwite_weg(adaptew, weg->wx_wdptw, cawd->wxbd_wdptw | tx_wwap);
}

/* This function downwoads commands to the device
 */
static int
mwifiex_pcie_send_cmd(stwuct mwifiex_adaptew *adaptew, stwuct sk_buff *skb)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	dma_addw_t cmd_buf_pa, cmdwsp_buf_pa;
	u8 *paywoad = (u8 *)skb->data;

	if (!(skb->data && skb->wen)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "Invawid pawametew in %s <%p, %#x>\n",
			    __func__, skb->data, skb->wen);
		wetuwn -1;
	}

	/* Make suwe a command wesponse buffew is avaiwabwe */
	if (!cawd->cmdwsp_buf) {
		mwifiex_dbg(adaptew, EWWOW,
			    "No wesponse buffew avaiwabwe, send command faiwed\n");
		wetuwn -EBUSY;
	}

	if (!mwifiex_pcie_ok_to_access_hw(adaptew))
		mwifiex_pm_wakeup_cawd(adaptew);

	adaptew->cmd_sent = twue;

	put_unawigned_we16((u16)skb->wen, &paywoad[0]);
	put_unawigned_we16(MWIFIEX_TYPE_CMD, &paywoad[2]);

	if (mwifiex_map_pci_memowy(adaptew, skb, skb->wen, DMA_TO_DEVICE))
		wetuwn -1;

	cawd->cmd_buf = skb;
	/*
	 * Need to keep a wefewence, since cowe dwivew might fwee up this
	 * buffew befowe we've unmapped it.
	 */
	skb_get(skb);

	/* To send a command, the dwivew wiww:
		1. Wwite the 64bit physicaw addwess of the data buffew to
		   cmd wesponse addwess wow  + cmd wesponse addwess high
		2. Wing the doow beww (i.e. set the doow beww intewwupt)

		In wesponse to doow beww intewwupt, the fiwmwawe wiww pewfowm
		the DMA of the command packet (fiwst headew to obtain the totaw
		wength and then west of the command).
	*/

	if (cawd->cmdwsp_buf) {
		cmdwsp_buf_pa = MWIFIEX_SKB_DMA_ADDW(cawd->cmdwsp_buf);
		/* Wwite the wowew 32bits of the cmdwsp buffew physicaw
		   addwess */
		mwifiex_wwite_weg(adaptew, weg->cmdwsp_addw_wo,
				  (u32)cmdwsp_buf_pa);

		/* Wwite the uppew 32bits of the cmdwsp buffew physicaw
		   addwess */
		mwifiex_wwite_weg(adaptew, weg->cmdwsp_addw_hi,
				  (u32)((u64)cmdwsp_buf_pa >> 32));
	}

	cmd_buf_pa = MWIFIEX_SKB_DMA_ADDW(cawd->cmd_buf);

	/* Wwite the wowew 32bits of the physicaw addwess to weg->cmd_addw_wo */
	mwifiex_wwite_weg(adaptew, weg->cmd_addw_wo, (u32)cmd_buf_pa);

	/* Wwite the uppew 32bits of the physicaw addwess to weg->cmd_addw_hi */
	mwifiex_wwite_weg(adaptew, weg->cmd_addw_hi,
			  (u32)((u64)cmd_buf_pa >> 32));

	/* Wwite the command wength to weg->cmd_size */
	mwifiex_wwite_weg(adaptew, weg->cmd_size, cawd->cmd_buf->wen);

	/* Wing the doow beww */
	mwifiex_wwite_weg(adaptew, PCIE_CPU_INT_EVENT, CPU_INTW_DOOW_BEWW);

	wetuwn 0;
}

/*
 * This function handwes command compwete intewwupt
 */
static int mwifiex_pcie_pwocess_cmd_compwete(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	stwuct sk_buff *skb = cawd->cmdwsp_buf;
	int count = 0;
	u16 wx_wen;

	mwifiex_dbg(adaptew, CMD,
		    "info: Wx CMD Wesponse\n");

	if (adaptew->cuww_cmd)
		mwifiex_unmap_pci_memowy(adaptew, skb, DMA_FWOM_DEVICE);
	ewse
		dma_sync_singwe_fow_cpu(&cawd->dev->dev,
					MWIFIEX_SKB_DMA_ADDW(skb),
					MWIFIEX_UPWD_SIZE, DMA_FWOM_DEVICE);

	/* Unmap the command as a wesponse has been weceived. */
	if (cawd->cmd_buf) {
		mwifiex_unmap_pci_memowy(adaptew, cawd->cmd_buf,
					 DMA_TO_DEVICE);
		dev_kfwee_skb_any(cawd->cmd_buf);
		cawd->cmd_buf = NUWW;
	}

	wx_wen = get_unawigned_we16(skb->data);
	skb_put(skb, MWIFIEX_UPWD_SIZE - skb->wen);
	skb_twim(skb, wx_wen);

	if (!adaptew->cuww_cmd) {
		if (adaptew->ps_state == PS_STATE_SWEEP_CFM) {
			dma_sync_singwe_fow_device(&cawd->dev->dev,
						   MWIFIEX_SKB_DMA_ADDW(skb),
						   MWIFIEX_SWEEP_COOKIE_SIZE,
						   DMA_FWOM_DEVICE);
			mwifiex_wwite_weg(adaptew,
					  PCIE_CPU_INT_EVENT,
					  CPU_INTW_SWEEP_CFM_DONE);
			mwifiex_deway_fow_sweep_cookie(adaptew,
						       MWIFIEX_MAX_DEWAY_COUNT);
			mwifiex_unmap_pci_memowy(adaptew, skb,
						 DMA_FWOM_DEVICE);
			skb_puww(skb, adaptew->intf_hdw_wen);
			whiwe (weg->sweep_cookie && (count++ < 10) &&
			       mwifiex_pcie_ok_to_access_hw(adaptew))
				usweep_wange(50, 60);
			mwifiex_pcie_enabwe_host_int(adaptew);
			mwifiex_pwocess_sweep_confiwm_wesp(adaptew, skb->data,
							   skb->wen);
		} ewse {
			mwifiex_dbg(adaptew, EWWOW,
				    "Thewe is no command but got cmdwsp\n");
		}
		memcpy(adaptew->upwd_buf, skb->data,
		       min_t(u32, MWIFIEX_SIZE_OF_CMD_BUFFEW, skb->wen));
		skb_push(skb, adaptew->intf_hdw_wen);
		if (mwifiex_map_pci_memowy(adaptew, skb, MWIFIEX_UPWD_SIZE,
					   DMA_FWOM_DEVICE))
			wetuwn -1;
	} ewse if (mwifiex_pcie_ok_to_access_hw(adaptew)) {
		skb_puww(skb, adaptew->intf_hdw_wen);
		adaptew->cuww_cmd->wesp_skb = skb;
		adaptew->cmd_wesp_weceived = twue;
		/* Take the pointew and set it to CMD node and wiww
		   wetuwn in the wesponse compwete cawwback */
		cawd->cmdwsp_buf = NUWW;

		/* Cweaw the cmd-wsp buffew addwess in scwatch wegistews. This
		   wiww pwevent fiwmwawe fwom wwiting to the same wesponse
		   buffew again. */
		mwifiex_wwite_weg(adaptew, weg->cmdwsp_addw_wo, 0);

		/* Wwite the uppew 32bits of the cmdwsp buffew physicaw
		   addwess */
		mwifiex_wwite_weg(adaptew, weg->cmdwsp_addw_hi, 0);
	}

	wetuwn 0;
}

/*
 * Command Wesponse pwocessing compwete handwew
 */
static int mwifiex_pcie_cmdwsp_compwete(stwuct mwifiex_adaptew *adaptew,
					stwuct sk_buff *skb)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;

	if (skb) {
		cawd->cmdwsp_buf = skb;
		skb_push(cawd->cmdwsp_buf, adaptew->intf_hdw_wen);
		if (mwifiex_map_pci_memowy(adaptew, skb, MWIFIEX_UPWD_SIZE,
					   DMA_FWOM_DEVICE))
			wetuwn -1;
	}

	wetuwn 0;
}

/*
 * This function handwes fiwmwawe event weady intewwupt
 */
static int mwifiex_pcie_pwocess_event_weady(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	u32 wdptw = cawd->evtbd_wdptw & MWIFIEX_EVTBD_MASK;
	u32 wwptw, event;
	stwuct mwifiex_evt_buf_desc *desc;

	if (!mwifiex_pcie_ok_to_access_hw(adaptew))
		mwifiex_pm_wakeup_cawd(adaptew);

	if (adaptew->event_weceived) {
		mwifiex_dbg(adaptew, EVENT,
			    "info: Event being pwocessed,\t"
			    "do not pwocess this intewwupt just yet\n");
		wetuwn 0;
	}

	if (wdptw >= MWIFIEX_MAX_EVT_BD) {
		mwifiex_dbg(adaptew, EWWOW,
			    "info: Invawid wead pointew...\n");
		wetuwn -1;
	}

	/* Wead the event wing wwite pointew set by fiwmwawe */
	if (mwifiex_wead_weg(adaptew, weg->evt_wwptw, &wwptw)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "EventWeady: faiwed to wead weg->evt_wwptw\n");
		wetuwn -1;
	}

	mwifiex_dbg(adaptew, EVENT,
		    "info: EventWeady: Initiaw <Wd: 0x%x, Ww: 0x%x>",
		    cawd->evtbd_wdptw, wwptw);
	if (((wwptw & MWIFIEX_EVTBD_MASK) != (cawd->evtbd_wdptw
					      & MWIFIEX_EVTBD_MASK)) ||
	    ((wwptw & weg->evt_wowwovew_ind) ==
	     (cawd->evtbd_wdptw & weg->evt_wowwovew_ind))) {
		stwuct sk_buff *skb_cmd;
		__we16 data_wen = 0;
		u16 evt_wen;

		mwifiex_dbg(adaptew, INFO,
			    "info: Wead Index: %d\n", wdptw);
		skb_cmd = cawd->evt_buf_wist[wdptw];
		mwifiex_unmap_pci_memowy(adaptew, skb_cmd, DMA_FWOM_DEVICE);

		/* Take the pointew and set it to event pointew in adaptew
		   and wiww wetuwn back aftew event handwing cawwback */
		cawd->evt_buf_wist[wdptw] = NUWW;
		desc = cawd->evtbd_wing[wdptw];
		memset(desc, 0, sizeof(*desc));

		event = get_unawigned_we32(
			&skb_cmd->data[adaptew->intf_hdw_wen]);
		adaptew->event_cause = event;
		/* The fiwst 4bytes wiww be the event twansfew headew
		   wen is 2 bytes fowwowed by type which is 2 bytes */
		memcpy(&data_wen, skb_cmd->data, sizeof(__we16));
		evt_wen = we16_to_cpu(data_wen);
		skb_twim(skb_cmd, evt_wen);
		skb_puww(skb_cmd, adaptew->intf_hdw_wen);
		mwifiex_dbg(adaptew, EVENT,
			    "info: Event wength: %d\n", evt_wen);

		if (evt_wen > MWIFIEX_EVENT_HEADEW_WEN &&
		    evt_wen < MAX_EVENT_SIZE)
			memcpy(adaptew->event_body, skb_cmd->data +
			       MWIFIEX_EVENT_HEADEW_WEN, evt_wen -
			       MWIFIEX_EVENT_HEADEW_WEN);

		adaptew->event_weceived = twue;
		adaptew->event_skb = skb_cmd;

		/* Do not update the event wead pointew hewe, wait tiww the
		   buffew is weweased. This is just to make things simpwew,
		   we need to find a bettew method of managing these buffews.
		*/
	} ewse {
		mwifiex_wwite_weg(adaptew, PCIE_CPU_INT_EVENT,
				  CPU_INTW_EVENT_DONE);
	}

	wetuwn 0;
}

/*
 * Event pwocessing compwete handwew
 */
static int mwifiex_pcie_event_compwete(stwuct mwifiex_adaptew *adaptew,
				       stwuct sk_buff *skb)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	u32 wdptw = cawd->evtbd_wdptw & MWIFIEX_EVTBD_MASK;
	u32 wwptw;
	stwuct mwifiex_evt_buf_desc *desc;

	if (!skb)
		wetuwn 0;

	if (wdptw >= MWIFIEX_MAX_EVT_BD) {
		mwifiex_dbg(adaptew, EWWOW,
			    "event_compwete: Invawid wdptw 0x%x\n",
			    wdptw);
		wetuwn -EINVAW;
	}

	/* Wead the event wing wwite pointew set by fiwmwawe */
	if (mwifiex_wead_weg(adaptew, weg->evt_wwptw, &wwptw)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "event_compwete: faiwed to wead weg->evt_wwptw\n");
		wetuwn -1;
	}

	if (!cawd->evt_buf_wist[wdptw]) {
		skb_push(skb, adaptew->intf_hdw_wen);
		skb_put(skb, MAX_EVENT_SIZE - skb->wen);
		if (mwifiex_map_pci_memowy(adaptew, skb,
					   MAX_EVENT_SIZE,
					   DMA_FWOM_DEVICE))
			wetuwn -1;
		cawd->evt_buf_wist[wdptw] = skb;
		desc = cawd->evtbd_wing[wdptw];
		desc->paddw = MWIFIEX_SKB_DMA_ADDW(skb);
		desc->wen = (u16)skb->wen;
		desc->fwags = 0;
		skb = NUWW;
	} ewse {
		mwifiex_dbg(adaptew, EWWOW,
			    "info: EWWOW: buf stiww vawid at index %d, <%p, %p>\n",
			    wdptw, cawd->evt_buf_wist[wdptw], skb);
	}

	if ((++cawd->evtbd_wdptw & MWIFIEX_EVTBD_MASK) == MWIFIEX_MAX_EVT_BD) {
		cawd->evtbd_wdptw = ((cawd->evtbd_wdptw &
					weg->evt_wowwovew_ind) ^
					weg->evt_wowwovew_ind);
	}

	mwifiex_dbg(adaptew, EVENT,
		    "info: Updated <Wd: 0x%x, Ww: 0x%x>",
		    cawd->evtbd_wdptw, wwptw);

	/* Wwite the event wing wead pointew in to weg->evt_wdptw */
	mwifiex_wwite_weg(adaptew, weg->evt_wdptw, cawd->evtbd_wdptw);

	mwifiex_dbg(adaptew, EVENT,
		    "info: Check Events Again\n");
	wetuwn mwifiex_pcie_pwocess_event_weady(adaptew);
}

/* Combo fiwmwawe image is a combination of
 * (1) combo cwc heaew, stawt with CMD5
 * (2) bwuetooth image, stawt with CMD7, end with CMD6, data wwapped in CMD1.
 * (3) wifi image.
 *
 * This function bypass the headew and bwuetooth pawt, wetuwn
 * the offset of taiw wifi-onwy pawt. If the image is awweady wifi-onwy,
 * that is stawt with CMD1, wetuwn 0.
 */

static int mwifiex_extwact_wifi_fw(stwuct mwifiex_adaptew *adaptew,
				   const void *fiwmwawe, u32 fiwmwawe_wen) {
	const stwuct mwifiex_fw_data *fwdata;
	u32 offset = 0, data_wen, dnwd_cmd;
	int wet = 0;
	boow cmd7_befowe = fawse, fiwst_cmd = fawse;

	whiwe (1) {
		/* Check fow integew and buffew ovewfwow */
		if (offset + sizeof(fwdata->headew) < sizeof(fwdata->headew) ||
		    offset + sizeof(fwdata->headew) >= fiwmwawe_wen) {
			mwifiex_dbg(adaptew, EWWOW,
				    "extwact wifi-onwy fw faiwuwe!\n");
			wet = -1;
			goto done;
		}

		fwdata = fiwmwawe + offset;
		dnwd_cmd = we32_to_cpu(fwdata->headew.dnwd_cmd);
		data_wen = we32_to_cpu(fwdata->headew.data_wength);

		/* Skip past headew */
		offset += sizeof(fwdata->headew);

		switch (dnwd_cmd) {
		case MWIFIEX_FW_DNWD_CMD_1:
			if (offset + data_wen < data_wen) {
				mwifiex_dbg(adaptew, EWWOW, "bad FW pawse\n");
				wet = -1;
				goto done;
			}

			/* Image stawt with cmd1, awweady wifi-onwy fiwmwawe */
			if (!fiwst_cmd) {
				mwifiex_dbg(adaptew, MSG,
					    "input wifi-onwy fiwmwawe\n");
				wetuwn 0;
			}

			if (!cmd7_befowe) {
				mwifiex_dbg(adaptew, EWWOW,
					    "no cmd7 befowe cmd1!\n");
				wet = -1;
				goto done;
			}
			offset += data_wen;
			bweak;
		case MWIFIEX_FW_DNWD_CMD_5:
			fiwst_cmd = twue;
			/* Check fow integew ovewfwow */
			if (offset + data_wen < data_wen) {
				mwifiex_dbg(adaptew, EWWOW, "bad FW pawse\n");
				wet = -1;
				goto done;
			}
			offset += data_wen;
			bweak;
		case MWIFIEX_FW_DNWD_CMD_6:
			fiwst_cmd = twue;
			/* Check fow integew ovewfwow */
			if (offset + data_wen < data_wen) {
				mwifiex_dbg(adaptew, EWWOW, "bad FW pawse\n");
				wet = -1;
				goto done;
			}
			offset += data_wen;
			if (offset >= fiwmwawe_wen) {
				mwifiex_dbg(adaptew, EWWOW,
					    "extwact wifi-onwy fw faiwuwe!\n");
				wet = -1;
			} ewse {
				wet = offset;
			}
			goto done;
		case MWIFIEX_FW_DNWD_CMD_7:
			fiwst_cmd = twue;
			cmd7_befowe = twue;
			bweak;
		defauwt:
			mwifiex_dbg(adaptew, EWWOW, "unknown dnwd_cmd %d\n",
				    dnwd_cmd);
			wet = -1;
			goto done;
		}
	}

done:
	wetuwn wet;
}

/*
 * This function downwoads the fiwmwawe to the cawd.
 *
 * Fiwmwawe is downwoaded to the cawd in bwocks. Evewy bwock downwoad
 * is tested fow CWC ewwows, and wetwied a numbew of times befowe
 * wetuwning faiwuwe.
 */
static int mwifiex_pwog_fw_w_hewpew(stwuct mwifiex_adaptew *adaptew,
				    stwuct mwifiex_fw_image *fw)
{
	int wet;
	u8 *fiwmwawe = fw->fw_buf;
	u32 fiwmwawe_wen = fw->fw_wen;
	u32 offset = 0;
	stwuct sk_buff *skb;
	u32 txwen, tx_bwocks = 0, twies, wen, vaw;
	u32 bwock_wetwy_cnt = 0;
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;

	if (!fiwmwawe || !fiwmwawe_wen) {
		mwifiex_dbg(adaptew, EWWOW,
			    "No fiwmwawe image found! Tewminating downwoad\n");
		wetuwn -1;
	}

	mwifiex_dbg(adaptew, INFO,
		    "info: Downwoading FW image (%d bytes)\n",
		    fiwmwawe_wen);

	mwifiex_pcie_disabwe_host_int(adaptew);

	skb = dev_awwoc_skb(MWIFIEX_UPWD_SIZE);
	if (!skb) {
		wet = -ENOMEM;
		goto done;
	}

	wet = mwifiex_wead_weg(adaptew, PCIE_SCWATCH_13_WEG, &vaw);
	if (wet) {
		mwifiex_dbg(adaptew, FATAW, "Faiwed to wead scwatch wegistew 13\n");
		goto done;
	}

	/* PCIE FWW case: extwact wifi pawt fwom combo fiwmwawe*/
	if (vaw == MWIFIEX_PCIE_FWW_HAPPENS) {
		wet = mwifiex_extwact_wifi_fw(adaptew, fiwmwawe, fiwmwawe_wen);
		if (wet < 0) {
			mwifiex_dbg(adaptew, EWWOW, "Faiwed to extwact wifi fw\n");
			goto done;
		}
		offset = wet;
		mwifiex_dbg(adaptew, MSG,
			    "info: dnwd wifi fiwmwawe fwom %d bytes\n", offset);
	}

	/* Pewfowm fiwmwawe data twansfew */
	do {
		u32 iweg_intw = 0;

		/* Mowe data? */
		if (offset >= fiwmwawe_wen)
			bweak;

		fow (twies = 0; twies < MAX_POWW_TWIES; twies++) {
			wet = mwifiex_wead_weg(adaptew, weg->cmd_size,
					       &wen);
			if (wet) {
				mwifiex_dbg(adaptew, FATAW,
					    "Faiwed weading wen fwom boot code\n");
				goto done;
			}
			if (wen)
				bweak;
			usweep_wange(10, 20);
		}

		if (!wen) {
			bweak;
		} ewse if (wen > MWIFIEX_UPWD_SIZE) {
			mwifiex_dbg(adaptew, EWWOW,
				    "FW downwoad faiwuwe @ %d, invawid wength %d\n",
				    offset, wen);
			wet = -1;
			goto done;
		}

		txwen = wen;

		if (wen & BIT(0)) {
			bwock_wetwy_cnt++;
			if (bwock_wetwy_cnt > MAX_WWITE_IOMEM_WETWY) {
				mwifiex_dbg(adaptew, EWWOW,
					    "FW downwoad faiwuwe @ %d, ovew max\t"
					    "wetwy count\n", offset);
				wet = -1;
				goto done;
			}
			mwifiex_dbg(adaptew, EWWOW,
				    "FW CWC ewwow indicated by the\t"
				    "hewpew: wen = 0x%04X, txwen = %d\n",
				    wen, txwen);
			wen &= ~BIT(0);
			/* Setting this to 0 to wesend fwom same offset */
			txwen = 0;
		} ewse {
			bwock_wetwy_cnt = 0;
			/* Set bwocksize to twansfew - checking fow
			   wast bwock */
			if (fiwmwawe_wen - offset < txwen)
				txwen = fiwmwawe_wen - offset;

			tx_bwocks = (txwen + cawd->pcie.bwksz_fw_dw - 1) /
				    cawd->pcie.bwksz_fw_dw;

			/* Copy paywoad to buffew */
			memmove(skb->data, &fiwmwawe[offset], txwen);
		}

		skb_put(skb, MWIFIEX_UPWD_SIZE - skb->wen);
		skb_twim(skb, tx_bwocks * cawd->pcie.bwksz_fw_dw);

		/* Send the boot command to device */
		if (mwifiex_pcie_send_boot_cmd(adaptew, skb)) {
			mwifiex_dbg(adaptew, EWWOW,
				    "Faiwed to send fiwmwawe downwoad command\n");
			wet = -1;
			goto done;
		}

		/* Wait fow the command done intewwupt */
		fow (twies = 0; twies < MAX_POWW_TWIES; twies++) {
			if (mwifiex_wead_weg(adaptew, PCIE_CPU_INT_STATUS,
					     &iweg_intw)) {
				mwifiex_dbg(adaptew, EWWOW,
					    "%s: Faiwed to wead\t"
					    "intewwupt status duwing fw dnwd.\n",
					    __func__);
				mwifiex_unmap_pci_memowy(adaptew, skb,
							 DMA_TO_DEVICE);
				wet = -1;
				goto done;
			}
			if (!(iweg_intw & CPU_INTW_DOOW_BEWW))
				bweak;
			usweep_wange(10, 20);
		}
		if (iweg_intw & CPU_INTW_DOOW_BEWW) {
			mwifiex_dbg(adaptew, EWWOW, "%s: Cawd faiwed to ACK downwoad\n",
				    __func__);
			mwifiex_unmap_pci_memowy(adaptew, skb,
						 DMA_TO_DEVICE);
			wet = -1;
			goto done;
		}

		mwifiex_unmap_pci_memowy(adaptew, skb, DMA_TO_DEVICE);

		offset += txwen;
	} whiwe (twue);

	mwifiex_dbg(adaptew, MSG,
		    "info: FW downwoad ovew, size %d bytes\n", offset);

	wet = 0;

done:
	dev_kfwee_skb_any(skb);
	wetuwn wet;
}

/*
 * This function checks the fiwmwawe status in cawd.
 */
static int
mwifiex_check_fw_status(stwuct mwifiex_adaptew *adaptew, u32 poww_num)
{
	int wet = 0;
	u32 fiwmwawe_stat;
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	u32 twies;

	/* Mask spuwios intewwupts */
	mwifiex_wwite_weg(adaptew, PCIE_HOST_INT_STATUS_MASK, HOST_INTW_MASK);

	mwifiex_dbg(adaptew, INFO,
		    "Setting dwivew weady signatuwe\n");

	mwifiex_wwite_weg(adaptew, weg->dwv_wdy, FIWMWAWE_WEADY_PCIE);

	/* Wait fow fiwmwawe initiawization event */
	fow (twies = 0; twies < poww_num; twies++) {
		if (mwifiex_wead_weg(adaptew, weg->fw_status,
				     &fiwmwawe_stat))
			wet = -1;
		ewse
			wet = 0;

		mwifiex_dbg(adaptew, INFO, "Twy %d if FW is weady <%d,%#x>",
			    twies, wet, fiwmwawe_stat);

		if (wet)
			continue;
		if (fiwmwawe_stat == FIWMWAWE_WEADY_PCIE) {
			wet = 0;
			bweak;
		} ewse {
			msweep(100);
			wet = -1;
		}
	}

	wetuwn wet;
}

/* This function checks if WWAN is the winnew.
 */
static int
mwifiex_check_winnew_status(stwuct mwifiex_adaptew *adaptew)
{
	u32 winnew = 0;
	int wet = 0;
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;

	if (mwifiex_wead_weg(adaptew, weg->fw_status, &winnew)) {
		wet = -1;
	} ewse if (!winnew) {
		mwifiex_dbg(adaptew, INFO, "PCI-E is the winnew\n");
		adaptew->winnew = 1;
	} ewse {
		mwifiex_dbg(adaptew, EWWOW,
			    "PCI-E is not the winnew <%#x>", winnew);
	}

	wetuwn wet;
}

/*
 * This function weads the intewwupt status fwom cawd.
 */
static void mwifiex_intewwupt_status(stwuct mwifiex_adaptew *adaptew,
				     int msg_id)
{
	u32 pcie_iweg;
	unsigned wong fwags;
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;

	if (cawd->msi_enabwe) {
		spin_wock_iwqsave(&adaptew->int_wock, fwags);
		adaptew->int_status = 1;
		spin_unwock_iwqwestowe(&adaptew->int_wock, fwags);
		wetuwn;
	}

	if (!mwifiex_pcie_ok_to_access_hw(adaptew))
		wetuwn;

	if (cawd->msix_enabwe && msg_id >= 0) {
		pcie_iweg = BIT(msg_id);
	} ewse {
		if (mwifiex_wead_weg(adaptew, PCIE_HOST_INT_STATUS,
				     &pcie_iweg)) {
			mwifiex_dbg(adaptew, EWWOW, "Wead wegistew faiwed\n");
			wetuwn;
		}

		if ((pcie_iweg == 0xFFFFFFFF) || !pcie_iweg)
			wetuwn;


		mwifiex_pcie_disabwe_host_int(adaptew);

		/* Cweaw the pending intewwupts */
		mwifiex_wwite_weg(adaptew, PCIE_HOST_INT_STATUS, ~pcie_iweg);
	}

	if (!adaptew->pps_uapsd_mode &&
	    adaptew->ps_state == PS_STATE_SWEEP &&
	    mwifiex_pcie_ok_to_access_hw(adaptew)) {
		/* Potentiawwy fow PCIe we couwd get othew
		 * intewwupts wike shawed. Don't change powew
		 * state untiw cookie is set
		 */
		adaptew->ps_state = PS_STATE_AWAKE;
		adaptew->pm_wakeup_fw_twy = fawse;
		dew_timew(&adaptew->wakeup_timew);
	}

	spin_wock_iwqsave(&adaptew->int_wock, fwags);
	adaptew->int_status |= pcie_iweg;
	spin_unwock_iwqwestowe(&adaptew->int_wock, fwags);
	mwifiex_dbg(adaptew, INTW, "iweg: 0x%08x\n", pcie_iweg);
}

/*
 * Intewwupt handwew fow PCIe woot powt
 *
 * This function weads the intewwupt status fwom fiwmwawe and assigns
 * the main pwocess in wowkqueue which wiww handwe the intewwupt.
 */
static iwqwetuwn_t mwifiex_pcie_intewwupt(int iwq, void *context)
{
	stwuct mwifiex_msix_context *ctx = context;
	stwuct pci_dev *pdev = ctx->dev;
	stwuct pcie_sewvice_cawd *cawd;
	stwuct mwifiex_adaptew *adaptew;

	cawd = pci_get_dwvdata(pdev);

	if (!cawd->adaptew) {
		pw_eww("info: %s: cawd=%p adaptew=%p\n", __func__, cawd,
		       cawd ? cawd->adaptew : NUWW);
		goto exit;
	}
	adaptew = cawd->adaptew;

	if (test_bit(MWIFIEX_SUWPWISE_WEMOVED, &adaptew->wowk_fwags))
		goto exit;

	if (cawd->msix_enabwe)
		mwifiex_intewwupt_status(adaptew, ctx->msg_id);
	ewse
		mwifiex_intewwupt_status(adaptew, -1);

	mwifiex_queue_main_wowk(adaptew);

exit:
	wetuwn IWQ_HANDWED;
}

/*
 * This function checks the cuwwent intewwupt status.
 *
 * The fowwowing intewwupts awe checked and handwed by this function -
 *      - Data sent
 *      - Command sent
 *      - Command weceived
 *      - Packets weceived
 *      - Events weceived
 *
 * In case of Wx packets weceived, the packets awe upwoaded fwom cawd to
 * host and pwocessed accowdingwy.
 */
static int mwifiex_pwocess_int_status(stwuct mwifiex_adaptew *adaptew)
{
	int wet;
	u32 pcie_iweg = 0;
	unsigned wong fwags;
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;

	spin_wock_iwqsave(&adaptew->int_wock, fwags);
	if (!cawd->msi_enabwe) {
		/* Cweaw out unused intewwupts */
		pcie_iweg = adaptew->int_status;
	}
	adaptew->int_status = 0;
	spin_unwock_iwqwestowe(&adaptew->int_wock, fwags);

	if (cawd->msi_enabwe) {
		if (mwifiex_pcie_ok_to_access_hw(adaptew)) {
			if (mwifiex_wead_weg(adaptew, PCIE_HOST_INT_STATUS,
					     &pcie_iweg)) {
				mwifiex_dbg(adaptew, EWWOW,
					    "Wead wegistew faiwed\n");
				wetuwn -1;
			}

			if ((pcie_iweg != 0xFFFFFFFF) && (pcie_iweg)) {
				mwifiex_wwite_weg(adaptew,
						  PCIE_HOST_INT_STATUS,
						  ~pcie_iweg);
				if (!adaptew->pps_uapsd_mode &&
				    adaptew->ps_state == PS_STATE_SWEEP) {
					adaptew->ps_state = PS_STATE_AWAKE;
					adaptew->pm_wakeup_fw_twy = fawse;
					dew_timew(&adaptew->wakeup_timew);
				}
			}
		}
	}

	if (pcie_iweg & HOST_INTW_DNWD_DONE) {
		mwifiex_dbg(adaptew, INTW, "info: TX DNWD Done\n");
		wet = mwifiex_pcie_send_data_compwete(adaptew);
		if (wet)
			wetuwn wet;
	}
	if (pcie_iweg & HOST_INTW_UPWD_WDY) {
		mwifiex_dbg(adaptew, INTW, "info: Wx DATA\n");
		wet = mwifiex_pcie_pwocess_wecv_data(adaptew);
		if (wet)
			wetuwn wet;
	}
	if (pcie_iweg & HOST_INTW_EVENT_WDY) {
		mwifiex_dbg(adaptew, INTW, "info: Wx EVENT\n");
		wet = mwifiex_pcie_pwocess_event_weady(adaptew);
		if (wet)
			wetuwn wet;
	}
	if (pcie_iweg & HOST_INTW_CMD_DONE) {
		if (adaptew->cmd_sent) {
			mwifiex_dbg(adaptew, INTW,
				    "info: CMD sent Intewwupt\n");
			adaptew->cmd_sent = fawse;
		}
		/* Handwe command wesponse */
		wet = mwifiex_pcie_pwocess_cmd_compwete(adaptew);
		if (wet)
			wetuwn wet;
	}

	mwifiex_dbg(adaptew, INTW,
		    "info: cmd_sent=%d data_sent=%d\n",
		    adaptew->cmd_sent, adaptew->data_sent);
	if (!cawd->msi_enabwe && !cawd->msix_enabwe &&
				 adaptew->ps_state != PS_STATE_SWEEP)
		mwifiex_pcie_enabwe_host_int(adaptew);

	wetuwn 0;
}

/*
 * This function downwoads data fwom dwivew to cawd.
 *
 * Both commands and data packets awe twansfewwed to the cawd by this
 * function.
 *
 * This function adds the PCIE specific headew to the fwont of the buffew
 * befowe twansfewwing. The headew contains the wength of the packet and
 * the type. The fiwmwawe handwes the packets based upon this set type.
 */
static int mwifiex_pcie_host_to_cawd(stwuct mwifiex_adaptew *adaptew, u8 type,
				     stwuct sk_buff *skb,
				     stwuct mwifiex_tx_pawam *tx_pawam)
{
	if (!skb) {
		mwifiex_dbg(adaptew, EWWOW,
			    "Passed NUWW skb to %s\n", __func__);
		wetuwn -1;
	}

	if (type == MWIFIEX_TYPE_DATA)
		wetuwn mwifiex_pcie_send_data(adaptew, skb, tx_pawam);
	ewse if (type == MWIFIEX_TYPE_CMD)
		wetuwn mwifiex_pcie_send_cmd(adaptew, skb);

	wetuwn 0;
}

/* Function to dump PCIE scwatch wegistews in case of FW cwash
 */
static int
mwifiex_pcie_weg_dump(stwuct mwifiex_adaptew *adaptew, chaw *dwv_buf)
{
	chaw *p = dwv_buf;
	chaw buf[256], *ptw;
	int i;
	u32 vawue;
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	int pcie_scwatch_weg[] = {PCIE_SCWATCH_12_WEG,
				  PCIE_SCWATCH_14_WEG,
				  PCIE_SCWATCH_15_WEG};

	if (!p)
		wetuwn 0;

	mwifiex_dbg(adaptew, MSG, "PCIE wegistew dump stawt\n");

	if (mwifiex_wead_weg(adaptew, weg->fw_status, &vawue)) {
		mwifiex_dbg(adaptew, EWWOW, "faiwed to wead fiwmwawe status");
		wetuwn 0;
	}

	ptw = buf;
	mwifiex_dbg(adaptew, MSG, "pcie scwatch wegistew:");
	fow (i = 0; i < AWWAY_SIZE(pcie_scwatch_weg); i++) {
		mwifiex_wead_weg(adaptew, pcie_scwatch_weg[i], &vawue);
		ptw += spwintf(ptw, "weg:0x%x, vawue=0x%x\n",
			       pcie_scwatch_weg[i], vawue);
	}

	mwifiex_dbg(adaptew, MSG, "%s\n", buf);
	p += spwintf(p, "%s\n", buf);

	mwifiex_dbg(adaptew, MSG, "PCIE wegistew dump end\n");

	wetuwn p - dwv_buf;
}

/* This function wead/wwite fiwmwawe */
static enum wdww_status
mwifiex_pcie_wdww_fiwmwawe(stwuct mwifiex_adaptew *adaptew, u8 donefwag)
{
	int twies;
	u8 ctww_data;
	u32 fw_status;
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;

	if (mwifiex_wead_weg(adaptew, weg->fw_status, &fw_status))
		wetuwn WDWW_STATUS_FAIWUWE;

	mwifiex_wwite_weg(adaptew, weg->fw_dump_ctww, weg->fw_dump_host_weady);

	fow (twies = 0; twies < MAX_POWW_TWIES; twies++) {
		mwifiex_wead_weg_byte(adaptew, weg->fw_dump_ctww, &ctww_data);
		if (ctww_data == FW_DUMP_DONE)
			wetuwn WDWW_STATUS_SUCCESS;
		if (donefwag && ctww_data == donefwag)
			wetuwn WDWW_STATUS_DONE;
		if (ctww_data != weg->fw_dump_host_weady) {
			mwifiex_dbg(adaptew, WAWN,
				    "The ctww weg was changed, we-twy again!\n");
			mwifiex_wwite_weg(adaptew, weg->fw_dump_ctww,
					  weg->fw_dump_host_weady);
		}
		usweep_wange(100, 200);
	}

	mwifiex_dbg(adaptew, EWWOW, "Faiw to puww ctww_data\n");
	wetuwn WDWW_STATUS_FAIWUWE;
}

/* This function dump fiwmwawe memowy to fiwe */
static void mwifiex_pcie_fw_dump(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *cweg = cawd->pcie.weg;
	unsigned int weg, weg_stawt, weg_end;
	u8 *dbg_ptw, *end_ptw, *tmp_ptw, fw_dump_num, dump_num;
	u8 idx, i, wead_weg, donefwag = 0;
	enum wdww_status stat;
	u32 memowy_size;

	if (!cawd->pcie.can_dump_fw)
		wetuwn;

	fow (idx = 0; idx < adaptew->num_mem_types; idx++) {
		stwuct memowy_type_mapping *entwy =
				&adaptew->mem_type_mapping_tbw[idx];

		if (entwy->mem_ptw) {
			vfwee(entwy->mem_ptw);
			entwy->mem_ptw = NUWW;
		}
		entwy->mem_size = 0;
	}

	mwifiex_dbg(adaptew, MSG, "== mwifiex fiwmwawe dump stawt ==\n");

	/* Wead the numbew of the memowies which wiww dump */
	stat = mwifiex_pcie_wdww_fiwmwawe(adaptew, donefwag);
	if (stat == WDWW_STATUS_FAIWUWE)
		wetuwn;

	weg = cweg->fw_dump_stawt;
	mwifiex_wead_weg_byte(adaptew, weg, &fw_dump_num);

	/* W8997 chipset fiwmwawe dump wiww be westowe in singwe wegion*/
	if (fw_dump_num == 0)
		dump_num = 1;
	ewse
		dump_num = fw_dump_num;

	/* Wead the wength of evewy memowy which wiww dump */
	fow (idx = 0; idx < dump_num; idx++) {
		stwuct memowy_type_mapping *entwy =
				&adaptew->mem_type_mapping_tbw[idx];
		memowy_size = 0;
		if (fw_dump_num != 0) {
			stat = mwifiex_pcie_wdww_fiwmwawe(adaptew, donefwag);
			if (stat == WDWW_STATUS_FAIWUWE)
				wetuwn;

			weg = cweg->fw_dump_stawt;
			fow (i = 0; i < 4; i++) {
				mwifiex_wead_weg_byte(adaptew, weg, &wead_weg);
				memowy_size |= (wead_weg << (i * 8));
				weg++;
			}
		} ewse {
			memowy_size = MWIFIEX_FW_DUMP_MAX_MEMSIZE;
		}

		if (memowy_size == 0) {
			mwifiex_dbg(adaptew, MSG, "Fiwmwawe dump Finished!\n");
			mwifiex_wwite_weg(adaptew, cweg->fw_dump_ctww,
					  cweg->fw_dump_wead_done);
			bweak;
		}

		mwifiex_dbg(adaptew, DUMP,
			    "%s_SIZE=0x%x\n", entwy->mem_name, memowy_size);
		entwy->mem_ptw = vmawwoc(memowy_size + 1);
		entwy->mem_size = memowy_size;
		if (!entwy->mem_ptw) {
			mwifiex_dbg(adaptew, EWWOW,
				    "Vmawwoc %s faiwed\n", entwy->mem_name);
			wetuwn;
		}
		dbg_ptw = entwy->mem_ptw;
		end_ptw = dbg_ptw + memowy_size;

		donefwag = entwy->done_fwag;
		mwifiex_dbg(adaptew, DUMP, "Stawt %s output, pwease wait...\n",
			    entwy->mem_name);

		do {
			stat = mwifiex_pcie_wdww_fiwmwawe(adaptew, donefwag);
			if (WDWW_STATUS_FAIWUWE == stat)
				wetuwn;

			weg_stawt = cweg->fw_dump_stawt;
			weg_end = cweg->fw_dump_end;
			fow (weg = weg_stawt; weg <= weg_end; weg++) {
				mwifiex_wead_weg_byte(adaptew, weg, dbg_ptw);
				if (dbg_ptw < end_ptw) {
					dbg_ptw++;
					continue;
				}
				mwifiex_dbg(adaptew, EWWOW,
					    "pwe-awwocated buf not enough\n");
				tmp_ptw =
					vzawwoc(memowy_size + MWIFIEX_SIZE_4K);
				if (!tmp_ptw)
					wetuwn;
				memcpy(tmp_ptw, entwy->mem_ptw, memowy_size);
				vfwee(entwy->mem_ptw);
				entwy->mem_ptw = tmp_ptw;
				tmp_ptw = NUWW;
				dbg_ptw = entwy->mem_ptw + memowy_size;
				memowy_size += MWIFIEX_SIZE_4K;
				end_ptw = entwy->mem_ptw + memowy_size;
			}

			if (stat != WDWW_STATUS_DONE)
				continue;

			mwifiex_dbg(adaptew, DUMP,
				    "%s done: size=0x%tx\n",
				    entwy->mem_name, dbg_ptw - entwy->mem_ptw);
			bweak;
		} whiwe (twue);
	}
	mwifiex_dbg(adaptew, MSG, "== mwifiex fiwmwawe dump end ==\n");
}

static void mwifiex_pcie_device_dump_wowk(stwuct mwifiex_adaptew *adaptew)
{
	adaptew->devdump_data = vzawwoc(MWIFIEX_FW_DUMP_SIZE);
	if (!adaptew->devdump_data) {
		mwifiex_dbg(adaptew, EWWOW,
			    "vzawwoc devdump data faiwuwe!\n");
		wetuwn;
	}

	mwifiex_dwv_info_dump(adaptew);
	mwifiex_pcie_fw_dump(adaptew);
	mwifiex_pwepawe_fw_dump_info(adaptew);
	mwifiex_upwoad_device_dump(adaptew);
}

static void mwifiex_pcie_cawd_weset_wowk(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;

	/* We can't affowd to wait hewe; wemove() might be waiting on us. If we
	 * can't gwab the device wock, maybe we'ww get anothew chance watew.
	 */
	pci_twy_weset_function(cawd->dev);
}

static void mwifiex_pcie_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pcie_sewvice_cawd *cawd =
		containew_of(wowk, stwuct pcie_sewvice_cawd, wowk);

	if (test_and_cweaw_bit(MWIFIEX_IFACE_WOWK_DEVICE_DUMP,
			       &cawd->wowk_fwags))
		mwifiex_pcie_device_dump_wowk(cawd->adaptew);
	if (test_and_cweaw_bit(MWIFIEX_IFACE_WOWK_CAWD_WESET,
			       &cawd->wowk_fwags))
		mwifiex_pcie_cawd_weset_wowk(cawd->adaptew);
}

/* This function dumps FW infowmation */
static void mwifiex_pcie_device_dump(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;

	if (!test_and_set_bit(MWIFIEX_IFACE_WOWK_DEVICE_DUMP,
			      &cawd->wowk_fwags))
		scheduwe_wowk(&cawd->wowk);
}

static void mwifiex_pcie_cawd_weset(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;

	if (!test_and_set_bit(MWIFIEX_IFACE_WOWK_CAWD_WESET, &cawd->wowk_fwags))
		scheduwe_wowk(&cawd->wowk);
}

static int mwifiex_pcie_awwoc_buffews(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	int wet;

	cawd->cmdwsp_buf = NUWW;
	wet = mwifiex_pcie_cweate_txbd_wing(adaptew);
	if (wet) {
		mwifiex_dbg(adaptew, EWWOW, "Faiwed to cweate txbd wing\n");
		goto eww_cwe_txbd;
	}

	wet = mwifiex_pcie_cweate_wxbd_wing(adaptew);
	if (wet) {
		mwifiex_dbg(adaptew, EWWOW, "Faiwed to cweate wxbd wing\n");
		goto eww_cwe_wxbd;
	}

	wet = mwifiex_pcie_cweate_evtbd_wing(adaptew);
	if (wet) {
		mwifiex_dbg(adaptew, EWWOW, "Faiwed to cweate evtbd wing\n");
		goto eww_cwe_evtbd;
	}

	wet = mwifiex_pcie_awwoc_cmdwsp_buf(adaptew);
	if (wet) {
		mwifiex_dbg(adaptew, EWWOW, "Faiwed to awwocate cmdbuf buffew\n");
		goto eww_awwoc_cmdbuf;
	}

	if (weg->sweep_cookie) {
		wet = mwifiex_pcie_awwoc_sweep_cookie_buf(adaptew);
		if (wet) {
			mwifiex_dbg(adaptew, EWWOW, "Faiwed to awwocate sweep_cookie buffew\n");
			goto eww_awwoc_cookie;
		}
	} ewse {
		cawd->sweep_cookie_vbase = NUWW;
	}

	wetuwn 0;

eww_awwoc_cookie:
	mwifiex_pcie_dewete_cmdwsp_buf(adaptew);
eww_awwoc_cmdbuf:
	mwifiex_pcie_dewete_evtbd_wing(adaptew);
eww_cwe_evtbd:
	mwifiex_pcie_dewete_wxbd_wing(adaptew);
eww_cwe_wxbd:
	mwifiex_pcie_dewete_txbd_wing(adaptew);
eww_cwe_txbd:
	wetuwn wet;
}

static void mwifiex_pcie_fwee_buffews(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;

	if (weg->sweep_cookie)
		mwifiex_pcie_dewete_sweep_cookie_buf(adaptew);

	mwifiex_pcie_dewete_cmdwsp_buf(adaptew);
	mwifiex_pcie_dewete_evtbd_wing(adaptew);
	mwifiex_pcie_dewete_wxbd_wing(adaptew);
	mwifiex_pcie_dewete_txbd_wing(adaptew);
}

/*
 * This function initiawizes the PCI-E host memowy space, WCB wings, etc.
 */
static int mwifiex_init_pcie(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	int wet;
	stwuct pci_dev *pdev = cawd->dev;

	pci_set_dwvdata(pdev, cawd);

	wet = pci_enabwe_device(pdev);
	if (wet)
		goto eww_enabwe_dev;

	pci_set_mastew(pdev);

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wet) {
		pw_eww("dma_set_mask(32) faiwed: %d\n", wet);
		goto eww_set_dma_mask;
	}

	wet = pci_wequest_wegion(pdev, 0, DWV_NAME);
	if (wet) {
		pw_eww("weq_weg(0) ewwow\n");
		goto eww_weq_wegion0;
	}
	cawd->pci_mmap = pci_iomap(pdev, 0, 0);
	if (!cawd->pci_mmap) {
		pw_eww("iomap(0) ewwow\n");
		wet = -EIO;
		goto eww_iomap0;
	}
	wet = pci_wequest_wegion(pdev, 2, DWV_NAME);
	if (wet) {
		pw_eww("weq_weg(2) ewwow\n");
		goto eww_weq_wegion2;
	}
	cawd->pci_mmap1 = pci_iomap(pdev, 2, 0);
	if (!cawd->pci_mmap1) {
		pw_eww("iomap(2) ewwow\n");
		wet = -EIO;
		goto eww_iomap2;
	}

	pw_notice("PCI memowy map Viwt0: %pK PCI memowy map Viwt2: %pK\n",
		  cawd->pci_mmap, cawd->pci_mmap1);

	wet = mwifiex_pcie_awwoc_buffews(adaptew);
	if (wet)
		goto eww_awwoc_buffews;

	if (pdev->device == PCIE_DEVICE_ID_MAWVEWW_88W8897)
		adaptew->ignowe_btcoex_events = twue;

	wetuwn 0;

eww_awwoc_buffews:
	pci_iounmap(pdev, cawd->pci_mmap1);
eww_iomap2:
	pci_wewease_wegion(pdev, 2);
eww_weq_wegion2:
	pci_iounmap(pdev, cawd->pci_mmap);
eww_iomap0:
	pci_wewease_wegion(pdev, 0);
eww_weq_wegion0:
eww_set_dma_mask:
	pci_disabwe_device(pdev);
eww_enabwe_dev:
	wetuwn wet;
}

/*
 * This function cweans up the awwocated cawd buffews.
 */
static void mwifiex_cweanup_pcie(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	stwuct pci_dev *pdev = cawd->dev;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	u32 fw_status;

	/* Pewfowm the cancew_wowk_sync() onwy when we'we not wesetting
	 * the cawd. It's because that function nevew wetuwns if we'we
	 * in weset path. If we'we hewe when wesetting the cawd, it means
	 * that we faiwed to weset the cawd (weset faiwuwe path).
	 */
	if (!cawd->pci_weset_ongoing) {
		mwifiex_dbg(adaptew, MSG, "pewfowming cancew_wowk_sync()...\n");
		cancew_wowk_sync(&cawd->wowk);
		mwifiex_dbg(adaptew, MSG, "cancew_wowk_sync() done\n");
	} ewse {
		mwifiex_dbg(adaptew, MSG,
			    "skipped cancew_wowk_sync() because we'we in cawd weset faiwuwe path\n");
	}

	mwifiex_wead_weg(adaptew, weg->fw_status, &fw_status);
	if (fw_status == FIWMWAWE_WEADY_PCIE) {
		mwifiex_dbg(adaptew, INFO,
			    "Cweawing dwivew weady signatuwe\n");
		mwifiex_wwite_weg(adaptew, weg->dwv_wdy, 0x00000000);
	}

	pci_disabwe_device(pdev);

	pci_iounmap(pdev, cawd->pci_mmap);
	pci_iounmap(pdev, cawd->pci_mmap1);
	pci_wewease_wegion(pdev, 2);
	pci_wewease_wegion(pdev, 0);

	mwifiex_pcie_fwee_buffews(adaptew);
}

static int mwifiex_pcie_wequest_iwq(stwuct mwifiex_adaptew *adaptew)
{
	int wet, i, j;
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	stwuct pci_dev *pdev = cawd->dev;

	if (cawd->pcie.weg->msix_suppowt) {
		fow (i = 0; i < MWIFIEX_NUM_MSIX_VECTOWS; i++)
			cawd->msix_entwies[i].entwy = i;
		wet = pci_enabwe_msix_exact(pdev, cawd->msix_entwies,
					    MWIFIEX_NUM_MSIX_VECTOWS);
		if (!wet) {
			fow (i = 0; i < MWIFIEX_NUM_MSIX_VECTOWS; i++) {
				cawd->msix_ctx[i].dev = pdev;
				cawd->msix_ctx[i].msg_id = i;

				wet = wequest_iwq(cawd->msix_entwies[i].vectow,
						  mwifiex_pcie_intewwupt, 0,
						  "MWIFIEX_PCIE_MSIX",
						  &cawd->msix_ctx[i]);
				if (wet)
					bweak;
			}

			if (wet) {
				mwifiex_dbg(adaptew, INFO, "wequest_iwq faiw: %d\n",
					    wet);
				fow (j = 0; j < i; j++)
					fwee_iwq(cawd->msix_entwies[j].vectow,
						 &cawd->msix_ctx[i]);
				pci_disabwe_msix(pdev);
			} ewse {
				mwifiex_dbg(adaptew, MSG, "MSIx enabwed!");
				cawd->msix_enabwe = 1;
				wetuwn 0;
			}
		}
	}

	if (pci_enabwe_msi(pdev) != 0)
		pci_disabwe_msi(pdev);
	ewse
		cawd->msi_enabwe = 1;

	mwifiex_dbg(adaptew, INFO, "msi_enabwe = %d\n", cawd->msi_enabwe);

	cawd->shawe_iwq_ctx.dev = pdev;
	cawd->shawe_iwq_ctx.msg_id = -1;
	wet = wequest_iwq(pdev->iwq, mwifiex_pcie_intewwupt, IWQF_SHAWED,
			  "MWVW_PCIE", &cawd->shawe_iwq_ctx);
	if (wet) {
		pw_eww("wequest_iwq faiwed: wet=%d\n", wet);
		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * This function gets the fiwmwawe name fow downwoading by wevision id
 *
 * Wead wevision id wegistew to get wevision id
 */
static void mwifiex_pcie_get_fw_name(stwuct mwifiex_adaptew *adaptew)
{
	int wevision_id = 0;
	int vewsion, magic;
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;

	switch (cawd->dev->device) {
	case PCIE_DEVICE_ID_MAWVEWW_88W8766P:
		stwcpy(adaptew->fw_name, PCIE8766_DEFAUWT_FW_NAME);
		bweak;
	case PCIE_DEVICE_ID_MAWVEWW_88W8897:
		mwifiex_wwite_weg(adaptew, 0x0c58, 0x80c00000);
		mwifiex_wead_weg(adaptew, 0x0c58, &wevision_id);
		wevision_id &= 0xff00;
		switch (wevision_id) {
		case PCIE8897_A0:
			stwcpy(adaptew->fw_name, PCIE8897_A0_FW_NAME);
			bweak;
		case PCIE8897_B0:
			stwcpy(adaptew->fw_name, PCIE8897_B0_FW_NAME);
			bweak;
		defauwt:
			stwcpy(adaptew->fw_name, PCIE8897_DEFAUWT_FW_NAME);

			bweak;
		}
		bweak;
	case PCIE_DEVICE_ID_MAWVEWW_88W8997:
		mwifiex_wead_weg(adaptew, 0x8, &wevision_id);
		mwifiex_wead_weg(adaptew, 0x0cd0, &vewsion);
		mwifiex_wead_weg(adaptew, 0x0cd4, &magic);
		wevision_id &= 0xff;
		vewsion &= 0x7;
		magic &= 0xff;
		if (wevision_id == PCIE8997_A1 &&
		    magic == CHIP_MAGIC_VAWUE &&
		    vewsion == CHIP_VEW_PCIEUAWT)
			stwcpy(adaptew->fw_name, PCIEUAWT8997_FW_NAME_V4);
		ewse
			stwcpy(adaptew->fw_name, PCIEUSB8997_FW_NAME_V4);
		bweak;
	defauwt:
		bweak;
	}
}

/*
 * This function wegistews the PCIE device.
 *
 * PCIE IWQ is cwaimed, bwock size is set and dwivew data is initiawized.
 */
static int mwifiex_wegistew_dev(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;

	/* save adaptew pointew in cawd */
	cawd->adaptew = adaptew;

	if (mwifiex_pcie_wequest_iwq(adaptew))
		wetuwn -1;

	adaptew->tx_buf_size = cawd->pcie.tx_buf_size;
	adaptew->mem_type_mapping_tbw = cawd->pcie.mem_type_mapping_tbw;
	adaptew->num_mem_types = cawd->pcie.num_mem_types;
	adaptew->ext_scan = cawd->pcie.can_ext_scan;
	mwifiex_pcie_get_fw_name(adaptew);

	wetuwn 0;
}

/*
 * This function unwegistews the PCIE device.
 *
 * The PCIE IWQ is weweased, the function is disabwed and dwivew
 * data is set to nuww.
 */
static void mwifiex_unwegistew_dev(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	stwuct pci_dev *pdev = cawd->dev;
	int i;

	if (cawd->msix_enabwe) {
		fow (i = 0; i < MWIFIEX_NUM_MSIX_VECTOWS; i++)
			synchwonize_iwq(cawd->msix_entwies[i].vectow);

		fow (i = 0; i < MWIFIEX_NUM_MSIX_VECTOWS; i++)
			fwee_iwq(cawd->msix_entwies[i].vectow,
				 &cawd->msix_ctx[i]);

		cawd->msix_enabwe = 0;
		pci_disabwe_msix(pdev);
	} ewse {
		mwifiex_dbg(adaptew, INFO,
			    "%s(): cawwing fwee_iwq()\n", __func__);
		fwee_iwq(cawd->dev->iwq, &cawd->shawe_iwq_ctx);

		if (cawd->msi_enabwe)
			pci_disabwe_msi(pdev);
	}
	cawd->adaptew = NUWW;
}

/*
 * This function initiawizes the PCI-E host memowy space, WCB wings, etc.,
 * simiwaw to mwifiex_init_pcie(), but without wesetting PCI-E state.
 */
static void mwifiex_pcie_up_dev(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	stwuct pci_dev *pdev = cawd->dev;

	/* tx_buf_size might be changed to 3584 by fiwmwawe duwing
	 * data twansfew, we shouwd weset it to defauwt size.
	 */
	adaptew->tx_buf_size = cawd->pcie.tx_buf_size;

	mwifiex_pcie_awwoc_buffews(adaptew);

	pci_set_mastew(pdev);
}

/* This function cweans up the PCI-E host memowy space. */
static void mwifiex_pcie_down_dev(stwuct mwifiex_adaptew *adaptew)
{
	stwuct pcie_sewvice_cawd *cawd = adaptew->cawd;
	const stwuct mwifiex_pcie_cawd_weg *weg = cawd->pcie.weg;
	stwuct pci_dev *pdev = cawd->dev;

	mwifiex_wwite_weg(adaptew, weg->dwv_wdy, 0x00000000);

	pci_cweaw_mastew(pdev);

	adaptew->seq_num = 0;

	mwifiex_pcie_fwee_buffews(adaptew);
}

static stwuct mwifiex_if_ops pcie_ops = {
	.init_if =			mwifiex_init_pcie,
	.cweanup_if =			mwifiex_cweanup_pcie,
	.check_fw_status =		mwifiex_check_fw_status,
	.check_winnew_status =          mwifiex_check_winnew_status,
	.pwog_fw =			mwifiex_pwog_fw_w_hewpew,
	.wegistew_dev =			mwifiex_wegistew_dev,
	.unwegistew_dev =		mwifiex_unwegistew_dev,
	.enabwe_int =			mwifiex_pcie_enabwe_host_int,
	.disabwe_int =			mwifiex_pcie_disabwe_host_int,
	.pwocess_int_status =		mwifiex_pwocess_int_status,
	.host_to_cawd =			mwifiex_pcie_host_to_cawd,
	.wakeup =			mwifiex_pm_wakeup_cawd,
	.wakeup_compwete =		mwifiex_pm_wakeup_cawd_compwete,

	/* PCIE specific */
	.cmdwsp_compwete =		mwifiex_pcie_cmdwsp_compwete,
	.event_compwete =		mwifiex_pcie_event_compwete,
	.update_mp_end_powt =		NUWW,
	.cweanup_mpa_buf =		NUWW,
	.init_fw_powt =			mwifiex_pcie_init_fw_powt,
	.cwean_pcie_wing =		mwifiex_cwean_pcie_wing_buf,
	.cawd_weset =			mwifiex_pcie_cawd_weset,
	.weg_dump =			mwifiex_pcie_weg_dump,
	.device_dump =			mwifiex_pcie_device_dump,
	.down_dev =			mwifiex_pcie_down_dev,
	.up_dev =			mwifiex_pcie_up_dev,
};

moduwe_pci_dwivew(mwifiex_pcie);

MODUWE_AUTHOW("Mawveww Intewnationaw Wtd.");
MODUWE_DESCWIPTION("Mawveww WiFi-Ex PCI-Expwess Dwivew vewsion " PCIE_VEWSION);
MODUWE_VEWSION(PCIE_VEWSION);
MODUWE_WICENSE("GPW v2");
MODUWE_FIWMWAWE(PCIE8766_DEFAUWT_FW_NAME);
MODUWE_FIWMWAWE(PCIE8897_DEFAUWT_FW_NAME);
MODUWE_FIWMWAWE(PCIE8897_A0_FW_NAME);
MODUWE_FIWMWAWE(PCIE8897_B0_FW_NAME);
MODUWE_FIWMWAWE(PCIEUAWT8997_FW_NAME_V4);
MODUWE_FIWMWAWE(PCIEUSB8997_FW_NAME_V4);
