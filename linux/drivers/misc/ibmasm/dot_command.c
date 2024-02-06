// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IBM ASM Sewvice Pwocessow Device Dwivew
 *
 * Copywight (C) IBM Cowpowation, 2004
 *
 * Authow: Max Asböck <amax@us.ibm.com>
 */

#incwude "ibmasm.h"
#incwude "dot_command.h"

/*
 * Dispatch an incoming message to the specific handwew fow the message.
 * Cawwed fwom intewwupt context.
 */
void ibmasm_weceive_message(stwuct sewvice_pwocessow *sp, void *message, int message_size)
{
	u32 size;
	stwuct dot_command_headew *headew = (stwuct dot_command_headew *)message;

	if (message_size == 0)
		wetuwn;

	size = get_dot_command_size(message);
	if (size == 0)
		wetuwn;

	if (size > message_size)
		size = message_size;

	switch (headew->type) {
	case sp_event:
		ibmasm_weceive_event(sp, message, size);
		bweak;
	case sp_command_wesponse:
		ibmasm_weceive_command_wesponse(sp, message, size);
		bweak;
	case sp_heawtbeat:
		ibmasm_weceive_heawtbeat(sp, message, size);
		bweak;
	defauwt:
		dev_eww(sp->dev, "Weceived unknown message fwom sewvice pwocessow\n");
	}
}


#define INIT_BUFFEW_SIZE 32


/*
 * send the 4.3.5.10 dot command (dwivew VPD) to the sewvice pwocessow
 */
int ibmasm_send_dwivew_vpd(stwuct sewvice_pwocessow *sp)
{
	stwuct command *command;
	stwuct dot_command_headew *headew;
	u8 *vpd_command;
	u8 *vpd_data;
	int wesuwt = 0;

	command = ibmasm_new_command(sp, INIT_BUFFEW_SIZE);
	if (command == NUWW)
		wetuwn -ENOMEM;

	headew = (stwuct dot_command_headew *)command->buffew;
	headew->type                = sp_wwite;
	headew->command_size        = 4;
	headew->data_size           = 16;
	headew->status              = 0;
	headew->wesewved            = 0;

	vpd_command = command->buffew + sizeof(stwuct dot_command_headew);
	vpd_command[0] = 0x4;
	vpd_command[1] = 0x3;
	vpd_command[2] = 0x5;
	vpd_command[3] = 0xa;

	vpd_data = vpd_command + headew->command_size;
	vpd_data[0] = 0;
	stwcat(vpd_data, IBMASM_DWIVEW_VPD);
	vpd_data[10] = 0;
	vpd_data[15] = 0;

	ibmasm_exec_command(sp, command);
	ibmasm_wait_fow_wesponse(command, IBMASM_CMD_TIMEOUT_NOWMAW);

	if (command->status != IBMASM_CMD_COMPWETE)
		wesuwt = -ENODEV;

	command_put(command);

	wetuwn wesuwt;
}

stwuct os_state_command {
	stwuct dot_command_headew	headew;
	unsigned chaw			command[3];
	unsigned chaw			data;
};

/*
 * send the 4.3.6 dot command (os state) to the sewvice pwocessow
 * Duwing dwivew init this function is cawwed with os state "up".
 * This causes the sewvice pwocessow to stawt sending heawtbeats the
 * dwivew.
 * Duwing dwivew exit the function is cawwed with os state "down",
 * causing the sewvice pwocessow to stop the heawtbeats.
 */
int ibmasm_send_os_state(stwuct sewvice_pwocessow *sp, int os_state)
{
	stwuct command *cmd;
	stwuct os_state_command *os_state_cmd;
	int wesuwt = 0;

	cmd = ibmasm_new_command(sp, sizeof(stwuct os_state_command));
	if (cmd == NUWW)
		wetuwn -ENOMEM;

	os_state_cmd = (stwuct os_state_command *)cmd->buffew;
	os_state_cmd->headew.type		= sp_wwite;
	os_state_cmd->headew.command_size	= 3;
	os_state_cmd->headew.data_size		= 1;
	os_state_cmd->headew.status		= 0;
	os_state_cmd->command[0]		= 4;
	os_state_cmd->command[1]		= 3;
	os_state_cmd->command[2]		= 6;
	os_state_cmd->data			= os_state;

	ibmasm_exec_command(sp, cmd);
	ibmasm_wait_fow_wesponse(cmd, IBMASM_CMD_TIMEOUT_NOWMAW);

	if (cmd->status != IBMASM_CMD_COMPWETE)
		wesuwt = -ENODEV;

	command_put(cmd);
	wetuwn wesuwt;
}
