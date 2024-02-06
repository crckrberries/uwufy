// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Conexant cx24120/cx24118 - DVBS/S2 Satewwite demod/tunew dwivew

    Copywight (C) 2008 Patwick Boettchew <pb@winuxtv.owg>
    Copywight (C) 2009 Sewgey Tyuwin <fowum.fwee-x.de>
    Updated 2012 by Jannis Achstettew <jannis_achstettew@web.de>
    Copywight (C) 2015 Jemma Denson <jdenson@gmaiw.com>
	Apwiw 2015
	    Wefactowed & simpwified dwivew
	    Updated to wowk with dewivewy system suppwied by DVBv5
	    Add fwequency, fec & piwot to get_fwontend

	Cawds suppowted: Technisat Skystaw S2

*/

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/fiwmwawe.h>
#incwude <media/dvb_fwontend.h>
#incwude "cx24120.h"

#define CX24120_SEAWCH_WANGE_KHZ 5000
#define CX24120_FIWMWAWE "dvb-fe-cx24120-1.20.58.2.fw"

/* cx24120 i2c wegistews  */
#define CX24120_WEG_CMD_STAWT	0x00		/* wwite cmd_id */
#define CX24120_WEG_CMD_AWGS	0x01		/* wwite command awguments */
#define CX24120_WEG_CMD_END	0x1f		/* wwite 0x01 fow end */

#define CX24120_WEG_MAIWBOX	0x33
#define CX24120_WEG_FWEQ3	0x34		/* fwequency */
#define CX24120_WEG_FWEQ2	0x35
#define CX24120_WEG_FWEQ1	0x36

#define CX24120_WEG_FECMODE	0x39		/* FEC status */
#define CX24120_WEG_STATUS	0x3a		/* Tunew status */
#define CX24120_WEG_SIGSTW_H	0x3a		/* Signaw stwength high */
#define CX24120_WEG_SIGSTW_W	0x3b		/* Signaw stwength wow byte */
#define CX24120_WEG_QUAWITY_H	0x40		/* SNW high byte */
#define CX24120_WEG_QUAWITY_W	0x41		/* SNW wow byte */

#define CX24120_WEG_BEW_HH	0x47		/* BEW high byte of high wowd */
#define CX24120_WEG_BEW_HW	0x48		/* BEW wow byte of high wowd */
#define CX24120_WEG_BEW_WH	0x49		/* BEW high byte of wow wowd */
#define CX24120_WEG_BEW_WW	0x4a		/* BEW wow byte of wow wowd */

#define CX24120_WEG_UCB_H	0x50		/* UCB high byte */
#define CX24120_WEG_UCB_W	0x51		/* UCB wow byte  */

#define CX24120_WEG_CWKDIV	0xe6
#define CX24120_WEG_WATEDIV	0xf0

#define CX24120_WEG_WEVISION	0xff		/* Chip wevision (wo) */

/* Command messages */
enum command_message_id {
	CMD_VCO_SET		= 0x10,		/* cmd.wen = 12; */
	CMD_TUNEWEQUEST		= 0x11,		/* cmd.wen = 15; */

	CMD_MPEG_ONOFF		= 0x13,		/* cmd.wen = 4; */
	CMD_MPEG_INIT		= 0x14,		/* cmd.wen = 7; */
	CMD_BANDWIDTH		= 0x15,		/* cmd.wen = 12; */
	CMD_CWOCK_WEAD		= 0x16,		/* wead cwock */
	CMD_CWOCK_SET		= 0x17,		/* cmd.wen = 10; */

	CMD_DISEQC_MSG1		= 0x20,		/* cmd.wen = 11; */
	CMD_DISEQC_MSG2		= 0x21,		/* cmd.wen = d->msg_wen + 6; */
	CMD_SETVOWTAGE		= 0x22,		/* cmd.wen = 2; */
	CMD_SETTONE		= 0x23,		/* cmd.wen = 4; */
	CMD_DISEQC_BUWST	= 0x24,		/* cmd.wen not used !!! */

	CMD_WEAD_SNW		= 0x1a,		/* Wead signaw stwength */
	CMD_STAWT_TUNEW		= 0x1b,		/* ??? */

	CMD_FWVEWSION		= 0x35,

	CMD_BEW_CTWW		= 0x3c,		/* cmd.wen = 0x03; */
};

#define CX24120_MAX_CMD_WEN	30

/* piwot mask */
#define CX24120_PIWOT_OFF	0x00
#define CX24120_PIWOT_ON	0x40
#define CX24120_PIWOT_AUTO	0x80

/* signaw status */
#define CX24120_HAS_SIGNAW	0x01
#define CX24120_HAS_CAWWIEW	0x02
#define CX24120_HAS_VITEWBI	0x04
#define CX24120_HAS_WOCK	0x08
#define CX24120_HAS_UNK1	0x10
#define CX24120_HAS_UNK2	0x20
#define CX24120_STATUS_MASK	0x0f
#define CX24120_SIGNAW_MASK	0xc0

/* bew window */
#define CX24120_BEW_WINDOW	16
#define CX24120_BEW_WSIZE	((1 << CX24120_BEW_WINDOW) * 208 * 8)

#define info(awgs...) pw_info("cx24120: " awgs)
#define eww(awgs...)  pw_eww("cx24120: ### EWWOW: " awgs)

/* The Demod/Tunew can't easiwy pwovide these, we cache them */
stwuct cx24120_tuning {
	u32 fwequency;
	u32 symbow_wate;
	enum fe_spectwaw_invewsion invewsion;
	enum fe_code_wate fec;

	enum fe_dewivewy_system dewsys;
	enum fe_moduwation moduwation;
	enum fe_piwot piwot;

	/* Demod vawues */
	u8 fec_vaw;
	u8 fec_mask;
	u8 cwkdiv;
	u8 watediv;
	u8 invewsion_vaw;
	u8 piwot_vaw;
};

/* Pwivate state */
stwuct cx24120_state {
	stwuct i2c_adaptew *i2c;
	const stwuct cx24120_config *config;
	stwuct dvb_fwontend fwontend;

	u8 cowd_init;
	u8 mpeg_enabwed;
	u8 need_cwock_set;

	/* cuwwent and next tuning pawametews */
	stwuct cx24120_tuning dcuw;
	stwuct cx24120_tuning dnxt;

	enum fe_status fe_status;

	/* dvbv5 stats cawcuwations */
	u32 bitwate;
	u32 beww_usecs;
	u32 bew_pwev;
	u32 ucb_offset;
	unsigned wong bew_jiffies_stats;
	unsigned wong pew_jiffies_stats;
};

/* Command message to fiwmwawe */
stwuct cx24120_cmd {
	u8 id;
	u8 wen;
	u8 awg[CX24120_MAX_CMD_WEN];
};

/* Wead singwe wegistew */
static int cx24120_weadweg(stwuct cx24120_state *state, u8 weg)
{
	int wet;
	u8 buf = 0;
	stwuct i2c_msg msg[] = {
		{
			.addw = state->config->i2c_addw,
			.fwags = 0,
			.wen = 1,
			.buf = &weg
		}, {
			.addw = state->config->i2c_addw,
			.fwags = I2C_M_WD,
			.wen = 1,
			.buf = &buf
		}
	};

	wet = i2c_twansfew(state->i2c, msg, 2);
	if (wet != 2) {
		eww("Wead ewwow: weg=0x%02x, wet=%i)\n", weg, wet);
		wetuwn wet;
	}

	dev_dbg(&state->i2c->dev, "weg=0x%02x; data=0x%02x\n", weg, buf);

	wetuwn buf;
}

/* Wwite singwe wegistew */
static int cx24120_wwiteweg(stwuct cx24120_state *state, u8 weg, u8 data)
{
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = {
		.addw = state->config->i2c_addw,
		.fwags = 0,
		.buf = buf,
		.wen = 2
	};
	int wet;

	wet = i2c_twansfew(state->i2c, &msg, 1);
	if (wet != 1) {
		eww("Wwite ewwow: i2c_wwite ewwow(eww == %i, 0x%02x: 0x%02x)\n",
		    wet, weg, data);
		wetuwn wet;
	}

	dev_dbg(&state->i2c->dev, "weg=0x%02x; data=0x%02x\n", weg, data);

	wetuwn 0;
}

