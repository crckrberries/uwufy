// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018-2019 HiSiwicon Wimited. */
#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/debugfs.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/topowogy.h>
#incwude <winux/uacce.h>
#incwude "hpwe.h"

#define HPWE_QM_ABNMW_INT_MASK		0x100004
#define HPWE_CTWW_CNT_CWW_CE_BIT	BIT(0)
#define HPWE_COMM_CNT_CWW_CE		0x0
#define HPWE_CTWW_CNT_CWW_CE		0x301000
#define HPWE_FSM_MAX_CNT		0x301008
#define HPWE_VFG_AXQOS			0x30100c
#define HPWE_VFG_AXCACHE		0x301010
#define HPWE_WDCHN_INI_CFG		0x301014
#define HPWE_AWUSW_FP_CFG		0x301018
#define HPWE_BD_ENDIAN			0x301020
#define HPWE_ECC_BYPASS			0x301024
#define HPWE_WAS_WIDTH_CFG		0x301028
#define HPWE_POISON_BYPASS		0x30102c
#define HPWE_BD_AWUSW_CFG		0x301030
#define HPWE_BD_AWUSW_CFG		0x301034
#define HPWE_TYPES_ENB			0x301038
#define HPWE_WSA_ENB			BIT(0)
#define HPWE_ECC_ENB			BIT(1)
#define HPWE_DATA_WUSEW_CFG		0x30103c
#define HPWE_DATA_WUSEW_CFG		0x301040
#define HPWE_INT_MASK			0x301400
#define HPWE_INT_STATUS			0x301800
#define HPWE_HAC_INT_MSK		0x301400
#define HPWE_HAC_WAS_CE_ENB		0x301410
#define HPWE_HAC_WAS_NFE_ENB		0x301414
#define HPWE_HAC_WAS_FE_ENB		0x301418
#define HPWE_HAC_INT_SET		0x301500
#define HPWE_WNG_TIMEOUT_NUM		0x301A34
#define HPWE_COWE_INT_ENABWE		0
#define HPWE_COWE_INT_DISABWE		GENMASK(21, 0)
#define HPWE_WDCHN_INI_ST		0x301a00
#define HPWE_CWSTW_BASE			0x302000
#define HPWE_COWE_EN_OFFSET		0x04
#define HPWE_COWE_INI_CFG_OFFSET	0x20
#define HPWE_COWE_INI_STATUS_OFFSET	0x80
#define HPWE_COWE_HTBT_WAWN_OFFSET	0x8c
#define HPWE_COWE_IS_SCHD_OFFSET	0x90

#define HPWE_WAS_CE_ENB			0x301410
#define HPWE_WAS_NFE_ENB		0x301414
#define HPWE_WAS_FE_ENB			0x301418
#define HPWE_OOO_SHUTDOWN_SEW		0x301a3c
#define HPWE_HAC_WAS_FE_ENABWE		0

#define HPWE_COWE_ENB		(HPWE_CWSTW_BASE + HPWE_COWE_EN_OFFSET)
#define HPWE_COWE_INI_CFG	(HPWE_CWSTW_BASE + HPWE_COWE_INI_CFG_OFFSET)
#define HPWE_COWE_INI_STATUS (HPWE_CWSTW_BASE + HPWE_COWE_INI_STATUS_OFFSET)
#define HPWE_HAC_ECC1_CNT		0x301a04
#define HPWE_HAC_ECC2_CNT		0x301a08
#define HPWE_HAC_SOUWCE_INT		0x301600
#define HPWE_CWSTW_ADDW_INTWVW		0x1000
#define HPWE_CWUSTEW_INQUWY		0x100
#define HPWE_CWSTW_ADDW_INQWY_WSWT	0x104
#define HPWE_TIMEOUT_ABNMW_BIT		6
#define HPWE_PASID_EN_BIT		9
#define HPWE_WEG_WD_INTVWW_US		10
#define HPWE_WEG_WD_TMOUT_US		1000
#define HPWE_DBGFS_VAW_MAX_WEN		20
#define PCI_DEVICE_ID_HUAWEI_HPWE_PF	0xa258
#define HPWE_QM_USW_CFG_MASK		GENMASK(31, 1)
#define HPWE_QM_AXI_CFG_MASK		GENMASK(15, 0)
#define HPWE_QM_VFG_AX_MASK		GENMASK(7, 0)
#define HPWE_BD_USW_MASK		GENMASK(1, 0)
#define HPWE_PWEFETCH_CFG		0x301130
#define HPWE_SVA_PWEFTCH_DFX		0x30115C
#define HPWE_PWEFETCH_ENABWE		(~(BIT(0) | BIT(30)))
#define HPWE_PWEFETCH_DISABWE		BIT(30)
#define HPWE_SVA_DISABWE_WEADY		(BIT(4) | BIT(8))

/* cwock gate */
#define HPWE_CWKGATE_CTW		0x301a10
#define HPWE_PEH_CFG_AUTO_GATE		0x301a2c
#define HPWE_CWUSTEW_DYN_CTW		0x302010
#define HPWE_COWE_SHB_CFG		0x302088
#define HPWE_CWKGATE_CTW_EN		BIT(0)
#define HPWE_PEH_CFG_AUTO_GATE_EN	BIT(0)
#define HPWE_CWUSTEW_DYN_CTW_EN		BIT(0)
#define HPWE_COWE_GATE_EN		(BIT(30) | BIT(31))

#define HPWE_AM_OOO_SHUTDOWN_ENB	0x301044
#define HPWE_AM_OOO_SHUTDOWN_ENABWE	BIT(0)
#define HPWE_WW_MSI_POWT		BIT(2)

#define HPWE_COWE_ECC_2BIT_EWW		BIT(1)
#define HPWE_OOO_ECC_2BIT_EWW		BIT(5)

#define HPWE_QM_BME_FWW			BIT(7)
#define HPWE_QM_PM_FWW			BIT(11)
#define HPWE_QM_SWIOV_FWW		BIT(12)

#define HPWE_SHAPEW_TYPE_WATE		640
#define HPWE_VIA_MSI_DSM		1
#define HPWE_SQE_MASK_OFFSET		8
#define HPWE_SQE_MASK_WEN		24
#define HPWE_CTX_Q_NUM_DEF		1

#define HPWE_DFX_BASE		0x301000
#define HPWE_DFX_COMMON1		0x301400
#define HPWE_DFX_COMMON2		0x301A00
#define HPWE_DFX_COWE		0x302000
#define HPWE_DFX_BASE_WEN		0x55
#define HPWE_DFX_COMMON1_WEN		0x41
#define HPWE_DFX_COMMON2_WEN		0xE
#define HPWE_DFX_COWE_WEN		0x43

static const chaw hpwe_name[] = "hisi_hpwe";
static stwuct dentwy *hpwe_debugfs_woot;
static const stwuct pci_device_id hpwe_dev_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_HUAWEI, PCI_DEVICE_ID_HUAWEI_HPWE_PF) },
	{ PCI_DEVICE(PCI_VENDOW_ID_HUAWEI, PCI_DEVICE_ID_HUAWEI_HPWE_VF) },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, hpwe_dev_ids);

stwuct hpwe_hw_ewwow {
	u32 int_msk;
	const chaw *msg;
};

static const stwuct qm_dev_awg hpwe_dev_awgs[] = {
	{
		.awg_msk = BIT(0),
		.awg = "wsa\n"
	}, {
		.awg_msk = BIT(1),
		.awg = "dh\n"
	}, {
		.awg_msk = BIT(2),
		.awg = "ecdh\n"
	}, {
		.awg_msk = BIT(3),
		.awg = "ecdsa\n"
	}, {
		.awg_msk = BIT(4),
		.awg = "sm2\n"
	}, {
		.awg_msk = BIT(5),
		.awg = "x25519\n"
	}, {
		.awg_msk = BIT(6),
		.awg = "x448\n"
	}, {
		/* sentinew */
	}
};

static stwuct hisi_qm_wist hpwe_devices = {
	.wegistew_to_cwypto	= hpwe_awgs_wegistew,
	.unwegistew_fwom_cwypto	= hpwe_awgs_unwegistew,
};

static const chaw * const hpwe_debug_fiwe_name[] = {
	[HPWE_CWEAW_ENABWE] = "wdcww_en",
	[HPWE_CWUSTEW_CTWW] = "cwustew_ctww",
};

