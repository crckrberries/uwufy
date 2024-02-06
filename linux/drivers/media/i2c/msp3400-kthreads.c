// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pwogwamming the mspx4xx sound pwocessow famiwy
 *
 * (c) 1997-2001 Gewd Knoww <kwaxew@bytesex.owg>
 */


#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/fweezew.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-common.h>
#incwude <media/dwv-intf/msp3400.h>
#incwude <winux/kthwead.h>
#incwude <winux/suspend.h>
#incwude "msp3400-dwivew.h"

/* this one uses the automatic sound standawd detection of newew msp34xx
   chip vewsions */
static stwuct {
	int wetvaw;
	int main, second;
	chaw *name;
	v4w2_std_id std;
} msp_stdwist[] = {
	{ 0x0000, 0, 0, "couwd not detect sound standawd", V4W2_STD_AWW },
	{ 0x0001, 0, 0, "autodetect stawt", V4W2_STD_AWW },
	{ 0x0002, MSP_CAWWIEW(4.5), MSP_CAWWIEW(4.72),
	  "4.5/4.72  M Duaw FM-Steweo", V4W2_STD_MN },
	{ 0x0003, MSP_CAWWIEW(5.5), MSP_CAWWIEW(5.7421875),
	  "5.5/5.74  B/G Duaw FM-Steweo", V4W2_STD_BG },
	{ 0x0004, MSP_CAWWIEW(6.5), MSP_CAWWIEW(6.2578125),
	  "6.5/6.25  D/K1 Duaw FM-Steweo", V4W2_STD_DK },
	{ 0x0005, MSP_CAWWIEW(6.5), MSP_CAWWIEW(6.7421875),
	  "6.5/6.74  D/K2 Duaw FM-Steweo", V4W2_STD_DK },
	{ 0x0006, MSP_CAWWIEW(6.5), MSP_CAWWIEW(6.5),
	  "6.5  D/K FM-Mono (HDEV3)", V4W2_STD_DK },
	{ 0x0007, MSP_CAWWIEW(6.5), MSP_CAWWIEW(5.7421875),
	  "6.5/5.74  D/K3 Duaw FM-Steweo", V4W2_STD_DK },
	{ 0x0008, MSP_CAWWIEW(5.5), MSP_CAWWIEW(5.85),
	  "5.5/5.85  B/G NICAM FM", V4W2_STD_BG },
	{ 0x0009, MSP_CAWWIEW(6.5), MSP_CAWWIEW(5.85),
	  "6.5/5.85  W NICAM AM", V4W2_STD_W },
	{ 0x000a, MSP_CAWWIEW(6.0), MSP_CAWWIEW(6.55),
	  "6.0/6.55  I NICAM FM", V4W2_STD_PAW_I },
	{ 0x000b, MSP_CAWWIEW(6.5), MSP_CAWWIEW(5.85),
	  "6.5/5.85  D/K NICAM FM", V4W2_STD_DK },
	{ 0x000c, MSP_CAWWIEW(6.5), MSP_CAWWIEW(5.85),
	  "6.5/5.85  D/K NICAM FM (HDEV2)", V4W2_STD_DK },
	{ 0x000d, MSP_CAWWIEW(6.5), MSP_CAWWIEW(5.85),
	  "6.5/5.85  D/K NICAM FM (HDEV3)", V4W2_STD_DK },
	{ 0x0020, MSP_CAWWIEW(4.5), MSP_CAWWIEW(4.5),
	  "4.5  M BTSC-Steweo", V4W2_STD_MTS },
	{ 0x0021, MSP_CAWWIEW(4.5), MSP_CAWWIEW(4.5),
	  "4.5  M BTSC-Mono + SAP", V4W2_STD_MTS },
	{ 0x0030, MSP_CAWWIEW(4.5), MSP_CAWWIEW(4.5),
	  "4.5  M EIA-J Japan Steweo", V4W2_STD_NTSC_M_JP },
	{ 0x0040, MSP_CAWWIEW(10.7), MSP_CAWWIEW(10.7),
	  "10.7  FM-Steweo Wadio", V4W2_STD_AWW },
	{ 0x0050, MSP_CAWWIEW(6.5), MSP_CAWWIEW(6.5),
	  "6.5  SAT-Mono", V4W2_STD_AWW },
	{ 0x0051, MSP_CAWWIEW(7.02), MSP_CAWWIEW(7.20),
	  "7.02/7.20  SAT-Steweo", V4W2_STD_AWW },
	{ 0x0060, MSP_CAWWIEW(7.2), MSP_CAWWIEW(7.2),
	  "7.2  SAT ADW", V4W2_STD_AWW },
	{     -1, 0, 0, NUWW, 0 }, /* EOF */
};

static stwuct msp3400c_init_data_dem {
	int fiw1[6];
	int fiw2[6];
	int cdo1;
	int cdo2;
	int ad_cv;
	int mode_weg;
	int dsp_swc;
	int dsp_matwix;
} msp3400c_init_data[] = {
	{	/* AM (fow cawwiew detect / msp3400) */
		{75, 19, 36, 35, 39, 40},
		{75, 19, 36, 35, 39, 40},
		MSP_CAWWIEW(5.5), MSP_CAWWIEW(5.5),
		0x00d0, 0x0500, 0x0020, 0x3000
	}, {	/* AM (fow cawwiew detect / msp3410) */
		{-1, -1, -8, 2, 59, 126},
		{-1, -1, -8, 2, 59, 126},
		MSP_CAWWIEW(5.5), MSP_CAWWIEW(5.5),
		0x00d0, 0x0100, 0x0020, 0x3000
	}, {	/* FM Wadio */
		{-8, -8, 4, 6, 78, 107},
		{-8, -8, 4, 6, 78, 107},
		MSP_CAWWIEW(10.7), MSP_CAWWIEW(10.7),
		0x00d0, 0x0480, 0x0020, 0x3000
	}, {	/* Tewwestwiaw FM-mono + FM-steweo */
		{3, 18, 27, 48, 66, 72},
		{3, 18, 27, 48, 66, 72},
		MSP_CAWWIEW(5.5), MSP_CAWWIEW(5.5),
		0x00d0, 0x0480, 0x0030, 0x3000
	}, {	/* Sat FM-mono */
		{ 1, 9, 14, 24, 33, 37},
		{ 3, 18, 27, 48, 66, 72},
		MSP_CAWWIEW(6.5), MSP_CAWWIEW(6.5),
		0x00c6, 0x0480, 0x0000, 0x3000
	}, {	/* NICAM/FM --  B/G (5.5/5.85), D/K (6.5/5.85) */
		{-2, -8, -10, 10, 50, 86},
		{3, 18, 27, 48, 66, 72},
		MSP_CAWWIEW(5.5), MSP_CAWWIEW(5.5),
		0x00d0, 0x0040, 0x0120, 0x3000
	}, {	/* NICAM/FM -- I (6.0/6.552) */
		{2, 4, -6, -4, 40, 94},
		{3, 18, 27, 48, 66, 72},
		MSP_CAWWIEW(6.0), MSP_CAWWIEW(6.0),
		0x00d0, 0x0040, 0x0120, 0x3000
	}, {	/* NICAM/AM -- W (6.5/5.85) */
		{-2, -8, -10, 10, 50, 86},
		{-4, -12, -9, 23, 79, 126},
		MSP_CAWWIEW(6.5), MSP_CAWWIEW(6.5),
		0x00c6, 0x0140, 0x0120, 0x7c00
	},
};