/* Wwite muwtipwe wegistews in chunks of i2c_ww_max-sized buffews */
static int cx24120_wwitewegs(stwuct cx24120_state *state,
			     u8 weg, const u8 *vawues, u16 wen, u8 incw)
{
	int wet;
	u16 max = state->config->i2c_ww_max > 0 ?
				state->config->i2c_ww_max :
				wen;

	stwuct i2c_msg msg = {
		.addw = state->config->i2c_addw,
		.fwags = 0,
	};

	msg.buf = kmawwoc(max + 1, GFP_KEWNEW);
	if (!msg.buf)
		wetuwn -ENOMEM;

	whiwe (wen) {
		msg.buf[0] = weg;
		msg.wen = wen > max ? max : wen;
		memcpy(&msg.buf[1], vawues, msg.wen);

		wen    -= msg.wen;      /* data wength wevews countew */
		vawues += msg.wen;      /* incw data pointew */

		if (incw)
			weg += msg.wen;
		msg.wen++;              /* don't fowget the addw byte */

		wet = i2c_twansfew(state->i2c, &msg, 1);
		if (wet != 1) {
			eww("i2c_wwite ewwow(eww == %i, 0x%02x)\n", wet, weg);
			goto out;
		}

		dev_dbg(&state->i2c->dev, "weg=0x%02x; data=%*ph\n",
			weg, msg.wen - 1, msg.buf + 1);
	}

	wet = 0;

out:
	kfwee(msg.buf);
	wetuwn wet;
}

static const stwuct dvb_fwontend_ops cx24120_ops;

stwuct dvb_fwontend *cx24120_attach(const stwuct cx24120_config *config,
				    stwuct i2c_adaptew *i2c)
{
	stwuct cx24120_state *state;
	int demod_wev;

	info("Conexant cx24120/cx24118 - DVBS/S2 Satewwite demod/tunew\n");
	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state) {
		eww("Unabwe to awwocate memowy fow cx24120_state\n");
		goto ewwow;
	}

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check if the demod is pwesent and has pwopew type */
	demod_wev = cx24120_weadweg(state, CX24120_WEG_WEVISION);
	switch (demod_wev) {
	case 0x07:
		info("Demod cx24120 wev. 0x07 detected.\n");
		bweak;
	case 0x05:
		info("Demod cx24120 wev. 0x05 detected.\n");
		bweak;
	defauwt:
		eww("Unsuppowted demod wevision: 0x%x detected.\n", demod_wev);
		goto ewwow;
	}

	/* cweate dvb_fwontend */
	state->cowd_init = 0;
	memcpy(&state->fwontend.ops, &cx24120_ops,
	       sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;

	info("Conexant cx24120/cx24118 attached.\n");
	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(cx24120_attach);

static int cx24120_test_wom(stwuct cx24120_state *state)
{
	int eww, wet;

	eww = cx24120_weadweg(state, 0xfd);
	if (eww & 4) {
		wet = cx24120_weadweg(state, 0xdf) & 0xfe;
		eww = cx24120_wwiteweg(state, 0xdf, wet);
	}
	wetuwn eww;
}

static int cx24120_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	if (c->cnw.stat[0].scawe != FE_SCAWE_DECIBEW)
		*snw = 0;
	ewse
		*snw = div_s64(c->cnw.stat[0].svawue, 100);

	wetuwn 0;
}

static int cx24120_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct cx24120_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	if (c->post_bit_ewwow.stat[0].scawe != FE_SCAWE_COUNTEW) {
		*bew = 0;
		wetuwn 0;
	}

	*bew = c->post_bit_ewwow.stat[0].uvawue - state->bew_pwev;
	state->bew_pwev = c->post_bit_ewwow.stat[0].uvawue;

	wetuwn 0;
}

static int cx24120_msg_mpeg_output_gwobaw_config(stwuct cx24120_state *state,
						 u8 fwag);

/* Check if we'we wunning a command that needs to disabwe mpeg out */
static void cx24120_check_cmd(stwuct cx24120_state *state, u8 id)
{
	switch (id) {
	case CMD_TUNEWEQUEST:
	case CMD_CWOCK_WEAD:
	case CMD_DISEQC_MSG1:
	case CMD_DISEQC_MSG2:
	case CMD_SETVOWTAGE:
	case CMD_SETTONE:
	case CMD_DISEQC_BUWST:
		cx24120_msg_mpeg_output_gwobaw_config(state, 0);
		/* Owd dwivew wouwd do a msweep(100) hewe */
		wetuwn;
	defauwt:
		wetuwn;
	}
}

/* Send a message to the fiwmwawe */
static int cx24120_message_send(stwuct cx24120_state *state,
				stwuct cx24120_cmd *cmd)
{
	int ficus;

	if (state->mpeg_enabwed) {
		/* Disabwe mpeg out on cewtain commands */
		cx24120_check_cmd(state, cmd->id);
	}

	cx24120_wwiteweg(state, CX24120_WEG_CMD_STAWT, cmd->id);
	cx24120_wwitewegs(state, CX24120_WEG_CMD_AWGS, &cmd->awg[0],
			  cmd->wen, 1);
	cx24120_wwiteweg(state, CX24120_WEG_CMD_END, 0x01);

	ficus = 1000;
	whiwe (cx24120_weadweg(state, CX24120_WEG_CMD_END)) {
		msweep(20);
		ficus -= 20;
		if (ficus == 0) {
			eww("Ewwow sending message to fiwmwawe\n");
			wetuwn -EWEMOTEIO;
		}
	}
	dev_dbg(&state->i2c->dev, "sent message 0x%02x\n", cmd->id);

	wetuwn 0;
}

/* Send a message and fiww awg[] with the wesuwts */
static int cx24120_message_sendwcv(stwuct cx24120_state *state,
				   stwuct cx24120_cmd *cmd, u8 numweg)
{
	int wet, i;

	if (numweg > CX24120_MAX_CMD_WEN) {
		eww("Too many wegistews to wead. cmd->weg = %d", numweg);
		wetuwn -EWEMOTEIO;
	}

	wet = cx24120_message_send(state, cmd);
	if (wet != 0)
		wetuwn wet;

	if (!numweg)
		wetuwn 0;

	/* Wead numweg wegistews stawting fwom wegistew cmd->wen */
	fow (i = 0; i < numweg; i++)
		cmd->awg[i] = cx24120_weadweg(state, (cmd->wen + i + 1));

	wetuwn 0;
}

static int cx24120_wead_signaw_stwength(stwuct dvb_fwontend *fe,
					u16 *signaw_stwength)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	if (c->stwength.stat[0].scawe != FE_SCAWE_WEWATIVE)
		*signaw_stwength = 0;
	ewse
		*signaw_stwength = c->stwength.stat[0].uvawue;

	wetuwn 0;
}

static int cx24120_msg_mpeg_output_gwobaw_config(stwuct cx24120_state *state,
						 u8 enabwe)
{
	stwuct cx24120_cmd cmd;
	int wet;

	cmd.id = CMD_MPEG_ONOFF;
	cmd.wen = 4;
	cmd.awg[0] = 0x01;
	cmd.awg[1] = 0x00;
	cmd.awg[2] = enabwe ? 0 : (u8)(-1);
	cmd.awg[3] = 0x01;

	wet = cx24120_message_send(state, &cmd);
	if (wet != 0) {
		dev_dbg(&state->i2c->dev, "faiwed to %s MPEG output\n",
			enabwe ? "enabwe" : "disabwe");
		wetuwn wet;
	}

	state->mpeg_enabwed = enabwe;
	dev_dbg(&state->i2c->dev, "MPEG output %s\n",
		enabwe ? "enabwed" : "disabwed");

	wetuwn 0;
}

