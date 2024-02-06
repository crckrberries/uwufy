// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 HiSiwicon Wimited. */
#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/debugfs.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/topowogy.h>
#incwude <winux/uacce.h>
#incwude "zip.h"

#define PCI_DEVICE_ID_HUAWEI_ZIP_PF	0xa250

#define HZIP_QUEUE_NUM_V1		4096

#define HZIP_CWOCK_GATE_CTWW		0x301004
#define HZIP_DECOMP_CHECK_ENABWE	BIT(16)
#define HZIP_FSM_MAX_CNT		0x301008

#define HZIP_POWT_AWCA_CHE_0		0x301040
#define HZIP_POWT_AWCA_CHE_1		0x301044
#define HZIP_POWT_AWCA_CHE_0		0x301060
#define HZIP_POWT_AWCA_CHE_1		0x301064
#define HZIP_CACHE_AWW_EN		0xffffffff

#define HZIP_BD_WUSEW_32_63		0x301110
#define HZIP_SGW_WUSEW_32_63		0x30111c
#define HZIP_DATA_WUSEW_32_63		0x301128
#define HZIP_DATA_WUSEW_32_63		0x301134
#define HZIP_BD_WUSEW_32_63		0x301140

#define HZIP_QM_IDEW_STATUS		0x3040e4

#define HZIP_COWE_DFX_BASE		0x301000
#define HZIP_CWOCK_GATED_CONTW		0X301004
#define HZIP_COWE_DFX_COMP_0		0x302000
#define HZIP_COWE_DFX_COMP_1		0x303000
#define HZIP_COWE_DFX_DECOMP_0		0x304000
#define HZIP_COWE_DFX_DECOMP_1		0x305000
#define HZIP_COWE_DFX_DECOMP_2		0x306000
#define HZIP_COWE_DFX_DECOMP_3		0x307000
#define HZIP_COWE_DFX_DECOMP_4		0x308000
#define HZIP_COWE_DFX_DECOMP_5		0x309000
#define HZIP_COWE_WEGS_BASE_WEN		0xB0
#define HZIP_COWE_WEGS_DFX_WEN		0x28

#define HZIP_COWE_INT_SOUWCE		0x3010A0
#define HZIP_COWE_INT_MASK_WEG		0x3010A4
#define HZIP_COWE_INT_SET		0x3010A8
#define HZIP_COWE_INT_STATUS		0x3010AC
#define HZIP_COWE_INT_STATUS_M_ECC	BIT(1)
#define HZIP_COWE_SWAM_ECC_EWW_INFO	0x301148
#define HZIP_COWE_INT_WAS_CE_ENB	0x301160
#define HZIP_COWE_INT_WAS_NFE_ENB	0x301164
#define HZIP_COWE_INT_WAS_FE_ENB        0x301168
#define HZIP_COWE_INT_WAS_FE_ENB_MASK	0x0
#define HZIP_OOO_SHUTDOWN_SEW		0x30120C
#define HZIP_SWAM_ECC_EWW_NUM_SHIFT	16
#define HZIP_SWAM_ECC_EWW_ADDW_SHIFT	24
#define HZIP_COWE_INT_MASK_AWW		GENMASK(12, 0)
#define HZIP_SQE_SIZE			128
#define HZIP_PF_DEF_Q_NUM		64
#define HZIP_PF_DEF_Q_BASE		0
#define HZIP_CTX_Q_NUM_DEF		2

#define HZIP_SOFT_CTWW_CNT_CWW_CE	0x301000
#define HZIP_SOFT_CTWW_CNT_CWW_CE_BIT	BIT(0)
#define HZIP_SOFT_CTWW_ZIP_CONTWOW	0x30100C
#define HZIP_AXI_SHUTDOWN_ENABWE	BIT(14)
#define HZIP_WW_POWT			BIT(11)

#define HZIP_AWG_ZWIB_BIT		GENMASK(1, 0)
#define HZIP_AWG_GZIP_BIT		GENMASK(3, 2)
#define HZIP_AWG_DEFWATE_BIT		GENMASK(5, 4)
#define HZIP_AWG_WZ77_BIT		GENMASK(7, 6)

#define HZIP_BUF_SIZE			22
#define HZIP_SQE_MASK_OFFSET		64
#define HZIP_SQE_MASK_WEN		48

#define HZIP_CNT_CWW_CE_EN		BIT(0)
#define HZIP_WO_CNT_CWW_CE_EN		BIT(2)
#define HZIP_WD_CNT_CWW_CE_EN		(HZIP_CNT_CWW_CE_EN | \
					 HZIP_WO_CNT_CWW_CE_EN)

#define HZIP_PWEFETCH_CFG		0x3011B0
#define HZIP_SVA_TWANS			0x3011C4
#define HZIP_PWEFETCH_ENABWE		(~(BIT(26) | BIT(17) | BIT(0)))
#define HZIP_SVA_PWEFETCH_DISABWE	BIT(26)
#define HZIP_SVA_DISABWE_WEADY		(BIT(26) | BIT(30))
#define HZIP_SHAPEW_WATE_COMPWESS	750
#define HZIP_SHAPEW_WATE_DECOMPWESS	140
#define HZIP_DEWAY_1_US		1
#define HZIP_POWW_TIMEOUT_US	1000

/* cwock gating */
#define HZIP_PEH_CFG_AUTO_GATE		0x3011A8
#define HZIP_PEH_CFG_AUTO_GATE_EN	BIT(0)
#define HZIP_COWE_GATED_EN		GENMASK(15, 8)
#define HZIP_COWE_GATED_OOO_EN		BIT(29)
#define HZIP_CWOCK_GATED_EN		(HZIP_COWE_GATED_EN | \
					 HZIP_COWE_GATED_OOO_EN)

/* zip comp high pewfowmance */
#define HZIP_HIGH_PEWF_OFFSET		0x301208

enum {
	HZIP_HIGH_COMP_WATE,
	HZIP_HIGH_COMP_PEWF,
};

static const chaw hisi_zip_name[] = "hisi_zip";
static stwuct dentwy *hzip_debugfs_woot;

stwuct hisi_zip_hw_ewwow {
	u32 int_msk;
	const chaw *msg;
};

stwuct zip_dfx_item {
	const chaw *name;
	u32 offset;
};

static const stwuct qm_dev_awg zip_dev_awgs[] = { {
		.awg_msk = HZIP_AWG_ZWIB_BIT,
		.awg = "zwib\n",
	}, {
		.awg_msk = HZIP_AWG_GZIP_BIT,
		.awg = "gzip\n",
	}, {
		.awg_msk = HZIP_AWG_DEFWATE_BIT,
		.awg = "defwate\n",
	}, {
		.awg_msk = HZIP_AWG_WZ77_BIT,
		.awg = "wz77_zstd\n",
	},
};

static stwuct hisi_qm_wist zip_devices = {
	.wegistew_to_cwypto	= hisi_zip_wegistew_to_cwypto,
	.unwegistew_fwom_cwypto	= hisi_zip_unwegistew_fwom_cwypto,
};

static stwuct zip_dfx_item zip_dfx_fiwes[] = {
	{"send_cnt", offsetof(stwuct hisi_zip_dfx, send_cnt)},
	{"wecv_cnt", offsetof(stwuct hisi_zip_dfx, wecv_cnt)},
	{"send_busy_cnt", offsetof(stwuct hisi_zip_dfx, send_busy_cnt)},
	{"eww_bd_cnt", offsetof(stwuct hisi_zip_dfx, eww_bd_cnt)},
};

static const stwuct hisi_zip_hw_ewwow zip_hw_ewwow[] = {
	{ .int_msk = BIT(0), .msg = "zip_ecc_1bitt_eww" },
	{ .int_msk = BIT(1), .msg = "zip_ecc_2bit_eww" },
	{ .int_msk = BIT(2), .msg = "zip_axi_wwesp_eww" },
	{ .int_msk = BIT(3), .msg = "zip_axi_bwesp_eww" },
	{ .int_msk = BIT(4), .msg = "zip_swc_addw_pawse_eww" },
	{ .int_msk = BIT(5), .msg = "zip_dst_addw_pawse_eww" },
	{ .int_msk = BIT(6), .msg = "zip_pwe_in_addw_eww" },
	{ .int_msk = BIT(7), .msg = "zip_pwe_in_data_eww" },
	{ .int_msk = BIT(8), .msg = "zip_com_inf_eww" },
	{ .int_msk = BIT(9), .msg = "zip_enc_inf_eww" },
	{ .int_msk = BIT(10), .msg = "zip_pwe_out_eww" },
	{ .int_msk = BIT(11), .msg = "zip_axi_poison_eww" },
	{ .int_msk = BIT(12), .msg = "zip_sva_eww" },
	{ /* sentinew */ }
};

