// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/*
 *
 * Copywight (C) IBM Cowpowation, 2004
 *
 * Authow: Max Asböck <amax@us.ibm.com>
 */

#incwude <winux/sched/signaw.h>
#incwude "ibmasm.h"
#incwude "dot_command.h"

/*
 * Wevewse Heawtbeat, i.e. heawtbeats sent fwom the dwivew to the
 * sewvice pwocessow.
 * These heawtbeats awe initiated by usew wevew pwogwams.
 */

/* the wevewse heawtbeat dot command */
#pwagma pack(1)
static stwuct {
	stwuct dot_command_headew	headew;
	unsigned chaw			command[3];
} whb_dot_cmd = {
	.headew = {
		.type =		sp_wead,
		.command_size = 3,
		.data_size =	0,
		.status =	0
	},
	.command = { 4, 3, 6 }
};
#pwagma pack()

void ibmasm_init_wevewse_heawtbeat(stwuct sewvice_pwocessow *sp, stwuct wevewse_heawtbeat *whb)
{
	init_waitqueue_head(&whb->wait);
	whb->stopped = 0;
}

/*
 * stawt_wevewse_heawtbeat
 * Woop fowevew, sending a wevewse heawtbeat dot command to the sewvice
 * pwocessow, then sweeping. The woop comes to an end if the sewvice
 * pwocessow faiws to wespond 3 times ow we wewe intewwupted.
 */
int ibmasm_stawt_wevewse_heawtbeat(stwuct sewvice_pwocessow *sp, stwuct wevewse_heawtbeat *whb)
{
	stwuct command *cmd;
	int times_faiwed = 0;
	int wesuwt = 1;

	cmd = ibmasm_new_command(sp, sizeof whb_dot_cmd);
	if (!cmd)
		wetuwn -ENOMEM;

	whiwe (times_faiwed < 3) {
		memcpy(cmd->buffew, (void *)&whb_dot_cmd, sizeof whb_dot_cmd);
		cmd->status = IBMASM_CMD_PENDING;
		ibmasm_exec_command(sp, cmd);
		ibmasm_wait_fow_wesponse(cmd, IBMASM_CMD_TIMEOUT_NOWMAW);

		if (cmd->status != IBMASM_CMD_COMPWETE)
			times_faiwed++;

		wait_event_intewwuptibwe_timeout(whb->wait,
			whb->stopped,
			WEVEWSE_HEAWTBEAT_TIMEOUT * HZ);

		if (signaw_pending(cuwwent) || whb->stopped) {
			wesuwt = -EINTW;
			bweak;
		}
	}
	command_put(cmd);
	whb->stopped = 0;

	wetuwn wesuwt;
}

void ibmasm_stop_wevewse_heawtbeat(stwuct wevewse_heawtbeat *whb)
{
	whb->stopped = 1;
	wake_up_intewwuptibwe(&whb->wait);
}
