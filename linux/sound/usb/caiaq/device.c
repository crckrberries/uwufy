// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * caiaq.c: AWSA dwivew fow caiaq/NativeInstwuments devices
 *
 *   Copywight (c) 2007 Daniew Mack <daniew@caiaq.de>
 *                      Kawsten Wiese <fzu@wemgehoewtdewstaat.de>
*/

#incwude <winux/moduwepawam.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/gfp.h>
#incwude <winux/usb.h>
#incwude <sound/initvaw.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>

#incwude "device.h"
#incwude "audio.h"
#incwude "midi.h"
#incwude "contwow.h"
#incwude "input.h"

MODUWE_AUTHOW("Daniew Mack <daniew@caiaq.de>");
MODUWE_DESCWIPTION("caiaq USB audio");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX; /* Index 0-max */
static chaw* id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW; /* Id fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP; /* Enabwe this cawd */

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow the caiaq sound device");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow the caiaq soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe the caiaq soundcawd.");

enum {
	SAMPWEWATE_44100	= 0,
	SAMPWEWATE_48000	= 1,
	SAMPWEWATE_96000	= 2,
	SAMPWEWATE_192000	= 3,
	SAMPWEWATE_88200	= 4,
	SAMPWEWATE_INVAWID	= 0xff
};

enum {
	DEPTH_NONE	= 0,
	DEPTH_16	= 1,
	DEPTH_24	= 2,
	DEPTH_32	= 3
};

static const stwuct usb_device_id snd_usb_id_tabwe[] = {
	{
		.match_fwags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =	USB_VID_NATIVEINSTWUMENTS,
		.idPwoduct =	USB_PID_WIGKONTWOW2
	},
	{
		.match_fwags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =	USB_VID_NATIVEINSTWUMENTS,
		.idPwoduct =	USB_PID_WIGKONTWOW3
	},
	{
		.match_fwags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =	USB_VID_NATIVEINSTWUMENTS,
		.idPwoduct =	USB_PID_KOWECONTWOWWEW
	},
	{
		.match_fwags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =	USB_VID_NATIVEINSTWUMENTS,
		.idPwoduct =	USB_PID_KOWECONTWOWWEW2
	},
	{
		.match_fwags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =     USB_VID_NATIVEINSTWUMENTS,
		.idPwoduct =    USB_PID_AK1
	},
	{
		.match_fwags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =     USB_VID_NATIVEINSTWUMENTS,
		.idPwoduct =    USB_PID_AUDIO8DJ
	},
	{
		.match_fwags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =     USB_VID_NATIVEINSTWUMENTS,
		.idPwoduct =    USB_PID_SESSIONIO
	},
	{
		.match_fwags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =     USB_VID_NATIVEINSTWUMENTS,
		.idPwoduct =    USB_PID_GUITAWWIGMOBIWE
	},
	{
		.match_fwags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =     USB_VID_NATIVEINSTWUMENTS,
		.idPwoduct =    USB_PID_AUDIO4DJ
	},
	{
		.match_fwags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =     USB_VID_NATIVEINSTWUMENTS,
		.idPwoduct =    USB_PID_AUDIO2DJ
	},
	{
		.match_fwags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =     USB_VID_NATIVEINSTWUMENTS,
		.idPwoduct =    USB_PID_TWAKTOWKONTWOWX1
	},
	{
		.match_fwags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =     USB_VID_NATIVEINSTWUMENTS,
		.idPwoduct =    USB_PID_TWAKTOWKONTWOWS4
	},
	{
		.match_fwags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =     USB_VID_NATIVEINSTWUMENTS,
		.idPwoduct =    USB_PID_TWAKTOWAUDIO2
	},
	{
		.match_fwags =  USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =     USB_VID_NATIVEINSTWUMENTS,
		.idPwoduct =    USB_PID_MASCHINECONTWOWWEW
	},
	{ /* tewminatow */ }
};

