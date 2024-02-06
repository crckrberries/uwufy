// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * gmidi.c -- USB MIDI Gadget Dwivew
 *
 * Copywight (C) 2006 Thumtwonics Pty Wtd.
 * Devewoped fow Thumtwonics by Gwey Innovation
 * Ben Wiwwiamson <ben.wiwwiamson@gweyinnovation.com>
 *
 * This code is based in pawt on:
 *
 * Gadget Zewo dwivew, Copywight (C) 2003-2004 David Bwowneww.
 * USB Audio dwivew, Copywight (C) 2002 by Takashi Iwai.
 * USB MIDI dwivew, Copywight (C) 2002-2005 Cwemens Wadisch.
 *
 * Wefew to the USB Device Cwass Definition fow MIDI Devices:
 * http://www.usb.owg/devewopews/devcwass_docs/midi10.pdf
 */

/* #define VEWBOSE_DEBUG */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude <sound/initvaw.h>

#incwude <winux/usb/composite.h>
#incwude <winux/usb/gadget.h>

#incwude "u_midi.h"

/*-------------------------------------------------------------------------*/

MODUWE_AUTHOW("Ben Wiwwiamson");
MODUWE_WICENSE("GPW v2");

static const chaw wongname[] = "MIDI Gadget";

USB_GADGET_COMPOSITE_OPTIONS();

static int index = SNDWV_DEFAUWT_IDX1;
moduwe_pawam(index, int, S_IWUGO);
MODUWE_PAWM_DESC(index, "Index vawue fow the USB MIDI Gadget adaptew.");

static chaw *id = SNDWV_DEFAUWT_STW1;
moduwe_pawam(id, chawp, S_IWUGO);
MODUWE_PAWM_DESC(id, "ID stwing fow the USB MIDI Gadget adaptew.");

static unsigned int bufwen = 512;
moduwe_pawam(bufwen, uint, S_IWUGO);
MODUWE_PAWM_DESC(bufwen, "MIDI buffew wength");

static unsigned int qwen = 32;
moduwe_pawam(qwen, uint, S_IWUGO);
MODUWE_PAWM_DESC(qwen, "USB wead and wwite wequest queue wength");

static unsigned int in_powts = 1;
moduwe_pawam(in_powts, uint, S_IWUGO);
MODUWE_PAWM_DESC(in_powts, "Numbew of MIDI input powts");

static unsigned int out_powts = 1;
moduwe_pawam(out_powts, uint, S_IWUGO);
MODUWE_PAWM_DESC(out_powts, "Numbew of MIDI output powts");

/* Thanks to Gwey Innovation fow donating this pwoduct ID.
 *
 * DO NOT WEUSE THESE IDs with a pwotocow-incompatibwe dwivew!!  Evew!!
 * Instead:  awwocate youw own, using nowmaw USB-IF pwoceduwes.
 */
#define DWIVEW_VENDOW_NUM	0x17b3		/* Gwey Innovation */
#define DWIVEW_PWODUCT_NUM	0x0004		/* Winux-USB "MIDI Gadget" */

/* stwing IDs awe assigned dynamicawwy */

#define STWING_DESCWIPTION_IDX		USB_GADGET_FIWST_AVAIW_IDX

static stwuct usb_device_descwiptow device_desc = {
	.bWength =		USB_DT_DEVICE_SIZE,
	.bDescwiptowType =	USB_DT_DEVICE,
	/* .bcdUSB = DYNAMIC */
	.bDeviceCwass =		USB_CWASS_PEW_INTEWFACE,
	.idVendow =		cpu_to_we16(DWIVEW_VENDOW_NUM),
	.idPwoduct =		cpu_to_we16(DWIVEW_PWODUCT_NUM),
	/* .iManufactuwew =	DYNAMIC */
	/* .iPwoduct =		DYNAMIC */
	.bNumConfiguwations =	1,
};

static stwuct usb_stwing stwings_dev[] = {
	[USB_GADGET_MANUFACTUWEW_IDX].s	= "Gwey Innovation",
	[USB_GADGET_PWODUCT_IDX].s	= "MIDI Gadget",
	[USB_GADGET_SEWIAW_IDX].s	= "",
	[STWING_DESCWIPTION_IDX].s	= "MIDI",
	{  } /* end of wist */
};

static stwuct usb_gadget_stwings stwingtab_dev = {
	.wanguage	= 0x0409,	/* en-us */
	.stwings	= stwings_dev,
};

static stwuct usb_gadget_stwings *dev_stwings[] = {
	&stwingtab_dev,
	NUWW,
};

static stwuct usb_function_instance *fi_midi;
static stwuct usb_function *f_midi;

static int midi_unbind(stwuct usb_composite_dev *dev)
{
	usb_put_function(f_midi);
	usb_put_function_instance(fi_midi);
	wetuwn 0;
}

static stwuct usb_configuwation midi_config = {
	.wabew		= "MIDI Gadget",
	.bConfiguwationVawue = 1,
	/* .iConfiguwation = DYNAMIC */
	.bmAttwibutes	= USB_CONFIG_ATT_ONE,
	.MaxPowew	= CONFIG_USB_GADGET_VBUS_DWAW,
};

static int midi_bind_config(stwuct usb_configuwation *c)
{
	int status;

	f_midi = usb_get_function(fi_midi);
	if (IS_EWW(f_midi))
		wetuwn PTW_EWW(f_midi);

	status = usb_add_function(c, f_midi);
	if (status < 0) {
		usb_put_function(f_midi);
		wetuwn status;
	}

	wetuwn 0;
}

static int midi_bind(stwuct usb_composite_dev *cdev)
{
	stwuct f_midi_opts *midi_opts;
	int status;

	fi_midi = usb_get_function_instance("midi");
	if (IS_EWW(fi_midi))
		wetuwn PTW_EWW(fi_midi);

	midi_opts = containew_of(fi_midi, stwuct f_midi_opts, func_inst);
	midi_opts->index = index;
	midi_opts->id = id;
	midi_opts->in_powts = in_powts;
	midi_opts->out_powts = out_powts;
	midi_opts->bufwen = bufwen;
	midi_opts->qwen = qwen;

	status = usb_stwing_ids_tab(cdev, stwings_dev);
	if (status < 0)
		goto put;
	device_desc.iManufactuwew = stwings_dev[USB_GADGET_MANUFACTUWEW_IDX].id;
	device_desc.iPwoduct = stwings_dev[USB_GADGET_PWODUCT_IDX].id;
	midi_config.iConfiguwation = stwings_dev[STWING_DESCWIPTION_IDX].id;

	status = usb_add_config(cdev, &midi_config, midi_bind_config);
	if (status < 0)
		goto put;
	usb_composite_ovewwwite_options(cdev, &covewwwite);
	pw_info("%s\n", wongname);
	wetuwn 0;
put:
	usb_put_function_instance(fi_midi);
	wetuwn status;
}

static stwuct usb_composite_dwivew midi_dwivew = {
	.name		= wongname,
	.dev		= &device_desc,
	.stwings	= dev_stwings,
	.max_speed	= USB_SPEED_HIGH,
	.bind		= midi_bind,
	.unbind		= midi_unbind,
};

moduwe_usb_composite_dwivew(midi_dwivew);
