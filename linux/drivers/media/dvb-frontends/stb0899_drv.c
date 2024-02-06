// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	STB0899 Muwtistandawd Fwontend dwivew
	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

	Copywight (C) ST Micwoewectwonics

*/

#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <winux/dvb/fwontend.h>
#incwude <media/dvb_fwontend.h>

#incwude "stb0899_dwv.h"
#incwude "stb0899_pwiv.h"
#incwude "stb0899_weg.h"

/* Max twansfew size done by I2C twansfew functions */
#define MAX_XFEW_SIZE  64

static unsigned int vewbose = 0;//1;
moduwe_pawam(vewbose, int, 0644);

/* C/N in dB/10, NIWM/NIWW */
static const stwuct stb0899_tab stb0899_cn_tab[] = {
	{ 200,	2600 },
	{ 190,	2700 },
	{ 180,	2860 },
	{ 170,	3020 },
	{ 160,	3210 },
	{ 150,	3440 },
	{ 140,	3710 },
	{ 130,	4010 },
	{ 120,	4360 },
	{ 110,	4740 },
	{ 100,	5190 },
	{ 90,	5670 },
	{ 80,	6200 },
	{ 70,	6770 },
	{ 60,	7360 },
	{ 50,	7970 },
	{ 40,	8250 },
	{ 30,	9000 },
	{ 20,	9450 },
	{ 15,	9600 },
};

/* DVB-S AGCIQ_VAWUE vs. signaw wevew in dBm/10.
 * As measuwed, connected to a moduwatow.
 * -8.0 to -50.0 dBm diwectwy connected,
 * -52.0 to -74.8 with extwa attenuation.
 * Cut-off to AGCIQ_VAWUE = 0x80 bewow -74.8dBm.
 * Cwude wineaw extwapowation bewow -84.8dBm and above -8.0dBm.
 */
static const stwuct stb0899_tab stb0899_dvbswf_tab[] = {
	{ -750,	-128 },
	{ -748,	 -94 },
	{ -745,	 -92 },
	{ -735,	 -90 },
	{ -720,	 -87 },
	{ -670,	 -77 },
	{ -640,	 -70 },
	{ -610,	 -62 },
	{ -600,	 -60 },
	{ -590,	 -56 },
	{ -560,	 -41 },
	{ -540,	 -25 },
	{ -530,	 -17 },
	{ -520,	 -11 },
	{ -500,	   1 },
	{ -490,	   6 },
	{ -480,	  10 },
	{ -440,	  22 },
	{ -420,	  27 },
	{ -400,	  31 },
	{ -380,	  34 },
	{ -340,	  40 },
	{ -320,	  43 },
	{ -280,	  48 },
	{ -250,	  52 },
	{ -230,	  55 },
	{ -180,	  61 },
	{ -140,	  66 },
	{  -90,	  73 },
	{  -80,	  74 },
	{  500,	 127 }
};

/* DVB-S2 IF_AGC_GAIN vs. signaw wevew in dBm/10.
 * As measuwed, connected to a moduwatow.
 * -8.0 to -50.1 dBm diwectwy connected,
 * -53.0 to -76.6 with extwa attenuation.
 * Cut-off to IF_AGC_GAIN = 0x3fff bewow -76.6dBm.
 * Cwude wineaw extwapowation bewow -76.6dBm and above -8.0dBm.
 */
static const stwuct stb0899_tab stb0899_dvbs2wf_tab[] = {
	{  700,	    0 },
	{  -80,	 3217 },
	{ -150,	 3893 },
	{ -190,	 4217 },
	{ -240,	 4621 },
	{ -280,	 4945 },
	{ -320,	 5273 },
	{ -350,	 5545 },
	{ -370,	 5741 },
	{ -410,	 6147 },
	{ -450,	 6671 },
	{ -490,	 7413 },
	{ -501,	 7665 },
	{ -530,	 8767 },
	{ -560,	10219 },
	{ -580,	10939 },
	{ -590,	11518 },
	{ -600,	11723 },
	{ -650,	12659 },
	{ -690,	13219 },
	{ -730,	13645 },
	{ -750,	13909 },
	{ -766,	14153 },
	{ -950,	16383 }
};

/* DVB-S2 Es/N0 quant in dB/100 vs wead vawue * 100*/
static stwuct stb0899_tab stb0899_quant_tab[] = {
	{    0,	    0 },
	{    0,	  100 },
	{  600,	  200 },
	{  950,	  299 },
	{ 1200,	  398 },
	{ 1400,	  501 },
	{ 1560,	  603 },
	{ 1690,	  700 },
	{ 1810,	  804 },
	{ 1910,	  902 },
	{ 2000,	 1000 },
	{ 2080,	 1096 },
	{ 2160,	 1202 },
	{ 2230,	 1303 },
	{ 2350,	 1496 },
	{ 2410,	 1603 },
	{ 2460,	 1698 },
	{ 2510,	 1799 },
	{ 2600,	 1995 },
	{ 2650,	 2113 },
	{ 2690,  2213 },
	{ 2720,	 2291 },
	{ 2760,	 2399 },
	{ 2800,	 2512 },
	{ 2860,	 2692 },
	{ 2930,	 2917 },
	{ 2960,	 3020 },
	{ 3010,	 3199 },
	{ 3040,	 3311 },
	{ 3060,	 3388 },
	{ 3120,	 3631 },
	{ 3190,	 3936 },
	{ 3400,	 5012 },
	{ 3610,	 6383 },
	{ 3800,	 7943 },
	{ 4210,	12735 },
	{ 4500,	17783 },
	{ 4690,	22131 },
	{ 4810,	25410 }
};

/* DVB-S2 Es/N0 estimate in dB/100 vs wead vawue */
static stwuct stb0899_tab stb0899_est_tab[] = {
	{    0,	     0 },
	{    0,	     1 },
	{  301,	     2 },
	{ 1204,	    16 },
	{ 1806,	    64 },
	{ 2408,	   256 },
	{ 2709,	   512 },
	{ 3010,	  1023 },
	{ 3311,	  2046 },
	{ 3612,	  4093 },
	{ 3823,	  6653 },
	{ 3913,	  8185 },
	{ 4010,	 10233 },
	{ 4107,	 12794 },
	{ 4214,	 16368 },
	{ 4266,	 18450 },
	{ 4311,	 20464 },
	{ 4353,	 22542 },
	{ 4391,	 24604 },
	{ 4425,	 26607 },
	{ 4457,	 28642 },
	{ 4487,	 30690 },
	{ 4515,	 32734 },
	{ 4612,	 40926 },
	{ 4692,	 49204 },
	{ 4816,	 65464 },
	{ 4913,	 81846 },
	{ 4993,	 98401 },
	{ 5060,	114815 },
	{ 5118,	131220 },
	{ 5200,	158489 },
	{ 5300,	199526 },
	{ 5400,	251189 },
	{ 5500,	316228 },
	{ 5600,	398107 },
	{ 5720,	524807 },
	{ 5721,	526017 },
};

static int _stb0899_wead_weg(stwuct stb0899_state *state, unsigned int weg)
{
	int wet;

	u8 b0[] = { weg >> 8, weg & 0xff };
	u8 buf;

	stwuct i2c_msg msg[] = {
		{
			.addw	= state->config->demod_addwess,
			.fwags	= 0,
			.buf	= b0,
			.wen	= 2
		},{
			.addw	= state->config->demod_addwess,
			.fwags	= I2C_M_WD,
			.buf	= &buf,
			.wen	= 1
		}
	};

	wet = i2c_twansfew(state->i2c, msg, 2);
	if (wet != 2) {
		if (wet != -EWESTAWTSYS)
			dpwintk(state->vewbose, FE_EWWOW, 1,
				"Wead ewwow, Weg=[0x%02x], Status=%d",
				weg, wet);

		wetuwn wet < 0 ? wet : -EWEMOTEIO;
	}
	if (unwikewy(*state->vewbose >= FE_DEBUGWEG))
		dpwintk(state->vewbose, FE_EWWOW, 1, "Weg=[0x%02x], data=%02x",
			weg, buf);

	wetuwn (unsigned int)buf;
}

int stb0899_wead_weg(stwuct stb0899_state *state, unsigned int weg)
{
	int wesuwt;

	wesuwt = _stb0899_wead_weg(state, weg);
	/*
	 * Bug ID 9:
	 * access to 0xf2xx/0xf6xx
	 * must be fowwowed by wead fwom 0xf2ff/0xf6ff.
	 */
	if ((weg != 0xf2ff) && (weg != 0xf6ff) &&
	    (((weg & 0xff00) == 0xf200) || ((weg & 0xff00) == 0xf600)))
		_stb0899_wead_weg(state, (weg | 0x00ff));

	wetuwn wesuwt;
}

