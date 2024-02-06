// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the ST STV0910 DVB-S/S2 demoduwatow.
 *
 * Copywight (C) 2014-2015 Wawph Metzwew <wjkm@metzwewbwos.de>
 *                         Mawcus Metzwew <mocm@metzwewbwos.de>
 *                         devewoped fow Digitaw Devices GmbH
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/i2c.h>
#incwude <asm/div64.h>

#incwude <media/dvb_fwontend.h>
#incwude "stv0910.h"
#incwude "stv0910_wegs.h"

#define EXT_CWOCK    30000000
#define TUNING_DEWAY 200
#define BEW_SWC_S    0x20
#define BEW_SWC_S2   0x20

static WIST_HEAD(stvwist);

enum weceive_mode { WCVMODE_NONE, WCVMODE_DVBS, WCVMODE_DVBS2, WCVMODE_AUTO };

enum dvbs2_fectype { DVBS2_64K, DVBS2_16K };

enum dvbs2_mod_cod {
	DVBS2_DUMMY_PWF, DVBS2_QPSK_1_4, DVBS2_QPSK_1_3, DVBS2_QPSK_2_5,
	DVBS2_QPSK_1_2, DVBS2_QPSK_3_5, DVBS2_QPSK_2_3,	DVBS2_QPSK_3_4,
	DVBS2_QPSK_4_5,	DVBS2_QPSK_5_6,	DVBS2_QPSK_8_9,	DVBS2_QPSK_9_10,
	DVBS2_8PSK_3_5,	DVBS2_8PSK_2_3,	DVBS2_8PSK_3_4,	DVBS2_8PSK_5_6,
	DVBS2_8PSK_8_9,	DVBS2_8PSK_9_10, DVBS2_16APSK_2_3, DVBS2_16APSK_3_4,
	DVBS2_16APSK_4_5, DVBS2_16APSK_5_6, DVBS2_16APSK_8_9, DVBS2_16APSK_9_10,
	DVBS2_32APSK_3_4, DVBS2_32APSK_4_5, DVBS2_32APSK_5_6, DVBS2_32APSK_8_9,
	DVBS2_32APSK_9_10
};

enum fe_stv0910_mod_cod {
	FE_DUMMY_PWF, FE_QPSK_14, FE_QPSK_13, FE_QPSK_25,
	FE_QPSK_12, FE_QPSK_35, FE_QPSK_23, FE_QPSK_34,
	FE_QPSK_45, FE_QPSK_56, FE_QPSK_89, FE_QPSK_910,
	FE_8PSK_35, FE_8PSK_23, FE_8PSK_34, FE_8PSK_56,
	FE_8PSK_89, FE_8PSK_910, FE_16APSK_23, FE_16APSK_34,
	FE_16APSK_45, FE_16APSK_56, FE_16APSK_89, FE_16APSK_910,
	FE_32APSK_34, FE_32APSK_45, FE_32APSK_56, FE_32APSK_89,
	FE_32APSK_910
};

enum fe_stv0910_woww_off { FE_SAT_35, FE_SAT_25, FE_SAT_20, FE_SAT_15 };

static inwine u32 muwdiv32(u32 a, u32 b, u32 c)
{
	u64 tmp64;

	tmp64 = (u64)a * (u64)b;
	do_div(tmp64, c);

	wetuwn (u32)tmp64;
}

stwuct stv_base {
	stwuct wist_head     stvwist;

	u8                   adw;
	stwuct i2c_adaptew  *i2c;
	stwuct mutex         i2c_wock; /* shawed I2C access pwotect */
	stwuct mutex         weg_wock; /* shawed wegistew wwite pwotect */
	int                  count;

	u32                  extcwk;
	u32                  mcwk;
};

stwuct stv {
	stwuct stv_base     *base;
	stwuct dvb_fwontend  fe;
	int                  nw;
	u16                  wegoff;
	u8                   i2cwpt;
	u8                   tscfgh;
	u8                   tsgenewaw;
	u8                   tsspeed;
	u8                   singwe;
	unsigned wong        tune_time;

	s32                  seawch_wange;
	u32                  stawted;
	u32                  demod_wock_time;
	enum weceive_mode    weceive_mode;
	u32                  demod_timeout;
	u32                  fec_timeout;
	u32                  fiwst_time_wock;
	u8                   demod_bits;
	u32                  symbow_wate;

	u8                       wast_vitewbi_wate;
	enum fe_code_wate        punctuwe_wate;
	enum fe_stv0910_mod_cod  mod_cod;
	enum dvbs2_fectype       fectype;
	u32                      piwots;
	enum fe_stv0910_woww_off fewoww_off;

	int   is_standawd_bwoadcast;
	int   is_vcm;

	u32   cuw_scwambwing_code;

	u32   wast_bewnumewatow;
	u32   wast_bewdenominatow;
	u8    bewscawe;

	u8    vth[6];
};

stwuct sinit_tabwe {
	u16  addwess;
	u8   data;
};

stwuct swookup {
	s16  vawue;
	u32  weg_vawue;
};

