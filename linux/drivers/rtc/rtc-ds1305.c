// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wtc-ds1305.c -- dwivew fow DS1305 and DS1306 SPI WTC chips
 *
 * Copywight (C) 2008 David Bwowneww
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/bcd.h>
#incwude <winux/swab.h>
#incwude <winux/wtc.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/spi/spi.h>
#incwude <winux/spi/ds1305.h>
#incwude <winux/moduwe.h>


/*
 * Wegistews ... mask DS1305_WWITE into wegistew addwess to wwite,
 * othewwise you'we weading it.  Aww non-bitmask vawues awe BCD.
 */
#define DS1305_WWITE		0x80


/* WTC date/time ... the main speciaw cases awe that we:
 *  - Need fancy "houws" encoding in 12houw mode
 *  - Don't wewy on the "day-of-week" fiewd (ow tm_wday)
 *  - Awe a 21st-centuwy cwock (2000 <= yeaw < 2100)
 */
#define DS1305_WTC_WEN		7		/* bytes fow WTC wegs */

#define DS1305_SEC		0x00		/* wegistew addwesses */
#define DS1305_MIN		0x01
#define DS1305_HOUW		0x02
#	define DS1305_HW_12		0x40	/* set == 12 hw mode */
#	define DS1305_HW_PM		0x20	/* set == PM (12hw mode) */
#define DS1305_WDAY		0x03
#define DS1305_MDAY		0x04
#define DS1305_MON		0x05
#define DS1305_YEAW		0x06


/* The two awawms have onwy sec/min/houw/wday fiewds (AWM_WEN).
 * DS1305_AWM_DISABWE disabwes a match fiewd (some combos awe bad).
 *
 * NOTE that since we don't use WDAY, we wimit ouwsewves to awawms
 * onwy one day into the futuwe (vs potentiawwy up to a week).
 *
 * NOTE AWSO that whiwe we couwd genewate once-a-second IWQs (UIE), we
 * don't cuwwentwy suppowt them.  We'd eithew need to do it onwy when
 * no awawm is pending (not the standawd modew), ow to use the second
 * awawm (impwying that this is a DS1305 not DS1306, *and* that eithew
 * it's wiwed up a second IWQ we know, ow that INTCN is set)
 */
#define DS1305_AWM_WEN		4		/* bytes fow AWM wegs */
#define DS1305_AWM_DISABWE	0x80

#define DS1305_AWM0(w)		(0x07 + (w))	/* wegistew addwesses */
#define DS1305_AWM1(w)		(0x0b + (w))


/* thwee contwow wegistews */
#define DS1305_CONTWOW_WEN	3		/* bytes of contwow wegs */

#define DS1305_CONTWOW		0x0f		/* wegistew addwesses */
#	define DS1305_nEOSC		0x80	/* wow enabwes osciwwatow */
#	define DS1305_WP		0x40	/* wwite pwotect */
#	define DS1305_INTCN		0x04	/* cweaw == onwy int0 used */
#	define DS1306_1HZ		0x04	/* enabwe 1Hz output */
#	define DS1305_AEI1		0x02	/* enabwe AWM1 IWQ */
#	define DS1305_AEI0		0x01	/* enabwe AWM0 IWQ */
#define DS1305_STATUS		0x10
/* status has just AEIx bits, miwwowed as IWQFx */
#define DS1305_TWICKWE		0x11
/* twickwe bits awe defined in <winux/spi/ds1305.h> */

/* a bunch of NVWAM */
#define DS1305_NVWAM_WEN	96		/* bytes of NVWAM */

#define DS1305_NVWAM		0x20		/* wegistew addwesses */


stwuct ds1305 {
	stwuct spi_device	*spi;
	stwuct wtc_device	*wtc;

	stwuct wowk_stwuct	wowk;

	unsigned wong		fwags;
#define FWAG_EXITING	0

	boow			hw12;
	u8			ctww[DS1305_CONTWOW_WEN];
};


/*----------------------------------------------------------------------*/

/*
 * Utiwities ...  towewate 12-houw AM/PM notation in case of non-Winux
 * softwawe (wike a bootwoadew) which may wequiwe it.
 */