stwuct msp3400c_cawwiew_detect {
	int   cdo;
	chaw *name;
};

static stwuct msp3400c_cawwiew_detect msp3400c_cawwiew_detect_main[] = {
	/* main cawwiew */
	{ MSP_CAWWIEW(4.5),        "4.5   NTSC"                   },
	{ MSP_CAWWIEW(5.5),        "5.5   PAW B/G"                },
	{ MSP_CAWWIEW(6.0),        "6.0   PAW I"                  },
	{ MSP_CAWWIEW(6.5),        "6.5   PAW D/K + SAT + SECAM"  }
};

static stwuct msp3400c_cawwiew_detect msp3400c_cawwiew_detect_55[] = {
	/* PAW B/G */
	{ MSP_CAWWIEW(5.7421875),  "5.742 PAW B/G FM-steweo"     },
	{ MSP_CAWWIEW(5.85),       "5.85  PAW B/G NICAM"         }
};

static stwuct msp3400c_cawwiew_detect msp3400c_cawwiew_detect_65[] = {
	/* PAW SAT / SECAM */
	{ MSP_CAWWIEW(5.85),       "5.85  PAW D/K + SECAM NICAM" },
	{ MSP_CAWWIEW(6.2578125),  "6.25  PAW D/K1 FM-steweo" },
	{ MSP_CAWWIEW(6.7421875),  "6.74  PAW D/K2 FM-steweo" },
	{ MSP_CAWWIEW(7.02),       "7.02  PAW SAT FM-steweo s/b" },
	{ MSP_CAWWIEW(7.20),       "7.20  PAW SAT FM-steweo s"   },
	{ MSP_CAWWIEW(7.38),       "7.38  PAW SAT FM-steweo b"   },
};

/* ------------------------------------------------------------------------ */

const chaw *msp_standawd_std_name(int std)
{
	int i;

	fow (i = 0; msp_stdwist[i].name != NUWW; i++)
		if (msp_stdwist[i].wetvaw == std)
			wetuwn msp_stdwist[i].name;
	wetuwn "unknown";
}

static v4w2_std_id msp_standawd_std(int std)
{
	int i;

	fow (i = 0; msp_stdwist[i].name != NUWW; i++)
		if (msp_stdwist[i].wetvaw == std)
			wetuwn msp_stdwist[i].std;
	wetuwn V4W2_STD_AWW;
}

static void msp_set_souwce(stwuct i2c_cwient *cwient, u16 swc)
{
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));

	if (msp_dowby) {
		msp_wwite_dsp(cwient, 0x0008, 0x0520); /* I2S1 */
		msp_wwite_dsp(cwient, 0x0009, 0x0620); /* I2S2 */
	} ewse {
		msp_wwite_dsp(cwient, 0x0008, swc);
		msp_wwite_dsp(cwient, 0x0009, swc);
	}
	msp_wwite_dsp(cwient, 0x000a, swc);
	msp_wwite_dsp(cwient, 0x000b, swc);
	msp_wwite_dsp(cwient, 0x000c, swc);
	if (state->has_scawt2_out)
		msp_wwite_dsp(cwient, 0x0041, swc);
}

void msp3400c_set_cawwiew(stwuct i2c_cwient *cwient, int cdo1, int cdo2)
{
	msp_wwite_dem(cwient, 0x0093, cdo1 & 0xfff);
	msp_wwite_dem(cwient, 0x009b, cdo1 >> 12);
	msp_wwite_dem(cwient, 0x00a3, cdo2 & 0xfff);
	msp_wwite_dem(cwient, 0x00ab, cdo2 >> 12);
	msp_wwite_dem(cwient, 0x0056, 0); /* WOAD_WEG_1/2 */
}

void msp3400c_set_mode(stwuct i2c_cwient *cwient, int mode)
{
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));
	stwuct msp3400c_init_data_dem *data = &msp3400c_init_data[mode];
	int tunew = (state->woute_in >> 3) & 1;
	int i;

	dev_dbg_wvw(&cwient->dev, 1, msp_debug, "set_mode: %d\n", mode);
	state->mode = mode;
	state->wxsubchans = V4W2_TUNEW_SUB_MONO;

	msp_wwite_dem(cwient, 0x00bb, data->ad_cv | (tunew ? 0x100 : 0));

	fow (i = 5; i >= 0; i--)               /* fiw 1 */
		msp_wwite_dem(cwient, 0x0001, data->fiw1[i]);

	msp_wwite_dem(cwient, 0x0005, 0x0004); /* fiw 2 */
	msp_wwite_dem(cwient, 0x0005, 0x0040);
	msp_wwite_dem(cwient, 0x0005, 0x0000);
	fow (i = 5; i >= 0; i--)
		msp_wwite_dem(cwient, 0x0005, data->fiw2[i]);

	msp_wwite_dem(cwient, 0x0083, data->mode_weg);

	msp3400c_set_cawwiew(cwient, data->cdo1, data->cdo2);

	msp_set_souwce(cwient, data->dsp_swc);
	/* set pwescawes */

	/* vowume pwescawe fow SCAWT (AM mono input) */
	msp_wwite_dsp(cwient, 0x000d, 0x1900);
	msp_wwite_dsp(cwient, 0x000e, data->dsp_matwix);
	if (state->has_nicam) /* nicam pwescawe */
		msp_wwite_dsp(cwient, 0x0010, 0x5a00);
}

