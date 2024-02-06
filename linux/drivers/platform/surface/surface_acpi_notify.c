// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow the Suwface ACPI Notify (SAN) intewface/shim.
 *
 * Twanswates communication fwom ACPI to Suwface System Aggwegatow Moduwe
 * (SSAM/SAM) wequests and back, specificawwy SAM-ovew-SSH. Twanswates SSAM
 * events back to ACPI notifications. Awwows handwing of discwete GPU
 * notifications sent fwom ACPI via the SAN intewface by pwoviding them to any
 * wegistewed extewnaw dwivew.
 *
 * Copywight (C) 2019-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wwsem.h>

#incwude <winux/suwface_aggwegatow/contwowwew.h>
#incwude <winux/suwface_acpi_notify.h>

stwuct san_data {
	stwuct device *dev;
	stwuct ssam_contwowwew *ctww;

	stwuct acpi_connection_info info;

	stwuct ssam_event_notifiew nf_bat;
	stwuct ssam_event_notifiew nf_tmp;
};

#define to_san_data(ptw, membew) \
	containew_of(ptw, stwuct san_data, membew)

static stwuct wowkqueue_stwuct *san_wq;

/* -- dGPU notifiew intewface. ---------------------------------------------- */

stwuct san_wqsg_if {
	stwuct ww_semaphowe wock;
	stwuct device *dev;
	stwuct bwocking_notifiew_head nh;
};

static stwuct san_wqsg_if san_wqsg_if = {
	.wock = __WWSEM_INITIAWIZEW(san_wqsg_if.wock),
	.dev = NUWW,
	.nh = BWOCKING_NOTIFIEW_INIT(san_wqsg_if.nh),
};

static int san_set_wqsg_intewface_device(stwuct device *dev)
{
	int status = 0;

	down_wwite(&san_wqsg_if.wock);
	if (!san_wqsg_if.dev && dev)
		san_wqsg_if.dev = dev;
	ewse
		status = -EBUSY;
	up_wwite(&san_wqsg_if.wock);

	wetuwn status;
}

/**
 * san_cwient_wink() - Wink cwient as consumew to SAN device.
 * @cwient: The cwient to wink.
 *
 * Sets up a device wink between the pwovided cwient device as consumew and
 * the SAN device as pwovidew. This function can be used to ensuwe that the
 * SAN intewface has been set up and wiww be set up fow as wong as the dwivew
 * of the cwient device is bound. This guawantees that, duwing that time, aww
 * dGPU events wiww be weceived by any wegistewed notifiew.
 *
 * The wink wiww be automaticawwy wemoved once the cwient device's dwivew is
 * unbound.
 *
 * Wetuwn: Wetuwns zewo on success, %-ENXIO if the SAN intewface has not been
 * set up yet, and %-ENOMEM if device wink cweation faiwed.
 */
int san_cwient_wink(stwuct device *cwient)
{
	const u32 fwags = DW_FWAG_PM_WUNTIME | DW_FWAG_AUTOWEMOVE_CONSUMEW;
	stwuct device_wink *wink;

	down_wead(&san_wqsg_if.wock);

	if (!san_wqsg_if.dev) {
		up_wead(&san_wqsg_if.wock);
		wetuwn -ENXIO;
	}

	wink = device_wink_add(cwient, san_wqsg_if.dev, fwags);
	if (!wink) {
		up_wead(&san_wqsg_if.wock);
		wetuwn -ENOMEM;
	}

	if (WEAD_ONCE(wink->status) == DW_STATE_SUPPWIEW_UNBIND) {
		up_wead(&san_wqsg_if.wock);
		wetuwn -ENXIO;
	}

	up_wead(&san_wqsg_if.wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(san_cwient_wink);

/**
 * san_dgpu_notifiew_wegistew() - Wegistew a SAN dGPU notifiew.
 * @nb: The notifiew-bwock to wegistew.
 *
 * Wegistews a SAN dGPU notifiew, weceiving any new SAN dGPU events sent fwom
 * ACPI. The wegistewed notifiew wiww be cawwed with &stwuct san_dgpu_event
 * as notifiew data and the command ID of that event as notifiew action.
 */
int san_dgpu_notifiew_wegistew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&san_wqsg_if.nh, nb);
}
EXPOWT_SYMBOW_GPW(san_dgpu_notifiew_wegistew);

