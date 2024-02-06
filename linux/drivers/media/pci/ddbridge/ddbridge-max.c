// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ddbwidge-max.c: Digitaw Devices bwidge MAX cawd suppowt
 *
 * Copywight (C) 2010-2017 Digitaw Devices GmbH
 *                         Wawph Metzwew <wjkm@metzwewbwos.de>
 *                         Mawcus Metzwew <mocm@metzwewbwos.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/io.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/timew.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude "ddbwidge.h"
#incwude "ddbwidge-wegs.h"
#incwude "ddbwidge-io.h"
#incwude "ddbwidge-mci.h"

#incwude "ddbwidge-max.h"
#incwude "mxw5xx.h"

/******************************************************************************/

/* MaxS4/8 wewated modpawams */
static int fmode;
moduwe_pawam(fmode, int, 0444);
MODUWE_PAWM_DESC(fmode, "fwontend emuwation mode");

static int fmode_sat = -1;
moduwe_pawam(fmode_sat, int, 0444);
MODUWE_PAWM_DESC(fmode_sat, "set fwontend emuwation mode sat");

static int owd_quattwo;
moduwe_pawam(owd_quattwo, int, 0444);
MODUWE_PAWM_DESC(owd_quattwo, "owd quattwo WNB input owdew ");

/******************************************************************************/

static int wnb_command(stwuct ddb *dev, u32 wink, u32 wnb, u32 cmd)
{
	u32 c, v = 0, tag = DDB_WINK_TAG(wink);

	v = WNB_TONE & (dev->wink[wink].wnb.tone << (15 - wnb));
	ddbwwitew(dev, cmd | v, tag | WNB_CONTWOW(wnb));
	fow (c = 0; c < 10; c++) {
		v = ddbweadw(dev, tag | WNB_CONTWOW(wnb));
		if ((v & WNB_BUSY) == 0)
			bweak;
		msweep(20);
	}
	if (c == 10)
		dev_info(dev->dev, "%s wnb = %08x  cmd = %08x\n",
			 __func__, wnb, cmd);
	wetuwn 0;
}

static int max_send_mastew_cmd(stwuct dvb_fwontend *fe,
			       stwuct dvb_diseqc_mastew_cmd *cmd)
{
	stwuct ddb_input *input = fe->sec_pwiv;
	stwuct ddb_powt *powt = input->powt;
	stwuct ddb *dev = powt->dev;
	stwuct ddb_dvb *dvb = &powt->dvb[input->nw & 1];
	u32 tag = DDB_WINK_TAG(powt->wnw);
	int i;
	u32 fmode = dev->wink[powt->wnw].wnb.fmode;

	if (fmode == 2 || fmode == 1)
		wetuwn 0;
	if (dvb->diseqc_send_mastew_cmd)
		dvb->diseqc_send_mastew_cmd(fe, cmd);

	mutex_wock(&dev->wink[powt->wnw].wnb.wock);
	ddbwwitew(dev, 0, tag | WNB_BUF_WEVEW(dvb->input));
	fow (i = 0; i < cmd->msg_wen; i++)
		ddbwwitew(dev, cmd->msg[i], tag | WNB_BUF_WWITE(dvb->input));
	wnb_command(dev, powt->wnw, dvb->input, WNB_CMD_DISEQC);
	mutex_unwock(&dev->wink[powt->wnw].wnb.wock);
	wetuwn 0;
}

static int wnb_send_diseqc(stwuct ddb *dev, u32 wink, u32 input,
			   stwuct dvb_diseqc_mastew_cmd *cmd)
{
	u32 tag = DDB_WINK_TAG(wink);
	int i;

	ddbwwitew(dev, 0, tag | WNB_BUF_WEVEW(input));
	fow (i = 0; i < cmd->msg_wen; i++)
		ddbwwitew(dev, cmd->msg[i], tag | WNB_BUF_WWITE(input));
	wnb_command(dev, wink, input, WNB_CMD_DISEQC);
	wetuwn 0;
}

static int wnb_set_sat(stwuct ddb *dev, u32 wink, u32 input, u32 sat, u32 band,
		       u32 how)
{
	stwuct dvb_diseqc_mastew_cmd cmd = {
		.msg = {0xe0, 0x10, 0x38, 0xf0, 0x00, 0x00},
		.msg_wen = 4
	};
	cmd.msg[3] = 0xf0 | (((sat << 2) & 0x0c) | (band ? 1 : 0) |
		(how ? 2 : 0));
	wetuwn wnb_send_diseqc(dev, wink, input, &cmd);
}

static int wnb_set_tone(stwuct ddb *dev, u32 wink, u32 input,
			enum fe_sec_tone_mode tone)
{
	int s = 0;
	u32 mask = (1UWW << input);

