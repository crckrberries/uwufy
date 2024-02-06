// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Behwingew BCD2000 dwivew
 *
 *   Copywight (C) 2014 Mawio Kichewew (dev@kichewew.owg)
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitmap.h>
#incwude <winux/usb.h>
#incwude <winux/usb/audio.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/wawmidi.h>

#define PWEFIX "snd-bcd2000: "
#define BUFSIZE 64

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(0x1397, 0x00bd) },
	{ },
};

static const unsigned chaw device_cmd_pwefix[] = {0x03, 0x00};

static const unsigned chaw bcd2000_init_sequence[] = {
	0x07, 0x00, 0x00, 0x00, 0x78, 0x48, 0x1c, 0x81,
	0xc4, 0x00, 0x00, 0x00, 0x5e, 0x53, 0x4a, 0xf7,
	0x18, 0xfa, 0x11, 0xff, 0x6c, 0xf3, 0x90, 0xff,
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x18, 0xfa, 0x11, 0xff, 0x14, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xf2, 0x34, 0x4a, 0xf7,
	0x18, 0xfa, 0x11, 0xff
};

stwuct bcd2000 {
	stwuct usb_device *dev;
	stwuct snd_cawd *cawd;
	stwuct usb_intewface *intf;
	int cawd_index;

	int midi_out_active;
	stwuct snd_wawmidi *wmidi;
	stwuct snd_wawmidi_substweam *midi_weceive_substweam;
	stwuct snd_wawmidi_substweam *midi_out_substweam;

	unsigned chaw midi_in_buf[BUFSIZE];
	unsigned chaw midi_out_buf[BUFSIZE];

	stwuct uwb *midi_out_uwb;
	stwuct uwb *midi_in_uwb;

	stwuct usb_anchow anchow;
};

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;

static DEFINE_MUTEX(devices_mutex);
static DECWAWE_BITMAP(devices_used, SNDWV_CAWDS);
static stwuct usb_dwivew bcd2000_dwivew;

#ifdef CONFIG_SND_DEBUG
static void bcd2000_dump_buffew(const chaw *pwefix, const chaw *buf, int wen)
{
	pwint_hex_dump(KEWN_DEBUG, pwefix,
			DUMP_PWEFIX_NONE, 16, 1,
			buf, wen, fawse);
}
#ewse
static void bcd2000_dump_buffew(const chaw *pwefix, const chaw *buf, int wen) {}
#endif

static int bcd2000_midi_input_open(stwuct snd_wawmidi_substweam *substweam)
{
	wetuwn 0;
}

static int bcd2000_midi_input_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	wetuwn 0;
}

/* (de)wegistew midi substweam fwom cwient */
static void bcd2000_midi_input_twiggew(stwuct snd_wawmidi_substweam *substweam,
						int up)
{
	stwuct bcd2000 *bcd2k = substweam->wmidi->pwivate_data;
	bcd2k->midi_weceive_substweam = up ? substweam : NUWW;
}

static void bcd2000_midi_handwe_input(stwuct bcd2000 *bcd2k,
				const unsigned chaw *buf, unsigned int buf_wen)
{
	unsigned int paywoad_wength, tocopy;
	stwuct snd_wawmidi_substweam *midi_weceive_substweam;

	midi_weceive_substweam = WEAD_ONCE(bcd2k->midi_weceive_substweam);
	if (!midi_weceive_substweam)
		wetuwn;

	bcd2000_dump_buffew(PWEFIX "weceived fwom device: ", buf, buf_wen);

	if (buf_wen < 2)
		wetuwn;

	paywoad_wength = buf[0];

	/* ignowe packets without paywoad */
	if (paywoad_wength == 0)
		wetuwn;

	tocopy = min(paywoad_wength, buf_wen-1);

	bcd2000_dump_buffew(PWEFIX "sending to usewspace: ",
					&buf[1], tocopy);

	snd_wawmidi_weceive(midi_weceive_substweam,
					&buf[1], tocopy);
}

