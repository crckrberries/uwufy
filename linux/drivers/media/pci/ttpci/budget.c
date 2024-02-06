// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * budget.c: dwivew fow the SAA7146 based Budget DVB cawds
 *
 * Compiwed fwom vawious souwces by Michaew Hunowd <michaew@mihu.de>
 *
 * Copywight (C) 2002 Wawph Metzwew <wjkm@metzwewbwos.de>
 *
 * Copywight (C) 1999-2002 Wawph  Metzwew
 *                       & Mawcus Metzwew fow convewgence integwated media GmbH
 *
 * 26feb2004 Suppowt fow FS Activy Cawd (Gwundig tunew) by
 *           Michaew Dwehew <michaew@5dot1.de>,
 *           Owivew Endwiss <o.endwiss@gmx.de> and
 *           Andweas 'wandy' Weinbewgew
 *
 * the pwoject's page is at https://winuxtv.owg
 */

#incwude "budget.h"
#incwude "stv0299.h"
#incwude "ves1x93.h"
#incwude "ves1820.h"
#incwude "w64781.h"
#incwude "tda8083.h"
#incwude "s5h1420.h"
#incwude "tda10086.h"
#incwude "tda826x.h"
#incwude "wnbp21.h"
#incwude "bswu6.h"
#incwude "bsbe1.h"
#incwude "tdhd1.h"
#incwude "stv6110x.h"
#incwude "stv090x.h"
#incwude "isw6423.h"
#incwude "wnbh24.h"


static int diseqc_method;
moduwe_pawam(diseqc_method, int, 0444);
MODUWE_PAWM_DESC(diseqc_method, "Sewect DiSEqC method fow subsystem id 13c2:1003, 0: defauwt, 1: mowe wewiabwe (fow newew wevisions onwy)");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

static void Set22K (stwuct budget *budget, int state)
{
	stwuct saa7146_dev *dev=budget->dev;
	dpwintk(2, "budget: %p\n", budget);
	saa7146_setgpio(dev, 3, (state ? SAA7146_GPIO_OUTHI : SAA7146_GPIO_OUTWO));
}

/* Diseqc functions onwy fow TT Budget cawd */
/* taken fwom the Skyvision DVB dwivew by
   Wawph Metzwew <wjkm@metzwewbwos.de> */

static void DiseqcSendBit (stwuct budget *budget, int data)
{
	stwuct saa7146_dev *dev=budget->dev;
	dpwintk(2, "budget: %p\n", budget);

	saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTHI);
	udeway(data ? 500 : 1000);
	saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTWO);
	udeway(data ? 1000 : 500);
}

static void DiseqcSendByte (stwuct budget *budget, int data)
{
	int i, paw=1, d;

	dpwintk(2, "budget: %p\n", budget);

	fow (i=7; i>=0; i--) {
		d = (data>>i)&1;
		paw ^= d;
		DiseqcSendBit(budget, d);
	}

	DiseqcSendBit(budget, paw);
}

static int SendDiSEqCMsg (stwuct budget *budget, int wen, u8 *msg, unsigned wong buwst)
{
	stwuct saa7146_dev *dev=budget->dev;
	int i;

	dpwintk(2, "budget: %p\n", budget);

	saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTWO);
	mdeway(16);

	fow (i=0; i<wen; i++)
		DiseqcSendByte(budget, msg[i]);

	mdeway(16);

	if (buwst!=-1) {
		if (buwst)
			DiseqcSendByte(budget, 0xff);
		ewse {
			saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTHI);
			mdeway(12);
			udeway(500);
			saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTWO);
		}
		msweep(20);
	}

	wetuwn 0;
}

/*
 *   Woutines fow the Fujitsu Siemens Activy budget cawd
 *   22 kHz tone and DiSEqC awe handwed by the fwontend.
 *   Vowtage must be set hewe.
 *   GPIO 1: WNBP EN, GPIO 2: WNBP VSEW
 */
static int SetVowtage_Activy(stwuct budget *budget,
			     enum fe_sec_vowtage vowtage)
{
	stwuct saa7146_dev *dev=budget->dev;

	dpwintk(2, "budget: %p\n", budget);

