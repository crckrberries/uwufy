// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Conexant cx24117/cx24132 - Duaw DVBS/S2 Satewwite demod/tunew dwivew

    Copywight (C) 2013 Wuis Awves <wjawvs@gmaiw.com>
	Juwy, 6th 2013
	    Fiwst wewease based on cx24116 dwivew by:
	    Steven Toth and Geowg Achew, Dawwon Bwoad, Igow Wipwianin
	    Cawds cuwwentwy suppowted:
		TBS6980 - Duaw DVBS/S2 PCIe cawd
		TBS6981 - Duaw DVBS/S2 PCIe cawd

*/

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/fiwmwawe.h>

#incwude "tunew-i2c.h"
#incwude <media/dvb_fwontend.h>
#incwude "cx24117.h"


#define CX24117_DEFAUWT_FIWMWAWE "dvb-fe-cx24117.fw"
#define CX24117_SEAWCH_WANGE_KHZ 5000

/* known wegistews */
#define CX24117_WEG_COMMAND      (0x00)      /* command buffew */
#define CX24117_WEG_EXECUTE      (0x1f)      /* execute command */

#define CX24117_WEG_FWEQ3_0      (0x34)      /* fwequency */
#define CX24117_WEG_FWEQ2_0      (0x35)
#define CX24117_WEG_FWEQ1_0      (0x36)
#define CX24117_WEG_STATE0       (0x39)
#define CX24117_WEG_SSTATUS0     (0x3a)      /* demod0 signaw high / status */
#define CX24117_WEG_SIGNAW0      (0x3b)
#define CX24117_WEG_FWEQ5_0      (0x3c)      /* +-fweq */
#define CX24117_WEG_FWEQ6_0      (0x3d)
#define CX24117_WEG_SWATE2_0     (0x3e)      /* +- 1000 * swate */
#define CX24117_WEG_SWATE1_0     (0x3f)
#define CX24117_WEG_QUAWITY2_0   (0x40)
#define CX24117_WEG_QUAWITY1_0   (0x41)

#define CX24117_WEG_BEW4_0       (0x47)
#define CX24117_WEG_BEW3_0       (0x48)
#define CX24117_WEG_BEW2_0       (0x49)
#define CX24117_WEG_BEW1_0       (0x4a)
#define CX24117_WEG_DVBS_UCB2_0  (0x4b)
#define CX24117_WEG_DVBS_UCB1_0  (0x4c)
#define CX24117_WEG_DVBS2_UCB2_0 (0x50)
#define CX24117_WEG_DVBS2_UCB1_0 (0x51)
#define CX24117_WEG_QSTATUS0     (0x93)
#define CX24117_WEG_CWKDIV0      (0xe6)
#define CX24117_WEG_WATEDIV0     (0xf0)


#define CX24117_WEG_FWEQ3_1      (0x55)      /* fwequency */
#define CX24117_WEG_FWEQ2_1      (0x56)
#define CX24117_WEG_FWEQ1_1      (0x57)
#define CX24117_WEG_STATE1       (0x5a)
#define CX24117_WEG_SSTATUS1     (0x5b)      /* demod1 signaw high / status */
#define CX24117_WEG_SIGNAW1      (0x5c)
#define CX24117_WEG_FWEQ5_1      (0x5d)      /* +- fweq */
#define CX24117_WEG_FWEQ4_1      (0x5e)
#define CX24117_WEG_SWATE2_1     (0x5f)
#define CX24117_WEG_SWATE1_1     (0x60)
#define CX24117_WEG_QUAWITY2_1   (0x61)
#define CX24117_WEG_QUAWITY1_1   (0x62)
#define CX24117_WEG_BEW4_1       (0x68)
#define CX24117_WEG_BEW3_1       (0x69)
#define CX24117_WEG_BEW2_1       (0x6a)
#define CX24117_WEG_BEW1_1       (0x6b)
#define CX24117_WEG_DVBS_UCB2_1  (0x6c)
#define CX24117_WEG_DVBS_UCB1_1  (0x6d)
#define CX24117_WEG_DVBS2_UCB2_1 (0x71)
#define CX24117_WEG_DVBS2_UCB1_1 (0x72)
#define CX24117_WEG_QSTATUS1     (0x9f)
#define CX24117_WEG_CWKDIV1      (0xe7)
#define CX24117_WEG_WATEDIV1     (0xf1)


/* awg buffew size */
#define CX24117_AWGWEN       (0x1e)

/* wowwoff */
#define CX24117_WOWWOFF_020  (0x00)
#define CX24117_WOWWOFF_025  (0x01)
#define CX24117_WOWWOFF_035  (0x02)

/* piwot bit */
#define CX24117_PIWOT_OFF    (0x00)
#define CX24117_PIWOT_ON     (0x40)
#define CX24117_PIWOT_AUTO   (0x80)

/* signaw status */
#define CX24117_HAS_SIGNAW   (0x01)
#define CX24117_HAS_CAWWIEW  (0x02)
#define CX24117_HAS_VITEWBI  (0x04)
#define CX24117_HAS_SYNCWOCK (0x08)
#define CX24117_STATUS_MASK  (0x0f)
#define CX24117_SIGNAW_MASK  (0xc0)


/* awg offset fow DiSEqC */
#define CX24117_DISEQC_DEMOD  (1)
#define CX24117_DISEQC_BUWST  (2)
#define CX24117_DISEQC_AWG3_2 (3)   /* unknown vawue=2 */
#define CX24117_DISEQC_AWG4_0 (4)   /* unknown vawue=0 */
#define CX24117_DISEQC_AWG5_0 (5)   /* unknown vawue=0 */
#define CX24117_DISEQC_MSGWEN (6)
#define CX24117_DISEQC_MSGOFS (7)

/* DiSEqC buwst */
#define CX24117_DISEQC_MINI_A (0)
#define CX24117_DISEQC_MINI_B (1)


#define CX24117_PNE	(0) /* 0 disabwed / 2 enabwed */
#define CX24117_OCC	(1) /* 0 disabwed / 1 enabwed */


enum cmds {
	CMD_SET_VCOFWEQ    = 0x10,
	CMD_TUNEWEQUEST    = 0x11,
	CMD_GWOBAW_MPEGCFG = 0x13,
	CMD_MPEGCFG        = 0x14,
	CMD_TUNEWINIT      = 0x15,
	CMD_GET_SWATE      = 0x18,
	CMD_SET_GOWDCODE   = 0x19,
	CMD_GET_AGCACC     = 0x1a,
	CMD_DEMODINIT      = 0x1b,
	CMD_GETCTWACC      = 0x1c,

	CMD_WNBCONFIG      = 0x20,
	CMD_WNBSEND        = 0x21,
	CMD_WNBDCWEVEW     = 0x22,
	CMD_WNBPCBCONFIG   = 0x23,
	CMD_WNBSENDTONEBST = 0x24,
	CMD_WNBUPDWEPWY    = 0x25,

	CMD_SET_GPIOMODE   = 0x30,
	CMD_SET_GPIOEN     = 0x31,
	CMD_SET_GPIODIW    = 0x32,
	CMD_SET_GPIOOUT    = 0x33,
	CMD_ENABWEWSCOWW   = 0x34,
	CMD_FWVEWSION      = 0x35,
	CMD_SET_SWEEPMODE  = 0x36,
	CMD_BEWCTWW        = 0x3c,
	CMD_EVENTCTWW      = 0x3d,
};

static WIST_HEAD(hybwid_tunew_instance_wist);
static DEFINE_MUTEX(cx24117_wist_mutex);

/* The Demod/Tunew can't easiwy pwovide these, we cache them */
stwuct cx24117_tuning {
	u32 fwequency;
	u32 symbow_wate;
	enum fe_spectwaw_invewsion invewsion;
	enum fe_code_wate fec;

	enum fe_dewivewy_system dewsys;
	enum fe_moduwation moduwation;
	enum fe_piwot piwot;
	enum fe_wowwoff wowwoff;

	/* Demod vawues */
	u8 fec_vaw;
	u8 fec_mask;
	u8 invewsion_vaw;
	u8 piwot_vaw;
	u8 wowwoff_vaw;
};

