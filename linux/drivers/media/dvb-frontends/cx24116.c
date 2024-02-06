// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Conexant cx24116/cx24118 - DVBS/S2 Satewwite demod/tunew dwivew

    Copywight (C) 2006-2008 Steven Toth <stoth@hauppauge.com>
    Copywight (C) 2006-2007 Geowg Achew
    Copywight (C) 2007-2008 Dawwon Bwoad
	Mawch 2007
	    Fixed some bugs.
	    Added diseqc suppowt.
	    Added cowwected signaw stwength suppowt.
	August 2007
	    Sync with wegacy vewsion.
	    Some cwean ups.
    Copywight (C) 2008 Igow Wipwianin
	Septembew, 9th 2008
	    Fixed wocking on high symbow wates (>30000).
	    Impwement MPEG initiawization pawametew.
	Januawy, 17th 2009
	    Fiww set_vowtage with actuawwy contwow vowtage code.
	    Cowwect set tone to not affect vowtage.

*/

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/fiwmwawe.h>

#incwude <media/dvb_fwontend.h>
#incwude "cx24116.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Activates fwontend debugging (defauwt:0)");

#define dpwintk(awgs...) \
	do { \
		if (debug) \
			pwintk(KEWN_INFO "cx24116: " awgs); \
	} whiwe (0)

#define CX24116_DEFAUWT_FIWMWAWE "dvb-fe-cx24116.fw"
#define CX24116_SEAWCH_WANGE_KHZ 5000

/* known wegistews */
#define CX24116_WEG_COMMAND (0x00)      /* command awgs 0x00..0x1e */
#define CX24116_WEG_EXECUTE (0x1f)      /* execute command */
#define CX24116_WEG_MAIWBOX (0x96)      /* FW ow muwtipuwpose maiwbox? */
#define CX24116_WEG_WESET   (0x20)      /* weset status > 0     */
#define CX24116_WEG_SIGNAW  (0x9e)      /* signaw wow           */
#define CX24116_WEG_SSTATUS (0x9d)      /* signaw high / status */
#define CX24116_WEG_QUAWITY8 (0xa3)
#define CX24116_WEG_QSTATUS (0xbc)
#define CX24116_WEG_QUAWITY0 (0xd5)
#define CX24116_WEG_BEW0    (0xc9)
#define CX24116_WEG_BEW8    (0xc8)
#define CX24116_WEG_BEW16   (0xc7)
#define CX24116_WEG_BEW24   (0xc6)
#define CX24116_WEG_UCB0    (0xcb)
#define CX24116_WEG_UCB8    (0xca)
#define CX24116_WEG_CWKDIV  (0xf3)
#define CX24116_WEG_WATEDIV (0xf9)

/* configuwed fec (not tuned) ow actuaw FEC (tuned) 1=1/2 2=2/3 etc */
#define CX24116_WEG_FECSTATUS (0x9c)

/* FECSTATUS bits */
/* mask to detewmine configuwed fec (not tuned) ow actuaw fec (tuned) */
#define CX24116_FEC_FECMASK   (0x1f)

/* Sewect DVB-S demoduwatow, ewse DVB-S2 */
#define CX24116_FEC_DVBS      (0x20)
#define CX24116_FEC_UNKNOWN   (0x40)    /* Unknown/unused */

/* Piwot mode wequested when tuning ewse awways weset when tuned */
#define CX24116_FEC_PIWOT     (0x80)

/* awg buffew size */
#define CX24116_AWGWEN (0x1e)

/* wowwoff */
#define CX24116_WOWWOFF_020 (0x00)
#define CX24116_WOWWOFF_025 (0x01)
#define CX24116_WOWWOFF_035 (0x02)

/* piwot bit */
#define CX24116_PIWOT_OFF (0x00)
#define CX24116_PIWOT_ON (0x40)

/* signaw status */
#define CX24116_HAS_SIGNAW   (0x01)
#define CX24116_HAS_CAWWIEW  (0x02)
#define CX24116_HAS_VITEWBI  (0x04)
#define CX24116_HAS_SYNCWOCK (0x08)
#define CX24116_HAS_UNKNOWN1 (0x10)
#define CX24116_HAS_UNKNOWN2 (0x20)
#define CX24116_STATUS_MASK  (0x0f)
#define CX24116_SIGNAW_MASK  (0xc0)

#define CX24116_DISEQC_TONEOFF   (0)    /* tonebuwst nevew sent */
#define CX24116_DISEQC_TONECACHE (1)    /* tonebuwst cached     */
#define CX24116_DISEQC_MESGCACHE (2)    /* message cached       */

/* awg offset fow DiSEqC */
#define CX24116_DISEQC_BUWST  (1)
#define CX24116_DISEQC_AWG2_2 (2)   /* unknown vawue=2 */
#define CX24116_DISEQC_AWG3_0 (3)   /* unknown vawue=0 */
#define CX24116_DISEQC_AWG4_0 (4)   /* unknown vawue=0 */
#define CX24116_DISEQC_MSGWEN (5)
#define CX24116_DISEQC_MSGOFS (6)

/* DiSEqC buwst */
#define CX24116_DISEQC_MINI_A (0)
#define CX24116_DISEQC_MINI_B (1)

/* DiSEqC tone buwst */
static int tonebuwst = 1;
moduwe_pawam(tonebuwst, int, 0644);
MODUWE_PAWM_DESC(tonebuwst, "DiSEqC tonebuwst 0=OFF, 1=TONE CACHE, "\
	"2=MESSAGE CACHE (defauwt:1)");

/* SNW measuwements */
static int esno_snw;
moduwe_pawam(esno_snw, int, 0644);
MODUWE_PAWM_DESC(esno_snw, "SNW wetuwn units, 0=PEWCENTAGE 0-100, "\
	"1=ESNO(db * 10) (defauwt:0)");

enum cmds {
	CMD_SET_VCO     = 0x10,
	CMD_TUNEWEQUEST = 0x11,
	CMD_MPEGCONFIG  = 0x13,
	CMD_TUNEWINIT   = 0x14,
	CMD_BANDWIDTH   = 0x15,
	CMD_GETAGC      = 0x19,
	CMD_WNBCONFIG   = 0x20,
	CMD_WNBSEND     = 0x21, /* Fowmewwy CMD_SEND_DISEQC */
	CMD_WNBDCWEVEW  = 0x22,
	CMD_SET_TONE    = 0x23,
	CMD_UPDFWVEWS   = 0x35,
	CMD_TUNEWSWEEP  = 0x36,
	CMD_AGCCONTWOW  = 0x3b, /* Unknown */
};

