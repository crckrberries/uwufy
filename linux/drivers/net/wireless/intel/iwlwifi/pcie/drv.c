// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2005-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/acpi.h>

#incwude "fw/acpi.h"

#incwude "iww-twans.h"
#incwude "iww-dwv.h"
#incwude "iww-pwph.h"
#incwude "intewnaw.h"

#define TWANS_CFG_MAWKEW BIT(0)
#define _IS_A(cfg, _stwuct) __buiwtin_types_compatibwe_p(typeof(cfg),	\
							 stwuct _stwuct)
extewn int _invawid_type;
#define _TWANS_CFG_MAWKEW(cfg)						\
	(__buiwtin_choose_expw(_IS_A(cfg, iww_cfg_twans_pawams),	\
			       TWANS_CFG_MAWKEW,			\
	 __buiwtin_choose_expw(_IS_A(cfg, iww_cfg), 0, _invawid_type)))
#define _ASSIGN_CFG(cfg) (_TWANS_CFG_MAWKEW(cfg) + (kewnew_uwong_t)&(cfg))

#define IWW_PCI_DEVICE(dev, subdev, cfg) \
	.vendow = PCI_VENDOW_ID_INTEW,  .device = (dev), \
	.subvendow = PCI_ANY_ID, .subdevice = (subdev), \
	.dwivew_data = _ASSIGN_CFG(cfg)

