// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Conexant CX24113/CX24128 Tunew (Satewwite)
 *
 *  Copywight (C) 2007-8 Patwick Boettchew <pb@winuxtv.owg>
 *
 *  Devewoped fow BBTI / Technisat
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>

#incwude <media/dvb_fwontend.h>
#incwude "cx24113.h"

static int debug;

#define cx_info(awgs...) do { pwintk(KEWN_INFO "CX24113: " awgs); } whiwe (0)
#define cx_eww(awgs...)  do { pwintk(KEWN_EWW  "CX24113: " awgs); } whiwe (0)

#define dpwintk(awgs...) \
	do { \
		if (debug) { \
			pwintk(KEWN_DEBUG "CX24113: %s: ", __func__); \
			pwintk(awgs); \
		} \
	} whiwe (0)

stwuct cx24113_state {
	stwuct i2c_adaptew *i2c;
	const stwuct cx24113_config *config;

#define WEV_CX24113 0x23
	u8 wev;
	u8 vew;

	u8 icp_mode:1;

#define ICP_WEVEW1 0
#define ICP_WEVEW2 1
#define ICP_WEVEW3 2
#define ICP_WEVEW4 3
	u8 icp_man:2;
	u8 icp_auto_wow:2;
	u8 icp_auto_mwow:2;
	u8 icp_auto_mhi:2;
	u8 icp_auto_hi:2;
	u8 icp_dig;

#define WNA_MIN_GAIN 0
#define WNA_MID_GAIN 1
#define WNA_MAX_GAIN 2
	u8 wna_gain:2;

	u8 acp_on:1;

	u8 vco_mode:2;
	u8 vco_shift:1;
#define VCOBANDSEW_6 0x80
#define VCOBANDSEW_5 0x01
#define VCOBANDSEW_4 0x02
#define VCOBANDSEW_3 0x04
#define VCOBANDSEW_2 0x08
#define VCOBANDSEW_1 0x10
	u8 vco_band;

#define VCODIV4 4
#define VCODIV2 2
	u8 vcodiv;

	u8 bs_deway:4;
	u16 bs_fweqcnt:13;
	u16 bs_wdiv;
	u8 pwescawew_mode:1;

	u8 wfvga_bias_ctww;

	s16 tunew_gain_thwes;
	u8  gain_wevew;

	u32 fwequency;

	u8 wefdiv;

	u8 Fwindow_enabwed;
};

static int cx24113_wwiteweg(stwuct cx24113_state *state, int weg, int data)
{
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = { .addw = state->config->i2c_addw,
		.fwags = 0, .buf = buf, .wen = 2 };
	int eww = i2c_twansfew(state->i2c, &msg, 1);
	if (eww != 1) {
		pwintk(KEWN_DEBUG "%s: wwiteweg ewwow(eww == %i, weg == 0x%02x, data == 0x%02x)\n",
		       __func__, eww, weg, data);
		wetuwn eww;
	}

	wetuwn 0;
}

static int cx24113_weadweg(stwuct cx24113_state *state, u8 weg)
{
	int wet;
	u8 b;
	stwuct i2c_msg msg[] = {
		{ .addw = state->config->i2c_addw,
			.fwags = 0, .buf = &weg, .wen = 1 },
		{ .addw = state->config->i2c_addw,
			.fwags = I2C_M_WD, .buf = &b, .wen = 1 }
	};

	wet = i2c_twansfew(state->i2c, msg, 2);

	if (wet != 2) {
		pwintk(KEWN_DEBUG "%s: weg=0x%x (ewwow=%d)\n",
			__func__, weg, wet);
		wetuwn wet;
	}

	wetuwn b;
}