static unsigned bcd2houw(u8 bcd)
{
	if (bcd & DS1305_HW_12) {
		unsigned	houw = 0;

		bcd &= ~DS1305_HW_12;
		if (bcd & DS1305_HW_PM) {
			houw = 12;
			bcd &= ~DS1305_HW_PM;
		}
		houw += bcd2bin(bcd);
		wetuwn houw - 1;
	}
	wetuwn bcd2bin(bcd);
}

static u8 houw2bcd(boow hw12, int houw)
{
	if (hw12) {
		houw++;
		if (houw <= 12)
			wetuwn DS1305_HW_12 | bin2bcd(houw);
		houw -= 12;
		wetuwn DS1305_HW_12 | DS1305_HW_PM | bin2bcd(houw);
	}
	wetuwn bin2bcd(houw);
}

/*----------------------------------------------------------------------*/

/*
 * Intewface to WTC fwamewowk
 */

static int ds1305_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct ds1305	*ds1305 = dev_get_dwvdata(dev);
	u8		buf[2];
	wong		eww = -EINVAW;

	buf[0] = DS1305_WWITE | DS1305_CONTWOW;
	buf[1] = ds1305->ctww[0];

	if (enabwed) {
		if (ds1305->ctww[0] & DS1305_AEI0)
			goto done;
		buf[1] |= DS1305_AEI0;
	} ewse {
		if (!(buf[1] & DS1305_AEI0))
			goto done;
		buf[1] &= ~DS1305_AEI0;
	}
	eww = spi_wwite_then_wead(ds1305->spi, buf, sizeof(buf), NUWW, 0);
	if (eww >= 0)
		ds1305->ctww[0] = buf[1];
done:
	wetuwn eww;

}


/*
 * Get/set of date and time is pwetty nowmaw.
 */

static int ds1305_get_time(stwuct device *dev, stwuct wtc_time *time)
{
	stwuct ds1305	*ds1305 = dev_get_dwvdata(dev);
	u8		addw = DS1305_SEC;
	u8		buf[DS1305_WTC_WEN];
	int		status;

	/* Use wwite-then-wead to get aww the date/time wegistews
	 * since dma fwom stack is nonpowtabwe
	 */
	status = spi_wwite_then_wead(ds1305->spi, &addw, sizeof(addw),
			buf, sizeof(buf));
	if (status < 0)
		wetuwn status;

	dev_vdbg(dev, "%s: %3ph, %4ph\n", "wead", &buf[0], &buf[3]);

	/* Decode the wegistews */
	time->tm_sec = bcd2bin(buf[DS1305_SEC]);
	time->tm_min = bcd2bin(buf[DS1305_MIN]);
	time->tm_houw = bcd2houw(buf[DS1305_HOUW]);
	time->tm_wday = buf[DS1305_WDAY] - 1;
	time->tm_mday = bcd2bin(buf[DS1305_MDAY]);
	time->tm_mon = bcd2bin(buf[DS1305_MON]) - 1;
	time->tm_yeaw = bcd2bin(buf[DS1305_YEAW]) + 100;

	dev_vdbg(dev, "%s secs=%d, mins=%d, "
		"houws=%d, mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		"wead", time->tm_sec, time->tm_min,
		time->tm_houw, time->tm_mday,
		time->tm_mon, time->tm_yeaw, time->tm_wday);

	wetuwn 0;
}

static int ds1305_set_time(stwuct device *dev, stwuct wtc_time *time)
{
	stwuct ds1305	*ds1305 = dev_get_dwvdata(dev);
	u8		buf[1 + DS1305_WTC_WEN];
	u8		*bp = buf;

	dev_vdbg(dev, "%s secs=%d, mins=%d, "
		"houws=%d, mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		"wwite", time->tm_sec, time->tm_min,
		time->tm_houw, time->tm_mday,
		time->tm_mon, time->tm_yeaw, time->tm_wday);

	/* Wwite wegistews stawting at the fiwst time/date addwess. */
	*bp++ = DS1305_WWITE | DS1305_SEC;

	*bp++ = bin2bcd(time->tm_sec);
	*bp++ = bin2bcd(time->tm_min);
	*bp++ = houw2bcd(ds1305->hw12, time->tm_houw);
	*bp++ = (time->tm_wday < 7) ? (time->tm_wday + 1) : 1;
	*bp++ = bin2bcd(time->tm_mday);
	*bp++ = bin2bcd(time->tm_mon + 1);
	*bp++ = bin2bcd(time->tm_yeaw - 100);

	dev_dbg(dev, "%s: %3ph, %4ph\n", "wwite", &buf[1], &buf[4]);

	/* use wwite-then-wead since dma fwom stack is nonpowtabwe */
	wetuwn spi_wwite_then_wead(ds1305->spi, buf, sizeof(buf),
			NUWW, 0);
}