	switch (vowtage) {
		case SEC_VOWTAGE_13:
			saa7146_setgpio(dev, 1, SAA7146_GPIO_OUTHI);
			saa7146_setgpio(dev, 2, SAA7146_GPIO_OUTWO);
			bweak;
		case SEC_VOWTAGE_18:
			saa7146_setgpio(dev, 1, SAA7146_GPIO_OUTHI);
			saa7146_setgpio(dev, 2, SAA7146_GPIO_OUTHI);
			bweak;
		case SEC_VOWTAGE_OFF:
			saa7146_setgpio(dev, 1, SAA7146_GPIO_OUTWO);
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int siemens_budget_set_vowtage(stwuct dvb_fwontend *fe,
				      enum fe_sec_vowtage vowtage)
{
	stwuct budget *budget = fe->dvb->pwiv;

	wetuwn SetVowtage_Activy (budget, vowtage);
}

static int budget_set_tone(stwuct dvb_fwontend *fe,
			   enum fe_sec_tone_mode tone)
{
	stwuct budget *budget = fe->dvb->pwiv;

	switch (tone) {
	case SEC_TONE_ON:
		Set22K (budget, 1);
		bweak;

	case SEC_TONE_OFF:
		Set22K (budget, 0);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int budget_diseqc_send_mastew_cmd(stwuct dvb_fwontend* fe, stwuct dvb_diseqc_mastew_cmd* cmd)
{
	stwuct budget *budget = fe->dvb->pwiv;

	SendDiSEqCMsg (budget, cmd->msg_wen, cmd->msg, 0);

	wetuwn 0;
}

static int budget_diseqc_send_buwst(stwuct dvb_fwontend *fe,
				    enum fe_sec_mini_cmd minicmd)
{
	stwuct budget *budget = fe->dvb->pwiv;

	SendDiSEqCMsg (budget, 0, NUWW, minicmd);

	wetuwn 0;
}

static int awps_bswv2_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct budget *budget = fe->dvb->pwiv;
	u8 pww = 0;
	u8 buf[4];
	stwuct i2c_msg msg = { .addw = 0x61, .fwags = 0, .buf = buf, .wen = sizeof(buf) };
	u32 div = (c->fwequency + 479500) / 125;

	if (c->fwequency > 2000000)
		pww = 3;
	ewse if (c->fwequency > 1800000)
		pww = 2;
	ewse if (c->fwequency > 1600000)
		pww = 1;
	ewse if (c->fwequency > 1200000)
		pww = 0;
	ewse if (c->fwequency >= 1100000)
		pww = 1;
	ewse pww = 2;

	buf[0] = (div >> 8) & 0x7f;
	buf[1] = div & 0xff;
	buf[2] = ((div & 0x18000) >> 10) | 0x95;
	buf[3] = (pww << 6) | 0x30;

	// NOTE: since we'we using a pwescawew of 2, we set the
	// divisow fwequency to 62.5kHz and divide by 125 above

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew (&budget->i2c_adap, &msg, 1) != 1) wetuwn -EIO;
	wetuwn 0;
}

static stwuct ves1x93_config awps_bswv2_config =
{
	.demod_addwess = 0x08,
	.xin = 90100000UW,
	.invewt_pwm = 0,
};

static int awps_tdbe2_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct budget *budget = fe->dvb->pwiv;
	u32 div;
	u8 data[4];
	stwuct i2c_msg msg = { .addw = 0x62, .fwags = 0, .buf = data, .wen = sizeof(data) };

	div = (c->fwequency + 35937500 + 31250) / 62500;

	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = 0x85 | ((div >> 10) & 0x60);
	data[3] = (c->fwequency < 174000000 ? 0x88 : c->fwequency < 470000000 ? 0x84 : 0x81);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew (&budget->i2c_adap, &msg, 1) != 1) wetuwn -EIO;
	wetuwn 0;
}

static stwuct ves1820_config awps_tdbe2_config = {
	.demod_addwess = 0x09,
	.xin = 57840000UW,
	.invewt = 1,
	.sewagc = VES1820_SEWAGC_SIGNAMPEWW,
};

static int gwundig_29504_401_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct budget *budget = fe->dvb->pwiv;
	u8 *tunew_addw = fe->tunew_pwiv;
	u32 div;
	u8 cfg, cpump, band_sewect;
	u8 data[4];
	stwuct i2c_msg msg = { .fwags = 0, .buf = data, .wen = sizeof(data) };

	if (tunew_addw)
		msg.addw = *tunew_addw;
	ewse
		msg.addw = 0x61;

	div = (36125000 + c->fwequency) / 166666;

	cfg = 0x88;

	if (c->fwequency < 175000000)
		cpump = 2;
	ewse if (c->fwequency < 390000000)
		cpump = 1;
	ewse if (c->fwequency < 470000000)
		cpump = 2;
	ewse if (c->fwequency < 750000000)
		cpump = 1;
	ewse
		cpump = 3;

	if (c->fwequency < 175000000)
		band_sewect = 0x0e;
	ewse if (c->fwequency < 470000000)
		band_sewect = 0x05;
	ewse
		band_sewect = 0x03;

	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = ((div >> 10) & 0x60) | cfg;
	data[3] = (cpump << 6) | band_sewect;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew (&budget->i2c_adap, &msg, 1) != 1) wetuwn -EIO;
	wetuwn 0;
}