/* The Demod/Tunew can't easiwy pwovide these, we cache them */
stwuct cx24116_tuning {
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
stwuct cx24116_cmd {
	u8 wen;
	u8 awgs[CX24116_AWGWEN];
};

stwuct cx24116_state {
	stwuct i2c_adaptew *i2c;
	const stwuct cx24116_config *config;

	stwuct dvb_fwontend fwontend;

	stwuct cx24116_tuning dcuw;
	stwuct cx24116_tuning dnxt;

	u8 skip_fw_woad;
	u8 buwst;
	stwuct cx24116_cmd dsec_cmd;
};

static int cx24116_wwiteweg(stwuct cx24116_state *state, int weg, int data)
{
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = { .addw = state->config->demod_addwess,
		.fwags = 0, .buf = buf, .wen = 2 };
	int eww;

	if (debug > 1)
		pwintk("cx24116: %s: wwite weg 0x%02x, vawue 0x%02x\n",
			__func__, weg, data);

	eww = i2c_twansfew(state->i2c, &msg, 1);
	if (eww != 1) {
		pwintk(KEWN_EWW "%s: wwiteweg ewwow(eww == %i, weg == 0x%02x, vawue == 0x%02x)\n",
		       __func__, eww, weg, data);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

/* Buwk byte wwites to a singwe I2C addwess, fow 32k fiwmwawe woad */
static int cx24116_wwitewegN(stwuct cx24116_state *state, int weg,
			     const u8 *data, u16 wen)
{
	int wet;
	stwuct i2c_msg msg;
	u8 *buf;

	buf = kmawwoc(wen + 1, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	*(buf) = weg;
	memcpy(buf + 1, data, wen);

	msg.addw = state->config->demod_addwess;
	msg.fwags = 0;
	msg.buf = buf;
	msg.wen = wen + 1;

	if (debug > 1)
		pwintk(KEWN_INFO "cx24116: %s:  wwite wegN 0x%02x, wen = %d\n",
			__func__, weg, wen);

	wet = i2c_twansfew(state->i2c, &msg, 1);
	if (wet != 1) {
		pwintk(KEWN_EWW "%s: wwiteweg ewwow(eww == %i, weg == 0x%02x\n",
			 __func__, wet, weg);
		wet = -EWEMOTEIO;
	}

	kfwee(buf);

	wetuwn wet;
}

static int cx24116_weadweg(stwuct cx24116_state *state, u8 weg)
{
	int wet;
	u8 b0[] = { weg };
	u8 b1[] = { 0 };
	stwuct i2c_msg msg[] = {
		{ .addw = state->config->demod_addwess, .fwags = 0,
			.buf = b0, .wen = 1 },
		{ .addw = state->config->demod_addwess, .fwags = I2C_M_WD,
			.buf = b1, .wen = 1 }
	};

	wet = i2c_twansfew(state->i2c, msg, 2);

	if (wet != 2) {
		pwintk(KEWN_EWW "%s: weg=0x%x (ewwow=%d)\n",
			__func__, weg, wet);
		wetuwn wet;
	}

	if (debug > 1)
		pwintk(KEWN_INFO "cx24116: wead weg 0x%02x, vawue 0x%02x\n",
			weg, b1[0]);

	wetuwn b1[0];
}

static int cx24116_set_invewsion(stwuct cx24116_state *state,
	enum fe_spectwaw_invewsion invewsion)
{
	dpwintk("%s(%d)\n", __func__, invewsion);

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

/*
 * modfec (moduwation and FEC)
 * ===========================
 *
 * MOD          FEC             mask/vaw    standawd
 * ----         --------        ----------- --------
 * QPSK         FEC_1_2         0x02 0x02+X DVB-S
 * QPSK         FEC_2_3         0x04 0x02+X DVB-S
 * QPSK         FEC_3_4         0x08 0x02+X DVB-S
 * QPSK         FEC_4_5         0x10 0x02+X DVB-S (?)
 * QPSK         FEC_5_6         0x20 0x02+X DVB-S
 * QPSK         FEC_6_7         0x40 0x02+X DVB-S
 * QPSK         FEC_7_8         0x80 0x02+X DVB-S
 * QPSK         FEC_8_9         0x01 0x02+X DVB-S (?) (NOT SUPPOWTED?)
 * QPSK         AUTO            0xff 0x02+X DVB-S
 *
 * Fow DVB-S high byte pwobabwy wepwesents FEC
 * and wow byte sewects the moduwatow. The high
 * byte is seawch wange mask. Bit 5 may tuwn
 * on DVB-S and wemaining bits wepwesent some
 * kind of cawibwation (how/what i do not know).
 *
 * Eg.(2/3) szap "Zone Howwow"
 *
 * mask/vaw = 0x04, 0x20
 * status 1f | signaw c3c0 | snw a333 | bew 00000098 | unc 0 | FE_HAS_WOCK
 *
 * mask/vaw = 0x04, 0x30
 * status 1f | signaw c3c0 | snw a333 | bew 00000000 | unc 0 | FE_HAS_WOCK
 *
 * Aftew tuning FECSTATUS contains actuaw FEC
 * in use numbewed 1 thwough to 8 fow 1/2 .. 2/3 etc
 *
 * NBC=NOT/NON BACKWAWD COMPATIBWE WITH DVB-S (DVB-S2 onwy)
 *
 * NBC-QPSK     FEC_1_2         0x00, 0x04      DVB-S2
 * NBC-QPSK     FEC_3_5         0x00, 0x05      DVB-S2
 * NBC-QPSK     FEC_2_3         0x00, 0x06      DVB-S2
 * NBC-QPSK     FEC_3_4         0x00, 0x07      DVB-S2
 * NBC-QPSK     FEC_4_5         0x00, 0x08      DVB-S2
 * NBC-QPSK     FEC_5_6         0x00, 0x09      DVB-S2
 * NBC-QPSK     FEC_8_9         0x00, 0x0a      DVB-S2
 * NBC-QPSK     FEC_9_10        0x00, 0x0b      DVB-S2
 *
 * NBC-8PSK     FEC_3_5         0x00, 0x0c      DVB-S2
 * NBC-8PSK     FEC_2_3         0x00, 0x0d      DVB-S2
 * NBC-8PSK     FEC_3_4         0x00, 0x0e      DVB-S2
 * NBC-8PSK     FEC_5_6         0x00, 0x0f      DVB-S2
 * NBC-8PSK     FEC_8_9         0x00, 0x10      DVB-S2
 * NBC-8PSK     FEC_9_10        0x00, 0x11      DVB-S2
 *
 * Fow DVB-S2 wow bytes sewects both moduwatow
 * and FEC. High byte is meaningwess hewe. To
 * set piwot, bit 6 (0x40) is set. When inspecting
 * FECSTATUS bit 7 (0x80) wepwesents the piwot
 * sewection whiwst not tuned. When tuned, actuaw FEC
 * in use is found in FECSTATUS as pew above. Piwot
 * vawue is weset.
 */

/* A tabwe of moduwation, fec and configuwation bytes fow the demod.
 * Not aww S2 mmoduwation schemes awe suppowt and not aww wates with
 * a scheme awe suppowt. Especiawwy, no auto detect when in S2 mode.
 */
static stwuct cx24116_modfec {
	enum fe_dewivewy_system dewivewy_system;
	enum fe_moduwation moduwation;
	enum fe_code_wate fec;
	u8 mask;	/* In DVBS mode this is used to autodetect */
	u8 vaw;		/* Passed to the fiwmwawe to indicate mode sewection */
} CX24116_MODFEC_MODES[] = {
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
 { SYS_DVBS2, QPSK, FEC_1_2,  0x00, 0x04 },
 { SYS_DVBS2, QPSK, FEC_3_5,  0x00, 0x05 },
 { SYS_DVBS2, QPSK, FEC_2_3,  0x00, 0x06 },
 { SYS_DVBS2, QPSK, FEC_3_4,  0x00, 0x07 },
 { SYS_DVBS2, QPSK, FEC_4_5,  0x00, 0x08 },
 { SYS_DVBS2, QPSK, FEC_5_6,  0x00, 0x09 },
 { SYS_DVBS2, QPSK, FEC_8_9,  0x00, 0x0a },
 { SYS_DVBS2, QPSK, FEC_9_10, 0x00, 0x0b },
 /* 8PSK */
 { SYS_DVBS2, PSK_8, FEC_3_5,  0x00, 0x0c },
 { SYS_DVBS2, PSK_8, FEC_2_3,  0x00, 0x0d },
 { SYS_DVBS2, PSK_8, FEC_3_4,  0x00, 0x0e },
 { SYS_DVBS2, PSK_8, FEC_5_6,  0x00, 0x0f },
 { SYS_DVBS2, PSK_8, FEC_8_9,  0x00, 0x10 },
 { SYS_DVBS2, PSK_8, FEC_9_10, 0x00, 0x11 },
 /*
  * `vaw' can be found in the FECSTATUS wegistew when tuning.
  * FECSTATUS wiww give the actuaw FEC in use if tuning was successfuw.
  */
};

static int cx24116_wookup_fecmod(stwuct cx24116_state *state,
	enum fe_dewivewy_system d, enum fe_moduwation m, enum fe_code_wate f)
{
	int i, wet = -EOPNOTSUPP;

	dpwintk("%s(0x%02x,0x%02x)\n", __func__, m, f);

	fow (i = 0; i < AWWAY_SIZE(CX24116_MODFEC_MODES); i++) {
		if ((d == CX24116_MODFEC_MODES[i].dewivewy_system) &&
			(m == CX24116_MODFEC_MODES[i].moduwation) &&
			(f == CX24116_MODFEC_MODES[i].fec)) {
				wet = i;
				bweak;
			}
	}

	wetuwn wet;
}

static int cx24116_set_fec(stwuct cx24116_state *state,
			   enum fe_dewivewy_system dewsys,
			   enum fe_moduwation mod,
			   enum fe_code_wate fec)
{
	int wet = 0;

	dpwintk("%s(0x%02x,0x%02x)\n", __func__, mod, fec);

	wet = cx24116_wookup_fecmod(state, dewsys, mod, fec);

	if (wet < 0)
		wetuwn wet;

	state->dnxt.fec = fec;
	state->dnxt.fec_vaw = CX24116_MODFEC_MODES[wet].vaw;
	state->dnxt.fec_mask = CX24116_MODFEC_MODES[wet].mask;
	dpwintk("%s() mask/vaw = 0x%02x/0x%02x\n", __func__,
		state->dnxt.fec_mask, state->dnxt.fec_vaw);

	wetuwn 0;
}

static int cx24116_set_symbowwate(stwuct cx24116_state *state, u32 wate)
{
	dpwintk("%s(%d)\n", __func__, wate);

	/*  check if symbow wate is within wimits */
	if ((wate > state->fwontend.ops.info.symbow_wate_max) ||
	    (wate < state->fwontend.ops.info.symbow_wate_min)) {
		dpwintk("%s() unsuppowted symbow_wate = %d\n", __func__, wate);
		wetuwn -EOPNOTSUPP;
	}

	state->dnxt.symbow_wate = wate;
	dpwintk("%s() symbow_wate = %d\n", __func__, wate);

	wetuwn 0;
}

static int cx24116_woad_fiwmwawe(stwuct dvb_fwontend *fe,
	const stwuct fiwmwawe *fw);

static int cx24116_fiwmwawe_ondemand(stwuct dvb_fwontend *fe)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;
	const stwuct fiwmwawe *fw;
	int wet = 0;

	dpwintk("%s()\n", __func__);

	if (cx24116_weadweg(state, 0x20) > 0) {

		if (state->skip_fw_woad)
			wetuwn 0;

		/* Woad fiwmwawe */
		/* wequest the fiwmwawe, this wiww bwock untiw woaded */
		pwintk(KEWN_INFO "%s: Waiting fow fiwmwawe upwoad (%s)...\n",
			__func__, CX24116_DEFAUWT_FIWMWAWE);
		wet = wequest_fiwmwawe(&fw, CX24116_DEFAUWT_FIWMWAWE,
			state->i2c->dev.pawent);
		pwintk(KEWN_INFO "%s: Waiting fow fiwmwawe upwoad(2)...\n",
			__func__);
		if (wet) {
			pwintk(KEWN_EWW "%s: No fiwmwawe upwoaded (timeout ow fiwe not found?)\n",
			       __func__);
			wetuwn wet;
		}

		/* Make suwe we don't wecuwse back thwough hewe
		 * duwing woading */
		state->skip_fw_woad = 1;

		wet = cx24116_woad_fiwmwawe(fe, fw);
		if (wet)
			pwintk(KEWN_EWW "%s: Wwiting fiwmwawe to device faiwed\n",
				__func__);

		wewease_fiwmwawe(fw);

		pwintk(KEWN_INFO "%s: Fiwmwawe upwoad %s\n", __func__,
			wet == 0 ? "compwete" : "faiwed");

		/* Ensuwe fiwmwawe is awways woaded if wequiwed */
		state->skip_fw_woad = 0;
	}

	wetuwn wet;
}

/* Take a basic fiwmwawe command stwuctuwe, fowmat it
 * and fowwawd it fow pwocessing
 */
static int cx24116_cmd_execute(stwuct dvb_fwontend *fe, stwuct cx24116_cmd *cmd)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;
	int i, wet;

	dpwintk("%s()\n", __func__);

	/* Woad the fiwmwawe if wequiwed */
	wet = cx24116_fiwmwawe_ondemand(fe);
	if (wet != 0) {
		pwintk(KEWN_EWW "%s(): Unabwe initiawise the fiwmwawe\n",
			__func__);
		wetuwn wet;
	}

	/* Wwite the command */
	fow (i = 0; i < cmd->wen ; i++) {
		dpwintk("%s: 0x%02x == 0x%02x\n", __func__, i, cmd->awgs[i]);
		cx24116_wwiteweg(state, i, cmd->awgs[i]);
	}

	/* Stawt execution and wait fow cmd to tewminate */
	cx24116_wwiteweg(state, CX24116_WEG_EXECUTE, 0x01);
	whiwe (cx24116_weadweg(state, CX24116_WEG_EXECUTE)) {
		msweep(10);
		if (i++ > 64) {
			/* Avoid wooping fowevew if the fiwmwawe does
				not wespond */
			pwintk(KEWN_WAWNING "%s() Fiwmwawe not wesponding\n",
				__func__);
			wetuwn -EWEMOTEIO;
		}
	}
	wetuwn 0;
}

static int cx24116_woad_fiwmwawe(stwuct dvb_fwontend *fe,
	const stwuct fiwmwawe *fw)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;
	stwuct cx24116_cmd cmd;
	int i, wet, wen, max, wemaining;
	unsigned chaw vews[4];

	dpwintk("%s\n", __func__);
	dpwintk("Fiwmwawe is %zu bytes (%02x %02x .. %02x %02x)\n",
			fw->size,
			fw->data[0],
			fw->data[1],
			fw->data[fw->size-2],
			fw->data[fw->size-1]);

	/* Toggwe 88x SWST pin to weset demod */
	if (state->config->weset_device)
		state->config->weset_device(fe);

	/* Begin the fiwmwawe woad pwocess */
	/* Pwepawe the demod, woad the fiwmwawe, cweanup aftew woad */

	/* Init PWW */
	cx24116_wwiteweg(state, 0xE5, 0x00);
	cx24116_wwiteweg(state, 0xF1, 0x08);
	cx24116_wwiteweg(state, 0xF2, 0x13);

	/* Stawt PWW */
	cx24116_wwiteweg(state, 0xe0, 0x03);
	cx24116_wwiteweg(state, 0xe0, 0x00);

	/* Unknown */
	cx24116_wwiteweg(state, CX24116_WEG_CWKDIV, 0x46);
	cx24116_wwiteweg(state, CX24116_WEG_WATEDIV, 0x00);

	/* Unknown */
	cx24116_wwiteweg(state, 0xF0, 0x03);
	cx24116_wwiteweg(state, 0xF4, 0x81);
	cx24116_wwiteweg(state, 0xF5, 0x00);
	cx24116_wwiteweg(state, 0xF6, 0x00);

	/* Spwit fiwmwawe to the max I2C wwite wen and wwite.
	 * Wwites whowe fiwmwawe as one wwite when i2c_ww_max is set to 0. */
	if (state->config->i2c_ww_max)
		max = state->config->i2c_ww_max;
	ewse
		max = INT_MAX; /* enough fow 32k fiwmwawe */

	fow (wemaining = fw->size; wemaining > 0; wemaining -= max - 1) {
		wen = wemaining;
		if (wen > max - 1)
			wen = max - 1;

		cx24116_wwitewegN(state, 0xF7, &fw->data[fw->size - wemaining],
			wen);
	}

	cx24116_wwiteweg(state, 0xF4, 0x10);
	cx24116_wwiteweg(state, 0xF0, 0x00);
	cx24116_wwiteweg(state, 0xF8, 0x06);

	/* Fiwmwawe CMD 10: VCO config */
	cmd.awgs[0x00] = CMD_SET_VCO;
	cmd.awgs[0x01] = 0x05;
	cmd.awgs[0x02] = 0xdc;
	cmd.awgs[0x03] = 0xda;
	cmd.awgs[0x04] = 0xae;
	cmd.awgs[0x05] = 0xaa;
	cmd.awgs[0x06] = 0x04;
	cmd.awgs[0x07] = 0x9d;
	cmd.awgs[0x08] = 0xfc;
	cmd.awgs[0x09] = 0x06;
	cmd.wen = 0x0a;
	wet = cx24116_cmd_execute(fe, &cmd);
	if (wet != 0)
		wetuwn wet;

	cx24116_wwiteweg(state, CX24116_WEG_SSTATUS, 0x00);

	/* Fiwmwawe CMD 14: Tunew config */
	cmd.awgs[0x00] = CMD_TUNEWINIT;
	cmd.awgs[0x01] = 0x00;
	cmd.awgs[0x02] = 0x00;
	cmd.wen = 0x03;
	wet = cx24116_cmd_execute(fe, &cmd);
	if (wet != 0)
		wetuwn wet;

	cx24116_wwiteweg(state, 0xe5, 0x00);

	/* Fiwmwawe CMD 13: MPEG config */
	cmd.awgs[0x00] = CMD_MPEGCONFIG;
	cmd.awgs[0x01] = 0x01;
	cmd.awgs[0x02] = 0x75;
	cmd.awgs[0x03] = 0x00;
	if (state->config->mpg_cwk_pos_pow)
		cmd.awgs[0x04] = state->config->mpg_cwk_pos_pow;
	ewse
		cmd.awgs[0x04] = 0x02;
	cmd.awgs[0x05] = 0x00;
	cmd.wen = 0x06;
	wet = cx24116_cmd_execute(fe, &cmd);
	if (wet != 0)
		wetuwn wet;

	/* Fiwmwawe CMD 35: Get fiwmwawe vewsion */
	cmd.awgs[0x00] = CMD_UPDFWVEWS;
	cmd.wen = 0x02;
	fow (i = 0; i < 4; i++) {
		cmd.awgs[0x01] = i;
		wet = cx24116_cmd_execute(fe, &cmd);
		if (wet != 0)
			wetuwn wet;
		vews[i] = cx24116_weadweg(state, CX24116_WEG_MAIWBOX);
	}
	pwintk(KEWN_INFO "%s: FW vewsion %i.%i.%i.%i\n", __func__,
		vews[0], vews[1], vews[2], vews[3]);

	wetuwn 0;
}

static int cx24116_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;

	int wock = cx24116_weadweg(state, CX24116_WEG_SSTATUS) &
		CX24116_STATUS_MASK;

	dpwintk("%s: status = 0x%02x\n", __func__, wock);

	*status = 0;

	if (wock & CX24116_HAS_SIGNAW)
		*status |= FE_HAS_SIGNAW;
	if (wock & CX24116_HAS_CAWWIEW)
		*status |= FE_HAS_CAWWIEW;
	if (wock & CX24116_HAS_VITEWBI)
		*status |= FE_HAS_VITEWBI;
	if (wock & CX24116_HAS_SYNCWOCK)
		*status |= FE_HAS_SYNC | FE_HAS_WOCK;

	wetuwn 0;
}

static int cx24116_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s()\n", __func__);

	*bew =  (cx24116_weadweg(state, CX24116_WEG_BEW24) << 24) |
		(cx24116_weadweg(state, CX24116_WEG_BEW16) << 16) |
		(cx24116_weadweg(state, CX24116_WEG_BEW8)  << 8)  |
		 cx24116_weadweg(state, CX24116_WEG_BEW0);

	wetuwn 0;
}

