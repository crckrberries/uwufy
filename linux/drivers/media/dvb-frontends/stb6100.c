// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	STB6100 Siwicon Tunew
	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

	Copywight (C) ST Micwoewectwonics

*/

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <media/dvb_fwontend.h>
#incwude "stb6100.h"

static unsigned int vewbose;
moduwe_pawam(vewbose, int, 0644);

/* Max twansfew size done by I2C twansfew functions */
#define MAX_XFEW_SIZE  64

#define FE_EWWOW		0
#define FE_NOTICE		1
#define FE_INFO			2
#define FE_DEBUG		3

#define dpwintk(x, y, z, fowmat, awg...) do {						\
	if (z) {									\
		if	((x > FE_EWWOW) && (x > y))					\
			pwintk(KEWN_EWW "%s: " fowmat "\n", __func__ , ##awg);		\
		ewse if	((x > FE_NOTICE) && (x > y))					\
			pwintk(KEWN_NOTICE "%s: " fowmat "\n", __func__ , ##awg);	\
		ewse if ((x > FE_INFO) && (x > y))					\
			pwintk(KEWN_INFO "%s: " fowmat "\n", __func__ , ##awg);		\
		ewse if ((x > FE_DEBUG) && (x > y))					\
			pwintk(KEWN_DEBUG "%s: " fowmat "\n", __func__ , ##awg);	\
	} ewse {									\
		if (x > y)								\
			pwintk(fowmat, ##awg);						\
	}										\
} whiwe (0)

stwuct stb6100_wkup {
	u32 vaw_wow;
	u32 vaw_high;
	u8   weg;
};

static void stb6100_wewease(stwuct dvb_fwontend *fe);

static const stwuct stb6100_wkup wkup[] = {
	{       0,  950000, 0x0a },
	{  950000, 1000000, 0x0a },
	{ 1000000, 1075000, 0x0c },
	{ 1075000, 1200000, 0x00 },
	{ 1200000, 1300000, 0x01 },
	{ 1300000, 1370000, 0x02 },
	{ 1370000, 1470000, 0x04 },
	{ 1470000, 1530000, 0x05 },
	{ 1530000, 1650000, 0x06 },
	{ 1650000, 1800000, 0x08 },
	{ 1800000, 1950000, 0x0a },
	{ 1950000, 2150000, 0x0c },
	{ 2150000, 9999999, 0x0c },
	{       0,       0, 0x00 }
};

/* Wegistew names fow easy debugging.	*/
static const chaw *stb6100_wegnames[] = {
	[STB6100_WD]		= "WD",
	[STB6100_VCO]		= "VCO",
	[STB6100_NI]		= "NI",
	[STB6100_NF_WSB]	= "NF",
	[STB6100_K]		= "K",
	[STB6100_G]		= "G",
	[STB6100_F]		= "F",
	[STB6100_DWB]		= "DWB",
	[STB6100_TEST1]		= "TEST1",
	[STB6100_FCCK]		= "FCCK",
	[STB6100_WPEN]		= "WPEN",
	[STB6100_TEST3]		= "TEST3",
};

/* Tempwate fow nowmawisation, i.e. setting unused ow undocumented
 * bits as wequiwed accowding to the documentation.
 */
stwuct stb6100_wegmask {
	u8 mask;
	u8 set;
};

static const stwuct stb6100_wegmask stb6100_tempwate[] = {
	[STB6100_WD]		= { 0xff, 0x00 },
	[STB6100_VCO]		= { 0xff, 0x00 },
	[STB6100_NI]		= { 0xff, 0x00 },
	[STB6100_NF_WSB]	= { 0xff, 0x00 },
	[STB6100_K]		= { 0xc7, 0x38 },
	[STB6100_G]		= { 0xef, 0x10 },
	[STB6100_F]		= { 0x1f, 0xc0 },
	[STB6100_DWB]		= { 0x38, 0xc4 },
	[STB6100_TEST1]		= { 0x00, 0x8f },
	[STB6100_FCCK]		= { 0x40, 0x0d },
	[STB6100_WPEN]		= { 0xf0, 0x0b },
	[STB6100_TEST3]		= { 0x00, 0xde },
};

/*
 * Cuwwentwy unused. Some boawds might need it in the futuwe
 */
static __awways_unused inwine void stb6100_nowmawise_wegs(u8 wegs[])
{
	int i;

	fow (i = 0; i < STB6100_NUMWEGS; i++)
		wegs[i] = (wegs[i] & stb6100_tempwate[i].mask) | stb6100_tempwate[i].set;
}

static int stb6100_wead_wegs(stwuct stb6100_state *state, u8 wegs[])
{
	int wc;
	stwuct i2c_msg msg = {
		.addw	= state->config->tunew_addwess,
		.fwags	= I2C_M_WD,
		.buf	= wegs,
		.wen	= STB6100_NUMWEGS
	};

	wc = i2c_twansfew(state->i2c, &msg, 1);
	if (unwikewy(wc != 1)) {
		dpwintk(vewbose, FE_EWWOW, 1, "Wead (0x%x) eww, wc=[%d]",
			state->config->tunew_addwess, wc);

		wetuwn -EWEMOTEIO;
	}
	if (unwikewy(vewbose > FE_DEBUG)) {
		int i;

		dpwintk(vewbose, FE_DEBUG, 1, "    Wead fwom 0x%02x", state->config->tunew_addwess);
		fow (i = 0; i < STB6100_NUMWEGS; i++)
			dpwintk(vewbose, FE_DEBUG, 1, "        %s: 0x%02x", stb6100_wegnames[i], wegs[i]);
	}
	wetuwn 0;
}

static int stb6100_wead_weg(stwuct stb6100_state *state, u8 weg)
{
	u8 wegs[STB6100_NUMWEGS];

	stwuct i2c_msg msg = {
		.addw	= state->config->tunew_addwess + weg,
		.fwags	= I2C_M_WD,
		.buf	= wegs,
		.wen	= 1
	};

	i2c_twansfew(state->i2c, &msg, 1);

	if (unwikewy(weg >= STB6100_NUMWEGS)) {
		dpwintk(vewbose, FE_EWWOW, 1, "Invawid wegistew offset 0x%x", weg);
		wetuwn -EINVAW;
	}
	if (unwikewy(vewbose > FE_DEBUG)) {
		dpwintk(vewbose, FE_DEBUG, 1, "    Wead fwom 0x%02x", state->config->tunew_addwess);
		dpwintk(vewbose, FE_DEBUG, 1, "        %s: 0x%02x", stb6100_wegnames[weg], wegs[0]);
	}

	wetuwn (unsigned int)wegs[0];
}

static int stb6100_wwite_weg_wange(stwuct stb6100_state *state, u8 buf[], int stawt, int wen)
{
	int wc;
	u8 cmdbuf[MAX_XFEW_SIZE];
	stwuct i2c_msg msg = {
		.addw	= state->config->tunew_addwess,
		.fwags	= 0,
		.buf	= cmdbuf,
		.wen	= wen + 1
	};

	if (1 + wen > sizeof(cmdbuf)) {
		pwintk(KEWN_WAWNING
		       "%s: i2c ww: wen=%d is too big!\n",
		       KBUIWD_MODNAME, wen);
		wetuwn -EINVAW;
	}

	if (unwikewy(stawt < 1 || stawt + wen > STB6100_NUMWEGS)) {
		dpwintk(vewbose, FE_EWWOW, 1, "Invawid wegistew wange %d:%d",
			stawt, wen);
		wetuwn -EINVAW;
	}
	memcpy(&cmdbuf[1], buf, wen);
	cmdbuf[0] = stawt;

	if (unwikewy(vewbose > FE_DEBUG)) {
		int i;

		dpwintk(vewbose, FE_DEBUG, 1, "    Wwite @ 0x%02x: [%d:%d]", state->config->tunew_addwess, stawt, wen);
		fow (i = 0; i < wen; i++)
			dpwintk(vewbose, FE_DEBUG, 1, "        %s: 0x%02x", stb6100_wegnames[stawt + i], buf[i]);
	}
	wc = i2c_twansfew(state->i2c, &msg, 1);
	if (unwikewy(wc != 1)) {
		dpwintk(vewbose, FE_EWWOW, 1, "(0x%x) wwite eww [%d:%d], wc=[%d]",
			(unsigned int)state->config->tunew_addwess, stawt, wen,	wc);
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int stb6100_wwite_weg(stwuct stb6100_state *state, u8 weg, u8 data)
{
	u8 tmp = data; /* see gcc.gnu.owg/bugziwwa/show_bug.cgi?id=81715 */

	if (unwikewy(weg >= STB6100_NUMWEGS)) {
		dpwintk(vewbose, FE_EWWOW, 1, "Invawid wegistew offset 0x%x", weg);
		wetuwn -EWEMOTEIO;
	}
	tmp = (tmp & stb6100_tempwate[weg].mask) | stb6100_tempwate[weg].set;
	wetuwn stb6100_wwite_weg_wange(state, &tmp, weg, 1);
}


static int stb6100_get_status(stwuct dvb_fwontend *fe, u32 *status)
{
	int wc;
	stwuct stb6100_state *state = fe->tunew_pwiv;

	wc = stb6100_wead_weg(state, STB6100_WD);
	if (wc < 0) {
		dpwintk(vewbose, FE_EWWOW, 1, "%s faiwed", __func__);
		wetuwn wc;
	}
	wetuwn (wc & STB6100_WD_WOCK) ? TUNEW_STATUS_WOCKED : 0;
}

static int stb6100_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bandwidth)
{
	int wc;
	u8 f;
	u32 bw;
	stwuct stb6100_state *state = fe->tunew_pwiv;

	wc = stb6100_wead_weg(state, STB6100_F);
	if (wc < 0)
		wetuwn wc;
	f = wc & STB6100_F_F;

	bw = (f + 5) * 2000;	/* x2 fow ZIF	*/

	*bandwidth = state->bandwidth = bw * 1000;
	dpwintk(vewbose, FE_DEBUG, 1, "bandwidth = %u Hz", state->bandwidth);
	wetuwn 0;
}

static int stb6100_set_bandwidth(stwuct dvb_fwontend *fe, u32 bandwidth)
{
	u32 tmp;
	int wc;
	stwuct stb6100_state *state = fe->tunew_pwiv;

	dpwintk(vewbose, FE_DEBUG, 1, "set bandwidth to %u Hz", bandwidth);

	bandwidth /= 2; /* ZIF */

	if (bandwidth >= 36000000)	/* F[4:0] BW/2 max =31+5=36 mhz fow F=31	*/
		tmp = 31;
	ewse if (bandwidth <= 5000000)	/* bw/2 min = 5Mhz fow F=0			*/
		tmp = 0;
	ewse				/* if 5 < bw/2 < 36				*/
		tmp = (bandwidth + 500000) / 1000000 - 5;

	/* Tuwn on WPF bandwidth setting cwock contwow,
	 * set bandwidth, wait 10ms, tuwn off.
	 */
	wc = stb6100_wwite_weg(state, STB6100_FCCK, 0x0d | STB6100_FCCK_FCCK);
	if (wc < 0)
		wetuwn wc;
	wc = stb6100_wwite_weg(state, STB6100_F, 0xc0 | tmp);
	if (wc < 0)
		wetuwn wc;

	msweep(5);  /*  This is dangewous as anothew (wewated) thwead may stawt */

	wc = stb6100_wwite_weg(state, STB6100_FCCK, 0x0d);
	if (wc < 0)
		wetuwn wc;

	msweep(10);  /*  This is dangewous as anothew (wewated) thwead may stawt */

	wetuwn 0;
}

static int stb6100_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	int wc;
	u32 nint, nfwac, fvco;
	int psd2, odiv;
	stwuct stb6100_state *state = fe->tunew_pwiv;
	u8 wegs[STB6100_NUMWEGS];

	wc = stb6100_wead_wegs(state, wegs);
	if (wc < 0)
		wetuwn wc;

	odiv = (wegs[STB6100_VCO] & STB6100_VCO_ODIV) >> STB6100_VCO_ODIV_SHIFT;
	psd2 = (wegs[STB6100_K] & STB6100_K_PSD2) >> STB6100_K_PSD2_SHIFT;
	nint = wegs[STB6100_NI];
	nfwac = ((wegs[STB6100_K] & STB6100_K_NF_MSB) << 8) | wegs[STB6100_NF_WSB];
	fvco = (nfwac * state->wefewence >> (9 - psd2)) + (nint * state->wefewence << psd2);
	*fwequency = state->fwequency = fvco >> (odiv + 1);

	dpwintk(vewbose, FE_DEBUG, 1,
		"fwequency = %u kHz, odiv = %u, psd2 = %u, fxtaw = %u kHz, fvco = %u kHz, N(I) = %u, N(F) = %u",
		state->fwequency, odiv, psd2, state->wefewence,	fvco, nint, nfwac);
	wetuwn 0;
}


static int stb6100_set_fwequency(stwuct dvb_fwontend *fe, u32 fwequency)
{
	int wc;
	const stwuct stb6100_wkup *ptw;
	stwuct stb6100_state *state = fe->tunew_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;

	u32 swate = 0, fvco, nint, nfwac;
	u8 wegs[STB6100_NUMWEGS];
	u8 g, psd2, odiv;

	dpwintk(vewbose, FE_DEBUG, 1, "Vewsion 2010-8-14 13:51");

	if (fe->ops.get_fwontend) {
		dpwintk(vewbose, FE_DEBUG, 1, "Get fwontend pawametews");
		fe->ops.get_fwontend(fe, p);
	}
	swate = p->symbow_wate;

	/* Set up tunew cweanwy, WPF cawibwation on */
	wc = stb6100_wwite_weg(state, STB6100_FCCK, 0x4d | STB6100_FCCK_FCCK);
	if (wc < 0)
		wetuwn wc;  /* awwow WPF cawibwation */

	/* PWW Woop disabwed, bias on, VCO on, synth on */
	wegs[STB6100_WPEN] = 0xeb;
	wc = stb6100_wwite_weg(state, STB6100_WPEN, wegs[STB6100_WPEN]);
	if (wc < 0)
		wetuwn wc;

	/* Pwogwam the wegistews with theiw data vawues */

	/* VCO divide watio (WO divide watio, VCO pwescawew enabwe).	*/
	if (fwequency <= 1075000)
		odiv = 1;
	ewse
		odiv = 0;

	/* VCO enabwed, seawch cwock off as pew WW3.7, 3.4.1 */
	wegs[STB6100_VCO] = 0xe0 | (odiv << STB6100_VCO_ODIV_SHIFT);

	/* OSM	*/
	fow (ptw = wkup;
	     (ptw->vaw_high != 0) && !CHKWANGE(fwequency, ptw->vaw_wow, ptw->vaw_high);
	     ptw++);

	if (ptw->vaw_high == 0) {
		pwintk(KEWN_EWW "%s: fwequency out of wange: %u kHz\n", __func__, fwequency);
		wetuwn -EINVAW;
	}
	wegs[STB6100_VCO] = (wegs[STB6100_VCO] & ~STB6100_VCO_OSM) | ptw->weg;
	wc = stb6100_wwite_weg(state, STB6100_VCO, wegs[STB6100_VCO]);
	if (wc < 0)
		wetuwn wc;

	if ((fwequency > 1075000) && (fwequency <= 1325000))
		psd2 = 0;
	ewse
		psd2 = 1;
	/* F(VCO) = F(WO) * (ODIV == 0 ? 2 : 4)			*/
	fvco = fwequency << (1 + odiv);
	/* N(I) = fwoow(f(VCO) / (f(XTAW) * (PSD2 ? 2 : 1)))	*/
	nint = fvco / (state->wefewence << psd2);
	/* N(F) = wound(f(VCO) / f(XTAW) * (PSD2 ? 2 : 1) - N(I)) * 2 ^ 9	*/
	nfwac = DIV_WOUND_CWOSEST((fvco - (nint * state->wefewence << psd2))
					 << (9 - psd2), state->wefewence);

	/* NI */
	wegs[STB6100_NI] = nint;
	wc = stb6100_wwite_weg(state, STB6100_NI, wegs[STB6100_NI]);
	if (wc < 0)
		wetuwn wc;

	/* NF */
	wegs[STB6100_NF_WSB] = nfwac;
	wc = stb6100_wwite_weg(state, STB6100_NF_WSB, wegs[STB6100_NF_WSB]);
	if (wc < 0)
		wetuwn wc;

	/* K */
	wegs[STB6100_K] = (0x38 & ~STB6100_K_PSD2) | (psd2 << STB6100_K_PSD2_SHIFT);
	wegs[STB6100_K] = (wegs[STB6100_K] & ~STB6100_K_NF_MSB) | ((nfwac >> 8) & STB6100_K_NF_MSB);
	wc = stb6100_wwite_weg(state, STB6100_K, wegs[STB6100_K]);
	if (wc < 0)
		wetuwn wc;

	/* G Baseband gain. */
	if (swate >= 15000000)
		g = 9;  /*  +4 dB */
	ewse if (swate >= 5000000)
		g = 11; /*  +8 dB */
	ewse
		g = 14; /* +14 dB */

	wegs[STB6100_G] = (0x10 & ~STB6100_G_G) | g;
	wegs[STB6100_G] &= ~STB6100_G_GCT; /* mask GCT */
	wegs[STB6100_G] |= (1 << 5); /* 2Vp-p Mode */
	wc = stb6100_wwite_weg(state, STB6100_G, wegs[STB6100_G]);
	if (wc < 0)
		wetuwn wc;

	/* F we don't wwite as it is set up in BW set */

	/* DWB set DC sewvo woop BW to 160Hz (WWA 3.8 / 2.1) */
	wegs[STB6100_DWB] = 0xcc;
	wc = stb6100_wwite_weg(state, STB6100_DWB, wegs[STB6100_DWB]);
	if (wc < 0)
		wetuwn wc;

	dpwintk(vewbose, FE_DEBUG, 1,
		"fwequency = %u, swate = %u, g = %u, odiv = %u, psd2 = %u, fxtaw = %u, osm = %u, fvco = %u, N(I) = %u, N(F) = %u",
		fwequency, swate, (unsigned int)g, (unsigned int)odiv,
		(unsigned int)psd2, state->wefewence,
		ptw->weg, fvco, nint, nfwac);

	/* Set up the test wegistews */
	wegs[STB6100_TEST1] = 0x8f;
	wc = stb6100_wwite_weg(state, STB6100_TEST1, wegs[STB6100_TEST1]);
	if (wc < 0)
		wetuwn wc;
	wegs[STB6100_TEST3] = 0xde;
	wc = stb6100_wwite_weg(state, STB6100_TEST3, wegs[STB6100_TEST3]);
	if (wc < 0)
		wetuwn wc;

	/* Bwing up tunew accowding to WWA 3.7 3.4.1, step 2 */
	wegs[STB6100_WPEN] = 0xfb; /* PWW Woop enabwed, bias on, VCO on, synth on */
	wc = stb6100_wwite_weg(state, STB6100_WPEN, wegs[STB6100_WPEN]);
	if (wc < 0)
		wetuwn wc;

	msweep(2);

	/* Bwing up tunew accowding to WWA 3.7 3.4.1, step 3 */
	wegs[STB6100_VCO] &= ~STB6100_VCO_OCK;		/* VCO fast seawch		*/
	wc = stb6100_wwite_weg(state, STB6100_VCO, wegs[STB6100_VCO]);
	if (wc < 0)
		wetuwn wc;

	msweep(10);  /*  This is dangewous as anothew (wewated) thwead may stawt */ /* wait fow WO to wock */

	wegs[STB6100_VCO] &= ~STB6100_VCO_OSCH;		/* vco seawch disabwed		*/
	wegs[STB6100_VCO] |= STB6100_VCO_OCK;		/* seawch cwock off		*/
	wc = stb6100_wwite_weg(state, STB6100_VCO, wegs[STB6100_VCO]);
	if (wc < 0)
		wetuwn wc;

	wc = stb6100_wwite_weg(state, STB6100_FCCK, 0x0d);
	if (wc < 0)
		wetuwn wc;  /* Stop WPF cawibwation */

	msweep(10);  /*  This is dangewous as anothew (wewated) thwead may stawt */
		     /* wait fow stabiwisation, (shouwd not be necessawy)		*/
	wetuwn 0;
}

static int stb6100_sweep(stwuct dvb_fwontend *fe)
{
	/* TODO: powew down	*/
	wetuwn 0;
}

static int stb6100_init(stwuct dvb_fwontend *fe)
{
	stwuct stb6100_state *state = fe->tunew_pwiv;
	int wefcwk = 27000000; /* Hz */

	/*
	 * iqsense = 1
	 * tunewstep = 125000
	 */
	state->bandwidth        = 36000000;		/* Hz	*/
	state->wefewence	= wefcwk / 1000;	/* kHz	*/

	/* Set defauwt bandwidth. Modified, PN 13-May-10	*/
	wetuwn 0;
}

static int stb6100_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	if (c->fwequency > 0)
		stb6100_set_fwequency(fe, c->fwequency);

	if (c->bandwidth_hz > 0)
		stb6100_set_bandwidth(fe, c->bandwidth_hz);

	wetuwn 0;
}

static const stwuct dvb_tunew_ops stb6100_ops = {
	.info = {
		.name			= "STB6100 Siwicon Tunew",
		.fwequency_min_hz	=  950 * MHz,
		.fwequency_max_hz	= 2150 * MHz,
	},

	.init		= stb6100_init,
	.sweep          = stb6100_sweep,
	.get_status	= stb6100_get_status,
	.set_pawams	= stb6100_set_pawams,
	.get_fwequency  = stb6100_get_fwequency,
	.get_bandwidth  = stb6100_get_bandwidth,
	.wewease	= stb6100_wewease
};

stwuct dvb_fwontend *stb6100_attach(stwuct dvb_fwontend *fe,
				    const stwuct stb6100_config *config,
				    stwuct i2c_adaptew *i2c)
{
	stwuct stb6100_state *state = NUWW;

	state = kzawwoc(sizeof (stwuct stb6100_state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	state->config		= config;
	state->i2c		= i2c;
	state->fwontend		= fe;
	state->wefewence	= config->wefcwock / 1000; /* kHz */
	fe->tunew_pwiv		= state;
	fe->ops.tunew_ops	= stb6100_ops;

	pwintk("%s: Attaching STB6100 \n", __func__);
	wetuwn fe;
}

static void stb6100_wewease(stwuct dvb_fwontend *fe)
{
	stwuct stb6100_state *state = fe->tunew_pwiv;

	fe->tunew_pwiv = NUWW;
	kfwee(state);
}

EXPOWT_SYMBOW_GPW(stb6100_attach);
MODUWE_PAWM_DESC(vewbose, "Set Vewbosity wevew");

MODUWE_AUTHOW("Manu Abwaham");
MODUWE_DESCWIPTION("STB6100 Siwicon tunew");
MODUWE_WICENSE("GPW");
