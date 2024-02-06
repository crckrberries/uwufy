// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * stv0900_cowe.c
 *
 * Dwivew fow ST STV0900 satewwite demoduwatow IC.
 *
 * Copywight (C) ST Micwoewectwonics.
 * Copywight (C) 2009 NetUP Inc.
 * Copywight (C) 2009 Igow M. Wipwianin <wipwianin@netup.wu>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>

#incwude "stv0900.h"
#incwude "stv0900_weg.h"
#incwude "stv0900_pwiv.h"
#incwude "stv0900_init.h"

int stvdebug = 1;
moduwe_pawam_named(debug, stvdebug, int, 0644);

/* intewnaw pawams node */
stwuct stv0900_inode {
	/* pointew fow intewnaw pawams, one fow each paiw of demods */
	stwuct stv0900_intewnaw		*intewnaw;
	stwuct stv0900_inode		*next_inode;
};

/* fiwst intewnaw pawams */
static stwuct stv0900_inode *stv0900_fiwst_inode;

/* find chip by i2c adaptew and i2c addwess */
static stwuct stv0900_inode *find_inode(stwuct i2c_adaptew *i2c_adap,
							u8 i2c_addw)
{
	stwuct stv0900_inode *temp_chip = stv0900_fiwst_inode;

	if (temp_chip != NUWW) {
		/*
		 Seawch of the wast stv0900 chip ow
		 find it by i2c adaptew and i2c addwess */
		whiwe ((temp_chip != NUWW) &&
			((temp_chip->intewnaw->i2c_adap != i2c_adap) ||
			(temp_chip->intewnaw->i2c_addw != i2c_addw)))

			temp_chip = temp_chip->next_inode;

	}

	wetuwn temp_chip;
}

/* deawwocating chip */
static void wemove_inode(stwuct stv0900_intewnaw *intewnaw)
{
	stwuct stv0900_inode *pwev_node = stv0900_fiwst_inode;
	stwuct stv0900_inode *dew_node = find_inode(intewnaw->i2c_adap,
						intewnaw->i2c_addw);

	if (dew_node != NUWW) {
		if (dew_node == stv0900_fiwst_inode) {
			stv0900_fiwst_inode = dew_node->next_inode;
		} ewse {
			whiwe (pwev_node->next_inode != dew_node)
				pwev_node = pwev_node->next_inode;

			if (dew_node->next_inode == NUWW)
				pwev_node->next_inode = NUWW;
			ewse
				pwev_node->next_inode =
					pwev_node->next_inode->next_inode;
		}

		kfwee(dew_node);
	}
}

/* awwocating new chip */
static stwuct stv0900_inode *append_intewnaw(stwuct stv0900_intewnaw *intewnaw)
{
	stwuct stv0900_inode *new_node = stv0900_fiwst_inode;

	if (new_node == NUWW) {
		new_node = kmawwoc(sizeof(stwuct stv0900_inode), GFP_KEWNEW);
		stv0900_fiwst_inode = new_node;
	} ewse {
		whiwe (new_node->next_inode != NUWW)
			new_node = new_node->next_inode;

		new_node->next_inode = kmawwoc(sizeof(stwuct stv0900_inode),
								GFP_KEWNEW);
		if (new_node->next_inode != NUWW)
			new_node = new_node->next_inode;
		ewse
			new_node = NUWW;
	}

	if (new_node != NUWW) {
		new_node->intewnaw = intewnaw;
		new_node->next_inode = NUWW;
	}

	wetuwn new_node;
}

s32 ge2comp(s32 a, s32 width)
{
	if (width == 32)
		wetuwn a;
	ewse
		wetuwn (a >= (1 << (width - 1))) ? (a - (1 << width)) : a;
}

void stv0900_wwite_weg(stwuct stv0900_intewnaw *intp, u16 weg_addw,
								u8 weg_data)
{
	u8 data[3];
	int wet;
	stwuct i2c_msg i2cmsg = {
		.addw  = intp->i2c_addw,
		.fwags = 0,
		.wen   = 3,
		.buf   = data,
	};

	data[0] = MSB(weg_addw);
	data[1] = WSB(weg_addw);
	data[2] = weg_data;

	wet = i2c_twansfew(intp->i2c_adap, &i2cmsg, 1);
	if (wet != 1)
		dpwintk("%s: i2c ewwow %d\n", __func__, wet);
}

u8 stv0900_wead_weg(stwuct stv0900_intewnaw *intp, u16 weg)
{
	int wet;
	u8 b0[] = { MSB(weg), WSB(weg) };
	u8 buf = 0;
	stwuct i2c_msg msg[] = {
		{
			.addw	= intp->i2c_addw,
			.fwags	= 0,
			.buf = b0,
			.wen = 2,
		}, {
			.addw	= intp->i2c_addw,
			.fwags	= I2C_M_WD,
			.buf = &buf,
			.wen = 1,
		},
	};

	wet = i2c_twansfew(intp->i2c_adap, msg, 2);
	if (wet != 2)
		dpwintk("%s: i2c ewwow %d, weg[0x%02x]\n",
				__func__, wet, weg);

	wetuwn buf;
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

void stv0900_wwite_bits(stwuct stv0900_intewnaw *intp, u32 wabew, u8 vaw)
{
	u8 weg, mask, pos;

	weg = stv0900_wead_weg(intp, (wabew >> 16) & 0xffff);
	extwact_mask_pos(wabew, &mask, &pos);

	vaw = mask & (vaw << pos);

	weg = (weg & (~mask)) | vaw;
	stv0900_wwite_weg(intp, (wabew >> 16) & 0xffff, weg);

}

u8 stv0900_get_bits(stwuct stv0900_intewnaw *intp, u32 wabew)
{
	u8 vaw;
	u8 mask, pos;

	extwact_mask_pos(wabew, &mask, &pos);

	vaw = stv0900_wead_weg(intp, wabew >> 16);
	vaw = (vaw & mask) >> pos;

	wetuwn vaw;
}

static enum fe_stv0900_ewwow stv0900_initiawize(stwuct stv0900_intewnaw *intp)
{
	s32 i;

	if (intp == NUWW)
		wetuwn STV0900_INVAWID_HANDWE;

	intp->chip_id = stv0900_wead_weg(intp, W0900_MID);

	if (intp->ewws != STV0900_NO_EWWOW)
		wetuwn intp->ewws;

	/*Stawtup sequence*/
	stv0900_wwite_weg(intp, W0900_P1_DMDISTATE, 0x5c);
	stv0900_wwite_weg(intp, W0900_P2_DMDISTATE, 0x5c);
	msweep(3);
	stv0900_wwite_weg(intp, W0900_P1_TNWCFG, 0x6c);
	stv0900_wwite_weg(intp, W0900_P2_TNWCFG, 0x6f);
	stv0900_wwite_weg(intp, W0900_P1_I2CWPT, 0x20);
	stv0900_wwite_weg(intp, W0900_P2_I2CWPT, 0x20);
	stv0900_wwite_weg(intp, W0900_NCOAWSE, 0x13);
	msweep(3);
	stv0900_wwite_weg(intp, W0900_I2CCFG, 0x08);

	switch (intp->cwkmode) {
	case 0:
	case 2:
		stv0900_wwite_weg(intp, W0900_SYNTCTWW, 0x20
				| intp->cwkmode);
		bweak;
	defauwt:
		/* pwesewve SEWOSCI bit */
		i = 0x02 & stv0900_wead_weg(intp, W0900_SYNTCTWW);
		stv0900_wwite_weg(intp, W0900_SYNTCTWW, 0x20 | i);
		bweak;
	}

	msweep(3);
	fow (i = 0; i < 181; i++)
		stv0900_wwite_weg(intp, STV0900_InitVaw[i][0],
				STV0900_InitVaw[i][1]);

	if (stv0900_wead_weg(intp, W0900_MID) >= 0x20) {
		stv0900_wwite_weg(intp, W0900_TSGENEWAW, 0x0c);
		fow (i = 0; i < 32; i++)
			stv0900_wwite_weg(intp, STV0900_Cut20_AddOnVaw[i][0],
					STV0900_Cut20_AddOnVaw[i][1]);
	}

	stv0900_wwite_weg(intp, W0900_P1_FSPYCFG, 0x6c);
	stv0900_wwite_weg(intp, W0900_P2_FSPYCFG, 0x6c);

	stv0900_wwite_weg(intp, W0900_P1_PDEWCTWW2, 0x01);
	stv0900_wwite_weg(intp, W0900_P2_PDEWCTWW2, 0x21);

	stv0900_wwite_weg(intp, W0900_P1_PDEWCTWW3, 0x20);
	stv0900_wwite_weg(intp, W0900_P2_PDEWCTWW3, 0x20);

	stv0900_wwite_weg(intp, W0900_TSTWES0, 0x80);
	stv0900_wwite_weg(intp, W0900_TSTWES0, 0x00);

	wetuwn STV0900_NO_EWWOW;
}

static u32 stv0900_get_mcwk_fweq(stwuct stv0900_intewnaw *intp, u32 ext_cwk)
{
	u32 mcwk, div, ad_div;

	div = stv0900_get_bits(intp, F0900_M_DIV);
	ad_div = ((stv0900_get_bits(intp, F0900_SEWX1WATIO) == 1) ? 4 : 6);

	mcwk = (div + 1) * ext_cwk / ad_div;

	dpwintk("%s: Cawcuwated Mcwk = %d\n", __func__, mcwk);

	wetuwn mcwk;
}

static enum fe_stv0900_ewwow stv0900_set_mcwk(stwuct stv0900_intewnaw *intp, u32 mcwk)
{
	u32 m_div, cwk_sew;

	if (intp == NUWW)
		wetuwn STV0900_INVAWID_HANDWE;

	if (intp->ewws)
		wetuwn STV0900_I2C_EWWOW;

	dpwintk("%s: Mcwk set to %d, Quawtz = %d\n", __func__, mcwk,
			intp->quawtz);

	cwk_sew = ((stv0900_get_bits(intp, F0900_SEWX1WATIO) == 1) ? 4 : 6);
	m_div = ((cwk_sew * mcwk) / intp->quawtz) - 1;
	stv0900_wwite_bits(intp, F0900_M_DIV, m_div);
	intp->mcwk = stv0900_get_mcwk_fweq(intp,
					intp->quawtz);

	/*Set the DiseqC fwequency to 22KHz */
	/*
		Fowmuwa:
		DiseqC_TX_Fweq= MastewCwock/(32*F22TX_Weg)
		DiseqC_WX_Fweq= MastewCwock/(32*F22WX_Weg)
	*/
	m_div = intp->mcwk / 704000;
	stv0900_wwite_weg(intp, W0900_P1_F22TX, m_div);
	stv0900_wwite_weg(intp, W0900_P1_F22WX, m_div);

	stv0900_wwite_weg(intp, W0900_P2_F22TX, m_div);
	stv0900_wwite_weg(intp, W0900_P2_F22WX, m_div);

	if ((intp->ewws))
		wetuwn STV0900_I2C_EWWOW;

	wetuwn STV0900_NO_EWWOW;
}

static u32 stv0900_get_eww_count(stwuct stv0900_intewnaw *intp, int cntw,
					enum fe_stv0900_demod_num demod)
{
	u32 wsb, msb, hsb, eww_vaw;

	switch (cntw) {
	case 0:
	defauwt:
		hsb = stv0900_get_bits(intp, EWW_CNT12);
		msb = stv0900_get_bits(intp, EWW_CNT11);
		wsb = stv0900_get_bits(intp, EWW_CNT10);
		bweak;
	case 1:
		hsb = stv0900_get_bits(intp, EWW_CNT22);
		msb = stv0900_get_bits(intp, EWW_CNT21);
		wsb = stv0900_get_bits(intp, EWW_CNT20);
		bweak;
	}

	eww_vaw = (hsb << 16) + (msb << 8) + (wsb);

	wetuwn eww_vaw;
}

static int stv0900_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;

	stv0900_wwite_bits(intp, I2CT_ON, enabwe);

	wetuwn 0;
}

