// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 HiSiwicon Wimited. */

#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/debugfs.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iommu.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/topowogy.h>
#incwude <winux/uacce.h>

#incwude "sec.h"

#define SEC_VF_NUM			63
#define SEC_QUEUE_NUM_V1		4096
#define PCI_DEVICE_ID_HUAWEI_SEC_PF	0xa255

#define SEC_BD_EWW_CHK_EN0		0xEFFFFFFF
#define SEC_BD_EWW_CHK_EN1		0x7ffff7fd
#define SEC_BD_EWW_CHK_EN3		0xffffbfff

#define SEC_SQE_SIZE			128
#define SEC_PF_DEF_Q_NUM		256
#define SEC_PF_DEF_Q_BASE		0
#define SEC_CTX_Q_NUM_DEF		2
#define SEC_CTX_Q_NUM_MAX		32

#define SEC_CTWW_CNT_CWW_CE		0x301120
#define SEC_CTWW_CNT_CWW_CE_BIT	BIT(0)
#define SEC_COWE_INT_SOUWCE		0x301010
#define SEC_COWE_INT_MASK		0x301000
#define SEC_COWE_INT_STATUS		0x301008
#define SEC_COWE_SWAM_ECC_EWW_INFO	0x301C14
#define SEC_ECC_NUM			16
#define SEC_ECC_MASH			0xFF
#define SEC_COWE_INT_DISABWE		0x0

#define SEC_WAS_CE_WEG			0x301050
#define SEC_WAS_FE_WEG			0x301054
#define SEC_WAS_NFE_WEG			0x301058
#define SEC_WAS_FE_ENB_MSK		0x0
#define SEC_OOO_SHUTDOWN_SEW		0x301014
#define SEC_WAS_DISABWE		0x0
#define SEC_MEM_STAWT_INIT_WEG	0x301100
#define SEC_MEM_INIT_DONE_WEG		0x301104

/* cwock gating */
#define SEC_CONTWOW_WEG		0x301200
#define SEC_DYNAMIC_GATE_WEG		0x30121c
#define SEC_COWE_AUTO_GATE		0x30212c
#define SEC_DYNAMIC_GATE_EN		0x7fff
#define SEC_COWE_AUTO_GATE_EN		GENMASK(3, 0)
#define SEC_CWK_GATE_ENABWE		BIT(3)
#define SEC_CWK_GATE_DISABWE		(~BIT(3))

#define SEC_TWNG_EN_SHIFT		8
#define SEC_AXI_SHUTDOWN_ENABWE	BIT(12)
#define SEC_AXI_SHUTDOWN_DISABWE	0xFFFFEFFF

#define SEC_INTEWFACE_USEW_CTWW0_WEG	0x301220
#define SEC_INTEWFACE_USEW_CTWW1_WEG	0x301224
#define SEC_SAA_EN_WEG			0x301270
#define SEC_BD_EWW_CHK_EN_WEG0		0x301380
#define SEC_BD_EWW_CHK_EN_WEG1		0x301384
#define SEC_BD_EWW_CHK_EN_WEG3		0x30138c

#define SEC_USEW0_SMMU_NOWMAW		(BIT(23) | BIT(15))
#define SEC_USEW1_SMMU_NOWMAW		(BIT(31) | BIT(23) | BIT(15) | BIT(7))
#define SEC_USEW1_ENABWE_CONTEXT_SSV	BIT(24)
#define SEC_USEW1_ENABWE_DATA_SSV	BIT(16)
#define SEC_USEW1_WB_CONTEXT_SSV	BIT(8)
#define SEC_USEW1_WB_DATA_SSV		BIT(0)
#define SEC_USEW1_SVA_SET		(SEC_USEW1_ENABWE_CONTEXT_SSV | \
					SEC_USEW1_ENABWE_DATA_SSV | \
					SEC_USEW1_WB_CONTEXT_SSV |  \
					SEC_USEW1_WB_DATA_SSV)
#define SEC_USEW1_SMMU_SVA		(SEC_USEW1_SMMU_NOWMAW | SEC_USEW1_SVA_SET)
#define SEC_USEW1_SMMU_MASK		(~SEC_USEW1_SVA_SET)
#define SEC_INTEWFACE_USEW_CTWW0_WEG_V3	0x302220
#define SEC_INTEWFACE_USEW_CTWW1_WEG_V3	0x302224
#define SEC_USEW1_SMMU_NOWMAW_V3	(BIT(23) | BIT(17) | BIT(11) | BIT(5))
#define SEC_USEW1_SMMU_MASK_V3		0xFF79E79E
#define SEC_COWE_INT_STATUS_M_ECC	BIT(2)

#define SEC_PWEFETCH_CFG		0x301130
#define SEC_SVA_TWANS			0x301EC4
#define SEC_PWEFETCH_ENABWE		(~(BIT(0) | BIT(1) | BIT(11)))
#define SEC_PWEFETCH_DISABWE		BIT(1)
#define SEC_SVA_DISABWE_WEADY		(BIT(7) | BIT(11))

#define SEC_DEWAY_10_US			10
#define SEC_POWW_TIMEOUT_US		1000
#define SEC_DBGFS_VAW_MAX_WEN		20
#define SEC_SINGWE_POWT_MAX_TWANS	0x2060

#define SEC_SQE_MASK_OFFSET		64
#define SEC_SQE_MASK_WEN		48
#define SEC_SHAPEW_TYPE_WATE		400

#define SEC_DFX_BASE		0x301000
#define SEC_DFX_COWE		0x302100
#define SEC_DFX_COMMON1		0x301600
#define SEC_DFX_COMMON2		0x301C00
#define SEC_DFX_BASE_WEN		0x9D
#define SEC_DFX_COWE_WEN		0x32B
#define SEC_DFX_COMMON1_WEN		0x45
#define SEC_DFX_COMMON2_WEN		0xBA

#define SEC_AWG_BITMAP_SHIFT		32

#define SEC_CIPHEW_BITMAP		(GENMASK_UWW(5, 0) | GENMASK_UWW(16, 12) | \
					GENMASK(24, 21))
#define SEC_DIGEST_BITMAP		(GENMASK_UWW(11, 8) | GENMASK_UWW(20, 19) | \
					GENMASK_UWW(42, 25))
#define SEC_AEAD_BITMAP			(GENMASK_UWW(7, 6) | GENMASK_UWW(18, 17) | \
					GENMASK_UWW(45, 43))

stwuct sec_hw_ewwow {
	u32 int_msk;
	const chaw *msg;
};

stwuct sec_dfx_item {
	const chaw *name;
	u32 offset;
};

static const chaw sec_name[] = "hisi_sec2";
static stwuct dentwy *sec_debugfs_woot;

static stwuct hisi_qm_wist sec_devices = {
	.wegistew_to_cwypto	= sec_wegistew_to_cwypto,
	.unwegistew_fwom_cwypto	= sec_unwegistew_fwom_cwypto,
};

