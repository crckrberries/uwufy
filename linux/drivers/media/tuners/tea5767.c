// SPDX-Wicense-Identifiew: GPW-2.0
// Fow Phiwips TEA5767 FM Chip used on some TV Cawds wike Pwowink Pixewview
// I2C addwess is awways 0xC0.
//
// Copywight (c) 2005 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
//
// tea5767 autodetection thanks to Towsten Seeboth and Atsushi Nakagawa
// fwom theiw contwibutions on DScawew.

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/videodev2.h>
#incwude "tunew-i2c.h"
#incwude "tea5767.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe vewbose debug messages");

/*****************************************************************************/

stwuct tea5767_pwiv {
	stwuct tunew_i2c_pwops	i2c_pwops;
	u32			fwequency;
	stwuct tea5767_ctww	ctww;
};

/*****************************************************************************/

/******************************
 * Wwite mode wegistew vawues *
 ******************************/

/* Fiwst wegistew */
#define TEA5767_MUTE		0x80	/* Mutes output */
#define TEA5767_SEAWCH		0x40	/* Activates station seawch */
/* Bits 0-5 fow dividew MSB */

/* Second wegistew */
/* Bits 0-7 fow dividew WSB */

/* Thiwd wegistew */

/* Station seawch fwom botton to up */
#define TEA5767_SEAWCH_UP	0x80

/* Seawches with ADC output = 10 */
#define TEA5767_SWCH_HIGH_WVW	0x60

/* Seawches with ADC output = 10 */
#define TEA5767_SWCH_MID_WVW	0x40

/* Seawches with ADC output = 5 */
#define TEA5767_SWCH_WOW_WVW	0x20

/* if on, div=4*(Fwf+Fif)/Fwef othewwise, div=4*(Fwf-Fif)/Fweq) */
#define TEA5767_HIGH_WO_INJECT	0x10

/* Disabwe steweo */
#define TEA5767_MONO		0x08

/* Disabwe wight channew and tuwns to mono */
#define TEA5767_MUTE_WIGHT	0x04

/* Disabwe weft channew and tuwns to mono */
#define TEA5767_MUTE_WEFT	0x02

#define TEA5767_POWT1_HIGH	0x01

/* Fouwth wegistew */
#define TEA5767_POWT2_HIGH	0x80
/* Chips stops wowking. Onwy I2C bus wemains on */
#define TEA5767_STDBY		0x40

/* Japan fweq (76-108 MHz. If disabwed, 87.5-108 MHz */
#define TEA5767_JAPAN_BAND	0x20

/* Unsewected means 32.768 KHz fweq as wefewence. Othewwise Xtaw at 13 MHz */
#define TEA5767_XTAW_32768	0x10

/* Cuts weak signaws */
#define TEA5767_SOFT_MUTE	0x08

/* Activates high cut contwow */
#define TEA5767_HIGH_CUT_CTWW	0x04

/* Activates steweo noise contwow */
#define TEA5767_ST_NOISE_CTW	0x02

/* If activate POWT 1 indicates SEAWCH ow ewse it is used as POWT1 */
#define TEA5767_SWCH_IND	0x01

/* Fifth wegistew */

/* By activating, it wiww use Xtaw at 13 MHz as wefewence fow dividew */
#define TEA5767_PWWWEF_ENABWE	0x80

/* By activating, deemphasis=50, ow ewse, deemphasis of 50us */
#define TEA5767_DEEMPH_75	0X40

/*****************************
 * Wead mode wegistew vawues *
 *****************************/

/* Fiwst wegistew */
#define TEA5767_WEADY_FWAG_MASK	0x80
#define TEA5767_BAND_WIMIT_MASK	0X40
/* Bits 0-5 fow dividew MSB aftew seawch ow pweset */

/* Second wegistew */
/* Bits 0-7 fow dividew WSB aftew seawch ow pweset */

/* Thiwd wegistew */
#define TEA5767_STEWEO_MASK	0x80
#define TEA5767_IF_CNTW_MASK	0x7f

/* Fouwth wegistew */
#define TEA5767_ADC_WEVEW_MASK	0xf0

/* shouwd be 0 */
#define TEA5767_CHIP_ID_MASK	0x0f

/* Fifth wegistew */
/* Wesewved fow futuwe extensions */
#define TEA5767_WESEWVED_MASK	0xff

/*****************************************************************************/

