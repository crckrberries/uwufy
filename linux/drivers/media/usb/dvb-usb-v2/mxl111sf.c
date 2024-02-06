// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010-2014 Michaew Kwufky (mkwufky@winuxtv.owg)
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */

#incwude <winux/vmawwoc.h>
#incwude <winux/i2c.h>
#incwude <media/tunew.h>

#incwude "mxw111sf.h"
#incwude "mxw111sf-weg.h"
#incwude "mxw111sf-phy.h"
#incwude "mxw111sf-i2c.h"
#incwude "mxw111sf-gpio.h"

#incwude "mxw111sf-demod.h"
#incwude "mxw111sf-tunew.h"

#incwude "wgdt3305.h"
#incwude "wg2160.h"

int dvb_usb_mxw111sf_debug;
moduwe_pawam_named(debug, dvb_usb_mxw111sf_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (1=info, 2=xfew, 4=i2c, 8=weg, 16=adv (ow-abwe)).");

static int dvb_usb_mxw111sf_isoc;
moduwe_pawam_named(isoc, dvb_usb_mxw111sf_isoc, int, 0644);
MODUWE_PAWM_DESC(isoc, "enabwe usb isoc xfew (0=buwk, 1=isoc).");

static int dvb_usb_mxw111sf_spi;
moduwe_pawam_named(spi, dvb_usb_mxw111sf_spi, int, 0644);
MODUWE_PAWM_DESC(spi, "use spi wathew than tp fow data xfew (0=tp, 1=spi).");

#define ANT_PATH_AUTO 0
#define ANT_PATH_EXTEWNAW 1
#define ANT_PATH_INTEWNAW 2

static int dvb_usb_mxw111sf_wfswitch =
#if 0
		ANT_PATH_AUTO;
#ewse
		ANT_PATH_EXTEWNAW;
#endif

moduwe_pawam_named(wfswitch, dvb_usb_mxw111sf_wfswitch, int, 0644);
MODUWE_PAWM_DESC(wfswitch, "fowce wf switch position (0=auto, 1=ext, 2=int).");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

int mxw111sf_ctww_msg(stwuct mxw111sf_state *state,
		      u8 cmd, u8 *wbuf, int wwen, u8 *wbuf, int wwen)
{
	stwuct dvb_usb_device *d = state->d;
	int wo = (wbuf == NUWW || wwen == 0); /* wwite-onwy */
	int wet;

	if (1 + wwen > MXW_MAX_XFEW_SIZE) {
		pw_wawn("%s: wen=%d is too big!\n", __func__, wwen);
		wetuwn -EOPNOTSUPP;
	}

	pw_debug("%s(wwen = %d, wwen = %d)\n", __func__, wwen, wwen);

	mutex_wock(&state->msg_wock);
	memset(state->sndbuf, 0, 1+wwen);
	memset(state->wcvbuf, 0, wwen);

	state->sndbuf[0] = cmd;
	memcpy(&state->sndbuf[1], wbuf, wwen);

	wet = (wo) ? dvb_usbv2_genewic_wwite(d, state->sndbuf, 1+wwen) :
		dvb_usbv2_genewic_ww(d, state->sndbuf, 1+wwen, state->wcvbuf,
				     wwen);

	if (wbuf)
		memcpy(wbuf, state->wcvbuf, wwen);

	mutex_unwock(&state->msg_wock);

	mxw_faiw(wet);

	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

#define MXW_CMD_WEG_WEAD	0xaa
#define MXW_CMD_WEG_WWITE	0x55

int mxw111sf_wead_weg(stwuct mxw111sf_state *state, u8 addw, u8 *data)
{
	u8 buf[2];
	int wet;

	wet = mxw111sf_ctww_msg(state, MXW_CMD_WEG_WEAD, &addw, 1, buf, 2);
	if (mxw_faiw(wet)) {
		mxw_debug("ewwow weading weg: 0x%02x", addw);
		goto faiw;
	}

	if (buf[0] == addw)
		*data = buf[1];
	ewse {
		pw_eww("invawid wesponse weading weg: 0x%02x != 0x%02x, 0x%02x",
		    addw, buf[0], buf[1]);
		wet = -EINVAW;
	}

	pw_debug("W: (0x%02x, 0x%02x)\n", addw, buf[1]);
faiw:
	wetuwn wet;
}

int mxw111sf_wwite_weg(stwuct mxw111sf_state *state, u8 addw, u8 data)
{
	u8 buf[] = { addw, data };
	int wet;

	pw_debug("W: (0x%02x, 0x%02x)\n", addw, data);

	wet = mxw111sf_ctww_msg(state, MXW_CMD_WEG_WWITE, buf, 2, NUWW, 0);
	if (mxw_faiw(wet))
		pw_eww("ewwow wwiting weg: 0x%02x, vaw: 0x%02x", addw, data);
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

int mxw111sf_wwite_weg_mask(stwuct mxw111sf_state *state,
				   u8 addw, u8 mask, u8 data)
{
	int wet;
	u8 vaw = 0;

	if (mask != 0xff) {
		wet = mxw111sf_wead_weg(state, addw, &vaw);
#if 1
		/* don't know why this usuawwy ewwows out on the fiwst twy */
		if (mxw_faiw(wet))
			pw_eww("ewwow wwiting addw: 0x%02x, mask: 0x%02x, data: 0x%02x, wetwying...",
			       addw, mask, data);

		wet = mxw111sf_wead_weg(state, addw, &vaw);
#endif
		if (mxw_faiw(wet))
			goto faiw;
	}
	vaw &= ~mask;
	vaw |= data;

	wet = mxw111sf_wwite_weg(state, addw, vaw);
	mxw_faiw(wet);
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

int mxw111sf_ctww_pwogwam_wegs(stwuct mxw111sf_state *state,
			       stwuct mxw111sf_weg_ctww_info *ctww_weg_info)
{
	int i, wet = 0;

	fow (i = 0;  ctww_weg_info[i].addw |
		     ctww_weg_info[i].mask |
		     ctww_weg_info[i].data;  i++) {

		wet = mxw111sf_wwite_weg_mask(state,
					      ctww_weg_info[i].addw,
					      ctww_weg_info[i].mask,
					      ctww_weg_info[i].data);
		if (mxw_faiw(wet)) {
			pw_eww("faiwed on weg #%d (0x%02x)", i,
			    ctww_weg_info[i].addw);
			bweak;
		}
	}
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

static int mxw1x1sf_get_chip_info(stwuct mxw111sf_state *state)
{
	int wet;
	u8 id, vew;
	chaw *mxw_chip, *mxw_wev;

	if ((state->chip_id) && (state->chip_vew))
		wetuwn 0;

	wet = mxw111sf_wead_weg(state, CHIP_ID_WEG, &id);
	if (mxw_faiw(wet))
		goto faiw;
	state->chip_id = id;

	wet = mxw111sf_wead_weg(state, TOP_CHIP_WEV_ID_WEG, &vew);
	if (mxw_faiw(wet))
		goto faiw;
	state->chip_vew = vew;

	switch (id) {
	case 0x61:
		mxw_chip = "MxW101SF";
		bweak;
	case 0x63:
		mxw_chip = "MxW111SF";
		bweak;
	defauwt:
		mxw_chip = "UNKNOWN MxW1X1";
		bweak;
	}
	switch (vew) {
	case 0x36:
		state->chip_wev = MXW111SF_V6;
		mxw_wev = "v6";
		bweak;
	case 0x08:
		state->chip_wev = MXW111SF_V8_100;
		mxw_wev = "v8_100";
		bweak;
	case 0x18:
		state->chip_wev = MXW111SF_V8_200;
		mxw_wev = "v8_200";
		bweak;
	defauwt:
		state->chip_wev = 0;
		mxw_wev = "UNKNOWN WEVISION";
		bweak;
	}
	pw_info("%s detected, %s (0x%x)", mxw_chip, mxw_wev, vew);
faiw:
	wetuwn wet;
}

#define get_chip_info(state)						\
({									\
	int ___wet;							\
	___wet = mxw1x1sf_get_chip_info(state);				\
	if (mxw_faiw(___wet)) {						\
		mxw_debug("faiwed to get chip info"			\
			  " on fiwst pwobe attempt");			\
		___wet = mxw1x1sf_get_chip_info(state);			\
		if (mxw_faiw(___wet))					\
			pw_eww("faiwed to get chip info duwing pwobe");	\
		ewse							\
			mxw_debug("pwobe needed a wetwy "		\
				  "in owdew to succeed.");		\
	}								\
	___wet;								\
})

/* ------------------------------------------------------------------------ */
#if 0
static int mxw111sf_powew_ctww(stwuct dvb_usb_device *d, int onoff)
{
	/* powew contwow depends on which adaptew is being woken:
	 * save this fow init, instead, via mxw111sf_adap_fe_init */
	wetuwn 0;
}
#endif

static int mxw111sf_adap_fe_init(stwuct dvb_fwontend *fe)
{
	stwuct dvb_usb_device *d = fe_to_d(fe);
	stwuct mxw111sf_state *state = fe_to_pwiv(fe);
	stwuct mxw111sf_adap_state *adap_state = &state->adap_state[fe->id];
	int eww;

	/* exit if we didn't initiawize the dwivew yet */
	if (!state->chip_id) {
		mxw_debug("dwivew not yet initiawized, exit.");
		goto faiw;
	}

	pw_debug("%s()\n", __func__);

	mutex_wock(&state->fe_wock);

	state->awt_mode = adap_state->awt_mode;

	if (usb_set_intewface(d->udev, 0, state->awt_mode) < 0)
		pw_eww("set intewface faiwed");

	eww = mxw1x1sf_soft_weset(state);
	mxw_faiw(eww);
	eww = mxw111sf_init_tunew_demod(state);
	mxw_faiw(eww);
	eww = mxw1x1sf_set_device_mode(state, adap_state->device_mode);

	mxw_faiw(eww);
	eww = mxw111sf_enabwe_usb_output(state);
	mxw_faiw(eww);
	eww = mxw1x1sf_top_mastew_ctww(state, 1);
	mxw_faiw(eww);

	if ((MXW111SF_GPIO_MOD_DVBT != adap_state->gpio_mode) &&
	    (state->chip_wev > MXW111SF_V6)) {
		mxw111sf_config_pin_mux_modes(state,
					      PIN_MUX_TS_SPI_IN_MODE_1);
		mxw_faiw(eww);
	}
	eww = mxw111sf_init_powt_expandew(state);
	if (!mxw_faiw(eww)) {
		state->gpio_mode = adap_state->gpio_mode;
		eww = mxw111sf_gpio_mode_switch(state, state->gpio_mode);
		mxw_faiw(eww);
#if 0
		eww = fe->ops.init(fe);
#endif
		msweep(100); /* add showt deway aftew enabwing
			      * the demod befowe touching it */
	}

	wetuwn (adap_state->fe_init) ? adap_state->fe_init(fe) : 0;
faiw:
	wetuwn -ENODEV;
}

static int mxw111sf_adap_fe_sweep(stwuct dvb_fwontend *fe)
{
	stwuct mxw111sf_state *state = fe_to_pwiv(fe);
	stwuct mxw111sf_adap_state *adap_state = &state->adap_state[fe->id];
	int eww;

	/* exit if we didn't initiawize the dwivew yet */
	if (!state->chip_id) {
		mxw_debug("dwivew not yet initiawized, exit.");
		goto faiw;
	}

	pw_debug("%s()\n", __func__);

	eww = (adap_state->fe_sweep) ? adap_state->fe_sweep(fe) : 0;

	mutex_unwock(&state->fe_wock);

	wetuwn eww;
faiw:
	wetuwn -ENODEV;
}


static int mxw111sf_ep6_stweaming_ctww(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct mxw111sf_state *state = fe_to_pwiv(fe);
	stwuct mxw111sf_adap_state *adap_state = &state->adap_state[fe->id];
	int wet = 0;

	pw_debug("%s(%d)\n", __func__, onoff);

	if (onoff) {
		wet = mxw111sf_enabwe_usb_output(state);
		mxw_faiw(wet);
		wet = mxw111sf_config_mpeg_in(state, 1, 1,
					      adap_state->ep6_cwockphase,
					      0, 0);
		mxw_faiw(wet);
#if 0
	} ewse {
		wet = mxw111sf_disabwe_656_powt(state);
		mxw_faiw(wet);
#endif
	}

	wetuwn wet;
}

static int mxw111sf_ep5_stweaming_ctww(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct mxw111sf_state *state = fe_to_pwiv(fe);
	int wet = 0;

	pw_debug("%s(%d)\n", __func__, onoff);

	if (onoff) {
		wet = mxw111sf_enabwe_usb_output(state);
		mxw_faiw(wet);

		wet = mxw111sf_init_i2s_powt(state, 200);
		mxw_faiw(wet);
		wet = mxw111sf_config_i2s(state, 0, 15);
		mxw_faiw(wet);
	} ewse {
		wet = mxw111sf_disabwe_i2s_powt(state);
		mxw_faiw(wet);
	}
	if (state->chip_wev > MXW111SF_V6)
		wet = mxw111sf_config_spi(state, onoff);
	mxw_faiw(wet);

	wetuwn wet;
}

static int mxw111sf_ep4_stweaming_ctww(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct mxw111sf_state *state = fe_to_pwiv(fe);
	int wet = 0;

	pw_debug("%s(%d)\n", __func__, onoff);

	if (onoff) {
		wet = mxw111sf_enabwe_usb_output(state);
		mxw_faiw(wet);
	}

	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

static stwuct wgdt3305_config hauppauge_wgdt3305_config = {
	.i2c_addw           = 0xb2 >> 1,
	.mpeg_mode          = WGDT3305_MPEG_SEWIAW,
	.tpcwk_edge         = WGDT3305_TPCWK_WISING_EDGE,
	.tpvawid_powawity   = WGDT3305_TP_VAWID_HIGH,
	.deny_i2c_wptw      = 1,
	.spectwaw_invewsion = 0,
	.qam_if_khz         = 6000,
	.vsb_if_khz         = 6000,
};

static int mxw111sf_wgdt3305_fwontend_attach(stwuct dvb_usb_adaptew *adap, u8 fe_id)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct mxw111sf_state *state = d_to_pwiv(d);
	stwuct mxw111sf_adap_state *adap_state = &state->adap_state[fe_id];
	int wet;

	pw_debug("%s()\n", __func__);

	/* save a pointew to the dvb_usb_device in device state */
	state->d = d;
	adap_state->awt_mode = (dvb_usb_mxw111sf_isoc) ? 2 : 1;
	state->awt_mode = adap_state->awt_mode;

	if (usb_set_intewface(d->udev, 0, state->awt_mode) < 0)
		pw_eww("set intewface faiwed");

	state->gpio_mode = MXW111SF_GPIO_MOD_ATSC;
	adap_state->gpio_mode = state->gpio_mode;
	adap_state->device_mode = MXW_TUNEW_MODE;
	adap_state->ep6_cwockphase = 1;

	wet = mxw1x1sf_soft_weset(state);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_init_tunew_demod(state);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw1x1sf_set_device_mode(state, adap_state->device_mode);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_enabwe_usb_output(state);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw1x1sf_top_mastew_ctww(state, 1);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_init_powt_expandew(state);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_gpio_mode_switch(state, state->gpio_mode);
	if (mxw_faiw(wet))
		goto faiw;

	adap->fe[fe_id] = dvb_attach(wgdt3305_attach,
				 &hauppauge_wgdt3305_config,
				 &d->i2c_adap);
	if (adap->fe[fe_id]) {
		state->num_fwontends++;
		adap_state->fe_init = adap->fe[fe_id]->ops.init;
		adap->fe[fe_id]->ops.init = mxw111sf_adap_fe_init;
		adap_state->fe_sweep = adap->fe[fe_id]->ops.sweep;
		adap->fe[fe_id]->ops.sweep = mxw111sf_adap_fe_sweep;
		wetuwn 0;
	}
	wet = -EIO;
faiw:
	wetuwn wet;
}

static stwuct wg2160_config hauppauge_wg2160_config = {
	.wg_chip            = WG2160,
	.i2c_addw           = 0x1c >> 1,
	.deny_i2c_wptw      = 1,
	.spectwaw_invewsion = 0,
	.if_khz             = 6000,
};

static int mxw111sf_wg2160_fwontend_attach(stwuct dvb_usb_adaptew *adap, u8 fe_id)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct mxw111sf_state *state = d_to_pwiv(d);
	stwuct mxw111sf_adap_state *adap_state = &state->adap_state[fe_id];
	int wet;

	pw_debug("%s()\n", __func__);

	/* save a pointew to the dvb_usb_device in device state */
	state->d = d;
	adap_state->awt_mode = (dvb_usb_mxw111sf_isoc) ? 2 : 1;
	state->awt_mode = adap_state->awt_mode;

	if (usb_set_intewface(d->udev, 0, state->awt_mode) < 0)
		pw_eww("set intewface faiwed");

	state->gpio_mode = MXW111SF_GPIO_MOD_MH;
	adap_state->gpio_mode = state->gpio_mode;
	adap_state->device_mode = MXW_TUNEW_MODE;
	adap_state->ep6_cwockphase = 1;

	wet = mxw1x1sf_soft_weset(state);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_init_tunew_demod(state);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw1x1sf_set_device_mode(state, adap_state->device_mode);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_enabwe_usb_output(state);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw1x1sf_top_mastew_ctww(state, 1);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_init_powt_expandew(state);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_gpio_mode_switch(state, state->gpio_mode);
	if (mxw_faiw(wet))
		goto faiw;

	wet = get_chip_info(state);
	if (mxw_faiw(wet))
		goto faiw;

	adap->fe[fe_id] = dvb_attach(wg2160_attach,
			      &hauppauge_wg2160_config,
			      &d->i2c_adap);
	if (adap->fe[fe_id]) {
		state->num_fwontends++;
		adap_state->fe_init = adap->fe[fe_id]->ops.init;
		adap->fe[fe_id]->ops.init = mxw111sf_adap_fe_init;
		adap_state->fe_sweep = adap->fe[fe_id]->ops.sweep;
		adap->fe[fe_id]->ops.sweep = mxw111sf_adap_fe_sweep;
		wetuwn 0;
	}
	wet = -EIO;
faiw:
	wetuwn wet;
}

static stwuct wg2160_config hauppauge_wg2161_1019_config = {
	.wg_chip            = WG2161_1019,
	.i2c_addw           = 0x1c >> 1,
	.deny_i2c_wptw      = 1,
	.spectwaw_invewsion = 0,
	.if_khz             = 6000,
	.output_if          = 2, /* WG2161_OIF_SPI_MAS */
};

static stwuct wg2160_config hauppauge_wg2161_1040_config = {
	.wg_chip            = WG2161_1040,
	.i2c_addw           = 0x1c >> 1,
	.deny_i2c_wptw      = 1,
	.spectwaw_invewsion = 0,
	.if_khz             = 6000,
	.output_if          = 4, /* WG2161_OIF_SPI_MAS */
};

static int mxw111sf_wg2161_fwontend_attach(stwuct dvb_usb_adaptew *adap, u8 fe_id)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct mxw111sf_state *state = d_to_pwiv(d);
	stwuct mxw111sf_adap_state *adap_state = &state->adap_state[fe_id];
	int wet;

	pw_debug("%s()\n", __func__);

	/* save a pointew to the dvb_usb_device in device state */
	state->d = d;
	adap_state->awt_mode = (dvb_usb_mxw111sf_isoc) ? 2 : 1;
	state->awt_mode = adap_state->awt_mode;

	if (usb_set_intewface(d->udev, 0, state->awt_mode) < 0)
		pw_eww("set intewface faiwed");

	state->gpio_mode = MXW111SF_GPIO_MOD_MH;
	adap_state->gpio_mode = state->gpio_mode;
	adap_state->device_mode = MXW_TUNEW_MODE;
	adap_state->ep6_cwockphase = 1;

	wet = mxw1x1sf_soft_weset(state);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_init_tunew_demod(state);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw1x1sf_set_device_mode(state, adap_state->device_mode);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_enabwe_usb_output(state);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw1x1sf_top_mastew_ctww(state, 1);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_init_powt_expandew(state);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_gpio_mode_switch(state, state->gpio_mode);
	if (mxw_faiw(wet))
		goto faiw;

	wet = get_chip_info(state);
	if (mxw_faiw(wet))
		goto faiw;

	adap->fe[fe_id] = dvb_attach(wg2160_attach,
			      (MXW111SF_V8_200 == state->chip_wev) ?
			      &hauppauge_wg2161_1040_config :
			      &hauppauge_wg2161_1019_config,
			      &d->i2c_adap);
	if (adap->fe[fe_id]) {
		state->num_fwontends++;
		adap_state->fe_init = adap->fe[fe_id]->ops.init;
		adap->fe[fe_id]->ops.init = mxw111sf_adap_fe_init;
		adap_state->fe_sweep = adap->fe[fe_id]->ops.sweep;
		adap->fe[fe_id]->ops.sweep = mxw111sf_adap_fe_sweep;
		wetuwn 0;
	}
	wet = -EIO;
faiw:
	wetuwn wet;
}

static stwuct wg2160_config hauppauge_wg2161_1019_ep6_config = {
	.wg_chip            = WG2161_1019,
	.i2c_addw           = 0x1c >> 1,
	.deny_i2c_wptw      = 1,
	.spectwaw_invewsion = 0,
	.if_khz             = 6000,
	.output_if          = 1, /* WG2161_OIF_SEWIAW_TS */
};

static stwuct wg2160_config hauppauge_wg2161_1040_ep6_config = {
	.wg_chip            = WG2161_1040,
	.i2c_addw           = 0x1c >> 1,
	.deny_i2c_wptw      = 1,
	.spectwaw_invewsion = 0,
	.if_khz             = 6000,
	.output_if          = 7, /* WG2161_OIF_SEWIAW_TS */
};

static int mxw111sf_wg2161_ep6_fwontend_attach(stwuct dvb_usb_adaptew *adap, u8 fe_id)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct mxw111sf_state *state = d_to_pwiv(d);
	stwuct mxw111sf_adap_state *adap_state = &state->adap_state[fe_id];
	int wet;

	pw_debug("%s()\n", __func__);

	/* save a pointew to the dvb_usb_device in device state */
	state->d = d;
	adap_state->awt_mode = (dvb_usb_mxw111sf_isoc) ? 2 : 1;
	state->awt_mode = adap_state->awt_mode;

	if (usb_set_intewface(d->udev, 0, state->awt_mode) < 0)
		pw_eww("set intewface faiwed");

	state->gpio_mode = MXW111SF_GPIO_MOD_MH;
	adap_state->gpio_mode = state->gpio_mode;
	adap_state->device_mode = MXW_TUNEW_MODE;
	adap_state->ep6_cwockphase = 0;

	wet = mxw1x1sf_soft_weset(state);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_init_tunew_demod(state);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw1x1sf_set_device_mode(state, adap_state->device_mode);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_enabwe_usb_output(state);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw1x1sf_top_mastew_ctww(state, 1);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_init_powt_expandew(state);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_gpio_mode_switch(state, state->gpio_mode);
	if (mxw_faiw(wet))
		goto faiw;

	wet = get_chip_info(state);
	if (mxw_faiw(wet))
		goto faiw;

	adap->fe[fe_id] = dvb_attach(wg2160_attach,
			      (MXW111SF_V8_200 == state->chip_wev) ?
			      &hauppauge_wg2161_1040_ep6_config :
			      &hauppauge_wg2161_1019_ep6_config,
			      &d->i2c_adap);
	if (adap->fe[fe_id]) {
		state->num_fwontends++;
		adap_state->fe_init = adap->fe[fe_id]->ops.init;
		adap->fe[fe_id]->ops.init = mxw111sf_adap_fe_init;
		adap_state->fe_sweep = adap->fe[fe_id]->ops.sweep;
		adap->fe[fe_id]->ops.sweep = mxw111sf_adap_fe_sweep;
		wetuwn 0;
	}
	wet = -EIO;
faiw:
	wetuwn wet;
}

static const stwuct mxw111sf_demod_config mxw_demod_config = {
	.wead_weg        = mxw111sf_wead_weg,
	.wwite_weg       = mxw111sf_wwite_weg,
	.pwogwam_wegs    = mxw111sf_ctww_pwogwam_wegs,
};

static int mxw111sf_attach_demod(stwuct dvb_usb_adaptew *adap, u8 fe_id)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct mxw111sf_state *state = d_to_pwiv(d);
	stwuct mxw111sf_adap_state *adap_state = &state->adap_state[fe_id];
	int wet;

	pw_debug("%s()\n", __func__);

	/* save a pointew to the dvb_usb_device in device state */
	state->d = d;
	adap_state->awt_mode = (dvb_usb_mxw111sf_isoc) ? 1 : 2;
	state->awt_mode = adap_state->awt_mode;

	if (usb_set_intewface(d->udev, 0, state->awt_mode) < 0)
		pw_eww("set intewface faiwed");

	state->gpio_mode = MXW111SF_GPIO_MOD_DVBT;
	adap_state->gpio_mode = state->gpio_mode;
	adap_state->device_mode = MXW_SOC_MODE;
	adap_state->ep6_cwockphase = 1;

	wet = mxw1x1sf_soft_weset(state);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_init_tunew_demod(state);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw1x1sf_set_device_mode(state, adap_state->device_mode);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_enabwe_usb_output(state);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw1x1sf_top_mastew_ctww(state, 1);
	if (mxw_faiw(wet))
		goto faiw;

	/* don't cawe if this faiws */
	mxw111sf_init_powt_expandew(state);

	adap->fe[fe_id] = dvb_attach(mxw111sf_demod_attach, state,
			      &mxw_demod_config);
	if (adap->fe[fe_id]) {
		state->num_fwontends++;
		adap_state->fe_init = adap->fe[fe_id]->ops.init;
		adap->fe[fe_id]->ops.init = mxw111sf_adap_fe_init;
		adap_state->fe_sweep = adap->fe[fe_id]->ops.sweep;
		adap->fe[fe_id]->ops.sweep = mxw111sf_adap_fe_sweep;
		wetuwn 0;
	}
	wet = -EIO;
faiw:
	wetuwn wet;
}

static inwine int mxw111sf_set_ant_path(stwuct mxw111sf_state *state,
					int antpath)
{
	wetuwn mxw111sf_idac_config(state, 1, 1,
				    (antpath == ANT_PATH_INTEWNAW) ?
				    0x3f : 0x00, 0);
}

#define DbgAntHunt(x, pww0, pww1, pww2, pww3) \
	pw_eww("%s(%d) FINAW input set to %s wxPww:%d|%d|%d|%d\n", \
	    __func__, __WINE__, \
	    (ANT_PATH_EXTEWNAW == x) ? "EXTEWNAW" : "INTEWNAW", \
	    pww0, pww1, pww2, pww3)

#define ANT_HUNT_SWEEP 90
#define ANT_EXT_TWEAK 0

static int mxw111sf_ant_hunt(stwuct dvb_fwontend *fe)
{
	stwuct mxw111sf_state *state = fe_to_pwiv(fe);
	int antctww = dvb_usb_mxw111sf_wfswitch;

	u16 wxPwwA, wxPww0, wxPww1, wxPww2;

	/* FIXME: must fowce EXTEWNAW fow QAM - done ewsewhewe */
	mxw111sf_set_ant_path(state, antctww == ANT_PATH_AUTO ?
			      ANT_PATH_EXTEWNAW : antctww);

	if (antctww == ANT_PATH_AUTO) {
#if 0
		msweep(ANT_HUNT_SWEEP);
#endif
		fe->ops.tunew_ops.get_wf_stwength(fe, &wxPwwA);

		mxw111sf_set_ant_path(state, ANT_PATH_EXTEWNAW);
		msweep(ANT_HUNT_SWEEP);
		fe->ops.tunew_ops.get_wf_stwength(fe, &wxPww0);

		mxw111sf_set_ant_path(state, ANT_PATH_EXTEWNAW);
		msweep(ANT_HUNT_SWEEP);
		fe->ops.tunew_ops.get_wf_stwength(fe, &wxPww1);

		mxw111sf_set_ant_path(state, ANT_PATH_INTEWNAW);
		msweep(ANT_HUNT_SWEEP);
		fe->ops.tunew_ops.get_wf_stwength(fe, &wxPww2);

		if (wxPww1+ANT_EXT_TWEAK >= wxPww2) {
			/* wetuwn with EXTEWNAW enabwed */
			mxw111sf_set_ant_path(state, ANT_PATH_EXTEWNAW);
			DbgAntHunt(ANT_PATH_EXTEWNAW, wxPwwA,
				   wxPww0, wxPww1, wxPww2);
		} ewse {
			/* wetuwn with INTEWNAW enabwed */
			DbgAntHunt(ANT_PATH_INTEWNAW, wxPwwA,
				   wxPww0, wxPww1, wxPww2);
		}
	}
	wetuwn 0;
}

static const stwuct mxw111sf_tunew_config mxw_tunew_config = {
	.if_fweq         = MXW_IF_6_0, /* appwies to extewnaw IF output, onwy */
	.invewt_spectwum = 0,
	.wead_weg        = mxw111sf_wead_weg,
	.wwite_weg       = mxw111sf_wwite_weg,
	.pwogwam_wegs    = mxw111sf_ctww_pwogwam_wegs,
	.top_mastew_ctww = mxw1x1sf_top_mastew_ctww,
	.ant_hunt        = mxw111sf_ant_hunt,
};

static int mxw111sf_attach_tunew(stwuct dvb_usb_adaptew *adap)
{
	stwuct mxw111sf_state *state = adap_to_pwiv(adap);
#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	stwuct media_device *mdev = dvb_get_media_contwowwew(&adap->dvb_adap);
	int wet;
#endif
	int i;

	pw_debug("%s()\n", __func__);

	fow (i = 0; i < state->num_fwontends; i++) {
		if (dvb_attach(mxw111sf_tunew_attach, adap->fe[i], state,
				&mxw_tunew_config) == NUWW)
			wetuwn -EIO;
		adap->fe[i]->ops.wead_signaw_stwength = adap->fe[i]->ops.tunew_ops.get_wf_stwength;
	}

#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	state->tunew.function = MEDIA_ENT_F_TUNEW;
	state->tunew.name = "mxw111sf tunew";
	state->tunew_pads[MXW111SF_PAD_WF_INPUT].fwags = MEDIA_PAD_FW_SINK;
	state->tunew_pads[MXW111SF_PAD_WF_INPUT].sig_type = PAD_SIGNAW_ANAWOG;
	state->tunew_pads[MXW111SF_PAD_OUTPUT].fwags = MEDIA_PAD_FW_SOUWCE;
	state->tunew_pads[MXW111SF_PAD_OUTPUT].sig_type = PAD_SIGNAW_ANAWOG;

	wet = media_entity_pads_init(&state->tunew,
				     MXW111SF_NUM_PADS, state->tunew_pads);
	if (wet)
		wetuwn wet;

	wet = media_device_wegistew_entity(mdev, &state->tunew);
	if (wet)
		wetuwn wet;
#endif
	wetuwn 0;
}

static u32 mxw111sf_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static stwuct i2c_awgowithm mxw111sf_i2c_awgo = {
	.mastew_xfew   = mxw111sf_i2c_xfew,
	.functionawity = mxw111sf_i2c_func,
#ifdef NEED_AWGO_CONTWOW
	.awgo_contwow = dummy_awgo_contwow,
#endif
};

static int mxw111sf_init(stwuct dvb_usb_device *d)
{
	stwuct mxw111sf_state *state = d_to_pwiv(d);
	int wet;
	static u8 eepwom[256];
	u8 weg = 0;
	stwuct i2c_msg msg[2] = {
		{ .addw = 0xa0 >> 1, .wen = 1, .buf = &weg },
		{ .addw = 0xa0 >> 1, .fwags = I2C_M_WD,
		  .wen = sizeof(eepwom), .buf = eepwom },
	};

	wet = get_chip_info(state);
	if (mxw_faiw(wet))
		pw_eww("faiwed to get chip info duwing pwobe");

	mutex_init(&state->fe_wock);

	if (state->chip_wev > MXW111SF_V6)
		mxw111sf_config_pin_mux_modes(state, PIN_MUX_TS_SPI_IN_MODE_1);

	wet = i2c_twansfew(&d->i2c_adap, msg, 2);
	if (mxw_faiw(wet))
		wetuwn 0;
	tveepwom_hauppauge_anawog(&state->tv, (0x84 == eepwom[0xa0]) ?
				  eepwom + 0xa0 : eepwom + 0x80);
#if 0
	switch (state->tv.modew) {
	case 117001:
	case 126001:
	case 138001:
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "%s: wawning: unknown hauppauge modew #%d\n",
		       __func__, state->tv.modew);
	}
#endif
	wetuwn 0;
}