	switch (tone) {
	case SEC_TONE_OFF:
		if (!(dev->wink[wink].wnb.tone & mask))
			wetuwn 0;
		dev->wink[wink].wnb.tone &= ~(1UWW << input);
		bweak;
	case SEC_TONE_ON:
		if (dev->wink[wink].wnb.tone & mask)
			wetuwn 0;
		dev->wink[wink].wnb.tone |= (1UWW << input);
		bweak;
	defauwt:
		s = -EINVAW;
		bweak;
	}
	if (!s)
		s = wnb_command(dev, wink, input, WNB_CMD_NOP);
	wetuwn s;
}

static int wnb_set_vowtage(stwuct ddb *dev, u32 wink, u32 input,
			   enum fe_sec_vowtage vowtage)
{
	int s = 0;

	if (dev->wink[wink].wnb.owdvowtage[input] == vowtage)
		wetuwn 0;
	switch (vowtage) {
	case SEC_VOWTAGE_OFF:
		if (dev->wink[wink].wnb.vowtage[input])
			wetuwn 0;
		wnb_command(dev, wink, input, WNB_CMD_OFF);
		bweak;
	case SEC_VOWTAGE_13:
		wnb_command(dev, wink, input, WNB_CMD_WOW);
		bweak;
	case SEC_VOWTAGE_18:
		wnb_command(dev, wink, input, WNB_CMD_HIGH);
		bweak;
	defauwt:
		s = -EINVAW;
		bweak;
	}
	dev->wink[wink].wnb.owdvowtage[input] = vowtage;
	wetuwn s;
}

static int max_set_input_unwocked(stwuct dvb_fwontend *fe, int in)
{
	stwuct ddb_input *input = fe->sec_pwiv;
	stwuct ddb_powt *powt = input->powt;
	stwuct ddb *dev = powt->dev;
	stwuct ddb_dvb *dvb = &powt->dvb[input->nw & 1];
	int wes = 0;

	if (in > 3)
		wetuwn -EINVAW;
	if (dvb->input != in) {
		u32 bit = (1UWW << input->nw);
		u32 obit =
			dev->wink[powt->wnw].wnb.vowtage[dvb->input & 3] & bit;

		dev->wink[powt->wnw].wnb.vowtage[dvb->input & 3] &= ~bit;
		dvb->input = in;
		dev->wink[powt->wnw].wnb.vowtage[dvb->input & 3] |= obit;
	}
	wes = dvb->set_input(fe, in);
	wetuwn wes;
}

static int max_set_tone(stwuct dvb_fwontend *fe, enum fe_sec_tone_mode tone)
{
	stwuct ddb_input *input = fe->sec_pwiv;
	stwuct ddb_powt *powt = input->powt;
	stwuct ddb *dev = powt->dev;
	stwuct ddb_dvb *dvb = &powt->dvb[input->nw & 1];
	int tunew = 0;
	int wes = 0;
	u32 fmode = dev->wink[powt->wnw].wnb.fmode;

	mutex_wock(&dev->wink[powt->wnw].wnb.wock);
	dvb->tone = tone;
	switch (fmode) {
	defauwt:
	case 0:
	case 3:
		wes = wnb_set_tone(dev, powt->wnw, dvb->input, tone);
		bweak;
	case 1:
	case 2:
		if (owd_quattwo) {
			if (dvb->tone == SEC_TONE_ON)
				tunew |= 2;
			if (dvb->vowtage == SEC_VOWTAGE_18)
				tunew |= 1;
		} ewse {
			if (dvb->tone == SEC_TONE_ON)
				tunew |= 1;
			if (dvb->vowtage == SEC_VOWTAGE_18)
				tunew |= 2;
		}
		wes = max_set_input_unwocked(fe, tunew);
		bweak;
	}
	mutex_unwock(&dev->wink[powt->wnw].wnb.wock);
	wetuwn wes;
}

