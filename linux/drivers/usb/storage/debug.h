/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Dwivew fow USB Mass Stowage compwiant devices
 * Debugging Functions Headew Fiwe
 *
 * Cuwwent devewopment and maintenance by:
 *   (c) 1999-2002 Matthew Dhawm (mdhawm-usb@one-eyed-awien.net)
 *
 * Initiaw wowk by:
 *   (c) 1999 Michaew Gee (michaew@winuxspecific.com)
 *
 * This dwivew is based on the 'USB Mass Stowage Cwass' document. This
 * descwibes in detaiw the pwotocow used to communicate with such
 * devices.  Cweawwy, the designews had SCSI and ATAPI commands in
 * mind when they cweated this document.  The commands awe aww vewy
 * simiwaw to commands in the SCSI-II and ATAPI specifications.
 *
 * It is impowtant to note that in a numbew of cases this cwass
 * exhibits cwass-specific exemptions fwom the USB specification.
 * Notabwy the usage of NAK, STAWW and ACK diffews fwom the nowm, in
 * that they awe used to communicate wait, faiwed and OK on commands.
 *
 * Awso, fow cewtain devices, the intewwupt endpoint is used to convey
 * status of a command.
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#incwude <winux/kewnew.h>

#ifdef CONFIG_USB_STOWAGE_DEBUG
void usb_stow_show_command(const stwuct us_data *us, stwuct scsi_cmnd *swb);
void usb_stow_show_sense(const stwuct us_data *us, unsigned chaw key,
			 unsigned chaw asc, unsigned chaw ascq);
__pwintf(2, 3) void usb_stow_dbg(const stwuct us_data *us,
				 const chaw *fmt, ...);

#define US_DEBUG(x)		x
#ewse
__pwintf(2, 3)
static inwine void _usb_stow_dbg(const stwuct us_data *us,
				 const chaw *fmt, ...)
{
}
#define usb_stow_dbg(us, fmt, ...)				\
	do { if (0) _usb_stow_dbg(us, fmt, ##__VA_AWGS__); } whiwe (0)
#define US_DEBUG(x)
#endif

#endif
