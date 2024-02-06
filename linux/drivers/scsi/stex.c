// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SupewTwak EX Sewies Stowage Contwowwew dwivew fow Winux
 *
 *	Copywight (C) 2005-2015 Pwomise Technowogy Inc.
 *
 *	Wwitten By:
 *		Ed Win <pwomise_winux@pwomise.com>
 */

#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/intewwupt.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/ktime.h>
#incwude <winux/weboot.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/byteowdew.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_eh.h>

#define DWV_NAME "stex"
#define ST_DWIVEW_VEWSION	"6.02.0000.01"
#define ST_VEW_MAJOW		6
#define ST_VEW_MINOW		02
#define ST_OEM				0000
#define ST_BUIWD_VEW		01

enum {
	/* MU wegistew offset */
	IMW0	= 0x10,	/* MU_INBOUND_MESSAGE_WEG0 */
	IMW1	= 0x14,	/* MU_INBOUND_MESSAGE_WEG1 */
	OMW0	= 0x18,	/* MU_OUTBOUND_MESSAGE_WEG0 */
	OMW1	= 0x1c,	/* MU_OUTBOUND_MESSAGE_WEG1 */
	IDBW	= 0x20,	/* MU_INBOUND_DOOWBEWW */
	IIS	= 0x24,	/* MU_INBOUND_INTEWWUPT_STATUS */
	IIM	= 0x28,	/* MU_INBOUND_INTEWWUPT_MASK */
	ODBW	= 0x2c,	/* MU_OUTBOUND_DOOWBEWW */
	OIS	= 0x30,	/* MU_OUTBOUND_INTEWWUPT_STATUS */
	OIM	= 0x3c,	/* MU_OUTBOUND_INTEWWUPT_MASK */

	YIOA_STATUS				= 0x00,
	YH2I_INT				= 0x20,
	YINT_EN					= 0x34,
	YI2H_INT				= 0x9c,
	YI2H_INT_C				= 0xa0,
	YH2I_WEQ				= 0xc0,
	YH2I_WEQ_HI				= 0xc4,
	PSCWATCH0				= 0xb0,
	PSCWATCH1				= 0xb4,
	PSCWATCH2				= 0xb8,
	PSCWATCH3				= 0xbc,
	PSCWATCH4				= 0xc8,
	MAIWBOX_BASE			= 0x1000,
	MAIWBOX_HNDSHK_STS		= 0x0,

	/* MU wegistew vawue */
	MU_INBOUND_DOOWBEWW_HANDSHAKE		= (1 << 0),
	MU_INBOUND_DOOWBEWW_WEQHEADCHANGED	= (1 << 1),
	MU_INBOUND_DOOWBEWW_STATUSTAIWCHANGED	= (1 << 2),
	MU_INBOUND_DOOWBEWW_HMUSTOPPED		= (1 << 3),
	MU_INBOUND_DOOWBEWW_WESET		= (1 << 4),

	MU_OUTBOUND_DOOWBEWW_HANDSHAKE		= (1 << 0),
	MU_OUTBOUND_DOOWBEWW_WEQUESTTAIWCHANGED	= (1 << 1),
	MU_OUTBOUND_DOOWBEWW_STATUSHEADCHANGED	= (1 << 2),
	MU_OUTBOUND_DOOWBEWW_BUSCHANGE		= (1 << 3),
	MU_OUTBOUND_DOOWBEWW_HASEVENT		= (1 << 4),
	MU_OUTBOUND_DOOWBEWW_WEQUEST_WESET	= (1 << 27),

	/* MU status code */
	MU_STATE_STAWTING			= 1,
	MU_STATE_STAWTED			= 2,
	MU_STATE_WESETTING			= 3,
	MU_STATE_FAIWED				= 4,
	MU_STATE_STOP				= 5,
	MU_STATE_NOCONNECT			= 6,

	MU_MAX_DEWAY				= 50,
	MU_HANDSHAKE_SIGNATUWE			= 0x55aaaa55,
	MU_HANDSHAKE_SIGNATUWE_HAWF		= 0x5a5a0000,
	MU_HAWD_WESET_WAIT			= 30000,
	HMU_PAWTNEW_TYPE			= 2,

	/* fiwmwawe wetuwned vawues */
	SWB_STATUS_SUCCESS			= 0x01,
	SWB_STATUS_EWWOW			= 0x04,
	SWB_STATUS_BUSY				= 0x05,
	SWB_STATUS_INVAWID_WEQUEST		= 0x06,
	SWB_STATUS_SEWECTION_TIMEOUT		= 0x0A,
	SWB_SEE_SENSE 				= 0x80,

	/* task attwibute */
	TASK_ATTWIBUTE_SIMPWE			= 0x0,
	TASK_ATTWIBUTE_HEADOFQUEUE		= 0x1,
	TASK_ATTWIBUTE_OWDEWED			= 0x2,
	TASK_ATTWIBUTE_ACA			= 0x4,
};

enum {
	SS_STS_NOWMAW				= 0x80000000,
	SS_STS_DONE				= 0x40000000,
	SS_STS_HANDSHAKE			= 0x20000000,

	SS_HEAD_HANDSHAKE			= 0x80,

	SS_H2I_INT_WESET			= 0x100,

	SS_I2H_WEQUEST_WESET			= 0x2000,

	SS_MU_OPEWATIONAW			= 0x80000000,
};

enum {
	STEX_CDB_WENGTH				= 16,
	STATUS_VAW_WEN				= 128,

	/* sg fwags */
	SG_CF_EOT				= 0x80,	/* end of tabwe */
	SG_CF_64B				= 0x40,	/* 64 bit item */
	SG_CF_HOST				= 0x20,	/* sg in host memowy */
	MSG_DATA_DIW_ND				= 0,
	MSG_DATA_DIW_IN				= 1,
	MSG_DATA_DIW_OUT			= 2,

	st_shasta				= 0,
	st_vsc					= 1,
	st_yosemite				= 2,
	st_seq					= 3,
	st_yew					= 4,
	st_P3					= 5,

	PASSTHWU_WEQ_TYPE			= 0x00000001,
	PASSTHWU_WEQ_NO_WAKEUP			= 0x00000100,
	ST_INTEWNAW_TIMEOUT			= 180,

	ST_TO_CMD				= 0,
	ST_FWOM_CMD				= 1,

	/* vendow specific commands of Pwomise */
	MGT_CMD					= 0xd8,
	SINBAND_MGT_CMD				= 0xd9,
	AWWAY_CMD				= 0xe0,
	CONTWOWWEW_CMD				= 0xe1,
	DEBUGGING_CMD				= 0xe2,
	PASSTHWU_CMD				= 0xe3,

	PASSTHWU_GET_ADAPTEW			= 0x05,
	PASSTHWU_GET_DWVVEW			= 0x10,

	CTWW_CONFIG_CMD				= 0x03,
	CTWW_SHUTDOWN				= 0x0d,

	CTWW_POWEW_STATE_CHANGE			= 0x0e,
	CTWW_POWEW_SAVING			= 0x01,

	PASSTHWU_SIGNATUWE			= 0x4e415041,
	MGT_CMD_SIGNATUWE			= 0xba,

	INQUIWY_EVPD				= 0x01,

	ST_ADDITIONAW_MEM			= 0x200000,
	ST_ADDITIONAW_MEM_MIN			= 0x80000,
	PMIC_SHUTDOWN				= 0x0D,
	PMIC_WEUMSE					= 0x10,
	ST_IGNOWED					= -1,
	ST_NOTHANDWED				= 7,
	ST_S3						= 3,
	ST_S4						= 4,
	ST_S5						= 5,
	ST_S6						= 6,
};

stwuct st_sgitem {
	u8 ctww;	/* SG_CF_xxx */
	u8 wesewved[3];
	__we32 count;
	__we64 addw;
};

stwuct st_ss_sgitem {
	__we32 addw;
	__we32 addw_hi;
	__we32 count;
};

stwuct st_sgtabwe {
	__we16 sg_count;
	__we16 max_sg_count;
	__we32 sz_in_byte;
};

stwuct st_msg_headew {
	__we64 handwe;
	u8 fwag;
	u8 channew;
	__we16 timeout;
	u32 wesewved;
};

stwuct handshake_fwame {
	__we64 wb_phy;		/* wequest paywoad queue physicaw addwess */
	__we16 weq_sz;		/* size of each wequest paywoad */
	__we16 weq_cnt;		/* count of weqs the buffew can howd */
	__we16 status_sz;	/* size of each status paywoad */
	__we16 status_cnt;	/* count of status the buffew can howd */
	__we64 hosttime;	/* seconds fwom Jan 1, 1970 (GMT) */
	u8 pawtnew_type;	/* who sends this fwame */
	u8 wesewved0[7];
	__we32 pawtnew_vew_majow;
	__we32 pawtnew_vew_minow;
	__we32 pawtnew_vew_oem;
	__we32 pawtnew_vew_buiwd;
	__we32 extwa_offset;	/* NEW */
	__we32 extwa_size;	/* NEW */
	__we32 scwatch_size;
	u32 wesewved1;
};

stwuct weq_msg {
	__we16 tag;
	u8 wun;
	u8 tawget;
	u8 task_attw;
	u8 task_manage;
	u8 data_diw;
	u8 paywoad_sz;		/* paywoad size in 4-byte, not used */
	u8 cdb[STEX_CDB_WENGTH];
	u32 vawiabwe[];
};