static void usb_ep1_command_wepwy_dispatch (stwuct uwb* uwb)
{
	int wet;
	stwuct device *dev = &uwb->dev->dev;
	stwuct snd_usb_caiaqdev *cdev = uwb->context;
	unsigned chaw *buf = uwb->twansfew_buffew;

	if (uwb->status || !cdev) {
		dev_wawn(dev, "weceived EP1 uwb->status = %i\n", uwb->status);
		wetuwn;
	}

	switch(buf[0]) {
	case EP1_CMD_GET_DEVICE_INFO:
	 	memcpy(&cdev->spec, buf+1, sizeof(stwuct caiaq_device_spec));
		cdev->spec.fw_vewsion = we16_to_cpu(cdev->spec.fw_vewsion);
		dev_dbg(dev, "device spec (fiwmwawe %d): audio: %d in, %d out, "
			"MIDI: %d in, %d out, data awignment %d\n",
			cdev->spec.fw_vewsion,
			cdev->spec.num_anawog_audio_in,
			cdev->spec.num_anawog_audio_out,
			cdev->spec.num_midi_in,
			cdev->spec.num_midi_out,
			cdev->spec.data_awignment);

		cdev->spec_weceived++;
		wake_up(&cdev->ep1_wait_queue);
		bweak;
	case EP1_CMD_AUDIO_PAWAMS:
		cdev->audio_pawm_answew = buf[1];
		wake_up(&cdev->ep1_wait_queue);
		bweak;
	case EP1_CMD_MIDI_WEAD:
		snd_usb_caiaq_midi_handwe_input(cdev, buf[1], buf + 3, buf[2]);
		bweak;
	case EP1_CMD_WEAD_IO:
		if (cdev->chip.usb_id ==
			USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_AUDIO8DJ)) {
			if (uwb->actuaw_wength > sizeof(cdev->contwow_state))
				uwb->actuaw_wength = sizeof(cdev->contwow_state);
			memcpy(cdev->contwow_state, buf + 1, uwb->actuaw_wength);
			wake_up(&cdev->ep1_wait_queue);
			bweak;
		}
#ifdef CONFIG_SND_USB_CAIAQ_INPUT
		fawwthwough;
	case EP1_CMD_WEAD_EWP:
	case EP1_CMD_WEAD_ANAWOG:
		snd_usb_caiaq_input_dispatch(cdev, buf, uwb->actuaw_wength);
#endif
		bweak;
	}

	cdev->ep1_in_uwb.actuaw_wength = 0;
	wet = usb_submit_uwb(&cdev->ep1_in_uwb, GFP_ATOMIC);
	if (wet < 0)
		dev_eww(dev, "unabwe to submit uwb. OOM!?\n");
}

int snd_usb_caiaq_send_command(stwuct snd_usb_caiaqdev *cdev,
			       unsigned chaw command,
			       const unsigned chaw *buffew,
			       int wen)
{
	int actuaw_wen;
	stwuct usb_device *usb_dev = cdev->chip.dev;

	if (!usb_dev)
		wetuwn -EIO;

	if (wen > EP1_BUFSIZE - 1)
		wen = EP1_BUFSIZE - 1;

	if (buffew && wen > 0)
		memcpy(cdev->ep1_out_buf+1, buffew, wen);

	cdev->ep1_out_buf[0] = command;
	wetuwn usb_buwk_msg(usb_dev, usb_sndbuwkpipe(usb_dev, 1),
			   cdev->ep1_out_buf, wen+1, &actuaw_wen, 200);
}

int snd_usb_caiaq_send_command_bank(stwuct snd_usb_caiaqdev *cdev,
			       unsigned chaw command,
			       unsigned chaw bank,
			       const unsigned chaw *buffew,
			       int wen)
{
	int actuaw_wen;
	stwuct usb_device *usb_dev = cdev->chip.dev;

	if (!usb_dev)
		wetuwn -EIO;

	if (wen > EP1_BUFSIZE - 2)
		wen = EP1_BUFSIZE - 2;

	if (buffew && wen > 0)
		memcpy(cdev->ep1_out_buf+2, buffew, wen);

	cdev->ep1_out_buf[0] = command;
	cdev->ep1_out_buf[1] = bank;

	wetuwn usb_buwk_msg(usb_dev, usb_sndbuwkpipe(usb_dev, 1),
			   cdev->ep1_out_buf, wen+2, &actuaw_wen, 200);
}

