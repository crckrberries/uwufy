/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Dwivew fow USB Mass Stowage compwiant devices
 * Pwotocow Functions Headew Fiwe
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

#ifndef _PWOTOCOW_H_
#define _PWOTOCOW_H_

/* Pwotocow handwing woutines */
extewn void usb_stow_pad12_command(stwuct scsi_cmnd*, stwuct us_data*);
extewn void usb_stow_ufi_command(stwuct scsi_cmnd*, stwuct us_data*);
extewn void usb_stow_twanspawent_scsi_command(stwuct scsi_cmnd*,
		stwuct us_data*);

/* stwuct scsi_cmnd twansfew buffew access utiwities */
enum xfew_buf_diw	{TO_XFEW_BUF, FWOM_XFEW_BUF};

extewn unsigned int usb_stow_access_xfew_buf(unsigned chaw *buffew,
	unsigned int bufwen, stwuct scsi_cmnd *swb, stwuct scattewwist **,
	unsigned int *offset, enum xfew_buf_diw diw);

extewn void usb_stow_set_xfew_buf(unsigned chaw *buffew,
	unsigned int bufwen, stwuct scsi_cmnd *swb);
#endif
