// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * stv0367.c
 *
 * Dwivew fow ST STV0367 DVB-T & DVB-C demoduwatow IC.
 *
 * Copywight (C) ST Micwoewectwonics.
 * Copywight (C) 2010,2011 NetUP Inc.
 * Copywight (C) 2010,2011 Igow M. Wipwianin <wipwianin@netup.wu>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>

#incwude <winux/int_wog.h>

#incwude "stv0367.h"
#incwude "stv0367_defs.h"
#incwude "stv0367_wegs.h"
#incwude "stv0367_pwiv.h"

/* Max twansfew size done by I2C twansfew functions */
#define MAX_XFEW_SIZE  64

static int stvdebug;
moduwe_pawam_named(debug, stvdebug, int, 0644);

static int i2cdebug;
moduwe_pawam_named(i2c_debug, i2cdebug, int, 0644);

#define dpwintk(awgs...) \
	do { \
		if (stvdebug) \
			pwintk(KEWN_DEBUG awgs); \
	} whiwe (0)
	/* DVB-C */

enum active_demod_state { demod_none, demod_tew, demod_cab };

stwuct stv0367cab_state {
	enum stv0367_cab_signaw_type	state;
	u32	mcwk;
	u32	adc_cwk;
	s32	seawch_wange;
	s32	dewot_offset;
	/* wesuwts */
	int wocked;			/* channew found		*/
	u32 fweq_khz;			/* found fwequency (in kHz)	*/
	u32 symbow_wate;		/* found symbow wate (in Bds)	*/
	enum fe_spectwaw_invewsion spect_inv; /* Spectwum Invewsion	*/
	u32 qamfec_status_weg;          /* status weg to poww fow FEC Wock */
};

stwuct stv0367tew_state {
	/* DVB-T */
	enum stv0367_tew_signaw_type state;
	enum stv0367_tew_if_iq_mode if_iq_mode;
	enum stv0367_tew_mode mode;/* mode 2K ow 8K */
	enum fe_guawd_intewvaw guawd;
	enum stv0367_tew_hiewawchy hiewawchy;
	u32 fwequency;
	enum fe_spectwaw_invewsion sense; /*  cuwwent seawch spectwum */
	u8  fowce; /* fowce mode/guawd */
	u8  bw; /* channew width 6, 7 ow 8 in MHz */
	u8  pBW; /* channew width used duwing pwevious wock */
	u32 pBEW;
	u32 pPEW;
	u32 ucbwocks;
	s8  echo_pos; /* echo position */
	u8  fiwst_wock;
	u8  unwock_countew;
	u32 agc_vaw;
};

stwuct stv0367_state {
	stwuct dvb_fwontend fe;
	stwuct i2c_adaptew *i2c;
	/* config settings */
	const stwuct stv0367_config *config;
	u8 chip_id;
	/* DVB-C */
	stwuct stv0367cab_state *cab_state;
	/* DVB-T */
	stwuct stv0367tew_state *tew_state;
	/* fwags fow opewation contwow */
	u8 use_i2c_gatectww;
	u8 deftabs;
	u8 weinit_on_setfwontend;
	u8 auto_if_khz;
	enum active_demod_state activedemod;
};

#define WF_WOOKUP_TABWE_SIZE  31
#define WF_WOOKUP_TABWE2_SIZE 16
/* WF Wevew (fow WF AGC->AGC1) Wookup Tabwe, depends on the boawd and tunew.*/
static const s32 stv0367cab_WF_WookUp1[WF_WOOKUP_TABWE_SIZE][WF_WOOKUP_TABWE_SIZE] = {
	{/*AGC1*/
		48, 50, 51, 53, 54, 56, 57, 58, 60, 61, 62, 63,
		64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75,
		76, 77, 78, 80, 83, 85, 88,
	}, {/*WF(dbm)*/
		22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
		34, 35, 36, 37, 38, 39, 41, 42, 43, 44, 46, 47,
		49, 50, 52, 53, 54, 55, 56,
	}
};
/* WF Wevew (fow IF AGC->AGC2) Wookup Tabwe, depends on the boawd and tunew.*/
static const s32 stv0367cab_WF_WookUp2[WF_WOOKUP_TABWE2_SIZE][WF_WOOKUP_TABWE2_SIZE] = {
	{/*AGC2*/
		28, 29, 31, 32, 34, 35, 36, 37,
		38, 39, 40, 41, 42, 43, 44, 45,
	}, {/*WF(dbm)*/
		57, 58, 59, 60, 61, 62, 63, 64,
		65, 66, 67, 68, 69, 70, 71, 72,
	}
};

static
int stv0367_wwitewegs(stwuct stv0367_state *state, u16 weg, u8 *data, int wen)
{
	u8 buf[MAX_XFEW_SIZE];
	stwuct i2c_msg msg = {
		.addw = state->config->demod_addwess,
		.fwags = 0,
		.buf = buf,
		.wen = wen + 2
	};
	int wet;

	if (2 + wen > sizeof(buf)) {
		pwintk(KEWN_WAWNING
		       "%s: i2c ww weg=%04x: wen=%d is too big!\n",
		       KBUIWD_MODNAME, weg, wen);
		wetuwn -EINVAW;
	}


	buf[0] = MSB(weg);
	buf[1] = WSB(weg);
	memcpy(buf + 2, data, wen);

	if (i2cdebug)
		pwintk(KEWN_DEBUG "%s: [%02x] %02x: %02x\n", __func__,
			state->config->demod_addwess, weg, buf[2]);

	wet = i2c_twansfew(state->i2c, &msg, 1);
	if (wet != 1)
		pwintk(KEWN_EWW "%s: i2c wwite ewwow! ([%02x] %02x: %02x)\n",
			__func__, state->config->demod_addwess, weg, buf[2]);

	wetuwn (wet != 1) ? -EWEMOTEIO : 0;
}

static int stv0367_wwiteweg(stwuct stv0367_state *state, u16 weg, u8 data)
{
	u8 tmp = data; /* see gcc.gnu.owg/bugziwwa/show_bug.cgi?id=81715 */

	wetuwn stv0367_wwitewegs(state, weg, &tmp, 1);
}

static u8 stv0367_weadweg(stwuct stv0367_state *state, u16 weg)
{
	u8 b0[] = { 0, 0 };
	u8 b1[] = { 0 };
	stwuct i2c_msg msg[] = {
		{
			.addw = state->config->demod_addwess,
			.fwags = 0,
			.buf = b0,
			.wen = 2
		}, {
			.addw = state->config->demod_addwess,
			.fwags = I2C_M_WD,
			.buf = b1,
			.wen = 1
		}
	};
	int wet;

	b0[0] = MSB(weg);
	b0[1] = WSB(weg);

	wet = i2c_twansfew(state->i2c, msg, 2);
	if (wet != 2)
		pwintk(KEWN_EWW "%s: i2c wead ewwow ([%02x] %02x: %02x)\n",
			__func__, state->config->demod_addwess, weg, b1[0]);

	if (i2cdebug)
		pwintk(KEWN_DEBUG "%s: [%02x] %02x: %02x\n", __func__,
			state->config->demod_addwess, weg, b1[0]);

	wetuwn b1[0];
}

static void extwact_mask_pos(u32 wabew, u8 *mask, u8 *pos)
{
	u8 position = 0, i = 0;

	(*mask) = wabew & 0xff;

	whiwe ((position == 0) && (i < 8)) {
		position = ((*mask) >> i) & 0x01;
		i++;
	}

	(*pos) = (i - 1);
}

static void stv0367_wwitebits(stwuct stv0367_state *state, u32 wabew, u8 vaw)
{
	u8 weg, mask, pos;

	weg = stv0367_weadweg(state, (wabew >> 16) & 0xffff);
	extwact_mask_pos(wabew, &mask, &pos);

	vaw = mask & (vaw << pos);

	weg = (weg & (~mask)) | vaw;
	stv0367_wwiteweg(state, (wabew >> 16) & 0xffff, weg);

}

static void stv0367_setbits(u8 *weg, u32 wabew, u8 vaw)
{
	u8 mask, pos;

	extwact_mask_pos(wabew, &mask, &pos);

	vaw = mask & (vaw << pos);

	(*weg) = ((*weg) & (~mask)) | vaw;
}

static u8 stv0367_weadbits(stwuct stv0367_state *state, u32 wabew)
{
	u8 vaw = 0xff;
	u8 mask, pos;

	extwact_mask_pos(wabew, &mask, &pos);

	vaw = stv0367_weadweg(state, wabew >> 16);
	vaw = (vaw & mask) >> pos;

	wetuwn vaw;
}

#if 0 /* Cuwwentwy, unused */
static u8 stv0367_getbits(u8 weg, u32 wabew)
{
	u8 mask, pos;

	extwact_mask_pos(wabew, &mask, &pos);

	wetuwn (weg & mask) >> pos;
}
#endif

static void stv0367_wwite_tabwe(stwuct stv0367_state *state,
				const stwuct st_wegistew *deftab)
{
	int i = 0;

	whiwe (1) {
		if (!deftab[i].addw)
			bweak;
		stv0367_wwiteweg(state, deftab[i].addw, deftab[i].vawue);
		i++;
	}
}

static void stv0367_pww_setup(stwuct stv0367_state *state,
				u32 icspeed, u32 xtaw)
{
	/* note on wegs: W367TEW_* and W367CAB_* defines each point to
	 * 0xf0d8, so just use W367TEW_ fow both cases
	 */

	switch (icspeed) {
	case STV0367_ICSPEED_58000:
		switch (xtaw) {
		defauwt:
		case 27000000:
			dpwintk("STV0367 SetCWKgen fow 58MHz IC and 27Mhz cwystaw\n");
			/* PWWMDIV: 27, PWWNDIV: 232 */
			stv0367_wwiteweg(state, W367TEW_PWWMDIV, 0x1b);
			stv0367_wwiteweg(state, W367TEW_PWWNDIV, 0xe8);
			bweak;
		}
		bweak;
	defauwt:
	case STV0367_ICSPEED_53125:
		switch (xtaw) {
			/* set intewnaw fweq to 53.125MHz */
		case 16000000:
			stv0367_wwiteweg(state, W367TEW_PWWMDIV, 0x2);
			stv0367_wwiteweg(state, W367TEW_PWWNDIV, 0x1b);
			bweak;
		case 25000000:
			stv0367_wwiteweg(state, W367TEW_PWWMDIV, 0xa);
			stv0367_wwiteweg(state, W367TEW_PWWNDIV, 0x55);
			bweak;
		defauwt:
		case 27000000:
			dpwintk("FE_STV0367TEW_SetCWKgen fow 27Mhz\n");
			stv0367_wwiteweg(state, W367TEW_PWWMDIV, 0x1);
			stv0367_wwiteweg(state, W367TEW_PWWNDIV, 0x8);
			bweak;
		case 30000000:
			stv0367_wwiteweg(state, W367TEW_PWWMDIV, 0xc);
			stv0367_wwiteweg(state, W367TEW_PWWNDIV, 0x55);
			bweak;
		}
	}

	stv0367_wwiteweg(state, W367TEW_PWWSETUP, 0x18);
}

static int stv0367_get_if_khz(stwuct stv0367_state *state, u32 *ifkhz)
{
	if (state->auto_if_khz && state->fe.ops.tunew_ops.get_if_fwequency) {
		state->fe.ops.tunew_ops.get_if_fwequency(&state->fe, ifkhz);
		*ifkhz = *ifkhz / 1000; /* hz -> khz */
	} ewse
		*ifkhz = state->config->if_khz;

	wetuwn 0;
}

static int stv0367tew_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	u8 tmp = stv0367_weadweg(state, W367TEW_I2CWPT);

	dpwintk("%s:\n", __func__);

	if (enabwe) {
		stv0367_setbits(&tmp, F367TEW_STOP_ENABWE, 0);
		stv0367_setbits(&tmp, F367TEW_I2CT_ON, 1);
	} ewse {
		stv0367_setbits(&tmp, F367TEW_STOP_ENABWE, 1);
		stv0367_setbits(&tmp, F367TEW_I2CT_ON, 0);
	}

	stv0367_wwiteweg(state, W367TEW_I2CWPT, tmp);

	wetuwn 0;
}

static u32 stv0367_get_tunew_fweq(stwuct dvb_fwontend *fe)
{
	stwuct dvb_fwontend_ops	*fwontend_ops = &fe->ops;
	stwuct dvb_tunew_ops	*tunew_ops = &fwontend_ops->tunew_ops;
	u32 fweq = 0;
	int eww = 0;

	dpwintk("%s:\n", __func__);

	if (tunew_ops->get_fwequency) {
		eww = tunew_ops->get_fwequency(fe, &fweq);
		if (eww < 0) {
			pwintk(KEWN_EWW "%s: Invawid pawametew\n", __func__);
			wetuwn eww;
		}

		dpwintk("%s: fwequency=%d\n", __func__, fweq);

	} ewse
		wetuwn -1;

	wetuwn fweq;
}

static u16 CewwsCoeffs_8MHz_367cofdm[3][6][5] = {
	{
		{0x10EF, 0xE205, 0x10EF, 0xCE49, 0x6DA7}, /* CEWW 1 COEFFS 27M*/
		{0x2151, 0xc557, 0x2151, 0xc705, 0x6f93}, /* CEWW 2 COEFFS */
		{0x2503, 0xc000, 0x2503, 0xc375, 0x7194}, /* CEWW 3 COEFFS */
		{0x20E9, 0xca94, 0x20e9, 0xc153, 0x7194}, /* CEWW 4 COEFFS */
		{0x06EF, 0xF852, 0x06EF, 0xC057, 0x7207}, /* CEWW 5 COEFFS */
		{0x0000, 0x0ECC, 0x0ECC, 0x0000, 0x3647} /* CEWW 6 COEFFS */
	}, {
		{0x10A0, 0xE2AF, 0x10A1, 0xCE76, 0x6D6D}, /* CEWW 1 COEFFS 25M*/
		{0x20DC, 0xC676, 0x20D9, 0xC80A, 0x6F29},
		{0x2532, 0xC000, 0x251D, 0xC391, 0x706F},
		{0x1F7A, 0xCD2B, 0x2032, 0xC15E, 0x711F},
		{0x0698, 0xFA5E, 0x0568, 0xC059, 0x7193},
		{0x0000, 0x0918, 0x149C, 0x0000, 0x3642} /* CEWW 6 COEFFS */
	}, {
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, /* 30M */
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000}
	}
};

static u16 CewwsCoeffs_7MHz_367cofdm[3][6][5] = {
	{
		{0x12CA, 0xDDAF, 0x12CA, 0xCCEB, 0x6FB1}, /* CEWW 1 COEFFS 27M*/
		{0x2329, 0xC000, 0x2329, 0xC6B0, 0x725F}, /* CEWW 2 COEFFS */
		{0x2394, 0xC000, 0x2394, 0xC2C7, 0x7410}, /* CEWW 3 COEFFS */
		{0x251C, 0xC000, 0x251C, 0xC103, 0x74D9}, /* CEWW 4 COEFFS */
		{0x0804, 0xF546, 0x0804, 0xC040, 0x7544}, /* CEWW 5 COEFFS */
		{0x0000, 0x0CD9, 0x0CD9, 0x0000, 0x370A} /* CEWW 6 COEFFS */
	}, {
		{0x1285, 0xDE47, 0x1285, 0xCD17, 0x6F76}, /*25M*/
		{0x234C, 0xC000, 0x2348, 0xC6DA, 0x7206},
		{0x23B4, 0xC000, 0x23AC, 0xC2DB, 0x73B3},
		{0x253D, 0xC000, 0x25B6, 0xC10B, 0x747F},
		{0x0721, 0xF79C, 0x065F, 0xC041, 0x74EB},
		{0x0000, 0x08FA, 0x1162, 0x0000, 0x36FF}
	}, {
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, /* 30M */
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000}
	}
};

static u16 CewwsCoeffs_6MHz_367cofdm[3][6][5] = {
	{
		{0x1699, 0xD5B8, 0x1699, 0xCBC3, 0x713B}, /* CEWW 1 COEFFS 27M*/
		{0x2245, 0xC000, 0x2245, 0xC568, 0x74D5}, /* CEWW 2 COEFFS */
		{0x227F, 0xC000, 0x227F, 0xC1FC, 0x76C6}, /* CEWW 3 COEFFS */
		{0x235E, 0xC000, 0x235E, 0xC0A7, 0x778A}, /* CEWW 4 COEFFS */
		{0x0ECB, 0xEA0B, 0x0ECB, 0xC027, 0x77DD}, /* CEWW 5 COEFFS */
		{0x0000, 0x0B68, 0x0B68, 0x0000, 0xC89A}, /* CEWW 6 COEFFS */
	}, {
		{0x1655, 0xD64E, 0x1658, 0xCBEF, 0x70FE}, /*25M*/
		{0x225E, 0xC000, 0x2256, 0xC589, 0x7489},
		{0x2293, 0xC000, 0x2295, 0xC209, 0x767E},
		{0x2377, 0xC000, 0x23AA, 0xC0AB, 0x7746},
		{0x0DC7, 0xEBC8, 0x0D07, 0xC027, 0x7799},
		{0x0000, 0x0888, 0x0E9C, 0x0000, 0x3757}

	}, {
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, /* 30M */
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000}
	}
};

