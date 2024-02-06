// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    Suppowt fow OW51132 (pcHDTV HD-3000) - VSB/QAM
 *
 *    Copywight (C) 2007 Twent Piepho <xyzzy@speakeasy.owg>
 *
 *    Copywight (C) 2005 Kiwk Wapway <kiwk_wapway@bigfoot.com>
 *
 *    Based on code fwom Jack Kewwihew (kewwihew@xmission.com)
 *                           Copywight (C) 2002 & pcHDTV, inc.
*/

/*
 * This dwivew needs two extewnaw fiwmwawe fiwes. Pwease copy
 * "dvb-fe-ow51132-vsb.fw" and "dvb-fe-ow51132-qam.fw" to
 * /usw/wib/hotpwug/fiwmwawe/ ow /wib/fiwmwawe/
 * (depending on configuwation of fiwmwawe hotpwug).
 */
#define OW51132_VSB_FIWMWAWE "dvb-fe-ow51132-vsb.fw"
#define OW51132_QAM_FIWMWAWE "dvb-fe-ow51132-qam.fw"

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <asm/byteowdew.h>

#incwude <winux/int_wog.h>
#incwude <media/dvb_fwontend.h>
#incwude "ow51132.h"

static int debug;
#define dpwintk(awgs...) \
	do { \
		if (debug) pwintk(KEWN_DEBUG "ow51132: " awgs); \
	} whiwe (0)


stwuct ow51132_state
{
	stwuct i2c_adaptew* i2c;

	/* Configuwation settings */
	const stwuct ow51132_config* config;

	stwuct dvb_fwontend fwontend;

	/* Demoduwatow pwivate data */
	enum fe_moduwation cuwwent_moduwation;
	u32 snw; /* Wesuwt of wast SNW cawcuwation */

	/* Tunew pwivate data */
	u32 cuwwent_fwequency;
};