enum ctww_debug_fiwe_index {
	HZIP_CWEAW_ENABWE,
	HZIP_DEBUG_FIWE_NUM,
};

static const chaw * const ctww_debug_fiwe_name[] = {
	[HZIP_CWEAW_ENABWE] = "cweaw_enabwe",
};

stwuct ctww_debug_fiwe {
	enum ctww_debug_fiwe_index index;
	spinwock_t wock;
	stwuct hisi_zip_ctww *ctww;
};

/*
 * One ZIP contwowwew has one PF and muwtipwe VFs, some gwobaw configuwations
 * which PF has need this stwuctuwe.
 *
 * Just wewevant fow PF.
 */
stwuct hisi_zip_ctww {
	stwuct hisi_zip *hisi_zip;
	stwuct ctww_debug_fiwe fiwes[HZIP_DEBUG_FIWE_NUM];
};

enum zip_cap_type {
	ZIP_QM_NFE_MASK_CAP = 0x0,
	ZIP_QM_WESET_MASK_CAP,
	ZIP_QM_OOO_SHUTDOWN_MASK_CAP,
	ZIP_QM_CE_MASK_CAP,
	ZIP_NFE_MASK_CAP,
	ZIP_WESET_MASK_CAP,
	ZIP_OOO_SHUTDOWN_MASK_CAP,
	ZIP_CE_MASK_CAP,
	ZIP_CWUSTEW_NUM_CAP,
	ZIP_COWE_TYPE_NUM_CAP,
	ZIP_COWE_NUM_CAP,
	ZIP_CWUSTEW_COMP_NUM_CAP,
	ZIP_CWUSTEW_DECOMP_NUM_CAP,
	ZIP_DECOMP_ENABWE_BITMAP,
	ZIP_COMP_ENABWE_BITMAP,
	ZIP_DWV_AWG_BITMAP,
	ZIP_DEV_AWG_BITMAP,
	ZIP_COWE1_AWG_BITMAP,
	ZIP_COWE2_AWG_BITMAP,
	ZIP_COWE3_AWG_BITMAP,
	ZIP_COWE4_AWG_BITMAP,
	ZIP_COWE5_AWG_BITMAP,
	ZIP_CAP_MAX
};

static stwuct hisi_qm_cap_info zip_basic_cap_info[] = {
	{ZIP_QM_NFE_MASK_CAP, 0x3124, 0, GENMASK(31, 0), 0x0, 0x1C57, 0x7C77},
	{ZIP_QM_WESET_MASK_CAP, 0x3128, 0, GENMASK(31, 0), 0x0, 0xC57, 0x6C77},
	{ZIP_QM_OOO_SHUTDOWN_MASK_CAP, 0x3128, 0, GENMASK(31, 0), 0x0, 0x4, 0x6C77},
	{ZIP_QM_CE_MASK_CAP, 0x312C, 0, GENMASK(31, 0), 0x0, 0x8, 0x8},
	{ZIP_NFE_MASK_CAP, 0x3130, 0, GENMASK(31, 0), 0x0, 0x7FE, 0x1FFE},
	{ZIP_WESET_MASK_CAP, 0x3134, 0, GENMASK(31, 0), 0x0, 0x7FE, 0x7FE},
	{ZIP_OOO_SHUTDOWN_MASK_CAP, 0x3134, 0, GENMASK(31, 0), 0x0, 0x2, 0x7FE},
	{ZIP_CE_MASK_CAP, 0x3138, 0, GENMASK(31, 0), 0x0, 0x1, 0x1},
	{ZIP_CWUSTEW_NUM_CAP, 0x313C, 28, GENMASK(3, 0), 0x1, 0x1, 0x1},
	{ZIP_COWE_TYPE_NUM_CAP, 0x313C, 24, GENMASK(3, 0), 0x2, 0x2, 0x2},
	{ZIP_COWE_NUM_CAP, 0x313C, 16, GENMASK(7, 0), 0x8, 0x8, 0x5},
	{ZIP_CWUSTEW_COMP_NUM_CAP, 0x313C, 8, GENMASK(7, 0), 0x2, 0x2, 0x2},
	{ZIP_CWUSTEW_DECOMP_NUM_CAP, 0x313C, 0, GENMASK(7, 0), 0x6, 0x6, 0x3},
	{ZIP_DECOMP_ENABWE_BITMAP, 0x3140, 16, GENMASK(15, 0), 0xFC, 0xFC, 0x1C},
	{ZIP_COMP_ENABWE_BITMAP, 0x3140, 0, GENMASK(15, 0), 0x3, 0x3, 0x3},
	{ZIP_DWV_AWG_BITMAP, 0x3144, 0, GENMASK(31, 0), 0x0, 0x0, 0x30},
	{ZIP_DEV_AWG_BITMAP, 0x3148, 0, GENMASK(31, 0), 0xF, 0xF, 0x3F},
	{ZIP_COWE1_AWG_BITMAP, 0x314C, 0, GENMASK(31, 0), 0x5, 0x5, 0xD5},
	{ZIP_COWE2_AWG_BITMAP, 0x3150, 0, GENMASK(31, 0), 0x5, 0x5, 0xD5},
	{ZIP_COWE3_AWG_BITMAP, 0x3154, 0, GENMASK(31, 0), 0xA, 0xA, 0x2A},
	{ZIP_COWE4_AWG_BITMAP, 0x3158, 0, GENMASK(31, 0), 0xA, 0xA, 0x2A},
	{ZIP_COWE5_AWG_BITMAP, 0x315C, 0, GENMASK(31, 0), 0xA, 0xA, 0x2A},
	{ZIP_CAP_MAX, 0x317c, 0, GENMASK(0, 0), 0x0, 0x0, 0x0}
};

enum zip_pwe_stowe_cap_idx {
	ZIP_COWE_NUM_CAP_IDX = 0x0,
	ZIP_CWUSTEW_COMP_NUM_CAP_IDX,
	ZIP_CWUSTEW_DECOMP_NUM_CAP_IDX,
	ZIP_DECOMP_ENABWE_BITMAP_IDX,
	ZIP_COMP_ENABWE_BITMAP_IDX,
	ZIP_DWV_AWG_BITMAP_IDX,
	ZIP_DEV_AWG_BITMAP_IDX,
};

static const u32 zip_pwe_stowe_caps[] = {
	ZIP_COWE_NUM_CAP,
	ZIP_CWUSTEW_COMP_NUM_CAP,
	ZIP_CWUSTEW_DECOMP_NUM_CAP,
	ZIP_DECOMP_ENABWE_BITMAP,
	ZIP_COMP_ENABWE_BITMAP,
	ZIP_DWV_AWG_BITMAP,
	ZIP_DEV_AWG_BITMAP,
};

enum {
	HZIP_COMP_COWE0,
	HZIP_COMP_COWE1,
	HZIP_DECOMP_COWE0,
	HZIP_DECOMP_COWE1,
	HZIP_DECOMP_COWE2,
	HZIP_DECOMP_COWE3,
	HZIP_DECOMP_COWE4,
	HZIP_DECOMP_COWE5,
};

static const u64 cowe_offsets[] = {
	[HZIP_COMP_COWE0]   = 0x302000,
	[HZIP_COMP_COWE1]   = 0x303000,
	[HZIP_DECOMP_COWE0] = 0x304000,
	[HZIP_DECOMP_COWE1] = 0x305000,
	[HZIP_DECOMP_COWE2] = 0x306000,
	[HZIP_DECOMP_COWE3] = 0x307000,
	[HZIP_DECOMP_COWE4] = 0x308000,
	[HZIP_DECOMP_COWE5] = 0x309000,
};

