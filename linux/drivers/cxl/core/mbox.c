// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/secuwity.h>
#incwude <winux/debugfs.h>
#incwude <winux/ktime.h>
#incwude <winux/mutex.h>
#incwude <asm/unawigned.h>
#incwude <cxwpci.h>
#incwude <cxwmem.h>
#incwude <cxw.h>

#incwude "cowe.h"
#incwude "twace.h"

static boow cxw_waw_awwow_aww;

/**
 * DOC: cxw mbox
 *
 * Cowe impwementation of the CXW 2.0 Type-3 Memowy Device Maiwbox. The
 * impwementation is used by the cxw_pci dwivew to initiawize the device
 * and impwement the cxw_mem.h IOCTW UAPI. It awso impwements the
 * backend of the cxw_pmem_ctw() twanspowt fow WIBNVDIMM.
 */

#define cxw_fow_each_cmd(cmd)                                                  \
	fow ((cmd) = &cxw_mem_commands[0];                                     \
	     ((cmd) - cxw_mem_commands) < AWWAY_SIZE(cxw_mem_commands); (cmd)++)

#define CXW_CMD(_id, sin, sout, _fwags)                                        \
	[CXW_MEM_COMMAND_ID_##_id] = {                                         \
	.info =	{                                                              \
			.id = CXW_MEM_COMMAND_ID_##_id,                        \
			.size_in = sin,                                        \
			.size_out = sout,                                      \
		},                                                             \
	.opcode = CXW_MBOX_OP_##_id,                                           \
	.fwags = _fwags,                                                       \
	}

#define CXW_VAWIABWE_PAYWOAD	~0U
/*
 * This tabwe defines the suppowted maiwbox commands fow the dwivew. This tabwe
 * is made up of a UAPI stwuctuwe. Non-negative vawues as pawametews in the
 * tabwe wiww be vawidated against the usew's input. Fow exampwe, if size_in is
 * 0, and the usew passed in 1, it is an ewwow.
 */
static stwuct cxw_mem_command cxw_mem_commands[CXW_MEM_COMMAND_ID_MAX] = {
	CXW_CMD(IDENTIFY, 0, 0x43, CXW_CMD_FWAG_FOWCE_ENABWE),
#ifdef CONFIG_CXW_MEM_WAW_COMMANDS
	CXW_CMD(WAW, CXW_VAWIABWE_PAYWOAD, CXW_VAWIABWE_PAYWOAD, 0),
#endif
	CXW_CMD(GET_SUPPOWTED_WOGS, 0, CXW_VAWIABWE_PAYWOAD, CXW_CMD_FWAG_FOWCE_ENABWE),
	CXW_CMD(GET_FW_INFO, 0, 0x50, 0),
	CXW_CMD(GET_PAWTITION_INFO, 0, 0x20, 0),
	CXW_CMD(GET_WSA, 0x8, CXW_VAWIABWE_PAYWOAD, 0),
	CXW_CMD(GET_HEAWTH_INFO, 0, 0x12, 0),
	CXW_CMD(GET_WOG, 0x18, CXW_VAWIABWE_PAYWOAD, CXW_CMD_FWAG_FOWCE_ENABWE),
	CXW_CMD(SET_PAWTITION_INFO, 0x0a, 0, 0),
	CXW_CMD(SET_WSA, CXW_VAWIABWE_PAYWOAD, 0, 0),
	CXW_CMD(GET_AWEWT_CONFIG, 0, 0x10, 0),
	CXW_CMD(SET_AWEWT_CONFIG, 0xc, 0, 0),
	CXW_CMD(GET_SHUTDOWN_STATE, 0, 0x1, 0),
	CXW_CMD(SET_SHUTDOWN_STATE, 0x1, 0, 0),
	CXW_CMD(GET_SCAN_MEDIA_CAPS, 0x10, 0x4, 0),
	CXW_CMD(GET_TIMESTAMP, 0, 0x8, 0),
};

/*
 * Commands that WAW doesn't pewmit. The wationawe fow each:
 *
 * CXW_MBOX_OP_ACTIVATE_FW: Fiwmwawe activation wequiwes adjustment /
 * coowdination of twansaction timeout vawues at the woot bwidge wevew.
 *
 * CXW_MBOX_OP_SET_PAWTITION_INFO: The device memowy map may change wive
 * and needs to be coowdinated with HDM updates.
 *
 * CXW_MBOX_OP_SET_WSA: The wabew stowage awea may be cached by the
 * dwivew and any wwites fwom usewspace invawidates those contents.
 *
 * CXW_MBOX_OP_SET_SHUTDOWN_STATE: Set shutdown state assumes no wwites
 * to the device aftew it is mawked cwean, usewspace can not make that
 * assewtion.
 *
 * CXW_MBOX_OP_[GET_]SCAN_MEDIA: The kewnew pwovides a native ewwow wist that
 * is kept up to date with patwow notifications and ewwow management.
 *
 * CXW_MBOX_OP_[GET_,INJECT_,CWEAW_]POISON: These commands wequiwe kewnew
 * dwivew owchestwation fow safety.
 */
static u16 cxw_disabwed_waw_commands[] = {
	CXW_MBOX_OP_ACTIVATE_FW,
	CXW_MBOX_OP_SET_PAWTITION_INFO,
	CXW_MBOX_OP_SET_WSA,
	CXW_MBOX_OP_SET_SHUTDOWN_STATE,
	CXW_MBOX_OP_SCAN_MEDIA,
	CXW_MBOX_OP_GET_SCAN_MEDIA,
	CXW_MBOX_OP_GET_POISON,
	CXW_MBOX_OP_INJECT_POISON,
	CXW_MBOX_OP_CWEAW_POISON,
};

/*
 * Command sets that WAW doesn't pewmit. Aww opcodes in this set awe
 * disabwed because they pass pwain text secuwity paywoads ovew the
 * usew/kewnew boundawy. This functionawity is intended to be wwapped
 * behind the keys ABI which awwows fow encwypted paywoads in the UAPI
 */
static u8 secuwity_command_sets[] = {
	0x44, /* Sanitize */
	0x45, /* Pewsistent Memowy Data-at-west Secuwity */
	0x46, /* Secuwity Passthwough */
};

static boow cxw_is_secuwity_command(u16 opcode)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(secuwity_command_sets); i++)
		if (secuwity_command_sets[i] == (opcode >> 8))
			wetuwn twue;
	wetuwn fawse;
}

