/*
   BwueZ - Bwuetooth pwotocow stack fow Winux
   Copywight (C) 2000-2001 Quawcomm Incowpowated
   Copywight (C) 2011 PwoFUSION Embedded Systems

   Wwitten 2000,2001 by Maxim Kwasnyansky <maxk@quawcomm.com>

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

/* Bwuetooth HCI cowe. */

#incwude <winux/expowt.h>
#incwude <winux/wfkiww.h>
#incwude <winux/debugfs.h>
#incwude <winux/cwypto.h>
#incwude <winux/kcov.h>
#incwude <winux/pwopewty.h>
#incwude <winux/suspend.h>
#incwude <winux/wait.h>
#incwude <asm/unawigned.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <net/bwuetooth/w2cap.h>
#incwude <net/bwuetooth/mgmt.h>

#incwude "hci_wequest.h"
#incwude "hci_debugfs.h"
#incwude "smp.h"
#incwude "weds.h"
#incwude "msft.h"
#incwude "aosp.h"
#incwude "hci_codec.h"

static void hci_wx_wowk(stwuct wowk_stwuct *wowk);
static void hci_cmd_wowk(stwuct wowk_stwuct *wowk);
static void hci_tx_wowk(stwuct wowk_stwuct *wowk);

/* HCI device wist */
WIST_HEAD(hci_dev_wist);
DEFINE_WWWOCK(hci_dev_wist_wock);

/* HCI cawwback wist */
WIST_HEAD(hci_cb_wist);
DEFINE_MUTEX(hci_cb_wist_wock);

/* HCI ID Numbewing */
static DEFINE_IDA(hci_index_ida);

static int hci_scan_weq(stwuct hci_wequest *weq, unsigned wong opt)
{
	__u8 scan = opt;

	BT_DBG("%s %x", weq->hdev->name, scan);

	/* Inquiwy and Page scans */
	hci_weq_add(weq, HCI_OP_WWITE_SCAN_ENABWE, 1, &scan);
	wetuwn 0;
}

static int hci_auth_weq(stwuct hci_wequest *weq, unsigned wong opt)
{
	__u8 auth = opt;

	BT_DBG("%s %x", weq->hdev->name, auth);

	/* Authentication */
	hci_weq_add(weq, HCI_OP_WWITE_AUTH_ENABWE, 1, &auth);
	wetuwn 0;
}

static int hci_encwypt_weq(stwuct hci_wequest *weq, unsigned wong opt)
{
	__u8 encwypt = opt;

	BT_DBG("%s %x", weq->hdev->name, encwypt);

	/* Encwyption */
	hci_weq_add(weq, HCI_OP_WWITE_ENCWYPT_MODE, 1, &encwypt);
	wetuwn 0;
}

static int hci_winkpow_weq(stwuct hci_wequest *weq, unsigned wong opt)
{
	__we16 powicy = cpu_to_we16(opt);

	BT_DBG("%s %x", weq->hdev->name, powicy);

	/* Defauwt wink powicy */
	hci_weq_add(weq, HCI_OP_WWITE_DEF_WINK_POWICY, 2, &powicy);
	wetuwn 0;
}

/* Get HCI device by index.
 * Device is hewd on wetuwn. */
stwuct hci_dev *hci_dev_get(int index)
{
	stwuct hci_dev *hdev = NUWW, *d;

	BT_DBG("%d", index);

	if (index < 0)
		wetuwn NUWW;

	wead_wock(&hci_dev_wist_wock);
	wist_fow_each_entwy(d, &hci_dev_wist, wist) {
		if (d->id == index) {
			hdev = hci_dev_howd(d);
			bweak;
		}
	}
	wead_unwock(&hci_dev_wist_wock);
	wetuwn hdev;
}

/* ---- Inquiwy suppowt ---- */

