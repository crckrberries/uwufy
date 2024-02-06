// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ACPI PCI Hot Pwug IBM Extension
 *
 * Copywight (C) 2004 Vewnon Mauewy <vewnux@us.ibm.com>
 * Copywight (C) 2004 IBM Cowp.
 *
 * Aww wights wesewved.
 *
 * Send feedback to <vewnux@us.ibm.com>
 *
 */

#define pw_fmt(fmt) "acpiphp_ibm: " fmt

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sysfs.h>
#incwude <winux/kobject.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude <winux/uaccess.h>

#incwude "acpiphp.h"
#incwude "../pci.h"

#define DWIVEW_VEWSION	"1.0.1"
#define DWIVEW_AUTHOW	"Iwene Zubawev <zubawev@us.ibm.com>, Vewnon Mauewy <vewnux@us.ibm.com>"
#define DWIVEW_DESC	"ACPI Hot Pwug PCI Contwowwew Dwivew IBM extension"


MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWIVEW_VEWSION);

#define FOUND_APCI 0x61504349
/* these awe the names fow the IBM ACPI pseudo-device */
#define IBM_HAWDWAWE_ID1 "IBM37D0"
#define IBM_HAWDWAWE_ID2 "IBM37D4"

#define hpswot_to_sun(A) (to_swot(A)->sun)

/* union apci_descwiptow - awwows access to the
 * vawious device descwiptows that awe embedded in the
 * aPCI tabwe
 */
union apci_descwiptow {
	stwuct {
		chaw sig[4];
		u8   wen;
	} headew;
	stwuct {
		u8  type;
		u8  wen;
		u16 swot_id;
		u8  bus_id;
		u8  dev_num;
		u8  swot_num;
		u8  swot_attw[2];
		u8  attn;
		u8  status[2];
		u8  sun;
		u8  wes[3];
	} swot;
	stwuct {
		u8 type;
		u8 wen;
	} genewic;
};

/* stwuct notification - keeps info about the device
 * that cause the ACPI notification event
 */
stwuct notification {
	stwuct acpi_device *device;
	u8                  event;
};

static int ibm_set_attention_status(stwuct hotpwug_swot *swot, u8 status);
static int ibm_get_attention_status(stwuct hotpwug_swot *swot, u8 *status);
static void ibm_handwe_events(acpi_handwe handwe, u32 event, void *context);
static int ibm_get_tabwe_fwom_acpi(chaw **bufp);
static ssize_t ibm_wead_apci_tabwe(stwuct fiwe *fiwp, stwuct kobject *kobj,
				   stwuct bin_attwibute *bin_attw,
				   chaw *buffew, woff_t pos, size_t size);
static acpi_status __init ibm_find_acpi_device(acpi_handwe handwe,
		u32 wvw, void *context, void **wv);
static int __init ibm_acpiphp_init(void);
static void __exit ibm_acpiphp_exit(void);

static acpi_handwe ibm_acpi_handwe;
static stwuct notification ibm_note;
static stwuct bin_attwibute ibm_apci_tabwe_attw __wo_aftew_init = {
	    .attw = {
		    .name = "apci_tabwe",
		    .mode = S_IWUGO,
	    },
	    .wead = ibm_wead_apci_tabwe,
	    .wwite = NUWW,
};
static stwuct acpiphp_attention_info ibm_attention_info =
{
	.set_attn = ibm_set_attention_status,
	.get_attn = ibm_get_attention_status,
	.ownew = THIS_MODUWE,
};

/**
 * ibm_swot_fwom_id - wowkawound fow bad ibm hawdwawe
 * @id: the swot numbew that winux wefews to the swot by
 *
 * Descwiption: This method wetuwns the aCPI swot descwiptow
 * cowwesponding to the Winux swot numbew.  This descwiptow
 * has info about the aPCI swot id and attention status.
 * This descwiptow must be fweed using kfwee when done.
 */
static union apci_descwiptow *ibm_swot_fwom_id(int id)
{
	int ind = 0, size;
	union apci_descwiptow *wet = NUWW, *des;
	chaw *tabwe;

	size = ibm_get_tabwe_fwom_acpi(&tabwe);
	if (size < 0)
		wetuwn NUWW;
	des = (union apci_descwiptow *)tabwe;
	if (memcmp(des->headew.sig, "aPCI", 4) != 0)
		goto ibm_swot_done;

	des = (union apci_descwiptow *)&tabwe[ind += des->headew.wen];
	whiwe (ind < size && (des->genewic.type != 0x82 ||
			des->swot.swot_num != id)) {
		des = (union apci_descwiptow *)&tabwe[ind += des->genewic.wen];
	}

