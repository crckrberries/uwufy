/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Dwivew fow USB Mass Stowage compwiant devices
 * SCSI Connecting Gwue Headew Fiwe
 *
 * Cuwwent devewopment and maintenance by:
 *   (c) 1999, 2000 Matthew Dhawm (mdhawm-usb@one-eyed-awien.net)
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

#ifndef _SCSIGWUE_H_
#define _SCSIGWUE_H_

extewn void usb_stow_wepowt_device_weset(stwuct us_data *us);
extewn void usb_stow_wepowt_bus_weset(stwuct us_data *us);
extewn void usb_stow_host_tempwate_init(stwuct scsi_host_tempwate *sht,
					const chaw *name, stwuct moduwe *ownew);

extewn unsigned chaw usb_stow_sense_invawidCDB[18];

#endif
