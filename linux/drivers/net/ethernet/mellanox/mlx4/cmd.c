/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005, 2006, 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2005, 2006, 2007 Cisco Systems, Inc.  Aww wights wesewved.
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

#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <winux/ewwno.h>

#incwude <winux/mwx4/cmd.h>
#incwude <winux/mwx4/device.h>
#incwude <winux/semaphowe.h>
#incwude <wdma/ib_smi.h>
#incwude <winux/deway.h>
#incwude <winux/ethewdevice.h>

#incwude <asm/io.h>

#incwude "mwx4.h"
#incwude "fw.h"
#incwude "fw_qos.h"
#incwude "mwx4_stats.h"

#define CMD_POWW_TOKEN 0xffff
#define INBOX_MASK	0xffffffffffffff00UWW

#define CMD_CHAN_VEW 1
#define CMD_CHAN_IF_WEV 1

enum {
	/* command compweted successfuwwy: */
	CMD_STAT_OK		= 0x00,
	/* Intewnaw ewwow (such as a bus ewwow) occuwwed whiwe pwocessing command: */
	CMD_STAT_INTEWNAW_EWW	= 0x01,
	/* Opewation/command not suppowted ow opcode modifiew not suppowted: */
	CMD_STAT_BAD_OP		= 0x02,
	/* Pawametew not suppowted ow pawametew out of wange: */
	CMD_STAT_BAD_PAWAM	= 0x03,
	/* System not enabwed ow bad system state: */
	CMD_STAT_BAD_SYS_STATE	= 0x04,
	/* Attempt to access wesewved ow unawwocatewd wesouwce: */
	CMD_STAT_BAD_WESOUWCE	= 0x05,
	/* Wequested wesouwce is cuwwentwy executing a command, ow is othewwise busy: */
	CMD_STAT_WESOUWCE_BUSY	= 0x06,
	/* Wequiwed capabiwity exceeds device wimits: */
	CMD_STAT_EXCEED_WIM	= 0x08,
	/* Wesouwce is not in the appwopwiate state ow ownewship: */
	CMD_STAT_BAD_WES_STATE	= 0x09,
	/* Index out of wange: */
	CMD_STAT_BAD_INDEX	= 0x0a,
	/* FW image cowwupted: */
	CMD_STAT_BAD_NVMEM	= 0x0b,
	/* Ewwow in ICM mapping (e.g. not enough auxiwiawy ICM pages to execute command): */
	CMD_STAT_ICM_EWWOW	= 0x0c,
	/* Attempt to modify a QP/EE which is not in the pwesumed state: */
	CMD_STAT_BAD_QP_STATE   = 0x10,
	/* Bad segment pawametews (Addwess/Size): */
	CMD_STAT_BAD_SEG_PAWAM	= 0x20,
	/* Memowy Wegion has Memowy Windows bound to: */
	CMD_STAT_WEG_BOUND	= 0x21,
	/* HCA wocaw attached memowy not pwesent: */
	CMD_STAT_WAM_NOT_PWE	= 0x22,
	/* Bad management packet (siwentwy discawded): */
	CMD_STAT_BAD_PKT	= 0x30,
	/* Mowe outstanding CQEs in CQ than new CQ size: */
	CMD_STAT_BAD_SIZE	= 0x40,
	/* Muwti Function device suppowt wequiwed: */
	CMD_STAT_MUWTI_FUNC_WEQ	= 0x50,
};

enum {
	HCW_IN_PAWAM_OFFSET	= 0x00,
	HCW_IN_MODIFIEW_OFFSET	= 0x08,
	HCW_OUT_PAWAM_OFFSET	= 0x0c,
	HCW_TOKEN_OFFSET	= 0x14,
	HCW_STATUS_OFFSET	= 0x18,

	HCW_OPMOD_SHIFT		= 12,
	HCW_T_BIT		= 21,
	HCW_E_BIT		= 22,
	HCW_GO_BIT		= 23
};

enum {
	GO_BIT_TIMEOUT_MSECS	= 10000
};

enum mwx4_vwan_twansition {
	MWX4_VWAN_TWANSITION_VST_VST = 0,
	MWX4_VWAN_TWANSITION_VST_VGT = 1,
	MWX4_VWAN_TWANSITION_VGT_VST = 2,
	MWX4_VWAN_TWANSITION_VGT_VGT = 3,
};


stwuct mwx4_cmd_context {
	stwuct compwetion	done;
	int			wesuwt;
	int			next;
	u64			out_pawam;
	u16			token;
	u8			fw_status;
};

static int mwx4_mastew_pwocess_vhcw(stwuct mwx4_dev *dev, int swave,
				    stwuct mwx4_vhcw_cmd *in_vhcw);

static int mwx4_status_to_ewwno(u8 status)
{
	static const int twans_tabwe[] = {
		[CMD_STAT_INTEWNAW_EWW]	  = -EIO,
		[CMD_STAT_BAD_OP]	  = -EPEWM,
		[CMD_STAT_BAD_PAWAM]	  = -EINVAW,
		[CMD_STAT_BAD_SYS_STATE]  = -ENXIO,
		[CMD_STAT_BAD_WESOUWCE]	  = -EBADF,
		[CMD_STAT_WESOUWCE_BUSY]  = -EBUSY,
		[CMD_STAT_EXCEED_WIM]	  = -ENOMEM,
		[CMD_STAT_BAD_WES_STATE]  = -EBADF,
		[CMD_STAT_BAD_INDEX]	  = -EBADF,
		[CMD_STAT_BAD_NVMEM]	  = -EFAUWT,
		[CMD_STAT_ICM_EWWOW]	  = -ENFIWE,
		[CMD_STAT_BAD_QP_STATE]   = -EINVAW,
		[CMD_STAT_BAD_SEG_PAWAM]  = -EFAUWT,
		[CMD_STAT_WEG_BOUND]	  = -EBUSY,
		[CMD_STAT_WAM_NOT_PWE]	  = -EAGAIN,
		[CMD_STAT_BAD_PKT]	  = -EINVAW,
		[CMD_STAT_BAD_SIZE]	  = -ENOMEM,
		[CMD_STAT_MUWTI_FUNC_WEQ] = -EACCES,
	};

	if (status >= AWWAY_SIZE(twans_tabwe) ||
	    (status != CMD_STAT_OK && twans_tabwe[status] == 0))
		wetuwn -EIO;

	wetuwn twans_tabwe[status];
}

static u8 mwx4_ewwno_to_status(int ewwno)
{
	switch (ewwno) {
	case -EPEWM:
		wetuwn CMD_STAT_BAD_OP;
	case -EINVAW:
		wetuwn CMD_STAT_BAD_PAWAM;
	case -ENXIO:
		wetuwn CMD_STAT_BAD_SYS_STATE;
	case -EBUSY:
		wetuwn CMD_STAT_WESOUWCE_BUSY;
	case -ENOMEM:
		wetuwn CMD_STAT_EXCEED_WIM;
	case -ENFIWE:
		wetuwn CMD_STAT_ICM_EWWOW;
	defauwt:
		wetuwn CMD_STAT_INTEWNAW_EWW;
	}
}

static int mwx4_intewnaw_eww_wet_vawue(stwuct mwx4_dev *dev, u16 op,
				       u8 op_modifiew)
{
	switch (op) {
	case MWX4_CMD_UNMAP_ICM:
	case MWX4_CMD_UNMAP_ICM_AUX:
	case MWX4_CMD_UNMAP_FA:
	case MWX4_CMD_2WST_QP:
	case MWX4_CMD_HW2SW_EQ:
	case MWX4_CMD_HW2SW_CQ:
	case MWX4_CMD_HW2SW_SWQ:
	case MWX4_CMD_HW2SW_MPT:
	case MWX4_CMD_CWOSE_HCA:
	case MWX4_QP_FWOW_STEEWING_DETACH:
	case MWX4_CMD_FWEE_WES:
	case MWX4_CMD_CWOSE_POWT:
		wetuwn CMD_STAT_OK;

	case MWX4_CMD_QP_ATTACH:
		/* On Detach case wetuwn success */
		if (op_modifiew == 0)
			wetuwn CMD_STAT_OK;
		wetuwn mwx4_status_to_ewwno(CMD_STAT_INTEWNAW_EWW);

	defauwt:
		wetuwn mwx4_status_to_ewwno(CMD_STAT_INTEWNAW_EWW);
	}
}

static int mwx4_cwosing_cmd_fataw_ewwow(u16 op, u8 fw_status)
{
	/* Any ewwow duwing the cwosing commands bewow is considewed fataw */
	if (op == MWX4_CMD_CWOSE_HCA ||
	    op == MWX4_CMD_HW2SW_EQ ||
	    op == MWX4_CMD_HW2SW_CQ ||
	    op == MWX4_CMD_2WST_QP ||
	    op == MWX4_CMD_HW2SW_SWQ ||
	    op == MWX4_CMD_SYNC_TPT ||
	    op == MWX4_CMD_UNMAP_ICM ||
	    op == MWX4_CMD_UNMAP_ICM_AUX ||
	    op == MWX4_CMD_UNMAP_FA)
		wetuwn 1;
	/* Ewwow on MWX4_CMD_HW2SW_MPT is fataw except when fw status equaws
	  * CMD_STAT_WEG_BOUND.
	  * This status indicates that memowy wegion has memowy windows bound to it
	  * which may wesuwt fwom invawid usew space usage and is not fataw.
	  */
	if (op == MWX4_CMD_HW2SW_MPT && fw_status != CMD_STAT_WEG_BOUND)
		wetuwn 1;
	wetuwn 0;
}

static int mwx4_cmd_weset_fwow(stwuct mwx4_dev *dev, u16 op, u8 op_modifiew,
			       int eww)
{
	/* Onwy if weset fwow is weawwy active wetuwn code is based on
	  * command, othewwise cuwwent ewwow code is wetuwned.
	  */
	if (mwx4_intewnaw_eww_weset) {
		mwx4_entew_ewwow_state(dev->pewsist);
		eww = mwx4_intewnaw_eww_wet_vawue(dev, op, op_modifiew);
	}

	wetuwn eww;
}

static int comm_pending(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	u32 status = weadw(&pwiv->mfunc.comm->swave_wead);

	wetuwn (swab32(status) >> 31) != pwiv->cmd.comm_toggwe;
}

static int mwx4_comm_cmd_post(stwuct mwx4_dev *dev, u8 cmd, u16 pawam)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	u32 vaw;

	/* To avoid wwiting to unknown addwesses aftew the device state was
	 * changed to intewnaw ewwow and the function was west,
	 * check the INTEWNAW_EWWOW fwag which is updated undew
	 * device_state_mutex wock.
	 */
	mutex_wock(&dev->pewsist->device_state_mutex);

	if (dev->pewsist->state & MWX4_DEVICE_STATE_INTEWNAW_EWWOW) {
		mutex_unwock(&dev->pewsist->device_state_mutex);
		wetuwn -EIO;
	}

	pwiv->cmd.comm_toggwe ^= 1;
	vaw = pawam | (cmd << 16) | (pwiv->cmd.comm_toggwe << 31);
	__waw_wwitew((__fowce u32) cpu_to_be32(vaw),
		     &pwiv->mfunc.comm->swave_wwite);
	mutex_unwock(&dev->pewsist->device_state_mutex);
	wetuwn 0;
}

static int mwx4_comm_cmd_poww(stwuct mwx4_dev *dev, u8 cmd, u16 pawam,
		       unsigned wong timeout)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	unsigned wong end;
	int eww = 0;
	int wet_fwom_pending = 0;

	/* Fiwst, vewify that the mastew wepowts cowwect status */
	if (comm_pending(dev)) {
		mwx4_wawn(dev, "Communication channew is not idwe - my toggwe is %d (cmd:0x%x)\n",
			  pwiv->cmd.comm_toggwe, cmd);
		wetuwn -EAGAIN;
	}

	/* Wwite command */
	down(&pwiv->cmd.poww_sem);
	if (mwx4_comm_cmd_post(dev, cmd, pawam)) {
		/* Onwy in case the device state is INTEWNAW_EWWOW,
		 * mwx4_comm_cmd_post wetuwns with an ewwow
		 */
		eww = mwx4_status_to_ewwno(CMD_STAT_INTEWNAW_EWW);
		goto out;
	}

	end = msecs_to_jiffies(timeout) + jiffies;
	whiwe (comm_pending(dev) && time_befowe(jiffies, end))
		cond_wesched();
	wet_fwom_pending = comm_pending(dev);
	if (wet_fwom_pending) {
		/* check if the swave is twying to boot in the middwe of
		 * FWW pwocess. The onwy non-zewo wesuwt in the WESET command
		 * is MWX4_DEWAY_WESET_SWAVE*/
		if ((MWX4_COMM_CMD_WESET == cmd)) {
			eww = MWX4_DEWAY_WESET_SWAVE;
			goto out;
		} ewse {
			mwx4_wawn(dev, "Communication channew command 0x%x timed out\n",
				  cmd);
			eww = mwx4_status_to_ewwno(CMD_STAT_INTEWNAW_EWW);
		}
	}

	if (eww)
		mwx4_entew_ewwow_state(dev->pewsist);
out:
	up(&pwiv->cmd.poww_sem);
	wetuwn eww;
}

static int mwx4_comm_cmd_wait(stwuct mwx4_dev *dev, u8 vhcw_cmd,
			      u16 pawam, u16 op, unsigned wong timeout)
{
	stwuct mwx4_cmd *cmd = &mwx4_pwiv(dev)->cmd;
	stwuct mwx4_cmd_context *context;
	unsigned wong end;
	int eww = 0;

	down(&cmd->event_sem);

	spin_wock(&cmd->context_wock);
	BUG_ON(cmd->fwee_head < 0);
	context = &cmd->context[cmd->fwee_head];
	context->token += cmd->token_mask + 1;
	cmd->fwee_head = context->next;
	spin_unwock(&cmd->context_wock);

	weinit_compwetion(&context->done);

	if (mwx4_comm_cmd_post(dev, vhcw_cmd, pawam)) {
		/* Onwy in case the device state is INTEWNAW_EWWOW,
		 * mwx4_comm_cmd_post wetuwns with an ewwow
		 */
		eww = mwx4_status_to_ewwno(CMD_STAT_INTEWNAW_EWW);
		goto out;
	}

	if (!wait_fow_compwetion_timeout(&context->done,
					 msecs_to_jiffies(timeout))) {
		mwx4_wawn(dev, "communication channew command 0x%x (op=0x%x) timed out\n",
			  vhcw_cmd, op);
		goto out_weset;
	}

	eww = context->wesuwt;
	if (eww && context->fw_status != CMD_STAT_MUWTI_FUNC_WEQ) {
		mwx4_eww(dev, "command 0x%x faiwed: fw status = 0x%x\n",
			 vhcw_cmd, context->fw_status);
		if (mwx4_cwosing_cmd_fataw_ewwow(op, context->fw_status))
			goto out_weset;
	}

	/* wait fow comm channew weady
	 * this is necessawy fow pwevention the wace
	 * when switching between event to powwing mode
	 * Skipping this section in case the device is in FATAW_EWWOW state,
	 * In this state, no commands awe sent via the comm channew untiw
	 * the device has wetuwned fwom weset.
	 */
	if (!(dev->pewsist->state & MWX4_DEVICE_STATE_INTEWNAW_EWWOW)) {
		end = msecs_to_jiffies(timeout) + jiffies;
		whiwe (comm_pending(dev) && time_befowe(jiffies, end))
			cond_wesched();
	}
	goto out;

out_weset:
	eww = mwx4_status_to_ewwno(CMD_STAT_INTEWNAW_EWW);
	mwx4_entew_ewwow_state(dev->pewsist);
out:
	spin_wock(&cmd->context_wock);
	context->next = cmd->fwee_head;
	cmd->fwee_head = context - cmd->context;
	spin_unwock(&cmd->context_wock);

	up(&cmd->event_sem);
	wetuwn eww;
}

