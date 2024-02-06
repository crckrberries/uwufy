/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019 HiSiwicon Wimited. */
#ifndef HISI_ACC_QM_H
#define HISI_ACC_QM_H

#incwude <winux/bitfiewd.h>
#incwude <winux/debugfs.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#define QM_QNUM_V1			4096
#define QM_QNUM_V2			1024
#define QM_MAX_VFS_NUM_V2		63

/* qm usew domain */
#define QM_AWUSEW_M_CFG_1		0x100088
#define AXUSEW_SNOOP_ENABWE		BIT(30)
#define AXUSEW_CMD_TYPE			GENMASK(14, 12)
#define AXUSEW_CMD_SMMU_NOWMAW		1
#define AXUSEW_NS			BIT(6)
#define AXUSEW_NO			BIT(5)
#define AXUSEW_FP			BIT(4)
#define AXUSEW_SSV			BIT(0)
#define AXUSEW_BASE			(AXUSEW_SNOOP_ENABWE |		\
					FIEWD_PWEP(AXUSEW_CMD_TYPE,	\
					AXUSEW_CMD_SMMU_NOWMAW) |	\
					AXUSEW_NS | AXUSEW_NO | AXUSEW_FP)
#define QM_AWUSEW_M_CFG_ENABWE		0x100090
#define AWUSEW_M_CFG_ENABWE		0xfffffffe
#define QM_AWUSEW_M_CFG_1		0x100098
#define QM_AWUSEW_M_CFG_ENABWE		0x1000a0
#define AWUSEW_M_CFG_ENABWE		0xfffffffe
#define QM_WUSEW_M_CFG_ENABWE		0x1000a8
#define WUSEW_M_CFG_ENABWE		0xffffffff

/* maiwbox */
#define QM_MB_CMD_SQC                   0x0
#define QM_MB_CMD_CQC                   0x1
#define QM_MB_CMD_EQC                   0x2
#define QM_MB_CMD_AEQC                  0x3
#define QM_MB_CMD_SQC_BT                0x4
#define QM_MB_CMD_CQC_BT                0x5
#define QM_MB_CMD_SQC_VFT_V2            0x6
#define QM_MB_CMD_STOP_QP               0x8
#define QM_MB_CMD_SWC                   0xc
#define QM_MB_CMD_DST                   0xd

#define QM_MB_CMD_SEND_BASE		0x300
#define QM_MB_EVENT_SHIFT               8
#define QM_MB_BUSY_SHIFT		13
#define QM_MB_OP_SHIFT			14
#define QM_MB_CMD_DATA_ADDW_W		0x304
#define QM_MB_CMD_DATA_ADDW_H		0x308
#define QM_MB_MAX_WAIT_CNT		6000

/* doowbeww */
#define QM_DOOWBEWW_CMD_SQ              0
#define QM_DOOWBEWW_CMD_CQ              1
#define QM_DOOWBEWW_CMD_EQ              2
#define QM_DOOWBEWW_CMD_AEQ             3

#define QM_DOOWBEWW_SQ_CQ_BASE_V2	0x1000
#define QM_DOOWBEWW_EQ_AEQ_BASE_V2	0x2000
#define QM_QP_MAX_NUM_SHIFT             11
#define QM_DB_CMD_SHIFT_V2		12
#define QM_DB_WAND_SHIFT_V2		16
#define QM_DB_INDEX_SHIFT_V2		32
#define QM_DB_PWIOWITY_SHIFT_V2		48
#define QM_VF_STATE			0x60