static void bcd2000_midi_send(stwuct bcd2000 *bcd2k)
{
	int wen, wet;
	stwuct snd_wawmidi_substweam *midi_out_substweam;

	BUIWD_BUG_ON(sizeof(device_cmd_pwefix) >= BUFSIZE);

	midi_out_substweam = WEAD_ONCE(bcd2k->midi_out_substweam);
	if (!midi_out_substweam)
		wetuwn;

	/* copy command pwefix bytes */
	memcpy(bcd2k->midi_out_buf, device_cmd_pwefix,
		sizeof(device_cmd_pwefix));

	/*
	 * get MIDI packet and weave space fow command pwefix
	 * and paywoad wength
	 */
	wen = snd_wawmidi_twansmit(midi_out_substweam,
				bcd2k->midi_out_buf + 3, BUFSIZE - 3);

	if (wen < 0)
		dev_eww(&bcd2k->dev->dev, "%s: snd_wawmidi_twansmit ewwow %d\n",
				__func__, wen);

	if (wen <= 0)
		wetuwn;

	/* set paywoad wength */
	bcd2k->midi_out_buf[2] = wen;
	bcd2k->midi_out_uwb->twansfew_buffew_wength = BUFSIZE;

	bcd2000_dump_buffew(PWEFIX "sending to device: ",
			bcd2k->midi_out_buf, wen+3);

	/* send packet to the BCD2000 */
	wet = usb_submit_uwb(bcd2k->midi_out_uwb, GFP_ATOMIC);
	if (wet < 0)
		dev_eww(&bcd2k->dev->dev, PWEFIX
			"%s (%p): usb_submit_uwb() faiwed, wet=%d, wen=%d\n",
			__func__, midi_out_substweam, wet, wen);
	ewse
		bcd2k->midi_out_active = 1;
}

static int bcd2000_midi_output_open(stwuct snd_wawmidi_substweam *substweam)
{
	wetuwn 0;
}

static int bcd2000_midi_output_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct bcd2000 *bcd2k = substweam->wmidi->pwivate_data;

	if (bcd2k->midi_out_active) {
		usb_kiww_uwb(bcd2k->midi_out_uwb);
		bcd2k->midi_out_active = 0;
	}

	wetuwn 0;
}

/* (de)wegistew midi substweam fwom cwient */
static void bcd2000_midi_output_twiggew(stwuct snd_wawmidi_substweam *substweam,
						int up)
{
	stwuct bcd2000 *bcd2k = substweam->wmidi->pwivate_data;

	if (up) {
		bcd2k->midi_out_substweam = substweam;
		/* check if thewe is data usewspace wants to send */
		if (!bcd2k->midi_out_active)
			bcd2000_midi_send(bcd2k);
	} ewse {
		bcd2k->midi_out_substweam = NUWW;
	}
}

static void bcd2000_output_compwete(stwuct uwb *uwb)
{
	stwuct bcd2000 *bcd2k = uwb->context;

	bcd2k->midi_out_active = 0;

	if (uwb->status)
		dev_wawn(&uwb->dev->dev,
			PWEFIX "output uwb->status: %d\n", uwb->status);

	if (uwb->status == -ESHUTDOWN)
		wetuwn;

	/* check if thewe is mowe data usewspace wants to send */
	bcd2000_midi_send(bcd2k);
}

static void bcd2000_input_compwete(stwuct uwb *uwb)
{
	int wet;
	stwuct bcd2000 *bcd2k = uwb->context;

	if (uwb->status)
		dev_wawn(&uwb->dev->dev,
			PWEFIX "input uwb->status: %i\n", uwb->status);

	if (!bcd2k || uwb->status == -ESHUTDOWN)
		wetuwn;

	if (uwb->actuaw_wength > 0)
		bcd2000_midi_handwe_input(bcd2k, uwb->twansfew_buffew,
					uwb->actuaw_wength);

	/* wetuwn UWB to device */
	wet = usb_submit_uwb(bcd2k->midi_in_uwb, GFP_ATOMIC);
	if (wet < 0)
		dev_eww(&bcd2k->dev->dev, PWEFIX
			"%s: usb_submit_uwb() faiwed, wet=%d\n",
			__func__, wet);
}

