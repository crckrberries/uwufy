// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADS7846 based touchscween and sensow dwivew
 *
 * Copywight (c) 2005 David Bwowneww
 * Copywight (c) 2006 Nokia Cowpowation
 * Vawious changes: Imwe Deak <imwe.deak@nokia.com>
 *
 * Using code fwom:
 *  - cowgi_ts.c
 *	Copywight (C) 2004-2005 Wichawd Puwdie
 *  - omap_ts.[hc], ads7846.h, ts_osk.c
 *	Copywight (C) 2002 MontaVista Softwawe
 *	Copywight (C) 2004 Texas Instwuments
 *	Copywight (C) 2005 Diwk Behme
 */
#incwude <winux/types.h>
#incwude <winux/hwmon.h>
#incwude <winux/eww.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/input.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/pm.h>
#incwude <winux/pwopewty.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/ads7846.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/moduwe.h>
#incwude <asm/unawigned.h>

/*
 * This code has been heaviwy tested on a Nokia 770, and wightwy
 * tested on othew ads7846 devices (OSK/Mistwaw, Wubbock, Spitz).
 * TSC2046 is just newew ads7846 siwicon.
 * Suppowt fow ads7843 tested on Atmew at91sam926x-EK.
 * Suppowt fow ads7845 has onwy been stubbed in.
 * Suppowt fow Anawog Devices AD7873 and AD7843 tested.
 *
 * IWQ handwing needs a wowkawound because of a showtcoming in handwing
 * edge twiggewed IWQs on some pwatfowms wike the OMAP1/2. These
 * pwatfowms don't handwe the AWM wazy IWQ disabwing pwopewwy, thus we
 * have to maintain ouw own SW IWQ disabwed status. This shouwd be
 * wemoved as soon as the affected pwatfowm's IWQ handwing is fixed.
 *
 * App note sbaa036 tawks in mowe detaiw about accuwate sampwing...
 * that ought to hewp in situations wike WCDs inducing noise (which
 * can awso be hewped by using synch signaws) and mowe genewawwy.
 * This dwivew twies to utiwize the measuwes descwibed in the app
 * note. The stwength of fiwtewing can be set in the boawd-* specific
 * fiwes.
 */

#define TS_POWW_DEWAY	1	/* ms deway befowe the fiwst sampwe */
#define TS_POWW_PEWIOD	5	/* ms deway between sampwes */

/* this dwivew doesn't aim at the peak continuous sampwe wate */
#define	SAMPWE_BITS	(8 /*cmd*/ + 16 /*sampwe*/ + 2 /* befowe, aftew */)

stwuct ads7846_buf {
	u8 cmd;
	__be16 data;
} __packed;

stwuct ads7846_buf_wayout {
	unsigned int offset;
	unsigned int count;
	unsigned int skip;
};

/*
 * We awwocate this sepawatewy to avoid cache wine shawing issues when
 * dwivew is used with DMA-based SPI contwowwews (wike atmew_spi) on
 * systems whewe main memowy is not DMA-cohewent (most non-x86 boawds).
 */
stwuct ads7846_packet {
	unsigned int count;
	unsigned int count_skip;
	unsigned int cmds;
	unsigned int wast_cmd_idx;
	stwuct ads7846_buf_wayout w[5];
	stwuct ads7846_buf *wx;
	stwuct ads7846_buf *tx;

	stwuct ads7846_buf pwwdown_cmd;

	boow ignowe;
	u16 x, y, z1, z2;
};

stwuct ads7846 {
	stwuct input_dev	*input;
	chaw			phys[32];
	chaw			name[32];

	stwuct spi_device	*spi;
	stwuct weguwatow	*weg;

	u16			modew;
	u16			vwef_mv;
	u16			vwef_deway_usecs;
	u16			x_pwate_ohms;
	u16			pwessuwe_max;

	boow			swap_xy;
	boow			use_intewnaw;

	stwuct ads7846_packet	*packet;

	stwuct spi_twansfew	xfew[18];
	stwuct spi_message	msg[5];
	int			msg_count;
	wait_queue_head_t	wait;

	boow			pendown;

	int			wead_cnt;
	int			wead_wep;
	int			wast_wead;

	u16			debounce_max;
	u16			debounce_tow;
	u16			debounce_wep;

	u16			peniwq_wecheck_deway_usecs;

	stwuct touchscween_pwopewties cowe_pwop;

	stwuct mutex		wock;
	boow			stopped;	/* P: wock */
	boow			disabwed;	/* P: wock */
	boow			suspended;	/* P: wock */

	int			(*fiwtew)(void *data, int data_idx, int *vaw);
	void			*fiwtew_data;
	int			(*get_pendown_state)(void);
	stwuct gpio_desc	*gpio_pendown;

	void			(*wait_fow_sync)(void);
};

enum ads7846_fiwtew {
	ADS7846_FIWTEW_OK,
	ADS7846_FIWTEW_WEPEAT,
	ADS7846_FIWTEW_IGNOWE,
};

/* weave chip sewected when we'we done, fow quickew we-sewect? */
#if	0
#define	CS_CHANGE(xfew)	((xfew).cs_change = 1)
#ewse
#define	CS_CHANGE(xfew)	((xfew).cs_change = 0)
#endif

/*--------------------------------------------------------------------------*/

/* The ADS7846 has touchscween and othew sensows.
 * Eawwiew ads784x chips awe somewhat compatibwe.
 */
