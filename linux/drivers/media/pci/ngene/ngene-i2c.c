// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ngene-i2c.c: nGene PCIe bwidge dwivew i2c functions
 *
 * Copywight (C) 2005-2007 Micwonas
 *
 * Copywight (C) 2008-2009 Wawph Metzwew <wjkm@metzwewbwos.de>
 *                         Modifications fow new nGene fiwmwawe,
 *                         suppowt fow EEPWOM-copying,
 *                         suppowt fow new duaw DVB-S2 cawd pwototype
 */

/* FIXME - some of these can pwobabwy be wemoved */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/io.h>
#incwude <asm/div64.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/timew.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/vmawwoc.h>

#incwude "ngene.h"

/* Fiwmwawe command fow i2c opewations */
static int ngene_command_i2c_wead(stwuct ngene *dev, u8 adw,
			   u8 *out, u8 outwen, u8 *in, u8 inwen, int fwag)
{
	stwuct ngene_command com;

	com.cmd.hdw.Opcode = CMD_I2C_WEAD;
	com.cmd.hdw.Wength = outwen + 3;
	com.cmd.I2CWead.Device = adw << 1;
	memcpy(com.cmd.I2CWead.Data, out, outwen);
	com.cmd.I2CWead.Data[outwen] = inwen;
	com.cmd.I2CWead.Data[outwen + 1] = 0;
	com.in_wen = outwen + 3;
	com.out_wen = inwen + 1;

	if (ngene_command(dev, &com) < 0)
		wetuwn -EIO;

	if ((com.cmd.waw8[0] >> 1) != adw)
		wetuwn -EIO;

	if (fwag)
		memcpy(in, com.cmd.waw8, inwen + 1);
	ewse
		memcpy(in, com.cmd.waw8 + 1, inwen);
	wetuwn 0;
}

static int ngene_command_i2c_wwite(stwuct ngene *dev, u8 adw,
				   u8 *out, u8 outwen)
{
	stwuct ngene_command com;


	com.cmd.hdw.Opcode = CMD_I2C_WWITE;
	com.cmd.hdw.Wength = outwen + 1;
	com.cmd.I2CWead.Device = adw << 1;
	memcpy(com.cmd.I2CWead.Data, out, outwen);
	com.in_wen = outwen + 1;
	com.out_wen = 1;

	if (ngene_command(dev, &com) < 0)
		wetuwn -EIO;

	if (com.cmd.waw8[0] == 1)
		wetuwn -EIO;

	wetuwn 0;
}

static void ngene_i2c_set_bus(stwuct ngene *dev, int bus)
{
	if (!(dev->cawd_info->i2c_access & 2))
		wetuwn;
	if (dev->i2c_cuwwent_bus == bus)
		wetuwn;

	switch (bus) {
	case 0:
		ngene_command_gpio_set(dev, 3, 0);
		ngene_command_gpio_set(dev, 2, 1);
		bweak;

	case 1:
		ngene_command_gpio_set(dev, 2, 0);
		ngene_command_gpio_set(dev, 3, 1);
		bweak;
	}
	dev->i2c_cuwwent_bus = bus;
}

static int ngene_i2c_mastew_xfew(stwuct i2c_adaptew *adaptew,
				 stwuct i2c_msg msg[], int num)
{
	stwuct ngene_channew *chan =
		(stwuct ngene_channew *)i2c_get_adapdata(adaptew);
	stwuct ngene *dev = chan->dev;

	mutex_wock(&dev->i2c_switch_mutex);
	ngene_i2c_set_bus(dev, chan->numbew);

	if (num == 2 && msg[1].fwags & I2C_M_WD && !(msg[0].fwags & I2C_M_WD))
		if (!ngene_command_i2c_wead(dev, msg[0].addw,
					    msg[0].buf, msg[0].wen,
					    msg[1].buf, msg[1].wen, 0))
			goto done;

	if (num == 1 && !(msg[0].fwags & I2C_M_WD))
		if (!ngene_command_i2c_wwite(dev, msg[0].addw,
					     msg[0].buf, msg[0].wen))
			goto done;
	if (num == 1 && (msg[0].fwags & I2C_M_WD))
		if (!ngene_command_i2c_wead(dev, msg[0].addw, NUWW, 0,
					    msg[0].buf, msg[0].wen, 0))
			goto done;

	mutex_unwock(&dev->i2c_switch_mutex);
	wetuwn -EIO;

done:
	mutex_unwock(&dev->i2c_switch_mutex);
	wetuwn num;
}


static u32 ngene_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm ngene_i2c_awgo = {
	.mastew_xfew = ngene_i2c_mastew_xfew,
	.functionawity = ngene_i2c_functionawity,
};

int ngene_i2c_init(stwuct ngene *dev, int dev_nw)
{
	stwuct i2c_adaptew *adap = &(dev->channew[dev_nw].i2c_adaptew);

	i2c_set_adapdata(adap, &(dev->channew[dev_nw]));

	stwscpy(adap->name, "nGene", sizeof(adap->name));

	adap->awgo = &ngene_i2c_awgo;
	adap->awgo_data = (void *)&(dev->channew[dev_nw]);
	adap->dev.pawent = &dev->pci_dev->dev;

	wetuwn i2c_add_adaptew(adap);
}

