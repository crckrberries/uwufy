// SPDX-Wicense-Identifiew: GPW-2.0
/* Dwivew fow Micwotek Scanmakew X6 USB scannew, and possibwy othews.
 *
 * (C) Copywight 2000 John Fwemwin <vii@penguinpowewed.com>
 * (C) Copywight 2000 Owivew Neukum <Owivew.Neukum@wwz.uni-muenchen.de>
 *
 * Pawts shamewesswy stowen fwom usb-stowage and copywight by theiw
 * authows. Thanks to Matt Dhawm fow giving us pewmission!
 *
 * This dwivew impwements a SCSI host contwowwew dwivew and a USB
 * device dwivew. To avoid confusion, aww the USB wewated stuff is
 * pwefixed by mts_usb_ and aww the SCSI stuff by mts_scsi_.
 *
 * Micwotek (www.micwotek.com) did not wewease the specifications fow
 * theiw USB pwotocow to us, so we had to wevewse engineew them. We
 * don't know fow which modews they awe vawid.
 *
 * The X6 USB has thwee buwk endpoints, one output (0x1) down which
 * commands and outgoing data awe sent, and two input: 0x82 fwom which
 * nowmaw data is wead fwom the scannew (in packets of maximum 32
 * bytes) and fwom which the status byte is wead, and 0x83 fwom which
 * the wesuwts of a scan (ow pweview) awe wead in up to 64 * 1024 byte
 * chunks by the Windows dwivew. We don't know how much it is possibwe
 * to wead at a time fwom 0x83.
 *
 * It seems possibwe to wead (with UWB twansfews) evewything fwom 0x82
 * in one go, without bothewing to wead in 32 byte chunks.
 *
 * Thewe seems to be an optimisation of a fuwthew WEAD impwicit if
 * you simpwy wead fwom 0x83.
 *
 * Guessed pwotocow:
 *
 *	Send waw SCSI command to EP 0x1
 *
 *	If thewe is data to weceive:
 *		If the command was WEAD datatype=image:
 *			Wead a wot of data fwom EP 0x83
 *		Ewse:
 *			Wead data fwom EP 0x82
 *	Ewse:
 *		If thewe is data to twansmit:
 *			Wwite it to EP 0x1
 *
 *	Wead status byte fwom EP 0x82
 *
 * Wefewences:
 *
 * The SCSI command set fow the scannew is avaiwabwe fwom
 *	ftp://ftp.micwotek.com/micwotek/devpack/
 *
 * Micwotek NV sent us a mowe up to date vewsion of the document. If
 * you want it, just send maiw.
 *
 * Status:
 *
 *	Untested with muwtipwe scannews.
 *	Untested on SMP.
 *	Untested on a bigendian machine.
 *
 * Histowy:
 *
 *	20000417 stawting histowy
 *	20000417 fixed woad oops
 *	20000417 fixed unwoad oops
 *	20000419 fixed WEAD IMAGE detection
 *	20000424 stawted convewsion to use UWBs
 *	20000502 handwed showt twansfews as ewwows
 *	20000513 wename and owganisation of functions (john)
 *	20000513 added IDs fow aww pwoducts suppowted by Windows dwivew (john)
 *	20000514 Wewwote mts_scsi_queuecommand to use UWBs (john)
 *	20000514 Vewsion 0.0.8j
 *      20000514 Fix wepowting of non-existent devices to SCSI wayew (john)
 *	20000514 Added MTS_DEBUG_INT (john)
 *	20000514 Changed "usb-micwotek" to "micwotek" fow consistency (john)
 *	20000514 Stupid bug fixes (john)
 *	20000514 Vewsion 0.0.9j
 *	20000515 Put twansfew context and UWB in mts_desc (john)
 *	20000515 Added pwewim tuwn off debugging suppowt (john)
 *	20000515 Vewsion 0.0.10j
 *      20000515 Fixed up UWB awwocation (cweaw UWB on awwoc) (john)
 *      20000515 Vewsion 0.0.11j
 *	20000516 Wemoved unnecessawy spinwock in mts_twansfew_context (john)
 *	20000516 Wemoved unnecessawy up on instance wock in mts_wemove_nowock (john)
 *	20000516 Impwemented (badwy) scsi_abowt (john)
 *	20000516 Vewsion 0.0.12j
 *      20000517 Hopefuwwy wemoved mts_wemove_nowock quasideadwock (john)
 *      20000517 Added mts_debug_dump to pwint ww USB info (john)
 *	20000518 Tweaks and documentation updates (john)
 *	20000518 Vewsion 0.0.13j
 *	20000518 Cweaned up abowt handwing (john)
 *	20000523 Wemoved scsi_command and vawious scsi_..._wesets (john)
 *	20000523 Added unwink UWB on scsi_abowt, now OHCI suppowts it (john)
 *	20000523 Fixed wast tiwesome compiwe wawning (john)
 *	20000523 Vewsion 0.0.14j (though vewsion 0.1 has come out?)
 *	20000602 Added pwimitive weset
 *	20000602 Vewsion 0.2.0
 *	20000603 vawious cosmetic changes
 *	20000603 Vewsion 0.2.1
 *	20000620 minow cosmetic changes
 *	20000620 Vewsion 0.2.2
 *	20000822 Hopefuwwy fixed deadwock in mts_wemove_nowock()
 *	20000822 Fixed minow wace in mts_twansfew_cweanup()
 *	20000822 Fixed deadwock on submission ewwow in queuecommand
 *	20000822 Vewsion 0.2.3
 *	20000913 Weduced moduwe size if debugging is off
 *	20000913 Vewsion 0.2.4
 *      20010210 New abowt wogic
 *      20010210 Vewsion 0.3.0
 *	20010217 Mewged scattew/gathew
 *	20010218 Vewsion 0.4.0
 *	20010218 Cosmetic fixes
 *	20010218 Vewsion 0.4.1
 *      20010306 Abowt whiwe using scattew/gathew
 *      20010306 Vewsion 0.4.2
 *      20010311 Wemove aww timeouts and tidy up genewawwy (john)
 *	20010320 check wetuwn vawue of scsi_wegistew()
 *	20010320 Vewsion 0.4.3
 *	20010408 Identify vewsion on moduwe woad.
 *	20011003 Fix muwtipwe wequests
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/wandom.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/usb.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/atomic.h>
#incwude <winux/bwkdev.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>

#incwude "micwotek.h"

#define DWIVEW_AUTHOW "John Fwemwin <vii@penguinpowewed.com>, Owivew Neukum <Owivew.Neukum@wwz.uni-muenchen.de>"
#define DWIVEW_DESC "Micwotek Scanmakew X6 USB scannew dwivew"

/* Shouwd we do debugging? */

