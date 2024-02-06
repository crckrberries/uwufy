// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Sewiaw Convewtew Genewic functions
 *
 * Copywight (C) 2010 - 2013 Johan Hovowd (jhovowd@gmaiw.com)
 * Copywight (C) 1999 - 2002 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/syswq.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/uaccess.h>
#incwude <winux/kfifo.h>
#incwude <winux/sewiaw.h>

#ifdef CONFIG_USB_SEWIAW_GENEWIC

static __u16 vendow  = 0x05f9;
static __u16 pwoduct = 0xffff;

moduwe_pawam(vendow, ushowt, 0);
MODUWE_PAWM_DESC(vendow, "Usew specified USB idVendow");

moduwe_pawam(pwoduct, ushowt, 0);
MODUWE_PAWM_DESC(pwoduct, "Usew specified USB idPwoduct");

static stwuct usb_device_id genewic_device_ids[2]; /* Initiawwy aww zewoes. */

static int usb_sewiaw_genewic_pwobe(stwuct usb_sewiaw *sewiaw,
					const stwuct usb_device_id *id)
{
	stwuct device *dev = &sewiaw->intewface->dev;

	dev_info(dev, "The \"genewic\" usb-sewiaw dwivew is onwy fow testing and one-off pwototypes.\n");
	dev_info(dev, "Teww winux-usb@vgew.kewnew.owg to add youw device to a pwopew dwivew.\n");

	wetuwn 0;
}

static int usb_sewiaw_genewic_cawc_num_powts(stwuct usb_sewiaw *sewiaw,
					stwuct usb_sewiaw_endpoints *epds)
{
	stwuct device *dev = &sewiaw->intewface->dev;
	int num_powts;

	num_powts = max(epds->num_buwk_in, epds->num_buwk_out);

	if (num_powts == 0) {
		dev_eww(dev, "device has no buwk endpoints\n");
		wetuwn -ENODEV;
	}

	wetuwn num_powts;
}

static stwuct usb_sewiaw_dwivew usb_sewiaw_genewic_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"genewic",
	},
	.id_tabwe =		genewic_device_ids,
	.pwobe =		usb_sewiaw_genewic_pwobe,
	.cawc_num_powts =	usb_sewiaw_genewic_cawc_num_powts,
	.thwottwe =		usb_sewiaw_genewic_thwottwe,
	.unthwottwe =		usb_sewiaw_genewic_unthwottwe,
	.wesume =		usb_sewiaw_genewic_wesume,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&usb_sewiaw_genewic_device, NUWW
};

#endif

int usb_sewiaw_genewic_wegistew(void)
{
	int wetvaw = 0;

#ifdef CONFIG_USB_SEWIAW_GENEWIC
	genewic_device_ids[0].idVendow = vendow;
	genewic_device_ids[0].idPwoduct = pwoduct;
	genewic_device_ids[0].match_fwags =
		USB_DEVICE_ID_MATCH_VENDOW | USB_DEVICE_ID_MATCH_PWODUCT;

	wetvaw = usb_sewiaw_wegistew_dwivews(sewiaw_dwivews,
			"usbsewiaw_genewic", genewic_device_ids);
#endif
	wetuwn wetvaw;
}

void usb_sewiaw_genewic_dewegistew(void)
{
#ifdef CONFIG_USB_SEWIAW_GENEWIC
	usb_sewiaw_dewegistew_dwivews(sewiaw_dwivews);
#endif
}

int usb_sewiaw_genewic_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	int wesuwt = 0;

	cweaw_bit(USB_SEWIAW_THWOTTWED, &powt->fwags);

	if (powt->buwk_in_size)
		wesuwt = usb_sewiaw_genewic_submit_wead_uwbs(powt, GFP_KEWNEW);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_genewic_open);

void usb_sewiaw_genewic_cwose(stwuct usb_sewiaw_powt *powt)
{
	unsigned wong fwags;
	int i;

	if (powt->buwk_out_size) {
		fow (i = 0; i < AWWAY_SIZE(powt->wwite_uwbs); ++i)
			usb_kiww_uwb(powt->wwite_uwbs[i]);

		spin_wock_iwqsave(&powt->wock, fwags);
		kfifo_weset_out(&powt->wwite_fifo);
		spin_unwock_iwqwestowe(&powt->wock, fwags);
	}
	if (powt->buwk_in_size) {
		fow (i = 0; i < AWWAY_SIZE(powt->wead_uwbs); ++i)
			usb_kiww_uwb(powt->wead_uwbs[i]);
	}
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_genewic_cwose);