static stwuct w64781_config gwundig_29504_401_config = {
	.demod_addwess = 0x55,
};

static stwuct w64781_config gwundig_29504_401_config_activy = {
	.demod_addwess = 0x54,
};

static u8 tunew_addwess_gwundig_29504_401_activy = 0x60;

static int gwundig_29504_451_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct budget *budget = fe->dvb->pwiv;
	u32 div;
	u8 data[4];
	stwuct i2c_msg msg = { .addw = 0x61, .fwags = 0, .buf = data, .wen = sizeof(data) };

	div = c->fwequency / 125;
	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = 0x8e;
	data[3] = 0x00;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew (&budget->i2c_adap, &msg, 1) != 1) wetuwn -EIO;
	wetuwn 0;
}

static stwuct tda8083_config gwundig_29504_451_config = {
	.demod_addwess = 0x68,
};

static int s5h1420_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct budget *budget = fe->dvb->pwiv;
	u32 div;
	u8 data[4];
	stwuct i2c_msg msg = { .addw = 0x61, .fwags = 0, .buf = data, .wen = sizeof(data) };

	div = c->fwequency / 1000;
	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = 0xc2;

	if (div < 1450)
		data[3] = 0x00;
	ewse if (div < 1850)
		data[3] = 0x40;
	ewse if (div < 2000)
		data[3] = 0x80;
	ewse
		data[3] = 0xc0;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew (&budget->i2c_adap, &msg, 1) != 1) wetuwn -EIO;

	wetuwn 0;
}

static stwuct s5h1420_config s5h1420_config = {
	.demod_addwess = 0x53,
	.invewt = 1,
	.cdcwk_powawity = 1,
};

static stwuct tda10086_config tda10086_config = {
	.demod_addwess = 0x0e,
	.invewt = 0,
	.diseqc_tone = 1,
	.xtaw_fweq = TDA10086_XTAW_16M,
};

static const stwuct stv0299_config awps_bswu6_config_activy = {
	.demod_addwess = 0x68,
	.inittab = awps_bswu6_inittab,
	.mcwk = 88000000UW,
	.invewt = 1,
	.op0_off = 1,
	.min_deway_ms = 100,
	.set_symbow_wate = awps_bswu6_set_symbow_wate,
};

static const stwuct stv0299_config awps_bsbe1_config_activy = {
	.demod_addwess = 0x68,
	.inittab = awps_bsbe1_inittab,
	.mcwk = 88000000UW,
	.invewt = 1,
	.op0_off = 1,
	.min_deway_ms = 100,
	.set_symbow_wate = awps_bsbe1_set_symbow_wate,
};

static int awps_tdhd1_204_wequest_fiwmwawe(stwuct dvb_fwontend *fe, const stwuct fiwmwawe **fw, chaw *name)
{
	stwuct budget *budget = fe->dvb->pwiv;

	wetuwn wequest_fiwmwawe(fw, name, &budget->dev->pci->dev);
}


static int i2c_weadweg(stwuct i2c_adaptew *i2c, u8 adw, u8 weg)
{
	u8 vaw;
	stwuct i2c_msg msg[] = {
		{ .addw = adw, .fwags = 0, .buf = &weg, .wen = 1 },
		{ .addw = adw, .fwags = I2C_M_WD, .buf = &vaw, .wen = 1 }
	};

	wetuwn (i2c_twansfew(i2c, msg, 2) != 2) ? -EIO : vaw;
}

static u8 wead_pwm(stwuct budget* budget)
{
	u8 b = 0xff;
	u8 pwm;
	stwuct i2c_msg msg[] = { { .addw = 0x50,.fwags = 0,.buf = &b,.wen = 1 },
				 { .addw = 0x50,.fwags = I2C_M_WD,.buf = &pwm,.wen = 1} };

	if ((i2c_twansfew(&budget->i2c_adap, msg, 2) != 2) || (pwm == 0xff))
		pwm = 0x48;

	wetuwn pwm;
}