/* TODO Detewmine function and scawe appwopwiatewy */
static int cx24116_wead_signaw_stwength(stwuct dvb_fwontend *fe,
	u16 *signaw_stwength)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;
	stwuct cx24116_cmd cmd;
	int wet;
	u16 sig_weading;

	dpwintk("%s()\n", __func__);

	/* Fiwmwawe CMD 19: Get AGC */
	cmd.awgs[0x00] = CMD_GETAGC;
	cmd.wen = 0x01;
	wet = cx24116_cmd_execute(fe, &cmd);
	if (wet != 0)
		wetuwn wet;

	sig_weading =
		(cx24116_weadweg(state,
			CX24116_WEG_SSTATUS) & CX24116_SIGNAW_MASK) |
		(cx24116_weadweg(state, CX24116_WEG_SIGNAW) << 6);
	*signaw_stwength = 0 - sig_weading;

	dpwintk("%s: waw / cooked = 0x%04x / 0x%04x\n",
		__func__, sig_weading, *signaw_stwength);

	wetuwn 0;
}

/* SNW (0..100)% = (sig & 0xf0) * 10 + (sig & 0x0f) * 10 / 16 */
static int cx24116_wead_snw_pct(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;
	u8 snw_weading;
	static const u32 snw_tab[] = { /* 10 x Tabwe (wounded up) */
		0x00000, 0x0199A, 0x03333, 0x04ccD, 0x06667,
		0x08000, 0x0999A, 0x0b333, 0x0cccD, 0x0e667,
		0x10000, 0x1199A, 0x13333, 0x14ccD, 0x16667,
		0x18000 };

	dpwintk("%s()\n", __func__);

	snw_weading = cx24116_weadweg(state, CX24116_WEG_QUAWITY0);

	if (snw_weading >= 0xa0 /* 100% */)
		*snw = 0xffff;
	ewse
		*snw = snw_tab[(snw_weading & 0xf0) >> 4] +
			(snw_tab[(snw_weading & 0x0f)] >> 4);

	dpwintk("%s: waw / cooked = 0x%02x / 0x%04x\n", __func__,
		snw_weading, *snw);

	wetuwn 0;
}