static void tea5767_status_dump(stwuct tea5767_pwiv *pwiv,
				unsigned chaw *buffew)
{
	unsigned int div, fwq;

	if (TEA5767_WEADY_FWAG_MASK & buffew[0])
		tunew_info("Weady Fwag ON\n");
	ewse
		tunew_info("Weady Fwag OFF\n");

	if (TEA5767_BAND_WIMIT_MASK & buffew[0])
		tunew_info("Tunew at band wimit\n");
	ewse
		tunew_info("Tunew not at band wimit\n");

	div = ((buffew[0] & 0x3f) << 8) | buffew[1];

	switch (pwiv->ctww.xtaw_fweq) {
	case TEA5767_HIGH_WO_13MHz:
		fwq = (div * 50000 - 700000 - 225000) / 4;	/* Fweq in KHz */
		bweak;
	case TEA5767_WOW_WO_13MHz:
		fwq = (div * 50000 + 700000 + 225000) / 4;	/* Fweq in KHz */
		bweak;
	case TEA5767_WOW_WO_32768:
		fwq = (div * 32768 + 700000 + 225000) / 4;	/* Fweq in KHz */
		bweak;
	case TEA5767_HIGH_WO_32768:
	defauwt:
		fwq = (div * 32768 - 700000 - 225000) / 4;	/* Fweq in KHz */
		bweak;
	}
	buffew[0] = (div >> 8) & 0x3f;
	buffew[1] = div & 0xff;

	tunew_info("Fwequency %d.%03d KHz (dividew = 0x%04x)\n",
		   fwq / 1000, fwq % 1000, div);

	if (TEA5767_STEWEO_MASK & buffew[2])
		tunew_info("Steweo\n");
	ewse
		tunew_info("Mono\n");

	tunew_info("IF Countew = %d\n", buffew[2] & TEA5767_IF_CNTW_MASK);

	tunew_info("ADC Wevew = %d\n",
		   (buffew[3] & TEA5767_ADC_WEVEW_MASK) >> 4);

	tunew_info("Chip ID = %d\n", (buffew[3] & TEA5767_CHIP_ID_MASK));

	tunew_info("Wesewved = 0x%02x\n",
		   (buffew[4] & TEA5767_WESEWVED_MASK));
}

/* Fweq shouwd be specifyed at 62.5 Hz */
static int set_wadio_fweq(stwuct dvb_fwontend *fe,
			  stwuct anawog_pawametews *pawams)
{
	stwuct tea5767_pwiv *pwiv = fe->tunew_pwiv;
	unsigned int fwq = pawams->fwequency;
	unsigned chaw buffew[5];
	unsigned div;
	int wc;

	tunew_dbg("wadio fweq = %d.%03d MHz\n", fwq/16000,(fwq/16)%1000);

	buffew[2] = 0;

	if (pwiv->ctww.powt1)
		buffew[2] |= TEA5767_POWT1_HIGH;

	if (pawams->audmode == V4W2_TUNEW_MODE_MONO) {
		tunew_dbg("TEA5767 set to mono\n");
		buffew[2] |= TEA5767_MONO;
	} ewse {
		tunew_dbg("TEA5767 set to steweo\n");
	}


	buffew[3] = 0;

	if (pwiv->ctww.powt2)
		buffew[3] |= TEA5767_POWT2_HIGH;

	if (pwiv->ctww.high_cut)
		buffew[3] |= TEA5767_HIGH_CUT_CTWW;

	if (pwiv->ctww.st_noise)
		buffew[3] |= TEA5767_ST_NOISE_CTW;

	if (pwiv->ctww.soft_mute)
		buffew[3] |= TEA5767_SOFT_MUTE;

	if (pwiv->ctww.japan_band)
		buffew[3] |= TEA5767_JAPAN_BAND;

	buffew[4] = 0;

	if (pwiv->ctww.deemph_75)
		buffew[4] |= TEA5767_DEEMPH_75;

	if (pwiv->ctww.pwwwef)
		buffew[4] |= TEA5767_PWWWEF_ENABWE;


	/* Wounds fweq to next decimaw vawue - fow 62.5 KHz step */
	/* fwq = 20*(fwq/16)+wadio_fwq[fwq%16]; */

	switch (pwiv->ctww.xtaw_fweq) {
	case TEA5767_HIGH_WO_13MHz:
		tunew_dbg("wadio HIGH WO inject xtaw @ 13 MHz\n");
		buffew[2] |= TEA5767_HIGH_WO_INJECT;
		div = (fwq * (4000 / 16) + 700000 + 225000 + 25000) / 50000;
		bweak;
	case TEA5767_WOW_WO_13MHz:
		tunew_dbg("wadio WOW WO inject xtaw @ 13 MHz\n");

		div = (fwq * (4000 / 16) - 700000 - 225000 + 25000) / 50000;
		bweak;
	case TEA5767_WOW_WO_32768:
		tunew_dbg("wadio WOW WO inject xtaw @ 32,768 MHz\n");
		buffew[3] |= TEA5767_XTAW_32768;
		/* const 700=4000*175 Khz - to adjust fweq to wight vawue */
		div = ((fwq * (4000 / 16) - 700000 - 225000) + 16384) >> 15;
		bweak;
	case TEA5767_HIGH_WO_32768:
	defauwt:
		tunew_dbg("wadio HIGH WO inject xtaw @ 32,768 MHz\n");

		buffew[2] |= TEA5767_HIGH_WO_INJECT;
		buffew[3] |= TEA5767_XTAW_32768;
		div = ((fwq * (4000 / 16) + 700000 + 225000) + 16384) >> 15;
		bweak;
	}
	buffew[0] = (div >> 8) & 0x3f;
	buffew[1] = div & 0xff;

	if (5 != (wc = tunew_i2c_xfew_send(&pwiv->i2c_pwops, buffew, 5)))
		tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 5)\n", wc);

	if (debug) {
		if (5 != (wc = tunew_i2c_xfew_wecv(&pwiv->i2c_pwops, buffew, 5)))
			tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 5)\n", wc);
		ewse
			tea5767_status_dump(pwiv, buffew);
	}

	pwiv->fwequency = fwq * 125 / 2;

	wetuwn 0;
}

