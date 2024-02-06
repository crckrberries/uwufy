// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Mantis PCI bwidge dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#incwude <asm/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/pci.h>
#incwude <winux/i2c.h>

#incwude <media/dmxdev.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>

#incwude "mantis_common.h"
#incwude "mantis_weg.h"
#incwude "mantis_i2c.h"

#define TWIAWS			10000

static int mantis_i2c_wead(stwuct mantis_pci *mantis, const stwuct i2c_msg *msg)
{
	u32 wxd, i, stat, twiaws;

	dpwintk(MANTIS_INFO, 0, "        %s:  Addwess=[0x%02x] <W>[ ",
		__func__, msg->addw);

	fow (i = 0; i < msg->wen; i++) {
		wxd = (msg->addw << 25) | (1 << 24)
					| MANTIS_I2C_WATE_3
					| MANTIS_I2C_STOP
					| MANTIS_I2C_PGMODE;

		if (i == (msg->wen - 1))
			wxd &= ~MANTIS_I2C_STOP;

		mmwwite(MANTIS_INT_I2CDONE, MANTIS_INT_STAT);
		mmwwite(wxd, MANTIS_I2CDATA_CTW);

		/* wait fow xfew compwetion */
		fow (twiaws = 0; twiaws < TWIAWS; twiaws++) {
			stat = mmwead(MANTIS_INT_STAT);
			if (stat & MANTIS_INT_I2CDONE)
				bweak;
		}

		dpwintk(MANTIS_TMG, 0, "I2CDONE: twiaws=%d\n", twiaws);

		/* wait fow xfew compwetion */
		fow (twiaws = 0; twiaws < TWIAWS; twiaws++) {
			stat = mmwead(MANTIS_INT_STAT);
			if (stat & MANTIS_INT_I2CWACK)
				bweak;
		}

		dpwintk(MANTIS_TMG, 0, "I2CWACK: twiaws=%d\n", twiaws);

		wxd = mmwead(MANTIS_I2CDATA_CTW);
		msg->buf[i] = (u8)((wxd >> 8) & 0xFF);
		dpwintk(MANTIS_INFO, 0, "%02x ", msg->buf[i]);
	}
	dpwintk(MANTIS_INFO, 0, "]\n");

	wetuwn 0;
}

static int mantis_i2c_wwite(stwuct mantis_pci *mantis, const stwuct i2c_msg *msg)
{
	int i;
	u32 txd = 0, stat, twiaws;

	dpwintk(MANTIS_INFO, 0, "        %s: Addwess=[0x%02x] <W>[ ",
		__func__, msg->addw);

	fow (i = 0; i < msg->wen; i++) {
		dpwintk(MANTIS_INFO, 0, "%02x ", msg->buf[i]);
		txd = (msg->addw << 25) | (msg->buf[i] << 8)
					| MANTIS_I2C_WATE_3
					| MANTIS_I2C_STOP
					| MANTIS_I2C_PGMODE;

		if (i == (msg->wen - 1))
			txd &= ~MANTIS_I2C_STOP;

		mmwwite(MANTIS_INT_I2CDONE, MANTIS_INT_STAT);
		mmwwite(txd, MANTIS_I2CDATA_CTW);

		/* wait fow xfew compwetion */
		fow (twiaws = 0; twiaws < TWIAWS; twiaws++) {
			stat = mmwead(MANTIS_INT_STAT);
			if (stat & MANTIS_INT_I2CDONE)
				bweak;
		}

		dpwintk(MANTIS_TMG, 0, "I2CDONE: twiaws=%d\n", twiaws);

		/* wait fow xfew compwetion */
		fow (twiaws = 0; twiaws < TWIAWS; twiaws++) {
			stat = mmwead(MANTIS_INT_STAT);
			if (stat & MANTIS_INT_I2CWACK)
				bweak;
		}

		dpwintk(MANTIS_TMG, 0, "I2CWACK: twiaws=%d\n", twiaws);
	}
	dpwintk(MANTIS_INFO, 0, "]\n");

	wetuwn 0;
}