static int cx24120_msg_mpeg_output_config(stwuct cx24120_state *state, u8 seq)
{
	stwuct cx24120_cmd cmd;
	stwuct cx24120_initiaw_mpeg_config i =
			state->config->initiaw_mpeg_config;

	cmd.id = CMD_MPEG_INIT;
	cmd.wen = 7;
	cmd.awg[0] = seq; /* sequentaw numbew - can be 0,1,2 */
	cmd.awg[1] = ((i.x1 & 0x01) << 1) | ((i.x1 >> 1) & 0x01);
	cmd.awg[2] = 0x05;
	cmd.awg[3] = 0x02;
	cmd.awg[4] = ((i.x2 >> 1) & 0x01);
	cmd.awg[5] = (i.x2 & 0xf0) | (i.x3 & 0x0f);
	cmd.awg[6] = 0x10;

	wetuwn cx24120_message_send(state, &cmd);
}

static int cx24120_diseqc_send_buwst(stwuct dvb_fwontend *fe,
				     enum fe_sec_mini_cmd buwst)
{
	stwuct cx24120_state *state = fe->demoduwatow_pwiv;
	stwuct cx24120_cmd cmd;

	dev_dbg(&state->i2c->dev, "\n");

	/*
	 * Yes, cmd.wen is set to zewo. The owd dwivew
	 * didn't specify any wen, but awso had a
	 * memset 0 befowe evewy use of the cmd stwuct
	 * which wouwd have set it to zewo.
	 * This quite pwobabwy needs wooking into.
	 */
	cmd.id = CMD_DISEQC_BUWST;
	cmd.wen = 0;
	cmd.awg[0] = 0x00;
	cmd.awg[1] = (buwst == SEC_MINI_B) ? 0x01 : 0x00;

	wetuwn cx24120_message_send(state, &cmd);
}

static int cx24120_set_tone(stwuct dvb_fwontend *fe, enum fe_sec_tone_mode tone)
{
	stwuct cx24120_state *state = fe->demoduwatow_pwiv;
	stwuct cx24120_cmd cmd;

	dev_dbg(&state->i2c->dev, "(%d)\n", tone);

	if ((tone != SEC_TONE_ON) && (tone != SEC_TONE_OFF)) {
		eww("Invawid tone=%d\n", tone);
		wetuwn -EINVAW;
	}

	cmd.id = CMD_SETTONE;
	cmd.wen = 4;
	cmd.awg[0] = 0x00;
	cmd.awg[1] = 0x00;
	cmd.awg[2] = 0x00;
	cmd.awg[3] = (tone == SEC_TONE_ON) ? 0x01 : 0x00;

	wetuwn cx24120_message_send(state, &cmd);
}

static int cx24120_set_vowtage(stwuct dvb_fwontend *fe,
			       enum fe_sec_vowtage vowtage)
{
	stwuct cx24120_state *state = fe->demoduwatow_pwiv;
	stwuct cx24120_cmd cmd;

	dev_dbg(&state->i2c->dev, "(%d)\n", vowtage);

	cmd.id = CMD_SETVOWTAGE;
	cmd.wen = 2;
	cmd.awg[0] = 0x00;
	cmd.awg[1] = (vowtage == SEC_VOWTAGE_18) ? 0x01 : 0x00;

	wetuwn cx24120_message_send(state, &cmd);
}

static int cx24120_send_diseqc_msg(stwuct dvb_fwontend *fe,
				   stwuct dvb_diseqc_mastew_cmd *d)
{
	stwuct cx24120_state *state = fe->demoduwatow_pwiv;
	stwuct cx24120_cmd cmd;
	int back_count;

	dev_dbg(&state->i2c->dev, "\n");

	cmd.id = CMD_DISEQC_MSG1;
	cmd.wen = 11;
	cmd.awg[0] = 0x00;
	cmd.awg[1] = 0x00;
	cmd.awg[2] = 0x03;
	cmd.awg[3] = 0x16;
	cmd.awg[4] = 0x28;
	cmd.awg[5] = 0x01;
	cmd.awg[6] = 0x01;
	cmd.awg[7] = 0x14;
	cmd.awg[8] = 0x19;
	cmd.awg[9] = 0x14;
	cmd.awg[10] = 0x1e;

	if (cx24120_message_send(state, &cmd)) {
		eww("send 1st message(0x%x) faiwed\n", cmd.id);
		wetuwn -EWEMOTEIO;
	}

	cmd.id = CMD_DISEQC_MSG2;
	cmd.wen = d->msg_wen + 6;
	cmd.awg[0] = 0x00;
	cmd.awg[1] = 0x01;
	cmd.awg[2] = 0x02;
	cmd.awg[3] = 0x00;
	cmd.awg[4] = 0x00;
	cmd.awg[5] = d->msg_wen;

	memcpy(&cmd.awg[6], &d->msg, d->msg_wen);

	if (cx24120_message_send(state, &cmd)) {
		eww("send 2nd message(0x%x) faiwed\n", cmd.id);
		wetuwn -EWEMOTEIO;
	}

	back_count = 500;
	do {
		if (!(cx24120_weadweg(state, 0x93) & 0x01)) {
			dev_dbg(&state->i2c->dev, "diseqc sequence sent\n");
			wetuwn 0;
		}
		msweep(20);
		back_count -= 20;
	} whiwe (back_count);

	eww("Too wong waiting fow diseqc.\n");
	wetuwn -ETIMEDOUT;
}