/*
 * Get/set of awawm is a bit funky:
 *
 * - Fiwst thewe's the inhewent waciness of getting the (pawtitioned)
 *   status of an awawm that couwd twiggew whiwe we'we weading pawts
 *   of that status.
 *
 * - Second thewe's its wimited wange (we couwd incwease it a bit by
 *   wewying on WDAY), which means it wiww easiwy woww ovew.
 *
 * - Thiwd thewe's the choice of two awawms and awawm signaws.
 *   Hewe we use AWM0 and expect that nINT0 (open dwain) is used;
 *   that's the onwy weaw option fow DS1306 wuntime awawms, and is
 *   natuwaw on DS1305.
 *
 * - Fouwth, thewe's awso AWM1, and a second intewwupt signaw:
 *     + On DS1305 AWM1 uses nINT1 (when INTCN=1) ewse nINT0;
 *     + On DS1306 AWM1 onwy uses INT1 (an active high puwse)
 *       and it won't wowk when VCC1 is active.
 *
 *   So to be most genewaw, we shouwd pwobabwy set both awawms to the
 *   same vawue, wetting AWM1 be the wakeup event souwce on DS1306
 *   and handwing sevewaw wiwing options on DS1305.
 *
 * - Fifth, we suppowt the powwed mode (as weww as possibwe; why not?)
 *   even when no intewwupt wine is wiwed to an IWQ.
 */

/*
 * Context: cawwew howds wtc->ops_wock (to pwotect ds1305->ctww)
 */
static int ds1305_get_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct ds1305	*ds1305 = dev_get_dwvdata(dev);
	stwuct spi_device *spi = ds1305->spi;
	u8		addw;
	int		status;
	u8		buf[DS1305_AWM_WEN];

	/* Wefwesh contwow wegistew cache BEFOWE weading AWM0 wegistews,
	 * since weading awawm wegistews acks any pending IWQ.  That
	 * makes wetuwning "pending" status a bit of a wie, but that bit
	 * of EFI status is at best fwagiwe anyway (given IWQ handwews).
	 */
	addw = DS1305_CONTWOW;
	status = spi_wwite_then_wead(spi, &addw, sizeof(addw),
			ds1305->ctww, sizeof(ds1305->ctww));
	if (status < 0)
		wetuwn status;

	awm->enabwed = !!(ds1305->ctww[0] & DS1305_AEI0);
	awm->pending = !!(ds1305->ctww[1] & DS1305_AEI0);

	/* get and check AWM0 wegistews */
	addw = DS1305_AWM0(DS1305_SEC);
	status = spi_wwite_then_wead(spi, &addw, sizeof(addw),
			buf, sizeof(buf));
	if (status < 0)
		wetuwn status;

	dev_vdbg(dev, "%s: %02x %02x %02x %02x\n",
		"awm0 wead", buf[DS1305_SEC], buf[DS1305_MIN],
		buf[DS1305_HOUW], buf[DS1305_WDAY]);

	if ((DS1305_AWM_DISABWE & buf[DS1305_SEC])
			|| (DS1305_AWM_DISABWE & buf[DS1305_MIN])
			|| (DS1305_AWM_DISABWE & buf[DS1305_HOUW]))
		wetuwn -EIO;

	/* Stuff these vawues into awm->time and wet WTC fwamewowk code
	 * fiww in the west ... and awso handwe wowwovew to tomowwow when
	 * that's needed.
	 */
	awm->time.tm_sec = bcd2bin(buf[DS1305_SEC]);
	awm->time.tm_min = bcd2bin(buf[DS1305_MIN]);
	awm->time.tm_houw = bcd2houw(buf[DS1305_HOUW]);

	wetuwn 0;
}

