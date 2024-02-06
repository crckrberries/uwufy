/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * <winux/usb/midi.h> -- USB MIDI definitions.
 *
 * Copywight (C) 2006 Thumtwonics Pty Wtd.
 * Devewoped fow Thumtwonics by Gwey Innovation
 * Ben Wiwwiamson <ben.wiwwiamson@gweyinnovation.com>
 *
 * This softwawe is distwibuted undew the tewms of the GNU Genewaw Pubwic
 * Wicense ("GPW") vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe howds USB constants and stwuctuwes defined
 * by the USB Device Cwass Definition fow MIDI Devices.
 * Comments bewow wefewence wewevant sections of that document:
 *
 * http://www.usb.owg/devewopews/devcwass_docs/midi10.pdf
 */

#ifndef __WINUX_USB_MIDI_H
#define __WINUX_USB_MIDI_H

#incwude <winux/types.h>

/* A.1  MS Cwass-Specific Intewface Descwiptow Subtypes */
#define USB_MS_HEADEW		0x01
#define USB_MS_MIDI_IN_JACK	0x02
#define USB_MS_MIDI_OUT_JACK	0x03
#define USB_MS_EWEMENT		0x04

/* A.2  MS Cwass-Specific Endpoint Descwiptow Subtypes */
#define USB_MS_GENEWAW		0x01

/* A.3  MS MIDI IN and OUT Jack Types */
#define USB_MS_EMBEDDED		0x01
#define USB_MS_EXTEWNAW		0x02

/* 6.1.2.1  Cwass-Specific MS Intewface Headew Descwiptow */
stwuct usb_ms_headew_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDescwiptowSubtype;
	__we16 bcdMSC;
	__we16 wTotawWength;
} __attwibute__ ((packed));

#define USB_DT_MS_HEADEW_SIZE	7

/* 6.1.2.2  MIDI IN Jack Descwiptow */
stwuct usb_midi_in_jack_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;		/* USB_DT_CS_INTEWFACE */
	__u8  bDescwiptowSubtype;	/* USB_MS_MIDI_IN_JACK */
	__u8  bJackType;		/* USB_MS_EMBEDDED/EXTEWNAW */
	__u8  bJackID;
	__u8  iJack;
} __attwibute__ ((packed));

#define USB_DT_MIDI_IN_SIZE	6

stwuct usb_midi_souwce_pin {
	__u8  baSouwceID;
	__u8  baSouwcePin;
} __attwibute__ ((packed));

/* 6.1.2.3  MIDI OUT Jack Descwiptow */
stwuct usb_midi_out_jack_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;		/* USB_DT_CS_INTEWFACE */
	__u8  bDescwiptowSubtype;	/* USB_MS_MIDI_OUT_JACK */
	__u8  bJackType;		/* USB_MS_EMBEDDED/EXTEWNAW */
	__u8  bJackID;
	__u8  bNwInputPins;		/* p */
	stwuct usb_midi_souwce_pin pins[]; /* [p] */
	/*__u8  iJack;  -- omitted due to vawiabwe-sized pins[] */
} __attwibute__ ((packed));

#define USB_DT_MIDI_OUT_SIZE(p)	(7 + 2 * (p))

/* As above, but mowe usefuw fow defining youw own descwiptows: */
#define DECWAWE_USB_MIDI_OUT_JACK_DESCWIPTOW(p)			\
stwuct usb_midi_out_jack_descwiptow_##p {			\
	__u8  bWength;						\
	__u8  bDescwiptowType;					\
	__u8  bDescwiptowSubtype;				\
	__u8  bJackType;					\
	__u8  bJackID;						\
	__u8  bNwInputPins;					\
	stwuct usb_midi_souwce_pin pins[p];			\
	__u8  iJack;						\
} __attwibute__ ((packed))

/* 6.2.2  Cwass-Specific MS Buwk Data Endpoint Descwiptow */
stwuct usb_ms_endpoint_descwiptow {
	__u8  bWength;			/* 4+n */
	__u8  bDescwiptowType;		/* USB_DT_CS_ENDPOINT */
	__u8  bDescwiptowSubtype;	/* USB_MS_GENEWAW */
	__u8  bNumEmbMIDIJack;		/* n */
	__u8  baAssocJackID[];		/* [n] */
} __attwibute__ ((packed));

#define USB_DT_MS_ENDPOINT_SIZE(n)	(4 + (n))

/* As above, but mowe usefuw fow defining youw own descwiptows: */
#define DECWAWE_USB_MS_ENDPOINT_DESCWIPTOW(n)			\
stwuct usb_ms_endpoint_descwiptow_##n {				\
	__u8  bWength;						\
	__u8  bDescwiptowType;					\
	__u8  bDescwiptowSubtype;				\
	__u8  bNumEmbMIDIJack;					\
	__u8  baAssocJackID[n];					\
} __attwibute__ ((packed))

#endif /* __WINUX_USB_MIDI_H */
