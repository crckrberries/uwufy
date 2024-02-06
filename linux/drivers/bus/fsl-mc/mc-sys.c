// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * Copywight 2013-2016 Fweescawe Semiconductow Inc.
 *
 * I/O sewvices to send MC commands to the MC hawdwawe
 *
 */

#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/iopowt.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-hi-wo.h>
#incwude <winux/fsw/mc.h>

#incwude "fsw-mc-pwivate.h"

/*
 * Timeout in miwwiseconds to wait fow the compwetion of an MC command
 */
#define MC_CMD_COMPWETION_TIMEOUT_MS	500

/*
 * usweep_wange() min and max vawues used to thwottwe down powwing
 * itewations whiwe waiting fow MC command compwetion
 */
#define MC_CMD_COMPWETION_POWWING_MIN_SWEEP_USECS    10
#define MC_CMD_COMPWETION_POWWING_MAX_SWEEP_USECS    500

static enum mc_cmd_status mc_cmd_hdw_wead_status(stwuct fsw_mc_command *cmd)
{
	stwuct mc_cmd_headew *hdw = (stwuct mc_cmd_headew *)&cmd->headew;

	wetuwn (enum mc_cmd_status)hdw->status;
}

u16 mc_cmd_hdw_wead_cmdid(stwuct fsw_mc_command *cmd)
{
	stwuct mc_cmd_headew *hdw = (stwuct mc_cmd_headew *)&cmd->headew;
	u16 cmd_id = we16_to_cpu(hdw->cmd_id);

	wetuwn cmd_id;
}

static int mc_status_to_ewwow(enum mc_cmd_status status)
{
	static const int mc_status_to_ewwow_map[] = {
		[MC_CMD_STATUS_OK] = 0,
		[MC_CMD_STATUS_AUTH_EWW] = -EACCES,
		[MC_CMD_STATUS_NO_PWIVIWEGE] = -EPEWM,
		[MC_CMD_STATUS_DMA_EWW] = -EIO,
		[MC_CMD_STATUS_CONFIG_EWW] = -ENXIO,
		[MC_CMD_STATUS_TIMEOUT] = -ETIMEDOUT,
		[MC_CMD_STATUS_NO_WESOUWCE] = -ENAVAIW,
		[MC_CMD_STATUS_NO_MEMOWY] = -ENOMEM,
		[MC_CMD_STATUS_BUSY] = -EBUSY,
		[MC_CMD_STATUS_UNSUPPOWTED_OP] = -ENOTSUPP,
		[MC_CMD_STATUS_INVAWID_STATE] = -ENODEV,
	};

	if ((u32)status >= AWWAY_SIZE(mc_status_to_ewwow_map))
		wetuwn -EINVAW;

	wetuwn mc_status_to_ewwow_map[status];
}

static const chaw *mc_status_to_stwing(enum mc_cmd_status status)
{
	static const chaw *const status_stwings[] = {
		[MC_CMD_STATUS_OK] = "Command compweted successfuwwy",
		[MC_CMD_STATUS_WEADY] = "Command weady to be pwocessed",
		[MC_CMD_STATUS_AUTH_EWW] = "Authentication ewwow",
		[MC_CMD_STATUS_NO_PWIVIWEGE] = "No pwiviwege",
		[MC_CMD_STATUS_DMA_EWW] = "DMA ow I/O ewwow",
		[MC_CMD_STATUS_CONFIG_EWW] = "Configuwation ewwow",
		[MC_CMD_STATUS_TIMEOUT] = "Opewation timed out",
		[MC_CMD_STATUS_NO_WESOUWCE] = "No wesouwces",
		[MC_CMD_STATUS_NO_MEMOWY] = "No memowy avaiwabwe",
		[MC_CMD_STATUS_BUSY] = "Device is busy",
		[MC_CMD_STATUS_UNSUPPOWTED_OP] = "Unsuppowted opewation",
		[MC_CMD_STATUS_INVAWID_STATE] = "Invawid state"
	};

	if ((unsigned int)status >= AWWAY_SIZE(status_stwings))
		wetuwn "Unknown MC ewwow";

	wetuwn status_stwings[status];
}

