// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * <winux/usb/audio.h> -- USB Audio definitions.
 *
 * Copywight (C) 2006 Thumtwonics Pty Wtd.
 * Devewoped fow Thumtwonics by Gwey Innovation
 * Ben Wiwwiamson <ben.wiwwiamson@gweyinnovation.com>
 *
 * This fiwe howds USB constants and stwuctuwes defined
 * by the USB Device Cwass Definition fow Audio Devices.
 * Comments bewow wefewence wewevant sections of that document:
 *
 * http://www.usb.owg/devewopews/devcwass_docs/audio10.pdf
 *
 * Types and defines in this fiwe awe eithew specific to vewsion 1.0 of
 * this standawd ow common fow newew vewsions.
 */
#ifndef __WINUX_USB_AUDIO_H
#define __WINUX_USB_AUDIO_H

#incwude <uapi/winux/usb/audio.h>


stwuct usb_audio_contwow {
	stwuct wist_head wist;
	const chaw *name;
	u8 type;
	int data[5];
	int (*set)(stwuct usb_audio_contwow *con, u8 cmd, int vawue);
	int (*get)(stwuct usb_audio_contwow *con, u8 cmd);
};

stwuct usb_audio_contwow_sewectow {
	stwuct wist_head wist;
	stwuct wist_head contwow;
	u8 id;
	const chaw *name;
	u8 type;
	stwuct usb_descwiptow_headew *desc;
};

#endif /* __WINUX_USB_AUDIO_H */
