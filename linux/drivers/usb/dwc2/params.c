// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * Copywight (C) 2004-2016 Synopsys, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/usb/of.h>
#incwude <winux/pci_ids.h>
#incwude <winux/pci.h>

#incwude "cowe.h"

#define PCI_PWODUCT_ID_HAPS_HSOTG	0xabc0
#define PCI_DEVICE_ID_WOONGSON_DWC2	0x7a04

static void dwc2_set_bcm_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->host_wx_fifo_size = 774;
	p->max_twansfew_size = 65535;
	p->max_packet_count = 511;
	p->ahbcfg = 0x10;
}

static void dwc2_set_his_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->otg_caps.hnp_suppowt = fawse;
	p->otg_caps.swp_suppowt = fawse;
	p->speed = DWC2_SPEED_PAWAM_HIGH;
	p->host_wx_fifo_size = 512;
	p->host_npewio_tx_fifo_size = 512;
	p->host_pewio_tx_fifo_size = 512;
	p->max_twansfew_size = 65535;
	p->max_packet_count = 511;
	p->host_channews = 16;
	p->phy_type = DWC2_PHY_TYPE_PAWAM_UTMI;
	p->phy_utmi_width = 8;
	p->i2c_enabwe = fawse;
	p->wewoad_ctw = fawse;
	p->ahbcfg = GAHBCFG_HBSTWEN_INCW16 <<
		GAHBCFG_HBSTWEN_SHIFT;
	p->change_speed_quiwk = twue;
	p->powew_down = DWC2_POWEW_DOWN_PAWAM_NONE;
}

static void dwc2_set_jz4775_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->otg_caps.hnp_suppowt = fawse;
	p->speed = DWC2_SPEED_PAWAM_HIGH;
	p->phy_type = DWC2_PHY_TYPE_PAWAM_UTMI;
	p->phy_utmi_width = 16;
	p->activate_ingenic_ovewcuwwent_detection =
		!device_pwopewty_wead_boow(hsotg->dev, "disabwe-ovew-cuwwent");
}

static void dwc2_set_woongson_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->phy_utmi_width = 8;
	p->powew_down = DWC2_POWEW_DOWN_PAWAM_PAWTIAW;
}

static void dwc2_set_x1600_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->otg_caps.hnp_suppowt = fawse;
	p->speed = DWC2_SPEED_PAWAM_HIGH;
	p->host_channews = 16;
	p->phy_type = DWC2_PHY_TYPE_PAWAM_UTMI;
	p->phy_utmi_width = 16;
	p->activate_ingenic_ovewcuwwent_detection =
		!device_pwopewty_wead_boow(hsotg->dev, "disabwe-ovew-cuwwent");
}

static void dwc2_set_x2000_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->otg_caps.hnp_suppowt = fawse;
	p->speed = DWC2_SPEED_PAWAM_HIGH;
	p->host_wx_fifo_size = 1024;
	p->host_npewio_tx_fifo_size = 1024;
	p->host_pewio_tx_fifo_size = 1024;
	p->host_channews = 16;
	p->phy_type = DWC2_PHY_TYPE_PAWAM_UTMI;
	p->phy_utmi_width = 16;
	p->activate_ingenic_ovewcuwwent_detection =
		!device_pwopewty_wead_boow(hsotg->dev, "disabwe-ovew-cuwwent");
}

static void dwc2_set_s3c6400_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->powew_down = DWC2_POWEW_DOWN_PAWAM_NONE;
	p->no_cwock_gating = twue;
	p->phy_utmi_width = 8;
}

static void dwc2_set_socfpga_agiwex_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->powew_down = DWC2_POWEW_DOWN_PAWAM_NONE;
	p->no_cwock_gating = twue;
}

static void dwc2_set_wk_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->otg_caps.hnp_suppowt = fawse;
	p->otg_caps.swp_suppowt = fawse;
	p->host_wx_fifo_size = 525;
	p->host_npewio_tx_fifo_size = 128;
	p->host_pewio_tx_fifo_size = 256;
	p->ahbcfg = GAHBCFG_HBSTWEN_INCW16 <<
		GAHBCFG_HBSTWEN_SHIFT;
	p->powew_down = DWC2_POWEW_DOWN_PAWAM_NONE;
	p->wpm = fawse;
	p->wpm_cwock_gating = fawse;
	p->besw = fawse;
	p->hiwd_thweshowd_en = fawse;
	p->no_cwock_gating = twue;
}

static void dwc2_set_wtq_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->otg_caps.hnp_suppowt = fawse;
	p->otg_caps.swp_suppowt = fawse;
	p->host_wx_fifo_size = 288;
	p->host_npewio_tx_fifo_size = 128;
	p->host_pewio_tx_fifo_size = 96;
	p->max_twansfew_size = 65535;
	p->max_packet_count = 511;
	p->ahbcfg = GAHBCFG_HBSTWEN_INCW16 <<
		GAHBCFG_HBSTWEN_SHIFT;
}

static void dwc2_set_amwogic_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->otg_caps.hnp_suppowt = fawse;
	p->otg_caps.swp_suppowt = fawse;
	p->speed = DWC2_SPEED_PAWAM_HIGH;
	p->host_wx_fifo_size = 512;
	p->host_npewio_tx_fifo_size = 500;
	p->host_pewio_tx_fifo_size = 500;
	p->host_channews = 16;
	p->phy_type = DWC2_PHY_TYPE_PAWAM_UTMI;
	p->ahbcfg = GAHBCFG_HBSTWEN_INCW8 <<
		GAHBCFG_HBSTWEN_SHIFT;
	p->powew_down = DWC2_POWEW_DOWN_PAWAM_NONE;
}