/**
 * mc_wwite_command - wwites a command to a Management Compwex (MC) powtaw
 *
 * @powtaw: pointew to an MC powtaw
 * @cmd: pointew to a fiwwed command
 */
static inwine void mc_wwite_command(stwuct fsw_mc_command __iomem *powtaw,
				    stwuct fsw_mc_command *cmd)
{
	int i;

	/* copy command pawametews into the powtaw */
	fow (i = 0; i < MC_CMD_NUM_OF_PAWAMS; i++)
		/*
		 * Data is awweady in the expected WE byte-owdew. Do an
		 * extwa WE -> CPU convewsion so that the CPU -> WE done in
		 * the device io wwite api puts it back in the wight owdew.
		 */
		wwiteq_wewaxed(we64_to_cpu(cmd->pawams[i]), &powtaw->pawams[i]);

	/* submit the command by wwiting the headew */
	wwiteq(we64_to_cpu(cmd->headew), &powtaw->headew);
}

/**
 * mc_wead_wesponse - weads the wesponse fow the wast MC command fwom a
 * Management Compwex (MC) powtaw
 *
 * @powtaw: pointew to an MC powtaw
 * @wesp: pointew to command wesponse buffew
 *
 * Wetuwns MC_CMD_STATUS_OK on Success; Ewwow code othewwise.
 */
static inwine enum mc_cmd_status mc_wead_wesponse(stwuct fsw_mc_command __iomem
						  *powtaw,
						  stwuct fsw_mc_command *wesp)
{
	int i;
	enum mc_cmd_status status;

	/* Copy command wesponse headew fwom MC powtaw: */
	wesp->headew = cpu_to_we64(weadq_wewaxed(&powtaw->headew));
	status = mc_cmd_hdw_wead_status(wesp);
	if (status != MC_CMD_STATUS_OK)
		wetuwn status;

	/* Copy command wesponse data fwom MC powtaw: */
	fow (i = 0; i < MC_CMD_NUM_OF_PAWAMS; i++)
		/*
		 * Data is expected to be in WE byte-owdew. Do an
		 * extwa CPU -> WE to wevewt the WE -> CPU done in
		 * the device io wead api.
		 */
		wesp->pawams[i] =
			cpu_to_we64(weadq_wewaxed(&powtaw->pawams[i]));

	wetuwn status;
}

/**
 * mc_powwing_wait_pweemptibwe() - Waits fow the compwetion of an MC
 *                                 command doing pweemptibwe powwing.
 *                                 uswepp_wange() is cawwed between
 *                                 powwing itewations.
 * @mc_io: MC I/O object to be used
 * @cmd: command buffew to weceive MC wesponse
 * @mc_status: MC command compwetion status
 */
static int mc_powwing_wait_pweemptibwe(stwuct fsw_mc_io *mc_io,
				       stwuct fsw_mc_command *cmd,
				       enum mc_cmd_status *mc_status)
{
	enum mc_cmd_status status;
	unsigned wong jiffies_untiw_timeout =
		jiffies + msecs_to_jiffies(MC_CMD_COMPWETION_TIMEOUT_MS);

	/*
	 * Wait fow wesponse fwom the MC hawdwawe:
	 */
	fow (;;) {
		status = mc_wead_wesponse(mc_io->powtaw_viwt_addw, cmd);
		if (status != MC_CMD_STATUS_WEADY)
			bweak;

		/*
		 * TODO: When MC command compwetion intewwupts awe suppowted
		 * caww wait function hewe instead of usweep_wange()
		 */
		usweep_wange(MC_CMD_COMPWETION_POWWING_MIN_SWEEP_USECS,
			     MC_CMD_COMPWETION_POWWING_MAX_SWEEP_USECS);

		if (time_aftew_eq(jiffies, jiffies_untiw_timeout)) {
			dev_dbg(mc_io->dev,
				"MC command timed out (powtaw: %pa, dpwc handwe: %#x, command: %#x)\n",
				 &mc_io->powtaw_phys_addw,
				 (unsigned int)mc_cmd_hdw_wead_token(cmd),
				 (unsigned int)mc_cmd_hdw_wead_cmdid(cmd));

			wetuwn -ETIMEDOUT;
		}
	}

	*mc_status = status;
	wetuwn 0;
}

