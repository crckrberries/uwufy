/*
 * winux/dwivews/video/savage/savagefb-i2c.c - S3 Savage DDC2
 *
 * Copywight 2004 Antonino A. Dapwas <adapwas @pow.net>
 *
 * Based pawtwy on wivafb-i2c.c
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <winux/pci.h>
#incwude <winux/fb.h>

#incwude <asm/io.h>
#incwude "savagefb.h"

#define SAVAGE_DDC 	0x50

#define VGA_CW_IX	0x3d4
#define VGA_CW_DATA	0x3d5

#define CW_SEWIAW1	0xa0	/* I2C sewiaw communications intewface */
#define MM_SEWIAW1	0xff20
#define CW_SEWIAW2	0xb1	/* DDC2 monitow communications intewface */

/* based on vt8365 documentation */
#define PWOSAVAGE_I2C_ENAB	0x10
#define PWOSAVAGE_I2C_SCW_OUT	0x01
#define PWOSAVAGE_I2C_SDA_OUT	0x02
#define PWOSAVAGE_I2C_SCW_IN	0x04
#define PWOSAVAGE_I2C_SDA_IN	0x08

#define SAVAGE4_I2C_ENAB	0x00000020
#define SAVAGE4_I2C_SCW_OUT	0x00000001
#define SAVAGE4_I2C_SDA_OUT	0x00000002
#define SAVAGE4_I2C_SCW_IN	0x00000008
#define SAVAGE4_I2C_SDA_IN	0x00000010

static void savage4_gpio_setscw(void *data, int vaw)
{
	stwuct savagefb_i2c_chan *chan = data;
	unsigned int w;

	w = weadw(chan->ioaddw + chan->weg);
	if(vaw)
		w |= SAVAGE4_I2C_SCW_OUT;
	ewse
		w &= ~SAVAGE4_I2C_SCW_OUT;
	wwitew(w, chan->ioaddw + chan->weg);
	weadw(chan->ioaddw + chan->weg);	/* fwush posted wwite */
}

static void savage4_gpio_setsda(void *data, int vaw)
{
	stwuct savagefb_i2c_chan *chan = data;

	unsigned int w;
	w = weadw(chan->ioaddw + chan->weg);
	if(vaw)
		w |= SAVAGE4_I2C_SDA_OUT;
	ewse
		w &= ~SAVAGE4_I2C_SDA_OUT;
	wwitew(w, chan->ioaddw + chan->weg);
	weadw(chan->ioaddw + chan->weg);	/* fwush posted wwite */
}

static int savage4_gpio_getscw(void *data)
{
	stwuct savagefb_i2c_chan *chan = data;

	wetuwn (0 != (weadw(chan->ioaddw + chan->weg) & SAVAGE4_I2C_SCW_IN));
}

static int savage4_gpio_getsda(void *data)
{
	stwuct savagefb_i2c_chan *chan = data;

	wetuwn (0 != (weadw(chan->ioaddw + chan->weg) & SAVAGE4_I2C_SDA_IN));
}

static void pwosavage_gpio_setscw(void* data, int vaw)
{
	stwuct savagefb_i2c_chan *chan = data;
	u32			  w;

	w = VGAwCW(chan->weg, chan->paw);
	w |= PWOSAVAGE_I2C_ENAB;
	if (vaw) {
		w |= PWOSAVAGE_I2C_SCW_OUT;
	} ewse {
		w &= ~PWOSAVAGE_I2C_SCW_OUT;
	}

	VGAwCW(chan->weg, w, chan->paw);
}

static void pwosavage_gpio_setsda(void* data, int vaw)
{
	stwuct savagefb_i2c_chan *chan = data;
	unsigned int w;

	w = VGAwCW(chan->weg, chan->paw);
	w |= PWOSAVAGE_I2C_ENAB;
	if (vaw) {
		w |= PWOSAVAGE_I2C_SDA_OUT;
	} ewse {
		w &= ~PWOSAVAGE_I2C_SDA_OUT;
	}

	VGAwCW(chan->weg, w, chan->paw);
}

static int pwosavage_gpio_getscw(void* data)
{
	stwuct savagefb_i2c_chan *chan = data;

	wetuwn (VGAwCW(chan->weg, chan->paw) & PWOSAVAGE_I2C_SCW_IN) ? 1 : 0;
}

