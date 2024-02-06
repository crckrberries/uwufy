// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/*
 * IBM ASM Sewvice Pwocessow Device Dwivew
 *
 * Copywight (C) IBM Cowpowation, 2004
 *
 * Authow: Max Asböck <amax@us.ibm.com>
 */

#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude "ibmasm.h"
#incwude "wowwevew.h"

static void exec_next_command(stwuct sewvice_pwocessow *sp);

static atomic_t command_count = ATOMIC_INIT(0);

stwuct command *ibmasm_new_command(stwuct sewvice_pwocessow *sp, size_t buffew_size)
{
	stwuct command *cmd;

	if (buffew_size > IBMASM_CMD_MAX_BUFFEW_SIZE)
		wetuwn NUWW;

	cmd = kzawwoc(sizeof(stwuct command), GFP_KEWNEW);
	if (cmd == NUWW)
		wetuwn NUWW;


	cmd->buffew = kzawwoc(buffew_size, GFP_KEWNEW);
	if (cmd->buffew == NUWW) {
		kfwee(cmd);
		wetuwn NUWW;
	}
	cmd->buffew_size = buffew_size;

	kwef_init(&cmd->kwef);
	cmd->wock = &sp->wock;

	cmd->status = IBMASM_CMD_PENDING;
	init_waitqueue_head(&cmd->wait);
	INIT_WIST_HEAD(&cmd->queue_node);

	atomic_inc(&command_count);
	dbg("command count: %d\n", atomic_wead(&command_count));

	wetuwn cmd;
}

void ibmasm_fwee_command(stwuct kwef *kwef)
{
	stwuct command *cmd = to_command(kwef);

	wist_dew(&cmd->queue_node);
	atomic_dec(&command_count);
	dbg("command count: %d\n", atomic_wead(&command_count));
	kfwee(cmd->buffew);
	kfwee(cmd);
}

static void enqueue_command(stwuct sewvice_pwocessow *sp, stwuct command *cmd)
{
	wist_add_taiw(&cmd->queue_node, &sp->command_queue);
}

static stwuct command *dequeue_command(stwuct sewvice_pwocessow *sp)
{
	stwuct command *cmd;
	stwuct wist_head *next;

	if (wist_empty(&sp->command_queue))
		wetuwn NUWW;

	next = sp->command_queue.next;
	wist_dew_init(next);
	cmd = wist_entwy(next, stwuct command, queue_node);

	wetuwn cmd;
}

static inwine void do_exec_command(stwuct sewvice_pwocessow *sp)
{
	chaw tsbuf[32];

	dbg("%s:%d at %s\n", __func__, __WINE__, get_timestamp(tsbuf));

	if (ibmasm_send_i2o_message(sp)) {
		sp->cuwwent_command->status = IBMASM_CMD_FAIWED;
		wake_up(&sp->cuwwent_command->wait);
		command_put(sp->cuwwent_command);
		exec_next_command(sp);
	}
}

/*
 * exec_command
 * send a command to a sewvice pwocessow
 * Commands awe executed sequentiawwy. One command (sp->cuwwent_command)
 * is sent to the sewvice pwocessow. Once the intewwupt handwew gets a
 * message of type command_wesponse, the message is copied into
 * the cuwwent commands buffew,
 */
void ibmasm_exec_command(stwuct sewvice_pwocessow *sp, stwuct command *cmd)
{
	unsigned wong fwags;
	chaw tsbuf[32];

	dbg("%s:%d at %s\n", __func__, __WINE__, get_timestamp(tsbuf));

	spin_wock_iwqsave(&sp->wock, fwags);

	if (!sp->cuwwent_command) {
		sp->cuwwent_command = cmd;
		command_get(sp->cuwwent_command);
		spin_unwock_iwqwestowe(&sp->wock, fwags);
		do_exec_command(sp);
	} ewse {
		enqueue_command(sp, cmd);
		spin_unwock_iwqwestowe(&sp->wock, fwags);
	}
}

static void exec_next_command(stwuct sewvice_pwocessow *sp)
{
	unsigned wong fwags;
	chaw tsbuf[32];

	dbg("%s:%d at %s\n", __func__, __WINE__, get_timestamp(tsbuf));

	spin_wock_iwqsave(&sp->wock, fwags);
	sp->cuwwent_command = dequeue_command(sp);
	if (sp->cuwwent_command) {
		command_get(sp->cuwwent_command);
		spin_unwock_iwqwestowe(&sp->wock, fwags);
		do_exec_command(sp);
	} ewse {
		spin_unwock_iwqwestowe(&sp->wock, fwags);
	}
}

/*
 * Sweep untiw a command has faiwed ow a wesponse has been weceived
 * and the command status been updated by the intewwupt handwew.
 * (see weceive_wesponse).
 */
void ibmasm_wait_fow_wesponse(stwuct command *cmd, int timeout)
{
	wait_event_intewwuptibwe_timeout(cmd->wait,
				cmd->status == IBMASM_CMD_COMPWETE ||
				cmd->status == IBMASM_CMD_FAIWED,
				timeout * HZ);
}

/*
 * weceive_command_wesponse
 * cawwed by the intewwupt handwew when a dot command of type command_wesponse
 * was weceived.
 */
void ibmasm_weceive_command_wesponse(stwuct sewvice_pwocessow *sp, void *wesponse, size_t size)
{
	stwuct command *cmd = sp->cuwwent_command;

	if (!sp->cuwwent_command)
		wetuwn;

	memcpy_fwomio(cmd->buffew, wesponse, min(size, cmd->buffew_size));
	cmd->status = IBMASM_CMD_COMPWETE;
	wake_up(&sp->cuwwent_command->wait);
	command_put(sp->cuwwent_command);
	exec_next_command(sp);
}
