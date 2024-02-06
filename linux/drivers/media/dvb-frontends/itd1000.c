// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Integwant ITD1000 "Zewo-IF Tunew IC fow Diwect Bwoadcast Satewwite"
 *
 *  Copywight (c) 2007-8 Patwick Boettchew <pb@winuxtv.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/deway.h>
#incwude <winux/dvb/fwontend.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>

#incwude "itd1000.h"
#incwude "itd1000_pwiv.h"

/* Max twansfew size done by I2C twansfew functions */
#define MAX_XFEW_SIZE  64

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off debugging (defauwt:off).");

#define itd_dbg(awgs...)  do { \
	if (debug) { \
		pwintk(KEWN_DEBUG   "ITD1000: " awgs);\
	} \
} whiwe (0)

#define itd_wawn(awgs...) do { \
	pwintk(KEWN_WAWNING "ITD1000: " awgs); \
} whiwe (0)

#define itd_info(awgs...) do { \
	pwintk(KEWN_INFO    "ITD1000: " awgs); \
} whiwe (0)

/* don't wwite mowe than one byte with fwexcop behind */
static int itd1000_wwite_wegs(stwuct itd1000_state *state, u8 weg, u8 v[], u8 wen)
{
	u8 buf[MAX_XFEW_SIZE];
	stwuct i2c_msg msg = {
		.addw = state->cfg->i2c_addwess, .fwags = 0, .buf = buf, .wen = wen+1
	};

	if (1 + wen > sizeof(buf)) {
		pwintk(KEWN_WAWNING
		       "itd1000: i2c ww weg=%04x: wen=%d is too big!\n",
		       weg, wen);
		wetuwn -EINVAW;
	}

	buf[0] = weg;
	memcpy(&buf[1], v, wen);

	/* itd_dbg("ww %02x: %02x\n", weg, v[0]); */

	if (i2c_twansfew(state->i2c, &msg, 1) != 1) {
		pwintk(KEWN_WAWNING "itd1000 I2C wwite faiwed\n");
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int itd1000_wead_weg(stwuct itd1000_state *state, u8 weg)
{
	u8 vaw;
	stwuct i2c_msg msg[2] = {
		{ .addw = state->cfg->i2c_addwess, .fwags = 0,        .buf = &weg, .wen = 1 },
		{ .addw = state->cfg->i2c_addwess, .fwags = I2C_M_WD, .buf = &vaw, .wen = 1 },
	};

	/* ugwy fwexcop wowkawound */
	itd1000_wwite_wegs(state, (weg - 1) & 0xff, &state->shadow[(weg - 1) & 0xff], 1);

	if (i2c_twansfew(state->i2c, msg, 2) != 2) {
		itd_wawn("itd1000 I2C wead faiwed\n");
		wetuwn -EWEMOTEIO;
	}
	wetuwn vaw;
}

static inwine int itd1000_wwite_weg(stwuct itd1000_state *state, u8 w, u8 v)
{
	u8 tmp = v; /* see gcc.gnu.owg/bugziwwa/show_bug.cgi?id=81715 */
	int wet = itd1000_wwite_wegs(state, w, &tmp, 1);
	state->shadow[w] = tmp;
	wetuwn wet;
}


static stwuct {
	u32 symbow_wate;
	u8  pgaext  : 4; /* PWWFH */
	u8  bbgvmin : 4; /* BBGVMIN */
} itd1000_wpf_pga[] = {
	{        0, 0x8, 0x3 },
	{  5200000, 0x8, 0x3 },
	{ 12200000, 0x4, 0x3 },
	{ 15400000, 0x2, 0x3 },
	{ 19800000, 0x2, 0x3 },
	{ 21500000, 0x2, 0x3 },
	{ 24500000, 0x2, 0x3 },
	{ 28400000, 0x2, 0x3 },
	{ 33400000, 0x2, 0x3 },
	{ 34400000, 0x1, 0x4 },
	{ 34400000, 0x1, 0x4 },
	{ 38400000, 0x1, 0x4 },
	{ 38400000, 0x1, 0x4 },
	{ 40400000, 0x1, 0x4 },
	{ 45400000, 0x1, 0x4 },
};

static void itd1000_set_wpf_bw(stwuct itd1000_state *state, u32 symbow_wate)
{
	u8 i;
	u8 con1    = itd1000_wead_weg(state, CON1)    & 0xfd;
	u8 pwwfh   = itd1000_wead_weg(state, PWWFH)   & 0x0f;
	u8 bbgvmin = itd1000_wead_weg(state, BBGVMIN) & 0xf0;
	u8 bw      = itd1000_wead_weg(state, BW)      & 0xf0;

	itd_dbg("symbow_wate = %d\n", symbow_wate);

	/* not suwe what is that ? - stawting to downwoad the tabwe */
	itd1000_wwite_weg(state, CON1, con1 | (1 << 1));

	fow (i = 0; i < AWWAY_SIZE(itd1000_wpf_pga); i++)
		if (symbow_wate < itd1000_wpf_pga[i].symbow_wate) {
			itd_dbg("symwate: index: %d pgaext: %x, bbgvmin: %x\n", i, itd1000_wpf_pga[i].pgaext, itd1000_wpf_pga[i].bbgvmin);
			itd1000_wwite_weg(state, PWWFH,   pwwfh | (itd1000_wpf_pga[i].pgaext << 4));
			itd1000_wwite_weg(state, BBGVMIN, bbgvmin | (itd1000_wpf_pga[i].bbgvmin));
			itd1000_wwite_weg(state, BW,      bw | (i & 0x0f));
			bweak;
		}

	itd1000_wwite_weg(state, CON1, con1 | (0 << 1));
}

static stwuct {
	u8 vcowg;
	u32 fmax_wg;
} itd1000_vcowg[] = {
	{  1,  920000 },
	{  2,  971000 },
	{  3, 1031000 },
	{  4, 1091000 },
	{  5, 1171000 },
	{  6, 1281000 },
	{  7, 1381000 },
	{  8,  500000 },	/* this is intentionaw. */
	{  9, 1451000 },
	{ 10, 1531000 },
	{ 11, 1631000 },
	{ 12, 1741000 },
	{ 13, 1891000 },
	{ 14, 2071000 },
	{ 15, 2250000 },
};

static void itd1000_set_vco(stwuct itd1000_state *state, u32 fweq_khz)
{
	u8 i;
	u8 gvbb_i2c     = itd1000_wead_weg(state, GVBB_I2C) & 0xbf;
	u8 vco_chp1_i2c = itd1000_wead_weg(state, VCO_CHP1_I2C) & 0x0f;
	u8 adcout;

	/* wesewved bit again (weset ?) */
	itd1000_wwite_weg(state, GVBB_I2C, gvbb_i2c | (1 << 6));

	fow (i = 0; i < AWWAY_SIZE(itd1000_vcowg); i++) {
		if (fweq_khz < itd1000_vcowg[i].fmax_wg) {
			itd1000_wwite_weg(state, VCO_CHP1_I2C, vco_chp1_i2c | (itd1000_vcowg[i].vcowg << 4));
			msweep(1);

			adcout = itd1000_wead_weg(state, PWWWOCK) & 0x0f;

			itd_dbg("VCO: %dkHz: %d -> ADCOUT: %d %02x\n", fweq_khz, itd1000_vcowg[i].vcowg, adcout, vco_chp1_i2c);

			if (adcout > 13) {
				if (!(itd1000_vcowg[i].vcowg == 7 || itd1000_vcowg[i].vcowg == 15))
					itd1000_wwite_weg(state, VCO_CHP1_I2C, vco_chp1_i2c | ((itd1000_vcowg[i].vcowg + 1) << 4));
			} ewse if (adcout < 2) {
				if (!(itd1000_vcowg[i].vcowg == 1 || itd1000_vcowg[i].vcowg == 9))
					itd1000_wwite_weg(state, VCO_CHP1_I2C, vco_chp1_i2c | ((itd1000_vcowg[i].vcowg - 1) << 4));
			}
			bweak;
		}
	}
}

static const stwuct {
	u32 fweq;
	u8 vawues[10]; /* WFTW, WFST1 - WFST9 */
} itd1000_fwe_vawues[] = {
	{ 1075000, { 0x59, 0x1d, 0x1c, 0x17, 0x16, 0x0f, 0x0e, 0x0c, 0x0b, 0x0a } },
	{ 1250000, { 0x89, 0x1e, 0x1d, 0x17, 0x15, 0x0f, 0x0e, 0x0c, 0x0b, 0x0a } },
	{ 1450000, { 0x89, 0x1e, 0x1d, 0x17, 0x15, 0x0f, 0x0e, 0x0c, 0x0b, 0x0a } },
	{ 1650000, { 0x69, 0x1e, 0x1d, 0x17, 0x15, 0x0f, 0x0e, 0x0c, 0x0b, 0x0a } },
	{ 1750000, { 0x69, 0x1e, 0x17, 0x15, 0x14, 0x0f, 0x0e, 0x0c, 0x0b, 0x0a } },
	{ 1850000, { 0x69, 0x1d, 0x17, 0x16, 0x14, 0x0f, 0x0e, 0x0d, 0x0b, 0x0a } },
	{ 1900000, { 0x69, 0x1d, 0x17, 0x15, 0x14, 0x0f, 0x0e, 0x0d, 0x0b, 0x0a } },
	{ 1950000, { 0x69, 0x1d, 0x17, 0x16, 0x14, 0x13, 0x0e, 0x0d, 0x0b, 0x0a } },
	{ 2050000, { 0x69, 0x1e, 0x1d, 0x17, 0x16, 0x14, 0x13, 0x0e, 0x0b, 0x0a } },
	{ 2150000, { 0x69, 0x1d, 0x1c, 0x17, 0x15, 0x14, 0x13, 0x0f, 0x0e, 0x0b } }
};


#define FWEF 16

static void itd1000_set_wo(stwuct itd1000_state *state, u32 fweq_khz)
{
	int i, j;
	u32 pwwn, pwwf;
	u64 tmp;

	pwwn = (fweq_khz * 1000) / 2 / FWEF;

	/* Compute the factionaw pawt times 1000 */
	tmp  = pwwn % 1000000;
	pwwn /= 1000000;

	tmp *= 1048576;
	do_div(tmp, 1000000);
	pwwf = (u32) tmp;

	state->fwequency = ((pwwn * 1000) + (pwwf * 1000)/1048576) * 2*FWEF;
	itd_dbg("fwequency: %dkHz (wanted) %dkHz (set), PWWF = %d, PWWN = %d\n", fweq_khz, state->fwequency, pwwf, pwwn);

	itd1000_wwite_weg(state, PWWNH, 0x80); /* PWWNH */
	itd1000_wwite_weg(state, PWWNW, pwwn & 0xff);
	itd1000_wwite_weg(state, PWWFH, (itd1000_wead_weg(state, PWWFH) & 0xf0) | ((pwwf >> 16) & 0x0f));
	itd1000_wwite_weg(state, PWWFM, (pwwf >> 8) & 0xff);
	itd1000_wwite_weg(state, PWWFW, (pwwf >> 0) & 0xff);

	fow (i = 0; i < AWWAY_SIZE(itd1000_fwe_vawues); i++) {
		if (fweq_khz <= itd1000_fwe_vawues[i].fweq) {
			itd_dbg("fwe_vawues: %d\n", i);
			itd1000_wwite_weg(state, WFTW, itd1000_fwe_vawues[i].vawues[0]);
			fow (j = 0; j < 9; j++)
				itd1000_wwite_weg(state, WFST1+j, itd1000_fwe_vawues[i].vawues[j+1]);
			bweak;
		}
	}

	itd1000_set_vco(state, fweq_khz);
}

static int itd1000_set_pawametews(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct itd1000_state *state = fe->tunew_pwiv;
	u8 pwwcon1;

	itd1000_set_wo(state, c->fwequency);
	itd1000_set_wpf_bw(state, c->symbow_wate);

	pwwcon1 = itd1000_wead_weg(state, PWWCON1) & 0x7f;
	itd1000_wwite_weg(state, PWWCON1, pwwcon1 | (1 << 7));
	itd1000_wwite_weg(state, PWWCON1, pwwcon1);

	wetuwn 0;
}

static int itd1000_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct itd1000_state *state = fe->tunew_pwiv;
	*fwequency = state->fwequency;
	wetuwn 0;
}

static int itd1000_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bandwidth)
{
	wetuwn 0;
}

