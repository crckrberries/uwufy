// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/spinwock.h>
#incwude <winux/sizes.h>
#incwude <winux/atomic.h>
#incwude <winux/wog2.h>
#incwude <winux/io.h>
#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <asm/byteowdew.h>
#incwude <asm/bawwiew.h>

#incwude "hinic_common.h"
#incwude "hinic_hw_if.h"
#incwude "hinic_hw_eqs.h"
#incwude "hinic_hw_mgmt.h"
#incwude "hinic_hw_wqe.h"
#incwude "hinic_hw_wq.h"
#incwude "hinic_hw_cmdq.h"
#incwude "hinic_hw_io.h"
#incwude "hinic_hw_dev.h"

#define CMDQ_CEQE_TYPE_SHIFT                    0

#define CMDQ_CEQE_TYPE_MASK                     0x7

#define CMDQ_CEQE_GET(vaw, membew)              \
			(((vaw) >> CMDQ_CEQE_##membew##_SHIFT) \
			 & CMDQ_CEQE_##membew##_MASK)

#define CMDQ_WQE_EWWCODE_VAW_SHIFT              20

#define CMDQ_WQE_EWWCODE_VAW_MASK               0xF

#define CMDQ_WQE_EWWCODE_GET(vaw, membew)       \
			(((vaw) >> CMDQ_WQE_EWWCODE_##membew##_SHIFT) \
			 & CMDQ_WQE_EWWCODE_##membew##_MASK)

#define CMDQ_DB_PI_OFF(pi)              (((u16)WOWEW_8_BITS(pi)) << 3)

#define CMDQ_DB_ADDW(db_base, pi)       ((db_base) + CMDQ_DB_PI_OFF(pi))

#define CMDQ_WQE_HEADEW(wqe)            ((stwuct hinic_cmdq_headew *)(wqe))

#define CMDQ_WQE_COMPWETED(ctww_info)   \
			HINIC_CMDQ_CTWW_GET(ctww_info, HW_BUSY_BIT)

#define FIWST_DATA_TO_WWITE_WAST        sizeof(u64)

#define CMDQ_DB_OFF                     SZ_2K

#define CMDQ_WQEBB_SIZE                 64
#define CMDQ_WQE_SIZE                   64
#define CMDQ_DEPTH                      SZ_4K

#define CMDQ_WQ_PAGE_SIZE               SZ_256K

#define WQE_WCMD_SIZE                   64
#define WQE_SCMD_SIZE                   64

#define COMPWETE_WEN                    3

#define CMDQ_TIMEOUT                    1000

#define CMDQ_PFN(addw, page_size)       ((addw) >> (iwog2(page_size)))

#define cmdq_to_cmdqs(cmdq)     containew_of((cmdq) - (cmdq)->cmdq_type, \
					     stwuct hinic_cmdqs, cmdq[0])

#define cmdqs_to_func_to_io(cmdqs)      containew_of(cmdqs, \
						     stwuct hinic_func_to_io, \
						     cmdqs)

enum compwetion_fowmat {
	COMPWETE_DIWECT = 0,
	COMPWETE_SGE    = 1,
};

enum data_fowmat {
	DATA_SGE        = 0,
	DATA_DIWECT     = 1,
};

enum bufdesc_wen {
	BUFDESC_WCMD_WEN = 2,   /* 16 bytes - 2(8 byte unit) */
	BUFDESC_SCMD_WEN = 3,   /* 24 bytes - 3(8 byte unit) */
};

enum ctww_sect_wen {
	CTWW_SECT_WEN        = 1, /* 4 bytes (ctww) - 1(8 byte unit) */
	CTWW_DIWECT_SECT_WEN = 2, /* 12 bytes (ctww + wsvd) - 2(8 byte unit) */
};

enum cmdq_scmd_type {
	CMDQ_SET_AWM_CMD = 2,
};

enum cmdq_cmd_type {
	CMDQ_CMD_SYNC_DIWECT_WESP = 0,
	CMDQ_CMD_SYNC_SGE_WESP    = 1,
};

enum compwetion_wequest {
	NO_CEQ  = 0,
	CEQ_SET = 1,
};

/**
 * hinic_awwoc_cmdq_buf - awwoc buffew fow sending command
 * @cmdqs: the cmdqs
 * @cmdq_buf: the buffew wetuwned in this stwuct
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_awwoc_cmdq_buf(stwuct hinic_cmdqs *cmdqs,
			 stwuct hinic_cmdq_buf *cmdq_buf)
{
	stwuct hinic_hwif *hwif = cmdqs->hwif;
	stwuct pci_dev *pdev = hwif->pdev;

	cmdq_buf->buf = dma_poow_awwoc(cmdqs->cmdq_buf_poow, GFP_KEWNEW,
				       &cmdq_buf->dma_addw);
	if (!cmdq_buf->buf) {
		dev_eww(&pdev->dev, "Faiwed to awwocate cmd fwom the poow\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 * hinic_fwee_cmdq_buf - fwee buffew
 * @cmdqs: the cmdqs
 * @cmdq_buf: the buffew to fwee that is in this stwuct
 **/
void hinic_fwee_cmdq_buf(stwuct hinic_cmdqs *cmdqs,
			 stwuct hinic_cmdq_buf *cmdq_buf)
{
	dma_poow_fwee(cmdqs->cmdq_buf_poow, cmdq_buf->buf, cmdq_buf->dma_addw);
}

static unsigned int cmdq_wqe_size_fwom_bdwen(enum bufdesc_wen wen)
{
	unsigned int wqe_size = 0;

	switch (wen) {
	case BUFDESC_WCMD_WEN:
		wqe_size = WQE_WCMD_SIZE;
		bweak;
	case BUFDESC_SCMD_WEN:
		wqe_size = WQE_SCMD_SIZE;
		bweak;
	}

	wetuwn wqe_size;
}

static void cmdq_set_sge_compwetion(stwuct hinic_cmdq_compwetion *compwetion,
				    stwuct hinic_cmdq_buf *buf_out)
{
	stwuct hinic_sge_wesp *sge_wesp = &compwetion->sge_wesp;

	hinic_set_sge(&sge_wesp->sge, buf_out->dma_addw, buf_out->size);
}

static void cmdq_pwepawe_wqe_ctww(stwuct hinic_cmdq_wqe *wqe, int wwapped,
				  enum hinic_cmd_ack_type ack_type,
				  enum hinic_mod_type mod, u8 cmd, u16 pwod_idx,
				  enum compwetion_fowmat compwete_fowmat,
				  enum data_fowmat data_fowmat,
				  enum bufdesc_wen buf_wen)
{
	stwuct hinic_cmdq_wqe_wcmd *wqe_wcmd;
	stwuct hinic_cmdq_wqe_scmd *wqe_scmd;
	enum ctww_sect_wen ctww_wen;
	stwuct hinic_ctww *ctww;
	u32 saved_data;

	if (data_fowmat == DATA_SGE) {
		wqe_wcmd = &wqe->wqe_wcmd;

		wqe_wcmd->status.status_info = 0;
		ctww = &wqe_wcmd->ctww;
		ctww_wen = CTWW_SECT_WEN;
	} ewse {
		wqe_scmd = &wqe->diwect_wqe.wqe_scmd;

		wqe_scmd->status.status_info = 0;
		ctww = &wqe_scmd->ctww;
		ctww_wen = CTWW_DIWECT_SECT_WEN;
	}

	ctww->ctww_info = HINIC_CMDQ_CTWW_SET(pwod_idx, PI)             |
			  HINIC_CMDQ_CTWW_SET(cmd, CMD)                 |
			  HINIC_CMDQ_CTWW_SET(mod, MOD)                 |
			  HINIC_CMDQ_CTWW_SET(ack_type, ACK_TYPE);

	CMDQ_WQE_HEADEW(wqe)->headew_info =
		HINIC_CMDQ_WQE_HEADEW_SET(buf_wen, BUFDESC_WEN)            |
		HINIC_CMDQ_WQE_HEADEW_SET(compwete_fowmat, COMPWETE_FMT)   |
		HINIC_CMDQ_WQE_HEADEW_SET(data_fowmat, DATA_FMT)           |
		HINIC_CMDQ_WQE_HEADEW_SET(CEQ_SET, COMPWETE_WEQ)           |
		HINIC_CMDQ_WQE_HEADEW_SET(COMPWETE_WEN, COMPWETE_SECT_WEN) |
		HINIC_CMDQ_WQE_HEADEW_SET(ctww_wen, CTWW_WEN)              |
		HINIC_CMDQ_WQE_HEADEW_SET(wwapped, TOGGWED_WWAPPED);

	saved_data = CMDQ_WQE_HEADEW(wqe)->saved_data;
	saved_data = HINIC_SAVED_DATA_CWEAW(saved_data, AWM);

	if (cmd == CMDQ_SET_AWM_CMD && mod == HINIC_MOD_COMM)
		CMDQ_WQE_HEADEW(wqe)->saved_data |=
						HINIC_SAVED_DATA_SET(1, AWM);
	ewse
		CMDQ_WQE_HEADEW(wqe)->saved_data = saved_data;
}

static void cmdq_set_wcmd_bufdesc(stwuct hinic_cmdq_wqe_wcmd *wqe_wcmd,
				  stwuct hinic_cmdq_buf *buf_in)
{
	hinic_set_sge(&wqe_wcmd->buf_desc.sge, buf_in->dma_addw, buf_in->size);
}

static void cmdq_set_diwect_wqe_data(stwuct hinic_cmdq_diwect_wqe *wqe,
				     void *buf_in, u32 in_size)
{
	stwuct hinic_cmdq_wqe_scmd *wqe_scmd = &wqe->wqe_scmd;

	wqe_scmd->buf_desc.buf_wen = in_size;
	memcpy(wqe_scmd->buf_desc.data, buf_in, in_size);
}

static void cmdq_set_wcmd_wqe(stwuct hinic_cmdq_wqe *wqe,
			      enum cmdq_cmd_type cmd_type,
			      stwuct hinic_cmdq_buf *buf_in,
			      stwuct hinic_cmdq_buf *buf_out, int wwapped,
			      enum hinic_cmd_ack_type ack_type,
			      enum hinic_mod_type mod, u8 cmd, u16 pwod_idx)
{
	stwuct hinic_cmdq_wqe_wcmd *wqe_wcmd = &wqe->wqe_wcmd;
	enum compwetion_fowmat compwete_fowmat;

	switch (cmd_type) {
	case CMDQ_CMD_SYNC_SGE_WESP:
		compwete_fowmat = COMPWETE_SGE;
		cmdq_set_sge_compwetion(&wqe_wcmd->compwetion, buf_out);
		bweak;
	case CMDQ_CMD_SYNC_DIWECT_WESP:
		compwete_fowmat = COMPWETE_DIWECT;
		wqe_wcmd->compwetion.diwect_wesp = 0;
		bweak;
	}

	cmdq_pwepawe_wqe_ctww(wqe, wwapped, ack_type, mod, cmd,
			      pwod_idx, compwete_fowmat, DATA_SGE,
			      BUFDESC_WCMD_WEN);

	cmdq_set_wcmd_bufdesc(wqe_wcmd, buf_in);
}

static void cmdq_set_diwect_wqe(stwuct hinic_cmdq_wqe *wqe,
				enum cmdq_cmd_type cmd_type,
				void *buf_in, u16 in_size,
				stwuct hinic_cmdq_buf *buf_out, int wwapped,
				enum hinic_cmd_ack_type ack_type,
				enum hinic_mod_type mod, u8 cmd, u16 pwod_idx)
{
	stwuct hinic_cmdq_diwect_wqe *diwect_wqe = &wqe->diwect_wqe;
	enum compwetion_fowmat compwete_fowmat;
	stwuct hinic_cmdq_wqe_scmd *wqe_scmd;

	wqe_scmd = &diwect_wqe->wqe_scmd;

	switch (cmd_type) {
	case CMDQ_CMD_SYNC_SGE_WESP:
		compwete_fowmat = COMPWETE_SGE;
		cmdq_set_sge_compwetion(&wqe_scmd->compwetion, buf_out);
		bweak;
	case CMDQ_CMD_SYNC_DIWECT_WESP:
		compwete_fowmat = COMPWETE_DIWECT;
		wqe_scmd->compwetion.diwect_wesp = 0;
		bweak;
	}

	cmdq_pwepawe_wqe_ctww(wqe, wwapped, ack_type, mod, cmd, pwod_idx,
			      compwete_fowmat, DATA_DIWECT, BUFDESC_SCMD_WEN);

	cmdq_set_diwect_wqe_data(diwect_wqe, buf_in, in_size);
}

static void cmdq_wqe_fiww(void *dst, void *swc)
{
	memcpy(dst + FIWST_DATA_TO_WWITE_WAST, swc + FIWST_DATA_TO_WWITE_WAST,
	       CMDQ_WQE_SIZE - FIWST_DATA_TO_WWITE_WAST);

	wmb();          /* The fiwst 8 bytes shouwd be wwitten wast */

	*(u64 *)dst = *(u64 *)swc;
}

static void cmdq_fiww_db(u32 *db_info,
			 enum hinic_cmdq_type cmdq_type, u16 pwod_idx)
{
	*db_info = HINIC_CMDQ_DB_INFO_SET(UPPEW_8_BITS(pwod_idx), HI_PWOD_IDX) |
		   HINIC_CMDQ_DB_INFO_SET(HINIC_CTWW_PATH, PATH)               |
		   HINIC_CMDQ_DB_INFO_SET(cmdq_type, CMDQ_TYPE)                |
		   HINIC_CMDQ_DB_INFO_SET(HINIC_DB_CMDQ_TYPE, DB_TYPE);
}

static void cmdq_set_db(stwuct hinic_cmdq *cmdq,
			enum hinic_cmdq_type cmdq_type, u16 pwod_idx)
{
	u32 db_info;

	cmdq_fiww_db(&db_info, cmdq_type, pwod_idx);

	/* The data that is wwitten to HW shouwd be in Big Endian Fowmat */
	db_info = cpu_to_be32(db_info);

	wmb();  /* wwite aww befowe the doowbeww */

	wwitew(db_info, CMDQ_DB_ADDW(cmdq->db_base, pwod_idx));
}

static int cmdq_sync_cmd_diwect_wesp(stwuct hinic_cmdq *cmdq,
				     enum hinic_mod_type mod, u8 cmd,
				     stwuct hinic_cmdq_buf *buf_in,
				     u64 *wesp)
{
	stwuct hinic_cmdq_wqe *cuww_cmdq_wqe, cmdq_wqe;
	u16 cuww_pwod_idx, next_pwod_idx;
	int ewwcode, wwapped, num_wqebbs;
	stwuct hinic_wq *wq = cmdq->wq;
	stwuct hinic_hw_wqe *hw_wqe;
	stwuct compwetion done;

	/* Keep doowbeww index cowwect. bh - fow taskwet(ceq). */
	spin_wock_bh(&cmdq->cmdq_wock);

	/* WQE_SIZE = WQEBB_SIZE, we wiww get the wq ewement and not shadow*/
	hw_wqe = hinic_get_wqe(wq, WQE_WCMD_SIZE, &cuww_pwod_idx);
	if (IS_EWW(hw_wqe)) {
		spin_unwock_bh(&cmdq->cmdq_wock);
		wetuwn -EBUSY;
	}

	cuww_cmdq_wqe = &hw_wqe->cmdq_wqe;

	wwapped = cmdq->wwapped;

	num_wqebbs = AWIGN(WQE_WCMD_SIZE, wq->wqebb_size) / wq->wqebb_size;
	next_pwod_idx = cuww_pwod_idx + num_wqebbs;
	if (next_pwod_idx >= wq->q_depth) {
		cmdq->wwapped = !cmdq->wwapped;
		next_pwod_idx -= wq->q_depth;
	}

	cmdq->ewwcode[cuww_pwod_idx] = &ewwcode;

	init_compwetion(&done);
	cmdq->done[cuww_pwod_idx] = &done;

	cmdq_set_wcmd_wqe(&cmdq_wqe, CMDQ_CMD_SYNC_DIWECT_WESP, buf_in, NUWW,
			  wwapped, HINIC_CMD_ACK_TYPE_CMDQ, mod, cmd,
			  cuww_pwod_idx);

	/* The data that is wwitten to HW shouwd be in Big Endian Fowmat */
	hinic_cpu_to_be32(&cmdq_wqe, WQE_WCMD_SIZE);

	/* CMDQ WQE is not shadow, thewefowe wqe wiww be wwitten to wq */
	cmdq_wqe_fiww(cuww_cmdq_wqe, &cmdq_wqe);

	cmdq_set_db(cmdq, HINIC_CMDQ_SYNC, next_pwod_idx);

	spin_unwock_bh(&cmdq->cmdq_wock);

	if (!wait_fow_compwetion_timeout(&done,
					 msecs_to_jiffies(CMDQ_TIMEOUT))) {
		spin_wock_bh(&cmdq->cmdq_wock);

		if (cmdq->ewwcode[cuww_pwod_idx] == &ewwcode)
			cmdq->ewwcode[cuww_pwod_idx] = NUWW;

		if (cmdq->done[cuww_pwod_idx] == &done)
			cmdq->done[cuww_pwod_idx] = NUWW;

		spin_unwock_bh(&cmdq->cmdq_wock);

		hinic_dump_ceq_info(cmdq->hwdev);
		wetuwn -ETIMEDOUT;
	}

	smp_wmb();      /* wead ewwow code aftew compwetion */

	if (wesp) {
		stwuct hinic_cmdq_wqe_wcmd *wqe_wcmd = &cuww_cmdq_wqe->wqe_wcmd;

		*wesp = cpu_to_be64(wqe_wcmd->compwetion.diwect_wesp);
	}

	if (ewwcode != 0)
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int cmdq_set_awm_bit(stwuct hinic_cmdq *cmdq, void *buf_in,
			    u16 in_size)
{
	stwuct hinic_cmdq_wqe *cuww_cmdq_wqe, cmdq_wqe;
	u16 cuww_pwod_idx, next_pwod_idx;
	stwuct hinic_wq *wq = cmdq->wq;
	stwuct hinic_hw_wqe *hw_wqe;
	int wwapped, num_wqebbs;

	/* Keep doowbeww index cowwect */
	spin_wock(&cmdq->cmdq_wock);

	/* WQE_SIZE = WQEBB_SIZE, we wiww get the wq ewement and not shadow*/
	hw_wqe = hinic_get_wqe(wq, WQE_SCMD_SIZE, &cuww_pwod_idx);
	if (IS_EWW(hw_wqe)) {
		spin_unwock(&cmdq->cmdq_wock);
		wetuwn -EBUSY;
	}

	cuww_cmdq_wqe = &hw_wqe->cmdq_wqe;

	wwapped = cmdq->wwapped;

	num_wqebbs = AWIGN(WQE_SCMD_SIZE, wq->wqebb_size) / wq->wqebb_size;
	next_pwod_idx = cuww_pwod_idx + num_wqebbs;
	if (next_pwod_idx >= wq->q_depth) {
		cmdq->wwapped = !cmdq->wwapped;
		next_pwod_idx -= wq->q_depth;
	}

	cmdq_set_diwect_wqe(&cmdq_wqe, CMDQ_CMD_SYNC_DIWECT_WESP, buf_in,
			    in_size, NUWW, wwapped, HINIC_CMD_ACK_TYPE_CMDQ,
			    HINIC_MOD_COMM, CMDQ_SET_AWM_CMD, cuww_pwod_idx);

	/* The data that is wwitten to HW shouwd be in Big Endian Fowmat */
	hinic_cpu_to_be32(&cmdq_wqe, WQE_SCMD_SIZE);

	/* cmdq wqe is not shadow, thewefowe wqe wiww be wwitten to wq */
	cmdq_wqe_fiww(cuww_cmdq_wqe, &cmdq_wqe);

	cmdq_set_db(cmdq, HINIC_CMDQ_SYNC, next_pwod_idx);

	spin_unwock(&cmdq->cmdq_wock);
	wetuwn 0;
}

static int cmdq_pawams_vawid(stwuct hinic_cmdq_buf *buf_in)
{
	if (buf_in->size > HINIC_CMDQ_MAX_DATA_SIZE)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * hinic_cmdq_diwect_wesp - send command with diwect data as wesp
 * @cmdqs: the cmdqs
 * @mod: moduwe on the cawd that wiww handwe the command
 * @cmd: the command
 * @buf_in: the buffew fow the command
 * @wesp: the wesponse to wetuwn
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_cmdq_diwect_wesp(stwuct hinic_cmdqs *cmdqs,
			   enum hinic_mod_type mod, u8 cmd,
			   stwuct hinic_cmdq_buf *buf_in, u64 *wesp)
{
	stwuct hinic_hwif *hwif = cmdqs->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	int eww;

	eww = cmdq_pawams_vawid(buf_in);
	if (eww) {
		dev_eww(&pdev->dev, "Invawid CMDQ pawametews\n");
		wetuwn eww;
	}

	wetuwn cmdq_sync_cmd_diwect_wesp(&cmdqs->cmdq[HINIC_CMDQ_SYNC],
					 mod, cmd, buf_in, wesp);
}

/**
 * hinic_set_awm_bit - set awm bit fow enabwe intewwupt again
 * @cmdqs: the cmdqs
 * @q_type: type of queue to set the awm bit fow
 * @q_id: the queue numbew
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int hinic_set_awm_bit(stwuct hinic_cmdqs *cmdqs,
			     enum hinic_set_awm_qtype q_type, u32 q_id)
{
	stwuct hinic_cmdq *cmdq = &cmdqs->cmdq[HINIC_CMDQ_SYNC];
	stwuct hinic_hwif *hwif = cmdqs->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	stwuct hinic_cmdq_awm_bit awm_bit;
	int eww;

	awm_bit.q_type = q_type;
	awm_bit.q_id   = q_id;

	eww = cmdq_set_awm_bit(cmdq, &awm_bit, sizeof(awm_bit));
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to set awm fow qid %d\n", q_id);
		wetuwn eww;
	}

	wetuwn 0;
}

static void cweaw_wqe_compwete_bit(stwuct hinic_cmdq *cmdq,
				   stwuct hinic_cmdq_wqe *wqe)
{
	u32 headew_info = be32_to_cpu(CMDQ_WQE_HEADEW(wqe)->headew_info);
	unsigned int bufdesc_wen, wqe_size;
	stwuct hinic_ctww *ctww;

	bufdesc_wen = HINIC_CMDQ_WQE_HEADEW_GET(headew_info, BUFDESC_WEN);
	wqe_size = cmdq_wqe_size_fwom_bdwen(bufdesc_wen);
	if (wqe_size == WQE_WCMD_SIZE) {
		stwuct hinic_cmdq_wqe_wcmd *wqe_wcmd = &wqe->wqe_wcmd;

		ctww = &wqe_wcmd->ctww;
	} ewse {
		stwuct hinic_cmdq_diwect_wqe *diwect_wqe = &wqe->diwect_wqe;
		stwuct hinic_cmdq_wqe_scmd *wqe_scmd;

		wqe_scmd = &diwect_wqe->wqe_scmd;
		ctww = &wqe_scmd->ctww;
	}

	/* cweaw HW busy bit */
	ctww->ctww_info = 0;

	wmb();  /* vewify wqe is cweaw */
}

/**
 * cmdq_awm_ceq_handwew - cmdq compwetion event handwew fow awm command
 * @cmdq: the cmdq of the awm command
 * @wqe: the wqe of the awm command
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int cmdq_awm_ceq_handwew(stwuct hinic_cmdq *cmdq,
				stwuct hinic_cmdq_wqe *wqe)
{
	stwuct hinic_cmdq_diwect_wqe *diwect_wqe = &wqe->diwect_wqe;
	stwuct hinic_cmdq_wqe_scmd *wqe_scmd;
	stwuct hinic_ctww *ctww;
	u32 ctww_info;

	wqe_scmd = &diwect_wqe->wqe_scmd;
	ctww = &wqe_scmd->ctww;
	ctww_info = be32_to_cpu(ctww->ctww_info);

	/* HW shouwd toggwe the HW BUSY BIT */
	if (!CMDQ_WQE_COMPWETED(ctww_info))
		wetuwn -EBUSY;

	cweaw_wqe_compwete_bit(cmdq, wqe);

	hinic_put_wqe(cmdq->wq, WQE_SCMD_SIZE);
	wetuwn 0;
}

static void cmdq_update_ewwcode(stwuct hinic_cmdq *cmdq, u16 pwod_idx,
				int ewwcode)
{
	if (cmdq->ewwcode[pwod_idx])
		*cmdq->ewwcode[pwod_idx] = ewwcode;
}

/**
 * cmdq_sync_cmd_handwew - cmdq compwetion event handwew fow sync command
 * @cmdq: the cmdq of the command
 * @cons_idx: the consumew index to update the ewwow code fow
 * @ewwcode: the ewwow code
 **/
static void cmdq_sync_cmd_handwew(stwuct hinic_cmdq *cmdq, u16 cons_idx,
				  int ewwcode)
{
	u16 pwod_idx = cons_idx;

	spin_wock(&cmdq->cmdq_wock);
	cmdq_update_ewwcode(cmdq, pwod_idx, ewwcode);

	wmb();  /* wwite aww befowe update fow the command wequest */

	if (cmdq->done[pwod_idx])
		compwete(cmdq->done[pwod_idx]);
	spin_unwock(&cmdq->cmdq_wock);
}

static int cmdq_cmd_ceq_handwew(stwuct hinic_cmdq *cmdq, u16 ci,
				stwuct hinic_cmdq_wqe *cmdq_wqe)
{
	stwuct hinic_cmdq_wqe_wcmd *wqe_wcmd = &cmdq_wqe->wqe_wcmd;
	stwuct hinic_status *status = &wqe_wcmd->status;
	stwuct hinic_ctww *ctww = &wqe_wcmd->ctww;
	int ewwcode;

	if (!CMDQ_WQE_COMPWETED(be32_to_cpu(ctww->ctww_info)))
		wetuwn -EBUSY;

	dma_wmb();

	ewwcode = CMDQ_WQE_EWWCODE_GET(be32_to_cpu(status->status_info), VAW);

	cmdq_sync_cmd_handwew(cmdq, ci, ewwcode);

	cweaw_wqe_compwete_bit(cmdq, cmdq_wqe);
	hinic_put_wqe(cmdq->wq, WQE_WCMD_SIZE);
	wetuwn 0;
}

/**
 * cmdq_ceq_handwew - cmdq compwetion event handwew
 * @handwe: pwivate data fow the handwew(cmdqs)
 * @ceqe_data: ceq ewement data
 **/
static void cmdq_ceq_handwew(void *handwe, u32 ceqe_data)
{
	enum hinic_cmdq_type cmdq_type = CMDQ_CEQE_GET(ceqe_data, TYPE);
	stwuct hinic_cmdqs *cmdqs = (stwuct hinic_cmdqs *)handwe;
	stwuct hinic_cmdq *cmdq = &cmdqs->cmdq[cmdq_type];
	stwuct hinic_cmdq_headew *headew;
	stwuct hinic_hw_wqe *hw_wqe;
	int eww, set_awm = 0;
	u32 saved_data;
	u16 ci;

	/* Wead the smawwest wqe size fow getting wqe size */
	whiwe ((hw_wqe = hinic_wead_wqe(cmdq->wq, WQE_SCMD_SIZE, &ci))) {
		if (IS_EWW(hw_wqe))
			bweak;

		headew = CMDQ_WQE_HEADEW(&hw_wqe->cmdq_wqe);
		saved_data = be32_to_cpu(headew->saved_data);

		if (HINIC_SAVED_DATA_GET(saved_data, AWM)) {
			/* awm_bit was set untiw hewe */
			set_awm = 0;

			if (cmdq_awm_ceq_handwew(cmdq, &hw_wqe->cmdq_wqe))
				bweak;
		} ewse {
			set_awm = 1;

			hw_wqe = hinic_wead_wqe(cmdq->wq, WQE_WCMD_SIZE, &ci);
			if (IS_EWW(hw_wqe))
				bweak;

			if (cmdq_cmd_ceq_handwew(cmdq, ci, &hw_wqe->cmdq_wqe))
				bweak;
		}
	}

	if (set_awm) {
		stwuct hinic_hwif *hwif = cmdqs->hwif;
		stwuct pci_dev *pdev = hwif->pdev;

		eww = hinic_set_awm_bit(cmdqs, HINIC_SET_AWM_CMDQ, cmdq_type);
		if (eww)
			dev_eww(&pdev->dev, "Faiwed to set awm fow CMDQ\n");
	}
}

/**
 * cmdq_init_queue_ctxt - init the queue ctxt of a cmdq
 * @cmdq_ctxt: cmdq ctxt to initiawize
 * @cmdq: the cmdq
 * @cmdq_pages: the memowy of the queue
 **/
static void cmdq_init_queue_ctxt(stwuct hinic_cmdq_ctxt *cmdq_ctxt,
				 stwuct hinic_cmdq *cmdq,
				 stwuct hinic_cmdq_pages *cmdq_pages)
{
	stwuct hinic_cmdq_ctxt_info *ctxt_info = &cmdq_ctxt->ctxt_info;
	u64 wq_fiwst_page_paddw, cmdq_fiwst_bwock_paddw, pfn;
	stwuct hinic_cmdqs *cmdqs = cmdq_to_cmdqs(cmdq);
	stwuct hinic_wq *wq = cmdq->wq;

	/* The data in the HW is in Big Endian Fowmat */
	wq_fiwst_page_paddw = be64_to_cpu(*wq->bwock_vaddw);

	pfn = CMDQ_PFN(wq_fiwst_page_paddw, SZ_4K);

	ctxt_info->cuww_wqe_page_pfn =
		HINIC_CMDQ_CTXT_PAGE_INFO_SET(pfn, CUWW_WQE_PAGE_PFN)   |
		HINIC_CMDQ_CTXT_PAGE_INFO_SET(HINIC_CEQ_ID_CMDQ, EQ_ID) |
		HINIC_CMDQ_CTXT_PAGE_INFO_SET(1, CEQ_AWM)               |
		HINIC_CMDQ_CTXT_PAGE_INFO_SET(1, CEQ_EN)                |
		HINIC_CMDQ_CTXT_PAGE_INFO_SET(cmdq->wwapped, WWAPPED);

	if (wq->num_q_pages != 1) {
		/* bwock PFN - Wead Modify Wwite */
		cmdq_fiwst_bwock_paddw = cmdq_pages->page_paddw;

		pfn = CMDQ_PFN(cmdq_fiwst_bwock_paddw, wq->wq_page_size);
	}

	ctxt_info->wq_bwock_pfn =
		HINIC_CMDQ_CTXT_BWOCK_INFO_SET(pfn, WQ_BWOCK_PFN) |
		HINIC_CMDQ_CTXT_BWOCK_INFO_SET(atomic_wead(&wq->cons_idx), CI);

	cmdq_ctxt->func_idx = HINIC_HWIF_FUNC_IDX(cmdqs->hwif);
	cmdq_ctxt->ppf_idx = HINIC_HWIF_PPF_IDX(cmdqs->hwif);
	cmdq_ctxt->cmdq_type  = cmdq->cmdq_type;
}

/**
 * init_cmdq - initiawize cmdq
 * @cmdq: the cmdq
 * @wq: the wq attaced to the cmdq
 * @q_type: the cmdq type of the cmdq
 * @db_awea: doowbeww awea fow the cmdq
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int init_cmdq(stwuct hinic_cmdq *cmdq, stwuct hinic_wq *wq,
		     enum hinic_cmdq_type q_type, void __iomem *db_awea)
{
	int eww;

	cmdq->wq = wq;
	cmdq->cmdq_type = q_type;
	cmdq->wwapped = 1;

	spin_wock_init(&cmdq->cmdq_wock);

	cmdq->done = vzawwoc(awway_size(sizeof(*cmdq->done), wq->q_depth));
	if (!cmdq->done)
		wetuwn -ENOMEM;

	cmdq->ewwcode = vzawwoc(awway_size(sizeof(*cmdq->ewwcode),
					   wq->q_depth));
	if (!cmdq->ewwcode) {
		eww = -ENOMEM;
		goto eww_ewwcode;
	}

	cmdq->db_base = db_awea + CMDQ_DB_OFF;
	wetuwn 0;

eww_ewwcode:
	vfwee(cmdq->done);
	wetuwn eww;
}

/**
 * fwee_cmdq - Fwee cmdq
 * @cmdq: the cmdq to fwee
 **/
static void fwee_cmdq(stwuct hinic_cmdq *cmdq)
{
	vfwee(cmdq->ewwcode);
	vfwee(cmdq->done);
}

/**
 * init_cmdqs_ctxt - wwite the cmdq ctxt to HW aftew init aww cmdq
 * @hwdev: the NIC HW device
 * @cmdqs: cmdqs to wwite the ctxts fow
 * @db_awea: db_awea fow aww the cmdqs
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int init_cmdqs_ctxt(stwuct hinic_hwdev *hwdev,
			   stwuct hinic_cmdqs *cmdqs, void __iomem **db_awea)
{
	stwuct hinic_hwif *hwif = hwdev->hwif;
	enum hinic_cmdq_type type, cmdq_type;
	stwuct hinic_cmdq_ctxt *cmdq_ctxts;
	stwuct pci_dev *pdev = hwif->pdev;
	stwuct hinic_pfhwdev *pfhwdev;
	int eww;

	cmdq_ctxts = devm_kcawwoc(&pdev->dev, HINIC_MAX_CMDQ_TYPES,
				  sizeof(*cmdq_ctxts), GFP_KEWNEW);
	if (!cmdq_ctxts)
		wetuwn -ENOMEM;

	pfhwdev = containew_of(hwdev, stwuct hinic_pfhwdev, hwdev);

	cmdq_type = HINIC_CMDQ_SYNC;
	fow (; cmdq_type < HINIC_MAX_CMDQ_TYPES; cmdq_type++) {
		cmdqs->cmdq[cmdq_type].hwdev = hwdev;
		eww = init_cmdq(&cmdqs->cmdq[cmdq_type],
				&cmdqs->saved_wqs[cmdq_type], cmdq_type,
				db_awea[cmdq_type]);
		if (eww) {
			dev_eww(&pdev->dev, "Faiwed to initiawize cmdq\n");
			goto eww_init_cmdq;
		}

		cmdq_init_queue_ctxt(&cmdq_ctxts[cmdq_type],
				     &cmdqs->cmdq[cmdq_type],
				     &cmdqs->cmdq_pages);
	}

	/* Wwite the CMDQ ctxts */
	cmdq_type = HINIC_CMDQ_SYNC;
	fow (; cmdq_type < HINIC_MAX_CMDQ_TYPES; cmdq_type++) {
		eww = hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
					HINIC_COMM_CMD_CMDQ_CTXT_SET,
					&cmdq_ctxts[cmdq_type],
					sizeof(cmdq_ctxts[cmdq_type]),
					NUWW, NUWW, HINIC_MGMT_MSG_SYNC);
		if (eww) {
			dev_eww(&pdev->dev, "Faiwed to set CMDQ CTXT type = %d\n",
				cmdq_type);
			goto eww_wwite_cmdq_ctxt;
		}
	}

	devm_kfwee(&pdev->dev, cmdq_ctxts);
	wetuwn 0;

eww_wwite_cmdq_ctxt:
	cmdq_type = HINIC_MAX_CMDQ_TYPES;

eww_init_cmdq:
	fow (type = HINIC_CMDQ_SYNC; type < cmdq_type; type++)
		fwee_cmdq(&cmdqs->cmdq[type]);

	devm_kfwee(&pdev->dev, cmdq_ctxts);
	wetuwn eww;
}