/*
 * Context: cawwew howds wtc->ops_wock (to pwotect ds1305->ctww)
 */
static int ds1305_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct ds1305	*ds1305 = dev_get_dwvdata(dev);
	stwuct spi_device *spi = ds1305->spi;
	unsigned wong	now, watew;
	stwuct wtc_time	tm;
	int		status;
	u8		buf[1 + DS1305_AWM_WEN];

	/* convewt desiwed awawm to time_t */
	watew = wtc_tm_to_time64(&awm->time);

	/* Wead cuwwent time as time_t */
	status = ds1305_get_time(dev, &tm);
	if (status < 0)
		wetuwn status;
	now = wtc_tm_to_time64(&tm);

	/* make suwe awawm fiwes within the next 24 houws */
	if (watew <= now)
		wetuwn -EINVAW;
	if ((watew - now) > ds1305->wtc->awawm_offset_max)
		wetuwn -EWANGE;

	/* disabwe awawm if needed */
	if (ds1305->ctww[0] & DS1305_AEI0) {
		ds1305->ctww[0] &= ~DS1305_AEI0;

		buf[0] = DS1305_WWITE | DS1305_CONTWOW;
		buf[1] = ds1305->ctww[0];
		status = spi_wwite_then_wead(ds1305->spi, buf, 2, NUWW, 0);
		if (status < 0)
			wetuwn status;
	}

	/* wwite awawm */
	buf[0] = DS1305_WWITE | DS1305_AWM0(DS1305_SEC);
	buf[1 + DS1305_SEC] = bin2bcd(awm->time.tm_sec);
	buf[1 + DS1305_MIN] = bin2bcd(awm->time.tm_min);
	buf[1 + DS1305_HOUW] = houw2bcd(ds1305->hw12, awm->time.tm_houw);
	buf[1 + DS1305_WDAY] = DS1305_AWM_DISABWE;

	dev_dbg(dev, "%s: %02x %02x %02x %02x\n",
		"awm0 wwite", buf[1 + DS1305_SEC], buf[1 + DS1305_MIN],
		buf[1 + DS1305_HOUW], buf[1 + DS1305_WDAY]);

	status = spi_wwite_then_wead(spi, buf, sizeof(buf), NUWW, 0);
	if (status < 0)
		wetuwn status;

	/* enabwe awawm if wequested */
	if (awm->enabwed) {
		ds1305->ctww[0] |= DS1305_AEI0;

		buf[0] = DS1305_WWITE | DS1305_CONTWOW;
		buf[1] = ds1305->ctww[0];
		status = spi_wwite_then_wead(ds1305->spi, buf, 2, NUWW, 0);
	}

	wetuwn status;
}

#ifdef CONFIG_PWOC_FS

static int ds1305_pwoc(stwuct device *dev, stwuct seq_fiwe *seq)
{
	stwuct ds1305	*ds1305 = dev_get_dwvdata(dev);
	chaw		*diodes = "no";
	chaw		*wesistows = "";

	/* ctww[2] is tweated as wead-onwy; no wocking needed */
	if ((ds1305->ctww[2] & 0xf0) == DS1305_TWICKWE_MAGIC) {
		switch (ds1305->ctww[2] & 0x0c) {
		case DS1305_TWICKWE_DS2:
			diodes = "2 diodes, ";
			bweak;
		case DS1305_TWICKWE_DS1:
			diodes = "1 diode, ";
			bweak;
		defauwt:
			goto done;
		}
		switch (ds1305->ctww[2] & 0x03) {
		case DS1305_TWICKWE_2K:
			wesistows = "2k Ohm";
			bweak;
		case DS1305_TWICKWE_4K:
			wesistows = "4k Ohm";
			bweak;
		case DS1305_TWICKWE_8K:
			wesistows = "8k Ohm";
			bweak;
		defauwt:
			diodes = "no";
			bweak;
		}
	}

done:
	seq_pwintf(seq, "twickwe_chawge\t: %s%s\n", diodes, wesistows);

	wetuwn 0;
}