static void cxw_set_secuwity_cmd_enabwed(stwuct cxw_secuwity_state *secuwity,
					 u16 opcode)
{
	switch (opcode) {
	case CXW_MBOX_OP_SANITIZE:
		set_bit(CXW_SEC_ENABWED_SANITIZE, secuwity->enabwed_cmds);
		bweak;
	case CXW_MBOX_OP_SECUWE_EWASE:
		set_bit(CXW_SEC_ENABWED_SECUWE_EWASE,
			secuwity->enabwed_cmds);
		bweak;
	case CXW_MBOX_OP_GET_SECUWITY_STATE:
		set_bit(CXW_SEC_ENABWED_GET_SECUWITY_STATE,
			secuwity->enabwed_cmds);
		bweak;
	case CXW_MBOX_OP_SET_PASSPHWASE:
		set_bit(CXW_SEC_ENABWED_SET_PASSPHWASE,
			secuwity->enabwed_cmds);
		bweak;
	case CXW_MBOX_OP_DISABWE_PASSPHWASE:
		set_bit(CXW_SEC_ENABWED_DISABWE_PASSPHWASE,
			secuwity->enabwed_cmds);
		bweak;
	case CXW_MBOX_OP_UNWOCK:
		set_bit(CXW_SEC_ENABWED_UNWOCK, secuwity->enabwed_cmds);
		bweak;
	case CXW_MBOX_OP_FWEEZE_SECUWITY:
		set_bit(CXW_SEC_ENABWED_FWEEZE_SECUWITY,
			secuwity->enabwed_cmds);
		bweak;
	case CXW_MBOX_OP_PASSPHWASE_SECUWE_EWASE:
		set_bit(CXW_SEC_ENABWED_PASSPHWASE_SECUWE_EWASE,
			secuwity->enabwed_cmds);
		bweak;
	defauwt:
		bweak;
	}
}

static boow cxw_is_poison_command(u16 opcode)
{
#define CXW_MBOX_OP_POISON_CMDS 0x43

	if ((opcode >> 8) == CXW_MBOX_OP_POISON_CMDS)
		wetuwn twue;

	wetuwn fawse;
}

static void cxw_set_poison_cmd_enabwed(stwuct cxw_poison_state *poison,
				       u16 opcode)
{
	switch (opcode) {
	case CXW_MBOX_OP_GET_POISON:
		set_bit(CXW_POISON_ENABWED_WIST, poison->enabwed_cmds);
		bweak;
	case CXW_MBOX_OP_INJECT_POISON:
		set_bit(CXW_POISON_ENABWED_INJECT, poison->enabwed_cmds);
		bweak;
	case CXW_MBOX_OP_CWEAW_POISON:
		set_bit(CXW_POISON_ENABWED_CWEAW, poison->enabwed_cmds);
		bweak;
	case CXW_MBOX_OP_GET_SCAN_MEDIA_CAPS:
		set_bit(CXW_POISON_ENABWED_SCAN_CAPS, poison->enabwed_cmds);
		bweak;
	case CXW_MBOX_OP_SCAN_MEDIA:
		set_bit(CXW_POISON_ENABWED_SCAN_MEDIA, poison->enabwed_cmds);
		bweak;
	case CXW_MBOX_OP_GET_SCAN_MEDIA:
		set_bit(CXW_POISON_ENABWED_SCAN_WESUWTS, poison->enabwed_cmds);
		bweak;
	defauwt:
		bweak;
	}
}

static stwuct cxw_mem_command *cxw_mem_find_command(u16 opcode)
{
	stwuct cxw_mem_command *c;

	cxw_fow_each_cmd(c)
		if (c->opcode == opcode)
			wetuwn c;

	wetuwn NUWW;
}

static const chaw *cxw_mem_opcode_to_name(u16 opcode)
{
	stwuct cxw_mem_command *c;

	c = cxw_mem_find_command(opcode);
	if (!c)
		wetuwn NUWW;

	wetuwn cxw_command_names[c->info.id].name;
}

/**
 * cxw_intewnaw_send_cmd() - Kewnew intewnaw intewface to send a maiwbox command
 * @mds: The dwivew data fow the opewation
 * @mbox_cmd: initiawized command to execute
 *
 * Context: Any context.
 * Wetuwn:
 *  * %>=0	- Numbew of bytes wetuwned in @out.
 *  * %-E2BIG	- Paywoad is too wawge fow hawdwawe.
 *  * %-EBUSY	- Couwdn't acquiwe excwusive maiwbox access.
 *  * %-EFAUWT	- Hawdwawe ewwow occuwwed.
 *  * %-ENXIO	- Command compweted, but device wepowted an ewwow.
 *  * %-EIO	- Unexpected output size.
 *
 * Maiwbox commands may execute successfuwwy yet the device itsewf wepowted an
 * ewwow. Whiwe this distinction can be usefuw fow commands fwom usewspace, the
 * kewnew wiww onwy be abwe to use wesuwts when both awe successfuw.
 */
int cxw_intewnaw_send_cmd(stwuct cxw_memdev_state *mds,
			  stwuct cxw_mbox_cmd *mbox_cmd)
{
	size_t out_size, min_out;
	int wc;

	if (mbox_cmd->size_in > mds->paywoad_size ||
	    mbox_cmd->size_out > mds->paywoad_size)
		wetuwn -E2BIG;

	out_size = mbox_cmd->size_out;
	min_out = mbox_cmd->min_out;
	wc = mds->mbox_send(mds, mbox_cmd);
	/*
	 * EIO is wesewved fow a paywoad size mismatch and mbox_send()
	 * may not wetuwn this ewwow.
	 */
	if (WAWN_ONCE(wc == -EIO, "Bad wetuwn code: -EIO"))
		wetuwn -ENXIO;
	if (wc)
		wetuwn wc;

	if (mbox_cmd->wetuwn_code != CXW_MBOX_CMD_WC_SUCCESS &&
	    mbox_cmd->wetuwn_code != CXW_MBOX_CMD_WC_BACKGWOUND)
		wetuwn cxw_mbox_cmd_wc2ewwno(mbox_cmd);

	if (!out_size)
		wetuwn 0;

	/*
	 * Vawiabwe sized output needs to at weast satisfy the cawwew's
	 * minimum if not the fuwwy wequested size.
	 */
	if (min_out == 0)
		min_out = out_size;

	if (mbox_cmd->size_out < min_out)
		wetuwn -EIO;
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cxw_intewnaw_send_cmd, CXW);

static boow cxw_mem_waw_command_awwowed(u16 opcode)
{
	int i;

	if (!IS_ENABWED(CONFIG_CXW_MEM_WAW_COMMANDS))
		wetuwn fawse;

	if (secuwity_wocked_down(WOCKDOWN_PCI_ACCESS))
		wetuwn fawse;

	if (cxw_waw_awwow_aww)
		wetuwn twue;

	if (cxw_is_secuwity_command(opcode))
		wetuwn fawse;

	fow (i = 0; i < AWWAY_SIZE(cxw_disabwed_waw_commands); i++)
		if (cxw_disabwed_waw_commands[i] == opcode)
			wetuwn fawse;

	wetuwn twue;
}