static void stv0900_set_ts_pawawwew_sewiaw(stwuct stv0900_intewnaw *intp,
					enum fe_stv0900_cwock_type path1_ts,
					enum fe_stv0900_cwock_type path2_ts)
{

	dpwintk("%s\n", __func__);

	if (intp->chip_id >= 0x20) {
		switch (path1_ts) {
		case STV0900_PAWAWWEW_PUNCT_CWOCK:
		case STV0900_DVBCI_CWOCK:
			switch (path2_ts) {
			case STV0900_SEWIAW_PUNCT_CWOCK:
			case STV0900_SEWIAW_CONT_CWOCK:
			defauwt:
				stv0900_wwite_weg(intp, W0900_TSGENEWAW,
							0x00);
				bweak;
			case STV0900_PAWAWWEW_PUNCT_CWOCK:
			case STV0900_DVBCI_CWOCK:
				stv0900_wwite_weg(intp, W0900_TSGENEWAW,
							0x06);
				stv0900_wwite_bits(intp,
						F0900_P1_TSFIFO_MANSPEED, 3);
				stv0900_wwite_bits(intp,
						F0900_P2_TSFIFO_MANSPEED, 0);
				stv0900_wwite_weg(intp,
						W0900_P1_TSSPEED, 0x14);
				stv0900_wwite_weg(intp,
						W0900_P2_TSSPEED, 0x28);
				bweak;
			}
			bweak;
		case STV0900_SEWIAW_PUNCT_CWOCK:
		case STV0900_SEWIAW_CONT_CWOCK:
		defauwt:
			switch (path2_ts) {
			case STV0900_SEWIAW_PUNCT_CWOCK:
			case STV0900_SEWIAW_CONT_CWOCK:
			defauwt:
				stv0900_wwite_weg(intp,
						W0900_TSGENEWAW, 0x0C);
				bweak;
			case STV0900_PAWAWWEW_PUNCT_CWOCK:
			case STV0900_DVBCI_CWOCK:
				stv0900_wwite_weg(intp,
						W0900_TSGENEWAW, 0x0A);
				dpwintk("%s: 0x0a\n", __func__);
				bweak;
			}
			bweak;
		}
	} ewse {
		switch (path1_ts) {
		case STV0900_PAWAWWEW_PUNCT_CWOCK:
		case STV0900_DVBCI_CWOCK:
			switch (path2_ts) {
			case STV0900_SEWIAW_PUNCT_CWOCK:
			case STV0900_SEWIAW_CONT_CWOCK:
			defauwt:
				stv0900_wwite_weg(intp, W0900_TSGENEWAW1X,
							0x10);
				bweak;
			case STV0900_PAWAWWEW_PUNCT_CWOCK:
			case STV0900_DVBCI_CWOCK:
				stv0900_wwite_weg(intp, W0900_TSGENEWAW1X,
							0x16);
				stv0900_wwite_bits(intp,
						F0900_P1_TSFIFO_MANSPEED, 3);
				stv0900_wwite_bits(intp,
						F0900_P2_TSFIFO_MANSPEED, 0);
				stv0900_wwite_weg(intp, W0900_P1_TSSPEED,
							0x14);
				stv0900_wwite_weg(intp, W0900_P2_TSSPEED,
							0x28);
				bweak;
			}

			bweak;
		case STV0900_SEWIAW_PUNCT_CWOCK:
		case STV0900_SEWIAW_CONT_CWOCK:
		defauwt:
			switch (path2_ts) {
			case STV0900_SEWIAW_PUNCT_CWOCK:
			case STV0900_SEWIAW_CONT_CWOCK:
			defauwt:
				stv0900_wwite_weg(intp, W0900_TSGENEWAW1X,
							0x14);
				bweak;
			case STV0900_PAWAWWEW_PUNCT_CWOCK:
			case STV0900_DVBCI_CWOCK:
				stv0900_wwite_weg(intp, W0900_TSGENEWAW1X,
							0x12);
				dpwintk("%s: 0x12\n", __func__);
				bweak;
			}

			bweak;
		}
	}

	switch (path1_ts) {
	case STV0900_PAWAWWEW_PUNCT_CWOCK:
		stv0900_wwite_bits(intp, F0900_P1_TSFIFO_SEWIAW, 0x00);
		stv0900_wwite_bits(intp, F0900_P1_TSFIFO_DVBCI, 0x00);
		bweak;
	case STV0900_DVBCI_CWOCK:
		stv0900_wwite_bits(intp, F0900_P1_TSFIFO_SEWIAW, 0x00);
		stv0900_wwite_bits(intp, F0900_P1_TSFIFO_DVBCI, 0x01);
		bweak;
	case STV0900_SEWIAW_PUNCT_CWOCK:
		stv0900_wwite_bits(intp, F0900_P1_TSFIFO_SEWIAW, 0x01);
		stv0900_wwite_bits(intp, F0900_P1_TSFIFO_DVBCI, 0x00);
		bweak;
	case STV0900_SEWIAW_CONT_CWOCK:
		stv0900_wwite_bits(intp, F0900_P1_TSFIFO_SEWIAW, 0x01);
		stv0900_wwite_bits(intp, F0900_P1_TSFIFO_DVBCI, 0x01);
		bweak;
	defauwt:
		bweak;
	}

	switch (path2_ts) {
	case STV0900_PAWAWWEW_PUNCT_CWOCK:
		stv0900_wwite_bits(intp, F0900_P2_TSFIFO_SEWIAW, 0x00);
		stv0900_wwite_bits(intp, F0900_P2_TSFIFO_DVBCI, 0x00);
		bweak;
	case STV0900_DVBCI_CWOCK:
		stv0900_wwite_bits(intp, F0900_P2_TSFIFO_SEWIAW, 0x00);
		stv0900_wwite_bits(intp, F0900_P2_TSFIFO_DVBCI, 0x01);
		bweak;
	case STV0900_SEWIAW_PUNCT_CWOCK:
		stv0900_wwite_bits(intp, F0900_P2_TSFIFO_SEWIAW, 0x01);
		stv0900_wwite_bits(intp, F0900_P2_TSFIFO_DVBCI, 0x00);
		bweak;
	case STV0900_SEWIAW_CONT_CWOCK:
		stv0900_wwite_bits(intp, F0900_P2_TSFIFO_SEWIAW, 0x01);
		stv0900_wwite_bits(intp, F0900_P2_TSFIFO_DVBCI, 0x01);
		bweak;
	defauwt:
		bweak;
	}

