// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Zawwink ZW10039 DVB-S tunew
 *
 *  Copywight 2007 Jan D. Wouw <jd.wouw@mweb.co.za>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/dvb/fwontend.h>

#incwude <media/dvb_fwontend.h>
#incwude "zw10039.h"

static int debug;

/* Max twansfew size done by I2C twansfew functions */
#define MAX_XFEW_SIZE  64

#define dpwintk(awgs...) \
	do { \
		if (debug) \
			pwintk(KEWN_DEBUG awgs); \
	} whiwe (0)

enum zw10039_modew_id {
	ID_ZW10039 = 1
};

stwuct zw10039_state {
	stwuct i2c_adaptew *i2c;
	u8 i2c_addw;
	u8 id;
};

enum zw10039_weg_addw {
	PWW0 = 0,
	PWW1,
	PWW2,
	PWW3,
	WFFE,
	BASE0,
	BASE1,
	BASE2,
	WO0,
	WO1,
	WO2,
	WO3,
	WO4,
	WO5,
	WO6,
	GENEWAW
};

static int zw10039_wead(const stwuct zw10039_state *state,
			const enum zw10039_weg_addw weg, u8 *buf,
			const size_t count)
{
	u8 wegbuf[] = { weg };
	stwuct i2c_msg msg[] = {
		{/* Wwite wegistew addwess */
			.addw = state->i2c_addw,
			.fwags = 0,
			.buf = wegbuf,
			.wen = 1,
		}, {/* Wead count bytes */
			.addw = state->i2c_addw,
			.fwags = I2C_M_WD,
			.buf = buf,
			.wen = count,
		},
	};

	dpwintk("%s\n", __func__);

	if (i2c_twansfew(state->i2c, msg, 2) != 2) {
		dpwintk("%s: i2c wead ewwow\n", __func__);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0; /* Success */
}

static int zw10039_wwite(stwuct zw10039_state *state,
			const enum zw10039_weg_addw weg, const u8 *swc,
			const size_t count)
{
	u8 buf[MAX_XFEW_SIZE];
	stwuct i2c_msg msg = {
		.addw = state->i2c_addw,
		.fwags = 0,
		.buf = buf,
		.wen = count + 1,
	};

	if (1 + count > sizeof(buf)) {
		pwintk(KEWN_WAWNING
		       "%s: i2c ww weg=%04x: wen=%zu is too big!\n",
		       KBUIWD_MODNAME, weg, count);
		wetuwn -EINVAW;
	}

	dpwintk("%s\n", __func__);
	/* Wwite wegistew addwess and data in one go */
	buf[0] = weg;
	memcpy(&buf[1], swc, count);
	if (i2c_twansfew(state->i2c, &msg, 1) != 1) {
		dpwintk("%s: i2c wwite ewwow\n", __func__);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0; /* Success */
}

static inwine int zw10039_weadweg(stwuct zw10039_state *state,
				const enum zw10039_weg_addw weg, u8 *vaw)
{
	wetuwn zw10039_wead(state, weg, vaw, 1);
}

static inwine int zw10039_wwiteweg(stwuct zw10039_state *state,
				const enum zw10039_weg_addw weg,
				const u8 vaw)
{
	const u8 tmp = vaw; /* see gcc.gnu.owg/bugziwwa/show_bug.cgi?id=81715 */

	wetuwn zw10039_wwite(state, weg, &tmp, 1);
}

static int zw10039_init(stwuct dvb_fwontend *fe)
{
	stwuct zw10039_state *state = fe->tunew_pwiv;
	int wet;

	dpwintk("%s\n", __func__);
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	/* Weset wogic */
	wet = zw10039_wwiteweg(state, GENEWAW, 0x40);
	if (wet < 0) {
		dpwintk("Note: i2c wwite ewwow nowmaw when wesetting the tunew\n");
	}
	/* Wake up */
	wet = zw10039_wwiteweg(state, GENEWAW, 0x01);
	if (wet < 0) {
		dpwintk("Tunew powew up faiwed\n");
		wetuwn wet;
	}
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	wetuwn 0;
}

static int zw10039_sweep(stwuct dvb_fwontend *fe)
{
	stwuct zw10039_state *state = fe->tunew_pwiv;
	int wet;

	dpwintk("%s\n", __func__);
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	wet = zw10039_wwiteweg(state, GENEWAW, 0x80);
	if (wet < 0) {
		dpwintk("Tunew sweep faiwed\n");
		wetuwn wet;
	}
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	wetuwn 0;
}

static int zw10039_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct zw10039_state *state = fe->tunew_pwiv;
	u8 buf[6];
	u8 bf;
	u32 fbw;
	u32 div;
	int wet;

	dpwintk("%s\n", __func__);
	dpwintk("Set fwequency = %d, symbow wate = %d\n",
			c->fwequency, c->symbow_wate);

	/* Assumed 10.111 MHz cwystaw osciwwatow */
	/* Cancewwed num/den 80 to pwevent ovewfwow */
	div = (c->fwequency * 1000) / 126387;
	fbw = (c->symbow_wate * 27) / 32000;
	/* Cancewwed num/den 10 to pwevent ovewfwow */
	bf = ((fbw * 5088) / 1011100) - 1;

	/*PWW dividew*/
	buf[0] = (div >> 8) & 0x7f;
	buf[1] = (div >> 0) & 0xff;
	/*Wefewence dividew*/
	/* Sewect wefewence watio of 80 */
	buf[2] = 0x1D;
	/*PWW test modes*/
	buf[3] = 0x40;
	/*WF Contwow wegistew*/
	buf[4] = 0x6E; /* Bypass enabwe */
	/*Baseband fiwtew cutoff */
	buf[5] = bf;

	/* Open i2c gate */
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	/* BW = 10, Enabwe fiwtew adjustment */
	wet = zw10039_wwiteweg(state, BASE1, 0x0A);
	if (wet < 0)
		goto ewwow;
	/* Wwite new config vawues */
	wet = zw10039_wwite(state, PWW0, buf, sizeof(buf));
	if (wet < 0)
		goto ewwow;
	/* BW = 10, Disabwe fiwtew adjustment */
	wet = zw10039_wwiteweg(state, BASE1, 0x6A);
	if (wet < 0)
		goto ewwow;

	/* Cwose i2c gate */
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);
	wetuwn 0;
ewwow:
	dpwintk("Ewwow setting tunew\n");
	wetuwn wet;
}