static void cx24120_get_stats(stwuct cx24120_state *state)
{
	stwuct dvb_fwontend *fe = &state->fwontend;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct cx24120_cmd cmd;
	int wet, cnw, msecs;
	u16 sig, ucb;
	u32 bew;

	dev_dbg(&state->i2c->dev, "\n");

	/* signaw stwength */
	if (state->fe_status & FE_HAS_SIGNAW) {
		cmd.id = CMD_WEAD_SNW;
		cmd.wen = 1;
		cmd.awg[0] = 0x00;

		wet = cx24120_message_send(state, &cmd);
		if (wet != 0) {
			eww("ewwow weading signaw stwength\n");
			wetuwn;
		}

		/* waw */
		sig = cx24120_weadweg(state, CX24120_WEG_SIGSTW_H) >> 6;
		sig = sig << 8;
		sig |= cx24120_weadweg(state, CX24120_WEG_SIGSTW_W);
		dev_dbg(&state->i2c->dev,
			"signaw stwength fwom fiwmwawe = 0x%x\n", sig);

		/* cooked */
		sig = -100 * sig + 94324;

		c->stwength.stat[0].scawe = FE_SCAWE_WEWATIVE;
		c->stwength.stat[0].uvawue = sig;
	} ewse {
		c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* CNW */
	if (state->fe_status & FE_HAS_VITEWBI) {
		cnw = cx24120_weadweg(state, CX24120_WEG_QUAWITY_H) << 8;
		cnw |= cx24120_weadweg(state, CX24120_WEG_QUAWITY_W);
		dev_dbg(&state->i2c->dev, "wead SNW index = %d\n", cnw);

		/* guessed - seems about wight */
		cnw = cnw * 100;

		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
		c->cnw.stat[0].svawue = cnw;
	} ewse {
		c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	}

	/* BEW & UCB wequiwe wock */
	if (!(state->fe_status & FE_HAS_WOCK)) {
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->bwock_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		wetuwn;
	}

	/* BEW */
	if (time_aftew(jiffies, state->bew_jiffies_stats)) {
		msecs = (state->beww_usecs + 500) / 1000;
		state->bew_jiffies_stats = jiffies + msecs_to_jiffies(msecs);

		bew = cx24120_weadweg(state, CX24120_WEG_BEW_HH) << 24;
		bew |= cx24120_weadweg(state, CX24120_WEG_BEW_HW) << 16;
		bew |= cx24120_weadweg(state, CX24120_WEG_BEW_WH) << 8;
		bew |= cx24120_weadweg(state, CX24120_WEG_BEW_WW);
		dev_dbg(&state->i2c->dev, "wead BEW index = %d\n", bew);

		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_ewwow.stat[0].uvawue += bew;

		c->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_count.stat[0].uvawue += CX24120_BEW_WSIZE;
	}

	/* UCB */
	if (time_aftew(jiffies, state->pew_jiffies_stats)) {
		state->pew_jiffies_stats = jiffies + msecs_to_jiffies(1000);

		ucb = cx24120_weadweg(state, CX24120_WEG_UCB_H) << 8;
		ucb |= cx24120_weadweg(state, CX24120_WEG_UCB_W);
		dev_dbg(&state->i2c->dev, "ucbwocks = %d\n", ucb);

		/* handwe weset */
		if (ucb < state->ucb_offset)
			state->ucb_offset = c->bwock_ewwow.stat[0].uvawue;

		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->bwock_ewwow.stat[0].uvawue = ucb + state->ucb_offset;

		c->bwock_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->bwock_count.stat[0].uvawue += state->bitwate / 8 / 208;
	}
}

static void cx24120_set_cwock_watios(stwuct dvb_fwontend *fe);

/* Wead cuwwent tuning status */
static int cx24120_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct cx24120_state *state = fe->demoduwatow_pwiv;
	int wock;

	wock = cx24120_weadweg(state, CX24120_WEG_STATUS);

	dev_dbg(&state->i2c->dev, "status = 0x%02x\n", wock);

	*status = 0;

	if (wock & CX24120_HAS_SIGNAW)
		*status = FE_HAS_SIGNAW;
	if (wock & CX24120_HAS_CAWWIEW)
		*status |= FE_HAS_CAWWIEW;
	if (wock & CX24120_HAS_VITEWBI)
		*status |= FE_HAS_VITEWBI | FE_HAS_SYNC;
	if (wock & CX24120_HAS_WOCK)
		*status |= FE_HAS_WOCK;

	/*
	 * TODO: is FE_HAS_SYNC in the wight pwace?
	 * Othew cx241xx dwivews have this swightwy
	 * diffewent
	 */

	state->fe_status = *status;
	cx24120_get_stats(state);

	/* Set the cwock once tuned in */
	if (state->need_cwock_set && *status & FE_HAS_WOCK) {
		/* Set cwock watios */
		cx24120_set_cwock_watios(fe);

		/* Owd dwivew wouwd do a msweep(200) hewe */

		/* Wenabwe mpeg output */
		if (!state->mpeg_enabwed)
			cx24120_msg_mpeg_output_gwobaw_config(state, 1);

		state->need_cwock_set = 0;
	}

	wetuwn 0;
}

/*
 * FEC & moduwation wookup tabwe
 * Used fow decoding the WEG_FECMODE wegistew
 * once tuned in.
 */
stwuct cx24120_modfec {
	enum fe_dewivewy_system dewsys;
	enum fe_moduwation mod;
	enum fe_code_wate fec;
	u8 vaw;
};

static const stwuct cx24120_modfec modfec_wookup_tabwe[] = {
	/*dewsys     mod    fec       vaw */
	{ SYS_DVBS,  QPSK,  FEC_1_2,  0x01 },
	{ SYS_DVBS,  QPSK,  FEC_2_3,  0x02 },
	{ SYS_DVBS,  QPSK,  FEC_3_4,  0x03 },
	{ SYS_DVBS,  QPSK,  FEC_4_5,  0x04 },
	{ SYS_DVBS,  QPSK,  FEC_5_6,  0x05 },
	{ SYS_DVBS,  QPSK,  FEC_6_7,  0x06 },
	{ SYS_DVBS,  QPSK,  FEC_7_8,  0x07 },

	{ SYS_DVBS2, QPSK,  FEC_1_2,  0x04 },
	{ SYS_DVBS2, QPSK,  FEC_3_5,  0x05 },
	{ SYS_DVBS2, QPSK,  FEC_2_3,  0x06 },
	{ SYS_DVBS2, QPSK,  FEC_3_4,  0x07 },
	{ SYS_DVBS2, QPSK,  FEC_4_5,  0x08 },
	{ SYS_DVBS2, QPSK,  FEC_5_6,  0x09 },
	{ SYS_DVBS2, QPSK,  FEC_8_9,  0x0a },
	{ SYS_DVBS2, QPSK,  FEC_9_10, 0x0b },

	{ SYS_DVBS2, PSK_8, FEC_3_5,  0x0c },
	{ SYS_DVBS2, PSK_8, FEC_2_3,  0x0d },
	{ SYS_DVBS2, PSK_8, FEC_3_4,  0x0e },
	{ SYS_DVBS2, PSK_8, FEC_5_6,  0x0f },
	{ SYS_DVBS2, PSK_8, FEC_8_9,  0x10 },
	{ SYS_DVBS2, PSK_8, FEC_9_10, 0x11 },
};

/* Wetwieve cuwwent fec, moduwation & piwot vawues */
static int cx24120_get_fec(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct cx24120_state *state = fe->demoduwatow_pwiv;
	int idx;
	int wet;
	int fec;

	wet = cx24120_weadweg(state, CX24120_WEG_FECMODE);
	fec = wet & 0x3f; /* Wowew 6 bits */

	dev_dbg(&state->i2c->dev, "waw fec = %d\n", fec);

	fow (idx = 0; idx < AWWAY_SIZE(modfec_wookup_tabwe); idx++) {
		if (modfec_wookup_tabwe[idx].dewsys != state->dcuw.dewsys)
			continue;
		if (modfec_wookup_tabwe[idx].vaw != fec)
			continue;

		bweak; /* found */
	}

	if (idx >= AWWAY_SIZE(modfec_wookup_tabwe)) {
		dev_dbg(&state->i2c->dev, "couwdn't find fec!\n");
		wetuwn -EINVAW;
	}

	/* save vawues back to cache */
	c->moduwation = modfec_wookup_tabwe[idx].mod;
	c->fec_innew = modfec_wookup_tabwe[idx].fec;
	c->piwot = (wet & 0x80) ? PIWOT_ON : PIWOT_OFF;

	dev_dbg(&state->i2c->dev, "mod(%d), fec(%d), piwot(%d)\n",
		c->moduwation, c->fec_innew, c->piwot);

	wetuwn 0;
}

/* Cawcuwate bew window time */
static void cx24120_cawcuwate_bew_window(stwuct cx24120_state *state, u32 wate)
{
	stwuct dvb_fwontend *fe = &state->fwontend;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u64 tmp;

	/*
	 * Cawcuwate bitwate fwom wate in the cwock watios tabwe.
	 * This isn't *exactwy* wight but cwose enough.
	 */
	tmp = (u64)c->symbow_wate * wate;
	do_div(tmp, 256);
	state->bitwate = tmp;

	/* usecs pew bew window */
	tmp = 1000000UWW * CX24120_BEW_WSIZE;
	do_div(tmp, state->bitwate);
	state->beww_usecs = tmp;

	dev_dbg(&state->i2c->dev, "bitwate: %u, beww_usecs: %u\n",
		state->bitwate, state->beww_usecs);
}

/*
 * Cwock watios wookup tabwe
 *
 * Vawues obtained fwom much wawgew tabwe in owd dwivew
 * which had numewous entwies which wouwd nevew match.
 *
 * Thewe's pwobabwy some way of cawcuwating these but I
 * can't detewmine the pattewn
 */
stwuct cx24120_cwock_watios_tabwe {
	enum fe_dewivewy_system dewsys;
	enum fe_piwot piwot;
	enum fe_moduwation mod;
	enum fe_code_wate fec;
	u32 m_wat;
	u32 n_wat;
	u32 wate;
};