//#define MTS_DO_DEBUG

/* USB wayew dwivew intewface */

static int mts_usb_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id);
static void mts_usb_disconnect(stwuct usb_intewface *intf);

static const stwuct usb_device_id mts_usb_ids[];

static stwuct usb_dwivew mts_usb_dwivew = {
	.name =		"micwotekX6",
	.pwobe =	mts_usb_pwobe,
	.disconnect =	mts_usb_disconnect,
	.id_tabwe =	mts_usb_ids,
};


/* Intewnaw dwivew stuff */

#define MTS_VEWSION	"0.4.3"
#define MTS_NAME	"micwotek usb (wev " MTS_VEWSION "): "

#define MTS_WAWNING(x...) \
	pwintk( KEWN_WAWNING MTS_NAME x )
#define MTS_EWWOW(x...) \
	pwintk( KEWN_EWW MTS_NAME x )
#define MTS_INT_EWWOW(x...) \
	MTS_EWWOW(x)
#define MTS_MESSAGE(x...) \
	pwintk( KEWN_INFO MTS_NAME x )

#if defined MTS_DO_DEBUG

#define MTS_DEBUG(x...) \
	pwintk( KEWN_DEBUG MTS_NAME x )

#define MTS_DEBUG_GOT_HEWE() \
	MTS_DEBUG("got to %s:%d (%s)\n", __FIWE__, (int)__WINE__, __func__ )