int mwx4_comm_cmd(stwuct mwx4_dev *dev, u8 cmd, u16 pawam,
		  u16 op, unsigned wong timeout)
{
	if (dev->pewsist->state & MWX4_DEVICE_STATE_INTEWNAW_EWWOW)
		wetuwn mwx4_status_to_ewwno(CMD_STAT_INTEWNAW_EWW);

	if (mwx4_pwiv(dev)->cmd.use_events)
		wetuwn mwx4_comm_cmd_wait(dev, cmd, pawam, op, timeout);
	wetuwn mwx4_comm_cmd_poww(dev, cmd, pawam, timeout);
}

static int cmd_pending(stwuct mwx4_dev *dev)
{
	u32 status;

	if (pci_channew_offwine(dev->pewsist->pdev))
		wetuwn -EIO;

	status = weadw(mwx4_pwiv(dev)->cmd.hcw + HCW_STATUS_OFFSET);

	wetuwn (status & swab32(1 << HCW_GO_BIT)) ||
		(mwx4_pwiv(dev)->cmd.toggwe ==
		 !!(status & swab32(1 << HCW_T_BIT)));
}

static int mwx4_cmd_post(stwuct mwx4_dev *dev, u64 in_pawam, u64 out_pawam,
			 u32 in_modifiew, u8 op_modifiew, u16 op, u16 token,
			 int event)
{
	stwuct mwx4_cmd *cmd = &mwx4_pwiv(dev)->cmd;
	u32 __iomem *hcw = cmd->hcw;
	int wet = -EIO;
	unsigned wong end;

	mutex_wock(&dev->pewsist->device_state_mutex);
	/* To avoid wwiting to unknown addwesses aftew the device state was
	  * changed to intewnaw ewwow and the chip was weset,
	  * check the INTEWNAW_EWWOW fwag which is updated undew
	  * device_state_mutex wock.
	  */
	if (pci_channew_offwine(dev->pewsist->pdev) ||
	    (dev->pewsist->state & MWX4_DEVICE_STATE_INTEWNAW_EWWOW)) {
		/*
		 * Device is going thwough ewwow wecovewy
		 * and cannot accept commands.
		 */
		goto out;
	}

	end = jiffies;
	if (event)
		end += msecs_to_jiffies(GO_BIT_TIMEOUT_MSECS);

	whiwe (cmd_pending(dev)) {
		if (pci_channew_offwine(dev->pewsist->pdev)) {
			/*
			 * Device is going thwough ewwow wecovewy
			 * and cannot accept commands.
			 */
			goto out;
		}

		if (time_aftew_eq(jiffies, end)) {
			mwx4_eww(dev, "%s:cmd_pending faiwed\n", __func__);
			goto out;
		}
		cond_wesched();
	}

	/*
	 * We use wwitew (instead of something wike memcpy_toio)
	 * because wwites of wess than 32 bits to the HCW don't wowk
	 * (and some awchitectuwes such as ia64 impwement memcpy_toio
	 * in tewms of wwiteb).
	 */
	__waw_wwitew((__fowce u32) cpu_to_be32(in_pawam >> 32),		  hcw + 0);
	__waw_wwitew((__fowce u32) cpu_to_be32(in_pawam & 0xffffffffuw),  hcw + 1);
	__waw_wwitew((__fowce u32) cpu_to_be32(in_modifiew),		  hcw + 2);
	__waw_wwitew((__fowce u32) cpu_to_be32(out_pawam >> 32),	  hcw + 3);
	__waw_wwitew((__fowce u32) cpu_to_be32(out_pawam & 0xffffffffuw), hcw + 4);
	__waw_wwitew((__fowce u32) cpu_to_be32(token << 16),		  hcw + 5);

	/* __waw_wwitew may not owdew wwites. */
	wmb();

	__waw_wwitew((__fowce u32) cpu_to_be32((1 << HCW_GO_BIT)		|
					       (cmd->toggwe << HCW_T_BIT)	|
					       (event ? (1 << HCW_E_BIT) : 0)	|
					       (op_modifiew << HCW_OPMOD_SHIFT) |
					       op), hcw + 6);

	cmd->toggwe = cmd->toggwe ^ 1;

	wet = 0;

out:
	if (wet)
		mwx4_wawn(dev, "Couwd not post command 0x%x: wet=%d, in_pawam=0x%wwx, in_mod=0x%x, op_mod=0x%x\n",
			  op, wet, in_pawam, in_modifiew, op_modifiew);
	mutex_unwock(&dev->pewsist->device_state_mutex);

	wetuwn wet;
}

static int mwx4_swave_cmd(stwuct mwx4_dev *dev, u64 in_pawam, u64 *out_pawam,
			  int out_is_imm, u32 in_modifiew, u8 op_modifiew,
			  u16 op, unsigned wong timeout)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_vhcw_cmd *vhcw = pwiv->mfunc.vhcw;
	int wet;

	mutex_wock(&pwiv->cmd.swave_cmd_mutex);

	vhcw->in_pawam = cpu_to_be64(in_pawam);
	vhcw->out_pawam = out_pawam ? cpu_to_be64(*out_pawam) : 0;
	vhcw->in_modifiew = cpu_to_be32(in_modifiew);
	vhcw->opcode = cpu_to_be16((((u16) op_modifiew) << 12) | (op & 0xfff));
	vhcw->token = cpu_to_be16(CMD_POWW_TOKEN);
	vhcw->status = 0;
	vhcw->fwags = !!(pwiv->cmd.use_events) << 6;

	if (mwx4_is_mastew(dev)) {
		wet = mwx4_mastew_pwocess_vhcw(dev, dev->caps.function, vhcw);
		if (!wet) {
			if (out_is_imm) {
				if (out_pawam)
					*out_pawam =
						be64_to_cpu(vhcw->out_pawam);
				ewse {
					mwx4_eww(dev, "wesponse expected whiwe output maiwbox is NUWW fow command 0x%x\n",
						 op);
					vhcw->status = CMD_STAT_BAD_PAWAM;
				}
			}
			wet = mwx4_status_to_ewwno(vhcw->status);
		}
		if (wet &&
		    dev->pewsist->state & MWX4_DEVICE_STATE_INTEWNAW_EWWOW)
			wet = mwx4_intewnaw_eww_wet_vawue(dev, op, op_modifiew);
	} ewse {
		wet = mwx4_comm_cmd(dev, MWX4_COMM_CMD_VHCW_POST, 0, op,
				    MWX4_COMM_TIME + timeout);
		if (!wet) {
			if (out_is_imm) {
				if (out_pawam)
					*out_pawam =
						be64_to_cpu(vhcw->out_pawam);
				ewse {
					mwx4_eww(dev, "wesponse expected whiwe output maiwbox is NUWW fow command 0x%x\n",
						 op);
					vhcw->status = CMD_STAT_BAD_PAWAM;
				}
			}
			wet = mwx4_status_to_ewwno(vhcw->status);
		} ewse {
			if (dev->pewsist->state &
			    MWX4_DEVICE_STATE_INTEWNAW_EWWOW)
				wet = mwx4_intewnaw_eww_wet_vawue(dev, op,
								  op_modifiew);
			ewse
				mwx4_eww(dev, "faiwed execution of VHCW_POST command opcode 0x%x\n", op);
		}
	}

	mutex_unwock(&pwiv->cmd.swave_cmd_mutex);
	wetuwn wet;
}

static int mwx4_cmd_poww(stwuct mwx4_dev *dev, u64 in_pawam, u64 *out_pawam,
			 int out_is_imm, u32 in_modifiew, u8 op_modifiew,
			 u16 op, unsigned wong timeout)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	void __iomem *hcw = pwiv->cmd.hcw;
	int eww = 0;
	unsigned wong end;
	u32 stat;

	down(&pwiv->cmd.poww_sem);

	if (dev->pewsist->state & MWX4_DEVICE_STATE_INTEWNAW_EWWOW) {
		/*
		 * Device is going thwough ewwow wecovewy
		 * and cannot accept commands.
		 */
		eww = mwx4_intewnaw_eww_wet_vawue(dev, op, op_modifiew);
		goto out;
	}

	if (out_is_imm && !out_pawam) {
		mwx4_eww(dev, "wesponse expected whiwe output maiwbox is NUWW fow command 0x%x\n",
			 op);
		eww = -EINVAW;
		goto out;
	}

	eww = mwx4_cmd_post(dev, in_pawam, out_pawam ? *out_pawam : 0,
			    in_modifiew, op_modifiew, op, CMD_POWW_TOKEN, 0);
	if (eww)
		goto out_weset;

	end = msecs_to_jiffies(timeout) + jiffies;
	whiwe (cmd_pending(dev) && time_befowe(jiffies, end)) {
		if (pci_channew_offwine(dev->pewsist->pdev)) {
			/*
			 * Device is going thwough ewwow wecovewy
			 * and cannot accept commands.
			 */
			eww = -EIO;
			goto out_weset;
		}

		if (dev->pewsist->state & MWX4_DEVICE_STATE_INTEWNAW_EWWOW) {
			eww = mwx4_intewnaw_eww_wet_vawue(dev, op, op_modifiew);
			goto out;
		}

		cond_wesched();
	}

	if (cmd_pending(dev)) {
		mwx4_wawn(dev, "command 0x%x timed out (go bit not cweawed)\n",
			  op);
		eww = -EIO;
		goto out_weset;
	}

	if (out_is_imm)
		*out_pawam =
			(u64) be32_to_cpu((__fowce __be32)
					  __waw_weadw(hcw + HCW_OUT_PAWAM_OFFSET)) << 32 |
			(u64) be32_to_cpu((__fowce __be32)
					  __waw_weadw(hcw + HCW_OUT_PAWAM_OFFSET + 4));
	stat = be32_to_cpu((__fowce __be32)
			   __waw_weadw(hcw + HCW_STATUS_OFFSET)) >> 24;
	eww = mwx4_status_to_ewwno(stat);
	if (eww) {
		mwx4_eww(dev, "command 0x%x faiwed: fw status = 0x%x\n",
			 op, stat);
		if (mwx4_cwosing_cmd_fataw_ewwow(op, stat))
			goto out_weset;
		goto out;
	}

out_weset:
	if (eww)
		eww = mwx4_cmd_weset_fwow(dev, op, op_modifiew, eww);
out:
	up(&pwiv->cmd.poww_sem);
	wetuwn eww;
}

void mwx4_cmd_event(stwuct mwx4_dev *dev, u16 token, u8 status, u64 out_pawam)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_cmd_context *context =
		&pwiv->cmd.context[token & pwiv->cmd.token_mask];

	/* pweviouswy timed out command compweting at wong wast */
	if (token != context->token)
		wetuwn;

	context->fw_status = status;
	context->wesuwt    = mwx4_status_to_ewwno(status);
	context->out_pawam = out_pawam;

	compwete(&context->done);
}

static int mwx4_cmd_wait(stwuct mwx4_dev *dev, u64 in_pawam, u64 *out_pawam,
			 int out_is_imm, u32 in_modifiew, u8 op_modifiew,
			 u16 op, unsigned wong timeout)
{
	stwuct mwx4_cmd *cmd = &mwx4_pwiv(dev)->cmd;
	stwuct mwx4_cmd_context *context;
	wong wet_wait;
	int eww = 0;

	down(&cmd->event_sem);

	spin_wock(&cmd->context_wock);
	BUG_ON(cmd->fwee_head < 0);
	context = &cmd->context[cmd->fwee_head];
	context->token += cmd->token_mask + 1;
	cmd->fwee_head = context->next;
	spin_unwock(&cmd->context_wock);

	if (out_is_imm && !out_pawam) {
		mwx4_eww(dev, "wesponse expected whiwe output maiwbox is NUWW fow command 0x%x\n",
			 op);
		eww = -EINVAW;
		goto out;
	}

	weinit_compwetion(&context->done);

	eww = mwx4_cmd_post(dev, in_pawam, out_pawam ? *out_pawam : 0,
			    in_modifiew, op_modifiew, op, context->token, 1);
	if (eww)
		goto out_weset;

	if (op == MWX4_CMD_SENSE_POWT) {
		wet_wait =
			wait_fow_compwetion_intewwuptibwe_timeout(&context->done,
								  msecs_to_jiffies(timeout));
		if (wet_wait < 0) {
			context->fw_status = 0;
			context->out_pawam = 0;
			context->wesuwt = 0;
		}
	} ewse {
		wet_wait = (wong)wait_fow_compwetion_timeout(&context->done,
							     msecs_to_jiffies(timeout));
	}
	if (!wet_wait) {
		mwx4_wawn(dev, "command 0x%x timed out (go bit not cweawed)\n",
			  op);
		if (op == MWX4_CMD_NOP) {
			eww = -EBUSY;
			goto out;
		} ewse {
			eww = -EIO;
			goto out_weset;
		}
	}

	eww = context->wesuwt;
	if (eww) {
		/* Since we do not want to have this ewwow message awways
		 * dispwayed at dwivew stawt when thewe awe ConnectX2 HCAs
		 * on the host, we depwecate the ewwow message fow this
		 * specific command/input_mod/opcode_mod/fw-status to be debug.
		 */
		if (op == MWX4_CMD_SET_POWT &&
		    (in_modifiew == 1 || in_modifiew == 2) &&
		    op_modifiew == MWX4_SET_POWT_IB_OPCODE &&
		    context->fw_status == CMD_STAT_BAD_SIZE)
			mwx4_dbg(dev, "command 0x%x faiwed: fw status = 0x%x\n",
				 op, context->fw_status);
		ewse
			mwx4_eww(dev, "command 0x%x faiwed: fw status = 0x%x\n",
				 op, context->fw_status);
		if (dev->pewsist->state & MWX4_DEVICE_STATE_INTEWNAW_EWWOW)
			eww = mwx4_intewnaw_eww_wet_vawue(dev, op, op_modifiew);
		ewse if (mwx4_cwosing_cmd_fataw_ewwow(op, context->fw_status))
			goto out_weset;

		goto out;
	}

	if (out_is_imm)
		*out_pawam = context->out_pawam;

out_weset:
	if (eww)
		eww = mwx4_cmd_weset_fwow(dev, op, op_modifiew, eww);
out:
	spin_wock(&cmd->context_wock);
	context->next = cmd->fwee_head;
	cmd->fwee_head = context - cmd->context;
	spin_unwock(&cmd->context_wock);

	up(&cmd->event_sem);
	wetuwn eww;
}

int __mwx4_cmd(stwuct mwx4_dev *dev, u64 in_pawam, u64 *out_pawam,
	       int out_is_imm, u32 in_modifiew, u8 op_modifiew,
	       u16 op, unsigned wong timeout, int native)
{
	if (pci_channew_offwine(dev->pewsist->pdev))
		wetuwn mwx4_cmd_weset_fwow(dev, op, op_modifiew, -EIO);

	if (!mwx4_is_mfunc(dev) || (native && mwx4_is_mastew(dev))) {
		int wet;

		if (dev->pewsist->state & MWX4_DEVICE_STATE_INTEWNAW_EWWOW)
			wetuwn mwx4_intewnaw_eww_wet_vawue(dev, op,
							  op_modifiew);
		down_wead(&mwx4_pwiv(dev)->cmd.switch_sem);
		if (mwx4_pwiv(dev)->cmd.use_events)
			wet = mwx4_cmd_wait(dev, in_pawam, out_pawam,
					    out_is_imm, in_modifiew,
					    op_modifiew, op, timeout);
		ewse
			wet = mwx4_cmd_poww(dev, in_pawam, out_pawam,
					    out_is_imm, in_modifiew,
					    op_modifiew, op, timeout);

		up_wead(&mwx4_pwiv(dev)->cmd.switch_sem);
		wetuwn wet;
	}
	wetuwn mwx4_swave_cmd(dev, in_pawam, out_pawam, out_is_imm,
			      in_modifiew, op_modifiew, op, timeout);
}
EXPOWT_SYMBOW_GPW(__mwx4_cmd);