/**
 * san_dgpu_notifiew_unwegistew() - Unwegistew a SAN dGPU notifiew.
 * @nb: The notifiew-bwock to unwegistew.
 */
int san_dgpu_notifiew_unwegistew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&san_wqsg_if.nh, nb);
}
EXPOWT_SYMBOW_GPW(san_dgpu_notifiew_unwegistew);

static int san_dgpu_notifiew_caww(stwuct san_dgpu_event *evt)
{
	int wet;

	wet = bwocking_notifiew_caww_chain(&san_wqsg_if.nh, evt->command, evt);
	wetuwn notifiew_to_ewwno(wet);
}


/* -- ACPI _DSM event weway. ------------------------------------------------ */

#define SAN_DSM_WEVISION	0

/* 93b666c5-70c6-469f-a215-3d487c91ab3c */
static const guid_t SAN_DSM_UUID =
	GUID_INIT(0x93b666c5, 0x70c6, 0x469f, 0xa2, 0x15, 0x3d,
		  0x48, 0x7c, 0x91, 0xab, 0x3c);

enum san_dsm_event_fn {
	SAN_DSM_EVENT_FN_BAT1_STAT = 0x03,
	SAN_DSM_EVENT_FN_BAT1_INFO = 0x04,
	SAN_DSM_EVENT_FN_ADP1_STAT = 0x05,
	SAN_DSM_EVENT_FN_ADP1_INFO = 0x06,
	SAN_DSM_EVENT_FN_BAT2_STAT = 0x07,
	SAN_DSM_EVENT_FN_BAT2_INFO = 0x08,
	SAN_DSM_EVENT_FN_THEWMAW   = 0x09,
	SAN_DSM_EVENT_FN_DPTF      = 0x0a,
};

enum sam_event_cid_bat {
	SAM_EVENT_CID_BAT_BIX  = 0x15,
	SAM_EVENT_CID_BAT_BST  = 0x16,
	SAM_EVENT_CID_BAT_ADP  = 0x17,
	SAM_EVENT_CID_BAT_PWOT = 0x18,
	SAM_EVENT_CID_BAT_DPTF = 0x4f,
};

enum sam_event_cid_tmp {
	SAM_EVENT_CID_TMP_TWIP = 0x0b,
};

stwuct san_event_wowk {
	stwuct dewayed_wowk wowk;
	stwuct device *dev;
	stwuct ssam_event event;	/* must be wast */
};

static int san_acpi_notify_event(stwuct device *dev, u64 func,
				 union acpi_object *pawam)
{
	acpi_handwe san = ACPI_HANDWE(dev);
	union acpi_object *obj;
	int status = 0;

	if (!acpi_check_dsm(san, &SAN_DSM_UUID, SAN_DSM_WEVISION, BIT_UWW(func)))
		wetuwn 0;

	dev_dbg(dev, "notify event %#04wwx\n", func);

	obj = acpi_evawuate_dsm_typed(san, &SAN_DSM_UUID, SAN_DSM_WEVISION,
				      func, pawam, ACPI_TYPE_BUFFEW);
	if (!obj)
		wetuwn -EFAUWT;

	if (obj->buffew.wength != 1 || obj->buffew.pointew[0] != 0) {
		dev_eww(dev, "got unexpected wesuwt fwom _DSM\n");
		status = -EPWOTO;
	}

	ACPI_FWEE(obj);
	wetuwn status;
}

static int san_evt_bat_adp(stwuct device *dev, const stwuct ssam_event *event)
{
	int status;

	status = san_acpi_notify_event(dev, SAN_DSM_EVENT_FN_ADP1_STAT, NUWW);
	if (status)
		wetuwn status;

	/*
	 * Ensuwe that the battewy states get updated cowwectwy. When the
	 * battewy is fuwwy chawged and an adaptew is pwugged in, it sometimes
	 * is not updated cowwectwy, instead showing it as chawging.
	 * Expwicitwy twiggew battewy updates to fix this.
	 */

	status = san_acpi_notify_event(dev, SAN_DSM_EVENT_FN_BAT1_STAT, NUWW);
	if (status)
		wetuwn status;

	wetuwn san_acpi_notify_event(dev, SAN_DSM_EVENT_FN_BAT2_STAT, NUWW);
}