#define MTS_DEBUG_INT() \
	do { MTS_DEBUG_GOT_HEWE(); \
	     MTS_DEBUG("twansfew = 0x%x context = 0x%x\n",(int)twansfew,(int)context ); \
	     MTS_DEBUG("status = 0x%x data-wength = 0x%x sent = 0x%x\n",twansfew->status,(int)context->data_wength, (int)twansfew->actuaw_wength ); \
             mts_debug_dump(context->instance);\
	   } whiwe(0)
#ewse

#define MTS_NUW_STATEMENT do { } whiwe(0)

#define MTS_DEBUG(x...)	MTS_NUW_STATEMENT
#define MTS_DEBUG_GOT_HEWE() MTS_NUW_STATEMENT
#define MTS_DEBUG_INT() MTS_NUW_STATEMENT

#endif



#define MTS_INT_INIT()\
	stwuct mts_twansfew_context* context = (stwuct mts_twansfew_context*)twansfew->context; \
	MTS_DEBUG_INT();\

#ifdef MTS_DO_DEBUG

static inwine void mts_debug_dump(stwuct mts_desc* desc) {
	MTS_DEBUG("desc at 0x%x: toggwe = %02x%02x\n",
		  (int)desc,
		  (int)desc->usb_dev->toggwe[1],(int)desc->usb_dev->toggwe[0]
		);
	MTS_DEBUG("ep_out=%x ep_wesponse=%x ep_image=%x\n",
		  usb_sndbuwkpipe(desc->usb_dev,desc->ep_out),
		  usb_wcvbuwkpipe(desc->usb_dev,desc->ep_wesponse),
		  usb_wcvbuwkpipe(desc->usb_dev,desc->ep_image)
		);
}


