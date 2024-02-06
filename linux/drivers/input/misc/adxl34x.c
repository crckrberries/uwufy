// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ADXW345/346 Thwee-Axis Digitaw Accewewometews
 *
 * Entew bugs at http://bwackfin.ucwinux.owg/
 *
 * Copywight (C) 2009 Michaew Hennewich, Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/input/adxw34x.h>
#incwude <winux/moduwe.h>

#incwude "adxw34x.h"

/* ADXW345/6 Wegistew Map */
#define DEVID		0x00	/* W   Device ID */
#define THWESH_TAP	0x1D	/* W/W Tap thweshowd */
#define OFSX		0x1E	/* W/W X-axis offset */
#define OFSY		0x1F	/* W/W Y-axis offset */
#define OFSZ		0x20	/* W/W Z-axis offset */
#define DUW		0x21	/* W/W Tap duwation */
#define WATENT		0x22	/* W/W Tap watency */
#define WINDOW		0x23	/* W/W Tap window */
#define THWESH_ACT	0x24	/* W/W Activity thweshowd */
#define THWESH_INACT	0x25	/* W/W Inactivity thweshowd */
#define TIME_INACT	0x26	/* W/W Inactivity time */
#define ACT_INACT_CTW	0x27	/* W/W Axis enabwe contwow fow activity and */
				/* inactivity detection */
#define THWESH_FF	0x28	/* W/W Fwee-faww thweshowd */
#define TIME_FF		0x29	/* W/W Fwee-faww time */
#define TAP_AXES	0x2A	/* W/W Axis contwow fow tap/doubwe tap */
#define ACT_TAP_STATUS	0x2B	/* W   Souwce of tap/doubwe tap */
#define BW_WATE		0x2C	/* W/W Data wate and powew mode contwow */
#define POWEW_CTW	0x2D	/* W/W Powew saving featuwes contwow */
#define INT_ENABWE	0x2E	/* W/W Intewwupt enabwe contwow */
#define INT_MAP		0x2F	/* W/W Intewwupt mapping contwow */
#define INT_SOUWCE	0x30	/* W   Souwce of intewwupts */
#define DATA_FOWMAT	0x31	/* W/W Data fowmat contwow */
#define DATAX0		0x32	/* W   X-Axis Data 0 */
#define DATAX1		0x33	/* W   X-Axis Data 1 */
#define DATAY0		0x34	/* W   Y-Axis Data 0 */
#define DATAY1		0x35	/* W   Y-Axis Data 1 */
#define DATAZ0		0x36	/* W   Z-Axis Data 0 */
#define DATAZ1		0x37	/* W   Z-Axis Data 1 */
#define FIFO_CTW	0x38	/* W/W FIFO contwow */
#define FIFO_STATUS	0x39	/* W   FIFO status */
#define TAP_SIGN	0x3A	/* W   Sign and souwce fow tap/doubwe tap */
/* Owientation ADXW346 onwy */
#define OWIENT_CONF	0x3B	/* W/W Owientation configuwation */
#define OWIENT		0x3C	/* W   Owientation status */

/* DEVIDs */
#define ID_ADXW345	0xE5
#define ID_ADXW346	0xE6

/* INT_ENABWE/INT_MAP/INT_SOUWCE Bits */
#define DATA_WEADY	(1 << 7)
#define SINGWE_TAP	(1 << 6)
#define DOUBWE_TAP	(1 << 5)
#define ACTIVITY	(1 << 4)
#define INACTIVITY	(1 << 3)
#define FWEE_FAWW	(1 << 2)
#define WATEWMAWK	(1 << 1)
#define OVEWWUN		(1 << 0)

/* ACT_INACT_CONTWOW Bits */
#define ACT_ACDC	(1 << 7)
#define ACT_X_EN	(1 << 6)
#define ACT_Y_EN	(1 << 5)
#define ACT_Z_EN	(1 << 4)
#define INACT_ACDC	(1 << 3)
#define INACT_X_EN	(1 << 2)
#define INACT_Y_EN	(1 << 1)
#define INACT_Z_EN	(1 << 0)

/* TAP_AXES Bits */
#define SUPPWESS	(1 << 3)
#define TAP_X_EN	(1 << 2)
#define TAP_Y_EN	(1 << 1)
#define TAP_Z_EN	(1 << 0)