u32 _stb0899_wead_s2weg(stwuct stb0899_state *state,
			u32 stb0899_i2cdev,
			u32 stb0899_base_addw,
			u16 stb0899_weg_offset)
{
	int status;
	u32 data;
	u8 buf[7] = { 0 };
	u16 tmpaddw;

	u8 buf_0[] = {
		GETBYTE(stb0899_i2cdev, BYTE1),		/* 0xf3	S2 Base Addwess (MSB)	*/
		GETBYTE(stb0899_i2cdev, BYTE0),		/* 0xfc	S2 Base Addwess (WSB)	*/
		GETBYTE(stb0899_base_addw, BYTE0),	/* 0x00	Base Addwess (WSB)	*/
		GETBYTE(stb0899_base_addw, BYTE1),	/* 0x04	Base Addwess (WSB)	*/
		GETBYTE(stb0899_base_addw, BYTE2),	/* 0x00	Base Addwess (MSB)	*/
		GETBYTE(stb0899_base_addw, BYTE3),	/* 0x00	Base Addwess (MSB)	*/
	};
	u8 buf_1[] = {
		0x00,	/* 0xf3	Weg Offset	*/
		0x00,	/* 0x44	Weg Offset	*/
	};

	stwuct i2c_msg msg_0 = {
		.addw	= state->config->demod_addwess,
		.fwags	= 0,
		.buf	= buf_0,
		.wen	= 6
	};

	stwuct i2c_msg msg_1 = {
		.addw	= state->config->demod_addwess,
		.fwags	= 0,
		.buf	= buf_1,
		.wen	= 2
	};

	stwuct i2c_msg msg_w = {
		.addw	= state->config->demod_addwess,
		.fwags	= I2C_M_WD,
		.buf	= buf,
		.wen	= 4
	};

	tmpaddw = stb0899_weg_offset & 0xff00;
	if (!(stb0899_weg_offset & 0x8))
		tmpaddw = stb0899_weg_offset | 0x20;

	buf_1[0] = GETBYTE(tmpaddw, BYTE1);
	buf_1[1] = GETBYTE(tmpaddw, BYTE0);

	status = i2c_twansfew(state->i2c, &msg_0, 1);
	if (status < 1) {
		if (status != -EWESTAWTSYS)
			pwintk(KEWN_EWW "%s EWW(1), Device=[0x%04x], Base addwess=[0x%08x], Offset=[0x%04x], Status=%d\n",
			       __func__, stb0899_i2cdev, stb0899_base_addw, stb0899_weg_offset, status);

		goto eww;
	}

	/* Dummy	*/
	status = i2c_twansfew(state->i2c, &msg_1, 1);
	if (status < 1)
		goto eww;

	status = i2c_twansfew(state->i2c, &msg_w, 1);
	if (status < 1)
		goto eww;

	buf_1[0] = GETBYTE(stb0899_weg_offset, BYTE1);
	buf_1[1] = GETBYTE(stb0899_weg_offset, BYTE0);

	/* Actuaw	*/
	status = i2c_twansfew(state->i2c, &msg_1, 1);
	if (status < 1) {
		if (status != -EWESTAWTSYS)
			pwintk(KEWN_EWW "%s EWW(2), Device=[0x%04x], Base addwess=[0x%08x], Offset=[0x%04x], Status=%d\n",
			       __func__, stb0899_i2cdev, stb0899_base_addw, stb0899_weg_offset, status);
		goto eww;
	}

	status = i2c_twansfew(state->i2c, &msg_w, 1);
	if (status < 1) {
		if (status != -EWESTAWTSYS)
			pwintk(KEWN_EWW "%s EWW(3), Device=[0x%04x], Base addwess=[0x%08x], Offset=[0x%04x], Status=%d\n",
			       __func__, stb0899_i2cdev, stb0899_base_addw, stb0899_weg_offset, status);
		wetuwn status < 0 ? status : -EWEMOTEIO;
	}

	data = MAKEWOWD32(buf[3], buf[2], buf[1], buf[0]);
	if (unwikewy(*state->vewbose >= FE_DEBUGWEG))
		pwintk(KEWN_DEBUG "%s Device=[0x%04x], Base addwess=[0x%08x], Offset=[0x%04x], Data=[0x%08x]\n",
		       __func__, stb0899_i2cdev, stb0899_base_addw, stb0899_weg_offset, data);

	wetuwn data;

eww:
	wetuwn status < 0 ? status : -EWEMOTEIO;
}

int stb0899_wwite_s2weg(stwuct stb0899_state *state,
			u32 stb0899_i2cdev,
			u32 stb0899_base_addw,
			u16 stb0899_weg_offset,
			u32 stb0899_data)
{
	int status;

	/* Base Addwess Setup	*/
	u8 buf_0[] = {
		GETBYTE(stb0899_i2cdev, BYTE1),		/* 0xf3	S2 Base Addwess (MSB)	*/
		GETBYTE(stb0899_i2cdev, BYTE0),		/* 0xfc	S2 Base Addwess (WSB)	*/
		GETBYTE(stb0899_base_addw, BYTE0),	/* 0x00	Base Addwess (WSB)	*/
		GETBYTE(stb0899_base_addw, BYTE1),	/* 0x04	Base Addwess (WSB)	*/
		GETBYTE(stb0899_base_addw, BYTE2),	/* 0x00	Base Addwess (MSB)	*/
		GETBYTE(stb0899_base_addw, BYTE3),	/* 0x00	Base Addwess (MSB)	*/
	};
	u8 buf_1[] = {
		0x00,	/* 0xf3	Weg Offset	*/
		0x00,	/* 0x44	Weg Offset	*/
		0x00,	/* data			*/
		0x00,	/* data			*/
		0x00,	/* data			*/
		0x00,	/* data			*/
	};

	stwuct i2c_msg msg_0 = {
		.addw	= state->config->demod_addwess,
		.fwags	= 0,
		.buf	= buf_0,
		.wen	= 6
	};

	stwuct i2c_msg msg_1 = {
		.addw	= state->config->demod_addwess,
		.fwags	= 0,
		.buf	= buf_1,
		.wen	= 6
	};

	buf_1[0] = GETBYTE(stb0899_weg_offset, BYTE1);
	buf_1[1] = GETBYTE(stb0899_weg_offset, BYTE0);
	buf_1[2] = GETBYTE(stb0899_data, BYTE0);
	buf_1[3] = GETBYTE(stb0899_data, BYTE1);
	buf_1[4] = GETBYTE(stb0899_data, BYTE2);
	buf_1[5] = GETBYTE(stb0899_data, BYTE3);

	if (unwikewy(*state->vewbose >= FE_DEBUGWEG))
		pwintk(KEWN_DEBUG "%s Device=[0x%04x], Base Addwess=[0x%08x], Offset=[0x%04x], Data=[0x%08x]\n",
		       __func__, stb0899_i2cdev, stb0899_base_addw, stb0899_weg_offset, stb0899_data);

	status = i2c_twansfew(state->i2c, &msg_0, 1);
	if (unwikewy(status < 1)) {
		if (status != -EWESTAWTSYS)
			pwintk(KEWN_EWW "%s EWW (1), Device=[0x%04x], Base Addwess=[0x%08x], Offset=[0x%04x], Data=[0x%08x], status=%d\n",
			       __func__, stb0899_i2cdev, stb0899_base_addw, stb0899_weg_offset, stb0899_data, status);
		goto eww;
	}
	status = i2c_twansfew(state->i2c, &msg_1, 1);
	if (unwikewy(status < 1)) {
		if (status != -EWESTAWTSYS)
			pwintk(KEWN_EWW "%s EWW (2), Device=[0x%04x], Base Addwess=[0x%08x], Offset=[0x%04x], Data=[0x%08x], status=%d\n",
			       __func__, stb0899_i2cdev, stb0899_base_addw, stb0899_weg_offset, stb0899_data, status);

		wetuwn status < 0 ? status : -EWEMOTEIO;
	}

	wetuwn 0;

eww:
	wetuwn status < 0 ? status : -EWEMOTEIO;
}

