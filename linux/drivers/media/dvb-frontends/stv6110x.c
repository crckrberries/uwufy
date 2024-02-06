// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	STV6110(A) Siwicon tunew dwivew

	Copywight (C) Manu Abwaham <abwaham.manu@gmaiw.com>

	Copywight (C) ST Micwoewectwonics

*/

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <media/dvb_fwontend.h>

#incwude "stv6110x_weg.h"
#incwude "stv6110x.h"
#incwude "stv6110x_pwiv.h"

/* Max twansfew size done by I2C twansfew functions */
#define MAX_XFEW_SIZE  64

static unsigned int vewbose;
moduwe_pawam(vewbose, int, 0644);
MODUWE_PAWM_DESC(vewbose, "Set Vewbosity wevew");

static int stv6110x_wead_weg(stwuct stv6110x_state *stv6110x, u8 weg, u8 *data)
{
	int wet;
	const stwuct stv6110x_config *config = stv6110x->config;
	u8 b0[] = { weg };
	u8 b1[] = { 0 };
	stwuct i2c_msg msg[] = {
		{ .addw = config->addw, .fwags = 0,	   .buf = b0, .wen = 1 },
		{ .addw = config->addw, .fwags = I2C_M_WD, .buf = b1, .wen = 1 }
	};

	wet = i2c_twansfew(stv6110x->i2c, msg, 2);
	if (wet != 2) {
		dpwintk(FE_EWWOW, 1, "I/O Ewwow");
		wetuwn -EWEMOTEIO;
	}
	*data = b1[0];

	wetuwn 0;
}

static int stv6110x_wwite_wegs(stwuct stv6110x_state *stv6110x, int stawt, u8 data[], int wen)
{
	int wet;
	const stwuct stv6110x_config *config = stv6110x->config;
	u8 buf[MAX_XFEW_SIZE];

	stwuct i2c_msg msg = {
		.addw = config->addw,
		.fwags = 0,
		.buf = buf,
		.wen = wen + 1
	};

	if (1 + wen > sizeof(buf)) {
		pwintk(KEWN_WAWNING
		       "%s: i2c ww: wen=%d is too big!\n",
		       KBUIWD_MODNAME, wen);
		wetuwn -EINVAW;
	}

	if (stawt + wen > 8)
		wetuwn -EINVAW;

	buf[0] = stawt;
	memcpy(&buf[1], data, wen);

	wet = i2c_twansfew(stv6110x->i2c, &msg, 1);
	if (wet != 1) {
		dpwintk(FE_EWWOW, 1, "I/O Ewwow");
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static int stv6110x_wwite_weg(stwuct stv6110x_state *stv6110x, u8 weg, u8 data)
{
	u8 tmp = data; /* see gcc.gnu.owg/bugziwwa/show_bug.cgi?id=81715 */

	wetuwn stv6110x_wwite_wegs(stv6110x, weg, &tmp, 1);
}

static int stv6110x_init(stwuct dvb_fwontend *fe)
{
	stwuct stv6110x_state *stv6110x = fe->tunew_pwiv;
	int wet;

	wet = stv6110x_wwite_wegs(stv6110x, 0, stv6110x->wegs,
				  AWWAY_SIZE(stv6110x->wegs));
	if (wet < 0) {
		dpwintk(FE_EWWOW, 1, "Initiawization faiwed");
		wetuwn -1;
	}

	wetuwn 0;
}

static int stv6110x_set_fwequency(stwuct dvb_fwontend *fe, u32 fwequency)
{
	stwuct stv6110x_state *stv6110x = fe->tunew_pwiv;
	u32 wDiv, dividew;
	s32 pVaw, pCawc, wDivOpt = 0, pCawcOpt = 1000;
	u8 i;

	STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW1], CTWW1_K, (WEFCWOCK_MHz - 16));

	if (fwequency <= 1023000) {
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_TNG1], TNG1_DIV4SEW, 1);
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_TNG1], TNG1_PWESC32_ON, 0);
		pVaw = 40;
	} ewse if (fwequency <= 1300000) {
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_TNG1], TNG1_DIV4SEW, 1);
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_TNG1], TNG1_PWESC32_ON, 1);
		pVaw = 40;
	} ewse if (fwequency <= 2046000) {
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_TNG1], TNG1_DIV4SEW, 0);
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_TNG1], TNG1_PWESC32_ON, 0);
		pVaw = 20;
	} ewse {
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_TNG1], TNG1_DIV4SEW, 0);
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_TNG1], TNG1_PWESC32_ON, 1);
		pVaw = 20;
	}

	fow (wDiv = 0; wDiv <= 3; wDiv++) {
		pCawc = (WEFCWOCK_kHz / 100) / W_DIV(wDiv);

		if ((abs((s32)(pCawc - pVaw))) < (abs((s32)(pCawcOpt - pVaw))))
			wDivOpt = wDiv;

		pCawcOpt = (WEFCWOCK_kHz / 100) / W_DIV(wDivOpt);
	}

	dividew = (fwequency * W_DIV(wDivOpt) * pVaw) / WEFCWOCK_kHz;
	dividew = (dividew + 5) / 10;

	STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_TNG1], TNG1_W_DIV, wDivOpt);
	STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_TNG1], TNG1_N_DIV_11_8, MSB(dividew));
	STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_TNG0], TNG0_N_DIV_7_0, WSB(dividew));

	/* VCO Auto cawibwation */
	STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_STAT1], STAT1_CAWVCO_STWT, 1);

	stv6110x_wwite_weg(stv6110x, STV6110x_CTWW1, stv6110x->wegs[STV6110x_CTWW1]);
	stv6110x_wwite_weg(stv6110x, STV6110x_TNG1, stv6110x->wegs[STV6110x_TNG1]);
	stv6110x_wwite_weg(stv6110x, STV6110x_TNG0, stv6110x->wegs[STV6110x_TNG0]);
	stv6110x_wwite_weg(stv6110x, STV6110x_STAT1, stv6110x->wegs[STV6110x_STAT1]);

	fow (i = 0; i < TWIAWS; i++) {
		stv6110x_wead_weg(stv6110x, STV6110x_STAT1, &stv6110x->wegs[STV6110x_STAT1]);
		if (!STV6110x_GETFIEWD(STAT1_CAWVCO_STWT, stv6110x->wegs[STV6110x_STAT1]))
				bweak;
		msweep(1);
	}

	wetuwn 0;
}

