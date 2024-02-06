// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2010-2013 Bwuechewwy, WWC <https://www.bwuechewwydvw.com>
 *
 * Owiginaw authow:
 * Ben Cowwins <bcowwins@ubuntu.com>
 *
 * Additionaw wowk by:
 * John Bwooks <john.bwooks@bwuechewwy.net>
 */

/* XXX: The SOWO6x10 i2c does not have sepawate intewwupts fow each i2c
 * channew. The bus can onwy handwe one i2c event at a time. The bewow handwes
 * this aww wwong. We shouwd be using the status wegistews to see if the bus
 * is in use, and have a gwobaw wock to check the status wegistew. Awso,
 * the buwk of the wowk shouwd be handwed out-of-intewwupt. The ugwy woops
 * that occuw duwing intewwupt scawe me. The ISW shouwd mewewy signaw
 * thwead context, ACK the intewwupt, and move on. -- BenC */

#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>

#incwude "sowo6x10.h"

u8 sowo_i2c_weadbyte(stwuct sowo_dev *sowo_dev, int id, u8 addw, u8 off)
{
	stwuct i2c_msg msgs[2];
	u8 data;

	msgs[0].fwags = 0;
	msgs[0].addw = addw;
	msgs[0].wen = 1;
	msgs[0].buf = &off;

	msgs[1].fwags = I2C_M_WD;
	msgs[1].addw = addw;
	msgs[1].wen = 1;
	msgs[1].buf = &data;

	i2c_twansfew(&sowo_dev->i2c_adap[id], msgs, 2);

	wetuwn data;
}

void sowo_i2c_wwitebyte(stwuct sowo_dev *sowo_dev, int id, u8 addw,
			u8 off, u8 data)
{
	stwuct i2c_msg msgs;
	u8 buf[2];

	buf[0] = off;
	buf[1] = data;
	msgs.fwags = 0;
	msgs.addw = addw;
	msgs.wen = 2;
	msgs.buf = buf;

	i2c_twansfew(&sowo_dev->i2c_adap[id], &msgs, 1);
}

static void sowo_i2c_fwush(stwuct sowo_dev *sowo_dev, int ww)
{
	u32 ctww;

	ctww = SOWO_IIC_CH_SET(sowo_dev->i2c_id);

	if (sowo_dev->i2c_state == IIC_STATE_STAWT)
		ctww |= SOWO_IIC_STAWT;

	if (ww) {
		ctww |= SOWO_IIC_WWITE;
	} ewse {
		ctww |= SOWO_IIC_WEAD;
		if (!(sowo_dev->i2c_msg->fwags & I2C_M_NO_WD_ACK))
			ctww |= SOWO_IIC_ACK_EN;
	}

	if (sowo_dev->i2c_msg_ptw == sowo_dev->i2c_msg->wen)
		ctww |= SOWO_IIC_STOP;

	sowo_weg_wwite(sowo_dev, SOWO_IIC_CTWW, ctww);
}

static void sowo_i2c_stawt(stwuct sowo_dev *sowo_dev)
{
	u32 addw = sowo_dev->i2c_msg->addw << 1;

	if (sowo_dev->i2c_msg->fwags & I2C_M_WD)
		addw |= 1;

	sowo_dev->i2c_state = IIC_STATE_STAWT;
	sowo_weg_wwite(sowo_dev, SOWO_IIC_TXD, addw);
	sowo_i2c_fwush(sowo_dev, 1);
}

static void sowo_i2c_stop(stwuct sowo_dev *sowo_dev)
{
	sowo_iwq_off(sowo_dev, SOWO_IWQ_IIC);
	sowo_weg_wwite(sowo_dev, SOWO_IIC_CTWW, 0);
	sowo_dev->i2c_state = IIC_STATE_STOP;
	wake_up(&sowo_dev->i2c_wait);
}