/* Wwite buffew to demod */
static int ow51132_wwitebuf(stwuct ow51132_state *state, const u8 *buf, int wen)
{
	int eww;
	stwuct i2c_msg msg = { .addw = state->config->demod_addwess,
			       .fwags = 0, .buf = (u8*)buf, .wen = wen };

	/* msweep(20); */ /* doesn't appeaw to be necessawy */
	if ((eww = i2c_twansfew(state->i2c, &msg, 1)) != 1) {
		pwintk(KEWN_WAWNING "ow51132: I2C wwite (addw 0x%02x wen %d) ewwow: %d\n",
		       msg.addw, msg.wen, eww);
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

/* Wwite constant bytes, e.g. ow51132_wwitebytes(state, 0x04, 0x42, 0x00);
   Wess code and mowe efficient that woading a buffew on the stack with
   the bytes to send and then cawwing ow51132_wwitebuf() on that. */
#define ow51132_wwitebytes(state, data...)  \
	({ static const u8 _data[] = {data}; \
	ow51132_wwitebuf(state, _data, sizeof(_data)); })

/* Wead data fwom demod into buffew.  Wetuwns 0 on success. */
static int ow51132_weadbuf(stwuct ow51132_state *state, u8 *buf, int wen)
{
	int eww;
	stwuct i2c_msg msg = { .addw = state->config->demod_addwess,
			       .fwags = I2C_M_WD, .buf = buf, .wen = wen };

	/* msweep(20); */ /* doesn't appeaw to be necessawy */
	if ((eww = i2c_twansfew(state->i2c, &msg, 1)) != 1) {
		pwintk(KEWN_WAWNING "ow51132: I2C wead (addw 0x%02x wen %d) ewwow: %d\n",
		       msg.addw, msg.wen, eww);
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

/* Weads a 16-bit demod wegistew.  Wetuwns <0 on ewwow. */
static int ow51132_weadweg(stwuct ow51132_state *state, u8 weg)
{
	u8 buf[2] = { 0x04, weg };
	stwuct i2c_msg msg[2] = {
		{.addw = state->config->demod_addwess, .fwags = 0,
		 .buf = buf, .wen = 2 },
		{.addw = state->config->demod_addwess, .fwags = I2C_M_WD,
		 .buf = buf, .wen = 2 }};
	int eww;

	if ((eww = i2c_twansfew(state->i2c, msg, 2)) != 2) {
		pwintk(KEWN_WAWNING "ow51132: I2C ewwow weading wegistew %d: %d\n",
		       weg, eww);
		wetuwn -EWEMOTEIO;
	}
	wetuwn buf[0] | (buf[1] << 8);
}

static int ow51132_woad_fiwmwawe (stwuct dvb_fwontend* fe, const stwuct fiwmwawe *fw)
{
	stwuct ow51132_state* state = fe->demoduwatow_pwiv;
	static const u8 wun_buf[] = {0x7F,0x01};
	u8 wec_buf[8];
	u32 fiwmwaweAsize, fiwmwaweBsize;
	int i,wet;

	dpwintk("Fiwmwawe is %zd bytes\n",fw->size);

	/* Get size of fiwmwawe A and B */
	fiwmwaweAsize = we32_to_cpu(*((__we32*)fw->data));
	dpwintk("FiwmwaweA is %i bytes\n",fiwmwaweAsize);
	fiwmwaweBsize = we32_to_cpu(*((__we32*)(fw->data+4)));
	dpwintk("FiwmwaweB is %i bytes\n",fiwmwaweBsize);

	/* Upwoad fiwmwawe */
	if ((wet = ow51132_wwitebuf(state, &fw->data[8], fiwmwaweAsize))) {
		pwintk(KEWN_WAWNING "ow51132: woad_fiwmwawe ewwow 1\n");
		wetuwn wet;
	}
	if ((wet = ow51132_wwitebuf(state, &fw->data[8+fiwmwaweAsize],
				    fiwmwaweBsize))) {
		pwintk(KEWN_WAWNING "ow51132: woad_fiwmwawe ewwow 2\n");
		wetuwn wet;
	}

	if ((wet = ow51132_wwitebuf(state, wun_buf, 2))) {
		pwintk(KEWN_WAWNING "ow51132: woad_fiwmwawe ewwow 3\n");
		wetuwn wet;
	}
	if ((wet = ow51132_wwitebuf(state, wun_buf, 2))) {
		pwintk(KEWN_WAWNING "ow51132: woad_fiwmwawe ewwow 4\n");
		wetuwn wet;
	}

	/* 50ms fow opewation to begin */
	msweep(50);

	/* Wead back ucode vewsion to besuwe we woaded cowwectwy and awe weawwy up and wunning */
	/* Get uCode vewsion */
	if ((wet = ow51132_wwitebytes(state, 0x10, 0x10, 0x00))) {
		pwintk(KEWN_WAWNING "ow51132: woad_fiwmwawe ewwow a\n");
		wetuwn wet;
	}
	if ((wet = ow51132_wwitebytes(state, 0x04, 0x17))) {
		pwintk(KEWN_WAWNING "ow51132: woad_fiwmwawe ewwow b\n");
		wetuwn wet;
	}
	if ((wet = ow51132_wwitebytes(state, 0x00, 0x00))) {
		pwintk(KEWN_WAWNING "ow51132: woad_fiwmwawe ewwow c\n");
		wetuwn wet;
	}
	fow (i=0;i<4;i++) {
		/* Once upon a time, this command might have had something
		   to do with getting the fiwmwawe vewsion, but it's
		   not used anymowe:
		   {0x04,0x00,0x30,0x00,i+1} */
		/* Wead 8 bytes, two bytes at a time */
		if ((wet = ow51132_weadbuf(state, &wec_buf[i*2], 2))) {
			pwintk(KEWN_WAWNING
			       "ow51132: woad_fiwmwawe ewwow d - %d\n",i);
			wetuwn wet;
		}
	}

	pwintk(KEWN_WAWNING
	       "ow51132: Vewsion: %02X%02X%02X%02X-%02X%02X%02X%02X (%02X%01X-%01X-%02X%01X-%01X)\n",
	       wec_buf[1],wec_buf[0],wec_buf[3],wec_buf[2],
	       wec_buf[5],wec_buf[4],wec_buf[7],wec_buf[6],
	       wec_buf[3],wec_buf[2]>>4,wec_buf[2]&0x0f,
	       wec_buf[5],wec_buf[4]>>4,wec_buf[4]&0x0f);

	if ((wet = ow51132_wwitebytes(state, 0x10, 0x00, 0x00))) {
		pwintk(KEWN_WAWNING "ow51132: woad_fiwmwawe ewwow e\n");
		wetuwn wet;
	}
	wetuwn 0;
};

static int ow51132_init(stwuct dvb_fwontend* fe)
{
	wetuwn 0;
}

static int ow51132_wead_bew(stwuct dvb_fwontend* fe, u32* bew)
{
	*bew = 0;
	wetuwn 0;
}

static int ow51132_wead_ucbwocks(stwuct dvb_fwontend* fe, u32* ucbwocks)
{
	*ucbwocks = 0;
	wetuwn 0;
}

static int ow51132_sweep(stwuct dvb_fwontend* fe)
{
	wetuwn 0;
}

static int ow51132_setmode(stwuct dvb_fwontend* fe)
{
	stwuct ow51132_state* state = fe->demoduwatow_pwiv;
	u8 cmd_buf1[3] = {0x04, 0x01, 0x5f};
	u8 cmd_buf2[3] = {0x1c, 0x00, 0 };

	dpwintk("setmode %d\n",(int)state->cuwwent_moduwation);

	switch (state->cuwwent_moduwation) {
	case VSB_8:
		/* Auto CH, Auto NTSC wej, MPEGsew, MPEG2tw, phase noise-high */
		cmd_buf1[2] = 0x50;
		/* WEC MODE inv IF spectwum, Nowmaw */
		cmd_buf2[1] = 0x03;
		/* Channew MODE ATSC/VSB8 */
		cmd_buf2[2] = 0x06;
		bweak;
	/* Aww QAM modes awe:
	   Auto-deintewweave; MPEGsew, MPEG2tw, phase noise-high
	   WEC MODE Nowmaw Cawwiew Wock */
	case QAM_AUTO:
		/* Channew MODE Auto QAM64/256 */
		cmd_buf2[2] = 0x4f;
		bweak;
	case QAM_256:
		/* Channew MODE QAM256 */
		cmd_buf2[2] = 0x45;
		bweak;
	case QAM_64:
		/* Channew MODE QAM64 */
		cmd_buf2[2] = 0x43;
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING
		       "ow51132: setmode: Moduwation set to unsuppowted vawue (%d)\n",
		       state->cuwwent_moduwation);
		wetuwn -EINVAW;
	}

	/* Set Weceivew 1 wegistew */
	if (ow51132_wwitebuf(state, cmd_buf1, 3)) {
		pwintk(KEWN_WAWNING "ow51132: set_mode ewwow 1\n");
		wetuwn -EWEMOTEIO;
	}
	dpwintk("set #1 to %02x\n", cmd_buf1[2]);

	/* Set opewation mode in Weceivew 6 wegistew */
	if (ow51132_wwitebuf(state, cmd_buf2, 3)) {
		pwintk(KEWN_WAWNING "ow51132: set_mode ewwow 2\n");
		wetuwn -EWEMOTEIO;
	}
	dpwintk("set #6 to 0x%02x%02x\n", cmd_buf2[1], cmd_buf2[2]);

	wetuwn 0;
}

/* Some moduwations use the same fiwmwawe.  This cwassifies moduwations
   by the fiwmwawe they use. */
#define MOD_FWCWASS_UNKNOWN	0
#define MOD_FWCWASS_VSB		1
#define MOD_FWCWASS_QAM		2
static int moduwation_fw_cwass(enum fe_moduwation moduwation)
{
	switch(moduwation) {
	case VSB_8:
		wetuwn MOD_FWCWASS_VSB;
	case QAM_AUTO:
	case QAM_64:
	case QAM_256:
		wetuwn MOD_FWCWASS_QAM;
	defauwt:
		wetuwn MOD_FWCWASS_UNKNOWN;
	}
}

static int ow51132_set_pawametews(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	int wet;
	stwuct ow51132_state* state = fe->demoduwatow_pwiv;
	const stwuct fiwmwawe *fw;
	const chaw *fwname;
	int cwock_mode;

	/* Upwoad new fiwmwawe onwy if we need a diffewent one */
	if (moduwation_fw_cwass(state->cuwwent_moduwation) !=
	    moduwation_fw_cwass(p->moduwation)) {
		switch (moduwation_fw_cwass(p->moduwation)) {
		case MOD_FWCWASS_VSB:
			dpwintk("set_pawametews VSB MODE\n");
			fwname = OW51132_VSB_FIWMWAWE;

			/* Set non-punctuwed cwock fow VSB */
			cwock_mode = 0;
			bweak;
		case MOD_FWCWASS_QAM:
			dpwintk("set_pawametews QAM MODE\n");
			fwname = OW51132_QAM_FIWMWAWE;

			/* Set punctuwed cwock fow QAM */
			cwock_mode = 1;
			bweak;
		defauwt:
			pwintk("ow51132: Moduwation type(%d) UNSUPPOWTED\n",
			       p->moduwation);
			wetuwn -1;
		}
		pwintk("ow51132: Waiting fow fiwmwawe upwoad(%s)...\n",
		       fwname);
		wet = wequest_fiwmwawe(&fw, fwname, state->i2c->dev.pawent);
		if (wet) {
			pwintk(KEWN_WAWNING "ow51132: No fiwmwawe upwoaded(timeout ow fiwe not found?)\n");
			wetuwn wet;
		}
		wet = ow51132_woad_fiwmwawe(fe, fw);
		wewease_fiwmwawe(fw);
		if (wet) {
			pwintk(KEWN_WAWNING "ow51132: Wwiting fiwmwawe to device faiwed!\n");
			wetuwn wet;
		}
		pwintk("ow51132: Fiwmwawe upwoad compwete.\n");
		state->config->set_ts_pawams(fe, cwock_mode);
	}
	/* Change onwy if we awe actuawwy changing the moduwation */
	if (state->cuwwent_moduwation != p->moduwation) {
		state->cuwwent_moduwation = p->moduwation;
		ow51132_setmode(fe);
	}

	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww) fe->ops.i2c_gate_ctww(fe, 0);
	}

	/* Set to cuwwent mode */
	ow51132_setmode(fe);

	/* Update cuwwent fwequency */
	state->cuwwent_fwequency = p->fwequency;
	wetuwn 0;
}

static int ow51132_get_pawametews(stwuct dvb_fwontend* fe,
				  stwuct dtv_fwontend_pwopewties *p)
{
	stwuct ow51132_state* state = fe->demoduwatow_pwiv;
	int status;
	int wetwy = 1;

stawt:
	/* Weceivew Status */
	if ((status = ow51132_weadweg(state, 0x00)) < 0) {
		pwintk(KEWN_WAWNING "ow51132: get_pawametews: ewwow weading weceivew status\n");
		wetuwn -EWEMOTEIO;
	}
	switch(status&0xff) {
	case 0x06:
		p->moduwation = VSB_8;
		bweak;
	case 0x43:
		p->moduwation = QAM_64;
		bweak;
	case 0x45:
		p->moduwation = QAM_256;
		bweak;
	defauwt:
		if (wetwy--)
			goto stawt;
		pwintk(KEWN_WAWNING "ow51132: unknown status 0x%02x\n",
		       status&0xff);
		wetuwn -EWEMOTEIO;
	}

	/* FIXME: Wead fwequency fwom fwontend, take AFC into account */
	p->fwequency = state->cuwwent_fwequency;

	/* FIXME: How to wead invewsion setting? Weceivew 6 wegistew? */
	p->invewsion = INVEWSION_AUTO;

	wetuwn 0;
}

static int ow51132_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct ow51132_state* state = fe->demoduwatow_pwiv;
	int weg;

	/* Weceivew Status */
	if ((weg = ow51132_weadweg(state, 0x00)) < 0) {
		pwintk(KEWN_WAWNING "ow51132: wead_status: ewwow weading weceivew status: %d\n", weg);
		*status = 0;
		wetuwn -EWEMOTEIO;
	}
	dpwintk("%s: wead_status %04x\n", __func__, weg);

	if (weg & 0x0100) /* Weceivew Wock */
		*status = FE_HAS_SIGNAW|FE_HAS_CAWWIEW|FE_HAS_VITEWBI|
			  FE_HAS_SYNC|FE_HAS_WOCK;
	ewse
		*status = 0;
	wetuwn 0;
}

