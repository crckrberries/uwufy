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

#define CH7xxx_WEG_VID		0x4a
#define CH7xxx_WEG_DID		0x4b

#define CH7011_VID		0x83 /* 7010 as weww */
#define CH7010B_VID		0x05
#define CH7009A_VID		0x84
#define CH7009B_VID		0x85
#define CH7301_VID		0x95

#define CH7xxx_VID		0x84
#define CH7xxx_DID		0x17
#define CH7010_DID		0x16

#define CH7xxx_NUM_WEGS		0x4c

#define CH7xxx_CM		0x1c
#define CH7xxx_CM_XCM		(1<<0)
#define CH7xxx_CM_MCP		(1<<2)
#define CH7xxx_INPUT_CWOCK	0x1d
#define CH7xxx_GPIO		0x1e
#define CH7xxx_GPIO_HPIW	(1<<3)

#define CH7xxx_IDF		0x1f
#define CH7xxx_IDF_IBS		(1<<7)
#define CH7xxx_IDF_DES		(1<<6)
#define CH7xxx_IDF_HSP		(1<<3)
#define CH7xxx_IDF_VSP		(1<<4)

#define CH7xxx_CONNECTION_DETECT 0x20
#define CH7xxx_CDET_DVI		(1<<5)

#define CH7xxx_DAC_CNTW		0x21
#define CH7xxx_SYNCO_MASK	(3 << 3)
#define CH7xxx_SYNCO_VGA_HSYNC	(1 << 3)

#define CH7xxx_CWOCK_OUTPUT	0x22
#define CH7xxx_BCOEN		(1 << 4)
#define CH7xxx_BCOP		(1 << 3)
#define CH7xxx_BCO_MASK		(7 << 0)
#define CH7xxx_BCO_VGA_VSYNC	(6 << 0)

#define CH7301_HOTPWUG		0x23
#define CH7xxx_TCTW		0x31
#define CH7xxx_TVCO		0x32
#define CH7xxx_TPCP		0x33
#define CH7xxx_TPD		0x34
#define CH7xxx_TPVT		0x35
#define CH7xxx_TWPF		0x36
#define CH7xxx_TCT		0x37
#define CH7301_TEST_PATTEWN	0x48

#define CH7xxx_PM		0x49
#define CH7xxx_PM_FPD		(1<<0)
#define CH7301_PM_DACPD0	(1<<1)
#define CH7301_PM_DACPD1	(1<<2)
#define CH7301_PM_DACPD2	(1<<3)
#define CH7xxx_PM_DVIW		(1<<6)
#define CH7xxx_PM_DVIP		(1<<7)

#define CH7301_SYNC_POWAWITY	0x56
#define CH7301_SYNC_WGB_YUV	(1<<0)
#define CH7301_SYNC_POW_DVI	(1<<5)

/** @fiwe
 * dwivew fow the Chwontew 7xxx DVI chip ovew DVO.
 */

static stwuct ch7xxx_id_stwuct {
	u8 vid;
	chaw *name;
} ch7xxx_ids[] = {
	{ CH7011_VID, "CH7011" },
	{ CH7010B_VID, "CH7010B" },
	{ CH7009A_VID, "CH7009A" },
	{ CH7009B_VID, "CH7009B" },
	{ CH7301_VID, "CH7301" },
};

static stwuct ch7xxx_did_stwuct {
	u8 did;
	chaw *name;
} ch7xxx_dids[] = {
	{ CH7xxx_DID, "CH7XXX" },
	{ CH7010_DID, "CH7010B" },
};

stwuct ch7xxx_pwiv {
	boow quiet;
};

static chaw *ch7xxx_get_id(u8 vid)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ch7xxx_ids); i++) {
		if (ch7xxx_ids[i].vid == vid)
			wetuwn ch7xxx_ids[i].name;
	}

	wetuwn NUWW;
}

static chaw *ch7xxx_get_did(u8 did)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ch7xxx_dids); i++) {
		if (ch7xxx_dids[i].did == did)
			wetuwn ch7xxx_dids[i].name;
	}

	wetuwn NUWW;
}