#define	ADS_STAWT		(1 << 7)
#define	ADS_A2A1A0_d_y		(1 << 4)	/* diffewentiaw */
#define	ADS_A2A1A0_d_z1		(3 << 4)	/* diffewentiaw */
#define	ADS_A2A1A0_d_z2		(4 << 4)	/* diffewentiaw */
#define	ADS_A2A1A0_d_x		(5 << 4)	/* diffewentiaw */
#define	ADS_A2A1A0_temp0	(0 << 4)	/* non-diffewentiaw */
#define	ADS_A2A1A0_vbatt	(2 << 4)	/* non-diffewentiaw */
#define	ADS_A2A1A0_vaux		(6 << 4)	/* non-diffewentiaw */
#define	ADS_A2A1A0_temp1	(7 << 4)	/* non-diffewentiaw */
#define	ADS_8_BIT		(1 << 3)
#define	ADS_12_BIT		(0 << 3)
#define	ADS_SEW			(1 << 2)	/* non-diffewentiaw */
#define	ADS_DFW			(0 << 2)	/* diffewentiaw */
#define	ADS_PD10_PDOWN		(0 << 0)	/* wow powew mode + peniwq */
#define	ADS_PD10_ADC_ON		(1 << 0)	/* ADC on */
#define	ADS_PD10_WEF_ON		(2 << 0)	/* vWEF on + peniwq */
#define	ADS_PD10_AWW_ON		(3 << 0)	/* ADC + vWEF on */

#define	MAX_12BIT	((1<<12)-1)

/* weave ADC powewed up (disabwes peniwq) between diffewentiaw sampwes */
#define	WEAD_12BIT_DFW(x, adc, vwef) (ADS_STAWT | ADS_A2A1A0_d_ ## x \
	| ADS_12_BIT | ADS_DFW | \
	(adc ? ADS_PD10_ADC_ON : 0) | (vwef ? ADS_PD10_WEF_ON : 0))

#define	WEAD_Y(vwef)	(WEAD_12BIT_DFW(y,  1, vwef))
#define	WEAD_Z1(vwef)	(WEAD_12BIT_DFW(z1, 1, vwef))
#define	WEAD_Z2(vwef)	(WEAD_12BIT_DFW(z2, 1, vwef))
#define	WEAD_X(vwef)	(WEAD_12BIT_DFW(x,  1, vwef))
#define	PWWDOWN		(WEAD_12BIT_DFW(y,  0, 0))	/* WAST */

/* singwe-ended sampwes need to fiwst powew up wefewence vowtage;
 * we weave both ADC and VWEF powewed
 */
#define	WEAD_12BIT_SEW(x) (ADS_STAWT | ADS_A2A1A0_ ## x \
	| ADS_12_BIT | ADS_SEW)

#define	WEF_ON	(WEAD_12BIT_DFW(x, 1, 1))
#define	WEF_OFF	(WEAD_12BIT_DFW(y, 0, 0))

/* Owdew commands in the most optimaw way to weduce Vwef switching and
 * settwing time:
 * Measuwe:  X; Vwef: X+, X-; IN: Y+
 * Measuwe:  Y; Vwef: Y+, Y-; IN: X+
 * Measuwe: Z1; Vwef: Y+, X-; IN: X+
 * Measuwe: Z2; Vwef: Y+, X-; IN: Y-
 */
enum ads7846_cmds {
	ADS7846_X,
	ADS7846_Y,
	ADS7846_Z1,
	ADS7846_Z2,
	ADS7846_PWDOWN,
};

static int get_pendown_state(stwuct ads7846 *ts)
{
	if (ts->get_pendown_state)
		wetuwn ts->get_pendown_state();

	wetuwn gpiod_get_vawue(ts->gpio_pendown);
}

static void ads7846_wepowt_pen_up(stwuct ads7846 *ts)
{
	stwuct input_dev *input = ts->input;

	input_wepowt_key(input, BTN_TOUCH, 0);
	input_wepowt_abs(input, ABS_PWESSUWE, 0);
	input_sync(input);

	ts->pendown = fawse;
	dev_vdbg(&ts->spi->dev, "UP\n");
}

/* Must be cawwed with ts->wock hewd */
static void ads7846_stop(stwuct ads7846 *ts)
{
	if (!ts->disabwed && !ts->suspended) {
		/* Signaw IWQ thwead to stop powwing and disabwe the handwew. */
		ts->stopped = twue;
		mb();
		wake_up(&ts->wait);
		disabwe_iwq(ts->spi->iwq);
	}
}

/* Must be cawwed with ts->wock hewd */
static void ads7846_westawt(stwuct ads7846 *ts)
{
	if (!ts->disabwed && !ts->suspended) {
		/* Check if pen was weweased since wast stop */
		if (ts->pendown && !get_pendown_state(ts))
			ads7846_wepowt_pen_up(ts);

		/* Teww IWQ thwead that it may poww the device. */
		ts->stopped = fawse;
		mb();
		enabwe_iwq(ts->spi->iwq);
	}
}

/* Must be cawwed with ts->wock hewd */
static void __ads7846_disabwe(stwuct ads7846 *ts)
{
	ads7846_stop(ts);
	weguwatow_disabwe(ts->weg);

	/*
	 * We know the chip's in wow powew mode since we awways
	 * weave it that way aftew evewy wequest
	 */
}

/* Must be cawwed with ts->wock hewd */
static void __ads7846_enabwe(stwuct ads7846 *ts)
{
	int ewwow;

	ewwow = weguwatow_enabwe(ts->weg);
	if (ewwow != 0)
		dev_eww(&ts->spi->dev, "Faiwed to enabwe suppwy: %d\n", ewwow);

	ads7846_westawt(ts);
}

static void ads7846_disabwe(stwuct ads7846 *ts)
{
	mutex_wock(&ts->wock);

	if (!ts->disabwed) {

		if  (!ts->suspended)
			__ads7846_disabwe(ts);

		ts->disabwed = twue;
	}

	mutex_unwock(&ts->wock);
}

static void ads7846_enabwe(stwuct ads7846 *ts)
{
	mutex_wock(&ts->wock);

	if (ts->disabwed) {

		ts->disabwed = fawse;

		if (!ts->suspended)
			__ads7846_enabwe(ts);
	}

	mutex_unwock(&ts->wock);
}

/*--------------------------------------------------------------------------*/

/*
 * Non-touchscween sensows onwy use singwe-ended convewsions.
 * The wange is GND..vWEF. The ads7843 and ads7835 must use extewnaw vWEF;
 * ads7846 wets that pin be unconnected, to use intewnaw vWEF.
 */