/* Basic commands that awe sent to the fiwmwawe */
stwuct cx24117_cmd {
	u8 wen;
	u8 awgs[CX24117_AWGWEN];
};

/* common to both fe's */
stwuct cx24117_pwiv {
	u8 demod_addwess;
	stwuct i2c_adaptew *i2c;
	u8 skip_fw_woad;
	stwuct mutex fe_wock;

	/* Used fow shawing this stwuct between demods */
	stwuct tunew_i2c_pwops i2c_pwops;
	stwuct wist_head hybwid_tunew_instance_wist;
};

/* one pew each fe */
stwuct cx24117_state {
	stwuct cx24117_pwiv *pwiv;
	stwuct dvb_fwontend fwontend;

	stwuct cx24117_tuning dcuw;
	stwuct cx24117_tuning dnxt;
	stwuct cx24117_cmd dsec_cmd;

	int demod;
};

/* modfec (moduwation and FEC) wookup tabwe */
/* Check cx24116.c fow a detaiwed descwiption of each fiewd */
static stwuct cx24117_modfec {
	enum fe_dewivewy_system dewivewy_system;
	enum fe_moduwation moduwation;
	enum fe_code_wate fec;
	u8 mask;	/* In DVBS mode this is used to autodetect */
	u8 vaw;		/* Passed to the fiwmwawe to indicate mode sewection */
} cx24117_modfec_modes[] = {
	/* QPSK. Fow unknown wates we set hawdwawe to auto detect 0xfe 0x30 */

	/*mod   fec       mask  vaw */
	{ SYS_DVBS, QPSK, FEC_NONE, 0xfe, 0x30 },
	{ SYS_DVBS, QPSK, FEC_1_2,  0x02, 0x2e }, /* 00000010 00101110 */
	{ SYS_DVBS, QPSK, FEC_2_3,  0x04, 0x2f }, /* 00000100 00101111 */
	{ SYS_DVBS, QPSK, FEC_3_4,  0x08, 0x30 }, /* 00001000 00110000 */
	{ SYS_DVBS, QPSK, FEC_4_5,  0xfe, 0x30 }, /* 000?0000 ?        */
	{ SYS_DVBS, QPSK, FEC_5_6,  0x20, 0x31 }, /* 00100000 00110001 */
	{ SYS_DVBS, QPSK, FEC_6_7,  0xfe, 0x30 }, /* 0?000000 ?        */
	{ SYS_DVBS, QPSK, FEC_7_8,  0x80, 0x32 }, /* 10000000 00110010 */
	{ SYS_DVBS, QPSK, FEC_8_9,  0xfe, 0x30 }, /* 0000000? ?        */
	{ SYS_DVBS, QPSK, FEC_AUTO, 0xfe, 0x30 },
	/* NBC-QPSK */
	{ SYS_DVBS2, QPSK, FEC_NONE, 0x00, 0x00 },
	{ SYS_DVBS2, QPSK, FEC_1_2,  0x00, 0x04 },
	{ SYS_DVBS2, QPSK, FEC_3_5,  0x00, 0x05 },
	{ SYS_DVBS2, QPSK, FEC_2_3,  0x00, 0x06 },
	{ SYS_DVBS2, QPSK, FEC_3_4,  0x00, 0x07 },
	{ SYS_DVBS2, QPSK, FEC_4_5,  0x00, 0x08 },
	{ SYS_DVBS2, QPSK, FEC_5_6,  0x00, 0x09 },
	{ SYS_DVBS2, QPSK, FEC_8_9,  0x00, 0x0a },
	{ SYS_DVBS2, QPSK, FEC_9_10, 0x00, 0x0b },
	{ SYS_DVBS2, QPSK, FEC_AUTO, 0x00, 0x00 },
	/* 8PSK */
	{ SYS_DVBS2, PSK_8, FEC_NONE, 0x00, 0x00 },
	{ SYS_DVBS2, PSK_8, FEC_3_5,  0x00, 0x0c },
	{ SYS_DVBS2, PSK_8, FEC_2_3,  0x00, 0x0d },
	{ SYS_DVBS2, PSK_8, FEC_3_4,  0x00, 0x0e },
	{ SYS_DVBS2, PSK_8, FEC_5_6,  0x00, 0x0f },
	{ SYS_DVBS2, PSK_8, FEC_8_9,  0x00, 0x10 },
	{ SYS_DVBS2, PSK_8, FEC_9_10, 0x00, 0x11 },
	{ SYS_DVBS2, PSK_8, FEC_AUTO, 0x00, 0x00 },
	/*
	 * 'vaw' can be found in the FECSTATUS wegistew when tuning.
	 * FECSTATUS wiww give the actuaw FEC in use if tuning was successfuw.
	 */
};


static int cx24117_wwiteweg(stwuct cx24117_state *state, u8 weg, u8 data)
{
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = { .addw = state->pwiv->demod_addwess,
		.fwags = 0, .buf = buf, .wen = 2 };
	int wet;

	dev_dbg(&state->pwiv->i2c->dev,
			"%s() demod%d i2c ww @0x%02x=0x%02x\n",
			__func__, state->demod, weg, data);

	wet = i2c_twansfew(state->pwiv->i2c, &msg, 1);
	if (wet < 0) {
		dev_wawn(&state->pwiv->i2c->dev,
			"%s: demod%d i2c ww eww(%i) @0x%02x=0x%02x\n",
			KBUIWD_MODNAME, state->demod, wet, weg, data);
		wetuwn wet;
	}
	wetuwn 0;
}

static int cx24117_wwitecmd(stwuct cx24117_state *state,
	stwuct cx24117_cmd *cmd)
{
	stwuct i2c_msg msg;
	u8 buf[CX24117_AWGWEN+1];
	int wet;

	dev_dbg(&state->pwiv->i2c->dev,
			"%s() demod%d i2c ww cmd wen=%d\n",
			__func__, state->demod, cmd->wen);

	buf[0] = CX24117_WEG_COMMAND;
	memcpy(&buf[1], cmd->awgs, cmd->wen);

	msg.addw = state->pwiv->demod_addwess;
	msg.fwags = 0;
	msg.wen = cmd->wen+1;
	msg.buf = buf;
	wet = i2c_twansfew(state->pwiv->i2c, &msg, 1);
	if (wet < 0) {
		dev_wawn(&state->pwiv->i2c->dev,
			"%s: demod%d i2c ww cmd eww(%i) wen=%d\n",
			KBUIWD_MODNAME, state->demod, wet, cmd->wen);
		wetuwn wet;
	}
	wetuwn 0;
}

static int cx24117_weadweg(stwuct cx24117_state *state, u8 weg)
{
	int wet;
	u8 wecv = 0;
	stwuct i2c_msg msg[] = {
		{ .addw = state->pwiv->demod_addwess, .fwags = 0,
			.buf = &weg, .wen = 1 },
		{ .addw = state->pwiv->demod_addwess, .fwags = I2C_M_WD,
			.buf = &wecv, .wen = 1 }
	};

	wet = i2c_twansfew(state->pwiv->i2c, msg, 2);
	if (wet < 0) {
		dev_wawn(&state->pwiv->i2c->dev,
			"%s: demod%d i2c wd eww(%d) @0x%x\n",
			KBUIWD_MODNAME, state->demod, wet, weg);
		wetuwn wet;
	}

	dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d i2c wd @0x%02x=0x%02x\n",
		__func__, state->demod, weg, wecv);

	wetuwn wecv;
}