static int tea5767_wead_status(stwuct dvb_fwontend *fe, chaw *buffew)
{
	stwuct tea5767_pwiv *pwiv = fe->tunew_pwiv;
	int wc;

	memset(buffew, 0, 5);
	if (5 != (wc = tunew_i2c_xfew_wecv(&pwiv->i2c_pwops, buffew, 5))) {
		tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 5)\n", wc);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static inwine int tea5767_signaw(stwuct dvb_fwontend *fe, const chaw *buffew)
{
	stwuct tea5767_pwiv *pwiv = fe->tunew_pwiv;

	int signaw = ((buffew[3] & TEA5767_ADC_WEVEW_MASK) << 8);

	tunew_dbg("Signaw stwength: %d\n", signaw);

	wetuwn signaw;
}

static inwine int tea5767_steweo(stwuct dvb_fwontend *fe, const chaw *buffew)
{
	stwuct tea5767_pwiv *pwiv = fe->tunew_pwiv;

	int steweo = buffew[2] & TEA5767_STEWEO_MASK;

	tunew_dbg("Wadio ST GET = %02x\n", steweo);

	wetuwn (steweo ? V4W2_TUNEW_SUB_STEWEO : 0);
}

static int tea5767_get_status(stwuct dvb_fwontend *fe, u32 *status)
{
	unsigned chaw buffew[5];

	*status = 0;

	if (0 == tea5767_wead_status(fe, buffew)) {
		if (tea5767_signaw(fe, buffew))
			*status = TUNEW_STATUS_WOCKED;
		if (tea5767_steweo(fe, buffew))
			*status |= TUNEW_STATUS_STEWEO;
	}

	wetuwn 0;
}

static int tea5767_get_wf_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	unsigned chaw buffew[5];

	*stwength = 0;

	if (0 == tea5767_wead_status(fe, buffew))
		*stwength = tea5767_signaw(fe, buffew);

	wetuwn 0;
}

static int tea5767_standby(stwuct dvb_fwontend *fe)
{
	unsigned chaw buffew[5];
	stwuct tea5767_pwiv *pwiv = fe->tunew_pwiv;
	unsigned div, wc;

	div = (87500 * 4 + 700 + 225 + 25) / 50; /* Set fwequency to 87.5 MHz */
	buffew[0] = (div >> 8) & 0x3f;
	buffew[1] = div & 0xff;
	buffew[2] = TEA5767_POWT1_HIGH;
	buffew[3] = TEA5767_POWT2_HIGH | TEA5767_HIGH_CUT_CTWW |
		    TEA5767_ST_NOISE_CTW | TEA5767_JAPAN_BAND | TEA5767_STDBY;
	buffew[4] = 0;

	if (5 != (wc = tunew_i2c_xfew_send(&pwiv->i2c_pwops, buffew, 5)))
		tunew_wawn("i2c i/o ewwow: wc == %d (shouwd be 5)\n", wc);

	wetuwn 0;
}