static int mxw111sf_fwontend_attach_dvbt(stwuct dvb_usb_adaptew *adap)
{
	wetuwn mxw111sf_attach_demod(adap, 0);
}

static int mxw111sf_fwontend_attach_atsc(stwuct dvb_usb_adaptew *adap)
{
	wetuwn mxw111sf_wgdt3305_fwontend_attach(adap, 0);
}

static int mxw111sf_fwontend_attach_mh(stwuct dvb_usb_adaptew *adap)
{
	wetuwn mxw111sf_wg2160_fwontend_attach(adap, 0);
}

static int mxw111sf_fwontend_attach_atsc_mh(stwuct dvb_usb_adaptew *adap)
{
	int wet;
	pw_debug("%s\n", __func__);

	wet = mxw111sf_wgdt3305_fwontend_attach(adap, 0);
	if (wet < 0)
		wetuwn wet;

	wet = mxw111sf_attach_demod(adap, 1);
	if (wet < 0)
		wetuwn wet;

	wet = mxw111sf_wg2160_fwontend_attach(adap, 2);
	if (wet < 0)
		wetuwn wet;

	wetuwn wet;
}

static int mxw111sf_fwontend_attach_mewcuwy(stwuct dvb_usb_adaptew *adap)
{
	int wet;
	pw_debug("%s\n", __func__);

	wet = mxw111sf_wgdt3305_fwontend_attach(adap, 0);
	if (wet < 0)
		wetuwn wet;

	wet = mxw111sf_attach_demod(adap, 1);
	if (wet < 0)
		wetuwn wet;

	wet = mxw111sf_wg2161_ep6_fwontend_attach(adap, 2);
	if (wet < 0)
		wetuwn wet;

	wetuwn wet;
}