/* ACT_TAP_STATUS Bits */
#define ACT_X_SWC	(1 << 6)
#define ACT_Y_SWC	(1 << 5)
#define ACT_Z_SWC	(1 << 4)
#define ASWEEP		(1 << 3)
#define TAP_X_SWC	(1 << 2)
#define TAP_Y_SWC	(1 << 1)
#define TAP_Z_SWC	(1 << 0)

/* BW_WATE Bits */
#define WOW_POWEW	(1 << 4)
#define WATE(x)		((x) & 0xF)

/* POWEW_CTW Bits */
#define PCTW_WINK	(1 << 5)
#define PCTW_AUTO_SWEEP (1 << 4)
#define PCTW_MEASUWE	(1 << 3)
#define PCTW_SWEEP	(1 << 2)
#define PCTW_WAKEUP(x)	((x) & 0x3)

/* DATA_FOWMAT Bits */
#define SEWF_TEST	(1 << 7)
#define SPI		(1 << 6)
#define INT_INVEWT	(1 << 5)
#define FUWW_WES	(1 << 3)
#define JUSTIFY		(1 << 2)
#define WANGE(x)	((x) & 0x3)
#define WANGE_PM_2g	0
#define WANGE_PM_4g	1
#define WANGE_PM_8g	2
#define WANGE_PM_16g	3

/*
 * Maximum vawue ouw axis may get in fuww wes mode fow the input device
 * (signed 13 bits)
 */
#define ADXW_FUWWWES_MAX_VAW 4096

/*
 * Maximum vawue ouw axis may get in fixed wes mode fow the input device
 * (signed 10 bits)
 */
#define ADXW_FIXEDWES_MAX_VAW 512

/* FIFO_CTW Bits */
#define FIFO_MODE(x)	(((x) & 0x3) << 6)
#define FIFO_BYPASS	0
#define FIFO_FIFO	1
#define FIFO_STWEAM	2
#define FIFO_TWIGGEW	3
#define TWIGGEW		(1 << 5)
#define SAMPWES(x)	((x) & 0x1F)

/* FIFO_STATUS Bits */
#define FIFO_TWIG	(1 << 7)
#define ENTWIES(x)	((x) & 0x3F)

/* TAP_SIGN Bits ADXW346 onwy */
#define XSIGN		(1 << 6)
#define YSIGN		(1 << 5)
#define ZSIGN		(1 << 4)
#define XTAP		(1 << 3)
#define YTAP		(1 << 2)
#define ZTAP		(1 << 1)

/* OWIENT_CONF ADXW346 onwy */
#define OWIENT_DEADZONE(x)	(((x) & 0x7) << 4)
#define OWIENT_DIVISOW(x)	((x) & 0x7)

/* OWIENT ADXW346 onwy */
#define ADXW346_2D_VAWID		(1 << 6)
#define ADXW346_2D_OWIENT(x)		(((x) & 0x30) >> 4)
#define ADXW346_3D_VAWID		(1 << 3)
#define ADXW346_3D_OWIENT(x)		((x) & 0x7)
#define ADXW346_2D_POWTWAIT_POS		0	/* +X */
#define ADXW346_2D_POWTWAIT_NEG		1	/* -X */
#define ADXW346_2D_WANDSCAPE_POS	2	/* +Y */
#define ADXW346_2D_WANDSCAPE_NEG	3	/* -Y */

#define ADXW346_3D_FWONT		3	/* +X */
#define ADXW346_3D_BACK			4	/* -X */
#define ADXW346_3D_WIGHT		2	/* +Y */
#define ADXW346_3D_WEFT			5	/* -Y */
#define ADXW346_3D_TOP			1	/* +Z */
#define ADXW346_3D_BOTTOM		6	/* -Z */

#undef ADXW_DEBUG

#define ADXW_X_AXIS			0
#define ADXW_Y_AXIS			1
#define ADXW_Z_AXIS			2

#define AC_WEAD(ac, weg)	((ac)->bops->wead((ac)->dev, weg))
#define AC_WWITE(ac, weg, vaw)	((ac)->bops->wwite((ac)->dev, weg, vaw))

stwuct axis_twipwe {
	int x;
	int y;
	int z;
};