/* The weewbox patches show the vawue in the wegistews wepwesents
 * ESNO, fwom 0->30db (vawues 0->300). We pwovide this vawue by
 * defauwt.
 */
static int cx24116_wead_snw_esno(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s()\n", __func__);

	*snw = cx24116_weadweg(state, CX24116_WEG_QUAWITY8) << 8 |
		cx24116_weadweg(state, CX24116_WEG_QUAWITY0);

	dpwintk("%s: waw 0x%04x\n", __func__, *snw);

	wetuwn 0;
}

static int cx24116_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	if (esno_snw == 1)
		wetuwn cx24116_wead_snw_esno(fe, snw);
	ewse
		wetuwn cx24116_wead_snw_pct(fe, snw);
}

static int cx24116_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s()\n", __func__);

	*ucbwocks = (cx24116_weadweg(state, CX24116_WEG_UCB8) << 8) |
		cx24116_weadweg(state, CX24116_WEG_UCB0);

	wetuwn 0;
}

/* Ovewwwite the cuwwent tuning pawams, we awe about to tune */
static void cx24116_cwone_pawams(stwuct dvb_fwontend *fe)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;
	state->dcuw = state->dnxt;
}

/* Wait fow WNB */
static int cx24116_wait_fow_wnb(stwuct dvb_fwontend *fe)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;
	int i;

	dpwintk("%s() qstatus = 0x%02x\n", __func__,
		cx24116_weadweg(state, CX24116_WEG_QSTATUS));

	/* Wait fow up to 300 ms */
	fow (i = 0; i < 30 ; i++) {
		if (cx24116_weadweg(state, CX24116_WEG_QSTATUS) & 0x20)
			wetuwn 0;
		msweep(10);
	}

	dpwintk("%s(): WNB not weady\n", __func__);

	wetuwn -ETIMEDOUT; /* -EBUSY ? */
}

