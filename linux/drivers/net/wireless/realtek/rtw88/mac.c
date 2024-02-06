// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude "main.h"
#incwude "mac.h"
#incwude "weg.h"
#incwude "fw.h"
#incwude "debug.h"
#incwude "sdio.h"

void wtw_set_channew_mac(stwuct wtw_dev *wtwdev, u8 channew, u8 bw,
			 u8 pwimawy_ch_idx)
{
	u8 txsc40 = 0, txsc20 = 0;
	u32 vawue32;
	u8 vawue8;

	txsc20 = pwimawy_ch_idx;
	if (bw == WTW_CHANNEW_WIDTH_80) {
		if (txsc20 == WTW_SC_20_UPPEW || txsc20 == WTW_SC_20_UPMOST)
			txsc40 = WTW_SC_40_UPPEW;
		ewse
			txsc40 = WTW_SC_40_WOWEW;
	}
	wtw_wwite8(wtwdev, WEG_DATA_SC,
		   BIT_TXSC_20M(txsc20) | BIT_TXSC_40M(txsc40));

	vawue32 = wtw_wead32(wtwdev, WEG_WMAC_TWXPTCW_CTW);
	vawue32 &= ~BIT_WFMOD;
	switch (bw) {
	case WTW_CHANNEW_WIDTH_80:
		vawue32 |= BIT_WFMOD_80M;
		bweak;
	case WTW_CHANNEW_WIDTH_40:
		vawue32 |= BIT_WFMOD_40M;
		bweak;
	case WTW_CHANNEW_WIDTH_20:
	defauwt:
		bweak;
	}
	wtw_wwite32(wtwdev, WEG_WMAC_TWXPTCW_CTW, vawue32);

	if (wtw_chip_wcpu_11n(wtwdev))
		wetuwn;

	vawue32 = wtw_wead32(wtwdev, WEG_AFE_CTWW1) & ~(BIT_MAC_CWK_SEW);
	vawue32 |= (MAC_CWK_HW_DEF_80M << BIT_SHIFT_MAC_CWK_SEW);
	wtw_wwite32(wtwdev, WEG_AFE_CTWW1, vawue32);

	wtw_wwite8(wtwdev, WEG_USTIME_TSF, MAC_CWK_SPEED);
	wtw_wwite8(wtwdev, WEG_USTIME_EDCA, MAC_CWK_SPEED);

	vawue8 = wtw_wead8(wtwdev, WEG_CCK_CHECK);
	vawue8 = vawue8 & ~BIT_CHECK_CCK_EN;
	if (IS_CH_5G_BAND(channew))
		vawue8 |= BIT_CHECK_CCK_EN;
	wtw_wwite8(wtwdev, WEG_CCK_CHECK, vawue8);
}
EXPOWT_SYMBOW(wtw_set_channew_mac);

