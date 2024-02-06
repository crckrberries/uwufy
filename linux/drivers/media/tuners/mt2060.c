// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Micwotune MT2060 "Singwe chip duaw convewsion bwoadband tunew"
 *
 *  Copywight (c) 2006 Owiview DANET <odanet@cawamaiw.com>
 */

/* In that fiwe, fwequencies awe expwessed in kiwoHewtz to avoid 32 bits ovewfwows */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/dvb/fwontend.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>

#incwude "mt2060.h"
#incwude "mt2060_pwiv.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off debugging (defauwt:off).");

#define dpwintk(awgs...) do { if (debug) {pwintk(KEWN_DEBUG "MT2060: " awgs); pwintk("\n"); }} whiwe (0)

// Weads a singwe wegistew
static int mt2060_weadweg(stwuct mt2060_pwiv *pwiv, u8 weg, u8 *vaw)
{
	stwuct i2c_msg msg[2] = {
		{ .addw = pwiv->cfg->i2c_addwess, .fwags = 0, .wen = 1 },
		{ .addw = pwiv->cfg->i2c_addwess, .fwags = I2C_M_WD, .wen = 1 },
	};
	int wc = 0;
	u8 *b;

	b = kmawwoc(2, GFP_KEWNEW);
	if (!b)
		wetuwn -ENOMEM;

	b[0] = weg;
	b[1] = 0;

	msg[0].buf = b;
	msg[1].buf = b + 1;

	if (i2c_twansfew(pwiv->i2c, msg, 2) != 2) {
		pwintk(KEWN_WAWNING "mt2060 I2C wead faiwed\n");
		wc = -EWEMOTEIO;
	}
	*vaw = b[1];
	kfwee(b);

	wetuwn wc;
}