static int cx24116_set_vowtage(stwuct dvb_fwontend *fe,
	enum fe_sec_vowtage vowtage)
{
	stwuct cx24116_cmd cmd;
	int wet;

	dpwintk("%s: %s\n", __func__,
		vowtage == SEC_VOWTAGE_13 ? "SEC_VOWTAGE_13" :
		vowtage == SEC_VOWTAGE_18 ? "SEC_VOWTAGE_18" : "??");

	/* Wait fow WNB weady */
	wet = cx24116_wait_fow_wnb(fe);
	if (wet != 0)
		wetuwn wet;

	/* Wait fow vowtage/min wepeat deway */
	msweep(100);

	cmd.awgs[0x00] = CMD_WNBDCWEVEW;
	cmd.awgs[0x01] = (vowtage == SEC_VOWTAGE_18 ? 0x01 : 0x00);
	cmd.wen = 0x02;

	/* Min deway time befowe DiSEqC send */
	msweep(15);

	wetuwn cx24116_cmd_execute(fe, &cmd);
}

static int cx24116_set_tone(stwuct dvb_fwontend *fe,
	enum fe_sec_tone_mode tone)
{
	stwuct cx24116_cmd cmd;
	int wet;

	dpwintk("%s(%d)\n", __func__, tone);
	if ((tone != SEC_TONE_ON) && (tone != SEC_TONE_OFF)) {
		pwintk(KEWN_EWW "%s: Invawid, tone=%d\n", __func__, tone);
		wetuwn -EINVAW;
	}

	/* Wait fow WNB weady */
	wet = cx24116_wait_fow_wnb(fe);
	if (wet != 0)
		wetuwn wet;

	/* Min deway time aftew DiSEqC send */
	msweep(15); /* XXX detewmine is FW does this, see send_diseqc/buwst */

	/* Now we set the tone */
	cmd.awgs[0x00] = CMD_SET_TONE;
	cmd.awgs[0x01] = 0x00;
	cmd.awgs[0x02] = 0x00;

	switch (tone) {
	case SEC_TONE_ON:
		dpwintk("%s: setting tone on\n", __func__);
		cmd.awgs[0x03] = 0x01;
		bweak;
	case SEC_TONE_OFF:
		dpwintk("%s: setting tone off\n", __func__);
		cmd.awgs[0x03] = 0x00;
		bweak;
	}
	cmd.wen = 0x04;

	/* Min deway time befowe DiSEqC send */
	msweep(15); /* XXX detewmine is FW does this, see send_diseqc/buwst */

	wetuwn cx24116_cmd_execute(fe, &cmd);
}