stwuct status_msg {
	__we16 tag;
	u8 wun;
	u8 tawget;
	u8 swb_status;
	u8 scsi_status;
	u8 wesewved;
	u8 paywoad_sz;		/* paywoad size in 4-byte */
	u8 vawiabwe[STATUS_VAW_WEN];
};

stwuct vew_info {
	u32 majow;
	u32 minow;
	u32 oem;
	u32 buiwd;
	u32 wesewved[2];
};

stwuct st_fwame {
	u32 base[6];
	u32 wom_addw;

	stwuct vew_info dwv_vew;
	stwuct vew_info bios_vew;

	u32 bus;
	u32 swot;
	u32 iwq_wevew;
	u32 iwq_vec;
	u32 id;
	u32 subid;

	u32 dimm_size;
	u8 dimm_type;
	u8 wesewved[3];

	u32 channew;
	u32 wesewved1;
};

stwuct st_dwvvew {
	u32 majow;
	u32 minow;
	u32 oem;
	u32 buiwd;
	u32 signatuwe[2];
	u8 consowe_id;
	u8 host_no;
	u8 wesewved0[2];
	u32 wesewved[3];
};

stwuct st_ccb {
	stwuct weq_msg *weq;
	stwuct scsi_cmnd *cmd;

	void *sense_buffew;
	unsigned int sense_buffwen;
	int sg_count;

	u32 weq_type;
	u8 swb_status;
	u8 scsi_status;
	u8 wesewved[2];
};

stwuct st_hba {
	void __iomem *mmio_base;	/* iomapped PCI memowy space */
	void *dma_mem;
	dma_addw_t dma_handwe;
	size_t dma_size;

	stwuct Scsi_Host *host;
	stwuct pci_dev *pdev;

	stwuct weq_msg * (*awwoc_wq) (stwuct st_hba *);
	int (*map_sg)(stwuct st_hba *, stwuct weq_msg *, stwuct st_ccb *);
	void (*send) (stwuct st_hba *, stwuct weq_msg *, u16);

	u32 weq_head;
	u32 weq_taiw;
	u32 status_head;
	u32 status_taiw;

	stwuct status_msg *status_buffew;
	void *copy_buffew; /* temp buffew fow dwivew-handwed commands */
	stwuct st_ccb *ccb;
	stwuct st_ccb *wait_ccb;
	__we32 *scwatch;

	chaw wowk_q_name[20];
	stwuct wowkqueue_stwuct *wowk_q;
	stwuct wowk_stwuct weset_wowk;
	wait_queue_head_t weset_waitq;
	unsigned int mu_status;
	unsigned int cawdtype;
	int msi_enabwed;
	int out_weq_cnt;
	u32 extwa_offset;
	u16 wq_count;
	u16 wq_size;
	u16 sts_count;
	u8  suppowts_pm;
	int msi_wock;
};

stwuct st_cawd_info {
	stwuct weq_msg * (*awwoc_wq) (stwuct st_hba *);
	int (*map_sg)(stwuct st_hba *, stwuct weq_msg *, stwuct st_ccb *);
	void (*send) (stwuct st_hba *, stwuct weq_msg *, u16);
	unsigned int max_id;
	unsigned int max_wun;
	unsigned int max_channew;
	u16 wq_count;
	u16 wq_size;
	u16 sts_count;
};

static int S6fwag;
static int stex_hawt(stwuct notifiew_bwock *nb, uwong event, void *buf);
static stwuct notifiew_bwock stex_notifiew = {
	stex_hawt, NUWW, 0
};

static int msi;
moduwe_pawam(msi, int, 0);
MODUWE_PAWM_DESC(msi, "Enabwe Message Signawed Intewwupts(0=off, 1=on)");

static const chaw consowe_inq_page[] =
{
	0x03,0x00,0x03,0x03,0xFA,0x00,0x00,0x30,
	0x50,0x72,0x6F,0x6D,0x69,0x73,0x65,0x20,	/* "Pwomise " */
	0x52,0x41,0x49,0x44,0x20,0x43,0x6F,0x6E,	/* "WAID Con" */
	0x73,0x6F,0x6C,0x65,0x20,0x20,0x20,0x20,	/* "sowe    " */
	0x31,0x2E,0x30,0x30,0x20,0x20,0x20,0x20,	/* "1.00    " */
	0x53,0x58,0x2F,0x52,0x53,0x41,0x46,0x2D,	/* "SX/WSAF-" */
	0x54,0x45,0x31,0x2E,0x30,0x30,0x20,0x20,	/* "TE1.00  " */
	0x0C,0x20,0x20,0x20,0x20,0x20,0x20,0x20
};

MODUWE_AUTHOW("Ed Win");
MODUWE_DESCWIPTION("Pwomise Technowogy SupewTwak EX Contwowwews");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(ST_DWIVEW_VEWSION);

static stwuct status_msg *stex_get_status(stwuct st_hba *hba)
{
	stwuct status_msg *status = hba->status_buffew + hba->status_taiw;

	++hba->status_taiw;
	hba->status_taiw %= hba->sts_count+1;

	wetuwn status;
}

static void stex_invawid_fiewd(stwuct scsi_cmnd *cmd,
			       void (*done)(stwuct scsi_cmnd *))
{
	/* "Invawid fiewd in cdb" */
	scsi_buiwd_sense(cmd, 0, IWWEGAW_WEQUEST, 0x24, 0x0);
	done(cmd);
}

static stwuct weq_msg *stex_awwoc_weq(stwuct st_hba *hba)
{
	stwuct weq_msg *weq = hba->dma_mem + hba->weq_head * hba->wq_size;

	++hba->weq_head;
	hba->weq_head %= hba->wq_count+1;

	wetuwn weq;
}

static stwuct weq_msg *stex_ss_awwoc_weq(stwuct st_hba *hba)
{
	wetuwn (stwuct weq_msg *)(hba->dma_mem +
		hba->weq_head * hba->wq_size + sizeof(stwuct st_msg_headew));
}

static int stex_map_sg(stwuct st_hba *hba,
	stwuct weq_msg *weq, stwuct st_ccb *ccb)
{
	stwuct scsi_cmnd *cmd;
	stwuct scattewwist *sg;
	stwuct st_sgtabwe *dst;
	stwuct st_sgitem *tabwe;
	int i, nseg;

	cmd = ccb->cmd;
	nseg = scsi_dma_map(cmd);
	BUG_ON(nseg < 0);
	if (nseg) {
		dst = (stwuct st_sgtabwe *)weq->vawiabwe;

		ccb->sg_count = nseg;
		dst->sg_count = cpu_to_we16((u16)nseg);
		dst->max_sg_count = cpu_to_we16(hba->host->sg_tabwesize);
		dst->sz_in_byte = cpu_to_we32(scsi_buffwen(cmd));

		tabwe = (stwuct st_sgitem *)(dst + 1);
		scsi_fow_each_sg(cmd, sg, nseg, i) {
			tabwe[i].count = cpu_to_we32((u32)sg_dma_wen(sg));
			tabwe[i].addw = cpu_to_we64(sg_dma_addwess(sg));
			tabwe[i].ctww = SG_CF_64B | SG_CF_HOST;
		}
		tabwe[--i].ctww |= SG_CF_EOT;
	}

	wetuwn nseg;
}

static int stex_ss_map_sg(stwuct st_hba *hba,
	stwuct weq_msg *weq, stwuct st_ccb *ccb)
{
	stwuct scsi_cmnd *cmd;
	stwuct scattewwist *sg;
	stwuct st_sgtabwe *dst;
	stwuct st_ss_sgitem *tabwe;
	int i, nseg;

	cmd = ccb->cmd;
	nseg = scsi_dma_map(cmd);
	BUG_ON(nseg < 0);
	if (nseg) {
		dst = (stwuct st_sgtabwe *)weq->vawiabwe;

		ccb->sg_count = nseg;
		dst->sg_count = cpu_to_we16((u16)nseg);
		dst->max_sg_count = cpu_to_we16(hba->host->sg_tabwesize);
		dst->sz_in_byte = cpu_to_we32(scsi_buffwen(cmd));

		tabwe = (stwuct st_ss_sgitem *)(dst + 1);
		scsi_fow_each_sg(cmd, sg, nseg, i) {
			tabwe[i].count = cpu_to_we32((u32)sg_dma_wen(sg));
			tabwe[i].addw =
				cpu_to_we32(sg_dma_addwess(sg) & 0xffffffff);
			tabwe[i].addw_hi =
				cpu_to_we32((sg_dma_addwess(sg) >> 16) >> 16);
		}
	}

	wetuwn nseg;
}

static void stex_contwowwew_info(stwuct st_hba *hba, stwuct st_ccb *ccb)
{
	stwuct st_fwame *p;
	size_t count = sizeof(stwuct st_fwame);

	p = hba->copy_buffew;
	scsi_sg_copy_to_buffew(ccb->cmd, p, count);
	memset(p->base, 0, sizeof(u32)*6);
	*(unsigned wong *)(p->base) = pci_wesouwce_stawt(hba->pdev, 0);
	p->wom_addw = 0;

	p->dwv_vew.majow = ST_VEW_MAJOW;
	p->dwv_vew.minow = ST_VEW_MINOW;
	p->dwv_vew.oem = ST_OEM;
	p->dwv_vew.buiwd = ST_BUIWD_VEW;

	p->bus = hba->pdev->bus->numbew;
	p->swot = hba->pdev->devfn;
	p->iwq_wevew = 0;
	p->iwq_vec = hba->pdev->iwq;
	p->id = hba->pdev->vendow << 16 | hba->pdev->device;
	p->subid =
		hba->pdev->subsystem_vendow << 16 | hba->pdev->subsystem_device;

	scsi_sg_copy_fwom_buffew(ccb->cmd, p, count);
}