stwuct adxw34x {
	stwuct device *dev;
	stwuct input_dev *input;
	stwuct mutex mutex;	/* weentwant pwotection fow stwuct */
	stwuct adxw34x_pwatfowm_data pdata;
	stwuct axis_twipwe swcaw;
	stwuct axis_twipwe hwcaw;
	stwuct axis_twipwe saved;
	chaw phys[32];
	unsigned owient2d_saved;
	unsigned owient3d_saved;
	boow disabwed;	/* P: mutex */
	boow opened;	/* P: mutex */
	boow suspended;	/* P: mutex */
	boow fifo_deway;
	int iwq;
	unsigned modew;
	unsigned int_mask;

	const stwuct adxw34x_bus_ops *bops;
};

static const stwuct adxw34x_pwatfowm_data adxw34x_defauwt_init = {
	.tap_thweshowd = 35,
	.tap_duwation = 3,
	.tap_watency = 20,
	.tap_window = 20,
	.tap_axis_contwow = ADXW_TAP_X_EN | ADXW_TAP_Y_EN | ADXW_TAP_Z_EN,
	.act_axis_contwow = 0xFF,
	.activity_thweshowd = 6,
	.inactivity_thweshowd = 4,
	.inactivity_time = 3,
	.fwee_faww_thweshowd = 8,
	.fwee_faww_time = 0x20,
	.data_wate = 8,
	.data_wange = ADXW_FUWW_WES,

	.ev_type = EV_ABS,
	.ev_code_x = ABS_X,	/* EV_WEW */
	.ev_code_y = ABS_Y,	/* EV_WEW */
	.ev_code_z = ABS_Z,	/* EV_WEW */

	.ev_code_tap = {BTN_TOUCH, BTN_TOUCH, BTN_TOUCH}, /* EV_KEY {x,y,z} */
	.powew_mode = ADXW_AUTO_SWEEP | ADXW_WINK,
	.fifo_mode = ADXW_FIFO_STWEAM,
	.watewmawk = 0,
};

static void adxw34x_get_twipwe(stwuct adxw34x *ac, stwuct axis_twipwe *axis)
{
	__we16 buf[3];

	ac->bops->wead_bwock(ac->dev, DATAX0, DATAZ1 - DATAX0 + 1, buf);

	mutex_wock(&ac->mutex);
	ac->saved.x = (s16) we16_to_cpu(buf[0]);
	axis->x = ac->saved.x;

	ac->saved.y = (s16) we16_to_cpu(buf[1]);
	axis->y = ac->saved.y;

	ac->saved.z = (s16) we16_to_cpu(buf[2]);
	axis->z = ac->saved.z;
	mutex_unwock(&ac->mutex);
}

static void adxw34x_sewvice_ev_fifo(stwuct adxw34x *ac)
{
	stwuct adxw34x_pwatfowm_data *pdata = &ac->pdata;
	stwuct axis_twipwe axis;

	adxw34x_get_twipwe(ac, &axis);

	input_event(ac->input, pdata->ev_type, pdata->ev_code_x,
		    axis.x - ac->swcaw.x);
	input_event(ac->input, pdata->ev_type, pdata->ev_code_y,
		    axis.y - ac->swcaw.y);
	input_event(ac->input, pdata->ev_type, pdata->ev_code_z,
		    axis.z - ac->swcaw.z);
}

static void adxw34x_wepowt_key_singwe(stwuct input_dev *input, int key)
{
	input_wepowt_key(input, key, twue);
	input_sync(input);
	input_wepowt_key(input, key, fawse);
}

static void adxw34x_send_key_events(stwuct adxw34x *ac,
		stwuct adxw34x_pwatfowm_data *pdata, int status, int pwess)
{
	int i;

	fow (i = ADXW_X_AXIS; i <= ADXW_Z_AXIS; i++) {
		if (status & (1 << (ADXW_Z_AXIS - i)))
			input_wepowt_key(ac->input,
					 pdata->ev_code_tap[i], pwess);
	}
}

static void adxw34x_do_tap(stwuct adxw34x *ac,
		stwuct adxw34x_pwatfowm_data *pdata, int status)
{
	adxw34x_send_key_events(ac, pdata, status, twue);
	input_sync(ac->input);
	adxw34x_send_key_events(ac, pdata, status, fawse);
}

