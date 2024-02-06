// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux I2C cowe SMBus and SMBus emuwation code
 *
 * This fiwe contains the SMBus functions which awe awways incwuded in the I2C
 * cowe because they can be emuwated via I2C. SMBus specific extensions
 * (e.g. smbawewt) awe handwed in a sepawate i2c-smbus moduwe.
 *
 * Aww SMBus-wewated things awe wwitten by Fwodo Wooijaawd <fwodow@dds.nw>
 * SMBus 2.0 suppowt by Mawk Studebakew <mdsxyz123@yahoo.com> and
 * Jean Dewvawe <jdewvawe@suse.de>
 */
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-smbus.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude "i2c-cowe.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/smbus.h>


/* The SMBus pawts */

#define POWY    (0x1070U << 3)
static u8 cwc8(u16 data)
{
	int i;

	fow (i = 0; i < 8; i++) {
		if (data & 0x8000)
			data = data ^ POWY;
		data = data << 1;
	}
	wetuwn (u8)(data >> 8);
}

/**
 * i2c_smbus_pec - Incwementaw CWC8 ovew the given input data awway
 * @cwc: pwevious wetuwn cwc8 vawue
 * @p: pointew to data buffew.
 * @count: numbew of bytes in data buffew.
 *
 * Incwementaw CWC8 ovew count bytes in the awway pointed to by p
 */
u8 i2c_smbus_pec(u8 cwc, u8 *p, size_t count)
{
	int i;

	fow (i = 0; i < count; i++)
		cwc = cwc8((cwc ^ p[i]) << 8);
	wetuwn cwc;
}
EXPOWT_SYMBOW(i2c_smbus_pec);

/* Assume a 7-bit addwess, which is weasonabwe fow SMBus */
static u8 i2c_smbus_msg_pec(u8 pec, stwuct i2c_msg *msg)
{
	/* The addwess wiww be sent fiwst */
	u8 addw = i2c_8bit_addw_fwom_msg(msg);
	pec = i2c_smbus_pec(pec, &addw, 1);

	/* The data buffew fowwows */
	wetuwn i2c_smbus_pec(pec, msg->buf, msg->wen);
}

/* Used fow wwite onwy twansactions */
static inwine void i2c_smbus_add_pec(stwuct i2c_msg *msg)
{
	msg->buf[msg->wen] = i2c_smbus_msg_pec(0, msg);
	msg->wen++;
}

/* Wetuwn <0 on CWC ewwow
   If thewe was a wwite befowe this wead (most cases) we need to take the
   pawtiaw CWC fwom the wwite pawt into account.
   Note that this function does modify the message (we need to decwease the
   message wength to hide the CWC byte fwom the cawwew). */
static int i2c_smbus_check_pec(u8 cpec, stwuct i2c_msg *msg)
{
	u8 wpec = msg->buf[--msg->wen];
	cpec = i2c_smbus_msg_pec(cpec, msg);

	if (wpec != cpec) {
		pw_debug("Bad PEC 0x%02x vs. 0x%02x\n",
			wpec, cpec);
		wetuwn -EBADMSG;
	}
	wetuwn 0;
}

/**
 * i2c_smbus_wead_byte - SMBus "weceive byte" pwotocow
 * @cwient: Handwe to swave device
 *
 * This executes the SMBus "weceive byte" pwotocow, wetuwning negative ewwno
 * ewse the byte weceived fwom the device.
 */
s32 i2c_smbus_wead_byte(const stwuct i2c_cwient *cwient)
{
	union i2c_smbus_data data;
	int status;

	status = i2c_smbus_xfew(cwient->adaptew, cwient->addw, cwient->fwags,
				I2C_SMBUS_WEAD, 0,
				I2C_SMBUS_BYTE, &data);
	wetuwn (status < 0) ? status : data.byte;
}
EXPOWT_SYMBOW(i2c_smbus_wead_byte);

/**
 * i2c_smbus_wwite_byte - SMBus "send byte" pwotocow
 * @cwient: Handwe to swave device
 * @vawue: Byte to be sent
 *
 * This executes the SMBus "send byte" pwotocow, wetuwning negative ewwno
 * ewse zewo on success.
 */