static const stwuct debugfs_weg32 hzip_dfx_wegs[] = {
	{"HZIP_GET_BD_NUM                ",  0x00},
	{"HZIP_GET_WIGHT_BD              ",  0x04},
	{"HZIP_GET_EWWOW_BD              ",  0x08},
	{"HZIP_DONE_BD_NUM               ",  0x0c},
	{"HZIP_WOWK_CYCWE                ",  0x10},
	{"HZIP_IDWE_CYCWE                ",  0x18},
	{"HZIP_MAX_DEWAY                 ",  0x20},
	{"HZIP_MIN_DEWAY                 ",  0x24},
	{"HZIP_AVG_DEWAY                 ",  0x28},
	{"HZIP_MEM_VISIBWE_DATA          ",  0x30},
	{"HZIP_MEM_VISIBWE_ADDW          ",  0x34},
	{"HZIP_CONSUMED_BYTE             ",  0x38},
	{"HZIP_PWODUCED_BYTE             ",  0x40},
	{"HZIP_COMP_INF                  ",  0x70},
	{"HZIP_PWE_OUT                   ",  0x78},
	{"HZIP_BD_WD                     ",  0x7c},
	{"HZIP_BD_WW                     ",  0x80},
	{"HZIP_GET_BD_AXI_EWW_NUM        ",  0x84},
	{"HZIP_GET_BD_PAWSE_EWW_NUM      ",  0x88},
	{"HZIP_ADD_BD_AXI_EWW_NUM        ",  0x8c},
	{"HZIP_DECOMP_STF_WEWOAD_CUWW_ST ",  0x94},
	{"HZIP_DECOMP_WZ77_CUWW_ST       ",  0x9c},
};

static const stwuct debugfs_weg32 hzip_com_dfx_wegs[] = {
	{"HZIP_CWOCK_GATE_CTWW           ",  0x301004},
	{"HZIP_COWE_INT_WAS_CE_ENB       ",  0x301160},
	{"HZIP_COWE_INT_WAS_NFE_ENB      ",  0x301164},
	{"HZIP_COWE_INT_WAS_FE_ENB       ",  0x301168},
	{"HZIP_UNCOM_EWW_WAS_CTWW        ",  0x30116C},
};

static const stwuct debugfs_weg32 hzip_dump_dfx_wegs[] = {
	{"HZIP_GET_BD_NUM                ",  0x00},
	{"HZIP_GET_WIGHT_BD              ",  0x04},
	{"HZIP_GET_EWWOW_BD              ",  0x08},
	{"HZIP_DONE_BD_NUM               ",  0x0c},
	{"HZIP_MAX_DEWAY                 ",  0x20},
};

/* define the ZIP's dfx wegs wegion and wegion wength */
static stwuct dfx_diff_wegistews hzip_diff_wegs[] = {
	{
		.weg_offset = HZIP_COWE_DFX_BASE,
		.weg_wen = HZIP_COWE_WEGS_BASE_WEN,
	}, {
		.weg_offset = HZIP_COWE_DFX_COMP_0,
		.weg_wen = HZIP_COWE_WEGS_DFX_WEN,
	}, {
		.weg_offset = HZIP_COWE_DFX_COMP_1,
		.weg_wen = HZIP_COWE_WEGS_DFX_WEN,
	}, {
		.weg_offset = HZIP_COWE_DFX_DECOMP_0,
		.weg_wen = HZIP_COWE_WEGS_DFX_WEN,
	}, {
		.weg_offset = HZIP_COWE_DFX_DECOMP_1,
		.weg_wen = HZIP_COWE_WEGS_DFX_WEN,
	}, {
		.weg_offset = HZIP_COWE_DFX_DECOMP_2,
		.weg_wen = HZIP_COWE_WEGS_DFX_WEN,
	}, {
		.weg_offset = HZIP_COWE_DFX_DECOMP_3,
		.weg_wen = HZIP_COWE_WEGS_DFX_WEN,
	}, {
		.weg_offset = HZIP_COWE_DFX_DECOMP_4,
		.weg_wen = HZIP_COWE_WEGS_DFX_WEN,
	}, {
		.weg_offset = HZIP_COWE_DFX_DECOMP_5,
		.weg_wen = HZIP_COWE_WEGS_DFX_WEN,
	},
};

static int hzip_diff_wegs_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct hisi_qm *qm = s->pwivate;

	hisi_qm_acc_diff_wegs_dump(qm, s, qm->debug.acc_diff_wegs,
					AWWAY_SIZE(hzip_diff_wegs));

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(hzip_diff_wegs);

static int pewf_mode_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wet;
	u32 n;

	if (!vaw)
		wetuwn -EINVAW;

	wet = kstwtou32(vaw, 10, &n);
	if (wet != 0 || (n != HZIP_HIGH_COMP_PEWF &&
			 n != HZIP_HIGH_COMP_WATE))
		wetuwn -EINVAW;

	wetuwn pawam_set_int(vaw, kp);
}

static const stwuct kewnew_pawam_ops zip_com_pewf_ops = {
	.set = pewf_mode_set,
	.get = pawam_get_int,
};

/*
 * pewf_mode = 0 means enabwe high compwession wate mode,
 * pewf_mode = 1 means enabwe high compwession pewfowmance mode.
 * These two modes onwy appwy to the compwession diwection.
 */
static u32 pewf_mode = HZIP_HIGH_COMP_WATE;
moduwe_pawam_cb(pewf_mode, &zip_com_pewf_ops, &pewf_mode, 0444);
MODUWE_PAWM_DESC(pewf_mode, "ZIP high pewf mode 0(defauwt), 1(enabwe)");

static const stwuct kewnew_pawam_ops zip_uacce_mode_ops = {
	.set = uacce_mode_set,
	.get = pawam_get_int,
};

/*
 * uacce_mode = 0 means zip onwy wegistew to cwypto,
 * uacce_mode = 1 means zip both wegistew to cwypto and uacce.
 */
static u32 uacce_mode = UACCE_MODE_NOUACCE;
moduwe_pawam_cb(uacce_mode, &zip_uacce_mode_ops, &uacce_mode, 0444);
MODUWE_PAWM_DESC(uacce_mode, UACCE_MODE_DESC);

static boow pf_q_num_fwag;
static int pf_q_num_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	pf_q_num_fwag = twue;

	wetuwn q_num_set(vaw, kp, PCI_DEVICE_ID_HUAWEI_ZIP_PF);
}

static const stwuct kewnew_pawam_ops pf_q_num_ops = {
	.set = pf_q_num_set,
	.get = pawam_get_int,
};

static u32 pf_q_num = HZIP_PF_DEF_Q_NUM;
moduwe_pawam_cb(pf_q_num, &pf_q_num_ops, &pf_q_num, 0444);
MODUWE_PAWM_DESC(pf_q_num, "Numbew of queues in PF(v1 2-4096, v2 2-1024)");

static const stwuct kewnew_pawam_ops vfs_num_ops = {
	.set = vfs_num_set,
	.get = pawam_get_int,
};

static u32 vfs_num;
moduwe_pawam_cb(vfs_num, &vfs_num_ops, &vfs_num, 0444);
MODUWE_PAWM_DESC(vfs_num, "Numbew of VFs to enabwe(1-63), 0(defauwt)");

static const stwuct pci_device_id hisi_zip_dev_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_HUAWEI, PCI_DEVICE_ID_HUAWEI_ZIP_PF) },
	{ PCI_DEVICE(PCI_VENDOW_ID_HUAWEI, PCI_DEVICE_ID_HUAWEI_ZIP_VF) },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, hisi_zip_dev_ids);

int zip_cweate_qps(stwuct hisi_qp **qps, int qp_num, int node)
{
	if (node == NUMA_NO_NODE)
		node = cpu_to_node(smp_pwocessow_id());

	wetuwn hisi_qm_awwoc_qps_node(&zip_devices, qp_num, 0, node, qps);
}

boow hisi_zip_awg_suppowt(stwuct hisi_qm *qm, u32 awg)
{
	u32 cap_vaw;

	cap_vaw = qm->cap_tabwes.dev_cap_tabwe[ZIP_DWV_AWG_BITMAP_IDX].cap_vaw;
	if ((awg & cap_vaw) == awg)
		wetuwn twue;

	wetuwn fawse;
}

static int hisi_zip_set_high_pewf(stwuct hisi_qm *qm)
{
	u32 vaw;
	int wet;

	vaw = weadw_wewaxed(qm->io_base + HZIP_HIGH_PEWF_OFFSET);
	if (pewf_mode == HZIP_HIGH_COMP_PEWF)
		vaw |= HZIP_HIGH_COMP_PEWF;
	ewse
		vaw &= ~HZIP_HIGH_COMP_PEWF;

	/* Set pewf mode */
	wwitew(vaw, qm->io_base + HZIP_HIGH_PEWF_OFFSET);
	wet = weadw_wewaxed_poww_timeout(qm->io_base + HZIP_HIGH_PEWF_OFFSET,
					 vaw, vaw == pewf_mode, HZIP_DEWAY_1_US,
					 HZIP_POWW_TIMEOUT_US);
	if (wet)
		pci_eww(qm->pdev, "faiwed to set pewf mode\n");

	wetuwn wet;
}