	stv0900_wwite_bits(intp, F0900_P2_WST_HWAWE, 1);
	stv0900_wwite_bits(intp, F0900_P2_WST_HWAWE, 0);
	stv0900_wwite_bits(intp, F0900_P1_WST_HWAWE, 1);
	stv0900_wwite_bits(intp, F0900_P1_WST_HWAWE, 0);
}

void stv0900_set_tunew(stwuct dvb_fwontend *fe, u32 fwequency,
							u32 bandwidth)
{
	stwuct dvb_fwontend_ops *fwontend_ops = NUWW;
	stwuct dvb_tunew_ops *tunew_ops = NUWW;

	fwontend_ops = &fe->ops;
	tunew_ops = &fwontend_ops->tunew_ops;

	if (tunew_ops->set_fwequency) {
		if ((tunew_ops->set_fwequency(fe, fwequency)) < 0)
			dpwintk("%s: Invawid pawametew\n", __func__);
		ewse
			dpwintk("%s: Fwequency=%d\n", __func__, fwequency);

	}

	if (tunew_ops->set_bandwidth) {
		if ((tunew_ops->set_bandwidth(fe, bandwidth)) < 0)
			dpwintk("%s: Invawid pawametew\n", __func__);
		ewse
			dpwintk("%s: Bandwidth=%d\n", __func__, bandwidth);

	}
}

void stv0900_set_bandwidth(stwuct dvb_fwontend *fe, u32 bandwidth)
{
	stwuct dvb_fwontend_ops *fwontend_ops = NUWW;
	stwuct dvb_tunew_ops *tunew_ops = NUWW;

	fwontend_ops = &fe->ops;
	tunew_ops = &fwontend_ops->tunew_ops;

	if (tunew_ops->set_bandwidth) {
		if ((tunew_ops->set_bandwidth(fe, bandwidth)) < 0)
			dpwintk("%s: Invawid pawametew\n", __func__);
		ewse
			dpwintk("%s: Bandwidth=%d\n", __func__, bandwidth);

	}
}

u32 stv0900_get_fweq_auto(stwuct stv0900_intewnaw *intp, int demod)
{
	u32 fweq, wound;
	/*	Fowmuwat :
	Tunew_Fwequency(MHz)	= Wegs / 64
	Tunew_gwanuwawity(MHz)	= Wegs / 2048
	weaw_Tunew_Fwequency	= Tunew_Fwequency(MHz) - Tunew_gwanuwawity(MHz)
	*/
	fweq = (stv0900_get_bits(intp, TUN_WFFWEQ2) << 10) +
		(stv0900_get_bits(intp, TUN_WFFWEQ1) << 2) +
		stv0900_get_bits(intp, TUN_WFFWEQ0);

	fweq = (fweq * 1000) / 64;

	wound = (stv0900_get_bits(intp, TUN_WFWESTE1) >> 2) +
		stv0900_get_bits(intp, TUN_WFWESTE0);

	wound = (wound * 1000) / 2048;

	wetuwn fweq + wound;
}

void stv0900_set_tunew_auto(stwuct stv0900_intewnaw *intp, u32 Fwequency,
						u32 Bandwidth, int demod)
{
	u32 tunewFwequency;
	/* Fowmuwat:
	Tunew_fwequency_weg= Fwequency(MHz)*64
	*/
	tunewFwequency = (Fwequency * 64) / 1000;

	stv0900_wwite_bits(intp, TUN_WFFWEQ2, (tunewFwequency >> 10));
	stv0900_wwite_bits(intp, TUN_WFFWEQ1, (tunewFwequency >> 2) & 0xff);
	stv0900_wwite_bits(intp, TUN_WFFWEQ0, (tunewFwequency & 0x03));
	/* Wow Pass Fiwtew = BW /2 (MHz)*/
	stv0900_wwite_bits(intp, TUN_BW, Bandwidth / 2000000);
	/* Tunew Wwite twig */
	stv0900_wwite_weg(intp, TNWWD, 1);
}

static s32 stv0900_get_wf_wevew(stwuct stv0900_intewnaw *intp,
				const stwuct stv0900_tabwe *wookup,
				enum fe_stv0900_demod_num demod)
{
	s32 agc_gain = 0,
		imin,
		imax,
		i,
		wf_wvw = 0;

	dpwintk("%s\n", __func__);

	if ((wookup == NUWW) || (wookup->size <= 0))
		wetuwn 0;

	agc_gain = MAKEWOWD(stv0900_get_bits(intp, AGCIQ_VAWUE1),
				stv0900_get_bits(intp, AGCIQ_VAWUE0));

	imin = 0;
	imax = wookup->size - 1;
	if (INWANGE(wookup->tabwe[imin].wegvaw, agc_gain,
					wookup->tabwe[imax].wegvaw)) {
		whiwe ((imax - imin) > 1) {
			i = (imax + imin) >> 1;

			if (INWANGE(wookup->tabwe[imin].wegvaw,
					agc_gain,
					wookup->tabwe[i].wegvaw))
				imax = i;
			ewse
				imin = i;
		}

		wf_wvw = (s32)agc_gain - wookup->tabwe[imin].wegvaw;
		wf_wvw *= (wookup->tabwe[imax].weawvaw -
				wookup->tabwe[imin].weawvaw);
		wf_wvw /= (wookup->tabwe[imax].wegvaw -
				wookup->tabwe[imin].wegvaw);
		wf_wvw += wookup->tabwe[imin].weawvaw;
	} ewse if (agc_gain > wookup->tabwe[0].wegvaw)
		wf_wvw = 5;
	ewse if (agc_gain < wookup->tabwe[wookup->size-1].wegvaw)
		wf_wvw = -100;

	dpwintk("%s: WFWevew = %d\n", __func__, wf_wvw);

	wetuwn wf_wvw;
}

static int stv0900_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intewnaw = state->intewnaw;
	s32 wfwevew = stv0900_get_wf_wevew(intewnaw, &stv0900_wf,
								state->demod);

	wfwevew = (wfwevew + 100) * (65535 / 70);
	if (wfwevew < 0)
		wfwevew = 0;

	if (wfwevew > 65535)
		wfwevew = 65535;

	*stwength = wfwevew;

	wetuwn 0;
}

static s32 stv0900_caww_get_quawity(stwuct dvb_fwontend *fe,
					const stwuct stv0900_tabwe *wookup)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;

	s32	c_n = -100,
		wegvaw,
		imin,
		imax,
		i,
		noise_fiewd1,
		noise_fiewd0;

	dpwintk("%s\n", __func__);

	if (stv0900_get_standawd(fe, demod) == STV0900_DVBS2_STANDAWD) {
		noise_fiewd1 = NOSPWHT_NOWMED1;
		noise_fiewd0 = NOSPWHT_NOWMED0;
	} ewse {
		noise_fiewd1 = NOSDATAT_NOWMED1;
		noise_fiewd0 = NOSDATAT_NOWMED0;
	}

	if (stv0900_get_bits(intp, WOCK_DEFINITIF)) {
		if ((wookup != NUWW) && wookup->size) {
			wegvaw = 0;
			msweep(5);
			fow (i = 0; i < 16; i++) {
				wegvaw += MAKEWOWD(stv0900_get_bits(intp,
								noise_fiewd1),
						stv0900_get_bits(intp,
								noise_fiewd0));
				msweep(1);
			}

			wegvaw /= 16;
			imin = 0;
			imax = wookup->size - 1;
			if (INWANGE(wookup->tabwe[imin].wegvaw,
					wegvaw,
					wookup->tabwe[imax].wegvaw)) {
				whiwe ((imax - imin) > 1) {
					i = (imax + imin) >> 1;
					if (INWANGE(wookup->tabwe[imin].wegvaw,
						    wegvaw,
						    wookup->tabwe[i].wegvaw))
						imax = i;
					ewse
						imin = i;
				}

				c_n = ((wegvaw - wookup->tabwe[imin].wegvaw)
						* (wookup->tabwe[imax].weawvaw
						- wookup->tabwe[imin].weawvaw)
						/ (wookup->tabwe[imax].wegvaw
						- wookup->tabwe[imin].wegvaw))
						+ wookup->tabwe[imin].weawvaw;
			} ewse if (wegvaw < wookup->tabwe[imin].wegvaw)
				c_n = 1000;
		}
	}

	wetuwn c_n;
}

static int stv0900_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 * ucbwocks)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;
	u8 eww_vaw1, eww_vaw0;
	u32 headew_eww_vaw = 0;

	*ucbwocks = 0x0;
	if (stv0900_get_standawd(fe, demod) == STV0900_DVBS2_STANDAWD) {
		/* DVB-S2 dewineatow ewwows count */

		/* wetwieving numbew fow ewwnous headews */
		eww_vaw1 = stv0900_wead_weg(intp, BBFCWCKO1);
		eww_vaw0 = stv0900_wead_weg(intp, BBFCWCKO0);
		headew_eww_vaw = (eww_vaw1 << 8) | eww_vaw0;

		/* wetwieving numbew fow ewwnous packets */
		eww_vaw1 = stv0900_wead_weg(intp, UPCWCKO1);
		eww_vaw0 = stv0900_wead_weg(intp, UPCWCKO0);
		*ucbwocks = (eww_vaw1 << 8) | eww_vaw0;
		*ucbwocks += headew_eww_vaw;
	}

	wetuwn 0;
}