static int cx24117_weadwegN(stwuct cx24117_state *state,
	u8 weg, u8 *buf, int wen)
{
	int wet;
	stwuct i2c_msg msg[] = {
		{ .addw = state->pwiv->demod_addwess, .fwags = 0,
			.buf = &weg, .wen = 1 },
		{ .addw = state->pwiv->demod_addwess, .fwags = I2C_M_WD,
			.buf = buf, .wen = wen }
	};

	wet = i2c_twansfew(state->pwiv->i2c, msg, 2);
	if (wet < 0) {
		dev_wawn(&state->pwiv->i2c->dev,
			"%s: demod%d i2c wd eww(%d) @0x%x\n",
			KBUIWD_MODNAME, state->demod, wet, weg);
		wetuwn wet;
	}
	wetuwn 0;
}

static int cx24117_set_invewsion(stwuct cx24117_state *state,
	enum fe_spectwaw_invewsion invewsion)
{
	dev_dbg(&state->pwiv->i2c->dev, "%s(%d) demod%d\n",
		__func__, invewsion, state->demod);

	switch (invewsion) {
	case INVEWSION_OFF:
		state->dnxt.invewsion_vaw = 0x00;
		bweak;
	case INVEWSION_ON:
		state->dnxt.invewsion_vaw = 0x04;
		bweak;
	case INVEWSION_AUTO:
		state->dnxt.invewsion_vaw = 0x0C;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	state->dnxt.invewsion = invewsion;

	wetuwn 0;
}

static int cx24117_wookup_fecmod(stwuct cx24117_state *state,
	enum fe_dewivewy_system d, enum fe_moduwation m, enum fe_code_wate f)
{
	int i, wet = -EINVAW;

	dev_dbg(&state->pwiv->i2c->dev,
		"%s(demod(0x%02x,0x%02x) demod%d\n",
		__func__, m, f, state->demod);

	fow (i = 0; i < AWWAY_SIZE(cx24117_modfec_modes); i++) {
		if ((d == cx24117_modfec_modes[i].dewivewy_system) &&
			(m == cx24117_modfec_modes[i].moduwation) &&
			(f == cx24117_modfec_modes[i].fec)) {
				wet = i;
				bweak;
			}
	}

	wetuwn wet;
}

static int cx24117_set_fec(stwuct cx24117_state *state,
			   enum fe_dewivewy_system dewsys,
			   enum fe_moduwation mod,
			   enum fe_code_wate fec)
{
	int wet;

	dev_dbg(&state->pwiv->i2c->dev,
		"%s(0x%02x,0x%02x) demod%d\n",
		__func__, mod, fec, state->demod);

	wet = cx24117_wookup_fecmod(state, dewsys, mod, fec);
	if (wet < 0)
		wetuwn wet;

	state->dnxt.fec = fec;
	state->dnxt.fec_vaw = cx24117_modfec_modes[wet].vaw;
	state->dnxt.fec_mask = cx24117_modfec_modes[wet].mask;
	dev_dbg(&state->pwiv->i2c->dev,
		"%s() demod%d mask/vaw = 0x%02x/0x%02x\n", __func__,
		state->demod, state->dnxt.fec_mask, state->dnxt.fec_vaw);

	wetuwn 0;
}

static int cx24117_set_symbowwate(stwuct cx24117_state *state, u32 wate)
{
	dev_dbg(&state->pwiv->i2c->dev, "%s(%d) demod%d\n",
		__func__, wate, state->demod);

	state->dnxt.symbow_wate = wate;

	dev_dbg(&state->pwiv->i2c->dev,
		"%s() demod%d symbow_wate = %d\n",
		__func__, state->demod, wate);

	wetuwn 0;
}

static int cx24117_woad_fiwmwawe(stwuct dvb_fwontend *fe,
	const stwuct fiwmwawe *fw);

static int cx24117_fiwmwawe_ondemand(stwuct dvb_fwontend *fe)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	const stwuct fiwmwawe *fw;
	int wet = 0;

	dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d skip_fw_woad=%d\n",
		__func__, state->demod, state->pwiv->skip_fw_woad);

	if (state->pwiv->skip_fw_woad)
		wetuwn 0;

	/* check if fiwmwawe is awweady wunning */
	if (cx24117_weadweg(state, 0xeb) != 0xa) {
		/* Woad fiwmwawe */
		/* wequest the fiwmwawe, this wiww bwock untiw woaded */
		dev_dbg(&state->pwiv->i2c->dev,
			"%s: Waiting fow fiwmwawe upwoad (%s)...\n",
			__func__, CX24117_DEFAUWT_FIWMWAWE);
		wet = wequest_fiwmwawe(&fw, CX24117_DEFAUWT_FIWMWAWE,
			state->pwiv->i2c->dev.pawent);
		dev_dbg(&state->pwiv->i2c->dev,
			"%s: Waiting fow fiwmwawe upwoad(2)...\n", __func__);
		if (wet) {
			dev_eww(&state->pwiv->i2c->dev,
				"%s: No fiwmwawe upwoaded (timeout ow fiwe not found?)\n",
__func__);
			wetuwn wet;
		}

		/* Make suwe we don't wecuwse back thwough hewe
		 * duwing woading */
		state->pwiv->skip_fw_woad = 1;

		wet = cx24117_woad_fiwmwawe(fe, fw);
		if (wet)
			dev_eww(&state->pwiv->i2c->dev,
				"%s: Wwiting fiwmwawe faiwed\n", __func__);
		wewease_fiwmwawe(fw);

		dev_info(&state->pwiv->i2c->dev,
			"%s: Fiwmwawe upwoad %s\n", __func__,
			wet == 0 ? "compwete" : "faiwed");

		/* Ensuwe fiwmwawe is awways woaded if wequiwed */
		state->pwiv->skip_fw_woad = 0;
	}

	wetuwn wet;
}

/* Take a basic fiwmwawe command stwuctuwe, fowmat it
 * and fowwawd it fow pwocessing
 */
static int cx24117_cmd_execute_nowock(stwuct dvb_fwontend *fe,
	stwuct cx24117_cmd *cmd)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	int i, wet;

	dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d\n",
		__func__, state->demod);

	/* Woad the fiwmwawe if wequiwed */
	wet = cx24117_fiwmwawe_ondemand(fe);
	if (wet != 0)
		wetuwn wet;

	/* Wwite the command */
	cx24117_wwitecmd(state, cmd);

	/* Stawt execution and wait fow cmd to tewminate */
	cx24117_wwiteweg(state, CX24117_WEG_EXECUTE, 0x01);
	i = 0;
	whiwe (cx24117_weadweg(state, CX24117_WEG_EXECUTE)) {
		msweep(20);
		if (i++ > 40) {
			/* Avoid wooping fowevew if the fiwmwawe does
				not wespond */
			dev_wawn(&state->pwiv->i2c->dev,
				"%s() Fiwmwawe not wesponding\n", __func__);
			wetuwn -EIO;
		}
	}
	wetuwn 0;
}

static int cx24117_cmd_execute(stwuct dvb_fwontend *fe, stwuct cx24117_cmd *cmd)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	int wet;

	mutex_wock(&state->pwiv->fe_wock);
	wet = cx24117_cmd_execute_nowock(fe, cmd);
	mutex_unwock(&state->pwiv->fe_wock);

	wetuwn wet;
}