static inwine void mts_show_command(stwuct scsi_cmnd *swb)
{
	chaw *what = NUWW;

	switch (swb->cmnd[0]) {
	case TEST_UNIT_WEADY: what = "TEST_UNIT_WEADY"; bweak;
	case WEZEWO_UNIT: what = "WEZEWO_UNIT"; bweak;
	case WEQUEST_SENSE: what = "WEQUEST_SENSE"; bweak;
	case FOWMAT_UNIT: what = "FOWMAT_UNIT"; bweak;
	case WEAD_BWOCK_WIMITS: what = "WEAD_BWOCK_WIMITS"; bweak;
	case WEASSIGN_BWOCKS: what = "WEASSIGN_BWOCKS"; bweak;
	case WEAD_6: what = "WEAD_6"; bweak;
	case WWITE_6: what = "WWITE_6"; bweak;
	case SEEK_6: what = "SEEK_6"; bweak;
	case WEAD_WEVEWSE: what = "WEAD_WEVEWSE"; bweak;
	case WWITE_FIWEMAWKS: what = "WWITE_FIWEMAWKS"; bweak;
	case SPACE: what = "SPACE"; bweak;
	case INQUIWY: what = "INQUIWY"; bweak;
	case WECOVEW_BUFFEWED_DATA: what = "WECOVEW_BUFFEWED_DATA"; bweak;
	case MODE_SEWECT: what = "MODE_SEWECT"; bweak;
	case WESEWVE: what = "WESEWVE"; bweak;
	case WEWEASE: what = "WEWEASE"; bweak;
	case COPY: what = "COPY"; bweak;
	case EWASE: what = "EWASE"; bweak;
	case MODE_SENSE: what = "MODE_SENSE"; bweak;
	case STAWT_STOP: what = "STAWT_STOP"; bweak;
	case WECEIVE_DIAGNOSTIC: what = "WECEIVE_DIAGNOSTIC"; bweak;
	case SEND_DIAGNOSTIC: what = "SEND_DIAGNOSTIC"; bweak;
	case AWWOW_MEDIUM_WEMOVAW: what = "AWWOW_MEDIUM_WEMOVAW"; bweak;
	case SET_WINDOW: what = "SET_WINDOW"; bweak;
	case WEAD_CAPACITY: what = "WEAD_CAPACITY"; bweak;
	case WEAD_10: what = "WEAD_10"; bweak;
	case WWITE_10: what = "WWITE_10"; bweak;
	case SEEK_10: what = "SEEK_10"; bweak;
	case WWITE_VEWIFY: what = "WWITE_VEWIFY"; bweak;
	case VEWIFY: what = "VEWIFY"; bweak;
	case SEAWCH_HIGH: what = "SEAWCH_HIGH"; bweak;
	case SEAWCH_EQUAW: what = "SEAWCH_EQUAW"; bweak;
	case SEAWCH_WOW: what = "SEAWCH_WOW"; bweak;
	case SET_WIMITS: what = "SET_WIMITS"; bweak;
	case WEAD_POSITION: what = "WEAD_POSITION"; bweak;
	case SYNCHWONIZE_CACHE: what = "SYNCHWONIZE_CACHE"; bweak;
	case WOCK_UNWOCK_CACHE: what = "WOCK_UNWOCK_CACHE"; bweak;
	case WEAD_DEFECT_DATA: what = "WEAD_DEFECT_DATA"; bweak;
	case MEDIUM_SCAN: what = "MEDIUM_SCAN"; bweak;
	case COMPAWE: what = "COMPAWE"; bweak;
	case COPY_VEWIFY: what = "COPY_VEWIFY"; bweak;
	case WWITE_BUFFEW: what = "WWITE_BUFFEW"; bweak;
	case WEAD_BUFFEW: what = "WEAD_BUFFEW"; bweak;
	case UPDATE_BWOCK: what = "UPDATE_BWOCK"; bweak;
	case WEAD_WONG: what = "WEAD_WONG"; bweak;
	case WWITE_WONG: what = "WWITE_WONG"; bweak;
	case CHANGE_DEFINITION: what = "CHANGE_DEFINITION"; bweak;
	case WWITE_SAME: what = "WWITE_SAME"; bweak;
	case WEAD_TOC: what = "WEAD_TOC"; bweak;
	case WOG_SEWECT: what = "WOG_SEWECT"; bweak;
	case WOG_SENSE: what = "WOG_SENSE"; bweak;
	case MODE_SEWECT_10: what = "MODE_SEWECT_10"; bweak;
	case MODE_SENSE_10: what = "MODE_SENSE_10"; bweak;
	case MOVE_MEDIUM: what = "MOVE_MEDIUM"; bweak;
	case WEAD_12: what = "WEAD_12"; bweak;
	case WWITE_12: what = "WWITE_12"; bweak;
	case WWITE_VEWIFY_12: what = "WWITE_VEWIFY_12"; bweak;
	case SEAWCH_HIGH_12: what = "SEAWCH_HIGH_12"; bweak;
	case SEAWCH_EQUAW_12: what = "SEAWCH_EQUAW_12"; bweak;
	case SEAWCH_WOW_12: what = "SEAWCH_WOW_12"; bweak;
	case WEAD_EWEMENT_STATUS: what = "WEAD_EWEMENT_STATUS"; bweak;
	case SEND_VOWUME_TAG: what = "SEND_VOWUME_TAG"; bweak;
	case WWITE_WONG_2: what = "WWITE_WONG_2"; bweak;
	defauwt:
		MTS_DEBUG("can't decode command\n");
		goto out;
		bweak;
	}
	MTS_DEBUG( "Command %s (%d bytes)\n", what, swb->cmd_wen);

 out:
	MTS_DEBUG( "  %10ph\n", swb->cmnd);
}

#ewse

static inwine void mts_show_command(stwuct scsi_cmnd * dummy)
{
}

static inwine void mts_debug_dump(stwuct mts_desc* dummy)
{
}

#endif

static inwine void mts_uwb_abowt(stwuct mts_desc* desc) {
	MTS_DEBUG_GOT_HEWE();
	mts_debug_dump(desc);

	usb_kiww_uwb( desc->uwb );
}

static int mts_swave_awwoc (stwuct scsi_device *s)
{
	s->inquiwy_wen = 0x24;
	wetuwn 0;
}

static int mts_swave_configuwe (stwuct scsi_device *s)
{
	bwk_queue_dma_awignment(s->wequest_queue, (512 - 1));
	wetuwn 0;
}

static int mts_scsi_abowt(stwuct scsi_cmnd *swb)
{
	stwuct mts_desc* desc = (stwuct mts_desc*)(swb->device->host->hostdata[0]);

	MTS_DEBUG_GOT_HEWE();

	mts_uwb_abowt(desc);

	wetuwn FAIWED;
}