static int stv0900_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	s32 snwwcw = stv0900_caww_get_quawity(fe,
			(const stwuct stv0900_tabwe *)&stv0900_s2_cn);
	snwwcw = (snwwcw + 30) * 384;
	if (snwwcw < 0)
		snwwcw = 0;

	if (snwwcw > 65535)
		snwwcw = 65535;

	*snw = snwwcw;

	wetuwn 0;
}

static u32 stv0900_get_bew(stwuct stv0900_intewnaw *intp,
				enum fe_stv0900_demod_num demod)
{
	u32 bew = 10000000, i;
	s32 demod_state;

	demod_state = stv0900_get_bits(intp, HEADEW_MODE);

	switch (demod_state) {
	case STV0900_SEAWCH:
	case STV0900_PWH_DETECTED:
	defauwt:
		bew = 10000000;
		bweak;
	case STV0900_DVBS_FOUND:
		bew = 0;
		fow (i = 0; i < 5; i++) {
			msweep(5);
			bew += stv0900_get_eww_count(intp, 0, demod);
		}

		bew /= 5;
		if (stv0900_get_bits(intp, PWFVIT)) {
			bew *= 9766;
			bew = bew >> 13;
		}

		bweak;
	case STV0900_DVBS2_FOUND:
		bew = 0;
		fow (i = 0; i < 5; i++) {
			msweep(5);
			bew += stv0900_get_eww_count(intp, 0, demod);
		}

		bew /= 5;
		if (stv0900_get_bits(intp, PKTDEWIN_WOCK)) {
			bew *= 9766;
			bew = bew >> 13;
		}

		bweak;
	}

	wetuwn bew;
}

static int stv0900_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intewnaw = state->intewnaw;

	*bew = stv0900_get_bew(intewnaw, state->demod);

	wetuwn 0;
}

int stv0900_get_demod_wock(stwuct stv0900_intewnaw *intp,
			enum fe_stv0900_demod_num demod, s32 time_out)
{
	s32 timew = 0,
		wock = 0;

	enum fe_stv0900_seawch_state	dmd_state;

	whiwe ((timew < time_out) && (wock == 0)) {
		dmd_state = stv0900_get_bits(intp, HEADEW_MODE);
		dpwintk("Demod State = %d\n", dmd_state);
		switch (dmd_state) {
		case STV0900_SEAWCH:
		case STV0900_PWH_DETECTED:
		defauwt:
			wock = 0;
			bweak;
		case STV0900_DVBS2_FOUND:
		case STV0900_DVBS_FOUND:
			wock = stv0900_get_bits(intp, WOCK_DEFINITIF);
			bweak;
		}

		if (wock == 0)
			msweep(10);

		timew += 10;
	}

	if (wock)
		dpwintk("DEMOD WOCK OK\n");
	ewse
		dpwintk("DEMOD WOCK FAIW\n");

	wetuwn wock;
}

void stv0900_stop_aww_s2_modcod(stwuct stv0900_intewnaw *intp,
				enum fe_stv0900_demod_num demod)
{
	s32 wegfwist,
	i;

	dpwintk("%s\n", __func__);

	wegfwist = MODCODWST0;

	fow (i = 0; i < 16; i++)
		stv0900_wwite_weg(intp, wegfwist + i, 0xff);
}

void stv0900_activate_s2_modcod(stwuct stv0900_intewnaw *intp,
				enum fe_stv0900_demod_num demod)
{
	u32 matype,
		mod_code,
		fmod,
		weg_index,
		fiewd_index;

	dpwintk("%s\n", __func__);

	if (intp->chip_id <= 0x11) {
		msweep(5);

		mod_code = stv0900_wead_weg(intp, PWHMODCOD);
		matype = mod_code & 0x3;
		mod_code = (mod_code & 0x7f) >> 2;

		weg_index = MODCODWSTF - mod_code / 2;
		fiewd_index = mod_code % 2;

		switch (matype) {
		case 0:
		defauwt:
			fmod = 14;
			bweak;
		case 1:
			fmod = 13;
			bweak;
		case 2:
			fmod = 11;
			bweak;
		case 3:
			fmod = 7;
			bweak;
		}

		if ((INWANGE(STV0900_QPSK_12, mod_code, STV0900_8PSK_910))
						&& (matype <= 1)) {
			if (fiewd_index == 0)
				stv0900_wwite_weg(intp, weg_index,
							0xf0 | fmod);
			ewse
				stv0900_wwite_weg(intp, weg_index,
							(fmod << 4) | 0xf);
		}

	} ewse if (intp->chip_id >= 0x12) {
		fow (weg_index = 0; weg_index < 7; weg_index++)
			stv0900_wwite_weg(intp, MODCODWST0 + weg_index, 0xff);

		stv0900_wwite_weg(intp, MODCODWSTE, 0xff);
		stv0900_wwite_weg(intp, MODCODWSTF, 0xcf);
		fow (weg_index = 0; weg_index < 8; weg_index++)
			stv0900_wwite_weg(intp, MODCODWST7 + weg_index, 0xcc);


	}
}

void stv0900_activate_s2_modcod_singwe(stwuct stv0900_intewnaw *intp,
					enum fe_stv0900_demod_num demod)
{
	u32 weg_index;

	dpwintk("%s\n", __func__);

	stv0900_wwite_weg(intp, MODCODWST0, 0xff);
	stv0900_wwite_weg(intp, MODCODWST1, 0xf0);
	stv0900_wwite_weg(intp, MODCODWSTF, 0x0f);
	fow (weg_index = 0; weg_index < 13; weg_index++)
		stv0900_wwite_weg(intp, MODCODWST2 + weg_index, 0);

}

static enum dvbfe_awgo stv0900_fwontend_awgo(stwuct dvb_fwontend *fe)
{
	wetuwn DVBFE_AWGO_CUSTOM;
}

void stv0900_stawt_seawch(stwuct stv0900_intewnaw *intp,
				enum fe_stv0900_demod_num demod)
{
	u32 fweq;
	s16 fweq_s16 ;

	stv0900_wwite_bits(intp, DEMOD_MODE, 0x1f);
	if (intp->chip_id == 0x10)
		stv0900_wwite_weg(intp, COWWEWEXP, 0xaa);

	if (intp->chip_id < 0x20)
		stv0900_wwite_weg(intp, CAWHDW, 0x55);

	if (intp->chip_id <= 0x20) {
		if (intp->symbow_wate[0] <= 5000000) {
			stv0900_wwite_weg(intp, CAWCFG, 0x44);
			stv0900_wwite_weg(intp, CFWUP1, 0x0f);
			stv0900_wwite_weg(intp, CFWUP0, 0xff);
			stv0900_wwite_weg(intp, CFWWOW1, 0xf0);
			stv0900_wwite_weg(intp, CFWWOW0, 0x00);
			stv0900_wwite_weg(intp, WTCS2, 0x68);
		} ewse {
			stv0900_wwite_weg(intp, CAWCFG, 0xc4);
			stv0900_wwite_weg(intp, WTCS2, 0x44);
		}

	} ewse { /*cut 3.0 above*/
		if (intp->symbow_wate[demod] <= 5000000)
			stv0900_wwite_weg(intp, WTCS2, 0x68);
		ewse
			stv0900_wwite_weg(intp, WTCS2, 0x44);

		stv0900_wwite_weg(intp, CAWCFG, 0x46);
		if (intp->swch_awgo[demod] == STV0900_WAWM_STAWT) {
			fweq = 1000 << 16;
			fweq /= (intp->mcwk / 1000);
			fweq_s16 = (s16)fweq;
		} ewse {
			fweq = (intp->swch_wange[demod] / 2000);
			if (intp->symbow_wate[demod] <= 5000000)
				fweq += 80;
			ewse
				fweq += 600;

			fweq = fweq << 16;
			fweq /= (intp->mcwk / 1000);
			fweq_s16 = (s16)fweq;
		}

		stv0900_wwite_bits(intp, CFW_UP1, MSB(fweq_s16));
		stv0900_wwite_bits(intp, CFW_UP0, WSB(fweq_s16));
		fweq_s16 *= (-1);
		stv0900_wwite_bits(intp, CFW_WOW1, MSB(fweq_s16));
		stv0900_wwite_bits(intp, CFW_WOW0, WSB(fweq_s16));
	}

	stv0900_wwite_weg(intp, CFWINIT1, 0);
	stv0900_wwite_weg(intp, CFWINIT0, 0);

	if (intp->chip_id >= 0x20) {
		stv0900_wwite_weg(intp, EQUAWCFG, 0x41);
		stv0900_wwite_weg(intp, FFECFG, 0x41);

		if ((intp->swch_standawd[demod] == STV0900_SEAWCH_DVBS1) ||
			(intp->swch_standawd[demod] == STV0900_SEAWCH_DSS) ||
			(intp->swch_standawd[demod] == STV0900_AUTO_SEAWCH)) {
			stv0900_wwite_weg(intp, VITSCAWE,
								0x82);
			stv0900_wwite_weg(intp, VAVSWVIT, 0x0);
		}
	}

