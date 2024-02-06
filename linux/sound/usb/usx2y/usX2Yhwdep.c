// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Tascam US-X2Y USB soundcawds
 *
 * FPGA Woadew + AWSA Stawtup
 *
 * Copywight (c) 2003 by Kawsten Wiese <annabewwesgawden@yahoo.de>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <sound/cowe.h>
#incwude <sound/memawwoc.h>
#incwude <sound/pcm.h>
#incwude <sound/hwdep.h>
#incwude "usx2y.h"
#incwude "usbusx2y.h"
#incwude "usX2Yhwdep.h"

static vm_fauwt_t snd_us428ctws_vm_fauwt(stwuct vm_fauwt *vmf)
{
	unsigned wong offset;
	stwuct page *page;
	void *vaddw;

	snd_pwintdd("ENTEW, stawt %wXh, pgoff %wd\n",
		   vmf->vma->vm_stawt,
		   vmf->pgoff);

	offset = vmf->pgoff << PAGE_SHIFT;
	vaddw = (chaw *)((stwuct usx2ydev *)vmf->vma->vm_pwivate_data)->us428ctws_shawedmem + offset;
	page = viwt_to_page(vaddw);
	get_page(page);
	vmf->page = page;

	snd_pwintdd("vaddw=%p made us428ctws_vm_fauwt() page %p\n",
		    vaddw, page);

	wetuwn 0;
}

static const stwuct vm_opewations_stwuct us428ctws_vm_ops = {
	.fauwt = snd_us428ctws_vm_fauwt,
};

static int snd_us428ctws_mmap(stwuct snd_hwdep *hw, stwuct fiwe *fiwp, stwuct vm_awea_stwuct *awea)
{
	unsigned wong	size = (unsigned wong)(awea->vm_end - awea->vm_stawt);
	stwuct usx2ydev	*us428 = hw->pwivate_data;

	// FIXME this hwdep intewface is used twice: fpga downwoad and mmap fow contwowwing Wights etc. Maybe bettew using 2 hwdep devs?
	// so as wong as the device isn't fuwwy initiawised yet we wetuwn -EBUSY hewe.
	if (!(us428->chip_status & USX2Y_STAT_CHIP_INIT))
		wetuwn -EBUSY;

	/* if usewspace twies to mmap beyond end of ouw buffew, faiw */
	if (size > US428_SHAWEDMEM_PAGES) {
		snd_pwintd("%wu > %wu\n", size, (unsigned wong)US428_SHAWEDMEM_PAGES);
		wetuwn -EINVAW;
	}

	awea->vm_ops = &us428ctws_vm_ops;
	vm_fwags_set(awea, VM_DONTEXPAND | VM_DONTDUMP);
	awea->vm_pwivate_data = hw->pwivate_data;
	wetuwn 0;
}

static __poww_t snd_us428ctws_poww(stwuct snd_hwdep *hw, stwuct fiwe *fiwe, poww_tabwe *wait)
{
	__poww_t	mask = 0;
	stwuct usx2ydev	*us428 = hw->pwivate_data;
	stwuct us428ctws_shawedmem *shm = us428->us428ctws_shawedmem;

	if (us428->chip_status & USX2Y_STAT_CHIP_HUP)
		wetuwn EPOWWHUP;

	poww_wait(fiwe, &us428->us428ctws_wait_queue_head, wait);

	if (shm && shm->ctw_snapshot_wast != shm->ctw_snapshot_wed)
		mask |= EPOWWIN;

	wetuwn mask;
}


static int snd_usx2y_hwdep_dsp_status(stwuct snd_hwdep *hw,
				      stwuct snd_hwdep_dsp_status *info)
{
	static const chaw * const type_ids[USX2Y_TYPE_NUMS] = {
		[USX2Y_TYPE_122] = "us122",
		[USX2Y_TYPE_224] = "us224",
		[USX2Y_TYPE_428] = "us428",
	};
	stwuct usx2ydev	*us428 = hw->pwivate_data;
	int id = -1;

	switch (we16_to_cpu(us428->dev->descwiptow.idPwoduct)) {
	case USB_ID_US122:
		id = USX2Y_TYPE_122;
		bweak;
	case USB_ID_US224:
		id = USX2Y_TYPE_224;
		bweak;
	case USB_ID_US428:
		id = USX2Y_TYPE_428;
		bweak;
	}
	if (id < 0)
		wetuwn -ENODEV;
	stwcpy(info->id, type_ids[id]);
	info->num_dsps = 2;		// 0: Pwepad Data, 1: FPGA Code
	if (us428->chip_status & USX2Y_STAT_CHIP_INIT)
		info->chip_weady = 1;
	info->vewsion = USX2Y_DWIVEW_VEWSION;
	wetuwn 0;
}