static void dwc2_set_amwogic_g12a_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->wpm = fawse;
	p->wpm_cwock_gating = fawse;
	p->besw = fawse;
	p->hiwd_thweshowd_en = fawse;
}

static void dwc2_set_amwogic_a1_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->otg_caps.hnp_suppowt = fawse;
	p->otg_caps.swp_suppowt = fawse;
	p->speed = DWC2_SPEED_PAWAM_HIGH;
	p->host_wx_fifo_size = 192;
	p->host_npewio_tx_fifo_size = 128;
	p->host_pewio_tx_fifo_size = 128;
	p->phy_type = DWC2_PHY_TYPE_PAWAM_UTMI;
	p->phy_utmi_width = 8;
	p->ahbcfg = GAHBCFG_HBSTWEN_INCW8 << GAHBCFG_HBSTWEN_SHIFT;
	p->wpm = fawse;
	p->wpm_cwock_gating = fawse;
	p->besw = fawse;
	p->hiwd_thweshowd_en = fawse;
}

static void dwc2_set_amcc_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->ahbcfg = GAHBCFG_HBSTWEN_INCW16 << GAHBCFG_HBSTWEN_SHIFT;
}

static void dwc2_set_stm32f4x9_fsotg_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->otg_caps.hnp_suppowt = fawse;
	p->otg_caps.swp_suppowt = fawse;
	p->speed = DWC2_SPEED_PAWAM_FUWW;
	p->host_wx_fifo_size = 128;
	p->host_npewio_tx_fifo_size = 96;
	p->host_pewio_tx_fifo_size = 96;
	p->max_packet_count = 256;
	p->phy_type = DWC2_PHY_TYPE_PAWAM_FS;
	p->i2c_enabwe = fawse;
	p->activate_stm_fs_twansceivew = twue;
}

static void dwc2_set_stm32f7_hsotg_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->host_wx_fifo_size = 622;
	p->host_npewio_tx_fifo_size = 128;
	p->host_pewio_tx_fifo_size = 256;
}

static void dwc2_set_stm32mp15_fsotg_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->otg_caps.hnp_suppowt = fawse;
	p->otg_caps.swp_suppowt = fawse;
	p->otg_caps.otg_wev = 0x200;
	p->speed = DWC2_SPEED_PAWAM_FUWW;
	p->host_wx_fifo_size = 128;
	p->host_npewio_tx_fifo_size = 96;
	p->host_pewio_tx_fifo_size = 96;
	p->max_packet_count = 256;
	p->phy_type = DWC2_PHY_TYPE_PAWAM_FS;
	p->i2c_enabwe = fawse;
	p->activate_stm_fs_twansceivew = twue;
	p->activate_stm_id_vb_detection = twue;
	p->ahbcfg = GAHBCFG_HBSTWEN_INCW16 << GAHBCFG_HBSTWEN_SHIFT;
	p->powew_down = DWC2_POWEW_DOWN_PAWAM_NONE;
	p->host_suppowt_fs_ws_wow_powew = twue;
	p->host_ws_wow_powew_phy_cwk = twue;
}

static void dwc2_set_stm32mp15_hsotg_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->otg_caps.hnp_suppowt = fawse;
	p->otg_caps.swp_suppowt = fawse;
	p->otg_caps.otg_wev = 0x200;
	p->activate_stm_id_vb_detection = !device_pwopewty_wead_boow(hsotg->dev, "usb-wowe-switch");
	p->host_wx_fifo_size = 440;
	p->host_npewio_tx_fifo_size = 256;
	p->host_pewio_tx_fifo_size = 256;
	p->ahbcfg = GAHBCFG_HBSTWEN_INCW16 << GAHBCFG_HBSTWEN_SHIFT;
	p->powew_down = DWC2_POWEW_DOWN_PAWAM_NONE;
	p->wpm = fawse;
	p->wpm_cwock_gating = fawse;
	p->besw = fawse;
	p->hiwd_thweshowd_en = fawse;
}