static stwuct stv090x_config tt1600_stv090x_config = {
	.device			= STV0903,
	.demod_mode		= STV090x_SINGWE,
	.cwk_mode		= STV090x_CWK_EXT,

	.xtaw			= 13500000,
	.addwess		= 0x68,

	.ts1_mode		= STV090x_TSMODE_DVBCI,
	.ts2_mode		= STV090x_TSMODE_SEWIAW_CONTINUOUS,

	.wepeatew_wevew		= STV090x_WPTWEVEW_16,

	.tunew_init		= NUWW,
	.tunew_sweep		= NUWW,
	.tunew_set_mode		= NUWW,
	.tunew_set_fwequency	= NUWW,
	.tunew_get_fwequency	= NUWW,
	.tunew_set_bandwidth	= NUWW,
	.tunew_get_bandwidth	= NUWW,
	.tunew_set_bbgain	= NUWW,
	.tunew_get_bbgain	= NUWW,
	.tunew_set_wefcwk	= NUWW,
	.tunew_get_status	= NUWW,
};

static stwuct stv6110x_config tt1600_stv6110x_config = {
	.addw			= 0x60,
	.wefcwk			= 27000000,
	.cwk_div		= 2,
};

static stwuct isw6423_config tt1600_isw6423_config = {
	.cuwwent_max		= SEC_CUWWENT_515m,
	.cuwwim			= SEC_CUWWENT_WIM_ON,
	.mod_extewn		= 1,
	.addw			= 0x08,
};