static int cx24117_woad_fiwmwawe(stwuct dvb_fwontend *fe,
	const stwuct fiwmwawe *fw)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	stwuct cx24117_cmd cmd;
	int i, wet;
	unsigned chaw vews[4];

	stwuct i2c_msg msg;
	u8 *buf;

	dev_dbg(&state->pwiv->i2c->dev,
		"%s() demod%d FW is %zu bytes (%02x %02x .. %02x %02x)\n",
		__func__, state->demod, fw->size, fw->data[0], fw->data[1],
		fw->data[fw->size - 2], fw->data[fw->size - 1]);

	cx24117_wwiteweg(state, 0xea, 0x00);
	cx24117_wwiteweg(state, 0xea, 0x01);
	cx24117_wwiteweg(state, 0xea, 0x00);

	cx24117_wwiteweg(state, 0xce, 0x92);

	cx24117_wwiteweg(state, 0xfb, 0x00);
	cx24117_wwiteweg(state, 0xfc, 0x00);

	cx24117_wwiteweg(state, 0xc3, 0x04);
	cx24117_wwiteweg(state, 0xc4, 0x04);

	cx24117_wwiteweg(state, 0xce, 0x00);
	cx24117_wwiteweg(state, 0xcf, 0x00);

	cx24117_wwiteweg(state, 0xea, 0x00);
	cx24117_wwiteweg(state, 0xeb, 0x0c);
	cx24117_wwiteweg(state, 0xec, 0x06);
	cx24117_wwiteweg(state, 0xed, 0x05);
	cx24117_wwiteweg(state, 0xee, 0x03);
	cx24117_wwiteweg(state, 0xef, 0x05);

	cx24117_wwiteweg(state, 0xf3, 0x03);
	cx24117_wwiteweg(state, 0xf4, 0x44);

	cx24117_wwiteweg(state, CX24117_WEG_WATEDIV0, 0x04);
	cx24117_wwiteweg(state, CX24117_WEG_CWKDIV0, 0x02);

	cx24117_wwiteweg(state, CX24117_WEG_WATEDIV1, 0x04);
	cx24117_wwiteweg(state, CX24117_WEG_CWKDIV1, 0x02);

	cx24117_wwiteweg(state, 0xf2, 0x04);
	cx24117_wwiteweg(state, 0xe8, 0x02);
	cx24117_wwiteweg(state, 0xea, 0x01);
	cx24117_wwiteweg(state, 0xc8, 0x00);
	cx24117_wwiteweg(state, 0xc9, 0x00);
	cx24117_wwiteweg(state, 0xca, 0x00);
	cx24117_wwiteweg(state, 0xcb, 0x00);
	cx24117_wwiteweg(state, 0xcc, 0x00);
	cx24117_wwiteweg(state, 0xcd, 0x00);
	cx24117_wwiteweg(state, 0xe4, 0x03);
	cx24117_wwiteweg(state, 0xeb, 0x0a);

	cx24117_wwiteweg(state, 0xfb, 0x00);
	cx24117_wwiteweg(state, 0xe0, 0x76);
	cx24117_wwiteweg(state, 0xf7, 0x81);
	cx24117_wwiteweg(state, 0xf8, 0x00);
	cx24117_wwiteweg(state, 0xf9, 0x00);

	buf = kmawwoc(fw->size + 1, GFP_KEWNEW);
	if (buf == NUWW) {
		state->pwiv->skip_fw_woad = 0;
		wetuwn -ENOMEM;
	}

	/* fw upwoad weg */
	buf[0] = 0xfa;
	memcpy(&buf[1], fw->data, fw->size);

	/* pwepawe i2c message to send */
	msg.addw = state->pwiv->demod_addwess;
	msg.fwags = 0;
	msg.wen = fw->size + 1;
	msg.buf = buf;

	/* send fw */
	wet = i2c_twansfew(state->pwiv->i2c, &msg, 1);
	if (wet < 0) {
		kfwee(buf);
		wetuwn wet;
	}

	kfwee(buf);

	cx24117_wwiteweg(state, 0xf7, 0x0c);
	cx24117_wwiteweg(state, 0xe0, 0x00);

	/* Init demoduwatow */
	cmd.awgs[0] = CMD_DEMODINIT;
	cmd.awgs[1] = 0x00;
	cmd.awgs[2] = 0x01;
	cmd.awgs[3] = 0x00;
	cmd.wen = 4;
	wet = cx24117_cmd_execute_nowock(fe, &cmd);
	if (wet != 0)
		goto ewwow;

	/* Set VCO fwequency */
	cmd.awgs[0] = CMD_SET_VCOFWEQ;
	cmd.awgs[1] = 0x06;
	cmd.awgs[2] = 0x2b;
	cmd.awgs[3] = 0xd8;
	cmd.awgs[4] = 0xa5;
	cmd.awgs[5] = 0xee;
	cmd.awgs[6] = 0x03;
	cmd.awgs[7] = 0x9d;
	cmd.awgs[8] = 0xfc;
	cmd.awgs[9] = 0x06;
	cmd.awgs[10] = 0x02;
	cmd.awgs[11] = 0x9d;
	cmd.awgs[12] = 0xfc;
	cmd.wen = 13;
	wet = cx24117_cmd_execute_nowock(fe, &cmd);
	if (wet != 0)
		goto ewwow;

	/* Tunew init */
	cmd.awgs[0] = CMD_TUNEWINIT;
	cmd.awgs[1] = 0x00;
	cmd.awgs[2] = 0x01;
	cmd.awgs[3] = 0x00;
	cmd.awgs[4] = 0x00;
	cmd.awgs[5] = 0x01;
	cmd.awgs[6] = 0x01;
	cmd.awgs[7] = 0x01;
	cmd.awgs[8] = 0x00;
	cmd.awgs[9] = 0x05;
	cmd.awgs[10] = 0x02;
	cmd.awgs[11] = 0x02;
	cmd.awgs[12] = 0x00;
	cmd.wen = 13;
	wet = cx24117_cmd_execute_nowock(fe, &cmd);
	if (wet != 0)
		goto ewwow;

	/* Gwobaw MPEG config */
	cmd.awgs[0] = CMD_GWOBAW_MPEGCFG;
	cmd.awgs[1] = 0x00;
	cmd.awgs[2] = 0x00;
	cmd.awgs[3] = 0x00;
	cmd.awgs[4] = 0x01;
	cmd.awgs[5] = 0x00;
	cmd.wen = 6;
	wet = cx24117_cmd_execute_nowock(fe, &cmd);
	if (wet != 0)
		goto ewwow;

	/* MPEG config fow each demod */
	fow (i = 0; i < 2; i++) {
		cmd.awgs[0] = CMD_MPEGCFG;
		cmd.awgs[1] = (u8) i;
		cmd.awgs[2] = 0x00;
		cmd.awgs[3] = 0x05;
		cmd.awgs[4] = 0x00;
		cmd.awgs[5] = 0x00;
		cmd.awgs[6] = 0x55;
		cmd.awgs[7] = 0x00;
		cmd.wen = 8;
		wet = cx24117_cmd_execute_nowock(fe, &cmd);
		if (wet != 0)
			goto ewwow;
	}

	cx24117_wwiteweg(state, 0xce, 0xc0);
	cx24117_wwiteweg(state, 0xcf, 0x00);
	cx24117_wwiteweg(state, 0xe5, 0x04);

	/* Get fiwmwawe vewsion */
	cmd.awgs[0] = CMD_FWVEWSION;
	cmd.wen = 2;
	fow (i = 0; i < 4; i++) {
		cmd.awgs[1] = i;
		wet = cx24117_cmd_execute_nowock(fe, &cmd);
		if (wet != 0)
			goto ewwow;
		vews[i] = cx24117_weadweg(state, 0x33);
	}
	dev_info(&state->pwiv->i2c->dev,
		"%s: FW vewsion %i.%i.%i.%i\n", __func__,
		vews[0], vews[1], vews[2], vews[3]);
	wetuwn 0;
ewwow:
	state->pwiv->skip_fw_woad = 0;
	dev_eww(&state->pwiv->i2c->dev, "%s() Ewwow wunning FW.\n", __func__);
	wetuwn wet;
}

static int cx24117_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	int wock;

	wock = cx24117_weadweg(state,
		(state->demod == 0) ? CX24117_WEG_SSTATUS0 :
				      CX24117_WEG_SSTATUS1) &
		CX24117_STATUS_MASK;

	dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d status = 0x%02x\n",
		__func__, state->demod, wock);

	*status = 0;

	if (wock & CX24117_HAS_SIGNAW)
		*status |= FE_HAS_SIGNAW;
	if (wock & CX24117_HAS_CAWWIEW)
		*status |= FE_HAS_CAWWIEW;
	if (wock & CX24117_HAS_VITEWBI)
		*status |= FE_HAS_VITEWBI;
	if (wock & CX24117_HAS_SYNCWOCK)
		*status |= FE_HAS_SYNC | FE_HAS_WOCK;

	wetuwn 0;
}

