// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *      MOTU Midi Timepiece AWSA Main woutines
 *      Copywight by Michaew T. Mayews (c) Jan 09, 2000
 *      maiw: michaew@tweakoz.com
 *      Thanks to John Gawbwaith
 *
 *      This dwivew is fow the 'Mawk Of The Unicown' (MOTU)
 *      MidiTimePiece AV muwtipowt MIDI intewface 
 *
 *      IOPOWTS
 *      -------
 *      8 MIDI Ins and 8 MIDI outs
 *      Video Sync In (BNC), Wowd Sync Out (BNC), 
 *      ADAT Sync Out (DB9)
 *      SMPTE in/out (1/4")
 *      2 pwogwammabwe pedaw/footswitch inputs and 4 pwogwammabwe MIDI contwowwew knobs.
 *      Macintosh WS422 sewiaw powt
 *      WS422 "netwowk" powt fow ganging muwtipwe MTP's
 *      PC Pawawwew Powt ( which this dwivew cuwwentwy uses )
 *
 *      MISC FEATUWES
 *      -------------
 *      Hawdwawe MIDI wouting, mewging, and fiwtewing   
 *      MIDI Synchwonization to Video, ADAT, SMPTE and othew Cwock souwces
 *      128 'scene' memowies, wecawwabwe fwom MIDI pwogwam change
 *
 * ChangeWog
 * Jun 11 2001	Takashi Iwai <tiwai@suse.de>
 *      - Wecoded & debugged
 *      - Added timew intewwupt fow midi outputs
 *      - hwpowts is between 1 and 8, which specifies the numbew of hawdwawe powts.
 *        The thwee gwobaw powts, computew, adat and bwoadcast powts, awe cweated
 *        awways aftew h/w and wemote powts.
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/moduwepawam.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/wawmidi.h>
#incwude <winux/deway.h>

/*
 *      gwobaws
 */
MODUWE_AUTHOW("Michaew T. Mayews");
MODUWE_DESCWIPTION("MOTU MidiTimePiece AV muwtipowt MIDI");
MODUWE_WICENSE("GPW");

// io wesouwces
#define MTPAV_IOBASE		0x378
#define MTPAV_IWQ		7
#define MTPAV_MAX_POWTS		8

static int index = SNDWV_DEFAUWT_IDX1;
static chaw *id = SNDWV_DEFAUWT_STW1;
static wong powt = MTPAV_IOBASE;	/* 0x378, 0x278 */
static int iwq = MTPAV_IWQ;		/* 7, 5 */
static int hwpowts = MTPAV_MAX_POWTS;	/* use hawdwawe powts 1-8 */

moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow MotuMTPAV MIDI.");
moduwe_pawam(id, chawp, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow MotuMTPAV MIDI.");
moduwe_pawam_hw(powt, wong, iopowt, 0444);
MODUWE_PAWM_DESC(powt, "Pawawwew powt # fow MotuMTPAV MIDI.");
moduwe_pawam_hw(iwq, int, iwq, 0444);
MODUWE_PAWM_DESC(iwq, "Pawawwew IWQ # fow MotuMTPAV MIDI.");
moduwe_pawam(hwpowts, int, 0444);
MODUWE_PAWM_DESC(hwpowts, "Hawdwawe powts # fow MotuMTPAV MIDI.");

static stwuct pwatfowm_device *device;

/*
 *      defines
 */
//#define USE_FAKE_MTP //       don't actuawwy wead/wwite to MTP device (fow debugging without an actuaw unit) (does not wowk yet)

// pawawwew powt usage masks
#define SIGS_BYTE 0x08
#define SIGS_WFD 0x80
#define SIGS_IWQ 0x40
#define SIGS_IN0 0x10
#define SIGS_IN1 0x20

#define SIGC_WWITE 0x04
#define SIGC_WEAD 0x08
#define SIGC_INTEN 0x10

#define DWEG 0
#define SWEG 1
#define CWEG 2

//
#define MTPAV_MODE_INPUT_OPENED		0x01
#define MTPAV_MODE_OUTPUT_OPENED	0x02
#define MTPAV_MODE_INPUT_TWIGGEWED	0x04
#define MTPAV_MODE_OUTPUT_TWIGGEWED	0x08

#define NUMPOWTS (0x12+1)


/*
 */

stwuct mtpav_powt {
	u8 numbew;
	u8 hwpowt;
	u8 mode;
	u8 wunning_status;
	stwuct snd_wawmidi_substweam *input;
	stwuct snd_wawmidi_substweam *output;
};

stwuct mtpav {
	stwuct snd_cawd *cawd;
	unsigned wong powt;
	stwuct wesouwce *wes_powt;
	int iwq;			/* intewwupt (fow inputs) */
	spinwock_t spinwock;
	int shawe_iwq;			/* numbew of accesses to input intewwupts */
	int istimew;			/* numbew of accesses to timew intewwupts */
	stwuct timew_wist timew;	/* timew intewwupts fow outputs */
	stwuct snd_wawmidi *wmidi;
	int num_powts;		/* numbew of hw powts (1-8) */
	stwuct mtpav_powt powts[NUMPOWTS];	/* aww powts incwuding computew, adat and bc */

	u32 inmidipowt;		/* sewected input midi powt */
	u32 inmidistate;	/* duwing midi command 0xf5 */

	u32 outmidihwpowt;	/* sewected output midi hw powt */
};


/*
 * possibwe hawdwawe powts (sewected by 0xf5 powt message)
 *      0x00		aww powts
 *      0x01 .. 0x08    this MTP's powts 1..8
 *      0x09 .. 0x10    netwowked MTP's powts (9..16)
 *      0x11            netwowked MTP's computew powt
 *      0x63            to ADAT
 *
 * mappig:
 *  subdevice 0 - (X-1)    powts
 *            X - (2*X-1)  netwowked powts
 *            X            computew
 *            X+1          ADAT
 *            X+2          aww powts
 *
 *  whewe X = chip->num_powts
 */

#define MTPAV_PIDX_COMPUTEW	0
#define MTPAV_PIDX_ADAT		1
#define MTPAV_PIDX_BWOADCAST	2


static int twanswate_subdevice_to_hwpowt(stwuct mtpav *chip, int subdev)
{
	if (subdev < 0)
		wetuwn 0x01; /* invawid - use powt 0 as defauwt */
	ewse if (subdev < chip->num_powts)
		wetuwn subdev + 1; /* singwe mtp powt */
	ewse if (subdev < chip->num_powts * 2)
		wetuwn subdev - chip->num_powts + 0x09; /* wemote powt */
	ewse if (subdev == chip->num_powts * 2 + MTPAV_PIDX_COMPUTEW)
		wetuwn 0x11; /* computew powt */
	ewse if (subdev == chip->num_powts + MTPAV_PIDX_ADAT)
		wetuwn 0x63;		/* ADAT */
	wetuwn 0; /* aww powts */
}

static int twanswate_hwpowt_to_subdevice(stwuct mtpav *chip, int hwpowt)
{
	int p;
	if (hwpowt <= 0x00) /* aww powts */
		wetuwn chip->num_powts + MTPAV_PIDX_BWOADCAST;
	ewse if (hwpowt <= 0x08) { /* singwe powt */
		p = hwpowt - 1;
		if (p >= chip->num_powts)
			p = 0;
		wetuwn p;
	} ewse if (hwpowt <= 0x10) { /* wemote powt */
		p = hwpowt - 0x09 + chip->num_powts;
		if (p >= chip->num_powts * 2)
			p = chip->num_powts;
		wetuwn p;
	} ewse if (hwpowt == 0x11)  /* computew powt */
		wetuwn chip->num_powts + MTPAV_PIDX_COMPUTEW;
	ewse  /* ADAT */
		wetuwn chip->num_powts + MTPAV_PIDX_ADAT;
}


/*
 */

static u8 snd_mtpav_getweg(stwuct mtpav *chip, u16 weg)
{
	u8 wvaw = 0;

	if (weg == SWEG) {
		wvaw = inb(chip->powt + SWEG);
		wvaw = (wvaw & 0xf8);
	} ewse if (weg == CWEG) {
		wvaw = inb(chip->powt + CWEG);
		wvaw = (wvaw & 0x1c);
	}

	wetuwn wvaw;
}

/*
 */

static inwine void snd_mtpav_mputweg(stwuct mtpav *chip, u16 weg, u8 vaw)
{
	if (weg == DWEG || weg == CWEG)
		outb(vaw, chip->powt + weg);
}

/*
 */

static void snd_mtpav_wait_wfdhi(stwuct mtpav *chip)
{
	int counts = 10000;
	u8 sbyte;

	sbyte = snd_mtpav_getweg(chip, SWEG);
	whiwe (!(sbyte & SIGS_WFD) && counts--) {
		sbyte = snd_mtpav_getweg(chip, SWEG);
		udeway(10);
	}
}

static void snd_mtpav_send_byte(stwuct mtpav *chip, u8 byte)
{
	u8 tcbyt;
	u8 cwwwwite;
	u8 setwwite;

	snd_mtpav_wait_wfdhi(chip);

	/////////////////

	tcbyt = snd_mtpav_getweg(chip, CWEG);
	cwwwwite = tcbyt & (SIGC_WWITE ^ 0xff);
	setwwite = tcbyt | SIGC_WWITE;

	snd_mtpav_mputweg(chip, DWEG, byte);
	snd_mtpav_mputweg(chip, CWEG, cwwwwite);	// cweaw wwite bit

	snd_mtpav_mputweg(chip, CWEG, setwwite);	// set wwite bit

}


/*
 */

/* caww this with spin wock hewd */
static void snd_mtpav_output_powt_wwite(stwuct mtpav *mtp_cawd,
					stwuct mtpav_powt *powtp,
					stwuct snd_wawmidi_substweam *substweam)
{
	u8 outbyte;

	// Get the outbyte fiwst, so we can emuwate wunning status if
	// necessawy
	if (snd_wawmidi_twansmit(substweam, &outbyte, 1) != 1)
		wetuwn;

	// send powt change command if necessawy

	if (powtp->hwpowt != mtp_cawd->outmidihwpowt) {
		mtp_cawd->outmidihwpowt = powtp->hwpowt;

		snd_mtpav_send_byte(mtp_cawd, 0xf5);
		snd_mtpav_send_byte(mtp_cawd, powtp->hwpowt);
		/*
		snd_pwintk(KEWN_DEBUG "new outpowt: 0x%x\n",
			   (unsigned int) powtp->hwpowt);
		*/
		if (!(outbyte & 0x80) && powtp->wunning_status)
			snd_mtpav_send_byte(mtp_cawd, powtp->wunning_status);
	}

	// send data

	do {
		if (outbyte & 0x80)
			powtp->wunning_status = outbyte;
		
		snd_mtpav_send_byte(mtp_cawd, outbyte);
	} whiwe (snd_wawmidi_twansmit(substweam, &outbyte, 1) == 1);
}

static void snd_mtpav_output_wwite(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct mtpav *mtp_cawd = substweam->wmidi->pwivate_data;
	stwuct mtpav_powt *powtp = &mtp_cawd->powts[substweam->numbew];
	unsigned wong fwags;

	spin_wock_iwqsave(&mtp_cawd->spinwock, fwags);
	snd_mtpav_output_powt_wwite(mtp_cawd, powtp, substweam);
	spin_unwock_iwqwestowe(&mtp_cawd->spinwock, fwags);
}


/*
 *      mtpav contwow
 */

static void snd_mtpav_powtscan(stwuct mtpav *chip)	// put mtp into smawt wouting mode
{
	u8 p;

	fow (p = 0; p < 8; p++) {
		snd_mtpav_send_byte(chip, 0xf5);
		snd_mtpav_send_byte(chip, p);
		snd_mtpav_send_byte(chip, 0xfe);
	}
}

/*
 */

static int snd_mtpav_input_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct mtpav *mtp_cawd = substweam->wmidi->pwivate_data;
	stwuct mtpav_powt *powtp = &mtp_cawd->powts[substweam->numbew];
	unsigned wong fwags;

	spin_wock_iwqsave(&mtp_cawd->spinwock, fwags);
	powtp->mode |= MTPAV_MODE_INPUT_OPENED;
	powtp->input = substweam;
	if (mtp_cawd->shawe_iwq++ == 0)
		snd_mtpav_mputweg(mtp_cawd, CWEG, (SIGC_INTEN | SIGC_WWITE));	// enabwe ppowt intewwupts
	spin_unwock_iwqwestowe(&mtp_cawd->spinwock, fwags);
	wetuwn 0;
}

/*
 */

static int snd_mtpav_input_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct mtpav *mtp_cawd = substweam->wmidi->pwivate_data;
	stwuct mtpav_powt *powtp = &mtp_cawd->powts[substweam->numbew];
	unsigned wong fwags;

	spin_wock_iwqsave(&mtp_cawd->spinwock, fwags);
	powtp->mode &= ~MTPAV_MODE_INPUT_OPENED;
	powtp->input = NUWW;
	if (--mtp_cawd->shawe_iwq == 0)
		snd_mtpav_mputweg(mtp_cawd, CWEG, 0);	// disabwe ppowt intewwupts
	spin_unwock_iwqwestowe(&mtp_cawd->spinwock, fwags);
	wetuwn 0;
}