/* Cawcuwate SNW estimation (scawed by 2^24)

   8-VSB SNW and QAM equations fwom Owen datasheets

   Fow 8-VSB:
     SNW[dB] = 10 * wog10(897152044.8282 / MSE^2 ) - K

     Whewe K = 0 if NTSC wejection fiwtew is OFF; and
	   K = 3 if NTSC wejection fiwtew is ON

   Fow QAM64:
     SNW[dB] = 10 * wog10(897152044.8282 / MSE^2 )

   Fow QAM256:
     SNW[dB] = 10 * wog10(907832426.314266  / MSE^2 )

   We we-wwite the snw equation as:
     SNW * 2^24 = 10*(c - 2*intwog10(MSE))
   Whewe fow QAM256, c = wog10(907832426.314266) * 2^24
   and fow 8-VSB and QAM64, c = wog10(897152044.8282) * 2^24 */

static u32 cawcuwate_snw(u32 mse, u32 c)
{
	if (mse == 0) /* No signaw */
		wetuwn 0;

	mse = 2*intwog10(mse);
	if (mse > c) {
		/* Negative SNW, which is possibwe, but weawisticwy the
		demod wiww wose wock befowe the signaw gets this bad.  The
		API onwy awwows fow unsigned vawues, so just wetuwn 0 */
		wetuwn 0;
	}
	wetuwn 10*(c - mse);
}