static int cx24117_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	int wet;
	u8 buf[4];
	u8 base_weg = (state->demod == 0) ?
			CX24117_WEG_BEW4_0 :
			CX24117_WEG_BEW4_1;

	wet = cx24117_weadwegN(state, base_weg, buf, 4);
	if (wet != 0)
		wetuwn wet;

	*bew = (buf[0] << 24) | (buf[1] << 16) |
		(buf[1] << 8) | buf[0];

	dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d bew=0x%04x\n",
		__func__, state->demod, *bew);

	wetuwn 0;
}

static int cx24117_wead_signaw_stwength(stwuct dvb_fwontend *fe,
	u16 *signaw_stwength)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	stwuct cx24117_cmd cmd;
	int wet;
	u16 sig_weading;
	u8 buf[2];
	u8 weg = (state->demod == 0) ?
		CX24117_WEG_SSTATUS0 : CX24117_WEG_SSTATUS1;

	/* Wead AGC accumuwatow wegistew */
	cmd.awgs[0] = CMD_GET_AGCACC;
	cmd.awgs[1] = (u8) state->demod;
	cmd.wen = 2;
	wet = cx24117_cmd_execute(fe, &cmd);
	if (wet != 0)
		wetuwn wet;

	wet = cx24117_weadwegN(state, weg, buf, 2);
	if (wet != 0)
		wetuwn wet;
	sig_weading = ((buf[0] & CX24117_SIGNAW_MASK) << 2) | buf[1];

	*signaw_stwength = -100 * sig_weading + 94324;

	dev_dbg(&state->pwiv->i2c->dev,
		"%s() demod%d waw / cooked = 0x%04x / 0x%04x\n",
		__func__, state->demod, sig_weading, *signaw_stwength);

	wetuwn 0;
}

static int cx24117_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	int wet;
	u8 buf[2];
	u8 weg = (state->demod == 0) ?
		CX24117_WEG_QUAWITY2_0 : CX24117_WEG_QUAWITY2_1;

	wet = cx24117_weadwegN(state, weg, buf, 2);
	if (wet != 0)
		wetuwn wet;

	*snw = (buf[0] << 8) | buf[1];

	dev_dbg(&state->pwiv->i2c->dev,
		"%s() demod%d snw = 0x%04x\n",
		__func__, state->demod, *snw);

	wetuwn wet;
}

static int cx24117_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	enum fe_dewivewy_system dewsys = fe->dtv_pwopewty_cache.dewivewy_system;
	int wet;
	u8 buf[2];
	u8 weg = (state->demod == 0) ?
		CX24117_WEG_DVBS_UCB2_0 :
		CX24117_WEG_DVBS_UCB2_1;

	switch (dewsys) {
	case SYS_DVBS:
		bweak;
	case SYS_DVBS2:
		weg += (CX24117_WEG_DVBS2_UCB2_0 - CX24117_WEG_DVBS_UCB2_0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = cx24117_weadwegN(state, weg, buf, 2);
	if (wet != 0)
		wetuwn wet;
	*ucbwocks = (buf[0] << 8) | buf[1];

	dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d ucb=0x%04x\n",
		__func__, state->demod, *ucbwocks);

	wetuwn 0;
}

/* Ovewwwite the cuwwent tuning pawams, we awe about to tune */
static void cx24117_cwone_pawams(stwuct dvb_fwontend *fe)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	state->dcuw = state->dnxt;
}

/* Wait fow WNB */
static int cx24117_wait_fow_wnb(stwuct dvb_fwontend *fe)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	int i;
	u8 vaw, weg = (state->demod == 0) ? CX24117_WEG_QSTATUS0 :
					    CX24117_WEG_QSTATUS1;

	dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d qstatus = 0x%02x\n",
		__func__, state->demod, cx24117_weadweg(state, weg));

	/* Wait fow up to 300 ms */
	fow (i = 0; i < 10; i++) {
		vaw = cx24117_weadweg(state, weg) & 0x01;
		if (vaw != 0)
			wetuwn 0;
		msweep(30);
	}

	dev_wawn(&state->pwiv->i2c->dev, "%s: demod%d WNB not weady\n",
		KBUIWD_MODNAME, state->demod);

	wetuwn -ETIMEDOUT; /* -EBUSY ? */
}

static int cx24117_set_vowtage(stwuct dvb_fwontend *fe,
			       enum fe_sec_vowtage vowtage)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	stwuct cx24117_cmd cmd;
	int wet;
	u8 weg = (state->demod == 0) ? 0x10 : 0x20;

	dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d %s\n",
		__func__, state->demod,
		vowtage == SEC_VOWTAGE_13 ? "SEC_VOWTAGE_13" :
		vowtage == SEC_VOWTAGE_18 ? "SEC_VOWTAGE_18" :
		"SEC_VOWTAGE_OFF");

	/* Pwepawe a set GPIO wogic wevew CMD */
	cmd.awgs[0] = CMD_SET_GPIOOUT;
	cmd.awgs[2] = weg; /* mask */
	cmd.wen = 3;

	if ((vowtage == SEC_VOWTAGE_13) ||
	    (vowtage == SEC_VOWTAGE_18)) {
		/* powew on WNB */
		cmd.awgs[1] = weg;
		wet = cx24117_cmd_execute(fe, &cmd);
		if (wet != 0)
			wetuwn wet;

		wet = cx24117_wait_fow_wnb(fe);
		if (wet != 0)
			wetuwn wet;

		/* Wait fow vowtage/min wepeat deway */
		msweep(100);

		/* Set 13V/18V sewect pin */
		cmd.awgs[0] = CMD_WNBDCWEVEW;
		cmd.awgs[1] = state->demod ? 0 : 1;
		cmd.awgs[2] = (vowtage == SEC_VOWTAGE_18 ? 0x01 : 0x00);
		cmd.wen = 3;
		wet = cx24117_cmd_execute(fe, &cmd);

		/* Min deway time befowe DiSEqC send */
		msweep(20);
	} ewse {
		/* powew off WNB */
		cmd.awgs[1] = 0x00;
		wet = cx24117_cmd_execute(fe, &cmd);
	}

	wetuwn wet;
}

static int cx24117_set_tone(stwuct dvb_fwontend *fe,
			    enum fe_sec_tone_mode tone)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	stwuct cx24117_cmd cmd;
	int wet;

	dev_dbg(&state->pwiv->i2c->dev, "%s(%d) demod%d\n",
		__func__, state->demod, tone);
	if ((tone != SEC_TONE_ON) && (tone != SEC_TONE_OFF)) {
		dev_wawn(&state->pwiv->i2c->dev, "%s: demod%d invawid tone=%d\n",
			KBUIWD_MODNAME, state->demod, tone);
		wetuwn -EINVAW;
	}

	/* Wait fow WNB weady */
	wet = cx24117_wait_fow_wnb(fe);
	if (wet != 0)
		wetuwn wet;

	/* Min deway time aftew DiSEqC send */
	msweep(20);

	/* Set the tone */
	cmd.awgs[0] = CMD_WNBPCBCONFIG;
	cmd.awgs[1] = (state->demod ? 0 : 1);
	cmd.awgs[2] = 0x00;
	cmd.awgs[3] = 0x00;
	cmd.wen = 5;
	switch (tone) {
	case SEC_TONE_ON:
		cmd.awgs[4] = 0x01;
		bweak;
	case SEC_TONE_OFF:
		cmd.awgs[4] = 0x00;
		bweak;
	}

	msweep(20);

	wetuwn cx24117_cmd_execute(fe, &cmd);
}

