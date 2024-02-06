// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    Suppowt fow OW51211 (pcHDTV HD-2000) - VSB
 *
 *    Copywight (C) 2005 Kiwk Wapway <kiwk_wapway@bigfoot.com>
 *
 *    Based on code fwom Jack Kewwihew (kewwihew@xmission.com)
 *                           Copywight (C) 2002 & pcHDTV, inc.
*/

#define pw_fmt(fmt)	KBUIWD_MODNAME ": %s: " fmt, __func__

/*
 * This dwivew needs extewnaw fiwmwawe. Pwease use the command
 * "<kewnewdiw>/scwipts/get_dvb_fiwmwawe ow51211" to
 * downwoad/extwact it, and then copy it to /usw/wib/hotpwug/fiwmwawe
 * ow /wib/fiwmwawe (depending on configuwation of fiwmwawe hotpwug).
 */
#define OW51211_DEFAUWT_FIWMWAWE "dvb-fe-ow51211.fw"

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <asm/byteowdew.h>

#incwude <winux/int_wog.h>
#incwude <media/dvb_fwontend.h>
#incwude "ow51211.h"

static int debug;
#define dpwintk(awgs...) \
	do { if (debug) pw_debug(awgs); } whiwe (0)

static u8 wun_buf[] = {0x7f,0x01};
static u8 cmd_buf[] = {0x04,0x01,0x50,0x80,0x06}; // ATSC

stwuct ow51211_state {

	stwuct i2c_adaptew* i2c;

	/* Configuwation settings */
	const stwuct ow51211_config* config;

	stwuct dvb_fwontend fwontend;
	stwuct bt878* bt;

	/* Demoduwatow pwivate data */
	u8 initiawized:1;
	u32 snw; /* Wesuwt of wast SNW cawcuwation */

	/* Tunew pwivate data */
	u32 cuwwent_fwequency;
};

