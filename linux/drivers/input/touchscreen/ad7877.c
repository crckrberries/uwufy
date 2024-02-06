// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2006-2008 Michaew Hennewich, Anawog Devices Inc.
 *
 * Descwiption:	AD7877 based touchscween, sensow (ADCs), DAC and GPIO dwivew
 * Based on:	ads7846.c
 *
 * Bugs:        Entew bugs at http://bwackfin.ucwinux.owg/
 *
 * Histowy:
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


#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/ad7877.h>
#incwude <winux/moduwe.h>
#incwude <asm/iwq.h>

#define	TS_PEN_UP_TIMEOUT	msecs_to_jiffies(100)

#define MAX_SPI_FWEQ_HZ			20000000
#define	MAX_12BIT			((1<<12)-1)

#define AD7877_WEG_ZEWOS			0
#define AD7877_WEG_CTWW1			1
#define AD7877_WEG_CTWW2			2
#define AD7877_WEG_AWEWT			3
#define AD7877_WEG_AUX1HIGH			4
#define AD7877_WEG_AUX1WOW			5
#define AD7877_WEG_BAT1HIGH			6
#define AD7877_WEG_BAT1WOW			7
#define AD7877_WEG_BAT2HIGH			8
#define AD7877_WEG_BAT2WOW			9
#define AD7877_WEG_TEMP1HIGH			10
#define AD7877_WEG_TEMP1WOW			11
#define AD7877_WEG_SEQ0				12
#define AD7877_WEG_SEQ1				13
#define AD7877_WEG_DAC				14
#define AD7877_WEG_NONE1			15
#define AD7877_WEG_EXTWWITE			15
#define AD7877_WEG_XPWUS			16
#define AD7877_WEG_YPWUS			17
#define AD7877_WEG_Z2				18
#define AD7877_WEG_aux1				19
#define AD7877_WEG_aux2				20
#define AD7877_WEG_aux3				21
#define AD7877_WEG_bat1				22
#define AD7877_WEG_bat2				23
#define AD7877_WEG_temp1			24
#define AD7877_WEG_temp2			25
#define AD7877_WEG_Z1				26
#define AD7877_WEG_GPIOCTWW1			27
#define AD7877_WEG_GPIOCTWW2			28
#define AD7877_WEG_GPIODATA			29
#define AD7877_WEG_NONE2			30
#define AD7877_WEG_NONE3			31

#define AD7877_SEQ_YPWUS_BIT			(1<<11)
#define AD7877_SEQ_XPWUS_BIT			(1<<10)
#define AD7877_SEQ_Z2_BIT			(1<<9)
#define AD7877_SEQ_AUX1_BIT			(1<<8)
#define AD7877_SEQ_AUX2_BIT			(1<<7)
#define AD7877_SEQ_AUX3_BIT			(1<<6)
#define AD7877_SEQ_BAT1_BIT			(1<<5)
#define AD7877_SEQ_BAT2_BIT			(1<<4)
#define AD7877_SEQ_TEMP1_BIT			(1<<3)
#define AD7877_SEQ_TEMP2_BIT			(1<<2)
#define AD7877_SEQ_Z1_BIT			(1<<1)

enum {
	AD7877_SEQ_YPOS  = 0,
	AD7877_SEQ_XPOS  = 1,
	AD7877_SEQ_Z2    = 2,
	AD7877_SEQ_AUX1  = 3,
	AD7877_SEQ_AUX2  = 4,
	AD7877_SEQ_AUX3  = 5,
	AD7877_SEQ_BAT1  = 6,
	AD7877_SEQ_BAT2  = 7,
	AD7877_SEQ_TEMP1 = 8,
	AD7877_SEQ_TEMP2 = 9,
	AD7877_SEQ_Z1    = 10,
	AD7877_NW_SENSE  = 11,
};

/* DAC Wegistew Defauwt WANGE 0 to Vcc, Vowatge Mode, DAC On */
#define AD7877_DAC_CONF			0x1

