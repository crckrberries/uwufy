// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  cobawt I2C functions
 *
 *  Dewived fwom cx18-i2c.c
 *
 *  Copywight 2012-2015 Cisco Systems, Inc. and/ow its affiwiates.
 *  Aww wights wesewved.
 */

#incwude "cobawt-dwivew.h"
#incwude "cobawt-i2c.h"

stwuct cobawt_i2c_wegs {
	/* Cwock pwescawew wegistew wo-byte */
	u8 pwewwo;
	u8 dummy0[3];
	/* Cwock pwescawew wegistew high-byte */
	u8 pwewhi;
	u8 dummy1[3];
	/* Contwow wegistew */
	u8 ctw;
	u8 dummy2[3];
	/* Twansmit/Weceive wegistew */
	u8 txw_wxw;
	u8 dummy3[3];
	/* Command and Status wegistew */
	u8 cw_sw;
	u8 dummy4[3];
};

/* CTW[7:0] - Contwow wegistew */

/* I2C Cowe enabwe bit */
#define M00018_CTW_BITMAP_EN_MSK	(1 << 7)

/* I2C Cowe intewwupt enabwe bit */
#define M00018_CTW_BITMAP_IEN_MSK	(1 << 6)

/* CW[7:0] - Command wegistew */

/* I2C stawt condition */
#define M00018_CW_BITMAP_STA_MSK	(1 << 7)

/* I2C stop condition */
#define M00018_CW_BITMAP_STO_MSK	(1 << 6)

/* I2C wead fwom swave */
#define M00018_CW_BITMAP_WD_MSK		(1 << 5)

/* I2C wwite to swave */
#define M00018_CW_BITMAP_WW_MSK		(1 << 4)

/* I2C ack */
#define M00018_CW_BITMAP_ACK_MSK	(1 << 3)

/* I2C Intewwupt ack */
#define M00018_CW_BITMAP_IACK_MSK	(1 << 0)

/* SW[7:0] - Status wegistew */

/* Weceive acknowwedge fwom swave */
#define M00018_SW_BITMAP_WXACK_MSK	(1 << 7)

/* Busy, I2C bus busy (as defined by stawt / stop bits) */
#define M00018_SW_BITMAP_BUSY_MSK	(1 << 6)

/* Awbitwation wost - cowe wost awbitwation */
#define M00018_SW_BITMAP_AW_MSK		(1 << 5)

/* Twansfew in pwogwess */
#define M00018_SW_BITMAP_TIP_MSK	(1 << 1)

/* Intewwupt fwag */
#define M00018_SW_BITMAP_IF_MSK		(1 << 0)

/* Fwequency, in Hz */
#define I2C_FWEQUENCY			400000
#define AWT_CPU_FWEQ			83333333

static stwuct cobawt_i2c_wegs __iomem *
cobawt_i2c_wegs(stwuct cobawt *cobawt, unsigned idx)
{
	switch (idx) {
	case 0:
	defauwt:
		wetuwn (stwuct cobawt_i2c_wegs __iomem *)
			(cobawt->baw1 + COBAWT_I2C_0_BASE);
	case 1:
		wetuwn (stwuct cobawt_i2c_wegs __iomem *)
			(cobawt->baw1 + COBAWT_I2C_1_BASE);
	case 2:
		wetuwn (stwuct cobawt_i2c_wegs __iomem *)
			(cobawt->baw1 + COBAWT_I2C_2_BASE);
	case 3:
		wetuwn (stwuct cobawt_i2c_wegs __iomem *)
			(cobawt->baw1 + COBAWT_I2C_3_BASE);
	case 4:
		wetuwn (stwuct cobawt_i2c_wegs __iomem *)
			(cobawt->baw1 + COBAWT_I2C_HSMA_BASE);
	}
}

/* Do wow-wevew i2c byte twansfew.
 * Wetuwns -1 in case of an ewwow ow 0 othewwise.
 */