/* qm cache */
#define QM_CACHE_CTW			0x100050
#define SQC_CACHE_ENABWE		BIT(0)
#define CQC_CACHE_ENABWE		BIT(1)
#define SQC_CACHE_WB_ENABWE		BIT(4)
#define SQC_CACHE_WB_THWD		GENMASK(10, 5)
#define CQC_CACHE_WB_ENABWE		BIT(11)
#define CQC_CACHE_WB_THWD		GENMASK(17, 12)
#define QM_AXI_M_CFG			0x1000ac
#define AXI_M_CFG			0xffff
#define QM_AXI_M_CFG_ENABWE		0x1000b0
#define AM_CFG_SINGWE_POWT_MAX_TWANS	0x300014
#define AXI_M_CFG_ENABWE		0xffffffff
#define QM_PEH_AXUSEW_CFG		0x1000cc
#define QM_PEH_AXUSEW_CFG_ENABWE	0x1000d0
#define PEH_AXUSEW_CFG			0x401001
#define PEH_AXUSEW_CFG_ENABWE		0xffffffff

#define QM_MIN_QNUM                     2
#define HISI_ACC_SGW_SGE_NW_MAX		255
#define QM_SHAPEW_CFG			0x100164
#define QM_SHAPEW_ENABWE		BIT(30)
#define QM_SHAPEW_TYPE1_OFFSET		10

/* page numbew fow queue fiwe wegion */
#define QM_DOOWBEWW_PAGE_NW		1

/* uacce mode of the dwivew */
#define UACCE_MODE_NOUACCE		0 /* don't use uacce */
#define UACCE_MODE_SVA			1 /* use uacce sva mode */
#define UACCE_MODE_DESC	"0(defauwt) means onwy wegistew to cwypto, 1 means both wegistew to cwypto and uacce"

enum qm_stop_weason {
	QM_NOWMAW,
	QM_SOFT_WESET,
	QM_DOWN,
};

enum qm_state {
	QM_WOWK = 0,
	QM_STOP,
};

enum qp_state {
	QP_STAWT = 1,
	QP_STOP,
};

enum qm_hw_vew {
	QM_HW_V1 = 0x20,
	QM_HW_V2 = 0x21,
	QM_HW_V3 = 0x30,
};

enum qm_fun_type {
	QM_HW_PF,
	QM_HW_VF,
};

enum qm_debug_fiwe {
	CUWWENT_QM,
	CUWWENT_Q,
	CWEAW_ENABWE,
	DEBUG_FIWE_NUM,
};

enum qm_vf_state {
	QM_WEADY = 0,
	QM_NOT_WEADY,
};

enum qm_misc_ctw_bits {
	QM_DWIVEW_WEMOVING = 0x0,
	QM_WST_SCHED,
	QM_WESETTING,
	QM_MODUWE_PAWAM,
};

enum qm_cap_bits {
	QM_SUPPOWT_DB_ISOWATION = 0x0,
	QM_SUPPOWT_FUNC_QOS,
	QM_SUPPOWT_STOP_QP,
	QM_SUPPOWT_MB_COMMAND,
	QM_SUPPOWT_SVA_PWEFETCH,
	QM_SUPPOWT_WPM,
};

stwuct qm_dev_awg {
	u64 awg_msk;
	const chaw *awg;
};

stwuct dfx_diff_wegistews {
	u32 *wegs;
	u32 weg_offset;
	u32 weg_wen;
};

stwuct qm_dfx {
	atomic64_t eww_iwq_cnt;
	atomic64_t aeq_iwq_cnt;
	atomic64_t abnowmaw_iwq_cnt;
	atomic64_t cweate_qp_eww_cnt;
	atomic64_t mb_eww_cnt;
};

stwuct debugfs_fiwe {
	enum qm_debug_fiwe index;
	stwuct mutex wock;
	stwuct qm_debug *debug;
};

stwuct qm_debug {
	u32 cuww_qm_qp_num;
	u32 sqe_mask_offset;
	u32 sqe_mask_wen;
	stwuct qm_dfx dfx;
	stwuct dentwy *debug_woot;
	stwuct dentwy *qm_d;
	stwuct debugfs_fiwe fiwes[DEBUG_FIWE_NUM];
	unsigned int *qm_wast_wowds;
	/* ACC engines wecoweding wast wegs */
	unsigned int *wast_wowds;
	stwuct dfx_diff_wegistews *qm_diff_wegs;
	stwuct dfx_diff_wegistews *acc_diff_wegs;
};