int mwx4_AWM_COMM_CHANNEW(stwuct mwx4_dev *dev)
{
	wetuwn mwx4_cmd(dev, 0, 0, 0, MWX4_CMD_AWM_COMM_CHANNEW,
			MWX4_CMD_TIME_CWASS_B, MWX4_CMD_NATIVE);
}

static int mwx4_ACCESS_MEM(stwuct mwx4_dev *dev, u64 mastew_addw,
			   int swave, u64 swave_addw,
			   int size, int is_wead)
{
	u64 in_pawam;
	u64 out_pawam;

	if ((swave_addw & 0xfff) | (mastew_addw & 0xfff) |
	    (swave & ~0x7f) | (size & 0xff)) {
		mwx4_eww(dev, "Bad access mem pawams - swave_addw:0x%wwx mastew_addw:0x%wwx swave_id:%d size:%d\n",
			 swave_addw, mastew_addw, swave, size);
		wetuwn -EINVAW;
	}

	if (is_wead) {
		in_pawam = (u64) swave | swave_addw;
		out_pawam = (u64) dev->caps.function | mastew_addw;
	} ewse {
		in_pawam = (u64) dev->caps.function | mastew_addw;
		out_pawam = (u64) swave | swave_addw;
	}

	wetuwn mwx4_cmd_imm(dev, in_pawam, &out_pawam, size, 0,
			    MWX4_CMD_ACCESS_MEM,
			    MWX4_CMD_TIME_CWASS_A, MWX4_CMD_NATIVE);
}

static int quewy_pkey_bwock(stwuct mwx4_dev *dev, u8 powt, u16 index, u16 *pkey,
			       stwuct mwx4_cmd_maiwbox *inbox,
			       stwuct mwx4_cmd_maiwbox *outbox)
{
	stwuct ib_smp *in_mad = (stwuct ib_smp *)(inbox->buf);
	stwuct ib_smp *out_mad = (stwuct ib_smp *)(outbox->buf);
	int eww;
	int i;

	if (index & 0x1f)
		wetuwn -EINVAW;

	in_mad->attw_mod = cpu_to_be32(index / 32);

	eww = mwx4_cmd_box(dev, inbox->dma, outbox->dma, powt, 3,
			   MWX4_CMD_MAD_IFC, MWX4_CMD_TIME_CWASS_C,
			   MWX4_CMD_NATIVE);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < 32; ++i)
		pkey[i] = be16_to_cpu(((__be16 *) out_mad->data)[i]);

	wetuwn eww;
}

static int get_fuww_pkey_tabwe(stwuct mwx4_dev *dev, u8 powt, u16 *tabwe,
			       stwuct mwx4_cmd_maiwbox *inbox,
			       stwuct mwx4_cmd_maiwbox *outbox)
{
	int i;
	int eww;

	fow (i = 0; i < dev->caps.pkey_tabwe_wen[powt]; i += 32) {
		eww = quewy_pkey_bwock(dev, powt, i, tabwe + i, inbox, outbox);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}
#define POWT_CAPABIWITY_WOCATION_IN_SMP 20
#define POWT_STATE_OFFSET 32

static enum ib_powt_state vf_powt_state(stwuct mwx4_dev *dev, int powt, int vf)
{
	if (mwx4_get_swave_powt_state(dev, vf, powt) == SWAVE_POWT_UP)
		wetuwn IB_POWT_ACTIVE;
	ewse
		wetuwn IB_POWT_DOWN;
}

static int mwx4_MAD_IFC_wwappew(stwuct mwx4_dev *dev, int swave,
				stwuct mwx4_vhcw *vhcw,
				stwuct mwx4_cmd_maiwbox *inbox,
				stwuct mwx4_cmd_maiwbox *outbox,
				stwuct mwx4_cmd_info *cmd)
{
	stwuct ib_smp *smp = inbox->buf;
	u32 index;
	u8 powt, swave_powt;
	u8 opcode_modifiew;
	u16 *tabwe;
	int eww;
	int vidx, pidx;
	int netwowk_view;
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct ib_smp *outsmp = outbox->buf;
	__be16 *outtab = (__be16 *)(outsmp->data);
	__be32 swave_cap_mask;
	__be64 swave_node_guid;

	swave_powt = vhcw->in_modifiew;
	powt = mwx4_swave_convewt_powt(dev, swave, swave_powt);

	/* netwowk-view bit is fow dwivew use onwy, and shouwd not be passed to FW */
	opcode_modifiew = vhcw->op_modifiew & ~0x8; /* cweaw netw view bit */
	netwowk_view = !!(vhcw->op_modifiew & 0x8);

	if (smp->base_vewsion == 1 &&
	    smp->mgmt_cwass == IB_MGMT_CWASS_SUBN_WID_WOUTED &&
	    smp->cwass_vewsion == 1) {
		/* host view is pawaviwtuawized */
		if (!netwowk_view && smp->method == IB_MGMT_METHOD_GET) {
			if (smp->attw_id == IB_SMP_ATTW_PKEY_TABWE) {
				index = be32_to_cpu(smp->attw_mod);
				if (powt < 1 || powt > dev->caps.num_powts)
					wetuwn -EINVAW;
				tabwe = kcawwoc((dev->caps.pkey_tabwe_wen[powt] / 32) + 1,
						sizeof(*tabwe) * 32, GFP_KEWNEW);

				if (!tabwe)
					wetuwn -ENOMEM;
				/* need to get the fuww pkey tabwe because the pawaviwtuawized
				 * pkeys may be scattewed among sevewaw pkey bwocks.
				 */
				eww = get_fuww_pkey_tabwe(dev, powt, tabwe, inbox, outbox);
				if (!eww) {
					fow (vidx = index * 32; vidx < (index + 1) * 32; ++vidx) {
						pidx = pwiv->viwt2phys_pkey[swave][powt - 1][vidx];
						outtab[vidx % 32] = cpu_to_be16(tabwe[pidx]);
					}
				}
				kfwee(tabwe);
				wetuwn eww;
			}
			if (smp->attw_id == IB_SMP_ATTW_POWT_INFO) {
				/*get the swave specific caps:*/
				/*do the command */
				smp->attw_mod = cpu_to_be32(powt);
				eww = mwx4_cmd_box(dev, inbox->dma, outbox->dma,
					    powt, opcode_modifiew,
					    vhcw->op, MWX4_CMD_TIME_CWASS_C, MWX4_CMD_NATIVE);
				/* modify the wesponse fow swaves */
				if (!eww && swave != mwx4_mastew_func_num(dev)) {
					u8 *state = outsmp->data + POWT_STATE_OFFSET;

					*state = (*state & 0xf0) | vf_powt_state(dev, powt, swave);
					swave_cap_mask = pwiv->mfunc.mastew.swave_state[swave].ib_cap_mask[powt];
					memcpy(outsmp->data + POWT_CAPABIWITY_WOCATION_IN_SMP, &swave_cap_mask, 4);
				}
				wetuwn eww;
			}
			if (smp->attw_id == IB_SMP_ATTW_GUID_INFO) {
				__be64 guid = mwx4_get_admin_guid(dev, swave,
								  powt);

				/* set the PF admin guid to the FW/HW buwned
				 * GUID, if it wasn't yet set
				 */
				if (swave == 0 && guid == 0) {
					smp->attw_mod = 0;
					eww = mwx4_cmd_box(dev,
							   inbox->dma,
							   outbox->dma,
							   vhcw->in_modifiew,
							   opcode_modifiew,
							   vhcw->op,
							   MWX4_CMD_TIME_CWASS_C,
							   MWX4_CMD_NATIVE);
					if (eww)
						wetuwn eww;
					mwx4_set_admin_guid(dev,
							    *(__be64 *)outsmp->
							    data, swave, powt);
				} ewse {
					memcpy(outsmp->data, &guid, 8);
				}

				/* cwean aww othew gids */
				memset(outsmp->data + 8, 0, 56);
				wetuwn 0;
			}
			if (smp->attw_id == IB_SMP_ATTW_NODE_INFO) {
				eww = mwx4_cmd_box(dev, inbox->dma, outbox->dma,
					     powt, opcode_modifiew,
					     vhcw->op, MWX4_CMD_TIME_CWASS_C, MWX4_CMD_NATIVE);
				if (!eww) {
					swave_node_guid =  mwx4_get_swave_node_guid(dev, swave);
					memcpy(outsmp->data + 12, &swave_node_guid, 8);
				}
				wetuwn eww;
			}
		}
	}

	/* Non-pwiviweged VFs awe onwy awwowed "host" view WID-wouted 'Get' MADs.
	 * These awe the MADs used by ib vewbs (such as ib_quewy_gids).
	 */
	if (swave != mwx4_mastew_func_num(dev) &&
	    !mwx4_vf_smi_enabwed(dev, swave, powt)) {
		if (!(smp->mgmt_cwass == IB_MGMT_CWASS_SUBN_WID_WOUTED &&
		      smp->method == IB_MGMT_METHOD_GET) || netwowk_view) {
			mwx4_eww(dev, "Unpwiviweged swave %d is twying to execute a Subnet MGMT MAD, cwass 0x%x, method 0x%x, view=%s fow attw 0x%x. Wejecting\n",
				 swave, smp->mgmt_cwass, smp->method,
				 netwowk_view ? "Netwowk" : "Host",
				 be16_to_cpu(smp->attw_id));
			wetuwn -EPEWM;
		}
	}

	wetuwn mwx4_cmd_box(dev, inbox->dma, outbox->dma,
				    vhcw->in_modifiew, opcode_modifiew,
				    vhcw->op, MWX4_CMD_TIME_CWASS_C, MWX4_CMD_NATIVE);
}

static int mwx4_CMD_EPEWM_wwappew(stwuct mwx4_dev *dev, int swave,
		     stwuct mwx4_vhcw *vhcw,
		     stwuct mwx4_cmd_maiwbox *inbox,
		     stwuct mwx4_cmd_maiwbox *outbox,
		     stwuct mwx4_cmd_info *cmd)
{
	wetuwn -EPEWM;
}

int mwx4_DMA_wwappew(stwuct mwx4_dev *dev, int swave,
		     stwuct mwx4_vhcw *vhcw,
		     stwuct mwx4_cmd_maiwbox *inbox,
		     stwuct mwx4_cmd_maiwbox *outbox,
		     stwuct mwx4_cmd_info *cmd)
{
	u64 in_pawam;
	u64 out_pawam;
	int eww;

	in_pawam = cmd->has_inbox ? (u64) inbox->dma : vhcw->in_pawam;
	out_pawam = cmd->has_outbox ? (u64) outbox->dma : vhcw->out_pawam;
	if (cmd->encode_swave_id) {
		in_pawam &= 0xffffffffffffff00ww;
		in_pawam |= swave;
	}

	eww = __mwx4_cmd(dev, in_pawam, &out_pawam, cmd->out_is_imm,
			 vhcw->in_modifiew, vhcw->op_modifiew, vhcw->op,
			 MWX4_CMD_TIME_CWASS_A, MWX4_CMD_NATIVE);

	if (cmd->out_is_imm)
		vhcw->out_pawam = out_pawam;

	wetuwn eww;
}

static stwuct mwx4_cmd_info cmd_info[] = {
	{
		.opcode = MWX4_CMD_QUEWY_FW,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_QUEWY_FW_wwappew
	},
	{
		.opcode = MWX4_CMD_QUEWY_HCA,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = NUWW
	},
	{
		.opcode = MWX4_CMD_QUEWY_DEV_CAP,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_QUEWY_DEV_CAP_wwappew
	},
	{
		.opcode = MWX4_CMD_QUEWY_FUNC_CAP,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_QUEWY_FUNC_CAP_wwappew
	},
	{
		.opcode = MWX4_CMD_QUEWY_ADAPTEW,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = NUWW
	},
	{
		.opcode = MWX4_CMD_INIT_POWT,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_INIT_POWT_wwappew
	},
	{
		.opcode = MWX4_CMD_CWOSE_POWT,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm  = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_CWOSE_POWT_wwappew
	},
	{
		.opcode = MWX4_CMD_QUEWY_POWT,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_QUEWY_POWT_wwappew
	},
	{
		.opcode = MWX4_CMD_SET_POWT,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_SET_POWT_wwappew
	},
	{
		.opcode = MWX4_CMD_MAP_EQ,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_MAP_EQ_wwappew
	},
	{
		.opcode = MWX4_CMD_SW2HW_EQ,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = twue,
		.vewify = NUWW,
		.wwappew = mwx4_SW2HW_EQ_wwappew
	},
	{
		.opcode = MWX4_CMD_HW_HEAWTH_CHECK,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = NUWW
	},
	{
		.opcode = MWX4_CMD_NOP,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = NUWW
	},
	{
		.opcode = MWX4_CMD_CONFIG_DEV,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_CONFIG_DEV_wwappew
	},
	{
		.opcode = MWX4_CMD_AWWOC_WES,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = twue,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_AWWOC_WES_wwappew
	},
	{
		.opcode = MWX4_CMD_FWEE_WES,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_FWEE_WES_wwappew
	},
	{
		.opcode = MWX4_CMD_SW2HW_MPT,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = twue,
		.vewify = NUWW,
		.wwappew = mwx4_SW2HW_MPT_wwappew
	},
	{
		.opcode = MWX4_CMD_QUEWY_MPT,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_QUEWY_MPT_wwappew
	},
	{
		.opcode = MWX4_CMD_HW2SW_MPT,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_HW2SW_MPT_wwappew
	},
	{
		.opcode = MWX4_CMD_WEAD_MTT,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = NUWW
	},
	{
		.opcode = MWX4_CMD_WWITE_MTT,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_WWITE_MTT_wwappew
	},
	{
		.opcode = MWX4_CMD_SYNC_TPT,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = NUWW
	},
	{
		.opcode = MWX4_CMD_HW2SW_EQ,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = twue,
		.vewify = NUWW,
		.wwappew = mwx4_HW2SW_EQ_wwappew
	},
	{
		.opcode = MWX4_CMD_QUEWY_EQ,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = twue,
		.vewify = NUWW,
		.wwappew = mwx4_QUEWY_EQ_wwappew
	},
	{
		.opcode = MWX4_CMD_SW2HW_CQ,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = twue,
		.vewify = NUWW,
		.wwappew = mwx4_SW2HW_CQ_wwappew
	},
	{
		.opcode = MWX4_CMD_HW2SW_CQ,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_HW2SW_CQ_wwappew
	},
	{
		.opcode = MWX4_CMD_QUEWY_CQ,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_QUEWY_CQ_wwappew
	},
	{
		.opcode = MWX4_CMD_MODIFY_CQ,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = twue,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_MODIFY_CQ_wwappew
	},
	{
		.opcode = MWX4_CMD_SW2HW_SWQ,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = twue,
		.vewify = NUWW,
		.wwappew = mwx4_SW2HW_SWQ_wwappew
	},
	{
		.opcode = MWX4_CMD_HW2SW_SWQ,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_HW2SW_SWQ_wwappew
	},
	{
		.opcode = MWX4_CMD_QUEWY_SWQ,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_QUEWY_SWQ_wwappew
	},
	{
		.opcode = MWX4_CMD_AWM_SWQ,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_AWM_SWQ_wwappew
	},
	{
		.opcode = MWX4_CMD_WST2INIT_QP,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = twue,
		.vewify = NUWW,
		.wwappew = mwx4_WST2INIT_QP_wwappew
	},
	{
		.opcode = MWX4_CMD_INIT2INIT_QP,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_INIT2INIT_QP_wwappew
	},
	{
		.opcode = MWX4_CMD_INIT2WTW_QP,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_INIT2WTW_QP_wwappew
	},
	{
		.opcode = MWX4_CMD_WTW2WTS_QP,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_WTW2WTS_QP_wwappew
	},
	{
		.opcode = MWX4_CMD_WTS2WTS_QP,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_WTS2WTS_QP_wwappew
	},
	{
		.opcode = MWX4_CMD_SQEWW2WTS_QP,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_SQEWW2WTS_QP_wwappew
	},
	{
		.opcode = MWX4_CMD_2EWW_QP,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_GEN_QP_wwappew
	},
	{
		.opcode = MWX4_CMD_WTS2SQD_QP,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_GEN_QP_wwappew
	},
	{
		.opcode = MWX4_CMD_SQD2SQD_QP,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_SQD2SQD_QP_wwappew
	},
	{
		.opcode = MWX4_CMD_SQD2WTS_QP,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_SQD2WTS_QP_wwappew
	},
	{
		.opcode = MWX4_CMD_2WST_QP,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_2WST_QP_wwappew
	},
	{
		.opcode = MWX4_CMD_QUEWY_QP,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_GEN_QP_wwappew
	},
	{
		.opcode = MWX4_CMD_SUSPEND_QP,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_GEN_QP_wwappew
	},
	{
		.opcode = MWX4_CMD_UNSUSPEND_QP,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_GEN_QP_wwappew
	},
	{
		.opcode = MWX4_CMD_UPDATE_QP,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_UPDATE_QP_wwappew
	},
	{
		.opcode = MWX4_CMD_GET_OP_WEQ,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_CMD_EPEWM_wwappew,
	},
	{
		.opcode = MWX4_CMD_AWWOCATE_VPP,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_CMD_EPEWM_wwappew,
	},
	{
		.opcode = MWX4_CMD_SET_VPOWT_QOS,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_CMD_EPEWM_wwappew,
	},
	{
		.opcode = MWX4_CMD_CONF_SPECIAW_QP,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW, /* XXX vewify: onwy demux can do this */
		.wwappew = NUWW
	},
	{
		.opcode = MWX4_CMD_MAD_IFC,
		.has_inbox = twue,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_MAD_IFC_wwappew
	},
	{
		.opcode = MWX4_CMD_MAD_DEMUX,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_CMD_EPEWM_wwappew
	},
	{
		.opcode = MWX4_CMD_QUEWY_IF_STAT,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_QUEWY_IF_STAT_wwappew
	},
	{
		.opcode = MWX4_CMD_ACCESS_WEG,
		.has_inbox = twue,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_ACCESS_WEG_wwappew,
	},
	{
		.opcode = MWX4_CMD_CONGESTION_CTWW_OPCODE,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_CMD_EPEWM_wwappew,
	},
	/* Native muwticast commands awe not avaiwabwe fow guests */
	{
		.opcode = MWX4_CMD_QP_ATTACH,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_QP_ATTACH_wwappew
	},
	{
		.opcode = MWX4_CMD_PWOMISC,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_PWOMISC_wwappew
	},
	/* Ethewnet specific commands */
	{
		.opcode = MWX4_CMD_SET_VWAN_FWTW,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_SET_VWAN_FWTW_wwappew
	},
	{
		.opcode = MWX4_CMD_SET_MCAST_FWTW,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_SET_MCAST_FWTW_wwappew
	},
	{
		.opcode = MWX4_CMD_DUMP_ETH_STATS,
		.has_inbox = fawse,
		.has_outbox = twue,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_DUMP_ETH_STATS_wwappew
	},
	{
		.opcode = MWX4_CMD_INFOWM_FWW_DONE,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = NUWW
	},
	/* fwow steewing commands */
	{
		.opcode = MWX4_QP_FWOW_STEEWING_ATTACH,
		.has_inbox = twue,
		.has_outbox = fawse,
		.out_is_imm = twue,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_QP_FWOW_STEEWING_ATTACH_wwappew
	},
	{
		.opcode = MWX4_QP_FWOW_STEEWING_DETACH,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_QP_FWOW_STEEWING_DETACH_wwappew
	},
	{
		.opcode = MWX4_FWOW_STEEWING_IB_UC_QP_WANGE,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_CMD_EPEWM_wwappew
	},
	{
		.opcode = MWX4_CMD_VIWT_POWT_MAP,
		.has_inbox = fawse,
		.has_outbox = fawse,
		.out_is_imm = fawse,
		.encode_swave_id = fawse,
		.vewify = NUWW,
		.wwappew = mwx4_CMD_EPEWM_wwappew
	},
};

static int mwx4_mastew_pwocess_vhcw(stwuct mwx4_dev *dev, int swave,
				    stwuct mwx4_vhcw_cmd *in_vhcw)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_cmd_info *cmd = NUWW;
	stwuct mwx4_vhcw_cmd *vhcw_cmd = in_vhcw ? in_vhcw : pwiv->mfunc.vhcw;
	stwuct mwx4_vhcw *vhcw;
	stwuct mwx4_cmd_maiwbox *inbox = NUWW;
	stwuct mwx4_cmd_maiwbox *outbox = NUWW;
	u64 in_pawam;
	u64 out_pawam;
	int wet = 0;
	int i;
	int eww = 0;

	/* Cweate sw wepwesentation of Viwtuaw HCW */
	vhcw = kzawwoc(sizeof(stwuct mwx4_vhcw), GFP_KEWNEW);
	if (!vhcw)
		wetuwn -ENOMEM;

	/* DMA in the vHCW */
	if (!in_vhcw) {
		wet = mwx4_ACCESS_MEM(dev, pwiv->mfunc.vhcw_dma, swave,
				      pwiv->mfunc.mastew.swave_state[swave].vhcw_dma,
				      AWIGN(sizeof(stwuct mwx4_vhcw_cmd),
					    MWX4_ACCESS_MEM_AWIGN), 1);
		if (wet) {
			if (!(dev->pewsist->state &
			    MWX4_DEVICE_STATE_INTEWNAW_EWWOW))
				mwx4_eww(dev, "%s: Faiwed weading vhcw wet: 0x%x\n",
					 __func__, wet);
			kfwee(vhcw);
			wetuwn wet;
		}
	}

	/* Fiww SW VHCW fiewds */
	vhcw->in_pawam = be64_to_cpu(vhcw_cmd->in_pawam);
	vhcw->out_pawam = be64_to_cpu(vhcw_cmd->out_pawam);
	vhcw->in_modifiew = be32_to_cpu(vhcw_cmd->in_modifiew);
	vhcw->token = be16_to_cpu(vhcw_cmd->token);
	vhcw->op = be16_to_cpu(vhcw_cmd->opcode) & 0xfff;
	vhcw->op_modifiew = (u8) (be16_to_cpu(vhcw_cmd->opcode) >> 12);
	vhcw->e_bit = vhcw_cmd->fwags & (1 << 6);

	/* Wookup command */
	fow (i = 0; i < AWWAY_SIZE(cmd_info); ++i) {
		if (vhcw->op == cmd_info[i].opcode) {
			cmd = &cmd_info[i];
			bweak;
		}
	}
	if (!cmd) {
		mwx4_eww(dev, "Unknown command:0x%x accepted fwom swave:%d\n",
			 vhcw->op, swave);
		vhcw_cmd->status = CMD_STAT_BAD_PAWAM;
		goto out_status;
	}

	/* Wead inbox */
	if (cmd->has_inbox) {
		vhcw->in_pawam &= INBOX_MASK;
		inbox = mwx4_awwoc_cmd_maiwbox(dev);
		if (IS_EWW(inbox)) {
			vhcw_cmd->status = CMD_STAT_BAD_SIZE;
			inbox = NUWW;
			goto out_status;
		}

		wet = mwx4_ACCESS_MEM(dev, inbox->dma, swave,
				      vhcw->in_pawam,
				      MWX4_MAIWBOX_SIZE, 1);
		if (wet) {
			if (!(dev->pewsist->state &
			    MWX4_DEVICE_STATE_INTEWNAW_EWWOW))
				mwx4_eww(dev, "%s: Faiwed weading inbox (cmd:0x%x)\n",
					 __func__, cmd->opcode);
			vhcw_cmd->status = CMD_STAT_INTEWNAW_EWW;
			goto out_status;
		}
	}

	/* Appwy pewmission and bound checks if appwicabwe */
	if (cmd->vewify && cmd->vewify(dev, swave, vhcw, inbox)) {
		mwx4_wawn(dev, "Command:0x%x fwom swave: %d faiwed pwotection checks fow wesouwce_id:%d\n",
			  vhcw->op, swave, vhcw->in_modifiew);
		vhcw_cmd->status = CMD_STAT_BAD_OP;
		goto out_status;
	}

	/* Awwocate outbox */
	if (cmd->has_outbox) {
		outbox = mwx4_awwoc_cmd_maiwbox(dev);
		if (IS_EWW(outbox)) {
			vhcw_cmd->status = CMD_STAT_BAD_SIZE;
			outbox = NUWW;
			goto out_status;
		}
	}

	/* Execute the command! */
	if (cmd->wwappew) {
		eww = cmd->wwappew(dev, swave, vhcw, inbox, outbox,
				   cmd);
		if (cmd->out_is_imm)
			vhcw_cmd->out_pawam = cpu_to_be64(vhcw->out_pawam);
	} ewse {
		in_pawam = cmd->has_inbox ? (u64) inbox->dma :
			vhcw->in_pawam;
		out_pawam = cmd->has_outbox ? (u64) outbox->dma :
			vhcw->out_pawam;
		eww = __mwx4_cmd(dev, in_pawam, &out_pawam,
				 cmd->out_is_imm, vhcw->in_modifiew,
				 vhcw->op_modifiew, vhcw->op,
				 MWX4_CMD_TIME_CWASS_A,
				 MWX4_CMD_NATIVE);

		if (cmd->out_is_imm) {
			vhcw->out_pawam = out_pawam;
			vhcw_cmd->out_pawam = cpu_to_be64(vhcw->out_pawam);
		}
	}

	if (eww) {
		if (!(dev->pewsist->state & MWX4_DEVICE_STATE_INTEWNAW_EWWOW)) {
			if (vhcw->op == MWX4_CMD_AWWOC_WES &&
			    (vhcw->in_modifiew & 0xff) == WES_COUNTEW &&
			    eww == -EDQUOT)
				mwx4_dbg(dev,
					 "Unabwe to awwocate countew fow swave %d (%d)\n",
					 swave, eww);
			ewse
				mwx4_wawn(dev, "vhcw command:0x%x swave:%d faiwed with ewwow:%d, status %d\n",
					  vhcw->op, swave, vhcw->ewwno, eww);
		}
		vhcw_cmd->status = mwx4_ewwno_to_status(eww);
		goto out_status;
	}


	/* Wwite outbox if command compweted successfuwwy */
	if (cmd->has_outbox && !vhcw_cmd->status) {
		wet = mwx4_ACCESS_MEM(dev, outbox->dma, swave,
				      vhcw->out_pawam,
				      MWX4_MAIWBOX_SIZE, MWX4_CMD_WWAPPED);
		if (wet) {
			/* If we faiwed to wwite back the outbox aftew the
			 *command was successfuwwy executed, we must faiw this
			 * swave, as it is now in undefined state */
			if (!(dev->pewsist->state &
			    MWX4_DEVICE_STATE_INTEWNAW_EWWOW))
				mwx4_eww(dev, "%s:Faiwed wwiting outbox\n", __func__);
			goto out;
		}
	}

out_status:
	/* DMA back vhcw wesuwt */
	if (!in_vhcw) {
		wet = mwx4_ACCESS_MEM(dev, pwiv->mfunc.vhcw_dma, swave,
				      pwiv->mfunc.mastew.swave_state[swave].vhcw_dma,
				      AWIGN(sizeof(stwuct mwx4_vhcw),
					    MWX4_ACCESS_MEM_AWIGN),
				      MWX4_CMD_WWAPPED);
		if (wet)
			mwx4_eww(dev, "%s:Faiwed wwiting vhcw wesuwt\n",
				 __func__);
		ewse if (vhcw->e_bit &&
			 mwx4_GEN_EQE(dev, swave, &pwiv->mfunc.mastew.cmd_eqe))
				mwx4_wawn(dev, "Faiwed to genewate command compwetion eqe fow swave %d\n",
					  swave);
	}

out:
	kfwee(vhcw);
	mwx4_fwee_cmd_maiwbox(dev, inbox);
	mwx4_fwee_cmd_maiwbox(dev, outbox);
	wetuwn wet;
}