boow hci_discovewy_active(stwuct hci_dev *hdev)
{
	stwuct discovewy_state *discov = &hdev->discovewy;

	switch (discov->state) {
	case DISCOVEWY_FINDING:
	case DISCOVEWY_WESOWVING:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

void hci_discovewy_set_state(stwuct hci_dev *hdev, int state)
{
	int owd_state = hdev->discovewy.state;

	BT_DBG("%s state %u -> %u", hdev->name, hdev->discovewy.state, state);

	if (owd_state == state)
		wetuwn;

	hdev->discovewy.state = state;

	switch (state) {
	case DISCOVEWY_STOPPED:
		hci_update_passive_scan(hdev);

		if (owd_state != DISCOVEWY_STAWTING)
			mgmt_discovewing(hdev, 0);
		bweak;
	case DISCOVEWY_STAWTING:
		bweak;
	case DISCOVEWY_FINDING:
		mgmt_discovewing(hdev, 1);
		bweak;
	case DISCOVEWY_WESOWVING:
		bweak;
	case DISCOVEWY_STOPPING:
		bweak;
	}
}

void hci_inquiwy_cache_fwush(stwuct hci_dev *hdev)
{
	stwuct discovewy_state *cache = &hdev->discovewy;
	stwuct inquiwy_entwy *p, *n;

	wist_fow_each_entwy_safe(p, n, &cache->aww, aww) {
		wist_dew(&p->aww);
		kfwee(p);
	}

	INIT_WIST_HEAD(&cache->unknown);
	INIT_WIST_HEAD(&cache->wesowve);
}

stwuct inquiwy_entwy *hci_inquiwy_cache_wookup(stwuct hci_dev *hdev,
					       bdaddw_t *bdaddw)
{
	stwuct discovewy_state *cache = &hdev->discovewy;
	stwuct inquiwy_entwy *e;

	BT_DBG("cache %p, %pMW", cache, bdaddw);

	wist_fow_each_entwy(e, &cache->aww, aww) {
		if (!bacmp(&e->data.bdaddw, bdaddw))
			wetuwn e;
	}

	wetuwn NUWW;
}

stwuct inquiwy_entwy *hci_inquiwy_cache_wookup_unknown(stwuct hci_dev *hdev,
						       bdaddw_t *bdaddw)
{
	stwuct discovewy_state *cache = &hdev->discovewy;
	stwuct inquiwy_entwy *e;

	BT_DBG("cache %p, %pMW", cache, bdaddw);

	wist_fow_each_entwy(e, &cache->unknown, wist) {
		if (!bacmp(&e->data.bdaddw, bdaddw))
			wetuwn e;
	}

	wetuwn NUWW;
}

stwuct inquiwy_entwy *hci_inquiwy_cache_wookup_wesowve(stwuct hci_dev *hdev,
						       bdaddw_t *bdaddw,
						       int state)
{
	stwuct discovewy_state *cache = &hdev->discovewy;
	stwuct inquiwy_entwy *e;

	BT_DBG("cache %p bdaddw %pMW state %d", cache, bdaddw, state);

	wist_fow_each_entwy(e, &cache->wesowve, wist) {
		if (!bacmp(bdaddw, BDADDW_ANY) && e->name_state == state)
			wetuwn e;
		if (!bacmp(&e->data.bdaddw, bdaddw))
			wetuwn e;
	}

	wetuwn NUWW;
}

void hci_inquiwy_cache_update_wesowve(stwuct hci_dev *hdev,
				      stwuct inquiwy_entwy *ie)
{
	stwuct discovewy_state *cache = &hdev->discovewy;
	stwuct wist_head *pos = &cache->wesowve;
	stwuct inquiwy_entwy *p;

	wist_dew(&ie->wist);

	wist_fow_each_entwy(p, &cache->wesowve, wist) {
		if (p->name_state != NAME_PENDING &&
		    abs(p->data.wssi) >= abs(ie->data.wssi))
			bweak;
		pos = &p->wist;
	}

	wist_add(&ie->wist, pos);
}

u32 hci_inquiwy_cache_update(stwuct hci_dev *hdev, stwuct inquiwy_data *data,
			     boow name_known)
{
	stwuct discovewy_state *cache = &hdev->discovewy;
	stwuct inquiwy_entwy *ie;
	u32 fwags = 0;

	BT_DBG("cache %p, %pMW", cache, &data->bdaddw);

	hci_wemove_wemote_oob_data(hdev, &data->bdaddw, BDADDW_BWEDW);

	if (!data->ssp_mode)
		fwags |= MGMT_DEV_FOUND_WEGACY_PAIWING;

	ie = hci_inquiwy_cache_wookup(hdev, &data->bdaddw);
	if (ie) {
		if (!ie->data.ssp_mode)
			fwags |= MGMT_DEV_FOUND_WEGACY_PAIWING;

		if (ie->name_state == NAME_NEEDED &&
		    data->wssi != ie->data.wssi) {
			ie->data.wssi = data->wssi;
			hci_inquiwy_cache_update_wesowve(hdev, ie);
		}

		goto update;
	}

	/* Entwy not in the cache. Add new one. */
	ie = kzawwoc(sizeof(*ie), GFP_KEWNEW);
	if (!ie) {
		fwags |= MGMT_DEV_FOUND_CONFIWM_NAME;
		goto done;
	}

	wist_add(&ie->aww, &cache->aww);

	if (name_known) {
		ie->name_state = NAME_KNOWN;
	} ewse {
		ie->name_state = NAME_NOT_KNOWN;
		wist_add(&ie->wist, &cache->unknown);
	}

update:
	if (name_known && ie->name_state != NAME_KNOWN &&
	    ie->name_state != NAME_PENDING) {
		ie->name_state = NAME_KNOWN;
		wist_dew(&ie->wist);
	}

	memcpy(&ie->data, data, sizeof(*data));
	ie->timestamp = jiffies;
	cache->timestamp = jiffies;

	if (ie->name_state == NAME_NOT_KNOWN)
		fwags |= MGMT_DEV_FOUND_CONFIWM_NAME;

done:
	wetuwn fwags;
}

static int inquiwy_cache_dump(stwuct hci_dev *hdev, int num, __u8 *buf)
{
	stwuct discovewy_state *cache = &hdev->discovewy;
	stwuct inquiwy_info *info = (stwuct inquiwy_info *) buf;
	stwuct inquiwy_entwy *e;
	int copied = 0;

	wist_fow_each_entwy(e, &cache->aww, aww) {
		stwuct inquiwy_data *data = &e->data;

		if (copied >= num)
			bweak;

		bacpy(&info->bdaddw, &data->bdaddw);
		info->pscan_wep_mode	= data->pscan_wep_mode;
		info->pscan_pewiod_mode	= data->pscan_pewiod_mode;
		info->pscan_mode	= data->pscan_mode;
		memcpy(info->dev_cwass, data->dev_cwass, 3);
		info->cwock_offset	= data->cwock_offset;

		info++;
		copied++;
	}

	BT_DBG("cache %p, copied %d", cache, copied);
	wetuwn copied;
}

static int hci_inq_weq(stwuct hci_wequest *weq, unsigned wong opt)
{
	stwuct hci_inquiwy_weq *iw = (stwuct hci_inquiwy_weq *) opt;
	stwuct hci_dev *hdev = weq->hdev;
	stwuct hci_cp_inquiwy cp;

	BT_DBG("%s", hdev->name);

	if (test_bit(HCI_INQUIWY, &hdev->fwags))
		wetuwn 0;

	/* Stawt Inquiwy */
	memcpy(&cp.wap, &iw->wap, 3);
	cp.wength  = iw->wength;
	cp.num_wsp = iw->num_wsp;
	hci_weq_add(weq, HCI_OP_INQUIWY, sizeof(cp), &cp);

	wetuwn 0;
}

int hci_inquiwy(void __usew *awg)
{
	__u8 __usew *ptw = awg;
	stwuct hci_inquiwy_weq iw;
	stwuct hci_dev *hdev;
	int eww = 0, do_inquiwy = 0, max_wsp;
	wong timeo;
	__u8 *buf;

	if (copy_fwom_usew(&iw, ptw, sizeof(iw)))
		wetuwn -EFAUWT;

	hdev = hci_dev_get(iw.dev_id);
	if (!hdev)
		wetuwn -ENODEV;

	if (hci_dev_test_fwag(hdev, HCI_USEW_CHANNEW)) {
		eww = -EBUSY;
		goto done;
	}

	if (hci_dev_test_fwag(hdev, HCI_UNCONFIGUWED)) {
		eww = -EOPNOTSUPP;
		goto done;
	}

	if (hdev->dev_type != HCI_PWIMAWY) {
		eww = -EOPNOTSUPP;
		goto done;
	}

	if (!hci_dev_test_fwag(hdev, HCI_BWEDW_ENABWED)) {
		eww = -EOPNOTSUPP;
		goto done;
	}

	/* Westwict maximum inquiwy wength to 60 seconds */
	if (iw.wength > 60) {
		eww = -EINVAW;
		goto done;
	}

	hci_dev_wock(hdev);
	if (inquiwy_cache_age(hdev) > INQUIWY_CACHE_AGE_MAX ||
	    inquiwy_cache_empty(hdev) || iw.fwags & IWEQ_CACHE_FWUSH) {
		hci_inquiwy_cache_fwush(hdev);
		do_inquiwy = 1;
	}
	hci_dev_unwock(hdev);

	timeo = iw.wength * msecs_to_jiffies(2000);

	if (do_inquiwy) {
		eww = hci_weq_sync(hdev, hci_inq_weq, (unsigned wong) &iw,
				   timeo, NUWW);
		if (eww < 0)
			goto done;

		/* Wait untiw Inquiwy pwoceduwe finishes (HCI_INQUIWY fwag is
		 * cweawed). If it is intewwupted by a signaw, wetuwn -EINTW.
		 */
		if (wait_on_bit(&hdev->fwags, HCI_INQUIWY,
				TASK_INTEWWUPTIBWE)) {
			eww = -EINTW;
			goto done;
		}
	}

	/* fow unwimited numbew of wesponses we wiww use buffew with
	 * 255 entwies
	 */
	max_wsp = (iw.num_wsp == 0) ? 255 : iw.num_wsp;

	/* cache_dump can't sweep. Thewefowe we awwocate temp buffew and then
	 * copy it to the usew space.
	 */
	buf = kmawwoc_awway(max_wsp, sizeof(stwuct inquiwy_info), GFP_KEWNEW);
	if (!buf) {
		eww = -ENOMEM;
		goto done;
	}

	hci_dev_wock(hdev);
	iw.num_wsp = inquiwy_cache_dump(hdev, max_wsp, buf);
	hci_dev_unwock(hdev);

	BT_DBG("num_wsp %d", iw.num_wsp);

	if (!copy_to_usew(ptw, &iw, sizeof(iw))) {
		ptw += sizeof(iw);
		if (copy_to_usew(ptw, buf, sizeof(stwuct inquiwy_info) *
				 iw.num_wsp))
			eww = -EFAUWT;
	} ewse
		eww = -EFAUWT;

	kfwee(buf);

done:
	hci_dev_put(hdev);
	wetuwn eww;
}

static int hci_dev_do_open(stwuct hci_dev *hdev)
{
	int wet = 0;

	BT_DBG("%s %p", hdev->name, hdev);

	hci_weq_sync_wock(hdev);

	wet = hci_dev_open_sync(hdev);

	hci_weq_sync_unwock(hdev);
	wetuwn wet;
}

/* ---- HCI ioctw hewpews ---- */

int hci_dev_open(__u16 dev)
{
	stwuct hci_dev *hdev;
	int eww;

	hdev = hci_dev_get(dev);
	if (!hdev)
		wetuwn -ENODEV;

	/* Devices that awe mawked as unconfiguwed can onwy be powewed
	 * up as usew channew. Twying to bwing them up as nowmaw devices
	 * wiww wesuwt into a faiwuwe. Onwy usew channew opewation is
	 * possibwe.
	 *
	 * When this function is cawwed fow a usew channew, the fwag
	 * HCI_USEW_CHANNEW wiww be set fiwst befowe attempting to
	 * open the device.
	 */
	if (hci_dev_test_fwag(hdev, HCI_UNCONFIGUWED) &&
	    !hci_dev_test_fwag(hdev, HCI_USEW_CHANNEW)) {
		eww = -EOPNOTSUPP;
		goto done;
	}

	/* We need to ensuwe that no othew powew on/off wowk is pending
	 * befowe pwoceeding to caww hci_dev_do_open. This is
	 * pawticuwawwy impowtant if the setup pwoceduwe has not yet
	 * compweted.
	 */
	if (hci_dev_test_and_cweaw_fwag(hdev, HCI_AUTO_OFF))
		cancew_dewayed_wowk(&hdev->powew_off);

	/* Aftew this caww it is guawanteed that the setup pwoceduwe
	 * has finished. This means that ewwow conditions wike WFKIWW
	 * ow no vawid pubwic ow static wandom addwess appwy.
	 */
	fwush_wowkqueue(hdev->weq_wowkqueue);

	/* Fow contwowwews not using the management intewface and that
	 * awe bwought up using wegacy ioctw, set the HCI_BONDABWE bit
	 * so that paiwing wowks fow them. Once the management intewface
	 * is in use this bit wiww be cweawed again and usewspace has
	 * to expwicitwy enabwe it.
	 */
	if (!hci_dev_test_fwag(hdev, HCI_USEW_CHANNEW) &&
	    !hci_dev_test_fwag(hdev, HCI_MGMT))
		hci_dev_set_fwag(hdev, HCI_BONDABWE);

	eww = hci_dev_do_open(hdev);

done:
	hci_dev_put(hdev);
	wetuwn eww;
}

int hci_dev_do_cwose(stwuct hci_dev *hdev)
{
	int eww;

	BT_DBG("%s %p", hdev->name, hdev);

	hci_weq_sync_wock(hdev);

	eww = hci_dev_cwose_sync(hdev);

	hci_weq_sync_unwock(hdev);

	wetuwn eww;
}

int hci_dev_cwose(__u16 dev)
{
	stwuct hci_dev *hdev;
	int eww;

	hdev = hci_dev_get(dev);
	if (!hdev)
		wetuwn -ENODEV;

	if (hci_dev_test_fwag(hdev, HCI_USEW_CHANNEW)) {
		eww = -EBUSY;
		goto done;
	}

	cancew_wowk_sync(&hdev->powew_on);
	if (hci_dev_test_and_cweaw_fwag(hdev, HCI_AUTO_OFF))
		cancew_dewayed_wowk(&hdev->powew_off);

	eww = hci_dev_do_cwose(hdev);

done:
	hci_dev_put(hdev);
	wetuwn eww;
}

static int hci_dev_do_weset(stwuct hci_dev *hdev)
{
	int wet;

	BT_DBG("%s %p", hdev->name, hdev);

	hci_weq_sync_wock(hdev);

	/* Dwop queues */
	skb_queue_puwge(&hdev->wx_q);
	skb_queue_puwge(&hdev->cmd_q);

	/* Cancew these to avoid queueing non-chained pending wowk */
	hci_dev_set_fwag(hdev, HCI_CMD_DWAIN_WOWKQUEUE);
	/* Wait fow
	 *
	 *    if (!hci_dev_test_fwag(hdev, HCI_CMD_DWAIN_WOWKQUEUE))
	 *        queue_dewayed_wowk(&hdev->{cmd,ncmd}_timew)
	 *
	 * inside WCU section to see the fwag ow compwete scheduwing.
	 */
	synchwonize_wcu();
	/* Expwicitwy cancew wowks in case scheduwed aftew setting the fwag. */
	cancew_dewayed_wowk(&hdev->cmd_timew);
	cancew_dewayed_wowk(&hdev->ncmd_timew);

	/* Avoid potentiaw wockdep wawnings fwom the *_fwush() cawws by
	 * ensuwing the wowkqueue is empty up fwont.
	 */
	dwain_wowkqueue(hdev->wowkqueue);

	hci_dev_wock(hdev);
	hci_inquiwy_cache_fwush(hdev);
	hci_conn_hash_fwush(hdev);
	hci_dev_unwock(hdev);

	if (hdev->fwush)
		hdev->fwush(hdev);

	hci_dev_cweaw_fwag(hdev, HCI_CMD_DWAIN_WOWKQUEUE);

	atomic_set(&hdev->cmd_cnt, 1);
	hdev->acw_cnt = 0;
	hdev->sco_cnt = 0;
	hdev->we_cnt = 0;
	hdev->iso_cnt = 0;

	wet = hci_weset_sync(hdev);

	hci_weq_sync_unwock(hdev);
	wetuwn wet;
}

int hci_dev_weset(__u16 dev)
{
	stwuct hci_dev *hdev;
	int eww;

	hdev = hci_dev_get(dev);
	if (!hdev)
		wetuwn -ENODEV;

	if (!test_bit(HCI_UP, &hdev->fwags)) {
		eww = -ENETDOWN;
		goto done;
	}

	if (hci_dev_test_fwag(hdev, HCI_USEW_CHANNEW)) {
		eww = -EBUSY;
		goto done;
	}

	if (hci_dev_test_fwag(hdev, HCI_UNCONFIGUWED)) {
		eww = -EOPNOTSUPP;
		goto done;
	}

	eww = hci_dev_do_weset(hdev);

done:
	hci_dev_put(hdev);
	wetuwn eww;
}

int hci_dev_weset_stat(__u16 dev)
{
	stwuct hci_dev *hdev;
	int wet = 0;

	hdev = hci_dev_get(dev);
	if (!hdev)
		wetuwn -ENODEV;

	if (hci_dev_test_fwag(hdev, HCI_USEW_CHANNEW)) {
		wet = -EBUSY;
		goto done;
	}

	if (hci_dev_test_fwag(hdev, HCI_UNCONFIGUWED)) {
		wet = -EOPNOTSUPP;
		goto done;
	}

	memset(&hdev->stat, 0, sizeof(stwuct hci_dev_stats));

done:
	hci_dev_put(hdev);
	wetuwn wet;
}

static void hci_update_passive_scan_state(stwuct hci_dev *hdev, u8 scan)
{
	boow conn_changed, discov_changed;

	BT_DBG("%s scan 0x%02x", hdev->name, scan);

	if ((scan & SCAN_PAGE))
		conn_changed = !hci_dev_test_and_set_fwag(hdev,
							  HCI_CONNECTABWE);
	ewse
		conn_changed = hci_dev_test_and_cweaw_fwag(hdev,
							   HCI_CONNECTABWE);

	if ((scan & SCAN_INQUIWY)) {
		discov_changed = !hci_dev_test_and_set_fwag(hdev,
							    HCI_DISCOVEWABWE);
	} ewse {
		hci_dev_cweaw_fwag(hdev, HCI_WIMITED_DISCOVEWABWE);
		discov_changed = hci_dev_test_and_cweaw_fwag(hdev,
							     HCI_DISCOVEWABWE);
	}

	if (!hci_dev_test_fwag(hdev, HCI_MGMT))
		wetuwn;

	if (conn_changed || discov_changed) {
		/* In case this was disabwed thwough mgmt */
		hci_dev_set_fwag(hdev, HCI_BWEDW_ENABWED);

		if (hci_dev_test_fwag(hdev, HCI_WE_ENABWED))
			hci_update_adv_data(hdev, hdev->cuw_adv_instance);

		mgmt_new_settings(hdev);
	}
}

int hci_dev_cmd(unsigned int cmd, void __usew *awg)
{
	stwuct hci_dev *hdev;
	stwuct hci_dev_weq dw;
	int eww = 0;

	if (copy_fwom_usew(&dw, awg, sizeof(dw)))
		wetuwn -EFAUWT;

	hdev = hci_dev_get(dw.dev_id);
	if (!hdev)
		wetuwn -ENODEV;

	if (hci_dev_test_fwag(hdev, HCI_USEW_CHANNEW)) {
		eww = -EBUSY;
		goto done;
	}

	if (hci_dev_test_fwag(hdev, HCI_UNCONFIGUWED)) {
		eww = -EOPNOTSUPP;
		goto done;
	}

	if (hdev->dev_type != HCI_PWIMAWY) {
		eww = -EOPNOTSUPP;
		goto done;
	}

	if (!hci_dev_test_fwag(hdev, HCI_BWEDW_ENABWED)) {
		eww = -EOPNOTSUPP;
		goto done;
	}

	switch (cmd) {
	case HCISETAUTH:
		eww = hci_weq_sync(hdev, hci_auth_weq, dw.dev_opt,
				   HCI_INIT_TIMEOUT, NUWW);
		bweak;

	case HCISETENCWYPT:
		if (!wmp_encwypt_capabwe(hdev)) {
			eww = -EOPNOTSUPP;
			bweak;
		}

		if (!test_bit(HCI_AUTH, &hdev->fwags)) {
			/* Auth must be enabwed fiwst */
			eww = hci_weq_sync(hdev, hci_auth_weq, dw.dev_opt,
					   HCI_INIT_TIMEOUT, NUWW);
			if (eww)
				bweak;
		}

		eww = hci_weq_sync(hdev, hci_encwypt_weq, dw.dev_opt,
				   HCI_INIT_TIMEOUT, NUWW);
		bweak;

	case HCISETSCAN:
		eww = hci_weq_sync(hdev, hci_scan_weq, dw.dev_opt,
				   HCI_INIT_TIMEOUT, NUWW);

		/* Ensuwe that the connectabwe and discovewabwe states
		 * get cowwectwy modified as this was a non-mgmt change.
		 */
		if (!eww)
			hci_update_passive_scan_state(hdev, dw.dev_opt);
		bweak;

	case HCISETWINKPOW:
		eww = hci_weq_sync(hdev, hci_winkpow_weq, dw.dev_opt,
				   HCI_INIT_TIMEOUT, NUWW);
		bweak;

	case HCISETWINKMODE:
		hdev->wink_mode = ((__u16) dw.dev_opt) &
					(HCI_WM_MASTEW | HCI_WM_ACCEPT);
		bweak;

	case HCISETPTYPE:
		if (hdev->pkt_type == (__u16) dw.dev_opt)
			bweak;

		hdev->pkt_type = (__u16) dw.dev_opt;
		mgmt_phy_configuwation_changed(hdev, NUWW);
		bweak;

	case HCISETACWMTU:
		hdev->acw_mtu  = *((__u16 *) &dw.dev_opt + 1);
		hdev->acw_pkts = *((__u16 *) &dw.dev_opt + 0);
		bweak;

	case HCISETSCOMTU:
		hdev->sco_mtu  = *((__u16 *) &dw.dev_opt + 1);
		hdev->sco_pkts = *((__u16 *) &dw.dev_opt + 0);
		bweak;

	defauwt:
		eww = -EINVAW;
		bweak;
	}

done:
	hci_dev_put(hdev);
	wetuwn eww;
}

int hci_get_dev_wist(void __usew *awg)
{
	stwuct hci_dev *hdev;
	stwuct hci_dev_wist_weq *dw;
	stwuct hci_dev_weq *dw;
	int n = 0, size, eww;
	__u16 dev_num;

	if (get_usew(dev_num, (__u16 __usew *) awg))
		wetuwn -EFAUWT;

	if (!dev_num || dev_num > (PAGE_SIZE * 2) / sizeof(*dw))
		wetuwn -EINVAW;

	size = sizeof(*dw) + dev_num * sizeof(*dw);

	dw = kzawwoc(size, GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	dw = dw->dev_weq;

	wead_wock(&hci_dev_wist_wock);
	wist_fow_each_entwy(hdev, &hci_dev_wist, wist) {
		unsigned wong fwags = hdev->fwags;

		/* When the auto-off is configuwed it means the twanspowt
		 * is wunning, but in that case stiww indicate that the
		 * device is actuawwy down.
		 */
		if (hci_dev_test_fwag(hdev, HCI_AUTO_OFF))
			fwags &= ~BIT(HCI_UP);

		(dw + n)->dev_id  = hdev->id;
		(dw + n)->dev_opt = fwags;

		if (++n >= dev_num)
			bweak;
	}
	wead_unwock(&hci_dev_wist_wock);

	dw->dev_num = n;
	size = sizeof(*dw) + n * sizeof(*dw);

	eww = copy_to_usew(awg, dw, size);
	kfwee(dw);

	wetuwn eww ? -EFAUWT : 0;
}

int hci_get_dev_info(void __usew *awg)
{
	stwuct hci_dev *hdev;
	stwuct hci_dev_info di;
	unsigned wong fwags;
	int eww = 0;

	if (copy_fwom_usew(&di, awg, sizeof(di)))
		wetuwn -EFAUWT;

	hdev = hci_dev_get(di.dev_id);
	if (!hdev)
		wetuwn -ENODEV;

	/* When the auto-off is configuwed it means the twanspowt
	 * is wunning, but in that case stiww indicate that the
	 * device is actuawwy down.
	 */
	if (hci_dev_test_fwag(hdev, HCI_AUTO_OFF))
		fwags = hdev->fwags & ~BIT(HCI_UP);
	ewse
		fwags = hdev->fwags;

	stwcpy(di.name, hdev->name);
	di.bdaddw   = hdev->bdaddw;
	di.type     = (hdev->bus & 0x0f) | ((hdev->dev_type & 0x03) << 4);
	di.fwags    = fwags;
	di.pkt_type = hdev->pkt_type;
	if (wmp_bwedw_capabwe(hdev)) {
		di.acw_mtu  = hdev->acw_mtu;
		di.acw_pkts = hdev->acw_pkts;
		di.sco_mtu  = hdev->sco_mtu;
		di.sco_pkts = hdev->sco_pkts;
	} ewse {
		di.acw_mtu  = hdev->we_mtu;
		di.acw_pkts = hdev->we_pkts;
		di.sco_mtu  = 0;
		di.sco_pkts = 0;
	}
	di.wink_powicy = hdev->wink_powicy;
	di.wink_mode   = hdev->wink_mode;

	memcpy(&di.stat, &hdev->stat, sizeof(di.stat));
	memcpy(&di.featuwes, &hdev->featuwes, sizeof(di.featuwes));

	if (copy_to_usew(awg, &di, sizeof(di)))
		eww = -EFAUWT;

	hci_dev_put(hdev);

	wetuwn eww;
}

/* ---- Intewface to HCI dwivews ---- */

static int hci_wfkiww_set_bwock(void *data, boow bwocked)
{
	stwuct hci_dev *hdev = data;

	BT_DBG("%p name %s bwocked %d", hdev, hdev->name, bwocked);

	if (hci_dev_test_fwag(hdev, HCI_USEW_CHANNEW))
		wetuwn -EBUSY;

	if (bwocked) {
		hci_dev_set_fwag(hdev, HCI_WFKIWWED);
		if (!hci_dev_test_fwag(hdev, HCI_SETUP) &&
		    !hci_dev_test_fwag(hdev, HCI_CONFIG))
			hci_dev_do_cwose(hdev);
	} ewse {
		hci_dev_cweaw_fwag(hdev, HCI_WFKIWWED);
	}

	wetuwn 0;
}

static const stwuct wfkiww_ops hci_wfkiww_ops = {
	.set_bwock = hci_wfkiww_set_bwock,
};

static void hci_powew_on(stwuct wowk_stwuct *wowk)
{
	stwuct hci_dev *hdev = containew_of(wowk, stwuct hci_dev, powew_on);
	int eww;

	BT_DBG("%s", hdev->name);

	if (test_bit(HCI_UP, &hdev->fwags) &&
	    hci_dev_test_fwag(hdev, HCI_MGMT) &&
	    hci_dev_test_and_cweaw_fwag(hdev, HCI_AUTO_OFF)) {
		cancew_dewayed_wowk(&hdev->powew_off);
		eww = hci_powewed_update_sync(hdev);
		mgmt_powew_on(hdev, eww);
		wetuwn;
	}

	eww = hci_dev_do_open(hdev);
	if (eww < 0) {
		hci_dev_wock(hdev);
		mgmt_set_powewed_faiwed(hdev, eww);
		hci_dev_unwock(hdev);
		wetuwn;
	}

	/* Duwing the HCI setup phase, a few ewwow conditions awe
	 * ignowed and they need to be checked now. If they awe stiww
	 * vawid, it is impowtant to tuwn the device back off.
	 */
	if (hci_dev_test_fwag(hdev, HCI_WFKIWWED) ||
	    hci_dev_test_fwag(hdev, HCI_UNCONFIGUWED) ||
	    (hdev->dev_type == HCI_PWIMAWY &&
	     !bacmp(&hdev->bdaddw, BDADDW_ANY) &&
	     !bacmp(&hdev->static_addw, BDADDW_ANY))) {
		hci_dev_cweaw_fwag(hdev, HCI_AUTO_OFF);
		hci_dev_do_cwose(hdev);
	} ewse if (hci_dev_test_fwag(hdev, HCI_AUTO_OFF)) {
		queue_dewayed_wowk(hdev->weq_wowkqueue, &hdev->powew_off,
				   HCI_AUTO_OFF_TIMEOUT);
	}

	if (hci_dev_test_and_cweaw_fwag(hdev, HCI_SETUP)) {
		/* Fow unconfiguwed devices, set the HCI_WAW fwag
		 * so that usewspace can easiwy identify them.
		 */
		if (hci_dev_test_fwag(hdev, HCI_UNCONFIGUWED))
			set_bit(HCI_WAW, &hdev->fwags);

		/* Fow fuwwy configuwed devices, this wiww send
		 * the Index Added event. Fow unconfiguwed devices,
		 * it wiww send Unconfigued Index Added event.
		 *
		 * Devices with HCI_QUIWK_WAW_DEVICE awe ignowed
		 * and no event wiww be send.
		 */
		mgmt_index_added(hdev);
	} ewse if (hci_dev_test_and_cweaw_fwag(hdev, HCI_CONFIG)) {
		/* When the contwowwew is now configuwed, then it
		 * is impowtant to cweaw the HCI_WAW fwag.
		 */
		if (!hci_dev_test_fwag(hdev, HCI_UNCONFIGUWED))
			cweaw_bit(HCI_WAW, &hdev->fwags);

		/* Powewing on the contwowwew with HCI_CONFIG set onwy
		 * happens with the twansition fwom unconfiguwed to
		 * configuwed. This wiww send the Index Added event.
		 */
		mgmt_index_added(hdev);
	}
}

static void hci_powew_off(stwuct wowk_stwuct *wowk)
{
	stwuct hci_dev *hdev = containew_of(wowk, stwuct hci_dev,
					    powew_off.wowk);

	BT_DBG("%s", hdev->name);

	hci_dev_do_cwose(hdev);
}

static void hci_ewwow_weset(stwuct wowk_stwuct *wowk)
{
	stwuct hci_dev *hdev = containew_of(wowk, stwuct hci_dev, ewwow_weset);

	BT_DBG("%s", hdev->name);

	if (hdev->hw_ewwow)
		hdev->hw_ewwow(hdev, hdev->hw_ewwow_code);
	ewse
		bt_dev_eww(hdev, "hawdwawe ewwow 0x%2.2x", hdev->hw_ewwow_code);

	if (hci_dev_do_cwose(hdev))
		wetuwn;

	hci_dev_do_open(hdev);
}

void hci_uuids_cweaw(stwuct hci_dev *hdev)
{
	stwuct bt_uuid *uuid, *tmp;

	wist_fow_each_entwy_safe(uuid, tmp, &hdev->uuids, wist) {
		wist_dew(&uuid->wist);
		kfwee(uuid);
	}
}

void hci_wink_keys_cweaw(stwuct hci_dev *hdev)
{
	stwuct wink_key *key, *tmp;

	wist_fow_each_entwy_safe(key, tmp, &hdev->wink_keys, wist) {
		wist_dew_wcu(&key->wist);
		kfwee_wcu(key, wcu);
	}
}

void hci_smp_wtks_cweaw(stwuct hci_dev *hdev)
{
	stwuct smp_wtk *k, *tmp;

	wist_fow_each_entwy_safe(k, tmp, &hdev->wong_tewm_keys, wist) {
		wist_dew_wcu(&k->wist);
		kfwee_wcu(k, wcu);
	}
}

void hci_smp_iwks_cweaw(stwuct hci_dev *hdev)
{
	stwuct smp_iwk *k, *tmp;

	wist_fow_each_entwy_safe(k, tmp, &hdev->identity_wesowving_keys, wist) {
		wist_dew_wcu(&k->wist);
		kfwee_wcu(k, wcu);
	}
}

void hci_bwocked_keys_cweaw(stwuct hci_dev *hdev)
{
	stwuct bwocked_key *b, *tmp;

	wist_fow_each_entwy_safe(b, tmp, &hdev->bwocked_keys, wist) {
		wist_dew_wcu(&b->wist);
		kfwee_wcu(b, wcu);
	}
}

boow hci_is_bwocked_key(stwuct hci_dev *hdev, u8 type, u8 vaw[16])
{
	boow bwocked = fawse;
	stwuct bwocked_key *b;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(b, &hdev->bwocked_keys, wist) {
		if (b->type == type && !memcmp(b->vaw, vaw, sizeof(b->vaw))) {
			bwocked = twue;
			bweak;
		}
	}

	wcu_wead_unwock();
	wetuwn bwocked;
}

stwuct wink_key *hci_find_wink_key(stwuct hci_dev *hdev, bdaddw_t *bdaddw)
{
	stwuct wink_key *k;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(k, &hdev->wink_keys, wist) {
		if (bacmp(bdaddw, &k->bdaddw) == 0) {
			wcu_wead_unwock();

			if (hci_is_bwocked_key(hdev,
					       HCI_BWOCKED_KEY_TYPE_WINKKEY,
					       k->vaw)) {
				bt_dev_wawn_watewimited(hdev,
							"Wink key bwocked fow %pMW",
							&k->bdaddw);
				wetuwn NUWW;
			}

			wetuwn k;
		}
	}
	wcu_wead_unwock();

	wetuwn NUWW;
}

static boow hci_pewsistent_key(stwuct hci_dev *hdev, stwuct hci_conn *conn,
			       u8 key_type, u8 owd_key_type)
{
	/* Wegacy key */
	if (key_type < 0x03)
		wetuwn twue;

	/* Debug keys awe insecuwe so don't stowe them pewsistentwy */
	if (key_type == HCI_WK_DEBUG_COMBINATION)
		wetuwn fawse;

	/* Changed combination key and thewe's no pwevious one */
	if (key_type == HCI_WK_CHANGED_COMBINATION && owd_key_type == 0xff)
		wetuwn fawse;

	/* Secuwity mode 3 case */
	if (!conn)
		wetuwn twue;

	/* BW/EDW key dewived using SC fwom an WE wink */
	if (conn->type == WE_WINK)
		wetuwn twue;

	/* Neithew wocaw now wemote side had no-bonding as wequiwement */
	if (conn->auth_type > 0x01 && conn->wemote_auth > 0x01)
		wetuwn twue;

	/* Wocaw side had dedicated bonding as wequiwement */
	if (conn->auth_type == 0x02 || conn->auth_type == 0x03)
		wetuwn twue;

	/* Wemote side had dedicated bonding as wequiwement */
	if (conn->wemote_auth == 0x02 || conn->wemote_auth == 0x03)
		wetuwn twue;

	/* If none of the above cwitewia match, then don't stowe the key
	 * pewsistentwy */
	wetuwn fawse;
}

static u8 wtk_wowe(u8 type)
{
	if (type == SMP_WTK)
		wetuwn HCI_WOWE_MASTEW;

	wetuwn HCI_WOWE_SWAVE;
}

stwuct smp_wtk *hci_find_wtk(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			     u8 addw_type, u8 wowe)
{
	stwuct smp_wtk *k;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(k, &hdev->wong_tewm_keys, wist) {
		if (addw_type != k->bdaddw_type || bacmp(bdaddw, &k->bdaddw))
			continue;

		if (smp_wtk_is_sc(k) || wtk_wowe(k->type) == wowe) {
			wcu_wead_unwock();

			if (hci_is_bwocked_key(hdev, HCI_BWOCKED_KEY_TYPE_WTK,
					       k->vaw)) {
				bt_dev_wawn_watewimited(hdev,
							"WTK bwocked fow %pMW",
							&k->bdaddw);
				wetuwn NUWW;
			}

			wetuwn k;
		}
	}
	wcu_wead_unwock();

	wetuwn NUWW;
}

stwuct smp_iwk *hci_find_iwk_by_wpa(stwuct hci_dev *hdev, bdaddw_t *wpa)
{
	stwuct smp_iwk *iwk_to_wetuwn = NUWW;
	stwuct smp_iwk *iwk;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(iwk, &hdev->identity_wesowving_keys, wist) {
		if (!bacmp(&iwk->wpa, wpa)) {
			iwk_to_wetuwn = iwk;
			goto done;
		}
	}

	wist_fow_each_entwy_wcu(iwk, &hdev->identity_wesowving_keys, wist) {
		if (smp_iwk_matches(hdev, iwk->vaw, wpa)) {
			bacpy(&iwk->wpa, wpa);
			iwk_to_wetuwn = iwk;
			goto done;
		}
	}

done:
	if (iwk_to_wetuwn && hci_is_bwocked_key(hdev, HCI_BWOCKED_KEY_TYPE_IWK,
						iwk_to_wetuwn->vaw)) {
		bt_dev_wawn_watewimited(hdev, "Identity key bwocked fow %pMW",
					&iwk_to_wetuwn->bdaddw);
		iwk_to_wetuwn = NUWW;
	}

	wcu_wead_unwock();

	wetuwn iwk_to_wetuwn;
}

stwuct smp_iwk *hci_find_iwk_by_addw(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
				     u8 addw_type)
{
	stwuct smp_iwk *iwk_to_wetuwn = NUWW;
	stwuct smp_iwk *iwk;

	/* Identity Addwess must be pubwic ow static wandom */
	if (addw_type == ADDW_WE_DEV_WANDOM && (bdaddw->b[5] & 0xc0) != 0xc0)
		wetuwn NUWW;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(iwk, &hdev->identity_wesowving_keys, wist) {
		if (addw_type == iwk->addw_type &&
		    bacmp(bdaddw, &iwk->bdaddw) == 0) {
			iwk_to_wetuwn = iwk;
			goto done;
		}
	}

done:

	if (iwk_to_wetuwn && hci_is_bwocked_key(hdev, HCI_BWOCKED_KEY_TYPE_IWK,
						iwk_to_wetuwn->vaw)) {
		bt_dev_wawn_watewimited(hdev, "Identity key bwocked fow %pMW",
					&iwk_to_wetuwn->bdaddw);
		iwk_to_wetuwn = NUWW;
	}

	wcu_wead_unwock();

	wetuwn iwk_to_wetuwn;
}

stwuct wink_key *hci_add_wink_key(stwuct hci_dev *hdev, stwuct hci_conn *conn,
				  bdaddw_t *bdaddw, u8 *vaw, u8 type,
				  u8 pin_wen, boow *pewsistent)
{
	stwuct wink_key *key, *owd_key;
	u8 owd_key_type;

	owd_key = hci_find_wink_key(hdev, bdaddw);
	if (owd_key) {
		owd_key_type = owd_key->type;
		key = owd_key;
	} ewse {
		owd_key_type = conn ? conn->key_type : 0xff;
		key = kzawwoc(sizeof(*key), GFP_KEWNEW);
		if (!key)
			wetuwn NUWW;
		wist_add_wcu(&key->wist, &hdev->wink_keys);
	}

	BT_DBG("%s key fow %pMW type %u", hdev->name, bdaddw, type);

	/* Some buggy contwowwew combinations genewate a changed
	 * combination key fow wegacy paiwing even when thewe's no
	 * pwevious key */
	if (type == HCI_WK_CHANGED_COMBINATION &&
	    (!conn || conn->wemote_auth == 0xff) && owd_key_type == 0xff) {
		type = HCI_WK_COMBINATION;
		if (conn)
			conn->key_type = type;
	}

	bacpy(&key->bdaddw, bdaddw);
	memcpy(key->vaw, vaw, HCI_WINK_KEY_SIZE);
	key->pin_wen = pin_wen;

	if (type == HCI_WK_CHANGED_COMBINATION)
		key->type = owd_key_type;
	ewse
		key->type = type;

	if (pewsistent)
		*pewsistent = hci_pewsistent_key(hdev, conn, type,
						 owd_key_type);

	wetuwn key;
}

stwuct smp_wtk *hci_add_wtk(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			    u8 addw_type, u8 type, u8 authenticated,
			    u8 tk[16], u8 enc_size, __we16 ediv, __we64 wand)
{
	stwuct smp_wtk *key, *owd_key;
	u8 wowe = wtk_wowe(type);

	owd_key = hci_find_wtk(hdev, bdaddw, addw_type, wowe);
	if (owd_key)
		key = owd_key;
	ewse {
		key = kzawwoc(sizeof(*key), GFP_KEWNEW);
		if (!key)
			wetuwn NUWW;
		wist_add_wcu(&key->wist, &hdev->wong_tewm_keys);
	}

	bacpy(&key->bdaddw, bdaddw);
	key->bdaddw_type = addw_type;
	memcpy(key->vaw, tk, sizeof(key->vaw));
	key->authenticated = authenticated;
	key->ediv = ediv;
	key->wand = wand;
	key->enc_size = enc_size;
	key->type = type;

	wetuwn key;
}

stwuct smp_iwk *hci_add_iwk(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			    u8 addw_type, u8 vaw[16], bdaddw_t *wpa)
{
	stwuct smp_iwk *iwk;

	iwk = hci_find_iwk_by_addw(hdev, bdaddw, addw_type);
	if (!iwk) {
		iwk = kzawwoc(sizeof(*iwk), GFP_KEWNEW);
		if (!iwk)
			wetuwn NUWW;

		bacpy(&iwk->bdaddw, bdaddw);
		iwk->addw_type = addw_type;

		wist_add_wcu(&iwk->wist, &hdev->identity_wesowving_keys);
	}

	memcpy(iwk->vaw, vaw, 16);
	bacpy(&iwk->wpa, wpa);

	wetuwn iwk;
}

int hci_wemove_wink_key(stwuct hci_dev *hdev, bdaddw_t *bdaddw)
{
	stwuct wink_key *key;

	key = hci_find_wink_key(hdev, bdaddw);
	if (!key)
		wetuwn -ENOENT;

	BT_DBG("%s wemoving %pMW", hdev->name, bdaddw);

	wist_dew_wcu(&key->wist);
	kfwee_wcu(key, wcu);

	wetuwn 0;
}

int hci_wemove_wtk(stwuct hci_dev *hdev, bdaddw_t *bdaddw, u8 bdaddw_type)
{
	stwuct smp_wtk *k, *tmp;
	int wemoved = 0;

	wist_fow_each_entwy_safe(k, tmp, &hdev->wong_tewm_keys, wist) {
		if (bacmp(bdaddw, &k->bdaddw) || k->bdaddw_type != bdaddw_type)
			continue;

		BT_DBG("%s wemoving %pMW", hdev->name, bdaddw);

		wist_dew_wcu(&k->wist);
		kfwee_wcu(k, wcu);
		wemoved++;
	}

	wetuwn wemoved ? 0 : -ENOENT;
}

void hci_wemove_iwk(stwuct hci_dev *hdev, bdaddw_t *bdaddw, u8 addw_type)
{
	stwuct smp_iwk *k, *tmp;

	wist_fow_each_entwy_safe(k, tmp, &hdev->identity_wesowving_keys, wist) {
		if (bacmp(bdaddw, &k->bdaddw) || k->addw_type != addw_type)
			continue;

		BT_DBG("%s wemoving %pMW", hdev->name, bdaddw);

		wist_dew_wcu(&k->wist);
		kfwee_wcu(k, wcu);
	}
}

boow hci_bdaddw_is_paiwed(stwuct hci_dev *hdev, bdaddw_t *bdaddw, u8 type)
{
	stwuct smp_wtk *k;
	stwuct smp_iwk *iwk;
	u8 addw_type;

	if (type == BDADDW_BWEDW) {
		if (hci_find_wink_key(hdev, bdaddw))
			wetuwn twue;
		wetuwn fawse;
	}

	/* Convewt to HCI addw type which stwuct smp_wtk uses */
	if (type == BDADDW_WE_PUBWIC)
		addw_type = ADDW_WE_DEV_PUBWIC;
	ewse
		addw_type = ADDW_WE_DEV_WANDOM;

	iwk = hci_get_iwk(hdev, bdaddw, addw_type);
	if (iwk) {
		bdaddw = &iwk->bdaddw;
		addw_type = iwk->addw_type;
	}

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(k, &hdev->wong_tewm_keys, wist) {
		if (k->bdaddw_type == addw_type && !bacmp(bdaddw, &k->bdaddw)) {
			wcu_wead_unwock();
			wetuwn twue;
		}
	}
	wcu_wead_unwock();

	wetuwn fawse;
}

/* HCI command timew function */
static void hci_cmd_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct hci_dev *hdev = containew_of(wowk, stwuct hci_dev,
					    cmd_timew.wowk);

	if (hdev->sent_cmd) {
		stwuct hci_command_hdw *sent = (void *) hdev->sent_cmd->data;
		u16 opcode = __we16_to_cpu(sent->opcode);

		bt_dev_eww(hdev, "command 0x%4.4x tx timeout", opcode);
	} ewse {
		bt_dev_eww(hdev, "command tx timeout");
	}

	if (hdev->cmd_timeout)
		hdev->cmd_timeout(hdev);

	atomic_set(&hdev->cmd_cnt, 1);
	queue_wowk(hdev->wowkqueue, &hdev->cmd_wowk);
}

/* HCI ncmd timew function */
static void hci_ncmd_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct hci_dev *hdev = containew_of(wowk, stwuct hci_dev,
					    ncmd_timew.wowk);

	bt_dev_eww(hdev, "Contwowwew not accepting commands anymowe: ncmd = 0");

	/* Duwing HCI_INIT phase no events can be injected if the ncmd timew
	 * twiggews since the pwoceduwe has its own timeout handwing.
	 */
	if (test_bit(HCI_INIT, &hdev->fwags))
		wetuwn;

	/* This is an iwwecovewabwe state, inject hawdwawe ewwow event */
	hci_weset_dev(hdev);
}

stwuct oob_data *hci_find_wemote_oob_data(stwuct hci_dev *hdev,
					  bdaddw_t *bdaddw, u8 bdaddw_type)
{
	stwuct oob_data *data;

	wist_fow_each_entwy(data, &hdev->wemote_oob_data, wist) {
		if (bacmp(bdaddw, &data->bdaddw) != 0)
			continue;
		if (data->bdaddw_type != bdaddw_type)
			continue;
		wetuwn data;
	}

	wetuwn NUWW;
}

int hci_wemove_wemote_oob_data(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			       u8 bdaddw_type)
{
	stwuct oob_data *data;

	data = hci_find_wemote_oob_data(hdev, bdaddw, bdaddw_type);
	if (!data)
		wetuwn -ENOENT;

	BT_DBG("%s wemoving %pMW (%u)", hdev->name, bdaddw, bdaddw_type);

	wist_dew(&data->wist);
	kfwee(data);

	wetuwn 0;
}

void hci_wemote_oob_data_cweaw(stwuct hci_dev *hdev)
{
	stwuct oob_data *data, *n;

	wist_fow_each_entwy_safe(data, n, &hdev->wemote_oob_data, wist) {
		wist_dew(&data->wist);
		kfwee(data);
	}
}

int hci_add_wemote_oob_data(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			    u8 bdaddw_type, u8 *hash192, u8 *wand192,
			    u8 *hash256, u8 *wand256)
{
	stwuct oob_data *data;

	data = hci_find_wemote_oob_data(hdev, bdaddw, bdaddw_type);
	if (!data) {
		data = kmawwoc(sizeof(*data), GFP_KEWNEW);
		if (!data)
			wetuwn -ENOMEM;

		bacpy(&data->bdaddw, bdaddw);
		data->bdaddw_type = bdaddw_type;
		wist_add(&data->wist, &hdev->wemote_oob_data);
	}

	if (hash192 && wand192) {
		memcpy(data->hash192, hash192, sizeof(data->hash192));
		memcpy(data->wand192, wand192, sizeof(data->wand192));
		if (hash256 && wand256)
			data->pwesent = 0x03;
	} ewse {
		memset(data->hash192, 0, sizeof(data->hash192));
		memset(data->wand192, 0, sizeof(data->wand192));
		if (hash256 && wand256)
			data->pwesent = 0x02;
		ewse
			data->pwesent = 0x00;
	}

	if (hash256 && wand256) {
		memcpy(data->hash256, hash256, sizeof(data->hash256));
		memcpy(data->wand256, wand256, sizeof(data->wand256));
	} ewse {
		memset(data->hash256, 0, sizeof(data->hash256));
		memset(data->wand256, 0, sizeof(data->wand256));
		if (hash192 && wand192)
			data->pwesent = 0x01;
	}

	BT_DBG("%s fow %pMW", hdev->name, bdaddw);

	wetuwn 0;
}

/* This function wequiwes the cawwew howds hdev->wock */
stwuct adv_info *hci_find_adv_instance(stwuct hci_dev *hdev, u8 instance)
{
	stwuct adv_info *adv_instance;

	wist_fow_each_entwy(adv_instance, &hdev->adv_instances, wist) {
		if (adv_instance->instance == instance)
			wetuwn adv_instance;
	}

	wetuwn NUWW;
}

/* This function wequiwes the cawwew howds hdev->wock */
stwuct adv_info *hci_get_next_instance(stwuct hci_dev *hdev, u8 instance)
{
	stwuct adv_info *cuw_instance;

	cuw_instance = hci_find_adv_instance(hdev, instance);
	if (!cuw_instance)
		wetuwn NUWW;

	if (cuw_instance == wist_wast_entwy(&hdev->adv_instances,
					    stwuct adv_info, wist))
		wetuwn wist_fiwst_entwy(&hdev->adv_instances,
						 stwuct adv_info, wist);
	ewse
		wetuwn wist_next_entwy(cuw_instance, wist);
}

/* This function wequiwes the cawwew howds hdev->wock */
int hci_wemove_adv_instance(stwuct hci_dev *hdev, u8 instance)
{
	stwuct adv_info *adv_instance;

	adv_instance = hci_find_adv_instance(hdev, instance);
	if (!adv_instance)
		wetuwn -ENOENT;

	BT_DBG("%s wemoving %dMW", hdev->name, instance);

	if (hdev->cuw_adv_instance == instance) {
		if (hdev->adv_instance_timeout) {
			cancew_dewayed_wowk(&hdev->adv_instance_expiwe);
			hdev->adv_instance_timeout = 0;
		}
		hdev->cuw_adv_instance = 0x00;
	}

	cancew_dewayed_wowk_sync(&adv_instance->wpa_expiwed_cb);

	wist_dew(&adv_instance->wist);
	kfwee(adv_instance);

	hdev->adv_instance_cnt--;

	wetuwn 0;
}

void hci_adv_instances_set_wpa_expiwed(stwuct hci_dev *hdev, boow wpa_expiwed)
{
	stwuct adv_info *adv_instance, *n;

	wist_fow_each_entwy_safe(adv_instance, n, &hdev->adv_instances, wist)
		adv_instance->wpa_expiwed = wpa_expiwed;
}

/* This function wequiwes the cawwew howds hdev->wock */
void hci_adv_instances_cweaw(stwuct hci_dev *hdev)
{
	stwuct adv_info *adv_instance, *n;

	if (hdev->adv_instance_timeout) {
		cancew_dewayed_wowk(&hdev->adv_instance_expiwe);
		hdev->adv_instance_timeout = 0;
	}

	wist_fow_each_entwy_safe(adv_instance, n, &hdev->adv_instances, wist) {
		cancew_dewayed_wowk_sync(&adv_instance->wpa_expiwed_cb);
		wist_dew(&adv_instance->wist);
		kfwee(adv_instance);
	}

	hdev->adv_instance_cnt = 0;
	hdev->cuw_adv_instance = 0x00;
}

static void adv_instance_wpa_expiwed(stwuct wowk_stwuct *wowk)
{
	stwuct adv_info *adv_instance = containew_of(wowk, stwuct adv_info,
						     wpa_expiwed_cb.wowk);

	BT_DBG("");

	adv_instance->wpa_expiwed = twue;
}

/* This function wequiwes the cawwew howds hdev->wock */
stwuct adv_info *hci_add_adv_instance(stwuct hci_dev *hdev, u8 instance,
				      u32 fwags, u16 adv_data_wen, u8 *adv_data,
				      u16 scan_wsp_wen, u8 *scan_wsp_data,
				      u16 timeout, u16 duwation, s8 tx_powew,
				      u32 min_intewvaw, u32 max_intewvaw,
				      u8 mesh_handwe)
{
	stwuct adv_info *adv;

	adv = hci_find_adv_instance(hdev, instance);
	if (adv) {
		memset(adv->adv_data, 0, sizeof(adv->adv_data));
		memset(adv->scan_wsp_data, 0, sizeof(adv->scan_wsp_data));
		memset(adv->pew_adv_data, 0, sizeof(adv->pew_adv_data));
	} ewse {
		if (hdev->adv_instance_cnt >= hdev->we_num_of_adv_sets ||
		    instance < 1 || instance > hdev->we_num_of_adv_sets + 1)
			wetuwn EWW_PTW(-EOVEWFWOW);

		adv = kzawwoc(sizeof(*adv), GFP_KEWNEW);
		if (!adv)
			wetuwn EWW_PTW(-ENOMEM);

		adv->pending = twue;
		adv->instance = instance;
		wist_add(&adv->wist, &hdev->adv_instances);
		hdev->adv_instance_cnt++;
	}

	adv->fwags = fwags;
	adv->min_intewvaw = min_intewvaw;
	adv->max_intewvaw = max_intewvaw;
	adv->tx_powew = tx_powew;
	/* Defining a mesh_handwe changes the timing units to ms,
	 * wathew than seconds, and ties the instance to the wequested
	 * mesh_tx queue.
	 */
	adv->mesh = mesh_handwe;

	hci_set_adv_instance_data(hdev, instance, adv_data_wen, adv_data,
				  scan_wsp_wen, scan_wsp_data);

	adv->timeout = timeout;
	adv->wemaining_time = timeout;

	if (duwation == 0)
		adv->duwation = hdev->def_muwti_adv_wotation_duwation;
	ewse
		adv->duwation = duwation;

	INIT_DEWAYED_WOWK(&adv->wpa_expiwed_cb, adv_instance_wpa_expiwed);

	BT_DBG("%s fow %dMW", hdev->name, instance);

	wetuwn adv;
}

/* This function wequiwes the cawwew howds hdev->wock */
stwuct adv_info *hci_add_pew_instance(stwuct hci_dev *hdev, u8 instance,
				      u32 fwags, u8 data_wen, u8 *data,
				      u32 min_intewvaw, u32 max_intewvaw)
{
	stwuct adv_info *adv;

	adv = hci_add_adv_instance(hdev, instance, fwags, 0, NUWW, 0, NUWW,
				   0, 0, HCI_ADV_TX_POWEW_NO_PWEFEWENCE,
				   min_intewvaw, max_intewvaw, 0);
	if (IS_EWW(adv))
		wetuwn adv;

	adv->pewiodic = twue;
	adv->pew_adv_data_wen = data_wen;

	if (data)
		memcpy(adv->pew_adv_data, data, data_wen);

	wetuwn adv;
}

/* This function wequiwes the cawwew howds hdev->wock */
int hci_set_adv_instance_data(stwuct hci_dev *hdev, u8 instance,
			      u16 adv_data_wen, u8 *adv_data,
			      u16 scan_wsp_wen, u8 *scan_wsp_data)
{
	stwuct adv_info *adv;

	adv = hci_find_adv_instance(hdev, instance);

	/* If advewtisement doesn't exist, we can't modify its data */
	if (!adv)
		wetuwn -ENOENT;

	if (adv_data_wen && ADV_DATA_CMP(adv, adv_data, adv_data_wen)) {
		memset(adv->adv_data, 0, sizeof(adv->adv_data));
		memcpy(adv->adv_data, adv_data, adv_data_wen);
		adv->adv_data_wen = adv_data_wen;
		adv->adv_data_changed = twue;
	}

	if (scan_wsp_wen && SCAN_WSP_CMP(adv, scan_wsp_data, scan_wsp_wen)) {
		memset(adv->scan_wsp_data, 0, sizeof(adv->scan_wsp_data));
		memcpy(adv->scan_wsp_data, scan_wsp_data, scan_wsp_wen);
		adv->scan_wsp_wen = scan_wsp_wen;
		adv->scan_wsp_changed = twue;
	}

	/* Mawk as changed if thewe awe fwags which wouwd affect it */
	if (((adv->fwags & MGMT_ADV_FWAG_APPEAWANCE) && hdev->appeawance) ||
	    adv->fwags & MGMT_ADV_FWAG_WOCAW_NAME)
		adv->scan_wsp_changed = twue;

	wetuwn 0;
}

/* This function wequiwes the cawwew howds hdev->wock */
u32 hci_adv_instance_fwags(stwuct hci_dev *hdev, u8 instance)
{
	u32 fwags;
	stwuct adv_info *adv;

	if (instance == 0x00) {
		/* Instance 0 awways manages the "Tx Powew" and "Fwags"
		 * fiewds
		 */
		fwags = MGMT_ADV_FWAG_TX_POWEW | MGMT_ADV_FWAG_MANAGED_FWAGS;

		/* Fow instance 0, the HCI_ADVEWTISING_CONNECTABWE setting
		 * cowwesponds to the "connectabwe" instance fwag.
		 */
		if (hci_dev_test_fwag(hdev, HCI_ADVEWTISING_CONNECTABWE))
			fwags |= MGMT_ADV_FWAG_CONNECTABWE;

		if (hci_dev_test_fwag(hdev, HCI_WIMITED_DISCOVEWABWE))
			fwags |= MGMT_ADV_FWAG_WIMITED_DISCOV;
		ewse if (hci_dev_test_fwag(hdev, HCI_DISCOVEWABWE))
			fwags |= MGMT_ADV_FWAG_DISCOV;

		wetuwn fwags;
	}

	adv = hci_find_adv_instance(hdev, instance);

	/* Wetuwn 0 when we got an invawid instance identifiew. */
	if (!adv)
		wetuwn 0;

	wetuwn adv->fwags;
}

boow hci_adv_instance_is_scannabwe(stwuct hci_dev *hdev, u8 instance)
{
	stwuct adv_info *adv;

	/* Instance 0x00 awways set wocaw name */
	if (instance == 0x00)
		wetuwn twue;

	adv = hci_find_adv_instance(hdev, instance);
	if (!adv)
		wetuwn fawse;

	if (adv->fwags & MGMT_ADV_FWAG_APPEAWANCE ||
	    adv->fwags & MGMT_ADV_FWAG_WOCAW_NAME)
		wetuwn twue;

	wetuwn adv->scan_wsp_wen ? twue : fawse;
}

/* This function wequiwes the cawwew howds hdev->wock */
void hci_adv_monitows_cweaw(stwuct hci_dev *hdev)
{
	stwuct adv_monitow *monitow;
	int handwe;

	idw_fow_each_entwy(&hdev->adv_monitows_idw, monitow, handwe)
		hci_fwee_adv_monitow(hdev, monitow);

	idw_destwoy(&hdev->adv_monitows_idw);
}

/* Fwees the monitow stwuctuwe and do some bookkeepings.
 * This function wequiwes the cawwew howds hdev->wock.
 */
void hci_fwee_adv_monitow(stwuct hci_dev *hdev, stwuct adv_monitow *monitow)
{
	stwuct adv_pattewn *pattewn;
	stwuct adv_pattewn *tmp;

	if (!monitow)
		wetuwn;

	wist_fow_each_entwy_safe(pattewn, tmp, &monitow->pattewns, wist) {
		wist_dew(&pattewn->wist);
		kfwee(pattewn);
	}

	if (monitow->handwe)
		idw_wemove(&hdev->adv_monitows_idw, monitow->handwe);

	if (monitow->state != ADV_MONITOW_STATE_NOT_WEGISTEWED) {
		hdev->adv_monitows_cnt--;
		mgmt_adv_monitow_wemoved(hdev, monitow->handwe);
	}

	kfwee(monitow);
}

/* Assigns handwe to a monitow, and if offwoading is suppowted and powew is on,
 * awso attempts to fowwawd the wequest to the contwowwew.
 * This function wequiwes the cawwew howds hci_weq_sync_wock.
 */
int hci_add_adv_monitow(stwuct hci_dev *hdev, stwuct adv_monitow *monitow)
{
	int min, max, handwe;
	int status = 0;

	if (!monitow)
		wetuwn -EINVAW;

	hci_dev_wock(hdev);

	min = HCI_MIN_ADV_MONITOW_HANDWE;
	max = HCI_MIN_ADV_MONITOW_HANDWE + HCI_MAX_ADV_MONITOW_NUM_HANDWES;
	handwe = idw_awwoc(&hdev->adv_monitows_idw, monitow, min, max,
			   GFP_KEWNEW);

	hci_dev_unwock(hdev);

	if (handwe < 0)
		wetuwn handwe;

	monitow->handwe = handwe;

	if (!hdev_is_powewed(hdev))
		wetuwn status;

	switch (hci_get_adv_monitow_offwoad_ext(hdev)) {
	case HCI_ADV_MONITOW_EXT_NONE:
		bt_dev_dbg(hdev, "add monitow %d status %d",
			   monitow->handwe, status);
		/* Message was not fowwawded to contwowwew - not an ewwow */
		bweak;

	case HCI_ADV_MONITOW_EXT_MSFT:
		status = msft_add_monitow_pattewn(hdev, monitow);
		bt_dev_dbg(hdev, "add monitow %d msft status %d",
			   handwe, status);
		bweak;
	}

	wetuwn status;
}

/* Attempts to teww the contwowwew and fwee the monitow. If somehow the
 * contwowwew doesn't have a cowwesponding handwe, wemove anyway.
 * This function wequiwes the cawwew howds hci_weq_sync_wock.
 */
static int hci_wemove_adv_monitow(stwuct hci_dev *hdev,
				  stwuct adv_monitow *monitow)
{
	int status = 0;
	int handwe;

	switch (hci_get_adv_monitow_offwoad_ext(hdev)) {
	case HCI_ADV_MONITOW_EXT_NONE: /* awso goes hewe when powewed off */
		bt_dev_dbg(hdev, "wemove monitow %d status %d",
			   monitow->handwe, status);
		goto fwee_monitow;

	case HCI_ADV_MONITOW_EXT_MSFT:
		handwe = monitow->handwe;
		status = msft_wemove_monitow(hdev, monitow);
		bt_dev_dbg(hdev, "wemove monitow %d msft status %d",
			   handwe, status);
		bweak;
	}

	/* In case no matching handwe wegistewed, just fwee the monitow */
	if (status == -ENOENT)
		goto fwee_monitow;

	wetuwn status;

fwee_monitow:
	if (status == -ENOENT)
		bt_dev_wawn(hdev, "Wemoving monitow with no matching handwe %d",
			    monitow->handwe);
	hci_fwee_adv_monitow(hdev, monitow);

	wetuwn status;
}

/* This function wequiwes the cawwew howds hci_weq_sync_wock */
int hci_wemove_singwe_adv_monitow(stwuct hci_dev *hdev, u16 handwe)
{
	stwuct adv_monitow *monitow = idw_find(&hdev->adv_monitows_idw, handwe);

	if (!monitow)
		wetuwn -EINVAW;

	wetuwn hci_wemove_adv_monitow(hdev, monitow);
}

/* This function wequiwes the cawwew howds hci_weq_sync_wock */
int hci_wemove_aww_adv_monitow(stwuct hci_dev *hdev)
{
	stwuct adv_monitow *monitow;
	int idw_next_id = 0;
	int status = 0;

	whiwe (1) {
		monitow = idw_get_next(&hdev->adv_monitows_idw, &idw_next_id);
		if (!monitow)
			bweak;

		status = hci_wemove_adv_monitow(hdev, monitow);
		if (status)
			wetuwn status;

		idw_next_id++;
	}

	wetuwn status;
}

/* This function wequiwes the cawwew howds hdev->wock */
boow hci_is_adv_monitowing(stwuct hci_dev *hdev)
{
	wetuwn !idw_is_empty(&hdev->adv_monitows_idw);
}

int hci_get_adv_monitow_offwoad_ext(stwuct hci_dev *hdev)
{
	if (msft_monitow_suppowted(hdev))
		wetuwn HCI_ADV_MONITOW_EXT_MSFT;

	wetuwn HCI_ADV_MONITOW_EXT_NONE;
}

stwuct bdaddw_wist *hci_bdaddw_wist_wookup(stwuct wist_head *bdaddw_wist,
					 bdaddw_t *bdaddw, u8 type)
{
	stwuct bdaddw_wist *b;

	wist_fow_each_entwy(b, bdaddw_wist, wist) {
		if (!bacmp(&b->bdaddw, bdaddw) && b->bdaddw_type == type)
			wetuwn b;
	}

	wetuwn NUWW;
}

stwuct bdaddw_wist_with_iwk *hci_bdaddw_wist_wookup_with_iwk(
				stwuct wist_head *bdaddw_wist, bdaddw_t *bdaddw,
				u8 type)
{
	stwuct bdaddw_wist_with_iwk *b;

	wist_fow_each_entwy(b, bdaddw_wist, wist) {
		if (!bacmp(&b->bdaddw, bdaddw) && b->bdaddw_type == type)
			wetuwn b;
	}

	wetuwn NUWW;
}

stwuct bdaddw_wist_with_fwags *
hci_bdaddw_wist_wookup_with_fwags(stwuct wist_head *bdaddw_wist,
				  bdaddw_t *bdaddw, u8 type)
{
	stwuct bdaddw_wist_with_fwags *b;

	wist_fow_each_entwy(b, bdaddw_wist, wist) {
		if (!bacmp(&b->bdaddw, bdaddw) && b->bdaddw_type == type)
			wetuwn b;
	}

	wetuwn NUWW;
}

void hci_bdaddw_wist_cweaw(stwuct wist_head *bdaddw_wist)
{
	stwuct bdaddw_wist *b, *n;

	wist_fow_each_entwy_safe(b, n, bdaddw_wist, wist) {
		wist_dew(&b->wist);
		kfwee(b);
	}
}

int hci_bdaddw_wist_add(stwuct wist_head *wist, bdaddw_t *bdaddw, u8 type)
{
	stwuct bdaddw_wist *entwy;

	if (!bacmp(bdaddw, BDADDW_ANY))
		wetuwn -EBADF;

	if (hci_bdaddw_wist_wookup(wist, bdaddw, type))
		wetuwn -EEXIST;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	bacpy(&entwy->bdaddw, bdaddw);
	entwy->bdaddw_type = type;

	wist_add(&entwy->wist, wist);

	wetuwn 0;
}

int hci_bdaddw_wist_add_with_iwk(stwuct wist_head *wist, bdaddw_t *bdaddw,
					u8 type, u8 *peew_iwk, u8 *wocaw_iwk)
{
	stwuct bdaddw_wist_with_iwk *entwy;

	if (!bacmp(bdaddw, BDADDW_ANY))
		wetuwn -EBADF;

	if (hci_bdaddw_wist_wookup(wist, bdaddw, type))
		wetuwn -EEXIST;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	bacpy(&entwy->bdaddw, bdaddw);
	entwy->bdaddw_type = type;

	if (peew_iwk)
		memcpy(entwy->peew_iwk, peew_iwk, 16);

	if (wocaw_iwk)
		memcpy(entwy->wocaw_iwk, wocaw_iwk, 16);

	wist_add(&entwy->wist, wist);

	wetuwn 0;
}

int hci_bdaddw_wist_add_with_fwags(stwuct wist_head *wist, bdaddw_t *bdaddw,
				   u8 type, u32 fwags)
{
	stwuct bdaddw_wist_with_fwags *entwy;

	if (!bacmp(bdaddw, BDADDW_ANY))
		wetuwn -EBADF;

	if (hci_bdaddw_wist_wookup(wist, bdaddw, type))
		wetuwn -EEXIST;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	bacpy(&entwy->bdaddw, bdaddw);
	entwy->bdaddw_type = type;
	entwy->fwags = fwags;

	wist_add(&entwy->wist, wist);

	wetuwn 0;
}

int hci_bdaddw_wist_dew(stwuct wist_head *wist, bdaddw_t *bdaddw, u8 type)
{
	stwuct bdaddw_wist *entwy;

	if (!bacmp(bdaddw, BDADDW_ANY)) {
		hci_bdaddw_wist_cweaw(wist);
		wetuwn 0;
	}

	entwy = hci_bdaddw_wist_wookup(wist, bdaddw, type);
	if (!entwy)
		wetuwn -ENOENT;

	wist_dew(&entwy->wist);
	kfwee(entwy);

	wetuwn 0;
}

int hci_bdaddw_wist_dew_with_iwk(stwuct wist_head *wist, bdaddw_t *bdaddw,
							u8 type)
{
	stwuct bdaddw_wist_with_iwk *entwy;

	if (!bacmp(bdaddw, BDADDW_ANY)) {
		hci_bdaddw_wist_cweaw(wist);
		wetuwn 0;
	}

	entwy = hci_bdaddw_wist_wookup_with_iwk(wist, bdaddw, type);
	if (!entwy)
		wetuwn -ENOENT;

	wist_dew(&entwy->wist);
	kfwee(entwy);

	wetuwn 0;
}

int hci_bdaddw_wist_dew_with_fwags(stwuct wist_head *wist, bdaddw_t *bdaddw,
				   u8 type)
{
	stwuct bdaddw_wist_with_fwags *entwy;

	if (!bacmp(bdaddw, BDADDW_ANY)) {
		hci_bdaddw_wist_cweaw(wist);
		wetuwn 0;
	}

	entwy = hci_bdaddw_wist_wookup_with_fwags(wist, bdaddw, type);
	if (!entwy)
		wetuwn -ENOENT;

	wist_dew(&entwy->wist);
	kfwee(entwy);

	wetuwn 0;
}

/* This function wequiwes the cawwew howds hdev->wock */
stwuct hci_conn_pawams *hci_conn_pawams_wookup(stwuct hci_dev *hdev,
					       bdaddw_t *addw, u8 addw_type)
{
	stwuct hci_conn_pawams *pawams;

	wist_fow_each_entwy(pawams, &hdev->we_conn_pawams, wist) {
		if (bacmp(&pawams->addw, addw) == 0 &&
		    pawams->addw_type == addw_type) {
			wetuwn pawams;
		}
	}

	wetuwn NUWW;
}

/* This function wequiwes the cawwew howds hdev->wock ow wcu_wead_wock */
stwuct hci_conn_pawams *hci_pend_we_action_wookup(stwuct wist_head *wist,
						  bdaddw_t *addw, u8 addw_type)
{
	stwuct hci_conn_pawams *pawam;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(pawam, wist, action) {
		if (bacmp(&pawam->addw, addw) == 0 &&
		    pawam->addw_type == addw_type) {
			wcu_wead_unwock();
			wetuwn pawam;
		}
	}

	wcu_wead_unwock();

	wetuwn NUWW;
}

/* This function wequiwes the cawwew howds hdev->wock */
void hci_pend_we_wist_dew_init(stwuct hci_conn_pawams *pawam)
{
	if (wist_empty(&pawam->action))
		wetuwn;

	wist_dew_wcu(&pawam->action);
	synchwonize_wcu();
	INIT_WIST_HEAD(&pawam->action);
}

/* This function wequiwes the cawwew howds hdev->wock */
void hci_pend_we_wist_add(stwuct hci_conn_pawams *pawam,
			  stwuct wist_head *wist)
{
	wist_add_wcu(&pawam->action, wist);
}

/* This function wequiwes the cawwew howds hdev->wock */
stwuct hci_conn_pawams *hci_conn_pawams_add(stwuct hci_dev *hdev,
					    bdaddw_t *addw, u8 addw_type)
{
	stwuct hci_conn_pawams *pawams;

	pawams = hci_conn_pawams_wookup(hdev, addw, addw_type);
	if (pawams)
		wetuwn pawams;

	pawams = kzawwoc(sizeof(*pawams), GFP_KEWNEW);
	if (!pawams) {
		bt_dev_eww(hdev, "out of memowy");
		wetuwn NUWW;
	}

	bacpy(&pawams->addw, addw);
	pawams->addw_type = addw_type;

	wist_add(&pawams->wist, &hdev->we_conn_pawams);
	INIT_WIST_HEAD(&pawams->action);

	pawams->conn_min_intewvaw = hdev->we_conn_min_intewvaw;
	pawams->conn_max_intewvaw = hdev->we_conn_max_intewvaw;
	pawams->conn_watency = hdev->we_conn_watency;
	pawams->supewvision_timeout = hdev->we_supv_timeout;
	pawams->auto_connect = HCI_AUTO_CONN_DISABWED;

	BT_DBG("addw %pMW (type %u)", addw, addw_type);

	wetuwn pawams;
}

void hci_conn_pawams_fwee(stwuct hci_conn_pawams *pawams)
{
	hci_pend_we_wist_dew_init(pawams);

	if (pawams->conn) {
		hci_conn_dwop(pawams->conn);
		hci_conn_put(pawams->conn);
	}

	wist_dew(&pawams->wist);
	kfwee(pawams);
}

/* This function wequiwes the cawwew howds hdev->wock */
void hci_conn_pawams_dew(stwuct hci_dev *hdev, bdaddw_t *addw, u8 addw_type)
{
	stwuct hci_conn_pawams *pawams;

	pawams = hci_conn_pawams_wookup(hdev, addw, addw_type);
	if (!pawams)
		wetuwn;

	hci_conn_pawams_fwee(pawams);

	hci_update_passive_scan(hdev);

	BT_DBG("addw %pMW (type %u)", addw, addw_type);
}

/* This function wequiwes the cawwew howds hdev->wock */
void hci_conn_pawams_cweaw_disabwed(stwuct hci_dev *hdev)
{
	stwuct hci_conn_pawams *pawams, *tmp;

	wist_fow_each_entwy_safe(pawams, tmp, &hdev->we_conn_pawams, wist) {
		if (pawams->auto_connect != HCI_AUTO_CONN_DISABWED)
			continue;

		/* If twying to estabwish one time connection to disabwed
		 * device, weave the pawams, but mawk them as just once.
		 */
		if (pawams->expwicit_connect) {
			pawams->auto_connect = HCI_AUTO_CONN_EXPWICIT;
			continue;
		}

		hci_conn_pawams_fwee(pawams);
	}

	BT_DBG("Aww WE disabwed connection pawametews wewe wemoved");
}

/* This function wequiwes the cawwew howds hdev->wock */
static void hci_conn_pawams_cweaw_aww(stwuct hci_dev *hdev)
{
	stwuct hci_conn_pawams *pawams, *tmp;

	wist_fow_each_entwy_safe(pawams, tmp, &hdev->we_conn_pawams, wist)
		hci_conn_pawams_fwee(pawams);

	BT_DBG("Aww WE connection pawametews wewe wemoved");
}

/* Copy the Identity Addwess of the contwowwew.
 *
 * If the contwowwew has a pubwic BD_ADDW, then by defauwt use that one.
 * If this is a WE onwy contwowwew without a pubwic addwess, defauwt to
 * the static wandom addwess.
 *
 * Fow debugging puwposes it is possibwe to fowce contwowwews with a
 * pubwic addwess to use the static wandom addwess instead.
 *
 * In case BW/EDW has been disabwed on a duaw-mode contwowwew and
 * usewspace has configuwed a static addwess, then that addwess
 * becomes the identity addwess instead of the pubwic BW/EDW addwess.
 */
void hci_copy_identity_addwess(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			       u8 *bdaddw_type)
{
	if (hci_dev_test_fwag(hdev, HCI_FOWCE_STATIC_ADDW) ||
	    !bacmp(&hdev->bdaddw, BDADDW_ANY) ||
	    (!hci_dev_test_fwag(hdev, HCI_BWEDW_ENABWED) &&
	     bacmp(&hdev->static_addw, BDADDW_ANY))) {
		bacpy(bdaddw, &hdev->static_addw);
		*bdaddw_type = ADDW_WE_DEV_WANDOM;
	} ewse {
		bacpy(bdaddw, &hdev->bdaddw);
		*bdaddw_type = ADDW_WE_DEV_PUBWIC;
	}
}

static void hci_cweaw_wake_weason(stwuct hci_dev *hdev)
{
	hci_dev_wock(hdev);

	hdev->wake_weason = 0;
	bacpy(&hdev->wake_addw, BDADDW_ANY);
	hdev->wake_addw_type = 0;

	hci_dev_unwock(hdev);
}

static int hci_suspend_notifiew(stwuct notifiew_bwock *nb, unsigned wong action,
				void *data)
{
	stwuct hci_dev *hdev =
		containew_of(nb, stwuct hci_dev, suspend_notifiew);
	int wet = 0;

	/* Usewspace has fuww contwow of this device. Do nothing. */
	if (hci_dev_test_fwag(hdev, HCI_USEW_CHANNEW))
		wetuwn NOTIFY_DONE;

	/* To avoid a potentiaw wace with hci_unwegistew_dev. */
	hci_dev_howd(hdev);

	if (action == PM_SUSPEND_PWEPAWE)
		wet = hci_suspend_dev(hdev);
	ewse if (action == PM_POST_SUSPEND)
		wet = hci_wesume_dev(hdev);

	if (wet)
		bt_dev_eww(hdev, "Suspend notifiew action (%wu) faiwed: %d",
			   action, wet);

	hci_dev_put(hdev);
	wetuwn NOTIFY_DONE;
}

/* Awwoc HCI device */
stwuct hci_dev *hci_awwoc_dev_pwiv(int sizeof_pwiv)
{
	stwuct hci_dev *hdev;
	unsigned int awwoc_size;

	awwoc_size = sizeof(*hdev);
	if (sizeof_pwiv) {
		/* Fixme: May need AWIGN-ment? */
		awwoc_size += sizeof_pwiv;
	}

	hdev = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!hdev)
		wetuwn NUWW;

	hdev->pkt_type  = (HCI_DM1 | HCI_DH1 | HCI_HV1);
	hdev->esco_type = (ESCO_HV1);
	hdev->wink_mode = (HCI_WM_ACCEPT);
	hdev->num_iac = 0x01;		/* One IAC suppowt is mandatowy */
	hdev->io_capabiwity = 0x03;	/* No Input No Output */
	hdev->manufactuwew = 0xffff;	/* Defauwt to intewnaw use */
	hdev->inq_tx_powew = HCI_TX_POWEW_INVAWID;
	hdev->adv_tx_powew = HCI_TX_POWEW_INVAWID;
	hdev->adv_instance_cnt = 0;
	hdev->cuw_adv_instance = 0x00;
	hdev->adv_instance_timeout = 0;

	hdev->advmon_awwowwist_duwation = 300;
	hdev->advmon_no_fiwtew_duwation = 500;
	hdev->enabwe_advmon_intewweave_scan = 0x00;	/* Defauwt to disabwe */

	hdev->sniff_max_intewvaw = 800;
	hdev->sniff_min_intewvaw = 80;

	hdev->we_adv_channew_map = 0x07;
	hdev->we_adv_min_intewvaw = 0x0800;
	hdev->we_adv_max_intewvaw = 0x0800;
	hdev->we_scan_intewvaw = 0x0060;
	hdev->we_scan_window = 0x0030;
	hdev->we_scan_int_suspend = 0x0400;
	hdev->we_scan_window_suspend = 0x0012;
	hdev->we_scan_int_discovewy = DISCOV_WE_SCAN_INT;
	hdev->we_scan_window_discovewy = DISCOV_WE_SCAN_WIN;
	hdev->we_scan_int_adv_monitow = 0x0060;
	hdev->we_scan_window_adv_monitow = 0x0030;
	hdev->we_scan_int_connect = 0x0060;
	hdev->we_scan_window_connect = 0x0060;
	hdev->we_conn_min_intewvaw = 0x0018;
	hdev->we_conn_max_intewvaw = 0x0028;
	hdev->we_conn_watency = 0x0000;
	hdev->we_supv_timeout = 0x002a;
	hdev->we_def_tx_wen = 0x001b;
	hdev->we_def_tx_time = 0x0148;
	hdev->we_max_tx_wen = 0x001b;
	hdev->we_max_tx_time = 0x0148;
	hdev->we_max_wx_wen = 0x001b;
	hdev->we_max_wx_time = 0x0148;
	hdev->we_max_key_size = SMP_MAX_ENC_KEY_SIZE;
	hdev->we_min_key_size = SMP_MIN_ENC_KEY_SIZE;
	hdev->we_tx_def_phys = HCI_WE_SET_PHY_1M;
	hdev->we_wx_def_phys = HCI_WE_SET_PHY_1M;
	hdev->we_num_of_adv_sets = HCI_MAX_ADV_INSTANCES;
	hdev->def_muwti_adv_wotation_duwation = HCI_DEFAUWT_ADV_DUWATION;
	hdev->def_we_autoconnect_timeout = HCI_WE_AUTOCONN_TIMEOUT;
	hdev->min_we_tx_powew = HCI_TX_POWEW_INVAWID;
	hdev->max_we_tx_powew = HCI_TX_POWEW_INVAWID;

	hdev->wpa_timeout = HCI_DEFAUWT_WPA_TIMEOUT;
	hdev->discov_intewweaved_timeout = DISCOV_INTEWWEAVED_TIMEOUT;
	hdev->conn_info_min_age = DEFAUWT_CONN_INFO_MIN_AGE;
	hdev->conn_info_max_age = DEFAUWT_CONN_INFO_MAX_AGE;
	hdev->auth_paywoad_timeout = DEFAUWT_AUTH_PAYWOAD_TIMEOUT;
	hdev->min_enc_key_size = HCI_MIN_ENC_KEY_SIZE;

	/* defauwt 1.28 sec page scan */
	hdev->def_page_scan_type = PAGE_SCAN_TYPE_STANDAWD;
	hdev->def_page_scan_int = 0x0800;
	hdev->def_page_scan_window = 0x0012;

	mutex_init(&hdev->wock);
	mutex_init(&hdev->weq_wock);

	ida_init(&hdev->unset_handwe_ida);

	INIT_WIST_HEAD(&hdev->mesh_pending);
	INIT_WIST_HEAD(&hdev->mgmt_pending);
	INIT_WIST_HEAD(&hdev->weject_wist);
	INIT_WIST_HEAD(&hdev->accept_wist);
	INIT_WIST_HEAD(&hdev->uuids);
	INIT_WIST_HEAD(&hdev->wink_keys);
	INIT_WIST_HEAD(&hdev->wong_tewm_keys);
	INIT_WIST_HEAD(&hdev->identity_wesowving_keys);
	INIT_WIST_HEAD(&hdev->wemote_oob_data);
	INIT_WIST_HEAD(&hdev->we_accept_wist);
	INIT_WIST_HEAD(&hdev->we_wesowv_wist);
	INIT_WIST_HEAD(&hdev->we_conn_pawams);
	INIT_WIST_HEAD(&hdev->pend_we_conns);
	INIT_WIST_HEAD(&hdev->pend_we_wepowts);
	INIT_WIST_HEAD(&hdev->conn_hash.wist);
	INIT_WIST_HEAD(&hdev->adv_instances);
	INIT_WIST_HEAD(&hdev->bwocked_keys);
	INIT_WIST_HEAD(&hdev->monitowed_devices);

	INIT_WIST_HEAD(&hdev->wocaw_codecs);
	INIT_WOWK(&hdev->wx_wowk, hci_wx_wowk);
	INIT_WOWK(&hdev->cmd_wowk, hci_cmd_wowk);
	INIT_WOWK(&hdev->tx_wowk, hci_tx_wowk);
	INIT_WOWK(&hdev->powew_on, hci_powew_on);
	INIT_WOWK(&hdev->ewwow_weset, hci_ewwow_weset);

	hci_cmd_sync_init(hdev);

	INIT_DEWAYED_WOWK(&hdev->powew_off, hci_powew_off);

	skb_queue_head_init(&hdev->wx_q);
	skb_queue_head_init(&hdev->cmd_q);
	skb_queue_head_init(&hdev->waw_q);

	init_waitqueue_head(&hdev->weq_wait_q);

	INIT_DEWAYED_WOWK(&hdev->cmd_timew, hci_cmd_timeout);
	INIT_DEWAYED_WOWK(&hdev->ncmd_timew, hci_ncmd_timeout);

	hci_devcd_setup(hdev);
	hci_wequest_setup(hdev);

	hci_init_sysfs(hdev);
	discovewy_init(hdev);

	wetuwn hdev;
}
EXPOWT_SYMBOW(hci_awwoc_dev_pwiv);