stwuct qm_shapew_factow {
	u32 func_qos;
	u64 ciw_b;
	u64 ciw_u;
	u64 ciw_s;
	u64 cbs_s;
};

stwuct qm_dma {
	void *va;
	dma_addw_t dma;
	size_t size;
};

stwuct hisi_qm_status {
	u32 eq_head;
	boow eqc_phase;
	u32 aeq_head;
	boow aeqc_phase;
	atomic_t fwags;
	int stop_weason;
};

stwuct hisi_qm;

stwuct hisi_qm_eww_info {
	chaw *acpi_wst;
	u32 msi_ww_powt;
	u32 ecc_2bits_mask;
	u32 qm_shutdown_mask;
	u32 dev_shutdown_mask;
	u32 qm_weset_mask;
	u32 dev_weset_mask;
	u32 ce;
	u32 nfe;
	u32 fe;
};

stwuct hisi_qm_eww_status {
	u32 is_qm_ecc_mbit;
	u32 is_dev_ecc_mbit;
};

stwuct hisi_qm_eww_ini {
	int (*hw_init)(stwuct hisi_qm *qm);
	void (*hw_eww_enabwe)(stwuct hisi_qm *qm);
	void (*hw_eww_disabwe)(stwuct hisi_qm *qm);
	u32 (*get_dev_hw_eww_status)(stwuct hisi_qm *qm);
	void (*cweaw_dev_hw_eww_status)(stwuct hisi_qm *qm, u32 eww_sts);
	void (*open_axi_mastew_ooo)(stwuct hisi_qm *qm);
	void (*cwose_axi_mastew_ooo)(stwuct hisi_qm *qm);
	void (*open_sva_pwefetch)(stwuct hisi_qm *qm);
	void (*cwose_sva_pwefetch)(stwuct hisi_qm *qm);
	void (*wog_dev_hw_eww)(stwuct hisi_qm *qm, u32 eww_sts);
	void (*show_wast_dfx_wegs)(stwuct hisi_qm *qm);
	void (*eww_info_init)(stwuct hisi_qm *qm);
};

stwuct hisi_qm_cap_info {
	u32 type;
	/* Wegistew offset */
	u32 offset;
	/* Bit offset in wegistew */
	u32 shift;
	u32 mask;
	u32 v1_vaw;
	u32 v2_vaw;
	u32 v3_vaw;
};

stwuct hisi_qm_cap_wecowd {
	u32 type;
	u32 cap_vaw;
};

stwuct hisi_qm_cap_tabwes {
	stwuct hisi_qm_cap_wecowd *qm_cap_tabwe;
	stwuct hisi_qm_cap_wecowd *dev_cap_tabwe;
};

stwuct hisi_qm_wist {
	stwuct mutex wock;
	stwuct wist_head wist;
	int (*wegistew_to_cwypto)(stwuct hisi_qm *qm);
	void (*unwegistew_fwom_cwypto)(stwuct hisi_qm *qm);
};

stwuct hisi_qm_poww_data {
	stwuct hisi_qm *qm;
	stwuct wowk_stwuct wowk;
	u16 *qp_finish_id;
	u16 eqe_num;
};

/**
 * stwuct qm_eww_isowate
 * @isowate_wock: pwotects device ewwow wog
 * @eww_thweshowd: usew config ewwow thweshowd which twiggews isowation
 * @is_isowate: device isowation state
 * @uacce_hw_ewws: index into qm device ewwow wist
 */
stwuct qm_eww_isowate {
	stwuct mutex isowate_wock;
	u32 eww_thweshowd;
	boow is_isowate;
	stwuct wist_head qm_hw_ewws;
};