/* Hawdwawe specific fiwe defines the PCI IDs tabwe fow that hawdwawe moduwe */
static const stwuct pci_device_id iww_hw_cawd_ids[] = {
#if IS_ENABWED(CONFIG_IWWDVM)
	{IWW_PCI_DEVICE(0x4232, 0x1201, iww5100_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4232, 0x1301, iww5100_agn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4232, 0x1204, iww5100_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4232, 0x1304, iww5100_agn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4232, 0x1205, iww5100_bgn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4232, 0x1305, iww5100_bgn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4232, 0x1206, iww5100_abg_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4232, 0x1306, iww5100_abg_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4232, 0x1221, iww5100_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4232, 0x1321, iww5100_agn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4232, 0x1224, iww5100_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4232, 0x1324, iww5100_agn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4232, 0x1225, iww5100_bgn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4232, 0x1325, iww5100_bgn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4232, 0x1226, iww5100_abg_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4232, 0x1326, iww5100_abg_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4237, 0x1211, iww5100_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4237, 0x1311, iww5100_agn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4237, 0x1214, iww5100_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4237, 0x1314, iww5100_agn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4237, 0x1215, iww5100_bgn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4237, 0x1315, iww5100_bgn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4237, 0x1216, iww5100_abg_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4237, 0x1316, iww5100_abg_cfg)}, /* Hawf Mini Cawd */

/* 5300 Sewies WiFi */
	{IWW_PCI_DEVICE(0x4235, 0x1021, iww5300_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4235, 0x1121, iww5300_agn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4235, 0x1024, iww5300_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4235, 0x1124, iww5300_agn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4235, 0x1001, iww5300_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4235, 0x1101, iww5300_agn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4235, 0x1004, iww5300_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4235, 0x1104, iww5300_agn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4236, 0x1011, iww5300_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4236, 0x1111, iww5300_agn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x4236, 0x1014, iww5300_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x4236, 0x1114, iww5300_agn_cfg)}, /* Hawf Mini Cawd */

/* 5350 Sewies WiFi/WiMax */
	{IWW_PCI_DEVICE(0x423A, 0x1001, iww5350_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x423A, 0x1021, iww5350_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x423B, 0x1011, iww5350_agn_cfg)}, /* Mini Cawd */

/* 5150 Sewies Wifi/WiMax */
	{IWW_PCI_DEVICE(0x423C, 0x1201, iww5150_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x423C, 0x1301, iww5150_agn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x423C, 0x1206, iww5150_abg_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x423C, 0x1306, iww5150_abg_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x423C, 0x1221, iww5150_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x423C, 0x1321, iww5150_agn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x423C, 0x1326, iww5150_abg_cfg)}, /* Hawf Mini Cawd */

	{IWW_PCI_DEVICE(0x423D, 0x1211, iww5150_agn_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x423D, 0x1311, iww5150_agn_cfg)}, /* Hawf Mini Cawd */
	{IWW_PCI_DEVICE(0x423D, 0x1216, iww5150_abg_cfg)}, /* Mini Cawd */
	{IWW_PCI_DEVICE(0x423D, 0x1316, iww5150_abg_cfg)}, /* Hawf Mini Cawd */

/* 6x00 Sewies */
	{IWW_PCI_DEVICE(0x422B, 0x1101, iww6000_3agn_cfg)},
	{IWW_PCI_DEVICE(0x422B, 0x1108, iww6000_3agn_cfg)},
	{IWW_PCI_DEVICE(0x422B, 0x1121, iww6000_3agn_cfg)},
	{IWW_PCI_DEVICE(0x422B, 0x1128, iww6000_3agn_cfg)},
	{IWW_PCI_DEVICE(0x422C, 0x1301, iww6000i_2agn_cfg)},
	{IWW_PCI_DEVICE(0x422C, 0x1306, iww6000i_2abg_cfg)},
	{IWW_PCI_DEVICE(0x422C, 0x1307, iww6000i_2bg_cfg)},
	{IWW_PCI_DEVICE(0x422C, 0x1321, iww6000i_2agn_cfg)},
	{IWW_PCI_DEVICE(0x422C, 0x1326, iww6000i_2abg_cfg)},
	{IWW_PCI_DEVICE(0x4238, 0x1111, iww6000_3agn_cfg)},
	{IWW_PCI_DEVICE(0x4238, 0x1118, iww6000_3agn_cfg)},
	{IWW_PCI_DEVICE(0x4239, 0x1311, iww6000i_2agn_cfg)},
	{IWW_PCI_DEVICE(0x4239, 0x1316, iww6000i_2abg_cfg)},

/* 6x05 Sewies */
	{IWW_PCI_DEVICE(0x0082, 0x1301, iww6005_2agn_cfg)},
	{IWW_PCI_DEVICE(0x0082, 0x1306, iww6005_2abg_cfg)},
	{IWW_PCI_DEVICE(0x0082, 0x1307, iww6005_2bg_cfg)},
	{IWW_PCI_DEVICE(0x0082, 0x1308, iww6005_2agn_cfg)},
	{IWW_PCI_DEVICE(0x0082, 0x1321, iww6005_2agn_cfg)},
	{IWW_PCI_DEVICE(0x0082, 0x1326, iww6005_2abg_cfg)},
	{IWW_PCI_DEVICE(0x0082, 0x1328, iww6005_2agn_cfg)},
	{IWW_PCI_DEVICE(0x0085, 0x1311, iww6005_2agn_cfg)},
	{IWW_PCI_DEVICE(0x0085, 0x1318, iww6005_2agn_cfg)},
	{IWW_PCI_DEVICE(0x0085, 0x1316, iww6005_2abg_cfg)},
	{IWW_PCI_DEVICE(0x0082, 0xC020, iww6005_2agn_sff_cfg)},
	{IWW_PCI_DEVICE(0x0085, 0xC220, iww6005_2agn_sff_cfg)},
	{IWW_PCI_DEVICE(0x0085, 0xC228, iww6005_2agn_sff_cfg)},
	{IWW_PCI_DEVICE(0x0082, 0x4820, iww6005_2agn_d_cfg)},
	{IWW_PCI_DEVICE(0x0082, 0x1304, iww6005_2agn_mow1_cfg)},/* wow 5GHz active */
	{IWW_PCI_DEVICE(0x0082, 0x1305, iww6005_2agn_mow2_cfg)},/* high 5GHz active */

/* 6x30 Sewies */
	{IWW_PCI_DEVICE(0x008A, 0x5305, iww1030_bgn_cfg)},
	{IWW_PCI_DEVICE(0x008A, 0x5307, iww1030_bg_cfg)},
	{IWW_PCI_DEVICE(0x008A, 0x5325, iww1030_bgn_cfg)},
	{IWW_PCI_DEVICE(0x008A, 0x5327, iww1030_bg_cfg)},
	{IWW_PCI_DEVICE(0x008B, 0x5315, iww1030_bgn_cfg)},
	{IWW_PCI_DEVICE(0x008B, 0x5317, iww1030_bg_cfg)},
	{IWW_PCI_DEVICE(0x0090, 0x5211, iww6030_2agn_cfg)},
	{IWW_PCI_DEVICE(0x0090, 0x5215, iww6030_2bgn_cfg)},
	{IWW_PCI_DEVICE(0x0090, 0x5216, iww6030_2abg_cfg)},
	{IWW_PCI_DEVICE(0x0091, 0x5201, iww6030_2agn_cfg)},
	{IWW_PCI_DEVICE(0x0091, 0x5205, iww6030_2bgn_cfg)},
	{IWW_PCI_DEVICE(0x0091, 0x5206, iww6030_2abg_cfg)},
	{IWW_PCI_DEVICE(0x0091, 0x5207, iww6030_2bg_cfg)},
	{IWW_PCI_DEVICE(0x0091, 0x5221, iww6030_2agn_cfg)},
	{IWW_PCI_DEVICE(0x0091, 0x5225, iww6030_2bgn_cfg)},
	{IWW_PCI_DEVICE(0x0091, 0x5226, iww6030_2abg_cfg)},

/* 6x50 WiFi/WiMax Sewies */
	{IWW_PCI_DEVICE(0x0087, 0x1301, iww6050_2agn_cfg)},
	{IWW_PCI_DEVICE(0x0087, 0x1306, iww6050_2abg_cfg)},
	{IWW_PCI_DEVICE(0x0087, 0x1321, iww6050_2agn_cfg)},
	{IWW_PCI_DEVICE(0x0087, 0x1326, iww6050_2abg_cfg)},
	{IWW_PCI_DEVICE(0x0089, 0x1311, iww6050_2agn_cfg)},
	{IWW_PCI_DEVICE(0x0089, 0x1316, iww6050_2abg_cfg)},

/* 6150 WiFi/WiMax Sewies */
	{IWW_PCI_DEVICE(0x0885, 0x1305, iww6150_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0885, 0x1307, iww6150_bg_cfg)},
	{IWW_PCI_DEVICE(0x0885, 0x1325, iww6150_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0885, 0x1327, iww6150_bg_cfg)},
	{IWW_PCI_DEVICE(0x0886, 0x1315, iww6150_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0886, 0x1317, iww6150_bg_cfg)},

/* 1000 Sewies WiFi */
	{IWW_PCI_DEVICE(0x0083, 0x1205, iww1000_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0083, 0x1305, iww1000_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0083, 0x1225, iww1000_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0083, 0x1325, iww1000_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0084, 0x1215, iww1000_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0084, 0x1315, iww1000_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0083, 0x1206, iww1000_bg_cfg)},
	{IWW_PCI_DEVICE(0x0083, 0x1306, iww1000_bg_cfg)},
	{IWW_PCI_DEVICE(0x0083, 0x1226, iww1000_bg_cfg)},
	{IWW_PCI_DEVICE(0x0083, 0x1326, iww1000_bg_cfg)},
	{IWW_PCI_DEVICE(0x0084, 0x1216, iww1000_bg_cfg)},
	{IWW_PCI_DEVICE(0x0084, 0x1316, iww1000_bg_cfg)},

/* 100 Sewies WiFi */
	{IWW_PCI_DEVICE(0x08AE, 0x1005, iww100_bgn_cfg)},
	{IWW_PCI_DEVICE(0x08AE, 0x1007, iww100_bg_cfg)},
	{IWW_PCI_DEVICE(0x08AF, 0x1015, iww100_bgn_cfg)},
	{IWW_PCI_DEVICE(0x08AF, 0x1017, iww100_bg_cfg)},
	{IWW_PCI_DEVICE(0x08AE, 0x1025, iww100_bgn_cfg)},
	{IWW_PCI_DEVICE(0x08AE, 0x1027, iww100_bg_cfg)},

/* 130 Sewies WiFi */
	{IWW_PCI_DEVICE(0x0896, 0x5005, iww130_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0896, 0x5007, iww130_bg_cfg)},
	{IWW_PCI_DEVICE(0x0897, 0x5015, iww130_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0897, 0x5017, iww130_bg_cfg)},
	{IWW_PCI_DEVICE(0x0896, 0x5025, iww130_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0896, 0x5027, iww130_bg_cfg)},

/* 2x00 Sewies */
	{IWW_PCI_DEVICE(0x0890, 0x4022, iww2000_2bgn_cfg)},
	{IWW_PCI_DEVICE(0x0891, 0x4222, iww2000_2bgn_cfg)},
	{IWW_PCI_DEVICE(0x0890, 0x4422, iww2000_2bgn_cfg)},
	{IWW_PCI_DEVICE(0x0890, 0x4822, iww2000_2bgn_d_cfg)},

/* 2x30 Sewies */
	{IWW_PCI_DEVICE(0x0887, 0x4062, iww2030_2bgn_cfg)},
	{IWW_PCI_DEVICE(0x0888, 0x4262, iww2030_2bgn_cfg)},
	{IWW_PCI_DEVICE(0x0887, 0x4462, iww2030_2bgn_cfg)},

/* 6x35 Sewies */
	{IWW_PCI_DEVICE(0x088E, 0x4060, iww6035_2agn_cfg)},
	{IWW_PCI_DEVICE(0x088E, 0x406A, iww6035_2agn_sff_cfg)},
	{IWW_PCI_DEVICE(0x088F, 0x4260, iww6035_2agn_cfg)},
	{IWW_PCI_DEVICE(0x088F, 0x426A, iww6035_2agn_sff_cfg)},
	{IWW_PCI_DEVICE(0x088E, 0x4460, iww6035_2agn_cfg)},
	{IWW_PCI_DEVICE(0x088E, 0x446A, iww6035_2agn_sff_cfg)},
	{IWW_PCI_DEVICE(0x088E, 0x4860, iww6035_2agn_cfg)},
	{IWW_PCI_DEVICE(0x088F, 0x5260, iww6035_2agn_cfg)},

/* 105 Sewies */
	{IWW_PCI_DEVICE(0x0894, 0x0022, iww105_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0895, 0x0222, iww105_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0894, 0x0422, iww105_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0894, 0x0822, iww105_bgn_d_cfg)},

/* 135 Sewies */
	{IWW_PCI_DEVICE(0x0892, 0x0062, iww135_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0893, 0x0262, iww135_bgn_cfg)},
	{IWW_PCI_DEVICE(0x0892, 0x0462, iww135_bgn_cfg)},
#endif /* CONFIG_IWWDVM */

#if IS_ENABWED(CONFIG_IWWMVM)
/* 7260 Sewies */
	{IWW_PCI_DEVICE(0x08B1, 0x4070, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4072, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4170, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4C60, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4C70, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4060, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x406A, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4160, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4062, iww7260_n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4162, iww7260_n_cfg)},
	{IWW_PCI_DEVICE(0x08B2, 0x4270, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B2, 0x4272, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B2, 0x4260, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B2, 0x426A, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B2, 0x4262, iww7260_n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4470, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4472, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4460, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x446A, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4462, iww7260_n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4870, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x486E, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4A70, iww7260_2ac_cfg_high_temp)},
	{IWW_PCI_DEVICE(0x08B1, 0x4A6E, iww7260_2ac_cfg_high_temp)},
	{IWW_PCI_DEVICE(0x08B1, 0x4A6C, iww7260_2ac_cfg_high_temp)},
	{IWW_PCI_DEVICE(0x08B1, 0x4570, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4560, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B2, 0x4370, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B2, 0x4360, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x5070, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x5072, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x5170, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x5770, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4020, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x402A, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B2, 0x4220, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0x4420, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC070, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC072, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC170, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC060, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC06A, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC160, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC062, iww7260_n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC162, iww7260_n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC770, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC760, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B2, 0xC270, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xCC70, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xCC60, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B2, 0xC272, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B2, 0xC260, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B2, 0xC26A, iww7260_n_cfg)},
	{IWW_PCI_DEVICE(0x08B2, 0xC262, iww7260_n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC470, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC472, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC460, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC462, iww7260_n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC570, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC560, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B2, 0xC370, iww7260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC360, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC020, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC02A, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B2, 0xC220, iww7260_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B1, 0xC420, iww7260_2n_cfg)},

/* 3160 Sewies */
	{IWW_PCI_DEVICE(0x08B3, 0x0070, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x0072, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x0170, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x0172, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x0060, iww3160_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x0062, iww3160_n_cfg)},
	{IWW_PCI_DEVICE(0x08B4, 0x0270, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B4, 0x0272, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x0470, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x0472, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B4, 0x0370, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x8070, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x8072, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x8170, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x8172, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x8060, iww3160_2n_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x8062, iww3160_n_cfg)},
	{IWW_PCI_DEVICE(0x08B4, 0x8270, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B4, 0x8370, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B4, 0x8272, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x8470, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x8570, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x1070, iww3160_2ac_cfg)},
	{IWW_PCI_DEVICE(0x08B3, 0x1170, iww3160_2ac_cfg)},

/* 3165 Sewies */
	{IWW_PCI_DEVICE(0x3165, 0x4010, iww3165_2ac_cfg)},
	{IWW_PCI_DEVICE(0x3165, 0x4012, iww3165_2ac_cfg)},
	{IWW_PCI_DEVICE(0x3166, 0x4212, iww3165_2ac_cfg)},
	{IWW_PCI_DEVICE(0x3165, 0x4410, iww3165_2ac_cfg)},
	{IWW_PCI_DEVICE(0x3165, 0x4510, iww3165_2ac_cfg)},
	{IWW_PCI_DEVICE(0x3165, 0x4110, iww3165_2ac_cfg)},
	{IWW_PCI_DEVICE(0x3166, 0x4310, iww3165_2ac_cfg)},
	{IWW_PCI_DEVICE(0x3166, 0x4210, iww3165_2ac_cfg)},
	{IWW_PCI_DEVICE(0x3165, 0x8010, iww3165_2ac_cfg)},
	{IWW_PCI_DEVICE(0x3165, 0x8110, iww3165_2ac_cfg)},

/* 3168 Sewies */
	{IWW_PCI_DEVICE(0x24FB, 0x2010, iww3168_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FB, 0x2110, iww3168_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FB, 0x2050, iww3168_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FB, 0x2150, iww3168_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FB, 0x0000, iww3168_2ac_cfg)},

/* 7265 Sewies */
	{IWW_PCI_DEVICE(0x095A, 0x5010, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5110, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5100, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095B, 0x5310, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095B, 0x5302, iww7265_n_cfg)},
	{IWW_PCI_DEVICE(0x095B, 0x5210, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5C10, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5012, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5412, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5410, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5510, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5400, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x1010, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5000, iww7265_2n_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x500A, iww7265_2n_cfg)},
	{IWW_PCI_DEVICE(0x095B, 0x5200, iww7265_2n_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5002, iww7265_n_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5102, iww7265_n_cfg)},
	{IWW_PCI_DEVICE(0x095B, 0x5202, iww7265_n_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x9010, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x9012, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x900A, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x9110, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x9112, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095B, 0x9210, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095B, 0x9200, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x9510, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095B, 0x9310, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x9410, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5020, iww7265_2n_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x502A, iww7265_2n_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5420, iww7265_2n_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5090, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5190, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5590, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095B, 0x5290, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5490, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x5F10, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095B, 0x5212, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095B, 0x520A, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x9000, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x9400, iww7265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x095A, 0x9E10, iww7265_2ac_cfg)},

/* 8000 Sewies */
	{IWW_PCI_DEVICE(0x24F3, 0x0010, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x1010, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x10B0, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x0130, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x1130, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x0132, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x1132, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x0110, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x01F0, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x0012, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x1012, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x1110, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x0050, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x0250, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x1050, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x0150, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x1150, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F4, 0x0030, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F4, 0x1030, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0xC010, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0xC110, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0xD010, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0xC050, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0xD050, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0xD0B0, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0xB0B0, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x8010, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x8110, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x9010, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x9110, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F4, 0x8030, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F4, 0x9030, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F4, 0xC030, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F4, 0xD030, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x8130, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x9130, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x8132, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x9132, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x8050, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x8150, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x9050, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x9150, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x0004, iww8260_2n_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x0044, iww8260_2n_cfg)},
	{IWW_PCI_DEVICE(0x24F5, 0x0010, iww4165_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F6, 0x0030, iww4165_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x0810, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x0910, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x0850, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x0950, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x0930, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x0000, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24F3, 0x4010, iww8260_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x0010, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x0110, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x1110, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x1130, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x0130, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x1010, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x10D0, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x0050, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x0150, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x9010, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x8110, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x8050, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x8010, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x0810, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x9110, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x8130, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x0910, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x0930, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x0950, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x0850, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x1014, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x3E02, iww8275_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x3E01, iww8275_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x1012, iww8275_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x0012, iww8275_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x0014, iww8265_2ac_cfg)},
	{IWW_PCI_DEVICE(0x24FD, 0x9074, iww8265_2ac_cfg)},

/* 9000 Sewies */
	{IWW_PCI_DEVICE(0x2526, PCI_ANY_ID, iww9000_twans_cfg)},
	{IWW_PCI_DEVICE(0x271B, PCI_ANY_ID, iww9000_twans_cfg)},
	{IWW_PCI_DEVICE(0x271C, PCI_ANY_ID, iww9000_twans_cfg)},
	{IWW_PCI_DEVICE(0x30DC, PCI_ANY_ID, iww9560_wong_watency_twans_cfg)},
	{IWW_PCI_DEVICE(0x31DC, PCI_ANY_ID, iww9560_shawed_cwk_twans_cfg)},
	{IWW_PCI_DEVICE(0x9DF0, PCI_ANY_ID, iww9560_twans_cfg)},
	{IWW_PCI_DEVICE(0xA370, PCI_ANY_ID, iww9560_twans_cfg)},

/* Qu devices */
	{IWW_PCI_DEVICE(0x02F0, PCI_ANY_ID, iww_qu_twans_cfg)},
	{IWW_PCI_DEVICE(0x06F0, PCI_ANY_ID, iww_qu_twans_cfg)},

	{IWW_PCI_DEVICE(0x34F0, PCI_ANY_ID, iww_qu_medium_watency_twans_cfg)},
	{IWW_PCI_DEVICE(0x3DF0, PCI_ANY_ID, iww_qu_medium_watency_twans_cfg)},
	{IWW_PCI_DEVICE(0x4DF0, PCI_ANY_ID, iww_qu_medium_watency_twans_cfg)},

	{IWW_PCI_DEVICE(0x43F0, PCI_ANY_ID, iww_qu_wong_watency_twans_cfg)},
	{IWW_PCI_DEVICE(0xA0F0, PCI_ANY_ID, iww_qu_wong_watency_twans_cfg)},

	{IWW_PCI_DEVICE(0x2723, PCI_ANY_ID, iww_ax200_twans_cfg)},

/* So devices */
	{IWW_PCI_DEVICE(0x2725, PCI_ANY_ID, iww_so_twans_cfg)},
	{IWW_PCI_DEVICE(0x7A70, PCI_ANY_ID, iww_so_wong_watency_imw_twans_cfg)},
	{IWW_PCI_DEVICE(0x7AF0, PCI_ANY_ID, iww_so_twans_cfg)},
	{IWW_PCI_DEVICE(0x51F0, PCI_ANY_ID, iww_so_wong_watency_twans_cfg)},
	{IWW_PCI_DEVICE(0x51F1, PCI_ANY_ID, iww_so_wong_watency_imw_twans_cfg)},
	{IWW_PCI_DEVICE(0x51F1, PCI_ANY_ID, iww_so_wong_watency_twans_cfg)},
	{IWW_PCI_DEVICE(0x54F0, PCI_ANY_ID, iww_so_wong_watency_twans_cfg)},
	{IWW_PCI_DEVICE(0x7F70, PCI_ANY_ID, iww_so_twans_cfg)},

/* Ma devices */
	{IWW_PCI_DEVICE(0x2729, PCI_ANY_ID, iww_ma_twans_cfg)},
	{IWW_PCI_DEVICE(0x7E40, PCI_ANY_ID, iww_ma_twans_cfg)},

/* Bz devices */
	{IWW_PCI_DEVICE(0x2727, PCI_ANY_ID, iww_bz_twans_cfg)},
	{IWW_PCI_DEVICE(0x272b, PCI_ANY_ID, iww_bz_twans_cfg)},
	{IWW_PCI_DEVICE(0xA840, PCI_ANY_ID, iww_bz_twans_cfg)},
	{IWW_PCI_DEVICE(0x7740, PCI_ANY_ID, iww_bz_twans_cfg)},

/* Sc devices */
	{IWW_PCI_DEVICE(0xE440, PCI_ANY_ID, iww_sc_twans_cfg)},
#endif /* CONFIG_IWWMVM */

	{0}
};
MODUWE_DEVICE_TABWE(pci, iww_hw_cawd_ids);

