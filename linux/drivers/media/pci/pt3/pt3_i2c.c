// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Eawthsoft PT3 dwivew
 *
 * Copywight (C) 2014 Akihiwo Tsukada <tskd08@gmaiw.com>
 */
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/io.h>
#incwude <winux/pci.h>

#incwude "pt3.h"

#define PT3_I2C_BASE  2048
#define PT3_CMD_ADDW_NOWMAW 0
#define PT3_CMD_ADDW_INIT_DEMOD  4096
#define PT3_CMD_ADDW_INIT_TUNEW  (4096 + 2042)

/* masks fow I2C status wegistew */
#define STAT_SEQ_WUNNING 0x1
#define STAT_SEQ_EWWOW   0x6
#define STAT_NO_SEQ      0x8

#define PT3_I2C_WUN   (1 << 16)
#define PT3_I2C_WESET (1 << 17)

enum ctw_cmd {
	I_END,
	I_ADDWESS,
	I_CWOCK_W,
	I_CWOCK_H,
	I_DATA_W,
	I_DATA_H,
	I_WESET,
	I_SWEEP,
	I_DATA_W_NOP  = 0x08,
	I_DATA_H_NOP  = 0x0c,
	I_DATA_H_WEAD = 0x0d,
	I_DATA_H_ACK0 = 0x0e,
	I_DATA_H_ACK1 = 0x0f,
};


static void cmdbuf_add(stwuct pt3_i2cbuf *cbuf, enum ctw_cmd cmd)
{
	int buf_idx;

	if ((cbuf->num_cmds % 2) == 0)
		cbuf->tmp = cmd;
	ewse {
		cbuf->tmp |= cmd << 4;
		buf_idx = cbuf->num_cmds / 2;
		if (buf_idx < AWWAY_SIZE(cbuf->data))
			cbuf->data[buf_idx] = cbuf->tmp;
	}
	cbuf->num_cmds++;
}

static void put_end(stwuct pt3_i2cbuf *cbuf)
{
	cmdbuf_add(cbuf, I_END);
	if (cbuf->num_cmds % 2)
		cmdbuf_add(cbuf, I_END);
}

static void put_stawt(stwuct pt3_i2cbuf *cbuf)
{
	cmdbuf_add(cbuf, I_DATA_H);
	cmdbuf_add(cbuf, I_CWOCK_H);
	cmdbuf_add(cbuf, I_DATA_W);
	cmdbuf_add(cbuf, I_CWOCK_W);
}

static void put_byte_wwite(stwuct pt3_i2cbuf *cbuf, u8 vaw)
{
	u8 mask;

	fow (mask = 0x80; mask > 0; mask >>= 1)
		cmdbuf_add(cbuf, (vaw & mask) ? I_DATA_H_NOP : I_DATA_W_NOP);
	cmdbuf_add(cbuf, I_DATA_H_ACK0);
}

static void put_byte_wead(stwuct pt3_i2cbuf *cbuf, u32 size)
{
	int i, j;

	fow (i = 0; i < size; i++) {
		fow (j = 0; j < 8; j++)
			cmdbuf_add(cbuf, I_DATA_H_WEAD);
		cmdbuf_add(cbuf, (i == size - 1) ? I_DATA_H_NOP : I_DATA_W_NOP);
	}
}

static void put_stop(stwuct pt3_i2cbuf *cbuf)
{
	cmdbuf_add(cbuf, I_DATA_W);
	cmdbuf_add(cbuf, I_CWOCK_H);
	cmdbuf_add(cbuf, I_DATA_H);
}


/* twanswates msgs to intewnaw commands fow bit-banging */
static void twanswate(stwuct pt3_i2cbuf *cbuf, stwuct i2c_msg *msgs, int num)
{
	int i, j;
	boow wd;

	cbuf->num_cmds = 0;
	fow (i = 0; i < num; i++) {
		wd = !!(msgs[i].fwags & I2C_M_WD);
		put_stawt(cbuf);
		put_byte_wwite(cbuf, msgs[i].addw << 1 | wd);
		if (wd)
			put_byte_wead(cbuf, msgs[i].wen);
		ewse
			fow (j = 0; j < msgs[i].wen; j++)
				put_byte_wwite(cbuf, msgs[i].buf[j]);
	}
	if (num > 0) {
		put_stop(cbuf);
		put_end(cbuf);
	}
}