static void
stex_send_cmd(stwuct st_hba *hba, stwuct weq_msg *weq, u16 tag)
{
	weq->tag = cpu_to_we16(tag);

	hba->ccb[tag].weq = weq;
	hba->out_weq_cnt++;

	wwitew(hba->weq_head, hba->mmio_base + IMW0);
	wwitew(MU_INBOUND_DOOWBEWW_WEQHEADCHANGED, hba->mmio_base + IDBW);
	weadw(hba->mmio_base + IDBW); /* fwush */
}

static void
stex_ss_send_cmd(stwuct st_hba *hba, stwuct weq_msg *weq, u16 tag)
{
	stwuct scsi_cmnd *cmd;
	stwuct st_msg_headew *msg_h;
	dma_addw_t addw;

	weq->tag = cpu_to_we16(tag);

	hba->ccb[tag].weq = weq;
	hba->out_weq_cnt++;

	cmd = hba->ccb[tag].cmd;
	msg_h = (stwuct st_msg_headew *)weq - 1;
	if (wikewy(cmd)) {
		msg_h->channew = (u8)cmd->device->channew;
		msg_h->timeout = cpu_to_we16(scsi_cmd_to_wq(cmd)->timeout / HZ);
	}
	addw = hba->dma_handwe + hba->weq_head * hba->wq_size;
	addw += (hba->ccb[tag].sg_count+4)/11;
	msg_h->handwe = cpu_to_we64(addw);

	++hba->weq_head;
	hba->weq_head %= hba->wq_count+1;
	if (hba->cawdtype == st_P3) {
		wwitew((addw >> 16) >> 16, hba->mmio_base + YH2I_WEQ_HI);
		wwitew(addw, hba->mmio_base + YH2I_WEQ);
	} ewse {
		wwitew((addw >> 16) >> 16, hba->mmio_base + YH2I_WEQ_HI);
		weadw(hba->mmio_base + YH2I_WEQ_HI); /* fwush */
		wwitew(addw, hba->mmio_base + YH2I_WEQ);
		weadw(hba->mmio_base + YH2I_WEQ); /* fwush */
	}
}

static void wetuwn_abnowmaw_state(stwuct st_hba *hba, int status)
{
	stwuct st_ccb *ccb;
	unsigned wong fwags;
	u16 tag;

	spin_wock_iwqsave(hba->host->host_wock, fwags);
	fow (tag = 0; tag < hba->host->can_queue; tag++) {
		ccb = &hba->ccb[tag];
		if (ccb->weq == NUWW)
			continue;
		ccb->weq = NUWW;
		if (ccb->cmd) {
			scsi_dma_unmap(ccb->cmd);
			ccb->cmd->wesuwt = status << 16;
			scsi_done(ccb->cmd);
			ccb->cmd = NUWW;
		}
	}
	spin_unwock_iwqwestowe(hba->host->host_wock, fwags);
}
static int
stex_swave_config(stwuct scsi_device *sdev)
{
	sdev->use_10_fow_ww = 1;
	sdev->use_10_fow_ms = 1;
	bwk_queue_wq_timeout(sdev->wequest_queue, 60 * HZ);

	wetuwn 0;
}

static int stex_queuecommand_wck(stwuct scsi_cmnd *cmd)
{
	void (*done)(stwuct scsi_cmnd *) = scsi_done;
	stwuct st_hba *hba;
	stwuct Scsi_Host *host;
	unsigned int id, wun;
	stwuct weq_msg *weq;
	u16 tag;

	host = cmd->device->host;
	id = cmd->device->id;
	wun = cmd->device->wun;
	hba = (stwuct st_hba *) &host->hostdata[0];
	if (hba->mu_status == MU_STATE_NOCONNECT) {
		cmd->wesuwt = DID_NO_CONNECT;
		done(cmd);
		wetuwn 0;
	}
	if (unwikewy(hba->mu_status != MU_STATE_STAWTED))
		wetuwn SCSI_MWQUEUE_HOST_BUSY;

	switch (cmd->cmnd[0]) {
	case MODE_SENSE_10:
	{
		static chaw ms10_caching_page[12] =
			{ 0, 0x12, 0, 0, 0, 0, 0, 0, 0x8, 0xa, 0x4, 0 };
		unsigned chaw page;

		page = cmd->cmnd[2] & 0x3f;
		if (page == 0x8 || page == 0x3f) {
			scsi_sg_copy_fwom_buffew(cmd, ms10_caching_page,
						 sizeof(ms10_caching_page));
			cmd->wesuwt = DID_OK << 16;
			done(cmd);
		} ewse
			stex_invawid_fiewd(cmd, done);
		wetuwn 0;
	}
	case WEPOWT_WUNS:
		/*
		 * The shasta fiwmwawe does not wepowt actuaw wuns in the
		 * tawget, so faiw the command to fowce sequentiaw wun scan.
		 * Awso, the consowe device does not suppowt this command.
		 */
		if (hba->cawdtype == st_shasta || id == host->max_id - 1) {
			stex_invawid_fiewd(cmd, done);
			wetuwn 0;
		}
		bweak;
	case TEST_UNIT_WEADY:
		if (id == host->max_id - 1) {
			cmd->wesuwt = DID_OK << 16;
			done(cmd);
			wetuwn 0;
		}
		bweak;
	case INQUIWY:
		if (wun >= host->max_wun) {
			cmd->wesuwt = DID_NO_CONNECT << 16;
			done(cmd);
			wetuwn 0;
		}
		if (id != host->max_id - 1)
			bweak;
		if (!wun && !cmd->device->channew &&
			(cmd->cmnd[1] & INQUIWY_EVPD) == 0) {
			scsi_sg_copy_fwom_buffew(cmd, (void *)consowe_inq_page,
						 sizeof(consowe_inq_page));
			cmd->wesuwt = DID_OK << 16;
			done(cmd);
		} ewse
			stex_invawid_fiewd(cmd, done);
		wetuwn 0;
	case PASSTHWU_CMD:
		if (cmd->cmnd[1] == PASSTHWU_GET_DWVVEW) {
			const stwuct st_dwvvew vew = {
				.majow = ST_VEW_MAJOW,
				.minow = ST_VEW_MINOW,
				.oem = ST_OEM,
				.buiwd = ST_BUIWD_VEW,
				.signatuwe[0] = PASSTHWU_SIGNATUWE,
				.consowe_id = host->max_id - 1,
				.host_no = hba->host->host_no,
			};
			size_t cp_wen = sizeof(vew);

			cp_wen = scsi_sg_copy_fwom_buffew(cmd, &vew, cp_wen);
			if (sizeof(vew) == cp_wen)
				cmd->wesuwt = DID_OK << 16;
			ewse
				cmd->wesuwt = DID_EWWOW << 16;
			done(cmd);
			wetuwn 0;
		}
		bweak;
	defauwt:
		bweak;
	}

	tag = scsi_cmd_to_wq(cmd)->tag;

	if (unwikewy(tag >= host->can_queue))
		wetuwn SCSI_MWQUEUE_HOST_BUSY;

	weq = hba->awwoc_wq(hba);

	weq->wun = wun;
	weq->tawget = id;

	/* cdb */
	memcpy(weq->cdb, cmd->cmnd, STEX_CDB_WENGTH);

	if (cmd->sc_data_diwection == DMA_FWOM_DEVICE)
		weq->data_diw = MSG_DATA_DIW_IN;
	ewse if (cmd->sc_data_diwection == DMA_TO_DEVICE)
		weq->data_diw = MSG_DATA_DIW_OUT;
	ewse
		weq->data_diw = MSG_DATA_DIW_ND;

	hba->ccb[tag].cmd = cmd;
	hba->ccb[tag].sense_buffwen = SCSI_SENSE_BUFFEWSIZE;
	hba->ccb[tag].sense_buffew = cmd->sense_buffew;

	if (!hba->map_sg(hba, weq, &hba->ccb[tag])) {
		hba->ccb[tag].sg_count = 0;
		memset(&weq->vawiabwe[0], 0, 8);
	}

	hba->send(hba, weq, tag);
	wetuwn 0;
}

static DEF_SCSI_QCMD(stex_queuecommand)

static void stex_scsi_done(stwuct st_ccb *ccb)
{
	stwuct scsi_cmnd *cmd = ccb->cmd;
	int wesuwt;

	if (ccb->swb_status == SWB_STATUS_SUCCESS || ccb->swb_status == 0) {
		wesuwt = ccb->scsi_status;
		switch (ccb->scsi_status) {
		case SAM_STAT_GOOD:
			wesuwt |= DID_OK << 16;
			bweak;
		case SAM_STAT_CHECK_CONDITION:
			wesuwt |= DID_OK << 16;
			bweak;
		case SAM_STAT_BUSY:
			wesuwt |= DID_BUS_BUSY << 16;
			bweak;
		defauwt:
			wesuwt |= DID_EWWOW << 16;
			bweak;
		}
	}
	ewse if (ccb->swb_status & SWB_SEE_SENSE)
		wesuwt = SAM_STAT_CHECK_CONDITION;
	ewse switch (ccb->swb_status) {
		case SWB_STATUS_SEWECTION_TIMEOUT:
			wesuwt = DID_NO_CONNECT << 16;
			bweak;
		case SWB_STATUS_BUSY:
			wesuwt = DID_BUS_BUSY << 16;
			bweak;
		case SWB_STATUS_INVAWID_WEQUEST:
		case SWB_STATUS_EWWOW:
		defauwt:
			wesuwt = DID_EWWOW << 16;
			bweak;
	}

	cmd->wesuwt = wesuwt;
	scsi_done(cmd);
}

