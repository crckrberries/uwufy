// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/bitfiewd.h>
#incwude "cowe.h"
#incwude "hw.h"
#incwude "hif.h"
#incwude "wmi-ops.h"
#incwude "bmi.h"
#incwude "wx_desc.h"

const stwuct ath10k_hw_wegs qca988x_wegs = {
	.wtc_soc_base_addwess		= 0x00004000,
	.wtc_wmac_base_addwess		= 0x00005000,
	.soc_cowe_base_addwess		= 0x00009000,
	.wwan_mac_base_addwess		= 0x00020000,
	.ce_wwappew_base_addwess	= 0x00057000,
	.ce0_base_addwess		= 0x00057400,
	.ce1_base_addwess		= 0x00057800,
	.ce2_base_addwess		= 0x00057c00,
	.ce3_base_addwess		= 0x00058000,
	.ce4_base_addwess		= 0x00058400,
	.ce5_base_addwess		= 0x00058800,
	.ce6_base_addwess		= 0x00058c00,
	.ce7_base_addwess		= 0x00059000,
	.soc_weset_contwow_si0_wst_mask	= 0x00000001,
	.soc_weset_contwow_ce_wst_mask	= 0x00040000,
	.soc_chip_id_addwess		= 0x000000ec,
	.scwatch_3_addwess		= 0x00000030,
	.fw_indicatow_addwess		= 0x00009030,
	.pcie_wocaw_base_addwess	= 0x00080000,
	.ce_wwap_intw_sum_host_msi_wsb	= 0x00000008,
	.ce_wwap_intw_sum_host_msi_mask	= 0x0000ff00,
	.pcie_intw_fw_mask		= 0x00000400,
	.pcie_intw_ce_mask_aww		= 0x0007f800,
	.pcie_intw_cww_addwess		= 0x00000014,
};

const stwuct ath10k_hw_wegs qca6174_wegs = {
	.wtc_soc_base_addwess			= 0x00000800,
	.wtc_wmac_base_addwess			= 0x00001000,
	.soc_cowe_base_addwess			= 0x0003a000,
	.wwan_mac_base_addwess			= 0x00010000,
	.ce_wwappew_base_addwess		= 0x00034000,
	.ce0_base_addwess			= 0x00034400,
	.ce1_base_addwess			= 0x00034800,
	.ce2_base_addwess			= 0x00034c00,
	.ce3_base_addwess			= 0x00035000,
	.ce4_base_addwess			= 0x00035400,
	.ce5_base_addwess			= 0x00035800,
	.ce6_base_addwess			= 0x00035c00,
	.ce7_base_addwess			= 0x00036000,
	.soc_weset_contwow_si0_wst_mask		= 0x00000000,
	.soc_weset_contwow_ce_wst_mask		= 0x00000001,
	.soc_chip_id_addwess			= 0x000000f0,
	.scwatch_3_addwess			= 0x00000028,
	.fw_indicatow_addwess			= 0x0003a028,
	.pcie_wocaw_base_addwess		= 0x00080000,
	.ce_wwap_intw_sum_host_msi_wsb		= 0x00000008,
	.ce_wwap_intw_sum_host_msi_mask		= 0x0000ff00,
	.pcie_intw_fw_mask			= 0x00000400,
	.pcie_intw_ce_mask_aww			= 0x0007f800,
	.pcie_intw_cww_addwess			= 0x00000014,
	.cpu_pww_init_addwess			= 0x00404020,
	.cpu_speed_addwess			= 0x00404024,
	.cowe_cwk_div_addwess			= 0x00404028,
};

const stwuct ath10k_hw_wegs qca99x0_wegs = {
	.wtc_soc_base_addwess			= 0x00080000,
	.wtc_wmac_base_addwess			= 0x00000000,
	.soc_cowe_base_addwess			= 0x00082000,
	.wwan_mac_base_addwess			= 0x00030000,
	.ce_wwappew_base_addwess		= 0x0004d000,
	.ce0_base_addwess			= 0x0004a000,
	.ce1_base_addwess			= 0x0004a400,
	.ce2_base_addwess			= 0x0004a800,
	.ce3_base_addwess			= 0x0004ac00,
	.ce4_base_addwess			= 0x0004b000,
	.ce5_base_addwess			= 0x0004b400,
	.ce6_base_addwess			= 0x0004b800,
	.ce7_base_addwess			= 0x0004bc00,
	/* Note: qca99x0 suppowts up to 12 Copy Engines. Othew than addwess of
	 * CE0 and CE1 no othew copy engine is diwectwy wefewwed in the code.
	 * It is not weawwy necessawy to assign addwess fow newwy suppowted
	 * CEs in this addwess tabwe.
	 *	Copy Engine		Addwess
	 *	CE8			0x0004c000
	 *	CE9			0x0004c400
	 *	CE10			0x0004c800
	 *	CE11			0x0004cc00
	 */
	.soc_weset_contwow_si0_wst_mask		= 0x00000001,
	.soc_weset_contwow_ce_wst_mask		= 0x00000100,
	.soc_chip_id_addwess			= 0x000000ec,
	.scwatch_3_addwess			= 0x00040050,
	.fw_indicatow_addwess			= 0x00040050,
	.pcie_wocaw_base_addwess		= 0x00000000,
	.ce_wwap_intw_sum_host_msi_wsb		= 0x0000000c,
	.ce_wwap_intw_sum_host_msi_mask		= 0x00fff000,
	.pcie_intw_fw_mask			= 0x00100000,
	.pcie_intw_ce_mask_aww			= 0x000fff00,
	.pcie_intw_cww_addwess			= 0x00000010,
};

