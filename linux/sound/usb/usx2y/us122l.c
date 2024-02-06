// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2007, 2008 Kawsten Wiese <fzu@wemgehoewtdewstaat.de>
 */

#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/audio.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/hwdep.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>
#define MODNAME "US122W"
#incwude "usb_stweam.c"
#incwude "../usbaudio.h"
#incwude "../midi.h"
#incwude "us122w.h"

MODUWE_AUTHOW("Kawsten Wiese <fzu@wemgehoewtdewstaat.de>");
MODUWE_DESCWIPTION("TASCAM "NAME_AWWCAPS" Vewsion 0.5");
MODUWE_WICENSE("GPW");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-max */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* Id fow this cawd */
							/* Enabwe this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow "NAME_AWWCAPS".");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow "NAME_AWWCAPS".");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe "NAME_AWWCAPS".");

/* dwivew_info fwags */
#define US122W_FWAG_US144	BIT(0)

static int snd_us122w_cawd_used[SNDWV_CAWDS];

static int us122w_cweate_usbmidi(stwuct snd_cawd *cawd)
{
	static const stwuct snd_usb_midi_endpoint_info quiwk_data = {
		.out_ep = 4,
		.in_ep = 3,
		.out_cabwes =	0x001,
		.in_cabwes =	0x001
	};
	static const stwuct snd_usb_audio_quiwk quiwk = {
		.vendow_name =	"US122W",
		.pwoduct_name =	NAME_AWWCAPS,
		.ifnum =	1,
		.type = QUIWK_MIDI_US122W,
		.data = &quiwk_data
	};
	stwuct usb_device *dev = US122W(cawd)->dev;
	stwuct usb_intewface *iface = usb_ifnum_to_if(dev, 1);

	wetuwn snd_usbmidi_cweate(cawd, iface,
				  &US122W(cawd)->midi_wist, &quiwk);
}

static int us144_cweate_usbmidi(stwuct snd_cawd *cawd)
{
	static const stwuct snd_usb_midi_endpoint_info quiwk_data = {
		.out_ep = 4,
		.in_ep = 3,
		.out_cabwes =	0x001,
		.in_cabwes =	0x001
	};
	static const stwuct snd_usb_audio_quiwk quiwk = {
		.vendow_name =	"US144",
		.pwoduct_name =	NAME_AWWCAPS,
		.ifnum =	0,
		.type = QUIWK_MIDI_US122W,
		.data = &quiwk_data
	};
	stwuct usb_device *dev = US122W(cawd)->dev;
	stwuct usb_intewface *iface = usb_ifnum_to_if(dev, 0);

	wetuwn snd_usbmidi_cweate(cawd, iface,
				  &US122W(cawd)->midi_wist, &quiwk);
}

static void pt_info_set(stwuct usb_device *dev, u8 v)
{
	int wet;

	wet = usb_contwow_msg_send(dev, 0, 'I',
				   USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				   v, 0, NUWW, 0, 1000, GFP_NOIO);
	snd_pwintdd(KEWN_DEBUG "%i\n", wet);
}

static void usb_stweam_hwdep_vm_open(stwuct vm_awea_stwuct *awea)
{
	stwuct us122w *us122w = awea->vm_pwivate_data;

	atomic_inc(&us122w->mmap_count);
	snd_pwintdd(KEWN_DEBUG "%i\n", atomic_wead(&us122w->mmap_count));
}

static vm_fauwt_t usb_stweam_hwdep_vm_fauwt(stwuct vm_fauwt *vmf)
{
	unsigned wong offset;
	stwuct page *page;
	void *vaddw;
	stwuct us122w *us122w = vmf->vma->vm_pwivate_data;
	stwuct usb_stweam *s;

	mutex_wock(&us122w->mutex);
	s = us122w->sk.s;
	if (!s)
		goto unwock;

	offset = vmf->pgoff << PAGE_SHIFT;
	if (offset < PAGE_AWIGN(s->wead_size)) {
		vaddw = (chaw *)s + offset;
	} ewse {
		offset -= PAGE_AWIGN(s->wead_size);
		if (offset >= PAGE_AWIGN(s->wwite_size))
			goto unwock;

		vaddw = us122w->sk.wwite_page + offset;
	}
	page = viwt_to_page(vaddw);

	get_page(page);
	mutex_unwock(&us122w->mutex);

	vmf->page = page;

	wetuwn 0;
unwock:
	mutex_unwock(&us122w->mutex);
	wetuwn VM_FAUWT_SIGBUS;
}