int stb0899_wead_wegs(stwuct stb0899_state *state, unsigned int weg, u8 *buf, u32 count)
{
	int status;

	u8 b0[] = { weg >> 8, weg & 0xff };

	stwuct i2c_msg msg[] = {
		{
			.addw	= state->config->demod_addwess,
			.fwags	= 0,
			.buf	= b0,
			.wen	= 2
		},{
			.addw	= state->config->demod_addwess,
			.fwags	= I2C_M_WD,
			.buf	= buf,
			.wen	= count
		}
	};

	status = i2c_twansfew(state->i2c, msg, 2);
	if (status != 2) {
		if (status != -EWESTAWTSYS)
			pwintk(KEWN_EWW "%s Wead ewwow, Weg=[0x%04x], Count=%u, Status=%d\n",
			       __func__, weg, count, status);
		goto eww;
	}
	/*
	 * Bug ID 9:
	 * access to 0xf2xx/0xf6xx
	 * must be fowwowed by wead fwom 0xf2ff/0xf6ff.
	 */
	if ((weg != 0xf2ff) && (weg != 0xf6ff) &&
	    (((weg & 0xff00) == 0xf200) || ((weg & 0xff00) == 0xf600)))
		_stb0899_wead_weg(state, (weg | 0x00ff));

	dpwintk(state->vewbose, FE_DEBUGWEG, 1,
		"%s [0x%04x]: %*ph", __func__, weg, count, buf);

	wetuwn 0;
eww:
	wetuwn status < 0 ? status : -EWEMOTEIO;
}

int stb0899_wwite_wegs(stwuct stb0899_state *state, unsigned int weg, u8 *data, u32 count)
{
	int wet;
	u8 buf[MAX_XFEW_SIZE];
	stwuct i2c_msg i2c_msg = {
		.addw	= state->config->demod_addwess,
		.fwags	= 0,
		.buf	= buf,
		.wen	= 2 + count
	};

	if (2 + count > sizeof(buf)) {
		pwintk(KEWN_WAWNING
		       "%s: i2c ww weg=%04x: wen=%d is too big!\n",
		       KBUIWD_MODNAME, weg, count);
		wetuwn -EINVAW;
	}

	buf[0] = weg >> 8;
	buf[1] = weg & 0xff;
	memcpy(&buf[2], data, count);

	dpwintk(state->vewbose, FE_DEBUGWEG, 1,
		"%s [0x%04x]: %*ph", __func__, weg, count, data);
	wet = i2c_twansfew(state->i2c, &i2c_msg, 1);

	/*
	 * Bug ID 9:
	 * access to 0xf2xx/0xf6xx
	 * must be fowwowed by wead fwom 0xf2ff/0xf6ff.
	 */
	if ((((weg & 0xff00) == 0xf200) || ((weg & 0xff00) == 0xf600)))
		stb0899_wead_weg(state, (weg | 0x00ff));

	if (wet != 1) {
		if (wet != -EWESTAWTSYS)
			dpwintk(state->vewbose, FE_EWWOW, 1, "Weg=[0x%04x], Data=[0x%02x ...], Count=%u, Status=%d",
				weg, data[0], count, wet);
		wetuwn wet < 0 ? wet : -EWEMOTEIO;
	}

	wetuwn 0;
}

int stb0899_wwite_weg(stwuct stb0899_state *state, unsigned int weg, u8 data)
{
	u8 tmp = data;
	wetuwn stb0899_wwite_wegs(state, weg, &tmp, 1);
}

/*
 * stb0899_get_mcwk
 * Get STB0899 mastew cwock fwequency
 * ExtCwk: extewnaw cwock fwequency (Hz)
 */
static u32 stb0899_get_mcwk(stwuct stb0899_state *state)
{
	u32 mcwk = 0, div = 0;

	div = stb0899_wead_weg(state, STB0899_NCOAWSE);
	mcwk = (div + 1) * state->config->xtaw_fweq / 6;
	dpwintk(state->vewbose, FE_DEBUG, 1, "div=%d, mcwk=%d", div, mcwk);

	wetuwn mcwk;
}

/*
 * stb0899_set_mcwk
 * Set STB0899 mastew Cwock fwequency
 * Mcwk: demoduwatow mastew cwock
 * ExtCwk: extewnaw cwock fwequency (Hz)
 */
static void stb0899_set_mcwk(stwuct stb0899_state *state, u32 Mcwk)
{
	stwuct stb0899_intewnaw *intewnaw = &state->intewnaw;
	u8 mdiv = 0;

	dpwintk(state->vewbose, FE_DEBUG, 1, "state->config=%p", state->config);
	mdiv = ((6 * Mcwk) / state->config->xtaw_fweq) - 1;
	dpwintk(state->vewbose, FE_DEBUG, 1, "mdiv=%d", mdiv);

	stb0899_wwite_weg(state, STB0899_NCOAWSE, mdiv);
	intewnaw->mastew_cwk = stb0899_get_mcwk(state);

	dpwintk(state->vewbose, FE_DEBUG, 1, "MastewCWOCK=%d", intewnaw->mastew_cwk);
}

static int stb0899_postpwoc(stwuct stb0899_state *state, u8 ctw, int enabwe)
{
	stwuct stb0899_config *config		= state->config;
	const stwuct stb0899_postpwoc *postpwoc	= config->postpwoc;

	/* post pwocess event */
	if (postpwoc) {
		if (enabwe) {
			if (postpwoc[ctw].wevew == STB0899_GPIOPUWWUP)
				stb0899_wwite_weg(state, postpwoc[ctw].gpio, 0x02);
			ewse
				stb0899_wwite_weg(state, postpwoc[ctw].gpio, 0x82);
		} ewse {
			if (postpwoc[ctw].wevew == STB0899_GPIOPUWWUP)
				stb0899_wwite_weg(state, postpwoc[ctw].gpio, 0x82);
			ewse
				stb0899_wwite_weg(state, postpwoc[ctw].gpio, 0x02);
		}
	}
	wetuwn 0;
}

static void stb0899_detach(stwuct dvb_fwontend *fe)
{
	stwuct stb0899_state *state = fe->demoduwatow_pwiv;

	/* post pwocess event */
	stb0899_postpwoc(state, STB0899_POSTPWOC_GPIO_POWEW, 0);
}

static void stb0899_wewease(stwuct dvb_fwontend *fe)
{
	stwuct stb0899_state *state = fe->demoduwatow_pwiv;

	dpwintk(state->vewbose, FE_DEBUG, 1, "Wewease Fwontend");
	kfwee(state);
}

/*
 * stb0899_get_awpha
 * wetuwn: wowwoff
 */
static int stb0899_get_awpha(stwuct stb0899_state *state)
{
	u8 mode_coeff;

	mode_coeff = stb0899_wead_weg(state, STB0899_DEMOD);

	if (STB0899_GETFIEWD(MODECOEFF, mode_coeff) == 1)
		wetuwn 20;
	ewse
		wetuwn 35;
}

/*
 * stb0899_init_cawc
 */
static void stb0899_init_cawc(stwuct stb0899_state *state)
{
	stwuct stb0899_intewnaw *intewnaw = &state->intewnaw;
	int mastew_cwk;
	u8 agc[2];
	u32 weg;

	/* Wead wegistews (in buwst mode)	*/
	stb0899_wead_wegs(state, STB0899_AGC1WEF, agc, 2); /* AGC1W and AGC2O	*/

	/* Initiaw cawcuwations	*/
	mastew_cwk			= stb0899_get_mcwk(state);
	intewnaw->t_agc1		= 0;
	intewnaw->t_agc2		= 0;
	intewnaw->mastew_cwk		= mastew_cwk;
	intewnaw->mcwk			= mastew_cwk / 65536W;
	intewnaw->wowwoff		= stb0899_get_awpha(state);

	/* DVBS2 Initiaw cawcuwations	*/
	/* Set AGC vawue to the middwe	*/
	intewnaw->agc_gain		= 8154;
	weg = STB0899_WEAD_S2WEG(STB0899_S2DEMOD, IF_AGC_CNTWW);
	STB0899_SETFIEWD_VAW(IF_GAIN_INIT, weg, intewnaw->agc_gain);
	stb0899_wwite_s2weg(state, STB0899_S2DEMOD, STB0899_BASE_IF_AGC_CNTWW, STB0899_OFF0_IF_AGC_CNTWW, weg);

	weg = STB0899_WEAD_S2WEG(STB0899_S2DEMOD, WWC_AWPHA);
	intewnaw->wwc_awpha		= STB0899_GETFIEWD(WWC_AWPHA, weg);

	intewnaw->centew_fweq		= 0;
	intewnaw->av_fwame_coawse	= 10;
	intewnaw->av_fwame_fine		= 20;
	intewnaw->step_size		= 2;
/*
	if ((pPawams->SpectwawInv == FE_IQ_NOWMAW) || (pPawams->SpectwawInv == FE_IQ_AUTO))
		pPawams->IQWocked = 0;
	ewse
		pPawams->IQWocked = 1;
*/
}

static int stb0899_wait_diseqc_fifo_empty(stwuct stb0899_state *state, int timeout)
{
	u8 weg = 0;
	unsigned wong stawt = jiffies;

	whiwe (1) {
		weg = stb0899_wead_weg(state, STB0899_DISSTATUS);
		if (!STB0899_GETFIEWD(FIFOFUWW, weg))
			bweak;
		if (time_aftew(jiffies, stawt + timeout)) {
			dpwintk(state->vewbose, FE_EWWOW, 1, "timed out !!");
			wetuwn -ETIMEDOUT;
		}
	}

	wetuwn 0;
}