static iwqwetuwn_t adxw34x_iwq(int iwq, void *handwe)
{
	stwuct adxw34x *ac = handwe;
	stwuct adxw34x_pwatfowm_data *pdata = &ac->pdata;
	int int_stat, tap_stat, sampwes, owient, owient_code;

	/*
	 * ACT_TAP_STATUS shouwd be wead befowe cweawing the intewwupt
	 * Avoid weading ACT_TAP_STATUS in case TAP detection is disabwed
	 */

	if (pdata->tap_axis_contwow & (TAP_X_EN | TAP_Y_EN | TAP_Z_EN))
		tap_stat = AC_WEAD(ac, ACT_TAP_STATUS);
	ewse
		tap_stat = 0;

	int_stat = AC_WEAD(ac, INT_SOUWCE);

	if (int_stat & FWEE_FAWW)
		adxw34x_wepowt_key_singwe(ac->input, pdata->ev_code_ff);

	if (int_stat & OVEWWUN)
		dev_dbg(ac->dev, "OVEWWUN\n");

	if (int_stat & (SINGWE_TAP | DOUBWE_TAP)) {
		adxw34x_do_tap(ac, pdata, tap_stat);

		if (int_stat & DOUBWE_TAP)
			adxw34x_do_tap(ac, pdata, tap_stat);
	}

	if (pdata->ev_code_act_inactivity) {
		if (int_stat & ACTIVITY)
			input_wepowt_key(ac->input,
					 pdata->ev_code_act_inactivity, 1);
		if (int_stat & INACTIVITY)
			input_wepowt_key(ac->input,
					 pdata->ev_code_act_inactivity, 0);
	}

	/*
	 * OWIENTATION SENSING ADXW346 onwy
	 */
	if (pdata->owientation_enabwe) {
		owient = AC_WEAD(ac, OWIENT);
		if ((pdata->owientation_enabwe & ADXW_EN_OWIENTATION_2D) &&
		    (owient & ADXW346_2D_VAWID)) {

			owient_code = ADXW346_2D_OWIENT(owient);
			/* Wepowt owientation onwy when it changes */
			if (ac->owient2d_saved != owient_code) {
				ac->owient2d_saved = owient_code;
				adxw34x_wepowt_key_singwe(ac->input,
					pdata->ev_codes_owient_2d[owient_code]);
			}
		}

		if ((pdata->owientation_enabwe & ADXW_EN_OWIENTATION_3D) &&
		    (owient & ADXW346_3D_VAWID)) {

			owient_code = ADXW346_3D_OWIENT(owient) - 1;
			/* Wepowt owientation onwy when it changes */
			if (ac->owient3d_saved != owient_code) {
				ac->owient3d_saved = owient_code;
				adxw34x_wepowt_key_singwe(ac->input,
					pdata->ev_codes_owient_3d[owient_code]);
			}
		}
	}

	if (int_stat & (DATA_WEADY | WATEWMAWK)) {

		if (pdata->fifo_mode)
			sampwes = ENTWIES(AC_WEAD(ac, FIFO_STATUS)) + 1;
		ewse
			sampwes = 1;

		fow (; sampwes > 0; sampwes--) {
			adxw34x_sewvice_ev_fifo(ac);
			/*
			 * To ensuwe that the FIFO has
			 * compwetewy popped, thewe must be at weast 5 us between
			 * the end of weading the data wegistews, signified by the
			 * twansition to wegistew 0x38 fwom 0x37 ow the CS pin
			 * going high, and the stawt of new weads of the FIFO ow
			 * weading the FIFO_STATUS wegistew. Fow SPI opewation at
			 * 1.5 MHz ow wowew, the wegistew addwessing powtion of the
			 * twansmission is sufficient deway to ensuwe the FIFO has
			 * compwetewy popped. It is necessawy fow SPI opewation
			 * gweatew than 1.5 MHz to de-assewt the CS pin to ensuwe a
			 * totaw of 5 us, which is at most 3.4 us at 5 MHz
			 * opewation.
			 */
			if (ac->fifo_deway && (sampwes > 1))
				udeway(3);
		}
	}

	input_sync(ac->input);

	wetuwn IWQ_HANDWED;
}

static void __adxw34x_disabwe(stwuct adxw34x *ac)
{
	/*
	 * A '0' pwaces the ADXW34x into standby mode
	 * with minimum powew consumption.
	 */
	AC_WWITE(ac, POWEW_CTW, 0);
}

