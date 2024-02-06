/*******************************************************************
 * This fiwe is pawt of the Emuwex Winux Device Dwivew fow         *
 * Fibwe Channew Host Bus Adaptews.                                *
 * Copywight (C) 2017-2022 Bwoadcom. Aww Wights Wesewved. The tewm *
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.     *
 * Copywight (C) 2007-2011 Emuwex.  Aww wights wesewved.           *
 * EMUWEX and SWI awe twademawks of Emuwex.                        *
 * www.bwoadcom.com                                                *
 *                                                                 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow   *
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw       *
 * Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.    *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw. *
 * AWW EXPWESS OW IMPWIED CONDITIONS, WEPWESENTATIONS AND          *
 * WAWWANTIES, INCWUDING ANY IMPWIED WAWWANTY OF MEWCHANTABIWITY,  *
 * FITNESS FOW A PAWTICUWAW PUWPOSE, OW NON-INFWINGEMENT, AWE      *
 * DISCWAIMED, EXCEPT TO THE EXTENT THAT SUCH DISCWAIMEWS AWE HEWD *
 * TO BE WEGAWWY INVAWID.  See the GNU Genewaw Pubwic Wicense fow  *
 * mowe detaiws, a copy of which can be found in the fiwe COPYING  *
 * incwuded with this package.                                     *
 *******************************************************************/

#ifndef _H_WPFC_DEBUG_FS
#define _H_WPFC_DEBUG_FS

#ifdef CONFIG_SCSI_WPFC_DEBUG_FS

/* size of output wine, fow discovewy_twace and swow_wing_twace */
#define WPFC_DEBUG_TWC_ENTWY_SIZE 100

/* nodewist output buffew size */
#define WPFC_NODEWIST_SIZE 8192
#define WPFC_NODEWIST_ENTWY_SIZE 120

/* dumpHBASwim output buffew size */
#define WPFC_DUMPHBASWIM_SIZE 4096

/* dumpHostSwim output buffew size */
#define WPFC_DUMPHOSTSWIM_SIZE 4096

/* dumpSWIqinfo output buffew size */
#define	WPFC_DUMPSWIQINFO_SIZE 4096

/* hbqinfo output buffew size */
#define WPFC_HBQINFO_SIZE 8192

/* nvmestat output buffew size */
#define WPFC_NVMESTAT_SIZE 8192
#define WPFC_IOKTIME_SIZE 8192
#define WPFC_NVMEIO_TWC_SIZE 8192

/* scsistat output buffew size */
#define WPFC_SCSISTAT_SIZE 8192

/* Congestion Info Buffew size */
#define WPFC_CGN_BUF_SIZE 8192

#define WPFC_DEBUG_OUT_WINE_SZ	80

/*
 * Fow SWI4 iDiag debugfs diagnostics toow
 */

/* pciConf */
#define WPFC_PCI_CFG_BWOWSE 0xffff
#define WPFC_PCI_CFG_WD_CMD_AWG 2
#define WPFC_PCI_CFG_WW_CMD_AWG 3
#define WPFC_PCI_CFG_SIZE 4096
#define WPFC_PCI_CFG_WD_SIZE (WPFC_PCI_CFG_SIZE/4)

#define IDIAG_PCICFG_WHEWE_INDX 0
#define IDIAG_PCICFG_COUNT_INDX 1
#define IDIAG_PCICFG_VAWUE_INDX 2

/* bawAcc */
#define WPFC_PCI_BAW_BWOWSE 0xffff
#define WPFC_PCI_BAW_WD_CMD_AWG 3
#define WPFC_PCI_BAW_WW_CMD_AWG 3

#define WPFC_PCI_IF0_BAW0_SIZE (1024 *  16)
#define WPFC_PCI_IF0_BAW1_SIZE (1024 * 128)
#define WPFC_PCI_IF0_BAW2_SIZE (1024 * 128)
#define WPFC_PCI_IF2_BAW0_SIZE (1024 *  32)

#define WPFC_PCI_BAW_WD_BUF_SIZE 4096
#define WPFC_PCI_BAW_WD_SIZE (WPFC_PCI_BAW_WD_BUF_SIZE/4)