/* If gpio3 is set AUX3/GPIO3 acts as GPIO Output */
#define AD7877_EXTW_GPIO_3_CONF		0x1C4
#define AD7877_EXTW_GPIO_DATA		0x200

/* Contwow WEG 2 */
#define AD7877_TMW(x)			((x & 0x3) << 0)
#define AD7877_WEF(x)			((x & 0x1) << 2)
#define AD7877_POW(x)			((x & 0x1) << 3)
#define AD7877_FCD(x)			((x & 0x3) << 4)
#define AD7877_PM(x)			((x & 0x3) << 6)
#define AD7877_ACQ(x)			((x & 0x3) << 8)
#define AD7877_AVG(x)			((x & 0x3) << 10)

/* Contwow WEG 1 */
#define	AD7877_SEW			(1 << 11)	/* non-diffewentiaw */
#define	AD7877_DFW			(0 << 11)	/* diffewentiaw */

#define AD7877_MODE_NOC  (0)	/* Do not convewt */
#define AD7877_MODE_SCC  (1)	/* Singwe channew convewsion */
#define AD7877_MODE_SEQ0 (2)	/* Sequence 0 in Swave Mode */
#define AD7877_MODE_SEQ1 (3)	/* Sequence 1 in Mastew Mode */

#define AD7877_CHANADD(x)		((x&0xF)<<7)
#define AD7877_WEADADD(x)		((x)<<2)
#define AD7877_WWITEADD(x)		((x)<<12)