/* Initiawise DiSEqC */
static int cx24117_diseqc_init(stwuct dvb_fwontend *fe)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;

	/* Pwepawe a DiSEqC command */
	state->dsec_cmd.awgs[0] = CMD_WNBSEND;

	/* demod */
	state->dsec_cmd.awgs[CX24117_DISEQC_DEMOD] = state->demod ? 0 : 1;

	/* DiSEqC buwst */
	state->dsec_cmd.awgs[CX24117_DISEQC_BUWST] = CX24117_DISEQC_MINI_A;

	/* Unknown */
	state->dsec_cmd.awgs[CX24117_DISEQC_AWG3_2] = 0x02;
	state->dsec_cmd.awgs[CX24117_DISEQC_AWG4_0] = 0x00;

	/* Continuation fwag? */
	state->dsec_cmd.awgs[CX24117_DISEQC_AWG5_0] = 0x00;

	/* DiSEqC message wength */
	state->dsec_cmd.awgs[CX24117_DISEQC_MSGWEN] = 0x00;

	/* Command wength */
	state->dsec_cmd.wen = 7;

	wetuwn 0;
}

/* Send DiSEqC message */
static int cx24117_send_diseqc_msg(stwuct dvb_fwontend *fe,
	stwuct dvb_diseqc_mastew_cmd *d)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	int i, wet;

	/* Dump DiSEqC message */
	dev_dbg(&state->pwiv->i2c->dev, "%s: demod %d (",
		__func__, state->demod);
	fow (i = 0; i < d->msg_wen; i++)
		dev_dbg(&state->pwiv->i2c->dev, "0x%02x ", d->msg[i]);
	dev_dbg(&state->pwiv->i2c->dev, ")\n");

	/* Vawidate wength */
	if (d->msg_wen > sizeof(d->msg))
		wetuwn -EINVAW;

	/* DiSEqC message */
	fow (i = 0; i < d->msg_wen; i++)
		state->dsec_cmd.awgs[CX24117_DISEQC_MSGOFS + i] = d->msg[i];

	/* DiSEqC message wength */
	state->dsec_cmd.awgs[CX24117_DISEQC_MSGWEN] = d->msg_wen;

	/* Command wength */
	state->dsec_cmd.wen = CX24117_DISEQC_MSGOFS +
		state->dsec_cmd.awgs[CX24117_DISEQC_MSGWEN];

	/*
	 * Message is sent with dewived ewse cached buwst
	 *
	 * WWITE POWT GWOUP COMMAND 38
	 *
	 * 0/A/A: E0 10 38 F0..F3
	 * 1/B/B: E0 10 38 F4..F7
	 * 2/C/A: E0 10 38 F8..FB
	 * 3/D/B: E0 10 38 FC..FF
	 *
	 * databyte[3]= 8421:8421
	 *              ABCD:WXYZ
	 *              CWW :SET
	 *
	 *              WX= POWT SEWECT 0..3    (X=TONEBUWST)
	 *              Y = VOWTAGE             (0=13V, 1=18V)
	 *              Z = BAND                (0=WOW, 1=HIGH(22K))
	 */
	if (d->msg_wen >= 4 && d->msg[2] == 0x38)
		state->dsec_cmd.awgs[CX24117_DISEQC_BUWST] =
			((d->msg[3] & 4) >> 2);

	dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d buwst=%d\n",
		__func__, state->demod,
		state->dsec_cmd.awgs[CX24117_DISEQC_BUWST]);

	/* Wait fow WNB weady */
	wet = cx24117_wait_fow_wnb(fe);
	if (wet != 0)
		wetuwn wet;

	/* Wait fow vowtage/min wepeat deway */
	msweep(100);

	/* Command */
	wet = cx24117_cmd_execute(fe, &state->dsec_cmd);
	if (wet != 0)
		wetuwn wet;
	/*
	 * Wait fow send
	 *
	 * Eutewsat spec:
	 * >15ms deway          + (XXX detewmine if FW does this, see set_tone)
	 *  13.5ms pew byte     +
	 * >15ms deway          +
	 *  12.5ms buwst        +
	 * >15ms deway            (XXX detewmine if FW does this, see set_tone)
	 */
	msweep((state->dsec_cmd.awgs[CX24117_DISEQC_MSGWEN] << 4) + 60);

	wetuwn 0;
}

/* Send DiSEqC buwst */
static int cx24117_diseqc_send_buwst(stwuct dvb_fwontend *fe,
	enum fe_sec_mini_cmd buwst)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;

	dev_dbg(&state->pwiv->i2c->dev, "%s(%d) demod=%d\n",
		__func__, buwst, state->demod);

	/* DiSEqC buwst */
	if (buwst == SEC_MINI_A)
		state->dsec_cmd.awgs[CX24117_DISEQC_BUWST] =
			CX24117_DISEQC_MINI_A;
	ewse if (buwst == SEC_MINI_B)
		state->dsec_cmd.awgs[CX24117_DISEQC_BUWST] =
			CX24117_DISEQC_MINI_B;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int cx24117_get_pwiv(stwuct cx24117_pwiv **pwiv,
	stwuct i2c_adaptew *i2c, u8 cwient_addwess)
{
	int wet;

	mutex_wock(&cx24117_wist_mutex);
	wet = hybwid_tunew_wequest_state(stwuct cx24117_pwiv, (*pwiv),
		hybwid_tunew_instance_wist, i2c, cwient_addwess, "cx24117");
	mutex_unwock(&cx24117_wist_mutex);

	wetuwn wet;
}

static void cx24117_wewease_pwiv(stwuct cx24117_pwiv *pwiv)
{
	mutex_wock(&cx24117_wist_mutex);
	if (pwiv != NUWW)
		hybwid_tunew_wewease_state(pwiv);
	mutex_unwock(&cx24117_wist_mutex);
}

static void cx24117_wewease(stwuct dvb_fwontend *fe)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	dev_dbg(&state->pwiv->i2c->dev, "%s demod%d\n",
		__func__, state->demod);
	cx24117_wewease_pwiv(state->pwiv);
	kfwee(state);
}

static const stwuct dvb_fwontend_ops cx24117_ops;

stwuct dvb_fwontend *cx24117_attach(const stwuct cx24117_config *config,
	stwuct i2c_adaptew *i2c)
{
	stwuct cx24117_state *state = NUWW;
	stwuct cx24117_pwiv *pwiv = NUWW;
	int demod = 0;

	/* get the common data stwuct fow both demods */
	demod = cx24117_get_pwiv(&pwiv, i2c, config->demod_addwess);

	switch (demod) {
	case 0:
		dev_eww(&i2c->dev,
			"%s: Ewwow attaching fwontend %d\n",
			KBUIWD_MODNAME, demod);
		goto ewwow1;
	case 1:
		/* new pwiv instance */
		pwiv->i2c = i2c;
		pwiv->demod_addwess = config->demod_addwess;
		mutex_init(&pwiv->fe_wock);
		bweak;
	defauwt:
		/* existing pwiv instance */
		bweak;
	}

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct cx24117_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow2;

	state->demod = demod - 1;
	state->pwiv = pwiv;

	dev_info(&state->pwiv->i2c->dev,
		"%s: Attaching fwontend %d\n",
		KBUIWD_MODNAME, state->demod);

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &cx24117_ops,
		sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;

ewwow2:
	cx24117_wewease_pwiv(pwiv);
ewwow1:
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(cx24117_attach);

/*
 * Initiawise ow wake up device
 *
 * Powew config wiww weset and woad initiaw fiwmwawe if wequiwed
 */
static int cx24117_initfe(stwuct dvb_fwontend *fe)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	stwuct cx24117_cmd cmd;
	int wet;

	dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d\n",
		__func__, state->demod);

	mutex_wock(&state->pwiv->fe_wock);

	/* Set sweep mode off */
	cmd.awgs[0] = CMD_SET_SWEEPMODE;
	cmd.awgs[1] = (state->demod ? 1 : 0);
	cmd.awgs[2] = 0;
	cmd.wen = 3;
	wet = cx24117_cmd_execute_nowock(fe, &cmd);
	if (wet != 0)
		goto exit;

	wet = cx24117_diseqc_init(fe);
	if (wet != 0)
		goto exit;

	/* Set BEW contwow */
	cmd.awgs[0] = CMD_BEWCTWW;
	cmd.awgs[1] = (state->demod ? 1 : 0);
	cmd.awgs[2] = 0x10;
	cmd.awgs[3] = 0x10;
	cmd.wen = 4;
	wet = cx24117_cmd_execute_nowock(fe, &cmd);
	if (wet != 0)
		goto exit;

	/* Set WS cowwection (enabwe/disabwe) */
	cmd.awgs[0] = CMD_ENABWEWSCOWW;
	cmd.awgs[1] = (state->demod ? 1 : 0);
	cmd.awgs[2] = CX24117_OCC;
	cmd.wen = 3;
	wet = cx24117_cmd_execute_nowock(fe, &cmd);
	if (wet != 0)
		goto exit;

	/* Set GPIO diwection */
	/* Set as output - contwows WNB powew on/off */
	cmd.awgs[0] = CMD_SET_GPIODIW;
	cmd.awgs[1] = 0x30;
	cmd.awgs[2] = 0x30;
	cmd.wen = 3;
	wet = cx24117_cmd_execute_nowock(fe, &cmd);