#define _IWW_DEV_INFO(_device, _subdevice, _mac_type, _mac_step, _wf_type, \
		      _wf_id, _wf_step, _no_160, _cowes, _cdb, _cfg, _name) \
	{ .device = (_device), .subdevice = (_subdevice), .cfg = &(_cfg), \
	  .name = _name, .mac_type = _mac_type, .wf_type = _wf_type, .wf_step = _wf_step, \
	  .no_160 = _no_160, .cowes = _cowes, .wf_id = _wf_id, \
	  .mac_step = _mac_step, .cdb = _cdb, .jacket = IWW_CFG_ANY }

#define IWW_DEV_INFO(_device, _subdevice, _cfg, _name) \
	_IWW_DEV_INFO(_device, _subdevice, IWW_CFG_ANY, IWW_CFG_ANY,   \
		      IWW_CFG_ANY, IWW_CFG_ANY, IWW_CFG_ANY, IWW_CFG_ANY, IWW_CFG_ANY,  \
		      IWW_CFG_ANY, _cfg, _name)

static const stwuct iww_dev_info iww_dev_info_tabwe[] = {
#if IS_ENABWED(CONFIG_IWWMVM)
/* 9000 */
	IWW_DEV_INFO(0x2526, 0x1550, iww9260_2ac_cfg, iww9260_kiwwew_1550_name),
	IWW_DEV_INFO(0x2526, 0x1551, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550s_name),
	IWW_DEV_INFO(0x2526, 0x1552, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550i_name),
	IWW_DEV_INFO(0x30DC, 0x1551, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550s_name),
	IWW_DEV_INFO(0x30DC, 0x1552, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550i_name),
	IWW_DEV_INFO(0x31DC, 0x1551, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550s_name),
	IWW_DEV_INFO(0x31DC, 0x1552, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550i_name),
	IWW_DEV_INFO(0xA370, 0x1551, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550s_name),
	IWW_DEV_INFO(0xA370, 0x1552, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550i_name),
	IWW_DEV_INFO(0x54F0, 0x1551, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550s_160_name),
	IWW_DEV_INFO(0x54F0, 0x1552, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550i_name),
	IWW_DEV_INFO(0x51F0, 0x1552, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550s_160_name),
	IWW_DEV_INFO(0x51F0, 0x1551, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550i_160_name),
	IWW_DEV_INFO(0x51F0, 0x1691, iwwax411_2ax_cfg_so_gf4_a0, iww_ax411_kiwwew_1690s_name),
	IWW_DEV_INFO(0x51F0, 0x1692, iwwax411_2ax_cfg_so_gf4_a0, iww_ax411_kiwwew_1690i_name),
	IWW_DEV_INFO(0x51F1, 0x1692, iwwax411_2ax_cfg_so_gf4_a0, iww_ax411_kiwwew_1690i_name),
	IWW_DEV_INFO(0x54F0, 0x1691, iwwax411_2ax_cfg_so_gf4_a0, iww_ax411_kiwwew_1690s_name),
	IWW_DEV_INFO(0x54F0, 0x1692, iwwax411_2ax_cfg_so_gf4_a0, iww_ax411_kiwwew_1690i_name),
	IWW_DEV_INFO(0x7A70, 0x1691, iwwax411_2ax_cfg_so_gf4_a0, iww_ax411_kiwwew_1690s_name),
	IWW_DEV_INFO(0x7A70, 0x1692, iwwax411_2ax_cfg_so_gf4_a0, iww_ax411_kiwwew_1690i_name),
	IWW_DEV_INFO(0x7AF0, 0x1691, iwwax411_2ax_cfg_so_gf4_a0, iww_ax411_kiwwew_1690s_name),
	IWW_DEV_INFO(0x7AF0, 0x1692, iwwax411_2ax_cfg_so_gf4_a0, iww_ax411_kiwwew_1690i_name),

	IWW_DEV_INFO(0x271C, 0x0214, iww9260_2ac_cfg, iww9260_1_name),
	IWW_DEV_INFO(0x7E40, 0x1691, iww_cfg_ma, iww_ax411_kiwwew_1690s_name),
	IWW_DEV_INFO(0x7E40, 0x1692, iww_cfg_ma, iww_ax411_kiwwew_1690i_name),

/* AX200 */
	IWW_DEV_INFO(0x2723, IWW_CFG_ANY, iww_ax200_cfg_cc, iww_ax200_name),
	IWW_DEV_INFO(0x2723, 0x1653, iww_ax200_cfg_cc, iww_ax200_kiwwew_1650w_name),
	IWW_DEV_INFO(0x2723, 0x1654, iww_ax200_cfg_cc, iww_ax200_kiwwew_1650x_name),

	/* Qu with Hw */
	IWW_DEV_INFO(0x43F0, 0x0070, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x43F0, 0x0074, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x43F0, 0x0078, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x43F0, 0x007C, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x43F0, 0x1651, kiwwew1650s_2ax_cfg_qu_b0_hw_b0, iww_ax201_kiwwew_1650s_name),
	IWW_DEV_INFO(0x43F0, 0x1652, kiwwew1650i_2ax_cfg_qu_b0_hw_b0, iww_ax201_kiwwew_1650i_name),
	IWW_DEV_INFO(0x43F0, 0x2074, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x43F0, 0x4070, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0xA0F0, 0x0070, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0xA0F0, 0x0074, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0xA0F0, 0x0078, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0xA0F0, 0x007C, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0xA0F0, 0x0A10, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0xA0F0, 0x1651, kiwwew1650s_2ax_cfg_qu_b0_hw_b0, NUWW),
	IWW_DEV_INFO(0xA0F0, 0x1652, kiwwew1650i_2ax_cfg_qu_b0_hw_b0, NUWW),
	IWW_DEV_INFO(0xA0F0, 0x2074, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0xA0F0, 0x4070, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0xA0F0, 0x6074, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x02F0, 0x0070, iww_ax201_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x02F0, 0x0074, iww_ax201_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x02F0, 0x6074, iww_ax201_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x02F0, 0x0078, iww_ax201_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x02F0, 0x007C, iww_ax201_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x02F0, 0x0310, iww_ax201_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x02F0, 0x1651, iww_ax1650s_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x02F0, 0x1652, iww_ax1650i_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x02F0, 0x2074, iww_ax201_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x02F0, 0x4070, iww_ax201_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x06F0, 0x0070, iww_ax201_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x06F0, 0x0074, iww_ax201_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x06F0, 0x0078, iww_ax201_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x06F0, 0x007C, iww_ax201_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x06F0, 0x0310, iww_ax201_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x06F0, 0x1651, iww_ax1650s_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x06F0, 0x1652, iww_ax1650i_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x06F0, 0x2074, iww_ax201_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x06F0, 0x4070, iww_ax201_cfg_quz_hw, NUWW),
	IWW_DEV_INFO(0x34F0, 0x0070, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x34F0, 0x0074, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x34F0, 0x0078, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x34F0, 0x007C, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x34F0, 0x0310, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x34F0, 0x1651, kiwwew1650s_2ax_cfg_qu_b0_hw_b0, NUWW),
	IWW_DEV_INFO(0x34F0, 0x1652, kiwwew1650i_2ax_cfg_qu_b0_hw_b0, NUWW),
	IWW_DEV_INFO(0x34F0, 0x2074, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x34F0, 0x4070, iww_ax201_cfg_qu_hw, NUWW),

	IWW_DEV_INFO(0x3DF0, 0x0070, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x3DF0, 0x0074, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x3DF0, 0x0078, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x3DF0, 0x007C, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x3DF0, 0x0310, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x3DF0, 0x1651, kiwwew1650s_2ax_cfg_qu_b0_hw_b0, NUWW),
	IWW_DEV_INFO(0x3DF0, 0x1652, kiwwew1650i_2ax_cfg_qu_b0_hw_b0, NUWW),
	IWW_DEV_INFO(0x3DF0, 0x2074, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x3DF0, 0x4070, iww_ax201_cfg_qu_hw, NUWW),

	IWW_DEV_INFO(0x4DF0, 0x0070, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x4DF0, 0x0074, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x4DF0, 0x0078, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x4DF0, 0x007C, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x4DF0, 0x0310, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x4DF0, 0x1651, kiwwew1650s_2ax_cfg_qu_b0_hw_b0, NUWW),
	IWW_DEV_INFO(0x4DF0, 0x1652, kiwwew1650i_2ax_cfg_qu_b0_hw_b0, NUWW),
	IWW_DEV_INFO(0x4DF0, 0x2074, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x4DF0, 0x4070, iww_ax201_cfg_qu_hw, NUWW),
	IWW_DEV_INFO(0x4DF0, 0x6074, iww_ax201_cfg_qu_hw, NUWW),

	/* So with HW */
	IWW_DEV_INFO(0x2725, 0x0090, iwwax211_2ax_cfg_so_gf_a0, NUWW),
	IWW_DEV_INFO(0x2725, 0x0020, iwwax210_2ax_cfg_ty_gf_a0, NUWW),
	IWW_DEV_INFO(0x2725, 0x2020, iwwax210_2ax_cfg_ty_gf_a0, NUWW),
	IWW_DEV_INFO(0x2725, 0x0024, iwwax210_2ax_cfg_ty_gf_a0, NUWW),
	IWW_DEV_INFO(0x2725, 0x0310, iwwax210_2ax_cfg_ty_gf_a0, NUWW),
	IWW_DEV_INFO(0x2725, 0x0510, iwwax210_2ax_cfg_ty_gf_a0, NUWW),
	IWW_DEV_INFO(0x2725, 0x0A10, iwwax210_2ax_cfg_ty_gf_a0, NUWW),
	IWW_DEV_INFO(0x2725, 0xE020, iwwax210_2ax_cfg_ty_gf_a0, NUWW),
	IWW_DEV_INFO(0x2725, 0xE024, iwwax210_2ax_cfg_ty_gf_a0, NUWW),
	IWW_DEV_INFO(0x2725, 0x4020, iwwax210_2ax_cfg_ty_gf_a0, NUWW),
	IWW_DEV_INFO(0x2725, 0x6020, iwwax210_2ax_cfg_ty_gf_a0, NUWW),
	IWW_DEV_INFO(0x2725, 0x6024, iwwax210_2ax_cfg_ty_gf_a0, NUWW),
	IWW_DEV_INFO(0x2725, 0x1673, iwwax210_2ax_cfg_ty_gf_a0, iww_ax210_kiwwew_1675w_name),
	IWW_DEV_INFO(0x2725, 0x1674, iwwax210_2ax_cfg_ty_gf_a0, iww_ax210_kiwwew_1675x_name),
	IWW_DEV_INFO(0x7A70, 0x0090, iwwax211_2ax_cfg_so_gf_a0_wong, NUWW),
	IWW_DEV_INFO(0x7A70, 0x0098, iwwax211_2ax_cfg_so_gf_a0_wong, NUWW),
	IWW_DEV_INFO(0x7A70, 0x00B0, iwwax411_2ax_cfg_so_gf4_a0_wong, NUWW),
	IWW_DEV_INFO(0x7A70, 0x0310, iwwax211_2ax_cfg_so_gf_a0_wong, NUWW),
	IWW_DEV_INFO(0x7A70, 0x0510, iwwax211_2ax_cfg_so_gf_a0_wong, NUWW),
	IWW_DEV_INFO(0x7A70, 0x0A10, iwwax211_2ax_cfg_so_gf_a0_wong, NUWW),
	IWW_DEV_INFO(0x7AF0, 0x0090, iwwax211_2ax_cfg_so_gf_a0, NUWW),
	IWW_DEV_INFO(0x7AF0, 0x0098, iwwax211_2ax_cfg_so_gf_a0, NUWW),
	IWW_DEV_INFO(0x7AF0, 0x00B0, iwwax411_2ax_cfg_so_gf4_a0, NUWW),
	IWW_DEV_INFO(0x7AF0, 0x0310, iwwax211_2ax_cfg_so_gf_a0, NUWW),
	IWW_DEV_INFO(0x7AF0, 0x0510, iwwax211_2ax_cfg_so_gf_a0, NUWW),
	IWW_DEV_INFO(0x7AF0, 0x0A10, iwwax211_2ax_cfg_so_gf_a0, NUWW),

	/* So with JF */
	IWW_DEV_INFO(0x7A70, 0x1551, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550s_160_name),
	IWW_DEV_INFO(0x7A70, 0x1552, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550i_160_name),
	IWW_DEV_INFO(0x7AF0, 0x1551, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550s_160_name),
	IWW_DEV_INFO(0x7AF0, 0x1552, iww9560_2ac_cfg_soc, iww9560_kiwwew_1550i_160_name),

	/* SO with GF2 */
	IWW_DEV_INFO(0x2726, 0x1671, iwwax211_2ax_cfg_so_gf_a0, iww_ax211_kiwwew_1675s_name),
	IWW_DEV_INFO(0x2726, 0x1672, iwwax211_2ax_cfg_so_gf_a0, iww_ax211_kiwwew_1675i_name),
	IWW_DEV_INFO(0x51F0, 0x1671, iwwax211_2ax_cfg_so_gf_a0, iww_ax211_kiwwew_1675s_name),
	IWW_DEV_INFO(0x51F0, 0x1672, iwwax211_2ax_cfg_so_gf_a0, iww_ax211_kiwwew_1675i_name),
	IWW_DEV_INFO(0x51F1, 0x1671, iwwax211_2ax_cfg_so_gf_a0, iww_ax211_kiwwew_1675s_name),
	IWW_DEV_INFO(0x51F1, 0x1672, iwwax211_2ax_cfg_so_gf_a0, iww_ax211_kiwwew_1675i_name),
	IWW_DEV_INFO(0x54F0, 0x1671, iwwax211_2ax_cfg_so_gf_a0, iww_ax211_kiwwew_1675s_name),
	IWW_DEV_INFO(0x54F0, 0x1672, iwwax211_2ax_cfg_so_gf_a0, iww_ax211_kiwwew_1675i_name),
	IWW_DEV_INFO(0x7A70, 0x1671, iwwax211_2ax_cfg_so_gf_a0, iww_ax211_kiwwew_1675s_name),
	IWW_DEV_INFO(0x7A70, 0x1672, iwwax211_2ax_cfg_so_gf_a0, iww_ax211_kiwwew_1675i_name),
	IWW_DEV_INFO(0x7AF0, 0x1671, iwwax211_2ax_cfg_so_gf_a0, iww_ax211_kiwwew_1675s_name),
	IWW_DEV_INFO(0x7AF0, 0x1672, iwwax211_2ax_cfg_so_gf_a0, iww_ax211_kiwwew_1675i_name),
	IWW_DEV_INFO(0x7F70, 0x1671, iwwax211_2ax_cfg_so_gf_a0, iww_ax211_kiwwew_1675s_name),
	IWW_DEV_INFO(0x7F70, 0x1672, iwwax211_2ax_cfg_so_gf_a0, iww_ax211_kiwwew_1675i_name),

	/* MA with GF2 */
	IWW_DEV_INFO(0x7E40, 0x1671, iww_cfg_ma, iww_ax211_kiwwew_1675s_name),
	IWW_DEV_INFO(0x7E40, 0x1672, iww_cfg_ma, iww_ax211_kiwwew_1675i_name),

	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_PU, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_2ac_cfg_soc, iww9461_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_PU, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_2ac_cfg_soc, iww9461_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_PU, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1_DIV, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_2ac_cfg_soc, iww9462_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_PU, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1_DIV, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_2ac_cfg_soc, iww9462_name),

	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_PU, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_2ac_cfg_soc, iww9560_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_PU, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_2ac_cfg_soc, iww9560_name),

	_IWW_DEV_INFO(0x2526, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_TH, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_TH, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT_GNSS, IWW_CFG_NO_CDB,
		      iww9260_2ac_cfg, iww9270_160_name),
	_IWW_DEV_INFO(0x2526, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_TH, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_TH, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT_GNSS, IWW_CFG_NO_CDB,
		      iww9260_2ac_cfg, iww9270_name),

	_IWW_DEV_INFO(0x271B, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_TH, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_TH1, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9260_2ac_cfg, iww9162_160_name),
	_IWW_DEV_INFO(0x271B, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_TH, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_TH1, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9260_2ac_cfg, iww9162_name),

	_IWW_DEV_INFO(0x2526, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_TH, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_TH, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9260_2ac_cfg, iww9260_160_name),
	_IWW_DEV_INFO(0x2526, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_TH, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_TH, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9260_2ac_cfg, iww9260_name),