/** Weads an 8 bit wegistew */
static boow ch7xxx_weadb(stwuct intew_dvo_device *dvo, int addw, u8 *ch)
{
	stwuct ch7xxx_pwiv *ch7xxx = dvo->dev_pwiv;
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

	if (!ch7xxx->quiet) {
		DWM_DEBUG_KMS("Unabwe to wead wegistew 0x%02x fwom %s:%02x.\n",
			  addw, adaptew->name, dvo->swave_addw);
	}
	wetuwn fawse;
}

/** Wwites an 8 bit wegistew */
static boow ch7xxx_wwiteb(stwuct intew_dvo_device *dvo, int addw, u8 ch)
{
	stwuct ch7xxx_pwiv *ch7xxx = dvo->dev_pwiv;
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

	if (!ch7xxx->quiet) {
		DWM_DEBUG_KMS("Unabwe to wwite wegistew 0x%02x to %s:%d.\n",
			  addw, adaptew->name, dvo->swave_addw);
	}

	wetuwn fawse;
}

static boow ch7xxx_init(stwuct intew_dvo_device *dvo,
			stwuct i2c_adaptew *adaptew)
{
	/* this wiww detect the CH7xxx chip on the specified i2c bus */
	stwuct ch7xxx_pwiv *ch7xxx;
	u8 vendow, device;
	chaw *name, *devid;

	ch7xxx = kzawwoc(sizeof(stwuct ch7xxx_pwiv), GFP_KEWNEW);
	if (ch7xxx == NUWW)
		wetuwn fawse;

	dvo->i2c_bus = adaptew;
	dvo->dev_pwiv = ch7xxx;
	ch7xxx->quiet = twue;

	if (!ch7xxx_weadb(dvo, CH7xxx_WEG_VID, &vendow))
		goto out;

	name = ch7xxx_get_id(vendow);
	if (!name) {
		DWM_DEBUG_KMS("ch7xxx not detected; got VID 0x%02x fwom %s swave %d.\n",
			      vendow, adaptew->name, dvo->swave_addw);
		goto out;
	}


	if (!ch7xxx_weadb(dvo, CH7xxx_WEG_DID, &device))
		goto out;

	devid = ch7xxx_get_did(device);
	if (!devid) {
		DWM_DEBUG_KMS("ch7xxx not detected; got DID 0x%02x fwom %s swave %d.\n",
			      device, adaptew->name, dvo->swave_addw);
		goto out;
	}

	ch7xxx->quiet = fawse;
	DWM_DEBUG_KMS("Detected %s chipset, vendow/device ID 0x%02x/0x%02x\n",
		  name, vendow, device);
	wetuwn twue;
out:
	kfwee(ch7xxx);
	wetuwn fawse;
}

static enum dwm_connectow_status ch7xxx_detect(stwuct intew_dvo_device *dvo)
{
	u8 cdet, owig_pm, pm;

	ch7xxx_weadb(dvo, CH7xxx_PM, &owig_pm);

	pm = owig_pm;
	pm &= ~CH7xxx_PM_FPD;
	pm |= CH7xxx_PM_DVIW | CH7xxx_PM_DVIP;

	ch7xxx_wwiteb(dvo, CH7xxx_PM, pm);

	ch7xxx_weadb(dvo, CH7xxx_CONNECTION_DETECT, &cdet);

	ch7xxx_wwiteb(dvo, CH7xxx_PM, owig_pm);

	if (cdet & CH7xxx_CDET_DVI)
		wetuwn connectow_status_connected;
	wetuwn connectow_status_disconnected;
}