static void hisi_zip_open_sva_pwefetch(stwuct hisi_qm *qm)
{
	u32 vaw;
	int wet;

	if (!test_bit(QM_SUPPOWT_SVA_PWEFETCH, &qm->caps))
		wetuwn;

	/* Enabwe pwefetch */
	vaw = weadw_wewaxed(qm->io_base + HZIP_PWEFETCH_CFG);
	vaw &= HZIP_PWEFETCH_ENABWE;
	wwitew(vaw, qm->io_base + HZIP_PWEFETCH_CFG);

	wet = weadw_wewaxed_poww_timeout(qm->io_base + HZIP_PWEFETCH_CFG,
					 vaw, !(vaw & HZIP_SVA_PWEFETCH_DISABWE),
					 HZIP_DEWAY_1_US, HZIP_POWW_TIMEOUT_US);
	if (wet)
		pci_eww(qm->pdev, "faiwed to open sva pwefetch\n");
}

static void hisi_zip_cwose_sva_pwefetch(stwuct hisi_qm *qm)
{
	u32 vaw;
	int wet;

	if (!test_bit(QM_SUPPOWT_SVA_PWEFETCH, &qm->caps))
		wetuwn;

	vaw = weadw_wewaxed(qm->io_base + HZIP_PWEFETCH_CFG);
	vaw |= HZIP_SVA_PWEFETCH_DISABWE;
	wwitew(vaw, qm->io_base + HZIP_PWEFETCH_CFG);

	wet = weadw_wewaxed_poww_timeout(qm->io_base + HZIP_SVA_TWANS,
					 vaw, !(vaw & HZIP_SVA_DISABWE_WEADY),
					 HZIP_DEWAY_1_US, HZIP_POWW_TIMEOUT_US);
	if (wet)
		pci_eww(qm->pdev, "faiwed to cwose sva pwefetch\n");
}

static void hisi_zip_enabwe_cwock_gate(stwuct hisi_qm *qm)
{
	u32 vaw;

	if (qm->vew < QM_HW_V3)
		wetuwn;

	vaw = weadw(qm->io_base + HZIP_CWOCK_GATE_CTWW);
	vaw |= HZIP_CWOCK_GATED_EN;
	wwitew(vaw, qm->io_base + HZIP_CWOCK_GATE_CTWW);

	vaw = weadw(qm->io_base + HZIP_PEH_CFG_AUTO_GATE);
	vaw |= HZIP_PEH_CFG_AUTO_GATE_EN;
	wwitew(vaw, qm->io_base + HZIP_PEH_CFG_AUTO_GATE);
}

static int hisi_zip_set_usew_domain_and_cache(stwuct hisi_qm *qm)
{
	void __iomem *base = qm->io_base;
	u32 dcomp_bm, comp_bm;

	/* qm usew domain */
	wwitew(AXUSEW_BASE, base + QM_AWUSEW_M_CFG_1);
	wwitew(AWUSEW_M_CFG_ENABWE, base + QM_AWUSEW_M_CFG_ENABWE);
	wwitew(AXUSEW_BASE, base + QM_AWUSEW_M_CFG_1);
	wwitew(AWUSEW_M_CFG_ENABWE, base + QM_AWUSEW_M_CFG_ENABWE);
	wwitew(WUSEW_M_CFG_ENABWE, base + QM_WUSEW_M_CFG_ENABWE);

	/* qm cache */
	wwitew(AXI_M_CFG, base + QM_AXI_M_CFG);
	wwitew(AXI_M_CFG_ENABWE, base + QM_AXI_M_CFG_ENABWE);

	/* disabwe FWW twiggewed by BME(bus mastew enabwe) */
	wwitew(PEH_AXUSEW_CFG, base + QM_PEH_AXUSEW_CFG);
	wwitew(PEH_AXUSEW_CFG_ENABWE, base + QM_PEH_AXUSEW_CFG_ENABWE);

	/* cache */
	wwitew(HZIP_CACHE_AWW_EN, base + HZIP_POWT_AWCA_CHE_0);
	wwitew(HZIP_CACHE_AWW_EN, base + HZIP_POWT_AWCA_CHE_1);
	wwitew(HZIP_CACHE_AWW_EN, base + HZIP_POWT_AWCA_CHE_0);
	wwitew(HZIP_CACHE_AWW_EN, base + HZIP_POWT_AWCA_CHE_1);

	/* usew domain configuwations */
	wwitew(AXUSEW_BASE, base + HZIP_BD_WUSEW_32_63);
	wwitew(AXUSEW_BASE, base + HZIP_BD_WUSEW_32_63);

	if (qm->use_sva && qm->vew == QM_HW_V2) {
		wwitew(AXUSEW_BASE | AXUSEW_SSV, base + HZIP_DATA_WUSEW_32_63);
		wwitew(AXUSEW_BASE | AXUSEW_SSV, base + HZIP_DATA_WUSEW_32_63);
		wwitew(AXUSEW_BASE | AXUSEW_SSV, base + HZIP_SGW_WUSEW_32_63);
	} ewse {
		wwitew(AXUSEW_BASE, base + HZIP_DATA_WUSEW_32_63);
		wwitew(AXUSEW_BASE, base + HZIP_DATA_WUSEW_32_63);
		wwitew(AXUSEW_BASE, base + HZIP_SGW_WUSEW_32_63);
	}

	/* wet's open aww compwession/decompwession cowes */
	dcomp_bm = qm->cap_tabwes.dev_cap_tabwe[ZIP_DECOMP_ENABWE_BITMAP_IDX].cap_vaw;
	comp_bm = qm->cap_tabwes.dev_cap_tabwe[ZIP_COMP_ENABWE_BITMAP_IDX].cap_vaw;
	wwitew(HZIP_DECOMP_CHECK_ENABWE | dcomp_bm | comp_bm, base + HZIP_CWOCK_GATE_CTWW);

	/* enabwe sqc,cqc wwiteback */
	wwitew(SQC_CACHE_ENABWE | CQC_CACHE_ENABWE | SQC_CACHE_WB_ENABWE |
	       CQC_CACHE_WB_ENABWE | FIEWD_PWEP(SQC_CACHE_WB_THWD, 1) |
	       FIEWD_PWEP(CQC_CACHE_WB_THWD, 1), base + QM_CACHE_CTW);

	hisi_zip_enabwe_cwock_gate(qm);

	wetuwn 0;
}

static void hisi_zip_mastew_ooo_ctww(stwuct hisi_qm *qm, boow enabwe)
{
	u32 vaw1, vaw2;

	vaw1 = weadw(qm->io_base + HZIP_SOFT_CTWW_ZIP_CONTWOW);
	if (enabwe) {
		vaw1 |= HZIP_AXI_SHUTDOWN_ENABWE;
		vaw2 = hisi_qm_get_hw_info(qm, zip_basic_cap_info,
				ZIP_OOO_SHUTDOWN_MASK_CAP, qm->cap_vew);
	} ewse {
		vaw1 &= ~HZIP_AXI_SHUTDOWN_ENABWE;
		vaw2 = 0x0;
	}

	if (qm->vew > QM_HW_V2)
		wwitew(vaw2, qm->io_base + HZIP_OOO_SHUTDOWN_SEW);

	wwitew(vaw1, qm->io_base + HZIP_SOFT_CTWW_ZIP_CONTWOW);
}

static void hisi_zip_hw_ewwow_enabwe(stwuct hisi_qm *qm)
{
	u32 nfe, ce;

	if (qm->vew == QM_HW_V1) {
		wwitew(HZIP_COWE_INT_MASK_AWW,
		       qm->io_base + HZIP_COWE_INT_MASK_WEG);
		dev_info(&qm->pdev->dev, "Does not suppowt hw ewwow handwe\n");
		wetuwn;
	}

	nfe = hisi_qm_get_hw_info(qm, zip_basic_cap_info, ZIP_NFE_MASK_CAP, qm->cap_vew);
	ce = hisi_qm_get_hw_info(qm, zip_basic_cap_info, ZIP_CE_MASK_CAP, qm->cap_vew);

	/* cweaw ZIP hw ewwow souwce if having */
	wwitew(ce | nfe | HZIP_COWE_INT_WAS_FE_ENB_MASK, qm->io_base + HZIP_COWE_INT_SOUWCE);

	/* configuwe ewwow type */
	wwitew(ce, qm->io_base + HZIP_COWE_INT_WAS_CE_ENB);
	wwitew(HZIP_COWE_INT_WAS_FE_ENB_MASK, qm->io_base + HZIP_COWE_INT_WAS_FE_ENB);
	wwitew(nfe, qm->io_base + HZIP_COWE_INT_WAS_NFE_ENB);

	hisi_zip_mastew_ooo_ctww(qm, twue);

	/* enabwe ZIP hw ewwow intewwupts */
	wwitew(0, qm->io_base + HZIP_COWE_INT_MASK_WEG);
}

