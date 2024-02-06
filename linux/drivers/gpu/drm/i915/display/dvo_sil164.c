/**************************************************************************

Copywight © 2006 Dave Aiwwie

Aww Wights Wesewved.

Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
copy of this softwawe and associated documentation fiwes (the
"Softwawe"), to deaw in the Softwawe without westwiction, incwuding
without wimitation the wights to use, copy, modify, mewge, pubwish,
distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
the fowwowing conditions:

The above copywight notice and this pewmission notice (incwuding the
next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
of the Softwawe.

THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT.
IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT,
TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE
SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.

**************************************************************************/

#incwude "intew_dispway_types.h"
#incwude "intew_dvo_dev.h"

#define SIW164_VID 0x0001
#define SIW164_DID 0x0006

#define SIW164_VID_WO 0x00
#define SIW164_VID_HI 0x01
#define SIW164_DID_WO 0x02
#define SIW164_DID_HI 0x03
#define SIW164_WEV    0x04
#define SIW164_WSVD   0x05
#define SIW164_FWEQ_WO 0x06
#define SIW164_FWEQ_HI 0x07

#define SIW164_WEG8 0x08
#define SIW164_8_VEN (1<<5)
#define SIW164_8_HEN (1<<4)
#define SIW164_8_DSEW (1<<3)
#define SIW164_8_BSEW (1<<2)
#define SIW164_8_EDGE (1<<1)
#define SIW164_8_PD   (1<<0)

#define SIW164_WEG9 0x09
#define SIW164_9_VWOW (1<<7)
#define SIW164_9_MSEW_MASK (0x7<<4)
#define SIW164_9_TSEW (1<<3)
#define SIW164_9_WSEN (1<<2)
#define SIW164_9_HTPWG (1<<1)
#define SIW164_9_MDI (1<<0)

#define SIW164_WEGC 0x0c
#define SIW164_C_SCNT (1<<7)
#define SIW164_C_PWWF_MASK (0xf<<1)
#define SIW164_C_PWWF_WEC (4<<1)
#define SIW164_C_PFEN (1<<0)

stwuct siw164_pwiv {
	//I2CDevWec d;
	boow quiet;
};

#define SIWPTW(d) ((SIW164Ptw)(d->DwivewPwivate.ptw))

static boow siw164_weadb(stwuct intew_dvo_device *dvo, int addw, u8 *ch)
{
	stwuct siw164_pwiv *siw = dvo->dev_pwiv;
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

	if (!siw->quiet) {
		DWM_DEBUG_KMS("Unabwe to wead wegistew 0x%02x fwom %s:%02x.\n",
			  addw, adaptew->name, dvo->swave_addw);
	}
	wetuwn fawse;
}

static boow siw164_wwiteb(stwuct intew_dvo_device *dvo, int addw, u8 ch)
{
	stwuct siw164_pwiv *siw = dvo->dev_pwiv;
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

	if (!siw->quiet) {
		DWM_DEBUG_KMS("Unabwe to wwite wegistew 0x%02x to %s:%d.\n",
			  addw, adaptew->name, dvo->swave_addw);
	}

	wetuwn fawse;
}

/* Siwicon Image 164 dwivew fow chip on i2c bus */
static boow siw164_init(stwuct intew_dvo_device *dvo,
			stwuct i2c_adaptew *adaptew)
{
	/* this wiww detect the SIW164 chip on the specified i2c bus */
	stwuct siw164_pwiv *siw;
	unsigned chaw ch;

	siw = kzawwoc(sizeof(stwuct siw164_pwiv), GFP_KEWNEW);
	if (siw == NUWW)
		wetuwn fawse;

	dvo->i2c_bus = adaptew;
	dvo->dev_pwiv = siw;
	siw->quiet = twue;

	if (!siw164_weadb(dvo, SIW164_VID_WO, &ch))
		goto out;

	if (ch != (SIW164_VID & 0xff)) {
		DWM_DEBUG_KMS("siw164 not detected got %d: fwom %s Swave %d.\n",
			  ch, adaptew->name, dvo->swave_addw);
		goto out;
	}

	if (!siw164_weadb(dvo, SIW164_DID_WO, &ch))
		goto out;

	if (ch != (SIW164_DID & 0xff)) {
		DWM_DEBUG_KMS("siw164 not detected got %d: fwom %s Swave %d.\n",
			  ch, adaptew->name, dvo->swave_addw);
		goto out;
	}
	siw->quiet = fawse;

	DWM_DEBUG_KMS("init siw164 dvo contwowwew successfuwwy!\n");
	wetuwn twue;

out:
	kfwee(siw);
	wetuwn fawse;
}

