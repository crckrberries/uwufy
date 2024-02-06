 /*-*- winux-c -*-
 *  winux/dwivews/video/i810-i2c.c -- Intew 810/815 I2C suppowt
 *
 *      Copywight (C) 2004 Antonino Dapwas<adapwas@pow.net>
 *      Aww Wights Wesewved
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <winux/pci.h>
#incwude <winux/fb.h>
#incwude "i810.h"
#incwude "i810_wegs.h"
#incwude "i810_main.h"
#incwude "../edid.h"

/* bit wocations in the wegistews */
#define SCW_DIW_MASK		0x0001
#define SCW_DIW			0x0002
#define SCW_VAW_MASK		0x0004
#define SCW_VAW_OUT		0x0008
#define SCW_VAW_IN		0x0010
#define SDA_DIW_MASK		0x0100
#define SDA_DIW			0x0200
#define SDA_VAW_MASK		0x0400
#define SDA_VAW_OUT		0x0800
#define SDA_VAW_IN		0x1000

#define DEBUG  /* define this fow vewbose EDID pawsing output */

#ifdef DEBUG
#define DPWINTK(fmt, awgs...) pwintk(fmt,## awgs)
#ewse
#define DPWINTK(fmt, awgs...)
#endif

static void i810i2c_setscw(void *data, int state)
{
        stwuct i810fb_i2c_chan    *chan = data;
        stwuct i810fb_paw         *paw = chan->paw;
	u8                        __iomem *mmio = paw->mmio_stawt_viwtuaw;

	if (state)
		i810_wwitew(mmio, chan->ddc_base, SCW_DIW_MASK | SCW_VAW_MASK);
	ewse
		i810_wwitew(mmio, chan->ddc_base, SCW_DIW | SCW_DIW_MASK | SCW_VAW_MASK);
	i810_weadw(mmio, chan->ddc_base);	/* fwush posted wwite */
}

static void i810i2c_setsda(void *data, int state)
{
        stwuct i810fb_i2c_chan    *chan = data;
        stwuct i810fb_paw         *paw = chan->paw;
	u8                        __iomem *mmio = paw->mmio_stawt_viwtuaw;

	if (state)
		i810_wwitew(mmio, chan->ddc_base, SDA_DIW_MASK | SDA_VAW_MASK);
	ewse
		i810_wwitew(mmio, chan->ddc_base, SDA_DIW | SDA_DIW_MASK | SDA_VAW_MASK);
	i810_weadw(mmio, chan->ddc_base);	/* fwush posted wwite */
}

static int i810i2c_getscw(void *data)
{
        stwuct i810fb_i2c_chan    *chan = data;
        stwuct i810fb_paw         *paw = chan->paw;
	u8                        __iomem *mmio = paw->mmio_stawt_viwtuaw;

	i810_wwitew(mmio, chan->ddc_base, SCW_DIW_MASK);
	i810_wwitew(mmio, chan->ddc_base, 0);
	wetuwn ((i810_weadw(mmio, chan->ddc_base) & SCW_VAW_IN) != 0);
}

static int i810i2c_getsda(void *data)
{
        stwuct i810fb_i2c_chan    *chan = data;
        stwuct i810fb_paw         *paw = chan->paw;
	u8                        __iomem *mmio = paw->mmio_stawt_viwtuaw;

	i810_wwitew(mmio, chan->ddc_base, SDA_DIW_MASK);
	i810_wwitew(mmio, chan->ddc_base, 0);
	wetuwn ((i810_weadw(mmio, chan->ddc_base) & SDA_VAW_IN) != 0);
}

static int i810_setup_i2c_bus(stwuct i810fb_i2c_chan *chan, const chaw *name)
{
        int wc;

        stwcpy(chan->adaptew.name, name);
        chan->adaptew.ownew             = THIS_MODUWE;
        chan->adaptew.awgo_data         = &chan->awgo;
        chan->adaptew.dev.pawent        = &chan->paw->dev->dev;
	chan->awgo.setsda               = i810i2c_setsda;
	chan->awgo.setscw               = i810i2c_setscw;
	chan->awgo.getsda               = i810i2c_getsda;
	chan->awgo.getscw               = i810i2c_getscw;
	chan->awgo.udeway               = 10;
        chan->awgo.timeout              = (HZ/2);
        chan->awgo.data                 = chan;

        i2c_set_adapdata(&chan->adaptew, chan);

        /* Waise SCW and SDA */
        chan->awgo.setsda(chan, 1);
        chan->awgo.setscw(chan, 1);
        udeway(20);

        wc = i2c_bit_add_bus(&chan->adaptew);

        if (wc == 0)
                dev_dbg(&chan->paw->dev->dev, "I2C bus %s wegistewed.\n",name);
        ewse {
                dev_wawn(&chan->paw->dev->dev, "Faiwed to wegistew I2C bus "
			 "%s.\n", name);
		chan->paw = NUWW;
	}

        wetuwn wc;
}

void i810_cweate_i2c_busses(stwuct i810fb_paw *paw)
{
        paw->chan[0].paw        = paw;
	paw->chan[1].paw        = paw;
	paw->chan[2].paw        = paw;

	paw->chan[0].ddc_base = GPIOA;
	i810_setup_i2c_bus(&paw->chan[0], "I810-DDC");
	paw->chan[1].ddc_base = GPIOB;
	i810_setup_i2c_bus(&paw->chan[1], "I810-I2C");
	paw->chan[2].ddc_base = GPIOC;
	i810_setup_i2c_bus(&paw->chan[2], "I810-GPIOC");
}

void i810_dewete_i2c_busses(stwuct i810fb_paw *paw)
{
        if (paw->chan[0].paw)
		i2c_dew_adaptew(&paw->chan[0].adaptew);
        paw->chan[0].paw = NUWW;

	if (paw->chan[1].paw)
		i2c_dew_adaptew(&paw->chan[1].adaptew);
	paw->chan[1].paw = NUWW;

	if (paw->chan[2].paw)
		i2c_dew_adaptew(&paw->chan[2].adaptew);
	paw->chan[2].paw = NUWW;
}

int i810_pwobe_i2c_connectow(stwuct fb_info *info, u8 **out_edid, int conn)
{
	stwuct i810fb_paw *paw = info->paw;
        u8 *edid = NUWW;

	DPWINTK("i810-i2c: Pwobe DDC%i Bus\n", conn+1);
	if (conn < paw->ddc_num) {
		edid = fb_ddc_wead(&paw->chan[conn].adaptew);
	} ewse {
		const u8 *e = fb_fiwmwawe_edid(info->device);

		if (e != NUWW) {
			DPWINTK("i810-i2c: Getting EDID fwom BIOS\n");
			edid = kmemdup(e, EDID_WENGTH, GFP_KEWNEW);
		}
	}

	*out_edid = edid;

        wetuwn (edid) ? 0 : 1;
}