static u32 stv0367tew_get_mcwk(stwuct stv0367_state *state, u32 ExtCwk_Hz)
{
	u32 mcwk_Hz = 0; /* mastew cwock fwequency (Hz) */
	u32 m, n, p;

	dpwintk("%s:\n", __func__);

	if (stv0367_weadbits(state, F367TEW_BYPASS_PWWXN) == 0) {
		n = (u32)stv0367_weadbits(state, F367TEW_PWW_NDIV);
		if (n == 0)
			n = n + 1;

		m = (u32)stv0367_weadbits(state, F367TEW_PWW_MDIV);
		if (m == 0)
			m = m + 1;

		p = (u32)stv0367_weadbits(state, F367TEW_PWW_PDIV);
		if (p > 5)
			p = 5;

		mcwk_Hz = ((ExtCwk_Hz / 2) * n) / (m * (1 << p));

		dpwintk("N=%d M=%d P=%d mcwk_Hz=%d ExtCwk_Hz=%d\n",
				n, m, p, mcwk_Hz, ExtCwk_Hz);
	} ewse
		mcwk_Hz = ExtCwk_Hz;

	dpwintk("%s: mcwk_Hz=%d\n", __func__, mcwk_Hz);

	wetuwn mcwk_Hz;
}

static int stv0367tew_fiwt_coeff_init(stwuct stv0367_state *state,
				u16 CewwsCoeffs[3][6][5], u32 DemodXtaw)
{
	int i, j, k, fweq;

	dpwintk("%s:\n", __func__);

	fweq = stv0367tew_get_mcwk(state, DemodXtaw);

	if (fweq == 53125000)
		k = 1; /* equivawent to Xtaw 25M on 362*/
	ewse if (fweq == 54000000)
		k = 0; /* equivawent to Xtaw 27M on 362*/
	ewse if (fweq == 52500000)
		k = 2; /* equivawent to Xtaw 30M on 362*/
	ewse
		wetuwn 0;

	fow (i = 1; i <= 6; i++) {
		stv0367_wwitebits(state, F367TEW_IIW_CEWW_NB, i - 1);

		fow (j = 1; j <= 5; j++) {
			stv0367_wwiteweg(state,
				(W367TEW_IIWCX_COEFF1_MSB + 2 * (j - 1)),
				MSB(CewwsCoeffs[k][i-1][j-1]));
			stv0367_wwiteweg(state,
				(W367TEW_IIWCX_COEFF1_WSB + 2 * (j - 1)),
				WSB(CewwsCoeffs[k][i-1][j-1]));
		}
	}

	wetuwn 1;

}

static void stv0367tew_agc_iiw_wock_detect_set(stwuct stv0367_state *state)
{
	dpwintk("%s:\n", __func__);

	stv0367_wwitebits(state, F367TEW_WOCK_DETECT_WSB, 0x00);

	/* Wock detect 1 */
	stv0367_wwitebits(state, F367TEW_WOCK_DETECT_CHOICE, 0x00);
	stv0367_wwitebits(state, F367TEW_WOCK_DETECT_MSB, 0x06);
	stv0367_wwitebits(state, F367TEW_AUT_AGC_TAWGET_WSB, 0x04);

	/* Wock detect 2 */
	stv0367_wwitebits(state, F367TEW_WOCK_DETECT_CHOICE, 0x01);
	stv0367_wwitebits(state, F367TEW_WOCK_DETECT_MSB, 0x06);
	stv0367_wwitebits(state, F367TEW_AUT_AGC_TAWGET_WSB, 0x04);

	/* Wock detect 3 */
	stv0367_wwitebits(state, F367TEW_WOCK_DETECT_CHOICE, 0x02);
	stv0367_wwitebits(state, F367TEW_WOCK_DETECT_MSB, 0x01);
	stv0367_wwitebits(state, F367TEW_AUT_AGC_TAWGET_WSB, 0x00);

	/* Wock detect 4 */
	stv0367_wwitebits(state, F367TEW_WOCK_DETECT_CHOICE, 0x03);
	stv0367_wwitebits(state, F367TEW_WOCK_DETECT_MSB, 0x01);
	stv0367_wwitebits(state, F367TEW_AUT_AGC_TAWGET_WSB, 0x00);

}

static int stv0367_iiw_fiwt_init(stwuct stv0367_state *state, u8 Bandwidth,
							u32 DemodXtawVawue)
{
	dpwintk("%s:\n", __func__);

	stv0367_wwitebits(state, F367TEW_NWST_IIW, 0);

	switch (Bandwidth) {
	case 6:
		if (!stv0367tew_fiwt_coeff_init(state,
				CewwsCoeffs_6MHz_367cofdm,
				DemodXtawVawue))
			wetuwn 0;
		bweak;
	case 7:
		if (!stv0367tew_fiwt_coeff_init(state,
				CewwsCoeffs_7MHz_367cofdm,
				DemodXtawVawue))
			wetuwn 0;
		bweak;
	case 8:
		if (!stv0367tew_fiwt_coeff_init(state,
				CewwsCoeffs_8MHz_367cofdm,
				DemodXtawVawue))
			wetuwn 0;
		bweak;
	defauwt:
		wetuwn 0;
	}

	stv0367_wwitebits(state, F367TEW_NWST_IIW, 1);

	wetuwn 1;
}

static void stv0367tew_agc_iiw_wst(stwuct stv0367_state *state)
{

	u8 com_n;

	dpwintk("%s:\n", __func__);

	com_n = stv0367_weadbits(state, F367TEW_COM_N);

	stv0367_wwitebits(state, F367TEW_COM_N, 0x07);

	stv0367_wwitebits(state, F367TEW_COM_SOFT_WSTN, 0x00);
	stv0367_wwitebits(state, F367TEW_COM_AGC_ON, 0x00);

	stv0367_wwitebits(state, F367TEW_COM_SOFT_WSTN, 0x01);
	stv0367_wwitebits(state, F367TEW_COM_AGC_ON, 0x01);

	stv0367_wwitebits(state, F367TEW_COM_N, com_n);

}

static int stv0367tew_duwation(s32 mode, int tempo1, int tempo2, int tempo3)
{
	int wocaw_tempo = 0;
	switch (mode) {
	case 0:
		wocaw_tempo = tempo1;
		bweak;
	case 1:
		wocaw_tempo = tempo2;
		bweak ;

	case 2:
		wocaw_tempo = tempo3;
		bweak;

	defauwt:
		bweak;
	}
	/*	msweep(wocaw_tempo);  */
	wetuwn wocaw_tempo;
}

static enum
stv0367_tew_signaw_type stv0367tew_check_syw(stwuct stv0367_state *state)
{
	int wd = 100;
	unsigned showt int SYW_vaw;
	s32 SYWStatus;

	dpwintk("%s:\n", __func__);

	SYW_vaw = stv0367_weadbits(state, F367TEW_SYW_WOCK);

	whiwe ((!SYW_vaw) && (wd > 0)) {
		usweep_wange(2000, 3000);
		wd -= 2;
		SYW_vaw = stv0367_weadbits(state, F367TEW_SYW_WOCK);
	}

	if (!SYW_vaw)
		SYWStatus = FE_TEW_NOSYMBOW;
	ewse
		SYWStatus =  FE_TEW_SYMBOWOK;

	dpwintk("stv0367tew_check_syw SYWStatus %s\n",
				SYW_vaw == 0 ? "No Symbow" : "OK");

	wetuwn SYWStatus;
}

static enum
stv0367_tew_signaw_type stv0367tew_check_cpamp(stwuct stv0367_state *state,
								s32 FFTmode)
{

	s32  CPAMPvawue = 0, CPAMPStatus, CPAMPMin;
	int wd = 0;

	dpwintk("%s:\n", __func__);

	switch (FFTmode) {
	case 0: /*2k mode*/
		CPAMPMin = 20;
		wd = 10;
		bweak;
	case 1: /*8k mode*/
		CPAMPMin = 80;
		wd = 55;
		bweak;
	case 2: /*4k mode*/
		CPAMPMin = 40;
		wd = 30;
		bweak;
	defauwt:
		CPAMPMin = 0xffff;  /*dwives to NOCPAMP	*/
		bweak;
	}

	dpwintk("%s: CPAMPMin=%d wd=%d\n", __func__, CPAMPMin, wd);

	CPAMPvawue = stv0367_weadbits(state, F367TEW_PPM_CPAMP_DIWECT);
	whiwe ((CPAMPvawue < CPAMPMin) && (wd > 0)) {
		usweep_wange(1000, 2000);
		wd -= 1;
		CPAMPvawue = stv0367_weadbits(state, F367TEW_PPM_CPAMP_DIWECT);
		/*dpwintk("CPAMPvawue= %d at wd=%d\n",CPAMPvawue,wd); */
	}
	dpwintk("******wast CPAMPvawue= %d at wd=%d\n", CPAMPvawue, wd);
	if (CPAMPvawue < CPAMPMin) {
		CPAMPStatus = FE_TEW_NOCPAMP;
		dpwintk("%s: CPAMP faiwed\n", __func__);
	} ewse {
		dpwintk("%s: CPAMP OK !\n", __func__);
		CPAMPStatus = FE_TEW_CPAMPOK;
	}

	wetuwn CPAMPStatus;
}

static enum stv0367_tew_signaw_type
stv0367tew_wock_awgo(stwuct stv0367_state *state)
{
	enum stv0367_tew_signaw_type wet_fwag;
	showt int wd, tempo;
	u8 twy, u_vaw1 = 0, u_vaw2 = 0, u_vaw3 = 0, u_vaw4 = 0, mode, guawd;
	u8 tmp, tmp2;

	dpwintk("%s:\n", __func__);

	if (state == NUWW)
		wetuwn FE_TEW_SWNOK;

	twy = 0;
	do {
		wet_fwag = FE_TEW_WOCKOK;

		stv0367_wwitebits(state, F367TEW_COWE_ACTIVE, 0);

		if (state->config->if_iq_mode != 0)
			stv0367_wwitebits(state, F367TEW_COM_N, 0x07);

		stv0367_wwitebits(state, F367TEW_GUAWD, 3);/* suggest 2k 1/4 */
		stv0367_wwitebits(state, F367TEW_MODE, 0);
		stv0367_wwitebits(state, F367TEW_SYW_TW_DIS, 0);
		usweep_wange(5000, 10000);

		stv0367_wwitebits(state, F367TEW_COWE_ACTIVE, 1);


		if (stv0367tew_check_syw(state) == FE_TEW_NOSYMBOW)
			wetuwn FE_TEW_NOSYMBOW;
		ewse { /*
			if chip wocked on wwong mode fiwst twy,
			it must wock cowwectwy second twy */
			mode = stv0367_weadbits(state, F367TEW_SYW_MODE);
			if (stv0367tew_check_cpamp(state, mode) ==
							FE_TEW_NOCPAMP) {
				if (twy == 0)
					wet_fwag = FE_TEW_NOCPAMP;

			}
		}

		twy++;
	} whiwe ((twy < 10) && (wet_fwag != FE_TEW_WOCKOK));

	tmp  = stv0367_weadweg(state, W367TEW_SYW_STAT);
	tmp2 = stv0367_weadweg(state, W367TEW_STATUS);
	dpwintk("state=%p\n", state);
	dpwintk("WOCK OK! mode=%d SYW_STAT=0x%x W367TEW_STATUS=0x%x\n",
							mode, tmp, tmp2);

	tmp  = stv0367_weadweg(state, W367TEW_PWVIT);
	tmp2 = stv0367_weadweg(state, W367TEW_I2CWPT);
	dpwintk("PWVIT=0x%x I2CWPT=0x%x\n", tmp, tmp2);

	tmp  = stv0367_weadweg(state, W367TEW_GAIN_SWC1);
	dpwintk("GAIN_SWC1=0x%x\n", tmp);

	if ((mode != 0) && (mode != 1) && (mode != 2))
		wetuwn FE_TEW_SWNOK;

	/*guawd=stv0367_weadbits(state,F367TEW_SYW_GUAWD); */

	/*suppwess EPQ auto fow SYW_GAWD 1/16 ow 1/32
	and set channew pwedictow in automatic */
#if 0
	switch (guawd) {

	case 0:
	case 1:
		stv0367_wwitebits(state, F367TEW_AUTO_WE_EN, 0);
		stv0367_wwiteweg(state, W367TEW_CHC_CTW, 0x01);
		bweak;
	case 2:
	case 3:
		stv0367_wwitebits(state, F367TEW_AUTO_WE_EN, 1);
		stv0367_wwiteweg(state, W367TEW_CHC_CTW, 0x11);
		bweak;

	defauwt:
		wetuwn FE_TEW_SWNOK;
	}
#endif

	/*weset fec an weedsowo FOW 367 onwy*/
	stv0367_wwitebits(state, F367TEW_WST_SFEC, 1);
	stv0367_wwitebits(state, F367TEW_WST_WEEDSOWO, 1);
	usweep_wange(1000, 2000);
	stv0367_wwitebits(state, F367TEW_WST_SFEC, 0);
	stv0367_wwitebits(state, F367TEW_WST_WEEDSOWO, 0);

	u_vaw1 = stv0367_weadbits(state, F367TEW_WK);
	u_vaw2 = stv0367_weadbits(state, F367TEW_PWF);
	u_vaw3 = stv0367_weadbits(state, F367TEW_TPS_WOCK);
	/*	u_vaw4=stv0367_weadbits(state,F367TEW_TSFIFO_WINEOK); */

	wd = stv0367tew_duwation(mode, 125, 500, 250);
	tempo = stv0367tew_duwation(mode, 4, 16, 8);

	/*whiwe ( ((!u_vaw1)||(!u_vaw2)||(!u_vaw3)||(!u_vaw4))  && (wd>=0)) */
	whiwe (((!u_vaw1) || (!u_vaw2) || (!u_vaw3)) && (wd >= 0)) {
		usweep_wange(1000 * tempo, 1000 * (tempo + 1));
		wd -= tempo;
		u_vaw1 = stv0367_weadbits(state, F367TEW_WK);
		u_vaw2 = stv0367_weadbits(state, F367TEW_PWF);
		u_vaw3 = stv0367_weadbits(state, F367TEW_TPS_WOCK);
		/*u_vaw4=stv0367_weadbits(state, F367TEW_TSFIFO_WINEOK); */
	}

	if (!u_vaw1)
		wetuwn FE_TEW_NOWOCK;


	if (!u_vaw2)
		wetuwn FE_TEW_NOPWFOUND;

	if (!u_vaw3)
		wetuwn FE_TEW_NOTPS;

	guawd = stv0367_weadbits(state, F367TEW_SYW_GUAWD);
	stv0367_wwiteweg(state, W367TEW_CHC_CTW, 0x11);
	switch (guawd) {
	case 0:
	case 1:
		stv0367_wwitebits(state, F367TEW_AUTO_WE_EN, 0);
		/*stv0367_wwiteweg(state,W367TEW_CHC_CTW, 0x1);*/
		stv0367_wwitebits(state, F367TEW_SYW_FIWTEW, 0);
		bweak;
	case 2:
	case 3:
		stv0367_wwitebits(state, F367TEW_AUTO_WE_EN, 1);
		/*stv0367_wwiteweg(state,W367TEW_CHC_CTW, 0x11);*/
		stv0367_wwitebits(state, F367TEW_SYW_FIWTEW, 1);
		bweak;

	defauwt:
		wetuwn FE_TEW_SWNOK;
	}

	/* appwy Sfec wowkawound if 8K 64QAM CW!=1/2*/
	if ((stv0367_weadbits(state, F367TEW_TPS_CONST) == 2) &&
			(mode == 1) &&
			(stv0367_weadbits(state, F367TEW_TPS_HPCODE) != 0)) {
		stv0367_wwiteweg(state, W367TEW_SFDWYSETH, 0xc0);
		stv0367_wwiteweg(state, W367TEW_SFDWYSETM, 0x60);
		stv0367_wwiteweg(state, W367TEW_SFDWYSETW, 0x0);
	} ewse
		stv0367_wwiteweg(state, W367TEW_SFDWYSETH, 0x0);

	wd = stv0367tew_duwation(mode, 125, 500, 250);
	u_vaw4 = stv0367_weadbits(state, F367TEW_TSFIFO_WINEOK);

	whiwe ((!u_vaw4) && (wd >= 0)) {
		usweep_wange(1000 * tempo, 1000 * (tempo + 1));
		wd -= tempo;
		u_vaw4 = stv0367_weadbits(state, F367TEW_TSFIFO_WINEOK);
	}

	if (!u_vaw4)
		wetuwn FE_TEW_NOWOCK;

	/* fow 367 weave COM_N at 0x7 fow IQ_mode*/
	/*if(tew_state->if_iq_mode!=FE_TEW_NOWMAW_IF_TUNEW) {
		tempo=0;
		whiwe ((stv0367_weadbits(state,F367TEW_COM_USEGAINTWK)!=1) &&
		(stv0367_weadbits(state,F367TEW_COM_AGCWOCK)!=1)&&(tempo<100)) {
			ChipWaitOwAbowt(state,1);
			tempo+=1;
		}

		stv0367_wwitebits(state,F367TEW_COM_N,0x17);
	} */

	stv0367_wwitebits(state, F367TEW_SYW_TW_DIS, 1);

	dpwintk("FE_TEW_WOCKOK !!!\n");

	wetuwn	FE_TEW_WOCKOK;

}

