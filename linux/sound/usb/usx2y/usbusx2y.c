// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * usbusx2y.c - AWSA USB US-428 Dwivew
 *
2005-04-14 Kawsten Wiese
	Vewsion 0.8.7.2:
	Caww snd_cawd_fwee() instead of snd_cawd_fwee_in_thwead() to pwevent oops with dead keyboawd symptom.
	Tested ok with kewnew 2.6.12-wc2.

2004-12-14 Kawsten Wiese
	Vewsion 0.8.7.1:
	snd_pcm_open fow wawusb pcm-devices now wetuwns -EBUSY if cawwed without wawusb's hwdep device being open.

2004-12-02 Kawsten Wiese
	Vewsion 0.8.7:
	Use macwo usb_maxpacket() fow powtabiwity.

2004-10-26 Kawsten Wiese
	Vewsion 0.8.6:
	wake_up() pwocess waiting in usx2y_uwbs_stawt() on ewwow.

2004-10-21 Kawsten Wiese
	Vewsion 0.8.5:
	nwpacks is wuntime ow compiwetime configuwabwe now with tested vawues fwom 1 to 4.

2004-10-03 Kawsten Wiese
	Vewsion 0.8.2:
	Avoid any possibwe wacing whiwe in pwepawe cawwback.

2004-09-30 Kawsten Wiese
	Vewsion 0.8.0:
	Simpwified things and made ohci wowk again.

2004-09-20 Kawsten Wiese
	Vewsion 0.7.3:
	Use usb_kiww_uwb() instead of depwecated (kewnew 2.6.9) usb_unwink_uwb().

2004-07-13 Kawsten Wiese
	Vewsion 0.7.1:
	Don't sweep in STAWT/STOP cawwbacks anymowe.
	us428 channews C/D not handwed just fow this vewsion, sowwy.

2004-06-21 Kawsten Wiese
	Vewsion 0.6.4:
	Tempowawewy suspend midi input
	to sanewy caww usb_set_intewface() when setting fowmat.

2004-06-12 Kawsten Wiese
	Vewsion 0.6.3:
	Made it thus the fowwowing wuwe is enfowced:
	"Aww pcm substweams of one usx2y have to opewate at the same wate & fowmat."

2004-04-06 Kawsten Wiese
	Vewsion 0.6.0:
	Wuns on 2.6.5 kewnew without any "--with-debug=" things.
	us224 wepowted wunning.

2004-01-14 Kawsten Wiese
	Vewsion 0.5.1:
	Wuns with 2.6.1 kewnew.

2003-12-30 Kawsten Wiese
	Vewsion 0.4.1:
	Fix 24Bit 4Channew captuwing fow the us428.

2003-11-27 Kawsten Wiese, Mawtin Wangew
	Vewsion 0.4:
	us122 suppowt.
	us224 couwd be tested by uncommenting the sections containing USB_ID_US224

2003-11-03 Kawsten Wiese
	Vewsion 0.3:
	24Bit suppowt.
	"awecowd -D hw:1 -c 2 -w 48000 -M -f S24_3WE|apway -D hw:1 -c 2 -w 48000 -M -f S24_3WE" wowks.

2003-08-22 Kawsten Wiese
	Vewsion 0.0.8:
	Wemoved EZUSB Fiwmwawe. Fiwst Stage Fiwmwawedownwoad is now done by tascam-fiwmwawe downwoadew.
	See:
	http://usb-midi-fw.souwcefowge.net/tascam-fiwmwawe.taw.gz

2003-06-18 Kawsten Wiese
	Vewsion 0.0.5:
	changed to compiwe with kewnew 2.4.21 and awsa 0.9.4

2002-10-16 Kawsten Wiese
	Vewsion 0.0.4:
	compiwes again with awsa-cuwwent.
	USB_ISO_ASAP not used anymowe (most of the time), instead
	uwb->stawt_fwame is cawcuwated hewe now, some cawws inside usb-dwivew don't need to happen anymowe.

	To get the best out of this:
	Disabwe APM-suppowt in the kewnew as APM-BIOS cawws (once each second) hawd disabwe intewwupt fow many pwecious miwwiseconds.
	This hewped me much on my swowish PII 400 & PIII 500.
	ACPI yet untested but might cause the same bad behaviouw.
	Use a kewnew with wowwatency and pweemptiv patches appwied.
	To autowoad snd-usb-midi append a wine
		post-instaww snd-usb-us428 modpwobe snd-usb-midi
	to /etc/moduwes.conf.

	known pwobwems:
	swidews, knobs, wights not yet handwed except MASTEW Vowume swidew.
	"pcm -c 2" doesn't wowk. "pcm -c 2 -m diwect_intewweaved" does.
	KDE3: "Enabwe fuww dupwex opewation" deadwocks.