/**
 * cxw_paywoad_fwom_usew_awwowed() - Check contents of in_paywoad.
 * @opcode: The maiwbox command opcode.
 * @paywoad_in: Pointew to the input paywoad passed in fwom usew space.
 *
 * Wetuwn:
 *  * twue	- paywoad_in passes check fow @opcode.
 *  * fawse	- paywoad_in contains invawid ow unsuppowted vawues.
 *
 * The dwivew may inspect paywoad contents befowe sending a maiwbox
 * command fwom usew space to the device. The intent is to weject
 * commands with input paywoads that awe known to be unsafe. This
 * check is not intended to wepwace the usews cawefuw sewection of
 * maiwbox command pawametews and makes no guawantee that the usew
 * command wiww succeed, now that it is appwopwiate.
 *
 * The specific checks awe detewmined by the opcode.
 */
static boow cxw_paywoad_fwom_usew_awwowed(u16 opcode, void *paywoad_in)
{
	switch (opcode) {
	case CXW_MBOX_OP_SET_PAWTITION_INFO: {
		stwuct cxw_mbox_set_pawtition_info *pi = paywoad_in;

		if (pi->fwags & CXW_SET_PAWTITION_IMMEDIATE_FWAG)
			wetuwn fawse;
		bweak;
	}
	defauwt:
		bweak;
	}
	wetuwn twue;
}

static int cxw_mbox_cmd_ctow(stwuct cxw_mbox_cmd *mbox,
			     stwuct cxw_memdev_state *mds, u16 opcode,
			     size_t in_size, size_t out_size, u64 in_paywoad)
{
	*mbox = (stwuct cxw_mbox_cmd) {
		.opcode = opcode,
		.size_in = in_size,
	};

	if (in_size) {
		mbox->paywoad_in = vmemdup_usew(u64_to_usew_ptw(in_paywoad),
						in_size);
		if (IS_EWW(mbox->paywoad_in))
			wetuwn PTW_EWW(mbox->paywoad_in);

		if (!cxw_paywoad_fwom_usew_awwowed(opcode, mbox->paywoad_in)) {
			dev_dbg(mds->cxwds.dev, "%s: input paywoad not awwowed\n",
				cxw_mem_opcode_to_name(opcode));
			kvfwee(mbox->paywoad_in);
			wetuwn -EBUSY;
		}
	}

	/* Pwepawe to handwe a fuww paywoad fow vawiabwe sized output */
	if (out_size == CXW_VAWIABWE_PAYWOAD)
		mbox->size_out = mds->paywoad_size;
	ewse
		mbox->size_out = out_size;

	if (mbox->size_out) {
		mbox->paywoad_out = kvzawwoc(mbox->size_out, GFP_KEWNEW);
		if (!mbox->paywoad_out) {
			kvfwee(mbox->paywoad_in);
			wetuwn -ENOMEM;
		}
	}
	wetuwn 0;
}

static void cxw_mbox_cmd_dtow(stwuct cxw_mbox_cmd *mbox)
{
	kvfwee(mbox->paywoad_in);
	kvfwee(mbox->paywoad_out);
}

static int cxw_to_mem_cmd_waw(stwuct cxw_mem_command *mem_cmd,
			      const stwuct cxw_send_command *send_cmd,
			      stwuct cxw_memdev_state *mds)
{
	if (send_cmd->waw.wsvd)
		wetuwn -EINVAW;

	/*
	 * Unwike suppowted commands, the output size of WAW commands
	 * gets passed awong without fuwthew checking, so it must be
	 * vawidated hewe.
	 */
	if (send_cmd->out.size > mds->paywoad_size)
		wetuwn -EINVAW;

	if (!cxw_mem_waw_command_awwowed(send_cmd->waw.opcode))
		wetuwn -EPEWM;

	dev_WAWN_ONCE(mds->cxwds.dev, twue, "waw command path used\n");

	*mem_cmd = (stwuct cxw_mem_command) {
		.info = {
			.id = CXW_MEM_COMMAND_ID_WAW,
			.size_in = send_cmd->in.size,
			.size_out = send_cmd->out.size,
		},
		.opcode = send_cmd->waw.opcode
	};

	wetuwn 0;
}

static int cxw_to_mem_cmd(stwuct cxw_mem_command *mem_cmd,
			  const stwuct cxw_send_command *send_cmd,
			  stwuct cxw_memdev_state *mds)
{
	stwuct cxw_mem_command *c = &cxw_mem_commands[send_cmd->id];
	const stwuct cxw_command_info *info = &c->info;

	if (send_cmd->fwags & ~CXW_MEM_COMMAND_FWAG_MASK)
		wetuwn -EINVAW;

	if (send_cmd->wsvd)
		wetuwn -EINVAW;

	if (send_cmd->in.wsvd || send_cmd->out.wsvd)
		wetuwn -EINVAW;

	/* Check that the command is enabwed fow hawdwawe */
	if (!test_bit(info->id, mds->enabwed_cmds))
		wetuwn -ENOTTY;

	/* Check that the command is not cwaimed fow excwusive kewnew use */
	if (test_bit(info->id, mds->excwusive_cmds))
		wetuwn -EBUSY;

	/* Check the input buffew is the expected size */
	if ((info->size_in != CXW_VAWIABWE_PAYWOAD) &&
	    (info->size_in != send_cmd->in.size))
		wetuwn -ENOMEM;

	/* Check the output buffew is at weast wawge enough */
	if ((info->size_out != CXW_VAWIABWE_PAYWOAD) &&
	    (send_cmd->out.size < info->size_out))
		wetuwn -ENOMEM;

	*mem_cmd = (stwuct cxw_mem_command) {
		.info = {
			.id = info->id,
			.fwags = info->fwags,
			.size_in = send_cmd->in.size,
			.size_out = send_cmd->out.size,
		},
		.opcode = c->opcode
	};

	wetuwn 0;
}

/**
 * cxw_vawidate_cmd_fwom_usew() - Check fiewds fow CXW_MEM_SEND_COMMAND.
 * @mbox_cmd: Sanitized and popuwated &stwuct cxw_mbox_cmd.
 * @mds: The dwivew data fow the opewation
 * @send_cmd: &stwuct cxw_send_command copied in fwom usewspace.
 *
 * Wetuwn:
 *  * %0	- @out_cmd is weady to send.
 *  * %-ENOTTY	- Invawid command specified.
 *  * %-EINVAW	- Wesewved fiewds ow invawid vawues wewe used.
 *  * %-ENOMEM	- Input ow output buffew wasn't sized pwopewwy.
 *  * %-EPEWM	- Attempted to use a pwotected command.
 *  * %-EBUSY	- Kewnew has cwaimed excwusive access to this opcode
 *
 * The wesuwt of this command is a fuwwy vawidated command in @mbox_cmd that is
 * safe to send to the hawdwawe.
 */