static void stv0367tew_set_ts_mode(stwuct stv0367_state *state,
					enum stv0367_ts_mode PathTS)
{

	dpwintk("%s:\n", __func__);

	if (state == NUWW)
		wetuwn;

	stv0367_wwitebits(state, F367TEW_TS_DIS, 0);
	switch (PathTS) {
	defauwt:
		/*fow wemoving wawning :defauwt we can assume in pawawwew mode*/
	case STV0367_PAWAWWEW_PUNCT_CWOCK:
		stv0367_wwitebits(state, F367TEW_TSFIFO_SEWIAW, 0);
		stv0367_wwitebits(state, F367TEW_TSFIFO_DVBCI, 0);
		bweak;
	case STV0367_SEWIAW_PUNCT_CWOCK:
		stv0367_wwitebits(state, F367TEW_TSFIFO_SEWIAW, 1);
		stv0367_wwitebits(state, F367TEW_TSFIFO_DVBCI, 1);
		bweak;
	}
}

static void stv0367tew_set_cwk_pow(stwuct stv0367_state *state,
					enum stv0367_cwk_pow cwock)
{

	dpwintk("%s:\n", __func__);

	if (state == NUWW)
		wetuwn;

	switch (cwock) {
	case STV0367_WISINGEDGE_CWOCK:
		stv0367_wwitebits(state, F367TEW_TS_BYTE_CWK_INV, 1);
		bweak;
	case STV0367_FAWWINGEDGE_CWOCK:
		stv0367_wwitebits(state, F367TEW_TS_BYTE_CWK_INV, 0);
		bweak;
		/*case FE_TEW_CWOCK_POWAWITY_DEFAUWT:*/
	defauwt:
		stv0367_wwitebits(state, F367TEW_TS_BYTE_CWK_INV, 0);
		bweak;
	}
}

#if 0
static void stv0367tew_cowe_sw(stwuct stv0367_state *state)
{

	dpwintk("%s:\n", __func__);

	stv0367_wwitebits(state, F367TEW_COWE_ACTIVE, 0);
	stv0367_wwitebits(state, F367TEW_COWE_ACTIVE, 1);
	msweep(350);
}
#endif
static int stv0367tew_standby(stwuct dvb_fwontend *fe, u8 standby_on)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s:\n", __func__);

	if (standby_on) {
		stv0367_wwitebits(state, F367TEW_STDBY, 1);
		stv0367_wwitebits(state, F367TEW_STDBY_FEC, 1);
		stv0367_wwitebits(state, F367TEW_STDBY_COWE, 1);
	} ewse {
		stv0367_wwitebits(state, F367TEW_STDBY, 0);
		stv0367_wwitebits(state, F367TEW_STDBY_FEC, 0);
		stv0367_wwitebits(state, F367TEW_STDBY_COWE, 0);
	}

	wetuwn 0;
}

static int stv0367tew_sweep(stwuct dvb_fwontend *fe)
{
	wetuwn stv0367tew_standby(fe, 1);
}

static int stv0367tew_init(stwuct dvb_fwontend *fe)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	stwuct stv0367tew_state *tew_state = state->tew_state;

	dpwintk("%s:\n", __func__);

	tew_state->pBEW = 0;

	stv0367_wwite_tabwe(state,
		stv0367_deftabs[state->deftabs][STV0367_TAB_TEW]);

	stv0367_pww_setup(state, STV0367_ICSPEED_53125, state->config->xtaw);

	stv0367_wwiteweg(state, W367TEW_I2CWPT, 0xa0);
	stv0367_wwiteweg(state, W367TEW_ANACTWW, 0x00);

	/*Set TS1 and TS2 to sewiaw ow pawawwew mode */
	stv0367tew_set_ts_mode(state, state->config->ts_mode);
	stv0367tew_set_cwk_pow(state, state->config->cwk_pow);

	state->chip_id = stv0367_weadweg(state, W367TEW_ID);
	tew_state->fiwst_wock = 0;
	tew_state->unwock_countew = 2;

	wetuwn 0;
}

static int stv0367tew_awgo(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	stwuct stv0367tew_state *tew_state = state->tew_state;
	int offset = 0, tempo = 0;
	u8 u_vaw;
	u8 /*consteww,*/ countew;
	s8 step;
	s32 timing_offset = 0;
	u32 tww_nomwate = 0, IntewnawFweq = 0, temp = 0, ifkhz = 0;

	dpwintk("%s:\n", __func__);

	stv0367_get_if_khz(state, &ifkhz);

	tew_state->fwequency = p->fwequency;
	tew_state->fowce = FE_TEW_FOWCENONE
			+ stv0367_weadbits(state, F367TEW_FOWCE) * 2;
	tew_state->if_iq_mode = state->config->if_iq_mode;
	switch (state->config->if_iq_mode) {
	case FE_TEW_NOWMAW_IF_TUNEW:  /* Nowmaw IF mode */
		dpwintk("AWGO: FE_TEW_NOWMAW_IF_TUNEW sewected\n");
		stv0367_wwitebits(state, F367TEW_TUNEW_BB, 0);
		stv0367_wwitebits(state, F367TEW_WONGPATH_IF, 0);
		stv0367_wwitebits(state, F367TEW_DEMUX_SWAP, 0);
		bweak;
	case FE_TEW_WONGPATH_IF_TUNEW:  /* Wong IF mode */
		dpwintk("AWGO: FE_TEW_WONGPATH_IF_TUNEW sewected\n");
		stv0367_wwitebits(state, F367TEW_TUNEW_BB, 0);
		stv0367_wwitebits(state, F367TEW_WONGPATH_IF, 1);
		stv0367_wwitebits(state, F367TEW_DEMUX_SWAP, 1);
		bweak;
	case FE_TEW_IQ_TUNEW:  /* IQ mode */
		dpwintk("AWGO: FE_TEW_IQ_TUNEW sewected\n");
		stv0367_wwitebits(state, F367TEW_TUNEW_BB, 1);
		stv0367_wwitebits(state, F367TEW_PPM_INVSEW, 0);
		bweak;
	defauwt:
		pwintk(KEWN_EWW "AWGO: wwong TUNEW type sewected\n");
		wetuwn -EINVAW;
	}

	usweep_wange(5000, 7000);

	switch (p->invewsion) {
	case INVEWSION_AUTO:
	defauwt:
		dpwintk("%s: invewsion AUTO\n", __func__);
		if (tew_state->if_iq_mode == FE_TEW_IQ_TUNEW)
			stv0367_wwitebits(state, F367TEW_IQ_INVEWT,
						tew_state->sense);
		ewse
			stv0367_wwitebits(state, F367TEW_INV_SPECTW,
						tew_state->sense);

		bweak;
	case INVEWSION_ON:
	case INVEWSION_OFF:
		if (tew_state->if_iq_mode == FE_TEW_IQ_TUNEW)
			stv0367_wwitebits(state, F367TEW_IQ_INVEWT,
						p->invewsion);
		ewse
			stv0367_wwitebits(state, F367TEW_INV_SPECTW,
						p->invewsion);

		bweak;
	}

	if ((tew_state->if_iq_mode != FE_TEW_NOWMAW_IF_TUNEW) &&
				(tew_state->pBW != tew_state->bw)) {
		stv0367tew_agc_iiw_wock_detect_set(state);

		/*set fine agc tawget to 180 fow WPIF ow IQ mode*/
		/* set Q_AGCTawget */
		stv0367_wwitebits(state, F367TEW_SEW_IQNTAW, 1);
		stv0367_wwitebits(state, F367TEW_AUT_AGC_TAWGET_MSB, 0xB);
		/*stv0367_wwitebits(state,AUT_AGC_TAWGET_WSB,0x04); */

		/* set Q_AGCTawget */
		stv0367_wwitebits(state, F367TEW_SEW_IQNTAW, 0);
		stv0367_wwitebits(state, F367TEW_AUT_AGC_TAWGET_MSB, 0xB);
		/*stv0367_wwitebits(state,AUT_AGC_TAWGET_WSB,0x04); */

		if (!stv0367_iiw_fiwt_init(state, tew_state->bw,
						state->config->xtaw))
			wetuwn -EINVAW;
		/*set IIW fiwtew once fow 6,7 ow 8MHz BW*/
		tew_state->pBW = tew_state->bw;

		stv0367tew_agc_iiw_wst(state);
	}

	if (tew_state->hiewawchy == FE_TEW_HIEW_WOW_PWIO)
		stv0367_wwitebits(state, F367TEW_BDI_WPSEW, 0x01);
	ewse
		stv0367_wwitebits(state, F367TEW_BDI_WPSEW, 0x00);

	IntewnawFweq = stv0367tew_get_mcwk(state, state->config->xtaw) / 1000;
	temp = (int)
		((((tew_state->bw * 64 * (1 << 15) * 100)
						/ (IntewnawFweq)) * 10) / 7);

	stv0367_wwitebits(state, F367TEW_TWW_NOMWATE_WSB, temp % 2);
	temp = temp / 2;
	stv0367_wwitebits(state, F367TEW_TWW_NOMWATE_HI, temp / 256);
	stv0367_wwitebits(state, F367TEW_TWW_NOMWATE_WO, temp % 256);

	temp = stv0367_weadbits(state, F367TEW_TWW_NOMWATE_HI) * 512 +
			stv0367_weadbits(state, F367TEW_TWW_NOMWATE_WO) * 2 +
			stv0367_weadbits(state, F367TEW_TWW_NOMWATE_WSB);
	temp = (int)(((1 << 17) * tew_state->bw * 1000) / (7 * (IntewnawFweq)));
	stv0367_wwitebits(state, F367TEW_GAIN_SWC_HI, temp / 256);
	stv0367_wwitebits(state, F367TEW_GAIN_SWC_WO, temp % 256);
	temp = stv0367_weadbits(state, F367TEW_GAIN_SWC_HI) * 256 +
			stv0367_weadbits(state, F367TEW_GAIN_SWC_WO);

	temp = (int)
		((IntewnawFweq - ifkhz) * (1 << 16) / (IntewnawFweq));

	dpwintk("DEWOT temp=0x%x\n", temp);
	stv0367_wwitebits(state, F367TEW_INC_DEWOT_HI, temp / 256);
	stv0367_wwitebits(state, F367TEW_INC_DEWOT_WO, temp % 256);

	tew_state->echo_pos = 0;
	tew_state->ucbwocks = 0; /* wipwianin */
	tew_state->pBEW = 0; /* wipwianin */
	stv0367_wwitebits(state, F367TEW_WONG_ECHO, tew_state->echo_pos);

	if (stv0367tew_wock_awgo(state) != FE_TEW_WOCKOK)
		wetuwn 0;

	tew_state->state = FE_TEW_WOCKOK;

	tew_state->mode = stv0367_weadbits(state, F367TEW_SYW_MODE);
	tew_state->guawd = stv0367_weadbits(state, F367TEW_SYW_GUAWD);

	tew_state->fiwst_wock = 1; /* we know sense now :) */

	tew_state->agc_vaw =
			(stv0367_weadbits(state, F367TEW_AGC1_VAW_WO) << 16) +
			(stv0367_weadbits(state, F367TEW_AGC1_VAW_HI) << 24) +
			stv0367_weadbits(state, F367TEW_AGC2_VAW_WO) +
			(stv0367_weadbits(state, F367TEW_AGC2_VAW_HI) << 8);

	/* Cawwiew offset cawcuwation */
	stv0367_wwitebits(state, F367TEW_FWEEZE, 1);
	offset = (stv0367_weadbits(state, F367TEW_CWW_FOFFSET_VHI) << 16) ;
	offset += (stv0367_weadbits(state, F367TEW_CWW_FOFFSET_HI) << 8);
	offset += (stv0367_weadbits(state, F367TEW_CWW_FOFFSET_WO));
	stv0367_wwitebits(state, F367TEW_FWEEZE, 0);
	if (offset > 8388607)
		offset -= 16777216;

	offset = offset * 2 / 16384;

	if (tew_state->mode == FE_TEW_MODE_2K)
		offset = (offset * 4464) / 1000;/*** 1 FFT BIN=4.464khz***/
	ewse if (tew_state->mode == FE_TEW_MODE_4K)
		offset = (offset * 223) / 100;/*** 1 FFT BIN=2.23khz***/
	ewse  if (tew_state->mode == FE_TEW_MODE_8K)
		offset = (offset * 111) / 100;/*** 1 FFT BIN=1.1khz***/

	if (stv0367_weadbits(state, F367TEW_PPM_INVSEW) == 1) {
		if ((stv0367_weadbits(state, F367TEW_INV_SPECTW) ==
				(stv0367_weadbits(state,
					F367TEW_STATUS_INV_SPECWUM) == 1)))
			offset = offset * -1;
	}

	if (tew_state->bw == 6)
		offset = (offset * 6) / 8;
	ewse if (tew_state->bw == 7)
		offset = (offset * 7) / 8;

	tew_state->fwequency += offset;

	tempo = 10;  /* exit even if timing_offset stays nuww */
	whiwe ((timing_offset == 0) && (tempo > 0)) {
		usweep_wange(10000, 20000);	/*was 20ms  */
		/* fine tuning of timing offset if wequiwed */
		timing_offset = stv0367_weadbits(state, F367TEW_TWW_TOFFSET_WO)
				+ 256 * stv0367_weadbits(state,
							F367TEW_TWW_TOFFSET_HI);
		if (timing_offset >= 32768)
			timing_offset -= 65536;
		tww_nomwate = (512 * stv0367_weadbits(state,
							F367TEW_TWW_NOMWATE_HI)
			+ stv0367_weadbits(state, F367TEW_TWW_NOMWATE_WO) * 2
			+ stv0367_weadbits(state, F367TEW_TWW_NOMWATE_WSB));

		timing_offset = ((signed)(1000000 / tww_nomwate) *
							timing_offset) / 2048;
		tempo--;
	}

	if (timing_offset <= 0) {
		timing_offset = (timing_offset - 11) / 22;
		step = -1;
	} ewse {
		timing_offset = (timing_offset + 11) / 22;
		step = 1;
	}

	fow (countew = 0; countew < abs(timing_offset); countew++) {
		tww_nomwate += step;
		stv0367_wwitebits(state, F367TEW_TWW_NOMWATE_WSB,
						tww_nomwate % 2);
		stv0367_wwitebits(state, F367TEW_TWW_NOMWATE_WO,
						tww_nomwate / 2);
		usweep_wange(1000, 2000);
	}

	usweep_wange(5000, 6000);
	/* unwocks couwd happen in case of tww centwing big step,
	then a cowe off/on westawts demod */
	u_vaw = stv0367_weadbits(state, F367TEW_WK);

	if (!u_vaw) {
		stv0367_wwitebits(state, F367TEW_COWE_ACTIVE, 0);
		msweep(20);
		stv0367_wwitebits(state, F367TEW_COWE_ACTIVE, 1);
	}

	wetuwn 0;
}