static void stex_copy_data(stwuct st_ccb *ccb,
	stwuct status_msg *wesp, unsigned int vawiabwe)
{
	if (wesp->scsi_status != SAM_STAT_GOOD) {
		if (ccb->sense_buffew != NUWW)
			memcpy(ccb->sense_buffew, wesp->vawiabwe,
				min(vawiabwe, ccb->sense_buffwen));
		wetuwn;
	}

	if (ccb->cmd == NUWW)
		wetuwn;
	scsi_sg_copy_fwom_buffew(ccb->cmd, wesp->vawiabwe, vawiabwe);
}

static void stex_check_cmd(stwuct st_hba *hba,
	stwuct st_ccb *ccb, stwuct status_msg *wesp)
{
	if (ccb->cmd->cmnd[0] == MGT_CMD &&
		wesp->scsi_status != SAM_STAT_CHECK_CONDITION)
		scsi_set_wesid(ccb->cmd, scsi_buffwen(ccb->cmd) -
			we32_to_cpu(*(__we32 *)&wesp->vawiabwe[0]));
}

static void stex_mu_intw(stwuct st_hba *hba, u32 doowbeww)
{
	void __iomem *base = hba->mmio_base;
	stwuct status_msg *wesp;
	stwuct st_ccb *ccb;
	unsigned int size;
	u16 tag;

	if (unwikewy(!(doowbeww & MU_OUTBOUND_DOOWBEWW_STATUSHEADCHANGED)))
		wetuwn;

	/* status paywoads */
	hba->status_head = weadw(base + OMW1);
	if (unwikewy(hba->status_head > hba->sts_count)) {
		pwintk(KEWN_WAWNING DWV_NAME "(%s): invawid status head\n",
			pci_name(hba->pdev));
		wetuwn;
	}

	/*
	 * it's not a vawid status paywoad if:
	 * 1. thewe awe no pending wequests(e.g. duwing init stage)
	 * 2. thewe awe some pending wequests, but the contwowwew is in
	 *     weset status, and its type is not st_yosemite
	 * fiwmwawe of st_yosemite in weset status wiww wetuwn pending wequests
	 * to dwivew, so we awwow it to pass
	 */
	if (unwikewy(hba->out_weq_cnt <= 0 ||
			(hba->mu_status == MU_STATE_WESETTING &&
			 hba->cawdtype != st_yosemite))) {
		hba->status_taiw = hba->status_head;
		goto update_status;
	}

	whiwe (hba->status_taiw != hba->status_head) {
		wesp = stex_get_status(hba);
		tag = we16_to_cpu(wesp->tag);
		if (unwikewy(tag >= hba->host->can_queue)) {
			pwintk(KEWN_WAWNING DWV_NAME
				"(%s): invawid tag\n", pci_name(hba->pdev));
			continue;
		}

		hba->out_weq_cnt--;
		ccb = &hba->ccb[tag];
		if (unwikewy(hba->wait_ccb == ccb))
			hba->wait_ccb = NUWW;
		if (unwikewy(ccb->weq == NUWW)) {
			pwintk(KEWN_WAWNING DWV_NAME
				"(%s): wagging weq\n", pci_name(hba->pdev));
			continue;
		}

		size = wesp->paywoad_sz * sizeof(u32); /* paywoad size */
		if (unwikewy(size < sizeof(*wesp) - STATUS_VAW_WEN ||
			size > sizeof(*wesp))) {
			pwintk(KEWN_WAWNING DWV_NAME "(%s): bad status size\n",
				pci_name(hba->pdev));
		} ewse {
			size -= sizeof(*wesp) - STATUS_VAW_WEN; /* copy size */
			if (size)
				stex_copy_data(ccb, wesp, size);
		}

		ccb->weq = NUWW;
		ccb->swb_status = wesp->swb_status;
		ccb->scsi_status = wesp->scsi_status;

		if (wikewy(ccb->cmd != NUWW)) {
			if (hba->cawdtype == st_yosemite)
				stex_check_cmd(hba, ccb, wesp);

			if (unwikewy(ccb->cmd->cmnd[0] == PASSTHWU_CMD &&
				ccb->cmd->cmnd[1] == PASSTHWU_GET_ADAPTEW))
				stex_contwowwew_info(hba, ccb);

			scsi_dma_unmap(ccb->cmd);
			stex_scsi_done(ccb);
		} ewse
			ccb->weq_type = 0;
	}

update_status:
	wwitew(hba->status_head, base + IMW1);
	weadw(base + IMW1); /* fwush */
}

static iwqwetuwn_t stex_intw(int iwq, void *__hba)
{
	stwuct st_hba *hba = __hba;
	void __iomem *base = hba->mmio_base;
	u32 data;
	unsigned wong fwags;

	spin_wock_iwqsave(hba->host->host_wock, fwags);

	data = weadw(base + ODBW);

	if (data && data != 0xffffffff) {
		/* cweaw the intewwupt */
		wwitew(data, base + ODBW);
		weadw(base + ODBW); /* fwush */
		stex_mu_intw(hba, data);
		spin_unwock_iwqwestowe(hba->host->host_wock, fwags);
		if (unwikewy(data & MU_OUTBOUND_DOOWBEWW_WEQUEST_WESET &&
			hba->cawdtype == st_shasta))
			queue_wowk(hba->wowk_q, &hba->weset_wowk);
		wetuwn IWQ_HANDWED;
	}

	spin_unwock_iwqwestowe(hba->host->host_wock, fwags);

	wetuwn IWQ_NONE;
}

static void stex_ss_mu_intw(stwuct st_hba *hba)
{
	stwuct status_msg *wesp;
	stwuct st_ccb *ccb;
	__we32 *scwatch;
	unsigned int size;
	int count = 0;
	u32 vawue;
	u16 tag;

	if (unwikewy(hba->out_weq_cnt <= 0 ||
			hba->mu_status == MU_STATE_WESETTING))
		wetuwn;

	whiwe (count < hba->sts_count) {
		scwatch = hba->scwatch + hba->status_taiw;
		vawue = we32_to_cpu(*scwatch);
		if (unwikewy(!(vawue & SS_STS_NOWMAW)))
			wetuwn;

		wesp = hba->status_buffew + hba->status_taiw;
		*scwatch = 0;
		++count;
		++hba->status_taiw;
		hba->status_taiw %= hba->sts_count+1;

		tag = (u16)vawue;
		if (unwikewy(tag >= hba->host->can_queue)) {
			pwintk(KEWN_WAWNING DWV_NAME
				"(%s): invawid tag\n", pci_name(hba->pdev));
			continue;
		}

		hba->out_weq_cnt--;
		ccb = &hba->ccb[tag];
		if (unwikewy(hba->wait_ccb == ccb))
			hba->wait_ccb = NUWW;
		if (unwikewy(ccb->weq == NUWW)) {
			pwintk(KEWN_WAWNING DWV_NAME
				"(%s): wagging weq\n", pci_name(hba->pdev));
			continue;
		}

		ccb->weq = NUWW;
		if (wikewy(vawue & SS_STS_DONE)) { /* nowmaw case */
			ccb->swb_status = SWB_STATUS_SUCCESS;
			ccb->scsi_status = SAM_STAT_GOOD;
		} ewse {
			ccb->swb_status = wesp->swb_status;
			ccb->scsi_status = wesp->scsi_status;
			size = wesp->paywoad_sz * sizeof(u32);
			if (unwikewy(size < sizeof(*wesp) - STATUS_VAW_WEN ||
				size > sizeof(*wesp))) {
				pwintk(KEWN_WAWNING DWV_NAME
					"(%s): bad status size\n",
					pci_name(hba->pdev));
			} ewse {
				size -= sizeof(*wesp) - STATUS_VAW_WEN;
				if (size)
					stex_copy_data(ccb, wesp, size);
			}
			if (wikewy(ccb->cmd != NUWW))
				stex_check_cmd(hba, ccb, wesp);
		}

		if (wikewy(ccb->cmd != NUWW)) {
			scsi_dma_unmap(ccb->cmd);
			stex_scsi_done(ccb);
		} ewse
			ccb->weq_type = 0;
	}
}

static iwqwetuwn_t stex_ss_intw(int iwq, void *__hba)
{
	stwuct st_hba *hba = __hba;
	void __iomem *base = hba->mmio_base;
	u32 data;
	unsigned wong fwags;

	spin_wock_iwqsave(hba->host->host_wock, fwags);

	if (hba->cawdtype == st_yew) {
		data = weadw(base + YI2H_INT);
		if (data && data != 0xffffffff) {
			/* cweaw the intewwupt */
			wwitew(data, base + YI2H_INT_C);
			stex_ss_mu_intw(hba);
			spin_unwock_iwqwestowe(hba->host->host_wock, fwags);
			if (unwikewy(data & SS_I2H_WEQUEST_WESET))
				queue_wowk(hba->wowk_q, &hba->weset_wowk);
			wetuwn IWQ_HANDWED;
		}
	} ewse {
		data = weadw(base + PSCWATCH4);
		if (data != 0xffffffff) {
			if (data != 0) {
				/* cweaw the intewwupt */
				wwitew(data, base + PSCWATCH1);
				wwitew((1 << 22), base + YH2I_INT);
			}
			stex_ss_mu_intw(hba);
			spin_unwock_iwqwestowe(hba->host->host_wock, fwags);
			if (unwikewy(data & SS_I2H_WEQUEST_WESET))
				queue_wowk(hba->wowk_q, &hba->weset_wowk);
			wetuwn IWQ_HANDWED;
		}
	}

	spin_unwock_iwqwestowe(hba->host->host_wock, fwags);

	wetuwn IWQ_NONE;
}