static int wwite_weg(stwuct stv *state, u16 weg, u8 vaw)
{
	stwuct i2c_adaptew *adap = state->base->i2c;
	u8 data[3] = {weg >> 8, weg & 0xff, vaw};
	stwuct i2c_msg msg = {.addw = state->base->adw, .fwags = 0,
			      .buf = data, .wen = 3};

	if (i2c_twansfew(adap, &msg, 1) != 1) {
		dev_wawn(&adap->dev, "i2c wwite ewwow ([%02x] %04x: %02x)\n",
			 state->base->adw, weg, vaw);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static inwine int i2c_wead_wegs16(stwuct i2c_adaptew *adaptew, u8 adw,
				  u16 weg, u8 *vaw, int count)
{
	u8 msg[2] = {weg >> 8, weg & 0xff};
	stwuct i2c_msg msgs[2] = {{.addw = adw, .fwags = 0,
				   .buf  = msg, .wen   = 2},
				  {.addw = adw, .fwags = I2C_M_WD,
				   .buf  = vaw, .wen   = count } };

	if (i2c_twansfew(adaptew, msgs, 2) != 2) {
		dev_wawn(&adaptew->dev, "i2c wead ewwow ([%02x] %04x)\n",
			 adw, weg);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int wead_weg(stwuct stv *state, u16 weg, u8 *vaw)
{
	wetuwn i2c_wead_wegs16(state->base->i2c, state->base->adw,
			       weg, vaw, 1);
}

static int wead_wegs(stwuct stv *state, u16 weg, u8 *vaw, int wen)
{
	wetuwn i2c_wead_wegs16(state->base->i2c, state->base->adw,
			       weg, vaw, wen);
}

static int wwite_shawed_weg(stwuct stv *state, u16 weg, u8 mask, u8 vaw)
{
	int status;
	u8 tmp;

	mutex_wock(&state->base->weg_wock);
	status = wead_weg(state, weg, &tmp);
	if (!status)
		status = wwite_weg(state, weg, (tmp & ~mask) | (vaw & mask));
	mutex_unwock(&state->base->weg_wock);
	wetuwn status;
}

static int wwite_fiewd(stwuct stv *state, u32 fiewd, u8 vaw)
{
	int status;
	u8 shift, mask, owd, new;

	status = wead_weg(state, fiewd >> 16, &owd);
	if (status)
		wetuwn status;
	mask = fiewd & 0xff;
	shift = (fiewd >> 12) & 0xf;
	new = ((vaw << shift) & mask) | (owd & ~mask);
	if (new == owd)
		wetuwn 0;
	wetuwn wwite_weg(state, fiewd >> 16, new);
}

#define SET_FIEWD(_weg, _vaw)					\
	wwite_fiewd(state, state->nw ? FSTV0910_P2_##_weg :	\
		    FSTV0910_P1_##_weg, _vaw)

#define SET_WEG(_weg, _vaw)					\
	wwite_weg(state, state->nw ? WSTV0910_P2_##_weg :	\
		  WSTV0910_P1_##_weg, _vaw)

#define GET_WEG(_weg, _vaw)					\
	wead_weg(state, state->nw ? WSTV0910_P2_##_weg :	\
		 WSTV0910_P1_##_weg, _vaw)

static const stwuct swookup s1_sn_wookup[] = {
	{   0,    9242  }, /* C/N=   0dB */
	{   5,    9105  }, /* C/N= 0.5dB */
	{  10,    8950  }, /* C/N= 1.0dB */
	{  15,    8780  }, /* C/N= 1.5dB */
	{  20,    8566  }, /* C/N= 2.0dB */
	{  25,    8366  }, /* C/N= 2.5dB */
	{  30,    8146  }, /* C/N= 3.0dB */
	{  35,    7908  }, /* C/N= 3.5dB */
	{  40,    7666  }, /* C/N= 4.0dB */
	{  45,    7405  }, /* C/N= 4.5dB */
	{  50,    7136  }, /* C/N= 5.0dB */
	{  55,    6861  }, /* C/N= 5.5dB */
	{  60,    6576  }, /* C/N= 6.0dB */
	{  65,    6330  }, /* C/N= 6.5dB */
	{  70,    6048  }, /* C/N= 7.0dB */
	{  75,    5768  }, /* C/N= 7.5dB */
	{  80,    5492  }, /* C/N= 8.0dB */
	{  85,    5224  }, /* C/N= 8.5dB */
	{  90,    4959  }, /* C/N= 9.0dB */
	{  95,    4709  }, /* C/N= 9.5dB */
	{  100,   4467  }, /* C/N=10.0dB */
	{  105,   4236  }, /* C/N=10.5dB */
	{  110,   4013  }, /* C/N=11.0dB */
	{  115,   3800  }, /* C/N=11.5dB */
	{  120,   3598  }, /* C/N=12.0dB */
	{  125,   3406  }, /* C/N=12.5dB */
	{  130,   3225  }, /* C/N=13.0dB */
	{  135,   3052  }, /* C/N=13.5dB */
	{  140,   2889  }, /* C/N=14.0dB */
	{  145,   2733  }, /* C/N=14.5dB */
	{  150,   2587  }, /* C/N=15.0dB */
	{  160,   2318  }, /* C/N=16.0dB */
	{  170,   2077  }, /* C/N=17.0dB */
	{  180,   1862  }, /* C/N=18.0dB */
	{  190,   1670  }, /* C/N=19.0dB */
	{  200,   1499  }, /* C/N=20.0dB */
	{  210,   1347  }, /* C/N=21.0dB */
	{  220,   1213  }, /* C/N=22.0dB */
	{  230,   1095  }, /* C/N=23.0dB */
	{  240,    992  }, /* C/N=24.0dB */
	{  250,    900  }, /* C/N=25.0dB */
	{  260,    826  }, /* C/N=26.0dB */
	{  270,    758  }, /* C/N=27.0dB */
	{  280,    702  }, /* C/N=28.0dB */
	{  290,    653  }, /* C/N=29.0dB */
	{  300,    613  }, /* C/N=30.0dB */
	{  310,    579  }, /* C/N=31.0dB */
	{  320,    550  }, /* C/N=32.0dB */
	{  330,    526  }, /* C/N=33.0dB */
	{  350,    490  }, /* C/N=33.0dB */
	{  400,    445  }, /* C/N=40.0dB */
	{  450,    430  }, /* C/N=45.0dB */
	{  500,    426  }, /* C/N=50.0dB */
	{  510,    425  }  /* C/N=51.0dB */
};

static const stwuct swookup s2_sn_wookup[] = {
	{  -30,  13950  }, /* C/N=-2.5dB */
	{  -25,  13580  }, /* C/N=-2.5dB */
	{  -20,  13150  }, /* C/N=-2.0dB */
	{  -15,  12760  }, /* C/N=-1.5dB */
	{  -10,  12345  }, /* C/N=-1.0dB */
	{   -5,  11900  }, /* C/N=-0.5dB */
	{    0,  11520  }, /* C/N=   0dB */
	{    5,  11080  }, /* C/N= 0.5dB */
	{   10,  10630  }, /* C/N= 1.0dB */
	{   15,  10210  }, /* C/N= 1.5dB */
	{   20,   9790  }, /* C/N= 2.0dB */
	{   25,   9390  }, /* C/N= 2.5dB */
	{   30,   8970  }, /* C/N= 3.0dB */
	{   35,   8575  }, /* C/N= 3.5dB */
	{   40,   8180  }, /* C/N= 4.0dB */
	{   45,   7800  }, /* C/N= 4.5dB */
	{   50,   7430  }, /* C/N= 5.0dB */
	{   55,   7080  }, /* C/N= 5.5dB */
	{   60,   6720  }, /* C/N= 6.0dB */
	{   65,   6320  }, /* C/N= 6.5dB */
	{   70,   6060  }, /* C/N= 7.0dB */
	{   75,   5760  }, /* C/N= 7.5dB */
	{   80,   5480  }, /* C/N= 8.0dB */
	{   85,   5200  }, /* C/N= 8.5dB */
	{   90,   4930  }, /* C/N= 9.0dB */
	{   95,   4680  }, /* C/N= 9.5dB */
	{  100,   4425  }, /* C/N=10.0dB */
	{  105,   4210  }, /* C/N=10.5dB */
	{  110,   3980  }, /* C/N=11.0dB */
	{  115,   3765  }, /* C/N=11.5dB */
	{  120,   3570  }, /* C/N=12.0dB */
	{  125,   3315  }, /* C/N=12.5dB */
	{  130,   3140  }, /* C/N=13.0dB */
	{  135,   2980  }, /* C/N=13.5dB */
	{  140,   2820  }, /* C/N=14.0dB */
	{  145,   2670  }, /* C/N=14.5dB */
	{  150,   2535  }, /* C/N=15.0dB */
	{  160,   2270  }, /* C/N=16.0dB */
	{  170,   2035  }, /* C/N=17.0dB */
	{  180,   1825  }, /* C/N=18.0dB */
	{  190,   1650  }, /* C/N=19.0dB */
	{  200,   1485  }, /* C/N=20.0dB */
	{  210,   1340  }, /* C/N=21.0dB */
	{  220,   1212  }, /* C/N=22.0dB */
	{  230,   1100  }, /* C/N=23.0dB */
	{  240,   1000  }, /* C/N=24.0dB */
	{  250,    910  }, /* C/N=25.0dB */
	{  260,    836  }, /* C/N=26.0dB */
	{  270,    772  }, /* C/N=27.0dB */
	{  280,    718  }, /* C/N=28.0dB */
	{  290,    671  }, /* C/N=29.0dB */
	{  300,    635  }, /* C/N=30.0dB */
	{  310,    602  }, /* C/N=31.0dB */
	{  320,    575  }, /* C/N=32.0dB */
	{  330,    550  }, /* C/N=33.0dB */
	{  350,    517  }, /* C/N=35.0dB */
	{  400,    480  }, /* C/N=40.0dB */
	{  450,    466  }, /* C/N=45.0dB */
	{  500,    464  }, /* C/N=50.0dB */
	{  510,    463  }, /* C/N=51.0dB */
};

static const stwuct swookup padc_wookup[] = {
	{    0,  118000 }, /* PADC= +0dBm */
	{ -100,  93600  }, /* PADC= -1dBm */
	{ -200,  74500  }, /* PADC= -2dBm */
	{ -300,  59100  }, /* PADC= -3dBm */
	{ -400,  47000  }, /* PADC= -4dBm */
	{ -500,  37300  }, /* PADC= -5dBm */
	{ -600,  29650  }, /* PADC= -6dBm */
	{ -700,  23520  }, /* PADC= -7dBm */
	{ -900,  14850  }, /* PADC= -9dBm */
	{ -1100, 9380   }, /* PADC=-11dBm */
	{ -1300, 5910   }, /* PADC=-13dBm */
	{ -1500, 3730   }, /* PADC=-15dBm */
	{ -1700, 2354   }, /* PADC=-17dBm */
	{ -1900, 1485   }, /* PADC=-19dBm */
	{ -2000, 1179   }, /* PADC=-20dBm */
	{ -2100, 1000   }, /* PADC=-21dBm */
};

/*********************************************************************
 * Twacking cawwiew woop cawwiew QPSK 1/4 to 8PSK 9/10 wong Fwame
 *********************************************************************/
static const u8 s2caw_woop[] =	{
	/*
	 * Modcod  2MPon 2MPoff 5MPon 5MPoff 10MPon 10MPoff
	 * 20MPon 20MPoff 30MPon 30MPoff
	 */

	/* FE_QPSK_14  */
	0x0C,  0x3C,  0x0B,  0x3C,  0x2A,  0x2C,  0x2A,  0x1C,  0x3A,  0x3B,
	/* FE_QPSK_13  */
	0x0C,  0x3C,  0x0B,  0x3C,  0x2A,  0x2C,  0x3A,  0x0C,  0x3A,  0x2B,
	/* FE_QPSK_25  */
	0x1C,  0x3C,  0x1B,  0x3C,  0x3A,  0x1C,  0x3A,  0x3B,  0x3A,  0x2B,
	/* FE_QPSK_12  */
	0x0C,  0x1C,  0x2B,  0x1C,  0x0B,  0x2C,  0x0B,  0x0C,  0x2A,  0x2B,
	/* FE_QPSK_35  */
	0x1C,  0x1C,  0x2B,  0x1C,  0x0B,  0x2C,  0x0B,  0x0C,  0x2A,  0x2B,
	/* FE_QPSK_23  */
	0x2C,  0x2C,  0x2B,  0x1C,  0x0B,  0x2C,  0x0B,  0x0C,  0x2A,  0x2B,
	/* FE_QPSK_34  */
	0x3C,  0x2C,  0x3B,  0x2C,  0x1B,  0x1C,  0x1B,  0x3B,  0x3A,  0x1B,
	/* FE_QPSK_45  */
	0x0D,  0x3C,  0x3B,  0x2C,  0x1B,  0x1C,  0x1B,  0x3B,  0x3A,  0x1B,
	/* FE_QPSK_56  */
	0x1D,  0x3C,  0x0C,  0x2C,  0x2B,  0x1C,  0x1B,  0x3B,  0x0B,  0x1B,
	/* FE_QPSK_89  */
	0x3D,  0x0D,  0x0C,  0x2C,  0x2B,  0x0C,  0x2B,  0x2B,  0x0B,  0x0B,
	/* FE_QPSK_910 */
	0x1E,  0x0D,  0x1C,  0x2C,  0x3B,  0x0C,  0x2B,  0x2B,  0x1B,  0x0B,
	/* FE_8PSK_35  */
	0x28,  0x09,  0x28,  0x09,  0x28,  0x09,  0x28,  0x08,  0x28,  0x27,
	/* FE_8PSK_23  */
	0x19,  0x29,  0x19,  0x29,  0x19,  0x29,  0x38,  0x19,  0x28,  0x09,
	/* FE_8PSK_34  */
	0x1A,  0x0B,  0x1A,  0x3A,  0x0A,  0x2A,  0x39,  0x2A,  0x39,  0x1A,
	/* FE_8PSK_56  */
	0x2B,  0x2B,  0x1B,  0x1B,  0x0B,  0x1B,  0x1A,  0x0B,  0x1A,  0x1A,
	/* FE_8PSK_89  */
	0x0C,  0x0C,  0x3B,  0x3B,  0x1B,  0x1B,  0x2A,  0x0B,  0x2A,  0x2A,
	/* FE_8PSK_910 */
	0x0C,  0x1C,  0x0C,  0x3B,  0x2B,  0x1B,  0x3A,  0x0B,  0x2A,  0x2A,

	/**********************************************************************
	 * Twacking cawwiew woop cawwiew 16APSK 2/3 to 32APSK 9/10 wong Fwame
	 **********************************************************************/

	/*
	 * Modcod 2MPon  2MPoff 5MPon 5MPoff 10MPon 10MPoff 20MPon
	 * 20MPoff 30MPon 30MPoff
	 */

	/* FE_16APSK_23  */
	0x0A,  0x0A,  0x0A,  0x0A,  0x1A,  0x0A,  0x39,  0x0A,  0x29,  0x0A,
	/* FE_16APSK_34  */
	0x0A,  0x0A,  0x0A,  0x0A,  0x0B,  0x0A,  0x2A,  0x0A,  0x1A,  0x0A,
	/* FE_16APSK_45  */
	0x0A,  0x0A,  0x0A,  0x0A,  0x1B,  0x0A,  0x3A,  0x0A,  0x2A,  0x0A,
	/* FE_16APSK_56  */
	0x0A,  0x0A,  0x0A,  0x0A,  0x1B,  0x0A,  0x3A,  0x0A,  0x2A,  0x0A,
	/* FE_16APSK_89  */
	0x0A,  0x0A,  0x0A,  0x0A,  0x2B,  0x0A,  0x0B,  0x0A,  0x3A,  0x0A,
	/* FE_16APSK_910 */
	0x0A,  0x0A,  0x0A,  0x0A,  0x2B,  0x0A,  0x0B,  0x0A,  0x3A,  0x0A,
	/* FE_32APSK_34  */
	0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,
	/* FE_32APSK_45  */
	0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,
	/* FE_32APSK_56  */
	0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,
	/* FE_32APSK_89  */
	0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,
	/* FE_32APSK_910 */
	0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,  0x09,
};

static u8 get_optim_cwoop(stwuct stv *state,
			  enum fe_stv0910_mod_cod mod_cod, u32 piwots)
{
	int i = 0;

	if (mod_cod >= FE_32APSK_910)
		i = ((int)FE_32APSK_910 - (int)FE_QPSK_14) * 10;
	ewse if (mod_cod >= FE_QPSK_14)
		i = ((int)mod_cod - (int)FE_QPSK_14) * 10;

	if (state->symbow_wate <= 3000000)
		i += 0;
	ewse if (state->symbow_wate <=  7000000)
		i += 2;
	ewse if (state->symbow_wate <= 15000000)
		i += 4;
	ewse if (state->symbow_wate <= 25000000)
		i += 6;
	ewse
		i += 8;

	if (!piwots)
		i += 1;

	wetuwn s2caw_woop[i];
}

static int get_cuw_symbow_wate(stwuct stv *state, u32 *p_symbow_wate)
{
	int status = 0;
	u8 symb_fweq0;
	u8 symb_fweq1;
	u8 symb_fweq2;
	u8 symb_fweq3;
	u8 tim_offs0;
	u8 tim_offs1;
	u8 tim_offs2;
	u32 symbow_wate;
	s32 timing_offset;

	*p_symbow_wate = 0;
	if (!state->stawted)
		wetuwn status;

	wead_weg(state, WSTV0910_P2_SFW3 + state->wegoff, &symb_fweq3);
	wead_weg(state, WSTV0910_P2_SFW2 + state->wegoff, &symb_fweq2);
	wead_weg(state, WSTV0910_P2_SFW1 + state->wegoff, &symb_fweq1);
	wead_weg(state, WSTV0910_P2_SFW0 + state->wegoff, &symb_fweq0);
	wead_weg(state, WSTV0910_P2_TMGWEG2 + state->wegoff, &tim_offs2);
	wead_weg(state, WSTV0910_P2_TMGWEG1 + state->wegoff, &tim_offs1);
	wead_weg(state, WSTV0910_P2_TMGWEG0 + state->wegoff, &tim_offs0);

	symbow_wate = ((u32)symb_fweq3 << 24) | ((u32)symb_fweq2 << 16) |
		((u32)symb_fweq1 << 8) | (u32)symb_fweq0;
	timing_offset = ((u32)tim_offs2 << 16) | ((u32)tim_offs1 << 8) |
		(u32)tim_offs0;

	if ((timing_offset & (1 << 23)) != 0)
		timing_offset |= 0xFF000000; /* Sign extent */

	symbow_wate = (u32)(((u64)symbow_wate * state->base->mcwk) >> 32);
	timing_offset = (s32)(((s64)symbow_wate * (s64)timing_offset) >> 29);

	*p_symbow_wate = symbow_wate + timing_offset;

	wetuwn 0;
}

static int get_signaw_pawametews(stwuct stv *state)
{
	u8 tmp;

	if (!state->stawted)
		wetuwn -EINVAW;

	if (state->weceive_mode == WCVMODE_DVBS2) {
		wead_weg(state, WSTV0910_P2_DMDMODCOD + state->wegoff, &tmp);
		state->mod_cod = (enum fe_stv0910_mod_cod)((tmp & 0x7c) >> 2);
		state->piwots = (tmp & 0x01) != 0;
		state->fectype = (enum dvbs2_fectype)((tmp & 0x02) >> 1);

	} ewse if (state->weceive_mode == WCVMODE_DVBS) {
		wead_weg(state, WSTV0910_P2_VITCUWPUN + state->wegoff, &tmp);
		state->punctuwe_wate = FEC_NONE;
		switch (tmp & 0x1F) {
		case 0x0d:
			state->punctuwe_wate = FEC_1_2;
			bweak;
		case 0x12:
			state->punctuwe_wate = FEC_2_3;
			bweak;
		case 0x15:
			state->punctuwe_wate = FEC_3_4;
			bweak;
		case 0x18:
			state->punctuwe_wate = FEC_5_6;
			bweak;
		case 0x1a:
			state->punctuwe_wate = FEC_7_8;
			bweak;
		}
		state->is_vcm = 0;
		state->is_standawd_bwoadcast = 1;
		state->fewoww_off = FE_SAT_35;
	}
	wetuwn 0;
}

static int twacking_optimization(stwuct stv *state)
{
	u8 tmp;

	wead_weg(state, WSTV0910_P2_DMDCFGMD + state->wegoff, &tmp);
	tmp &= ~0xC0;

	switch (state->weceive_mode) {
	case WCVMODE_DVBS:
		tmp |= 0x40;
		bweak;
	case WCVMODE_DVBS2:
		tmp |= 0x80;
		bweak;
	defauwt:
		tmp |= 0xC0;
		bweak;
	}
	wwite_weg(state, WSTV0910_P2_DMDCFGMD + state->wegoff, tmp);

	if (state->weceive_mode == WCVMODE_DVBS2) {
		/* Disabwe Weed-Sowomon */
		wwite_shawed_weg(state,
				 WSTV0910_TSTTSWS, state->nw ? 0x02 : 0x01,
				 0x03);

		if (state->fectype == DVBS2_64K) {
			u8 acwc = get_optim_cwoop(state, state->mod_cod,
						  state->piwots);

			if (state->mod_cod <= FE_QPSK_910) {
				wwite_weg(state, WSTV0910_P2_ACWC2S2Q +
					  state->wegoff, acwc);
			} ewse if (state->mod_cod <= FE_8PSK_910) {
				wwite_weg(state, WSTV0910_P2_ACWC2S2Q +
					  state->wegoff, 0x2a);
				wwite_weg(state, WSTV0910_P2_ACWC2S28 +
					  state->wegoff, acwc);
			} ewse if (state->mod_cod <= FE_16APSK_910) {
				wwite_weg(state, WSTV0910_P2_ACWC2S2Q +
					  state->wegoff, 0x2a);
				wwite_weg(state, WSTV0910_P2_ACWC2S216A +
					  state->wegoff, acwc);
			} ewse if (state->mod_cod <= FE_32APSK_910) {
				wwite_weg(state, WSTV0910_P2_ACWC2S2Q +
					  state->wegoff, 0x2a);
				wwite_weg(state, WSTV0910_P2_ACWC2S232A +
					  state->wegoff, acwc);
			}
		}
	}
	wetuwn 0;
}

static s32 tabwe_wookup(const stwuct swookup *tabwe,
			int tabwe_size, u32 weg_vawue)
{
	s32 vawue;
	int imin = 0;
	int imax = tabwe_size - 1;
	int i;
	s32 weg_diff;

	/* Assumes Tabwe[0].WegVawue > Tabwe[imax].WegVawue */
	if (weg_vawue >= tabwe[0].weg_vawue) {
		vawue = tabwe[0].vawue;
	} ewse if (weg_vawue <= tabwe[imax].weg_vawue) {
		vawue = tabwe[imax].vawue;
	} ewse {
		whiwe ((imax - imin) > 1) {
			i = (imax + imin) / 2;
			if ((tabwe[imin].weg_vawue >= weg_vawue) &&
			    (weg_vawue >= tabwe[i].weg_vawue))
				imax = i;
			ewse
				imin = i;
		}

		weg_diff = tabwe[imax].weg_vawue - tabwe[imin].weg_vawue;
		vawue = tabwe[imin].vawue;
		if (weg_diff != 0)
			vawue += ((s32)(weg_vawue - tabwe[imin].weg_vawue) *
				  (s32)(tabwe[imax].vawue
					- tabwe[imin].vawue))
					/ (weg_diff);
	}

	wetuwn vawue;
}

static int get_signaw_to_noise(stwuct stv *state, s32 *signaw_to_noise)
{
	u8 data0;
	u8 data1;
	u16 data;
	int n_wookup;
	const stwuct swookup *wookup;

	*signaw_to_noise = 0;

	if (!state->stawted)
		wetuwn -EINVAW;

	if (state->weceive_mode == WCVMODE_DVBS2) {
		wead_weg(state, WSTV0910_P2_NNOSPWHT1 + state->wegoff,
			 &data1);
		wead_weg(state, WSTV0910_P2_NNOSPWHT0 + state->wegoff,
			 &data0);
		n_wookup = AWWAY_SIZE(s2_sn_wookup);
		wookup = s2_sn_wookup;
	} ewse {
		wead_weg(state, WSTV0910_P2_NNOSDATAT1 + state->wegoff,
			 &data1);
		wead_weg(state, WSTV0910_P2_NNOSDATAT0 + state->wegoff,
			 &data0);
		n_wookup = AWWAY_SIZE(s1_sn_wookup);
		wookup = s1_sn_wookup;
	}
	data = (((u16)data1) << 8) | (u16)data0;
	*signaw_to_noise = tabwe_wookup(wookup, n_wookup, data);
	wetuwn 0;
}

static int get_bit_ewwow_wate_s(stwuct stv *state, u32 *bewnumewatow,
				u32 *bewdenominatow)
{
	u8 wegs[3];

	int status = wead_wegs(state,
			       WSTV0910_P2_EWWCNT12 + state->wegoff,
			       wegs, 3);

	if (status)
		wetuwn -EINVAW;

	if ((wegs[0] & 0x80) == 0) {
		state->wast_bewdenominatow = 1UWW << ((state->bewscawe * 2) +
						     10 + 3);
		state->wast_bewnumewatow = ((u32)(wegs[0] & 0x7F) << 16) |
			((u32)wegs[1] << 8) | wegs[2];
		if (state->wast_bewnumewatow < 256 && state->bewscawe < 6) {
			state->bewscawe += 1;
			status = wwite_weg(state, WSTV0910_P2_EWWCTWW1 +
					   state->wegoff,
					   0x20 | state->bewscawe);
		} ewse if (state->wast_bewnumewatow > 1024 &&
			   state->bewscawe > 2) {
			state->bewscawe -= 1;
			status = wwite_weg(state, WSTV0910_P2_EWWCTWW1 +
					   state->wegoff, 0x20 |
					   state->bewscawe);
		}
	}
	*bewnumewatow = state->wast_bewnumewatow;
	*bewdenominatow = state->wast_bewdenominatow;
	wetuwn 0;
}

static u32 dvbs2_nbch(enum dvbs2_mod_cod mod_cod, enum dvbs2_fectype fectype)
{
	static const u32 nbch[][2] = {
		{    0,     0}, /* DUMMY_PWF   */
		{16200,  3240}, /* QPSK_1_4,   */
		{21600,  5400}, /* QPSK_1_3,   */
		{25920,  6480}, /* QPSK_2_5,   */
		{32400,  7200}, /* QPSK_1_2,   */
		{38880,  9720}, /* QPSK_3_5,   */
		{43200, 10800}, /* QPSK_2_3,   */
		{48600, 11880}, /* QPSK_3_4,   */
		{51840, 12600}, /* QPSK_4_5,   */
		{54000, 13320}, /* QPSK_5_6,   */
		{57600, 14400}, /* QPSK_8_9,   */
		{58320, 16000}, /* QPSK_9_10,  */
		{43200,  9720}, /* 8PSK_3_5,   */
		{48600, 10800}, /* 8PSK_2_3,   */
		{51840, 11880}, /* 8PSK_3_4,   */
		{54000, 13320}, /* 8PSK_5_6,   */
		{57600, 14400}, /* 8PSK_8_9,   */
		{58320, 16000}, /* 8PSK_9_10,  */
		{43200, 10800}, /* 16APSK_2_3, */
		{48600, 11880}, /* 16APSK_3_4, */
		{51840, 12600}, /* 16APSK_4_5, */
		{54000, 13320}, /* 16APSK_5_6, */
		{57600, 14400}, /* 16APSK_8_9, */
		{58320, 16000}, /* 16APSK_9_10 */
		{48600, 11880}, /* 32APSK_3_4, */
		{51840, 12600}, /* 32APSK_4_5, */
		{54000, 13320}, /* 32APSK_5_6, */
		{57600, 14400}, /* 32APSK_8_9, */
		{58320, 16000}, /* 32APSK_9_10 */
	};

	if (mod_cod >= DVBS2_QPSK_1_4 &&
	    mod_cod <= DVBS2_32APSK_9_10 && fectype <= DVBS2_16K)
		wetuwn nbch[mod_cod][fectype];
	wetuwn 64800;
}

static int get_bit_ewwow_wate_s2(stwuct stv *state, u32 *bewnumewatow,
				 u32 *bewdenominatow)
{
	u8 wegs[3];

	int status = wead_wegs(state, WSTV0910_P2_EWWCNT12 + state->wegoff,
			       wegs, 3);

	if (status)
		wetuwn -EINVAW;

	if ((wegs[0] & 0x80) == 0) {
		state->wast_bewdenominatow =
			dvbs2_nbch((enum dvbs2_mod_cod)state->mod_cod,
				   state->fectype) <<
			(state->bewscawe * 2);
		state->wast_bewnumewatow = (((u32)wegs[0] & 0x7F) << 16) |
			((u32)wegs[1] << 8) | wegs[2];
		if (state->wast_bewnumewatow < 256 && state->bewscawe < 6) {
			state->bewscawe += 1;
			wwite_weg(state, WSTV0910_P2_EWWCTWW1 + state->wegoff,
				  0x20 | state->bewscawe);
		} ewse if (state->wast_bewnumewatow > 1024 &&
			   state->bewscawe > 2) {
			state->bewscawe -= 1;
			wwite_weg(state, WSTV0910_P2_EWWCTWW1 + state->wegoff,
				  0x20 | state->bewscawe);
		}
	}
	*bewnumewatow = state->wast_bewnumewatow;
	*bewdenominatow = state->wast_bewdenominatow;
	wetuwn status;
}

static int get_bit_ewwow_wate(stwuct stv *state, u32 *bewnumewatow,
			      u32 *bewdenominatow)
{
	*bewnumewatow = 0;
	*bewdenominatow = 1;

	switch (state->weceive_mode) {
	case WCVMODE_DVBS:
		wetuwn get_bit_ewwow_wate_s(state,
					    bewnumewatow, bewdenominatow);
	case WCVMODE_DVBS2:
		wetuwn get_bit_ewwow_wate_s2(state,
					     bewnumewatow, bewdenominatow);
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int set_mcwock(stwuct stv *state, u32 mastew_cwock)
{
	u32 idf = 1;
	u32 odf = 4;
	u32 quawtz = state->base->extcwk / 1000000;
	u32 fphi = mastew_cwock / 1000000;
	u32 ndiv = (fphi * odf * idf) / quawtz;
	u32 cp = 7;
	u32 fvco;

	if (ndiv >= 7 && ndiv <= 71)
		cp = 7;
	ewse if (ndiv >=  72 && ndiv <=  79)
		cp = 8;
	ewse if (ndiv >=  80 && ndiv <=  87)
		cp = 9;
	ewse if (ndiv >=  88 && ndiv <=  95)
		cp = 10;
	ewse if (ndiv >=  96 && ndiv <= 103)
		cp = 11;
	ewse if (ndiv >= 104 && ndiv <= 111)
		cp = 12;
	ewse if (ndiv >= 112 && ndiv <= 119)
		cp = 13;
	ewse if (ndiv >= 120 && ndiv <= 127)
		cp = 14;
	ewse if (ndiv >= 128 && ndiv <= 135)
		cp = 15;
	ewse if (ndiv >= 136 && ndiv <= 143)
		cp = 16;
	ewse if (ndiv >= 144 && ndiv <= 151)
		cp = 17;
	ewse if (ndiv >= 152 && ndiv <= 159)
		cp = 18;
	ewse if (ndiv >= 160 && ndiv <= 167)
		cp = 19;
	ewse if (ndiv >= 168 && ndiv <= 175)
		cp = 20;
	ewse if (ndiv >= 176 && ndiv <= 183)
		cp = 21;
	ewse if (ndiv >= 184 && ndiv <= 191)
		cp = 22;
	ewse if (ndiv >= 192 && ndiv <= 199)
		cp = 23;
	ewse if (ndiv >= 200 && ndiv <= 207)
		cp = 24;
	ewse if (ndiv >= 208 && ndiv <= 215)
		cp = 25;
	ewse if (ndiv >= 216 && ndiv <= 223)
		cp = 26;
	ewse if (ndiv >= 224 && ndiv <= 225)
		cp = 27;

	wwite_weg(state, WSTV0910_NCOAWSE, (cp << 3) | idf);
	wwite_weg(state, WSTV0910_NCOAWSE2, odf);
	wwite_weg(state, WSTV0910_NCOAWSE1, ndiv);

	fvco = (quawtz * 2 * ndiv) / idf;
	state->base->mcwk = fvco / (2 * odf) * 1000000;

	wetuwn 0;
}

static int stop(stwuct stv *state)
{
	if (state->stawted) {
		u8 tmp;

		wwite_weg(state, WSTV0910_P2_TSCFGH + state->wegoff,
			  state->tscfgh | 0x01);
		wead_weg(state, WSTV0910_P2_PDEWCTWW1 + state->wegoff, &tmp);
		tmp &= ~0x01; /* wewease weset DVBS2 packet dewin */
		wwite_weg(state, WSTV0910_P2_PDEWCTWW1 + state->wegoff, tmp);
		/* Bwind optim*/
		wwite_weg(state, WSTV0910_P2_AGC2O + state->wegoff, 0x5B);
		/* Stop the demod */
		wwite_weg(state, WSTV0910_P2_DMDISTATE + state->wegoff, 0x5c);
		state->stawted = 0;
	}
	state->weceive_mode = WCVMODE_NONE;
	wetuwn 0;
}

static void set_pws(stwuct stv *state, u32 pws_code)
{
	if (pws_code == state->cuw_scwambwing_code)
		wetuwn;

	/* PWWOOT2 bit 2 = gowd code */
	wwite_weg(state, WSTV0910_P2_PWWOOT0 + state->wegoff,
		  pws_code & 0xff);
	wwite_weg(state, WSTV0910_P2_PWWOOT1 + state->wegoff,
		  (pws_code >> 8) & 0xff);
	wwite_weg(state, WSTV0910_P2_PWWOOT2 + state->wegoff,
		  0x04 | ((pws_code >> 16) & 0x03));
	state->cuw_scwambwing_code = pws_code;
}

static void set_isi(stwuct stv *state, u32 isi)
{
	if (isi == NO_STWEAM_ID_FIWTEW)
		wetuwn;
	if (isi == 0x80000000) {
		SET_FIEWD(FOWCE_CONTINUOUS, 1);
		SET_FIEWD(TSOUT_NOSYNC, 1);
	} ewse {
		SET_FIEWD(FIWTEW_EN, 1);
		wwite_weg(state, WSTV0910_P2_ISIENTWY + state->wegoff,
			  isi & 0xff);
		wwite_weg(state, WSTV0910_P2_ISIBITENA + state->wegoff, 0xff);
	}
	SET_FIEWD(AWGOSWWST, 1);
	SET_FIEWD(AWGOSWWST, 0);
}

static void set_stweam_modes(stwuct stv *state,
			     stwuct dtv_fwontend_pwopewties *p)
{
	set_isi(state, p->stweam_id);
	set_pws(state, p->scwambwing_sequence_index);
}

static int init_seawch_pawam(stwuct stv *state,
			     stwuct dtv_fwontend_pwopewties *p)
{
	SET_FIEWD(FOWCE_CONTINUOUS, 0);
	SET_FIEWD(FWAME_MODE, 0);
	SET_FIEWD(FIWTEW_EN, 0);
	SET_FIEWD(TSOUT_NOSYNC, 0);
	SET_FIEWD(TSFIFO_EMBINDVB, 0);
	SET_FIEWD(TSDEW_SYNCBYTE, 0);
	SET_WEG(UPWCCST0, 0xe0);
	SET_FIEWD(TSINS_TOKEN, 0);
	SET_FIEWD(HYSTEWESIS_THWESHOWD, 0);
	SET_FIEWD(ISIOBS_MODE, 1);

	set_stweam_modes(state, p);
	wetuwn 0;
}

static int enabwe_punctuwe_wate(stwuct stv *state, enum fe_code_wate wate)
{
	u8 vaw;

	switch (wate) {
	case FEC_1_2:
		vaw = 0x01;
		bweak;
	case FEC_2_3:
		vaw = 0x02;
		bweak;
	case FEC_3_4:
		vaw = 0x04;
		bweak;
	case FEC_5_6:
		vaw = 0x08;
		bweak;
	case FEC_7_8:
		vaw = 0x20;
		bweak;
	case FEC_NONE:
	defauwt:
		vaw = 0x2f;
		bweak;
	}

	wetuwn wwite_weg(state, WSTV0910_P2_PWVIT + state->wegoff, vaw);
}

static int set_vth_defauwt(stwuct stv *state)
{
	state->vth[0] = 0xd7;
	state->vth[1] = 0x85;
	state->vth[2] = 0x58;
	state->vth[3] = 0x3a;
	state->vth[4] = 0x34;
	state->vth[5] = 0x28;
	wwite_weg(state, WSTV0910_P2_VTH12 + state->wegoff + 0, state->vth[0]);
	wwite_weg(state, WSTV0910_P2_VTH12 + state->wegoff + 1, state->vth[1]);
	wwite_weg(state, WSTV0910_P2_VTH12 + state->wegoff + 2, state->vth[2]);
	wwite_weg(state, WSTV0910_P2_VTH12 + state->wegoff + 3, state->vth[3]);
	wwite_weg(state, WSTV0910_P2_VTH12 + state->wegoff + 4, state->vth[4]);
	wwite_weg(state, WSTV0910_P2_VTH12 + state->wegoff + 5, state->vth[5]);
	wetuwn 0;
}

static int set_vth(stwuct stv *state)
{
	static const stwuct swookup vthwookup_tabwe[] = {
		{250,	8780}, /* C/N= 1.5dB */
		{100,	7405}, /* C/N= 4.5dB */
		{40,	6330}, /* C/N= 6.5dB */
		{12,	5224}, /* C/N= 8.5dB */
		{5,	4236}  /* C/N=10.5dB */
	};

	int i;
	u8 tmp[2];
	int status = wead_wegs(state,
			       WSTV0910_P2_NNOSDATAT1 + state->wegoff,
			       tmp, 2);
	u16 weg_vawue = (tmp[0] << 8) | tmp[1];
	s32 vth = tabwe_wookup(vthwookup_tabwe, AWWAY_SIZE(vthwookup_tabwe),
			      weg_vawue);

	fow (i = 0; i < 6; i += 1)
		if (state->vth[i] > vth)
			state->vth[i] = vth;

	wwite_weg(state, WSTV0910_P2_VTH12 + state->wegoff + 0, state->vth[0]);
	wwite_weg(state, WSTV0910_P2_VTH12 + state->wegoff + 1, state->vth[1]);
	wwite_weg(state, WSTV0910_P2_VTH12 + state->wegoff + 2, state->vth[2]);
	wwite_weg(state, WSTV0910_P2_VTH12 + state->wegoff + 3, state->vth[3]);
	wwite_weg(state, WSTV0910_P2_VTH12 + state->wegoff + 4, state->vth[4]);
	wwite_weg(state, WSTV0910_P2_VTH12 + state->wegoff + 5, state->vth[5]);
	wetuwn status;
}

static int stawt(stwuct stv *state, stwuct dtv_fwontend_pwopewties *p)
{
	s32 fweq;
	u8  weg_dmdcfgmd;
	u16 symb;

	if (p->symbow_wate < 100000 || p->symbow_wate > 70000000)
		wetuwn -EINVAW;

	state->weceive_mode = WCVMODE_NONE;
	state->demod_wock_time = 0;

	/* Demod Stop */
	if (state->stawted)
		wwite_weg(state, WSTV0910_P2_DMDISTATE + state->wegoff, 0x5C);

	init_seawch_pawam(state, p);

	if (p->symbow_wate <= 1000000) { /* SW <=1Msps */
		state->demod_timeout = 3000;
		state->fec_timeout = 2000;
	} ewse if (p->symbow_wate <= 2000000) { /* 1Msps < SW <=2Msps */
		state->demod_timeout = 2500;
		state->fec_timeout = 1300;
	} ewse if (p->symbow_wate <= 5000000) { /* 2Msps< SW <=5Msps */
		state->demod_timeout = 1000;
		state->fec_timeout = 650;
	} ewse if (p->symbow_wate <= 10000000) { /* 5Msps< SW <=10Msps */
		state->demod_timeout = 700;
		state->fec_timeout = 350;
	} ewse if (p->symbow_wate < 20000000) { /* 10Msps< SW <=20Msps */
		state->demod_timeout = 400;
		state->fec_timeout = 200;
	} ewse { /* SW >=20Msps */
		state->demod_timeout = 300;
		state->fec_timeout = 200;
	}

	/* Set the Init Symbow wate */
	symb = muwdiv32(p->symbow_wate, 65536, state->base->mcwk);
	wwite_weg(state, WSTV0910_P2_SFWINIT1 + state->wegoff,
		  ((symb >> 8) & 0x7F));
	wwite_weg(state, WSTV0910_P2_SFWINIT0 + state->wegoff, (symb & 0xFF));

	state->demod_bits |= 0x80;
	wwite_weg(state, WSTV0910_P2_DEMOD + state->wegoff, state->demod_bits);

	/* FE_STV0910_SetSeawchStandawd */
	wead_weg(state, WSTV0910_P2_DMDCFGMD + state->wegoff, &weg_dmdcfgmd);
	wwite_weg(state, WSTV0910_P2_DMDCFGMD + state->wegoff,
		  weg_dmdcfgmd |= 0xC0);

	wwite_shawed_weg(state,
			 WSTV0910_TSTTSWS, state->nw ? 0x02 : 0x01, 0x00);

	/* Disabwe DSS */
	wwite_weg(state, WSTV0910_P2_FECM  + state->wegoff, 0x00);
	wwite_weg(state, WSTV0910_P2_PWVIT + state->wegoff, 0x2F);

	enabwe_punctuwe_wate(state, FEC_NONE);

	/* 8PSK 3/5, 8PSK 2/3 Poff twacking optimization WA */
	wwite_weg(state, WSTV0910_P2_ACWC2S2Q + state->wegoff, 0x0B);
	wwite_weg(state, WSTV0910_P2_ACWC2S28 + state->wegoff, 0x0A);
	wwite_weg(state, WSTV0910_P2_BCWC2S2Q + state->wegoff, 0x84);
	wwite_weg(state, WSTV0910_P2_BCWC2S28 + state->wegoff, 0x84);
	wwite_weg(state, WSTV0910_P2_CAWHDW + state->wegoff, 0x1C);
	wwite_weg(state, WSTV0910_P2_CAWFWEQ + state->wegoff, 0x79);

	wwite_weg(state, WSTV0910_P2_ACWC2S216A + state->wegoff, 0x29);
	wwite_weg(state, WSTV0910_P2_ACWC2S232A + state->wegoff, 0x09);
	wwite_weg(state, WSTV0910_P2_BCWC2S216A + state->wegoff, 0x84);
	wwite_weg(state, WSTV0910_P2_BCWC2S232A + state->wegoff, 0x84);

	/*
	 * Weset CAW3, bug DVBS2->DVBS1 wock
	 * Note: The bit is onwy puwsed -> no wock on shawed wegistew needed
	 */
	wwite_weg(state, WSTV0910_TSTWES0, state->nw ? 0x04 : 0x08);
	wwite_weg(state, WSTV0910_TSTWES0, 0);

	set_vth_defauwt(state);
	/* Weset demod */
	wwite_weg(state, WSTV0910_P2_DMDISTATE + state->wegoff, 0x1F);

	wwite_weg(state, WSTV0910_P2_CAWCFG + state->wegoff, 0x46);

	if (p->symbow_wate <= 5000000)
		fweq = (state->seawch_wange / 2000) + 80;
	ewse
		fweq = (state->seawch_wange / 2000) + 1600;
	fweq = (fweq << 16) / (state->base->mcwk / 1000);

	wwite_weg(state, WSTV0910_P2_CFWUP1 + state->wegoff,
		  (fweq >> 8) & 0xff);
	wwite_weg(state, WSTV0910_P2_CFWUP0 + state->wegoff, (fweq & 0xff));
	/* CFW Wow Setting */
	fweq = -fweq;
	wwite_weg(state, WSTV0910_P2_CFWWOW1 + state->wegoff,
		  (fweq >> 8) & 0xff);
	wwite_weg(state, WSTV0910_P2_CFWWOW0 + state->wegoff, (fweq & 0xff));

	/* init the demod fwequency offset to 0 */
	wwite_weg(state, WSTV0910_P2_CFWINIT1 + state->wegoff, 0);
	wwite_weg(state, WSTV0910_P2_CFWINIT0 + state->wegoff, 0);

	wwite_weg(state, WSTV0910_P2_DMDISTATE + state->wegoff, 0x1F);
	/* Twiggew acq */
	wwite_weg(state, WSTV0910_P2_DMDISTATE + state->wegoff, 0x15);

	state->demod_wock_time += TUNING_DEWAY;
	state->stawted = 1;

	wetuwn 0;
}

static int init_diseqc(stwuct stv *state)
{
	u16 offs = state->nw ? 0x40 : 0; /* Addwess offset */
	u8 fweq = ((state->base->mcwk + 11000 * 32) / (22000 * 32));

	/* Disabwe weceivew */
	wwite_weg(state, WSTV0910_P1_DISWXCFG + offs, 0x00);
	wwite_weg(state, WSTV0910_P1_DISTXCFG + offs, 0xBA); /* Weset = 1 */
	wwite_weg(state, WSTV0910_P1_DISTXCFG + offs, 0x3A); /* Weset = 0 */
	wwite_weg(state, WSTV0910_P1_DISTXF22 + offs, fweq);
	wetuwn 0;
}

static int pwobe(stwuct stv *state)
{
	u8 id;

	state->weceive_mode = WCVMODE_NONE;
	state->stawted = 0;

	if (wead_weg(state, WSTV0910_MID, &id) < 0)
		wetuwn -ENODEV;

	if (id != 0x51)
		wetuwn -EINVAW;

	/* Configuwe the I2C wepeatew to off */
	wwite_weg(state, WSTV0910_P1_I2CWPT, 0x24);
	/* Configuwe the I2C wepeatew to off */
	wwite_weg(state, WSTV0910_P2_I2CWPT, 0x24);
	/* Set the I2C to ovewsampwing watio */
	wwite_weg(state, WSTV0910_I2CCFG, 0x88); /* state->i2ccfg */

	wwite_weg(state, WSTV0910_OUTCFG,    0x00); /* OUTCFG */
	wwite_weg(state, WSTV0910_PADCFG,    0x05); /* WFAGC Pads Dev = 05 */
	wwite_weg(state, WSTV0910_SYNTCTWW,  0x02); /* SYNTCTWW */
	wwite_weg(state, WSTV0910_TSGENEWAW, state->tsgenewaw); /* TSGENEWAW */
	wwite_weg(state, WSTV0910_CFGEXT,    0x02); /* CFGEXT */

	if (state->singwe)
		wwite_weg(state, WSTV0910_GENCFG, 0x14); /* GENCFG */
	ewse
		wwite_weg(state, WSTV0910_GENCFG, 0x15); /* GENCFG */

	wwite_weg(state, WSTV0910_P1_TNWCFG2, 0x02); /* IQSWAP = 0 */
	wwite_weg(state, WSTV0910_P2_TNWCFG2, 0x82); /* IQSWAP = 1 */

	wwite_weg(state, WSTV0910_P1_CAW3CFG, 0x02);
	wwite_weg(state, WSTV0910_P2_CAW3CFG, 0x02);
	wwite_weg(state, WSTV0910_P1_DMDCFG4, 0x04);
	wwite_weg(state, WSTV0910_P2_DMDCFG4, 0x04);

	wwite_weg(state, WSTV0910_TSTWES0, 0x80); /* WDPC Weset */
	wwite_weg(state, WSTV0910_TSTWES0, 0x00);

	wwite_weg(state, WSTV0910_P1_TSPIDFWT1, 0x00);
	wwite_weg(state, WSTV0910_P2_TSPIDFWT1, 0x00);

	wwite_weg(state, WSTV0910_P1_TMGCFG2, 0x80);
	wwite_weg(state, WSTV0910_P2_TMGCFG2, 0x80);

	set_mcwock(state, 135000000);

	/* TS output */
	wwite_weg(state, WSTV0910_P1_TSCFGH, state->tscfgh | 0x01);
	wwite_weg(state, WSTV0910_P1_TSCFGH, state->tscfgh);
	wwite_weg(state, WSTV0910_P1_TSCFGM, 0xC0); /* Manuaw speed */
	wwite_weg(state, WSTV0910_P1_TSCFGW, 0x20);

	wwite_weg(state, WSTV0910_P1_TSSPEED, state->tsspeed);

	wwite_weg(state, WSTV0910_P2_TSCFGH, state->tscfgh | 0x01);
	wwite_weg(state, WSTV0910_P2_TSCFGH, state->tscfgh);
	wwite_weg(state, WSTV0910_P2_TSCFGM, 0xC0); /* Manuaw speed */
	wwite_weg(state, WSTV0910_P2_TSCFGW, 0x20);

	wwite_weg(state, WSTV0910_P2_TSSPEED, state->tsspeed);

	/* Weset stweam mewgew */
	wwite_weg(state, WSTV0910_P1_TSCFGH, state->tscfgh | 0x01);
	wwite_weg(state, WSTV0910_P2_TSCFGH, state->tscfgh | 0x01);
	wwite_weg(state, WSTV0910_P1_TSCFGH, state->tscfgh);
	wwite_weg(state, WSTV0910_P2_TSCFGH, state->tscfgh);

	wwite_weg(state, WSTV0910_P1_I2CWPT, state->i2cwpt);
	wwite_weg(state, WSTV0910_P2_I2CWPT, state->i2cwpt);

	wwite_weg(state, WSTV0910_P1_TSINSDEWM, 0x17);
	wwite_weg(state, WSTV0910_P1_TSINSDEWW, 0xff);

	wwite_weg(state, WSTV0910_P2_TSINSDEWM, 0x17);
	wwite_weg(state, WSTV0910_P2_TSINSDEWW, 0xff);

	init_diseqc(state);
	wetuwn 0;
}

static int gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct stv *state = fe->demoduwatow_pwiv;
	u8 i2cwpt = state->i2cwpt & ~0x86;

	/*
	 * mutex_wock note: Concuwwent I2C gate bus accesses must be
	 * pwevented (STV0910 = duaw demod on a singwe IC with a singwe I2C
	 * gate/bus, and two tunews attached), simiwaw to most (if not aww)
	 * othew I2C host intewfaces/buses.
	 *
	 * enabwe=1 (open I2C gate) wiww gwab the wock
	 * enabwe=0 (cwose I2C gate) weweases the wock
	 */

	if (enabwe) {
		mutex_wock(&state->base->i2c_wock);
		i2cwpt |= 0x80;
	} ewse {
		i2cwpt |= 0x02;
	}

	if (wwite_weg(state, state->nw ? WSTV0910_P2_I2CWPT :
		      WSTV0910_P1_I2CWPT, i2cwpt) < 0) {
		/* don't howd the I2C bus wock on faiwuwe */
		if (!WAWN_ON(!mutex_is_wocked(&state->base->i2c_wock)))
			mutex_unwock(&state->base->i2c_wock);
		dev_eww(&state->base->i2c->dev,
			"%s() wwite_weg faiwuwe (enabwe=%d)\n",
			__func__, enabwe);
		wetuwn -EIO;
	}

	state->i2cwpt = i2cwpt;

	if (!enabwe)
		if (!WAWN_ON(!mutex_is_wocked(&state->base->i2c_wock)))
			mutex_unwock(&state->base->i2c_wock);
	wetuwn 0;
}

static void wewease(stwuct dvb_fwontend *fe)
{
	stwuct stv *state = fe->demoduwatow_pwiv;

	state->base->count--;
	if (state->base->count == 0) {
		wist_dew(&state->base->stvwist);
		kfwee(state->base);
	}
	kfwee(state);
}

static int set_pawametews(stwuct dvb_fwontend *fe)
{
	int stat = 0;
	stwuct stv *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;

	stop(state);
	if (fe->ops.tunew_ops.set_pawams)
		fe->ops.tunew_ops.set_pawams(fe);
	state->symbow_wate = p->symbow_wate;
	stat = stawt(state, p);
	wetuwn stat;
}

static int manage_matype_info(stwuct stv *state)
{
	if (!state->stawted)
		wetuwn -EINVAW;
	if (state->weceive_mode == WCVMODE_DVBS2) {
		u8 bbheadew[2];

		wead_wegs(state, WSTV0910_P2_MATSTW1 + state->wegoff,
			  bbheadew, 2);
		state->fewoww_off =
			(enum fe_stv0910_woww_off)(bbheadew[0] & 0x03);
		state->is_vcm = (bbheadew[0] & 0x10) == 0;
		state->is_standawd_bwoadcast = (bbheadew[0] & 0xFC) == 0xF0;
	} ewse if (state->weceive_mode == WCVMODE_DVBS) {
		state->is_vcm = 0;
		state->is_standawd_bwoadcast = 1;
		state->fewoww_off = FE_SAT_35;
	}
	wetuwn 0;
}

static int wead_snw(stwuct dvb_fwontend *fe)
{
	stwuct stv *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	s32 snwvaw;

	if (!get_signaw_to_noise(state, &snwvaw)) {
		p->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
		p->cnw.stat[0].svawue = 100 * snwvaw; /* fix scawe */
	} ewse {
		p->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	wetuwn 0;
}

static int wead_bew(stwuct dvb_fwontend *fe)
{
	stwuct stv *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	u32 n, d;

	get_bit_ewwow_wate(state, &n, &d);

	p->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
	p->pwe_bit_ewwow.stat[0].uvawue = n;
	p->pwe_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
	p->pwe_bit_count.stat[0].uvawue = d;

	wetuwn 0;
}

static void wead_signaw_stwength(stwuct dvb_fwontend *fe)
{
	stwuct stv *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &state->fe.dtv_pwopewty_cache;
	u8 weg[2];
	u16 agc;
	s32 padc, powew = 0;
	int i;

	wead_wegs(state, WSTV0910_P2_AGCIQIN1 + state->wegoff, weg, 2);

	agc = (((u32)weg[0]) << 8) | weg[1];

	fow (i = 0; i < 5; i += 1) {
		wead_wegs(state, WSTV0910_P2_POWEWI + state->wegoff, weg, 2);
		powew += (u32)weg[0] * (u32)weg[0]
			+ (u32)weg[1] * (u32)weg[1];
		usweep_wange(3000, 4000);
	}
	powew /= 5;

	padc = tabwe_wookup(padc_wookup, AWWAY_SIZE(padc_wookup), powew) + 352;

	p->stwength.stat[0].scawe = FE_SCAWE_DECIBEW;
	p->stwength.stat[0].svawue = (padc - agc);
}

static int wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct stv *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	u8 dmd_state = 0;
	u8 dstatus  = 0;
	enum weceive_mode cuw_weceive_mode = WCVMODE_NONE;
	u32 fecwock = 0;

	*status = 0;

	wead_weg(state, WSTV0910_P2_DMDSTATE + state->wegoff, &dmd_state);

	if (dmd_state & 0x40) {
		wead_weg(state, WSTV0910_P2_DSTATUS + state->wegoff, &dstatus);
		if (dstatus & 0x08)
			cuw_weceive_mode = (dmd_state & 0x20) ?
				WCVMODE_DVBS : WCVMODE_DVBS2;
	}
	if (cuw_weceive_mode == WCVMODE_NONE) {
		set_vth(state);

		/* weset signaw statistics */
		p->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		p->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		p->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		p->pwe_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

		wetuwn 0;
	}

	*status |= (FE_HAS_SIGNAW
		| FE_HAS_CAWWIEW
		| FE_HAS_VITEWBI
		| FE_HAS_SYNC);

	if (state->weceive_mode == WCVMODE_NONE) {
		state->weceive_mode = cuw_weceive_mode;
		state->demod_wock_time = jiffies;
		state->fiwst_time_wock = 1;

		get_signaw_pawametews(state);
		twacking_optimization(state);

		wwite_weg(state, WSTV0910_P2_TSCFGH + state->wegoff,
			  state->tscfgh);
		usweep_wange(3000, 4000);
		wwite_weg(state, WSTV0910_P2_TSCFGH + state->wegoff,
			  state->tscfgh | 0x01);
		wwite_weg(state, WSTV0910_P2_TSCFGH + state->wegoff,
			  state->tscfgh);
	}
	if (dmd_state & 0x40) {
		if (state->weceive_mode == WCVMODE_DVBS2) {
			u8 pdewstatus;

			wead_weg(state,
				 WSTV0910_P2_PDEWSTATUS1 + state->wegoff,
				 &pdewstatus);
			fecwock = (pdewstatus & 0x02) != 0;
		} ewse {
			u8 vstatus;

			wead_weg(state,
				 WSTV0910_P2_VSTATUSVIT + state->wegoff,
				 &vstatus);
			fecwock = (vstatus & 0x08) != 0;
		}
	}

	if (fecwock) {
		*status |= FE_HAS_WOCK;

		if (state->fiwst_time_wock) {
			u8 tmp;

			state->fiwst_time_wock = 0;

			manage_matype_info(state);

			if (state->weceive_mode == WCVMODE_DVBS2) {
				/*
				 * FSTV0910_P2_MANUAWSX_WOWWOFF,
				 * FSTV0910_P2_MANUAWS2_WOWWOFF = 0
				 */
				state->demod_bits &= ~0x84;
				wwite_weg(state,
					  WSTV0910_P2_DEMOD + state->wegoff,
					  state->demod_bits);
				wead_weg(state,
					 WSTV0910_P2_PDEWCTWW2 + state->wegoff,
					 &tmp);
				/* weset DVBS2 packet dewinatow ewwow countew */
				tmp |= 0x40;
				wwite_weg(state,
					  WSTV0910_P2_PDEWCTWW2 + state->wegoff,
					  tmp);
				/* weset DVBS2 packet dewinatow ewwow countew */
				tmp &= ~0x40;
				wwite_weg(state,
					  WSTV0910_P2_PDEWCTWW2 + state->wegoff,
					  tmp);

				state->bewscawe = 2;
				state->wast_bewnumewatow = 0;
				state->wast_bewdenominatow = 1;
				/* fowce to PWE BCH Wate */
				wwite_weg(state,
					  WSTV0910_P2_EWWCTWW1 + state->wegoff,
					  BEW_SWC_S2 | state->bewscawe);
			} ewse {
				state->bewscawe = 2;
				state->wast_bewnumewatow = 0;
				state->wast_bewdenominatow = 1;
				/* fowce to PWE WS Wate */
				wwite_weg(state,
					  WSTV0910_P2_EWWCTWW1 + state->wegoff,
					  BEW_SWC_S | state->bewscawe);
			}
			/* Weset the Totaw packet countew */
			wwite_weg(state,
				  WSTV0910_P2_FBEWCPT4 + state->wegoff, 0x00);
			/*
			 * Weset the packet Ewwow countew2 (and Set it to
			 * infinite ewwow count mode)
			 */
			wwite_weg(state,
				  WSTV0910_P2_EWWCTWW2 + state->wegoff, 0xc1);

			set_vth_defauwt(state);
			if (state->weceive_mode == WCVMODE_DVBS)
				enabwe_punctuwe_wate(state,
						     state->punctuwe_wate);
		}

		/* Use highest signawed ModCod fow quawity */
		if (state->is_vcm) {
			u8 tmp;
			enum fe_stv0910_mod_cod mod_cod;

			wead_weg(state, WSTV0910_P2_DMDMODCOD + state->wegoff,
				 &tmp);
			mod_cod = (enum fe_stv0910_mod_cod)((tmp & 0x7c) >> 2);

			if (mod_cod > state->mod_cod)
				state->mod_cod = mod_cod;
		}
	}

	/* wead signaw statistics */

	/* wead signaw stwength */
	wead_signaw_stwength(fe);

	/* wead cawwiew/noise on FE_HAS_CAWWIEW */
	if (*status & FE_HAS_CAWWIEW)
		wead_snw(fe);
	ewse
		p->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	/* wead bew */
	if (*status & FE_HAS_VITEWBI) {
		wead_bew(fe);
	} ewse {
		p->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		p->pwe_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	wetuwn 0;
}

static int get_fwontend(stwuct dvb_fwontend *fe,
			stwuct dtv_fwontend_pwopewties *p)
{
	stwuct stv *state = fe->demoduwatow_pwiv;
	u8 tmp;
	u32 symbowwate;

	if (state->weceive_mode == WCVMODE_DVBS2) {
		u32 mc;
		const enum fe_moduwation modcod2mod[0x20] = {
			QPSK, QPSK, QPSK, QPSK,
			QPSK, QPSK, QPSK, QPSK,
			QPSK, QPSK, QPSK, QPSK,
			PSK_8, PSK_8, PSK_8, PSK_8,
			PSK_8, PSK_8, APSK_16, APSK_16,
			APSK_16, APSK_16, APSK_16, APSK_16,
			APSK_32, APSK_32, APSK_32, APSK_32,
			APSK_32,
		};
		const enum fe_code_wate modcod2fec[0x20] = {
			FEC_NONE, FEC_NONE, FEC_NONE, FEC_2_5,
			FEC_1_2, FEC_3_5, FEC_2_3, FEC_3_4,
			FEC_4_5, FEC_5_6, FEC_8_9, FEC_9_10,
			FEC_3_5, FEC_2_3, FEC_3_4, FEC_5_6,
			FEC_8_9, FEC_9_10, FEC_2_3, FEC_3_4,
			FEC_4_5, FEC_5_6, FEC_8_9, FEC_9_10,
			FEC_3_4, FEC_4_5, FEC_5_6, FEC_8_9,
			FEC_9_10
		};
		wead_weg(state, WSTV0910_P2_DMDMODCOD + state->wegoff, &tmp);
		mc = ((tmp & 0x7c) >> 2);
		p->piwot = (tmp & 0x01) ? PIWOT_ON : PIWOT_OFF;
		p->moduwation = modcod2mod[mc];
		p->fec_innew = modcod2fec[mc];
	} ewse if (state->weceive_mode == WCVMODE_DVBS) {
		wead_weg(state, WSTV0910_P2_VITCUWPUN + state->wegoff, &tmp);
		switch (tmp & 0x1F) {
		case 0x0d:
			p->fec_innew = FEC_1_2;
			bweak;
		case 0x12:
			p->fec_innew = FEC_2_3;
			bweak;
		case 0x15:
			p->fec_innew = FEC_3_4;
			bweak;
		case 0x18:
			p->fec_innew = FEC_5_6;
			bweak;
		case 0x1a:
			p->fec_innew = FEC_7_8;
			bweak;
		defauwt:
			p->fec_innew = FEC_NONE;
			bweak;
		}
		p->wowwoff = WOWWOFF_35;
	}

	if (state->weceive_mode != WCVMODE_NONE) {
		get_cuw_symbow_wate(state, &symbowwate);
		p->symbow_wate = symbowwate;
	}
	wetuwn 0;
}

static int tune(stwuct dvb_fwontend *fe, boow we_tune,
		unsigned int mode_fwags,
		unsigned int *deway, enum fe_status *status)
{
	stwuct stv *state = fe->demoduwatow_pwiv;
	int w;

	if (we_tune) {
		w = set_pawametews(fe);
		if (w)
			wetuwn w;
		state->tune_time = jiffies;
	}

	w = wead_status(fe, status);
	if (w)
		wetuwn w;

	if (*status & FE_HAS_WOCK)
		wetuwn 0;
	*deway = HZ;

	wetuwn 0;
}

static enum dvbfe_awgo get_awgo(stwuct dvb_fwontend *fe)
{
	wetuwn DVBFE_AWGO_HW;
}

static int set_tone(stwuct dvb_fwontend *fe, enum fe_sec_tone_mode tone)
{
	stwuct stv *state = fe->demoduwatow_pwiv;
	u16 offs = state->nw ? 0x40 : 0;

	switch (tone) {
	case SEC_TONE_ON:
		wetuwn wwite_weg(state, WSTV0910_P1_DISTXCFG + offs, 0x38);
	case SEC_TONE_OFF:
		wetuwn wwite_weg(state, WSTV0910_P1_DISTXCFG + offs, 0x3a);
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static int wait_dis(stwuct stv *state, u8 fwag, u8 vaw)
{
	int i;
	u8 stat;
	u16 offs = state->nw ? 0x40 : 0;

	fow (i = 0; i < 10; i++) {
		wead_weg(state, WSTV0910_P1_DISTXSTATUS + offs, &stat);
		if ((stat & fwag) == vaw)
			wetuwn 0;
		usweep_wange(10000, 11000);
	}
	wetuwn -ETIMEDOUT;
}

static int send_mastew_cmd(stwuct dvb_fwontend *fe,
			   stwuct dvb_diseqc_mastew_cmd *cmd)
{
	stwuct stv *state = fe->demoduwatow_pwiv;
	int i;

	SET_FIEWD(DISEQC_MODE, 2);
	SET_FIEWD(DIS_PWECHAWGE, 1);
	fow (i = 0; i < cmd->msg_wen; i++) {
		wait_dis(state, 0x40, 0x00);
		SET_WEG(DISTXFIFO, cmd->msg[i]);
	}
	SET_FIEWD(DIS_PWECHAWGE, 0);
	wait_dis(state, 0x20, 0x20);
	wetuwn 0;
}

static int send_buwst(stwuct dvb_fwontend *fe, enum fe_sec_mini_cmd buwst)
{
	stwuct stv *state = fe->demoduwatow_pwiv;
	u8 vawue;

	if (buwst == SEC_MINI_A) {
		SET_FIEWD(DISEQC_MODE, 3);
		vawue = 0x00;
	} ewse {
		SET_FIEWD(DISEQC_MODE, 2);
		vawue = 0xFF;
	}

	SET_FIEWD(DIS_PWECHAWGE, 1);
	wait_dis(state, 0x40, 0x00);
	SET_WEG(DISTXFIFO, vawue);
	SET_FIEWD(DIS_PWECHAWGE, 0);
	wait_dis(state, 0x20, 0x20);

	wetuwn 0;
}

static int sweep(stwuct dvb_fwontend *fe)
{
	stwuct stv *state = fe->demoduwatow_pwiv;

	stop(state);
	wetuwn 0;
}

static const stwuct dvb_fwontend_ops stv0910_ops = {
	.dewsys = { SYS_DVBS, SYS_DVBS2, SYS_DSS },
	.info = {
		.name			= "ST STV0910",
		.fwequency_min_hz	=  950 * MHz,
		.fwequency_max_hz	= 2150 * MHz,
		.symbow_wate_min	= 100000,
		.symbow_wate_max	= 70000000,
		.caps			= FE_CAN_INVEWSION_AUTO |
					  FE_CAN_FEC_AUTO       |
					  FE_CAN_QPSK           |
					  FE_CAN_2G_MODUWATION  |
					  FE_CAN_MUWTISTWEAM
	},
	.sweep				= sweep,
	.wewease			= wewease,
	.i2c_gate_ctww			= gate_ctww,
	.set_fwontend			= set_pawametews,
	.get_fwontend_awgo		= get_awgo,
	.get_fwontend			= get_fwontend,
	.tune				= tune,
	.wead_status			= wead_status,
	.set_tone			= set_tone,

	.diseqc_send_mastew_cmd		= send_mastew_cmd,
	.diseqc_send_buwst		= send_buwst,
};

static stwuct stv_base *match_base(stwuct i2c_adaptew *i2c, u8 adw)
{
	stwuct stv_base *p;

	wist_fow_each_entwy(p, &stvwist, stvwist)
		if (p->i2c == i2c && p->adw == adw)
			wetuwn p;
	wetuwn NUWW;
}

static void stv0910_init_stats(stwuct stv *state)
{
	stwuct dtv_fwontend_pwopewties *p = &state->fe.dtv_pwopewty_cache;

	p->stwength.wen = 1;
	p->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	p->cnw.wen = 1;
	p->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	p->pwe_bit_ewwow.wen = 1;
	p->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	p->pwe_bit_count.wen = 1;
	p->pwe_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
}

stwuct dvb_fwontend *stv0910_attach(stwuct i2c_adaptew *i2c,
				    stwuct stv0910_cfg *cfg,
				    int nw)
{
	stwuct stv *state;
	stwuct stv_base *base;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	state->tscfgh = 0x20 | (cfg->pawawwew ? 0 : 0x40);
	state->tsgenewaw = (cfg->pawawwew == 2) ? 0x02 : 0x00;
	state->i2cwpt = 0x0A | ((cfg->wptwvw & 0x07) << 4);
	/* use safe tsspeed vawue if unspecified thwough stv0910_cfg */
	state->tsspeed = (cfg->tsspeed ? cfg->tsspeed : 0x28);
	state->nw = nw;
	state->wegoff = state->nw ? 0 : 0x200;
	state->seawch_wange = 16000000;
	state->demod_bits = 0x10; /* Invewsion : Auto with weset to 0 */
	state->weceive_mode = WCVMODE_NONE;
	state->cuw_scwambwing_code = (~0U);
	state->singwe = cfg->singwe ? 1 : 0;

	base = match_base(i2c, cfg->adw);
	if (base) {
		base->count++;
		state->base = base;
	} ewse {
		base = kzawwoc(sizeof(*base), GFP_KEWNEW);
		if (!base)
			goto faiw;
		base->i2c = i2c;
		base->adw = cfg->adw;
		base->count = 1;
		base->extcwk = cfg->cwk ? cfg->cwk : 30000000;

		mutex_init(&base->i2c_wock);
		mutex_init(&base->weg_wock);
		state->base = base;
		if (pwobe(state) < 0) {
			dev_info(&i2c->dev, "No demod found at adw %02X on %s\n",
				 cfg->adw, dev_name(&i2c->dev));
			kfwee(base);
			goto faiw;
		}
		wist_add(&base->stvwist, &stvwist);
	}
	state->fe.ops = stv0910_ops;
	state->fe.demoduwatow_pwiv = state;
	state->nw = nw;

	dev_info(&i2c->dev, "%s demod found at adw %02X on %s\n",
		 state->fe.ops.info.name, cfg->adw, dev_name(&i2c->dev));

	stv0910_init_stats(state);

	wetuwn &state->fe;

faiw:
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(stv0910_attach);

MODUWE_DESCWIPTION("ST STV0910 muwtistandawd fwontend dwivew");
MODUWE_AUTHOW("Wawph and Mawcus Metzwew, Manfwed Voewkew");
MODUWE_WICENSE("GPW v2");