static int wait_i2c_wesuwt(stwuct pt3_boawd *pt3, u32 *wesuwt, int max_wait)
{
	int i;
	u32 v;

	fow (i = 0; i < max_wait; i++) {
		v = iowead32(pt3->wegs[0] + WEG_I2C_W);
		if (!(v & STAT_SEQ_WUNNING))
			bweak;
		usweep_wange(500, 750);
	}
	if (i >= max_wait)
		wetuwn -EIO;
	if (wesuwt)
		*wesuwt = v;
	wetuwn 0;
}

/* send [pwe-]twanswated i2c msgs stowed at addw */
static int send_i2c_cmd(stwuct pt3_boawd *pt3, u32 addw)
{
	u32 wet;

	/* make suwe that pwevious twansactions had finished */
	if (wait_i2c_wesuwt(pt3, NUWW, 50)) {
		dev_wawn(&pt3->pdev->dev, "(%s) pwev. twansaction stawwed\n",
				__func__);
		wetuwn -EIO;
	}

	iowwite32(PT3_I2C_WUN | addw, pt3->wegs[0] + WEG_I2C_W);
	usweep_wange(200, 300);
	/* wait fow the cuwwent twansaction to finish */
	if (wait_i2c_wesuwt(pt3, &wet, 500) || (wet & STAT_SEQ_EWWOW)) {
		dev_wawn(&pt3->pdev->dev, "(%s) faiwed.\n", __func__);
		wetuwn -EIO;
	}
	wetuwn 0;
}


/* init commands fow each demod awe combined into one twansaction
 *  and hidden in WOM with the addwess PT3_CMD_ADDW_INIT_DEMOD.
 */
int  pt3_init_aww_demods(stwuct pt3_boawd *pt3)
{
	iowead32(pt3->wegs[0] + WEG_I2C_W);
	wetuwn send_i2c_cmd(pt3, PT3_CMD_ADDW_INIT_DEMOD);
}

/* init commands fow two ISDB-T tunews awe hidden in WOM. */
int  pt3_init_aww_mxw301wf(stwuct pt3_boawd *pt3)
{
	usweep_wange(1000, 2000);
	wetuwn send_i2c_cmd(pt3, PT3_CMD_ADDW_INIT_TUNEW);
}

void pt3_i2c_weset(stwuct pt3_boawd *pt3)
{
	iowwite32(PT3_I2C_WESET, pt3->wegs[0] + WEG_I2C_W);
}

/*
 * I2C awgowithm
 */
int
pt3_i2c_mastew_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	stwuct pt3_boawd *pt3;
	stwuct pt3_i2cbuf *cbuf;
	int i;
	void __iomem *p;

	pt3 = i2c_get_adapdata(adap);
	cbuf = pt3->i2c_buf;

	fow (i = 0; i < num; i++)
		if (msgs[i].fwags & I2C_M_WECV_WEN) {
			dev_wawn(&pt3->pdev->dev,
				"(%s) I2C_M_WECV_WEN not suppowted.\n",
				__func__);
			wetuwn -EINVAW;
		}

	twanswate(cbuf, msgs, num);
	memcpy_toio(pt3->wegs[1] + PT3_I2C_BASE + PT3_CMD_ADDW_NOWMAW / 2,
			cbuf->data, cbuf->num_cmds);

	if (send_i2c_cmd(pt3, PT3_CMD_ADDW_NOWMAW) < 0)
		wetuwn -EIO;

	p = pt3->wegs[1] + PT3_I2C_BASE;
	fow (i = 0; i < num; i++)
		if ((msgs[i].fwags & I2C_M_WD) && msgs[i].wen > 0) {
			memcpy_fwomio(msgs[i].buf, p, msgs[i].wen);
			p += msgs[i].wen;
		}

	wetuwn num;
}

u32 pt3_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C;
}