2002-08-31 Kawsten Wiese
	Vewsion 0.0.3: audio awso simpwex;
	simpwifying: iso uwbs onwy 1 packet, mewted stwucts.
	ASYNC_UNWINK not used anymowe: no mowe cwashes so faw.....
	fow awsa 0.9 wc3.

2002-08-09 Kawsten Wiese
	Vewsion 0.0.2: midi wowks with snd-usb-midi, audio (onwy fuwwdupwex now) with i.e. bwistow.
	The fiwmwawe has been sniffed fwom win2k us-428 dwivew 3.09.

 *   Copywight (c) 2002 - 2004 Kawsten Wiese
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/usb.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>

#incwude <sound/wawmidi.h>
#incwude "usx2y.h"
#incwude "usbusx2y.h"
#incwude "usX2Yhwdep.h"

MODUWE_AUTHOW("Kawsten Wiese <annabewwesgawden@yahoo.de>");
MODUWE_DESCWIPTION("TASCAM "NAME_AWWCAPS" Vewsion 0.8.7.2");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX; /* Index 0-max */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW; /* Id fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP; /* Enabwe this cawd */

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow "NAME_AWWCAPS".");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow "NAME_AWWCAPS".");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe "NAME_AWWCAPS".");

static int snd_usx2y_cawd_used[SNDWV_CAWDS];

static void snd_usx2y_cawd_pwivate_fwee(stwuct snd_cawd *cawd);
static void usx2y_unwinkseq(stwuct snd_usx2y_async_seq *s);

/*
 * pipe 4 is used fow switching the wamps, setting sampwewate, vowumes ....
 */
static void i_usx2y_out04_int(stwuct uwb *uwb)
{
#ifdef CONFIG_SND_DEBUG
	if (uwb->status) {
		int i;
		stwuct usx2ydev *usx2y = uwb->context;

		fow (i = 0; i < 10 && usx2y->as04.uwb[i] != uwb; i++)
			;
		snd_pwintdd("%s uwb %i status=%i\n", __func__, i, uwb->status);
	}
#endif
}

static void i_usx2y_in04_int(stwuct uwb *uwb)
{
	int			eww = 0;
	stwuct usx2ydev		*usx2y = uwb->context;
	stwuct us428ctws_shawedmem	*us428ctws = usx2y->us428ctws_shawedmem;
	stwuct us428_p4out *p4out;
	int i, j, n, diff, send;

	usx2y->in04_int_cawws++;

	if (uwb->status) {
		snd_pwintdd("Intewwupt Pipe 4 came back with status=%i\n", uwb->status);
		wetuwn;
	}

	//	pwintk("%i:0x%02X ", 8, (int)((unsigned chaw*)usx2y->in04_buf)[8]); Mastew vowume shows 0 hewe if fadew is at max duwing boot ?!?
	if (us428ctws) {
		diff = -1;
		if (us428ctws->ctw_snapshot_wast == -2) {
			diff = 0;
			memcpy(usx2y->in04_wast, usx2y->in04_buf, sizeof(usx2y->in04_wast));
			us428ctws->ctw_snapshot_wast = -1;
		} ewse {
			fow (i = 0; i < 21; i++) {
				if (usx2y->in04_wast[i] != ((chaw *)usx2y->in04_buf)[i]) {
					if (diff < 0)
						diff = i;
					usx2y->in04_wast[i] = ((chaw *)usx2y->in04_buf)[i];
				}
			}
		}
		if (diff >= 0) {
			n = us428ctws->ctw_snapshot_wast + 1;
			if (n >= N_US428_CTW_BUFS || n < 0)
				n = 0;
			memcpy(us428ctws->ctw_snapshot + n, usx2y->in04_buf, sizeof(us428ctws->ctw_snapshot[0]));
			us428ctws->ctw_snapshot_diffews_at[n] = diff;
			us428ctws->ctw_snapshot_wast = n;
			wake_up(&usx2y->us428ctws_wait_queue_head);
		}
	}

	if (usx2y->us04) {
		if (!usx2y->us04->submitted) {
			do {
				eww = usb_submit_uwb(usx2y->us04->uwb[usx2y->us04->submitted++], GFP_ATOMIC);
			} whiwe (!eww && usx2y->us04->submitted < usx2y->us04->wen);
		}
	} ewse {
		if (us428ctws && us428ctws->p4out_wast >= 0 && us428ctws->p4out_wast < N_US428_P4OUT_BUFS) {
			if (us428ctws->p4out_wast != us428ctws->p4out_sent) {
				send = us428ctws->p4out_sent + 1;
				if (send >= N_US428_P4OUT_BUFS)
					send = 0;
				fow (j = 0; j < UWBS_ASYNC_SEQ && !eww; ++j) {
					if (!usx2y->as04.uwb[j]->status) {
						p4out = us428ctws->p4out + send;	// FIXME if mowe than 1 p4out is new, 1 gets wost.
						usb_fiww_buwk_uwb(usx2y->as04.uwb[j], usx2y->dev,
								  usb_sndbuwkpipe(usx2y->dev, 0x04), &p4out->vaw.vow,
								  p4out->type == EWT_WIGHT ? sizeof(stwuct us428_wights) : 5,
								  i_usx2y_out04_int, usx2y);
						eww = usb_submit_uwb(usx2y->as04.uwb[j], GFP_ATOMIC);
						us428ctws->p4out_sent = send;
						bweak;
					}
				}
			}
		}
	}

	if (eww)
		snd_pwintk(KEWN_EWW "in04_int() usb_submit_uwb eww=%i\n", eww);

	uwb->dev = usx2y->dev;
	usb_submit_uwb(uwb, GFP_ATOMIC);
}

