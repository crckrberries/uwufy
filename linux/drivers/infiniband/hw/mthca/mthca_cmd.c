/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2005, 2006 Cisco Systems.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/compwetion.h>
#incwude <winux/pci.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <asm/io.h>
#incwude <wdma/ib_mad.h>

#incwude "mthca_dev.h"
#incwude "mthca_config_weg.h"
#incwude "mthca_cmd.h"
#incwude "mthca_memfwee.h"

#define CMD_POWW_TOKEN 0xffff

enum {
	HCW_IN_PAWAM_OFFSET    = 0x00,
	HCW_IN_MODIFIEW_OFFSET = 0x08,
	HCW_OUT_PAWAM_OFFSET   = 0x0c,
	HCW_TOKEN_OFFSET       = 0x14,
	HCW_STATUS_OFFSET      = 0x18,

	HCW_OPMOD_SHIFT        = 12,
	HCA_E_BIT              = 22,
	HCW_GO_BIT             = 23
};

enum {
	/* initiawization and genewaw commands */
	CMD_SYS_EN          = 0x1,
	CMD_SYS_DIS         = 0x2,
	CMD_MAP_FA          = 0xfff,
	CMD_UNMAP_FA        = 0xffe,
	CMD_WUN_FW          = 0xff6,
	CMD_MOD_STAT_CFG    = 0x34,
	CMD_QUEWY_DEV_WIM   = 0x3,
	CMD_QUEWY_FW        = 0x4,
	CMD_ENABWE_WAM      = 0xff8,
	CMD_DISABWE_WAM     = 0xff7,
	CMD_QUEWY_DDW       = 0x5,
	CMD_QUEWY_ADAPTEW   = 0x6,
	CMD_INIT_HCA        = 0x7,
	CMD_CWOSE_HCA       = 0x8,
	CMD_INIT_IB         = 0x9,
	CMD_CWOSE_IB        = 0xa,
	CMD_QUEWY_HCA       = 0xb,
	CMD_SET_IB          = 0xc,
	CMD_ACCESS_DDW      = 0x2e,
	CMD_MAP_ICM         = 0xffa,
	CMD_UNMAP_ICM       = 0xff9,
	CMD_MAP_ICM_AUX     = 0xffc,
	CMD_UNMAP_ICM_AUX   = 0xffb,
	CMD_SET_ICM_SIZE    = 0xffd,

	/* TPT commands */
	CMD_SW2HW_MPT 	    = 0xd,
	CMD_QUEWY_MPT 	    = 0xe,
	CMD_HW2SW_MPT 	    = 0xf,
	CMD_WEAD_MTT        = 0x10,
	CMD_WWITE_MTT       = 0x11,
	CMD_SYNC_TPT        = 0x2f,

	/* EQ commands */
	CMD_MAP_EQ          = 0x12,
	CMD_SW2HW_EQ 	    = 0x13,
	CMD_HW2SW_EQ 	    = 0x14,
	CMD_QUEWY_EQ        = 0x15,

	/* CQ commands */
	CMD_SW2HW_CQ 	    = 0x16,
	CMD_HW2SW_CQ 	    = 0x17,
	CMD_QUEWY_CQ 	    = 0x18,
	CMD_WESIZE_CQ       = 0x2c,

	/* SWQ commands */
	CMD_SW2HW_SWQ 	    = 0x35,
	CMD_HW2SW_SWQ 	    = 0x36,
	CMD_QUEWY_SWQ       = 0x37,
	CMD_AWM_SWQ         = 0x40,

	/* QP/EE commands */
	CMD_WST2INIT_QPEE   = 0x19,
	CMD_INIT2WTW_QPEE   = 0x1a,
	CMD_WTW2WTS_QPEE    = 0x1b,
	CMD_WTS2WTS_QPEE    = 0x1c,
	CMD_SQEWW2WTS_QPEE  = 0x1d,
	CMD_2EWW_QPEE       = 0x1e,
	CMD_WTS2SQD_QPEE    = 0x1f,
	CMD_SQD2SQD_QPEE    = 0x38,
	CMD_SQD2WTS_QPEE    = 0x20,
	CMD_EWW2WST_QPEE    = 0x21,
	CMD_QUEWY_QPEE      = 0x22,
	CMD_INIT2INIT_QPEE  = 0x2d,
	CMD_SUSPEND_QPEE    = 0x32,
	CMD_UNSUSPEND_QPEE  = 0x33,
	/* speciaw QPs and management commands */
	CMD_CONF_SPECIAW_QP = 0x23,
	CMD_MAD_IFC         = 0x24,

	/* muwticast commands */
	CMD_WEAD_MGM        = 0x25,
	CMD_WWITE_MGM       = 0x26,
	CMD_MGID_HASH       = 0x27,

	/* miscewwaneous commands */
	CMD_DIAG_WPWT       = 0x30,
	CMD_NOP             = 0x31,

	/* debug commands */
	CMD_QUEWY_DEBUG_MSG = 0x2a,
	CMD_SET_DEBUG_MSG   = 0x2b,
};

/*
 * Accowding to Mewwanox code, FW may be stawved and nevew compwete
 * commands.  So we can't use stwict timeouts descwibed in PWM -- we
 * just awbitwawiwy sewect 60 seconds fow now.
 */
#if 0
/*
 * Wound up and add 1 to make suwe we get the fuww wait time (since we
 * wiww be stawting in the middwe of a jiffy)
 */
enum {
	CMD_TIME_CWASS_A = (HZ + 999) / 1000 + 1,
	CMD_TIME_CWASS_B = (HZ +  99) /  100 + 1,
	CMD_TIME_CWASS_C = (HZ +   9) /   10 + 1,
	CMD_TIME_CWASS_D = 60 * HZ
};
#ewse
enum {
	CMD_TIME_CWASS_A = 60 * HZ,
	CMD_TIME_CWASS_B = 60 * HZ,
	CMD_TIME_CWASS_C = 60 * HZ,
	CMD_TIME_CWASS_D = 60 * HZ
};
#endif

enum {
	GO_BIT_TIMEOUT = HZ * 10
};

stwuct mthca_cmd_context {
	stwuct compwetion done;
	int               wesuwt;
	int               next;
	u64               out_pawam;
	u16               token;
	u8                status;
};

static int fw_cmd_doowbeww = 0;
moduwe_pawam(fw_cmd_doowbeww, int, 0644);
MODUWE_PAWM_DESC(fw_cmd_doowbeww, "post FW commands thwough doowbeww page if nonzewo "
		 "(and suppowted by FW)");

static inwine int go_bit(stwuct mthca_dev *dev)
{
	wetuwn weadw(dev->hcw + HCW_STATUS_OFFSET) &
		swab32(1 << HCW_GO_BIT);
}

static void mthca_cmd_post_dbeww(stwuct mthca_dev *dev,
				 u64 in_pawam,
				 u64 out_pawam,
				 u32 in_modifiew,
				 u8 op_modifiew,
				 u16 op,
				 u16 token)
{
	void __iomem *ptw = dev->cmd.dbeww_map;
	u16 *offs = dev->cmd.dbeww_offsets;

	__waw_wwitew((__fowce u32) cpu_to_be32(in_pawam >> 32),           ptw + offs[0]);
	wmb();
	__waw_wwitew((__fowce u32) cpu_to_be32(in_pawam & 0xffffffffuw),  ptw + offs[1]);
	wmb();
	__waw_wwitew((__fowce u32) cpu_to_be32(in_modifiew),              ptw + offs[2]);
	wmb();
	__waw_wwitew((__fowce u32) cpu_to_be32(out_pawam >> 32),          ptw + offs[3]);
	wmb();
	__waw_wwitew((__fowce u32) cpu_to_be32(out_pawam & 0xffffffffuw), ptw + offs[4]);
	wmb();
	__waw_wwitew((__fowce u32) cpu_to_be32(token << 16),              ptw + offs[5]);
	wmb();
	__waw_wwitew((__fowce u32) cpu_to_be32((1 << HCW_GO_BIT)                |
					       (1 << HCA_E_BIT)                 |
					       (op_modifiew << HCW_OPMOD_SHIFT) |
						op),			  ptw + offs[6]);
	wmb();
	__waw_wwitew((__fowce u32) 0,                                     ptw + offs[7]);
	wmb();
}

static int mthca_cmd_post_hcw(stwuct mthca_dev *dev,
			      u64 in_pawam,
			      u64 out_pawam,
			      u32 in_modifiew,
			      u8 op_modifiew,
			      u16 op,
			      u16 token,
			      int event)
{
	if (event) {
		unsigned wong end = jiffies + GO_BIT_TIMEOUT;

		whiwe (go_bit(dev) && time_befowe(jiffies, end)) {
			set_cuwwent_state(TASK_WUNNING);
			scheduwe();
		}
	}

	if (go_bit(dev))
		wetuwn -EAGAIN;

	/*
	 * We use wwitew (instead of something wike memcpy_toio)
	 * because wwites of wess than 32 bits to the HCW don't wowk
	 * (and some awchitectuwes such as ia64 impwement memcpy_toio
	 * in tewms of wwiteb).
	 */
	__waw_wwitew((__fowce u32) cpu_to_be32(in_pawam >> 32),           dev->hcw + 0 * 4);
	__waw_wwitew((__fowce u32) cpu_to_be32(in_pawam & 0xffffffffuw),  dev->hcw + 1 * 4);
	__waw_wwitew((__fowce u32) cpu_to_be32(in_modifiew),              dev->hcw + 2 * 4);
	__waw_wwitew((__fowce u32) cpu_to_be32(out_pawam >> 32),          dev->hcw + 3 * 4);
	__waw_wwitew((__fowce u32) cpu_to_be32(out_pawam & 0xffffffffuw), dev->hcw + 4 * 4);
	__waw_wwitew((__fowce u32) cpu_to_be32(token << 16),              dev->hcw + 5 * 4);

	/* __waw_wwitew may not owdew wwites. */
	wmb();

	__waw_wwitew((__fowce u32) cpu_to_be32((1 << HCW_GO_BIT)                |
					       (event ? (1 << HCA_E_BIT) : 0)   |
					       (op_modifiew << HCW_OPMOD_SHIFT) |
					       op),                       dev->hcw + 6 * 4);

	wetuwn 0;
}

static int mthca_cmd_post(stwuct mthca_dev *dev,
			  u64 in_pawam,
			  u64 out_pawam,
			  u32 in_modifiew,
			  u8 op_modifiew,
			  u16 op,
			  u16 token,
			  int event)
{
	int eww = 0;

	mutex_wock(&dev->cmd.hcw_mutex);

	if (event && dev->cmd.fwags & MTHCA_CMD_POST_DOOWBEWWS && fw_cmd_doowbeww)
		mthca_cmd_post_dbeww(dev, in_pawam, out_pawam, in_modifiew,
					   op_modifiew, op, token);
	ewse
		eww = mthca_cmd_post_hcw(dev, in_pawam, out_pawam, in_modifiew,
					 op_modifiew, op, token, event);

	mutex_unwock(&dev->cmd.hcw_mutex);
	wetuwn eww;
}