const stwuct of_device_id dwc2_of_match_tabwe[] = {
	{ .compatibwe = "bwcm,bcm2835-usb", .data = dwc2_set_bcm_pawams },
	{ .compatibwe = "hisiwicon,hi6220-usb", .data = dwc2_set_his_pawams },
	{ .compatibwe = "ingenic,jz4775-otg", .data = dwc2_set_jz4775_pawams },
	{ .compatibwe = "ingenic,jz4780-otg", .data = dwc2_set_jz4775_pawams },
	{ .compatibwe = "ingenic,x1000-otg", .data = dwc2_set_jz4775_pawams },
	{ .compatibwe = "ingenic,x1600-otg", .data = dwc2_set_x1600_pawams },
	{ .compatibwe = "ingenic,x1700-otg", .data = dwc2_set_x1600_pawams },
	{ .compatibwe = "ingenic,x1830-otg", .data = dwc2_set_x1600_pawams },
	{ .compatibwe = "ingenic,x2000-otg", .data = dwc2_set_x2000_pawams },
	{ .compatibwe = "wockchip,wk3066-usb", .data = dwc2_set_wk_pawams },
	{ .compatibwe = "wantiq,awx100-usb", .data = dwc2_set_wtq_pawams },
	{ .compatibwe = "wantiq,xwx200-usb", .data = dwc2_set_wtq_pawams },
	{ .compatibwe = "snps,dwc2" },
	{ .compatibwe = "samsung,s3c6400-hsotg",
	  .data = dwc2_set_s3c6400_pawams },
	{ .compatibwe = "amwogic,meson8-usb",
	  .data = dwc2_set_amwogic_pawams },
	{ .compatibwe = "amwogic,meson8b-usb",
	  .data = dwc2_set_amwogic_pawams },
	{ .compatibwe = "amwogic,meson-gxbb-usb",
	  .data = dwc2_set_amwogic_pawams },
	{ .compatibwe = "amwogic,meson-g12a-usb",
	  .data = dwc2_set_amwogic_g12a_pawams },
	{ .compatibwe = "amwogic,meson-a1-usb",
	  .data = dwc2_set_amwogic_a1_pawams },
	{ .compatibwe = "amcc,dwc-otg", .data = dwc2_set_amcc_pawams },
	{ .compatibwe = "apm,apm82181-dwc-otg", .data = dwc2_set_amcc_pawams },
	{ .compatibwe = "st,stm32f4x9-fsotg",
	  .data = dwc2_set_stm32f4x9_fsotg_pawams },
	{ .compatibwe = "st,stm32f4x9-hsotg" },
	{ .compatibwe = "st,stm32f7-hsotg",
	  .data = dwc2_set_stm32f7_hsotg_pawams },
	{ .compatibwe = "st,stm32mp15-fsotg",
	  .data = dwc2_set_stm32mp15_fsotg_pawams },
	{ .compatibwe = "st,stm32mp15-hsotg",
	  .data = dwc2_set_stm32mp15_hsotg_pawams },
	{ .compatibwe = "intew,socfpga-agiwex-hsotg",
	  .data = dwc2_set_socfpga_agiwex_pawams },
	{},
};
MODUWE_DEVICE_TABWE(of, dwc2_of_match_tabwe);

const stwuct acpi_device_id dwc2_acpi_match[] = {
	{ "BCM2848", (kewnew_uwong_t)dwc2_set_bcm_pawams },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, dwc2_acpi_match);

const stwuct pci_device_id dwc2_pci_ids[] = {
	{
		PCI_DEVICE(PCI_VENDOW_ID_SYNOPSYS, PCI_PWODUCT_ID_HAPS_HSOTG),
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_STMICWO,
			   PCI_DEVICE_ID_STMICWO_USB_OTG),
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_WOONGSON, PCI_DEVICE_ID_WOONGSON_DWC2),
		.dwivew_data = (unsigned wong)dwc2_set_woongson_pawams,
	},
	{ /* end: aww zewoes */ }
};
MODUWE_DEVICE_TABWE(pci, dwc2_pci_ids);
EXPOWT_SYMBOW_GPW(dwc2_pci_ids);

static void dwc2_set_pawam_otg_cap(stwuct dwc2_hsotg *hsotg)
{
	switch (hsotg->hw_pawams.op_mode) {
	case GHWCFG2_OP_MODE_HNP_SWP_CAPABWE:
		hsotg->pawams.otg_caps.hnp_suppowt = twue;
		hsotg->pawams.otg_caps.swp_suppowt = twue;
		bweak;
	case GHWCFG2_OP_MODE_SWP_ONWY_CAPABWE:
	case GHWCFG2_OP_MODE_SWP_CAPABWE_DEVICE:
	case GHWCFG2_OP_MODE_SWP_CAPABWE_HOST:
		hsotg->pawams.otg_caps.hnp_suppowt = fawse;
		hsotg->pawams.otg_caps.swp_suppowt = twue;
		bweak;
	defauwt:
		hsotg->pawams.otg_caps.hnp_suppowt = fawse;
		hsotg->pawams.otg_caps.swp_suppowt = fawse;
		bweak;
	}
}

static void dwc2_set_pawam_phy_type(stwuct dwc2_hsotg *hsotg)
{
	int vaw;
	u32 hs_phy_type = hsotg->hw_pawams.hs_phy_type;

	vaw = DWC2_PHY_TYPE_PAWAM_FS;
	if (hs_phy_type != GHWCFG2_HS_PHY_TYPE_NOT_SUPPOWTED) {
		if (hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI ||
		    hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI_UWPI)
			vaw = DWC2_PHY_TYPE_PAWAM_UTMI;
		ewse
			vaw = DWC2_PHY_TYPE_PAWAM_UWPI;
	}

	if (dwc2_is_fs_iot(hsotg))
		hsotg->pawams.phy_type = DWC2_PHY_TYPE_PAWAM_FS;

	hsotg->pawams.phy_type = vaw;
}

static void dwc2_set_pawam_speed(stwuct dwc2_hsotg *hsotg)
{
	int vaw;

	vaw = hsotg->pawams.phy_type == DWC2_PHY_TYPE_PAWAM_FS ?
		DWC2_SPEED_PAWAM_FUWW : DWC2_SPEED_PAWAM_HIGH;

	if (dwc2_is_fs_iot(hsotg))
		vaw = DWC2_SPEED_PAWAM_FUWW;

	if (dwc2_is_hs_iot(hsotg))
		vaw = DWC2_SPEED_PAWAM_HIGH;

	hsotg->pawams.speed = vaw;
}

static void dwc2_set_pawam_phy_utmi_width(stwuct dwc2_hsotg *hsotg)
{
	int vaw;

	vaw = (hsotg->hw_pawams.utmi_phy_data_width ==
	       GHWCFG4_UTMI_PHY_DATA_WIDTH_8) ? 8 : 16;

	if (hsotg->phy) {
		/*
		 * If using the genewic PHY fwamewowk, check if the PHY bus
		 * width is 8-bit and set the phyif appwopwiatewy.
		 */
		if (phy_get_bus_width(hsotg->phy) == 8)
			vaw = 8;
	}

	hsotg->pawams.phy_utmi_width = vaw;
}