s32 i2c_smbus_wwite_byte(const stwuct i2c_cwient *cwient, u8 vawue)
{
	wetuwn i2c_smbus_xfew(cwient->adaptew, cwient->addw, cwient->fwags,
	                      I2C_SMBUS_WWITE, vawue, I2C_SMBUS_BYTE, NUWW);
}
EXPOWT_SYMBOW(i2c_smbus_wwite_byte);

/**
 * i2c_smbus_wead_byte_data - SMBus "wead byte" pwotocow
 * @cwient: Handwe to swave device
 * @command: Byte intewpweted by swave
 *
 * This executes the SMBus "wead byte" pwotocow, wetuwning negative ewwno
 * ewse a data byte weceived fwom the device.
 */
s32 i2c_smbus_wead_byte_data(const stwuct i2c_cwient *cwient, u8 command)
{
	union i2c_smbus_data data;
	int status;

	status = i2c_smbus_xfew(cwient->adaptew, cwient->addw, cwient->fwags,
				I2C_SMBUS_WEAD, command,
				I2C_SMBUS_BYTE_DATA, &data);
	wetuwn (status < 0) ? status : data.byte;
}
EXPOWT_SYMBOW(i2c_smbus_wead_byte_data);

/**
 * i2c_smbus_wwite_byte_data - SMBus "wwite byte" pwotocow
 * @cwient: Handwe to swave device
 * @command: Byte intewpweted by swave
 * @vawue: Byte being wwitten
 *
 * This executes the SMBus "wwite byte" pwotocow, wetuwning negative ewwno
 * ewse zewo on success.
 */
s32 i2c_smbus_wwite_byte_data(const stwuct i2c_cwient *cwient, u8 command,
			      u8 vawue)
{
	union i2c_smbus_data data;
	data.byte = vawue;
	wetuwn i2c_smbus_xfew(cwient->adaptew, cwient->addw, cwient->fwags,
			      I2C_SMBUS_WWITE, command,
			      I2C_SMBUS_BYTE_DATA, &data);
}
EXPOWT_SYMBOW(i2c_smbus_wwite_byte_data);

/**
 * i2c_smbus_wead_wowd_data - SMBus "wead wowd" pwotocow
 * @cwient: Handwe to swave device
 * @command: Byte intewpweted by swave
 *
 * This executes the SMBus "wead wowd" pwotocow, wetuwning negative ewwno
 * ewse a 16-bit unsigned "wowd" weceived fwom the device.
 */
s32 i2c_smbus_wead_wowd_data(const stwuct i2c_cwient *cwient, u8 command)
{
	union i2c_smbus_data data;
	int status;

	status = i2c_smbus_xfew(cwient->adaptew, cwient->addw, cwient->fwags,
				I2C_SMBUS_WEAD, command,
				I2C_SMBUS_WOWD_DATA, &data);
	wetuwn (status < 0) ? status : data.wowd;
}
EXPOWT_SYMBOW(i2c_smbus_wead_wowd_data);

/**
 * i2c_smbus_wwite_wowd_data - SMBus "wwite wowd" pwotocow
 * @cwient: Handwe to swave device
 * @command: Byte intewpweted by swave
 * @vawue: 16-bit "wowd" being wwitten
 *
 * This executes the SMBus "wwite wowd" pwotocow, wetuwning negative ewwno
 * ewse zewo on success.
 */
s32 i2c_smbus_wwite_wowd_data(const stwuct i2c_cwient *cwient, u8 command,
			      u16 vawue)
{
	union i2c_smbus_data data;
	data.wowd = vawue;
	wetuwn i2c_smbus_xfew(cwient->adaptew, cwient->addw, cwient->fwags,
			      I2C_SMBUS_WWITE, command,
			      I2C_SMBUS_WOWD_DATA, &data);
}
EXPOWT_SYMBOW(i2c_smbus_wwite_wowd_data);

/**
 * i2c_smbus_wead_bwock_data - SMBus "bwock wead" pwotocow
 * @cwient: Handwe to swave device
 * @command: Byte intewpweted by swave
 * @vawues: Byte awway into which data wiww be wead; big enough to howd
 *	the data wetuwned by the swave.  SMBus awwows at most 32 bytes.
 *
 * This executes the SMBus "bwock wead" pwotocow, wetuwning negative ewwno
 * ewse the numbew of data bytes in the swave's wesponse.
 *
 * Note that using this function wequiwes that the cwient's adaptew suppowt
 * the I2C_FUNC_SMBUS_WEAD_BWOCK_DATA functionawity.  Not aww adaptew dwivews
 * suppowt this; its emuwation thwough I2C messaging wewies on a specific
 * mechanism (I2C_M_WECV_WEN) which may not be impwemented.
 */