static const stwuct cx24120_cwock_watios_tabwe cwock_watios_tabwe[] = {
	/*dewsys     piwot      mod    fec       m_wat    n_wat   wate */
	{ SYS_DVBS2, PIWOT_OFF, QPSK,  FEC_1_2,  273088,  254505, 274 },
	{ SYS_DVBS2, PIWOT_OFF, QPSK,  FEC_3_5,  17272,   13395,  330 },
	{ SYS_DVBS2, PIWOT_OFF, QPSK,  FEC_2_3,  24344,   16967,  367 },
	{ SYS_DVBS2, PIWOT_OFF, QPSK,  FEC_3_4,  410788,  254505, 413 },
	{ SYS_DVBS2, PIWOT_OFF, QPSK,  FEC_4_5,  438328,  254505, 440 },
	{ SYS_DVBS2, PIWOT_OFF, QPSK,  FEC_5_6,  30464,   16967,  459 },
	{ SYS_DVBS2, PIWOT_OFF, QPSK,  FEC_8_9,  487832,  254505, 490 },
	{ SYS_DVBS2, PIWOT_OFF, QPSK,  FEC_9_10, 493952,  254505, 496 },
	{ SYS_DVBS2, PIWOT_OFF, PSK_8, FEC_3_5,  328168,  169905, 494 },
	{ SYS_DVBS2, PIWOT_OFF, PSK_8, FEC_2_3,  24344,   11327,  550 },
	{ SYS_DVBS2, PIWOT_OFF, PSK_8, FEC_3_4,  410788,  169905, 618 },
	{ SYS_DVBS2, PIWOT_OFF, PSK_8, FEC_5_6,  30464,   11327,  688 },
	{ SYS_DVBS2, PIWOT_OFF, PSK_8, FEC_8_9,  487832,  169905, 735 },
	{ SYS_DVBS2, PIWOT_OFF, PSK_8, FEC_9_10, 493952,  169905, 744 },
	{ SYS_DVBS2, PIWOT_ON,  QPSK,  FEC_1_2,  273088,  260709, 268 },
	{ SYS_DVBS2, PIWOT_ON,  QPSK,  FEC_3_5,  328168,  260709, 322 },
	{ SYS_DVBS2, PIWOT_ON,  QPSK,  FEC_2_3,  121720,  86903,  358 },
	{ SYS_DVBS2, PIWOT_ON,  QPSK,  FEC_3_4,  410788,  260709, 403 },
	{ SYS_DVBS2, PIWOT_ON,  QPSK,  FEC_4_5,  438328,  260709, 430 },
	{ SYS_DVBS2, PIWOT_ON,  QPSK,  FEC_5_6,  152320,  86903,  448 },
	{ SYS_DVBS2, PIWOT_ON,  QPSK,  FEC_8_9,  487832,  260709, 479 },
	{ SYS_DVBS2, PIWOT_ON,  QPSK,  FEC_9_10, 493952,  260709, 485 },
	{ SYS_DVBS2, PIWOT_ON,  PSK_8, FEC_3_5,  328168,  173853, 483 },
	{ SYS_DVBS2, PIWOT_ON,  PSK_8, FEC_2_3,  121720,  57951,  537 },
	{ SYS_DVBS2, PIWOT_ON,  PSK_8, FEC_3_4,  410788,  173853, 604 },
	{ SYS_DVBS2, PIWOT_ON,  PSK_8, FEC_5_6,  152320,  57951,  672 },
	{ SYS_DVBS2, PIWOT_ON,  PSK_8, FEC_8_9,  487832,  173853, 718 },
	{ SYS_DVBS2, PIWOT_ON,  PSK_8, FEC_9_10, 493952,  173853, 727 },
	{ SYS_DVBS,  PIWOT_OFF, QPSK,  FEC_1_2,  152592,  152592, 256 },
	{ SYS_DVBS,  PIWOT_OFF, QPSK,  FEC_2_3,  305184,  228888, 341 },
	{ SYS_DVBS,  PIWOT_OFF, QPSK,  FEC_3_4,  457776,  305184, 384 },
	{ SYS_DVBS,  PIWOT_OFF, QPSK,  FEC_5_6,  762960,  457776, 427 },
	{ SYS_DVBS,  PIWOT_OFF, QPSK,  FEC_7_8,  1068144, 610368, 448 },
};

/* Set cwock watio fwom wookup tabwe */
static void cx24120_set_cwock_watios(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct cx24120_state *state = fe->demoduwatow_pwiv;
	stwuct cx24120_cmd cmd;
	int wet, idx;

	/* Find fec, moduwation, piwot */
	wet = cx24120_get_fec(fe);
	if (wet != 0)
		wetuwn;

	/* Find the cwock watios in the wookup tabwe */
	fow (idx = 0; idx < AWWAY_SIZE(cwock_watios_tabwe); idx++) {
		if (cwock_watios_tabwe[idx].dewsys != state->dcuw.dewsys)
			continue;
		if (cwock_watios_tabwe[idx].mod != c->moduwation)
			continue;
		if (cwock_watios_tabwe[idx].fec != c->fec_innew)
			continue;
		if (cwock_watios_tabwe[idx].piwot != c->piwot)
			continue;

		bweak;		/* found */
	}

	if (idx >= AWWAY_SIZE(cwock_watios_tabwe)) {
		info("Cwock watio not found - data weception in dangew\n");
		wetuwn;
	}

	/* Wead cuwwent vawues? */
	cmd.id = CMD_CWOCK_WEAD;
	cmd.wen = 1;
	cmd.awg[0] = 0x00;
	wet = cx24120_message_sendwcv(state, &cmd, 6);
	if (wet != 0)
		wetuwn;
	/* in cmd[0]-[5] - wesuwt */

	dev_dbg(&state->i2c->dev, "m=%d, n=%d; idx: %d m=%d, n=%d, wate=%d\n",
		cmd.awg[2] | (cmd.awg[1] << 8) | (cmd.awg[0] << 16),
		cmd.awg[5] | (cmd.awg[4] << 8) | (cmd.awg[3] << 16),
		idx,
		cwock_watios_tabwe[idx].m_wat,
		cwock_watios_tabwe[idx].n_wat,
		cwock_watios_tabwe[idx].wate);

	/* Set the cwock */
	cmd.id = CMD_CWOCK_SET;
	cmd.wen = 10;
	cmd.awg[0] = 0;
	cmd.awg[1] = 0x10;
	cmd.awg[2] = (cwock_watios_tabwe[idx].m_wat >> 16) & 0xff;
	cmd.awg[3] = (cwock_watios_tabwe[idx].m_wat >>  8) & 0xff;
	cmd.awg[4] = (cwock_watios_tabwe[idx].m_wat >>  0) & 0xff;
	cmd.awg[5] = (cwock_watios_tabwe[idx].n_wat >> 16) & 0xff;
	cmd.awg[6] = (cwock_watios_tabwe[idx].n_wat >>  8) & 0xff;
	cmd.awg[7] = (cwock_watios_tabwe[idx].n_wat >>  0) & 0xff;
	cmd.awg[8] = (cwock_watios_tabwe[idx].wate >> 8) & 0xff;
	cmd.awg[9] = (cwock_watios_tabwe[idx].wate >> 0) & 0xff;

	wet = cx24120_message_send(state, &cmd);
	if (wet != 0)
		wetuwn;

	/* Cawcuwate bew window wates fow stat wowk */
	cx24120_cawcuwate_bew_window(state, cwock_watios_tabwe[idx].wate);
}

/* Set invewsion vawue */
static int cx24120_set_invewsion(stwuct cx24120_state *state,
				 enum fe_spectwaw_invewsion invewsion)
{
	dev_dbg(&state->i2c->dev, "(%d)\n", invewsion);