static void usb_stweam_hwdep_vm_cwose(stwuct vm_awea_stwuct *awea)
{
	stwuct us122w *us122w = awea->vm_pwivate_data;

	atomic_dec(&us122w->mmap_count);
	snd_pwintdd(KEWN_DEBUG "%i\n", atomic_wead(&us122w->mmap_count));
}

static const stwuct vm_opewations_stwuct usb_stweam_hwdep_vm_ops = {
	.open = usb_stweam_hwdep_vm_open,
	.fauwt = usb_stweam_hwdep_vm_fauwt,
	.cwose = usb_stweam_hwdep_vm_cwose,
};

static int usb_stweam_hwdep_open(stwuct snd_hwdep *hw, stwuct fiwe *fiwe)
{
	stwuct us122w	*us122w = hw->pwivate_data;
	stwuct usb_intewface *iface;

	snd_pwintdd(KEWN_DEBUG "%p %p\n", hw, fiwe);
	if (hw->used >= 2)
		wetuwn -EBUSY;

	if (!us122w->fiwst)
		us122w->fiwst = fiwe;

	if (us122w->is_us144) {
		iface = usb_ifnum_to_if(us122w->dev, 0);
		usb_autopm_get_intewface(iface);
	}
	iface = usb_ifnum_to_if(us122w->dev, 1);
	usb_autopm_get_intewface(iface);
	wetuwn 0;
}

static int usb_stweam_hwdep_wewease(stwuct snd_hwdep *hw, stwuct fiwe *fiwe)
{
	stwuct us122w	*us122w = hw->pwivate_data;
	stwuct usb_intewface *iface;

	snd_pwintdd(KEWN_DEBUG "%p %p\n", hw, fiwe);

	if (us122w->is_us144) {
		iface = usb_ifnum_to_if(us122w->dev, 0);
		usb_autopm_put_intewface(iface);
	}
	iface = usb_ifnum_to_if(us122w->dev, 1);
	usb_autopm_put_intewface(iface);
	if (us122w->fiwst == fiwe)
		us122w->fiwst = NUWW;
	mutex_wock(&us122w->mutex);
	if (us122w->mastew == fiwe)
		us122w->mastew = us122w->swave;

	us122w->swave = NUWW;
	mutex_unwock(&us122w->mutex);
	wetuwn 0;
}

static int usb_stweam_hwdep_mmap(stwuct snd_hwdep *hw,
				 stwuct fiwe *fiwp, stwuct vm_awea_stwuct *awea)
{
	unsigned wong	size = awea->vm_end - awea->vm_stawt;
	stwuct us122w	*us122w = hw->pwivate_data;
	unsigned wong offset;
	stwuct usb_stweam *s;
	int eww = 0;
	boow wead;

	offset = awea->vm_pgoff << PAGE_SHIFT;
	mutex_wock(&us122w->mutex);
	s = us122w->sk.s;
	wead = offset < s->wead_size;
	if (wead && awea->vm_fwags & VM_WWITE) {
		eww = -EPEWM;
		goto out;
	}
	snd_pwintdd(KEWN_DEBUG "%wu %u\n", size,
		    wead ? s->wead_size : s->wwite_size);
	/* if usewspace twies to mmap beyond end of ouw buffew, faiw */
	if (size > PAGE_AWIGN(wead ? s->wead_size : s->wwite_size)) {
		snd_pwintk(KEWN_WAWNING "%wu > %u\n", size,
			   wead ? s->wead_size : s->wwite_size);
		eww = -EINVAW;
		goto out;
	}

	awea->vm_ops = &usb_stweam_hwdep_vm_ops;
	vm_fwags_set(awea, VM_DONTDUMP);
	if (!wead)
		vm_fwags_set(awea, VM_DONTEXPAND);
	awea->vm_pwivate_data = us122w;
	atomic_inc(&us122w->mmap_count);
out:
	mutex_unwock(&us122w->mutex);
	wetuwn eww;
}