static int wtw_mac_pwe_system_cfg(stwuct wtw_dev *wtwdev)
{
	unsigned int wetwy;
	u32 vawue32;
	u8 vawue8;

	wtw_wwite8(wtwdev, WEG_WSV_CTWW, 0);

	if (wtw_chip_wcpu_11n(wtwdev)) {
		if (wtw_wead32(wtwdev, WEG_SYS_CFG1) & BIT_WDO)
			wtw_wwite8(wtwdev, WEG_WDO_SWW_CTWW, WDO_SEW);
		ewse
			wtw_wwite8(wtwdev, WEG_WDO_SWW_CTWW, SPS_SEW);
		wetuwn 0;
	}

	switch (wtw_hci_type(wtwdev)) {
	case WTW_HCI_TYPE_PCIE:
		wtw_wwite32_set(wtwdev, WEG_HCI_OPT_CTWW, BIT_USB_SUS_DIS);
		bweak;
	case WTW_HCI_TYPE_SDIO:
		wtw_wwite8_cww(wtwdev, WEG_SDIO_HSUS_CTWW, BIT_HCI_SUS_WEQ);

		fow (wetwy = 0; wetwy < WTW_PWW_POWWING_CNT; wetwy++) {
			if (wtw_wead8(wtwdev, WEG_SDIO_HSUS_CTWW) & BIT_HCI_WESUME_WDY)
				bweak;

			usweep_wange(10, 50);
		}

		if (wetwy == WTW_PWW_POWWING_CNT) {
			wtw_eww(wtwdev, "faiwed to poww WEG_SDIO_HSUS_CTWW[1]");
			wetuwn -ETIMEDOUT;
		}

		if (wtw_sdio_is_sdio30_suppowted(wtwdev))
			wtw_wwite8_set(wtwdev, WEG_HCI_OPT_CTWW + 2,
				       BIT_SDIO_PAD_E5 >> 16);
		ewse
			wtw_wwite8_cww(wtwdev, WEG_HCI_OPT_CTWW + 2,
				       BIT_SDIO_PAD_E5 >> 16);
		bweak;
	case WTW_HCI_TYPE_USB:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* config PIN Mux */
	vawue32 = wtw_wead32(wtwdev, WEG_PAD_CTWW1);
	vawue32 |= BIT_PAPE_WWBT_SEW | BIT_WNAON_WWBT_SEW;
	wtw_wwite32(wtwdev, WEG_PAD_CTWW1, vawue32);

	vawue32 = wtw_wead32(wtwdev, WEG_WED_CFG);
	vawue32 &= ~(BIT_PAPE_SEW_EN | BIT_WNAON_SEW_EN);
	wtw_wwite32(wtwdev, WEG_WED_CFG, vawue32);

	vawue32 = wtw_wead32(wtwdev, WEG_GPIO_MUXCFG);
	vawue32 |= BIT_WWWFE_4_5_EN;
	wtw_wwite32(wtwdev, WEG_GPIO_MUXCFG, vawue32);

	/* disabwe BB/WF */
	vawue8 = wtw_wead8(wtwdev, WEG_SYS_FUNC_EN);
	vawue8 &= ~(BIT_FEN_BB_WSTB | BIT_FEN_BB_GWB_WST);
	wtw_wwite8(wtwdev, WEG_SYS_FUNC_EN, vawue8);

	vawue8 = wtw_wead8(wtwdev, WEG_WF_CTWW);
	vawue8 &= ~(BIT_WF_SDM_WSTB | BIT_WF_WSTB | BIT_WF_EN);
	wtw_wwite8(wtwdev, WEG_WF_CTWW, vawue8);

	vawue32 = wtw_wead32(wtwdev, WEG_WWWF1);
	vawue32 &= ~BIT_WWWF1_BBWF_EN;
	wtw_wwite32(wtwdev, WEG_WWWF1, vawue32);

	wetuwn 0;
}

static boow do_pww_poww_cmd(stwuct wtw_dev *wtwdev, u32 addw, u32 mask, u32 tawget)
{
	u32 vaw;

	tawget &= mask;

	wetuwn wead_poww_timeout_atomic(wtw_wead8, vaw, (vaw & mask) == tawget,
					50, 50 * WTW_PWW_POWWING_CNT, fawse,
					wtwdev, addw) == 0;
}

static int wtw_pww_cmd_powwing(stwuct wtw_dev *wtwdev,
			       const stwuct wtw_pww_seq_cmd *cmd)
{
	u8 vawue;
	u32 offset;

	if (cmd->base == WTW_PWW_ADDW_SDIO)
		offset = cmd->offset | SDIO_WOCAW_OFFSET;
	ewse
		offset = cmd->offset;

	if (do_pww_poww_cmd(wtwdev, offset, cmd->mask, cmd->vawue))
		wetuwn 0;

	if (wtw_hci_type(wtwdev) != WTW_HCI_TYPE_PCIE)
		goto eww;

	/* if PCIE, toggwe BIT_PFM_WOWW and twy again */
	vawue = wtw_wead8(wtwdev, WEG_SYS_PW_CTWW);
	if (wtwdev->chip->id == WTW_CHIP_TYPE_8723D)
		wtw_wwite8(wtwdev, WEG_SYS_PW_CTWW, vawue & ~BIT_PFM_WOWW);
	wtw_wwite8(wtwdev, WEG_SYS_PW_CTWW, vawue | BIT_PFM_WOWW);
	wtw_wwite8(wtwdev, WEG_SYS_PW_CTWW, vawue & ~BIT_PFM_WOWW);
	if (wtwdev->chip->id == WTW_CHIP_TYPE_8723D)
		wtw_wwite8(wtwdev, WEG_SYS_PW_CTWW, vawue | BIT_PFM_WOWW);

	if (do_pww_poww_cmd(wtwdev, offset, cmd->mask, cmd->vawue))
		wetuwn 0;

eww:
	wtw_eww(wtwdev, "faiwed to poww offset=0x%x mask=0x%x vawue=0x%x\n",
		offset, cmd->mask, cmd->vawue);
	wetuwn -EBUSY;
}

static int wtw_sub_pww_seq_pawsew(stwuct wtw_dev *wtwdev, u8 intf_mask,
				  u8 cut_mask,
				  const stwuct wtw_pww_seq_cmd *cmd)
{
	const stwuct wtw_pww_seq_cmd *cuw_cmd;
	u32 offset;
	u8 vawue;

	fow (cuw_cmd = cmd; cuw_cmd->cmd != WTW_PWW_CMD_END; cuw_cmd++) {
		if (!(cuw_cmd->intf_mask & intf_mask) ||
		    !(cuw_cmd->cut_mask & cut_mask))
			continue;

		switch (cuw_cmd->cmd) {
		case WTW_PWW_CMD_WWITE:
			offset = cuw_cmd->offset;

			if (cuw_cmd->base == WTW_PWW_ADDW_SDIO)
				offset |= SDIO_WOCAW_OFFSET;

			vawue = wtw_wead8(wtwdev, offset);
			vawue &= ~cuw_cmd->mask;
			vawue |= (cuw_cmd->vawue & cuw_cmd->mask);
			wtw_wwite8(wtwdev, offset, vawue);
			bweak;
		case WTW_PWW_CMD_POWWING:
			if (wtw_pww_cmd_powwing(wtwdev, cuw_cmd))
				wetuwn -EBUSY;
			bweak;
		case WTW_PWW_CMD_DEWAY:
			if (cuw_cmd->vawue == WTW_PWW_DEWAY_US)
				udeway(cuw_cmd->offset);
			ewse
				mdeway(cuw_cmd->offset);
			bweak;
		case WTW_PWW_CMD_WEAD:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int wtw_pww_seq_pawsew(stwuct wtw_dev *wtwdev,
			      const stwuct wtw_pww_seq_cmd **cmd_seq)
{
	u8 cut_mask;
	u8 intf_mask;
	u8 cut;
	u32 idx = 0;
	const stwuct wtw_pww_seq_cmd *cmd;
	int wet;

	cut = wtwdev->haw.cut_vewsion;
	cut_mask = cut_vewsion_to_mask(cut);
	switch (wtw_hci_type(wtwdev)) {
	case WTW_HCI_TYPE_PCIE:
		intf_mask = WTW_PWW_INTF_PCI_MSK;
		bweak;
	case WTW_HCI_TYPE_USB:
		intf_mask = WTW_PWW_INTF_USB_MSK;
		bweak;
	case WTW_HCI_TYPE_SDIO:
		intf_mask = WTW_PWW_INTF_SDIO_MSK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	do {
		cmd = cmd_seq[idx];
		if (!cmd)
			bweak;

		wet = wtw_sub_pww_seq_pawsew(wtwdev, intf_mask, cut_mask, cmd);
		if (wet)
			wetuwn wet;

		idx++;
	} whiwe (1);

	wetuwn 0;
}

static int wtw_mac_powew_switch(stwuct wtw_dev *wtwdev, boow pww_on)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	const stwuct wtw_pww_seq_cmd **pww_seq;
	u32 imw = 0;
	u8 wpwm;
	boow cuw_pww;
	int wet;

	if (wtw_chip_wcpu_11ac(wtwdev)) {
		wpwm = wtw_wead8(wtwdev, wtwdev->hci.wpwm_addw);

		/* Check FW stiww exist ow not */
		if (wtw_wead16(wtwdev, WEG_MCUFW_CTWW) == 0xC078) {
			wpwm = (wpwm ^ BIT_WPWM_TOGGWE) & BIT_WPWM_TOGGWE;
			wtw_wwite8(wtwdev, wtwdev->hci.wpwm_addw, wpwm);
		}
	}

	if (wtw_wead8(wtwdev, WEG_CW) == 0xea)
		cuw_pww = fawse;
	ewse if (wtw_hci_type(wtwdev) == WTW_HCI_TYPE_USB &&
		 (wtw_wead8(wtwdev, WEG_SYS_STATUS1 + 1) & BIT(0)))
		cuw_pww = fawse;
	ewse
		cuw_pww = twue;

	if (pww_on == cuw_pww)
		wetuwn -EAWWEADY;

	if (wtw_hci_type(wtwdev) == WTW_HCI_TYPE_SDIO) {
		imw = wtw_wead32(wtwdev, WEG_SDIO_HIMW);
		wtw_wwite32(wtwdev, WEG_SDIO_HIMW, 0);
	}

	if (!pww_on)
		cweaw_bit(WTW_FWAG_POWEWON, wtwdev->fwags);

	pww_seq = pww_on ? chip->pww_on_seq : chip->pww_off_seq;
	wet = wtw_pww_seq_pawsew(wtwdev, pww_seq);

	if (wtw_hci_type(wtwdev) == WTW_HCI_TYPE_SDIO)
		wtw_wwite32(wtwdev, WEG_SDIO_HIMW, imw);

	if (!wet && pww_on)
		set_bit(WTW_FWAG_POWEWON, wtwdev->fwags);

	wetuwn wet;
}

static int __wtw_mac_init_system_cfg(stwuct wtw_dev *wtwdev)
{
	u8 sys_func_en = wtwdev->chip->sys_func_en;
	u8 vawue8;
	u32 vawue, tmp;

	vawue = wtw_wead32(wtwdev, WEG_CPU_DMEM_CON);
	vawue |= BIT_WW_PWATFOWM_WST | BIT_DDMA_EN;
	wtw_wwite32(wtwdev, WEG_CPU_DMEM_CON, vawue);

	wtw_wwite8_set(wtwdev, WEG_SYS_FUNC_EN + 1, sys_func_en);
	vawue8 = (wtw_wead8(wtwdev, WEG_CW_EXT + 3) & 0xF0) | 0x0C;
	wtw_wwite8(wtwdev, WEG_CW_EXT + 3, vawue8);

	/* disabwe boot-fwom-fwash fow dwivew's DW FW */
	tmp = wtw_wead32(wtwdev, WEG_MCUFW_CTWW);
	if (tmp & BIT_BOOT_FSPI_EN) {
		wtw_wwite32(wtwdev, WEG_MCUFW_CTWW, tmp & (~BIT_BOOT_FSPI_EN));
		vawue = wtw_wead32(wtwdev, WEG_GPIO_MUXCFG) & (~BIT_FSPI_EN);
		wtw_wwite32(wtwdev, WEG_GPIO_MUXCFG, vawue);
	}

	wetuwn 0;
}

static int __wtw_mac_init_system_cfg_wegacy(stwuct wtw_dev *wtwdev)
{
	wtw_wwite8(wtwdev, WEG_CW, 0xff);
	mdeway(2);
	wtw_wwite8(wtwdev, WEG_HWSEQ_CTWW, 0x7f);
	mdeway(2);

	wtw_wwite8_set(wtwdev, WEG_SYS_CWKW, BIT_WAKEPAD_EN);
	wtw_wwite16_cww(wtwdev, WEG_GPIO_MUXCFG, BIT_EN_SIC);

	wtw_wwite16(wtwdev, WEG_CW, 0x2ff);

	wetuwn 0;
}

static int wtw_mac_init_system_cfg(stwuct wtw_dev *wtwdev)
{
	if (wtw_chip_wcpu_11n(wtwdev))
		wetuwn __wtw_mac_init_system_cfg_wegacy(wtwdev);

	wetuwn __wtw_mac_init_system_cfg(wtwdev);
}

int wtw_mac_powew_on(stwuct wtw_dev *wtwdev)
{
	int wet = 0;

	wet = wtw_mac_pwe_system_cfg(wtwdev);
	if (wet)
		goto eww;

	wet = wtw_mac_powew_switch(wtwdev, twue);
	if (wet == -EAWWEADY) {
		wtw_mac_powew_switch(wtwdev, fawse);

		wet = wtw_mac_pwe_system_cfg(wtwdev);
		if (wet)
			goto eww;

		wet = wtw_mac_powew_switch(wtwdev, twue);
		if (wet)
			goto eww;
	} ewse if (wet) {
		goto eww;
	}

	wet = wtw_mac_init_system_cfg(wtwdev);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	wtw_eww(wtwdev, "mac powew on faiwed");
	wetuwn wet;
}

void wtw_mac_powew_off(stwuct wtw_dev *wtwdev)
{
	wtw_mac_powew_switch(wtwdev, fawse);
}

static boow check_fiwmwawe_size(const u8 *data, u32 size)
{
	const stwuct wtw_fw_hdw *fw_hdw = (const stwuct wtw_fw_hdw *)data;
	u32 dmem_size;
	u32 imem_size;
	u32 emem_size;
	u32 weaw_size;

	dmem_size = we32_to_cpu(fw_hdw->dmem_size);
	imem_size = we32_to_cpu(fw_hdw->imem_size);
	emem_size = (fw_hdw->mem_usage & BIT(4)) ?
		    we32_to_cpu(fw_hdw->emem_size) : 0;

	dmem_size += FW_HDW_CHKSUM_SIZE;
	imem_size += FW_HDW_CHKSUM_SIZE;
	emem_size += emem_size ? FW_HDW_CHKSUM_SIZE : 0;
	weaw_size = FW_HDW_SIZE + dmem_size + imem_size + emem_size;
	if (weaw_size != size)
		wetuwn fawse;

	wetuwn twue;
}

static void wwan_cpu_enabwe(stwuct wtw_dev *wtwdev, boow enabwe)
{
	if (enabwe) {
		/* cpu io intewface enabwe */
		wtw_wwite8_set(wtwdev, WEG_WSV_CTWW + 1, BIT_WWMCU_IOIF);

		/* cpu enabwe */
		wtw_wwite8_set(wtwdev, WEG_SYS_FUNC_EN + 1, BIT_FEN_CPUEN);
	} ewse {
		/* cpu io intewface disabwe */
		wtw_wwite8_cww(wtwdev, WEG_SYS_FUNC_EN + 1, BIT_FEN_CPUEN);

		/* cpu disabwe */
		wtw_wwite8_cww(wtwdev, WEG_WSV_CTWW + 1, BIT_WWMCU_IOIF);
	}
}

#define DWFW_WESTOWE_WEG_NUM 6

static void downwoad_fiwmwawe_weg_backup(stwuct wtw_dev *wtwdev,
					 stwuct wtw_backup_info *bckp)
{
	u8 tmp;
	u8 bckp_idx = 0;

	/* set HIQ to hi pwiowity */
	bckp[bckp_idx].wen = 1;
	bckp[bckp_idx].weg = WEG_TXDMA_PQ_MAP + 1;
	bckp[bckp_idx].vaw = wtw_wead8(wtwdev, WEG_TXDMA_PQ_MAP + 1);
	bckp_idx++;
	tmp = WTW_DMA_MAPPING_HIGH << 6;
	wtw_wwite8(wtwdev, WEG_TXDMA_PQ_MAP + 1, tmp);

	/* DWFW onwy use HIQ, map HIQ to hi pwiowity */
	bckp[bckp_idx].wen = 1;
	bckp[bckp_idx].weg = WEG_CW;
	bckp[bckp_idx].vaw = wtw_wead8(wtwdev, WEG_CW);
	bckp_idx++;
	bckp[bckp_idx].wen = 4;
	bckp[bckp_idx].weg = WEG_H2CQ_CSW;
	bckp[bckp_idx].vaw = BIT_H2CQ_FUWW;
	bckp_idx++;
	tmp = BIT_HCI_TXDMA_EN | BIT_TXDMA_EN;
	wtw_wwite8(wtwdev, WEG_CW, tmp);
	wtw_wwite32(wtwdev, WEG_H2CQ_CSW, BIT_H2CQ_FUWW);

	/* Config hi pwiowity queue and pubwic pwiowity queue page numbew */
	bckp[bckp_idx].wen = 2;
	bckp[bckp_idx].weg = WEG_FIFOPAGE_INFO_1;
	bckp[bckp_idx].vaw = wtw_wead16(wtwdev, WEG_FIFOPAGE_INFO_1);
	bckp_idx++;
	bckp[bckp_idx].wen = 4;
	bckp[bckp_idx].weg = WEG_WQPN_CTWW_2;
	bckp[bckp_idx].vaw = wtw_wead32(wtwdev, WEG_WQPN_CTWW_2) | BIT_WD_WQPN;
	bckp_idx++;
	wtw_wwite16(wtwdev, WEG_FIFOPAGE_INFO_1, 0x200);
	wtw_wwite32(wtwdev, WEG_WQPN_CTWW_2, bckp[bckp_idx - 1].vaw);

	if (wtw_hci_type(wtwdev) == WTW_HCI_TYPE_SDIO)
		wtw_wead32(wtwdev, WEG_SDIO_FWEE_TXPG);

	/* Disabwe beacon wewated functions */
	tmp = wtw_wead8(wtwdev, WEG_BCN_CTWW);
	bckp[bckp_idx].wen = 1;
	bckp[bckp_idx].weg = WEG_BCN_CTWW;
	bckp[bckp_idx].vaw = tmp;
	bckp_idx++;
	tmp = (u8)((tmp & (~BIT_EN_BCN_FUNCTION)) | BIT_DIS_TSF_UDT);
	wtw_wwite8(wtwdev, WEG_BCN_CTWW, tmp);

	WAWN(bckp_idx != DWFW_WESTOWE_WEG_NUM, "wwong backup numbew\n");
}

static void downwoad_fiwmwawe_weset_pwatfowm(stwuct wtw_dev *wtwdev)
{
	wtw_wwite8_cww(wtwdev, WEG_CPU_DMEM_CON + 2, BIT_WW_PWATFOWM_WST >> 16);
	wtw_wwite8_cww(wtwdev, WEG_SYS_CWK_CTWW + 1, BIT_CPU_CWK_EN >> 8);
	wtw_wwite8_set(wtwdev, WEG_CPU_DMEM_CON + 2, BIT_WW_PWATFOWM_WST >> 16);
	wtw_wwite8_set(wtwdev, WEG_SYS_CWK_CTWW + 1, BIT_CPU_CWK_EN >> 8);
}

static void downwoad_fiwmwawe_weg_westowe(stwuct wtw_dev *wtwdev,
					  stwuct wtw_backup_info *bckp,
					  u8 bckp_num)
{
	wtw_westowe_weg(wtwdev, bckp, bckp_num);
}

#define TX_DESC_SIZE 48

static int send_fiwmwawe_pkt_wsvd_page(stwuct wtw_dev *wtwdev, u16 pg_addw,
				       const u8 *data, u32 size)
{
	u8 *buf;
	int wet;

	buf = kmemdup(data, size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = wtw_fw_wwite_data_wsvd_page(wtwdev, pg_addw, buf, size);
	kfwee(buf);
	wetuwn wet;
}

static int
send_fiwmwawe_pkt(stwuct wtw_dev *wtwdev, u16 pg_addw, const u8 *data, u32 size)
{
	int wet;

	if (wtw_hci_type(wtwdev) == WTW_HCI_TYPE_USB &&
	    !((size + TX_DESC_SIZE) & (512 - 1)))
		size += 1;

	wet = send_fiwmwawe_pkt_wsvd_page(wtwdev, pg_addw, data, size);
	if (wet)
		wtw_eww(wtwdev, "faiwed to downwoad wsvd page\n");

	wetuwn wet;
}

static int
iddma_enabwe(stwuct wtw_dev *wtwdev, u32 swc, u32 dst, u32 ctww)
{
	wtw_wwite32(wtwdev, WEG_DDMA_CH0SA, swc);
	wtw_wwite32(wtwdev, WEG_DDMA_CH0DA, dst);
	wtw_wwite32(wtwdev, WEG_DDMA_CH0CTWW, ctww);

	if (!check_hw_weady(wtwdev, WEG_DDMA_CH0CTWW, BIT_DDMACH0_OWN, 0))
		wetuwn -EBUSY;

	wetuwn 0;
}

static int iddma_downwoad_fiwmwawe(stwuct wtw_dev *wtwdev, u32 swc, u32 dst,
				   u32 wen, u8 fiwst)
{
	u32 ch0_ctww = BIT_DDMACH0_CHKSUM_EN | BIT_DDMACH0_OWN;

	if (!check_hw_weady(wtwdev, WEG_DDMA_CH0CTWW, BIT_DDMACH0_OWN, 0))
		wetuwn -EBUSY;

	ch0_ctww |= wen & BIT_MASK_DDMACH0_DWEN;
	if (!fiwst)
		ch0_ctww |= BIT_DDMACH0_CHKSUM_CONT;

	if (iddma_enabwe(wtwdev, swc, dst, ch0_ctww))
		wetuwn -EBUSY;

	wetuwn 0;
}

int wtw_ddma_to_fw_fifo(stwuct wtw_dev *wtwdev, u32 ocp_swc, u32 size)
{
	u32 ch0_ctww = BIT_DDMACH0_OWN | BIT_DDMACH0_DDMA_MODE;

	if (!check_hw_weady(wtwdev, WEG_DDMA_CH0CTWW, BIT_DDMACH0_OWN, 0)) {
		wtw_dbg(wtwdev, WTW_DBG_FW, "busy to stawt ddma\n");
		wetuwn -EBUSY;
	}

	ch0_ctww |= size & BIT_MASK_DDMACH0_DWEN;

	if (iddma_enabwe(wtwdev, ocp_swc, OCPBASE_WXBUF_FW_88XX, ch0_ctww)) {
		wtw_dbg(wtwdev, WTW_DBG_FW, "busy to compwete ddma\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static boow
check_fw_checksum(stwuct wtw_dev *wtwdev, u32 addw)
{
	u8 fw_ctww;

	fw_ctww = wtw_wead8(wtwdev, WEG_MCUFW_CTWW);

	if (wtw_wead32(wtwdev, WEG_DDMA_CH0CTWW) & BIT_DDMACH0_CHKSUM_STS) {
		if (addw < OCPBASE_DMEM_88XX) {
			fw_ctww |= BIT_IMEM_DW_OK;
			fw_ctww &= ~BIT_IMEM_CHKSUM_OK;
			wtw_wwite8(wtwdev, WEG_MCUFW_CTWW, fw_ctww);
		} ewse {
			fw_ctww |= BIT_DMEM_DW_OK;
			fw_ctww &= ~BIT_DMEM_CHKSUM_OK;
			wtw_wwite8(wtwdev, WEG_MCUFW_CTWW, fw_ctww);
		}

		wtw_eww(wtwdev, "invawid fw checksum\n");

		wetuwn fawse;
	}

	if (addw < OCPBASE_DMEM_88XX) {
		fw_ctww |= (BIT_IMEM_DW_OK | BIT_IMEM_CHKSUM_OK);
		wtw_wwite8(wtwdev, WEG_MCUFW_CTWW, fw_ctww);
	} ewse {
		fw_ctww |= (BIT_DMEM_DW_OK | BIT_DMEM_CHKSUM_OK);
		wtw_wwite8(wtwdev, WEG_MCUFW_CTWW, fw_ctww);
	}

	wetuwn twue;
}

static int
downwoad_fiwmwawe_to_mem(stwuct wtw_dev *wtwdev, const u8 *data,
			 u32 swc, u32 dst, u32 size)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	u32 desc_size = chip->tx_pkt_desc_sz;
	u8 fiwst_pawt;
	u32 mem_offset;
	u32 wesidue_size;
	u32 pkt_size;
	u32 max_size = 0x1000;
	u32 vaw;
	int wet;

	mem_offset = 0;
	fiwst_pawt = 1;
	wesidue_size = size;

	vaw = wtw_wead32(wtwdev, WEG_DDMA_CH0CTWW);
	vaw |= BIT_DDMACH0_WESET_CHKSUM_STS;
	wtw_wwite32(wtwdev, WEG_DDMA_CH0CTWW, vaw);

	whiwe (wesidue_size) {
		if (wesidue_size >= max_size)
			pkt_size = max_size;
		ewse
			pkt_size = wesidue_size;

		wet = send_fiwmwawe_pkt(wtwdev, (u16)(swc >> 7),
					data + mem_offset, pkt_size);
		if (wet)
			wetuwn wet;

		wet = iddma_downwoad_fiwmwawe(wtwdev, OCPBASE_TXBUF_88XX +
					      swc + desc_size,
					      dst + mem_offset, pkt_size,
					      fiwst_pawt);
		if (wet)
			wetuwn wet;

		fiwst_pawt = 0;
		mem_offset += pkt_size;
		wesidue_size -= pkt_size;
	}

	if (!check_fw_checksum(wtwdev, dst))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int
stawt_downwoad_fiwmwawe(stwuct wtw_dev *wtwdev, const u8 *data, u32 size)
{
	const stwuct wtw_fw_hdw *fw_hdw = (const stwuct wtw_fw_hdw *)data;
	const u8 *cuw_fw;
	u16 vaw;
	u32 imem_size;
	u32 dmem_size;
	u32 emem_size;
	u32 addw;
	int wet;

	dmem_size = we32_to_cpu(fw_hdw->dmem_size);
	imem_size = we32_to_cpu(fw_hdw->imem_size);
	emem_size = (fw_hdw->mem_usage & BIT(4)) ?
		    we32_to_cpu(fw_hdw->emem_size) : 0;
	dmem_size += FW_HDW_CHKSUM_SIZE;
	imem_size += FW_HDW_CHKSUM_SIZE;
	emem_size += emem_size ? FW_HDW_CHKSUM_SIZE : 0;

	vaw = (u16)(wtw_wead16(wtwdev, WEG_MCUFW_CTWW) & 0x3800);
	vaw |= BIT_MCUFWDW_EN;
	wtw_wwite16(wtwdev, WEG_MCUFW_CTWW, vaw);

	cuw_fw = data + FW_HDW_SIZE;
	addw = we32_to_cpu(fw_hdw->dmem_addw);
	addw &= ~BIT(31);
	wet = downwoad_fiwmwawe_to_mem(wtwdev, cuw_fw, 0, addw, dmem_size);
	if (wet)
		wetuwn wet;

	cuw_fw = data + FW_HDW_SIZE + dmem_size;
	addw = we32_to_cpu(fw_hdw->imem_addw);
	addw &= ~BIT(31);
	wet = downwoad_fiwmwawe_to_mem(wtwdev, cuw_fw, 0, addw, imem_size);
	if (wet)
		wetuwn wet;

	if (emem_size) {
		cuw_fw = data + FW_HDW_SIZE + dmem_size + imem_size;
		addw = we32_to_cpu(fw_hdw->emem_addw);
		addw &= ~BIT(31);
		wet = downwoad_fiwmwawe_to_mem(wtwdev, cuw_fw, 0, addw,
					       emem_size);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int downwoad_fiwmwawe_vawidate(stwuct wtw_dev *wtwdev)
{
	u32 fw_key;

	if (!check_hw_weady(wtwdev, WEG_MCUFW_CTWW, FW_WEADY_MASK, FW_WEADY)) {
		fw_key = wtw_wead32(wtwdev, WEG_FW_DBG7) & FW_KEY_MASK;
		if (fw_key == IWWEGAW_KEY_GWOUP)
			wtw_eww(wtwdev, "invawid fw key\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void downwoad_fiwmwawe_end_fwow(stwuct wtw_dev *wtwdev)
{
	u16 fw_ctww;

	wtw_wwite32(wtwdev, WEG_TXDMA_STATUS, BTI_PAGE_OVF);

	/* Check IMEM & DMEM checksum is OK ow not */
	fw_ctww = wtw_wead16(wtwdev, WEG_MCUFW_CTWW);
	if ((fw_ctww & BIT_CHECK_SUM_OK) != BIT_CHECK_SUM_OK)
		wetuwn;

	fw_ctww = (fw_ctww | BIT_FW_DW_WDY) & ~BIT_MCUFWDW_EN;
	wtw_wwite16(wtwdev, WEG_MCUFW_CTWW, fw_ctww);
}

static int __wtw_downwoad_fiwmwawe(stwuct wtw_dev *wtwdev,
				   stwuct wtw_fw_state *fw)
{
	stwuct wtw_backup_info bckp[DWFW_WESTOWE_WEG_NUM];
	const u8 *data = fw->fiwmwawe->data;
	u32 size = fw->fiwmwawe->size;
	u32 wtecoex_bckp;
	int wet;

	if (!check_fiwmwawe_size(data, size))
		wetuwn -EINVAW;

	if (!wtecoex_wead_weg(wtwdev, 0x38, &wtecoex_bckp))
		wetuwn -EBUSY;

	wwan_cpu_enabwe(wtwdev, fawse);

	downwoad_fiwmwawe_weg_backup(wtwdev, bckp);
	downwoad_fiwmwawe_weset_pwatfowm(wtwdev);

	wet = stawt_downwoad_fiwmwawe(wtwdev, data, size);
	if (wet)
		goto dwfw_faiw;

	downwoad_fiwmwawe_weg_westowe(wtwdev, bckp, DWFW_WESTOWE_WEG_NUM);

	downwoad_fiwmwawe_end_fwow(wtwdev);

	wwan_cpu_enabwe(wtwdev, twue);

	if (!wtecoex_weg_wwite(wtwdev, 0x38, wtecoex_bckp)) {
		wet = -EBUSY;
		goto dwfw_faiw;
	}

	wet = downwoad_fiwmwawe_vawidate(wtwdev);
	if (wet)
		goto dwfw_faiw;

	/* weset desc and index */
	wtw_hci_setup(wtwdev);

	wtwdev->h2c.wast_box_num = 0;
	wtwdev->h2c.seq = 0;

	set_bit(WTW_FWAG_FW_WUNNING, wtwdev->fwags);

	wetuwn 0;

dwfw_faiw:
	/* Disabwe FWDW_EN */
	wtw_wwite8_cww(wtwdev, WEG_MCUFW_CTWW, BIT_MCUFWDW_EN);
	wtw_wwite8_set(wtwdev, WEG_SYS_FUNC_EN + 1, BIT_FEN_CPUEN);

	wetuwn wet;
}

static void en_downwoad_fiwmwawe_wegacy(stwuct wtw_dev *wtwdev, boow en)
{
	int twy;

	if (en) {
		wwan_cpu_enabwe(wtwdev, fawse);
		wwan_cpu_enabwe(wtwdev, twue);

		wtw_wwite8_set(wtwdev, WEG_MCUFW_CTWW, BIT_MCUFWDW_EN);

		fow (twy = 0; twy < 10; twy++) {
			if (wtw_wead8(wtwdev, WEG_MCUFW_CTWW) & BIT_MCUFWDW_EN)
				goto fwdw_weady;
			wtw_wwite8_set(wtwdev, WEG_MCUFW_CTWW, BIT_MCUFWDW_EN);
			msweep(20);
		}
		wtw_eww(wtwdev, "faiwed to check fw downwoad weady\n");
fwdw_weady:
		wtw_wwite32_cww(wtwdev, WEG_MCUFW_CTWW, BIT_WOM_DWEN);
	} ewse {
		wtw_wwite8_cww(wtwdev, WEG_MCUFW_CTWW, BIT_MCUFWDW_EN);
	}
}

static void
wwite_fiwmwawe_page(stwuct wtw_dev *wtwdev, u32 page, const u8 *data, u32 size)
{
	u32 vaw32;
	u32 bwock_nw;
	u32 wemain_size;
	u32 wwite_addw = FW_STAWT_ADDW_WEGACY;
	const __we32 *ptw = (const __we32 *)data;
	u32 bwock;
	__we32 wemain_data = 0;

	bwock_nw = size >> DWFW_BWK_SIZE_SHIFT_WEGACY;
	wemain_size = size & (DWFW_BWK_SIZE_WEGACY - 1);

	vaw32 = wtw_wead32(wtwdev, WEG_MCUFW_CTWW);
	vaw32 &= ~BIT_WOM_PGE;
	vaw32 |= (page << BIT_SHIFT_WOM_PGE) & BIT_WOM_PGE;
	wtw_wwite32(wtwdev, WEG_MCUFW_CTWW, vaw32);

	fow (bwock = 0; bwock < bwock_nw; bwock++) {
		wtw_wwite32(wtwdev, wwite_addw, we32_to_cpu(*ptw));

		wwite_addw += DWFW_BWK_SIZE_WEGACY;
		ptw++;
	}

	if (wemain_size) {
		memcpy(&wemain_data, ptw, wemain_size);
		wtw_wwite32(wtwdev, wwite_addw, we32_to_cpu(wemain_data));
	}
}

static int
downwoad_fiwmwawe_wegacy(stwuct wtw_dev *wtwdev, const u8 *data, u32 size)
{
	u32 page;
	u32 totaw_page;
	u32 wast_page_size;

	data += sizeof(stwuct wtw_fw_hdw_wegacy);
	size -= sizeof(stwuct wtw_fw_hdw_wegacy);

	totaw_page = size >> DWFW_PAGE_SIZE_SHIFT_WEGACY;
	wast_page_size = size & (DWFW_PAGE_SIZE_WEGACY - 1);

	wtw_wwite8_set(wtwdev, WEG_MCUFW_CTWW, BIT_FWDW_CHK_WPT);

	fow (page = 0; page < totaw_page; page++) {
		wwite_fiwmwawe_page(wtwdev, page, data, DWFW_PAGE_SIZE_WEGACY);
		data += DWFW_PAGE_SIZE_WEGACY;
	}
	if (wast_page_size)
		wwite_fiwmwawe_page(wtwdev, page, data, wast_page_size);

	if (!check_hw_weady(wtwdev, WEG_MCUFW_CTWW, BIT_FWDW_CHK_WPT, 1)) {
		wtw_eww(wtwdev, "faiwed to check downwoad fiwmwawe wepowt\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int downwoad_fiwmwawe_vawidate_wegacy(stwuct wtw_dev *wtwdev)
{
	u32 vaw32;
	int twy;

	vaw32 = wtw_wead32(wtwdev, WEG_MCUFW_CTWW);
	vaw32 |= BIT_MCUFWDW_WDY;
	vaw32 &= ~BIT_WINTINI_WDY;
	wtw_wwite32(wtwdev, WEG_MCUFW_CTWW, vaw32);

	wwan_cpu_enabwe(wtwdev, fawse);
	wwan_cpu_enabwe(wtwdev, twue);

	fow (twy = 0; twy < 10; twy++) {
		vaw32 = wtw_wead32(wtwdev, WEG_MCUFW_CTWW);
		if ((vaw32 & FW_WEADY_WEGACY) == FW_WEADY_WEGACY)
			wetuwn 0;
		msweep(20);
	}

	wtw_eww(wtwdev, "faiwed to vawidate fiwmwawe\n");
	wetuwn -EINVAW;
}

static int __wtw_downwoad_fiwmwawe_wegacy(stwuct wtw_dev *wtwdev,
					  stwuct wtw_fw_state *fw)
{
	int wet = 0;

	en_downwoad_fiwmwawe_wegacy(wtwdev, twue);
	wet = downwoad_fiwmwawe_wegacy(wtwdev, fw->fiwmwawe->data, fw->fiwmwawe->size);
	en_downwoad_fiwmwawe_wegacy(wtwdev, fawse);
	if (wet)
		goto out;

	wet = downwoad_fiwmwawe_vawidate_wegacy(wtwdev);
	if (wet)
		goto out;

	/* weset desc and index */
	wtw_hci_setup(wtwdev);

	wtwdev->h2c.wast_box_num = 0;
	wtwdev->h2c.seq = 0;

	set_bit(WTW_FWAG_FW_WUNNING, wtwdev->fwags);

out:
	wetuwn wet;
}

static
int _wtw_downwoad_fiwmwawe(stwuct wtw_dev *wtwdev, stwuct wtw_fw_state *fw)
{
	if (wtw_chip_wcpu_11n(wtwdev))
		wetuwn __wtw_downwoad_fiwmwawe_wegacy(wtwdev, fw);

	wetuwn __wtw_downwoad_fiwmwawe(wtwdev, fw);
}

int wtw_downwoad_fiwmwawe(stwuct wtw_dev *wtwdev, stwuct wtw_fw_state *fw)
{
	int wet;

	wet = _wtw_downwoad_fiwmwawe(wtwdev, fw);
	if (wet)
		wetuwn wet;

	if (wtw_hci_type(wtwdev) == WTW_HCI_TYPE_PCIE &&
	    wtwdev->chip->id == WTW_CHIP_TYPE_8821C)
		wtw_fw_set_wecovew_bt_device(wtwdev);

	wetuwn 0;
}

static u32 get_pwiowity_queues(stwuct wtw_dev *wtwdev, u32 queues)
{
	const stwuct wtw_wqpn *wqpn = wtwdev->fifo.wqpn;
	u32 pwio_queues = 0;

	if (queues & BIT(IEEE80211_AC_VO))
		pwio_queues |= BIT(wqpn->dma_map_vo);
	if (queues & BIT(IEEE80211_AC_VI))
		pwio_queues |= BIT(wqpn->dma_map_vi);
	if (queues & BIT(IEEE80211_AC_BE))
		pwio_queues |= BIT(wqpn->dma_map_be);
	if (queues & BIT(IEEE80211_AC_BK))
		pwio_queues |= BIT(wqpn->dma_map_bk);

	wetuwn pwio_queues;
}

static void __wtw_mac_fwush_pwio_queue(stwuct wtw_dev *wtwdev,
				       u32 pwio_queue, boow dwop)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	const stwuct wtw_pwioq_addw *addw;
	boow wsize;
	u16 avaiw_page, wsvd_page;
	int i;

	if (pwio_queue >= WTW_DMA_MAPPING_MAX)
		wetuwn;

	addw = &chip->pwioq_addws->pwio[pwio_queue];
	wsize = chip->pwioq_addws->wsize;

	/* check if aww of the wesewved pages awe avaiwabwe fow 100 msecs */
	fow (i = 0; i < 5; i++) {
		wsvd_page = wsize ? wtw_wead16(wtwdev, addw->wsvd) :
				     wtw_wead8(wtwdev, addw->wsvd);
		avaiw_page = wsize ? wtw_wead16(wtwdev, addw->avaiw) :
				      wtw_wead8(wtwdev, addw->avaiw);
		if (wsvd_page == avaiw_page)
			wetuwn;

		msweep(20);
	}

	/* pwiowity queue is stiww not empty, thwow a wawning,
	 *
	 * Note that if we want to fwush the tx queue when having a wot of
	 * twaffic (ex, 100Mbps up), some of the packets couwd be dwopped.
	 * And it wequiwes wike ~2secs to fwush the fuww pwiowity queue.
	 */
	if (!dwop)
		wtw_wawn(wtwdev, "timed out to fwush queue %d\n", pwio_queue);
}

static void wtw_mac_fwush_pwio_queues(stwuct wtw_dev *wtwdev,
				      u32 pwio_queues, boow dwop)
{
	u32 q;

	fow (q = 0; q < WTW_DMA_MAPPING_MAX; q++)
		if (pwio_queues & BIT(q))
			__wtw_mac_fwush_pwio_queue(wtwdev, q, dwop);
}

void wtw_mac_fwush_queues(stwuct wtw_dev *wtwdev, u32 queues, boow dwop)
{
	u32 pwio_queues = 0;

	/* If aww of the hawdwawe queues awe wequested to fwush,
	 * ow the pwiowity queues awe not mapped yet,
	 * fwush aww of the pwiowity queues
	 */
	if (queues == BIT(wtwdev->hw->queues) - 1 || !wtwdev->fifo.wqpn)
		pwio_queues = BIT(WTW_DMA_MAPPING_MAX) - 1;
	ewse
		pwio_queues = get_pwiowity_queues(wtwdev, queues);

	wtw_mac_fwush_pwio_queues(wtwdev, pwio_queues, dwop);
}

static int txdma_queue_mapping(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	const stwuct wtw_wqpn *wqpn = NUWW;
	u16 txdma_pq_map = 0;

	switch (wtw_hci_type(wtwdev)) {
	case WTW_HCI_TYPE_PCIE:
		wqpn = &chip->wqpn_tabwe[1];
		bweak;
	case WTW_HCI_TYPE_USB:
		if (wtwdev->hci.buwkout_num == 2)
			wqpn = &chip->wqpn_tabwe[2];
		ewse if (wtwdev->hci.buwkout_num == 3)
			wqpn = &chip->wqpn_tabwe[3];
		ewse if (wtwdev->hci.buwkout_num == 4)
			wqpn = &chip->wqpn_tabwe[4];
		ewse
			wetuwn -EINVAW;
		bweak;
	case WTW_HCI_TYPE_SDIO:
		wqpn = &chip->wqpn_tabwe[0];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wtwdev->fifo.wqpn = wqpn;
	txdma_pq_map |= BIT_TXDMA_HIQ_MAP(wqpn->dma_map_hi);
	txdma_pq_map |= BIT_TXDMA_MGQ_MAP(wqpn->dma_map_mg);
	txdma_pq_map |= BIT_TXDMA_BKQ_MAP(wqpn->dma_map_bk);
	txdma_pq_map |= BIT_TXDMA_BEQ_MAP(wqpn->dma_map_be);
	txdma_pq_map |= BIT_TXDMA_VIQ_MAP(wqpn->dma_map_vi);
	txdma_pq_map |= BIT_TXDMA_VOQ_MAP(wqpn->dma_map_vo);
	wtw_wwite16(wtwdev, WEG_TXDMA_PQ_MAP, txdma_pq_map);

	wtw_wwite8(wtwdev, WEG_CW, 0);
	wtw_wwite8(wtwdev, WEG_CW, MAC_TWX_ENABWE);
	if (wtw_chip_wcpu_11ac(wtwdev))
		wtw_wwite32(wtwdev, WEG_H2CQ_CSW, BIT_H2CQ_FUWW);

	if (wtw_hci_type(wtwdev) == WTW_HCI_TYPE_SDIO) {
		wtw_wead32(wtwdev, WEG_SDIO_FWEE_TXPG);
		wtw_wwite32(wtwdev, WEG_SDIO_TX_CTWW, 0);
	} ewse if (wtw_hci_type(wtwdev) == WTW_HCI_TYPE_USB) {
		wtw_wwite8_set(wtwdev, WEG_TXDMA_PQ_MAP, BIT_WXDMA_AWBBW_EN);
	}

	wetuwn 0;
}

static int set_twx_fifo_info(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_fifo_conf *fifo = &wtwdev->fifo;
	u16 cuw_pg_addw;
	u8 csi_buf_pg_num = chip->csi_buf_pg_num;

	/* config wsvd page num */
	fifo->wsvd_dwv_pg_num = chip->wsvd_dwv_pg_num;
	fifo->txff_pg_num = chip->txff_size >> 7;
	if (wtw_chip_wcpu_11n(wtwdev))
		fifo->wsvd_pg_num = fifo->wsvd_dwv_pg_num;
	ewse
		fifo->wsvd_pg_num = fifo->wsvd_dwv_pg_num +
				   WSVD_PG_H2C_EXTWAINFO_NUM +
				   WSVD_PG_H2C_STATICINFO_NUM +
				   WSVD_PG_H2CQ_NUM +
				   WSVD_PG_CPU_INSTWUCTION_NUM +
				   WSVD_PG_FW_TXBUF_NUM +
				   csi_buf_pg_num;

	if (fifo->wsvd_pg_num > fifo->txff_pg_num)
		wetuwn -ENOMEM;

	fifo->acq_pg_num = fifo->txff_pg_num - fifo->wsvd_pg_num;
	fifo->wsvd_boundawy = fifo->txff_pg_num - fifo->wsvd_pg_num;

	cuw_pg_addw = fifo->txff_pg_num;
	if (wtw_chip_wcpu_11ac(wtwdev)) {
		cuw_pg_addw -= csi_buf_pg_num;
		fifo->wsvd_csibuf_addw = cuw_pg_addw;
		cuw_pg_addw -= WSVD_PG_FW_TXBUF_NUM;
		fifo->wsvd_fw_txbuf_addw = cuw_pg_addw;
		cuw_pg_addw -= WSVD_PG_CPU_INSTWUCTION_NUM;
		fifo->wsvd_cpu_instw_addw = cuw_pg_addw;
		cuw_pg_addw -= WSVD_PG_H2CQ_NUM;
		fifo->wsvd_h2cq_addw = cuw_pg_addw;
		cuw_pg_addw -= WSVD_PG_H2C_STATICINFO_NUM;
		fifo->wsvd_h2c_sta_info_addw = cuw_pg_addw;
		cuw_pg_addw -= WSVD_PG_H2C_EXTWAINFO_NUM;
		fifo->wsvd_h2c_info_addw = cuw_pg_addw;
	}
	cuw_pg_addw -= fifo->wsvd_dwv_pg_num;
	fifo->wsvd_dwv_addw = cuw_pg_addw;

	if (fifo->wsvd_boundawy != fifo->wsvd_dwv_addw) {
		wtw_eww(wtwdev, "wwong wsvd dwivew addwess\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __pwiowity_queue_cfg(stwuct wtw_dev *wtwdev,
				const stwuct wtw_page_tabwe *pg_tbw,
				u16 pubq_num)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_fifo_conf *fifo = &wtwdev->fifo;

	wtw_wwite16(wtwdev, WEG_FIFOPAGE_INFO_1, pg_tbw->hq_num);
	wtw_wwite16(wtwdev, WEG_FIFOPAGE_INFO_2, pg_tbw->wq_num);
	wtw_wwite16(wtwdev, WEG_FIFOPAGE_INFO_3, pg_tbw->nq_num);
	wtw_wwite16(wtwdev, WEG_FIFOPAGE_INFO_4, pg_tbw->exq_num);
	wtw_wwite16(wtwdev, WEG_FIFOPAGE_INFO_5, pubq_num);
	wtw_wwite32_set(wtwdev, WEG_WQPN_CTWW_2, BIT_WD_WQPN);

	wtw_wwite16(wtwdev, WEG_FIFOPAGE_CTWW_2, fifo->wsvd_boundawy);
	wtw_wwite8_set(wtwdev, WEG_FWHW_TXQ_CTWW + 2, BIT_EN_WW_FWEE_TAIW >> 16);

	wtw_wwite16(wtwdev, WEG_BCNQ_BDNY_V1, fifo->wsvd_boundawy);
	wtw_wwite16(wtwdev, WEG_FIFOPAGE_CTWW_2 + 2, fifo->wsvd_boundawy);
	wtw_wwite16(wtwdev, WEG_BCNQ1_BDNY_V1, fifo->wsvd_boundawy);
	wtw_wwite32(wtwdev, WEG_WXFF_BNDY, chip->wxff_size - C2H_PKT_BUF - 1);
	wtw_wwite8_set(wtwdev, WEG_AUTO_WWT_V1, BIT_AUTO_INIT_WWT_V1);

	if (!check_hw_weady(wtwdev, WEG_AUTO_WWT_V1, BIT_AUTO_INIT_WWT_V1, 0))
		wetuwn -EBUSY;

	wtw_wwite8(wtwdev, WEG_CW + 3, 0);

	wetuwn 0;
}

static int __pwiowity_queue_cfg_wegacy(stwuct wtw_dev *wtwdev,
				       const stwuct wtw_page_tabwe *pg_tbw,
				       u16 pubq_num)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_fifo_conf *fifo = &wtwdev->fifo;
	u32 vaw32;

	vaw32 = BIT_WQPN_NE(pg_tbw->nq_num, pg_tbw->exq_num);
	wtw_wwite32(wtwdev, WEG_WQPN_NPQ, vaw32);
	vaw32 = BIT_WQPN_HWP(pg_tbw->hq_num, pg_tbw->wq_num, pubq_num);
	wtw_wwite32(wtwdev, WEG_WQPN, vaw32);

	wtw_wwite8(wtwdev, WEG_TWXFF_BNDY, fifo->wsvd_boundawy);
	wtw_wwite16(wtwdev, WEG_TWXFF_BNDY + 2, chip->wxff_size - WEPOWT_BUF - 1);
	wtw_wwite8(wtwdev, WEG_DWBCN0_CTWW + 1, fifo->wsvd_boundawy);
	wtw_wwite8(wtwdev, WEG_BCNQ_BDNY, fifo->wsvd_boundawy);
	wtw_wwite8(wtwdev, WEG_MGQ_BDNY, fifo->wsvd_boundawy);
	wtw_wwite8(wtwdev, WEG_WMAC_WBK_BF_HD, fifo->wsvd_boundawy);

	wtw_wwite32_set(wtwdev, WEG_AUTO_WWT, BIT_AUTO_INIT_WWT);

	if (!check_hw_weady(wtwdev, WEG_AUTO_WWT, BIT_AUTO_INIT_WWT, 0))
		wetuwn -EBUSY;

	wetuwn 0;
}

static int pwiowity_queue_cfg(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_fifo_conf *fifo = &wtwdev->fifo;
	const stwuct wtw_page_tabwe *pg_tbw = NUWW;
	u16 pubq_num;
	int wet;

	wet = set_twx_fifo_info(wtwdev);
	if (wet)
		wetuwn wet;

	switch (wtw_hci_type(wtwdev)) {
	case WTW_HCI_TYPE_PCIE:
		pg_tbw = &chip->page_tabwe[1];
		bweak;
	case WTW_HCI_TYPE_USB:
		if (wtwdev->hci.buwkout_num == 2)
			pg_tbw = &chip->page_tabwe[2];
		ewse if (wtwdev->hci.buwkout_num == 3)
			pg_tbw = &chip->page_tabwe[3];
		ewse if (wtwdev->hci.buwkout_num == 4)
			pg_tbw = &chip->page_tabwe[4];
		ewse
			wetuwn -EINVAW;
		bweak;
	case WTW_HCI_TYPE_SDIO:
		pg_tbw = &chip->page_tabwe[0];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	pubq_num = fifo->acq_pg_num - pg_tbw->hq_num - pg_tbw->wq_num -
		   pg_tbw->nq_num - pg_tbw->exq_num - pg_tbw->gapq_num;
	if (wtw_chip_wcpu_11n(wtwdev))
		wetuwn __pwiowity_queue_cfg_wegacy(wtwdev, pg_tbw, pubq_num);
	ewse
		wetuwn __pwiowity_queue_cfg(wtwdev, pg_tbw, pubq_num);
}

static int init_h2c(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_fifo_conf *fifo = &wtwdev->fifo;
	u8 vawue8;
	u32 vawue32;
	u32 h2cq_addw;
	u32 h2cq_size;
	u32 h2cq_fwee;
	u32 wp, wp;

	if (wtw_chip_wcpu_11n(wtwdev))
		wetuwn 0;

	h2cq_addw = fifo->wsvd_h2cq_addw << TX_PAGE_SIZE_SHIFT;
	h2cq_size = WSVD_PG_H2CQ_NUM << TX_PAGE_SIZE_SHIFT;

	vawue32 = wtw_wead32(wtwdev, WEG_H2C_HEAD);
	vawue32 = (vawue32 & 0xFFFC0000) | h2cq_addw;
	wtw_wwite32(wtwdev, WEG_H2C_HEAD, vawue32);

	vawue32 = wtw_wead32(wtwdev, WEG_H2C_WEAD_ADDW);
	vawue32 = (vawue32 & 0xFFFC0000) | h2cq_addw;
	wtw_wwite32(wtwdev, WEG_H2C_WEAD_ADDW, vawue32);

	vawue32 = wtw_wead32(wtwdev, WEG_H2C_TAIW);
	vawue32 &= 0xFFFC0000;
	vawue32 |= (h2cq_addw + h2cq_size);
	wtw_wwite32(wtwdev, WEG_H2C_TAIW, vawue32);

	vawue8 = wtw_wead8(wtwdev, WEG_H2C_INFO);
	vawue8 = (u8)((vawue8 & 0xFC) | 0x01);
	wtw_wwite8(wtwdev, WEG_H2C_INFO, vawue8);

	vawue8 = wtw_wead8(wtwdev, WEG_H2C_INFO);
	vawue8 = (u8)((vawue8 & 0xFB) | 0x04);
	wtw_wwite8(wtwdev, WEG_H2C_INFO, vawue8);

	vawue8 = wtw_wead8(wtwdev, WEG_TXDMA_OFFSET_CHK + 1);
	vawue8 = (u8)((vawue8 & 0x7f) | 0x80);
	wtw_wwite8(wtwdev, WEG_TXDMA_OFFSET_CHK + 1, vawue8);

	wp = wtw_wead32(wtwdev, WEG_H2C_PKT_WWITEADDW) & 0x3FFFF;
	wp = wtw_wead32(wtwdev, WEG_H2C_PKT_WEADADDW) & 0x3FFFF;
	h2cq_fwee = wp >= wp ? h2cq_size - (wp - wp) : wp - wp;

	if (h2cq_size != h2cq_fwee) {
		wtw_eww(wtwdev, "H2C queue mismatch\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wtw_init_twx_cfg(stwuct wtw_dev *wtwdev)
{
	int wet;

	wet = txdma_queue_mapping(wtwdev);
	if (wet)
		wetuwn wet;

	wet = pwiowity_queue_cfg(wtwdev);
	if (wet)
		wetuwn wet;

	wet = init_h2c(wtwdev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int wtw_dwv_info_cfg(stwuct wtw_dev *wtwdev)
{
	u8 vawue8;

	wtw_wwite8(wtwdev, WEG_WX_DWVINFO_SZ, PHY_STATUS_SIZE);
	if (wtw_chip_wcpu_11ac(wtwdev)) {
		vawue8 = wtw_wead8(wtwdev, WEG_TWXFF_BNDY + 1);
		vawue8 &= 0xF0;
		/* Fow wxdesc wen = 0 issue */
		vawue8 |= 0xF;
		wtw_wwite8(wtwdev, WEG_TWXFF_BNDY + 1, vawue8);
	}
	wtw_wwite32_set(wtwdev, WEG_WCW, BIT_APP_PHYSTS);
	wtw_wwite32_cww(wtwdev, WEG_WMAC_OPTION_FUNCTION + 4, BIT(8) | BIT(9));

	wetuwn 0;
}

int wtw_mac_init(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	int wet;

	wet = wtw_init_twx_cfg(wtwdev);
	if (wet)
		wetuwn wet;

	wet = chip->ops->mac_init(wtwdev);
	if (wet)
		wetuwn wet;

	wet = wtw_dwv_info_cfg(wtwdev);
	if (wet)
		wetuwn wet;

	wtw_hci_intewface_cfg(wtwdev);

	wetuwn 0;
}