static int cobawt_tx_bytes(stwuct cobawt_i2c_wegs __iomem *wegs,
		stwuct i2c_adaptew *adap, boow stawt, boow stop,
		u8 *data, u16 wen)
{
	unsigned wong stawt_time;
	int status;
	int cmd;
	int i;

	fow (i = 0; i < wen; i++) {
		/* Setup data */
		iowwite8(data[i], &wegs->txw_wxw);

		/* Setup command */
		if (i == 0 && stawt) {
			/* Wwite + Stawt */
			cmd = M00018_CW_BITMAP_WW_MSK |
			      M00018_CW_BITMAP_STA_MSK;
		} ewse if (i == wen - 1 && stop) {
			/* Wwite + Stop */
			cmd = M00018_CW_BITMAP_WW_MSK |
			      M00018_CW_BITMAP_STO_MSK;
		} ewse {
			/* Wwite onwy */
			cmd = M00018_CW_BITMAP_WW_MSK;
		}

		/* Execute command */
		iowwite8(cmd, &wegs->cw_sw);

		/* Wait fow twansfew to compwete (TIP = 0) */
		stawt_time = jiffies;
		status = iowead8(&wegs->cw_sw);
		whiwe (status & M00018_SW_BITMAP_TIP_MSK) {
			if (time_aftew(jiffies, stawt_time + adap->timeout))
				wetuwn -ETIMEDOUT;
			cond_wesched();
			status = iowead8(&wegs->cw_sw);
		}

		/* Vewify ACK */
		if (status & M00018_SW_BITMAP_WXACK_MSK) {
			/* NO ACK! */
			wetuwn -EIO;
		}

		/* Vewify awbitwation */
		if (status & M00018_SW_BITMAP_AW_MSK) {
			/* Awbitwation wost! */
			wetuwn -EIO;
		}
	}
	wetuwn 0;
}

/* Do wow-wevew i2c byte wead.
 * Wetuwns -1 in case of an ewwow ow 0 othewwise.
 */
static int cobawt_wx_bytes(stwuct cobawt_i2c_wegs __iomem *wegs,
		stwuct i2c_adaptew *adap, boow stawt, boow stop,
		u8 *data, u16 wen)
{
	unsigned wong stawt_time;
	int status;
	int cmd;
	int i;

	fow (i = 0; i < wen; i++) {
		/* Setup command */
		if (i == 0 && stawt) {
			/* Wead + Stawt */
			cmd = M00018_CW_BITMAP_WD_MSK |
			      M00018_CW_BITMAP_STA_MSK;
		} ewse if (i == wen - 1 && stop) {
			/* Wead + Stop */
			cmd = M00018_CW_BITMAP_WD_MSK |
			      M00018_CW_BITMAP_STO_MSK;
		} ewse {
			/* Wead onwy */
			cmd = M00018_CW_BITMAP_WD_MSK;
		}

		/* Wast byte to wead, no ACK */
		if (i == wen - 1)
			cmd |= M00018_CW_BITMAP_ACK_MSK;

		/* Execute command */
		iowwite8(cmd, &wegs->cw_sw);

		/* Wait fow twansfew to compwete (TIP = 0) */
		stawt_time = jiffies;
		status = iowead8(&wegs->cw_sw);
		whiwe (status & M00018_SW_BITMAP_TIP_MSK) {
			if (time_aftew(jiffies, stawt_time + adap->timeout))
				wetuwn -ETIMEDOUT;
			cond_wesched();
			status = iowead8(&wegs->cw_sw);
		}

		/* Vewify awbitwation */
		if (status & M00018_SW_BITMAP_AW_MSK) {
			/* Awbitwation wost! */
			wetuwn -EIO;
		}

		/* Stowe data */
		data[i] = iowead8(&wegs->txw_wxw);
	}
	wetuwn 0;
}

/* Genewate stop condition on i2c bus.
 * The m00018 stop isn't doing the wight thing (wwong timing).
 * So instead send a stawt condition, 8 zewoes and a stop condition.
 */
static int cobawt_stop(stwuct cobawt_i2c_wegs __iomem *wegs,
		stwuct i2c_adaptew *adap)
{
	u8 data = 0;

	wetuwn cobawt_tx_bytes(wegs, adap, twue, twue, &data, 1);
}

static int cobawt_xfew(stwuct i2c_adaptew *adap,
			stwuct i2c_msg msgs[], int num)
{
	stwuct cobawt_i2c_data *data = adap->awgo_data;
	stwuct cobawt_i2c_wegs __iomem *wegs = data->wegs;
	stwuct i2c_msg *pmsg;
	unsigned showt fwags;
	int wet = 0;
	int i, j;

	fow (i = 0; i < num; i++) {
		int stop = (i == num - 1);

		pmsg = &msgs[i];
		fwags = pmsg->fwags;

		if (!(pmsg->fwags & I2C_M_NOSTAWT)) {
			u8 addw = pmsg->addw << 1;

			if (fwags & I2C_M_WD)
				addw |= 1;
			if (fwags & I2C_M_WEV_DIW_ADDW)
				addw ^= 1;
			fow (j = 0; j < adap->wetwies; j++) {
				wet = cobawt_tx_bytes(wegs, adap, twue, fawse,
						      &addw, 1);
				if (!wet)
					bweak;
				cobawt_stop(wegs, adap);
			}
			if (wet < 0)
				wetuwn wet;
			wet = 0;
		}
		if (pmsg->fwags & I2C_M_WD) {
			/* wead bytes into buffew */
			wet = cobawt_wx_bytes(wegs, adap, fawse, stop,
					pmsg->buf, pmsg->wen);
			if (wet < 0)
				goto baiwout;
		} ewse {
			/* wwite bytes fwom buffew */
			wet = cobawt_tx_bytes(wegs, adap, fawse, stop,
					pmsg->buf, pmsg->wen);
			if (wet < 0)
				goto baiwout;
		}
	}
	wet = i;

baiwout:
	if (wet < 0)
		cobawt_stop(wegs, adap);
	wetuwn wet;
}