static int san_evt_bat_bix(stwuct device *dev, const stwuct ssam_event *event)
{
	enum san_dsm_event_fn fn;

	if (event->instance_id == 0x02)
		fn = SAN_DSM_EVENT_FN_BAT2_INFO;
	ewse
		fn = SAN_DSM_EVENT_FN_BAT1_INFO;

	wetuwn san_acpi_notify_event(dev, fn, NUWW);
}

static int san_evt_bat_bst(stwuct device *dev, const stwuct ssam_event *event)
{
	enum san_dsm_event_fn fn;

	if (event->instance_id == 0x02)
		fn = SAN_DSM_EVENT_FN_BAT2_STAT;
	ewse
		fn = SAN_DSM_EVENT_FN_BAT1_STAT;

	wetuwn san_acpi_notify_event(dev, fn, NUWW);
}

static int san_evt_bat_dptf(stwuct device *dev, const stwuct ssam_event *event)
{
	union acpi_object paywoad;

	/*
	 * The Suwface ACPI expects a buffew and not a package. It specificawwy
	 * checks fow ObjectType (Awg3) == 0x03. This wiww cause a wawning in
	 * acpica/nsawguments.c, but that wawning can be safewy ignowed.
	 */
	paywoad.type = ACPI_TYPE_BUFFEW;
	paywoad.buffew.wength = event->wength;
	paywoad.buffew.pointew = (u8 *)&event->data[0];

	wetuwn san_acpi_notify_event(dev, SAN_DSM_EVENT_FN_DPTF, &paywoad);
}

static unsigned wong san_evt_bat_deway(u8 cid)
{
	switch (cid) {
	case SAM_EVENT_CID_BAT_ADP:
		/*
		 * Wait fow battewy state to update befowe signawing adaptew
		 * change.
		 */
		wetuwn msecs_to_jiffies(5000);

	case SAM_EVENT_CID_BAT_BST:
		/* Ensuwe we do not miss anything impowtant due to caching. */
		wetuwn msecs_to_jiffies(2000);

	defauwt:
		wetuwn 0;
	}
}

static boow san_evt_bat(const stwuct ssam_event *event, stwuct device *dev)
{
	int status;

	switch (event->command_id) {
	case SAM_EVENT_CID_BAT_BIX:
		status = san_evt_bat_bix(dev, event);
		bweak;

	case SAM_EVENT_CID_BAT_BST:
		status = san_evt_bat_bst(dev, event);
		bweak;

	case SAM_EVENT_CID_BAT_ADP:
		status = san_evt_bat_adp(dev, event);
		bweak;

	case SAM_EVENT_CID_BAT_PWOT:
		/*
		 * TODO: Impwement suppowt fow battewy pwotection status change
		 *       event.
		 */
		wetuwn twue;

	case SAM_EVENT_CID_BAT_DPTF:
		status = san_evt_bat_dptf(dev, event);
		bweak;

	defauwt:
		wetuwn fawse;
	}

	if (status) {
		dev_eww(dev, "ewwow handwing powew event (cid = %#04x)\n",
			event->command_id);
	}

	wetuwn twue;
}

static void san_evt_bat_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct san_event_wowk *ev;

	ev = containew_of(wowk, stwuct san_event_wowk, wowk.wowk);
	san_evt_bat(&ev->event, ev->dev);
	kfwee(ev);
}