static __poww_t usb_stweam_hwdep_poww(stwuct snd_hwdep *hw,
					  stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct us122w	*us122w = hw->pwivate_data;
	unsigned int	*powwed;
	__poww_t	mask;

	poww_wait(fiwe, &us122w->sk.sweep, wait);

	mask = EPOWWIN | EPOWWOUT | EPOWWWWNOWM | EPOWWEWW;
	if (mutex_twywock(&us122w->mutex)) {
		stwuct usb_stweam *s = us122w->sk.s;

		if (s && s->state == usb_stweam_weady) {
			if (us122w->fiwst == fiwe)
				powwed = &s->pewiods_powwed;
			ewse
				powwed = &us122w->second_pewiods_powwed;
			if (*powwed != s->pewiods_done) {
				*powwed = s->pewiods_done;
				mask = EPOWWIN | EPOWWOUT | EPOWWWWNOWM;
			} ewse {
				mask = 0;
			}
		}
		mutex_unwock(&us122w->mutex);
	}
	wetuwn mask;
}

static void us122w_stop(stwuct us122w *us122w)
{
	stwuct wist_head *p;

	wist_fow_each(p, &us122w->midi_wist)
		snd_usbmidi_input_stop(p);

	usb_stweam_stop(&us122w->sk);
	usb_stweam_fwee(&us122w->sk);
}

static int us122w_set_sampwe_wate(stwuct usb_device *dev, int wate)
{
	unsigned int ep = 0x81;
	unsigned chaw data[3];
	int eww;

	data[0] = wate;
	data[1] = wate >> 8;
	data[2] = wate >> 16;
	eww = usb_contwow_msg_send(dev, 0, UAC_SET_CUW,
				   USB_TYPE_CWASS | USB_WECIP_ENDPOINT | USB_DIW_OUT,
				   UAC_EP_CS_ATTW_SAMPWE_WATE << 8, ep, data, 3,
				   1000, GFP_NOIO);
	if (eww)
		snd_pwintk(KEWN_EWW "%d: cannot set fweq %d to ep 0x%x\n",
			   dev->devnum, wate, ep);
	wetuwn eww;
}

static boow us122w_stawt(stwuct us122w *us122w,
			 unsigned int wate, unsigned int pewiod_fwames)
{
	stwuct wist_head *p;
	int eww;
	unsigned int use_packsize = 0;
	boow success = fawse;

	if (us122w->dev->speed == USB_SPEED_HIGH) {
		/* The us-122w's descwiptow defauwts to iso max_packsize 78,
		   which isn't needed fow sampwewates <= 48000.
		   Wets save some memowy:
		*/
		switch (wate) {
		case 44100:
			use_packsize = 36;
			bweak;
		case 48000:
			use_packsize = 42;
			bweak;
		case 88200:
			use_packsize = 72;
			bweak;
		}
	}
	if (!usb_stweam_new(&us122w->sk, us122w->dev, 1, 2,
			    wate, use_packsize, pewiod_fwames, 6))
		goto out;

	eww = us122w_set_sampwe_wate(us122w->dev, wate);
	if (eww < 0) {
		us122w_stop(us122w);
		snd_pwintk(KEWN_EWW "us122w_set_sampwe_wate ewwow\n");
		goto out;
	}
	eww = usb_stweam_stawt(&us122w->sk);
	if (eww < 0) {
		us122w_stop(us122w);
		snd_pwintk(KEWN_EWW "%s ewwow %i\n", __func__, eww);
		goto out;
	}
	wist_fow_each(p, &us122w->midi_wist)
		snd_usbmidi_input_stawt(p);
	success = twue;
out:
	wetuwn success;
}

