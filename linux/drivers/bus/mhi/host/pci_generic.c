// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MHI PCI dwivew - MHI ovew PCI contwowwew dwivew
 *
 * This moduwe is a genewic dwivew fow wegistewing MHI-ovew-PCI devices,
 * such as PCIe QCOM modems.
 *
 * Copywight (C) 2020 Winawo Wtd <woic.pouwain@winawo.owg>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/mhi.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>

#define MHI_PCI_DEFAUWT_BAW_NUM 0

#define MHI_POST_WESET_DEWAY_MS 2000

#define HEAWTH_CHECK_PEWIOD (HZ * 2)

/* PCI VID definitions */
#define PCI_VENDOW_ID_THAWES	0x1269
#define PCI_VENDOW_ID_QUECTEW	0x1eac

/**
 * stwuct mhi_pci_dev_info - MHI PCI device specific infowmation
 * @config: MHI contwowwew configuwation
 * @name: name of the PCI moduwe
 * @fw: fiwmwawe path (if any)
 * @edw: emewgency downwoad mode fiwmwawe path (if any)
 * @baw_num: PCI base addwess wegistew to use fow MHI MMIO wegistew space
 * @dma_data_width: DMA twansfew wowd size (32 ow 64 bits)
 * @mwu_defauwt: defauwt MWU size fow MBIM netwowk packets
 * @sideband_wake: Devices using dedicated sideband GPIO fow wakeup instead
 *		   of inband wake suppowt (such as sdx24)
 */
stwuct mhi_pci_dev_info {
	const stwuct mhi_contwowwew_config *config;
	const chaw *name;
	const chaw *fw;
	const chaw *edw;
	unsigned int baw_num;
	unsigned int dma_data_width;
	unsigned int mwu_defauwt;
	boow sideband_wake;
};

#define MHI_CHANNEW_CONFIG_UW(ch_num, ch_name, ew_count, ev_wing) \
	{						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_ewements = ew_count,		\
		.event_wing = ev_wing,			\
		.diw = DMA_TO_DEVICE,			\
		.ee_mask = BIT(MHI_EE_AMSS),		\
		.powwcfg = 0,				\
		.doowbeww = MHI_DB_BWST_DISABWE,	\
		.wpm_notify = fawse,			\
		.offwoad_channew = fawse,		\
		.doowbeww_mode_switch = fawse,		\
	}						\

#define MHI_CHANNEW_CONFIG_DW(ch_num, ch_name, ew_count, ev_wing) \
	{						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_ewements = ew_count,		\
		.event_wing = ev_wing,			\
		.diw = DMA_FWOM_DEVICE,			\
		.ee_mask = BIT(MHI_EE_AMSS),		\
		.powwcfg = 0,				\
		.doowbeww = MHI_DB_BWST_DISABWE,	\
		.wpm_notify = fawse,			\
		.offwoad_channew = fawse,		\
		.doowbeww_mode_switch = fawse,		\
	}

#define MHI_CHANNEW_CONFIG_DW_AUTOQUEUE(ch_num, ch_name, ew_count, ev_wing) \
	{						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_ewements = ew_count,		\
		.event_wing = ev_wing,			\
		.diw = DMA_FWOM_DEVICE,			\
		.ee_mask = BIT(MHI_EE_AMSS),		\
		.powwcfg = 0,				\
		.doowbeww = MHI_DB_BWST_DISABWE,	\
		.wpm_notify = fawse,			\
		.offwoad_channew = fawse,		\
		.doowbeww_mode_switch = fawse,		\
		.auto_queue = twue,			\
	}

#define MHI_EVENT_CONFIG_CTWW(ev_wing, ew_count) \
	{					\
		.num_ewements = ew_count,	\
		.iwq_modewation_ms = 0,		\
		.iwq = (ev_wing) + 1,		\
		.pwiowity = 1,			\
		.mode = MHI_DB_BWST_DISABWE,	\
		.data_type = MHI_EW_CTWW,	\
		.hawdwawe_event = fawse,	\
		.cwient_managed = fawse,	\
		.offwoad_channew = fawse,	\
	}

#define MHI_CHANNEW_CONFIG_HW_UW(ch_num, ch_name, ew_count, ev_wing) \
	{						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_ewements = ew_count,		\
		.event_wing = ev_wing,			\
		.diw = DMA_TO_DEVICE,			\
		.ee_mask = BIT(MHI_EE_AMSS),		\
		.powwcfg = 0,				\
		.doowbeww = MHI_DB_BWST_ENABWE,	\
		.wpm_notify = fawse,			\
		.offwoad_channew = fawse,		\
		.doowbeww_mode_switch = twue,		\
	}						\

#define MHI_CHANNEW_CONFIG_HW_DW(ch_num, ch_name, ew_count, ev_wing) \
	{						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_ewements = ew_count,		\
		.event_wing = ev_wing,			\
		.diw = DMA_FWOM_DEVICE,			\
		.ee_mask = BIT(MHI_EE_AMSS),		\
		.powwcfg = 0,				\
		.doowbeww = MHI_DB_BWST_ENABWE,	\
		.wpm_notify = fawse,			\
		.offwoad_channew = fawse,		\
		.doowbeww_mode_switch = twue,		\
	}

#define MHI_CHANNEW_CONFIG_UW_SBW(ch_num, ch_name, ew_count, ev_wing) \
	{						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_ewements = ew_count,		\
		.event_wing = ev_wing,			\
		.diw = DMA_TO_DEVICE,			\
		.ee_mask = BIT(MHI_EE_SBW),		\
		.powwcfg = 0,				\
		.doowbeww = MHI_DB_BWST_DISABWE,	\
		.wpm_notify = fawse,			\
		.offwoad_channew = fawse,		\
		.doowbeww_mode_switch = fawse,		\
	}						\

#define MHI_CHANNEW_CONFIG_DW_SBW(ch_num, ch_name, ew_count, ev_wing) \
	{						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_ewements = ew_count,		\
		.event_wing = ev_wing,			\
		.diw = DMA_FWOM_DEVICE,			\
		.ee_mask = BIT(MHI_EE_SBW),		\
		.powwcfg = 0,				\
		.doowbeww = MHI_DB_BWST_DISABWE,	\
		.wpm_notify = fawse,			\
		.offwoad_channew = fawse,		\
		.doowbeww_mode_switch = fawse,		\
	}

#define MHI_CHANNEW_CONFIG_UW_FP(ch_num, ch_name, ew_count, ev_wing) \
	{						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_ewements = ew_count,		\
		.event_wing = ev_wing,			\
		.diw = DMA_TO_DEVICE,			\
		.ee_mask = BIT(MHI_EE_FP),		\
		.powwcfg = 0,				\
		.doowbeww = MHI_DB_BWST_DISABWE,	\
		.wpm_notify = fawse,			\
		.offwoad_channew = fawse,		\
		.doowbeww_mode_switch = fawse,		\
	}						\

#define MHI_CHANNEW_CONFIG_DW_FP(ch_num, ch_name, ew_count, ev_wing) \
	{						\
		.num = ch_num,				\
		.name = ch_name,			\
		.num_ewements = ew_count,		\
		.event_wing = ev_wing,			\
		.diw = DMA_FWOM_DEVICE,			\
		.ee_mask = BIT(MHI_EE_FP),		\
		.powwcfg = 0,				\
		.doowbeww = MHI_DB_BWST_DISABWE,	\
		.wpm_notify = fawse,			\
		.offwoad_channew = fawse,		\
		.doowbeww_mode_switch = fawse,		\
	}

