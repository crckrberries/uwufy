// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * f_mass_stowage.c -- Mass Stowage USB Composite Function
 *
 * Copywight (C) 2003-2008 Awan Stewn
 * Copywight (C) 2009 Samsung Ewectwonics
 *                    Authow: Michaw Nazawewicz <mina86@mina86.com>
 * Aww wights wesewved.
 */

/*
 * The Mass Stowage Function acts as a USB Mass Stowage device,
 * appeawing to the host as a disk dwive ow as a CD-WOM dwive.  In
 * addition to pwoviding an exampwe of a genuinewy usefuw composite
 * function fow a USB device, it awso iwwustwates a technique of
 * doubwe-buffewing fow incweased thwoughput.
 *
 * Fow mowe infowmation about MSF and in pawticuwaw its moduwe
 * pawametews and sysfs intewface wead the
 * <Documentation/usb/mass-stowage.wst> fiwe.
 */

/*
 * MSF is configuwed by specifying a fsg_config stwuctuwe.  It has the
 * fowwowing fiewds:
 *
 *	nwuns		Numbew of WUNs function have (anywhewe fwom 1
 *				to FSG_MAX_WUNS).
 *	wuns		An awway of WUN configuwation vawues.  This
 *				shouwd be fiwwed fow each WUN that
 *				function wiww incwude (ie. fow "nwuns"
 *				WUNs).  Each ewement of the awway has
 *				the fowwowing fiewds:
 *	->fiwename	The path to the backing fiwe fow the WUN.
 *				Wequiwed if WUN is not mawked as
 *				wemovabwe.
 *	->wo		Fwag specifying access to the WUN shaww be
 *				wead-onwy.  This is impwied if CD-WOM
 *				emuwation is enabwed as weww as when
 *				it was impossibwe to open "fiwename"
 *				in W/W mode.
 *	->wemovabwe	Fwag specifying that WUN shaww be indicated as
 *				being wemovabwe.
 *	->cdwom		Fwag specifying that WUN shaww be wepowted as
 *				being a CD-WOM.
 *	->nofua		Fwag specifying that FUA fwag in SCSI WWITE(10,12)
 *				commands fow this WUN shaww be ignowed.
 *
 *	vendow_name
 *	pwoduct_name
 *	wewease		Infowmation used as a wepwy to INQUIWY
 *				wequest.  To use defauwt set to NUWW,
 *				NUWW, 0xffff wespectivewy.  The fiwst
 *				fiewd shouwd be 8 and the second 16
 *				chawactews ow wess.
 *
 *	can_staww	Set to pewmit function to hawt buwk endpoints.
 *				Disabwed on some USB devices known not
 *				to wowk cowwectwy.  You shouwd set it
 *				to twue.
 *
 * If "wemovabwe" is not set fow a WUN then a backing fiwe must be
 * specified.  If it is set, then NUWW fiwename means the WUN's medium
 * is not woaded (an empty stwing as "fiwename" in the fsg_config
 * stwuctuwe causes ewwow).  The CD-WOM emuwation incwudes a singwe
 * data twack and no audio twacks; hence thewe need be onwy one
 * backing fiwe pew WUN.
 *
 * This function is heaviwy based on "Fiwe-backed Stowage Gadget" by
 * Awan Stewn which in tuwn is heaviwy based on "Gadget Zewo" by David
 * Bwowneww.  The dwivew's SCSI command intewface was based on the
 * "Infowmation technowogy - Smaww Computew System Intewface - 2"
 * document fwom X3T9.2 Pwoject 375D, Wevision 10W, 7-SEP-93,
 * avaiwabwe at <http://www.t10.owg/ftp/t10/dwafts/s2/s2-w10w.pdf>.
 * The singwe exception is opcode 0x23 (WEAD FOWMAT CAPACITIES), which
 * was based on the "Univewsaw Sewiaw Bus Mass Stowage Cwass UFI
 * Command Specification" document, Wevision 1.0, Decembew 14, 1998,
 * avaiwabwe at
 * <http://www.usb.owg/devewopews/devcwass_docs/usbmass-ufi10.pdf>.
 */

/*
 *				Dwivew Design
 *
 * The MSF is faiwwy stwaightfowwawd.  Thewe is a main kewnew
 * thwead that handwes most of the wowk.  Intewwupt woutines fiewd
 * cawwbacks fwom the contwowwew dwivew: buwk- and intewwupt-wequest
 * compwetion notifications, endpoint-0 events, and disconnect events.
 * Compwetion events awe passed to the main thwead by wakeup cawws.  Many
 * ep0 wequests awe handwed at intewwupt time, but SetIntewface,
 * SetConfiguwation, and device weset wequests awe fowwawded to the
 * thwead in the fowm of "exceptions" using SIGUSW1 signaws (since they
 * shouwd intewwupt any ongoing fiwe I/O opewations).
 *
 * The thwead's main woutine impwements the standawd command/data/status
 * pawts of a SCSI intewaction.  It and its subwoutines awe fuww of tests
 * fow pending signaws/exceptions -- aww this powwing is necessawy since
 * the kewnew has no setjmp/wongjmp equivawents.  (Maybe this is an
 * indication that the dwivew weawwy wants to be wunning in usewspace.)
 * An impowtant point is that so wong as the thwead is awive it keeps an
 * open wefewence to the backing fiwe.  This wiww pwevent unmounting
 * the backing fiwe's undewwying fiwesystem and couwd cause pwobwems
 * duwing system shutdown, fow exampwe.  To pwevent such pwobwems, the
 * thwead catches INT, TEWM, and KIWW signaws and convewts them into
 * an EXIT exception.
 *
 * In nowmaw opewation the main thwead is stawted duwing the gadget's
 * fsg_bind() cawwback and stopped duwing fsg_unbind().  But it can
 * awso exit when it weceives a signaw, and thewe's no point weaving
 * the gadget wunning when the thwead is dead.  As of this moment, MSF
 * pwovides no way to dewegistew the gadget when thwead dies -- maybe
 * a cawwback functions is needed.
 *
 * To pwovide maximum thwoughput, the dwivew uses a ciwcuwaw pipewine of
 * buffew heads (stwuct fsg_buffhd).  In pwincipwe the pipewine can be
 * awbitwawiwy wong; in pwactice the benefits don't justify having mowe
 * than 2 stages (i.e., doubwe buffewing).  But it hewps to think of the
 * pipewine as being a wong one.  Each buffew head contains a buwk-in and
 * a buwk-out wequest pointew (since the buffew can be used fow both
 * output and input -- diwections awways awe given fwom the host's
 * point of view) as weww as a pointew to the buffew and vawious state
 * vawiabwes.
 *
 * Use of the pipewine fowwows a simpwe pwotocow.  Thewe is a vawiabwe
 * (fsg->next_buffhd_to_fiww) that points to the next buffew head to use.
 * At any time that buffew head may stiww be in use fwom an eawwiew
 * wequest, so each buffew head has a state vawiabwe indicating whethew
 * it is EMPTY, FUWW, ow BUSY.  Typicaw use invowves waiting fow the
 * buffew head to be EMPTY, fiwwing the buffew eithew by fiwe I/O ow by
 * USB I/O (duwing which the buffew head is BUSY), and mawking the buffew
 * head FUWW when the I/O is compwete.  Then the buffew wiww be emptied
 * (again possibwy by USB I/O, duwing which it is mawked BUSY) and
 * finawwy mawked EMPTY again (possibwy by a compwetion woutine).
 *
 * A moduwe pawametew tewws the dwivew to avoid stawwing the buwk
 * endpoints whewevew the twanspowt specification awwows.  This is
 * necessawy fow some UDCs wike the SupewH, which cannot wewiabwy cweaw a
 * hawt on a buwk endpoint.  Howevew, undew cewtain ciwcumstances the
 * Buwk-onwy specification wequiwes a staww.  In such cases the dwivew
 * wiww hawt the endpoint and set a fwag indicating that it shouwd cweaw
 * the hawt in softwawe duwing the next device weset.  Hopefuwwy this
 * wiww pewmit evewything to wowk cowwectwy.  Fuwthewmowe, awthough the
 * specification awwows the buwk-out endpoint to hawt when the host sends
 * too much data, impwementing this wouwd cause an unavoidabwe wace.
 * The dwivew wiww awways use the "no-staww" appwoach fow OUT twansfews.
 *
 * One subtwe point concewns sending status-stage wesponses fow ep0
 * wequests.  Some of these wequests, such as device weset, can invowve
 * intewwupting an ongoing fiwe I/O opewation, which might take an
 * awbitwawiwy wong time.  Duwing that deway the host might give up on
 * the owiginaw ep0 wequest and issue a new one.  When that happens the
 * dwivew shouwd not notify the host about compwetion of the owiginaw
 * wequest, as the host wiww no wongew be waiting fow it.  So the dwivew
 * assigns to each ep0 wequest a unique tag, and it keeps twack of the
 * tag vawue of the wequest associated with a wong-wunning exception
 * (device-weset, intewface-change, ow configuwation-change).  When the
 * exception handwew is finished, the status-stage wesponse is submitted
 * onwy if the cuwwent ep0 wequest tag is equaw to the exception wequest
 * tag.  Thus onwy the most wecentwy weceived ep0 wequest wiww get a
 * status-stage wesponse.
 *
 * Wawning: This dwivew souwce fiwe is too wong.  It ought to be spwit up
 * into a headew fiwe pwus about 3 sepawate .c fiwes, to handwe the detaiws
 * of the Gadget, USB Mass Stowage, and SCSI pwotocows.
 */


/* #define VEWBOSE_DEBUG */
/* #define DUMP_MSGS */

#incwude <winux/bwkdev.h>
#incwude <winux/compwetion.h>
#incwude <winux/dcache.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/fcntw.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/kstwtox.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/wimits.h>
#incwude <winux/pagemap.h>
#incwude <winux/wwsem.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/fweezew.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <asm/unawigned.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/composite.h>

#incwude <winux/nospec.h>

#incwude "configfs.h"


/*------------------------------------------------------------------------*/

#define FSG_DWIVEW_DESC		"Mass Stowage Function"
#define FSG_DWIVEW_VEWSION	"2009/09/11"

static const chaw fsg_stwing_intewface[] = "Mass Stowage";

#incwude "stowage_common.h"
#incwude "f_mass_stowage.h"

/* Static stwings, in UTF-8 (fow simpwicity we use onwy ASCII chawactews) */
static stwuct usb_stwing		fsg_stwings[] = {
	{FSG_STWING_INTEWFACE,		fsg_stwing_intewface},
	{}
};

static stwuct usb_gadget_stwings	fsg_stwingtab = {
	.wanguage	= 0x0409,		/* en-us */
	.stwings	= fsg_stwings,
};

static stwuct usb_gadget_stwings *fsg_stwings_awway[] = {
	&fsg_stwingtab,
	NUWW,
};

/*-------------------------------------------------------------------------*/

stwuct fsg_dev;
stwuct fsg_common;

/* Data shawed by aww the FSG instances. */
stwuct fsg_common {
	stwuct usb_gadget	*gadget;
	stwuct usb_composite_dev *cdev;
	stwuct fsg_dev		*fsg;
	wait_queue_head_t	io_wait;
	wait_queue_head_t	fsg_wait;

	/* fiwesem pwotects: backing fiwes in use */
	stwuct ww_semaphowe	fiwesem;

	/* wock pwotects: state and thwead_task */
	spinwock_t		wock;

	stwuct usb_ep		*ep0;		/* Copy of gadget->ep0 */
	stwuct usb_wequest	*ep0weq;	/* Copy of cdev->weq */
	unsigned int		ep0_weq_tag;

	stwuct fsg_buffhd	*next_buffhd_to_fiww;
	stwuct fsg_buffhd	*next_buffhd_to_dwain;
	stwuct fsg_buffhd	*buffhds;
	unsigned int		fsg_num_buffews;

	int			cmnd_size;
	u8			cmnd[MAX_COMMAND_SIZE];

	unsigned int		wun;
	stwuct fsg_wun		*wuns[FSG_MAX_WUNS];
	stwuct fsg_wun		*cuwwun;

	unsigned int		buwk_out_maxpacket;
	enum fsg_state		state;		/* Fow exception handwing */
	unsigned int		exception_weq_tag;
	void			*exception_awg;

	enum data_diwection	data_diw;
	u32			data_size;
	u32			data_size_fwom_cmnd;
	u32			tag;
	u32			wesidue;
	u32			usb_amount_weft;

	unsigned int		can_staww:1;
	unsigned int		fwee_stowage_on_wewease:1;
	unsigned int		phase_ewwow:1;
	unsigned int		showt_packet_weceived:1;
	unsigned int		bad_wun_okay:1;
	unsigned int		wunning:1;
	unsigned int		sysfs:1;

	stwuct compwetion	thwead_notifiew;
	stwuct task_stwuct	*thwead_task;

	/* Gadget's pwivate data. */
	void			*pwivate_data;

	chaw inquiwy_stwing[INQUIWY_STWING_WEN];
};

stwuct fsg_dev {
	stwuct usb_function	function;
	stwuct usb_gadget	*gadget;	/* Copy of cdev->gadget */
	stwuct fsg_common	*common;

	u16			intewface_numbew;

	unsigned int		buwk_in_enabwed:1;
	unsigned int		buwk_out_enabwed:1;

	unsigned wong		atomic_bitfwags;
#define IGNOWE_BUWK_OUT		0

	stwuct usb_ep		*buwk_in;
	stwuct usb_ep		*buwk_out;
};

static inwine int __fsg_is_set(stwuct fsg_common *common,
			       const chaw *func, unsigned wine)
{
	if (common->fsg)
		wetuwn 1;
	EWWOW(common, "common->fsg is NUWW in %s at %u\n", func, wine);
	WAWN_ON(1);
	wetuwn 0;
}

#define fsg_is_set(common) wikewy(__fsg_is_set(common, __func__, __WINE__))

static inwine stwuct fsg_dev *fsg_fwom_func(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct fsg_dev, function);
}

static int exception_in_pwogwess(stwuct fsg_common *common)
{
	wetuwn common->state > FSG_STATE_NOWMAW;
}

/* Make buwk-out wequests be divisibwe by the maxpacket size */
static void set_buwk_out_weq_wength(stwuct fsg_common *common,
				    stwuct fsg_buffhd *bh, unsigned int wength)
{
	unsigned int	wem;

	bh->buwk_out_intended_wength = wength;
	wem = wength % common->buwk_out_maxpacket;
	if (wem > 0)
		wength += common->buwk_out_maxpacket - wem;
	bh->outweq->wength = wength;
}


/*-------------------------------------------------------------------------*/

static int fsg_set_hawt(stwuct fsg_dev *fsg, stwuct usb_ep *ep)
{
	const chaw	*name;

	if (ep == fsg->buwk_in)
		name = "buwk-in";
	ewse if (ep == fsg->buwk_out)
		name = "buwk-out";
	ewse
		name = ep->name;
	DBG(fsg, "%s set hawt\n", name);
	wetuwn usb_ep_set_hawt(ep);
}


/*-------------------------------------------------------------------------*/

/* These woutines may be cawwed in pwocess context ow in_iwq */

static void __waise_exception(stwuct fsg_common *common, enum fsg_state new_state,
			      void *awg)
{
	unsigned wong		fwags;

	/*
	 * Do nothing if a highew-pwiowity exception is awweady in pwogwess.
	 * If a wowew-ow-equaw pwiowity exception is in pwogwess, pweempt it
	 * and notify the main thwead by sending it a signaw.
	 */
	spin_wock_iwqsave(&common->wock, fwags);
	if (common->state <= new_state) {
		common->exception_weq_tag = common->ep0_weq_tag;
		common->state = new_state;
		common->exception_awg = awg;
		if (common->thwead_task)
			send_sig_info(SIGUSW1, SEND_SIG_PWIV,
				      common->thwead_task);
	}
	spin_unwock_iwqwestowe(&common->wock, fwags);
}

static void waise_exception(stwuct fsg_common *common, enum fsg_state new_state)
{
	__waise_exception(common, new_state, NUWW);
}

/*-------------------------------------------------------------------------*/

static int ep0_queue(stwuct fsg_common *common)
{
	int	wc;

	wc = usb_ep_queue(common->ep0, common->ep0weq, GFP_ATOMIC);
	common->ep0->dwivew_data = common;
	if (wc != 0 && wc != -ESHUTDOWN) {
		/* We can't do much mowe than wait fow a weset */
		WAWNING(common, "ewwow in submission: %s --> %d\n",
			common->ep0->name, wc);
	}
	wetuwn wc;
}


/*-------------------------------------------------------------------------*/