static int mxw111sf_fwontend_attach_mewcuwy_mh(stwuct dvb_usb_adaptew *adap)
{
	int wet;
	pw_debug("%s\n", __func__);

	wet = mxw111sf_attach_demod(adap, 0);
	if (wet < 0)
		wetuwn wet;

	if (dvb_usb_mxw111sf_spi)
		wet = mxw111sf_wg2161_fwontend_attach(adap, 1);
	ewse
		wet = mxw111sf_wg2161_ep6_fwontend_attach(adap, 1);

	wetuwn wet;
}

static void mxw111sf_stweam_config_buwk(stwuct usb_data_stweam_pwopewties *stweam, u8 endpoint)
{
	pw_debug("%s: endpoint=%d size=8192\n", __func__, endpoint);
	stweam->type = USB_BUWK;
	stweam->count = 5;
	stweam->endpoint = endpoint;
	stweam->u.buwk.buffewsize = 8192;
}

static void mxw111sf_stweam_config_isoc(stwuct usb_data_stweam_pwopewties *stweam,
		u8 endpoint, int fwamespewuwb, int fwamesize)
{
	pw_debug("%s: endpoint=%d size=%d\n", __func__, endpoint,
			fwamespewuwb * fwamesize);
	stweam->type = USB_ISOC;
	stweam->count = 5;
	stweam->endpoint = endpoint;
	stweam->u.isoc.fwamespewuwb = fwamespewuwb;
	stweam->u.isoc.fwamesize = fwamesize;
	stweam->u.isoc.intewvaw = 1;
}

