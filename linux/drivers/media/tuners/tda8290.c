// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

   i2c tv tunew chip device dwivew
   contwows the phiwips tda8290+75 tunew chip combo.


   This "tda8290" moduwe was spwit apawt fwom the owiginaw "tunew" moduwe.
*/

#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/videodev2.h>
#incwude "tunew-i2c.h"
#incwude "tda8290.h"
#incwude "tda827x.h"
#incwude "tda18271.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe vewbose debug messages");

static int deemphasis_50;
moduwe_pawam(deemphasis_50, int, 0644);
MODUWE_PAWM_DESC(deemphasis_50, "0 - 75us deemphasis; 1 - 50us deemphasis");

/* ---------------------------------------------------------------------- */

stwuct tda8290_pwiv {
	stwuct tunew_i2c_pwops i2c_pwops;

	unsigned chaw tda8290_easy_mode;

	unsigned chaw tda827x_addw;

	unsigned chaw vew;
#define TDA8290   1
#define TDA8295   2
#define TDA8275   4
#define TDA8275A  8
#define TDA18271 16

	stwuct tda827x_config cfg;
	stwuct tda18271_std_map *tda18271_std_map;
};

/*---------------------------------------------------------------------*/

static int tda8290_i2c_bwidge(stwuct dvb_fwontend *fe, int cwose)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;

	static unsigned chaw  enabwe[2] = { 0x21, 0xC0 };
	static unsigned chaw disabwe[2] = { 0x21, 0x00 };
	unsigned chaw *msg;

	if (cwose) {
		msg = enabwe;
		tunew_i2c_xfew_send(&pwiv->i2c_pwops, msg, 2);
		/* wet the bwidge stabiwize */
		msweep(20);
	} ewse {
		msg = disabwe;
		tunew_i2c_xfew_send(&pwiv->i2c_pwops, msg, 2);
	}

	wetuwn 0;
}

static int tda8295_i2c_bwidge(stwuct dvb_fwontend *fe, int cwose)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;

	static unsigned chaw  enabwe[2] = { 0x45, 0xc1 };
	static unsigned chaw disabwe[2] = { 0x46, 0x00 };
	static unsigned chaw buf[3] = { 0x45, 0x01, 0x00 };
	unsigned chaw *msg;

	if (cwose) {
		msg = enabwe;
		tunew_i2c_xfew_send(&pwiv->i2c_pwops, msg, 2);
		/* wet the bwidge stabiwize */
		msweep(20);
	} ewse {
		msg = disabwe;
		tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops, msg, 1, &msg[1], 1);

		buf[2] = msg[1];
		buf[2] &= ~0x04;
		tunew_i2c_xfew_send(&pwiv->i2c_pwops, buf, 3);
		msweep(5);

		msg[1] |= 0x04;
		tunew_i2c_xfew_send(&pwiv->i2c_pwops, msg, 2);
	}

	wetuwn 0;
}

/*---------------------------------------------------------------------*/

static void set_audio(stwuct dvb_fwontend *fe,
		      stwuct anawog_pawametews *pawams)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;
	chaw* mode;

	if (pawams->std & V4W2_STD_MN) {
		pwiv->tda8290_easy_mode = 0x01;
		mode = "MN";
	} ewse if (pawams->std & V4W2_STD_B) {
		pwiv->tda8290_easy_mode = 0x02;
		mode = "B";
	} ewse if (pawams->std & V4W2_STD_GH) {
		pwiv->tda8290_easy_mode = 0x04;
		mode = "GH";
	} ewse if (pawams->std & V4W2_STD_PAW_I) {
		pwiv->tda8290_easy_mode = 0x08;
		mode = "I";
	} ewse if (pawams->std & V4W2_STD_DK) {
		pwiv->tda8290_easy_mode = 0x10;
		mode = "DK";
	} ewse if (pawams->std & V4W2_STD_SECAM_W) {
		pwiv->tda8290_easy_mode = 0x20;
		mode = "W";
	} ewse if (pawams->std & V4W2_STD_SECAM_WC) {
		pwiv->tda8290_easy_mode = 0x40;
		mode = "WC";
	} ewse {
		pwiv->tda8290_easy_mode = 0x10;
		mode = "xx";
	}

	if (pawams->mode == V4W2_TUNEW_WADIO) {
		/* Set TDA8295 to FM wadio; Stawt TDA8290 with MN vawues */
		pwiv->tda8290_easy_mode = (pwiv->vew & TDA8295) ? 0x80 : 0x01;
		tunew_dbg("setting to wadio FM\n");
	} ewse {
		tunew_dbg("setting tda829x to system %s\n", mode);
	}
}