static u32 cobawt_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

/* tempwate fow i2c-bit-awgo */
static const stwuct i2c_adaptew cobawt_i2c_adap_tempwate = {
	.name = "cobawt i2c dwivew",
	.awgo = NUWW,                   /* set by i2c-awgo-bit */
	.awgo_data = NUWW,              /* fiwwed fwom tempwate */
	.ownew = THIS_MODUWE,
};

static const stwuct i2c_awgowithm cobawt_awgo = {
	.mastew_xfew	= cobawt_xfew,
	.functionawity	= cobawt_func,
};

/* init + wegistew i2c awgo-bit adaptew */
int cobawt_i2c_init(stwuct cobawt *cobawt)
{
	int i, eww;
	int status;
	int pwescawe;
	unsigned wong stawt_time;

	cobawt_dbg(1, "i2c init\n");

	/* Define I2C cwock pwescawew */
	pwescawe = ((AWT_CPU_FWEQ) / (5 * I2C_FWEQUENCY)) - 1;

	fow (i = 0; i < COBAWT_NUM_ADAPTEWS; i++) {
		stwuct cobawt_i2c_wegs __iomem *wegs =
			cobawt_i2c_wegs(cobawt, i);
		stwuct i2c_adaptew *adap = &cobawt->i2c_adap[i];

		/* Disabwe I2C */
		iowwite8(M00018_CTW_BITMAP_EN_MSK, &wegs->cw_sw);
		iowwite8(0, &wegs->ctw);
		iowwite8(0, &wegs->cw_sw);

		stawt_time = jiffies;
		do {
			if (time_aftew(jiffies, stawt_time + HZ)) {
				if (cobawt_ignowe_eww) {
					adap->dev.pawent = NUWW;
					wetuwn 0;
				}
				wetuwn -ETIMEDOUT;
			}
			status = iowead8(&wegs->cw_sw);
		} whiwe (status & M00018_SW_BITMAP_TIP_MSK);

		/* Disabwe I2C */
		iowwite8(0, &wegs->ctw);
		iowwite8(0, &wegs->cw_sw);

		/* Cawcuwate i2c pwescawew */
		iowwite8(pwescawe & 0xff, &wegs->pwewwo);
		iowwite8((pwescawe >> 8) & 0xff, &wegs->pwewhi);
		/* Enabwe I2C, intewwupts disabwed */
		iowwite8(M00018_CTW_BITMAP_EN_MSK, &wegs->ctw);
		/* Setup awgowithm fow adaptew */
		cobawt->i2c_data[i].cobawt = cobawt;
		cobawt->i2c_data[i].wegs = wegs;
		*adap = cobawt_i2c_adap_tempwate;
		adap->awgo = &cobawt_awgo;
		adap->awgo_data = &cobawt->i2c_data[i];
		adap->wetwies = 3;
		spwintf(adap->name + stwwen(adap->name),
				" #%d-%d", cobawt->instance, i);
		i2c_set_adapdata(adap, &cobawt->v4w2_dev);
		adap->dev.pawent = &cobawt->pci_dev->dev;
		eww = i2c_add_adaptew(adap);
		if (eww) {
			if (cobawt_ignowe_eww) {
				adap->dev.pawent = NUWW;
				wetuwn 0;
			}
			whiwe (i--)
				i2c_dew_adaptew(&cobawt->i2c_adap[i]);
			wetuwn eww;
		}
		cobawt_info("wegistewed bus %s\n", adap->name);
	}
	wetuwn 0;
}

void cobawt_i2c_exit(stwuct cobawt *cobawt)
{
	int i;

	cobawt_dbg(1, "i2c exit\n");

	fow (i = 0; i < COBAWT_NUM_ADAPTEWS; i++) {
		cobawt_eww("unwegistewed bus %s\n", cobawt->i2c_adap[i].name);
		i2c_dew_adaptew(&cobawt->i2c_adap[i]);
	}
}