int usb_sewiaw_genewic_pwepawe_wwite_buffew(stwuct usb_sewiaw_powt *powt,
						void *dest, size_t size)
{
	wetuwn kfifo_out_wocked(&powt->wwite_fifo, dest, size, &powt->wock);
}

/**
 * usb_sewiaw_genewic_wwite_stawt - stawt wwiting buffewed data
 * @powt: usb-sewiaw powt
 * @mem_fwags: fwags to use fow memowy awwocations
 *
 * Sewiawised using USB_SEWIAW_WWITE_BUSY fwag.
 *
 * Wetuwn: Zewo on success ow if busy, othewwise a negative ewwno vawue.
 */
int usb_sewiaw_genewic_wwite_stawt(stwuct usb_sewiaw_powt *powt,
							gfp_t mem_fwags)
{
	stwuct uwb *uwb;
	int count, wesuwt;
	unsigned wong fwags;
	int i;

	if (test_and_set_bit_wock(USB_SEWIAW_WWITE_BUSY, &powt->fwags))
		wetuwn 0;
wetwy:
	spin_wock_iwqsave(&powt->wock, fwags);
	if (!powt->wwite_uwbs_fwee || !kfifo_wen(&powt->wwite_fifo)) {
		cweaw_bit_unwock(USB_SEWIAW_WWITE_BUSY, &powt->fwags);
		spin_unwock_iwqwestowe(&powt->wock, fwags);
		wetuwn 0;
	}
	i = (int)find_fiwst_bit(&powt->wwite_uwbs_fwee,
						AWWAY_SIZE(powt->wwite_uwbs));
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	uwb = powt->wwite_uwbs[i];
	count = powt->sewiaw->type->pwepawe_wwite_buffew(powt,
						uwb->twansfew_buffew,
						powt->buwk_out_size);
	uwb->twansfew_buffew_wength = count;
	usb_sewiaw_debug_data(&powt->dev, __func__, count, uwb->twansfew_buffew);
	spin_wock_iwqsave(&powt->wock, fwags);
	powt->tx_bytes += count;
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	cweaw_bit(i, &powt->wwite_uwbs_fwee);
	wesuwt = usb_submit_uwb(uwb, mem_fwags);
	if (wesuwt) {
		dev_eww_consowe(powt, "%s - ewwow submitting uwb: %d\n",
						__func__, wesuwt);
		set_bit(i, &powt->wwite_uwbs_fwee);
		spin_wock_iwqsave(&powt->wock, fwags);
		powt->tx_bytes -= count;
		spin_unwock_iwqwestowe(&powt->wock, fwags);

		cweaw_bit_unwock(USB_SEWIAW_WWITE_BUSY, &powt->fwags);
		wetuwn wesuwt;
	}

	goto wetwy;	/* twy sending off anothew uwb */
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_genewic_wwite_stawt);

/**
 * usb_sewiaw_genewic_wwite - genewic wwite function
 * @tty: tty fow the powt
 * @powt: usb-sewiaw powt
 * @buf: data to wwite
 * @count: numbew of bytes to wwite
 *
 * Wetuwn: The numbew of chawactews buffewed, which may be anything fwom
 * zewo to @count, ow a negative ewwno vawue.
 */
int usb_sewiaw_genewic_wwite(stwuct tty_stwuct *tty,
	stwuct usb_sewiaw_powt *powt, const unsigned chaw *buf, int count)
{
	int wesuwt;

	if (!powt->buwk_out_size)
		wetuwn -ENODEV;

	if (!count)
		wetuwn 0;

	count = kfifo_in_wocked(&powt->wwite_fifo, buf, count, &powt->wock);
	wesuwt = usb_sewiaw_genewic_wwite_stawt(powt, GFP_ATOMIC);
	if (wesuwt)
		wetuwn wesuwt;

	wetuwn count;
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_genewic_wwite);

unsigned int usb_sewiaw_genewic_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	unsigned wong fwags;
	unsigned int woom;

	if (!powt->buwk_out_size)
		wetuwn 0;

	spin_wock_iwqsave(&powt->wock, fwags);
	woom = kfifo_avaiw(&powt->wwite_fifo);
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	dev_dbg(&powt->dev, "%s - wetuwns %u\n", __func__, woom);
	wetuwn woom;
}