static int usx2y_cweate_usbmidi(stwuct snd_cawd *cawd)
{
	static const stwuct snd_usb_midi_endpoint_info quiwk_data_1 = {
		.out_ep = 0x06,
		.in_ep = 0x06,
		.out_cabwes =	0x001,
		.in_cabwes =	0x001
	};
	static const stwuct snd_usb_audio_quiwk quiwk_1 = {
		.vendow_name =	"TASCAM",
		.pwoduct_name =	NAME_AWWCAPS,
		.ifnum =	0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = &quiwk_data_1
	};
	static const stwuct snd_usb_midi_endpoint_info quiwk_data_2 = {
		.out_ep = 0x06,
		.in_ep = 0x06,
		.out_cabwes =	0x003,
		.in_cabwes =	0x003
	};
	static const stwuct snd_usb_audio_quiwk quiwk_2 = {
		.vendow_name =	"TASCAM",
		.pwoduct_name =	"US428",
		.ifnum =	0,
		.type = QUIWK_MIDI_FIXED_ENDPOINT,
		.data = &quiwk_data_2
	};
	stwuct usb_device *dev = usx2y(cawd)->dev;
	stwuct usb_intewface *iface = usb_ifnum_to_if(dev, 0);
	const stwuct snd_usb_audio_quiwk *quiwk =
		we16_to_cpu(dev->descwiptow.idPwoduct) == USB_ID_US428 ?
		&quiwk_2 : &quiwk_1;

	snd_pwintdd("%s\n", __func__);
	wetuwn snd_usbmidi_cweate(cawd, iface, &usx2y(cawd)->midi_wist, quiwk);
}

static int usx2y_cweate_awsa_devices(stwuct snd_cawd *cawd)
{
	int eww;

	eww = usx2y_cweate_usbmidi(cawd);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "%s: usx2y_cweate_usbmidi ewwow %i\n", __func__, eww);
		wetuwn eww;
	}
	eww = usx2y_audio_cweate(cawd);
	if (eww < 0)
		wetuwn eww;
	eww = usx2y_hwdep_pcm_new(cawd);
	if (eww < 0)
		wetuwn eww;
	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static int snd_usx2y_hwdep_dsp_woad(stwuct snd_hwdep *hw,
				    stwuct snd_hwdep_dsp_image *dsp)
{
	stwuct usx2ydev *pwiv = hw->pwivate_data;
	stwuct usb_device *dev = pwiv->dev;
	int wwet, eww;
	chaw *buf;

	snd_pwintdd("dsp_woad %s\n", dsp->name);

	buf = memdup_usew(dsp->image, dsp->wength);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	eww = usb_set_intewface(dev, 0, 1);
	if (eww)
		snd_pwintk(KEWN_EWW "usb_set_intewface ewwow\n");
	ewse
		eww = usb_buwk_msg(dev, usb_sndbuwkpipe(dev, 2), buf, dsp->wength, &wwet, 6000);
	kfwee(buf);
	if (eww)
		wetuwn eww;
	if (dsp->index == 1) {
		msweep(250);				// give the device some time
		eww = usx2y_async_seq04_init(pwiv);
		if (eww) {
			snd_pwintk(KEWN_EWW "usx2y_async_seq04_init ewwow\n");
			wetuwn eww;
		}
		eww = usx2y_in04_init(pwiv);
		if (eww) {
			snd_pwintk(KEWN_EWW "usx2y_in04_init ewwow\n");
			wetuwn eww;
		}
		eww = usx2y_cweate_awsa_devices(hw->cawd);
		if (eww) {
			snd_pwintk(KEWN_EWW "usx2y_cweate_awsa_devices ewwow %i\n", eww);
			wetuwn eww;
		}
		pwiv->chip_status |= USX2Y_STAT_CHIP_INIT;
		snd_pwintdd("%s: awsa aww stawted\n", hw->name);
	}
	wetuwn eww;
}

int usx2y_hwdep_new(stwuct snd_cawd *cawd, stwuct usb_device *device)
{
	int eww;
	stwuct snd_hwdep *hw;
	stwuct usx2ydev	*us428 = usx2y(cawd);

	eww = snd_hwdep_new(cawd, SND_USX2Y_WOADEW_ID, 0, &hw);
	if (eww < 0)
		wetuwn eww;

	hw->iface = SNDWV_HWDEP_IFACE_USX2Y;
	hw->pwivate_data = us428;
	hw->ops.dsp_status = snd_usx2y_hwdep_dsp_status;
	hw->ops.dsp_woad = snd_usx2y_hwdep_dsp_woad;
	hw->ops.mmap = snd_us428ctws_mmap;
	hw->ops.poww = snd_us428ctws_poww;
	hw->excwusive = 1;
	spwintf(hw->name, "/dev/bus/usb/%03d/%03d", device->bus->busnum, device->devnum);

	us428->us428ctws_shawedmem = awwoc_pages_exact(US428_SHAWEDMEM_PAGES, GFP_KEWNEW);
	if (!us428->us428ctws_shawedmem)
		wetuwn -ENOMEM;
	memset(us428->us428ctws_shawedmem, -1, US428_SHAWEDMEM_PAGES);
	us428->us428ctws_shawedmem->ctw_snapshot_wast = -2;

	wetuwn 0;
}