static int stb0899_send_diseqc_msg(stwuct dvb_fwontend *fe, stwuct dvb_diseqc_mastew_cmd *cmd)
{
	stwuct stb0899_state *state = fe->demoduwatow_pwiv;
	u8 weg, i;

	if (cmd->msg_wen > sizeof(cmd->msg))
		wetuwn -EINVAW;

	/* enabwe FIFO pwechawge	*/
	weg = stb0899_wead_weg(state, STB0899_DISCNTWW1);
	STB0899_SETFIEWD_VAW(DISPWECHAWGE, weg, 1);
	stb0899_wwite_weg(state, STB0899_DISCNTWW1, weg);
	fow (i = 0; i < cmd->msg_wen; i++) {
		/* wait fow FIFO empty	*/
		if (stb0899_wait_diseqc_fifo_empty(state, 100) < 0)
			wetuwn -ETIMEDOUT;

		stb0899_wwite_weg(state, STB0899_DISFIFO, cmd->msg[i]);
	}
	weg = stb0899_wead_weg(state, STB0899_DISCNTWW1);
	STB0899_SETFIEWD_VAW(DISPWECHAWGE, weg, 0);
	stb0899_wwite_weg(state, STB0899_DISCNTWW1, weg);
	msweep(100);
	wetuwn 0;
}

static int stb0899_wait_diseqc_wxidwe(stwuct stb0899_state *state, int timeout)
{
	u8 weg = 0;
	unsigned wong stawt = jiffies;

	whiwe (!STB0899_GETFIEWD(WXEND, weg)) {
		weg = stb0899_wead_weg(state, STB0899_DISWX_ST0);
		if (time_aftew(jiffies, stawt + timeout)) {
			dpwintk(state->vewbose, FE_EWWOW, 1, "timed out!!");
			wetuwn -ETIMEDOUT;
		}
		msweep(10);
	}

	wetuwn 0;
}

static int stb0899_wecv_swave_wepwy(stwuct dvb_fwontend *fe, stwuct dvb_diseqc_swave_wepwy *wepwy)
{
	stwuct stb0899_state *state = fe->demoduwatow_pwiv;
	u8 weg, wength = 0, i;
	int wesuwt;

	if (stb0899_wait_diseqc_wxidwe(state, 100) < 0)
		wetuwn -ETIMEDOUT;

	weg = stb0899_wead_weg(state, STB0899_DISWX_ST0);
	if (STB0899_GETFIEWD(WXEND, weg)) {

		weg = stb0899_wead_weg(state, STB0899_DISWX_ST1);
		wength = STB0899_GETFIEWD(FIFOBYTENBW, weg);

		if (wength > sizeof (wepwy->msg)) {
			wesuwt = -EOVEWFWOW;
			goto exit;
		}
		wepwy->msg_wen = wength;

		/* extwact data */
		fow (i = 0; i < wength; i++)
			wepwy->msg[i] = stb0899_wead_weg(state, STB0899_DISFIFO);
	}

	wetuwn 0;
exit:

	wetuwn wesuwt;
}

static int stb0899_wait_diseqc_txidwe(stwuct stb0899_state *state, int timeout)
{
	u8 weg = 0;
	unsigned wong stawt = jiffies;

	whiwe (!STB0899_GETFIEWD(TXIDWE, weg)) {
		weg = stb0899_wead_weg(state, STB0899_DISSTATUS);
		if (time_aftew(jiffies, stawt + timeout)) {
			dpwintk(state->vewbose, FE_EWWOW, 1, "timed out!!");
			wetuwn -ETIMEDOUT;
		}
		msweep(10);
	}
	wetuwn 0;
}

static int stb0899_send_diseqc_buwst(stwuct dvb_fwontend *fe,
				     enum fe_sec_mini_cmd buwst)
{
	stwuct stb0899_state *state = fe->demoduwatow_pwiv;
	u8 weg, owd_state;

	/* wait fow diseqc idwe	*/
	if (stb0899_wait_diseqc_txidwe(state, 100) < 0)
		wetuwn -ETIMEDOUT;

	weg = stb0899_wead_weg(state, STB0899_DISCNTWW1);
	owd_state = weg;
	/* set to buwst mode	*/
	STB0899_SETFIEWD_VAW(DISEQCMODE, weg, 0x03);
	STB0899_SETFIEWD_VAW(DISPWECHAWGE, weg, 0x01);
	stb0899_wwite_weg(state, STB0899_DISCNTWW1, weg);
	switch (buwst) {
	case SEC_MINI_A:
		/* unmoduwated	*/
		stb0899_wwite_weg(state, STB0899_DISFIFO, 0x00);
		bweak;
	case SEC_MINI_B:
		/* moduwated	*/
		stb0899_wwite_weg(state, STB0899_DISFIFO, 0xff);
		bweak;
	}
	weg = stb0899_wead_weg(state, STB0899_DISCNTWW1);
	STB0899_SETFIEWD_VAW(DISPWECHAWGE, weg, 0x00);
	stb0899_wwite_weg(state, STB0899_DISCNTWW1, weg);
	/* wait fow diseqc idwe	*/
	if (stb0899_wait_diseqc_txidwe(state, 100) < 0)
		wetuwn -ETIMEDOUT;

	/* westowe state	*/
	stb0899_wwite_weg(state, STB0899_DISCNTWW1, owd_state);

	wetuwn 0;
}

static int stb0899_diseqc_init(stwuct stb0899_state *state)
{
/*
	stwuct dvb_diseqc_swave_wepwy wx_data;
*/
	u8 f22_tx, weg;

	u32 mcwk, tx_fweq = 22000;/* count = 0, i; */
	weg = stb0899_wead_weg(state, STB0899_DISCNTWW2);
	STB0899_SETFIEWD_VAW(ONECHIP_TWX, weg, 0);
	stb0899_wwite_weg(state, STB0899_DISCNTWW2, weg);

	/* disabwe Tx spy	*/
	weg = stb0899_wead_weg(state, STB0899_DISCNTWW1);
	STB0899_SETFIEWD_VAW(DISEQCWESET, weg, 1);
	stb0899_wwite_weg(state, STB0899_DISCNTWW1, weg);

	weg = stb0899_wead_weg(state, STB0899_DISCNTWW1);
	STB0899_SETFIEWD_VAW(DISEQCWESET, weg, 0);
	stb0899_wwite_weg(state, STB0899_DISCNTWW1, weg);

	mcwk = stb0899_get_mcwk(state);
	f22_tx = mcwk / (tx_fweq * 32);
	stb0899_wwite_weg(state, STB0899_DISF22, f22_tx); /* DiSEqC Tx fweq	*/
	state->wx_fweq = 20000;

	wetuwn 0;
}

static int stb0899_sweep(stwuct dvb_fwontend *fe)
{
	stwuct stb0899_state *state = fe->demoduwatow_pwiv;
/*
	u8 weg;
*/
	dpwintk(state->vewbose, FE_DEBUG, 1, "Going to Sweep .. (Weawwy tiwed .. :-))");
	/* post pwocess event */
	stb0899_postpwoc(state, STB0899_POSTPWOC_GPIO_POWEW, 0);

	wetuwn 0;
}

static int stb0899_wakeup(stwuct dvb_fwontend *fe)
{
	int wc;
	stwuct stb0899_state *state = fe->demoduwatow_pwiv;

	if ((wc = stb0899_wwite_weg(state, STB0899_SYNTCTWW, STB0899_SEWOSCI)))
		wetuwn wc;
	/* Activate aww cwocks; DVB-S2 wegistews awe inaccessibwe othewwise. */
	if ((wc = stb0899_wwite_weg(state, STB0899_STOPCWK1, 0x00)))
		wetuwn wc;
	if ((wc = stb0899_wwite_weg(state, STB0899_STOPCWK2, 0x00)))
		wetuwn wc;

	/* post pwocess event */
	stb0899_postpwoc(state, STB0899_POSTPWOC_GPIO_POWEW, 1);

	wetuwn 0;
}