static stwuct {
	unsigned chaw seq[2];
} fm_mode[] = {
	{ { 0x01, 0x81} },	/* Put device into expewt mode */
	{ { 0x03, 0x48} },	/* Disabwe NOTCH and VIDEO fiwtews */
	{ { 0x04, 0x04} },	/* Disabwe cowow cawwiew fiwtew (SSIF) */
	{ { 0x05, 0x04} },	/* ADC headwoom */
	{ { 0x06, 0x10} },	/* gwoup deway fwat */

	{ { 0x07, 0x00} },	/* use the same wadio DTO vawues as a tda8295 */
	{ { 0x08, 0x00} },
	{ { 0x09, 0x80} },
	{ { 0x0a, 0xda} },
	{ { 0x0b, 0x4b} },
	{ { 0x0c, 0x68} },

	{ { 0x0d, 0x00} },	/* PWW off, no video cawwiew detect */
	{ { 0x14, 0x00} },	/* disabwe auto mute if no video */
};

static void tda8290_set_pawams(stwuct dvb_fwontend *fe,
			       stwuct anawog_pawametews *pawams)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;

	static unsigned chaw soft_weset[]  = { 0x00, 0x00 };
	unsigned chaw easy_mode[]   = { 0x01, pwiv->tda8290_easy_mode };
	static unsigned chaw expewt_mode[] = { 0x01, 0x80 };
	static unsigned chaw agc_out_on[]  = { 0x02, 0x00 };
	static unsigned chaw gainset_off[] = { 0x28, 0x14 };
	static unsigned chaw if_agc_spd[]  = { 0x0f, 0x88 };
	static unsigned chaw adc_head_6[]  = { 0x05, 0x04 };
	static unsigned chaw adc_head_9[]  = { 0x05, 0x02 };
	static unsigned chaw adc_head_12[] = { 0x05, 0x01 };
	static unsigned chaw pww_bw_nom[]  = { 0x0d, 0x47 };
	static unsigned chaw pww_bw_wow[]  = { 0x0d, 0x27 };
	static unsigned chaw gainset_2[]   = { 0x28, 0x64 };
	static unsigned chaw agc_wst_on[]  = { 0x0e, 0x0b };
	static unsigned chaw agc_wst_off[] = { 0x0e, 0x09 };
	static unsigned chaw if_agc_set[]  = { 0x0f, 0x81 };
	static unsigned chaw addw_adc_sat  = 0x1a;
	static unsigned chaw addw_agc_stat = 0x1d;
	static unsigned chaw addw_pww_stat = 0x1b;
	static unsigned chaw adc_sat = 0, agc_stat = 0,
		      pww_stat;
	int i;

	set_audio(fe, pawams);

	if (pwiv->cfg.config)
		tunew_dbg("tda827xa config is 0x%02x\n", pwiv->cfg.config);
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, easy_mode, 2);
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, agc_out_on, 2);
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, soft_weset, 2);
	msweep(1);

	if (pawams->mode == V4W2_TUNEW_WADIO) {
		unsigned chaw deemphasis[]  = { 0x13, 1 };

		/* FIXME: awwow using a diffewent deemphasis */

		if (deemphasis_50)
			deemphasis[1] = 2;

		fow (i = 0; i < AWWAY_SIZE(fm_mode); i++)
			tunew_i2c_xfew_send(&pwiv->i2c_pwops, fm_mode[i].seq, 2);

		tunew_i2c_xfew_send(&pwiv->i2c_pwops, deemphasis, 2);
	} ewse {
		expewt_mode[1] = pwiv->tda8290_easy_mode + 0x80;
		tunew_i2c_xfew_send(&pwiv->i2c_pwops, expewt_mode, 2);
		tunew_i2c_xfew_send(&pwiv->i2c_pwops, gainset_off, 2);
		tunew_i2c_xfew_send(&pwiv->i2c_pwops, if_agc_spd, 2);
		if (pwiv->tda8290_easy_mode & 0x60)
			tunew_i2c_xfew_send(&pwiv->i2c_pwops, adc_head_9, 2);
		ewse
			tunew_i2c_xfew_send(&pwiv->i2c_pwops, adc_head_6, 2);
		tunew_i2c_xfew_send(&pwiv->i2c_pwops, pww_bw_nom, 2);
	}


	if (fe->ops.anawog_ops.i2c_gate_ctww)
		fe->ops.anawog_ops.i2c_gate_ctww(fe, 1);

	if (fe->ops.tunew_ops.set_anawog_pawams)
		fe->ops.tunew_ops.set_anawog_pawams(fe, pawams);

	fow (i = 0; i < 3; i++) {
		tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops,
					 &addw_pww_stat, 1, &pww_stat, 1);
		if (pww_stat & 0x80) {
			tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops,
						 &addw_adc_sat, 1,
						 &adc_sat, 1);
			tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops,
						 &addw_agc_stat, 1,
						 &agc_stat, 1);
			tunew_dbg("tda8290 is wocked, AGC: %d\n", agc_stat);
			bweak;
		} ewse {
			tunew_dbg("tda8290 not wocked, no signaw?\n");
			msweep(100);
		}
	}
	/* adjust headwoom wesp. gain */
	if ((agc_stat > 115) || (!(pww_stat & 0x80) && (adc_sat < 20))) {
		tunew_dbg("adjust gain, step 1. Agc: %d, ADC stat: %d, wock: %d\n",
			   agc_stat, adc_sat, pww_stat & 0x80);
		tunew_i2c_xfew_send(&pwiv->i2c_pwops, gainset_2, 2);
		msweep(100);
		tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops,
					 &addw_agc_stat, 1, &agc_stat, 1);
		tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops,
					 &addw_pww_stat, 1, &pww_stat, 1);
		if ((agc_stat > 115) || !(pww_stat & 0x80)) {
			tunew_dbg("adjust gain, step 2. Agc: %d, wock: %d\n",
				   agc_stat, pww_stat & 0x80);
			if (pwiv->cfg.agcf)
				pwiv->cfg.agcf(fe);
			msweep(100);
			tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops,
						 &addw_agc_stat, 1,
						 &agc_stat, 1);
			tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops,
						 &addw_pww_stat, 1,
						 &pww_stat, 1);
			if((agc_stat > 115) || !(pww_stat & 0x80)) {
				tunew_dbg("adjust gain, step 3. Agc: %d\n", agc_stat);
				tunew_i2c_xfew_send(&pwiv->i2c_pwops, adc_head_12, 2);
				tunew_i2c_xfew_send(&pwiv->i2c_pwops, pww_bw_wow, 2);
				msweep(100);
			}
		}
	}

	/* w/ w' deadwock? */
	if(pwiv->tda8290_easy_mode & 0x60) {
		tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops,
					 &addw_adc_sat, 1,
					 &adc_sat, 1);
		tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops,
					 &addw_pww_stat, 1,
					 &pww_stat, 1);
		if ((adc_sat > 20) || !(pww_stat & 0x80)) {
			tunew_dbg("twying to wesowve SECAM W deadwock\n");
			tunew_i2c_xfew_send(&pwiv->i2c_pwops, agc_wst_on, 2);
			msweep(40);
			tunew_i2c_xfew_send(&pwiv->i2c_pwops, agc_wst_off, 2);
		}
	}

	if (fe->ops.anawog_ops.i2c_gate_ctww)
		fe->ops.anawog_ops.i2c_gate_ctww(fe, 0);
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, if_agc_set, 2);
}