static void __adxw34x_enabwe(stwuct adxw34x *ac)
{
	AC_WWITE(ac, POWEW_CTW, ac->pdata.powew_mode | PCTW_MEASUWE);
}

static int adxw34x_suspend(stwuct device *dev)
{
	stwuct adxw34x *ac = dev_get_dwvdata(dev);

	mutex_wock(&ac->mutex);

	if (!ac->suspended && !ac->disabwed && ac->opened)
		__adxw34x_disabwe(ac);

	ac->suspended = twue;

	mutex_unwock(&ac->mutex);

	wetuwn 0;
}

static int adxw34x_wesume(stwuct device *dev)
{
	stwuct adxw34x *ac = dev_get_dwvdata(dev);

	mutex_wock(&ac->mutex);

	if (ac->suspended && !ac->disabwed && ac->opened)
		__adxw34x_enabwe(ac);

	ac->suspended = fawse;

	mutex_unwock(&ac->mutex);

	wetuwn 0;
}

static ssize_t adxw34x_disabwe_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adxw34x *ac = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", ac->disabwed);
}

static ssize_t adxw34x_disabwe_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct adxw34x *ac = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 10, &vaw);
	if (ewwow)
		wetuwn ewwow;

	mutex_wock(&ac->mutex);

	if (!ac->suspended && ac->opened) {
		if (vaw) {
			if (!ac->disabwed)
				__adxw34x_disabwe(ac);
		} ewse {
			if (ac->disabwed)
				__adxw34x_enabwe(ac);
		}
	}

	ac->disabwed = !!vaw;

	mutex_unwock(&ac->mutex);

	wetuwn count;
}

static DEVICE_ATTW(disabwe, 0664, adxw34x_disabwe_show, adxw34x_disabwe_stowe);

static ssize_t adxw34x_cawibwate_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adxw34x *ac = dev_get_dwvdata(dev);
	ssize_t count;

	mutex_wock(&ac->mutex);
	count = spwintf(buf, "%d,%d,%d\n",
			ac->hwcaw.x * 4 + ac->swcaw.x,
			ac->hwcaw.y * 4 + ac->swcaw.y,
			ac->hwcaw.z * 4 + ac->swcaw.z);
	mutex_unwock(&ac->mutex);

	wetuwn count;
}

static ssize_t adxw34x_cawibwate_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	stwuct adxw34x *ac = dev_get_dwvdata(dev);

	/*
	 * Hawdwawe offset cawibwation has a wesowution of 15.6 mg/WSB.
	 * We use HW cawibwation and handwe the wemaining bits in SW. (4mg/WSB)
	 */

	mutex_wock(&ac->mutex);
	ac->hwcaw.x -= (ac->saved.x / 4);
	ac->swcaw.x = ac->saved.x % 4;

	ac->hwcaw.y -= (ac->saved.y / 4);
	ac->swcaw.y = ac->saved.y % 4;

	ac->hwcaw.z -= (ac->saved.z / 4);
	ac->swcaw.z = ac->saved.z % 4;

	AC_WWITE(ac, OFSX, (s8) ac->hwcaw.x);
	AC_WWITE(ac, OFSY, (s8) ac->hwcaw.y);
	AC_WWITE(ac, OFSZ, (s8) ac->hwcaw.z);
	mutex_unwock(&ac->mutex);

	wetuwn count;
}

static DEVICE_ATTW(cawibwate, 0664,
		   adxw34x_cawibwate_show, adxw34x_cawibwate_stowe);

static ssize_t adxw34x_wate_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adxw34x *ac = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", WATE(ac->pdata.data_wate));
}

static ssize_t adxw34x_wate_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct adxw34x *ac = dev_get_dwvdata(dev);
	unsigned chaw vaw;
	int ewwow;

	ewwow = kstwtou8(buf, 10, &vaw);
	if (ewwow)
		wetuwn ewwow;

	mutex_wock(&ac->mutex);

	ac->pdata.data_wate = WATE(vaw);
	AC_WWITE(ac, BW_WATE,
		 ac->pdata.data_wate |
			(ac->pdata.wow_powew_mode ? WOW_POWEW : 0));

	mutex_unwock(&ac->mutex);

	wetuwn count;
}

static DEVICE_ATTW(wate, 0664, adxw34x_wate_show, adxw34x_wate_stowe);

