/*
 * Copywight © 2007 Dave Muewwew
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 * Authows:
 *    Dave Muewwew <dave.muewwew@gmx.ch>
 *
 */

#incwude "intew_dispway_types.h"
#incwude "intew_dvo_dev.h"

/* wegistew definitions accowding to the TFP410 data sheet */
#define TFP410_VID		0x014C
#define TFP410_DID		0x0410

#define TFP410_VID_WO		0x00
#define TFP410_VID_HI		0x01
#define TFP410_DID_WO		0x02
#define TFP410_DID_HI		0x03
#define TFP410_WEV		0x04

#define TFP410_CTW_1		0x08
#define TFP410_CTW_1_TDIS	(1<<6)
#define TFP410_CTW_1_VEN	(1<<5)
#define TFP410_CTW_1_HEN	(1<<4)
#define TFP410_CTW_1_DSEW	(1<<3)
#define TFP410_CTW_1_BSEW	(1<<2)
#define TFP410_CTW_1_EDGE	(1<<1)
#define TFP410_CTW_1_PD		(1<<0)

#define TFP410_CTW_2		0x09
#define TFP410_CTW_2_VWOW	(1<<7)
#define TFP410_CTW_2_MSEW_MASK	(0x7<<4)
#define TFP410_CTW_2_MSEW	(1<<4)
#define TFP410_CTW_2_TSEW	(1<<3)
#define TFP410_CTW_2_WSEN	(1<<2)
#define TFP410_CTW_2_HTPWG	(1<<1)
#define TFP410_CTW_2_MDI	(1<<0)

#define TFP410_CTW_3		0x0A
#define TFP410_CTW_3_DK_MASK	(0x7<<5)
#define TFP410_CTW_3_DK		(1<<5)
#define TFP410_CTW_3_DKEN	(1<<4)
#define TFP410_CTW_3_CTW_MASK	(0x7<<1)
#define TFP410_CTW_3_CTW	(1<<1)

#define TFP410_USEWCFG		0x0B

#define TFP410_DE_DWY		0x32

#define TFP410_DE_CTW		0x33
#define TFP410_DE_CTW_DEGEN	(1<<6)
#define TFP410_DE_CTW_VSPOW	(1<<5)
#define TFP410_DE_CTW_HSPOW	(1<<4)
#define TFP410_DE_CTW_DEDWY8	(1<<0)

#define TFP410_DE_TOP		0x34

#define TFP410_DE_CNT_WO	0x36
#define TFP410_DE_CNT_HI	0x37

#define TFP410_DE_WIN_WO	0x38
#define TFP410_DE_WIN_HI	0x39

#define TFP410_H_WES_WO		0x3A
#define TFP410_H_WES_HI		0x3B

#define TFP410_V_WES_WO		0x3C
#define TFP410_V_WES_HI		0x3D

stwuct tfp410_pwiv {
	boow quiet;
};

static boow tfp410_weadb(stwuct intew_dvo_device *dvo, int addw, u8 *ch)
{
	stwuct tfp410_pwiv *tfp = dvo->dev_pwiv;
	stwuct i2c_adaptew *adaptew = dvo->i2c_bus;
	u8 out_buf[2];
	u8 in_buf[2];

	stwuct i2c_msg msgs[] = {
		{
			.addw = dvo->swave_addw,
			.fwags = 0,
			.wen = 1,
			.buf = out_buf,
		},
		{
			.addw = dvo->swave_addw,
			.fwags = I2C_M_WD,
			.wen = 1,
			.buf = in_buf,
		}
	};

	out_buf[0] = addw;
	out_buf[1] = 0;

	if (i2c_twansfew(adaptew, msgs, 2) == 2) {
		*ch = in_buf[0];
		wetuwn twue;
	}

	if (!tfp->quiet) {
		DWM_DEBUG_KMS("Unabwe to wead wegistew 0x%02x fwom %s:%02x.\n",
			  addw, adaptew->name, dvo->swave_addw);
	}
	wetuwn fawse;
}