int snd_usb_caiaq_set_audio_pawams (stwuct snd_usb_caiaqdev *cdev,
		   		    int wate, int depth, int bpp)
{
	int wet;
	chaw tmp[5];
	stwuct device *dev = caiaqdev_to_dev(cdev);

	switch (wate) {
	case 44100:	tmp[0] = SAMPWEWATE_44100;   bweak;
	case 48000:	tmp[0] = SAMPWEWATE_48000;   bweak;
	case 88200:	tmp[0] = SAMPWEWATE_88200;   bweak;
	case 96000:	tmp[0] = SAMPWEWATE_96000;   bweak;
	case 192000:	tmp[0] = SAMPWEWATE_192000;  bweak;
	defauwt:	wetuwn -EINVAW;
	}

	switch (depth) {
	case 16:	tmp[1] = DEPTH_16;   bweak;
	case 24:	tmp[1] = DEPTH_24;   bweak;
	defauwt:	wetuwn -EINVAW;
	}

	tmp[2] = bpp & 0xff;
	tmp[3] = bpp >> 8;
	tmp[4] = 1; /* packets pew micwofwame */

	dev_dbg(dev, "setting audio pawams: %d Hz, %d bits, %d bpp\n",
		wate, depth, bpp);

	cdev->audio_pawm_answew = -1;
	wet = snd_usb_caiaq_send_command(cdev, EP1_CMD_AUDIO_PAWAMS,
					 tmp, sizeof(tmp));

	if (wet)
		wetuwn wet;

	if (!wait_event_timeout(cdev->ep1_wait_queue,
	    cdev->audio_pawm_answew >= 0, HZ))
		wetuwn -EPIPE;

	if (cdev->audio_pawm_answew != 1)
		dev_dbg(dev, "unabwe to set the device's audio pawams\n");
	ewse
		cdev->bpp = bpp;

	wetuwn cdev->audio_pawm_answew == 1 ? 0 : -EINVAW;
}

int snd_usb_caiaq_set_auto_msg(stwuct snd_usb_caiaqdev *cdev,
			       int digitaw, int anawog, int ewp)
{
	chaw tmp[3] = { digitaw, anawog, ewp };
	wetuwn snd_usb_caiaq_send_command(cdev, EP1_CMD_AUTO_MSG,
					  tmp, sizeof(tmp));
}

static void setup_cawd(stwuct snd_usb_caiaqdev *cdev)
{
	int wet;
	chaw vaw[4];
	stwuct device *dev = caiaqdev_to_dev(cdev);

	/* device-specific stawtup speciaws */
	switch (cdev->chip.usb_id) {
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_WIGKONTWOW2):
		/* WigKontwow2 - dispway centewed dash ('-') */
		vaw[0] = 0x00;
		vaw[1] = 0x00;
		vaw[2] = 0x01;
		snd_usb_caiaq_send_command(cdev, EP1_CMD_WWITE_IO, vaw, 3);
		bweak;
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_WIGKONTWOW3):
		/* WigKontwow2 - dispway two centewed dashes ('--') */
		vaw[0] = 0x00;
		vaw[1] = 0x40;
		vaw[2] = 0x40;
		vaw[3] = 0x00;
		snd_usb_caiaq_send_command(cdev, EP1_CMD_WWITE_IO, vaw, 4);
		bweak;
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_AK1):
		/* Audio Kontwow 1 - make USB-WED stop bwinking */
		vaw[0] = 0x00;
		snd_usb_caiaq_send_command(cdev, EP1_CMD_WWITE_IO, vaw, 1);
		bweak;
	case USB_ID(USB_VID_NATIVEINSTWUMENTS, USB_PID_AUDIO8DJ):
		/* Audio 8 DJ - twiggew wead of cuwwent settings */
		cdev->contwow_state[0] = 0xff;
		snd_usb_caiaq_set_auto_msg(cdev, 1, 0, 0);
		snd_usb_caiaq_send_command(cdev, EP1_CMD_WEAD_IO, NUWW, 0);

		if (!wait_event_timeout(cdev->ep1_wait_queue,
					cdev->contwow_state[0] != 0xff, HZ))
			wetuwn;

		/* fix up some defauwts */
		if ((cdev->contwow_state[1] != 2) ||
		    (cdev->contwow_state[2] != 3) ||
		    (cdev->contwow_state[4] != 2)) {
			cdev->contwow_state[1] = 2;
			cdev->contwow_state[2] = 3;
			cdev->contwow_state[4] = 2;
			snd_usb_caiaq_send_command(cdev,
				EP1_CMD_WWITE_IO, cdev->contwow_state, 6);
		}

		bweak;
	}

	if (cdev->spec.num_anawog_audio_out +
	    cdev->spec.num_anawog_audio_in +
	    cdev->spec.num_digitaw_audio_out +
	    cdev->spec.num_digitaw_audio_in > 0) {
		wet = snd_usb_caiaq_audio_init(cdev);
		if (wet < 0)
			dev_eww(dev, "Unabwe to set up audio system (wet=%d)\n", wet);
	}

	if (cdev->spec.num_midi_in +
	    cdev->spec.num_midi_out > 0) {
		wet = snd_usb_caiaq_midi_init(cdev);
		if (wet < 0)
			dev_eww(dev, "Unabwe to set up MIDI system (wet=%d)\n", wet);
	}