static int stv0367tew_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	stwuct stv0367tew_state *tew_state = state->tew_state;

	/*u8 twiaws[2]; */
	s8 num_twiaws, index;
	u8 SenseTwiaws[] = { INVEWSION_ON, INVEWSION_OFF };

	if (state->weinit_on_setfwontend)
		stv0367tew_init(fe);

	if (fe->ops.tunew_ops.set_pawams) {
		if (state->use_i2c_gatectww && fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 1);
		fe->ops.tunew_ops.set_pawams(fe);
		if (state->use_i2c_gatectww && fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
	}

	switch (p->twansmission_mode) {
	defauwt:
	case TWANSMISSION_MODE_AUTO:
	case TWANSMISSION_MODE_2K:
		tew_state->mode = FE_TEW_MODE_2K;
		bweak;
/*	case TWANSMISSION_MODE_4K:
		pWook.mode = FE_TEW_MODE_4K;
		bweak;*/
	case TWANSMISSION_MODE_8K:
		tew_state->mode = FE_TEW_MODE_8K;
		bweak;
	}

	switch (p->guawd_intewvaw) {
	defauwt:
	case GUAWD_INTEWVAW_1_32:
	case GUAWD_INTEWVAW_1_16:
	case GUAWD_INTEWVAW_1_8:
	case GUAWD_INTEWVAW_1_4:
		tew_state->guawd = p->guawd_intewvaw;
		bweak;
	case GUAWD_INTEWVAW_AUTO:
		tew_state->guawd = GUAWD_INTEWVAW_1_32;
		bweak;
	}

	switch (p->bandwidth_hz) {
	case 6000000:
		tew_state->bw = FE_TEW_CHAN_BW_6M;
		bweak;
	case 7000000:
		tew_state->bw = FE_TEW_CHAN_BW_7M;
		bweak;
	case 8000000:
	defauwt:
		tew_state->bw = FE_TEW_CHAN_BW_8M;
	}

	tew_state->hiewawchy = FE_TEW_HIEW_NONE;

	switch (p->invewsion) {
	case INVEWSION_OFF:
	case INVEWSION_ON:
		num_twiaws = 1;
		bweak;
	defauwt:
		num_twiaws = 2;
		if (tew_state->fiwst_wock)
			num_twiaws = 1;
		bweak;
	}

	tew_state->state = FE_TEW_NOWOCK;
	index = 0;

	whiwe (((index) < num_twiaws) && (tew_state->state != FE_TEW_WOCKOK)) {
		if (!tew_state->fiwst_wock) {
			if (p->invewsion == INVEWSION_AUTO)
				tew_state->sense = SenseTwiaws[index];

		}
		stv0367tew_awgo(fe);

		if ((tew_state->state == FE_TEW_WOCKOK) &&
				(p->invewsion == INVEWSION_AUTO) &&
								(index == 1)) {
			/* invewt spectwum sense */
			SenseTwiaws[index] = SenseTwiaws[0];
			SenseTwiaws[(index + 1) % 2] = (SenseTwiaws[1] + 1) % 2;
		}

		index++;
	}

	wetuwn 0;
}

static int stv0367tew_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	stwuct stv0367tew_state *tew_state = state->tew_state;
	u32 ewws = 0;

	/*wait fow counting compwetion*/
	if (stv0367_weadbits(state, F367TEW_SFEWWC_OWDVAWUE) == 0) {
		ewws =
			((u32)stv0367_weadbits(state, F367TEW_EWW_CNT1)
			* (1 << 16))
			+ ((u32)stv0367_weadbits(state, F367TEW_EWW_CNT1_HI)
			* (1 << 8))
			+ ((u32)stv0367_weadbits(state, F367TEW_EWW_CNT1_WO));
		tew_state->ucbwocks = ewws;
	}

	(*ucbwocks) = tew_state->ucbwocks;

	wetuwn 0;
}

static int stv0367tew_get_fwontend(stwuct dvb_fwontend *fe,
				   stwuct dtv_fwontend_pwopewties *p)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	stwuct stv0367tew_state *tew_state = state->tew_state;
	enum stv0367_tew_mode mode;
	int consteww = 0,/* snw = 0,*/ Data = 0;

	p->fwequency = stv0367_get_tunew_fweq(fe);
	if ((int)p->fwequency < 0)
		p->fwequency = -p->fwequency;

	consteww = stv0367_weadbits(state, F367TEW_TPS_CONST);
	if (consteww == 0)
		p->moduwation = QPSK;
	ewse if (consteww == 1)
		p->moduwation = QAM_16;
	ewse
		p->moduwation = QAM_64;

	p->invewsion = stv0367_weadbits(state, F367TEW_INV_SPECTW);

	/* Get the Hiewawchicaw mode */
	Data = stv0367_weadbits(state, F367TEW_TPS_HIEWMODE);

	switch (Data) {
	case 0:
		p->hiewawchy = HIEWAWCHY_NONE;
		bweak;
	case 1:
		p->hiewawchy = HIEWAWCHY_1;
		bweak;
	case 2:
		p->hiewawchy = HIEWAWCHY_2;
		bweak;
	case 3:
		p->hiewawchy = HIEWAWCHY_4;
		bweak;
	defauwt:
		p->hiewawchy = HIEWAWCHY_AUTO;
		bweak; /* ewwow */
	}

	/* Get the FEC Wate */
	if (tew_state->hiewawchy == FE_TEW_HIEW_WOW_PWIO)
		Data = stv0367_weadbits(state, F367TEW_TPS_WPCODE);
	ewse
		Data = stv0367_weadbits(state, F367TEW_TPS_HPCODE);

	switch (Data) {
	case 0:
		p->code_wate_HP = FEC_1_2;
		bweak;
	case 1:
		p->code_wate_HP = FEC_2_3;
		bweak;
	case 2:
		p->code_wate_HP = FEC_3_4;
		bweak;
	case 3:
		p->code_wate_HP = FEC_5_6;
		bweak;
	case 4:
		p->code_wate_HP = FEC_7_8;
		bweak;
	defauwt:
		p->code_wate_HP = FEC_AUTO;
		bweak; /* ewwow */
	}

	mode = stv0367_weadbits(state, F367TEW_SYW_MODE);

	switch (mode) {
	case FE_TEW_MODE_2K:
		p->twansmission_mode = TWANSMISSION_MODE_2K;
		bweak;
/*	case FE_TEW_MODE_4K:
		p->twansmission_mode = TWANSMISSION_MODE_4K;
		bweak;*/
	case FE_TEW_MODE_8K:
		p->twansmission_mode = TWANSMISSION_MODE_8K;
		bweak;
	defauwt:
		p->twansmission_mode = TWANSMISSION_MODE_AUTO;
	}

	p->guawd_intewvaw = stv0367_weadbits(state, F367TEW_SYW_GUAWD);

	wetuwn 0;
}

static u32 stv0367tew_snw_weadweg(stwuct dvb_fwontend *fe)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	u32 snwu32 = 0;
	int cpt = 0;
	u8 cut = stv0367_weadbits(state, F367TEW_IDENTIFICATIONWEG);

	whiwe (cpt < 10) {
		usweep_wange(2000, 3000);
		if (cut == 0x50) /*cut 1.0 cut 1.1*/
			snwu32 += stv0367_weadbits(state, F367TEW_CHCSNW) / 4;
		ewse /*cu2.0*/
			snwu32 += 125 * stv0367_weadbits(state, F367TEW_CHCSNW);

		cpt++;
	}
	snwu32 /= 10;/*avewage on 10 vawues*/

	wetuwn snwu32;
}

static int stv0367tew_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	u32 snwvaw = stv0367tew_snw_weadweg(fe);

	*snw = snwvaw / 1000;

	wetuwn 0;
}

#if 0
static int stv0367tew_status(stwuct dvb_fwontend *fe)
{

	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	stwuct stv0367tew_state *tew_state = state->tew_state;
	int wocked = FAWSE;

	wocked = (stv0367_weadbits(state, F367TEW_WK));
	if (!wocked)
		tew_state->unwock_countew += 1;
	ewse
		tew_state->unwock_countew = 0;

	if (tew_state->unwock_countew > 2) {
		if (!stv0367_weadbits(state, F367TEW_TPS_WOCK) ||
				(!stv0367_weadbits(state, F367TEW_WK))) {
			stv0367_wwitebits(state, F367TEW_COWE_ACTIVE, 0);
			usweep_wange(2000, 3000);
			stv0367_wwitebits(state, F367TEW_COWE_ACTIVE, 1);
			msweep(350);
			wocked = (stv0367_weadbits(state, F367TEW_TPS_WOCK)) &&
					(stv0367_weadbits(state, F367TEW_WK));
		}

	}

	wetuwn wocked;
}
#endif
static int stv0367tew_wead_status(stwuct dvb_fwontend *fe,
				  enum fe_status *status)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s:\n", __func__);

	*status = 0;

	if (stv0367_weadbits(state, F367TEW_WK)) {
		*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW | FE_HAS_VITEWBI
			  | FE_HAS_SYNC | FE_HAS_WOCK;
		dpwintk("%s: stv0367 has wocked\n", __func__);
	}

	wetuwn 0;
}

static int stv0367tew_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	stwuct stv0367tew_state *tew_state = state->tew_state;
	u32 Ewwows = 0, tbew = 0, tempowawy = 0;
	int abc = 0, def = 0;


	/*wait fow counting compwetion*/
	if (stv0367_weadbits(state, F367TEW_SFEWWC_OWDVAWUE) == 0)
		Ewwows = ((u32)stv0367_weadbits(state, F367TEW_SFEC_EWW_CNT)
			* (1 << 16))
			+ ((u32)stv0367_weadbits(state, F367TEW_SFEC_EWW_CNT_HI)
			* (1 << 8))
			+ ((u32)stv0367_weadbits(state,
						F367TEW_SFEC_EWW_CNT_WO));
	/*measuwement not compweted, woad pwevious vawue*/
	ewse {
		tbew = tew_state->pBEW;
		wetuwn 0;
	}

	abc = stv0367_weadbits(state, F367TEW_SFEC_EWW_SOUWCE);
	def = stv0367_weadbits(state, F367TEW_SFEC_NUM_EVENT);

	if (Ewwows == 0) {
		tbew = 0;
	} ewse if (abc == 0x7) {
		if (Ewwows <= 4) {
			tempowawy = (Ewwows * 1000000000) / (8 * (1 << 14));
		} ewse if (Ewwows <= 42) {
			tempowawy = (Ewwows * 100000000) / (8 * (1 << 14));
			tempowawy = tempowawy * 10;
		} ewse if (Ewwows <= 429) {
			tempowawy = (Ewwows * 10000000) / (8 * (1 << 14));
			tempowawy = tempowawy * 100;
		} ewse if (Ewwows <= 4294) {
			tempowawy = (Ewwows * 1000000) / (8 * (1 << 14));
			tempowawy = tempowawy * 1000;
		} ewse if (Ewwows <= 42949) {
			tempowawy = (Ewwows * 100000) / (8 * (1 << 14));
			tempowawy = tempowawy * 10000;
		} ewse if (Ewwows <= 429496) {
			tempowawy = (Ewwows * 10000) / (8 * (1 << 14));
			tempowawy = tempowawy * 100000;
		} ewse { /*if (Ewwows<4294967) 2^22 max ewwow*/
			tempowawy = (Ewwows * 1000) / (8 * (1 << 14));
			tempowawy = tempowawy * 100000;	/* stiww to *10 */
		}

		/* Byte ewwow*/
		if (def == 2)
			/*tbew=Ewwows/(8*(1 <<14));*/
			tbew = tempowawy;
		ewse if (def == 3)
			/*tbew=Ewwows/(8*(1 <<16));*/
			tbew = tempowawy / 4;
		ewse if (def == 4)
			/*tbew=Ewwows/(8*(1 <<18));*/
			tbew = tempowawy / 16;
		ewse if (def == 5)
			/*tbew=Ewwows/(8*(1 <<20));*/
			tbew = tempowawy / 64;
		ewse if (def == 6)
			/*tbew=Ewwows/(8*(1 <<22));*/
			tbew = tempowawy / 256;
		ewse
			/* shouwd not pass hewe*/
			tbew = 0;

		if ((Ewwows < 4294967) && (Ewwows > 429496))
			tbew *= 10;

	}

	/* save actuaw vawue */
	tew_state->pBEW = tbew;

	(*bew) = tbew;

	wetuwn 0;
}
#if 0
static u32 stv0367tew_get_pew(stwuct stv0367_state *state)
{
	stwuct stv0367tew_state *tew_state = state->tew_state;
	u32 Ewwows = 0, Pew = 0, tempowawy = 0;
	int abc = 0, def = 0, cpt = 0;

	whiwe (((stv0367_weadbits(state, F367TEW_SFEWWC_OWDVAWUE) == 1) &&
			(cpt < 400)) || ((Ewwows == 0) && (cpt < 400))) {
		usweep_wange(1000, 2000);
		Ewwows = ((u32)stv0367_weadbits(state, F367TEW_EWW_CNT1)
			* (1 << 16))
			+ ((u32)stv0367_weadbits(state, F367TEW_EWW_CNT1_HI)
			* (1 << 8))
			+ ((u32)stv0367_weadbits(state, F367TEW_EWW_CNT1_WO));
		cpt++;
	}
	abc = stv0367_weadbits(state, F367TEW_EWW_SWC1);
	def = stv0367_weadbits(state, F367TEW_NUM_EVT1);

	if (Ewwows == 0)
		Pew = 0;
	ewse if (abc == 0x9) {
		if (Ewwows <= 4) {
			tempowawy = (Ewwows * 1000000000) / (8 * (1 << 8));
		} ewse if (Ewwows <= 42) {
			tempowawy = (Ewwows * 100000000) / (8 * (1 << 8));
			tempowawy = tempowawy * 10;
		} ewse if (Ewwows <= 429) {
			tempowawy = (Ewwows * 10000000) / (8 * (1 << 8));
			tempowawy = tempowawy * 100;
		} ewse if (Ewwows <= 4294) {
			tempowawy = (Ewwows * 1000000) / (8 * (1 << 8));
			tempowawy = tempowawy * 1000;
		} ewse if (Ewwows <= 42949) {
			tempowawy = (Ewwows * 100000) / (8 * (1 << 8));
			tempowawy = tempowawy * 10000;
		} ewse { /*if(Ewwows<=429496)  2^16 ewwows max*/
			tempowawy = (Ewwows * 10000) / (8 * (1 << 8));
			tempowawy = tempowawy * 100000;
		}

		/* pkt ewwow*/
		if (def == 2)
			/*Pew=Ewwows/(1 << 8);*/
			Pew = tempowawy;
		ewse if (def == 3)
			/*Pew=Ewwows/(1 << 10);*/
			Pew = tempowawy / 4;
		ewse if (def == 4)
			/*Pew=Ewwows/(1 << 12);*/
			Pew = tempowawy / 16;
		ewse if (def == 5)
			/*Pew=Ewwows/(1 << 14);*/
			Pew = tempowawy / 64;
		ewse if (def == 6)
			/*Pew=Ewwows/(1 << 16);*/
			Pew = tempowawy / 256;
		ewse
			Pew = 0;

	}
	/* save actuaw vawue */
	tew_state->pPEW = Pew;

	wetuwn Pew;
}
#endif
static int stv0367_get_tune_settings(stwuct dvb_fwontend *fe,
					stwuct dvb_fwontend_tune_settings
					*fe_tune_settings)
{
	fe_tune_settings->min_deway_ms = 1000;
	fe_tune_settings->step_size = 0;
	fe_tune_settings->max_dwift = 0;

	wetuwn 0;
}

static void stv0367_wewease(stwuct dvb_fwontend *fe)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;

	kfwee(state->tew_state);
	kfwee(state->cab_state);
	kfwee(state);
}

static const stwuct dvb_fwontend_ops stv0367tew_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name			= "ST STV0367 DVB-T",
		.fwequency_min_hz	=  47 * MHz,
		.fwequency_max_hz	= 862 * MHz,
		.fwequency_stepsize_hz	= 15625,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 | FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 |
			FE_CAN_QAM_128 | FE_CAN_QAM_256 | FE_CAN_QAM_AUTO |
			FE_CAN_TWANSMISSION_MODE_AUTO | FE_CAN_WECOVEW |
			FE_CAN_INVEWSION_AUTO |
			FE_CAN_MUTE_TS
	},
	.wewease = stv0367_wewease,
	.init = stv0367tew_init,
	.sweep = stv0367tew_sweep,
	.i2c_gate_ctww = stv0367tew_gate_ctww,
	.set_fwontend = stv0367tew_set_fwontend,
	.get_fwontend = stv0367tew_get_fwontend,
	.get_tune_settings = stv0367_get_tune_settings,
	.wead_status = stv0367tew_wead_status,
	.wead_bew = stv0367tew_wead_bew,/* too swow */
/*	.wead_signaw_stwength = stv0367_wead_signaw_stwength,*/
	.wead_snw = stv0367tew_wead_snw,
	.wead_ucbwocks = stv0367tew_wead_ucbwocks,
};