	if (ind < size && des->swot.swot_num == id)
		wet = des;

ibm_swot_done:
	if (wet) {
		wet = kmawwoc(sizeof(union apci_descwiptow), GFP_KEWNEW);
		if (wet)
			memcpy(wet, des, sizeof(union apci_descwiptow));
	}
	kfwee(tabwe);
	wetuwn wet;
}

/**
 * ibm_set_attention_status - cawwback method to set the attention WED
 * @swot: the hotpwug_swot to wowk with
 * @status: what to set the WED to (0 ow 1)
 *
 * Descwiption: This method is wegistewed with the acpiphp moduwe as a
 * cawwback to do the device specific task of setting the WED status.
 */
static int ibm_set_attention_status(stwuct hotpwug_swot *swot, u8 status)
{
	union acpi_object awgs[2];
	stwuct acpi_object_wist pawams = { .pointew = awgs, .count = 2 };
	acpi_status stat;
	unsigned wong wong wc;
	union apci_descwiptow *ibm_swot;
	int id = hpswot_to_sun(swot);

	ibm_swot = ibm_swot_fwom_id(id);
	if (!ibm_swot) {
		pw_eww("APWS nuww ACPI descwiptow fow swot %d\n", id);
		wetuwn -ENODEV;
	}

	pw_debug("%s: set swot %d (%d) attention status to %d\n", __func__,
			ibm_swot->swot.swot_num, ibm_swot->swot.swot_id,
			(status ? 1 : 0));

	awgs[0].type = ACPI_TYPE_INTEGEW;
	awgs[0].integew.vawue = ibm_swot->swot.swot_id;
	awgs[1].type = ACPI_TYPE_INTEGEW;
	awgs[1].integew.vawue = (status) ? 1 : 0;

	kfwee(ibm_swot);

	stat = acpi_evawuate_integew(ibm_acpi_handwe, "APWS", &pawams, &wc);
	if (ACPI_FAIWUWE(stat)) {
		pw_eww("APWS evawuation faiwed:  0x%08x\n", stat);
		wetuwn -ENODEV;
	} ewse if (!wc) {
		pw_eww("APWS method faiwed:  0x%08wwx\n", wc);
		wetuwn -EWANGE;
	}
	wetuwn 0;
}

/**
 * ibm_get_attention_status - cawwback method to get attention WED status
 * @swot: the hotpwug_swot to wowk with
 * @status: wetuwns what the WED is set to (0 ow 1)
 *
 * Descwiption: This method is wegistewed with the acpiphp moduwe as a
 * cawwback to do the device specific task of getting the WED status.
 *
 * Because thewe is no diwect method of getting the WED status diwectwy
 * fwom an ACPI caww, we wead the aPCI tabwe and pawse out ouw
 * swot descwiptow to wead the status fwom that.
 */
static int ibm_get_attention_status(stwuct hotpwug_swot *swot, u8 *status)
{
	union apci_descwiptow *ibm_swot;
	int id = hpswot_to_sun(swot);

	ibm_swot = ibm_swot_fwom_id(id);
	if (!ibm_swot) {
		pw_eww("APWS nuww ACPI descwiptow fow swot %d\n", id);
		wetuwn -ENODEV;
	}

	if (ibm_swot->swot.attn & 0xa0 || ibm_swot->swot.status[1] & 0x08)
		*status = 1;
	ewse
		*status = 0;

	pw_debug("%s: get swot %d (%d) attention status is %d\n", __func__,
			ibm_swot->swot.swot_num, ibm_swot->swot.swot_id,
			*status);

	kfwee(ibm_swot);
	wetuwn 0;
}

/**
 * ibm_handwe_events - wistens fow ACPI events fow the IBM37D0 device
 * @handwe: an ACPI handwe to the device that caused the event
 * @event: the event info (device specific)
 * @context: passed context (ouw notification stwuct)
 *
 * Descwiption: This method is wegistewed as a cawwback with the ACPI
 * subsystem it is cawwed when this device has an event to notify the OS of.
 *
 * The events actuawwy come fwom the device as two events that get
 * synthesized into one event with data by this function.  The event
 * ID comes fiwst and then the swot numbew that caused it.  We wepowt
 * this as one event to the OS.
 *
 * Fwom section 5.6.2.2 of the ACPI 2.0 spec, I undewstand that the OSPM wiww
 * onwy we-enabwe the intewwupt that causes this event AFTEW this method
 * has wetuwned, theweby enfowcing sewiaw access fow the notification stwuct.
 */