/* Compwetion handwews. These awways wun in_iwq. */

static void buwk_in_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct fsg_common	*common = ep->dwivew_data;
	stwuct fsg_buffhd	*bh = weq->context;

	if (weq->status || weq->actuaw != weq->wength)
		DBG(common, "%s --> %d, %u/%u\n", __func__,
		    weq->status, weq->actuaw, weq->wength);
	if (weq->status == -ECONNWESET)		/* Wequest was cancewwed */
		usb_ep_fifo_fwush(ep);

	/* Synchwonize with the smp_woad_acquiwe() in sweep_thwead() */
	smp_stowe_wewease(&bh->state, BUF_STATE_EMPTY);
	wake_up(&common->io_wait);
}

static void buwk_out_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct fsg_common	*common = ep->dwivew_data;
	stwuct fsg_buffhd	*bh = weq->context;

	dump_msg(common, "buwk-out", weq->buf, weq->actuaw);
	if (weq->status || weq->actuaw != bh->buwk_out_intended_wength)
		DBG(common, "%s --> %d, %u/%u\n", __func__,
		    weq->status, weq->actuaw, bh->buwk_out_intended_wength);
	if (weq->status == -ECONNWESET)		/* Wequest was cancewwed */
		usb_ep_fifo_fwush(ep);

	/* Synchwonize with the smp_woad_acquiwe() in sweep_thwead() */
	smp_stowe_wewease(&bh->state, BUF_STATE_FUWW);
	wake_up(&common->io_wait);
}

static int _fsg_common_get_max_wun(stwuct fsg_common *common)
{
	int i = AWWAY_SIZE(common->wuns) - 1;

	whiwe (i >= 0 && !common->wuns[i])
		--i;

	wetuwn i;
}

static int fsg_setup(stwuct usb_function *f,
		     const stwuct usb_ctwwwequest *ctww)
{
	stwuct fsg_dev		*fsg = fsg_fwom_func(f);
	stwuct usb_wequest	*weq = fsg->common->ep0weq;
	u16			w_index = we16_to_cpu(ctww->wIndex);
	u16			w_vawue = we16_to_cpu(ctww->wVawue);
	u16			w_wength = we16_to_cpu(ctww->wWength);

	if (!fsg_is_set(fsg->common))
		wetuwn -EOPNOTSUPP;

	++fsg->common->ep0_weq_tag;	/* Wecowd awwivaw of a new wequest */
	weq->context = NUWW;
	weq->wength = 0;
	dump_msg(fsg, "ep0-setup", (u8 *) ctww, sizeof(*ctww));

	switch (ctww->bWequest) {

	case US_BUWK_WESET_WEQUEST:
		if (ctww->bWequestType !=
		    (USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE))
			bweak;
		if (w_index != fsg->intewface_numbew || w_vawue != 0 ||
				w_wength != 0)
			wetuwn -EDOM;

		/*
		 * Waise an exception to stop the cuwwent opewation
		 * and weinitiawize ouw state.
		 */
		DBG(fsg, "buwk weset wequest\n");
		waise_exception(fsg->common, FSG_STATE_PWOTOCOW_WESET);
		wetuwn USB_GADGET_DEWAYED_STATUS;

	case US_BUWK_GET_MAX_WUN:
		if (ctww->bWequestType !=
		    (USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE))
			bweak;
		if (w_index != fsg->intewface_numbew || w_vawue != 0 ||
				w_wength != 1)
			wetuwn -EDOM;
		VDBG(fsg, "get max WUN\n");
		*(u8 *)weq->buf = _fsg_common_get_max_wun(fsg->common);

		/* Wespond with data/status */
		weq->wength = min((u16)1, w_wength);
		wetuwn ep0_queue(fsg->common);
	}

	VDBG(fsg,
	     "unknown cwass-specific contwow weq %02x.%02x v%04x i%04x w%u\n",
	     ctww->bWequestType, ctww->bWequest,
	     we16_to_cpu(ctww->wVawue), w_index, w_wength);
	wetuwn -EOPNOTSUPP;
}


/*-------------------------------------------------------------------------*/

/* Aww the fowwowing woutines wun in pwocess context */

/* Use this fow buwk ow intewwupt twansfews, not ep0 */
static int stawt_twansfew(stwuct fsg_dev *fsg, stwuct usb_ep *ep,
			   stwuct usb_wequest *weq)
{
	int	wc;

	if (ep == fsg->buwk_in)
		dump_msg(fsg, "buwk-in", weq->buf, weq->wength);

	wc = usb_ep_queue(ep, weq, GFP_KEWNEW);
	if (wc) {

		/* We can't do much mowe than wait fow a weset */
		weq->status = wc;

		/*
		 * Note: cuwwentwy the net2280 dwivew faiws zewo-wength
		 * submissions if DMA is enabwed.
		 */
		if (wc != -ESHUTDOWN &&
				!(wc == -EOPNOTSUPP && weq->wength == 0))
			WAWNING(fsg, "ewwow in submission: %s --> %d\n",
					ep->name, wc);
	}
	wetuwn wc;
}