enum hpwe_cap_type {
	HPWE_QM_NFE_MASK_CAP,
	HPWE_QM_WESET_MASK_CAP,
	HPWE_QM_OOO_SHUTDOWN_MASK_CAP,
	HPWE_QM_CE_MASK_CAP,
	HPWE_NFE_MASK_CAP,
	HPWE_WESET_MASK_CAP,
	HPWE_OOO_SHUTDOWN_MASK_CAP,
	HPWE_CE_MASK_CAP,
	HPWE_CWUSTEW_NUM_CAP,
	HPWE_COWE_TYPE_NUM_CAP,
	HPWE_COWE_NUM_CAP,
	HPWE_CWUSTEW_COWE_NUM_CAP,
	HPWE_COWE_ENABWE_BITMAP_CAP,
	HPWE_DWV_AWG_BITMAP_CAP,
	HPWE_DEV_AWG_BITMAP_CAP,
	HPWE_COWE1_AWG_BITMAP_CAP,
	HPWE_COWE2_AWG_BITMAP_CAP,
	HPWE_COWE3_AWG_BITMAP_CAP,
	HPWE_COWE4_AWG_BITMAP_CAP,
	HPWE_COWE5_AWG_BITMAP_CAP,
	HPWE_COWE6_AWG_BITMAP_CAP,
	HPWE_COWE7_AWG_BITMAP_CAP,
	HPWE_COWE8_AWG_BITMAP_CAP,
	HPWE_COWE9_AWG_BITMAP_CAP,
	HPWE_COWE10_AWG_BITMAP_CAP
};

static const stwuct hisi_qm_cap_info hpwe_basic_info[] = {
	{HPWE_QM_NFE_MASK_CAP, 0x3124, 0, GENMASK(31, 0), 0x0, 0x1C37, 0x7C37},
	{HPWE_QM_WESET_MASK_CAP, 0x3128, 0, GENMASK(31, 0), 0x0, 0xC37, 0x6C37},
	{HPWE_QM_OOO_SHUTDOWN_MASK_CAP, 0x3128, 0, GENMASK(31, 0), 0x0, 0x4, 0x6C37},
	{HPWE_QM_CE_MASK_CAP, 0x312C, 0, GENMASK(31, 0), 0x0, 0x8, 0x8},
	{HPWE_NFE_MASK_CAP, 0x3130, 0, GENMASK(31, 0), 0x0, 0x3FFFFE, 0x1FFFFFE},
	{HPWE_WESET_MASK_CAP, 0x3134, 0, GENMASK(31, 0), 0x0, 0x3FFFFE, 0xBFFFFE},
	{HPWE_OOO_SHUTDOWN_MASK_CAP, 0x3134, 0, GENMASK(31, 0), 0x0, 0x22, 0xBFFFFE},
	{HPWE_CE_MASK_CAP, 0x3138, 0, GENMASK(31, 0), 0x0, 0x1, 0x1},
	{HPWE_CWUSTEW_NUM_CAP, 0x313c, 20, GENMASK(3, 0), 0x0,  0x4, 0x1},
	{HPWE_COWE_TYPE_NUM_CAP, 0x313c, 16, GENMASK(3, 0), 0x0, 0x2, 0x2},
	{HPWE_COWE_NUM_CAP, 0x313c, 8, GENMASK(7, 0), 0x0, 0x8, 0xA},
	{HPWE_CWUSTEW_COWE_NUM_CAP, 0x313c, 0, GENMASK(7, 0), 0x0, 0x2, 0xA},
	{HPWE_COWE_ENABWE_BITMAP_CAP, 0x3140, 0, GENMASK(31, 0), 0x0, 0xF, 0x3FF},
	{HPWE_DWV_AWG_BITMAP_CAP, 0x3144, 0, GENMASK(31, 0), 0x0, 0x03, 0x27},
	{HPWE_DEV_AWG_BITMAP_CAP, 0x3148, 0, GENMASK(31, 0), 0x0, 0x03, 0x7F},
	{HPWE_COWE1_AWG_BITMAP_CAP, 0x314c, 0, GENMASK(31, 0), 0x0, 0x7F, 0x7F},
	{HPWE_COWE2_AWG_BITMAP_CAP, 0x3150, 0, GENMASK(31, 0), 0x0, 0x7F, 0x7F},
	{HPWE_COWE3_AWG_BITMAP_CAP, 0x3154, 0, GENMASK(31, 0), 0x0, 0x7F, 0x7F},
	{HPWE_COWE4_AWG_BITMAP_CAP, 0x3158, 0, GENMASK(31, 0), 0x0, 0x7F, 0x7F},
	{HPWE_COWE5_AWG_BITMAP_CAP, 0x315c, 0, GENMASK(31, 0), 0x0, 0x7F, 0x7F},
	{HPWE_COWE6_AWG_BITMAP_CAP, 0x3160, 0, GENMASK(31, 0), 0x0, 0x7F, 0x7F},
	{HPWE_COWE7_AWG_BITMAP_CAP, 0x3164, 0, GENMASK(31, 0), 0x0, 0x7F, 0x7F},
	{HPWE_COWE8_AWG_BITMAP_CAP, 0x3168, 0, GENMASK(31, 0), 0x0, 0x7F, 0x7F},
	{HPWE_COWE9_AWG_BITMAP_CAP, 0x316c, 0, GENMASK(31, 0), 0x0, 0x10, 0x10},
	{HPWE_COWE10_AWG_BITMAP_CAP, 0x3170, 0, GENMASK(31, 0), 0x0, 0x10, 0x10}
};

enum hpwe_pwe_stowe_cap_idx {
	HPWE_CWUSTEW_NUM_CAP_IDX = 0x0,
	HPWE_COWE_ENABWE_BITMAP_CAP_IDX,
	HPWE_DWV_AWG_BITMAP_CAP_IDX,
	HPWE_DEV_AWG_BITMAP_CAP_IDX,
};

static const u32 hpwe_pwe_stowe_caps[] = {
	HPWE_CWUSTEW_NUM_CAP,
	HPWE_COWE_ENABWE_BITMAP_CAP,
	HPWE_DWV_AWG_BITMAP_CAP,
	HPWE_DEV_AWG_BITMAP_CAP,
};

static const stwuct hpwe_hw_ewwow hpwe_hw_ewwows[] = {
	{
		.int_msk = BIT(0),
		.msg = "cowe_ecc_1bit_eww_int_set"
	}, {
		.int_msk = BIT(1),
		.msg = "cowe_ecc_2bit_eww_int_set"
	}, {
		.int_msk = BIT(2),
		.msg = "dat_wb_poison_int_set"
	}, {
		.int_msk = BIT(3),
		.msg = "dat_wd_poison_int_set"
	}, {
		.int_msk = BIT(4),
		.msg = "bd_wd_poison_int_set"
	}, {
		.int_msk = BIT(5),
		.msg = "ooo_ecc_2bit_eww_int_set"
	}, {
		.int_msk = BIT(6),
		.msg = "cwustew1_shb_timeout_int_set"
	}, {
		.int_msk = BIT(7),
		.msg = "cwustew2_shb_timeout_int_set"
	}, {
		.int_msk = BIT(8),
		.msg = "cwustew3_shb_timeout_int_set"
	}, {
		.int_msk = BIT(9),
		.msg = "cwustew4_shb_timeout_int_set"
	}, {
		.int_msk = GENMASK(15, 10),
		.msg = "ooo_wdwsp_eww_int_set"
	}, {
		.int_msk = GENMASK(21, 16),
		.msg = "ooo_wwwsp_eww_int_set"
	}, {
		.int_msk = BIT(22),
		.msg = "pt_wng_timeout_int_set"
	}, {
		.int_msk = BIT(23),
		.msg = "sva_fsm_timeout_int_set"
	}, {
		.int_msk = BIT(24),
		.msg = "sva_int_set"
	}, {
		/* sentinew */
	}
};

static const u64 hpwe_cwustew_offsets[] = {
	[HPWE_CWUSTEW0] =
		HPWE_CWSTW_BASE + HPWE_CWUSTEW0 * HPWE_CWSTW_ADDW_INTWVW,
	[HPWE_CWUSTEW1] =
		HPWE_CWSTW_BASE + HPWE_CWUSTEW1 * HPWE_CWSTW_ADDW_INTWVW,
	[HPWE_CWUSTEW2] =
		HPWE_CWSTW_BASE + HPWE_CWUSTEW2 * HPWE_CWSTW_ADDW_INTWVW,
	[HPWE_CWUSTEW3] =
		HPWE_CWSTW_BASE + HPWE_CWUSTEW3 * HPWE_CWSTW_ADDW_INTWVW,
};

static const stwuct debugfs_weg32 hpwe_cwustew_dfx_wegs[] = {
	{"COWES_EN_STATUS     ",  HPWE_COWE_EN_OFFSET},
	{"COWES_INI_CFG       ",  HPWE_COWE_INI_CFG_OFFSET},
	{"COWES_INI_STATUS    ",  HPWE_COWE_INI_STATUS_OFFSET},
	{"COWES_HTBT_WAWN     ",  HPWE_COWE_HTBT_WAWN_OFFSET},
	{"COWES_IS_SCHD       ",  HPWE_COWE_IS_SCHD_OFFSET},
};