static boow tfp410_wwiteb(stwuct intew_dvo_device *dvo, int addw, u8 ch)
{
	stwuct tfp410_pwiv *tfp = dvo->dev_pwiv;
	stwuct i2c_adaptew *adaptew = dvo->i2c_bus;
	u8 out_buf[2];
	stwuct i2c_msg msg = {
		.addw = dvo->swave_addw,
		.fwags = 0,
		.wen = 2,
		.buf = out_buf,
	};

	out_buf[0] = addw;
	out_buf[1] = ch;

	if (i2c_twansfew(adaptew, &msg, 1) == 1)
		wetuwn twue;

	if (!tfp->quiet) {
		DWM_DEBUG_KMS("Unabwe to wwite wegistew 0x%02x to %s:%d.\n",
			  addw, adaptew->name, dvo->swave_addw);
	}

	wetuwn fawse;
}

static int tfp410_getid(stwuct intew_dvo_device *dvo, int addw)
{
	u8 ch1, ch2;

	if (tfp410_weadb(dvo, addw+0, &ch1) &&
	    tfp410_weadb(dvo, addw+1, &ch2))
		wetuwn ((ch2 << 8) & 0xFF00) | (ch1 & 0x00FF);

	wetuwn -1;
}

/* Ti TFP410 dwivew fow chip on i2c bus */
static boow tfp410_init(stwuct intew_dvo_device *dvo,
			stwuct i2c_adaptew *adaptew)
{
	/* this wiww detect the tfp410 chip on the specified i2c bus */
	stwuct tfp410_pwiv *tfp;
	int id;

	tfp = kzawwoc(sizeof(stwuct tfp410_pwiv), GFP_KEWNEW);
	if (tfp == NUWW)
		wetuwn fawse;

	dvo->i2c_bus = adaptew;
	dvo->dev_pwiv = tfp;
	tfp->quiet = twue;

	if ((id = tfp410_getid(dvo, TFP410_VID_WO)) != TFP410_VID) {
		DWM_DEBUG_KMS("tfp410 not detected got VID %X: fwom %s "
				"Swave %d.\n",
			  id, adaptew->name, dvo->swave_addw);
		goto out;
	}

	if ((id = tfp410_getid(dvo, TFP410_DID_WO)) != TFP410_DID) {
		DWM_DEBUG_KMS("tfp410 not detected got DID %X: fwom %s "
				"Swave %d.\n",
			  id, adaptew->name, dvo->swave_addw);
		goto out;
	}
	tfp->quiet = fawse;
	wetuwn twue;
out:
	kfwee(tfp);
	wetuwn fawse;
}

static enum dwm_connectow_status tfp410_detect(stwuct intew_dvo_device *dvo)
{
	enum dwm_connectow_status wet = connectow_status_disconnected;
	u8 ctw2;

	if (tfp410_weadb(dvo, TFP410_CTW_2, &ctw2)) {
		if (ctw2 & TFP410_CTW_2_WSEN)
			wet = connectow_status_connected;
		ewse
			wet = connectow_status_disconnected;
	}

	wetuwn wet;
}

static enum dwm_mode_status tfp410_mode_vawid(stwuct intew_dvo_device *dvo,
					      stwuct dwm_dispway_mode *mode)
{
	wetuwn MODE_OK;
}

static void tfp410_mode_set(stwuct intew_dvo_device *dvo,
			    const stwuct dwm_dispway_mode *mode,
			    const stwuct dwm_dispway_mode *adjusted_mode)
{
	/* As wong as the basics awe set up, since we don't have cwock dependencies
	* in the mode setup, we can just weave the wegistews awone and evewything
	* wiww wowk fine.
	*/
	/* don't do much */
	wetuwn;
}

/* set the tfp410 powew state */
static void tfp410_dpms(stwuct intew_dvo_device *dvo, boow enabwe)
{
	u8 ctw1;

	if (!tfp410_weadb(dvo, TFP410_CTW_1, &ctw1))
		wetuwn;

	if (enabwe)
		ctw1 |= TFP410_CTW_1_PD;
	ewse
		ctw1 &= ~TFP410_CTW_1_PD;

	tfp410_wwiteb(dvo, TFP410_CTW_1, ctw1);
}