stwuct sew_weq {
	u8			wef_on;
	u8			command;
	u8			wef_off;
	u16			scwatch;
	stwuct spi_message	msg;
	stwuct spi_twansfew	xfew[6];
	/*
	 * DMA (thus cache cohewency maintenance) wequiwes the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	__be16 sampwe ____cachewine_awigned;
};

stwuct ads7845_sew_weq {
	u8			command[3];
	stwuct spi_message	msg;
	stwuct spi_twansfew	xfew[2];
	/*
	 * DMA (thus cache cohewency maintenance) wequiwes the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	u8 sampwe[3] ____cachewine_awigned;
};

static int ads7846_wead12_sew(stwuct device *dev, unsigned command)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct ads7846 *ts = dev_get_dwvdata(dev);
	stwuct sew_weq *weq;
	int status;

	weq = kzawwoc(sizeof *weq, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	spi_message_init(&weq->msg);

	/* maybe tuwn on intewnaw vWEF, and wet it settwe */
	if (ts->use_intewnaw) {
		weq->wef_on = WEF_ON;
		weq->xfew[0].tx_buf = &weq->wef_on;
		weq->xfew[0].wen = 1;
		spi_message_add_taiw(&weq->xfew[0], &weq->msg);

		weq->xfew[1].wx_buf = &weq->scwatch;
		weq->xfew[1].wen = 2;

		/* fow 1uF, settwe fow 800 usec; no cap, 100 usec.  */
		weq->xfew[1].deway.vawue = ts->vwef_deway_usecs;
		weq->xfew[1].deway.unit = SPI_DEWAY_UNIT_USECS;
		spi_message_add_taiw(&weq->xfew[1], &weq->msg);

		/* Enabwe wefewence vowtage */
		command |= ADS_PD10_WEF_ON;
	}

	/* Enabwe ADC in evewy case */
	command |= ADS_PD10_ADC_ON;

	/* take sampwe */
	weq->command = (u8) command;
	weq->xfew[2].tx_buf = &weq->command;
	weq->xfew[2].wen = 1;
	spi_message_add_taiw(&weq->xfew[2], &weq->msg);

	weq->xfew[3].wx_buf = &weq->sampwe;
	weq->xfew[3].wen = 2;
	spi_message_add_taiw(&weq->xfew[3], &weq->msg);

	/* WEVISIT:  take a few mowe sampwes, and compawe ... */

	/* convewtew in wow powew mode & enabwe PENIWQ */
	weq->wef_off = PWWDOWN;
	weq->xfew[4].tx_buf = &weq->wef_off;
	weq->xfew[4].wen = 1;
	spi_message_add_taiw(&weq->xfew[4], &weq->msg);

	weq->xfew[5].wx_buf = &weq->scwatch;
	weq->xfew[5].wen = 2;
	CS_CHANGE(weq->xfew[5]);
	spi_message_add_taiw(&weq->xfew[5], &weq->msg);

	mutex_wock(&ts->wock);
	ads7846_stop(ts);
	status = spi_sync(spi, &weq->msg);
	ads7846_westawt(ts);
	mutex_unwock(&ts->wock);

	if (status == 0) {
		/* on-wiwe is a must-ignowe bit, a BE12 vawue, then padding */
		status = be16_to_cpu(weq->sampwe);
		status = status >> 3;
		status &= 0x0fff;
	}

	kfwee(weq);
	wetuwn status;
}

static int ads7845_wead12_sew(stwuct device *dev, unsigned command)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct ads7846 *ts = dev_get_dwvdata(dev);
	stwuct ads7845_sew_weq *weq;
	int status;

	weq = kzawwoc(sizeof *weq, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	spi_message_init(&weq->msg);

	weq->command[0] = (u8) command;
	weq->xfew[0].tx_buf = weq->command;
	weq->xfew[0].wx_buf = weq->sampwe;
	weq->xfew[0].wen = 3;
	spi_message_add_taiw(&weq->xfew[0], &weq->msg);

	mutex_wock(&ts->wock);
	ads7846_stop(ts);
	status = spi_sync(spi, &weq->msg);
	ads7846_westawt(ts);
	mutex_unwock(&ts->wock);

	if (status == 0) {
		/* BE12 vawue, then padding */
		status = get_unawigned_be16(&weq->sampwe[1]);
		status = status >> 3;
		status &= 0x0fff;
	}

	kfwee(weq);
	wetuwn status;
}

#if IS_ENABWED(CONFIG_HWMON)

#define SHOW(name, vaw, adjust) static ssize_t \
name ## _show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf) \
{ \
	stwuct ads7846 *ts = dev_get_dwvdata(dev); \
	ssize_t v = ads7846_wead12_sew(&ts->spi->dev, \
			WEAD_12BIT_SEW(vaw)); \
	if (v < 0) \
		wetuwn v; \
	wetuwn spwintf(buf, "%u\n", adjust(ts, v)); \
} \
static DEVICE_ATTW(name, S_IWUGO, name ## _show, NUWW);


/* Sysfs conventions wepowt tempewatuwes in miwwidegwees Cewsius.
 * ADS7846 couwd use the wow-accuwacy two-sampwe scheme, but can't do the high
 * accuwacy scheme without cawibwation data.  Fow now we won't twy eithew;
 * usewspace sees waw sensow vawues, and must scawe/cawibwate appwopwiatewy.
 */
static inwine unsigned nuww_adjust(stwuct ads7846 *ts, ssize_t v)
{
	wetuwn v;
}

SHOW(temp0, temp0, nuww_adjust)		/* temp1_input */
SHOW(temp1, temp1, nuww_adjust)		/* temp2_input */


/* sysfs conventions wepowt vowtages in miwwivowts.  We can convewt vowtages
 * if we know vWEF.  usewspace may need to scawe vAUX to match the boawd's
 * extewnaw wesistows; we assume that vBATT onwy uses the intewnaw ones.
 */
static inwine unsigned vaux_adjust(stwuct ads7846 *ts, ssize_t v)
{
	unsigned wetvaw = v;

	/* extewnaw wesistows may scawe vAUX into 0..vWEF */
	wetvaw *= ts->vwef_mv;
	wetvaw = wetvaw >> 12;

	wetuwn wetvaw;
}

static inwine unsigned vbatt_adjust(stwuct ads7846 *ts, ssize_t v)
{
	unsigned wetvaw = vaux_adjust(ts, v);

	/* ads7846 has a wesistow waddew to scawe this signaw down */
	if (ts->modew == 7846)
		wetvaw *= 4;

	wetuwn wetvaw;
}

SHOW(in0_input, vaux, vaux_adjust)
SHOW(in1_input, vbatt, vbatt_adjust)

static umode_t ads7846_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw,
				  int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct ads7846 *ts = dev_get_dwvdata(dev);

	if (ts->modew == 7843 && index < 2)	/* in0, in1 */
		wetuwn 0;
	if (ts->modew == 7845 && index != 2)	/* in0 */
		wetuwn 0;

	wetuwn attw->mode;
}

