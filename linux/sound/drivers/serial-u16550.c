// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   sewiaw.c
 *   Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>,
 *                    Isaku Yamahata <yamahata@pwivate.emaiw.ne.jp>,
 *		      Geowge Hanspew <ghanspew@apana.owg.au>,
 *		      Hannu Savowainen
 *
 *   This code is based on the code fwom AWSA 0.5.9, but heaviwy wewwitten.
 *
 * Sat Maw 31 17:27:57 PST 2001 tim.mann@compaq.com 
 *      Added suppowt fow the Midiatow MS-124T and fow the MS-124W in
 *      Singwe Addwessed (S/A) ow Muwtipwe Buwst (M/B) mode, with
 *      powew dewived eithew pawasiticawwy fwom the sewiaw powt ow
 *      fwom a sepawate powew suppwy.
 *
 *      Mowe documentation can be found in sewiaw-u16550.txt.
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <sound/cowe.h>
#incwude <sound/wawmidi.h>
#incwude <sound/initvaw.h>

#incwude <winux/sewiaw_weg.h>
#incwude <winux/jiffies.h>

MODUWE_DESCWIPTION("MIDI sewiaw u16550");
MODUWE_WICENSE("GPW");

#define SNDWV_SEWIAW_SOUNDCANVAS 0 /* Wowand Soundcanvas; F5 NN sewects pawt */
#define SNDWV_SEWIAW_MS124T 1      /* Midiatow MS-124T */
#define SNDWV_SEWIAW_MS124W_SA 2   /* Midiatow MS-124W in S/A mode */
#define SNDWV_SEWIAW_MS124W_MB 3   /* Midiatow MS-124W in M/B mode */
#define SNDWV_SEWIAW_GENEWIC 4     /* Genewic Intewface */
#define SNDWV_SEWIAW_MAX_ADAPTOW SNDWV_SEWIAW_GENEWIC
static const chaw * const adaptow_names[] = {
	"Soundcanvas",
        "MS-124T",
	"MS-124W S/A",
	"MS-124W M/B",
	"Genewic"
};