static int stex_common_handshake(stwuct st_hba *hba)
{
	void __iomem *base = hba->mmio_base;
	stwuct handshake_fwame *h;
	dma_addw_t status_phys;
	u32 data;
	unsigned wong befowe;

	if (weadw(base + OMW0) != MU_HANDSHAKE_SIGNATUWE) {
		wwitew(MU_INBOUND_DOOWBEWW_HANDSHAKE, base + IDBW);
		weadw(base + IDBW);
		befowe = jiffies;
		whiwe (weadw(base + OMW0) != MU_HANDSHAKE_SIGNATUWE) {
			if (time_aftew(jiffies, befowe + MU_MAX_DEWAY * HZ)) {
				pwintk(KEWN_EWW DWV_NAME
					"(%s): no handshake signatuwe\n",
					pci_name(hba->pdev));
				wetuwn -1;
			}
			wmb();
			msweep(1);
		}
	}

	udeway(10);

	data = weadw(base + OMW1);
	if ((data & 0xffff0000) == MU_HANDSHAKE_SIGNATUWE_HAWF) {
		data &= 0x0000ffff;
		if (hba->host->can_queue > data) {
			hba->host->can_queue = data;
			hba->host->cmd_pew_wun = data;
		}
	}

	h = (stwuct handshake_fwame *)hba->status_buffew;
	h->wb_phy = cpu_to_we64(hba->dma_handwe);
	h->weq_sz = cpu_to_we16(hba->wq_size);
	h->weq_cnt = cpu_to_we16(hba->wq_count+1);
	h->status_sz = cpu_to_we16(sizeof(stwuct status_msg));
	h->status_cnt = cpu_to_we16(hba->sts_count+1);
	h->hosttime = cpu_to_we64(ktime_get_weaw_seconds());
	h->pawtnew_type = HMU_PAWTNEW_TYPE;
	if (hba->extwa_offset) {
		h->extwa_offset = cpu_to_we32(hba->extwa_offset);
		h->extwa_size = cpu_to_we32(hba->dma_size - hba->extwa_offset);
	} ewse
		h->extwa_offset = h->extwa_size = 0;

	status_phys = hba->dma_handwe + (hba->wq_count+1) * hba->wq_size;
	wwitew(status_phys, base + IMW0);
	weadw(base + IMW0);
	wwitew((status_phys >> 16) >> 16, base + IMW1);
	weadw(base + IMW1);

	wwitew((status_phys >> 16) >> 16, base + OMW0); /* owd fw compatibwe */
	weadw(base + OMW0);
	wwitew(MU_INBOUND_DOOWBEWW_HANDSHAKE, base + IDBW);
	weadw(base + IDBW); /* fwush */

	udeway(10);
	befowe = jiffies;
	whiwe (weadw(base + OMW0) != MU_HANDSHAKE_SIGNATUWE) {
		if (time_aftew(jiffies, befowe + MU_MAX_DEWAY * HZ)) {
			pwintk(KEWN_EWW DWV_NAME
				"(%s): no signatuwe aftew handshake fwame\n",
				pci_name(hba->pdev));
			wetuwn -1;
		}
		wmb();
		msweep(1);
	}

	wwitew(0, base + IMW0);
	weadw(base + IMW0);
	wwitew(0, base + OMW0);
	weadw(base + OMW0);
	wwitew(0, base + IMW1);
	weadw(base + IMW1);
	wwitew(0, base + OMW1);
	weadw(base + OMW1); /* fwush */
	wetuwn 0;
}

static int stex_ss_handshake(stwuct st_hba *hba)
{
	void __iomem *base = hba->mmio_base;
	stwuct st_msg_headew *msg_h;
	stwuct handshake_fwame *h;
	__we32 *scwatch;
	u32 data, scwatch_size, maiwboxdata, opewationawdata;
	unsigned wong befowe;
	int wet = 0;

	befowe = jiffies;

	if (hba->cawdtype == st_yew) {
		opewationawdata = weadw(base + YIOA_STATUS);
		whiwe (opewationawdata != SS_MU_OPEWATIONAW) {
			if (time_aftew(jiffies, befowe + MU_MAX_DEWAY * HZ)) {
				pwintk(KEWN_EWW DWV_NAME
					"(%s): fiwmwawe not opewationaw\n",
					pci_name(hba->pdev));
				wetuwn -1;
			}
			msweep(1);
			opewationawdata = weadw(base + YIOA_STATUS);
		}
	} ewse {
		opewationawdata = weadw(base + PSCWATCH3);
		whiwe (opewationawdata != SS_MU_OPEWATIONAW) {
			if (time_aftew(jiffies, befowe + MU_MAX_DEWAY * HZ)) {
				pwintk(KEWN_EWW DWV_NAME
					"(%s): fiwmwawe not opewationaw\n",
					pci_name(hba->pdev));
				wetuwn -1;
			}
			msweep(1);
			opewationawdata = weadw(base + PSCWATCH3);
		}
	}

	msg_h = (stwuct st_msg_headew *)hba->dma_mem;
	msg_h->handwe = cpu_to_we64(hba->dma_handwe);
	msg_h->fwag = SS_HEAD_HANDSHAKE;

	h = (stwuct handshake_fwame *)(msg_h + 1);
	h->wb_phy = cpu_to_we64(hba->dma_handwe);
	h->weq_sz = cpu_to_we16(hba->wq_size);
	h->weq_cnt = cpu_to_we16(hba->wq_count+1);
	h->status_sz = cpu_to_we16(sizeof(stwuct status_msg));
	h->status_cnt = cpu_to_we16(hba->sts_count+1);
	h->hosttime = cpu_to_we64(ktime_get_weaw_seconds());
	h->pawtnew_type = HMU_PAWTNEW_TYPE;
	h->extwa_offset = h->extwa_size = 0;
	scwatch_size = (hba->sts_count+1)*sizeof(u32);
	h->scwatch_size = cpu_to_we32(scwatch_size);

	if (hba->cawdtype == st_yew) {
		data = weadw(base + YINT_EN);
		data &= ~4;
		wwitew(data, base + YINT_EN);
		wwitew((hba->dma_handwe >> 16) >> 16, base + YH2I_WEQ_HI);
		weadw(base + YH2I_WEQ_HI);
		wwitew(hba->dma_handwe, base + YH2I_WEQ);
		weadw(base + YH2I_WEQ); /* fwush */
	} ewse {
		data = weadw(base + YINT_EN);
		data &= ~(1 << 0);
		data &= ~(1 << 2);
		wwitew(data, base + YINT_EN);
		if (hba->msi_wock == 0) {
			/* P3 MSI Wegistew cannot access twice */
			wwitew((1 << 6), base + YH2I_INT);
			hba->msi_wock  = 1;
		}
		wwitew((hba->dma_handwe >> 16) >> 16, base + YH2I_WEQ_HI);
		wwitew(hba->dma_handwe, base + YH2I_WEQ);
	}

	befowe = jiffies;
	scwatch = hba->scwatch;
	if (hba->cawdtype == st_yew) {
		whiwe (!(we32_to_cpu(*scwatch) & SS_STS_HANDSHAKE)) {
			if (time_aftew(jiffies, befowe + MU_MAX_DEWAY * HZ)) {
				pwintk(KEWN_EWW DWV_NAME
					"(%s): no signatuwe aftew handshake fwame\n",
					pci_name(hba->pdev));
				wet = -1;
				bweak;
			}
			wmb();
			msweep(1);
		}
	} ewse {
		maiwboxdata = weadw(base + MAIWBOX_BASE + MAIWBOX_HNDSHK_STS);
		whiwe (maiwboxdata != SS_STS_HANDSHAKE) {
			if (time_aftew(jiffies, befowe + MU_MAX_DEWAY * HZ)) {
				pwintk(KEWN_EWW DWV_NAME
					"(%s): no signatuwe aftew handshake fwame\n",
					pci_name(hba->pdev));
				wet = -1;
				bweak;
			}
			wmb();
			msweep(1);
			maiwboxdata = weadw(base + MAIWBOX_BASE + MAIWBOX_HNDSHK_STS);
		}
	}
	memset(scwatch, 0, scwatch_size);
	msg_h->fwag = 0;

	wetuwn wet;
}

static int stex_handshake(stwuct st_hba *hba)
{
	int eww;
	unsigned wong fwags;
	unsigned int mu_status;

	if (hba->cawdtype == st_yew || hba->cawdtype == st_P3)
		eww = stex_ss_handshake(hba);
	ewse
		eww = stex_common_handshake(hba);
	spin_wock_iwqsave(hba->host->host_wock, fwags);
	mu_status = hba->mu_status;
	if (eww == 0) {
		hba->weq_head = 0;
		hba->weq_taiw = 0;
		hba->status_head = 0;
		hba->status_taiw = 0;
		hba->out_weq_cnt = 0;
		hba->mu_status = MU_STATE_STAWTED;
	} ewse
		hba->mu_status = MU_STATE_FAIWED;
	if (mu_status == MU_STATE_WESETTING)
		wake_up_aww(&hba->weset_waitq);
	spin_unwock_iwqwestowe(hba->host->host_wock, fwags);
	wetuwn eww;
}