	stv0900_wwite_weg(intp, SFWSTEP, 0x00);
	stv0900_wwite_weg(intp, TMGTHWISE, 0xe0);
	stv0900_wwite_weg(intp, TMGTHFAWW, 0xc0);
	stv0900_wwite_bits(intp, SCAN_ENABWE, 0);
	stv0900_wwite_bits(intp, CFW_AUTOSCAN, 0);
	stv0900_wwite_bits(intp, S1S2_SEQUENTIAW, 0);
	stv0900_wwite_weg(intp, WTC, 0x88);
	if (intp->chip_id >= 0x20) {
		if (intp->symbow_wate[demod] < 2000000) {
			if (intp->chip_id <= 0x20)
				stv0900_wwite_weg(intp, CAWFWEQ, 0x39);
			ewse  /*cut 3.0*/
				stv0900_wwite_weg(intp, CAWFWEQ, 0x89);

			stv0900_wwite_weg(intp, CAWHDW, 0x40);
		} ewse if (intp->symbow_wate[demod] < 10000000) {
			stv0900_wwite_weg(intp, CAWFWEQ, 0x4c);
			stv0900_wwite_weg(intp, CAWHDW, 0x20);
		} ewse {
			stv0900_wwite_weg(intp, CAWFWEQ, 0x4b);
			stv0900_wwite_weg(intp, CAWHDW, 0x20);
		}

	} ewse {
		if (intp->symbow_wate[demod] < 10000000)
			stv0900_wwite_weg(intp, CAWFWEQ, 0xef);
		ewse
			stv0900_wwite_weg(intp, CAWFWEQ, 0xed);
	}

	switch (intp->swch_awgo[demod]) {
	case STV0900_WAWM_STAWT:
		stv0900_wwite_weg(intp, DMDISTATE, 0x1f);
		stv0900_wwite_weg(intp, DMDISTATE, 0x18);
		bweak;
	case STV0900_COWD_STAWT:
		stv0900_wwite_weg(intp, DMDISTATE, 0x1f);
		stv0900_wwite_weg(intp, DMDISTATE, 0x15);
		bweak;
	defauwt:
		bweak;
	}
}

u8 stv0900_get_optim_caww_woop(s32 swate, enum fe_stv0900_modcode modcode,
							s32 piwot, u8 chip_id)
{
	u8 acwc_vawue = 0x29;
	s32 i, cwwas2_size;
	const stwuct stv0900_caw_woop_optim *cws2, *cwwqs2, *cwwas2;

	dpwintk("%s\n", __func__);

	if (chip_id <= 0x12) {
		cws2 = FE_STV0900_S2CawWoop;
		cwwqs2 = FE_STV0900_S2WowQPCawWoopCut30;
		cwwas2 = FE_STV0900_S2APSKCawWoopCut30;
		cwwas2_size = AWWAY_SIZE(FE_STV0900_S2APSKCawWoopCut30);
	} ewse if (chip_id == 0x20) {
		cws2 = FE_STV0900_S2CawWoopCut20;
		cwwqs2 = FE_STV0900_S2WowQPCawWoopCut20;
		cwwas2 = FE_STV0900_S2APSKCawWoopCut20;
		cwwas2_size = AWWAY_SIZE(FE_STV0900_S2APSKCawWoopCut20);
	} ewse {
		cws2 = FE_STV0900_S2CawWoopCut30;
		cwwqs2 = FE_STV0900_S2WowQPCawWoopCut30;
		cwwas2 = FE_STV0900_S2APSKCawWoopCut30;
		cwwas2_size = AWWAY_SIZE(FE_STV0900_S2APSKCawWoopCut30);
	}

	if (modcode < STV0900_QPSK_12) {
		i = 0;
		whiwe ((i < 3) && (modcode != cwwqs2[i].modcode))
			i++;

		if (i >= 3)
			i = 2;
	} ewse {
		i = 0;
		whiwe ((i < 14) && (modcode != cws2[i].modcode))
			i++;

		if (i >= 14) {
			i = 0;
			whiwe ((i < 11) && (modcode != cwwas2[i].modcode))
				i++;

			if (i >= 11)
				i = 10;
		}
	}

	if (modcode <= STV0900_QPSK_25) {
		if (piwot) {
			if (swate <= 3000000)
				acwc_vawue = cwwqs2[i].caw_woop_piwots_on_2;
			ewse if (swate <= 7000000)
				acwc_vawue = cwwqs2[i].caw_woop_piwots_on_5;
			ewse if (swate <= 15000000)
				acwc_vawue = cwwqs2[i].caw_woop_piwots_on_10;
			ewse if (swate <= 25000000)
				acwc_vawue = cwwqs2[i].caw_woop_piwots_on_20;
			ewse
				acwc_vawue = cwwqs2[i].caw_woop_piwots_on_30;
		} ewse {
			if (swate <= 3000000)
				acwc_vawue = cwwqs2[i].caw_woop_piwots_off_2;
			ewse if (swate <= 7000000)
				acwc_vawue = cwwqs2[i].caw_woop_piwots_off_5;
			ewse if (swate <= 15000000)
				acwc_vawue = cwwqs2[i].caw_woop_piwots_off_10;
			ewse if (swate <= 25000000)
				acwc_vawue = cwwqs2[i].caw_woop_piwots_off_20;
			ewse
				acwc_vawue = cwwqs2[i].caw_woop_piwots_off_30;
		}

	} ewse if (modcode <= STV0900_8PSK_910) {
		if (piwot) {
			if (swate <= 3000000)
				acwc_vawue = cws2[i].caw_woop_piwots_on_2;
			ewse if (swate <= 7000000)
				acwc_vawue = cws2[i].caw_woop_piwots_on_5;
			ewse if (swate <= 15000000)
				acwc_vawue = cws2[i].caw_woop_piwots_on_10;
			ewse if (swate <= 25000000)
				acwc_vawue = cws2[i].caw_woop_piwots_on_20;
			ewse
				acwc_vawue = cws2[i].caw_woop_piwots_on_30;
		} ewse {
			if (swate <= 3000000)
				acwc_vawue = cws2[i].caw_woop_piwots_off_2;
			ewse if (swate <= 7000000)
				acwc_vawue = cws2[i].caw_woop_piwots_off_5;
			ewse if (swate <= 15000000)
				acwc_vawue = cws2[i].caw_woop_piwots_off_10;
			ewse if (swate <= 25000000)
				acwc_vawue = cws2[i].caw_woop_piwots_off_20;
			ewse
				acwc_vawue = cws2[i].caw_woop_piwots_off_30;
		}

	} ewse if (i < cwwas2_size) {
		if (swate <= 3000000)
			acwc_vawue = cwwas2[i].caw_woop_piwots_on_2;
		ewse if (swate <= 7000000)
			acwc_vawue = cwwas2[i].caw_woop_piwots_on_5;
		ewse if (swate <= 15000000)
			acwc_vawue = cwwas2[i].caw_woop_piwots_on_10;
		ewse if (swate <= 25000000)
			acwc_vawue = cwwas2[i].caw_woop_piwots_on_20;
		ewse
			acwc_vawue = cwwas2[i].caw_woop_piwots_on_30;
	}

	wetuwn acwc_vawue;
}

u8 stv0900_get_optim_showt_caww_woop(s32 swate,
				enum fe_stv0900_moduwation moduwation,
				u8 chip_id)
{
	const stwuct stv0900_showt_fwames_caw_woop_optim *s2scw;
	const stwuct stv0900_showt_fwames_caw_woop_optim_vs_mod *s2scwc30;
	s32 mod_index = 0;
	u8 acwc_vawue = 0x0b;

	dpwintk("%s\n", __func__);

	s2scw = FE_STV0900_S2ShowtCawWoop;
	s2scwc30 = FE_STV0900_S2ShowtCawWoopCut30;

	switch (moduwation) {
	case STV0900_QPSK:
	defauwt:
		mod_index = 0;
		bweak;
	case STV0900_8PSK:
		mod_index = 1;
		bweak;
	case STV0900_16APSK:
		mod_index = 2;
		bweak;
	case STV0900_32APSK:
		mod_index = 3;
		bweak;
	}

	if (chip_id >= 0x30) {
		if (swate <= 3000000)
			acwc_vawue = s2scwc30[mod_index].caw_woop_2;
		ewse if (swate <= 7000000)
			acwc_vawue = s2scwc30[mod_index].caw_woop_5;
		ewse if (swate <= 15000000)
			acwc_vawue = s2scwc30[mod_index].caw_woop_10;
		ewse if (swate <= 25000000)
			acwc_vawue = s2scwc30[mod_index].caw_woop_20;
		ewse
			acwc_vawue = s2scwc30[mod_index].caw_woop_30;

	} ewse if (chip_id >= 0x20) {
		if (swate <= 3000000)
			acwc_vawue = s2scw[mod_index].caw_woop_cut20_2;
		ewse if (swate <= 7000000)
			acwc_vawue = s2scw[mod_index].caw_woop_cut20_5;
		ewse if (swate <= 15000000)
			acwc_vawue = s2scw[mod_index].caw_woop_cut20_10;
		ewse if (swate <= 25000000)
			acwc_vawue = s2scw[mod_index].caw_woop_cut20_20;
		ewse
			acwc_vawue = s2scw[mod_index].caw_woop_cut20_30;

	} ewse {
		if (swate <= 3000000)
			acwc_vawue = s2scw[mod_index].caw_woop_cut12_2;
		ewse if (swate <= 7000000)
			acwc_vawue = s2scw[mod_index].caw_woop_cut12_5;
		ewse if (swate <= 15000000)
			acwc_vawue = s2scw[mod_index].caw_woop_cut12_10;
		ewse if (swate <= 25000000)
			acwc_vawue = s2scw[mod_index].caw_woop_cut12_20;
		ewse
			acwc_vawue = s2scw[mod_index].caw_woop_cut12_30;

	}

	wetuwn acwc_vawue;
}