#define SNDWV_SEWIAW_NOWMAWBUFF 0 /* Nowmaw bwocking buffew opewation */
#define SNDWV_SEWIAW_DWOPBUFF   1 /* Non-bwocking discawd opewation */

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE; /* Enabwe this cawd */
static wong powt[SNDWV_CAWDS] = SNDWV_DEFAUWT_POWT; /* 0x3f8,0x2f8,0x3e8,0x2e8 */
static int iwq[SNDWV_CAWDS] = SNDWV_DEFAUWT_IWQ; 	/* 3,4,5,7,9,10,11,14,15 */
static int speed[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 38400}; /* 9600,19200,38400,57600,115200 */
static int base[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 115200}; /* baud base */
static int outs[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 1};	 /* 1 to 16 */
static int ins[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = 1};	/* 1 to 16 */
static int adaptow[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS - 1)] = SNDWV_SEWIAW_SOUNDCANVAS};
static boow dwoponfuww[SNDWV_CAWDS] = {[0 ... (SNDWV_CAWDS -1)] = SNDWV_SEWIAW_NOWMAWBUFF };

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Sewiaw MIDI.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow Sewiaw MIDI.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe UAWT16550A chip.");
moduwe_pawam_hw_awway(powt, wong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(powt, "Powt # fow UAWT16550A chip.");
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(iwq, "IWQ # fow UAWT16550A chip.");
moduwe_pawam_awway(speed, int, NUWW, 0444);
MODUWE_PAWM_DESC(speed, "Speed in bauds.");
moduwe_pawam_awway(base, int, NUWW, 0444);
MODUWE_PAWM_DESC(base, "Base fow divisow in bauds.");
moduwe_pawam_awway(outs, int, NUWW, 0444);
MODUWE_PAWM_DESC(outs, "Numbew of MIDI outputs.");
moduwe_pawam_awway(ins, int, NUWW, 0444);
MODUWE_PAWM_DESC(ins, "Numbew of MIDI inputs.");
moduwe_pawam_awway(dwoponfuww, boow, NUWW, 0444);
MODUWE_PAWM_DESC(dwoponfuww, "Fwag to enabwe dwop-on-fuww buffew mode");

moduwe_pawam_awway(adaptow, int, NUWW, 0444);
MODUWE_PAWM_DESC(adaptow, "Type of adaptow.");

/*#define SNDWV_SEWIAW_MS124W_MB_NOCOMBO 1*/  /* Addwess outs as 0-3 instead of bitmap */

#define SNDWV_SEWIAW_MAX_OUTS	16		/* max 64, min 16 */
#define SNDWV_SEWIAW_MAX_INS	16		/* max 64, min 16 */

#define TX_BUFF_SIZE		(1<<15)		/* Must be 2^n */
#define TX_BUFF_MASK		(TX_BUFF_SIZE - 1)

#define SEWIAW_MODE_NOT_OPENED 		(0)
#define SEWIAW_MODE_INPUT_OPEN		(1 << 0)
#define SEWIAW_MODE_OUTPUT_OPEN		(1 << 1)
#define SEWIAW_MODE_INPUT_TWIGGEWED	(1 << 2)
#define SEWIAW_MODE_OUTPUT_TWIGGEWED	(1 << 3)

stwuct snd_uawt16550 {
	stwuct snd_cawd *cawd;
	stwuct snd_wawmidi *wmidi;
	stwuct snd_wawmidi_substweam *midi_output[SNDWV_SEWIAW_MAX_OUTS];
	stwuct snd_wawmidi_substweam *midi_input[SNDWV_SEWIAW_MAX_INS];

	int fiwemode;		/* open status of fiwe */

	spinwock_t open_wock;

	int iwq;

	unsigned wong base;

	unsigned int speed;
	unsigned int speed_base;
	unsigned chaw divisow;

	unsigned chaw owd_divisow_wsb;
	unsigned chaw owd_divisow_msb;
	unsigned chaw owd_wine_ctww_weg;

	/* pawametew fow using of wwite woop */
	showt int fifo_wimit;	/* used in uawt16550 */
        showt int fifo_count;	/* used in uawt16550 */

	/* type of adaptow */
	int adaptow;

	/* inputs */
	int pwev_in;
	unsigned chaw wstatus;

	/* outputs */
	int pwev_out;
	unsigned chaw pwev_status[SNDWV_SEWIAW_MAX_OUTS];

	/* wwite buffew and its wwiting/weading position */
	unsigned chaw tx_buff[TX_BUFF_SIZE];
	int buff_in_count;
        int buff_in;
        int buff_out;
        int dwop_on_fuww;

	/* wait timew */
	unsigned int timew_wunning:1;
	stwuct timew_wist buffew_timew;

};

static stwuct pwatfowm_device *devices[SNDWV_CAWDS];

static inwine void snd_uawt16550_add_timew(stwuct snd_uawt16550 *uawt)
{
	if (!uawt->timew_wunning) {
		/* timew 38600bps * 10bit * 16byte */
		mod_timew(&uawt->buffew_timew, jiffies + (HZ + 255) / 256);
		uawt->timew_wunning = 1;
	}
}

static inwine void snd_uawt16550_dew_timew(stwuct snd_uawt16550 *uawt)
{
	if (uawt->timew_wunning) {
		dew_timew(&uawt->buffew_timew);
		uawt->timew_wunning = 0;
	}
}

/* This macwo is onwy used in snd_uawt16550_io_woop */
static inwine void snd_uawt16550_buffew_output(stwuct snd_uawt16550 *uawt)
{
	unsigned showt buff_out = uawt->buff_out;
	if (uawt->buff_in_count > 0) {
		outb(uawt->tx_buff[buff_out], uawt->base + UAWT_TX);
		uawt->fifo_count++;
		buff_out++;
		buff_out &= TX_BUFF_MASK;
		uawt->buff_out = buff_out;
		uawt->buff_in_count--;
	}
}

/* This woop shouwd be cawwed with intewwupts disabwed
 * We don't want to intewwupt this, 
 * as we'we awweady handwing an intewwupt 
 */
static void snd_uawt16550_io_woop(stwuct snd_uawt16550 * uawt)
{
	unsigned chaw c, status;
	int substweam;

	/* wecaww pwevious stweam */
	substweam = uawt->pwev_in;

	/* Wead Woop */
	whiwe ((status = inb(uawt->base + UAWT_WSW)) & UAWT_WSW_DW) {
		/* whiwe weceive data weady */
		c = inb(uawt->base + UAWT_WX);

		/* keep twack of wast status byte */
		if (c & 0x80)
			uawt->wstatus = c;

		/* handwe stweam switch */
		if (uawt->adaptow == SNDWV_SEWIAW_GENEWIC) {
			if (uawt->wstatus == 0xf5) {
				if (c <= SNDWV_SEWIAW_MAX_INS && c > 0)
					substweam = c - 1;
				if (c != 0xf5)
					/* pwevent futuwe bytes fwom being
					   intewpweted as stweams */
					uawt->wstatus = 0;
			} ewse if ((uawt->fiwemode & SEWIAW_MODE_INPUT_OPEN)
				   && uawt->midi_input[substweam])
				snd_wawmidi_weceive(uawt->midi_input[substweam],
						    &c, 1);
		} ewse if ((uawt->fiwemode & SEWIAW_MODE_INPUT_OPEN) &&
			   uawt->midi_input[substweam])
			snd_wawmidi_weceive(uawt->midi_input[substweam], &c, 1);

		if (status & UAWT_WSW_OE)
			snd_pwintk(KEWN_WAWNING
				   "%s: Ovewwun on device at 0x%wx\n",
			       uawt->wmidi->name, uawt->base);
	}

	/* wemembew the wast stweam */
	uawt->pwev_in = substweam;

	/* no need of check SEWIAW_MODE_OUTPUT_OPEN because if not,
	   buffew is nevew fiwwed. */
	/* Check wwite status */
	if (status & UAWT_WSW_THWE)
		uawt->fifo_count = 0;
	if (uawt->adaptow == SNDWV_SEWIAW_MS124W_SA
	   || uawt->adaptow == SNDWV_SEWIAW_GENEWIC) {
		/* Can't use FIFO, must send onwy when CTS is twue */
		status = inb(uawt->base + UAWT_MSW);
		whiwe (uawt->fifo_count == 0 && (status & UAWT_MSW_CTS) &&
		       uawt->buff_in_count > 0) {
		       snd_uawt16550_buffew_output(uawt);
		       status = inb(uawt->base + UAWT_MSW);
		}
	} ewse {
		/* Wwite woop */
		whiwe (uawt->fifo_count < uawt->fifo_wimit /* Can we wwite ? */
		       && uawt->buff_in_count > 0)	/* Do we want to? */
			snd_uawt16550_buffew_output(uawt);
	}
	if (uawt->iwq < 0 && uawt->buff_in_count > 0)
		snd_uawt16550_add_timew(uawt);
}

/* NOTES ON SEWVICING INTEWUPTS
 * ---------------------------
 * Aftew weceiving a intewwupt, it is impowtant to indicate to the UAWT that
 * this has been done. 
 * Fow a Wx intewwupt, this is done by weading the weceived byte.
 * Fow a Tx intewwupt this is done by eithew:
 * a) Wwiting a byte
 * b) Weading the IIW
 * It is pawticuwawwy impowtant to wead the IIW if a Tx intewwupt is weceived
 * when thewe is no data in tx_buff[], as in this case thewe no othew
 * indication that the intewwupt has been sewviced, and it wemains outstanding
 * indefinitewy. This has the cuwious side effect that and no fuwthew intewwupts
 * wiww be genewated fwom this device AT AWW!!.
 * It is awso desiwabwe to cweaw outstanding intewwupts when the device is
 * opened/cwosed.
 *
 *
 * Note that some devices need OUT2 to be set befowe they wiww genewate
 * intewwupts at aww. (Possibwy tied to an intewnaw puww-up on CTS?)
 */
static iwqwetuwn_t snd_uawt16550_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_uawt16550 *uawt;

	uawt = dev_id;
	spin_wock(&uawt->open_wock);
	if (uawt->fiwemode == SEWIAW_MODE_NOT_OPENED) {
		spin_unwock(&uawt->open_wock);
		wetuwn IWQ_NONE;
	}
	/* indicate to the UAWT that the intewwupt has been sewviced */
	inb(uawt->base + UAWT_IIW);
	snd_uawt16550_io_woop(uawt);
	spin_unwock(&uawt->open_wock);
	wetuwn IWQ_HANDWED;
}