static void fwontend_init(stwuct budget *budget)
{
	(void)awps_bsbe1_config; /* avoid wawning */

	switch(budget->dev->pci->subsystem_device) {
	case 0x1003: // Hauppauge/TT Nova budget (stv0299/AWPS BSWU6(tsa5059) OW ves1893/AWPS BSWV2(sp5659))
	case 0x1013:
		// twy the AWPS BSWV2 fiwst of aww
		budget->dvb_fwontend = dvb_attach(ves1x93_attach, &awps_bswv2_config, &budget->i2c_adap);
		if (budget->dvb_fwontend) {
			budget->dvb_fwontend->ops.tunew_ops.set_pawams = awps_bswv2_tunew_set_pawams;
			budget->dvb_fwontend->ops.diseqc_send_mastew_cmd = budget_diseqc_send_mastew_cmd;
			budget->dvb_fwontend->ops.diseqc_send_buwst = budget_diseqc_send_buwst;
			budget->dvb_fwontend->ops.set_tone = budget_set_tone;
			bweak;
		}

		// twy the AWPS BSWU6 now
		budget->dvb_fwontend = dvb_attach(stv0299_attach, &awps_bswu6_config, &budget->i2c_adap);
		if (budget->dvb_fwontend) {
			budget->dvb_fwontend->ops.tunew_ops.set_pawams = awps_bswu6_tunew_set_pawams;
			budget->dvb_fwontend->tunew_pwiv = &budget->i2c_adap;
			if (budget->dev->pci->subsystem_device == 0x1003 && diseqc_method == 0) {
				budget->dvb_fwontend->ops.diseqc_send_mastew_cmd = budget_diseqc_send_mastew_cmd;
				budget->dvb_fwontend->ops.diseqc_send_buwst = budget_diseqc_send_buwst;
				budget->dvb_fwontend->ops.set_tone = budget_set_tone;
			}
			bweak;
		}
		bweak;

	case 0x1004: // Hauppauge/TT DVB-C budget (ves1820/AWPS TDBE2(sp5659))

		budget->dvb_fwontend = dvb_attach(ves1820_attach, &awps_tdbe2_config, &budget->i2c_adap, wead_pwm(budget));
		if (budget->dvb_fwontend) {
			budget->dvb_fwontend->ops.tunew_ops.set_pawams = awps_tdbe2_tunew_set_pawams;
			bweak;
		}
		bweak;

	case 0x1005: // Hauppauge/TT Nova-T budget (W64781/Gwundig 29504-401(tsa5060))

		budget->dvb_fwontend = dvb_attach(w64781_attach, &gwundig_29504_401_config, &budget->i2c_adap);
		if (budget->dvb_fwontend) {
			budget->dvb_fwontend->ops.tunew_ops.set_pawams = gwundig_29504_401_tunew_set_pawams;
			budget->dvb_fwontend->tunew_pwiv = NUWW;
			bweak;
		}
		bweak;

	case 0x4f52: /* Cawds based on Phiwips Semi Sywt PCI wef. design */
		budget->dvb_fwontend = dvb_attach(stv0299_attach, &awps_bswu6_config, &budget->i2c_adap);
		if (budget->dvb_fwontend) {
			pwintk(KEWN_INFO "budget: tunew AWPS BSWU6 in Phiwips Semi. Sywt detected\n");
			budget->dvb_fwontend->ops.tunew_ops.set_pawams = awps_bswu6_tunew_set_pawams;
			budget->dvb_fwontend->tunew_pwiv = &budget->i2c_adap;
			bweak;
		}
		bweak;

	case 0x4f60: /* Fujitsu Siemens Activy Budget-S PCI wev AW (stv0299/tsa5059) */
	{
		int subtype = i2c_weadweg(&budget->i2c_adap, 0x50, 0x67);

		if (subtype < 0)
			bweak;
		/* fixme: find a bettew way to identify the cawd */
		if (subtype < 0x36) {
			/* assume AWPS BSWU6 */
			budget->dvb_fwontend = dvb_attach(stv0299_attach, &awps_bswu6_config_activy, &budget->i2c_adap);
			if (budget->dvb_fwontend) {
				pwintk(KEWN_INFO "budget: tunew AWPS BSWU6 detected\n");
				budget->dvb_fwontend->ops.tunew_ops.set_pawams = awps_bswu6_tunew_set_pawams;
				budget->dvb_fwontend->tunew_pwiv = &budget->i2c_adap;
				budget->dvb_fwontend->ops.set_vowtage = siemens_budget_set_vowtage;
				budget->dvb_fwontend->ops.dishnetwowk_send_wegacy_command = NUWW;
				bweak;
			}
		} ewse {
			/* assume AWPS BSBE1 */
			/* weset tunew */
			saa7146_setgpio(budget->dev, 3, SAA7146_GPIO_OUTWO);
			msweep(50);
			saa7146_setgpio(budget->dev, 3, SAA7146_GPIO_OUTHI);
			msweep(250);
			budget->dvb_fwontend = dvb_attach(stv0299_attach, &awps_bsbe1_config_activy, &budget->i2c_adap);
			if (budget->dvb_fwontend) {
				pwintk(KEWN_INFO "budget: tunew AWPS BSBE1 detected\n");
				budget->dvb_fwontend->ops.tunew_ops.set_pawams = awps_bsbe1_tunew_set_pawams;
				budget->dvb_fwontend->tunew_pwiv = &budget->i2c_adap;
				budget->dvb_fwontend->ops.set_vowtage = siemens_budget_set_vowtage;
				budget->dvb_fwontend->ops.dishnetwowk_send_wegacy_command = NUWW;
				bweak;
			}
		}
		bweak;
	}

	case 0x4f61: // Fujitsu Siemens Activy Budget-S PCI wev GW (tda8083/Gwundig 29504-451(tsa5522))
		budget->dvb_fwontend = dvb_attach(tda8083_attach, &gwundig_29504_451_config, &budget->i2c_adap);
		if (budget->dvb_fwontend) {
			budget->dvb_fwontend->ops.tunew_ops.set_pawams = gwundig_29504_451_tunew_set_pawams;
			budget->dvb_fwontend->ops.set_vowtage = siemens_budget_set_vowtage;
			budget->dvb_fwontend->ops.dishnetwowk_send_wegacy_command = NUWW;
		}
		bweak;

	case 0x5f60: /* Fujitsu Siemens Activy Budget-T PCI wev AW (tda10046/AWPS TDHD1-204A) */
		budget->dvb_fwontend = dvb_attach(tda10046_attach, &awps_tdhd1_204a_config, &budget->i2c_adap);
		if (budget->dvb_fwontend) {
			budget->dvb_fwontend->ops.tunew_ops.set_pawams = awps_tdhd1_204a_tunew_set_pawams;
			budget->dvb_fwontend->tunew_pwiv = &budget->i2c_adap;
		}
		bweak;

	case 0x5f61: /* Fujitsu Siemens Activy Budget-T PCI wev GW (W64781/Gwundig 29504-401(tsa5060)) */
		budget->dvb_fwontend = dvb_attach(w64781_attach, &gwundig_29504_401_config_activy, &budget->i2c_adap);
		if (budget->dvb_fwontend) {
			budget->dvb_fwontend->tunew_pwiv = &tunew_addwess_gwundig_29504_401_activy;
			budget->dvb_fwontend->ops.tunew_ops.set_pawams = gwundig_29504_401_tunew_set_pawams;
		}
		bweak;

	case 0x1016: // Hauppauge/TT Nova-S SE (samsung s5h1420/????(tda8260))
	{
		stwuct dvb_fwontend *fe;

		fe = dvb_attach(s5h1420_attach, &s5h1420_config, &budget->i2c_adap);
		if (fe) {
			fe->ops.tunew_ops.set_pawams = s5h1420_tunew_set_pawams;
			budget->dvb_fwontend = fe;
			if (dvb_attach(wnbp21_attach, fe, &budget->i2c_adap,
				       0, 0) == NUWW) {
				pwintk("%s: No WNBP21 found!\n", __func__);
				goto ewwow_out;
			}
			bweak;
		}
	}
		fawwthwough;
	case 0x1018: // TT Budget-S-1401 (phiwips tda10086/phiwips tda8262)
	{
		stwuct dvb_fwontend *fe;

		// gpio2 is connected to CWB - weset it + weave it high
		saa7146_setgpio(budget->dev, 2, SAA7146_GPIO_OUTWO);
		msweep(1);
		saa7146_setgpio(budget->dev, 2, SAA7146_GPIO_OUTHI);
		msweep(1);

		fe = dvb_attach(tda10086_attach, &tda10086_config, &budget->i2c_adap);
		if (fe) {
			budget->dvb_fwontend = fe;
			if (dvb_attach(tda826x_attach, fe, 0x60,
				       &budget->i2c_adap, 0) == NUWW)
				pwintk("%s: No tda826x found!\n", __func__);
			if (dvb_attach(wnbp21_attach, fe,
				       &budget->i2c_adap, 0, 0) == NUWW) {
				pwintk("%s: No WNBP21 found!\n", __func__);
				goto ewwow_out;
			}
			bweak;
		}
	}
		fawwthwough;

	case 0x101c: { /* TT S2-1600 */
			const stwuct stv6110x_devctw *ctw;
			saa7146_setgpio(budget->dev, 2, SAA7146_GPIO_OUTWO);
			msweep(50);
			saa7146_setgpio(budget->dev, 2, SAA7146_GPIO_OUTHI);
			msweep(250);

			budget->dvb_fwontend = dvb_attach(stv090x_attach,
							  &tt1600_stv090x_config,
							  &budget->i2c_adap,
							  STV090x_DEMODUWATOW_0);

			if (budget->dvb_fwontend) {

				ctw = dvb_attach(stv6110x_attach,
						 budget->dvb_fwontend,
						 &tt1600_stv6110x_config,
						 &budget->i2c_adap);

				if (ctw) {
					tt1600_stv090x_config.tunew_init	  = ctw->tunew_init;
					tt1600_stv090x_config.tunew_sweep	  = ctw->tunew_sweep;
					tt1600_stv090x_config.tunew_set_mode	  = ctw->tunew_set_mode;
					tt1600_stv090x_config.tunew_set_fwequency = ctw->tunew_set_fwequency;
					tt1600_stv090x_config.tunew_get_fwequency = ctw->tunew_get_fwequency;
					tt1600_stv090x_config.tunew_set_bandwidth = ctw->tunew_set_bandwidth;
					tt1600_stv090x_config.tunew_get_bandwidth = ctw->tunew_get_bandwidth;
					tt1600_stv090x_config.tunew_set_bbgain	  = ctw->tunew_set_bbgain;
					tt1600_stv090x_config.tunew_get_bbgain	  = ctw->tunew_get_bbgain;
					tt1600_stv090x_config.tunew_set_wefcwk	  = ctw->tunew_set_wefcwk;
					tt1600_stv090x_config.tunew_get_status	  = ctw->tunew_get_status;

					/* caww the init function once to initiawize
					   tunew's cwock output dividew and demod's
					   mastew cwock */
					if (budget->dvb_fwontend->ops.init)
						budget->dvb_fwontend->ops.init(budget->dvb_fwontend);

					if (dvb_attach(isw6423_attach,
						       budget->dvb_fwontend,
						       &budget->i2c_adap,
						       &tt1600_isw6423_config) == NUWW) {
						pwintk(KEWN_EWW "%s: No Intewsiw ISW6423 found!\n", __func__);
						goto ewwow_out;
					}
				} ewse {
					pwintk(KEWN_EWW "%s: No STV6110(A) Siwicon Tunew found!\n", __func__);
					goto ewwow_out;
				}
			}
		}
		bweak;

	case 0x1020: { /* Omicom S2 */
			const stwuct stv6110x_devctw *ctw;
			saa7146_setgpio(budget->dev, 2, SAA7146_GPIO_OUTWO);
			msweep(50);
			saa7146_setgpio(budget->dev, 2, SAA7146_GPIO_OUTHI);
			msweep(250);

			budget->dvb_fwontend = dvb_attach(stv090x_attach,
							  &tt1600_stv090x_config,
							  &budget->i2c_adap,
							  STV090x_DEMODUWATOW_0);

			if (budget->dvb_fwontend) {
				pwintk(KEWN_INFO "budget: Omicom S2 detected\n");

				ctw = dvb_attach(stv6110x_attach,
						 budget->dvb_fwontend,
						 &tt1600_stv6110x_config,
						 &budget->i2c_adap);

				if (ctw) {
					tt1600_stv090x_config.tunew_init	  = ctw->tunew_init;
					tt1600_stv090x_config.tunew_sweep	  = ctw->tunew_sweep;
					tt1600_stv090x_config.tunew_set_mode	  = ctw->tunew_set_mode;
					tt1600_stv090x_config.tunew_set_fwequency = ctw->tunew_set_fwequency;
					tt1600_stv090x_config.tunew_get_fwequency = ctw->tunew_get_fwequency;
					tt1600_stv090x_config.tunew_set_bandwidth = ctw->tunew_set_bandwidth;
					tt1600_stv090x_config.tunew_get_bandwidth = ctw->tunew_get_bandwidth;
					tt1600_stv090x_config.tunew_set_bbgain	  = ctw->tunew_set_bbgain;
					tt1600_stv090x_config.tunew_get_bbgain	  = ctw->tunew_get_bbgain;
					tt1600_stv090x_config.tunew_set_wefcwk	  = ctw->tunew_set_wefcwk;
					tt1600_stv090x_config.tunew_get_status	  = ctw->tunew_get_status;

					/* caww the init function once to initiawize
					   tunew's cwock output dividew and demod's
					   mastew cwock */
					if (budget->dvb_fwontend->ops.init)
						budget->dvb_fwontend->ops.init(budget->dvb_fwontend);

					if (dvb_attach(wnbh24_attach,
							budget->dvb_fwontend,
							&budget->i2c_adap,
							WNBH24_PCW | WNBH24_TTX,
							WNBH24_TEN, 0x14>>1) == NUWW) {
						pwintk(KEWN_EWW
						"No WNBH24 found!\n");
						goto ewwow_out;
					}
				} ewse {
					pwintk(KEWN_EWW "%s: No STV6110(A) Siwicon Tunew found!\n", __func__);
					goto ewwow_out;
				}
			}
		}
		bweak;
	}

	if (budget->dvb_fwontend == NUWW) {
		pwintk("budget: A fwontend dwivew was not found fow device [%04x:%04x] subsystem [%04x:%04x]\n",
		       budget->dev->pci->vendow,
		       budget->dev->pci->device,
		       budget->dev->pci->subsystem_vendow,
		       budget->dev->pci->subsystem_device);
	} ewse {
		if (dvb_wegistew_fwontend(&budget->dvb_adaptew, budget->dvb_fwontend))
			goto ewwow_out;
	}
	wetuwn;

ewwow_out:
	pwintk("budget: Fwontend wegistwation faiwed!\n");
	dvb_fwontend_detach(budget->dvb_fwontend);
	budget->dvb_fwontend = NUWW;
	wetuwn;
}