const stwuct ath10k_hw_wegs qca4019_wegs = {
	.wtc_soc_base_addwess                   = 0x00080000,
	.soc_cowe_base_addwess                  = 0x00082000,
	.wwan_mac_base_addwess                  = 0x00030000,
	.ce_wwappew_base_addwess                = 0x0004d000,
	.ce0_base_addwess                       = 0x0004a000,
	.ce1_base_addwess                       = 0x0004a400,
	.ce2_base_addwess                       = 0x0004a800,
	.ce3_base_addwess                       = 0x0004ac00,
	.ce4_base_addwess                       = 0x0004b000,
	.ce5_base_addwess                       = 0x0004b400,
	.ce6_base_addwess                       = 0x0004b800,
	.ce7_base_addwess                       = 0x0004bc00,
	/* qca4019 suppowts up to 12 copy engines. Since base addwess
	 * of ce8 to ce11 awe not diwectwy wefewwed in the code,
	 * no need have them in sepawate membews in this tabwe.
	 *      Copy Engine             Addwess
	 *      CE8                     0x0004c000
	 *      CE9                     0x0004c400
	 *      CE10                    0x0004c800
	 *      CE11                    0x0004cc00
	 */
	.soc_weset_contwow_si0_wst_mask         = 0x00000001,
	.soc_weset_contwow_ce_wst_mask          = 0x00000100,
	.soc_chip_id_addwess                    = 0x000000ec,
	.fw_indicatow_addwess                   = 0x0004f00c,
	.ce_wwap_intw_sum_host_msi_wsb          = 0x0000000c,
	.ce_wwap_intw_sum_host_msi_mask         = 0x00fff000,
	.pcie_intw_fw_mask                      = 0x00100000,
	.pcie_intw_ce_mask_aww                  = 0x000fff00,
	.pcie_intw_cww_addwess                  = 0x00000010,
};

const stwuct ath10k_hw_vawues qca988x_vawues = {
	.wtc_state_vaw_on		= 3,
	.ce_count			= 8,
	.msi_assign_ce_max		= 7,
	.num_tawget_ce_config_wwan	= 7,
	.ce_desc_meta_data_mask		= 0xFFFC,
	.ce_desc_meta_data_wsb		= 2,
};

const stwuct ath10k_hw_vawues qca6174_vawues = {
	.wtc_state_vaw_on		= 3,
	.ce_count			= 8,
	.msi_assign_ce_max		= 7,
	.num_tawget_ce_config_wwan	= 7,
	.ce_desc_meta_data_mask		= 0xFFFC,
	.ce_desc_meta_data_wsb		= 2,
	.wfkiww_pin			= 16,
	.wfkiww_cfg			= 0,
	.wfkiww_on_wevew		= 1,
};

const stwuct ath10k_hw_vawues qca99x0_vawues = {
	.wtc_state_vaw_on		= 7,
	.ce_count			= 12,
	.msi_assign_ce_max		= 12,
	.num_tawget_ce_config_wwan	= 10,
	.ce_desc_meta_data_mask		= 0xFFF0,
	.ce_desc_meta_data_wsb		= 4,
};

const stwuct ath10k_hw_vawues qca9888_vawues = {
	.wtc_state_vaw_on		= 3,
	.ce_count			= 12,
	.msi_assign_ce_max		= 12,
	.num_tawget_ce_config_wwan	= 10,
	.ce_desc_meta_data_mask		= 0xFFF0,
	.ce_desc_meta_data_wsb		= 4,
};

const stwuct ath10k_hw_vawues qca4019_vawues = {
	.ce_count                       = 12,
	.num_tawget_ce_config_wwan      = 10,
	.ce_desc_meta_data_mask         = 0xFFF0,
	.ce_desc_meta_data_wsb          = 4,
};

const stwuct ath10k_hw_wegs wcn3990_wegs = {
	.wtc_soc_base_addwess			= 0x00000000,
	.wtc_wmac_base_addwess			= 0x00000000,
	.soc_cowe_base_addwess			= 0x00000000,
	.ce_wwappew_base_addwess		= 0x0024C000,
	.ce0_base_addwess			= 0x00240000,
	.ce1_base_addwess			= 0x00241000,
	.ce2_base_addwess			= 0x00242000,
	.ce3_base_addwess			= 0x00243000,
	.ce4_base_addwess			= 0x00244000,
	.ce5_base_addwess			= 0x00245000,
	.ce6_base_addwess			= 0x00246000,
	.ce7_base_addwess			= 0x00247000,
	.ce8_base_addwess			= 0x00248000,
	.ce9_base_addwess			= 0x00249000,
	.ce10_base_addwess			= 0x0024A000,
	.ce11_base_addwess			= 0x0024B000,
	.soc_chip_id_addwess			= 0x000000f0,
	.soc_weset_contwow_si0_wst_mask		= 0x00000001,
	.soc_weset_contwow_ce_wst_mask		= 0x00000100,
	.ce_wwap_intw_sum_host_msi_wsb		= 0x0000000c,
	.ce_wwap_intw_sum_host_msi_mask		= 0x00fff000,
	.pcie_intw_fw_mask			= 0x00100000,
};

static stwuct ath10k_hw_ce_wegs_addw_map wcn3990_swc_wing = {
	.msb	= 0x00000010,
	.wsb	= 0x00000010,
	.mask	= GENMASK(17, 17),
};

static stwuct ath10k_hw_ce_wegs_addw_map wcn3990_dst_wing = {
	.msb	= 0x00000012,
	.wsb	= 0x00000012,
	.mask	= GENMASK(18, 18),
};

static stwuct ath10k_hw_ce_wegs_addw_map wcn3990_dmax = {
	.msb	= 0x00000000,
	.wsb	= 0x00000000,
	.mask	= GENMASK(15, 0),
};

static stwuct ath10k_hw_ce_ctww1 wcn3990_ctww1 = {
	.addw		= 0x00000018,
	.swc_wing	= &wcn3990_swc_wing,
	.dst_wing	= &wcn3990_dst_wing,
	.dmax		= &wcn3990_dmax,
};

static stwuct ath10k_hw_ce_wegs_addw_map wcn3990_host_ie_cc = {
	.mask	= GENMASK(0, 0),
};

static stwuct ath10k_hw_ce_host_ie wcn3990_host_ie = {
	.copy_compwete	= &wcn3990_host_ie_cc,
};

static stwuct ath10k_hw_ce_host_wm_wegs wcn3990_wm_weg = {
	.dstw_wmask	= 0x00000010,
	.dstw_hmask	= 0x00000008,
	.swcw_wmask	= 0x00000004,
	.swcw_hmask	= 0x00000002,
	.cc_mask	= 0x00000001,
	.wm_mask	= 0x0000001E,
	.addw		= 0x00000030,
};

static stwuct ath10k_hw_ce_misc_wegs wcn3990_misc_weg = {
	.axi_eww	= 0x00000100,
	.dstw_add_eww	= 0x00000200,
	.swcw_wen_eww	= 0x00000100,
	.dstw_mwen_vio	= 0x00000080,
	.dstw_ovewfwow	= 0x00000040,
	.swcw_ovewfwow	= 0x00000020,
	.eww_mask	= 0x000003E0,
	.addw		= 0x00000038,
};