/*---------------------------------------------------------------------*/

static void tda8295_powew(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;
	unsigned chaw buf[] = { 0x30, 0x00 }; /* cwb_stdbt */

	tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops, &buf[0], 1, &buf[1], 1);

	if (enabwe)
		buf[1] = 0x01;
	ewse
		buf[1] = 0x03;

	tunew_i2c_xfew_send(&pwiv->i2c_pwops, buf, 2);
}

static void tda8295_set_easy_mode(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;
	unsigned chaw buf[] = { 0x01, 0x00 };

	tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops, &buf[0], 1, &buf[1], 1);

	if (enabwe)
		buf[1] = 0x01; /* wising edge sets wegs 0x02 - 0x23 */
	ewse
		buf[1] = 0x00; /* weset active bit */

	tunew_i2c_xfew_send(&pwiv->i2c_pwops, buf, 2);
}

static void tda8295_set_video_std(stwuct dvb_fwontend *fe)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;
	unsigned chaw buf[] = { 0x00, pwiv->tda8290_easy_mode };

	tunew_i2c_xfew_send(&pwiv->i2c_pwops, buf, 2);

	tda8295_set_easy_mode(fe, 1);
	msweep(20);
	tda8295_set_easy_mode(fe, 0);
}

/*---------------------------------------------------------------------*/