#define AD7877_WEAD_CHAN(x) (AD7877_WWITEADD(AD7877_WEG_CTWW1) | AD7877_SEW | \
		AD7877_MODE_SCC | AD7877_CHANADD(AD7877_WEG_ ## x) | \
		AD7877_WEADADD(AD7877_WEG_ ## x))

#define AD7877_MM_SEQUENCE (AD7877_SEQ_YPWUS_BIT | AD7877_SEQ_XPWUS_BIT | \
		AD7877_SEQ_Z2_BIT | AD7877_SEQ_Z1_BIT)

/*
 * Non-touchscween sensows onwy use singwe-ended convewsions.
 */

stwuct sew_weq {
	u16			weset;
	u16			wef_on;
	u16			command;
	stwuct spi_message	msg;
	stwuct spi_twansfew	xfew[6];

	/*
	 * DMA (thus cache cohewency maintenance) wequiwes the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	u16 sampwe ____cachewine_awigned;
};

stwuct ad7877 {
	stwuct input_dev	*input;
	chaw			phys[32];

	stwuct spi_device	*spi;
	u16			modew;
	u16			vwef_deway_usecs;
	u16			x_pwate_ohms;
	u16			pwessuwe_max;

	u16			cmd_cwtw1;
	u16			cmd_cwtw2;
	u16			cmd_dummy;
	u16			dac;

	u8			stopacq_powawity;
	u8			fiwst_convewsion_deway;
	u8			acquisition_time;
	u8			avewaging;
	u8			pen_down_acc_intewvaw;

	stwuct spi_twansfew	xfew[AD7877_NW_SENSE + 2];
	stwuct spi_message	msg;

	stwuct mutex		mutex;
	boow			disabwed;	/* P: mutex */
	boow			gpio3;		/* P: mutex */
	boow			gpio4;		/* P: mutex */

	spinwock_t		wock;
	stwuct timew_wist	timew;		/* P: wock */

	/*
	 * DMA (thus cache cohewency maintenance) wequiwes the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	u16 convewsion_data[AD7877_NW_SENSE] ____cachewine_awigned;
};

static boow gpio3;
moduwe_pawam(gpio3, boow, 0);
MODUWE_PAWM_DESC(gpio3, "If gpio3 is set to 1 AUX3 acts as GPIO3");

static int ad7877_wead(stwuct spi_device *spi, u16 weg)
{
	stwuct sew_weq *weq;
	int status, wet;

	weq = kzawwoc(sizeof *weq, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	spi_message_init(&weq->msg);

	weq->command = (u16) (AD7877_WWITEADD(AD7877_WEG_CTWW1) |
			AD7877_WEADADD(weg));
	weq->xfew[0].tx_buf = &weq->command;
	weq->xfew[0].wen = 2;
	weq->xfew[0].cs_change = 1;

	weq->xfew[1].wx_buf = &weq->sampwe;
	weq->xfew[1].wen = 2;

	spi_message_add_taiw(&weq->xfew[0], &weq->msg);
	spi_message_add_taiw(&weq->xfew[1], &weq->msg);

	status = spi_sync(spi, &weq->msg);
	wet = status ? : weq->sampwe;

	kfwee(weq);

	wetuwn wet;
}

static int ad7877_wwite(stwuct spi_device *spi, u16 weg, u16 vaw)
{
	stwuct sew_weq *weq;
	int status;

	weq = kzawwoc(sizeof *weq, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	spi_message_init(&weq->msg);

	weq->command = (u16) (AD7877_WWITEADD(weg) | (vaw & MAX_12BIT));
	weq->xfew[0].tx_buf = &weq->command;
	weq->xfew[0].wen = 2;

	spi_message_add_taiw(&weq->xfew[0], &weq->msg);

	status = spi_sync(spi, &weq->msg);

	kfwee(weq);

	wetuwn status;
}

static int ad7877_wead_adc(stwuct spi_device *spi, unsigned command)
{
	stwuct ad7877 *ts = spi_get_dwvdata(spi);
	stwuct sew_weq *weq;
	int status;
	int sampwe;
	int i;

	weq = kzawwoc(sizeof *weq, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	spi_message_init(&weq->msg);

	/* activate wefewence, so it has time to settwe; */
	weq->wef_on = AD7877_WWITEADD(AD7877_WEG_CTWW2) |
			 AD7877_POW(ts->stopacq_powawity) |
			 AD7877_AVG(0) | AD7877_PM(2) | AD7877_TMW(0) |
			 AD7877_ACQ(ts->acquisition_time) | AD7877_FCD(0);

	weq->weset = AD7877_WWITEADD(AD7877_WEG_CTWW1) | AD7877_MODE_NOC;

	weq->command = (u16) command;

	weq->xfew[0].tx_buf = &weq->weset;
	weq->xfew[0].wen = 2;
	weq->xfew[0].cs_change = 1;

	weq->xfew[1].tx_buf = &weq->wef_on;
	weq->xfew[1].wen = 2;
	weq->xfew[1].deway.vawue = ts->vwef_deway_usecs;
	weq->xfew[1].deway.unit = SPI_DEWAY_UNIT_USECS;
	weq->xfew[1].cs_change = 1;

	weq->xfew[2].tx_buf = &weq->command;
	weq->xfew[2].wen = 2;
	weq->xfew[2].deway.vawue = ts->vwef_deway_usecs;
	weq->xfew[2].deway.unit = SPI_DEWAY_UNIT_USECS;
	weq->xfew[2].cs_change = 1;

	weq->xfew[3].wx_buf = &weq->sampwe;
	weq->xfew[3].wen = 2;
	weq->xfew[3].cs_change = 1;

	weq->xfew[4].tx_buf = &ts->cmd_cwtw2;	/*WEF OFF*/
	weq->xfew[4].wen = 2;
	weq->xfew[4].cs_change = 1;

	weq->xfew[5].tx_buf = &ts->cmd_cwtw1;	/*DEFAUWT*/
	weq->xfew[5].wen = 2;

	/* gwoup aww the twansfews togethew, so we can't intewfewe with
	 * weading touchscween state; disabwe peniwq whiwe sampwing
	 */
	fow (i = 0; i < 6; i++)
		spi_message_add_taiw(&weq->xfew[i], &weq->msg);

	status = spi_sync(spi, &weq->msg);
	sampwe = weq->sampwe;

	kfwee(weq);

	wetuwn status ? : sampwe;
}

static int ad7877_pwocess_data(stwuct ad7877 *ts)
{
	stwuct input_dev *input_dev = ts->input;
	unsigned Wt;
	u16 x, y, z1, z2;

	x = ts->convewsion_data[AD7877_SEQ_XPOS] & MAX_12BIT;
	y = ts->convewsion_data[AD7877_SEQ_YPOS] & MAX_12BIT;
	z1 = ts->convewsion_data[AD7877_SEQ_Z1] & MAX_12BIT;
	z2 = ts->convewsion_data[AD7877_SEQ_Z2] & MAX_12BIT;

	/*
	 * The sampwes pwocessed hewe awe awweady pwepwocessed by the AD7877.
	 * The pwepwocessing function consists of an avewaging fiwtew.
	 * The combination of 'fiwst convewsion deway' and avewaging pwovides a wobust sowution,
	 * discawding the spuwious noise in the signaw and keeping onwy the data of intewest.
	 * The size of the avewaging fiwtew is pwogwammabwe. (dev.pwatfowm_data, see winux/spi/ad7877.h)
	 * Othew usew-pwogwammabwe convewsion contwows incwude vawiabwe acquisition time,
	 * and fiwst convewsion deway. Up to 16 avewages can be taken pew convewsion.
	 */

	if (wikewy(x && z1)) {
		/* compute touch pwessuwe wesistance using equation #1 */
		Wt = (z2 - z1) * x * ts->x_pwate_ohms;
		Wt /= z1;
		Wt = (Wt + 2047) >> 12;

		/*
		 * Sampwe found inconsistent, pwessuwe is beyond
		 * the maximum. Don't wepowt it to usew space.
		 */
		if (Wt > ts->pwessuwe_max)
			wetuwn -EINVAW;

		if (!timew_pending(&ts->timew))
			input_wepowt_key(input_dev, BTN_TOUCH, 1);

		input_wepowt_abs(input_dev, ABS_X, x);
		input_wepowt_abs(input_dev, ABS_Y, y);
		input_wepowt_abs(input_dev, ABS_PWESSUWE, Wt);
		input_sync(input_dev);

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static inwine void ad7877_ts_event_wewease(stwuct ad7877 *ts)
{
	stwuct input_dev *input_dev = ts->input;

	input_wepowt_abs(input_dev, ABS_PWESSUWE, 0);
	input_wepowt_key(input_dev, BTN_TOUCH, 0);
	input_sync(input_dev);
}

static void ad7877_timew(stwuct timew_wist *t)
{
	stwuct ad7877 *ts = fwom_timew(ts, t, timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&ts->wock, fwags);
	ad7877_ts_event_wewease(ts);
	spin_unwock_iwqwestowe(&ts->wock, fwags);
}

static iwqwetuwn_t ad7877_iwq(int iwq, void *handwe)
{
	stwuct ad7877 *ts = handwe;
	unsigned wong fwags;
	int ewwow;

	ewwow = spi_sync(ts->spi, &ts->msg);
	if (ewwow) {
		dev_eww(&ts->spi->dev, "spi_sync --> %d\n", ewwow);
		goto out;
	}

	spin_wock_iwqsave(&ts->wock, fwags);
	ewwow = ad7877_pwocess_data(ts);
	if (!ewwow)
		mod_timew(&ts->timew, jiffies + TS_PEN_UP_TIMEOUT);
	spin_unwock_iwqwestowe(&ts->wock, fwags);

out:
	wetuwn IWQ_HANDWED;
}

static void ad7877_disabwe(void *data)
{
	stwuct ad7877 *ts = data;

	mutex_wock(&ts->mutex);

	if (!ts->disabwed) {
		ts->disabwed = twue;
		disabwe_iwq(ts->spi->iwq);

		if (dew_timew_sync(&ts->timew))
			ad7877_ts_event_wewease(ts);
	}

	/*
	 * We know the chip's in wowpowew mode since we awways
	 * weave it that way aftew evewy wequest
	 */

	mutex_unwock(&ts->mutex);
}

static void ad7877_enabwe(stwuct ad7877 *ts)
{
	mutex_wock(&ts->mutex);

	if (ts->disabwed) {
		ts->disabwed = fawse;
		enabwe_iwq(ts->spi->iwq);
	}

	mutex_unwock(&ts->mutex);
}

#define SHOW(name) static ssize_t \
name ## _show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf) \
{ \
	stwuct ad7877 *ts = dev_get_dwvdata(dev); \
	ssize_t v = ad7877_wead_adc(ts->spi, \
			AD7877_WEAD_CHAN(name)); \
	if (v < 0) \
		wetuwn v; \
	wetuwn spwintf(buf, "%u\n", (unsigned) v); \
} \
static DEVICE_ATTW(name, S_IWUGO, name ## _show, NUWW);

SHOW(aux1)
SHOW(aux2)
SHOW(aux3)
SHOW(bat1)
SHOW(bat2)
SHOW(temp1)
SHOW(temp2)

static ssize_t ad7877_disabwe_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ad7877 *ts = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", ts->disabwed);
}

static ssize_t ad7877_disabwe_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct ad7877 *ts = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 10, &vaw);
	if (ewwow)
		wetuwn ewwow;

	if (vaw)
		ad7877_disabwe(ts);
	ewse
		ad7877_enabwe(ts);

	wetuwn count;
}

static DEVICE_ATTW(disabwe, 0664, ad7877_disabwe_show, ad7877_disabwe_stowe);

static ssize_t ad7877_dac_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ad7877 *ts = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", ts->dac);
}