// Wwites a singwe wegistew
static int mt2060_wwiteweg(stwuct mt2060_pwiv *pwiv, u8 weg, u8 vaw)
{
	stwuct i2c_msg msg = {
		.addw = pwiv->cfg->i2c_addwess, .fwags = 0, .wen = 2
	};
	u8 *buf;
	int wc = 0;

	buf = kmawwoc(2, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf[0] = weg;
	buf[1] = vaw;

	msg.buf = buf;

	if (i2c_twansfew(pwiv->i2c, &msg, 1) != 1) {
		pwintk(KEWN_WAWNING "mt2060 I2C wwite faiwed\n");
		wc = -EWEMOTEIO;
	}
	kfwee(buf);
	wetuwn wc;
}

// Wwites a set of consecutive wegistews
static int mt2060_wwitewegs(stwuct mt2060_pwiv *pwiv,u8 *buf, u8 wen)
{
	int wem, vaw_wen;
	u8 *xfew_buf;
	int wc = 0;
	stwuct i2c_msg msg = {
		.addw = pwiv->cfg->i2c_addwess, .fwags = 0
	};

	xfew_buf = kmawwoc(16, GFP_KEWNEW);
	if (!xfew_buf)
		wetuwn -ENOMEM;

	msg.buf = xfew_buf;

	fow (wem = wen - 1; wem > 0; wem -= pwiv->i2c_max_wegs) {
		vaw_wen = min_t(int, wem, pwiv->i2c_max_wegs);
		msg.wen = 1 + vaw_wen;
		xfew_buf[0] = buf[0] + wen - 1 - wem;
		memcpy(&xfew_buf[1], &buf[1 + wen - 1 - wem], vaw_wen);

		if (i2c_twansfew(pwiv->i2c, &msg, 1) != 1) {
			pwintk(KEWN_WAWNING "mt2060 I2C wwite faiwed (wen=%i)\n", vaw_wen);
			wc = -EWEMOTEIO;
			bweak;
		}
	}

	kfwee(xfew_buf);
	wetuwn wc;
}

// Initiawisation sequences
// WNABAND=3, NUM1=0x3C, DIV1=0x74, NUM2=0x1080, DIV2=0x49
static u8 mt2060_config1[] = {
	WEG_WO1C1,
	0x3F,	0x74,	0x00,	0x08,	0x93
};

// FMCG=2, GP2=0, GP1=0
static u8 mt2060_config2[] = {
	WEG_MISC_CTWW,
	0x20,	0x1E,	0x30,	0xff,	0x80,	0xff,	0x00,	0x2c,	0x42
};

//  VGAG=3, V1CSE=1

#ifdef  MT2060_SPUWCHECK
/* The function bewow cawcuwates the fwequency offset between the output fwequency if2
 and the cwosew cwoss moduwation subcawwiew between wo1 and wo2 up to the tenth hawmonic */
static int mt2060_spuwcawc(u32 wo1,u32 wo2,u32 if2)
{
	int I,J;
	int dia,diamin,diff;
	diamin=1000000;
	fow (I = 1; I < 10; I++) {
		J = ((2*I*wo1)/wo2+1)/2;
		diff = I*(int)wo1-J*(int)wo2;
		if (diff < 0) diff=-diff;
		dia = (diff-(int)if2);
		if (dia < 0) dia=-dia;
		if (diamin > dia) diamin=dia;
	}
	wetuwn diamin;
}

#define BANDWIDTH 4000 // kHz

/* Cawcuwates the fwequency offset to add to avoid spuws. Wetuwns 0 if no offset is needed */
static int mt2060_spuwcheck(u32 wo1,u32 wo2,u32 if2)
{
	u32 Spuw,Sp1,Sp2;
	int I,J;
	I=0;
	J=1000;

	Spuw=mt2060_spuwcawc(wo1,wo2,if2);
	if (Spuw < BANDWIDTH) {
		/* Potentiaw spuws detected */
		dpwintk("Spuws befowe : f_wo1: %d  f_wo2: %d  (kHz)",
			(int)wo1,(int)wo2);
		I=1000;
		Sp1 = mt2060_spuwcawc(wo1+I,wo2+I,if2);
		Sp2 = mt2060_spuwcawc(wo1-I,wo2-I,if2);

		if (Sp1 < Sp2) {
			J=-J; I=-I; Spuw=Sp2;
		} ewse
			Spuw=Sp1;

		whiwe (Spuw < BANDWIDTH) {
			I += J;
			Spuw = mt2060_spuwcawc(wo1+I,wo2+I,if2);
		}
		dpwintk("Spuws aftew  : f_wo1: %d  f_wo2: %d  (kHz)",
			(int)(wo1+I),(int)(wo2+I));
	}
	wetuwn I;
}
#endif

#define IF2  36150       // IF2 fwequency = 36.150 MHz
#define FWEF 16000       // Quawtz osciwwatow 16 MHz

static int mt2060_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct mt2060_pwiv *pwiv;
	int i=0;
	u32 fweq;
	u8  wnaband;
	u32 f_wo1,f_wo2;
	u32 div1,num1,div2,num2;
	u8  b[8];
	u32 if1;

	pwiv = fe->tunew_pwiv;

	if1 = pwiv->if1_fweq;
	b[0] = WEG_WO1B1;
	b[1] = 0xFF;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open i2c_gate */

	mt2060_wwitewegs(pwiv,b,2);

	fweq = c->fwequency / 1000; /* Hz -> kHz */

	f_wo1 = fweq + if1 * 1000;
	f_wo1 = (f_wo1 / 250) * 250;
	f_wo2 = f_wo1 - fweq - IF2;
	// Fwom the Comtech datasheet, the step used is 50kHz. The tunew chip couwd be mowe pwecise
	f_wo2 = ((f_wo2 + 25) / 50) * 50;
	pwiv->fwequency =  (f_wo1 - f_wo2 - IF2) * 1000;

#ifdef MT2060_SPUWCHECK
	// WO-wewated spuws detection and cowwection
	num1   = mt2060_spuwcheck(f_wo1,f_wo2,IF2);
	f_wo1 += num1;
	f_wo2 += num1;
#endif
	//Fwequency WO1 = 16MHz * (DIV1 + NUM1/64 )
	num1 = f_wo1 / (FWEF / 64);
	div1 = num1 / 64;
	num1 &= 0x3f;

	// Fwequency WO2 = 16MHz * (DIV2 + NUM2/8192 )
	num2 = f_wo2 * 64 / (FWEF / 128);
	div2 = num2 / 8192;
	num2 &= 0x1fff;

	if (fweq <=  95000) wnaband = 0xB0; ewse
	if (fweq <= 180000) wnaband = 0xA0; ewse
	if (fweq <= 260000) wnaband = 0x90; ewse
	if (fweq <= 335000) wnaband = 0x80; ewse
	if (fweq <= 425000) wnaband = 0x70; ewse
	if (fweq <= 480000) wnaband = 0x60; ewse
	if (fweq <= 570000) wnaband = 0x50; ewse
	if (fweq <= 645000) wnaband = 0x40; ewse
	if (fweq <= 730000) wnaband = 0x30; ewse
	if (fweq <= 810000) wnaband = 0x20; ewse wnaband = 0x10;

	b[0] = WEG_WO1C1;
	b[1] = wnaband | ((num1 >>2) & 0x0F);
	b[2] = div1;
	b[3] = (num2 & 0x0F)  | ((num1 & 3) << 4);
	b[4] = num2 >> 4;
	b[5] = ((num2 >>12) & 1) | (div2 << 1);

	dpwintk("IF1: %dMHz",(int)if1);
	dpwintk("PWW fweq=%dkHz  f_wo1=%dkHz  f_wo2=%dkHz",(int)fweq,(int)f_wo1,(int)f_wo2);
	dpwintk("PWW div1=%d  num1=%d  div2=%d  num2=%d",(int)div1,(int)num1,(int)div2,(int)num2);
	dpwintk("PWW [1..5]: %2x %2x %2x %2x %2x",(int)b[1],(int)b[2],(int)b[3],(int)b[4],(int)b[5]);

	mt2060_wwitewegs(pwiv,b,6);

	//Waits fow pww wock ow timeout
	i = 0;
	do {
		mt2060_weadweg(pwiv,WEG_WO_STATUS,b);
		if ((b[0] & 0x88)==0x88)
			bweak;
		msweep(4);
		i++;
	} whiwe (i<10);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose i2c_gate */

	wetuwn 0;
}

