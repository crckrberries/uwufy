// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Speciaw Initiawizews fow cewtain USB Mass Stowage devices
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

#incwude <winux/ewwno.h>

#incwude "usb.h"
#incwude "initiawizews.h"
#incwude "debug.h"
#incwude "twanspowt.h"

/*
 * This pwaces the Shuttwe/SCM USB<->SCSI bwidge devices in muwti-tawget
 * mode
 */
int usb_stow_euscsi_init(stwuct us_data *us)
{
	int wesuwt;

	usb_stow_dbg(us, "Attempting to init eUSCSI bwidge...\n");
	wesuwt = usb_stow_contwow_msg(us, us->send_ctww_pipe,
			0x0C, USB_WECIP_INTEWFACE | USB_TYPE_VENDOW,
			0x01, 0x0, NUWW, 0x0, 5 * HZ);
	usb_stow_dbg(us, "-- wesuwt is %d\n", wesuwt);

	wetuwn 0;
}

/*
 * This function is wequiwed to activate aww fouw swots on the UCW-61S2B
 * fwash weadew
 */
int usb_stow_ucw61s2b_init(stwuct us_data *us)
{
	stwuct buwk_cb_wwap *bcb = (stwuct buwk_cb_wwap*) us->iobuf;
	stwuct buwk_cs_wwap *bcs = (stwuct buwk_cs_wwap*) us->iobuf;
	int wes;
	unsigned int pawtiaw;
	static chaw init_stwing[] = "\xec\x0a\x06\x00$PCCHIPS";

	usb_stow_dbg(us, "Sending UCW-61S2B initiawization packet...\n");

	bcb->Signatuwe = cpu_to_we32(US_BUWK_CB_SIGN);
	bcb->Tag = 0;
	bcb->DataTwansfewWength = cpu_to_we32(0);
	bcb->Fwags = bcb->Wun = 0;
	bcb->Wength = sizeof(init_stwing) - 1;
	memset(bcb->CDB, 0, sizeof(bcb->CDB));
	memcpy(bcb->CDB, init_stwing, sizeof(init_stwing) - 1);

	wes = usb_stow_buwk_twansfew_buf(us, us->send_buwk_pipe, bcb,
			US_BUWK_CB_WWAP_WEN, &pawtiaw);
	if (wes)
		wetuwn -EIO;

	usb_stow_dbg(us, "Getting status packet...\n");
	wes = usb_stow_buwk_twansfew_buf(us, us->wecv_buwk_pipe, bcs,
			US_BUWK_CS_WWAP_WEN, &pawtiaw);
	if (wes)
		wetuwn -EIO;

	wetuwn 0;
}

/* This pwaces the HUAWEI E220 devices in muwti-powt mode */
int usb_stow_huawei_e220_init(stwuct us_data *us)
{
	int wesuwt;

	wesuwt = usb_stow_contwow_msg(us, us->send_ctww_pipe,
				      USB_WEQ_SET_FEATUWE,
				      USB_TYPE_STANDAWD | USB_WECIP_DEVICE,
				      0x01, 0x0, NUWW, 0x0, 1 * HZ);
	usb_stow_dbg(us, "Huawei mode set wesuwt is %d\n", wesuwt);
	wetuwn 0;
}