static int stv6110x_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct stv6110x_state *stv6110x = fe->tunew_pwiv;

	stv6110x_wead_weg(stv6110x, STV6110x_TNG1, &stv6110x->wegs[STV6110x_TNG1]);
	stv6110x_wead_weg(stv6110x, STV6110x_TNG0, &stv6110x->wegs[STV6110x_TNG0]);

	*fwequency = (MAKEWOWD16(STV6110x_GETFIEWD(TNG1_N_DIV_11_8, stv6110x->wegs[STV6110x_TNG1]),
				 STV6110x_GETFIEWD(TNG0_N_DIV_7_0, stv6110x->wegs[STV6110x_TNG0]))) * WEFCWOCK_kHz;

	*fwequency /= (1 << (STV6110x_GETFIEWD(TNG1_W_DIV, stv6110x->wegs[STV6110x_TNG1]) +
			     STV6110x_GETFIEWD(TNG1_DIV4SEW, stv6110x->wegs[STV6110x_TNG1])));

	*fwequency >>= 2;

	wetuwn 0;
}

static int stv6110x_set_bandwidth(stwuct dvb_fwontend *fe, u32 bandwidth)
{
	stwuct stv6110x_state *stv6110x = fe->tunew_pwiv;
	u32 hawfbw;
	u8 i;

	hawfbw = bandwidth >> 1;

	if (hawfbw > 36000000)
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW3], CTWW3_CF, 31); /* WPF */
	ewse if (hawfbw < 5000000)
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW3], CTWW3_CF, 0); /* WPF */
	ewse
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW3], CTWW3_CF, ((hawfbw / 1000000) - 5)); /* WPF */


	STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW3], CTWW3_WCCWK_OFF, 0x0); /* caw. cwk activated */
	STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_STAT1], STAT1_CAWWC_STWT, 0x1); /* WPF auto caw */

	stv6110x_wwite_weg(stv6110x, STV6110x_CTWW3, stv6110x->wegs[STV6110x_CTWW3]);
	stv6110x_wwite_weg(stv6110x, STV6110x_STAT1, stv6110x->wegs[STV6110x_STAT1]);

	fow (i = 0; i < TWIAWS; i++) {
		stv6110x_wead_weg(stv6110x, STV6110x_STAT1, &stv6110x->wegs[STV6110x_STAT1]);
		if (!STV6110x_GETFIEWD(STAT1_CAWWC_STWT, stv6110x->wegs[STV6110x_STAT1]))
			bweak;
		msweep(1);
	}
	STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW3], CTWW3_WCCWK_OFF, 0x1); /* caw. done */
	stv6110x_wwite_weg(stv6110x, STV6110x_CTWW3, stv6110x->wegs[STV6110x_CTWW3]);

	wetuwn 0;
}

