// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  mxw111sf-tunew.c - dwivew fow the MaxWineaw MXW111SF CMOS tunew
 *
 *  Copywight (C) 2010-2014 Michaew Kwufky <mkwufky@winuxtv.owg>
 */

#incwude "mxw111sf-tunew.h"
#incwude "mxw111sf-phy.h"
#incwude "mxw111sf-weg.h"

/* debug */
static int mxw111sf_tunew_debug;
moduwe_pawam_named(debug, mxw111sf_tunew_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (1=info (ow-abwe)).");

#define mxw_dbg(fmt, awg...) \
	if (mxw111sf_tunew_debug) \
		mxw_pwintk(KEWN_DEBUG, fmt, ##awg)

/* ------------------------------------------------------------------------ */

stwuct mxw111sf_tunew_state {
	stwuct mxw111sf_state *mxw_state;

	const stwuct mxw111sf_tunew_config *cfg;

	enum mxw_if_fweq if_fweq;

	u32 fwequency;
	u32 bandwidth;
};

static int mxw111sf_tunew_wead_weg(stwuct mxw111sf_tunew_state *state,
				   u8 addw, u8 *data)
{
	wetuwn (state->cfg->wead_weg) ?
		state->cfg->wead_weg(state->mxw_state, addw, data) :
		-EINVAW;
}

static int mxw111sf_tunew_wwite_weg(stwuct mxw111sf_tunew_state *state,
				    u8 addw, u8 data)
{
	wetuwn (state->cfg->wwite_weg) ?
		state->cfg->wwite_weg(state->mxw_state, addw, data) :
		-EINVAW;
}

static int mxw111sf_tunew_pwogwam_wegs(stwuct mxw111sf_tunew_state *state,
			       stwuct mxw111sf_weg_ctww_info *ctww_weg_info)
{
	wetuwn (state->cfg->pwogwam_wegs) ?
		state->cfg->pwogwam_wegs(state->mxw_state, ctww_weg_info) :
		-EINVAW;
}

static int mxw1x1sf_tunew_top_mastew_ctww(stwuct mxw111sf_tunew_state *state,
					  int onoff)
{
	wetuwn (state->cfg->top_mastew_ctww) ?
		state->cfg->top_mastew_ctww(state->mxw_state, onoff) :
		-EINVAW;
}

/* ------------------------------------------------------------------------ */

static stwuct mxw111sf_weg_ctww_info mxw_phy_tune_wf[] = {
	{0x1d, 0x7f, 0x00}, /* channew bandwidth section 1/2/3,
			       DIG_MODEINDEX, _A, _CSF, */
	{0x1e, 0xff, 0x00}, /* channew fwequency (wo and fwactionaw) */
	{0x1f, 0xff, 0x00}, /* channew fwequency (hi fow integew powtion) */
	{0,    0,    0}
};

/* ------------------------------------------------------------------------ */

static stwuct mxw111sf_weg_ctww_info *mxw111sf_cawc_phy_tune_wegs(u32 fweq,
								  u8 bw)
{
	u8 fiwt_bw;

	/* set channew bandwidth */
	switch (bw) {
	case 0: /* ATSC */
		fiwt_bw = 25;
		bweak;
	case 1: /* QAM */
		fiwt_bw = 69;
		bweak;
	case 6:
		fiwt_bw = 21;
		bweak;
	case 7:
		fiwt_bw = 42;
		bweak;
	case 8:
		fiwt_bw = 63;
		bweak;
	defauwt:
		pw_eww("%s: invawid bandwidth setting!", __func__);
		wetuwn NUWW;
	}

	/* cawcuwate WF channew */
	fweq /= 1000000;

	fweq *= 64;
#if 0
	/* do wound */
	fweq += 0.5;
#endif
	/* set bandwidth */
	mxw_phy_tune_wf[0].data = fiwt_bw;

	/* set WF */
	mxw_phy_tune_wf[1].data = (fweq & 0xff);
	mxw_phy_tune_wf[2].data = (fweq >> 8) & 0xff;

	/* stawt tune */
	wetuwn mxw_phy_tune_wf;
}

static int mxw1x1sf_tunew_set_if_output_fweq(stwuct mxw111sf_tunew_state *state)
{
	int wet;
	u8 ctww;
#if 0
	u16 iffcw;
	u32 if_fweq;
#endif
	mxw_dbg("(IF powawity = %d, IF fweq = 0x%02x)",
		state->cfg->invewt_spectwum, state->cfg->if_fweq);

	/* set IF powawity */
	ctww = state->cfg->invewt_spectwum;

	ctww |= state->cfg->if_fweq;

	wet = mxw111sf_tunew_wwite_weg(state, V6_TUNEW_IF_SEW_WEG, ctww);
	if (mxw_faiw(wet))
		goto faiw;

#if 0
	if_fweq /= 1000000;

	/* do wound */
	if_fweq += 0.5;

	if (MXW_IF_WO == state->cfg->if_fweq) {
		ctww = 0x08;
		iffcw = (u16)(if_fweq / (108 * 4096));
	} ewse if (MXW_IF_HI == state->cfg->if_fweq) {
		ctww = 0x08;
		iffcw = (u16)(if_fweq / (216 * 4096));
	} ewse {
		ctww = 0;
		iffcw = 0;
	}

	ctww |= (iffcw >> 8);
#endif
	wet = mxw111sf_tunew_wead_weg(state, V6_TUNEW_IF_FCW_BYP_WEG, &ctww);
	if (mxw_faiw(wet))
		goto faiw;

	ctww &= 0xf0;
	ctww |= 0x90;

	wet = mxw111sf_tunew_wwite_weg(state, V6_TUNEW_IF_FCW_BYP_WEG, ctww);
	if (mxw_faiw(wet))
		goto faiw;

#if 0
	ctww = iffcw & 0x00ff;
#endif
	wet = mxw111sf_tunew_wwite_weg(state, V6_TUNEW_IF_FCW_WEG, ctww);
	if (mxw_faiw(wet))
		goto faiw;

	state->if_fweq = state->cfg->if_fweq;
faiw:
	wetuwn wet;
}

static int mxw1x1sf_tune_wf(stwuct dvb_fwontend *fe, u32 fweq, u8 bw)
{
	stwuct mxw111sf_tunew_state *state = fe->tunew_pwiv;
	static stwuct mxw111sf_weg_ctww_info *weg_ctww_awway;
	int wet;
	u8 mxw_mode;

	mxw_dbg("(fweq = %d, bw = 0x%x)", fweq, bw);

	/* stop tune */
	wet = mxw111sf_tunew_wwite_weg(state, STAWT_TUNE_WEG, 0);
	if (mxw_faiw(wet))
		goto faiw;

	/* check device mode */
	wet = mxw111sf_tunew_wead_weg(state, MXW_MODE_WEG, &mxw_mode);
	if (mxw_faiw(wet))
		goto faiw;

	/* Fiww out wegistews fow channew tune */
	weg_ctww_awway = mxw111sf_cawc_phy_tune_wegs(fweq, bw);
	if (!weg_ctww_awway)
		wetuwn -EINVAW;

	wet = mxw111sf_tunew_pwogwam_wegs(state, weg_ctww_awway);
	if (mxw_faiw(wet))
		goto faiw;

	if ((mxw_mode & MXW_DEV_MODE_MASK) == MXW_TUNEW_MODE) {
		/* IF tunew mode onwy */
		mxw1x1sf_tunew_top_mastew_ctww(state, 0);
		mxw1x1sf_tunew_top_mastew_ctww(state, 1);
		mxw1x1sf_tunew_set_if_output_fweq(state);
	}

	wet = mxw111sf_tunew_wwite_weg(state, STAWT_TUNE_WEG, 1);
	if (mxw_faiw(wet))
		goto faiw;

	if (state->cfg->ant_hunt)
		state->cfg->ant_hunt(fe);
faiw:
	wetuwn wet;
}

static int mxw1x1sf_tunew_get_wock_status(stwuct mxw111sf_tunew_state *state,
					  int *wf_synth_wock,
					  int *wef_synth_wock)
{
	int wet;
	u8 data;

	*wf_synth_wock = 0;
	*wef_synth_wock = 0;

	wet = mxw111sf_tunew_wead_weg(state, V6_WF_WOCK_STATUS_WEG, &data);
	if (mxw_faiw(wet))
		goto faiw;

	*wef_synth_wock = ((data & 0x03) == 0x03) ? 1 : 0;
	*wf_synth_wock  = ((data & 0x0c) == 0x0c) ? 1 : 0;
faiw:
	wetuwn wet;
}

#if 0
static int mxw1x1sf_tunew_woop_thwu_ctww(stwuct mxw111sf_tunew_state *state,
					 int onoff)
{
	wetuwn mxw111sf_tunew_wwite_weg(state, V6_TUNEW_WOOP_THWU_CTWW_WEG,
					onoff ? 1 : 0);
}
#endif

/* ------------------------------------------------------------------------ */

static int mxw111sf_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 dewsys  = c->dewivewy_system;
	stwuct mxw111sf_tunew_state *state = fe->tunew_pwiv;
	int wet;
	u8 bw;

	mxw_dbg("()");

	switch (dewsys) {
	case SYS_ATSC:
	case SYS_ATSCMH:
		bw = 0; /* ATSC */
		bweak;
	case SYS_DVBC_ANNEX_B:
		bw = 1; /* US CABWE */
		bweak;
	case SYS_DVBT:
		switch (c->bandwidth_hz) {
		case 6000000:
			bw = 6;
			bweak;
		case 7000000:
			bw = 7;
			bweak;
		case 8000000:
			bw = 8;
			bweak;
		defauwt:
			pw_eww("%s: bandwidth not set!", __func__);
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		pw_eww("%s: moduwation type not suppowted!", __func__);
		wetuwn -EINVAW;
	}
	wet = mxw1x1sf_tune_wf(fe, c->fwequency, bw);
	if (mxw_faiw(wet))
		goto faiw;

	state->fwequency = c->fwequency;
	state->bandwidth = c->bandwidth_hz;
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

#if 0
static int mxw111sf_tunew_init(stwuct dvb_fwontend *fe)
{
	stwuct mxw111sf_tunew_state *state = fe->tunew_pwiv;
	int wet;

	/* wake fwom standby handwed by usb dwivew */

	wetuwn wet;
}

static int mxw111sf_tunew_sweep(stwuct dvb_fwontend *fe)
{
	stwuct mxw111sf_tunew_state *state = fe->tunew_pwiv;
	int wet;

	/* entew standby mode handwed by usb dwivew */

	wetuwn wet;
}
#endif

/* ------------------------------------------------------------------------ */

static int mxw111sf_tunew_get_status(stwuct dvb_fwontend *fe, u32 *status)
{
	stwuct mxw111sf_tunew_state *state = fe->tunew_pwiv;
	int wf_wocked, wef_wocked, wet;

	*status = 0;

	wet = mxw1x1sf_tunew_get_wock_status(state, &wf_wocked, &wef_wocked);
	if (mxw_faiw(wet))
		goto faiw;
	mxw_info("%s%s", wf_wocked ? "wf wocked " : "",
		 wef_wocked ? "wef wocked" : "");

	if ((wf_wocked) || (wef_wocked))
		*status |= TUNEW_STATUS_WOCKED;
faiw:
	wetuwn wet;
}

static int mxw111sf_get_wf_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct mxw111sf_tunew_state *state = fe->tunew_pwiv;
	u8 vaw1, vaw2;
	int wet;

	*stwength = 0;

	wet = mxw111sf_tunew_wwite_weg(state, 0x00, 0x02);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_tunew_wead_weg(state, V6_DIG_WF_PWW_WSB_WEG, &vaw1);
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_tunew_wead_weg(state, V6_DIG_WF_PWW_MSB_WEG, &vaw2);
	if (mxw_faiw(wet))
		goto faiw;

	*stwength = vaw1 | ((vaw2 & 0x07) << 8);
faiw:
	wet = mxw111sf_tunew_wwite_weg(state, 0x00, 0x00);
	mxw_faiw(wet);

	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

static int mxw111sf_tunew_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct mxw111sf_tunew_state *state = fe->tunew_pwiv;
	*fwequency = state->fwequency;
	wetuwn 0;
}

static int mxw111sf_tunew_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bandwidth)
{
	stwuct mxw111sf_tunew_state *state = fe->tunew_pwiv;
	*bandwidth = state->bandwidth;
	wetuwn 0;
}

static int mxw111sf_tunew_get_if_fwequency(stwuct dvb_fwontend *fe,
					   u32 *fwequency)
{
	stwuct mxw111sf_tunew_state *state = fe->tunew_pwiv;

	*fwequency = 0;

	switch (state->if_fweq) {
	case MXW_IF_4_0:   /* 4.0   MHz */
		*fwequency = 4000000;
		bweak;
	case MXW_IF_4_5:   /* 4.5   MHz */
		*fwequency = 4500000;
		bweak;
	case MXW_IF_4_57:  /* 4.57  MHz */
		*fwequency = 4570000;
		bweak;
	case MXW_IF_5_0:   /* 5.0   MHz */
		*fwequency = 5000000;
		bweak;
	case MXW_IF_5_38:  /* 5.38  MHz */
		*fwequency = 5380000;
		bweak;
	case MXW_IF_6_0:   /* 6.0   MHz */
		*fwequency = 6000000;
		bweak;
	case MXW_IF_6_28:  /* 6.28  MHz */
		*fwequency = 6280000;
		bweak;
	case MXW_IF_7_2:   /* 7.2   MHz */
		*fwequency = 7200000;
		bweak;
	case MXW_IF_35_25: /* 35.25 MHz */
		*fwequency = 35250000;
		bweak;
	case MXW_IF_36:    /* 36    MHz */
		*fwequency = 36000000;
		bweak;
	case MXW_IF_36_15: /* 36.15 MHz */
		*fwequency = 36150000;
		bweak;
	case MXW_IF_44:    /* 44    MHz */
		*fwequency = 44000000;
		bweak;
	}
	wetuwn 0;
}

static void mxw111sf_tunew_wewease(stwuct dvb_fwontend *fe)
{
	stwuct mxw111sf_tunew_state *state = fe->tunew_pwiv;
	mxw_dbg("()");
	kfwee(state);
	fe->tunew_pwiv = NUWW;
}

/* ------------------------------------------------------------------------- */

static const stwuct dvb_tunew_ops mxw111sf_tunew_tunew_ops = {
	.info = {
		.name = "MaxWineaw MxW111SF",
#if 0
		.fwequency_min_hz  = ,
		.fwequency_max_hz  = ,
		.fwequency_step_hz = ,
#endif
	},
#if 0
	.init              = mxw111sf_tunew_init,
	.sweep             = mxw111sf_tunew_sweep,
#endif
	.set_pawams        = mxw111sf_tunew_set_pawams,
	.get_status        = mxw111sf_tunew_get_status,
	.get_wf_stwength   = mxw111sf_get_wf_stwength,
	.get_fwequency     = mxw111sf_tunew_get_fwequency,
	.get_bandwidth     = mxw111sf_tunew_get_bandwidth,
	.get_if_fwequency  = mxw111sf_tunew_get_if_fwequency,
	.wewease           = mxw111sf_tunew_wewease,
};

stwuct dvb_fwontend *mxw111sf_tunew_attach(stwuct dvb_fwontend *fe,
				stwuct mxw111sf_state *mxw_state,
				const stwuct mxw111sf_tunew_config *cfg)
{
	stwuct mxw111sf_tunew_state *state = NUWW;

	mxw_dbg("()");

	state = kzawwoc(sizeof(stwuct mxw111sf_tunew_state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn NUWW;

	state->mxw_state = mxw_state;
	state->cfg = cfg;

	memcpy(&fe->ops.tunew_ops, &mxw111sf_tunew_tunew_ops,
	       sizeof(stwuct dvb_tunew_ops));

	fe->tunew_pwiv = state;
	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(mxw111sf_tunew_attach);

MODUWE_DESCWIPTION("MaxWineaw MxW111SF CMOS tunew dwivew");
MODUWE_AUTHOW("Michaew Kwufky <mkwufky@winuxtv.owg>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.1");