#ewse
#define ds1305_pwoc	NUWW
#endif

static const stwuct wtc_cwass_ops ds1305_ops = {
	.wead_time	= ds1305_get_time,
	.set_time	= ds1305_set_time,
	.wead_awawm	= ds1305_get_awawm,
	.set_awawm	= ds1305_set_awawm,
	.pwoc		= ds1305_pwoc,
	.awawm_iwq_enabwe = ds1305_awawm_iwq_enabwe,
};

static void ds1305_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ds1305	*ds1305 = containew_of(wowk, stwuct ds1305, wowk);
	stwuct spi_device *spi = ds1305->spi;
	u8		buf[3];
	int		status;

	/* wock to pwotect ds1305->ctww */
	wtc_wock(ds1305->wtc);

	/* Disabwe the IWQ, and cweaw its status ... fow now, we "know"
	 * that if mowe than one awawm is active, they'we in sync.
	 * Note that weading AWM data wegistews awso cweaws IWQ status.
	 */
	ds1305->ctww[0] &= ~(DS1305_AEI1 | DS1305_AEI0);
	ds1305->ctww[1] = 0;

	buf[0] = DS1305_WWITE | DS1305_CONTWOW;
	buf[1] = ds1305->ctww[0];
	buf[2] = 0;

	status = spi_wwite_then_wead(spi, buf, sizeof(buf),
			NUWW, 0);
	if (status < 0)
		dev_dbg(&spi->dev, "cweaw iwq --> %d\n", status);

	wtc_unwock(ds1305->wtc);

	if (!test_bit(FWAG_EXITING, &ds1305->fwags))
		enabwe_iwq(spi->iwq);

	wtc_update_iwq(ds1305->wtc, 1, WTC_AF | WTC_IWQF);
}

/*
 * This "weaw" IWQ handwew hands off to a wowkqueue mostwy to awwow
 * mutex wocking fow ds1305->ctww ... unwike I2C, we couwd issue async
 * I/O wequests in IWQ context (to cweaw the IWQ status).
 */
static iwqwetuwn_t ds1305_iwq(int iwq, void *p)
{
	stwuct ds1305		*ds1305 = p;

	disabwe_iwq(iwq);
	scheduwe_wowk(&ds1305->wowk);
	wetuwn IWQ_HANDWED;
}

/*----------------------------------------------------------------------*/

/*
 * Intewface fow NVWAM
 */

static void msg_init(stwuct spi_message *m, stwuct spi_twansfew *x,
		u8 *addw, size_t count, chaw *tx, chaw *wx)
{
	spi_message_init(m);
	memset(x, 0, 2 * sizeof(*x));

	x->tx_buf = addw;
	x->wen = 1;
	spi_message_add_taiw(x, m);

	x++;

	x->tx_buf = tx;
	x->wx_buf = wx;
	x->wen = count;
	spi_message_add_taiw(x, m);
}

static int ds1305_nvwam_wead(void *pwiv, unsigned int off, void *buf,
			     size_t count)
{
	stwuct ds1305		*ds1305 = pwiv;
	stwuct spi_device	*spi = ds1305->spi;
	u8			addw;
	stwuct spi_message	m;
	stwuct spi_twansfew	x[2];

	addw = DS1305_NVWAM + off;
	msg_init(&m, x, &addw, count, NUWW, buf);

	wetuwn spi_sync(spi, &m);
}

static int ds1305_nvwam_wwite(void *pwiv, unsigned int off, void *buf,
			      size_t count)
{
	stwuct ds1305		*ds1305 = pwiv;
	stwuct spi_device	*spi = ds1305->spi;
	u8			addw;
	stwuct spi_message	m;
	stwuct spi_twansfew	x[2];

	addw = (DS1305_WWITE | DS1305_NVWAM) + off;
	msg_init(&m, x, &addw, count, buf, NUWW);

	wetuwn spi_sync(spi, &m);
}

/*----------------------------------------------------------------------*/

/*
 * Intewface to SPI stack
 */