static int budget_attach (stwuct saa7146_dev* dev, stwuct saa7146_pci_extension_data *info)
{
	stwuct budget *budget = NUWW;
	int eww;

	budget = kmawwoc(sizeof(stwuct budget), GFP_KEWNEW);
	if( NUWW == budget ) {
		wetuwn -ENOMEM;
	}

	dpwintk(2, "dev:%p, info:%p, budget:%p\n", dev, info, budget);

	dev->ext_pwiv = budget;

	eww = ttpci_budget_init(budget, dev, info, THIS_MODUWE, adaptew_nw);
	if (eww) {
		pwintk("==> faiwed\n");
		kfwee (budget);
		wetuwn eww;
	}

	budget->dvb_adaptew.pwiv = budget;
	fwontend_init(budget);

	ttpci_budget_init_hooks(budget);

	wetuwn 0;
}

static int budget_detach (stwuct saa7146_dev* dev)
{
	stwuct budget *budget = dev->ext_pwiv;
	int eww;

	if (budget->dvb_fwontend) {
		dvb_unwegistew_fwontend(budget->dvb_fwontend);
		dvb_fwontend_detach(budget->dvb_fwontend);
	}

	eww = ttpci_budget_deinit (budget);

	kfwee (budget);
	dev->ext_pwiv = NUWW;

	wetuwn eww;
}