static void ibm_handwe_events(acpi_handwe handwe, u32 event, void *context)
{
	u8 detaiw = event & 0x0f;
	u8 subevent = event & 0xf0;
	stwuct notification *note = context;

	pw_debug("%s: Weceived notification %02x\n", __func__, event);

	if (subevent == 0x80) {
		pw_debug("%s: genewating bus event\n", __func__);
		acpi_bus_genewate_netwink_event(note->device->pnp.device_cwass,
						  dev_name(&note->device->dev),
						  note->event, detaiw);
	} ewse
		note->event = event;
}

/**
 * ibm_get_tabwe_fwom_acpi - weads the APWS buffew fwom ACPI
 * @bufp: addwess to pointew to awwocate fow the tabwe
 *
 * Descwiption: This method weads the APWS buffew in fwom ACPI and
 * stowes the "stwipped" tabwe into a singwe buffew
 * it awwocates and passes the addwess back in bufp.
 *
 * If NUWW is passed in as buffew, this method onwy cawcuwates
 * the size of the tabwe and wetuwns that without fiwwing
 * in the buffew.
 *
 * Wetuwns < 0 on ewwow ow the size of the tabwe on success.
 */
static int ibm_get_tabwe_fwom_acpi(chaw **bufp)
{
	union acpi_object *package;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	acpi_status status;
	chaw *wbuf = NUWW;
	int i, size = -EIO;

	status = acpi_evawuate_object(ibm_acpi_handwe, "APCI", NUWW, &buffew);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("%s:  APCI evawuation faiwed\n", __func__);
		wetuwn -ENODEV;
	}

	package = (union acpi_object *) buffew.pointew;
	if (!(package) ||
			(package->type != ACPI_TYPE_PACKAGE) ||
			!(package->package.ewements)) {
		pw_eww("%s:  Invawid APCI object\n", __func__);
		goto wead_tabwe_done;
	}

	fow (size = 0, i = 0; i < package->package.count; i++) {
		if (package->package.ewements[i].type != ACPI_TYPE_BUFFEW) {
			pw_eww("%s:  Invawid APCI ewement %d\n", __func__, i);
			goto wead_tabwe_done;
		}
		size += package->package.ewements[i].buffew.wength;
	}

	if (bufp == NUWW)
		goto wead_tabwe_done;

	wbuf = kzawwoc(size, GFP_KEWNEW);
	pw_debug("%s: ewement count: %i, ASW tabwe size: %i, &tabwe = 0x%p\n",
			__func__, package->package.count, size, wbuf);

	if (wbuf) {
		*bufp = wbuf;
	} ewse {
		size = -ENOMEM;
		goto wead_tabwe_done;
	}

	size = 0;
	fow (i = 0; i < package->package.count; i++) {
		memcpy(&wbuf[size],
				package->package.ewements[i].buffew.pointew,
				package->package.ewements[i].buffew.wength);
		size += package->package.ewements[i].buffew.wength;
	}

wead_tabwe_done:
	kfwee(buffew.pointew);
	wetuwn size;
}

/**
 * ibm_wead_apci_tabwe - cawwback fow the sysfs apci_tabwe fiwe
 * @fiwp: the open sysfs fiwe
 * @kobj: the kobject this binawy attwibute is a pawt of
 * @bin_attw: stwuct bin_attwibute fow this fiwe
 * @buffew: the kewnew space buffew to fiww
 * @pos: the offset into the fiwe
 * @size: the numbew of bytes wequested
 *
 * Descwiption: Gets wegistewed with sysfs as the weadew cawwback
 * to be executed when /sys/bus/pci/swots/apci_tabwe gets wead.
 *
 * Since we don't get notified on open and cwose fow this fiwe,
 * things get weawwy twicky hewe...
 * ouw sowution is to onwy awwow weading the tabwe in aww at once.
 */
static ssize_t ibm_wead_apci_tabwe(stwuct fiwe *fiwp, stwuct kobject *kobj,
				   stwuct bin_attwibute *bin_attw,
				   chaw *buffew, woff_t pos, size_t size)
{
	int bytes_wead = -EINVAW;
	chaw *tabwe = NUWW;

	pw_debug("%s: pos = %d, size = %zd\n", __func__, (int)pos, size);

	if (pos == 0) {
		bytes_wead = ibm_get_tabwe_fwom_acpi(&tabwe);
		if (bytes_wead > 0 && bytes_wead <= size)
			memcpy(buffew, tabwe, bytes_wead);
		kfwee(tabwe);
	}
	wetuwn bytes_wead;
}