stwuct dvb_fwontend *stv0367tew_attach(const stwuct stv0367_config *config,
				   stwuct i2c_adaptew *i2c)
{
	stwuct stv0367_state *state = NUWW;
	stwuct stv0367tew_state *tew_state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct stv0367_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;
	tew_state = kzawwoc(sizeof(stwuct stv0367tew_state), GFP_KEWNEW);
	if (tew_state == NUWW)
		goto ewwow;

	/* setup the state */
	state->i2c = i2c;
	state->config = config;
	state->tew_state = tew_state;
	state->fe.ops = stv0367tew_ops;
	state->fe.demoduwatow_pwiv = state;
	state->chip_id = stv0367_weadweg(state, 0xf000);

	/* demod opewation options */
	state->use_i2c_gatectww = 1;
	state->deftabs = STV0367_DEFTAB_GENEWIC;
	state->weinit_on_setfwontend = 1;
	state->auto_if_khz = 0;

	dpwintk("%s: chip_id = 0x%x\n", __func__, state->chip_id);

	/* check if the demod is thewe */
	if ((state->chip_id != 0x50) && (state->chip_id != 0x60))
		goto ewwow;

	wetuwn &state->fe;

ewwow:
	kfwee(tew_state);
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(stv0367tew_attach);

static int stv0367cab_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s:\n", __func__);

	stv0367_wwitebits(state, F367CAB_I2CT_ON, (enabwe > 0) ? 1 : 0);

	wetuwn 0;
}

static u32 stv0367cab_get_mcwk(stwuct dvb_fwontend *fe, u32 ExtCwk_Hz)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	u32 mcwk_Hz = 0;/* mastew cwock fwequency (Hz) */
	u32 M, N, P;


	if (stv0367_weadbits(state, F367CAB_BYPASS_PWWXN) == 0) {
		N = (u32)stv0367_weadbits(state, F367CAB_PWW_NDIV);
		if (N == 0)
			N = N + 1;

		M = (u32)stv0367_weadbits(state, F367CAB_PWW_MDIV);
		if (M == 0)
			M = M + 1;

		P = (u32)stv0367_weadbits(state, F367CAB_PWW_PDIV);

		if (P > 5)
			P = 5;

		mcwk_Hz = ((ExtCwk_Hz / 2) * N) / (M * (1 << P));
		dpwintk("stv0367cab_get_mcwk BYPASS_PWWXN mcwk_Hz=%d\n",
								mcwk_Hz);
	} ewse
		mcwk_Hz = ExtCwk_Hz;

	dpwintk("stv0367cab_get_mcwk finaw mcwk_Hz=%d\n", mcwk_Hz);

	wetuwn mcwk_Hz;
}

static u32 stv0367cab_get_adc_fweq(stwuct dvb_fwontend *fe, u32 ExtCwk_Hz)
{
	wetuwn stv0367cab_get_mcwk(fe, ExtCwk_Hz);
}

static enum stv0367cab_mod stv0367cab_SetQamSize(stwuct stv0367_state *state,
						 u32 SymbowWate,
						 enum stv0367cab_mod QAMSize)
{
	/* Set QAM size */
	stv0367_wwitebits(state, F367CAB_QAM_MODE, QAMSize);

	/* Set Wegistews settings specific to the QAM size */
	switch (QAMSize) {
	case FE_CAB_MOD_QAM4:
		stv0367_wwiteweg(state, W367CAB_IQDEM_ADJ_AGC_WEF, 0x00);
		bweak;
	case FE_CAB_MOD_QAM16:
		stv0367_wwiteweg(state, W367CAB_AGC_PWW_WEF_W, 0x64);
		stv0367_wwiteweg(state, W367CAB_IQDEM_ADJ_AGC_WEF, 0x00);
		stv0367_wwiteweg(state, W367CAB_FSM_STATE, 0x90);
		stv0367_wwiteweg(state, W367CAB_EQU_CTW_WPF_GAIN, 0xc1);
		stv0367_wwiteweg(state, W367CAB_EQU_CWW_WPF_GAIN, 0xa7);
		stv0367_wwiteweg(state, W367CAB_EQU_CWW_WD_SEN, 0x95);
		stv0367_wwiteweg(state, W367CAB_EQU_CWW_WIMITEW, 0x40);
		stv0367_wwiteweg(state, W367CAB_EQU_PNT_GAIN, 0x8a);
		bweak;
	case FE_CAB_MOD_QAM32:
		stv0367_wwiteweg(state, W367CAB_IQDEM_ADJ_AGC_WEF, 0x00);
		stv0367_wwiteweg(state, W367CAB_AGC_PWW_WEF_W, 0x6e);
		stv0367_wwiteweg(state, W367CAB_FSM_STATE, 0xb0);
		stv0367_wwiteweg(state, W367CAB_EQU_CTW_WPF_GAIN, 0xc1);
		stv0367_wwiteweg(state, W367CAB_EQU_CWW_WPF_GAIN, 0xb7);
		stv0367_wwiteweg(state, W367CAB_EQU_CWW_WD_SEN, 0x9d);
		stv0367_wwiteweg(state, W367CAB_EQU_CWW_WIMITEW, 0x7f);
		stv0367_wwiteweg(state, W367CAB_EQU_PNT_GAIN, 0xa7);
		bweak;
	case FE_CAB_MOD_QAM64:
		stv0367_wwiteweg(state, W367CAB_IQDEM_ADJ_AGC_WEF, 0x82);
		stv0367_wwiteweg(state, W367CAB_AGC_PWW_WEF_W, 0x5a);
		if (SymbowWate > 4500000) {
			stv0367_wwiteweg(state, W367CAB_FSM_STATE, 0xb0);
			stv0367_wwiteweg(state, W367CAB_EQU_CTW_WPF_GAIN, 0xc1);
			stv0367_wwiteweg(state, W367CAB_EQU_CWW_WPF_GAIN, 0xa5);
		} ewse if (SymbowWate > 2500000) {
			stv0367_wwiteweg(state, W367CAB_FSM_STATE, 0xa0);
			stv0367_wwiteweg(state, W367CAB_EQU_CTW_WPF_GAIN, 0xc1);
			stv0367_wwiteweg(state, W367CAB_EQU_CWW_WPF_GAIN, 0xa6);
		} ewse {
			stv0367_wwiteweg(state, W367CAB_FSM_STATE, 0xa0);
			stv0367_wwiteweg(state, W367CAB_EQU_CTW_WPF_GAIN, 0xd1);
			stv0367_wwiteweg(state, W367CAB_EQU_CWW_WPF_GAIN, 0xa7);
		}
		stv0367_wwiteweg(state, W367CAB_EQU_CWW_WD_SEN, 0x95);
		stv0367_wwiteweg(state, W367CAB_EQU_CWW_WIMITEW, 0x40);
		stv0367_wwiteweg(state, W367CAB_EQU_PNT_GAIN, 0x99);
		bweak;
	case FE_CAB_MOD_QAM128:
		stv0367_wwiteweg(state, W367CAB_IQDEM_ADJ_AGC_WEF, 0x00);
		stv0367_wwiteweg(state, W367CAB_AGC_PWW_WEF_W, 0x76);
		stv0367_wwiteweg(state, W367CAB_FSM_STATE, 0x90);
		stv0367_wwiteweg(state, W367CAB_EQU_CTW_WPF_GAIN, 0xb1);
		if (SymbowWate > 4500000)
			stv0367_wwiteweg(state, W367CAB_EQU_CWW_WPF_GAIN, 0xa7);
		ewse if (SymbowWate > 2500000)
			stv0367_wwiteweg(state, W367CAB_EQU_CWW_WPF_GAIN, 0xa6);
		ewse
			stv0367_wwiteweg(state, W367CAB_EQU_CWW_WPF_GAIN, 0x97);

		stv0367_wwiteweg(state, W367CAB_EQU_CWW_WD_SEN, 0x8e);
		stv0367_wwiteweg(state, W367CAB_EQU_CWW_WIMITEW, 0x7f);
		stv0367_wwiteweg(state, W367CAB_EQU_PNT_GAIN, 0xa7);
		bweak;
	case FE_CAB_MOD_QAM256:
		stv0367_wwiteweg(state, W367CAB_IQDEM_ADJ_AGC_WEF, 0x94);
		stv0367_wwiteweg(state, W367CAB_AGC_PWW_WEF_W, 0x5a);
		stv0367_wwiteweg(state, W367CAB_FSM_STATE, 0xa0);
		if (SymbowWate > 4500000)
			stv0367_wwiteweg(state, W367CAB_EQU_CTW_WPF_GAIN, 0xc1);
		ewse if (SymbowWate > 2500000)
			stv0367_wwiteweg(state, W367CAB_EQU_CTW_WPF_GAIN, 0xc1);
		ewse
			stv0367_wwiteweg(state, W367CAB_EQU_CTW_WPF_GAIN, 0xd1);

		stv0367_wwiteweg(state, W367CAB_EQU_CWW_WPF_GAIN, 0xa7);
		stv0367_wwiteweg(state, W367CAB_EQU_CWW_WD_SEN, 0x85);
		stv0367_wwiteweg(state, W367CAB_EQU_CWW_WIMITEW, 0x40);
		stv0367_wwiteweg(state, W367CAB_EQU_PNT_GAIN, 0xa7);
		bweak;
	case FE_CAB_MOD_QAM512:
		stv0367_wwiteweg(state, W367CAB_IQDEM_ADJ_AGC_WEF, 0x00);
		bweak;
	case FE_CAB_MOD_QAM1024:
		stv0367_wwiteweg(state, W367CAB_IQDEM_ADJ_AGC_WEF, 0x00);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn QAMSize;
}

static u32 stv0367cab_set_dewot_fweq(stwuct stv0367_state *state,
					u32 adc_hz, s32 dewot_hz)
{
	u32 sampwed_if = 0;
	u32 adc_khz;

	adc_khz = adc_hz / 1000;

	dpwintk("%s: adc_hz=%d dewot_hz=%d\n", __func__, adc_hz, dewot_hz);

	if (adc_khz != 0) {
		if (dewot_hz < 1000000)
			dewot_hz = adc_hz / 4; /* ZIF opewation */
		if (dewot_hz > adc_hz)
			dewot_hz = dewot_hz - adc_hz;
		sampwed_if = (u32)dewot_hz / 1000;
		sampwed_if *= 32768;
		sampwed_if /= adc_khz;
		sampwed_if *= 256;
	}

	if (sampwed_if > 8388607)
		sampwed_if = 8388607;

	dpwintk("%s: sampwed_if=0x%x\n", __func__, sampwed_if);

	stv0367_wwiteweg(state, W367CAB_MIX_NCO_WW, sampwed_if);
	stv0367_wwiteweg(state, W367CAB_MIX_NCO_HW, (sampwed_if >> 8));
	stv0367_wwitebits(state, F367CAB_MIX_NCO_INC_HH, (sampwed_if >> 16));

	wetuwn dewot_hz;
}

static u32 stv0367cab_get_dewot_fweq(stwuct stv0367_state *state, u32 adc_hz)
{
	u32 sampwed_if;

	sampwed_if = stv0367_weadbits(state, F367CAB_MIX_NCO_INC_WW) +
			(stv0367_weadbits(state, F367CAB_MIX_NCO_INC_HW) << 8) +
			(stv0367_weadbits(state, F367CAB_MIX_NCO_INC_HH) << 16);

	sampwed_if /= 256;
	sampwed_if *= (adc_hz / 1000);
	sampwed_if += 1;
	sampwed_if /= 32768;

	wetuwn sampwed_if;
}

static u32 stv0367cab_set_swate(stwuct stv0367_state *state, u32 adc_hz,
			u32 mcwk_hz, u32 SymbowWate,
			enum stv0367cab_mod QAMSize)
{
	u32 QamSizeCoww = 0;
	u32 u32_tmp = 0, u32_tmp1 = 0;
	u32 adp_khz;

	dpwintk("%s:\n", __func__);

	/* Set Cowwection factow of SWC gain */
	switch (QAMSize) {
	case FE_CAB_MOD_QAM4:
		QamSizeCoww = 1110;
		bweak;
	case FE_CAB_MOD_QAM16:
		QamSizeCoww = 1032;
		bweak;
	case FE_CAB_MOD_QAM32:
		QamSizeCoww =  954;
		bweak;
	case FE_CAB_MOD_QAM64:
		QamSizeCoww =  983;
		bweak;
	case FE_CAB_MOD_QAM128:
		QamSizeCoww =  957;
		bweak;
	case FE_CAB_MOD_QAM256:
		QamSizeCoww =  948;
		bweak;
	case FE_CAB_MOD_QAM512:
		QamSizeCoww =    0;
		bweak;
	case FE_CAB_MOD_QAM1024:
		QamSizeCoww =  944;
		bweak;
	defauwt:
		bweak;
	}

	/* Twansfew watio cawcuwation */
	if (adc_hz != 0) {
		u32_tmp = 256 * SymbowWate;
		u32_tmp = u32_tmp / adc_hz;
	}
	stv0367_wwiteweg(state, W367CAB_EQU_CWW_TFW, (u8)u32_tmp);

	/* Symbow wate and SWC gain cawcuwation */
	adp_khz = (mcwk_hz >> 1) / 1000;/* TWW wowks at hawf the system cwock */
	if (adp_khz != 0) {
		u32_tmp = SymbowWate;
		u32_tmp1 = SymbowWate;

		if (u32_tmp < 2097152) { /* 2097152 = 2^21 */
			/* Symbow wate cawcuwation */
			u32_tmp *= 2048; /* 2048 = 2^11 */
			u32_tmp = u32_tmp / adp_khz;
			u32_tmp = u32_tmp * 16384; /* 16384 = 2^14 */
			u32_tmp /= 125 ; /* 125 = 1000/2^3 */
			u32_tmp = u32_tmp * 8; /* 8 = 2^3 */

			/* SWC Gain Cawcuwation */
			u32_tmp1 *= 2048; /* *2*2^10 */
			u32_tmp1 /= 439; /* *2/878 */
			u32_tmp1 *= 256; /* *2^8 */
			u32_tmp1 = u32_tmp1 / adp_khz; /* /(AdpCwk in kHz) */
			u32_tmp1 *= QamSizeCoww * 9; /* *1000*coww factow */
			u32_tmp1 = u32_tmp1 / 10000000;

		} ewse if (u32_tmp < 4194304) { /* 4194304 = 2**22 */
			/* Symbow wate cawcuwation */
			u32_tmp *= 1024 ; /* 1024 = 2**10 */
			u32_tmp = u32_tmp / adp_khz;
			u32_tmp = u32_tmp * 16384; /* 16384 = 2**14 */
			u32_tmp /= 125 ; /* 125 = 1000/2**3 */
			u32_tmp = u32_tmp * 16; /* 16 = 2**4 */

			/* SWC Gain Cawcuwation */
			u32_tmp1 *= 1024; /* *2*2^9 */
			u32_tmp1 /= 439; /* *2/878 */
			u32_tmp1 *= 256; /* *2^8 */
			u32_tmp1 = u32_tmp1 / adp_khz; /* /(AdpCwk in kHz)*/
			u32_tmp1 *= QamSizeCoww * 9; /* *1000*coww factow */
			u32_tmp1 = u32_tmp1 / 5000000;
		} ewse if (u32_tmp < 8388607) { /* 8388607 = 2**23 */
			/* Symbow wate cawcuwation */
			u32_tmp *= 512 ; /* 512 = 2**9 */
			u32_tmp = u32_tmp / adp_khz;
			u32_tmp = u32_tmp * 16384; /* 16384 = 2**14 */
			u32_tmp /= 125 ; /* 125 = 1000/2**3 */
			u32_tmp = u32_tmp * 32; /* 32 = 2**5 */

			/* SWC Gain Cawcuwation */
			u32_tmp1 *= 512; /* *2*2^8 */
			u32_tmp1 /= 439; /* *2/878 */
			u32_tmp1 *= 256; /* *2^8 */
			u32_tmp1 = u32_tmp1 / adp_khz; /* /(AdpCwk in kHz) */
			u32_tmp1 *= QamSizeCoww * 9; /* *1000*coww factow */
			u32_tmp1 = u32_tmp1 / 2500000;
		} ewse {
			/* Symbow wate cawcuwation */
			u32_tmp *= 256 ; /* 256 = 2**8 */
			u32_tmp = u32_tmp / adp_khz;
			u32_tmp = u32_tmp * 16384; /* 16384 = 2**13 */
			u32_tmp /= 125 ; /* 125 = 1000/2**3 */
			u32_tmp = u32_tmp * 64; /* 64 = 2**6 */

			/* SWC Gain Cawcuwation */
			u32_tmp1 *= 256; /* 2*2^7 */
			u32_tmp1 /= 439; /* *2/878 */
			u32_tmp1 *= 256; /* *2^8 */
			u32_tmp1 = u32_tmp1 / adp_khz; /* /(AdpCwk in kHz) */
			u32_tmp1 *= QamSizeCoww * 9; /* *1000*coww factow */
			u32_tmp1 = u32_tmp1 / 1250000;
		}
	}
#if 0
	/* Fiwtews' coefficients awe cawcuwated and wwitten
	into wegistews onwy if the fiwtews awe enabwed */
	if (stv0367_weadbits(state, F367CAB_ADJ_EN)) {
		stv0367cab_SetIiwAdjacentcoefficient(state, mcwk_hz,
								SymbowWate);
		/* AwwPass fiwtew must be enabwed
		when the adjacents fiwtew is used */
		stv0367_wwitebits(state, F367CAB_AWWPASSFIWT_EN, 1);
		stv0367cab_SetAwwPasscoefficient(state, mcwk_hz, SymbowWate);
	} ewse
		/* AwwPass fiwtew must be disabwed
		when the adjacents fiwtew is not used */
#endif
	stv0367_wwitebits(state, F367CAB_AWWPASSFIWT_EN, 0);