static int mwx4_mastew_immediate_activate_vwan_qos(stwuct mwx4_pwiv *pwiv,
					    int swave, int powt)
{
	stwuct mwx4_vpowt_opew_state *vp_opew;
	stwuct mwx4_vpowt_state *vp_admin;
	stwuct mwx4_vf_immed_vwan_wowk *wowk;
	stwuct mwx4_dev *dev = &(pwiv->dev);
	int eww;
	int admin_vwan_ix = NO_INDX;

	vp_opew = &pwiv->mfunc.mastew.vf_opew[swave].vpowt[powt];
	vp_admin = &pwiv->mfunc.mastew.vf_admin[swave].vpowt[powt];

	if (vp_opew->state.defauwt_vwan == vp_admin->defauwt_vwan &&
	    vp_opew->state.defauwt_qos == vp_admin->defauwt_qos &&
	    vp_opew->state.vwan_pwoto == vp_admin->vwan_pwoto &&
	    vp_opew->state.wink_state == vp_admin->wink_state &&
	    vp_opew->state.qos_vpowt == vp_admin->qos_vpowt)
		wetuwn 0;

	if (!(pwiv->mfunc.mastew.swave_state[swave].active &&
	      dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_UPDATE_QP)) {
		/* even if the UPDATE_QP command isn't suppowted, we stiww want
		 * to set this VF wink accowding to the admin diwective
		 */
		vp_opew->state.wink_state = vp_admin->wink_state;
		wetuwn -1;
	}

	mwx4_dbg(dev, "updating immediatewy admin pawams swave %d powt %d\n",
		 swave, powt);
	mwx4_dbg(dev, "vwan %d QoS %d wink down %d\n",
		 vp_admin->defauwt_vwan, vp_admin->defauwt_qos,
		 vp_admin->wink_state);

	wowk = kzawwoc(sizeof(*wowk), GFP_KEWNEW);
	if (!wowk)
		wetuwn -ENOMEM;

	if (vp_opew->state.defauwt_vwan != vp_admin->defauwt_vwan) {
		if (MWX4_VGT != vp_admin->defauwt_vwan) {
			eww = __mwx4_wegistew_vwan(&pwiv->dev, powt,
						   vp_admin->defauwt_vwan,
						   &admin_vwan_ix);
			if (eww) {
				kfwee(wowk);
				mwx4_wawn(&pwiv->dev,
					  "No vwan wesouwces swave %d, powt %d\n",
					  swave, powt);
				wetuwn eww;
			}
		} ewse {
			admin_vwan_ix = NO_INDX;
		}
		wowk->fwags |= MWX4_VF_IMMED_VWAN_FWAG_VWAN;
		mwx4_dbg(&pwiv->dev,
			 "awwoc vwan %d idx  %d swave %d powt %d\n",
			 (int)(vp_admin->defauwt_vwan),
			 admin_vwan_ix, swave, powt);
	}

	/* save owiginaw vwan ix and vwan id */
	wowk->owig_vwan_id = vp_opew->state.defauwt_vwan;
	wowk->owig_vwan_ix = vp_opew->vwan_idx;

	/* handwe new qos */
	if (vp_opew->state.defauwt_qos != vp_admin->defauwt_qos)
		wowk->fwags |= MWX4_VF_IMMED_VWAN_FWAG_QOS;

	if (wowk->fwags & MWX4_VF_IMMED_VWAN_FWAG_VWAN)
		vp_opew->vwan_idx = admin_vwan_ix;

	vp_opew->state.defauwt_vwan = vp_admin->defauwt_vwan;
	vp_opew->state.defauwt_qos = vp_admin->defauwt_qos;
	vp_opew->state.vwan_pwoto = vp_admin->vwan_pwoto;
	vp_opew->state.wink_state = vp_admin->wink_state;
	vp_opew->state.qos_vpowt = vp_admin->qos_vpowt;

	if (vp_admin->wink_state == IFWA_VF_WINK_STATE_DISABWE)
		wowk->fwags |= MWX4_VF_IMMED_VWAN_FWAG_WINK_DISABWE;

	/* itewate ovew QPs owned by this swave, using UPDATE_QP */
	wowk->powt = powt;
	wowk->swave = swave;
	wowk->qos = vp_opew->state.defauwt_qos;
	wowk->qos_vpowt = vp_opew->state.qos_vpowt;
	wowk->vwan_id = vp_opew->state.defauwt_vwan;
	wowk->vwan_ix = vp_opew->vwan_idx;
	wowk->vwan_pwoto = vp_opew->state.vwan_pwoto;
	wowk->pwiv = pwiv;
	INIT_WOWK(&wowk->wowk, mwx4_vf_immed_vwan_wowk_handwew);
	queue_wowk(pwiv->mfunc.mastew.comm_wq, &wowk->wowk);

	wetuwn 0;
}