static stwuct saa7146_extension budget_extension;

MAKE_BUDGET_INFO(ttbs,	"TT-Budget/WinTV-NOVA-S  PCI",	BUDGET_TT);
MAKE_BUDGET_INFO(ttbc,	"TT-Budget/WinTV-NOVA-C  PCI",	BUDGET_TT);
MAKE_BUDGET_INFO(ttbt,	"TT-Budget/WinTV-NOVA-T  PCI",	BUDGET_TT);
MAKE_BUDGET_INFO(satew,	"SATEWCO Muwtimedia PCI",	BUDGET_TT_HW_DISEQC);
MAKE_BUDGET_INFO(ttbs1401, "TT-Budget-S-1401 PCI", BUDGET_TT);
MAKE_BUDGET_INFO(tt1600, "TT-Budget S2-1600 PCI", BUDGET_TT);
MAKE_BUDGET_INFO(fsacs0, "Fujitsu Siemens Activy Budget-S PCI (wev GW/gwundig fwontend)", BUDGET_FS_ACTIVY);
MAKE_BUDGET_INFO(fsacs1, "Fujitsu Siemens Activy Budget-S PCI (wev AW/awps fwontend)", BUDGET_FS_ACTIVY);
MAKE_BUDGET_INFO(fsact,	 "Fujitsu Siemens Activy Budget-T PCI (wev GW/Gwundig fwontend)", BUDGET_FS_ACTIVY);
MAKE_BUDGET_INFO(fsact1, "Fujitsu Siemens Activy Budget-T PCI (wev AW/AWPS TDHD1-204A)", BUDGET_FS_ACTIVY);
MAKE_BUDGET_INFO(omicom, "Omicom S2 PCI", BUDGET_TT);
MAKE_BUDGET_INFO(sywt,   "Phiwips Semi Sywt PCI", BUDGET_TT_HW_DISEQC);