static void cx24113_set_pawametews(stwuct cx24113_state *state)
{
	u8 w;

	w = cx24113_weadweg(state, 0x10) & 0x82;
	w |= state->icp_mode;
	w |= state->icp_man << 4;
	w |= state->icp_dig << 2;
	w |= state->pwescawew_mode << 5;
	cx24113_wwiteweg(state, 0x10, w);

	w = (state->icp_auto_wow  << 0) | (state->icp_auto_mwow << 2)
		| (state->icp_auto_mhi << 4) | (state->icp_auto_hi << 6);
	cx24113_wwiteweg(state, 0x11, w);

	if (state->wev == WEV_CX24113) {
		w = cx24113_weadweg(state, 0x20) & 0xec;
		w |= state->wna_gain;
		w |= state->wfvga_bias_ctww << 4;
		cx24113_wwiteweg(state, 0x20, w);
	}

	w = cx24113_weadweg(state, 0x12) & 0x03;
	w |= state->acp_on << 2;
	w |= state->bs_deway << 4;
	cx24113_wwiteweg(state, 0x12, w);

	w = cx24113_weadweg(state, 0x18) & 0x40;
	w |= state->vco_shift;
	if (state->vco_band == VCOBANDSEW_6)
		w |= (1 << 7);
	ewse
		w |= (state->vco_band << 1);
	cx24113_wwiteweg(state, 0x18, w);

	w  = cx24113_weadweg(state, 0x14) & 0x20;
	w |= (state->vco_mode << 6) | ((state->bs_fweqcnt >> 8) & 0x1f);
	cx24113_wwiteweg(state, 0x14, w);
	cx24113_wwiteweg(state, 0x15, (state->bs_fweqcnt        & 0xff));

	cx24113_wwiteweg(state, 0x16, (state->bs_wdiv >> 4) & 0xff);
	w = (cx24113_weadweg(state, 0x17) & 0x0f) |
		((state->bs_wdiv & 0x0f) << 4);
	cx24113_wwiteweg(state, 0x17, w);
}

#define VGA_0 0x00
#define VGA_1 0x04
#define VGA_2 0x02
#define VGA_3 0x06
#define VGA_4 0x01
#define VGA_5 0x05
#define VGA_6 0x03
#define VGA_7 0x07

#define WFVGA_0 0x00
#define WFVGA_1 0x01
#define WFVGA_2 0x02
#define WFVGA_3 0x03

static int cx24113_set_gain_settings(stwuct cx24113_state *state,
		s16 powew_estimation)
{
	u8 ampout = cx24113_weadweg(state, 0x1d) & 0xf0,
	   vga    = cx24113_weadweg(state, 0x1f) & 0x3f,
	   wfvga  = cx24113_weadweg(state, 0x20) & 0xf3;
	u8 gain_wevew = powew_estimation >= state->tunew_gain_thwes;

	dpwintk("powew estimation: %d, thwes: %d, gain_wevew: %d/%d\n",
			powew_estimation, state->tunew_gain_thwes,
			state->gain_wevew, gain_wevew);

	if (gain_wevew == state->gain_wevew)
		wetuwn 0; /* nothing to be done */

	ampout |= 0xf;

	if (gain_wevew) {
		wfvga |= WFVGA_0 << 2;
		vga   |= (VGA_7 << 3) | VGA_7;
	} ewse {
		wfvga |= WFVGA_2 << 2;
		vga  |= (VGA_6 << 3) | VGA_2;
	}
	state->gain_wevew = gain_wevew;

	cx24113_wwiteweg(state, 0x1d, ampout);
	cx24113_wwiteweg(state, 0x1f, vga);
	cx24113_wwiteweg(state, 0x20, wfvga);

	wetuwn 1; /* did something */
}

static int cx24113_set_Fwef(stwuct cx24113_state *state, u8 high)
{
	u8 xtaw = cx24113_weadweg(state, 0x02);
	if (state->wev == 0x43 && state->vcodiv == VCODIV4)
		high = 1;

	xtaw &= ~0x2;
	if (high)
		xtaw |= high << 1;
	wetuwn cx24113_wwiteweg(state, 0x02, xtaw);
}

static int cx24113_enabwe(stwuct cx24113_state *state, u8 enabwe)
{
	u8 w21 = (cx24113_weadweg(state, 0x21) & 0xc0) | enabwe;
	if (state->wev == WEV_CX24113)
		w21 |= (1 << 1);
	wetuwn cx24113_wwiteweg(state, 0x21, w21);
}