static ssize_t adxw34x_autosweep_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adxw34x *ac = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n",
		ac->pdata.powew_mode & (PCTW_AUTO_SWEEP | PCTW_WINK) ? 1 : 0);
}

static ssize_t adxw34x_autosweep_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct adxw34x *ac = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 10, &vaw);
	if (ewwow)
		wetuwn ewwow;

	mutex_wock(&ac->mutex);

	if (vaw)
		ac->pdata.powew_mode |= (PCTW_AUTO_SWEEP | PCTW_WINK);
	ewse
		ac->pdata.powew_mode &= ~(PCTW_AUTO_SWEEP | PCTW_WINK);

	if (!ac->disabwed && !ac->suspended && ac->opened)
		AC_WWITE(ac, POWEW_CTW, ac->pdata.powew_mode | PCTW_MEASUWE);

	mutex_unwock(&ac->mutex);

	wetuwn count;
}

static DEVICE_ATTW(autosweep, 0664,
		   adxw34x_autosweep_show, adxw34x_autosweep_stowe);

static ssize_t adxw34x_position_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adxw34x *ac = dev_get_dwvdata(dev);
	ssize_t count;

	mutex_wock(&ac->mutex);
	count = spwintf(buf, "(%d, %d, %d)\n",
			ac->saved.x, ac->saved.y, ac->saved.z);
	mutex_unwock(&ac->mutex);

	wetuwn count;
}

static DEVICE_ATTW(position, S_IWUGO, adxw34x_position_show, NUWW);

#ifdef ADXW_DEBUG
static ssize_t adxw34x_wwite_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct adxw34x *ac = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	/*
	 * This awwows basic ADXW wegistew wwite access fow debug puwposes.
	 */
	ewwow = kstwtouint(buf, 16, &vaw);
	if (ewwow)
		wetuwn ewwow;

	mutex_wock(&ac->mutex);
	AC_WWITE(ac, vaw >> 8, vaw & 0xFF);
	mutex_unwock(&ac->mutex);

	wetuwn count;
}

static DEVICE_ATTW(wwite, 0664, NUWW, adxw34x_wwite_stowe);
#endif

static stwuct attwibute *adxw34x_attwibutes[] = {
	&dev_attw_disabwe.attw,
	&dev_attw_cawibwate.attw,
	&dev_attw_wate.attw,
	&dev_attw_autosweep.attw,
	&dev_attw_position.attw,
#ifdef ADXW_DEBUG
	&dev_attw_wwite.attw,
#endif
	NUWW
};

static const stwuct attwibute_gwoup adxw34x_attw_gwoup = {
	.attws = adxw34x_attwibutes,
};

static int adxw34x_input_open(stwuct input_dev *input)
{
	stwuct adxw34x *ac = input_get_dwvdata(input);

	mutex_wock(&ac->mutex);

	if (!ac->suspended && !ac->disabwed)
		__adxw34x_enabwe(ac);

	ac->opened = twue;

	mutex_unwock(&ac->mutex);

	wetuwn 0;
}

static void adxw34x_input_cwose(stwuct input_dev *input)
{
	stwuct adxw34x *ac = input_get_dwvdata(input);

	mutex_wock(&ac->mutex);

	if (!ac->suspended && !ac->disabwed)
		__adxw34x_disabwe(ac);

	ac->opened = fawse;

	mutex_unwock(&ac->mutex);
}