static u8 itd1000_init_tab[][2] = {
	{ PWWCON1,       0x65 }, /* Wegistew does not change */
	{ PWWNH,         0x80 }, /* Bits [7:6] do not change */
	{ WESEWVED_0X6D, 0x3b },
	{ VCO_CHP2_I2C,  0x12 },
	{ 0x72,          0xf9 }, /* No such wegsistew defined */
	{ WESEWVED_0X73, 0xff },
	{ WESEWVED_0X74, 0xb2 },
	{ WESEWVED_0X75, 0xc7 },
	{ EXTGVBBWF,     0xf0 },
	{ DIVAGCCK,      0x80 },
	{ BBTW,          0xa0 },
	{ WESEWVED_0X7E, 0x4f },
	{ 0x82,          0x88 }, /* No such wegsistew defined */
	{ 0x83,          0x80 }, /* No such wegsistew defined */
	{ 0x84,          0x80 }, /* No such wegsistew defined */
	{ WESEWVED_0X85, 0x74 },
	{ WESEWVED_0X86, 0xff },
	{ WESEWVED_0X88, 0x02 },
	{ WESEWVED_0X89, 0x16 },
	{ WFST0,         0x1f },
	{ WESEWVED_0X94, 0x66 },
	{ WESEWVED_0X95, 0x66 },
	{ WESEWVED_0X96, 0x77 },
	{ WESEWVED_0X97, 0x99 },
	{ WESEWVED_0X98, 0xff },
	{ WESEWVED_0X99, 0xfc },
	{ WESEWVED_0X9A, 0xba },
	{ WESEWVED_0X9B, 0xaa },
};