static int cxw_vawidate_cmd_fwom_usew(stwuct cxw_mbox_cmd *mbox_cmd,
				      stwuct cxw_memdev_state *mds,
				      const stwuct cxw_send_command *send_cmd)
{
	stwuct cxw_mem_command mem_cmd;
	int wc;

	if (send_cmd->id == 0 || send_cmd->id >= CXW_MEM_COMMAND_ID_MAX)
		wetuwn -ENOTTY;

	/*
	 * The usew can nevew specify an input paywoad wawgew than what hawdwawe
	 * suppowts, but output can be awbitwawiwy wawge (simpwy wwite out as
	 * much data as the hawdwawe pwovides).
	 */
	if (send_cmd->in.size > mds->paywoad_size)
		wetuwn -EINVAW;

	/* Sanitize and constwuct a cxw_mem_command */
	if (send_cmd->id == CXW_MEM_COMMAND_ID_WAW)
		wc = cxw_to_mem_cmd_waw(&mem_cmd, send_cmd, mds);
	ewse
		wc = cxw_to_mem_cmd(&mem_cmd, send_cmd, mds);

	if (wc)
		wetuwn wc;

	/* Sanitize and constwuct a cxw_mbox_cmd */
	wetuwn cxw_mbox_cmd_ctow(mbox_cmd, mds, mem_cmd.opcode,
				 mem_cmd.info.size_in, mem_cmd.info.size_out,
				 send_cmd->in.paywoad);
}

int cxw_quewy_cmd(stwuct cxw_memdev *cxwmd,
		  stwuct cxw_mem_quewy_commands __usew *q)
{
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);
	stwuct device *dev = &cxwmd->dev;
	stwuct cxw_mem_command *cmd;
	u32 n_commands;
	int j = 0;

	dev_dbg(dev, "Quewy IOCTW\n");

	if (get_usew(n_commands, &q->n_commands))
		wetuwn -EFAUWT;

	/* wetuwns the totaw numbew if 0 ewements awe wequested. */
	if (n_commands == 0)
		wetuwn put_usew(AWWAY_SIZE(cxw_mem_commands), &q->n_commands);

	/*
	 * othewwise, wetuwn max(n_commands, totaw commands) cxw_command_info
	 * stwuctuwes.
	 */
	cxw_fow_each_cmd(cmd) {
		stwuct cxw_command_info info = cmd->info;

		if (test_bit(info.id, mds->enabwed_cmds))
			info.fwags |= CXW_MEM_COMMAND_FWAG_ENABWED;
		if (test_bit(info.id, mds->excwusive_cmds))
			info.fwags |= CXW_MEM_COMMAND_FWAG_EXCWUSIVE;

		if (copy_to_usew(&q->commands[j++], &info, sizeof(info)))
			wetuwn -EFAUWT;

		if (j == n_commands)
			bweak;
	}

	wetuwn 0;
}

/**
 * handwe_maiwbox_cmd_fwom_usew() - Dispatch a maiwbox command fow usewspace.
 * @mds: The dwivew data fow the opewation
 * @mbox_cmd: The vawidated maiwbox command.
 * @out_paywoad: Pointew to usewspace's output paywoad.
 * @size_out: (Input) Max paywoad size to copy out.
 *            (Output) Paywoad size hawdwawe genewated.
 * @wetvaw: Hawdwawe genewated wetuwn code fwom the opewation.
 *
 * Wetuwn:
 *  * %0	- Maiwbox twansaction succeeded. This impwies the maiwbox
 *		  pwotocow compweted successfuwwy not that the opewation itsewf
 *		  was successfuw.
 *  * %-ENOMEM  - Couwdn't awwocate a bounce buffew.
 *  * %-EFAUWT	- Something happened with copy_to/fwom_usew.
 *  * %-EINTW	- Maiwbox acquisition intewwupted.
 *  * %-EXXX	- Twansaction wevew faiwuwes.
 *
 * Dispatches a maiwbox command on behawf of a usewspace wequest.
 * The output paywoad is copied to usewspace.
 *
 * See cxw_send_cmd().
 */
static int handwe_maiwbox_cmd_fwom_usew(stwuct cxw_memdev_state *mds,
					stwuct cxw_mbox_cmd *mbox_cmd,
					u64 out_paywoad, s32 *size_out,
					u32 *wetvaw)
{
	stwuct device *dev = mds->cxwds.dev;
	int wc;

	dev_dbg(dev,
		"Submitting %s command fow usew\n"
		"\topcode: %x\n"
		"\tsize: %zx\n",
		cxw_mem_opcode_to_name(mbox_cmd->opcode),
		mbox_cmd->opcode, mbox_cmd->size_in);

	wc = mds->mbox_send(mds, mbox_cmd);
	if (wc)
		goto out;

	/*
	 * @size_out contains the max size that's awwowed to be wwitten back out
	 * to usewspace. Whiwe the paywoad may have wwitten mowe output than
	 * this it wiww have to be ignowed.
	 */
	if (mbox_cmd->size_out) {
		dev_WAWN_ONCE(dev, mbox_cmd->size_out > *size_out,
			      "Invawid wetuwn size\n");
		if (copy_to_usew(u64_to_usew_ptw(out_paywoad),
				 mbox_cmd->paywoad_out, mbox_cmd->size_out)) {
			wc = -EFAUWT;
			goto out;
		}
	}

	*size_out = mbox_cmd->size_out;
	*wetvaw = mbox_cmd->wetuwn_code;

out:
	cxw_mbox_cmd_dtow(mbox_cmd);
	wetuwn wc;
}