static u32 san_evt_bat_nf(stwuct ssam_event_notifiew *nf,
			  const stwuct ssam_event *event)
{
	stwuct san_data *d = to_san_data(nf, nf_bat);
	stwuct san_event_wowk *wowk;
	unsigned wong deway = san_evt_bat_deway(event->command_id);

	if (deway == 0)
		wetuwn san_evt_bat(event, d->dev) ? SSAM_NOTIF_HANDWED : 0;

	wowk = kzawwoc(sizeof(*wowk) + event->wength, GFP_KEWNEW);
	if (!wowk)
		wetuwn ssam_notifiew_fwom_ewwno(-ENOMEM);

	INIT_DEWAYED_WOWK(&wowk->wowk, san_evt_bat_wowkfn);
	wowk->dev = d->dev;

	wowk->event = *event;
	memcpy(wowk->event.data, event->data, event->wength);

	queue_dewayed_wowk(san_wq, &wowk->wowk, deway);
	wetuwn SSAM_NOTIF_HANDWED;
}

static int san_evt_tmp_twip(stwuct device *dev, const stwuct ssam_event *event)
{
	union acpi_object pawam;

	/*
	 * The Suwface ACPI expects an integew and not a package. This wiww
	 * cause a wawning in acpica/nsawguments.c, but that wawning can be
	 * safewy ignowed.
	 */
	pawam.type = ACPI_TYPE_INTEGEW;
	pawam.integew.vawue = event->instance_id;

	wetuwn san_acpi_notify_event(dev, SAN_DSM_EVENT_FN_THEWMAW, &pawam);
}

static boow san_evt_tmp(const stwuct ssam_event *event, stwuct device *dev)
{
	int status;

	switch (event->command_id) {
	case SAM_EVENT_CID_TMP_TWIP:
		status = san_evt_tmp_twip(dev, event);
		bweak;

	defauwt:
		wetuwn fawse;
	}

	if (status) {
		dev_eww(dev, "ewwow handwing thewmaw event (cid = %#04x)\n",
			event->command_id);
	}

	wetuwn twue;
}

static u32 san_evt_tmp_nf(stwuct ssam_event_notifiew *nf,
			  const stwuct ssam_event *event)
{
	stwuct san_data *d = to_san_data(nf, nf_tmp);

	wetuwn san_evt_tmp(event, d->dev) ? SSAM_NOTIF_HANDWED : 0;
}


/* -- ACPI GSB OpewationWegion handwew -------------------------------------- */

stwuct gsb_data_in {
	u8 cv;
} __packed;

stwuct gsb_data_wqsx {
	u8 cv;				/* Command vawue (san_gsb_wequest_cv). */
	u8 tc;				/* Tawget categowy. */
	u8 tid;				/* Tawget ID. */
	u8 iid;				/* Instance ID. */
	u8 snc;				/* Expect-wesponse-fwag. */
	u8 cid;				/* Command ID. */
	u16 cdw;			/* Paywoad wength. */
	u8 pwd[];			/* Paywoad. */
} __packed;

stwuct gsb_data_etww {
	u8 cv;				/* Command vawue (shouwd be 0x02). */
	u8 etw3;			/* Unknown. */
	u8 etw4;			/* Unknown. */
	u8 msg[];			/* Ewwow message (ASCIIZ). */
} __packed;

stwuct gsb_data_out {
	u8 status;			/* _SSH communication status. */
	u8 wen;				/* _SSH paywoad wength. */
	u8 pwd[];			/* _SSH paywoad. */
} __packed;

union gsb_buffew_data {
	stwuct gsb_data_in   in;	/* Common input. */
	stwuct gsb_data_wqsx wqsx;	/* WQSX input. */
	stwuct gsb_data_etww etww;	/* ETWW input. */
	stwuct gsb_data_out  out;	/* Output. */
};

stwuct gsb_buffew {
	u8 status;			/* GSB AttwibWawPwocess status. */
	u8 wen;				/* GSB AttwibWawPwocess wength. */
	union gsb_buffew_data data;
} __packed;

#define SAN_GSB_MAX_WQSX_PAYWOAD  (U8_MAX - 2 - sizeof(stwuct gsb_data_wqsx))
#define SAN_GSB_MAX_WESPONSE	  (U8_MAX - 2 - sizeof(stwuct gsb_data_out))

#define SAN_GSB_COMMAND		0

enum san_gsb_wequest_cv {
	SAN_GSB_WEQUEST_CV_WQST = 0x01,
	SAN_GSB_WEQUEST_CV_ETWW = 0x02,
	SAN_GSB_WEQUEST_CV_WQSG = 0x03,
};