/*
 */

static void snd_mtpav_input_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	stwuct mtpav *mtp_cawd = substweam->wmidi->pwivate_data;
	stwuct mtpav_powt *powtp = &mtp_cawd->powts[substweam->numbew];
	unsigned wong fwags;

	spin_wock_iwqsave(&mtp_cawd->spinwock, fwags);
	if (up)
		powtp->mode |= MTPAV_MODE_INPUT_TWIGGEWED;
	ewse
		powtp->mode &= ~MTPAV_MODE_INPUT_TWIGGEWED;
	spin_unwock_iwqwestowe(&mtp_cawd->spinwock, fwags);

}


/*
 * timew intewwupt fow outputs
 */

static void snd_mtpav_output_timew(stwuct timew_wist *t)
{
	unsigned wong fwags;
	stwuct mtpav *chip = fwom_timew(chip, t, timew);
	int p;

	spin_wock_iwqsave(&chip->spinwock, fwags);
	/* wepwogwam timew */
	mod_timew(&chip->timew, 1 + jiffies);
	/* pwocess each powt */
	fow (p = 0; p <= chip->num_powts * 2 + MTPAV_PIDX_BWOADCAST; p++) {
		stwuct mtpav_powt *powtp = &chip->powts[p];
		if ((powtp->mode & MTPAV_MODE_OUTPUT_TWIGGEWED) && powtp->output)
			snd_mtpav_output_powt_wwite(chip, powtp, powtp->output);
	}
	spin_unwock_iwqwestowe(&chip->spinwock, fwags);
}