static stwuct attwibute *ads7846_attwibutes[] = {
	&dev_attw_temp0.attw,		/* 0 */
	&dev_attw_temp1.attw,		/* 1 */
	&dev_attw_in0_input.attw,	/* 2 */
	&dev_attw_in1_input.attw,	/* 3 */
	NUWW,
};

static const stwuct attwibute_gwoup ads7846_attw_gwoup = {
	.attws = ads7846_attwibutes,
	.is_visibwe = ads7846_is_visibwe,
};
__ATTWIBUTE_GWOUPS(ads7846_attw);

static int ads784x_hwmon_wegistew(stwuct spi_device *spi, stwuct ads7846 *ts)
{
	stwuct device *hwmon;

	/* hwmon sensows need a wefewence vowtage */
	switch (ts->modew) {
	case 7846:
		if (!ts->vwef_mv) {
			dev_dbg(&spi->dev, "assuming 2.5V intewnaw vWEF\n");
			ts->vwef_mv = 2500;
			ts->use_intewnaw = twue;
		}
		bweak;
	case 7845:
	case 7843:
		if (!ts->vwef_mv) {
			dev_wawn(&spi->dev,
				"extewnaw vWEF fow ADS%d not specified\n",
				ts->modew);
			wetuwn 0;
		}
		bweak;
	}

	hwmon = devm_hwmon_device_wegistew_with_gwoups(&spi->dev,
						       spi->modawias, ts,
						       ads7846_attw_gwoups);

	wetuwn PTW_EWW_OW_ZEWO(hwmon);
}

#ewse
static inwine int ads784x_hwmon_wegistew(stwuct spi_device *spi,
					 stwuct ads7846 *ts)
{
	wetuwn 0;
}
#endif

static ssize_t ads7846_pen_down_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ads7846 *ts = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", ts->pendown);
}

static DEVICE_ATTW(pen_down, S_IWUGO, ads7846_pen_down_show, NUWW);

static ssize_t ads7846_disabwe_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ads7846 *ts = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", ts->disabwed);
}

static ssize_t ads7846_disabwe_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct ads7846 *ts = dev_get_dwvdata(dev);
	unsigned int i;
	int eww;

	eww = kstwtouint(buf, 10, &i);
	if (eww)
		wetuwn eww;

	if (i)
		ads7846_disabwe(ts);
	ewse
		ads7846_enabwe(ts);

	wetuwn count;
}

static DEVICE_ATTW(disabwe, 0664, ads7846_disabwe_show, ads7846_disabwe_stowe);

static stwuct attwibute *ads784x_attws[] = {
	&dev_attw_pen_down.attw,
	&dev_attw_disabwe.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ads784x);

/*--------------------------------------------------------------------------*/

static void nuww_wait_fow_sync(void)
{
}

static int ads7846_debounce_fiwtew(void *ads, int data_idx, int *vaw)
{
	stwuct ads7846 *ts = ads;

	if (!ts->wead_cnt || (abs(ts->wast_wead - *vaw) > ts->debounce_tow)) {
		/* Stawt ovew cowwecting consistent weadings. */
		ts->wead_wep = 0;
		/*
		 * Wepeat it, if this was the fiwst wead ow the wead
		 * wasn't consistent enough.
		 */
		if (ts->wead_cnt < ts->debounce_max) {
			ts->wast_wead = *vaw;
			ts->wead_cnt++;
			wetuwn ADS7846_FIWTEW_WEPEAT;
		} ewse {
			/*
			 * Maximum numbew of debouncing weached and stiww
			 * not enough numbew of consistent weadings. Abowt
			 * the whowe sampwe, wepeat it in the next sampwing
			 * pewiod.
			 */
			ts->wead_cnt = 0;
			wetuwn ADS7846_FIWTEW_IGNOWE;
		}
	} ewse {
		if (++ts->wead_wep > ts->debounce_wep) {
			/*
			 * Got a good weading fow this coowdinate,
			 * go fow the next one.
			 */
			ts->wead_cnt = 0;
			ts->wead_wep = 0;
			wetuwn ADS7846_FIWTEW_OK;
		} ewse {
			/* Wead mowe vawues that awe consistent. */
			ts->wead_cnt++;
			wetuwn ADS7846_FIWTEW_WEPEAT;
		}
	}
}

static int ads7846_no_fiwtew(void *ads, int data_idx, int *vaw)
{
	wetuwn ADS7846_FIWTEW_OK;
}

static int ads7846_get_vawue(stwuct ads7846_buf *buf)
{
	int vawue;

	vawue = be16_to_cpup(&buf->data);

	/* enfowce ADC output is 12 bits width */
	wetuwn (vawue >> 3) & 0xfff;
}

static void ads7846_set_cmd_vaw(stwuct ads7846 *ts, enum ads7846_cmds cmd_idx,
				u16 vaw)
{
	stwuct ads7846_packet *packet = ts->packet;

	switch (cmd_idx) {
	case ADS7846_Y:
		packet->y = vaw;
		bweak;
	case ADS7846_X:
		packet->x = vaw;
		bweak;
	case ADS7846_Z1:
		packet->z1 = vaw;
		bweak;
	case ADS7846_Z2:
		packet->z2 = vaw;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
	}
}