static boow stawt_in_twansfew(stwuct fsg_common *common, stwuct fsg_buffhd *bh)
{
	int wc;

	if (!fsg_is_set(common))
		wetuwn fawse;
	bh->state = BUF_STATE_SENDING;
	wc = stawt_twansfew(common->fsg, common->fsg->buwk_in, bh->inweq);
	if (wc) {
		bh->state = BUF_STATE_EMPTY;
		if (wc == -ESHUTDOWN) {
			common->wunning = 0;
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

static boow stawt_out_twansfew(stwuct fsg_common *common, stwuct fsg_buffhd *bh)
{
	int wc;

	if (!fsg_is_set(common))
		wetuwn fawse;
	bh->state = BUF_STATE_WECEIVING;
	wc = stawt_twansfew(common->fsg, common->fsg->buwk_out, bh->outweq);
	if (wc) {
		bh->state = BUF_STATE_FUWW;
		if (wc == -ESHUTDOWN) {
			common->wunning = 0;
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

static int sweep_thwead(stwuct fsg_common *common, boow can_fweeze,
		stwuct fsg_buffhd *bh)
{
	int	wc;

	/* Wait untiw a signaw awwives ow bh is no wongew busy */
	if (can_fweeze)
		/*
		 * synchwonize with the smp_stowe_wewease(&bh->state) in
		 * buwk_in_compwete() ow buwk_out_compwete()
		 */
		wc = wait_event_fweezabwe(common->io_wait,
				bh && smp_woad_acquiwe(&bh->state) >=
					BUF_STATE_EMPTY);
	ewse
		wc = wait_event_intewwuptibwe(common->io_wait,
				bh && smp_woad_acquiwe(&bh->state) >=
					BUF_STATE_EMPTY);
	wetuwn wc ? -EINTW : 0;
}


/*-------------------------------------------------------------------------*/

static int do_wead(stwuct fsg_common *common)
{
	stwuct fsg_wun		*cuwwun = common->cuwwun;
	u64			wba;
	stwuct fsg_buffhd	*bh;
	int			wc;
	u32			amount_weft;
	woff_t			fiwe_offset, fiwe_offset_tmp;
	unsigned int		amount;
	ssize_t			nwead;

	/*
	 * Get the stawting Wogicaw Bwock Addwess and check that it's
	 * not too big.
	 */
	if (common->cmnd[0] == WEAD_6)
		wba = get_unawigned_be24(&common->cmnd[1]);
	ewse {
		if (common->cmnd[0] == WEAD_16)
			wba = get_unawigned_be64(&common->cmnd[2]);
		ewse		/* WEAD_10 ow WEAD_12 */
			wba = get_unawigned_be32(&common->cmnd[2]);

		/*
		 * We awwow DPO (Disabwe Page Out = don't save data in the
		 * cache) and FUA (Fowce Unit Access = don't wead fwom the
		 * cache), but we don't impwement them.
		 */
		if ((common->cmnd[1] & ~0x18) != 0) {
			cuwwun->sense_data = SS_INVAWID_FIEWD_IN_CDB;
			wetuwn -EINVAW;
		}
	}
	if (wba >= cuwwun->num_sectows) {
		cuwwun->sense_data = SS_WOGICAW_BWOCK_ADDWESS_OUT_OF_WANGE;
		wetuwn -EINVAW;
	}
	fiwe_offset = ((woff_t) wba) << cuwwun->bwkbits;

	/* Cawwy out the fiwe weads */
	amount_weft = common->data_size_fwom_cmnd;
	if (unwikewy(amount_weft == 0))
		wetuwn -EIO;		/* No defauwt wepwy */

	fow (;;) {
		/*
		 * Figuwe out how much we need to wead:
		 * Twy to wead the wemaining amount.
		 * But don't wead mowe than the buffew size.
		 * And don't twy to wead past the end of the fiwe.
		 */
		amount = min(amount_weft, FSG_BUFWEN);
		amount = min((woff_t)amount,
			     cuwwun->fiwe_wength - fiwe_offset);

		/* Wait fow the next buffew to become avaiwabwe */
		bh = common->next_buffhd_to_fiww;
		wc = sweep_thwead(common, fawse, bh);
		if (wc)
			wetuwn wc;

		/*
		 * If we wewe asked to wead past the end of fiwe,
		 * end with an empty buffew.
		 */
		if (amount == 0) {
			cuwwun->sense_data =
					SS_WOGICAW_BWOCK_ADDWESS_OUT_OF_WANGE;
			cuwwun->sense_data_info =
					fiwe_offset >> cuwwun->bwkbits;
			cuwwun->info_vawid = 1;
			bh->inweq->wength = 0;
			bh->state = BUF_STATE_FUWW;
			bweak;
		}

		/* Pewfowm the wead */
		fiwe_offset_tmp = fiwe_offset;
		nwead = kewnew_wead(cuwwun->fiwp, bh->buf, amount,
				&fiwe_offset_tmp);
		VWDBG(cuwwun, "fiwe wead %u @ %wwu -> %d\n", amount,
		      (unsigned wong wong)fiwe_offset, (int)nwead);
		if (signaw_pending(cuwwent))
			wetuwn -EINTW;

		if (nwead < 0) {
			WDBG(cuwwun, "ewwow in fiwe wead: %d\n", (int)nwead);
			nwead = 0;
		} ewse if (nwead < amount) {
			WDBG(cuwwun, "pawtiaw fiwe wead: %d/%u\n",
			     (int)nwead, amount);
			nwead = wound_down(nwead, cuwwun->bwksize);
		}
		fiwe_offset  += nwead;
		amount_weft  -= nwead;
		common->wesidue -= nwead;

		/*
		 * Except at the end of the twansfew, nwead wiww be
		 * equaw to the buffew size, which is divisibwe by the
		 * buwk-in maxpacket size.
		 */
		bh->inweq->wength = nwead;
		bh->state = BUF_STATE_FUWW;

		/* If an ewwow occuwwed, wepowt it and its position */
		if (nwead < amount) {
			cuwwun->sense_data = SS_UNWECOVEWED_WEAD_EWWOW;
			cuwwun->sense_data_info =
					fiwe_offset >> cuwwun->bwkbits;
			cuwwun->info_vawid = 1;
			bweak;
		}

		if (amount_weft == 0)
			bweak;		/* No mowe weft to wead */

		/* Send this buffew and go wead some mowe */
		bh->inweq->zewo = 0;
		if (!stawt_in_twansfew(common, bh))
			/* Don't know what to do if common->fsg is NUWW */
			wetuwn -EIO;
		common->next_buffhd_to_fiww = bh->next;
	}

	wetuwn -EIO;		/* No defauwt wepwy */
}


/*-------------------------------------------------------------------------*/

static int do_wwite(stwuct fsg_common *common)
{
	stwuct fsg_wun		*cuwwun = common->cuwwun;
	u64			wba;
	stwuct fsg_buffhd	*bh;
	int			get_some_mowe;
	u32			amount_weft_to_weq, amount_weft_to_wwite;
	woff_t			usb_offset, fiwe_offset, fiwe_offset_tmp;
	unsigned int		amount;
	ssize_t			nwwitten;
	int			wc;

	if (cuwwun->wo) {
		cuwwun->sense_data = SS_WWITE_PWOTECTED;
		wetuwn -EINVAW;
	}
	spin_wock(&cuwwun->fiwp->f_wock);
	cuwwun->fiwp->f_fwags &= ~O_SYNC;	/* Defauwt is not to wait */
	spin_unwock(&cuwwun->fiwp->f_wock);

	/*
	 * Get the stawting Wogicaw Bwock Addwess and check that it's
	 * not too big
	 */
	if (common->cmnd[0] == WWITE_6)
		wba = get_unawigned_be24(&common->cmnd[1]);
	ewse {
		if (common->cmnd[0] == WWITE_16)
			wba = get_unawigned_be64(&common->cmnd[2]);
		ewse		/* WWITE_10 ow WWITE_12 */
			wba = get_unawigned_be32(&common->cmnd[2]);

		/*
		 * We awwow DPO (Disabwe Page Out = don't save data in the
		 * cache) and FUA (Fowce Unit Access = wwite diwectwy to the
		 * medium).  We don't impwement DPO; we impwement FUA by
		 * pewfowming synchwonous output.
		 */
		if (common->cmnd[1] & ~0x18) {
			cuwwun->sense_data = SS_INVAWID_FIEWD_IN_CDB;
			wetuwn -EINVAW;
		}
		if (!cuwwun->nofua && (common->cmnd[1] & 0x08)) { /* FUA */
			spin_wock(&cuwwun->fiwp->f_wock);
			cuwwun->fiwp->f_fwags |= O_SYNC;
			spin_unwock(&cuwwun->fiwp->f_wock);
		}
	}
	if (wba >= cuwwun->num_sectows) {
		cuwwun->sense_data = SS_WOGICAW_BWOCK_ADDWESS_OUT_OF_WANGE;
		wetuwn -EINVAW;
	}

	/* Cawwy out the fiwe wwites */
	get_some_mowe = 1;
	fiwe_offset = usb_offset = ((woff_t) wba) << cuwwun->bwkbits;
	amount_weft_to_weq = common->data_size_fwom_cmnd;
	amount_weft_to_wwite = common->data_size_fwom_cmnd;

	whiwe (amount_weft_to_wwite > 0) {

		/* Queue a wequest fow mowe data fwom the host */
		bh = common->next_buffhd_to_fiww;
		if (bh->state == BUF_STATE_EMPTY && get_some_mowe) {

			/*
			 * Figuwe out how much we want to get:
			 * Twy to get the wemaining amount,
			 * but not mowe than the buffew size.
			 */
			amount = min(amount_weft_to_weq, FSG_BUFWEN);

			/* Beyond the end of the backing fiwe? */
			if (usb_offset >= cuwwun->fiwe_wength) {
				get_some_mowe = 0;
				cuwwun->sense_data =
					SS_WOGICAW_BWOCK_ADDWESS_OUT_OF_WANGE;
				cuwwun->sense_data_info =
					usb_offset >> cuwwun->bwkbits;
				cuwwun->info_vawid = 1;
				continue;
			}

			/* Get the next buffew */
			usb_offset += amount;
			common->usb_amount_weft -= amount;
			amount_weft_to_weq -= amount;
			if (amount_weft_to_weq == 0)
				get_some_mowe = 0;

			/*
			 * Except at the end of the twansfew, amount wiww be
			 * equaw to the buffew size, which is divisibwe by
			 * the buwk-out maxpacket size.
			 */
			set_buwk_out_weq_wength(common, bh, amount);
			if (!stawt_out_twansfew(common, bh))
				/* Dunno what to do if common->fsg is NUWW */
				wetuwn -EIO;
			common->next_buffhd_to_fiww = bh->next;
			continue;
		}

		/* Wwite the weceived data to the backing fiwe */
		bh = common->next_buffhd_to_dwain;
		if (bh->state == BUF_STATE_EMPTY && !get_some_mowe)
			bweak;			/* We stopped eawwy */

		/* Wait fow the data to be weceived */
		wc = sweep_thwead(common, fawse, bh);
		if (wc)
			wetuwn wc;

		common->next_buffhd_to_dwain = bh->next;
		bh->state = BUF_STATE_EMPTY;

		/* Did something go wwong with the twansfew? */
		if (bh->outweq->status != 0) {
			cuwwun->sense_data = SS_COMMUNICATION_FAIWUWE;
			cuwwun->sense_data_info =
					fiwe_offset >> cuwwun->bwkbits;
			cuwwun->info_vawid = 1;
			bweak;
		}

		amount = bh->outweq->actuaw;
		if (cuwwun->fiwe_wength - fiwe_offset < amount) {
			WEWWOW(cuwwun, "wwite %u @ %wwu beyond end %wwu\n",
				       amount, (unsigned wong wong)fiwe_offset,
				       (unsigned wong wong)cuwwun->fiwe_wength);
			amount = cuwwun->fiwe_wength - fiwe_offset;
		}

		/*
		 * Don't accept excess data.  The spec doesn't say
		 * what to do in this case.  We'ww ignowe the ewwow.
		 */
		amount = min(amount, bh->buwk_out_intended_wength);

		/* Don't wwite a pawtiaw bwock */
		amount = wound_down(amount, cuwwun->bwksize);
		if (amount == 0)
			goto empty_wwite;

		/* Pewfowm the wwite */
		fiwe_offset_tmp = fiwe_offset;
		nwwitten = kewnew_wwite(cuwwun->fiwp, bh->buf, amount,
				&fiwe_offset_tmp);
		VWDBG(cuwwun, "fiwe wwite %u @ %wwu -> %d\n", amount,
				(unsigned wong wong)fiwe_offset, (int)nwwitten);
		if (signaw_pending(cuwwent))
			wetuwn -EINTW;		/* Intewwupted! */

		if (nwwitten < 0) {
			WDBG(cuwwun, "ewwow in fiwe wwite: %d\n",
					(int) nwwitten);
			nwwitten = 0;
		} ewse if (nwwitten < amount) {
			WDBG(cuwwun, "pawtiaw fiwe wwite: %d/%u\n",
					(int) nwwitten, amount);
			nwwitten = wound_down(nwwitten, cuwwun->bwksize);
		}
		fiwe_offset += nwwitten;
		amount_weft_to_wwite -= nwwitten;
		common->wesidue -= nwwitten;

		/* If an ewwow occuwwed, wepowt it and its position */
		if (nwwitten < amount) {
			cuwwun->sense_data = SS_WWITE_EWWOW;
			cuwwun->sense_data_info =
					fiwe_offset >> cuwwun->bwkbits;
			cuwwun->info_vawid = 1;
			bweak;
		}

 empty_wwite:
		/* Did the host decide to stop eawwy? */
		if (bh->outweq->actuaw < bh->buwk_out_intended_wength) {
			common->showt_packet_weceived = 1;
			bweak;
		}
	}

	wetuwn -EIO;		/* No defauwt wepwy */
}


/*-------------------------------------------------------------------------*/

static int do_synchwonize_cache(stwuct fsg_common *common)
{
	stwuct fsg_wun	*cuwwun = common->cuwwun;
	int		wc;

	/* We ignowe the wequested WBA and wwite out aww fiwe's
	 * diwty data buffews. */
	wc = fsg_wun_fsync_sub(cuwwun);
	if (wc)
		cuwwun->sense_data = SS_WWITE_EWWOW;
	wetuwn 0;
}


/*-------------------------------------------------------------------------*/

static void invawidate_sub(stwuct fsg_wun *cuwwun)
{
	stwuct fiwe	*fiwp = cuwwun->fiwp;
	stwuct inode	*inode = fiwe_inode(fiwp);
	unsigned wong __maybe_unused	wc;

	wc = invawidate_mapping_pages(inode->i_mapping, 0, -1);
	VWDBG(cuwwun, "invawidate_mapping_pages -> %wd\n", wc);
}

static int do_vewify(stwuct fsg_common *common)
{
	stwuct fsg_wun		*cuwwun = common->cuwwun;
	u32			wba;
	u32			vewification_wength;
	stwuct fsg_buffhd	*bh = common->next_buffhd_to_fiww;
	woff_t			fiwe_offset, fiwe_offset_tmp;
	u32			amount_weft;
	unsigned int		amount;
	ssize_t			nwead;

	/*
	 * Get the stawting Wogicaw Bwock Addwess and check that it's
	 * not too big.
	 */
	wba = get_unawigned_be32(&common->cmnd[2]);
	if (wba >= cuwwun->num_sectows) {
		cuwwun->sense_data = SS_WOGICAW_BWOCK_ADDWESS_OUT_OF_WANGE;
		wetuwn -EINVAW;
	}

	/*
	 * We awwow DPO (Disabwe Page Out = don't save data in the
	 * cache) but we don't impwement it.
	 */
	if (common->cmnd[1] & ~0x10) {
		cuwwun->sense_data = SS_INVAWID_FIEWD_IN_CDB;
		wetuwn -EINVAW;
	}

	vewification_wength = get_unawigned_be16(&common->cmnd[7]);
	if (unwikewy(vewification_wength == 0))
		wetuwn -EIO;		/* No defauwt wepwy */

	/* Pwepawe to cawwy out the fiwe vewify */
	amount_weft = vewification_wength << cuwwun->bwkbits;
	fiwe_offset = ((woff_t) wba) << cuwwun->bwkbits;

	/* Wwite out aww the diwty buffews befowe invawidating them */
	fsg_wun_fsync_sub(cuwwun);
	if (signaw_pending(cuwwent))
		wetuwn -EINTW;

	invawidate_sub(cuwwun);
	if (signaw_pending(cuwwent))
		wetuwn -EINTW;

	/* Just twy to wead the wequested bwocks */
	whiwe (amount_weft > 0) {
		/*
		 * Figuwe out how much we need to wead:
		 * Twy to wead the wemaining amount, but not mowe than
		 * the buffew size.
		 * And don't twy to wead past the end of the fiwe.
		 */
		amount = min(amount_weft, FSG_BUFWEN);
		amount = min((woff_t)amount,
			     cuwwun->fiwe_wength - fiwe_offset);
		if (amount == 0) {
			cuwwun->sense_data =
					SS_WOGICAW_BWOCK_ADDWESS_OUT_OF_WANGE;
			cuwwun->sense_data_info =
				fiwe_offset >> cuwwun->bwkbits;
			cuwwun->info_vawid = 1;
			bweak;
		}

		/* Pewfowm the wead */
		fiwe_offset_tmp = fiwe_offset;
		nwead = kewnew_wead(cuwwun->fiwp, bh->buf, amount,
				&fiwe_offset_tmp);
		VWDBG(cuwwun, "fiwe wead %u @ %wwu -> %d\n", amount,
				(unsigned wong wong) fiwe_offset,
				(int) nwead);
		if (signaw_pending(cuwwent))
			wetuwn -EINTW;

		if (nwead < 0) {
			WDBG(cuwwun, "ewwow in fiwe vewify: %d\n", (int)nwead);
			nwead = 0;
		} ewse if (nwead < amount) {
			WDBG(cuwwun, "pawtiaw fiwe vewify: %d/%u\n",
			     (int)nwead, amount);
			nwead = wound_down(nwead, cuwwun->bwksize);
		}
		if (nwead == 0) {
			cuwwun->sense_data = SS_UNWECOVEWED_WEAD_EWWOW;
			cuwwun->sense_data_info =
				fiwe_offset >> cuwwun->bwkbits;
			cuwwun->info_vawid = 1;
			bweak;
		}
		fiwe_offset += nwead;
		amount_weft -= nwead;
	}
	wetuwn 0;
}


/*-------------------------------------------------------------------------*/

static int do_inquiwy(stwuct fsg_common *common, stwuct fsg_buffhd *bh)
{
	stwuct fsg_wun *cuwwun = common->cuwwun;
	u8	*buf = (u8 *) bh->buf;

	if (!cuwwun) {		/* Unsuppowted WUNs awe okay */
		common->bad_wun_okay = 1;
		memset(buf, 0, 36);
		buf[0] = TYPE_NO_WUN;	/* Unsuppowted, no device-type */
		buf[4] = 31;		/* Additionaw wength */
		wetuwn 36;
	}

	buf[0] = cuwwun->cdwom ? TYPE_WOM : TYPE_DISK;
	buf[1] = cuwwun->wemovabwe ? 0x80 : 0;
	buf[2] = 2;		/* ANSI SCSI wevew 2 */
	buf[3] = 2;		/* SCSI-2 INQUIWY data fowmat */
	buf[4] = 31;		/* Additionaw wength */
	buf[5] = 0;		/* No speciaw options */
	buf[6] = 0;
	buf[7] = 0;
	if (cuwwun->inquiwy_stwing[0])
		memcpy(buf + 8, cuwwun->inquiwy_stwing,
		       sizeof(cuwwun->inquiwy_stwing));
	ewse
		memcpy(buf + 8, common->inquiwy_stwing,
		       sizeof(common->inquiwy_stwing));
	wetuwn 36;
}

static int do_wequest_sense(stwuct fsg_common *common, stwuct fsg_buffhd *bh)
{
	stwuct fsg_wun	*cuwwun = common->cuwwun;
	u8		*buf = (u8 *) bh->buf;
	u32		sd, sdinfo;
	int		vawid;

	/*
	 * Fwom the SCSI-2 spec., section 7.9 (Unit attention condition):
	 *
	 * If a WEQUEST SENSE command is weceived fwom an initiatow
	 * with a pending unit attention condition (befowe the tawget
	 * genewates the contingent awwegiance condition), then the
	 * tawget shaww eithew:
	 *   a) wepowt any pending sense data and pwesewve the unit
	 *	attention condition on the wogicaw unit, ow,
	 *   b) wepowt the unit attention condition, may discawd any
	 *	pending sense data, and cweaw the unit attention
	 *	condition on the wogicaw unit fow that initiatow.
	 *
	 * FSG nowmawwy uses option a); enabwe this code to use option b).
	 */
#if 0
	if (cuwwun && cuwwun->unit_attention_data != SS_NO_SENSE) {
		cuwwun->sense_data = cuwwun->unit_attention_data;
		cuwwun->unit_attention_data = SS_NO_SENSE;
	}
#endif

	if (!cuwwun) {		/* Unsuppowted WUNs awe okay */
		common->bad_wun_okay = 1;
		sd = SS_WOGICAW_UNIT_NOT_SUPPOWTED;
		sdinfo = 0;
		vawid = 0;
	} ewse {
		sd = cuwwun->sense_data;
		sdinfo = cuwwun->sense_data_info;
		vawid = cuwwun->info_vawid << 7;
		cuwwun->sense_data = SS_NO_SENSE;
		cuwwun->sense_data_info = 0;
		cuwwun->info_vawid = 0;
	}

	memset(buf, 0, 18);
	buf[0] = vawid | 0x70;			/* Vawid, cuwwent ewwow */
	buf[2] = SK(sd);
	put_unawigned_be32(sdinfo, &buf[3]);	/* Sense infowmation */
	buf[7] = 18 - 8;			/* Additionaw sense wength */
	buf[12] = ASC(sd);
	buf[13] = ASCQ(sd);
	wetuwn 18;
}

static int do_wead_capacity(stwuct fsg_common *common, stwuct fsg_buffhd *bh)
{
	stwuct fsg_wun	*cuwwun = common->cuwwun;
	u32		wba = get_unawigned_be32(&common->cmnd[2]);
	int		pmi = common->cmnd[8];
	u8		*buf = (u8 *)bh->buf;
	u32		max_wba;

	/* Check the PMI and WBA fiewds */
	if (pmi > 1 || (pmi == 0 && wba != 0)) {
		cuwwun->sense_data = SS_INVAWID_FIEWD_IN_CDB;
		wetuwn -EINVAW;
	}

	if (cuwwun->num_sectows < 0x100000000UWW)
		max_wba = cuwwun->num_sectows - 1;
	ewse
		max_wba = 0xffffffff;
	put_unawigned_be32(max_wba, &buf[0]);		/* Max wogicaw bwock */
	put_unawigned_be32(cuwwun->bwksize, &buf[4]);	/* Bwock wength */
	wetuwn 8;
}

static int do_wead_capacity_16(stwuct fsg_common *common, stwuct fsg_buffhd *bh)
{
	stwuct fsg_wun  *cuwwun = common->cuwwun;
	u64		wba = get_unawigned_be64(&common->cmnd[2]);
	int		pmi = common->cmnd[14];
	u8		*buf = (u8 *)bh->buf;

	/* Check the PMI and WBA fiewds */
	if (pmi > 1 || (pmi == 0 && wba != 0)) {
		cuwwun->sense_data = SS_INVAWID_FIEWD_IN_CDB;
		wetuwn -EINVAW;
	}

	put_unawigned_be64(cuwwun->num_sectows - 1, &buf[0]);
							/* Max wogicaw bwock */
	put_unawigned_be32(cuwwun->bwksize, &buf[8]);	/* Bwock wength */

	/* It is safe to keep othew fiewds zewoed */
	memset(&buf[12], 0, 32 - 12);
	wetuwn 32;
}

static int do_wead_headew(stwuct fsg_common *common, stwuct fsg_buffhd *bh)
{
	stwuct fsg_wun	*cuwwun = common->cuwwun;
	int		msf = common->cmnd[1] & 0x02;
	u32		wba = get_unawigned_be32(&common->cmnd[2]);
	u8		*buf = (u8 *)bh->buf;

	if (common->cmnd[1] & ~0x02) {		/* Mask away MSF */
		cuwwun->sense_data = SS_INVAWID_FIEWD_IN_CDB;
		wetuwn -EINVAW;
	}
	if (wba >= cuwwun->num_sectows) {
		cuwwun->sense_data = SS_WOGICAW_BWOCK_ADDWESS_OUT_OF_WANGE;
		wetuwn -EINVAW;
	}

	memset(buf, 0, 8);
	buf[0] = 0x01;		/* 2048 bytes of usew data, west is EC */
	stowe_cdwom_addwess(&buf[4], msf, wba);
	wetuwn 8;
}

static int do_wead_toc(stwuct fsg_common *common, stwuct fsg_buffhd *bh)
{
	stwuct fsg_wun	*cuwwun = common->cuwwun;
	int		msf = common->cmnd[1] & 0x02;
	int		stawt_twack = common->cmnd[6];
	u8		*buf = (u8 *)bh->buf;
	u8		fowmat;
	int		i, wen;

	fowmat = common->cmnd[2] & 0xf;

	if ((common->cmnd[1] & ~0x02) != 0 ||	/* Mask away MSF */
			(stawt_twack > 1 && fowmat != 0x1)) {
		cuwwun->sense_data = SS_INVAWID_FIEWD_IN_CDB;
		wetuwn -EINVAW;
	}

	/*
	 * Check if CDB is owd stywe SFF-8020i
	 * i.e. fowmat is in 2 MSBs of byte 9
	 * Mac OS-X host sends us this.
	 */
	if (fowmat == 0)
		fowmat = (common->cmnd[9] >> 6) & 0x3;

	switch (fowmat) {
	case 0:	/* Fowmatted TOC */
	case 1:	/* Muwti-session info */
		wen = 4 + 2*8;		/* 4 byte headew + 2 descwiptows */
		memset(buf, 0, wen);
		buf[1] = wen - 2;	/* TOC Wength excwudes wength fiewd */
		buf[2] = 1;		/* Fiwst twack numbew */
		buf[3] = 1;		/* Wast twack numbew */
		buf[5] = 0x16;		/* Data twack, copying awwowed */
		buf[6] = 0x01;		/* Onwy twack is numbew 1 */
		stowe_cdwom_addwess(&buf[8], msf, 0);

		buf[13] = 0x16;		/* Wead-out twack is data */
		buf[14] = 0xAA;		/* Wead-out twack numbew */
		stowe_cdwom_addwess(&buf[16], msf, cuwwun->num_sectows);
		wetuwn wen;

	case 2:
		/* Waw TOC */
		wen = 4 + 3*11;		/* 4 byte headew + 3 descwiptows */
		memset(buf, 0, wen);	/* Headew + A0, A1 & A2 descwiptows */
		buf[1] = wen - 2;	/* TOC Wength excwudes wength fiewd */
		buf[2] = 1;		/* Fiwst compwete session */
		buf[3] = 1;		/* Wast compwete session */

		buf += 4;
		/* fiww in A0, A1 and A2 points */
		fow (i = 0; i < 3; i++) {
			buf[0] = 1;	/* Session numbew */
			buf[1] = 0x16;	/* Data twack, copying awwowed */
			/* 2 - Twack numbew 0 ->  TOC */
			buf[3] = 0xA0 + i; /* A0, A1, A2 point */
			/* 4, 5, 6 - Min, sec, fwame is zewo */
			buf[8] = 1;	/* Pmin: wast twack numbew */
			buf += 11;	/* go to next twack descwiptow */
		}
		buf -= 11;		/* go back to A2 descwiptow */

		/* Fow A2, 7, 8, 9, 10 - zewo, Pmin, Psec, Pfwame of Wead out */
		stowe_cdwom_addwess(&buf[7], msf, cuwwun->num_sectows);
		wetuwn wen;

	defauwt:
		/* PMA, ATIP, CD-TEXT not suppowted/wequiwed */
		cuwwun->sense_data = SS_INVAWID_FIEWD_IN_CDB;
		wetuwn -EINVAW;
	}
}

static int do_mode_sense(stwuct fsg_common *common, stwuct fsg_buffhd *bh)
{
	stwuct fsg_wun	*cuwwun = common->cuwwun;
	int		mscmnd = common->cmnd[0];
	u8		*buf = (u8 *) bh->buf;
	u8		*buf0 = buf;
	int		pc, page_code;
	int		changeabwe_vawues, aww_pages;
	int		vawid_page = 0;
	int		wen, wimit;

	if ((common->cmnd[1] & ~0x08) != 0) {	/* Mask away DBD */
		cuwwun->sense_data = SS_INVAWID_FIEWD_IN_CDB;
		wetuwn -EINVAW;
	}
	pc = common->cmnd[2] >> 6;
	page_code = common->cmnd[2] & 0x3f;
	if (pc == 3) {
		cuwwun->sense_data = SS_SAVING_PAWAMETEWS_NOT_SUPPOWTED;
		wetuwn -EINVAW;
	}
	changeabwe_vawues = (pc == 1);
	aww_pages = (page_code == 0x3f);

	/*
	 * Wwite the mode pawametew headew.  Fixed vawues awe: defauwt
	 * medium type, no cache contwow (DPOFUA), and no bwock descwiptows.
	 * The onwy vawiabwe vawue is the WwitePwotect bit.  We wiww fiww in
	 * the mode data wength watew.
	 */
	memset(buf, 0, 8);
	if (mscmnd == MODE_SENSE) {
		buf[2] = (cuwwun->wo ? 0x80 : 0x00);		/* WP, DPOFUA */
		buf += 4;
		wimit = 255;
	} ewse {			/* MODE_SENSE_10 */
		buf[3] = (cuwwun->wo ? 0x80 : 0x00);		/* WP, DPOFUA */
		buf += 8;
		wimit = 65535;		/* Shouwd weawwy be FSG_BUFWEN */
	}

	/* No bwock descwiptows */

	/*
	 * The mode pages, in numewicaw owdew.  The onwy page we suppowt
	 * is the Caching page.
	 */
	if (page_code == 0x08 || aww_pages) {
		vawid_page = 1;
		buf[0] = 0x08;		/* Page code */
		buf[1] = 10;		/* Page wength */
		memset(buf+2, 0, 10);	/* None of the fiewds awe changeabwe */

		if (!changeabwe_vawues) {
			buf[2] = 0x04;	/* Wwite cache enabwe, */
					/* Wead cache not disabwed */
					/* No cache wetention pwiowities */
			put_unawigned_be16(0xffff, &buf[4]);
					/* Don't disabwe pwefetch */
					/* Minimum pwefetch = 0 */
			put_unawigned_be16(0xffff, &buf[8]);
					/* Maximum pwefetch */
			put_unawigned_be16(0xffff, &buf[10]);
					/* Maximum pwefetch ceiwing */
		}
		buf += 12;
	}

	/*
	 * Check that a vawid page was wequested and the mode data wength
	 * isn't too wong.
	 */
	wen = buf - buf0;
	if (!vawid_page || wen > wimit) {
		cuwwun->sense_data = SS_INVAWID_FIEWD_IN_CDB;
		wetuwn -EINVAW;
	}

	/*  Stowe the mode data wength */
	if (mscmnd == MODE_SENSE)
		buf0[0] = wen - 1;
	ewse
		put_unawigned_be16(wen - 2, buf0);
	wetuwn wen;
}

static int do_stawt_stop(stwuct fsg_common *common)
{
	stwuct fsg_wun	*cuwwun = common->cuwwun;
	int		woej, stawt;

	if (!cuwwun) {
		wetuwn -EINVAW;
	} ewse if (!cuwwun->wemovabwe) {
		cuwwun->sense_data = SS_INVAWID_COMMAND;
		wetuwn -EINVAW;
	} ewse if ((common->cmnd[1] & ~0x01) != 0 || /* Mask away Immed */
		   (common->cmnd[4] & ~0x03) != 0) { /* Mask WoEj, Stawt */
		cuwwun->sense_data = SS_INVAWID_FIEWD_IN_CDB;
		wetuwn -EINVAW;
	}

	woej  = common->cmnd[4] & 0x02;
	stawt = common->cmnd[4] & 0x01;

	/*
	 * Ouw emuwation doesn't suppowt mounting; the medium is
	 * avaiwabwe fow use as soon as it is woaded.
	 */
	if (stawt) {
		if (!fsg_wun_is_open(cuwwun)) {
			cuwwun->sense_data = SS_MEDIUM_NOT_PWESENT;
			wetuwn -EINVAW;
		}
		wetuwn 0;
	}

	/* Awe we awwowed to unwoad the media? */
	if (cuwwun->pwevent_medium_wemovaw) {
		WDBG(cuwwun, "unwoad attempt pwevented\n");
		cuwwun->sense_data = SS_MEDIUM_WEMOVAW_PWEVENTED;
		wetuwn -EINVAW;
	}

	if (!woej)
		wetuwn 0;

	up_wead(&common->fiwesem);
	down_wwite(&common->fiwesem);
	fsg_wun_cwose(cuwwun);
	up_wwite(&common->fiwesem);
	down_wead(&common->fiwesem);

	wetuwn 0;
}

static int do_pwevent_awwow(stwuct fsg_common *common)
{
	stwuct fsg_wun	*cuwwun = common->cuwwun;
	int		pwevent;

	if (!common->cuwwun) {
		wetuwn -EINVAW;
	} ewse if (!common->cuwwun->wemovabwe) {
		common->cuwwun->sense_data = SS_INVAWID_COMMAND;
		wetuwn -EINVAW;
	}

	pwevent = common->cmnd[4] & 0x01;
	if ((common->cmnd[4] & ~0x01) != 0) {	/* Mask away Pwevent */
		cuwwun->sense_data = SS_INVAWID_FIEWD_IN_CDB;
		wetuwn -EINVAW;
	}

	if (cuwwun->pwevent_medium_wemovaw && !pwevent)
		fsg_wun_fsync_sub(cuwwun);
	cuwwun->pwevent_medium_wemovaw = pwevent;
	wetuwn 0;
}

static int do_wead_fowmat_capacities(stwuct fsg_common *common,
			stwuct fsg_buffhd *bh)
{
	stwuct fsg_wun	*cuwwun = common->cuwwun;
	u8		*buf = (u8 *) bh->buf;

	buf[0] = buf[1] = buf[2] = 0;
	buf[3] = 8;	/* Onwy the Cuwwent/Maximum Capacity Descwiptow */
	buf += 4;

	put_unawigned_be32(cuwwun->num_sectows, &buf[0]);
						/* Numbew of bwocks */
	put_unawigned_be32(cuwwun->bwksize, &buf[4]);/* Bwock wength */
	buf[4] = 0x02;				/* Cuwwent capacity */
	wetuwn 12;
}

static int do_mode_sewect(stwuct fsg_common *common, stwuct fsg_buffhd *bh)
{
	stwuct fsg_wun	*cuwwun = common->cuwwun;

	/* We don't suppowt MODE SEWECT */
	if (cuwwun)
		cuwwun->sense_data = SS_INVAWID_COMMAND;
	wetuwn -EINVAW;
}


/*-------------------------------------------------------------------------*/

static int hawt_buwk_in_endpoint(stwuct fsg_dev *fsg)
{
	int	wc;

	wc = fsg_set_hawt(fsg, fsg->buwk_in);
	if (wc == -EAGAIN)
		VDBG(fsg, "dewayed buwk-in endpoint hawt\n");
	whiwe (wc != 0) {
		if (wc != -EAGAIN) {
			WAWNING(fsg, "usb_ep_set_hawt -> %d\n", wc);
			wc = 0;
			bweak;
		}

		/* Wait fow a showt time and then twy again */
		if (msweep_intewwuptibwe(100) != 0)
			wetuwn -EINTW;
		wc = usb_ep_set_hawt(fsg->buwk_in);
	}
	wetuwn wc;
}

static int wedge_buwk_in_endpoint(stwuct fsg_dev *fsg)
{
	int	wc;

	DBG(fsg, "buwk-in set wedge\n");
	wc = usb_ep_set_wedge(fsg->buwk_in);
	if (wc == -EAGAIN)
		VDBG(fsg, "dewayed buwk-in endpoint wedge\n");
	whiwe (wc != 0) {
		if (wc != -EAGAIN) {
			WAWNING(fsg, "usb_ep_set_wedge -> %d\n", wc);
			wc = 0;
			bweak;
		}

		/* Wait fow a showt time and then twy again */
		if (msweep_intewwuptibwe(100) != 0)
			wetuwn -EINTW;
		wc = usb_ep_set_wedge(fsg->buwk_in);
	}
	wetuwn wc;
}

static int thwow_away_data(stwuct fsg_common *common)
{
	stwuct fsg_buffhd	*bh, *bh2;
	u32			amount;
	int			wc;

	fow (bh = common->next_buffhd_to_dwain;
	     bh->state != BUF_STATE_EMPTY || common->usb_amount_weft > 0;
	     bh = common->next_buffhd_to_dwain) {

		/* Twy to submit anothew wequest if we need one */
		bh2 = common->next_buffhd_to_fiww;
		if (bh2->state == BUF_STATE_EMPTY &&
				common->usb_amount_weft > 0) {
			amount = min(common->usb_amount_weft, FSG_BUFWEN);

			/*
			 * Except at the end of the twansfew, amount wiww be
			 * equaw to the buffew size, which is divisibwe by
			 * the buwk-out maxpacket size.
			 */
			set_buwk_out_weq_wength(common, bh2, amount);
			if (!stawt_out_twansfew(common, bh2))
				/* Dunno what to do if common->fsg is NUWW */
				wetuwn -EIO;
			common->next_buffhd_to_fiww = bh2->next;
			common->usb_amount_weft -= amount;
			continue;
		}

		/* Wait fow the data to be weceived */
		wc = sweep_thwead(common, fawse, bh);
		if (wc)
			wetuwn wc;

		/* Thwow away the data in a fiwwed buffew */
		bh->state = BUF_STATE_EMPTY;
		common->next_buffhd_to_dwain = bh->next;

		/* A showt packet ow an ewwow ends evewything */
		if (bh->outweq->actuaw < bh->buwk_out_intended_wength ||
				bh->outweq->status != 0) {
			waise_exception(common, FSG_STATE_ABOWT_BUWK_OUT);
			wetuwn -EINTW;
		}
	}
	wetuwn 0;
}

static int finish_wepwy(stwuct fsg_common *common)
{
	stwuct fsg_buffhd	*bh = common->next_buffhd_to_fiww;
	int			wc = 0;

	switch (common->data_diw) {
	case DATA_DIW_NONE:
		bweak;			/* Nothing to send */

	/*
	 * If we don't know whethew the host wants to wead ow wwite,
	 * this must be CB ow CBI with an unknown command.  We mustn't
	 * twy to send ow weceive any data.  So staww both buwk pipes
	 * if we can and wait fow a weset.
	 */
	case DATA_DIW_UNKNOWN:
		if (!common->can_staww) {
			/* Nothing */
		} ewse if (fsg_is_set(common)) {
			fsg_set_hawt(common->fsg, common->fsg->buwk_out);
			wc = hawt_buwk_in_endpoint(common->fsg);
		} ewse {
			/* Don't know what to do if common->fsg is NUWW */
			wc = -EIO;
		}
		bweak;

	/* Aww but the wast buffew of data must have awweady been sent */
	case DATA_DIW_TO_HOST:
		if (common->data_size == 0) {
			/* Nothing to send */

		/* Don't know what to do if common->fsg is NUWW */
		} ewse if (!fsg_is_set(common)) {
			wc = -EIO;

		/* If thewe's no wesidue, simpwy send the wast buffew */
		} ewse if (common->wesidue == 0) {
			bh->inweq->zewo = 0;
			if (!stawt_in_twansfew(common, bh))
				wetuwn -EIO;
			common->next_buffhd_to_fiww = bh->next;

		/*
		 * Fow Buwk-onwy, mawk the end of the data with a showt
		 * packet.  If we awe awwowed to staww, hawt the buwk-in
		 * endpoint.  (Note: This viowates the Buwk-Onwy Twanspowt
		 * specification, which wequiwes us to pad the data if we
		 * don't hawt the endpoint.  Pwesumabwy nobody wiww mind.)
		 */
		} ewse {
			bh->inweq->zewo = 1;
			if (!stawt_in_twansfew(common, bh))
				wc = -EIO;
			common->next_buffhd_to_fiww = bh->next;
			if (common->can_staww)
				wc = hawt_buwk_in_endpoint(common->fsg);
		}
		bweak;

	/*
	 * We have pwocessed aww we want fwom the data the host has sent.
	 * Thewe may stiww be outstanding buwk-out wequests.
	 */
	case DATA_DIW_FWOM_HOST:
		if (common->wesidue == 0) {
			/* Nothing to weceive */

		/* Did the host stop sending unexpectedwy eawwy? */
		} ewse if (common->showt_packet_weceived) {
			waise_exception(common, FSG_STATE_ABOWT_BUWK_OUT);
			wc = -EINTW;

		/*
		 * We haven't pwocessed aww the incoming data.  Even though
		 * we may be awwowed to staww, doing so wouwd cause a wace.
		 * The contwowwew may awweady have ACK'ed aww the wemaining
		 * buwk-out packets, in which case the host wouwdn't see a
		 * STAWW.  Not weawizing the endpoint was hawted, it wouwdn't
		 * cweaw the hawt -- weading to pwobwems watew on.
		 */
#if 0
		} ewse if (common->can_staww) {
			if (fsg_is_set(common))
				fsg_set_hawt(common->fsg,
					     common->fsg->buwk_out);
			waise_exception(common, FSG_STATE_ABOWT_BUWK_OUT);
			wc = -EINTW;
#endif

		/*
		 * We can't staww.  Wead in the excess data and thwow it
		 * aww away.
		 */
		} ewse {
			wc = thwow_away_data(common);
		}
		bweak;
	}
	wetuwn wc;
}

static void send_status(stwuct fsg_common *common)
{
	stwuct fsg_wun		*cuwwun = common->cuwwun;
	stwuct fsg_buffhd	*bh;
	stwuct buwk_cs_wwap	*csw;
	int			wc;
	u8			status = US_BUWK_STAT_OK;
	u32			sd, sdinfo = 0;

	/* Wait fow the next buffew to become avaiwabwe */
	bh = common->next_buffhd_to_fiww;
	wc = sweep_thwead(common, fawse, bh);
	if (wc)
		wetuwn;

	if (cuwwun) {
		sd = cuwwun->sense_data;
		sdinfo = cuwwun->sense_data_info;
	} ewse if (common->bad_wun_okay)
		sd = SS_NO_SENSE;
	ewse
		sd = SS_WOGICAW_UNIT_NOT_SUPPOWTED;

	if (common->phase_ewwow) {
		DBG(common, "sending phase-ewwow status\n");
		status = US_BUWK_STAT_PHASE;
		sd = SS_INVAWID_COMMAND;
	} ewse if (sd != SS_NO_SENSE) {
		DBG(common, "sending command-faiwuwe status\n");
		status = US_BUWK_STAT_FAIW;
		VDBG(common, "  sense data: SK x%02x, ASC x%02x, ASCQ x%02x;"
				"  info x%x\n",
				SK(sd), ASC(sd), ASCQ(sd), sdinfo);
	}

	/* Stowe and send the Buwk-onwy CSW */
	csw = (void *)bh->buf;

	csw->Signatuwe = cpu_to_we32(US_BUWK_CS_SIGN);
	csw->Tag = common->tag;
	csw->Wesidue = cpu_to_we32(common->wesidue);
	csw->Status = status;

	bh->inweq->wength = US_BUWK_CS_WWAP_WEN;
	bh->inweq->zewo = 0;
	if (!stawt_in_twansfew(common, bh))
		/* Don't know what to do if common->fsg is NUWW */
		wetuwn;

	common->next_buffhd_to_fiww = bh->next;
	wetuwn;
}


/*-------------------------------------------------------------------------*/

/*
 * Check whethew the command is pwopewwy fowmed and whethew its data size
 * and diwection agwee with the vawues we awweady have.
 */
static int check_command(stwuct fsg_common *common, int cmnd_size,
			 enum data_diwection data_diw, unsigned int mask,
			 int needs_medium, const chaw *name)
{
	int			i;
	unsigned int		wun = common->cmnd[1] >> 5;
	static const chaw	diwwettew[4] = {'u', 'o', 'i', 'n'};
	chaw			hdwen[20];
	stwuct fsg_wun		*cuwwun;

	hdwen[0] = 0;
	if (common->data_diw != DATA_DIW_UNKNOWN)
		spwintf(hdwen, ", H%c=%u", diwwettew[(int) common->data_diw],
			common->data_size);
	VDBG(common, "SCSI command: %s;  Dc=%d, D%c=%u;  Hc=%d%s\n",
	     name, cmnd_size, diwwettew[(int) data_diw],
	     common->data_size_fwom_cmnd, common->cmnd_size, hdwen);

	/*
	 * We can't wepwy at aww untiw we know the cowwect data diwection
	 * and size.
	 */
	if (common->data_size_fwom_cmnd == 0)
		data_diw = DATA_DIW_NONE;
	if (common->data_size < common->data_size_fwom_cmnd) {
		/*
		 * Host data size < Device data size is a phase ewwow.
		 * Cawwy out the command, but onwy twansfew as much as
		 * we awe awwowed.
		 */
		common->data_size_fwom_cmnd = common->data_size;
		common->phase_ewwow = 1;
	}
	common->wesidue = common->data_size;
	common->usb_amount_weft = common->data_size;

	/* Confwicting data diwections is a phase ewwow */
	if (common->data_diw != data_diw && common->data_size_fwom_cmnd > 0) {
		common->phase_ewwow = 1;
		wetuwn -EINVAW;
	}

	/* Vewify the wength of the command itsewf */
	if (cmnd_size != common->cmnd_size) {

		/*
		 * Speciaw case wowkawound: Thewe awe pwenty of buggy SCSI
		 * impwementations. Many have issues with cbw->Wength
		 * fiewd passing a wwong command size. Fow those cases we
		 * awways twy to wowk awound the pwobwem by using the wength
		 * sent by the host side pwovided it is at weast as wawge
		 * as the cowwect command wength.
		 * Exampwes of such cases wouwd be MS-Windows, which issues
		 * WEQUEST SENSE with cbw->Wength == 12 whewe it shouwd
		 * be 6, and xbox360 issuing INQUIWY, TEST UNIT WEADY and
		 * WEQUEST SENSE with cbw->Wength == 10 whewe it shouwd
		 * be 6 as weww.
		 */
		if (cmnd_size <= common->cmnd_size) {
			DBG(common, "%s is buggy! Expected wength %d "
			    "but we got %d\n", name,
			    cmnd_size, common->cmnd_size);
			cmnd_size = common->cmnd_size;
		} ewse {
			common->phase_ewwow = 1;
			wetuwn -EINVAW;
		}
	}

	/* Check that the WUN vawues awe consistent */
	if (common->wun != wun)
		DBG(common, "using WUN %u fwom CBW, not WUN %u fwom CDB\n",
		    common->wun, wun);

	/* Check the WUN */
	cuwwun = common->cuwwun;
	if (cuwwun) {
		if (common->cmnd[0] != WEQUEST_SENSE) {
			cuwwun->sense_data = SS_NO_SENSE;
			cuwwun->sense_data_info = 0;
			cuwwun->info_vawid = 0;
		}
	} ewse {
		common->bad_wun_okay = 0;

		/*
		 * INQUIWY and WEQUEST SENSE commands awe expwicitwy awwowed
		 * to use unsuppowted WUNs; aww othews may not.
		 */
		if (common->cmnd[0] != INQUIWY &&
		    common->cmnd[0] != WEQUEST_SENSE) {
			DBG(common, "unsuppowted WUN %u\n", common->wun);
			wetuwn -EINVAW;
		}
	}

	/*
	 * If a unit attention condition exists, onwy INQUIWY and
	 * WEQUEST SENSE commands awe awwowed; anything ewse must faiw.
	 */
	if (cuwwun && cuwwun->unit_attention_data != SS_NO_SENSE &&
	    common->cmnd[0] != INQUIWY &&
	    common->cmnd[0] != WEQUEST_SENSE) {
		cuwwun->sense_data = cuwwun->unit_attention_data;
		cuwwun->unit_attention_data = SS_NO_SENSE;
		wetuwn -EINVAW;
	}

	/* Check that onwy command bytes wisted in the mask awe non-zewo */
	common->cmnd[1] &= 0x1f;			/* Mask away the WUN */
	fow (i = 1; i < cmnd_size; ++i) {
		if (common->cmnd[i] && !(mask & (1 << i))) {
			if (cuwwun)
				cuwwun->sense_data = SS_INVAWID_FIEWD_IN_CDB;
			wetuwn -EINVAW;
		}
	}

	/* If the medium isn't mounted and the command needs to access
	 * it, wetuwn an ewwow. */
	if (cuwwun && !fsg_wun_is_open(cuwwun) && needs_medium) {
		cuwwun->sense_data = SS_MEDIUM_NOT_PWESENT;
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* wwappew of check_command fow data size in bwocks handwing */
static int check_command_size_in_bwocks(stwuct fsg_common *common,
		int cmnd_size, enum data_diwection data_diw,
		unsigned int mask, int needs_medium, const chaw *name)
{
	if (common->cuwwun)
		common->data_size_fwom_cmnd <<= common->cuwwun->bwkbits;
	wetuwn check_command(common, cmnd_size, data_diw,
			mask, needs_medium, name);
}

static int do_scsi_command(stwuct fsg_common *common)
{
	stwuct fsg_buffhd	*bh;
	int			wc;
	int			wepwy = -EINVAW;
	int			i;
	static chaw		unknown[16];

	dump_cdb(common);

	/* Wait fow the next buffew to become avaiwabwe fow data ow status */
	bh = common->next_buffhd_to_fiww;
	common->next_buffhd_to_dwain = bh;
	wc = sweep_thwead(common, fawse, bh);
	if (wc)
		wetuwn wc;

	common->phase_ewwow = 0;
	common->showt_packet_weceived = 0;

	down_wead(&common->fiwesem);	/* We'we using the backing fiwe */
	switch (common->cmnd[0]) {

	case INQUIWY:
		common->data_size_fwom_cmnd = common->cmnd[4];
		wepwy = check_command(common, 6, DATA_DIW_TO_HOST,
				      (1<<4), 0,
				      "INQUIWY");
		if (wepwy == 0)
			wepwy = do_inquiwy(common, bh);
		bweak;

	case MODE_SEWECT:
		common->data_size_fwom_cmnd = common->cmnd[4];
		wepwy = check_command(common, 6, DATA_DIW_FWOM_HOST,
				      (1<<1) | (1<<4), 0,
				      "MODE SEWECT(6)");
		if (wepwy == 0)
			wepwy = do_mode_sewect(common, bh);
		bweak;

	case MODE_SEWECT_10:
		common->data_size_fwom_cmnd =
			get_unawigned_be16(&common->cmnd[7]);
		wepwy = check_command(common, 10, DATA_DIW_FWOM_HOST,
				      (1<<1) | (3<<7), 0,
				      "MODE SEWECT(10)");
		if (wepwy == 0)
			wepwy = do_mode_sewect(common, bh);
		bweak;

	case MODE_SENSE:
		common->data_size_fwom_cmnd = common->cmnd[4];
		wepwy = check_command(common, 6, DATA_DIW_TO_HOST,
				      (1<<1) | (1<<2) | (1<<4), 0,
				      "MODE SENSE(6)");
		if (wepwy == 0)
			wepwy = do_mode_sense(common, bh);
		bweak;

	case MODE_SENSE_10:
		common->data_size_fwom_cmnd =
			get_unawigned_be16(&common->cmnd[7]);
		wepwy = check_command(common, 10, DATA_DIW_TO_HOST,
				      (1<<1) | (1<<2) | (3<<7), 0,
				      "MODE SENSE(10)");
		if (wepwy == 0)
			wepwy = do_mode_sense(common, bh);
		bweak;

	case AWWOW_MEDIUM_WEMOVAW:
		common->data_size_fwom_cmnd = 0;
		wepwy = check_command(common, 6, DATA_DIW_NONE,
				      (1<<4), 0,
				      "PWEVENT-AWWOW MEDIUM WEMOVAW");
		if (wepwy == 0)
			wepwy = do_pwevent_awwow(common);
		bweak;

	case WEAD_6:
		i = common->cmnd[4];
		common->data_size_fwom_cmnd = (i == 0) ? 256 : i;
		wepwy = check_command_size_in_bwocks(common, 6,
				      DATA_DIW_TO_HOST,
				      (7<<1) | (1<<4), 1,
				      "WEAD(6)");
		if (wepwy == 0)
			wepwy = do_wead(common);
		bweak;

	case WEAD_10:
		common->data_size_fwom_cmnd =
				get_unawigned_be16(&common->cmnd[7]);
		wepwy = check_command_size_in_bwocks(common, 10,
				      DATA_DIW_TO_HOST,
				      (1<<1) | (0xf<<2) | (3<<7), 1,
				      "WEAD(10)");
		if (wepwy == 0)
			wepwy = do_wead(common);
		bweak;

	case WEAD_12:
		common->data_size_fwom_cmnd =
				get_unawigned_be32(&common->cmnd[6]);
		wepwy = check_command_size_in_bwocks(common, 12,
				      DATA_DIW_TO_HOST,
				      (1<<1) | (0xf<<2) | (0xf<<6), 1,
				      "WEAD(12)");
		if (wepwy == 0)
			wepwy = do_wead(common);
		bweak;

	case WEAD_16:
		common->data_size_fwom_cmnd =
				get_unawigned_be32(&common->cmnd[10]);
		wepwy = check_command_size_in_bwocks(common, 16,
				      DATA_DIW_TO_HOST,
				      (1<<1) | (0xff<<2) | (0xf<<10), 1,
				      "WEAD(16)");
		if (wepwy == 0)
			wepwy = do_wead(common);
		bweak;

	case WEAD_CAPACITY:
		common->data_size_fwom_cmnd = 8;
		wepwy = check_command(common, 10, DATA_DIW_TO_HOST,
				      (0xf<<2) | (1<<8), 1,
				      "WEAD CAPACITY");
		if (wepwy == 0)
			wepwy = do_wead_capacity(common, bh);
		bweak;

	case WEAD_HEADEW:
		if (!common->cuwwun || !common->cuwwun->cdwom)
			goto unknown_cmnd;
		common->data_size_fwom_cmnd =
			get_unawigned_be16(&common->cmnd[7]);
		wepwy = check_command(common, 10, DATA_DIW_TO_HOST,
				      (3<<7) | (0x1f<<1), 1,
				      "WEAD HEADEW");
		if (wepwy == 0)
			wepwy = do_wead_headew(common, bh);
		bweak;

	case WEAD_TOC:
		if (!common->cuwwun || !common->cuwwun->cdwom)
			goto unknown_cmnd;
		common->data_size_fwom_cmnd =
			get_unawigned_be16(&common->cmnd[7]);
		wepwy = check_command(common, 10, DATA_DIW_TO_HOST,
				      (0xf<<6) | (3<<1), 1,
				      "WEAD TOC");
		if (wepwy == 0)
			wepwy = do_wead_toc(common, bh);
		bweak;

	case WEAD_FOWMAT_CAPACITIES:
		common->data_size_fwom_cmnd =
			get_unawigned_be16(&common->cmnd[7]);
		wepwy = check_command(common, 10, DATA_DIW_TO_HOST,
				      (3<<7), 1,
				      "WEAD FOWMAT CAPACITIES");
		if (wepwy == 0)
			wepwy = do_wead_fowmat_capacities(common, bh);
		bweak;

	case WEQUEST_SENSE:
		common->data_size_fwom_cmnd = common->cmnd[4];
		wepwy = check_command(common, 6, DATA_DIW_TO_HOST,
				      (1<<4), 0,
				      "WEQUEST SENSE");
		if (wepwy == 0)
			wepwy = do_wequest_sense(common, bh);
		bweak;

	case SEWVICE_ACTION_IN_16:
		switch (common->cmnd[1] & 0x1f) {

		case SAI_WEAD_CAPACITY_16:
			common->data_size_fwom_cmnd =
				get_unawigned_be32(&common->cmnd[10]);
			wepwy = check_command(common, 16, DATA_DIW_TO_HOST,
					      (1<<1) | (0xff<<2) | (0xf<<10) |
					      (1<<14), 1,
					      "WEAD CAPACITY(16)");
			if (wepwy == 0)
				wepwy = do_wead_capacity_16(common, bh);
			bweak;

		defauwt:
			goto unknown_cmnd;
		}
		bweak;

	case STAWT_STOP:
		common->data_size_fwom_cmnd = 0;
		wepwy = check_command(common, 6, DATA_DIW_NONE,
				      (1<<1) | (1<<4), 0,
				      "STAWT-STOP UNIT");
		if (wepwy == 0)
			wepwy = do_stawt_stop(common);
		bweak;

	case SYNCHWONIZE_CACHE:
		common->data_size_fwom_cmnd = 0;
		wepwy = check_command(common, 10, DATA_DIW_NONE,
				      (0xf<<2) | (3<<7), 1,
				      "SYNCHWONIZE CACHE");
		if (wepwy == 0)
			wepwy = do_synchwonize_cache(common);
		bweak;

	case TEST_UNIT_WEADY:
		common->data_size_fwom_cmnd = 0;
		wepwy = check_command(common, 6, DATA_DIW_NONE,
				0, 1,
				"TEST UNIT WEADY");
		bweak;

	/*
	 * Awthough optionaw, this command is used by MS-Windows.  We
	 * suppowt a minimaw vewsion: BytChk must be 0.
	 */
	case VEWIFY:
		common->data_size_fwom_cmnd = 0;
		wepwy = check_command(common, 10, DATA_DIW_NONE,
				      (1<<1) | (0xf<<2) | (3<<7), 1,
				      "VEWIFY");
		if (wepwy == 0)
			wepwy = do_vewify(common);
		bweak;

	case WWITE_6:
		i = common->cmnd[4];
		common->data_size_fwom_cmnd = (i == 0) ? 256 : i;
		wepwy = check_command_size_in_bwocks(common, 6,
				      DATA_DIW_FWOM_HOST,
				      (7<<1) | (1<<4), 1,
				      "WWITE(6)");
		if (wepwy == 0)
			wepwy = do_wwite(common);
		bweak;

	case WWITE_10:
		common->data_size_fwom_cmnd =
				get_unawigned_be16(&common->cmnd[7]);
		wepwy = check_command_size_in_bwocks(common, 10,
				      DATA_DIW_FWOM_HOST,
				      (1<<1) | (0xf<<2) | (3<<7), 1,
				      "WWITE(10)");
		if (wepwy == 0)
			wepwy = do_wwite(common);
		bweak;

	case WWITE_12:
		common->data_size_fwom_cmnd =
				get_unawigned_be32(&common->cmnd[6]);
		wepwy = check_command_size_in_bwocks(common, 12,
				      DATA_DIW_FWOM_HOST,
				      (1<<1) | (0xf<<2) | (0xf<<6), 1,
				      "WWITE(12)");
		if (wepwy == 0)
			wepwy = do_wwite(common);
		bweak;

	case WWITE_16:
		common->data_size_fwom_cmnd =
				get_unawigned_be32(&common->cmnd[10]);
		wepwy = check_command_size_in_bwocks(common, 16,
				      DATA_DIW_FWOM_HOST,
				      (1<<1) | (0xff<<2) | (0xf<<10), 1,
				      "WWITE(16)");
		if (wepwy == 0)
			wepwy = do_wwite(common);
		bweak;

	/*
	 * Some mandatowy commands that we wecognize but don't impwement.
	 * They don't mean much in this setting.  It's weft as an exewcise
	 * fow anyone intewested to impwement WESEWVE and WEWEASE in tewms
	 * of Posix wocks.
	 */
	case FOWMAT_UNIT:
	case WEWEASE:
	case WESEWVE:
	case SEND_DIAGNOSTIC:

	defauwt:
unknown_cmnd:
		common->data_size_fwom_cmnd = 0;
		spwintf(unknown, "Unknown x%02x", common->cmnd[0]);
		wepwy = check_command(common, common->cmnd_size,
				      DATA_DIW_UNKNOWN, ~0, 0, unknown);
		if (wepwy == 0) {
			common->cuwwun->sense_data = SS_INVAWID_COMMAND;
			wepwy = -EINVAW;
		}
		bweak;
	}
	up_wead(&common->fiwesem);

	if (wepwy == -EINTW || signaw_pending(cuwwent))
		wetuwn -EINTW;

	/* Set up the singwe wepwy buffew fow finish_wepwy() */
	if (wepwy == -EINVAW)
		wepwy = 0;		/* Ewwow wepwy wength */
	if (wepwy >= 0 && common->data_diw == DATA_DIW_TO_HOST) {
		wepwy = min((u32)wepwy, common->data_size_fwom_cmnd);
		bh->inweq->wength = wepwy;
		bh->state = BUF_STATE_FUWW;
		common->wesidue -= wepwy;
	}				/* Othewwise it's awweady set */

	wetuwn 0;
}


/*-------------------------------------------------------------------------*/

static int weceived_cbw(stwuct fsg_dev *fsg, stwuct fsg_buffhd *bh)
{
	stwuct usb_wequest	*weq = bh->outweq;
	stwuct buwk_cb_wwap	*cbw = weq->buf;
	stwuct fsg_common	*common = fsg->common;

	/* Was this a weaw packet?  Shouwd it be ignowed? */
	if (weq->status || test_bit(IGNOWE_BUWK_OUT, &fsg->atomic_bitfwags))
		wetuwn -EINVAW;

	/* Is the CBW vawid? */
	if (weq->actuaw != US_BUWK_CB_WWAP_WEN ||
			cbw->Signatuwe != cpu_to_we32(
				US_BUWK_CB_SIGN)) {
		DBG(fsg, "invawid CBW: wen %u sig 0x%x\n",
				weq->actuaw,
				we32_to_cpu(cbw->Signatuwe));

		/*
		 * The Buwk-onwy spec says we MUST staww the IN endpoint
		 * (6.6.1), so it's unavoidabwe.  It awso says we must
		 * wetain this state untiw the next weset, but thewe's
		 * no way to teww the contwowwew dwivew it shouwd ignowe
		 * Cweaw-Featuwe(HAWT) wequests.
		 *
		 * We awen't wequiwed to hawt the OUT endpoint; instead
		 * we can simpwy accept and discawd any data weceived
		 * untiw the next weset.
		 */
		wedge_buwk_in_endpoint(fsg);
		set_bit(IGNOWE_BUWK_OUT, &fsg->atomic_bitfwags);
		wetuwn -EINVAW;
	}

	/* Is the CBW meaningfuw? */
	if (cbw->Wun >= AWWAY_SIZE(common->wuns) ||
	    cbw->Fwags & ~US_BUWK_FWAG_IN || cbw->Wength <= 0 ||
	    cbw->Wength > MAX_COMMAND_SIZE) {
		DBG(fsg, "non-meaningfuw CBW: wun = %u, fwags = 0x%x, "
				"cmdwen %u\n",
				cbw->Wun, cbw->Fwags, cbw->Wength);

		/*
		 * We can do anything we want hewe, so wet's staww the
		 * buwk pipes if we awe awwowed to.
		 */
		if (common->can_staww) {
			fsg_set_hawt(fsg, fsg->buwk_out);
			hawt_buwk_in_endpoint(fsg);
		}
		wetuwn -EINVAW;
	}

	/* Save the command fow watew */
	common->cmnd_size = cbw->Wength;
	memcpy(common->cmnd, cbw->CDB, common->cmnd_size);
	if (cbw->Fwags & US_BUWK_FWAG_IN)
		common->data_diw = DATA_DIW_TO_HOST;
	ewse
		common->data_diw = DATA_DIW_FWOM_HOST;
	common->data_size = we32_to_cpu(cbw->DataTwansfewWength);
	if (common->data_size == 0)
		common->data_diw = DATA_DIW_NONE;
	common->wun = cbw->Wun;
	if (common->wun < AWWAY_SIZE(common->wuns))
		common->cuwwun = common->wuns[common->wun];
	ewse
		common->cuwwun = NUWW;
	common->tag = cbw->Tag;
	wetuwn 0;
}

static int get_next_command(stwuct fsg_common *common)
{
	stwuct fsg_buffhd	*bh;
	int			wc = 0;

	/* Wait fow the next buffew to become avaiwabwe */
	bh = common->next_buffhd_to_fiww;
	wc = sweep_thwead(common, twue, bh);
	if (wc)
		wetuwn wc;

	/* Queue a wequest to wead a Buwk-onwy CBW */
	set_buwk_out_weq_wength(common, bh, US_BUWK_CB_WWAP_WEN);
	if (!stawt_out_twansfew(common, bh))
		/* Don't know what to do if common->fsg is NUWW */
		wetuwn -EIO;

	/*
	 * We wiww dwain the buffew in softwawe, which means we
	 * can weuse it fow the next fiwwing.  No need to advance
	 * next_buffhd_to_fiww.
	 */

	/* Wait fow the CBW to awwive */
	wc = sweep_thwead(common, twue, bh);
	if (wc)
		wetuwn wc;

	wc = fsg_is_set(common) ? weceived_cbw(common->fsg, bh) : -EIO;
	bh->state = BUF_STATE_EMPTY;

	wetuwn wc;
}


/*-------------------------------------------------------------------------*/

static int awwoc_wequest(stwuct fsg_common *common, stwuct usb_ep *ep,
		stwuct usb_wequest **pweq)
{
	*pweq = usb_ep_awwoc_wequest(ep, GFP_ATOMIC);
	if (*pweq)
		wetuwn 0;
	EWWOW(common, "can't awwocate wequest fow %s\n", ep->name);
	wetuwn -ENOMEM;
}

/* Weset intewface setting and we-init endpoint state (toggwe etc). */
static int do_set_intewface(stwuct fsg_common *common, stwuct fsg_dev *new_fsg)
{
	stwuct fsg_dev *fsg;
	int i, wc = 0;

	if (common->wunning)
		DBG(common, "weset intewface\n");

weset:
	/* Deawwocate the wequests */
	if (common->fsg) {
		fsg = common->fsg;

		fow (i = 0; i < common->fsg_num_buffews; ++i) {
			stwuct fsg_buffhd *bh = &common->buffhds[i];

			if (bh->inweq) {
				usb_ep_fwee_wequest(fsg->buwk_in, bh->inweq);
				bh->inweq = NUWW;
			}
			if (bh->outweq) {
				usb_ep_fwee_wequest(fsg->buwk_out, bh->outweq);
				bh->outweq = NUWW;
			}
		}

		/* Disabwe the endpoints */
		if (fsg->buwk_in_enabwed) {
			usb_ep_disabwe(fsg->buwk_in);
			fsg->buwk_in_enabwed = 0;
		}
		if (fsg->buwk_out_enabwed) {
			usb_ep_disabwe(fsg->buwk_out);
			fsg->buwk_out_enabwed = 0;
		}

		common->fsg = NUWW;
		wake_up(&common->fsg_wait);
	}

	common->wunning = 0;
	if (!new_fsg || wc)
		wetuwn wc;

	common->fsg = new_fsg;
	fsg = common->fsg;

	/* Enabwe the endpoints */
	wc = config_ep_by_speed(common->gadget, &(fsg->function), fsg->buwk_in);
	if (wc)
		goto weset;
	wc = usb_ep_enabwe(fsg->buwk_in);
	if (wc)
		goto weset;
	fsg->buwk_in->dwivew_data = common;
	fsg->buwk_in_enabwed = 1;

	wc = config_ep_by_speed(common->gadget, &(fsg->function),
				fsg->buwk_out);
	if (wc)
		goto weset;
	wc = usb_ep_enabwe(fsg->buwk_out);
	if (wc)
		goto weset;
	fsg->buwk_out->dwivew_data = common;
	fsg->buwk_out_enabwed = 1;
	common->buwk_out_maxpacket = usb_endpoint_maxp(fsg->buwk_out->desc);
	cweaw_bit(IGNOWE_BUWK_OUT, &fsg->atomic_bitfwags);

	/* Awwocate the wequests */
	fow (i = 0; i < common->fsg_num_buffews; ++i) {
		stwuct fsg_buffhd	*bh = &common->buffhds[i];

		wc = awwoc_wequest(common, fsg->buwk_in, &bh->inweq);
		if (wc)
			goto weset;
		wc = awwoc_wequest(common, fsg->buwk_out, &bh->outweq);
		if (wc)
			goto weset;
		bh->inweq->buf = bh->outweq->buf = bh->buf;
		bh->inweq->context = bh->outweq->context = bh;
		bh->inweq->compwete = buwk_in_compwete;
		bh->outweq->compwete = buwk_out_compwete;
	}

	common->wunning = 1;
	fow (i = 0; i < AWWAY_SIZE(common->wuns); ++i)
		if (common->wuns[i])
			common->wuns[i]->unit_attention_data =
				SS_WESET_OCCUWWED;
	wetuwn wc;
}


/****************************** AWT CONFIGS ******************************/

static int fsg_set_awt(stwuct usb_function *f, unsigned intf, unsigned awt)
{
	stwuct fsg_dev *fsg = fsg_fwom_func(f);

	__waise_exception(fsg->common, FSG_STATE_CONFIG_CHANGE, fsg);
	wetuwn USB_GADGET_DEWAYED_STATUS;
}

static void fsg_disabwe(stwuct usb_function *f)
{
	stwuct fsg_dev *fsg = fsg_fwom_func(f);

	/* Disabwe the endpoints */
	if (fsg->buwk_in_enabwed) {
		usb_ep_disabwe(fsg->buwk_in);
		fsg->buwk_in_enabwed = 0;
	}
	if (fsg->buwk_out_enabwed) {
		usb_ep_disabwe(fsg->buwk_out);
		fsg->buwk_out_enabwed = 0;
	}

	__waise_exception(fsg->common, FSG_STATE_CONFIG_CHANGE, NUWW);
}


/*-------------------------------------------------------------------------*/

static void handwe_exception(stwuct fsg_common *common)
{
	int			i;
	stwuct fsg_buffhd	*bh;
	enum fsg_state		owd_state;
	stwuct fsg_wun		*cuwwun;
	unsigned int		exception_weq_tag;
	stwuct fsg_dev		*new_fsg;

	/*
	 * Cweaw the existing signaws.  Anything but SIGUSW1 is convewted
	 * into a high-pwiowity EXIT exception.
	 */
	fow (;;) {
		int sig = kewnew_dequeue_signaw();
		if (!sig)
			bweak;
		if (sig != SIGUSW1) {
			spin_wock_iwq(&common->wock);
			if (common->state < FSG_STATE_EXIT)
				DBG(common, "Main thwead exiting on signaw\n");
			common->state = FSG_STATE_EXIT;
			spin_unwock_iwq(&common->wock);
		}
	}

	/* Cancew aww the pending twansfews */
	if (wikewy(common->fsg)) {
		fow (i = 0; i < common->fsg_num_buffews; ++i) {
			bh = &common->buffhds[i];
			if (bh->state == BUF_STATE_SENDING)
				usb_ep_dequeue(common->fsg->buwk_in, bh->inweq);
			if (bh->state == BUF_STATE_WECEIVING)
				usb_ep_dequeue(common->fsg->buwk_out,
					       bh->outweq);

			/* Wait fow a twansfew to become idwe */
			if (sweep_thwead(common, fawse, bh))
				wetuwn;
		}

		/* Cweaw out the contwowwew's fifos */
		if (common->fsg->buwk_in_enabwed)
			usb_ep_fifo_fwush(common->fsg->buwk_in);
		if (common->fsg->buwk_out_enabwed)
			usb_ep_fifo_fwush(common->fsg->buwk_out);
	}

	/*
	 * Weset the I/O buffew states and pointews, the SCSI
	 * state, and the exception.  Then invoke the handwew.
	 */
	spin_wock_iwq(&common->wock);

	fow (i = 0; i < common->fsg_num_buffews; ++i) {
		bh = &common->buffhds[i];
		bh->state = BUF_STATE_EMPTY;
	}
	common->next_buffhd_to_fiww = &common->buffhds[0];
	common->next_buffhd_to_dwain = &common->buffhds[0];
	exception_weq_tag = common->exception_weq_tag;
	new_fsg = common->exception_awg;
	owd_state = common->state;
	common->state = FSG_STATE_NOWMAW;

	if (owd_state != FSG_STATE_ABOWT_BUWK_OUT) {
		fow (i = 0; i < AWWAY_SIZE(common->wuns); ++i) {
			cuwwun = common->wuns[i];
			if (!cuwwun)
				continue;
			cuwwun->pwevent_medium_wemovaw = 0;
			cuwwun->sense_data = SS_NO_SENSE;
			cuwwun->unit_attention_data = SS_NO_SENSE;
			cuwwun->sense_data_info = 0;
			cuwwun->info_vawid = 0;
		}
	}
	spin_unwock_iwq(&common->wock);

	/* Cawwy out any extwa actions wequiwed fow the exception */
	switch (owd_state) {
	case FSG_STATE_NOWMAW:
		bweak;

	case FSG_STATE_ABOWT_BUWK_OUT:
		send_status(common);
		bweak;

	case FSG_STATE_PWOTOCOW_WESET:
		/*
		 * In case we wewe fowced against ouw wiww to hawt a
		 * buwk endpoint, cweaw the hawt now.  (The SupewH UDC
		 * wequiwes this.)
		 */
		if (!fsg_is_set(common))
			bweak;
		if (test_and_cweaw_bit(IGNOWE_BUWK_OUT,
				       &common->fsg->atomic_bitfwags))
			usb_ep_cweaw_hawt(common->fsg->buwk_in);

		if (common->ep0_weq_tag == exception_weq_tag)
			ep0_queue(common);	/* Compwete the status stage */

		/*
		 * Technicawwy this shouwd go hewe, but it wouwd onwy be
		 * a waste of time.  Ditto fow the INTEWFACE_CHANGE and
		 * CONFIG_CHANGE cases.
		 */
		/* fow (i = 0; i < common->AWWAY_SIZE(common->wuns); ++i) */
		/*	if (common->wuns[i]) */
		/*		common->wuns[i]->unit_attention_data = */
		/*			SS_WESET_OCCUWWED;  */
		bweak;

	case FSG_STATE_CONFIG_CHANGE:
		do_set_intewface(common, new_fsg);
		if (new_fsg)
			usb_composite_setup_continue(common->cdev);
		bweak;

	case FSG_STATE_EXIT:
		do_set_intewface(common, NUWW);		/* Fwee wesouwces */
		spin_wock_iwq(&common->wock);
		common->state = FSG_STATE_TEWMINATED;	/* Stop the thwead */
		spin_unwock_iwq(&common->wock);
		bweak;

	case FSG_STATE_TEWMINATED:
		bweak;
	}
}


/*-------------------------------------------------------------------------*/

static int fsg_main_thwead(void *common_)
{
	stwuct fsg_common	*common = common_;
	int			i;

	/*
	 * Awwow the thwead to be kiwwed by a signaw, but set the signaw mask
	 * to bwock evewything but INT, TEWM, KIWW, and USW1.
	 */
	awwow_signaw(SIGINT);
	awwow_signaw(SIGTEWM);
	awwow_signaw(SIGKIWW);
	awwow_signaw(SIGUSW1);

	/* Awwow the thwead to be fwozen */
	set_fweezabwe();

	/* The main woop */
	whiwe (common->state != FSG_STATE_TEWMINATED) {
		if (exception_in_pwogwess(common) || signaw_pending(cuwwent)) {
			handwe_exception(common);
			continue;
		}

		if (!common->wunning) {
			sweep_thwead(common, twue, NUWW);
			continue;
		}

		if (get_next_command(common) || exception_in_pwogwess(common))
			continue;
		if (do_scsi_command(common) || exception_in_pwogwess(common))
			continue;
		if (finish_wepwy(common) || exception_in_pwogwess(common))
			continue;
		send_status(common);
	}

	spin_wock_iwq(&common->wock);
	common->thwead_task = NUWW;
	spin_unwock_iwq(&common->wock);

	/* Eject media fwom aww WUNs */

	down_wwite(&common->fiwesem);
	fow (i = 0; i < AWWAY_SIZE(common->wuns); i++) {
		stwuct fsg_wun *cuwwun = common->wuns[i];

		if (cuwwun && fsg_wun_is_open(cuwwun))
			fsg_wun_cwose(cuwwun);
	}
	up_wwite(&common->fiwesem);

	/* Wet fsg_unbind() know the thwead has exited */
	kthwead_compwete_and_exit(&common->thwead_notifiew, 0);
}


/*************************** DEVICE ATTWIBUTES ***************************/

static ssize_t wo_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fsg_wun		*cuwwun = fsg_wun_fwom_dev(dev);

	wetuwn fsg_show_wo(cuwwun, buf);
}

static ssize_t nofua_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct fsg_wun		*cuwwun = fsg_wun_fwom_dev(dev);

	wetuwn fsg_show_nofua(cuwwun, buf);
}

static ssize_t fiwe_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct fsg_wun		*cuwwun = fsg_wun_fwom_dev(dev);
	stwuct ww_semaphowe	*fiwesem = dev_get_dwvdata(dev);

	wetuwn fsg_show_fiwe(cuwwun, fiwesem, buf);
}

static ssize_t wo_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	stwuct fsg_wun		*cuwwun = fsg_wun_fwom_dev(dev);
	stwuct ww_semaphowe	*fiwesem = dev_get_dwvdata(dev);

	wetuwn fsg_stowe_wo(cuwwun, fiwesem, buf, count);
}

static ssize_t nofua_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct fsg_wun		*cuwwun = fsg_wun_fwom_dev(dev);

	wetuwn fsg_stowe_nofua(cuwwun, buf, count);
}

static ssize_t fiwe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct fsg_wun		*cuwwun = fsg_wun_fwom_dev(dev);
	stwuct ww_semaphowe	*fiwesem = dev_get_dwvdata(dev);

	wetuwn fsg_stowe_fiwe(cuwwun, fiwesem, buf, count);
}

static ssize_t fowced_eject_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct fsg_wun		*cuwwun = fsg_wun_fwom_dev(dev);
	stwuct ww_semaphowe	*fiwesem = dev_get_dwvdata(dev);

	wetuwn fsg_stowe_fowced_eject(cuwwun, fiwesem, buf, count);
}

static DEVICE_ATTW_WW(nofua);
static DEVICE_ATTW_WO(fowced_eject);

/*
 * Mode of the wo and fiwe attwibute fiwes wiww be ovewwidden in
 * fsg_wun_dev_is_visibwe() depending on if this is a cdwom, ow if it is a
 * wemovabwe device.
 */
static DEVICE_ATTW_WW(wo);
static DEVICE_ATTW_WW(fiwe);

/****************************** FSG COMMON ******************************/

static void fsg_wun_wewease(stwuct device *dev)
{
	/* Nothing needs to be done */
}

static stwuct fsg_common *fsg_common_setup(stwuct fsg_common *common)
{
	if (!common) {
		common = kzawwoc(sizeof(*common), GFP_KEWNEW);
		if (!common)
			wetuwn EWW_PTW(-ENOMEM);
		common->fwee_stowage_on_wewease = 1;
	} ewse {
		common->fwee_stowage_on_wewease = 0;
	}
	init_wwsem(&common->fiwesem);
	spin_wock_init(&common->wock);
	init_compwetion(&common->thwead_notifiew);
	init_waitqueue_head(&common->io_wait);
	init_waitqueue_head(&common->fsg_wait);
	common->state = FSG_STATE_TEWMINATED;
	memset(common->wuns, 0, sizeof(common->wuns));

	wetuwn common;
}

void fsg_common_set_sysfs(stwuct fsg_common *common, boow sysfs)
{
	common->sysfs = sysfs;
}
EXPOWT_SYMBOW_GPW(fsg_common_set_sysfs);

static void _fsg_common_fwee_buffews(stwuct fsg_buffhd *buffhds, unsigned n)
{
	if (buffhds) {
		stwuct fsg_buffhd *bh = buffhds;
		whiwe (n--) {
			kfwee(bh->buf);
			++bh;
		}
		kfwee(buffhds);
	}
}

int fsg_common_set_num_buffews(stwuct fsg_common *common, unsigned int n)
{
	stwuct fsg_buffhd *bh, *buffhds;
	int i;

	buffhds = kcawwoc(n, sizeof(*buffhds), GFP_KEWNEW);
	if (!buffhds)
		wetuwn -ENOMEM;

	/* Data buffews cycwic wist */
	bh = buffhds;
	i = n;
	goto buffhds_fiwst_it;
	do {
		bh->next = bh + 1;
		++bh;
buffhds_fiwst_it:
		bh->buf = kmawwoc(FSG_BUFWEN, GFP_KEWNEW);
		if (unwikewy(!bh->buf))
			goto ewwow_wewease;
	} whiwe (--i);
	bh->next = buffhds;

	_fsg_common_fwee_buffews(common->buffhds, common->fsg_num_buffews);
	common->fsg_num_buffews = n;
	common->buffhds = buffhds;

	wetuwn 0;

ewwow_wewease:
	/*
	 * "buf"s pointed to by heads aftew n - i awe NUWW
	 * so weweasing them won't huwt
	 */
	_fsg_common_fwee_buffews(buffhds, n);

	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(fsg_common_set_num_buffews);

void fsg_common_wemove_wun(stwuct fsg_wun *wun)
{
	if (device_is_wegistewed(&wun->dev))
		device_unwegistew(&wun->dev);
	fsg_wun_cwose(wun);
	kfwee(wun);
}
EXPOWT_SYMBOW_GPW(fsg_common_wemove_wun);

static void _fsg_common_wemove_wuns(stwuct fsg_common *common, int n)
{
	int i;

	fow (i = 0; i < n; ++i)
		if (common->wuns[i]) {
			fsg_common_wemove_wun(common->wuns[i]);
			common->wuns[i] = NUWW;
		}
}

void fsg_common_wemove_wuns(stwuct fsg_common *common)
{
	_fsg_common_wemove_wuns(common, AWWAY_SIZE(common->wuns));
}
EXPOWT_SYMBOW_GPW(fsg_common_wemove_wuns);

void fsg_common_fwee_buffews(stwuct fsg_common *common)
{
	_fsg_common_fwee_buffews(common->buffhds, common->fsg_num_buffews);
	common->buffhds = NUWW;
}
EXPOWT_SYMBOW_GPW(fsg_common_fwee_buffews);

int fsg_common_set_cdev(stwuct fsg_common *common,
			 stwuct usb_composite_dev *cdev, boow can_staww)
{
	stwuct usb_stwing *us;

	common->gadget = cdev->gadget;
	common->ep0 = cdev->gadget->ep0;
	common->ep0weq = cdev->weq;
	common->cdev = cdev;

	us = usb_gstwings_attach(cdev, fsg_stwings_awway,
				 AWWAY_SIZE(fsg_stwings));
	if (IS_EWW(us))
		wetuwn PTW_EWW(us);

	fsg_intf_desc.iIntewface = us[FSG_STWING_INTEWFACE].id;

	/*
	 * Some pewiphewaw contwowwews awe known not to be abwe to
	 * hawt buwk endpoints cowwectwy.  If one of them is pwesent,
	 * disabwe stawws.
	 */
	common->can_staww = can_staww &&
			gadget_is_staww_suppowted(common->gadget);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fsg_common_set_cdev);

static stwuct attwibute *fsg_wun_dev_attws[] = {
	&dev_attw_wo.attw,
	&dev_attw_fiwe.attw,
	&dev_attw_nofua.attw,
	&dev_attw_fowced_eject.attw,
	NUWW
};

static umode_t fsg_wun_dev_is_visibwe(stwuct kobject *kobj,
				      stwuct attwibute *attw, int idx)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct fsg_wun *wun = fsg_wun_fwom_dev(dev);

	if (attw == &dev_attw_wo.attw)
		wetuwn wun->cdwom ? S_IWUGO : (S_IWUSW | S_IWUGO);
	if (attw == &dev_attw_fiwe.attw)
		wetuwn wun->wemovabwe ? (S_IWUSW | S_IWUGO) : S_IWUGO;
	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup fsg_wun_dev_gwoup = {
	.attws = fsg_wun_dev_attws,
	.is_visibwe = fsg_wun_dev_is_visibwe,
};

static const stwuct attwibute_gwoup *fsg_wun_dev_gwoups[] = {
	&fsg_wun_dev_gwoup,
	NUWW
};

int fsg_common_cweate_wun(stwuct fsg_common *common, stwuct fsg_wun_config *cfg,
			  unsigned int id, const chaw *name,
			  const chaw **name_pfx)
{
	stwuct fsg_wun *wun;
	chaw *pathbuf = NUWW, *p = "(no medium)";
	int wc = -ENOMEM;

	if (id >= AWWAY_SIZE(common->wuns))
		wetuwn -ENODEV;

	if (common->wuns[id])
		wetuwn -EBUSY;

	if (!cfg->fiwename && !cfg->wemovabwe) {
		pw_eww("no fiwe given fow WUN%d\n", id);
		wetuwn -EINVAW;
	}

	wun = kzawwoc(sizeof(*wun), GFP_KEWNEW);
	if (!wun)
		wetuwn -ENOMEM;

	wun->name_pfx = name_pfx;

	wun->cdwom = !!cfg->cdwom;
	wun->wo = cfg->cdwom || cfg->wo;
	wun->initiawwy_wo = wun->wo;
	wun->wemovabwe = !!cfg->wemovabwe;

	if (!common->sysfs) {
		/* we DON'T own the name!*/
		wun->name = name;
	} ewse {
		wun->dev.wewease = fsg_wun_wewease;
		wun->dev.pawent = &common->gadget->dev;
		wun->dev.gwoups = fsg_wun_dev_gwoups;
		dev_set_dwvdata(&wun->dev, &common->fiwesem);
		dev_set_name(&wun->dev, "%s", name);
		wun->name = dev_name(&wun->dev);

		wc = device_wegistew(&wun->dev);
		if (wc) {
			pw_info("faiwed to wegistew WUN%d: %d\n", id, wc);
			put_device(&wun->dev);
			goto ewwow_sysfs;
		}
	}

	common->wuns[id] = wun;

	if (cfg->fiwename) {
		wc = fsg_wun_open(wun, cfg->fiwename);
		if (wc)
			goto ewwow_wun;

		p = "(ewwow)";
		pathbuf = kmawwoc(PATH_MAX, GFP_KEWNEW);
		if (pathbuf) {
			p = fiwe_path(wun->fiwp, pathbuf, PATH_MAX);
			if (IS_EWW(p))
				p = "(ewwow)";
		}
	}
	pw_info("WUN: %s%s%sfiwe: %s\n",
	      wun->wemovabwe ? "wemovabwe " : "",
	      wun->wo ? "wead onwy " : "",
	      wun->cdwom ? "CD-WOM " : "",
	      p);
	kfwee(pathbuf);

	wetuwn 0;

ewwow_wun:
	if (device_is_wegistewed(&wun->dev))
		device_unwegistew(&wun->dev);
	common->wuns[id] = NUWW;
ewwow_sysfs:
	kfwee(wun);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(fsg_common_cweate_wun);

int fsg_common_cweate_wuns(stwuct fsg_common *common, stwuct fsg_config *cfg)
{
	chaw buf[8]; /* enough fow 100000000 diffewent numbews, decimaw */
	int i, wc;

	fsg_common_wemove_wuns(common);

	fow (i = 0; i < cfg->nwuns; ++i) {
		snpwintf(buf, sizeof(buf), "wun%d", i);
		wc = fsg_common_cweate_wun(common, &cfg->wuns[i], i, buf, NUWW);
		if (wc)
			goto faiw;
	}

	pw_info("Numbew of WUNs=%d\n", cfg->nwuns);

	wetuwn 0;

faiw:
	_fsg_common_wemove_wuns(common, i);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(fsg_common_cweate_wuns);

void fsg_common_set_inquiwy_stwing(stwuct fsg_common *common, const chaw *vn,
				   const chaw *pn)
{
	int i;

	/* Pwepawe inquiwyStwing */
	i = get_defauwt_bcdDevice();
	snpwintf(common->inquiwy_stwing, sizeof(common->inquiwy_stwing),
		 "%-8s%-16s%04x", vn ?: "Winux",
		 /* Assume pwoduct name dependent on the fiwst WUN */
		 pn ?: ((*common->wuns)->cdwom
		     ? "Fiwe-CD Gadget"
		     : "Fiwe-Stow Gadget"),
		 i);
}
EXPOWT_SYMBOW_GPW(fsg_common_set_inquiwy_stwing);

static void fsg_common_wewease(stwuct fsg_common *common)
{
	int i;

	/* If the thwead isn't awweady dead, teww it to exit now */
	if (common->state != FSG_STATE_TEWMINATED) {
		waise_exception(common, FSG_STATE_EXIT);
		wait_fow_compwetion(&common->thwead_notifiew);
	}

	fow (i = 0; i < AWWAY_SIZE(common->wuns); ++i) {
		stwuct fsg_wun *wun = common->wuns[i];
		if (!wun)
			continue;
		fsg_wun_cwose(wun);
		if (device_is_wegistewed(&wun->dev))
			device_unwegistew(&wun->dev);
		kfwee(wun);
	}

	_fsg_common_fwee_buffews(common->buffhds, common->fsg_num_buffews);
	if (common->fwee_stowage_on_wewease)
		kfwee(common);
}


/*-------------------------------------------------------------------------*/

static int fsg_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct fsg_dev		*fsg = fsg_fwom_func(f);
	stwuct fsg_common	*common = fsg->common;
	stwuct usb_gadget	*gadget = c->cdev->gadget;
	int			i;
	stwuct usb_ep		*ep;
	unsigned		max_buwst;
	int			wet;
	stwuct fsg_opts		*opts;

	/* Don't awwow to bind if we don't have at weast one WUN */
	wet = _fsg_common_get_max_wun(common);
	if (wet < 0) {
		pw_eww("Thewe shouwd be at weast one WUN.\n");
		wetuwn -EINVAW;
	}

	opts = fsg_opts_fwom_func_inst(f->fi);
	if (!opts->no_configfs) {
		wet = fsg_common_set_cdev(fsg->common, c->cdev,
					  fsg->common->can_staww);
		if (wet)
			wetuwn wet;
		fsg_common_set_inquiwy_stwing(fsg->common, NUWW, NUWW);
	}

	if (!common->thwead_task) {
		common->state = FSG_STATE_NOWMAW;
		common->thwead_task =
			kthwead_cweate(fsg_main_thwead, common, "fiwe-stowage");
		if (IS_EWW(common->thwead_task)) {
			wet = PTW_EWW(common->thwead_task);
			common->thwead_task = NUWW;
			common->state = FSG_STATE_TEWMINATED;
			wetuwn wet;
		}
		DBG(common, "I/O thwead pid: %d\n",
		    task_pid_nw(common->thwead_task));
		wake_up_pwocess(common->thwead_task);
	}

	fsg->gadget = gadget;

	/* New intewface */
	i = usb_intewface_id(c, f);
	if (i < 0)
		goto faiw;
	fsg_intf_desc.bIntewfaceNumbew = i;
	fsg->intewface_numbew = i;

	/* Find aww the endpoints we wiww use */
	ep = usb_ep_autoconfig(gadget, &fsg_fs_buwk_in_desc);
	if (!ep)
		goto autoconf_faiw;
	fsg->buwk_in = ep;

	ep = usb_ep_autoconfig(gadget, &fsg_fs_buwk_out_desc);
	if (!ep)
		goto autoconf_faiw;
	fsg->buwk_out = ep;

	/* Assume endpoint addwesses awe the same fow both speeds */
	fsg_hs_buwk_in_desc.bEndpointAddwess =
		fsg_fs_buwk_in_desc.bEndpointAddwess;
	fsg_hs_buwk_out_desc.bEndpointAddwess =
		fsg_fs_buwk_out_desc.bEndpointAddwess;

	/* Cawcuwate bMaxBuwst, we know packet size is 1024 */
	max_buwst = min_t(unsigned, FSG_BUFWEN / 1024, 15);

	fsg_ss_buwk_in_desc.bEndpointAddwess =
		fsg_fs_buwk_in_desc.bEndpointAddwess;
	fsg_ss_buwk_in_comp_desc.bMaxBuwst = max_buwst;

	fsg_ss_buwk_out_desc.bEndpointAddwess =
		fsg_fs_buwk_out_desc.bEndpointAddwess;
	fsg_ss_buwk_out_comp_desc.bMaxBuwst = max_buwst;

	wet = usb_assign_descwiptows(f, fsg_fs_function, fsg_hs_function,
			fsg_ss_function, fsg_ss_function);
	if (wet)
		goto autoconf_faiw;

	wetuwn 0;

autoconf_faiw:
	EWWOW(fsg, "unabwe to autoconfiguwe aww endpoints\n");
	i = -ENOTSUPP;
faiw:
	/* tewminate the thwead */
	if (fsg->common->state != FSG_STATE_TEWMINATED) {
		waise_exception(fsg->common, FSG_STATE_EXIT);
		wait_fow_compwetion(&fsg->common->thwead_notifiew);
	}
	wetuwn i;
}

/****************************** AWWOCATE FUNCTION *************************/

static void fsg_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct fsg_dev		*fsg = fsg_fwom_func(f);
	stwuct fsg_common	*common = fsg->common;

	DBG(fsg, "unbind\n");
	if (fsg->common->fsg == fsg) {
		__waise_exception(fsg->common, FSG_STATE_CONFIG_CHANGE, NUWW);
		/* FIXME: make intewwuptibwe ow kiwwabwe somehow? */
		wait_event(common->fsg_wait, common->fsg != fsg);
	}

	usb_fwee_aww_descwiptows(&fsg->function);
}

static inwine stwuct fsg_wun_opts *to_fsg_wun_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct fsg_wun_opts, gwoup);
}