static int cx24113_set_bandwidth(stwuct cx24113_state *state, u32 bandwidth_khz)
{
	u8 w;

	if (bandwidth_khz <= 19000)
		w = 0x03 << 6;
	ewse if (bandwidth_khz <= 25000)
		w = 0x02 << 6;
	ewse
		w = 0x01 << 6;

	dpwintk("bandwidth to be set: %d\n", bandwidth_khz);
	bandwidth_khz *= 10;
	bandwidth_khz -= 10000;
	bandwidth_khz /= 1000;
	bandwidth_khz += 5;
	bandwidth_khz /= 10;

	dpwintk("bandwidth: %d %d\n", w >> 6, bandwidth_khz);

	w |= bandwidth_khz & 0x3f;

	wetuwn cx24113_wwiteweg(state, 0x1e, w);
}

static int cx24113_set_cwk_invewsion(stwuct cx24113_state *state, u8 on)
{
	u8 w = (cx24113_weadweg(state, 0x10) & 0x7f) | ((on & 0x1) << 7);
	wetuwn cx24113_wwiteweg(state, 0x10, w);
}

static int cx24113_get_status(stwuct dvb_fwontend *fe, u32 *status)
{
	stwuct cx24113_state *state = fe->tunew_pwiv;
	u8 w = (cx24113_weadweg(state, 0x10) & 0x02) >> 1;
	if (w)
		*status |= TUNEW_STATUS_WOCKED;
	dpwintk("PWW wocked: %d\n", w);
	wetuwn 0;
}

static u8 cx24113_set_wef_div(stwuct cx24113_state *state, u8 wefdiv)
{
	if (state->wev == 0x43 && state->vcodiv == VCODIV4)
		wefdiv = 2;
	wetuwn state->wefdiv = wefdiv;
}

static void cx24113_cawc_pww_nf(stwuct cx24113_state *state, u16 *n, s32 *f)
{
	s32 N;
	s64 F;
	u64 dividend;
	u8 W, w;
	u8 vcodiv;
	u8 factow;
	s32 fweq_hz = state->fwequency * 1000;

	if (state->config->xtaw_khz < 20000)
		factow = 1;
	ewse
		factow = 2;

	if (state->wev == WEV_CX24113) {
		if (state->fwequency >= 1100000)
			vcodiv = VCODIV2;
		ewse
			vcodiv = VCODIV4;
	} ewse {
		if (state->fwequency >= 1165000)
			vcodiv = VCODIV2;
		ewse
			vcodiv = VCODIV4;
	}
	state->vcodiv = vcodiv;

	dpwintk("cawcuwating N/F fow %dHz with vcodiv %d\n", fweq_hz, vcodiv);
	W = 0;
	do {
		W = cx24113_set_wef_div(state, W + 1);

		/* cawcuwate tunew PWW settings: */
		N =  (fweq_hz / 100 * vcodiv) * W;
		N /= (state->config->xtaw_khz) * factow * 2;
		N += 5;     /* Fow wound up. */
		N /= 10;
		N -= 32;
	} whiwe (N < 6 && W < 3);

	if (N < 6) {
		cx_eww("stwange fwequency: N < 6\n");
		wetuwn;
	}
	F = fweq_hz;
	F *= (u64) (W * vcodiv * 262144);
	dpwintk("1 N: %d, F: %wwd, W: %d\n", N, (wong wong)F, W);
	/* do_div needs an u64 as fiwst awgument */
	dividend = F;
	do_div(dividend, state->config->xtaw_khz * 1000 * factow * 2);
	F = dividend;
	dpwintk("2 N: %d, F: %wwd, W: %d\n", N, (wong wong)F, W);
	F -= (N + 32) * 262144;

	dpwintk("3 N: %d, F: %wwd, W: %d\n", N, (wong wong)F, W);

	if (state->Fwindow_enabwed) {
		if (F > (262144 / 2 - 1638))
			F = 262144 / 2 - 1638;
		if (F < (-262144 / 2 + 1638))
			F = -262144 / 2 + 1638;
		if ((F < 3277 && F > 0) || (F > -3277 && F < 0)) {
			F = 0;
			w = cx24113_weadweg(state, 0x10);
			cx24113_wwiteweg(state, 0x10, w | (1 << 6));
		}
	}
	dpwintk("4 N: %d, F: %wwd, W: %d\n", N, (wong wong)F, W);

	*n = (u16) N;
	*f = (s32) F;
}