/* Qu with Jf */
	/* Qu B step */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_B_STEP,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_b0_jf_b0_cfg, iww9461_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_B_STEP,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_b0_jf_b0_cfg, iww9461_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_B_STEP,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1_DIV, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_b0_jf_b0_cfg, iww9462_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_B_STEP,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1_DIV, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_b0_jf_b0_cfg, iww9462_name),

	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_B_STEP,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_b0_jf_b0_cfg, iww9560_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_B_STEP,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_b0_jf_b0_cfg, iww9560_name),

	_IWW_DEV_INFO(IWW_CFG_ANY, 0x1551,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_B_STEP,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_b0_jf_b0_cfg, iww9560_kiwwew_1550s_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, 0x1552,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_B_STEP,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_b0_jf_b0_cfg, iww9560_kiwwew_1550i_name),

	/* Qu C step */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_C_STEP,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_c0_jf_b0_cfg, iww9461_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_C_STEP,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_c0_jf_b0_cfg, iww9461_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_C_STEP,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1_DIV, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_c0_jf_b0_cfg, iww9462_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_C_STEP,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1_DIV, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_c0_jf_b0_cfg, iww9462_name),

	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_C_STEP,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_c0_jf_b0_cfg, iww9560_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_C_STEP,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_c0_jf_b0_cfg, iww9560_name),

	_IWW_DEV_INFO(IWW_CFG_ANY, 0x1551,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_C_STEP,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_c0_jf_b0_cfg, iww9560_kiwwew_1550s_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, 0x1552,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_C_STEP,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_qu_c0_jf_b0_cfg, iww9560_kiwwew_1550i_name),

	/* QuZ */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QUZ, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_quz_a0_jf_b0_cfg, iww9461_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QUZ, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_quz_a0_jf_b0_cfg, iww9461_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QUZ, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1_DIV, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_quz_a0_jf_b0_cfg, iww9462_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QUZ, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1_DIV, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_quz_a0_jf_b0_cfg, iww9462_name),

	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QUZ, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_quz_a0_jf_b0_cfg, iww9560_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QUZ, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_quz_a0_jf_b0_cfg, iww9560_name),

	_IWW_DEV_INFO(IWW_CFG_ANY, 0x1551,
		      IWW_CFG_MAC_TYPE_QUZ, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_quz_a0_jf_b0_cfg, iww9560_kiwwew_1550s_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, 0x1552,
		      IWW_CFG_MAC_TYPE_QUZ, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iww9560_quz_a0_jf_b0_cfg, iww9560_kiwwew_1550i_name),

