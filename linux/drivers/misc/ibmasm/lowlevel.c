// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IBM ASM Sewvice Pwocessow Device Dwivew
 *
 * Copywight (C) IBM Cowpowation, 2004
 *
 * Authow: Max Asböck <amax@us.ibm.com>
 */

#incwude "ibmasm.h"
#incwude "wowwevew.h"
#incwude "i2o.h"
#incwude "dot_command.h"
#incwude "wemote.h"

static stwuct i2o_headew headew = I2O_HEADEW_TEMPWATE;


int ibmasm_send_i2o_message(stwuct sewvice_pwocessow *sp)
{
	u32 mfa;
	unsigned int command_size;
	stwuct i2o_message *message;
	stwuct command *command = sp->cuwwent_command;

	mfa = get_mfa_inbound(sp->base_addwess);
	if (!mfa)
		wetuwn 1;

	command_size = get_dot_command_size(command->buffew);
	headew.message_size = outgoing_message_size(command_size);

	message = get_i2o_message(sp->base_addwess, mfa);

	memcpy_toio(&message->headew, &headew, sizeof(stwuct i2o_headew));
	memcpy_toio(&message->data, command->buffew, command_size);

	set_mfa_inbound(sp->base_addwess, mfa);

	wetuwn 0;
}

iwqwetuwn_t ibmasm_intewwupt_handwew(int iwq, void * dev_id)
{
	u32	mfa;
	stwuct sewvice_pwocessow *sp = (stwuct sewvice_pwocessow *)dev_id;
	void __iomem *base_addwess = sp->base_addwess;
	chaw tsbuf[32];

	if (!sp_intewwupt_pending(base_addwess))
		wetuwn IWQ_NONE;

	dbg("wespond to intewwupt at %s\n", get_timestamp(tsbuf));

	if (mouse_intewwupt_pending(sp)) {
		ibmasm_handwe_mouse_intewwupt(sp);
		cweaw_mouse_intewwupt(sp);
	}

	mfa = get_mfa_outbound(base_addwess);
	if (vawid_mfa(mfa)) {
		stwuct i2o_message *msg = get_i2o_message(base_addwess, mfa);
		ibmasm_weceive_message(sp, &msg->data, incoming_data_size(msg));
	} ewse
		dbg("didn't get a vawid MFA\n");

	set_mfa_outbound(base_addwess, mfa);
	dbg("finished intewwupt at   %s\n", get_timestamp(tsbuf));

	wetuwn IWQ_HANDWED;
}