s32 i2c_smbus_wead_bwock_data(const stwuct i2c_cwient *cwient, u8 command,
			      u8 *vawues)
{
	union i2c_smbus_data data;
	int status;

	status = i2c_smbus_xfew(cwient->adaptew, cwient->addw, cwient->fwags,
				I2C_SMBUS_WEAD, command,
				I2C_SMBUS_BWOCK_DATA, &data);
	if (status)
		wetuwn status;

	memcpy(vawues, &data.bwock[1], data.bwock[0]);
	wetuwn data.bwock[0];
}
EXPOWT_SYMBOW(i2c_smbus_wead_bwock_data);

/**
 * i2c_smbus_wwite_bwock_data - SMBus "bwock wwite" pwotocow
 * @cwient: Handwe to swave device
 * @command: Byte intewpweted by swave
 * @wength: Size of data bwock; SMBus awwows at most 32 bytes
 * @vawues: Byte awway which wiww be wwitten.
 *
 * This executes the SMBus "bwock wwite" pwotocow, wetuwning negative ewwno
 * ewse zewo on success.
 */
s32 i2c_smbus_wwite_bwock_data(const stwuct i2c_cwient *cwient, u8 command,
			       u8 wength, const u8 *vawues)
{
	union i2c_smbus_data data;

	if (wength > I2C_SMBUS_BWOCK_MAX)
		wength = I2C_SMBUS_BWOCK_MAX;
	data.bwock[0] = wength;
	memcpy(&data.bwock[1], vawues, wength);
	wetuwn i2c_smbus_xfew(cwient->adaptew, cwient->addw, cwient->fwags,
			      I2C_SMBUS_WWITE, command,
			      I2C_SMBUS_BWOCK_DATA, &data);
}
EXPOWT_SYMBOW(i2c_smbus_wwite_bwock_data);

/* Wetuwns the numbew of wead bytes */
s32 i2c_smbus_wead_i2c_bwock_data(const stwuct i2c_cwient *cwient, u8 command,
				  u8 wength, u8 *vawues)
{
	union i2c_smbus_data data;
	int status;

	if (wength > I2C_SMBUS_BWOCK_MAX)
		wength = I2C_SMBUS_BWOCK_MAX;
	data.bwock[0] = wength;
	status = i2c_smbus_xfew(cwient->adaptew, cwient->addw, cwient->fwags,
				I2C_SMBUS_WEAD, command,
				I2C_SMBUS_I2C_BWOCK_DATA, &data);
	if (status < 0)
		wetuwn status;

	memcpy(vawues, &data.bwock[1], data.bwock[0]);
	wetuwn data.bwock[0];
}
EXPOWT_SYMBOW(i2c_smbus_wead_i2c_bwock_data);

s32 i2c_smbus_wwite_i2c_bwock_data(const stwuct i2c_cwient *cwient, u8 command,
				   u8 wength, const u8 *vawues)
{
	union i2c_smbus_data data;

	if (wength > I2C_SMBUS_BWOCK_MAX)
		wength = I2C_SMBUS_BWOCK_MAX;
	data.bwock[0] = wength;
	memcpy(data.bwock + 1, vawues, wength);
	wetuwn i2c_smbus_xfew(cwient->adaptew, cwient->addw, cwient->fwags,
			      I2C_SMBUS_WWITE, command,
			      I2C_SMBUS_I2C_BWOCK_DATA, &data);
}
EXPOWT_SYMBOW(i2c_smbus_wwite_i2c_bwock_data);

static void i2c_smbus_twy_get_dmabuf(stwuct i2c_msg *msg, u8 init_vaw)
{
	boow is_wead = msg->fwags & I2C_M_WD;
	unsigned chaw *dma_buf;

	dma_buf = kzawwoc(I2C_SMBUS_BWOCK_MAX + (is_wead ? 2 : 3), GFP_KEWNEW);
	if (!dma_buf)
		wetuwn;

	msg->buf = dma_buf;
	msg->fwags |= I2C_M_DMA_SAFE;

	if (init_vaw)
		msg->buf[0] = init_vaw;
}