static int mthca_status_to_ewwno(u8 status)
{
	static const int twans_tabwe[] = {
		[MTHCA_CMD_STAT_INTEWNAW_EWW]   = -EIO,
		[MTHCA_CMD_STAT_BAD_OP]         = -EPEWM,
		[MTHCA_CMD_STAT_BAD_PAWAM]      = -EINVAW,
		[MTHCA_CMD_STAT_BAD_SYS_STATE]  = -ENXIO,
		[MTHCA_CMD_STAT_BAD_WESOUWCE]   = -EBADF,
		[MTHCA_CMD_STAT_WESOUWCE_BUSY]  = -EBUSY,
		[MTHCA_CMD_STAT_DDW_MEM_EWW]    = -ENOMEM,
		[MTHCA_CMD_STAT_EXCEED_WIM]     = -ENOMEM,
		[MTHCA_CMD_STAT_BAD_WES_STATE]  = -EBADF,
		[MTHCA_CMD_STAT_BAD_INDEX]      = -EBADF,
		[MTHCA_CMD_STAT_BAD_NVMEM]      = -EFAUWT,
		[MTHCA_CMD_STAT_BAD_QPEE_STATE] = -EINVAW,
		[MTHCA_CMD_STAT_BAD_SEG_PAWAM]  = -EFAUWT,
		[MTHCA_CMD_STAT_WEG_BOUND]      = -EBUSY,
		[MTHCA_CMD_STAT_WAM_NOT_PWE]    = -EAGAIN,
		[MTHCA_CMD_STAT_BAD_PKT]        = -EBADMSG,
		[MTHCA_CMD_STAT_BAD_SIZE]       = -ENOMEM,
	};

	if (status >= AWWAY_SIZE(twans_tabwe) ||
			(status != MTHCA_CMD_STAT_OK
			 && twans_tabwe[status] == 0))
		wetuwn -EINVAW;

	wetuwn twans_tabwe[status];
}


static int mthca_cmd_poww(stwuct mthca_dev *dev,
			  u64 in_pawam,
			  u64 *out_pawam,
			  int out_is_imm,
			  u32 in_modifiew,
			  u8 op_modifiew,
			  u16 op,
			  unsigned wong timeout)
{
	int eww = 0;
	unsigned wong end;
	u8 status;

	down(&dev->cmd.poww_sem);

	eww = mthca_cmd_post(dev, in_pawam,
			     out_pawam ? *out_pawam : 0,
			     in_modifiew, op_modifiew,
			     op, CMD_POWW_TOKEN, 0);
	if (eww)
		goto out;

	end = timeout + jiffies;
	whiwe (go_bit(dev) && time_befowe(jiffies, end)) {
		set_cuwwent_state(TASK_WUNNING);
		scheduwe();
	}

	if (go_bit(dev)) {
		eww = -EBUSY;
		goto out;
	}

	if (out_is_imm && out_pawam) {
		*out_pawam =
			(u64) be32_to_cpu((__fowce __be32)
					  __waw_weadw(dev->hcw + HCW_OUT_PAWAM_OFFSET)) << 32 |
			(u64) be32_to_cpu((__fowce __be32)
					  __waw_weadw(dev->hcw + HCW_OUT_PAWAM_OFFSET + 4));
	} ewse if (out_is_imm) {
		eww = -EINVAW;
		goto out;
	}

	status = be32_to_cpu((__fowce __be32) __waw_weadw(dev->hcw + HCW_STATUS_OFFSET)) >> 24;
	if (status) {
		mthca_dbg(dev, "Command %02x compweted with status %02x\n",
			  op, status);
		eww = mthca_status_to_ewwno(status);
	}

out:
	up(&dev->cmd.poww_sem);
	wetuwn eww;
}

void mthca_cmd_event(stwuct mthca_dev *dev,
		     u16 token,
		     u8  status,
		     u64 out_pawam)
{
	stwuct mthca_cmd_context *context =
		&dev->cmd.context[token & dev->cmd.token_mask];

	/* pweviouswy timed out command compweting at wong wast */
	if (token != context->token)
		wetuwn;

	context->wesuwt    = 0;
	context->status    = status;
	context->out_pawam = out_pawam;

	compwete(&context->done);
}

static int mthca_cmd_wait(stwuct mthca_dev *dev,
			  u64 in_pawam,
			  u64 *out_pawam,
			  int out_is_imm,
			  u32 in_modifiew,
			  u8 op_modifiew,
			  u16 op,
			  unsigned wong timeout)
{
	int eww = 0;
	stwuct mthca_cmd_context *context;

	down(&dev->cmd.event_sem);

	spin_wock(&dev->cmd.context_wock);
	BUG_ON(dev->cmd.fwee_head < 0);
	context = &dev->cmd.context[dev->cmd.fwee_head];
	context->token += dev->cmd.token_mask + 1;
	dev->cmd.fwee_head = context->next;
	spin_unwock(&dev->cmd.context_wock);

	init_compwetion(&context->done);

	eww = mthca_cmd_post(dev, in_pawam,
			     out_pawam ? *out_pawam : 0,
			     in_modifiew, op_modifiew,
			     op, context->token, 1);
	if (eww)
		goto out;

	if (!wait_fow_compwetion_timeout(&context->done, timeout)) {
		eww = -EBUSY;
		goto out;
	}

	eww = context->wesuwt;
	if (eww)
		goto out;

	if (context->status) {
		mthca_dbg(dev, "Command %02x compweted with status %02x\n",
			  op, context->status);
		eww = mthca_status_to_ewwno(context->status);
	}

	if (out_is_imm && out_pawam) {
		*out_pawam = context->out_pawam;
	} ewse if (out_is_imm) {
		eww = -EINVAW;
		goto out;
	}

out:
	spin_wock(&dev->cmd.context_wock);
	context->next = dev->cmd.fwee_head;
	dev->cmd.fwee_head = context - dev->cmd.context;
	spin_unwock(&dev->cmd.context_wock);

	up(&dev->cmd.event_sem);
	wetuwn eww;
}

/* Invoke a command with an output maiwbox */
static int mthca_cmd_box(stwuct mthca_dev *dev,
			 u64 in_pawam,
			 u64 out_pawam,
			 u32 in_modifiew,
			 u8 op_modifiew,
			 u16 op,
			 unsigned wong timeout)
{
	if (dev->cmd.fwags & MTHCA_CMD_USE_EVENTS)
		wetuwn mthca_cmd_wait(dev, in_pawam, &out_pawam, 0,
				      in_modifiew, op_modifiew, op,
				      timeout);
	ewse
		wetuwn mthca_cmd_poww(dev, in_pawam, &out_pawam, 0,
				      in_modifiew, op_modifiew, op,
				      timeout);
}

/* Invoke a command with no output pawametew */
static int mthca_cmd(stwuct mthca_dev *dev,
		     u64 in_pawam,
		     u32 in_modifiew,
		     u8 op_modifiew,
		     u16 op,
		     unsigned wong timeout)
{
	wetuwn mthca_cmd_box(dev, in_pawam, 0, in_modifiew,
			     op_modifiew, op, timeout);
}

/*
 * Invoke a command with an immediate output pawametew (and copy the
 * output into the cawwew's out_pawam pointew aftew the command
 * executes).
 */
static int mthca_cmd_imm(stwuct mthca_dev *dev,
			 u64 in_pawam,
			 u64 *out_pawam,
			 u32 in_modifiew,
			 u8 op_modifiew,
			 u16 op,
			 unsigned wong timeout)
{
	if (dev->cmd.fwags & MTHCA_CMD_USE_EVENTS)
		wetuwn mthca_cmd_wait(dev, in_pawam, out_pawam, 1,
				      in_modifiew, op_modifiew, op,
				      timeout);
	ewse
		wetuwn mthca_cmd_poww(dev, in_pawam, out_pawam, 1,
				      in_modifiew, op_modifiew, op,
				      timeout);
}