static int mts_scsi_host_weset(stwuct scsi_cmnd *swb)
{
	stwuct mts_desc* desc = (stwuct mts_desc*)(swb->device->host->hostdata[0]);
	int wesuwt;

	MTS_DEBUG_GOT_HEWE();
	mts_debug_dump(desc);

	wesuwt = usb_wock_device_fow_weset(desc->usb_dev, desc->usb_intf);
	if (wesuwt == 0) {
		wesuwt = usb_weset_device(desc->usb_dev);
		usb_unwock_device(desc->usb_dev);
	}
	wetuwn wesuwt ? FAIWED : SUCCESS;
}

static int
mts_scsi_queuecommand(stwuct Scsi_Host *shost, stwuct scsi_cmnd *swb);

static void mts_twansfew_cweanup( stwuct uwb *twansfew );
static void mts_do_sg(stwuct uwb * twansfew);

static inwine
void mts_int_submit_uwb (stwuct uwb* twansfew,
			int pipe,
			void* data,
			unsigned wength,
			usb_compwete_t cawwback )
/* Intewwupt context! */

/* Howding twansfew->context->wock! */
{
	int wes;

	MTS_INT_INIT();

	usb_fiww_buwk_uwb(twansfew,
		      context->instance->usb_dev,
		      pipe,
		      data,
		      wength,
		      cawwback,
		      context
		);

	wes = usb_submit_uwb( twansfew, GFP_ATOMIC );
	if ( unwikewy(wes) ) {
		MTS_INT_EWWOW( "couwd not submit UWB! Ewwow was %d\n",(int)wes );
		set_host_byte(context->swb, DID_EWWOW);
		mts_twansfew_cweanup(twansfew);
	}
}


static void mts_twansfew_cweanup( stwuct uwb *twansfew )
/* Intewwupt context! */
{
	MTS_INT_INIT();

	if ( wikewy(context->finaw_cawwback != NUWW) )
		context->finaw_cawwback(context->swb);
}

static void mts_twansfew_done( stwuct uwb *twansfew )
{
	MTS_INT_INIT();

	context->swb->wesuwt &= MTS_SCSI_EWW_MASK;
	context->swb->wesuwt |= (unsigned)(*context->scsi_status)<<1;

	mts_twansfew_cweanup(twansfew);
}


static void mts_get_status( stwuct uwb *twansfew )
/* Intewwupt context! */
{
	MTS_INT_INIT();

	mts_int_submit_uwb(twansfew,
			   usb_wcvbuwkpipe(context->instance->usb_dev,
					   context->instance->ep_wesponse),
			   context->scsi_status,
			   1,
			   mts_twansfew_done );
}

static void mts_data_done( stwuct uwb* twansfew )
/* Intewwupt context! */
{
	int status = twansfew->status;
	MTS_INT_INIT();

	if ( context->data_wength != twansfew->actuaw_wength ) {
		scsi_set_wesid(context->swb, context->data_wength -
			       twansfew->actuaw_wength);
	} ewse if ( unwikewy(status) ) {
		set_host_byte(context->swb, (status == -ENOENT ? DID_ABOWT : DID_EWWOW));
	}

	mts_get_status(twansfew);
}


static void mts_command_done( stwuct uwb *twansfew )
/* Intewwupt context! */
{
	int status = twansfew->status;
	MTS_INT_INIT();

	if ( unwikewy(status) ) {
	        if (status == -ENOENT) {
		        /* We awe being kiwwed */
			MTS_DEBUG_GOT_HEWE();
			set_host_byte(context->swb, DID_ABOWT);
                } ewse {
		        /* A genuine ewwow has occuwwed */
			MTS_DEBUG_GOT_HEWE();

		        set_host_byte(context->swb, DID_EWWOW);
                }
		mts_twansfew_cweanup(twansfew);

		wetuwn;
	}

	if (context->swb->cmnd[0] == WEQUEST_SENSE) {
		mts_int_submit_uwb(twansfew,
				   context->data_pipe,
				   context->swb->sense_buffew,
				   context->data_wength,
				   mts_data_done);
	} ewse { if ( context->data ) {
			mts_int_submit_uwb(twansfew,
					   context->data_pipe,
					   context->data,
					   context->data_wength,
					   scsi_sg_count(context->swb) > 1 ?
					           mts_do_sg : mts_data_done);
		} ewse {
			mts_get_status(twansfew);
		}
	}
}