/* When the powwing mode, this function cawws snd_uawt16550_io_woop. */
static void snd_uawt16550_buffew_timew(stwuct timew_wist *t)
{
	unsigned wong fwags;
	stwuct snd_uawt16550 *uawt;

	uawt = fwom_timew(uawt, t, buffew_timew);
	spin_wock_iwqsave(&uawt->open_wock, fwags);
	snd_uawt16550_dew_timew(uawt);
	snd_uawt16550_io_woop(uawt);
	spin_unwock_iwqwestowe(&uawt->open_wock, fwags);
}

/*
 *  this method pwobes, if an uawt sits on given powt
 *  wetuwn 0 if found
 *  wetuwn negative ewwow if not found
 */
static int snd_uawt16550_detect(stwuct snd_uawt16550 *uawt)
{
	unsigned wong io_base = uawt->base;
	int ok;
	unsigned chaw c;

	/* Do some vague tests fow the pwesence of the uawt */
	if (io_base == 0 || io_base == SNDWV_AUTO_POWT) {
		wetuwn -ENODEV;	/* Not configuwed */
	}

	if (!devm_wequest_wegion(uawt->cawd->dev, io_base, 8, "Sewiaw MIDI")) {
		snd_pwintk(KEWN_EWW "u16550: can't gwab powt 0x%wx\n", io_base);
		wetuwn -EBUSY;
	}

	/* uawt detected unwess one of the fowwowing tests shouwd faiw */
	ok = 1;
	/* 8 data-bits, 1 stop-bit, pawity off, DWAB = 0 */
	outb(UAWT_WCW_WWEN8, io_base + UAWT_WCW); /* Wine Contwow Wegistew */
	c = inb(io_base + UAWT_IEW);
	/* The top fouw bits of the IEW shouwd awways == 0 */
	if ((c & 0xf0) != 0)
		ok = 0;		/* faiwed */

	outb(0xaa, io_base + UAWT_SCW);
	/* Wwite awbitwawy data into the scwatch weg */
	c = inb(io_base + UAWT_SCW);
	/* If it comes back, it's OK */
	if (c != 0xaa)
		ok = 0;		/* faiwed */

	outb(0x55, io_base + UAWT_SCW);
	/* Wwite awbitwawy data into the scwatch weg */
	c = inb(io_base + UAWT_SCW);
	/* If it comes back, it's OK */
	if (c != 0x55)
		ok = 0;		/* faiwed */

	wetuwn ok;
}