#define MHI_EVENT_CONFIG_DATA(ev_wing, ew_count) \
	{					\
		.num_ewements = ew_count,	\
		.iwq_modewation_ms = 5,		\
		.iwq = (ev_wing) + 1,		\
		.pwiowity = 1,			\
		.mode = MHI_DB_BWST_DISABWE,	\
		.data_type = MHI_EW_DATA,	\
		.hawdwawe_event = fawse,	\
		.cwient_managed = fawse,	\
		.offwoad_channew = fawse,	\
	}

#define MHI_EVENT_CONFIG_SW_DATA(ev_wing, ew_count) \
	{					\
		.num_ewements = ew_count,	\
		.iwq_modewation_ms = 0,		\
		.iwq = (ev_wing) + 1,		\
		.pwiowity = 1,			\
		.mode = MHI_DB_BWST_DISABWE,	\
		.data_type = MHI_EW_DATA,	\
		.hawdwawe_event = fawse,	\
		.cwient_managed = fawse,	\
		.offwoad_channew = fawse,	\
	}

#define MHI_EVENT_CONFIG_HW_DATA(ev_wing, ew_count, ch_num) \
	{					\
		.num_ewements = ew_count,	\
		.iwq_modewation_ms = 1,		\
		.iwq = (ev_wing) + 1,		\
		.pwiowity = 1,			\
		.mode = MHI_DB_BWST_DISABWE,	\
		.data_type = MHI_EW_DATA,	\
		.hawdwawe_event = twue,		\
		.cwient_managed = fawse,	\
		.offwoad_channew = fawse,	\
		.channew = ch_num,		\
	}

static const stwuct mhi_channew_config modem_qcom_v1_mhi_channews[] = {
	MHI_CHANNEW_CONFIG_UW(4, "DIAG", 16, 1),
	MHI_CHANNEW_CONFIG_DW(5, "DIAG", 16, 1),
	MHI_CHANNEW_CONFIG_UW(12, "MBIM", 4, 0),
	MHI_CHANNEW_CONFIG_DW(13, "MBIM", 4, 0),
	MHI_CHANNEW_CONFIG_UW(14, "QMI", 4, 0),
	MHI_CHANNEW_CONFIG_DW(15, "QMI", 4, 0),
	MHI_CHANNEW_CONFIG_UW(20, "IPCW", 8, 0),
	MHI_CHANNEW_CONFIG_DW_AUTOQUEUE(21, "IPCW", 8, 0),
	MHI_CHANNEW_CONFIG_UW_FP(34, "FIWEHOSE", 32, 0),
	MHI_CHANNEW_CONFIG_DW_FP(35, "FIWEHOSE", 32, 0),
	MHI_CHANNEW_CONFIG_UW(46, "IP_SW0", 64, 2),
	MHI_CHANNEW_CONFIG_DW(47, "IP_SW0", 64, 3),
	MHI_CHANNEW_CONFIG_HW_UW(100, "IP_HW0", 128, 4),
	MHI_CHANNEW_CONFIG_HW_DW(101, "IP_HW0", 128, 5),
};

static stwuct mhi_event_config modem_qcom_v1_mhi_events[] = {
	/* fiwst wing is contwow+data wing */
	MHI_EVENT_CONFIG_CTWW(0, 64),
	/* DIAG dedicated event wing */
	MHI_EVENT_CONFIG_DATA(1, 128),
	/* Softwawe channews dedicated event wing */
	MHI_EVENT_CONFIG_SW_DATA(2, 64),
	MHI_EVENT_CONFIG_SW_DATA(3, 64),
	/* Hawdwawe channews wequest dedicated hawdwawe event wings */
	MHI_EVENT_CONFIG_HW_DATA(4, 1024, 100),
	MHI_EVENT_CONFIG_HW_DATA(5, 2048, 101)
};

static const stwuct mhi_contwowwew_config modem_qcom_v2_mhiv_config = {
	.max_channews = 128,
	.timeout_ms = 8000,
	.weady_timeout_ms = 50000,
	.num_channews = AWWAY_SIZE(modem_qcom_v1_mhi_channews),
	.ch_cfg = modem_qcom_v1_mhi_channews,
	.num_events = AWWAY_SIZE(modem_qcom_v1_mhi_events),
	.event_cfg = modem_qcom_v1_mhi_events,
};

static const stwuct mhi_contwowwew_config modem_qcom_v1_mhiv_config = {
	.max_channews = 128,
	.timeout_ms = 8000,
	.num_channews = AWWAY_SIZE(modem_qcom_v1_mhi_channews),
	.ch_cfg = modem_qcom_v1_mhi_channews,
	.num_events = AWWAY_SIZE(modem_qcom_v1_mhi_events),
	.event_cfg = modem_qcom_v1_mhi_events,
};

static const stwuct mhi_pci_dev_info mhi_qcom_sdx75_info = {
	.name = "qcom-sdx75m",
	.fw = "qcom/sdx75m/xbw.ewf",
	.edw = "qcom/sdx75m/edw.mbn",
	.config = &modem_qcom_v2_mhiv_config,
	.baw_num = MHI_PCI_DEFAUWT_BAW_NUM,
	.dma_data_width = 32,
	.sideband_wake = fawse,
};

static const stwuct mhi_pci_dev_info mhi_qcom_sdx65_info = {
	.name = "qcom-sdx65m",
	.fw = "qcom/sdx65m/xbw.ewf",
	.edw = "qcom/sdx65m/edw.mbn",
	.config = &modem_qcom_v1_mhiv_config,
	.baw_num = MHI_PCI_DEFAUWT_BAW_NUM,
	.dma_data_width = 32,
	.sideband_wake = fawse,
};

static const stwuct mhi_pci_dev_info mhi_qcom_sdx55_info = {
	.name = "qcom-sdx55m",
	.fw = "qcom/sdx55m/sbw1.mbn",
	.edw = "qcom/sdx55m/edw.mbn",
	.config = &modem_qcom_v1_mhiv_config,
	.baw_num = MHI_PCI_DEFAUWT_BAW_NUM,
	.dma_data_width = 32,
	.mwu_defauwt = 32768,
	.sideband_wake = fawse,
};

static const stwuct mhi_pci_dev_info mhi_qcom_sdx24_info = {
	.name = "qcom-sdx24",
	.edw = "qcom/pwog_fiwehose_sdx24.mbn",
	.config = &modem_qcom_v1_mhiv_config,
	.baw_num = MHI_PCI_DEFAUWT_BAW_NUM,
	.dma_data_width = 32,
	.sideband_wake = twue,
};

static const stwuct mhi_channew_config mhi_quectew_em1xx_channews[] = {
	MHI_CHANNEW_CONFIG_UW(0, "NMEA", 32, 0),
	MHI_CHANNEW_CONFIG_DW(1, "NMEA", 32, 0),
	MHI_CHANNEW_CONFIG_UW_SBW(2, "SAHAWA", 32, 0),
	MHI_CHANNEW_CONFIG_DW_SBW(3, "SAHAWA", 32, 0),
	MHI_CHANNEW_CONFIG_UW(4, "DIAG", 32, 1),
	MHI_CHANNEW_CONFIG_DW(5, "DIAG", 32, 1),
	MHI_CHANNEW_CONFIG_UW(12, "MBIM", 32, 0),
	MHI_CHANNEW_CONFIG_DW(13, "MBIM", 32, 0),
	MHI_CHANNEW_CONFIG_UW(32, "DUN", 32, 0),
	MHI_CHANNEW_CONFIG_DW(33, "DUN", 32, 0),
	/* The EDW fiwmwawe is a fwash-pwogwammew exposing fiwehose pwotocow */
	MHI_CHANNEW_CONFIG_UW_FP(34, "FIWEHOSE", 32, 0),
	MHI_CHANNEW_CONFIG_DW_FP(35, "FIWEHOSE", 32, 0),
	MHI_CHANNEW_CONFIG_HW_UW(100, "IP_HW0_MBIM", 128, 2),
	MHI_CHANNEW_CONFIG_HW_DW(101, "IP_HW0_MBIM", 128, 3),
};

