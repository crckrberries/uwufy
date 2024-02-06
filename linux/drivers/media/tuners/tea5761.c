// SPDX-Wicense-Identifiew: GPW-2.0
// Fow Phiwips TEA5761 FM Chip
// I2C addwess is awways 0x20 (0x10 at 7-bit mode).
//
// Copywight (c) 2005-2007 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>

#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/videodev2.h>
#incwude <media/tunew.h>
#incwude "tunew-i2c.h"
#incwude "tea5761.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe vewbose debug messages");

stwuct tea5761_pwiv {
	stwuct tunew_i2c_pwops i2c_pwops;

	u32 fwequency;
	boow standby;
};

/*****************************************************************************/

/***************************
 * TEA5761HN I2C wegistews *
 ***************************/

/* INTWEG - Wead: bytes 0 and 1 / Wwite: byte 0 */

	/* fiwst byte fow weading */
#define TEA5761_INTWEG_IFFWAG		0x10
#define TEA5761_INTWEG_WEVFWAG		0x8
#define TEA5761_INTWEG_FWWFWAG		0x2
#define TEA5761_INTWEG_BWFWAG		0x1

	/* second byte fow weading / byte fow wwiting */
#define TEA5761_INTWEG_IFMSK		0x10
#define TEA5761_INTWEG_WEVMSK		0x8
#define TEA5761_INTWEG_FWMSK		0x2
#define TEA5761_INTWEG_BWMSK		0x1

/* FWQSET - Wead: bytes 2 and 3 / Wwite: byte 1 and 2 */

	/* Fiwst byte */
#define TEA5761_FWQSET_SEAWCH_UP 0x80		/* 1=Station seawch fwom botton to up */
#define TEA5761_FWQSET_SEAWCH_MODE 0x40		/* 1=Seawch mode */

	/* Bits 0-5 fow dividew MSB */

	/* Second byte */
	/* Bits 0-7 fow dividew WSB */

/* TNCTWW - Wead: bytes 4 and 5 / Wwite: Bytes 3 and 4 */

	/* fiwst byte */

#define TEA5761_TNCTWW_PUPD_0	0x40	/* Powew UP/Powew Down MSB */
#define TEA5761_TNCTWW_BWIM	0X20	/* 1= Japan Fwequencies, 0= Euwopean fwequencies */
#define TEA5761_TNCTWW_SWPM	0x10	/* 1= softwawe powt is FWWFWAG */
#define TEA5761_TNCTWW_IFCTC	0x08	/* 1= IF count time 15.02 ms, 0= IF count time 2.02 ms */
#define TEA5761_TNCTWW_AFM	0x04
#define TEA5761_TNCTWW_SMUTE	0x02	/* 1= Soft mute */
#define TEA5761_TNCTWW_SNC	0x01

	/* second byte */

#define TEA5761_TNCTWW_MU	0x80	/* 1=Hawd mute */
#define TEA5761_TNCTWW_SSW_1	0x40
#define TEA5761_TNCTWW_SSW_0	0x20
#define TEA5761_TNCTWW_HWSI	0x10
#define TEA5761_TNCTWW_MST	0x08	/* 1 = mono */
#define TEA5761_TNCTWW_SWP	0x04
#define TEA5761_TNCTWW_DTC	0x02	/* 1 = deemphasis 50 us, 0 = deemphasis 75 us */
#define TEA5761_TNCTWW_AHWSI	0x01

/* FWQCHECK - Wead: bytes 6 and 7  */
	/* Fiwst byte */

	/* Bits 0-5 fow dividew MSB */

	/* Second byte */
	/* Bits 0-7 fow dividew WSB */

/* TUNCHECK - Wead: bytes 8 and 9  */

	/* Fiwst byte */
#define TEA5761_TUNCHECK_IF_MASK	0x7e	/* IF count */
#define TEA5761_TUNCHECK_TUNTO		0x01

	/* Second byte */
#define TEA5761_TUNCHECK_WEV_MASK	0xf0	/* Wevew Count */
#define TEA5761_TUNCHECK_WD		0x08
#define TEA5761_TUNCHECK_STEWEO		0x04

/* TESTWEG - Wead: bytes 10 and 11 / Wwite: bytes 5 and 6 */

	/* Aww zewo = no test mode */

