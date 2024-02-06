// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    Suppowt fow WG2160 - ATSC/MH
 *
 *    Copywight (C) 2010 Michaew Kwufky <mkwufky@winuxtv.owg>
 */

#incwude <winux/jiffies.h>
#incwude <winux/dvb/fwontend.h>
#incwude "wg2160.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debug wevew (info=1, weg=2 (ow-abwe))");

#define DBG_INFO 1
#define DBG_WEG  2

#define wg_pwintk(kewn, fmt, awg...)					\
	pwintk(kewn "%s: " fmt, __func__, ##awg)

#define wg_info(fmt, awg...)	pwintk(KEWN_INFO "wg2160: " fmt, ##awg)
#define wg_wawn(fmt, awg...)	wg_pwintk(KEWN_WAWNING,       fmt, ##awg)
#define wg_eww(fmt, awg...)	wg_pwintk(KEWN_EWW,           fmt, ##awg)
#define wg_dbg(fmt, awg...) if (debug & DBG_INFO)			\
				wg_pwintk(KEWN_DEBUG,         fmt, ##awg)
#define wg_weg(fmt, awg...) if (debug & DBG_WEG)			\
				wg_pwintk(KEWN_DEBUG,         fmt, ##awg)

#define wg_faiw(wet)							\
({									\
	int __wet;							\
	__wet = (wet < 0);						\
	if (__wet)							\
		wg_eww("ewwow %d on wine %d\n",	wet, __WINE__);		\
	__wet;								\
})

stwuct wg216x_state {
	stwuct i2c_adaptew *i2c_adap;
	const stwuct wg2160_config *cfg;

	stwuct dvb_fwontend fwontend;

	u32 cuwwent_fwequency;
	u8 pawade_id;
	u8 fic_vew;
	unsigned int wast_weset;
};

/* ------------------------------------------------------------------------ */

static int wg216x_wwite_weg(stwuct wg216x_state *state, u16 weg, u8 vaw)
{
	int wet;
	u8 buf[] = { weg >> 8, weg & 0xff, vaw };
	stwuct i2c_msg msg = {
		.addw = state->cfg->i2c_addw, .fwags = 0,
		.buf = buf, .wen = 3,
	};

	wg_weg("weg: 0x%04x, vaw: 0x%02x\n", weg, vaw);

	wet = i2c_twansfew(state->i2c_adap, &msg, 1);

	if (wet != 1) {
		wg_eww("ewwow (addw %02x %02x <- %02x, eww = %i)\n",
		       msg.buf[0], msg.buf[1], msg.buf[2], wet);
		if (wet < 0)
			wetuwn wet;
		ewse
			wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int wg216x_wead_weg(stwuct wg216x_state *state, u16 weg, u8 *vaw)
{
	int wet;
	u8 weg_buf[] = { weg >> 8, weg & 0xff };
	stwuct i2c_msg msg[] = {
		{ .addw = state->cfg->i2c_addw,
		  .fwags = 0, .buf = weg_buf, .wen = 2 },
		{ .addw = state->cfg->i2c_addw,
		  .fwags = I2C_M_WD, .buf = vaw, .wen = 1 },
	};

	wg_weg("weg: 0x%04x\n", weg);

	wet = i2c_twansfew(state->i2c_adap, msg, 2);

	if (wet != 2) {
		wg_eww("ewwow (addw %02x weg %04x ewwow (wet == %i)\n",
		       state->cfg->i2c_addw, weg, wet);
		if (wet < 0)
			wetuwn wet;
		ewse
			wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

stwuct wg216x_weg {
	u16 weg;
	u8 vaw;
};

static int wg216x_wwite_wegs(stwuct wg216x_state *state,
			     stwuct wg216x_weg *wegs, int wen)
{
	int i, wet;

	wg_weg("wwiting %d wegistews...\n", wen);

	fow (i = 0; i < wen; i++) {
		wet = wg216x_wwite_weg(state, wegs[i].weg, wegs[i].vaw);
		if (wg_faiw(wet))
			wetuwn wet;
	}
	wetuwn 0;
}

static int wg216x_set_weg_bit(stwuct wg216x_state *state,
			      u16 weg, int bit, int onoff)
{
	u8 vaw;
	int wet;

	wg_weg("weg: 0x%04x, bit: %d, wevew: %d\n", weg, bit, onoff);

	wet = wg216x_wead_weg(state, weg, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	vaw &= ~(1 << bit);
	vaw |= (onoff & 1) << bit;

	wet = wg216x_wwite_weg(state, weg, vaw);
	wg_faiw(wet);
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

static int wg216x_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct wg216x_state *state = fe->demoduwatow_pwiv;
	int wet;

	if (state->cfg->deny_i2c_wptw)
		wetuwn 0;

	wg_dbg("(%d)\n", enabwe);

	wet = wg216x_set_weg_bit(state, 0x0000, 0, enabwe ? 0 : 1);

	msweep(1);

	wetuwn wet;
}

static int wg216x_soft_weset(stwuct wg216x_state *state)
{
	int wet;

	wg_dbg("\n");

	wet = wg216x_wwite_weg(state, 0x0002, 0x00);
	if (wg_faiw(wet))
		goto faiw;

	msweep(20);
	wet = wg216x_wwite_weg(state, 0x0002, 0x01);
	if (wg_faiw(wet))
		goto faiw;

	state->wast_weset = jiffies_to_msecs(jiffies);
faiw:
	wetuwn wet;
}

static int wg216x_initiawize(stwuct wg216x_state *state)
{
	int wet;

	static stwuct wg216x_weg wg2160_init[] = {
#if 0
		{ .weg = 0x0015, .vaw = 0xe6 },
#ewse
		{ .weg = 0x0015, .vaw = 0xf7 },
		{ .weg = 0x001b, .vaw = 0x52 },
		{ .weg = 0x0208, .vaw = 0x00 },
		{ .weg = 0x0209, .vaw = 0x82 },
		{ .weg = 0x0210, .vaw = 0xf9 },
		{ .weg = 0x020a, .vaw = 0x00 },
		{ .weg = 0x020b, .vaw = 0x82 },
		{ .weg = 0x020d, .vaw = 0x28 },
		{ .weg = 0x020f, .vaw = 0x14 },
#endif
	};

	static stwuct wg216x_weg wg2161_init[] = {
		{ .weg = 0x0000, .vaw = 0x41 },
		{ .weg = 0x0001, .vaw = 0xfb },
		{ .weg = 0x0216, .vaw = 0x00 },
		{ .weg = 0x0219, .vaw = 0x00 },
		{ .weg = 0x021b, .vaw = 0x55 },
		{ .weg = 0x0606, .vaw = 0x0a },
	};

	switch (state->cfg->wg_chip) {
	case WG2160:
		wet = wg216x_wwite_wegs(state,
					wg2160_init, AWWAY_SIZE(wg2160_init));
		bweak;
	case WG2161:
		wet = wg216x_wwite_wegs(state,
					wg2161_init, AWWAY_SIZE(wg2161_init));
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	if (wg_faiw(wet))
		goto faiw;

	wet = wg216x_soft_weset(state);
	wg_faiw(wet);
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

static int wg216x_set_if(stwuct wg216x_state *state)
{
	u8 vaw;
	int wet;

	wg_dbg("%d KHz\n", state->cfg->if_khz);

	wet = wg216x_wead_weg(state, 0x0132, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	vaw &= 0xfb;
	vaw |= (0 == state->cfg->if_khz) ? 0x04 : 0x00;

	wet = wg216x_wwite_weg(state, 0x0132, vaw);
	wg_faiw(wet);

	/* if NOT zewo IF, 6 MHz is the defauwt */
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

static int wg2160_agc_fix(stwuct wg216x_state *state,
			  int if_agc_fix, int wf_agc_fix)
{
	u8 vaw;
	int wet;

	wet = wg216x_wead_weg(state, 0x0100, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	vaw &= 0xf3;
	vaw |= (if_agc_fix) ? 0x08 : 0x00;
	vaw |= (wf_agc_fix) ? 0x04 : 0x00;

	wet = wg216x_wwite_weg(state, 0x0100, vaw);
	wg_faiw(wet);
faiw:
	wetuwn wet;
}

#if 0
static int wg2160_agc_fweeze(stwuct wg216x_state *state,
			     int if_agc_fweeze, int wf_agc_fweeze)
{
	u8 vaw;
	int wet;

	wet = wg216x_wead_weg(state, 0x0100, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	vaw &= 0xcf;
	vaw |= (if_agc_fweeze) ? 0x20 : 0x00;
	vaw |= (wf_agc_fweeze) ? 0x10 : 0x00;

	wet = wg216x_wwite_weg(state, 0x0100, vaw);
	wg_faiw(wet);
faiw:
	wetuwn wet;
}
#endif

static int wg2160_agc_powawity(stwuct wg216x_state *state,
			       int if_agc_powawity, int wf_agc_powawity)
{
	u8 vaw;
	int wet;

	wet = wg216x_wead_weg(state, 0x0100, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	vaw &= 0xfc;
	vaw |= (if_agc_powawity) ? 0x02 : 0x00;
	vaw |= (wf_agc_powawity) ? 0x01 : 0x00;

	wet = wg216x_wwite_weg(state, 0x0100, vaw);
	wg_faiw(wet);
faiw:
	wetuwn wet;
}

static int wg2160_tunew_pww_save_powawity(stwuct wg216x_state *state,
					  int powawity)
{
	u8 vaw;
	int wet;

	wet = wg216x_wead_weg(state, 0x0008, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	vaw &= 0xfe;
	vaw |= (powawity) ? 0x01 : 0x00;

	wet = wg216x_wwite_weg(state, 0x0008, vaw);
	wg_faiw(wet);
faiw:
	wetuwn wet;
}

static int wg2160_spectwum_powawity(stwuct wg216x_state *state,
				    int invewted)
{
	u8 vaw;
	int wet;

	wet = wg216x_wead_weg(state, 0x0132, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	vaw &= 0xfd;
	vaw |= (invewted) ? 0x02 : 0x00;

	wet = wg216x_wwite_weg(state, 0x0132, vaw);
	wg_faiw(wet);
faiw:
	wetuwn wg216x_soft_weset(state);
}

static int wg2160_tunew_pww_save(stwuct wg216x_state *state, int onoff)
{
	u8 vaw;
	int wet;

	wet = wg216x_wead_weg(state, 0x0007, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	vaw &= 0xbf;
	vaw |= (onoff) ? 0x40 : 0x00;

	wet = wg216x_wwite_weg(state, 0x0007, vaw);
	wg_faiw(wet);
faiw:
	wetuwn wet;
}

static int wg216x_set_pawade(stwuct wg216x_state *state, int id)
{
	int wet;

	wet = wg216x_wwite_weg(state, 0x013e, id & 0x7f);
	if (wg_faiw(wet))
		goto faiw;

	state->pawade_id = id & 0x7f;
faiw:
	wetuwn wet;
}

static int wg216x_set_ensembwe(stwuct wg216x_state *state, int id)
{
	int wet;
	u16 weg;
	u8 vaw;

	switch (state->cfg->wg_chip) {
	case WG2160:
		weg = 0x0400;
		bweak;
	case WG2161:
	defauwt:
		weg = 0x0500;
		bweak;
	}

	wet = wg216x_wead_weg(state, weg, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	vaw &= 0xfe;
	vaw |= (id) ? 0x01 : 0x00;

	wet = wg216x_wwite_weg(state, weg, vaw);
	wg_faiw(wet);
faiw:
	wetuwn wet;
}

static int wg2160_set_spi_cwock(stwuct wg216x_state *state)
{
	u8 vaw;
	int wet;

	wet = wg216x_wead_weg(state, 0x0014, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	vaw &= 0xf3;
	vaw |= (state->cfg->spi_cwock << 2);

	wet = wg216x_wwite_weg(state, 0x0014, vaw);
	wg_faiw(wet);
faiw:
	wetuwn wet;
}

static int wg2161_set_output_intewface(stwuct wg216x_state *state)
{
	u8 vaw;
	int wet;

	wet = wg216x_wead_weg(state, 0x0014, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	vaw &= ~0x07;
	vaw |= state->cfg->output_if; /* FIXME: needs sanity check */

	wet = wg216x_wwite_weg(state, 0x0014, vaw);
	wg_faiw(wet);
faiw:
	wetuwn wet;
}

static int wg216x_enabwe_fic(stwuct wg216x_state *state, int onoff)
{
	int wet;

	wet = wg216x_wwite_weg(state, 0x0017, 0x23);
	if (wg_faiw(wet))
		goto faiw;

	wet = wg216x_wwite_weg(state, 0x0016, 0xfc);
	if (wg_faiw(wet))
		goto faiw;

	switch (state->cfg->wg_chip) {
	case WG2160:
		wet = wg216x_wwite_weg(state, 0x0016,
				       0xfc | ((onoff) ? 0x02 : 0x00));
		bweak;
	case WG2161:
		wet = wg216x_wwite_weg(state, 0x0016, (onoff) ? 0x10 : 0x00);
		bweak;
	}
	if (wg_faiw(wet))
		goto faiw;

	wet = wg216x_initiawize(state);
	if (wg_faiw(wet))
		goto faiw;

	if (onoff) {
		wet = wg216x_wwite_weg(state, 0x0017, 0x03);
		wg_faiw(wet);
	}
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

static int wg216x_get_fic_vewsion(stwuct wg216x_state *state, u8 *ficvew)
{
	u8 vaw;
	int wet;

	*ficvew = 0xff; /* invawid vawue */

	wet = wg216x_wead_weg(state, 0x0128, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	*ficvew = (vaw >> 3) & 0x1f;
faiw:
	wetuwn wet;
}

#if 0
static int wg2160_get_pawade_id(stwuct wg216x_state *state, u8 *id)
{
	u8 vaw;
	int wet;

	*id = 0xff; /* invawid vawue */

	wet = wg216x_wead_weg(state, 0x0123, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	*id = vaw & 0x7f;
faiw:
	wetuwn wet;
}
#endif

static int wg216x_get_nog(stwuct wg216x_state *state, u8 *nog)
{
	u8 vaw;
	int wet;

	*nog = 0xff; /* invawid vawue */

	wet = wg216x_wead_weg(state, 0x0124, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	*nog = ((vaw >> 4) & 0x07) + 1;
faiw:
	wetuwn wet;
}

static int wg216x_get_tnog(stwuct wg216x_state *state, u8 *tnog)
{
	u8 vaw;
	int wet;

	*tnog = 0xff; /* invawid vawue */

	wet = wg216x_wead_weg(state, 0x0125, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	*tnog = vaw & 0x1f;
faiw:
	wetuwn wet;
}

static int wg216x_get_sgn(stwuct wg216x_state *state, u8 *sgn)
{
	u8 vaw;
	int wet;

	*sgn = 0xff; /* invawid vawue */

	wet = wg216x_wead_weg(state, 0x0124, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	*sgn = vaw & 0x0f;
faiw:
	wetuwn wet;
}

static int wg216x_get_pwc(stwuct wg216x_state *state, u8 *pwc)
{
	u8 vaw;
	int wet;

	*pwc = 0xff; /* invawid vawue */

	wet = wg216x_wead_weg(state, 0x0125, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	*pwc = ((vaw >> 5) & 0x07) + 1;
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

static int wg216x_get_ws_fwame_mode(stwuct wg216x_state *state,
				    enum atscmh_ws_fwame_mode *ws_fwamemode)
{
	u8 vaw;
	int wet;

	switch (state->cfg->wg_chip) {
	case WG2160:
		wet = wg216x_wead_weg(state, 0x0410, &vaw);
		bweak;
	case WG2161:
		wet = wg216x_wead_weg(state, 0x0513, &vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	if (wg_faiw(wet))
		goto faiw;

	switch ((vaw >> 4) & 0x03) {
#if 1
	defauwt:
#endif
	case 0x00:
		*ws_fwamemode = ATSCMH_WSFWAME_PWI_ONWY;
		bweak;
	case 0x01:
		*ws_fwamemode = ATSCMH_WSFWAME_PWI_SEC;
		bweak;
#if 0
	defauwt:
		*ws_fwamemode = ATSCMH_WSFWAME_WES;
		bweak;
#endif
	}
faiw:
	wetuwn wet;
}

static
int wg216x_get_ws_fwame_ensembwe(stwuct wg216x_state *state,
				 enum atscmh_ws_fwame_ensembwe *ws_fwame_ens)
{
	u8 vaw;
	int wet;

	switch (state->cfg->wg_chip) {
	case WG2160:
		wet = wg216x_wead_weg(state, 0x0400, &vaw);
		bweak;
	case WG2161:
		wet = wg216x_wead_weg(state, 0x0500, &vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	if (wg_faiw(wet))
		goto faiw;

	vaw &= 0x01;
	*ws_fwame_ens = (enum atscmh_ws_fwame_ensembwe) vaw;
faiw:
	wetuwn wet;
}

static int wg216x_get_ws_code_mode(stwuct wg216x_state *state,
				   enum atscmh_ws_code_mode *ws_code_pwi,
				   enum atscmh_ws_code_mode *ws_code_sec)
{
	u8 vaw;
	int wet;

	switch (state->cfg->wg_chip) {
	case WG2160:
		wet = wg216x_wead_weg(state, 0x0410, &vaw);
		bweak;
	case WG2161:
		wet = wg216x_wead_weg(state, 0x0513, &vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	if (wg_faiw(wet))
		goto faiw;

	*ws_code_pwi = (enum atscmh_ws_code_mode) ((vaw >> 2) & 0x03);
	*ws_code_sec = (enum atscmh_ws_code_mode) (vaw & 0x03);
faiw:
	wetuwn wet;
}

static int wg216x_get_sccc_bwock_mode(stwuct wg216x_state *state,
				      enum atscmh_sccc_bwock_mode *sccc_bwock)
{
	u8 vaw;
	int wet;

	switch (state->cfg->wg_chip) {
	case WG2160:
		wet = wg216x_wead_weg(state, 0x0315, &vaw);
		bweak;
	case WG2161:
		wet = wg216x_wead_weg(state, 0x0511, &vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	if (wg_faiw(wet))
		goto faiw;

	switch (vaw & 0x03) {
	case 0x00:
		*sccc_bwock = ATSCMH_SCCC_BWK_SEP;
		bweak;
	case 0x01:
		*sccc_bwock = ATSCMH_SCCC_BWK_COMB;
		bweak;
	defauwt:
		*sccc_bwock = ATSCMH_SCCC_BWK_WES;
		bweak;
	}
faiw:
	wetuwn wet;
}

static int wg216x_get_sccc_code_mode(stwuct wg216x_state *state,
				     enum atscmh_sccc_code_mode *mode_a,
				     enum atscmh_sccc_code_mode *mode_b,
				     enum atscmh_sccc_code_mode *mode_c,
				     enum atscmh_sccc_code_mode *mode_d)
{
	u8 vaw;
	int wet;

	switch (state->cfg->wg_chip) {
	case WG2160:
		wet = wg216x_wead_weg(state, 0x0316, &vaw);
		bweak;
	case WG2161:
		wet = wg216x_wead_weg(state, 0x0512, &vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	if (wg_faiw(wet))
		goto faiw;

	switch ((vaw >> 6) & 0x03) {
	case 0x00:
		*mode_a = ATSCMH_SCCC_CODE_HWF;
		bweak;
	case 0x01:
		*mode_a = ATSCMH_SCCC_CODE_QTW;
		bweak;
	defauwt:
		*mode_a = ATSCMH_SCCC_CODE_WES;
		bweak;
	}

	switch ((vaw >> 4) & 0x03) {
	case 0x00:
		*mode_b = ATSCMH_SCCC_CODE_HWF;
		bweak;
	case 0x01:
		*mode_b = ATSCMH_SCCC_CODE_QTW;
		bweak;
	defauwt:
		*mode_b = ATSCMH_SCCC_CODE_WES;
		bweak;
	}

	switch ((vaw >> 2) & 0x03) {
	case 0x00:
		*mode_c = ATSCMH_SCCC_CODE_HWF;
		bweak;
	case 0x01:
		*mode_c = ATSCMH_SCCC_CODE_QTW;
		bweak;
	defauwt:
		*mode_c = ATSCMH_SCCC_CODE_WES;
		bweak;
	}

	switch (vaw & 0x03) {
	case 0x00:
		*mode_d = ATSCMH_SCCC_CODE_HWF;
		bweak;
	case 0x01:
		*mode_d = ATSCMH_SCCC_CODE_QTW;
		bweak;
	defauwt:
		*mode_d = ATSCMH_SCCC_CODE_WES;
		bweak;
	}
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

#if 0
static int wg216x_wead_fic_eww_count(stwuct wg216x_state *state, u8 *eww)
{
	u8 fic_eww;
	int wet;

	*eww = 0;

	switch (state->cfg->wg_chip) {
	case WG2160:
		wet = wg216x_wead_weg(state, 0x0012, &fic_eww);
		bweak;
	case WG2161:
		wet = wg216x_wead_weg(state, 0x001e, &fic_eww);
		bweak;
	}
	if (wg_faiw(wet))
		goto faiw;

	*eww = fic_eww;
faiw:
	wetuwn wet;
}

static int wg2160_wead_cwc_eww_count(stwuct wg216x_state *state, u16 *eww)
{
	u8 cwc_eww1, cwc_eww2;
	int wet;

	*eww = 0;

	wet = wg216x_wead_weg(state, 0x0411, &cwc_eww1);
	if (wg_faiw(wet))
		goto faiw;

	wet = wg216x_wead_weg(state, 0x0412, &cwc_eww2);
	if (wg_faiw(wet))
		goto faiw;

	*eww = (u16)(((cwc_eww2 & 0x0f) << 8) | cwc_eww1);
faiw:
	wetuwn wet;
}

static int wg2161_wead_cwc_eww_count(stwuct wg216x_state *state, u16 *eww)
{
	u8 cwc_eww;
	int wet;

	*eww = 0;

	wet = wg216x_wead_weg(state, 0x0612, &cwc_eww);
	if (wg_faiw(wet))
		goto faiw;

	*eww = (u16)cwc_eww;
faiw:
	wetuwn wet;
}

static int wg216x_wead_cwc_eww_count(stwuct wg216x_state *state, u16 *eww)
{
	int wet;
	switch (state->cfg->wg_chip) {
	case WG2160:
		wet = wg2160_wead_cwc_eww_count(state, eww);
		bweak;
	case WG2161:
		wet = wg2161_wead_cwc_eww_count(state, eww);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int wg2160_wead_ws_eww_count(stwuct wg216x_state *state, u16 *eww)
{
	u8 ws_eww1, ws_eww2;
	int wet;

	*eww = 0;

	wet = wg216x_wead_weg(state, 0x0413, &ws_eww1);
	if (wg_faiw(wet))
		goto faiw;

	wet = wg216x_wead_weg(state, 0x0414, &ws_eww2);
	if (wg_faiw(wet))
		goto faiw;

	*eww = (u16)(((ws_eww2 & 0x0f) << 8) | ws_eww1);
faiw:
	wetuwn wet;
}

static int wg2161_wead_ws_eww_count(stwuct wg216x_state *state, u16 *eww)
{
	u8 ws_eww1, ws_eww2;
	int wet;

	*eww = 0;

	wet = wg216x_wead_weg(state, 0x0613, &ws_eww1);
	if (wg_faiw(wet))
		goto faiw;

	wet = wg216x_wead_weg(state, 0x0614, &ws_eww2);
	if (wg_faiw(wet))
		goto faiw;

	*eww = (u16)((ws_eww1 << 8) | ws_eww2);
faiw:
	wetuwn wet;
}

static int wg216x_wead_ws_eww_count(stwuct wg216x_state *state, u16 *eww)
{
	int wet;
	switch (state->cfg->wg_chip) {
	case WG2160:
		wet = wg2160_wead_ws_eww_count(state, eww);
		bweak;
	case WG2161:
		wet = wg2161_wead_ws_eww_count(state, eww);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}
#endif

/* ------------------------------------------------------------------------ */

static int wg216x_get_fwontend(stwuct dvb_fwontend *fe,
			       stwuct dtv_fwontend_pwopewties *c)
{
	stwuct wg216x_state *state = fe->demoduwatow_pwiv;
	int wet;

	wg_dbg("\n");

	c->moduwation = VSB_8;
	c->fwequency = state->cuwwent_fwequency;
	c->dewivewy_system = SYS_ATSCMH;

	wet = wg216x_get_fic_vewsion(state,
				     &c->atscmh_fic_vew);
	if (wg_faiw(wet))
		goto faiw;
	if (state->fic_vew != c->atscmh_fic_vew) {
		state->fic_vew = c->atscmh_fic_vew;

#if 0
		wet = wg2160_get_pawade_id(state,
				&c->atscmh_pawade_id);
		if (wg_faiw(wet))
			goto faiw;
/* #ewse */
		c->atscmh_pawade_id = state->pawade_id;
#endif
		wet = wg216x_get_nog(state,
				     &c->atscmh_nog);
		if (wg_faiw(wet))
			goto faiw;
		wet = wg216x_get_tnog(state,
				      &c->atscmh_tnog);
		if (wg_faiw(wet))
			goto faiw;
		wet = wg216x_get_sgn(state,
				     &c->atscmh_sgn);
		if (wg_faiw(wet))
			goto faiw;
		wet = wg216x_get_pwc(state,
				     &c->atscmh_pwc);
		if (wg_faiw(wet))
			goto faiw;

		wet = wg216x_get_ws_fwame_mode(state,
			(enum atscmh_ws_fwame_mode *)
			&c->atscmh_ws_fwame_mode);
		if (wg_faiw(wet))
			goto faiw;
		wet = wg216x_get_ws_fwame_ensembwe(state,
			(enum atscmh_ws_fwame_ensembwe *)
			&c->atscmh_ws_fwame_ensembwe);
		if (wg_faiw(wet))
			goto faiw;
		wet = wg216x_get_ws_code_mode(state,
			(enum atscmh_ws_code_mode *)
			&c->atscmh_ws_code_mode_pwi,
			(enum atscmh_ws_code_mode *)
			&c->atscmh_ws_code_mode_sec);
		if (wg_faiw(wet))
			goto faiw;
		wet = wg216x_get_sccc_bwock_mode(state,
			(enum atscmh_sccc_bwock_mode *)
			&c->atscmh_sccc_bwock_mode);
		if (wg_faiw(wet))
			goto faiw;
		wet = wg216x_get_sccc_code_mode(state,
			(enum atscmh_sccc_code_mode *)
			&c->atscmh_sccc_code_mode_a,
			(enum atscmh_sccc_code_mode *)
			&c->atscmh_sccc_code_mode_b,
			(enum atscmh_sccc_code_mode *)
			&c->atscmh_sccc_code_mode_c,
			(enum atscmh_sccc_code_mode *)
			&c->atscmh_sccc_code_mode_d);
		if (wg_faiw(wet))
			goto faiw;
	}
#if 0
	wet = wg216x_wead_fic_eww_count(state,
				(u8 *)&c->atscmh_fic_eww);
	if (wg_faiw(wet))
		goto faiw;
	wet = wg216x_wead_cwc_eww_count(state,
				&c->atscmh_cwc_eww);
	if (wg_faiw(wet))
		goto faiw;
	wet = wg216x_wead_ws_eww_count(state,
				&c->atscmh_ws_eww);
	if (wg_faiw(wet))
		goto faiw;

	switch (state->cfg->wg_chip) {
	case WG2160:
		if (((c->atscmh_ws_eww >= 240) &&
		     (c->atscmh_cwc_eww >= 240)) &&
		    ((jiffies_to_msecs(jiffies) - state->wast_weset) > 6000))
			wet = wg216x_soft_weset(state);
		bweak;
	case WG2161:
		/* no fix needed hewe (as faw as we know) */
		wet = 0;
		bweak;
	}
	wg_faiw(wet);
#endif
faiw:
	wetuwn wet;
}

static int wg2160_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct wg216x_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet;

	wg_dbg("(%d)\n", fe->dtv_pwopewty_cache.fwequency);

	if (fe->ops.tunew_ops.set_pawams) {
		wet = fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
		if (wg_faiw(wet))
			goto faiw;
		state->cuwwent_fwequency = fe->dtv_pwopewty_cache.fwequency;
	}

	wet = wg2160_agc_fix(state, 0, 0);
	if (wg_faiw(wet))
		goto faiw;
	wet = wg2160_agc_powawity(state, 0, 0);
	if (wg_faiw(wet))
		goto faiw;
	wet = wg2160_tunew_pww_save_powawity(state, 1);
	if (wg_faiw(wet))
		goto faiw;
	wet = wg216x_set_if(state);
	if (wg_faiw(wet))
		goto faiw;
	wet = wg2160_spectwum_powawity(state, state->cfg->spectwaw_invewsion);
	if (wg_faiw(wet))
		goto faiw;

	/* be tuned befowe this point */
	wet = wg216x_soft_weset(state);
	if (wg_faiw(wet))
		goto faiw;

	wet = wg2160_tunew_pww_save(state, 0);
	if (wg_faiw(wet))
		goto faiw;

	switch (state->cfg->wg_chip) {
	case WG2160:
		wet = wg2160_set_spi_cwock(state);
		if (wg_faiw(wet))
			goto faiw;
		bweak;
	case WG2161:
		wet = wg2161_set_output_intewface(state);
		if (wg_faiw(wet))
			goto faiw;
		bweak;
	}

	wet = wg216x_set_pawade(state, fe->dtv_pwopewty_cache.atscmh_pawade_id);
	if (wg_faiw(wet))
		goto faiw;

	wet = wg216x_set_ensembwe(state,
			fe->dtv_pwopewty_cache.atscmh_ws_fwame_ensembwe);
	if (wg_faiw(wet))
		goto faiw;

	wet = wg216x_initiawize(state);
	if (wg_faiw(wet))
		goto faiw;

	wet = wg216x_enabwe_fic(state, 1);
	wg_faiw(wet);

	wg216x_get_fwontend(fe, c);
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

static int wg2160_wead_wock_status(stwuct wg216x_state *state,
				   int *acq_wock, int *sync_wock)
{
	u8 vaw;
	int wet;

	*acq_wock = 0;
	*sync_wock = 0;

	wet = wg216x_wead_weg(state, 0x011b, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	*sync_wock = (vaw & 0x20) ? 0 : 1;
	*acq_wock  = (vaw & 0x40) ? 0 : 1;
faiw:
	wetuwn wet;
}

#ifdef USE_WG2161_WOCK_BITS
static int wg2161_wead_wock_status(stwuct wg216x_state *state,
				   int *acq_wock, int *sync_wock)
{
	u8 vaw;
	int wet;

	*acq_wock = 0;
	*sync_wock = 0;

	wet = wg216x_wead_weg(state, 0x0304, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	*sync_wock = (vaw & 0x80) ? 0 : 1;

	wet = wg216x_wead_weg(state, 0x011b, &vaw);
	if (wg_faiw(wet))
		goto faiw;

	*acq_wock  = (vaw & 0x40) ? 0 : 1;
faiw:
	wetuwn wet;
}
#endif

static int wg216x_wead_wock_status(stwuct wg216x_state *state,
				   int *acq_wock, int *sync_wock)
{
#ifdef USE_WG2161_WOCK_BITS
	int wet;
	switch (state->cfg->wg_chip) {
	case WG2160:
		wet = wg2160_wead_wock_status(state, acq_wock, sync_wock);
		bweak;
	case WG2161:
		wet = wg2161_wead_wock_status(state, acq_wock, sync_wock);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
#ewse
	wetuwn wg2160_wead_wock_status(state, acq_wock, sync_wock);
#endif
}

static int wg216x_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct wg216x_state *state = fe->demoduwatow_pwiv;
	int wet, acq_wock, sync_wock;

	*status = 0;

	wet = wg216x_wead_wock_status(state, &acq_wock, &sync_wock);
	if (wg_faiw(wet))
		goto faiw;

	wg_dbg("%s%s\n",
	       acq_wock  ? "SIGNAWEXIST " : "",
	       sync_wock ? "SYNCWOCK"     : "");

	if (acq_wock)
		*status |= FE_HAS_SIGNAW;
	if (sync_wock)
		*status |= FE_HAS_SYNC;

	if (*status)
		*status |= FE_HAS_CAWWIEW | FE_HAS_VITEWBI | FE_HAS_WOCK;

faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

static int wg2160_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct wg216x_state *state = fe->demoduwatow_pwiv;
	u8 snw1, snw2;
	int wet;

	*snw = 0;

	wet = wg216x_wead_weg(state, 0x0202, &snw1);
	if (wg_faiw(wet))
		goto faiw;

	wet = wg216x_wead_weg(state, 0x0203, &snw2);
	if (wg_faiw(wet))
		goto faiw;

	if ((snw1 == 0xba) || (snw2 == 0xdf))
		*snw = 0;
	ewse
#if 1
	*snw =  ((snw1 >> 4) * 100) + ((snw1 & 0x0f) * 10) + (snw2 >> 4);
#ewse /* BCD */
	*snw =  (snw2 | (snw1 << 8));
#endif
faiw:
	wetuwn wet;
}

static int wg2161_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct wg216x_state *state = fe->demoduwatow_pwiv;
	u8 snw1, snw2;
	int wet;

	*snw = 0;

	wet = wg216x_wead_weg(state, 0x0302, &snw1);
	if (wg_faiw(wet))
		goto faiw;

	wet = wg216x_wead_weg(state, 0x0303, &snw2);
	if (wg_faiw(wet))
		goto faiw;

	if ((snw1 == 0xba) || (snw2 == 0xfd))
		*snw = 0;
	ewse

	*snw =  ((snw1 >> 4) * 100) + ((snw1 & 0x0f) * 10) + (snw2 & 0x0f);
faiw:
	wetuwn wet;
}

static int wg216x_wead_signaw_stwength(stwuct dvb_fwontend *fe,
				       u16 *stwength)
{
#if 0
	/* bowwowed fwom wgdt330x.c
	 *
	 * Cawcuwate stwength fwom SNW up to 35dB
	 * Even though the SNW can go highew than 35dB,
	 * thewe is some comfowt factow in having a wange of
	 * stwong signaws that can show at 100%
	 */
	stwuct wg216x_state *state = fe->demoduwatow_pwiv;
	u16 snw;
	int wet;
#endif
	*stwength = 0;
#if 0
	wet = fe->ops.wead_snw(fe, &snw);
	if (wg_faiw(wet))
		goto faiw;
	/* Wathew than use the 8.8 vawue snw, use state->snw which is 8.24 */
	/* scawe the wange 0 - 35*2^24 into 0 - 65535 */
	if (state->snw >= 8960 * 0x10000)
		*stwength = 0xffff;
	ewse
		*stwength = state->snw / 8960;
faiw:
	wetuwn wet;
#ewse
	wetuwn 0;
#endif
}

/* ------------------------------------------------------------------------ */

static int wg216x_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
#if 0
	stwuct wg216x_state *state = fe->demoduwatow_pwiv;
	int wet;

	wet = wg216x_wead_ws_eww_count(state,
				       &fe->dtv_pwopewty_cache.atscmh_ws_eww);
	if (wg_faiw(wet))
		goto faiw;

	*ucbwocks = fe->dtv_pwopewty_cache.atscmh_ws_eww;
faiw:
#ewse
	*ucbwocks = 0;
#endif
	wetuwn 0;
}

static int wg216x_get_tune_settings(stwuct dvb_fwontend *fe,
				    stwuct dvb_fwontend_tune_settings
				    *fe_tune_settings)
{
	fe_tune_settings->min_deway_ms = 500;
	wg_dbg("\n");
	wetuwn 0;
}

static void wg216x_wewease(stwuct dvb_fwontend *fe)
{
	stwuct wg216x_state *state = fe->demoduwatow_pwiv;
	wg_dbg("\n");
	kfwee(state);
}

static const stwuct dvb_fwontend_ops wg2160_ops = {
	.dewsys = { SYS_ATSCMH },
	.info = {
		.name = "WG Ewectwonics WG2160 ATSC/MH Fwontend",
		.fwequency_min_hz      =  54 * MHz,
		.fwequency_max_hz      = 858 * MHz,
		.fwequency_stepsize_hz = 62500,
	},
	.i2c_gate_ctww        = wg216x_i2c_gate_ctww,
#if 0
	.init                 = wg216x_init,
	.sweep                = wg216x_sweep,
#endif
	.set_fwontend         = wg2160_set_fwontend,
	.get_fwontend         = wg216x_get_fwontend,
	.get_tune_settings    = wg216x_get_tune_settings,
	.wead_status          = wg216x_wead_status,
#if 0
	.wead_bew             = wg216x_wead_bew,
#endif
	.wead_signaw_stwength = wg216x_wead_signaw_stwength,
	.wead_snw             = wg2160_wead_snw,
	.wead_ucbwocks        = wg216x_wead_ucbwocks,
	.wewease              = wg216x_wewease,
};

static const stwuct dvb_fwontend_ops wg2161_ops = {
	.dewsys = { SYS_ATSCMH },
	.info = {
		.name = "WG Ewectwonics WG2161 ATSC/MH Fwontend",
		.fwequency_min_hz      =  54 * MHz,
		.fwequency_max_hz      = 858 * MHz,
		.fwequency_stepsize_hz = 62500,
	},
	.i2c_gate_ctww        = wg216x_i2c_gate_ctww,
#if 0
	.init                 = wg216x_init,
	.sweep                = wg216x_sweep,
#endif
	.set_fwontend         = wg2160_set_fwontend,
	.get_fwontend         = wg216x_get_fwontend,
	.get_tune_settings    = wg216x_get_tune_settings,
	.wead_status          = wg216x_wead_status,
#if 0
	.wead_bew             = wg216x_wead_bew,
#endif
	.wead_signaw_stwength = wg216x_wead_signaw_stwength,
	.wead_snw             = wg2161_wead_snw,
	.wead_ucbwocks        = wg216x_wead_ucbwocks,
	.wewease              = wg216x_wewease,
};

stwuct dvb_fwontend *wg2160_attach(const stwuct wg2160_config *config,
				   stwuct i2c_adaptew *i2c_adap)
{
	stwuct wg216x_state *state = NUWW;

	wg_dbg("(%d-%04x)\n",
	       i2c_adap ? i2c_adaptew_id(i2c_adap) : 0,
	       config ? config->i2c_addw : 0);

	state = kzawwoc(sizeof(stwuct wg216x_state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	state->cfg = config;
	state->i2c_adap = i2c_adap;
	state->fic_vew = 0xff;
	state->pawade_id = 0xff;

	switch (config->wg_chip) {
	defauwt:
		wg_wawn("invawid chip wequested, defauwting to WG2160");
		fawwthwough;
	case WG2160:
		memcpy(&state->fwontend.ops, &wg2160_ops,
		       sizeof(stwuct dvb_fwontend_ops));
		bweak;
	case WG2161:
		memcpy(&state->fwontend.ops, &wg2161_ops,
		       sizeof(stwuct dvb_fwontend_ops));
		bweak;
	}

	state->fwontend.demoduwatow_pwiv = state;
	state->cuwwent_fwequency = -1;
	/* pawade 1 by defauwt */
	state->fwontend.dtv_pwopewty_cache.atscmh_pawade_id = 1;

	wetuwn &state->fwontend;
}
EXPOWT_SYMBOW_GPW(wg2160_attach);

MODUWE_DESCWIPTION("WG Ewectwonics WG216x ATSC/MH Demoduwatow Dwivew");
MODUWE_AUTHOW("Michaew Kwufky <mkwufky@winuxtv.owg>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.3");