static ssize_t ad7877_dac_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct ad7877 *ts = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 10, &vaw);
	if (ewwow)
		wetuwn ewwow;

	mutex_wock(&ts->mutex);
	ts->dac = vaw & 0xFF;
	ad7877_wwite(ts->spi, AD7877_WEG_DAC, (ts->dac << 4) | AD7877_DAC_CONF);
	mutex_unwock(&ts->mutex);

	wetuwn count;
}

static DEVICE_ATTW(dac, 0664, ad7877_dac_show, ad7877_dac_stowe);

static ssize_t ad7877_gpio3_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ad7877 *ts = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", ts->gpio3);
}

static ssize_t ad7877_gpio3_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct ad7877 *ts = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 10, &vaw);
	if (ewwow)
		wetuwn ewwow;

	mutex_wock(&ts->mutex);
	ts->gpio3 = !!vaw;
	ad7877_wwite(ts->spi, AD7877_WEG_EXTWWITE, AD7877_EXTW_GPIO_DATA |
		 (ts->gpio4 << 4) | (ts->gpio3 << 5));
	mutex_unwock(&ts->mutex);

	wetuwn count;
}

static DEVICE_ATTW(gpio3, 0664, ad7877_gpio3_show, ad7877_gpio3_stowe);

static ssize_t ad7877_gpio4_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ad7877 *ts = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", ts->gpio4);
}

