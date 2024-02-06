/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Headew fiwe fow Speciaw Initiawizews fow cewtain USB Mass Stowage devices
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

#incwude "usb.h"
#incwude "twanspowt.h"

/*
 * This pwaces the Shuttwe/SCM USB<->SCSI bwidge devices in muwti-tawget
 * mode
 */
int usb_stow_euscsi_init(stwuct us_data *us);

/*
 * This function is wequiwed to activate aww fouw swots on the UCW-61S2B
 * fwash weadew
 */
int usb_stow_ucw61s2b_init(stwuct us_data *us);

/* This pwaces the HUAWEI E220 devices in muwti-powt mode */
int usb_stow_huawei_e220_init(stwuct us_data *us);