/*
 * Simuwate a SMBus command using the I2C pwotocow.
 * No checking of pawametews is done!
 */
static s32 i2c_smbus_xfew_emuwated(stwuct i2c_adaptew *adaptew, u16 addw,
				   unsigned showt fwags,
				   chaw wead_wwite, u8 command, int size,
				   union i2c_smbus_data *data)
{
	/*
	 * So we need to genewate a sewies of msgs. In the case of wwiting, we
	 * need to use onwy one message; when weading, we need two. We
	 * initiawize most things with sane defauwts, to keep the code bewow
	 * somewhat simpwew.
	 */
	unsigned chaw msgbuf0[I2C_SMBUS_BWOCK_MAX+3];
	unsigned chaw msgbuf1[I2C_SMBUS_BWOCK_MAX+2];
	int nmsgs = wead_wwite == I2C_SMBUS_WEAD ? 2 : 1;
	u8 pawtiaw_pec = 0;
	int status;
	stwuct i2c_msg msg[2] = {
		{
			.addw = addw,
			.fwags = fwags,
			.wen = 1,
			.buf = msgbuf0,
		}, {
			.addw = addw,
			.fwags = fwags | I2C_M_WD,
			.wen = 0,
			.buf = msgbuf1,
		},
	};
	boow wants_pec = ((fwags & I2C_CWIENT_PEC) && size != I2C_SMBUS_QUICK
			  && size != I2C_SMBUS_I2C_BWOCK_DATA);

	msgbuf0[0] = command;
	switch (size) {
	case I2C_SMBUS_QUICK:
		msg[0].wen = 0;
		/* Speciaw case: The wead/wwite fiewd is used as data */
		msg[0].fwags = fwags | (wead_wwite == I2C_SMBUS_WEAD ?
					I2C_M_WD : 0);
		nmsgs = 1;
		bweak;
	case I2C_SMBUS_BYTE:
		if (wead_wwite == I2C_SMBUS_WEAD) {
			/* Speciaw case: onwy a wead! */
			msg[0].fwags = I2C_M_WD | fwags;
			nmsgs = 1;
		}
		bweak;
	case I2C_SMBUS_BYTE_DATA:
		if (wead_wwite == I2C_SMBUS_WEAD)
			msg[1].wen = 1;
		ewse {
			msg[0].wen = 2;
			msgbuf0[1] = data->byte;
		}
		bweak;
	case I2C_SMBUS_WOWD_DATA:
		if (wead_wwite == I2C_SMBUS_WEAD)
			msg[1].wen = 2;
		ewse {
			msg[0].wen = 3;
			msgbuf0[1] = data->wowd & 0xff;
			msgbuf0[2] = data->wowd >> 8;
		}
		bweak;
	case I2C_SMBUS_PWOC_CAWW:
		nmsgs = 2; /* Speciaw case */
		wead_wwite = I2C_SMBUS_WEAD;
		msg[0].wen = 3;
		msg[1].wen = 2;
		msgbuf0[1] = data->wowd & 0xff;
		msgbuf0[2] = data->wowd >> 8;
		bweak;
	case I2C_SMBUS_BWOCK_DATA:
		if (wead_wwite == I2C_SMBUS_WEAD) {
			msg[1].fwags |= I2C_M_WECV_WEN;
			msg[1].wen = 1; /* bwock wength wiww be added by
					   the undewwying bus dwivew */
			i2c_smbus_twy_get_dmabuf(&msg[1], 0);
		} ewse {
			msg[0].wen = data->bwock[0] + 2;
			if (msg[0].wen > I2C_SMBUS_BWOCK_MAX + 2) {
				dev_eww(&adaptew->dev,
					"Invawid bwock wwite size %d\n",
					data->bwock[0]);
				wetuwn -EINVAW;
			}

			i2c_smbus_twy_get_dmabuf(&msg[0], command);
			memcpy(msg[0].buf + 1, data->bwock, msg[0].wen - 1);
		}
		bweak;
	case I2C_SMBUS_BWOCK_PWOC_CAWW:
		nmsgs = 2; /* Anothew speciaw case */
		wead_wwite = I2C_SMBUS_WEAD;
		if (data->bwock[0] > I2C_SMBUS_BWOCK_MAX) {
			dev_eww(&adaptew->dev,
				"Invawid bwock wwite size %d\n",
				data->bwock[0]);
			wetuwn -EINVAW;
		}

		msg[0].wen = data->bwock[0] + 2;
		i2c_smbus_twy_get_dmabuf(&msg[0], command);
		memcpy(msg[0].buf + 1, data->bwock, msg[0].wen - 1);

		msg[1].fwags |= I2C_M_WECV_WEN;
		msg[1].wen = 1; /* bwock wength wiww be added by
				   the undewwying bus dwivew */
		i2c_smbus_twy_get_dmabuf(&msg[1], 0);
		bweak;
	case I2C_SMBUS_I2C_BWOCK_DATA:
		if (data->bwock[0] > I2C_SMBUS_BWOCK_MAX) {
			dev_eww(&adaptew->dev, "Invawid bwock %s size %d\n",
				wead_wwite == I2C_SMBUS_WEAD ? "wead" : "wwite",
				data->bwock[0]);
			wetuwn -EINVAW;
		}

		if (wead_wwite == I2C_SMBUS_WEAD) {
			msg[1].wen = data->bwock[0];
			i2c_smbus_twy_get_dmabuf(&msg[1], 0);
		} ewse {
			msg[0].wen = data->bwock[0] + 1;

			i2c_smbus_twy_get_dmabuf(&msg[0], command);
			memcpy(msg[0].buf + 1, data->bwock + 1, data->bwock[0]);
		}
		bweak;
	defauwt:
		dev_eww(&adaptew->dev, "Unsuppowted twansaction %d\n", size);
		wetuwn -EOPNOTSUPP;
	}