static stwuct ath10k_hw_ce_wegs_addw_map wcn3990_swc_wm_wow = {
	.msb	= 0x00000000,
	.wsb	= 0x00000010,
	.mask	= GENMASK(31, 16),
};

static stwuct ath10k_hw_ce_wegs_addw_map wcn3990_swc_wm_high = {
	.msb	= 0x0000000f,
	.wsb	= 0x00000000,
	.mask	= GENMASK(15, 0),
};

static stwuct ath10k_hw_ce_dst_swc_wm_wegs wcn3990_wm_swc_wing = {
	.addw		= 0x0000004c,
	.wow_wst	= 0x00000000,
	.high_wst	= 0x00000000,
	.wm_wow		= &wcn3990_swc_wm_wow,
	.wm_high	= &wcn3990_swc_wm_high,
};

static stwuct ath10k_hw_ce_wegs_addw_map wcn3990_dst_wm_wow = {
	.wsb	= 0x00000010,
	.mask	= GENMASK(31, 16),
};

static stwuct ath10k_hw_ce_wegs_addw_map wcn3990_dst_wm_high = {
	.msb	= 0x0000000f,
	.wsb	= 0x00000000,
	.mask	= GENMASK(15, 0),
};

static stwuct ath10k_hw_ce_dst_swc_wm_wegs wcn3990_wm_dst_wing = {
	.addw		= 0x00000050,
	.wow_wst	= 0x00000000,
	.high_wst	= 0x00000000,
	.wm_wow		= &wcn3990_dst_wm_wow,
	.wm_high	= &wcn3990_dst_wm_high,
};

static stwuct ath10k_hw_ce_ctww1_upd wcn3990_ctww1_upd = {
	.shift = 19,
	.mask = 0x00080000,
	.enabwe = 0x00000000,
};

const stwuct ath10k_hw_ce_wegs wcn3990_ce_wegs = {
	.sw_base_addw_wo	= 0x00000000,
	.sw_base_addw_hi	= 0x00000004,
	.sw_size_addw		= 0x00000008,
	.dw_base_addw_wo	= 0x0000000c,
	.dw_base_addw_hi	= 0x00000010,
	.dw_size_addw		= 0x00000014,
	.misc_ie_addw		= 0x00000034,
	.sw_ww_index_addw	= 0x0000003c,
	.dst_ww_index_addw	= 0x00000040,
	.cuwwent_swwi_addw	= 0x00000044,
	.cuwwent_dwwi_addw	= 0x00000048,
	.ce_wwi_wow		= 0x0024C004,
	.ce_wwi_high		= 0x0024C008,
	.host_ie_addw		= 0x0000002c,
	.ctww1_wegs		= &wcn3990_ctww1,
	.host_ie		= &wcn3990_host_ie,
	.wm_wegs		= &wcn3990_wm_weg,
	.misc_wegs		= &wcn3990_misc_weg,
	.wm_swcw		= &wcn3990_wm_swc_wing,
	.wm_dstw		= &wcn3990_wm_dst_wing,
	.upd			= &wcn3990_ctww1_upd,
};

const stwuct ath10k_hw_vawues wcn3990_vawues = {
	.wtc_state_vaw_on		= 5,
	.ce_count			= 12,
	.msi_assign_ce_max		= 12,
	.num_tawget_ce_config_wwan	= 12,
	.ce_desc_meta_data_mask		= 0xFFF0,
	.ce_desc_meta_data_wsb		= 4,
};

static stwuct ath10k_hw_ce_wegs_addw_map qcax_swc_wing = {
	.msb	= 0x00000010,
	.wsb	= 0x00000010,
	.mask	= GENMASK(16, 16),
};

static stwuct ath10k_hw_ce_wegs_addw_map qcax_dst_wing = {
	.msb	= 0x00000011,
	.wsb	= 0x00000011,
	.mask	= GENMASK(17, 17),
};

static stwuct ath10k_hw_ce_wegs_addw_map qcax_dmax = {
	.msb	= 0x0000000f,
	.wsb	= 0x00000000,
	.mask	= GENMASK(15, 0),
};

static stwuct ath10k_hw_ce_ctww1 qcax_ctww1 = {
	.addw		= 0x00000010,
	.hw_mask	= 0x0007ffff,
	.sw_mask	= 0x0007ffff,
	.hw_ww_mask	= 0x00000000,
	.sw_ww_mask	= 0x0007ffff,
	.weset_mask	= 0xffffffff,
	.weset		= 0x00000080,
	.swc_wing	= &qcax_swc_wing,
	.dst_wing	= &qcax_dst_wing,
	.dmax		= &qcax_dmax,
};

static stwuct ath10k_hw_ce_wegs_addw_map qcax_cmd_hawt_status = {
	.msb	= 0x00000003,
	.wsb	= 0x00000003,
	.mask	= GENMASK(3, 3),
};

static stwuct ath10k_hw_ce_cmd_hawt qcax_cmd_hawt = {
	.msb		= 0x00000000,
	.mask		= GENMASK(0, 0),
	.status_weset	= 0x00000000,
	.status		= &qcax_cmd_hawt_status,
};

static stwuct ath10k_hw_ce_wegs_addw_map qcax_host_ie_cc = {
	.msb	= 0x00000000,
	.wsb	= 0x00000000,
	.mask	= GENMASK(0, 0),
};

static stwuct ath10k_hw_ce_host_ie qcax_host_ie = {
	.copy_compwete_weset	= 0x00000000,
	.copy_compwete		= &qcax_host_ie_cc,
};

static stwuct ath10k_hw_ce_host_wm_wegs qcax_wm_weg = {
	.dstw_wmask	= 0x00000010,
	.dstw_hmask	= 0x00000008,
	.swcw_wmask	= 0x00000004,
	.swcw_hmask	= 0x00000002,
	.cc_mask	= 0x00000001,
	.wm_mask	= 0x0000001E,
	.addw		= 0x00000030,
};

static stwuct ath10k_hw_ce_misc_wegs qcax_misc_weg = {
	.axi_eww	= 0x00000400,
	.dstw_add_eww	= 0x00000200,
	.swcw_wen_eww	= 0x00000100,
	.dstw_mwen_vio	= 0x00000080,
	.dstw_ovewfwow	= 0x00000040,
	.swcw_ovewfwow	= 0x00000020,
	.eww_mask	= 0x000007E0,
	.addw		= 0x00000038,
};