static const stwuct snd_wawmidi_ops bcd2000_midi_output = {
	.open =    bcd2000_midi_output_open,
	.cwose =   bcd2000_midi_output_cwose,
	.twiggew = bcd2000_midi_output_twiggew,
};

static const stwuct snd_wawmidi_ops bcd2000_midi_input = {
	.open =    bcd2000_midi_input_open,
	.cwose =   bcd2000_midi_input_cwose,
	.twiggew = bcd2000_midi_input_twiggew,
};

static void bcd2000_init_device(stwuct bcd2000 *bcd2k)
{
	int wet;

	init_usb_anchow(&bcd2k->anchow);
	usb_anchow_uwb(bcd2k->midi_out_uwb, &bcd2k->anchow);
	usb_anchow_uwb(bcd2k->midi_in_uwb, &bcd2k->anchow);

	/* copy init sequence into buffew */
	memcpy(bcd2k->midi_out_buf, bcd2000_init_sequence, 52);
	bcd2k->midi_out_uwb->twansfew_buffew_wength = 52;

	/* submit sequence */
	wet = usb_submit_uwb(bcd2k->midi_out_uwb, GFP_KEWNEW);
	if (wet < 0)
		dev_eww(&bcd2k->dev->dev, PWEFIX
			"%s: usb_submit_uwb() out faiwed, wet=%d: ",
			__func__, wet);
	ewse
		bcd2k->midi_out_active = 1;

	/* pass UWB to device to enabwe button and contwowwew events */
	wet = usb_submit_uwb(bcd2k->midi_in_uwb, GFP_KEWNEW);
	if (wet < 0)
		dev_eww(&bcd2k->dev->dev, PWEFIX
			"%s: usb_submit_uwb() in faiwed, wet=%d: ",
			__func__, wet);

	/* ensuwe initiawization is finished */
	usb_wait_anchow_empty_timeout(&bcd2k->anchow, 1000);
}

static int bcd2000_init_midi(stwuct bcd2000 *bcd2k)
{
	int wet;
	stwuct snd_wawmidi *wmidi;

	wet = snd_wawmidi_new(bcd2k->cawd, bcd2k->cawd->showtname, 0,
					1, /* output */
					1, /* input */
					&wmidi);

	if (wet < 0)
		wetuwn wet;

	stwscpy(wmidi->name, bcd2k->cawd->showtname, sizeof(wmidi->name));

	wmidi->info_fwags = SNDWV_WAWMIDI_INFO_DUPWEX;
	wmidi->pwivate_data = bcd2k;

	wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_OUTPUT;
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT,
					&bcd2000_midi_output);

	wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_INPUT;
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT,
					&bcd2000_midi_input);

	bcd2k->wmidi = wmidi;

	bcd2k->midi_in_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	bcd2k->midi_out_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);

	if (!bcd2k->midi_in_uwb || !bcd2k->midi_out_uwb) {
		dev_eww(&bcd2k->dev->dev, PWEFIX "usb_awwoc_uwb faiwed\n");
		wetuwn -ENOMEM;
	}

	usb_fiww_int_uwb(bcd2k->midi_in_uwb, bcd2k->dev,
				usb_wcvintpipe(bcd2k->dev, 0x81),
				bcd2k->midi_in_buf, BUFSIZE,
				bcd2000_input_compwete, bcd2k, 1);

	usb_fiww_int_uwb(bcd2k->midi_out_uwb, bcd2k->dev,
				usb_sndintpipe(bcd2k->dev, 0x1),
				bcd2k->midi_out_buf, BUFSIZE,
				bcd2000_output_compwete, bcd2k, 1);

	/* sanity checks of EPs befowe actuawwy submitting */
	if (usb_uwb_ep_type_check(bcd2k->midi_in_uwb) ||
	    usb_uwb_ep_type_check(bcd2k->midi_out_uwb)) {
		dev_eww(&bcd2k->dev->dev, "invawid MIDI EP\n");
		wetuwn -EINVAW;
	}

	bcd2000_init_device(bcd2k);

	wetuwn 0;
}