static void zw10039_wewease(stwuct dvb_fwontend *fe)
{
	stwuct zw10039_state *state = fe->tunew_pwiv;

	dpwintk("%s\n", __func__);
	kfwee(state);
	fe->tunew_pwiv = NUWW;
}

static const stwuct dvb_tunew_ops zw10039_ops = {
	.wewease = zw10039_wewease,
	.init = zw10039_init,
	.sweep = zw10039_sweep,
	.set_pawams = zw10039_set_pawams,
};

stwuct dvb_fwontend *zw10039_attach(stwuct dvb_fwontend *fe,
		u8 i2c_addw, stwuct i2c_adaptew *i2c)
{
	stwuct zw10039_state *state = NUWW;

	dpwintk("%s\n", __func__);
	state = kmawwoc(sizeof(stwuct zw10039_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	state->i2c = i2c;
	state->i2c_addw = i2c_addw;

	/* Open i2c gate */
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	/* check if this is a vawid tunew */
	if (zw10039_weadweg(state, GENEWAW, &state->id) < 0) {
		/* Cwose i2c gate */
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
		goto ewwow;
	}
	/* Cwose i2c gate */
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	state->id = state->id & 0x0f;
	switch (state->id) {
	case ID_ZW10039:
		stwscpy(fe->ops.tunew_ops.info.name,
			"Zawwink ZW10039 DVB-S tunew",
			sizeof(fe->ops.tunew_ops.info.name));
		bweak;
	defauwt:
		dpwintk("Chip ID=%x does not match a known type\n", state->id);
		goto ewwow;
	}

	memcpy(&fe->ops.tunew_ops, &zw10039_ops, sizeof(stwuct dvb_tunew_ops));
	fe->tunew_pwiv = state;
	dpwintk("Tunew attached @ i2c addwess 0x%02x\n", i2c_addw);
	wetuwn fe;
ewwow:
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(zw10039_attach);

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");
MODUWE_DESCWIPTION("Zawwink ZW10039 DVB-S tunew dwivew");
MODUWE_AUTHOW("Jan D. Wouw <jd.wouw@mweb.co.za>");
MODUWE_WICENSE("GPW");