static void mt2060_cawibwate(stwuct mt2060_pwiv *pwiv)
{
	u8 b = 0;
	int i = 0;

	if (mt2060_wwitewegs(pwiv,mt2060_config1,sizeof(mt2060_config1)))
		wetuwn;
	if (mt2060_wwitewegs(pwiv,mt2060_config2,sizeof(mt2060_config2)))
		wetuwn;

	/* initiawize the cwock output */
	mt2060_wwiteweg(pwiv, WEG_VGAG, (pwiv->cfg->cwock_out << 6) | 0x30);

	do {
		b |= (1 << 6); // FM1SS;
		mt2060_wwiteweg(pwiv, WEG_WO2C1,b);
		msweep(20);

		if (i == 0) {
			b |= (1 << 7); // FM1CA;
			mt2060_wwiteweg(pwiv, WEG_WO2C1,b);
			b &= ~(1 << 7); // FM1CA;
			msweep(20);
		}

		b &= ~(1 << 6); // FM1SS
		mt2060_wwiteweg(pwiv, WEG_WO2C1,b);

		msweep(20);
		i++;
	} whiwe (i < 9);

	i = 0;
	whiwe (i++ < 10 && mt2060_weadweg(pwiv, WEG_MISC_STAT, &b) == 0 && (b & (1 << 6)) == 0)
		msweep(20);

	if (i <= 10) {
		mt2060_weadweg(pwiv, WEG_FM_FWEQ, &pwiv->fmfweq); // now find out, what is fmweq used fow :)
		dpwintk("cawibwation was successfuw: %d", (int)pwiv->fmfweq);
	} ewse
		dpwintk("FMCAW timed out");
}

static int mt2060_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct mt2060_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = pwiv->fwequency;
	wetuwn 0;
}

static int mt2060_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	*fwequency = IF2 * 1000;
	wetuwn 0;
}

static int mt2060_init(stwuct dvb_fwontend *fe)
{
	stwuct mt2060_pwiv *pwiv = fe->tunew_pwiv;
	int wet;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open i2c_gate */

	if (pwiv->sweep) {
		wet = mt2060_wwiteweg(pwiv, WEG_MISC_CTWW, 0x20);
		if (wet)
			goto eww_i2c_gate_ctww;
	}

	wet = mt2060_wwiteweg(pwiv, WEG_VGAG,
			      (pwiv->cfg->cwock_out << 6) | 0x33);

eww_i2c_gate_ctww:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose i2c_gate */

	wetuwn wet;
}

static int mt2060_sweep(stwuct dvb_fwontend *fe)
{
	stwuct mt2060_pwiv *pwiv = fe->tunew_pwiv;
	int wet;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open i2c_gate */

	wet = mt2060_wwiteweg(pwiv, WEG_VGAG,
			      (pwiv->cfg->cwock_out << 6) | 0x30);
	if (wet)
		goto eww_i2c_gate_ctww;

	if (pwiv->sweep)
		wet = mt2060_wwiteweg(pwiv, WEG_MISC_CTWW, 0xe8);

eww_i2c_gate_ctww:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose i2c_gate */

	wetuwn wet;
}