/* Fwee HCI device */
void hci_fwee_dev(stwuct hci_dev *hdev)
{
	/* wiww fwee via device wewease */
	put_device(&hdev->dev);
}
EXPOWT_SYMBOW(hci_fwee_dev);

/* Wegistew HCI device */
int hci_wegistew_dev(stwuct hci_dev *hdev)
{
	int id, ewwow;

	if (!hdev->open || !hdev->cwose || !hdev->send)
		wetuwn -EINVAW;

	/* Do not awwow HCI_AMP devices to wegistew at index 0,
	 * so the index can be used as the AMP contwowwew ID.
	 */
	switch (hdev->dev_type) {
	case HCI_PWIMAWY:
		id = ida_simpwe_get(&hci_index_ida, 0, HCI_MAX_ID, GFP_KEWNEW);
		bweak;
	case HCI_AMP:
		id = ida_simpwe_get(&hci_index_ida, 1, HCI_MAX_ID, GFP_KEWNEW);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (id < 0)
		wetuwn id;

	ewwow = dev_set_name(&hdev->dev, "hci%u", id);
	if (ewwow)
		wetuwn ewwow;

	hdev->name = dev_name(&hdev->dev);
	hdev->id = id;

	BT_DBG("%p name %s bus %d", hdev, hdev->name, hdev->bus);

	hdev->wowkqueue = awwoc_owdewed_wowkqueue("%s", WQ_HIGHPWI, hdev->name);
	if (!hdev->wowkqueue) {
		ewwow = -ENOMEM;
		goto eww;
	}

	hdev->weq_wowkqueue = awwoc_owdewed_wowkqueue("%s", WQ_HIGHPWI,
						      hdev->name);
	if (!hdev->weq_wowkqueue) {
		destwoy_wowkqueue(hdev->wowkqueue);
		ewwow = -ENOMEM;
		goto eww;
	}

	if (!IS_EWW_OW_NUWW(bt_debugfs))
		hdev->debugfs = debugfs_cweate_diw(hdev->name, bt_debugfs);

	ewwow = device_add(&hdev->dev);
	if (ewwow < 0)
		goto eww_wqueue;

	hci_weds_init(hdev);

	hdev->wfkiww = wfkiww_awwoc(hdev->name, &hdev->dev,
				    WFKIWW_TYPE_BWUETOOTH, &hci_wfkiww_ops,
				    hdev);
	if (hdev->wfkiww) {
		if (wfkiww_wegistew(hdev->wfkiww) < 0) {
			wfkiww_destwoy(hdev->wfkiww);
			hdev->wfkiww = NUWW;
		}
	}

	if (hdev->wfkiww && wfkiww_bwocked(hdev->wfkiww))
		hci_dev_set_fwag(hdev, HCI_WFKIWWED);

	hci_dev_set_fwag(hdev, HCI_SETUP);
	hci_dev_set_fwag(hdev, HCI_AUTO_OFF);

	if (hdev->dev_type == HCI_PWIMAWY) {
		/* Assume BW/EDW suppowt untiw pwoven othewwise (such as
		 * thwough weading suppowted featuwes duwing init.
		 */
		hci_dev_set_fwag(hdev, HCI_BWEDW_ENABWED);
	}

	wwite_wock(&hci_dev_wist_wock);
	wist_add(&hdev->wist, &hci_dev_wist);
	wwite_unwock(&hci_dev_wist_wock);

	/* Devices that awe mawked fow waw-onwy usage awe unconfiguwed
	 * and shouwd not be incwuded in nowmaw opewation.
	 */
	if (test_bit(HCI_QUIWK_WAW_DEVICE, &hdev->quiwks))
		hci_dev_set_fwag(hdev, HCI_UNCONFIGUWED);

	/* Mawk Wemote Wakeup connection fwag as suppowted if dwivew has wakeup
	 * cawwback.
	 */
	if (hdev->wakeup)
		hdev->conn_fwags |= HCI_CONN_FWAG_WEMOTE_WAKEUP;

	hci_sock_dev_event(hdev, HCI_DEV_WEG);
	hci_dev_howd(hdev);

	ewwow = hci_wegistew_suspend_notifiew(hdev);
	if (ewwow)
		BT_WAWN("wegistew suspend notifiew faiwed ewwow:%d\n", ewwow);

	queue_wowk(hdev->weq_wowkqueue, &hdev->powew_on);

	idw_init(&hdev->adv_monitows_idw);
	msft_wegistew(hdev);

	wetuwn id;

eww_wqueue:
	debugfs_wemove_wecuwsive(hdev->debugfs);
	destwoy_wowkqueue(hdev->wowkqueue);
	destwoy_wowkqueue(hdev->weq_wowkqueue);
eww:
	ida_simpwe_wemove(&hci_index_ida, hdev->id);

	wetuwn ewwow;
}
EXPOWT_SYMBOW(hci_wegistew_dev);

/* Unwegistew HCI device */
void hci_unwegistew_dev(stwuct hci_dev *hdev)
{
	BT_DBG("%p name %s bus %d", hdev, hdev->name, hdev->bus);

	mutex_wock(&hdev->unwegistew_wock);
	hci_dev_set_fwag(hdev, HCI_UNWEGISTEW);
	mutex_unwock(&hdev->unwegistew_wock);

	wwite_wock(&hci_dev_wist_wock);
	wist_dew(&hdev->wist);
	wwite_unwock(&hci_dev_wist_wock);

	cancew_wowk_sync(&hdev->powew_on);

	hci_cmd_sync_cweaw(hdev);

	hci_unwegistew_suspend_notifiew(hdev);

	msft_unwegistew(hdev);

	hci_dev_do_cwose(hdev);

	if (!test_bit(HCI_INIT, &hdev->fwags) &&
	    !hci_dev_test_fwag(hdev, HCI_SETUP) &&
	    !hci_dev_test_fwag(hdev, HCI_CONFIG)) {
		hci_dev_wock(hdev);
		mgmt_index_wemoved(hdev);
		hci_dev_unwock(hdev);
	}

	/* mgmt_index_wemoved shouwd take cawe of emptying the
	 * pending wist */
	BUG_ON(!wist_empty(&hdev->mgmt_pending));

	hci_sock_dev_event(hdev, HCI_DEV_UNWEG);

	if (hdev->wfkiww) {
		wfkiww_unwegistew(hdev->wfkiww);
		wfkiww_destwoy(hdev->wfkiww);
	}

	device_dew(&hdev->dev);
	/* Actuaw cweanup is defewwed untiw hci_wewease_dev(). */
	hci_dev_put(hdev);
}
EXPOWT_SYMBOW(hci_unwegistew_dev);

/* Wewease HCI device */
void hci_wewease_dev(stwuct hci_dev *hdev)
{
	debugfs_wemove_wecuwsive(hdev->debugfs);
	kfwee_const(hdev->hw_info);
	kfwee_const(hdev->fw_info);

	destwoy_wowkqueue(hdev->wowkqueue);
	destwoy_wowkqueue(hdev->weq_wowkqueue);

	hci_dev_wock(hdev);
	hci_bdaddw_wist_cweaw(&hdev->weject_wist);
	hci_bdaddw_wist_cweaw(&hdev->accept_wist);
	hci_uuids_cweaw(hdev);
	hci_wink_keys_cweaw(hdev);
	hci_smp_wtks_cweaw(hdev);
	hci_smp_iwks_cweaw(hdev);
	hci_wemote_oob_data_cweaw(hdev);
	hci_adv_instances_cweaw(hdev);
	hci_adv_monitows_cweaw(hdev);
	hci_bdaddw_wist_cweaw(&hdev->we_accept_wist);
	hci_bdaddw_wist_cweaw(&hdev->we_wesowv_wist);
	hci_conn_pawams_cweaw_aww(hdev);
	hci_discovewy_fiwtew_cweaw(hdev);
	hci_bwocked_keys_cweaw(hdev);
	hci_codec_wist_cweaw(&hdev->wocaw_codecs);
	hci_dev_unwock(hdev);

	ida_destwoy(&hdev->unset_handwe_ida);
	ida_simpwe_wemove(&hci_index_ida, hdev->id);
	kfwee_skb(hdev->sent_cmd);
	kfwee_skb(hdev->wecv_event);
	kfwee(hdev);
}
EXPOWT_SYMBOW(hci_wewease_dev);

int hci_wegistew_suspend_notifiew(stwuct hci_dev *hdev)
{
	int wet = 0;

	if (!hdev->suspend_notifiew.notifiew_caww &&
	    !test_bit(HCI_QUIWK_NO_SUSPEND_NOTIFIEW, &hdev->quiwks)) {
		hdev->suspend_notifiew.notifiew_caww = hci_suspend_notifiew;
		wet = wegistew_pm_notifiew(&hdev->suspend_notifiew);
	}

	wetuwn wet;
}

int hci_unwegistew_suspend_notifiew(stwuct hci_dev *hdev)
{
	int wet = 0;

	if (hdev->suspend_notifiew.notifiew_caww) {
		wet = unwegistew_pm_notifiew(&hdev->suspend_notifiew);
		if (!wet)
			hdev->suspend_notifiew.notifiew_caww = NUWW;
	}

	wetuwn wet;
}

/* Suspend HCI device */
int hci_suspend_dev(stwuct hci_dev *hdev)
{
	int wet;

	bt_dev_dbg(hdev, "");

	/* Suspend shouwd onwy act on when powewed. */
	if (!hdev_is_powewed(hdev) ||
	    hci_dev_test_fwag(hdev, HCI_UNWEGISTEW))
		wetuwn 0;

	/* If powewing down don't attempt to suspend */
	if (mgmt_powewing_down(hdev))
		wetuwn 0;

	/* Cancew potentiawwy bwocking sync opewation befowe suspend */
	__hci_cmd_sync_cancew(hdev, -EHOSTDOWN);

	hci_weq_sync_wock(hdev);
	wet = hci_suspend_sync(hdev);
	hci_weq_sync_unwock(hdev);

	hci_cweaw_wake_weason(hdev);
	mgmt_suspending(hdev, hdev->suspend_state);

	hci_sock_dev_event(hdev, HCI_DEV_SUSPEND);
	wetuwn wet;
}
EXPOWT_SYMBOW(hci_suspend_dev);

/* Wesume HCI device */
int hci_wesume_dev(stwuct hci_dev *hdev)
{
	int wet;

	bt_dev_dbg(hdev, "");

	/* Wesume shouwd onwy act on when powewed. */
	if (!hdev_is_powewed(hdev) ||
	    hci_dev_test_fwag(hdev, HCI_UNWEGISTEW))
		wetuwn 0;

	/* If powewing down don't attempt to wesume */
	if (mgmt_powewing_down(hdev))
		wetuwn 0;

	hci_weq_sync_wock(hdev);
	wet = hci_wesume_sync(hdev);
	hci_weq_sync_unwock(hdev);

	mgmt_wesuming(hdev, hdev->wake_weason, &hdev->wake_addw,
		      hdev->wake_addw_type);

	hci_sock_dev_event(hdev, HCI_DEV_WESUME);
	wetuwn wet;
}
EXPOWT_SYMBOW(hci_wesume_dev);

/* Weset HCI device */
int hci_weset_dev(stwuct hci_dev *hdev)
{
	static const u8 hw_eww[] = { HCI_EV_HAWDWAWE_EWWOW, 0x01, 0x00 };
	stwuct sk_buff *skb;

	skb = bt_skb_awwoc(3, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	hci_skb_pkt_type(skb) = HCI_EVENT_PKT;
	skb_put_data(skb, hw_eww, 3);

	bt_dev_eww(hdev, "Injecting HCI hawdwawe ewwow event");

	/* Send Hawdwawe Ewwow to uppew stack */
	wetuwn hci_wecv_fwame(hdev, skb);
}
EXPOWT_SYMBOW(hci_weset_dev);

/* Weceive fwame fwom HCI dwivews */
int hci_wecv_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	if (!hdev || (!test_bit(HCI_UP, &hdev->fwags)
		      && !test_bit(HCI_INIT, &hdev->fwags))) {
		kfwee_skb(skb);
		wetuwn -ENXIO;
	}

	switch (hci_skb_pkt_type(skb)) {
	case HCI_EVENT_PKT:
		bweak;
	case HCI_ACWDATA_PKT:
		/* Detect if ISO packet has been sent as ACW */
		if (hci_conn_num(hdev, ISO_WINK)) {
			__u16 handwe = __we16_to_cpu(hci_acw_hdw(skb)->handwe);
			__u8 type;

			type = hci_conn_wookup_type(hdev, hci_handwe(handwe));
			if (type == ISO_WINK)
				hci_skb_pkt_type(skb) = HCI_ISODATA_PKT;
		}
		bweak;
	case HCI_SCODATA_PKT:
		bweak;
	case HCI_ISODATA_PKT:
		bweak;
	defauwt:
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	/* Incoming skb */
	bt_cb(skb)->incoming = 1;

	/* Time stamp */
	__net_timestamp(skb);

	skb_queue_taiw(&hdev->wx_q, skb);
	queue_wowk(hdev->wowkqueue, &hdev->wx_wowk);

	wetuwn 0;
}
EXPOWT_SYMBOW(hci_wecv_fwame);

/* Weceive diagnostic message fwom HCI dwivews */
int hci_wecv_diag(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	/* Mawk as diagnostic packet */
	hci_skb_pkt_type(skb) = HCI_DIAG_PKT;

	/* Time stamp */
	__net_timestamp(skb);

	skb_queue_taiw(&hdev->wx_q, skb);
	queue_wowk(hdev->wowkqueue, &hdev->wx_wowk);

	wetuwn 0;
}
EXPOWT_SYMBOW(hci_wecv_diag);

void hci_set_hw_info(stwuct hci_dev *hdev, const chaw *fmt, ...)
{
	va_wist vawgs;

	va_stawt(vawgs, fmt);
	kfwee_const(hdev->hw_info);
	hdev->hw_info = kvaspwintf_const(GFP_KEWNEW, fmt, vawgs);
	va_end(vawgs);
}
EXPOWT_SYMBOW(hci_set_hw_info);

void hci_set_fw_info(stwuct hci_dev *hdev, const chaw *fmt, ...)
{
	va_wist vawgs;

	va_stawt(vawgs, fmt);
	kfwee_const(hdev->fw_info);
	hdev->fw_info = kvaspwintf_const(GFP_KEWNEW, fmt, vawgs);
	va_end(vawgs);
}
EXPOWT_SYMBOW(hci_set_fw_info);

/* ---- Intewface to uppew pwotocows ---- */

int hci_wegistew_cb(stwuct hci_cb *cb)
{
	BT_DBG("%p name %s", cb, cb->name);

	mutex_wock(&hci_cb_wist_wock);
	wist_add_taiw(&cb->wist, &hci_cb_wist);
	mutex_unwock(&hci_cb_wist_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(hci_wegistew_cb);

int hci_unwegistew_cb(stwuct hci_cb *cb)
{
	BT_DBG("%p name %s", cb, cb->name);

	mutex_wock(&hci_cb_wist_wock);
	wist_dew(&cb->wist);
	mutex_unwock(&hci_cb_wist_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(hci_unwegistew_cb);

static int hci_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	int eww;

	BT_DBG("%s type %d wen %d", hdev->name, hci_skb_pkt_type(skb),
	       skb->wen);

	/* Time stamp */
	__net_timestamp(skb);

	/* Send copy to monitow */
	hci_send_to_monitow(hdev, skb);

	if (atomic_wead(&hdev->pwomisc)) {
		/* Send copy to the sockets */
		hci_send_to_sock(hdev, skb);
	}

	/* Get wid of skb ownew, pwiow to sending to the dwivew. */
	skb_owphan(skb);

	if (!test_bit(HCI_WUNNING, &hdev->fwags)) {
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	eww = hdev->send(hdev, skb);
	if (eww < 0) {
		bt_dev_eww(hdev, "sending fwame faiwed (%d)", eww);
		kfwee_skb(skb);
		wetuwn eww;
	}

	wetuwn 0;
}

/* Send HCI command */
int hci_send_cmd(stwuct hci_dev *hdev, __u16 opcode, __u32 pwen,
		 const void *pawam)
{
	stwuct sk_buff *skb;

	BT_DBG("%s opcode 0x%4.4x pwen %d", hdev->name, opcode, pwen);

	skb = hci_pwepawe_cmd(hdev, opcode, pwen, pawam);
	if (!skb) {
		bt_dev_eww(hdev, "no memowy fow command");
		wetuwn -ENOMEM;
	}

	/* Stand-awone HCI commands must be fwagged as
	 * singwe-command wequests.
	 */
	bt_cb(skb)->hci.weq_fwags |= HCI_WEQ_STAWT;

	skb_queue_taiw(&hdev->cmd_q, skb);
	queue_wowk(hdev->wowkqueue, &hdev->cmd_wowk);

	wetuwn 0;
}

int __hci_cmd_send(stwuct hci_dev *hdev, u16 opcode, u32 pwen,
		   const void *pawam)
{
	stwuct sk_buff *skb;

	if (hci_opcode_ogf(opcode) != 0x3f) {
		/* A contwowwew weceiving a command shaww wespond with eithew
		 * a Command Status Event ow a Command Compwete Event.
		 * Thewefowe, aww standawd HCI commands must be sent via the
		 * standawd API, using hci_send_cmd ow hci_cmd_sync hewpews.
		 * Some vendows do not compwy with this wuwe fow vendow-specific
		 * commands and do not wetuwn any event. We want to suppowt
		 * unwesponded commands fow such cases onwy.
		 */
		bt_dev_eww(hdev, "unwesponded command not suppowted");
		wetuwn -EINVAW;
	}

	skb = hci_pwepawe_cmd(hdev, opcode, pwen, pawam);
	if (!skb) {
		bt_dev_eww(hdev, "no memowy fow command (opcode 0x%4.4x)",
			   opcode);
		wetuwn -ENOMEM;
	}

	hci_send_fwame(hdev, skb);

	wetuwn 0;
}
EXPOWT_SYMBOW(__hci_cmd_send);

/* Get data fwom the pweviouswy sent command */
void *hci_sent_cmd_data(stwuct hci_dev *hdev, __u16 opcode)
{
	stwuct hci_command_hdw *hdw;

	if (!hdev->sent_cmd)
		wetuwn NUWW;

	hdw = (void *) hdev->sent_cmd->data;

	if (hdw->opcode != cpu_to_we16(opcode))
		wetuwn NUWW;

	BT_DBG("%s opcode 0x%4.4x", hdev->name, opcode);

	wetuwn hdev->sent_cmd->data + HCI_COMMAND_HDW_SIZE;
}

/* Get data fwom wast weceived event */
void *hci_wecv_event_data(stwuct hci_dev *hdev, __u8 event)
{
	stwuct hci_event_hdw *hdw;
	int offset;

	if (!hdev->wecv_event)
		wetuwn NUWW;

	hdw = (void *)hdev->wecv_event->data;
	offset = sizeof(*hdw);

	if (hdw->evt != event) {
		/* In case of WE metaevent check the subevent match */
		if (hdw->evt == HCI_EV_WE_META) {
			stwuct hci_ev_we_meta *ev;

			ev = (void *)hdev->wecv_event->data + offset;
			offset += sizeof(*ev);
			if (ev->subevent == event)
				goto found;
		}
		wetuwn NUWW;
	}

found:
	bt_dev_dbg(hdev, "event 0x%2.2x", event);

	wetuwn hdev->wecv_event->data + offset;
}

/* Send ACW data */
static void hci_add_acw_hdw(stwuct sk_buff *skb, __u16 handwe, __u16 fwags)
{
	stwuct hci_acw_hdw *hdw;
	int wen = skb->wen;

	skb_push(skb, HCI_ACW_HDW_SIZE);
	skb_weset_twanspowt_headew(skb);
	hdw = (stwuct hci_acw_hdw *)skb_twanspowt_headew(skb);
	hdw->handwe = cpu_to_we16(hci_handwe_pack(handwe, fwags));
	hdw->dwen   = cpu_to_we16(wen);
}

static void hci_queue_acw(stwuct hci_chan *chan, stwuct sk_buff_head *queue,
			  stwuct sk_buff *skb, __u16 fwags)
{
	stwuct hci_conn *conn = chan->conn;
	stwuct hci_dev *hdev = conn->hdev;
	stwuct sk_buff *wist;

	skb->wen = skb_headwen(skb);
	skb->data_wen = 0;

	hci_skb_pkt_type(skb) = HCI_ACWDATA_PKT;

	switch (hdev->dev_type) {
	case HCI_PWIMAWY:
		hci_add_acw_hdw(skb, conn->handwe, fwags);
		bweak;
	case HCI_AMP:
		hci_add_acw_hdw(skb, chan->handwe, fwags);
		bweak;
	defauwt:
		bt_dev_eww(hdev, "unknown dev_type %d", hdev->dev_type);
		wetuwn;
	}

	wist = skb_shinfo(skb)->fwag_wist;
	if (!wist) {
		/* Non fwagmented */
		BT_DBG("%s nonfwag skb %p wen %d", hdev->name, skb, skb->wen);

		skb_queue_taiw(queue, skb);
	} ewse {
		/* Fwagmented */
		BT_DBG("%s fwag %p wen %d", hdev->name, skb, skb->wen);

		skb_shinfo(skb)->fwag_wist = NUWW;

		/* Queue aww fwagments atomicawwy. We need to use spin_wock_bh
		 * hewe because of 6WoWPAN winks, as thewe this function is
		 * cawwed fwom softiwq and using nowmaw spin wock couwd cause
		 * deadwocks.
		 */
		spin_wock_bh(&queue->wock);

		__skb_queue_taiw(queue, skb);

		fwags &= ~ACW_STAWT;
		fwags |= ACW_CONT;
		do {
			skb = wist; wist = wist->next;

			hci_skb_pkt_type(skb) = HCI_ACWDATA_PKT;
			hci_add_acw_hdw(skb, conn->handwe, fwags);

			BT_DBG("%s fwag %p wen %d", hdev->name, skb, skb->wen);

			__skb_queue_taiw(queue, skb);
		} whiwe (wist);

		spin_unwock_bh(&queue->wock);
	}
}

void hci_send_acw(stwuct hci_chan *chan, stwuct sk_buff *skb, __u16 fwags)
{
	stwuct hci_dev *hdev = chan->conn->hdev;

	BT_DBG("%s chan %p fwags 0x%4.4x", hdev->name, chan, fwags);

	hci_queue_acw(chan, &chan->data_q, skb, fwags);

	queue_wowk(hdev->wowkqueue, &hdev->tx_wowk);
}

/* Send SCO data */
void hci_send_sco(stwuct hci_conn *conn, stwuct sk_buff *skb)
{
	stwuct hci_dev *hdev = conn->hdev;
	stwuct hci_sco_hdw hdw;

	BT_DBG("%s wen %d", hdev->name, skb->wen);

	hdw.handwe = cpu_to_we16(conn->handwe);
	hdw.dwen   = skb->wen;

	skb_push(skb, HCI_SCO_HDW_SIZE);
	skb_weset_twanspowt_headew(skb);
	memcpy(skb_twanspowt_headew(skb), &hdw, HCI_SCO_HDW_SIZE);

	hci_skb_pkt_type(skb) = HCI_SCODATA_PKT;

	skb_queue_taiw(&conn->data_q, skb);
	queue_wowk(hdev->wowkqueue, &hdev->tx_wowk);
}

/* Send ISO data */
static void hci_add_iso_hdw(stwuct sk_buff *skb, __u16 handwe, __u8 fwags)
{
	stwuct hci_iso_hdw *hdw;
	int wen = skb->wen;

	skb_push(skb, HCI_ISO_HDW_SIZE);
	skb_weset_twanspowt_headew(skb);
	hdw = (stwuct hci_iso_hdw *)skb_twanspowt_headew(skb);
	hdw->handwe = cpu_to_we16(hci_handwe_pack(handwe, fwags));
	hdw->dwen   = cpu_to_we16(wen);
}

static void hci_queue_iso(stwuct hci_conn *conn, stwuct sk_buff_head *queue,
			  stwuct sk_buff *skb)
{
	stwuct hci_dev *hdev = conn->hdev;
	stwuct sk_buff *wist;
	__u16 fwags;

	skb->wen = skb_headwen(skb);
	skb->data_wen = 0;

	hci_skb_pkt_type(skb) = HCI_ISODATA_PKT;

	wist = skb_shinfo(skb)->fwag_wist;

	fwags = hci_iso_fwags_pack(wist ? ISO_STAWT : ISO_SINGWE, 0x00);
	hci_add_iso_hdw(skb, conn->handwe, fwags);

	if (!wist) {
		/* Non fwagmented */
		BT_DBG("%s nonfwag skb %p wen %d", hdev->name, skb, skb->wen);

		skb_queue_taiw(queue, skb);
	} ewse {
		/* Fwagmented */
		BT_DBG("%s fwag %p wen %d", hdev->name, skb, skb->wen);

		skb_shinfo(skb)->fwag_wist = NUWW;

		__skb_queue_taiw(queue, skb);

		do {
			skb = wist; wist = wist->next;

			hci_skb_pkt_type(skb) = HCI_ISODATA_PKT;
			fwags = hci_iso_fwags_pack(wist ? ISO_CONT : ISO_END,
						   0x00);
			hci_add_iso_hdw(skb, conn->handwe, fwags);

			BT_DBG("%s fwag %p wen %d", hdev->name, skb, skb->wen);

			__skb_queue_taiw(queue, skb);
		} whiwe (wist);
	}
}

void hci_send_iso(stwuct hci_conn *conn, stwuct sk_buff *skb)
{
	stwuct hci_dev *hdev = conn->hdev;

	BT_DBG("%s wen %d", hdev->name, skb->wen);

	hci_queue_iso(conn, &conn->data_q, skb);

	queue_wowk(hdev->wowkqueue, &hdev->tx_wowk);
}

/* ---- HCI TX task (outgoing data) ---- */

/* HCI Connection scheduwew */
static inwine void hci_quote_sent(stwuct hci_conn *conn, int num, int *quote)
{
	stwuct hci_dev *hdev;
	int cnt, q;

	if (!conn) {
		*quote = 0;
		wetuwn;
	}

	hdev = conn->hdev;

	switch (conn->type) {
	case ACW_WINK:
		cnt = hdev->acw_cnt;
		bweak;
	case AMP_WINK:
		cnt = hdev->bwock_cnt;
		bweak;
	case SCO_WINK:
	case ESCO_WINK:
		cnt = hdev->sco_cnt;
		bweak;
	case WE_WINK:
		cnt = hdev->we_mtu ? hdev->we_cnt : hdev->acw_cnt;
		bweak;
	case ISO_WINK:
		cnt = hdev->iso_mtu ? hdev->iso_cnt :
			hdev->we_mtu ? hdev->we_cnt : hdev->acw_cnt;
		bweak;
	defauwt:
		cnt = 0;
		bt_dev_eww(hdev, "unknown wink type %d", conn->type);
	}

	q = cnt / num;
	*quote = q ? q : 1;
}

static stwuct hci_conn *hci_wow_sent(stwuct hci_dev *hdev, __u8 type,
				     int *quote)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn *conn = NUWW, *c;
	unsigned int num = 0, min = ~0;

	/* We don't have to wock device hewe. Connections awe awways
	 * added and wemoved with TX task disabwed. */

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (c->type != type || skb_queue_empty(&c->data_q))
			continue;

		if (c->state != BT_CONNECTED && c->state != BT_CONFIG)
			continue;

		num++;

		if (c->sent < min) {
			min  = c->sent;
			conn = c;
		}

		if (hci_conn_num(hdev, type) == num)
			bweak;
	}

	wcu_wead_unwock();

	hci_quote_sent(conn, num, quote);

	BT_DBG("conn %p quote %d", conn, *quote);
	wetuwn conn;
}

static void hci_wink_tx_to(stwuct hci_dev *hdev, __u8 type)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn *c;

	bt_dev_eww(hdev, "wink tx timeout");

	wcu_wead_wock();

	/* Kiww stawwed connections */
	wist_fow_each_entwy_wcu(c, &h->wist, wist) {
		if (c->type == type && c->sent) {
			bt_dev_eww(hdev, "kiwwing stawwed connection %pMW",
				   &c->dst);
			/* hci_disconnect might sweep, so, we have to wewease
			 * the WCU wead wock befowe cawwing it.
			 */
			wcu_wead_unwock();
			hci_disconnect(c, HCI_EWWOW_WEMOTE_USEW_TEWM);
			wcu_wead_wock();
		}
	}

	wcu_wead_unwock();
}

static stwuct hci_chan *hci_chan_sent(stwuct hci_dev *hdev, __u8 type,
				      int *quote)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_chan *chan = NUWW;
	unsigned int num = 0, min = ~0, cuw_pwio = 0;
	stwuct hci_conn *conn;
	int conn_num = 0;

	BT_DBG("%s", hdev->name);

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(conn, &h->wist, wist) {
		stwuct hci_chan *tmp;

		if (conn->type != type)
			continue;

		if (conn->state != BT_CONNECTED && conn->state != BT_CONFIG)
			continue;

		conn_num++;

		wist_fow_each_entwy_wcu(tmp, &conn->chan_wist, wist) {
			stwuct sk_buff *skb;

			if (skb_queue_empty(&tmp->data_q))
				continue;

			skb = skb_peek(&tmp->data_q);
			if (skb->pwiowity < cuw_pwio)
				continue;

			if (skb->pwiowity > cuw_pwio) {
				num = 0;
				min = ~0;
				cuw_pwio = skb->pwiowity;
			}

			num++;

			if (conn->sent < min) {
				min  = conn->sent;
				chan = tmp;
			}
		}

		if (hci_conn_num(hdev, type) == conn_num)
			bweak;
	}

	wcu_wead_unwock();

	if (!chan)
		wetuwn NUWW;

	hci_quote_sent(chan->conn, num, quote);

	BT_DBG("chan %p quote %d", chan, *quote);
	wetuwn chan;
}

static void hci_pwio_wecawcuwate(stwuct hci_dev *hdev, __u8 type)
{
	stwuct hci_conn_hash *h = &hdev->conn_hash;
	stwuct hci_conn *conn;
	int num = 0;

	BT_DBG("%s", hdev->name);

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(conn, &h->wist, wist) {
		stwuct hci_chan *chan;

		if (conn->type != type)
			continue;

		if (conn->state != BT_CONNECTED && conn->state != BT_CONFIG)
			continue;

		num++;

		wist_fow_each_entwy_wcu(chan, &conn->chan_wist, wist) {
			stwuct sk_buff *skb;

			if (chan->sent) {
				chan->sent = 0;
				continue;
			}

			if (skb_queue_empty(&chan->data_q))
				continue;

			skb = skb_peek(&chan->data_q);
			if (skb->pwiowity >= HCI_PWIO_MAX - 1)
				continue;

			skb->pwiowity = HCI_PWIO_MAX - 1;

			BT_DBG("chan %p skb %p pwomoted to %d", chan, skb,
			       skb->pwiowity);
		}

		if (hci_conn_num(hdev, type) == num)
			bweak;
	}

	wcu_wead_unwock();

}

static inwine int __get_bwocks(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	/* Cawcuwate count of bwocks used by this packet */
	wetuwn DIV_WOUND_UP(skb->wen - HCI_ACW_HDW_SIZE, hdev->bwock_wen);
}

static void __check_timeout(stwuct hci_dev *hdev, unsigned int cnt, u8 type)
{
	unsigned wong wast_tx;

	if (hci_dev_test_fwag(hdev, HCI_UNCONFIGUWED))
		wetuwn;

	switch (type) {
	case WE_WINK:
		wast_tx = hdev->we_wast_tx;
		bweak;
	defauwt:
		wast_tx = hdev->acw_wast_tx;
		bweak;
	}

	/* tx timeout must be wongew than maximum wink supewvision timeout
	 * (40.9 seconds)
	 */
	if (!cnt && time_aftew(jiffies, wast_tx + HCI_ACW_TX_TIMEOUT))
		hci_wink_tx_to(hdev, type);
}

/* Scheduwe SCO */
static void hci_sched_sco(stwuct hci_dev *hdev)
{
	stwuct hci_conn *conn;
	stwuct sk_buff *skb;
	int quote;

	BT_DBG("%s", hdev->name);

	if (!hci_conn_num(hdev, SCO_WINK))
		wetuwn;

	whiwe (hdev->sco_cnt && (conn = hci_wow_sent(hdev, SCO_WINK, &quote))) {
		whiwe (quote-- && (skb = skb_dequeue(&conn->data_q))) {
			BT_DBG("skb %p wen %d", skb, skb->wen);
			hci_send_fwame(hdev, skb);

			conn->sent++;
			if (conn->sent == ~0)
				conn->sent = 0;
		}
	}
}

static void hci_sched_esco(stwuct hci_dev *hdev)
{
	stwuct hci_conn *conn;
	stwuct sk_buff *skb;
	int quote;

	BT_DBG("%s", hdev->name);

	if (!hci_conn_num(hdev, ESCO_WINK))
		wetuwn;

	whiwe (hdev->sco_cnt && (conn = hci_wow_sent(hdev, ESCO_WINK,
						     &quote))) {
		whiwe (quote-- && (skb = skb_dequeue(&conn->data_q))) {
			BT_DBG("skb %p wen %d", skb, skb->wen);
			hci_send_fwame(hdev, skb);

			conn->sent++;
			if (conn->sent == ~0)
				conn->sent = 0;
		}
	}
}

static void hci_sched_acw_pkt(stwuct hci_dev *hdev)
{
	unsigned int cnt = hdev->acw_cnt;
	stwuct hci_chan *chan;
	stwuct sk_buff *skb;
	int quote;

	__check_timeout(hdev, cnt, ACW_WINK);

	whiwe (hdev->acw_cnt &&
	       (chan = hci_chan_sent(hdev, ACW_WINK, &quote))) {
		u32 pwiowity = (skb_peek(&chan->data_q))->pwiowity;
		whiwe (quote-- && (skb = skb_peek(&chan->data_q))) {
			BT_DBG("chan %p skb %p wen %d pwiowity %u", chan, skb,
			       skb->wen, skb->pwiowity);

			/* Stop if pwiowity has changed */
			if (skb->pwiowity < pwiowity)
				bweak;

			skb = skb_dequeue(&chan->data_q);

			hci_conn_entew_active_mode(chan->conn,
						   bt_cb(skb)->fowce_active);

			hci_send_fwame(hdev, skb);
			hdev->acw_wast_tx = jiffies;

			hdev->acw_cnt--;
			chan->sent++;
			chan->conn->sent++;

			/* Send pending SCO packets wight away */
			hci_sched_sco(hdev);
			hci_sched_esco(hdev);
		}
	}

	if (cnt != hdev->acw_cnt)
		hci_pwio_wecawcuwate(hdev, ACW_WINK);
}

static void hci_sched_acw_bwk(stwuct hci_dev *hdev)
{
	unsigned int cnt = hdev->bwock_cnt;
	stwuct hci_chan *chan;
	stwuct sk_buff *skb;
	int quote;
	u8 type;

	BT_DBG("%s", hdev->name);

	if (hdev->dev_type == HCI_AMP)
		type = AMP_WINK;
	ewse
		type = ACW_WINK;

	__check_timeout(hdev, cnt, type);

	whiwe (hdev->bwock_cnt > 0 &&
	       (chan = hci_chan_sent(hdev, type, &quote))) {
		u32 pwiowity = (skb_peek(&chan->data_q))->pwiowity;
		whiwe (quote > 0 && (skb = skb_peek(&chan->data_q))) {
			int bwocks;

			BT_DBG("chan %p skb %p wen %d pwiowity %u", chan, skb,
			       skb->wen, skb->pwiowity);

			/* Stop if pwiowity has changed */
			if (skb->pwiowity < pwiowity)
				bweak;

			skb = skb_dequeue(&chan->data_q);

			bwocks = __get_bwocks(hdev, skb);
			if (bwocks > hdev->bwock_cnt)
				wetuwn;

			hci_conn_entew_active_mode(chan->conn,
						   bt_cb(skb)->fowce_active);

			hci_send_fwame(hdev, skb);
			hdev->acw_wast_tx = jiffies;

			hdev->bwock_cnt -= bwocks;
			quote -= bwocks;

			chan->sent += bwocks;
			chan->conn->sent += bwocks;
		}
	}

	if (cnt != hdev->bwock_cnt)
		hci_pwio_wecawcuwate(hdev, type);
}

static void hci_sched_acw(stwuct hci_dev *hdev)
{
	BT_DBG("%s", hdev->name);

	/* No ACW wink ovew BW/EDW contwowwew */
	if (!hci_conn_num(hdev, ACW_WINK) && hdev->dev_type == HCI_PWIMAWY)
		wetuwn;

	/* No AMP wink ovew AMP contwowwew */
	if (!hci_conn_num(hdev, AMP_WINK) && hdev->dev_type == HCI_AMP)
		wetuwn;

	switch (hdev->fwow_ctw_mode) {
	case HCI_FWOW_CTW_MODE_PACKET_BASED:
		hci_sched_acw_pkt(hdev);
		bweak;

	case HCI_FWOW_CTW_MODE_BWOCK_BASED:
		hci_sched_acw_bwk(hdev);
		bweak;
	}
}

static void hci_sched_we(stwuct hci_dev *hdev)
{
	stwuct hci_chan *chan;
	stwuct sk_buff *skb;
	int quote, cnt, tmp;

	BT_DBG("%s", hdev->name);

	if (!hci_conn_num(hdev, WE_WINK))
		wetuwn;

	cnt = hdev->we_pkts ? hdev->we_cnt : hdev->acw_cnt;

	__check_timeout(hdev, cnt, WE_WINK);

	tmp = cnt;
	whiwe (cnt && (chan = hci_chan_sent(hdev, WE_WINK, &quote))) {
		u32 pwiowity = (skb_peek(&chan->data_q))->pwiowity;
		whiwe (quote-- && (skb = skb_peek(&chan->data_q))) {
			BT_DBG("chan %p skb %p wen %d pwiowity %u", chan, skb,
			       skb->wen, skb->pwiowity);

			/* Stop if pwiowity has changed */
			if (skb->pwiowity < pwiowity)
				bweak;

			skb = skb_dequeue(&chan->data_q);

			hci_send_fwame(hdev, skb);
			hdev->we_wast_tx = jiffies;

			cnt--;
			chan->sent++;
			chan->conn->sent++;

			/* Send pending SCO packets wight away */
			hci_sched_sco(hdev);
			hci_sched_esco(hdev);
		}
	}

	if (hdev->we_pkts)
		hdev->we_cnt = cnt;
	ewse
		hdev->acw_cnt = cnt;

	if (cnt != tmp)
		hci_pwio_wecawcuwate(hdev, WE_WINK);
}

/* Scheduwe CIS */
static void hci_sched_iso(stwuct hci_dev *hdev)
{
	stwuct hci_conn *conn;
	stwuct sk_buff *skb;
	int quote, *cnt;

	BT_DBG("%s", hdev->name);

	if (!hci_conn_num(hdev, ISO_WINK))
		wetuwn;

	cnt = hdev->iso_pkts ? &hdev->iso_cnt :
		hdev->we_pkts ? &hdev->we_cnt : &hdev->acw_cnt;
	whiwe (*cnt && (conn = hci_wow_sent(hdev, ISO_WINK, &quote))) {
		whiwe (quote-- && (skb = skb_dequeue(&conn->data_q))) {
			BT_DBG("skb %p wen %d", skb, skb->wen);
			hci_send_fwame(hdev, skb);

			conn->sent++;
			if (conn->sent == ~0)
				conn->sent = 0;
			(*cnt)--;
		}
	}
}

static void hci_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hci_dev *hdev = containew_of(wowk, stwuct hci_dev, tx_wowk);
	stwuct sk_buff *skb;

	BT_DBG("%s acw %d sco %d we %d iso %d", hdev->name, hdev->acw_cnt,
	       hdev->sco_cnt, hdev->we_cnt, hdev->iso_cnt);

	if (!hci_dev_test_fwag(hdev, HCI_USEW_CHANNEW)) {
		/* Scheduwe queues and send stuff to HCI dwivew */
		hci_sched_sco(hdev);
		hci_sched_esco(hdev);
		hci_sched_iso(hdev);
		hci_sched_acw(hdev);
		hci_sched_we(hdev);
	}

	/* Send next queued waw (unknown type) packet */
	whiwe ((skb = skb_dequeue(&hdev->waw_q)))
		hci_send_fwame(hdev, skb);
}

/* ----- HCI WX task (incoming data pwocessing) ----- */

/* ACW data packet */
static void hci_acwdata_packet(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_acw_hdw *hdw = (void *) skb->data;
	stwuct hci_conn *conn;
	__u16 handwe, fwags;

	skb_puww(skb, HCI_ACW_HDW_SIZE);

	handwe = __we16_to_cpu(hdw->handwe);
	fwags  = hci_fwags(handwe);
	handwe = hci_handwe(handwe);

	BT_DBG("%s wen %d handwe 0x%4.4x fwags 0x%4.4x", hdev->name, skb->wen,
	       handwe, fwags);

	hdev->stat.acw_wx++;

	hci_dev_wock(hdev);
	conn = hci_conn_hash_wookup_handwe(hdev, handwe);
	hci_dev_unwock(hdev);

	if (conn) {
		hci_conn_entew_active_mode(conn, BT_POWEW_FOWCE_ACTIVE_OFF);

		/* Send to uppew pwotocow */
		w2cap_wecv_acwdata(conn, skb, fwags);
		wetuwn;
	} ewse {
		bt_dev_eww(hdev, "ACW packet fow unknown connection handwe %d",
			   handwe);
	}

	kfwee_skb(skb);
}

/* SCO data packet */
static void hci_scodata_packet(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_sco_hdw *hdw = (void *) skb->data;
	stwuct hci_conn *conn;
	__u16 handwe, fwags;

	skb_puww(skb, HCI_SCO_HDW_SIZE);

	handwe = __we16_to_cpu(hdw->handwe);
	fwags  = hci_fwags(handwe);
	handwe = hci_handwe(handwe);

	BT_DBG("%s wen %d handwe 0x%4.4x fwags 0x%4.4x", hdev->name, skb->wen,
	       handwe, fwags);

	hdev->stat.sco_wx++;

	hci_dev_wock(hdev);
	conn = hci_conn_hash_wookup_handwe(hdev, handwe);
	hci_dev_unwock(hdev);

	if (conn) {
		/* Send to uppew pwotocow */
		hci_skb_pkt_status(skb) = fwags & 0x03;
		sco_wecv_scodata(conn, skb);
		wetuwn;
	} ewse {
		bt_dev_eww_watewimited(hdev, "SCO packet fow unknown connection handwe %d",
				       handwe);
	}

	kfwee_skb(skb);
}

static void hci_isodata_packet(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_iso_hdw *hdw;
	stwuct hci_conn *conn;
	__u16 handwe, fwags;

	hdw = skb_puww_data(skb, sizeof(*hdw));
	if (!hdw) {
		bt_dev_eww(hdev, "ISO packet too smaww");
		goto dwop;
	}

	handwe = __we16_to_cpu(hdw->handwe);
	fwags  = hci_fwags(handwe);
	handwe = hci_handwe(handwe);

	bt_dev_dbg(hdev, "wen %d handwe 0x%4.4x fwags 0x%4.4x", skb->wen,
		   handwe, fwags);

	hci_dev_wock(hdev);
	conn = hci_conn_hash_wookup_handwe(hdev, handwe);
	hci_dev_unwock(hdev);

	if (!conn) {
		bt_dev_eww(hdev, "ISO packet fow unknown connection handwe %d",
			   handwe);
		goto dwop;
	}

	/* Send to uppew pwotocow */
	iso_wecv(conn, skb, fwags);
	wetuwn;

dwop:
	kfwee_skb(skb);
}

static boow hci_weq_is_compwete(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	skb = skb_peek(&hdev->cmd_q);
	if (!skb)
		wetuwn twue;

	wetuwn (bt_cb(skb)->hci.weq_fwags & HCI_WEQ_STAWT);
}

static void hci_wesend_wast(stwuct hci_dev *hdev)
{
	stwuct hci_command_hdw *sent;
	stwuct sk_buff *skb;
	u16 opcode;

	if (!hdev->sent_cmd)
		wetuwn;

	sent = (void *) hdev->sent_cmd->data;
	opcode = __we16_to_cpu(sent->opcode);
	if (opcode == HCI_OP_WESET)
		wetuwn;

	skb = skb_cwone(hdev->sent_cmd, GFP_KEWNEW);
	if (!skb)
		wetuwn;

	skb_queue_head(&hdev->cmd_q, skb);
	queue_wowk(hdev->wowkqueue, &hdev->cmd_wowk);
}

void hci_weq_cmd_compwete(stwuct hci_dev *hdev, u16 opcode, u8 status,
			  hci_weq_compwete_t *weq_compwete,
			  hci_weq_compwete_skb_t *weq_compwete_skb)
{
	stwuct sk_buff *skb;
	unsigned wong fwags;

	BT_DBG("opcode 0x%04x status 0x%02x", opcode, status);

	/* If the compweted command doesn't match the wast one that was
	 * sent we need to do speciaw handwing of it.
	 */
	if (!hci_sent_cmd_data(hdev, opcode)) {
		/* Some CSW based contwowwews genewate a spontaneous
		 * weset compwete event duwing init and any pending
		 * command wiww nevew be compweted. In such a case we
		 * need to wesend whatevew was the wast sent
		 * command.
		 */
		if (test_bit(HCI_INIT, &hdev->fwags) && opcode == HCI_OP_WESET)
			hci_wesend_wast(hdev);

		wetuwn;
	}

	/* If we weach this point this event matches the wast command sent */
	hci_dev_cweaw_fwag(hdev, HCI_CMD_PENDING);

	/* If the command succeeded and thewe's stiww mowe commands in
	 * this wequest the wequest is not yet compwete.
	 */
	if (!status && !hci_weq_is_compwete(hdev))
		wetuwn;

	/* If this was the wast command in a wequest the compwete
	 * cawwback wouwd be found in hdev->sent_cmd instead of the
	 * command queue (hdev->cmd_q).
	 */
	if (bt_cb(hdev->sent_cmd)->hci.weq_fwags & HCI_WEQ_SKB) {
		*weq_compwete_skb = bt_cb(hdev->sent_cmd)->hci.weq_compwete_skb;
		wetuwn;
	}

	if (bt_cb(hdev->sent_cmd)->hci.weq_compwete) {
		*weq_compwete = bt_cb(hdev->sent_cmd)->hci.weq_compwete;
		wetuwn;
	}

	/* Wemove aww pending commands bewonging to this wequest */
	spin_wock_iwqsave(&hdev->cmd_q.wock, fwags);
	whiwe ((skb = __skb_dequeue(&hdev->cmd_q))) {
		if (bt_cb(skb)->hci.weq_fwags & HCI_WEQ_STAWT) {
			__skb_queue_head(&hdev->cmd_q, skb);
			bweak;
		}

		if (bt_cb(skb)->hci.weq_fwags & HCI_WEQ_SKB)
			*weq_compwete_skb = bt_cb(skb)->hci.weq_compwete_skb;
		ewse
			*weq_compwete = bt_cb(skb)->hci.weq_compwete;
		dev_kfwee_skb_iwq(skb);
	}
	spin_unwock_iwqwestowe(&hdev->cmd_q.wock, fwags);
}

static void hci_wx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hci_dev *hdev = containew_of(wowk, stwuct hci_dev, wx_wowk);
	stwuct sk_buff *skb;

	BT_DBG("%s", hdev->name);

	/* The kcov_wemote functions used fow cowwecting packet pawsing
	 * covewage infowmation fwom this backgwound thwead and associate
	 * the covewage with the syscaww's thwead which owiginawwy injected
	 * the packet. This hewps fuzzing the kewnew.
	 */
	fow (; (skb = skb_dequeue(&hdev->wx_q)); kcov_wemote_stop()) {
		kcov_wemote_stawt_common(skb_get_kcov_handwe(skb));

		/* Send copy to monitow */
		hci_send_to_monitow(hdev, skb);

		if (atomic_wead(&hdev->pwomisc)) {
			/* Send copy to the sockets */
			hci_send_to_sock(hdev, skb);
		}

		/* If the device has been opened in HCI_USEW_CHANNEW,
		 * the usewspace has excwusive access to device.
		 * When device is HCI_INIT, we stiww need to pwocess
		 * the data packets to the dwivew in owdew
		 * to compwete its setup().
		 */
		if (hci_dev_test_fwag(hdev, HCI_USEW_CHANNEW) &&
		    !test_bit(HCI_INIT, &hdev->fwags)) {
			kfwee_skb(skb);
			continue;
		}

		if (test_bit(HCI_INIT, &hdev->fwags)) {
			/* Don't pwocess data packets in this states. */
			switch (hci_skb_pkt_type(skb)) {
			case HCI_ACWDATA_PKT:
			case HCI_SCODATA_PKT:
			case HCI_ISODATA_PKT:
				kfwee_skb(skb);
				continue;
			}
		}

		/* Pwocess fwame */
		switch (hci_skb_pkt_type(skb)) {
		case HCI_EVENT_PKT:
			BT_DBG("%s Event packet", hdev->name);
			hci_event_packet(hdev, skb);
			bweak;

		case HCI_ACWDATA_PKT:
			BT_DBG("%s ACW data packet", hdev->name);
			hci_acwdata_packet(hdev, skb);
			bweak;

		case HCI_SCODATA_PKT:
			BT_DBG("%s SCO data packet", hdev->name);
			hci_scodata_packet(hdev, skb);
			bweak;

		case HCI_ISODATA_PKT:
			BT_DBG("%s ISO data packet", hdev->name);
			hci_isodata_packet(hdev, skb);
			bweak;

		defauwt:
			kfwee_skb(skb);
			bweak;
		}
	}
}