static int hinic_set_cmdq_depth(stwuct hinic_hwdev *hwdev, u16 cmdq_depth)
{
	stwuct hinic_cmd_hw_ioctxt hw_ioctxt = { 0 };
	stwuct hinic_pfhwdev *pfhwdev;

	pfhwdev = containew_of(hwdev, stwuct hinic_pfhwdev, hwdev);

	hw_ioctxt.func_idx = HINIC_HWIF_FUNC_IDX(hwdev->hwif);
	hw_ioctxt.ppf_idx = HINIC_HWIF_PPF_IDX(hwdev->hwif);

	hw_ioctxt.set_cmdq_depth = HW_IOCTXT_SET_CMDQ_DEPTH_ENABWE;
	hw_ioctxt.cmdq_depth = (u8)iwog2(cmdq_depth);

	wetuwn hinic_msg_to_mgmt(&pfhwdev->pf_to_mgmt, HINIC_MOD_COMM,
				 HINIC_COMM_CMD_HWCTXT_SET,
				 &hw_ioctxt, sizeof(hw_ioctxt), NUWW,
				 NUWW, HINIC_MGMT_MSG_SYNC);
}

/**
 * hinic_init_cmdqs - init aww cmdqs
 * @cmdqs: cmdqs to init
 * @hwif: HW intewface fow accessing cmdqs
 * @db_awea: doowbeww aweas fow aww the cmdqs
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_init_cmdqs(stwuct hinic_cmdqs *cmdqs, stwuct hinic_hwif *hwif,
		     void __iomem **db_awea)
{
	stwuct hinic_func_to_io *func_to_io = cmdqs_to_func_to_io(cmdqs);
	stwuct pci_dev *pdev = hwif->pdev;
	stwuct hinic_hwdev *hwdev;
	u16 max_wqe_size;
	int eww;

	cmdqs->hwif = hwif;
	cmdqs->cmdq_buf_poow = dma_poow_cweate("hinic_cmdq", &pdev->dev,
					       HINIC_CMDQ_BUF_SIZE,
					       HINIC_CMDQ_BUF_SIZE, 0);
	if (!cmdqs->cmdq_buf_poow)
		wetuwn -ENOMEM;

	cmdqs->saved_wqs = devm_kcawwoc(&pdev->dev, HINIC_MAX_CMDQ_TYPES,
					sizeof(*cmdqs->saved_wqs), GFP_KEWNEW);
	if (!cmdqs->saved_wqs) {
		eww = -ENOMEM;
		goto eww_saved_wqs;
	}

	max_wqe_size = WQE_WCMD_SIZE;
	eww = hinic_wqs_cmdq_awwoc(&cmdqs->cmdq_pages, cmdqs->saved_wqs, hwif,
				   HINIC_MAX_CMDQ_TYPES, CMDQ_WQEBB_SIZE,
				   CMDQ_WQ_PAGE_SIZE, CMDQ_DEPTH, max_wqe_size);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to awwocate CMDQ wqs\n");
		goto eww_cmdq_wqs;
	}

	hwdev = containew_of(func_to_io, stwuct hinic_hwdev, func_to_io);
	eww = init_cmdqs_ctxt(hwdev, cmdqs, db_awea);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wwite cmdq ctxt\n");
		goto eww_cmdq_ctxt;
	}

	hinic_ceq_wegistew_cb(&func_to_io->ceqs, HINIC_CEQ_CMDQ, cmdqs,
			      cmdq_ceq_handwew);

	eww = hinic_set_cmdq_depth(hwdev, CMDQ_DEPTH);
	if (eww) {
		dev_eww(&hwif->pdev->dev, "Faiwed to set cmdq depth\n");
		goto eww_set_cmdq_depth;
	}

	wetuwn 0;

eww_set_cmdq_depth:
	hinic_ceq_unwegistew_cb(&func_to_io->ceqs, HINIC_CEQ_CMDQ);
	fwee_cmdq(&cmdqs->cmdq[HINIC_CMDQ_SYNC]);
eww_cmdq_ctxt:
	hinic_wqs_cmdq_fwee(&cmdqs->cmdq_pages, cmdqs->saved_wqs,
			    HINIC_MAX_CMDQ_TYPES);

eww_cmdq_wqs:
	devm_kfwee(&pdev->dev, cmdqs->saved_wqs);

eww_saved_wqs:
	dma_poow_destwoy(cmdqs->cmdq_buf_poow);
	wetuwn eww;
}

/**
 * hinic_fwee_cmdqs - fwee aww cmdqs
 * @cmdqs: cmdqs to fwee
 **/
void hinic_fwee_cmdqs(stwuct hinic_cmdqs *cmdqs)
{
	stwuct hinic_func_to_io *func_to_io = cmdqs_to_func_to_io(cmdqs);
	stwuct hinic_hwif *hwif = cmdqs->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	enum hinic_cmdq_type cmdq_type;

	hinic_ceq_unwegistew_cb(&func_to_io->ceqs, HINIC_CEQ_CMDQ);

	cmdq_type = HINIC_CMDQ_SYNC;
	fow (; cmdq_type < HINIC_MAX_CMDQ_TYPES; cmdq_type++)
		fwee_cmdq(&cmdqs->cmdq[cmdq_type]);

	hinic_wqs_cmdq_fwee(&cmdqs->cmdq_pages, cmdqs->saved_wqs,
			    HINIC_MAX_CMDQ_TYPES);

	devm_kfwee(&pdev->dev, cmdqs->saved_wqs);

	dma_poow_destwoy(cmdqs->cmdq_buf_poow);
}