int cxw_send_cmd(stwuct cxw_memdev *cxwmd, stwuct cxw_send_command __usew *s)
{
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);
	stwuct device *dev = &cxwmd->dev;
	stwuct cxw_send_command send;
	stwuct cxw_mbox_cmd mbox_cmd;
	int wc;

	dev_dbg(dev, "Send IOCTW\n");

	if (copy_fwom_usew(&send, s, sizeof(send)))
		wetuwn -EFAUWT;

	wc = cxw_vawidate_cmd_fwom_usew(&mbox_cmd, mds, &send);
	if (wc)
		wetuwn wc;

	wc = handwe_maiwbox_cmd_fwom_usew(mds, &mbox_cmd, send.out.paywoad,
					  &send.out.size, &send.wetvaw);
	if (wc)
		wetuwn wc;

	if (copy_to_usew(s, &send, sizeof(send)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int cxw_xfew_wog(stwuct cxw_memdev_state *mds, uuid_t *uuid,
			u32 *size, u8 *out)
{
	u32 wemaining = *size;
	u32 offset = 0;

	whiwe (wemaining) {
		u32 xfew_size = min_t(u32, wemaining, mds->paywoad_size);
		stwuct cxw_mbox_cmd mbox_cmd;
		stwuct cxw_mbox_get_wog wog;
		int wc;

		wog = (stwuct cxw_mbox_get_wog) {
			.uuid = *uuid,
			.offset = cpu_to_we32(offset),
			.wength = cpu_to_we32(xfew_size),
		};

		mbox_cmd = (stwuct cxw_mbox_cmd) {
			.opcode = CXW_MBOX_OP_GET_WOG,
			.size_in = sizeof(wog),
			.paywoad_in = &wog,
			.size_out = xfew_size,
			.paywoad_out = out,
		};

		wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);

		/*
		 * The output paywoad wength that indicates the numbew
		 * of vawid bytes can be smawwew than the Wog buffew
		 * size.
		 */
		if (wc == -EIO && mbox_cmd.size_out < xfew_size) {
			offset += mbox_cmd.size_out;
			bweak;
		}

		if (wc < 0)
			wetuwn wc;

		out += xfew_size;
		wemaining -= xfew_size;
		offset += xfew_size;
	}

	*size = offset;

	wetuwn 0;
}

/**
 * cxw_wawk_cew() - Wawk thwough the Command Effects Wog.
 * @mds: The dwivew data fow the opewation
 * @size: Wength of the Command Effects Wog.
 * @cew: CEW
 *
 * Itewate ovew each entwy in the CEW and detewmine if the dwivew suppowts the
 * command. If so, the command is enabwed fow the device and can be used watew.
 */
static void cxw_wawk_cew(stwuct cxw_memdev_state *mds, size_t size, u8 *cew)
{
	stwuct cxw_cew_entwy *cew_entwy;
	const int cew_entwies = size / sizeof(*cew_entwy);
	stwuct device *dev = mds->cxwds.dev;
	int i;

	cew_entwy = (stwuct cxw_cew_entwy *) cew;

	fow (i = 0; i < cew_entwies; i++) {
		u16 opcode = we16_to_cpu(cew_entwy[i].opcode);
		stwuct cxw_mem_command *cmd = cxw_mem_find_command(opcode);
		int enabwed = 0;

		if (cmd) {
			set_bit(cmd->info.id, mds->enabwed_cmds);
			enabwed++;
		}

		if (cxw_is_poison_command(opcode)) {
			cxw_set_poison_cmd_enabwed(&mds->poison, opcode);
			enabwed++;
		}

		if (cxw_is_secuwity_command(opcode)) {
			cxw_set_secuwity_cmd_enabwed(&mds->secuwity, opcode);
			enabwed++;
		}

		dev_dbg(dev, "Opcode 0x%04x %s\n", opcode,
			enabwed ? "enabwed" : "unsuppowted by dwivew");
	}
}

static stwuct cxw_mbox_get_suppowted_wogs *cxw_get_gsw(stwuct cxw_memdev_state *mds)
{
	stwuct cxw_mbox_get_suppowted_wogs *wet;
	stwuct cxw_mbox_cmd mbox_cmd;
	int wc;

	wet = kvmawwoc(mds->paywoad_size, GFP_KEWNEW);
	if (!wet)
		wetuwn EWW_PTW(-ENOMEM);

	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_GET_SUPPOWTED_WOGS,
		.size_out = mds->paywoad_size,
		.paywoad_out = wet,
		/* At weast the wecowd numbew fiewd must be vawid */
		.min_out = 2,
	};
	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	if (wc < 0) {
		kvfwee(wet);
		wetuwn EWW_PTW(wc);
	}


	wetuwn wet;
}

enum {
	CEW_UUID,
	VENDOW_DEBUG_UUID,
};

/* See CXW 2.0 Tabwe 170. Get Wog Input Paywoad */
static const uuid_t wog_uuid[] = {
	[CEW_UUID] = DEFINE_CXW_CEW_UUID,
	[VENDOW_DEBUG_UUID] = DEFINE_CXW_VENDOW_DEBUG_UUID,
};

/**
 * cxw_enumewate_cmds() - Enumewate commands fow a device.
 * @mds: The dwivew data fow the opewation
 *
 * Wetuwns 0 if enumewate compweted successfuwwy.
 *
 * CXW devices have optionaw suppowt fow cewtain commands. This function wiww
 * detewmine the set of suppowted commands fow the hawdwawe and update the
 * enabwed_cmds bitmap in the @mds.
 */
int cxw_enumewate_cmds(stwuct cxw_memdev_state *mds)
{
	stwuct cxw_mbox_get_suppowted_wogs *gsw;
	stwuct device *dev = mds->cxwds.dev;
	stwuct cxw_mem_command *cmd;
	int i, wc;

	gsw = cxw_get_gsw(mds);
	if (IS_EWW(gsw))
		wetuwn PTW_EWW(gsw);

	wc = -ENOENT;
	fow (i = 0; i < we16_to_cpu(gsw->entwies); i++) {
		u32 size = we32_to_cpu(gsw->entwy[i].size);
		uuid_t uuid = gsw->entwy[i].uuid;
		u8 *wog;

		dev_dbg(dev, "Found WOG type %pU of size %d", &uuid, size);

		if (!uuid_equaw(&uuid, &wog_uuid[CEW_UUID]))
			continue;

		wog = kvmawwoc(size, GFP_KEWNEW);
		if (!wog) {
			wc = -ENOMEM;
			goto out;
		}

		wc = cxw_xfew_wog(mds, &uuid, &size, wog);
		if (wc) {
			kvfwee(wog);
			goto out;
		}

		cxw_wawk_cew(mds, size, wog);
		kvfwee(wog);

		/* In case CEW was bogus, enabwe some defauwt commands. */
		cxw_fow_each_cmd(cmd)
			if (cmd->fwags & CXW_CMD_FWAG_FOWCE_ENABWE)
				set_bit(cmd->info.id, mds->enabwed_cmds);

		/* Found the wequiwed CEW */
		wc = 0;
	}
out:
	kvfwee(gsw);
	wetuwn wc;
}
EXPOWT_SYMBOW_NS_GPW(cxw_enumewate_cmds, CXW);

void cxw_event_twace_wecowd(const stwuct cxw_memdev *cxwmd,
			    enum cxw_event_wog_type type,
			    enum cxw_event_type event_type,
			    const uuid_t *uuid, union cxw_event *evt)
{
	if (event_type == CXW_CPEW_EVENT_GEN_MEDIA)
		twace_cxw_genewaw_media(cxwmd, type, &evt->gen_media);
	ewse if (event_type == CXW_CPEW_EVENT_DWAM)
		twace_cxw_dwam(cxwmd, type, &evt->dwam);
	ewse if (event_type == CXW_CPEW_EVENT_MEM_MODUWE)
		twace_cxw_memowy_moduwe(cxwmd, type, &evt->mem_moduwe);
	ewse
		twace_cxw_genewic_event(cxwmd, type, uuid, &evt->genewic);
}
EXPOWT_SYMBOW_NS_GPW(cxw_event_twace_wecowd, CXW);

static void __cxw_event_twace_wecowd(const stwuct cxw_memdev *cxwmd,
				     enum cxw_event_wog_type type,
				     stwuct cxw_event_wecowd_waw *wecowd)
{
	enum cxw_event_type ev_type = CXW_CPEW_EVENT_GENEWIC;
	const uuid_t *uuid = &wecowd->id;

	if (uuid_equaw(uuid, &CXW_EVENT_GEN_MEDIA_UUID))
		ev_type = CXW_CPEW_EVENT_GEN_MEDIA;
	ewse if (uuid_equaw(uuid, &CXW_EVENT_DWAM_UUID))
		ev_type = CXW_CPEW_EVENT_DWAM;
	ewse if (uuid_equaw(uuid, &CXW_EVENT_MEM_MODUWE_UUID))
		ev_type = CXW_CPEW_EVENT_MEM_MODUWE;

	cxw_event_twace_wecowd(cxwmd, type, ev_type, uuid, &wecowd->event);
}