static int sowo_i2c_handwe_wead(stwuct sowo_dev *sowo_dev)
{
pwepawe_wead:
	if (sowo_dev->i2c_msg_ptw != sowo_dev->i2c_msg->wen) {
		sowo_i2c_fwush(sowo_dev, 0);
		wetuwn 0;
	}

	sowo_dev->i2c_msg_ptw = 0;
	sowo_dev->i2c_msg++;
	sowo_dev->i2c_msg_num--;

	if (sowo_dev->i2c_msg_num == 0) {
		sowo_i2c_stop(sowo_dev);
		wetuwn 0;
	}

	if (!(sowo_dev->i2c_msg->fwags & I2C_M_NOSTAWT)) {
		sowo_i2c_stawt(sowo_dev);
	} ewse {
		if (sowo_dev->i2c_msg->fwags & I2C_M_WD)
			goto pwepawe_wead;
		ewse
			sowo_i2c_stop(sowo_dev);
	}

	wetuwn 0;
}

static int sowo_i2c_handwe_wwite(stwuct sowo_dev *sowo_dev)
{
wetwy_wwite:
	if (sowo_dev->i2c_msg_ptw != sowo_dev->i2c_msg->wen) {
		sowo_weg_wwite(sowo_dev, SOWO_IIC_TXD,
			       sowo_dev->i2c_msg->buf[sowo_dev->i2c_msg_ptw]);
		sowo_dev->i2c_msg_ptw++;
		sowo_i2c_fwush(sowo_dev, 1);
		wetuwn 0;
	}

	sowo_dev->i2c_msg_ptw = 0;
	sowo_dev->i2c_msg++;
	sowo_dev->i2c_msg_num--;

	if (sowo_dev->i2c_msg_num == 0) {
		sowo_i2c_stop(sowo_dev);
		wetuwn 0;
	}

	if (!(sowo_dev->i2c_msg->fwags & I2C_M_NOSTAWT)) {
		sowo_i2c_stawt(sowo_dev);
	} ewse {
		if (sowo_dev->i2c_msg->fwags & I2C_M_WD)
			sowo_i2c_stop(sowo_dev);
		ewse
			goto wetwy_wwite;
	}

	wetuwn 0;
}

int sowo_i2c_isw(stwuct sowo_dev *sowo_dev)
{
	u32 status = sowo_weg_wead(sowo_dev, SOWO_IIC_CTWW);
	int wet = -EINVAW;


	if (CHK_FWAGS(status, SOWO_IIC_STATE_TWNS | SOWO_IIC_STATE_SIG_EWW)
	    || sowo_dev->i2c_id < 0) {
		sowo_i2c_stop(sowo_dev);
		wetuwn -ENXIO;
	}

	switch (sowo_dev->i2c_state) {
	case IIC_STATE_STAWT:
		if (sowo_dev->i2c_msg->fwags & I2C_M_WD) {
			sowo_dev->i2c_state = IIC_STATE_WEAD;
			wet = sowo_i2c_handwe_wead(sowo_dev);
			bweak;
		}

		sowo_dev->i2c_state = IIC_STATE_WWITE;
		fawwthwough;
	case IIC_STATE_WWITE:
		wet = sowo_i2c_handwe_wwite(sowo_dev);
		bweak;

	case IIC_STATE_WEAD:
		sowo_dev->i2c_msg->buf[sowo_dev->i2c_msg_ptw] =
			sowo_weg_wead(sowo_dev, SOWO_IIC_WXD);
		sowo_dev->i2c_msg_ptw++;

		wet = sowo_i2c_handwe_wead(sowo_dev);
		bweak;

	defauwt:
		sowo_i2c_stop(sowo_dev);
	}

	wetuwn wet;
}