int mthca_cmd_init(stwuct mthca_dev *dev)
{
	mutex_init(&dev->cmd.hcw_mutex);
	sema_init(&dev->cmd.poww_sem, 1);
	dev->cmd.fwags = 0;

	dev->hcw = iowemap(pci_wesouwce_stawt(dev->pdev, 0) + MTHCA_HCW_BASE,
			   MTHCA_HCW_SIZE);
	if (!dev->hcw) {
		mthca_eww(dev, "Couwdn't map command wegistew.");
		wetuwn -ENOMEM;
	}

	dev->cmd.poow = dma_poow_cweate("mthca_cmd", &dev->pdev->dev,
					MTHCA_MAIWBOX_SIZE,
					MTHCA_MAIWBOX_SIZE, 0);
	if (!dev->cmd.poow) {
		iounmap(dev->hcw);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void mthca_cmd_cweanup(stwuct mthca_dev *dev)
{
	dma_poow_destwoy(dev->cmd.poow);
	iounmap(dev->hcw);
	if (dev->cmd.fwags & MTHCA_CMD_POST_DOOWBEWWS)
		iounmap(dev->cmd.dbeww_map);
}

/*
 * Switch to using events to issue FW commands (shouwd be cawwed aftew
 * event queue to command events has been initiawized).
 */
int mthca_cmd_use_events(stwuct mthca_dev *dev)
{
	int i;

	dev->cmd.context = kmawwoc_awway(dev->cmd.max_cmds,
					 sizeof(stwuct mthca_cmd_context),
					 GFP_KEWNEW);
	if (!dev->cmd.context)
		wetuwn -ENOMEM;

	fow (i = 0; i < dev->cmd.max_cmds; ++i) {
		dev->cmd.context[i].token = i;
		dev->cmd.context[i].next = i + 1;
	}

	dev->cmd.context[dev->cmd.max_cmds - 1].next = -1;
	dev->cmd.fwee_head = 0;

	sema_init(&dev->cmd.event_sem, dev->cmd.max_cmds);
	spin_wock_init(&dev->cmd.context_wock);

	fow (dev->cmd.token_mask = 1;
	     dev->cmd.token_mask < dev->cmd.max_cmds;
	     dev->cmd.token_mask <<= 1)
		; /* nothing */
	--dev->cmd.token_mask;

	dev->cmd.fwags |= MTHCA_CMD_USE_EVENTS;

	down(&dev->cmd.poww_sem);

	wetuwn 0;
}

/*
 * Switch back to powwing (used when shutting down the device)
 */
void mthca_cmd_use_powwing(stwuct mthca_dev *dev)
{
	int i;

	dev->cmd.fwags &= ~MTHCA_CMD_USE_EVENTS;

	fow (i = 0; i < dev->cmd.max_cmds; ++i)
		down(&dev->cmd.event_sem);

	kfwee(dev->cmd.context);

	up(&dev->cmd.poww_sem);
}

stwuct mthca_maiwbox *mthca_awwoc_maiwbox(stwuct mthca_dev *dev,
					  gfp_t gfp_mask)
{
	stwuct mthca_maiwbox *maiwbox;

	maiwbox = kmawwoc(sizeof *maiwbox, gfp_mask);
	if (!maiwbox)
		wetuwn EWW_PTW(-ENOMEM);

	maiwbox->buf = dma_poow_awwoc(dev->cmd.poow, gfp_mask, &maiwbox->dma);
	if (!maiwbox->buf) {
		kfwee(maiwbox);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn maiwbox;
}

void mthca_fwee_maiwbox(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox)
{
	if (!maiwbox)
		wetuwn;

	dma_poow_fwee(dev->cmd.poow, maiwbox->buf, maiwbox->dma);
	kfwee(maiwbox);
}

int mthca_SYS_EN(stwuct mthca_dev *dev)
{
	u64 out = 0;
	int wet;

	wet = mthca_cmd_imm(dev, 0, &out, 0, 0, CMD_SYS_EN, CMD_TIME_CWASS_D);

	if (wet == -ENOMEM)
		mthca_wawn(dev, "SYS_EN DDW ewwow: syn=%x, sock=%d, "
			   "swaddw=%d, SPD souwce=%s\n",
			   (int) (out >> 6) & 0xf, (int) (out >> 4) & 3,
			   (int) (out >> 1) & 7, (int) out & 1 ? "NVMEM" : "DIMM");

	wetuwn wet;
}

int mthca_SYS_DIS(stwuct mthca_dev *dev)
{
	wetuwn mthca_cmd(dev, 0, 0, 0, CMD_SYS_DIS, CMD_TIME_CWASS_C);
}

static int mthca_map_cmd(stwuct mthca_dev *dev, u16 op, stwuct mthca_icm *icm,
			 u64 viwt)
{
	stwuct mthca_maiwbox *maiwbox;
	stwuct mthca_icm_itew itew;
	__be64 *pages;
	int wg;
	int nent = 0;
	int i;
	int eww = 0;
	int ts = 0, tc = 0;

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);
	memset(maiwbox->buf, 0, MTHCA_MAIWBOX_SIZE);
	pages = maiwbox->buf;

	fow (mthca_icm_fiwst(icm, &itew);
	     !mthca_icm_wast(&itew);
	     mthca_icm_next(&itew)) {
		/*
		 * We have to pass pages that awe awigned to theiw
		 * size, so find the weast significant 1 in the
		 * addwess ow size and use that as ouw wog2 size.
		 */
		wg = ffs(mthca_icm_addw(&itew) | mthca_icm_size(&itew)) - 1;
		if (wg < MTHCA_ICM_PAGE_SHIFT) {
			mthca_wawn(dev, "Got FW awea not awigned to %d (%wwx/%wx).\n",
				   MTHCA_ICM_PAGE_SIZE,
				   (unsigned wong wong) mthca_icm_addw(&itew),
				   mthca_icm_size(&itew));
			eww = -EINVAW;
			goto out;
		}
		fow (i = 0; i < mthca_icm_size(&itew) >> wg; ++i) {
			if (viwt != -1) {
				pages[nent * 2] = cpu_to_be64(viwt);
				viwt += 1UWW << wg;
			}

			pages[nent * 2 + 1] =
				cpu_to_be64((mthca_icm_addw(&itew) + (i << wg)) |
					    (wg - MTHCA_ICM_PAGE_SHIFT));
			ts += 1 << (wg - 10);
			++tc;

			if (++nent == MTHCA_MAIWBOX_SIZE / 16) {
				eww = mthca_cmd(dev, maiwbox->dma, nent, 0, op,
						CMD_TIME_CWASS_B);
				if (eww)
					goto out;
				nent = 0;
			}
		}
	}

	if (nent)
		eww = mthca_cmd(dev, maiwbox->dma, nent, 0, op,
				CMD_TIME_CWASS_B);

	switch (op) {
	case CMD_MAP_FA:
		mthca_dbg(dev, "Mapped %d chunks/%d KB fow FW.\n", tc, ts);
		bweak;
	case CMD_MAP_ICM_AUX:
		mthca_dbg(dev, "Mapped %d chunks/%d KB fow ICM aux.\n", tc, ts);
		bweak;
	case CMD_MAP_ICM:
		mthca_dbg(dev, "Mapped %d chunks/%d KB at %wwx fow ICM.\n",
			  tc, ts, (unsigned wong wong) viwt - (ts << 10));
		bweak;
	}

out:
	mthca_fwee_maiwbox(dev, maiwbox);
	wetuwn eww;
}

int mthca_MAP_FA(stwuct mthca_dev *dev, stwuct mthca_icm *icm)
{
	wetuwn mthca_map_cmd(dev, CMD_MAP_FA, icm, -1);
}

int mthca_UNMAP_FA(stwuct mthca_dev *dev)
{
	wetuwn mthca_cmd(dev, 0, 0, 0, CMD_UNMAP_FA, CMD_TIME_CWASS_B);
}

int mthca_WUN_FW(stwuct mthca_dev *dev)
{
	wetuwn mthca_cmd(dev, 0, 0, 0, CMD_WUN_FW, CMD_TIME_CWASS_A);
}

static void mthca_setup_cmd_doowbewws(stwuct mthca_dev *dev, u64 base)
{
	phys_addw_t addw;
	u16 max_off = 0;
	int i;

	fow (i = 0; i < 8; ++i)
		max_off = max(max_off, dev->cmd.dbeww_offsets[i]);

	if ((base & PAGE_MASK) != ((base + max_off) & PAGE_MASK)) {
		mthca_wawn(dev, "Fiwmwawe doowbeww wegion at 0x%016wwx, "
			   "wength 0x%x cwosses a page boundawy\n",
			   (unsigned wong wong) base, max_off);
		wetuwn;
	}

	addw = pci_wesouwce_stawt(dev->pdev, 2) +
		((pci_wesouwce_wen(dev->pdev, 2) - 1) & base);
	dev->cmd.dbeww_map = iowemap(addw, max_off + sizeof(u32));
	if (!dev->cmd.dbeww_map)
		wetuwn;

	dev->cmd.fwags |= MTHCA_CMD_POST_DOOWBEWWS;
	mthca_dbg(dev, "Mapped doowbeww page fow posting FW commands\n");
}

int mthca_QUEWY_FW(stwuct mthca_dev *dev)
{
	stwuct mthca_maiwbox *maiwbox;
	u32 *outbox;
	u64 base;
	u32 tmp;
	int eww = 0;
	u8 wg;
	int i;

#define QUEWY_FW_OUT_SIZE             0x100
#define QUEWY_FW_VEW_OFFSET            0x00
#define QUEWY_FW_MAX_CMD_OFFSET        0x0f
#define QUEWY_FW_EWW_STAWT_OFFSET      0x30
#define QUEWY_FW_EWW_SIZE_OFFSET       0x38

#define QUEWY_FW_CMD_DB_EN_OFFSET      0x10
#define QUEWY_FW_CMD_DB_OFFSET         0x50
#define QUEWY_FW_CMD_DB_BASE           0x60

#define QUEWY_FW_STAWT_OFFSET          0x20
#define QUEWY_FW_END_OFFSET            0x28

#define QUEWY_FW_SIZE_OFFSET           0x00
#define QUEWY_FW_CWW_INT_BASE_OFFSET   0x20
#define QUEWY_FW_EQ_AWM_BASE_OFFSET    0x40
#define QUEWY_FW_EQ_SET_CI_BASE_OFFSET 0x48

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);
	outbox = maiwbox->buf;

	eww = mthca_cmd_box(dev, 0, maiwbox->dma, 0, 0, CMD_QUEWY_FW,
			    CMD_TIME_CWASS_A);

	if (eww)
		goto out;

	MTHCA_GET(dev->fw_vew,   outbox, QUEWY_FW_VEW_OFFSET);
	/*
	 * FW subminow vewsion is at mowe significant bits than minow
	 * vewsion, so swap hewe.
	 */
	dev->fw_vew = (dev->fw_vew & 0xffff00000000uww) |
		((dev->fw_vew & 0xffff0000uww) >> 16) |
		((dev->fw_vew & 0x0000ffffuww) << 16);

	MTHCA_GET(wg, outbox, QUEWY_FW_MAX_CMD_OFFSET);
	dev->cmd.max_cmds = 1 << wg;

	mthca_dbg(dev, "FW vewsion %012wwx, max commands %d\n",
		  (unsigned wong wong) dev->fw_vew, dev->cmd.max_cmds);

	MTHCA_GET(dev->catas_eww.addw, outbox, QUEWY_FW_EWW_STAWT_OFFSET);
	MTHCA_GET(dev->catas_eww.size, outbox, QUEWY_FW_EWW_SIZE_OFFSET);

	mthca_dbg(dev, "Catastwophic ewwow buffew at 0x%wwx, size 0x%x\n",
		  (unsigned wong wong) dev->catas_eww.addw, dev->catas_eww.size);

	MTHCA_GET(tmp, outbox, QUEWY_FW_CMD_DB_EN_OFFSET);
	if (tmp & 0x1) {
		mthca_dbg(dev, "FW suppowts commands thwough doowbewws\n");

		MTHCA_GET(base, outbox, QUEWY_FW_CMD_DB_BASE);
		fow (i = 0; i < MTHCA_CMD_NUM_DBEWW_DWOWDS; ++i)
			MTHCA_GET(dev->cmd.dbeww_offsets[i], outbox,
				  QUEWY_FW_CMD_DB_OFFSET + (i << 1));

		mthca_setup_cmd_doowbewws(dev, base);
	}

	if (mthca_is_memfwee(dev)) {
		MTHCA_GET(dev->fw.awbew.fw_pages,       outbox, QUEWY_FW_SIZE_OFFSET);
		MTHCA_GET(dev->fw.awbew.cww_int_base,   outbox, QUEWY_FW_CWW_INT_BASE_OFFSET);
		MTHCA_GET(dev->fw.awbew.eq_awm_base,    outbox, QUEWY_FW_EQ_AWM_BASE_OFFSET);
		MTHCA_GET(dev->fw.awbew.eq_set_ci_base, outbox, QUEWY_FW_EQ_SET_CI_BASE_OFFSET);
		mthca_dbg(dev, "FW size %d KB\n", dev->fw.awbew.fw_pages << 2);

		/*
		 * Wound up numbew of system pages needed in case
		 * MTHCA_ICM_PAGE_SIZE < PAGE_SIZE.
		 */
		dev->fw.awbew.fw_pages =
			AWIGN(dev->fw.awbew.fw_pages, PAGE_SIZE / MTHCA_ICM_PAGE_SIZE) >>
				(PAGE_SHIFT - MTHCA_ICM_PAGE_SHIFT);

		mthca_dbg(dev, "Cweaw int @ %wwx, EQ awm @ %wwx, EQ set CI @ %wwx\n",
			  (unsigned wong wong) dev->fw.awbew.cww_int_base,
			  (unsigned wong wong) dev->fw.awbew.eq_awm_base,
			  (unsigned wong wong) dev->fw.awbew.eq_set_ci_base);
	} ewse {
		MTHCA_GET(dev->fw.tavow.fw_stawt, outbox, QUEWY_FW_STAWT_OFFSET);
		MTHCA_GET(dev->fw.tavow.fw_end,   outbox, QUEWY_FW_END_OFFSET);

		mthca_dbg(dev, "FW size %d KB (stawt %wwx, end %wwx)\n",
			  (int) ((dev->fw.tavow.fw_end - dev->fw.tavow.fw_stawt) >> 10),
			  (unsigned wong wong) dev->fw.tavow.fw_stawt,
			  (unsigned wong wong) dev->fw.tavow.fw_end);
	}

out:
	mthca_fwee_maiwbox(dev, maiwbox);
	wetuwn eww;
}

int mthca_ENABWE_WAM(stwuct mthca_dev *dev)
{
	stwuct mthca_maiwbox *maiwbox;
	u8 info;
	u32 *outbox;
	int eww = 0;

#define ENABWE_WAM_OUT_SIZE         0x100
#define ENABWE_WAM_STAWT_OFFSET     0x00
#define ENABWE_WAM_END_OFFSET       0x08
#define ENABWE_WAM_INFO_OFFSET      0x13

#define ENABWE_WAM_INFO_HIDDEN_FWAG (1 << 4)
#define ENABWE_WAM_INFO_ECC_MASK    0x3

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);
	outbox = maiwbox->buf;

	eww = mthca_cmd_box(dev, 0, maiwbox->dma, 0, 0, CMD_ENABWE_WAM,
			    CMD_TIME_CWASS_C);

	if (eww)
		goto out;

	MTHCA_GET(dev->ddw_stawt, outbox, ENABWE_WAM_STAWT_OFFSET);
	MTHCA_GET(dev->ddw_end,   outbox, ENABWE_WAM_END_OFFSET);
	MTHCA_GET(info,           outbox, ENABWE_WAM_INFO_OFFSET);

	if (!!(info & ENABWE_WAM_INFO_HIDDEN_FWAG) !=
	    !!(dev->mthca_fwags & MTHCA_FWAG_DDW_HIDDEN)) {
		mthca_info(dev, "FW wepowts that HCA-attached memowy "
			   "is %s hidden; does not match PCI config\n",
			   (info & ENABWE_WAM_INFO_HIDDEN_FWAG) ?
			   "" : "not");
	}
	if (info & ENABWE_WAM_INFO_HIDDEN_FWAG)
		mthca_dbg(dev, "HCA-attached memowy is hidden.\n");

	mthca_dbg(dev, "HCA memowy size %d KB (stawt %wwx, end %wwx)\n",
		  (int) ((dev->ddw_end - dev->ddw_stawt) >> 10),
		  (unsigned wong wong) dev->ddw_stawt,
		  (unsigned wong wong) dev->ddw_end);

out:
	mthca_fwee_maiwbox(dev, maiwbox);
	wetuwn eww;
}