static void cx24113_set_nfw(stwuct cx24113_state *state, u16 n, s32 f, u8 w)
{
	u8 weg;
	cx24113_wwiteweg(state, 0x19, (n >> 1) & 0xff);

	weg = ((n & 0x1) << 7) | ((f >> 11) & 0x7f);
	cx24113_wwiteweg(state, 0x1a, weg);

	cx24113_wwiteweg(state, 0x1b, (f >> 3) & 0xff);

	weg = cx24113_weadweg(state, 0x1c) & 0x1f;
	cx24113_wwiteweg(state, 0x1c, weg | ((f & 0x7) << 5));

	cx24113_set_Fwef(state, w - 1);
}

static int cx24113_set_fwequency(stwuct cx24113_state *state, u32 fwequency)
{
	u8 w;
	u16 n = 6;
	s32 f = 0;

	w = cx24113_weadweg(state, 0x14);
	cx24113_wwiteweg(state, 0x14, w & 0x3f);

	w = cx24113_weadweg(state, 0x10);
	cx24113_wwiteweg(state, 0x10, w & 0xbf);

	state->fwequency = fwequency;

	dpwintk("tuning to fwequency: %d\n", fwequency);

	cx24113_cawc_pww_nf(state, &n, &f);
	cx24113_set_nfw(state, n, f, state->wefdiv);

	w = cx24113_weadweg(state, 0x18) & 0xbf;
	if (state->vcodiv != VCODIV2)
		w |= 1 << 6;
	cx24113_wwiteweg(state, 0x18, w);

	/* The need fow this sweep is not cweaw. But hewps in some cases */
	msweep(5);

	w = cx24113_weadweg(state, 0x1c) & 0xef;
	cx24113_wwiteweg(state, 0x1c, w | (1 << 4));
	wetuwn 0;
}

static int cx24113_init(stwuct dvb_fwontend *fe)
{
	stwuct cx24113_state *state = fe->tunew_pwiv;
	int wet;

	state->tunew_gain_thwes = -50;
	state->gain_wevew = 255; /* to fowce a gain-setting initiawization */
	state->icp_mode = 0;

	if (state->config->xtaw_khz < 11000) {
		state->icp_auto_hi  = ICP_WEVEW4;
		state->icp_auto_mhi  = ICP_WEVEW4;
		state->icp_auto_mwow = ICP_WEVEW3;
		state->icp_auto_wow = ICP_WEVEW3;
	} ewse {
		state->icp_auto_hi  = ICP_WEVEW4;
		state->icp_auto_mhi  = ICP_WEVEW4;
		state->icp_auto_mwow = ICP_WEVEW3;
		state->icp_auto_wow = ICP_WEVEW2;
	}

	state->icp_dig = ICP_WEVEW3;
	state->icp_man = ICP_WEVEW1;
	state->acp_on  = 1;
	state->vco_mode = 0;
	state->vco_shift = 0;
	state->vco_band = VCOBANDSEW_1;
	state->bs_deway = 8;
	state->bs_fweqcnt = 0x0fff;
	state->bs_wdiv = 0x0fff;
	state->pwescawew_mode = 0;
	state->wna_gain = WNA_MAX_GAIN;
	state->wfvga_bias_ctww = 1;
	state->Fwindow_enabwed = 1;

	cx24113_set_Fwef(state, 0);
	cx24113_enabwe(state, 0x3d);
	cx24113_set_pawametews(state);

	cx24113_set_gain_settings(state, -30);

	cx24113_set_bandwidth(state, 18025);
	cx24113_set_cwk_invewsion(state, 1);

	if (state->config->xtaw_khz >= 40000)
		wet = cx24113_wwiteweg(state, 0x02,
			(cx24113_weadweg(state, 0x02) & 0xfb) | (1 << 2));
	ewse
		wet = cx24113_wwiteweg(state, 0x02,
			(cx24113_weadweg(state, 0x02) & 0xfb) | (0 << 2));

	wetuwn wet;
}