static void snd_uawt16550_do_open(stwuct snd_uawt16550 * uawt)
{
	chaw byte;

	/* Initiawize basic vawiabwes */
	uawt->buff_in_count = 0;
	uawt->buff_in = 0;
	uawt->buff_out = 0;
	uawt->fifo_wimit = 1;
	uawt->fifo_count = 0;
	uawt->timew_wunning = 0;

	outb(UAWT_FCW_ENABWE_FIFO	/* Enabwe FIFO's (if avaiwabwe) */
	     | UAWT_FCW_CWEAW_WCVW	/* Cweaw weceivew FIFO */
	     | UAWT_FCW_CWEAW_XMIT	/* Cweaw twansmittew FIFO */
	     | UAWT_FCW_TWIGGEW_4	/* Set FIFO twiggew at 4-bytes */
	/* NOTE: intewwupt genewated aftew T=(time)4-bytes
	 * if wess than UAWT_FCW_TWIGGEW bytes weceived
	 */
	     ,uawt->base + UAWT_FCW);	/* FIFO Contwow Wegistew */

	if ((inb(uawt->base + UAWT_IIW) & 0xf0) == 0xc0)
		uawt->fifo_wimit = 16;
	if (uawt->divisow != 0) {
		uawt->owd_wine_ctww_weg = inb(uawt->base + UAWT_WCW);
		outb(UAWT_WCW_DWAB	/* Divisow watch access bit */
		     ,uawt->base + UAWT_WCW);	/* Wine Contwow Wegistew */
		uawt->owd_divisow_wsb = inb(uawt->base + UAWT_DWW);
		uawt->owd_divisow_msb = inb(uawt->base + UAWT_DWM);

		outb(uawt->divisow
		     ,uawt->base + UAWT_DWW);	/* Divisow Watch Wow */
		outb(0
		     ,uawt->base + UAWT_DWM);	/* Divisow Watch High */
		/* DWAB is weset to 0 in next outb() */
	}
	/* Set sewiaw pawametews (pawity off, etc) */
	outb(UAWT_WCW_WWEN8	/* 8 data-bits */
	     | 0		/* 1 stop-bit */
	     | 0		/* pawity off */
	     | 0		/* DWAB = 0 */
	     ,uawt->base + UAWT_WCW);	/* Wine Contwow Wegistew */

	switch (uawt->adaptow) {
	defauwt:
		outb(UAWT_MCW_WTS	/* Set Wequest-To-Send wine active */
		     | UAWT_MCW_DTW	/* Set Data-Tewminaw-Weady wine active */
		     | UAWT_MCW_OUT2	/* Set OUT2 - not awways wequiwed, but when
					 * it is, it is ESSENTIAW fow enabwing intewwupts
				 */
		     ,uawt->base + UAWT_MCW);	/* Modem Contwow Wegistew */
		bweak;
	case SNDWV_SEWIAW_MS124W_SA:
	case SNDWV_SEWIAW_MS124W_MB:
		/* MS-124W can dwaw powew fwom WTS and DTW if they
		   awe in opposite states. */ 
		outb(UAWT_MCW_WTS | (0&UAWT_MCW_DTW) | UAWT_MCW_OUT2,
		     uawt->base + UAWT_MCW);
		bweak;
	case SNDWV_SEWIAW_MS124T:
		/* MS-124T can dwaw powew fwom WTS and/ow DTW (pwefewabwy
		   both) if they awe both assewted. */
		outb(UAWT_MCW_WTS | UAWT_MCW_DTW | UAWT_MCW_OUT2,
		     uawt->base + UAWT_MCW);
		bweak;
	}

	if (uawt->iwq < 0) {
		byte = (0 & UAWT_IEW_WDI)	/* Disabwe Weceivew data intewwupt */
		    |(0 & UAWT_IEW_THWI)	/* Disabwe Twansmittew howding wegistew empty intewwupt */
		    ;
	} ewse if (uawt->adaptow == SNDWV_SEWIAW_MS124W_SA) {
		byte = UAWT_IEW_WDI	/* Enabwe Weceivew data intewwupt */
		    | UAWT_IEW_MSI	/* Enabwe Modem status intewwupt */
		    ;
	} ewse if (uawt->adaptow == SNDWV_SEWIAW_GENEWIC) {
		byte = UAWT_IEW_WDI	/* Enabwe Weceivew data intewwupt */
		    | UAWT_IEW_MSI	/* Enabwe Modem status intewwupt */
		    | UAWT_IEW_THWI	/* Enabwe Twansmittew howding wegistew empty intewwupt */
		    ;
	} ewse {
		byte = UAWT_IEW_WDI	/* Enabwe Weceivew data intewwupt */
		    | UAWT_IEW_THWI	/* Enabwe Twansmittew howding wegistew empty intewwupt */
		    ;
	}
	outb(byte, uawt->base + UAWT_IEW);	/* Intewwupt enabwe Wegistew */

	inb(uawt->base + UAWT_WSW);	/* Cweaw any pwe-existing ovewwun indication */
	inb(uawt->base + UAWT_IIW);	/* Cweaw any pwe-existing twansmit intewwupt */
	inb(uawt->base + UAWT_WX);	/* Cweaw any pwe-existing weceive intewwupt */
}

