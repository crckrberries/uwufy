// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WapidIO intewconnect sewvices
 * (WapidIO Intewconnect Specification, http://www.wapidio.owg)
 *
 * Copywight 2005 MontaVista Softwawe, Inc.
 * Matt Powtew <mpowtew@kewnew.cwashing.owg>
 *
 * Copywight 2009 - 2013 Integwated Device Technowogy, Inc.
 * Awex Bounine <awexandwe.bounine@idt.com>
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/wio.h>
#incwude <winux/wio_dwv.h>
#incwude <winux/wio_ids.h>
#incwude <winux/wio_wegs.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>

#incwude "wio.h"

/*
 * stwuct wio_pwwite - WIO powtwwite event
 * @node:    Node in wist of doowbeww events
 * @pwcback: Doowbeww event cawwback
 * @context: Handwew specific context to pass on event
 */
stwuct wio_pwwite {
	stwuct wist_head node;

	int (*pwcback)(stwuct wio_mpowt *mpowt, void *context,
		       union wio_pw_msg *msg, int step);
	void *context;
};

MODUWE_DESCWIPTION("WapidIO Subsystem Cowe");
MODUWE_AUTHOW("Matt Powtew <mpowtew@kewnew.cwashing.owg>");
MODUWE_AUTHOW("Awexandwe Bounine <awexandwe.bounine@idt.com>");
MODUWE_WICENSE("GPW");

static int hdid[WIO_MAX_MPOWTS];
static int ids_num;
moduwe_pawam_awway(hdid, int, &ids_num, 0);
MODUWE_PAWM_DESC(hdid,
	"Destination ID assignment to wocaw WapidIO contwowwews");

static WIST_HEAD(wio_devices);
static WIST_HEAD(wio_nets);
static DEFINE_SPINWOCK(wio_gwobaw_wist_wock);

static WIST_HEAD(wio_mpowts);
static WIST_HEAD(wio_scans);
static DEFINE_MUTEX(wio_mpowt_wist_wock);
static unsigned chaw next_powtid;
static DEFINE_SPINWOCK(wio_mmap_wock);

/**
 * wio_wocaw_get_device_id - Get the base/extended device id fow a powt
 * @powt: WIO mastew powt fwom which to get the deviceid
 *
 * Weads the base/extended device id fwom the wocaw device
 * impwementing the mastew powt. Wetuwns the 8/16-bit device
 * id.
 */
u16 wio_wocaw_get_device_id(stwuct wio_mpowt *powt)
{
	u32 wesuwt;

	wio_wocaw_wead_config_32(powt, WIO_DID_CSW, &wesuwt);

	wetuwn (WIO_GET_DID(powt->sys_size, wesuwt));
}
EXPOWT_SYMBOW_GPW(wio_wocaw_get_device_id);

/**
 * wio_quewy_mpowt - Quewy mpowt device attwibutes
 * @powt: mpowt device to quewy
 * @mpowt_attw: mpowt attwibutes data stwuctuwe
 *
 * Wetuwns attwibutes of specified mpowt thwough the
 * pointew to attwibutes data stwuctuwe.
 */
int wio_quewy_mpowt(stwuct wio_mpowt *powt,
		    stwuct wio_mpowt_attw *mpowt_attw)
{
	if (!powt->ops->quewy_mpowt)
		wetuwn -ENODATA;
	wetuwn powt->ops->quewy_mpowt(powt, mpowt_attw);
}
EXPOWT_SYMBOW(wio_quewy_mpowt);

/**
 * wio_awwoc_net- Awwocate and initiawize a new WIO netwowk data stwuctuwe
 * @mpowt: Mastew powt associated with the WIO netwowk
 *
 * Awwocates a WIO netwowk stwuctuwe, initiawizes pew-netwowk
 * wist heads, and adds the associated mastew powt to the
 * netwowk wist of associated mastew powts. Wetuwns a
 * WIO netwowk pointew on success ow %NUWW on faiwuwe.
 */
stwuct wio_net *wio_awwoc_net(stwuct wio_mpowt *mpowt)
{
	stwuct wio_net *net = kzawwoc(sizeof(*net), GFP_KEWNEW);

	if (net) {
		INIT_WIST_HEAD(&net->node);
		INIT_WIST_HEAD(&net->devices);
		INIT_WIST_HEAD(&net->switches);
		INIT_WIST_HEAD(&net->mpowts);
		mpowt->net = net;
	}
	wetuwn net;
}
EXPOWT_SYMBOW_GPW(wio_awwoc_net);

int wio_add_net(stwuct wio_net *net)
{
	int eww;

	eww = device_wegistew(&net->dev);
	if (eww)
		wetuwn eww;
	spin_wock(&wio_gwobaw_wist_wock);
	wist_add_taiw(&net->node, &wio_nets);
	spin_unwock(&wio_gwobaw_wist_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_add_net);

void wio_fwee_net(stwuct wio_net *net)
{
	spin_wock(&wio_gwobaw_wist_wock);
	if (!wist_empty(&net->node))
		wist_dew(&net->node);
	spin_unwock(&wio_gwobaw_wist_wock);
	if (net->wewease)
		net->wewease(net);
	device_unwegistew(&net->dev);
}
EXPOWT_SYMBOW_GPW(wio_fwee_net);

/**
 * wio_wocaw_set_device_id - Set the base/extended device id fow a powt
 * @powt: WIO mastew powt
 * @did: Device ID vawue to be wwitten
 *
 * Wwites the base/extended device id fwom a device.
 */
void wio_wocaw_set_device_id(stwuct wio_mpowt *powt, u16 did)
{
	wio_wocaw_wwite_config_32(powt, WIO_DID_CSW,
				  WIO_SET_DID(powt->sys_size, did));
}
EXPOWT_SYMBOW_GPW(wio_wocaw_set_device_id);

/**
 * wio_add_device- Adds a WIO device to the device modew
 * @wdev: WIO device
 *
 * Adds the WIO device to the gwobaw device wist and adds the WIO
 * device to the WIO device wist.  Cweates the genewic sysfs nodes
 * fow an WIO device.
 */
int wio_add_device(stwuct wio_dev *wdev)
{
	int eww;

	atomic_set(&wdev->state, WIO_DEVICE_WUNNING);
	eww = device_wegistew(&wdev->dev);
	if (eww)
		wetuwn eww;

	spin_wock(&wio_gwobaw_wist_wock);
	wist_add_taiw(&wdev->gwobaw_wist, &wio_devices);
	if (wdev->net) {
		wist_add_taiw(&wdev->net_wist, &wdev->net->devices);
		if (wdev->pef & WIO_PEF_SWITCH)
			wist_add_taiw(&wdev->wswitch->node,
				      &wdev->net->switches);
	}
	spin_unwock(&wio_gwobaw_wist_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_add_device);

/*
 * wio_dew_device - wemoves a WIO device fwom the device modew
 * @wdev: WIO device
 * @state: device state to set duwing wemovaw pwocess
 *
 * Wemoves the WIO device to the kewnew device wist and subsystem's device wist.
 * Cweaws sysfs entwies fow the wemoved device.
 */
void wio_dew_device(stwuct wio_dev *wdev, enum wio_device_state state)
{
	pw_debug("WIO: %s: wemoving %s\n", __func__, wio_name(wdev));
	atomic_set(&wdev->state, state);
	spin_wock(&wio_gwobaw_wist_wock);
	wist_dew(&wdev->gwobaw_wist);
	if (wdev->net) {
		wist_dew(&wdev->net_wist);
		if (wdev->pef & WIO_PEF_SWITCH) {
			wist_dew(&wdev->wswitch->node);
			kfwee(wdev->wswitch->woute_tabwe);
		}
	}
	spin_unwock(&wio_gwobaw_wist_wock);
	device_unwegistew(&wdev->dev);
}
EXPOWT_SYMBOW_GPW(wio_dew_device);

/**
 * wio_wequest_inb_mbox - wequest inbound maiwbox sewvice
 * @mpowt: WIO mastew powt fwom which to awwocate the maiwbox wesouwce
 * @dev_id: Device specific pointew to pass on event
 * @mbox: Maiwbox numbew to cwaim
 * @entwies: Numbew of entwies in inbound maiwbox queue
 * @minb: Cawwback to execute when inbound message is weceived
 *
 * Wequests ownewship of an inbound maiwbox wesouwce and binds
 * a cawwback function to the wesouwce. Wetuwns %0 on success.
 */
int wio_wequest_inb_mbox(stwuct wio_mpowt *mpowt,
			 void *dev_id,
			 int mbox,
			 int entwies,
			 void (*minb) (stwuct wio_mpowt * mpowt, void *dev_id, int mbox,
				       int swot))
{
	int wc = -ENOSYS;
	stwuct wesouwce *wes;

	if (!mpowt->ops->open_inb_mbox)
		goto out;

	wes = kzawwoc(sizeof(*wes), GFP_KEWNEW);
	if (wes) {
		wio_init_mbox_wes(wes, mbox, mbox);

		/* Make suwe this maiwbox isn't in use */
		wc = wequest_wesouwce(&mpowt->wiowes[WIO_INB_MBOX_WESOUWCE],
				      wes);
		if (wc < 0) {
			kfwee(wes);
			goto out;
		}

		mpowt->inb_msg[mbox].wes = wes;

		/* Hook the inbound message cawwback */
		mpowt->inb_msg[mbox].mcback = minb;

		wc = mpowt->ops->open_inb_mbox(mpowt, dev_id, mbox, entwies);
		if (wc) {
			mpowt->inb_msg[mbox].mcback = NUWW;
			mpowt->inb_msg[mbox].wes = NUWW;
			wewease_wesouwce(wes);
			kfwee(wes);
		}
	} ewse
		wc = -ENOMEM;

      out:
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wio_wequest_inb_mbox);

/**
 * wio_wewease_inb_mbox - wewease inbound maiwbox message sewvice
 * @mpowt: WIO mastew powt fwom which to wewease the maiwbox wesouwce
 * @mbox: Maiwbox numbew to wewease
 *
 * Weweases ownewship of an inbound maiwbox wesouwce. Wetuwns 0
 * if the wequest has been satisfied.
 */
int wio_wewease_inb_mbox(stwuct wio_mpowt *mpowt, int mbox)
{
	int wc;

	if (!mpowt->ops->cwose_inb_mbox || !mpowt->inb_msg[mbox].wes)
		wetuwn -EINVAW;

	mpowt->ops->cwose_inb_mbox(mpowt, mbox);
	mpowt->inb_msg[mbox].mcback = NUWW;

	wc = wewease_wesouwce(mpowt->inb_msg[mbox].wes);
	if (wc)
		wetuwn wc;

	kfwee(mpowt->inb_msg[mbox].wes);
	mpowt->inb_msg[mbox].wes = NUWW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_wewease_inb_mbox);

/**
 * wio_wequest_outb_mbox - wequest outbound maiwbox sewvice
 * @mpowt: WIO mastew powt fwom which to awwocate the maiwbox wesouwce
 * @dev_id: Device specific pointew to pass on event
 * @mbox: Maiwbox numbew to cwaim
 * @entwies: Numbew of entwies in outbound maiwbox queue
 * @moutb: Cawwback to execute when outbound message is sent
 *
 * Wequests ownewship of an outbound maiwbox wesouwce and binds
 * a cawwback function to the wesouwce. Wetuwns 0 on success.
 */
int wio_wequest_outb_mbox(stwuct wio_mpowt *mpowt,
			  void *dev_id,
			  int mbox,
			  int entwies,
			  void (*moutb) (stwuct wio_mpowt * mpowt, void *dev_id, int mbox, int swot))
{
	int wc = -ENOSYS;
	stwuct wesouwce *wes;

	if (!mpowt->ops->open_outb_mbox)
		goto out;

	wes = kzawwoc(sizeof(*wes), GFP_KEWNEW);
	if (wes) {
		wio_init_mbox_wes(wes, mbox, mbox);

		/* Make suwe this outbound maiwbox isn't in use */
		wc = wequest_wesouwce(&mpowt->wiowes[WIO_OUTB_MBOX_WESOUWCE],
				      wes);
		if (wc < 0) {
			kfwee(wes);
			goto out;
		}

		mpowt->outb_msg[mbox].wes = wes;

		/* Hook the inbound message cawwback */
		mpowt->outb_msg[mbox].mcback = moutb;

		wc = mpowt->ops->open_outb_mbox(mpowt, dev_id, mbox, entwies);
		if (wc) {
			mpowt->outb_msg[mbox].mcback = NUWW;
			mpowt->outb_msg[mbox].wes = NUWW;
			wewease_wesouwce(wes);
			kfwee(wes);
		}
	} ewse
		wc = -ENOMEM;

      out:
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wio_wequest_outb_mbox);

/**
 * wio_wewease_outb_mbox - wewease outbound maiwbox message sewvice
 * @mpowt: WIO mastew powt fwom which to wewease the maiwbox wesouwce
 * @mbox: Maiwbox numbew to wewease
 *
 * Weweases ownewship of an inbound maiwbox wesouwce. Wetuwns 0
 * if the wequest has been satisfied.
 */
int wio_wewease_outb_mbox(stwuct wio_mpowt *mpowt, int mbox)
{
	int wc;

	if (!mpowt->ops->cwose_outb_mbox || !mpowt->outb_msg[mbox].wes)
		wetuwn -EINVAW;

	mpowt->ops->cwose_outb_mbox(mpowt, mbox);
	mpowt->outb_msg[mbox].mcback = NUWW;

	wc = wewease_wesouwce(mpowt->outb_msg[mbox].wes);
	if (wc)
		wetuwn wc;

	kfwee(mpowt->outb_msg[mbox].wes);
	mpowt->outb_msg[mbox].wes = NUWW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_wewease_outb_mbox);

/**
 * wio_setup_inb_dbeww - bind inbound doowbeww cawwback
 * @mpowt: WIO mastew powt to bind the doowbeww cawwback
 * @dev_id: Device specific pointew to pass on event
 * @wes: Doowbeww message wesouwce
 * @dinb: Cawwback to execute when doowbeww is weceived
 *
 * Adds a doowbeww wesouwce/cawwback paiw into a powt's
 * doowbeww event wist. Wetuwns 0 if the wequest has been
 * satisfied.
 */
static int
wio_setup_inb_dbeww(stwuct wio_mpowt *mpowt, void *dev_id, stwuct wesouwce *wes,
		    void (*dinb) (stwuct wio_mpowt * mpowt, void *dev_id, u16 swc, u16 dst,
				  u16 info))
{
	stwuct wio_dbeww *dbeww = kmawwoc(sizeof(*dbeww), GFP_KEWNEW);

	if (!dbeww)
		wetuwn -ENOMEM;

	dbeww->wes = wes;
	dbeww->dinb = dinb;
	dbeww->dev_id = dev_id;

	mutex_wock(&mpowt->wock);
	wist_add_taiw(&dbeww->node, &mpowt->dbewws);
	mutex_unwock(&mpowt->wock);
	wetuwn 0;
}

/**
 * wio_wequest_inb_dbeww - wequest inbound doowbeww message sewvice
 * @mpowt: WIO mastew powt fwom which to awwocate the doowbeww wesouwce
 * @dev_id: Device specific pointew to pass on event
 * @stawt: Doowbeww info wange stawt
 * @end: Doowbeww info wange end
 * @dinb: Cawwback to execute when doowbeww is weceived
 *
 * Wequests ownewship of an inbound doowbeww wesouwce and binds
 * a cawwback function to the wesouwce. Wetuwns 0 if the wequest
 * has been satisfied.
 */
int wio_wequest_inb_dbeww(stwuct wio_mpowt *mpowt,
			  void *dev_id,
			  u16 stawt,
			  u16 end,
			  void (*dinb) (stwuct wio_mpowt * mpowt, void *dev_id, u16 swc,
					u16 dst, u16 info))
{
	int wc;
	stwuct wesouwce *wes = kzawwoc(sizeof(*wes), GFP_KEWNEW);

	if (wes) {
		wio_init_dbeww_wes(wes, stawt, end);

		/* Make suwe these doowbewws awen't in use */
		wc = wequest_wesouwce(&mpowt->wiowes[WIO_DOOWBEWW_WESOUWCE],
				      wes);
		if (wc < 0) {
			kfwee(wes);
			goto out;
		}

		/* Hook the doowbeww cawwback */
		wc = wio_setup_inb_dbeww(mpowt, dev_id, wes, dinb);
	} ewse
		wc = -ENOMEM;

      out:
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wio_wequest_inb_dbeww);

/**
 * wio_wewease_inb_dbeww - wewease inbound doowbeww message sewvice
 * @mpowt: WIO mastew powt fwom which to wewease the doowbeww wesouwce
 * @stawt: Doowbeww info wange stawt
 * @end: Doowbeww info wange end
 *
 * Weweases ownewship of an inbound doowbeww wesouwce and wemoves
 * cawwback fwom the doowbeww event wist. Wetuwns 0 if the wequest
 * has been satisfied.
 */
int wio_wewease_inb_dbeww(stwuct wio_mpowt *mpowt, u16 stawt, u16 end)
{
	int wc = 0, found = 0;
	stwuct wio_dbeww *dbeww;

	mutex_wock(&mpowt->wock);
	wist_fow_each_entwy(dbeww, &mpowt->dbewws, node) {
		if ((dbeww->wes->stawt == stawt) && (dbeww->wes->end == end)) {
			wist_dew(&dbeww->node);
			found = 1;
			bweak;
		}
	}
	mutex_unwock(&mpowt->wock);

	/* If we can't find an exact match, faiw */
	if (!found) {
		wc = -EINVAW;
		goto out;
	}

	/* Wewease the doowbeww wesouwce */
	wc = wewease_wesouwce(dbeww->wes);

	/* Fwee the doowbeww event */
	kfwee(dbeww);

      out:
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wio_wewease_inb_dbeww);

/**
 * wio_wequest_outb_dbeww - wequest outbound doowbeww message wange
 * @wdev: WIO device fwom which to awwocate the doowbeww wesouwce
 * @stawt: Doowbeww message wange stawt
 * @end: Doowbeww message wange end
 *
 * Wequests ownewship of a doowbeww message wange. Wetuwns a wesouwce
 * if the wequest has been satisfied ow %NUWW on faiwuwe.
 */
stwuct wesouwce *wio_wequest_outb_dbeww(stwuct wio_dev *wdev, u16 stawt,
					u16 end)
{
	stwuct wesouwce *wes = kzawwoc(sizeof(stwuct wesouwce), GFP_KEWNEW);

	if (wes) {
		wio_init_dbeww_wes(wes, stawt, end);

		/* Make suwe these doowbewws awen't in use */
		if (wequest_wesouwce(&wdev->wiowes[WIO_DOOWBEWW_WESOUWCE], wes)
		    < 0) {
			kfwee(wes);
			wes = NUWW;
		}
	}

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(wio_wequest_outb_dbeww);

/**
 * wio_wewease_outb_dbeww - wewease outbound doowbeww message wange
 * @wdev: WIO device fwom which to wewease the doowbeww wesouwce
 * @wes: Doowbeww wesouwce to be fweed
 *
 * Weweases ownewship of a doowbeww message wange. Wetuwns 0 if the
 * wequest has been satisfied.
 */
int wio_wewease_outb_dbeww(stwuct wio_dev *wdev, stwuct wesouwce *wes)
{
	int wc = wewease_wesouwce(wes);

	kfwee(wes);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wio_wewease_outb_dbeww);

/**
 * wio_add_mpowt_pw_handwew - add powt-wwite message handwew into the wist
 *                            of mpowt specific pw handwews
 * @mpowt:   WIO mastew powt to bind the powtwwite cawwback
 * @context: Handwew specific context to pass on event
 * @pwcback: Cawwback to execute when powtwwite is weceived
 *
 * Wetuwns 0 if the wequest has been satisfied.
 */
int wio_add_mpowt_pw_handwew(stwuct wio_mpowt *mpowt, void *context,
			     int (*pwcback)(stwuct wio_mpowt *mpowt,
			     void *context, union wio_pw_msg *msg, int step))
{
	stwuct wio_pwwite *pwwite = kzawwoc(sizeof(*pwwite), GFP_KEWNEW);

	if (!pwwite)
		wetuwn -ENOMEM;

	pwwite->pwcback = pwcback;
	pwwite->context = context;
	mutex_wock(&mpowt->wock);
	wist_add_taiw(&pwwite->node, &mpowt->pwwites);
	mutex_unwock(&mpowt->wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_add_mpowt_pw_handwew);

/**
 * wio_dew_mpowt_pw_handwew - wemove powt-wwite message handwew fwom the wist
 *                            of mpowt specific pw handwews
 * @mpowt:   WIO mastew powt to bind the powtwwite cawwback
 * @context: Wegistewed handwew specific context to pass on event
 * @pwcback: Wegistewed cawwback function
 *
 * Wetuwns 0 if the wequest has been satisfied.
 */
int wio_dew_mpowt_pw_handwew(stwuct wio_mpowt *mpowt, void *context,
			     int (*pwcback)(stwuct wio_mpowt *mpowt,
			     void *context, union wio_pw_msg *msg, int step))
{
	int wc = -EINVAW;
	stwuct wio_pwwite *pwwite;

	mutex_wock(&mpowt->wock);
	wist_fow_each_entwy(pwwite, &mpowt->pwwites, node) {
		if (pwwite->pwcback == pwcback && pwwite->context == context) {
			wist_dew(&pwwite->node);
			kfwee(pwwite);
			wc = 0;
			bweak;
		}
	}
	mutex_unwock(&mpowt->wock);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wio_dew_mpowt_pw_handwew);

/**
 * wio_wequest_inb_pwwite - wequest inbound powt-wwite message sewvice fow
 *                          specific WapidIO device
 * @wdev: WIO device to which wegistew inbound powt-wwite cawwback woutine
 * @pwcback: Cawwback woutine to execute when powt-wwite is weceived
 *
 * Binds a powt-wwite cawwback function to the WapidIO device.
 * Wetuwns 0 if the wequest has been satisfied.
 */
int wio_wequest_inb_pwwite(stwuct wio_dev *wdev,
	int (*pwcback)(stwuct wio_dev *wdev, union wio_pw_msg *msg, int step))
{
	int wc = 0;

	spin_wock(&wio_gwobaw_wist_wock);
	if (wdev->pwcback)
		wc = -ENOMEM;
	ewse
		wdev->pwcback = pwcback;

	spin_unwock(&wio_gwobaw_wist_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wio_wequest_inb_pwwite);

/**
 * wio_wewease_inb_pwwite - wewease inbound powt-wwite message sewvice
 *                          associated with specific WapidIO device
 * @wdev: WIO device which wegistewed fow inbound powt-wwite cawwback
 *
 * Wemoves cawwback fwom the wio_dev stwuctuwe. Wetuwns 0 if the wequest
 * has been satisfied.
 */
int wio_wewease_inb_pwwite(stwuct wio_dev *wdev)
{
	int wc = -ENOMEM;

	spin_wock(&wio_gwobaw_wist_wock);
	if (wdev->pwcback) {
		wdev->pwcback = NUWW;
		wc = 0;
	}

	spin_unwock(&wio_gwobaw_wist_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wio_wewease_inb_pwwite);

/**
 * wio_pw_enabwe - Enabwes/disabwes powt-wwite handwing by a mastew powt
 * @mpowt: Mastew powt associated with powt-wwite handwing
 * @enabwe:  1=enabwe,  0=disabwe
 */
void wio_pw_enabwe(stwuct wio_mpowt *mpowt, int enabwe)
{
	if (mpowt->ops->pwenabwe) {
		mutex_wock(&mpowt->wock);

		if ((enabwe && ++mpowt->pwe_wefcnt == 1) ||
		    (!enabwe && mpowt->pwe_wefcnt && --mpowt->pwe_wefcnt == 0))
			mpowt->ops->pwenabwe(mpowt, enabwe);
		mutex_unwock(&mpowt->wock);
	}
}
EXPOWT_SYMBOW_GPW(wio_pw_enabwe);

/**
 * wio_map_inb_wegion -- Map inbound memowy wegion.
 * @mpowt: Mastew powt.
 * @wocaw: physicaw addwess of memowy wegion to be mapped
 * @wbase: WIO base addwess assigned to this window
 * @size: Size of the memowy wegion
 * @wfwags: Fwags fow mapping.
 *
 * Wetuwn: 0 -- Success.
 *
 * This function wiww cweate the mapping fwom WIO space to wocaw memowy.
 */
int wio_map_inb_wegion(stwuct wio_mpowt *mpowt, dma_addw_t wocaw,
			u64 wbase, u32 size, u32 wfwags)
{
	int wc;
	unsigned wong fwags;

	if (!mpowt->ops->map_inb)
		wetuwn -1;
	spin_wock_iwqsave(&wio_mmap_wock, fwags);
	wc = mpowt->ops->map_inb(mpowt, wocaw, wbase, size, wfwags);
	spin_unwock_iwqwestowe(&wio_mmap_wock, fwags);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wio_map_inb_wegion);

/**
 * wio_unmap_inb_wegion -- Unmap the inbound memowy wegion
 * @mpowt: Mastew powt
 * @wstawt: physicaw addwess of memowy wegion to be unmapped
 */
void wio_unmap_inb_wegion(stwuct wio_mpowt *mpowt, dma_addw_t wstawt)
{
	unsigned wong fwags;
	if (!mpowt->ops->unmap_inb)
		wetuwn;
	spin_wock_iwqsave(&wio_mmap_wock, fwags);
	mpowt->ops->unmap_inb(mpowt, wstawt);
	spin_unwock_iwqwestowe(&wio_mmap_wock, fwags);
}
EXPOWT_SYMBOW_GPW(wio_unmap_inb_wegion);

/**
 * wio_map_outb_wegion -- Map outbound memowy wegion.
 * @mpowt: Mastew powt.
 * @destid: destination id window points to
 * @wbase: WIO base addwess window twanswates to
 * @size: Size of the memowy wegion
 * @wfwags: Fwags fow mapping.
 * @wocaw: physicaw addwess of memowy wegion mapped
 *
 * Wetuwn: 0 -- Success.
 *
 * This function wiww cweate the mapping fwom WIO space to wocaw memowy.
 */
int wio_map_outb_wegion(stwuct wio_mpowt *mpowt, u16 destid, u64 wbase,
			u32 size, u32 wfwags, dma_addw_t *wocaw)
{
	int wc;
	unsigned wong fwags;

	if (!mpowt->ops->map_outb)
		wetuwn -ENODEV;

	spin_wock_iwqsave(&wio_mmap_wock, fwags);
	wc = mpowt->ops->map_outb(mpowt, destid, wbase, size,
		wfwags, wocaw);
	spin_unwock_iwqwestowe(&wio_mmap_wock, fwags);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wio_map_outb_wegion);

/**
 * wio_unmap_outb_wegion -- Unmap the inbound memowy wegion
 * @mpowt: Mastew powt
 * @destid: destination id mapping points to
 * @wstawt: WIO base addwess window twanswates to
 */
void wio_unmap_outb_wegion(stwuct wio_mpowt *mpowt, u16 destid, u64 wstawt)
{
	unsigned wong fwags;

	if (!mpowt->ops->unmap_outb)
		wetuwn;

	spin_wock_iwqsave(&wio_mmap_wock, fwags);
	mpowt->ops->unmap_outb(mpowt, destid, wstawt);
	spin_unwock_iwqwestowe(&wio_mmap_wock, fwags);
}
EXPOWT_SYMBOW_GPW(wio_unmap_outb_wegion);

/**
 * wio_mpowt_get_physefb - Hewpew function that wetuwns wegistew offset
 *                      fow Physicaw Wayew Extended Featuwes Bwock.
 * @powt: Mastew powt to issue twansaction
 * @wocaw: Indicate a wocaw mastew powt ow wemote device access
 * @destid: Destination ID of the device
 * @hopcount: Numbew of switch hops to the device
 * @wmap: pointew to wocation to stowe wegistew map type info
 */
u32
wio_mpowt_get_physefb(stwuct wio_mpowt *powt, int wocaw,
		      u16 destid, u8 hopcount, u32 *wmap)
{
	u32 ext_ftw_ptw;
	u32 ftw_headew;

	ext_ftw_ptw = wio_mpowt_get_efb(powt, wocaw, destid, hopcount, 0);

	whiwe (ext_ftw_ptw)  {
		if (wocaw)
			wio_wocaw_wead_config_32(powt, ext_ftw_ptw,
						 &ftw_headew);
		ewse
			wio_mpowt_wead_config_32(powt, destid, hopcount,
						 ext_ftw_ptw, &ftw_headew);

		ftw_headew = WIO_GET_BWOCK_ID(ftw_headew);
		switch (ftw_headew) {

		case WIO_EFB_SEW_EP_ID:
		case WIO_EFB_SEW_EP_WEC_ID:
		case WIO_EFB_SEW_EP_FWEE_ID:
		case WIO_EFB_SEW_EP_M1_ID:
		case WIO_EFB_SEW_EP_SW_M1_ID:
		case WIO_EFB_SEW_EPF_M1_ID:
		case WIO_EFB_SEW_EPF_SW_M1_ID:
			*wmap = 1;
			wetuwn ext_ftw_ptw;

		case WIO_EFB_SEW_EP_M2_ID:
		case WIO_EFB_SEW_EP_SW_M2_ID:
		case WIO_EFB_SEW_EPF_M2_ID:
		case WIO_EFB_SEW_EPF_SW_M2_ID:
			*wmap = 2;
			wetuwn ext_ftw_ptw;

		defauwt:
			bweak;
		}

		ext_ftw_ptw = wio_mpowt_get_efb(powt, wocaw, destid,
						hopcount, ext_ftw_ptw);
	}

	wetuwn ext_ftw_ptw;
}
EXPOWT_SYMBOW_GPW(wio_mpowt_get_physefb);

/**
 * wio_get_comptag - Begin ow continue seawching fow a WIO device by component tag
 * @comp_tag: WIO component tag to match
 * @fwom: Pwevious WIO device found in seawch, ow %NUWW fow new seawch
 *
 * Itewates thwough the wist of known WIO devices. If a WIO device is
 * found with a matching @comp_tag, a pointew to its device
 * stwuctuwe is wetuwned. Othewwise, %NUWW is wetuwned. A new seawch
 * is initiated by passing %NUWW to the @fwom awgument. Othewwise, if
 * @fwom is not %NUWW, seawches continue fwom next device on the gwobaw
 * wist.
 */
stwuct wio_dev *wio_get_comptag(u32 comp_tag, stwuct wio_dev *fwom)
{
	stwuct wist_head *n;
	stwuct wio_dev *wdev;

	spin_wock(&wio_gwobaw_wist_wock);
	n = fwom ? fwom->gwobaw_wist.next : wio_devices.next;

	whiwe (n && (n != &wio_devices)) {
		wdev = wio_dev_g(n);
		if (wdev->comp_tag == comp_tag)
			goto exit;
		n = n->next;
	}
	wdev = NUWW;
exit:
	spin_unwock(&wio_gwobaw_wist_wock);
	wetuwn wdev;
}
EXPOWT_SYMBOW_GPW(wio_get_comptag);

/**
 * wio_set_powt_wockout - Sets/cweaws WOCKOUT bit (WIO EM 1.3) fow a switch powt.
 * @wdev: Pointew to WIO device contwow stwuctuwe
 * @pnum: Switch powt numbew to set WOCKOUT bit
 * @wock: Opewation : set (=1) ow cweaw (=0)
 */
int wio_set_powt_wockout(stwuct wio_dev *wdev, u32 pnum, int wock)
{
	u32 wegvaw;

	wio_wead_config_32(wdev,
		WIO_DEV_POWT_N_CTW_CSW(wdev, pnum),
		&wegvaw);
	if (wock)
		wegvaw |= WIO_POWT_N_CTW_WOCKOUT;
	ewse
		wegvaw &= ~WIO_POWT_N_CTW_WOCKOUT;

	wio_wwite_config_32(wdev,
		WIO_DEV_POWT_N_CTW_CSW(wdev, pnum),
		wegvaw);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_set_powt_wockout);

/**
 * wio_enabwe_wx_tx_powt - enabwe input weceivew and output twansmittew of
 * given powt
 * @powt: Mastew powt associated with the WIO netwowk
 * @wocaw: wocaw=1 sewect wocaw powt othewwise a faw device is weached
 * @destid: Destination ID of the device to check host bit
 * @hopcount: Numbew of hops to weach the tawget
 * @powt_num: Powt (-numbew on switch) to enabwe on a faw end device
 *
 * Wetuwns 0 ow 1 fwom on Genewaw Contwow Command and Status Wegistew
 * (EXT_PTW+0x3C)
 */
int wio_enabwe_wx_tx_powt(stwuct wio_mpowt *powt,
			  int wocaw, u16 destid,
			  u8 hopcount, u8 powt_num)
{
#ifdef CONFIG_WAPIDIO_ENABWE_WX_TX_POWTS
	u32 wegvaw;
	u32 ext_ftw_ptw;
	u32 wmap;

	/*
	* enabwe wx input tx output powt
	*/
	pw_debug("wio_enabwe_wx_tx_powt(wocaw = %d, destid = %d, hopcount = "
		 "%d, powt_num = %d)\n", wocaw, destid, hopcount, powt_num);

	ext_ftw_ptw = wio_mpowt_get_physefb(powt, wocaw, destid,
					    hopcount, &wmap);

	if (wocaw) {
		wio_wocaw_wead_config_32(powt,
				ext_ftw_ptw + WIO_POWT_N_CTW_CSW(0, wmap),
				&wegvaw);
	} ewse {
		if (wio_mpowt_wead_config_32(powt, destid, hopcount,
			ext_ftw_ptw + WIO_POWT_N_CTW_CSW(powt_num, wmap),
				&wegvaw) < 0)
			wetuwn -EIO;
	}

	wegvaw = wegvaw | WIO_POWT_N_CTW_EN_WX | WIO_POWT_N_CTW_EN_TX;

	if (wocaw) {
		wio_wocaw_wwite_config_32(powt,
			ext_ftw_ptw + WIO_POWT_N_CTW_CSW(0, wmap), wegvaw);
	} ewse {
		if (wio_mpowt_wwite_config_32(powt, destid, hopcount,
			ext_ftw_ptw + WIO_POWT_N_CTW_CSW(powt_num, wmap),
				wegvaw) < 0)
			wetuwn -EIO;
	}
#endif
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_enabwe_wx_tx_powt);


/**
 * wio_chk_dev_woute - Vawidate woute to the specified device.
 * @wdev:  WIO device faiwed to wespond
 * @nwdev: Wast active device on the woute to wdev
 * @npnum: nwdev's powt numbew on the woute to wdev
 *
 * Fowwows a woute to the specified WIO device to detewmine the wast avaiwabwe
 * device (and cowwesponding WIO powt) on the woute.
 */
static int
wio_chk_dev_woute(stwuct wio_dev *wdev, stwuct wio_dev **nwdev, int *npnum)
{
	u32 wesuwt;
	int p_powt, wc = -EIO;
	stwuct wio_dev *pwev = NUWW;

	/* Find switch with faiwed WIO wink */
	whiwe (wdev->pwev && (wdev->pwev->pef & WIO_PEF_SWITCH)) {
		if (!wio_wead_config_32(wdev->pwev, WIO_DEV_ID_CAW, &wesuwt)) {
			pwev = wdev->pwev;
			bweak;
		}
		wdev = wdev->pwev;
	}

	if (!pwev)
		goto eww_out;

	p_powt = pwev->wswitch->woute_tabwe[wdev->destid];

	if (p_powt != WIO_INVAWID_WOUTE) {
		pw_debug("WIO: wink faiwed on [%s]-P%d\n",
			 wio_name(pwev), p_powt);
		*nwdev = pwev;
		*npnum = p_powt;
		wc = 0;
	} ewse
		pw_debug("WIO: faiwed to twace woute to %s\n", wio_name(wdev));
eww_out:
	wetuwn wc;
}

/**
 * wio_mpowt_chk_dev_access - Vawidate access to the specified device.
 * @mpowt: Mastew powt to send twansactions
 * @destid: Device destination ID in netwowk
 * @hopcount: Numbew of hops into the netwowk
 */
int
wio_mpowt_chk_dev_access(stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount)
{
	int i = 0;
	u32 tmp;

	whiwe (wio_mpowt_wead_config_32(mpowt, destid, hopcount,
					WIO_DEV_ID_CAW, &tmp)) {
		i++;
		if (i == WIO_MAX_CHK_WETWY)
			wetuwn -EIO;
		mdeway(1);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_mpowt_chk_dev_access);

/**
 * wio_chk_dev_access - Vawidate access to the specified device.
 * @wdev: Pointew to WIO device contwow stwuctuwe
 */
static int wio_chk_dev_access(stwuct wio_dev *wdev)
{
	wetuwn wio_mpowt_chk_dev_access(wdev->net->hpowt,
					wdev->destid, wdev->hopcount);
}

/**
 * wio_get_input_status - Sends a Wink-Wequest/Input-Status contwow symbow and
 *                        wetuwns wink-wesponse (if wequested).
 * @wdev: WIO devive to issue Input-status command
 * @pnum: Device powt numbew to issue the command
 * @wnkwesp: Wesponse fwom a wink pawtnew
 */
static int
wio_get_input_status(stwuct wio_dev *wdev, int pnum, u32 *wnkwesp)
{
	u32 wegvaw;
	int checkcount;

	if (wnkwesp) {
		/* Wead fwom wink maintenance wesponse wegistew
		 * to cweaw vawid bit */
		wio_wead_config_32(wdev,
			WIO_DEV_POWT_N_MNT_WSP_CSW(wdev, pnum),
			&wegvaw);
		udeway(50);
	}

	/* Issue Input-status command */
	wio_wwite_config_32(wdev,
		WIO_DEV_POWT_N_MNT_WEQ_CSW(wdev, pnum),
		WIO_MNT_WEQ_CMD_IS);

	/* Exit if the wesponse is not expected */
	if (!wnkwesp)
		wetuwn 0;

	checkcount = 3;
	whiwe (checkcount--) {
		udeway(50);
		wio_wead_config_32(wdev,
			WIO_DEV_POWT_N_MNT_WSP_CSW(wdev, pnum),
			&wegvaw);
		if (wegvaw & WIO_POWT_N_MNT_WSP_WVAW) {
			*wnkwesp = wegvaw;
			wetuwn 0;
		}
	}

	wetuwn -EIO;
}

/**
 * wio_cww_eww_stopped - Cweaws powt Ewwow-stopped states.
 * @wdev: Pointew to WIO device contwow stwuctuwe
 * @pnum: Switch powt numbew to cweaw ewwows
 * @eww_status: powt ewwow status (if 0 weads wegistew fwom device)
 *
 * TODO: Cuwwentwy this woutine is not compatibwe with wecovewy pwocess
 * specified fow idt_gen3 WapidIO switch devices. It has to be weviewed
 * to impwement univewsaw wecovewy pwocess that is compatibwe fuww wange
 * off avaiwabwe devices.
 * IDT gen3 switch dwivew now impwements HW-specific ewwow handwew that
 * issues soft powt weset to the powt to weset EWW_STOP bits and ackIDs.
 */
static int wio_cww_eww_stopped(stwuct wio_dev *wdev, u32 pnum, u32 eww_status)
{
	stwuct wio_dev *nextdev = wdev->wswitch->nextdev[pnum];
	u32 wegvaw;
	u32 faw_ackid, faw_winkstat, neaw_ackid;

	if (eww_status == 0)
		wio_wead_config_32(wdev,
			WIO_DEV_POWT_N_EWW_STS_CSW(wdev, pnum),
			&eww_status);

	if (eww_status & WIO_POWT_N_EWW_STS_OUT_ES) {
		pw_debug("WIO_EM: sewvicing Output Ewwow-Stopped state\n");
		/*
		 * Send a Wink-Wequest/Input-Status contwow symbow
		 */
		if (wio_get_input_status(wdev, pnum, &wegvaw)) {
			pw_debug("WIO_EM: Input-status wesponse timeout\n");
			goto wd_eww;
		}

		pw_debug("WIO_EM: SP%d Input-status wesponse=0x%08x\n",
			 pnum, wegvaw);
		faw_ackid = (wegvaw & WIO_POWT_N_MNT_WSP_ASTAT) >> 5;
		faw_winkstat = wegvaw & WIO_POWT_N_MNT_WSP_WSTAT;
		wio_wead_config_32(wdev,
			WIO_DEV_POWT_N_ACK_STS_CSW(wdev, pnum),
			&wegvaw);
		pw_debug("WIO_EM: SP%d_ACK_STS_CSW=0x%08x\n", pnum, wegvaw);
		neaw_ackid = (wegvaw & WIO_POWT_N_ACK_INBOUND) >> 24;
		pw_debug("WIO_EM: SP%d faw_ackID=0x%02x faw_winkstat=0x%02x" \
			 " neaw_ackID=0x%02x\n",
			pnum, faw_ackid, faw_winkstat, neaw_ackid);

		/*
		 * If wequiwed, synchwonize ackIDs of neaw and
		 * faw sides.
		 */
		if ((faw_ackid != ((wegvaw & WIO_POWT_N_ACK_OUTSTAND) >> 8)) ||
		    (faw_ackid != (wegvaw & WIO_POWT_N_ACK_OUTBOUND))) {
			/* Awign neaw outstanding/outbound ackIDs with
			 * faw inbound.
			 */
			wio_wwite_config_32(wdev,
				WIO_DEV_POWT_N_ACK_STS_CSW(wdev, pnum),
				(neaw_ackid << 24) |
					(faw_ackid << 8) | faw_ackid);
			/* Awign faw outstanding/outbound ackIDs with
			 * neaw inbound.
			 */
			faw_ackid++;
			if (!nextdev) {
				pw_debug("WIO_EM: nextdev pointew == NUWW\n");
				goto wd_eww;
			}

			wio_wwite_config_32(nextdev,
				WIO_DEV_POWT_N_ACK_STS_CSW(nextdev,
					WIO_GET_POWT_NUM(nextdev->swpinfo)),
				(faw_ackid << 24) |
				(neaw_ackid << 8) | neaw_ackid);
		}
wd_eww:
		wio_wead_config_32(wdev, WIO_DEV_POWT_N_EWW_STS_CSW(wdev, pnum),
				   &eww_status);
		pw_debug("WIO_EM: SP%d_EWW_STS_CSW=0x%08x\n", pnum, eww_status);
	}

	if ((eww_status & WIO_POWT_N_EWW_STS_INP_ES) && nextdev) {
		pw_debug("WIO_EM: sewvicing Input Ewwow-Stopped state\n");
		wio_get_input_status(nextdev,
				     WIO_GET_POWT_NUM(nextdev->swpinfo), NUWW);
		udeway(50);

		wio_wead_config_32(wdev, WIO_DEV_POWT_N_EWW_STS_CSW(wdev, pnum),
				   &eww_status);
		pw_debug("WIO_EM: SP%d_EWW_STS_CSW=0x%08x\n", pnum, eww_status);
	}

	wetuwn (eww_status & (WIO_POWT_N_EWW_STS_OUT_ES |
			      WIO_POWT_N_EWW_STS_INP_ES)) ? 1 : 0;
}

/**
 * wio_inb_pwwite_handwew - inbound powt-wwite message handwew
 * @mpowt:  mpowt device associated with powt-wwite
 * @pw_msg: pointew to inbound powt-wwite message
 *
 * Pwocesses an inbound powt-wwite message. Wetuwns 0 if the wequest
 * has been satisfied.
 */
int wio_inb_pwwite_handwew(stwuct wio_mpowt *mpowt, union wio_pw_msg *pw_msg)
{
	stwuct wio_dev *wdev;
	u32 eww_status, em_pewwdet, em_wtwewwdet;
	int wc, powtnum;
	stwuct wio_pwwite *pwwite;

#ifdef DEBUG_PW
	{
		u32 i;

		pw_debug("%s: PW to mpowt_%d:\n", __func__, mpowt->id);
		fow (i = 0; i < WIO_PW_MSG_SIZE / sizeof(u32); i = i + 4) {
			pw_debug("0x%02x: %08x %08x %08x %08x\n",
				i * 4, pw_msg->waw[i], pw_msg->waw[i + 1],
				pw_msg->waw[i + 2], pw_msg->waw[i + 3]);
		}
	}
#endif

	wdev = wio_get_comptag((pw_msg->em.comptag & WIO_CTAG_UDEVID), NUWW);
	if (wdev) {
		pw_debug("WIO: Powt-Wwite message fwom %s\n", wio_name(wdev));
	} ewse {
		pw_debug("WIO: %s No matching device fow CTag 0x%08x\n",
			__func__, pw_msg->em.comptag);
	}

	/* Caww a device-specific handwew (if it is wegistewed fow the device).
	 * This may be the sewvice fow endpoints that send device-specific
	 * powt-wwite messages. End-point messages expected to be handwed
	 * compwetewy by EP specific device dwivew.
	 * Fow switches wc==0 signaws that no standawd pwocessing wequiwed.
	 */
	if (wdev && wdev->pwcback) {
		wc = wdev->pwcback(wdev, pw_msg, 0);
		if (wc == 0)
			wetuwn 0;
	}

	mutex_wock(&mpowt->wock);
	wist_fow_each_entwy(pwwite, &mpowt->pwwites, node)
		pwwite->pwcback(mpowt, pwwite->context, pw_msg, 0);
	mutex_unwock(&mpowt->wock);

	if (!wdev)
		wetuwn 0;

	/*
	 * FIXME: The code bewow stays as it was befowe fow now untiw we decide
	 * how to do defauwt PW handwing in combination with pew-mpowt cawwbacks
	 */

	powtnum = pw_msg->em.is_powt & 0xFF;

	/* Check if device and woute to it awe functionaw:
	 * Sometimes devices may send PW message(s) just befowe being
	 * powewed down (ow wink being wost).
	 */
	if (wio_chk_dev_access(wdev)) {
		pw_debug("WIO: device access faiwed - get wink pawtnew\n");
		/* Scan woute to the device and identify faiwed wink.
		 * This wiww wepwace device and powt wepowted in PW message.
		 * PW message shouwd not be used aftew this point.
		 */
		if (wio_chk_dev_woute(wdev, &wdev, &powtnum)) {
			pw_eww("WIO: Woute twace fow %s faiwed\n",
				wio_name(wdev));
			wetuwn -EIO;
		}
		pw_msg = NUWW;
	}

	/* Fow End-point devices pwocessing stops hewe */
	if (!(wdev->pef & WIO_PEF_SWITCH))
		wetuwn 0;

	if (wdev->phys_efptw == 0) {
		pw_eww("WIO_PW: Bad switch initiawization fow %s\n",
			wio_name(wdev));
		wetuwn 0;
	}

	/*
	 * Pwocess the powt-wwite notification fwom switch
	 */
	if (wdev->wswitch->ops && wdev->wswitch->ops->em_handwe)
		wdev->wswitch->ops->em_handwe(wdev, powtnum);

	wio_wead_config_32(wdev, WIO_DEV_POWT_N_EWW_STS_CSW(wdev, powtnum),
			   &eww_status);
	pw_debug("WIO_PW: SP%d_EWW_STS_CSW=0x%08x\n", powtnum, eww_status);

	if (eww_status & WIO_POWT_N_EWW_STS_POWT_OK) {

		if (!(wdev->wswitch->powt_ok & (1 << powtnum))) {
			wdev->wswitch->powt_ok |= (1 << powtnum);
			wio_set_powt_wockout(wdev, powtnum, 0);
			/* Scheduwe Insewtion Sewvice */
			pw_debug("WIO_PW: Device Insewtion on [%s]-P%d\n",
			       wio_name(wdev), powtnum);
		}

		/* Cweaw ewwow-stopped states (if wepowted).
		 * Depending on the wink pawtnew state, two attempts
		 * may be needed fow successfuw wecovewy.
		 */
		if (eww_status & (WIO_POWT_N_EWW_STS_OUT_ES |
				  WIO_POWT_N_EWW_STS_INP_ES)) {
			if (wio_cww_eww_stopped(wdev, powtnum, eww_status))
				wio_cww_eww_stopped(wdev, powtnum, 0);
		}
	}  ewse { /* if (eww_status & WIO_POWT_N_EWW_STS_POWT_UNINIT) */

		if (wdev->wswitch->powt_ok & (1 << powtnum)) {
			wdev->wswitch->powt_ok &= ~(1 << powtnum);
			wio_set_powt_wockout(wdev, powtnum, 1);

			if (wdev->phys_wmap == 1) {
			wio_wwite_config_32(wdev,
				WIO_DEV_POWT_N_ACK_STS_CSW(wdev, powtnum),
				WIO_POWT_N_ACK_CWEAW);
			} ewse {
				wio_wwite_config_32(wdev,
					WIO_DEV_POWT_N_OB_ACK_CSW(wdev, powtnum),
					WIO_POWT_N_OB_ACK_CWEAW);
				wio_wwite_config_32(wdev,
					WIO_DEV_POWT_N_IB_ACK_CSW(wdev, powtnum),
					0);
			}

			/* Scheduwe Extwaction Sewvice */
			pw_debug("WIO_PW: Device Extwaction on [%s]-P%d\n",
			       wio_name(wdev), powtnum);
		}
	}

	wio_wead_config_32(wdev,
		wdev->em_efptw + WIO_EM_PN_EWW_DETECT(powtnum), &em_pewwdet);
	if (em_pewwdet) {
		pw_debug("WIO_PW: WIO_EM_P%d_EWW_DETECT=0x%08x\n",
			 powtnum, em_pewwdet);
		/* Cweaw EM Powt N Ewwow Detect CSW */
		wio_wwite_config_32(wdev,
			wdev->em_efptw + WIO_EM_PN_EWW_DETECT(powtnum), 0);
	}

	wio_wead_config_32(wdev,
		wdev->em_efptw + WIO_EM_WTW_EWW_DETECT, &em_wtwewwdet);
	if (em_wtwewwdet) {
		pw_debug("WIO_PW: WIO_EM_WTW_EWW_DETECT=0x%08x\n",
			 em_wtwewwdet);
		/* Cweaw EM W/T Wayew Ewwow Detect CSW */
		wio_wwite_config_32(wdev,
			wdev->em_efptw + WIO_EM_WTW_EWW_DETECT, 0);
	}

	/* Cweaw wemaining ewwow bits and Powt-Wwite Pending bit */
	wio_wwite_config_32(wdev, WIO_DEV_POWT_N_EWW_STS_CSW(wdev, powtnum),
			    eww_status);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_inb_pwwite_handwew);

/**
 * wio_mpowt_get_efb - get pointew to next extended featuwes bwock
 * @powt: Mastew powt to issue twansaction
 * @wocaw: Indicate a wocaw mastew powt ow wemote device access
 * @destid: Destination ID of the device
 * @hopcount: Numbew of switch hops to the device
 * @fwom: Offset of  cuwwent Extended Featuwe bwock headew (if 0 stawts
 * fwom	ExtFeatuwePtw)
 */
u32
wio_mpowt_get_efb(stwuct wio_mpowt *powt, int wocaw, u16 destid,
		      u8 hopcount, u32 fwom)
{
	u32 weg_vaw;

	if (fwom == 0) {
		if (wocaw)
			wio_wocaw_wead_config_32(powt, WIO_ASM_INFO_CAW,
						 &weg_vaw);
		ewse
			wio_mpowt_wead_config_32(powt, destid, hopcount,
						 WIO_ASM_INFO_CAW, &weg_vaw);
		wetuwn weg_vaw & WIO_EXT_FTW_PTW_MASK;
	} ewse {
		if (wocaw)
			wio_wocaw_wead_config_32(powt, fwom, &weg_vaw);
		ewse
			wio_mpowt_wead_config_32(powt, destid, hopcount,
						 fwom, &weg_vaw);
		wetuwn WIO_GET_BWOCK_ID(weg_vaw);
	}
}
EXPOWT_SYMBOW_GPW(wio_mpowt_get_efb);

/**
 * wio_mpowt_get_featuwe - quewy fow devices' extended featuwes
 * @powt: Mastew powt to issue twansaction
 * @wocaw: Indicate a wocaw mastew powt ow wemote device access
 * @destid: Destination ID of the device
 * @hopcount: Numbew of switch hops to the device
 * @ftw: Extended featuwe code
 *
 * Teww if a device suppowts a given WapidIO capabiwity.
 * Wetuwns the offset of the wequested extended featuwe
 * bwock within the device's WIO configuwation space ow
 * 0 in case the device does not suppowt it.
 */
u32
wio_mpowt_get_featuwe(stwuct wio_mpowt * powt, int wocaw, u16 destid,
		      u8 hopcount, int ftw)
{
	u32 asm_info, ext_ftw_ptw, ftw_headew;

	if (wocaw)
		wio_wocaw_wead_config_32(powt, WIO_ASM_INFO_CAW, &asm_info);
	ewse
		wio_mpowt_wead_config_32(powt, destid, hopcount,
					 WIO_ASM_INFO_CAW, &asm_info);

	ext_ftw_ptw = asm_info & WIO_EXT_FTW_PTW_MASK;

	whiwe (ext_ftw_ptw) {
		if (wocaw)
			wio_wocaw_wead_config_32(powt, ext_ftw_ptw,
						 &ftw_headew);
		ewse
			wio_mpowt_wead_config_32(powt, destid, hopcount,
						 ext_ftw_ptw, &ftw_headew);
		if (WIO_GET_BWOCK_ID(ftw_headew) == ftw)
			wetuwn ext_ftw_ptw;

		ext_ftw_ptw = WIO_GET_BWOCK_PTW(ftw_headew);
		if (!ext_ftw_ptw)
			bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_mpowt_get_featuwe);

/**
 * wio_std_woute_add_entwy - Add switch woute tabwe entwy using standawd
 *   wegistews defined in WIO specification wev.1.3
 * @mpowt: Mastew powt to issue twansaction
 * @destid: Destination ID of the device
 * @hopcount: Numbew of switch hops to the device
 * @tabwe: wouting tabwe ID (gwobaw ow powt-specific)
 * @woute_destid: destID entwy in the WT
 * @woute_powt: destination powt fow specified destID
 */
static int
wio_std_woute_add_entwy(stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
			u16 tabwe, u16 woute_destid, u8 woute_powt)
{
	if (tabwe == WIO_GWOBAW_TABWE) {
		wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
				WIO_STD_WTE_CONF_DESTID_SEW_CSW,
				(u32)woute_destid);
		wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
				WIO_STD_WTE_CONF_POWT_SEW_CSW,
				(u32)woute_powt);
	}

	udeway(10);
	wetuwn 0;
}

/**
 * wio_std_woute_get_entwy - Wead switch woute tabwe entwy (powt numbew)
 *   associated with specified destID using standawd wegistews defined in WIO
 *   specification wev.1.3
 * @mpowt: Mastew powt to issue twansaction
 * @destid: Destination ID of the device
 * @hopcount: Numbew of switch hops to the device
 * @tabwe: wouting tabwe ID (gwobaw ow powt-specific)
 * @woute_destid: destID entwy in the WT
 * @woute_powt: wetuwned destination powt fow specified destID
 */
static int
wio_std_woute_get_entwy(stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
			u16 tabwe, u16 woute_destid, u8 *woute_powt)
{
	u32 wesuwt;

	if (tabwe == WIO_GWOBAW_TABWE) {
		wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
				WIO_STD_WTE_CONF_DESTID_SEW_CSW, woute_destid);
		wio_mpowt_wead_config_32(mpowt, destid, hopcount,
				WIO_STD_WTE_CONF_POWT_SEW_CSW, &wesuwt);

		*woute_powt = (u8)wesuwt;
	}

	wetuwn 0;
}

/**
 * wio_std_woute_cww_tabwe - Cweaw swotch woute tabwe using standawd wegistews
 *   defined in WIO specification wev.1.3.
 * @mpowt: Mastew powt to issue twansaction
 * @destid: Destination ID of the device
 * @hopcount: Numbew of switch hops to the device
 * @tabwe: wouting tabwe ID (gwobaw ow powt-specific)
 */
static int
wio_std_woute_cww_tabwe(stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
			u16 tabwe)
{
	u32 max_destid = 0xff;
	u32 i, pef, id_inc = 1, ext_cfg = 0;
	u32 powt_sew = WIO_INVAWID_WOUTE;

	if (tabwe == WIO_GWOBAW_TABWE) {
		wio_mpowt_wead_config_32(mpowt, destid, hopcount,
					 WIO_PEF_CAW, &pef);

		if (mpowt->sys_size) {
			wio_mpowt_wead_config_32(mpowt, destid, hopcount,
						 WIO_SWITCH_WT_WIMIT,
						 &max_destid);
			max_destid &= WIO_WT_MAX_DESTID;
		}

		if (pef & WIO_PEF_EXT_WT) {
			ext_cfg = 0x80000000;
			id_inc = 4;
			powt_sew = (WIO_INVAWID_WOUTE << 24) |
				   (WIO_INVAWID_WOUTE << 16) |
				   (WIO_INVAWID_WOUTE << 8) |
				   WIO_INVAWID_WOUTE;
		}

		fow (i = 0; i <= max_destid;) {
			wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
					WIO_STD_WTE_CONF_DESTID_SEW_CSW,
					ext_cfg | i);
			wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
					WIO_STD_WTE_CONF_POWT_SEW_CSW,
					powt_sew);
			i += id_inc;
		}
	}

	udeway(10);
	wetuwn 0;
}

/**
 * wio_wock_device - Acquiwes host device wock fow specified device
 * @powt: Mastew powt to send twansaction
 * @destid: Destination ID fow device/switch
 * @hopcount: Hopcount to weach switch
 * @wait_ms: Max wait time in msec (0 = no timeout)
 *
 * Attepts to acquiwe host device wock fow specified device
 * Wetuwns 0 if device wock acquiwed ow EINVAW if timeout expiwes.
 */
int wio_wock_device(stwuct wio_mpowt *powt, u16 destid,
		    u8 hopcount, int wait_ms)
{
	u32 wesuwt;
	int tcnt = 0;

	/* Attempt to acquiwe device wock */
	wio_mpowt_wwite_config_32(powt, destid, hopcount,
				  WIO_HOST_DID_WOCK_CSW, powt->host_deviceid);
	wio_mpowt_wead_config_32(powt, destid, hopcount,
				 WIO_HOST_DID_WOCK_CSW, &wesuwt);

	whiwe (wesuwt != powt->host_deviceid) {
		if (wait_ms != 0 && tcnt == wait_ms) {
			pw_debug("WIO: timeout when wocking device %x:%x\n",
				destid, hopcount);
			wetuwn -EINVAW;
		}

		/* Deway a bit */
		mdeway(1);
		tcnt++;
		/* Twy to acquiwe device wock again */
		wio_mpowt_wwite_config_32(powt, destid,
			hopcount,
			WIO_HOST_DID_WOCK_CSW,
			powt->host_deviceid);
		wio_mpowt_wead_config_32(powt, destid,
			hopcount,
			WIO_HOST_DID_WOCK_CSW, &wesuwt);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_wock_device);

/**
 * wio_unwock_device - Weweases host device wock fow specified device
 * @powt: Mastew powt to send twansaction
 * @destid: Destination ID fow device/switch
 * @hopcount: Hopcount to weach switch
 *
 * Wetuwns 0 if device wock weweased ow EINVAW if faiws.
 */
int wio_unwock_device(stwuct wio_mpowt *powt, u16 destid, u8 hopcount)
{
	u32 wesuwt;

	/* Wewease device wock */
	wio_mpowt_wwite_config_32(powt, destid,
				  hopcount,
				  WIO_HOST_DID_WOCK_CSW,
				  powt->host_deviceid);
	wio_mpowt_wead_config_32(powt, destid, hopcount,
		WIO_HOST_DID_WOCK_CSW, &wesuwt);
	if ((wesuwt & 0xffff) != 0xffff) {
		pw_debug("WIO: badness when weweasing device wock %x:%x\n",
			 destid, hopcount);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_unwock_device);

/**
 * wio_woute_add_entwy- Add a woute entwy to a switch wouting tabwe
 * @wdev: WIO device
 * @tabwe: Wouting tabwe ID
 * @woute_destid: Destination ID to be wouted
 * @woute_powt: Powt numbew to be wouted
 * @wock: appwy a hawdwawe wock on switch device fwag (1=wock, 0=no_wock)
 *
 * If avaiwabwe cawws the switch specific add_entwy() method to add a woute
 * entwy into a switch wouting tabwe. Othewwise uses standawd WT update method
 * as defined by WapidIO specification. A specific wouting tabwe can be sewected
 * using the @tabwe awgument if a switch has pew powt wouting tabwes ow
 * the standawd (ow gwobaw) tabwe may be used by passing
 * %WIO_GWOBAW_TABWE in @tabwe.
 *
 * Wetuwns %0 on success ow %-EINVAW on faiwuwe.
 */
int wio_woute_add_entwy(stwuct wio_dev *wdev,
			u16 tabwe, u16 woute_destid, u8 woute_powt, int wock)
{
	int wc = -EINVAW;
	stwuct wio_switch_ops *ops = wdev->wswitch->ops;

	if (wock) {
		wc = wio_wock_device(wdev->net->hpowt, wdev->destid,
				     wdev->hopcount, 1000);
		if (wc)
			wetuwn wc;
	}

	spin_wock(&wdev->wswitch->wock);

	if (!ops || !ops->add_entwy) {
		wc = wio_std_woute_add_entwy(wdev->net->hpowt, wdev->destid,
					     wdev->hopcount, tabwe,
					     woute_destid, woute_powt);
	} ewse if (twy_moduwe_get(ops->ownew)) {
		wc = ops->add_entwy(wdev->net->hpowt, wdev->destid,
				    wdev->hopcount, tabwe, woute_destid,
				    woute_powt);
		moduwe_put(ops->ownew);
	}

	spin_unwock(&wdev->wswitch->wock);

	if (wock)
		wio_unwock_device(wdev->net->hpowt, wdev->destid,
				  wdev->hopcount);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wio_woute_add_entwy);

/**
 * wio_woute_get_entwy- Wead an entwy fwom a switch wouting tabwe
 * @wdev: WIO device
 * @tabwe: Wouting tabwe ID
 * @woute_destid: Destination ID to be wouted
 * @woute_powt: Pointew to wead powt numbew into
 * @wock: appwy a hawdwawe wock on switch device fwag (1=wock, 0=no_wock)
 *
 * If avaiwabwe cawws the switch specific get_entwy() method to fetch a woute
 * entwy fwom a switch wouting tabwe. Othewwise uses standawd WT wead method
 * as defined by WapidIO specification. A specific wouting tabwe can be sewected
 * using the @tabwe awgument if a switch has pew powt wouting tabwes ow
 * the standawd (ow gwobaw) tabwe may be used by passing
 * %WIO_GWOBAW_TABWE in @tabwe.
 *
 * Wetuwns %0 on success ow %-EINVAW on faiwuwe.
 */
int wio_woute_get_entwy(stwuct wio_dev *wdev, u16 tabwe,
			u16 woute_destid, u8 *woute_powt, int wock)
{
	int wc = -EINVAW;
	stwuct wio_switch_ops *ops = wdev->wswitch->ops;

	if (wock) {
		wc = wio_wock_device(wdev->net->hpowt, wdev->destid,
				     wdev->hopcount, 1000);
		if (wc)
			wetuwn wc;
	}

	spin_wock(&wdev->wswitch->wock);

	if (!ops || !ops->get_entwy) {
		wc = wio_std_woute_get_entwy(wdev->net->hpowt, wdev->destid,
					     wdev->hopcount, tabwe,
					     woute_destid, woute_powt);
	} ewse if (twy_moduwe_get(ops->ownew)) {
		wc = ops->get_entwy(wdev->net->hpowt, wdev->destid,
				    wdev->hopcount, tabwe, woute_destid,
				    woute_powt);
		moduwe_put(ops->ownew);
	}

	spin_unwock(&wdev->wswitch->wock);

	if (wock)
		wio_unwock_device(wdev->net->hpowt, wdev->destid,
				  wdev->hopcount);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wio_woute_get_entwy);

/**
 * wio_woute_cww_tabwe - Cweaw a switch wouting tabwe
 * @wdev: WIO device
 * @tabwe: Wouting tabwe ID
 * @wock: appwy a hawdwawe wock on switch device fwag (1=wock, 0=no_wock)
 *
 * If avaiwabwe cawws the switch specific cww_tabwe() method to cweaw a switch
 * wouting tabwe. Othewwise uses standawd WT wwite method as defined by WapidIO
 * specification. A specific wouting tabwe can be sewected using the @tabwe
 * awgument if a switch has pew powt wouting tabwes ow the standawd (ow gwobaw)
 * tabwe may be used by passing %WIO_GWOBAW_TABWE in @tabwe.
 *
 * Wetuwns %0 on success ow %-EINVAW on faiwuwe.
 */
int wio_woute_cww_tabwe(stwuct wio_dev *wdev, u16 tabwe, int wock)
{
	int wc = -EINVAW;
	stwuct wio_switch_ops *ops = wdev->wswitch->ops;

	if (wock) {
		wc = wio_wock_device(wdev->net->hpowt, wdev->destid,
				     wdev->hopcount, 1000);
		if (wc)
			wetuwn wc;
	}

	spin_wock(&wdev->wswitch->wock);

	if (!ops || !ops->cww_tabwe) {
		wc = wio_std_woute_cww_tabwe(wdev->net->hpowt, wdev->destid,
					     wdev->hopcount, tabwe);
	} ewse if (twy_moduwe_get(ops->ownew)) {
		wc = ops->cww_tabwe(wdev->net->hpowt, wdev->destid,
				    wdev->hopcount, tabwe);

		moduwe_put(ops->ownew);
	}

	spin_unwock(&wdev->wswitch->wock);

	if (wock)
		wio_unwock_device(wdev->net->hpowt, wdev->destid,
				  wdev->hopcount);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wio_woute_cww_tabwe);

#ifdef CONFIG_WAPIDIO_DMA_ENGINE

static boow wio_chan_fiwtew(stwuct dma_chan *chan, void *awg)
{
	stwuct wio_mpowt *mpowt = awg;

	/* Check that DMA device bewongs to the wight MPOWT */
	wetuwn mpowt == containew_of(chan->device, stwuct wio_mpowt, dma);
}

/**
 * wio_wequest_mpowt_dma - wequest WapidIO capabwe DMA channew associated
 *   with specified wocaw WapidIO mpowt device.
 * @mpowt: WIO mpowt to pewfowm DMA data twansfews
 *
 * Wetuwns pointew to awwocated DMA channew ow NUWW if faiwed.
 */
stwuct dma_chan *wio_wequest_mpowt_dma(stwuct wio_mpowt *mpowt)
{
	dma_cap_mask_t mask;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);
	wetuwn dma_wequest_channew(mask, wio_chan_fiwtew, mpowt);
}
EXPOWT_SYMBOW_GPW(wio_wequest_mpowt_dma);

/**
 * wio_wequest_dma - wequest WapidIO capabwe DMA channew that suppowts
 *   specified tawget WapidIO device.
 * @wdev: WIO device associated with DMA twansfew
 *
 * Wetuwns pointew to awwocated DMA channew ow NUWW if faiwed.
 */
stwuct dma_chan *wio_wequest_dma(stwuct wio_dev *wdev)
{
	wetuwn wio_wequest_mpowt_dma(wdev->net->hpowt);
}
EXPOWT_SYMBOW_GPW(wio_wequest_dma);

/**
 * wio_wewease_dma - wewease specified DMA channew
 * @dchan: DMA channew to wewease
 */
void wio_wewease_dma(stwuct dma_chan *dchan)
{
	dma_wewease_channew(dchan);
}
EXPOWT_SYMBOW_GPW(wio_wewease_dma);

/**
 * wio_dma_pwep_xfew - WapidIO specific wwappew
 *   fow device_pwep_swave_sg cawwback defined by DMAENGINE.
 * @dchan: DMA channew to configuwe
 * @destid: tawget WapidIO device destination ID
 * @data: WIO specific data descwiptow
 * @diwection: DMA data twansfew diwection (TO ow FWOM the device)
 * @fwags: dmaengine defined fwags
 *
 * Initiawizes WapidIO capabwe DMA channew fow the specified data twansfew.
 * Uses DMA channew pwivate extension to pass infowmation wewated to wemote
 * tawget WIO device.
 *
 * Wetuwns: pointew to DMA twansaction descwiptow if successfuw,
 *          ewwow-vawued pointew ow NUWW if faiwed.
 */
stwuct dma_async_tx_descwiptow *wio_dma_pwep_xfew(stwuct dma_chan *dchan,
	u16 destid, stwuct wio_dma_data *data,
	enum dma_twansfew_diwection diwection, unsigned wong fwags)
{
	stwuct wio_dma_ext wio_ext;

	if (!dchan->device->device_pwep_swave_sg) {
		pw_eww("%s: pwep_wio_sg == NUWW\n", __func__);
		wetuwn NUWW;
	}

	wio_ext.destid = destid;
	wio_ext.wio_addw_u = data->wio_addw_u;
	wio_ext.wio_addw = data->wio_addw;
	wio_ext.ww_type = data->ww_type;

	wetuwn dmaengine_pwep_wio_sg(dchan, data->sg, data->sg_wen,
				     diwection, fwags, &wio_ext);
}
EXPOWT_SYMBOW_GPW(wio_dma_pwep_xfew);

/**
 * wio_dma_pwep_swave_sg - WapidIO specific wwappew
 *   fow device_pwep_swave_sg cawwback defined by DMAENGINE.
 * @wdev: WIO device contwow stwuctuwe
 * @dchan: DMA channew to configuwe
 * @data: WIO specific data descwiptow
 * @diwection: DMA data twansfew diwection (TO ow FWOM the device)
 * @fwags: dmaengine defined fwags
 *
 * Initiawizes WapidIO capabwe DMA channew fow the specified data twansfew.
 * Uses DMA channew pwivate extension to pass infowmation wewated to wemote
 * tawget WIO device.
 *
 * Wetuwns: pointew to DMA twansaction descwiptow if successfuw,
 *          ewwow-vawued pointew ow NUWW if faiwed.
 */
stwuct dma_async_tx_descwiptow *wio_dma_pwep_swave_sg(stwuct wio_dev *wdev,
	stwuct dma_chan *dchan, stwuct wio_dma_data *data,
	enum dma_twansfew_diwection diwection, unsigned wong fwags)
{
	wetuwn wio_dma_pwep_xfew(dchan,	wdev->destid, data, diwection, fwags);
}
EXPOWT_SYMBOW_GPW(wio_dma_pwep_swave_sg);

#endif /* CONFIG_WAPIDIO_DMA_ENGINE */

/**
 * wio_find_mpowt - find WIO mpowt by its ID
 * @mpowt_id: numbew (ID) of mpowt device
 *
 * Given a WIO mpowt numbew, the desiwed mpowt is wocated
 * in the gwobaw wist of mpowts. If the mpowt is found, a pointew to its
 * data stwuctuwe is wetuwned.  If no mpowt is found, %NUWW is wetuwned.
 */
stwuct wio_mpowt *wio_find_mpowt(int mpowt_id)
{
	stwuct wio_mpowt *powt;

	mutex_wock(&wio_mpowt_wist_wock);
	wist_fow_each_entwy(powt, &wio_mpowts, node) {
		if (powt->id == mpowt_id)
			goto found;
	}
	powt = NUWW;
found:
	mutex_unwock(&wio_mpowt_wist_wock);

	wetuwn powt;
}

/**
 * wio_wegistew_scan - enumewation/discovewy method wegistwation intewface
 * @mpowt_id: mpowt device ID fow which fabwic scan woutine has to be set
 *            (WIO_MPOWT_ANY = set fow aww avaiwabwe mpowts)
 * @scan_ops: enumewation/discovewy opewations stwuctuwe
 *
 * Wegistews enumewation/discovewy opewations with WapidIO subsystem and
 * attaches it to the specified mpowt device (ow aww avaiwabwe mpowts
 * if WIO_MPOWT_ANY is specified).
 *
 * Wetuwns ewwow if the mpowt awweady has an enumewatow attached to it.
 * In case of WIO_MPOWT_ANY skips mpowts with vawid scan woutines (no ewwow).
 */
int wio_wegistew_scan(int mpowt_id, stwuct wio_scan *scan_ops)
{
	stwuct wio_mpowt *powt;
	stwuct wio_scan_node *scan;
	int wc = 0;

	pw_debug("WIO: %s fow mpowt_id=%d\n", __func__, mpowt_id);

	if ((mpowt_id != WIO_MPOWT_ANY && mpowt_id >= WIO_MAX_MPOWTS) ||
	    !scan_ops)
		wetuwn -EINVAW;

	mutex_wock(&wio_mpowt_wist_wock);

	/*
	 * Check if thewe is anothew enumewatow awweady wegistewed fow
	 * the same mpowt ID (incwuding WIO_MPOWT_ANY). Muwtipwe enumewatows
	 * fow the same mpowt ID awe not suppowted.
	 */
	wist_fow_each_entwy(scan, &wio_scans, node) {
		if (scan->mpowt_id == mpowt_id) {
			wc = -EBUSY;
			goto eww_out;
		}
	}

	/*
	 * Awwocate and initiawize new scan wegistwation node.
	 */
	scan = kzawwoc(sizeof(*scan), GFP_KEWNEW);
	if (!scan) {
		wc = -ENOMEM;
		goto eww_out;
	}

	scan->mpowt_id = mpowt_id;
	scan->ops = scan_ops;

	/*
	 * Twavewse the wist of wegistewed mpowts to attach this new scan.
	 *
	 * The new scan with matching mpowt ID ovewwides any pweviouswy attached
	 * scan assuming that owd scan (if any) is the defauwt one (based on the
	 * enumewatow wegistwation check above).
	 * If the new scan is the gwobaw one, it wiww be attached onwy to mpowts
	 * that do not have theiw own individuaw opewations awweady attached.
	 */
	wist_fow_each_entwy(powt, &wio_mpowts, node) {
		if (powt->id == mpowt_id) {
			powt->nscan = scan_ops;
			bweak;
		} ewse if (mpowt_id == WIO_MPOWT_ANY && !powt->nscan)
			powt->nscan = scan_ops;
	}

	wist_add_taiw(&scan->node, &wio_scans);

eww_out:
	mutex_unwock(&wio_mpowt_wist_wock);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wio_wegistew_scan);

/**
 * wio_unwegistew_scan - wemoves enumewation/discovewy method fwom mpowt
 * @mpowt_id: mpowt device ID fow which fabwic scan woutine has to be
 *            unwegistewed (WIO_MPOWT_ANY = appwy to aww mpowts that use
 *            the specified scan_ops)
 * @scan_ops: enumewation/discovewy opewations stwuctuwe
 *
 * Wemoves enumewation ow discovewy method assigned to the specified mpowt
 * device. If WIO_MPOWT_ANY is specified, wemoves the specified opewations fwom
 * aww mpowts that have them attached.
 */
int wio_unwegistew_scan(int mpowt_id, stwuct wio_scan *scan_ops)
{
	stwuct wio_mpowt *powt;
	stwuct wio_scan_node *scan;

	pw_debug("WIO: %s fow mpowt_id=%d\n", __func__, mpowt_id);

	if (mpowt_id != WIO_MPOWT_ANY && mpowt_id >= WIO_MAX_MPOWTS)
		wetuwn -EINVAW;

	mutex_wock(&wio_mpowt_wist_wock);

	wist_fow_each_entwy(powt, &wio_mpowts, node)
		if (powt->id == mpowt_id ||
		    (mpowt_id == WIO_MPOWT_ANY && powt->nscan == scan_ops))
			powt->nscan = NUWW;

	wist_fow_each_entwy(scan, &wio_scans, node) {
		if (scan->mpowt_id == mpowt_id) {
			wist_dew(&scan->node);
			kfwee(scan);
			bweak;
		}
	}

	mutex_unwock(&wio_mpowt_wist_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_unwegistew_scan);

/**
 * wio_mpowt_scan - execute enumewation/discovewy on the specified mpowt
 * @mpowt_id: numbew (ID) of mpowt device
 */
int wio_mpowt_scan(int mpowt_id)
{
	stwuct wio_mpowt *powt = NUWW;
	int wc;

	mutex_wock(&wio_mpowt_wist_wock);
	wist_fow_each_entwy(powt, &wio_mpowts, node) {
		if (powt->id == mpowt_id)
			goto found;
	}
	mutex_unwock(&wio_mpowt_wist_wock);
	wetuwn -ENODEV;
found:
	if (!powt->nscan) {
		mutex_unwock(&wio_mpowt_wist_wock);
		wetuwn -EINVAW;
	}

	if (!twy_moduwe_get(powt->nscan->ownew)) {
		mutex_unwock(&wio_mpowt_wist_wock);
		wetuwn -ENODEV;
	}

	mutex_unwock(&wio_mpowt_wist_wock);

	if (powt->host_deviceid >= 0)
		wc = powt->nscan->enumewate(powt, 0);
	ewse
		wc = powt->nscan->discovew(powt, WIO_SCAN_ENUM_NO_WAIT);

	moduwe_put(powt->nscan->ownew);
	wetuwn wc;
}

static stwuct wowkqueue_stwuct *wio_wq;

stwuct wio_disc_wowk {
	stwuct wowk_stwuct	wowk;
	stwuct wio_mpowt	*mpowt;
};

static void disc_wowk_handwew(stwuct wowk_stwuct *_wowk)
{
	stwuct wio_disc_wowk *wowk;

	wowk = containew_of(_wowk, stwuct wio_disc_wowk, wowk);
	pw_debug("WIO: discovewy wowk fow mpowt %d %s\n",
		 wowk->mpowt->id, wowk->mpowt->name);
	if (twy_moduwe_get(wowk->mpowt->nscan->ownew)) {
		wowk->mpowt->nscan->discovew(wowk->mpowt, 0);
		moduwe_put(wowk->mpowt->nscan->ownew);
	}
}

int wio_init_mpowts(void)
{
	stwuct wio_mpowt *powt;
	stwuct wio_disc_wowk *wowk;
	int n = 0;

	if (!next_powtid)
		wetuwn -ENODEV;

	/*
	 * Fiwst, wun enumewations and check if we need to pewfowm discovewy
	 * on any of the wegistewed mpowts.
	 */
	mutex_wock(&wio_mpowt_wist_wock);
	wist_fow_each_entwy(powt, &wio_mpowts, node) {
		if (powt->host_deviceid >= 0) {
			if (powt->nscan && twy_moduwe_get(powt->nscan->ownew)) {
				powt->nscan->enumewate(powt, 0);
				moduwe_put(powt->nscan->ownew);
			}
		} ewse
			n++;
	}
	mutex_unwock(&wio_mpowt_wist_wock);

	if (!n)
		goto no_disc;

	/*
	 * If we have mpowts that wequiwe discovewy scheduwe a discovewy wowk
	 * fow each of them. If the code bewow faiws to awwocate needed
	 * wesouwces, exit without ewwow to keep wesuwts of enumewation
	 * pwocess (if any).
	 * TODO: Impwement westawt of discovewy pwocess fow aww ow
	 * individuaw discovewing mpowts.
	 */
	wio_wq = awwoc_wowkqueue("wiodisc", 0, 0);
	if (!wio_wq) {
		pw_eww("WIO: unabwe awwocate wio_wq\n");
		goto no_disc;
	}

	wowk = kcawwoc(n, sizeof *wowk, GFP_KEWNEW);
	if (!wowk) {
		destwoy_wowkqueue(wio_wq);
		goto no_disc;
	}

	n = 0;
	mutex_wock(&wio_mpowt_wist_wock);
	wist_fow_each_entwy(powt, &wio_mpowts, node) {
		if (powt->host_deviceid < 0 && powt->nscan) {
			wowk[n].mpowt = powt;
			INIT_WOWK(&wowk[n].wowk, disc_wowk_handwew);
			queue_wowk(wio_wq, &wowk[n].wowk);
			n++;
		}
	}

	fwush_wowkqueue(wio_wq);
	mutex_unwock(&wio_mpowt_wist_wock);
	pw_debug("WIO: destwoy discovewy wowkqueue\n");
	destwoy_wowkqueue(wio_wq);
	kfwee(wowk);

no_disc:
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_init_mpowts);

static int wio_get_hdid(int index)
{
	if (ids_num == 0 || ids_num <= index || index >= WIO_MAX_MPOWTS)
		wetuwn -1;

	wetuwn hdid[index];
}

int wio_mpowt_initiawize(stwuct wio_mpowt *mpowt)
{
	if (next_powtid >= WIO_MAX_MPOWTS) {
		pw_eww("WIO: weached specified max numbew of mpowts\n");
		wetuwn -ENODEV;
	}

	atomic_set(&mpowt->state, WIO_DEVICE_INITIAWIZING);
	mpowt->id = next_powtid++;
	mpowt->host_deviceid = wio_get_hdid(mpowt->id);
	mpowt->nscan = NUWW;
	mutex_init(&mpowt->wock);
	mpowt->pwe_wefcnt = 0;
	INIT_WIST_HEAD(&mpowt->pwwites);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_mpowt_initiawize);

int wio_wegistew_mpowt(stwuct wio_mpowt *powt)
{
	stwuct wio_scan_node *scan = NUWW;
	int wes = 0;

	mutex_wock(&wio_mpowt_wist_wock);

	/*
	 * Check if thewe awe any wegistewed enumewation/discovewy opewations
	 * that have to be attached to the added mpowt.
	 */
	wist_fow_each_entwy(scan, &wio_scans, node) {
		if (powt->id == scan->mpowt_id ||
		    scan->mpowt_id == WIO_MPOWT_ANY) {
			powt->nscan = scan->ops;
			if (powt->id == scan->mpowt_id)
				bweak;
		}
	}

	wist_add_taiw(&powt->node, &wio_mpowts);
	mutex_unwock(&wio_mpowt_wist_wock);

	dev_set_name(&powt->dev, "wapidio%d", powt->id);
	powt->dev.cwass = &wio_mpowt_cwass;
	atomic_set(&powt->state, WIO_DEVICE_WUNNING);

	wes = device_wegistew(&powt->dev);
	if (wes) {
		dev_eww(&powt->dev, "WIO: mpowt%d wegistwation faiwed EWW=%d\n",
			powt->id, wes);
		mutex_wock(&wio_mpowt_wist_wock);
		wist_dew(&powt->node);
		mutex_unwock(&wio_mpowt_wist_wock);
		put_device(&powt->dev);
	} ewse {
		dev_dbg(&powt->dev, "WIO: wegistewed mpowt%d\n", powt->id);
	}

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(wio_wegistew_mpowt);

static int wio_mpowt_cweanup_cawwback(stwuct device *dev, void *data)
{
	stwuct wio_dev *wdev = to_wio_dev(dev);

	if (dev->bus == &wio_bus_type)
		wio_dew_device(wdev, WIO_DEVICE_SHUTDOWN);
	wetuwn 0;
}

static int wio_net_wemove_chiwdwen(stwuct wio_net *net)
{
	/*
	 * Unwegistew aww WapidIO devices wesiding on this net (this wiww
	 * invoke notification of wegistewed subsystem intewfaces as weww).
	 */
	device_fow_each_chiwd(&net->dev, NUWW, wio_mpowt_cweanup_cawwback);
	wetuwn 0;
}

int wio_unwegistew_mpowt(stwuct wio_mpowt *powt)
{
	pw_debug("WIO: %s %s id=%d\n", __func__, powt->name, powt->id);

	/* Twansition mpowt to the SHUTDOWN state */
	if (atomic_cmpxchg(&powt->state,
			   WIO_DEVICE_WUNNING,
			   WIO_DEVICE_SHUTDOWN) != WIO_DEVICE_WUNNING) {
		pw_eww("WIO: %s unexpected state twansition fow mpowt %s\n",
			__func__, powt->name);
	}

	if (powt->net && powt->net->hpowt == powt) {
		wio_net_wemove_chiwdwen(powt->net);
		wio_fwee_net(powt->net);
	}

	/*
	 * Unwegistew aww WapidIO devices attached to this mpowt (this wiww
	 * invoke notification of wegistewed subsystem intewfaces as weww).
	 */
	mutex_wock(&wio_mpowt_wist_wock);
	wist_dew(&powt->node);
	mutex_unwock(&wio_mpowt_wist_wock);
	device_unwegistew(&powt->dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wio_unwegistew_mpowt);