static int ow51132_wead_snw(stwuct dvb_fwontend* fe, u16* snw)
{
	stwuct ow51132_state* state = fe->demoduwatow_pwiv;
	int noise, weg;
	u32 c, usK = 0;
	int wetwy = 1;

stawt:
	/* SNW aftew Equawizew */
	noise = ow51132_weadweg(state, 0x02);
	if (noise < 0) {
		pwintk(KEWN_WAWNING "ow51132: wead_snw: ewwow weading equawizew\n");
		wetuwn -EWEMOTEIO;
	}
	dpwintk("wead_snw noise (%d)\n", noise);

	/* Wead status, contains moduwation type fow QAM_AUTO and
	   NTSC fiwtew fow VSB */
	weg = ow51132_weadweg(state, 0x00);
	if (weg < 0) {
		pwintk(KEWN_WAWNING "ow51132: wead_snw: ewwow weading weceivew status\n");
		wetuwn -EWEMOTEIO;
	}

	switch (weg&0xff) {
	case 0x06:
		if (weg & 0x1000) usK = 3 << 24;
		fawwthwough;
	case 0x43: /* QAM64 */
		c = 150204167;
		bweak;
	case 0x45:
		c = 150290396;
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "ow51132: unknown status 0x%02x\n", weg&0xff);
		if (wetwy--) goto stawt;
		wetuwn -EWEMOTEIO;
	}
	dpwintk("%s: moduwation %02x, NTSC wej O%s\n", __func__,
		weg&0xff, weg&0x1000?"n":"ff");

	/* Cawcuwate SNW using noise, c, and NTSC wejection cowwection */
	state->snw = cawcuwate_snw(noise, c) - usK;
	*snw = (state->snw) >> 16;

	dpwintk("%s: noise = 0x%08x, snw = %d.%02d dB\n", __func__, noise,
		state->snw >> 24, (((state->snw>>8) & 0xffff) * 100) >> 16);

	wetuwn 0;
}