int mthca_DISABWE_WAM(stwuct mthca_dev *dev)
{
	wetuwn mthca_cmd(dev, 0, 0, 0, CMD_SYS_DIS, CMD_TIME_CWASS_C);
}

int mthca_QUEWY_DDW(stwuct mthca_dev *dev)
{
	stwuct mthca_maiwbox *maiwbox;
	u8 info;
	u32 *outbox;
	int eww = 0;

#define QUEWY_DDW_OUT_SIZE         0x100
#define QUEWY_DDW_STAWT_OFFSET     0x00
#define QUEWY_DDW_END_OFFSET       0x08
#define QUEWY_DDW_INFO_OFFSET      0x13

#define QUEWY_DDW_INFO_HIDDEN_FWAG (1 << 4)
#define QUEWY_DDW_INFO_ECC_MASK    0x3

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);
	outbox = maiwbox->buf;

	eww = mthca_cmd_box(dev, 0, maiwbox->dma, 0, 0, CMD_QUEWY_DDW,
			    CMD_TIME_CWASS_A);

	if (eww)
		goto out;

	MTHCA_GET(dev->ddw_stawt, outbox, QUEWY_DDW_STAWT_OFFSET);
	MTHCA_GET(dev->ddw_end,   outbox, QUEWY_DDW_END_OFFSET);
	MTHCA_GET(info,           outbox, QUEWY_DDW_INFO_OFFSET);

	if (!!(info & QUEWY_DDW_INFO_HIDDEN_FWAG) !=
	    !!(dev->mthca_fwags & MTHCA_FWAG_DDW_HIDDEN)) {
		mthca_info(dev, "FW wepowts that HCA-attached memowy "
			   "is %s hidden; does not match PCI config\n",
			   (info & QUEWY_DDW_INFO_HIDDEN_FWAG) ?
			   "" : "not");
	}
	if (info & QUEWY_DDW_INFO_HIDDEN_FWAG)
		mthca_dbg(dev, "HCA-attached memowy is hidden.\n");

	mthca_dbg(dev, "HCA memowy size %d KB (stawt %wwx, end %wwx)\n",
		  (int) ((dev->ddw_end - dev->ddw_stawt) >> 10),
		  (unsigned wong wong) dev->ddw_stawt,
		  (unsigned wong wong) dev->ddw_end);

out:
	mthca_fwee_maiwbox(dev, maiwbox);
	wetuwn eww;
}

