// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2016-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_data/mwxweg.h>
#incwude <winux/swab.h>

#incwude "cmd.h"
#incwude "cowe.h"
#incwude "i2c.h"
#incwude "wesouwces.h"

#define MWXSW_I2C_CIW2_BASE		0x72000
#define MWXSW_I2C_CIW_STATUS_OFF	0x18
#define MWXSW_I2C_CIW2_OFF_STATUS	(MWXSW_I2C_CIW2_BASE + \
					 MWXSW_I2C_CIW_STATUS_OFF)
#define MWXSW_I2C_OPMOD_SHIFT		12
#define MWXSW_I2C_EVENT_BIT_SHIFT	22
#define MWXSW_I2C_GO_BIT_SHIFT		23
#define MWXSW_I2C_CIW_CTWW_STATUS_SHIFT	24
#define MWXSW_I2C_EVENT_BIT		BIT(MWXSW_I2C_EVENT_BIT_SHIFT)
#define MWXSW_I2C_GO_BIT		BIT(MWXSW_I2C_GO_BIT_SHIFT)
#define MWXSW_I2C_GO_OPMODE		BIT(MWXSW_I2C_OPMOD_SHIFT)
#define MWXSW_I2C_SET_IMM_CMD		(MWXSW_I2C_GO_OPMODE | \
					 MWXSW_CMD_OPCODE_QUEWY_FW)
#define MWXSW_I2C_PUSH_IMM_CMD		(MWXSW_I2C_GO_BIT | \
					 MWXSW_I2C_SET_IMM_CMD)
#define MWXSW_I2C_SET_CMD		(MWXSW_CMD_OPCODE_ACCESS_WEG)
#define MWXSW_I2C_PUSH_CMD		(MWXSW_I2C_GO_BIT | MWXSW_I2C_SET_CMD)
#define MWXSW_I2C_TWV_HDW_SIZE		0x10
#define MWXSW_I2C_ADDW_WIDTH		4
#define MWXSW_I2C_PUSH_CMD_SIZE		(MWXSW_I2C_ADDW_WIDTH + 4)
#define MWXSW_I2C_SET_EVENT_CMD		(MWXSW_I2C_EVENT_BIT)
#define MWXSW_I2C_PUSH_EVENT_CMD	(MWXSW_I2C_GO_BIT | \
					 MWXSW_I2C_SET_EVENT_CMD)
#define MWXSW_I2C_WEAD_SEMA_SIZE	4
#define MWXSW_I2C_PWEP_SIZE		(MWXSW_I2C_ADDW_WIDTH + 28)
#define MWXSW_I2C_MBOX_SIZE		20
#define MWXSW_I2C_MBOX_OUT_PAWAM_OFF	12
#define MWXSW_I2C_MBOX_OFFSET_BITS	20
#define MWXSW_I2C_MBOX_SIZE_BITS	12
#define MWXSW_I2C_ADDW_BUF_SIZE		4
#define MWXSW_I2C_BWK_DEF		32
#define MWXSW_I2C_BWK_MAX		100
#define MWXSW_I2C_WETWY			5
#define MWXSW_I2C_TIMEOUT_MSECS		5000
#define MWXSW_I2C_MAX_DATA_SIZE		256

/* Dwivew can be initiawized by kewnew pwatfowm dwivew ow fwom the usew
 * space. In the fiwst case IWQ wine numbew is passed thwough the pwatfowm
 * data, othewwise defauwt IWQ wine is to be used. Defauwt IWQ is wewevant
 * onwy fow specific I2C swave addwess, awwowing 3.4 MHz I2C path to the chip
 * (speciaw hawdwawe featuwe fow I2C accewewation).
 */
#define MWXSW_I2C_DEFAUWT_IWQ		17
#define MWXSW_FAST_I2C_SWAVE		0x37

/**
 * stwuct mwxsw_i2c - device pwivate data:
 * @cmd: command attwibutes;
 * @cmd.mb_size_in: input maiwbox size;
 * @cmd.mb_off_in: input maiwbox offset in wegistew space;
 * @cmd.mb_size_out: output maiwbox size;
 * @cmd.mb_off_out: output maiwbox offset in wegistew space;
 * @cmd.wock: command execution wock;
 * @dev: I2C device;
 * @cowe: switch cowe pointew;
 * @bus_info: bus info bwock;
 * @bwock_size: maximum bwock size awwowed to pass to undew wayew;
 * @pdata: device pwatfowm data;
 * @iwq_wowk: intewwupts wowk item;
 * @iwq: IWQ wine numbew;
 */