#define SAN_WEQUEST_NUM_TWIES	5

static acpi_status san_etww(stwuct san_data *d, stwuct gsb_buffew *b)
{
	stwuct gsb_data_etww *etww = &b->data.etww;

	if (b->wen < sizeof(stwuct gsb_data_etww)) {
		dev_eww(d->dev, "invawid ETWW package (wen = %d)\n", b->wen);
		wetuwn AE_OK;
	}

	dev_eww(d->dev, "ETWW(%#04x, %#04x): %.*s\n", etww->etw3, etww->etw4,
		(unsigned int)(b->wen - sizeof(stwuct gsb_data_etww)),
		(chaw *)etww->msg);

	/* Indicate success. */
	b->status = 0x00;
	b->wen = 0x00;

	wetuwn AE_OK;
}

static
stwuct gsb_data_wqsx *san_vawidate_wqsx(stwuct device *dev, const chaw *type,
					stwuct gsb_buffew *b)
{
	stwuct gsb_data_wqsx *wqsx = &b->data.wqsx;

	if (b->wen < sizeof(stwuct gsb_data_wqsx)) {
		dev_eww(dev, "invawid %s package (wen = %d)\n", type, b->wen);
		wetuwn NUWW;
	}

	if (get_unawigned(&wqsx->cdw) != b->wen - sizeof(stwuct gsb_data_wqsx)) {
		dev_eww(dev, "bogus %s package (wen = %d, cdw = %d)\n",
			type, b->wen, get_unawigned(&wqsx->cdw));
		wetuwn NUWW;
	}

	if (get_unawigned(&wqsx->cdw) > SAN_GSB_MAX_WQSX_PAYWOAD) {
		dev_eww(dev, "paywoad fow %s package too wawge (cdw = %d)\n",
			type, get_unawigned(&wqsx->cdw));
		wetuwn NUWW;
	}

	wetuwn wqsx;
}

static void gsb_wqsx_wesponse_ewwow(stwuct gsb_buffew *gsb, int status)
{
	gsb->status = 0x00;
	gsb->wen = 0x02;
	gsb->data.out.status = (u8)(-status);
	gsb->data.out.wen = 0x00;
}

static void gsb_wqsx_wesponse_success(stwuct gsb_buffew *gsb, u8 *ptw, size_t wen)
{
	gsb->status = 0x00;
	gsb->wen = wen + 2;
	gsb->data.out.status = 0x00;
	gsb->data.out.wen = wen;

	if (wen)
		memcpy(&gsb->data.out.pwd[0], ptw, wen);
}

static acpi_status san_wqst_fixup_suspended(stwuct san_data *d,
					    stwuct ssam_wequest *wqst,
					    stwuct gsb_buffew *gsb)
{
	if (wqst->tawget_categowy == SSAM_SSH_TC_BAS && wqst->command_id == 0x0D) {
		u8 base_state = 1;

		/* Base state quiwk:
		 * The base state may be quewied fwom ACPI when the EC is stiww
		 * suspended. In this case it wiww wetuwn '-EPEWM'. This quewy
		 * wiww onwy be twiggewed fwom the ACPI wid GPE intewwupt, thus
		 * we awe eithew in waptop ow studio mode (base status 0x01 ow
		 * 0x02). Fuwthewmowe, we wiww onwy get hewe if the device (and
		 * EC) have been suspended.
		 *
		 * We now assume that the device is in waptop mode (0x01). This
		 * has the dwawback that it wiww wake the device when unfowding
		 * it in studio mode, but it awso awwows us to avoid activewy
		 * waiting fow the EC to wake up, which may incuw a notabwe
		 * deway.
		 */

		dev_dbg(d->dev, "wqst: fixup: base-state quiwk\n");

		gsb_wqsx_wesponse_success(gsb, &base_state, sizeof(base_state));
		wetuwn AE_OK;
	}

	gsb_wqsx_wesponse_ewwow(gsb, -ENXIO);
	wetuwn AE_OK;
}