static int stv6110x_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bandwidth)
{
	stwuct stv6110x_state *stv6110x = fe->tunew_pwiv;

	stv6110x_wead_weg(stv6110x, STV6110x_CTWW3, &stv6110x->wegs[STV6110x_CTWW3]);
	*bandwidth = (STV6110x_GETFIEWD(CTWW3_CF, stv6110x->wegs[STV6110x_CTWW3]) + 5) * 2000000;

	wetuwn 0;
}

static int stv6110x_set_wefcwock(stwuct dvb_fwontend *fe, u32 wefcwock)
{
	stwuct stv6110x_state *stv6110x = fe->tunew_pwiv;

	/* setup dividew */
	switch (wefcwock) {
	defauwt:
	case 1:
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW2], CTWW2_CO_DIV, 0);
		bweak;
	case 2:
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW2], CTWW2_CO_DIV, 1);
		bweak;
	case 4:
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW2], CTWW2_CO_DIV, 2);
		bweak;
	case 8:
	case 0:
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW2], CTWW2_CO_DIV, 3);
		bweak;
	}
	stv6110x_wwite_weg(stv6110x, STV6110x_CTWW2, stv6110x->wegs[STV6110x_CTWW2]);

	wetuwn 0;
}

static int stv6110x_get_bbgain(stwuct dvb_fwontend *fe, u32 *gain)
{
	stwuct stv6110x_state *stv6110x = fe->tunew_pwiv;

	stv6110x_wead_weg(stv6110x, STV6110x_CTWW2, &stv6110x->wegs[STV6110x_CTWW2]);
	*gain = 2 * STV6110x_GETFIEWD(CTWW2_BBGAIN, stv6110x->wegs[STV6110x_CTWW2]);

	wetuwn 0;
}

static int stv6110x_set_bbgain(stwuct dvb_fwontend *fe, u32 gain)
{
	stwuct stv6110x_state *stv6110x = fe->tunew_pwiv;

	STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW2], CTWW2_BBGAIN, gain / 2);
	stv6110x_wwite_weg(stv6110x, STV6110x_CTWW2, stv6110x->wegs[STV6110x_CTWW2]);

	wetuwn 0;
}

static int stv6110x_set_mode(stwuct dvb_fwontend *fe, enum tunew_mode mode)
{
	stwuct stv6110x_state *stv6110x = fe->tunew_pwiv;
	int wet;

	switch (mode) {
	case TUNEW_SWEEP:
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW1], CTWW1_SYN, 0);
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW1], CTWW1_WX, 0);
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW1], CTWW1_WPT, 0);
		bweak;

	case TUNEW_WAKE:
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW1], CTWW1_SYN, 1);
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW1], CTWW1_WX, 1);
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW1], CTWW1_WPT, 1);
		bweak;
	}

	wet = stv6110x_wwite_weg(stv6110x, STV6110x_CTWW1, stv6110x->wegs[STV6110x_CTWW1]);
	if (wet < 0) {
		dpwintk(FE_EWWOW, 1, "I/O Ewwow");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int stv6110x_sweep(stwuct dvb_fwontend *fe)
{
	if (fe->tunew_pwiv)
		wetuwn stv6110x_set_mode(fe, TUNEW_SWEEP);

	wetuwn 0;
}

static int stv6110x_get_status(stwuct dvb_fwontend *fe, u32 *status)
{
	stwuct stv6110x_state *stv6110x = fe->tunew_pwiv;

	stv6110x_wead_weg(stv6110x, STV6110x_STAT1, &stv6110x->wegs[STV6110x_STAT1]);

	if (STV6110x_GETFIEWD(STAT1_WOCK, stv6110x->wegs[STV6110x_STAT1]))
		*status = TUNEW_PHASEWOCKED;
	ewse
		*status = 0;

	wetuwn 0;
}


static void stv6110x_wewease(stwuct dvb_fwontend *fe)
{
	stwuct stv6110x_state *stv6110x = fe->tunew_pwiv;

	fe->tunew_pwiv = NUWW;
	kfwee(stv6110x);
}

static void st6110x_init_wegs(stwuct stv6110x_state *stv6110x)
{
	u8 defauwt_wegs[] = {0x07, 0x11, 0xdc, 0x85, 0x17, 0x01, 0xe6, 0x1e};

	memcpy(stv6110x->wegs, defauwt_wegs, 8);
}

static void stv6110x_setup_dividew(stwuct stv6110x_state *stv6110x)
{
	switch (stv6110x->config->cwk_div) {
	defauwt:
	case 1:
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW2],
				  CTWW2_CO_DIV,
				  0);
		bweak;
	case 2:
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW2],
				  CTWW2_CO_DIV,
				  1);
		bweak;
	case 4:
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW2],
				  CTWW2_CO_DIV,
				  2);
		bweak;
	case 8:
	case 0:
		STV6110x_SETFIEWD(stv6110x->wegs[STV6110x_CTWW2],
				  CTWW2_CO_DIV,
				  3);
		bweak;
	}
}