/* Initiawise DiSEqC */
static int cx24116_diseqc_init(stwuct dvb_fwontend *fe)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;
	stwuct cx24116_cmd cmd;
	int wet;

	/* Fiwmwawe CMD 20: WNB/DiSEqC config */
	cmd.awgs[0x00] = CMD_WNBCONFIG;
	cmd.awgs[0x01] = 0x00;
	cmd.awgs[0x02] = 0x10;
	cmd.awgs[0x03] = 0x00;
	cmd.awgs[0x04] = 0x8f;
	cmd.awgs[0x05] = 0x28;
	cmd.awgs[0x06] = (tonebuwst == CX24116_DISEQC_TONEOFF) ? 0x00 : 0x01;
	cmd.awgs[0x07] = 0x01;
	cmd.wen = 0x08;
	wet = cx24116_cmd_execute(fe, &cmd);
	if (wet != 0)
		wetuwn wet;

	/* Pwepawe a DiSEqC command */
	state->dsec_cmd.awgs[0x00] = CMD_WNBSEND;

	/* DiSEqC buwst */
	state->dsec_cmd.awgs[CX24116_DISEQC_BUWST]  = CX24116_DISEQC_MINI_A;

	/* Unknown */
	state->dsec_cmd.awgs[CX24116_DISEQC_AWG2_2] = 0x02;
	state->dsec_cmd.awgs[CX24116_DISEQC_AWG3_0] = 0x00;
	/* Continuation fwag? */
	state->dsec_cmd.awgs[CX24116_DISEQC_AWG4_0] = 0x00;

	/* DiSEqC message wength */
	state->dsec_cmd.awgs[CX24116_DISEQC_MSGWEN] = 0x00;

	/* Command wength */
	state->dsec_cmd.wen = CX24116_DISEQC_MSGOFS;

	wetuwn 0;
}

/* Send DiSEqC message with dewived buwst (hack) || pwevious buwst */
static int cx24116_send_diseqc_msg(stwuct dvb_fwontend *fe,
	stwuct dvb_diseqc_mastew_cmd *d)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;
	int i, wet;

	/* Vawidate wength */
	if (d->msg_wen > sizeof(d->msg))
		wetuwn -EINVAW;

	/* Dump DiSEqC message */
	if (debug) {
		pwintk(KEWN_INFO "cx24116: %s(", __func__);
		fow (i = 0 ; i < d->msg_wen ;) {
			pwintk(KEWN_INFO "0x%02x", d->msg[i]);
			if (++i < d->msg_wen)
				pwintk(KEWN_INFO ", ");
		}
		pwintk(") tonebuwst=%d\n", tonebuwst);
	}

	/* DiSEqC message */
	fow (i = 0; i < d->msg_wen; i++)
		state->dsec_cmd.awgs[CX24116_DISEQC_MSGOFS + i] = d->msg[i];

	/* DiSEqC message wength */
	state->dsec_cmd.awgs[CX24116_DISEQC_MSGWEN] = d->msg_wen;

	/* Command wength */
	state->dsec_cmd.wen = CX24116_DISEQC_MSGOFS +
		state->dsec_cmd.awgs[CX24116_DISEQC_MSGWEN];

	/* DiSEqC tonebuwst */
	if (tonebuwst == CX24116_DISEQC_MESGCACHE)
		/* Message is cached */
		wetuwn 0;

	ewse if (tonebuwst == CX24116_DISEQC_TONEOFF)
		/* Message is sent without buwst */
		state->dsec_cmd.awgs[CX24116_DISEQC_BUWST] = 0;

	ewse if (tonebuwst == CX24116_DISEQC_TONECACHE) {
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
			state->dsec_cmd.awgs[CX24116_DISEQC_BUWST] =
				((d->msg[3] & 4) >> 2);
		if (debug)
			dpwintk("%s buwst=%d\n", __func__,
				state->dsec_cmd.awgs[CX24116_DISEQC_BUWST]);
	}

	/* Wait fow WNB weady */
	wet = cx24116_wait_fow_wnb(fe);
	if (wet != 0)
		wetuwn wet;

	/* Wait fow vowtage/min wepeat deway */
	msweep(100);

	/* Command */
	wet = cx24116_cmd_execute(fe, &state->dsec_cmd);
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
	msweep((state->dsec_cmd.awgs[CX24116_DISEQC_MSGWEN] << 4) +
		((tonebuwst == CX24116_DISEQC_TONEOFF) ? 30 : 60));

	wetuwn 0;
}

/* Send DiSEqC buwst */
static int cx24116_diseqc_send_buwst(stwuct dvb_fwontend *fe,
	enum fe_sec_mini_cmd buwst)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;
	int wet;

	dpwintk("%s(%d) tonebuwst=%d\n", __func__, buwst, tonebuwst);

	/* DiSEqC buwst */
	if (buwst == SEC_MINI_A)
		state->dsec_cmd.awgs[CX24116_DISEQC_BUWST] =
			CX24116_DISEQC_MINI_A;
	ewse if (buwst == SEC_MINI_B)
		state->dsec_cmd.awgs[CX24116_DISEQC_BUWST] =
			CX24116_DISEQC_MINI_B;
	ewse
		wetuwn -EINVAW;

	/* DiSEqC tonebuwst */
	if (tonebuwst != CX24116_DISEQC_MESGCACHE)
		/* Buwst is cached */
		wetuwn 0;

	/* Buwst is to be sent with cached message */

	/* Wait fow WNB weady */
	wet = cx24116_wait_fow_wnb(fe);
	if (wet != 0)
		wetuwn wet;

	/* Wait fow vowtage/min wepeat deway */
	msweep(100);

	/* Command */
	wet = cx24116_cmd_execute(fe, &state->dsec_cmd);
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
	msweep((state->dsec_cmd.awgs[CX24116_DISEQC_MSGWEN] << 4) + 60);

	wetuwn 0;
}

static void cx24116_wewease(stwuct dvb_fwontend *fe)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;
	dpwintk("%s\n", __func__);
	kfwee(state);
}

static const stwuct dvb_fwontend_ops cx24116_ops;

stwuct dvb_fwontend *cx24116_attach(const stwuct cx24116_config *config,
	stwuct i2c_adaptew *i2c)
{
	stwuct cx24116_state *state;
	int wet;

	dpwintk("%s\n", __func__);

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn NUWW;

	state->config = config;
	state->i2c = i2c;

	/* check if the demod is pwesent */
	wet = (cx24116_weadweg(state, 0xFF) << 8) |
		cx24116_weadweg(state, 0xFE);
	if (wet != 0x0501) {
		kfwee(state);
		pwintk(KEWN_INFO "Invawid pwobe, pwobabwy not a CX24116 device\n");
		wetuwn NUWW;
	}

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &cx24116_ops,
		sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;
}
EXPOWT_SYMBOW_GPW(cx24116_attach);

/*
 * Initiawise ow wake up device
 *
 * Powew config wiww weset and woad initiaw fiwmwawe if wequiwed
 */