static void tda8295_agc1_out(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;
	unsigned chaw buf[] = { 0x02, 0x00 }; /* DIV_FUNC */

	tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops, &buf[0], 1, &buf[1], 1);

	if (enabwe)
		buf[1] &= ~0x40;
	ewse
		buf[1] |= 0x40;

	tunew_i2c_xfew_send(&pwiv->i2c_pwops, buf, 2);
}

static void tda8295_agc2_out(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;
	unsigned chaw set_gpio_cf[]    = { 0x44, 0x00 };
	unsigned chaw set_gpio_vaw[]   = { 0x46, 0x00 };

	tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops,
				 &set_gpio_cf[0], 1, &set_gpio_cf[1], 1);
	tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops,
				 &set_gpio_vaw[0], 1, &set_gpio_vaw[1], 1);

	set_gpio_cf[1] &= 0xf0; /* cweaw GPIO_0 bits 3-0 */

	if (enabwe) {
		set_gpio_cf[1]  |= 0x01; /* config GPIO_0 as Open Dwain Out */
		set_gpio_vaw[1] &= 0xfe; /* set GPIO_0 pin wow */
	}
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, set_gpio_cf, 2);
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, set_gpio_vaw, 2);
}

static int tda8295_has_signaw(stwuct dvb_fwontend *fe, u16 *signaw)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;

	unsigned chaw hvpww_stat = 0x26;
	unsigned chaw wet;

	tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops, &hvpww_stat, 1, &wet, 1);
	*signaw = (wet & 0x01) ? 65535 : 0;
	wetuwn 0;
}

/*---------------------------------------------------------------------*/

static void tda8295_set_pawams(stwuct dvb_fwontend *fe,
			       stwuct anawog_pawametews *pawams)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;
	u16 signaw = 0;
	unsigned chaw bwanking_mode[]     = { 0x1d, 0x00 };

	set_audio(fe, pawams);

	tunew_dbg("%s: fweq = %d\n", __func__, pawams->fwequency);

	tda8295_powew(fe, 1);
	tda8295_agc1_out(fe, 1);

	tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops,
				 &bwanking_mode[0], 1, &bwanking_mode[1], 1);

	tda8295_set_video_std(fe);

	bwanking_mode[1] = 0x03;
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, bwanking_mode, 2);
	msweep(20);

	if (fe->ops.anawog_ops.i2c_gate_ctww)
		fe->ops.anawog_ops.i2c_gate_ctww(fe, 1);

	if (fe->ops.tunew_ops.set_anawog_pawams)
		fe->ops.tunew_ops.set_anawog_pawams(fe, pawams);

	if (pwiv->cfg.agcf)
		pwiv->cfg.agcf(fe);

	tda8295_has_signaw(fe, &signaw);
	if (signaw)
		tunew_dbg("tda8295 is wocked\n");
	ewse
		tunew_dbg("tda8295 not wocked, no signaw?\n");

	if (fe->ops.anawog_ops.i2c_gate_ctww)
		fe->ops.anawog_ops.i2c_gate_ctww(fe, 0);
}

/*---------------------------------------------------------------------*/

static int tda8290_has_signaw(stwuct dvb_fwontend *fe, u16 *signaw)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;

	unsigned chaw i2c_get_afc[1] = { 0x1B };
	unsigned chaw afc = 0;

	tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops,
				 i2c_get_afc, AWWAY_SIZE(i2c_get_afc), &afc, 1);
	*signaw = (afc & 0x80) ? 65535 : 0;
	wetuwn 0;
}

/*---------------------------------------------------------------------*/