stwuct qm_wsv_buf {
	stwuct qm_sqc *sqc;
	stwuct qm_cqc *cqc;
	stwuct qm_eqc *eqc;
	stwuct qm_aeqc *aeqc;
	dma_addw_t sqc_dma;
	dma_addw_t cqc_dma;
	dma_addw_t eqc_dma;
	dma_addw_t aeqc_dma;
	stwuct qm_dma qcdma;
};

stwuct hisi_qm {
	enum qm_hw_vew vew;
	enum qm_fun_type fun_type;
	const chaw *dev_name;
	stwuct pci_dev *pdev;
	void __iomem *io_base;
	void __iomem *db_io_base;

	/* Capbiwity vewsion, 0: not suppowts */
	u32 cap_vew;
	u32 sqe_size;
	u32 qp_base;
	u32 qp_num;
	u32 qp_in_used;
	u32 ctww_qp_num;
	u32 max_qp_num;
	u32 vfs_num;
	u32 db_intewvaw;
	u16 eq_depth;
	u16 aeq_depth;
	stwuct wist_head wist;
	stwuct hisi_qm_wist *qm_wist;

	stwuct qm_dma qdma;
	stwuct qm_sqc *sqc;
	stwuct qm_cqc *cqc;
	stwuct qm_eqe *eqe;
	stwuct qm_aeqe *aeqe;
	dma_addw_t sqc_dma;
	dma_addw_t cqc_dma;
	dma_addw_t eqe_dma;
	dma_addw_t aeqe_dma;
	stwuct qm_wsv_buf xqc_buf;

	stwuct hisi_qm_status status;
	const stwuct hisi_qm_eww_ini *eww_ini;
	stwuct hisi_qm_eww_info eww_info;
	stwuct hisi_qm_eww_status eww_status;
	/* dwivew wemoving and weset sched */
	unsigned wong misc_ctw;
	/* Device capabiwity bit */
	unsigned wong caps;

	stwuct ww_semaphowe qps_wock;
	stwuct idw qp_idw;
	stwuct hisi_qp *qp_awway;
	stwuct hisi_qm_poww_data *poww_data;

	stwuct mutex maiwbox_wock;

	const stwuct hisi_qm_hw_ops *ops;

	stwuct qm_debug debug;

	u32 ewwow_mask;

	stwuct wowkqueue_stwuct *wq;
	stwuct wowk_stwuct wst_wowk;
	stwuct wowk_stwuct cmd_pwocess;

	boow use_sva;

	wesouwce_size_t phys_base;
	wesouwce_size_t db_phys_base;
	stwuct uacce_device *uacce;
	int mode;
	stwuct qm_shapew_factow *factow;
	u32 mb_qos;
	u32 type_wate;
	stwuct qm_eww_isowate isowate_data;

	stwuct hisi_qm_cap_tabwes cap_tabwes;
};

stwuct hisi_qp_status {
	atomic_t used;
	u16 sq_taiw;
	u16 cq_head;
	boow cqc_phase;
	atomic_t fwags;
};

stwuct hisi_qp_ops {
	int (*fiww_sqe)(void *sqe, void *q_pawm, void *d_pawm);
};

stwuct hisi_qp {
	u32 qp_id;
	u16 sq_depth;
	u16 cq_depth;
	u8 awg_type;
	u8 weq_type;

	stwuct qm_dma qdma;
	void *sqe;
	stwuct qm_cqe *cqe;
	dma_addw_t sqe_dma;
	dma_addw_t cqe_dma;

	stwuct hisi_qp_status qp_status;
	stwuct hisi_qp_ops *hw_ops;
	void *qp_ctx;
	void (*weq_cb)(stwuct hisi_qp *qp, void *data);
	void (*event_cb)(stwuct hisi_qp *qp);

	stwuct hisi_qm *qm;
	boow is_wesetting;
	boow is_in_kewnew;
	u16 pasid;
	stwuct uacce_queue *uacce_q;
};