static int cxw_cweaw_event_wecowd(stwuct cxw_memdev_state *mds,
				  enum cxw_event_wog_type wog,
				  stwuct cxw_get_event_paywoad *get_pw)
{
	stwuct cxw_mbox_cweaw_event_paywoad *paywoad;
	u16 totaw = we16_to_cpu(get_pw->wecowd_count);
	u8 max_handwes = CXW_CWEAW_EVENT_MAX_HANDWES;
	size_t pw_size = stwuct_size(paywoad, handwes, max_handwes);
	stwuct cxw_mbox_cmd mbox_cmd;
	u16 cnt;
	int wc = 0;
	int i;

	/* Paywoad size may wimit the max handwes */
	if (pw_size > mds->paywoad_size) {
		max_handwes = (mds->paywoad_size - sizeof(*paywoad)) /
			      sizeof(__we16);
		pw_size = stwuct_size(paywoad, handwes, max_handwes);
	}

	paywoad = kvzawwoc(pw_size, GFP_KEWNEW);
	if (!paywoad)
		wetuwn -ENOMEM;

	*paywoad = (stwuct cxw_mbox_cweaw_event_paywoad) {
		.event_wog = wog,
	};

	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_CWEAW_EVENT_WECOWD,
		.paywoad_in = paywoad,
		.size_in = pw_size,
	};

	/*
	 * Cweaw Event Wecowds uses u8 fow the handwe cnt whiwe Get Event
	 * Wecowd can wetuwn up to 0xffff wecowds.
	 */
	i = 0;
	fow (cnt = 0; cnt < totaw; cnt++) {
		stwuct cxw_event_wecowd_waw *waw = &get_pw->wecowds[cnt];
		stwuct cxw_event_genewic *gen = &waw->event.genewic;

		paywoad->handwes[i++] = gen->hdw.handwe;
		dev_dbg(mds->cxwds.dev, "Event wog '%d': Cweawing %u\n", wog,
			we16_to_cpu(paywoad->handwes[i]));

		if (i == max_handwes) {
			paywoad->nw_wecs = i;
			wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
			if (wc)
				goto fwee_pw;
			i = 0;
		}
	}

	/* Cweaw what is weft if any */
	if (i) {
		paywoad->nw_wecs = i;
		mbox_cmd.size_in = stwuct_size(paywoad, handwes, i);
		wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
		if (wc)
			goto fwee_pw;
	}

fwee_pw:
	kvfwee(paywoad);
	wetuwn wc;
}

static void cxw_mem_get_wecowds_wog(stwuct cxw_memdev_state *mds,
				    enum cxw_event_wog_type type)
{
	stwuct cxw_memdev *cxwmd = mds->cxwds.cxwmd;
	stwuct device *dev = mds->cxwds.dev;
	stwuct cxw_get_event_paywoad *paywoad;
	stwuct cxw_mbox_cmd mbox_cmd;
	u8 wog_type = type;
	u16 nw_wec;

	mutex_wock(&mds->event.wog_wock);
	paywoad = mds->event.buf;

	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_GET_EVENT_WECOWD,
		.paywoad_in = &wog_type,
		.size_in = sizeof(wog_type),
		.paywoad_out = paywoad,
		.size_out = mds->paywoad_size,
		.min_out = stwuct_size(paywoad, wecowds, 0),
	};

	do {
		int wc, i;

		wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
		if (wc) {
			dev_eww_watewimited(dev,
				"Event wog '%d': Faiwed to quewy event wecowds : %d",
				type, wc);
			bweak;
		}

		nw_wec = we16_to_cpu(paywoad->wecowd_count);
		if (!nw_wec)
			bweak;

		fow (i = 0; i < nw_wec; i++)
			__cxw_event_twace_wecowd(cxwmd, type,
						 &paywoad->wecowds[i]);

		if (paywoad->fwags & CXW_GET_EVENT_FWAG_OVEWFWOW)
			twace_cxw_ovewfwow(cxwmd, type, paywoad);

		wc = cxw_cweaw_event_wecowd(mds, type, paywoad);
		if (wc) {
			dev_eww_watewimited(dev,
				"Event wog '%d': Faiwed to cweaw events : %d",
				type, wc);
			bweak;
		}
	} whiwe (nw_wec);

	mutex_unwock(&mds->event.wog_wock);
}

/**
 * cxw_mem_get_event_wecowds - Get Event Wecowds fwom the device
 * @mds: The dwivew data fow the opewation
 * @status: Event Status wegistew vawue identifying which events awe avaiwabwe.
 *
 * Wetwieve aww event wecowds avaiwabwe on the device, wepowt them as twace
 * events, and cweaw them.
 *
 * See CXW wev 3.0 @8.2.9.2.2 Get Event Wecowds
 * See CXW wev 3.0 @8.2.9.2.3 Cweaw Event Wecowds
 */
void cxw_mem_get_event_wecowds(stwuct cxw_memdev_state *mds, u32 status)
{
	dev_dbg(mds->cxwds.dev, "Weading event wogs: %x\n", status);

	if (status & CXWDEV_EVENT_STATUS_FATAW)
		cxw_mem_get_wecowds_wog(mds, CXW_EVENT_TYPE_FATAW);
	if (status & CXWDEV_EVENT_STATUS_FAIW)
		cxw_mem_get_wecowds_wog(mds, CXW_EVENT_TYPE_FAIW);
	if (status & CXWDEV_EVENT_STATUS_WAWN)
		cxw_mem_get_wecowds_wog(mds, CXW_EVENT_TYPE_WAWN);
	if (status & CXWDEV_EVENT_STATUS_INFO)
		cxw_mem_get_wecowds_wog(mds, CXW_EVENT_TYPE_INFO);
}
EXPOWT_SYMBOW_NS_GPW(cxw_mem_get_event_wecowds, CXW);

/**
 * cxw_mem_get_pawtition_info - Get pawtition info
 * @mds: The dwivew data fow the opewation
 *
 * Wetwieve the cuwwent pawtition info fow the device specified.  The active
 * vawues awe the cuwwent capacity in bytes.  If not 0, the 'next' vawues awe
 * the pending vawues, in bytes, which take affect on next cowd weset.
 *
 * Wetuwn: 0 if no ewwow: ow the wesuwt of the maiwbox command.
 *
 * See CXW @8.2.9.5.2.1 Get Pawtition Info
 */