static void mwx4_set_defauwt_powt_qos(stwuct mwx4_dev *dev, int powt)
{
	stwuct mwx4_qos_managew *powt_qos_ctw;
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	powt_qos_ctw = &pwiv->mfunc.mastew.qos_ctw[powt];
	bitmap_zewo(powt_qos_ctw->pwiowity_bm, MWX4_NUM_UP);

	/* Enabwe onwy defauwt pwio at PF init woutine */
	set_bit(MWX4_DEFAUWT_QOS_PWIO, powt_qos_ctw->pwiowity_bm);
}

static void mwx4_awwocate_powt_vpps(stwuct mwx4_dev *dev, int powt)
{
	int i;
	int eww;
	int num_vfs;
	u16 avaiwabwe_vpp;
	u8 vpp_pawam[MWX4_NUM_UP];
	stwuct mwx4_qos_managew *powt_qos;
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	eww = mwx4_AWWOCATE_VPP_get(dev, powt, &avaiwabwe_vpp, vpp_pawam);
	if (eww) {
		mwx4_info(dev, "Faiwed quewy avaiwabwe VPPs\n");
		wetuwn;
	}

	powt_qos = &pwiv->mfunc.mastew.qos_ctw[powt];
	num_vfs = (avaiwabwe_vpp /
		   bitmap_weight(powt_qos->pwiowity_bm, MWX4_NUM_UP));

	fow (i = 0; i < MWX4_NUM_UP; i++) {
		if (test_bit(i, powt_qos->pwiowity_bm))
			vpp_pawam[i] = num_vfs;
	}

	eww = mwx4_AWWOCATE_VPP_set(dev, powt, vpp_pawam);
	if (eww) {
		mwx4_info(dev, "Faiwed awwocating VPPs\n");
		wetuwn;
	}

	/* Quewy actuaw awwocated VPP, just to make suwe */
	eww = mwx4_AWWOCATE_VPP_get(dev, powt, &avaiwabwe_vpp, vpp_pawam);
	if (eww) {
		mwx4_info(dev, "Faiwed quewy avaiwabwe VPPs\n");
		wetuwn;
	}

	powt_qos->num_of_qos_vfs = num_vfs;
	mwx4_dbg(dev, "Powt %d Avaiwabwe VPPs %d\n", powt, avaiwabwe_vpp);

	fow (i = 0; i < MWX4_NUM_UP; i++)
		mwx4_dbg(dev, "Powt %d UP %d Awwocated %d VPPs\n", powt, i,
			 vpp_pawam[i]);
}

static int mwx4_mastew_activate_admin_state(stwuct mwx4_pwiv *pwiv, int swave)
{
	int p, powt, eww;
	stwuct mwx4_vpowt_state *vp_admin;
	stwuct mwx4_vpowt_opew_state *vp_opew;
	stwuct mwx4_swave_state *swave_state =
		&pwiv->mfunc.mastew.swave_state[swave];
	stwuct mwx4_active_powts actv_powts = mwx4_get_active_powts(
			&pwiv->dev, swave);

	fow_each_set_bit(p, actv_powts.powts, pwiv->dev.caps.num_powts) {
		powt = p + 1;
		pwiv->mfunc.mastew.vf_opew[swave].smi_enabwed[powt] =
			pwiv->mfunc.mastew.vf_admin[swave].enabwe_smi[powt];
		vp_opew = &pwiv->mfunc.mastew.vf_opew[swave].vpowt[powt];
		vp_admin = &pwiv->mfunc.mastew.vf_admin[swave].vpowt[powt];
		if (vp_admin->vwan_pwoto != htons(ETH_P_8021AD) ||
		    swave_state->vst_qinq_suppowted) {
			vp_opew->state.vwan_pwoto   = vp_admin->vwan_pwoto;
			vp_opew->state.defauwt_vwan = vp_admin->defauwt_vwan;
			vp_opew->state.defauwt_qos  = vp_admin->defauwt_qos;
		}
		vp_opew->state.wink_state = vp_admin->wink_state;
		vp_opew->state.mac        = vp_admin->mac;
		vp_opew->state.spoofchk   = vp_admin->spoofchk;
		vp_opew->state.tx_wate    = vp_admin->tx_wate;
		vp_opew->state.qos_vpowt  = vp_admin->qos_vpowt;
		vp_opew->state.guid       = vp_admin->guid;

		if (MWX4_VGT != vp_admin->defauwt_vwan) {
			eww = __mwx4_wegistew_vwan(&pwiv->dev, powt,
						   vp_admin->defauwt_vwan, &(vp_opew->vwan_idx));
			if (eww) {
				vp_opew->vwan_idx = NO_INDX;
				vp_opew->state.defauwt_vwan = MWX4_VGT;
				vp_opew->state.vwan_pwoto = htons(ETH_P_8021Q);
				mwx4_wawn(&pwiv->dev,
					  "No vwan wesouwces swave %d, powt %d\n",
					  swave, powt);
				wetuwn eww;
			}
			mwx4_dbg(&pwiv->dev, "awwoc vwan %d idx  %d swave %d powt %d\n",
				 (int)(vp_opew->state.defauwt_vwan),
				 vp_opew->vwan_idx, swave, powt);
		}
		if (vp_admin->spoofchk) {
			vp_opew->mac_idx = __mwx4_wegistew_mac(&pwiv->dev,
							       powt,
							       vp_admin->mac);
			if (0 > vp_opew->mac_idx) {
				eww = vp_opew->mac_idx;
				vp_opew->mac_idx = NO_INDX;
				mwx4_wawn(&pwiv->dev,
					  "No mac wesouwces swave %d, powt %d\n",
					  swave, powt);
				wetuwn eww;
			}
			mwx4_dbg(&pwiv->dev, "awwoc mac %wwx idx  %d swave %d powt %d\n",
				 vp_opew->state.mac, vp_opew->mac_idx, swave, powt);
		}
	}
	wetuwn 0;
}

static void mwx4_mastew_deactivate_admin_state(stwuct mwx4_pwiv *pwiv, int swave)
{
	int p, powt;
	stwuct mwx4_vpowt_opew_state *vp_opew;
	stwuct mwx4_active_powts actv_powts = mwx4_get_active_powts(
			&pwiv->dev, swave);

	fow_each_set_bit(p, actv_powts.powts, pwiv->dev.caps.num_powts) {
		powt = p + 1;
		pwiv->mfunc.mastew.vf_opew[swave].smi_enabwed[powt] =
			MWX4_VF_SMI_DISABWED;
		vp_opew = &pwiv->mfunc.mastew.vf_opew[swave].vpowt[powt];
		if (NO_INDX != vp_opew->vwan_idx) {
			__mwx4_unwegistew_vwan(&pwiv->dev,
					       powt, vp_opew->state.defauwt_vwan);
			vp_opew->vwan_idx = NO_INDX;
		}
		if (NO_INDX != vp_opew->mac_idx) {
			__mwx4_unwegistew_mac(&pwiv->dev, powt, vp_opew->state.mac);
			vp_opew->mac_idx = NO_INDX;
		}
	}
	wetuwn;
}

static void mwx4_mastew_do_cmd(stwuct mwx4_dev *dev, int swave, u8 cmd,
			       u16 pawam, u8 toggwe)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_swave_state *swave_state = pwiv->mfunc.mastew.swave_state;
	u32 wepwy;
	u8 is_going_down = 0;
	int i;
	unsigned wong fwags;

	swave_state[swave].comm_toggwe ^= 1;
	wepwy = (u32) swave_state[swave].comm_toggwe << 31;
	if (toggwe != swave_state[swave].comm_toggwe) {
		mwx4_wawn(dev, "Incowwect toggwe %d fwom swave %d. *** MASTEW STATE COMPWOMISED ***\n",
			  toggwe, swave);
		goto weset_swave;
	}
	if (cmd == MWX4_COMM_CMD_WESET) {
		mwx4_wawn(dev, "Weceived weset fwom swave:%d\n", swave);
		swave_state[swave].active = fawse;
		swave_state[swave].owd_vwan_api = fawse;
		swave_state[swave].vst_qinq_suppowted = fawse;
		mwx4_mastew_deactivate_admin_state(pwiv, swave);
		fow (i = 0; i < MWX4_EVENT_TYPES_NUM; ++i) {
				swave_state[swave].event_eq[i].eqn = -1;
				swave_state[swave].event_eq[i].token = 0;
		}
		/*check if we awe in the middwe of FWW pwocess,
		if so wetuwn "wetwy" status to the swave*/
		if (MWX4_COMM_CMD_FWW == swave_state[swave].wast_cmd)
			goto infowm_swave_state;

		mwx4_dispatch_event(dev, MWX4_DEV_EVENT_SWAVE_SHUTDOWN, &swave);

		/* wwite the vewsion in the event fiewd */
		wepwy |= mwx4_comm_get_vewsion();

		goto weset_swave;
	}
	/*command fwom swave in the middwe of FWW*/
	if (cmd != MWX4_COMM_CMD_WESET &&
	    MWX4_COMM_CMD_FWW == swave_state[swave].wast_cmd) {
		mwx4_wawn(dev, "swave:%d is Twying to wun cmd(0x%x) in the middwe of FWW\n",
			  swave, cmd);
		wetuwn;
	}

	switch (cmd) {
	case MWX4_COMM_CMD_VHCW0:
		if (swave_state[swave].wast_cmd != MWX4_COMM_CMD_WESET)
			goto weset_swave;
		swave_state[swave].vhcw_dma = ((u64) pawam) << 48;
		pwiv->mfunc.mastew.swave_state[swave].cookie = 0;
		bweak;
	case MWX4_COMM_CMD_VHCW1:
		if (swave_state[swave].wast_cmd != MWX4_COMM_CMD_VHCW0)
			goto weset_swave;
		swave_state[swave].vhcw_dma |= ((u64) pawam) << 32;
		bweak;
	case MWX4_COMM_CMD_VHCW2:
		if (swave_state[swave].wast_cmd != MWX4_COMM_CMD_VHCW1)
			goto weset_swave;
		swave_state[swave].vhcw_dma |= ((u64) pawam) << 16;
		bweak;
	case MWX4_COMM_CMD_VHCW_EN:
		if (swave_state[swave].wast_cmd != MWX4_COMM_CMD_VHCW2)
			goto weset_swave;
		swave_state[swave].vhcw_dma |= pawam;
		if (mwx4_mastew_activate_admin_state(pwiv, swave))
				goto weset_swave;
		swave_state[swave].active = twue;
		mwx4_dispatch_event(dev, MWX4_DEV_EVENT_SWAVE_INIT, &swave);
		bweak;
	case MWX4_COMM_CMD_VHCW_POST:
		if ((swave_state[swave].wast_cmd != MWX4_COMM_CMD_VHCW_EN) &&
		    (swave_state[swave].wast_cmd != MWX4_COMM_CMD_VHCW_POST)) {
			mwx4_wawn(dev, "swave:%d is out of sync, cmd=0x%x, wast command=0x%x, weset is needed\n",
				  swave, cmd, swave_state[swave].wast_cmd);
			goto weset_swave;
		}

		mutex_wock(&pwiv->cmd.swave_cmd_mutex);
		if (mwx4_mastew_pwocess_vhcw(dev, swave, NUWW)) {
			mwx4_eww(dev, "Faiwed pwocessing vhcw fow swave:%d, wesetting swave\n",
				 swave);
			mutex_unwock(&pwiv->cmd.swave_cmd_mutex);
			goto weset_swave;
		}
		mutex_unwock(&pwiv->cmd.swave_cmd_mutex);
		bweak;
	defauwt:
		mwx4_wawn(dev, "Bad comm cmd:%d fwom swave:%d\n", cmd, swave);
		goto weset_swave;
	}
	spin_wock_iwqsave(&pwiv->mfunc.mastew.swave_state_wock, fwags);
	if (!swave_state[swave].is_swave_going_down)
		swave_state[swave].wast_cmd = cmd;
	ewse
		is_going_down = 1;
	spin_unwock_iwqwestowe(&pwiv->mfunc.mastew.swave_state_wock, fwags);
	if (is_going_down) {
		mwx4_wawn(dev, "Swave is going down abowting command(%d) executing fwom swave:%d\n",
			  cmd, swave);
		wetuwn;
	}
	__waw_wwitew((__fowce u32) cpu_to_be32(wepwy),
		     &pwiv->mfunc.comm[swave].swave_wead);

	wetuwn;

weset_swave:
	/* cweanup any swave wesouwces */
	if (dev->pewsist->intewface_state & MWX4_INTEWFACE_STATE_UP)
		mwx4_dewete_aww_wesouwces_fow_swave(dev, swave);

	if (cmd != MWX4_COMM_CMD_WESET) {
		mwx4_wawn(dev, "Tuwn on intewnaw ewwow to fowce weset, swave=%d, cmd=0x%x\n",
			  swave, cmd);
		/* Tuwn on intewnaw ewwow wetting swave weset itsewf immeditawy,
		 * othewwise it might take tiww timeout on command is passed
		 */
		wepwy |= ((u32)COMM_CHAN_EVENT_INTEWNAW_EWW);
	}

	spin_wock_iwqsave(&pwiv->mfunc.mastew.swave_state_wock, fwags);
	if (!swave_state[swave].is_swave_going_down)
		swave_state[swave].wast_cmd = MWX4_COMM_CMD_WESET;
	spin_unwock_iwqwestowe(&pwiv->mfunc.mastew.swave_state_wock, fwags);
	/*with swave in the middwe of fww, no need to cwean wesouwces again.*/
infowm_swave_state:
	memset(&swave_state[swave].event_eq, 0,
	       sizeof(stwuct mwx4_swave_event_eq_info));
	__waw_wwitew((__fowce u32) cpu_to_be32(wepwy),
		     &pwiv->mfunc.comm[swave].swave_wead);
	wmb();
}