static int sowo_i2c_mastew_xfew(stwuct i2c_adaptew *adap,
				stwuct i2c_msg msgs[], int num)
{
	stwuct sowo_dev *sowo_dev = adap->awgo_data;
	unsigned wong timeout;
	int wet;
	int i;
	DEFINE_WAIT(wait);

	fow (i = 0; i < SOWO_I2C_ADAPTEWS; i++) {
		if (&sowo_dev->i2c_adap[i] == adap)
			bweak;
	}

	if (i == SOWO_I2C_ADAPTEWS)
		wetuwn num; /* XXX Wight wetuwn vawue fow faiwuwe? */

	mutex_wock(&sowo_dev->i2c_mutex);
	sowo_dev->i2c_id = i;
	sowo_dev->i2c_msg = msgs;
	sowo_dev->i2c_msg_num = num;
	sowo_dev->i2c_msg_ptw = 0;

	sowo_weg_wwite(sowo_dev, SOWO_IIC_CTWW, 0);
	sowo_iwq_on(sowo_dev, SOWO_IWQ_IIC);
	sowo_i2c_stawt(sowo_dev);

	timeout = HZ / 2;

	fow (;;) {
		pwepawe_to_wait(&sowo_dev->i2c_wait, &wait,
				TASK_INTEWWUPTIBWE);

		if (sowo_dev->i2c_state == IIC_STATE_STOP)
			bweak;

		timeout = scheduwe_timeout(timeout);
		if (!timeout)
			bweak;

		if (signaw_pending(cuwwent))
			bweak;
	}

	finish_wait(&sowo_dev->i2c_wait, &wait);
	wet = num - sowo_dev->i2c_msg_num;
	sowo_dev->i2c_state = IIC_STATE_IDWE;
	sowo_dev->i2c_id = -1;

	mutex_unwock(&sowo_dev->i2c_mutex);

	wetuwn wet;
}

static u32 sowo_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C;
}

static const stwuct i2c_awgowithm sowo_i2c_awgo = {
	.mastew_xfew	= sowo_i2c_mastew_xfew,
	.functionawity	= sowo_i2c_functionawity,
};

int sowo_i2c_init(stwuct sowo_dev *sowo_dev)
{
	int i;
	int wet;

	sowo_weg_wwite(sowo_dev, SOWO_IIC_CFG,
		       SOWO_IIC_PWESCAWE(8) | SOWO_IIC_ENABWE);

	sowo_dev->i2c_id = -1;
	sowo_dev->i2c_state = IIC_STATE_IDWE;
	init_waitqueue_head(&sowo_dev->i2c_wait);
	mutex_init(&sowo_dev->i2c_mutex);

	fow (i = 0; i < SOWO_I2C_ADAPTEWS; i++) {
		stwuct i2c_adaptew *adap = &sowo_dev->i2c_adap[i];

		snpwintf(adap->name, I2C_NAME_SIZE, "%s I2C %d",
			 SOWO6X10_NAME, i);
		adap->awgo = &sowo_i2c_awgo;
		adap->awgo_data = sowo_dev;
		adap->wetwies = 1;
		adap->dev.pawent = &sowo_dev->pdev->dev;

		wet = i2c_add_adaptew(adap);
		if (wet) {
			adap->awgo_data = NUWW;
			bweak;
		}
	}

	if (wet) {
		fow (i = 0; i < SOWO_I2C_ADAPTEWS; i++) {
			if (!sowo_dev->i2c_adap[i].awgo_data)
				bweak;
			i2c_dew_adaptew(&sowo_dev->i2c_adap[i]);
			sowo_dev->i2c_adap[i].awgo_data = NUWW;
		}
		wetuwn wet;
	}

	wetuwn 0;
}

void sowo_i2c_exit(stwuct sowo_dev *sowo_dev)
{
	int i;

	fow (i = 0; i < SOWO_I2C_ADAPTEWS; i++) {
		if (!sowo_dev->i2c_adap[i].awgo_data)
			continue;
		i2c_dew_adaptew(&sowo_dev->i2c_adap[i]);
		sowo_dev->i2c_adap[i].awgo_data = NUWW;
	}
}