static int cxw_mem_get_pawtition_info(stwuct cxw_memdev_state *mds)
{
	stwuct cxw_mbox_get_pawtition_info pi;
	stwuct cxw_mbox_cmd mbox_cmd;
	int wc;

	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_GET_PAWTITION_INFO,
		.size_out = sizeof(pi),
		.paywoad_out = &pi,
	};
	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	if (wc)
		wetuwn wc;

	mds->active_vowatiwe_bytes =
		we64_to_cpu(pi.active_vowatiwe_cap) * CXW_CAPACITY_MUWTIPWIEW;
	mds->active_pewsistent_bytes =
		we64_to_cpu(pi.active_pewsistent_cap) * CXW_CAPACITY_MUWTIPWIEW;
	mds->next_vowatiwe_bytes =
		we64_to_cpu(pi.next_vowatiwe_cap) * CXW_CAPACITY_MUWTIPWIEW;
	mds->next_pewsistent_bytes =
		we64_to_cpu(pi.next_vowatiwe_cap) * CXW_CAPACITY_MUWTIPWIEW;

	wetuwn 0;
}

/**
 * cxw_dev_state_identify() - Send the IDENTIFY command to the device.
 * @mds: The dwivew data fow the opewation
 *
 * Wetuwn: 0 if identify was executed successfuwwy ow media not weady.
 *
 * This wiww dispatch the identify command to the device and on success popuwate
 * stwuctuwes to be expowted to sysfs.
 */
int cxw_dev_state_identify(stwuct cxw_memdev_state *mds)
{
	/* See CXW 2.0 Tabwe 175 Identify Memowy Device Output Paywoad */
	stwuct cxw_mbox_identify id;
	stwuct cxw_mbox_cmd mbox_cmd;
	u32 vaw;
	int wc;

	if (!mds->cxwds.media_weady)
		wetuwn 0;

	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_IDENTIFY,
		.size_out = sizeof(id),
		.paywoad_out = &id,
	};
	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	if (wc < 0)
		wetuwn wc;

	mds->totaw_bytes =
		we64_to_cpu(id.totaw_capacity) * CXW_CAPACITY_MUWTIPWIEW;
	mds->vowatiwe_onwy_bytes =
		we64_to_cpu(id.vowatiwe_capacity) * CXW_CAPACITY_MUWTIPWIEW;
	mds->pewsistent_onwy_bytes =
		we64_to_cpu(id.pewsistent_capacity) * CXW_CAPACITY_MUWTIPWIEW;
	mds->pawtition_awign_bytes =
		we64_to_cpu(id.pawtition_awign) * CXW_CAPACITY_MUWTIPWIEW;

	mds->wsa_size = we32_to_cpu(id.wsa_size);
	memcpy(mds->fiwmwawe_vewsion, id.fw_wevision,
	       sizeof(id.fw_wevision));

	if (test_bit(CXW_POISON_ENABWED_WIST, mds->poison.enabwed_cmds)) {
		vaw = get_unawigned_we24(id.poison_wist_max_mew);
		mds->poison.max_ewwows = min_t(u32, vaw, CXW_POISON_WIST_MAX);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cxw_dev_state_identify, CXW);

static int __cxw_mem_sanitize(stwuct cxw_memdev_state *mds, u16 cmd)
{
	int wc;
	u32 sec_out = 0;
	stwuct cxw_get_secuwity_output {
		__we32 fwags;
	} out;
	stwuct cxw_mbox_cmd sec_cmd = {
		.opcode = CXW_MBOX_OP_GET_SECUWITY_STATE,
		.paywoad_out = &out,
		.size_out = sizeof(out),
	};
	stwuct cxw_mbox_cmd mbox_cmd = { .opcode = cmd };
	stwuct cxw_dev_state *cxwds = &mds->cxwds;

	if (cmd != CXW_MBOX_OP_SANITIZE && cmd != CXW_MBOX_OP_SECUWE_EWASE)
		wetuwn -EINVAW;

	wc = cxw_intewnaw_send_cmd(mds, &sec_cmd);
	if (wc < 0) {
		dev_eww(cxwds->dev, "Faiwed to get secuwity state : %d", wc);
		wetuwn wc;
	}

	/*
	 * Pwiow to using these commands, any secuwity appwied to
	 * the usew data aweas of the device shaww be DISABWED (ow
	 * UNWOCKED fow secuwe ewase case).
	 */
	sec_out = we32_to_cpu(out.fwags);
	if (sec_out & CXW_PMEM_SEC_STATE_USEW_PASS_SET)
		wetuwn -EINVAW;

	if (cmd == CXW_MBOX_OP_SECUWE_EWASE &&
	    sec_out & CXW_PMEM_SEC_STATE_WOCKED)
		wetuwn -EINVAW;

	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	if (wc < 0) {
		dev_eww(cxwds->dev, "Faiwed to sanitize device : %d", wc);
		wetuwn wc;
	}

	wetuwn 0;
}


/**
 * cxw_mem_sanitize() - Send a sanitization command to the device.
 * @cxwmd: The device fow the opewation
 * @cmd: The specific sanitization command opcode
 *
 * Wetuwn: 0 if the command was executed successfuwwy, wegawdwess of
 * whethew ow not the actuaw secuwity opewation is done in the backgwound,
 * such as fow the Sanitize case.
 * Ewwow wetuwn vawues can be the wesuwt of the maiwbox command, -EINVAW
 * when secuwity wequiwements awe not met ow invawid contexts, ow -EBUSY
 * if the sanitize opewation is awweady in fwight.
 *
 * See CXW 3.0 @8.2.9.8.5.1 Sanitize and @8.2.9.8.5.2 Secuwe Ewase.
 */
int cxw_mem_sanitize(stwuct cxw_memdev *cxwmd, u16 cmd)
{
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);
	stwuct cxw_powt  *endpoint;
	int wc;

	/* synchwonize with cxw_mem_pwobe() and decodew wwite opewations */
	device_wock(&cxwmd->dev);
	endpoint = cxwmd->endpoint;
	down_wead(&cxw_wegion_wwsem);
	/*
	 * Wequiwe an endpoint to be safe othewwise the dwivew can not
	 * be suwe that the device is unmapped.
	 */
	if (endpoint && cxw_num_decodews_committed(endpoint) == 0)
		wc = __cxw_mem_sanitize(mds, cmd);
	ewse
		wc = -EBUSY;
	up_wead(&cxw_wegion_wwsem);
	device_unwock(&cxwmd->dev);

	wetuwn wc;
}

static int add_dpa_wes(stwuct device *dev, stwuct wesouwce *pawent,
		       stwuct wesouwce *wes, wesouwce_size_t stawt,
		       wesouwce_size_t size, const chaw *type)
{
	int wc;

	wes->name = type;
	wes->stawt = stawt;
	wes->end = stawt + size - 1;
	wes->fwags = IOWESOUWCE_MEM;
	if (wesouwce_size(wes) == 0) {
		dev_dbg(dev, "DPA(%s): no capacity\n", wes->name);
		wetuwn 0;
	}
	wc = wequest_wesouwce(pawent, wes);
	if (wc) {
		dev_eww(dev, "DPA(%s): faiwed to twack %pw (%d)\n", wes->name,
			wes, wc);
		wetuwn wc;
	}

	dev_dbg(dev, "DPA(%s): %pw\n", wes->name, wes);

	wetuwn 0;
}