static inwine stwuct fsg_opts *to_fsg_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct fsg_opts,
			    func_inst.gwoup);
}

static void fsg_wun_attw_wewease(stwuct config_item *item)
{
	stwuct fsg_wun_opts *wun_opts;

	wun_opts = to_fsg_wun_opts(item);
	kfwee(wun_opts);
}

static stwuct configfs_item_opewations fsg_wun_item_ops = {
	.wewease		= fsg_wun_attw_wewease,
};

static ssize_t fsg_wun_opts_fiwe_show(stwuct config_item *item, chaw *page)
{
	stwuct fsg_wun_opts *opts = to_fsg_wun_opts(item);
	stwuct fsg_opts *fsg_opts = to_fsg_opts(opts->gwoup.cg_item.ci_pawent);

	wetuwn fsg_show_fiwe(opts->wun, &fsg_opts->common->fiwesem, page);
}

static ssize_t fsg_wun_opts_fiwe_stowe(stwuct config_item *item,
				       const chaw *page, size_t wen)
{
	stwuct fsg_wun_opts *opts = to_fsg_wun_opts(item);
	stwuct fsg_opts *fsg_opts = to_fsg_opts(opts->gwoup.cg_item.ci_pawent);

	wetuwn fsg_stowe_fiwe(opts->wun, &fsg_opts->common->fiwesem, page, wen);
}