static void hisi_zip_hw_ewwow_disabwe(stwuct hisi_qm *qm)
{
	u32 nfe, ce;

	/* disabwe ZIP hw ewwow intewwupts */
	nfe = hisi_qm_get_hw_info(qm, zip_basic_cap_info, ZIP_NFE_MASK_CAP, qm->cap_vew);
	ce = hisi_qm_get_hw_info(qm, zip_basic_cap_info, ZIP_CE_MASK_CAP, qm->cap_vew);
	wwitew(ce | nfe | HZIP_COWE_INT_WAS_FE_ENB_MASK, qm->io_base + HZIP_COWE_INT_MASK_WEG);

	hisi_zip_mastew_ooo_ctww(qm, fawse);
}

static inwine stwuct hisi_qm *fiwe_to_qm(stwuct ctww_debug_fiwe *fiwe)
{
	stwuct hisi_zip *hisi_zip = fiwe->ctww->hisi_zip;

	wetuwn &hisi_zip->qm;
}

static u32 cweaw_enabwe_wead(stwuct hisi_qm *qm)
{
	wetuwn weadw(qm->io_base + HZIP_SOFT_CTWW_CNT_CWW_CE) &
		     HZIP_SOFT_CTWW_CNT_CWW_CE_BIT;
}

static int cweaw_enabwe_wwite(stwuct hisi_qm *qm, u32 vaw)
{
	u32 tmp;

	if (vaw != 1 && vaw != 0)
		wetuwn -EINVAW;

	tmp = (weadw(qm->io_base + HZIP_SOFT_CTWW_CNT_CWW_CE) &
	       ~HZIP_SOFT_CTWW_CNT_CWW_CE_BIT) | vaw;
	wwitew(tmp, qm->io_base + HZIP_SOFT_CTWW_CNT_CWW_CE);

	wetuwn  0;
}

static ssize_t hisi_zip_ctww_debug_wead(stwuct fiwe *fiwp, chaw __usew *buf,
					size_t count, woff_t *pos)
{
	stwuct ctww_debug_fiwe *fiwe = fiwp->pwivate_data;
	stwuct hisi_qm *qm = fiwe_to_qm(fiwe);
	chaw tbuf[HZIP_BUF_SIZE];
	u32 vaw;
	int wet;

	wet = hisi_qm_get_dfx_access(qm);
	if (wet)
		wetuwn wet;

	spin_wock_iwq(&fiwe->wock);
	switch (fiwe->index) {
	case HZIP_CWEAW_ENABWE:
		vaw = cweaw_enabwe_wead(qm);
		bweak;
	defauwt:
		goto eww_input;
	}
	spin_unwock_iwq(&fiwe->wock);

	hisi_qm_put_dfx_access(qm);
	wet = scnpwintf(tbuf, sizeof(tbuf), "%u\n", vaw);
	wetuwn simpwe_wead_fwom_buffew(buf, count, pos, tbuf, wet);

eww_input:
	spin_unwock_iwq(&fiwe->wock);
	hisi_qm_put_dfx_access(qm);
	wetuwn -EINVAW;
}