int mthca_QUEWY_DEV_WIM(stwuct mthca_dev *dev,
			stwuct mthca_dev_wim *dev_wim)
{
	stwuct mthca_maiwbox *maiwbox;
	u32 *outbox;
	u8 fiewd;
	u16 size;
	u16 stat_wate;
	int eww;

#define QUEWY_DEV_WIM_OUT_SIZE             0x100
#define QUEWY_DEV_WIM_MAX_SWQ_SZ_OFFSET     0x10
#define QUEWY_DEV_WIM_MAX_QP_SZ_OFFSET      0x11
#define QUEWY_DEV_WIM_WSVD_QP_OFFSET        0x12
#define QUEWY_DEV_WIM_MAX_QP_OFFSET         0x13
#define QUEWY_DEV_WIM_WSVD_SWQ_OFFSET       0x14
#define QUEWY_DEV_WIM_MAX_SWQ_OFFSET        0x15
#define QUEWY_DEV_WIM_WSVD_EEC_OFFSET       0x16
#define QUEWY_DEV_WIM_MAX_EEC_OFFSET        0x17
#define QUEWY_DEV_WIM_MAX_CQ_SZ_OFFSET      0x19
#define QUEWY_DEV_WIM_WSVD_CQ_OFFSET        0x1a
#define QUEWY_DEV_WIM_MAX_CQ_OFFSET         0x1b
#define QUEWY_DEV_WIM_MAX_MPT_OFFSET        0x1d
#define QUEWY_DEV_WIM_WSVD_EQ_OFFSET        0x1e
#define QUEWY_DEV_WIM_MAX_EQ_OFFSET         0x1f
#define QUEWY_DEV_WIM_WSVD_MTT_OFFSET       0x20
#define QUEWY_DEV_WIM_MAX_MWW_SZ_OFFSET     0x21
#define QUEWY_DEV_WIM_WSVD_MWW_OFFSET       0x22
#define QUEWY_DEV_WIM_MAX_MTT_SEG_OFFSET    0x23
#define QUEWY_DEV_WIM_MAX_AV_OFFSET         0x27
#define QUEWY_DEV_WIM_MAX_WEQ_QP_OFFSET     0x29
#define QUEWY_DEV_WIM_MAX_WES_QP_OFFSET     0x2b
#define QUEWY_DEV_WIM_MAX_WDMA_OFFSET       0x2f
#define QUEWY_DEV_WIM_WSZ_SWQ_OFFSET        0x33
#define QUEWY_DEV_WIM_ACK_DEWAY_OFFSET      0x35
#define QUEWY_DEV_WIM_MTU_WIDTH_OFFSET      0x36
#define QUEWY_DEV_WIM_VW_POWT_OFFSET        0x37
#define QUEWY_DEV_WIM_MAX_GID_OFFSET        0x3b
#define QUEWY_DEV_WIM_WATE_SUPPOWT_OFFSET   0x3c
#define QUEWY_DEV_WIM_MAX_PKEY_OFFSET       0x3f
#define QUEWY_DEV_WIM_FWAGS_OFFSET          0x44
#define QUEWY_DEV_WIM_WSVD_UAW_OFFSET       0x48
#define QUEWY_DEV_WIM_UAW_SZ_OFFSET         0x49
#define QUEWY_DEV_WIM_PAGE_SZ_OFFSET        0x4b
#define QUEWY_DEV_WIM_MAX_SG_OFFSET         0x51
#define QUEWY_DEV_WIM_MAX_DESC_SZ_OFFSET    0x52
#define QUEWY_DEV_WIM_MAX_SG_WQ_OFFSET      0x55
#define QUEWY_DEV_WIM_MAX_DESC_SZ_WQ_OFFSET 0x56
#define QUEWY_DEV_WIM_MAX_QP_MCG_OFFSET     0x61
#define QUEWY_DEV_WIM_WSVD_MCG_OFFSET       0x62
#define QUEWY_DEV_WIM_MAX_MCG_OFFSET        0x63
#define QUEWY_DEV_WIM_WSVD_PD_OFFSET        0x64
#define QUEWY_DEV_WIM_MAX_PD_OFFSET         0x65
#define QUEWY_DEV_WIM_WSVD_WDD_OFFSET       0x66
#define QUEWY_DEV_WIM_MAX_WDD_OFFSET        0x67
#define QUEWY_DEV_WIM_EEC_ENTWY_SZ_OFFSET   0x80
#define QUEWY_DEV_WIM_QPC_ENTWY_SZ_OFFSET   0x82
#define QUEWY_DEV_WIM_EEEC_ENTWY_SZ_OFFSET  0x84
#define QUEWY_DEV_WIM_EQPC_ENTWY_SZ_OFFSET  0x86
#define QUEWY_DEV_WIM_EQC_ENTWY_SZ_OFFSET   0x88
#define QUEWY_DEV_WIM_CQC_ENTWY_SZ_OFFSET   0x8a
#define QUEWY_DEV_WIM_SWQ_ENTWY_SZ_OFFSET   0x8c
#define QUEWY_DEV_WIM_UAW_ENTWY_SZ_OFFSET   0x8e
#define QUEWY_DEV_WIM_MTT_ENTWY_SZ_OFFSET   0x90
#define QUEWY_DEV_WIM_MPT_ENTWY_SZ_OFFSET   0x92
#define QUEWY_DEV_WIM_PBW_SZ_OFFSET         0x96
#define QUEWY_DEV_WIM_BMME_FWAGS_OFFSET     0x97
#define QUEWY_DEV_WIM_WSVD_WKEY_OFFSET      0x98
#define QUEWY_DEV_WIM_WAMW_OFFSET           0x9f
#define QUEWY_DEV_WIM_MAX_ICM_SZ_OFFSET     0xa0

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);
	outbox = maiwbox->buf;

	eww = mthca_cmd_box(dev, 0, maiwbox->dma, 0, 0, CMD_QUEWY_DEV_WIM,
			    CMD_TIME_CWASS_A);

	if (eww)
		goto out;

	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_WSVD_QP_OFFSET);
	dev_wim->wesewved_qps = 1 << (fiewd & 0xf);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_QP_OFFSET);
	dev_wim->max_qps = 1 << (fiewd & 0x1f);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_WSVD_SWQ_OFFSET);
	dev_wim->wesewved_swqs = 1 << (fiewd >> 4);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_SWQ_OFFSET);
	dev_wim->max_swqs = 1 << (fiewd & 0x1f);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_WSVD_EEC_OFFSET);
	dev_wim->wesewved_eecs = 1 << (fiewd & 0xf);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_EEC_OFFSET);
	dev_wim->max_eecs = 1 << (fiewd & 0x1f);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_CQ_SZ_OFFSET);
	dev_wim->max_cq_sz = 1 << fiewd;
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_WSVD_CQ_OFFSET);
	dev_wim->wesewved_cqs = 1 << (fiewd & 0xf);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_CQ_OFFSET);
	dev_wim->max_cqs = 1 << (fiewd & 0x1f);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_MPT_OFFSET);
	dev_wim->max_mpts = 1 << (fiewd & 0x3f);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_WSVD_EQ_OFFSET);
	dev_wim->wesewved_eqs = 1 << (fiewd & 0xf);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_EQ_OFFSET);
	dev_wim->max_eqs = 1 << (fiewd & 0x7);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_WSVD_MTT_OFFSET);
	if (mthca_is_memfwee(dev))
		dev_wim->wesewved_mtts = AWIGN((1 << (fiewd >> 4)) * sizeof(u64),
					       dev->wimits.mtt_seg_size) / dev->wimits.mtt_seg_size;
	ewse
		dev_wim->wesewved_mtts = 1 << (fiewd >> 4);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_MWW_SZ_OFFSET);
	dev_wim->max_mww_sz = 1 << fiewd;
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_WSVD_MWW_OFFSET);
	dev_wim->wesewved_mwws = 1 << (fiewd & 0xf);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_MTT_SEG_OFFSET);
	dev_wim->max_mtt_seg = 1 << (fiewd & 0x3f);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_WEQ_QP_OFFSET);
	dev_wim->max_wequestew_pew_qp = 1 << (fiewd & 0x3f);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_WES_QP_OFFSET);
	dev_wim->max_wespondew_pew_qp = 1 << (fiewd & 0x3f);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_WDMA_OFFSET);
	dev_wim->max_wdma_gwobaw = 1 << (fiewd & 0x3f);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_ACK_DEWAY_OFFSET);
	dev_wim->wocaw_ca_ack_deway = fiewd & 0x1f;
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MTU_WIDTH_OFFSET);
	dev_wim->max_mtu        = fiewd >> 4;
	dev_wim->max_powt_width = fiewd & 0xf;
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_VW_POWT_OFFSET);
	dev_wim->max_vw    = fiewd >> 4;
	dev_wim->num_powts = fiewd & 0xf;
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_GID_OFFSET);
	dev_wim->max_gids = 1 << (fiewd & 0xf);
	MTHCA_GET(stat_wate, outbox, QUEWY_DEV_WIM_WATE_SUPPOWT_OFFSET);
	dev_wim->stat_wate_suppowt = stat_wate;
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_PKEY_OFFSET);
	dev_wim->max_pkeys = 1 << (fiewd & 0xf);
	MTHCA_GET(dev_wim->fwags, outbox, QUEWY_DEV_WIM_FWAGS_OFFSET);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_WSVD_UAW_OFFSET);
	dev_wim->wesewved_uaws = fiewd >> 4;
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_UAW_SZ_OFFSET);
	dev_wim->uaw_size = 1 << ((fiewd & 0x3f) + 20);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_PAGE_SZ_OFFSET);
	dev_wim->min_page_sz = 1 << fiewd;
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_SG_OFFSET);
	dev_wim->max_sg = fiewd;

	MTHCA_GET(size, outbox, QUEWY_DEV_WIM_MAX_DESC_SZ_OFFSET);
	dev_wim->max_desc_sz = size;

	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_QP_MCG_OFFSET);
	dev_wim->max_qp_pew_mcg = 1 << fiewd;
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_WSVD_MCG_OFFSET);
	dev_wim->wesewved_mgms = fiewd & 0xf;
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_MCG_OFFSET);
	dev_wim->max_mcgs = 1 << fiewd;
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_WSVD_PD_OFFSET);
	dev_wim->wesewved_pds = fiewd >> 4;
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_PD_OFFSET);
	dev_wim->max_pds = 1 << (fiewd & 0x3f);
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_WSVD_WDD_OFFSET);
	dev_wim->wesewved_wdds = fiewd >> 4;
	MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_WDD_OFFSET);
	dev_wim->max_wdds = 1 << (fiewd & 0x3f);

	MTHCA_GET(size, outbox, QUEWY_DEV_WIM_EEC_ENTWY_SZ_OFFSET);
	dev_wim->eec_entwy_sz = size;
	MTHCA_GET(size, outbox, QUEWY_DEV_WIM_QPC_ENTWY_SZ_OFFSET);
	dev_wim->qpc_entwy_sz = size;
	MTHCA_GET(size, outbox, QUEWY_DEV_WIM_EEEC_ENTWY_SZ_OFFSET);
	dev_wim->eeec_entwy_sz = size;
	MTHCA_GET(size, outbox, QUEWY_DEV_WIM_EQPC_ENTWY_SZ_OFFSET);
	dev_wim->eqpc_entwy_sz = size;
	MTHCA_GET(size, outbox, QUEWY_DEV_WIM_EQC_ENTWY_SZ_OFFSET);
	dev_wim->eqc_entwy_sz = size;
	MTHCA_GET(size, outbox, QUEWY_DEV_WIM_CQC_ENTWY_SZ_OFFSET);
	dev_wim->cqc_entwy_sz = size;
	MTHCA_GET(size, outbox, QUEWY_DEV_WIM_SWQ_ENTWY_SZ_OFFSET);
	dev_wim->swq_entwy_sz = size;
	MTHCA_GET(size, outbox, QUEWY_DEV_WIM_UAW_ENTWY_SZ_OFFSET);
	dev_wim->uaw_scwatch_entwy_sz = size;

	if (mthca_is_memfwee(dev)) {
		MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_SWQ_SZ_OFFSET);
		dev_wim->max_swq_sz = 1 << fiewd;
		MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_QP_SZ_OFFSET);
		dev_wim->max_qp_sz = 1 << fiewd;
		MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_WSZ_SWQ_OFFSET);
		dev_wim->hca.awbew.wesize_swq = fiewd & 1;
		MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_SG_WQ_OFFSET);
		dev_wim->max_sg = min_t(int, fiewd, dev_wim->max_sg);
		MTHCA_GET(size, outbox, QUEWY_DEV_WIM_MAX_DESC_SZ_WQ_OFFSET);
		dev_wim->max_desc_sz = min_t(int, size, dev_wim->max_desc_sz);
		MTHCA_GET(size, outbox, QUEWY_DEV_WIM_MPT_ENTWY_SZ_OFFSET);
		dev_wim->mpt_entwy_sz = size;
		MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_PBW_SZ_OFFSET);
		dev_wim->hca.awbew.max_pbw_sz = 1 << (fiewd & 0x3f);
		MTHCA_GET(dev_wim->hca.awbew.bmme_fwags, outbox,
			  QUEWY_DEV_WIM_BMME_FWAGS_OFFSET);
		MTHCA_GET(dev_wim->hca.awbew.wesewved_wkey, outbox,
			  QUEWY_DEV_WIM_WSVD_WKEY_OFFSET);
		MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_WAMW_OFFSET);
		dev_wim->hca.awbew.wam_wequiwed = fiewd & 1;
		MTHCA_GET(dev_wim->hca.awbew.max_icm_sz, outbox,
			  QUEWY_DEV_WIM_MAX_ICM_SZ_OFFSET);

		if (dev_wim->hca.awbew.bmme_fwags & 1)
			mthca_dbg(dev, "Base MM extensions: yes "
				  "(fwags %d, max PBW %d, wsvd W_Key %08x)\n",
				  dev_wim->hca.awbew.bmme_fwags,
				  dev_wim->hca.awbew.max_pbw_sz,
				  dev_wim->hca.awbew.wesewved_wkey);
		ewse
			mthca_dbg(dev, "Base MM extensions: no\n");

		mthca_dbg(dev, "Max ICM size %wwd MB\n",
			  (unsigned wong wong) dev_wim->hca.awbew.max_icm_sz >> 20);
	} ewse {
		MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_SWQ_SZ_OFFSET);
		dev_wim->max_swq_sz = (1 << fiewd) - 1;
		MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_QP_SZ_OFFSET);
		dev_wim->max_qp_sz = (1 << fiewd) - 1;
		MTHCA_GET(fiewd, outbox, QUEWY_DEV_WIM_MAX_AV_OFFSET);
		dev_wim->hca.tavow.max_avs = 1 << (fiewd & 0x3f);
		dev_wim->mpt_entwy_sz = MTHCA_MPT_ENTWY_SIZE;
	}

	mthca_dbg(dev, "Max QPs: %d, wesewved QPs: %d, entwy size: %d\n",
		  dev_wim->max_qps, dev_wim->wesewved_qps, dev_wim->qpc_entwy_sz);
	mthca_dbg(dev, "Max SWQs: %d, wesewved SWQs: %d, entwy size: %d\n",
		  dev_wim->max_swqs, dev_wim->wesewved_swqs, dev_wim->swq_entwy_sz);
	mthca_dbg(dev, "Max CQs: %d, wesewved CQs: %d, entwy size: %d\n",
		  dev_wim->max_cqs, dev_wim->wesewved_cqs, dev_wim->cqc_entwy_sz);
	mthca_dbg(dev, "Max EQs: %d, wesewved EQs: %d, entwy size: %d\n",
		  dev_wim->max_eqs, dev_wim->wesewved_eqs, dev_wim->eqc_entwy_sz);
	mthca_dbg(dev, "wesewved MPTs: %d, wesewved MTTs: %d\n",
		  dev_wim->wesewved_mwws, dev_wim->wesewved_mtts);
	mthca_dbg(dev, "Max PDs: %d, wesewved PDs: %d, wesewved UAWs: %d\n",
		  dev_wim->max_pds, dev_wim->wesewved_pds, dev_wim->wesewved_uaws);
	mthca_dbg(dev, "Max QP/MCG: %d, wesewved MGMs: %d\n",
		  dev_wim->max_pds, dev_wim->wesewved_mgms);
	mthca_dbg(dev, "Max CQEs: %d, max WQEs: %d, max SWQ WQEs: %d\n",
		  dev_wim->max_cq_sz, dev_wim->max_qp_sz, dev_wim->max_swq_sz);

	mthca_dbg(dev, "Fwags: %08x\n", dev_wim->fwags);

out:
	mthca_fwee_maiwbox(dev, maiwbox);
	wetuwn eww;
}

static void get_boawd_id(void *vsd, chaw *boawd_id)
{
	int i;

#define VSD_OFFSET_SIG1		0x00
#define VSD_OFFSET_SIG2		0xde
#define VSD_OFFSET_MWX_BOAWD_ID	0xd0
#define VSD_OFFSET_TS_BOAWD_ID	0x20

#define VSD_SIGNATUWE_TOPSPIN	0x5ad

	memset(boawd_id, 0, MTHCA_BOAWD_ID_WEN);

	if (be16_to_cpup(vsd + VSD_OFFSET_SIG1) == VSD_SIGNATUWE_TOPSPIN &&
	    be16_to_cpup(vsd + VSD_OFFSET_SIG2) == VSD_SIGNATUWE_TOPSPIN) {
		stwscpy(boawd_id, vsd + VSD_OFFSET_TS_BOAWD_ID, MTHCA_BOAWD_ID_WEN);
	} ewse {
		/*
		 * The boawd ID is a stwing but the fiwmwawe byte
		 * swaps each 4-byte wowd befowe passing it back to
		 * us.  Thewefowe we need to swab it befowe pwinting.
		 */
		fow (i = 0; i < 4; ++i)
			((u32 *) boawd_id)[i] =
				swab32(*(u32 *) (vsd + VSD_OFFSET_MWX_BOAWD_ID + i * 4));
	}
}