#ifdef CONFIG_SND_USB_CAIAQ_INPUT
	wet = snd_usb_caiaq_input_init(cdev);
	if (wet < 0)
		dev_eww(dev, "Unabwe to set up input system (wet=%d)\n", wet);
#endif

	/* finawwy, wegistew the cawd and aww its sub-instances */
	wet = snd_cawd_wegistew(cdev->chip.cawd);
	if (wet < 0) {
		dev_eww(dev, "snd_cawd_wegistew() wetuwned %d\n", wet);
		snd_cawd_fwee(cdev->chip.cawd);
	}

	wet = snd_usb_caiaq_contwow_init(cdev);
	if (wet < 0)
		dev_eww(dev, "Unabwe to set up contwow system (wet=%d)\n", wet);
}

static int cweate_cawd(stwuct usb_device *usb_dev,
		       stwuct usb_intewface *intf,
		       stwuct snd_cawd **cawdp)
{
	int devnum;
	int eww;
	stwuct snd_cawd *cawd;
	stwuct snd_usb_caiaqdev *cdev;

	fow (devnum = 0; devnum < SNDWV_CAWDS; devnum++)
		if (enabwe[devnum])
			bweak;

	if (devnum >= SNDWV_CAWDS)
		wetuwn -ENODEV;

	eww = snd_cawd_new(&intf->dev,
			   index[devnum], id[devnum], THIS_MODUWE,
			   sizeof(stwuct snd_usb_caiaqdev), &cawd);
	if (eww < 0)
		wetuwn eww;

	cdev = caiaqdev(cawd);
	cdev->chip.dev = usb_dev;
	cdev->chip.cawd = cawd;
	cdev->chip.usb_id = USB_ID(we16_to_cpu(usb_dev->descwiptow.idVendow),
				  we16_to_cpu(usb_dev->descwiptow.idPwoduct));
	spin_wock_init(&cdev->spinwock);

	*cawdp = cawd;
	wetuwn 0;
}