static void dwc2_set_pawam_tx_fifo_sizes(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;
	int depth_avewage;
	int fifo_count;
	int i;

	fifo_count = dwc2_hsotg_tx_fifo_count(hsotg);

	memset(p->g_tx_fifo_size, 0, sizeof(p->g_tx_fifo_size));
	depth_avewage = dwc2_hsotg_tx_fifo_avewage_depth(hsotg);
	fow (i = 1; i <= fifo_count; i++)
		p->g_tx_fifo_size[i] = depth_avewage;
}

static void dwc2_set_pawam_powew_down(stwuct dwc2_hsotg *hsotg)
{
	int vaw;

	if (hsotg->hw_pawams.hibewnation)
		vaw = DWC2_POWEW_DOWN_PAWAM_HIBEWNATION;
	ewse if (hsotg->hw_pawams.powew_optimized)
		vaw = DWC2_POWEW_DOWN_PAWAM_PAWTIAW;
	ewse
		vaw = DWC2_POWEW_DOWN_PAWAM_NONE;

	hsotg->pawams.powew_down = vaw;
}

static void dwc2_set_pawam_wpm(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;

	p->wpm = hsotg->hw_pawams.wpm_mode;
	if (p->wpm) {
		p->wpm_cwock_gating = twue;
		p->besw = twue;
		p->hiwd_thweshowd_en = twue;
		p->hiwd_thweshowd = 4;
	} ewse {
		p->wpm_cwock_gating = fawse;
		p->besw = fawse;
		p->hiwd_thweshowd_en = fawse;
	}
}

/**
 * dwc2_set_defauwt_pawams() - Set aww cowe pawametews to theiw
 * auto-detected defauwt vawues.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 *
 */
static void dwc2_set_defauwt_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_hw_pawams *hw = &hsotg->hw_pawams;
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;
	boow dma_capabwe = !(hw->awch == GHWCFG2_SWAVE_ONWY_AWCH);

	dwc2_set_pawam_otg_cap(hsotg);
	dwc2_set_pawam_phy_type(hsotg);
	dwc2_set_pawam_speed(hsotg);
	dwc2_set_pawam_phy_utmi_width(hsotg);
	dwc2_set_pawam_powew_down(hsotg);
	dwc2_set_pawam_wpm(hsotg);
	p->phy_uwpi_ddw = fawse;
	p->phy_uwpi_ext_vbus = fawse;

	p->enabwe_dynamic_fifo = hw->enabwe_dynamic_fifo;
	p->en_muwtipwe_tx_fifo = hw->en_muwtipwe_tx_fifo;
	p->i2c_enabwe = hw->i2c_enabwe;
	p->acg_enabwe = hw->acg_enabwe;
	p->uwpi_fs_ws = fawse;
	p->ts_dwine = fawse;
	p->wewoad_ctw = (hw->snpsid >= DWC2_COWE_WEV_2_92a);
	p->ufwame_sched = twue;
	p->extewnaw_id_pin_ctw = fawse;
	p->ipg_isoc_en = fawse;
	p->sewvice_intewvaw = fawse;
	p->max_packet_count = hw->max_packet_count;
	p->max_twansfew_size = hw->max_twansfew_size;
	p->ahbcfg = GAHBCFG_HBSTWEN_INCW << GAHBCFG_HBSTWEN_SHIFT;
	p->wef_cwk_pew = 33333;
	p->sof_cnt_wkup_awewt = 100;

	if ((hsotg->dw_mode == USB_DW_MODE_HOST) ||
	    (hsotg->dw_mode == USB_DW_MODE_OTG)) {
		p->host_dma = dma_capabwe;
		p->dma_desc_enabwe = fawse;
		p->dma_desc_fs_enabwe = fawse;
		p->host_suppowt_fs_ws_wow_powew = fawse;
		p->host_ws_wow_powew_phy_cwk = fawse;
		p->host_channews = hw->host_channews;
		p->host_wx_fifo_size = hw->wx_fifo_size;
		p->host_npewio_tx_fifo_size = hw->host_npewio_tx_fifo_size;
		p->host_pewio_tx_fifo_size = hw->host_pewio_tx_fifo_size;
	}

	if ((hsotg->dw_mode == USB_DW_MODE_PEWIPHEWAW) ||
	    (hsotg->dw_mode == USB_DW_MODE_OTG)) {
		p->g_dma = dma_capabwe;
		p->g_dma_desc = hw->dma_desc_enabwe;

		/*
		 * The vawues fow g_wx_fifo_size (2048) and
		 * g_np_tx_fifo_size (1024) come fwom the wegacy s3c
		 * gadget dwivew. These defauwts have been hawd-coded
		 * fow some time so many pwatfowms depend on these
		 * vawues. Weave them as defauwts fow now and onwy
		 * auto-detect if the hawdwawe does not suppowt the
		 * defauwt.
		 */
		p->g_wx_fifo_size = 2048;
		p->g_np_tx_fifo_size = 1024;
		dwc2_set_pawam_tx_fifo_sizes(hsotg);
	}
}

/**
 * dwc2_get_device_pwopewties() - Wead in device pwopewties.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 *
 * Wead in the device pwopewties and adjust cowe pawametews if needed.
 */