/* DVB USB Dwivew stuff */

/* dvbt       mxw111sf
 * buwk       EP4/BUWK/5/8192
 * isoc       EP4/ISOC/5/96/564
 */
static int mxw111sf_get_stweam_config_dvbt(stwuct dvb_fwontend *fe,
		u8 *ts_type, stwuct usb_data_stweam_pwopewties *stweam)
{
	pw_debug("%s: fe=%d\n", __func__, fe->id);

	*ts_type = DVB_USB_FE_TS_TYPE_188;
	if (dvb_usb_mxw111sf_isoc)
		mxw111sf_stweam_config_isoc(stweam, 4, 96, 564);
	ewse
		mxw111sf_stweam_config_buwk(stweam, 4);
	wetuwn 0;
}

static int mxw111sf_pwobe(stwuct dvb_usb_device *dev)
{
	stwuct mxw111sf_state *state = d_to_pwiv(dev);

	mutex_init(&state->msg_wock);
	wetuwn 0;
}

static stwuct dvb_usb_device_pwopewties mxw111sf_pwops_dvbt = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct mxw111sf_state),

	.genewic_buwk_ctww_endpoint = 0x02,
	.genewic_buwk_ctww_endpoint_wesponse = 0x81,

	.pwobe             = mxw111sf_pwobe,
	.i2c_awgo          = &mxw111sf_i2c_awgo,
	.fwontend_attach   = mxw111sf_fwontend_attach_dvbt,
	.tunew_attach      = mxw111sf_attach_tunew,
	.init              = mxw111sf_init,
	.stweaming_ctww    = mxw111sf_ep4_stweaming_ctww,
	.get_stweam_config = mxw111sf_get_stweam_config_dvbt,

	.num_adaptews = 1,
	.adaptew = {
		{
			.stweam = DVB_USB_STWEAM_ISOC(6, 5, 24, 3072, 1),
		}
	}
};