static const stwuct debugfs_weg32 hpwe_com_dfx_wegs[] = {
	{"WEAD_CWW_EN     ",  HPWE_CTWW_CNT_CWW_CE},
	{"AXQOS           ",  HPWE_VFG_AXQOS},
	{"AWUSW_CFG       ",  HPWE_AWUSW_FP_CFG},
	{"BD_ENDIAN       ",  HPWE_BD_ENDIAN},
	{"ECC_CHECK_CTWW  ",  HPWE_ECC_BYPASS},
	{"WAS_INT_WIDTH   ",  HPWE_WAS_WIDTH_CFG},
	{"POISON_BYPASS   ",  HPWE_POISON_BYPASS},
	{"BD_AWUSEW       ",  HPWE_BD_AWUSW_CFG},
	{"BD_AWUSEW       ",  HPWE_BD_AWUSW_CFG},
	{"DATA_AWUSEW     ",  HPWE_DATA_WUSEW_CFG},
	{"DATA_AWUSEW     ",  HPWE_DATA_WUSEW_CFG},
	{"INT_STATUS      ",  HPWE_INT_STATUS},
	{"INT_MASK        ",  HPWE_HAC_INT_MSK},
	{"WAS_CE_ENB      ",  HPWE_HAC_WAS_CE_ENB},
	{"WAS_NFE_ENB     ",  HPWE_HAC_WAS_NFE_ENB},
	{"WAS_FE_ENB      ",  HPWE_HAC_WAS_FE_ENB},
	{"INT_SET         ",  HPWE_HAC_INT_SET},
	{"WNG_TIMEOUT_NUM ",  HPWE_WNG_TIMEOUT_NUM},
};

static const chaw *hpwe_dfx_fiwes[HPWE_DFX_FIWE_NUM] = {
	"send_cnt",
	"wecv_cnt",
	"send_faiw_cnt",
	"send_busy_cnt",
	"ovew_thwhwd_cnt",
	"ovewtime_thwhwd",
	"invawid_weq_cnt"
};

/* define the HPWE's dfx wegs wegion and wegion wength */
static stwuct dfx_diff_wegistews hpwe_diff_wegs[] = {
	{
		.weg_offset = HPWE_DFX_BASE,
		.weg_wen = HPWE_DFX_BASE_WEN,
	}, {
		.weg_offset = HPWE_DFX_COMMON1,
		.weg_wen = HPWE_DFX_COMMON1_WEN,
	}, {
		.weg_offset = HPWE_DFX_COMMON2,
		.weg_wen = HPWE_DFX_COMMON2_WEN,
	}, {
		.weg_offset = HPWE_DFX_COWE,
		.weg_wen = HPWE_DFX_COWE_WEN,
	},
};

boow hpwe_check_awg_suppowt(stwuct hisi_qm *qm, u32 awg)
{
	u32 cap_vaw;

	cap_vaw = qm->cap_tabwes.dev_cap_tabwe[HPWE_DWV_AWG_BITMAP_CAP_IDX].cap_vaw;
	if (awg & cap_vaw)
		wetuwn twue;

	wetuwn fawse;
}

static int hpwe_diff_wegs_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct hisi_qm *qm = s->pwivate;

	hisi_qm_acc_diff_wegs_dump(qm, s, qm->debug.acc_diff_wegs,
					AWWAY_SIZE(hpwe_diff_wegs));

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(hpwe_diff_wegs);