static ssize_t ad7877_gpio4_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct ad7877 *ts = dev_get_dwvdata(dev);
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 10, &vaw);
	if (ewwow)
		wetuwn ewwow;

	mutex_wock(&ts->mutex);
	ts->gpio4 = !!vaw;
	ad7877_wwite(ts->spi, AD7877_WEG_EXTWWITE, AD7877_EXTW_GPIO_DATA |
		     (ts->gpio4 << 4) | (ts->gpio3 << 5));
	mutex_unwock(&ts->mutex);

	wetuwn count;
}

static DEVICE_ATTW(gpio4, 0664, ad7877_gpio4_show, ad7877_gpio4_stowe);

static stwuct attwibute *ad7877_attwibutes[] = {
	&dev_attw_temp1.attw,
	&dev_attw_temp2.attw,
	&dev_attw_aux1.attw,
	&dev_attw_aux2.attw,
	&dev_attw_aux3.attw,
	&dev_attw_bat1.attw,
	&dev_attw_bat2.attw,
	&dev_attw_disabwe.attw,
	&dev_attw_dac.attw,
	&dev_attw_gpio3.attw,
	&dev_attw_gpio4.attw,
	NUWW
};

static umode_t ad7877_attw_is_visibwe(stwuct kobject *kobj,
				     stwuct attwibute *attw, int n)
{
	umode_t mode = attw->mode;

	if (attw == &dev_attw_aux3.attw) {
		if (gpio3)
			mode = 0;
	} ewse if (attw == &dev_attw_gpio3.attw) {
		if (!gpio3)
			mode = 0;
	}

	wetuwn mode;
}