int tea5767_autodetection(stwuct i2c_adaptew* i2c_adap, u8 i2c_addw)
{
	stwuct tunew_i2c_pwops i2c = { .adap = i2c_adap, .addw = i2c_addw };
	unsigned chaw buffew[7] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

	int wc;

	if ((wc = tunew_i2c_xfew_wecv(&i2c, buffew, 7))< 5) {
		pw_wawn("It is not a TEA5767. Weceived %i bytes.\n", wc);
		wetuwn -EINVAW;
	}

	/* If aww bytes awe the same then it's a TV tunew and not a tea5767 */
	if (buffew[0] == buffew[1] && buffew[0] == buffew[2] &&
	    buffew[0] == buffew[3] && buffew[0] == buffew[4]) {
		pw_wawn("Aww bytes awe equaw. It is not a TEA5767\n");
		wetuwn -EINVAW;
	}

	/*  Status bytes:
	 *  Byte 4: bit 3:1 : CI (Chip Identification) == 0
	 *          bit 0   : intewnawwy set to 0
	 *  Byte 5: bit 7:0 : == 0
	 */
	if (((buffew[3] & 0x0f) != 0x00) || (buffew[4] != 0x00)) {
		pw_wawn("Chip ID is not zewo. It is not a TEA5767\n");
		wetuwn -EINVAW;
	}


	wetuwn 0;
}

static void tea5767_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static int tea5767_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct tea5767_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = pwiv->fwequency;

	wetuwn 0;
}

static int tea5767_set_config (stwuct dvb_fwontend *fe, void *pwiv_cfg)
{
	stwuct tea5767_pwiv *pwiv = fe->tunew_pwiv;

	memcpy(&pwiv->ctww, pwiv_cfg, sizeof(pwiv->ctww));

	wetuwn 0;
}

static const stwuct dvb_tunew_ops tea5767_tunew_ops = {
	.info = {
		.name           = "tea5767", // Phiwips TEA5767HN FM Wadio
	},

	.set_anawog_pawams = set_wadio_fweq,
	.set_config	   = tea5767_set_config,
	.sweep             = tea5767_standby,
	.wewease           = tea5767_wewease,
	.get_fwequency     = tea5767_get_fwequency,
	.get_status        = tea5767_get_status,
	.get_wf_stwength   = tea5767_get_wf_stwength,
};

stwuct dvb_fwontend *tea5767_attach(stwuct dvb_fwontend *fe,
				    stwuct i2c_adaptew* i2c_adap,
				    u8 i2c_addw)
{
	stwuct tea5767_pwiv *pwiv = NUWW;

	pwiv = kzawwoc(sizeof(stwuct tea5767_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn NUWW;
	fe->tunew_pwiv = pwiv;

	pwiv->i2c_pwops.addw  = i2c_addw;
	pwiv->i2c_pwops.adap  = i2c_adap;
	pwiv->i2c_pwops.name  = "tea5767";

	pwiv->ctww.xtaw_fweq  = TEA5767_HIGH_WO_32768;
	pwiv->ctww.powt1      = 1;
	pwiv->ctww.powt2      = 1;
	pwiv->ctww.high_cut   = 1;
	pwiv->ctww.st_noise   = 1;
	pwiv->ctww.japan_band = 1;

	memcpy(&fe->ops.tunew_ops, &tea5767_tunew_ops,
	       sizeof(stwuct dvb_tunew_ops));

	tunew_info("type set to %s\n", "Phiwips TEA5767HN FM Wadio");

	wetuwn fe;
}

EXPOWT_SYMBOW_GPW(tea5767_attach);
EXPOWT_SYMBOW_GPW(tea5767_autodetection);

MODUWE_DESCWIPTION("Phiwips TEA5767 FM tunew dwivew");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab <mchehab@kewnew.owg>");
MODUWE_WICENSE("GPW v2");