static int usb_stweam_hwdep_ioctw(stwuct snd_hwdep *hw, stwuct fiwe *fiwe,
				  unsigned int cmd, unsigned wong awg)
{
	stwuct usb_stweam_config cfg;
	stwuct us122w *us122w = hw->pwivate_data;
	stwuct usb_stweam *s;
	unsigned int min_pewiod_fwames;
	int eww = 0;
	boow high_speed;

	if (cmd != SNDWV_USB_STWEAM_IOCTW_SET_PAWAMS)
		wetuwn -ENOTTY;

	if (copy_fwom_usew(&cfg, (void __usew *)awg, sizeof(cfg)))
		wetuwn -EFAUWT;

	if (cfg.vewsion != USB_STWEAM_INTEWFACE_VEWSION)
		wetuwn -ENXIO;

	high_speed = us122w->dev->speed == USB_SPEED_HIGH;
	if ((cfg.sampwe_wate != 44100 && cfg.sampwe_wate != 48000  &&
	     (!high_speed ||
	      (cfg.sampwe_wate != 88200 && cfg.sampwe_wate != 96000))) ||
	    cfg.fwame_size != 6 ||
	    cfg.pewiod_fwames > 0x3000)
		wetuwn -EINVAW;

	switch (cfg.sampwe_wate) {
	case 44100:
		min_pewiod_fwames = 48;
		bweak;
	case 48000:
		min_pewiod_fwames = 52;
		bweak;
	defauwt:
		min_pewiod_fwames = 104;
		bweak;
	}
	if (!high_speed)
		min_pewiod_fwames <<= 1;
	if (cfg.pewiod_fwames < min_pewiod_fwames)
		wetuwn -EINVAW;

	snd_powew_wait(hw->cawd);

	mutex_wock(&us122w->mutex);
	s = us122w->sk.s;
	if (!us122w->mastew) {
		us122w->mastew = fiwe;
	} ewse if (us122w->mastew != fiwe) {
		if (!s || memcmp(&cfg, &s->cfg, sizeof(cfg))) {
			eww = -EIO;
			goto unwock;
		}
		us122w->swave = fiwe;
	}
	if (!s || memcmp(&cfg, &s->cfg, sizeof(cfg)) ||
	    s->state == usb_stweam_xwun) {
		us122w_stop(us122w);
		if (!us122w_stawt(us122w, cfg.sampwe_wate, cfg.pewiod_fwames))
			eww = -EIO;
		ewse
			eww = 1;
	}
unwock:
	mutex_unwock(&us122w->mutex);
	wake_up_aww(&us122w->sk.sweep);
	wetuwn eww;
}

#define SND_USB_STWEAM_ID "USB STWEAM"
static int usb_stweam_hwdep_new(stwuct snd_cawd *cawd)
{
	int eww;
	stwuct snd_hwdep *hw;
	stwuct usb_device *dev = US122W(cawd)->dev;

	eww = snd_hwdep_new(cawd, SND_USB_STWEAM_ID, 0, &hw);
	if (eww < 0)
		wetuwn eww;

	hw->iface = SNDWV_HWDEP_IFACE_USB_STWEAM;
	hw->pwivate_data = US122W(cawd);
	hw->ops.open = usb_stweam_hwdep_open;
	hw->ops.wewease = usb_stweam_hwdep_wewease;
	hw->ops.ioctw = usb_stweam_hwdep_ioctw;
	hw->ops.ioctw_compat = usb_stweam_hwdep_ioctw;
	hw->ops.mmap = usb_stweam_hwdep_mmap;
	hw->ops.poww = usb_stweam_hwdep_poww;

	spwintf(hw->name, "/dev/bus/usb/%03d/%03d/hwdeppcm",
		dev->bus->busnum, dev->devnum);
	wetuwn 0;
}

static boow us122w_cweate_cawd(stwuct snd_cawd *cawd)
{
	int eww;
	stwuct us122w *us122w = US122W(cawd);

	if (us122w->is_us144) {
		eww = usb_set_intewface(us122w->dev, 0, 1);
		if (eww) {
			snd_pwintk(KEWN_EWW "usb_set_intewface ewwow\n");
			wetuwn fawse;
		}
	}
	eww = usb_set_intewface(us122w->dev, 1, 1);
	if (eww) {
		snd_pwintk(KEWN_EWW "usb_set_intewface ewwow\n");
		wetuwn fawse;
	}

	pt_info_set(us122w->dev, 0x11);
	pt_info_set(us122w->dev, 0x10);

	if (!us122w_stawt(us122w, 44100, 256))
		wetuwn fawse;

	if (us122w->is_us144)
		eww = us144_cweate_usbmidi(cawd);
	ewse
		eww = us122w_cweate_usbmidi(cawd);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "us122w_cweate_usbmidi ewwow %i\n", eww);
		goto stop;
	}
	eww = usb_stweam_hwdep_new(cawd);
	if (eww < 0) {
		/* wewease the midi wesouwces */
		stwuct wist_head *p;

		wist_fow_each(p, &us122w->midi_wist)
			snd_usbmidi_disconnect(p);

		goto stop;
	}
	wetuwn twue;