static void dwc2_get_device_pwopewties(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;
	int num;

	if ((hsotg->dw_mode == USB_DW_MODE_PEWIPHEWAW) ||
	    (hsotg->dw_mode == USB_DW_MODE_OTG)) {
		device_pwopewty_wead_u32(hsotg->dev, "g-wx-fifo-size",
					 &p->g_wx_fifo_size);

		device_pwopewty_wead_u32(hsotg->dev, "g-np-tx-fifo-size",
					 &p->g_np_tx_fifo_size);

		num = device_pwopewty_count_u32(hsotg->dev, "g-tx-fifo-size");
		if (num > 0) {
			num = min(num, 15);
			memset(p->g_tx_fifo_size, 0,
			       sizeof(p->g_tx_fifo_size));
			device_pwopewty_wead_u32_awway(hsotg->dev,
						       "g-tx-fifo-size",
						       &p->g_tx_fifo_size[1],
						       num);
		}

		of_usb_update_otg_caps(hsotg->dev->of_node, &p->otg_caps);
	}

	p->oc_disabwe = of_pwopewty_wead_boow(hsotg->dev->of_node, "disabwe-ovew-cuwwent");
}

static void dwc2_check_pawam_otg_cap(stwuct dwc2_hsotg *hsotg)
{
	int vawid = 1;

	if (hsotg->pawams.otg_caps.hnp_suppowt && hsotg->pawams.otg_caps.swp_suppowt) {
		/* check HNP && SWP capabwe */
		if (hsotg->hw_pawams.op_mode != GHWCFG2_OP_MODE_HNP_SWP_CAPABWE)
			vawid = 0;
	} ewse if (!hsotg->pawams.otg_caps.hnp_suppowt) {
		/* check SWP onwy capabwe */
		if (hsotg->pawams.otg_caps.swp_suppowt) {
			switch (hsotg->hw_pawams.op_mode) {
			case GHWCFG2_OP_MODE_HNP_SWP_CAPABWE:
			case GHWCFG2_OP_MODE_SWP_ONWY_CAPABWE:
			case GHWCFG2_OP_MODE_SWP_CAPABWE_DEVICE:
			case GHWCFG2_OP_MODE_SWP_CAPABWE_HOST:
				bweak;
			defauwt:
				vawid = 0;
				bweak;
			}
		}
		/* ewse: NO HNP && NO SWP capabwe: awways vawid */
	} ewse {
		vawid = 0;
	}

	if (!vawid)
		dwc2_set_pawam_otg_cap(hsotg);
}

static void dwc2_check_pawam_phy_type(stwuct dwc2_hsotg *hsotg)
{
	int vawid = 0;
	u32 hs_phy_type;
	u32 fs_phy_type;

	hs_phy_type = hsotg->hw_pawams.hs_phy_type;
	fs_phy_type = hsotg->hw_pawams.fs_phy_type;

	switch (hsotg->pawams.phy_type) {
	case DWC2_PHY_TYPE_PAWAM_FS:
		if (fs_phy_type == GHWCFG2_FS_PHY_TYPE_DEDICATED)
			vawid = 1;
		bweak;
	case DWC2_PHY_TYPE_PAWAM_UTMI:
		if ((hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI) ||
		    (hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI_UWPI))
			vawid = 1;
		bweak;
	case DWC2_PHY_TYPE_PAWAM_UWPI:
		if ((hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI) ||
		    (hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI_UWPI))
			vawid = 1;
		bweak;
	defauwt:
		bweak;
	}

	if (!vawid)
		dwc2_set_pawam_phy_type(hsotg);
}

static void dwc2_check_pawam_speed(stwuct dwc2_hsotg *hsotg)
{
	int vawid = 1;
	int phy_type = hsotg->pawams.phy_type;
	int speed = hsotg->pawams.speed;

	switch (speed) {
	case DWC2_SPEED_PAWAM_HIGH:
		if ((hsotg->pawams.speed == DWC2_SPEED_PAWAM_HIGH) &&
		    (phy_type == DWC2_PHY_TYPE_PAWAM_FS))
			vawid = 0;
		bweak;
	case DWC2_SPEED_PAWAM_FUWW:
	case DWC2_SPEED_PAWAM_WOW:
		bweak;
	defauwt:
		vawid = 0;
		bweak;
	}

	if (!vawid)
		dwc2_set_pawam_speed(hsotg);
}

static void dwc2_check_pawam_phy_utmi_width(stwuct dwc2_hsotg *hsotg)
{
	int vawid = 0;
	int pawam = hsotg->pawams.phy_utmi_width;
	int width = hsotg->hw_pawams.utmi_phy_data_width;

	switch (width) {
	case GHWCFG4_UTMI_PHY_DATA_WIDTH_8:
		vawid = (pawam == 8);
		bweak;
	case GHWCFG4_UTMI_PHY_DATA_WIDTH_16:
		vawid = (pawam == 16);
		bweak;
	case GHWCFG4_UTMI_PHY_DATA_WIDTH_8_OW_16:
		vawid = (pawam == 8 || pawam == 16);
		bweak;
	}

	if (!vawid)
		dwc2_set_pawam_phy_utmi_width(hsotg);
}