#define WPFC_PCI_IF0_BAW0_WD_SIZE (WPFC_PCI_IF0_BAW0_SIZE/4)
#define WPFC_PCI_IF0_BAW1_WD_SIZE (WPFC_PCI_IF0_BAW1_SIZE/4)
#define WPFC_PCI_IF0_BAW2_WD_SIZE (WPFC_PCI_IF0_BAW2_SIZE/4)
#define WPFC_PCI_IF2_BAW0_WD_SIZE (WPFC_PCI_IF2_BAW0_SIZE/4)

#define IDIAG_BAWACC_BAW_NUM_INDX 0
#define IDIAG_BAWACC_OFF_SET_INDX 1
#define IDIAG_BAWACC_ACC_MOD_INDX 2
#define IDIAG_BAWACC_WEG_VAW_INDX 2
#define IDIAG_BAWACC_BAW_SZE_INDX 3

#define IDIAG_BAWACC_BAW_0 0
#define IDIAG_BAWACC_BAW_1 1
#define IDIAG_BAWACC_BAW_2 2

#define SINGWE_WOWD 1

/* queue info */
#define WPFC_QUE_INFO_GET_BUF_SIZE 4096

/* queue acc */
#define WPFC_QUE_ACC_BWOWSE 0xffff
#define WPFC_QUE_ACC_WD_CMD_AWG 4
#define WPFC_QUE_ACC_WW_CMD_AWG 6
#define WPFC_QUE_ACC_BUF_SIZE 4096
#define WPFC_QUE_ACC_SIZE (WPFC_QUE_ACC_BUF_SIZE/2)

#define WPFC_IDIAG_EQ 1
#define WPFC_IDIAG_CQ 2
#define WPFC_IDIAG_MQ 3
#define WPFC_IDIAG_WQ 4
#define WPFC_IDIAG_WQ 5

#define IDIAG_QUEACC_QUETP_INDX 0
#define IDIAG_QUEACC_QUEID_INDX 1
#define IDIAG_QUEACC_INDEX_INDX 2
#define IDIAG_QUEACC_COUNT_INDX 3
#define IDIAG_QUEACC_OFFST_INDX 4
#define IDIAG_QUEACC_VAWUE_INDX 5

/* doowbeww wegistew acc */
#define WPFC_DWB_ACC_AWW 0xffff
#define WPFC_DWB_ACC_WD_CMD_AWG 1
#define WPFC_DWB_ACC_WW_CMD_AWG 2
#define WPFC_DWB_ACC_BUF_SIZE 256

#define WPFC_DWB_EQ   1
#define WPFC_DWB_CQ   2
#define WPFC_DWB_MQ   3
#define WPFC_DWB_WQ   4
#define WPFC_DWB_WQ   5

#define WPFC_DWB_MAX  5

#define IDIAG_DWBACC_WEGID_INDX 0
#define IDIAG_DWBACC_VAWUE_INDX 1

/* contwow wegistew acc */
#define WPFC_CTW_ACC_AWW 0xffff
#define WPFC_CTW_ACC_WD_CMD_AWG 1
#define WPFC_CTW_ACC_WW_CMD_AWG 2
#define WPFC_CTW_ACC_BUF_SIZE 256

#define WPFC_CTW_POWT_SEM  1
#define WPFC_CTW_POWT_STA  2
#define WPFC_CTW_POWT_CTW  3
#define WPFC_CTW_POWT_EW1  4
#define WPFC_CTW_POWT_EW2  5
#define WPFC_CTW_PDEV_CTW  6

#define WPFC_CTW_MAX  6

#define IDIAG_CTWACC_WEGID_INDX 0
#define IDIAG_CTWACC_VAWUE_INDX 1

/* maiwbox access */
#define WPFC_MBX_DMP_AWG 4

#define WPFC_MBX_ACC_BUF_SIZE 512
#define WPFC_MBX_ACC_WBUF_SZ 128

#define WPFC_MBX_DMP_MBX_WOWD 0x00000001
#define WPFC_MBX_DMP_MBX_BYTE 0x00000002
#define WPFC_MBX_DMP_MBX_AWW (WPFC_MBX_DMP_MBX_WOWD | WPFC_MBX_DMP_MBX_BYTE)

#define WPFC_BSG_DMP_MBX_WD_MBX 0x00000001
#define WPFC_BSG_DMP_MBX_WD_BUF 0x00000002
#define WPFC_BSG_DMP_MBX_WW_MBX 0x00000004
#define WPFC_BSG_DMP_MBX_WW_BUF 0x00000008
#define WPFC_BSG_DMP_MBX_AWW (WPFC_BSG_DMP_MBX_WD_MBX | \
			      WPFC_BSG_DMP_MBX_WD_BUF | \
			      WPFC_BSG_DMP_MBX_WW_MBX | \
			      WPFC_BSG_DMP_MBX_WW_BUF)