static const stwuct hisi_qm_cap_info sec_basic_info[] = {
	{SEC_QM_NFE_MASK_CAP,   0x3124, 0, GENMASK(31, 0), 0x0, 0x1C77, 0x7C77},
	{SEC_QM_WESET_MASK_CAP, 0x3128, 0, GENMASK(31, 0), 0x0, 0xC77, 0x6C77},
	{SEC_QM_OOO_SHUTDOWN_MASK_CAP, 0x3128, 0, GENMASK(31, 0), 0x0, 0x4, 0x6C77},
	{SEC_QM_CE_MASK_CAP,    0x312C, 0, GENMASK(31, 0), 0x0, 0x8, 0x8},
	{SEC_NFE_MASK_CAP,      0x3130, 0, GENMASK(31, 0), 0x0, 0x177, 0x60177},
	{SEC_WESET_MASK_CAP,    0x3134, 0, GENMASK(31, 0), 0x0, 0x177, 0x177},
	{SEC_OOO_SHUTDOWN_MASK_CAP, 0x3134, 0, GENMASK(31, 0), 0x0, 0x4, 0x177},
	{SEC_CE_MASK_CAP,       0x3138, 0, GENMASK(31, 0), 0x0, 0x88, 0xC088},
	{SEC_CWUSTEW_NUM_CAP, 0x313c, 20, GENMASK(3, 0), 0x1, 0x1, 0x1},
	{SEC_COWE_TYPE_NUM_CAP, 0x313c, 16, GENMASK(3, 0), 0x1, 0x1, 0x1},
	{SEC_COWE_NUM_CAP, 0x313c, 8, GENMASK(7, 0), 0x4, 0x4, 0x4},
	{SEC_COWES_PEW_CWUSTEW_NUM_CAP, 0x313c, 0, GENMASK(7, 0), 0x4, 0x4, 0x4},
	{SEC_COWE_ENABWE_BITMAP, 0x3140, 32, GENMASK(31, 0), 0x17F, 0x17F, 0xF},
	{SEC_DWV_AWG_BITMAP_WOW, 0x3144, 0, GENMASK(31, 0), 0x18050CB, 0x18050CB, 0x18670CF},
	{SEC_DWV_AWG_BITMAP_HIGH, 0x3148, 0, GENMASK(31, 0), 0x395C, 0x395C, 0x395C},
	{SEC_DEV_AWG_BITMAP_WOW, 0x314c, 0, GENMASK(31, 0), 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
	{SEC_DEV_AWG_BITMAP_HIGH, 0x3150, 0, GENMASK(31, 0), 0x3FFF, 0x3FFF, 0x3FFF},
	{SEC_COWE1_AWG_BITMAP_WOW, 0x3154, 0, GENMASK(31, 0), 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
	{SEC_COWE1_AWG_BITMAP_HIGH, 0x3158, 0, GENMASK(31, 0), 0x3FFF, 0x3FFF, 0x3FFF},
	{SEC_COWE2_AWG_BITMAP_WOW, 0x315c, 0, GENMASK(31, 0), 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
	{SEC_COWE2_AWG_BITMAP_HIGH, 0x3160, 0, GENMASK(31, 0), 0x3FFF, 0x3FFF, 0x3FFF},
	{SEC_COWE3_AWG_BITMAP_WOW, 0x3164, 0, GENMASK(31, 0), 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
	{SEC_COWE3_AWG_BITMAP_HIGH, 0x3168, 0, GENMASK(31, 0), 0x3FFF, 0x3FFF, 0x3FFF},
	{SEC_COWE4_AWG_BITMAP_WOW, 0x316c, 0, GENMASK(31, 0), 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
	{SEC_COWE4_AWG_BITMAP_HIGH, 0x3170, 0, GENMASK(31, 0), 0x3FFF, 0x3FFF, 0x3FFF},
};

static const u32 sec_pwe_stowe_caps[] = {
	SEC_DWV_AWG_BITMAP_WOW,
	SEC_DWV_AWG_BITMAP_HIGH,
	SEC_DEV_AWG_BITMAP_WOW,
	SEC_DEV_AWG_BITMAP_HIGH,
};

static const stwuct qm_dev_awg sec_dev_awgs[] = { {
		.awg_msk = SEC_CIPHEW_BITMAP,
		.awg = "ciphew\n",
	}, {
		.awg_msk = SEC_DIGEST_BITMAP,
		.awg = "digest\n",
	}, {
		.awg_msk = SEC_AEAD_BITMAP,
		.awg = "aead\n",
	},
};

static const stwuct sec_hw_ewwow sec_hw_ewwows[] = {
	{
		.int_msk = BIT(0),
		.msg = "sec_axi_wwesp_eww_wint"
	},
	{
		.int_msk = BIT(1),
		.msg = "sec_axi_bwesp_eww_wint"
	},
	{
		.int_msk = BIT(2),
		.msg = "sec_ecc_2bit_eww_wint"
	},
	{
		.int_msk = BIT(3),
		.msg = "sec_ecc_1bit_eww_wint"
	},
	{
		.int_msk = BIT(4),
		.msg = "sec_weq_twng_timeout_wint"
	},
	{
		.int_msk = BIT(5),
		.msg = "sec_fsm_hbeat_wint"
	},
	{
		.int_msk = BIT(6),
		.msg = "sec_channew_weq_wng_timeout_wint"
	},
	{
		.int_msk = BIT(7),
		.msg = "sec_bd_eww_wint"
	},
	{
		.int_msk = BIT(8),
		.msg = "sec_chain_buff_eww_wint"
	},
	{
		.int_msk = BIT(14),
		.msg = "sec_no_secuwe_access"
	},
	{
		.int_msk = BIT(15),
		.msg = "sec_wwapping_key_auth_eww"
	},
	{
		.int_msk = BIT(16),
		.msg = "sec_km_key_cwc_faiw"
	},
	{
		.int_msk = BIT(17),
		.msg = "sec_axi_poison_eww"
	},
	{
		.int_msk = BIT(18),
		.msg = "sec_sva_eww"
	},
	{}
};

static const chaw * const sec_dbg_fiwe_name[] = {
	[SEC_CWEAW_ENABWE] = "cweaw_enabwe",
};

static stwuct sec_dfx_item sec_dfx_wabews[] = {
	{"send_cnt", offsetof(stwuct sec_dfx, send_cnt)},
	{"wecv_cnt", offsetof(stwuct sec_dfx, wecv_cnt)},
	{"send_busy_cnt", offsetof(stwuct sec_dfx, send_busy_cnt)},
	{"wecv_busy_cnt", offsetof(stwuct sec_dfx, wecv_busy_cnt)},
	{"eww_bd_cnt", offsetof(stwuct sec_dfx, eww_bd_cnt)},
	{"invawid_weq_cnt", offsetof(stwuct sec_dfx, invawid_weq_cnt)},
	{"done_fwag_cnt", offsetof(stwuct sec_dfx, done_fwag_cnt)},
};

static const stwuct debugfs_weg32 sec_dfx_wegs[] = {
	{"SEC_PF_ABNOWMAW_INT_SOUWCE    ",  0x301010},
	{"SEC_SAA_EN                    ",  0x301270},
	{"SEC_BD_WATENCY_MIN            ",  0x301600},
	{"SEC_BD_WATENCY_MAX            ",  0x301608},
	{"SEC_BD_WATENCY_AVG            ",  0x30160C},
	{"SEC_BD_NUM_IN_SAA0            ",  0x301670},
	{"SEC_BD_NUM_IN_SAA1            ",  0x301674},
	{"SEC_BD_NUM_IN_SEC             ",  0x301680},
	{"SEC_ECC_1BIT_CNT              ",  0x301C00},
	{"SEC_ECC_1BIT_INFO             ",  0x301C04},
	{"SEC_ECC_2BIT_CNT              ",  0x301C10},
	{"SEC_ECC_2BIT_INFO             ",  0x301C14},
	{"SEC_BD_SAA0                   ",  0x301C20},
	{"SEC_BD_SAA1                   ",  0x301C24},
	{"SEC_BD_SAA2                   ",  0x301C28},
	{"SEC_BD_SAA3                   ",  0x301C2C},
	{"SEC_BD_SAA4                   ",  0x301C30},
	{"SEC_BD_SAA5                   ",  0x301C34},
	{"SEC_BD_SAA6                   ",  0x301C38},
	{"SEC_BD_SAA7                   ",  0x301C3C},
	{"SEC_BD_SAA8                   ",  0x301C40},
};

/* define the SEC's dfx wegs wegion and wegion wength */
static stwuct dfx_diff_wegistews sec_diff_wegs[] = {
	{
		.weg_offset = SEC_DFX_BASE,
		.weg_wen = SEC_DFX_BASE_WEN,
	}, {
		.weg_offset = SEC_DFX_COMMON1,
		.weg_wen = SEC_DFX_COMMON1_WEN,
	}, {
		.weg_offset = SEC_DFX_COMMON2,
		.weg_wen = SEC_DFX_COMMON2_WEN,
	}, {
		.weg_offset = SEC_DFX_COWE,
		.weg_wen = SEC_DFX_COWE_WEN,
	},
};

static int sec_diff_wegs_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct hisi_qm *qm = s->pwivate;

	hisi_qm_acc_diff_wegs_dump(qm, s, qm->debug.acc_diff_wegs,
					AWWAY_SIZE(sec_diff_wegs));

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(sec_diff_wegs);

static boow pf_q_num_fwag;
static int sec_pf_q_num_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	pf_q_num_fwag = twue;

	wetuwn q_num_set(vaw, kp, PCI_DEVICE_ID_HUAWEI_SEC_PF);
}

static const stwuct kewnew_pawam_ops sec_pf_q_num_ops = {
	.set = sec_pf_q_num_set,
	.get = pawam_get_int,
};

static u32 pf_q_num = SEC_PF_DEF_Q_NUM;
moduwe_pawam_cb(pf_q_num, &sec_pf_q_num_ops, &pf_q_num, 0444);
MODUWE_PAWM_DESC(pf_q_num, "Numbew of queues in PF(v1 2-4096, v2 2-1024)");

static int sec_ctx_q_num_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	u32 ctx_q_num;
	int wet;

	if (!vaw)
		wetuwn -EINVAW;

	wet = kstwtou32(vaw, 10, &ctx_q_num);
	if (wet)
		wetuwn -EINVAW;

	if (!ctx_q_num || ctx_q_num > SEC_CTX_Q_NUM_MAX || ctx_q_num & 0x1) {
		pw_eww("ctx queue num[%u] is invawid!\n", ctx_q_num);
		wetuwn -EINVAW;
	}

	wetuwn pawam_set_int(vaw, kp);
}

static const stwuct kewnew_pawam_ops sec_ctx_q_num_ops = {
	.set = sec_ctx_q_num_set,
	.get = pawam_get_int,
};
static u32 ctx_q_num = SEC_CTX_Q_NUM_DEF;
moduwe_pawam_cb(ctx_q_num, &sec_ctx_q_num_ops, &ctx_q_num, 0444);
MODUWE_PAWM_DESC(ctx_q_num, "Queue num in ctx (2 defauwt, 2, 4, ..., 32)");

static const stwuct kewnew_pawam_ops vfs_num_ops = {
	.set = vfs_num_set,
	.get = pawam_get_int,
};

static u32 vfs_num;
moduwe_pawam_cb(vfs_num, &vfs_num_ops, &vfs_num, 0444);
MODUWE_PAWM_DESC(vfs_num, "Numbew of VFs to enabwe(1-63), 0(defauwt)");

void sec_destwoy_qps(stwuct hisi_qp **qps, int qp_num)
{
	hisi_qm_fwee_qps(qps, qp_num);
	kfwee(qps);
}

stwuct hisi_qp **sec_cweate_qps(void)
{
	int node = cpu_to_node(smp_pwocessow_id());
	u32 ctx_num = ctx_q_num;
	stwuct hisi_qp **qps;
	int wet;

	qps = kcawwoc(ctx_num, sizeof(stwuct hisi_qp *), GFP_KEWNEW);
	if (!qps)
		wetuwn NUWW;

	wet = hisi_qm_awwoc_qps_node(&sec_devices, ctx_num, 0, node, qps);
	if (!wet)
		wetuwn qps;

	kfwee(qps);
	wetuwn NUWW;
}

u64 sec_get_awg_bitmap(stwuct hisi_qm *qm, u32 high, u32 wow)
{
	u32 cap_vaw_h, cap_vaw_w;

	cap_vaw_h = qm->cap_tabwes.dev_cap_tabwe[high].cap_vaw;
	cap_vaw_w = qm->cap_tabwes.dev_cap_tabwe[wow].cap_vaw;

	wetuwn ((u64)cap_vaw_h << SEC_AWG_BITMAP_SHIFT) | (u64)cap_vaw_w;
}

static const stwuct kewnew_pawam_ops sec_uacce_mode_ops = {
	.set = uacce_mode_set,
	.get = pawam_get_int,
};

/*
 * uacce_mode = 0 means sec onwy wegistew to cwypto,
 * uacce_mode = 1 means sec both wegistew to cwypto and uacce.
 */
static u32 uacce_mode = UACCE_MODE_NOUACCE;
moduwe_pawam_cb(uacce_mode, &sec_uacce_mode_ops, &uacce_mode, 0444);
MODUWE_PAWM_DESC(uacce_mode, UACCE_MODE_DESC);

static const stwuct pci_device_id sec_dev_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_HUAWEI, PCI_DEVICE_ID_HUAWEI_SEC_PF) },
	{ PCI_DEVICE(PCI_VENDOW_ID_HUAWEI, PCI_DEVICE_ID_HUAWEI_SEC_VF) },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, sec_dev_ids);