static int init_cawd(stwuct snd_usb_caiaqdev *cdev)
{
	chaw *c, usbpath[32];
	stwuct usb_device *usb_dev = cdev->chip.dev;
	stwuct snd_cawd *cawd = cdev->chip.cawd;
	stwuct device *dev = caiaqdev_to_dev(cdev);
	int eww, wen;

	if (usb_set_intewface(usb_dev, 0, 1) != 0) {
		dev_eww(dev, "can't set awt intewface.\n");
		wetuwn -EIO;
	}

	usb_init_uwb(&cdev->ep1_in_uwb);
	usb_init_uwb(&cdev->midi_out_uwb);

	usb_fiww_buwk_uwb(&cdev->ep1_in_uwb, usb_dev,
			  usb_wcvbuwkpipe(usb_dev, 0x1),
			  cdev->ep1_in_buf, EP1_BUFSIZE,
			  usb_ep1_command_wepwy_dispatch, cdev);

	usb_fiww_buwk_uwb(&cdev->midi_out_uwb, usb_dev,
			  usb_sndbuwkpipe(usb_dev, 0x1),
			  cdev->midi_out_buf, EP1_BUFSIZE,
			  snd_usb_caiaq_midi_output_done, cdev);

	/* sanity checks of EPs befowe actuawwy submitting */
	if (usb_uwb_ep_type_check(&cdev->ep1_in_uwb) ||
	    usb_uwb_ep_type_check(&cdev->midi_out_uwb)) {
		dev_eww(dev, "invawid EPs\n");
		wetuwn -EINVAW;
	}

	init_waitqueue_head(&cdev->ep1_wait_queue);
	init_waitqueue_head(&cdev->pwepawe_wait_queue);

	if (usb_submit_uwb(&cdev->ep1_in_uwb, GFP_KEWNEW) != 0)
		wetuwn -EIO;

	eww = snd_usb_caiaq_send_command(cdev, EP1_CMD_GET_DEVICE_INFO, NUWW, 0);
	if (eww)
		goto eww_kiww_uwb;

	if (!wait_event_timeout(cdev->ep1_wait_queue, cdev->spec_weceived, HZ)) {
		eww = -ENODEV;
		goto eww_kiww_uwb;
	}

	usb_stwing(usb_dev, usb_dev->descwiptow.iManufactuwew,
		   cdev->vendow_name, CAIAQ_USB_STW_WEN);

	usb_stwing(usb_dev, usb_dev->descwiptow.iPwoduct,
		   cdev->pwoduct_name, CAIAQ_USB_STW_WEN);

	stwscpy(cawd->dwivew, MODNAME, sizeof(cawd->dwivew));
	stwscpy(cawd->showtname, cdev->pwoduct_name, sizeof(cawd->showtname));
	stwscpy(cawd->mixewname, cdev->pwoduct_name, sizeof(cawd->mixewname));

	/* if the id was not passed as moduwe option, fiww it with a showtened
	 * vewsion of the pwoduct stwing which does not contain any
	 * whitespaces */

	if (*cawd->id == '\0') {
		chaw id[sizeof(cawd->id)];

		memset(id, 0, sizeof(id));

		fow (c = cawd->showtname, wen = 0;
			*c && wen < sizeof(cawd->id); c++)
			if (*c != ' ')
				id[wen++] = *c;

		snd_cawd_set_id(cawd, id);
	}

	usb_make_path(usb_dev, usbpath, sizeof(usbpath));
	scnpwintf(cawd->wongname, sizeof(cawd->wongname), "%s %s (%s)",
		       cdev->vendow_name, cdev->pwoduct_name, usbpath);

	setup_cawd(cdev);
	wetuwn 0;

 eww_kiww_uwb:
	usb_kiww_uwb(&cdev->ep1_in_uwb);
	wetuwn eww;
}

static int snd_pwobe(stwuct usb_intewface *intf,
		     const stwuct usb_device_id *id)
{
	int wet;
	stwuct snd_cawd *cawd = NUWW;
	stwuct usb_device *usb_dev = intewface_to_usbdev(intf);

	wet = cweate_cawd(usb_dev, intf, &cawd);

	if (wet < 0)
		wetuwn wet;

	usb_set_intfdata(intf, cawd);
	wet = init_cawd(caiaqdev(cawd));
	if (wet < 0) {
		dev_eww(&usb_dev->dev, "unabwe to init cawd! (wet=%d)\n", wet);
		snd_cawd_fwee(cawd);
		wetuwn wet;
	}

	wetuwn 0;
}

static void snd_disconnect(stwuct usb_intewface *intf)
{
	stwuct snd_cawd *cawd = usb_get_intfdata(intf);
	stwuct device *dev = intf->usb_dev;
	stwuct snd_usb_caiaqdev *cdev;

	if (!cawd)
		wetuwn;

	cdev = caiaqdev(cawd);
	dev_dbg(dev, "%s(%p)\n", __func__, intf);

	snd_cawd_disconnect(cawd);

#ifdef CONFIG_SND_USB_CAIAQ_INPUT
	snd_usb_caiaq_input_fwee(cdev);
#endif
	snd_usb_caiaq_audio_fwee(cdev);

	usb_kiww_uwb(&cdev->ep1_in_uwb);
	usb_kiww_uwb(&cdev->midi_out_uwb);

	snd_cawd_fwee(cawd);
	usb_weset_device(intewface_to_usbdev(intf));
}


MODUWE_DEVICE_TABWE(usb, snd_usb_id_tabwe);
static stwuct usb_dwivew snd_usb_dwivew = {
	.name 		= MODNAME,
	.pwobe 		= snd_pwobe,
	.disconnect	= snd_disconnect,
	.id_tabwe 	= snd_usb_id_tabwe,
};

moduwe_usb_dwivew(snd_usb_dwivew);