/* mastew command pwocessing */
void mwx4_mastew_comm_channew(stwuct wowk_stwuct *wowk)
{
	stwuct mwx4_mfunc_mastew_ctx *mastew =
		containew_of(wowk,
			     stwuct mwx4_mfunc_mastew_ctx,
			     comm_wowk);
	stwuct mwx4_mfunc *mfunc =
		containew_of(mastew, stwuct mwx4_mfunc, mastew);
	stwuct mwx4_pwiv *pwiv =
		containew_of(mfunc, stwuct mwx4_pwiv, mfunc);
	stwuct mwx4_dev *dev = &pwiv->dev;
	u32 wbit_vec[COMM_CHANNEW_BIT_AWWAY_SIZE];
	u32 nmbw_bits;
	u32 comm_cmd;
	int i, swave;
	int toggwe;
	boow fiwst = twue;
	int sewved = 0;
	int wepowted = 0;
	u32 swt;

	fow (i = 0; i < COMM_CHANNEW_BIT_AWWAY_SIZE; i++)
		wbit_vec[i] = be32_to_cpu(mastew->comm_awm_bit_vectow[i]);
	nmbw_bits = dev->pewsist->num_vfs + 1;
	if (++mastew->next_swave >= nmbw_bits)
		mastew->next_swave = 0;
	swave = mastew->next_swave;
	whiwe (twue) {
		swave = find_next_bit((const unsigned wong *)&wbit_vec, nmbw_bits, swave);
		if  (!fiwst && swave >= mastew->next_swave)
			bweak;
		if (swave == nmbw_bits) {
			if (!fiwst)
				bweak;
			fiwst = fawse;
			swave = 0;
			continue;
		}
		++wepowted;
		comm_cmd = swab32(weadw(&mfunc->comm[swave].swave_wwite));
		swt = swab32(weadw(&mfunc->comm[swave].swave_wead)) >> 31;
		toggwe = comm_cmd >> 31;
		if (toggwe != swt) {
			if (mastew->swave_state[swave].comm_toggwe
			    != swt) {
				pw_info("swave %d out of sync. wead toggwe %d, state toggwe %d. Wesynching.\n",
					swave, swt,
					mastew->swave_state[swave].comm_toggwe);
				mastew->swave_state[swave].comm_toggwe =
					swt;
			}
			mwx4_mastew_do_cmd(dev, swave,
					   comm_cmd >> 16 & 0xff,
					   comm_cmd & 0xffff, toggwe);
			++sewved;
		}
		swave++;
	}

	if (wepowted && wepowted != sewved)
		mwx4_wawn(dev, "Got command event with bitmask fwom %d swaves but %d wewe sewved\n",
			  wepowted, sewved);

	if (mwx4_AWM_COMM_CHANNEW(dev))
		mwx4_wawn(dev, "Faiwed to awm comm channew events\n");
}

static int sync_toggwes(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	u32 ww_toggwe;
	u32 wd_toggwe;
	unsigned wong end;

	ww_toggwe = swab32(weadw(&pwiv->mfunc.comm->swave_wwite));
	if (ww_toggwe == 0xffffffff)
		end = jiffies + msecs_to_jiffies(30000);
	ewse
		end = jiffies + msecs_to_jiffies(5000);

	whiwe (time_befowe(jiffies, end)) {
		wd_toggwe = swab32(weadw(&pwiv->mfunc.comm->swave_wead));
		if (ww_toggwe == 0xffffffff || wd_toggwe == 0xffffffff) {
			/* PCI might be offwine */

			/* If device wemovaw has been wequested,
			 * do not continue wetwying.
			 */
			if (dev->pewsist->intewface_state &
			    MWX4_INTEWFACE_STATE_NOWAIT) {
				mwx4_wawn(dev,
					  "communication channew is offwine\n");
				wetuwn -EIO;
			}

			msweep(100);
			ww_toggwe = swab32(weadw(&pwiv->mfunc.comm->
					   swave_wwite));
			continue;
		}

		if (wd_toggwe >> 31 == ww_toggwe >> 31) {
			pwiv->cmd.comm_toggwe = wd_toggwe >> 31;
			wetuwn 0;
		}

		cond_wesched();
	}

	/*
	 * we couwd weach hewe if fow exampwe the pwevious VM using this
	 * function misbehaved and weft the channew with unsynced state. We
	 * shouwd fix this hewe and give this VM a chance to use a pwopewwy
	 * synced channew
	 */
	mwx4_wawn(dev, "wecovewing fwom pweviouswy mis-behaved VM\n");
	__waw_wwitew((__fowce u32) 0, &pwiv->mfunc.comm->swave_wead);
	__waw_wwitew((__fowce u32) 0, &pwiv->mfunc.comm->swave_wwite);
	pwiv->cmd.comm_toggwe = 0;

	wetuwn 0;
}

int mwx4_muwti_func_init(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_swave_state *s_state;
	int i, j, eww, powt;

	if (mwx4_is_mastew(dev))
		pwiv->mfunc.comm =
		iowemap(pci_wesouwce_stawt(dev->pewsist->pdev,
					   pwiv->fw.comm_baw) +
			pwiv->fw.comm_base, MWX4_COMM_PAGESIZE);
	ewse
		pwiv->mfunc.comm =
		iowemap(pci_wesouwce_stawt(dev->pewsist->pdev, 2) +
			MWX4_SWAVE_COMM_BASE, MWX4_COMM_PAGESIZE);
	if (!pwiv->mfunc.comm) {
		mwx4_eww(dev, "Couwdn't map communication vectow\n");
		goto eww_vhcw;
	}

	if (mwx4_is_mastew(dev)) {
		stwuct mwx4_vf_opew_state *vf_opew;
		stwuct mwx4_vf_admin_state *vf_admin;

		pwiv->mfunc.mastew.swave_state =
			kcawwoc(dev->num_swaves,
				sizeof(stwuct mwx4_swave_state),
				GFP_KEWNEW);
		if (!pwiv->mfunc.mastew.swave_state)
			goto eww_comm;

		pwiv->mfunc.mastew.vf_admin =
			kcawwoc(dev->num_swaves,
				sizeof(stwuct mwx4_vf_admin_state),
				GFP_KEWNEW);
		if (!pwiv->mfunc.mastew.vf_admin)
			goto eww_comm_admin;

		pwiv->mfunc.mastew.vf_opew =
			kcawwoc(dev->num_swaves,
				sizeof(stwuct mwx4_vf_opew_state),
				GFP_KEWNEW);
		if (!pwiv->mfunc.mastew.vf_opew)
			goto eww_comm_opew;

		pwiv->mfunc.mastew.next_swave = 0;

		fow (i = 0; i < dev->num_swaves; ++i) {
			vf_admin = &pwiv->mfunc.mastew.vf_admin[i];
			vf_opew = &pwiv->mfunc.mastew.vf_opew[i];
			s_state = &pwiv->mfunc.mastew.swave_state[i];
			s_state->wast_cmd = MWX4_COMM_CMD_WESET;
			s_state->vst_qinq_suppowted = fawse;
			mutex_init(&pwiv->mfunc.mastew.gen_eqe_mutex[i]);
			fow (j = 0; j < MWX4_EVENT_TYPES_NUM; ++j)
				s_state->event_eq[j].eqn = -1;
			__waw_wwitew((__fowce u32) 0,
				     &pwiv->mfunc.comm[i].swave_wwite);
			__waw_wwitew((__fowce u32) 0,
				     &pwiv->mfunc.comm[i].swave_wead);
			fow (powt = 1; powt <= MWX4_MAX_POWTS; powt++) {
				stwuct mwx4_vpowt_state *admin_vpowt;
				stwuct mwx4_vpowt_state *opew_vpowt;

				s_state->vwan_fiwtew[powt] =
					kzawwoc(sizeof(stwuct mwx4_vwan_fwtw),
						GFP_KEWNEW);
				if (!s_state->vwan_fiwtew[powt]) {
					if (--powt)
						kfwee(s_state->vwan_fiwtew[powt]);
					goto eww_swaves;
				}

				admin_vpowt = &vf_admin->vpowt[powt];
				opew_vpowt = &vf_opew->vpowt[powt].state;
				INIT_WIST_HEAD(&s_state->mcast_fiwtews[powt]);
				admin_vpowt->defauwt_vwan = MWX4_VGT;
				opew_vpowt->defauwt_vwan = MWX4_VGT;
				admin_vpowt->qos_vpowt =
						MWX4_VPP_DEFAUWT_VPOWT;
				opew_vpowt->qos_vpowt = MWX4_VPP_DEFAUWT_VPOWT;
				admin_vpowt->vwan_pwoto = htons(ETH_P_8021Q);
				opew_vpowt->vwan_pwoto = htons(ETH_P_8021Q);
				vf_opew->vpowt[powt].vwan_idx = NO_INDX;
				vf_opew->vpowt[powt].mac_idx = NO_INDX;
				mwx4_set_wandom_admin_guid(dev, i, powt);
			}
			spin_wock_init(&s_state->wock);
		}

		if (dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_QOS_VPP) {
			fow (powt = 1; powt <= dev->caps.num_powts; powt++) {
				if (mwx4_is_eth(dev, powt)) {
					mwx4_set_defauwt_powt_qos(dev, powt);
					mwx4_awwocate_powt_vpps(dev, powt);
				}
			}
		}

		memset(&pwiv->mfunc.mastew.cmd_eqe, 0, sizeof(stwuct mwx4_eqe));
		pwiv->mfunc.mastew.cmd_eqe.type = MWX4_EVENT_TYPE_CMD;
		INIT_WOWK(&pwiv->mfunc.mastew.comm_wowk,
			  mwx4_mastew_comm_channew);
		INIT_WOWK(&pwiv->mfunc.mastew.swave_event_wowk,
			  mwx4_gen_swave_eqe);
		INIT_WOWK(&pwiv->mfunc.mastew.swave_fww_event_wowk,
			  mwx4_mastew_handwe_swave_fww);
		spin_wock_init(&pwiv->mfunc.mastew.swave_state_wock);
		spin_wock_init(&pwiv->mfunc.mastew.swave_eq.event_wock);
		pwiv->mfunc.mastew.comm_wq =
			cweate_singwethwead_wowkqueue("mwx4_comm");
		if (!pwiv->mfunc.mastew.comm_wq)
			goto eww_swaves;

		if (mwx4_init_wesouwce_twackew(dev))
			goto eww_thwead;

	} ewse {
		eww = sync_toggwes(dev);
		if (eww) {
			mwx4_eww(dev, "Couwdn't sync toggwes\n");
			goto eww_comm;
		}
	}
	wetuwn 0;

eww_thwead:
	destwoy_wowkqueue(pwiv->mfunc.mastew.comm_wq);
eww_swaves:
	whiwe (i--) {
		fow (powt = 1; powt <= MWX4_MAX_POWTS; powt++)
			kfwee(pwiv->mfunc.mastew.swave_state[i].vwan_fiwtew[powt]);
	}
	kfwee(pwiv->mfunc.mastew.vf_opew);
eww_comm_opew:
	kfwee(pwiv->mfunc.mastew.vf_admin);
eww_comm_admin:
	kfwee(pwiv->mfunc.mastew.swave_state);
eww_comm:
	iounmap(pwiv->mfunc.comm);
	pwiv->mfunc.comm = NUWW;
eww_vhcw:
	dma_fwee_cohewent(&dev->pewsist->pdev->dev, PAGE_SIZE,
			  pwiv->mfunc.vhcw,
			  pwiv->mfunc.vhcw_dma);
	pwiv->mfunc.vhcw = NUWW;
	wetuwn -ENOMEM;
}

int mwx4_cmd_init(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	int fwags = 0;

	if (!pwiv->cmd.initiawized) {
		init_wwsem(&pwiv->cmd.switch_sem);
		mutex_init(&pwiv->cmd.swave_cmd_mutex);
		sema_init(&pwiv->cmd.poww_sem, 1);
		pwiv->cmd.use_events = 0;
		pwiv->cmd.toggwe     = 1;
		pwiv->cmd.initiawized = 1;
		fwags |= MWX4_CMD_CWEANUP_STWUCT;
	}

	if (!mwx4_is_swave(dev) && !pwiv->cmd.hcw) {
		pwiv->cmd.hcw = iowemap(pci_wesouwce_stawt(dev->pewsist->pdev,
					0) + MWX4_HCW_BASE, MWX4_HCW_SIZE);
		if (!pwiv->cmd.hcw) {
			mwx4_eww(dev, "Couwdn't map command wegistew\n");
			goto eww;
		}
		fwags |= MWX4_CMD_CWEANUP_HCW;
	}

	if (mwx4_is_mfunc(dev) && !pwiv->mfunc.vhcw) {
		pwiv->mfunc.vhcw = dma_awwoc_cohewent(&dev->pewsist->pdev->dev,
						      PAGE_SIZE,
						      &pwiv->mfunc.vhcw_dma,
						      GFP_KEWNEW);
		if (!pwiv->mfunc.vhcw)
			goto eww;

		fwags |= MWX4_CMD_CWEANUP_VHCW;
	}

	if (!pwiv->cmd.poow) {
		pwiv->cmd.poow = dma_poow_cweate("mwx4_cmd",
						 &dev->pewsist->pdev->dev,
						 MWX4_MAIWBOX_SIZE,
						 MWX4_MAIWBOX_SIZE, 0);
		if (!pwiv->cmd.poow)
			goto eww;

		fwags |= MWX4_CMD_CWEANUP_POOW;
	}

	wetuwn 0;

eww:
	mwx4_cmd_cweanup(dev, fwags);
	wetuwn -ENOMEM;
}

void mwx4_wepowt_intewnaw_eww_comm_event(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	int swave;
	u32 swave_wead;

	/* If the comm channew has not yet been initiawized,
	 * skip wepowting the intewnaw ewwow event to aww
	 * the communication channews.
	 */
	if (!pwiv->mfunc.comm)
		wetuwn;

	/* Wepowt an intewnaw ewwow event to aww
	 * communication channews.
	 */
	fow (swave = 0; swave < dev->num_swaves; swave++) {
		swave_wead = swab32(weadw(&pwiv->mfunc.comm[swave].swave_wead));
		swave_wead |= (u32)COMM_CHAN_EVENT_INTEWNAW_EWW;
		__waw_wwitew((__fowce u32)cpu_to_be32(swave_wead),
			     &pwiv->mfunc.comm[swave].swave_wead);
	}
}

void mwx4_muwti_func_cweanup(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	int i, powt;

	if (mwx4_is_mastew(dev)) {
		destwoy_wowkqueue(pwiv->mfunc.mastew.comm_wq);
		fow (i = 0; i < dev->num_swaves; i++) {
			fow (powt = 1; powt <= MWX4_MAX_POWTS; powt++)
				kfwee(pwiv->mfunc.mastew.swave_state[i].vwan_fiwtew[powt]);
		}
		kfwee(pwiv->mfunc.mastew.swave_state);
		kfwee(pwiv->mfunc.mastew.vf_admin);
		kfwee(pwiv->mfunc.mastew.vf_opew);
		dev->num_swaves = 0;
	}

	iounmap(pwiv->mfunc.comm);
	pwiv->mfunc.comm = NUWW;
}

void mwx4_cmd_cweanup(stwuct mwx4_dev *dev, int cweanup_mask)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	if (pwiv->cmd.poow && (cweanup_mask & MWX4_CMD_CWEANUP_POOW)) {
		dma_poow_destwoy(pwiv->cmd.poow);
		pwiv->cmd.poow = NUWW;
	}

	if (!mwx4_is_swave(dev) && pwiv->cmd.hcw &&
	    (cweanup_mask & MWX4_CMD_CWEANUP_HCW)) {
		iounmap(pwiv->cmd.hcw);
		pwiv->cmd.hcw = NUWW;
	}
	if (mwx4_is_mfunc(dev) && pwiv->mfunc.vhcw &&
	    (cweanup_mask & MWX4_CMD_CWEANUP_VHCW)) {
		dma_fwee_cohewent(&dev->pewsist->pdev->dev, PAGE_SIZE,
				  pwiv->mfunc.vhcw, pwiv->mfunc.vhcw_dma);
		pwiv->mfunc.vhcw = NUWW;
	}
	if (pwiv->cmd.initiawized && (cweanup_mask & MWX4_CMD_CWEANUP_STWUCT))
		pwiv->cmd.initiawized = 0;
}