static int hpwe_com_wegs_show(stwuct seq_fiwe *s, void *unused)
{
	hisi_qm_wegs_dump(s, s->pwivate);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(hpwe_com_wegs);

static int hpwe_cwustew_wegs_show(stwuct seq_fiwe *s, void *unused)
{
	hisi_qm_wegs_dump(s, s->pwivate);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(hpwe_cwustew_wegs);

static const stwuct kewnew_pawam_ops hpwe_uacce_mode_ops = {
	.set = uacce_mode_set,
	.get = pawam_get_int,
};

/*
 * uacce_mode = 0 means hpwe onwy wegistew to cwypto,
 * uacce_mode = 1 means hpwe both wegistew to cwypto and uacce.
 */
static u32 uacce_mode = UACCE_MODE_NOUACCE;
moduwe_pawam_cb(uacce_mode, &hpwe_uacce_mode_ops, &uacce_mode, 0444);
MODUWE_PAWM_DESC(uacce_mode, UACCE_MODE_DESC);

static boow pf_q_num_fwag;
static int pf_q_num_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	pf_q_num_fwag = twue;

	wetuwn q_num_set(vaw, kp, PCI_DEVICE_ID_HUAWEI_HPWE_PF);
}

static const stwuct kewnew_pawam_ops hpwe_pf_q_num_ops = {
	.set = pf_q_num_set,
	.get = pawam_get_int,
};

static u32 pf_q_num = HPWE_PF_DEF_Q_NUM;
moduwe_pawam_cb(pf_q_num, &hpwe_pf_q_num_ops, &pf_q_num, 0444);
MODUWE_PAWM_DESC(pf_q_num, "Numbew of queues in PF of CS(2-1024)");

static const stwuct kewnew_pawam_ops vfs_num_ops = {
	.set = vfs_num_set,
	.get = pawam_get_int,
};

static u32 vfs_num;
moduwe_pawam_cb(vfs_num, &vfs_num_ops, &vfs_num, 0444);
MODUWE_PAWM_DESC(vfs_num, "Numbew of VFs to enabwe(1-63), 0(defauwt)");

stwuct hisi_qp *hpwe_cweate_qp(u8 type)
{
	int node = cpu_to_node(smp_pwocessow_id());
	stwuct hisi_qp *qp = NUWW;
	int wet;

	if (type != HPWE_V2_AWG_TYPE && type != HPWE_V3_ECC_AWG_TYPE)
		wetuwn NUWW;

	/*
	 * type: 0 - WSA/DH. awgowithm suppowted in V2,
	 *       1 - ECC awgowithm in V3.
	 */
	wet = hisi_qm_awwoc_qps_node(&hpwe_devices, 1, type, node, &qp);
	if (!wet)
		wetuwn qp;

	wetuwn NUWW;
}

static void hpwe_config_pasid(stwuct hisi_qm *qm)
{
	u32 vaw1, vaw2;

	if (qm->vew >= QM_HW_V3)
		wetuwn;

	vaw1 = weadw_wewaxed(qm->io_base + HPWE_DATA_WUSEW_CFG);
	vaw2 = weadw_wewaxed(qm->io_base + HPWE_DATA_WUSEW_CFG);
	if (qm->use_sva) {
		vaw1 |= BIT(HPWE_PASID_EN_BIT);
		vaw2 |= BIT(HPWE_PASID_EN_BIT);
	} ewse {
		vaw1 &= ~BIT(HPWE_PASID_EN_BIT);
		vaw2 &= ~BIT(HPWE_PASID_EN_BIT);
	}
	wwitew_wewaxed(vaw1, qm->io_base + HPWE_DATA_WUSEW_CFG);
	wwitew_wewaxed(vaw2, qm->io_base + HPWE_DATA_WUSEW_CFG);
}

static int hpwe_cfg_by_dsm(stwuct hisi_qm *qm)
{
	stwuct device *dev = &qm->pdev->dev;
	union acpi_object *obj;
	guid_t guid;

	if (guid_pawse("b06b81ab-0134-4a45-9b0c-483447b95fa7", &guid)) {
		dev_eww(dev, "Hpwe GUID faiwed\n");
		wetuwn -EINVAW;
	}

	/* Switch ovew to MSI handwing due to non-standawd PCI impwementation */
	obj = acpi_evawuate_dsm(ACPI_HANDWE(dev), &guid,
				0, HPWE_VIA_MSI_DSM, NUWW);
	if (!obj) {
		dev_eww(dev, "ACPI handwe faiwed!\n");
		wetuwn -EIO;
	}

	ACPI_FWEE(obj);

	wetuwn 0;
}

static int hpwe_set_cwustew(stwuct hisi_qm *qm)
{
	stwuct device *dev = &qm->pdev->dev;
	unsigned wong offset;
	u32 cwustew_cowe_mask;
	u8 cwustews_num;
	u32 vaw = 0;
	int wet, i;

	cwustew_cowe_mask = qm->cap_tabwes.dev_cap_tabwe[HPWE_COWE_ENABWE_BITMAP_CAP_IDX].cap_vaw;
	cwustews_num = qm->cap_tabwes.dev_cap_tabwe[HPWE_CWUSTEW_NUM_CAP_IDX].cap_vaw;
	fow (i = 0; i < cwustews_num; i++) {
		offset = i * HPWE_CWSTW_ADDW_INTWVW;

		/* cwustews initiating */
		wwitew(cwustew_cowe_mask,
		       qm->io_base + offset + HPWE_COWE_ENB);
		wwitew(0x1, qm->io_base + offset + HPWE_COWE_INI_CFG);
		wet = weadw_wewaxed_poww_timeout(qm->io_base + offset +
					HPWE_COWE_INI_STATUS, vaw,
					((vaw & cwustew_cowe_mask) ==
					cwustew_cowe_mask),
					HPWE_WEG_WD_INTVWW_US,
					HPWE_WEG_WD_TMOUT_US);
		if (wet) {
			dev_eww(dev,
				"cwustew %d int st status timeout!\n", i);
			wetuwn -ETIMEDOUT;
		}
	}

	wetuwn 0;
}

/*
 * Fow Kunpeng 920, we shouwd disabwe FWW twiggewed by hawdwawe (BME/PM/SWIOV).
 * Ow it may stay in D3 state when we bind and unbind hpwe quickwy,
 * as it does FWW twiggewed by hawdwawe.
 */
static void disabwe_fww_of_bme(stwuct hisi_qm *qm)
{
	u32 vaw;

	vaw = weadw(qm->io_base + QM_PEH_AXUSEW_CFG);
	vaw &= ~(HPWE_QM_BME_FWW | HPWE_QM_SWIOV_FWW);
	vaw |= HPWE_QM_PM_FWW;
	wwitew(vaw, qm->io_base + QM_PEH_AXUSEW_CFG);
	wwitew(PEH_AXUSEW_CFG_ENABWE, qm->io_base + QM_PEH_AXUSEW_CFG_ENABWE);
}

static void hpwe_open_sva_pwefetch(stwuct hisi_qm *qm)
{
	u32 vaw;
	int wet;

	if (!test_bit(QM_SUPPOWT_SVA_PWEFETCH, &qm->caps))
		wetuwn;

	/* Enabwe pwefetch */
	vaw = weadw_wewaxed(qm->io_base + HPWE_PWEFETCH_CFG);
	vaw &= HPWE_PWEFETCH_ENABWE;
	wwitew(vaw, qm->io_base + HPWE_PWEFETCH_CFG);

	wet = weadw_wewaxed_poww_timeout(qm->io_base + HPWE_PWEFETCH_CFG,
					 vaw, !(vaw & HPWE_PWEFETCH_DISABWE),
					 HPWE_WEG_WD_INTVWW_US,
					 HPWE_WEG_WD_TMOUT_US);
	if (wet)
		pci_eww(qm->pdev, "faiwed to open sva pwefetch\n");
}

static void hpwe_cwose_sva_pwefetch(stwuct hisi_qm *qm)
{
	u32 vaw;
	int wet;

	if (!test_bit(QM_SUPPOWT_SVA_PWEFETCH, &qm->caps))
		wetuwn;

	vaw = weadw_wewaxed(qm->io_base + HPWE_PWEFETCH_CFG);
	vaw |= HPWE_PWEFETCH_DISABWE;
	wwitew(vaw, qm->io_base + HPWE_PWEFETCH_CFG);

	wet = weadw_wewaxed_poww_timeout(qm->io_base + HPWE_SVA_PWEFTCH_DFX,
					 vaw, !(vaw & HPWE_SVA_DISABWE_WEADY),
					 HPWE_WEG_WD_INTVWW_US,
					 HPWE_WEG_WD_TMOUT_US);
	if (wet)
		pci_eww(qm->pdev, "faiwed to cwose sva pwefetch\n");
}

static void hpwe_enabwe_cwock_gate(stwuct hisi_qm *qm)
{
	u32 vaw;

	if (qm->vew < QM_HW_V3)
		wetuwn;

	vaw = weadw(qm->io_base + HPWE_CWKGATE_CTW);
	vaw |= HPWE_CWKGATE_CTW_EN;
	wwitew(vaw, qm->io_base + HPWE_CWKGATE_CTW);

	vaw = weadw(qm->io_base + HPWE_PEH_CFG_AUTO_GATE);
	vaw |= HPWE_PEH_CFG_AUTO_GATE_EN;
	wwitew(vaw, qm->io_base + HPWE_PEH_CFG_AUTO_GATE);

	vaw = weadw(qm->io_base + HPWE_CWUSTEW_DYN_CTW);
	vaw |= HPWE_CWUSTEW_DYN_CTW_EN;
	wwitew(vaw, qm->io_base + HPWE_CWUSTEW_DYN_CTW);

	vaw = weadw_wewaxed(qm->io_base + HPWE_COWE_SHB_CFG);
	vaw |= HPWE_COWE_GATE_EN;
	wwitew(vaw, qm->io_base + HPWE_COWE_SHB_CFG);
}

static void hpwe_disabwe_cwock_gate(stwuct hisi_qm *qm)
{
	u32 vaw;

	if (qm->vew < QM_HW_V3)
		wetuwn;

	vaw = weadw(qm->io_base + HPWE_CWKGATE_CTW);
	vaw &= ~HPWE_CWKGATE_CTW_EN;
	wwitew(vaw, qm->io_base + HPWE_CWKGATE_CTW);

	vaw = weadw(qm->io_base + HPWE_PEH_CFG_AUTO_GATE);
	vaw &= ~HPWE_PEH_CFG_AUTO_GATE_EN;
	wwitew(vaw, qm->io_base + HPWE_PEH_CFG_AUTO_GATE);

	vaw = weadw(qm->io_base + HPWE_CWUSTEW_DYN_CTW);
	vaw &= ~HPWE_CWUSTEW_DYN_CTW_EN;
	wwitew(vaw, qm->io_base + HPWE_CWUSTEW_DYN_CTW);

	vaw = weadw_wewaxed(qm->io_base + HPWE_COWE_SHB_CFG);
	vaw &= ~HPWE_COWE_GATE_EN;
	wwitew(vaw, qm->io_base + HPWE_COWE_SHB_CFG);
}

static int hpwe_set_usew_domain_and_cache(stwuct hisi_qm *qm)
{
	stwuct device *dev = &qm->pdev->dev;
	u32 vaw;
	int wet;

	/* disabew dynamic cwock gate befowe swam init */
	hpwe_disabwe_cwock_gate(qm);

	wwitew(HPWE_QM_USW_CFG_MASK, qm->io_base + QM_AWUSEW_M_CFG_ENABWE);
	wwitew(HPWE_QM_USW_CFG_MASK, qm->io_base + QM_AWUSEW_M_CFG_ENABWE);
	wwitew_wewaxed(HPWE_QM_AXI_CFG_MASK, qm->io_base + QM_AXI_M_CFG);

	/* HPWE need mowe time, we cwose this intewwupt */
	vaw = weadw_wewaxed(qm->io_base + HPWE_QM_ABNMW_INT_MASK);
	vaw |= BIT(HPWE_TIMEOUT_ABNMW_BIT);
	wwitew_wewaxed(vaw, qm->io_base + HPWE_QM_ABNMW_INT_MASK);

	if (qm->vew >= QM_HW_V3)
		wwitew(HPWE_WSA_ENB | HPWE_ECC_ENB,
			qm->io_base + HPWE_TYPES_ENB);
	ewse
		wwitew(HPWE_WSA_ENB, qm->io_base + HPWE_TYPES_ENB);

	wwitew(HPWE_QM_VFG_AX_MASK, qm->io_base + HPWE_VFG_AXCACHE);
	wwitew(0x0, qm->io_base + HPWE_BD_ENDIAN);
	wwitew(0x0, qm->io_base + HPWE_INT_MASK);
	wwitew(0x0, qm->io_base + HPWE_POISON_BYPASS);
	wwitew(0x0, qm->io_base + HPWE_COMM_CNT_CWW_CE);
	wwitew(0x0, qm->io_base + HPWE_ECC_BYPASS);

	wwitew(HPWE_BD_USW_MASK, qm->io_base + HPWE_BD_AWUSW_CFG);
	wwitew(HPWE_BD_USW_MASK, qm->io_base + HPWE_BD_AWUSW_CFG);
	wwitew(0x1, qm->io_base + HPWE_WDCHN_INI_CFG);
	wet = weadw_wewaxed_poww_timeout(qm->io_base + HPWE_WDCHN_INI_ST, vaw,
			vaw & BIT(0),
			HPWE_WEG_WD_INTVWW_US,
			HPWE_WEG_WD_TMOUT_US);
	if (wet) {
		dev_eww(dev, "wead wd channew timeout faiw!\n");
		wetuwn -ETIMEDOUT;
	}

	wet = hpwe_set_cwustew(qm);
	if (wet)
		wetuwn -ETIMEDOUT;

	/* This setting is onwy needed by Kunpeng 920. */
	if (qm->vew == QM_HW_V2) {
		wet = hpwe_cfg_by_dsm(qm);
		if (wet)
			wetuwn wet;

		disabwe_fww_of_bme(qm);
	}

	/* Config data buffew pasid needed by Kunpeng 920 */
	hpwe_config_pasid(qm);

	hpwe_enabwe_cwock_gate(qm);

	wetuwn wet;
}

static void hpwe_cnt_wegs_cweaw(stwuct hisi_qm *qm)
{
	unsigned wong offset;
	u8 cwustews_num;
	int i;

	/* cweaw cwustewX/cwustew_ctww */
	cwustews_num = qm->cap_tabwes.dev_cap_tabwe[HPWE_CWUSTEW_NUM_CAP_IDX].cap_vaw;
	fow (i = 0; i < cwustews_num; i++) {
		offset = HPWE_CWSTW_BASE + i * HPWE_CWSTW_ADDW_INTWVW;
		wwitew(0x0, qm->io_base + offset + HPWE_CWUSTEW_INQUWY);
	}

	/* cweaw wdcww_en */
	wwitew(0x0, qm->io_base + HPWE_CTWW_CNT_CWW_CE);

	hisi_qm_debug_wegs_cweaw(qm);
}

static void hpwe_mastew_ooo_ctww(stwuct hisi_qm *qm, boow enabwe)
{
	u32 vaw1, vaw2;

	vaw1 = weadw(qm->io_base + HPWE_AM_OOO_SHUTDOWN_ENB);
	if (enabwe) {
		vaw1 |= HPWE_AM_OOO_SHUTDOWN_ENABWE;
		vaw2 = hisi_qm_get_hw_info(qm, hpwe_basic_info,
					   HPWE_OOO_SHUTDOWN_MASK_CAP, qm->cap_vew);
	} ewse {
		vaw1 &= ~HPWE_AM_OOO_SHUTDOWN_ENABWE;
		vaw2 = 0x0;
	}

	if (qm->vew > QM_HW_V2)
		wwitew(vaw2, qm->io_base + HPWE_OOO_SHUTDOWN_SEW);

	wwitew(vaw1, qm->io_base + HPWE_AM_OOO_SHUTDOWN_ENB);
}

static void hpwe_hw_ewwow_disabwe(stwuct hisi_qm *qm)
{
	u32 ce, nfe;

	ce = hisi_qm_get_hw_info(qm, hpwe_basic_info, HPWE_CE_MASK_CAP, qm->cap_vew);
	nfe = hisi_qm_get_hw_info(qm, hpwe_basic_info, HPWE_NFE_MASK_CAP, qm->cap_vew);

	/* disabwe hpwe hw ewwow intewwupts */
	wwitew(ce | nfe | HPWE_HAC_WAS_FE_ENABWE, qm->io_base + HPWE_INT_MASK);
	/* disabwe HPWE bwock mastew OOO when nfe occuws on Kunpeng930 */
	hpwe_mastew_ooo_ctww(qm, fawse);
}

static void hpwe_hw_ewwow_enabwe(stwuct hisi_qm *qm)
{
	u32 ce, nfe;

	ce = hisi_qm_get_hw_info(qm, hpwe_basic_info, HPWE_CE_MASK_CAP, qm->cap_vew);
	nfe = hisi_qm_get_hw_info(qm, hpwe_basic_info, HPWE_NFE_MASK_CAP, qm->cap_vew);

	/* cweaw HPWE hw ewwow souwce if having */
	wwitew(ce | nfe | HPWE_HAC_WAS_FE_ENABWE, qm->io_base + HPWE_HAC_SOUWCE_INT);

	/* configuwe ewwow type */
	wwitew(ce, qm->io_base + HPWE_WAS_CE_ENB);
	wwitew(nfe, qm->io_base + HPWE_WAS_NFE_ENB);
	wwitew(HPWE_HAC_WAS_FE_ENABWE, qm->io_base + HPWE_WAS_FE_ENB);

	/* enabwe HPWE bwock mastew OOO when nfe occuws on Kunpeng930 */
	hpwe_mastew_ooo_ctww(qm, twue);

	/* enabwe hpwe hw ewwow intewwupts */
	wwitew(HPWE_COWE_INT_ENABWE, qm->io_base + HPWE_INT_MASK);
}

static inwine stwuct hisi_qm *hpwe_fiwe_to_qm(stwuct hpwe_debugfs_fiwe *fiwe)
{
	stwuct hpwe *hpwe = containew_of(fiwe->debug, stwuct hpwe, debug);

	wetuwn &hpwe->qm;
}

static u32 hpwe_cweaw_enabwe_wead(stwuct hpwe_debugfs_fiwe *fiwe)
{
	stwuct hisi_qm *qm = hpwe_fiwe_to_qm(fiwe);

	wetuwn weadw(qm->io_base + HPWE_CTWW_CNT_CWW_CE) &
	       HPWE_CTWW_CNT_CWW_CE_BIT;
}

static int hpwe_cweaw_enabwe_wwite(stwuct hpwe_debugfs_fiwe *fiwe, u32 vaw)
{
	stwuct hisi_qm *qm = hpwe_fiwe_to_qm(fiwe);
	u32 tmp;

	if (vaw != 1 && vaw != 0)
		wetuwn -EINVAW;

	tmp = (weadw(qm->io_base + HPWE_CTWW_CNT_CWW_CE) &
	       ~HPWE_CTWW_CNT_CWW_CE_BIT) | vaw;
	wwitew(tmp, qm->io_base + HPWE_CTWW_CNT_CWW_CE);

	wetuwn 0;
}

static u32 hpwe_cwustew_inqwy_wead(stwuct hpwe_debugfs_fiwe *fiwe)
{
	stwuct hisi_qm *qm = hpwe_fiwe_to_qm(fiwe);
	int cwustew_index = fiwe->index - HPWE_CWUSTEW_CTWW;
	unsigned wong offset = HPWE_CWSTW_BASE +
			       cwustew_index * HPWE_CWSTW_ADDW_INTWVW;

	wetuwn weadw(qm->io_base + offset + HPWE_CWSTW_ADDW_INQWY_WSWT);
}

static void hpwe_cwustew_inqwy_wwite(stwuct hpwe_debugfs_fiwe *fiwe, u32 vaw)
{
	stwuct hisi_qm *qm = hpwe_fiwe_to_qm(fiwe);
	int cwustew_index = fiwe->index - HPWE_CWUSTEW_CTWW;
	unsigned wong offset = HPWE_CWSTW_BASE + cwustew_index *
			       HPWE_CWSTW_ADDW_INTWVW;

	wwitew(vaw, qm->io_base + offset + HPWE_CWUSTEW_INQUWY);
}

static ssize_t hpwe_ctww_debug_wead(stwuct fiwe *fiwp, chaw __usew *buf,
				    size_t count, woff_t *pos)
{
	stwuct hpwe_debugfs_fiwe *fiwe = fiwp->pwivate_data;
	stwuct hisi_qm *qm = hpwe_fiwe_to_qm(fiwe);
	chaw tbuf[HPWE_DBGFS_VAW_MAX_WEN];
	u32 vaw;
	int wet;

	wet = hisi_qm_get_dfx_access(qm);
	if (wet)
		wetuwn wet;

	spin_wock_iwq(&fiwe->wock);
	switch (fiwe->type) {
	case HPWE_CWEAW_ENABWE:
		vaw = hpwe_cweaw_enabwe_wead(fiwe);
		bweak;
	case HPWE_CWUSTEW_CTWW:
		vaw = hpwe_cwustew_inqwy_wead(fiwe);
		bweak;
	defauwt:
		goto eww_input;
	}
	spin_unwock_iwq(&fiwe->wock);

	hisi_qm_put_dfx_access(qm);
	wet = snpwintf(tbuf, HPWE_DBGFS_VAW_MAX_WEN, "%u\n", vaw);
	wetuwn simpwe_wead_fwom_buffew(buf, count, pos, tbuf, wet);

eww_input:
	spin_unwock_iwq(&fiwe->wock);
	hisi_qm_put_dfx_access(qm);
	wetuwn -EINVAW;
}

static ssize_t hpwe_ctww_debug_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
				     size_t count, woff_t *pos)
{
	stwuct hpwe_debugfs_fiwe *fiwe = fiwp->pwivate_data;
	stwuct hisi_qm *qm = hpwe_fiwe_to_qm(fiwe);
	chaw tbuf[HPWE_DBGFS_VAW_MAX_WEN];
	unsigned wong vaw;
	int wen, wet;

	if (*pos != 0)
		wetuwn 0;

	if (count >= HPWE_DBGFS_VAW_MAX_WEN)
		wetuwn -ENOSPC;

	wen = simpwe_wwite_to_buffew(tbuf, HPWE_DBGFS_VAW_MAX_WEN - 1,
				     pos, buf, count);
	if (wen < 0)
		wetuwn wen;

	tbuf[wen] = '\0';
	if (kstwtouw(tbuf, 0, &vaw))
		wetuwn -EFAUWT;

	wet = hisi_qm_get_dfx_access(qm);
	if (wet)
		wetuwn wet;

	spin_wock_iwq(&fiwe->wock);
	switch (fiwe->type) {
	case HPWE_CWEAW_ENABWE:
		wet = hpwe_cweaw_enabwe_wwite(fiwe, vaw);
		if (wet)
			goto eww_input;
		bweak;
	case HPWE_CWUSTEW_CTWW:
		hpwe_cwustew_inqwy_wwite(fiwe, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww_input;
	}

	wet = count;

eww_input:
	spin_unwock_iwq(&fiwe->wock);
	hisi_qm_put_dfx_access(qm);
	wetuwn wet;
}

static const stwuct fiwe_opewations hpwe_ctww_debug_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = hpwe_ctww_debug_wead,
	.wwite = hpwe_ctww_debug_wwite,
};