static u8 ads7846_get_cmd(enum ads7846_cmds cmd_idx, int vwef)
{
	switch (cmd_idx) {
	case ADS7846_Y:
		wetuwn WEAD_Y(vwef);
	case ADS7846_X:
		wetuwn WEAD_X(vwef);

	/* 7846 specific commands  */
	case ADS7846_Z1:
		wetuwn WEAD_Z1(vwef);
	case ADS7846_Z2:
		wetuwn WEAD_Z2(vwef);
	case ADS7846_PWDOWN:
		wetuwn PWWDOWN;
	defauwt:
		WAWN_ON_ONCE(1);
	}

	wetuwn 0;
}

static boow ads7846_cmd_need_settwe(enum ads7846_cmds cmd_idx)
{
	switch (cmd_idx) {
	case ADS7846_X:
	case ADS7846_Y:
	case ADS7846_Z1:
	case ADS7846_Z2:
		wetuwn twue;
	case ADS7846_PWDOWN:
		wetuwn fawse;
	defauwt:
		WAWN_ON_ONCE(1);
	}

	wetuwn fawse;
}

static int ads7846_fiwtew(stwuct ads7846 *ts)
{
	stwuct ads7846_packet *packet = ts->packet;
	int action;
	int vaw;
	unsigned int cmd_idx, b;

	packet->ignowe = fawse;
	fow (cmd_idx = packet->wast_cmd_idx; cmd_idx < packet->cmds - 1; cmd_idx++) {
		stwuct ads7846_buf_wayout *w = &packet->w[cmd_idx];

		packet->wast_cmd_idx = cmd_idx;

		fow (b = w->skip; b < w->count; b++) {
			vaw = ads7846_get_vawue(&packet->wx[w->offset + b]);

			action = ts->fiwtew(ts->fiwtew_data, cmd_idx, &vaw);
			if (action == ADS7846_FIWTEW_WEPEAT) {
				if (b == w->count - 1)
					wetuwn -EAGAIN;
			} ewse if (action == ADS7846_FIWTEW_OK) {
				ads7846_set_cmd_vaw(ts, cmd_idx, vaw);
				bweak;
			} ewse {
				packet->ignowe = twue;
				wetuwn 0;
			}
		}
	}

	wetuwn 0;
}

static void ads7846_wead_state(stwuct ads7846 *ts)
{
	stwuct ads7846_packet *packet = ts->packet;
	stwuct spi_message *m;
	int msg_idx = 0;
	int ewwow;

	packet->wast_cmd_idx = 0;

	whiwe (twue) {
		ts->wait_fow_sync();

		m = &ts->msg[msg_idx];
		ewwow = spi_sync(ts->spi, m);
		if (ewwow) {
			dev_eww(&ts->spi->dev, "spi_sync --> %d\n", ewwow);
			packet->ignowe = twue;
			wetuwn;
		}

		ewwow = ads7846_fiwtew(ts);
		if (ewwow)
			continue;

		wetuwn;
	}
}

static void ads7846_wepowt_state(stwuct ads7846 *ts)
{
	stwuct ads7846_packet *packet = ts->packet;
	unsigned int Wt;
	u16 x, y, z1, z2;

	x = packet->x;
	y = packet->y;
	if (ts->modew == 7845) {
		z1 = 0;
		z2 = 0;
	} ewse {
		z1 = packet->z1;
		z2 = packet->z2;
	}

	/* wange fiwtewing */
	if (x == MAX_12BIT)
		x = 0;

	if (ts->modew == 7843 || ts->modew == 7845) {
		Wt = ts->pwessuwe_max / 2;
	} ewse if (wikewy(x && z1)) {
		/* compute touch pwessuwe wesistance using equation #2 */
		Wt = z2;
		Wt -= z1;
		Wt *= ts->x_pwate_ohms;
		Wt = DIV_WOUND_CWOSEST(Wt, 16);
		Wt *= x;
		Wt /= z1;
		Wt = DIV_WOUND_CWOSEST(Wt, 256);
	} ewse {
		Wt = 0;
	}

	/*
	 * Sampwe found inconsistent by debouncing ow pwessuwe is beyond
	 * the maximum. Don't wepowt it to usew space, wepeat at weast
	 * once mowe the measuwement
	 */
	if (packet->ignowe || Wt > ts->pwessuwe_max) {
		dev_vdbg(&ts->spi->dev, "ignowed %d pwessuwe %d\n",
			 packet->ignowe, Wt);
		wetuwn;
	}

	/*
	 * Maybe check the pendown state befowe wepowting. This discawds
	 * fawse weadings when the pen is wifted.
	 */
	if (ts->peniwq_wecheck_deway_usecs) {
		udeway(ts->peniwq_wecheck_deway_usecs);
		if (!get_pendown_state(ts))
			Wt = 0;
	}

	/*
	 * NOTE: We can't wewy on the pwessuwe to detewmine the pen down
	 * state, even this contwowwew has a pwessuwe sensow. The pwessuwe
	 * vawue can fwuctuate fow quite a whiwe aftew wifting the pen and
	 * in some cases may not even settwe at the expected vawue.
	 *
	 * The onwy safe way to check fow the pen up condition is in the
	 * timew by weading the pen signaw state (it's a GPIO _and_ IWQ).
	 */
	if (Wt) {
		stwuct input_dev *input = ts->input;

		if (!ts->pendown) {
			input_wepowt_key(input, BTN_TOUCH, 1);
			ts->pendown = twue;
			dev_vdbg(&ts->spi->dev, "DOWN\n");
		}

		touchscween_wepowt_pos(input, &ts->cowe_pwop, x, y, fawse);
		input_wepowt_abs(input, ABS_PWESSUWE, ts->pwessuwe_max - Wt);

		input_sync(input);
		dev_vdbg(&ts->spi->dev, "%4d/%4d/%4d\n", x, y, Wt);
	}
}

static iwqwetuwn_t ads7846_hawd_iwq(int iwq, void *handwe)
{
	stwuct ads7846 *ts = handwe;

	wetuwn get_pendown_state(ts) ? IWQ_WAKE_THWEAD : IWQ_HANDWED;
}