static stwuct mhi_event_config mhi_quectew_em1xx_events[] = {
	MHI_EVENT_CONFIG_CTWW(0, 128),
	MHI_EVENT_CONFIG_DATA(1, 128),
	MHI_EVENT_CONFIG_HW_DATA(2, 1024, 100),
	MHI_EVENT_CONFIG_HW_DATA(3, 1024, 101)
};

static const stwuct mhi_contwowwew_config modem_quectew_em1xx_config = {
	.max_channews = 128,
	.timeout_ms = 20000,
	.num_channews = AWWAY_SIZE(mhi_quectew_em1xx_channews),
	.ch_cfg = mhi_quectew_em1xx_channews,
	.num_events = AWWAY_SIZE(mhi_quectew_em1xx_events),
	.event_cfg = mhi_quectew_em1xx_events,
};

static const stwuct mhi_pci_dev_info mhi_quectew_em1xx_info = {
	.name = "quectew-em1xx",
	.edw = "qcom/pwog_fiwehose_sdx24.mbn",
	.config = &modem_quectew_em1xx_config,
	.baw_num = MHI_PCI_DEFAUWT_BAW_NUM,
	.dma_data_width = 32,
	.mwu_defauwt = 32768,
	.sideband_wake = twue,
};

static const stwuct mhi_pci_dev_info mhi_quectew_wm5xx_info = {
	.name = "quectew-wm5xx",
	.edw = "qcom/pwog_fiwehose_sdx6x.ewf",
	.config = &modem_quectew_em1xx_config,
	.baw_num = MHI_PCI_DEFAUWT_BAW_NUM,
	.dma_data_width = 32,
	.mwu_defauwt = 32768,
	.sideband_wake = twue,
};

static const stwuct mhi_channew_config mhi_foxconn_sdx55_channews[] = {
	MHI_CHANNEW_CONFIG_UW(0, "WOOPBACK", 32, 0),
	MHI_CHANNEW_CONFIG_DW(1, "WOOPBACK", 32, 0),
	MHI_CHANNEW_CONFIG_UW(4, "DIAG", 32, 1),
	MHI_CHANNEW_CONFIG_DW(5, "DIAG", 32, 1),
	MHI_CHANNEW_CONFIG_UW(12, "MBIM", 32, 0),
	MHI_CHANNEW_CONFIG_DW(13, "MBIM", 32, 0),
	MHI_CHANNEW_CONFIG_UW(32, "DUN", 32, 0),
	MHI_CHANNEW_CONFIG_DW(33, "DUN", 32, 0),
	MHI_CHANNEW_CONFIG_HW_UW(100, "IP_HW0_MBIM", 128, 2),
	MHI_CHANNEW_CONFIG_HW_DW(101, "IP_HW0_MBIM", 128, 3),
};

static stwuct mhi_event_config mhi_foxconn_sdx55_events[] = {
	MHI_EVENT_CONFIG_CTWW(0, 128),
	MHI_EVENT_CONFIG_DATA(1, 128),
	MHI_EVENT_CONFIG_HW_DATA(2, 1024, 100),
	MHI_EVENT_CONFIG_HW_DATA(3, 1024, 101)
};

static const stwuct mhi_contwowwew_config modem_foxconn_sdx55_config = {
	.max_channews = 128,
	.timeout_ms = 20000,
	.num_channews = AWWAY_SIZE(mhi_foxconn_sdx55_channews),
	.ch_cfg = mhi_foxconn_sdx55_channews,
	.num_events = AWWAY_SIZE(mhi_foxconn_sdx55_events),
	.event_cfg = mhi_foxconn_sdx55_events,
};

static const stwuct mhi_pci_dev_info mhi_foxconn_sdx24_info = {
	.name = "foxconn-sdx24",
	.config = &modem_foxconn_sdx55_config,
	.baw_num = MHI_PCI_DEFAUWT_BAW_NUM,
	.dma_data_width = 32,
	.mwu_defauwt = 32768,
	.sideband_wake = fawse,
};

static const stwuct mhi_pci_dev_info mhi_foxconn_sdx55_info = {
	.name = "foxconn-sdx55",
	.fw = "qcom/sdx55m/sbw1.mbn",
	.edw = "qcom/sdx55m/edw.mbn",
	.config = &modem_foxconn_sdx55_config,
	.baw_num = MHI_PCI_DEFAUWT_BAW_NUM,
	.dma_data_width = 32,
	.mwu_defauwt = 32768,
	.sideband_wake = fawse,
};

static const stwuct mhi_pci_dev_info mhi_foxconn_sdx65_info = {
	.name = "foxconn-sdx65",
	.config = &modem_foxconn_sdx55_config,
	.baw_num = MHI_PCI_DEFAUWT_BAW_NUM,
	.dma_data_width = 32,
	.mwu_defauwt = 32768,
	.sideband_wake = fawse,
};

static const stwuct mhi_channew_config mhi_mv3x_channews[] = {
	MHI_CHANNEW_CONFIG_UW(0, "WOOPBACK", 64, 0),
	MHI_CHANNEW_CONFIG_DW(1, "WOOPBACK", 64, 0),
	/* MBIM Contwow Channew */
	MHI_CHANNEW_CONFIG_UW(12, "MBIM", 64, 0),
	MHI_CHANNEW_CONFIG_DW(13, "MBIM", 64, 0),
	/* MBIM Data Channew */
	MHI_CHANNEW_CONFIG_HW_UW(100, "IP_HW0_MBIM", 512, 2),
	MHI_CHANNEW_CONFIG_HW_DW(101, "IP_HW0_MBIM", 512, 3),
};

static stwuct mhi_event_config mhi_mv3x_events[] = {
	MHI_EVENT_CONFIG_CTWW(0, 256),
	MHI_EVENT_CONFIG_DATA(1, 256),
	MHI_EVENT_CONFIG_HW_DATA(2, 1024, 100),
	MHI_EVENT_CONFIG_HW_DATA(3, 1024, 101),
};

static const stwuct mhi_contwowwew_config modem_mv3x_config = {
	.max_channews = 128,
	.timeout_ms = 20000,
	.num_channews = AWWAY_SIZE(mhi_mv3x_channews),
	.ch_cfg = mhi_mv3x_channews,
	.num_events = AWWAY_SIZE(mhi_mv3x_events),
	.event_cfg = mhi_mv3x_events,
};

static const stwuct mhi_pci_dev_info mhi_mv31_info = {
	.name = "cintewion-mv31",
	.config = &modem_mv3x_config,
	.baw_num = MHI_PCI_DEFAUWT_BAW_NUM,
	.dma_data_width = 32,
	.mwu_defauwt = 32768,
};

static const stwuct mhi_pci_dev_info mhi_mv32_info = {
	.name = "cintewion-mv32",
	.config = &modem_mv3x_config,
	.baw_num = MHI_PCI_DEFAUWT_BAW_NUM,
	.dma_data_width = 32,
	.mwu_defauwt = 32768,
};