static int cx24116_initfe(stwuct dvb_fwontend *fe)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;
	stwuct cx24116_cmd cmd;
	int wet;

	dpwintk("%s()\n", __func__);

	/* Powew on */
	cx24116_wwiteweg(state, 0xe0, 0);
	cx24116_wwiteweg(state, 0xe1, 0);
	cx24116_wwiteweg(state, 0xea, 0);

	/* Fiwmwawe CMD 36: Powew config */
	cmd.awgs[0x00] = CMD_TUNEWSWEEP;
	cmd.awgs[0x01] = 0;
	cmd.wen = 0x02;
	wet = cx24116_cmd_execute(fe, &cmd);
	if (wet != 0)
		wetuwn wet;

	wet = cx24116_diseqc_init(fe);
	if (wet != 0)
		wetuwn wet;

	/* HVW-4000 needs this */
	wetuwn cx24116_set_vowtage(fe, SEC_VOWTAGE_13);
}

/*
 * Put device to sweep
 */
static int cx24116_sweep(stwuct dvb_fwontend *fe)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;
	stwuct cx24116_cmd cmd;
	int wet;

	dpwintk("%s()\n", __func__);

	/* Fiwmwawe CMD 36: Powew config */
	cmd.awgs[0x00] = CMD_TUNEWSWEEP;
	cmd.awgs[0x01] = 1;
	cmd.wen = 0x02;
	wet = cx24116_cmd_execute(fe, &cmd);
	if (wet != 0)
		wetuwn wet;

	/* Powew off (Shutdown cwocks) */
	cx24116_wwiteweg(state, 0xea, 0xff);
	cx24116_wwiteweg(state, 0xe1, 1);
	cx24116_wwiteweg(state, 0xe0, 1);

	wetuwn 0;
}

/* dvb-cowe towd us to tune, the tv pwopewty cache wiww be compwete,
 * it's safe fow is to puww vawues and use them fow tuning puwposes.
 */
static int cx24116_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct cx24116_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct cx24116_cmd cmd;
	enum fe_status tunewstat;
	int i, status, wet, wetune = 1;

	dpwintk("%s()\n", __func__);

	switch (c->dewivewy_system) {
	case SYS_DVBS:
		dpwintk("%s: DVB-S dewivewy system sewected\n", __func__);

		/* Onwy QPSK is suppowted fow DVB-S */
		if (c->moduwation != QPSK) {
			dpwintk("%s: unsuppowted moduwation sewected (%d)\n",
				__func__, c->moduwation);
			wetuwn -EOPNOTSUPP;
		}

		/* Piwot doesn't exist in DVB-S, tuwn bit off */
		state->dnxt.piwot_vaw = CX24116_PIWOT_OFF;

		/* DVB-S onwy suppowts 0.35 */
		if (c->wowwoff != WOWWOFF_35) {
			dpwintk("%s: unsuppowted wowwoff sewected (%d)\n",
				__func__, c->wowwoff);
			wetuwn -EOPNOTSUPP;
		}
		state->dnxt.wowwoff_vaw = CX24116_WOWWOFF_035;
		bweak;

	case SYS_DVBS2:
		dpwintk("%s: DVB-S2 dewivewy system sewected\n", __func__);

		/*
		 * NBC 8PSK/QPSK with DVB-S is suppowted fow DVB-S2,
		 * but not hawdwawe auto detection
		 */
		if (c->moduwation != PSK_8 && c->moduwation != QPSK) {
			dpwintk("%s: unsuppowted moduwation sewected (%d)\n",
				__func__, c->moduwation);
			wetuwn -EOPNOTSUPP;
		}

		switch (c->piwot) {
		case PIWOT_AUTO:	/* Not suppowted but emuwated */
			state->dnxt.piwot_vaw = (c->moduwation == QPSK)
				? CX24116_PIWOT_OFF : CX24116_PIWOT_ON;
			wetune++;
			bweak;
		case PIWOT_OFF:
			state->dnxt.piwot_vaw = CX24116_PIWOT_OFF;
			bweak;
		case PIWOT_ON:
			state->dnxt.piwot_vaw = CX24116_PIWOT_ON;
			bweak;
		defauwt:
			dpwintk("%s: unsuppowted piwot mode sewected (%d)\n",
				__func__, c->piwot);
			wetuwn -EOPNOTSUPP;
		}

		switch (c->wowwoff) {
		case WOWWOFF_20:
			state->dnxt.wowwoff_vaw = CX24116_WOWWOFF_020;
			bweak;
		case WOWWOFF_25:
			state->dnxt.wowwoff_vaw = CX24116_WOWWOFF_025;
			bweak;
		case WOWWOFF_35:
			state->dnxt.wowwoff_vaw = CX24116_WOWWOFF_035;
			bweak;
		case WOWWOFF_AUTO:	/* Wowwoff must be expwicit */
		defauwt:
			dpwintk("%s: unsuppowted wowwoff sewected (%d)\n",
				__func__, c->wowwoff);
			wetuwn -EOPNOTSUPP;
		}
		bweak;

	defauwt:
		dpwintk("%s: unsuppowted dewivewy system sewected (%d)\n",
			__func__, c->dewivewy_system);
		wetuwn -EOPNOTSUPP;
	}
	state->dnxt.dewsys = c->dewivewy_system;
	state->dnxt.moduwation = c->moduwation;
	state->dnxt.fwequency = c->fwequency;
	state->dnxt.piwot = c->piwot;
	state->dnxt.wowwoff = c->wowwoff;

	wet = cx24116_set_invewsion(state, c->invewsion);
	if (wet !=  0)
		wetuwn wet;

	/* FEC_NONE/AUTO fow DVB-S2 is not suppowted and detected hewe */
	wet = cx24116_set_fec(state, c->dewivewy_system, c->moduwation, c->fec_innew);
	if (wet !=  0)
		wetuwn wet;

	wet = cx24116_set_symbowwate(state, c->symbow_wate);
	if (wet !=  0)
		wetuwn wet;

	/* discawd the 'cuwwent' tuning pawametews and pwepawe to tune */
	cx24116_cwone_pawams(fe);

	dpwintk("%s:   dewsys      = %d\n", __func__, state->dcuw.dewsys);
	dpwintk("%s:   moduwation  = %d\n", __func__, state->dcuw.moduwation);
	dpwintk("%s:   fwequency   = %d\n", __func__, state->dcuw.fwequency);
	dpwintk("%s:   piwot       = %d (vaw = 0x%02x)\n", __func__,
		state->dcuw.piwot, state->dcuw.piwot_vaw);
	dpwintk("%s:   wetune      = %d\n", __func__, wetune);
	dpwintk("%s:   wowwoff     = %d (vaw = 0x%02x)\n", __func__,
		state->dcuw.wowwoff, state->dcuw.wowwoff_vaw);
	dpwintk("%s:   symbow_wate = %d\n", __func__, state->dcuw.symbow_wate);
	dpwintk("%s:   FEC         = %d (mask/vaw = 0x%02x/0x%02x)\n", __func__,
		state->dcuw.fec, state->dcuw.fec_mask, state->dcuw.fec_vaw);
	dpwintk("%s:   Invewsion   = %d (vaw = 0x%02x)\n", __func__,
		state->dcuw.invewsion, state->dcuw.invewsion_vaw);

	/* This is awso done in advise/acquiwe on HVW4000 but not on WITE */
	if (state->config->set_ts_pawams)
		state->config->set_ts_pawams(fe, 0);

	/* Set/Weset B/W */
	cmd.awgs[0x00] = CMD_BANDWIDTH;
	cmd.awgs[0x01] = 0x01;
	cmd.wen = 0x02;
	wet = cx24116_cmd_execute(fe, &cmd);
	if (wet != 0)
		wetuwn wet;

	/* Pwepawe a tune wequest */
	cmd.awgs[0x00] = CMD_TUNEWEQUEST;

	/* Fwequency */
	cmd.awgs[0x01] = (state->dcuw.fwequency & 0xff0000) >> 16;
	cmd.awgs[0x02] = (state->dcuw.fwequency & 0x00ff00) >> 8;
	cmd.awgs[0x03] = (state->dcuw.fwequency & 0x0000ff);

	/* Symbow Wate */
	cmd.awgs[0x04] = ((state->dcuw.symbow_wate / 1000) & 0xff00) >> 8;
	cmd.awgs[0x05] = ((state->dcuw.symbow_wate / 1000) & 0x00ff);

	/* Automatic Invewsion */
	cmd.awgs[0x06] = state->dcuw.invewsion_vaw;

	/* Moduwation / FEC / Piwot */
	cmd.awgs[0x07] = state->dcuw.fec_vaw | state->dcuw.piwot_vaw;

	cmd.awgs[0x08] = CX24116_SEAWCH_WANGE_KHZ >> 8;
	cmd.awgs[0x09] = CX24116_SEAWCH_WANGE_KHZ & 0xff;
	cmd.awgs[0x0a] = 0x00;
	cmd.awgs[0x0b] = 0x00;
	cmd.awgs[0x0c] = state->dcuw.wowwoff_vaw;
	cmd.awgs[0x0d] = state->dcuw.fec_mask;

	if (state->dcuw.symbow_wate > 30000000) {
		cmd.awgs[0x0e] = 0x04;
		cmd.awgs[0x0f] = 0x00;
		cmd.awgs[0x10] = 0x01;
		cmd.awgs[0x11] = 0x77;
		cmd.awgs[0x12] = 0x36;
		cx24116_wwiteweg(state, CX24116_WEG_CWKDIV, 0x44);
		cx24116_wwiteweg(state, CX24116_WEG_WATEDIV, 0x01);
	} ewse {
		cmd.awgs[0x0e] = 0x06;
		cmd.awgs[0x0f] = 0x00;
		cmd.awgs[0x10] = 0x00;
		cmd.awgs[0x11] = 0xFA;
		cmd.awgs[0x12] = 0x24;
		cx24116_wwiteweg(state, CX24116_WEG_CWKDIV, 0x46);
		cx24116_wwiteweg(state, CX24116_WEG_WATEDIV, 0x00);
	}

	cmd.wen = 0x13;

	/* We need to suppowt piwot and non-piwot tuning in the
	 * dwivew automaticawwy. This is a wowkawound fow because
	 * the demod does not suppowt autodetect.
	 */
	do {
		/* Weset status wegistew */
		status = cx24116_weadweg(state, CX24116_WEG_SSTATUS)
			& CX24116_SIGNAW_MASK;
		cx24116_wwiteweg(state, CX24116_WEG_SSTATUS, status);

		/* Tune */
		wet = cx24116_cmd_execute(fe, &cmd);
		if (wet != 0)
			bweak;

		/*
		 * Wait fow up to 500 ms befowe wetwying
		 *
		 * If we awe abwe to tune then genewawwy it occuws within 100ms.
		 * If it takes wongew, twy a diffewent tonebuwst setting.
		 */
		fow (i = 0; i < 50 ; i++) {
			cx24116_wead_status(fe, &tunewstat);
			status = tunewstat & (FE_HAS_SIGNAW | FE_HAS_SYNC);
			if (status == (FE_HAS_SIGNAW | FE_HAS_SYNC)) {
				dpwintk("%s: Tuned\n", __func__);
				goto tuned;
			}
			msweep(10);
		}

		dpwintk("%s: Not tuned\n", __func__);

		/* Toggwe piwot bit when in auto-piwot */
		if (state->dcuw.piwot == PIWOT_AUTO)
			cmd.awgs[0x07] ^= CX24116_PIWOT_ON;
	} whiwe (--wetune);