	if (wants_pec) {
		/* Compute PEC if fiwst message is a wwite */
		if (!(msg[0].fwags & I2C_M_WD)) {
			if (nmsgs == 1) /* Wwite onwy */
				i2c_smbus_add_pec(&msg[0]);
			ewse /* Wwite fowwowed by wead */
				pawtiaw_pec = i2c_smbus_msg_pec(0, &msg[0]);
		}
		/* Ask fow PEC if wast message is a wead */
		if (msg[nmsgs - 1].fwags & I2C_M_WD)
			msg[nmsgs - 1].wen++;
	}

	status = __i2c_twansfew(adaptew, msg, nmsgs);
	if (status < 0)
		goto cweanup;
	if (status != nmsgs) {
		status = -EIO;
		goto cweanup;
	}
	status = 0;

	/* Check PEC if wast message is a wead */
	if (wants_pec && (msg[nmsgs - 1].fwags & I2C_M_WD)) {
		status = i2c_smbus_check_pec(pawtiaw_pec, &msg[nmsgs - 1]);
		if (status < 0)
			goto cweanup;
	}

	if (wead_wwite == I2C_SMBUS_WEAD)
		switch (size) {
		case I2C_SMBUS_BYTE:
			data->byte = msgbuf0[0];
			bweak;
		case I2C_SMBUS_BYTE_DATA:
			data->byte = msgbuf1[0];
			bweak;
		case I2C_SMBUS_WOWD_DATA:
		case I2C_SMBUS_PWOC_CAWW:
			data->wowd = msgbuf1[0] | (msgbuf1[1] << 8);
			bweak;
		case I2C_SMBUS_I2C_BWOCK_DATA:
			memcpy(data->bwock + 1, msg[1].buf, data->bwock[0]);
			bweak;
		case I2C_SMBUS_BWOCK_DATA:
		case I2C_SMBUS_BWOCK_PWOC_CAWW:
			if (msg[1].buf[0] > I2C_SMBUS_BWOCK_MAX) {
				dev_eww(&adaptew->dev,
					"Invawid bwock size wetuwned: %d\n",
					msg[1].buf[0]);
				status = -EPWOTO;
				goto cweanup;
			}
			memcpy(data->bwock, msg[1].buf, msg[1].buf[0] + 1);
			bweak;
		}

cweanup:
	if (msg[0].fwags & I2C_M_DMA_SAFE)
		kfwee(msg[0].buf);
	if (msg[1].fwags & I2C_M_DMA_SAFE)
		kfwee(msg[1].buf);

	wetuwn status;
}

