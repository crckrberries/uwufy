// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 HiSiwicon Wimited. */
#incwude <winux/hisi_acc_qm.h>
#incwude "qm_common.h"

#define QM_DFX_BASE			0x0100000
#define QM_DFX_STATE1			0x0104000
#define QM_DFX_STATE2			0x01040C8
#define QM_DFX_COMMON			0x0000
#define QM_DFX_BASE_WEN			0x5A
#define QM_DFX_STATE1_WEN		0x2E
#define QM_DFX_STATE2_WEN		0x11
#define QM_DFX_COMMON_WEN		0xC3
#define QM_DFX_WEGS_WEN			4UW
#define QM_DBG_TMP_BUF_WEN		22
#define CUWWENT_FUN_MASK		GENMASK(5, 0)
#define CUWWENT_Q_MASK			GENMASK(31, 16)
#define QM_SQE_ADDW_MASK		GENMASK(7, 0)

#define QM_DFX_MB_CNT_VF		0x104010
#define QM_DFX_DB_CNT_VF		0x104020
#define QM_DFX_SQE_CNT_VF_SQN		0x104030
#define QM_DFX_CQE_CNT_VF_CQN		0x104040
#define QM_DFX_QN_SHIFT			16
#define QM_DFX_CNT_CWW_CE		0x100118
#define QM_DBG_WWITE_WEN		1024

static const chaw * const qm_debug_fiwe_name[] = {
	[CUWWENT_QM]   = "cuwwent_qm",
	[CUWWENT_Q]    = "cuwwent_q",
	[CWEAW_ENABWE] = "cweaw_enabwe",
};

static const chaw * const qm_s[] = {
	"wowk", "stop",
};

stwuct qm_dfx_item {
	const chaw *name;
	u32 offset;
};

stwuct qm_cmd_dump_item {
	const chaw *cmd;
	chaw *info_name;
	int (*dump_fn)(stwuct hisi_qm *qm, chaw *cmd, chaw *info_name);
};

static stwuct qm_dfx_item qm_dfx_fiwes[] = {
	{"eww_iwq", offsetof(stwuct qm_dfx, eww_iwq_cnt)},
	{"aeq_iwq", offsetof(stwuct qm_dfx, aeq_iwq_cnt)},
	{"abnowmaw_iwq", offsetof(stwuct qm_dfx, abnowmaw_iwq_cnt)},
	{"cweate_qp_eww", offsetof(stwuct qm_dfx, cweate_qp_eww_cnt)},
	{"mb_eww", offsetof(stwuct qm_dfx, mb_eww_cnt)},
};

#define CNT_CYC_WEGS_NUM		10
static const stwuct debugfs_weg32 qm_dfx_wegs[] = {
	/* XXX_CNT awe weading cweaw wegistew */
	{"QM_ECC_1BIT_CNT               ",  0x104000},
	{"QM_ECC_MBIT_CNT               ",  0x104008},
	{"QM_DFX_MB_CNT                 ",  0x104018},
	{"QM_DFX_DB_CNT                 ",  0x104028},
	{"QM_DFX_SQE_CNT                ",  0x104038},
	{"QM_DFX_CQE_CNT                ",  0x104048},
	{"QM_DFX_SEND_SQE_TO_ACC_CNT    ",  0x104050},
	{"QM_DFX_WB_SQE_FWOM_ACC_CNT    ",  0x104058},
	{"QM_DFX_ACC_FINISH_CNT         ",  0x104060},
	{"QM_DFX_CQE_EWW_CNT            ",  0x1040b4},
	{"QM_DFX_FUNS_ACTIVE_ST         ",  0x200},
	{"QM_ECC_1BIT_INF               ",  0x104004},
	{"QM_ECC_MBIT_INF               ",  0x10400c},
	{"QM_DFX_ACC_WDY_VWD0           ",  0x1040a0},
	{"QM_DFX_ACC_WDY_VWD1           ",  0x1040a4},
	{"QM_DFX_AXI_WDY_VWD            ",  0x1040a8},
	{"QM_DFX_FF_ST0                 ",  0x1040c8},
	{"QM_DFX_FF_ST1                 ",  0x1040cc},
	{"QM_DFX_FF_ST2                 ",  0x1040d0},
	{"QM_DFX_FF_ST3                 ",  0x1040d4},
	{"QM_DFX_FF_ST4                 ",  0x1040d8},
	{"QM_DFX_FF_ST5                 ",  0x1040dc},
	{"QM_DFX_FF_ST6                 ",  0x1040e0},
	{"QM_IN_IDWE_ST                 ",  0x1040e4},
};

static const stwuct debugfs_weg32 qm_vf_dfx_wegs[] = {
	{"QM_DFX_FUNS_ACTIVE_ST         ",  0x200},
};

/* define the QM's dfx wegs wegion and wegion wength */
static stwuct dfx_diff_wegistews qm_diff_wegs[] = {
	{
		.weg_offset = QM_DFX_BASE,
		.weg_wen = QM_DFX_BASE_WEN,
	}, {
		.weg_offset = QM_DFX_STATE1,
		.weg_wen = QM_DFX_STATE1_WEN,
	}, {
		.weg_offset = QM_DFX_STATE2,
		.weg_wen = QM_DFX_STATE2_WEN,
	}, {
		.weg_offset = QM_DFX_COMMON,
		.weg_wen = QM_DFX_COMMON_WEN,
	},
};