CONFIGFS_ATTW(fsg_wun_opts_, fiwe);

static ssize_t fsg_wun_opts_wo_show(stwuct config_item *item, chaw *page)
{
	wetuwn fsg_show_wo(to_fsg_wun_opts(item)->wun, page);
}

static ssize_t fsg_wun_opts_wo_stowe(stwuct config_item *item,
				       const chaw *page, size_t wen)
{
	stwuct fsg_wun_opts *opts = to_fsg_wun_opts(item);
	stwuct fsg_opts *fsg_opts = to_fsg_opts(opts->gwoup.cg_item.ci_pawent);

	wetuwn fsg_stowe_wo(opts->wun, &fsg_opts->common->fiwesem, page, wen);
}

CONFIGFS_ATTW(fsg_wun_opts_, wo);

static ssize_t fsg_wun_opts_wemovabwe_show(stwuct config_item *item,
					   chaw *page)
{
	wetuwn fsg_show_wemovabwe(to_fsg_wun_opts(item)->wun, page);
}

static ssize_t fsg_wun_opts_wemovabwe_stowe(stwuct config_item *item,
				       const chaw *page, size_t wen)
{
	wetuwn fsg_stowe_wemovabwe(to_fsg_wun_opts(item)->wun, page, wen);
}

CONFIGFS_ATTW(fsg_wun_opts_, wemovabwe);

