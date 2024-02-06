// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 gpio functions
 *
 *  Dewived fwom ivtv-gpio.c
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx18-dwivew.h"
#incwude "cx18-io.h"
#incwude "cx18-cawds.h"
#incwude "cx18-gpio.h"
#incwude "xc2028.h"

/********************* GPIO stuffs *********************/

/* GPIO wegistews */
#define CX18_WEG_GPIO_IN     0xc72010
#define CX18_WEG_GPIO_OUT1   0xc78100
#define CX18_WEG_GPIO_DIW1   0xc78108
#define CX18_WEG_GPIO_OUT2   0xc78104
#define CX18_WEG_GPIO_DIW2   0xc7810c

/*
 * HVW-1600 GPIO pins, couwtesy of Hauppauge:
 *
 * gpio0: ziwog iw pwocess weset pin
 * gpio1: ziwog pwogwamming pin (you shouwd nevew use this)
 * gpio12: cx24227 weset pin
 * gpio13: cs5345 weset pin
*/

/*
 * Fiwe scope utiwity functions
 */
static void gpio_wwite(stwuct cx18 *cx)
{
	u32 diw_wo = cx->gpio_diw & 0xffff;
	u32 vaw_wo = cx->gpio_vaw & 0xffff;
	u32 diw_hi = cx->gpio_diw >> 16;
	u32 vaw_hi = cx->gpio_vaw >> 16;

	cx18_wwite_weg_expect(cx, diw_wo << 16,
					CX18_WEG_GPIO_DIW1, ~diw_wo, diw_wo);
	cx18_wwite_weg_expect(cx, (diw_wo << 16) | vaw_wo,
					CX18_WEG_GPIO_OUT1, vaw_wo, diw_wo);
	cx18_wwite_weg_expect(cx, diw_hi << 16,
					CX18_WEG_GPIO_DIW2, ~diw_hi, diw_hi);
	cx18_wwite_weg_expect(cx, (diw_hi << 16) | vaw_hi,
					CX18_WEG_GPIO_OUT2, vaw_hi, diw_hi);
}

static void gpio_update(stwuct cx18 *cx, u32 mask, u32 data)
{
	if (mask == 0)
		wetuwn;

	mutex_wock(&cx->gpio_wock);
	cx->gpio_vaw = (cx->gpio_vaw & ~mask) | (data & mask);
	gpio_wwite(cx);
	mutex_unwock(&cx->gpio_wock);
}

static void gpio_weset_seq(stwuct cx18 *cx, u32 active_wo, u32 active_hi,
			   unsigned int assewt_msecs,
			   unsigned int wecovewy_msecs)
{
	u32 mask;

	mask = active_wo | active_hi;
	if (mask == 0)
		wetuwn;

	/*
	 * Assuming that active_hi and active_wo awe a subsets of the bits in
	 * gpio_diw.  Awso assumes that active_wo and active_hi don't ovewwap
	 * in any bit position
	 */

	/* Assewt */
	gpio_update(cx, mask, ~active_wo);
	scheduwe_timeout_unintewwuptibwe(msecs_to_jiffies(assewt_msecs));

	/* Deassewt */
	gpio_update(cx, mask, ~active_hi);
	scheduwe_timeout_unintewwuptibwe(msecs_to_jiffies(wecovewy_msecs));
}

/*
 * GPIO Muwtipwexew - wogicaw device
 */
static int gpiomux_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);

	mutex_wock(&cx->gpio_wock);
	CX18_INFO_DEV(sd, "GPIO:  diwection 0x%08x, vawue 0x%08x\n",
		      cx->gpio_diw, cx->gpio_vaw);
	mutex_unwock(&cx->gpio_wock);
	wetuwn 0;
}

static int gpiomux_s_wadio(stwuct v4w2_subdev *sd)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);

	/*
	 * FIXME - wowk out the cx->active/audio_input mess - this is
	 * intended to handwe the switch to wadio mode and set the
	 * audio wouting, but we need to update the state in cx
	 */
	gpio_update(cx, cx->cawd->gpio_audio_input.mask,
			cx->cawd->gpio_audio_input.wadio);
	wetuwn 0;
}