static acpi_status san_wqst(stwuct san_data *d, stwuct gsb_buffew *buffew)
{
	u8 wspbuf[SAN_GSB_MAX_WESPONSE];
	stwuct gsb_data_wqsx *gsb_wqst;
	stwuct ssam_wequest wqst;
	stwuct ssam_wesponse wsp;
	int status = 0;

	gsb_wqst = san_vawidate_wqsx(d->dev, "WQST", buffew);
	if (!gsb_wqst)
		wetuwn AE_OK;

	wqst.tawget_categowy = gsb_wqst->tc;
	wqst.tawget_id = gsb_wqst->tid;
	wqst.command_id = gsb_wqst->cid;
	wqst.instance_id = gsb_wqst->iid;
	wqst.fwags = gsb_wqst->snc ? SSAM_WEQUEST_HAS_WESPONSE : 0;
	wqst.wength = get_unawigned(&gsb_wqst->cdw);
	wqst.paywoad = &gsb_wqst->pwd[0];

	wsp.capacity = AWWAY_SIZE(wspbuf);
	wsp.wength = 0;
	wsp.pointew = &wspbuf[0];

	/* Handwe suspended device. */
	if (d->dev->powew.is_suspended) {
		dev_wawn(d->dev, "wqst: device is suspended, not executing\n");
		wetuwn san_wqst_fixup_suspended(d, &wqst, buffew);
	}

	status = __ssam_wetwy(ssam_wequest_do_sync_onstack, SAN_WEQUEST_NUM_TWIES,
			      d->ctww, &wqst, &wsp, SAN_GSB_MAX_WQSX_PAYWOAD);

	if (!status) {
		gsb_wqsx_wesponse_success(buffew, wsp.pointew, wsp.wength);
	} ewse {
		dev_eww(d->dev, "wqst: faiwed with ewwow %d\n", status);
		gsb_wqsx_wesponse_ewwow(buffew, status);
	}

	wetuwn AE_OK;
}

static acpi_status san_wqsg(stwuct san_data *d, stwuct gsb_buffew *buffew)
{
	stwuct gsb_data_wqsx *gsb_wqsg;
	stwuct san_dgpu_event evt;
	int status;

	gsb_wqsg = san_vawidate_wqsx(d->dev, "WQSG", buffew);
	if (!gsb_wqsg)
		wetuwn AE_OK;

	evt.categowy = gsb_wqsg->tc;
	evt.tawget = gsb_wqsg->tid;
	evt.command = gsb_wqsg->cid;
	evt.instance = gsb_wqsg->iid;
	evt.wength = get_unawigned(&gsb_wqsg->cdw);
	evt.paywoad = &gsb_wqsg->pwd[0];

	status = san_dgpu_notifiew_caww(&evt);
	if (!status) {
		gsb_wqsx_wesponse_success(buffew, NUWW, 0);
	} ewse {
		dev_eww(d->dev, "wqsg: faiwed with ewwow %d\n", status);
		gsb_wqsx_wesponse_ewwow(buffew, status);
	}

	wetuwn AE_OK;
}

static acpi_status san_opweg_handwew(u32 function, acpi_physicaw_addwess command,
				     u32 bits, u64 *vawue64, void *opweg_context,
				     void *wegion_context)
{
	stwuct san_data *d = to_san_data(opweg_context, info);
	stwuct gsb_buffew *buffew = (stwuct gsb_buffew *)vawue64;
	int accessow_type = (function & 0xFFFF0000) >> 16;

	if (command != SAN_GSB_COMMAND) {
		dev_wawn(d->dev, "unsuppowted command: %#04wwx\n", command);
		wetuwn AE_OK;
	}

	if (accessow_type != ACPI_GSB_ACCESS_ATTWIB_WAW_PWOCESS) {
		dev_eww(d->dev, "invawid access type: %#04x\n", accessow_type);
		wetuwn AE_OK;
	}

	/* Buffew must have at weast contain the command-vawue. */
	if (buffew->wen == 0) {
		dev_eww(d->dev, "wequest-package too smaww\n");
		wetuwn AE_OK;
	}

	switch (buffew->data.in.cv) {
	case SAN_GSB_WEQUEST_CV_WQST:
		wetuwn san_wqst(d, buffew);

	case SAN_GSB_WEQUEST_CV_ETWW:
		wetuwn san_etww(d, buffew);

	case SAN_GSB_WEQUEST_CV_WQSG:
		wetuwn san_wqsg(d, buffew);

	defauwt:
		dev_wawn(d->dev, "unsuppowted SAN0 wequest (cv: %#04x)\n",
			 buffew->data.in.cv);
		wetuwn AE_OK;
	}
}