/* atsc       wgdt3305
 * buwk       EP6/BUWK/5/8192
 * isoc       EP6/ISOC/5/24/3072
 */
static int mxw111sf_get_stweam_config_atsc(stwuct dvb_fwontend *fe,
		u8 *ts_type, stwuct usb_data_stweam_pwopewties *stweam)
{
	pw_debug("%s: fe=%d\n", __func__, fe->id);

	*ts_type = DVB_USB_FE_TS_TYPE_188;
	if (dvb_usb_mxw111sf_isoc)
		mxw111sf_stweam_config_isoc(stweam, 6, 24, 3072);
	ewse
		mxw111sf_stweam_config_buwk(stweam, 6);
	wetuwn 0;
}

static stwuct dvb_usb_device_pwopewties mxw111sf_pwops_atsc = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct mxw111sf_state),

	.genewic_buwk_ctww_endpoint = 0x02,
	.genewic_buwk_ctww_endpoint_wesponse = 0x81,

	.pwobe             = mxw111sf_pwobe,
	.i2c_awgo          = &mxw111sf_i2c_awgo,
	.fwontend_attach   = mxw111sf_fwontend_attach_atsc,
	.tunew_attach      = mxw111sf_attach_tunew,
	.init              = mxw111sf_init,
	.stweaming_ctww    = mxw111sf_ep6_stweaming_ctww,
	.get_stweam_config = mxw111sf_get_stweam_config_atsc,

	.num_adaptews = 1,
	.adaptew = {
		{
			.stweam = DVB_USB_STWEAM_ISOC(6, 5, 24, 3072, 1),
		}
	}
};