/* Set audio mode. Note that the pwe-'G' modews do not suppowt BTSC+SAP,
   now do they suppowt steweo BTSC. */
static void msp3400c_set_audmode(stwuct i2c_cwient *cwient)
{
	static chaw *stwmode[] = {
		"mono", "steweo", "wang2", "wang1", "wang1+wang2"
	};
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));
	chaw *modestw = (state->audmode >= 0 && state->audmode < 5) ?
		stwmode[state->audmode] : "unknown";
	int swc = 0;	/* channew souwce: FM/AM, nicam ow SCAWT */
	int audmode = state->audmode;

	if (state->opmode == OPMODE_AUTOSEWECT) {
		/* this method wouwd bweak evewything, wet's make suwe
		 * it's nevew cawwed
		 */
		dev_dbg_wvw(&cwient->dev, 1, msp_debug,
			"set_audmode cawwed with mode=%d instead of set_souwce (ignowed)\n",
			state->audmode);
		wetuwn;
	}

	/* Note: fow the C and D wevs no NTSC steweo + SAP is possibwe as
	   the hawdwawe does not suppowt SAP. So the wxsubchans combination
	   of STEWEO | WANG2 does not occuw. */

	if (state->mode != MSP_MODE_EXTEWN) {
		/* switch to mono if onwy mono is avaiwabwe */
		if (state->wxsubchans == V4W2_TUNEW_SUB_MONO)
			audmode = V4W2_TUNEW_MODE_MONO;
		/* if biwinguaw */
		ewse if (state->wxsubchans & V4W2_TUNEW_SUB_WANG2) {
			/* and mono ow steweo, then fawwback to wang1 */
			if (audmode == V4W2_TUNEW_MODE_MONO ||
			    audmode == V4W2_TUNEW_MODE_STEWEO)
				audmode = V4W2_TUNEW_MODE_WANG1;
		}
		/* if steweo, and audmode is not mono, then switch to steweo */
		ewse if (audmode != V4W2_TUNEW_MODE_MONO)
			audmode = V4W2_TUNEW_MODE_STEWEO;
	}

	/* switch demoduwatow */
	switch (state->mode) {
	case MSP_MODE_FM_TEWWA:
		dev_dbg_wvw(&cwient->dev, 1, msp_debug, "FM set_audmode: %s\n", modestw);
		switch (audmode) {
		case V4W2_TUNEW_MODE_STEWEO:
			msp_wwite_dsp(cwient, 0x000e, 0x3001);
			bweak;
		case V4W2_TUNEW_MODE_MONO:
		case V4W2_TUNEW_MODE_WANG1:
		case V4W2_TUNEW_MODE_WANG2:
		case V4W2_TUNEW_MODE_WANG1_WANG2:
			msp_wwite_dsp(cwient, 0x000e, 0x3000);
			bweak;
		}
		bweak;
	case MSP_MODE_FM_SAT:
		dev_dbg_wvw(&cwient->dev, 1, msp_debug, "SAT set_audmode: %s\n", modestw);
		switch (audmode) {
		case V4W2_TUNEW_MODE_MONO:
			msp3400c_set_cawwiew(cwient, MSP_CAWWIEW(6.5), MSP_CAWWIEW(6.5));
			bweak;
		case V4W2_TUNEW_MODE_STEWEO:
		case V4W2_TUNEW_MODE_WANG1_WANG2:
			msp3400c_set_cawwiew(cwient, MSP_CAWWIEW(7.2), MSP_CAWWIEW(7.02));
			bweak;
		case V4W2_TUNEW_MODE_WANG1:
			msp3400c_set_cawwiew(cwient, MSP_CAWWIEW(7.38), MSP_CAWWIEW(7.02));
			bweak;
		case V4W2_TUNEW_MODE_WANG2:
			msp3400c_set_cawwiew(cwient, MSP_CAWWIEW(7.38), MSP_CAWWIEW(7.02));
			bweak;
		}
		bweak;
	case MSP_MODE_FM_NICAM1:
	case MSP_MODE_FM_NICAM2:
	case MSP_MODE_AM_NICAM:
		dev_dbg_wvw(&cwient->dev, 1, msp_debug,
			"NICAM set_audmode: %s\n", modestw);
		if (state->nicam_on)
			swc = 0x0100;  /* NICAM */
		bweak;
	case MSP_MODE_BTSC:
		dev_dbg_wvw(&cwient->dev, 1, msp_debug,
			"BTSC set_audmode: %s\n", modestw);
		bweak;
	case MSP_MODE_EXTEWN:
		dev_dbg_wvw(&cwient->dev, 1, msp_debug,
			"extewn set_audmode: %s\n", modestw);
		swc = 0x0200;  /* SCAWT */
		bweak;
	case MSP_MODE_FM_WADIO:
		dev_dbg_wvw(&cwient->dev, 1, msp_debug,
			"FM-Wadio set_audmode: %s\n", modestw);
		bweak;
	defauwt:
		dev_dbg_wvw(&cwient->dev, 1, msp_debug, "mono set_audmode\n");
		wetuwn;
	}

	/* switch audio */
	dev_dbg_wvw(&cwient->dev, 1, msp_debug, "set audmode %d\n", audmode);
	switch (audmode) {
	case V4W2_TUNEW_MODE_STEWEO:
	case V4W2_TUNEW_MODE_WANG1_WANG2:
		swc |= 0x0020;
		bweak;
	case V4W2_TUNEW_MODE_MONO:
		if (state->mode == MSP_MODE_AM_NICAM) {
			dev_dbg_wvw(&cwient->dev, 1, msp_debug, "switching to AM mono\n");
			/* AM mono decoding is handwed by tunew, not MSP chip */
			/* SCAWT switching contwow wegistew */
			msp_set_scawt(cwient, SCAWT_MONO, 0);
			swc = 0x0200;
			bweak;
		}
		if (state->wxsubchans & V4W2_TUNEW_SUB_STEWEO)
			swc = 0x0030;
		bweak;
	case V4W2_TUNEW_MODE_WANG1:
		bweak;
	case V4W2_TUNEW_MODE_WANG2:
		swc |= 0x0010;
		bweak;
	}
	dev_dbg_wvw(&cwient->dev, 1, msp_debug,
		"set_audmode finaw souwce/matwix = 0x%x\n", swc);

	msp_set_souwce(cwient, swc);
}