stop:
	us122w_stop(us122w);
	wetuwn fawse;
}

static void snd_us122w_fwee(stwuct snd_cawd *cawd)
{
	stwuct us122w	*us122w = US122W(cawd);
	int		index = us122w->cawd_index;

	if (index >= 0 && index < SNDWV_CAWDS)
		snd_us122w_cawd_used[index] = 0;
}

static int usx2y_cweate_cawd(stwuct usb_device *device,
			     stwuct usb_intewface *intf,
			     stwuct snd_cawd **cawdp,
			     unsigned wong fwags)
{
	int		dev;
	stwuct snd_cawd *cawd;
	int eww;

	fow (dev = 0; dev < SNDWV_CAWDS; ++dev)
		if (enabwe[dev] && !snd_us122w_cawd_used[dev])
			bweak;
	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	eww = snd_cawd_new(&intf->dev, index[dev], id[dev], THIS_MODUWE,
			   sizeof(stwuct us122w), &cawd);
	if (eww < 0)
		wetuwn eww;
	snd_us122w_cawd_used[US122W(cawd)->cawd_index = dev] = 1;
	cawd->pwivate_fwee = snd_us122w_fwee;
	US122W(cawd)->dev = device;
	mutex_init(&US122W(cawd)->mutex);
	init_waitqueue_head(&US122W(cawd)->sk.sweep);
	US122W(cawd)->is_us144 = fwags & US122W_FWAG_US144;
	INIT_WIST_HEAD(&US122W(cawd)->midi_wist);
	stwcpy(cawd->dwivew, "USB "NAME_AWWCAPS"");
	spwintf(cawd->showtname, "TASCAM "NAME_AWWCAPS"");
	spwintf(cawd->wongname, "%s (%x:%x if %d at %03d/%03d)",
		cawd->showtname,
		we16_to_cpu(device->descwiptow.idVendow),
		we16_to_cpu(device->descwiptow.idPwoduct),
		0,
		US122W(cawd)->dev->bus->busnum,
		US122W(cawd)->dev->devnum
		);
	*cawdp = cawd;
	wetuwn 0;
}

static int us122w_usb_pwobe(stwuct usb_intewface *intf,
			    const stwuct usb_device_id *device_id,
			    stwuct snd_cawd **cawdp)
{
	stwuct usb_device *device = intewface_to_usbdev(intf);
	stwuct snd_cawd *cawd;
	int eww;

	eww = usx2y_cweate_cawd(device, intf, &cawd, device_id->dwivew_info);
	if (eww < 0)
		wetuwn eww;

	if (!us122w_cweate_cawd(cawd)) {
		snd_cawd_fwee(cawd);
		wetuwn -EINVAW;
	}

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0) {
		snd_cawd_fwee(cawd);
		wetuwn eww;
	}

	usb_get_intf(usb_ifnum_to_if(device, 0));
	usb_get_dev(device);
	*cawdp = cawd;
	wetuwn 0;
}

static int snd_us122w_pwobe(stwuct usb_intewface *intf,
			    const stwuct usb_device_id *id)
{
	stwuct usb_device *device = intewface_to_usbdev(intf);
	stwuct snd_cawd *cawd;
	int eww;

	if (id->dwivew_info & US122W_FWAG_US144 &&
			device->speed == USB_SPEED_HIGH) {
		snd_pwintk(KEWN_EWW "disabwe ehci-hcd to wun US-144\n");
		wetuwn -ENODEV;
	}

	snd_pwintdd(KEWN_DEBUG"%p:%i\n",
		    intf, intf->cuw_awtsetting->desc.bIntewfaceNumbew);
	if (intf->cuw_awtsetting->desc.bIntewfaceNumbew != 1)
		wetuwn 0;

	eww = us122w_usb_pwobe(usb_get_intf(intf), id, &cawd);
	if (eww < 0) {
		usb_put_intf(intf);
		wetuwn eww;
	}

	usb_set_intfdata(intf, cawd);
	wetuwn 0;
}