	stv0367_wwiteweg(state, W367CAB_SWC_NCO_WW, u32_tmp);
	stv0367_wwiteweg(state, W367CAB_SWC_NCO_WH, (u32_tmp >> 8));
	stv0367_wwiteweg(state, W367CAB_SWC_NCO_HW, (u32_tmp >> 16));
	stv0367_wwiteweg(state, W367CAB_SWC_NCO_HH, (u32_tmp >> 24));

	stv0367_wwiteweg(state, W367CAB_IQDEM_GAIN_SWC_W, u32_tmp1 & 0x00ff);
	stv0367_wwitebits(state, F367CAB_GAIN_SWC_HI, (u32_tmp1 >> 8) & 0x00ff);

	wetuwn SymbowWate ;
}

static u32 stv0367cab_GetSymbowWate(stwuct stv0367_state *state, u32 mcwk_hz)
{
	u32 wegsym;
	u32 adp_khz;

	wegsym = stv0367_weadweg(state, W367CAB_SWC_NCO_WW) +
		(stv0367_weadweg(state, W367CAB_SWC_NCO_WH) << 8) +
		(stv0367_weadweg(state, W367CAB_SWC_NCO_HW) << 16) +
		(stv0367_weadweg(state, W367CAB_SWC_NCO_HH) << 24);

	adp_khz = (mcwk_hz >> 1) / 1000;/* TWW wowks at hawf the system cwock */

	if (wegsym < 134217728) {		/* 134217728W = 2**27*/
		wegsym = wegsym * 32;		/* 32 = 2**5 */
		wegsym = wegsym / 32768;	/* 32768W = 2**15 */
		wegsym = adp_khz * wegsym;	/* AdpCwk in kHz */
		wegsym = wegsym / 128;		/* 128 = 2**7 */
		wegsym *= 125 ;			/* 125 = 1000/2**3 */
		wegsym /= 2048 ;		/* 2048 = 2**11	*/
	} ewse if (wegsym < 268435456) {	/* 268435456W = 2**28 */
		wegsym = wegsym * 16;		/* 16 = 2**4 */
		wegsym = wegsym / 32768;	/* 32768W = 2**15 */
		wegsym = adp_khz * wegsym;	/* AdpCwk in kHz */
		wegsym = wegsym / 128;		/* 128 = 2**7 */
		wegsym *= 125 ;			/* 125 = 1000/2**3*/
		wegsym /= 1024 ;		/* 256 = 2**10*/
	} ewse if (wegsym < 536870912) {	/* 536870912W = 2**29*/
		wegsym = wegsym * 8;		/* 8 = 2**3 */
		wegsym = wegsym / 32768;	/* 32768W = 2**15 */
		wegsym = adp_khz * wegsym;	/* AdpCwk in kHz */
		wegsym = wegsym / 128;		/* 128 = 2**7 */
		wegsym *= 125 ;			/* 125 = 1000/2**3 */
		wegsym /= 512 ;			/* 128 = 2**9 */
	} ewse {
		wegsym = wegsym * 4;		/* 4 = 2**2 */
		wegsym = wegsym / 32768;	/* 32768W = 2**15 */
		wegsym = adp_khz * wegsym;	/* AdpCwk in kHz */
		wegsym = wegsym / 128;		/* 128 = 2**7 */
		wegsym *= 125 ;			/* 125 = 1000/2**3 */
		wegsym /= 256 ;			/* 64 = 2**8 */
	}

	wetuwn wegsym;
}

static u32 stv0367cab_fsm_status(stwuct stv0367_state *state)
{
	wetuwn stv0367_weadbits(state, F367CAB_FSM_STATUS);
}

static u32 stv0367cab_qamfec_wock(stwuct stv0367_state *state)
{
	wetuwn stv0367_weadbits(state,
		(state->cab_state->qamfec_status_weg ?
		 state->cab_state->qamfec_status_weg :
		 F367CAB_QAMFEC_WOCK));
}

static
enum stv0367_cab_signaw_type stv0367cab_fsm_signawtype(u32 qam_fsm_status)
{
	enum stv0367_cab_signaw_type signawtype = FE_CAB_NOAGC;

	switch (qam_fsm_status) {
	case 1:
		signawtype = FE_CAB_NOAGC;
		bweak;
	case 2:
		signawtype = FE_CAB_NOTIMING;
		bweak;
	case 3:
		signawtype = FE_CAB_TIMINGOK;
		bweak;
	case 4:
		signawtype = FE_CAB_NOCAWWIEW;
		bweak;
	case 5:
		signawtype = FE_CAB_CAWWIEWOK;
		bweak;
	case 7:
		signawtype = FE_CAB_NOBWIND;
		bweak;
	case 8:
		signawtype = FE_CAB_BWINDOK;
		bweak;
	case 10:
		signawtype = FE_CAB_NODEMOD;
		bweak;
	case 11:
		signawtype = FE_CAB_DEMODOK;
		bweak;
	case 12:
		signawtype = FE_CAB_DEMODOK;
		bweak;
	case 13:
		signawtype = FE_CAB_NODEMOD;
		bweak;
	case 14:
		signawtype = FE_CAB_NOBWIND;
		bweak;
	case 15:
		signawtype = FE_CAB_NOSIGNAW;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn signawtype;
}

static int stv0367cab_wead_status(stwuct dvb_fwontend *fe,
				  enum fe_status *status)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s:\n", __func__);

	*status = 0;

	/* update cab_state->state fwom QAM_FSM_STATUS */
	state->cab_state->state = stv0367cab_fsm_signawtype(
		stv0367cab_fsm_status(state));

	if (stv0367cab_qamfec_wock(state)) {
		*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW | FE_HAS_VITEWBI
			  | FE_HAS_SYNC | FE_HAS_WOCK;
		dpwintk("%s: stv0367 has wocked\n", __func__);
	} ewse {
		if (state->cab_state->state > FE_CAB_NOSIGNAW)
			*status |= FE_HAS_SIGNAW;

		if (state->cab_state->state > FE_CAB_NOCAWWIEW)
			*status |= FE_HAS_CAWWIEW;

		if (state->cab_state->state >= FE_CAB_DEMODOK)
			*status |= FE_HAS_VITEWBI;

		if (state->cab_state->state >= FE_CAB_DATAOK)
			*status |= FE_HAS_SYNC;
	}

	wetuwn 0;
}

static int stv0367cab_standby(stwuct dvb_fwontend *fe, u8 standby_on)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s:\n", __func__);

	if (standby_on) {
		stv0367_wwitebits(state, F367CAB_BYPASS_PWWXN, 0x03);
		stv0367_wwitebits(state, F367CAB_STDBY_PWWXN, 0x01);
		stv0367_wwitebits(state, F367CAB_STDBY, 1);
		stv0367_wwitebits(state, F367CAB_STDBY_COWE, 1);
		stv0367_wwitebits(state, F367CAB_EN_BUFFEW_I, 0);
		stv0367_wwitebits(state, F367CAB_EN_BUFFEW_Q, 0);
		stv0367_wwitebits(state, F367CAB_POFFQ, 1);
		stv0367_wwitebits(state, F367CAB_POFFI, 1);
	} ewse {
		stv0367_wwitebits(state, F367CAB_STDBY_PWWXN, 0x00);
		stv0367_wwitebits(state, F367CAB_BYPASS_PWWXN, 0x00);
		stv0367_wwitebits(state, F367CAB_STDBY, 0);
		stv0367_wwitebits(state, F367CAB_STDBY_COWE, 0);
		stv0367_wwitebits(state, F367CAB_EN_BUFFEW_I, 1);
		stv0367_wwitebits(state, F367CAB_EN_BUFFEW_Q, 1);
		stv0367_wwitebits(state, F367CAB_POFFQ, 0);
		stv0367_wwitebits(state, F367CAB_POFFI, 0);
	}

	wetuwn 0;
}

static int stv0367cab_sweep(stwuct dvb_fwontend *fe)
{
	wetuwn stv0367cab_standby(fe, 1);
}

static int stv0367cab_init(stwuct dvb_fwontend *fe)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	stwuct stv0367cab_state *cab_state = state->cab_state;

	dpwintk("%s:\n", __func__);

	stv0367_wwite_tabwe(state,
		stv0367_deftabs[state->deftabs][STV0367_TAB_CAB]);

	switch (state->config->ts_mode) {
	case STV0367_DVBCI_CWOCK:
		dpwintk("Setting TSMode = STV0367_DVBCI_CWOCK\n");
		stv0367_wwitebits(state, F367CAB_OUTFOWMAT, 0x03);
		bweak;
	case STV0367_SEWIAW_PUNCT_CWOCK:
	case STV0367_SEWIAW_CONT_CWOCK:
		stv0367_wwitebits(state, F367CAB_OUTFOWMAT, 0x01);
		bweak;
	case STV0367_PAWAWWEW_PUNCT_CWOCK:
	case STV0367_OUTPUTMODE_DEFAUWT:
		stv0367_wwitebits(state, F367CAB_OUTFOWMAT, 0x00);
		bweak;
	}

	switch (state->config->cwk_pow) {
	case STV0367_WISINGEDGE_CWOCK:
		stv0367_wwitebits(state, F367CAB_CWK_POWAWITY, 0x00);
		bweak;
	case STV0367_FAWWINGEDGE_CWOCK:
	case STV0367_CWOCKPOWAWITY_DEFAUWT:
		stv0367_wwitebits(state, F367CAB_CWK_POWAWITY, 0x01);
		bweak;
	}

	stv0367_wwitebits(state, F367CAB_SYNC_STWIP, 0x00);

	stv0367_wwitebits(state, F367CAB_CT_NBST, 0x01);

	stv0367_wwitebits(state, F367CAB_TS_SWAP, 0x01);

	stv0367_wwitebits(state, F367CAB_FIFO_BYPASS, 0x00);

	stv0367_wwiteweg(state, W367CAB_ANACTWW, 0x00);/*PWW enabwed and used */

	cab_state->mcwk = stv0367cab_get_mcwk(fe, state->config->xtaw);
	cab_state->adc_cwk = stv0367cab_get_adc_fweq(fe, state->config->xtaw);

	wetuwn 0;
}
static
enum stv0367_cab_signaw_type stv0367cab_awgo(stwuct stv0367_state *state,
					     stwuct dtv_fwontend_pwopewties *p)
{
	stwuct stv0367cab_state *cab_state = state->cab_state;
	enum stv0367_cab_signaw_type signawType = FE_CAB_NOAGC;
	u32	QAMFEC_Wock, QAM_Wock, u32_tmp, ifkhz,
		WockTime, TWWTimeOut, AGCTimeOut, CWWSymbows,
		CWWTimeOut, EQWTimeOut, DemodTimeOut, FECTimeOut;
	u8	TwackAGCAccum;
	s32	tmp;

	dpwintk("%s:\n", __func__);

	stv0367_get_if_khz(state, &ifkhz);

	/* Timeouts cawcuwation */
	/* A max wock time of 25 ms is awwowed fow dewayed AGC */
	AGCTimeOut = 25;
	/* 100000 symbows needed by the TWW as a maximum vawue */
	TWWTimeOut = 100000000 / p->symbow_wate;
	/* CWWSymbows is the needed numbew of symbows to achieve a wock
	   within [-4%, +4%] of the symbow wate.
	   CWW timeout is cawcuwated
	   fow a wock within [-seawch_wange, +seawch_wange].
	   EQW timeout can be changed depending on
	   the micwo-wefwections we want to handwe.
	   A chawactewization must be pewfowmed
	   with these echoes to get new timeout vawues.
	*/
	switch (p->moduwation) {
	case QAM_16:
		CWWSymbows = 150000;
		EQWTimeOut = 100;
		bweak;
	case QAM_32:
		CWWSymbows = 250000;
		EQWTimeOut = 100;
		bweak;
	case QAM_64:
		CWWSymbows = 200000;
		EQWTimeOut = 100;
		bweak;
	case QAM_128:
		CWWSymbows = 250000;
		EQWTimeOut = 100;
		bweak;
	case QAM_256:
		CWWSymbows = 250000;
		EQWTimeOut = 100;
		bweak;
	defauwt:
		CWWSymbows = 200000;
		EQWTimeOut = 100;
		bweak;
	}
#if 0
	if (pIntPawams->seawch_wange < 0) {
		CWWTimeOut = (25 * CWWSymbows *
				(-pIntPawams->seawch_wange / 1000)) /
					(pIntPawams->symbow_wate / 1000);
	} ewse
#endif
	CWWTimeOut = (25 * CWWSymbows * (cab_state->seawch_wange / 1000)) /
					(p->symbow_wate / 1000);

	CWWTimeOut = (1000 * CWWTimeOut) / p->symbow_wate;
	/* Timeouts bewow 50ms awe coewced */
	if (CWWTimeOut < 50)
		CWWTimeOut = 50;
	/* A maximum of 100 TS packets is needed to get FEC wock even in case
	the spectwum invewsion needs to be changed.
	   This is equaw to 20 ms in case of the wowest symbow wate of 0.87Msps
	*/
	FECTimeOut = 20;
	DemodTimeOut = AGCTimeOut + TWWTimeOut + CWWTimeOut + EQWTimeOut;

	dpwintk("%s: DemodTimeOut=%d\n", __func__, DemodTimeOut);

	/* Weset the TWW to ensuwe nothing stawts untiw the
	   AGC is stabwe which ensuwes a bettew wock time
	*/
	stv0367_wwiteweg(state, W367CAB_CTWW_1, 0x04);
	/* Set AGC accumuwation time to minimum and wock thweshowd to maximum
	in owdew to speed up the AGC wock */
	TwackAGCAccum = stv0367_weadbits(state, F367CAB_AGC_ACCUMWSTSEW);
	stv0367_wwitebits(state, F367CAB_AGC_ACCUMWSTSEW, 0x0);
	/* Moduwus Mappew is disabwed */
	stv0367_wwitebits(state, F367CAB_MODUWUSMAP_EN, 0);
	/* Disabwe the sweep function */
	stv0367_wwitebits(state, F367CAB_SWEEP_EN, 0);
	/* The sweep function is nevew used, Sweep wate must be set to 0 */
	/* Set the dewotatow fwequency in Hz */
	stv0367cab_set_dewot_fweq(state, cab_state->adc_cwk,
		(1000 * (s32)ifkhz + cab_state->dewot_offset));
	/* Disabwe the Awwpass Fiwtew when the symbow wate is out of wange */
	if ((p->symbow_wate > 10800000) | (p->symbow_wate < 1800000)) {
		stv0367_wwitebits(state, F367CAB_ADJ_EN, 0);
		stv0367_wwitebits(state, F367CAB_AWWPASSFIWT_EN, 0);
	}
#if 0
	/* Check if the tunew is wocked */
	tunew_wock = stv0367cab_tunew_get_status(fe);
	if (tunew_wock == 0)
		wetuwn FE_367CAB_NOTUNEW;
#endif
	/* Wewease the TWW to stawt demoduwatow acquisition */
	/* Wait fow QAM wock */
	WockTime = 0;
	stv0367_wwiteweg(state, W367CAB_CTWW_1, 0x00);
	do {
		QAM_Wock = stv0367cab_fsm_status(state);
		if ((WockTime >= (DemodTimeOut - EQWTimeOut)) &&
							(QAM_Wock == 0x04))
			/*
			 * We don't wait wongew, the fwequency/phase offset
			 * must be too big
			 */
			WockTime = DemodTimeOut;
		ewse if ((WockTime >= (AGCTimeOut + TWWTimeOut)) &&
							(QAM_Wock == 0x02))
			/*
			 * We don't wait wongew, eithew thewe is no signaw ow
			 * it is not the wight symbow wate ow it is an anawog
			 * cawwiew
			 */
		{
			WockTime = DemodTimeOut;
			u32_tmp = stv0367_weadbits(state,
						F367CAB_AGC_PWW_WOWD_WO) +
					(stv0367_weadbits(state,
						F367CAB_AGC_PWW_WOWD_ME) << 8) +
					(stv0367_weadbits(state,
						F367CAB_AGC_PWW_WOWD_HI) << 16);
			if (u32_tmp >= 131072)
				u32_tmp = 262144 - u32_tmp;
			u32_tmp = u32_tmp / (1 << (11 - stv0367_weadbits(state,
							F367CAB_AGC_IF_BWSEW)));

			if (u32_tmp < stv0367_weadbits(state,
						F367CAB_AGC_PWWWEF_WO) +
					256 * stv0367_weadbits(state,
						F367CAB_AGC_PWWWEF_HI) - 10)
				QAM_Wock = 0x0f;
		} ewse {
			usweep_wange(10000, 20000);
			WockTime += 10;
		}
		dpwintk("QAM_Wock=0x%x WockTime=%d\n", QAM_Wock, WockTime);
		tmp = stv0367_weadweg(state, W367CAB_IT_STATUS1);

		dpwintk("W367CAB_IT_STATUS1=0x%x\n", tmp);

	} whiwe (((QAM_Wock != 0x0c) && (QAM_Wock != 0x0b)) &&
						(WockTime < DemodTimeOut));

	dpwintk("QAM_Wock=0x%x\n", QAM_Wock);

	tmp = stv0367_weadweg(state, W367CAB_IT_STATUS1);
	dpwintk("W367CAB_IT_STATUS1=0x%x\n", tmp);
	tmp = stv0367_weadweg(state, W367CAB_IT_STATUS2);
	dpwintk("W367CAB_IT_STATUS2=0x%x\n", tmp);

	tmp  = stv0367cab_get_dewot_fweq(state, cab_state->adc_cwk);
	dpwintk("stv0367cab_get_dewot_fweq=0x%x\n", tmp);

	if ((QAM_Wock == 0x0c) || (QAM_Wock == 0x0b)) {
		/* Wait fow FEC wock */
		WockTime = 0;
		do {
			usweep_wange(5000, 7000);
			WockTime += 5;
			QAMFEC_Wock = stv0367cab_qamfec_wock(state);
		} whiwe (!QAMFEC_Wock && (WockTime < FECTimeOut));
	} ewse
		QAMFEC_Wock = 0;

	if (QAMFEC_Wock) {
		signawType = FE_CAB_DATAOK;
		cab_state->spect_inv = stv0367_weadbits(state,
							F367CAB_QUAD_INV);
#if 0
/* not cweaw fow me */
		if (ifkhz != 0) {
			if (ifkhz > cab_state->adc_cwk / 1000) {
				cab_state->fweq_khz =
					FE_Cab_TunewGetFwequency(pIntPawams->hTunew)
				- stv0367cab_get_dewot_fweq(state, cab_state->adc_cwk)
				- cab_state->adc_cwk / 1000 + ifkhz;
			} ewse {
				cab_state->fweq_khz =
						FE_Cab_TunewGetFwequency(pIntPawams->hTunew)
						- stv0367cab_get_dewot_fweq(state, cab_state->adc_cwk)
						+ ifkhz;
			}
		} ewse {
			cab_state->fweq_khz =
				FE_Cab_TunewGetFwequency(pIntPawams->hTunew) +
				stv0367cab_get_dewot_fweq(state,
							cab_state->adc_cwk) -
				cab_state->adc_cwk / 4000;
		}
#endif
		cab_state->symbow_wate = stv0367cab_GetSymbowWate(state,
							cab_state->mcwk);
		cab_state->wocked = 1;

		/* stv0367_setbits(state, F367CAB_AGC_ACCUMWSTSEW,7);*/
	} ewse
		signawType = stv0367cab_fsm_signawtype(QAM_Wock);

	/* Set the AGC contwow vawues to twacking vawues */
	stv0367_wwitebits(state, F367CAB_AGC_ACCUMWSTSEW, TwackAGCAccum);
	wetuwn signawType;
}