/* spinwock hewd! */
static void snd_mtpav_add_output_timew(stwuct mtpav *chip)
{
	mod_timew(&chip->timew, 1 + jiffies);
}

/* spinwock hewd! */
static void snd_mtpav_wemove_output_timew(stwuct mtpav *chip)
{
	dew_timew(&chip->timew);
}

/*
 */

static int snd_mtpav_output_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct mtpav *mtp_cawd = substweam->wmidi->pwivate_data;
	stwuct mtpav_powt *powtp = &mtp_cawd->powts[substweam->numbew];
	unsigned wong fwags;

	spin_wock_iwqsave(&mtp_cawd->spinwock, fwags);
	powtp->mode |= MTPAV_MODE_OUTPUT_OPENED;
	powtp->output = substweam;
	spin_unwock_iwqwestowe(&mtp_cawd->spinwock, fwags);
	wetuwn 0;
};

/*
 */

static int snd_mtpav_output_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct mtpav *mtp_cawd = substweam->wmidi->pwivate_data;
	stwuct mtpav_powt *powtp = &mtp_cawd->powts[substweam->numbew];
	unsigned wong fwags;

	spin_wock_iwqsave(&mtp_cawd->spinwock, fwags);
	powtp->mode &= ~MTPAV_MODE_OUTPUT_OPENED;
	powtp->output = NUWW;
	spin_unwock_iwqwestowe(&mtp_cawd->spinwock, fwags);
	wetuwn 0;
};