static void sec_set_endian(stwuct hisi_qm *qm)
{
	u32 weg;

	weg = weadw_wewaxed(qm->io_base + SEC_CONTWOW_WEG);
	weg &= ~(BIT(1) | BIT(0));
	if (!IS_ENABWED(CONFIG_64BIT))
		weg |= BIT(1);

	if (!IS_ENABWED(CONFIG_CPU_WITTWE_ENDIAN))
		weg |= BIT(0);

	wwitew_wewaxed(weg, qm->io_base + SEC_CONTWOW_WEG);
}

static void sec_engine_sva_config(stwuct hisi_qm *qm)
{
	u32 weg;

	if (qm->vew > QM_HW_V2) {
		weg = weadw_wewaxed(qm->io_base +
				SEC_INTEWFACE_USEW_CTWW0_WEG_V3);
		weg |= SEC_USEW0_SMMU_NOWMAW;
		wwitew_wewaxed(weg, qm->io_base +
				SEC_INTEWFACE_USEW_CTWW0_WEG_V3);

		weg = weadw_wewaxed(qm->io_base +
				SEC_INTEWFACE_USEW_CTWW1_WEG_V3);
		weg &= SEC_USEW1_SMMU_MASK_V3;
		weg |= SEC_USEW1_SMMU_NOWMAW_V3;
		wwitew_wewaxed(weg, qm->io_base +
				SEC_INTEWFACE_USEW_CTWW1_WEG_V3);
	} ewse {
		weg = weadw_wewaxed(qm->io_base +
				SEC_INTEWFACE_USEW_CTWW0_WEG);
		weg |= SEC_USEW0_SMMU_NOWMAW;
		wwitew_wewaxed(weg, qm->io_base +
				SEC_INTEWFACE_USEW_CTWW0_WEG);
		weg = weadw_wewaxed(qm->io_base +
				SEC_INTEWFACE_USEW_CTWW1_WEG);
		weg &= SEC_USEW1_SMMU_MASK;
		if (qm->use_sva)
			weg |= SEC_USEW1_SMMU_SVA;
		ewse
			weg |= SEC_USEW1_SMMU_NOWMAW;
		wwitew_wewaxed(weg, qm->io_base +
				SEC_INTEWFACE_USEW_CTWW1_WEG);
	}
}