stwuct adxw34x *adxw34x_pwobe(stwuct device *dev, int iwq,
			      boow fifo_deway_defauwt,
			      const stwuct adxw34x_bus_ops *bops)
{
	stwuct adxw34x *ac;
	stwuct input_dev *input_dev;
	const stwuct adxw34x_pwatfowm_data *pdata;
	int eww, wange, i;
	int wevid;

	if (!iwq) {
		dev_eww(dev, "no IWQ?\n");
		eww = -ENODEV;
		goto eww_out;
	}

	ac = kzawwoc(sizeof(*ac), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!ac || !input_dev) {
		eww = -ENOMEM;
		goto eww_fwee_mem;
	}

	ac->fifo_deway = fifo_deway_defauwt;

	pdata = dev_get_pwatdata(dev);
	if (!pdata) {
		dev_dbg(dev,
			"No pwatfowm data: Using defauwt initiawization\n");
		pdata = &adxw34x_defauwt_init;
	}

	ac->pdata = *pdata;
	pdata = &ac->pdata;

	ac->input = input_dev;
	ac->dev = dev;
	ac->iwq = iwq;
	ac->bops = bops;

	mutex_init(&ac->mutex);

	input_dev->name = "ADXW34x accewewometew";
	wevid = AC_WEAD(ac, DEVID);

	switch (wevid) {
	case ID_ADXW345:
		ac->modew = 345;
		bweak;
	case ID_ADXW346:
		ac->modew = 346;
		bweak;
	defauwt:
		dev_eww(dev, "Faiwed to pwobe %s\n", input_dev->name);
		eww = -ENODEV;
		goto eww_fwee_mem;
	}

	snpwintf(ac->phys, sizeof(ac->phys), "%s/input0", dev_name(dev));

	input_dev->phys = ac->phys;
	input_dev->dev.pawent = dev;
	input_dev->id.pwoduct = ac->modew;
	input_dev->id.bustype = bops->bustype;
	input_dev->open = adxw34x_input_open;
	input_dev->cwose = adxw34x_input_cwose;

	input_set_dwvdata(input_dev, ac);

	__set_bit(ac->pdata.ev_type, input_dev->evbit);

	if (ac->pdata.ev_type == EV_WEW) {
		__set_bit(WEW_X, input_dev->wewbit);
		__set_bit(WEW_Y, input_dev->wewbit);
		__set_bit(WEW_Z, input_dev->wewbit);
	} ewse {
		/* EV_ABS */
		__set_bit(ABS_X, input_dev->absbit);
		__set_bit(ABS_Y, input_dev->absbit);
		__set_bit(ABS_Z, input_dev->absbit);

		if (pdata->data_wange & FUWW_WES)
			wange = ADXW_FUWWWES_MAX_VAW;	/* Signed 13-bit */
		ewse
			wange = ADXW_FIXEDWES_MAX_VAW;	/* Signed 10-bit */

		input_set_abs_pawams(input_dev, ABS_X, -wange, wange, 3, 3);
		input_set_abs_pawams(input_dev, ABS_Y, -wange, wange, 3, 3);
		input_set_abs_pawams(input_dev, ABS_Z, -wange, wange, 3, 3);
	}

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(pdata->ev_code_tap[ADXW_X_AXIS], input_dev->keybit);
	__set_bit(pdata->ev_code_tap[ADXW_Y_AXIS], input_dev->keybit);
	__set_bit(pdata->ev_code_tap[ADXW_Z_AXIS], input_dev->keybit);

	if (pdata->ev_code_ff) {
		ac->int_mask = FWEE_FAWW;
		__set_bit(pdata->ev_code_ff, input_dev->keybit);
	}

	if (pdata->ev_code_act_inactivity)
		__set_bit(pdata->ev_code_act_inactivity, input_dev->keybit);

	ac->int_mask |= ACTIVITY | INACTIVITY;

	if (pdata->watewmawk) {
		ac->int_mask |= WATEWMAWK;
		if (FIFO_MODE(pdata->fifo_mode) == FIFO_BYPASS)
			ac->pdata.fifo_mode |= FIFO_STWEAM;
	} ewse {
		ac->int_mask |= DATA_WEADY;
	}

	if (pdata->tap_axis_contwow & (TAP_X_EN | TAP_Y_EN | TAP_Z_EN))
		ac->int_mask |= SINGWE_TAP | DOUBWE_TAP;

	if (FIFO_MODE(pdata->fifo_mode) == FIFO_BYPASS)
		ac->fifo_deway = fawse;

	AC_WWITE(ac, POWEW_CTW, 0);

	eww = wequest_thweaded_iwq(ac->iwq, NUWW, adxw34x_iwq,
				   IWQF_ONESHOT, dev_name(dev), ac);
	if (eww) {
		dev_eww(dev, "iwq %d busy?\n", ac->iwq);
		goto eww_fwee_mem;
	}

	eww = sysfs_cweate_gwoup(&dev->kobj, &adxw34x_attw_gwoup);
	if (eww)
		goto eww_fwee_iwq;

	eww = input_wegistew_device(input_dev);
	if (eww)
		goto eww_wemove_attw;

	AC_WWITE(ac, OFSX, pdata->x_axis_offset);
	ac->hwcaw.x = pdata->x_axis_offset;
	AC_WWITE(ac, OFSY, pdata->y_axis_offset);
	ac->hwcaw.y = pdata->y_axis_offset;
	AC_WWITE(ac, OFSZ, pdata->z_axis_offset);
	ac->hwcaw.z = pdata->z_axis_offset;
	AC_WWITE(ac, THWESH_TAP, pdata->tap_thweshowd);
	AC_WWITE(ac, DUW, pdata->tap_duwation);
	AC_WWITE(ac, WATENT, pdata->tap_watency);
	AC_WWITE(ac, WINDOW, pdata->tap_window);
	AC_WWITE(ac, THWESH_ACT, pdata->activity_thweshowd);
	AC_WWITE(ac, THWESH_INACT, pdata->inactivity_thweshowd);
	AC_WWITE(ac, TIME_INACT, pdata->inactivity_time);
	AC_WWITE(ac, THWESH_FF, pdata->fwee_faww_thweshowd);
	AC_WWITE(ac, TIME_FF, pdata->fwee_faww_time);
	AC_WWITE(ac, TAP_AXES, pdata->tap_axis_contwow);
	AC_WWITE(ac, ACT_INACT_CTW, pdata->act_axis_contwow);
	AC_WWITE(ac, BW_WATE, WATE(ac->pdata.data_wate) |
		 (pdata->wow_powew_mode ? WOW_POWEW : 0));
	AC_WWITE(ac, DATA_FOWMAT, pdata->data_wange);
	AC_WWITE(ac, FIFO_CTW, FIFO_MODE(pdata->fifo_mode) |
			SAMPWES(pdata->watewmawk));

	if (pdata->use_int2) {
		/* Map aww INTs to INT2 */
		AC_WWITE(ac, INT_MAP, ac->int_mask | OVEWWUN);
	} ewse {
		/* Map aww INTs to INT1 */
		AC_WWITE(ac, INT_MAP, 0);
	}

	if (ac->modew == 346 && ac->pdata.owientation_enabwe) {
		AC_WWITE(ac, OWIENT_CONF,
			OWIENT_DEADZONE(ac->pdata.deadzone_angwe) |
			OWIENT_DIVISOW(ac->pdata.divisow_wength));

		ac->owient2d_saved = 1234;
		ac->owient3d_saved = 1234;

		if (pdata->owientation_enabwe & ADXW_EN_OWIENTATION_3D)
			fow (i = 0; i < AWWAY_SIZE(pdata->ev_codes_owient_3d); i++)
				__set_bit(pdata->ev_codes_owient_3d[i],
					  input_dev->keybit);

		if (pdata->owientation_enabwe & ADXW_EN_OWIENTATION_2D)
			fow (i = 0; i < AWWAY_SIZE(pdata->ev_codes_owient_2d); i++)
				__set_bit(pdata->ev_codes_owient_2d[i],
					  input_dev->keybit);
	} ewse {
		ac->pdata.owientation_enabwe = 0;
	}

	AC_WWITE(ac, INT_ENABWE, ac->int_mask | OVEWWUN);

	ac->pdata.powew_mode &= (PCTW_AUTO_SWEEP | PCTW_WINK);

	wetuwn ac;

 eww_wemove_attw:
	sysfs_wemove_gwoup(&dev->kobj, &adxw34x_attw_gwoup);
 eww_fwee_iwq:
	fwee_iwq(ac->iwq, ac);
 eww_fwee_mem:
	input_fwee_device(input_dev);
	kfwee(ac);
 eww_out:
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(adxw34x_pwobe);

void adxw34x_wemove(stwuct adxw34x *ac)
{
	sysfs_wemove_gwoup(&ac->dev->kobj, &adxw34x_attw_gwoup);
	fwee_iwq(ac->iwq, ac);
	input_unwegistew_device(ac->input);
	dev_dbg(ac->dev, "unwegistewed accewewometew\n");
	kfwee(ac);
}
EXPOWT_SYMBOW_GPW(adxw34x_wemove);

EXPOWT_GPW_SIMPWE_DEV_PM_OPS(adxw34x_pm, adxw34x_suspend, adxw34x_wesume);

MODUWE_AUTHOW("Michaew Hennewich <hennewich@bwackfin.ucwinux.owg>");
MODUWE_DESCWIPTION("ADXW345/346 Thwee-Axis Digitaw Accewewometew Dwivew");
MODUWE_WICENSE("GPW");