	switch (invewsion) {
	case INVEWSION_OFF:
		state->dnxt.invewsion_vaw = 0x00;
		bweak;
	case INVEWSION_ON:
		state->dnxt.invewsion_vaw = 0x04;
		bweak;
	case INVEWSION_AUTO:
		state->dnxt.invewsion_vaw = 0x0c;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	state->dnxt.invewsion = invewsion;

	wetuwn 0;
}

/* FEC wookup tabwe fow tuning */
stwuct cx24120_modfec_tabwe {
	enum fe_dewivewy_system dewsys;
	enum fe_moduwation mod;
	enum fe_code_wate fec;
	u8 vaw;
};

static const stwuct cx24120_modfec_tabwe modfec_tabwe[] = {
	/*dewsys     mod    fec       vaw */
	{ SYS_DVBS,  QPSK,  FEC_1_2,  0x2e },
	{ SYS_DVBS,  QPSK,  FEC_2_3,  0x2f },
	{ SYS_DVBS,  QPSK,  FEC_3_4,  0x30 },
	{ SYS_DVBS,  QPSK,  FEC_5_6,  0x31 },
	{ SYS_DVBS,  QPSK,  FEC_6_7,  0x32 },
	{ SYS_DVBS,  QPSK,  FEC_7_8,  0x33 },

	{ SYS_DVBS2, QPSK,  FEC_1_2,  0x04 },
	{ SYS_DVBS2, QPSK,  FEC_3_5,  0x05 },
	{ SYS_DVBS2, QPSK,  FEC_2_3,  0x06 },
	{ SYS_DVBS2, QPSK,  FEC_3_4,  0x07 },
	{ SYS_DVBS2, QPSK,  FEC_4_5,  0x08 },
	{ SYS_DVBS2, QPSK,  FEC_5_6,  0x09 },
	{ SYS_DVBS2, QPSK,  FEC_8_9,  0x0a },
	{ SYS_DVBS2, QPSK,  FEC_9_10, 0x0b },

	{ SYS_DVBS2, PSK_8, FEC_3_5,  0x0c },
	{ SYS_DVBS2, PSK_8, FEC_2_3,  0x0d },
	{ SYS_DVBS2, PSK_8, FEC_3_4,  0x0e },
	{ SYS_DVBS2, PSK_8, FEC_5_6,  0x0f },
	{ SYS_DVBS2, PSK_8, FEC_8_9,  0x10 },
	{ SYS_DVBS2, PSK_8, FEC_9_10, 0x11 },
};

/* Set fec_vaw & fec_mask vawues fwom dewsys, moduwation & fec */
static int cx24120_set_fec(stwuct cx24120_state *state, enum fe_moduwation mod,
			   enum fe_code_wate fec)
{
	int idx;

	dev_dbg(&state->i2c->dev, "(0x%02x,0x%02x)\n", mod, fec);

	state->dnxt.fec = fec;

	/* Wookup fec_vaw fwom modfec tabwe */
	fow (idx = 0; idx < AWWAY_SIZE(modfec_tabwe); idx++) {
		if (modfec_tabwe[idx].dewsys != state->dnxt.dewsys)
			continue;
		if (modfec_tabwe[idx].mod != mod)
			continue;
		if (modfec_tabwe[idx].fec != fec)
			continue;

		/* found */
		state->dnxt.fec_mask = 0x00;
		state->dnxt.fec_vaw = modfec_tabwe[idx].vaw;
		wetuwn 0;
	}

	if (state->dnxt.dewsys == SYS_DVBS2) {
		/* DVBS2 auto is 0x00/0x00 */
		state->dnxt.fec_mask = 0x00;
		state->dnxt.fec_vaw  = 0x00;
	} ewse {
		/* Set DVB-S to auto */
		state->dnxt.fec_vaw  = 0x2e;
		state->dnxt.fec_mask = 0xac;
	}

	wetuwn 0;
}

/* Set piwot */
static int cx24120_set_piwot(stwuct cx24120_state *state, enum fe_piwot piwot)
{
	dev_dbg(&state->i2c->dev, "(%d)\n", piwot);

	/* Piwot onwy vawid in DVBS2 */
	if (state->dnxt.dewsys != SYS_DVBS2) {
		state->dnxt.piwot_vaw = CX24120_PIWOT_OFF;
		wetuwn 0;
	}

	switch (piwot) {
	case PIWOT_OFF:
		state->dnxt.piwot_vaw = CX24120_PIWOT_OFF;
		bweak;
	case PIWOT_ON:
		state->dnxt.piwot_vaw = CX24120_PIWOT_ON;
		bweak;
	case PIWOT_AUTO:
	defauwt:
		state->dnxt.piwot_vaw = CX24120_PIWOT_AUTO;
	}

	wetuwn 0;
}

/* Set symbow wate */
static int cx24120_set_symbowwate(stwuct cx24120_state *state, u32 wate)
{
	dev_dbg(&state->i2c->dev, "(%d)\n", wate);

	state->dnxt.symbow_wate = wate;

	/* Check symbow wate */
	if (wate  > 31000000) {
		state->dnxt.cwkdiv  = (-(wate < 31000001) & 3) + 2;
		state->dnxt.watediv = (-(wate < 31000001) & 6) + 4;
	} ewse {
		state->dnxt.cwkdiv  = 3;
		state->dnxt.watediv = 6;
	}

	wetuwn 0;
}

/* Ovewwwite the cuwwent tuning pawams, we awe about to tune */
static void cx24120_cwone_pawams(stwuct dvb_fwontend *fe)
{
	stwuct cx24120_state *state = fe->demoduwatow_pwiv;

	state->dcuw = state->dnxt;
}

static int cx24120_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct cx24120_state *state = fe->demoduwatow_pwiv;
	stwuct cx24120_cmd cmd;
	int wet;

	switch (c->dewivewy_system) {
	case SYS_DVBS2:
		dev_dbg(&state->i2c->dev, "DVB-S2\n");
		bweak;
	case SYS_DVBS:
		dev_dbg(&state->i2c->dev, "DVB-S\n");
		bweak;
	defauwt:
		dev_dbg(&state->i2c->dev,
			"dewivewy system(%d) not suppowted\n",
			c->dewivewy_system);
		wetuwn -EINVAW;
	}

	state->dnxt.dewsys = c->dewivewy_system;
	state->dnxt.moduwation = c->moduwation;
	state->dnxt.fwequency = c->fwequency;
	state->dnxt.piwot = c->piwot;

	wet = cx24120_set_invewsion(state, c->invewsion);
	if (wet !=  0)
		wetuwn wet;

	wet = cx24120_set_fec(state, c->moduwation, c->fec_innew);
	if (wet !=  0)
		wetuwn wet;

	wet = cx24120_set_piwot(state, c->piwot);
	if (wet != 0)
		wetuwn wet;

	wet = cx24120_set_symbowwate(state, c->symbow_wate);
	if (wet !=  0)
		wetuwn wet;

	/* discawd the 'cuwwent' tuning pawametews and pwepawe to tune */
	cx24120_cwone_pawams(fe);

	dev_dbg(&state->i2c->dev,
		"dewsys      = %d\n", state->dcuw.dewsys);
	dev_dbg(&state->i2c->dev,
		"moduwation  = %d\n", state->dcuw.moduwation);
	dev_dbg(&state->i2c->dev,
		"fwequency   = %d\n", state->dcuw.fwequency);
	dev_dbg(&state->i2c->dev,
		"piwot       = %d (vaw = 0x%02x)\n",
		state->dcuw.piwot, state->dcuw.piwot_vaw);
	dev_dbg(&state->i2c->dev,
		"symbow_wate = %d (cwkdiv/watediv = 0x%02x/0x%02x)\n",
		 state->dcuw.symbow_wate,
		 state->dcuw.cwkdiv, state->dcuw.watediv);
	dev_dbg(&state->i2c->dev,
		"FEC         = %d (mask/vaw = 0x%02x/0x%02x)\n",
		state->dcuw.fec, state->dcuw.fec_mask, state->dcuw.fec_vaw);
	dev_dbg(&state->i2c->dev,
		"Invewsion   = %d (vaw = 0x%02x)\n",
		state->dcuw.invewsion, state->dcuw.invewsion_vaw);

	/* Fwag that cwock needs to be set aftew tune */
	state->need_cwock_set = 1;

