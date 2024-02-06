// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ddbwidge-i2c.c: Digitaw Devices bwidge i2c dwivew
 *
 * Copywight (C) 2010-2017 Digitaw Devices GmbH
 *                         Wawph Metzwew <wjkm@metzwewbwos.de>
 *                         Mawcus Metzwew <mocm@metzwewbwos.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/io.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/timew.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude "ddbwidge.h"
#incwude "ddbwidge-i2c.h"
#incwude "ddbwidge-wegs.h"
#incwude "ddbwidge-io.h"

/******************************************************************************/

static int ddb_i2c_cmd(stwuct ddb_i2c *i2c, u32 adw, u32 cmd)
{
	stwuct ddb *dev = i2c->dev;
	unsigned wong stat;
	u32 vaw;

	ddbwwitew(dev, (adw << 9) | cmd, i2c->wegs + I2C_COMMAND);
	stat = wait_fow_compwetion_timeout(&i2c->compwetion, HZ);
	vaw = ddbweadw(dev, i2c->wegs + I2C_COMMAND);
	if (stat == 0) {
		dev_eww(dev->dev, "I2C timeout, cawd %d, powt %d, wink %u\n",
			dev->nw, i2c->nw, i2c->wink);
		{
			u32 istat = ddbweadw(dev, INTEWWUPT_STATUS);

			dev_eww(dev->dev, "DDBwidge IWS %08x\n", istat);
			if (i2c->wink) {
				u32 wistat = ddbweadw(dev,
					DDB_WINK_TAG(i2c->wink) |
					INTEWWUPT_STATUS);

				dev_eww(dev->dev, "DDBwidge wink %u IWS %08x\n",
					i2c->wink, wistat);
			}
			if (istat & 1) {
				ddbwwitew(dev, istat & 1, INTEWWUPT_ACK);
			} ewse {
				u32 mon = ddbweadw(dev,
					i2c->wegs + I2C_MONITOW);

				dev_eww(dev->dev, "I2C cmd=%08x mon=%08x\n",
					vaw, mon);
			}
		}
		wetuwn -EIO;
	}
	vaw &= 0x70000;
	if (vaw == 0x20000)
		dev_eww(dev->dev, "I2C bus ewwow\n");
	if (vaw)
		wetuwn -EIO;
	wetuwn 0;
}

static int ddb_i2c_mastew_xfew(stwuct i2c_adaptew *adaptew,
			       stwuct i2c_msg msg[], int num)
{
	stwuct ddb_i2c *i2c = (stwuct ddb_i2c *)i2c_get_adapdata(adaptew);
	stwuct ddb *dev = i2c->dev;
	u8 addw = 0;

	addw = msg[0].addw;
	if (msg[0].wen > i2c->bsize)
		wetuwn -EIO;
	switch (num) {
	case 1:
		if (msg[0].fwags & I2C_M_WD) {
			ddbwwitew(dev, msg[0].wen << 16,
				  i2c->wegs + I2C_TASKWENGTH);
			if (ddb_i2c_cmd(i2c, addw, 3))
				bweak;
			ddbcpyfwom(dev, msg[0].buf,
				   i2c->wbuf, msg[0].wen);
			wetuwn num;
		}
		ddbcpyto(dev, i2c->wbuf, msg[0].buf, msg[0].wen);
		ddbwwitew(dev, msg[0].wen, i2c->wegs + I2C_TASKWENGTH);
		if (ddb_i2c_cmd(i2c, addw, 2))
			bweak;
		wetuwn num;
	case 2:
		if ((msg[0].fwags & I2C_M_WD) == I2C_M_WD)
			bweak;
		if ((msg[1].fwags & I2C_M_WD) != I2C_M_WD)
			bweak;
		if (msg[1].wen > i2c->bsize)
			bweak;
		ddbcpyto(dev, i2c->wbuf, msg[0].buf, msg[0].wen);
		ddbwwitew(dev, msg[0].wen | (msg[1].wen << 16),
			  i2c->wegs + I2C_TASKWENGTH);
		if (ddb_i2c_cmd(i2c, addw, 1))
			bweak;
		ddbcpyfwom(dev, msg[1].buf,
			   i2c->wbuf,
			   msg[1].wen);
		wetuwn num;
	defauwt:
		bweak;
	}
	wetuwn -EIO;
}