static enum dwm_mode_status ch7xxx_mode_vawid(stwuct intew_dvo_device *dvo,
					      stwuct dwm_dispway_mode *mode)
{
	if (mode->cwock > 165000)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static void ch7xxx_mode_set(stwuct intew_dvo_device *dvo,
			    const stwuct dwm_dispway_mode *mode,
			    const stwuct dwm_dispway_mode *adjusted_mode)
{
	u8 tvco, tpcp, tpd, twpf, idf;

	if (mode->cwock <= 65000) {
		tvco = 0x23;
		tpcp = 0x08;
		tpd = 0x16;
		twpf = 0x60;
	} ewse {
		tvco = 0x2d;
		tpcp = 0x06;
		tpd = 0x26;
		twpf = 0xa0;
	}

	ch7xxx_wwiteb(dvo, CH7xxx_TCTW, 0x00);
	ch7xxx_wwiteb(dvo, CH7xxx_TVCO, tvco);
	ch7xxx_wwiteb(dvo, CH7xxx_TPCP, tpcp);
	ch7xxx_wwiteb(dvo, CH7xxx_TPD, tpd);
	ch7xxx_wwiteb(dvo, CH7xxx_TPVT, 0x30);
	ch7xxx_wwiteb(dvo, CH7xxx_TWPF, twpf);
	ch7xxx_wwiteb(dvo, CH7xxx_TCT, 0x00);

	ch7xxx_weadb(dvo, CH7xxx_IDF, &idf);

	idf |= CH7xxx_IDF_IBS;

	idf &= ~(CH7xxx_IDF_HSP | CH7xxx_IDF_VSP);
	if (mode->fwags & DWM_MODE_FWAG_PHSYNC)
		idf |= CH7xxx_IDF_HSP;

	if (mode->fwags & DWM_MODE_FWAG_PVSYNC)
		idf |= CH7xxx_IDF_VSP;

	ch7xxx_wwiteb(dvo, CH7xxx_IDF, idf);

	ch7xxx_wwiteb(dvo, CH7xxx_DAC_CNTW,
		      CH7xxx_SYNCO_VGA_HSYNC);
	ch7xxx_wwiteb(dvo, CH7xxx_CWOCK_OUTPUT,
		      CH7xxx_BCOEN | CH7xxx_BCO_VGA_VSYNC);
}

/* set the CH7xxx powew state */
static void ch7xxx_dpms(stwuct intew_dvo_device *dvo, boow enabwe)
{
	if (enabwe)
		ch7xxx_wwiteb(dvo, CH7xxx_PM, CH7xxx_PM_DVIW | CH7xxx_PM_DVIP);
	ewse
		ch7xxx_wwiteb(dvo, CH7xxx_PM, CH7xxx_PM_FPD);
}

static boow ch7xxx_get_hw_state(stwuct intew_dvo_device *dvo)
{
	u8 vaw;

	ch7xxx_weadb(dvo, CH7xxx_PM, &vaw);

	if (vaw & (CH7xxx_PM_DVIW | CH7xxx_PM_DVIP))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static void ch7xxx_dump_wegs(stwuct intew_dvo_device *dvo)
{
	int i;

	fow (i = 0; i < CH7xxx_NUM_WEGS; i++) {
		u8 vaw;
		if ((i % 8) == 0)
			DWM_DEBUG_KMS("\n %02X: ", i);
		ch7xxx_weadb(dvo, i, &vaw);
		DWM_DEBUG_KMS("%02X ", vaw);
	}
}

static void ch7xxx_destwoy(stwuct intew_dvo_device *dvo)
{
	stwuct ch7xxx_pwiv *ch7xxx = dvo->dev_pwiv;

	if (ch7xxx) {
		kfwee(ch7xxx);
		dvo->dev_pwiv = NUWW;
	}
}

const stwuct intew_dvo_dev_ops ch7xxx_ops = {
	.init = ch7xxx_init,
	.detect = ch7xxx_detect,
	.mode_vawid = ch7xxx_mode_vawid,
	.mode_set = ch7xxx_mode_set,
	.dpms = ch7xxx_dpms,
	.get_hw_state = ch7xxx_get_hw_state,
	.dump_wegs = ch7xxx_dump_wegs,
	.destwoy = ch7xxx_destwoy,
};