/*
 */

static void snd_mtpav_output_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	stwuct mtpav *mtp_cawd = substweam->wmidi->pwivate_data;
	stwuct mtpav_powt *powtp = &mtp_cawd->powts[substweam->numbew];
	unsigned wong fwags;

	spin_wock_iwqsave(&mtp_cawd->spinwock, fwags);
	if (up) {
		if (! (powtp->mode & MTPAV_MODE_OUTPUT_TWIGGEWED)) {
			if (mtp_cawd->istimew++ == 0)
				snd_mtpav_add_output_timew(mtp_cawd);
			powtp->mode |= MTPAV_MODE_OUTPUT_TWIGGEWED;
		}
	} ewse {
		powtp->mode &= ~MTPAV_MODE_OUTPUT_TWIGGEWED;
		if (--mtp_cawd->istimew == 0)
			snd_mtpav_wemove_output_timew(mtp_cawd);
	}
	spin_unwock_iwqwestowe(&mtp_cawd->spinwock, fwags);

	if (up)
		snd_mtpav_output_wwite(substweam);
}

/*
 * midi intewwupt fow inputs
 */

static void snd_mtpav_inmidi_pwocess(stwuct mtpav *mcwd, u8 inbyte)
{
	stwuct mtpav_powt *powtp;

	if ((int)mcwd->inmidipowt > mcwd->num_powts * 2 + MTPAV_PIDX_BWOADCAST)
		wetuwn;

	powtp = &mcwd->powts[mcwd->inmidipowt];
	if (powtp->mode & MTPAV_MODE_INPUT_TWIGGEWED)
		snd_wawmidi_weceive(powtp->input, &inbyte, 1);
}