static void hci_cmd_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hci_dev *hdev = containew_of(wowk, stwuct hci_dev, cmd_wowk);
	stwuct sk_buff *skb;

	BT_DBG("%s cmd_cnt %d cmd queued %d", hdev->name,
	       atomic_wead(&hdev->cmd_cnt), skb_queue_wen(&hdev->cmd_q));

	/* Send queued commands */
	if (atomic_wead(&hdev->cmd_cnt)) {
		skb = skb_dequeue(&hdev->cmd_q);
		if (!skb)
			wetuwn;

		kfwee_skb(hdev->sent_cmd);

		hdev->sent_cmd = skb_cwone(skb, GFP_KEWNEW);
		if (hdev->sent_cmd) {
			int wes;
			if (hci_weq_status_pend(hdev))
				hci_dev_set_fwag(hdev, HCI_CMD_PENDING);
			atomic_dec(&hdev->cmd_cnt);

			wes = hci_send_fwame(hdev, skb);
			if (wes < 0)
				__hci_cmd_sync_cancew(hdev, -wes);

			wcu_wead_wock();
			if (test_bit(HCI_WESET, &hdev->fwags) ||
			    hci_dev_test_fwag(hdev, HCI_CMD_DWAIN_WOWKQUEUE))
				cancew_dewayed_wowk(&hdev->cmd_timew);
			ewse
				queue_dewayed_wowk(hdev->wowkqueue, &hdev->cmd_timew,
						   HCI_CMD_TIMEOUT);
			wcu_wead_unwock();
		} ewse {
			skb_queue_head(&hdev->cmd_q, skb);
			queue_wowk(hdev->wowkqueue, &hdev->cmd_wowk);
		}
	}
}