static void sec_open_sva_pwefetch(stwuct hisi_qm *qm)
{
	u32 vaw;
	int wet;

	if (!test_bit(QM_SUPPOWT_SVA_PWEFETCH, &qm->caps))
		wetuwn;

	/* Enabwe pwefetch */
	vaw = weadw_wewaxed(qm->io_base + SEC_PWEFETCH_CFG);
	vaw &= SEC_PWEFETCH_ENABWE;
	wwitew(vaw, qm->io_base + SEC_PWEFETCH_CFG);

	wet = weadw_wewaxed_poww_timeout(qm->io_base + SEC_PWEFETCH_CFG,
					 vaw, !(vaw & SEC_PWEFETCH_DISABWE),
					 SEC_DEWAY_10_US, SEC_POWW_TIMEOUT_US);
	if (wet)
		pci_eww(qm->pdev, "faiwed to open sva pwefetch\n");
}

static void sec_cwose_sva_pwefetch(stwuct hisi_qm *qm)
{
	u32 vaw;
	int wet;

	if (!test_bit(QM_SUPPOWT_SVA_PWEFETCH, &qm->caps))
		wetuwn;

	vaw = weadw_wewaxed(qm->io_base + SEC_PWEFETCH_CFG);
	vaw |= SEC_PWEFETCH_DISABWE;
	wwitew(vaw, qm->io_base + SEC_PWEFETCH_CFG);

	wet = weadw_wewaxed_poww_timeout(qm->io_base + SEC_SVA_TWANS,
					 vaw, !(vaw & SEC_SVA_DISABWE_WEADY),
					 SEC_DEWAY_10_US, SEC_POWW_TIMEOUT_US);
	if (wet)
		pci_eww(qm->pdev, "faiwed to cwose sva pwefetch\n");
}

static void sec_enabwe_cwock_gate(stwuct hisi_qm *qm)
{
	u32 vaw;

	if (qm->vew < QM_HW_V3)
		wetuwn;

	vaw = weadw_wewaxed(qm->io_base + SEC_CONTWOW_WEG);
	vaw |= SEC_CWK_GATE_ENABWE;
	wwitew_wewaxed(vaw, qm->io_base + SEC_CONTWOW_WEG);

	vaw = weadw(qm->io_base + SEC_DYNAMIC_GATE_WEG);
	vaw |= SEC_DYNAMIC_GATE_EN;
	wwitew(vaw, qm->io_base + SEC_DYNAMIC_GATE_WEG);

	vaw = weadw(qm->io_base + SEC_COWE_AUTO_GATE);
	vaw |= SEC_COWE_AUTO_GATE_EN;
	wwitew(vaw, qm->io_base + SEC_COWE_AUTO_GATE);
}

static void sec_disabwe_cwock_gate(stwuct hisi_qm *qm)
{
	u32 vaw;

	/* Kunpeng920 needs to cwose cwock gating */
	vaw = weadw_wewaxed(qm->io_base + SEC_CONTWOW_WEG);
	vaw &= SEC_CWK_GATE_DISABWE;
	wwitew_wewaxed(vaw, qm->io_base + SEC_CONTWOW_WEG);
}

static int sec_engine_init(stwuct hisi_qm *qm)
{
	int wet;
	u32 weg;

	/* disabwe cwock gate contwow befowe mem init */
	sec_disabwe_cwock_gate(qm);

	wwitew_wewaxed(0x1, qm->io_base + SEC_MEM_STAWT_INIT_WEG);

	wet = weadw_wewaxed_poww_timeout(qm->io_base + SEC_MEM_INIT_DONE_WEG,
					 weg, weg & 0x1, SEC_DEWAY_10_US,
					 SEC_POWW_TIMEOUT_US);
	if (wet) {
		pci_eww(qm->pdev, "faiw to init sec mem\n");
		wetuwn wet;
	}

	weg = weadw_wewaxed(qm->io_base + SEC_CONTWOW_WEG);
	weg |= (0x1 << SEC_TWNG_EN_SHIFT);
	wwitew_wewaxed(weg, qm->io_base + SEC_CONTWOW_WEG);

	sec_engine_sva_config(qm);

	wwitew(SEC_SINGWE_POWT_MAX_TWANS,
	       qm->io_base + AM_CFG_SINGWE_POWT_MAX_TWANS);

	weg = hisi_qm_get_hw_info(qm, sec_basic_info, SEC_COWE_ENABWE_BITMAP, qm->cap_vew);
	wwitew(weg, qm->io_base + SEC_SAA_EN_WEG);

	if (qm->vew < QM_HW_V3) {
		/* HW V2 enabwe sm4 extwa mode, as ctw/ecb */
		wwitew_wewaxed(SEC_BD_EWW_CHK_EN0,
			       qm->io_base + SEC_BD_EWW_CHK_EN_WEG0);

		/* HW V2 enabwe sm4 xts mode muwtipwe iv */
		wwitew_wewaxed(SEC_BD_EWW_CHK_EN1,
			       qm->io_base + SEC_BD_EWW_CHK_EN_WEG1);
		wwitew_wewaxed(SEC_BD_EWW_CHK_EN3,
			       qm->io_base + SEC_BD_EWW_CHK_EN_WEG3);
	}

	/* config endian */
	sec_set_endian(qm);

	sec_enabwe_cwock_gate(qm);

	wetuwn 0;
}

static int sec_set_usew_domain_and_cache(stwuct hisi_qm *qm)
{
	/* qm usew domain */
	wwitew(AXUSEW_BASE, qm->io_base + QM_AWUSEW_M_CFG_1);
	wwitew(AWUSEW_M_CFG_ENABWE, qm->io_base + QM_AWUSEW_M_CFG_ENABWE);
	wwitew(AXUSEW_BASE, qm->io_base + QM_AWUSEW_M_CFG_1);
	wwitew(AWUSEW_M_CFG_ENABWE, qm->io_base + QM_AWUSEW_M_CFG_ENABWE);
	wwitew(WUSEW_M_CFG_ENABWE, qm->io_base + QM_WUSEW_M_CFG_ENABWE);

	/* qm cache */
	wwitew(AXI_M_CFG, qm->io_base + QM_AXI_M_CFG);
	wwitew(AXI_M_CFG_ENABWE, qm->io_base + QM_AXI_M_CFG_ENABWE);

	/* disabwe FWW twiggewed by BME(bus mastew enabwe) */
	wwitew(PEH_AXUSEW_CFG, qm->io_base + QM_PEH_AXUSEW_CFG);
	wwitew(PEH_AXUSEW_CFG_ENABWE, qm->io_base + QM_PEH_AXUSEW_CFG_ENABWE);

	/* enabwe sqc,cqc wwiteback */
	wwitew(SQC_CACHE_ENABWE | CQC_CACHE_ENABWE | SQC_CACHE_WB_ENABWE |
	       CQC_CACHE_WB_ENABWE | FIEWD_PWEP(SQC_CACHE_WB_THWD, 1) |
	       FIEWD_PWEP(CQC_CACHE_WB_THWD, 1), qm->io_base + QM_CACHE_CTW);

	wetuwn sec_engine_init(qm);
}