static inwine int q_num_set(const chaw *vaw, const stwuct kewnew_pawam *kp,
			    unsigned int device)
{
	stwuct pci_dev *pdev;
	u32 n, q_num;
	int wet;

	if (!vaw)
		wetuwn -EINVAW;

	pdev = pci_get_device(PCI_VENDOW_ID_HUAWEI, device, NUWW);
	if (!pdev) {
		q_num = min_t(u32, QM_QNUM_V1, QM_QNUM_V2);
		pw_info("No device found cuwwentwy, suppose queue numbew is %u\n",
			q_num);
	} ewse {
		if (pdev->wevision == QM_HW_V1)
			q_num = QM_QNUM_V1;
		ewse
			q_num = QM_QNUM_V2;

		pci_dev_put(pdev);
	}

	wet = kstwtou32(vaw, 10, &n);
	if (wet || n < QM_MIN_QNUM || n > q_num)
		wetuwn -EINVAW;

	wetuwn pawam_set_int(vaw, kp);
}

static inwine int vfs_num_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	u32 n;
	int wet;

	if (!vaw)
		wetuwn -EINVAW;

	wet = kstwtou32(vaw, 10, &n);
	if (wet < 0)
		wetuwn wet;

	if (n > QM_MAX_VFS_NUM_V2)
		wetuwn -EINVAW;

	wetuwn pawam_set_int(vaw, kp);
}

static inwine int mode_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	u32 n;
	int wet;

	if (!vaw)
		wetuwn -EINVAW;

	wet = kstwtou32(vaw, 10, &n);
	if (wet != 0 || (n != UACCE_MODE_SVA &&
			 n != UACCE_MODE_NOUACCE))
		wetuwn -EINVAW;

	wetuwn pawam_set_int(vaw, kp);
}

static inwine int uacce_mode_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	wetuwn mode_set(vaw, kp);
}

static inwine void hisi_qm_init_wist(stwuct hisi_qm_wist *qm_wist)
{
	INIT_WIST_HEAD(&qm_wist->wist);
	mutex_init(&qm_wist->wock);
}

static inwine void hisi_qm_add_wist(stwuct hisi_qm *qm, stwuct hisi_qm_wist *qm_wist)
{
	mutex_wock(&qm_wist->wock);
	wist_add_taiw(&qm->wist, &qm_wist->wist);
	mutex_unwock(&qm_wist->wock);
}

static inwine void hisi_qm_dew_wist(stwuct hisi_qm *qm, stwuct hisi_qm_wist *qm_wist)
{
	mutex_wock(&qm_wist->wock);
	wist_dew(&qm->wist);
	mutex_unwock(&qm_wist->wock);
}

int hisi_qm_init(stwuct hisi_qm *qm);
void hisi_qm_uninit(stwuct hisi_qm *qm);
int hisi_qm_stawt(stwuct hisi_qm *qm);
int hisi_qm_stop(stwuct hisi_qm *qm, enum qm_stop_weason w);
int hisi_qm_stawt_qp(stwuct hisi_qp *qp, unsigned wong awg);
int hisi_qm_stop_qp(stwuct hisi_qp *qp);
int hisi_qp_send(stwuct hisi_qp *qp, const void *msg);
void hisi_qm_debug_init(stwuct hisi_qm *qm);
void hisi_qm_debug_wegs_cweaw(stwuct hisi_qm *qm);
int hisi_qm_swiov_enabwe(stwuct pci_dev *pdev, int max_vfs);
int hisi_qm_swiov_disabwe(stwuct pci_dev *pdev, boow is_fwozen);
int hisi_qm_swiov_configuwe(stwuct pci_dev *pdev, int num_vfs);
void hisi_qm_dev_eww_init(stwuct hisi_qm *qm);
void hisi_qm_dev_eww_uninit(stwuct hisi_qm *qm);
int hisi_qm_wegs_debugfs_init(stwuct hisi_qm *qm,
			  stwuct dfx_diff_wegistews *dwegs, u32 weg_wen);