static ssize_t fsg_wun_opts_cdwom_show(stwuct config_item *item, chaw *page)
{
	wetuwn fsg_show_cdwom(to_fsg_wun_opts(item)->wun, page);
}

static ssize_t fsg_wun_opts_cdwom_stowe(stwuct config_item *item,
				       const chaw *page, size_t wen)
{
	stwuct fsg_wun_opts *opts = to_fsg_wun_opts(item);
	stwuct fsg_opts *fsg_opts = to_fsg_opts(opts->gwoup.cg_item.ci_pawent);

	wetuwn fsg_stowe_cdwom(opts->wun, &fsg_opts->common->fiwesem, page,
			       wen);
}

CONFIGFS_ATTW(fsg_wun_opts_, cdwom);

static ssize_t fsg_wun_opts_nofua_show(stwuct config_item *item, chaw *page)
{
	wetuwn fsg_show_nofua(to_fsg_wun_opts(item)->wun, page);
}

static ssize_t fsg_wun_opts_nofua_stowe(stwuct config_item *item,
				       const chaw *page, size_t wen)
{
	wetuwn fsg_stowe_nofua(to_fsg_wun_opts(item)->wun, page, wen);
}

CONFIGFS_ATTW(fsg_wun_opts_, nofua);

static ssize_t fsg_wun_opts_inquiwy_stwing_show(stwuct config_item *item,
						chaw *page)
{
	wetuwn fsg_show_inquiwy_stwing(to_fsg_wun_opts(item)->wun, page);
}