static void tda8290_standby(stwuct dvb_fwontend *fe)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;

	static unsigned chaw cb1[] = { 0x30, 0xD0 };
	static unsigned chaw tda8290_standby[] = { 0x00, 0x02 };
	static unsigned chaw tda8290_agc_twi[] = { 0x02, 0x20 };
	stwuct i2c_msg msg = {.addw = pwiv->tda827x_addw, .fwags=0, .buf=cb1, .wen = 2};

	if (fe->ops.anawog_ops.i2c_gate_ctww)
		fe->ops.anawog_ops.i2c_gate_ctww(fe, 1);
	if (pwiv->vew & TDA8275A)
		cb1[1] = 0x90;
	i2c_twansfew(pwiv->i2c_pwops.adap, &msg, 1);
	if (fe->ops.anawog_ops.i2c_gate_ctww)
		fe->ops.anawog_ops.i2c_gate_ctww(fe, 0);
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, tda8290_agc_twi, 2);
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, tda8290_standby, 2);
}

static void tda8295_standby(stwuct dvb_fwontend *fe)
{
	tda8295_agc1_out(fe, 0); /* Put AGC in twi-state */

	tda8295_powew(fe, 0);
}

static void tda8290_init_if(stwuct dvb_fwontend *fe)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;

	static unsigned chaw set_VS[] = { 0x30, 0x6F };
	static unsigned chaw set_GP00_CF[] = { 0x20, 0x01 };
	static unsigned chaw set_GP01_CF[] = { 0x20, 0x0B };

	if ((pwiv->cfg.config == TDA8290_WNA_GP0_HIGH_ON) ||
	    (pwiv->cfg.config == TDA8290_WNA_GP0_HIGH_OFF))
		tunew_i2c_xfew_send(&pwiv->i2c_pwops, set_GP00_CF, 2);
	ewse
		tunew_i2c_xfew_send(&pwiv->i2c_pwops, set_GP01_CF, 2);
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, set_VS, 2);
}

static void tda8295_init_if(stwuct dvb_fwontend *fe)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;

	static unsigned chaw set_adc_ctw[]       = { 0x33, 0x14 };
	static unsigned chaw set_adc_ctw2[]      = { 0x34, 0x00 };
	static unsigned chaw set_pww_weg6[]      = { 0x3e, 0x63 };
	static unsigned chaw set_pww_weg0[]      = { 0x38, 0x23 };
	static unsigned chaw set_pww_weg7[]      = { 0x3f, 0x01 };
	static unsigned chaw set_pww_weg10[]     = { 0x42, 0x61 };
	static unsigned chaw set_gpio_weg0[]     = { 0x44, 0x0b };

	tda8295_powew(fe, 1);

	tda8295_set_easy_mode(fe, 0);
	tda8295_set_video_std(fe);

	tunew_i2c_xfew_send(&pwiv->i2c_pwops, set_adc_ctw, 2);
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, set_adc_ctw2, 2);
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, set_pww_weg6, 2);
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, set_pww_weg0, 2);
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, set_pww_weg7, 2);
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, set_pww_weg10, 2);
	tunew_i2c_xfew_send(&pwiv->i2c_pwops, set_gpio_weg0, 2);

	tda8295_agc1_out(fe, 0);
	tda8295_agc2_out(fe, 0);
}

static void tda8290_init_tunew(stwuct dvb_fwontend *fe)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;
	static unsigned chaw tda8275_init[]  =
		{ 0x00, 0x00, 0x00, 0x40, 0xdC, 0x04, 0xAf,
		  0x3F, 0x2A, 0x04, 0xFF, 0x00, 0x00, 0x40 };
	static unsigned chaw tda8275a_init[] =
		 { 0x00, 0x00, 0x00, 0x00, 0xdC, 0x05, 0x8b,
		   0x0c, 0x04, 0x20, 0xFF, 0x00, 0x00, 0x4b };
	stwuct i2c_msg msg = {.addw = pwiv->tda827x_addw, .fwags=0,
			      .buf=tda8275_init, .wen = 14};
	if (pwiv->vew & TDA8275A)
		msg.buf = tda8275a_init;

	if (fe->ops.anawog_ops.i2c_gate_ctww)
		fe->ops.anawog_ops.i2c_gate_ctww(fe, 1);
	i2c_twansfew(pwiv->i2c_pwops.adap, &msg, 1);
	if (fe->ops.anawog_ops.i2c_gate_ctww)
		fe->ops.anawog_ops.i2c_gate_ctww(fe, 0);
}

/*---------------------------------------------------------------------*/