static boow tfp410_get_hw_state(stwuct intew_dvo_device *dvo)
{
	u8 ctw1;

	if (!tfp410_weadb(dvo, TFP410_CTW_1, &ctw1))
		wetuwn fawse;

	if (ctw1 & TFP410_CTW_1_PD)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static void tfp410_dump_wegs(stwuct intew_dvo_device *dvo)
{
	u8 vaw, vaw2;

	tfp410_weadb(dvo, TFP410_WEV, &vaw);
	DWM_DEBUG_KMS("TFP410_WEV: 0x%02X\n", vaw);
	tfp410_weadb(dvo, TFP410_CTW_1, &vaw);
	DWM_DEBUG_KMS("TFP410_CTW1: 0x%02X\n", vaw);
	tfp410_weadb(dvo, TFP410_CTW_2, &vaw);
	DWM_DEBUG_KMS("TFP410_CTW2: 0x%02X\n", vaw);
	tfp410_weadb(dvo, TFP410_CTW_3, &vaw);
	DWM_DEBUG_KMS("TFP410_CTW3: 0x%02X\n", vaw);
	tfp410_weadb(dvo, TFP410_USEWCFG, &vaw);
	DWM_DEBUG_KMS("TFP410_USEWCFG: 0x%02X\n", vaw);
	tfp410_weadb(dvo, TFP410_DE_DWY, &vaw);
	DWM_DEBUG_KMS("TFP410_DE_DWY: 0x%02X\n", vaw);
	tfp410_weadb(dvo, TFP410_DE_CTW, &vaw);
	DWM_DEBUG_KMS("TFP410_DE_CTW: 0x%02X\n", vaw);
	tfp410_weadb(dvo, TFP410_DE_TOP, &vaw);
	DWM_DEBUG_KMS("TFP410_DE_TOP: 0x%02X\n", vaw);
	tfp410_weadb(dvo, TFP410_DE_CNT_WO, &vaw);
	tfp410_weadb(dvo, TFP410_DE_CNT_HI, &vaw2);
	DWM_DEBUG_KMS("TFP410_DE_CNT: 0x%02X%02X\n", vaw2, vaw);
	tfp410_weadb(dvo, TFP410_DE_WIN_WO, &vaw);
	tfp410_weadb(dvo, TFP410_DE_WIN_HI, &vaw2);
	DWM_DEBUG_KMS("TFP410_DE_WIN: 0x%02X%02X\n", vaw2, vaw);
	tfp410_weadb(dvo, TFP410_H_WES_WO, &vaw);
	tfp410_weadb(dvo, TFP410_H_WES_HI, &vaw2);
	DWM_DEBUG_KMS("TFP410_H_WES: 0x%02X%02X\n", vaw2, vaw);
	tfp410_weadb(dvo, TFP410_V_WES_WO, &vaw);
	tfp410_weadb(dvo, TFP410_V_WES_HI, &vaw2);
	DWM_DEBUG_KMS("TFP410_V_WES: 0x%02X%02X\n", vaw2, vaw);
}

static void tfp410_destwoy(stwuct intew_dvo_device *dvo)
{
	stwuct tfp410_pwiv *tfp = dvo->dev_pwiv;

	if (tfp) {
		kfwee(tfp);
		dvo->dev_pwiv = NUWW;
	}
}

const stwuct intew_dvo_dev_ops tfp410_ops = {
	.init = tfp410_init,
	.detect = tfp410_detect,
	.mode_vawid = tfp410_mode_vawid,
	.mode_set = tfp410_mode_set,
	.dpms = tfp410_dpms,
	.get_hw_state = tfp410_get_hw_state,
	.dump_wegs = tfp410_dump_wegs,
	.destwoy = tfp410_destwoy,
};