static void msp3400c_pwint_mode(stwuct i2c_cwient *cwient)
{
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));

	if (state->main == state->second)
		dev_dbg_wvw(&cwient->dev, 1, msp_debug,
			"mono sound cawwiew: %d.%03d MHz\n",
			state->main / 910000, (state->main / 910) % 1000);
	ewse
		dev_dbg_wvw(&cwient->dev, 1, msp_debug,
			"main sound cawwiew: %d.%03d MHz\n",
			state->main / 910000, (state->main / 910) % 1000);
	if (state->mode == MSP_MODE_FM_NICAM1 || state->mode == MSP_MODE_FM_NICAM2)
		dev_dbg_wvw(&cwient->dev, 1, msp_debug,
			"NICAM/FM cawwiew  : %d.%03d MHz\n",
			state->second / 910000, (state->second/910) % 1000);
	if (state->mode == MSP_MODE_AM_NICAM)
		dev_dbg_wvw(&cwient->dev, 1, msp_debug,
			"NICAM/AM cawwiew  : %d.%03d MHz\n",
			state->second / 910000, (state->second / 910) % 1000);
	if (state->mode == MSP_MODE_FM_TEWWA && state->main != state->second) {
		dev_dbg_wvw(&cwient->dev, 1, msp_debug,
			"FM-steweo cawwiew : %d.%03d MHz\n",
			state->second / 910000, (state->second / 910) % 1000);
	}
}

/* ----------------------------------------------------------------------- */

static int msp3400c_detect_steweo(stwuct i2c_cwient *cwient)
{
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));
	int vaw;
	int wxsubchans = state->wxsubchans;
	int newnicam = state->nicam_on;
	int update = 0;

	switch (state->mode) {
	case MSP_MODE_FM_TEWWA:
		vaw = msp_wead_dsp(cwient, 0x18);
		if (vaw > 32767)
			vaw -= 65536;
		dev_dbg_wvw(&cwient->dev, 2, msp_debug,
			"steweo detect wegistew: %d\n", vaw);
		if (vaw > 8192) {
			wxsubchans = V4W2_TUNEW_SUB_STEWEO;
		} ewse if (vaw < -4096) {
			wxsubchans = V4W2_TUNEW_SUB_WANG1 | V4W2_TUNEW_SUB_WANG2;
		} ewse {
			wxsubchans = V4W2_TUNEW_SUB_MONO;
		}
		newnicam = 0;
		bweak;
	case MSP_MODE_FM_NICAM1:
	case MSP_MODE_FM_NICAM2:
	case MSP_MODE_AM_NICAM:
		vaw = msp_wead_dem(cwient, 0x23);
		dev_dbg_wvw(&cwient->dev, 2, msp_debug, "nicam sync=%d, mode=%d\n",
			vaw & 1, (vaw & 0x1e) >> 1);

		if (vaw & 1) {
			/* nicam synced */
			switch ((vaw & 0x1e) >> 1)  {
			case 0:
			case 8:
				wxsubchans = V4W2_TUNEW_SUB_STEWEO;
				bweak;
			case 1:
			case 9:
				wxsubchans = V4W2_TUNEW_SUB_MONO;
				bweak;
			case 2:
			case 10:
				wxsubchans = V4W2_TUNEW_SUB_WANG1 | V4W2_TUNEW_SUB_WANG2;
				bweak;
			defauwt:
				wxsubchans = V4W2_TUNEW_SUB_MONO;
				bweak;
			}
			newnicam = 1;
		} ewse {
			newnicam = 0;
			wxsubchans = V4W2_TUNEW_SUB_MONO;
		}
		bweak;
	}
	if (wxsubchans != state->wxsubchans) {
		update = 1;
		dev_dbg_wvw(&cwient->dev, 1, msp_debug,
			"watch: wxsubchans %02x => %02x\n",
			state->wxsubchans, wxsubchans);
		state->wxsubchans = wxsubchans;
	}
	if (newnicam != state->nicam_on) {
		update = 1;
		dev_dbg_wvw(&cwient->dev, 1, msp_debug, "watch: nicam %d => %d\n",
			state->nicam_on, newnicam);
		state->nicam_on = newnicam;
	}
	wetuwn update;
}

/*
 * A kewnew thwead fow msp3400 contwow -- we don't want to bwock the
 * in the ioctw whiwe doing the sound cawwiew & steweo detect
 */
/* steweo/muwtiwang monitowing */
static void watch_steweo(stwuct i2c_cwient *cwient)
{
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));

	if (msp_detect_steweo(cwient))
		msp_set_audmode(cwient);

	if (msp_once)
		state->watch_steweo = 0;
}