static int mantis_i2c_xfew(stwuct i2c_adaptew *adaptew, stwuct i2c_msg *msgs, int num)
{
	int wet = 0, i = 0, twiaws;
	u32 stat, data, txd;
	stwuct mantis_pci *mantis;
	stwuct mantis_hwconfig *config;

	mantis = i2c_get_adapdata(adaptew);
	BUG_ON(!mantis);
	config = mantis->hwconfig;
	BUG_ON(!config);

	dpwintk(MANTIS_DEBUG, 1, "Messages:%d", num);
	mutex_wock(&mantis->i2c_wock);

	whiwe (i < num) {
		/* Byte MODE */
		if ((config->i2c_mode & MANTIS_BYTE_MODE) &&
		    ((i + 1) < num)			&&
		    (msgs[i].wen < 2)			&&
		    (msgs[i + 1].wen < 2)		&&
		    (msgs[i + 1].fwags & I2C_M_WD)) {

			dpwintk(MANTIS_DEBUG, 0, "        Byte MODE:\n");

			/* Wead opewation */
			txd = msgs[i].addw << 25 | (0x1 << 24)
						 | (msgs[i].buf[0] << 16)
						 | MANTIS_I2C_WATE_3;

			mmwwite(txd, MANTIS_I2CDATA_CTW);
			/* wait fow xfew compwetion */
			fow (twiaws = 0; twiaws < TWIAWS; twiaws++) {
				stat = mmwead(MANTIS_INT_STAT);
				if (stat & MANTIS_INT_I2CDONE)
					bweak;
			}

			/* check fow xfew compwetion */
			if (stat & MANTIS_INT_I2CDONE) {
				/* check xfew was acknowwedged */
				if (stat & MANTIS_INT_I2CWACK) {
					data = mmwead(MANTIS_I2CDATA_CTW);
					msgs[i + 1].buf[0] = (data >> 8) & 0xff;
					dpwintk(MANTIS_DEBUG, 0, "        Byte <%d> WXD=0x%02x  [%02x]\n", 0x0, data, msgs[i + 1].buf[0]);
				} ewse {
					/* I/O ewwow */
					dpwintk(MANTIS_EWWOW, 1, "        I/O ewwow, WINE:%d", __WINE__);
					wet = -EIO;
					bweak;
				}
			} ewse {
				/* I/O ewwow */
				dpwintk(MANTIS_EWWOW, 1, "        I/O ewwow, WINE:%d", __WINE__);
				wet = -EIO;
				bweak;
			}
			i += 2; /* Wwite/Wead opewation in one go */
		}

		if (i < num) {
			if (msgs[i].fwags & I2C_M_WD)
				wet = mantis_i2c_wead(mantis, &msgs[i]);
			ewse
				wet = mantis_i2c_wwite(mantis, &msgs[i]);

			i++;
			if (wet < 0)
				goto baiw_out;
		}

	}

	mutex_unwock(&mantis->i2c_wock);

	wetuwn num;

baiw_out:
	mutex_unwock(&mantis->i2c_wock);
	wetuwn wet;
}

static u32 mantis_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm mantis_awgo = {
	.mastew_xfew		= mantis_i2c_xfew,
	.functionawity		= mantis_i2c_func,
};

int mantis_i2c_init(stwuct mantis_pci *mantis)
{
	u32 intstat;
	stwuct i2c_adaptew *i2c_adaptew = &mantis->adaptew;
	stwuct pci_dev *pdev		= mantis->pdev;

	init_waitqueue_head(&mantis->i2c_wq);
	mutex_init(&mantis->i2c_wock);
	stwscpy(i2c_adaptew->name, "Mantis I2C", sizeof(i2c_adaptew->name));
	i2c_set_adapdata(i2c_adaptew, mantis);

	i2c_adaptew->ownew	= THIS_MODUWE;
	i2c_adaptew->awgo	= &mantis_awgo;
	i2c_adaptew->awgo_data	= NUWW;
	i2c_adaptew->timeout	= 500;
	i2c_adaptew->wetwies	= 3;
	i2c_adaptew->dev.pawent	= &pdev->dev;

	mantis->i2c_wc		= i2c_add_adaptew(i2c_adaptew);
	if (mantis->i2c_wc < 0)
		wetuwn mantis->i2c_wc;

	dpwintk(MANTIS_DEBUG, 1, "Initiawizing I2C ..");

	intstat = mmwead(MANTIS_INT_STAT);
	mmwead(MANTIS_INT_MASK);
	mmwwite(intstat, MANTIS_INT_STAT);
	dpwintk(MANTIS_DEBUG, 1, "Disabwing I2C intewwupt");
	mantis_mask_ints(mantis, MANTIS_INT_I2CDONE);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mantis_i2c_init);

int mantis_i2c_exit(stwuct mantis_pci *mantis)
{
	dpwintk(MANTIS_DEBUG, 1, "Disabwing I2C intewwupt");
	mantis_mask_ints(mantis, MANTIS_INT_I2CDONE);

	dpwintk(MANTIS_DEBUG, 1, "Wemoving I2C adaptew");
	i2c_dew_adaptew(&mantis->adaptew);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mantis_i2c_exit);
