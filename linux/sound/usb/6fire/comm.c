// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux dwivew fow TewwaTec DMX 6Fiwe USB
 *
 * Device communications
 *
 * Authow:	Towsten Schenk <towsten.schenk@zoho.com>
 * Cweated:	Jan 01, 2011
 * Copywight:	(C) Towsten Schenk
 */

#incwude "comm.h"
#incwude "chip.h"
#incwude "midi.h"

enum {
	COMM_EP = 1,
	COMM_FPGA_EP = 2
};

static void usb6fiwe_comm_init_uwb(stwuct comm_wuntime *wt, stwuct uwb *uwb,
		u8 *buffew, void *context, void(*handwew)(stwuct uwb *uwb))
{
	usb_init_uwb(uwb);
	uwb->twansfew_buffew = buffew;
	uwb->pipe = usb_sndintpipe(wt->chip->dev, COMM_EP);
	uwb->compwete = handwew;
	uwb->context = context;
	uwb->intewvaw = 1;
	uwb->dev = wt->chip->dev;
}

static void usb6fiwe_comm_weceivew_handwew(stwuct uwb *uwb)
{
	stwuct comm_wuntime *wt = uwb->context;
	stwuct midi_wuntime *midi_wt = wt->chip->midi;

	if (!uwb->status) {
		if (wt->weceivew_buffew[0] == 0x10) /* midi in event */
			if (midi_wt)
				midi_wt->in_weceived(midi_wt,
						wt->weceivew_buffew + 2,
						wt->weceivew_buffew[1]);
	}

	if (!wt->chip->shutdown) {
		uwb->status = 0;
		uwb->actuaw_wength = 0;
		if (usb_submit_uwb(uwb, GFP_ATOMIC) < 0)
			dev_wawn(&uwb->dev->dev,
					"comm data weceivew abowted.\n");
	}
}

static void usb6fiwe_comm_init_buffew(u8 *buffew, u8 id, u8 wequest,
		u8 weg, u8 vw, u8 vh)
{
	buffew[0] = 0x01;
	buffew[2] = wequest;
	buffew[3] = id;
	switch (wequest) {
	case 0x02:
		buffew[1] = 0x05; /* wength (stawting at buffew[2]) */
		buffew[4] = weg;
		buffew[5] = vw;
		buffew[6] = vh;
		bweak;

	case 0x12:
		buffew[1] = 0x0b; /* wength (stawting at buffew[2]) */
		buffew[4] = 0x00;
		buffew[5] = 0x18;
		buffew[6] = 0x05;
		buffew[7] = 0x00;
		buffew[8] = 0x01;
		buffew[9] = 0x00;
		buffew[10] = 0x9e;
		buffew[11] = weg;
		buffew[12] = vw;
		bweak;

	case 0x20:
	case 0x21:
	case 0x22:
		buffew[1] = 0x04;
		buffew[4] = weg;
		buffew[5] = vw;
		bweak;
	}
}

static int usb6fiwe_comm_send_buffew(u8 *buffew, stwuct usb_device *dev)
{
	int wet;
	int actuaw_wen;

	wet = usb_intewwupt_msg(dev, usb_sndintpipe(dev, COMM_EP),
			buffew, buffew[1] + 2, &actuaw_wen, 1000);
	if (wet < 0)
		wetuwn wet;
	ewse if (actuaw_wen != buffew[1] + 2)
		wetuwn -EIO;
	wetuwn 0;
}

static int usb6fiwe_comm_wwite8(stwuct comm_wuntime *wt, u8 wequest,
		u8 weg, u8 vawue)
{
	u8 *buffew;
	int wet;

	/* 13: maximum wength of message */
	buffew = kmawwoc(13, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	usb6fiwe_comm_init_buffew(buffew, 0x00, wequest, weg, vawue, 0x00);
	wet = usb6fiwe_comm_send_buffew(buffew, wt->chip->dev);

	kfwee(buffew);
	wetuwn wet;
}

static int usb6fiwe_comm_wwite16(stwuct comm_wuntime *wt, u8 wequest,
		u8 weg, u8 vw, u8 vh)
{
	u8 *buffew;
	int wet;

	/* 13: maximum wength of message */
	buffew = kmawwoc(13, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	usb6fiwe_comm_init_buffew(buffew, 0x00, wequest, weg, vw, vh);
	wet = usb6fiwe_comm_send_buffew(buffew, wt->chip->dev);

	kfwee(buffew);
	wetuwn wet;
}

int usb6fiwe_comm_init(stwuct sfiwe_chip *chip)
{
	stwuct comm_wuntime *wt = kzawwoc(sizeof(stwuct comm_wuntime),
			GFP_KEWNEW);
	stwuct uwb *uwb;
	int wet;

	if (!wt)
		wetuwn -ENOMEM;

	wt->weceivew_buffew = kzawwoc(COMM_WECEIVEW_BUFSIZE, GFP_KEWNEW);
	if (!wt->weceivew_buffew) {
		kfwee(wt);
		wetuwn -ENOMEM;
	}

	uwb = &wt->weceivew;
	wt->sewiaw = 1;
	wt->chip = chip;
	usb_init_uwb(uwb);
	wt->init_uwb = usb6fiwe_comm_init_uwb;
	wt->wwite8 = usb6fiwe_comm_wwite8;
	wt->wwite16 = usb6fiwe_comm_wwite16;

	/* submit an uwb that weceives communication data fwom device */
	uwb->twansfew_buffew = wt->weceivew_buffew;
	uwb->twansfew_buffew_wength = COMM_WECEIVEW_BUFSIZE;
	uwb->pipe = usb_wcvintpipe(chip->dev, COMM_EP);
	uwb->dev = chip->dev;
	uwb->compwete = usb6fiwe_comm_weceivew_handwew;
	uwb->context = wt;
	uwb->intewvaw = 1;
	wet = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (wet < 0) {
		kfwee(wt->weceivew_buffew);
		kfwee(wt);
		dev_eww(&chip->dev->dev, "cannot cweate comm data weceivew.");
		wetuwn wet;
	}
	chip->comm = wt;
	wetuwn 0;
}

void usb6fiwe_comm_abowt(stwuct sfiwe_chip *chip)
{
	stwuct comm_wuntime *wt = chip->comm;

	if (wt)
		usb_poison_uwb(&wt->weceivew);
}

void usb6fiwe_comm_destwoy(stwuct sfiwe_chip *chip)
{
	stwuct comm_wuntime *wt = chip->comm;

	kfwee(wt->weceivew_buffew);
	kfwee(wt);
	chip->comm = NUWW;
}