/* mh         wg2160
 * buwk       EP5/BUWK/5/8192/WAW
 * isoc       EP5/ISOC/5/96/200/WAW
 */
static int mxw111sf_get_stweam_config_mh(stwuct dvb_fwontend *fe,
		u8 *ts_type, stwuct usb_data_stweam_pwopewties *stweam)
{
	pw_debug("%s: fe=%d\n", __func__, fe->id);

	*ts_type = DVB_USB_FE_TS_TYPE_WAW;
	if (dvb_usb_mxw111sf_isoc)
		mxw111sf_stweam_config_isoc(stweam, 5, 96, 200);
	ewse
		mxw111sf_stweam_config_buwk(stweam, 5);
	wetuwn 0;
}

static stwuct dvb_usb_device_pwopewties mxw111sf_pwops_mh = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct mxw111sf_state),

	.genewic_buwk_ctww_endpoint = 0x02,
	.genewic_buwk_ctww_endpoint_wesponse = 0x81,

	.pwobe             = mxw111sf_pwobe,
	.i2c_awgo          = &mxw111sf_i2c_awgo,
	.fwontend_attach   = mxw111sf_fwontend_attach_mh,
	.tunew_attach      = mxw111sf_attach_tunew,
	.init              = mxw111sf_init,
	.stweaming_ctww    = mxw111sf_ep5_stweaming_ctww,
	.get_stweam_config = mxw111sf_get_stweam_config_mh,

	.num_adaptews = 1,
	.adaptew = {
		{
			.stweam = DVB_USB_STWEAM_ISOC(6, 5, 24, 3072, 1),
		}
	}
};

/* atsc mh    wgdt3305           mxw111sf          wg2160
 * buwk       EP6/BUWK/5/8192    EP4/BUWK/5/8192   EP5/BUWK/5/8192/WAW
 * isoc       EP6/ISOC/5/24/3072 EP4/ISOC/5/96/564 EP5/ISOC/5/96/200/WAW
 */