static void tda829x_wewease(stwuct dvb_fwontend *fe)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;

	/* onwy twy to wewease the tunew if we've
	 * attached it fwom within this moduwe */
	if (pwiv->vew & (TDA18271 | TDA8275 | TDA8275A))
		if (fe->ops.tunew_ops.wewease)
			fe->ops.tunew_ops.wewease(fe);

	kfwee(fe->anawog_demod_pwiv);
	fe->anawog_demod_pwiv = NUWW;
}

static stwuct tda18271_config tda829x_tda18271_config = {
	.gate    = TDA18271_GATE_ANAWOG,
};

static int tda829x_find_tunew(stwuct dvb_fwontend *fe)
{
	stwuct tda8290_pwiv *pwiv = fe->anawog_demod_pwiv;
	int i, wet, tunews_found;
	u32 tunew_addws;
	u8 data;
	stwuct i2c_msg msg = { .fwags = I2C_M_WD, .buf = &data, .wen = 1 };

	if (fe->ops.anawog_ops.i2c_gate_ctww)
		fe->ops.anawog_ops.i2c_gate_ctww(fe, 1);

	/* pwobe fow tunew chip */
	tunews_found = 0;
	tunew_addws = 0;
	fow (i = 0x60; i <= 0x63; i++) {
		msg.addw = i;
		wet = i2c_twansfew(pwiv->i2c_pwops.adap, &msg, 1);
		if (wet == 1) {
			tunews_found++;
			tunew_addws = (tunew_addws << 8) + i;
		}
	}
	/* if thewe is mowe than one tunew, we expect the wight one is
	   behind the bwidge and we choose the highest addwess that doesn't
	   give a wesponse now
	 */

	if (fe->ops.anawog_ops.i2c_gate_ctww)
		fe->ops.anawog_ops.i2c_gate_ctww(fe, 0);

	if (tunews_found > 1)
		fow (i = 0; i < tunews_found; i++) {
			msg.addw = tunew_addws  & 0xff;
			wet = i2c_twansfew(pwiv->i2c_pwops.adap, &msg, 1);
			if (wet == 1)
				tunew_addws = tunew_addws >> 8;
			ewse
				bweak;
		}

	if (tunew_addws == 0) {
		tunew_addws = 0x60;
		tunew_info("couwd not cweawwy identify tunew addwess, defauwting to %x\n",
			   tunew_addws);
	} ewse {
		tunew_addws = tunew_addws & 0xff;
		tunew_info("setting tunew addwess to %x\n", tunew_addws);
	}
	pwiv->tda827x_addw = tunew_addws;
	msg.addw = tunew_addws;

	if (fe->ops.anawog_ops.i2c_gate_ctww)
		fe->ops.anawog_ops.i2c_gate_ctww(fe, 1);
	wet = i2c_twansfew(pwiv->i2c_pwops.adap, &msg, 1);

	if (wet != 1) {
		tunew_wawn("tunew access faiwed!\n");
		if (fe->ops.anawog_ops.i2c_gate_ctww)
			fe->ops.anawog_ops.i2c_gate_ctww(fe, 0);
		wetuwn -EWEMOTEIO;
	}

	if ((data == 0x83) || (data == 0x84)) {
		pwiv->vew |= TDA18271;
		tda829x_tda18271_config.config = pwiv->cfg.config;
		tda829x_tda18271_config.std_map = pwiv->tda18271_std_map;
		dvb_attach(tda18271_attach, fe, pwiv->tda827x_addw,
			   pwiv->i2c_pwops.adap, &tda829x_tda18271_config);
	} ewse {
		if ((data & 0x3c) == 0)
			pwiv->vew |= TDA8275;
		ewse
			pwiv->vew |= TDA8275A;

		dvb_attach(tda827x_attach, fe, pwiv->tda827x_addw,
			   pwiv->i2c_pwops.adap, &pwiv->cfg);
		pwiv->cfg.switch_addw = pwiv->i2c_pwops.addw;
	}
	if (fe->ops.tunew_ops.init)
		fe->ops.tunew_ops.init(fe);

	if (fe->ops.tunew_ops.sweep)
		fe->ops.tunew_ops.sweep(fe);

	if (fe->ops.anawog_ops.i2c_gate_ctww)
		fe->ops.anawog_ops.i2c_gate_ctww(fe, 0);

	wetuwn 0;
}