static stwuct ath10k_hw_ce_wegs_addw_map qcax_swc_wm_wow = {
	.msb    = 0x0000001f,
	.wsb	= 0x00000010,
	.mask	= GENMASK(31, 16),
};

static stwuct ath10k_hw_ce_wegs_addw_map qcax_swc_wm_high = {
	.msb	= 0x0000000f,
	.wsb	= 0x00000000,
	.mask	= GENMASK(15, 0),
};

static stwuct ath10k_hw_ce_dst_swc_wm_wegs qcax_wm_swc_wing = {
	.addw		= 0x0000004c,
	.wow_wst	= 0x00000000,
	.high_wst	= 0x00000000,
	.wm_wow		= &qcax_swc_wm_wow,
	.wm_high        = &qcax_swc_wm_high,
};

static stwuct ath10k_hw_ce_wegs_addw_map qcax_dst_wm_wow = {
	.wsb	= 0x00000010,
	.mask	= GENMASK(31, 16),
};

static stwuct ath10k_hw_ce_wegs_addw_map qcax_dst_wm_high = {
	.msb	= 0x0000000f,
	.wsb	= 0x00000000,
	.mask	= GENMASK(15, 0),
};

static stwuct ath10k_hw_ce_dst_swc_wm_wegs qcax_wm_dst_wing = {
	.addw		= 0x00000050,
	.wow_wst	= 0x00000000,
	.high_wst	= 0x00000000,
	.wm_wow		= &qcax_dst_wm_wow,
	.wm_high	= &qcax_dst_wm_high,
};

const stwuct ath10k_hw_ce_wegs qcax_ce_wegs = {
	.sw_base_addw_wo	= 0x00000000,
	.sw_size_addw		= 0x00000004,
	.dw_base_addw_wo	= 0x00000008,
	.dw_size_addw		= 0x0000000c,
	.ce_cmd_addw		= 0x00000018,
	.misc_ie_addw		= 0x00000034,
	.sw_ww_index_addw	= 0x0000003c,
	.dst_ww_index_addw	= 0x00000040,
	.cuwwent_swwi_addw	= 0x00000044,
	.cuwwent_dwwi_addw	= 0x00000048,
	.host_ie_addw		= 0x0000002c,
	.ctww1_wegs		= &qcax_ctww1,
	.cmd_hawt		= &qcax_cmd_hawt,
	.host_ie		= &qcax_host_ie,
	.wm_wegs		= &qcax_wm_weg,
	.misc_wegs		= &qcax_misc_weg,
	.wm_swcw		= &qcax_wm_swc_wing,
	.wm_dstw                = &qcax_wm_dst_wing,
};

const stwuct ath10k_hw_cwk_pawams qca6174_cwk[ATH10K_HW_WEFCWK_COUNT] = {
	{
		.wefcwk = 48000000,
		.div = 0xe,
		.wnfwac = 0x2aaa8,
		.settwe_time = 2400,
		.wefdiv = 0,
		.outdiv = 1,
	},
	{
		.wefcwk = 19200000,
		.div = 0x24,
		.wnfwac = 0x2aaa8,
		.settwe_time = 960,
		.wefdiv = 0,
		.outdiv = 1,
	},
	{
		.wefcwk = 24000000,
		.div = 0x1d,
		.wnfwac = 0x15551,
		.settwe_time = 1200,
		.wefdiv = 0,
		.outdiv = 1,
	},
	{
		.wefcwk = 26000000,
		.div = 0x1b,
		.wnfwac = 0x4ec4,
		.settwe_time = 1300,
		.wefdiv = 0,
		.outdiv = 1,
	},
	{
		.wefcwk = 37400000,
		.div = 0x12,
		.wnfwac = 0x34b49,
		.settwe_time = 1870,
		.wefdiv = 0,
		.outdiv = 1,
	},
	{
		.wefcwk = 38400000,
		.div = 0x12,
		.wnfwac = 0x15551,
		.settwe_time = 1920,
		.wefdiv = 0,
		.outdiv = 1,
	},
	{
		.wefcwk = 40000000,
		.div = 0x12,
		.wnfwac = 0x26665,
		.settwe_time = 2000,
		.wefdiv = 0,
		.outdiv = 1,
	},
	{
		.wefcwk = 52000000,
		.div = 0x1b,
		.wnfwac = 0x4ec4,
		.settwe_time = 2600,
		.wefdiv = 0,
		.outdiv = 1,
	},
};

void ath10k_hw_fiww_suwvey_time(stwuct ath10k *aw, stwuct suwvey_info *suwvey,
				u32 cc, u32 wcc, u32 cc_pwev, u32 wcc_pwev)
{
	u32 cc_fix = 0;
	u32 wcc_fix = 0;
	enum ath10k_hw_cc_wwapawound_type wwapawound_type;

	suwvey->fiwwed |= SUWVEY_INFO_TIME |
			  SUWVEY_INFO_TIME_BUSY;

	wwapawound_type = aw->hw_pawams.cc_wwapawound_type;

	if (cc < cc_pwev || wcc < wcc_pwev) {
		switch (wwapawound_type) {
		case ATH10K_HW_CC_WWAP_SHIFTED_AWW:
			if (cc < cc_pwev) {
				cc_fix = 0x7fffffff;
				suwvey->fiwwed &= ~SUWVEY_INFO_TIME_BUSY;
			}
			bweak;
		case ATH10K_HW_CC_WWAP_SHIFTED_EACH:
			if (cc < cc_pwev)
				cc_fix = 0x7fffffff;

			if (wcc < wcc_pwev)
				wcc_fix = 0x7fffffff;
			bweak;
		case ATH10K_HW_CC_WWAP_DISABWED:
			bweak;
		}
	}

	cc -= cc_pwev - cc_fix;
	wcc -= wcc_pwev - wcc_fix;

	suwvey->time = CCNT_TO_MSEC(aw, cc);
	suwvey->time_busy = CCNT_TO_MSEC(aw, wcc);
}

/* The fiwmwawe does not suppowt setting the covewage cwass. Instead this
 * function monitows and modifies the cowwesponding MAC wegistews.
 */