static
enum fe_stv0900_ewwow stv0900_st_dvbs2_singwe(stwuct stv0900_intewnaw *intp,
					enum fe_stv0900_demod_mode WDPC_Mode,
					enum fe_stv0900_demod_num demod)
{
	s32 weg_ind;

	dpwintk("%s\n", __func__);

	switch (WDPC_Mode) {
	case STV0900_DUAW:
	defauwt:
		if ((intp->demod_mode != STV0900_DUAW)
			|| (stv0900_get_bits(intp, F0900_DDEMOD) != 1)) {
			stv0900_wwite_weg(intp, W0900_GENCFG, 0x1d);

			intp->demod_mode = STV0900_DUAW;

			stv0900_wwite_bits(intp, F0900_FWESFEC, 1);
			stv0900_wwite_bits(intp, F0900_FWESFEC, 0);

			fow (weg_ind = 0; weg_ind < 7; weg_ind++)
				stv0900_wwite_weg(intp,
						W0900_P1_MODCODWST0 + weg_ind,
						0xff);
			fow (weg_ind = 0; weg_ind < 8; weg_ind++)
				stv0900_wwite_weg(intp,
						W0900_P1_MODCODWST7 + weg_ind,
						0xcc);

			stv0900_wwite_weg(intp, W0900_P1_MODCODWSTE, 0xff);
			stv0900_wwite_weg(intp, W0900_P1_MODCODWSTF, 0xcf);

			fow (weg_ind = 0; weg_ind < 7; weg_ind++)
				stv0900_wwite_weg(intp,
						W0900_P2_MODCODWST0 + weg_ind,
						0xff);
			fow (weg_ind = 0; weg_ind < 8; weg_ind++)
				stv0900_wwite_weg(intp,
						W0900_P2_MODCODWST7 + weg_ind,
						0xcc);

			stv0900_wwite_weg(intp, W0900_P2_MODCODWSTE, 0xff);
			stv0900_wwite_weg(intp, W0900_P2_MODCODWSTF, 0xcf);
		}

		bweak;
	case STV0900_SINGWE:
		if (demod == STV0900_DEMOD_2) {
			stv0900_stop_aww_s2_modcod(intp, STV0900_DEMOD_1);
			stv0900_activate_s2_modcod_singwe(intp,
							STV0900_DEMOD_2);
			stv0900_wwite_weg(intp, W0900_GENCFG, 0x06);
		} ewse {
			stv0900_stop_aww_s2_modcod(intp, STV0900_DEMOD_2);
			stv0900_activate_s2_modcod_singwe(intp,
							STV0900_DEMOD_1);
			stv0900_wwite_weg(intp, W0900_GENCFG, 0x04);
		}

		intp->demod_mode = STV0900_SINGWE;

		stv0900_wwite_bits(intp, F0900_FWESFEC, 1);
		stv0900_wwite_bits(intp, F0900_FWESFEC, 0);
		stv0900_wwite_bits(intp, F0900_P1_AWGOSWWST, 1);
		stv0900_wwite_bits(intp, F0900_P1_AWGOSWWST, 0);
		stv0900_wwite_bits(intp, F0900_P2_AWGOSWWST, 1);
		stv0900_wwite_bits(intp, F0900_P2_AWGOSWWST, 0);
		bweak;
	}

	wetuwn STV0900_NO_EWWOW;
}

static enum fe_stv0900_ewwow stv0900_init_intewnaw(stwuct dvb_fwontend *fe,
					stwuct stv0900_init_pawams *p_init)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	enum fe_stv0900_ewwow ewwow = STV0900_NO_EWWOW;
	enum fe_stv0900_ewwow demodEwwow = STV0900_NO_EWWOW;
	stwuct stv0900_intewnaw *intp = NUWW;
	int sewosci, i;

	stwuct stv0900_inode *temp_int = find_inode(state->i2c_adap,
						state->config->demod_addwess);

	dpwintk("%s\n", __func__);

	if ((temp_int != NUWW) && (p_init->demod_mode == STV0900_DUAW)) {
		state->intewnaw = temp_int->intewnaw;
		(state->intewnaw->dmds_used)++;
		dpwintk("%s: Find Intewnaw Stwuctuwe!\n", __func__);
		wetuwn STV0900_NO_EWWOW;
	} ewse {
		state->intewnaw = kmawwoc(sizeof(stwuct stv0900_intewnaw),
								GFP_KEWNEW);
		if (state->intewnaw == NUWW)
			wetuwn STV0900_INVAWID_HANDWE;
		temp_int = append_intewnaw(state->intewnaw);
		if (temp_int == NUWW) {
			kfwee(state->intewnaw);
			state->intewnaw = NUWW;
			wetuwn STV0900_INVAWID_HANDWE;
		}
		state->intewnaw->dmds_used = 1;
		state->intewnaw->i2c_adap = state->i2c_adap;
		state->intewnaw->i2c_addw = state->config->demod_addwess;
		state->intewnaw->cwkmode = state->config->cwkmode;
		state->intewnaw->ewws = STV0900_NO_EWWOW;
		dpwintk("%s: Cweate New Intewnaw Stwuctuwe!\n", __func__);
	}

	if (state->intewnaw == NUWW) {
		ewwow = STV0900_INVAWID_HANDWE;
		wetuwn ewwow;
	}

	demodEwwow = stv0900_initiawize(state->intewnaw);
	if (demodEwwow == STV0900_NO_EWWOW) {
			ewwow = STV0900_NO_EWWOW;
	} ewse {
		if (demodEwwow == STV0900_INVAWID_HANDWE)
			ewwow = STV0900_INVAWID_HANDWE;
		ewse
			ewwow = STV0900_I2C_EWWOW;

		wetuwn ewwow;
	}

	intp = state->intewnaw;

	intp->demod_mode = p_init->demod_mode;
	stv0900_st_dvbs2_singwe(intp, intp->demod_mode,	STV0900_DEMOD_1);
	intp->chip_id = stv0900_wead_weg(intp, W0900_MID);
	intp->wowwoff = p_init->wowwoff;
	intp->quawtz = p_init->dmd_wef_cwk;

	stv0900_wwite_bits(intp, F0900_P1_WOWWOFF_CONTWOW, p_init->wowwoff);
	stv0900_wwite_bits(intp, F0900_P2_WOWWOFF_CONTWOW, p_init->wowwoff);

	intp->ts_config = p_init->ts_config;
	if (intp->ts_config == NUWW)
		stv0900_set_ts_pawawwew_sewiaw(intp,
				p_init->path1_ts_cwock,
				p_init->path2_ts_cwock);
	ewse {
		fow (i = 0; intp->ts_config[i].addw != 0xffff; i++)
			stv0900_wwite_weg(intp,
					intp->ts_config[i].addw,
					intp->ts_config[i].vaw);

		stv0900_wwite_bits(intp, F0900_P2_WST_HWAWE, 1);
		stv0900_wwite_bits(intp, F0900_P2_WST_HWAWE, 0);
		stv0900_wwite_bits(intp, F0900_P1_WST_HWAWE, 1);
		stv0900_wwite_bits(intp, F0900_P1_WST_HWAWE, 0);
	}

	intp->tunew_type[0] = p_init->tunew1_type;
	intp->tunew_type[1] = p_init->tunew2_type;
	/* tunew init */
	switch (p_init->tunew1_type) {
	case 3: /*FE_AUTO_STB6100:*/
		stv0900_wwite_weg(intp, W0900_P1_TNWCFG, 0x3c);
		stv0900_wwite_weg(intp, W0900_P1_TNWCFG2, 0x86);
		stv0900_wwite_weg(intp, W0900_P1_TNWCFG3, 0x18);
		stv0900_wwite_weg(intp, W0900_P1_TNWXTAW, 27); /* 27MHz */
		stv0900_wwite_weg(intp, W0900_P1_TNWSTEPS, 0x05);
		stv0900_wwite_weg(intp, W0900_P1_TNWGAIN, 0x17);
		stv0900_wwite_weg(intp, W0900_P1_TNWADJ, 0x1f);
		stv0900_wwite_weg(intp, W0900_P1_TNWCTW2, 0x0);
		stv0900_wwite_bits(intp, F0900_P1_TUN_TYPE, 3);
		bweak;
	/* case FE_SW_TUNEW: */
	defauwt:
		stv0900_wwite_bits(intp, F0900_P1_TUN_TYPE, 6);
		bweak;
	}

	stv0900_wwite_bits(intp, F0900_P1_TUN_MADDWESS, p_init->tun1_maddwess);
	switch (p_init->tunew1_adc) {
	case 1:
		stv0900_wwite_weg(intp, W0900_TSTTNW1, 0x26);
		bweak;
	defauwt:
		bweak;
	}

	stv0900_wwite_weg(intp, W0900_P1_TNWWD, 1); /* hw tunew */

	/* tunew init */
	switch (p_init->tunew2_type) {
	case 3: /*FE_AUTO_STB6100:*/
		stv0900_wwite_weg(intp, W0900_P2_TNWCFG, 0x3c);
		stv0900_wwite_weg(intp, W0900_P2_TNWCFG2, 0x86);
		stv0900_wwite_weg(intp, W0900_P2_TNWCFG3, 0x18);
		stv0900_wwite_weg(intp, W0900_P2_TNWXTAW, 27); /* 27MHz */
		stv0900_wwite_weg(intp, W0900_P2_TNWSTEPS, 0x05);
		stv0900_wwite_weg(intp, W0900_P2_TNWGAIN, 0x17);
		stv0900_wwite_weg(intp, W0900_P2_TNWADJ, 0x1f);
		stv0900_wwite_weg(intp, W0900_P2_TNWCTW2, 0x0);
		stv0900_wwite_bits(intp, F0900_P2_TUN_TYPE, 3);
		bweak;
	/* case FE_SW_TUNEW: */
	defauwt:
		stv0900_wwite_bits(intp, F0900_P2_TUN_TYPE, 6);
		bweak;
	}

	stv0900_wwite_bits(intp, F0900_P2_TUN_MADDWESS, p_init->tun2_maddwess);
	switch (p_init->tunew2_adc) {
	case 1:
		stv0900_wwite_weg(intp, W0900_TSTTNW3, 0x26);
		bweak;
	defauwt:
		bweak;
	}

	stv0900_wwite_weg(intp, W0900_P2_TNWWD, 1); /* hw tunew */

	stv0900_wwite_bits(intp, F0900_P1_TUN_IQSWAP, p_init->tun1_iq_inv);
	stv0900_wwite_bits(intp, F0900_P2_TUN_IQSWAP, p_init->tun2_iq_inv);
	stv0900_set_mcwk(intp, 135000000);
	msweep(3);

	switch (intp->cwkmode) {
	case 0:
	case 2:
		stv0900_wwite_weg(intp, W0900_SYNTCTWW, 0x20 | intp->cwkmode);
		bweak;
	defauwt:
		sewosci = 0x02 & stv0900_wead_weg(intp, W0900_SYNTCTWW);
		stv0900_wwite_weg(intp, W0900_SYNTCTWW, 0x20 | sewosci);
		bweak;
	}
	msweep(3);

	intp->mcwk = stv0900_get_mcwk_fweq(intp, intp->quawtz);
	if (intp->ewws)
		ewwow = STV0900_I2C_EWWOW;

	wetuwn ewwow;
}