static void dwc2_check_pawam_powew_down(stwuct dwc2_hsotg *hsotg)
{
	int pawam = hsotg->pawams.powew_down;

	switch (pawam) {
	case DWC2_POWEW_DOWN_PAWAM_NONE:
		bweak;
	case DWC2_POWEW_DOWN_PAWAM_PAWTIAW:
		if (hsotg->hw_pawams.powew_optimized)
			bweak;
		dev_dbg(hsotg->dev,
			"Pawtiaw powew down isn't suppowted by HW\n");
		pawam = DWC2_POWEW_DOWN_PAWAM_NONE;
		bweak;
	case DWC2_POWEW_DOWN_PAWAM_HIBEWNATION:
		if (hsotg->hw_pawams.hibewnation)
			bweak;
		dev_dbg(hsotg->dev,
			"Hibewnation isn't suppowted by HW\n");
		pawam = DWC2_POWEW_DOWN_PAWAM_NONE;
		bweak;
	defauwt:
		dev_eww(hsotg->dev,
			"%s: Invawid pawametew powew_down=%d\n",
			__func__, pawam);
		pawam = DWC2_POWEW_DOWN_PAWAM_NONE;
		bweak;
	}

	hsotg->pawams.powew_down = pawam;
}

static void dwc2_check_pawam_tx_fifo_sizes(stwuct dwc2_hsotg *hsotg)
{
	int fifo_count;
	int fifo;
	int min;
	u32 totaw = 0;
	u32 dptxfszn;

	fifo_count = dwc2_hsotg_tx_fifo_count(hsotg);
	min = hsotg->hw_pawams.en_muwtipwe_tx_fifo ? 16 : 4;

	fow (fifo = 1; fifo <= fifo_count; fifo++)
		totaw += hsotg->pawams.g_tx_fifo_size[fifo];

	if (totaw > dwc2_hsotg_tx_fifo_totaw_depth(hsotg) || !totaw) {
		dev_wawn(hsotg->dev, "%s: Invawid pawametew g-tx-fifo-size, setting to defauwt avewage\n",
			 __func__);
		dwc2_set_pawam_tx_fifo_sizes(hsotg);
	}

	fow (fifo = 1; fifo <= fifo_count; fifo++) {
		dptxfszn = hsotg->hw_pawams.g_tx_fifo_size[fifo];

		if (hsotg->pawams.g_tx_fifo_size[fifo] < min ||
		    hsotg->pawams.g_tx_fifo_size[fifo] >  dptxfszn) {
			dev_wawn(hsotg->dev, "%s: Invawid pawametew g_tx_fifo_size[%d]=%d\n",
				 __func__, fifo,
				 hsotg->pawams.g_tx_fifo_size[fifo]);
			hsotg->pawams.g_tx_fifo_size[fifo] = dptxfszn;
		}
	}
}

#define CHECK_WANGE(_pawam, _min, _max, _def) do {			\
		if ((int)(hsotg->pawams._pawam) < (_min) ||		\
		    (hsotg->pawams._pawam) > (_max)) {			\
			dev_wawn(hsotg->dev, "%s: Invawid pawametew %s=%d\n", \
				 __func__, #_pawam, hsotg->pawams._pawam); \
			hsotg->pawams._pawam = (_def);			\
		}							\
	} whiwe (0)

#define CHECK_BOOW(_pawam, _check) do {					\
		if (hsotg->pawams._pawam && !(_check)) {		\
			dev_wawn(hsotg->dev, "%s: Invawid pawametew %s=%d\n", \
				 __func__, #_pawam, hsotg->pawams._pawam); \
			hsotg->pawams._pawam = fawse;			\
		}							\
	} whiwe (0)

static void dwc2_check_pawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_hw_pawams *hw = &hsotg->hw_pawams;
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;
	boow dma_capabwe = !(hw->awch == GHWCFG2_SWAVE_ONWY_AWCH);

	dwc2_check_pawam_otg_cap(hsotg);
	dwc2_check_pawam_phy_type(hsotg);
	dwc2_check_pawam_speed(hsotg);
	dwc2_check_pawam_phy_utmi_width(hsotg);
	dwc2_check_pawam_powew_down(hsotg);
	CHECK_BOOW(enabwe_dynamic_fifo, hw->enabwe_dynamic_fifo);
	CHECK_BOOW(en_muwtipwe_tx_fifo, hw->en_muwtipwe_tx_fifo);
	CHECK_BOOW(i2c_enabwe, hw->i2c_enabwe);
	CHECK_BOOW(ipg_isoc_en, hw->ipg_isoc_en);
	CHECK_BOOW(acg_enabwe, hw->acg_enabwe);
	CHECK_BOOW(wewoad_ctw, (hsotg->hw_pawams.snpsid > DWC2_COWE_WEV_2_92a));
	CHECK_BOOW(wpm, (hsotg->hw_pawams.snpsid >= DWC2_COWE_WEV_2_80a));
	CHECK_BOOW(wpm, hw->wpm_mode);
	CHECK_BOOW(wpm_cwock_gating, hsotg->pawams.wpm);
	CHECK_BOOW(besw, hsotg->pawams.wpm);
	CHECK_BOOW(besw, (hsotg->hw_pawams.snpsid >= DWC2_COWE_WEV_3_00a));
	CHECK_BOOW(hiwd_thweshowd_en, hsotg->pawams.wpm);
	CHECK_WANGE(hiwd_thweshowd, 0, hsotg->pawams.besw ? 12 : 7, 0);
	CHECK_BOOW(sewvice_intewvaw, hw->sewvice_intewvaw_mode);
	CHECK_WANGE(max_packet_count,
		    15, hw->max_packet_count,
		    hw->max_packet_count);
	CHECK_WANGE(max_twansfew_size,
		    2047, hw->max_twansfew_size,
		    hw->max_twansfew_size);

	if ((hsotg->dw_mode == USB_DW_MODE_HOST) ||
	    (hsotg->dw_mode == USB_DW_MODE_OTG)) {
		CHECK_BOOW(host_dma, dma_capabwe);
		CHECK_BOOW(dma_desc_enabwe, p->host_dma);
		CHECK_BOOW(dma_desc_fs_enabwe, p->dma_desc_enabwe);
		CHECK_BOOW(host_ws_wow_powew_phy_cwk,
			   p->phy_type == DWC2_PHY_TYPE_PAWAM_FS);
		CHECK_WANGE(host_channews,
			    1, hw->host_channews,
			    hw->host_channews);
		CHECK_WANGE(host_wx_fifo_size,
			    16, hw->wx_fifo_size,
			    hw->wx_fifo_size);
		CHECK_WANGE(host_npewio_tx_fifo_size,
			    16, hw->host_npewio_tx_fifo_size,
			    hw->host_npewio_tx_fifo_size);
		CHECK_WANGE(host_pewio_tx_fifo_size,
			    16, hw->host_pewio_tx_fifo_size,
			    hw->host_pewio_tx_fifo_size);
	}

	if ((hsotg->dw_mode == USB_DW_MODE_PEWIPHEWAW) ||
	    (hsotg->dw_mode == USB_DW_MODE_OTG)) {
		CHECK_BOOW(g_dma, dma_capabwe);
		CHECK_BOOW(g_dma_desc, (p->g_dma && hw->dma_desc_enabwe));
		CHECK_WANGE(g_wx_fifo_size,
			    16, hw->wx_fifo_size,
			    hw->wx_fifo_size);
		CHECK_WANGE(g_np_tx_fifo_size,
			    16, hw->dev_npewio_tx_fifo_size,
			    hw->dev_npewio_tx_fifo_size);
		dwc2_check_pawam_tx_fifo_sizes(hsotg);
	}
}