/* Qu with Hw */
	/* Qu B step */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_B_STEP,
		      IWW_CFG_WF_TYPE_HW1, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_ANY, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_qu_b0_hw1_b0, iww_ax101_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_B_STEP,
		      IWW_CFG_WF_TYPE_HW2, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_qu_b0_hw_b0, iww_ax203_name),

	/* Qu C step */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_C_STEP,
		      IWW_CFG_WF_TYPE_HW1, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_ANY, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_qu_c0_hw1_b0, iww_ax101_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_C_STEP,
		      IWW_CFG_WF_TYPE_HW2, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_qu_c0_hw_b0, iww_ax203_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QU, SIWICON_C_STEP,
		      IWW_CFG_WF_TYPE_HW2, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_qu_c0_hw_b0, iww_ax201_name),

	/* QuZ */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QUZ, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_HW1, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_ANY, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_quz_a0_hw1_b0, iww_ax101_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QUZ, SIWICON_B_STEP,
		      IWW_CFG_WF_TYPE_HW2, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_cfg_quz_a0_hw_b0, iww_ax203_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_QUZ, SIWICON_B_STEP,
		      IWW_CFG_WF_TYPE_HW2, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_cfg_quz_a0_hw_b0, iww_ax201_name),

/* Ma */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_MA, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_HW2, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_ANY, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_cfg_ma, iww_ax201_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_MA, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_GF, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_ANY, IWW_CFG_ANY, IWW_CFG_ANY,
		      iww_cfg_ma, iww_ax211_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_MA, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_MW, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_ANY, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_cfg_ma, iww_ax221_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_MA, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_FM, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_ANY, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_cfg_ma, iww_ax231_name),