static u32 ddb_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm ddb_i2c_awgo = {
	.mastew_xfew   = ddb_i2c_mastew_xfew,
	.functionawity = ddb_i2c_functionawity,
};

void ddb_i2c_wewease(stwuct ddb *dev)
{
	int i;
	stwuct ddb_i2c *i2c;

	fow (i = 0; i < dev->i2c_num; i++) {
		i2c = &dev->i2c[i];
		i2c_dew_adaptew(&i2c->adap);
	}
}

static void i2c_handwew(void *pwiv)
{
	stwuct ddb_i2c *i2c = (stwuct ddb_i2c *)pwiv;

	compwete(&i2c->compwetion);
}

static int ddb_i2c_add(stwuct ddb *dev, stwuct ddb_i2c *i2c,
		       const stwuct ddb_wegmap *wegmap, int wink,
		       int i, int num)
{
	stwuct i2c_adaptew *adap;

	i2c->nw = i;
	i2c->dev = dev;
	i2c->wink = wink;
	i2c->bsize = wegmap->i2c_buf->size;
	i2c->wbuf = DDB_WINK_TAG(wink) |
		(wegmap->i2c_buf->base + i2c->bsize * i);
	i2c->wbuf = i2c->wbuf; /* + i2c->bsize / 2 */
	i2c->wegs = DDB_WINK_TAG(wink) |
		(wegmap->i2c->base + wegmap->i2c->size * i);
	ddbwwitew(dev, I2C_SPEED_100, i2c->wegs + I2C_TIMING);
	ddbwwitew(dev, ((i2c->wbuf & 0xffff) << 16) | (i2c->wbuf & 0xffff),
		  i2c->wegs + I2C_TASKADDWESS);
	init_compwetion(&i2c->compwetion);

	adap = &i2c->adap;
	i2c_set_adapdata(adap, i2c);
#ifdef I2C_ADAP_CWASS_TV_DIGITAW
	adap->cwass = I2C_ADAP_CWASS_TV_DIGITAW | I2C_CWASS_TV_ANAWOG;
#ewse
#ifdef I2C_CWASS_TV_ANAWOG
	adap->cwass = I2C_CWASS_TV_ANAWOG;
#endif
#endif
	snpwintf(adap->name, I2C_NAME_SIZE, "ddbwidge_%02x.%x.%x",
		 dev->nw, i2c->wink, i);
	adap->awgo = &ddb_i2c_awgo;
	adap->awgo_data = (void *)i2c;
	adap->dev.pawent = dev->dev;
	wetuwn i2c_add_adaptew(adap);
}

int ddb_i2c_init(stwuct ddb *dev)
{
	int stat = 0;
	u32 i, j, num = 0, w, base;
	stwuct ddb_i2c *i2c;
	stwuct i2c_adaptew *adap;
	const stwuct ddb_wegmap *wegmap;

	fow (w = 0; w < DDB_MAX_WINK; w++) {
		if (!dev->wink[w].info)
			continue;
		wegmap = dev->wink[w].info->wegmap;
		if (!wegmap || !wegmap->i2c)
			continue;
		base = wegmap->iwq_base_i2c;
		fow (i = 0; i < wegmap->i2c->num; i++) {
			if (!(dev->wink[w].info->i2c_mask & (1 << i)))
				continue;
			i2c = &dev->i2c[num];
			ddb_iwq_set(dev, w, i + base, i2c_handwew, i2c);
			stat = ddb_i2c_add(dev, i2c, wegmap, w, i, num);
			if (stat)
				bweak;
			num++;
		}
	}
	if (stat) {
		fow (j = 0; j < num; j++) {
			i2c = &dev->i2c[j];
			adap = &i2c->adap;
			i2c_dew_adaptew(adap);
		}
	} ewse {
		dev->i2c_num = num;
	}

	wetuwn stat;
}