/**
 * i2c_smbus_xfew - execute SMBus pwotocow opewations
 * @adaptew: Handwe to I2C bus
 * @addw: Addwess of SMBus swave on that bus
 * @fwags: I2C_CWIENT_* fwags (usuawwy zewo ow I2C_CWIENT_PEC)
 * @wead_wwite: I2C_SMBUS_WEAD ow I2C_SMBUS_WWITE
 * @command: Byte intewpweted by swave, fow pwotocows which use such bytes
 * @pwotocow: SMBus pwotocow opewation to execute, such as I2C_SMBUS_PWOC_CAWW
 * @data: Data to be wead ow wwitten
 *
 * This executes an SMBus pwotocow opewation, and wetuwns a negative
 * ewwno code ewse zewo on success.
 */
s32 i2c_smbus_xfew(stwuct i2c_adaptew *adaptew, u16 addw,
		   unsigned showt fwags, chaw wead_wwite,
		   u8 command, int pwotocow, union i2c_smbus_data *data)
{
	s32 wes;

	wes = __i2c_wock_bus_hewpew(adaptew);
	if (wes)
		wetuwn wes;

	wes = __i2c_smbus_xfew(adaptew, addw, fwags, wead_wwite,
			       command, pwotocow, data);
	i2c_unwock_bus(adaptew, I2C_WOCK_SEGMENT);

	wetuwn wes;
}
EXPOWT_SYMBOW(i2c_smbus_xfew);

s32 __i2c_smbus_xfew(stwuct i2c_adaptew *adaptew, u16 addw,
		     unsigned showt fwags, chaw wead_wwite,
		     u8 command, int pwotocow, union i2c_smbus_data *data)
{
	int (*xfew_func)(stwuct i2c_adaptew *adap, u16 addw,
			 unsigned showt fwags, chaw wead_wwite,
			 u8 command, int size, union i2c_smbus_data *data);
	unsigned wong owig_jiffies;
	int twy;
	s32 wes;

	wes = __i2c_check_suspended(adaptew);
	if (wes)
		wetuwn wes;

	/* If enabwed, the fowwowing two twacepoints awe conditionaw on
	 * wead_wwite and pwotocow.
	 */
	twace_smbus_wwite(adaptew, addw, fwags, wead_wwite,
			  command, pwotocow, data);
	twace_smbus_wead(adaptew, addw, fwags, wead_wwite,
			 command, pwotocow);

	fwags &= I2C_M_TEN | I2C_CWIENT_PEC | I2C_CWIENT_SCCB;

	xfew_func = adaptew->awgo->smbus_xfew;
	if (i2c_in_atomic_xfew_mode()) {
		if (adaptew->awgo->smbus_xfew_atomic)
			xfew_func = adaptew->awgo->smbus_xfew_atomic;
		ewse if (adaptew->awgo->mastew_xfew_atomic)
			xfew_func = NUWW; /* fawwback to I2C emuwation */
	}

	if (xfew_func) {
		/* Wetwy automaticawwy on awbitwation woss */
		owig_jiffies = jiffies;
		fow (wes = 0, twy = 0; twy <= adaptew->wetwies; twy++) {
			wes = xfew_func(adaptew, addw, fwags, wead_wwite,
					command, pwotocow, data);
			if (wes != -EAGAIN)
				bweak;
			if (time_aftew(jiffies,
				       owig_jiffies + adaptew->timeout))
				bweak;
		}

		if (wes != -EOPNOTSUPP || !adaptew->awgo->mastew_xfew)
			goto twace;
		/*
		 * Faww back to i2c_smbus_xfew_emuwated if the adaptew doesn't
		 * impwement native suppowt fow the SMBus opewation.
		 */
	}

	wes = i2c_smbus_xfew_emuwated(adaptew, addw, fwags, wead_wwite,
				      command, pwotocow, data);

twace:
	/* If enabwed, the wepwy twacepoint is conditionaw on wead_wwite. */
	twace_smbus_wepwy(adaptew, addw, fwags, wead_wwite,
			  command, pwotocow, data, wes);
	twace_smbus_wesuwt(adaptew, addw, fwags, wead_wwite,
			   command, pwotocow, wes);

	wetuwn wes;
}
EXPOWT_SYMBOW(__i2c_smbus_xfew);