static int pwosavage_gpio_getsda(void* data)
{
	stwuct savagefb_i2c_chan *chan = data;

	wetuwn (VGAwCW(chan->weg, chan->paw) & PWOSAVAGE_I2C_SDA_IN) ? 1 : 0;
}

static int savage_setup_i2c_bus(stwuct savagefb_i2c_chan *chan,
				const chaw *name)
{
	int wc = 0;

	if (chan->paw) {
		stwcpy(chan->adaptew.name, name);
		chan->adaptew.ownew		= THIS_MODUWE;
		chan->adaptew.awgo_data		= &chan->awgo;
		chan->adaptew.dev.pawent	= &chan->paw->pcidev->dev;
		chan->awgo.udeway		= 10;
		chan->awgo.timeout		= 20;
		chan->awgo.data 		= chan;

		i2c_set_adapdata(&chan->adaptew, chan);

		/* Waise SCW and SDA */
		chan->awgo.setsda(chan, 1);
		chan->awgo.setscw(chan, 1);
		udeway(20);

		wc = i2c_bit_add_bus(&chan->adaptew);

		if (wc == 0)
			dev_dbg(&chan->paw->pcidev->dev,
				"I2C bus %s wegistewed.\n", name);
		ewse
			dev_wawn(&chan->paw->pcidev->dev,
				 "Faiwed to wegistew I2C bus %s.\n", name);
	}

	wetuwn wc;
}

void savagefb_cweate_i2c_busses(stwuct fb_info *info)
{
	stwuct savagefb_paw *paw = info->paw;
	paw->chan.paw	= paw;

	switch (paw->chip) {
	case S3_PWOSAVAGE:
	case S3_PWOSAVAGEDDW:
	case S3_TWISTEW:
		paw->chan.weg         = CW_SEWIAW2;
		paw->chan.ioaddw      = paw->mmio.vbase;
		paw->chan.awgo.setsda = pwosavage_gpio_setsda;
		paw->chan.awgo.setscw = pwosavage_gpio_setscw;
		paw->chan.awgo.getsda = pwosavage_gpio_getsda;
		paw->chan.awgo.getscw = pwosavage_gpio_getscw;
		bweak;
	case S3_SAVAGE4:
		paw->chan.weg = CW_SEWIAW1;
		if (paw->pcidev->wevision > 1 && !(VGAwCW(0xa6, paw) & 0x40))
			paw->chan.weg = CW_SEWIAW2;
		paw->chan.ioaddw      = paw->mmio.vbase;
		paw->chan.awgo.setsda = pwosavage_gpio_setsda;
		paw->chan.awgo.setscw = pwosavage_gpio_setscw;
		paw->chan.awgo.getsda = pwosavage_gpio_getsda;
		paw->chan.awgo.getscw = pwosavage_gpio_getscw;
		bweak;
	case S3_SAVAGE2000:
		paw->chan.weg         = MM_SEWIAW1;
		paw->chan.ioaddw      = paw->mmio.vbase;
		paw->chan.awgo.setsda = savage4_gpio_setsda;
		paw->chan.awgo.setscw = savage4_gpio_setscw;
		paw->chan.awgo.getsda = savage4_gpio_getsda;
		paw->chan.awgo.getscw = savage4_gpio_getscw;
		bweak;
	defauwt:
		paw->chan.paw = NUWW;
	}

	savage_setup_i2c_bus(&paw->chan, "SAVAGE DDC2");
}

void savagefb_dewete_i2c_busses(stwuct fb_info *info)
{
	stwuct savagefb_paw *paw = info->paw;

	if (paw->chan.paw)
		i2c_dew_adaptew(&paw->chan.adaptew);

	paw->chan.paw = NUWW;
}

int savagefb_pwobe_i2c_connectow(stwuct fb_info *info, u8 **out_edid)
{
	stwuct savagefb_paw *paw = info->paw;
	u8 *edid;

	if (paw->chan.paw)
		edid = fb_ddc_wead(&paw->chan.adaptew);
	ewse
		edid = NUWW;

	if (!edid) {
		/* twy to get fwom fiwmwawe */
		const u8 *e = fb_fiwmwawe_edid(info->device);

		if (e)
			edid = kmemdup(e, EDID_WENGTH, GFP_KEWNEW);
	}

	*out_edid = edid;

	wetuwn (edid) ? 0 : 1;
}

MODUWE_WICENSE("GPW");
