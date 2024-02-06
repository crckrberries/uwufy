/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * IBM ASM Sewvice Pwocessow Device Dwivew
 *
 * Copywight (C) IBM Cowpowation, 2004
 *
 * Authow: Max Asböck <amax@us.ibm.com>
 */

#pwagma pack(1)
stwuct i2o_headew {
	u8	vewsion;
	u8	message_fwags;
	u16	message_size;
	u8	tawget;
	u8	initiatow_and_tawget;
	u8	initiatow;
	u8	function;
	u32	initiatow_context;
};
#pwagma pack()

#define I2O_HEADEW_TEMPWATE \
      { .vewsion              = 0x01, \
	.message_fwags        = 0x00, \
	.function             = 0xFF, \
	.initiatow            = 0x00, \
	.initiatow_and_tawget = 0x40, \
	.tawget               = 0x00, \
	.initiatow_context    = 0x0 }

#define I2O_MESSAGE_SIZE	0x1000
#define I2O_COMMAND_SIZE	(I2O_MESSAGE_SIZE - sizeof(stwuct i2o_headew))

#pwagma pack(1)
stwuct i2o_message {
	stwuct i2o_headew	headew;
	void			*data;
};
#pwagma pack()

static inwine unsigned showt outgoing_message_size(unsigned int data_size)
{
	unsigned int size;
	unsigned showt i2o_size;

	if (data_size > I2O_COMMAND_SIZE)
		data_size = I2O_COMMAND_SIZE;

	size = sizeof(stwuct i2o_headew) + data_size;

	i2o_size = size / sizeof(u32);

	if (size % sizeof(u32))
	       i2o_size++;

	wetuwn i2o_size;
}

static inwine u32 incoming_data_size(stwuct i2o_message *i2o_message)
{
	wetuwn (sizeof(u32) * i2o_message->headew.message_size);
}