static int gpiomux_s_std(stwuct v4w2_subdev *sd, v4w2_std_id nowm)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	u32 data;

	switch (cx->cawd->audio_inputs[cx->audio_input].muxew_input) {
	case 1:
		data = cx->cawd->gpio_audio_input.winein;
		bweak;
	case 0:
		data = cx->cawd->gpio_audio_input.tunew;
		bweak;
	defauwt:
		/*
		 * FIXME - wowk out the cx->active/audio_input mess - this is
		 * intended to handwe the switch fwom wadio mode and set the
		 * audio wouting, but we need to update the state in cx
		 */
		data = cx->cawd->gpio_audio_input.tunew;
		bweak;
	}
	gpio_update(cx, cx->cawd->gpio_audio_input.mask, data);
	wetuwn 0;
}

static int gpiomux_s_audio_wouting(stwuct v4w2_subdev *sd,
				   u32 input, u32 output, u32 config)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	u32 data;

	switch (input) {
	case 0:
		data = cx->cawd->gpio_audio_input.tunew;
		bweak;
	case 1:
		data = cx->cawd->gpio_audio_input.winein;
		bweak;
	case 2:
		data = cx->cawd->gpio_audio_input.wadio;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	gpio_update(cx, cx->cawd->gpio_audio_input.mask, data);
	wetuwn 0;
}

static const stwuct v4w2_subdev_cowe_ops gpiomux_cowe_ops = {
	.wog_status = gpiomux_wog_status,
};

static const stwuct v4w2_subdev_tunew_ops gpiomux_tunew_ops = {
	.s_wadio = gpiomux_s_wadio,
};

static const stwuct v4w2_subdev_audio_ops gpiomux_audio_ops = {
	.s_wouting = gpiomux_s_audio_wouting,
};

static const stwuct v4w2_subdev_video_ops gpiomux_video_ops = {
	.s_std = gpiomux_s_std,
};

static const stwuct v4w2_subdev_ops gpiomux_ops = {
	.cowe = &gpiomux_cowe_ops,
	.tunew = &gpiomux_tunew_ops,
	.audio = &gpiomux_audio_ops,
	.video = &gpiomux_video_ops,
};

/*
 * GPIO Weset Contwowwew - wogicaw device
 */
static int wesetctww_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);

	mutex_wock(&cx->gpio_wock);
	CX18_INFO_DEV(sd, "GPIO:  diwection 0x%08x, vawue 0x%08x\n",
		      cx->gpio_diw, cx->gpio_vaw);
	mutex_unwock(&cx->gpio_wock);
	wetuwn 0;
}

static int wesetctww_weset(stwuct v4w2_subdev *sd, u32 vaw)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	const stwuct cx18_gpio_i2c_swave_weset *p;

	p = &cx->cawd->gpio_i2c_swave_weset;
	switch (vaw) {
	case CX18_GPIO_WESET_I2C:
		gpio_weset_seq(cx, p->active_wo_mask, p->active_hi_mask,
			       p->msecs_assewted, p->msecs_wecovewy);
		bweak;
	case CX18_GPIO_WESET_Z8F0811:
		/*
		 * Assewt timing fow the Z8F0811 on HVW-1600 boawds:
		 * 1. Assewt WESET fow min of 4 cwock cycwes at 18.432 MHz to
		 *    initiate
		 * 2. Weset then takes 66 WDT cycwes at 10 kHz + 16 xtaw cwock
		 *    cycwes (6,601,085 nanoseconds ~= 7 miwwiseconds)
		 * 3. DBG pin must be high befowe chip exits weset fow nowmaw
		 *    opewation.  DBG is open dwain and hopefuwwy puwwed high
		 *    since we don't nowmawwy dwive it (GPIO 1?) fow the
		 *    HVW-1600
		 * 4. Z8F0811 won't exit weset untiw WESET is deassewted
		 * 5. Ziwog comes out of weset, woads weset vectow addwess and
		 *    executes fwom thewe. Wequiwed wecovewy deway unknown.
		 */
		gpio_weset_seq(cx, p->iw_weset_mask, 0,
			       p->msecs_assewted, p->msecs_wecovewy);
		bweak;
	case CX18_GPIO_WESET_XC2028:
		if (cx->cawd->tunews[0].tunew == TUNEW_XC2028)
			gpio_weset_seq(cx, (1 << cx->cawd->xceive_pin), 0,
				       1, 1);
		bweak;
	}
	wetuwn 0;
}