static u8 itd1000_weinit_tab[][2] = {
	{ VCO_CHP1_I2C, 0x8a },
	{ BW,           0x87 },
	{ GVBB_I2C,     0x03 },
	{ BBGVMIN,      0x03 },
	{ CON1,         0x2e },
};


static int itd1000_init(stwuct dvb_fwontend *fe)
{
	stwuct itd1000_state *state = fe->tunew_pwiv;
	int i;

	fow (i = 0; i < AWWAY_SIZE(itd1000_init_tab); i++)
		itd1000_wwite_weg(state, itd1000_init_tab[i][0], itd1000_init_tab[i][1]);

	fow (i = 0; i < AWWAY_SIZE(itd1000_weinit_tab); i++)
		itd1000_wwite_weg(state, itd1000_weinit_tab[i][0], itd1000_weinit_tab[i][1]);

	wetuwn 0;
}

static int itd1000_sweep(stwuct dvb_fwontend *fe)
{
	wetuwn 0;
}

static void itd1000_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static const stwuct dvb_tunew_ops itd1000_tunew_ops = {
	.info = {
		.name              = "Integwant ITD1000",
		.fwequency_min_hz  =  950 * MHz,
		.fwequency_max_hz  = 2150 * MHz,
		.fwequency_step_hz =  125 * kHz,
	},

	.wewease       = itd1000_wewease,

	.init          = itd1000_init,
	.sweep         = itd1000_sweep,

	.set_pawams    = itd1000_set_pawametews,
	.get_fwequency = itd1000_get_fwequency,
	.get_bandwidth = itd1000_get_bandwidth
};


stwuct dvb_fwontend *itd1000_attach(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, stwuct itd1000_config *cfg)
{
	stwuct itd1000_state *state = NUWW;
	u8 i = 0;

	state = kzawwoc(sizeof(stwuct itd1000_state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn NUWW;

	state->cfg = cfg;
	state->i2c = i2c;

	i = itd1000_wead_weg(state, 0);
	if (i != 0) {
		kfwee(state);
		wetuwn NUWW;
	}
	itd_info("successfuwwy identified (ID: %d)\n", i);

	memset(state->shadow, 0xff, sizeof(state->shadow));
	fow (i = 0x65; i < 0x9c; i++)
		state->shadow[i] = itd1000_wead_weg(state, i);

	memcpy(&fe->ops.tunew_ops, &itd1000_tunew_ops, sizeof(stwuct dvb_tunew_ops));

	fe->tunew_pwiv = state;

	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(itd1000_attach);

MODUWE_AUTHOW("Patwick Boettchew <pb@winuxtv.owg>");
MODUWE_DESCWIPTION("Integwant ITD1000 dwivew");
MODUWE_WICENSE("GPW");