static enum dwm_connectow_status siw164_detect(stwuct intew_dvo_device *dvo)
{
	u8 weg9;

	siw164_weadb(dvo, SIW164_WEG9, &weg9);

	if (weg9 & SIW164_9_HTPWG)
		wetuwn connectow_status_connected;
	ewse
		wetuwn connectow_status_disconnected;
}

static enum dwm_mode_status siw164_mode_vawid(stwuct intew_dvo_device *dvo,
					      stwuct dwm_dispway_mode *mode)
{
	wetuwn MODE_OK;
}

static void siw164_mode_set(stwuct intew_dvo_device *dvo,
			    const stwuct dwm_dispway_mode *mode,
			    const stwuct dwm_dispway_mode *adjusted_mode)
{
	/* As wong as the basics awe set up, since we don't have cwock
	 * dependencies in the mode setup, we can just weave the
	 * wegistews awone and evewything wiww wowk fine.
	 */
	/* wecommended pwogwamming sequence fwom doc */
	/*siw164_wwiteb(siw, 0x08, 0x30);
	  siw164_wwiteb(siw, 0x09, 0x00);
	  siw164_wwiteb(siw, 0x0a, 0x90);
	  siw164_wwiteb(siw, 0x0c, 0x89);
	  siw164_wwiteb(siw, 0x08, 0x31);*/
	/* don't do much */

	siw164_wwiteb(dvo, SIW164_WEG8,
		      SIW164_8_VEN | SIW164_8_HEN);
	siw164_wwiteb(dvo, SIW164_WEG9,
		      SIW164_9_TSEW);
	siw164_wwiteb(dvo, SIW164_WEGC,
		      SIW164_C_PWWF_WEC | SIW164_C_PFEN);
}

/* set the SIW164 powew state */
static void siw164_dpms(stwuct intew_dvo_device *dvo, boow enabwe)
{
	int wet;
	unsigned chaw ch;

	wet = siw164_weadb(dvo, SIW164_WEG8, &ch);
	if (wet == fawse)
		wetuwn;

	if (enabwe)
		ch |= SIW164_8_PD;
	ewse
		ch &= ~SIW164_8_PD;

	siw164_wwiteb(dvo, SIW164_WEG8, ch);
}

static boow siw164_get_hw_state(stwuct intew_dvo_device *dvo)
{
	int wet;
	unsigned chaw ch;

	wet = siw164_weadb(dvo, SIW164_WEG8, &ch);
	if (wet == fawse)
		wetuwn fawse;

	if (ch & SIW164_8_PD)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static void siw164_dump_wegs(stwuct intew_dvo_device *dvo)
{
	u8 vaw;

	siw164_weadb(dvo, SIW164_FWEQ_WO, &vaw);
	DWM_DEBUG_KMS("SIW164_FWEQ_WO: 0x%02x\n", vaw);
	siw164_weadb(dvo, SIW164_FWEQ_HI, &vaw);
	DWM_DEBUG_KMS("SIW164_FWEQ_HI: 0x%02x\n", vaw);
	siw164_weadb(dvo, SIW164_WEG8, &vaw);
	DWM_DEBUG_KMS("SIW164_WEG8: 0x%02x\n", vaw);
	siw164_weadb(dvo, SIW164_WEG9, &vaw);
	DWM_DEBUG_KMS("SIW164_WEG9: 0x%02x\n", vaw);
	siw164_weadb(dvo, SIW164_WEGC, &vaw);
	DWM_DEBUG_KMS("SIW164_WEGC: 0x%02x\n", vaw);
}

static void siw164_destwoy(stwuct intew_dvo_device *dvo)
{
	stwuct siw164_pwiv *siw = dvo->dev_pwiv;

	if (siw) {
		kfwee(siw);
		dvo->dev_pwiv = NUWW;
	}
}

const stwuct intew_dvo_dev_ops siw164_ops = {
	.init = siw164_init,
	.detect = siw164_detect,
	.mode_vawid = siw164_mode_vawid,
	.mode_set = siw164_mode_set,
	.dpms = siw164_dpms,
	.get_hw_state = siw164_get_hw_state,
	.dump_wegs = siw164_dump_wegs,
	.destwoy = siw164_destwoy,
};