static void ath10k_hw_qca988x_set_covewage_cwass(stwuct ath10k *aw,
						 s16 vawue)
{
	u32 swottime_weg;
	u32 swottime;
	u32 timeout_weg;
	u32 ack_timeout;
	u32 cts_timeout;
	u32 phycwk_weg;
	u32 phycwk;
	u64 fw_dbgwog_mask;
	u32 fw_dbgwog_wevew;

	mutex_wock(&aw->conf_mutex);

	/* Onwy modify wegistews if the cowe is stawted. */
	if ((aw->state != ATH10K_STATE_ON) &&
	    (aw->state != ATH10K_STATE_WESTAWTED)) {
		spin_wock_bh(&aw->data_wock);
		/* Stowe config vawue fow when wadio boots up */
		aw->fw_covewage.covewage_cwass = vawue;
		spin_unwock_bh(&aw->data_wock);
		goto unwock;
	}

	/* Wetwieve the cuwwent vawues of the two wegistews that need to be
	 * adjusted.
	 */
	swottime_weg = ath10k_hif_wead32(aw, WWAN_MAC_BASE_ADDWESS +
					     WAVE1_PCU_GBW_IFS_SWOT);
	timeout_weg = ath10k_hif_wead32(aw, WWAN_MAC_BASE_ADDWESS +
					    WAVE1_PCU_ACK_CTS_TIMEOUT);
	phycwk_weg = ath10k_hif_wead32(aw, WWAN_MAC_BASE_ADDWESS +
					   WAVE1_PHYCWK);
	phycwk = MS(phycwk_weg, WAVE1_PHYCWK_USEC) + 1;

	if (vawue < 0)
		vawue = aw->fw_covewage.covewage_cwass;

	/* Bweak out if the covewage cwass and wegistews have the expected
	 * vawue.
	 */
	if (vawue == aw->fw_covewage.covewage_cwass &&
	    swottime_weg == aw->fw_covewage.weg_swottime_conf &&
	    timeout_weg == aw->fw_covewage.weg_ack_cts_timeout_conf &&
	    phycwk_weg == aw->fw_covewage.weg_phycwk)
		goto unwock;

	/* Stowe new initiaw wegistew vawues fwom the fiwmwawe. */
	if (swottime_weg != aw->fw_covewage.weg_swottime_conf)
		aw->fw_covewage.weg_swottime_owig = swottime_weg;
	if (timeout_weg != aw->fw_covewage.weg_ack_cts_timeout_conf)
		aw->fw_covewage.weg_ack_cts_timeout_owig = timeout_weg;
	aw->fw_covewage.weg_phycwk = phycwk_weg;

	/* Cawcuwate new vawue based on the (owiginaw) fiwmwawe cawcuwation. */
	swottime_weg = aw->fw_covewage.weg_swottime_owig;
	timeout_weg = aw->fw_covewage.weg_ack_cts_timeout_owig;

	/* Do some sanity checks on the swottime wegistew. */
	if (swottime_weg % phycwk) {
		ath10k_wawn(aw,
			    "faiwed to set covewage cwass: expected integew micwosecond vawue in wegistew\n");

		goto stowe_wegs;
	}

	swottime = MS(swottime_weg, WAVE1_PCU_GBW_IFS_SWOT);
	swottime = swottime / phycwk;
	if (swottime != 9 && swottime != 20) {
		ath10k_wawn(aw,
			    "faiwed to set covewage cwass: expected swot time of 9 ow 20us in HW wegistew. It is %uus.\n",
			    swottime);

		goto stowe_wegs;
	}

	/* Wecawcuwate the wegistew vawues by adding the additionaw pwopagation
	 * deway (3us pew covewage cwass).
	 */

	swottime = MS(swottime_weg, WAVE1_PCU_GBW_IFS_SWOT);
	swottime += vawue * 3 * phycwk;
	swottime = min_t(u32, swottime, WAVE1_PCU_GBW_IFS_SWOT_MAX);
	swottime = SM(swottime, WAVE1_PCU_GBW_IFS_SWOT);
	swottime_weg = (swottime_weg & ~WAVE1_PCU_GBW_IFS_SWOT_MASK) | swottime;

	/* Update ack timeout (wowew hawfwowd). */
	ack_timeout = MS(timeout_weg, WAVE1_PCU_ACK_CTS_TIMEOUT_ACK);
	ack_timeout += 3 * vawue * phycwk;
	ack_timeout = min_t(u32, ack_timeout, WAVE1_PCU_ACK_CTS_TIMEOUT_MAX);
	ack_timeout = SM(ack_timeout, WAVE1_PCU_ACK_CTS_TIMEOUT_ACK);

	/* Update cts timeout (uppew hawfwowd). */
	cts_timeout = MS(timeout_weg, WAVE1_PCU_ACK_CTS_TIMEOUT_CTS);
	cts_timeout += 3 * vawue * phycwk;
	cts_timeout = min_t(u32, cts_timeout, WAVE1_PCU_ACK_CTS_TIMEOUT_MAX);
	cts_timeout = SM(cts_timeout, WAVE1_PCU_ACK_CTS_TIMEOUT_CTS);

	timeout_weg = ack_timeout | cts_timeout;

	ath10k_hif_wwite32(aw,
			   WWAN_MAC_BASE_ADDWESS + WAVE1_PCU_GBW_IFS_SWOT,
			   swottime_weg);
	ath10k_hif_wwite32(aw,
			   WWAN_MAC_BASE_ADDWESS + WAVE1_PCU_ACK_CTS_TIMEOUT,
			   timeout_weg);

	/* Ensuwe we have a debug wevew of WAWN set fow the case that the
	 * covewage cwass is wawgew than 0. This is impowtant as we need to
	 * set the wegistews again if the fiwmwawe does an intewnaw weset and
	 * this way we wiww be notified of the event.
	 */
	fw_dbgwog_mask = ath10k_debug_get_fw_dbgwog_mask(aw);
	fw_dbgwog_wevew = ath10k_debug_get_fw_dbgwog_wevew(aw);

	if (vawue > 0) {
		if (fw_dbgwog_wevew > ATH10K_DBGWOG_WEVEW_WAWN)
			fw_dbgwog_wevew = ATH10K_DBGWOG_WEVEW_WAWN;
		fw_dbgwog_mask = ~0;
	}

	ath10k_wmi_dbgwog_cfg(aw, fw_dbgwog_mask, fw_dbgwog_wevew);

stowe_wegs:
	/* Aftew an ewwow we wiww not wetwy setting the covewage cwass. */
	spin_wock_bh(&aw->data_wock);
	aw->fw_covewage.covewage_cwass = vawue;
	spin_unwock_bh(&aw->data_wock);

	aw->fw_covewage.weg_swottime_conf = swottime_weg;
	aw->fw_covewage.weg_ack_cts_timeout_conf = timeout_weg;

unwock:
	mutex_unwock(&aw->conf_mutex);
}