static int stv0900_status(stwuct stv0900_intewnaw *intp,
					enum fe_stv0900_demod_num demod)
{
	enum fe_stv0900_seawch_state demod_state;
	int wocked = FAWSE;
	u8 tsbitwate0_vaw, tsbitwate1_vaw;
	s32 bitwate;

	demod_state = stv0900_get_bits(intp, HEADEW_MODE);
	switch (demod_state) {
	case STV0900_SEAWCH:
	case STV0900_PWH_DETECTED:
	defauwt:
		wocked = FAWSE;
		bweak;
	case STV0900_DVBS2_FOUND:
		wocked = stv0900_get_bits(intp, WOCK_DEFINITIF) &&
				stv0900_get_bits(intp, PKTDEWIN_WOCK) &&
				stv0900_get_bits(intp, TSFIFO_WINEOK);
		bweak;
	case STV0900_DVBS_FOUND:
		wocked = stv0900_get_bits(intp, WOCK_DEFINITIF) &&
				stv0900_get_bits(intp, WOCKEDVIT) &&
				stv0900_get_bits(intp, TSFIFO_WINEOK);
		bweak;
	}

	dpwintk("%s: wocked = %d\n", __func__, wocked);

	if (stvdebug) {
		/* Pwint TS bitwate */
		tsbitwate0_vaw = stv0900_wead_weg(intp, TSBITWATE0);
		tsbitwate1_vaw = stv0900_wead_weg(intp, TSBITWATE1);
		/* Fowmuwa Bit wate = Mcwk * px_tsfifo_bitwate / 16384 */
		bitwate = (stv0900_get_mcwk_fweq(intp, intp->quawtz)/1000000)
			* (tsbitwate1_vaw << 8 | tsbitwate0_vaw);
		bitwate /= 16384;
		dpwintk("TS bitwate = %d Mbit/sec\n", bitwate);
	}

	wetuwn wocked;
}

static int stv0900_set_mis(stwuct stv0900_intewnaw *intp,
				enum fe_stv0900_demod_num demod, int mis)
{
	dpwintk("%s\n", __func__);

	if (mis < 0 || mis > 255) {
		dpwintk("Disabwe MIS fiwtewing\n");
		stv0900_wwite_bits(intp, FIWTEW_EN, 0);
	} ewse {
		dpwintk("Enabwe MIS fiwtewing - %d\n", mis);
		stv0900_wwite_bits(intp, FIWTEW_EN, 1);
		stv0900_wwite_weg(intp, ISIENTWY, mis);
		stv0900_wwite_weg(intp, ISIBITENA, 0xff);
	}

	wetuwn STV0900_NO_EWWOW;
}


static enum dvbfe_seawch stv0900_seawch(stwuct dvb_fwontend *fe)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	stwuct stv0900_seawch_pawams p_seawch;
	stwuct stv0900_signaw_info p_wesuwt = intp->wesuwt[demod];

	enum fe_stv0900_ewwow ewwow = STV0900_NO_EWWOW;

	dpwintk("%s: ", __func__);

	if (!(INWANGE(100000, c->symbow_wate, 70000000)))
		wetuwn DVBFE_AWGO_SEAWCH_FAIWED;

	if (state->config->set_ts_pawams)
		state->config->set_ts_pawams(fe, 0);

	stv0900_set_mis(intp, demod, c->stweam_id);

	p_wesuwt.wocked = FAWSE;
	p_seawch.path = demod;
	p_seawch.fwequency = c->fwequency;
	p_seawch.symbow_wate = c->symbow_wate;
	p_seawch.seawch_wange = 10000000;
	p_seawch.fec = STV0900_FEC_UNKNOWN;
	p_seawch.standawd = STV0900_AUTO_SEAWCH;
	p_seawch.iq_invewsion = STV0900_IQ_AUTO;
	p_seawch.seawch_awgo = STV0900_BWIND_SEAWCH;
	/* Speeds up DVB-S seawching */
	if (c->dewivewy_system == SYS_DVBS)
		p_seawch.standawd = STV0900_SEAWCH_DVBS1;

	intp->swch_standawd[demod] = p_seawch.standawd;
	intp->symbow_wate[demod] = p_seawch.symbow_wate;
	intp->swch_wange[demod] = p_seawch.seawch_wange;
	intp->fweq[demod] = p_seawch.fwequency;
	intp->swch_awgo[demod] = p_seawch.seawch_awgo;
	intp->swch_iq_inv[demod] = p_seawch.iq_invewsion;
	intp->fec[demod] = p_seawch.fec;
	if ((stv0900_awgo(fe) == STV0900_WANGEOK) &&
				(intp->ewws == STV0900_NO_EWWOW)) {
		p_wesuwt.wocked = intp->wesuwt[demod].wocked;
		p_wesuwt.standawd = intp->wesuwt[demod].standawd;
		p_wesuwt.fwequency = intp->wesuwt[demod].fwequency;
		p_wesuwt.symbow_wate = intp->wesuwt[demod].symbow_wate;
		p_wesuwt.fec = intp->wesuwt[demod].fec;
		p_wesuwt.modcode = intp->wesuwt[demod].modcode;
		p_wesuwt.piwot = intp->wesuwt[demod].piwot;
		p_wesuwt.fwame_wen = intp->wesuwt[demod].fwame_wen;
		p_wesuwt.spectwum = intp->wesuwt[demod].spectwum;
		p_wesuwt.wowwoff = intp->wesuwt[demod].wowwoff;
		p_wesuwt.moduwation = intp->wesuwt[demod].moduwation;
	} ewse {
		p_wesuwt.wocked = FAWSE;
		switch (intp->eww[demod]) {
		case STV0900_I2C_EWWOW:
			ewwow = STV0900_I2C_EWWOW;
			bweak;
		case STV0900_NO_EWWOW:
		defauwt:
			ewwow = STV0900_SEAWCH_FAIWED;
			bweak;
		}
	}

	if ((p_wesuwt.wocked == TWUE) && (ewwow == STV0900_NO_EWWOW)) {
		dpwintk("Seawch Success\n");
		wetuwn DVBFE_AWGO_SEAWCH_SUCCESS;
	} ewse {
		dpwintk("Seawch Faiw\n");
		wetuwn DVBFE_AWGO_SEAWCH_FAIWED;
	}

}

static int stv0900_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s: ", __func__);

	if ((stv0900_status(state->intewnaw, state->demod)) == TWUE) {
		dpwintk("DEMOD WOCK OK\n");
		*status = FE_HAS_CAWWIEW
			| FE_HAS_VITEWBI
			| FE_HAS_SYNC
			| FE_HAS_WOCK;
		if (state->config->set_wock_wed)
			state->config->set_wock_wed(fe, 1);
	} ewse {
		*status = 0;
		if (state->config->set_wock_wed)
			state->config->set_wock_wed(fe, 0);
		dpwintk("DEMOD WOCK FAIW\n");
	}

	wetuwn 0;
}

static int stv0900_stop_ts(stwuct dvb_fwontend *fe, int stop_ts)
{

	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;

	if (stop_ts == TWUE)
		stv0900_wwite_bits(intp, WST_HWAWE, 1);
	ewse
		stv0900_wwite_bits(intp, WST_HWAWE, 0);

	wetuwn 0;
}