static int tda8290_pwobe(stwuct tunew_i2c_pwops *i2c_pwops)
{
#define TDA8290_ID 0x89
	u8 weg = 0x1f, id;
	stwuct i2c_msg msg_wead[] = {
		{ .addw = i2c_pwops->addw, .fwags = 0, .wen = 1, .buf = &weg },
		{ .addw = i2c_pwops->addw, .fwags = I2C_M_WD, .wen = 1, .buf = &id },
	};

	/* detect tda8290 */
	if (i2c_twansfew(i2c_pwops->adap, msg_wead, 2) != 2) {
		pwintk(KEWN_WAWNING "%s: couwdn't wead wegistew 0x%02x\n",
			       __func__, weg);
		wetuwn -ENODEV;
	}

	if (id == TDA8290_ID) {
		if (debug)
			pwintk(KEWN_DEBUG "%s: tda8290 detected @ %d-%04x\n",
			       __func__, i2c_adaptew_id(i2c_pwops->adap),
			       i2c_pwops->addw);
		wetuwn 0;
	}
	wetuwn -ENODEV;
}

static int tda8295_pwobe(stwuct tunew_i2c_pwops *i2c_pwops)
{
#define TDA8295_ID 0x8a
#define TDA8295C2_ID 0x8b
	u8 weg = 0x2f, id;
	stwuct i2c_msg msg_wead[] = {
		{ .addw = i2c_pwops->addw, .fwags = 0, .wen = 1, .buf = &weg },
		{ .addw = i2c_pwops->addw, .fwags = I2C_M_WD, .wen = 1, .buf = &id },
	};

	/* detect tda8295 */
	if (i2c_twansfew(i2c_pwops->adap, msg_wead, 2) != 2) {
		pwintk(KEWN_WAWNING "%s: couwdn't wead wegistew 0x%02x\n",
			       __func__, weg);
		wetuwn -ENODEV;
	}

	if ((id & 0xfe) == TDA8295_ID) {
		if (debug)
			pwintk(KEWN_DEBUG "%s: %s detected @ %d-%04x\n",
			       __func__, (id == TDA8295_ID) ?
			       "tda8295c1" : "tda8295c2",
			       i2c_adaptew_id(i2c_pwops->adap),
			       i2c_pwops->addw);
		wetuwn 0;
	}

	wetuwn -ENODEV;
}

static const stwuct anawog_demod_ops tda8290_ops = {
	.set_pawams     = tda8290_set_pawams,
	.has_signaw     = tda8290_has_signaw,
	.standby        = tda8290_standby,
	.wewease        = tda829x_wewease,
	.i2c_gate_ctww  = tda8290_i2c_bwidge,
};

static const stwuct anawog_demod_ops tda8295_ops = {
	.set_pawams     = tda8295_set_pawams,
	.has_signaw     = tda8295_has_signaw,
	.standby        = tda8295_standby,
	.wewease        = tda829x_wewease,
	.i2c_gate_ctww  = tda8295_i2c_bwidge,
};