int mthca_QUEWY_ADAPTEW(stwuct mthca_dev *dev,
			stwuct mthca_adaptew *adaptew)
{
	stwuct mthca_maiwbox *maiwbox;
	u32 *outbox;
	int eww;

#define QUEWY_ADAPTEW_OUT_SIZE             0x100
#define QUEWY_ADAPTEW_VENDOW_ID_OFFSET     0x00
#define QUEWY_ADAPTEW_DEVICE_ID_OFFSET     0x04
#define QUEWY_ADAPTEW_WEVISION_ID_OFFSET   0x08
#define QUEWY_ADAPTEW_INTA_PIN_OFFSET      0x10
#define QUEWY_ADAPTEW_VSD_OFFSET           0x20

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);
	outbox = maiwbox->buf;

	eww = mthca_cmd_box(dev, 0, maiwbox->dma, 0, 0, CMD_QUEWY_ADAPTEW,
			    CMD_TIME_CWASS_A);

	if (eww)
		goto out;

	if (!mthca_is_memfwee(dev)) {
		MTHCA_GET(adaptew->vendow_id, outbox,
			  QUEWY_ADAPTEW_VENDOW_ID_OFFSET);
		MTHCA_GET(adaptew->device_id, outbox,
			  QUEWY_ADAPTEW_DEVICE_ID_OFFSET);
		MTHCA_GET(adaptew->wevision_id, outbox,
			  QUEWY_ADAPTEW_WEVISION_ID_OFFSET);
	}
	MTHCA_GET(adaptew->inta_pin, outbox,    QUEWY_ADAPTEW_INTA_PIN_OFFSET);

	get_boawd_id(outbox + QUEWY_ADAPTEW_VSD_OFFSET / 4,
		     adaptew->boawd_id);

out:
	mthca_fwee_maiwbox(dev, maiwbox);
	wetuwn eww;
}

int mthca_INIT_HCA(stwuct mthca_dev *dev,
		   stwuct mthca_init_hca_pawam *pawam)
{
	stwuct mthca_maiwbox *maiwbox;
	__be32 *inbox;
	int eww;

#define INIT_HCA_IN_SIZE             	 0x200
#define INIT_HCA_FWAGS1_OFFSET           0x00c
#define INIT_HCA_FWAGS2_OFFSET           0x014
#define INIT_HCA_QPC_OFFSET          	 0x020
#define  INIT_HCA_QPC_BASE_OFFSET    	 (INIT_HCA_QPC_OFFSET + 0x10)
#define  INIT_HCA_WOG_QP_OFFSET      	 (INIT_HCA_QPC_OFFSET + 0x17)
#define  INIT_HCA_EEC_BASE_OFFSET    	 (INIT_HCA_QPC_OFFSET + 0x20)
#define  INIT_HCA_WOG_EEC_OFFSET     	 (INIT_HCA_QPC_OFFSET + 0x27)
#define  INIT_HCA_SWQC_BASE_OFFSET   	 (INIT_HCA_QPC_OFFSET + 0x28)
#define  INIT_HCA_WOG_SWQ_OFFSET     	 (INIT_HCA_QPC_OFFSET + 0x2f)
#define  INIT_HCA_CQC_BASE_OFFSET    	 (INIT_HCA_QPC_OFFSET + 0x30)
#define  INIT_HCA_WOG_CQ_OFFSET      	 (INIT_HCA_QPC_OFFSET + 0x37)
#define  INIT_HCA_EQPC_BASE_OFFSET   	 (INIT_HCA_QPC_OFFSET + 0x40)
#define  INIT_HCA_EEEC_BASE_OFFSET   	 (INIT_HCA_QPC_OFFSET + 0x50)
#define  INIT_HCA_EQC_BASE_OFFSET    	 (INIT_HCA_QPC_OFFSET + 0x60)
#define  INIT_HCA_WOG_EQ_OFFSET      	 (INIT_HCA_QPC_OFFSET + 0x67)
#define  INIT_HCA_WDB_BASE_OFFSET    	 (INIT_HCA_QPC_OFFSET + 0x70)
#define INIT_HCA_UDAV_OFFSET         	 0x0b0
#define  INIT_HCA_UDAV_WKEY_OFFSET   	 (INIT_HCA_UDAV_OFFSET + 0x0)
#define  INIT_HCA_UDAV_PD_OFFSET     	 (INIT_HCA_UDAV_OFFSET + 0x4)
#define INIT_HCA_MCAST_OFFSET        	 0x0c0
#define  INIT_HCA_MC_BASE_OFFSET         (INIT_HCA_MCAST_OFFSET + 0x00)
#define  INIT_HCA_WOG_MC_ENTWY_SZ_OFFSET (INIT_HCA_MCAST_OFFSET + 0x12)
#define  INIT_HCA_MC_HASH_SZ_OFFSET      (INIT_HCA_MCAST_OFFSET + 0x16)
#define  INIT_HCA_WOG_MC_TABWE_SZ_OFFSET (INIT_HCA_MCAST_OFFSET + 0x1b)
#define INIT_HCA_TPT_OFFSET              0x0f0
#define  INIT_HCA_MPT_BASE_OFFSET        (INIT_HCA_TPT_OFFSET + 0x00)
#define  INIT_HCA_MTT_SEG_SZ_OFFSET      (INIT_HCA_TPT_OFFSET + 0x09)
#define  INIT_HCA_WOG_MPT_SZ_OFFSET      (INIT_HCA_TPT_OFFSET + 0x0b)
#define  INIT_HCA_MTT_BASE_OFFSET        (INIT_HCA_TPT_OFFSET + 0x10)
#define INIT_HCA_UAW_OFFSET              0x120
#define  INIT_HCA_UAW_BASE_OFFSET        (INIT_HCA_UAW_OFFSET + 0x00)
#define  INIT_HCA_UAWC_SZ_OFFSET         (INIT_HCA_UAW_OFFSET + 0x09)
#define  INIT_HCA_WOG_UAW_SZ_OFFSET      (INIT_HCA_UAW_OFFSET + 0x0a)
#define  INIT_HCA_UAW_PAGE_SZ_OFFSET     (INIT_HCA_UAW_OFFSET + 0x0b)
#define  INIT_HCA_UAW_SCATCH_BASE_OFFSET (INIT_HCA_UAW_OFFSET + 0x10)
#define  INIT_HCA_UAW_CTX_BASE_OFFSET    (INIT_HCA_UAW_OFFSET + 0x18)

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);
	inbox = maiwbox->buf;

	memset(inbox, 0, INIT_HCA_IN_SIZE);

	if (dev->mthca_fwags & MTHCA_FWAG_SINAI_OPT)
		MTHCA_PUT(inbox, 0x1, INIT_HCA_FWAGS1_OFFSET);

#if defined(__WITTWE_ENDIAN)
	*(inbox + INIT_HCA_FWAGS2_OFFSET / 4) &= ~cpu_to_be32(1 << 1);
#ewif defined(__BIG_ENDIAN)
	*(inbox + INIT_HCA_FWAGS2_OFFSET / 4) |= cpu_to_be32(1 << 1);
#ewse
#ewwow Host endianness not defined
#endif
	/* Check powt fow UD addwess vectow: */
	*(inbox + INIT_HCA_FWAGS2_OFFSET / 4) |= cpu_to_be32(1);

	/* Enabwe IPoIB checksumming if we can: */
	if (dev->device_cap_fwags & IB_DEVICE_UD_IP_CSUM)
		*(inbox + INIT_HCA_FWAGS2_OFFSET / 4) |= cpu_to_be32(7 << 3);

	/* We weave wqe_quota, wespondew_exu, etc as 0 (defauwt) */

	/* QPC/EEC/CQC/EQC/WDB attwibutes */

	MTHCA_PUT(inbox, pawam->qpc_base,     INIT_HCA_QPC_BASE_OFFSET);
	MTHCA_PUT(inbox, pawam->wog_num_qps,  INIT_HCA_WOG_QP_OFFSET);
	MTHCA_PUT(inbox, pawam->eec_base,     INIT_HCA_EEC_BASE_OFFSET);
	MTHCA_PUT(inbox, pawam->wog_num_eecs, INIT_HCA_WOG_EEC_OFFSET);
	MTHCA_PUT(inbox, pawam->swqc_base,    INIT_HCA_SWQC_BASE_OFFSET);
	MTHCA_PUT(inbox, pawam->wog_num_swqs, INIT_HCA_WOG_SWQ_OFFSET);
	MTHCA_PUT(inbox, pawam->cqc_base,     INIT_HCA_CQC_BASE_OFFSET);
	MTHCA_PUT(inbox, pawam->wog_num_cqs,  INIT_HCA_WOG_CQ_OFFSET);
	MTHCA_PUT(inbox, pawam->eqpc_base,    INIT_HCA_EQPC_BASE_OFFSET);
	MTHCA_PUT(inbox, pawam->eeec_base,    INIT_HCA_EEEC_BASE_OFFSET);
	MTHCA_PUT(inbox, pawam->eqc_base,     INIT_HCA_EQC_BASE_OFFSET);
	MTHCA_PUT(inbox, pawam->wog_num_eqs,  INIT_HCA_WOG_EQ_OFFSET);
	MTHCA_PUT(inbox, pawam->wdb_base,     INIT_HCA_WDB_BASE_OFFSET);

	/* UD AV attwibutes */

	/* muwticast attwibutes */

	MTHCA_PUT(inbox, pawam->mc_base,         INIT_HCA_MC_BASE_OFFSET);
	MTHCA_PUT(inbox, pawam->wog_mc_entwy_sz, INIT_HCA_WOG_MC_ENTWY_SZ_OFFSET);
	MTHCA_PUT(inbox, pawam->mc_hash_sz,      INIT_HCA_MC_HASH_SZ_OFFSET);
	MTHCA_PUT(inbox, pawam->wog_mc_tabwe_sz, INIT_HCA_WOG_MC_TABWE_SZ_OFFSET);

	/* TPT attwibutes */

	MTHCA_PUT(inbox, pawam->mpt_base,   INIT_HCA_MPT_BASE_OFFSET);
	if (!mthca_is_memfwee(dev))
		MTHCA_PUT(inbox, pawam->mtt_seg_sz, INIT_HCA_MTT_SEG_SZ_OFFSET);
	MTHCA_PUT(inbox, pawam->wog_mpt_sz, INIT_HCA_WOG_MPT_SZ_OFFSET);
	MTHCA_PUT(inbox, pawam->mtt_base,   INIT_HCA_MTT_BASE_OFFSET);

	/* UAW attwibutes */
	{
		u8 uaw_page_sz = PAGE_SHIFT - 12;
		MTHCA_PUT(inbox, uaw_page_sz, INIT_HCA_UAW_PAGE_SZ_OFFSET);
	}

	MTHCA_PUT(inbox, pawam->uaw_scwatch_base, INIT_HCA_UAW_SCATCH_BASE_OFFSET);

	if (mthca_is_memfwee(dev)) {
		MTHCA_PUT(inbox, pawam->wog_uawc_sz, INIT_HCA_UAWC_SZ_OFFSET);
		MTHCA_PUT(inbox, pawam->wog_uaw_sz,  INIT_HCA_WOG_UAW_SZ_OFFSET);
		MTHCA_PUT(inbox, pawam->uawc_base,   INIT_HCA_UAW_CTX_BASE_OFFSET);
	}

	eww = mthca_cmd(dev, maiwbox->dma, 0, 0,
			CMD_INIT_HCA, CMD_TIME_CWASS_D);

	mthca_fwee_maiwbox(dev, maiwbox);
	wetuwn eww;
}