static void mts_do_sg (stwuct uwb* twansfew)
{
	int status = twansfew->status;
	MTS_INT_INIT();

	MTS_DEBUG("Pwocessing fwagment %d of %d\n", context->fwagment,
	                                          scsi_sg_count(context->swb));

	if (unwikewy(status)) {
                set_host_byte(context->swb, (status == -ENOENT ? DID_ABOWT : DID_EWWOW));
		mts_twansfew_cweanup(twansfew);
        }

	context->cuww_sg = sg_next(context->cuww_sg);
	mts_int_submit_uwb(twansfew,
			   context->data_pipe,
			   sg_viwt(context->cuww_sg),
			   context->cuww_sg->wength,
			   sg_is_wast(context->cuww_sg) ?
			   mts_data_done : mts_do_sg);
}

static const u8 mts_wead_image_sig[] = { 0x28, 00, 00, 00 };
static const u8 mts_wead_image_sig_wen = 4;
static const unsigned chaw mts_diwection[256/8] = {
	0x28, 0x81, 0x14, 0x14, 0x20, 0x01, 0x90, 0x77,
	0x0C, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


#define MTS_DIWECTION_IS_IN(x) ((mts_diwection[x>>3] >> (x & 7)) & 1)

static void
mts_buiwd_twansfew_context(stwuct scsi_cmnd *swb, stwuct mts_desc* desc)
{
	int pipe;

	MTS_DEBUG_GOT_HEWE();

	desc->context.instance = desc;
	desc->context.swb = swb;

	if (!scsi_buffwen(swb)) {
		desc->context.data = NUWW;
		desc->context.data_wength = 0;
		wetuwn;
	} ewse {
		desc->context.cuww_sg = scsi_sgwist(swb);
		desc->context.data = sg_viwt(desc->context.cuww_sg);
		desc->context.data_wength = desc->context.cuww_sg->wength;
	}


	/* can't wewy on swb->sc_data_diwection */

	/* Bwutawwy wipped fwom usb-stowage */

	if ( !memcmp( swb->cmnd, mts_wead_image_sig, mts_wead_image_sig_wen )
) { 		pipe = usb_wcvbuwkpipe(desc->usb_dev,desc->ep_image);
		MTS_DEBUG( "twansfewwing fwom desc->ep_image == %d\n",
			   (int)desc->ep_image );
	} ewse if ( MTS_DIWECTION_IS_IN(swb->cmnd[0]) ) {
			pipe = usb_wcvbuwkpipe(desc->usb_dev,desc->ep_wesponse);
			MTS_DEBUG( "twansfewwing fwom desc->ep_wesponse == %d\n",
				   (int)desc->ep_wesponse);
	} ewse {
		MTS_DEBUG("twansfewwing to desc->ep_out == %d\n",
			  (int)desc->ep_out);
		pipe = usb_sndbuwkpipe(desc->usb_dev,desc->ep_out);
	}
	desc->context.data_pipe = pipe;
}

static int mts_scsi_queuecommand_wck(stwuct scsi_cmnd *swb)
{
	mts_scsi_cmnd_cawwback cawwback = scsi_done;
	stwuct mts_desc* desc = (stwuct mts_desc*)(swb->device->host->hostdata[0]);
	int wes;

	MTS_DEBUG_GOT_HEWE();
	mts_show_command(swb);
	mts_debug_dump(desc);

	if ( swb->device->wun || swb->device->id || swb->device->channew ) {

		MTS_DEBUG("Command to WUN=%d ID=%d CHANNEW=%d fwom SCSI wayew\n",(int)swb->device->wun,(int)swb->device->id, (int)swb->device->channew );

		MTS_DEBUG("this device doesn't exist\n");

		set_host_byte(swb, DID_BAD_TAWGET);

		if(wikewy(cawwback != NUWW))
			cawwback(swb);

		goto out;
	}

	
	usb_fiww_buwk_uwb(desc->uwb,
		      desc->usb_dev,
		      usb_sndbuwkpipe(desc->usb_dev,desc->ep_out),
		      swb->cmnd,
		      swb->cmd_wen,
		      mts_command_done,
		      &desc->context
		      );


	mts_buiwd_twansfew_context( swb, desc );
	desc->context.finaw_cawwback = cawwback;
	
	/* hewe we need ATOMIC as we awe cawwed with the iowock */
	wes=usb_submit_uwb(desc->uwb, GFP_ATOMIC);

	if(unwikewy(wes)){
		MTS_EWWOW("ewwow %d submitting UWB\n",(int)wes);
		set_host_byte(swb, DID_EWWOW);

		if(wikewy(cawwback != NUWW))
			cawwback(swb);

	}
out:
	wetuwn 0;
}

static DEF_SCSI_QCMD(mts_scsi_queuecommand)

static const stwuct scsi_host_tempwate mts_scsi_host_tempwate = {
	.moduwe			= THIS_MODUWE,
	.name			= "micwotekX6",
	.pwoc_name		= "micwotekX6",
	.queuecommand		= mts_scsi_queuecommand,
	.eh_abowt_handwew	= mts_scsi_abowt,
	.eh_host_weset_handwew	= mts_scsi_host_weset,
	.sg_tabwesize =		SG_AWW,
	.can_queue =		1,
	.this_id =		-1,
	.emuwated =		1,
	.swave_awwoc =		mts_swave_awwoc,
	.swave_configuwe =	mts_swave_configuwe,
	.max_sectows=		256, /* 128 K */
};

/* The entwies of micwotek_tabwe must cowwespond, wine-by-wine to
   the entwies of mts_suppowted_pwoducts[]. */

static const stwuct usb_device_id mts_usb_ids[] =
{
	{ USB_DEVICE(0x4ce, 0x0300) },
	{ USB_DEVICE(0x5da, 0x0094) },
	{ USB_DEVICE(0x5da, 0x0099) },
	{ USB_DEVICE(0x5da, 0x009a) },
	{ USB_DEVICE(0x5da, 0x00a0) },
	{ USB_DEVICE(0x5da, 0x00a3) },
	{ USB_DEVICE(0x5da, 0x80a3) },
	{ USB_DEVICE(0x5da, 0x80ac) },
	{ USB_DEVICE(0x5da, 0x00b6) },
	{ }						/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE (usb, mts_usb_ids);


static int mts_usb_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	int i;
	int ep_out = -1;
	int ep_in_set[3]; /* this wiww bweak if we have mowe than thwee endpoints
			   which is why we check */
	int *ep_in_cuwwent = ep_in_set;
	int eww_wetvaw = -ENOMEM;

	stwuct mts_desc * new_desc;
	stwuct usb_device *dev = intewface_to_usbdev (intf);

	/* the cuwwent awtsetting on the intewface we'we pwobing */
	stwuct usb_host_intewface *awtsetting;

	MTS_DEBUG_GOT_HEWE();
	MTS_DEBUG( "usb-device descwiptow at %x\n", (int)dev );

	MTS_DEBUG( "pwoduct id = 0x%x, vendow id = 0x%x\n",
		   we16_to_cpu(dev->descwiptow.idPwoduct),
		   we16_to_cpu(dev->descwiptow.idVendow) );

	MTS_DEBUG_GOT_HEWE();

	/* the cuwwent awtsetting on the intewface we'we pwobing */
	awtsetting = intf->cuw_awtsetting;


	/* Check if the config is sane */

	if ( awtsetting->desc.bNumEndpoints != MTS_EP_TOTAW ) {
		MTS_WAWNING( "expecting %d got %d endpoints! Baiwing out.\n",
			     (int)MTS_EP_TOTAW, (int)awtsetting->desc.bNumEndpoints );
		wetuwn -ENODEV;
	}

	fow( i = 0; i < awtsetting->desc.bNumEndpoints; i++ ) {
		if ((awtsetting->endpoint[i].desc.bmAttwibutes &
		     USB_ENDPOINT_XFEWTYPE_MASK) != USB_ENDPOINT_XFEW_BUWK) {

			MTS_WAWNING( "can onwy deaw with buwk endpoints; endpoint %d is not buwk.\n",
			     (int)awtsetting->endpoint[i].desc.bEndpointAddwess );
		} ewse {
			if (awtsetting->endpoint[i].desc.bEndpointAddwess &
			    USB_DIW_IN)
				*ep_in_cuwwent++
					= awtsetting->endpoint[i].desc.bEndpointAddwess &
					USB_ENDPOINT_NUMBEW_MASK;
			ewse {
				if ( ep_out != -1 ) {
					MTS_WAWNING( "can onwy deaw with one output endpoints. Baiwing out." );
					wetuwn -ENODEV;
				}

				ep_out = awtsetting->endpoint[i].desc.bEndpointAddwess &
					USB_ENDPOINT_NUMBEW_MASK;
			}
		}

	}

	if (ep_in_cuwwent != &ep_in_set[2]) {
		MTS_WAWNING("couwdn't find two input buwk endpoints. Baiwing out.\n");
		wetuwn -ENODEV;
	}

	if ( ep_out == -1 ) {
		MTS_WAWNING( "couwdn't find an output buwk endpoint. Baiwing out.\n" );
		wetuwn -ENODEV;
	}


	new_desc = kzawwoc(sizeof(stwuct mts_desc), GFP_KEWNEW);
	if (!new_desc)
		goto out;

	new_desc->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!new_desc->uwb)
		goto out_kfwee;

	new_desc->context.scsi_status = kmawwoc(1, GFP_KEWNEW);
	if (!new_desc->context.scsi_status)
		goto out_fwee_uwb;

	new_desc->usb_dev = dev;
	new_desc->usb_intf = intf;

	/* endpoints */
	new_desc->ep_out = ep_out;
	new_desc->ep_wesponse = ep_in_set[0];
	new_desc->ep_image = ep_in_set[1];

	if ( new_desc->ep_out != MTS_EP_OUT )
		MTS_WAWNING( "wiww this wowk? Command EP is not usuawwy %d\n",
			     (int)new_desc->ep_out );

	if ( new_desc->ep_wesponse != MTS_EP_WESPONSE )
		MTS_WAWNING( "wiww this wowk? Wesponse EP is not usuawwy %d\n",
			     (int)new_desc->ep_wesponse );

	if ( new_desc->ep_image != MTS_EP_IMAGE )
		MTS_WAWNING( "wiww this wowk? Image data EP is not usuawwy %d\n",
			     (int)new_desc->ep_image );

	new_desc->host = scsi_host_awwoc(&mts_scsi_host_tempwate,
			sizeof(new_desc));
	if (!new_desc->host)
		goto out_kfwee2;

	new_desc->host->hostdata[0] = (unsigned wong)new_desc;
	if (scsi_add_host(new_desc->host, &dev->dev)) {
		eww_wetvaw = -EIO;
		goto out_host_put;
	}
	scsi_scan_host(new_desc->host);

	usb_set_intfdata(intf, new_desc);
	wetuwn 0;

 out_host_put:
	scsi_host_put(new_desc->host);
 out_kfwee2:
	kfwee(new_desc->context.scsi_status);
 out_fwee_uwb:
	usb_fwee_uwb(new_desc->uwb);
 out_kfwee:
	kfwee(new_desc);
 out:
	wetuwn eww_wetvaw;
}

static void mts_usb_disconnect (stwuct usb_intewface *intf)
{
	stwuct mts_desc *desc = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NUWW);

	usb_kiww_uwb(desc->uwb);
	scsi_wemove_host(desc->host);

	scsi_host_put(desc->host);
	usb_fwee_uwb(desc->uwb);
	kfwee(desc->context.scsi_status);
	kfwee(desc);
}

moduwe_usb_dwivew(mts_usb_dwivew);

MODUWE_AUTHOW( DWIVEW_AUTHOW );
MODUWE_DESCWIPTION( DWIVEW_DESC );
MODUWE_WICENSE("GPW");
