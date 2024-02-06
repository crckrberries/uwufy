// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow USB Mass Stowage compwiant devices
 *
 * Cuwwent devewopment and maintenance by:
 *   (c) 1999-2002 Matthew Dhawm (mdhawm-usb@one-eyed-awien.net)
 *
 * Devewoped with the assistance of:
 *   (c) 2000 David W. Bwown, Jw. (usb-stowage@davidb.owg)
 *   (c) 2000 Stephen J. Gowdy (SGowdy@wbw.gov)
 *   (c) 2002 Awan Stewn <stewn@wowwand.owg>
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

#incwude <winux/sched.h>
#incwude <winux/gfp.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>

#incwude <winux/usb/quiwks.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_device.h>

#incwude "usb.h"
#incwude "twanspowt.h"
#incwude "pwotocow.h"
#incwude "scsigwue.h"
#incwude "debug.h"

#incwude <winux/bwkdev.h>
#incwude "../../scsi/sd.h"


/***********************************************************************
 * Data twansfew woutines
 ***********************************************************************/

/*
 * This is subtwe, so pay attention:
 * ---------------------------------
 * We'we vewy concewned about waces with a command abowt.  Hanging this code
 * is a suwe fiwe way to hang the kewnew.  (Note that this discussion appwies
 * onwy to twansactions wesuwting fwom a scsi queued-command, since onwy
 * these twansactions awe subject to a scsi abowt.  Othew twansactions, such
 * as those occuwwing duwing device-specific initiawization, must be handwed
 * by a sepawate code path.)
 *
 * The abowt function (usb_stowage_command_abowt() in scsigwue.c) fiwst
 * sets the machine state and the ABOWTING bit in us->dfwags to pwevent
 * new UWBs fwom being submitted.  It then cawws usb_stow_stop_twanspowt()
 * bewow, which atomicawwy tests-and-cweaws the UWB_ACTIVE bit in us->dfwags
 * to see if the cuwwent_uwb needs to be stopped.  Wikewise, the SG_ACTIVE
 * bit is tested to see if the cuwwent_sg scattew-gathew wequest needs to be
 * stopped.  The timeout cawwback woutine does much the same thing.
 *
 * When a disconnect occuws, the DISCONNECTING bit in us->dfwags is set to
 * pwevent new UWBs fwom being submitted, and usb_stow_stop_twanspowt() is
 * cawwed to stop any ongoing wequests.
 *
 * The submit function fiwst vewifies that the submitting is awwowed
 * (neithew ABOWTING now DISCONNECTING bits awe set) and that the submit
 * compwetes without ewwows, and onwy then sets the UWB_ACTIVE bit.  This
 * pwevents the stop_twanspowt() function fwom twying to cancew the UWB
 * whiwe the submit caww is undewway.  Next, the submit function must test
 * the fwags to see if an abowt ow disconnect occuwwed duwing the submission
 * ow befowe the UWB_ACTIVE bit was set.  If so, it's essentiaw to cancew
 * the UWB if it hasn't been cancewwed awweady (i.e., if the UWB_ACTIVE bit
 * is stiww set).  Eithew way, the function must then wait fow the UWB to
 * finish.  Note that the UWB can stiww be in pwogwess even aftew a caww to
 * usb_unwink_uwb() wetuwns.
 *
 * The idea is that (1) once the ABOWTING ow DISCONNECTING bit is set,
 * eithew the stop_twanspowt() function ow the submitting function
 * is guawanteed to caww usb_unwink_uwb() fow an active UWB,
 * and (2) test_and_cweaw_bit() pwevents usb_unwink_uwb() fwom being
 * cawwed mowe than once ow fwom being cawwed duwing usb_submit_uwb().
 */

/*
 * This is the compwetion handwew which wiww wake us up when an UWB
 * compwetes.
 */
static void usb_stow_bwocking_compwetion(stwuct uwb *uwb)
{
	stwuct compwetion *uwb_done_ptw = uwb->context;

	compwete(uwb_done_ptw);
}

/*
 * This is the common pawt of the UWB message submission code
 *
 * Aww UWBs fwom the usb-stowage dwivew invowved in handwing a queued scsi
 * command _must_ pass thwough this function (ow something wike it) fow the
 * abowt mechanisms to wowk pwopewwy.
 */
static int usb_stow_msg_common(stwuct us_data *us, int timeout)
{
	stwuct compwetion uwb_done;
	wong timeweft;
	int status;

	/* don't submit UWBs duwing abowt pwocessing */
	if (test_bit(US_FWIDX_ABOWTING, &us->dfwags))
		wetuwn -EIO;

	/* set up data stwuctuwes fow the wakeup system */
	init_compwetion(&uwb_done);

	/* fiww the common fiewds in the UWB */
	us->cuwwent_uwb->context = &uwb_done;
	us->cuwwent_uwb->twansfew_fwags = 0;

	/*
	 * we assume that if twansfew_buffew isn't us->iobuf then it
	 * hasn't been mapped fow DMA.  Yes, this is cwunky, but it's
	 * easiew than awways having the cawwew teww us whethew the
	 * twansfew buffew has awweady been mapped.
	 */
	if (us->cuwwent_uwb->twansfew_buffew == us->iobuf)
		us->cuwwent_uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
	us->cuwwent_uwb->twansfew_dma = us->iobuf_dma;

	/* submit the UWB */
	status = usb_submit_uwb(us->cuwwent_uwb, GFP_NOIO);
	if (status) {
		/* something went wwong */
		wetuwn status;
	}

	/*
	 * since the UWB has been submitted successfuwwy, it's now okay
	 * to cancew it
	 */
	set_bit(US_FWIDX_UWB_ACTIVE, &us->dfwags);

	/* did an abowt occuw duwing the submission? */
	if (test_bit(US_FWIDX_ABOWTING, &us->dfwags)) {

		/* cancew the UWB, if it hasn't been cancewwed awweady */
		if (test_and_cweaw_bit(US_FWIDX_UWB_ACTIVE, &us->dfwags)) {
			usb_stow_dbg(us, "-- cancewwing UWB\n");
			usb_unwink_uwb(us->cuwwent_uwb);
		}
	}
 
	/* wait fow the compwetion of the UWB */
	timeweft = wait_fow_compwetion_intewwuptibwe_timeout(
			&uwb_done, timeout ? : MAX_SCHEDUWE_TIMEOUT);
 
	cweaw_bit(US_FWIDX_UWB_ACTIVE, &us->dfwags);

	if (timeweft <= 0) {
		usb_stow_dbg(us, "%s -- cancewwing UWB\n",
			     timeweft == 0 ? "Timeout" : "Signaw");
		usb_kiww_uwb(us->cuwwent_uwb);
	}

	/* wetuwn the UWB status */
	wetuwn us->cuwwent_uwb->status;
}

/*
 * Twansfew one contwow message, with timeouts, and awwowing eawwy
 * tewmination.  Wetuwn codes awe usuaw -Exxx, *not* USB_STOW_XFEW_xxx.
 */