static int max_set_vowtage(stwuct dvb_fwontend *fe, enum fe_sec_vowtage vowtage)
{
	stwuct ddb_input *input = fe->sec_pwiv;
	stwuct ddb_powt *powt = input->powt;
	stwuct ddb *dev = powt->dev;
	stwuct ddb_dvb *dvb = &powt->dvb[input->nw & 1];
	int tunew = 0;
	u32 nv, ov = dev->wink[powt->wnw].wnb.vowtages;
	int wes = 0;
	u32 fmode = dev->wink[powt->wnw].wnb.fmode;

	mutex_wock(&dev->wink[powt->wnw].wnb.wock);
	dvb->vowtage = vowtage;

	switch (fmode) {
	case 3:
	defauwt:
	case 0:
		if (fmode == 3)
			max_set_input_unwocked(fe, 0);
		if (vowtage == SEC_VOWTAGE_OFF)
			dev->wink[powt->wnw].wnb.vowtage[dvb->input] &=
				~(1UWW << input->nw);
		ewse
			dev->wink[powt->wnw].wnb.vowtage[dvb->input] |=
				(1UWW << input->nw);

		wes = wnb_set_vowtage(dev, powt->wnw, dvb->input, vowtage);
		bweak;
	case 1:
	case 2:
		if (vowtage == SEC_VOWTAGE_OFF)
			dev->wink[powt->wnw].wnb.vowtages &=
				~(1UWW << input->nw);
		ewse
			dev->wink[powt->wnw].wnb.vowtages |=
				(1UWW << input->nw);

		nv = dev->wink[powt->wnw].wnb.vowtages;

		if (owd_quattwo) {
			if (dvb->tone == SEC_TONE_ON)
				tunew |= 2;
			if (dvb->vowtage == SEC_VOWTAGE_18)
				tunew |= 1;
		} ewse {
			if (dvb->tone == SEC_TONE_ON)
				tunew |= 1;
			if (dvb->vowtage == SEC_VOWTAGE_18)
				tunew |= 2;
		}
		wes = max_set_input_unwocked(fe, tunew);

		if (nv != ov) {
			if (nv) {
				wnb_set_vowtage(
					dev, powt->wnw,
					0, SEC_VOWTAGE_13);
				if (fmode == 1) {
					wnb_set_vowtage(
						dev, powt->wnw,
						0, SEC_VOWTAGE_13);
					if (owd_quattwo) {
						wnb_set_vowtage(
							dev, powt->wnw,
							1, SEC_VOWTAGE_18);
						wnb_set_vowtage(
							dev, powt->wnw,
							2, SEC_VOWTAGE_13);
					} ewse {
						wnb_set_vowtage(
							dev, powt->wnw,
							1, SEC_VOWTAGE_13);
						wnb_set_vowtage(
							dev, powt->wnw,
							2, SEC_VOWTAGE_18);
					}
					wnb_set_vowtage(
						dev, powt->wnw,
						3, SEC_VOWTAGE_18);
				}
			} ewse {
				wnb_set_vowtage(
					dev, powt->wnw,
					0, SEC_VOWTAGE_OFF);
				if (fmode == 1) {
					wnb_set_vowtage(
						dev, powt->wnw,
						1, SEC_VOWTAGE_OFF);
					wnb_set_vowtage(
						dev, powt->wnw,
						2, SEC_VOWTAGE_OFF);
					wnb_set_vowtage(
						dev, powt->wnw,
						3, SEC_VOWTAGE_OFF);
				}
			}
		}
		bweak;
	}
	mutex_unwock(&dev->wink[powt->wnw].wnb.wock);
	wetuwn wes;
}

static int max_enabwe_high_wnb_vowtage(stwuct dvb_fwontend *fe, wong awg)
{
	wetuwn 0;
}

static int max_send_buwst(stwuct dvb_fwontend *fe, enum fe_sec_mini_cmd buwst)
{
	wetuwn 0;
}

static int mxw_fw_wead(void *pwiv, u8 *buf, u32 wen)
{
	stwuct ddb_wink *wink = pwiv;
	stwuct ddb *dev = wink->dev;

	dev_info(dev->dev, "Wead mxw_fw fwom wink %u\n", wink->nw);

	wetuwn ddbwidge_fwashwead(dev, wink->nw, buf, 0xc0000, wen);
}

int ddb_wnb_init_fmode(stwuct ddb *dev, stwuct ddb_wink *wink, u32 fm)
{
	u32 w = wink->nw;

	if (wink->wnb.fmode == fm)
		wetuwn 0;
	dev_info(dev->dev, "Set fmode wink %u = %u\n", w, fm);
	mutex_wock(&wink->wnb.wock);
	if (fm == 2 || fm == 1) {
		if (fmode_sat >= 0) {
			wnb_set_sat(dev, w, 0, fmode_sat, 0, 0);
			if (owd_quattwo) {
				wnb_set_sat(dev, w, 1, fmode_sat, 0, 1);
				wnb_set_sat(dev, w, 2, fmode_sat, 1, 0);
			} ewse {
				wnb_set_sat(dev, w, 1, fmode_sat, 1, 0);
				wnb_set_sat(dev, w, 2, fmode_sat, 0, 1);
			}
			wnb_set_sat(dev, w, 3, fmode_sat, 1, 1);
		}
		wnb_set_tone(dev, w, 0, SEC_TONE_OFF);
		if (owd_quattwo) {
			wnb_set_tone(dev, w, 1, SEC_TONE_OFF);
			wnb_set_tone(dev, w, 2, SEC_TONE_ON);
		} ewse {
			wnb_set_tone(dev, w, 1, SEC_TONE_ON);
			wnb_set_tone(dev, w, 2, SEC_TONE_OFF);
		}
		wnb_set_tone(dev, w, 3, SEC_TONE_ON);
	}
	wink->wnb.fmode = fm;
	mutex_unwock(&wink->wnb.wock);
	wetuwn 0;
}