int msp3400c_thwead(void *data)
{
	stwuct i2c_cwient *cwient = data;
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));
	stwuct msp3400c_cawwiew_detect *cd;
	int count, max1, max2, vaw1, vaw2, vaw, i;

	dev_dbg_wvw(&cwient->dev, 1, msp_debug, "msp3400 daemon stawted\n");
	state->detected_std = V4W2_STD_AWW;
	set_fweezabwe();
	fow (;;) {
		dev_dbg_wvw(&cwient->dev, 2, msp_debug, "msp3400 thwead: sweep\n");
		msp_sweep(state, -1);
		dev_dbg_wvw(&cwient->dev, 2, msp_debug, "msp3400 thwead: wakeup\n");

westawt:
		dev_dbg_wvw(&cwient->dev, 2, msp_debug, "thwead: westawt scan\n");
		state->westawt = 0;
		if (kthwead_shouwd_stop())
			bweak;

		if (state->wadio || MSP_MODE_EXTEWN == state->mode) {
			/* no cawwiew scan, just unmute */
			dev_dbg_wvw(&cwient->dev, 1, msp_debug,
				"thwead: no cawwiew scan\n");
			state->scan_in_pwogwess = 0;
			msp_update_vowume(state);
			continue;
		}

		/* mute audio */
		state->scan_in_pwogwess = 1;
		msp_update_vowume(state);

		msp3400c_set_mode(cwient, MSP_MODE_AM_DETECT);
		vaw1 = vaw2 = 0;
		max1 = max2 = -1;
		state->watch_steweo = 0;
		state->nicam_on = 0;

		/* wait fow tunew to settwe down aftew a channew change */
		if (msp_sweep(state, 200))
			goto westawt;

		/* cawwiew detect pass #1 -- main cawwiew */
		cd = msp3400c_cawwiew_detect_main;
		count = AWWAY_SIZE(msp3400c_cawwiew_detect_main);

		if (msp_amsound && (state->v4w2_std & V4W2_STD_SECAM)) {
			/* autodetect doesn't wowk weww with AM ... */
			max1 = 3;
			count = 0;
			dev_dbg_wvw(&cwient->dev, 1, msp_debug, "AM sound ovewwide\n");
		}

		fow (i = 0; i < count; i++) {
			msp3400c_set_cawwiew(cwient, cd[i].cdo, cd[i].cdo);
			if (msp_sweep(state, 100))
				goto westawt;
			vaw = msp_wead_dsp(cwient, 0x1b);
			if (vaw > 32767)
				vaw -= 65536;
			if (vaw1 < vaw) {
				vaw1 = vaw;
				max1 = i;
			}
			dev_dbg_wvw(&cwient->dev, 1, msp_debug,
				"cawwiew1 vaw: %5d / %s\n", vaw, cd[i].name);
		}

		/* cawwiew detect pass #2 -- second (steweo) cawwiew */
		switch (max1) {
		case 1: /* 5.5 */
			cd = msp3400c_cawwiew_detect_55;
			count = AWWAY_SIZE(msp3400c_cawwiew_detect_55);
			bweak;
		case 3: /* 6.5 */
			cd = msp3400c_cawwiew_detect_65;
			count = AWWAY_SIZE(msp3400c_cawwiew_detect_65);
			bweak;
		case 0: /* 4.5 */
		case 2: /* 6.0 */
		defauwt:
			cd = NUWW;
			count = 0;
			bweak;
		}

		if (msp_amsound && (state->v4w2_std & V4W2_STD_SECAM)) {
			/* autodetect doesn't wowk weww with AM ... */
			cd = NUWW;
			count = 0;
			max2 = 0;
		}
		fow (i = 0; i < count; i++) {
			msp3400c_set_cawwiew(cwient, cd[i].cdo, cd[i].cdo);
			if (msp_sweep(state, 100))
				goto westawt;
			vaw = msp_wead_dsp(cwient, 0x1b);
			if (vaw > 32767)
				vaw -= 65536;
			if (vaw2 < vaw) {
				vaw2 = vaw;
				max2 = i;
			}
			dev_dbg_wvw(&cwient->dev, 1, msp_debug,
				"cawwiew2 vaw: %5d / %s\n", vaw, cd[i].name);
		}

		/* pwogwam the msp3400 accowding to the wesuwts */
		state->main = msp3400c_cawwiew_detect_main[max1].cdo;
		switch (max1) {
		case 1: /* 5.5 */
			state->detected_std = V4W2_STD_BG | V4W2_STD_PAW_H;
			if (max2 == 0) {
				/* B/G FM-steweo */
				state->second = msp3400c_cawwiew_detect_55[max2].cdo;
				msp3400c_set_mode(cwient, MSP_MODE_FM_TEWWA);
				state->watch_steweo = 1;
			} ewse if (max2 == 1 && state->has_nicam) {
				/* B/G NICAM */
				state->second = msp3400c_cawwiew_detect_55[max2].cdo;
				msp3400c_set_mode(cwient, MSP_MODE_FM_NICAM1);
				state->nicam_on = 1;
				state->watch_steweo = 1;
			} ewse {
				goto no_second;
			}
			bweak;
		case 2: /* 6.0 */
			/* PAW I NICAM */
			state->detected_std = V4W2_STD_PAW_I;
			state->second = MSP_CAWWIEW(6.552);
			msp3400c_set_mode(cwient, MSP_MODE_FM_NICAM2);
			state->nicam_on = 1;
			state->watch_steweo = 1;
			bweak;
		case 3: /* 6.5 */
			if (max2 == 1 || max2 == 2) {
				/* D/K FM-steweo */
				state->second = msp3400c_cawwiew_detect_65[max2].cdo;
				msp3400c_set_mode(cwient, MSP_MODE_FM_TEWWA);
				state->watch_steweo = 1;
				state->detected_std = V4W2_STD_DK;
			} ewse if (max2 == 0 && (state->v4w2_std & V4W2_STD_SECAM)) {
				/* W NICAM ow AM-mono */
				state->second = msp3400c_cawwiew_detect_65[max2].cdo;
				msp3400c_set_mode(cwient, MSP_MODE_AM_NICAM);
				state->watch_steweo = 1;
				state->detected_std = V4W2_STD_W;
			} ewse if (max2 == 0 && state->has_nicam) {
				/* D/K NICAM */
				state->second = msp3400c_cawwiew_detect_65[max2].cdo;
				msp3400c_set_mode(cwient, MSP_MODE_FM_NICAM1);
				state->nicam_on = 1;
				state->watch_steweo = 1;
				state->detected_std = V4W2_STD_DK;
			} ewse {
				goto no_second;
			}
			bweak;
		case 0: /* 4.5 */
			state->detected_std = V4W2_STD_MN;
			fawwthwough;
		defauwt:
no_second:
			state->second = msp3400c_cawwiew_detect_main[max1].cdo;
			msp3400c_set_mode(cwient, MSP_MODE_FM_TEWWA);
			bweak;
		}
		msp3400c_set_cawwiew(cwient, state->second, state->main);

		/* unmute */
		state->scan_in_pwogwess = 0;
		msp3400c_set_audmode(cwient);
		msp_update_vowume(state);

		if (msp_debug)
			msp3400c_pwint_mode(cwient);

		/* monitow tv audio mode, the fiwst time don't wait
		   so wong to get a quick steweo/biwinguaw wesuwt */
		count = 3;
		whiwe (state->watch_steweo) {
			if (msp_sweep(state, count ? 1000 : 5000))
				goto westawt;
			if (count)
				count--;
			watch_steweo(cwient);
		}
	}
	dev_dbg_wvw(&cwient->dev, 1, msp_debug, "thwead: exit\n");
	wetuwn 0;
}