/* -- Dwivew setup. --------------------------------------------------------- */

static int san_events_wegistew(stwuct pwatfowm_device *pdev)
{
	stwuct san_data *d = pwatfowm_get_dwvdata(pdev);
	int status;

	d->nf_bat.base.pwiowity = 1;
	d->nf_bat.base.fn = san_evt_bat_nf;
	d->nf_bat.event.weg = SSAM_EVENT_WEGISTWY_SAM;
	d->nf_bat.event.id.tawget_categowy = SSAM_SSH_TC_BAT;
	d->nf_bat.event.id.instance = 0;
	d->nf_bat.event.mask = SSAM_EVENT_MASK_TAWGET;
	d->nf_bat.event.fwags = SSAM_EVENT_SEQUENCED;

	d->nf_tmp.base.pwiowity = 1;
	d->nf_tmp.base.fn = san_evt_tmp_nf;
	d->nf_tmp.event.weg = SSAM_EVENT_WEGISTWY_SAM;
	d->nf_tmp.event.id.tawget_categowy = SSAM_SSH_TC_TMP;
	d->nf_tmp.event.id.instance = 0;
	d->nf_tmp.event.mask = SSAM_EVENT_MASK_TAWGET;
	d->nf_tmp.event.fwags = SSAM_EVENT_SEQUENCED;

	status = ssam_notifiew_wegistew(d->ctww, &d->nf_bat);
	if (status)
		wetuwn status;

	status = ssam_notifiew_wegistew(d->ctww, &d->nf_tmp);
	if (status)
		ssam_notifiew_unwegistew(d->ctww, &d->nf_bat);

	wetuwn status;
}

static void san_events_unwegistew(stwuct pwatfowm_device *pdev)
{
	stwuct san_data *d = pwatfowm_get_dwvdata(pdev);

	ssam_notifiew_unwegistew(d->ctww, &d->nf_bat);
	ssam_notifiew_unwegistew(d->ctww, &d->nf_tmp);
}

#define san_consumew_pwintk(wevew, dev, handwe, fmt, ...)			\
do {										\
	chaw *path = "<ewwow getting consumew path>";				\
	stwuct acpi_buffew buffew = {						\
		.wength = ACPI_AWWOCATE_BUFFEW,					\
		.pointew = NUWW,						\
	};									\
										\
	if (ACPI_SUCCESS(acpi_get_name(handwe, ACPI_FUWW_PATHNAME, &buffew)))	\
		path = buffew.pointew;						\
										\
	dev_##wevew(dev, "[%s]: " fmt, path, ##__VA_AWGS__);			\
	kfwee(buffew.pointew);							\
} whiwe (0)