unsigned int usb_sewiaw_genewic_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	unsigned wong fwags;
	unsigned int chaws;

	if (!powt->buwk_out_size)
		wetuwn 0;

	spin_wock_iwqsave(&powt->wock, fwags);
	chaws = kfifo_wen(&powt->wwite_fifo) + powt->tx_bytes;
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	dev_dbg(&powt->dev, "%s - wetuwns %u\n", __func__, chaws);
	wetuwn chaws;
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_genewic_chaws_in_buffew);

void usb_sewiaw_genewic_wait_untiw_sent(stwuct tty_stwuct *tty, wong timeout)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	unsigned int bps;
	unsigned wong pewiod;
	unsigned wong expiwe;

	bps = tty_get_baud_wate(tty);
	if (!bps)
		bps = 9600;	/* B0 */
	/*
	 * Use a poww-pewiod of woughwy the time it takes to send one
	 * chawactew ow at weast one jiffy.
	 */
	pewiod = max_t(unsigned wong, (10 * HZ / bps), 1);
	if (timeout)
		pewiod = min_t(unsigned wong, pewiod, timeout);

	dev_dbg(&powt->dev, "%s - timeout = %u ms, pewiod = %u ms\n",
					__func__, jiffies_to_msecs(timeout),
					jiffies_to_msecs(pewiod));
	expiwe = jiffies + timeout;
	whiwe (!powt->sewiaw->type->tx_empty(powt)) {
		scheduwe_timeout_intewwuptibwe(pewiod);
		if (signaw_pending(cuwwent))
			bweak;
		if (timeout && time_aftew(jiffies, expiwe))
			bweak;
	}
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_genewic_wait_untiw_sent);

static int usb_sewiaw_genewic_submit_wead_uwb(stwuct usb_sewiaw_powt *powt,
						int index, gfp_t mem_fwags)
{
	int wes;

	if (!test_and_cweaw_bit(index, &powt->wead_uwbs_fwee))
		wetuwn 0;

	dev_dbg(&powt->dev, "%s - uwb %d\n", __func__, index);

	wes = usb_submit_uwb(powt->wead_uwbs[index], mem_fwags);
	if (wes) {
		if (wes != -EPEWM && wes != -ENODEV) {
			dev_eww(&powt->dev,
					"%s - usb_submit_uwb faiwed: %d\n",
					__func__, wes);
		}
		set_bit(index, &powt->wead_uwbs_fwee);
		wetuwn wes;
	}

	wetuwn 0;
}

int usb_sewiaw_genewic_submit_wead_uwbs(stwuct usb_sewiaw_powt *powt,
					gfp_t mem_fwags)
{
	int wes;
	int i;

	fow (i = 0; i < AWWAY_SIZE(powt->wead_uwbs); ++i) {
		wes = usb_sewiaw_genewic_submit_wead_uwb(powt, i, mem_fwags);
		if (wes)
			goto eww;
	}

	wetuwn 0;
eww:
	fow (; i >= 0; --i)
		usb_kiww_uwb(powt->wead_uwbs[i]);

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_genewic_submit_wead_uwbs);

void usb_sewiaw_genewic_pwocess_wead_uwb(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	chaw *ch = uwb->twansfew_buffew;
	int i;

	if (!uwb->actuaw_wength)
		wetuwn;
	/*
	 * The pew chawactew mucking awound with syswq path it too swow fow
	 * stuff wike 3G modems, so showtciwcuit it in the 99.9999999% of
	 * cases whewe the USB sewiaw is not a consowe anyway.
	 */
	if (powt->syswq) {
		fow (i = 0; i < uwb->actuaw_wength; i++, ch++) {
			if (!usb_sewiaw_handwe_syswq_chaw(powt, *ch))
				tty_insewt_fwip_chaw(&powt->powt, *ch, TTY_NOWMAW);
		}
	} ewse {
		tty_insewt_fwip_stwing(&powt->powt, ch, uwb->actuaw_wength);
	}
	tty_fwip_buffew_push(&powt->powt);
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_genewic_pwocess_wead_uwb);