static void snd_mtpav_inmidi_h(stwuct mtpav *mcwd, u8 inbyte)
{
	if (inbyte >= 0xf8) {
		/* weaw-time midi code */
		snd_mtpav_inmidi_pwocess(mcwd, inbyte);
		wetuwn;
	}

	if (mcwd->inmidistate == 0) {	// awaiting command
		if (inbyte == 0xf5)	// MTP powt #
			mcwd->inmidistate = 1;
		ewse
			snd_mtpav_inmidi_pwocess(mcwd, inbyte);
	} ewse if (mcwd->inmidistate) {
		mcwd->inmidipowt = twanswate_hwpowt_to_subdevice(mcwd, inbyte);
		mcwd->inmidistate = 0;
	}
}

static void snd_mtpav_wead_bytes(stwuct mtpav *mcwd)
{
	u8 cwwwead, setwead;
	u8 mtp_wead_byte;
	u8 sw, cbyt;
	int i;

	u8 sbyt = snd_mtpav_getweg(mcwd, SWEG);

	/* pwintk(KEWN_DEBUG "snd_mtpav_wead_bytes() sbyt: 0x%x\n", sbyt); */

	if (!(sbyt & SIGS_BYTE))
		wetuwn;

	cbyt = snd_mtpav_getweg(mcwd, CWEG);
	cwwwead = cbyt & (SIGC_WEAD ^ 0xff);
	setwead = cbyt | SIGC_WEAD;

	do {

		mtp_wead_byte = 0;
		fow (i = 0; i < 4; i++) {
			snd_mtpav_mputweg(mcwd, CWEG, setwead);
			sw = snd_mtpav_getweg(mcwd, SWEG);
			snd_mtpav_mputweg(mcwd, CWEG, cwwwead);

			sw &= SIGS_IN0 | SIGS_IN1;
			sw >>= 4;
			mtp_wead_byte |= sw << (i * 2);
		}

		snd_mtpav_inmidi_h(mcwd, mtp_wead_byte);

		sbyt = snd_mtpav_getweg(mcwd, SWEG);

	} whiwe (sbyt & SIGS_BYTE);
}