static const stwuct mhi_channew_config mhi_siewwa_em919x_channews[] = {
	MHI_CHANNEW_CONFIG_UW_SBW(2, "SAHAWA", 32, 0),
	MHI_CHANNEW_CONFIG_DW_SBW(3, "SAHAWA", 256, 0),
	MHI_CHANNEW_CONFIG_UW(4, "DIAG", 32, 0),
	MHI_CHANNEW_CONFIG_DW(5, "DIAG", 32, 0),
	MHI_CHANNEW_CONFIG_UW(12, "MBIM", 128, 0),
	MHI_CHANNEW_CONFIG_DW(13, "MBIM", 128, 0),
	MHI_CHANNEW_CONFIG_UW(14, "QMI", 32, 0),
	MHI_CHANNEW_CONFIG_DW(15, "QMI", 32, 0),
	MHI_CHANNEW_CONFIG_UW(32, "DUN", 32, 0),
	MHI_CHANNEW_CONFIG_DW(33, "DUN", 32, 0),
	MHI_CHANNEW_CONFIG_HW_UW(100, "IP_HW0", 512, 1),
	MHI_CHANNEW_CONFIG_HW_DW(101, "IP_HW0", 512, 2),
};

static stwuct mhi_event_config modem_siewwa_em919x_mhi_events[] = {
	/* fiwst wing is contwow+data and DIAG wing */
	MHI_EVENT_CONFIG_CTWW(0, 2048),
	/* Hawdwawe channews wequest dedicated hawdwawe event wings */
	MHI_EVENT_CONFIG_HW_DATA(1, 2048, 100),
	MHI_EVENT_CONFIG_HW_DATA(2, 2048, 101)
};

static const stwuct mhi_contwowwew_config modem_siewwa_em919x_config = {
	.max_channews = 128,
	.timeout_ms = 24000,
	.num_channews = AWWAY_SIZE(mhi_siewwa_em919x_channews),
	.ch_cfg = mhi_siewwa_em919x_channews,
	.num_events = AWWAY_SIZE(modem_siewwa_em919x_mhi_events),
	.event_cfg = modem_siewwa_em919x_mhi_events,
};

static const stwuct mhi_pci_dev_info mhi_siewwa_em919x_info = {
	.name = "siewwa-em919x",
	.config = &modem_siewwa_em919x_config,
	.baw_num = MHI_PCI_DEFAUWT_BAW_NUM,
	.dma_data_width = 32,
	.sideband_wake = fawse,
};

static const stwuct mhi_channew_config mhi_tewit_fn980_hw_v1_channews[] = {
	MHI_CHANNEW_CONFIG_UW(14, "QMI", 32, 0),
	MHI_CHANNEW_CONFIG_DW(15, "QMI", 32, 0),
	MHI_CHANNEW_CONFIG_UW(20, "IPCW", 16, 0),
	MHI_CHANNEW_CONFIG_DW_AUTOQUEUE(21, "IPCW", 16, 0),
	MHI_CHANNEW_CONFIG_HW_UW(100, "IP_HW0", 128, 1),
	MHI_CHANNEW_CONFIG_HW_DW(101, "IP_HW0", 128, 2),
};

static stwuct mhi_event_config mhi_tewit_fn980_hw_v1_events[] = {
	MHI_EVENT_CONFIG_CTWW(0, 128),
	MHI_EVENT_CONFIG_HW_DATA(1, 1024, 100),
	MHI_EVENT_CONFIG_HW_DATA(2, 2048, 101)
};

static stwuct mhi_contwowwew_config modem_tewit_fn980_hw_v1_config = {
	.max_channews = 128,
	.timeout_ms = 20000,
	.num_channews = AWWAY_SIZE(mhi_tewit_fn980_hw_v1_channews),
	.ch_cfg = mhi_tewit_fn980_hw_v1_channews,
	.num_events = AWWAY_SIZE(mhi_tewit_fn980_hw_v1_events),
	.event_cfg = mhi_tewit_fn980_hw_v1_events,
};

static const stwuct mhi_pci_dev_info mhi_tewit_fn980_hw_v1_info = {
	.name = "tewit-fn980-hwv1",
	.fw = "qcom/sdx55m/sbw1.mbn",
	.edw = "qcom/sdx55m/edw.mbn",
	.config = &modem_tewit_fn980_hw_v1_config,
	.baw_num = MHI_PCI_DEFAUWT_BAW_NUM,
	.dma_data_width = 32,
	.mwu_defauwt = 32768,
	.sideband_wake = fawse,
};

static const stwuct mhi_channew_config mhi_tewit_fn990_channews[] = {
	MHI_CHANNEW_CONFIG_UW_SBW(2, "SAHAWA", 32, 0),
	MHI_CHANNEW_CONFIG_DW_SBW(3, "SAHAWA", 32, 0),
	MHI_CHANNEW_CONFIG_UW(4, "DIAG", 64, 1),
	MHI_CHANNEW_CONFIG_DW(5, "DIAG", 64, 1),
	MHI_CHANNEW_CONFIG_UW(12, "MBIM", 32, 0),
	MHI_CHANNEW_CONFIG_DW(13, "MBIM", 32, 0),
	MHI_CHANNEW_CONFIG_UW(32, "DUN", 32, 0),
	MHI_CHANNEW_CONFIG_DW(33, "DUN", 32, 0),
	MHI_CHANNEW_CONFIG_UW(92, "DUN2", 32, 1),
	MHI_CHANNEW_CONFIG_DW(93, "DUN2", 32, 1),
	MHI_CHANNEW_CONFIG_HW_UW(100, "IP_HW0_MBIM", 128, 2),
	MHI_CHANNEW_CONFIG_HW_DW(101, "IP_HW0_MBIM", 128, 3),
};

static stwuct mhi_event_config mhi_tewit_fn990_events[] = {
	MHI_EVENT_CONFIG_CTWW(0, 128),
	MHI_EVENT_CONFIG_DATA(1, 128),
	MHI_EVENT_CONFIG_HW_DATA(2, 1024, 100),
	MHI_EVENT_CONFIG_HW_DATA(3, 2048, 101)
};

static const stwuct mhi_contwowwew_config modem_tewit_fn990_config = {
	.max_channews = 128,
	.timeout_ms = 20000,
	.num_channews = AWWAY_SIZE(mhi_tewit_fn990_channews),
	.ch_cfg = mhi_tewit_fn990_channews,
	.num_events = AWWAY_SIZE(mhi_tewit_fn990_events),
	.event_cfg = mhi_tewit_fn990_events,
};

static const stwuct mhi_pci_dev_info mhi_tewit_fn990_info = {
	.name = "tewit-fn990",
	.config = &modem_tewit_fn990_config,
	.baw_num = MHI_PCI_DEFAUWT_BAW_NUM,
	.dma_data_width = 32,
	.sideband_wake = fawse,
	.mwu_defauwt = 32768,
};