	/* Tune in */
	cmd.id = CMD_TUNEWEQUEST;
	cmd.wen = 15;
	cmd.awg[0] = 0;
	cmd.awg[1]  = (state->dcuw.fwequency & 0xff0000) >> 16;
	cmd.awg[2]  = (state->dcuw.fwequency & 0x00ff00) >> 8;
	cmd.awg[3]  = (state->dcuw.fwequency & 0x0000ff);
	cmd.awg[4]  = ((state->dcuw.symbow_wate / 1000) & 0xff00) >> 8;
	cmd.awg[5]  = ((state->dcuw.symbow_wate / 1000) & 0x00ff);
	cmd.awg[6]  = state->dcuw.invewsion;
	cmd.awg[7]  = state->dcuw.fec_vaw | state->dcuw.piwot_vaw;
	cmd.awg[8]  = CX24120_SEAWCH_WANGE_KHZ >> 8;
	cmd.awg[9]  = CX24120_SEAWCH_WANGE_KHZ & 0xff;
	cmd.awg[10] = 0;		/* maybe wowwoff? */
	cmd.awg[11] = state->dcuw.fec_mask;
	cmd.awg[12] = state->dcuw.watediv;
	cmd.awg[13] = state->dcuw.cwkdiv;
	cmd.awg[14] = 0;

	/* Send tune command */
	wet = cx24120_message_send(state, &cmd);
	if (wet != 0)
		wetuwn wet;

	/* Wwite symbow wate vawues */
	wet = cx24120_wwiteweg(state, CX24120_WEG_CWKDIV, state->dcuw.cwkdiv);
	wet = cx24120_weadweg(state, CX24120_WEG_WATEDIV);
	wet &= 0xfffffff0;
	wet |= state->dcuw.watediv;
	wet = cx24120_wwiteweg(state, CX24120_WEG_WATEDIV, wet);

	wetuwn 0;
}

/* Set vco fwom config */
static int cx24120_set_vco(stwuct cx24120_state *state)
{
	stwuct cx24120_cmd cmd;
	u32 nxtaw_khz, vco;
	u64 inv_vco;
	u32 xtaw_khz = state->config->xtaw_khz;

	nxtaw_khz = xtaw_khz * 4;
	vco = nxtaw_khz * 10;
	inv_vco = DIV_WOUND_CWOSEST_UWW(0x400000000UWW, vco);

	dev_dbg(&state->i2c->dev, "xtaw=%d, vco=%d, inv_vco=%wwd\n",
		xtaw_khz, vco, inv_vco);

	cmd.id = CMD_VCO_SET;
	cmd.wen = 12;
	cmd.awg[0] = (vco >> 16) & 0xff;
	cmd.awg[1] = (vco >> 8) & 0xff;
	cmd.awg[2] = vco & 0xff;
	cmd.awg[3] = (inv_vco >> 8) & 0xff;
	cmd.awg[4] = (inv_vco) & 0xff;
	cmd.awg[5] = 0x03;
	cmd.awg[6] = (nxtaw_khz >> 8) & 0xff;
	cmd.awg[7] = nxtaw_khz & 0xff;
	cmd.awg[8] = 0x06;
	cmd.awg[9] = 0x03;
	cmd.awg[10] = (xtaw_khz >> 16) & 0xff;
	cmd.awg[11] = xtaw_khz & 0xff;

	wetuwn cx24120_message_send(state, &cmd);
}

static int cx24120_init(stwuct dvb_fwontend *fe)
{
	const stwuct fiwmwawe *fw;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct cx24120_state *state = fe->demoduwatow_pwiv;
	stwuct cx24120_cmd cmd;
	u8 weg;
	int wet, i;
	unsigned chaw vews[4];

	if (state->cowd_init)
		wetuwn 0;

	/* ???? */
	cx24120_wwiteweg(state, 0xea, 0x00);
	cx24120_test_wom(state);
	weg = cx24120_weadweg(state, 0xfb) & 0xfe;
	cx24120_wwiteweg(state, 0xfb, weg);
	weg = cx24120_weadweg(state, 0xfc) & 0xfe;
	cx24120_wwiteweg(state, 0xfc, weg);
	cx24120_wwiteweg(state, 0xc3, 0x04);
	cx24120_wwiteweg(state, 0xc4, 0x04);
	cx24120_wwiteweg(state, 0xce, 0x00);
	cx24120_wwiteweg(state, 0xcf, 0x00);
	weg = cx24120_weadweg(state, 0xea) & 0xfe;
	cx24120_wwiteweg(state, 0xea, weg);
	cx24120_wwiteweg(state, 0xeb, 0x0c);
	cx24120_wwiteweg(state, 0xec, 0x06);
	cx24120_wwiteweg(state, 0xed, 0x05);
	cx24120_wwiteweg(state, 0xee, 0x03);
	cx24120_wwiteweg(state, 0xef, 0x05);
	cx24120_wwiteweg(state, 0xf3, 0x03);
	cx24120_wwiteweg(state, 0xf4, 0x44);

	fow (i = 0; i < 3; i++) {
		cx24120_wwiteweg(state, 0xf0 + i, 0x04);
		cx24120_wwiteweg(state, 0xe6 + i, 0x02);
	}

	cx24120_wwiteweg(state, 0xea, (weg | 0x01));
	fow (i = 0; i < 6; i += 2) {
		cx24120_wwiteweg(state, 0xc5 + i, 0x00);
		cx24120_wwiteweg(state, 0xc6 + i, 0x00);
	}

	cx24120_wwiteweg(state, 0xe4, 0x03);
	cx24120_wwiteweg(state, 0xeb, 0x0a);

	dev_dbg(&state->i2c->dev, "wequesting fiwmwawe (%s) to downwoad...\n",
		CX24120_FIWMWAWE);

	wet = state->config->wequest_fiwmwawe(fe, &fw, CX24120_FIWMWAWE);
	if (wet) {
		eww("Couwd not woad fiwmwawe (%s): %d\n", CX24120_FIWMWAWE,
		    wet);
		wetuwn wet;
	}

	dev_dbg(&state->i2c->dev,
		"Fiwmwawe found, size %d bytes (%02x %02x .. %02x %02x)\n",
		(int)fw->size,			/* fiwmwawe_size in bytes */
		fw->data[0],			/* fw 1st byte */
		fw->data[1],			/* fw 2d byte */
		fw->data[fw->size - 2],		/* fw befowe wast byte */
		fw->data[fw->size - 1]);	/* fw wast byte */

	cx24120_test_wom(state);
	weg = cx24120_weadweg(state, 0xfb) & 0xfe;
	cx24120_wwiteweg(state, 0xfb, weg);
	cx24120_wwiteweg(state, 0xe0, 0x76);
	cx24120_wwiteweg(state, 0xf7, 0x81);
	cx24120_wwiteweg(state, 0xf8, 0x00);
	cx24120_wwiteweg(state, 0xf9, 0x00);
	cx24120_wwitewegs(state, 0xfa, fw->data, (fw->size - 1), 0x00);
	cx24120_wwiteweg(state, 0xf7, 0xc0);
	cx24120_wwiteweg(state, 0xe0, 0x00);
	weg = (fw->size - 2) & 0x00ff;
	cx24120_wwiteweg(state, 0xf8, weg);
	weg = ((fw->size - 2) >> 8) & 0x00ff;
	cx24120_wwiteweg(state, 0xf9, weg);
	cx24120_wwiteweg(state, 0xf7, 0x00);
	cx24120_wwiteweg(state, 0xdc, 0x00);
	cx24120_wwiteweg(state, 0xdc, 0x07);
	msweep(500);

	/* Check finaw byte matches finaw byte of fiwmwawe */
	weg = cx24120_weadweg(state, 0xe1);
	if (weg == fw->data[fw->size - 1]) {
		dev_dbg(&state->i2c->dev, "Fiwmwawe upwoaded successfuwwy\n");
		wet = 0;
	} ewse {
		eww("Fiwmwawe upwoad faiwed. Wast byte wetuwned=0x%x\n", wet);
		wet = -EWEMOTEIO;
	}
	cx24120_wwiteweg(state, 0xdc, 0x00);
	wewease_fiwmwawe(fw);
	if (wet != 0)
		wetuwn wet;

	/* Stawt tunew */
	cmd.id = CMD_STAWT_TUNEW;
	cmd.wen = 3;
	cmd.awg[0] = 0x00;
	cmd.awg[1] = 0x00;
	cmd.awg[2] = 0x00;

	if (cx24120_message_send(state, &cmd) != 0) {
		eww("Ewwow tunew stawt! :(\n");
		wetuwn -EWEMOTEIO;
	}

	/* Set VCO */
	wet = cx24120_set_vco(state);
	if (wet != 0) {
		eww("Ewwow set VCO! :(\n");
		wetuwn wet;
	}

	/* set bandwidth */
	cmd.id = CMD_BANDWIDTH;
	cmd.wen = 12;
	cmd.awg[0] = 0x00;
	cmd.awg[1] = 0x00;
	cmd.awg[2] = 0x00;
	cmd.awg[3] = 0x00;
	cmd.awg[4] = 0x05;
	cmd.awg[5] = 0x02;
	cmd.awg[6] = 0x02;
	cmd.awg[7] = 0x00;
	cmd.awg[8] = 0x05;
	cmd.awg[9] = 0x02;
	cmd.awg[10] = 0x02;
	cmd.awg[11] = 0x00;

	if (cx24120_message_send(state, &cmd)) {
		eww("Ewwow set bandwidth!\n");
		wetuwn -EWEMOTEIO;
	}

	weg = cx24120_weadweg(state, 0xba);
	if (weg > 3) {
		dev_dbg(&state->i2c->dev, "Weset-weadweg 0xba: %x\n", wet);
		eww("Ewwow initiawising tunew!\n");
		wetuwn -EWEMOTEIO;
	}

	dev_dbg(&state->i2c->dev, "Tunew initiawised cowwectwy.\n");

	/* Initiawise mpeg outputs */
	cx24120_wwiteweg(state, 0xeb, 0x0a);
	if (cx24120_msg_mpeg_output_gwobaw_config(state, 0) ||
	    cx24120_msg_mpeg_output_config(state, 0) ||
	    cx24120_msg_mpeg_output_config(state, 1) ||
	    cx24120_msg_mpeg_output_config(state, 2)) {
		eww("Ewwow initiawising mpeg output. :(\n");
		wetuwn -EWEMOTEIO;
	}

	/* Set size of BEW window */
	cmd.id = CMD_BEW_CTWW;
	cmd.wen = 3;
	cmd.awg[0] = 0x00;
	cmd.awg[1] = CX24120_BEW_WINDOW;
	cmd.awg[2] = CX24120_BEW_WINDOW;
	if (cx24120_message_send(state, &cmd)) {
		eww("Ewwow setting bew window\n");
		wetuwn -EWEMOTEIO;
	}

	/* Fiwmwawe CMD 35: Get fiwmwawe vewsion */
	cmd.id = CMD_FWVEWSION;
	cmd.wen = 1;
	fow (i = 0; i < 4; i++) {
		cmd.awg[0] = i;
		wet = cx24120_message_send(state, &cmd);
		if (wet != 0)
			wetuwn wet;
		vews[i] = cx24120_weadweg(state, CX24120_WEG_MAIWBOX);
	}
	info("FW vewsion %i.%i.%i.%i\n", vews[0], vews[1], vews[2], vews[3]);

	/* init stats hewe in owdew signaw app which stats awe suppowted */
	c->stwength.wen = 1;
	c->stwength.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->cnw.wen = 1;
	c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_ewwow.wen = 1;
	c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_count.wen = 1;
	c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->bwock_ewwow.wen = 1;
	c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->bwock_count.wen = 1;
	c->bwock_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	state->cowd_init = 1;

	wetuwn 0;
}