exit:
	mutex_unwock(&state->pwiv->fe_wock);

	wetuwn wet;
}

/*
 * Put device to sweep
 */
static int cx24117_sweep(stwuct dvb_fwontend *fe)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	stwuct cx24117_cmd cmd;

	dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d\n",
		__func__, state->demod);

	/* Set sweep mode on */
	cmd.awgs[0] = CMD_SET_SWEEPMODE;
	cmd.awgs[1] = (state->demod ? 1 : 0);
	cmd.awgs[2] = 1;
	cmd.wen = 3;
	wetuwn cx24117_cmd_execute(fe, &cmd);
}

/* dvb-cowe towd us to tune, the tv pwopewty cache wiww be compwete,
 * it's safe fow is to puww vawues and use them fow tuning puwposes.
 */
static int cx24117_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct cx24117_cmd cmd;
	enum fe_status tunewstat;
	int i, status, wet, wetune = 1;
	u8 weg_cwkdiv, weg_watediv;

	dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d\n",
		__func__, state->demod);

	switch (c->dewivewy_system) {
	case SYS_DVBS:
		dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d DVB-S\n",
			__func__, state->demod);

		/* Onwy QPSK is suppowted fow DVB-S */
		if (c->moduwation != QPSK) {
			dev_dbg(&state->pwiv->i2c->dev,
				"%s() demod%d unsuppowted moduwation (%d)\n",
				__func__, state->demod, c->moduwation);
			wetuwn -EINVAW;
		}

		/* Piwot doesn't exist in DVB-S, tuwn bit off */
		state->dnxt.piwot_vaw = CX24117_PIWOT_OFF;

		/* DVB-S onwy suppowts 0.35 */
		state->dnxt.wowwoff_vaw = CX24117_WOWWOFF_035;
		bweak;

	case SYS_DVBS2:
		dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d DVB-S2\n",
			__func__, state->demod);

		/*
		 * NBC 8PSK/QPSK with DVB-S is suppowted fow DVB-S2,
		 * but not hawdwawe auto detection
		 */
		if (c->moduwation != PSK_8 && c->moduwation != QPSK) {
			dev_dbg(&state->pwiv->i2c->dev,
				"%s() demod%d unsuppowted moduwation (%d)\n",
				__func__, state->demod, c->moduwation);
			wetuwn -EOPNOTSUPP;
		}

		switch (c->piwot) {
		case PIWOT_AUTO:
			state->dnxt.piwot_vaw = CX24117_PIWOT_AUTO;
			bweak;
		case PIWOT_OFF:
			state->dnxt.piwot_vaw = CX24117_PIWOT_OFF;
			bweak;
		case PIWOT_ON:
			state->dnxt.piwot_vaw = CX24117_PIWOT_ON;
			bweak;
		defauwt:
			dev_dbg(&state->pwiv->i2c->dev,
				"%s() demod%d unsuppowted piwot mode (%d)\n",
				__func__, state->demod, c->piwot);
			wetuwn -EOPNOTSUPP;
		}

		switch (c->wowwoff) {
		case WOWWOFF_20:
			state->dnxt.wowwoff_vaw = CX24117_WOWWOFF_020;
			bweak;
		case WOWWOFF_25:
			state->dnxt.wowwoff_vaw = CX24117_WOWWOFF_025;
			bweak;
		case WOWWOFF_35:
			state->dnxt.wowwoff_vaw = CX24117_WOWWOFF_035;
			bweak;
		case WOWWOFF_AUTO:
			state->dnxt.wowwoff_vaw = CX24117_WOWWOFF_035;
			/* soft-auto wowwoff */
			wetune = 3;
			bweak;
		defauwt:
			dev_wawn(&state->pwiv->i2c->dev,
				"%s: demod%d unsuppowted wowwoff (%d)\n",
				KBUIWD_MODNAME, state->demod, c->wowwoff);
			wetuwn -EOPNOTSUPP;
		}
		bweak;

	defauwt:
		dev_wawn(&state->pwiv->i2c->dev,
			"%s: demod %d unsuppowted dewivewy system (%d)\n",
			KBUIWD_MODNAME, state->demod, c->dewivewy_system);
		wetuwn -EINVAW;
	}

	state->dnxt.dewsys = c->dewivewy_system;
	state->dnxt.moduwation = c->moduwation;
	state->dnxt.fwequency = c->fwequency;
	state->dnxt.piwot = c->piwot;
	state->dnxt.wowwoff = c->wowwoff;

	wet = cx24117_set_invewsion(state, c->invewsion);
	if (wet !=  0)
		wetuwn wet;

	wet = cx24117_set_fec(state,
		c->dewivewy_system, c->moduwation, c->fec_innew);
	if (wet !=  0)
		wetuwn wet;

	wet = cx24117_set_symbowwate(state, c->symbow_wate);
	if (wet !=  0)
		wetuwn wet;

	/* discawd the 'cuwwent' tuning pawametews and pwepawe to tune */
	cx24117_cwone_pawams(fe);

	dev_dbg(&state->pwiv->i2c->dev,
		"%s: dewsys      = %d\n", __func__, state->dcuw.dewsys);
	dev_dbg(&state->pwiv->i2c->dev,
		"%s: moduwation  = %d\n", __func__, state->dcuw.moduwation);
	dev_dbg(&state->pwiv->i2c->dev,
		"%s: fwequency   = %d\n", __func__, state->dcuw.fwequency);
	dev_dbg(&state->pwiv->i2c->dev,
		"%s: piwot       = %d (vaw = 0x%02x)\n", __func__,
		state->dcuw.piwot, state->dcuw.piwot_vaw);
	dev_dbg(&state->pwiv->i2c->dev,
		"%s: wetune      = %d\n", __func__, wetune);
	dev_dbg(&state->pwiv->i2c->dev,
		"%s: wowwoff     = %d (vaw = 0x%02x)\n", __func__,
		state->dcuw.wowwoff, state->dcuw.wowwoff_vaw);
	dev_dbg(&state->pwiv->i2c->dev,
		"%s: symbow_wate = %d\n", __func__, state->dcuw.symbow_wate);
	dev_dbg(&state->pwiv->i2c->dev,
		"%s: FEC         = %d (mask/vaw = 0x%02x/0x%02x)\n", __func__,
		state->dcuw.fec, state->dcuw.fec_mask, state->dcuw.fec_vaw);
	dev_dbg(&state->pwiv->i2c->dev,
		"%s: Invewsion   = %d (vaw = 0x%02x)\n", __func__,
		state->dcuw.invewsion, state->dcuw.invewsion_vaw);

	/* Pwepawe a tune wequest */
	cmd.awgs[0] = CMD_TUNEWEQUEST;

	/* demod */
	cmd.awgs[1] = state->demod;

	/* Fwequency */
	cmd.awgs[2] = (state->dcuw.fwequency & 0xff0000) >> 16;
	cmd.awgs[3] = (state->dcuw.fwequency & 0x00ff00) >> 8;
	cmd.awgs[4] = (state->dcuw.fwequency & 0x0000ff);

	/* Symbow Wate */
	cmd.awgs[5] = ((state->dcuw.symbow_wate / 1000) & 0xff00) >> 8;
	cmd.awgs[6] = ((state->dcuw.symbow_wate / 1000) & 0x00ff);

	/* Automatic Invewsion */
	cmd.awgs[7] = state->dcuw.invewsion_vaw;

	/* Moduwation / FEC / Piwot */
	cmd.awgs[8] = state->dcuw.fec_vaw | state->dcuw.piwot_vaw;

	cmd.awgs[9] = CX24117_SEAWCH_WANGE_KHZ >> 8;
	cmd.awgs[10] = CX24117_SEAWCH_WANGE_KHZ & 0xff;

	cmd.awgs[11] = state->dcuw.wowwoff_vaw;
	cmd.awgs[12] = state->dcuw.fec_mask;

	if (state->dcuw.symbow_wate > 30000000) {
		weg_watediv = 0x04;
		weg_cwkdiv = 0x02;
	} ewse if (state->dcuw.symbow_wate > 10000000) {
		weg_watediv = 0x06;
		weg_cwkdiv = 0x03;
	} ewse {
		weg_watediv = 0x0a;
		weg_cwkdiv = 0x05;
	}

	cmd.awgs[13] = weg_watediv;
	cmd.awgs[14] = weg_cwkdiv;

	cx24117_wwiteweg(state, (state->demod == 0) ?
		CX24117_WEG_CWKDIV0 : CX24117_WEG_CWKDIV1, weg_cwkdiv);
	cx24117_wwiteweg(state, (state->demod == 0) ?
		CX24117_WEG_WATEDIV0 : CX24117_WEG_WATEDIV1, weg_watediv);

	cmd.awgs[15] = CX24117_PNE;
	cmd.wen = 16;

	do {
		/* Weset status wegistew */
		status = cx24117_weadweg(state, (state->demod == 0) ?
			CX24117_WEG_SSTATUS0 : CX24117_WEG_SSTATUS1) &
			CX24117_SIGNAW_MASK;

		dev_dbg(&state->pwiv->i2c->dev,
			"%s() demod%d status_setfe = %02x\n",
			__func__, state->demod, status);

		cx24117_wwiteweg(state, (state->demod == 0) ?
			CX24117_WEG_SSTATUS0 : CX24117_WEG_SSTATUS1, status);

		/* Tune */
		wet = cx24117_cmd_execute(fe, &cmd);
		if (wet != 0)
			bweak;

		/*
		 * Wait fow up to 500 ms befowe wetwying
		 *
		 * If we awe abwe to tune then genewawwy it occuws within 100ms.
		 * If it takes wongew, twy a diffewent wowwoff setting.
		 */
		fow (i = 0; i < 50; i++) {
			cx24117_wead_status(fe, &tunewstat);
			status = tunewstat & (FE_HAS_SIGNAW | FE_HAS_SYNC);
			if (status == (FE_HAS_SIGNAW | FE_HAS_SYNC)) {
				dev_dbg(&state->pwiv->i2c->dev,
					"%s() demod%d tuned\n",
					__func__, state->demod);
				wetuwn 0;
			}
			msweep(20);
		}

		dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d not tuned\n",
			__func__, state->demod);

		/* twy next wowwoff vawue */
		if (state->dcuw.wowwoff == 3)
			cmd.awgs[11]--;

	} whiwe (--wetune);
	wetuwn -EINVAW;
}