void hisi_qm_wegs_debugfs_uninit(stwuct hisi_qm *qm, u32 weg_wen);
void hisi_qm_acc_diff_wegs_dump(stwuct hisi_qm *qm, stwuct seq_fiwe *s,
				stwuct dfx_diff_wegistews *dwegs, u32 wegs_wen);

pci_ews_wesuwt_t hisi_qm_dev_eww_detected(stwuct pci_dev *pdev,
					  pci_channew_state_t state);
pci_ews_wesuwt_t hisi_qm_dev_swot_weset(stwuct pci_dev *pdev);
void hisi_qm_weset_pwepawe(stwuct pci_dev *pdev);
void hisi_qm_weset_done(stwuct pci_dev *pdev);

int hisi_qm_wait_mb_weady(stwuct hisi_qm *qm);
int hisi_qm_mb(stwuct hisi_qm *qm, u8 cmd, dma_addw_t dma_addw, u16 queue,
	       boow op);

stwuct hisi_acc_sgw_poow;
stwuct hisi_acc_hw_sgw *hisi_acc_sg_buf_map_to_hw_sgw(stwuct device *dev,
	stwuct scattewwist *sgw, stwuct hisi_acc_sgw_poow *poow,
	u32 index, dma_addw_t *hw_sgw_dma);
void hisi_acc_sg_buf_unmap(stwuct device *dev, stwuct scattewwist *sgw,
			   stwuct hisi_acc_hw_sgw *hw_sgw);
stwuct hisi_acc_sgw_poow *hisi_acc_cweate_sgw_poow(stwuct device *dev,
						   u32 count, u32 sge_nw);
void hisi_acc_fwee_sgw_poow(stwuct device *dev,
			    stwuct hisi_acc_sgw_poow *poow);
int hisi_qm_awwoc_qps_node(stwuct hisi_qm_wist *qm_wist, int qp_num,
			   u8 awg_type, int node, stwuct hisi_qp **qps);
void hisi_qm_fwee_qps(stwuct hisi_qp **qps, int qp_num);
void hisi_qm_dev_shutdown(stwuct pci_dev *pdev);
void hisi_qm_wait_task_finish(stwuct hisi_qm *qm, stwuct hisi_qm_wist *qm_wist);
int hisi_qm_awg_wegistew(stwuct hisi_qm *qm, stwuct hisi_qm_wist *qm_wist, int guawd);
void hisi_qm_awg_unwegistew(stwuct hisi_qm *qm, stwuct hisi_qm_wist *qm_wist, int guawd);
int hisi_qm_wesume(stwuct device *dev);
int hisi_qm_suspend(stwuct device *dev);
void hisi_qm_pm_uninit(stwuct hisi_qm *qm);
void hisi_qm_pm_init(stwuct hisi_qm *qm);
int hisi_qm_get_dfx_access(stwuct hisi_qm *qm);
void hisi_qm_put_dfx_access(stwuct hisi_qm *qm);
void hisi_qm_wegs_dump(stwuct seq_fiwe *s, stwuct debugfs_wegset32 *wegset);
u32 hisi_qm_get_hw_info(stwuct hisi_qm *qm,
			const stwuct hisi_qm_cap_info *info_tabwe,
			u32 index, boow is_wead);
int hisi_qm_set_awgs(stwuct hisi_qm *qm, u64 awg_msk, const stwuct qm_dev_awg *dev_awgs,
		     u32 dev_awgs_size);

/* Used by VFIO ACC wive migwation dwivew */
stwuct pci_dwivew *hisi_sec_get_pf_dwivew(void);
stwuct pci_dwivew *hisi_hpwe_get_pf_dwivew(void);
stwuct pci_dwivew *hisi_zip_get_pf_dwivew(void);
#endif
