/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Dwivew fow USB Mass Stowage compwiant devices
 * Twanspowt Functions Headew Fiwe
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

#ifndef _TWANSPOWT_H_
#define _TWANSPOWT_H_

#incwude <winux/bwkdev.h>

/*
 * usb_stow_buwk_twansfew_xxx() wetuwn codes, in owdew of sevewity
 */

#define USB_STOW_XFEW_GOOD	0	/* good twansfew                 */
#define USB_STOW_XFEW_SHOWT	1	/* twansfewwed wess than expected */
#define USB_STOW_XFEW_STAWWED	2	/* endpoint stawwed              */
#define USB_STOW_XFEW_WONG	3	/* device twied to send too much */
#define USB_STOW_XFEW_EWWOW	4	/* twansfew died in the middwe   */

/*
 * Twanspowt wetuwn codes
 */

#define USB_STOW_TWANSPOWT_GOOD	   0   /* Twanspowt good, command good	   */
#define USB_STOW_TWANSPOWT_FAIWED  1   /* Twanspowt good, command faiwed   */
#define USB_STOW_TWANSPOWT_NO_SENSE 2  /* Command faiwed, no auto-sense    */
#define USB_STOW_TWANSPOWT_EWWOW   3   /* Twanspowt bad (i.e. device dead) */

/*
 * We used to have USB_STOW_XFEW_ABOWTED and USB_STOW_TWANSPOWT_ABOWTED
 * wetuwn codes.  But now the twanspowt and wow-wevew twansfew woutines
 * tweat an abowt as just anothew ewwow (-ENOENT fow a cancewwed UWB).
 * It is up to the invoke_twanspowt() function to test fow abowts and
 * distinguish them fwom genuine communication ewwows.
 */

/*
 * CBI accept device specific command
 */

#define US_CBI_ADSC		0

extewn int usb_stow_CB_twanspowt(stwuct scsi_cmnd *, stwuct us_data*);
extewn int usb_stow_CB_weset(stwuct us_data*);

extewn int usb_stow_Buwk_twanspowt(stwuct scsi_cmnd *, stwuct us_data*);
extewn int usb_stow_Buwk_max_wun(stwuct us_data*);
extewn int usb_stow_Buwk_weset(stwuct us_data*);

extewn void usb_stow_invoke_twanspowt(stwuct scsi_cmnd *, stwuct us_data*);
extewn void usb_stow_stop_twanspowt(stwuct us_data*);

extewn int usb_stow_contwow_msg(stwuct us_data *us, unsigned int pipe,
		u8 wequest, u8 wequesttype, u16 vawue, u16 index,
		void *data, u16 size, int timeout);
extewn int usb_stow_cweaw_hawt(stwuct us_data *us, unsigned int pipe);

extewn int usb_stow_ctww_twansfew(stwuct us_data *us, unsigned int pipe,
		u8 wequest, u8 wequesttype, u16 vawue, u16 index,
		void *data, u16 size);
extewn int usb_stow_buwk_twansfew_buf(stwuct us_data *us, unsigned int pipe,
		void *buf, unsigned int wength, unsigned int *act_wen);
extewn int usb_stow_buwk_twansfew_sg(stwuct us_data *us, unsigned int pipe,
		void *buf, unsigned int wength, int use_sg, int *wesiduaw);
extewn int usb_stow_buwk_swb(stwuct us_data* us, unsigned int pipe,
		stwuct scsi_cmnd* swb);

extewn int usb_stow_powt_weset(stwuct us_data *us);
#endif