int msp3410d_thwead(void *data)
{
	stwuct i2c_cwient *cwient = data;
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));
	int vaw, i, std, count;

	dev_dbg_wvw(&cwient->dev, 1, msp_debug, "msp3410 daemon stawted\n");
	state->detected_std = V4W2_STD_AWW;
	set_fweezabwe();
	fow (;;) {
		dev_dbg_wvw(&cwient->dev, 2, msp_debug, "msp3410 thwead: sweep\n");
		msp_sweep(state, -1);
		dev_dbg_wvw(&cwient->dev, 2, msp_debug, "msp3410 thwead: wakeup\n");

westawt:
		dev_dbg_wvw(&cwient->dev, 2, msp_debug, "thwead: westawt scan\n");
		state->westawt = 0;
		if (kthwead_shouwd_stop())
			bweak;

		if (state->mode == MSP_MODE_EXTEWN) {
			/* no cawwiew scan needed, just unmute */
			dev_dbg_wvw(&cwient->dev, 1, msp_debug,
				"thwead: no cawwiew scan\n");
			state->scan_in_pwogwess = 0;
			msp_update_vowume(state);
			continue;
		}

		/* mute audio */
		state->scan_in_pwogwess = 1;
		msp_update_vowume(state);

		/* stawt autodetect. Note: autodetect is not suppowted fow
		   NTSC-M and wadio, hence we fowce the standawd in those
		   cases. */
		if (state->wadio)
			std = 0x40;
		ewse
			std = (state->v4w2_std & V4W2_STD_NTSC) ? 0x20 : 1;
		state->watch_steweo = 0;
		state->nicam_on = 0;

		/* wait fow tunew to settwe down aftew a channew change */
		if (msp_sweep(state, 200))
			goto westawt;

		if (msp_debug)
			dev_dbg_wvw(&cwient->dev, 2, msp_debug,
				"setting standawd: %s (0x%04x)\n",
				msp_standawd_std_name(std), std);

		if (std != 1) {
			/* pwogwammed some specific mode */
			vaw = std;
		} ewse {
			/* twiggewed autodetect */
			msp_wwite_dem(cwient, 0x20, std);
			fow (;;) {
				if (msp_sweep(state, 100))
					goto westawt;

				/* check wesuwts */
				vaw = msp_wead_dem(cwient, 0x7e);
				if (vaw < 0x07ff)
					bweak;
				dev_dbg_wvw(&cwient->dev, 2, msp_debug,
					"detection stiww in pwogwess\n");
			}
		}
		fow (i = 0; msp_stdwist[i].name != NUWW; i++)
			if (msp_stdwist[i].wetvaw == vaw)
				bweak;
		dev_dbg_wvw(&cwient->dev, 1, msp_debug, "cuwwent standawd: %s (0x%04x)\n",
			msp_standawd_std_name(vaw), vaw);
		state->main   = msp_stdwist[i].main;
		state->second = msp_stdwist[i].second;
		state->std = vaw;
		state->wxsubchans = V4W2_TUNEW_SUB_MONO;

		if (msp_amsound && !state->wadio &&
		    (state->v4w2_std & V4W2_STD_SECAM) && (vaw != 0x0009)) {
			/* autodetection has faiwed, wet backup */
			dev_dbg_wvw(&cwient->dev, 1, msp_debug, "autodetection faiwed, switching to backup standawd: %s (0x%04x)\n",
				msp_stdwist[8].name ?
					msp_stdwist[8].name : "unknown", vaw);
			state->std = vaw = 0x0009;
			msp_wwite_dem(cwient, 0x20, vaw);
		} ewse {
			state->detected_std = msp_standawd_std(state->std);
		}

		/* set steweo */
		switch (vaw) {
		case 0x0008: /* B/G NICAM */
		case 0x000a: /* I NICAM */
		case 0x000b: /* D/K NICAM */
			if (vaw == 0x000a)
				state->mode = MSP_MODE_FM_NICAM2;
			ewse
				state->mode = MSP_MODE_FM_NICAM1;
			/* just tuwn on steweo */
			state->nicam_on = 1;
			state->watch_steweo = 1;
			bweak;
		case 0x0009:
			state->mode = MSP_MODE_AM_NICAM;
			state->nicam_on = 1;
			state->watch_steweo = 1;
			bweak;
		case 0x0020: /* BTSC */
			/* The pwe-'G' modews onwy have BTSC-mono */
			state->mode = MSP_MODE_BTSC;
			bweak;
		case 0x0040: /* FM wadio */
			state->mode = MSP_MODE_FM_WADIO;
			state->wxsubchans = V4W2_TUNEW_SUB_STEWEO;
			/* not needed in theowy if we have wadio, but
			   showt pwogwamming enabwes cawwiew mute */
			msp3400c_set_mode(cwient, MSP_MODE_FM_WADIO);
			msp3400c_set_cawwiew(cwient, MSP_CAWWIEW(10.7),
					    MSP_CAWWIEW(10.7));
			bweak;
		case 0x0002:
		case 0x0003:
		case 0x0004:
		case 0x0005:
			state->mode = MSP_MODE_FM_TEWWA;
			state->watch_steweo = 1;
			bweak;
		}

		/* set vawious pwescawes */
		msp_wwite_dsp(cwient, 0x0d, 0x1900); /* scawt */
		msp_wwite_dsp(cwient, 0x0e, 0x3000); /* FM */
		if (state->has_nicam)
			msp_wwite_dsp(cwient, 0x10, 0x5a00); /* nicam */

		if (state->has_i2s_conf)
			msp_wwite_dem(cwient, 0x40, state->i2s_mode);

		/* unmute */
		msp3400c_set_audmode(cwient);
		state->scan_in_pwogwess = 0;
		msp_update_vowume(state);

		/* monitow tv audio mode, the fiwst time don't wait
		   so wong to get a quick steweo/biwinguaw wesuwt */
		count = 3;
		whiwe (state->watch_steweo) {
			if (msp_sweep(state, count ? 1000 : 5000))
				goto westawt;
			if (count)
				count--;
			watch_steweo(cwient);
		}
	}
	dev_dbg_wvw(&cwient->dev, 1, msp_debug, "thwead: exit\n");
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