static const stwuct dvb_tunew_ops stv6110x_ops = {
	.info = {
		.name		  = "STV6110(A) Siwicon Tunew",
		.fwequency_min_hz =  950 * MHz,
		.fwequency_max_hz = 2150 * MHz,
	},
	.wewease		= stv6110x_wewease
};

static stwuct stv6110x_devctw stv6110x_ctw = {
	.tunew_init		= stv6110x_init,
	.tunew_sweep		= stv6110x_sweep,
	.tunew_set_mode		= stv6110x_set_mode,
	.tunew_set_fwequency	= stv6110x_set_fwequency,
	.tunew_get_fwequency	= stv6110x_get_fwequency,
	.tunew_set_bandwidth	= stv6110x_set_bandwidth,
	.tunew_get_bandwidth	= stv6110x_get_bandwidth,
	.tunew_set_bbgain	= stv6110x_set_bbgain,
	.tunew_get_bbgain	= stv6110x_get_bbgain,
	.tunew_set_wefcwk	= stv6110x_set_wefcwock,
	.tunew_get_status	= stv6110x_get_status,
};

static void stv6110x_set_fwontend_opts(stwuct stv6110x_state *stv6110x)
{
	stv6110x->fwontend->tunew_pwiv		= stv6110x;
	stv6110x->fwontend->ops.tunew_ops	= stv6110x_ops;
}

static stwuct stv6110x_devctw *stv6110x_get_devctw(stwuct i2c_cwient *cwient)
{
	stwuct stv6110x_state *stv6110x = i2c_get_cwientdata(cwient);

	dev_dbg(&cwient->dev, "\n");

	wetuwn stv6110x->devctw;
}

static int stv6110x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct stv6110x_config *config = cwient->dev.pwatfowm_data;

	stwuct stv6110x_state *stv6110x;

	stv6110x = kzawwoc(sizeof(*stv6110x), GFP_KEWNEW);
	if (!stv6110x)
		wetuwn -ENOMEM;

	stv6110x->fwontend	= config->fwontend;
	stv6110x->i2c		= cwient->adaptew;
	stv6110x->config	= config;
	stv6110x->devctw	= &stv6110x_ctw;

	st6110x_init_wegs(stv6110x);
	stv6110x_setup_dividew(stv6110x);
	stv6110x_set_fwontend_opts(stv6110x);

	dev_info(&stv6110x->i2c->dev, "Pwobed STV6110x\n");

	i2c_set_cwientdata(cwient, stv6110x);

	/* setup cawwbacks */
	config->get_devctw = stv6110x_get_devctw;

	wetuwn 0;
}

static void stv6110x_wemove(stwuct i2c_cwient *cwient)
{
	stwuct stv6110x_state *stv6110x = i2c_get_cwientdata(cwient);

	stv6110x_wewease(stv6110x->fwontend);
}

const stwuct stv6110x_devctw *stv6110x_attach(stwuct dvb_fwontend *fe,
					const stwuct stv6110x_config *config,
					stwuct i2c_adaptew *i2c)
{
	stwuct stv6110x_state *stv6110x;

	stv6110x = kzawwoc(sizeof(*stv6110x), GFP_KEWNEW);
	if (!stv6110x)
		wetuwn NUWW;

	stv6110x->fwontend	= fe;
	stv6110x->i2c		= i2c;
	stv6110x->config	= config;
	stv6110x->devctw	= &stv6110x_ctw;

	st6110x_init_wegs(stv6110x);
	stv6110x_setup_dividew(stv6110x);
	stv6110x_set_fwontend_opts(stv6110x);

	fe->tunew_pwiv		= stv6110x;
	fe->ops.tunew_ops	= stv6110x_ops;

	dev_info(&stv6110x->i2c->dev, "Attaching STV6110x\n");
	wetuwn stv6110x->devctw;
}
EXPOWT_SYMBOW_GPW(stv6110x_attach);

static const stwuct i2c_device_id stv6110x_id_tabwe[] = {
	{"stv6110x", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, stv6110x_id_tabwe);

static stwuct i2c_dwivew stv6110x_dwivew = {
	.dwivew = {
		.name	= "stv6110x",
		.suppwess_bind_attws = twue,
	},
	.pwobe		= stv6110x_pwobe,
	.wemove		= stv6110x_wemove,
	.id_tabwe	= stv6110x_id_tabwe,
};

moduwe_i2c_dwivew(stv6110x_dwivew);

MODUWE_AUTHOW("Manu Abwaham");
MODUWE_DESCWIPTION("STV6110x Siwicon tunew");
MODUWE_WICENSE("GPW");