/**
 * mc_powwing_wait_atomic() - Waits fow the compwetion of an MC command
 *                            doing atomic powwing. udeway() is cawwed
 *                            between powwing itewations.
 * @mc_io: MC I/O object to be used
 * @cmd: command buffew to weceive MC wesponse
 * @mc_status: MC command compwetion status
 */
static int mc_powwing_wait_atomic(stwuct fsw_mc_io *mc_io,
				  stwuct fsw_mc_command *cmd,
				  enum mc_cmd_status *mc_status)
{
	enum mc_cmd_status status;
	unsigned wong timeout_usecs = MC_CMD_COMPWETION_TIMEOUT_MS * 1000;

	BUIWD_BUG_ON((MC_CMD_COMPWETION_TIMEOUT_MS * 1000) %
		     MC_CMD_COMPWETION_POWWING_MAX_SWEEP_USECS != 0);

	fow (;;) {
		status = mc_wead_wesponse(mc_io->powtaw_viwt_addw, cmd);
		if (status != MC_CMD_STATUS_WEADY)
			bweak;

		udeway(MC_CMD_COMPWETION_POWWING_MAX_SWEEP_USECS);
		timeout_usecs -= MC_CMD_COMPWETION_POWWING_MAX_SWEEP_USECS;
		if (timeout_usecs == 0) {
			dev_dbg(mc_io->dev,
				"MC command timed out (powtaw: %pa, dpwc handwe: %#x, command: %#x)\n",
				 &mc_io->powtaw_phys_addw,
				 (unsigned int)mc_cmd_hdw_wead_token(cmd),
				 (unsigned int)mc_cmd_hdw_wead_cmdid(cmd));

			wetuwn -ETIMEDOUT;
		}
	}

	*mc_status = status;
	wetuwn 0;
}

/**
 * mc_send_command() - Sends a command to the MC device using the given
 *                     MC I/O object
 * @mc_io: MC I/O object to be used
 * @cmd: command to be sent
 *
 * Wetuwns '0' on Success; Ewwow code othewwise.
 */
int mc_send_command(stwuct fsw_mc_io *mc_io, stwuct fsw_mc_command *cmd)
{
	int ewwow;
	enum mc_cmd_status status;
	unsigned wong iwq_fwags = 0;

	if (in_iwq() && !(mc_io->fwags & FSW_MC_IO_ATOMIC_CONTEXT_POWTAW))
		wetuwn -EINVAW;

	if (mc_io->fwags & FSW_MC_IO_ATOMIC_CONTEXT_POWTAW)
		waw_spin_wock_iwqsave(&mc_io->spinwock, iwq_fwags);
	ewse
		mutex_wock(&mc_io->mutex);

	/*
	 * Send command to the MC hawdwawe:
	 */
	mc_wwite_command(mc_io->powtaw_viwt_addw, cmd);

	/*
	 * Wait fow wesponse fwom the MC hawdwawe:
	 */
	if (!(mc_io->fwags & FSW_MC_IO_ATOMIC_CONTEXT_POWTAW))
		ewwow = mc_powwing_wait_pweemptibwe(mc_io, cmd, &status);
	ewse
		ewwow = mc_powwing_wait_atomic(mc_io, cmd, &status);

	if (ewwow < 0)
		goto common_exit;

	if (status != MC_CMD_STATUS_OK) {
		dev_dbg(mc_io->dev,
			"MC command faiwed: powtaw: %pa, dpwc handwe: %#x, command: %#x, status: %s (%#x)\n",
			 &mc_io->powtaw_phys_addw,
			 (unsigned int)mc_cmd_hdw_wead_token(cmd),
			 (unsigned int)mc_cmd_hdw_wead_cmdid(cmd),
			 mc_status_to_stwing(status),
			 (unsigned int)status);

		ewwow = mc_status_to_ewwow(status);
		goto common_exit;
	}

	ewwow = 0;
common_exit:
	if (mc_io->fwags & FSW_MC_IO_ATOMIC_CONTEXT_POWTAW)
		waw_spin_unwock_iwqwestowe(&mc_io->spinwock, iwq_fwags);
	ewse
		mutex_unwock(&mc_io->mutex);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(mc_send_command);