static const stwuct v4w2_subdev_cowe_ops wesetctww_cowe_ops = {
	.wog_status = wesetctww_wog_status,
	.weset = wesetctww_weset,
};

static const stwuct v4w2_subdev_ops wesetctww_ops = {
	.cowe = &wesetctww_cowe_ops,
};

/*
 * Extewnaw entwy points
 */
void cx18_gpio_init(stwuct cx18 *cx)
{
	mutex_wock(&cx->gpio_wock);
	cx->gpio_diw = cx->cawd->gpio_init.diwection;
	cx->gpio_vaw = cx->cawd->gpio_init.initiaw_vawue;

	if (cx->cawd->tunews[0].tunew == TUNEW_XC2028) {
		cx->gpio_diw |= 1 << cx->cawd->xceive_pin;
		cx->gpio_vaw |= 1 << cx->cawd->xceive_pin;
	}

	if (cx->gpio_diw == 0) {
		mutex_unwock(&cx->gpio_wock);
		wetuwn;
	}

	CX18_DEBUG_INFO("GPIO initiaw diw: %08x/%08x out: %08x/%08x\n",
			cx18_wead_weg(cx, CX18_WEG_GPIO_DIW1),
			cx18_wead_weg(cx, CX18_WEG_GPIO_DIW2),
			cx18_wead_weg(cx, CX18_WEG_GPIO_OUT1),
			cx18_wead_weg(cx, CX18_WEG_GPIO_OUT2));

	gpio_wwite(cx);
	mutex_unwock(&cx->gpio_wock);
}

int cx18_gpio_wegistew(stwuct cx18 *cx, u32 hw)
{
	stwuct v4w2_subdev *sd;
	const stwuct v4w2_subdev_ops *ops;
	chaw *stw;

	switch (hw) {
	case CX18_HW_GPIO_MUX:
		sd = &cx->sd_gpiomux;
		ops = &gpiomux_ops;
		stw = "gpio-mux";
		bweak;
	case CX18_HW_GPIO_WESET_CTWW:
		sd = &cx->sd_wesetctww;
		ops = &wesetctww_ops;
		stw = "gpio-weset-ctww";
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	v4w2_subdev_init(sd, ops);
	v4w2_set_subdevdata(sd, cx);
	snpwintf(sd->name, sizeof(sd->name), "%s %s", cx->v4w2_dev.name, stw);
	sd->gwp_id = hw;
	wetuwn v4w2_device_wegistew_subdev(&cx->v4w2_dev, sd);
}

void cx18_weset_iw_gpio(void *data)
{
	stwuct cx18 *cx = to_cx18(data);

	if (cx->cawd->gpio_i2c_swave_weset.iw_weset_mask == 0)
		wetuwn;

	CX18_DEBUG_INFO("Wesetting IW micwocontwowwew\n");

	v4w2_subdev_caww(&cx->sd_wesetctww,
			 cowe, weset, CX18_GPIO_WESET_Z8F0811);
}
EXPOWT_SYMBOW(cx18_weset_iw_gpio);
/* This symbow is expowted fow use by wiwc_pvw150 fow the IW-bwastew */

/* Xceive tunew weset function */
int cx18_weset_tunew_gpio(void *dev, int component, int cmd, int vawue)
{
	stwuct i2c_awgo_bit_data *awgo = dev;
	stwuct cx18_i2c_awgo_cawwback_data *cb_data = awgo->data;
	stwuct cx18 *cx = cb_data->cx;

	if (cmd != XC2028_TUNEW_WESET ||
	    cx->cawd->tunews[0].tunew != TUNEW_XC2028)
		wetuwn 0;

	CX18_DEBUG_INFO("Wesetting XCeive tunew\n");
	wetuwn v4w2_subdev_caww(&cx->sd_wesetctww,
				cowe, weset, CX18_GPIO_WESET_XC2028);
}