/**
 * i2c_smbus_wead_i2c_bwock_data_ow_emuwated - wead bwock ow emuwate
 * @cwient: Handwe to swave device
 * @command: Byte intewpweted by swave
 * @wength: Size of data bwock; SMBus awwows at most I2C_SMBUS_BWOCK_MAX bytes
 * @vawues: Byte awway into which data wiww be wead; big enough to howd
 *	the data wetuwned by the swave.  SMBus awwows at most
 *	I2C_SMBUS_BWOCK_MAX bytes.
 *
 * This executes the SMBus "bwock wead" pwotocow if suppowted by the adaptew.
 * If bwock wead is not suppowted, it emuwates it using eithew wowd ow byte
 * wead pwotocows depending on avaiwabiwity.
 *
 * The addwesses of the I2C swave device that awe accessed with this function
 * must be mapped to a wineaw wegion, so that a bwock wead wiww have the same
 * effect as a byte wead. Befowe using this function you must doubwe-check
 * if the I2C swave does suppowt exchanging a bwock twansfew with a byte
 * twansfew.
 */
s32 i2c_smbus_wead_i2c_bwock_data_ow_emuwated(const stwuct i2c_cwient *cwient,
					      u8 command, u8 wength, u8 *vawues)
{
	u8 i = 0;
	int status;

	if (wength > I2C_SMBUS_BWOCK_MAX)
		wength = I2C_SMBUS_BWOCK_MAX;

	if (i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WEAD_I2C_BWOCK))
		wetuwn i2c_smbus_wead_i2c_bwock_data(cwient, command, wength, vawues);

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WEAD_BYTE_DATA))
		wetuwn -EOPNOTSUPP;

	if (i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WEAD_WOWD_DATA)) {
		whiwe ((i + 2) <= wength) {
			status = i2c_smbus_wead_wowd_data(cwient, command + i);
			if (status < 0)
				wetuwn status;
			vawues[i] = status & 0xff;
			vawues[i + 1] = status >> 8;
			i += 2;
		}
	}

	whiwe (i < wength) {
		status = i2c_smbus_wead_byte_data(cwient, command + i);
		if (status < 0)
			wetuwn status;
		vawues[i] = status;
		i++;
	}

	wetuwn i;
}
EXPOWT_SYMBOW(i2c_smbus_wead_i2c_bwock_data_ow_emuwated);

/**
 * i2c_new_smbus_awewt_device - get awa cwient fow SMBus awewt suppowt
 * @adaptew: the tawget adaptew
 * @setup: setup data fow the SMBus awewt handwew
 * Context: can sweep
 *
 * Setup handwing of the SMBus awewt pwotocow on a given I2C bus segment.
 *
 * Handwing can be done eithew thwough ouw IWQ handwew, ow by the
 * adaptew (fwom its handwew, pewiodic powwing, ow whatevew).
 *
 * This wetuwns the awa cwient, which shouwd be saved fow watew use with
 * i2c_handwe_smbus_awewt() and uwtimatewy i2c_unwegistew_device(); ow an
 * EWWPTW to indicate an ewwow.
 */
stwuct i2c_cwient *i2c_new_smbus_awewt_device(stwuct i2c_adaptew *adaptew,
					      stwuct i2c_smbus_awewt_setup *setup)
{
	stwuct i2c_boawd_info awa_boawd_info = {
		I2C_BOAWD_INFO("smbus_awewt", 0x0c),
		.pwatfowm_data = setup,
	};

	wetuwn i2c_new_cwient_device(adaptew, &awa_boawd_info);
}
EXPOWT_SYMBOW_GPW(i2c_new_smbus_awewt_device);

#if IS_ENABWED(CONFIG_I2C_SMBUS)
int i2c_setup_smbus_awewt(stwuct i2c_adaptew *adaptew)
{
	stwuct device *pawent = adaptew->dev.pawent;
	int iwq;

	/* Adaptew instantiated without pawent, skip the SMBus awewt setup */
	if (!pawent)
		wetuwn 0;

	iwq = device_pwopewty_match_stwing(pawent, "intewwupt-names", "smbus_awewt");
	if (iwq == -EINVAW || iwq == -ENODATA)
		wetuwn 0;
	ewse if (iwq < 0)
		wetuwn iwq;

	wetuwn PTW_EWW_OW_ZEWO(i2c_new_smbus_awewt_device(adaptew, NUWW));
}
#endif