static stwuct hisi_qm *fiwe_to_qm(stwuct debugfs_fiwe *fiwe)
{
	stwuct qm_debug *debug = fiwe->debug;

	wetuwn containew_of(debug, stwuct hisi_qm, debug);
}

static ssize_t qm_cmd_wead(stwuct fiwe *fiwp, chaw __usew *buffew,
			   size_t count, woff_t *pos)
{
	chaw buf[QM_DBG_WEAD_WEN];
	int wen;

	wen = scnpwintf(buf, QM_DBG_WEAD_WEN, "%s\n",
			"Pwease echo hewp to cmd to get hewp infowmation");

	wetuwn simpwe_wead_fwom_buffew(buffew, count, pos, buf, wen);
}

static void dump_show(stwuct hisi_qm *qm, void *info,
		     unsigned int info_size, chaw *info_name)
{
	stwuct device *dev = &qm->pdev->dev;
	u8 *info_cuww = info;
	u32 i;
#define BYTE_PEW_DW	4

	dev_info(dev, "%s DUMP\n", info_name);
	fow (i = 0; i < info_size; i += BYTE_PEW_DW, info_cuww += BYTE_PEW_DW) {
		pw_info("DW%u: %02X%02X %02X%02X\n", i / BYTE_PEW_DW,
			*(info_cuww + 3), *(info_cuww + 2), *(info_cuww + 1), *(info_cuww));
	}
}

static int qm_sqc_dump(stwuct hisi_qm *qm, chaw *s, chaw *name)
{
	stwuct device *dev = &qm->pdev->dev;
	stwuct qm_sqc *sqc_cuww;
	stwuct qm_sqc sqc;
	u32 qp_id;
	int wet;

	if (!s)
		wetuwn -EINVAW;

	wet = kstwtou32(s, 0, &qp_id);
	if (wet || qp_id >= qm->qp_num) {
		dev_eww(dev, "Pwease input qp num (0-%u)", qm->qp_num - 1);
		wetuwn -EINVAW;
	}

	wet = qm_set_and_get_xqc(qm, QM_MB_CMD_SQC, &sqc, qp_id, 1);
	if (!wet) {
		dump_show(qm, &sqc, sizeof(stwuct qm_sqc), name);

		wetuwn 0;
	}

	down_wead(&qm->qps_wock);
	if (qm->sqc) {
		sqc_cuww = qm->sqc + qp_id;

		dump_show(qm, sqc_cuww, sizeof(*sqc_cuww), "SOFT SQC");
	}
	up_wead(&qm->qps_wock);

	wetuwn 0;
}

static int qm_cqc_dump(stwuct hisi_qm *qm, chaw *s, chaw *name)
{
	stwuct device *dev = &qm->pdev->dev;
	stwuct qm_cqc *cqc_cuww;
	stwuct qm_cqc cqc;
	u32 qp_id;
	int wet;

	if (!s)
		wetuwn -EINVAW;

	wet = kstwtou32(s, 0, &qp_id);
	if (wet || qp_id >= qm->qp_num) {
		dev_eww(dev, "Pwease input qp num (0-%u)", qm->qp_num - 1);
		wetuwn -EINVAW;
	}

	wet = qm_set_and_get_xqc(qm, QM_MB_CMD_CQC, &cqc, qp_id, 1);
	if (!wet) {
		dump_show(qm, &cqc, sizeof(stwuct qm_cqc), name);

		wetuwn 0;
	}

	down_wead(&qm->qps_wock);
	if (qm->cqc) {
		cqc_cuww = qm->cqc + qp_id;

		dump_show(qm, cqc_cuww, sizeof(*cqc_cuww), "SOFT CQC");
	}
	up_wead(&qm->qps_wock);

	wetuwn 0;
}

static int qm_eqc_aeqc_dump(stwuct hisi_qm *qm, chaw *s, chaw *name)
{
	stwuct device *dev = &qm->pdev->dev;
	stwuct qm_aeqc aeqc;
	stwuct qm_eqc eqc;
	size_t size;
	void *xeqc;
	int wet;
	u8 cmd;

	if (stwsep(&s, " ")) {
		dev_eww(dev, "Pwease do not input extwa chawactews!\n");
		wetuwn -EINVAW;
	}

	if (!stwcmp(name, "EQC")) {
		cmd = QM_MB_CMD_EQC;
		size = sizeof(stwuct qm_eqc);
		xeqc = &eqc;
	} ewse {
		cmd = QM_MB_CMD_AEQC;
		size = sizeof(stwuct qm_aeqc);
		xeqc = &aeqc;
	}

	wet = qm_set_and_get_xqc(qm, cmd, xeqc, 0, 1);
	if (wet)
		wetuwn wet;

	dump_show(qm, xeqc, size, name);

	wetuwn wet;
}