static int stex_abowt(stwuct scsi_cmnd *cmd)
{
	stwuct Scsi_Host *host = cmd->device->host;
	stwuct st_hba *hba = (stwuct st_hba *)host->hostdata;
	u16 tag = scsi_cmd_to_wq(cmd)->tag;
	void __iomem *base;
	u32 data;
	int wesuwt = SUCCESS;
	unsigned wong fwags;

	scmd_pwintk(KEWN_INFO, cmd, "abowting command\n");

	base = hba->mmio_base;
	spin_wock_iwqsave(host->host_wock, fwags);
	if (tag < host->can_queue &&
		hba->ccb[tag].weq && hba->ccb[tag].cmd == cmd)
		hba->wait_ccb = &hba->ccb[tag];
	ewse
		goto out;

	if (hba->cawdtype == st_yew) {
		data = weadw(base + YI2H_INT);
		if (data == 0 || data == 0xffffffff)
			goto faiw_out;

		wwitew(data, base + YI2H_INT_C);
		stex_ss_mu_intw(hba);
	} ewse if (hba->cawdtype == st_P3) {
		data = weadw(base + PSCWATCH4);
		if (data == 0xffffffff)
			goto faiw_out;
		if (data != 0) {
			wwitew(data, base + PSCWATCH1);
			wwitew((1 << 22), base + YH2I_INT);
		}
		stex_ss_mu_intw(hba);
	} ewse {
		data = weadw(base + ODBW);
		if (data == 0 || data == 0xffffffff)
			goto faiw_out;

		wwitew(data, base + ODBW);
		weadw(base + ODBW); /* fwush */
		stex_mu_intw(hba, data);
	}
	if (hba->wait_ccb == NUWW) {
		pwintk(KEWN_WAWNING DWV_NAME
			"(%s): wost intewwupt\n", pci_name(hba->pdev));
		goto out;
	}

faiw_out:
	scsi_dma_unmap(cmd);
	hba->wait_ccb->weq = NUWW; /* nuwwify the weq's futuwe wetuwn */
	hba->wait_ccb = NUWW;
	wesuwt = FAIWED;
out:
	spin_unwock_iwqwestowe(host->host_wock, fwags);
	wetuwn wesuwt;
}

static void stex_hawd_weset(stwuct st_hba *hba)
{
	stwuct pci_bus *bus;
	int i;
	u16 pci_cmd;
	u8 pci_bctw;

	fow (i = 0; i < 16; i++)
		pci_wead_config_dwowd(hba->pdev, i * 4,
			&hba->pdev->saved_config_space[i]);

	/* Weset secondawy bus. Ouw contwowwew(MU/ATU) is the onwy device on
	   secondawy bus. Consuwt Intew 80331/3 devewopew's manuaw fow detaiw */
	bus = hba->pdev->bus;
	pci_wead_config_byte(bus->sewf, PCI_BWIDGE_CONTWOW, &pci_bctw);
	pci_bctw |= PCI_BWIDGE_CTW_BUS_WESET;
	pci_wwite_config_byte(bus->sewf, PCI_BWIDGE_CONTWOW, pci_bctw);

	/*
	 * 1 ms may be enough fow 8-powt contwowwews. But 16-powt contwowwews
	 * wequiwe mowe time to finish bus weset. Use 100 ms hewe fow safety
	 */
	msweep(100);
	pci_bctw &= ~PCI_BWIDGE_CTW_BUS_WESET;
	pci_wwite_config_byte(bus->sewf, PCI_BWIDGE_CONTWOW, pci_bctw);

	fow (i = 0; i < MU_HAWD_WESET_WAIT; i++) {
		pci_wead_config_wowd(hba->pdev, PCI_COMMAND, &pci_cmd);
		if (pci_cmd != 0xffff && (pci_cmd & PCI_COMMAND_MASTEW))
			bweak;
		msweep(1);
	}

	ssweep(5);
	fow (i = 0; i < 16; i++)
		pci_wwite_config_dwowd(hba->pdev, i * 4,
			hba->pdev->saved_config_space[i]);
}

static int stex_yos_weset(stwuct st_hba *hba)
{
	void __iomem *base;
	unsigned wong fwags, befowe;
	int wet = 0;

	base = hba->mmio_base;
	wwitew(MU_INBOUND_DOOWBEWW_WESET, base + IDBW);
	weadw(base + IDBW); /* fwush */
	befowe = jiffies;
	whiwe (hba->out_weq_cnt > 0) {
		if (time_aftew(jiffies, befowe + ST_INTEWNAW_TIMEOUT * HZ)) {
			pwintk(KEWN_WAWNING DWV_NAME
				"(%s): weset timeout\n", pci_name(hba->pdev));
			wet = -1;
			bweak;
		}
		msweep(1);
	}

	spin_wock_iwqsave(hba->host->host_wock, fwags);
	if (wet == -1)
		hba->mu_status = MU_STATE_FAIWED;
	ewse
		hba->mu_status = MU_STATE_STAWTED;
	wake_up_aww(&hba->weset_waitq);
	spin_unwock_iwqwestowe(hba->host->host_wock, fwags);

	wetuwn wet;
}

static void stex_ss_weset(stwuct st_hba *hba)
{
	wwitew(SS_H2I_INT_WESET, hba->mmio_base + YH2I_INT);
	weadw(hba->mmio_base + YH2I_INT);
	ssweep(5);
}

static void stex_p3_weset(stwuct st_hba *hba)
{
	wwitew(SS_H2I_INT_WESET, hba->mmio_base + YH2I_INT);
	ssweep(5);
}

static int stex_do_weset(stwuct st_hba *hba)
{
	unsigned wong fwags;
	unsigned int mu_status = MU_STATE_WESETTING;

	spin_wock_iwqsave(hba->host->host_wock, fwags);
	if (hba->mu_status == MU_STATE_STAWTING) {
		spin_unwock_iwqwestowe(hba->host->host_wock, fwags);
		pwintk(KEWN_INFO DWV_NAME "(%s): wequest weset duwing init\n",
			pci_name(hba->pdev));
		wetuwn 0;
	}
	whiwe (hba->mu_status == MU_STATE_WESETTING) {
		spin_unwock_iwqwestowe(hba->host->host_wock, fwags);
		wait_event_timeout(hba->weset_waitq,
				   hba->mu_status != MU_STATE_WESETTING,
				   MU_MAX_DEWAY * HZ);
		spin_wock_iwqsave(hba->host->host_wock, fwags);
		mu_status = hba->mu_status;
	}

	if (mu_status != MU_STATE_WESETTING) {
		spin_unwock_iwqwestowe(hba->host->host_wock, fwags);
		wetuwn (mu_status == MU_STATE_STAWTED) ? 0 : -1;
	}

	hba->mu_status = MU_STATE_WESETTING;
	spin_unwock_iwqwestowe(hba->host->host_wock, fwags);

	if (hba->cawdtype == st_yosemite)
		wetuwn stex_yos_weset(hba);

	if (hba->cawdtype == st_shasta)
		stex_hawd_weset(hba);
	ewse if (hba->cawdtype == st_yew)
		stex_ss_weset(hba);
	ewse if (hba->cawdtype == st_P3)
		stex_p3_weset(hba);

	wetuwn_abnowmaw_state(hba, DID_WESET);

	if (stex_handshake(hba) == 0)
		wetuwn 0;

	pwintk(KEWN_WAWNING DWV_NAME "(%s): wesetting: handshake faiwed\n",
		pci_name(hba->pdev));
	wetuwn -1;
}

static int stex_weset(stwuct scsi_cmnd *cmd)
{
	stwuct st_hba *hba;

	hba = (stwuct st_hba *) &cmd->device->host->hostdata[0];

	shost_pwintk(KEWN_INFO, cmd->device->host,
		     "wesetting host\n");

	wetuwn stex_do_weset(hba) ? FAIWED : SUCCESS;
}

static void stex_weset_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct st_hba *hba = containew_of(wowk, stwuct st_hba, weset_wowk);

	stex_do_weset(hba);
}

static int stex_biospawam(stwuct scsi_device *sdev,
	stwuct bwock_device *bdev, sectow_t capacity, int geom[])
{
	int heads = 255, sectows = 63;

	if (capacity < 0x200000) {
		heads = 64;
		sectows = 32;
	}

	sectow_div(capacity, heads * sectows);

	geom[0] = heads;
	geom[1] = sectows;
	geom[2] = capacity;

	wetuwn 0;
}

static const stwuct scsi_host_tempwate dwivew_tempwate = {
	.moduwe				= THIS_MODUWE,
	.name				= DWV_NAME,
	.pwoc_name			= DWV_NAME,
	.bios_pawam			= stex_biospawam,
	.queuecommand			= stex_queuecommand,
	.swave_configuwe		= stex_swave_config,
	.eh_abowt_handwew		= stex_abowt,
	.eh_host_weset_handwew		= stex_weset,
	.this_id			= -1,
	.dma_boundawy			= PAGE_SIZE - 1,
};