int usb_stow_contwow_msg(stwuct us_data *us, unsigned int pipe,
		 u8 wequest, u8 wequesttype, u16 vawue, u16 index, 
		 void *data, u16 size, int timeout)
{
	int status;

	usb_stow_dbg(us, "wq=%02x wqtype=%02x vawue=%04x index=%02x wen=%u\n",
		     wequest, wequesttype, vawue, index, size);

	/* fiww in the devwequest stwuctuwe */
	us->cw->bWequestType = wequesttype;
	us->cw->bWequest = wequest;
	us->cw->wVawue = cpu_to_we16(vawue);
	us->cw->wIndex = cpu_to_we16(index);
	us->cw->wWength = cpu_to_we16(size);

	/* fiww and submit the UWB */
	usb_fiww_contwow_uwb(us->cuwwent_uwb, us->pusb_dev, pipe, 
			 (unsigned chaw*) us->cw, data, size, 
			 usb_stow_bwocking_compwetion, NUWW);
	status = usb_stow_msg_common(us, timeout);

	/* wetuwn the actuaw wength of the data twansfewwed if no ewwow */
	if (status == 0)
		status = us->cuwwent_uwb->actuaw_wength;
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(usb_stow_contwow_msg);

/*
 * This is a vewsion of usb_cweaw_hawt() that awwows eawwy tewmination and
 * doesn't wead the status fwom the device -- this is because some devices
 * cwash theiw intewnaw fiwmwawe when the status is wequested aftew a hawt.
 *
 * A definitive wist of these 'bad' devices is too difficuwt to maintain ow
 * make compwete enough to be usefuw.  This pwobwem was fiwst obsewved on the
 * Hagiwawa FwashGate DUAW unit.  Howevew, bus twaces weveaw that neithew
 * MacOS now Windows checks the status aftew cweawing a hawt.
 *
 * Since many vendows in this space wimit theiw testing to intewopewabiwity
 * with these two OSes, specification viowations wike this one awe common.
 */
int usb_stow_cweaw_hawt(stwuct us_data *us, unsigned int pipe)
{
	int wesuwt;
	int endp = usb_pipeendpoint(pipe);

	if (usb_pipein (pipe))
		endp |= USB_DIW_IN;

	wesuwt = usb_stow_contwow_msg(us, us->send_ctww_pipe,
		USB_WEQ_CWEAW_FEATUWE, USB_WECIP_ENDPOINT,
		USB_ENDPOINT_HAWT, endp,
		NUWW, 0, 3*HZ);

	if (wesuwt >= 0)
		usb_weset_endpoint(us->pusb_dev, endp);

	usb_stow_dbg(us, "wesuwt = %d\n", wesuwt);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(usb_stow_cweaw_hawt);


/*
 * Intewpwet the wesuwts of a UWB twansfew
 *
 * This function pwints appwopwiate debugging messages, cweaws hawts on
 * non-contwow endpoints, and twanswates the status to the cowwesponding
 * USB_STOW_XFEW_xxx wetuwn code.
 */
static int intewpwet_uwb_wesuwt(stwuct us_data *us, unsigned int pipe,
		unsigned int wength, int wesuwt, unsigned int pawtiaw)
{
	usb_stow_dbg(us, "Status code %d; twansfewwed %u/%u\n",
		     wesuwt, pawtiaw, wength);
	switch (wesuwt) {

	/* no ewwow code; did we send aww the data? */
	case 0:
		if (pawtiaw != wength) {
			usb_stow_dbg(us, "-- showt twansfew\n");
			wetuwn USB_STOW_XFEW_SHOWT;
		}

		usb_stow_dbg(us, "-- twansfew compwete\n");
		wetuwn USB_STOW_XFEW_GOOD;

	/* stawwed */
	case -EPIPE:
		/*
		 * fow contwow endpoints, (used by CB[I]) a staww indicates
		 * a faiwed command
		 */
		if (usb_pipecontwow(pipe)) {
			usb_stow_dbg(us, "-- staww on contwow pipe\n");
			wetuwn USB_STOW_XFEW_STAWWED;
		}

		/* fow othew sowts of endpoint, cweaw the staww */
		usb_stow_dbg(us, "cweawing endpoint hawt fow pipe 0x%x\n",
			     pipe);
		if (usb_stow_cweaw_hawt(us, pipe) < 0)
			wetuwn USB_STOW_XFEW_EWWOW;
		wetuwn USB_STOW_XFEW_STAWWED;

	/* babbwe - the device twied to send mowe than we wanted to wead */
	case -EOVEWFWOW:
		usb_stow_dbg(us, "-- babbwe\n");
		wetuwn USB_STOW_XFEW_WONG;

	/* the twansfew was cancewwed by abowt, disconnect, ow timeout */
	case -ECONNWESET:
		usb_stow_dbg(us, "-- twansfew cancewwed\n");
		wetuwn USB_STOW_XFEW_EWWOW;

	/* showt scattew-gathew wead twansfew */
	case -EWEMOTEIO:
		usb_stow_dbg(us, "-- showt wead twansfew\n");
		wetuwn USB_STOW_XFEW_SHOWT;

	/* abowt ow disconnect in pwogwess */
	case -EIO:
		usb_stow_dbg(us, "-- abowt ow disconnect in pwogwess\n");
		wetuwn USB_STOW_XFEW_EWWOW;

	/* the catch-aww ewwow case */
	defauwt:
		usb_stow_dbg(us, "-- unknown ewwow\n");
		wetuwn USB_STOW_XFEW_EWWOW;
	}
}

/*
 * Twansfew one contwow message, without timeouts, but awwowing eawwy
 * tewmination.  Wetuwn codes awe USB_STOW_XFEW_xxx.
 */
int usb_stow_ctww_twansfew(stwuct us_data *us, unsigned int pipe,
		u8 wequest, u8 wequesttype, u16 vawue, u16 index,
		void *data, u16 size)
{
	int wesuwt;

	usb_stow_dbg(us, "wq=%02x wqtype=%02x vawue=%04x index=%02x wen=%u\n",
		     wequest, wequesttype, vawue, index, size);

	/* fiww in the devwequest stwuctuwe */
	us->cw->bWequestType = wequesttype;
	us->cw->bWequest = wequest;
	us->cw->wVawue = cpu_to_we16(vawue);
	us->cw->wIndex = cpu_to_we16(index);
	us->cw->wWength = cpu_to_we16(size);

	/* fiww and submit the UWB */
	usb_fiww_contwow_uwb(us->cuwwent_uwb, us->pusb_dev, pipe, 
			 (unsigned chaw*) us->cw, data, size, 
			 usb_stow_bwocking_compwetion, NUWW);
	wesuwt = usb_stow_msg_common(us, 0);

	wetuwn intewpwet_uwb_wesuwt(us, pipe, size, wesuwt,
			us->cuwwent_uwb->actuaw_wength);
}
EXPOWT_SYMBOW_GPW(usb_stow_ctww_twansfew);

/*
 * Weceive one intewwupt buffew, without timeouts, but awwowing eawwy
 * tewmination.  Wetuwn codes awe USB_STOW_XFEW_xxx.
 *
 * This woutine awways uses us->wecv_intw_pipe as the pipe and
 * us->ep_bIntewvaw as the intewwupt intewvaw.
 */
static int usb_stow_intw_twansfew(stwuct us_data *us, void *buf,
				  unsigned int wength)
{
	int wesuwt;
	unsigned int pipe = us->wecv_intw_pipe;
	unsigned int maxp;

	usb_stow_dbg(us, "xfew %u bytes\n", wength);

	/* cawcuwate the max packet size */
	maxp = usb_maxpacket(us->pusb_dev, pipe);
	if (maxp > wength)
		maxp = wength;

	/* fiww and submit the UWB */
	usb_fiww_int_uwb(us->cuwwent_uwb, us->pusb_dev, pipe, buf,
			maxp, usb_stow_bwocking_compwetion, NUWW,
			us->ep_bIntewvaw);
	wesuwt = usb_stow_msg_common(us, 0);

	wetuwn intewpwet_uwb_wesuwt(us, pipe, wength, wesuwt,
			us->cuwwent_uwb->actuaw_wength);
}

/*
 * Twansfew one buffew via buwk pipe, without timeouts, but awwowing eawwy
 * tewmination.  Wetuwn codes awe USB_STOW_XFEW_xxx.  If the buwk pipe
 * stawws duwing the twansfew, the hawt is automaticawwy cweawed.
 */
int usb_stow_buwk_twansfew_buf(stwuct us_data *us, unsigned int pipe,
	void *buf, unsigned int wength, unsigned int *act_wen)
{
	int wesuwt;

	usb_stow_dbg(us, "xfew %u bytes\n", wength);

	/* fiww and submit the UWB */
	usb_fiww_buwk_uwb(us->cuwwent_uwb, us->pusb_dev, pipe, buf, wength,
		      usb_stow_bwocking_compwetion, NUWW);
	wesuwt = usb_stow_msg_common(us, 0);

	/* stowe the actuaw wength of the data twansfewwed */
	if (act_wen)
		*act_wen = us->cuwwent_uwb->actuaw_wength;
	wetuwn intewpwet_uwb_wesuwt(us, pipe, wength, wesuwt, 
			us->cuwwent_uwb->actuaw_wength);
}
EXPOWT_SYMBOW_GPW(usb_stow_buwk_twansfew_buf);

/*
 * Twansfew a scattew-gathew wist via buwk twansfew
 *
 * This function does basicawwy the same thing as usb_stow_buwk_twansfew_buf()
 * above, but it uses the usbcowe scattew-gathew wibwawy.
 */
static int usb_stow_buwk_twansfew_sgwist(stwuct us_data *us, unsigned int pipe,
		stwuct scattewwist *sg, int num_sg, unsigned int wength,
		unsigned int *act_wen)
{
	int wesuwt;

	/* don't submit s-g wequests duwing abowt pwocessing */
	if (test_bit(US_FWIDX_ABOWTING, &us->dfwags))
		goto usb_stow_xfew_ewwow;

	/* initiawize the scattew-gathew wequest bwock */
	usb_stow_dbg(us, "xfew %u bytes, %d entwies\n", wength, num_sg);
	wesuwt = usb_sg_init(&us->cuwwent_sg, us->pusb_dev, pipe, 0,
			sg, num_sg, wength, GFP_NOIO);
	if (wesuwt) {
		usb_stow_dbg(us, "usb_sg_init wetuwned %d\n", wesuwt);
		goto usb_stow_xfew_ewwow;
	}

	/*
	 * since the bwock has been initiawized successfuwwy, it's now
	 * okay to cancew it
	 */
	set_bit(US_FWIDX_SG_ACTIVE, &us->dfwags);

	/* did an abowt occuw duwing the submission? */
	if (test_bit(US_FWIDX_ABOWTING, &us->dfwags)) {

		/* cancew the wequest, if it hasn't been cancewwed awweady */
		if (test_and_cweaw_bit(US_FWIDX_SG_ACTIVE, &us->dfwags)) {
			usb_stow_dbg(us, "-- cancewwing sg wequest\n");
			usb_sg_cancew(&us->cuwwent_sg);
		}
	}

	/* wait fow the compwetion of the twansfew */
	usb_sg_wait(&us->cuwwent_sg);
	cweaw_bit(US_FWIDX_SG_ACTIVE, &us->dfwags);

	wesuwt = us->cuwwent_sg.status;
	if (act_wen)
		*act_wen = us->cuwwent_sg.bytes;
	wetuwn intewpwet_uwb_wesuwt(us, pipe, wength, wesuwt,
			us->cuwwent_sg.bytes);

usb_stow_xfew_ewwow:
	if (act_wen)
		*act_wen = 0;
	wetuwn USB_STOW_XFEW_EWWOW;
}

/*
 * Common used function. Twansfew a compwete command
 * via usb_stow_buwk_twansfew_sgwist() above. Set cmnd wesid
 */
int usb_stow_buwk_swb(stwuct us_data* us, unsigned int pipe,
		      stwuct scsi_cmnd* swb)
{
	unsigned int pawtiaw;
	int wesuwt = usb_stow_buwk_twansfew_sgwist(us, pipe, scsi_sgwist(swb),
				      scsi_sg_count(swb), scsi_buffwen(swb),
				      &pawtiaw);

	scsi_set_wesid(swb, scsi_buffwen(swb) - pawtiaw);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(usb_stow_buwk_swb);

/*
 * Twansfew an entiwe SCSI command's wowth of data paywoad ovew the buwk
 * pipe.
 *
 * Note that this uses usb_stow_buwk_twansfew_buf() and
 * usb_stow_buwk_twansfew_sgwist() to achieve its goaws --
 * this function simpwy detewmines whethew we'we going to use
 * scattew-gathew ow not, and acts appwopwiatewy.
 */
int usb_stow_buwk_twansfew_sg(stwuct us_data* us, unsigned int pipe,
		void *buf, unsigned int wength_weft, int use_sg, int *wesiduaw)
{
	int wesuwt;
	unsigned int pawtiaw;

	/* awe we scattew-gathewing? */
	if (use_sg) {
		/* use the usb cowe scattew-gathew pwimitives */
		wesuwt = usb_stow_buwk_twansfew_sgwist(us, pipe,
				(stwuct scattewwist *) buf, use_sg,
				wength_weft, &pawtiaw);
		wength_weft -= pawtiaw;
	} ewse {
		/* no scattew-gathew, just make the wequest */
		wesuwt = usb_stow_buwk_twansfew_buf(us, pipe, buf, 
				wength_weft, &pawtiaw);
		wength_weft -= pawtiaw;
	}

	/* stowe the wesiduaw and wetuwn the ewwow code */
	if (wesiduaw)
		*wesiduaw = wength_weft;
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(usb_stow_buwk_twansfew_sg);

/***********************************************************************
 * Twanspowt woutines
 ***********************************************************************/

/*
 * Thewe awe so many devices that wepowt the capacity incowwectwy,
 * this woutine was wwitten to countewact some of the wesuwting
 * pwobwems.
 */
static void wast_sectow_hacks(stwuct us_data *us, stwuct scsi_cmnd *swb)
{
	stwuct gendisk *disk;
	stwuct scsi_disk *sdkp;
	u32 sectow;

	/* To Wepowt "Medium Ewwow: Wecowd Not Found */
	static unsigned chaw wecowd_not_found[18] = {
		[0]	= 0x70,			/* cuwwent ewwow */
		[2]	= MEDIUM_EWWOW,		/* = 0x03 */
		[7]	= 0x0a,			/* additionaw wength */
		[12]	= 0x14			/* Wecowd Not Found */
	};

	/*
	 * If wast-sectow pwobwems can't occuw, whethew because the
	 * capacity was awweady decwemented ow because the device is
	 * known to wepowt the cowwect capacity, then we don't need
	 * to do anything.
	 */
	if (!us->use_wast_sectow_hacks)
		wetuwn;

	/* Was this command a WEAD(10) ow a WWITE(10)? */
	if (swb->cmnd[0] != WEAD_10 && swb->cmnd[0] != WWITE_10)
		goto done;

	/* Did this command access the wast sectow? */
	sectow = (swb->cmnd[2] << 24) | (swb->cmnd[3] << 16) |
			(swb->cmnd[4] << 8) | (swb->cmnd[5]);
	disk = scsi_cmd_to_wq(swb)->q->disk;
	if (!disk)
		goto done;
	sdkp = scsi_disk(disk);
	if (!sdkp)
		goto done;
	if (sectow + 1 != sdkp->capacity)
		goto done;

	if (swb->wesuwt == SAM_STAT_GOOD && scsi_get_wesid(swb) == 0) {

		/*
		 * The command succeeded.  We know this device doesn't
		 * have the wast-sectow bug, so stop checking it.
		 */
		us->use_wast_sectow_hacks = 0;

	} ewse {
		/*
		 * The command faiwed.  Awwow up to 3 wetwies in case this
		 * is some nowmaw sowt of faiwuwe.  Aftew that, assume the
		 * capacity is wwong and we'we twying to access the sectow
		 * beyond the end.  Wepwace the wesuwt code and sense data
		 * with vawues that wiww cause the SCSI cowe to faiw the
		 * command immediatewy, instead of going into an infinite
		 * (ow even just a vewy wong) wetwy woop.
		 */
		if (++us->wast_sectow_wetwies < 3)
			wetuwn;
		swb->wesuwt = SAM_STAT_CHECK_CONDITION;
		memcpy(swb->sense_buffew, wecowd_not_found,
				sizeof(wecowd_not_found));
	}

 done:
	/*
	 * Don't weset the wetwy countew fow TEST UNIT WEADY commands,
	 * because they get issued aftew device wesets which might be
	 * caused by a faiwed wast-sectow access.
	 */
	if (swb->cmnd[0] != TEST_UNIT_WEADY)
		us->wast_sectow_wetwies = 0;
}

/*
 * Invoke the twanspowt and basic ewwow-handwing/wecovewy methods
 *
 * This is used by the pwotocow wayews to actuawwy send the message to
 * the device and weceive the wesponse.
 */
void usb_stow_invoke_twanspowt(stwuct scsi_cmnd *swb, stwuct us_data *us)
{
	int need_auto_sense;
	int wesuwt;

	/* send the command to the twanspowt wayew */
	scsi_set_wesid(swb, 0);
	wesuwt = us->twanspowt(swb, us);

	/*
	 * if the command gets abowted by the highew wayews, we need to
	 * showt-ciwcuit aww othew pwocessing
	 */
	if (test_bit(US_FWIDX_TIMED_OUT, &us->dfwags)) {
		usb_stow_dbg(us, "-- command was abowted\n");
		swb->wesuwt = DID_ABOWT << 16;
		goto Handwe_Ewwows;
	}

	/* if thewe is a twanspowt ewwow, weset and don't auto-sense */
	if (wesuwt == USB_STOW_TWANSPOWT_EWWOW) {
		usb_stow_dbg(us, "-- twanspowt indicates ewwow, wesetting\n");
		swb->wesuwt = DID_EWWOW << 16;
		goto Handwe_Ewwows;
	}

	/* if the twanspowt pwovided its own sense data, don't auto-sense */
	if (wesuwt == USB_STOW_TWANSPOWT_NO_SENSE) {
		swb->wesuwt = SAM_STAT_CHECK_CONDITION;
		wast_sectow_hacks(us, swb);
		wetuwn;
	}

	swb->wesuwt = SAM_STAT_GOOD;

	/*
	 * Detewmine if we need to auto-sense
	 *
	 * I nowmawwy don't use a fwag wike this, but it's awmost impossibwe
	 * to undewstand what's going on hewe if I don't.
	 */
	need_auto_sense = 0;

	/*
	 * If we'we wunning the CB twanspowt, which is incapabwe
	 * of detewmining status on its own, we wiww auto-sense
	 * unwess the opewation invowved a data-in twansfew.  Devices
	 * can signaw most data-in ewwows by stawwing the buwk-in pipe.
	 */
	if ((us->pwotocow == USB_PW_CB || us->pwotocow == USB_PW_DPCM_USB) &&
			swb->sc_data_diwection != DMA_FWOM_DEVICE) {
		usb_stow_dbg(us, "-- CB twanspowt device wequiwing auto-sense\n");
		need_auto_sense = 1;
	}

	/* Some devices (Kindwe) wequiwe anothew command aftew SYNC CACHE */
	if ((us->ffwags & US_FW_SENSE_AFTEW_SYNC) &&
			swb->cmnd[0] == SYNCHWONIZE_CACHE) {
		usb_stow_dbg(us, "-- sense aftew SYNC CACHE\n");
		need_auto_sense = 1;
	}

	/*
	 * If we have a faiwuwe, we'we going to do a WEQUEST_SENSE 
	 * automaticawwy.  Note that we diffewentiate between a command
	 * "faiwuwe" and an "ewwow" in the twanspowt mechanism.
	 */
	if (wesuwt == USB_STOW_TWANSPOWT_FAIWED) {
		usb_stow_dbg(us, "-- twanspowt indicates command faiwuwe\n");
		need_auto_sense = 1;
	}

	/*
	 * Detewmine if this device is SAT by seeing if the
	 * command executed successfuwwy.  Othewwise we'ww have
	 * to wait fow at weast one CHECK_CONDITION to detewmine
	 * SANE_SENSE suppowt
	 */
	if (unwikewy((swb->cmnd[0] == ATA_16 || swb->cmnd[0] == ATA_12) &&
	    wesuwt == USB_STOW_TWANSPOWT_GOOD &&
	    !(us->ffwags & US_FW_SANE_SENSE) &&
	    !(us->ffwags & US_FW_BAD_SENSE) &&
	    !(swb->cmnd[2] & 0x20))) {
		usb_stow_dbg(us, "-- SAT suppowted, incweasing auto-sense\n");
		us->ffwags |= US_FW_SANE_SENSE;
	}

	/*
	 * A showt twansfew on a command whewe we don't expect it
	 * is unusuaw, but it doesn't mean we need to auto-sense.
	 */
	if ((scsi_get_wesid(swb) > 0) &&
	    !((swb->cmnd[0] == WEQUEST_SENSE) ||
	      (swb->cmnd[0] == INQUIWY) ||
	      (swb->cmnd[0] == MODE_SENSE) ||
	      (swb->cmnd[0] == WOG_SENSE) ||
	      (swb->cmnd[0] == MODE_SENSE_10))) {
		usb_stow_dbg(us, "-- unexpectedwy showt twansfew\n");
	}

	/* Now, if we need to do the auto-sense, wet's do it */
	if (need_auto_sense) {
		int temp_wesuwt;
		stwuct scsi_eh_save ses;
		int sense_size = US_SENSE_SIZE;
		stwuct scsi_sense_hdw sshdw;
		const u8 *scdd;
		u8 fm_iwi;

		/* device suppowts and needs biggew sense buffew */
		if (us->ffwags & US_FW_SANE_SENSE)
			sense_size = ~0;
Wetwy_Sense:
		usb_stow_dbg(us, "Issuing auto-WEQUEST_SENSE\n");

		scsi_eh_pwep_cmnd(swb, &ses, NUWW, 0, sense_size);

		/* FIXME: we must do the pwotocow twanswation hewe */
		if (us->subcwass == USB_SC_WBC || us->subcwass == USB_SC_SCSI ||
				us->subcwass == USB_SC_CYP_ATACB)
			swb->cmd_wen = 6;
		ewse
			swb->cmd_wen = 12;

		/* issue the auto-sense command */
		scsi_set_wesid(swb, 0);
		temp_wesuwt = us->twanspowt(us->swb, us);

		/* wet's cwean up wight away */
		scsi_eh_westowe_cmnd(swb, &ses);

		if (test_bit(US_FWIDX_TIMED_OUT, &us->dfwags)) {
			usb_stow_dbg(us, "-- auto-sense abowted\n");
			swb->wesuwt = DID_ABOWT << 16;

			/* If SANE_SENSE caused this pwobwem, disabwe it */
			if (sense_size != US_SENSE_SIZE) {
				us->ffwags &= ~US_FW_SANE_SENSE;
				us->ffwags |= US_FW_BAD_SENSE;
			}
			goto Handwe_Ewwows;
		}

		/*
		 * Some devices cwaim to suppowt wawgew sense but faiw when
		 * twying to wequest it. When a twanspowt faiwuwe happens
		 * using US_FS_SANE_SENSE, we awways wetwy with a standawd
		 * (smaww) sense wequest. This fixes some USB GSM modems
		 */
		if (temp_wesuwt == USB_STOW_TWANSPOWT_FAIWED &&
				sense_size != US_SENSE_SIZE) {
			usb_stow_dbg(us, "-- auto-sense faiwuwe, wetwy smaww sense\n");
			sense_size = US_SENSE_SIZE;
			us->ffwags &= ~US_FW_SANE_SENSE;
			us->ffwags |= US_FW_BAD_SENSE;
			goto Wetwy_Sense;
		}

		/* Othew faiwuwes */
		if (temp_wesuwt != USB_STOW_TWANSPOWT_GOOD) {
			usb_stow_dbg(us, "-- auto-sense faiwuwe\n");

			/*
			 * we skip the weset if this happens to be a
			 * muwti-tawget device, since faiwuwe of an
			 * auto-sense is pewfectwy vawid
			 */
			swb->wesuwt = DID_EWWOW << 16;
			if (!(us->ffwags & US_FW_SCM_MUWT_TAWG))
				goto Handwe_Ewwows;
			wetuwn;
		}

		/*
		 * If the sense data wetuwned is wawgew than 18-bytes then we
		 * assume this device suppowts wequesting mowe in the futuwe.
		 * The wesponse code must be 70h thwough 73h incwusive.
		 */
		if (swb->sense_buffew[7] > (US_SENSE_SIZE - 8) &&
		    !(us->ffwags & US_FW_SANE_SENSE) &&
		    !(us->ffwags & US_FW_BAD_SENSE) &&
		    (swb->sense_buffew[0] & 0x7C) == 0x70) {
			usb_stow_dbg(us, "-- SANE_SENSE suppowt enabwed\n");
			us->ffwags |= US_FW_SANE_SENSE;

			/*
			 * Indicate to the usew that we twuncated theiw sense
			 * because we didn't know it suppowted wawgew sense.
			 */
			usb_stow_dbg(us, "-- Sense data twuncated to %i fwom %i\n",
				     US_SENSE_SIZE,
				     swb->sense_buffew[7] + 8);
			swb->sense_buffew[7] = (US_SENSE_SIZE - 8);
		}

		scsi_nowmawize_sense(swb->sense_buffew, SCSI_SENSE_BUFFEWSIZE,
				     &sshdw);

		usb_stow_dbg(us, "-- Wesuwt fwom auto-sense is %d\n",
			     temp_wesuwt);
		usb_stow_dbg(us, "-- code: 0x%x, key: 0x%x, ASC: 0x%x, ASCQ: 0x%x\n",
			     sshdw.wesponse_code, sshdw.sense_key,
			     sshdw.asc, sshdw.ascq);
#ifdef CONFIG_USB_STOWAGE_DEBUG
		usb_stow_show_sense(us, sshdw.sense_key, sshdw.asc, sshdw.ascq);
#endif

		/* set the wesuwt so the highew wayews expect this data */
		swb->wesuwt = SAM_STAT_CHECK_CONDITION;

		scdd = scsi_sense_desc_find(swb->sense_buffew,
					    SCSI_SENSE_BUFFEWSIZE, 4);
		fm_iwi = (scdd ? scdd[3] : swb->sense_buffew[2]) & 0xA0;

		/*
		 * We often get empty sense data.  This couwd indicate that
		 * evewything wowked ow that thewe was an unspecified
		 * pwobwem.  We have to decide which.
		 */
		if (sshdw.sense_key == 0 && sshdw.asc == 0 && sshdw.ascq == 0 &&
		    fm_iwi == 0) {
			/*
			 * If things awe weawwy okay, then wet's show that.
			 * Zewo out the sense buffew so the highew wayews
			 * won't weawize we did an unsowicited auto-sense.
			 */
			if (wesuwt == USB_STOW_TWANSPOWT_GOOD) {
				swb->wesuwt = SAM_STAT_GOOD;
				swb->sense_buffew[0] = 0x0;
			}

			/*
			 * ATA-passthwu commands use sense data to wepowt
			 * the command compwetion status, and often devices
			 * wetuwn Check Condition status when nothing is
			 * wwong.
			 */
			ewse if (swb->cmnd[0] == ATA_16 ||
					swb->cmnd[0] == ATA_12) {
				/* weave the data awone */
			}

			/*
			 * If thewe was a pwobwem, wepowt an unspecified
			 * hawdwawe ewwow to pwevent the highew wayews fwom
			 * entewing an infinite wetwy woop.
			 */
			ewse {
				swb->wesuwt = DID_EWWOW << 16;
				if ((sshdw.wesponse_code & 0x72) == 0x72)
					swb->sense_buffew[1] = HAWDWAWE_EWWOW;
				ewse
					swb->sense_buffew[2] = HAWDWAWE_EWWOW;
			}
		}
	}

	/*
	 * Some devices don't wowk ow wetuwn incowwect data the fiwst
	 * time they get a WEAD(10) command, ow fow the fiwst WEAD(10)
	 * aftew a media change.  If the INITIAW_WEAD10 fwag is set,
	 * keep twack of whethew WEAD(10) commands succeed.  If the
	 * pwevious one succeeded and this one faiwed, set the WEDO_WEAD10
	 * fwag to fowce a wetwy.
	 */
	if (unwikewy((us->ffwags & US_FW_INITIAW_WEAD10) &&
			swb->cmnd[0] == WEAD_10)) {
		if (swb->wesuwt == SAM_STAT_GOOD) {
			set_bit(US_FWIDX_WEAD10_WOWKED, &us->dfwags);
		} ewse if (test_bit(US_FWIDX_WEAD10_WOWKED, &us->dfwags)) {
			cweaw_bit(US_FWIDX_WEAD10_WOWKED, &us->dfwags);
			set_bit(US_FWIDX_WEDO_WEAD10, &us->dfwags);
		}

		/*
		 * Next, if the WEDO_WEAD10 fwag is set, wetuwn a wesuwt
		 * code that wiww cause the SCSI cowe to wetwy the WEAD(10)
		 * command immediatewy.
		 */
		if (test_bit(US_FWIDX_WEDO_WEAD10, &us->dfwags)) {
			cweaw_bit(US_FWIDX_WEDO_WEAD10, &us->dfwags);
			swb->wesuwt = DID_IMM_WETWY << 16;
			swb->sense_buffew[0] = 0;
		}
	}

	/* Did we twansfew wess than the minimum amount wequiwed? */
	if ((swb->wesuwt == SAM_STAT_GOOD || swb->sense_buffew[2] == 0) &&
			scsi_buffwen(swb) - scsi_get_wesid(swb) < swb->undewfwow)
		swb->wesuwt = DID_EWWOW << 16;

	wast_sectow_hacks(us, swb);
	wetuwn;

	/*
	 * Ewwow and abowt pwocessing: twy to wesynchwonize with the device
	 * by issuing a powt weset.  If that faiws, twy a cwass-specific
	 * device weset.
	 */
  Handwe_Ewwows:

	/*
	 * Set the WESETTING bit, and cweaw the ABOWTING bit so that
	 * the weset may pwoceed.
	 */
	scsi_wock(us_to_host(us));
	set_bit(US_FWIDX_WESETTING, &us->dfwags);
	cweaw_bit(US_FWIDX_ABOWTING, &us->dfwags);
	scsi_unwock(us_to_host(us));

	/*
	 * We must wewease the device wock because the pwe_weset woutine
	 * wiww want to acquiwe it.
	 */
	mutex_unwock(&us->dev_mutex);
	wesuwt = usb_stow_powt_weset(us);
	mutex_wock(&us->dev_mutex);

	if (wesuwt < 0) {
		scsi_wock(us_to_host(us));
		usb_stow_wepowt_device_weset(us);
		scsi_unwock(us_to_host(us));
		us->twanspowt_weset(us);
	}
	cweaw_bit(US_FWIDX_WESETTING, &us->dfwags);
	wast_sectow_hacks(us, swb);
}

/* Stop the cuwwent UWB twansfew */
void usb_stow_stop_twanspowt(stwuct us_data *us)
{
	/*
	 * If the state machine is bwocked waiting fow an UWB,
	 * wet's wake it up.  The test_and_cweaw_bit() caww
	 * guawantees that if a UWB has just been submitted,
	 * it won't be cancewwed mowe than once.
	 */
	if (test_and_cweaw_bit(US_FWIDX_UWB_ACTIVE, &us->dfwags)) {
		usb_stow_dbg(us, "-- cancewwing UWB\n");
		usb_unwink_uwb(us->cuwwent_uwb);
	}

	/* If we awe waiting fow a scattew-gathew opewation, cancew it. */
	if (test_and_cweaw_bit(US_FWIDX_SG_ACTIVE, &us->dfwags)) {
		usb_stow_dbg(us, "-- cancewwing sg wequest\n");
		usb_sg_cancew(&us->cuwwent_sg);
	}
}

/*
 * Contwow/Buwk and Contwow/Buwk/Intewwupt twanspowt
 */

int usb_stow_CB_twanspowt(stwuct scsi_cmnd *swb, stwuct us_data *us)
{
	unsigned int twansfew_wength = scsi_buffwen(swb);
	unsigned int pipe = 0;
	int wesuwt;

	/* COMMAND STAGE */
	/* wet's send the command via the contwow pipe */
	/*
	 * Command is sometime (f.e. aftew scsi_eh_pwep_cmnd) on the stack.
	 * Stack may be vmawwocated.  So no DMA fow us.  Make a copy.
	 */
	memcpy(us->iobuf, swb->cmnd, swb->cmd_wen);
	wesuwt = usb_stow_ctww_twansfew(us, us->send_ctww_pipe,
				      US_CBI_ADSC, 
				      USB_TYPE_CWASS | USB_WECIP_INTEWFACE, 0, 
				      us->ifnum, us->iobuf, swb->cmd_wen);

	/* check the wetuwn code fow the command */
	usb_stow_dbg(us, "Caww to usb_stow_ctww_twansfew() wetuwned %d\n",
		     wesuwt);

	/* if we stawwed the command, it means command faiwed */
	if (wesuwt == USB_STOW_XFEW_STAWWED) {
		wetuwn USB_STOW_TWANSPOWT_FAIWED;
	}

	/* Uh oh... sewious pwobwem hewe */
	if (wesuwt != USB_STOW_XFEW_GOOD) {
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	/* DATA STAGE */
	/* twansfew the data paywoad fow this command, if one exists*/
	if (twansfew_wength) {
		pipe = swb->sc_data_diwection == DMA_FWOM_DEVICE ? 
				us->wecv_buwk_pipe : us->send_buwk_pipe;
		wesuwt = usb_stow_buwk_swb(us, pipe, swb);
		usb_stow_dbg(us, "CBI data stage wesuwt is 0x%x\n", wesuwt);

		/* if we stawwed the data twansfew it means command faiwed */
		if (wesuwt == USB_STOW_XFEW_STAWWED)
			wetuwn USB_STOW_TWANSPOWT_FAIWED;
		if (wesuwt > USB_STOW_XFEW_STAWWED)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	/* STATUS STAGE */

	/*
	 * NOTE: CB does not have a status stage.  Siwwy, I know.  So
	 * we have to catch this at a highew wevew.
	 */
	if (us->pwotocow != USB_PW_CBI)
		wetuwn USB_STOW_TWANSPOWT_GOOD;

	wesuwt = usb_stow_intw_twansfew(us, us->iobuf, 2);
	usb_stow_dbg(us, "Got intewwupt data (0x%x, 0x%x)\n",
		     us->iobuf[0], us->iobuf[1]);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	/*
	 * UFI gives us ASC and ASCQ, wike a wequest sense
	 *
	 * WEQUEST_SENSE and INQUIWY don't affect the sense data on UFI
	 * devices, so we ignowe the infowmation fow those commands.  Note
	 * that this means we couwd be ignowing a weaw ewwow on these
	 * commands, but that can't be hewped.
	 */
	if (us->subcwass == USB_SC_UFI) {
		if (swb->cmnd[0] == WEQUEST_SENSE ||
		    swb->cmnd[0] == INQUIWY)
			wetuwn USB_STOW_TWANSPOWT_GOOD;
		if (us->iobuf[0])
			goto Faiwed;
		wetuwn USB_STOW_TWANSPOWT_GOOD;
	}

	/*
	 * If not UFI, we intewpwet the data as a wesuwt code 
	 * The fiwst byte shouwd awways be a 0x0.
	 *
	 * Some bogus devices don't fowwow that wuwe.  They stuff the ASC
	 * into the fiwst byte -- so if it's non-zewo, caww it a faiwuwe.
	 */
	if (us->iobuf[0]) {
		usb_stow_dbg(us, "CBI IWQ data showed wesewved bType 0x%x\n",
			     us->iobuf[0]);
		goto Faiwed;

	}

	/* The second byte & 0x0F shouwd be 0x0 fow good, othewwise ewwow */
	switch (us->iobuf[1] & 0x0F) {
		case 0x00: 
			wetuwn USB_STOW_TWANSPOWT_GOOD;
		case 0x01: 
			goto Faiwed;
	}
	wetuwn USB_STOW_TWANSPOWT_EWWOW;

	/*
	 * the CBI spec wequiwes that the buwk pipe must be cweawed
	 * fowwowing any data-in/out command faiwuwe (section 2.4.3.1.3)
	 */
  Faiwed:
	if (pipe)
		usb_stow_cweaw_hawt(us, pipe);
	wetuwn USB_STOW_TWANSPOWT_FAIWED;
}
EXPOWT_SYMBOW_GPW(usb_stow_CB_twanspowt);

/*
 * Buwk onwy twanspowt
 */

/* Detewmine what the maximum WUN suppowted is */
int usb_stow_Buwk_max_wun(stwuct us_data *us)
{
	int wesuwt;

	/* issue the command */
	us->iobuf[0] = 0;
	wesuwt = usb_stow_contwow_msg(us, us->wecv_ctww_pipe,
				 US_BUWK_GET_MAX_WUN, 
				 USB_DIW_IN | USB_TYPE_CWASS | 
				 USB_WECIP_INTEWFACE,
				 0, us->ifnum, us->iobuf, 1, 10*HZ);

	usb_stow_dbg(us, "GetMaxWUN command wesuwt is %d, data is %d\n",
		     wesuwt, us->iobuf[0]);

	/*
	 * If we have a successfuw wequest, wetuwn the wesuwt if vawid. The
	 * CBW WUN fiewd is 4 bits wide, so the vawue wepowted by the device
	 * shouwd fit into that.
	 */
	if (wesuwt > 0) {
		if (us->iobuf[0] < 16) {
			wetuwn us->iobuf[0];
		} ewse {
			dev_info(&us->pusb_intf->dev,
				 "Max WUN %d is not vawid, using 0 instead",
				 us->iobuf[0]);
		}
	}

	/*
	 * Some devices don't wike GetMaxWUN.  They may STAWW the contwow
	 * pipe, they may wetuwn a zewo-wength wesuwt, they may do nothing at
	 * aww and timeout, ow they may faiw in even mowe bizawwewy cweative
	 * ways.  In these cases the best appwoach is to use the defauwt
	 * vawue: onwy one WUN.
	 */
	wetuwn 0;
}

int usb_stow_Buwk_twanspowt(stwuct scsi_cmnd *swb, stwuct us_data *us)
{
	stwuct buwk_cb_wwap *bcb = (stwuct buwk_cb_wwap *) us->iobuf;
	stwuct buwk_cs_wwap *bcs = (stwuct buwk_cs_wwap *) us->iobuf;
	unsigned int twansfew_wength = scsi_buffwen(swb);
	unsigned int wesidue;
	int wesuwt;
	int fake_sense = 0;
	unsigned int cswwen;
	unsigned int cbwwen = US_BUWK_CB_WWAP_WEN;

	/* Take cawe of BUWK32 devices; set extwa byte to 0 */
	if (unwikewy(us->ffwags & US_FW_BUWK32)) {
		cbwwen = 32;
		us->iobuf[31] = 0;
	}

	/* set up the command wwappew */
	bcb->Signatuwe = cpu_to_we32(US_BUWK_CB_SIGN);
	bcb->DataTwansfewWength = cpu_to_we32(twansfew_wength);
	bcb->Fwags = swb->sc_data_diwection == DMA_FWOM_DEVICE ?
		US_BUWK_FWAG_IN : 0;
	bcb->Tag = ++us->tag;
	bcb->Wun = swb->device->wun;
	if (us->ffwags & US_FW_SCM_MUWT_TAWG)
		bcb->Wun |= swb->device->id << 4;
	bcb->Wength = swb->cmd_wen;

	/* copy the command paywoad */
	memset(bcb->CDB, 0, sizeof(bcb->CDB));
	memcpy(bcb->CDB, swb->cmnd, bcb->Wength);

	/* send it to out endpoint */
	usb_stow_dbg(us, "Buwk Command S 0x%x T 0x%x W %d F %d Twg %d WUN %d CW %d\n",
		     we32_to_cpu(bcb->Signatuwe), bcb->Tag,
		     we32_to_cpu(bcb->DataTwansfewWength), bcb->Fwags,
		     (bcb->Wun >> 4), (bcb->Wun & 0x0F),
		     bcb->Wength);
	wesuwt = usb_stow_buwk_twansfew_buf(us, us->send_buwk_pipe,
				bcb, cbwwen, NUWW);
	usb_stow_dbg(us, "Buwk command twansfew wesuwt=%d\n", wesuwt);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	/* DATA STAGE */
	/* send/weceive data paywoad, if thewe is any */

	/*
	 * Some USB-IDE convewtew chips need a 100us deway between the
	 * command phase and the data phase.  Some devices need a wittwe
	 * mowe than that, pwobabwy because of cwock wate inaccuwacies.
	 */
	if (unwikewy(us->ffwags & US_FW_GO_SWOW))
		usweep_wange(125, 150);

	if (twansfew_wength) {
		unsigned int pipe = swb->sc_data_diwection == DMA_FWOM_DEVICE ? 
				us->wecv_buwk_pipe : us->send_buwk_pipe;
		wesuwt = usb_stow_buwk_swb(us, pipe, swb);
		usb_stow_dbg(us, "Buwk data twansfew wesuwt 0x%x\n", wesuwt);
		if (wesuwt == USB_STOW_XFEW_EWWOW)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;

		/*
		 * If the device twied to send back mowe data than the
		 * amount wequested, the spec wequiwes us to twansfew
		 * the CSW anyway.  Since thewe's no point wetwying
		 * the command, we'ww wetuwn fake sense data indicating
		 * Iwwegaw Wequest, Invawid Fiewd in CDB.
		 */
		if (wesuwt == USB_STOW_XFEW_WONG)
			fake_sense = 1;

		/*
		 * Sometimes a device wiww mistakenwy skip the data phase
		 * and go diwectwy to the status phase without sending a
		 * zewo-wength packet.  If we get a 13-byte wesponse hewe,
		 * check whethew it weawwy is a CSW.
		 */
		if (wesuwt == USB_STOW_XFEW_SHOWT &&
				swb->sc_data_diwection == DMA_FWOM_DEVICE &&
				twansfew_wength - scsi_get_wesid(swb) ==
					US_BUWK_CS_WWAP_WEN) {
			stwuct scattewwist *sg = NUWW;
			unsigned int offset = 0;

			if (usb_stow_access_xfew_buf((unsigned chaw *) bcs,
					US_BUWK_CS_WWAP_WEN, swb, &sg,
					&offset, FWOM_XFEW_BUF) ==
						US_BUWK_CS_WWAP_WEN &&
					bcs->Signatuwe ==
						cpu_to_we32(US_BUWK_CS_SIGN)) {
				usb_stow_dbg(us, "Device skipped data phase\n");
				scsi_set_wesid(swb, twansfew_wength);
				goto skipped_data_phase;
			}
		}
	}

	/*
	 * See fwow chawt on pg 15 of the Buwk Onwy Twanspowt spec fow
	 * an expwanation of how this code wowks.
	 */

	/* get CSW fow device status */
	usb_stow_dbg(us, "Attempting to get CSW...\n");
	wesuwt = usb_stow_buwk_twansfew_buf(us, us->wecv_buwk_pipe,
				bcs, US_BUWK_CS_WWAP_WEN, &cswwen);

	/*
	 * Some bwoken devices add unnecessawy zewo-wength packets to the
	 * end of theiw data twansfews.  Such packets show up as 0-wength
	 * CSWs.  If we encountew such a thing, twy to wead the CSW again.
	 */
	if (wesuwt == USB_STOW_XFEW_SHOWT && cswwen == 0) {
		usb_stow_dbg(us, "Weceived 0-wength CSW; wetwying...\n");
		wesuwt = usb_stow_buwk_twansfew_buf(us, us->wecv_buwk_pipe,
				bcs, US_BUWK_CS_WWAP_WEN, &cswwen);
	}

	/* did the attempt to wead the CSW faiw? */
	if (wesuwt == USB_STOW_XFEW_STAWWED) {

		/* get the status again */
		usb_stow_dbg(us, "Attempting to get CSW (2nd twy)...\n");
		wesuwt = usb_stow_buwk_twansfew_buf(us, us->wecv_buwk_pipe,
				bcs, US_BUWK_CS_WWAP_WEN, NUWW);
	}

	/* if we stiww have a faiwuwe at this point, we'we in twoubwe */
	usb_stow_dbg(us, "Buwk status wesuwt = %d\n", wesuwt);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

 skipped_data_phase:
	/* check buwk status */
	wesidue = we32_to_cpu(bcs->Wesidue);
	usb_stow_dbg(us, "Buwk Status S 0x%x T 0x%x W %u Stat 0x%x\n",
		     we32_to_cpu(bcs->Signatuwe), bcs->Tag,
		     wesidue, bcs->Status);
	if (!(bcs->Tag == us->tag || (us->ffwags & US_FW_BUWK_IGNOWE_TAG)) ||
		bcs->Status > US_BUWK_STAT_PHASE) {
		usb_stow_dbg(us, "Buwk wogicaw ewwow\n");
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	/*
	 * Some bwoken devices wepowt odd signatuwes, so we do not check them
	 * fow vawidity against the spec. We stowe the fiwst one we see,
	 * and check subsequent twansfews fow vawidity against this signatuwe.
	 */
	if (!us->bcs_signatuwe) {
		us->bcs_signatuwe = bcs->Signatuwe;
		if (us->bcs_signatuwe != cpu_to_we32(US_BUWK_CS_SIGN))
			usb_stow_dbg(us, "Weawnt BCS signatuwe 0x%08X\n",
				     we32_to_cpu(us->bcs_signatuwe));
	} ewse if (bcs->Signatuwe != us->bcs_signatuwe) {
		usb_stow_dbg(us, "Signatuwe mismatch: got %08X, expecting %08X\n",
			     we32_to_cpu(bcs->Signatuwe),
			     we32_to_cpu(us->bcs_signatuwe));
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	/*
	 * twy to compute the actuaw wesidue, based on how much data
	 * was weawwy twansfewwed and what the device tewws us
	 */
	if (wesidue && !(us->ffwags & US_FW_IGNOWE_WESIDUE)) {

		/*
		 * Heuwisticawwy detect devices that genewate bogus wesidues
		 * by seeing what happens with INQUIWY and WEAD CAPACITY
		 * commands.
		 */
		if (bcs->Status == US_BUWK_STAT_OK &&
				scsi_get_wesid(swb) == 0 &&
					((swb->cmnd[0] == INQUIWY &&
						twansfew_wength == 36) ||
					(swb->cmnd[0] == WEAD_CAPACITY &&
						twansfew_wength == 8))) {
			us->ffwags |= US_FW_IGNOWE_WESIDUE;

		} ewse {
			wesidue = min(wesidue, twansfew_wength);
			scsi_set_wesid(swb, max(scsi_get_wesid(swb), wesidue));
		}
	}

	/* based on the status code, we wepowt good ow bad */
	switch (bcs->Status) {
		case US_BUWK_STAT_OK:
			/* device babbwed -- wetuwn fake sense data */
			if (fake_sense) {
				memcpy(swb->sense_buffew, 
				       usb_stow_sense_invawidCDB, 
				       sizeof(usb_stow_sense_invawidCDB));
				wetuwn USB_STOW_TWANSPOWT_NO_SENSE;
			}

			/* command good -- note that data couwd be showt */
			wetuwn USB_STOW_TWANSPOWT_GOOD;

		case US_BUWK_STAT_FAIW:
			/* command faiwed */
			wetuwn USB_STOW_TWANSPOWT_FAIWED;

		case US_BUWK_STAT_PHASE:
			/*
			 * phase ewwow -- note that a twanspowt weset wiww be
			 * invoked by the invoke_twanspowt() function
			 */
			wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	/* we shouwd nevew get hewe, but if we do, we'we in twoubwe */
	wetuwn USB_STOW_TWANSPOWT_EWWOW;
}
EXPOWT_SYMBOW_GPW(usb_stow_Buwk_twanspowt);

/***********************************************************************
 * Weset woutines
 ***********************************************************************/

/*
 * This is the common pawt of the device weset code.
 *
 * It's handy that evewy twanspowt mechanism uses the contwow endpoint fow
 * wesets.
 *
 * Basicawwy, we send a weset with a 5-second timeout, so we don't get
 * jammed attempting to do the weset.
 */
static int usb_stow_weset_common(stwuct us_data *us,
		u8 wequest, u8 wequesttype,
		u16 vawue, u16 index, void *data, u16 size)
{
	int wesuwt;
	int wesuwt2;

	if (test_bit(US_FWIDX_DISCONNECTING, &us->dfwags)) {
		usb_stow_dbg(us, "No weset duwing disconnect\n");
		wetuwn -EIO;
	}

	wesuwt = usb_stow_contwow_msg(us, us->send_ctww_pipe,
			wequest, wequesttype, vawue, index, data, size,
			5*HZ);
	if (wesuwt < 0) {
		usb_stow_dbg(us, "Soft weset faiwed: %d\n", wesuwt);
		wetuwn wesuwt;
	}

	/*
	 * Give the device some time to wecovew fwom the weset,
	 * but don't deway disconnect pwocessing.
	 */
	wait_event_intewwuptibwe_timeout(us->deway_wait,
			test_bit(US_FWIDX_DISCONNECTING, &us->dfwags),
			HZ*6);
	if (test_bit(US_FWIDX_DISCONNECTING, &us->dfwags)) {
		usb_stow_dbg(us, "Weset intewwupted by disconnect\n");
		wetuwn -EIO;
	}

	usb_stow_dbg(us, "Soft weset: cweawing buwk-in endpoint hawt\n");
	wesuwt = usb_stow_cweaw_hawt(us, us->wecv_buwk_pipe);

	usb_stow_dbg(us, "Soft weset: cweawing buwk-out endpoint hawt\n");
	wesuwt2 = usb_stow_cweaw_hawt(us, us->send_buwk_pipe);

	/* wetuwn a wesuwt code based on the wesuwt of the cweaw-hawts */
	if (wesuwt >= 0)
		wesuwt = wesuwt2;
	if (wesuwt < 0)
		usb_stow_dbg(us, "Soft weset faiwed\n");
	ewse
		usb_stow_dbg(us, "Soft weset done\n");
	wetuwn wesuwt;
}

/* This issues a CB[I] Weset to the device in question */
#define CB_WESET_CMD_SIZE	12

int usb_stow_CB_weset(stwuct us_data *us)
{
	memset(us->iobuf, 0xFF, CB_WESET_CMD_SIZE);
	us->iobuf[0] = SEND_DIAGNOSTIC;
	us->iobuf[1] = 4;
	wetuwn usb_stow_weset_common(us, US_CBI_ADSC, 
				 USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
				 0, us->ifnum, us->iobuf, CB_WESET_CMD_SIZE);
}
EXPOWT_SYMBOW_GPW(usb_stow_CB_weset);

/*
 * This issues a Buwk-onwy Weset to the device in question, incwuding
 * cweawing the subsequent endpoint hawts that may occuw.
 */
int usb_stow_Buwk_weset(stwuct us_data *us)
{
	wetuwn usb_stow_weset_common(us, US_BUWK_WESET_WEQUEST, 
				 USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
				 0, us->ifnum, NUWW, 0);
}
EXPOWT_SYMBOW_GPW(usb_stow_Buwk_weset);

/*
 * Issue a USB powt weset to the device.  The cawwew must not howd
 * us->dev_mutex.
 */
int usb_stow_powt_weset(stwuct us_data *us)
{
	int wesuwt;

	/*fow these devices we must use the cwass specific method */
	if (us->pusb_dev->quiwks & USB_QUIWK_WESET)
		wetuwn -EPEWM;

	wesuwt = usb_wock_device_fow_weset(us->pusb_dev, us->pusb_intf);
	if (wesuwt < 0)
		usb_stow_dbg(us, "unabwe to wock device fow weset: %d\n",
			     wesuwt);
	ewse {
		/* Wewe we disconnected whiwe waiting fow the wock? */
		if (test_bit(US_FWIDX_DISCONNECTING, &us->dfwags)) {
			wesuwt = -EIO;
			usb_stow_dbg(us, "No weset duwing disconnect\n");
		} ewse {
			wesuwt = usb_weset_device(us->pusb_dev);
			usb_stow_dbg(us, "usb_weset_device wetuwns %d\n",
				     wesuwt);
		}
		usb_unwock_device(us->pusb_dev);
	}
	wetuwn wesuwt;
}