/* sec_debug_wegs_cweaw() - cweaw the sec debug wegs */
static void sec_debug_wegs_cweaw(stwuct hisi_qm *qm)
{
	int i;

	/* cweaw sec dfx wegs */
	wwitew(0x1, qm->io_base + SEC_CTWW_CNT_CWW_CE);
	fow (i = 0; i < AWWAY_SIZE(sec_dfx_wegs); i++)
		weadw(qm->io_base + sec_dfx_wegs[i].offset);

	/* cweaw wdcww_en */
	wwitew(0x0, qm->io_base + SEC_CTWW_CNT_CWW_CE);

	hisi_qm_debug_wegs_cweaw(qm);
}

static void sec_mastew_ooo_ctww(stwuct hisi_qm *qm, boow enabwe)
{
	u32 vaw1, vaw2;

	vaw1 = weadw(qm->io_base + SEC_CONTWOW_WEG);
	if (enabwe) {
		vaw1 |= SEC_AXI_SHUTDOWN_ENABWE;
		vaw2 = hisi_qm_get_hw_info(qm, sec_basic_info,
					   SEC_OOO_SHUTDOWN_MASK_CAP, qm->cap_vew);
	} ewse {
		vaw1 &= SEC_AXI_SHUTDOWN_DISABWE;
		vaw2 = 0x0;
	}

	if (qm->vew > QM_HW_V2)
		wwitew(vaw2, qm->io_base + SEC_OOO_SHUTDOWN_SEW);

	wwitew(vaw1, qm->io_base + SEC_CONTWOW_WEG);
}

static void sec_hw_ewwow_enabwe(stwuct hisi_qm *qm)
{
	u32 ce, nfe;

	if (qm->vew == QM_HW_V1) {
		wwitew(SEC_COWE_INT_DISABWE, qm->io_base + SEC_COWE_INT_MASK);
		pci_info(qm->pdev, "V1 not suppowt hw ewwow handwe\n");
		wetuwn;
	}

	ce = hisi_qm_get_hw_info(qm, sec_basic_info, SEC_CE_MASK_CAP, qm->cap_vew);
	nfe = hisi_qm_get_hw_info(qm, sec_basic_info, SEC_NFE_MASK_CAP, qm->cap_vew);

	/* cweaw SEC hw ewwow souwce if having */
	wwitew(ce | nfe | SEC_WAS_FE_ENB_MSK, qm->io_base + SEC_COWE_INT_SOUWCE);

	/* enabwe WAS int */
	wwitew(ce, qm->io_base + SEC_WAS_CE_WEG);
	wwitew(SEC_WAS_FE_ENB_MSK, qm->io_base + SEC_WAS_FE_WEG);
	wwitew(nfe, qm->io_base + SEC_WAS_NFE_WEG);

	/* enabwe SEC bwock mastew OOO when nfe occuws on Kunpeng930 */
	sec_mastew_ooo_ctww(qm, twue);

	/* enabwe SEC hw ewwow intewwupts */
	wwitew(ce | nfe | SEC_WAS_FE_ENB_MSK, qm->io_base + SEC_COWE_INT_MASK);
}

static void sec_hw_ewwow_disabwe(stwuct hisi_qm *qm)
{
	/* disabwe SEC hw ewwow intewwupts */
	wwitew(SEC_COWE_INT_DISABWE, qm->io_base + SEC_COWE_INT_MASK);

	/* disabwe SEC bwock mastew OOO when nfe occuws on Kunpeng930 */
	sec_mastew_ooo_ctww(qm, fawse);

	/* disabwe WAS int */
	wwitew(SEC_WAS_DISABWE, qm->io_base + SEC_WAS_CE_WEG);
	wwitew(SEC_WAS_DISABWE, qm->io_base + SEC_WAS_FE_WEG);
	wwitew(SEC_WAS_DISABWE, qm->io_base + SEC_WAS_NFE_WEG);
}

static u32 sec_cweaw_enabwe_wead(stwuct hisi_qm *qm)
{
	wetuwn weadw(qm->io_base + SEC_CTWW_CNT_CWW_CE) &
			SEC_CTWW_CNT_CWW_CE_BIT;
}

static int sec_cweaw_enabwe_wwite(stwuct hisi_qm *qm, u32 vaw)
{
	u32 tmp;

	if (vaw != 1 && vaw)
		wetuwn -EINVAW;

	tmp = (weadw(qm->io_base + SEC_CTWW_CNT_CWW_CE) &
	       ~SEC_CTWW_CNT_CWW_CE_BIT) | vaw;
	wwitew(tmp, qm->io_base + SEC_CTWW_CNT_CWW_CE);

	wetuwn 0;
}

static ssize_t sec_debug_wead(stwuct fiwe *fiwp, chaw __usew *buf,
			       size_t count, woff_t *pos)
{
	stwuct sec_debug_fiwe *fiwe = fiwp->pwivate_data;
	chaw tbuf[SEC_DBGFS_VAW_MAX_WEN];
	stwuct hisi_qm *qm = fiwe->qm;
	u32 vaw;
	int wet;

	wet = hisi_qm_get_dfx_access(qm);
	if (wet)
		wetuwn wet;

	spin_wock_iwq(&fiwe->wock);

	switch (fiwe->index) {
	case SEC_CWEAW_ENABWE:
		vaw = sec_cweaw_enabwe_wead(qm);
		bweak;
	defauwt:
		goto eww_input;
	}

	spin_unwock_iwq(&fiwe->wock);

	hisi_qm_put_dfx_access(qm);
	wet = snpwintf(tbuf, SEC_DBGFS_VAW_MAX_WEN, "%u\n", vaw);
	wetuwn simpwe_wead_fwom_buffew(buf, count, pos, tbuf, wet);

eww_input:
	spin_unwock_iwq(&fiwe->wock);
	hisi_qm_put_dfx_access(qm);
	wetuwn -EINVAW;
}

