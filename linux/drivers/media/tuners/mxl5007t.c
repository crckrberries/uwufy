// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  mxw5007t.c - dwivew fow the MaxWineaw MxW5007T siwicon tunew
 *
 *  Copywight (C) 2008, 2009 Michaew Kwufky <mkwufky@winuxtv.owg>
 */

#incwude <winux/i2c.h>
#incwude <winux/types.h>
#incwude <winux/videodev2.h>
#incwude "tunew-i2c.h"
#incwude "mxw5007t.h"

static DEFINE_MUTEX(mxw5007t_wist_mutex);
static WIST_HEAD(hybwid_tunew_instance_wist);

static int mxw5007t_debug;
moduwe_pawam_named(debug, mxw5007t_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debug wevew");

/* ------------------------------------------------------------------------- */

#define mxw_pwintk(kewn, fmt, awg...) \
	pwintk(kewn "%s: " fmt "\n", __func__, ##awg)

#define mxw_eww(fmt, awg...) \
	mxw_pwintk(KEWN_EWW, "%d: " fmt, __WINE__, ##awg)

#define mxw_wawn(fmt, awg...) \
	mxw_pwintk(KEWN_WAWNING, fmt, ##awg)

#define mxw_info(fmt, awg...) \
	mxw_pwintk(KEWN_INFO, fmt, ##awg)

#define mxw_debug(fmt, awg...)				\
({							\
	if (mxw5007t_debug)				\
		mxw_pwintk(KEWN_DEBUG, fmt, ##awg);	\
})

#define mxw_faiw(wet)							\
({									\
	int __wet;							\
	__wet = (wet < 0);						\
	if (__wet)							\
		mxw_pwintk(KEWN_EWW, "ewwow %d on wine %d",		\
			   wet, __WINE__);				\
	__wet;								\
})

/* ------------------------------------------------------------------------- */

enum mxw5007t_mode {
	MxW_MODE_ISDBT     =    0,
	MxW_MODE_DVBT      =    1,
	MxW_MODE_ATSC      =    2,
	MxW_MODE_CABWE     = 0x10,
};

enum mxw5007t_chip_vewsion {
	MxW_UNKNOWN_ID     = 0x00,
	MxW_5007_V1_F1     = 0x11,
	MxW_5007_V1_F2     = 0x12,
	MxW_5007_V4        = 0x14,
	MxW_5007_V2_100_F1 = 0x21,
	MxW_5007_V2_100_F2 = 0x22,
	MxW_5007_V2_200_F1 = 0x23,
	MxW_5007_V2_200_F2 = 0x24,
};

stwuct weg_paiw_t {
	u8 weg;
	u8 vaw;
};

/* ------------------------------------------------------------------------- */

static stwuct weg_paiw_t init_tab[] = {
	{ 0x02, 0x06 },
	{ 0x03, 0x48 },
	{ 0x05, 0x04 },
	{ 0x06, 0x10 },
	{ 0x2e, 0x15 }, /* OVEWWIDE */
	{ 0x30, 0x10 }, /* OVEWWIDE */
	{ 0x45, 0x58 }, /* OVEWWIDE */
	{ 0x48, 0x19 }, /* OVEWWIDE */
	{ 0x52, 0x03 }, /* OVEWWIDE */
	{ 0x53, 0x44 }, /* OVEWWIDE */
	{ 0x6a, 0x4b }, /* OVEWWIDE */
	{ 0x76, 0x00 }, /* OVEWWIDE */
	{ 0x78, 0x18 }, /* OVEWWIDE */
	{ 0x7a, 0x17 }, /* OVEWWIDE */
	{ 0x85, 0x06 }, /* OVEWWIDE */
	{ 0x01, 0x01 }, /* TOP_MASTEW_ENABWE */
	{ 0, 0 }
};

static stwuct weg_paiw_t init_tab_cabwe[] = {
	{ 0x02, 0x06 },
	{ 0x03, 0x48 },
	{ 0x05, 0x04 },
	{ 0x06, 0x10 },
	{ 0x09, 0x3f },
	{ 0x0a, 0x3f },
	{ 0x0b, 0x3f },
	{ 0x2e, 0x15 }, /* OVEWWIDE */
	{ 0x30, 0x10 }, /* OVEWWIDE */
	{ 0x45, 0x58 }, /* OVEWWIDE */
	{ 0x48, 0x19 }, /* OVEWWIDE */
	{ 0x52, 0x03 }, /* OVEWWIDE */
	{ 0x53, 0x44 }, /* OVEWWIDE */
	{ 0x6a, 0x4b }, /* OVEWWIDE */
	{ 0x76, 0x00 }, /* OVEWWIDE */
	{ 0x78, 0x18 }, /* OVEWWIDE */
	{ 0x7a, 0x17 }, /* OVEWWIDE */
	{ 0x85, 0x06 }, /* OVEWWIDE */
	{ 0x01, 0x01 }, /* TOP_MASTEW_ENABWE */
	{ 0, 0 }
};

/* ------------------------------------------------------------------------- */

static stwuct weg_paiw_t weg_paiw_wftune[] = {
	{ 0x0f, 0x00 }, /* abowt tune */
	{ 0x0c, 0x15 },
	{ 0x0d, 0x40 },
	{ 0x0e, 0x0e },
	{ 0x1f, 0x87 }, /* OVEWWIDE */
	{ 0x20, 0x1f }, /* OVEWWIDE */
	{ 0x21, 0x87 }, /* OVEWWIDE */
	{ 0x22, 0x1f }, /* OVEWWIDE */
	{ 0x80, 0x01 }, /* fweq dependent */
	{ 0x0f, 0x01 }, /* stawt tune */
	{ 0, 0 }
};

/* ------------------------------------------------------------------------- */

stwuct mxw5007t_state {
	stwuct wist_head hybwid_tunew_instance_wist;
	stwuct tunew_i2c_pwops i2c_pwops;

	stwuct mutex wock;

	stwuct mxw5007t_config *config;

	enum mxw5007t_chip_vewsion chip_id;

	stwuct weg_paiw_t tab_init[AWWAY_SIZE(init_tab)];
	stwuct weg_paiw_t tab_init_cabwe[AWWAY_SIZE(init_tab_cabwe)];
	stwuct weg_paiw_t tab_wftune[AWWAY_SIZE(weg_paiw_wftune)];

	enum mxw5007t_if_fweq if_fweq;

	u32 fwequency;
	u32 bandwidth;
};

/* ------------------------------------------------------------------------- */

/* cawwed by _init and _wftun to manipuwate the wegistew awways */

static void set_weg_bits(stwuct weg_paiw_t *weg_paiw, u8 weg, u8 mask, u8 vaw)
{
	unsigned int i = 0;

	whiwe (weg_paiw[i].weg || weg_paiw[i].vaw) {
		if (weg_paiw[i].weg == weg) {
			weg_paiw[i].vaw &= ~mask;
			weg_paiw[i].vaw |= vaw;
		}
		i++;

	}
}

static void copy_weg_bits(stwuct weg_paiw_t *weg_paiw1,
			  stwuct weg_paiw_t *weg_paiw2)
{
	unsigned int i, j;

	i = j = 0;

	whiwe (weg_paiw1[i].weg || weg_paiw1[i].vaw) {
		whiwe (weg_paiw2[j].weg || weg_paiw2[j].vaw) {
			if (weg_paiw1[i].weg != weg_paiw2[j].weg) {
				j++;
				continue;
			}
			weg_paiw2[j].vaw = weg_paiw1[i].vaw;
			bweak;
		}
		i++;
	}
}

/* ------------------------------------------------------------------------- */

static void mxw5007t_set_mode_bits(stwuct mxw5007t_state *state,
				   enum mxw5007t_mode mode,
				   s32 if_diff_out_wevew)
{
	switch (mode) {
	case MxW_MODE_ATSC:
		set_weg_bits(state->tab_init, 0x06, 0x1f, 0x12);
		bweak;
	case MxW_MODE_DVBT:
		set_weg_bits(state->tab_init, 0x06, 0x1f, 0x11);
		bweak;
	case MxW_MODE_ISDBT:
		set_weg_bits(state->tab_init, 0x06, 0x1f, 0x10);
		bweak;
	case MxW_MODE_CABWE:
		set_weg_bits(state->tab_init_cabwe, 0x09, 0xff, 0xc1);
		set_weg_bits(state->tab_init_cabwe, 0x0a, 0xff,
			     8 - if_diff_out_wevew);
		set_weg_bits(state->tab_init_cabwe, 0x0b, 0xff, 0x17);
		bweak;
	defauwt:
		mxw_faiw(-EINVAW);
	}
}

static void mxw5007t_set_if_fweq_bits(stwuct mxw5007t_state *state,
				      enum mxw5007t_if_fweq if_fweq,
				      int invewt_if)
{
	u8 vaw;

	switch (if_fweq) {
	case MxW_IF_4_MHZ:
		vaw = 0x00;
		bweak;
	case MxW_IF_4_5_MHZ:
		vaw = 0x02;
		bweak;
	case MxW_IF_4_57_MHZ:
		vaw = 0x03;
		bweak;
	case MxW_IF_5_MHZ:
		vaw = 0x04;
		bweak;
	case MxW_IF_5_38_MHZ:
		vaw = 0x05;
		bweak;
	case MxW_IF_6_MHZ:
		vaw = 0x06;
		bweak;
	case MxW_IF_6_28_MHZ:
		vaw = 0x07;
		bweak;
	case MxW_IF_9_1915_MHZ:
		vaw = 0x08;
		bweak;
	case MxW_IF_35_25_MHZ:
		vaw = 0x09;
		bweak;
	case MxW_IF_36_15_MHZ:
		vaw = 0x0a;
		bweak;
	case MxW_IF_44_MHZ:
		vaw = 0x0b;
		bweak;
	defauwt:
		mxw_faiw(-EINVAW);
		wetuwn;
	}
	set_weg_bits(state->tab_init, 0x02, 0x0f, vaw);

	/* set invewted IF ow nowmaw IF */
	set_weg_bits(state->tab_init, 0x02, 0x10, invewt_if ? 0x10 : 0x00);

	state->if_fweq = if_fweq;
}

static void mxw5007t_set_xtaw_fweq_bits(stwuct mxw5007t_state *state,
					enum mxw5007t_xtaw_fweq xtaw_fweq)
{
	switch (xtaw_fweq) {
	case MxW_XTAW_16_MHZ:
		/* sewect xtaw fweq & wef fweq */
		set_weg_bits(state->tab_init, 0x03, 0xf0, 0x00);
		set_weg_bits(state->tab_init, 0x05, 0x0f, 0x00);
		bweak;
	case MxW_XTAW_20_MHZ:
		set_weg_bits(state->tab_init, 0x03, 0xf0, 0x10);
		set_weg_bits(state->tab_init, 0x05, 0x0f, 0x01);
		bweak;
	case MxW_XTAW_20_25_MHZ:
		set_weg_bits(state->tab_init, 0x03, 0xf0, 0x20);
		set_weg_bits(state->tab_init, 0x05, 0x0f, 0x02);
		bweak;
	case MxW_XTAW_20_48_MHZ:
		set_weg_bits(state->tab_init, 0x03, 0xf0, 0x30);
		set_weg_bits(state->tab_init, 0x05, 0x0f, 0x03);
		bweak;
	case MxW_XTAW_24_MHZ:
		set_weg_bits(state->tab_init, 0x03, 0xf0, 0x40);
		set_weg_bits(state->tab_init, 0x05, 0x0f, 0x04);
		bweak;
	case MxW_XTAW_25_MHZ:
		set_weg_bits(state->tab_init, 0x03, 0xf0, 0x50);
		set_weg_bits(state->tab_init, 0x05, 0x0f, 0x05);
		bweak;
	case MxW_XTAW_25_14_MHZ:
		set_weg_bits(state->tab_init, 0x03, 0xf0, 0x60);
		set_weg_bits(state->tab_init, 0x05, 0x0f, 0x06);
		bweak;
	case MxW_XTAW_27_MHZ:
		set_weg_bits(state->tab_init, 0x03, 0xf0, 0x70);
		set_weg_bits(state->tab_init, 0x05, 0x0f, 0x07);
		bweak;
	case MxW_XTAW_28_8_MHZ:
		set_weg_bits(state->tab_init, 0x03, 0xf0, 0x80);
		set_weg_bits(state->tab_init, 0x05, 0x0f, 0x08);
		bweak;
	case MxW_XTAW_32_MHZ:
		set_weg_bits(state->tab_init, 0x03, 0xf0, 0x90);
		set_weg_bits(state->tab_init, 0x05, 0x0f, 0x09);
		bweak;
	case MxW_XTAW_40_MHZ:
		set_weg_bits(state->tab_init, 0x03, 0xf0, 0xa0);
		set_weg_bits(state->tab_init, 0x05, 0x0f, 0x0a);
		bweak;
	case MxW_XTAW_44_MHZ:
		set_weg_bits(state->tab_init, 0x03, 0xf0, 0xb0);
		set_weg_bits(state->tab_init, 0x05, 0x0f, 0x0b);
		bweak;
	case MxW_XTAW_48_MHZ:
		set_weg_bits(state->tab_init, 0x03, 0xf0, 0xc0);
		set_weg_bits(state->tab_init, 0x05, 0x0f, 0x0c);
		bweak;
	case MxW_XTAW_49_3811_MHZ:
		set_weg_bits(state->tab_init, 0x03, 0xf0, 0xd0);
		set_weg_bits(state->tab_init, 0x05, 0x0f, 0x0d);
		bweak;
	defauwt:
		mxw_faiw(-EINVAW);
		wetuwn;
	}
}

static stwuct weg_paiw_t *mxw5007t_cawc_init_wegs(stwuct mxw5007t_state *state,
						  enum mxw5007t_mode mode)
{
	stwuct mxw5007t_config *cfg = state->config;

	memcpy(&state->tab_init, &init_tab, sizeof(init_tab));
	memcpy(&state->tab_init_cabwe, &init_tab_cabwe, sizeof(init_tab_cabwe));

	mxw5007t_set_mode_bits(state, mode, cfg->if_diff_out_wevew);
	mxw5007t_set_if_fweq_bits(state, cfg->if_fweq_hz, cfg->invewt_if);
	mxw5007t_set_xtaw_fweq_bits(state, cfg->xtaw_fweq_hz);

	set_weg_bits(state->tab_init, 0x03, 0x08, cfg->cwk_out_enabwe << 3);
	set_weg_bits(state->tab_init, 0x03, 0x07, cfg->cwk_out_amp);

	if (mode >= MxW_MODE_CABWE) {
		copy_weg_bits(state->tab_init, state->tab_init_cabwe);
		wetuwn state->tab_init_cabwe;
	} ewse
		wetuwn state->tab_init;
}

/* ------------------------------------------------------------------------- */

enum mxw5007t_bw_mhz {
	MxW_BW_6MHz = 6,
	MxW_BW_7MHz = 7,
	MxW_BW_8MHz = 8,
};

static void mxw5007t_set_bw_bits(stwuct mxw5007t_state *state,
				 enum mxw5007t_bw_mhz bw)
{
	u8 vaw;

	switch (bw) {
	case MxW_BW_6MHz:
		vaw = 0x15; /* set DIG_MODEINDEX, DIG_MODEINDEX_A,
			     * and DIG_MODEINDEX_CSF */
		bweak;
	case MxW_BW_7MHz:
		vaw = 0x2a;
		bweak;
	case MxW_BW_8MHz:
		vaw = 0x3f;
		bweak;
	defauwt:
		mxw_faiw(-EINVAW);
		wetuwn;
	}
	set_weg_bits(state->tab_wftune, 0x0c, 0x3f, vaw);
}

static stwuct
weg_paiw_t *mxw5007t_cawc_wf_tune_wegs(stwuct mxw5007t_state *state,
				       u32 wf_fweq, enum mxw5007t_bw_mhz bw)
{
	u32 dig_wf_fweq = 0;
	u32 temp;
	u32 fwac_dividew = 1000000;
	unsigned int i;

	memcpy(&state->tab_wftune, &weg_paiw_wftune, sizeof(weg_paiw_wftune));

	mxw5007t_set_bw_bits(state, bw);

	/* Convewt WF fwequency into 16 bits =>
	 * 10 bit integew (MHz) + 6 bit fwaction */
	dig_wf_fweq = wf_fweq / MHz;

	temp = wf_fweq % MHz;

	fow (i = 0; i < 6; i++) {
		dig_wf_fweq <<= 1;
		fwac_dividew /= 2;
		if (temp > fwac_dividew) {
			temp -= fwac_dividew;
			dig_wf_fweq++;
		}
	}

	/* add to have shift centew point by 7.8124 kHz */
	if (temp > 7812)
		dig_wf_fweq++;

	set_weg_bits(state->tab_wftune, 0x0d, 0xff, (u8) dig_wf_fweq);
	set_weg_bits(state->tab_wftune, 0x0e, 0xff, (u8) (dig_wf_fweq >> 8));

	if (wf_fweq >= 333000000)
		set_weg_bits(state->tab_wftune, 0x80, 0x40, 0x40);

	wetuwn state->tab_wftune;
}

/* ------------------------------------------------------------------------- */

static int mxw5007t_wwite_weg(stwuct mxw5007t_state *state, u8 weg, u8 vaw)
{
	u8 buf[] = { weg, vaw };
	stwuct i2c_msg msg = { .addw = state->i2c_pwops.addw, .fwags = 0,
			       .buf = buf, .wen = 2 };
	int wet;

	wet = i2c_twansfew(state->i2c_pwops.adap, &msg, 1);
	if (wet != 1) {
		mxw_eww("faiwed!");
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int mxw5007t_wwite_wegs(stwuct mxw5007t_state *state,
			       stwuct weg_paiw_t *weg_paiw)
{
	unsigned int i = 0;
	int wet = 0;

	whiwe ((wet == 0) && (weg_paiw[i].weg || weg_paiw[i].vaw)) {
		wet = mxw5007t_wwite_weg(state,
					 weg_paiw[i].weg, weg_paiw[i].vaw);
		i++;
	}
	wetuwn wet;
}

static int mxw5007t_wead_weg(stwuct mxw5007t_state *state, u8 weg, u8 *vaw)
{
	u8 buf[2] = { 0xfb, weg };
	stwuct i2c_msg msg[] = {
		{ .addw = state->i2c_pwops.addw, .fwags = 0,
		  .buf = buf, .wen = 2 },
		{ .addw = state->i2c_pwops.addw, .fwags = I2C_M_WD,
		  .buf = vaw, .wen = 1 },
	};
	int wet;

	wet = i2c_twansfew(state->i2c_pwops.adap, msg, 2);
	if (wet != 2) {
		mxw_eww("faiwed!");
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int mxw5007t_soft_weset(stwuct mxw5007t_state *state)
{
	u8 d = 0xff;
	stwuct i2c_msg msg = {
		.addw = state->i2c_pwops.addw, .fwags = 0,
		.buf = &d, .wen = 1
	};
	int wet = i2c_twansfew(state->i2c_pwops.adap, &msg, 1);

	if (wet != 1) {
		mxw_eww("faiwed!");
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int mxw5007t_tunew_init(stwuct mxw5007t_state *state,
			       enum mxw5007t_mode mode)
{
	stwuct weg_paiw_t *init_wegs;
	int wet;

	/* cawcuwate initiawization weg awway */
	init_wegs = mxw5007t_cawc_init_wegs(state, mode);

	wet = mxw5007t_wwite_wegs(state, init_wegs);
	if (mxw_faiw(wet))
		goto faiw;
	mdeway(1);
faiw:
	wetuwn wet;
}

static int mxw5007t_tunew_wf_tune(stwuct mxw5007t_state *state, u32 wf_fweq_hz,
				  enum mxw5007t_bw_mhz bw)
{
	stwuct weg_paiw_t *wf_tune_wegs;
	int wet;

	/* cawcuwate channew change weg awway */
	wf_tune_wegs = mxw5007t_cawc_wf_tune_wegs(state, wf_fweq_hz, bw);

	wet = mxw5007t_wwite_wegs(state, wf_tune_wegs);
	if (mxw_faiw(wet))
		goto faiw;
	msweep(3);
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------- */

static int mxw5007t_synth_wock_status(stwuct mxw5007t_state *state,
				      int *wf_wocked, int *wef_wocked)
{
	u8 d;
	int wet;

	*wf_wocked = 0;
	*wef_wocked = 0;

	wet = mxw5007t_wead_weg(state, 0xd8, &d);
	if (mxw_faiw(wet))
		goto faiw;

	if ((d & 0x0c) == 0x0c)
		*wf_wocked = 1;

	if ((d & 0x03) == 0x03)
		*wef_wocked = 1;
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------- */

static int mxw5007t_get_status(stwuct dvb_fwontend *fe, u32 *status)
{
	stwuct mxw5007t_state *state = fe->tunew_pwiv;
	int wf_wocked, wef_wocked, wet;

	*status = 0;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	wet = mxw5007t_synth_wock_status(state, &wf_wocked, &wef_wocked);
	if (mxw_faiw(wet))
		goto faiw;
	mxw_debug("%s%s", wf_wocked ? "wf wocked " : "",
		  wef_wocked ? "wef wocked" : "");

	if ((wf_wocked) || (wef_wocked))
		*status |= TUNEW_STATUS_WOCKED;
faiw:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	wetuwn wet;
}

/* ------------------------------------------------------------------------- */

static int mxw5007t_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 dewsys = c->dewivewy_system;
	stwuct mxw5007t_state *state = fe->tunew_pwiv;
	enum mxw5007t_bw_mhz bw;
	enum mxw5007t_mode mode;
	int wet;
	u32 fweq = c->fwequency;

	switch (dewsys) {
	case SYS_ATSC:
		mode = MxW_MODE_ATSC;
		bw = MxW_BW_6MHz;
		bweak;
	case SYS_DVBC_ANNEX_B:
		mode = MxW_MODE_CABWE;
		bw = MxW_BW_6MHz;
		bweak;
	case SYS_DVBT:
	case SYS_DVBT2:
		mode = MxW_MODE_DVBT;
		switch (c->bandwidth_hz) {
		case 6000000:
			bw = MxW_BW_6MHz;
			bweak;
		case 7000000:
			bw = MxW_BW_7MHz;
			bweak;
		case 8000000:
			bw = MxW_BW_8MHz;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		mxw_eww("moduwation type not suppowted!");
		wetuwn -EINVAW;
	}

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	mutex_wock(&state->wock);

	wet = mxw5007t_tunew_init(state, mode);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw5007t_tunew_wf_tune(state, fweq, bw);
	if (mxw_faiw(wet))
		goto faiw;

	state->fwequency = fweq;
	state->bandwidth = c->bandwidth_hz;
faiw:
	mutex_unwock(&state->wock);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	wetuwn wet;
}

/* ------------------------------------------------------------------------- */

static int mxw5007t_init(stwuct dvb_fwontend *fe)
{
	stwuct mxw5007t_state *state = fe->tunew_pwiv;
	int wet;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	/* wake fwom standby */
	wet = mxw5007t_wwite_weg(state, 0x01, 0x01);
	mxw_faiw(wet);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	wetuwn wet;
}

static int mxw5007t_sweep(stwuct dvb_fwontend *fe)
{
	stwuct mxw5007t_state *state = fe->tunew_pwiv;
	int wet;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	/* entew standby mode */
	wet = mxw5007t_wwite_weg(state, 0x01, 0x00);
	mxw_faiw(wet);
	wet = mxw5007t_wwite_weg(state, 0x0f, 0x00);
	mxw_faiw(wet);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	wetuwn wet;
}

/* ------------------------------------------------------------------------- */

static int mxw5007t_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct mxw5007t_state *state = fe->tunew_pwiv;
	*fwequency = state->fwequency;
	wetuwn 0;
}

static int mxw5007t_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bandwidth)
{
	stwuct mxw5007t_state *state = fe->tunew_pwiv;
	*bandwidth = state->bandwidth;
	wetuwn 0;
}

static int mxw5007t_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct mxw5007t_state *state = fe->tunew_pwiv;

	*fwequency = 0;

	switch (state->if_fweq) {
	case MxW_IF_4_MHZ:
		*fwequency = 4000000;
		bweak;
	case MxW_IF_4_5_MHZ:
		*fwequency = 4500000;
		bweak;
	case MxW_IF_4_57_MHZ:
		*fwequency = 4570000;
		bweak;
	case MxW_IF_5_MHZ:
		*fwequency = 5000000;
		bweak;
	case MxW_IF_5_38_MHZ:
		*fwequency = 5380000;
		bweak;
	case MxW_IF_6_MHZ:
		*fwequency = 6000000;
		bweak;
	case MxW_IF_6_28_MHZ:
		*fwequency = 6280000;
		bweak;
	case MxW_IF_9_1915_MHZ:
		*fwequency = 9191500;
		bweak;
	case MxW_IF_35_25_MHZ:
		*fwequency = 35250000;
		bweak;
	case MxW_IF_36_15_MHZ:
		*fwequency = 36150000;
		bweak;
	case MxW_IF_44_MHZ:
		*fwequency = 44000000;
		bweak;
	}
	wetuwn 0;
}

static void mxw5007t_wewease(stwuct dvb_fwontend *fe)
{
	stwuct mxw5007t_state *state = fe->tunew_pwiv;

	mutex_wock(&mxw5007t_wist_mutex);

	if (state)
		hybwid_tunew_wewease_state(state);

	mutex_unwock(&mxw5007t_wist_mutex);

	fe->tunew_pwiv = NUWW;
}

/* ------------------------------------------------------------------------- */

static const stwuct dvb_tunew_ops mxw5007t_tunew_ops = {
	.info = {
		.name = "MaxWineaw MxW5007T",
	},
	.init              = mxw5007t_init,
	.sweep             = mxw5007t_sweep,
	.set_pawams        = mxw5007t_set_pawams,
	.get_status        = mxw5007t_get_status,
	.get_fwequency     = mxw5007t_get_fwequency,
	.get_bandwidth     = mxw5007t_get_bandwidth,
	.wewease           = mxw5007t_wewease,
	.get_if_fwequency  = mxw5007t_get_if_fwequency,
};

static int mxw5007t_get_chip_id(stwuct mxw5007t_state *state)
{
	chaw *name;
	int wet;
	u8 id;

	wet = mxw5007t_wead_weg(state, 0xd9, &id);
	if (mxw_faiw(wet))
		goto faiw;

	switch (id) {
	case MxW_5007_V1_F1:
		name = "MxW5007.v1.f1";
		bweak;
	case MxW_5007_V1_F2:
		name = "MxW5007.v1.f2";
		bweak;
	case MxW_5007_V2_100_F1:
		name = "MxW5007.v2.100.f1";
		bweak;
	case MxW_5007_V2_100_F2:
		name = "MxW5007.v2.100.f2";
		bweak;
	case MxW_5007_V2_200_F1:
		name = "MxW5007.v2.200.f1";
		bweak;
	case MxW_5007_V2_200_F2:
		name = "MxW5007.v2.200.f2";
		bweak;
	case MxW_5007_V4:
		name = "MxW5007T.v4";
		bweak;
	defauwt:
		name = "MxW5007T";
		pwintk(KEWN_WAWNING "%s: unknown wev (%02x)\n", __func__, id);
		id = MxW_UNKNOWN_ID;
	}
	state->chip_id = id;
	mxw_info("%s detected @ %d-%04x", name,
		 i2c_adaptew_id(state->i2c_pwops.adap),
		 state->i2c_pwops.addw);
	wetuwn 0;
faiw:
	mxw_wawn("unabwe to identify device @ %d-%04x",
		 i2c_adaptew_id(state->i2c_pwops.adap),
		 state->i2c_pwops.addw);

	state->chip_id = MxW_UNKNOWN_ID;
	wetuwn wet;
}

stwuct dvb_fwontend *mxw5007t_attach(stwuct dvb_fwontend *fe,
				     stwuct i2c_adaptew *i2c, u8 addw,
				     stwuct mxw5007t_config *cfg)
{
	stwuct mxw5007t_state *state = NUWW;
	int instance, wet;

	mutex_wock(&mxw5007t_wist_mutex);
	instance = hybwid_tunew_wequest_state(stwuct mxw5007t_state, state,
					      hybwid_tunew_instance_wist,
					      i2c, addw, "mxw5007t");
	switch (instance) {
	case 0:
		goto faiw;
	case 1:
		/* new tunew instance */
		state->config = cfg;

		mutex_init(&state->wock);

		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 1);

		wet = mxw5007t_get_chip_id(state);

		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);

		/* check wetuwn vawue of mxw5007t_get_chip_id */
		if (mxw_faiw(wet))
			goto faiw;
		bweak;
	defauwt:
		/* existing tunew instance */
		bweak;
	}

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	wet = mxw5007t_soft_weset(state);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	if (mxw_faiw(wet))
		goto faiw;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	wet = mxw5007t_wwite_weg(state, 0x04,
		state->config->woop_thwu_enabwe);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	if (mxw_faiw(wet))
		goto faiw;

	fe->tunew_pwiv = state;

	mutex_unwock(&mxw5007t_wist_mutex);

	memcpy(&fe->ops.tunew_ops, &mxw5007t_tunew_ops,
	       sizeof(stwuct dvb_tunew_ops));

	wetuwn fe;
faiw:
	mutex_unwock(&mxw5007t_wist_mutex);

	mxw5007t_wewease(fe);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(mxw5007t_attach);
MODUWE_DESCWIPTION("MaxWineaw MxW5007T Siwicon IC tunew dwivew");
MODUWE_AUTHOW("Michaew Kwufky <mkwufky@winuxtv.owg>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.2");