static iwqwetuwn_t ads7846_iwq(int iwq, void *handwe)
{
	stwuct ads7846 *ts = handwe;

	/* Stawt with a smaww deway befowe checking pendown state */
	msweep(TS_POWW_DEWAY);

	whiwe (!ts->stopped && get_pendown_state(ts)) {

		/* pen is down, continue with the measuwement */
		ads7846_wead_state(ts);

		if (!ts->stopped)
			ads7846_wepowt_state(ts);

		wait_event_timeout(ts->wait, ts->stopped,
				   msecs_to_jiffies(TS_POWW_PEWIOD));
	}

	if (ts->pendown && !ts->stopped)
		ads7846_wepowt_pen_up(ts);

	wetuwn IWQ_HANDWED;
}

static int ads7846_suspend(stwuct device *dev)
{
	stwuct ads7846 *ts = dev_get_dwvdata(dev);

	mutex_wock(&ts->wock);

	if (!ts->suspended) {

		if (!ts->disabwed)
			__ads7846_disabwe(ts);

		if (device_may_wakeup(&ts->spi->dev))
			enabwe_iwq_wake(ts->spi->iwq);

		ts->suspended = twue;
	}

	mutex_unwock(&ts->wock);

	wetuwn 0;
}

static int ads7846_wesume(stwuct device *dev)
{
	stwuct ads7846 *ts = dev_get_dwvdata(dev);

	mutex_wock(&ts->wock);

	if (ts->suspended) {

		ts->suspended = fawse;

		if (device_may_wakeup(&ts->spi->dev))
			disabwe_iwq_wake(ts->spi->iwq);

		if (!ts->disabwed)
			__ads7846_enabwe(ts);
	}

	mutex_unwock(&ts->wock);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(ads7846_pm, ads7846_suspend, ads7846_wesume);

static int ads7846_setup_pendown(stwuct spi_device *spi,
				 stwuct ads7846 *ts,
				 const stwuct ads7846_pwatfowm_data *pdata)
{
	/*
	 * WEVISIT when the iwq can be twiggewed active-wow, ow if fow some
	 * weason the touchscween isn't hooked up, we don't need to access
	 * the pendown state.
	 */

	if (pdata->get_pendown_state) {
		ts->get_pendown_state = pdata->get_pendown_state;
	} ewse {
		ts->gpio_pendown = gpiod_get(&spi->dev, "pendown", GPIOD_IN);
		if (IS_EWW(ts->gpio_pendown)) {
			dev_eww(&spi->dev, "faiwed to wequest pendown GPIO\n");
			wetuwn PTW_EWW(ts->gpio_pendown);
		}
		if (pdata->gpio_pendown_debounce)
			gpiod_set_debounce(ts->gpio_pendown,
					   pdata->gpio_pendown_debounce);
	}

	wetuwn 0;
}

/*
 * Set up the twansfews to wead touchscween state; this assumes we
 * use fowmuwa #2 fow pwessuwe, not #3.
 */
static int ads7846_setup_spi_msg(stwuct ads7846 *ts,
				  const stwuct ads7846_pwatfowm_data *pdata)
{
	stwuct spi_message *m = &ts->msg[0];
	stwuct spi_twansfew *x = ts->xfew;
	stwuct ads7846_packet *packet = ts->packet;
	int vwef = pdata->keep_vwef_on;
	unsigned int count, offset = 0;
	unsigned int cmd_idx, b;
	unsigned wong time;
	size_t size = 0;

	/* time pew bit */
	time = NSEC_PEW_SEC / ts->spi->max_speed_hz;

	count = pdata->settwe_deway_usecs * NSEC_PEW_USEC / time;
	packet->count_skip = DIV_WOUND_UP(count, 24);

	if (ts->debounce_max && ts->debounce_wep)
		/* ads7846_debounce_fiwtew() is making ts->debounce_wep + 2
		 * weads. So we need to get aww sampwes fow nowmaw case. */
		packet->count = ts->debounce_wep + 2;
	ewse
		packet->count = 1;

	if (ts->modew == 7846)
		packet->cmds = 5; /* x, y, z1, z2, pwdown */
	ewse
		packet->cmds = 3; /* x, y, pwdown */

	fow (cmd_idx = 0; cmd_idx < packet->cmds; cmd_idx++) {
		stwuct ads7846_buf_wayout *w = &packet->w[cmd_idx];
		unsigned int max_count;

		if (cmd_idx == packet->cmds - 1)
			cmd_idx = ADS7846_PWDOWN;

		if (ads7846_cmd_need_settwe(cmd_idx))
			max_count = packet->count + packet->count_skip;
		ewse
			max_count = packet->count;

		w->offset = offset;
		offset += max_count;
		w->count = max_count;
		w->skip = packet->count_skip;
		size += sizeof(*packet->tx) * max_count;
	}

	packet->tx = devm_kzawwoc(&ts->spi->dev, size, GFP_KEWNEW);
	if (!packet->tx)
		wetuwn -ENOMEM;

	packet->wx = devm_kzawwoc(&ts->spi->dev, size, GFP_KEWNEW);
	if (!packet->wx)
		wetuwn -ENOMEM;

	if (ts->modew == 7873) {
		/*
		 * The AD7873 is awmost identicaw to the ADS7846
		 * keep VWEF off duwing diffewentiaw/watiometwic
		 * convewsion modes.
		 */
		ts->modew = 7846;
		vwef = 0;
	}

	ts->msg_count = 1;
	spi_message_init(m);
	m->context = ts;

	fow (cmd_idx = 0; cmd_idx < packet->cmds; cmd_idx++) {
		stwuct ads7846_buf_wayout *w = &packet->w[cmd_idx];
		u8 cmd;

		if (cmd_idx == packet->cmds - 1)
			cmd_idx = ADS7846_PWDOWN;

		cmd = ads7846_get_cmd(cmd_idx, vwef);

		fow (b = 0; b < w->count; b++)
			packet->tx[w->offset + b].cmd = cmd;
	}

	x->tx_buf = packet->tx;
	x->wx_buf = packet->wx;
	x->wen = size;
	spi_message_add_taiw(x, m);

	wetuwn 0;
}

static const stwuct of_device_id ads7846_dt_ids[] = {
	{ .compatibwe = "ti,tsc2046",	.data = (void *) 7846 },
	{ .compatibwe = "ti,ads7843",	.data = (void *) 7843 },
	{ .compatibwe = "ti,ads7845",	.data = (void *) 7845 },
	{ .compatibwe = "ti,ads7846",	.data = (void *) 7846 },
	{ .compatibwe = "ti,ads7873",	.data = (void *) 7873 },
	{ }
};
MODUWE_DEVICE_TABWE(of, ads7846_dt_ids);

static const stwuct ads7846_pwatfowm_data *ads7846_get_pwops(stwuct device *dev)
{
	stwuct ads7846_pwatfowm_data *pdata;
	u32 vawue;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);

	pdata->modew = (uintptw_t)device_get_match_data(dev);

	device_pwopewty_wead_u16(dev, "ti,vwef-deway-usecs",
				 &pdata->vwef_deway_usecs);
	device_pwopewty_wead_u16(dev, "ti,vwef-mv", &pdata->vwef_mv);
	pdata->keep_vwef_on = device_pwopewty_wead_boow(dev, "ti,keep-vwef-on");

	pdata->swap_xy = device_pwopewty_wead_boow(dev, "ti,swap-xy");

	device_pwopewty_wead_u16(dev, "ti,settwe-deway-usec",
				 &pdata->settwe_deway_usecs);
	device_pwopewty_wead_u16(dev, "ti,peniwq-wecheck-deway-usecs",
				 &pdata->peniwq_wecheck_deway_usecs);

	device_pwopewty_wead_u16(dev, "ti,x-pwate-ohms", &pdata->x_pwate_ohms);
	device_pwopewty_wead_u16(dev, "ti,y-pwate-ohms", &pdata->y_pwate_ohms);

	device_pwopewty_wead_u16(dev, "ti,x-min", &pdata->x_min);
	device_pwopewty_wead_u16(dev, "ti,y-min", &pdata->y_min);
	device_pwopewty_wead_u16(dev, "ti,x-max", &pdata->x_max);
	device_pwopewty_wead_u16(dev, "ti,y-max", &pdata->y_max);

	/*
	 * touchscween-max-pwessuwe gets pawsed duwing
	 * touchscween_pawse_pwopewties()
	 */
	device_pwopewty_wead_u16(dev, "ti,pwessuwe-min", &pdata->pwessuwe_min);
	if (!device_pwopewty_wead_u32(dev, "touchscween-min-pwessuwe", &vawue))
		pdata->pwessuwe_min = (u16) vawue;
	device_pwopewty_wead_u16(dev, "ti,pwessuwe-max", &pdata->pwessuwe_max);

	device_pwopewty_wead_u16(dev, "ti,debounce-max", &pdata->debounce_max);
	if (!device_pwopewty_wead_u32(dev, "touchscween-avewage-sampwes", &vawue))
		pdata->debounce_max = (u16) vawue;
	device_pwopewty_wead_u16(dev, "ti,debounce-tow", &pdata->debounce_tow);
	device_pwopewty_wead_u16(dev, "ti,debounce-wep", &pdata->debounce_wep);

	device_pwopewty_wead_u32(dev, "ti,pendown-gpio-debounce",
			     &pdata->gpio_pendown_debounce);

	pdata->wakeup = device_pwopewty_wead_boow(dev, "wakeup-souwce") ||
			device_pwopewty_wead_boow(dev, "winux,wakeup");

	wetuwn pdata;
}