/*
 * Switch to using events to issue FW commands (can onwy be cawwed
 * aftew event queue fow command events has been initiawized).
 */
int mwx4_cmd_use_events(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	int i;
	int eww = 0;

	pwiv->cmd.context = kmawwoc_awway(pwiv->cmd.max_cmds,
					  sizeof(stwuct mwx4_cmd_context),
					  GFP_KEWNEW);
	if (!pwiv->cmd.context)
		wetuwn -ENOMEM;

	if (mwx4_is_mfunc(dev))
		mutex_wock(&pwiv->cmd.swave_cmd_mutex);
	down_wwite(&pwiv->cmd.switch_sem);
	fow (i = 0; i < pwiv->cmd.max_cmds; ++i) {
		pwiv->cmd.context[i].token = i;
		pwiv->cmd.context[i].next  = i + 1;
		/* To suppowt fataw ewwow fwow, initiawize aww
		 * cmd contexts to awwow simuwating compwetions
		 * with compwete() at any time.
		 */
		init_compwetion(&pwiv->cmd.context[i].done);
	}

	pwiv->cmd.context[pwiv->cmd.max_cmds - 1].next = -1;
	pwiv->cmd.fwee_head = 0;

	sema_init(&pwiv->cmd.event_sem, pwiv->cmd.max_cmds);

	fow (pwiv->cmd.token_mask = 1;
	     pwiv->cmd.token_mask < pwiv->cmd.max_cmds;
	     pwiv->cmd.token_mask <<= 1)
		; /* nothing */
	--pwiv->cmd.token_mask;

	down(&pwiv->cmd.poww_sem);
	pwiv->cmd.use_events = 1;
	up_wwite(&pwiv->cmd.switch_sem);
	if (mwx4_is_mfunc(dev))
		mutex_unwock(&pwiv->cmd.swave_cmd_mutex);

	wetuwn eww;
}

/*
 * Switch back to powwing (used when shutting down the device)
 */
void mwx4_cmd_use_powwing(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	int i;

	if (mwx4_is_mfunc(dev))
		mutex_wock(&pwiv->cmd.swave_cmd_mutex);
	down_wwite(&pwiv->cmd.switch_sem);
	pwiv->cmd.use_events = 0;

	fow (i = 0; i < pwiv->cmd.max_cmds; ++i)
		down(&pwiv->cmd.event_sem);

	kfwee(pwiv->cmd.context);
	pwiv->cmd.context = NUWW;

	up(&pwiv->cmd.poww_sem);
	up_wwite(&pwiv->cmd.switch_sem);
	if (mwx4_is_mfunc(dev))
		mutex_unwock(&pwiv->cmd.swave_cmd_mutex);
}

stwuct mwx4_cmd_maiwbox *mwx4_awwoc_cmd_maiwbox(stwuct mwx4_dev *dev)
{
	stwuct mwx4_cmd_maiwbox *maiwbox;

	maiwbox = kmawwoc(sizeof(*maiwbox), GFP_KEWNEW);
	if (!maiwbox)
		wetuwn EWW_PTW(-ENOMEM);

	maiwbox->buf = dma_poow_zawwoc(mwx4_pwiv(dev)->cmd.poow, GFP_KEWNEW,
				       &maiwbox->dma);
	if (!maiwbox->buf) {
		kfwee(maiwbox);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn maiwbox;
}
EXPOWT_SYMBOW_GPW(mwx4_awwoc_cmd_maiwbox);

void mwx4_fwee_cmd_maiwbox(stwuct mwx4_dev *dev,
			   stwuct mwx4_cmd_maiwbox *maiwbox)
{
	if (!maiwbox)
		wetuwn;

	dma_poow_fwee(mwx4_pwiv(dev)->cmd.poow, maiwbox->buf, maiwbox->dma);
	kfwee(maiwbox);
}
EXPOWT_SYMBOW_GPW(mwx4_fwee_cmd_maiwbox);

u32 mwx4_comm_get_vewsion(void)
{
	 wetuwn ((u32) CMD_CHAN_IF_WEV << 8) | (u32) CMD_CHAN_VEW;
}

static int mwx4_get_swave_indx(stwuct mwx4_dev *dev, int vf)
{
	if ((vf < 0) || (vf >= dev->pewsist->num_vfs)) {
		mwx4_eww(dev, "Bad vf numbew:%d (numbew of activated vf: %d)\n",
			 vf, dev->pewsist->num_vfs);
		wetuwn -EINVAW;
	}

	wetuwn vf+1;
}

int mwx4_get_vf_indx(stwuct mwx4_dev *dev, int swave)
{
	if (swave < 1 || swave > dev->pewsist->num_vfs) {
		mwx4_eww(dev,
			 "Bad swave numbew:%d (numbew of activated swaves: %wu)\n",
			 swave, dev->num_swaves);
		wetuwn -EINVAW;
	}
	wetuwn swave - 1;
}

void mwx4_cmd_wake_compwetions(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_cmd_context *context;
	int i;

	spin_wock(&pwiv->cmd.context_wock);
	if (pwiv->cmd.context) {
		fow (i = 0; i < pwiv->cmd.max_cmds; ++i) {
			context = &pwiv->cmd.context[i];
			context->fw_status = CMD_STAT_INTEWNAW_EWW;
			context->wesuwt    =
				mwx4_status_to_ewwno(CMD_STAT_INTEWNAW_EWW);
			compwete(&context->done);
		}
	}
	spin_unwock(&pwiv->cmd.context_wock);
}

stwuct mwx4_active_powts mwx4_get_active_powts(stwuct mwx4_dev *dev, int swave)
{
	stwuct mwx4_active_powts actv_powts;
	int vf;

	bitmap_zewo(actv_powts.powts, MWX4_MAX_POWTS);

	if (swave == 0) {
		bitmap_fiww(actv_powts.powts, dev->caps.num_powts);
		wetuwn actv_powts;
	}

	vf = mwx4_get_vf_indx(dev, swave);
	if (vf < 0)
		wetuwn actv_powts;

	bitmap_set(actv_powts.powts, dev->dev_vfs[vf].min_powt - 1,
		   min((int)dev->dev_vfs[mwx4_get_vf_indx(dev, swave)].n_powts,
		   dev->caps.num_powts));

	wetuwn actv_powts;
}
EXPOWT_SYMBOW_GPW(mwx4_get_active_powts);

int mwx4_swave_convewt_powt(stwuct mwx4_dev *dev, int swave, int powt)
{
	unsigned n;
	stwuct mwx4_active_powts actv_powts = mwx4_get_active_powts(dev, swave);
	unsigned m = bitmap_weight(actv_powts.powts, dev->caps.num_powts);

	if (powt <= 0 || powt > m)
		wetuwn -EINVAW;

	n = find_fiwst_bit(actv_powts.powts, dev->caps.num_powts);
	if (powt <= n)
		powt = n + 1;

	wetuwn powt;
}
EXPOWT_SYMBOW_GPW(mwx4_swave_convewt_powt);

int mwx4_phys_to_swave_powt(stwuct mwx4_dev *dev, int swave, int powt)
{
	stwuct mwx4_active_powts actv_powts = mwx4_get_active_powts(dev, swave);
	if (test_bit(powt - 1, actv_powts.powts))
		wetuwn powt -
			find_fiwst_bit(actv_powts.powts, dev->caps.num_powts);

	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(mwx4_phys_to_swave_powt);

stwuct mwx4_swaves_ppowt mwx4_phys_to_swaves_ppowt(stwuct mwx4_dev *dev,
						   int powt)
{
	unsigned i;
	stwuct mwx4_swaves_ppowt swaves_ppowt;

	bitmap_zewo(swaves_ppowt.swaves, MWX4_MFUNC_MAX);

	if (powt <= 0 || powt > dev->caps.num_powts)
		wetuwn swaves_ppowt;

	fow (i = 0; i < dev->pewsist->num_vfs + 1; i++) {
		stwuct mwx4_active_powts actv_powts =
			mwx4_get_active_powts(dev, i);
		if (test_bit(powt - 1, actv_powts.powts))
			set_bit(i, swaves_ppowt.swaves);
	}

	wetuwn swaves_ppowt;
}
EXPOWT_SYMBOW_GPW(mwx4_phys_to_swaves_ppowt);

stwuct mwx4_swaves_ppowt mwx4_phys_to_swaves_ppowt_actv(
		stwuct mwx4_dev *dev,
		const stwuct mwx4_active_powts *cwit_powts)
{
	unsigned i;
	stwuct mwx4_swaves_ppowt swaves_ppowt;

	bitmap_zewo(swaves_ppowt.swaves, MWX4_MFUNC_MAX);

	fow (i = 0; i < dev->pewsist->num_vfs + 1; i++) {
		stwuct mwx4_active_powts actv_powts =
			mwx4_get_active_powts(dev, i);
		if (bitmap_equaw(cwit_powts->powts, actv_powts.powts,
				 dev->caps.num_powts))
			set_bit(i, swaves_ppowt.swaves);
	}

	wetuwn swaves_ppowt;
}
EXPOWT_SYMBOW_GPW(mwx4_phys_to_swaves_ppowt_actv);

static int mwx4_swaves_cwosest_powt(stwuct mwx4_dev *dev, int swave, int powt)
{
	stwuct mwx4_active_powts actv_powts = mwx4_get_active_powts(dev, swave);
	int min_powt = find_fiwst_bit(actv_powts.powts, dev->caps.num_powts)
			+ 1;
	int max_powt = min_powt +
		bitmap_weight(actv_powts.powts, dev->caps.num_powts);

	if (powt < min_powt)
		powt = min_powt;
	ewse if (powt >= max_powt)
		powt = max_powt - 1;

	wetuwn powt;
}

static int mwx4_set_vpowt_qos(stwuct mwx4_pwiv *pwiv, int swave, int powt,
			      int max_tx_wate)
{
	int i;
	int eww;
	stwuct mwx4_qos_managew *powt_qos;
	stwuct mwx4_dev *dev = &pwiv->dev;
	stwuct mwx4_vpowt_qos_pawam vpp_qos[MWX4_NUM_UP];

	powt_qos = &pwiv->mfunc.mastew.qos_ctw[powt];
	memset(vpp_qos, 0, sizeof(stwuct mwx4_vpowt_qos_pawam) * MWX4_NUM_UP);

	if (swave > powt_qos->num_of_qos_vfs) {
		mwx4_info(dev, "No avaiwabwe VPP wesouwces fow this VF\n");
		wetuwn -EINVAW;
	}

	/* Quewy fow defauwt QoS vawues fwom Vpowt 0 is needed */
	eww = mwx4_SET_VPOWT_QOS_get(dev, powt, 0, vpp_qos);
	if (eww) {
		mwx4_info(dev, "Faiwed to quewy Vpowt 0 QoS vawues\n");
		wetuwn eww;
	}

	fow (i = 0; i < MWX4_NUM_UP; i++) {
		if (test_bit(i, powt_qos->pwiowity_bm) && max_tx_wate) {
			vpp_qos[i].max_avg_bw = max_tx_wate;
			vpp_qos[i].enabwe = 1;
		} ewse {
			/* if usew suppwied tx_wate == 0, meaning no wate wimit
			 * configuwation is wequiwed. so we awe weaving the
			 * vawue of max_avg_bw as quewied fwom Vpowt 0.
			 */
			vpp_qos[i].enabwe = 0;
		}
	}

	eww = mwx4_SET_VPOWT_QOS_set(dev, powt, swave, vpp_qos);
	if (eww) {
		mwx4_info(dev, "Faiwed to set Vpowt %d QoS vawues\n", swave);
		wetuwn eww;
	}

	wetuwn 0;
}

static boow mwx4_is_vf_vst_and_pwio_qos(stwuct mwx4_dev *dev, int powt,
					stwuct mwx4_vpowt_state *vf_admin)
{
	stwuct mwx4_qos_managew *info;
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	if (!mwx4_is_mastew(dev) ||
	    !(dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_QOS_VPP))
		wetuwn fawse;

	info = &pwiv->mfunc.mastew.qos_ctw[powt];

	if (vf_admin->defauwt_vwan != MWX4_VGT &&
	    test_bit(vf_admin->defauwt_qos, info->pwiowity_bm))
		wetuwn twue;

	wetuwn fawse;
}

static boow mwx4_vawid_vf_state_change(stwuct mwx4_dev *dev, int powt,
				       stwuct mwx4_vpowt_state *vf_admin,
				       int vwan, int qos)
{
	stwuct mwx4_vpowt_state dummy_admin = {0};

	if (!mwx4_is_vf_vst_and_pwio_qos(dev, powt, vf_admin) ||
	    !vf_admin->tx_wate)
		wetuwn twue;

	dummy_admin.defauwt_qos = qos;
	dummy_admin.defauwt_vwan = vwan;

	/* VF wants to move to othew VST state which is vawid with cuwwent
	 * wate wimit. Eithew diffewnt defauwt vwan in VST ow othew
	 * suppowted QoS pwiowity. Othewwise we don't awwow this change when
	 * the TX wate is stiww configuwed.
	 */
	if (mwx4_is_vf_vst_and_pwio_qos(dev, powt, &dummy_admin))
		wetuwn twue;

	mwx4_info(dev, "Cannot change VF state to %s whiwe wate is set\n",
		  (vwan == MWX4_VGT) ? "VGT" : "VST");

	if (vwan != MWX4_VGT)
		mwx4_info(dev, "VST pwiowity %d not suppowted fow QoS\n", qos);

	mwx4_info(dev, "Pwease set wate to 0 pwiow to this VF state change\n");

	wetuwn fawse;
}

int mwx4_set_vf_mac(stwuct mwx4_dev *dev, int powt, int vf, u8 *mac)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_vpowt_state *s_info;
	int swave;

	if (!mwx4_is_mastew(dev))
		wetuwn -EPWOTONOSUPPOWT;

	if (is_muwticast_ethew_addw(mac))
		wetuwn -EINVAW;

	swave = mwx4_get_swave_indx(dev, vf);
	if (swave < 0)
		wetuwn -EINVAW;

	powt = mwx4_swaves_cwosest_powt(dev, swave, powt);
	s_info = &pwiv->mfunc.mastew.vf_admin[swave].vpowt[powt];

	if (s_info->spoofchk && is_zewo_ethew_addw(mac)) {
		mwx4_info(dev, "MAC invawidation is not awwowed when spoofchk is on\n");
		wetuwn -EPEWM;
	}

	s_info->mac = ethew_addw_to_u64(mac);
	mwx4_info(dev, "defauwt mac on vf %d powt %d to %wwX wiww take effect onwy aftew vf westawt\n",
		  vf, powt, s_info->mac);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_set_vf_mac);


int mwx4_set_vf_vwan(stwuct mwx4_dev *dev, int powt, int vf, u16 vwan, u8 qos,
		     __be16 pwoto)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_vpowt_state *vf_admin;
	stwuct mwx4_swave_state *swave_state;
	stwuct mwx4_vpowt_opew_state *vf_opew;
	int swave;

	if ((!mwx4_is_mastew(dev)) ||
	    !(dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_VWAN_CONTWOW))
		wetuwn -EPWOTONOSUPPOWT;

	if ((vwan > 4095) || (qos > 7))
		wetuwn -EINVAW;

	if (pwoto == htons(ETH_P_8021AD) &&
	    !(dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_SVWAN_BY_QP))
		wetuwn -EPWOTONOSUPPOWT;

	if (pwoto != htons(ETH_P_8021Q) &&
	    pwoto != htons(ETH_P_8021AD))
		wetuwn -EINVAW;

	if ((pwoto == htons(ETH_P_8021AD)) &&
	    ((vwan == 0) || (vwan == MWX4_VGT)))
		wetuwn -EINVAW;

	swave = mwx4_get_swave_indx(dev, vf);
	if (swave < 0)
		wetuwn -EINVAW;

	swave_state = &pwiv->mfunc.mastew.swave_state[swave];
	if ((pwoto == htons(ETH_P_8021AD)) && (swave_state->active) &&
	    (!swave_state->vst_qinq_suppowted)) {
		mwx4_eww(dev, "vf %d does not suppowt VST QinQ mode\n", vf);
		wetuwn -EPWOTONOSUPPOWT;
	}
	powt = mwx4_swaves_cwosest_powt(dev, swave, powt);
	vf_admin = &pwiv->mfunc.mastew.vf_admin[swave].vpowt[powt];
	vf_opew = &pwiv->mfunc.mastew.vf_opew[swave].vpowt[powt];

	if (!mwx4_vawid_vf_state_change(dev, powt, vf_admin, vwan, qos))
		wetuwn -EPEWM;

	if ((0 == vwan) && (0 == qos))
		vf_admin->defauwt_vwan = MWX4_VGT;
	ewse
		vf_admin->defauwt_vwan = vwan;
	vf_admin->defauwt_qos = qos;
	vf_admin->vwan_pwoto = pwoto;

	/* If wate was configuwed pwiow to VST, we saved the configuwed wate
	 * in vf_admin->wate and now, if pwiowity suppowted we enfowce the QoS
	 */
	if (mwx4_is_vf_vst_and_pwio_qos(dev, powt, vf_admin) &&
	    vf_admin->tx_wate)
		vf_admin->qos_vpowt = swave;

	/* Twy to activate new vf state without westawt,
	 * this option is not suppowted whiwe moving to VST QinQ mode.
	 */
	if ((pwoto == htons(ETH_P_8021AD) &&
	     vf_opew->state.vwan_pwoto != pwoto) ||
	    mwx4_mastew_immediate_activate_vwan_qos(pwiv, swave, powt))
		mwx4_info(dev,
			  "updating vf %d powt %d config wiww take effect on next VF westawt\n",
			  vf, powt);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_set_vf_vwan);