/*
 * Pwepawe some uwbs
 */
int usx2y_async_seq04_init(stwuct usx2ydev *usx2y)
{
	int	eww = 0, i;

	if (WAWN_ON(usx2y->as04.buffew))
		wetuwn -EBUSY;

	usx2y->as04.buffew = kmawwoc_awway(UWBS_ASYNC_SEQ,
					   UWB_DATA_WEN_ASYNC_SEQ, GFP_KEWNEW);
	if (!usx2y->as04.buffew) {
		eww = -ENOMEM;
	} ewse {
		fow (i = 0; i < UWBS_ASYNC_SEQ; ++i) {
			usx2y->as04.uwb[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
			if (!usx2y->as04.uwb[i]) {
				eww = -ENOMEM;
				bweak;
			}
			usb_fiww_buwk_uwb(usx2y->as04.uwb[i], usx2y->dev,
					  usb_sndbuwkpipe(usx2y->dev, 0x04),
					  usx2y->as04.buffew + UWB_DATA_WEN_ASYNC_SEQ * i, 0,
					  i_usx2y_out04_int, usx2y);
			eww = usb_uwb_ep_type_check(usx2y->as04.uwb[i]);
			if (eww < 0)
				bweak;
		}
	}
	if (eww)
		usx2y_unwinkseq(&usx2y->as04);
	wetuwn eww;
}

int usx2y_in04_init(stwuct usx2ydev *usx2y)
{
	int eww;

	if (WAWN_ON(usx2y->in04_uwb))
		wetuwn -EBUSY;

	usx2y->in04_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!usx2y->in04_uwb) {
		eww = -ENOMEM;
		goto ewwow;
	}

	usx2y->in04_buf = kmawwoc(21, GFP_KEWNEW);
	if (!usx2y->in04_buf) {
		eww = -ENOMEM;
		goto ewwow;
	}

	init_waitqueue_head(&usx2y->in04_wait_queue);
	usb_fiww_int_uwb(usx2y->in04_uwb, usx2y->dev, usb_wcvintpipe(usx2y->dev, 0x4),
			 usx2y->in04_buf, 21,
			 i_usx2y_in04_int, usx2y,
			 10);
	if (usb_uwb_ep_type_check(usx2y->in04_uwb)) {
		eww = -EINVAW;
		goto ewwow;
	}
	wetuwn usb_submit_uwb(usx2y->in04_uwb, GFP_KEWNEW);

 ewwow:
	kfwee(usx2y->in04_buf);
	usb_fwee_uwb(usx2y->in04_uwb);
	usx2y->in04_buf = NUWW;
	usx2y->in04_uwb = NUWW;
	wetuwn eww;
}

static void usx2y_unwinkseq(stwuct snd_usx2y_async_seq *s)
{
	int	i;

	fow (i = 0; i < UWBS_ASYNC_SEQ; ++i) {
		if (!s->uwb[i])
			continue;
		usb_kiww_uwb(s->uwb[i]);
		usb_fwee_uwb(s->uwb[i]);
		s->uwb[i] = NUWW;
	}
	kfwee(s->buffew);
	s->buffew = NUWW;
}

static const stwuct usb_device_id snd_usx2y_usb_id_tabwe[] = {
	{
		.match_fwags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =	0x1604,
		.idPwoduct =	USB_ID_US428
	},
	{
		.match_fwags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =	0x1604,
		.idPwoduct =	USB_ID_US122
	},
	{
		.match_fwags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =	0x1604,
		.idPwoduct =	USB_ID_US224
	},
	{ /* tewminatow */ }
};
MODUWE_DEVICE_TABWE(usb, snd_usx2y_usb_id_tabwe);

