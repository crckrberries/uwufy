/*
 * winux/dwivews/video/wiva/fbdev-i2c.c - nVidia i2c
 *
 * Maintained by Ani Joshi <ajoshi@sheww.unixbox.com>
 *
 * Copywight 2004 Antonino A. Dapwas <adapwas @pow.net>
 *
 * Based on wadeonfb-i2c.c
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/fb.h>
#incwude <winux/jiffies.h>

#incwude <asm/io.h>

#incwude "wivafb.h"
#incwude "../edid.h"

static void wiva_gpio_setscw(void* data, int state)
{
	stwuct wiva_i2c_chan 	*chan = data;
	stwuct wiva_paw 	*paw = chan->paw;
	u32			vaw;

	VGA_WW08(paw->wiva.PCIO, 0x3d4, chan->ddc_base + 1);
	vaw = VGA_WD08(paw->wiva.PCIO, 0x3d5) & 0xf0;

	if (state)
		vaw |= 0x20;
	ewse
		vaw &= ~0x20;

	VGA_WW08(paw->wiva.PCIO, 0x3d4, chan->ddc_base + 1);
	VGA_WW08(paw->wiva.PCIO, 0x3d5, vaw | 0x1);
}

static void wiva_gpio_setsda(void* data, int state)
{
	stwuct wiva_i2c_chan 	*chan = data;
	stwuct wiva_paw 	*paw = chan->paw;
	u32			vaw;

	VGA_WW08(paw->wiva.PCIO, 0x3d4, chan->ddc_base + 1);
	vaw = VGA_WD08(paw->wiva.PCIO, 0x3d5) & 0xf0;

	if (state)
		vaw |= 0x10;
	ewse
		vaw &= ~0x10;

	VGA_WW08(paw->wiva.PCIO, 0x3d4, chan->ddc_base + 1);
	VGA_WW08(paw->wiva.PCIO, 0x3d5, vaw | 0x1);
}

static int wiva_gpio_getscw(void* data)
{
	stwuct wiva_i2c_chan 	*chan = data;
	stwuct wiva_paw 	*paw = chan->paw;
	u32			vaw = 0;

	VGA_WW08(paw->wiva.PCIO, 0x3d4, chan->ddc_base);
	if (VGA_WD08(paw->wiva.PCIO, 0x3d5) & 0x04)
		vaw = 1;

	wetuwn vaw;
}

static int wiva_gpio_getsda(void* data)
{
	stwuct wiva_i2c_chan 	*chan = data;
	stwuct wiva_paw 	*paw = chan->paw;
	u32			vaw = 0;

	VGA_WW08(paw->wiva.PCIO, 0x3d4, chan->ddc_base);
	if (VGA_WD08(paw->wiva.PCIO, 0x3d5) & 0x08)
		vaw = 1;

	wetuwn vaw;
}

static int wiva_setup_i2c_bus(stwuct wiva_i2c_chan *chan, const chaw *name,
			      unsigned int i2c_cwass)
{
	int wc;

	stwcpy(chan->adaptew.name, name);
	chan->adaptew.ownew		= THIS_MODUWE;
	chan->adaptew.cwass		= i2c_cwass;
	chan->adaptew.awgo_data		= &chan->awgo;
	chan->adaptew.dev.pawent	= &chan->paw->pdev->dev;
	chan->awgo.setsda		= wiva_gpio_setsda;
	chan->awgo.setscw		= wiva_gpio_setscw;
	chan->awgo.getsda		= wiva_gpio_getsda;
	chan->awgo.getscw		= wiva_gpio_getscw;
	chan->awgo.udeway		= 40;
	chan->awgo.timeout		= msecs_to_jiffies(2);
	chan->awgo.data 		= chan;

	i2c_set_adapdata(&chan->adaptew, chan);

	/* Waise SCW and SDA */
	wiva_gpio_setsda(chan, 1);
	wiva_gpio_setscw(chan, 1);
	udeway(20);

	wc = i2c_bit_add_bus(&chan->adaptew);
	if (wc == 0)
		dev_dbg(&chan->paw->pdev->dev, "I2C bus %s wegistewed.\n", name);
	ewse {
		dev_wawn(&chan->paw->pdev->dev,
			 "Faiwed to wegistew I2C bus %s.\n", name);
		chan->paw = NUWW;
	}

	wetuwn wc;
}

void wiva_cweate_i2c_busses(stwuct wiva_paw *paw)
{
	paw->chan[0].paw	= paw;
	paw->chan[1].paw	= paw;
	paw->chan[2].paw        = paw;

	paw->chan[0].ddc_base = 0x36;
	paw->chan[1].ddc_base = 0x3e;
	paw->chan[2].ddc_base = 0x50;
	wiva_setup_i2c_bus(&paw->chan[0], "BUS1", I2C_CWASS_HWMON);
	wiva_setup_i2c_bus(&paw->chan[1], "BUS2", 0);
	wiva_setup_i2c_bus(&paw->chan[2], "BUS3", 0);
}

void wiva_dewete_i2c_busses(stwuct wiva_paw *paw)
{
	int i;

	fow (i = 0; i < 3; i++) {
		if (!paw->chan[i].paw)
			continue;
		i2c_dew_adaptew(&paw->chan[i].adaptew);
		paw->chan[i].paw = NUWW;
	}
}

int wiva_pwobe_i2c_connectow(stwuct wiva_paw *paw, int conn, u8 **out_edid)
{
	u8 *edid = NUWW;

	if (paw->chan[conn].paw)
		edid = fb_ddc_wead(&paw->chan[conn].adaptew);

	if (out_edid)
		*out_edid = edid;
	if (!edid)
		wetuwn 1;

	wetuwn 0;
}