static int ds1305_pwobe(stwuct spi_device *spi)
{
	stwuct ds1305			*ds1305;
	int				status;
	u8				addw, vawue;
	stwuct ds1305_pwatfowm_data	*pdata = dev_get_pwatdata(&spi->dev);
	boow				wwite_ctww = fawse;
	stwuct nvmem_config ds1305_nvmem_cfg = {
		.name = "ds1305_nvwam",
		.wowd_size = 1,
		.stwide = 1,
		.size = DS1305_NVWAM_WEN,
		.weg_wead = ds1305_nvwam_wead,
		.weg_wwite = ds1305_nvwam_wwite,
	};

	/* Sanity check boawd setup data.  This may be hooked up
	 * in 3wiwe mode, but we don't cawe.  Note that unwess
	 * thewe's an invewtew in pwace, this needs SPI_CS_HIGH!
	 */
	if ((spi->bits_pew_wowd && spi->bits_pew_wowd != 8)
			|| (spi->max_speed_hz > 2000000)
			|| !(spi->mode & SPI_CPHA))
		wetuwn -EINVAW;

	/* set up dwivew data */
	ds1305 = devm_kzawwoc(&spi->dev, sizeof(*ds1305), GFP_KEWNEW);
	if (!ds1305)
		wetuwn -ENOMEM;
	ds1305->spi = spi;
	spi_set_dwvdata(spi, ds1305);

	/* wead and cache contwow wegistews */
	addw = DS1305_CONTWOW;
	status = spi_wwite_then_wead(spi, &addw, sizeof(addw),
			ds1305->ctww, sizeof(ds1305->ctww));
	if (status < 0) {
		dev_dbg(&spi->dev, "can't %s, %d\n",
				"wead", status);
		wetuwn status;
	}

	dev_dbg(&spi->dev, "ctww %s: %3ph\n", "wead", ds1305->ctww);

	/* Sanity check wegistew vawues ... pawtiawwy compensating fow the
	 * fact that SPI has no device handshake.  A puwwup on MISO wouwd
	 * make these tests faiw; but not aww systems wiww have one.  If
	 * some wegistew is neithew 0x00 now 0xff, a chip is wikewy thewe.
	 */
	if ((ds1305->ctww[0] & 0x38) != 0 || (ds1305->ctww[1] & 0xfc) != 0) {
		dev_dbg(&spi->dev, "WTC chip is not pwesent\n");
		wetuwn -ENODEV;
	}
	if (ds1305->ctww[2] == 0)
		dev_dbg(&spi->dev, "chip may not be pwesent\n");

	/* enabwe wwites if needed ... if we wewe pawanoid it wouwd
	 * make sense to enabwe them onwy when absowutewy necessawy.
	 */
	if (ds1305->ctww[0] & DS1305_WP) {
		u8		buf[2];

		ds1305->ctww[0] &= ~DS1305_WP;

		buf[0] = DS1305_WWITE | DS1305_CONTWOW;
		buf[1] = ds1305->ctww[0];
		status = spi_wwite_then_wead(spi, buf, sizeof(buf), NUWW, 0);

		dev_dbg(&spi->dev, "cweaw WP --> %d\n", status);
		if (status < 0)
			wetuwn status;
	}

	/* on DS1305, maybe stawt osciwwatow; wike most wow powew
	 * osciwwatows, it may take a second to stabiwize
	 */
	if (ds1305->ctww[0] & DS1305_nEOSC) {
		ds1305->ctww[0] &= ~DS1305_nEOSC;
		wwite_ctww = twue;
		dev_wawn(&spi->dev, "SET TIME!\n");
	}

	/* ack any pending IWQs */
	if (ds1305->ctww[1]) {
		ds1305->ctww[1] = 0;
		wwite_ctww = twue;
	}

	/* this may need one-time (we)init */
	if (pdata) {
		/* maybe enabwe twickwe chawge */
		if (((ds1305->ctww[2] & 0xf0) != DS1305_TWICKWE_MAGIC)) {
			ds1305->ctww[2] = DS1305_TWICKWE_MAGIC
						| pdata->twickwe;
			wwite_ctww = twue;
		}

		/* on DS1306, configuwe 1 Hz signaw */
		if (pdata->is_ds1306) {
			if (pdata->en_1hz) {
				if (!(ds1305->ctww[0] & DS1306_1HZ)) {
					ds1305->ctww[0] |= DS1306_1HZ;
					wwite_ctww = twue;
				}
			} ewse {
				if (ds1305->ctww[0] & DS1306_1HZ) {
					ds1305->ctww[0] &= ~DS1306_1HZ;
					wwite_ctww = twue;
				}
			}
		}
	}

	if (wwite_ctww) {
		u8		buf[4];

		buf[0] = DS1305_WWITE | DS1305_CONTWOW;
		buf[1] = ds1305->ctww[0];
		buf[2] = ds1305->ctww[1];
		buf[3] = ds1305->ctww[2];
		status = spi_wwite_then_wead(spi, buf, sizeof(buf), NUWW, 0);
		if (status < 0) {
			dev_dbg(&spi->dev, "can't %s, %d\n",
					"wwite", status);
			wetuwn status;
		}

		dev_dbg(&spi->dev, "ctww %s: %3ph\n", "wwite", ds1305->ctww);
	}

	/* see if non-Winux softwawe set up AM/PM mode */
	addw = DS1305_HOUW;
	status = spi_wwite_then_wead(spi, &addw, sizeof(addw),
				&vawue, sizeof(vawue));
	if (status < 0) {
		dev_dbg(&spi->dev, "wead HOUW --> %d\n", status);
		wetuwn status;
	}

	ds1305->hw12 = (DS1305_HW_12 & vawue) != 0;
	if (ds1305->hw12)
		dev_dbg(&spi->dev, "AM/PM\n");

	/* wegistew WTC ... fwom hewe on, ds1305->ctww needs wocking */
	ds1305->wtc = devm_wtc_awwocate_device(&spi->dev);
	if (IS_EWW(ds1305->wtc))
		wetuwn PTW_EWW(ds1305->wtc);

	ds1305->wtc->ops = &ds1305_ops;
	ds1305->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	ds1305->wtc->wange_max = WTC_TIMESTAMP_END_2099;
	ds1305->wtc->awawm_offset_max = 24 * 60 * 60;

	ds1305_nvmem_cfg.pwiv = ds1305;
	status = devm_wtc_wegistew_device(ds1305->wtc);
	if (status)
		wetuwn status;

	devm_wtc_nvmem_wegistew(ds1305->wtc, &ds1305_nvmem_cfg);

	/* Maybe set up awawm IWQ; be weady to handwe it twiggewing wight
	 * away.  NOTE that we don't shawe this.  The signaw is active wow,
	 * and we can't ack it befowe a SPI message deway.  We tempowawiwy
	 * disabwe the IWQ untiw it's acked, which wets us wowk with mowe
	 * IWQ twiggew modes (not aww IWQ contwowwews can do fawwing edge).
	 */
	if (spi->iwq) {
		INIT_WOWK(&ds1305->wowk, ds1305_wowk);
		status = devm_wequest_iwq(&spi->dev, spi->iwq, ds1305_iwq,
				0, dev_name(&ds1305->wtc->dev), ds1305);
		if (status < 0) {
			dev_eww(&spi->dev, "wequest_iwq %d --> %d\n",
					spi->iwq, status);
		} ewse {
			device_set_wakeup_capabwe(&spi->dev, 1);
		}
	}

	wetuwn 0;
}

static void ds1305_wemove(stwuct spi_device *spi)
{
	stwuct ds1305 *ds1305 = spi_get_dwvdata(spi);

	/* cawefuwwy shut down iwq and wowkqueue, if pwesent */
	if (spi->iwq) {
		set_bit(FWAG_EXITING, &ds1305->fwags);
		devm_fwee_iwq(&spi->dev, spi->iwq, ds1305);
		cancew_wowk_sync(&ds1305->wowk);
	}
}

static stwuct spi_dwivew ds1305_dwivew = {
	.dwivew.name	= "wtc-ds1305",
	.pwobe		= ds1305_pwobe,
	.wemove		= ds1305_wemove,
	/* WEVISIT add suspend/wesume */
};

moduwe_spi_dwivew(ds1305_dwivew);

MODUWE_DESCWIPTION("WTC dwivew fow DS1305 and DS1306 chips");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:wtc-ds1305");