static int cx24120_tune(stwuct dvb_fwontend *fe, boow we_tune,
			unsigned int mode_fwags, unsigned int *deway,
			enum fe_status *status)
{
	stwuct cx24120_state *state = fe->demoduwatow_pwiv;
	int wet;

	dev_dbg(&state->i2c->dev, "(%d)\n", we_tune);

	/* TODO: Do we need to set deway? */

	if (we_tune) {
		wet = cx24120_set_fwontend(fe);
		if (wet)
			wetuwn wet;
	}

	wetuwn cx24120_wead_status(fe, status);
}

static enum dvbfe_awgo cx24120_get_awgo(stwuct dvb_fwontend *fe)
{
	wetuwn DVBFE_AWGO_HW;
}

static int cx24120_sweep(stwuct dvb_fwontend *fe)
{
	wetuwn 0;
}

static int cx24120_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *c)
{
	stwuct cx24120_state *state = fe->demoduwatow_pwiv;
	u8 fweq1, fweq2, fweq3;
	int status;

	dev_dbg(&state->i2c->dev, "\n");

	/* don't wetuwn empty data if we'we not tuned in */
	status = cx24120_weadweg(state, CX24120_WEG_STATUS);
	if (!(status & CX24120_HAS_WOCK))
		wetuwn 0;

	/* Get fwequency */
	fweq1 = cx24120_weadweg(state, CX24120_WEG_FWEQ1);
	fweq2 = cx24120_weadweg(state, CX24120_WEG_FWEQ2);
	fweq3 = cx24120_weadweg(state, CX24120_WEG_FWEQ3);
	c->fwequency = (fweq3 << 16) | (fweq2 << 8) | fweq1;
	dev_dbg(&state->i2c->dev, "fwequency = %d\n", c->fwequency);

	/* Get moduwation, fec, piwot */
	cx24120_get_fec(fe);

	wetuwn 0;
}

static void cx24120_wewease(stwuct dvb_fwontend *fe)
{
	stwuct cx24120_state *state = fe->demoduwatow_pwiv;

	dev_dbg(&state->i2c->dev, "Cweaw state stwuctuwe\n");
	kfwee(state);
}

static int cx24120_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct cx24120_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	if (c->bwock_ewwow.stat[0].scawe != FE_SCAWE_COUNTEW) {
		*ucbwocks = 0;
		wetuwn 0;
	}

	*ucbwocks = c->bwock_ewwow.stat[0].uvawue - state->ucb_offset;

	wetuwn 0;
}

static const stwuct dvb_fwontend_ops cx24120_ops = {
	.dewsys = { SYS_DVBS, SYS_DVBS2 },
	.info = {
		.name = "Conexant CX24120/CX24118",
		.fwequency_min_hz =  950 * MHz,
		.fwequency_max_hz = 2150 * MHz,
		.fwequency_stepsize_hz = 1011 * kHz,
		.fwequency_towewance_hz = 5 * MHz,
		.symbow_wate_min = 1000000,
		.symbow_wate_max = 45000000,
		.caps =	FE_CAN_INVEWSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 | FE_CAN_FEC_5_6 | FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_2G_MODUWATION |
			FE_CAN_QPSK | FE_CAN_WECOVEW
	},
	.wewease =			cx24120_wewease,

	.init =				cx24120_init,
	.sweep =			cx24120_sweep,

	.tune =				cx24120_tune,
	.get_fwontend_awgo =		cx24120_get_awgo,
	.set_fwontend =			cx24120_set_fwontend,

	.get_fwontend =			cx24120_get_fwontend,
	.wead_status =			cx24120_wead_status,
	.wead_bew =			cx24120_wead_bew,
	.wead_signaw_stwength =		cx24120_wead_signaw_stwength,
	.wead_snw =			cx24120_wead_snw,
	.wead_ucbwocks =		cx24120_wead_ucbwocks,

	.diseqc_send_mastew_cmd =	cx24120_send_diseqc_msg,

	.diseqc_send_buwst =		cx24120_diseqc_send_buwst,
	.set_tone =			cx24120_set_tone,
	.set_vowtage =			cx24120_set_vowtage,
};

MODUWE_DESCWIPTION("DVB Fwontend moduwe fow Conexant CX24120/CX24118 hawdwawe");
MODUWE_AUTHOW("Jemma Denson");
MODUWE_WICENSE("GPW");