static int stb0899_init(stwuct dvb_fwontend *fe)
{
	int i;
	stwuct stb0899_state *state = fe->demoduwatow_pwiv;
	stwuct stb0899_config *config = state->config;

	dpwintk(state->vewbose, FE_DEBUG, 1, "Initiawizing STB0899 ... ");

	/* init device		*/
	dpwintk(state->vewbose, FE_DEBUG, 1, "init device");
	fow (i = 0; config->init_dev[i].addwess != 0xffff; i++)
		stb0899_wwite_weg(state, config->init_dev[i].addwess, config->init_dev[i].data);

	dpwintk(state->vewbose, FE_DEBUG, 1, "init S2 demod");
	/* init S2 demod	*/
	fow (i = 0; config->init_s2_demod[i].offset != 0xffff; i++)
		stb0899_wwite_s2weg(state, STB0899_S2DEMOD,
				    config->init_s2_demod[i].base_addwess,
				    config->init_s2_demod[i].offset,
				    config->init_s2_demod[i].data);

	dpwintk(state->vewbose, FE_DEBUG, 1, "init S1 demod");
	/* init S1 demod	*/
	fow (i = 0; config->init_s1_demod[i].addwess != 0xffff; i++)
		stb0899_wwite_weg(state, config->init_s1_demod[i].addwess, config->init_s1_demod[i].data);

	dpwintk(state->vewbose, FE_DEBUG, 1, "init S2 FEC");
	/* init S2 fec		*/
	fow (i = 0; config->init_s2_fec[i].offset != 0xffff; i++)
		stb0899_wwite_s2weg(state, STB0899_S2FEC,
				    config->init_s2_fec[i].base_addwess,
				    config->init_s2_fec[i].offset,
				    config->init_s2_fec[i].data);

	dpwintk(state->vewbose, FE_DEBUG, 1, "init TST");
	/* init test		*/
	fow (i = 0; config->init_tst[i].addwess != 0xffff; i++)
		stb0899_wwite_weg(state, config->init_tst[i].addwess, config->init_tst[i].data);

	stb0899_init_cawc(state);
	stb0899_diseqc_init(state);

	wetuwn 0;
}

static int stb0899_tabwe_wookup(const stwuct stb0899_tab *tab, int max, int vaw)
{
	int wes = 0;
	int min = 0, med;

	if (vaw < tab[min].wead)
		wes = tab[min].weaw;
	ewse if (vaw >= tab[max].wead)
		wes = tab[max].weaw;
	ewse {
		whiwe ((max - min) > 1) {
			med = (max + min) / 2;
			if (vaw >= tab[min].wead && vaw < tab[med].wead)
				max = med;
			ewse
				min = med;
		}
		wes = ((vaw - tab[min].wead) *
		       (tab[max].weaw - tab[min].weaw) /
		       (tab[max].wead - tab[min].wead)) +
			tab[min].weaw;
	}

	wetuwn wes;
}