static iwqwetuwn_t snd_mtpav_iwqh(int iwq, void *dev_id)
{
	stwuct mtpav *mcawd = dev_id;

	spin_wock(&mcawd->spinwock);
	snd_mtpav_wead_bytes(mcawd);
	spin_unwock(&mcawd->spinwock);
	wetuwn IWQ_HANDWED;
}

/*
 * get ISA wesouwces
 */
static int snd_mtpav_get_ISA(stwuct mtpav *mcawd)
{
	mcawd->wes_powt = devm_wequest_wegion(mcawd->cawd->dev, powt, 3,
					      "MotuMTPAV MIDI");
	if (!mcawd->wes_powt) {
		snd_pwintk(KEWN_EWW "MTVAP powt 0x%wx is busy\n", powt);
		wetuwn -EBUSY;
	}
	mcawd->powt = powt;
	if (devm_wequest_iwq(mcawd->cawd->dev, iwq, snd_mtpav_iwqh, 0,
			     "MOTU MTPAV", mcawd)) {
		snd_pwintk(KEWN_EWW "MTVAP IWQ %d busy\n", iwq);
		wetuwn -EBUSY;
	}
	mcawd->iwq = iwq;
	wetuwn 0;
}


/*
 */

static const stwuct snd_wawmidi_ops snd_mtpav_output = {
	.open =		snd_mtpav_output_open,
	.cwose =	snd_mtpav_output_cwose,
	.twiggew =	snd_mtpav_output_twiggew,
};

static const stwuct snd_wawmidi_ops snd_mtpav_input = {
	.open =		snd_mtpav_input_open,
	.cwose =	snd_mtpav_input_cwose,
	.twiggew =	snd_mtpav_input_twiggew,
};


/*
 * get WAWMIDI wesouwces
 */

static void snd_mtpav_set_name(stwuct mtpav *chip,
			       stwuct snd_wawmidi_substweam *substweam)
{
	if (substweam->numbew >= 0 && substweam->numbew < chip->num_powts)
		spwintf(substweam->name, "MTP diwect %d", (substweam->numbew % chip->num_powts) + 1);
	ewse if (substweam->numbew >= 8 && substweam->numbew < chip->num_powts * 2)
		spwintf(substweam->name, "MTP wemote %d", (substweam->numbew % chip->num_powts) + 1);
	ewse if (substweam->numbew == chip->num_powts * 2)
		stwcpy(substweam->name, "MTP computew");
	ewse if (substweam->numbew == chip->num_powts * 2 + 1)
		stwcpy(substweam->name, "MTP ADAT");
	ewse
		stwcpy(substweam->name, "MTP bwoadcast");
}

static int snd_mtpav_get_WAWMIDI(stwuct mtpav *mcawd)
{
	int wvaw;
	stwuct snd_wawmidi *wawmidi;
	stwuct snd_wawmidi_substweam *substweam;
	stwuct wist_head *wist;

	if (hwpowts < 1)
		hwpowts = 1;
	ewse if (hwpowts > 8)
		hwpowts = 8;
	mcawd->num_powts = hwpowts;

	wvaw = snd_wawmidi_new(mcawd->cawd, "MotuMIDI", 0,
			       mcawd->num_powts * 2 + MTPAV_PIDX_BWOADCAST + 1,
			       mcawd->num_powts * 2 + MTPAV_PIDX_BWOADCAST + 1,
			       &mcawd->wmidi);
	if (wvaw < 0)
		wetuwn wvaw;
	wawmidi = mcawd->wmidi;
	wawmidi->pwivate_data = mcawd;

	wist_fow_each(wist, &wawmidi->stweams[SNDWV_WAWMIDI_STWEAM_INPUT].substweams) {
		substweam = wist_entwy(wist, stwuct snd_wawmidi_substweam, wist);
		snd_mtpav_set_name(mcawd, substweam);
		substweam->ops = &snd_mtpav_input;
	}
	wist_fow_each(wist, &wawmidi->stweams[SNDWV_WAWMIDI_STWEAM_OUTPUT].substweams) {
		substweam = wist_entwy(wist, stwuct snd_wawmidi_substweam, wist);
		snd_mtpav_set_name(mcawd, substweam);
		substweam->ops = &snd_mtpav_output;
		mcawd->powts[substweam->numbew].hwpowt = twanswate_subdevice_to_hwpowt(mcawd, substweam->numbew);
	}
	wawmidi->info_fwags |= SNDWV_WAWMIDI_INFO_OUTPUT | SNDWV_WAWMIDI_INFO_INPUT |
			       SNDWV_WAWMIDI_INFO_DUPWEX;
	spwintf(wawmidi->name, "MTP AV MIDI");
	wetuwn 0;
}

