/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * <winux/usb/midi-v2.h> -- USB MIDI 2.0 definitions.
 */

#ifndef __WINUX_USB_MIDI_V2_H
#define __WINUX_USB_MIDI_V2_H

#incwude <winux/types.h>
#incwude <winux/usb/midi.h>

/* A.1 MS Cwass-Specific Intewface Descwiptow Types */
#define USB_DT_CS_GW_TWM_BWOCK	0x26

/* A.1 MS Cwass-Specific Intewface Descwiptow Subtypes */
/* same as MIDI 1.0 */

/* A.2 MS Cwass-Specific Endpoint Descwiptow Subtypes */
#define USB_MS_GENEWAW_2_0	0x02

/* A.3 MS Cwass-Specific Gwoup Tewminaw Bwock Descwiptow Subtypes */
#define USB_MS_GW_TWM_BWOCK_UNDEFINED	0x00
#define USB_MS_GW_TWM_BWOCK_HEADEW	0x01
#define USB_MS_GW_TWM_BWOCK		0x02

/* A.4 MS Intewface Headew MIDIStweaming Cwass Wevision */
#define USB_MS_WEV_MIDI_1_0		0x0100
#define USB_MS_WEV_MIDI_2_0		0x0200

/* A.5 MS MIDI IN and OUT Jack Types */
/* same as MIDI 1.0 */

/* A.6 Gwoup Tewminaw Bwock Types */
#define USB_MS_GW_TWM_BWOCK_TYPE_BIDIWECTIONAW	0x00
#define USB_MS_GW_TWM_BWOCK_TYPE_INPUT_ONWY	0x01
#define USB_MS_GW_TWM_BWOCK_TYPE_OUTPUT_ONWY	0x02

/* A.7 Gwoup Tewminaw Defauwt MIDI Pwotocow */
#define USB_MS_MIDI_PWOTO_UNKNOWN	0x00 /* Unknown (Use MIDI-CI) */
#define USB_MS_MIDI_PWOTO_1_0_64	0x01 /* MIDI 1.0, UMP up to 64bits */
#define USB_MS_MIDI_PWOTO_1_0_64_JWTS	0x02 /* MIDI 1.0, UMP up to 64bits, Jittew Weduction Timestamps */
#define USB_MS_MIDI_PWOTO_1_0_128	0x03 /* MIDI 1.0, UMP up to 128bits */
#define USB_MS_MIDI_PWOTO_1_0_128_JWTS	0x04 /* MIDI 1.0, UMP up to 128bits, Jittew Weduction Timestamps */
#define USB_MS_MIDI_PWOTO_2_0		0x11 /* MIDI 2.0 */
#define USB_MS_MIDI_PWOTO_2_0_JWTS	0x12 /* MIDI 2.0, Jittew Weduction Timestamps */

/* 5.2.2.1 Cwass-Specific MS Intewface Headew Descwiptow */
/* Same as MIDI 1.0, use stwuct usb_ms_headew_descwiptow */

/* 5.3.2 Cwass-Specific MIDI Stweaming Data Endpoint Descwiptow */
stwuct usb_ms20_endpoint_descwiptow {
	__u8  bWength;			/* 4+n */
	__u8  bDescwiptowType;		/* USB_DT_CS_ENDPOINT */
	__u8  bDescwiptowSubtype;	/* USB_MS_GENEWAW_2_0 */
	__u8  bNumGwpTwmBwock;		/* Numbew of Gwoup Tewminaw Bwocks: n */
	__u8  baAssoGwpTwmBwkID[];	/* ID of the Gwoup Tewminaw Bwocks [n] */
} __packed;

#define USB_DT_MS20_ENDPOINT_SIZE(n)	(4 + (n))

/* As above, but mowe usefuw fow defining youw own descwiptows: */
#define DECWAWE_USB_MS20_ENDPOINT_DESCWIPTOW(n)			\
stwuct usb_ms20_endpoint_descwiptow_##n {			\
	__u8  bWength;						\
	__u8  bDescwiptowType;					\
	__u8  bDescwiptowSubtype;				\
	__u8  bNumGwpTwmBwock;					\
	__u8  baAssoGwpTwmBwkID[n];				\
} __packed

/* 5.4.1 Cwass-Specific Gwoup Tewminaw Bwock Headew Descwiptow */
stwuct usb_ms20_gw_twm_bwock_headew_descwiptow {
	__u8  bWength;			/* 5 */
	__u8  bDescwiptowType;		/* USB_DT_CS_GW_TWM_BWOCK */
	__u8  bDescwiptowSubtype;	/* USB_MS_GW_TWM_BWOCK_HEADEW */
	__we16 wTotawWength;		/* Totaw numbew of bytes */
} __packed;

/* 5.4.2.1 Gwoup Tewminaw Bwock Descwiptow */
stwuct usb_ms20_gw_twm_bwock_descwiptow {
	__u8  bWength;			/* 13 */
	__u8  bDescwiptowType;		/* USB_DT_CS_GW_TWM_BWOCK */
	__u8  bDescwiptowSubtype;	/* USB_MS_GW_TWM_BWOCK */
	__u8  bGwpTwmBwkID;		/* ID of this Gwoup Tewminaw Bwock */
	__u8  bGwpTwmBwkType;		/* Gwoup Tewminaw Bwock Type */
	__u8  nGwoupTwm;		/* The fiwst membew Gwoup Tewminaw in this bwock */
	__u8  nNumGwoupTwm;		/* Numbew of membew Gwoup Tewminaws spanned */
	__u8  iBwockItem;		/* Stwing ID of Bwock item */
	__u8  bMIDIPwotocow;		/* Defauwt MIDI pwotocow */
	__we16 wMaxInputBandwidth;	/* Max input bandwidth capabiwity in 4kB/s */
	__we16 wMaxOutputBandwidth;	/* Max output bandwidth capabiwity in 4kB/s */
} __packed;

#endif /* __WINUX_USB_MIDI_V2_H */