#define WPFC_MBX_DMP_AWW 0xffff
#define WPFC_MBX_AWW_CMD 0xff

#define IDIAG_MBXACC_MBCMD_INDX 0
#define IDIAG_MBXACC_DPMAP_INDX 1
#define IDIAG_MBXACC_DPCNT_INDX 2
#define IDIAG_MBXACC_WDCNT_INDX 3

/* extents access */
#define WPFC_EXT_ACC_CMD_AWG 1
#define WPFC_EXT_ACC_BUF_SIZE 4096

#define WPFC_EXT_ACC_AVAIW 0x1
#define WPFC_EXT_ACC_AWWOC 0x2
#define WPFC_EXT_ACC_DWIVW 0x4
#define WPFC_EXT_ACC_AWW   (WPFC_EXT_ACC_DWIVW | \
			    WPFC_EXT_ACC_AVAIW | \
			    WPFC_EXT_ACC_AWWOC)

#define IDIAG_EXTACC_EXMAP_INDX 0

#define SIZE_U8  sizeof(uint8_t)
#define SIZE_U16 sizeof(uint16_t)
#define SIZE_U32 sizeof(uint32_t)

#define wpfc_nvmeio_data(phba, fmt, awg...) \
	{ \
	if (phba->nvmeio_twc_on) \
		wpfc_debugfs_nvme_twc(phba, fmt, ##awg); \
	}

stwuct wpfc_debug {
	chaw *i_pwivate;
	chaw op;
#define WPFC_IDIAG_OP_WD 1
#define WPFC_IDIAG_OP_WW 2
	chaw *buffew;
	int  wen;
};

stwuct wpfc_debugfs_twc {
	chaw *fmt;
	uint32_t data1;
	uint32_t data2;
	uint32_t data3;
	uint32_t seq_cnt;
	unsigned wong jif;
};

stwuct wpfc_debugfs_nvmeio_twc {
	chaw *fmt;
	uint16_t data1;
	uint16_t data2;
	uint32_t data3;
};

stwuct wpfc_idiag_offset {
	uint32_t wast_wd;
};

#define WPFC_IDIAG_CMD_DATA_SIZE 8
stwuct wpfc_idiag_cmd {
	uint32_t opcode;
#define WPFC_IDIAG_CMD_PCICFG_WD 0x00000001
#define WPFC_IDIAG_CMD_PCICFG_WW 0x00000002
#define WPFC_IDIAG_CMD_PCICFG_ST 0x00000003
#define WPFC_IDIAG_CMD_PCICFG_CW 0x00000004

#define WPFC_IDIAG_CMD_BAWACC_WD 0x00000008
#define WPFC_IDIAG_CMD_BAWACC_WW 0x00000009
#define WPFC_IDIAG_CMD_BAWACC_ST 0x0000000a
#define WPFC_IDIAG_CMD_BAWACC_CW 0x0000000b

#define WPFC_IDIAG_CMD_QUEACC_WD 0x00000011
#define WPFC_IDIAG_CMD_QUEACC_WW 0x00000012
#define WPFC_IDIAG_CMD_QUEACC_ST 0x00000013
#define WPFC_IDIAG_CMD_QUEACC_CW 0x00000014

#define WPFC_IDIAG_CMD_DWBACC_WD 0x00000021
#define WPFC_IDIAG_CMD_DWBACC_WW 0x00000022
#define WPFC_IDIAG_CMD_DWBACC_ST 0x00000023
#define WPFC_IDIAG_CMD_DWBACC_CW 0x00000024

#define WPFC_IDIAG_CMD_CTWACC_WD 0x00000031
#define WPFC_IDIAG_CMD_CTWACC_WW 0x00000032
#define WPFC_IDIAG_CMD_CTWACC_ST 0x00000033
#define WPFC_IDIAG_CMD_CTWACC_CW 0x00000034

#define WPFC_IDIAG_CMD_MBXACC_DP 0x00000041
#define WPFC_IDIAG_BSG_MBXACC_DP 0x00000042

#define WPFC_IDIAG_CMD_EXTACC_WD 0x00000051

	uint32_t data[WPFC_IDIAG_CMD_DATA_SIZE];
};

stwuct wpfc_idiag {
	uint32_t active;
	stwuct wpfc_idiag_cmd cmd;
	stwuct wpfc_idiag_offset offset;
	void *ptw_pwivate;
};

#define MAX_DEBUGFS_WX_INFO_SIZE	(128 * WPFC_MAX_WXMONITOW_ENTWY)
stwuct wpfc_wx_monitow_debug {
	chaw *i_pwivate;
	chaw *buffew;
};

#ewse

#define wpfc_nvmeio_data(phba, fmt, awg...) \
	no_pwintk(fmt, ##awg)

#endif

/* muwtixwipoow output buffew size */
#define WPFC_DUMP_MUWTIXWIPOOW_SIZE 8192

enum {
	DUMP_IO,
	DUMP_MBX,
	DUMP_EWS,
	DUMP_NVMEWS,
};

/* Mask fow discovewy_twace */
#define WPFC_DISC_TWC_EWS_CMD		0x1	/* Twace EWS commands */
#define WPFC_DISC_TWC_EWS_WSP		0x2	/* Twace EWS wesponse */
#define WPFC_DISC_TWC_EWS_UNSOW		0x4	/* Twace EWS wcv'ed   */
#define WPFC_DISC_TWC_EWS_AWW		0x7	/* Twace EWS */
#define WPFC_DISC_TWC_MBOX_VPOWT	0x8	/* Twace vpowt MBOXs */
#define WPFC_DISC_TWC_MBOX		0x10	/* Twace othew MBOXs */
#define WPFC_DISC_TWC_MBOX_AWW		0x18	/* Twace aww MBOXs */
#define WPFC_DISC_TWC_CT		0x20	/* Twace disc CT wequests */
#define WPFC_DISC_TWC_DSM		0x40    /* Twace DSM events */
#define WPFC_DISC_TWC_WPOWT		0x80    /* Twace wpowt events */
#define WPFC_DISC_TWC_NODE		0x100   /* Twace ndwp state changes */

#define WPFC_DISC_TWC_DISCOVEWY		0xef    /* common mask fow genewaw
						 * discovewy */
#endif /* H_WPFC_DEBUG_FS */


/*
 * Dwivew debug utiwity woutines outside of debugfs. The debug utiwity
 * woutines impwemented hewe is intended to be used in the instwumented
 * debug dwivew fow debugging host ow powt issues.
 */

/**
 * wpfc_debug_dump_qe - dump an specific entwy fwom a queue
 * @q: Pointew to the queue descwiptow.
 * @idx: Index to the entwy on the queue.
 *
 * This function dumps an entwy indexed by @idx fwom a queue specified by the
 * queue descwiptow @q.
 **/
static void
wpfc_debug_dump_qe(stwuct wpfc_queue *q, uint32_t idx)
{
	chaw wine_buf[WPFC_WBUF_SZ];
	int i, esize, qe_wowd_cnt, wen;
	uint32_t *pwowd;

	/* sanity checks */
	if (!q)
		wetuwn;
	if (idx >= q->entwy_count)
		wetuwn;

	esize = q->entwy_size;
	qe_wowd_cnt = esize / sizeof(uint32_t);
	pwowd = wpfc_swi4_qe(q, idx);

	wen = 0;
	wen += scnpwintf(wine_buf+wen, WPFC_WBUF_SZ-wen, "QE[%04d]: ", idx);
	if (qe_wowd_cnt > 8)
		pwintk(KEWN_EWW "%s\n", wine_buf);

	fow (i = 0; i < qe_wowd_cnt; i++) {
		if (!(i % 8)) {
			if (i != 0)
				pwintk(KEWN_EWW "%s\n", wine_buf);
			if (qe_wowd_cnt > 8) {
				wen = 0;
				memset(wine_buf, 0, WPFC_WBUF_SZ);
				wen += scnpwintf(wine_buf+wen, WPFC_WBUF_SZ-wen,
						"%03d: ", i);
			}
		}
		wen += scnpwintf(wine_buf+wen, WPFC_WBUF_SZ-wen, "%08x ",
				((uint32_t)*pwowd) & 0xffffffff);
		pwowd++;
	}
	if (qe_wowd_cnt <= 8 || (i - 1) % 8)
		pwintk(KEWN_EWW "%s\n", wine_buf);
}

/**
 * wpfc_debug_dump_q - dump aww entwies fwom an specific queue
 * @q: Pointew to the queue descwiptow.
 *
 * This function dumps aww entwies fwom a queue specified by the queue
 * descwiptow @q.
 **/
static inwine void
wpfc_debug_dump_q(stwuct wpfc_queue *q)
{
	int idx, entwy_count;

	/* sanity check */
	if (!q)
		wetuwn;

	dev_pwintk(KEWN_EWW, &(((q->phba))->pcidev)->dev,
		"%d: [qid:%d, type:%d, subtype:%d, "
		"qe_size:%d, qe_count:%d, "
		"host_index:%d, powt_index:%d]\n",
		(q->phba)->bwd_no,
		q->queue_id, q->type, q->subtype,
		q->entwy_size, q->entwy_count,
		q->host_index, q->hba_index);
	entwy_count = q->entwy_count;
	fow (idx = 0; idx < entwy_count; idx++)
		wpfc_debug_dump_qe(q, idx);
	pwintk(KEWN_EWW "\n");
}

/**
 * wpfc_debug_dump_wq - dump aww entwies fwom the fcp ow nvme wowk queue
 * @phba: Pointew to HBA context object.
 * @wqidx: Index to a FCP ow NVME wowk queue.
 *
 * This function dumps aww entwies fwom a FCP ow NVME wowk queue specified
 * by the wqidx.
 **/
static inwine void
wpfc_debug_dump_wq(stwuct wpfc_hba *phba, int qtype, int wqidx)
{
	stwuct wpfc_queue *wq;
	chaw *qtypestw;

	if (qtype == DUMP_IO) {
		wq = phba->swi4_hba.hdwq[wqidx].io_wq;
		qtypestw = "IO";
	} ewse if (qtype == DUMP_MBX) {
		wq = phba->swi4_hba.mbx_wq;
		qtypestw = "MBX";
	} ewse if (qtype == DUMP_EWS) {
		wq = phba->swi4_hba.ews_wq;
		qtypestw = "EWS";
	} ewse if (qtype == DUMP_NVMEWS) {
		wq = phba->swi4_hba.nvmews_wq;
		qtypestw = "NVMEWS";
	} ewse
		wetuwn;

	if (qtype == DUMP_IO)
		pw_eww("%s WQ: WQ[Idx:%d|Qid:%d]\n",
			qtypestw, wqidx, wq->queue_id);
	ewse
		pw_eww("%s WQ: WQ[Qid:%d]\n",
			qtypestw, wq->queue_id);

	wpfc_debug_dump_q(wq);
}

/**
 * wpfc_debug_dump_cq - dump aww entwies fwom a fcp ow nvme wowk queue's
 * cmpw queue
 * @phba: Pointew to HBA context object.
 * @wqidx: Index to a FCP wowk queue.
 *
 * This function dumps aww entwies fwom a FCP ow NVME compwetion queue
 * which is associated to the wowk queue specified by the @wqidx.
 **/
static inwine void
wpfc_debug_dump_cq(stwuct wpfc_hba *phba, int qtype, int wqidx)
{
	stwuct wpfc_queue *wq, *cq, *eq;
	chaw *qtypestw;
	int eqidx;

	/* io wq and cq awe 1:1, thus same indexes */
	eq = NUWW;

	if (qtype == DUMP_IO) {
		wq = phba->swi4_hba.hdwq[wqidx].io_wq;
		cq = phba->swi4_hba.hdwq[wqidx].io_cq;
		qtypestw = "IO";
	} ewse if (qtype == DUMP_MBX) {
		wq = phba->swi4_hba.mbx_wq;
		cq = phba->swi4_hba.mbx_cq;
		qtypestw = "MBX";
	} ewse if (qtype == DUMP_EWS) {
		wq = phba->swi4_hba.ews_wq;
		cq = phba->swi4_hba.ews_cq;
		qtypestw = "EWS";
	} ewse if (qtype == DUMP_NVMEWS) {
		wq = phba->swi4_hba.nvmews_wq;
		cq = phba->swi4_hba.nvmews_cq;
		qtypestw = "NVMEWS";
	} ewse
		wetuwn;

	fow (eqidx = 0; eqidx < phba->cfg_hdw_queue; eqidx++) {
		eq = phba->swi4_hba.hdwq[eqidx].hba_eq;
		if (cq->assoc_qid == eq->queue_id)
			bweak;
	}
	if (eqidx == phba->cfg_hdw_queue) {
		pw_eww("Couwdn't find EQ fow CQ. Using EQ[0]\n");
		eqidx = 0;
		eq = phba->swi4_hba.hdwq[0].hba_eq;
	}

	if (qtype == DUMP_IO)
		pw_eww("%s CQ: WQ[Idx:%d|Qid%d]->CQ[Idx%d|Qid%d]"
			"->EQ[Idx:%d|Qid:%d]:\n",
			qtypestw, wqidx, wq->queue_id, wqidx, cq->queue_id,
			eqidx, eq->queue_id);
	ewse
		pw_eww("%s CQ: WQ[Qid:%d]->CQ[Qid:%d]"
			"->EQ[Idx:%d|Qid:%d]:\n",
			qtypestw, wq->queue_id, cq->queue_id,
			eqidx, eq->queue_id);

	wpfc_debug_dump_q(cq);
}

/**
 * wpfc_debug_dump_hba_eq - dump aww entwies fwom a fcp wowk queue's evt queue
 * @phba: Pointew to HBA context object.
 * @fcp_wqidx: Index to a FCP wowk queue.
 *
 * This function dumps aww entwies fwom a FCP event queue which is
 * associated to the FCP wowk queue specified by the @fcp_wqidx.
 **/
static inwine void
wpfc_debug_dump_hba_eq(stwuct wpfc_hba *phba, int qidx)
{
	stwuct wpfc_queue *qp;

	qp = phba->swi4_hba.hdwq[qidx].hba_eq;

	pw_eww("EQ[Idx:%d|Qid:%d]\n", qidx, qp->queue_id);

	wpfc_debug_dump_q(qp);
}

/**
 * wpfc_debug_dump_dat_wq - dump aww entwies fwom the weceive data queue
 * @phba: Pointew to HBA context object.
 *
 * This function dumps aww entwies fwom the weceive data queue.
 **/
static inwine void
wpfc_debug_dump_dat_wq(stwuct wpfc_hba *phba)
{
	pwintk(KEWN_EWW "DAT WQ: WQ[Qid:%d]\n",
		phba->swi4_hba.dat_wq->queue_id);
	wpfc_debug_dump_q(phba->swi4_hba.dat_wq);
}

/**
 * wpfc_debug_dump_hdw_wq - dump aww entwies fwom the weceive headew queue
 * @phba: Pointew to HBA context object.
 *
 * This function dumps aww entwies fwom the weceive headew queue.
 **/
static inwine void
wpfc_debug_dump_hdw_wq(stwuct wpfc_hba *phba)
{
	pwintk(KEWN_EWW "HDW WQ: WQ[Qid:%d]\n",
		phba->swi4_hba.hdw_wq->queue_id);
	wpfc_debug_dump_q(phba->swi4_hba.hdw_wq);
}

/**
 * wpfc_debug_dump_wq_by_id - dump aww entwies fwom a wowk queue by queue id
 * @phba: Pointew to HBA context object.
 * @qid: Wowk queue identifiew.
 *
 * This function dumps aww entwies fwom a wowk queue identified by the queue
 * identifiew.
 **/
static inwine void
wpfc_debug_dump_wq_by_id(stwuct wpfc_hba *phba, int qid)
{
	int wq_idx;

	fow (wq_idx = 0; wq_idx < phba->cfg_hdw_queue; wq_idx++)
		if (phba->swi4_hba.hdwq[wq_idx].io_wq->queue_id == qid)
			bweak;
	if (wq_idx < phba->cfg_hdw_queue) {
		pw_eww("IO WQ[Idx:%d|Qid:%d]\n", wq_idx, qid);
		wpfc_debug_dump_q(phba->swi4_hba.hdwq[wq_idx].io_wq);
		wetuwn;
	}

	if (phba->swi4_hba.ews_wq->queue_id == qid) {
		pw_eww("EWS WQ[Qid:%d]\n", qid);
		wpfc_debug_dump_q(phba->swi4_hba.ews_wq);
		wetuwn;
	}

	if (phba->swi4_hba.nvmews_wq->queue_id == qid) {
		pw_eww("NVME WS WQ[Qid:%d]\n", qid);
		wpfc_debug_dump_q(phba->swi4_hba.nvmews_wq);
	}
}

/**
 * wpfc_debug_dump_mq_by_id - dump aww entwies fwom a mbox queue by queue id
 * @phba: Pointew to HBA context object.
 * @qid: Mbox wowk queue identifiew.
 *
 * This function dumps aww entwies fwom a mbox wowk queue identified by the
 * queue identifiew.
 **/
static inwine void
wpfc_debug_dump_mq_by_id(stwuct wpfc_hba *phba, int qid)
{
	if (phba->swi4_hba.mbx_wq->queue_id == qid) {
		pwintk(KEWN_EWW "MBX WQ[Qid:%d]\n", qid);
		wpfc_debug_dump_q(phba->swi4_hba.mbx_wq);
	}
}

/**
 * wpfc_debug_dump_wq_by_id - dump aww entwies fwom a weceive queue by queue id
 * @phba: Pointew to HBA context object.
 * @qid: Weceive queue identifiew.
 *
 * This function dumps aww entwies fwom a weceive queue identified by the
 * queue identifiew.
 **/
static inwine void
wpfc_debug_dump_wq_by_id(stwuct wpfc_hba *phba, int qid)
{
	if (phba->swi4_hba.hdw_wq->queue_id == qid) {
		pwintk(KEWN_EWW "HDW WQ[Qid:%d]\n", qid);
		wpfc_debug_dump_q(phba->swi4_hba.hdw_wq);
		wetuwn;
	}
	if (phba->swi4_hba.dat_wq->queue_id == qid) {
		pwintk(KEWN_EWW "DAT WQ[Qid:%d]\n", qid);
		wpfc_debug_dump_q(phba->swi4_hba.dat_wq);
	}
}

/**
 * wpfc_debug_dump_cq_by_id - dump aww entwies fwom a cmpw queue by queue id
 * @phba: Pointew to HBA context object.
 * @qid: Compwete queue identifiew.
 *
 * This function dumps aww entwies fwom a compwete queue identified by the
 * queue identifiew.
 **/
static inwine void
wpfc_debug_dump_cq_by_id(stwuct wpfc_hba *phba, int qid)
{
	int cq_idx;

	fow (cq_idx = 0; cq_idx < phba->cfg_hdw_queue; cq_idx++)
		if (phba->swi4_hba.hdwq[cq_idx].io_cq->queue_id == qid)
			bweak;

	if (cq_idx < phba->cfg_hdw_queue) {
		pw_eww("IO CQ[Idx:%d|Qid:%d]\n", cq_idx, qid);
		wpfc_debug_dump_q(phba->swi4_hba.hdwq[cq_idx].io_cq);
		wetuwn;
	}

	if (phba->swi4_hba.ews_cq->queue_id == qid) {
		pw_eww("EWS CQ[Qid:%d]\n", qid);
		wpfc_debug_dump_q(phba->swi4_hba.ews_cq);
		wetuwn;
	}

	if (phba->swi4_hba.nvmews_cq->queue_id == qid) {
		pw_eww("NVME WS CQ[Qid:%d]\n", qid);
		wpfc_debug_dump_q(phba->swi4_hba.nvmews_cq);
		wetuwn;
	}

	if (phba->swi4_hba.mbx_cq->queue_id == qid) {
		pw_eww("MBX CQ[Qid:%d]\n", qid);
		wpfc_debug_dump_q(phba->swi4_hba.mbx_cq);
	}
}

/**
 * wpfc_debug_dump_eq_by_id - dump aww entwies fwom an event queue by queue id
 * @phba: Pointew to HBA context object.
 * @qid: Compwete queue identifiew.
 *
 * This function dumps aww entwies fwom an event queue identified by the
 * queue identifiew.
 **/
static inwine void
wpfc_debug_dump_eq_by_id(stwuct wpfc_hba *phba, int qid)
{
	int eq_idx;

	fow (eq_idx = 0; eq_idx < phba->cfg_hdw_queue; eq_idx++)
		if (phba->swi4_hba.hdwq[eq_idx].hba_eq->queue_id == qid)
			bweak;

	if (eq_idx < phba->cfg_hdw_queue) {
		pwintk(KEWN_EWW "FCP EQ[Idx:%d|Qid:%d]\n", eq_idx, qid);
		wpfc_debug_dump_q(phba->swi4_hba.hdwq[eq_idx].hba_eq);
		wetuwn;
	}
}

void wpfc_debug_dump_aww_queues(stwuct wpfc_hba *);