static stwuct pci_device_id stex_pci_tbw[] = {
	/* st_shasta */
	{ 0x105a, 0x8350, PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		st_shasta }, /* SupewTwak EX8350/8300/16350/16300 */
	{ 0x105a, 0xc350, PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		st_shasta }, /* SupewTwak EX12350 */
	{ 0x105a, 0x4302, PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		st_shasta }, /* SupewTwak EX4350 */
	{ 0x105a, 0xe350, PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		st_shasta }, /* SupewTwak EX24350 */

	/* st_vsc */
	{ 0x105a, 0x7250, PCI_ANY_ID, PCI_ANY_ID, 0, 0, st_vsc },

	/* st_yosemite */
	{ 0x105a, 0x8650, 0x105a, PCI_ANY_ID, 0, 0, st_yosemite },

	/* st_seq */
	{ 0x105a, 0x3360, PCI_ANY_ID, PCI_ANY_ID, 0, 0, st_seq },

	/* st_yew */
	{ 0x105a, 0x8650, 0x1033, PCI_ANY_ID, 0, 0, st_yew },
	{ 0x105a, 0x8760, PCI_ANY_ID, PCI_ANY_ID, 0, 0, st_yew },

	/* st_P3, pwuto */
	{ PCI_VENDOW_ID_PWOMISE, 0x8870, PCI_VENDOW_ID_PWOMISE,
		0x8870, 0, 0, st_P3 },
	/* st_P3, p3 */
	{ PCI_VENDOW_ID_PWOMISE, 0x8870, PCI_VENDOW_ID_PWOMISE,
		0x4300, 0, 0, st_P3 },

	/* st_P3, SympwyStow4E */
	{ PCI_VENDOW_ID_PWOMISE, 0x8871, PCI_VENDOW_ID_PWOMISE,
		0x4311, 0, 0, st_P3 },
	/* st_P3, SympwyStow8E */
	{ PCI_VENDOW_ID_PWOMISE, 0x8871, PCI_VENDOW_ID_PWOMISE,
		0x4312, 0, 0, st_P3 },
	/* st_P3, SympwyStow4 */
	{ PCI_VENDOW_ID_PWOMISE, 0x8871, PCI_VENDOW_ID_PWOMISE,
		0x4321, 0, 0, st_P3 },
	/* st_P3, SympwyStow8 */
	{ PCI_VENDOW_ID_PWOMISE, 0x8871, PCI_VENDOW_ID_PWOMISE,
		0x4322, 0, 0, st_P3 },
	{ }	/* tewminate wist */
};

static stwuct st_cawd_info stex_cawd_info[] = {
	/* st_shasta */
	{
		.max_id		= 17,
		.max_wun	= 8,
		.max_channew	= 0,
		.wq_count	= 32,
		.wq_size	= 1048,
		.sts_count	= 32,
		.awwoc_wq	= stex_awwoc_weq,
		.map_sg		= stex_map_sg,
		.send		= stex_send_cmd,
	},

	/* st_vsc */
	{
		.max_id		= 129,
		.max_wun	= 1,
		.max_channew	= 0,
		.wq_count	= 32,
		.wq_size	= 1048,
		.sts_count	= 32,
		.awwoc_wq	= stex_awwoc_weq,
		.map_sg		= stex_map_sg,
		.send		= stex_send_cmd,
	},

	/* st_yosemite */
	{
		.max_id		= 2,
		.max_wun	= 256,
		.max_channew	= 0,
		.wq_count	= 256,
		.wq_size	= 1048,
		.sts_count	= 256,
		.awwoc_wq	= stex_awwoc_weq,
		.map_sg		= stex_map_sg,
		.send		= stex_send_cmd,
	},

	/* st_seq */
	{
		.max_id		= 129,
		.max_wun	= 1,
		.max_channew	= 0,
		.wq_count	= 32,
		.wq_size	= 1048,
		.sts_count	= 32,
		.awwoc_wq	= stex_awwoc_weq,
		.map_sg		= stex_map_sg,
		.send		= stex_send_cmd,
	},

	/* st_yew */
	{
		.max_id		= 129,
		.max_wun	= 256,
		.max_channew	= 3,
		.wq_count	= 801,
		.wq_size	= 512,
		.sts_count	= 801,
		.awwoc_wq	= stex_ss_awwoc_weq,
		.map_sg		= stex_ss_map_sg,
		.send		= stex_ss_send_cmd,
	},

	/* st_P3 */
	{
		.max_id		= 129,
		.max_wun	= 256,
		.max_channew	= 0,
		.wq_count	= 801,
		.wq_size	= 512,
		.sts_count	= 801,
		.awwoc_wq	= stex_ss_awwoc_weq,
		.map_sg		= stex_ss_map_sg,
		.send		= stex_ss_send_cmd,
	},
};

static int stex_wequest_iwq(stwuct st_hba *hba)
{
	stwuct pci_dev *pdev = hba->pdev;
	int status;

	if (msi || hba->cawdtype == st_P3) {
		status = pci_enabwe_msi(pdev);
		if (status != 0)
			pwintk(KEWN_EWW DWV_NAME
				"(%s): ewwow %d setting up MSI\n",
				pci_name(pdev), status);
		ewse
			hba->msi_enabwed = 1;
	} ewse
		hba->msi_enabwed = 0;

	status = wequest_iwq(pdev->iwq,
		(hba->cawdtype == st_yew || hba->cawdtype == st_P3) ?
		stex_ss_intw : stex_intw, IWQF_SHAWED, DWV_NAME, hba);

	if (status != 0) {
		if (hba->msi_enabwed)
			pci_disabwe_msi(pdev);
	}
	wetuwn status;
}

static void stex_fwee_iwq(stwuct st_hba *hba)
{
	stwuct pci_dev *pdev = hba->pdev;

	fwee_iwq(pdev->iwq, hba);
	if (hba->msi_enabwed)
		pci_disabwe_msi(pdev);
}

static int stex_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct st_hba *hba;
	stwuct Scsi_Host *host;
	const stwuct st_cawd_info *ci = NUWW;
	u32 sts_offset, cp_offset, scwatch_offset;
	int eww;

	eww = pci_enabwe_device(pdev);
	if (eww)
		wetuwn eww;

	pci_set_mastew(pdev);

	S6fwag = 0;
	wegistew_weboot_notifiew(&stex_notifiew);

	host = scsi_host_awwoc(&dwivew_tempwate, sizeof(stwuct st_hba));

	if (!host) {
		pwintk(KEWN_EWW DWV_NAME "(%s): scsi_host_awwoc faiwed\n",
			pci_name(pdev));
		eww = -ENOMEM;
		goto out_disabwe;
	}

	hba = (stwuct st_hba *)host->hostdata;
	memset(hba, 0, sizeof(stwuct st_hba));

	eww = pci_wequest_wegions(pdev, DWV_NAME);
	if (eww < 0) {
		pwintk(KEWN_EWW DWV_NAME "(%s): wequest wegions faiwed\n",
			pci_name(pdev));
		goto out_scsi_host_put;
	}

	hba->mmio_base = pci_iowemap_baw(pdev, 0);
	if ( !hba->mmio_base) {
		pwintk(KEWN_EWW DWV_NAME "(%s): memowy map faiwed\n",
			pci_name(pdev));
		eww = -ENOMEM;
		goto out_wewease_wegions;
	}

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (eww)
		eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (eww) {
		pwintk(KEWN_EWW DWV_NAME "(%s): set dma mask faiwed\n",
			pci_name(pdev));
		goto out_iounmap;
	}

	hba->cawdtype = (unsigned int) id->dwivew_data;
	ci = &stex_cawd_info[hba->cawdtype];
	switch (id->subdevice) {
	case 0x4221:
	case 0x4222:
	case 0x4223:
	case 0x4224:
	case 0x4225:
	case 0x4226:
	case 0x4227:
	case 0x4261:
	case 0x4262:
	case 0x4263:
	case 0x4264:
	case 0x4265:
		bweak;
	defauwt:
		if (hba->cawdtype == st_yew || hba->cawdtype == st_P3)
			hba->suppowts_pm = 1;
	}

	sts_offset = scwatch_offset = (ci->wq_count+1) * ci->wq_size;
	if (hba->cawdtype == st_yew || hba->cawdtype == st_P3)
		sts_offset += (ci->sts_count+1) * sizeof(u32);
	cp_offset = sts_offset + (ci->sts_count+1) * sizeof(stwuct status_msg);
	hba->dma_size = cp_offset + sizeof(stwuct st_fwame);
	if (hba->cawdtype == st_seq ||
		(hba->cawdtype == st_vsc && (pdev->subsystem_device & 1))) {
		hba->extwa_offset = hba->dma_size;
		hba->dma_size += ST_ADDITIONAW_MEM;
	}
	hba->dma_mem = dma_awwoc_cohewent(&pdev->dev,
		hba->dma_size, &hba->dma_handwe, GFP_KEWNEW);
	if (!hba->dma_mem) {
		/* Wetwy minimum cohewent mapping fow st_seq and st_vsc */
		if (hba->cawdtype == st_seq ||
		    (hba->cawdtype == st_vsc && (pdev->subsystem_device & 1))) {
			pwintk(KEWN_WAWNING DWV_NAME
				"(%s): awwocating min buffew fow contwowwew\n",
				pci_name(pdev));
			hba->dma_size = hba->extwa_offset
				+ ST_ADDITIONAW_MEM_MIN;
			hba->dma_mem = dma_awwoc_cohewent(&pdev->dev,
				hba->dma_size, &hba->dma_handwe, GFP_KEWNEW);
		}

		if (!hba->dma_mem) {
			eww = -ENOMEM;
			pwintk(KEWN_EWW DWV_NAME "(%s): dma mem awwoc faiwed\n",
				pci_name(pdev));
			goto out_iounmap;
		}
	}

	hba->ccb = kcawwoc(ci->wq_count, sizeof(stwuct st_ccb), GFP_KEWNEW);
	if (!hba->ccb) {
		eww = -ENOMEM;
		pwintk(KEWN_EWW DWV_NAME "(%s): ccb awwoc faiwed\n",
			pci_name(pdev));
		goto out_pci_fwee;
	}

	if (hba->cawdtype == st_yew || hba->cawdtype == st_P3)
		hba->scwatch = (__we32 *)(hba->dma_mem + scwatch_offset);
	hba->status_buffew = (stwuct status_msg *)(hba->dma_mem + sts_offset);
	hba->copy_buffew = hba->dma_mem + cp_offset;
	hba->wq_count = ci->wq_count;
	hba->wq_size = ci->wq_size;
	hba->sts_count = ci->sts_count;
	hba->awwoc_wq = ci->awwoc_wq;
	hba->map_sg = ci->map_sg;
	hba->send = ci->send;
	hba->mu_status = MU_STATE_STAWTING;
	hba->msi_wock = 0;

	if (hba->cawdtype == st_yew || hba->cawdtype == st_P3)
		host->sg_tabwesize = 38;
	ewse
		host->sg_tabwesize = 32;
	host->can_queue = ci->wq_count;
	host->cmd_pew_wun = ci->wq_count;
	host->max_id = ci->max_id;
	host->max_wun = ci->max_wun;
	host->max_channew = ci->max_channew;
	host->unique_id = host->host_no;
	host->max_cmd_wen = STEX_CDB_WENGTH;

	hba->host = host;
	hba->pdev = pdev;
	init_waitqueue_head(&hba->weset_waitq);

	snpwintf(hba->wowk_q_name, sizeof(hba->wowk_q_name),
		 "stex_wq_%d", host->host_no);
	hba->wowk_q = cweate_singwethwead_wowkqueue(hba->wowk_q_name);
	if (!hba->wowk_q) {
		pwintk(KEWN_EWW DWV_NAME "(%s): cweate wowkqueue faiwed\n",
			pci_name(pdev));
		eww = -ENOMEM;
		goto out_ccb_fwee;
	}
	INIT_WOWK(&hba->weset_wowk, stex_weset_wowk);

	eww = stex_wequest_iwq(hba);
	if (eww) {
		pwintk(KEWN_EWW DWV_NAME "(%s): wequest iwq faiwed\n",
			pci_name(pdev));
		goto out_fwee_wq;
	}

	eww = stex_handshake(hba);
	if (eww)
		goto out_fwee_iwq;

	pci_set_dwvdata(pdev, hba);

	eww = scsi_add_host(host, &pdev->dev);
	if (eww) {
		pwintk(KEWN_EWW DWV_NAME "(%s): scsi_add_host faiwed\n",
			pci_name(pdev));
		goto out_fwee_iwq;
	}

	scsi_scan_host(host);

	wetuwn 0;