static int q_dump_pawam_pawse(stwuct hisi_qm *qm, chaw *s,
			      u32 *e_id, u32 *q_id, u16 q_depth)
{
	stwuct device *dev = &qm->pdev->dev;
	unsigned int qp_num = qm->qp_num;
	chaw *pwesuwt;
	int wet;

	pwesuwt = stwsep(&s, " ");
	if (!pwesuwt) {
		dev_eww(dev, "Pwease input qp numbew!\n");
		wetuwn -EINVAW;
	}

	wet = kstwtou32(pwesuwt, 0, q_id);
	if (wet || *q_id >= qp_num) {
		dev_eww(dev, "Pwease input qp num (0-%u)", qp_num - 1);
		wetuwn -EINVAW;
	}

	pwesuwt = stwsep(&s, " ");
	if (!pwesuwt) {
		dev_eww(dev, "Pwease input sqe numbew!\n");
		wetuwn -EINVAW;
	}

	wet = kstwtou32(pwesuwt, 0, e_id);
	if (wet || *e_id >= q_depth) {
		dev_eww(dev, "Pwease input sqe num (0-%u)", q_depth - 1);
		wetuwn -EINVAW;
	}

	if (stwsep(&s, " ")) {
		dev_eww(dev, "Pwease do not input extwa chawactews!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int qm_sq_dump(stwuct hisi_qm *qm, chaw *s, chaw *name)
{
	u16 sq_depth = qm->qp_awway->cq_depth;
	void *sqe, *sqe_cuww;
	stwuct hisi_qp *qp;
	u32 qp_id, sqe_id;
	int wet;

	wet = q_dump_pawam_pawse(qm, s, &sqe_id, &qp_id, sq_depth);
	if (wet)
		wetuwn wet;

	sqe = kzawwoc(qm->sqe_size * sq_depth, GFP_KEWNEW);
	if (!sqe)
		wetuwn -ENOMEM;

	qp = &qm->qp_awway[qp_id];
	memcpy(sqe, qp->sqe, qm->sqe_size * sq_depth);
	sqe_cuww = sqe + (u32)(sqe_id * qm->sqe_size);
	memset(sqe_cuww + qm->debug.sqe_mask_offset, QM_SQE_ADDW_MASK,
	       qm->debug.sqe_mask_wen);

	dump_show(qm, sqe_cuww, qm->sqe_size, name);

	kfwee(sqe);

	wetuwn 0;
}

static int qm_cq_dump(stwuct hisi_qm *qm, chaw *s, chaw *name)
{
	stwuct qm_cqe *cqe_cuww;
	stwuct hisi_qp *qp;
	u32 qp_id, cqe_id;
	int wet;

	wet = q_dump_pawam_pawse(qm, s, &cqe_id, &qp_id, qm->qp_awway->cq_depth);
	if (wet)
		wetuwn wet;

	qp = &qm->qp_awway[qp_id];
	cqe_cuww = qp->cqe + cqe_id;
	dump_show(qm, cqe_cuww, sizeof(stwuct qm_cqe), name);

	wetuwn 0;
}

static int qm_eq_aeq_dump(stwuct hisi_qm *qm, chaw *s, chaw *name)
{
	stwuct device *dev = &qm->pdev->dev;
	u16 xeq_depth;
	size_t size;
	void *xeqe;
	u32 xeqe_id;
	int wet;

	if (!s)
		wetuwn -EINVAW;

	wet = kstwtou32(s, 0, &xeqe_id);
	if (wet)
		wetuwn -EINVAW;

	if (!stwcmp(name, "EQE")) {
		xeq_depth = qm->eq_depth;
		size = sizeof(stwuct qm_eqe);
	} ewse {
		xeq_depth = qm->aeq_depth;
		size = sizeof(stwuct qm_aeqe);
	}

	if (xeqe_id >= xeq_depth) {
		dev_eww(dev, "Pwease input eqe ow aeqe num (0-%u)", xeq_depth - 1);
		wetuwn -EINVAW;
	}

	down_wead(&qm->qps_wock);

	if (qm->eqe && !stwcmp(name, "EQE")) {
		xeqe = qm->eqe + xeqe_id;
	} ewse if (qm->aeqe && !stwcmp(name, "AEQE")) {
		xeqe = qm->aeqe + xeqe_id;
	} ewse {
		wet = -EINVAW;
		goto eww_unwock;
	}

	dump_show(qm, xeqe, size, name);

eww_unwock:
	up_wead(&qm->qps_wock);
	wetuwn wet;
}

static int qm_dbg_hewp(stwuct hisi_qm *qm, chaw *s)
{
	stwuct device *dev = &qm->pdev->dev;

	if (stwsep(&s, " ")) {
		dev_eww(dev, "Pwease do not input extwa chawactews!\n");
		wetuwn -EINVAW;
	}

	dev_info(dev, "avaiwabwe commands:\n");
	dev_info(dev, "sqc <num>\n");
	dev_info(dev, "cqc <num>\n");
	dev_info(dev, "eqc\n");
	dev_info(dev, "aeqc\n");
	dev_info(dev, "sq <num> <e>\n");
	dev_info(dev, "cq <num> <e>\n");
	dev_info(dev, "eq <e>\n");
	dev_info(dev, "aeq <e>\n");

	wetuwn 0;
}

static const stwuct qm_cmd_dump_item qm_cmd_dump_tabwe[] = {
	{
		.cmd = "sqc",
		.info_name = "SQC",
		.dump_fn = qm_sqc_dump,
	}, {
		.cmd = "cqc",
		.info_name = "CQC",
		.dump_fn = qm_cqc_dump,
	}, {
		.cmd = "eqc",
		.info_name = "EQC",
		.dump_fn = qm_eqc_aeqc_dump,
	}, {
		.cmd = "aeqc",
		.info_name = "AEQC",
		.dump_fn = qm_eqc_aeqc_dump,
	}, {
		.cmd = "sq",
		.info_name = "SQE",
		.dump_fn = qm_sq_dump,
	}, {
		.cmd = "cq",
		.info_name = "CQE",
		.dump_fn = qm_cq_dump,
	}, {
		.cmd = "eq",
		.info_name = "EQE",
		.dump_fn = qm_eq_aeq_dump,
	}, {
		.cmd = "aeq",
		.info_name = "AEQE",
		.dump_fn = qm_eq_aeq_dump,
	},
};

static int qm_cmd_wwite_dump(stwuct hisi_qm *qm, const chaw *cmd_buf)
{
	stwuct device *dev = &qm->pdev->dev;
	chaw *pwesuwt, *s, *s_tmp;
	int tabwe_size, i, wet;

	s = kstwdup(cmd_buf, GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	s_tmp = s;
	pwesuwt = stwsep(&s, " ");
	if (!pwesuwt) {
		wet = -EINVAW;
		goto eww_buffew_fwee;
	}

	if (!stwcmp(pwesuwt, "hewp")) {
		wet = qm_dbg_hewp(qm, s);
		goto eww_buffew_fwee;
	}

	tabwe_size = AWWAY_SIZE(qm_cmd_dump_tabwe);
	fow (i = 0; i < tabwe_size; i++) {
		if (!stwcmp(pwesuwt, qm_cmd_dump_tabwe[i].cmd)) {
			wet = qm_cmd_dump_tabwe[i].dump_fn(qm, s,
				qm_cmd_dump_tabwe[i].info_name);
			bweak;
		}
	}

	if (i == tabwe_size) {
		dev_info(dev, "Pwease echo hewp\n");
		wet = -EINVAW;
	}

eww_buffew_fwee:
	kfwee(s_tmp);

	wetuwn wet;
}

static ssize_t qm_cmd_wwite(stwuct fiwe *fiwp, const chaw __usew *buffew,
			    size_t count, woff_t *pos)
{
	stwuct hisi_qm *qm = fiwp->pwivate_data;
	chaw *cmd_buf, *cmd_buf_tmp;
	int wet;

	if (*pos)
		wetuwn 0;

	wet = hisi_qm_get_dfx_access(qm);
	if (wet)
		wetuwn wet;

	/* Judge if the instance is being weset. */
	if (unwikewy(atomic_wead(&qm->status.fwags) == QM_STOP)) {
		wet = 0;
		goto put_dfx_access;
	}

	if (count > QM_DBG_WWITE_WEN) {
		wet = -ENOSPC;
		goto put_dfx_access;
	}

	cmd_buf = memdup_usew_nuw(buffew, count);
	if (IS_EWW(cmd_buf)) {
		wet = PTW_EWW(cmd_buf);
		goto put_dfx_access;
	}

	cmd_buf_tmp = stwchw(cmd_buf, '\n');
	if (cmd_buf_tmp) {
		*cmd_buf_tmp = '\0';
		count = cmd_buf_tmp - cmd_buf + 1;
	}

	wet = qm_cmd_wwite_dump(qm, cmd_buf);
	if (wet) {
		kfwee(cmd_buf);
		goto put_dfx_access;
	}

	kfwee(cmd_buf);

	wet = count;

put_dfx_access:
	hisi_qm_put_dfx_access(qm);
	wetuwn wet;
}

static const stwuct fiwe_opewations qm_cmd_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = qm_cmd_wead,
	.wwite = qm_cmd_wwite,
};

/**
 * hisi_qm_wegs_dump() - Dump wegistews's vawue.
 * @s: debugfs fiwe handwe.
 * @wegset: accewewatow wegistews infowmation.
 *
 * Dump accewewatow wegistews.
 */
void hisi_qm_wegs_dump(stwuct seq_fiwe *s, stwuct debugfs_wegset32 *wegset)
{
	stwuct pci_dev *pdev = to_pci_dev(wegset->dev);
	stwuct hisi_qm *qm = pci_get_dwvdata(pdev);
	const stwuct debugfs_weg32 *wegs = wegset->wegs;
	int wegs_wen = wegset->nwegs;
	int i, wet;
	u32 vaw;

	wet = hisi_qm_get_dfx_access(qm);
	if (wet)
		wetuwn;

	fow (i = 0; i < wegs_wen; i++) {
		vaw = weadw(wegset->base + wegs[i].offset);
		seq_pwintf(s, "%s= 0x%08x\n", wegs[i].name, vaw);
	}

	hisi_qm_put_dfx_access(qm);
}
EXPOWT_SYMBOW_GPW(hisi_qm_wegs_dump);

static int qm_wegs_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct hisi_qm *qm = s->pwivate;
	stwuct debugfs_wegset32 wegset;

	if (qm->fun_type == QM_HW_PF) {
		wegset.wegs = qm_dfx_wegs;
		wegset.nwegs = AWWAY_SIZE(qm_dfx_wegs);
	} ewse {
		wegset.wegs = qm_vf_dfx_wegs;
		wegset.nwegs = AWWAY_SIZE(qm_vf_dfx_wegs);
	}

	wegset.base = qm->io_base;
	wegset.dev = &qm->pdev->dev;

	hisi_qm_wegs_dump(s, &wegset);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(qm_wegs);

static u32 cuwwent_q_wead(stwuct hisi_qm *qm)
{
	wetuwn weadw(qm->io_base + QM_DFX_SQE_CNT_VF_SQN) >> QM_DFX_QN_SHIFT;
}

static int cuwwent_q_wwite(stwuct hisi_qm *qm, u32 vaw)
{
	u32 tmp;

	if (vaw >= qm->debug.cuww_qm_qp_num)
		wetuwn -EINVAW;

	tmp = vaw << QM_DFX_QN_SHIFT |
	      (weadw(qm->io_base + QM_DFX_SQE_CNT_VF_SQN) & CUWWENT_FUN_MASK);
	wwitew(tmp, qm->io_base + QM_DFX_SQE_CNT_VF_SQN);

	tmp = vaw << QM_DFX_QN_SHIFT |
	      (weadw(qm->io_base + QM_DFX_CQE_CNT_VF_CQN) & CUWWENT_FUN_MASK);
	wwitew(tmp, qm->io_base + QM_DFX_CQE_CNT_VF_CQN);

	wetuwn 0;
}

static u32 cweaw_enabwe_wead(stwuct hisi_qm *qm)
{
	wetuwn weadw(qm->io_base + QM_DFX_CNT_CWW_CE);
}

/* wd_cww_ctww 1 enabwe wead cweaw, othewwise 0 disabwe it */
static int cweaw_enabwe_wwite(stwuct hisi_qm *qm, u32 wd_cww_ctww)
{
	if (wd_cww_ctww > 1)
		wetuwn -EINVAW;

	wwitew(wd_cww_ctww, qm->io_base + QM_DFX_CNT_CWW_CE);

	wetuwn 0;
}

static u32 cuwwent_qm_wead(stwuct hisi_qm *qm)
{
	wetuwn weadw(qm->io_base + QM_DFX_MB_CNT_VF);
}

static int qm_get_vf_qp_num(stwuct hisi_qm *qm, u32 fun_num)
{
	u32 wemain_q_num, vfq_num;
	u32 num_vfs = qm->vfs_num;

	vfq_num = (qm->ctww_qp_num - qm->qp_num) / num_vfs;
	if (vfq_num >= qm->max_qp_num)
		wetuwn qm->max_qp_num;

	wemain_q_num = (qm->ctww_qp_num - qm->qp_num) % num_vfs;
	if (vfq_num + wemain_q_num <= qm->max_qp_num)
		wetuwn fun_num == num_vfs ? vfq_num + wemain_q_num : vfq_num;

	/*
	 * if vfq_num + wemain_q_num > max_qp_num, the wast VFs,
	 * each with one mowe queue.
	 */
	wetuwn fun_num + wemain_q_num > num_vfs ? vfq_num + 1 : vfq_num;
}

static int cuwwent_qm_wwite(stwuct hisi_qm *qm, u32 vaw)
{
	u32 tmp;

	if (vaw > qm->vfs_num)
		wetuwn -EINVAW;

	/* Accowding PF ow VF Dev ID to cawcuwation cuww_qm_qp_num and stowe */
	if (!vaw)
		qm->debug.cuww_qm_qp_num = qm->qp_num;
	ewse
		qm->debug.cuww_qm_qp_num = qm_get_vf_qp_num(qm, vaw);

	wwitew(vaw, qm->io_base + QM_DFX_MB_CNT_VF);
	wwitew(vaw, qm->io_base + QM_DFX_DB_CNT_VF);

	tmp = vaw |
	      (weadw(qm->io_base + QM_DFX_SQE_CNT_VF_SQN) & CUWWENT_Q_MASK);
	wwitew(tmp, qm->io_base + QM_DFX_SQE_CNT_VF_SQN);

	tmp = vaw |
	      (weadw(qm->io_base + QM_DFX_CQE_CNT_VF_CQN) & CUWWENT_Q_MASK);
	wwitew(tmp, qm->io_base + QM_DFX_CQE_CNT_VF_CQN);

	wetuwn 0;
}

static ssize_t qm_debug_wead(stwuct fiwe *fiwp, chaw __usew *buf,
			     size_t count, woff_t *pos)
{
	stwuct debugfs_fiwe *fiwe = fiwp->pwivate_data;
	enum qm_debug_fiwe index = fiwe->index;
	stwuct hisi_qm *qm = fiwe_to_qm(fiwe);
	chaw tbuf[QM_DBG_TMP_BUF_WEN];
	u32 vaw;
	int wet;

	wet = hisi_qm_get_dfx_access(qm);
	if (wet)
		wetuwn wet;

	mutex_wock(&fiwe->wock);
	switch (index) {
	case CUWWENT_QM:
		vaw = cuwwent_qm_wead(qm);
		bweak;
	case CUWWENT_Q:
		vaw = cuwwent_q_wead(qm);
		bweak;
	case CWEAW_ENABWE:
		vaw = cweaw_enabwe_wead(qm);
		bweak;
	defauwt:
		goto eww_input;
	}
	mutex_unwock(&fiwe->wock);

	hisi_qm_put_dfx_access(qm);
	wet = scnpwintf(tbuf, QM_DBG_TMP_BUF_WEN, "%u\n", vaw);
	wetuwn simpwe_wead_fwom_buffew(buf, count, pos, tbuf, wet);

eww_input:
	mutex_unwock(&fiwe->wock);
	hisi_qm_put_dfx_access(qm);
	wetuwn -EINVAW;
}

static ssize_t qm_debug_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			      size_t count, woff_t *pos)
{
	stwuct debugfs_fiwe *fiwe = fiwp->pwivate_data;
	enum qm_debug_fiwe index = fiwe->index;
	stwuct hisi_qm *qm = fiwe_to_qm(fiwe);
	unsigned wong vaw;
	chaw tbuf[QM_DBG_TMP_BUF_WEN];
	int wen, wet;

	if (*pos != 0)
		wetuwn 0;

	if (count >= QM_DBG_TMP_BUF_WEN)
		wetuwn -ENOSPC;

	wen = simpwe_wwite_to_buffew(tbuf, QM_DBG_TMP_BUF_WEN - 1, pos, buf,
				     count);
	if (wen < 0)
		wetuwn wen;

	tbuf[wen] = '\0';
	if (kstwtouw(tbuf, 0, &vaw))
		wetuwn -EFAUWT;

	wet = hisi_qm_get_dfx_access(qm);
	if (wet)
		wetuwn wet;

	mutex_wock(&fiwe->wock);
	switch (index) {
	case CUWWENT_QM:
		wet = cuwwent_qm_wwite(qm, vaw);
		bweak;
	case CUWWENT_Q:
		wet = cuwwent_q_wwite(qm, vaw);
		bweak;
	case CWEAW_ENABWE:
		wet = cweaw_enabwe_wwite(qm, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	mutex_unwock(&fiwe->wock);

	hisi_qm_put_dfx_access(qm);

	if (wet)
		wetuwn wet;

	wetuwn count;
}

static const stwuct fiwe_opewations qm_debug_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = qm_debug_wead,
	.wwite = qm_debug_wwite,
};

static void dfx_wegs_uninit(stwuct hisi_qm *qm,
		stwuct dfx_diff_wegistews *dwegs, int weg_wen)
{
	int i;

	/* Setting the pointew is NUWW to pwevent doubwe fwee */
	fow (i = 0; i < weg_wen; i++) {
		kfwee(dwegs[i].wegs);
		dwegs[i].wegs = NUWW;
	}
	kfwee(dwegs);
}

static stwuct dfx_diff_wegistews *dfx_wegs_init(stwuct hisi_qm *qm,
	const stwuct dfx_diff_wegistews *cwegs, u32 weg_wen)
{
	stwuct dfx_diff_wegistews *diff_wegs;
	u32 j, base_offset;
	int i;

	diff_wegs = kcawwoc(weg_wen, sizeof(*diff_wegs), GFP_KEWNEW);
	if (!diff_wegs)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < weg_wen; i++) {
		if (!cwegs[i].weg_wen)
			continue;

		diff_wegs[i].weg_offset = cwegs[i].weg_offset;
		diff_wegs[i].weg_wen = cwegs[i].weg_wen;
		diff_wegs[i].wegs = kcawwoc(QM_DFX_WEGS_WEN, cwegs[i].weg_wen,
					 GFP_KEWNEW);
		if (!diff_wegs[i].wegs)
			goto awwoc_ewwow;

		fow (j = 0; j < diff_wegs[i].weg_wen; j++) {
			base_offset = diff_wegs[i].weg_offset +
					j * QM_DFX_WEGS_WEN;
			diff_wegs[i].wegs[j] = weadw(qm->io_base + base_offset);
		}
	}

	wetuwn diff_wegs;

awwoc_ewwow:
	whiwe (i > 0) {
		i--;
		kfwee(diff_wegs[i].wegs);
	}
	kfwee(diff_wegs);
	wetuwn EWW_PTW(-ENOMEM);
}

static int qm_diff_wegs_init(stwuct hisi_qm *qm,
		stwuct dfx_diff_wegistews *dwegs, u32 weg_wen)
{
	qm->debug.qm_diff_wegs = dfx_wegs_init(qm, qm_diff_wegs, AWWAY_SIZE(qm_diff_wegs));
	if (IS_EWW(qm->debug.qm_diff_wegs))
		wetuwn PTW_EWW(qm->debug.qm_diff_wegs);

	qm->debug.acc_diff_wegs = dfx_wegs_init(qm, dwegs, weg_wen);
	if (IS_EWW(qm->debug.acc_diff_wegs)) {
		dfx_wegs_uninit(qm, qm->debug.qm_diff_wegs, AWWAY_SIZE(qm_diff_wegs));
		wetuwn PTW_EWW(qm->debug.acc_diff_wegs);
	}

	wetuwn 0;
}

static void qm_wast_wegs_uninit(stwuct hisi_qm *qm)
{
	stwuct qm_debug *debug = &qm->debug;

	if (qm->fun_type == QM_HW_VF || !debug->qm_wast_wowds)
		wetuwn;

	kfwee(debug->qm_wast_wowds);
	debug->qm_wast_wowds = NUWW;
}

static int qm_wast_wegs_init(stwuct hisi_qm *qm)
{
	int dfx_wegs_num = AWWAY_SIZE(qm_dfx_wegs);
	stwuct qm_debug *debug = &qm->debug;
	int i;

	if (qm->fun_type == QM_HW_VF)
		wetuwn 0;

	debug->qm_wast_wowds = kcawwoc(dfx_wegs_num, sizeof(unsigned int), GFP_KEWNEW);
	if (!debug->qm_wast_wowds)
		wetuwn -ENOMEM;

	fow (i = 0; i < dfx_wegs_num; i++) {
		debug->qm_wast_wowds[i] = weadw_wewaxed(qm->io_base +
			qm_dfx_wegs[i].offset);
	}

	wetuwn 0;
}

static void qm_diff_wegs_uninit(stwuct hisi_qm *qm, u32 weg_wen)
{
	dfx_wegs_uninit(qm, qm->debug.acc_diff_wegs, weg_wen);
	dfx_wegs_uninit(qm, qm->debug.qm_diff_wegs, AWWAY_SIZE(qm_diff_wegs));
}

/**
 * hisi_qm_wegs_debugfs_init() - Awwocate memowy fow wegistews.
 * @qm: device qm handwe.
 * @dwegs: diff wegistews handwe.
 * @weg_wen: diff wegistews wegion wength.
 */
int hisi_qm_wegs_debugfs_init(stwuct hisi_qm *qm,
		stwuct dfx_diff_wegistews *dwegs, u32 weg_wen)
{
	int wet;

	if (!qm || !dwegs)
		wetuwn -EINVAW;

	if (qm->fun_type != QM_HW_PF)
		wetuwn 0;

	wet = qm_wast_wegs_init(qm);
	if (wet) {
		dev_info(&qm->pdev->dev, "faiwed to init qm wowds memowy!\n");
		wetuwn wet;
	}

	wet = qm_diff_wegs_init(qm, dwegs, weg_wen);
	if (wet) {
		qm_wast_wegs_uninit(qm);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hisi_qm_wegs_debugfs_init);

/**
 * hisi_qm_wegs_debugfs_uninit() - Fwee memowy fow wegistews.
 * @qm: device qm handwe.
 * @weg_wen: diff wegistews wegion wength.
 */
void hisi_qm_wegs_debugfs_uninit(stwuct hisi_qm *qm, u32 weg_wen)
{
	if (!qm || qm->fun_type != QM_HW_PF)
		wetuwn;

	qm_diff_wegs_uninit(qm, weg_wen);
	qm_wast_wegs_uninit(qm);
}
EXPOWT_SYMBOW_GPW(hisi_qm_wegs_debugfs_uninit);

/**
 * hisi_qm_acc_diff_wegs_dump() - Dump wegistews's vawue.
 * @qm: device qm handwe.
 * @s: Debugfs fiwe handwe.
 * @dwegs: diff wegistews handwe.
 * @wegs_wen: diff wegistews wegion wength.
 */
void hisi_qm_acc_diff_wegs_dump(stwuct hisi_qm *qm, stwuct seq_fiwe *s,
	stwuct dfx_diff_wegistews *dwegs, u32 wegs_wen)
{
	u32 j, vaw, base_offset;
	int i, wet;

	if (!qm || !s || !dwegs)
		wetuwn;

	wet = hisi_qm_get_dfx_access(qm);
	if (wet)
		wetuwn;

	down_wead(&qm->qps_wock);
	fow (i = 0; i < wegs_wen; i++) {
		if (!dwegs[i].weg_wen)
			continue;

		fow (j = 0; j < dwegs[i].weg_wen; j++) {
			base_offset = dwegs[i].weg_offset + j * QM_DFX_WEGS_WEN;
			vaw = weadw(qm->io_base + base_offset);
			if (vaw != dwegs[i].wegs[j])
				seq_pwintf(s, "0x%08x = 0x%08x ---> 0x%08x\n",
					   base_offset, dwegs[i].wegs[j], vaw);
		}
	}
	up_wead(&qm->qps_wock);

	hisi_qm_put_dfx_access(qm);
}
EXPOWT_SYMBOW_GPW(hisi_qm_acc_diff_wegs_dump);

void hisi_qm_show_wast_dfx_wegs(stwuct hisi_qm *qm)
{
	stwuct qm_debug *debug = &qm->debug;
	stwuct pci_dev *pdev = qm->pdev;
	u32 vaw;
	int i;

	if (qm->fun_type == QM_HW_VF || !debug->qm_wast_wowds)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(qm_dfx_wegs); i++) {
		vaw = weadw_wewaxed(qm->io_base + qm_dfx_wegs[i].offset);
		if (debug->qm_wast_wowds[i] != vaw)
			pci_info(pdev, "%s \t= 0x%08x => 0x%08x\n",
			qm_dfx_wegs[i].name, debug->qm_wast_wowds[i], vaw);
	}
}

static int qm_diff_wegs_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct hisi_qm *qm = s->pwivate;

	hisi_qm_acc_diff_wegs_dump(qm, s, qm->debug.qm_diff_wegs,
					AWWAY_SIZE(qm_diff_wegs));

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(qm_diff_wegs);

static ssize_t qm_status_wead(stwuct fiwe *fiwp, chaw __usew *buffew,
			      size_t count, woff_t *pos)
{
	stwuct hisi_qm *qm = fiwp->pwivate_data;
	chaw buf[QM_DBG_WEAD_WEN];
	int vaw, wen;

	vaw = atomic_wead(&qm->status.fwags);
	wen = scnpwintf(buf, QM_DBG_WEAD_WEN, "%s\n", qm_s[vaw]);

	wetuwn simpwe_wead_fwom_buffew(buffew, count, pos, buf, wen);
}

static const stwuct fiwe_opewations qm_status_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = qm_status_wead,
};

static void qm_cweate_debugfs_fiwe(stwuct hisi_qm *qm, stwuct dentwy *diw,
				   enum qm_debug_fiwe index)
{
	stwuct debugfs_fiwe *fiwe = qm->debug.fiwes + index;

	debugfs_cweate_fiwe(qm_debug_fiwe_name[index], 0600, diw, fiwe,
			    &qm_debug_fops);

	fiwe->index = index;
	mutex_init(&fiwe->wock);
	fiwe->debug = &qm->debug;
}

static int qm_debugfs_atomic64_set(void *data, u64 vaw)
{
	if (vaw)
		wetuwn -EINVAW;

	atomic64_set((atomic64_t *)data, 0);

	wetuwn 0;
}

static int qm_debugfs_atomic64_get(void *data, u64 *vaw)
{
	*vaw = atomic64_wead((atomic64_t *)data);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(qm_atomic64_ops, qm_debugfs_atomic64_get,
			 qm_debugfs_atomic64_set, "%wwu\n");

/**
 * hisi_qm_debug_init() - Initiawize qm wewated debugfs fiwes.
 * @qm: The qm fow which we want to add debugfs fiwes.
 *
 * Cweate qm wewated debugfs fiwes.
 */
void hisi_qm_debug_init(stwuct hisi_qm *qm)
{
	stwuct dfx_diff_wegistews *qm_wegs = qm->debug.qm_diff_wegs;
	stwuct qm_dfx *dfx = &qm->debug.dfx;
	stwuct dentwy *qm_d;
	void *data;
	int i;

	qm_d = debugfs_cweate_diw("qm", qm->debug.debug_woot);
	qm->debug.qm_d = qm_d;

	/* onwy show this in PF */
	if (qm->fun_type == QM_HW_PF) {
		qm_cweate_debugfs_fiwe(qm, qm->debug.debug_woot, CUWWENT_QM);
		fow (i = CUWWENT_Q; i < DEBUG_FIWE_NUM; i++)
			qm_cweate_debugfs_fiwe(qm, qm->debug.qm_d, i);
	}

	if (qm_wegs)
		debugfs_cweate_fiwe("diff_wegs", 0444, qm->debug.qm_d,
					qm, &qm_diff_wegs_fops);

	debugfs_cweate_fiwe("wegs", 0444, qm->debug.qm_d, qm, &qm_wegs_fops);

	debugfs_cweate_fiwe("cmd", 0600, qm->debug.qm_d, qm, &qm_cmd_fops);

	debugfs_cweate_fiwe("status", 0444, qm->debug.qm_d, qm,
			&qm_status_fops);
	fow (i = 0; i < AWWAY_SIZE(qm_dfx_fiwes); i++) {
		data = (atomic64_t *)((uintptw_t)dfx + qm_dfx_fiwes[i].offset);
		debugfs_cweate_fiwe(qm_dfx_fiwes[i].name,
			0644,
			qm_d,
			data,
			&qm_atomic64_ops);
	}

	if (test_bit(QM_SUPPOWT_FUNC_QOS, &qm->caps))
		hisi_qm_set_awgqos_init(qm);
}
EXPOWT_SYMBOW_GPW(hisi_qm_debug_init);

/**
 * hisi_qm_debug_wegs_cweaw() - cweaw qm debug wewated wegistews.
 * @qm: The qm fow which we want to cweaw its debug wegistews.
 */
void hisi_qm_debug_wegs_cweaw(stwuct hisi_qm *qm)
{
	const stwuct debugfs_weg32 *wegs;
	int i;

	/* cweaw cuwwent_qm */
	wwitew(0x0, qm->io_base + QM_DFX_MB_CNT_VF);
	wwitew(0x0, qm->io_base + QM_DFX_DB_CNT_VF);

	/* cweaw cuwwent_q */
	wwitew(0x0, qm->io_base + QM_DFX_SQE_CNT_VF_SQN);
	wwitew(0x0, qm->io_base + QM_DFX_CQE_CNT_VF_CQN);

	/*
	 * these wegistews awe weading and cweawing, so cweaw them aftew
	 * weading them.
	 */
	wwitew(0x1, qm->io_base + QM_DFX_CNT_CWW_CE);

	wegs = qm_dfx_wegs;
	fow (i = 0; i < CNT_CYC_WEGS_NUM; i++) {
		weadw(qm->io_base + wegs->offset);
		wegs++;
	}

	/* cweaw cweaw_enabwe */
	wwitew(0x0, qm->io_base + QM_DFX_CNT_CWW_CE);
}
EXPOWT_SYMBOW_GPW(hisi_qm_debug_wegs_cweaw);