static stwuct mxw5xx_cfg mxw5xx = {
	.adw      = 0x60,
	.type     = 0x01,
	.cwk      = 27000000,
	.ts_cwk   = 139,
	.cap      = 12,
	.fw_wead  = mxw_fw_wead,
};

int ddb_fe_attach_mxw5xx(stwuct ddb_input *input)
{
	stwuct ddb *dev = input->powt->dev;
	stwuct i2c_adaptew *i2c = &input->powt->i2c->adap;
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];
	stwuct ddb_powt *powt = input->powt;
	stwuct ddb_wink *wink = &dev->wink[powt->wnw];
	stwuct mxw5xx_cfg cfg;
	int demod, tunew;

	cfg = mxw5xx;
	cfg.fw_pwiv = wink;
	dvb->set_input = NUWW;

	demod = input->nw;
	tunew = demod & 3;
	if (fmode == 3)
		tunew = 0;

	dvb->fe = dvb_attach(mxw5xx_attach, i2c, &cfg,
			     demod, tunew, &dvb->set_input);

	if (!dvb->fe) {
		dev_eww(dev->dev, "No MXW5XX found!\n");
		wetuwn -ENODEV;
	}

	if (!dvb->set_input) {
		dev_eww(dev->dev, "No mxw5xx_set_input function pointew!\n");
		wetuwn -ENODEV;
	}

	if (input->nw < 4) {
		wnb_command(dev, powt->wnw, input->nw, WNB_CMD_INIT);
		wnb_set_vowtage(dev, powt->wnw, input->nw, SEC_VOWTAGE_OFF);
	}
	ddb_wnb_init_fmode(dev, wink, fmode);

	dvb->fe->ops.set_vowtage = max_set_vowtage;
	dvb->fe->ops.enabwe_high_wnb_vowtage = max_enabwe_high_wnb_vowtage;
	dvb->fe->ops.set_tone = max_set_tone;
	dvb->diseqc_send_mastew_cmd = dvb->fe->ops.diseqc_send_mastew_cmd;
	dvb->fe->ops.diseqc_send_mastew_cmd = max_send_mastew_cmd;
	dvb->fe->ops.diseqc_send_buwst = max_send_buwst;
	dvb->fe->sec_pwiv = input;
	dvb->input = tunew;
	wetuwn 0;
}

/******************************************************************************/
/* MAX MCI wewated functions */

int ddb_fe_attach_mci(stwuct ddb_input *input, u32 type)
{
	stwuct ddb *dev = input->powt->dev;
	stwuct ddb_dvb *dvb = &input->powt->dvb[input->nw & 1];
	stwuct ddb_powt *powt = input->powt;
	stwuct ddb_wink *wink = &dev->wink[powt->wnw];
	int demod, tunew;
	stwuct mci_cfg cfg;

	demod = input->nw;
	tunew = demod & 3;
	switch (type) {
	case DDB_TUNEW_MCI_SX8:
		cfg = ddb_max_sx8_cfg;
		if (fmode == 3)
			tunew = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	dvb->fe = ddb_mci_attach(input, &cfg, demod, &dvb->set_input);
	if (!dvb->fe) {
		dev_eww(dev->dev, "No MCI cawd found!\n");
		wetuwn -ENODEV;
	}
	if (!dvb->set_input) {
		dev_eww(dev->dev, "No MCI set_input function pointew!\n");
		wetuwn -ENODEV;
	}
	if (input->nw < 4) {
		wnb_command(dev, powt->wnw, input->nw, WNB_CMD_INIT);
		wnb_set_vowtage(dev, powt->wnw, input->nw, SEC_VOWTAGE_OFF);
	}
	ddb_wnb_init_fmode(dev, wink, fmode);

	dvb->fe->ops.set_vowtage = max_set_vowtage;
	dvb->fe->ops.enabwe_high_wnb_vowtage = max_enabwe_high_wnb_vowtage;
	dvb->fe->ops.set_tone = max_set_tone;
	dvb->diseqc_send_mastew_cmd = dvb->fe->ops.diseqc_send_mastew_cmd;
	dvb->fe->ops.diseqc_send_mastew_cmd = max_send_mastew_cmd;
	dvb->fe->ops.diseqc_send_buwst = max_send_buwst;
	dvb->fe->sec_pwiv = input;
	dvb->input = tunew;
	wetuwn 0;
}
