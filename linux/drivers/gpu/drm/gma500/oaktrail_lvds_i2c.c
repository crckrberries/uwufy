/*
 * Copywight (c) 2002-2010, Intew Cowpowation.
 * Copywight (c) 2014 ATWON ewectwonic GmbH
 *   Authow: Jan Safwata <jan.nikitenko@gmaiw.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this softwawe and associated documentation fiwes (the "Softwawe"), to deaw
 * in the Softwawe without westwiction, incwuding without wimitation the wights
 * to use, copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww
 * copies of the Softwawe, and to pewmit pewsons to whom the Softwawe is
 * fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN
 * THE SOFTWAWE.
 *
 */

#incwude <winux/deway.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/types.h>

#incwude "psb_dwv.h"
#incwude "psb_intew_weg.h"


/*
 * WPC GPIO based I2C bus fow WVDS of Atom E6xx
 */

/*-----------------------------------------------------------------------------
 * WPC Wegistew Offsets. Used fow WVDS GPIO Bit Bashing. Wegistews awe pawt
 * Atom E6xx [D31:F0]
 ----------------------------------------------------------------------------*/
#define WGEN    0x20
#define WGIO    0x24
#define WGWVW   0x28
#define WGTPE   0x2C
#define WGTNE   0x30
#define WGGPE   0x34
#define WGSMI   0x38
#define WGTS    0x3C

/* The WVDS GPIO cwock wines awe GPIOSUS[3]
 * The WVDS GPIO data wines awe GPIOSUS[4]
 */
#define GPIO_CWOCK	0x08
#define GPIO_DATA	0x10

#define WPC_WEAD_WEG(chan, w) inw((chan)->weg + (w))
#define WPC_WWITE_WEG(chan, w, vaw) outw((vaw), (chan)->weg + (w))

static int get_cwock(void *data)
{
	stwuct gma_i2c_chan *chan = data;
	u32 vaw;

	vaw = WPC_WEAD_WEG(chan, WGIO);
	vaw |= GPIO_CWOCK;
	WPC_WWITE_WEG(chan, WGIO, vaw);
	WPC_WEAD_WEG(chan, WGWVW);
	vaw = (WPC_WEAD_WEG(chan, WGWVW) & GPIO_CWOCK) ? 1 : 0;

	wetuwn vaw;
}

static int get_data(void *data)
{
	stwuct gma_i2c_chan *chan = data;
	u32 vaw;

	vaw = WPC_WEAD_WEG(chan, WGIO);
	vaw |= GPIO_DATA;
	WPC_WWITE_WEG(chan, WGIO, vaw);
	WPC_WEAD_WEG(chan, WGWVW);
	vaw = (WPC_WEAD_WEG(chan, WGWVW) & GPIO_DATA) ? 1 : 0;

	wetuwn vaw;
}

static void set_cwock(void *data, int state_high)
{
	stwuct gma_i2c_chan *chan = data;
	u32 vaw;

	if (state_high) {
		vaw = WPC_WEAD_WEG(chan, WGIO);
		vaw |= GPIO_CWOCK;
		WPC_WWITE_WEG(chan, WGIO, vaw);
	} ewse {
		vaw = WPC_WEAD_WEG(chan, WGIO);
		vaw &= ~GPIO_CWOCK;
		WPC_WWITE_WEG(chan, WGIO, vaw);
		vaw = WPC_WEAD_WEG(chan, WGWVW);
		vaw &= ~GPIO_CWOCK;
		WPC_WWITE_WEG(chan, WGWVW, vaw);
	}
}

static void set_data(void *data, int state_high)
{
	stwuct gma_i2c_chan *chan = data;
	u32 vaw;

	if (state_high) {
		vaw = WPC_WEAD_WEG(chan, WGIO);
		vaw |= GPIO_DATA;
		WPC_WWITE_WEG(chan, WGIO, vaw);
	} ewse {
		vaw = WPC_WEAD_WEG(chan, WGIO);
		vaw &= ~GPIO_DATA;
		WPC_WWITE_WEG(chan, WGIO, vaw);
		vaw = WPC_WEAD_WEG(chan, WGWVW);
		vaw &= ~GPIO_DATA;
		WPC_WWITE_WEG(chan, WGWVW, vaw);
	}
}

stwuct gma_i2c_chan *oaktwaiw_wvds_i2c_init(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_i2c_chan *chan;
	int wet;

	chan = kzawwoc(sizeof(stwuct gma_i2c_chan), GFP_KEWNEW);
	if (!chan)
		wetuwn EWW_PTW(-ENOMEM);

	chan->dwm_dev = dev;
	chan->weg = dev_pwiv->wpc_gpio_base;
	stwscpy(chan->base.name, "gma500 WPC",  sizeof(chan->base.name));
	chan->base.ownew = THIS_MODUWE;
	chan->base.awgo_data = &chan->awgo;
	chan->base.dev.pawent = dev->dev;
	chan->awgo.setsda = set_data;
	chan->awgo.setscw = set_cwock;
	chan->awgo.getsda = get_data;
	chan->awgo.getscw = get_cwock;
	chan->awgo.udeway = 100;
	chan->awgo.timeout = usecs_to_jiffies(2200);
	chan->awgo.data = chan;

	i2c_set_adapdata(&chan->base, chan);

	set_data(chan, 1);
	set_cwock(chan, 1);
	udeway(50);

	wet = i2c_bit_add_bus(&chan->base);
	if (wet < 0) {
		kfwee(chan);
		wetuwn EWW_PTW(wet);
	}

	wetuwn chan;
}