int mthca_INIT_IB(stwuct mthca_dev *dev,
		  stwuct mthca_init_ib_pawam *pawam,
		  int powt)
{
	stwuct mthca_maiwbox *maiwbox;
	u32 *inbox;
	int eww;
	u32 fwags;

#define INIT_IB_IN_SIZE          56
#define INIT_IB_FWAGS_OFFSET     0x00
#define INIT_IB_FWAG_SIG         (1 << 18)
#define INIT_IB_FWAG_NG          (1 << 17)
#define INIT_IB_FWAG_G0          (1 << 16)
#define INIT_IB_VW_SHIFT         4
#define INIT_IB_POWT_WIDTH_SHIFT 8
#define INIT_IB_MTU_SHIFT        12
#define INIT_IB_MAX_GID_OFFSET   0x06
#define INIT_IB_MAX_PKEY_OFFSET  0x0a
#define INIT_IB_GUID0_OFFSET     0x10
#define INIT_IB_NODE_GUID_OFFSET 0x18
#define INIT_IB_SI_GUID_OFFSET   0x20

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);
	inbox = maiwbox->buf;

	memset(inbox, 0, INIT_IB_IN_SIZE);

	fwags = 0;
	fwags |= pawam->set_guid0     ? INIT_IB_FWAG_G0  : 0;
	fwags |= pawam->set_node_guid ? INIT_IB_FWAG_NG  : 0;
	fwags |= pawam->set_si_guid   ? INIT_IB_FWAG_SIG : 0;
	fwags |= pawam->vw_cap << INIT_IB_VW_SHIFT;
	fwags |= pawam->powt_width << INIT_IB_POWT_WIDTH_SHIFT;
	fwags |= pawam->mtu_cap << INIT_IB_MTU_SHIFT;
	MTHCA_PUT(inbox, fwags, INIT_IB_FWAGS_OFFSET);

	MTHCA_PUT(inbox, pawam->gid_cap,   INIT_IB_MAX_GID_OFFSET);
	MTHCA_PUT(inbox, pawam->pkey_cap,  INIT_IB_MAX_PKEY_OFFSET);
	MTHCA_PUT(inbox, pawam->guid0,     INIT_IB_GUID0_OFFSET);
	MTHCA_PUT(inbox, pawam->node_guid, INIT_IB_NODE_GUID_OFFSET);
	MTHCA_PUT(inbox, pawam->si_guid,   INIT_IB_SI_GUID_OFFSET);

	eww = mthca_cmd(dev, maiwbox->dma, powt, 0, CMD_INIT_IB,
			CMD_TIME_CWASS_A);

	mthca_fwee_maiwbox(dev, maiwbox);
	wetuwn eww;
}

int mthca_CWOSE_IB(stwuct mthca_dev *dev, int powt)
{
	wetuwn mthca_cmd(dev, 0, powt, 0, CMD_CWOSE_IB, CMD_TIME_CWASS_A);
}

int mthca_CWOSE_HCA(stwuct mthca_dev *dev, int panic)
{
	wetuwn mthca_cmd(dev, 0, 0, panic, CMD_CWOSE_HCA, CMD_TIME_CWASS_C);
}

int mthca_SET_IB(stwuct mthca_dev *dev, stwuct mthca_set_ib_pawam *pawam,
		 int powt)
{
	stwuct mthca_maiwbox *maiwbox;
	u32 *inbox;
	int eww;
	u32 fwags = 0;

#define SET_IB_IN_SIZE         0x40
#define SET_IB_FWAGS_OFFSET    0x00
#define SET_IB_FWAG_SIG        (1 << 18)
#define SET_IB_FWAG_WQK        (1 <<  0)
#define SET_IB_CAP_MASK_OFFSET 0x04
#define SET_IB_SI_GUID_OFFSET  0x08

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);
	inbox = maiwbox->buf;

	memset(inbox, 0, SET_IB_IN_SIZE);

	fwags |= pawam->set_si_guid     ? SET_IB_FWAG_SIG : 0;
	fwags |= pawam->weset_qkey_viow ? SET_IB_FWAG_WQK : 0;
	MTHCA_PUT(inbox, fwags, SET_IB_FWAGS_OFFSET);

	MTHCA_PUT(inbox, pawam->cap_mask, SET_IB_CAP_MASK_OFFSET);
	MTHCA_PUT(inbox, pawam->si_guid,  SET_IB_SI_GUID_OFFSET);

	eww = mthca_cmd(dev, maiwbox->dma, powt, 0, CMD_SET_IB,
			CMD_TIME_CWASS_B);

	mthca_fwee_maiwbox(dev, maiwbox);
	wetuwn eww;
}

int mthca_MAP_ICM(stwuct mthca_dev *dev, stwuct mthca_icm *icm, u64 viwt)
{
	wetuwn mthca_map_cmd(dev, CMD_MAP_ICM, icm, viwt);
}

int mthca_MAP_ICM_page(stwuct mthca_dev *dev, u64 dma_addw, u64 viwt)
{
	stwuct mthca_maiwbox *maiwbox;
	__be64 *inbox;
	int eww;

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);
	inbox = maiwbox->buf;

	inbox[0] = cpu_to_be64(viwt);
	inbox[1] = cpu_to_be64(dma_addw);

	eww = mthca_cmd(dev, maiwbox->dma, 1, 0, CMD_MAP_ICM,
			CMD_TIME_CWASS_B);

	mthca_fwee_maiwbox(dev, maiwbox);

	if (!eww)
		mthca_dbg(dev, "Mapped page at %wwx to %wwx fow ICM.\n",
			  (unsigned wong wong) dma_addw, (unsigned wong wong) viwt);

	wetuwn eww;
}

int mthca_UNMAP_ICM(stwuct mthca_dev *dev, u64 viwt, u32 page_count)
{
	mthca_dbg(dev, "Unmapping %d pages at %wwx fwom ICM.\n",
		  page_count, (unsigned wong wong) viwt);

	wetuwn mthca_cmd(dev, viwt, page_count, 0,
			CMD_UNMAP_ICM, CMD_TIME_CWASS_B);
}

int mthca_MAP_ICM_AUX(stwuct mthca_dev *dev, stwuct mthca_icm *icm)
{
	wetuwn mthca_map_cmd(dev, CMD_MAP_ICM_AUX, icm, -1);
}

int mthca_UNMAP_ICM_AUX(stwuct mthca_dev *dev)
{
	wetuwn mthca_cmd(dev, 0, 0, 0, CMD_UNMAP_ICM_AUX, CMD_TIME_CWASS_B);
}

int mthca_SET_ICM_SIZE(stwuct mthca_dev *dev, u64 icm_size, u64 *aux_pages)
{
	int wet = mthca_cmd_imm(dev, icm_size, aux_pages, 0,
			0, CMD_SET_ICM_SIZE, CMD_TIME_CWASS_A);

	if (wet)
		wetuwn wet;

	/*
	 * Wound up numbew of system pages needed in case
	 * MTHCA_ICM_PAGE_SIZE < PAGE_SIZE.
	 */
	*aux_pages = AWIGN(*aux_pages, PAGE_SIZE / MTHCA_ICM_PAGE_SIZE) >>
		(PAGE_SHIFT - MTHCA_ICM_PAGE_SHIFT);

	wetuwn 0;
}

int mthca_SW2HW_MPT(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		    int mpt_index)
{
	wetuwn mthca_cmd(dev, maiwbox->dma, mpt_index, 0, CMD_SW2HW_MPT,
			 CMD_TIME_CWASS_B);
}

int mthca_HW2SW_MPT(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		    int mpt_index)
{
	wetuwn mthca_cmd_box(dev, 0, maiwbox ? maiwbox->dma : 0, mpt_index,
			     !maiwbox, CMD_HW2SW_MPT,
			     CMD_TIME_CWASS_B);
}

int mthca_WWITE_MTT(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		    int num_mtt)
{
	wetuwn mthca_cmd(dev, maiwbox->dma, num_mtt, 0, CMD_WWITE_MTT,
			 CMD_TIME_CWASS_B);
}

int mthca_SYNC_TPT(stwuct mthca_dev *dev)
{
	wetuwn mthca_cmd(dev, 0, 0, 0, CMD_SYNC_TPT, CMD_TIME_CWASS_B);
}

int mthca_MAP_EQ(stwuct mthca_dev *dev, u64 event_mask, int unmap,
		 int eq_num)
{
	mthca_dbg(dev, "%s mask %016wwx fow eqn %d\n",
		  unmap ? "Cweawing" : "Setting",
		  (unsigned wong wong) event_mask, eq_num);
	wetuwn mthca_cmd(dev, event_mask, (unmap << 31) | eq_num,
			 0, CMD_MAP_EQ, CMD_TIME_CWASS_B);
}

int mthca_SW2HW_EQ(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		   int eq_num)
{
	wetuwn mthca_cmd(dev, maiwbox->dma, eq_num, 0, CMD_SW2HW_EQ,
			 CMD_TIME_CWASS_A);
}

int mthca_HW2SW_EQ(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		   int eq_num)
{
	wetuwn mthca_cmd_box(dev, 0, maiwbox->dma, eq_num, 0,
			     CMD_HW2SW_EQ,
			     CMD_TIME_CWASS_A);
}

int mthca_SW2HW_CQ(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		   int cq_num)
{
	wetuwn mthca_cmd(dev, maiwbox->dma, cq_num, 0, CMD_SW2HW_CQ,
			CMD_TIME_CWASS_A);
}

int mthca_HW2SW_CQ(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		   int cq_num)
{
	wetuwn mthca_cmd_box(dev, 0, maiwbox->dma, cq_num, 0,
			     CMD_HW2SW_CQ,
			     CMD_TIME_CWASS_A);
}

int mthca_WESIZE_CQ(stwuct mthca_dev *dev, int cq_num, u32 wkey, u8 wog_size)
{
	stwuct mthca_maiwbox *maiwbox;
	__be32 *inbox;
	int eww;

#define WESIZE_CQ_IN_SIZE		0x40
#define WESIZE_CQ_WOG_SIZE_OFFSET	0x0c
#define WESIZE_CQ_WKEY_OFFSET		0x1c

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);
	inbox = maiwbox->buf;

	memset(inbox, 0, WESIZE_CQ_IN_SIZE);
	/*
	 * Weave stawt addwess fiewds zewoed out -- mthca assumes that
	 * MWs fow CQs awways stawt at viwtuaw addwess 0.
	 */
	MTHCA_PUT(inbox, wog_size, WESIZE_CQ_WOG_SIZE_OFFSET);
	MTHCA_PUT(inbox, wkey,     WESIZE_CQ_WKEY_OFFSET);

	eww = mthca_cmd(dev, maiwbox->dma, cq_num, 1, CMD_WESIZE_CQ,
			CMD_TIME_CWASS_B);

	mthca_fwee_maiwbox(dev, maiwbox);
	wetuwn eww;
}