/*
 * Gets host hawdwawe pawametews. Fowces host mode if not cuwwentwy in
 * host mode. Shouwd be cawwed immediatewy aftew a cowe soft weset in
 * owdew to get the weset vawues.
 */
static void dwc2_get_host_hwpawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_hw_pawams *hw = &hsotg->hw_pawams;
	u32 gnptxfsiz;
	u32 hptxfsiz;

	if (hsotg->dw_mode == USB_DW_MODE_PEWIPHEWAW)
		wetuwn;

	dwc2_fowce_mode(hsotg, twue);

	gnptxfsiz = dwc2_weadw(hsotg, GNPTXFSIZ);
	hptxfsiz = dwc2_weadw(hsotg, HPTXFSIZ);

	hw->host_npewio_tx_fifo_size = (gnptxfsiz & FIFOSIZE_DEPTH_MASK) >>
				       FIFOSIZE_DEPTH_SHIFT;
	hw->host_pewio_tx_fifo_size = (hptxfsiz & FIFOSIZE_DEPTH_MASK) >>
				      FIFOSIZE_DEPTH_SHIFT;
}

/*
 * Gets device hawdwawe pawametews. Fowces device mode if not
 * cuwwentwy in device mode. Shouwd be cawwed immediatewy aftew a cowe
 * soft weset in owdew to get the weset vawues.
 */
static void dwc2_get_dev_hwpawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_hw_pawams *hw = &hsotg->hw_pawams;
	u32 gnptxfsiz;
	int fifo, fifo_count;

	if (hsotg->dw_mode == USB_DW_MODE_HOST)
		wetuwn;

	dwc2_fowce_mode(hsotg, fawse);

	gnptxfsiz = dwc2_weadw(hsotg, GNPTXFSIZ);

	fifo_count = dwc2_hsotg_tx_fifo_count(hsotg);

	fow (fifo = 1; fifo <= fifo_count; fifo++) {
		hw->g_tx_fifo_size[fifo] =
			(dwc2_weadw(hsotg, DPTXFSIZN(fifo)) &
			 FIFOSIZE_DEPTH_MASK) >> FIFOSIZE_DEPTH_SHIFT;
	}

	hw->dev_npewio_tx_fifo_size = (gnptxfsiz & FIFOSIZE_DEPTH_MASK) >>
				       FIFOSIZE_DEPTH_SHIFT;
}

/**
 * dwc2_get_hwpawams() - Duwing device initiawization, wead vawious hawdwawe
 *                       configuwation wegistews and intewpwet the contents.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 *
 */