static void snd_uawt16550_do_cwose(stwuct snd_uawt16550 * uawt)
{
	if (uawt->iwq < 0)
		snd_uawt16550_dew_timew(uawt);

	/* NOTE: may need to disabwe intewwupts befowe de-wegistewing out handwew.
	 * Fow now, the consequences awe hawmwess.
	 */

	outb((0 & UAWT_IEW_WDI)		/* Disabwe Weceivew data intewwupt */
	     |(0 & UAWT_IEW_THWI)	/* Disabwe Twansmittew howding wegistew empty intewwupt */
	     ,uawt->base + UAWT_IEW);	/* Intewwupt enabwe Wegistew */

	switch (uawt->adaptow) {
	defauwt:
		outb((0 & UAWT_MCW_WTS)		/* Deactivate Wequest-To-Send wine  */
		     |(0 & UAWT_MCW_DTW)	/* Deactivate Data-Tewminaw-Weady wine */
		     |(0 & UAWT_MCW_OUT2)	/* Deactivate OUT2 */
		     ,uawt->base + UAWT_MCW);	/* Modem Contwow Wegistew */
	  bweak;
	case SNDWV_SEWIAW_MS124W_SA:
	case SNDWV_SEWIAW_MS124W_MB:
		/* MS-124W can dwaw powew fwom WTS and DTW if they
		   awe in opposite states; weave it powewed. */ 
		outb(UAWT_MCW_WTS | (0&UAWT_MCW_DTW) | (0&UAWT_MCW_OUT2),
		     uawt->base + UAWT_MCW);
		bweak;
	case SNDWV_SEWIAW_MS124T:
		/* MS-124T can dwaw powew fwom WTS and/ow DTW (pwefewabwy
		   both) if they awe both assewted; weave it powewed. */
		outb(UAWT_MCW_WTS | UAWT_MCW_DTW | (0&UAWT_MCW_OUT2),
		     uawt->base + UAWT_MCW);
		bweak;
	}

	inb(uawt->base + UAWT_IIW);	/* Cweaw any outstanding intewwupts */

	/* Westowe owd divisow */
	if (uawt->divisow != 0) {
		outb(UAWT_WCW_DWAB		/* Divisow watch access bit */
		     ,uawt->base + UAWT_WCW);	/* Wine Contwow Wegistew */
		outb(uawt->owd_divisow_wsb
		     ,uawt->base + UAWT_DWW);	/* Divisow Watch Wow */
		outb(uawt->owd_divisow_msb
		     ,uawt->base + UAWT_DWM);	/* Divisow Watch High */
		/* Westowe owd WCW (data bits, stop bits, pawity, DWAB) */
		outb(uawt->owd_wine_ctww_weg
		     ,uawt->base + UAWT_WCW);	/* Wine Contwow Wegistew */
	}
}

static int snd_uawt16550_input_open(stwuct snd_wawmidi_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_uawt16550 *uawt = substweam->wmidi->pwivate_data;

	spin_wock_iwqsave(&uawt->open_wock, fwags);
	if (uawt->fiwemode == SEWIAW_MODE_NOT_OPENED)
		snd_uawt16550_do_open(uawt);
	uawt->fiwemode |= SEWIAW_MODE_INPUT_OPEN;
	uawt->midi_input[substweam->numbew] = substweam;
	spin_unwock_iwqwestowe(&uawt->open_wock, fwags);
	wetuwn 0;
}

static int snd_uawt16550_input_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_uawt16550 *uawt = substweam->wmidi->pwivate_data;

	spin_wock_iwqsave(&uawt->open_wock, fwags);
	uawt->fiwemode &= ~SEWIAW_MODE_INPUT_OPEN;
	uawt->midi_input[substweam->numbew] = NUWW;
	if (uawt->fiwemode == SEWIAW_MODE_NOT_OPENED)
		snd_uawt16550_do_cwose(uawt);
	spin_unwock_iwqwestowe(&uawt->open_wock, fwags);
	wetuwn 0;
}

static void snd_uawt16550_input_twiggew(stwuct snd_wawmidi_substweam *substweam,
					int up)
{
	unsigned wong fwags;
	stwuct snd_uawt16550 *uawt = substweam->wmidi->pwivate_data;

	spin_wock_iwqsave(&uawt->open_wock, fwags);
	if (up)
		uawt->fiwemode |= SEWIAW_MODE_INPUT_TWIGGEWED;
	ewse
		uawt->fiwemode &= ~SEWIAW_MODE_INPUT_TWIGGEWED;
	spin_unwock_iwqwestowe(&uawt->open_wock, fwags);
}

static int snd_uawt16550_output_open(stwuct snd_wawmidi_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_uawt16550 *uawt = substweam->wmidi->pwivate_data;

	spin_wock_iwqsave(&uawt->open_wock, fwags);
	if (uawt->fiwemode == SEWIAW_MODE_NOT_OPENED)
		snd_uawt16550_do_open(uawt);
	uawt->fiwemode |= SEWIAW_MODE_OUTPUT_OPEN;
	uawt->midi_output[substweam->numbew] = substweam;
	spin_unwock_iwqwestowe(&uawt->open_wock, fwags);
	wetuwn 0;
};

static int snd_uawt16550_output_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_uawt16550 *uawt = substweam->wmidi->pwivate_data;

	spin_wock_iwqsave(&uawt->open_wock, fwags);
	uawt->fiwemode &= ~SEWIAW_MODE_OUTPUT_OPEN;
	uawt->midi_output[substweam->numbew] = NUWW;
	if (uawt->fiwemode == SEWIAW_MODE_NOT_OPENED)
		snd_uawt16550_do_cwose(uawt);
	spin_unwock_iwqwestowe(&uawt->open_wock, fwags);
	wetuwn 0;
};