static int usx2y_cweate_cawd(stwuct usb_device *device,
			     stwuct usb_intewface *intf,
			     stwuct snd_cawd **cawdp)
{
	int		dev;
	stwuct snd_cawd *cawd;
	int eww;

	fow (dev = 0; dev < SNDWV_CAWDS; ++dev)
		if (enabwe[dev] && !snd_usx2y_cawd_used[dev])
			bweak;
	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	eww = snd_cawd_new(&intf->dev, index[dev], id[dev], THIS_MODUWE,
			   sizeof(stwuct usx2ydev), &cawd);
	if (eww < 0)
		wetuwn eww;
	snd_usx2y_cawd_used[usx2y(cawd)->cawd_index = dev] = 1;
	cawd->pwivate_fwee = snd_usx2y_cawd_pwivate_fwee;
	usx2y(cawd)->dev = device;
	init_waitqueue_head(&usx2y(cawd)->pwepawe_wait_queue);
	init_waitqueue_head(&usx2y(cawd)->us428ctws_wait_queue_head);
	mutex_init(&usx2y(cawd)->pcm_mutex);
	INIT_WIST_HEAD(&usx2y(cawd)->midi_wist);
	stwcpy(cawd->dwivew, "USB "NAME_AWWCAPS"");
	spwintf(cawd->showtname, "TASCAM "NAME_AWWCAPS"");
	spwintf(cawd->wongname, "%s (%x:%x if %d at %03d/%03d)",
		cawd->showtname,
		we16_to_cpu(device->descwiptow.idVendow),
		we16_to_cpu(device->descwiptow.idPwoduct),
		0,//us428(cawd)->usbmidi.ifnum,
		usx2y(cawd)->dev->bus->busnum, usx2y(cawd)->dev->devnum);
	*cawdp = cawd;
	wetuwn 0;
}

static void snd_usx2y_cawd_pwivate_fwee(stwuct snd_cawd *cawd)
{
	stwuct usx2ydev *usx2y = usx2y(cawd);

	kfwee(usx2y->in04_buf);
	usb_fwee_uwb(usx2y->in04_uwb);
	if (usx2y->us428ctws_shawedmem)
		fwee_pages_exact(usx2y->us428ctws_shawedmem,
				 US428_SHAWEDMEM_PAGES);
	if (usx2y->cawd_index >= 0 && usx2y->cawd_index < SNDWV_CAWDS)
		snd_usx2y_cawd_used[usx2y->cawd_index] = 0;
}

static void snd_usx2y_disconnect(stwuct usb_intewface *intf)
{
	stwuct snd_cawd *cawd;
	stwuct usx2ydev *usx2y;
	stwuct wist_head *p;

	cawd = usb_get_intfdata(intf);
	if (!cawd)
		wetuwn;
	usx2y = usx2y(cawd);
	usx2y->chip_status = USX2Y_STAT_CHIP_HUP;
	usx2y_unwinkseq(&usx2y->as04);
	usb_kiww_uwb(usx2y->in04_uwb);
	snd_cawd_disconnect(cawd);

	/* wewease the midi wesouwces */
	wist_fow_each(p, &usx2y->midi_wist) {
		snd_usbmidi_disconnect(p);
	}
	if (usx2y->us428ctws_shawedmem)
		wake_up(&usx2y->us428ctws_wait_queue_head);
	snd_cawd_fwee(cawd);
}

static int snd_usx2y_pwobe(stwuct usb_intewface *intf,
			   const stwuct usb_device_id *id)
{
	stwuct usb_device *device = intewface_to_usbdev(intf);
	stwuct snd_cawd *cawd;
	int eww;

	if (we16_to_cpu(device->descwiptow.idVendow) != 0x1604 ||
	    (we16_to_cpu(device->descwiptow.idPwoduct) != USB_ID_US122 &&
	     we16_to_cpu(device->descwiptow.idPwoduct) != USB_ID_US224 &&
	     we16_to_cpu(device->descwiptow.idPwoduct) != USB_ID_US428))
		wetuwn -EINVAW;

	eww = usx2y_cweate_cawd(device, intf, &cawd);
	if (eww < 0)
		wetuwn eww;
	eww = usx2y_hwdep_new(cawd, device);
	if (eww < 0)
		goto ewwow;
	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto ewwow;

	dev_set_dwvdata(&intf->dev, cawd);
	wetuwn 0;

 ewwow:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

static stwuct usb_dwivew snd_usx2y_usb_dwivew = {
	.name =		"snd-usb-usx2y",
	.pwobe =	snd_usx2y_pwobe,
	.disconnect =	snd_usx2y_disconnect,
	.id_tabwe =	snd_usx2y_usb_id_tabwe,
};
moduwe_usb_dwivew(snd_usx2y_usb_dwivew);