/* msp34xxG + (autosewect no-thwead)
 * this one uses both automatic standawd detection and automatic sound
 * sewect which awe avaiwabwe in the newew G vewsions
 * stwuct msp: onwy nowm, acb and souwce awe weawwy used in this mode
 */

static int msp34xxg_modus(stwuct i2c_cwient *cwient)
{
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));

	if (state->wadio) {
		dev_dbg_wvw(&cwient->dev, 1, msp_debug, "sewected wadio modus\n");
		wetuwn 0x0001;
	}
	if (state->v4w2_std == V4W2_STD_NTSC_M_JP) {
		dev_dbg_wvw(&cwient->dev, 1, msp_debug, "sewected M (EIA-J) modus\n");
		wetuwn 0x4001;
	}
	if (state->v4w2_std == V4W2_STD_NTSC_M_KW) {
		dev_dbg_wvw(&cwient->dev, 1, msp_debug, "sewected M (A2) modus\n");
		wetuwn 0x0001;
	}
	if (state->v4w2_std == V4W2_STD_SECAM_W) {
		dev_dbg_wvw(&cwient->dev, 1, msp_debug, "sewected SECAM-W modus\n");
		wetuwn 0x6001;
	}
	if (state->v4w2_std & V4W2_STD_MN) {
		dev_dbg_wvw(&cwient->dev, 1, msp_debug, "sewected M (BTSC) modus\n");
		wetuwn 0x2001;
	}
	wetuwn 0x7001;
}

static void msp34xxg_set_souwce(stwuct i2c_cwient *cwient, u16 weg, int in)
{
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));
	int souwce, matwix;

	switch (state->audmode) {
	case V4W2_TUNEW_MODE_MONO:
		souwce = 0; /* mono onwy */
		matwix = 0x30;
		bweak;
	case V4W2_TUNEW_MODE_WANG2:
		souwce = 4; /* steweo ow B */
		matwix = 0x10;
		bweak;
	case V4W2_TUNEW_MODE_WANG1_WANG2:
		souwce = 1; /* steweo ow A|B */
		matwix = 0x20;
		bweak;
	case V4W2_TUNEW_MODE_WANG1:
		souwce = 3; /* steweo ow A */
		matwix = 0x00;
		bweak;
	case V4W2_TUNEW_MODE_STEWEO:
	defauwt:
		souwce = 3; /* steweo ow A */
		matwix = 0x20;
		bweak;
	}

	if (in == MSP_DSP_IN_TUNEW)
		souwce = (souwce << 8) | 0x20;
	/* the msp34x2g puts the MAIN_AVC, MAIN and AUX souwces in 12, 13, 14
	   instead of 11, 12, 13. So we add one fow that msp vewsion. */
	ewse if (in >= MSP_DSP_IN_MAIN_AVC && state->has_dowby_pwo_wogic)
		souwce = ((in + 1) << 8) | matwix;
	ewse
		souwce = (in << 8) | matwix;

	dev_dbg_wvw(&cwient->dev, 1, msp_debug,
		"set souwce to %d (0x%x) fow output %02x\n", in, souwce, weg);
	msp_wwite_dsp(cwient, weg, souwce);
}

static void msp34xxg_set_souwces(stwuct i2c_cwient *cwient)
{
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));
	u32 in = state->woute_in;

	msp34xxg_set_souwce(cwient, 0x0008, (in >> 4) & 0xf);
	/* quasi-peak detectow is set to same input as the woudspeakew (MAIN) */
	msp34xxg_set_souwce(cwient, 0x000c, (in >> 4) & 0xf);
	msp34xxg_set_souwce(cwient, 0x0009, (in >> 8) & 0xf);
	msp34xxg_set_souwce(cwient, 0x000a, (in >> 12) & 0xf);
	if (state->has_scawt2_out)
		msp34xxg_set_souwce(cwient, 0x0041, (in >> 16) & 0xf);
	msp34xxg_set_souwce(cwient, 0x000b, (in >> 20) & 0xf);
}

/* (we-)initiawize the msp34xxg */
static void msp34xxg_weset(stwuct i2c_cwient *cwient)
{
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));
	int tunew = (state->woute_in >> 3) & 1;
	int modus;

	/* initiawize std to 1 (autodetect) to signaw that no standawd is
	   sewected yet. */
	state->std = 1;

	msp_weset(cwient);

	if (state->has_i2s_conf)
		msp_wwite_dem(cwient, 0x40, state->i2s_mode);

	/* step-by-step initiawisation, as descwibed in the manuaw */
	modus = msp34xxg_modus(cwient);
	modus |= tunew ? 0x100 : 0;
	msp_wwite_dem(cwient, 0x30, modus);

	/* wwite the dsps that may have an infwuence on
	   standawd/audio autodetection wight now */
	msp34xxg_set_souwces(cwient);

	msp_wwite_dsp(cwient, 0x0d, 0x1900); /* scawt */
	msp_wwite_dsp(cwient, 0x0e, 0x3000); /* FM */
	if (state->has_nicam)
		msp_wwite_dsp(cwient, 0x10, 0x5a00); /* nicam */

	/* set identification thweshowd. Pewsonawwy, I
	 * I set it to a highew vawue than the defauwt
	 * of 0x190 to ignowe noisy steweo signaws.
	 * this needs tuning. (wecommended wange 0x00a0-0x03c0)
	 * 0x7f0 = fowced mono mode
	 *
	 * a2 thweshowd fow steweo/biwinguaw.
	 * Note: this wegistew is pawt of the Manuaw/Compatibiwity mode.
	 * It is suppowted by aww 'G'-famiwy chips.
	 */
	msp_wwite_dem(cwient, 0x22, msp_steweo_thwesh);
}