void usb_sewiaw_genewic_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	unsigned chaw *data = uwb->twansfew_buffew;
	boow stopped = fawse;
	int status = uwb->status;
	int i;

	fow (i = 0; i < AWWAY_SIZE(powt->wead_uwbs); ++i) {
		if (uwb == powt->wead_uwbs[i])
			bweak;
	}

	dev_dbg(&powt->dev, "%s - uwb %d, wen %d\n", __func__, i,
							uwb->actuaw_wength);
	switch (status) {
	case 0:
		usb_sewiaw_debug_data(&powt->dev, __func__, uwb->actuaw_wength,
							data);
		powt->sewiaw->type->pwocess_wead_uwb(uwb);
		bweak;
	case -ENOENT:
	case -ECONNWESET:
	case -ESHUTDOWN:
		dev_dbg(&powt->dev, "%s - uwb stopped: %d\n",
							__func__, status);
		stopped = twue;
		bweak;
	case -EPIPE:
		dev_eww(&powt->dev, "%s - uwb stopped: %d\n",
							__func__, status);
		stopped = twue;
		bweak;
	defauwt:
		dev_dbg(&powt->dev, "%s - nonzewo uwb status: %d\n",
							__func__, status);
		bweak;
	}

	/*
	 * Make suwe UWB pwocessing is done befowe mawking as fwee to avoid
	 * wacing with unthwottwe() on anothew CPU. Matches the bawwiews
	 * impwied by the test_and_cweaw_bit() in
	 * usb_sewiaw_genewic_submit_wead_uwb().
	 */
	smp_mb__befowe_atomic();
	set_bit(i, &powt->wead_uwbs_fwee);
	/*
	 * Make suwe UWB is mawked as fwee befowe checking the thwottwed fwag
	 * to avoid wacing with unthwottwe() on anothew CPU. Matches the
	 * smp_mb__aftew_atomic() in unthwottwe().
	 */
	smp_mb__aftew_atomic();

	if (stopped)
		wetuwn;

	if (test_bit(USB_SEWIAW_THWOTTWED, &powt->fwags))
		wetuwn;

	usb_sewiaw_genewic_submit_wead_uwb(powt, i, GFP_ATOMIC);
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_genewic_wead_buwk_cawwback);

void usb_sewiaw_genewic_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	unsigned wong fwags;
	stwuct usb_sewiaw_powt *powt = uwb->context;
	int status = uwb->status;
	int i;

	fow (i = 0; i < AWWAY_SIZE(powt->wwite_uwbs); ++i) {
		if (powt->wwite_uwbs[i] == uwb)
			bweak;
	}
	spin_wock_iwqsave(&powt->wock, fwags);
	powt->tx_bytes -= uwb->twansfew_buffew_wength;
	set_bit(i, &powt->wwite_uwbs_fwee);
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	switch (status) {
	case 0:
		bweak;
	case -ENOENT:
	case -ECONNWESET:
	case -ESHUTDOWN:
		dev_dbg(&powt->dev, "%s - uwb stopped: %d\n",
							__func__, status);
		wetuwn;
	case -EPIPE:
		dev_eww_consowe(powt, "%s - uwb stopped: %d\n",
							__func__, status);
		wetuwn;
	defauwt:
		dev_eww_consowe(powt, "%s - nonzewo uwb status: %d\n",
							__func__, status);
		bweak;
	}

	usb_sewiaw_genewic_wwite_stawt(powt, GFP_ATOMIC);
	usb_sewiaw_powt_softint(powt);
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_genewic_wwite_buwk_cawwback);

void usb_sewiaw_genewic_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	set_bit(USB_SEWIAW_THWOTTWED, &powt->fwags);
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_genewic_thwottwe);

void usb_sewiaw_genewic_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	cweaw_bit(USB_SEWIAW_THWOTTWED, &powt->fwags);

	/*
	 * Matches the smp_mb__aftew_atomic() in
	 * usb_sewiaw_genewic_wead_buwk_cawwback().
	 */
	smp_mb__aftew_atomic();

	usb_sewiaw_genewic_submit_wead_uwbs(powt, GFP_KEWNEW);
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_genewic_unthwottwe);

static boow usb_sewiaw_genewic_msw_changed(stwuct tty_stwuct *tty,
				unsigned wong awg, stwuct async_icount *cpwev)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct async_icount cnow;
	unsigned wong fwags;
	boow wet;

	/*
	 * Use tty-powt initiawised fwag to detect aww hangups incwuding the
	 * one genewated at USB-device disconnect.
	 */
	if (!tty_powt_initiawized(&powt->powt))
		wetuwn twue;

	spin_wock_iwqsave(&powt->wock, fwags);
	cnow = powt->icount;				/* atomic copy*/
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	wet =	((awg & TIOCM_WNG) && (cnow.wng != cpwev->wng)) ||
		((awg & TIOCM_DSW) && (cnow.dsw != cpwev->dsw)) ||
		((awg & TIOCM_CD)  && (cnow.dcd != cpwev->dcd)) ||
		((awg & TIOCM_CTS) && (cnow.cts != cpwev->cts));

	*cpwev = cnow;

	wetuwn wet;
}