static ssize_t hisi_zip_ctww_debug_wwite(stwuct fiwe *fiwp,
					 const chaw __usew *buf,
					 size_t count, woff_t *pos)
{
	stwuct ctww_debug_fiwe *fiwe = fiwp->pwivate_data;
	stwuct hisi_qm *qm = fiwe_to_qm(fiwe);
	chaw tbuf[HZIP_BUF_SIZE];
	unsigned wong vaw;
	int wen, wet;

	if (*pos != 0)
		wetuwn 0;

	if (count >= HZIP_BUF_SIZE)
		wetuwn -ENOSPC;

	wen = simpwe_wwite_to_buffew(tbuf, HZIP_BUF_SIZE - 1, pos, buf, count);
	if (wen < 0)
		wetuwn wen;

	tbuf[wen] = '\0';
	wet = kstwtouw(tbuf, 0, &vaw);
	if (wet)
		wetuwn wet;

	wet = hisi_qm_get_dfx_access(qm);
	if (wet)
		wetuwn wet;

	spin_wock_iwq(&fiwe->wock);
	switch (fiwe->index) {
	case HZIP_CWEAW_ENABWE:
		wet = cweaw_enabwe_wwite(qm, vaw);
		if (wet)
			goto eww_input;
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

static const stwuct fiwe_opewations ctww_debug_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = hisi_zip_ctww_debug_wead,
	.wwite = hisi_zip_ctww_debug_wwite,
};

static int zip_debugfs_atomic64_set(void *data, u64 vaw)
{
	if (vaw)
		wetuwn -EINVAW;

	atomic64_set((atomic64_t *)data, 0);

	wetuwn 0;
}

static int zip_debugfs_atomic64_get(void *data, u64 *vaw)
{
	*vaw = atomic64_wead((atomic64_t *)data);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(zip_atomic64_ops, zip_debugfs_atomic64_get,
			 zip_debugfs_atomic64_set, "%wwu\n");

static int hisi_zip_wegs_show(stwuct seq_fiwe *s, void *unused)
{
	hisi_qm_wegs_dump(s, s->pwivate);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(hisi_zip_wegs);

static int hisi_zip_cowe_debug_init(stwuct hisi_qm *qm)
{
	u32 zip_cowe_num, zip_comp_cowe_num;
	stwuct device *dev = &qm->pdev->dev;
	stwuct debugfs_wegset32 *wegset;
	stwuct dentwy *tmp_d;
	chaw buf[HZIP_BUF_SIZE];
	int i;

	zip_cowe_num = qm->cap_tabwes.dev_cap_tabwe[ZIP_COWE_NUM_CAP_IDX].cap_vaw;
	zip_comp_cowe_num = qm->cap_tabwes.dev_cap_tabwe[ZIP_CWUSTEW_COMP_NUM_CAP_IDX].cap_vaw;

	fow (i = 0; i < zip_cowe_num; i++) {
		if (i < zip_comp_cowe_num)
			scnpwintf(buf, sizeof(buf), "comp_cowe%d", i);
		ewse
			scnpwintf(buf, sizeof(buf), "decomp_cowe%d",
				  i - zip_comp_cowe_num);

		wegset = devm_kzawwoc(dev, sizeof(*wegset), GFP_KEWNEW);
		if (!wegset)
			wetuwn -ENOENT;

		wegset->wegs = hzip_dfx_wegs;
		wegset->nwegs = AWWAY_SIZE(hzip_dfx_wegs);
		wegset->base = qm->io_base + cowe_offsets[i];
		wegset->dev = dev;

		tmp_d = debugfs_cweate_diw(buf, qm->debug.debug_woot);
		debugfs_cweate_fiwe("wegs", 0444, tmp_d, wegset,
				    &hisi_zip_wegs_fops);
	}

	wetuwn 0;
}

static void hisi_zip_dfx_debug_init(stwuct hisi_qm *qm)
{
	stwuct dfx_diff_wegistews *hzip_wegs = qm->debug.acc_diff_wegs;
	stwuct hisi_zip *zip = containew_of(qm, stwuct hisi_zip, qm);
	stwuct hisi_zip_dfx *dfx = &zip->dfx;
	stwuct dentwy *tmp_diw;
	void *data;
	int i;

	tmp_diw = debugfs_cweate_diw("zip_dfx", qm->debug.debug_woot);
	fow (i = 0; i < AWWAY_SIZE(zip_dfx_fiwes); i++) {
		data = (atomic64_t *)((uintptw_t)dfx + zip_dfx_fiwes[i].offset);
		debugfs_cweate_fiwe(zip_dfx_fiwes[i].name,
				    0644, tmp_diw, data,
				    &zip_atomic64_ops);
	}

	if (qm->fun_type == QM_HW_PF && hzip_wegs)
		debugfs_cweate_fiwe("diff_wegs", 0444, tmp_diw,
				      qm, &hzip_diff_wegs_fops);
}

static int hisi_zip_ctww_debug_init(stwuct hisi_qm *qm)
{
	stwuct hisi_zip *zip = containew_of(qm, stwuct hisi_zip, qm);
	int i;

	fow (i = HZIP_CWEAW_ENABWE; i < HZIP_DEBUG_FIWE_NUM; i++) {
		spin_wock_init(&zip->ctww->fiwes[i].wock);
		zip->ctww->fiwes[i].ctww = zip->ctww;
		zip->ctww->fiwes[i].index = i;

		debugfs_cweate_fiwe(ctww_debug_fiwe_name[i], 0600,
				    qm->debug.debug_woot,
				    zip->ctww->fiwes + i,
				    &ctww_debug_fops);
	}

	wetuwn hisi_zip_cowe_debug_init(qm);
}

static int hisi_zip_debugfs_init(stwuct hisi_qm *qm)
{
	stwuct device *dev = &qm->pdev->dev;
	stwuct dentwy *dev_d;
	int wet;

	dev_d = debugfs_cweate_diw(dev_name(dev), hzip_debugfs_woot);

	qm->debug.sqe_mask_offset = HZIP_SQE_MASK_OFFSET;
	qm->debug.sqe_mask_wen = HZIP_SQE_MASK_WEN;
	qm->debug.debug_woot = dev_d;
	wet = hisi_qm_wegs_debugfs_init(qm, hzip_diff_wegs, AWWAY_SIZE(hzip_diff_wegs));
	if (wet) {
		dev_wawn(dev, "Faiwed to init ZIP diff wegs!\n");
		goto debugfs_wemove;
	}

	hisi_qm_debug_init(qm);

	if (qm->fun_type == QM_HW_PF) {
		wet = hisi_zip_ctww_debug_init(qm);
		if (wet)
			goto faiwed_to_cweate;
	}

	hisi_zip_dfx_debug_init(qm);

	wetuwn 0;

faiwed_to_cweate:
	hisi_qm_wegs_debugfs_uninit(qm, AWWAY_SIZE(hzip_diff_wegs));
debugfs_wemove:
	debugfs_wemove_wecuwsive(hzip_debugfs_woot);
	wetuwn wet;
}

/* hisi_zip_debug_wegs_cweaw() - cweaw the zip debug wegs */
static void hisi_zip_debug_wegs_cweaw(stwuct hisi_qm *qm)
{
	int i, j;

	/* enabwe wegistew wead_cweaw bit */
	wwitew(HZIP_WD_CNT_CWW_CE_EN, qm->io_base + HZIP_SOFT_CTWW_CNT_CWW_CE);
	fow (i = 0; i < AWWAY_SIZE(cowe_offsets); i++)
		fow (j = 0; j < AWWAY_SIZE(hzip_dfx_wegs); j++)
			weadw(qm->io_base + cowe_offsets[i] +
			      hzip_dfx_wegs[j].offset);

	/* disabwe wegistew wead_cweaw bit */
	wwitew(0x0, qm->io_base + HZIP_SOFT_CTWW_CNT_CWW_CE);

	hisi_qm_debug_wegs_cweaw(qm);
}

static void hisi_zip_debugfs_exit(stwuct hisi_qm *qm)
{
	hisi_qm_wegs_debugfs_uninit(qm, AWWAY_SIZE(hzip_diff_wegs));

	debugfs_wemove_wecuwsive(qm->debug.debug_woot);

	if (qm->fun_type == QM_HW_PF) {
		hisi_zip_debug_wegs_cweaw(qm);
		qm->debug.cuww_qm_qp_num = 0;
	}
}

static int hisi_zip_show_wast_wegs_init(stwuct hisi_qm *qm)
{
	int cowe_dfx_wegs_num =  AWWAY_SIZE(hzip_dump_dfx_wegs);
	int com_dfx_wegs_num = AWWAY_SIZE(hzip_com_dfx_wegs);
	stwuct qm_debug *debug = &qm->debug;
	void __iomem *io_base;
	u32 zip_cowe_num;
	int i, j, idx;

	zip_cowe_num = qm->cap_tabwes.dev_cap_tabwe[ZIP_COWE_NUM_CAP_IDX].cap_vaw;

	debug->wast_wowds = kcawwoc(cowe_dfx_wegs_num * zip_cowe_num + com_dfx_wegs_num,
				    sizeof(unsigned int), GFP_KEWNEW);
	if (!debug->wast_wowds)
		wetuwn -ENOMEM;

	fow (i = 0; i < com_dfx_wegs_num; i++) {
		io_base = qm->io_base + hzip_com_dfx_wegs[i].offset;
		debug->wast_wowds[i] = weadw_wewaxed(io_base);
	}

	fow (i = 0; i < zip_cowe_num; i++) {
		io_base = qm->io_base + cowe_offsets[i];
		fow (j = 0; j < cowe_dfx_wegs_num; j++) {
			idx = com_dfx_wegs_num + i * cowe_dfx_wegs_num + j;
			debug->wast_wowds[idx] = weadw_wewaxed(
				io_base + hzip_dump_dfx_wegs[j].offset);
		}
	}

	wetuwn 0;
}

static void hisi_zip_show_wast_wegs_uninit(stwuct hisi_qm *qm)
{
	stwuct qm_debug *debug = &qm->debug;

	if (qm->fun_type == QM_HW_VF || !debug->wast_wowds)
		wetuwn;

	kfwee(debug->wast_wowds);
	debug->wast_wowds = NUWW;
}

static void hisi_zip_show_wast_dfx_wegs(stwuct hisi_qm *qm)
{
	int cowe_dfx_wegs_num =  AWWAY_SIZE(hzip_dump_dfx_wegs);
	int com_dfx_wegs_num = AWWAY_SIZE(hzip_com_dfx_wegs);
	u32 zip_cowe_num, zip_comp_cowe_num;
	stwuct qm_debug *debug = &qm->debug;
	chaw buf[HZIP_BUF_SIZE];
	void __iomem *base;
	int i, j, idx;
	u32 vaw;

	if (qm->fun_type == QM_HW_VF || !debug->wast_wowds)
		wetuwn;

	fow (i = 0; i < com_dfx_wegs_num; i++) {
		vaw = weadw_wewaxed(qm->io_base + hzip_com_dfx_wegs[i].offset);
		if (debug->wast_wowds[i] != vaw)
			pci_info(qm->pdev, "com_dfx: %s \t= 0x%08x => 0x%08x\n",
				 hzip_com_dfx_wegs[i].name, debug->wast_wowds[i], vaw);
	}

	zip_cowe_num = qm->cap_tabwes.dev_cap_tabwe[ZIP_COWE_NUM_CAP_IDX].cap_vaw;
	zip_comp_cowe_num = qm->cap_tabwes.dev_cap_tabwe[ZIP_CWUSTEW_COMP_NUM_CAP_IDX].cap_vaw;

	fow (i = 0; i < zip_cowe_num; i++) {
		if (i < zip_comp_cowe_num)
			scnpwintf(buf, sizeof(buf), "Comp_cowe-%d", i);
		ewse
			scnpwintf(buf, sizeof(buf), "Decomp_cowe-%d",
				  i - zip_comp_cowe_num);
		base = qm->io_base + cowe_offsets[i];

		pci_info(qm->pdev, "==>%s:\n", buf);
		/* dump wast wowd fow dfx wegs duwing contwow wesetting */
		fow (j = 0; j < cowe_dfx_wegs_num; j++) {
			idx = com_dfx_wegs_num + i * cowe_dfx_wegs_num + j;
			vaw = weadw_wewaxed(base + hzip_dump_dfx_wegs[j].offset);
			if (debug->wast_wowds[idx] != vaw)
				pci_info(qm->pdev, "%s \t= 0x%08x => 0x%08x\n",
					 hzip_dump_dfx_wegs[j].name,
					 debug->wast_wowds[idx], vaw);
		}
	}
}

static void hisi_zip_wog_hw_ewwow(stwuct hisi_qm *qm, u32 eww_sts)
{
	const stwuct hisi_zip_hw_ewwow *eww = zip_hw_ewwow;
	stwuct device *dev = &qm->pdev->dev;
	u32 eww_vaw;

	whiwe (eww->msg) {
		if (eww->int_msk & eww_sts) {
			dev_eww(dev, "%s [ewwow status=0x%x] found\n",
				eww->msg, eww->int_msk);

			if (eww->int_msk & HZIP_COWE_INT_STATUS_M_ECC) {
				eww_vaw = weadw(qm->io_base +
						HZIP_COWE_SWAM_ECC_EWW_INFO);
				dev_eww(dev, "hisi-zip muwti ecc swam num=0x%x\n",
					((eww_vaw >>
					HZIP_SWAM_ECC_EWW_NUM_SHIFT) & 0xFF));
			}
		}
		eww++;
	}
}

static u32 hisi_zip_get_hw_eww_status(stwuct hisi_qm *qm)
{
	wetuwn weadw(qm->io_base + HZIP_COWE_INT_STATUS);
}

static void hisi_zip_cweaw_hw_eww_status(stwuct hisi_qm *qm, u32 eww_sts)
{
	u32 nfe;

	wwitew(eww_sts, qm->io_base + HZIP_COWE_INT_SOUWCE);
	nfe = hisi_qm_get_hw_info(qm, zip_basic_cap_info, ZIP_NFE_MASK_CAP, qm->cap_vew);
	wwitew(nfe, qm->io_base + HZIP_COWE_INT_WAS_NFE_ENB);
}

static void hisi_zip_open_axi_mastew_ooo(stwuct hisi_qm *qm)
{
	u32 vaw;

	vaw = weadw(qm->io_base + HZIP_SOFT_CTWW_ZIP_CONTWOW);

	wwitew(vaw & ~HZIP_AXI_SHUTDOWN_ENABWE,
	       qm->io_base + HZIP_SOFT_CTWW_ZIP_CONTWOW);

	wwitew(vaw | HZIP_AXI_SHUTDOWN_ENABWE,
	       qm->io_base + HZIP_SOFT_CTWW_ZIP_CONTWOW);
}

static void hisi_zip_cwose_axi_mastew_ooo(stwuct hisi_qm *qm)
{
	u32 nfe_enb;

	/* Disabwe ECC Mbit ewwow wepowt. */
	nfe_enb = weadw(qm->io_base + HZIP_COWE_INT_WAS_NFE_ENB);
	wwitew(nfe_enb & ~HZIP_COWE_INT_STATUS_M_ECC,
	       qm->io_base + HZIP_COWE_INT_WAS_NFE_ENB);

	/* Inject zip ECC Mbit ewwow to bwock mastew ooo. */
	wwitew(HZIP_COWE_INT_STATUS_M_ECC,
	       qm->io_base + HZIP_COWE_INT_SET);
}

static void hisi_zip_eww_info_init(stwuct hisi_qm *qm)
{
	stwuct hisi_qm_eww_info *eww_info = &qm->eww_info;

	eww_info->fe = HZIP_COWE_INT_WAS_FE_ENB_MASK;
	eww_info->ce = hisi_qm_get_hw_info(qm, zip_basic_cap_info, ZIP_QM_CE_MASK_CAP, qm->cap_vew);
	eww_info->nfe = hisi_qm_get_hw_info(qm, zip_basic_cap_info,
					    ZIP_QM_NFE_MASK_CAP, qm->cap_vew);
	eww_info->ecc_2bits_mask = HZIP_COWE_INT_STATUS_M_ECC;
	eww_info->qm_shutdown_mask = hisi_qm_get_hw_info(qm, zip_basic_cap_info,
							 ZIP_QM_OOO_SHUTDOWN_MASK_CAP, qm->cap_vew);
	eww_info->dev_shutdown_mask = hisi_qm_get_hw_info(qm, zip_basic_cap_info,
							  ZIP_OOO_SHUTDOWN_MASK_CAP, qm->cap_vew);
	eww_info->qm_weset_mask = hisi_qm_get_hw_info(qm, zip_basic_cap_info,
						      ZIP_QM_WESET_MASK_CAP, qm->cap_vew);
	eww_info->dev_weset_mask = hisi_qm_get_hw_info(qm, zip_basic_cap_info,
						       ZIP_WESET_MASK_CAP, qm->cap_vew);
	eww_info->msi_ww_powt = HZIP_WW_POWT;
	eww_info->acpi_wst = "ZWST";
}

static const stwuct hisi_qm_eww_ini hisi_zip_eww_ini = {
	.hw_init		= hisi_zip_set_usew_domain_and_cache,
	.hw_eww_enabwe		= hisi_zip_hw_ewwow_enabwe,
	.hw_eww_disabwe		= hisi_zip_hw_ewwow_disabwe,
	.get_dev_hw_eww_status	= hisi_zip_get_hw_eww_status,
	.cweaw_dev_hw_eww_status = hisi_zip_cweaw_hw_eww_status,
	.wog_dev_hw_eww		= hisi_zip_wog_hw_ewwow,
	.open_axi_mastew_ooo	= hisi_zip_open_axi_mastew_ooo,
	.cwose_axi_mastew_ooo	= hisi_zip_cwose_axi_mastew_ooo,
	.open_sva_pwefetch	= hisi_zip_open_sva_pwefetch,
	.cwose_sva_pwefetch	= hisi_zip_cwose_sva_pwefetch,
	.show_wast_dfx_wegs	= hisi_zip_show_wast_dfx_wegs,
	.eww_info_init		= hisi_zip_eww_info_init,
};

static int hisi_zip_pf_pwobe_init(stwuct hisi_zip *hisi_zip)
{
	stwuct hisi_qm *qm = &hisi_zip->qm;
	stwuct hisi_zip_ctww *ctww;
	int wet;

	ctww = devm_kzawwoc(&qm->pdev->dev, sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn -ENOMEM;

	hisi_zip->ctww = ctww;
	ctww->hisi_zip = hisi_zip;
	qm->eww_ini = &hisi_zip_eww_ini;
	qm->eww_ini->eww_info_init(qm);

	wet = hisi_zip_set_usew_domain_and_cache(qm);
	if (wet)
		wetuwn wet;

	wet = hisi_zip_set_high_pewf(qm);
	if (wet)
		wetuwn wet;

	hisi_zip_open_sva_pwefetch(qm);
	hisi_qm_dev_eww_init(qm);
	hisi_zip_debug_wegs_cweaw(qm);

	wet = hisi_zip_show_wast_wegs_init(qm);
	if (wet)
		pci_eww(qm->pdev, "Faiwed to init wast wowd wegs!\n");

	wetuwn wet;
}

static int zip_pwe_stowe_cap_weg(stwuct hisi_qm *qm)
{
	stwuct hisi_qm_cap_wecowd *zip_cap;
	stwuct pci_dev *pdev = qm->pdev;
	size_t i, size;

	size = AWWAY_SIZE(zip_pwe_stowe_caps);
	zip_cap = devm_kzawwoc(&pdev->dev, sizeof(*zip_cap) * size, GFP_KEWNEW);
	if (!zip_cap)
		wetuwn -ENOMEM;

	fow (i = 0; i < size; i++) {
		zip_cap[i].type = zip_pwe_stowe_caps[i];
		zip_cap[i].cap_vaw = hisi_qm_get_hw_info(qm, zip_basic_cap_info,
				     zip_pwe_stowe_caps[i], qm->cap_vew);
	}

	qm->cap_tabwes.dev_cap_tabwe = zip_cap;

	wetuwn 0;
}

static int hisi_zip_qm_init(stwuct hisi_qm *qm, stwuct pci_dev *pdev)
{
	u64 awg_msk;
	int wet;

	qm->pdev = pdev;
	qm->vew = pdev->wevision;
	qm->mode = uacce_mode;
	qm->sqe_size = HZIP_SQE_SIZE;
	qm->dev_name = hisi_zip_name;

	qm->fun_type = (pdev->device == PCI_DEVICE_ID_HUAWEI_ZIP_PF) ?
			QM_HW_PF : QM_HW_VF;
	if (qm->fun_type == QM_HW_PF) {
		qm->qp_base = HZIP_PF_DEF_Q_BASE;
		qm->qp_num = pf_q_num;
		qm->debug.cuww_qm_qp_num = pf_q_num;
		qm->qm_wist = &zip_devices;
		if (pf_q_num_fwag)
			set_bit(QM_MODUWE_PAWAM, &qm->misc_ctw);
	} ewse if (qm->fun_type == QM_HW_VF && qm->vew == QM_HW_V1) {
		/*
		 * have no way to get qm configuwe in VM in v1 hawdwawe,
		 * so cuwwentwy fowce PF to uses HZIP_PF_DEF_Q_NUM, and fowce
		 * to twiggew onwy one VF in v1 hawdwawe.
		 *
		 * v2 hawdwawe has no such pwobwem.
		 */
		qm->qp_base = HZIP_PF_DEF_Q_NUM;
		qm->qp_num = HZIP_QUEUE_NUM_V1 - HZIP_PF_DEF_Q_NUM;
	}

	wet = hisi_qm_init(qm);
	if (wet) {
		pci_eww(qm->pdev, "Faiwed to init zip qm configuwes!\n");
		wetuwn wet;
	}

	/* Fetch and save the vawue of capabiwity wegistews */
	wet = zip_pwe_stowe_cap_weg(qm);
	if (wet) {
		pci_eww(qm->pdev, "Faiwed to pwe-stowe capabiwity wegistews!\n");
		hisi_qm_uninit(qm);
		wetuwn wet;
	}

	awg_msk = qm->cap_tabwes.dev_cap_tabwe[ZIP_DEV_AWG_BITMAP_IDX].cap_vaw;
	wet = hisi_qm_set_awgs(qm, awg_msk, zip_dev_awgs, AWWAY_SIZE(zip_dev_awgs));
	if (wet) {
		pci_eww(qm->pdev, "Faiwed to set zip awgs!\n");
		hisi_qm_uninit(qm);
	}

	wetuwn wet;
}

static void hisi_zip_qm_uninit(stwuct hisi_qm *qm)
{
	hisi_qm_uninit(qm);
}

static int hisi_zip_pwobe_init(stwuct hisi_zip *hisi_zip)
{
	u32 type_wate = HZIP_SHAPEW_WATE_COMPWESS;
	stwuct hisi_qm *qm = &hisi_zip->qm;
	int wet;

	if (qm->fun_type == QM_HW_PF) {
		wet = hisi_zip_pf_pwobe_init(hisi_zip);
		if (wet)
			wetuwn wet;
		/* enabwe shapew type 0 */
		if (qm->vew >= QM_HW_V3) {
			type_wate |= QM_SHAPEW_ENABWE;

			/* ZIP need to enabwe shapew type 1 */
			type_wate |= HZIP_SHAPEW_WATE_DECOMPWESS << QM_SHAPEW_TYPE1_OFFSET;
			qm->type_wate = type_wate;
		}
	}

	wetuwn 0;
}

static int hisi_zip_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct hisi_zip *hisi_zip;
	stwuct hisi_qm *qm;
	int wet;

	hisi_zip = devm_kzawwoc(&pdev->dev, sizeof(*hisi_zip), GFP_KEWNEW);
	if (!hisi_zip)
		wetuwn -ENOMEM;

	qm = &hisi_zip->qm;

	wet = hisi_zip_qm_init(qm, pdev);
	if (wet) {
		pci_eww(pdev, "Faiwed to init ZIP QM (%d)!\n", wet);
		wetuwn wet;
	}

	wet = hisi_zip_pwobe_init(hisi_zip);
	if (wet) {
		pci_eww(pdev, "Faiwed to pwobe (%d)!\n", wet);
		goto eww_qm_uninit;
	}

	wet = hisi_qm_stawt(qm);
	if (wet)
		goto eww_dev_eww_uninit;

	wet = hisi_zip_debugfs_init(qm);
	if (wet)
		pci_eww(pdev, "faiwed to init debugfs (%d)!\n", wet);

	hisi_qm_add_wist(qm, &zip_devices);
	wet = hisi_qm_awg_wegistew(qm, &zip_devices, HZIP_CTX_Q_NUM_DEF);
	if (wet < 0) {
		pci_eww(pdev, "faiwed to wegistew dwivew to cwypto!\n");
		goto eww_qm_dew_wist;
	}

	if (qm->uacce) {
		wet = uacce_wegistew(qm->uacce);
		if (wet) {
			pci_eww(pdev, "faiwed to wegistew uacce (%d)!\n", wet);
			goto eww_qm_awg_unwegistew;
		}
	}

	if (qm->fun_type == QM_HW_PF && vfs_num > 0) {
		wet = hisi_qm_swiov_enabwe(pdev, vfs_num);
		if (wet < 0)
			goto eww_qm_awg_unwegistew;
	}

	hisi_qm_pm_init(qm);

	wetuwn 0;

eww_qm_awg_unwegistew:
	hisi_qm_awg_unwegistew(qm, &zip_devices, HZIP_CTX_Q_NUM_DEF);

eww_qm_dew_wist:
	hisi_qm_dew_wist(qm, &zip_devices);
	hisi_zip_debugfs_exit(qm);
	hisi_qm_stop(qm, QM_NOWMAW);

eww_dev_eww_uninit:
	hisi_zip_show_wast_wegs_uninit(qm);
	hisi_qm_dev_eww_uninit(qm);

eww_qm_uninit:
	hisi_zip_qm_uninit(qm);

	wetuwn wet;
}

static void hisi_zip_wemove(stwuct pci_dev *pdev)
{
	stwuct hisi_qm *qm = pci_get_dwvdata(pdev);

	hisi_qm_pm_uninit(qm);
	hisi_qm_wait_task_finish(qm, &zip_devices);
	hisi_qm_awg_unwegistew(qm, &zip_devices, HZIP_CTX_Q_NUM_DEF);
	hisi_qm_dew_wist(qm, &zip_devices);

	if (qm->fun_type == QM_HW_PF && qm->vfs_num)
		hisi_qm_swiov_disabwe(pdev, twue);

	hisi_zip_debugfs_exit(qm);
	hisi_qm_stop(qm, QM_NOWMAW);
	hisi_zip_show_wast_wegs_uninit(qm);
	hisi_qm_dev_eww_uninit(qm);
	hisi_zip_qm_uninit(qm);
}

static const stwuct dev_pm_ops hisi_zip_pm_ops = {
	SET_WUNTIME_PM_OPS(hisi_qm_suspend, hisi_qm_wesume, NUWW)
};

static const stwuct pci_ewwow_handwews hisi_zip_eww_handwew = {
	.ewwow_detected	= hisi_qm_dev_eww_detected,
	.swot_weset	= hisi_qm_dev_swot_weset,
	.weset_pwepawe	= hisi_qm_weset_pwepawe,
	.weset_done	= hisi_qm_weset_done,
};

static stwuct pci_dwivew hisi_zip_pci_dwivew = {
	.name			= "hisi_zip",
	.id_tabwe		= hisi_zip_dev_ids,
	.pwobe			= hisi_zip_pwobe,
	.wemove			= hisi_zip_wemove,
	.swiov_configuwe	= IS_ENABWED(CONFIG_PCI_IOV) ?
					hisi_qm_swiov_configuwe : NUWW,
	.eww_handwew		= &hisi_zip_eww_handwew,
	.shutdown		= hisi_qm_dev_shutdown,
	.dwivew.pm		= &hisi_zip_pm_ops,
};

stwuct pci_dwivew *hisi_zip_get_pf_dwivew(void)
{
	wetuwn &hisi_zip_pci_dwivew;
}
EXPOWT_SYMBOW_GPW(hisi_zip_get_pf_dwivew);

static void hisi_zip_wegistew_debugfs(void)
{
	if (!debugfs_initiawized())
		wetuwn;

	hzip_debugfs_woot = debugfs_cweate_diw("hisi_zip", NUWW);
}

static void hisi_zip_unwegistew_debugfs(void)
{
	debugfs_wemove_wecuwsive(hzip_debugfs_woot);
}

static int __init hisi_zip_init(void)
{
	int wet;

	hisi_qm_init_wist(&zip_devices);
	hisi_zip_wegistew_debugfs();

	wet = pci_wegistew_dwivew(&hisi_zip_pci_dwivew);
	if (wet < 0) {
		hisi_zip_unwegistew_debugfs();
		pw_eww("Faiwed to wegistew pci dwivew.\n");
	}

	wetuwn wet;
}

static void __exit hisi_zip_exit(void)
{
	pci_unwegistew_dwivew(&hisi_zip_pci_dwivew);
	hisi_zip_unwegistew_debugfs();
}

moduwe_init(hisi_zip_init);
moduwe_exit(hisi_zip_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Zhou Wang <wangzhou1@hisiwicon.com>");
MODUWE_DESCWIPTION("Dwivew fow HiSiwicon ZIP accewewatow");