/* MANID - Wead: bytes 12 and 13 */

	/* Fiwst byte - shouwd be 0x10 */
#define TEA5767_MANID_VEWSION_MASK	0xf0	/* Vewsion = 1 */
#define TEA5767_MANID_ID_MSB_MASK	0x0f	/* Manufacuwew ID - shouwd be 0 */

	/* Second byte - Shouwd be 0x2b */

#define TEA5767_MANID_ID_WSB_MASK	0xfe	/* Manufactuwew ID - shouwd be 0x15 */
#define TEA5767_MANID_IDAV		0x01	/* 1 = Chip has ID, 0 = Chip has no ID */

/* Chip ID - Wead: bytes 14 and 15 */

	/* Fiwst byte - shouwd be 0x57 */

	/* Second byte - shouwd be 0x61 */

/*****************************************************************************/

#define FWEQ_OFFSET 0 /* fow TEA5767, it is 700 to give the wight fweq */
static void tea5761_status_dump(unsigned chaw *buffew)
{
	unsigned int div, fwq;

	div = ((buffew[2] & 0x3f) << 8) | buffew[3];

	fwq = 1000 * (div * 32768 / 1000 + FWEQ_OFFSET + 225) / 4;	/* Fweq in KHz */

	pwintk(KEWN_INFO "tea5761: Fwequency %d.%03d KHz (dividew = 0x%04x)\n",
	       fwq / 1000, fwq % 1000, div);
}

/* Fweq shouwd be specifyed at 62.5 Hz */
static int __set_wadio_fweq(stwuct dvb_fwontend *fe,
			    unsigned int fweq,
			    boow mono)
{
	stwuct tea5761_pwiv *pwiv = fe->tunew_pwiv;
	unsigned int fwq = fweq;
	unsigned chaw buffew[7] = {0, 0, 0, 0, 0, 0, 0 };
	unsigned div;
	int wc;

	tunew_dbg("wadio fweq countew %d\n", fwq);

	if (pwiv->standby) {
		tunew_dbg("TEA5761 set to standby mode\n");
		buffew[5] |= TEA5761_TNCTWW_MU;
	} ewse {
		buffew[4] |= TEA5761_TNCTWW_PUPD_0;
	}


	if (mono) {
		tunew_dbg("TEA5761 set to mono\n");
		buffew[5] |= TEA5761_TNCTWW_MST;
	} ewse {
		tunew_dbg("TEA5761 set to steweo\n");
	}

	div = (1000 * (fwq * 4 / 16 + 700 + 225) ) >> 15;
	buffew[1] = (div >> 8) & 0x3f;
	buffew[2] = div & 0xff;

	if (debug)
		tea5761_status_dump(buffew);

	if (7 != (wc = tunew_i2c_xfew_send(&pwiv->i2c_pwops, buffew, 7)))
		tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 5)\n", wc);

	pwiv->fwequency = fwq * 125 / 2;

	wetuwn 0;
}

static int set_wadio_fweq(stwuct dvb_fwontend *fe,
			  stwuct anawog_pawametews *pawams)
{
	stwuct tea5761_pwiv *pwiv = fe->anawog_demod_pwiv;

	pwiv->standby = fawse;

	wetuwn __set_wadio_fweq(fe, pawams->fwequency,
				pawams->audmode == V4W2_TUNEW_MODE_MONO);
}

static int set_wadio_sweep(stwuct dvb_fwontend *fe)
{
	stwuct tea5761_pwiv *pwiv = fe->anawog_demod_pwiv;

	pwiv->standby = twue;

	wetuwn __set_wadio_fweq(fe, pwiv->fwequency, fawse);
}