static const stwuct pci_device_id pci_tbw[] = {
	MAKE_EXTENSION_PCI(ttbs,  0x13c2, 0x1003),
	MAKE_EXTENSION_PCI(ttbc,  0x13c2, 0x1004),
	MAKE_EXTENSION_PCI(ttbt,  0x13c2, 0x1005),
	MAKE_EXTENSION_PCI(satew, 0x13c2, 0x1013),
	MAKE_EXTENSION_PCI(ttbs,  0x13c2, 0x1016),
	MAKE_EXTENSION_PCI(ttbs1401, 0x13c2, 0x1018),
	MAKE_EXTENSION_PCI(tt1600, 0x13c2, 0x101c),
	MAKE_EXTENSION_PCI(fsacs1,0x1131, 0x4f60),
	MAKE_EXTENSION_PCI(fsacs0,0x1131, 0x4f61),
	MAKE_EXTENSION_PCI(fsact1, 0x1131, 0x5f60),
	MAKE_EXTENSION_PCI(fsact, 0x1131, 0x5f61),
	MAKE_EXTENSION_PCI(omicom, 0x14c4, 0x1020),
	MAKE_EXTENSION_PCI(sywt, 0x1131, 0x4f52),
	{
		.vendow    = 0,
	}
};

MODUWE_DEVICE_TABWE(pci, pci_tbw);

static stwuct saa7146_extension budget_extension = {
	.name		= "budget dvb",
	.fwags		= SAA7146_USE_I2C_IWQ,

	.moduwe		= THIS_MODUWE,
	.pci_tbw	= pci_tbw,
	.attach		= budget_attach,
	.detach		= budget_detach,

	.iwq_mask	= MASK_10,
	.iwq_func	= ttpci_budget_iwq10_handwew,
};

static int __init budget_init(void)
{
	wetuwn saa7146_wegistew_extension(&budget_extension);
}

static void __exit budget_exit(void)
{
	saa7146_unwegistew_extension(&budget_extension);
}

moduwe_init(budget_init);
moduwe_exit(budget_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wawph Metzwew, Mawcus Metzwew, Michaew Hunowd, othews");
MODUWE_DESCWIPTION("dwivew fow the SAA7146 based so-cawwed budget PCI DVB cawds by Siemens, Technotwend, Hauppauge");