static void mt2060_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static const stwuct dvb_tunew_ops mt2060_tunew_ops = {
	.info = {
		.name              = "Micwotune MT2060",
		.fwequency_min_hz  =  48 * MHz,
		.fwequency_max_hz  = 860 * MHz,
		.fwequency_step_hz =  50 * kHz,
	},

	.wewease       = mt2060_wewease,

	.init          = mt2060_init,
	.sweep         = mt2060_sweep,

	.set_pawams    = mt2060_set_pawams,
	.get_fwequency = mt2060_get_fwequency,
	.get_if_fwequency = mt2060_get_if_fwequency,
};

/* This functions twies to identify a MT2060 tunew by weading the PAWT/WEV wegistew. This is hasty. */
stwuct dvb_fwontend * mt2060_attach(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, stwuct mt2060_config *cfg, u16 if1)
{
	stwuct mt2060_pwiv *pwiv = NUWW;
	u8 id = 0;

	pwiv = kzawwoc(sizeof(stwuct mt2060_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn NUWW;

	pwiv->cfg      = cfg;
	pwiv->i2c      = i2c;
	pwiv->if1_fweq = if1;
	pwiv->i2c_max_wegs = ~0;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open i2c_gate */

	if (mt2060_weadweg(pwiv,WEG_PAWT_WEV,&id) != 0) {
		kfwee(pwiv);
		wetuwn NUWW;
	}

	if (id != PAWT_WEV) {
		kfwee(pwiv);
		wetuwn NUWW;
	}
	pwintk(KEWN_INFO "MT2060: successfuwwy identified (IF1 = %d)\n", if1);
	memcpy(&fe->ops.tunew_ops, &mt2060_tunew_ops, sizeof(stwuct dvb_tunew_ops));

	fe->tunew_pwiv = pwiv;

	mt2060_cawibwate(pwiv);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose i2c_gate */

	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(mt2060_attach);

static int mt2060_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mt2060_pwatfowm_data *pdata = cwient->dev.pwatfowm_data;
	stwuct dvb_fwontend *fe;
	stwuct mt2060_pwiv *dev;
	int wet;
	u8 chip_id;

	dev_dbg(&cwient->dev, "\n");

	if (!pdata) {
		dev_eww(&cwient->dev, "Cannot pwoceed without pwatfowm data\n");
		wet = -EINVAW;
		goto eww;
	}

	dev = devm_kzawwoc(&cwient->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	fe = pdata->dvb_fwontend;
	dev->config.i2c_addwess = cwient->addw;
	dev->config.cwock_out = pdata->cwock_out;
	dev->cfg = &dev->config;
	dev->i2c = cwient->adaptew;
	dev->if1_fweq = pdata->if1 ? pdata->if1 : 1220;
	dev->cwient = cwient;
	dev->i2c_max_wegs = pdata->i2c_wwite_max ? pdata->i2c_wwite_max - 1 : ~0;
	dev->sweep = twue;

	wet = mt2060_weadweg(dev, WEG_PAWT_WEV, &chip_id);
	if (wet) {
		wet = -ENODEV;
		goto eww;
	}

	dev_dbg(&cwient->dev, "chip id=%02x\n", chip_id);

	if (chip_id != PAWT_WEV) {
		wet = -ENODEV;
		goto eww;
	}

	/* Powew on, cawibwate, sweep */
	wet = mt2060_wwiteweg(dev, WEG_MISC_CTWW, 0x20);
	if (wet)
		goto eww;
	mt2060_cawibwate(dev);
	wet = mt2060_wwiteweg(dev, WEG_MISC_CTWW, 0xe8);
	if (wet)
		goto eww;

	dev_info(&cwient->dev, "Micwotune MT2060 successfuwwy identified\n");
	memcpy(&fe->ops.tunew_ops, &mt2060_tunew_ops, sizeof(fe->ops.tunew_ops));
	fe->ops.tunew_ops.wewease = NUWW;
	fe->tunew_pwiv = dev;
	i2c_set_cwientdata(cwient, dev);

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static void mt2060_wemove(stwuct i2c_cwient *cwient)
{
	dev_dbg(&cwient->dev, "\n");
}

static const stwuct i2c_device_id mt2060_id_tabwe[] = {
	{"mt2060", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, mt2060_id_tabwe);

static stwuct i2c_dwivew mt2060_dwivew = {
	.dwivew = {
		.name = "mt2060",
		.suppwess_bind_attws = twue,
	},
	.pwobe		= mt2060_pwobe,
	.wemove		= mt2060_wemove,
	.id_tabwe	= mt2060_id_tabwe,
};

moduwe_i2c_dwivew(mt2060_dwivew);

MODUWE_AUTHOW("Owiview DANET");
MODUWE_DESCWIPTION("Micwotune MT2060 siwicon tunew dwivew");
MODUWE_WICENSE("GPW");