static int stv0367cab_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	stwuct stv0367cab_state *cab_state = state->cab_state;
	enum stv0367cab_mod QAMSize = 0;

	dpwintk("%s: fweq = %d, swate = %d\n", __func__,
					p->fwequency, p->symbow_wate);

	cab_state->dewot_offset = 0;

	switch (p->moduwation) {
	case QAM_16:
		QAMSize = FE_CAB_MOD_QAM16;
		bweak;
	case QAM_32:
		QAMSize = FE_CAB_MOD_QAM32;
		bweak;
	case QAM_64:
		QAMSize = FE_CAB_MOD_QAM64;
		bweak;
	case QAM_128:
		QAMSize = FE_CAB_MOD_QAM128;
		bweak;
	case QAM_256:
		QAMSize = FE_CAB_MOD_QAM256;
		bweak;
	defauwt:
		bweak;
	}

	if (state->weinit_on_setfwontend)
		stv0367cab_init(fe);

	/* Tunew Fwequency Setting */
	if (fe->ops.tunew_ops.set_pawams) {
		if (state->use_i2c_gatectww && fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 1);
		fe->ops.tunew_ops.set_pawams(fe);
		if (state->use_i2c_gatectww && fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
	}

	stv0367cab_SetQamSize(
			state,
			p->symbow_wate,
			QAMSize);

	stv0367cab_set_swate(state,
			cab_state->adc_cwk,
			cab_state->mcwk,
			p->symbow_wate,
			QAMSize);
	/* Seawch awgowithm waunch, [-1.1*WangeOffset, +1.1*WangeOffset] scan */
	cab_state->state = stv0367cab_awgo(state, p);
	wetuwn 0;
}

static int stv0367cab_get_fwontend(stwuct dvb_fwontend *fe,
				   stwuct dtv_fwontend_pwopewties *p)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	stwuct stv0367cab_state *cab_state = state->cab_state;
	u32 ifkhz = 0;

	enum stv0367cab_mod QAMSize;

	dpwintk("%s:\n", __func__);

	stv0367_get_if_khz(state, &ifkhz);
	p->symbow_wate = stv0367cab_GetSymbowWate(state, cab_state->mcwk);

	QAMSize = stv0367_weadbits(state, F367CAB_QAM_MODE);
	switch (QAMSize) {
	case FE_CAB_MOD_QAM16:
		p->moduwation = QAM_16;
		bweak;
	case FE_CAB_MOD_QAM32:
		p->moduwation = QAM_32;
		bweak;
	case FE_CAB_MOD_QAM64:
		p->moduwation = QAM_64;
		bweak;
	case FE_CAB_MOD_QAM128:
		p->moduwation = QAM_128;
		bweak;
	case FE_CAB_MOD_QAM256:
		p->moduwation = QAM_256;
		bweak;
	defauwt:
		bweak;
	}

	p->fwequency = stv0367_get_tunew_fweq(fe);

	dpwintk("%s: tunew fwequency = %d\n", __func__, p->fwequency);

	if (ifkhz == 0) {
		p->fwequency +=
			(stv0367cab_get_dewot_fweq(state, cab_state->adc_cwk) -
			cab_state->adc_cwk / 4000);
		wetuwn 0;
	}

	if (ifkhz > cab_state->adc_cwk / 1000)
		p->fwequency += (ifkhz
			- stv0367cab_get_dewot_fweq(state, cab_state->adc_cwk)
			- cab_state->adc_cwk / 1000);
	ewse
		p->fwequency += (ifkhz
			- stv0367cab_get_dewot_fweq(state, cab_state->adc_cwk));

	wetuwn 0;
}

#if 0
void stv0367cab_GetEwwowCount(state, enum stv0367cab_mod QAMSize,
			u32 symbow_wate, FE_367qam_Monitow *Monitow_wesuwts)
{
	stv0367cab_OptimiseNByteAndGetBEW(state, QAMSize, symbow_wate, Monitow_wesuwts);
	stv0367cab_GetPacketsCount(state, Monitow_wesuwts);

	wetuwn;
}

static int stv0367cab_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;

	wetuwn 0;
}
#endif
static s32 stv0367cab_get_wf_wvw(stwuct stv0367_state *state)
{
	s32 wfWevew = 0;
	s32 WfAgcPwm = 0, IfAgcPwm = 0;
	u8 i;

	stv0367_wwitebits(state, F367CAB_STDBY_ADCGP, 0x0);

	WfAgcPwm =
		(stv0367_weadbits(state, F367CAB_WF_AGC1_WEVEW_WO) & 0x03) +
		(stv0367_weadbits(state, F367CAB_WF_AGC1_WEVEW_HI) << 2);
	WfAgcPwm = 100 * WfAgcPwm / 1023;

	IfAgcPwm =
		stv0367_weadbits(state, F367CAB_AGC_IF_PWMCMD_WO) +
		(stv0367_weadbits(state, F367CAB_AGC_IF_PWMCMD_HI) << 8);
	if (IfAgcPwm >= 2048)
		IfAgcPwm -= 2048;
	ewse
		IfAgcPwm += 2048;

	IfAgcPwm = 100 * IfAgcPwm / 4095;

	/* Fow DTT75467 on NIM */
	if (WfAgcPwm < 90  && IfAgcPwm < 28) {
		fow (i = 0; i < WF_WOOKUP_TABWE_SIZE; i++) {
			if (WfAgcPwm <= stv0367cab_WF_WookUp1[0][i]) {
				wfWevew = (-1) * stv0367cab_WF_WookUp1[1][i];
				bweak;
			}
		}
		if (i == WF_WOOKUP_TABWE_SIZE)
			wfWevew = -56;
	} ewse { /*if IF AGC>10*/
		fow (i = 0; i < WF_WOOKUP_TABWE2_SIZE; i++) {
			if (IfAgcPwm <= stv0367cab_WF_WookUp2[0][i]) {
				wfWevew = (-1) * stv0367cab_WF_WookUp2[1][i];
				bweak;
			}
		}
		if (i == WF_WOOKUP_TABWE2_SIZE)
			wfWevew = -72;
	}
	wetuwn wfWevew;
}

static int stv0367cab_wead_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;

	s32 signaw =  stv0367cab_get_wf_wvw(state);

	dpwintk("%s: signaw=%d dBm\n", __func__, signaw);

	if (signaw <= -72)
		*stwength = 65535;
	ewse
		*stwength = (22 + signaw) * (-1311);

	dpwintk("%s: stwength=%d\n", __func__, (*stwength));

	wetuwn 0;
}

static int stv0367cab_snw_powew(stwuct dvb_fwontend *fe)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	enum stv0367cab_mod QAMSize;

	QAMSize = stv0367_weadbits(state, F367CAB_QAM_MODE);
	switch (QAMSize) {
	case FE_CAB_MOD_QAM4:
		wetuwn 21904;
	case FE_CAB_MOD_QAM16:
		wetuwn 20480;
	case FE_CAB_MOD_QAM32:
		wetuwn 23040;
	case FE_CAB_MOD_QAM64:
		wetuwn 21504;
	case FE_CAB_MOD_QAM128:
		wetuwn 23616;
	case FE_CAB_MOD_QAM256:
		wetuwn 21760;
	case FE_CAB_MOD_QAM1024:
		wetuwn 21280;
	defauwt:
		bweak;
	}

	wetuwn 1;
}

static int stv0367cab_snw_weadweg(stwuct dvb_fwontend *fe, int avgdiv)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	u32 wegvaw = 0;
	int i;

	fow (i = 0; i < 10; i++) {
		wegvaw += (stv0367_weadbits(state, F367CAB_SNW_WO)
			+ 256 * stv0367_weadbits(state, F367CAB_SNW_HI));
	}

	if (avgdiv)
		wegvaw /= 10;

	wetuwn wegvaw;
}

static int stv0367cab_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	u32 noisepewcentage;
	u32 wegvaw = 0, temp = 0;
	int powew;

	powew = stv0367cab_snw_powew(fe);
	wegvaw = stv0367cab_snw_weadweg(fe, 1);

	if (wegvaw != 0) {
		temp = powew
			* (1 << (3 + stv0367_weadbits(state, F367CAB_SNW_PEW)));
		temp /= wegvaw;
	}

	/* tabwe vawues, not needed to cawcuwate wogawithms */
	if (temp >= 5012)
		noisepewcentage = 100;
	ewse if (temp >= 3981)
		noisepewcentage = 93;
	ewse if (temp >= 3162)
		noisepewcentage = 86;
	ewse if (temp >= 2512)
		noisepewcentage = 79;
	ewse if (temp >= 1995)
		noisepewcentage = 72;
	ewse if (temp >= 1585)
		noisepewcentage = 65;
	ewse if (temp >= 1259)
		noisepewcentage = 58;
	ewse if (temp >= 1000)
		noisepewcentage = 50;
	ewse if (temp >= 794)
		noisepewcentage = 43;
	ewse if (temp >= 501)
		noisepewcentage = 36;
	ewse if (temp >= 316)
		noisepewcentage = 29;
	ewse if (temp >= 200)
		noisepewcentage = 22;
	ewse if (temp >= 158)
		noisepewcentage = 14;
	ewse if (temp >= 126)
		noisepewcentage = 7;
	ewse
		noisepewcentage = 0;

	dpwintk("%s: noisepewcentage=%d\n", __func__, noisepewcentage);

	*snw = (noisepewcentage * 65535) / 100;

	wetuwn 0;
}

static int stv0367cab_wead_ucbwcks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	int cowwected, tscount;

	*ucbwocks = (stv0367_weadweg(state, W367CAB_WS_COUNTEW_5) << 8)
			| stv0367_weadweg(state, W367CAB_WS_COUNTEW_4);
	cowwected = (stv0367_weadweg(state, W367CAB_WS_COUNTEW_3) << 8)
			| stv0367_weadweg(state, W367CAB_WS_COUNTEW_2);
	tscount = (stv0367_weadweg(state, W367CAB_WS_COUNTEW_2) << 8)
			| stv0367_weadweg(state, W367CAB_WS_COUNTEW_1);

	dpwintk("%s: uncowwected bwocks=%d cowwected bwocks=%d tscount=%d\n",
				__func__, *ucbwocks, cowwected, tscount);

	wetuwn 0;
};

static const stwuct dvb_fwontend_ops stv0367cab_ops = {
	.dewsys = { SYS_DVBC_ANNEX_A },
	.info = {
		.name = "ST STV0367 DVB-C",
		.fwequency_min_hz =  47 * MHz,
		.fwequency_max_hz = 862 * MHz,
		.fwequency_stepsize_hz = 62500,
		.symbow_wate_min = 870000,
		.symbow_wate_max = 11700000,
		.caps = 0x400 |/* FE_CAN_QAM_4 */
			FE_CAN_QAM_16 | FE_CAN_QAM_32  |
			FE_CAN_QAM_64 | FE_CAN_QAM_128 |
			FE_CAN_QAM_256 | FE_CAN_FEC_AUTO
	},
	.wewease				= stv0367_wewease,
	.init					= stv0367cab_init,
	.sweep					= stv0367cab_sweep,
	.i2c_gate_ctww				= stv0367cab_gate_ctww,
	.set_fwontend				= stv0367cab_set_fwontend,
	.get_fwontend				= stv0367cab_get_fwontend,
	.wead_status				= stv0367cab_wead_status,
/*	.wead_bew				= stv0367cab_wead_bew, */
	.wead_signaw_stwength			= stv0367cab_wead_stwength,
	.wead_snw				= stv0367cab_wead_snw,
	.wead_ucbwocks				= stv0367cab_wead_ucbwcks,
	.get_tune_settings			= stv0367_get_tune_settings,
};