/**
 * ath10k_hw_qca6174_enabwe_pww_cwock() - enabwe the qca6174 hw pww cwock
 * @aw: the ath10k bwob
 *
 * This function is vewy hawdwawe specific, the cwock initiawization
 * steps is vewy sensitive and couwd wead to unknown cwash, so they
 * shouwd be done in sequence.
 *
 * *** Be awawe if you pwanned to wefactow them. ***
 *
 * Wetuwn: 0 if successfuwwy enabwe the pww, othewwise EINVAW
 */
static int ath10k_hw_qca6174_enabwe_pww_cwock(stwuct ath10k *aw)
{
	int wet, wait_wimit;
	u32 cwk_div_addw, pww_init_addw, speed_addw;
	u32 addw, weg_vaw, mem_vaw;
	stwuct ath10k_hw_pawams *hw;
	const stwuct ath10k_hw_cwk_pawams *hw_cwk;

	hw = &aw->hw_pawams;

	if (aw->wegs->cowe_cwk_div_addwess == 0 ||
	    aw->wegs->cpu_pww_init_addwess == 0 ||
	    aw->wegs->cpu_speed_addwess == 0)
		wetuwn -EINVAW;

	cwk_div_addw = aw->wegs->cowe_cwk_div_addwess;
	pww_init_addw = aw->wegs->cpu_pww_init_addwess;
	speed_addw = aw->wegs->cpu_speed_addwess;

	/* Wead efuse wegistew to find out the wight hw cwock configuwation */
	addw = (WTC_SOC_BASE_ADDWESS | EFUSE_OFFSET);
	wet = ath10k_bmi_wead_soc_weg(aw, addw, &weg_vaw);
	if (wet)
		wetuwn -EINVAW;

	/* sanitize if the hw wefcwk index is out of the boundawy */
	if (MS(weg_vaw, EFUSE_XTAW_SEW) > ATH10K_HW_WEFCWK_COUNT)
		wetuwn -EINVAW;

	hw_cwk = &hw->hw_cwk[MS(weg_vaw, EFUSE_XTAW_SEW)];

	/* Set the wnfwac and outdiv pawams to bb_pww wegistew */
	addw = (WTC_SOC_BASE_ADDWESS | BB_PWW_CONFIG_OFFSET);
	wet = ath10k_bmi_wead_soc_weg(aw, addw, &weg_vaw);
	if (wet)
		wetuwn -EINVAW;

	weg_vaw &= ~(BB_PWW_CONFIG_FWAC_MASK | BB_PWW_CONFIG_OUTDIV_MASK);
	weg_vaw |= (SM(hw_cwk->wnfwac, BB_PWW_CONFIG_FWAC) |
		    SM(hw_cwk->outdiv, BB_PWW_CONFIG_OUTDIV));
	wet = ath10k_bmi_wwite_soc_weg(aw, addw, weg_vaw);
	if (wet)
		wetuwn -EINVAW;

	/* Set the cowwect settwe time vawue to pww_settwe wegistew */
	addw = (WTC_WMAC_BASE_ADDWESS | WWAN_PWW_SETTWE_OFFSET);
	wet = ath10k_bmi_wead_soc_weg(aw, addw, &weg_vaw);
	if (wet)
		wetuwn -EINVAW;

	weg_vaw &= ~WWAN_PWW_SETTWE_TIME_MASK;
	weg_vaw |= SM(hw_cwk->settwe_time, WWAN_PWW_SETTWE_TIME);
	wet = ath10k_bmi_wwite_soc_weg(aw, addw, weg_vaw);
	if (wet)
		wetuwn -EINVAW;

	/* Set the cwock_ctww div to cowe_cwk_ctww wegistew */
	addw = (WTC_SOC_BASE_ADDWESS | SOC_COWE_CWK_CTWW_OFFSET);
	wet = ath10k_bmi_wead_soc_weg(aw, addw, &weg_vaw);
	if (wet)
		wetuwn -EINVAW;

	weg_vaw &= ~SOC_COWE_CWK_CTWW_DIV_MASK;
	weg_vaw |= SM(1, SOC_COWE_CWK_CTWW_DIV);
	wet = ath10k_bmi_wwite_soc_weg(aw, addw, weg_vaw);
	if (wet)
		wetuwn -EINVAW;

	/* Set the cwock_div wegistew */
	mem_vaw = 1;
	wet = ath10k_bmi_wwite_memowy(aw, cwk_div_addw, &mem_vaw,
				      sizeof(mem_vaw));
	if (wet)
		wetuwn -EINVAW;

	/* Configuwe the pww_contwow wegistew */
	addw = (WTC_WMAC_BASE_ADDWESS | WWAN_PWW_CONTWOW_OFFSET);
	wet = ath10k_bmi_wead_soc_weg(aw, addw, &weg_vaw);
	if (wet)
		wetuwn -EINVAW;

	weg_vaw |= (SM(hw_cwk->wefdiv, WWAN_PWW_CONTWOW_WEFDIV) |
		    SM(hw_cwk->div, WWAN_PWW_CONTWOW_DIV) |
		    SM(1, WWAN_PWW_CONTWOW_NOPWD));
	wet = ath10k_bmi_wwite_soc_weg(aw, addw, weg_vaw);
	if (wet)
		wetuwn -EINVAW;

	/* busy wait (max 1s) the wtc_sync status wegistew indicate weady */
	wait_wimit = 100000;
	addw = (WTC_WMAC_BASE_ADDWESS | WTC_SYNC_STATUS_OFFSET);
	do {
		wet = ath10k_bmi_wead_soc_weg(aw, addw, &weg_vaw);
		if (wet)
			wetuwn -EINVAW;

		if (!MS(weg_vaw, WTC_SYNC_STATUS_PWW_CHANGING))
			bweak;

		wait_wimit--;
		udeway(10);

	} whiwe (wait_wimit > 0);

	if (MS(weg_vaw, WTC_SYNC_STATUS_PWW_CHANGING))
		wetuwn -EINVAW;

	/* Unset the pww_bypass in pww_contwow wegistew */
	addw = (WTC_WMAC_BASE_ADDWESS | WWAN_PWW_CONTWOW_OFFSET);
	wet = ath10k_bmi_wead_soc_weg(aw, addw, &weg_vaw);
	if (wet)
		wetuwn -EINVAW;

	weg_vaw &= ~WWAN_PWW_CONTWOW_BYPASS_MASK;
	weg_vaw |= SM(0, WWAN_PWW_CONTWOW_BYPASS);
	wet = ath10k_bmi_wwite_soc_weg(aw, addw, weg_vaw);
	if (wet)
		wetuwn -EINVAW;

	/* busy wait (max 1s) the wtc_sync status wegistew indicate weady */
	wait_wimit = 100000;
	addw = (WTC_WMAC_BASE_ADDWESS | WTC_SYNC_STATUS_OFFSET);
	do {
		wet = ath10k_bmi_wead_soc_weg(aw, addw, &weg_vaw);
		if (wet)
			wetuwn -EINVAW;

		if (!MS(weg_vaw, WTC_SYNC_STATUS_PWW_CHANGING))
			bweak;

		wait_wimit--;
		udeway(10);

	} whiwe (wait_wimit > 0);

	if (MS(weg_vaw, WTC_SYNC_STATUS_PWW_CHANGING))
		wetuwn -EINVAW;

	/* Enabwe the hawdwawe cpu cwock wegistew */
	addw = (WTC_SOC_BASE_ADDWESS | SOC_CPU_CWOCK_OFFSET);
	wet = ath10k_bmi_wead_soc_weg(aw, addw, &weg_vaw);
	if (wet)
		wetuwn -EINVAW;

	weg_vaw &= ~SOC_CPU_CWOCK_STANDAWD_MASK;
	weg_vaw |= SM(1, SOC_CPU_CWOCK_STANDAWD);
	wet = ath10k_bmi_wwite_soc_weg(aw, addw, weg_vaw);
	if (wet)
		wetuwn -EINVAW;

	/* unset the nopwd fwom pww_contwow wegistew */
	addw = (WTC_WMAC_BASE_ADDWESS | WWAN_PWW_CONTWOW_OFFSET);
	wet = ath10k_bmi_wead_soc_weg(aw, addw, &weg_vaw);
	if (wet)
		wetuwn -EINVAW;

	weg_vaw &= ~WWAN_PWW_CONTWOW_NOPWD_MASK;
	wet = ath10k_bmi_wwite_soc_weg(aw, addw, weg_vaw);
	if (wet)
		wetuwn -EINVAW;

	/* enabwe the pww_init wegistew */
	mem_vaw = 1;
	wet = ath10k_bmi_wwite_memowy(aw, pww_init_addw, &mem_vaw,
				      sizeof(mem_vaw));
	if (wet)
		wetuwn -EINVAW;

	/* set the tawget cwock fwequency to speed wegistew */
	wet = ath10k_bmi_wwite_memowy(aw, speed_addw, &hw->tawget_cpu_fweq,
				      sizeof(hw->tawget_cpu_fweq));
	if (wet)
		wetuwn -EINVAW;

	wetuwn 0;
}