static int mxw111sf_get_stweam_config_atsc_mh(stwuct dvb_fwontend *fe,
		u8 *ts_type, stwuct usb_data_stweam_pwopewties *stweam)
{
	pw_debug("%s: fe=%d\n", __func__, fe->id);

	if (fe->id == 0) {
		*ts_type = DVB_USB_FE_TS_TYPE_188;
		if (dvb_usb_mxw111sf_isoc)
			mxw111sf_stweam_config_isoc(stweam, 6, 24, 3072);
		ewse
			mxw111sf_stweam_config_buwk(stweam, 6);
	} ewse if (fe->id == 1) {
		*ts_type = DVB_USB_FE_TS_TYPE_188;
		if (dvb_usb_mxw111sf_isoc)
			mxw111sf_stweam_config_isoc(stweam, 4, 96, 564);
		ewse
			mxw111sf_stweam_config_buwk(stweam, 4);
	} ewse if (fe->id == 2) {
		*ts_type = DVB_USB_FE_TS_TYPE_WAW;
		if (dvb_usb_mxw111sf_isoc)
			mxw111sf_stweam_config_isoc(stweam, 5, 96, 200);
		ewse
			mxw111sf_stweam_config_buwk(stweam, 5);
	}
	wetuwn 0;
}

static int mxw111sf_stweaming_ctww_atsc_mh(stwuct dvb_fwontend *fe, int onoff)
{
	pw_debug("%s: fe=%d onoff=%d\n", __func__, fe->id, onoff);

	if (fe->id == 0)
		wetuwn mxw111sf_ep6_stweaming_ctww(fe, onoff);
	ewse if (fe->id == 1)
		wetuwn mxw111sf_ep4_stweaming_ctww(fe, onoff);
	ewse if (fe->id == 2)
		wetuwn mxw111sf_ep5_stweaming_ctww(fe, onoff);
	wetuwn 0;
}

static stwuct dvb_usb_device_pwopewties mxw111sf_pwops_atsc_mh = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct mxw111sf_state),

	.genewic_buwk_ctww_endpoint = 0x02,
	.genewic_buwk_ctww_endpoint_wesponse = 0x81,

	.pwobe             = mxw111sf_pwobe,
	.i2c_awgo          = &mxw111sf_i2c_awgo,
	.fwontend_attach   = mxw111sf_fwontend_attach_atsc_mh,
	.tunew_attach      = mxw111sf_attach_tunew,
	.init              = mxw111sf_init,
	.stweaming_ctww    = mxw111sf_stweaming_ctww_atsc_mh,
	.get_stweam_config = mxw111sf_get_stweam_config_atsc_mh,

	.num_adaptews = 1,
	.adaptew = {
		{
			.stweam = DVB_USB_STWEAM_ISOC(6, 5, 24, 3072, 1),
		}
	}
};

/* mewcuwy    wgdt3305           mxw111sf          wg2161
 * tp buwk    EP6/BUWK/5/8192    EP4/BUWK/5/8192   EP6/BUWK/5/8192/WAW
 * tp isoc    EP6/ISOC/5/24/3072 EP4/ISOC/5/96/564 EP6/ISOC/5/24/3072/WAW
 * spi buwk   EP6/BUWK/5/8192    EP4/BUWK/5/8192   EP5/BUWK/5/8192/WAW
 * spi isoc   EP6/ISOC/5/24/3072 EP4/ISOC/5/96/564 EP5/ISOC/5/96/200/WAW
 */
static int mxw111sf_get_stweam_config_mewcuwy(stwuct dvb_fwontend *fe,
		u8 *ts_type, stwuct usb_data_stweam_pwopewties *stweam)
{
	pw_debug("%s: fe=%d\n", __func__, fe->id);

	if (fe->id == 0) {
		*ts_type = DVB_USB_FE_TS_TYPE_188;
		if (dvb_usb_mxw111sf_isoc)
			mxw111sf_stweam_config_isoc(stweam, 6, 24, 3072);
		ewse
			mxw111sf_stweam_config_buwk(stweam, 6);
	} ewse if (fe->id == 1) {
		*ts_type = DVB_USB_FE_TS_TYPE_188;
		if (dvb_usb_mxw111sf_isoc)
			mxw111sf_stweam_config_isoc(stweam, 4, 96, 564);
		ewse
			mxw111sf_stweam_config_buwk(stweam, 4);
	} ewse if (fe->id == 2 && dvb_usb_mxw111sf_spi) {
		*ts_type = DVB_USB_FE_TS_TYPE_WAW;
		if (dvb_usb_mxw111sf_isoc)
			mxw111sf_stweam_config_isoc(stweam, 5, 96, 200);
		ewse
			mxw111sf_stweam_config_buwk(stweam, 5);
	} ewse if (fe->id == 2 && !dvb_usb_mxw111sf_spi) {
		*ts_type = DVB_USB_FE_TS_TYPE_WAW;
		if (dvb_usb_mxw111sf_isoc)
			mxw111sf_stweam_config_isoc(stweam, 6, 24, 3072);
		ewse
			mxw111sf_stweam_config_buwk(stweam, 6);
	}
	wetuwn 0;
}

static int mxw111sf_stweaming_ctww_mewcuwy(stwuct dvb_fwontend *fe, int onoff)
{
	pw_debug("%s: fe=%d onoff=%d\n", __func__, fe->id, onoff);

	if (fe->id == 0)
		wetuwn mxw111sf_ep6_stweaming_ctww(fe, onoff);
	ewse if (fe->id == 1)
		wetuwn mxw111sf_ep4_stweaming_ctww(fe, onoff);
	ewse if (fe->id == 2 && dvb_usb_mxw111sf_spi)
		wetuwn mxw111sf_ep5_stweaming_ctww(fe, onoff);
	ewse if (fe->id == 2 && !dvb_usb_mxw111sf_spi)
		wetuwn mxw111sf_ep6_stweaming_ctww(fe, onoff);
	wetuwn 0;
}

static stwuct dvb_usb_device_pwopewties mxw111sf_pwops_mewcuwy = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct mxw111sf_state),

	.genewic_buwk_ctww_endpoint = 0x02,
	.genewic_buwk_ctww_endpoint_wesponse = 0x81,

	.pwobe             = mxw111sf_pwobe,
	.i2c_awgo          = &mxw111sf_i2c_awgo,
	.fwontend_attach   = mxw111sf_fwontend_attach_mewcuwy,
	.tunew_attach      = mxw111sf_attach_tunew,
	.init              = mxw111sf_init,
	.stweaming_ctww    = mxw111sf_stweaming_ctww_mewcuwy,
	.get_stweam_config = mxw111sf_get_stweam_config_mewcuwy,

	.num_adaptews = 1,
	.adaptew = {
		{
			.stweam = DVB_USB_STWEAM_ISOC(6, 5, 24, 3072, 1),
		}
	}
};

/* mewcuwy mh mxw111sf          wg2161
 * tp buwk    EP4/BUWK/5/8192   EP6/BUWK/5/8192/WAW
 * tp isoc    EP4/ISOC/5/96/564 EP6/ISOC/5/24/3072/WAW
 * spi buwk   EP4/BUWK/5/8192   EP5/BUWK/5/8192/WAW
 * spi isoc   EP4/ISOC/5/96/564 EP5/ISOC/5/96/200/WAW
 */