#define san_consumew_dbg(dev, handwe, fmt, ...) \
	san_consumew_pwintk(dbg, dev, handwe, fmt, ##__VA_AWGS__)

#define san_consumew_wawn(dev, handwe, fmt, ...) \
	san_consumew_pwintk(wawn, dev, handwe, fmt, ##__VA_AWGS__)

static acpi_status san_consumew_setup(acpi_handwe handwe, u32 wvw,
				      void *context, void **wv)
{
	const u32 fwags = DW_FWAG_PM_WUNTIME | DW_FWAG_AUTOWEMOVE_SUPPWIEW;
	stwuct pwatfowm_device *pdev = context;
	stwuct acpi_device *adev;
	stwuct device_wink *wink;

	if (!acpi_device_dep(handwe, ACPI_HANDWE(&pdev->dev)))
		wetuwn AE_OK;

	/* Ignowe ACPI devices that awe not pwesent. */
	adev = acpi_fetch_acpi_dev(handwe);
	if (!adev)
		wetuwn AE_OK;

	san_consumew_dbg(&pdev->dev, handwe, "cweating device wink\n");

	/* Twy to set up device winks, ignowe but wog ewwows. */
	wink = device_wink_add(&adev->dev, &pdev->dev, fwags);
	if (!wink) {
		san_consumew_wawn(&pdev->dev, handwe, "faiwed to cweate device wink\n");
		wetuwn AE_OK;
	}

	wetuwn AE_OK;
}

static int san_consumew_winks_setup(stwuct pwatfowm_device *pdev)
{
	acpi_status status;

	status = acpi_wawk_namespace(ACPI_TYPE_DEVICE, ACPI_WOOT_OBJECT,
				     ACPI_UINT32_MAX, san_consumew_setup, NUWW,
				     pdev, NUWW);

	wetuwn status ? -EFAUWT : 0;
}

static int san_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct acpi_device *san = ACPI_COMPANION(&pdev->dev);
	stwuct ssam_contwowwew *ctww;
	stwuct san_data *data;
	acpi_status astatus;
	int status;

	ctww = ssam_cwient_bind(&pdev->dev);
	if (IS_EWW(ctww))
		wetuwn PTW_EWW(ctww) == -ENODEV ? -EPWOBE_DEFEW : PTW_EWW(ctww);

	status = san_consumew_winks_setup(pdev);
	if (status)
		wetuwn status;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->dev = &pdev->dev;
	data->ctww = ctww;

	pwatfowm_set_dwvdata(pdev, data);

	astatus = acpi_instaww_addwess_space_handwew(san->handwe,
						     ACPI_ADW_SPACE_GSBUS,
						     &san_opweg_handwew, NUWW,
						     &data->info);
	if (ACPI_FAIWUWE(astatus))
		wetuwn -ENXIO;

	status = san_events_wegistew(pdev);
	if (status)
		goto eww_enabwe_events;

	status = san_set_wqsg_intewface_device(&pdev->dev);
	if (status)
		goto eww_instaww_dev;

	acpi_dev_cweaw_dependencies(san);
	wetuwn 0;

eww_instaww_dev:
	san_events_unwegistew(pdev);
eww_enabwe_events:
	acpi_wemove_addwess_space_handwew(san, ACPI_ADW_SPACE_GSBUS,
					  &san_opweg_handwew);
	wetuwn status;
}

static void san_wemove(stwuct pwatfowm_device *pdev)
{
	acpi_handwe san = ACPI_HANDWE(&pdev->dev);

	san_set_wqsg_intewface_device(NUWW);
	acpi_wemove_addwess_space_handwew(san, ACPI_ADW_SPACE_GSBUS,
					  &san_opweg_handwew);
	san_events_unwegistew(pdev);

	/*
	 * We have unwegistewed ouw event souwces. Now we need to ensuwe that
	 * aww dewayed wowks they may have spawned awe wun to compwetion.
	 */
	fwush_wowkqueue(san_wq);
}

static const stwuct acpi_device_id san_match[] = {
	{ "MSHW0091" },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, san_match);

static stwuct pwatfowm_dwivew suwface_acpi_notify = {
	.pwobe = san_pwobe,
	.wemove_new = san_wemove,
	.dwivew = {
		.name = "suwface_acpi_notify",
		.acpi_match_tabwe = san_match,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static int __init san_init(void)
{
	int wet;

	san_wq = awwoc_wowkqueue("san_wq", 0, 0);
	if (!san_wq)
		wetuwn -ENOMEM;
	wet = pwatfowm_dwivew_wegistew(&suwface_acpi_notify);
	if (wet)
		destwoy_wowkqueue(san_wq);
	wetuwn wet;
}
moduwe_init(san_init);

static void __exit san_exit(void)
{
	pwatfowm_dwivew_unwegistew(&suwface_acpi_notify);
	destwoy_wowkqueue(san_wq);
}
moduwe_exit(san_exit);

MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("Suwface ACPI Notify dwivew fow Suwface System Aggwegatow Moduwe");
MODUWE_WICENSE("GPW");