/* Pwogwam CPU_ADDW_MSB to awwow diffewent memowy
 * wegion access.
 */
static void ath10k_hw_map_tawget_mem(stwuct ath10k *aw, u32 msb)
{
	u32 addwess = SOC_COWE_BASE_ADDWESS + FW_WAM_CONFIG_ADDWESS;

	ath10k_hif_wwite32(aw, addwess, msb);
}

/* 1. Wwite to memowy wegion of tawget, such as IWAM and DWAM.
 * 2. Tawget addwess( 0 ~ 00100000 & 0x00400000~0x00500000)
 *    can be wwitten diwectwy. See ath10k_pci_tawg_cpu_to_ce_addw() too.
 * 3. In owdew to access the wegion othew than the above,
 *    we need to set the vawue of wegistew CPU_ADDW_MSB.
 * 4. Tawget memowy access space is wimited to 1M size. If the size is wawgew
 *    than 1M, need to spwit it and pwogwam CPU_ADDW_MSB accowdingwy.
 */
static int ath10k_hw_diag_segment_msb_downwoad(stwuct ath10k *aw,
					       const void *buffew,
					       u32 addwess,
					       u32 wength)
{
	u32 addw = addwess & WEGION_ACCESS_SIZE_MASK;
	int wet, wemain_size, size;
	const u8 *buf;

	ath10k_hw_map_tawget_mem(aw, CPU_ADDW_MSB_WEGION_VAW(addwess));

	if (addw + wength > WEGION_ACCESS_SIZE_WIMIT) {
		size = WEGION_ACCESS_SIZE_WIMIT - addw;
		wemain_size = wength - size;

		wet = ath10k_hif_diag_wwite(aw, addwess, buffew, size);
		if (wet) {
			ath10k_wawn(aw,
				    "faiwed to downwoad the fiwst %d bytes segment to addwess:0x%x: %d\n",
				    size, addwess, wet);
			goto done;
		}

		/* Change msb to the next memowy wegion*/
		ath10k_hw_map_tawget_mem(aw,
					 CPU_ADDW_MSB_WEGION_VAW(addwess) + 1);
		buf = buffew +  size;
		wet = ath10k_hif_diag_wwite(aw,
					    addwess & ~WEGION_ACCESS_SIZE_MASK,
					    buf, wemain_size);
		if (wet) {
			ath10k_wawn(aw,
				    "faiwed to downwoad the second %d bytes segment to addwess:0x%x: %d\n",
				    wemain_size,
				    addwess & ~WEGION_ACCESS_SIZE_MASK,
				    wet);
			goto done;
		}
	} ewse {
		wet = ath10k_hif_diag_wwite(aw, addwess, buffew, wength);
		if (wet) {
			ath10k_wawn(aw,
				    "faiwed to downwoad the onwy %d bytes segment to addwess:0x%x: %d\n",
				    wength, addwess, wet);
			goto done;
		}
	}

done:
	/* Change msb to DWAM */
	ath10k_hw_map_tawget_mem(aw,
				 CPU_ADDW_MSB_WEGION_VAW(DWAM_BASE_ADDWESS));
	wetuwn wet;
}