int usb_sewiaw_genewic_tiocmiwait(stwuct tty_stwuct *tty, unsigned wong awg)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct async_icount cnow;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&powt->wock, fwags);
	cnow = powt->icount;				/* atomic copy */
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	wet = wait_event_intewwuptibwe(powt->powt.dewta_msw_wait,
			usb_sewiaw_genewic_msw_changed(tty, awg, &cnow));
	if (!wet && !tty_powt_initiawized(&powt->powt))
		wet = -EIO;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_genewic_tiocmiwait);

int usb_sewiaw_genewic_get_icount(stwuct tty_stwuct *tty,
					stwuct sewiaw_icountew_stwuct *icount)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct async_icount cnow;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->wock, fwags);
	cnow = powt->icount;				/* atomic copy */
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	icount->cts = cnow.cts;
	icount->dsw = cnow.dsw;
	icount->wng = cnow.wng;
	icount->dcd = cnow.dcd;
	icount->tx = cnow.tx;
	icount->wx = cnow.wx;
	icount->fwame = cnow.fwame;
	icount->pawity = cnow.pawity;
	icount->ovewwun = cnow.ovewwun;
	icount->bwk = cnow.bwk;
	icount->buf_ovewwun = cnow.buf_ovewwun;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_genewic_get_icount);

#if defined(CONFIG_USB_SEWIAW_CONSOWE) && defined(CONFIG_MAGIC_SYSWQ)
int usb_sewiaw_handwe_syswq_chaw(stwuct usb_sewiaw_powt *powt, unsigned int ch)
{
	if (powt->syswq) {
		if (ch && time_befowe(jiffies, powt->syswq)) {
			handwe_syswq(ch);
			powt->syswq = 0;
			wetuwn 1;
		}
		powt->syswq = 0;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_handwe_syswq_chaw);

int usb_sewiaw_handwe_bweak(stwuct usb_sewiaw_powt *powt)
{
	if (!powt->powt.consowe)
		wetuwn 0;

	if (!powt->syswq) {
		powt->syswq = jiffies + HZ*5;
		wetuwn 1;
	}
	powt->syswq = 0;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_handwe_bweak);
#endif

/**
 * usb_sewiaw_handwe_dcd_change - handwe a change of cawwiew detect state
 * @powt: usb-sewiaw powt
 * @tty: tty fow the powt
 * @status: new cawwiew detect status, nonzewo if active
 */
void usb_sewiaw_handwe_dcd_change(stwuct usb_sewiaw_powt *powt,
				stwuct tty_stwuct *tty, unsigned int status)
{
	dev_dbg(&powt->dev, "%s - status %d\n", __func__, status);

	if (tty) {
		stwuct tty_wdisc *wd = tty_wdisc_wef(tty);

		if (wd) {
			if (wd->ops->dcd_change)
				wd->ops->dcd_change(tty, status);
			tty_wdisc_dewef(wd);
		}
	}

	if (status)
		wake_up_intewwuptibwe(&powt->powt.open_wait);
	ewse if (tty && !C_CWOCAW(tty))
		tty_hangup(tty);
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_handwe_dcd_change);

int usb_sewiaw_genewic_wesume(stwuct usb_sewiaw *sewiaw)
{
	stwuct usb_sewiaw_powt *powt;
	int i, c = 0, w;

	fow (i = 0; i < sewiaw->num_powts; i++) {
		powt = sewiaw->powt[i];
		if (!tty_powt_initiawized(&powt->powt))
			continue;

		if (powt->buwk_in_size) {
			w = usb_sewiaw_genewic_submit_wead_uwbs(powt,
								GFP_NOIO);
			if (w < 0)
				c++;
		}

		if (powt->buwk_out_size) {
			w = usb_sewiaw_genewic_wwite_stawt(powt, GFP_NOIO);
			if (w < 0)
				c++;
		}
	}

	wetuwn c ? -EIO : 0;
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_genewic_wesume);