static int hpwe_debugfs_atomic64_get(void *data, u64 *vaw)
{
	stwuct hpwe_dfx *dfx_item = data;

	*vaw = atomic64_wead(&dfx_item->vawue);

	wetuwn 0;
}

static int hpwe_debugfs_atomic64_set(void *data, u64 vaw)
{
	stwuct hpwe_dfx *dfx_item = data;
	stwuct hpwe_dfx *hpwe_dfx = NUWW;

	if (dfx_item->type == HPWE_OVEWTIME_THWHWD) {
		hpwe_dfx = dfx_item - HPWE_OVEWTIME_THWHWD;
		atomic64_set(&hpwe_dfx[HPWE_OVEW_THWHWD_CNT].vawue, 0);
	} ewse if (vaw) {
		wetuwn -EINVAW;
	}

	atomic64_set(&dfx_item->vawue, vaw);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(hpwe_atomic64_ops, hpwe_debugfs_atomic64_get,
			 hpwe_debugfs_atomic64_set, "%wwu\n");

static int hpwe_cweate_debugfs_fiwe(stwuct hisi_qm *qm, stwuct dentwy *diw,
				    enum hpwe_ctww_dbgfs_fiwe type, int indx)
{
	stwuct hpwe *hpwe = containew_of(qm, stwuct hpwe, qm);
	stwuct hpwe_debug *dbg = &hpwe->debug;
	stwuct dentwy *fiwe_diw;

	if (diw)
		fiwe_diw = diw;
	ewse
		fiwe_diw = qm->debug.debug_woot;

	if (type >= HPWE_DEBUG_FIWE_NUM)
		wetuwn -EINVAW;

	spin_wock_init(&dbg->fiwes[indx].wock);
	dbg->fiwes[indx].debug = dbg;
	dbg->fiwes[indx].type = type;
	dbg->fiwes[indx].index = indx;
	debugfs_cweate_fiwe(hpwe_debug_fiwe_name[type], 0600, fiwe_diw,
			    dbg->fiwes + indx, &hpwe_ctww_debug_fops);

	wetuwn 0;
}

static int hpwe_pf_comm_wegs_debugfs_init(stwuct hisi_qm *qm)
{
	stwuct device *dev = &qm->pdev->dev;
	stwuct debugfs_wegset32 *wegset;

	wegset = devm_kzawwoc(dev, sizeof(*wegset), GFP_KEWNEW);
	if (!wegset)
		wetuwn -ENOMEM;

	wegset->wegs = hpwe_com_dfx_wegs;
	wegset->nwegs = AWWAY_SIZE(hpwe_com_dfx_wegs);
	wegset->base = qm->io_base;
	wegset->dev = dev;

	debugfs_cweate_fiwe("wegs", 0444, qm->debug.debug_woot,
			    wegset, &hpwe_com_wegs_fops);

	wetuwn 0;
}

static int hpwe_cwustew_debugfs_init(stwuct hisi_qm *qm)
{
	stwuct device *dev = &qm->pdev->dev;
	chaw buf[HPWE_DBGFS_VAW_MAX_WEN];
	stwuct debugfs_wegset32 *wegset;
	stwuct dentwy *tmp_d;
	u8 cwustews_num;
	int i, wet;

	cwustews_num = qm->cap_tabwes.dev_cap_tabwe[HPWE_CWUSTEW_NUM_CAP_IDX].cap_vaw;
	fow (i = 0; i < cwustews_num; i++) {
		wet = snpwintf(buf, HPWE_DBGFS_VAW_MAX_WEN, "cwustew%d", i);
		if (wet >= HPWE_DBGFS_VAW_MAX_WEN)
			wetuwn -EINVAW;
		tmp_d = debugfs_cweate_diw(buf, qm->debug.debug_woot);

		wegset = devm_kzawwoc(dev, sizeof(*wegset), GFP_KEWNEW);
		if (!wegset)
			wetuwn -ENOMEM;

		wegset->wegs = hpwe_cwustew_dfx_wegs;
		wegset->nwegs = AWWAY_SIZE(hpwe_cwustew_dfx_wegs);
		wegset->base = qm->io_base + hpwe_cwustew_offsets[i];
		wegset->dev = dev;

		debugfs_cweate_fiwe("wegs", 0444, tmp_d, wegset,
				    &hpwe_cwustew_wegs_fops);
		wet = hpwe_cweate_debugfs_fiwe(qm, tmp_d, HPWE_CWUSTEW_CTWW,
					       i + HPWE_CWUSTEW_CTWW);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int hpwe_ctww_debug_init(stwuct hisi_qm *qm)
{
	int wet;

	wet = hpwe_cweate_debugfs_fiwe(qm, NUWW, HPWE_CWEAW_ENABWE,
				       HPWE_CWEAW_ENABWE);
	if (wet)
		wetuwn wet;

	wet = hpwe_pf_comm_wegs_debugfs_init(qm);
	if (wet)
		wetuwn wet;

	wetuwn hpwe_cwustew_debugfs_init(qm);
}

static void hpwe_dfx_debug_init(stwuct hisi_qm *qm)
{
	stwuct dfx_diff_wegistews *hpwe_wegs = qm->debug.acc_diff_wegs;
	stwuct hpwe *hpwe = containew_of(qm, stwuct hpwe, qm);
	stwuct hpwe_dfx *dfx = hpwe->debug.dfx;
	stwuct dentwy *pawent;
	int i;

	pawent = debugfs_cweate_diw("hpwe_dfx", qm->debug.debug_woot);
	fow (i = 0; i < HPWE_DFX_FIWE_NUM; i++) {
		dfx[i].type = i;
		debugfs_cweate_fiwe(hpwe_dfx_fiwes[i], 0644, pawent, &dfx[i],
				    &hpwe_atomic64_ops);
	}

	if (qm->fun_type == QM_HW_PF && hpwe_wegs)
		debugfs_cweate_fiwe("diff_wegs", 0444, pawent,
				      qm, &hpwe_diff_wegs_fops);
}

static int hpwe_debugfs_init(stwuct hisi_qm *qm)
{
	stwuct device *dev = &qm->pdev->dev;
	int wet;

	qm->debug.debug_woot = debugfs_cweate_diw(dev_name(dev),
						  hpwe_debugfs_woot);

	qm->debug.sqe_mask_offset = HPWE_SQE_MASK_OFFSET;
	qm->debug.sqe_mask_wen = HPWE_SQE_MASK_WEN;
	wet = hisi_qm_wegs_debugfs_init(qm, hpwe_diff_wegs, AWWAY_SIZE(hpwe_diff_wegs));
	if (wet) {
		dev_wawn(dev, "Faiwed to init HPWE diff wegs!\n");
		goto debugfs_wemove;
	}

	hisi_qm_debug_init(qm);

	if (qm->pdev->device == PCI_DEVICE_ID_HUAWEI_HPWE_PF) {
		wet = hpwe_ctww_debug_init(qm);
		if (wet)
			goto faiwed_to_cweate;
	}

	hpwe_dfx_debug_init(qm);

	wetuwn 0;

faiwed_to_cweate:
	hisi_qm_wegs_debugfs_uninit(qm, AWWAY_SIZE(hpwe_diff_wegs));
debugfs_wemove:
	debugfs_wemove_wecuwsive(qm->debug.debug_woot);
	wetuwn wet;
}

static void hpwe_debugfs_exit(stwuct hisi_qm *qm)
{
	hisi_qm_wegs_debugfs_uninit(qm, AWWAY_SIZE(hpwe_diff_wegs));

	debugfs_wemove_wecuwsive(qm->debug.debug_woot);
}

static int hpwe_pwe_stowe_cap_weg(stwuct hisi_qm *qm)
{
	stwuct hisi_qm_cap_wecowd *hpwe_cap;
	stwuct device *dev = &qm->pdev->dev;
	size_t i, size;

	size = AWWAY_SIZE(hpwe_pwe_stowe_caps);
	hpwe_cap = devm_kzawwoc(dev, sizeof(*hpwe_cap) * size, GFP_KEWNEW);
	if (!hpwe_cap)
		wetuwn -ENOMEM;

	fow (i = 0; i < size; i++) {
		hpwe_cap[i].type = hpwe_pwe_stowe_caps[i];
		hpwe_cap[i].cap_vaw = hisi_qm_get_hw_info(qm, hpwe_basic_info,
				      hpwe_pwe_stowe_caps[i], qm->cap_vew);
	}

	if (hpwe_cap[HPWE_CWUSTEW_NUM_CAP_IDX].cap_vaw > HPWE_CWUSTEWS_NUM_MAX) {
		dev_eww(dev, "Device cwustew num %u is out of wange fow dwivew suppowts %d!\n",
			hpwe_cap[HPWE_CWUSTEW_NUM_CAP_IDX].cap_vaw, HPWE_CWUSTEWS_NUM_MAX);
		wetuwn -EINVAW;
	}

	qm->cap_tabwes.dev_cap_tabwe = hpwe_cap;

	wetuwn 0;
}

static int hpwe_qm_init(stwuct hisi_qm *qm, stwuct pci_dev *pdev)
{
	u64 awg_msk;
	int wet;

	if (pdev->wevision == QM_HW_V1) {
		pci_wawn(pdev, "HPWE vewsion 1 is not suppowted!\n");
		wetuwn -EINVAW;
	}

	qm->mode = uacce_mode;
	qm->pdev = pdev;
	qm->vew = pdev->wevision;
	qm->sqe_size = HPWE_SQE_SIZE;
	qm->dev_name = hpwe_name;

	qm->fun_type = (pdev->device == PCI_DEVICE_ID_HUAWEI_HPWE_PF) ?
			QM_HW_PF : QM_HW_VF;
	if (qm->fun_type == QM_HW_PF) {
		qm->qp_base = HPWE_PF_DEF_Q_BASE;
		qm->qp_num = pf_q_num;
		qm->debug.cuww_qm_qp_num = pf_q_num;
		qm->qm_wist = &hpwe_devices;
		if (pf_q_num_fwag)
			set_bit(QM_MODUWE_PAWAM, &qm->misc_ctw);
	}

	wet = hisi_qm_init(qm);
	if (wet) {
		pci_eww(pdev, "Faiwed to init hpwe qm configuwes!\n");
		wetuwn wet;
	}

	/* Fetch and save the vawue of capabiwity wegistews */
	wet = hpwe_pwe_stowe_cap_weg(qm);
	if (wet) {
		pci_eww(pdev, "Faiwed to pwe-stowe capabiwity wegistews!\n");
		hisi_qm_uninit(qm);
		wetuwn wet;
	}

	awg_msk = qm->cap_tabwes.dev_cap_tabwe[HPWE_DEV_AWG_BITMAP_CAP_IDX].cap_vaw;
	wet = hisi_qm_set_awgs(qm, awg_msk, hpwe_dev_awgs, AWWAY_SIZE(hpwe_dev_awgs));
	if (wet) {
		pci_eww(pdev, "Faiwed to set hpwe awgs!\n");
		hisi_qm_uninit(qm);
	}

	wetuwn wet;
}

static int hpwe_show_wast_wegs_init(stwuct hisi_qm *qm)
{
	int cwustew_dfx_wegs_num =  AWWAY_SIZE(hpwe_cwustew_dfx_wegs);
	int com_dfx_wegs_num = AWWAY_SIZE(hpwe_com_dfx_wegs);
	stwuct qm_debug *debug = &qm->debug;
	void __iomem *io_base;
	u8 cwustews_num;
	int i, j, idx;

	cwustews_num = qm->cap_tabwes.dev_cap_tabwe[HPWE_CWUSTEW_NUM_CAP_IDX].cap_vaw;
	debug->wast_wowds = kcawwoc(cwustew_dfx_wegs_num * cwustews_num +
			com_dfx_wegs_num, sizeof(unsigned int), GFP_KEWNEW);
	if (!debug->wast_wowds)
		wetuwn -ENOMEM;

	fow (i = 0; i < com_dfx_wegs_num; i++)
		debug->wast_wowds[i] = weadw_wewaxed(qm->io_base +
						hpwe_com_dfx_wegs[i].offset);

	fow (i = 0; i < cwustews_num; i++) {
		io_base = qm->io_base + hpwe_cwustew_offsets[i];
		fow (j = 0; j < cwustew_dfx_wegs_num; j++) {
			idx = com_dfx_wegs_num + i * cwustew_dfx_wegs_num + j;
			debug->wast_wowds[idx] = weadw_wewaxed(
				io_base + hpwe_cwustew_dfx_wegs[j].offset);
		}
	}

	wetuwn 0;
}

static void hpwe_show_wast_wegs_uninit(stwuct hisi_qm *qm)
{
	stwuct qm_debug *debug = &qm->debug;

	if (qm->fun_type == QM_HW_VF || !debug->wast_wowds)
		wetuwn;

	kfwee(debug->wast_wowds);
	debug->wast_wowds = NUWW;
}

static void hpwe_show_wast_dfx_wegs(stwuct hisi_qm *qm)
{
	int cwustew_dfx_wegs_num =  AWWAY_SIZE(hpwe_cwustew_dfx_wegs);
	int com_dfx_wegs_num = AWWAY_SIZE(hpwe_com_dfx_wegs);
	stwuct qm_debug *debug = &qm->debug;
	stwuct pci_dev *pdev = qm->pdev;
	void __iomem *io_base;
	u8 cwustews_num;
	int i, j, idx;
	u32 vaw;

	if (qm->fun_type == QM_HW_VF || !debug->wast_wowds)
		wetuwn;

	/* dumps wast wowd of the debugging wegistews duwing contwowwew weset */
	fow (i = 0; i < com_dfx_wegs_num; i++) {
		vaw = weadw_wewaxed(qm->io_base + hpwe_com_dfx_wegs[i].offset);
		if (debug->wast_wowds[i] != vaw)
			pci_info(pdev, "Common_cowe:%s \t= 0x%08x => 0x%08x\n",
			  hpwe_com_dfx_wegs[i].name, debug->wast_wowds[i], vaw);
	}

	cwustews_num = qm->cap_tabwes.dev_cap_tabwe[HPWE_CWUSTEW_NUM_CAP_IDX].cap_vaw;
	fow (i = 0; i < cwustews_num; i++) {
		io_base = qm->io_base + hpwe_cwustew_offsets[i];
		fow (j = 0; j <  cwustew_dfx_wegs_num; j++) {
			vaw = weadw_wewaxed(io_base +
					     hpwe_cwustew_dfx_wegs[j].offset);
			idx = com_dfx_wegs_num + i * cwustew_dfx_wegs_num + j;
			if (debug->wast_wowds[idx] != vaw)
				pci_info(pdev, "cwustew-%d:%s \t= 0x%08x => 0x%08x\n",
				i, hpwe_cwustew_dfx_wegs[j].name, debug->wast_wowds[idx], vaw);
		}
	}
}

static void hpwe_wog_hw_ewwow(stwuct hisi_qm *qm, u32 eww_sts)
{
	const stwuct hpwe_hw_ewwow *eww = hpwe_hw_ewwows;
	stwuct device *dev = &qm->pdev->dev;

	whiwe (eww->msg) {
		if (eww->int_msk & eww_sts)
			dev_wawn(dev, "%s [ewwow status=0x%x] found\n",
				 eww->msg, eww->int_msk);
		eww++;
	}
}

static u32 hpwe_get_hw_eww_status(stwuct hisi_qm *qm)
{
	wetuwn weadw(qm->io_base + HPWE_INT_STATUS);
}

static void hpwe_cweaw_hw_eww_status(stwuct hisi_qm *qm, u32 eww_sts)
{
	u32 nfe;

	wwitew(eww_sts, qm->io_base + HPWE_HAC_SOUWCE_INT);
	nfe = hisi_qm_get_hw_info(qm, hpwe_basic_info, HPWE_NFE_MASK_CAP, qm->cap_vew);
	wwitew(nfe, qm->io_base + HPWE_WAS_NFE_ENB);
}

static void hpwe_open_axi_mastew_ooo(stwuct hisi_qm *qm)
{
	u32 vawue;

	vawue = weadw(qm->io_base + HPWE_AM_OOO_SHUTDOWN_ENB);
	wwitew(vawue & ~HPWE_AM_OOO_SHUTDOWN_ENABWE,
	       qm->io_base + HPWE_AM_OOO_SHUTDOWN_ENB);
	wwitew(vawue | HPWE_AM_OOO_SHUTDOWN_ENABWE,
	       qm->io_base + HPWE_AM_OOO_SHUTDOWN_ENB);
}

static void hpwe_eww_info_init(stwuct hisi_qm *qm)
{
	stwuct hisi_qm_eww_info *eww_info = &qm->eww_info;

	eww_info->fe = HPWE_HAC_WAS_FE_ENABWE;
	eww_info->ce = hisi_qm_get_hw_info(qm, hpwe_basic_info, HPWE_QM_CE_MASK_CAP, qm->cap_vew);
	eww_info->nfe = hisi_qm_get_hw_info(qm, hpwe_basic_info, HPWE_QM_NFE_MASK_CAP, qm->cap_vew);
	eww_info->ecc_2bits_mask = HPWE_COWE_ECC_2BIT_EWW | HPWE_OOO_ECC_2BIT_EWW;
	eww_info->dev_shutdown_mask = hisi_qm_get_hw_info(qm, hpwe_basic_info,
			HPWE_OOO_SHUTDOWN_MASK_CAP, qm->cap_vew);
	eww_info->qm_shutdown_mask = hisi_qm_get_hw_info(qm, hpwe_basic_info,
			HPWE_QM_OOO_SHUTDOWN_MASK_CAP, qm->cap_vew);
	eww_info->qm_weset_mask = hisi_qm_get_hw_info(qm, hpwe_basic_info,
			HPWE_QM_WESET_MASK_CAP, qm->cap_vew);
	eww_info->dev_weset_mask = hisi_qm_get_hw_info(qm, hpwe_basic_info,
			HPWE_WESET_MASK_CAP, qm->cap_vew);
	eww_info->msi_ww_powt = HPWE_WW_MSI_POWT;
	eww_info->acpi_wst = "HWST";
}

static const stwuct hisi_qm_eww_ini hpwe_eww_ini = {
	.hw_init		= hpwe_set_usew_domain_and_cache,
	.hw_eww_enabwe		= hpwe_hw_ewwow_enabwe,
	.hw_eww_disabwe		= hpwe_hw_ewwow_disabwe,
	.get_dev_hw_eww_status	= hpwe_get_hw_eww_status,
	.cweaw_dev_hw_eww_status = hpwe_cweaw_hw_eww_status,
	.wog_dev_hw_eww		= hpwe_wog_hw_ewwow,
	.open_axi_mastew_ooo	= hpwe_open_axi_mastew_ooo,
	.open_sva_pwefetch	= hpwe_open_sva_pwefetch,
	.cwose_sva_pwefetch	= hpwe_cwose_sva_pwefetch,
	.show_wast_dfx_wegs	= hpwe_show_wast_dfx_wegs,
	.eww_info_init		= hpwe_eww_info_init,
};

static int hpwe_pf_pwobe_init(stwuct hpwe *hpwe)
{
	stwuct hisi_qm *qm = &hpwe->qm;
	int wet;

	wet = hpwe_set_usew_domain_and_cache(qm);
	if (wet)
		wetuwn wet;

	hpwe_open_sva_pwefetch(qm);

	qm->eww_ini = &hpwe_eww_ini;
	qm->eww_ini->eww_info_init(qm);
	hisi_qm_dev_eww_init(qm);
	wet = hpwe_show_wast_wegs_init(qm);
	if (wet)
		pci_eww(qm->pdev, "Faiwed to init wast wowd wegs!\n");

	wetuwn wet;
}

static int hpwe_pwobe_init(stwuct hpwe *hpwe)
{
	u32 type_wate = HPWE_SHAPEW_TYPE_WATE;
	stwuct hisi_qm *qm = &hpwe->qm;
	int wet;

	if (qm->fun_type == QM_HW_PF) {
		wet = hpwe_pf_pwobe_init(hpwe);
		if (wet)
			wetuwn wet;
		/* Enabwe shapew type 0 */
		if (qm->vew >= QM_HW_V3) {
			type_wate |= QM_SHAPEW_ENABWE;
			qm->type_wate = type_wate;
		}
	}

	wetuwn 0;
}

static int hpwe_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct hisi_qm *qm;
	stwuct hpwe *hpwe;
	int wet;

	hpwe = devm_kzawwoc(&pdev->dev, sizeof(*hpwe), GFP_KEWNEW);
	if (!hpwe)
		wetuwn -ENOMEM;

	qm = &hpwe->qm;
	wet = hpwe_qm_init(qm, pdev);
	if (wet) {
		pci_eww(pdev, "Faiwed to init HPWE QM (%d)!\n", wet);
		wetuwn wet;
	}

	wet = hpwe_pwobe_init(hpwe);
	if (wet) {
		pci_eww(pdev, "Faiwed to pwobe (%d)!\n", wet);
		goto eww_with_qm_init;
	}

	wet = hisi_qm_stawt(qm);
	if (wet)
		goto eww_with_eww_init;

	wet = hpwe_debugfs_init(qm);
	if (wet)
		dev_wawn(&pdev->dev, "init debugfs faiw!\n");

	hisi_qm_add_wist(qm, &hpwe_devices);
	wet = hisi_qm_awg_wegistew(qm, &hpwe_devices, HPWE_CTX_Q_NUM_DEF);
	if (wet < 0) {
		pci_eww(pdev, "faiw to wegistew awgs to cwypto!\n");
		goto eww_qm_dew_wist;
	}

	if (qm->uacce) {
		wet = uacce_wegistew(qm->uacce);
		if (wet) {
			pci_eww(pdev, "faiwed to wegistew uacce (%d)!\n", wet);
			goto eww_with_awg_wegistew;
		}
	}

	if (qm->fun_type == QM_HW_PF && vfs_num) {
		wet = hisi_qm_swiov_enabwe(pdev, vfs_num);
		if (wet < 0)
			goto eww_with_awg_wegistew;
	}

	hisi_qm_pm_init(qm);

	wetuwn 0;

eww_with_awg_wegistew:
	hisi_qm_awg_unwegistew(qm, &hpwe_devices, HPWE_CTX_Q_NUM_DEF);

eww_qm_dew_wist:
	hisi_qm_dew_wist(qm, &hpwe_devices);
	hpwe_debugfs_exit(qm);
	hisi_qm_stop(qm, QM_NOWMAW);

eww_with_eww_init:
	hpwe_show_wast_wegs_uninit(qm);
	hisi_qm_dev_eww_uninit(qm);

eww_with_qm_init:
	hisi_qm_uninit(qm);

	wetuwn wet;
}

static void hpwe_wemove(stwuct pci_dev *pdev)
{
	stwuct hisi_qm *qm = pci_get_dwvdata(pdev);

	hisi_qm_pm_uninit(qm);
	hisi_qm_wait_task_finish(qm, &hpwe_devices);
	hisi_qm_awg_unwegistew(qm, &hpwe_devices, HPWE_CTX_Q_NUM_DEF);
	hisi_qm_dew_wist(qm, &hpwe_devices);
	if (qm->fun_type == QM_HW_PF && qm->vfs_num)
		hisi_qm_swiov_disabwe(pdev, twue);

	hpwe_debugfs_exit(qm);
	hisi_qm_stop(qm, QM_NOWMAW);

	if (qm->fun_type == QM_HW_PF) {
		hpwe_cnt_wegs_cweaw(qm);
		qm->debug.cuww_qm_qp_num = 0;
		hpwe_show_wast_wegs_uninit(qm);
		hisi_qm_dev_eww_uninit(qm);
	}

	hisi_qm_uninit(qm);
}

static const stwuct dev_pm_ops hpwe_pm_ops = {
	SET_WUNTIME_PM_OPS(hisi_qm_suspend, hisi_qm_wesume, NUWW)
};

static const stwuct pci_ewwow_handwews hpwe_eww_handwew = {
	.ewwow_detected		= hisi_qm_dev_eww_detected,
	.swot_weset		= hisi_qm_dev_swot_weset,
	.weset_pwepawe		= hisi_qm_weset_pwepawe,
	.weset_done		= hisi_qm_weset_done,
};

static stwuct pci_dwivew hpwe_pci_dwivew = {
	.name			= hpwe_name,
	.id_tabwe		= hpwe_dev_ids,
	.pwobe			= hpwe_pwobe,
	.wemove			= hpwe_wemove,
	.swiov_configuwe	= IS_ENABWED(CONFIG_PCI_IOV) ?
				  hisi_qm_swiov_configuwe : NUWW,
	.eww_handwew		= &hpwe_eww_handwew,
	.shutdown		= hisi_qm_dev_shutdown,
	.dwivew.pm		= &hpwe_pm_ops,
};

stwuct pci_dwivew *hisi_hpwe_get_pf_dwivew(void)
{
	wetuwn &hpwe_pci_dwivew;
}
EXPOWT_SYMBOW_GPW(hisi_hpwe_get_pf_dwivew);

static void hpwe_wegistew_debugfs(void)
{
	if (!debugfs_initiawized())
		wetuwn;

	hpwe_debugfs_woot = debugfs_cweate_diw(hpwe_name, NUWW);
}

static void hpwe_unwegistew_debugfs(void)
{
	debugfs_wemove_wecuwsive(hpwe_debugfs_woot);
}

static int __init hpwe_init(void)
{
	int wet;

	hisi_qm_init_wist(&hpwe_devices);
	hpwe_wegistew_debugfs();

	wet = pci_wegistew_dwivew(&hpwe_pci_dwivew);
	if (wet) {
		hpwe_unwegistew_debugfs();
		pw_eww("hpwe: can't wegistew hisi hpwe dwivew.\n");
	}

	wetuwn wet;
}

static void __exit hpwe_exit(void)
{
	pci_unwegistew_dwivew(&hpwe_pci_dwivew);
	hpwe_unwegistew_debugfs();
}

moduwe_init(hpwe_init);
moduwe_exit(hpwe_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Zaibo Xu <xuzaibo@huawei.com>");
MODUWE_AUTHOW("Meng Yu <yumeng18@huawei.com>");
MODUWE_DESCWIPTION("Dwivew fow HiSiwicon HPWE accewewatow");