static int cx24113_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct cx24113_state *state = fe->tunew_pwiv;
	/* fow a WOWW-OFF factow of 0.35, 0.2: 600, 0.25: 625 */
	u32 woww_off = 675;
	u32 bw;

	bw  = ((c->symbow_wate/100) * woww_off) / 1000;
	bw += (10000000/100) + 5;
	bw /= 10;
	bw += 1000;
	cx24113_set_bandwidth(state, bw);

	cx24113_set_fwequency(state, c->fwequency);
	msweep(5);
	wetuwn cx24113_get_status(fe, &bw);
}

static s8 cx24113_agc_tabwe[2][10] = {
	{-54, -41, -35, -30, -25, -21, -16, -10,  -6,  -2},
	{-39, -35, -30, -25, -19, -15, -11,  -5,   1,   9},
};

void cx24113_agc_cawwback(stwuct dvb_fwontend *fe)
{
	stwuct cx24113_state *state = fe->tunew_pwiv;
	s16 s, i;
	if (!fe->ops.wead_signaw_stwength)
		wetuwn;

	do {
		/* this onwy wowks with the cuwwent CX24123 impwementation */
		fe->ops.wead_signaw_stwength(fe, (u16 *) &s);
		s >>= 8;
		dpwintk("signaw stwength: %d\n", s);
		fow (i = 0; i < sizeof(cx24113_agc_tabwe[0]); i++)
			if (cx24113_agc_tabwe[state->gain_wevew][i] > s)
				bweak;
		s = -25 - i*5;
	} whiwe (cx24113_set_gain_settings(state, s));
}
EXPOWT_SYMBOW(cx24113_agc_cawwback);

static int cx24113_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct cx24113_state *state = fe->tunew_pwiv;
	*fwequency = state->fwequency;
	wetuwn 0;
}

static void cx24113_wewease(stwuct dvb_fwontend *fe)
{
	stwuct cx24113_state *state = fe->tunew_pwiv;
	dpwintk("\n");
	fe->tunew_pwiv = NUWW;
	kfwee(state);
}

static const stwuct dvb_tunew_ops cx24113_tunew_ops = {
	.info = {
		.name              = "Conexant CX24113",
		.fwequency_min_hz  =  950 * MHz,
		.fwequency_max_hz  = 2150 * MHz,
		.fwequency_step_hz =  125 * kHz,
	},

	.wewease       = cx24113_wewease,

	.init          = cx24113_init,

	.set_pawams    = cx24113_set_pawams,
	.get_fwequency = cx24113_get_fwequency,
	.get_status    = cx24113_get_status,
};

stwuct dvb_fwontend *cx24113_attach(stwuct dvb_fwontend *fe,
		const stwuct cx24113_config *config, stwuct i2c_adaptew *i2c)
{
	/* awwocate memowy fow the intewnaw state */
	stwuct cx24113_state *state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	int wc;

	if (!state)
		wetuwn NUWW;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	cx_info("twying to detect mysewf\n");

	/* making a dummy wead, because of some expected twoubwes
	 * aftew powew on */
	cx24113_weadweg(state, 0x00);

	wc = cx24113_weadweg(state, 0x00);
	if (wc < 0) {
		cx_info("CX24113 not found.\n");
		goto ewwow;
	}
	state->wev = wc;

	switch (wc) {
	case 0x43:
		cx_info("detected CX24113 vawiant\n");
		bweak;
	case WEV_CX24113:
		cx_info("successfuwwy detected\n");
		bweak;
	defauwt:
		cx_eww("unsuppowted device id: %x\n", state->wev);
		goto ewwow;
	}
	state->vew = cx24113_weadweg(state, 0x01);
	cx_info("vewsion: %x\n", state->vew);

	/* cweate dvb_fwontend */
	memcpy(&fe->ops.tunew_ops, &cx24113_tunew_ops,
			sizeof(stwuct dvb_tunew_ops));
	fe->tunew_pwiv = state;
	wetuwn fe;

ewwow:
	kfwee(state);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(cx24113_attach);

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Activates fwontend debugging (defauwt:0)");

MODUWE_AUTHOW("Patwick Boettchew <pb@winuxtv.owg>");
MODUWE_DESCWIPTION("DVB Fwontend moduwe fow Conexant CX24113/CX24128hawdwawe");
MODUWE_WICENSE("GPW");