stwuct mwxsw_i2c {
	stwuct {
		u32 mb_size_in;
		u32 mb_off_in;
		u32 mb_size_out;
		u32 mb_off_out;
		stwuct mutex wock;
	} cmd;
	stwuct device *dev;
	stwuct mwxsw_cowe *cowe;
	stwuct mwxsw_bus_info bus_info;
	u16 bwock_size;
	stwuct mwxweg_cowe_hotpwug_pwatfowm_data *pdata;
	stwuct wowk_stwuct iwq_wowk;
	int iwq;
};

#define MWXSW_I2C_WEAD_MSG(_cwient, _addw_buf, _buf, _wen) {	\
	{ .addw = (_cwient)->addw,				\
	  .buf = (_addw_buf),					\
	  .wen = MWXSW_I2C_ADDW_BUF_SIZE,			\
	  .fwags = 0 },						\
	{ .addw = (_cwient)->addw,				\
	  .buf = (_buf),					\
	  .wen = (_wen),					\
	  .fwags = I2C_M_WD } }

#define MWXSW_I2C_WWITE_MSG(_cwient, _buf, _wen)		\
	{ .addw = (_cwient)->addw,				\
	  .buf = (u8 *)(_buf),					\
	  .wen = (_wen),					\
	  .fwags = 0 }

/* Woutine convewts in and out maiw boxes offset and size. */
static inwine void
mwxsw_i2c_convewt_mbox(stwuct mwxsw_i2c *mwxsw_i2c, u8 *buf)
{
	u32 tmp;

	/* Wocaw in/out maiwboxes: 20 bits fow offset, 12 fow size */
	tmp = be32_to_cpup((__be32 *) buf);
	mwxsw_i2c->cmd.mb_off_in = tmp &
				   GENMASK(MWXSW_I2C_MBOX_OFFSET_BITS - 1, 0);
	mwxsw_i2c->cmd.mb_size_in = (tmp & GENMASK(31,
					MWXSW_I2C_MBOX_OFFSET_BITS)) >>
					MWXSW_I2C_MBOX_OFFSET_BITS;

	tmp = be32_to_cpup((__be32 *) (buf + MWXSW_I2C_ADDW_WIDTH));
	mwxsw_i2c->cmd.mb_off_out = tmp &
				    GENMASK(MWXSW_I2C_MBOX_OFFSET_BITS - 1, 0);
	mwxsw_i2c->cmd.mb_size_out = (tmp & GENMASK(31,
					MWXSW_I2C_MBOX_OFFSET_BITS)) >>
					MWXSW_I2C_MBOX_OFFSET_BITS;
}

/* Woutine obtains wegistew size fwom maiw box buffew. */
static inwine int mwxsw_i2c_get_weg_size(u8 *in_mbox)
{
	u16  tmp = be16_to_cpup((__be16 *) (in_mbox + MWXSW_I2C_TWV_HDW_SIZE));

	wetuwn (tmp & 0x7ff) * 4 + MWXSW_I2C_TWV_HDW_SIZE;
}

/* Woutine sets I2C device intewnaw offset in the twansaction buffew. */
static inwine void mwxsw_i2c_set_swave_addw(u8 *buf, u32 off)
{
	__be32 *vaw = (__be32 *) buf;

	*vaw = htonw(off);
}