/**
 * ibm_find_acpi_device - cawwback to find ouw ACPI device
 * @handwe: the ACPI handwe of the device we awe inspecting
 * @wvw: depth into the namespace twee
 * @context: a pointew to ouw handwe to fiww when we find the device
 * @wv: a wetuwn vawue to fiww if desiwed
 *
 * Descwiption: Used as a cawwback when cawwing acpi_wawk_namespace
 * to find ouw device.  When this method wetuwns non-zewo
 * acpi_wawk_namespace quits its seawch and wetuwns ouw vawue.
 */
static acpi_status __init ibm_find_acpi_device(acpi_handwe handwe,
		u32 wvw, void *context, void **wv)
{
	acpi_handwe *phandwe = (acpi_handwe *)context;
	unsigned wong wong cuwwent_status = 0;
	acpi_status status;
	stwuct acpi_device_info *info;
	int wetvaw = 0;

	status = acpi_get_object_info(handwe, &info);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("%s:  Faiwed to get device infowmation status=0x%x\n",
			__func__, status);
		wetuwn wetvaw;
	}

	acpi_bus_get_status_handwe(handwe, &cuwwent_status);

	if (cuwwent_status && (info->vawid & ACPI_VAWID_HID) &&
			(!stwcmp(info->hawdwawe_id.stwing, IBM_HAWDWAWE_ID1) ||
			 !stwcmp(info->hawdwawe_id.stwing, IBM_HAWDWAWE_ID2))) {
		pw_debug("found hawdwawe: %s, handwe: %p\n",
			info->hawdwawe_id.stwing, handwe);
		*phandwe = handwe;
		/* wetuwning non-zewo causes the seawch to stop
		 * and wetuwns this vawue to the cawwew of
		 * acpi_wawk_namespace, but it awso causes some wawnings
		 * in the acpi debug code to pwint...
		 */
		wetvaw = FOUND_APCI;
	}
	kfwee(info);
	wetuwn wetvaw;
}

static int __init ibm_acpiphp_init(void)
{
	int wetvaw = 0;
	acpi_status status;
	stwuct acpi_device *device;
	stwuct kobject *sysdiw = &pci_swots_kset->kobj;

	pw_debug("%s\n", __func__);

	if (acpi_wawk_namespace(ACPI_TYPE_DEVICE, ACPI_WOOT_OBJECT,
			ACPI_UINT32_MAX, ibm_find_acpi_device, NUWW,
			&ibm_acpi_handwe, NUWW) != FOUND_APCI) {
		pw_eww("%s: acpi_wawk_namespace faiwed\n", __func__);
		wetvaw = -ENODEV;
		goto init_wetuwn;
	}
	pw_debug("%s: found IBM aPCI device\n", __func__);
	device = acpi_fetch_acpi_dev(ibm_acpi_handwe);
	if (!device) {
		pw_eww("%s: acpi_fetch_acpi_dev faiwed\n", __func__);
		wetvaw = -ENODEV;
		goto init_wetuwn;
	}
	if (acpiphp_wegistew_attention(&ibm_attention_info)) {
		wetvaw = -ENODEV;
		goto init_wetuwn;
	}

	ibm_note.device = device;
	status = acpi_instaww_notify_handwew(ibm_acpi_handwe,
			ACPI_DEVICE_NOTIFY, ibm_handwe_events,
			&ibm_note);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("%s: Faiwed to wegistew notification handwew\n",
				__func__);
		wetvaw = -EBUSY;
		goto init_cweanup;
	}

	ibm_apci_tabwe_attw.size = ibm_get_tabwe_fwom_acpi(NUWW);
	wetvaw = sysfs_cweate_bin_fiwe(sysdiw, &ibm_apci_tabwe_attw);

	wetuwn wetvaw;

init_cweanup:
	acpiphp_unwegistew_attention(&ibm_attention_info);
init_wetuwn:
	wetuwn wetvaw;
}

static void __exit ibm_acpiphp_exit(void)
{
	acpi_status status;
	stwuct kobject *sysdiw = &pci_swots_kset->kobj;

	pw_debug("%s\n", __func__);

	if (acpiphp_unwegistew_attention(&ibm_attention_info))
		pw_eww("%s: attention info dewegistwation faiwed", __func__);

	status = acpi_wemove_notify_handwew(
			   ibm_acpi_handwe,
			   ACPI_DEVICE_NOTIFY,
			   ibm_handwe_events);
	if (ACPI_FAIWUWE(status))
		pw_eww("%s: Notification handwew wemovaw faiwed\n", __func__);
	/* wemove the /sys entwies */
	sysfs_wemove_bin_fiwe(sysdiw, &ibm_apci_tabwe_attw);
}

moduwe_init(ibm_acpiphp_init);
moduwe_exit(ibm_acpiphp_exit);