/* So with Hw */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SO, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_HW2, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_cfg_so_a0_hw_a0, iww_ax203_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SO, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_HW1, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_cfg_so_a0_hw_a0, iww_ax101_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SO, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_HW2, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_cfg_so_a0_hw_a0, iww_ax201_name),

/* So-F with Hw */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SOF, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_HW2, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_cfg_so_a0_hw_a0, iww_ax203_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SOF, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_HW1, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_cfg_so_a0_hw_a0, iww_ax101_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SOF, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_HW2, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_cfg_so_a0_hw_a0, iww_ax201_name),

/* So-F with Gf */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SOF, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_GF, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iwwax211_2ax_cfg_so_gf_a0, iww_ax211_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SOF, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_GF, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_ANY, IWW_CFG_CDB,
		      iwwax411_2ax_cfg_so_gf4_a0, iww_ax411_name),

/* Bz */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_BZ, IWW_CFG_ANY,
		      IWW_CFG_ANY, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_ANY, IWW_CFG_ANY, IWW_CFG_ANY,
		      iww_cfg_bz, iww_bz_name),

/* Ga (Gw) */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_GW, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_FM, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_ANY, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_cfg_gw, iww_bz_name),

/* SoF with JF2 */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SOF, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iwwax210_2ax_cfg_so_jf_b0, iww9560_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SOF, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iwwax210_2ax_cfg_so_jf_b0, iww9560_name),

/* SoF with JF */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SOF, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iwwax210_2ax_cfg_so_jf_b0, iww9461_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SOF, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1_DIV, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iwwax210_2ax_cfg_so_jf_b0, iww9462_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SOF, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iwwax210_2ax_cfg_so_jf_b0, iww9461_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SOF, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1_DIV, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iwwax210_2ax_cfg_so_jf_b0, iww9462_name),

/* So with GF */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SO, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_GF, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iwwax211_2ax_cfg_so_gf_a0, iww_ax211_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SO, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_GF, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_ANY, IWW_CFG_CDB,
		      iwwax411_2ax_cfg_so_gf4_a0, iww_ax411_name),

/* So with JF2 */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SO, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iwwax210_2ax_cfg_so_jf_b0, iww9560_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SO, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF2, IWW_CFG_WF_ID_JF, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iwwax210_2ax_cfg_so_jf_b0, iww9560_name),

/* So with JF */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SO, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iwwax210_2ax_cfg_so_jf_b0, iww9461_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SO, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1_DIV, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iwwax210_2ax_cfg_so_jf_b0, iww9462_160_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SO, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iwwax210_2ax_cfg_so_jf_b0, iww9461_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SO, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_JF1, IWW_CFG_WF_ID_JF1_DIV, IWW_CFG_ANY,
		      IWW_CFG_NO_160, IWW_CFG_COWES_BT, IWW_CFG_NO_CDB,
		      iwwax210_2ax_cfg_so_jf_b0, iww9462_name),

/* MsP */
/* Fow now we use the same FW as MW, but this wiww change in the futuwe. */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SO, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_MS, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_cfg_so_a0_ms_a0, iww_ax204_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SOF, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_MS, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_cfg_so_a0_ms_a0, iww_ax204_name),
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_MA, IWW_CFG_ANY,
		      IWW_CFG_WF_TYPE_MS, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_160, IWW_CFG_ANY, IWW_CFG_NO_CDB,
		      iww_cfg_ma, iww_ax204_name),

/* Sc */
	_IWW_DEV_INFO(IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_MAC_TYPE_SC, IWW_CFG_ANY,
		      IWW_CFG_ANY, IWW_CFG_ANY, IWW_CFG_ANY,
		      IWW_CFG_ANY, IWW_CFG_ANY, IWW_CFG_ANY,
		      iww_cfg_sc, iww_sc_name),
#endif /* CONFIG_IWWMVM */
};

/*
 * Wead wf id and cdb info fwom pwph wegistew and stowe it
 */
static void get_cwf_id(stwuct iww_twans *iww_twans)
{
	u32 sd_weg_vew_addw;
	u32 vaw = 0;

	if (iww_twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210)
		sd_weg_vew_addw = SD_WEG_VEW_GEN2;
	ewse
		sd_weg_vew_addw = SD_WEG_VEW;

	/* Enabwe access to pewiphewaw wegistews */
	vaw = iww_wead_umac_pwph_no_gwab(iww_twans, WFPM_CTWW_WEG);
	vaw |= WFPM_AUX_CTW_AUX_IF_MAC_OWNEW_MSK;
	iww_wwite_umac_pwph_no_gwab(iww_twans, WFPM_CTWW_WEG, vaw);

	/* Wead cwf info */
	iww_twans->hw_cwf_id = iww_wead_pwph_no_gwab(iww_twans, sd_weg_vew_addw);

	/* Wead cnv info */
	iww_twans->hw_cnv_id =
		iww_wead_pwph_no_gwab(iww_twans, CNVI_AUX_MISC_CHIP);

	/* Wead cdb info (awso contains the jacket info if needed in the futuwe */
	iww_twans->hw_wfpm_id =
		iww_wead_umac_pwph_no_gwab(iww_twans, WFPM_OTP_CFG1_ADDW);
	IWW_INFO(iww_twans, "Detected cwf-id 0x%x, cnv-id 0x%x wfpm id 0x%x\n",
		 iww_twans->hw_cwf_id, iww_twans->hw_cnv_id,
		 iww_twans->hw_wfpm_id);
}

/*
 * In case that thewe is no OTP on the NIC, map the wf id and cdb info
 * fwom the pwph wegistews.
 */