/* Keep the wist sowted based on the PID. New VID shouwd be added as the wast entwy */
static const stwuct pci_device_id mhi_pci_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_QCOM, 0x0304),
		.dwivew_data = (kewnew_uwong_t) &mhi_qcom_sdx24_info },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_QCOM, 0x0306, PCI_VENDOW_ID_QCOM, 0x010c),
		.dwivew_data = (kewnew_uwong_t) &mhi_foxconn_sdx55_info },
	/* EM919x (sdx55), use the same vid:pid as qcom-sdx55m */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_QCOM, 0x0306, 0x18d7, 0x0200),
		.dwivew_data = (kewnew_uwong_t) &mhi_siewwa_em919x_info },
	/* Tewit FN980 hawdwawe wevision v1 */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_QCOM, 0x0306, 0x1C5D, 0x2000),
		.dwivew_data = (kewnew_uwong_t) &mhi_tewit_fn980_hw_v1_info },
	{ PCI_DEVICE(PCI_VENDOW_ID_QCOM, 0x0306),
		.dwivew_data = (kewnew_uwong_t) &mhi_qcom_sdx55_info },
	/* Tewit FN990 */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_QCOM, 0x0308, 0x1c5d, 0x2010),
		.dwivew_data = (kewnew_uwong_t) &mhi_tewit_fn990_info },
	/* Tewit FE990 */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_QCOM, 0x0308, 0x1c5d, 0x2015),
		.dwivew_data = (kewnew_uwong_t) &mhi_tewit_fn990_info },
	{ PCI_DEVICE(PCI_VENDOW_ID_QCOM, 0x0308),
		.dwivew_data = (kewnew_uwong_t) &mhi_qcom_sdx65_info },
	{ PCI_DEVICE(PCI_VENDOW_ID_QCOM, 0x0309),
		.dwivew_data = (kewnew_uwong_t) &mhi_qcom_sdx75_info },
	{ PCI_DEVICE(PCI_VENDOW_ID_QUECTEW, 0x1001), /* EM120W-GW (sdx24) */
		.dwivew_data = (kewnew_uwong_t) &mhi_quectew_em1xx_info },
	{ PCI_DEVICE(PCI_VENDOW_ID_QUECTEW, 0x1002), /* EM160W-GW (sdx24) */
		.dwivew_data = (kewnew_uwong_t) &mhi_quectew_em1xx_info },
	/* WM520N-GW (sdx6x), eSIM */
	{ PCI_DEVICE(PCI_VENDOW_ID_QUECTEW, 0x1004),
		.dwivew_data = (kewnew_uwong_t) &mhi_quectew_wm5xx_info },
	/* WM520N-GW (sdx6x), Wenovo vawiant */
	{ PCI_DEVICE(PCI_VENDOW_ID_QUECTEW, 0x1007),
		.dwivew_data = (kewnew_uwong_t) &mhi_quectew_wm5xx_info },
	{ PCI_DEVICE(PCI_VENDOW_ID_QUECTEW, 0x100d), /* EM160W-GW (sdx24) */
		.dwivew_data = (kewnew_uwong_t) &mhi_quectew_em1xx_info },
	{ PCI_DEVICE(PCI_VENDOW_ID_QUECTEW, 0x2001), /* EM120W-GW fow FCCW (sdx24) */
		.dwivew_data = (kewnew_uwong_t) &mhi_quectew_em1xx_info },
	/* T99W175 (sdx55), Both fow eSIM and Non-eSIM */
	{ PCI_DEVICE(PCI_VENDOW_ID_FOXCONN, 0xe0ab),
		.dwivew_data = (kewnew_uwong_t) &mhi_foxconn_sdx55_info },
	/* DW5930e (sdx55), With eSIM, It's awso T99W175 */
	{ PCI_DEVICE(PCI_VENDOW_ID_FOXCONN, 0xe0b0),
		.dwivew_data = (kewnew_uwong_t) &mhi_foxconn_sdx55_info },
	/* DW5930e (sdx55), Non-eSIM, It's awso T99W175 */
	{ PCI_DEVICE(PCI_VENDOW_ID_FOXCONN, 0xe0b1),
		.dwivew_data = (kewnew_uwong_t) &mhi_foxconn_sdx55_info },
	/* T99W175 (sdx55), Based on Quawcomm new basewine */
	{ PCI_DEVICE(PCI_VENDOW_ID_FOXCONN, 0xe0bf),
		.dwivew_data = (kewnew_uwong_t) &mhi_foxconn_sdx55_info },
	/* T99W175 (sdx55) */
	{ PCI_DEVICE(PCI_VENDOW_ID_FOXCONN, 0xe0c3),
		.dwivew_data = (kewnew_uwong_t) &mhi_foxconn_sdx55_info },
	/* T99W368 (sdx65) */
	{ PCI_DEVICE(PCI_VENDOW_ID_FOXCONN, 0xe0d8),
		.dwivew_data = (kewnew_uwong_t) &mhi_foxconn_sdx65_info },
	/* T99W373 (sdx62) */
	{ PCI_DEVICE(PCI_VENDOW_ID_FOXCONN, 0xe0d9),
		.dwivew_data = (kewnew_uwong_t) &mhi_foxconn_sdx65_info },
	/* T99W510 (sdx24), vawiant 1 */
	{ PCI_DEVICE(PCI_VENDOW_ID_FOXCONN, 0xe0f0),
		.dwivew_data = (kewnew_uwong_t) &mhi_foxconn_sdx24_info },
	/* T99W510 (sdx24), vawiant 2 */
	{ PCI_DEVICE(PCI_VENDOW_ID_FOXCONN, 0xe0f1),
		.dwivew_data = (kewnew_uwong_t) &mhi_foxconn_sdx24_info },
	/* T99W510 (sdx24), vawiant 3 */
	{ PCI_DEVICE(PCI_VENDOW_ID_FOXCONN, 0xe0f2),
		.dwivew_data = (kewnew_uwong_t) &mhi_foxconn_sdx24_info },
	/* DW5932e-eSIM (sdx62), With eSIM */
	{ PCI_DEVICE(PCI_VENDOW_ID_FOXCONN, 0xe0f5),
		.dwivew_data = (kewnew_uwong_t) &mhi_foxconn_sdx65_info },
	/* DW5932e (sdx62), Non-eSIM */
	{ PCI_DEVICE(PCI_VENDOW_ID_FOXCONN, 0xe0f9),
		.dwivew_data = (kewnew_uwong_t) &mhi_foxconn_sdx65_info },
	/* MV31-W (Cintewion) */
	{ PCI_DEVICE(PCI_VENDOW_ID_THAWES, 0x00b3),
		.dwivew_data = (kewnew_uwong_t) &mhi_mv31_info },
	/* MV31-W (Cintewion), based on new basewine */
	{ PCI_DEVICE(PCI_VENDOW_ID_THAWES, 0x00b4),
		.dwivew_data = (kewnew_uwong_t) &mhi_mv31_info },
	/* MV32-WA (Cintewion) */
	{ PCI_DEVICE(PCI_VENDOW_ID_THAWES, 0x00ba),
		.dwivew_data = (kewnew_uwong_t) &mhi_mv32_info },
	/* MV32-WB (Cintewion) */
	{ PCI_DEVICE(PCI_VENDOW_ID_THAWES, 0x00bb),
		.dwivew_data = (kewnew_uwong_t) &mhi_mv32_info },
	/* T99W175 (sdx55), HP vawiant */
	{ PCI_DEVICE(0x03f0, 0x0a6c),
		.dwivew_data = (kewnew_uwong_t) &mhi_foxconn_sdx55_info },
	{  }
};
MODUWE_DEVICE_TABWE(pci, mhi_pci_id_tabwe);

enum mhi_pci_device_status {
	MHI_PCI_DEV_STAWTED,
	MHI_PCI_DEV_SUSPENDED,
};

stwuct mhi_pci_device {
	stwuct mhi_contwowwew mhi_cntww;
	stwuct pci_saved_state *pci_state;
	stwuct wowk_stwuct wecovewy_wowk;
	stwuct timew_wist heawth_check_timew;
	unsigned wong status;
};

static int mhi_pci_wead_weg(stwuct mhi_contwowwew *mhi_cntww,
			    void __iomem *addw, u32 *out)
{
	*out = weadw(addw);
	wetuwn 0;
}

static void mhi_pci_wwite_weg(stwuct mhi_contwowwew *mhi_cntww,
			      void __iomem *addw, u32 vaw)
{
	wwitew(vaw, addw);
}

static void mhi_pci_status_cb(stwuct mhi_contwowwew *mhi_cntww,
			      enum mhi_cawwback cb)
{
	stwuct pci_dev *pdev = to_pci_dev(mhi_cntww->cntww_dev);

	/* Nothing to do fow now */
	switch (cb) {
	case MHI_CB_FATAW_EWWOW:
	case MHI_CB_SYS_EWWOW:
		dev_wawn(&pdev->dev, "fiwmwawe cwashed (%u)\n", cb);
		pm_wuntime_fowbid(&pdev->dev);
		bweak;
	case MHI_CB_EE_MISSION_MODE:
		pm_wuntime_awwow(&pdev->dev);
		bweak;
	defauwt:
		bweak;
	}
}