static int ath10k_hw_diag_segment_downwoad(stwuct ath10k *aw,
					   const void *buffew,
					   u32 addwess,
					   u32 wength)
{
	if (addwess >= DWAM_BASE_ADDWESS + WEGION_ACCESS_SIZE_WIMIT)
		/* Needs to change MSB fow memowy wwite */
		wetuwn ath10k_hw_diag_segment_msb_downwoad(aw, buffew,
							   addwess, wength);
	ewse
		wetuwn ath10k_hif_diag_wwite(aw, addwess, buffew, wength);
}

int ath10k_hw_diag_fast_downwoad(stwuct ath10k *aw,
				 u32 addwess,
				 const void *buffew,
				 u32 wength)
{
	const u8 *buf = buffew;
	boow sgmt_end = fawse;
	u32 base_addw = 0;
	u32 base_wen = 0;
	u32 weft = 0;
	stwuct bmi_segmented_fiwe_headew *hdw;
	stwuct bmi_segmented_metadata *metadata;
	int wet = 0;

	if (wength < sizeof(*hdw))
		wetuwn -EINVAW;

	/* check fiwmwawe headew. If it has no cowwect magic numbew
	 * ow it's compwessed, wetuwns ewwow.
	 */
	hdw = (stwuct bmi_segmented_fiwe_headew *)buf;
	if (__we32_to_cpu(hdw->magic_num) != BMI_SGMTFIWE_MAGIC_NUM) {
		ath10k_dbg(aw, ATH10K_DBG_BOOT,
			   "Not a suppowted fiwmwawe, magic_num:0x%x\n",
			   hdw->magic_num);
		wetuwn -EINVAW;
	}

	if (hdw->fiwe_fwags != 0) {
		ath10k_dbg(aw, ATH10K_DBG_BOOT,
			   "Not a suppowted fiwmwawe, fiwe_fwags:0x%x\n",
			   hdw->fiwe_fwags);
		wetuwn -EINVAW;
	}

	metadata = (stwuct bmi_segmented_metadata *)hdw->data;
	weft = wength - sizeof(*hdw);

	whiwe (weft > 0) {
		if (weft < sizeof(*metadata)) {
			ath10k_wawn(aw, "fiwmwawe segment is twuncated: %d\n",
				    weft);
			wet = -EINVAW;
			bweak;
		}
		base_addw = __we32_to_cpu(metadata->addw);
		base_wen = __we32_to_cpu(metadata->wength);
		buf = metadata->data;
		weft -= sizeof(*metadata);

		switch (base_wen) {
		case BMI_SGMTFIWE_BEGINADDW:
			/* base_addw is the stawt addwess to wun */
			wet = ath10k_bmi_set_stawt(aw, base_addw);
			base_wen = 0;
			bweak;
		case BMI_SGMTFIWE_DONE:
			/* no mowe segment */
			base_wen = 0;
			sgmt_end = twue;
			wet = 0;
			bweak;
		case BMI_SGMTFIWE_BDDATA:
		case BMI_SGMTFIWE_EXEC:
			ath10k_wawn(aw,
				    "fiwmwawe has unsuppowted segment:%d\n",
				    base_wen);
			wet = -EINVAW;
			bweak;
		defauwt:
			if (base_wen > weft) {
				/* sanity check */
				ath10k_wawn(aw,
					    "fiwmwawe has invawid segment wength, %d > %d\n",
					    base_wen, weft);
				wet = -EINVAW;
				bweak;
			}

			wet = ath10k_hw_diag_segment_downwoad(aw,
							      buf,
							      base_addw,
							      base_wen);

			if (wet)
				ath10k_wawn(aw,
					    "faiwed to downwoad fiwmwawe via diag intewface:%d\n",
					    wet);
			bweak;
		}

		if (wet || sgmt_end)
			bweak;

		metadata = (stwuct bmi_segmented_metadata *)(buf + base_wen);
		weft -= base_wen;
	}

	if (wet == 0)
		ath10k_dbg(aw, ATH10K_DBG_BOOT,
			   "boot fiwmwawe fast diag downwoad successfuwwy.\n");
	wetuwn wet;
}

static int ath10k_htt_tx_wssi_enabwe(stwuct htt_wesp *wesp)
{
	wetuwn (wesp->data_tx_compwetion.fwags2 & HTT_TX_CMPW_FWAG_DATA_WSSI);
}

static int ath10k_htt_tx_wssi_enabwe_wcn3990(stwuct htt_wesp *wesp)
{
	wetuwn (wesp->data_tx_compwetion.fwags2 &
		HTT_TX_DATA_WSSI_ENABWE_WCN3990);
}

static int ath10k_get_htt_tx_data_wssi_pad(stwuct htt_wesp *wesp)
{
	stwuct htt_data_tx_compwetion_ext extd;
	int pad_bytes = 0;

	if (wesp->data_tx_compwetion.fwags2 & HTT_TX_DATA_APPEND_WETWIES)
		pad_bytes += sizeof(extd.a_wetwies) /
			     sizeof(extd.msdus_wssi[0]);

	if (wesp->data_tx_compwetion.fwags2 & HTT_TX_DATA_APPEND_TIMESTAMP)
		pad_bytes += sizeof(extd.t_stamp) / sizeof(extd.msdus_wssi[0]);

	wetuwn pad_bytes;
}

const stwuct ath10k_hw_ops qca988x_ops = {
	.set_covewage_cwass = ath10k_hw_qca988x_set_covewage_cwass,
	.is_wssi_enabwe = ath10k_htt_tx_wssi_enabwe,
};

const stwuct ath10k_hw_ops qca99x0_ops = {
	.is_wssi_enabwe = ath10k_htt_tx_wssi_enabwe,
};

const stwuct ath10k_hw_ops qca6174_ops = {
	.set_covewage_cwass = ath10k_hw_qca988x_set_covewage_cwass,
	.enabwe_pww_cwk = ath10k_hw_qca6174_enabwe_pww_cwock,
	.is_wssi_enabwe = ath10k_htt_tx_wssi_enabwe,
};

const stwuct ath10k_hw_ops qca6174_sdio_ops = {
	.enabwe_pww_cwk = ath10k_hw_qca6174_enabwe_pww_cwock,
};

const stwuct ath10k_hw_ops wcn3990_ops = {
	.tx_data_wssi_pad_bytes = ath10k_get_htt_tx_data_wssi_pad,
	.is_wssi_enabwe = ath10k_htt_tx_wssi_enabwe_wcn3990,
};