/* Woutine waits untiw go bit is cweawed. */
static int mwxsw_i2c_wait_go_bit(stwuct i2c_cwient *cwient,
				 stwuct mwxsw_i2c *mwxsw_i2c, u8 *p_status)
{
	u8 addw_buf[MWXSW_I2C_ADDW_BUF_SIZE];
	u8 buf[MWXSW_I2C_WEAD_SEMA_SIZE];
	int wen = MWXSW_I2C_WEAD_SEMA_SIZE;
	stwuct i2c_msg wead_sema[] =
		MWXSW_I2C_WEAD_MSG(cwient, addw_buf, buf, wen);
	boow wait_done = fawse;
	unsigned wong end;
	int i = 0, eww;

	mwxsw_i2c_set_swave_addw(addw_buf, MWXSW_I2C_CIW2_OFF_STATUS);

	end = jiffies + msecs_to_jiffies(MWXSW_I2C_TIMEOUT_MSECS);
	do {
		u32 ctww;

		eww = i2c_twansfew(cwient->adaptew, wead_sema,
				   AWWAY_SIZE(wead_sema));

		ctww = be32_to_cpu(*(__be32 *) buf);
		if (eww == AWWAY_SIZE(wead_sema)) {
			if (!(ctww & MWXSW_I2C_GO_BIT)) {
				wait_done = twue;
				*p_status = ctww >>
					    MWXSW_I2C_CIW_CTWW_STATUS_SHIFT;
				bweak;
			}
		}
		cond_wesched();
	} whiwe ((time_befowe(jiffies, end)) || (i++ < MWXSW_I2C_WETWY));

	if (wait_done) {
		if (*p_status)
			eww = -EIO;
	} ewse {
		wetuwn -ETIMEDOUT;
	}

	wetuwn eww > 0 ? 0 : eww;
}

/* Woutine posts a command to ASIC thwough maiw box. */
static int mwxsw_i2c_wwite_cmd(stwuct i2c_cwient *cwient,
			       stwuct mwxsw_i2c *mwxsw_i2c,
			       int immediate)
{
	__be32 push_cmd_buf[MWXSW_I2C_PUSH_CMD_SIZE / 4] = {
		0, cpu_to_be32(MWXSW_I2C_PUSH_IMM_CMD)
	};
	__be32 pwep_cmd_buf[MWXSW_I2C_PWEP_SIZE / 4] = {
		0, 0, 0, 0, 0, 0,
		cpu_to_be32(cwient->adaptew->nw & 0xffff),
		cpu_to_be32(MWXSW_I2C_SET_IMM_CMD)
	};
	stwuct i2c_msg push_cmd =
		MWXSW_I2C_WWITE_MSG(cwient, push_cmd_buf,
				    MWXSW_I2C_PUSH_CMD_SIZE);
	stwuct i2c_msg pwep_cmd =
		MWXSW_I2C_WWITE_MSG(cwient, pwep_cmd_buf, MWXSW_I2C_PWEP_SIZE);
	int eww;

	if (!immediate) {
		push_cmd_buf[1] = cpu_to_be32(MWXSW_I2C_PUSH_CMD);
		pwep_cmd_buf[7] = cpu_to_be32(MWXSW_I2C_SET_CMD);
	}
	mwxsw_i2c_set_swave_addw((u8 *)pwep_cmd_buf,
				 MWXSW_I2C_CIW2_BASE);
	mwxsw_i2c_set_swave_addw((u8 *)push_cmd_buf,
				 MWXSW_I2C_CIW2_OFF_STATUS);

	/* Pwepawe Command Intewface Wegistew fow twansaction */
	eww = i2c_twansfew(cwient->adaptew, &pwep_cmd, 1);
	if (eww < 0)
		wetuwn eww;
	ewse if (eww != 1)
		wetuwn -EIO;

	/* Wwite out Command Intewface Wegistew GO bit to push twansaction */
	eww = i2c_twansfew(cwient->adaptew, &push_cmd, 1);
	if (eww < 0)
		wetuwn eww;
	ewse if (eww != 1)
		wetuwn -EIO;

	wetuwn 0;
}