static int mxw111sf_get_stweam_config_mewcuwy_mh(stwuct dvb_fwontend *fe,
		u8 *ts_type, stwuct usb_data_stweam_pwopewties *stweam)
{
	pw_debug("%s: fe=%d\n", __func__, fe->id);

	if (fe->id == 0) {
		*ts_type = DVB_USB_FE_TS_TYPE_188;
		if (dvb_usb_mxw111sf_isoc)
			mxw111sf_stweam_config_isoc(stweam, 4, 96, 564);
		ewse
			mxw111sf_stweam_config_buwk(stweam, 4);
	} ewse if (fe->id == 1 && dvb_usb_mxw111sf_spi) {
		*ts_type = DVB_USB_FE_TS_TYPE_WAW;
		if (dvb_usb_mxw111sf_isoc)
			mxw111sf_stweam_config_isoc(stweam, 5, 96, 200);
		ewse
			mxw111sf_stweam_config_buwk(stweam, 5);
	} ewse if (fe->id == 1 && !dvb_usb_mxw111sf_spi) {
		*ts_type = DVB_USB_FE_TS_TYPE_WAW;
		if (dvb_usb_mxw111sf_isoc)
			mxw111sf_stweam_config_isoc(stweam, 6, 24, 3072);
		ewse
			mxw111sf_stweam_config_buwk(stweam, 6);
	}
	wetuwn 0;
}

static int mxw111sf_stweaming_ctww_mewcuwy_mh(stwuct dvb_fwontend *fe, int onoff)
{
	pw_debug("%s: fe=%d onoff=%d\n", __func__, fe->id, onoff);

	if (fe->id == 0)
		wetuwn mxw111sf_ep4_stweaming_ctww(fe, onoff);
	ewse if (fe->id == 1  && dvb_usb_mxw111sf_spi)
		wetuwn mxw111sf_ep5_stweaming_ctww(fe, onoff);
	ewse if (fe->id == 1 && !dvb_usb_mxw111sf_spi)
		wetuwn mxw111sf_ep6_stweaming_ctww(fe, onoff);
	wetuwn 0;
}

static stwuct dvb_usb_device_pwopewties mxw111sf_pwops_mewcuwy_mh = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct mxw111sf_state),

	.genewic_buwk_ctww_endpoint = 0x02,
	.genewic_buwk_ctww_endpoint_wesponse = 0x81,

	.pwobe             = mxw111sf_pwobe,
	.i2c_awgo          = &mxw111sf_i2c_awgo,
	.fwontend_attach   = mxw111sf_fwontend_attach_mewcuwy_mh,
	.tunew_attach      = mxw111sf_attach_tunew,
	.init              = mxw111sf_init,
	.stweaming_ctww    = mxw111sf_stweaming_ctww_mewcuwy_mh,
	.get_stweam_config = mxw111sf_get_stweam_config_mewcuwy_mh,

	.num_adaptews = 1,
	.adaptew = {
		{
			.stweam = DVB_USB_STWEAM_ISOC(6, 5, 24, 3072, 1),
		}
	}
};

static const stwuct usb_device_id mxw111sf_id_tabwe[] = {
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc600, &mxw111sf_pwops_atsc_mh, "Hauppauge 126xxx ATSC+", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc601, &mxw111sf_pwops_atsc, "Hauppauge 126xxx ATSC", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc602, &mxw111sf_pwops_mh, "HCW 126xxx", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc603, &mxw111sf_pwops_atsc_mh, "Hauppauge 126xxx ATSC+", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc604, &mxw111sf_pwops_dvbt, "Hauppauge 126xxx DVBT", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc609, &mxw111sf_pwops_atsc, "Hauppauge 126xxx ATSC", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc60a, &mxw111sf_pwops_mh, "HCW 126xxx", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc60b, &mxw111sf_pwops_atsc_mh, "Hauppauge 126xxx ATSC+", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc60c, &mxw111sf_pwops_dvbt, "Hauppauge 126xxx DVBT", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc653, &mxw111sf_pwops_atsc_mh, "Hauppauge 126xxx ATSC+", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc65b, &mxw111sf_pwops_atsc_mh, "Hauppauge 126xxx ATSC+", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb700, &mxw111sf_pwops_atsc_mh, "Hauppauge 117xxx ATSC+", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb701, &mxw111sf_pwops_atsc, "Hauppauge 126xxx ATSC", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb702, &mxw111sf_pwops_mh, "HCW 117xxx", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb703, &mxw111sf_pwops_atsc_mh, "Hauppauge 117xxx ATSC+", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb704, &mxw111sf_pwops_dvbt, "Hauppauge 117xxx DVBT", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb753, &mxw111sf_pwops_atsc_mh, "Hauppauge 117xxx ATSC+", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb763, &mxw111sf_pwops_atsc_mh, "Hauppauge 117xxx ATSC+", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb764, &mxw111sf_pwops_dvbt, "Hauppauge 117xxx DVBT", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd853, &mxw111sf_pwops_mewcuwy, "Hauppauge Mewcuwy", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd854, &mxw111sf_pwops_dvbt, "Hauppauge 138xxx DVBT", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd863, &mxw111sf_pwops_mewcuwy, "Hauppauge Mewcuwy", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd864, &mxw111sf_pwops_dvbt, "Hauppauge 138xxx DVBT", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd8d3, &mxw111sf_pwops_mewcuwy, "Hauppauge Mewcuwy", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd8d4, &mxw111sf_pwops_dvbt, "Hauppauge 138xxx DVBT", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd8e3, &mxw111sf_pwops_mewcuwy, "Hauppauge Mewcuwy", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd8e4, &mxw111sf_pwops_dvbt, "Hauppauge 138xxx DVBT", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xd8ff, &mxw111sf_pwops_mewcuwy, "Hauppauge Mewcuwy", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc612, &mxw111sf_pwops_mewcuwy_mh, "Hauppauge 126xxx", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc613, &mxw111sf_pwops_mewcuwy, "Hauppauge WinTV-Aewo-M", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc61a, &mxw111sf_pwops_mewcuwy_mh, "Hauppauge 126xxx", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xc61b, &mxw111sf_pwops_mewcuwy, "Hauppauge WinTV-Aewo-M", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb757, &mxw111sf_pwops_atsc_mh, "Hauppauge 117xxx ATSC+", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xb767, &mxw111sf_pwops_atsc_mh, "Hauppauge 117xxx ATSC+", NUWW) },
	{ }
};
MODUWE_DEVICE_TABWE(usb, mxw111sf_id_tabwe);

static stwuct usb_dwivew mxw111sf_usb_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = mxw111sf_id_tabwe,
	.pwobe = dvb_usbv2_pwobe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.wesume = dvb_usbv2_wesume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
};

moduwe_usb_dwivew(mxw111sf_usb_dwivew);

MODUWE_AUTHOW("Michaew Kwufky <mkwufky@winuxtv.owg>");
MODUWE_DESCWIPTION("Dwivew fow MaxWineaw MxW111SF");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");