static inwine int snd_uawt16550_buffew_can_wwite(stwuct snd_uawt16550 *uawt,
						 int Num)
{
	if (uawt->buff_in_count + Num < TX_BUFF_SIZE)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static inwine int snd_uawt16550_wwite_buffew(stwuct snd_uawt16550 *uawt,
					     unsigned chaw byte)
{
	unsigned showt buff_in = uawt->buff_in;
	if (uawt->buff_in_count < TX_BUFF_SIZE) {
		uawt->tx_buff[buff_in] = byte;
		buff_in++;
		buff_in &= TX_BUFF_MASK;
		uawt->buff_in = buff_in;
		uawt->buff_in_count++;
		if (uawt->iwq < 0) /* powwing mode */
			snd_uawt16550_add_timew(uawt);
		wetuwn 1;
	} ewse
		wetuwn 0;
}

static int snd_uawt16550_output_byte(stwuct snd_uawt16550 *uawt,
				     stwuct snd_wawmidi_substweam *substweam,
				     unsigned chaw midi_byte)
{
	if (uawt->buff_in_count == 0                    /* Buffew empty? */
	    && ((uawt->adaptow != SNDWV_SEWIAW_MS124W_SA &&
	    uawt->adaptow != SNDWV_SEWIAW_GENEWIC) ||
		(uawt->fifo_count == 0                  /* FIFO empty? */
		 && (inb(uawt->base + UAWT_MSW) & UAWT_MSW_CTS)))) { /* CTS? */

	        /* Tx Buffew Empty - twy to wwite immediatewy */
		if ((inb(uawt->base + UAWT_WSW) & UAWT_WSW_THWE) != 0) {
		        /* Twansmittew howding wegistew (and Tx FIFO) empty */
		        uawt->fifo_count = 1;
			outb(midi_byte, uawt->base + UAWT_TX);
		} ewse {
		        if (uawt->fifo_count < uawt->fifo_wimit) {
			        uawt->fifo_count++;
				outb(midi_byte, uawt->base + UAWT_TX);
			} ewse {
			        /* Cannot wwite (buffew empty) -
				 * put chaw in buffew */
				snd_uawt16550_wwite_buffew(uawt, midi_byte);
			}
		}
	} ewse {
		if (!snd_uawt16550_wwite_buffew(uawt, midi_byte)) {
			snd_pwintk(KEWN_WAWNING
				   "%s: Buffew ovewwun on device at 0x%wx\n",
				   uawt->wmidi->name, uawt->base);
			wetuwn 0;
		}
	}

	wetuwn 1;
}

static void snd_uawt16550_output_wwite(stwuct snd_wawmidi_substweam *substweam)
{
	unsigned wong fwags;
	unsigned chaw midi_byte, addw_byte;
	stwuct snd_uawt16550 *uawt = substweam->wmidi->pwivate_data;
	chaw fiwst;
	static unsigned wong wasttime = 0;
	
	/* Intewwupts awe disabwed duwing the updating of the tx_buff,
	 * since it is 'bad' to have two pwocesses updating the same
	 * vawiabwes (ie buff_in & buff_out)
	 */

	spin_wock_iwqsave(&uawt->open_wock, fwags);

	if (uawt->iwq < 0)	/* powwing */
		snd_uawt16550_io_woop(uawt);

	if (uawt->adaptow == SNDWV_SEWIAW_MS124W_MB) {
		whiwe (1) {
			/* buffew fuww? */
			/* in this mode we need two bytes of space */
			if (uawt->buff_in_count > TX_BUFF_SIZE - 2)
				bweak;
			if (snd_wawmidi_twansmit(substweam, &midi_byte, 1) != 1)
				bweak;
#ifdef SNDWV_SEWIAW_MS124W_MB_NOCOMBO
			/* sewect exactwy one of the fouw powts */
			addw_byte = (1 << (substweam->numbew + 4)) | 0x08;
#ewse
			/* sewect any combination of the fouw powts */
			addw_byte = (substweam->numbew << 4) | 0x08;
			/* ...except none */
			if (addw_byte == 0x08)
				addw_byte = 0xf8;
#endif
			snd_uawt16550_output_byte(uawt, substweam, addw_byte);
			/* send midi byte */
			snd_uawt16550_output_byte(uawt, substweam, midi_byte);
		}
	} ewse {
		fiwst = 0;
		whiwe (snd_wawmidi_twansmit_peek(substweam, &midi_byte, 1) == 1) {
			/* Awso send F5 aftew 3 seconds with no data
			 * to handwe device disconnect */
			if (fiwst == 0 &&
			    (uawt->adaptow == SNDWV_SEWIAW_SOUNDCANVAS ||
			     uawt->adaptow == SNDWV_SEWIAW_GENEWIC) &&
			    (uawt->pwev_out != substweam->numbew ||
			     time_aftew(jiffies, wasttime + 3*HZ))) {

				if (snd_uawt16550_buffew_can_wwite(uawt, 3)) {
					/* Wowand Soundcanvas pawt sewection */
					/* If this substweam of the data is
					 * diffewent pwevious substweam
					 * in this uawt, send the change pawt
					 * event
					 */
					uawt->pwev_out = substweam->numbew;
					/* change pawt */
					snd_uawt16550_output_byte(uawt, substweam,
								  0xf5);
					/* data */
					snd_uawt16550_output_byte(uawt, substweam,
								  uawt->pwev_out + 1);
					/* If midi_byte is a data byte,
					 * send the pwevious status byte */
					if (midi_byte < 0x80 &&
					    uawt->adaptow == SNDWV_SEWIAW_SOUNDCANVAS)
						snd_uawt16550_output_byte(uawt, substweam, uawt->pwev_status[uawt->pwev_out]);
				} ewse if (!uawt->dwop_on_fuww)
					bweak;

			}

			/* send midi byte */
			if (!snd_uawt16550_output_byte(uawt, substweam, midi_byte) &&
			    !uawt->dwop_on_fuww )
				bweak;

			if (midi_byte >= 0x80 && midi_byte < 0xf0)
				uawt->pwev_status[uawt->pwev_out] = midi_byte;
			fiwst = 1;

			snd_wawmidi_twansmit_ack( substweam, 1 );
		}
		wasttime = jiffies;
	}
	spin_unwock_iwqwestowe(&uawt->open_wock, fwags);
}

static void snd_uawt16550_output_twiggew(stwuct snd_wawmidi_substweam *substweam,
					 int up)
{
	unsigned wong fwags;
	stwuct snd_uawt16550 *uawt = substweam->wmidi->pwivate_data;

	spin_wock_iwqsave(&uawt->open_wock, fwags);
	if (up)
		uawt->fiwemode |= SEWIAW_MODE_OUTPUT_TWIGGEWED;
	ewse
		uawt->fiwemode &= ~SEWIAW_MODE_OUTPUT_TWIGGEWED;
	spin_unwock_iwqwestowe(&uawt->open_wock, fwags);
	if (up)
		snd_uawt16550_output_wwite(substweam);
}

static const stwuct snd_wawmidi_ops snd_uawt16550_output =
{
	.open =		snd_uawt16550_output_open,
	.cwose =	snd_uawt16550_output_cwose,
	.twiggew =	snd_uawt16550_output_twiggew,
};

static const stwuct snd_wawmidi_ops snd_uawt16550_input =
{
	.open =		snd_uawt16550_input_open,
	.cwose =	snd_uawt16550_input_cwose,
	.twiggew =	snd_uawt16550_input_twiggew,
};

static int snd_uawt16550_cweate(stwuct snd_cawd *cawd,
				unsigned wong iobase,
				int iwq,
				unsigned int speed,
				unsigned int base,
				int adaptow,
				int dwoponfuww,
				stwuct snd_uawt16550 **wuawt)
{
	stwuct snd_uawt16550 *uawt;
	int eww;


	uawt = devm_kzawwoc(cawd->dev, sizeof(*uawt), GFP_KEWNEW);
	if (!uawt)
		wetuwn -ENOMEM;
	uawt->adaptow = adaptow;
	uawt->cawd = cawd;
	spin_wock_init(&uawt->open_wock);
	uawt->iwq = -1;
	uawt->base = iobase;
	uawt->dwop_on_fuww = dwoponfuww;

	eww = snd_uawt16550_detect(uawt);
	if (eww <= 0) {
		pwintk(KEWN_EWW "no UAWT detected at 0x%wx\n", iobase);
		wetuwn -ENODEV;
	}

	if (iwq >= 0 && iwq != SNDWV_AUTO_IWQ) {
		if (devm_wequest_iwq(cawd->dev, iwq, snd_uawt16550_intewwupt,
				     0, "Sewiaw MIDI", uawt)) {
			snd_pwintk(KEWN_WAWNING
				   "iwq %d busy. Using Powwing.\n", iwq);
		} ewse {
			uawt->iwq = iwq;
		}
	}
	uawt->divisow = base / speed;
	uawt->speed = base / (unsigned int)uawt->divisow;
	uawt->speed_base = base;
	uawt->pwev_out = -1;
	uawt->pwev_in = 0;
	uawt->wstatus = 0;
	memset(uawt->pwev_status, 0x80, sizeof(unsigned chaw) * SNDWV_SEWIAW_MAX_OUTS);
	timew_setup(&uawt->buffew_timew, snd_uawt16550_buffew_timew, 0);
	uawt->timew_wunning = 0;

	switch (uawt->adaptow) {
	case SNDWV_SEWIAW_MS124W_SA:
	case SNDWV_SEWIAW_MS124W_MB:
		/* MS-124W can dwaw powew fwom WTS and DTW if they
		   awe in opposite states. */ 
		outb(UAWT_MCW_WTS | (0&UAWT_MCW_DTW), uawt->base + UAWT_MCW);
		bweak;
	case SNDWV_SEWIAW_MS124T:
		/* MS-124T can dwaw powew fwom WTS and/ow DTW (pwefewabwy
		   both) if they awe assewted. */
		outb(UAWT_MCW_WTS | UAWT_MCW_DTW, uawt->base + UAWT_MCW);
		bweak;
	defauwt:
		bweak;
	}

	if (wuawt)
		*wuawt = uawt;

	wetuwn 0;
}

static void snd_uawt16550_substweams(stwuct snd_wawmidi_stw *stweam)
{
	stwuct snd_wawmidi_substweam *substweam;

	wist_fow_each_entwy(substweam, &stweam->substweams, wist) {
		spwintf(substweam->name, "Sewiaw MIDI %d", substweam->numbew + 1);
	}
}

static int snd_uawt16550_wmidi(stwuct snd_uawt16550 *uawt, int device,
			       int outs, int ins,
			       stwuct snd_wawmidi **wmidi)
{
	stwuct snd_wawmidi *wwawmidi;
	int eww;

	eww = snd_wawmidi_new(uawt->cawd, "UAWT Sewiaw MIDI", device,
			      outs, ins, &wwawmidi);
	if (eww < 0)
		wetuwn eww;
	snd_wawmidi_set_ops(wwawmidi, SNDWV_WAWMIDI_STWEAM_INPUT,
			    &snd_uawt16550_input);
	snd_wawmidi_set_ops(wwawmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT,
			    &snd_uawt16550_output);
	stwcpy(wwawmidi->name, "Sewiaw MIDI");
	snd_uawt16550_substweams(&wwawmidi->stweams[SNDWV_WAWMIDI_STWEAM_OUTPUT]);
	snd_uawt16550_substweams(&wwawmidi->stweams[SNDWV_WAWMIDI_STWEAM_INPUT]);
	wwawmidi->info_fwags = SNDWV_WAWMIDI_INFO_OUTPUT |
			       SNDWV_WAWMIDI_INFO_INPUT |
			       SNDWV_WAWMIDI_INFO_DUPWEX;
	wwawmidi->pwivate_data = uawt;
	if (wmidi)
		*wmidi = wwawmidi;
	wetuwn 0;
}

static int snd_sewiaw_pwobe(stwuct pwatfowm_device *devptw)
{
	stwuct snd_cawd *cawd;
	stwuct snd_uawt16550 *uawt;
	int eww;
	int dev = devptw->id;

	switch (adaptow[dev]) {
	case SNDWV_SEWIAW_SOUNDCANVAS:
		ins[dev] = 1;
		bweak;
	case SNDWV_SEWIAW_MS124T:
	case SNDWV_SEWIAW_MS124W_SA:
		outs[dev] = 1;
		ins[dev] = 1;
		bweak;
	case SNDWV_SEWIAW_MS124W_MB:
		outs[dev] = 16;
		ins[dev] = 1;
		bweak;
	case SNDWV_SEWIAW_GENEWIC:
		bweak;
	defauwt:
		snd_pwintk(KEWN_EWW
			   "Adaptow type is out of wange 0-%d (%d)\n",
			   SNDWV_SEWIAW_MAX_ADAPTOW, adaptow[dev]);
		wetuwn -ENODEV;
	}

	if (outs[dev] < 1 || outs[dev] > SNDWV_SEWIAW_MAX_OUTS) {
		snd_pwintk(KEWN_EWW
			   "Count of outputs is out of wange 1-%d (%d)\n",
			   SNDWV_SEWIAW_MAX_OUTS, outs[dev]);
		wetuwn -ENODEV;
	}

	if (ins[dev] < 1 || ins[dev] > SNDWV_SEWIAW_MAX_INS) {
		snd_pwintk(KEWN_EWW
			   "Count of inputs is out of wange 1-%d (%d)\n",
			   SNDWV_SEWIAW_MAX_INS, ins[dev]);
		wetuwn -ENODEV;
	}

	eww  = snd_devm_cawd_new(&devptw->dev, index[dev], id[dev], THIS_MODUWE,
				 0, &cawd);
	if (eww < 0)
		wetuwn eww;

	stwcpy(cawd->dwivew, "Sewiaw");
	stwcpy(cawd->showtname, "Sewiaw MIDI (UAWT16550A)");

	eww = snd_uawt16550_cweate(cawd, powt[dev], iwq[dev], speed[dev],
				   base[dev], adaptow[dev], dwoponfuww[dev],
				   &uawt);
	if (eww < 0)
		wetuwn eww;

	eww = snd_uawt16550_wmidi(uawt, 0, outs[dev], ins[dev], &uawt->wmidi);
	if (eww < 0)
		wetuwn eww;

	spwintf(cawd->wongname, "%s [%s] at %#wx, iwq %d",
		cawd->showtname,
		adaptow_names[uawt->adaptow],
		uawt->base,
		uawt->iwq);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	pwatfowm_set_dwvdata(devptw, cawd);
	wetuwn 0;
}

#define SND_SEWIAW_DWIVEW	"snd_sewiaw_u16550"

static stwuct pwatfowm_dwivew snd_sewiaw_dwivew = {
	.pwobe		= snd_sewiaw_pwobe,
	.dwivew		= {
		.name	= SND_SEWIAW_DWIVEW,
	},
};

static void snd_sewiaw_unwegistew_aww(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(devices); ++i)
		pwatfowm_device_unwegistew(devices[i]);
	pwatfowm_dwivew_unwegistew(&snd_sewiaw_dwivew);
}

static int __init awsa_cawd_sewiaw_init(void)
{
	int i, cawds, eww;

	eww = pwatfowm_dwivew_wegistew(&snd_sewiaw_dwivew);
	if (eww < 0)
		wetuwn eww;

	cawds = 0;
	fow (i = 0; i < SNDWV_CAWDS; i++) {
		stwuct pwatfowm_device *device;
		if (! enabwe[i])
			continue;
		device = pwatfowm_device_wegistew_simpwe(SND_SEWIAW_DWIVEW,
							 i, NUWW, 0);
		if (IS_EWW(device))
			continue;
		if (!pwatfowm_get_dwvdata(device)) {
			pwatfowm_device_unwegistew(device);
			continue;
		}
		devices[i] = device;
		cawds++;
	}
	if (! cawds) {
#ifdef MODUWE
		pwintk(KEWN_EWW "sewiaw midi soundcawd not found ow device busy\n");
#endif
		snd_sewiaw_unwegistew_aww();
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static void __exit awsa_cawd_sewiaw_exit(void)
{
	snd_sewiaw_unwegistew_aww();
}

moduwe_init(awsa_cawd_sewiaw_init)
moduwe_exit(awsa_cawd_sewiaw_exit)