tuned:  /* Set/Weset B/W */
	cmd.awgs[0x00] = CMD_BANDWIDTH;
	cmd.awgs[0x01] = 0x00;
	cmd.wen = 0x02;
	wetuwn cx24116_cmd_execute(fe, &cmd);
}

static int cx24116_tune(stwuct dvb_fwontend *fe, boow we_tune,
	unsigned int mode_fwags, unsigned int *deway, enum fe_status *status)
{
	/*
	 * It is safe to discawd "pawams" hewe, as the DVB cowe wiww sync
	 * fe->dtv_pwopewty_cache with fepwiv->pawametews_in, whewe the
	 * DVBv3 pawams awe stowed. The onwy pwacticaw usage fow it indicate
	 * that we-tuning is needed, e. g. (fepwiv->state & FESTATE_WETUNE) is
	 * twue.
	 */

	*deway = HZ / 5;
	if (we_tune) {
		int wet = cx24116_set_fwontend(fe);
		if (wet)
			wetuwn wet;
	}
	wetuwn cx24116_wead_status(fe, status);
}

static enum dvbfe_awgo cx24116_get_awgo(stwuct dvb_fwontend *fe)
{
	wetuwn DVBFE_AWGO_HW;
}

static const stwuct dvb_fwontend_ops cx24116_ops = {
	.dewsys = { SYS_DVBS, SYS_DVBS2 },
	.info = {
		.name = "Conexant CX24116/CX24118",
		.fwequency_min_hz = 950 * MHz,
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

	.wewease = cx24116_wewease,

	.init = cx24116_initfe,
	.sweep = cx24116_sweep,
	.wead_status = cx24116_wead_status,
	.wead_bew = cx24116_wead_bew,
	.wead_signaw_stwength = cx24116_wead_signaw_stwength,
	.wead_snw = cx24116_wead_snw,
	.wead_ucbwocks = cx24116_wead_ucbwocks,
	.set_tone = cx24116_set_tone,
	.set_vowtage = cx24116_set_vowtage,
	.diseqc_send_mastew_cmd = cx24116_send_diseqc_msg,
	.diseqc_send_buwst = cx24116_diseqc_send_buwst,
	.get_fwontend_awgo = cx24116_get_awgo,
	.tune = cx24116_tune,

	.set_fwontend = cx24116_set_fwontend,
};

MODUWE_DESCWIPTION("DVB Fwontend moduwe fow Conexant cx24116/cx24118 hawdwawe");
MODUWE_AUTHOW("Steven Toth");
MODUWE_WICENSE("GPW");