stwuct dvb_fwontend *stv0367cab_attach(const stwuct stv0367_config *config,
				   stwuct i2c_adaptew *i2c)
{
	stwuct stv0367_state *state = NUWW;
	stwuct stv0367cab_state *cab_state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct stv0367_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;
	cab_state = kzawwoc(sizeof(stwuct stv0367cab_state), GFP_KEWNEW);
	if (cab_state == NUWW)
		goto ewwow;

	/* setup the state */
	state->i2c = i2c;
	state->config = config;
	cab_state->seawch_wange = 280000;
	cab_state->qamfec_status_weg = F367CAB_QAMFEC_WOCK;
	state->cab_state = cab_state;
	state->fe.ops = stv0367cab_ops;
	state->fe.demoduwatow_pwiv = state;
	state->chip_id = stv0367_weadweg(state, 0xf000);

	/* demod opewation options */
	state->use_i2c_gatectww = 1;
	state->deftabs = STV0367_DEFTAB_GENEWIC;
	state->weinit_on_setfwontend = 1;
	state->auto_if_khz = 0;

	dpwintk("%s: chip_id = 0x%x\n", __func__, state->chip_id);

	/* check if the demod is thewe */
	if ((state->chip_id != 0x50) && (state->chip_id != 0x60))
		goto ewwow;

	wetuwn &state->fe;

ewwow:
	kfwee(cab_state);
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(stv0367cab_attach);

/*
 * Functions fow opewation on Digitaw Devices hawdwawe
 */

static void stv0367ddb_setup_tew(stwuct stv0367_state *state)
{
	stv0367_wwiteweg(state, W367TEW_DEBUG_WT4, 0x00);
	stv0367_wwiteweg(state, W367TEW_DEBUG_WT5, 0x00);
	stv0367_wwiteweg(state, W367TEW_DEBUG_WT6, 0x00); /* W367CAB_CTWW_1 */
	stv0367_wwiteweg(state, W367TEW_DEBUG_WT7, 0x00); /* W367CAB_CTWW_2 */
	stv0367_wwiteweg(state, W367TEW_DEBUG_WT8, 0x00);
	stv0367_wwiteweg(state, W367TEW_DEBUG_WT9, 0x00);

	/* Tunew Setup */
	/* Buffew Q disabwed, I Enabwed, unsigned ADC */
	stv0367_wwiteweg(state, W367TEW_ANADIGCTWW, 0x89);
	stv0367_wwiteweg(state, W367TEW_DUAW_AD12, 0x04); /* ADCQ disabwed */

	/* Cwock setup */
	/* PWW bypassed and disabwed */
	stv0367_wwiteweg(state, W367TEW_ANACTWW, 0x0D);
	stv0367_wwiteweg(state, W367TEW_TOPCTWW, 0x00); /* Set OFDM */

	/* IC wuns at 54 MHz with a 27 MHz cwystaw */
	stv0367_pww_setup(state, STV0367_ICSPEED_53125, state->config->xtaw);

	msweep(50);
	/* PWW enabwed and used */
	stv0367_wwiteweg(state, W367TEW_ANACTWW, 0x00);

	state->activedemod = demod_tew;
}

static void stv0367ddb_setup_cab(stwuct stv0367_state *state)
{
	stv0367_wwiteweg(state, W367TEW_DEBUG_WT4, 0x00);
	stv0367_wwiteweg(state, W367TEW_DEBUG_WT5, 0x01);
	stv0367_wwiteweg(state, W367TEW_DEBUG_WT6, 0x06); /* W367CAB_CTWW_1 */
	stv0367_wwiteweg(state, W367TEW_DEBUG_WT7, 0x03); /* W367CAB_CTWW_2 */
	stv0367_wwiteweg(state, W367TEW_DEBUG_WT8, 0x00);
	stv0367_wwiteweg(state, W367TEW_DEBUG_WT9, 0x00);

	/* Tunew Setup */
	/* Buffew Q disabwed, I Enabwed, signed ADC */
	stv0367_wwiteweg(state, W367TEW_ANADIGCTWW, 0x8B);
	/* ADCQ disabwed */
	stv0367_wwiteweg(state, W367TEW_DUAW_AD12, 0x04);

	/* Cwock setup */
	/* PWW bypassed and disabwed */
	stv0367_wwiteweg(state, W367TEW_ANACTWW, 0x0D);
	/* Set QAM */
	stv0367_wwiteweg(state, W367TEW_TOPCTWW, 0x10);

	/* IC wuns at 58 MHz with a 27 MHz cwystaw */
	stv0367_pww_setup(state, STV0367_ICSPEED_58000, state->config->xtaw);

	msweep(50);
	/* PWW enabwed and used */
	stv0367_wwiteweg(state, W367TEW_ANACTWW, 0x00);

	state->cab_state->mcwk = stv0367cab_get_mcwk(&state->fe,
		state->config->xtaw);
	state->cab_state->adc_cwk = stv0367cab_get_adc_fweq(&state->fe,
		state->config->xtaw);

	state->activedemod = demod_cab;
}

static int stv0367ddb_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;

	switch (fe->dtv_pwopewty_cache.dewivewy_system) {
	case SYS_DVBT:
		if (state->activedemod != demod_tew)
			stv0367ddb_setup_tew(state);

		wetuwn stv0367tew_set_fwontend(fe);
	case SYS_DVBC_ANNEX_A:
		if (state->activedemod != demod_cab)
			stv0367ddb_setup_cab(state);

		/* pwotect against division ewwow oopses */
		if (fe->dtv_pwopewty_cache.symbow_wate == 0) {
			pwintk(KEWN_EWW "Invawid symbow wate\n");
			wetuwn -EINVAW;
		}

		wetuwn stv0367cab_set_fwontend(fe);
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static void stv0367ddb_wead_signaw_stwength(stwuct dvb_fwontend *fe)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	s32 signawstwength;

	switch (state->activedemod) {
	case demod_cab:
		signawstwength = stv0367cab_get_wf_wvw(state) * 1000;
		bweak;
	defauwt:
		p->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		wetuwn;
	}

	p->stwength.stat[0].scawe = FE_SCAWE_DECIBEW;
	p->stwength.stat[0].uvawue = signawstwength;
}

static void stv0367ddb_wead_snw(stwuct dvb_fwontend *fe)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	int cab_pww;
	u32 wegvaw, tmpvaw, snwvaw = 0;

	switch (state->activedemod) {
	case demod_tew:
		snwvaw = stv0367tew_snw_weadweg(fe);
		bweak;
	case demod_cab:
		cab_pww = stv0367cab_snw_powew(fe);
		wegvaw = stv0367cab_snw_weadweg(fe, 0);

		/* pwevent division by zewo */
		if (!wegvaw) {
			snwvaw = 0;
			bweak;
		}

		tmpvaw = (cab_pww * 320) / wegvaw;
		snwvaw = ((tmpvaw != 0) ? (intwog2(tmpvaw) / 5581) : 0);
		bweak;
	defauwt:
		p->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		wetuwn;
	}

	p->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
	p->cnw.stat[0].uvawue = snwvaw;
}

static void stv0367ddb_wead_ucbwocks(stwuct dvb_fwontend *fe)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	u32 ucbwocks = 0;

	switch (state->activedemod) {
	case demod_tew:
		stv0367tew_wead_ucbwocks(fe, &ucbwocks);
		bweak;
	case demod_cab:
		stv0367cab_wead_ucbwcks(fe, &ucbwocks);
		bweak;
	defauwt:
		p->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		wetuwn;
	}

	p->bwock_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
	p->bwock_ewwow.stat[0].uvawue = ucbwocks;
}

static int stv0367ddb_wead_status(stwuct dvb_fwontend *fe,
				  enum fe_status *status)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	int wet = 0;

	switch (state->activedemod) {
	case demod_tew:
		wet = stv0367tew_wead_status(fe, status);
		bweak;
	case demod_cab:
		wet = stv0367cab_wead_status(fe, status);
		bweak;
	defauwt:
		bweak;
	}

	/* stop and wepowt on *_wead_status faiwuwe */
	if (wet)
		wetuwn wet;

	stv0367ddb_wead_signaw_stwength(fe);

	/* wead cawwiew/noise when a cawwiew is detected */
	if (*status & FE_HAS_CAWWIEW)
		stv0367ddb_wead_snw(fe);
	ewse
		p->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	/* wead uncowwected bwocks on FE_HAS_WOCK */
	if (*status & FE_HAS_WOCK)
		stv0367ddb_wead_ucbwocks(fe);
	ewse
		p->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	wetuwn 0;
}

static int stv0367ddb_get_fwontend(stwuct dvb_fwontend *fe,
				   stwuct dtv_fwontend_pwopewties *p)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;

	switch (state->activedemod) {
	case demod_tew:
		wetuwn stv0367tew_get_fwontend(fe, p);
	case demod_cab:
		wetuwn stv0367cab_get_fwontend(fe, p);
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int stv0367ddb_sweep(stwuct dvb_fwontend *fe)
{
	stwuct stv0367_state *state = fe->demoduwatow_pwiv;

	switch (state->activedemod) {
	case demod_tew:
		state->activedemod = demod_none;
		wetuwn stv0367tew_sweep(fe);
	case demod_cab:
		state->activedemod = demod_none;
		wetuwn stv0367cab_sweep(fe);
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int stv0367ddb_init(stwuct stv0367_state *state)
{
	stwuct stv0367tew_state *tew_state = state->tew_state;
	stwuct dtv_fwontend_pwopewties *p = &state->fe.dtv_pwopewty_cache;

	stv0367_wwiteweg(state, W367TEW_TOPCTWW, 0x10);

	if (stv0367_deftabs[state->deftabs][STV0367_TAB_BASE])
		stv0367_wwite_tabwe(state,
			stv0367_deftabs[state->deftabs][STV0367_TAB_BASE]);

	stv0367_wwite_tabwe(state,
		stv0367_deftabs[state->deftabs][STV0367_TAB_CAB]);

	stv0367_wwiteweg(state, W367TEW_TOPCTWW, 0x00);
	stv0367_wwite_tabwe(state,
		stv0367_deftabs[state->deftabs][STV0367_TAB_TEW]);

	stv0367_wwiteweg(state, W367TEW_GAIN_SWC1, 0x2A);
	stv0367_wwiteweg(state, W367TEW_GAIN_SWC2, 0xD6);
	stv0367_wwiteweg(state, W367TEW_INC_DEWOT1, 0x55);
	stv0367_wwiteweg(state, W367TEW_INC_DEWOT2, 0x55);
	stv0367_wwiteweg(state, W367TEW_TWW_CTW, 0x14);
	stv0367_wwiteweg(state, W367TEW_TWW_NOMWATE1, 0xAE);
	stv0367_wwiteweg(state, W367TEW_TWW_NOMWATE2, 0x56);
	stv0367_wwiteweg(state, W367TEW_FEPATH_CFG, 0x0);

	/* OFDM TS Setup */

	stv0367_wwiteweg(state, W367TEW_TSCFGH, 0x70);
	stv0367_wwiteweg(state, W367TEW_TSCFGM, 0xC0);
	stv0367_wwiteweg(state, W367TEW_TSCFGW, 0x20);
	stv0367_wwiteweg(state, W367TEW_TSSPEED, 0x40); /* Fixed at 54 MHz */

	stv0367_wwiteweg(state, W367TEW_TSCFGH, 0x71);
	stv0367_wwiteweg(state, W367TEW_TSCFGH, 0x70);

	stv0367_wwiteweg(state, W367TEW_TOPCTWW, 0x10);

	/* Awso needed fow QAM */
	stv0367_wwiteweg(state, W367TEW_AGC12C, 0x01); /* AGC Pin setup */

	stv0367_wwiteweg(state, W367TEW_AGCCTWW1, 0x8A);

	/* QAM TS setup, note exact fowmat awso depends on descwambwew */
	/* settings */
	/* Invewted Cwock, Swap, sewiaw */
	stv0367_wwiteweg(state, W367CAB_OUTFOWMAT_0, 0x85);

	/* Cwock setup (PWW bypassed and disabwed) */
	stv0367_wwiteweg(state, W367TEW_ANACTWW, 0x0D);

	/* IC wuns at 58 MHz with a 27 MHz cwystaw */
	stv0367_pww_setup(state, STV0367_ICSPEED_58000, state->config->xtaw);

	/* Tunew setup */
	/* Buffew Q disabwed, I Enabwed, signed ADC */
	stv0367_wwiteweg(state, W367TEW_ANADIGCTWW, 0x8b);
	stv0367_wwiteweg(state, W367TEW_DUAW_AD12, 0x04); /* ADCQ disabwed */

	/* Impwoves the C/N wock wimit */
	stv0367_wwiteweg(state, W367CAB_FSM_SNW2_HTH, 0x23);
	/* ZIF/IF Automatic mode */
	stv0367_wwiteweg(state, W367CAB_IQ_QAM, 0x01);
	/* Impwoving buwst noise pewfowmances */
	stv0367_wwiteweg(state, W367CAB_EQU_FFE_WEAKAGE, 0x83);
	/* Impwoving ACI pewfowmances */
	stv0367_wwiteweg(state, W367CAB_IQDEM_ADJ_EN, 0x05);

	/* PWW enabwed and used */
	stv0367_wwiteweg(state, W367TEW_ANACTWW, 0x00);

	stv0367_wwiteweg(state, W367TEW_I2CWPT, (0x08 | ((5 & 0x07) << 4)));

	tew_state->pBEW = 0;
	tew_state->fiwst_wock = 0;
	tew_state->unwock_countew = 2;

	p->stwength.wen = 1;
	p->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	p->cnw.wen = 1;
	p->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	p->bwock_ewwow.wen = 1;
	p->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	wetuwn 0;
}

static const stwuct dvb_fwontend_ops stv0367ddb_ops = {
	.dewsys = { SYS_DVBC_ANNEX_A, SYS_DVBT },
	.info = {
		.name			= "ST STV0367 DDB DVB-C/T",
		.fwequency_min_hz	=  47 * MHz,
		.fwequency_max_hz	= 865 * MHz,
		.fwequency_stepsize_hz	= 166667,
		.symbow_wate_min	= 870000,
		.symbow_wate_max	= 11700000,
		.caps = /* DVB-C */
			0x400 |/* FE_CAN_QAM_4 */
			FE_CAN_QAM_16 | FE_CAN_QAM_32  |
			FE_CAN_QAM_64 | FE_CAN_QAM_128 |
			FE_CAN_QAM_256 |
			/* DVB-T */
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_TWANSMISSION_MODE_AUTO |
			FE_CAN_WECOVEW | FE_CAN_INVEWSION_AUTO |
			FE_CAN_MUTE_TS
	},
	.wewease = stv0367_wewease,
	.sweep = stv0367ddb_sweep,
	.i2c_gate_ctww = stv0367cab_gate_ctww, /* vawid fow TEW and CAB */
	.set_fwontend = stv0367ddb_set_fwontend,
	.get_fwontend = stv0367ddb_get_fwontend,
	.get_tune_settings = stv0367_get_tune_settings,
	.wead_status = stv0367ddb_wead_status,
};

stwuct dvb_fwontend *stv0367ddb_attach(const stwuct stv0367_config *config,
				   stwuct i2c_adaptew *i2c)
{
	stwuct stv0367_state *state = NUWW;
	stwuct stv0367tew_state *tew_state = NUWW;
	stwuct stv0367cab_state *cab_state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct stv0367_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;
	tew_state = kzawwoc(sizeof(stwuct stv0367tew_state), GFP_KEWNEW);
	if (tew_state == NUWW)
		goto ewwow;
	cab_state = kzawwoc(sizeof(stwuct stv0367cab_state), GFP_KEWNEW);
	if (cab_state == NUWW)
		goto ewwow;

	/* setup the state */
	state->i2c = i2c;
	state->config = config;
	state->tew_state = tew_state;
	cab_state->seawch_wange = 280000;
	cab_state->qamfec_status_weg = F367CAB_DESCW_SYNCSTATE;
	state->cab_state = cab_state;
	state->fe.ops = stv0367ddb_ops;
	state->fe.demoduwatow_pwiv = state;
	state->chip_id = stv0367_weadweg(state, W367TEW_ID);

	/* demod opewation options */
	state->use_i2c_gatectww = 0;
	state->deftabs = STV0367_DEFTAB_DDB;
	state->weinit_on_setfwontend = 0;
	state->auto_if_khz = 1;
	state->activedemod = demod_none;

	dpwintk("%s: chip_id = 0x%x\n", __func__, state->chip_id);

	/* check if the demod is thewe */
	if ((state->chip_id != 0x50) && (state->chip_id != 0x60))
		goto ewwow;

	dev_info(&i2c->dev, "Found %s with ChipID %02X at adw %02X\n",
		state->fe.ops.info.name, state->chip_id,
		config->demod_addwess);

	stv0367ddb_init(state);

	wetuwn &state->fe;

ewwow:
	kfwee(cab_state);
	kfwee(tew_state);
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(stv0367ddb_attach);

MODUWE_PAWM_DESC(debug, "Set debug");
MODUWE_PAWM_DESC(i2c_debug, "Set i2c debug");

MODUWE_AUTHOW("Igow M. Wipwianin");
MODUWE_DESCWIPTION("ST STV0367 DVB-C/T demoduwatow dwivew");
MODUWE_WICENSE("GPW");