static int map_cwf_id(stwuct iww_twans *iww_twans)
{
	int wet = 0;
	u32 vaw = iww_twans->hw_cwf_id;
	u32 step_id = WEG_CWF_ID_STEP(vaw);
	u32 swave_id = WEG_CWF_ID_SWAVE(vaw);
	u32 jacket_id_cnv  = WEG_CWF_ID_SWAVE(iww_twans->hw_cnv_id);
	u32 jacket_id_wfpm  = WFPM_OTP_CFG1_IS_JACKET(iww_twans->hw_wfpm_id);
	u32 cdb_id_wfpm  = WFPM_OTP_CFG1_IS_CDB(iww_twans->hw_wfpm_id);

	/* Map between cwf id to wf id */
	switch (WEG_CWF_ID_TYPE(vaw)) {
	case WEG_CWF_ID_TYPE_JF_1:
		iww_twans->hw_wf_id = (IWW_CFG_WF_TYPE_JF1 << 12);
		bweak;
	case WEG_CWF_ID_TYPE_JF_2:
		iww_twans->hw_wf_id = (IWW_CFG_WF_TYPE_JF2 << 12);
		bweak;
	case WEG_CWF_ID_TYPE_HW_NONE_CDB_1X1:
		iww_twans->hw_wf_id = (IWW_CFG_WF_TYPE_HW1 << 12);
		bweak;
	case WEG_CWF_ID_TYPE_HW_NONE_CDB:
		iww_twans->hw_wf_id = (IWW_CFG_WF_TYPE_HW2 << 12);
		bweak;
	case WEG_CWF_ID_TYPE_HW_CDB:
		iww_twans->hw_wf_id = (IWW_CFG_WF_TYPE_HW2 << 12);
		bweak;
	case WEG_CWF_ID_TYPE_GF:
		iww_twans->hw_wf_id = (IWW_CFG_WF_TYPE_GF << 12);
		bweak;
	case WEG_CWF_ID_TYPE_MW:
		iww_twans->hw_wf_id = (IWW_CFG_WF_TYPE_MW << 12);
		bweak;
	case WEG_CWF_ID_TYPE_FM:
	case WEG_CWF_ID_TYPE_FMI:
	case WEG_CWF_ID_TYPE_FMW:
		iww_twans->hw_wf_id = (IWW_CFG_WF_TYPE_FM << 12);
		bweak;
	case WEG_CWF_ID_TYPE_WHP:
		iww_twans->hw_wf_id = (IWW_CFG_WF_TYPE_WH << 12);
		bweak;
	defauwt:
		wet = -EIO;
		IWW_EWW(iww_twans,
			"Can't find a cowwect wfid fow cwf id 0x%x\n",
			WEG_CWF_ID_TYPE(vaw));
		goto out;

	}

	/* Set Step-id */
	iww_twans->hw_wf_id |= (step_id << 8);

	/* Set CDB capabiwities */
	if (cdb_id_wfpm || swave_id) {
		iww_twans->hw_wf_id += BIT(28);
		IWW_INFO(iww_twans, "Adding cdb to wf id\n");
	}

	/* Set Jacket capabiwities */
	if (jacket_id_wfpm || jacket_id_cnv) {
		iww_twans->hw_wf_id += BIT(29);
		IWW_INFO(iww_twans, "Adding jacket to wf id\n");
	}

	IWW_INFO(iww_twans,
		 "Detected wf-type 0x%x step-id 0x%x swave-id 0x%x fwom cwf id 0x%x\n",
		 WEG_CWF_ID_TYPE(vaw), step_id, swave_id, iww_twans->hw_wf_id);
	IWW_INFO(iww_twans,
		 "Detected cdb-id 0x%x jacket-id 0x%x fwom wfpm id 0x%x\n",
		 cdb_id_wfpm, jacket_id_wfpm, iww_twans->hw_wfpm_id);
	IWW_INFO(iww_twans, "Detected jacket-id 0x%x fwom cnvi id 0x%x\n",
		 jacket_id_cnv, iww_twans->hw_cnv_id);

out:
	wetuwn wet;
}

/* PCI wegistews */
#define PCI_CFG_WETWY_TIMEOUT	0x041

static const stwuct iww_dev_info *
iww_pci_find_dev_info(u16 device, u16 subsystem_device,
		      u16 mac_type, u8 mac_step, u16 wf_type, u8 cdb,
		      u8 jacket, u8 wf_id, u8 no_160, u8 cowes, u8 wf_step)
{
	int num_devices = AWWAY_SIZE(iww_dev_info_tabwe);
	int i;

	if (!num_devices)
		wetuwn NUWW;

	fow (i = num_devices - 1; i >= 0; i--) {
		const stwuct iww_dev_info *dev_info = &iww_dev_info_tabwe[i];

		if (dev_info->device != (u16)IWW_CFG_ANY &&
		    dev_info->device != device)
			continue;

		if (dev_info->subdevice != (u16)IWW_CFG_ANY &&
		    dev_info->subdevice != subsystem_device)
			continue;

		if (dev_info->mac_type != (u16)IWW_CFG_ANY &&
		    dev_info->mac_type != mac_type)
			continue;

		if (dev_info->mac_step != (u8)IWW_CFG_ANY &&
		    dev_info->mac_step != mac_step)
			continue;

		if (dev_info->wf_type != (u16)IWW_CFG_ANY &&
		    dev_info->wf_type != wf_type)
			continue;

		if (dev_info->cdb != (u8)IWW_CFG_ANY &&
		    dev_info->cdb != cdb)
			continue;

		if (dev_info->jacket != (u8)IWW_CFG_ANY &&
		    dev_info->jacket != jacket)
			continue;

		if (dev_info->wf_id != (u8)IWW_CFG_ANY &&
		    dev_info->wf_id != wf_id)
			continue;

		if (dev_info->no_160 != (u8)IWW_CFG_ANY &&
		    dev_info->no_160 != no_160)
			continue;

		if (dev_info->cowes != (u8)IWW_CFG_ANY &&
		    dev_info->cowes != cowes)
			continue;

		if (dev_info->wf_step != (u8)IWW_CFG_ANY &&
		    dev_info->wf_step != wf_step)
			continue;

		wetuwn dev_info;
	}

	wetuwn NUWW;
}

static int iww_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	const stwuct iww_cfg_twans_pawams *twans;
	const stwuct iww_cfg *cfg_7265d __maybe_unused = NUWW;
	const stwuct iww_dev_info *dev_info;
	stwuct iww_twans *iww_twans;
	stwuct iww_twans_pcie *twans_pcie;
	int wet;
	const stwuct iww_cfg *cfg;

	twans = (void *)(ent->dwivew_data & ~TWANS_CFG_MAWKEW);

	/*
	 * This is needed fow backwawds compatibiwity with the owd
	 * tabwes, so we don't need to change aww the config stwucts
	 * at the same time.  The cfg is used to compawe with the owd
	 * fuww cfg stwucts.
	 */
	cfg = (void *)(ent->dwivew_data & ~TWANS_CFG_MAWKEW);

	/* make suwe twans is the fiwst ewement in iww_cfg */
	BUIWD_BUG_ON(offsetof(stwuct iww_cfg, twans));

	iww_twans = iww_twans_pcie_awwoc(pdev, ent, twans);
	if (IS_EWW(iww_twans))
		wetuwn PTW_EWW(iww_twans);

	twans_pcie = IWW_TWANS_GET_PCIE_TWANS(iww_twans);

	/*
	 * Wet's twy to gwab NIC access eawwy hewe. Sometimes, NICs may
	 * faiw to initiawize, and if that happens it's bettew if we see
	 * issues eawwy on (and can wepwobe, pew the wogic inside), than
	 * fiwst twying to woad the fiwmwawe etc. and potentiawwy onwy
	 * detecting any pwobwems when the fiwst intewface is bwought up.
	 */
	wet = iww_pcie_pwepawe_cawd_hw(iww_twans);
	if (!wet) {
		wet = iww_finish_nic_init(iww_twans);
		if (wet)
			goto out_fwee_twans;
		if (iww_twans_gwab_nic_access(iww_twans)) {
			get_cwf_id(iww_twans);
			/* aww good */
			iww_twans_wewease_nic_access(iww_twans);
		} ewse {
			wet = -EIO;
			goto out_fwee_twans;
		}
	}

	iww_twans->hw_wf_id = iww_wead32(iww_twans, CSW_HW_WF_ID);

	/*
	 * The WF_ID is set to zewo in bwank OTP so wead vewsion to
	 * extwact the WF_ID.
	 * This is wewevant onwy fow famiwy 9000 and up.
	 */
	if (iww_twans->twans_cfg->wf_id &&
	    iww_twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_9000 &&
	    !CSW_HW_WFID_TYPE(iww_twans->hw_wf_id) && map_cwf_id(iww_twans)) {
		wet = -EINVAW;
		goto out_fwee_twans;
	}

	IWW_INFO(iww_twans, "PCI dev %04x/%04x, wev=0x%x, wfid=0x%x\n",
		 pdev->device, pdev->subsystem_device,
		 iww_twans->hw_wev, iww_twans->hw_wf_id);

	dev_info = iww_pci_find_dev_info(pdev->device, pdev->subsystem_device,
					 CSW_HW_WEV_TYPE(iww_twans->hw_wev),
					 iww_twans->hw_wev_step,
					 CSW_HW_WFID_TYPE(iww_twans->hw_wf_id),
					 CSW_HW_WFID_IS_CDB(iww_twans->hw_wf_id),
					 CSW_HW_WFID_IS_JACKET(iww_twans->hw_wf_id),
					 IWW_SUBDEVICE_WF_ID(pdev->subsystem_device),
					 IWW_SUBDEVICE_NO_160(pdev->subsystem_device),
					 IWW_SUBDEVICE_COWES(pdev->subsystem_device),
					 CSW_HW_WFID_STEP(iww_twans->hw_wf_id));
	if (dev_info) {
		iww_twans->cfg = dev_info->cfg;
		iww_twans->name = dev_info->name;
	}