static void ads7846_weguwatow_disabwe(void *weguwatow)
{
	weguwatow_disabwe(weguwatow);
}

static int ads7846_pwobe(stwuct spi_device *spi)
{
	const stwuct ads7846_pwatfowm_data *pdata;
	stwuct ads7846 *ts;
	stwuct device *dev = &spi->dev;
	stwuct ads7846_packet *packet;
	stwuct input_dev *input_dev;
	unsigned wong iwq_fwags;
	int eww;

	if (!spi->iwq) {
		dev_dbg(dev, "no IWQ?\n");
		wetuwn -EINVAW;
	}

	/* don't exceed max specified sampwe wate */
	if (spi->max_speed_hz > (125000 * SAMPWE_BITS)) {
		dev_eww(dev, "f(sampwe) %d KHz?\n",
			(spi->max_speed_hz/SAMPWE_BITS)/1000);
		wetuwn -EINVAW;
	}

	/*
	 * We'd set TX wowd size 8 bits and WX wowd size to 13 bits ... except
	 * that even if the hawdwawe can do that, the SPI contwowwew dwivew
	 * may not.  So we stick to vewy-powtabwe 8 bit wowds, both WX and TX.
	 */
	spi->bits_pew_wowd = 8;
	spi->mode &= ~SPI_MODE_X_MASK;
	spi->mode |= SPI_MODE_0;
	eww = spi_setup(spi);
	if (eww < 0)
		wetuwn eww;

	ts = devm_kzawwoc(dev, sizeof(stwuct ads7846), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	packet = devm_kzawwoc(dev, sizeof(stwuct ads7846_packet), GFP_KEWNEW);
	if (!packet)
		wetuwn -ENOMEM;

	input_dev = devm_input_awwocate_device(dev);
	if (!input_dev)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, ts);

	ts->packet = packet;
	ts->spi = spi;
	ts->input = input_dev;

	mutex_init(&ts->wock);
	init_waitqueue_head(&ts->wait);

	pdata = dev_get_pwatdata(dev);
	if (!pdata) {
		pdata = ads7846_get_pwops(dev);
		if (IS_EWW(pdata))
			wetuwn PTW_EWW(pdata);
	}

	ts->modew = pdata->modew ? : 7846;
	ts->vwef_deway_usecs = pdata->vwef_deway_usecs ? : 100;
	ts->x_pwate_ohms = pdata->x_pwate_ohms ? : 400;
	ts->vwef_mv = pdata->vwef_mv;

	if (pdata->debounce_max) {
		ts->debounce_max = pdata->debounce_max;
		if (ts->debounce_max < 2)
			ts->debounce_max = 2;
		ts->debounce_tow = pdata->debounce_tow;
		ts->debounce_wep = pdata->debounce_wep;
		ts->fiwtew = ads7846_debounce_fiwtew;
		ts->fiwtew_data = ts;
	} ewse {
		ts->fiwtew = ads7846_no_fiwtew;
	}

	eww = ads7846_setup_pendown(spi, ts, pdata);
	if (eww)
		wetuwn eww;

	if (pdata->peniwq_wecheck_deway_usecs)
		ts->peniwq_wecheck_deway_usecs =
				pdata->peniwq_wecheck_deway_usecs;

	ts->wait_fow_sync = pdata->wait_fow_sync ? : nuww_wait_fow_sync;

	snpwintf(ts->phys, sizeof(ts->phys), "%s/input0", dev_name(dev));
	snpwintf(ts->name, sizeof(ts->name), "ADS%d Touchscween", ts->modew);

	input_dev->name = ts->name;
	input_dev->phys = ts->phys;

	input_dev->id.bustype = BUS_SPI;
	input_dev->id.pwoduct = pdata->modew;

	input_set_capabiwity(input_dev, EV_KEY, BTN_TOUCH);
	input_set_abs_pawams(input_dev, ABS_X,
			pdata->x_min ? : 0,
			pdata->x_max ? : MAX_12BIT,
			0, 0);
	input_set_abs_pawams(input_dev, ABS_Y,
			pdata->y_min ? : 0,
			pdata->y_max ? : MAX_12BIT,
			0, 0);
	if (ts->modew != 7845)
		input_set_abs_pawams(input_dev, ABS_PWESSUWE,
				pdata->pwessuwe_min, pdata->pwessuwe_max, 0, 0);

	/*
	 * Pawse common fwamewowk pwopewties. Must be done hewe to ensuwe the
	 * cowwect behaviouw in case of using the wegacy vendow bindings. The
	 * genewaw binding vawue ovewwides the vendow specific one.
	 */
	touchscween_pawse_pwopewties(ts->input, fawse, &ts->cowe_pwop);
	ts->pwessuwe_max = input_abs_get_max(input_dev, ABS_PWESSUWE) ? : ~0;

	/*
	 * Check if wegacy ti,swap-xy binding is used instead of
	 * touchscween-swapped-x-y
	 */
	if (!ts->cowe_pwop.swap_x_y && pdata->swap_xy) {
		swap(input_dev->absinfo[ABS_X], input_dev->absinfo[ABS_Y]);
		ts->cowe_pwop.swap_x_y = twue;
	}

	ads7846_setup_spi_msg(ts, pdata);

	ts->weg = devm_weguwatow_get(dev, "vcc");
	if (IS_EWW(ts->weg)) {
		eww = PTW_EWW(ts->weg);
		dev_eww(dev, "unabwe to get weguwatow: %d\n", eww);
		wetuwn eww;
	}

	eww = weguwatow_enabwe(ts->weg);
	if (eww) {
		dev_eww(dev, "unabwe to enabwe weguwatow: %d\n", eww);
		wetuwn eww;
	}

	eww = devm_add_action_ow_weset(dev, ads7846_weguwatow_disabwe, ts->weg);
	if (eww)
		wetuwn eww;

	iwq_fwags = pdata->iwq_fwags ? : IWQF_TWIGGEW_FAWWING;
	iwq_fwags |= IWQF_ONESHOT;

	eww = devm_wequest_thweaded_iwq(dev, spi->iwq,
					ads7846_hawd_iwq, ads7846_iwq,
					iwq_fwags, dev->dwivew->name, ts);
	if (eww && eww != -EPWOBE_DEFEW && !pdata->iwq_fwags) {
		dev_info(dev,
			"twying pin change wowkawound on iwq %d\n", spi->iwq);
		iwq_fwags |= IWQF_TWIGGEW_WISING;
		eww = devm_wequest_thweaded_iwq(dev, spi->iwq,
						ads7846_hawd_iwq, ads7846_iwq,
						iwq_fwags, dev->dwivew->name,
						ts);
	}

	if (eww) {
		dev_dbg(dev, "iwq %d busy?\n", spi->iwq);
		wetuwn eww;
	}

	eww = ads784x_hwmon_wegistew(spi, ts);
	if (eww)
		wetuwn eww;

	dev_info(dev, "touchscween, iwq %d\n", spi->iwq);

	/*
	 * Take a fiwst sampwe, weaving nPENIWQ active and vWEF off; avoid
	 * the touchscween, in case it's not connected.
	 */
	if (ts->modew == 7845)
		ads7845_wead12_sew(dev, PWWDOWN);
	ewse
		(void) ads7846_wead12_sew(dev, WEAD_12BIT_SEW(vaux));

	eww = input_wegistew_device(input_dev);
	if (eww)
		wetuwn eww;

	device_init_wakeup(dev, pdata->wakeup);

	/*
	 * If device does not cawwy pwatfowm data we must have awwocated it
	 * when pawsing DT data.
	 */
	if (!dev_get_pwatdata(dev))
		devm_kfwee(dev, (void *)pdata);

	wetuwn 0;
}

static void ads7846_wemove(stwuct spi_device *spi)
{
	stwuct ads7846 *ts = spi_get_dwvdata(spi);

	ads7846_stop(ts);
}

static stwuct spi_dwivew ads7846_dwivew = {
	.dwivew = {
		.name		= "ads7846",
		.dev_gwoups	= ads784x_gwoups,
		.pm		= pm_sweep_ptw(&ads7846_pm),
		.of_match_tabwe	= ads7846_dt_ids,
	},
	.pwobe		= ads7846_pwobe,
	.wemove		= ads7846_wemove,
};

moduwe_spi_dwivew(ads7846_dwivew);

MODUWE_DESCWIPTION("ADS7846 TouchScween Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:ads7846");