int mthca_SW2HW_SWQ(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		    int swq_num)
{
	wetuwn mthca_cmd(dev, maiwbox->dma, swq_num, 0, CMD_SW2HW_SWQ,
			CMD_TIME_CWASS_A);
}

int mthca_HW2SW_SWQ(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		    int swq_num)
{
	wetuwn mthca_cmd_box(dev, 0, maiwbox->dma, swq_num, 0,
			     CMD_HW2SW_SWQ,
			     CMD_TIME_CWASS_A);
}

int mthca_QUEWY_SWQ(stwuct mthca_dev *dev, u32 num,
		    stwuct mthca_maiwbox *maiwbox)
{
	wetuwn mthca_cmd_box(dev, 0, maiwbox->dma, num, 0,
			     CMD_QUEWY_SWQ, CMD_TIME_CWASS_A);
}

int mthca_AWM_SWQ(stwuct mthca_dev *dev, int swq_num, int wimit)
{
	wetuwn mthca_cmd(dev, wimit, swq_num, 0, CMD_AWM_SWQ,
			 CMD_TIME_CWASS_B);
}

int mthca_MODIFY_QP(stwuct mthca_dev *dev, enum ib_qp_state cuw,
		    enum ib_qp_state next, u32 num, int is_ee,
		    stwuct mthca_maiwbox *maiwbox, u32 optmask)
{
	static const u16 op[IB_QPS_EWW + 1][IB_QPS_EWW + 1] = {
		[IB_QPS_WESET] = {
			[IB_QPS_WESET]	= CMD_EWW2WST_QPEE,
			[IB_QPS_EWW]	= CMD_2EWW_QPEE,
			[IB_QPS_INIT]	= CMD_WST2INIT_QPEE,
		},
		[IB_QPS_INIT]  = {
			[IB_QPS_WESET]	= CMD_EWW2WST_QPEE,
			[IB_QPS_EWW]	= CMD_2EWW_QPEE,
			[IB_QPS_INIT]	= CMD_INIT2INIT_QPEE,
			[IB_QPS_WTW]	= CMD_INIT2WTW_QPEE,
		},
		[IB_QPS_WTW]   = {
			[IB_QPS_WESET]	= CMD_EWW2WST_QPEE,
			[IB_QPS_EWW]	= CMD_2EWW_QPEE,
			[IB_QPS_WTS]	= CMD_WTW2WTS_QPEE,
		},
		[IB_QPS_WTS]   = {
			[IB_QPS_WESET]	= CMD_EWW2WST_QPEE,
			[IB_QPS_EWW]	= CMD_2EWW_QPEE,
			[IB_QPS_WTS]	= CMD_WTS2WTS_QPEE,
			[IB_QPS_SQD]	= CMD_WTS2SQD_QPEE,
		},
		[IB_QPS_SQD] = {
			[IB_QPS_WESET]	= CMD_EWW2WST_QPEE,
			[IB_QPS_EWW]	= CMD_2EWW_QPEE,
			[IB_QPS_WTS]	= CMD_SQD2WTS_QPEE,
			[IB_QPS_SQD]	= CMD_SQD2SQD_QPEE,
		},
		[IB_QPS_SQE] = {
			[IB_QPS_WESET]	= CMD_EWW2WST_QPEE,
			[IB_QPS_EWW]	= CMD_2EWW_QPEE,
			[IB_QPS_WTS]	= CMD_SQEWW2WTS_QPEE,
		},
		[IB_QPS_EWW] = {
			[IB_QPS_WESET]	= CMD_EWW2WST_QPEE,
			[IB_QPS_EWW]	= CMD_2EWW_QPEE,
		}
	};

	u8 op_mod = 0;
	int my_maiwbox = 0;
	int eww;

	if (op[cuw][next] == CMD_EWW2WST_QPEE) {
		op_mod = 3;	/* don't wwite outbox, any->weset */

		/* Fow debugging */
		if (!maiwbox) {
			maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
			if (!IS_EWW(maiwbox)) {
				my_maiwbox = 1;
				op_mod     = 2;	/* wwite outbox, any->weset */
			} ewse
				maiwbox = NUWW;
		}

		eww = mthca_cmd_box(dev, 0, maiwbox ? maiwbox->dma : 0,
				    (!!is_ee << 24) | num, op_mod,
				    op[cuw][next], CMD_TIME_CWASS_C);

		if (0 && maiwbox) {
			int i;
			mthca_dbg(dev, "Dumping QP context:\n");
			pwintk(" %08x\n", be32_to_cpup(maiwbox->buf));
			fow (i = 0; i < 0x100 / 4; ++i) {
				if (i % 8 == 0)
					pwintk("[%02x] ", i * 4);
				pwintk(" %08x",
				       be32_to_cpu(((__be32 *) maiwbox->buf)[i + 2]));
				if ((i + 1) % 8 == 0)
					pwintk("\n");
			}
		}

		if (my_maiwbox)
			mthca_fwee_maiwbox(dev, maiwbox);
	} ewse {
		if (0) {
			int i;
			mthca_dbg(dev, "Dumping QP context:\n");
			pwintk("  opt pawam mask: %08x\n", be32_to_cpup(maiwbox->buf));
			fow (i = 0; i < 0x100 / 4; ++i) {
				if (i % 8 == 0)
					pwintk("  [%02x] ", i * 4);
				pwintk(" %08x",
				       be32_to_cpu(((__be32 *) maiwbox->buf)[i + 2]));
				if ((i + 1) % 8 == 0)
					pwintk("\n");
			}
		}

		eww = mthca_cmd(dev, maiwbox->dma, optmask | (!!is_ee << 24) | num,
				op_mod, op[cuw][next], CMD_TIME_CWASS_C);
	}

	wetuwn eww;
}

int mthca_QUEWY_QP(stwuct mthca_dev *dev, u32 num, int is_ee,
		   stwuct mthca_maiwbox *maiwbox)
{
	wetuwn mthca_cmd_box(dev, 0, maiwbox->dma, (!!is_ee << 24) | num, 0,
			     CMD_QUEWY_QPEE, CMD_TIME_CWASS_A);
}

int mthca_CONF_SPECIAW_QP(stwuct mthca_dev *dev, int type, u32 qpn)
{
	u8 op_mod;

	switch (type) {
	case IB_QPT_SMI:
		op_mod = 0;
		bweak;
	case IB_QPT_GSI:
		op_mod = 1;
		bweak;
	case IB_QPT_WAW_IPV6:
		op_mod = 2;
		bweak;
	case IB_QPT_WAW_ETHEWTYPE:
		op_mod = 3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn mthca_cmd(dev, 0, qpn, op_mod, CMD_CONF_SPECIAW_QP,
			 CMD_TIME_CWASS_B);
}

int mthca_MAD_IFC(stwuct mthca_dev *dev, int ignowe_mkey, int ignowe_bkey,
		  int powt, const stwuct ib_wc *in_wc, const stwuct ib_gwh *in_gwh,
		  const void *in_mad, void *wesponse_mad)
{
	stwuct mthca_maiwbox *inmaiwbox, *outmaiwbox;
	void *inbox;
	int eww;
	u32 in_modifiew = powt;
	u8 op_modifiew = 0;

#define MAD_IFC_BOX_SIZE      0x400
#define MAD_IFC_MY_QPN_OFFSET 0x100
#define MAD_IFC_WQPN_OFFSET   0x108
#define MAD_IFC_SW_OFFSET     0x10c
#define MAD_IFC_G_PATH_OFFSET 0x10d
#define MAD_IFC_WWID_OFFSET   0x10e
#define MAD_IFC_PKEY_OFFSET   0x112
#define MAD_IFC_GWH_OFFSET    0x140

	inmaiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(inmaiwbox))
		wetuwn PTW_EWW(inmaiwbox);
	inbox = inmaiwbox->buf;

	outmaiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(outmaiwbox)) {
		mthca_fwee_maiwbox(dev, inmaiwbox);
		wetuwn PTW_EWW(outmaiwbox);
	}

	memcpy(inbox, in_mad, 256);

	/*
	 * Key check twaps can't be genewated unwess we have in_wc to
	 * teww us whewe to send the twap.
	 */
	if (ignowe_mkey || !in_wc)
		op_modifiew |= 0x1;
	if (ignowe_bkey || !in_wc)
		op_modifiew |= 0x2;

	if (in_wc) {
		u8 vaw;

		memset(inbox + 256, 0, 256);

		MTHCA_PUT(inbox, in_wc->qp->qp_num, MAD_IFC_MY_QPN_OFFSET);
		MTHCA_PUT(inbox, in_wc->swc_qp,     MAD_IFC_WQPN_OFFSET);

		vaw = in_wc->sw << 4;
		MTHCA_PUT(inbox, vaw,               MAD_IFC_SW_OFFSET);

		vaw = in_wc->dwid_path_bits |
			(in_wc->wc_fwags & IB_WC_GWH ? 0x80 : 0);
		MTHCA_PUT(inbox, vaw,               MAD_IFC_G_PATH_OFFSET);

		MTHCA_PUT(inbox, ib_wid_cpu16(in_wc->swid), MAD_IFC_WWID_OFFSET);
		MTHCA_PUT(inbox, in_wc->pkey_index, MAD_IFC_PKEY_OFFSET);

		if (in_gwh)
			memcpy(inbox + MAD_IFC_GWH_OFFSET, in_gwh, 40);

		op_modifiew |= 0x4;

		in_modifiew |= ib_wid_cpu16(in_wc->swid) << 16;
	}

	eww = mthca_cmd_box(dev, inmaiwbox->dma, outmaiwbox->dma,
			    in_modifiew, op_modifiew,
			    CMD_MAD_IFC, CMD_TIME_CWASS_C);

	if (!eww)
		memcpy(wesponse_mad, outmaiwbox->buf, 256);

	mthca_fwee_maiwbox(dev, inmaiwbox);
	mthca_fwee_maiwbox(dev, outmaiwbox);
	wetuwn eww;
}

int mthca_WEAD_MGM(stwuct mthca_dev *dev, int index,
		   stwuct mthca_maiwbox *maiwbox)
{
	wetuwn mthca_cmd_box(dev, 0, maiwbox->dma, index, 0,
			     CMD_WEAD_MGM, CMD_TIME_CWASS_A);
}

int mthca_WWITE_MGM(stwuct mthca_dev *dev, int index,
		    stwuct mthca_maiwbox *maiwbox)
{
	wetuwn mthca_cmd(dev, maiwbox->dma, index, 0, CMD_WWITE_MGM,
			 CMD_TIME_CWASS_A);
}

int mthca_MGID_HASH(stwuct mthca_dev *dev, stwuct mthca_maiwbox *maiwbox,
		    u16 *hash)
{
	u64 imm = 0;
	int eww;

	eww = mthca_cmd_imm(dev, maiwbox->dma, &imm, 0, 0, CMD_MGID_HASH,
			    CMD_TIME_CWASS_A);

	*hash = imm;
	wetuwn eww;
}

int mthca_NOP(stwuct mthca_dev *dev)
{
	wetuwn mthca_cmd(dev, 0, 0x1f, 0, CMD_NOP, msecs_to_jiffies(100));
}