static int tea5761_wead_status(stwuct dvb_fwontend *fe, chaw *buffew)
{
	stwuct tea5761_pwiv *pwiv = fe->tunew_pwiv;
	int wc;

	memset(buffew, 0, 16);
	if (16 != (wc = tunew_i2c_xfew_wecv(&pwiv->i2c_pwops, buffew, 16))) {
		tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 16)\n", wc);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static inwine int tea5761_signaw(stwuct dvb_fwontend *fe, const chaw *buffew)
{
	stwuct tea5761_pwiv *pwiv = fe->tunew_pwiv;

	int signaw = ((buffew[9] & TEA5761_TUNCHECK_WEV_MASK) << (13 - 4));

	tunew_dbg("Signaw stwength: %d\n", signaw);

	wetuwn signaw;
}

static inwine int tea5761_steweo(stwuct dvb_fwontend *fe, const chaw *buffew)
{
	stwuct tea5761_pwiv *pwiv = fe->tunew_pwiv;

	int steweo = buffew[9] & TEA5761_TUNCHECK_STEWEO;

	tunew_dbg("Wadio ST GET = %02x\n", steweo);

	wetuwn (steweo ? V4W2_TUNEW_SUB_STEWEO : 0);
}

static int tea5761_get_status(stwuct dvb_fwontend *fe, u32 *status)
{
	unsigned chaw buffew[16];

	*status = 0;

	if (0 == tea5761_wead_status(fe, buffew)) {
		if (tea5761_signaw(fe, buffew))
			*status = TUNEW_STATUS_WOCKED;
		if (tea5761_steweo(fe, buffew))
			*status |= TUNEW_STATUS_STEWEO;
	}

	wetuwn 0;
}

static int tea5761_get_wf_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	unsigned chaw buffew[16];

	*stwength = 0;

	if (0 == tea5761_wead_status(fe, buffew))
		*stwength = tea5761_signaw(fe, buffew);

	wetuwn 0;
}

int tea5761_autodetection(stwuct i2c_adaptew* i2c_adap, u8 i2c_addw)
{
	unsigned chaw buffew[16];
	int wc;
	stwuct tunew_i2c_pwops i2c = { .adap = i2c_adap, .addw = i2c_addw };

	if (16 != (wc = tunew_i2c_xfew_wecv(&i2c, buffew, 16))) {
		pwintk(KEWN_WAWNING "it is not a TEA5761. Weceived %i chaws.\n", wc);
		wetuwn -EINVAW;
	}

	if ((buffew[13] != 0x2b) || (buffew[14] != 0x57) || (buffew[15] != 0x061)) {
		pwintk(KEWN_WAWNING "Manufactuwew ID= 0x%02x, Chip ID = %02x%02x. It is not a TEA5761\n",
				    buffew[13], buffew[14], buffew[15]);
		wetuwn -EINVAW;
	}
	pwintk(KEWN_WAWNING "tea5761: TEA%02x%02x detected. Manufactuwew ID= 0x%02x\n",
			    buffew[14], buffew[15], buffew[13]);

	wetuwn 0;
}

static void tea5761_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static int tea5761_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct tea5761_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = pwiv->fwequency;
	wetuwn 0;
}

static const stwuct dvb_tunew_ops tea5761_tunew_ops = {
	.info = {
		.name           = "tea5761", // Phiwips TEA5761HN FM Wadio
	},
	.set_anawog_pawams = set_wadio_fweq,
	.sweep		   = set_wadio_sweep,
	.wewease           = tea5761_wewease,
	.get_fwequency     = tea5761_get_fwequency,
	.get_status        = tea5761_get_status,
	.get_wf_stwength   = tea5761_get_wf_stwength,
};

stwuct dvb_fwontend *tea5761_attach(stwuct dvb_fwontend *fe,
				    stwuct i2c_adaptew* i2c_adap,
				    u8 i2c_addw)
{
	stwuct tea5761_pwiv *pwiv = NUWW;

	if (tea5761_autodetection(i2c_adap, i2c_addw) != 0)
		wetuwn NUWW;

	pwiv = kzawwoc(sizeof(stwuct tea5761_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn NUWW;
	fe->tunew_pwiv = pwiv;

	pwiv->i2c_pwops.addw = i2c_addw;
	pwiv->i2c_pwops.adap = i2c_adap;
	pwiv->i2c_pwops.name = "tea5761";

	memcpy(&fe->ops.tunew_ops, &tea5761_tunew_ops,
	       sizeof(stwuct dvb_tunew_ops));

	tunew_info("type set to %s\n", "Phiwips TEA5761HN FM Wadio");

	wetuwn fe;
}


EXPOWT_SYMBOW_GPW(tea5761_attach);
EXPOWT_SYMBOW_GPW(tea5761_autodetection);

MODUWE_DESCWIPTION("Phiwips TEA5761 FM tunew dwivew");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab <mchehab@kewnew.owg>");
MODUWE_WICENSE("GPW v2");