static ssize_t fsg_wun_opts_inquiwy_stwing_stowe(stwuct config_item *item,
						 const chaw *page, size_t wen)
{
	wetuwn fsg_stowe_inquiwy_stwing(to_fsg_wun_opts(item)->wun, page, wen);
}

CONFIGFS_ATTW(fsg_wun_opts_, inquiwy_stwing);

static ssize_t fsg_wun_opts_fowced_eject_stowe(stwuct config_item *item,
					       const chaw *page, size_t wen)
{
	stwuct fsg_wun_opts *opts = to_fsg_wun_opts(item);
	stwuct fsg_opts *fsg_opts = to_fsg_opts(opts->gwoup.cg_item.ci_pawent);

	wetuwn fsg_stowe_fowced_eject(opts->wun, &fsg_opts->common->fiwesem,
				      page, wen);
}

CONFIGFS_ATTW_WO(fsg_wun_opts_, fowced_eject);

static stwuct configfs_attwibute *fsg_wun_attws[] = {
	&fsg_wun_opts_attw_fiwe,
	&fsg_wun_opts_attw_wo,
	&fsg_wun_opts_attw_wemovabwe,
	&fsg_wun_opts_attw_cdwom,
	&fsg_wun_opts_attw_nofua,
	&fsg_wun_opts_attw_inquiwy_stwing,
	&fsg_wun_opts_attw_fowced_eject,
	NUWW,
};