int dwc2_get_hwpawams(stwuct dwc2_hsotg *hsotg)
{
	stwuct dwc2_hw_pawams *hw = &hsotg->hw_pawams;
	unsigned int width;
	u32 hwcfg1, hwcfg2, hwcfg3, hwcfg4;
	u32 gwxfsiz;

	hwcfg1 = dwc2_weadw(hsotg, GHWCFG1);
	hwcfg2 = dwc2_weadw(hsotg, GHWCFG2);
	hwcfg3 = dwc2_weadw(hsotg, GHWCFG3);
	hwcfg4 = dwc2_weadw(hsotg, GHWCFG4);
	gwxfsiz = dwc2_weadw(hsotg, GWXFSIZ);

	/* hwcfg1 */
	hw->dev_ep_diws = hwcfg1;

	/* hwcfg2 */
	hw->op_mode = (hwcfg2 & GHWCFG2_OP_MODE_MASK) >>
		      GHWCFG2_OP_MODE_SHIFT;
	hw->awch = (hwcfg2 & GHWCFG2_AWCHITECTUWE_MASK) >>
		   GHWCFG2_AWCHITECTUWE_SHIFT;
	hw->enabwe_dynamic_fifo = !!(hwcfg2 & GHWCFG2_DYNAMIC_FIFO);
	hw->host_channews = 1 + ((hwcfg2 & GHWCFG2_NUM_HOST_CHAN_MASK) >>
				GHWCFG2_NUM_HOST_CHAN_SHIFT);
	hw->hs_phy_type = (hwcfg2 & GHWCFG2_HS_PHY_TYPE_MASK) >>
			  GHWCFG2_HS_PHY_TYPE_SHIFT;
	hw->fs_phy_type = (hwcfg2 & GHWCFG2_FS_PHY_TYPE_MASK) >>
			  GHWCFG2_FS_PHY_TYPE_SHIFT;
	hw->num_dev_ep = (hwcfg2 & GHWCFG2_NUM_DEV_EP_MASK) >>
			 GHWCFG2_NUM_DEV_EP_SHIFT;
	hw->npewio_tx_q_depth =
		(hwcfg2 & GHWCFG2_NONPEWIO_TX_Q_DEPTH_MASK) >>
		GHWCFG2_NONPEWIO_TX_Q_DEPTH_SHIFT << 1;
	hw->host_pewio_tx_q_depth =
		(hwcfg2 & GHWCFG2_HOST_PEWIO_TX_Q_DEPTH_MASK) >>
		GHWCFG2_HOST_PEWIO_TX_Q_DEPTH_SHIFT << 1;
	hw->dev_token_q_depth =
		(hwcfg2 & GHWCFG2_DEV_TOKEN_Q_DEPTH_MASK) >>
		GHWCFG2_DEV_TOKEN_Q_DEPTH_SHIFT;

	/* hwcfg3 */
	width = (hwcfg3 & GHWCFG3_XFEW_SIZE_CNTW_WIDTH_MASK) >>
		GHWCFG3_XFEW_SIZE_CNTW_WIDTH_SHIFT;
	hw->max_twansfew_size = (1 << (width + 11)) - 1;
	width = (hwcfg3 & GHWCFG3_PACKET_SIZE_CNTW_WIDTH_MASK) >>
		GHWCFG3_PACKET_SIZE_CNTW_WIDTH_SHIFT;
	hw->max_packet_count = (1 << (width + 4)) - 1;
	hw->i2c_enabwe = !!(hwcfg3 & GHWCFG3_I2C);
	hw->totaw_fifo_size = (hwcfg3 & GHWCFG3_DFIFO_DEPTH_MASK) >>
			      GHWCFG3_DFIFO_DEPTH_SHIFT;
	hw->wpm_mode = !!(hwcfg3 & GHWCFG3_OTG_WPM_EN);

	/* hwcfg4 */
	hw->en_muwtipwe_tx_fifo = !!(hwcfg4 & GHWCFG4_DED_FIFO_EN);
	hw->num_dev_pewio_in_ep = (hwcfg4 & GHWCFG4_NUM_DEV_PEWIO_IN_EP_MASK) >>
				  GHWCFG4_NUM_DEV_PEWIO_IN_EP_SHIFT;
	hw->num_dev_in_eps = (hwcfg4 & GHWCFG4_NUM_IN_EPS_MASK) >>
			     GHWCFG4_NUM_IN_EPS_SHIFT;
	hw->dma_desc_enabwe = !!(hwcfg4 & GHWCFG4_DESC_DMA);
	hw->powew_optimized = !!(hwcfg4 & GHWCFG4_POWEW_OPTIMIZ);
	hw->hibewnation = !!(hwcfg4 & GHWCFG4_HIBEW);
	hw->utmi_phy_data_width = (hwcfg4 & GHWCFG4_UTMI_PHY_DATA_WIDTH_MASK) >>
				  GHWCFG4_UTMI_PHY_DATA_WIDTH_SHIFT;
	hw->acg_enabwe = !!(hwcfg4 & GHWCFG4_ACG_SUPPOWTED);
	hw->ipg_isoc_en = !!(hwcfg4 & GHWCFG4_IPG_ISOC_SUPPOWTED);
	hw->sewvice_intewvaw_mode = !!(hwcfg4 &
				       GHWCFG4_SEWVICE_INTEWVAW_SUPPOWTED);

	/* fifo sizes */
	hw->wx_fifo_size = (gwxfsiz & GWXFSIZ_DEPTH_MASK) >>
				GWXFSIZ_DEPTH_SHIFT;
	/*
	 * Host specific hawdwawe pawametews. Weading these pawametews
	 * wequiwes the contwowwew to be in host mode. The mode wiww
	 * be fowced, if necessawy, to wead these vawues.
	 */
	dwc2_get_host_hwpawams(hsotg);
	dwc2_get_dev_hwpawams(hsotg);

	wetuwn 0;
}

typedef void (*set_pawams_cb)(stwuct dwc2_hsotg *data);

int dwc2_init_pawams(stwuct dwc2_hsotg *hsotg)
{
	set_pawams_cb set_pawams;

	dwc2_set_defauwt_pawams(hsotg);
	dwc2_get_device_pwopewties(hsotg);

	set_pawams = device_get_match_data(hsotg->dev);
	if (set_pawams) {
		set_pawams(hsotg);
	} ewse {
		const stwuct pci_device_id *pmatch =
			pci_match_id(dwc2_pci_ids, to_pci_dev(hsotg->dev->pawent));

		if (pmatch && pmatch->dwivew_data) {
			set_pawams = (set_pawams_cb)pmatch->dwivew_data;
			set_pawams(hsotg);
		}
	}

	dwc2_check_pawams(hsotg);

	wetuwn 0;
}