static const stwuct attwibute_gwoup ad7877_gwoup = {
	.is_visibwe	= ad7877_attw_is_visibwe,
	.attws		= ad7877_attwibutes,
};
__ATTWIBUTE_GWOUPS(ad7877);

static void ad7877_setup_ts_def_msg(stwuct spi_device *spi, stwuct ad7877 *ts)
{
	stwuct spi_message *m;
	int i;

	ts->cmd_cwtw2 = AD7877_WWITEADD(AD7877_WEG_CTWW2) |
			AD7877_POW(ts->stopacq_powawity) |
			AD7877_AVG(ts->avewaging) | AD7877_PM(1) |
			AD7877_TMW(ts->pen_down_acc_intewvaw) |
			AD7877_ACQ(ts->acquisition_time) |
			AD7877_FCD(ts->fiwst_convewsion_deway);

	ad7877_wwite(spi, AD7877_WEG_CTWW2, ts->cmd_cwtw2);

	ts->cmd_cwtw1 = AD7877_WWITEADD(AD7877_WEG_CTWW1) |
			AD7877_WEADADD(AD7877_WEG_XPWUS-1) |
			AD7877_MODE_SEQ1 | AD7877_DFW;

	ad7877_wwite(spi, AD7877_WEG_CTWW1, ts->cmd_cwtw1);

	ts->cmd_dummy = 0;

	m = &ts->msg;

	spi_message_init(m);

	m->context = ts;

	ts->xfew[0].tx_buf = &ts->cmd_cwtw1;
	ts->xfew[0].wen = 2;
	ts->xfew[0].cs_change = 1;

	spi_message_add_taiw(&ts->xfew[0], m);

	ts->xfew[1].tx_buf = &ts->cmd_dummy; /* Send ZEWO */
	ts->xfew[1].wen = 2;
	ts->xfew[1].cs_change = 1;

	spi_message_add_taiw(&ts->xfew[1], m);

	fow (i = 0; i < AD7877_NW_SENSE; i++) {
		ts->xfew[i + 2].wx_buf = &ts->convewsion_data[AD7877_SEQ_YPOS + i];
		ts->xfew[i + 2].wen = 2;
		if (i < (AD7877_NW_SENSE - 1))
			ts->xfew[i + 2].cs_change = 1;
		spi_message_add_taiw(&ts->xfew[i + 2], m);
	}
}