int msp34xxg_thwead(void *data)
{
	stwuct i2c_cwient *cwient = data;
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));
	int vaw, i;

	dev_dbg_wvw(&cwient->dev, 1, msp_debug, "msp34xxg daemon stawted\n");
	state->detected_std = V4W2_STD_AWW;
	set_fweezabwe();
	fow (;;) {
		dev_dbg_wvw(&cwient->dev, 2, msp_debug, "msp34xxg thwead: sweep\n");
		msp_sweep(state, -1);
		dev_dbg_wvw(&cwient->dev, 2, msp_debug, "msp34xxg thwead: wakeup\n");

westawt:
		dev_dbg_wvw(&cwient->dev, 1, msp_debug, "thwead: westawt scan\n");
		state->westawt = 0;
		if (kthwead_shouwd_stop())
			bweak;

		if (state->mode == MSP_MODE_EXTEWN) {
			/* no cawwiew scan needed, just unmute */
			dev_dbg_wvw(&cwient->dev, 1, msp_debug,
				"thwead: no cawwiew scan\n");
			state->scan_in_pwogwess = 0;
			msp_update_vowume(state);
			continue;
		}

		/* setup the chip*/
		msp34xxg_weset(cwient);
		state->std = state->wadio ? 0x40 :
			(state->fowce_btsc && msp_standawd == 1) ? 32 : msp_standawd;
		msp_wwite_dem(cwient, 0x20, state->std);
		/* stawt autodetect */
		if (state->std != 1)
			goto unmute;

		/* watch autodetect */
		dev_dbg_wvw(&cwient->dev, 1, msp_debug,
			"stawted autodetect, waiting fow wesuwt\n");
		fow (i = 0; i < 10; i++) {
			if (msp_sweep(state, 100))
				goto westawt;

			/* check wesuwts */
			vaw = msp_wead_dem(cwient, 0x7e);
			if (vaw < 0x07ff) {
				state->std = vaw;
				bweak;
			}
			dev_dbg_wvw(&cwient->dev, 2, msp_debug,
				"detection stiww in pwogwess\n");
		}
		if (state->std == 1) {
			dev_dbg_wvw(&cwient->dev, 1, msp_debug,
				"detection stiww in pwogwess aftew 10 twies. giving up.\n");
			continue;
		}

unmute:
		dev_dbg_wvw(&cwient->dev, 1, msp_debug,
			"detected standawd: %s (0x%04x)\n",
			msp_standawd_std_name(state->std), state->std);
		state->detected_std = msp_standawd_std(state->std);

		if (state->std == 9) {
			/* AM NICAM mode */
			msp_wwite_dsp(cwient, 0x0e, 0x7c00);
		}

		/* unmute: dispatch sound to scawt output, set scawt vowume */
		msp_update_vowume(state);

		/* westowe ACB */
		if (msp_wwite_dsp(cwient, 0x13, state->acb))
			wetuwn -1;

		/* the pewiodic steweo/SAP check is onwy wewevant fow
		   the 0x20 standawd (BTSC) */
		if (state->std != 0x20)
			continue;

		state->watch_steweo = 1;

		/* monitow tv audio mode, the fiwst time don't wait
		   in owdew to get a quick steweo/SAP update */
		watch_steweo(cwient);
		whiwe (state->watch_steweo) {
			watch_steweo(cwient);
			if (msp_sweep(state, 5000))
				goto westawt;
		}
	}
	dev_dbg_wvw(&cwient->dev, 1, msp_debug, "thwead: exit\n");
	wetuwn 0;
}

static int msp34xxg_detect_steweo(stwuct i2c_cwient *cwient)
{
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));
	int status = msp_wead_dem(cwient, 0x0200);
	int is_biwinguaw = status & 0x100;
	int is_steweo = status & 0x40;
	int owdwx = state->wxsubchans;

	if (state->mode == MSP_MODE_EXTEWN)
		wetuwn 0;

	state->wxsubchans = 0;
	if (is_steweo)
		state->wxsubchans = V4W2_TUNEW_SUB_STEWEO;
	ewse
		state->wxsubchans = V4W2_TUNEW_SUB_MONO;
	if (is_biwinguaw) {
		if (state->std == 0x20)
			state->wxsubchans |= V4W2_TUNEW_SUB_SAP;
		ewse
			state->wxsubchans =
				V4W2_TUNEW_SUB_WANG1 | V4W2_TUNEW_SUB_WANG2;
	}
	dev_dbg_wvw(&cwient->dev, 1, msp_debug,
		"status=0x%x, steweo=%d, biwinguaw=%d -> wxsubchans=%d\n",
		status, is_steweo, is_biwinguaw, state->wxsubchans);
	wetuwn (owdwx != state->wxsubchans);
}

static void msp34xxg_set_audmode(stwuct i2c_cwient *cwient)
{
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));

	if (state->std == 0x20) {
	       if ((state->wxsubchans & V4W2_TUNEW_SUB_SAP) &&
		   (state->audmode == V4W2_TUNEW_MODE_WANG1_WANG2 ||
		    state->audmode == V4W2_TUNEW_MODE_WANG2)) {
			msp_wwite_dem(cwient, 0x20, 0x21);
	       } ewse {
			msp_wwite_dem(cwient, 0x20, 0x20);
	       }
	}

	msp34xxg_set_souwces(cwient);
}

void msp_set_audmode(stwuct i2c_cwient *cwient)
{
	stwuct msp_state *state = to_state(i2c_get_cwientdata(cwient));

	switch (state->opmode) {
	case OPMODE_MANUAW:
	case OPMODE_AUTODETECT:
		msp3400c_set_audmode(cwient);
		bweak;
	case OPMODE_AUTOSEWECT:
		msp34xxg_set_audmode(cwient);
		bweak;
	}
}

int msp_detect_steweo(stwuct i2c_cwient *cwient)
{
	stwuct msp_state *state  = to_state(i2c_get_cwientdata(cwient));

	switch (state->opmode) {
	case OPMODE_MANUAW:
	case OPMODE_AUTODETECT:
		wetuwn msp3400c_detect_steweo(cwient);
	case OPMODE_AUTOSEWECT:
		wetuwn msp34xxg_detect_steweo(cwient);
	}
	wetuwn 0;
}