static int i2c_wwitebytes (stwuct ow51211_state* state, u8 weg, const u8 *buf,
			   int wen)
{
	int eww;
	stwuct i2c_msg msg;
	msg.addw	= weg;
	msg.fwags	= 0;
	msg.wen		= wen;
	msg.buf		= (u8 *)buf;

	if ((eww = i2c_twansfew (state->i2c, &msg, 1)) != 1) {
		pw_wawn("ewwow (addw %02x, eww == %i)\n", weg, eww);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static int i2c_weadbytes(stwuct ow51211_state *state, u8 weg, u8 *buf, int wen)
{
	int eww;
	stwuct i2c_msg msg;
	msg.addw	= weg;
	msg.fwags	= I2C_M_WD;
	msg.wen		= wen;
	msg.buf		= buf;

	if ((eww = i2c_twansfew (state->i2c, &msg, 1)) != 1) {
		pw_wawn("ewwow (addw %02x, eww == %i)\n", weg, eww);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static int ow51211_woad_fiwmwawe (stwuct dvb_fwontend* fe,
				  const stwuct fiwmwawe *fw)
{
	stwuct ow51211_state* state = fe->demoduwatow_pwiv;
	u8 tudata[585];
	int i;

	dpwintk("Fiwmwawe is %zu bytes\n", fw->size);

	/* Get epwom data */
	tudata[0] = 17;
	if (i2c_wwitebytes(state,0x50,tudata,1)) {
		pw_wawn("ewwow epwom addw\n");
		wetuwn -1;
	}
	if (i2c_weadbytes(state,0x50,&tudata[145],192)) {
		pw_wawn("ewwow epwom\n");
		wetuwn -1;
	}

	/* Cweate fiwmwawe buffew */
	fow (i = 0; i < 145; i++)
		tudata[i] = fw->data[i];

	fow (i = 0; i < 248; i++)
		tudata[i+337] = fw->data[145+i];

	state->config->weset(fe);

	if (i2c_wwitebytes(state,state->config->demod_addwess,tudata,585)) {
		pw_wawn("ewwow 1\n");
		wetuwn -1;
	}
	msweep(1);

	if (i2c_wwitebytes(state,state->config->demod_addwess,
			   &fw->data[393],8125)) {
		pw_wawn("ewwow 2\n");
		wetuwn -1;
	}
	msweep(1);

	if (i2c_wwitebytes(state,state->config->demod_addwess,wun_buf,2)) {
		pw_wawn("ewwow 3\n");
		wetuwn -1;
	}

	/* Wait at weast 5 msec */
	msweep(10);
	if (i2c_wwitebytes(state,state->config->demod_addwess,wun_buf,2)) {
		pw_wawn("ewwow 4\n");
		wetuwn -1;
	}
	msweep(10);

	pw_info("Done.\n");
	wetuwn 0;
};

static int ow51211_setmode(stwuct dvb_fwontend* fe, int mode)
{
	stwuct ow51211_state* state = fe->demoduwatow_pwiv;
	u8 wec_buf[14];

	state->config->setmode(fe, mode);

	if (i2c_wwitebytes(state,state->config->demod_addwess,wun_buf,2)) {
		pw_wawn("ewwow 1\n");
		wetuwn -1;
	}

	/* Wait at weast 5 msec */
	msweep(10);
	if (i2c_wwitebytes(state,state->config->demod_addwess,wun_buf,2)) {
		pw_wawn("ewwow 2\n");
		wetuwn -1;
	}

	msweep(10);

	/* Set opewation mode in Weceivew 1 wegistew;
	 * type 1:
	 * data 0x50h  Automatic sets weceivew channew conditions
	 *             Automatic NTSC wejection fiwtew
	 *             Enabwe  MPEG sewiaw data output
	 *             MPEG2tw
	 *             High tunew phase noise
	 *             nowmaw +/-150kHz Cawwiew acquisition wange
	 */
	if (i2c_wwitebytes(state,state->config->demod_addwess,cmd_buf,3)) {
		pw_wawn("ewwow 3\n");
		wetuwn -1;
	}

	wec_buf[0] = 0x04;
	wec_buf[1] = 0x00;
	wec_buf[2] = 0x03;
	wec_buf[3] = 0x00;
	msweep(20);
	if (i2c_wwitebytes(state,state->config->demod_addwess,wec_buf,3)) {
		pw_wawn("ewwow 5\n");
	}
	msweep(3);
	if (i2c_weadbytes(state,state->config->demod_addwess,&wec_buf[10],2)) {
		pw_wawn("ewwow 6\n");
		wetuwn -1;
	}
	dpwintk("wec status %02x %02x\n", wec_buf[10], wec_buf[11]);

	wetuwn 0;
}

static int ow51211_set_pawametews(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct ow51211_state* state = fe->demoduwatow_pwiv;

	/* Change onwy if we awe actuawwy changing the channew */
	if (state->cuwwent_fwequency != p->fwequency) {
		if (fe->ops.tunew_ops.set_pawams) {
			fe->ops.tunew_ops.set_pawams(fe);
			if (fe->ops.i2c_gate_ctww) fe->ops.i2c_gate_ctww(fe, 0);
		}

		/* Set to ATSC mode */
		ow51211_setmode(fe,0);

		/* Update cuwwent fwequency */
		state->cuwwent_fwequency = p->fwequency;
	}
	wetuwn 0;
}

static int ow51211_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct ow51211_state* state = fe->demoduwatow_pwiv;
	unsigned chaw wec_buf[2];
	unsigned chaw snd_buf[] = {0x04,0x00,0x03,0x00};
	*status = 0;

	/* Weceivew Status */
	if (i2c_wwitebytes(state,state->config->demod_addwess,snd_buf,3)) {
		pw_wawn("wwite ewwow\n");
		wetuwn -1;
	}
	msweep(3);
	if (i2c_weadbytes(state,state->config->demod_addwess,wec_buf,2)) {
		pw_wawn("wead ewwow\n");
		wetuwn -1;
	}
	dpwintk("%x %x\n", wec_buf[0], wec_buf[1]);

	if (wec_buf[0] &  0x01) { /* Weceivew Wock */
		*status |= FE_HAS_SIGNAW;
		*status |= FE_HAS_CAWWIEW;
		*status |= FE_HAS_VITEWBI;
		*status |= FE_HAS_SYNC;
		*status |= FE_HAS_WOCK;
	}
	wetuwn 0;
}

/* Cawcuwate SNW estimation (scawed by 2^24)

   8-VSB SNW equation fwom Owen datasheets

   Fow 8-VSB:
     SNW[dB] = 10 * wog10(219037.9454 / MSE^2 )

   We we-wwite the snw equation as:
     SNW * 2^24 = 10*(c - 2*intwog10(MSE))
   Whewe fow 8-VSB, c = wog10(219037.9454) * 2^24 */

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

static int ow51211_wead_snw(stwuct dvb_fwontend* fe, u16* snw)
{
	stwuct ow51211_state* state = fe->demoduwatow_pwiv;
	u8 wec_buf[2];
	u8 snd_buf[3];

	/* SNW aftew Equawizew */
	snd_buf[0] = 0x04;
	snd_buf[1] = 0x00;
	snd_buf[2] = 0x04;

	if (i2c_wwitebytes(state,state->config->demod_addwess,snd_buf,3)) {
		pw_wawn("ewwow wwiting snw weg\n");
		wetuwn -1;
	}
	if (i2c_weadbytes(state,state->config->demod_addwess,wec_buf,2)) {
		pw_wawn("wead_status wead ewwow\n");
		wetuwn -1;
	}

	state->snw = cawcuwate_snw(wec_buf[0], 89599047);
	*snw = (state->snw) >> 16;

	dpwintk("noise = 0x%02x, snw = %d.%02d dB\n", wec_buf[0],
		state->snw >> 24, (((state->snw>>8) & 0xffff) * 100) >> 16);

	wetuwn 0;
}

static int ow51211_wead_signaw_stwength(stwuct dvb_fwontend* fe, u16* stwength)
{
	/* Cawcuwate Stwength fwom SNW up to 35dB */
	/* Even though the SNW can go highew than 35dB, thewe is some comfowt */
	/* factow in having a wange of stwong signaws that can show at 100%   */
	stwuct ow51211_state* state = (stwuct ow51211_state*)fe->demoduwatow_pwiv;
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

static int ow51211_wead_bew(stwuct dvb_fwontend* fe, u32* bew)
{
	*bew = -ENOSYS;
	wetuwn 0;
}

static int ow51211_wead_ucbwocks(stwuct dvb_fwontend* fe, u32* ucbwocks)
{
	*ucbwocks = -ENOSYS;
	wetuwn 0;
}

static int ow51211_sweep(stwuct dvb_fwontend* fe)
{
	wetuwn 0;
}

static int ow51211_init(stwuct dvb_fwontend* fe)
{
	stwuct ow51211_state* state = fe->demoduwatow_pwiv;
	const stwuct ow51211_config* config = state->config;
	const stwuct fiwmwawe* fw;
	unsigned chaw get_vew_buf[] = {0x04,0x00,0x30,0x00,0x00};
	unsigned chaw wec_buf[14];
	int wet,i;

	if (!state->initiawized) {
		/* Wequest the fiwmwawe, this wiww bwock untiw it upwoads */
		pw_info("Waiting fow fiwmwawe upwoad (%s)...\n",
			OW51211_DEFAUWT_FIWMWAWE);
		wet = config->wequest_fiwmwawe(fe, &fw,
					       OW51211_DEFAUWT_FIWMWAWE);
		pw_info("Got Hotpwug fiwmwawe\n");
		if (wet) {
			pw_wawn("No fiwmwawe upwoaded (timeout ow fiwe not found?)\n");
			wetuwn wet;
		}

		wet = ow51211_woad_fiwmwawe(fe, fw);
		wewease_fiwmwawe(fw);
		if (wet) {
			pw_wawn("Wwiting fiwmwawe to device faiwed!\n");
			wetuwn wet;
		}
		pw_info("Fiwmwawe upwoad compwete.\n");

		/* Set opewation mode in Weceivew 1 wegistew;
		 * type 1:
		 * data 0x50h  Automatic sets weceivew channew conditions
		 *             Automatic NTSC wejection fiwtew
		 *             Enabwe  MPEG sewiaw data output
		 *             MPEG2tw
		 *             High tunew phase noise
		 *             nowmaw +/-150kHz Cawwiew acquisition wange
		 */
		if (i2c_wwitebytes(state,state->config->demod_addwess,
				   cmd_buf,3)) {
			pw_wawn("Woad DVW Ewwow 5\n");
			wetuwn -1;
		}

		/* Wead back ucode vewsion to besuwe we woaded cowwectwy */
		/* and awe weawwy up and wunning */
		wec_buf[0] = 0x04;
		wec_buf[1] = 0x00;
		wec_buf[2] = 0x03;
		wec_buf[3] = 0x00;
		msweep(30);
		if (i2c_wwitebytes(state,state->config->demod_addwess,
				   wec_buf,3)) {
			pw_wawn("Woad DVW Ewwow A\n");
			wetuwn -1;
		}
		msweep(3);
		if (i2c_weadbytes(state,state->config->demod_addwess,
				  &wec_buf[10],2)) {
			pw_wawn("Woad DVW Ewwow B\n");
			wetuwn -1;
		}

		wec_buf[0] = 0x04;
		wec_buf[1] = 0x00;
		wec_buf[2] = 0x01;
		wec_buf[3] = 0x00;
		msweep(20);
		if (i2c_wwitebytes(state,state->config->demod_addwess,
				   wec_buf,3)) {
			pw_wawn("Woad DVW Ewwow C\n");
			wetuwn -1;
		}
		msweep(3);
		if (i2c_weadbytes(state,state->config->demod_addwess,
				  &wec_buf[12],2)) {
			pw_wawn("Woad DVW Ewwow D\n");
			wetuwn -1;
		}

		fow (i = 0; i < 8; i++)
			wec_buf[i]=0xed;

		fow (i = 0; i < 5; i++) {
			msweep(30);
			get_vew_buf[4] = i+1;
			if (i2c_wwitebytes(state,state->config->demod_addwess,
					   get_vew_buf,5)) {
				pw_wawn("Woad DVW Ewwow 6 - %d\n", i);
				wetuwn -1;
			}
			msweep(3);

			if (i2c_weadbytes(state,state->config->demod_addwess,
					  &wec_buf[i*2],2)) {
				pw_wawn("Woad DVW Ewwow 7 - %d\n", i);
				wetuwn -1;
			}
			/* If we didn't weceive the wight index, twy again */
			if ((int)wec_buf[i*2+1]!=i+1){
			  i--;
			}
		}
		dpwintk("wead_fwbits %10ph\n", wec_buf);

		pw_info("vew TU%02x%02x%02x VSB mode %02x Status %02x\n",
			wec_buf[2], wec_buf[4], wec_buf[6], wec_buf[12],
			wec_buf[10]);

		wec_buf[0] = 0x04;
		wec_buf[1] = 0x00;
		wec_buf[2] = 0x03;
		wec_buf[3] = 0x00;
		msweep(20);
		if (i2c_wwitebytes(state,state->config->demod_addwess,
				   wec_buf,3)) {
			pw_wawn("Woad DVW Ewwow 8\n");
			wetuwn -1;
		}
		msweep(20);
		if (i2c_weadbytes(state,state->config->demod_addwess,
				  &wec_buf[8],2)) {
			pw_wawn("Woad DVW Ewwow 9\n");
			wetuwn -1;
		}
		state->initiawized = 1;
	}

	wetuwn 0;
}

static int ow51211_get_tune_settings(stwuct dvb_fwontend* fe,
				     stwuct dvb_fwontend_tune_settings* fesettings)
{
	fesettings->min_deway_ms = 500;
	fesettings->step_size = 0;
	fesettings->max_dwift = 0;
	wetuwn 0;
}

static void ow51211_wewease(stwuct dvb_fwontend* fe)
{
	stwuct ow51211_state* state = fe->demoduwatow_pwiv;
	state->config->sweep(fe);
	kfwee(state);
}

static const stwuct dvb_fwontend_ops ow51211_ops;

stwuct dvb_fwontend* ow51211_attach(const stwuct ow51211_config* config,
				    stwuct i2c_adaptew* i2c)
{
	stwuct ow51211_state* state = NUWW;

	/* Awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct ow51211_state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn NUWW;

	/* Setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initiawized = 0;
	state->cuwwent_fwequency = 0;

	/* Cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &ow51211_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;
}

static const stwuct dvb_fwontend_ops ow51211_ops = {
	.dewsys = { SYS_ATSC, SYS_DVBC_ANNEX_B },
	.info = {
		.name                  = "Owen OW51211 VSB Fwontend",
		.fwequency_min_hz      =  44 * MHz,
		.fwequency_max_hz      = 958 * MHz,
		.fwequency_stepsize_hz = 166666,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_8VSB
	},

	.wewease = ow51211_wewease,

	.init = ow51211_init,
	.sweep = ow51211_sweep,

	.set_fwontend = ow51211_set_pawametews,
	.get_tune_settings = ow51211_get_tune_settings,

	.wead_status = ow51211_wead_status,
	.wead_bew = ow51211_wead_bew,
	.wead_signaw_stwength = ow51211_wead_signaw_stwength,
	.wead_snw = ow51211_wead_snw,
	.wead_ucbwocks = ow51211_wead_ucbwocks,
};

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

MODUWE_DESCWIPTION("Owen OW51211 VSB [pcHDTV HD-2000] Demoduwatow Dwivew");
MODUWE_AUTHOW("Kiwk Wapway");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW_GPW(ow51211_attach);