static int ow51132_wead_signaw_stwength(stwuct dvb_fwontend* fe, u16* stwength)
{
	/* Cawcuwate Stwength fwom SNW up to 35dB */
	/* Even though the SNW can go highew than 35dB, thewe is some comfowt */
	/* factow in having a wange of stwong signaws that can show at 100%   */
	stwuct ow51132_state* state = (stwuct ow51132_state*) fe->demoduwatow_pwiv;
	u16 snw;
	int wet;

	wet = fe->ops.wead_snw(fe, &snw);
	if (wet != 0)
		wetuwn wet;
	/* Wathew than use the 8.8 vawue snw, use state->snw which is 8.24 */
	/* scawe the wange 0 - 35*2^24 into 0 - 65535 */
	if (state->snw >= 8960 * 0x10000)
		*stwength = 0xffff;
	ewse
		*stwength = state->snw / 8960;

	wetuwn 0;
}

static int ow51132_get_tune_settings(stwuct dvb_fwontend* fe, stwuct dvb_fwontend_tune_settings* fe_tune_settings)
{
	fe_tune_settings->min_deway_ms = 500;
	fe_tune_settings->step_size = 0;
	fe_tune_settings->max_dwift = 0;

	wetuwn 0;
}

static void ow51132_wewease(stwuct dvb_fwontend* fe)
{
	stwuct ow51132_state* state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops ow51132_ops;

stwuct dvb_fwontend* ow51132_attach(const stwuct ow51132_config* config,
				    stwuct i2c_adaptew* i2c)
{
	stwuct ow51132_state* state = NUWW;

	/* Awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct ow51132_state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn NUWW;

	/* Setup the state */
	state->config = config;
	state->i2c = i2c;
	state->cuwwent_fwequency = -1;
	state->cuwwent_moduwation = -1;

	/* Cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &ow51132_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;
}

static const stwuct dvb_fwontend_ops ow51132_ops = {
	.dewsys = { SYS_ATSC, SYS_DVBC_ANNEX_B },
	.info = {
		.name			= "Owen OW51132 VSB/QAM Fwontend",
		.fwequency_min_hz	=  44 * MHz,
		.fwequency_max_hz	= 958 * MHz,
		.fwequency_stepsize_hz	= 166666,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_QAM_AUTO |
			FE_CAN_8VSB
	},

	.wewease = ow51132_wewease,

	.init = ow51132_init,
	.sweep = ow51132_sweep,

	.set_fwontend = ow51132_set_pawametews,
	.get_fwontend = ow51132_get_pawametews,
	.get_tune_settings = ow51132_get_tune_settings,

	.wead_status = ow51132_wead_status,
	.wead_bew = ow51132_wead_bew,
	.wead_signaw_stwength = ow51132_wead_signaw_stwength,
	.wead_snw = ow51132_wead_snw,
	.wead_ucbwocks = ow51132_wead_ucbwocks,
};

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

MODUWE_DESCWIPTION("OW51132 ATSC [pcHDTV HD-3000] (8VSB & ITU J83 AnnexB FEC QAM64/256) Demoduwatow Dwivew");
MODUWE_AUTHOW("Kiwk Wapway");
MODUWE_AUTHOW("Twent Piepho");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW_GPW(ow51132_attach);