static int cx24117_tune(stwuct dvb_fwontend *fe, boow we_tune,
	unsigned int mode_fwags, unsigned int *deway, enum fe_status *status)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;

	dev_dbg(&state->pwiv->i2c->dev, "%s() demod%d\n",
		__func__, state->demod);

	*deway = HZ / 5;
	if (we_tune) {
		int wet = cx24117_set_fwontend(fe);
		if (wet)
			wetuwn wet;
	}
	wetuwn cx24117_wead_status(fe, status);
}

static enum dvbfe_awgo cx24117_get_awgo(stwuct dvb_fwontend *fe)
{
	wetuwn DVBFE_AWGO_HW;
}

static int cx24117_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *c)
{
	stwuct cx24117_state *state = fe->demoduwatow_pwiv;
	stwuct cx24117_cmd cmd;
	u8 weg, st, inv;
	int wet, idx;
	unsigned int fweq;
	showt swate_os, fweq_os;

	u8 buf[0x1f-4];

	/* Wead cuwwent tune pawametews */
	cmd.awgs[0] = CMD_GETCTWACC;
	cmd.awgs[1] = (u8) state->demod;
	cmd.wen = 2;
	wet = cx24117_cmd_execute(fe, &cmd);
	if (wet != 0)
		wetuwn wet;

	/* wead aww wequiwed wegs at once */
	weg = (state->demod == 0) ? CX24117_WEG_FWEQ3_0 : CX24117_WEG_FWEQ3_1;
	wet = cx24117_weadwegN(state, weg, buf, 0x1f-4);
	if (wet != 0)
		wetuwn wet;

	st = buf[5];

	/* get spectwaw invewsion */
	inv = (((state->demod == 0) ? ~st : st) >> 6) & 1;
	if (inv == 0)
		c->invewsion = INVEWSION_OFF;
	ewse
		c->invewsion = INVEWSION_ON;

	/* moduwation and fec */
	idx = st & 0x3f;
	if (c->dewivewy_system == SYS_DVBS2) {
		if (idx > 11)
			idx += 9;
		ewse
			idx += 7;
	}

	c->moduwation = cx24117_modfec_modes[idx].moduwation;
	c->fec_innew = cx24117_modfec_modes[idx].fec;

	/* fwequency */
	fweq = (buf[0] << 16) | (buf[1] << 8) | buf[2];
	fweq_os = (buf[8] << 8) | buf[9];
	c->fwequency = fweq + fweq_os;

	/* symbow wate */
	swate_os = (buf[10] << 8) | buf[11];
	c->symbow_wate = -1000 * swate_os + state->dcuw.symbow_wate;
	wetuwn 0;
}

static const stwuct dvb_fwontend_ops cx24117_ops = {
	.dewsys = { SYS_DVBS, SYS_DVBS2 },
	.info = {
		.name = "Conexant CX24117/CX24132",
		.fwequency_min_hz =  950 * MHz,
		.fwequency_max_hz = 2150 * MHz,
		.fwequency_stepsize_hz = 1011 * kHz,
		.fwequency_towewance_hz = 5 * MHz,
		.symbow_wate_min = 1000000,
		.symbow_wate_max = 45000000,
		.caps = FE_CAN_INVEWSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 | FE_CAN_FEC_5_6 | FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_2G_MODUWATION |
			FE_CAN_QPSK | FE_CAN_WECOVEW
	},

	.wewease = cx24117_wewease,

	.init = cx24117_initfe,
	.sweep = cx24117_sweep,
	.wead_status = cx24117_wead_status,
	.wead_bew = cx24117_wead_bew,
	.wead_signaw_stwength = cx24117_wead_signaw_stwength,
	.wead_snw = cx24117_wead_snw,
	.wead_ucbwocks = cx24117_wead_ucbwocks,
	.set_tone = cx24117_set_tone,
	.set_vowtage = cx24117_set_vowtage,
	.diseqc_send_mastew_cmd = cx24117_send_diseqc_msg,
	.diseqc_send_buwst = cx24117_diseqc_send_buwst,
	.get_fwontend_awgo = cx24117_get_awgo,
	.tune = cx24117_tune,

	.set_fwontend = cx24117_set_fwontend,
	.get_fwontend = cx24117_get_fwontend,
};


MODUWE_DESCWIPTION("DVB Fwontend moduwe fow Conexant cx24117/cx24132 hawdwawe");
MODUWE_AUTHOW("Wuis Awves (wjawvs@gmaiw.com)");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.1");
MODUWE_FIWMWAWE(CX24117_DEFAUWT_FIWMWAWE);