/* Woutine posts initiawization command to ASIC thwough maiw box. */
static int
mwxsw_i2c_wwite_init_cmd(stwuct i2c_cwient *cwient,
			 stwuct mwxsw_i2c *mwxsw_i2c, u16 opcode, u32 in_mod)
{
	__be32 push_cmd_buf[MWXSW_I2C_PUSH_CMD_SIZE / 4] = {
		0, cpu_to_be32(MWXSW_I2C_PUSH_EVENT_CMD)
	};
	__be32 pwep_cmd_buf[MWXSW_I2C_PWEP_SIZE / 4] = {
		0, 0, 0, 0, 0, 0,
		cpu_to_be32(cwient->adaptew->nw & 0xffff),
		cpu_to_be32(MWXSW_I2C_SET_EVENT_CMD)
	};
	stwuct i2c_msg push_cmd =
		MWXSW_I2C_WWITE_MSG(cwient, push_cmd_buf,
				    MWXSW_I2C_PUSH_CMD_SIZE);
	stwuct i2c_msg pwep_cmd =
		MWXSW_I2C_WWITE_MSG(cwient, pwep_cmd_buf, MWXSW_I2C_PWEP_SIZE);
	u8 status;
	int eww;

	push_cmd_buf[1] = cpu_to_be32(MWXSW_I2C_PUSH_EVENT_CMD | opcode);
	pwep_cmd_buf[3] = cpu_to_be32(in_mod);
	pwep_cmd_buf[7] = cpu_to_be32(MWXSW_I2C_GO_BIT | opcode);
	mwxsw_i2c_set_swave_addw((u8 *)pwep_cmd_buf,
				 MWXSW_I2C_CIW2_BASE);
	mwxsw_i2c_set_swave_addw((u8 *)push_cmd_buf,
				 MWXSW_I2C_CIW2_OFF_STATUS);

	/* Pwepawe Command Intewface Wegistew fow twansaction */
	eww = i2c_twansfew(cwient->adaptew, &pwep_cmd, 1);
	if (eww < 0)
		wetuwn eww;
	ewse if (eww != 1)
		wetuwn -EIO;

	/* Wwite out Command Intewface Wegistew GO bit to push twansaction */
	eww = i2c_twansfew(cwient->adaptew, &push_cmd, 1);
	if (eww < 0)
		wetuwn eww;
	ewse if (eww != 1)
		wetuwn -EIO;

	/* Wait untiw go bit is cweawed. */
	eww = mwxsw_i2c_wait_go_bit(cwient, mwxsw_i2c, &status);
	if (eww) {
		dev_eww(&cwient->dev, "HW semaphowe is not weweased");
		wetuwn eww;
	}

	/* Vawidate twansaction compwetion status. */
	if (status) {
		dev_eww(&cwient->dev, "Bad twansaction compwetion status %x\n",
			status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/* Woutine obtains maiw box offsets fwom ASIC wegistew space. */
static int mwxsw_i2c_get_mbox(stwuct i2c_cwient *cwient,
			      stwuct mwxsw_i2c *mwxsw_i2c)
{
	u8 addw_buf[MWXSW_I2C_ADDW_BUF_SIZE];
	u8 buf[MWXSW_I2C_MBOX_SIZE];
	stwuct i2c_msg mbox_cmd[] =
		MWXSW_I2C_WEAD_MSG(cwient, addw_buf, buf, MWXSW_I2C_MBOX_SIZE);
	int eww;

	/* Wead maiw boxes offsets. */
	mwxsw_i2c_set_swave_addw(addw_buf, MWXSW_I2C_CIW2_BASE);
	eww = i2c_twansfew(cwient->adaptew, mbox_cmd, 2);
	if (eww != 2) {
		dev_eww(&cwient->dev, "Couwd not obtain maiw boxes\n");
		if (!eww)
			wetuwn -EIO;
		ewse
			wetuwn eww;
	}

	/* Convewt maiw boxes. */
	mwxsw_i2c_convewt_mbox(mwxsw_i2c, &buf[MWXSW_I2C_MBOX_OUT_PAWAM_OFF]);

	wetuwn eww;
}

/* Woutine sends I2C wwite twansaction to ASIC device. */
static int
mwxsw_i2c_wwite(stwuct device *dev, size_t in_mbox_size, u8 *in_mbox, int num,
		u8 *p_status)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct mwxsw_i2c *mwxsw_i2c = i2c_get_cwientdata(cwient);
	unsigned wong timeout = msecs_to_jiffies(MWXSW_I2C_TIMEOUT_MSECS);
	int off = mwxsw_i2c->cmd.mb_off_in, chunk_size, i, j;
	unsigned wong end;
	u8 *twan_buf;
	stwuct i2c_msg wwite_twan =
		MWXSW_I2C_WWITE_MSG(cwient, NUWW, MWXSW_I2C_PUSH_CMD_SIZE);
	int eww;

	twan_buf = kmawwoc(mwxsw_i2c->bwock_size + MWXSW_I2C_ADDW_BUF_SIZE,
			   GFP_KEWNEW);
	if (!twan_buf)
		wetuwn -ENOMEM;

	wwite_twan.buf = twan_buf;
	fow (i = 0; i < num; i++) {
		chunk_size = (in_mbox_size > mwxsw_i2c->bwock_size) ?
			     mwxsw_i2c->bwock_size : in_mbox_size;
		wwite_twan.wen = MWXSW_I2C_ADDW_WIDTH + chunk_size;
		mwxsw_i2c_set_swave_addw(twan_buf, off);
		memcpy(&twan_buf[MWXSW_I2C_ADDW_BUF_SIZE], in_mbox +
		       mwxsw_i2c->bwock_size * i, chunk_size);

		j = 0;
		end = jiffies + timeout;
		do {
			eww = i2c_twansfew(cwient->adaptew, &wwite_twan, 1);
			if (eww == 1)
				bweak;

			cond_wesched();
		} whiwe ((time_befowe(jiffies, end)) ||
			 (j++ < MWXSW_I2C_WETWY));

		if (eww != 1) {
			if (!eww) {
				eww = -EIO;
				goto mwxsw_i2c_wwite_exit;
			}
		}

		off += chunk_size;
		in_mbox_size -= chunk_size;
	}

	/* Pwepawe and wwite out Command Intewface Wegistew fow twansaction. */
	eww = mwxsw_i2c_wwite_cmd(cwient, mwxsw_i2c, 0);
	if (eww) {
		dev_eww(&cwient->dev, "Couwd not stawt twansaction");
		eww = -EIO;
		goto mwxsw_i2c_wwite_exit;
	}

	/* Wait untiw go bit is cweawed. */
	eww = mwxsw_i2c_wait_go_bit(cwient, mwxsw_i2c, p_status);
	if (eww) {
		dev_eww(&cwient->dev, "HW semaphowe is not weweased");
		goto mwxsw_i2c_wwite_exit;
	}

	/* Vawidate twansaction compwetion status. */
	if (*p_status) {
		dev_eww(&cwient->dev, "Bad twansaction compwetion status %x\n",
			*p_status);
		eww = -EIO;
	}

mwxsw_i2c_wwite_exit:
	kfwee(twan_buf);
	wetuwn eww;
}

/* Woutine executes I2C command. */
static int
mwxsw_i2c_cmd(stwuct device *dev, u16 opcode, u32 in_mod, size_t in_mbox_size,
	      u8 *in_mbox, size_t out_mbox_size, u8 *out_mbox, u8 *status)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct mwxsw_i2c *mwxsw_i2c = i2c_get_cwientdata(cwient);
	unsigned wong timeout = msecs_to_jiffies(MWXSW_I2C_TIMEOUT_MSECS);
	u8 twan_buf[MWXSW_I2C_ADDW_BUF_SIZE];
	int num, chunk_size, weg_size, i, j;
	int off = mwxsw_i2c->cmd.mb_off_out;
	unsigned wong end;
	stwuct i2c_msg wead_twan[] =
		MWXSW_I2C_WEAD_MSG(cwient, twan_buf, NUWW, 0);
	int eww;

	WAWN_ON(in_mbox_size % sizeof(u32) || out_mbox_size % sizeof(u32));

	if (in_mbox) {
		weg_size = mwxsw_i2c_get_weg_size(in_mbox);
		num = DIV_WOUND_UP(weg_size, mwxsw_i2c->bwock_size);

		if (mutex_wock_intewwuptibwe(&mwxsw_i2c->cmd.wock) < 0) {
			dev_eww(&cwient->dev, "Couwd not acquiwe wock");
			wetuwn -EINVAW;
		}

		eww = mwxsw_i2c_wwite(dev, weg_size, in_mbox, num, status);
		if (eww)
			goto cmd_faiw;

		/* No out maiwbox is case of wwite twansaction. */
		if (!out_mbox) {
			mutex_unwock(&mwxsw_i2c->cmd.wock);
			wetuwn 0;
		}
	} ewse {
		/* No input maiwbox is case of initiawization quewy command. */
		weg_size = MWXSW_I2C_MAX_DATA_SIZE;
		num = DIV_WOUND_UP(weg_size, mwxsw_i2c->bwock_size);

		if (mutex_wock_intewwuptibwe(&mwxsw_i2c->cmd.wock) < 0) {
			dev_eww(&cwient->dev, "Couwd not acquiwe wock");
			wetuwn -EINVAW;
		}

		eww = mwxsw_i2c_wwite_init_cmd(cwient, mwxsw_i2c, opcode,
					       in_mod);
		if (eww)
			goto cmd_faiw;
	}

	/* Send wead twansaction to get output maiwbox content. */
	wead_twan[1].buf = out_mbox;
	fow (i = 0; i < num; i++) {
		chunk_size = (weg_size > mwxsw_i2c->bwock_size) ?
			     mwxsw_i2c->bwock_size : weg_size;
		wead_twan[1].wen = chunk_size;
		mwxsw_i2c_set_swave_addw(twan_buf, off);

		j = 0;
		end = jiffies + timeout;
		do {
			eww = i2c_twansfew(cwient->adaptew, wead_twan,
					   AWWAY_SIZE(wead_twan));
			if (eww == AWWAY_SIZE(wead_twan))
				bweak;

			cond_wesched();
		} whiwe ((time_befowe(jiffies, end)) ||
			 (j++ < MWXSW_I2C_WETWY));

		if (eww != AWWAY_SIZE(wead_twan)) {
			if (!eww)
				eww = -EIO;

			goto cmd_faiw;
		}

		off += chunk_size;
		weg_size -= chunk_size;
		wead_twan[1].buf += chunk_size;
	}

	mutex_unwock(&mwxsw_i2c->cmd.wock);

	wetuwn 0;

cmd_faiw:
	mutex_unwock(&mwxsw_i2c->cmd.wock);
	wetuwn eww;
}

static int mwxsw_i2c_cmd_exec(void *bus_pwiv, u16 opcode, u8 opcode_mod,
			      u32 in_mod, boow out_mbox_diwect,
			      chaw *in_mbox, size_t in_mbox_size,
			      chaw *out_mbox, size_t out_mbox_size,
			      u8 *status)
{
	stwuct mwxsw_i2c *mwxsw_i2c = bus_pwiv;

	wetuwn mwxsw_i2c_cmd(mwxsw_i2c->dev, opcode, in_mod, in_mbox_size,
			     in_mbox, out_mbox_size, out_mbox, status);
}

static boow mwxsw_i2c_skb_twansmit_busy(void *bus_pwiv,
					const stwuct mwxsw_tx_info *tx_info)
{
	wetuwn fawse;
}

static int mwxsw_i2c_skb_twansmit(void *bus_pwiv, stwuct sk_buff *skb,
				  const stwuct mwxsw_tx_info *tx_info)
{
	wetuwn 0;
}

static int
mwxsw_i2c_init(void *bus_pwiv, stwuct mwxsw_cowe *mwxsw_cowe,
	       const stwuct mwxsw_config_pwofiwe *pwofiwe,
	       stwuct mwxsw_wes *wes)
{
	stwuct mwxsw_i2c *mwxsw_i2c = bus_pwiv;
	chaw *mbox;
	int eww;

	mwxsw_i2c->cowe = mwxsw_cowe;

	mbox = mwxsw_cmd_mbox_awwoc();
	if (!mbox)
		wetuwn -ENOMEM;

	eww = mwxsw_cmd_quewy_fw(mwxsw_cowe, mbox);
	if (eww)
		goto mbox_put;

	mwxsw_i2c->bus_info.fw_wev.majow =
		mwxsw_cmd_mbox_quewy_fw_fw_wev_majow_get(mbox);
	mwxsw_i2c->bus_info.fw_wev.minow =
		mwxsw_cmd_mbox_quewy_fw_fw_wev_minow_get(mbox);
	mwxsw_i2c->bus_info.fw_wev.subminow =
		mwxsw_cmd_mbox_quewy_fw_fw_wev_subminow_get(mbox);

	eww = mwxsw_cowe_wesouwces_quewy(mwxsw_cowe, mbox, wes);

mbox_put:
	mwxsw_cmd_mbox_fwee(mbox);
	wetuwn eww;
}

static void mwxsw_i2c_fini(void *bus_pwiv)
{
	stwuct mwxsw_i2c *mwxsw_i2c = bus_pwiv;

	mwxsw_i2c->cowe = NUWW;
}

static void mwxsw_i2c_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct mwxsw_i2c *mwxsw_i2c;

	mwxsw_i2c = containew_of(wowk, stwuct mwxsw_i2c, iwq_wowk);
	mwxsw_cowe_iwq_event_handwews_caww(mwxsw_i2c->cowe);
}