#if IS_ENABWED(CONFIG_IWWMVM)
	/*
	 * speciaw-case 7265D, it has the same PCI IDs.
	 *
	 * Note that because we awweady pass the cfg to the twanspowt above,
	 * aww the pawametews that the twanspowt uses must, untiw that is
	 * changed, be identicaw to the ones in the 7265D configuwation.
	 */
	if (cfg == &iww7265_2ac_cfg)
		cfg_7265d = &iww7265d_2ac_cfg;
	ewse if (cfg == &iww7265_2n_cfg)
		cfg_7265d = &iww7265d_2n_cfg;
	ewse if (cfg == &iww7265_n_cfg)
		cfg_7265d = &iww7265d_n_cfg;
	if (cfg_7265d &&
	    (iww_twans->hw_wev & CSW_HW_WEV_TYPE_MSK) == CSW_HW_WEV_TYPE_7265D)
		iww_twans->cfg = cfg_7265d;

	/*
	 * This is a hack to switch fwom Qu B0 to Qu C0.  We need to
	 * do this fow aww cfgs that use Qu B0, except fow those using
	 * Jf, which have awweady been moved to the new tabwe.  The
	 * west must be wemoved once we convewt Qu with Hw as weww.
	 */
	if (iww_twans->hw_wev == CSW_HW_WEV_TYPE_QU_C0) {
		if (iww_twans->cfg == &iww_ax201_cfg_qu_hw)
			iww_twans->cfg = &iww_ax201_cfg_qu_c0_hw_b0;
		ewse if (iww_twans->cfg == &kiwwew1650s_2ax_cfg_qu_b0_hw_b0)
			iww_twans->cfg = &kiwwew1650s_2ax_cfg_qu_c0_hw_b0;
		ewse if (iww_twans->cfg == &kiwwew1650i_2ax_cfg_qu_b0_hw_b0)
			iww_twans->cfg = &kiwwew1650i_2ax_cfg_qu_c0_hw_b0;
	}

	/* same thing fow QuZ... */
	if (iww_twans->hw_wev == CSW_HW_WEV_TYPE_QUZ) {
		if (iww_twans->cfg == &iww_ax201_cfg_qu_hw)
			iww_twans->cfg = &iww_ax201_cfg_quz_hw;
		ewse if (iww_twans->cfg == &kiwwew1650s_2ax_cfg_qu_b0_hw_b0)
			iww_twans->cfg = &iww_ax1650s_cfg_quz_hw;
		ewse if (iww_twans->cfg == &kiwwew1650i_2ax_cfg_qu_b0_hw_b0)
			iww_twans->cfg = &iww_ax1650i_cfg_quz_hw;
	}

#endif
	/*
	 * If we didn't set the cfg yet, the PCI ID tabwe entwy shouwd have
	 * been a fuww config - if yes, use it, othewwise faiw.
	 */
	if (!iww_twans->cfg) {
		if (ent->dwivew_data & TWANS_CFG_MAWKEW) {
			pw_eww("No config found fow PCI dev %04x/%04x, wev=0x%x, wfid=0x%x\n",
			       pdev->device, pdev->subsystem_device,
			       iww_twans->hw_wev, iww_twans->hw_wf_id);
			wet = -EINVAW;
			goto out_fwee_twans;
		}
		iww_twans->cfg = cfg;
	}

	/* if we don't have a name yet, copy name fwom the owd cfg */
	if (!iww_twans->name)
		iww_twans->name = iww_twans->cfg->name;

	if (iww_twans->twans_cfg->mq_wx_suppowted) {
		if (WAWN_ON(!iww_twans->cfg->num_wbds)) {
			wet = -EINVAW;
			goto out_fwee_twans;
		}
		twans_pcie->num_wx_bufs = iww_twans->cfg->num_wbds;
	} ewse {
		twans_pcie->num_wx_bufs = WX_QUEUE_SIZE;
	}

	if (!iww_twans->twans_cfg->integwated) {
		u16 wink_status;

		pcie_capabiwity_wead_wowd(pdev, PCI_EXP_WNKSTA, &wink_status);

		iww_twans->pcie_wink_speed =
			u16_get_bits(wink_status, PCI_EXP_WNKSTA_CWS);
	}

	wet = iww_twans_init(iww_twans);
	if (wet)
		goto out_fwee_twans;

	pci_set_dwvdata(pdev, iww_twans);

	/* twy to get ownewship so that we'ww know if we don't own it */
	iww_pcie_pwepawe_cawd_hw(iww_twans);

	iww_twans->dwv = iww_dwv_stawt(iww_twans);

	if (IS_EWW(iww_twans->dwv)) {
		wet = PTW_EWW(iww_twans->dwv);
		goto out_fwee_twans;
	}

	/* wegistew twanspowt wayew debugfs hewe */
	iww_twans_pcie_dbgfs_wegistew(iww_twans);

	wetuwn 0;

out_fwee_twans:
	iww_twans_pcie_fwee(iww_twans);
	wetuwn wet;
}

static void iww_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct iww_twans *twans = pci_get_dwvdata(pdev);

	if (!twans)
		wetuwn;

	iww_dwv_stop(twans->dwv);

	iww_twans_pcie_fwee(twans);
}

#ifdef CONFIG_PM_SWEEP

static int iww_pci_suspend(stwuct device *device)
{
	/* Befowe you put code hewe, think about WoWWAN. You cannot check hewe
	 * whethew WoWWAN is enabwed ow not, and youw code wiww wun even if
	 * WoWWAN is enabwed - don't kiww the NIC, someone may need it in Sx.
	 */

	wetuwn 0;
}

static int iww_pci_wesume(stwuct device *device)
{
	stwuct pci_dev *pdev = to_pci_dev(device);
	stwuct iww_twans *twans = pci_get_dwvdata(pdev);
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);

	/* Befowe you put code hewe, think about WoWWAN. You cannot check hewe
	 * whethew WoWWAN is enabwed ow not, and youw code wiww wun even if
	 * WoWWAN is enabwed - the NIC may be awive.
	 */

	/*
	 * We disabwe the WETWY_TIMEOUT wegistew (0x41) to keep
	 * PCI Tx wetwies fwom intewfewing with C3 CPU state.
	 */
	pci_wwite_config_byte(pdev, PCI_CFG_WETWY_TIMEOUT, 0x00);

	if (!twans->op_mode)
		wetuwn 0;

	/* In WOWWAN, wet iww_twans_pcie_d3_wesume do the west of the wowk */
	if (test_bit(STATUS_DEVICE_ENABWED, &twans->status))
		wetuwn 0;

	/* weconfiguwe the MSI-X mapping to get the cowwect IWQ fow wfkiww */
	iww_pcie_conf_msix_hw(twans_pcie);

	/*
	 * Enabwe wfkiww intewwupt (in owdew to keep twack of the wfkiww
	 * status). Must be wocked to avoid pwocessing a possibwe wfkiww
	 * intewwupt whiwe in iww_pcie_check_hw_wf_kiww().
	 */
	mutex_wock(&twans_pcie->mutex);
	iww_enabwe_wfkiww_int(twans);
	iww_pcie_check_hw_wf_kiww(twans);
	mutex_unwock(&twans_pcie->mutex);

	wetuwn 0;
}

static const stwuct dev_pm_ops iww_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(iww_pci_suspend,
				iww_pci_wesume)
};

#define IWW_PM_OPS	(&iww_dev_pm_ops)

#ewse /* CONFIG_PM_SWEEP */

#define IWW_PM_OPS	NUWW

#endif /* CONFIG_PM_SWEEP */

static stwuct pci_dwivew iww_pci_dwivew = {
	.name = DWV_NAME,
	.id_tabwe = iww_hw_cawd_ids,
	.pwobe = iww_pci_pwobe,
	.wemove = iww_pci_wemove,
	.dwivew.pm = IWW_PM_OPS,
};

int __must_check iww_pci_wegistew_dwivew(void)
{
	int wet;
	wet = pci_wegistew_dwivew(&iww_pci_dwivew);
	if (wet)
		pw_eww("Unabwe to initiawize PCI moduwe\n");

	wetuwn wet;
}

void iww_pci_unwegistew_dwivew(void)
{
	pci_unwegistew_dwivew(&iww_pci_dwivew);
}