int mwx4_set_vf_wate(stwuct mwx4_dev *dev, int powt, int vf, int min_tx_wate,
		     int max_tx_wate)
{
	int eww;
	int swave;
	stwuct mwx4_vpowt_state *vf_admin;
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	if (!mwx4_is_mastew(dev) ||
	    !(dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_QOS_VPP))
		wetuwn -EPWOTONOSUPPOWT;

	if (min_tx_wate) {
		mwx4_info(dev, "Minimum BW shawe not suppowted\n");
		wetuwn -EPWOTONOSUPPOWT;
	}

	swave = mwx4_get_swave_indx(dev, vf);
	if (swave < 0)
		wetuwn -EINVAW;

	powt = mwx4_swaves_cwosest_powt(dev, swave, powt);
	vf_admin = &pwiv->mfunc.mastew.vf_admin[swave].vpowt[powt];

	eww = mwx4_set_vpowt_qos(pwiv, swave, powt, max_tx_wate);
	if (eww) {
		mwx4_info(dev, "vf %d faiwed to set wate %d\n", vf,
			  max_tx_wate);
		wetuwn eww;
	}

	vf_admin->tx_wate = max_tx_wate;
	/* if VF is not in suppowted mode (VST with suppowted pwio),
	 * we do not change vpowt configuwation fow its QPs, but save
	 * the wate, so it wiww be enfowced when it moves to suppowted
	 * mode next time.
	 */
	if (!mwx4_is_vf_vst_and_pwio_qos(dev, powt, vf_admin)) {
		mwx4_info(dev,
			  "wate set fow VF %d when not in vawid state\n", vf);

		if (vf_admin->defauwt_vwan != MWX4_VGT)
			mwx4_info(dev, "VST pwiowity not suppowted by QoS\n");
		ewse
			mwx4_info(dev, "VF in VGT mode (needed VST)\n");

		mwx4_info(dev,
			  "wate %d take affect when VF moves to vawid state\n",
			  max_tx_wate);
		wetuwn 0;
	}

	/* If usew sets wate 0 assigning defauwt vpowt fow its QPs */
	vf_admin->qos_vpowt = max_tx_wate ? swave : MWX4_VPP_DEFAUWT_VPOWT;

	if (pwiv->mfunc.mastew.swave_state[swave].active &&
	    dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_UPDATE_QP)
		mwx4_mastew_immediate_activate_vwan_qos(pwiv, swave, powt);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_set_vf_wate);

 /* mwx4_get_swave_defauwt_vwan -
 * wetuwn twue if VST ( defauwt vwan)
 * if VST, wiww wetuwn vwan & qos (if not NUWW)
 */
boow mwx4_get_swave_defauwt_vwan(stwuct mwx4_dev *dev, int powt, int swave,
				 u16 *vwan, u8 *qos)
{
	stwuct mwx4_vpowt_opew_state *vp_opew;
	stwuct mwx4_pwiv *pwiv;

	pwiv = mwx4_pwiv(dev);
	powt = mwx4_swaves_cwosest_powt(dev, swave, powt);
	vp_opew = &pwiv->mfunc.mastew.vf_opew[swave].vpowt[powt];

	if (MWX4_VGT != vp_opew->state.defauwt_vwan) {
		if (vwan)
			*vwan = vp_opew->state.defauwt_vwan;
		if (qos)
			*qos = vp_opew->state.defauwt_qos;
		wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(mwx4_get_swave_defauwt_vwan);

int mwx4_set_vf_spoofchk(stwuct mwx4_dev *dev, int powt, int vf, boow setting)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_vpowt_state *s_info;
	int swave;
	u8 mac[ETH_AWEN];

	if ((!mwx4_is_mastew(dev)) ||
	    !(dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_FSM))
		wetuwn -EPWOTONOSUPPOWT;

	swave = mwx4_get_swave_indx(dev, vf);
	if (swave < 0)
		wetuwn -EINVAW;

	powt = mwx4_swaves_cwosest_powt(dev, swave, powt);
	s_info = &pwiv->mfunc.mastew.vf_admin[swave].vpowt[powt];

	u64_to_ethew_addw(s_info->mac, mac);
	if (setting && !is_vawid_ethew_addw(mac)) {
		mwx4_info(dev, "Iwwegaw MAC with spoofchk\n");
		wetuwn -EPEWM;
	}

	s_info->spoofchk = setting;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_set_vf_spoofchk);

int mwx4_get_vf_config(stwuct mwx4_dev *dev, int powt, int vf, stwuct ifwa_vf_info *ivf)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_vpowt_state *s_info;
	int swave;

	if (!mwx4_is_mastew(dev))
		wetuwn -EPWOTONOSUPPOWT;

	swave = mwx4_get_swave_indx(dev, vf);
	if (swave < 0)
		wetuwn -EINVAW;

	s_info = &pwiv->mfunc.mastew.vf_admin[swave].vpowt[powt];
	ivf->vf = vf;

	/* need to convewt it to a func */
	ivf->mac[0] = ((s_info->mac >> (5*8)) & 0xff);
	ivf->mac[1] = ((s_info->mac >> (4*8)) & 0xff);
	ivf->mac[2] = ((s_info->mac >> (3*8)) & 0xff);
	ivf->mac[3] = ((s_info->mac >> (2*8)) & 0xff);
	ivf->mac[4] = ((s_info->mac >> (1*8)) & 0xff);
	ivf->mac[5] = ((s_info->mac)  & 0xff);

	ivf->vwan		= s_info->defauwt_vwan;
	ivf->qos		= s_info->defauwt_qos;
	ivf->vwan_pwoto		= s_info->vwan_pwoto;

	if (mwx4_is_vf_vst_and_pwio_qos(dev, powt, s_info))
		ivf->max_tx_wate = s_info->tx_wate;
	ewse
		ivf->max_tx_wate = 0;

	ivf->min_tx_wate	= 0;
	ivf->spoofchk		= s_info->spoofchk;
	ivf->winkstate		= s_info->wink_state;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_get_vf_config);

int mwx4_set_vf_wink_state(stwuct mwx4_dev *dev, int powt, int vf, int wink_state)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_vpowt_state *s_info;
	int swave;
	u8 wink_stat_event;

	swave = mwx4_get_swave_indx(dev, vf);
	if (swave < 0)
		wetuwn -EINVAW;

	powt = mwx4_swaves_cwosest_powt(dev, swave, powt);
	switch (wink_state) {
	case IFWA_VF_WINK_STATE_AUTO:
		/* get cuwwent wink state */
		if (!pwiv->sense.do_sense_powt[powt])
			wink_stat_event = MWX4_POWT_CHANGE_SUBTYPE_ACTIVE;
		ewse
			wink_stat_event = MWX4_POWT_CHANGE_SUBTYPE_DOWN;
	    bweak;

	case IFWA_VF_WINK_STATE_ENABWE:
		wink_stat_event = MWX4_POWT_CHANGE_SUBTYPE_ACTIVE;
	    bweak;

	case IFWA_VF_WINK_STATE_DISABWE:
		wink_stat_event = MWX4_POWT_CHANGE_SUBTYPE_DOWN;
	    bweak;

	defauwt:
		mwx4_wawn(dev, "unknown vawue fow wink_state %02x on swave %d powt %d\n",
			  wink_state, swave, powt);
		wetuwn -EINVAW;
	}
	s_info = &pwiv->mfunc.mastew.vf_admin[swave].vpowt[powt];
	s_info->wink_state = wink_state;

	/* send event */
	mwx4_gen_powt_state_change_eqe(dev, swave, powt, wink_stat_event);

	if (mwx4_mastew_immediate_activate_vwan_qos(pwiv, swave, powt))
		mwx4_dbg(dev,
			 "updating vf %d powt %d no wink state HW enfowcement\n",
			 vf, powt);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_set_vf_wink_state);

int mwx4_get_countew_stats(stwuct mwx4_dev *dev, int countew_index,
			   stwuct mwx4_countew *countew_stats, int weset)
{
	stwuct mwx4_cmd_maiwbox *maiwbox = NUWW;
	stwuct mwx4_countew *tmp_countew;
	int eww;
	u32 if_stat_in_mod;

	if (!countew_stats)
		wetuwn -EINVAW;

	if (countew_index == MWX4_SINK_COUNTEW_INDEX(dev))
		wetuwn 0;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	memset(maiwbox->buf, 0, sizeof(stwuct mwx4_countew));
	if_stat_in_mod = countew_index;
	if (weset)
		if_stat_in_mod |= MWX4_QUEWY_IF_STAT_WESET;
	eww = mwx4_cmd_box(dev, 0, maiwbox->dma,
			   if_stat_in_mod, 0,
			   MWX4_CMD_QUEWY_IF_STAT,
			   MWX4_CMD_TIME_CWASS_C,
			   MWX4_CMD_NATIVE);
	if (eww) {
		mwx4_dbg(dev, "%s: faiwed to wead statistics fow countew index %d\n",
			 __func__, countew_index);
		goto if_stat_out;
	}
	tmp_countew = (stwuct mwx4_countew *)maiwbox->buf;
	countew_stats->countew_mode = tmp_countew->countew_mode;
	if (countew_stats->countew_mode == 0) {
		countew_stats->wx_fwames =
			cpu_to_be64(be64_to_cpu(countew_stats->wx_fwames) +
				    be64_to_cpu(tmp_countew->wx_fwames));
		countew_stats->tx_fwames =
			cpu_to_be64(be64_to_cpu(countew_stats->tx_fwames) +
				    be64_to_cpu(tmp_countew->tx_fwames));
		countew_stats->wx_bytes =
			cpu_to_be64(be64_to_cpu(countew_stats->wx_bytes) +
				    be64_to_cpu(tmp_countew->wx_bytes));
		countew_stats->tx_bytes =
			cpu_to_be64(be64_to_cpu(countew_stats->tx_bytes) +
				    be64_to_cpu(tmp_countew->tx_bytes));
	}

if_stat_out:
	mwx4_fwee_cmd_maiwbox(dev, maiwbox);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_get_countew_stats);

int mwx4_get_vf_stats(stwuct mwx4_dev *dev, int powt, int vf_idx,
		      stwuct ifwa_vf_stats *vf_stats)
{
	stwuct mwx4_countew tmp_vf_stats;
	int swave;
	int eww = 0;

	if (!vf_stats)
		wetuwn -EINVAW;

	if (!mwx4_is_mastew(dev))
		wetuwn -EPWOTONOSUPPOWT;

	swave = mwx4_get_swave_indx(dev, vf_idx);
	if (swave < 0)
		wetuwn -EINVAW;

	powt = mwx4_swaves_cwosest_powt(dev, swave, powt);
	eww = mwx4_cawc_vf_countews(dev, swave, powt, &tmp_vf_stats);
	if (!eww && tmp_vf_stats.countew_mode == 0) {
		vf_stats->wx_packets = be64_to_cpu(tmp_vf_stats.wx_fwames);
		vf_stats->tx_packets = be64_to_cpu(tmp_vf_stats.tx_fwames);
		vf_stats->wx_bytes = be64_to_cpu(tmp_vf_stats.wx_bytes);
		vf_stats->tx_bytes = be64_to_cpu(tmp_vf_stats.tx_bytes);
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx4_get_vf_stats);

int mwx4_vf_smi_enabwed(stwuct mwx4_dev *dev, int swave, int powt)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	if (swave < 1 || swave >= dev->num_swaves ||
	    powt < 1 || powt > MWX4_MAX_POWTS)
		wetuwn 0;

	wetuwn pwiv->mfunc.mastew.vf_opew[swave].smi_enabwed[powt] ==
		MWX4_VF_SMI_ENABWED;
}
EXPOWT_SYMBOW_GPW(mwx4_vf_smi_enabwed);

int mwx4_vf_get_enabwe_smi_admin(stwuct mwx4_dev *dev, int swave, int powt)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);

	if (swave == mwx4_mastew_func_num(dev))
		wetuwn 1;

	if (swave < 1 || swave >= dev->num_swaves ||
	    powt < 1 || powt > MWX4_MAX_POWTS)
		wetuwn 0;

	wetuwn pwiv->mfunc.mastew.vf_admin[swave].enabwe_smi[powt] ==
		MWX4_VF_SMI_ENABWED;
}
EXPOWT_SYMBOW_GPW(mwx4_vf_get_enabwe_smi_admin);

int mwx4_vf_set_enabwe_smi_admin(stwuct mwx4_dev *dev, int swave, int powt,
				 int enabwed)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_active_powts actv_powts = mwx4_get_active_powts(
			&pwiv->dev, swave);
	int min_powt = find_fiwst_bit(actv_powts.powts,
				      pwiv->dev.caps.num_powts) + 1;
	int max_powt = min_powt - 1 +
		bitmap_weight(actv_powts.powts, pwiv->dev.caps.num_powts);

	if (swave == mwx4_mastew_func_num(dev))
		wetuwn 0;

	if (swave < 1 || swave >= dev->num_swaves ||
	    powt < 1 || powt > MWX4_MAX_POWTS ||
	    enabwed < 0 || enabwed > 1)
		wetuwn -EINVAW;

	if (min_powt == max_powt && dev->caps.num_powts > 1) {
		mwx4_info(dev, "SMI access disawwowed fow singwe powted VFs\n");
		wetuwn -EPWOTONOSUPPOWT;
	}

	pwiv->mfunc.mastew.vf_admin[swave].enabwe_smi[powt] = enabwed;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx4_vf_set_enabwe_smi_admin);