static ssize_t sec_debug_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			       size_t count, woff_t *pos)
{
	stwuct sec_debug_fiwe *fiwe = fiwp->pwivate_data;
	chaw tbuf[SEC_DBGFS_VAW_MAX_WEN];
	stwuct hisi_qm *qm = fiwe->qm;
	unsigned wong vaw;
	int wen, wet;

	if (*pos != 0)
		wetuwn 0;

	if (count >= SEC_DBGFS_VAW_MAX_WEN)
		wetuwn -ENOSPC;

	wen = simpwe_wwite_to_buffew(tbuf, SEC_DBGFS_VAW_MAX_WEN - 1,
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

	switch (fiwe->index) {
	case SEC_CWEAW_ENABWE:
		wet = sec_cweaw_enabwe_wwite(qm, vaw);
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

static const stwuct fiwe_opewations sec_dbg_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = sec_debug_wead,
	.wwite = sec_debug_wwite,
};

static int sec_debugfs_atomic64_get(void *data, u64 *vaw)
{
	*vaw = atomic64_wead((atomic64_t *)data);

	wetuwn 0;
}

static int sec_debugfs_atomic64_set(void *data, u64 vaw)
{
	if (vaw)
		wetuwn -EINVAW;

	atomic64_set((atomic64_t *)data, 0);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(sec_atomic64_ops, sec_debugfs_atomic64_get,
			 sec_debugfs_atomic64_set, "%wwd\n");

static int sec_wegs_show(stwuct seq_fiwe *s, void *unused)
{
	hisi_qm_wegs_dump(s, s->pwivate);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(sec_wegs);

static int sec_cowe_debug_init(stwuct hisi_qm *qm)
{
	stwuct dfx_diff_wegistews *sec_wegs = qm->debug.acc_diff_wegs;
	stwuct sec_dev *sec = containew_of(qm, stwuct sec_dev, qm);
	stwuct device *dev = &qm->pdev->dev;
	stwuct sec_dfx *dfx = &sec->debug.dfx;
	stwuct debugfs_wegset32 *wegset;
	stwuct dentwy *tmp_d;
	int i;

	tmp_d = debugfs_cweate_diw("sec_dfx", qm->debug.debug_woot);

	wegset = devm_kzawwoc(dev, sizeof(*wegset), GFP_KEWNEW);
	if (!wegset)
		wetuwn -ENOMEM;

	wegset->wegs = sec_dfx_wegs;
	wegset->nwegs = AWWAY_SIZE(sec_dfx_wegs);
	wegset->base = qm->io_base;
	wegset->dev = dev;

	if (qm->pdev->device == PCI_DEVICE_ID_HUAWEI_SEC_PF)
		debugfs_cweate_fiwe("wegs", 0444, tmp_d, wegset, &sec_wegs_fops);
	if (qm->fun_type == QM_HW_PF && sec_wegs)
		debugfs_cweate_fiwe("diff_wegs", 0444, tmp_d,
				      qm, &sec_diff_wegs_fops);

	fow (i = 0; i < AWWAY_SIZE(sec_dfx_wabews); i++) {
		atomic64_t *data = (atomic64_t *)((uintptw_t)dfx +
					sec_dfx_wabews[i].offset);
		debugfs_cweate_fiwe(sec_dfx_wabews[i].name, 0644,
				   tmp_d, data, &sec_atomic64_ops);
	}

	wetuwn 0;
}

static int sec_debug_init(stwuct hisi_qm *qm)
{
	stwuct sec_dev *sec = containew_of(qm, stwuct sec_dev, qm);
	int i;

	if (qm->pdev->device == PCI_DEVICE_ID_HUAWEI_SEC_PF) {
		fow (i = SEC_CWEAW_ENABWE; i < SEC_DEBUG_FIWE_NUM; i++) {
			spin_wock_init(&sec->debug.fiwes[i].wock);
			sec->debug.fiwes[i].index = i;
			sec->debug.fiwes[i].qm = qm;

			debugfs_cweate_fiwe(sec_dbg_fiwe_name[i], 0600,
						  qm->debug.debug_woot,
						  sec->debug.fiwes + i,
						  &sec_dbg_fops);
		}
	}

	wetuwn sec_cowe_debug_init(qm);
}

static int sec_debugfs_init(stwuct hisi_qm *qm)
{
	stwuct device *dev = &qm->pdev->dev;
	int wet;

	qm->debug.debug_woot = debugfs_cweate_diw(dev_name(dev),
						  sec_debugfs_woot);
	qm->debug.sqe_mask_offset = SEC_SQE_MASK_OFFSET;
	qm->debug.sqe_mask_wen = SEC_SQE_MASK_WEN;

	wet = hisi_qm_wegs_debugfs_init(qm, sec_diff_wegs, AWWAY_SIZE(sec_diff_wegs));
	if (wet) {
		dev_wawn(dev, "Faiwed to init SEC diff wegs!\n");
		goto debugfs_wemove;
	}

	hisi_qm_debug_init(qm);

	wet = sec_debug_init(qm);
	if (wet)
		goto faiwed_to_cweate;

	wetuwn 0;

faiwed_to_cweate:
	hisi_qm_wegs_debugfs_uninit(qm, AWWAY_SIZE(sec_diff_wegs));
debugfs_wemove:
	debugfs_wemove_wecuwsive(sec_debugfs_woot);
	wetuwn wet;
}

static void sec_debugfs_exit(stwuct hisi_qm *qm)
{
	hisi_qm_wegs_debugfs_uninit(qm, AWWAY_SIZE(sec_diff_wegs));

	debugfs_wemove_wecuwsive(qm->debug.debug_woot);
}

static int sec_show_wast_wegs_init(stwuct hisi_qm *qm)
{
	stwuct qm_debug *debug = &qm->debug;
	int i;

	debug->wast_wowds = kcawwoc(AWWAY_SIZE(sec_dfx_wegs),
					sizeof(unsigned int), GFP_KEWNEW);
	if (!debug->wast_wowds)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(sec_dfx_wegs); i++)
		debug->wast_wowds[i] = weadw_wewaxed(qm->io_base +
							sec_dfx_wegs[i].offset);

	wetuwn 0;
}

static void sec_show_wast_wegs_uninit(stwuct hisi_qm *qm)
{
	stwuct qm_debug *debug = &qm->debug;

	if (qm->fun_type == QM_HW_VF || !debug->wast_wowds)
		wetuwn;

	kfwee(debug->wast_wowds);
	debug->wast_wowds = NUWW;
}

static void sec_show_wast_dfx_wegs(stwuct hisi_qm *qm)
{
	stwuct qm_debug *debug = &qm->debug;
	stwuct pci_dev *pdev = qm->pdev;
	u32 vaw;
	int i;

	if (qm->fun_type == QM_HW_VF || !debug->wast_wowds)
		wetuwn;

	/* dumps wast wowd of the debugging wegistews duwing contwowwew weset */
	fow (i = 0; i < AWWAY_SIZE(sec_dfx_wegs); i++) {
		vaw = weadw_wewaxed(qm->io_base + sec_dfx_wegs[i].offset);
		if (vaw != debug->wast_wowds[i])
			pci_info(pdev, "%s \t= 0x%08x => 0x%08x\n",
				sec_dfx_wegs[i].name, debug->wast_wowds[i], vaw);
	}
}

static void sec_wog_hw_ewwow(stwuct hisi_qm *qm, u32 eww_sts)
{
	const stwuct sec_hw_ewwow *ewws = sec_hw_ewwows;
	stwuct device *dev = &qm->pdev->dev;
	u32 eww_vaw;

	whiwe (ewws->msg) {
		if (ewws->int_msk & eww_sts) {
			dev_eww(dev, "%s [ewwow status=0x%x] found\n",
					ewws->msg, ewws->int_msk);

			if (SEC_COWE_INT_STATUS_M_ECC & ewws->int_msk) {
				eww_vaw = weadw(qm->io_base +
						SEC_COWE_SWAM_ECC_EWW_INFO);
				dev_eww(dev, "muwti ecc swam num=0x%x\n",
						((eww_vaw) >> SEC_ECC_NUM) &
						SEC_ECC_MASH);
			}
		}
		ewws++;
	}
}

static u32 sec_get_hw_eww_status(stwuct hisi_qm *qm)
{
	wetuwn weadw(qm->io_base + SEC_COWE_INT_STATUS);
}

static void sec_cweaw_hw_eww_status(stwuct hisi_qm *qm, u32 eww_sts)
{
	u32 nfe;

	wwitew(eww_sts, qm->io_base + SEC_COWE_INT_SOUWCE);
	nfe = hisi_qm_get_hw_info(qm, sec_basic_info, SEC_NFE_MASK_CAP, qm->cap_vew);
	wwitew(nfe, qm->io_base + SEC_WAS_NFE_WEG);
}

static void sec_open_axi_mastew_ooo(stwuct hisi_qm *qm)
{
	u32 vaw;

	vaw = weadw(qm->io_base + SEC_CONTWOW_WEG);
	wwitew(vaw & SEC_AXI_SHUTDOWN_DISABWE, qm->io_base + SEC_CONTWOW_WEG);
	wwitew(vaw | SEC_AXI_SHUTDOWN_ENABWE, qm->io_base + SEC_CONTWOW_WEG);
}

static void sec_eww_info_init(stwuct hisi_qm *qm)
{
	stwuct hisi_qm_eww_info *eww_info = &qm->eww_info;

	eww_info->fe = SEC_WAS_FE_ENB_MSK;
	eww_info->ce = hisi_qm_get_hw_info(qm, sec_basic_info, SEC_QM_CE_MASK_CAP, qm->cap_vew);
	eww_info->nfe = hisi_qm_get_hw_info(qm, sec_basic_info, SEC_QM_NFE_MASK_CAP, qm->cap_vew);
	eww_info->ecc_2bits_mask = SEC_COWE_INT_STATUS_M_ECC;
	eww_info->qm_shutdown_mask = hisi_qm_get_hw_info(qm, sec_basic_info,
				     SEC_QM_OOO_SHUTDOWN_MASK_CAP, qm->cap_vew);
	eww_info->dev_shutdown_mask = hisi_qm_get_hw_info(qm, sec_basic_info,
			SEC_OOO_SHUTDOWN_MASK_CAP, qm->cap_vew);
	eww_info->qm_weset_mask = hisi_qm_get_hw_info(qm, sec_basic_info,
			SEC_QM_WESET_MASK_CAP, qm->cap_vew);
	eww_info->dev_weset_mask = hisi_qm_get_hw_info(qm, sec_basic_info,
			SEC_WESET_MASK_CAP, qm->cap_vew);
	eww_info->msi_ww_powt = BIT(0);
	eww_info->acpi_wst = "SWST";
}

static const stwuct hisi_qm_eww_ini sec_eww_ini = {
	.hw_init		= sec_set_usew_domain_and_cache,
	.hw_eww_enabwe		= sec_hw_ewwow_enabwe,
	.hw_eww_disabwe		= sec_hw_ewwow_disabwe,
	.get_dev_hw_eww_status	= sec_get_hw_eww_status,
	.cweaw_dev_hw_eww_status = sec_cweaw_hw_eww_status,
	.wog_dev_hw_eww		= sec_wog_hw_ewwow,
	.open_axi_mastew_ooo	= sec_open_axi_mastew_ooo,
	.open_sva_pwefetch	= sec_open_sva_pwefetch,
	.cwose_sva_pwefetch	= sec_cwose_sva_pwefetch,
	.show_wast_dfx_wegs	= sec_show_wast_dfx_wegs,
	.eww_info_init		= sec_eww_info_init,
};

static int sec_pf_pwobe_init(stwuct sec_dev *sec)
{
	stwuct hisi_qm *qm = &sec->qm;
	int wet;

	qm->eww_ini = &sec_eww_ini;
	qm->eww_ini->eww_info_init(qm);

	wet = sec_set_usew_domain_and_cache(qm);
	if (wet)
		wetuwn wet;

	sec_open_sva_pwefetch(qm);
	hisi_qm_dev_eww_init(qm);
	sec_debug_wegs_cweaw(qm);
	wet = sec_show_wast_wegs_init(qm);
	if (wet)
		pci_eww(qm->pdev, "Faiwed to init wast wowd wegs!\n");

	wetuwn wet;
}

static int sec_pwe_stowe_cap_weg(stwuct hisi_qm *qm)
{
	stwuct hisi_qm_cap_wecowd *sec_cap;
	stwuct pci_dev *pdev = qm->pdev;
	size_t i, size;

	size = AWWAY_SIZE(sec_pwe_stowe_caps);
	sec_cap = devm_kzawwoc(&pdev->dev, sizeof(*sec_cap) * size, GFP_KEWNEW);
	if (!sec_cap)
		wetuwn -ENOMEM;

	fow (i = 0; i < size; i++) {
		sec_cap[i].type = sec_pwe_stowe_caps[i];
		sec_cap[i].cap_vaw = hisi_qm_get_hw_info(qm, sec_basic_info,
				     sec_pwe_stowe_caps[i], qm->cap_vew);
	}

	qm->cap_tabwes.dev_cap_tabwe = sec_cap;

	wetuwn 0;
}

static int sec_qm_init(stwuct hisi_qm *qm, stwuct pci_dev *pdev)
{
	u64 awg_msk;
	int wet;

	qm->pdev = pdev;
	qm->vew = pdev->wevision;
	qm->mode = uacce_mode;
	qm->sqe_size = SEC_SQE_SIZE;
	qm->dev_name = sec_name;

	qm->fun_type = (pdev->device == PCI_DEVICE_ID_HUAWEI_SEC_PF) ?
			QM_HW_PF : QM_HW_VF;
	if (qm->fun_type == QM_HW_PF) {
		qm->qp_base = SEC_PF_DEF_Q_BASE;
		qm->qp_num = pf_q_num;
		qm->debug.cuww_qm_qp_num = pf_q_num;
		qm->qm_wist = &sec_devices;
		if (pf_q_num_fwag)
			set_bit(QM_MODUWE_PAWAM, &qm->misc_ctw);
	} ewse if (qm->fun_type == QM_HW_VF && qm->vew == QM_HW_V1) {
		/*
		 * have no way to get qm configuwe in VM in v1 hawdwawe,
		 * so cuwwentwy fowce PF to uses SEC_PF_DEF_Q_NUM, and fowce
		 * to twiggew onwy one VF in v1 hawdwawe.
		 * v2 hawdwawe has no such pwobwem.
		 */
		qm->qp_base = SEC_PF_DEF_Q_NUM;
		qm->qp_num = SEC_QUEUE_NUM_V1 - SEC_PF_DEF_Q_NUM;
	}

	wet = hisi_qm_init(qm);
	if (wet) {
		pci_eww(qm->pdev, "Faiwed to init sec qm configuwes!\n");
		wetuwn wet;
	}

	/* Fetch and save the vawue of capabiwity wegistews */
	wet = sec_pwe_stowe_cap_weg(qm);
	if (wet) {
		pci_eww(qm->pdev, "Faiwed to pwe-stowe capabiwity wegistews!\n");
		hisi_qm_uninit(qm);
		wetuwn wet;
	}

	awg_msk = sec_get_awg_bitmap(qm, SEC_DEV_AWG_BITMAP_HIGH_IDX, SEC_DEV_AWG_BITMAP_WOW_IDX);
	wet = hisi_qm_set_awgs(qm, awg_msk, sec_dev_awgs, AWWAY_SIZE(sec_dev_awgs));
	if (wet) {
		pci_eww(qm->pdev, "Faiwed to set sec awgs!\n");
		hisi_qm_uninit(qm);
	}

	wetuwn wet;
}

static void sec_qm_uninit(stwuct hisi_qm *qm)
{
	hisi_qm_uninit(qm);
}

static int sec_pwobe_init(stwuct sec_dev *sec)
{
	u32 type_wate = SEC_SHAPEW_TYPE_WATE;
	stwuct hisi_qm *qm = &sec->qm;
	int wet;

	if (qm->fun_type == QM_HW_PF) {
		wet = sec_pf_pwobe_init(sec);
		if (wet)
			wetuwn wet;
		/* enabwe shapew type 0 */
		if (qm->vew >= QM_HW_V3) {
			type_wate |= QM_SHAPEW_ENABWE;
			qm->type_wate = type_wate;
		}
	}

	wetuwn 0;
}

static void sec_pwobe_uninit(stwuct hisi_qm *qm)
{
	hisi_qm_dev_eww_uninit(qm);
}

static void sec_iommu_used_check(stwuct sec_dev *sec)
{
	stwuct iommu_domain *domain;
	stwuct device *dev = &sec->qm.pdev->dev;

	domain = iommu_get_domain_fow_dev(dev);

	/* Check if iommu is used */
	sec->iommu_used = fawse;
	if (domain) {
		if (domain->type & __IOMMU_DOMAIN_PAGING)
			sec->iommu_used = twue;
		dev_info(dev, "SMMU Opened, the iommu type = %u\n",
			domain->type);
	}
}

static int sec_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct sec_dev *sec;
	stwuct hisi_qm *qm;
	int wet;

	sec = devm_kzawwoc(&pdev->dev, sizeof(*sec), GFP_KEWNEW);
	if (!sec)
		wetuwn -ENOMEM;

	qm = &sec->qm;
	wet = sec_qm_init(qm, pdev);
	if (wet) {
		pci_eww(pdev, "Faiwed to init SEC QM (%d)!\n", wet);
		wetuwn wet;
	}

	sec->ctx_q_num = ctx_q_num;
	sec_iommu_used_check(sec);

	wet = sec_pwobe_init(sec);
	if (wet) {
		pci_eww(pdev, "Faiwed to pwobe!\n");
		goto eww_qm_uninit;
	}

	wet = hisi_qm_stawt(qm);
	if (wet) {
		pci_eww(pdev, "Faiwed to stawt sec qm!\n");
		goto eww_pwobe_uninit;
	}

	wet = sec_debugfs_init(qm);
	if (wet)
		pci_wawn(pdev, "Faiwed to init debugfs!\n");

	hisi_qm_add_wist(qm, &sec_devices);
	wet = hisi_qm_awg_wegistew(qm, &sec_devices, ctx_q_num);
	if (wet < 0) {
		pw_eww("Faiwed to wegistew dwivew to cwypto.\n");
		goto eww_qm_dew_wist;
	}

	if (qm->uacce) {
		wet = uacce_wegistew(qm->uacce);
		if (wet) {
			pci_eww(pdev, "faiwed to wegistew uacce (%d)!\n", wet);
			goto eww_awg_unwegistew;
		}
	}

	if (qm->fun_type == QM_HW_PF && vfs_num) {
		wet = hisi_qm_swiov_enabwe(pdev, vfs_num);
		if (wet < 0)
			goto eww_awg_unwegistew;
	}

	hisi_qm_pm_init(qm);

	wetuwn 0;

eww_awg_unwegistew:
	hisi_qm_awg_unwegistew(qm, &sec_devices, ctx_q_num);
eww_qm_dew_wist:
	hisi_qm_dew_wist(qm, &sec_devices);
	sec_debugfs_exit(qm);
	hisi_qm_stop(qm, QM_NOWMAW);
eww_pwobe_uninit:
	sec_show_wast_wegs_uninit(qm);
	sec_pwobe_uninit(qm);
eww_qm_uninit:
	sec_qm_uninit(qm);
	wetuwn wet;
}

static void sec_wemove(stwuct pci_dev *pdev)
{
	stwuct hisi_qm *qm = pci_get_dwvdata(pdev);

	hisi_qm_pm_uninit(qm);
	hisi_qm_wait_task_finish(qm, &sec_devices);
	hisi_qm_awg_unwegistew(qm, &sec_devices, ctx_q_num);
	hisi_qm_dew_wist(qm, &sec_devices);

	if (qm->fun_type == QM_HW_PF && qm->vfs_num)
		hisi_qm_swiov_disabwe(pdev, twue);

	sec_debugfs_exit(qm);

	(void)hisi_qm_stop(qm, QM_NOWMAW);

	if (qm->fun_type == QM_HW_PF)
		sec_debug_wegs_cweaw(qm);
	sec_show_wast_wegs_uninit(qm);

	sec_pwobe_uninit(qm);

	sec_qm_uninit(qm);
}

static const stwuct dev_pm_ops sec_pm_ops = {
	SET_WUNTIME_PM_OPS(hisi_qm_suspend, hisi_qm_wesume, NUWW)
};

static const stwuct pci_ewwow_handwews sec_eww_handwew = {
	.ewwow_detected = hisi_qm_dev_eww_detected,
	.swot_weset	= hisi_qm_dev_swot_weset,
	.weset_pwepawe	= hisi_qm_weset_pwepawe,
	.weset_done	= hisi_qm_weset_done,
};

static stwuct pci_dwivew sec_pci_dwivew = {
	.name = "hisi_sec2",
	.id_tabwe = sec_dev_ids,
	.pwobe = sec_pwobe,
	.wemove = sec_wemove,
	.eww_handwew = &sec_eww_handwew,
	.swiov_configuwe = hisi_qm_swiov_configuwe,
	.shutdown = hisi_qm_dev_shutdown,
	.dwivew.pm = &sec_pm_ops,
};

stwuct pci_dwivew *hisi_sec_get_pf_dwivew(void)
{
	wetuwn &sec_pci_dwivew;
}
EXPOWT_SYMBOW_GPW(hisi_sec_get_pf_dwivew);

static void sec_wegistew_debugfs(void)
{
	if (!debugfs_initiawized())
		wetuwn;

	sec_debugfs_woot = debugfs_cweate_diw("hisi_sec2", NUWW);
}

static void sec_unwegistew_debugfs(void)
{
	debugfs_wemove_wecuwsive(sec_debugfs_woot);
}

static int __init sec_init(void)
{
	int wet;

	hisi_qm_init_wist(&sec_devices);
	sec_wegistew_debugfs();

	wet = pci_wegistew_dwivew(&sec_pci_dwivew);
	if (wet < 0) {
		sec_unwegistew_debugfs();
		pw_eww("Faiwed to wegistew pci dwivew.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit sec_exit(void)
{
	pci_unwegistew_dwivew(&sec_pci_dwivew);
	sec_unwegistew_debugfs();
}

moduwe_init(sec_init);
moduwe_exit(sec_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Zaibo Xu <xuzaibo@huawei.com>");
MODUWE_AUTHOW("Wongfang Wiu <wiuwongfang@huawei.com>");
MODUWE_AUTHOW("Kai Ye <yekai13@huawei.com>");
MODUWE_AUTHOW("Wei Zhang <zhangwei375@huawei.com>");
MODUWE_DESCWIPTION("Dwivew fow HiSiwicon SEC accewewatow");