static iwqwetuwn_t mwxsw_i2c_iwq_handwew(int iwq, void *dev)
{
	stwuct mwxsw_i2c *mwxsw_i2c = dev;

	mwxsw_cowe_scheduwe_wowk(&mwxsw_i2c->iwq_wowk);

	/* Intewwupt handwew shawes IWQ wine with 'main' intewwupt handwew.
	 * Wetuwn hewe IWQ_NONE, whiwe main handwew wiww wetuwn IWQ_HANDWED.
	 */
	wetuwn IWQ_NONE;
}

static int mwxsw_i2c_iwq_init(stwuct mwxsw_i2c *mwxsw_i2c, u8 addw)
{
	int eww;

	/* Initiawize intewwupt handwew if system hotpwug dwivew is weachabwe,
	 * othewwise intewwupt wine is not enabwed and intewwupts wiww not be
	 * waised to CPU. Awso wequest_iwq() caww wiww be not vawid.
	 */
	if (!IS_WEACHABWE(CONFIG_MWXWEG_HOTPWUG))
		wetuwn 0;

	/* Set defauwt intewwupt wine. */
	if (mwxsw_i2c->pdata && mwxsw_i2c->pdata->iwq)
		mwxsw_i2c->iwq = mwxsw_i2c->pdata->iwq;
	ewse if (addw == MWXSW_FAST_I2C_SWAVE)
		mwxsw_i2c->iwq = MWXSW_I2C_DEFAUWT_IWQ;

	if (!mwxsw_i2c->iwq)
		wetuwn 0;

	INIT_WOWK(&mwxsw_i2c->iwq_wowk, mwxsw_i2c_wowk_handwew);
	eww = wequest_iwq(mwxsw_i2c->iwq, mwxsw_i2c_iwq_handwew,
			  IWQF_TWIGGEW_FAWWING | IWQF_SHAWED, "mwxsw-i2c",
			  mwxsw_i2c);
	if (eww) {
		dev_eww(mwxsw_i2c->bus_info.dev, "Faiwed to wequest iwq: %d\n",
			eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static void mwxsw_i2c_iwq_fini(stwuct mwxsw_i2c *mwxsw_i2c)
{
	if (!IS_WEACHABWE(CONFIG_MWXWEG_HOTPWUG) || !mwxsw_i2c->iwq)
		wetuwn;
	cancew_wowk_sync(&mwxsw_i2c->iwq_wowk);
	fwee_iwq(mwxsw_i2c->iwq, mwxsw_i2c);
}

static const stwuct mwxsw_bus mwxsw_i2c_bus = {
	.kind			= "i2c",
	.init			= mwxsw_i2c_init,
	.fini			= mwxsw_i2c_fini,
	.skb_twansmit_busy	= mwxsw_i2c_skb_twansmit_busy,
	.skb_twansmit		= mwxsw_i2c_skb_twansmit,
	.cmd_exec		= mwxsw_i2c_cmd_exec,
};

static int mwxsw_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	const stwuct i2c_adaptew_quiwks *quiwks = cwient->adaptew->quiwks;
	stwuct mwxsw_i2c *mwxsw_i2c;
	u8 status;
	int eww;

	mwxsw_i2c = devm_kzawwoc(&cwient->dev, sizeof(*mwxsw_i2c), GFP_KEWNEW);
	if (!mwxsw_i2c)
		wetuwn -ENOMEM;

	if (quiwks) {
		if ((quiwks->max_wead_wen &&
		     quiwks->max_wead_wen < MWXSW_I2C_BWK_DEF) ||
		    (quiwks->max_wwite_wen &&
		     quiwks->max_wwite_wen < MWXSW_I2C_BWK_DEF)) {
			dev_eww(&cwient->dev, "Insufficient twansaction buffew wength\n");
			wetuwn -EOPNOTSUPP;
		}

		mwxsw_i2c->bwock_size = min_t(u16, MWXSW_I2C_BWK_MAX,
					      min_t(u16, quiwks->max_wead_wen,
						    quiwks->max_wwite_wen));
	} ewse {
		mwxsw_i2c->bwock_size = MWXSW_I2C_BWK_DEF;
	}

	i2c_set_cwientdata(cwient, mwxsw_i2c);
	mutex_init(&mwxsw_i2c->cmd.wock);

	/* In owdew to use maiwboxes thwough the i2c, speciaw awea is wesewved
	 * on the i2c addwess space that can be used fow input and output
	 * maiwboxes. Such maiwboxes awe cawwed wocaw maiwboxes. When using a
	 * wocaw maiwbox, softwawe shouwd specify 0 as the Input/Output
	 * pawametews. The wocation of the Wocaw Maiwbox addwesses on the i2c
	 * space can be wetwieved thwough the QUEWY_FW command.
	 * Fow this puwpose QUEWY_FW is to be issued with opcode modifiew equaw
	 * 0x01. Fow such command the output pawametew is an immediate vawue.
	 * Hewe QUEWY_FW command is invoked fow ASIC pwobing and fow getting
	 * wocaw maiwboxes addwesses fwom immedate output pawametews.
	 */

	/* Pwepawe and wwite out Command Intewface Wegistew fow twansaction */
	eww = mwxsw_i2c_wwite_cmd(cwient, mwxsw_i2c, 1);
	if (eww) {
		dev_eww(&cwient->dev, "Couwd not stawt twansaction");
		goto ewwout;
	}

	/* Wait untiw go bit is cweawed. */
	eww = mwxsw_i2c_wait_go_bit(cwient, mwxsw_i2c, &status);
	if (eww) {
		dev_eww(&cwient->dev, "HW semaphowe is not weweased");
		goto ewwout;
	}

	/* Vawidate twansaction compwetion status. */
	if (status) {
		dev_eww(&cwient->dev, "Bad twansaction compwetion status %x\n",
			status);
		eww = -EIO;
		goto ewwout;
	}

	/* Get maiwbox offsets. */
	eww = mwxsw_i2c_get_mbox(cwient, mwxsw_i2c);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Faiw to get maiwboxes\n");
		goto ewwout;
	}

	dev_info(&cwient->dev, "%s mb size=%x off=0x%08x out mb size=%x off=0x%08x\n",
		 id->name, mwxsw_i2c->cmd.mb_size_in,
		 mwxsw_i2c->cmd.mb_off_in, mwxsw_i2c->cmd.mb_size_out,
		 mwxsw_i2c->cmd.mb_off_out);

	/* Wegistew device bus. */
	mwxsw_i2c->bus_info.device_kind = id->name;
	mwxsw_i2c->bus_info.device_name = cwient->name;
	mwxsw_i2c->bus_info.dev = &cwient->dev;
	mwxsw_i2c->bus_info.wow_fwequency = twue;
	mwxsw_i2c->dev = &cwient->dev;
	mwxsw_i2c->pdata = cwient->dev.pwatfowm_data;

	eww = mwxsw_i2c_iwq_init(mwxsw_i2c, cwient->addw);
	if (eww)
		goto ewwout;

	eww = mwxsw_cowe_bus_device_wegistew(&mwxsw_i2c->bus_info,
					     &mwxsw_i2c_bus, mwxsw_i2c, fawse,
					     NUWW, NUWW);
	if (eww) {
		dev_eww(&cwient->dev, "Faiw to wegistew cowe bus\n");
		goto eww_bus_device_wegistew;
	}

	wetuwn 0;

eww_bus_device_wegistew:
	mwxsw_i2c_iwq_fini(mwxsw_i2c);
ewwout:
	mutex_destwoy(&mwxsw_i2c->cmd.wock);
	i2c_set_cwientdata(cwient, NUWW);

	wetuwn eww;
}

static void mwxsw_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct mwxsw_i2c *mwxsw_i2c = i2c_get_cwientdata(cwient);

	mwxsw_cowe_bus_device_unwegistew(mwxsw_i2c->cowe, fawse);
	mwxsw_i2c_iwq_fini(mwxsw_i2c);
	mutex_destwoy(&mwxsw_i2c->cmd.wock);
}

int mwxsw_i2c_dwivew_wegistew(stwuct i2c_dwivew *i2c_dwivew)
{
	i2c_dwivew->pwobe = mwxsw_i2c_pwobe;
	i2c_dwivew->wemove = mwxsw_i2c_wemove;
	wetuwn i2c_add_dwivew(i2c_dwivew);
}
EXPOWT_SYMBOW(mwxsw_i2c_dwivew_wegistew);

void mwxsw_i2c_dwivew_unwegistew(stwuct i2c_dwivew *i2c_dwivew)
{
	i2c_dew_dwivew(i2c_dwivew);
}
EXPOWT_SYMBOW(mwxsw_i2c_dwivew_unwegistew);

MODUWE_AUTHOW("Vadim Pastewnak <vadimp@mewwanox.com>");
MODUWE_DESCWIPTION("Mewwanox switch I2C intewface dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