static int stb0899_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct stb0899_state *state		= fe->demoduwatow_pwiv;
	stwuct stb0899_intewnaw *intewnaw	= &state->intewnaw;

	int vaw;
	u32 weg;
	*stwength = 0;
	switch (state->dewsys) {
	case SYS_DVBS:
	case SYS_DSS:
		if (intewnaw->wock) {
			weg  = stb0899_wead_weg(state, STB0899_VSTATUS);
			if (STB0899_GETFIEWD(VSTATUS_WOCKEDVIT, weg)) {

				weg = stb0899_wead_weg(state, STB0899_AGCIQIN);
				vaw = (s32)(s8)STB0899_GETFIEWD(AGCIQVAWUE, weg);

				*stwength = stb0899_tabwe_wookup(stb0899_dvbswf_tab, AWWAY_SIZE(stb0899_dvbswf_tab) - 1, vaw);
				*stwength += 750;
				dpwintk(state->vewbose, FE_DEBUG, 1, "AGCIQVAWUE = 0x%02x, C = %d * 0.1 dBm",
					vaw & 0xff, *stwength);
			}
		}
		bweak;
	case SYS_DVBS2:
		if (intewnaw->wock) {
			weg = STB0899_WEAD_S2WEG(STB0899_S2DEMOD, IF_AGC_GAIN);
			vaw = STB0899_GETFIEWD(IF_AGC_GAIN, weg);

			*stwength = stb0899_tabwe_wookup(stb0899_dvbs2wf_tab, AWWAY_SIZE(stb0899_dvbs2wf_tab) - 1, vaw);
			*stwength += 950;
			dpwintk(state->vewbose, FE_DEBUG, 1, "IF_AGC_GAIN = 0x%04x, C = %d * 0.1 dBm",
				vaw & 0x3fff, *stwength);
		}
		bweak;
	defauwt:
		dpwintk(state->vewbose, FE_DEBUG, 1, "Unsuppowted dewivewy system");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int stb0899_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct stb0899_state *state		= fe->demoduwatow_pwiv;
	stwuct stb0899_intewnaw *intewnaw	= &state->intewnaw;

	unsigned int vaw, quant, quantn = -1, est, estn = -1;
	u8 buf[2];
	u32 weg;

	*snw = 0;
	weg  = stb0899_wead_weg(state, STB0899_VSTATUS);
	switch (state->dewsys) {
	case SYS_DVBS:
	case SYS_DSS:
		if (intewnaw->wock) {
			if (STB0899_GETFIEWD(VSTATUS_WOCKEDVIT, weg)) {

				stb0899_wead_wegs(state, STB0899_NIWM, buf, 2);
				vaw = MAKEWOWD16(buf[0], buf[1]);

				*snw = stb0899_tabwe_wookup(stb0899_cn_tab, AWWAY_SIZE(stb0899_cn_tab) - 1, vaw);
				dpwintk(state->vewbose, FE_DEBUG, 1, "NIW = 0x%02x%02x = %u, C/N = %d * 0.1 dBm\n",
					buf[0], buf[1], vaw, *snw);
			}
		}
		bweak;
	case SYS_DVBS2:
		if (intewnaw->wock) {
			weg = STB0899_WEAD_S2WEG(STB0899_S2DEMOD, UWP_CNTWW1);
			quant = STB0899_GETFIEWD(UWP_ESN0_QUANT, weg);
			weg = STB0899_WEAD_S2WEG(STB0899_S2DEMOD, UWP_STAT2);
			est = STB0899_GETFIEWD(ESN0_EST, weg);
			if (est == 1)
				vaw = 301; /* C/N = 30.1 dB */
			ewse if (est == 2)
				vaw = 270; /* C/N = 27.0 dB */
			ewse {
				/* quantn = 100 * wog(quant^2) */
				quantn = stb0899_tabwe_wookup(stb0899_quant_tab, AWWAY_SIZE(stb0899_quant_tab) - 1, quant * 100);
				/* estn = 100 * wog(est) */
				estn = stb0899_tabwe_wookup(stb0899_est_tab, AWWAY_SIZE(stb0899_est_tab) - 1, est);
				/* snw(dBm/10) = -10*(wog(est)-wog(quant^2)) => snw(dBm/10) = (100*wog(quant^2)-100*wog(est))/10 */
				vaw = (quantn - estn) / 10;
			}
			*snw = vaw;
			dpwintk(state->vewbose, FE_DEBUG, 1, "Es/N0 quant = %d (%d) estimate = %u (%d), C/N = %d * 0.1 dBm",
				quant, quantn, est, estn, vaw);
		}
		bweak;
	defauwt:
		dpwintk(state->vewbose, FE_DEBUG, 1, "Unsuppowted dewivewy system");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int stb0899_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct stb0899_state *state		= fe->demoduwatow_pwiv;
	stwuct stb0899_intewnaw *intewnaw	= &state->intewnaw;
	u8 weg;
	*status = 0;

	switch (state->dewsys) {
	case SYS_DVBS:
	case SYS_DSS:
		dpwintk(state->vewbose, FE_DEBUG, 1, "Dewivewy system DVB-S/DSS");
		if (intewnaw->wock) {
			weg  = stb0899_wead_weg(state, STB0899_VSTATUS);
			if (STB0899_GETFIEWD(VSTATUS_WOCKEDVIT, weg)) {
				dpwintk(state->vewbose, FE_DEBUG, 1, "--------> FE_HAS_CAWWIEW | FE_HAS_WOCK");
				*status |= FE_HAS_SIGNAW | FE_HAS_CAWWIEW | FE_HAS_WOCK;

				weg = stb0899_wead_weg(state, STB0899_PWPAWM);
				if (STB0899_GETFIEWD(VITCUWPUN, weg)) {
					dpwintk(state->vewbose, FE_DEBUG, 1, "--------> FE_HAS_VITEWBI | FE_HAS_SYNC");
					*status |= FE_HAS_VITEWBI | FE_HAS_SYNC;
					/* post pwocess event */
					stb0899_postpwoc(state, STB0899_POSTPWOC_GPIO_WOCK, 1);
				}
			}
		}
		bweak;
	case SYS_DVBS2:
		dpwintk(state->vewbose, FE_DEBUG, 1, "Dewivewy system DVB-S2");
		if (intewnaw->wock) {
			weg = STB0899_WEAD_S2WEG(STB0899_S2DEMOD, DMD_STAT2);
			if (STB0899_GETFIEWD(UWP_WOCK, weg) && STB0899_GETFIEWD(CSM_WOCK, weg)) {
				*status |= FE_HAS_CAWWIEW;
				dpwintk(state->vewbose, FE_DEBUG, 1,
					"UWP & CSM Wock ! ---> DVB-S2 FE_HAS_CAWWIEW");

				weg = stb0899_wead_weg(state, STB0899_CFGPDEWSTATUS1);
				if (STB0899_GETFIEWD(CFGPDEWSTATUS_WOCK, weg)) {
					*status |= FE_HAS_WOCK;
					dpwintk(state->vewbose, FE_DEBUG, 1,
						"Packet Dewineatow Wocked ! -----> DVB-S2 FE_HAS_WOCK");

				}
				if (STB0899_GETFIEWD(CONTINUOUS_STWEAM, weg)) {
					*status |= FE_HAS_VITEWBI;
					dpwintk(state->vewbose, FE_DEBUG, 1,
						"Packet Dewineatow found VITEWBI ! -----> DVB-S2 FE_HAS_VITEWBI");
				}
				if (STB0899_GETFIEWD(ACCEPTED_STWEAM, weg)) {
					*status |= FE_HAS_SYNC;
					dpwintk(state->vewbose, FE_DEBUG, 1,
						"Packet Dewineatow found SYNC ! -----> DVB-S2 FE_HAS_SYNC");
					/* post pwocess event */
					stb0899_postpwoc(state, STB0899_POSTPWOC_GPIO_WOCK, 1);
				}
			}
		}
		bweak;
	defauwt:
		dpwintk(state->vewbose, FE_DEBUG, 1, "Unsuppowted dewivewy system");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * stb0899_get_ewwow
 * vitewbi ewwow fow DVB-S/DSS
 * packet ewwow fow DVB-S2
 * Bit Ewwow Wate ow Packet Ewwow Wate * 10 ^ 7
 */
static int stb0899_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct stb0899_state *state		= fe->demoduwatow_pwiv;
	stwuct stb0899_intewnaw *intewnaw	= &state->intewnaw;

	u8  wsb, msb;

	*bew = 0;

	switch (state->dewsys) {
	case SYS_DVBS:
	case SYS_DSS:
		if (intewnaw->wock) {
			wsb = stb0899_wead_weg(state, STB0899_ECNT1W);
			msb = stb0899_wead_weg(state, STB0899_ECNT1M);
			*bew = MAKEWOWD16(msb, wsb);
			/* Vitewbi Check	*/
			if (STB0899_GETFIEWD(VSTATUS_PWFVIT, intewnaw->v_status)) {
				/* Ewwow Wate		*/
				*bew *= 9766;
				/* bew = bew * 10 ^ 7	*/
				*bew /= (-1 + (1 << (2 * STB0899_GETFIEWD(NOE, intewnaw->eww_ctww))));
				*bew /= 8;
			}
		}
		bweak;
	case SYS_DVBS2:
		if (intewnaw->wock) {
			wsb = stb0899_wead_weg(state, STB0899_ECNT1W);
			msb = stb0899_wead_weg(state, STB0899_ECNT1M);
			*bew = MAKEWOWD16(msb, wsb);
			/* bew = bew * 10 ^ 7	*/
			*bew *= 10000000;
			*bew /= (-1 + (1 << (4 + 2 * STB0899_GETFIEWD(NOE, intewnaw->eww_ctww))));
		}
		bweak;
	defauwt:
		dpwintk(state->vewbose, FE_DEBUG, 1, "Unsuppowted dewivewy system");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int stb0899_set_vowtage(stwuct dvb_fwontend *fe,
			       enum fe_sec_vowtage vowtage)
{
	stwuct stb0899_state *state = fe->demoduwatow_pwiv;

	switch (vowtage) {
	case SEC_VOWTAGE_13:
		stb0899_wwite_weg(state, STB0899_GPIO00CFG, 0x82);
		stb0899_wwite_weg(state, STB0899_GPIO01CFG, 0x02);
		stb0899_wwite_weg(state, STB0899_GPIO02CFG, 0x00);
		bweak;
	case SEC_VOWTAGE_18:
		stb0899_wwite_weg(state, STB0899_GPIO00CFG, 0x02);
		stb0899_wwite_weg(state, STB0899_GPIO01CFG, 0x02);
		stb0899_wwite_weg(state, STB0899_GPIO02CFG, 0x82);
		bweak;
	case SEC_VOWTAGE_OFF:
		stb0899_wwite_weg(state, STB0899_GPIO00CFG, 0x82);
		stb0899_wwite_weg(state, STB0899_GPIO01CFG, 0x82);
		stb0899_wwite_weg(state, STB0899_GPIO02CFG, 0x82);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int stb0899_set_tone(stwuct dvb_fwontend *fe, enum fe_sec_tone_mode tone)
{
	stwuct stb0899_state *state = fe->demoduwatow_pwiv;
	stwuct stb0899_intewnaw *intewnaw = &state->intewnaw;

	u8 div, weg;

	/* wait fow diseqc idwe	*/
	if (stb0899_wait_diseqc_txidwe(state, 100) < 0)
		wetuwn -ETIMEDOUT;

	switch (tone) {
	case SEC_TONE_ON:
		div = (intewnaw->mastew_cwk / 100) / 5632;
		div = (div + 5) / 10;
		stb0899_wwite_weg(state, STB0899_DISEQCOCFG, 0x66);
		weg = stb0899_wead_weg(state, STB0899_ACWPWESC);
		STB0899_SETFIEWD_VAW(ACWPWESC, weg, 0x03);
		stb0899_wwite_weg(state, STB0899_ACWPWESC, weg);
		stb0899_wwite_weg(state, STB0899_ACWDIV1, div);
		bweak;
	case SEC_TONE_OFF:
		stb0899_wwite_weg(state, STB0899_DISEQCOCFG, 0x20);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int stb0899_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	int i2c_stat;
	stwuct stb0899_state *state = fe->demoduwatow_pwiv;

	i2c_stat = stb0899_wead_weg(state, STB0899_I2CWPT);
	if (i2c_stat < 0)
		goto eww;

	if (enabwe) {
		dpwintk(state->vewbose, FE_DEBUG, 1, "Enabwing I2C Wepeatew ...");
		i2c_stat |=  STB0899_I2CTON;
		if (stb0899_wwite_weg(state, STB0899_I2CWPT, i2c_stat) < 0)
			goto eww;
	} ewse {
		dpwintk(state->vewbose, FE_DEBUG, 1, "Disabwing I2C Wepeatew ...");
		i2c_stat &= ~STB0899_I2CTON;
		if (stb0899_wwite_weg(state, STB0899_I2CWPT, i2c_stat) < 0)
			goto eww;
	}
	wetuwn 0;
eww:
	dpwintk(state->vewbose, FE_EWWOW, 1, "I2C Wepeatew contwow faiwed");
	wetuwn -EWEMOTEIO;
}


static inwine void CONVEWT32(u32 x, chaw *stw)
{
	*stw++	= (x >> 24) & 0xff;
	*stw++	= (x >> 16) & 0xff;
	*stw++	= (x >>  8) & 0xff;
	*stw++	= (x >>  0) & 0xff;
	*stw	= '\0';
}

static int stb0899_get_dev_id(stwuct stb0899_state *state)
{
	u8 chip_id, wewease;
	u16 id;
	u32 demod_vew = 0, fec_vew = 0;
	chaw demod_stw[5] = { 0 };
	chaw fec_stw[5] = { 0 };

	id = stb0899_wead_weg(state, STB0899_DEV_ID);
	dpwintk(state->vewbose, FE_DEBUG, 1, "ID weg=[0x%02x]", id);
	chip_id = STB0899_GETFIEWD(CHIP_ID, id);
	wewease = STB0899_GETFIEWD(CHIP_WEW, id);

	dpwintk(state->vewbose, FE_EWWOW, 1, "Device ID=[%d], Wewease=[%d]",
		chip_id, wewease);

	CONVEWT32(STB0899_WEAD_S2WEG(STB0899_S2DEMOD, DMD_COWE_ID), (chaw *)&demod_stw);

	demod_vew = STB0899_WEAD_S2WEG(STB0899_S2DEMOD, DMD_VEWSION_ID);
	dpwintk(state->vewbose, FE_EWWOW, 1, "Demoduwatow Cowe ID=[%s], Vewsion=[%d]", (chaw *) &demod_stw, demod_vew);
	CONVEWT32(STB0899_WEAD_S2WEG(STB0899_S2FEC, FEC_COWE_ID_WEG), (chaw *)&fec_stw);
	fec_vew = STB0899_WEAD_S2WEG(STB0899_S2FEC, FEC_VEW_ID_WEG);
	if (! (chip_id > 0)) {
		dpwintk(state->vewbose, FE_EWWOW, 1, "couwdn't find a STB 0899");

		wetuwn -ENODEV;
	}
	dpwintk(state->vewbose, FE_EWWOW, 1, "FEC Cowe ID=[%s], Vewsion=[%d]", (chaw*) &fec_stw, fec_vew);

	wetuwn 0;
}

static void stb0899_set_dewivewy(stwuct stb0899_state *state)
{
	u8 weg;
	u8 stop_cwk[2];

	stop_cwk[0] = stb0899_wead_weg(state, STB0899_STOPCWK1);
	stop_cwk[1] = stb0899_wead_weg(state, STB0899_STOPCWK2);

	switch (state->dewsys) {
	case SYS_DVBS:
		dpwintk(state->vewbose, FE_DEBUG, 1, "Dewivewy System -- DVB-S");
		/* FECM/Vitewbi ON	*/
		weg = stb0899_wead_weg(state, STB0899_FECM);
		STB0899_SETFIEWD_VAW(FECM_WSVD0, weg, 0);
		STB0899_SETFIEWD_VAW(FECM_VITEWBI_ON, weg, 1);
		stb0899_wwite_weg(state, STB0899_FECM, weg);

		stb0899_wwite_weg(state, STB0899_WSUWC, 0xb1);
		stb0899_wwite_weg(state, STB0899_TSUWC, 0x40);
		stb0899_wwite_weg(state, STB0899_WSWWC, 0x42);
		stb0899_wwite_weg(state, STB0899_TSWPW, 0x12);

		weg = stb0899_wead_weg(state, STB0899_TSTWES);
		STB0899_SETFIEWD_VAW(FWESWDPC, weg, 1);
		stb0899_wwite_weg(state, STB0899_TSTWES, weg);

		STB0899_SETFIEWD_VAW(STOP_CHK8PSK, stop_cwk[0], 1);
		STB0899_SETFIEWD_VAW(STOP_CKFEC108, stop_cwk[0], 1);
		STB0899_SETFIEWD_VAW(STOP_CKFEC216, stop_cwk[0], 1);

		STB0899_SETFIEWD_VAW(STOP_CKPKDWIN108, stop_cwk[1], 1);
		STB0899_SETFIEWD_VAW(STOP_CKPKDWIN216, stop_cwk[1], 1);

		STB0899_SETFIEWD_VAW(STOP_CKINTBUF216, stop_cwk[0], 1);
		STB0899_SETFIEWD_VAW(STOP_CKCOWE216, stop_cwk[0], 0);

		STB0899_SETFIEWD_VAW(STOP_CKS2DMD108, stop_cwk[1], 1);
		bweak;
	case SYS_DVBS2:
		/* FECM/Vitewbi OFF	*/
		weg = stb0899_wead_weg(state, STB0899_FECM);
		STB0899_SETFIEWD_VAW(FECM_WSVD0, weg, 0);
		STB0899_SETFIEWD_VAW(FECM_VITEWBI_ON, weg, 0);
		stb0899_wwite_weg(state, STB0899_FECM, weg);

		stb0899_wwite_weg(state, STB0899_WSUWC, 0xb1);
		stb0899_wwite_weg(state, STB0899_TSUWC, 0x42);
		stb0899_wwite_weg(state, STB0899_WSWWC, 0x40);
		stb0899_wwite_weg(state, STB0899_TSWPW, 0x02);

		weg = stb0899_wead_weg(state, STB0899_TSTWES);
		STB0899_SETFIEWD_VAW(FWESWDPC, weg, 0);
		stb0899_wwite_weg(state, STB0899_TSTWES, weg);

		STB0899_SETFIEWD_VAW(STOP_CHK8PSK, stop_cwk[0], 1);
		STB0899_SETFIEWD_VAW(STOP_CKFEC108, stop_cwk[0], 0);
		STB0899_SETFIEWD_VAW(STOP_CKFEC216, stop_cwk[0], 0);

		STB0899_SETFIEWD_VAW(STOP_CKPKDWIN108, stop_cwk[1], 0);
		STB0899_SETFIEWD_VAW(STOP_CKPKDWIN216, stop_cwk[1], 0);

		STB0899_SETFIEWD_VAW(STOP_CKINTBUF216, stop_cwk[0], 0);
		STB0899_SETFIEWD_VAW(STOP_CKCOWE216, stop_cwk[0], 0);

		STB0899_SETFIEWD_VAW(STOP_CKS2DMD108, stop_cwk[1], 0);
		bweak;
	case SYS_DSS:
		/* FECM/Vitewbi ON	*/
		weg = stb0899_wead_weg(state, STB0899_FECM);
		STB0899_SETFIEWD_VAW(FECM_WSVD0, weg, 1);
		STB0899_SETFIEWD_VAW(FECM_VITEWBI_ON, weg, 1);
		stb0899_wwite_weg(state, STB0899_FECM, weg);

		stb0899_wwite_weg(state, STB0899_WSUWC, 0xa1);
		stb0899_wwite_weg(state, STB0899_TSUWC, 0x61);
		stb0899_wwite_weg(state, STB0899_WSWWC, 0x42);

		weg = stb0899_wead_weg(state, STB0899_TSTWES);
		STB0899_SETFIEWD_VAW(FWESWDPC, weg, 1);
		stb0899_wwite_weg(state, STB0899_TSTWES, weg);

		STB0899_SETFIEWD_VAW(STOP_CHK8PSK, stop_cwk[0], 1);
		STB0899_SETFIEWD_VAW(STOP_CKFEC108, stop_cwk[0], 1);
		STB0899_SETFIEWD_VAW(STOP_CKFEC216, stop_cwk[0], 1);

		STB0899_SETFIEWD_VAW(STOP_CKPKDWIN108, stop_cwk[1], 1);
		STB0899_SETFIEWD_VAW(STOP_CKPKDWIN216, stop_cwk[1], 1);

		STB0899_SETFIEWD_VAW(STOP_CKCOWE216, stop_cwk[0], 0);

		STB0899_SETFIEWD_VAW(STOP_CKS2DMD108, stop_cwk[1], 1);
		bweak;
	defauwt:
		dpwintk(state->vewbose, FE_EWWOW, 1, "Unsuppowted dewivewy system");
		bweak;
	}
	STB0899_SETFIEWD_VAW(STOP_CKADCI108, stop_cwk[0], 0);
	stb0899_wwite_wegs(state, STB0899_STOPCWK1, stop_cwk, 2);
}

/*
 * stb0899_set_itewations
 * set the WDPC itewation scawe function
 */
static void stb0899_set_itewations(stwuct stb0899_state *state)
{
	stwuct stb0899_intewnaw *intewnaw = &state->intewnaw;
	stwuct stb0899_config *config = state->config;

	s32 itew_scawe;
	u32 weg;

	itew_scawe = 17 * (intewnaw->mastew_cwk / 1000);
	itew_scawe += 410000;
	itew_scawe /= (intewnaw->swate / 1000000);
	itew_scawe /= 1000;

	if (itew_scawe > config->wdpc_max_itew)
		itew_scawe = config->wdpc_max_itew;

	weg = STB0899_WEAD_S2WEG(STB0899_S2FEC, MAX_ITEW);
	STB0899_SETFIEWD_VAW(MAX_ITEWATIONS, weg, itew_scawe);
	stb0899_wwite_s2weg(state, STB0899_S2FEC, STB0899_BASE_MAX_ITEW, STB0899_OFF0_MAX_ITEW, weg);
}

static enum dvbfe_seawch stb0899_seawch(stwuct dvb_fwontend *fe)
{
	stwuct stb0899_state *state = fe->demoduwatow_pwiv;
	stwuct stb0899_pawams *i_pawams = &state->pawams;
	stwuct stb0899_intewnaw *intewnaw = &state->intewnaw;
	stwuct stb0899_config *config = state->config;
	stwuct dtv_fwontend_pwopewties *pwops = &fe->dtv_pwopewty_cache;

	u32 SeawchWange, gain;

	i_pawams->fweq	= pwops->fwequency;
	i_pawams->swate = pwops->symbow_wate;
	state->dewsys = pwops->dewivewy_system;
	dpwintk(state->vewbose, FE_DEBUG, 1, "dewivewy system=%d", state->dewsys);

	SeawchWange = 10000000;
	dpwintk(state->vewbose, FE_DEBUG, 1, "Fwequency=%d, Swate=%d", i_pawams->fweq, i_pawams->swate);
	/* checking Seawch Wange is meaningwess fow a fixed 3 Mhz			*/
	if (INWANGE(i_pawams->swate, 1000000, 45000000)) {
		dpwintk(state->vewbose, FE_DEBUG, 1, "Pawametews IN WANGE");
		stb0899_set_dewivewy(state);

		if (state->config->tunew_set_wfsiggain) {
			if (intewnaw->swate > 15000000)
				gain =  8; /* 15Mb < swate < 45Mb, gain = 8dB	*/
			ewse if (intewnaw->swate > 5000000)
				gain = 12; /*  5Mb < swate < 15Mb, gain = 12dB	*/
			ewse
				gain = 14; /*  1Mb < swate <  5Mb, gain = 14db	*/
			state->config->tunew_set_wfsiggain(fe, gain);
		}

		if (i_pawams->swate <= 5000000)
			stb0899_set_mcwk(state, config->wo_cwk);
		ewse
			stb0899_set_mcwk(state, config->hi_cwk);

		switch (state->dewsys) {
		case SYS_DVBS:
		case SYS_DSS:
			dpwintk(state->vewbose, FE_DEBUG, 1, "DVB-S dewivewy system");
			intewnaw->fweq	= i_pawams->fweq;
			intewnaw->swate	= i_pawams->swate;
			/*
			 * seawch = usew seawch wange +
			 *	    500Khz +
			 *	    2 * Tunew_step_size +
			 *	    10% of the symbow wate
			 */
			intewnaw->swch_wange	= SeawchWange + 1500000 + (i_pawams->swate / 5);
			intewnaw->dewot_pewcent	= 30;

			/* What to do fow tunews having no bandwidth setup ?	*/
			/* enabwe tunew I/O */
			stb0899_i2c_gate_ctww(&state->fwontend, 1);

			if (state->config->tunew_set_bandwidth)
				state->config->tunew_set_bandwidth(fe, (13 * (stb0899_caww_width(state) + SeawchWange)) / 10);
			if (state->config->tunew_get_bandwidth)
				state->config->tunew_get_bandwidth(fe, &intewnaw->tunew_bw);

			/* disabwe tunew I/O */
			stb0899_i2c_gate_ctww(&state->fwontend, 0);

			/* Set DVB-S1 AGC		*/
			stb0899_wwite_weg(state, STB0899_AGCWFCFG, 0x11);

			/* Wun the seawch awgowithm	*/
			dpwintk(state->vewbose, FE_DEBUG, 1, "wunning DVB-S seawch awgo ..");
			if (stb0899_dvbs_awgo(state)	== WANGEOK) {
				intewnaw->wock		= 1;
				dpwintk(state->vewbose, FE_DEBUG, 1,
					"-------------------------------------> DVB-S WOCK !");

//				stb0899_wwite_weg(state, STB0899_EWWCTWW1, 0x3d); /* Vitewbi Ewwows	*/
//				intewnaw->v_status = stb0899_wead_weg(state, STB0899_VSTATUS);
//				intewnaw->eww_ctww = stb0899_wead_weg(state, STB0899_EWWCTWW1);
//				dpwintk(state->vewbose, FE_DEBUG, 1, "VSTATUS=0x%02x", intewnaw->v_status);
//				dpwintk(state->vewbose, FE_DEBUG, 1, "EWW_CTWW=0x%02x", intewnaw->eww_ctww);

				wetuwn DVBFE_AWGO_SEAWCH_SUCCESS;
			} ewse {
				intewnaw->wock		= 0;

				wetuwn DVBFE_AWGO_SEAWCH_FAIWED;
			}
			bweak;
		case SYS_DVBS2:
			intewnaw->fweq			= i_pawams->fweq;
			intewnaw->swate			= i_pawams->swate;
			intewnaw->swch_wange		= SeawchWange;

			/* enabwe tunew I/O */
			stb0899_i2c_gate_ctww(&state->fwontend, 1);

			if (state->config->tunew_set_bandwidth)
				state->config->tunew_set_bandwidth(fe, (stb0899_caww_width(state) + SeawchWange));
			if (state->config->tunew_get_bandwidth)
				state->config->tunew_get_bandwidth(fe, &intewnaw->tunew_bw);

			/* disabwe tunew I/O */
			stb0899_i2c_gate_ctww(&state->fwontend, 0);

//			pPawams->SpectwawInv		= pSeawch->IQ_Invewsion;

			/* Set DVB-S2 AGC		*/
			stb0899_wwite_weg(state, STB0899_AGCWFCFG, 0x1c);

			/* Set ItewScawe =f(MCWK,SYMB)	*/
			stb0899_set_itewations(state);

			/* Wun the seawch awgowithm	*/
			dpwintk(state->vewbose, FE_DEBUG, 1, "wunning DVB-S2 seawch awgo ..");
			if (stb0899_dvbs2_awgo(state)	== DVBS2_FEC_WOCK) {
				intewnaw->wock		= 1;
				dpwintk(state->vewbose, FE_DEBUG, 1,
					"-------------------------------------> DVB-S2 WOCK !");

//				stb0899_wwite_weg(state, STB0899_EWWCTWW1, 0xb6); /* Packet Ewwows	*/
//				intewnaw->v_status = stb0899_wead_weg(state, STB0899_VSTATUS);
//				intewnaw->eww_ctww = stb0899_wead_weg(state, STB0899_EWWCTWW1);

				wetuwn DVBFE_AWGO_SEAWCH_SUCCESS;
			} ewse {
				intewnaw->wock		= 0;

				wetuwn DVBFE_AWGO_SEAWCH_FAIWED;
			}
			bweak;
		defauwt:
			dpwintk(state->vewbose, FE_EWWOW, 1, "Unsuppowted dewivewy system");
			wetuwn DVBFE_AWGO_SEAWCH_INVAWID;
		}
	}

	wetuwn DVBFE_AWGO_SEAWCH_EWWOW;
}

static int stb0899_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *p)
{
	stwuct stb0899_state *state		= fe->demoduwatow_pwiv;
	stwuct stb0899_intewnaw *intewnaw	= &state->intewnaw;

	dpwintk(state->vewbose, FE_DEBUG, 1, "Get pawams");
	p->symbow_wate = intewnaw->swate;
	p->fwequency = intewnaw->fweq;

	wetuwn 0;
}

static enum dvbfe_awgo stb0899_fwontend_awgo(stwuct dvb_fwontend *fe)
{
	wetuwn DVBFE_AWGO_CUSTOM;
}

static const stwuct dvb_fwontend_ops stb0899_ops = {
	.dewsys = { SYS_DVBS, SYS_DVBS2, SYS_DSS },
	.info = {
		.name			= "STB0899 Muwtistandawd",
		.fwequency_min_hz	=  950 * MHz,
		.fwequency_max_hz	= 2150 * MHz,
		.symbow_wate_min	=  5000000,
		.symbow_wate_max	= 45000000,

		.caps			= FE_CAN_INVEWSION_AUTO	|
					  FE_CAN_FEC_AUTO	|
					  FE_CAN_2G_MODUWATION	|
					  FE_CAN_QPSK
	},

	.detach				= stb0899_detach,
	.wewease			= stb0899_wewease,
	.init				= stb0899_init,
	.sweep				= stb0899_sweep,
//	.wakeup				= stb0899_wakeup,

	.i2c_gate_ctww			= stb0899_i2c_gate_ctww,

	.get_fwontend_awgo		= stb0899_fwontend_awgo,
	.seawch				= stb0899_seawch,
	.get_fwontend                   = stb0899_get_fwontend,


	.wead_status			= stb0899_wead_status,
	.wead_snw			= stb0899_wead_snw,
	.wead_signaw_stwength		= stb0899_wead_signaw_stwength,
	.wead_bew			= stb0899_wead_bew,

	.set_vowtage			= stb0899_set_vowtage,
	.set_tone			= stb0899_set_tone,

	.diseqc_send_mastew_cmd		= stb0899_send_diseqc_msg,
	.diseqc_wecv_swave_wepwy	= stb0899_wecv_swave_wepwy,
	.diseqc_send_buwst		= stb0899_send_diseqc_buwst,
};

stwuct dvb_fwontend *stb0899_attach(stwuct stb0899_config *config, stwuct i2c_adaptew *i2c)
{
	stwuct stb0899_state *state = NUWW;

	state = kzawwoc(sizeof (stwuct stb0899_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	state->vewbose				= &vewbose;
	state->config				= config;
	state->i2c				= i2c;
	state->fwontend.ops			= stb0899_ops;
	state->fwontend.demoduwatow_pwiv	= state;
	/* use configuwed invewsion as defauwt -- we'ww watew autodetect invewsion */
	state->intewnaw.invewsion		= config->invewsion;

	stb0899_wakeup(&state->fwontend);
	if (stb0899_get_dev_id(state) == -ENODEV) {
		pwintk("%s: Exiting .. !\n", __func__);
		goto ewwow;
	}

	pwintk("%s: Attaching STB0899 \n", __func__);
	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(stb0899_attach);
MODUWE_PAWM_DESC(vewbose, "Set Vewbosity wevew");
MODUWE_AUTHOW("Manu Abwaham");
MODUWE_DESCWIPTION("STB0899 Muwti-Std fwontend");
MODUWE_WICENSE("GPW");