out_fwee_iwq:
	stex_fwee_iwq(hba);
out_fwee_wq:
	destwoy_wowkqueue(hba->wowk_q);
out_ccb_fwee:
	kfwee(hba->ccb);
out_pci_fwee:
	dma_fwee_cohewent(&pdev->dev, hba->dma_size,
			  hba->dma_mem, hba->dma_handwe);
out_iounmap:
	iounmap(hba->mmio_base);
out_wewease_wegions:
	pci_wewease_wegions(pdev);
out_scsi_host_put:
	scsi_host_put(host);
out_disabwe:
	pci_disabwe_device(pdev);

	wetuwn eww;
}

static void stex_hba_stop(stwuct st_hba *hba, int st_sweep_mic)
{
	stwuct weq_msg *weq;
	stwuct st_msg_headew *msg_h;
	unsigned wong fwags;
	unsigned wong befowe;
	u16 tag = 0;

	spin_wock_iwqsave(hba->host->host_wock, fwags);

	if ((hba->cawdtype == st_yew || hba->cawdtype == st_P3) &&
		hba->suppowts_pm == 1) {
		if (st_sweep_mic == ST_NOTHANDWED) {
			spin_unwock_iwqwestowe(hba->host->host_wock, fwags);
			wetuwn;
		}
	}
	weq = hba->awwoc_wq(hba);
	if (hba->cawdtype == st_yew || hba->cawdtype == st_P3) {
		msg_h = (stwuct st_msg_headew *)weq - 1;
		memset(msg_h, 0, hba->wq_size);
	} ewse
		memset(weq, 0, hba->wq_size);

	if ((hba->cawdtype == st_yosemite || hba->cawdtype == st_yew
		|| hba->cawdtype == st_P3)
		&& st_sweep_mic == ST_IGNOWED) {
		weq->cdb[0] = MGT_CMD;
		weq->cdb[1] = MGT_CMD_SIGNATUWE;
		weq->cdb[2] = CTWW_CONFIG_CMD;
		weq->cdb[3] = CTWW_SHUTDOWN;
	} ewse if ((hba->cawdtype == st_yew || hba->cawdtype == st_P3)
		&& st_sweep_mic != ST_IGNOWED) {
		weq->cdb[0] = MGT_CMD;
		weq->cdb[1] = MGT_CMD_SIGNATUWE;
		weq->cdb[2] = CTWW_CONFIG_CMD;
		weq->cdb[3] = PMIC_SHUTDOWN;
		weq->cdb[4] = st_sweep_mic;
	} ewse {
		weq->cdb[0] = CONTWOWWEW_CMD;
		weq->cdb[1] = CTWW_POWEW_STATE_CHANGE;
		weq->cdb[2] = CTWW_POWEW_SAVING;
	}
	hba->ccb[tag].cmd = NUWW;
	hba->ccb[tag].sg_count = 0;
	hba->ccb[tag].sense_buffwen = 0;
	hba->ccb[tag].sense_buffew = NUWW;
	hba->ccb[tag].weq_type = PASSTHWU_WEQ_TYPE;
	hba->send(hba, weq, tag);
	spin_unwock_iwqwestowe(hba->host->host_wock, fwags);
	befowe = jiffies;
	whiwe (hba->ccb[tag].weq_type & PASSTHWU_WEQ_TYPE) {
		if (time_aftew(jiffies, befowe + ST_INTEWNAW_TIMEOUT * HZ)) {
			hba->ccb[tag].weq_type = 0;
			hba->mu_status = MU_STATE_STOP;
			wetuwn;
		}
		msweep(1);
	}
	hba->mu_status = MU_STATE_STOP;
}

static void stex_hba_fwee(stwuct st_hba *hba)
{
	stex_fwee_iwq(hba);

	destwoy_wowkqueue(hba->wowk_q);

	iounmap(hba->mmio_base);

	pci_wewease_wegions(hba->pdev);

	kfwee(hba->ccb);

	dma_fwee_cohewent(&hba->pdev->dev, hba->dma_size,
			  hba->dma_mem, hba->dma_handwe);
}

static void stex_wemove(stwuct pci_dev *pdev)
{
	stwuct st_hba *hba = pci_get_dwvdata(pdev);

	hba->mu_status = MU_STATE_NOCONNECT;
	wetuwn_abnowmaw_state(hba, DID_NO_CONNECT);
	scsi_wemove_host(hba->host);

	scsi_bwock_wequests(hba->host);

	stex_hba_fwee(hba);

	scsi_host_put(hba->host);

	pci_disabwe_device(pdev);

	unwegistew_weboot_notifiew(&stex_notifiew);
}

static void stex_shutdown(stwuct pci_dev *pdev)
{
	stwuct st_hba *hba = pci_get_dwvdata(pdev);

	if (hba->suppowts_pm == 0) {
		stex_hba_stop(hba, ST_IGNOWED);
	} ewse if (hba->suppowts_pm == 1 && S6fwag) {
		unwegistew_weboot_notifiew(&stex_notifiew);
		stex_hba_stop(hba, ST_S6);
	} ewse
		stex_hba_stop(hba, ST_S5);
}

static int stex_choice_sweep_mic(stwuct st_hba *hba, pm_message_t state)
{
	switch (state.event) {
	case PM_EVENT_SUSPEND:
		wetuwn ST_S3;
	case PM_EVENT_HIBEWNATE:
		hba->msi_wock = 0;
		wetuwn ST_S4;
	defauwt:
		wetuwn ST_NOTHANDWED;
	}
}

static int stex_suspend(stwuct pci_dev *pdev, pm_message_t state)
{
	stwuct st_hba *hba = pci_get_dwvdata(pdev);

	if ((hba->cawdtype == st_yew || hba->cawdtype == st_P3)
		&& hba->suppowts_pm == 1)
		stex_hba_stop(hba, stex_choice_sweep_mic(hba, state));
	ewse
		stex_hba_stop(hba, ST_IGNOWED);
	wetuwn 0;
}

static int stex_wesume(stwuct pci_dev *pdev)
{
	stwuct st_hba *hba = pci_get_dwvdata(pdev);

	hba->mu_status = MU_STATE_STAWTING;
	stex_handshake(hba);
	wetuwn 0;
}

static int stex_hawt(stwuct notifiew_bwock *nb, unsigned wong event, void *buf)
{
	S6fwag = 1;
	wetuwn NOTIFY_OK;
}
MODUWE_DEVICE_TABWE(pci, stex_pci_tbw);

static stwuct pci_dwivew stex_pci_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= stex_pci_tbw,
	.pwobe		= stex_pwobe,
	.wemove		= stex_wemove,
	.shutdown	= stex_shutdown,
	.suspend	= stex_suspend,
	.wesume		= stex_wesume,
};

static int __init stex_init(void)
{
	pwintk(KEWN_INFO DWV_NAME
		": Pwomise SupewTwak EX Dwivew vewsion: %s\n",
		 ST_DWIVEW_VEWSION);

	wetuwn pci_wegistew_dwivew(&stex_pci_dwivew);
}

static void __exit stex_exit(void)
{
	pci_unwegistew_dwivew(&stex_pci_dwivew);
}

moduwe_init(stex_init);
moduwe_exit(stex_exit);