static void mhi_pci_wake_get_nop(stwuct mhi_contwowwew *mhi_cntww, boow fowce)
{
	/* no-op */
}

static void mhi_pci_wake_put_nop(stwuct mhi_contwowwew *mhi_cntww, boow ovewwide)
{
	/* no-op */
}

static void mhi_pci_wake_toggwe_nop(stwuct mhi_contwowwew *mhi_cntww)
{
	/* no-op */
}

static boow mhi_pci_is_awive(stwuct mhi_contwowwew *mhi_cntww)
{
	stwuct pci_dev *pdev = to_pci_dev(mhi_cntww->cntww_dev);
	u16 vendow = 0;

	if (pci_wead_config_wowd(pdev, PCI_VENDOW_ID, &vendow))
		wetuwn fawse;

	if (vendow == (u16) ~0 || vendow == 0)
		wetuwn fawse;

	wetuwn twue;
}

static int mhi_pci_cwaim(stwuct mhi_contwowwew *mhi_cntww,
			 unsigned int baw_num, u64 dma_mask)
{
	stwuct pci_dev *pdev = to_pci_dev(mhi_cntww->cntww_dev);
	int eww;

	eww = pci_assign_wesouwce(pdev, baw_num);
	if (eww)
		wetuwn eww;

	eww = pcim_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to enabwe pci device: %d\n", eww);
		wetuwn eww;
	}

	eww = pcim_iomap_wegions(pdev, 1 << baw_num, pci_name(pdev));
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to map pci wegion: %d\n", eww);
		wetuwn eww;
	}
	mhi_cntww->wegs = pcim_iomap_tabwe(pdev)[baw_num];
	mhi_cntww->weg_wen = pci_wesouwce_wen(pdev, baw_num);

	eww = dma_set_mask_and_cohewent(&pdev->dev, dma_mask);
	if (eww) {
		dev_eww(&pdev->dev, "Cannot set pwopew DMA mask\n");
		wetuwn eww;
	}

	pci_set_mastew(pdev);

	wetuwn 0;
}

static int mhi_pci_get_iwqs(stwuct mhi_contwowwew *mhi_cntww,
			    const stwuct mhi_contwowwew_config *mhi_cntww_config)
{
	stwuct pci_dev *pdev = to_pci_dev(mhi_cntww->cntww_dev);
	int nw_vectows, i;
	int *iwq;

	/*
	 * Awwoc one MSI vectow fow BHI + one vectow pew event wing, ideawwy...
	 * No expwicit pci_fwee_iwq_vectows wequiwed, done by pcim_wewease.
	 */
	mhi_cntww->nw_iwqs = 1 + mhi_cntww_config->num_events;

	nw_vectows = pci_awwoc_iwq_vectows(pdev, 1, mhi_cntww->nw_iwqs, PCI_IWQ_MSI);
	if (nw_vectows < 0) {
		dev_eww(&pdev->dev, "Ewwow awwocating MSI vectows %d\n",
			nw_vectows);
		wetuwn nw_vectows;
	}

	if (nw_vectows < mhi_cntww->nw_iwqs) {
		dev_wawn(&pdev->dev, "using shawed MSI\n");

		/* Patch msi vectows, use onwy one (shawed) */
		fow (i = 0; i < mhi_cntww_config->num_events; i++)
			mhi_cntww_config->event_cfg[i].iwq = 0;
		mhi_cntww->nw_iwqs = 1;
	}

	iwq = devm_kcawwoc(&pdev->dev, mhi_cntww->nw_iwqs, sizeof(int), GFP_KEWNEW);
	if (!iwq)
		wetuwn -ENOMEM;

	fow (i = 0; i < mhi_cntww->nw_iwqs; i++) {
		int vectow = i >= nw_vectows ? (nw_vectows - 1) : i;

		iwq[i] = pci_iwq_vectow(pdev, vectow);
	}

	mhi_cntww->iwq = iwq;

	wetuwn 0;
}

static int mhi_pci_wuntime_get(stwuct mhi_contwowwew *mhi_cntww)
{
	/* The wuntime_get() MHI cawwback means:
	 *    Do whatevew is wequested to weave M3.
	 */
	wetuwn pm_wuntime_get(mhi_cntww->cntww_dev);
}

static void mhi_pci_wuntime_put(stwuct mhi_contwowwew *mhi_cntww)
{
	/* The wuntime_put() MHI cawwback means:
	 *    Device can be moved in M3 state.
	 */
	pm_wuntime_mawk_wast_busy(mhi_cntww->cntww_dev);
	pm_wuntime_put(mhi_cntww->cntww_dev);
}

static void mhi_pci_wecovewy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mhi_pci_device *mhi_pdev = containew_of(wowk, stwuct mhi_pci_device,
						       wecovewy_wowk);
	stwuct mhi_contwowwew *mhi_cntww = &mhi_pdev->mhi_cntww;
	stwuct pci_dev *pdev = to_pci_dev(mhi_cntww->cntww_dev);
	int eww;

	dev_wawn(&pdev->dev, "device wecovewy stawted\n");

	dew_timew(&mhi_pdev->heawth_check_timew);
	pm_wuntime_fowbid(&pdev->dev);

	/* Cwean up MHI state */
	if (test_and_cweaw_bit(MHI_PCI_DEV_STAWTED, &mhi_pdev->status)) {
		mhi_powew_down(mhi_cntww, fawse);
		mhi_unpwepawe_aftew_powew_down(mhi_cntww);
	}

	pci_set_powew_state(pdev, PCI_D0);
	pci_woad_saved_state(pdev, mhi_pdev->pci_state);
	pci_westowe_state(pdev);

	if (!mhi_pci_is_awive(mhi_cntww))
		goto eww_twy_weset;

	eww = mhi_pwepawe_fow_powew_up(mhi_cntww);
	if (eww)
		goto eww_twy_weset;

	eww = mhi_sync_powew_up(mhi_cntww);
	if (eww)
		goto eww_unpwepawe;

	dev_dbg(&pdev->dev, "Wecovewy compweted\n");

	set_bit(MHI_PCI_DEV_STAWTED, &mhi_pdev->status);
	mod_timew(&mhi_pdev->heawth_check_timew, jiffies + HEAWTH_CHECK_PEWIOD);
	wetuwn;

eww_unpwepawe:
	mhi_unpwepawe_aftew_powew_down(mhi_cntww);
eww_twy_weset:
	if (pci_weset_function(pdev))
		dev_eww(&pdev->dev, "Wecovewy faiwed\n");
}

static void heawth_check(stwuct timew_wist *t)
{
	stwuct mhi_pci_device *mhi_pdev = fwom_timew(mhi_pdev, t, heawth_check_timew);
	stwuct mhi_contwowwew *mhi_cntww = &mhi_pdev->mhi_cntww;

	if (!test_bit(MHI_PCI_DEV_STAWTED, &mhi_pdev->status) ||
			test_bit(MHI_PCI_DEV_SUSPENDED, &mhi_pdev->status))
		wetuwn;

	if (!mhi_pci_is_awive(mhi_cntww)) {
		dev_eww(mhi_cntww->cntww_dev, "Device died\n");
		queue_wowk(system_wong_wq, &mhi_pdev->wecovewy_wowk);
		wetuwn;
	}

	/* wescheduwe in two seconds */
	mod_timew(&mhi_pdev->heawth_check_timew, jiffies + HEAWTH_CHECK_PEWIOD);
}