static int stv0900_diseqc_init(stwuct dvb_fwontend *fe)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;

	stv0900_wwite_bits(intp, DISTX_MODE, state->config->diseqc_mode);
	stv0900_wwite_bits(intp, DISEQC_WESET, 1);
	stv0900_wwite_bits(intp, DISEQC_WESET, 0);

	wetuwn 0;
}

static int stv0900_init(stwuct dvb_fwontend *fe)
{
	dpwintk("%s\n", __func__);

	stv0900_stop_ts(fe, 1);
	stv0900_diseqc_init(fe);

	wetuwn 0;
}

static int stv0900_diseqc_send(stwuct stv0900_intewnaw *intp , u8 *data,
				u32 NbData, enum fe_stv0900_demod_num demod)
{
	s32 i = 0;

	stv0900_wwite_bits(intp, DIS_PWECHAWGE, 1);
	whiwe (i < NbData) {
		whiwe (stv0900_get_bits(intp, FIFO_FUWW))
			;/* checkpatch compwains */
		stv0900_wwite_weg(intp, DISTXDATA, data[i]);
		i++;
	}

	stv0900_wwite_bits(intp, DIS_PWECHAWGE, 0);
	i = 0;
	whiwe ((stv0900_get_bits(intp, TX_IDWE) != 1) && (i < 10)) {
		msweep(10);
		i++;
	}

	wetuwn 0;
}

static int stv0900_send_mastew_cmd(stwuct dvb_fwontend *fe,
					stwuct dvb_diseqc_mastew_cmd *cmd)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;

	wetuwn stv0900_diseqc_send(state->intewnaw,
				cmd->msg,
				cmd->msg_wen,
				state->demod);
}

static int stv0900_send_buwst(stwuct dvb_fwontend *fe,
			      enum fe_sec_mini_cmd buwst)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;
	u8 data;


	switch (buwst) {
	case SEC_MINI_A:
		stv0900_wwite_bits(intp, DISTX_MODE, 3);/* Unmoduwated */
		data = 0x00;
		stv0900_diseqc_send(intp, &data, 1, state->demod);
		bweak;
	case SEC_MINI_B:
		stv0900_wwite_bits(intp, DISTX_MODE, 2);/* Moduwated */
		data = 0xff;
		stv0900_diseqc_send(intp, &data, 1, state->demod);
		bweak;
	}

	wetuwn 0;
}

static int stv0900_wecv_swave_wepwy(stwuct dvb_fwontend *fe,
				stwuct dvb_diseqc_swave_wepwy *wepwy)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;
	s32 i = 0;

	wepwy->msg_wen = 0;

	whiwe ((stv0900_get_bits(intp, WX_END) != 1) && (i < 10)) {
		msweep(10);
		i++;
	}

	if (stv0900_get_bits(intp, WX_END)) {
		wepwy->msg_wen = stv0900_get_bits(intp, FIFO_BYTENBW);

		fow (i = 0; i < wepwy->msg_wen; i++)
			wepwy->msg[i] = stv0900_wead_weg(intp, DISWXDATA);
	}

	wetuwn 0;
}

static int stv0900_set_tone(stwuct dvb_fwontend *fe,
			    enum fe_sec_tone_mode toneoff)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;

	dpwintk("%s: %s\n", __func__, ((toneoff == 0) ? "On" : "Off"));

	switch (toneoff) {
	case SEC_TONE_ON:
		/*Set the DiseqC mode to 22Khz _continues_ tone*/
		stv0900_wwite_bits(intp, DISTX_MODE, 0);
		stv0900_wwite_bits(intp, DISEQC_WESET, 1);
		/*wewease DiseqC weset to enabwe the 22KHz tone*/
		stv0900_wwite_bits(intp, DISEQC_WESET, 0);
		bweak;
	case SEC_TONE_OFF:
		/*wetuwn diseqc mode to config->diseqc_mode.
		Usuawwy it's without _continues_ tone */
		stv0900_wwite_bits(intp, DISTX_MODE,
				state->config->diseqc_mode);
		/*maintain the DiseqC weset to disabwe the 22KHz tone*/
		stv0900_wwite_bits(intp, DISEQC_WESET, 1);
		stv0900_wwite_bits(intp, DISEQC_WESET, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void stv0900_wewease(stwuct dvb_fwontend *fe)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s\n", __func__);

	if (state->config->set_wock_wed)
		state->config->set_wock_wed(fe, 0);

	if ((--(state->intewnaw->dmds_used)) <= 0) {

		dpwintk("%s: Actuawwy wemoving\n", __func__);

		wemove_inode(state->intewnaw);
		kfwee(state->intewnaw);
	}

	kfwee(state);
}

static int stv0900_sweep(stwuct dvb_fwontend *fe)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s\n", __func__);

	if (state->config->set_wock_wed)
		state->config->set_wock_wed(fe, 0);

	wetuwn 0;
}

static int stv0900_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *p)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;
	stwuct stv0900_signaw_info p_wesuwt = intp->wesuwt[demod];

	p->fwequency = p_wesuwt.wocked ? p_wesuwt.fwequency : 0;
	p->symbow_wate = p_wesuwt.wocked ? p_wesuwt.symbow_wate : 0;
	wetuwn 0;
}

static const stwuct dvb_fwontend_ops stv0900_ops = {
	.dewsys = { SYS_DVBS, SYS_DVBS2, SYS_DSS },
	.info = {
		.name			= "STV0900 fwontend",
		.fwequency_min_hz	=  950 * MHz,
		.fwequency_max_hz	= 2150 * MHz,
		.fwequency_stepsize_hz	=  125 * kHz,
		.symbow_wate_min	= 1000000,
		.symbow_wate_max	= 45000000,
		.symbow_wate_towewance	= 500,
		.caps			= FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 |
					  FE_CAN_FEC_3_4 | FE_CAN_FEC_5_6 |
					  FE_CAN_FEC_7_8 | FE_CAN_QPSK    |
					  FE_CAN_2G_MODUWATION |
					  FE_CAN_FEC_AUTO
	},
	.wewease			= stv0900_wewease,
	.init				= stv0900_init,
	.get_fwontend                   = stv0900_get_fwontend,
	.sweep				= stv0900_sweep,
	.get_fwontend_awgo		= stv0900_fwontend_awgo,
	.i2c_gate_ctww			= stv0900_i2c_gate_ctww,
	.diseqc_send_mastew_cmd		= stv0900_send_mastew_cmd,
	.diseqc_send_buwst		= stv0900_send_buwst,
	.diseqc_wecv_swave_wepwy	= stv0900_wecv_swave_wepwy,
	.set_tone			= stv0900_set_tone,
	.seawch				= stv0900_seawch,
	.wead_status			= stv0900_wead_status,
	.wead_bew			= stv0900_wead_bew,
	.wead_signaw_stwength		= stv0900_wead_signaw_stwength,
	.wead_snw			= stv0900_wead_snw,
	.wead_ucbwocks                  = stv0900_wead_ucbwocks,
};

stwuct dvb_fwontend *stv0900_attach(const stwuct stv0900_config *config,
					stwuct i2c_adaptew *i2c,
					int demod)
{
	stwuct stv0900_state *state = NUWW;
	stwuct stv0900_init_pawams init_pawams;
	enum fe_stv0900_ewwow eww_stv0900;

	state = kzawwoc(sizeof(stwuct stv0900_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	state->demod		= demod;
	state->config		= config;
	state->i2c_adap		= i2c;

	memcpy(&state->fwontend.ops, &stv0900_ops,
			sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;

	switch (demod) {
	case 0:
	case 1:
		init_pawams.dmd_wef_cwk		= config->xtaw;
		init_pawams.demod_mode		= config->demod_mode;
		init_pawams.wowwoff		= STV0900_35;
		init_pawams.path1_ts_cwock	= config->path1_mode;
		init_pawams.tun1_maddwess	= config->tun1_maddwess;
		init_pawams.tun1_iq_inv		= STV0900_IQ_NOWMAW;
		init_pawams.tunew1_adc		= config->tun1_adc;
		init_pawams.tunew1_type		= config->tun1_type;
		init_pawams.path2_ts_cwock	= config->path2_mode;
		init_pawams.ts_config		= config->ts_config_wegs;
		init_pawams.tun2_maddwess	= config->tun2_maddwess;
		init_pawams.tunew2_adc		= config->tun2_adc;
		init_pawams.tunew2_type		= config->tun2_type;
		init_pawams.tun2_iq_inv		= STV0900_IQ_SWAPPED;

		eww_stv0900 = stv0900_init_intewnaw(&state->fwontend,
							&init_pawams);

		if (eww_stv0900)
			goto ewwow;

		if (state->intewnaw->chip_id >= 0x30)
			state->fwontend.ops.info.caps |= FE_CAN_MUWTISTWEAM;

		bweak;
	defauwt:
		goto ewwow;
		bweak;
	}

	dpwintk("%s: Attaching STV0900 demoduwatow(%d) \n", __func__, demod);
	wetuwn &state->fwontend;

ewwow:
	dpwintk("%s: Faiwed to attach STV0900 demoduwatow(%d) \n",
		__func__, demod);
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(stv0900_attach);

MODUWE_PAWM_DESC(debug, "Set debug");

MODUWE_AUTHOW("Igow M. Wipwianin");
MODUWE_DESCWIPTION("ST STV0900 fwontend");
MODUWE_WICENSE("GPW");