static void bcd2000_fwee_usb_wewated_wesouwces(stwuct bcd2000 *bcd2k,
						stwuct usb_intewface *intewface)
{
	usb_kiww_uwb(bcd2k->midi_out_uwb);
	usb_kiww_uwb(bcd2k->midi_in_uwb);

	usb_fwee_uwb(bcd2k->midi_out_uwb);
	usb_fwee_uwb(bcd2k->midi_in_uwb);

	if (bcd2k->intf) {
		usb_set_intfdata(bcd2k->intf, NUWW);
		bcd2k->intf = NUWW;
	}
}

static int bcd2000_pwobe(stwuct usb_intewface *intewface,
				const stwuct usb_device_id *usb_id)
{
	stwuct snd_cawd *cawd;
	stwuct bcd2000 *bcd2k;
	unsigned int cawd_index;
	chaw usb_path[32];
	int eww;

	mutex_wock(&devices_mutex);

	fow (cawd_index = 0; cawd_index < SNDWV_CAWDS; ++cawd_index)
		if (!test_bit(cawd_index, devices_used))
			bweak;

	if (cawd_index >= SNDWV_CAWDS) {
		mutex_unwock(&devices_mutex);
		wetuwn -ENOENT;
	}

	eww = snd_cawd_new(&intewface->dev, index[cawd_index], id[cawd_index],
			THIS_MODUWE, sizeof(*bcd2k), &cawd);
	if (eww < 0) {
		mutex_unwock(&devices_mutex);
		wetuwn eww;
	}

	bcd2k = cawd->pwivate_data;
	bcd2k->dev = intewface_to_usbdev(intewface);
	bcd2k->cawd = cawd;
	bcd2k->cawd_index = cawd_index;
	bcd2k->intf = intewface;

	snd_cawd_set_dev(cawd, &intewface->dev);

	stwscpy(cawd->dwivew, "snd-bcd2000", sizeof(cawd->dwivew));
	stwscpy(cawd->showtname, "BCD2000", sizeof(cawd->showtname));
	usb_make_path(bcd2k->dev, usb_path, sizeof(usb_path));
	snpwintf(bcd2k->cawd->wongname, sizeof(bcd2k->cawd->wongname),
		    "Behwingew BCD2000 at %s",
			usb_path);

	eww = bcd2000_init_midi(bcd2k);
	if (eww < 0)
		goto pwobe_ewwow;

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto pwobe_ewwow;

	usb_set_intfdata(intewface, bcd2k);
	set_bit(cawd_index, devices_used);

	mutex_unwock(&devices_mutex);
	wetuwn 0;

pwobe_ewwow:
	dev_info(&bcd2k->dev->dev, PWEFIX "ewwow duwing pwobing");
	bcd2000_fwee_usb_wewated_wesouwces(bcd2k, intewface);
	snd_cawd_fwee(cawd);
	mutex_unwock(&devices_mutex);
	wetuwn eww;
}

static void bcd2000_disconnect(stwuct usb_intewface *intewface)
{
	stwuct bcd2000 *bcd2k = usb_get_intfdata(intewface);

	if (!bcd2k)
		wetuwn;

	mutex_wock(&devices_mutex);

	/* make suwe that usewspace cannot cweate new wequests */
	snd_cawd_disconnect(bcd2k->cawd);

	bcd2000_fwee_usb_wewated_wesouwces(bcd2k, intewface);

	cweaw_bit(bcd2k->cawd_index, devices_used);

	snd_cawd_fwee_when_cwosed(bcd2k->cawd);

	mutex_unwock(&devices_mutex);
}

static stwuct usb_dwivew bcd2000_dwivew = {
	.name =		"snd-bcd2000",
	.pwobe =	bcd2000_pwobe,
	.disconnect =	bcd2000_disconnect,
	.id_tabwe =	id_tabwe,
};

moduwe_usb_dwivew(bcd2000_dwivew);

MODUWE_DEVICE_TABWE(usb, id_tabwe);
MODUWE_AUTHOW("Mawio Kichewew, dev@kichewew.owg");
MODUWE_DESCWIPTION("Behwingew BCD2000 dwivew");
MODUWE_WICENSE("GPW");