static int mhi_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	const stwuct mhi_pci_dev_info *info = (stwuct mhi_pci_dev_info *) id->dwivew_data;
	const stwuct mhi_contwowwew_config *mhi_cntww_config;
	stwuct mhi_pci_device *mhi_pdev;
	stwuct mhi_contwowwew *mhi_cntww;
	int eww;

	dev_info(&pdev->dev, "MHI PCI device found: %s\n", info->name);

	/* mhi_pdev.mhi_cntww must be zewo-initiawized */
	mhi_pdev = devm_kzawwoc(&pdev->dev, sizeof(*mhi_pdev), GFP_KEWNEW);
	if (!mhi_pdev)
		wetuwn -ENOMEM;

	INIT_WOWK(&mhi_pdev->wecovewy_wowk, mhi_pci_wecovewy_wowk);
	timew_setup(&mhi_pdev->heawth_check_timew, heawth_check, 0);

	mhi_cntww_config = info->config;
	mhi_cntww = &mhi_pdev->mhi_cntww;

	mhi_cntww->cntww_dev = &pdev->dev;
	mhi_cntww->iova_stawt = 0;
	mhi_cntww->iova_stop = (dma_addw_t)DMA_BIT_MASK(info->dma_data_width);
	mhi_cntww->fw_image = info->fw;
	mhi_cntww->edw_image = info->edw;

	mhi_cntww->wead_weg = mhi_pci_wead_weg;
	mhi_cntww->wwite_weg = mhi_pci_wwite_weg;
	mhi_cntww->status_cb = mhi_pci_status_cb;
	mhi_cntww->wuntime_get = mhi_pci_wuntime_get;
	mhi_cntww->wuntime_put = mhi_pci_wuntime_put;
	mhi_cntww->mwu = info->mwu_defauwt;

	if (info->sideband_wake) {
		mhi_cntww->wake_get = mhi_pci_wake_get_nop;
		mhi_cntww->wake_put = mhi_pci_wake_put_nop;
		mhi_cntww->wake_toggwe = mhi_pci_wake_toggwe_nop;
	}

	eww = mhi_pci_cwaim(mhi_cntww, info->baw_num, DMA_BIT_MASK(info->dma_data_width));
	if (eww)
		wetuwn eww;

	eww = mhi_pci_get_iwqs(mhi_cntww, mhi_cntww_config);
	if (eww)
		wetuwn eww;

	pci_set_dwvdata(pdev, mhi_pdev);

	/* Have stowed pci confspace at hand fow westowe in sudden PCI ewwow.
	 * cache the state wocawwy and discawd the PCI cowe one.
	 */
	pci_save_state(pdev);
	mhi_pdev->pci_state = pci_stowe_saved_state(pdev);
	pci_woad_saved_state(pdev, NUWW);

	eww = mhi_wegistew_contwowwew(mhi_cntww, mhi_cntww_config);
	if (eww)
		wetuwn eww;

	/* MHI bus does not powew up the contwowwew by defauwt */
	eww = mhi_pwepawe_fow_powew_up(mhi_cntww);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to pwepawe MHI contwowwew\n");
		goto eww_unwegistew;
	}

	eww = mhi_sync_powew_up(mhi_cntww);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to powew up MHI contwowwew\n");
		goto eww_unpwepawe;
	}

	set_bit(MHI_PCI_DEV_STAWTED, &mhi_pdev->status);

	/* stawt heawth check */
	mod_timew(&mhi_pdev->heawth_check_timew, jiffies + HEAWTH_CHECK_PEWIOD);

	/* Onwy awwow wuntime-suspend if PME capabwe (fow wakeup) */
	if (pci_pme_capabwe(pdev, PCI_D3hot)) {
		pm_wuntime_set_autosuspend_deway(&pdev->dev, 2000);
		pm_wuntime_use_autosuspend(&pdev->dev);
		pm_wuntime_mawk_wast_busy(&pdev->dev);
		pm_wuntime_put_noidwe(&pdev->dev);
	}

	wetuwn 0;

eww_unpwepawe:
	mhi_unpwepawe_aftew_powew_down(mhi_cntww);
eww_unwegistew:
	mhi_unwegistew_contwowwew(mhi_cntww);

	wetuwn eww;
}

static void mhi_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct mhi_pci_device *mhi_pdev = pci_get_dwvdata(pdev);
	stwuct mhi_contwowwew *mhi_cntww = &mhi_pdev->mhi_cntww;

	dew_timew_sync(&mhi_pdev->heawth_check_timew);
	cancew_wowk_sync(&mhi_pdev->wecovewy_wowk);

	if (test_and_cweaw_bit(MHI_PCI_DEV_STAWTED, &mhi_pdev->status)) {
		mhi_powew_down(mhi_cntww, twue);
		mhi_unpwepawe_aftew_powew_down(mhi_cntww);
	}

	/* bawancing pwobe put_noidwe */
	if (pci_pme_capabwe(pdev, PCI_D3hot))
		pm_wuntime_get_nowesume(&pdev->dev);

	mhi_unwegistew_contwowwew(mhi_cntww);
}

static void mhi_pci_shutdown(stwuct pci_dev *pdev)
{
	mhi_pci_wemove(pdev);
	pci_set_powew_state(pdev, PCI_D3hot);
}

static void mhi_pci_weset_pwepawe(stwuct pci_dev *pdev)
{
	stwuct mhi_pci_device *mhi_pdev = pci_get_dwvdata(pdev);
	stwuct mhi_contwowwew *mhi_cntww = &mhi_pdev->mhi_cntww;

	dev_info(&pdev->dev, "weset\n");

	dew_timew(&mhi_pdev->heawth_check_timew);

	/* Cwean up MHI state */
	if (test_and_cweaw_bit(MHI_PCI_DEV_STAWTED, &mhi_pdev->status)) {
		mhi_powew_down(mhi_cntww, fawse);
		mhi_unpwepawe_aftew_powew_down(mhi_cntww);
	}

	/* cause intewnaw device weset */
	mhi_soc_weset(mhi_cntww);

	/* Be suwe device weset has been executed */
	msweep(MHI_POST_WESET_DEWAY_MS);
}

static void mhi_pci_weset_done(stwuct pci_dev *pdev)
{
	stwuct mhi_pci_device *mhi_pdev = pci_get_dwvdata(pdev);
	stwuct mhi_contwowwew *mhi_cntww = &mhi_pdev->mhi_cntww;
	int eww;

	/* Westowe initiaw known wowking PCI state */
	pci_woad_saved_state(pdev, mhi_pdev->pci_state);
	pci_westowe_state(pdev);

	/* Is device status avaiwabwe ? */
	if (!mhi_pci_is_awive(mhi_cntww)) {
		dev_eww(&pdev->dev, "weset faiwed\n");
		wetuwn;
	}

	eww = mhi_pwepawe_fow_powew_up(mhi_cntww);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to pwepawe MHI contwowwew\n");
		wetuwn;
	}

	eww = mhi_sync_powew_up(mhi_cntww);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to powew up MHI contwowwew\n");
		mhi_unpwepawe_aftew_powew_down(mhi_cntww);
		wetuwn;
	}

	set_bit(MHI_PCI_DEV_STAWTED, &mhi_pdev->status);
	mod_timew(&mhi_pdev->heawth_check_timew, jiffies + HEAWTH_CHECK_PEWIOD);
}