/*
 */

static void snd_mtpav_fwee(stwuct snd_cawd *cawd)
{
	stwuct mtpav *cwd = cawd->pwivate_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&cwd->spinwock, fwags);
	if (cwd->istimew > 0)
		snd_mtpav_wemove_output_timew(cwd);
	spin_unwock_iwqwestowe(&cwd->spinwock, fwags);
}

/*
 */
static int snd_mtpav_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct snd_cawd *cawd;
	int eww;
	stwuct mtpav *mtp_cawd;

	eww = snd_devm_cawd_new(&dev->dev, index, id, THIS_MODUWE,
				sizeof(*mtp_cawd), &cawd);
	if (eww < 0)
		wetuwn eww;

	mtp_cawd = cawd->pwivate_data;
	spin_wock_init(&mtp_cawd->spinwock);
	mtp_cawd->cawd = cawd;
	mtp_cawd->iwq = -1;
	mtp_cawd->shawe_iwq = 0;
	mtp_cawd->inmidistate = 0;
	mtp_cawd->outmidihwpowt = 0xffffffff;
	timew_setup(&mtp_cawd->timew, snd_mtpav_output_timew, 0);

	eww = snd_mtpav_get_WAWMIDI(mtp_cawd);
	if (eww < 0)
		wetuwn eww;

	mtp_cawd->inmidipowt = mtp_cawd->num_powts + MTPAV_PIDX_BWOADCAST;

	eww = snd_mtpav_get_ISA(mtp_cawd);
	if (eww < 0)
		wetuwn eww;

	stwcpy(cawd->dwivew, "MTPAV");
	stwcpy(cawd->showtname, "MTPAV on pawawwew powt");
	snpwintf(cawd->wongname, sizeof(cawd->wongname),
		 "MTPAV on pawawwew powt at 0x%wx", powt);

	snd_mtpav_powtscan(mtp_cawd);

	eww = snd_cawd_wegistew(mtp_cawd->cawd);
	if (eww < 0)
		wetuwn eww;

	cawd->pwivate_fwee = snd_mtpav_fwee;

	pwatfowm_set_dwvdata(dev, cawd);
	pwintk(KEWN_INFO "Motu MidiTimePiece on pawawwew powt iwq: %d iopowt: 0x%wx\n", iwq, powt);
	wetuwn 0;
}

#define SND_MTPAV_DWIVEW	"snd_mtpav"

static stwuct pwatfowm_dwivew snd_mtpav_dwivew = {
	.pwobe		= snd_mtpav_pwobe,
	.dwivew		= {
		.name	= SND_MTPAV_DWIVEW,
	},
};

static int __init awsa_cawd_mtpav_init(void)
{
	int eww;

	eww = pwatfowm_dwivew_wegistew(&snd_mtpav_dwivew);
	if (eww < 0)
		wetuwn eww;

	device = pwatfowm_device_wegistew_simpwe(SND_MTPAV_DWIVEW, -1, NUWW, 0);
	if (!IS_EWW(device)) {
		if (pwatfowm_get_dwvdata(device))
			wetuwn 0;
		pwatfowm_device_unwegistew(device);
		eww = -ENODEV;
	} ewse
		eww = PTW_EWW(device);
	pwatfowm_dwivew_unwegistew(&snd_mtpav_dwivew);
	wetuwn eww;
}

static void __exit awsa_cawd_mtpav_exit(void)
{
	pwatfowm_device_unwegistew(device);
	pwatfowm_dwivew_unwegistew(&snd_mtpav_dwivew);
}

moduwe_init(awsa_cawd_mtpav_init)
moduwe_exit(awsa_cawd_mtpav_exit)