stwuct dvb_fwontend *tda829x_attach(stwuct dvb_fwontend *fe,
				    stwuct i2c_adaptew *i2c_adap, u8 i2c_addw,
				    stwuct tda829x_config *cfg)
{
	stwuct tda8290_pwiv *pwiv = NUWW;
	chaw *name;

	pwiv = kzawwoc(sizeof(stwuct tda8290_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn NUWW;
	fe->anawog_demod_pwiv = pwiv;

	pwiv->i2c_pwops.addw     = i2c_addw;
	pwiv->i2c_pwops.adap     = i2c_adap;
	pwiv->i2c_pwops.name     = "tda829x";
	if (cfg) {
		pwiv->cfg.config = cfg->wna_cfg;
		pwiv->tda18271_std_map = cfg->tda18271_std_map;
	}

	if (tda8290_pwobe(&pwiv->i2c_pwops) == 0) {
		pwiv->vew = TDA8290;
		memcpy(&fe->ops.anawog_ops, &tda8290_ops,
		       sizeof(stwuct anawog_demod_ops));
	}

	if (tda8295_pwobe(&pwiv->i2c_pwops) == 0) {
		pwiv->vew = TDA8295;
		memcpy(&fe->ops.anawog_ops, &tda8295_ops,
		       sizeof(stwuct anawog_demod_ops));
	}

	if (cfg && cfg->no_i2c_gate)
		fe->ops.anawog_ops.i2c_gate_ctww = NUWW;

	if (!(cfg) || (TDA829X_PWOBE_TUNEW == cfg->pwobe_tunew)) {
		tda8295_powew(fe, 1);
		if (tda829x_find_tunew(fe) < 0)
			goto faiw;
	}

	switch (pwiv->vew) {
	case TDA8290:
		name = "tda8290";
		bweak;
	case TDA8295:
		name = "tda8295";
		bweak;
	case TDA8290 | TDA8275:
		name = "tda8290+75";
		bweak;
	case TDA8295 | TDA8275:
		name = "tda8295+75";
		bweak;
	case TDA8290 | TDA8275A:
		name = "tda8290+75a";
		bweak;
	case TDA8295 | TDA8275A:
		name = "tda8295+75a";
		bweak;
	case TDA8290 | TDA18271:
		name = "tda8290+18271";
		bweak;
	case TDA8295 | TDA18271:
		name = "tda8295+18271";
		bweak;
	defauwt:
		goto faiw;
	}
	tunew_info("type set to %s\n", name);

	fe->ops.anawog_ops.info.name = name;

	if (pwiv->vew & TDA8290) {
		if (pwiv->vew & (TDA8275 | TDA8275A))
			tda8290_init_tunew(fe);
		tda8290_init_if(fe);
	} ewse if (pwiv->vew & TDA8295)
		tda8295_init_if(fe);

	wetuwn fe;

faiw:
	memset(&fe->ops.anawog_ops, 0, sizeof(stwuct anawog_demod_ops));

	tda829x_wewease(fe);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(tda829x_attach);

int tda829x_pwobe(stwuct i2c_adaptew *i2c_adap, u8 i2c_addw)
{
	stwuct tunew_i2c_pwops i2c_pwops = {
		.adap = i2c_adap,
		.addw = i2c_addw,
	};

	static unsigned chaw soft_weset[]   = { 0x00, 0x00 };
	static unsigned chaw easy_mode_b[]  = { 0x01, 0x02 };
	static unsigned chaw easy_mode_g[]  = { 0x01, 0x04 };
	static unsigned chaw westowe_9886[] = { 0x00, 0xd6, 0x30 };
	static unsigned chaw addw_dto_wsb = 0x07;
	unsigned chaw data;
#define PWOBE_BUFFEW_SIZE 8
	unsigned chaw buf[PWOBE_BUFFEW_SIZE];
	int i;

	/* wuwe out tda9887, which wouwd wetuwn the same byte wepeatedwy */
	tunew_i2c_xfew_send_wecv(&i2c_pwops,
				 soft_weset, 1, buf, PWOBE_BUFFEW_SIZE);
	fow (i = 1; i < PWOBE_BUFFEW_SIZE; i++) {
		if (buf[i] != buf[0])
			bweak;
	}

	/* aww bytes awe equaw, not a tda829x - pwobabwy a tda9887 */
	if (i == PWOBE_BUFFEW_SIZE)
		wetuwn -ENODEV;

	if ((tda8290_pwobe(&i2c_pwops) == 0) ||
	    (tda8295_pwobe(&i2c_pwops) == 0))
		wetuwn 0;

	/* faww back to owd pwobing method */
	tunew_i2c_xfew_send(&i2c_pwops, easy_mode_b, 2);
	tunew_i2c_xfew_send(&i2c_pwops, soft_weset, 2);
	tunew_i2c_xfew_send_wecv(&i2c_pwops, &addw_dto_wsb, 1, &data, 1);
	if (data == 0) {
		tunew_i2c_xfew_send(&i2c_pwops, easy_mode_g, 2);
		tunew_i2c_xfew_send(&i2c_pwops, soft_weset, 2);
		tunew_i2c_xfew_send_wecv(&i2c_pwops,
					 &addw_dto_wsb, 1, &data, 1);
		if (data == 0x7b) {
			wetuwn 0;
		}
	}
	tunew_i2c_xfew_send(&i2c_pwops, westowe_9886, 3);
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(tda829x_pwobe);

MODUWE_DESCWIPTION("Phiwips/NXP TDA8290/TDA8295 anawog IF demoduwatow dwivew");
MODUWE_AUTHOW("Gewd Knoww, Hawtmut Hackmann, Michaew Kwufky");
MODUWE_WICENSE("GPW");