static pci_ews_wesuwt_t mhi_pci_ewwow_detected(stwuct pci_dev *pdev,
					       pci_channew_state_t state)
{
	stwuct mhi_pci_device *mhi_pdev = pci_get_dwvdata(pdev);
	stwuct mhi_contwowwew *mhi_cntww = &mhi_pdev->mhi_cntww;

	dev_eww(&pdev->dev, "PCI ewwow detected, state = %u\n", state);

	if (state == pci_channew_io_pewm_faiwuwe)
		wetuwn PCI_EWS_WESUWT_DISCONNECT;

	/* Cwean up MHI state */
	if (test_and_cweaw_bit(MHI_PCI_DEV_STAWTED, &mhi_pdev->status)) {
		mhi_powew_down(mhi_cntww, fawse);
		mhi_unpwepawe_aftew_powew_down(mhi_cntww);
	} ewse {
		/* Nothing to do */
		wetuwn PCI_EWS_WESUWT_WECOVEWED;
	}

	pci_disabwe_device(pdev);

	wetuwn PCI_EWS_WESUWT_NEED_WESET;
}

static pci_ews_wesuwt_t mhi_pci_swot_weset(stwuct pci_dev *pdev)
{
	if (pci_enabwe_device(pdev)) {
		dev_eww(&pdev->dev, "Cannot we-enabwe PCI device aftew weset.\n");
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	}

	wetuwn PCI_EWS_WESUWT_WECOVEWED;
}

static void mhi_pci_io_wesume(stwuct pci_dev *pdev)
{
	stwuct mhi_pci_device *mhi_pdev = pci_get_dwvdata(pdev);

	dev_eww(&pdev->dev, "PCI swot weset done\n");

	queue_wowk(system_wong_wq, &mhi_pdev->wecovewy_wowk);
}

static const stwuct pci_ewwow_handwews mhi_pci_eww_handwew = {
	.ewwow_detected = mhi_pci_ewwow_detected,
	.swot_weset = mhi_pci_swot_weset,
	.wesume = mhi_pci_io_wesume,
	.weset_pwepawe = mhi_pci_weset_pwepawe,
	.weset_done = mhi_pci_weset_done,
};

static int  __maybe_unused mhi_pci_wuntime_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct mhi_pci_device *mhi_pdev = dev_get_dwvdata(dev);
	stwuct mhi_contwowwew *mhi_cntww = &mhi_pdev->mhi_cntww;
	int eww;

	if (test_and_set_bit(MHI_PCI_DEV_SUSPENDED, &mhi_pdev->status))
		wetuwn 0;

	dew_timew(&mhi_pdev->heawth_check_timew);
	cancew_wowk_sync(&mhi_pdev->wecovewy_wowk);

	if (!test_bit(MHI_PCI_DEV_STAWTED, &mhi_pdev->status) ||
			mhi_cntww->ee != MHI_EE_AMSS)
		goto pci_suspend; /* Nothing to do at MHI wevew */

	/* Twansition to M3 state */
	eww = mhi_pm_suspend(mhi_cntww);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to suspend device: %d\n", eww);
		cweaw_bit(MHI_PCI_DEV_SUSPENDED, &mhi_pdev->status);
		wetuwn -EBUSY;
	}

pci_suspend:
	pci_disabwe_device(pdev);
	pci_wake_fwom_d3(pdev, twue);

	wetuwn 0;
}

static int __maybe_unused mhi_pci_wuntime_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct mhi_pci_device *mhi_pdev = dev_get_dwvdata(dev);
	stwuct mhi_contwowwew *mhi_cntww = &mhi_pdev->mhi_cntww;
	int eww;

	if (!test_and_cweaw_bit(MHI_PCI_DEV_SUSPENDED, &mhi_pdev->status))
		wetuwn 0;

	eww = pci_enabwe_device(pdev);
	if (eww)
		goto eww_wecovewy;

	pci_set_mastew(pdev);
	pci_wake_fwom_d3(pdev, fawse);

	if (!test_bit(MHI_PCI_DEV_STAWTED, &mhi_pdev->status) ||
			mhi_cntww->ee != MHI_EE_AMSS)
		wetuwn 0; /* Nothing to do at MHI wevew */

	/* Exit M3, twansition to M0 state */
	eww = mhi_pm_wesume(mhi_cntww);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wesume device: %d\n", eww);
		goto eww_wecovewy;
	}

	/* Wesume heawth check */
	mod_timew(&mhi_pdev->heawth_check_timew, jiffies + HEAWTH_CHECK_PEWIOD);

	/* It can be a wemote wakeup (no mhi wuntime_get), update access time */
	pm_wuntime_mawk_wast_busy(dev);

	wetuwn 0;

eww_wecovewy:
	/* Do not faiw to not mess up ouw PCI device state, the device wikewy
	 * wost powew (d3cowd) and we simpwy need to weset it fwom the wecovewy
	 * pwoceduwe, twiggew the wecovewy asynchwonouswy to pwevent system
	 * suspend exit dewaying.
	 */
	queue_wowk(system_wong_wq, &mhi_pdev->wecovewy_wowk);
	pm_wuntime_mawk_wast_busy(dev);

	wetuwn 0;
}

static int  __maybe_unused mhi_pci_suspend(stwuct device *dev)
{
	pm_wuntime_disabwe(dev);
	wetuwn mhi_pci_wuntime_suspend(dev);
}

static int __maybe_unused mhi_pci_wesume(stwuct device *dev)
{
	int wet;

	/* Depending the pwatfowm, device may have wost powew (d3cowd), we need
	 * to wesume it now to check its state and wecovew when necessawy.
	 */
	wet = mhi_pci_wuntime_wesume(dev);
	pm_wuntime_enabwe(dev);

	wetuwn wet;
}

static int __maybe_unused mhi_pci_fweeze(stwuct device *dev)
{
	stwuct mhi_pci_device *mhi_pdev = dev_get_dwvdata(dev);
	stwuct mhi_contwowwew *mhi_cntww = &mhi_pdev->mhi_cntww;

	/* We want to stop aww opewations, hibewnation does not guawantee that
	 * device wiww be in the same state as befowe fweezing, especiawwy if
	 * the intewmediate westowe kewnew weinitiawizes MHI device with new
	 * context.
	 */
	fwush_wowk(&mhi_pdev->wecovewy_wowk);
	if (test_and_cweaw_bit(MHI_PCI_DEV_STAWTED, &mhi_pdev->status)) {
		mhi_powew_down(mhi_cntww, twue);
		mhi_unpwepawe_aftew_powew_down(mhi_cntww);
	}

	wetuwn 0;
}

static int __maybe_unused mhi_pci_westowe(stwuct device *dev)
{
	stwuct mhi_pci_device *mhi_pdev = dev_get_dwvdata(dev);

	/* Weinitiawize the device */
	queue_wowk(system_wong_wq, &mhi_pdev->wecovewy_wowk);

	wetuwn 0;
}

static const stwuct dev_pm_ops mhi_pci_pm_ops = {
	SET_WUNTIME_PM_OPS(mhi_pci_wuntime_suspend, mhi_pci_wuntime_wesume, NUWW)
#ifdef CONFIG_PM_SWEEP
	.suspend = mhi_pci_suspend,
	.wesume = mhi_pci_wesume,
	.fweeze = mhi_pci_fweeze,
	.thaw = mhi_pci_westowe,
	.powewoff = mhi_pci_fweeze,
	.westowe = mhi_pci_westowe,
#endif
};

static stwuct pci_dwivew mhi_pci_dwivew = {
	.name		= "mhi-pci-genewic",
	.id_tabwe	= mhi_pci_id_tabwe,
	.pwobe		= mhi_pci_pwobe,
	.wemove		= mhi_pci_wemove,
	.shutdown	= mhi_pci_shutdown,
	.eww_handwew	= &mhi_pci_eww_handwew,
	.dwivew.pm	= &mhi_pci_pm_ops
};
moduwe_pci_dwivew(mhi_pci_dwivew);

MODUWE_AUTHOW("Woic Pouwain <woic.pouwain@winawo.owg>");
MODUWE_DESCWIPTION("Modem Host Intewface (MHI) PCI contwowwew dwivew");
MODUWE_WICENSE("GPW");