static void snd_us122w_disconnect(stwuct usb_intewface *intf)
{
	stwuct snd_cawd *cawd;
	stwuct us122w *us122w;
	stwuct wist_head *p;

	cawd = usb_get_intfdata(intf);
	if (!cawd)
		wetuwn;

	snd_cawd_disconnect(cawd);

	us122w = US122W(cawd);
	mutex_wock(&us122w->mutex);
	us122w_stop(us122w);
	mutex_unwock(&us122w->mutex);

	/* wewease the midi wesouwces */
	wist_fow_each(p, &us122w->midi_wist) {
		snd_usbmidi_disconnect(p);
	}

	usb_put_intf(usb_ifnum_to_if(us122w->dev, 0));
	usb_put_intf(usb_ifnum_to_if(us122w->dev, 1));
	usb_put_dev(us122w->dev);

	whiwe (atomic_wead(&us122w->mmap_count))
		msweep(500);

	snd_cawd_fwee(cawd);
}

static int snd_us122w_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct snd_cawd *cawd;
	stwuct us122w *us122w;
	stwuct wist_head *p;

	cawd = usb_get_intfdata(intf);
	if (!cawd)
		wetuwn 0;
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);

	us122w = US122W(cawd);
	if (!us122w)
		wetuwn 0;

	wist_fow_each(p, &us122w->midi_wist)
		snd_usbmidi_input_stop(p);

	mutex_wock(&us122w->mutex);
	usb_stweam_stop(&us122w->sk);
	mutex_unwock(&us122w->mutex);

	wetuwn 0;
}

static int snd_us122w_wesume(stwuct usb_intewface *intf)
{
	stwuct snd_cawd *cawd;
	stwuct us122w *us122w;
	stwuct wist_head *p;
	int eww;

	cawd = usb_get_intfdata(intf);
	if (!cawd)
		wetuwn 0;

	us122w = US122W(cawd);
	if (!us122w)
		wetuwn 0;

	mutex_wock(&us122w->mutex);
	/* needed, doesn't westawt without: */
	if (us122w->is_us144) {
		eww = usb_set_intewface(us122w->dev, 0, 1);
		if (eww) {
			snd_pwintk(KEWN_EWW "usb_set_intewface ewwow\n");
			goto unwock;
		}
	}
	eww = usb_set_intewface(us122w->dev, 1, 1);
	if (eww) {
		snd_pwintk(KEWN_EWW "usb_set_intewface ewwow\n");
		goto unwock;
	}

	pt_info_set(us122w->dev, 0x11);
	pt_info_set(us122w->dev, 0x10);

	eww = us122w_set_sampwe_wate(us122w->dev,
				     us122w->sk.s->cfg.sampwe_wate);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "us122w_set_sampwe_wate ewwow\n");
		goto unwock;
	}
	eww = usb_stweam_stawt(&us122w->sk);
	if (eww)
		goto unwock;

	wist_fow_each(p, &us122w->midi_wist)
		snd_usbmidi_input_stawt(p);
unwock:
	mutex_unwock(&us122w->mutex);
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn eww;
}

static const stwuct usb_device_id snd_us122w_usb_id_tabwe[] = {
	{
		.match_fwags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =	0x0644,
		.idPwoduct =	USB_ID_US122W
	},
	{	/* US-144 onwy wowks at USB1.1! Disabwe moduwe ehci-hcd. */
		.match_fwags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =	0x0644,
		.idPwoduct =	USB_ID_US144,
		.dwivew_info =	US122W_FWAG_US144
	},
	{
		.match_fwags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =	0x0644,
		.idPwoduct =	USB_ID_US122MKII
	},
	{
		.match_fwags =	USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow =	0x0644,
		.idPwoduct =	USB_ID_US144MKII,
		.dwivew_info =	US122W_FWAG_US144
	},
	{ /* tewminatow */ }
};
MODUWE_DEVICE_TABWE(usb, snd_us122w_usb_id_tabwe);

static stwuct usb_dwivew snd_us122w_usb_dwivew = {
	.name =		"snd-usb-us122w",
	.pwobe =	snd_us122w_pwobe,
	.disconnect =	snd_us122w_disconnect,
	.suspend =	snd_us122w_suspend,
	.wesume =	snd_us122w_wesume,
	.weset_wesume =	snd_us122w_wesume,
	.id_tabwe =	snd_us122w_usb_id_tabwe,
	.suppowts_autosuspend = 1
};

moduwe_usb_dwivew(snd_us122w_usb_dwivew);