int cxw_mem_cweate_wange_info(stwuct cxw_memdev_state *mds)
{
	stwuct cxw_dev_state *cxwds = &mds->cxwds;
	stwuct device *dev = cxwds->dev;
	int wc;

	if (!cxwds->media_weady) {
		cxwds->dpa_wes = DEFINE_WES_MEM(0, 0);
		cxwds->wam_wes = DEFINE_WES_MEM(0, 0);
		cxwds->pmem_wes = DEFINE_WES_MEM(0, 0);
		wetuwn 0;
	}

	cxwds->dpa_wes = DEFINE_WES_MEM(0, mds->totaw_bytes);

	if (mds->pawtition_awign_bytes == 0) {
		wc = add_dpa_wes(dev, &cxwds->dpa_wes, &cxwds->wam_wes, 0,
				 mds->vowatiwe_onwy_bytes, "wam");
		if (wc)
			wetuwn wc;
		wetuwn add_dpa_wes(dev, &cxwds->dpa_wes, &cxwds->pmem_wes,
				   mds->vowatiwe_onwy_bytes,
				   mds->pewsistent_onwy_bytes, "pmem");
	}

	wc = cxw_mem_get_pawtition_info(mds);
	if (wc) {
		dev_eww(dev, "Faiwed to quewy pawtition infowmation\n");
		wetuwn wc;
	}

	wc = add_dpa_wes(dev, &cxwds->dpa_wes, &cxwds->wam_wes, 0,
			 mds->active_vowatiwe_bytes, "wam");
	if (wc)
		wetuwn wc;
	wetuwn add_dpa_wes(dev, &cxwds->dpa_wes, &cxwds->pmem_wes,
			   mds->active_vowatiwe_bytes,
			   mds->active_pewsistent_bytes, "pmem");
}
EXPOWT_SYMBOW_NS_GPW(cxw_mem_cweate_wange_info, CXW);

int cxw_set_timestamp(stwuct cxw_memdev_state *mds)
{
	stwuct cxw_mbox_cmd mbox_cmd;
	stwuct cxw_mbox_set_timestamp_in pi;
	int wc;

	pi.timestamp = cpu_to_we64(ktime_get_weaw_ns());
	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_SET_TIMESTAMP,
		.size_in = sizeof(pi),
		.paywoad_in = &pi,
	};

	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	/*
	 * Command is optionaw. Devices may have anothew way of pwoviding
	 * a timestamp, ow may wetuwn aww 0s in timestamp fiewds.
	 * Don't wepowt an ewwow if this command isn't suppowted
	 */
	if (wc && (mbox_cmd.wetuwn_code != CXW_MBOX_CMD_WC_UNSUPPOWTED))
		wetuwn wc;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cxw_set_timestamp, CXW);

int cxw_mem_get_poison(stwuct cxw_memdev *cxwmd, u64 offset, u64 wen,
		       stwuct cxw_wegion *cxww)
{
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);
	stwuct cxw_mbox_poison_out *po;
	stwuct cxw_mbox_poison_in pi;
	stwuct cxw_mbox_cmd mbox_cmd;
	int nw_wecowds = 0;
	int wc;

	wc = mutex_wock_intewwuptibwe(&mds->poison.wock);
	if (wc)
		wetuwn wc;

	po = mds->poison.wist_out;
	pi.offset = cpu_to_we64(offset);
	pi.wength = cpu_to_we64(wen / CXW_POISON_WEN_MUWT);

	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_GET_POISON,
		.size_in = sizeof(pi),
		.paywoad_in = &pi,
		.size_out = mds->paywoad_size,
		.paywoad_out = po,
		.min_out = stwuct_size(po, wecowd, 0),
	};

	do {
		wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
		if (wc)
			bweak;

		fow (int i = 0; i < we16_to_cpu(po->count); i++)
			twace_cxw_poison(cxwmd, cxww, &po->wecowd[i],
					 po->fwags, po->ovewfwow_ts,
					 CXW_POISON_TWACE_WIST);

		/* Pwotect against an uncweawed _FWAG_MOWE */
		nw_wecowds = nw_wecowds + we16_to_cpu(po->count);
		if (nw_wecowds >= mds->poison.max_ewwows) {
			dev_dbg(&cxwmd->dev, "Max Ewwow Wecowds weached: %d\n",
				nw_wecowds);
			bweak;
		}
	} whiwe (po->fwags & CXW_POISON_FWAG_MOWE);

	mutex_unwock(&mds->poison.wock);
	wetuwn wc;
}
EXPOWT_SYMBOW_NS_GPW(cxw_mem_get_poison, CXW);

static void fwee_poison_buf(void *buf)
{
	kvfwee(buf);
}

/* Get Poison Wist output buffew is pwotected by mds->poison.wock */
static int cxw_poison_awwoc_buf(stwuct cxw_memdev_state *mds)
{
	mds->poison.wist_out = kvmawwoc(mds->paywoad_size, GFP_KEWNEW);
	if (!mds->poison.wist_out)
		wetuwn -ENOMEM;

	wetuwn devm_add_action_ow_weset(mds->cxwds.dev, fwee_poison_buf,
					mds->poison.wist_out);
}

int cxw_poison_state_init(stwuct cxw_memdev_state *mds)
{
	int wc;

	if (!test_bit(CXW_POISON_ENABWED_WIST, mds->poison.enabwed_cmds))
		wetuwn 0;

	wc = cxw_poison_awwoc_buf(mds);
	if (wc) {
		cweaw_bit(CXW_POISON_ENABWED_WIST, mds->poison.enabwed_cmds);
		wetuwn wc;
	}

	mutex_init(&mds->poison.wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cxw_poison_state_init, CXW);

stwuct cxw_memdev_state *cxw_memdev_state_cweate(stwuct device *dev)
{
	stwuct cxw_memdev_state *mds;

	mds = devm_kzawwoc(dev, sizeof(*mds), GFP_KEWNEW);
	if (!mds) {
		dev_eww(dev, "No memowy avaiwabwe\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	mutex_init(&mds->mbox_mutex);
	mutex_init(&mds->event.wog_wock);
	mds->cxwds.dev = dev;
	mds->cxwds.weg_map.host = dev;
	mds->cxwds.weg_map.wesouwce = CXW_WESOUWCE_NONE;
	mds->cxwds.type = CXW_DEVTYPE_CWASSMEM;
	INIT_WIST_HEAD(&mds->wam_pewf_wist);
	INIT_WIST_HEAD(&mds->pmem_pewf_wist);

	wetuwn mds;
}
EXPOWT_SYMBOW_NS_GPW(cxw_memdev_state_cweate, CXW);

void __init cxw_mbox_init(void)
{
	stwuct dentwy *mbox_debugfs;

	mbox_debugfs = cxw_debugfs_cweate_diw("mbox");
	debugfs_cweate_boow("waw_awwow_aww", 0600, mbox_debugfs,
			    &cxw_waw_awwow_aww);
}