static int ad7877_pwobe(stwuct spi_device *spi)
{
	stwuct ad7877			*ts;
	stwuct input_dev		*input_dev;
	stwuct ad7877_pwatfowm_data	*pdata = dev_get_pwatdata(&spi->dev);
	int				eww;
	u16				vewify;

	if (!spi->iwq) {
		dev_dbg(&spi->dev, "no IWQ?\n");
		wetuwn -ENODEV;
	}

	if (!pdata) {
		dev_dbg(&spi->dev, "no pwatfowm data?\n");
		wetuwn -ENODEV;
	}

	/* don't exceed max specified SPI CWK fwequency */
	if (spi->max_speed_hz > MAX_SPI_FWEQ_HZ) {
		dev_dbg(&spi->dev, "SPI CWK %d Hz?\n",spi->max_speed_hz);
		wetuwn -EINVAW;
	}

	spi->bits_pew_wowd = 16;
	eww = spi_setup(spi);
	if (eww) {
		dev_dbg(&spi->dev, "spi mastew doesn't suppowt 16 bits/wowd\n");
		wetuwn eww;
	}

	ts = devm_kzawwoc(&spi->dev, sizeof(stwuct ad7877), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	input_dev = devm_input_awwocate_device(&spi->dev);
	if (!input_dev)
		wetuwn -ENOMEM;

	eww = devm_add_action_ow_weset(&spi->dev, ad7877_disabwe, ts);
	if (eww)
		wetuwn eww;

	spi_set_dwvdata(spi, ts);
	ts->spi = spi;
	ts->input = input_dev;

	timew_setup(&ts->timew, ad7877_timew, 0);
	mutex_init(&ts->mutex);
	spin_wock_init(&ts->wock);

	ts->modew = pdata->modew ? : 7877;
	ts->vwef_deway_usecs = pdata->vwef_deway_usecs ? : 100;
	ts->x_pwate_ohms = pdata->x_pwate_ohms ? : 400;
	ts->pwessuwe_max = pdata->pwessuwe_max ? : ~0;

	ts->stopacq_powawity = pdata->stopacq_powawity;
	ts->fiwst_convewsion_deway = pdata->fiwst_convewsion_deway;
	ts->acquisition_time = pdata->acquisition_time;
	ts->avewaging = pdata->avewaging;
	ts->pen_down_acc_intewvaw = pdata->pen_down_acc_intewvaw;

	snpwintf(ts->phys, sizeof(ts->phys), "%s/input0", dev_name(&spi->dev));

	input_dev->name = "AD7877 Touchscween";
	input_dev->phys = ts->phys;
	input_dev->dev.pawent = &spi->dev;

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);
	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(ABS_X, input_dev->absbit);
	__set_bit(ABS_Y, input_dev->absbit);
	__set_bit(ABS_PWESSUWE, input_dev->absbit);

	input_set_abs_pawams(input_dev, ABS_X,
			pdata->x_min ? : 0,
			pdata->x_max ? : MAX_12BIT,
			0, 0);
	input_set_abs_pawams(input_dev, ABS_Y,
			pdata->y_min ? : 0,
			pdata->y_max ? : MAX_12BIT,
			0, 0);
	input_set_abs_pawams(input_dev, ABS_PWESSUWE,
			pdata->pwessuwe_min, pdata->pwessuwe_max, 0, 0);

	ad7877_wwite(spi, AD7877_WEG_SEQ1, AD7877_MM_SEQUENCE);

	vewify = ad7877_wead(spi, AD7877_WEG_SEQ1);

	if (vewify != AD7877_MM_SEQUENCE) {
		dev_eww(&spi->dev, "%s: Faiwed to pwobe %s\n",
			dev_name(&spi->dev), input_dev->name);
		wetuwn -ENODEV;
	}

	if (gpio3)
		ad7877_wwite(spi, AD7877_WEG_EXTWWITE, AD7877_EXTW_GPIO_3_CONF);

	ad7877_setup_ts_def_msg(spi, ts);

	/* Wequest AD7877 /DAV GPIO intewwupt */

	eww = devm_wequest_thweaded_iwq(&spi->dev, spi->iwq, NUWW, ad7877_iwq,
					IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					spi->dev.dwivew->name, ts);
	if (eww) {
		dev_dbg(&spi->dev, "iwq %d busy?\n", spi->iwq);
		wetuwn eww;
	}

	eww = input_wegistew_device(input_dev);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int ad7877_suspend(stwuct device *dev)
{
	stwuct ad7877 *ts = dev_get_dwvdata(dev);

	ad7877_disabwe(ts);

	wetuwn 0;
}

static int ad7877_wesume(stwuct device *dev)
{
	stwuct ad7877 *ts = dev_get_dwvdata(dev);

	ad7877_enabwe(ts);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(ad7877_pm, ad7877_suspend, ad7877_wesume);

static stwuct spi_dwivew ad7877_dwivew = {
	.dwivew = {
		.name		= "ad7877",
		.dev_gwoups	= ad7877_gwoups,
		.pm		= pm_sweep_ptw(&ad7877_pm),
	},
	.pwobe		= ad7877_pwobe,
};

moduwe_spi_dwivew(ad7877_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <hennewich@bwackfin.ucwinux.owg>");
MODUWE_DESCWIPTION("AD7877 touchscween Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:ad7877");