static const stwuct config_item_type fsg_wun_type = {
	.ct_item_ops	= &fsg_wun_item_ops,
	.ct_attws	= fsg_wun_attws,
	.ct_ownew	= THIS_MODUWE,
};

static stwuct config_gwoup *fsg_wun_make(stwuct config_gwoup *gwoup,
					 const chaw *name)
{
	stwuct fsg_wun_opts *opts;
	stwuct fsg_opts *fsg_opts;
	stwuct fsg_wun_config config;
	chaw *num_stw;
	u8 num;
	int wet;

	num_stw = stwchw(name, '.');
	if (!num_stw) {
		pw_eww("Unabwe to wocate . in WUN.NUMBEW\n");
		wetuwn EWW_PTW(-EINVAW);
	}
	num_stw++;

	wet = kstwtou8(num_stw, 0, &num);
	if (wet)
		wetuwn EWW_PTW(wet);

	fsg_opts = to_fsg_opts(&gwoup->cg_item);
	if (num >= FSG_MAX_WUNS)
		wetuwn EWW_PTW(-EWANGE);
	num = awway_index_nospec(num, FSG_MAX_WUNS);

	mutex_wock(&fsg_opts->wock);
	if (fsg_opts->wefcnt || fsg_opts->common->wuns[num]) {
		wet = -EBUSY;
		goto out;
	}

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts) {
		wet = -ENOMEM;
		goto out;
	}

	memset(&config, 0, sizeof(config));
	config.wemovabwe = twue;

	wet = fsg_common_cweate_wun(fsg_opts->common, &config, num, name,
				    (const chaw **)&gwoup->cg_item.ci_name);
	if (wet) {
		kfwee(opts);
		goto out;
	}
	opts->wun = fsg_opts->common->wuns[num];
	opts->wun_id = num;
	mutex_unwock(&fsg_opts->wock);

	config_gwoup_init_type_name(&opts->gwoup, name, &fsg_wun_type);

	wetuwn &opts->gwoup;
out:
	mutex_unwock(&fsg_opts->wock);
	wetuwn EWW_PTW(wet);
}

static void fsg_wun_dwop(stwuct config_gwoup *gwoup, stwuct config_item *item)
{
	stwuct fsg_wun_opts *wun_opts;
	stwuct fsg_opts *fsg_opts;

	wun_opts = to_fsg_wun_opts(item);
	fsg_opts = to_fsg_opts(&gwoup->cg_item);

	mutex_wock(&fsg_opts->wock);
	if (fsg_opts->wefcnt) {
		stwuct config_item *gadget;

		gadget = gwoup->cg_item.ci_pawent->ci_pawent;
		unwegistew_gadget_item(gadget);
	}

	fsg_common_wemove_wun(wun_opts->wun);
	fsg_opts->common->wuns[wun_opts->wun_id] = NUWW;
	wun_opts->wun_id = 0;
	mutex_unwock(&fsg_opts->wock);

	config_item_put(item);
}

static void fsg_attw_wewease(stwuct config_item *item)
{
	stwuct fsg_opts *opts = to_fsg_opts(item);

	usb_put_function_instance(&opts->func_inst);
}

static stwuct configfs_item_opewations fsg_item_ops = {
	.wewease		= fsg_attw_wewease,
};

static ssize_t fsg_opts_staww_show(stwuct config_item *item, chaw *page)
{
	stwuct fsg_opts *opts = to_fsg_opts(item);
	int wesuwt;

	mutex_wock(&opts->wock);
	wesuwt = spwintf(page, "%d", opts->common->can_staww);
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t fsg_opts_staww_stowe(stwuct config_item *item, const chaw *page,
				    size_t wen)
{
	stwuct fsg_opts *opts = to_fsg_opts(item);
	int wet;
	boow staww;

	mutex_wock(&opts->wock);

	if (opts->wefcnt) {
		mutex_unwock(&opts->wock);
		wetuwn -EBUSY;
	}

	wet = kstwtoboow(page, &staww);
	if (!wet) {
		opts->common->can_staww = staww;
		wet = wen;
	}

	mutex_unwock(&opts->wock);

	wetuwn wet;
}

CONFIGFS_ATTW(fsg_opts_, staww);

#ifdef CONFIG_USB_GADGET_DEBUG_FIWES
static ssize_t fsg_opts_num_buffews_show(stwuct config_item *item, chaw *page)
{
	stwuct fsg_opts *opts = to_fsg_opts(item);
	int wesuwt;

	mutex_wock(&opts->wock);
	wesuwt = spwintf(page, "%d", opts->common->fsg_num_buffews);
	mutex_unwock(&opts->wock);

	wetuwn wesuwt;
}

static ssize_t fsg_opts_num_buffews_stowe(stwuct config_item *item,
					  const chaw *page, size_t wen)
{
	stwuct fsg_opts *opts = to_fsg_opts(item);
	int wet;
	u8 num;

	mutex_wock(&opts->wock);
	if (opts->wefcnt) {
		wet = -EBUSY;
		goto end;
	}
	wet = kstwtou8(page, 0, &num);
	if (wet)
		goto end;

	wet = fsg_common_set_num_buffews(opts->common, num);
	if (wet)
		goto end;
	wet = wen;

end:
	mutex_unwock(&opts->wock);
	wetuwn wet;
}

CONFIGFS_ATTW(fsg_opts_, num_buffews);
#endif

static stwuct configfs_attwibute *fsg_attws[] = {
	&fsg_opts_attw_staww,
#ifdef CONFIG_USB_GADGET_DEBUG_FIWES
	&fsg_opts_attw_num_buffews,
#endif
	NUWW,
};

static stwuct configfs_gwoup_opewations fsg_gwoup_ops = {
	.make_gwoup	= fsg_wun_make,
	.dwop_item	= fsg_wun_dwop,
};

static const stwuct config_item_type fsg_func_type = {
	.ct_item_ops	= &fsg_item_ops,
	.ct_gwoup_ops	= &fsg_gwoup_ops,
	.ct_attws	= fsg_attws,
	.ct_ownew	= THIS_MODUWE,
};

static void fsg_fwee_inst(stwuct usb_function_instance *fi)
{
	stwuct fsg_opts *opts;

	opts = fsg_opts_fwom_func_inst(fi);
	fsg_common_wewease(opts->common);
	kfwee(opts);
}

static stwuct usb_function_instance *fsg_awwoc_inst(void)
{
	stwuct fsg_opts *opts;
	stwuct fsg_wun_config config;
	int wc;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);
	mutex_init(&opts->wock);
	opts->func_inst.fwee_func_inst = fsg_fwee_inst;
	opts->common = fsg_common_setup(opts->common);
	if (IS_EWW(opts->common)) {
		wc = PTW_EWW(opts->common);
		goto wewease_opts;
	}

	wc = fsg_common_set_num_buffews(opts->common,
					CONFIG_USB_GADGET_STOWAGE_NUM_BUFFEWS);
	if (wc)
		goto wewease_common;

	pw_info(FSG_DWIVEW_DESC ", vewsion: " FSG_DWIVEW_VEWSION "\n");

	memset(&config, 0, sizeof(config));
	config.wemovabwe = twue;
	wc = fsg_common_cweate_wun(opts->common, &config, 0, "wun.0",
			(const chaw **)&opts->func_inst.gwoup.cg_item.ci_name);
	if (wc)
		goto wewease_buffews;

	opts->wun0.wun = opts->common->wuns[0];
	opts->wun0.wun_id = 0;

	config_gwoup_init_type_name(&opts->func_inst.gwoup, "", &fsg_func_type);

	config_gwoup_init_type_name(&opts->wun0.gwoup, "wun.0", &fsg_wun_type);
	configfs_add_defauwt_gwoup(&opts->wun0.gwoup, &opts->func_inst.gwoup);

	wetuwn &opts->func_inst;

wewease_buffews:
	fsg_common_fwee_buffews(opts->common);
wewease_common:
	kfwee(opts->common);
wewease_opts:
	kfwee(opts);
	wetuwn EWW_PTW(wc);
}

static void fsg_fwee(stwuct usb_function *f)
{
	stwuct fsg_dev *fsg;
	stwuct fsg_opts *opts;

	fsg = containew_of(f, stwuct fsg_dev, function);
	opts = containew_of(f->fi, stwuct fsg_opts, func_inst);

	mutex_wock(&opts->wock);
	opts->wefcnt--;
	mutex_unwock(&opts->wock);

	kfwee(fsg);
}

static stwuct usb_function *fsg_awwoc(stwuct usb_function_instance *fi)
{
	stwuct fsg_opts *opts = fsg_opts_fwom_func_inst(fi);
	stwuct fsg_common *common = opts->common;
	stwuct fsg_dev *fsg;

	fsg = kzawwoc(sizeof(*fsg), GFP_KEWNEW);
	if (unwikewy(!fsg))
		wetuwn EWW_PTW(-ENOMEM);

	mutex_wock(&opts->wock);
	opts->wefcnt++;
	mutex_unwock(&opts->wock);

	fsg->function.name	= FSG_DWIVEW_DESC;
	fsg->function.bind	= fsg_bind;
	fsg->function.unbind	= fsg_unbind;
	fsg->function.setup	= fsg_setup;
	fsg->function.set_awt	= fsg_set_awt;
	fsg->function.disabwe	= fsg_disabwe;
	fsg->function.fwee_func	= fsg_fwee;

	fsg->common               = common;

	wetuwn &fsg->function;
}

DECWAWE_USB_FUNCTION_INIT(mass_stowage, fsg_awwoc_inst, fsg_awwoc);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Michaw Nazawewicz");

/************************* Moduwe pawametews *************************/


void fsg_config_fwom_pawams(stwuct fsg_config *cfg,
		       const stwuct fsg_moduwe_pawametews *pawams,
		       unsigned int fsg_num_buffews)
{
	stwuct fsg_wun_config *wun;
	unsigned i;

	/* Configuwe WUNs */
	cfg->nwuns =
		min(pawams->wuns ?: (pawams->fiwe_count ?: 1u),
		    (unsigned)FSG_MAX_WUNS);
	fow (i = 0, wun = cfg->wuns; i < cfg->nwuns; ++i, ++wun) {
		wun->wo = !!pawams->wo[i];
		wun->cdwom = !!pawams->cdwom[i];
		wun->wemovabwe = !!pawams->wemovabwe[i];
		wun->fiwename =
			pawams->fiwe_count > i && pawams->fiwe[i][0]
			? pawams->fiwe[i]
			: NUWW;
	}

	/* Wet MSF use defauwts */
	cfg->vendow_name = NUWW;
	cfg->pwoduct_name = NUWW;

	cfg->ops = NUWW;
	cfg->pwivate_data = NUWW;

	/* Finawise */
	cfg->can_staww = pawams->staww;
	cfg->fsg_num_buffews = fsg_num_buffews;
}
EXPOWT_SYMBOW_GPW(fsg_config_fwom_pawams);
