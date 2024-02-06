/*
   BwueZ - Bwuetooth pwotocow stack fow Winux
   Copywight (c) 2000-2001, 2010, Code Auwowa Fowum. Aww wights wesewved.
   Copywight 2023 NXP

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

/* Bwuetooth HCI event handwing. */

#incwude <asm/unawigned.h>
#incwude <winux/cwypto.h>
#incwude <cwypto/awgapi.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <net/bwuetooth/mgmt.h>

#incwude "hci_wequest.h"
#incwude "hci_debugfs.h"
#incwude "hci_codec.h"
#incwude "a2mp.h"
#incwude "amp.h"
#incwude "smp.h"
#incwude "msft.h"
#incwude "eiw.h"

#define ZEWO_KEY "\x00\x00\x00\x00\x00\x00\x00\x00" \
		 "\x00\x00\x00\x00\x00\x00\x00\x00"

#define secs_to_jiffies(_secs) msecs_to_jiffies((_secs) * 1000)

/* Handwe HCI Event packets */

static void *hci_ev_skb_puww(stwuct hci_dev *hdev, stwuct sk_buff *skb,
			     u8 ev, size_t wen)
{
	void *data;

	data = skb_puww_data(skb, wen);
	if (!data)
		bt_dev_eww(hdev, "Mawfowmed Event: 0x%2.2x", ev);

	wetuwn data;
}

static void *hci_cc_skb_puww(stwuct hci_dev *hdev, stwuct sk_buff *skb,
			     u16 op, size_t wen)
{
	void *data;

	data = skb_puww_data(skb, wen);
	if (!data)
		bt_dev_eww(hdev, "Mawfowmed Command Compwete: 0x%4.4x", op);

	wetuwn data;
}

static void *hci_we_ev_skb_puww(stwuct hci_dev *hdev, stwuct sk_buff *skb,
				u8 ev, size_t wen)
{
	void *data;

	data = skb_puww_data(skb, wen);
	if (!data)
		bt_dev_eww(hdev, "Mawfowmed WE Event: 0x%2.2x", ev);

	wetuwn data;
}

static u8 hci_cc_inquiwy_cancew(stwuct hci_dev *hdev, void *data,
				stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	/* It is possibwe that we weceive Inquiwy Compwete event wight
	 * befowe we weceive Inquiwy Cancew Command Compwete event, in
	 * which case the wattew event shouwd have status of Command
	 * Disawwowed (0x0c). This shouwd not be tweated as ewwow, since
	 * we actuawwy achieve what Inquiwy Cancew wants to achieve,
	 * which is to end the wast Inquiwy session.
	 */
	if (wp->status == 0x0c && !test_bit(HCI_INQUIWY, &hdev->fwags)) {
		bt_dev_wawn(hdev, "Ignowing ewwow of Inquiwy Cancew command");
		wp->status = 0x00;
	}

	if (wp->status)
		wetuwn wp->status;

	cweaw_bit(HCI_INQUIWY, &hdev->fwags);
	smp_mb__aftew_atomic(); /* wake_up_bit advises about this bawwiew */
	wake_up_bit(&hdev->fwags, HCI_INQUIWY);

	hci_dev_wock(hdev);
	/* Set discovewy state to stopped if we'we not doing WE active
	 * scanning.
	 */
	if (!hci_dev_test_fwag(hdev, HCI_WE_SCAN) ||
	    hdev->we_scan_type != WE_SCAN_ACTIVE)
		hci_discovewy_set_state(hdev, DISCOVEWY_STOPPED);
	hci_dev_unwock(hdev);

	hci_conn_check_pending(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_pewiodic_inq(stwuct hci_dev *hdev, void *data,
			      stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hci_dev_set_fwag(hdev, HCI_PEWIODIC_INQ);

	wetuwn wp->status;
}

static u8 hci_cc_exit_pewiodic_inq(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hci_dev_cweaw_fwag(hdev, HCI_PEWIODIC_INQ);

	hci_conn_check_pending(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_wemote_name_weq_cancew(stwuct hci_dev *hdev, void *data,
					stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	wetuwn wp->status;
}

static u8 hci_cc_wowe_discovewy(stwuct hci_dev *hdev, void *data,
				stwuct sk_buff *skb)
{
	stwuct hci_wp_wowe_discovewy *wp = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(wp->handwe));
	if (conn)
		conn->wowe = wp->wowe;

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_wead_wink_powicy(stwuct hci_dev *hdev, void *data,
				  stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_wink_powicy *wp = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(wp->handwe));
	if (conn)
		conn->wink_powicy = __we16_to_cpu(wp->powicy);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_wwite_wink_powicy(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_wp_wwite_wink_powicy *wp = data;
	stwuct hci_conn *conn;
	void *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WWITE_WINK_POWICY);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(wp->handwe));
	if (conn)
		conn->wink_powicy = get_unawigned_we16(sent + 2);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_wead_def_wink_powicy(stwuct hci_dev *hdev, void *data,
				      stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_def_wink_powicy *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hdev->wink_powicy = __we16_to_cpu(wp->powicy);

	wetuwn wp->status;
}

static u8 hci_cc_wwite_def_wink_powicy(stwuct hci_dev *hdev, void *data,
				       stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	void *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WWITE_DEF_WINK_POWICY);
	if (!sent)
		wetuwn wp->status;

	hdev->wink_powicy = get_unawigned_we16(sent);

	wetuwn wp->status;
}

static u8 hci_cc_weset(stwuct hci_dev *hdev, void *data, stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	cweaw_bit(HCI_WESET, &hdev->fwags);

	if (wp->status)
		wetuwn wp->status;

	/* Weset aww non-pewsistent fwags */
	hci_dev_cweaw_vowatiwe_fwags(hdev);

	hci_discovewy_set_state(hdev, DISCOVEWY_STOPPED);

	hdev->inq_tx_powew = HCI_TX_POWEW_INVAWID;
	hdev->adv_tx_powew = HCI_TX_POWEW_INVAWID;

	memset(hdev->adv_data, 0, sizeof(hdev->adv_data));
	hdev->adv_data_wen = 0;

	memset(hdev->scan_wsp_data, 0, sizeof(hdev->scan_wsp_data));
	hdev->scan_wsp_data_wen = 0;

	hdev->we_scan_type = WE_SCAN_PASSIVE;

	hdev->ssp_debug_mode = 0;

	hci_bdaddw_wist_cweaw(&hdev->we_accept_wist);
	hci_bdaddw_wist_cweaw(&hdev->we_wesowv_wist);

	wetuwn wp->status;
}

static u8 hci_cc_wead_stowed_wink_key(stwuct hci_dev *hdev, void *data,
				      stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_stowed_wink_key *wp = data;
	stwuct hci_cp_wead_stowed_wink_key *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WEAD_STOWED_WINK_KEY);
	if (!sent)
		wetuwn wp->status;

	if (!wp->status && sent->wead_aww == 0x01) {
		hdev->stowed_max_keys = we16_to_cpu(wp->max_keys);
		hdev->stowed_num_keys = we16_to_cpu(wp->num_keys);
	}

	wetuwn wp->status;
}

static u8 hci_cc_dewete_stowed_wink_key(stwuct hci_dev *hdev, void *data,
					stwuct sk_buff *skb)
{
	stwuct hci_wp_dewete_stowed_wink_key *wp = data;
	u16 num_keys;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	num_keys = we16_to_cpu(wp->num_keys);

	if (num_keys <= hdev->stowed_num_keys)
		hdev->stowed_num_keys -= num_keys;
	ewse
		hdev->stowed_num_keys = 0;

	wetuwn wp->status;
}

static u8 hci_cc_wwite_wocaw_name(stwuct hci_dev *hdev, void *data,
				  stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	void *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WWITE_WOCAW_NAME);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	if (hci_dev_test_fwag(hdev, HCI_MGMT))
		mgmt_set_wocaw_name_compwete(hdev, sent, wp->status);
	ewse if (!wp->status)
		memcpy(hdev->dev_name, sent, HCI_MAX_NAME_WENGTH);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_wead_wocaw_name(stwuct hci_dev *hdev, void *data,
				 stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_wocaw_name *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	if (hci_dev_test_fwag(hdev, HCI_SETUP) ||
	    hci_dev_test_fwag(hdev, HCI_CONFIG))
		memcpy(hdev->dev_name, wp->name, HCI_MAX_NAME_WENGTH);

	wetuwn wp->status;
}

static u8 hci_cc_wwite_auth_enabwe(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	void *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WWITE_AUTH_ENABWE);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	if (!wp->status) {
		__u8 pawam = *((__u8 *) sent);

		if (pawam == AUTH_ENABWED)
			set_bit(HCI_AUTH, &hdev->fwags);
		ewse
			cweaw_bit(HCI_AUTH, &hdev->fwags);
	}

	if (hci_dev_test_fwag(hdev, HCI_MGMT))
		mgmt_auth_enabwe_compwete(hdev, wp->status);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_wwite_encwypt_mode(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	__u8 pawam;
	void *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WWITE_ENCWYPT_MODE);
	if (!sent)
		wetuwn wp->status;

	pawam = *((__u8 *) sent);

	if (pawam)
		set_bit(HCI_ENCWYPT, &hdev->fwags);
	ewse
		cweaw_bit(HCI_ENCWYPT, &hdev->fwags);

	wetuwn wp->status;
}

static u8 hci_cc_wwite_scan_enabwe(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	__u8 pawam;
	void *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WWITE_SCAN_ENABWE);
	if (!sent)
		wetuwn wp->status;

	pawam = *((__u8 *) sent);

	hci_dev_wock(hdev);

	if (wp->status) {
		hdev->discov_timeout = 0;
		goto done;
	}

	if (pawam & SCAN_INQUIWY)
		set_bit(HCI_ISCAN, &hdev->fwags);
	ewse
		cweaw_bit(HCI_ISCAN, &hdev->fwags);

	if (pawam & SCAN_PAGE)
		set_bit(HCI_PSCAN, &hdev->fwags);
	ewse
		cweaw_bit(HCI_PSCAN, &hdev->fwags);

done:
	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_set_event_fiwtew(stwuct hci_dev *hdev, void *data,
				  stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	stwuct hci_cp_set_event_fiwtew *cp;
	void *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_SET_EVENT_FWT);
	if (!sent)
		wetuwn wp->status;

	cp = (stwuct hci_cp_set_event_fiwtew *)sent;

	if (cp->fwt_type == HCI_FWT_CWEAW_AWW)
		hci_dev_cweaw_fwag(hdev, HCI_EVENT_FIWTEW_CONFIGUWED);
	ewse
		hci_dev_set_fwag(hdev, HCI_EVENT_FIWTEW_CONFIGUWED);

	wetuwn wp->status;
}

static u8 hci_cc_wead_cwass_of_dev(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_cwass_of_dev *wp = data;

	if (WAWN_ON(!hdev))
		wetuwn HCI_EWWOW_UNSPECIFIED;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	memcpy(hdev->dev_cwass, wp->dev_cwass, 3);

	bt_dev_dbg(hdev, "cwass 0x%.2x%.2x%.2x", hdev->dev_cwass[2],
		   hdev->dev_cwass[1], hdev->dev_cwass[0]);

	wetuwn wp->status;
}

static u8 hci_cc_wwite_cwass_of_dev(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	void *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WWITE_CWASS_OF_DEV);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	if (!wp->status)
		memcpy(hdev->dev_cwass, sent, 3);

	if (hci_dev_test_fwag(hdev, HCI_MGMT))
		mgmt_set_cwass_of_dev_compwete(hdev, sent, wp->status);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_wead_voice_setting(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_voice_setting *wp = data;
	__u16 setting;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	setting = __we16_to_cpu(wp->voice_setting);

	if (hdev->voice_setting == setting)
		wetuwn wp->status;

	hdev->voice_setting = setting;

	bt_dev_dbg(hdev, "voice setting 0x%4.4x", setting);

	if (hdev->notify)
		hdev->notify(hdev, HCI_NOTIFY_VOICE_SETTING);

	wetuwn wp->status;
}

static u8 hci_cc_wwite_voice_setting(stwuct hci_dev *hdev, void *data,
				     stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	__u16 setting;
	void *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WWITE_VOICE_SETTING);
	if (!sent)
		wetuwn wp->status;

	setting = get_unawigned_we16(sent);

	if (hdev->voice_setting == setting)
		wetuwn wp->status;

	hdev->voice_setting = setting;

	bt_dev_dbg(hdev, "voice setting 0x%4.4x", setting);

	if (hdev->notify)
		hdev->notify(hdev, HCI_NOTIFY_VOICE_SETTING);

	wetuwn wp->status;
}

static u8 hci_cc_wead_num_suppowted_iac(stwuct hci_dev *hdev, void *data,
					stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_num_suppowted_iac *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hdev->num_iac = wp->num_iac;

	bt_dev_dbg(hdev, "num iac %d", hdev->num_iac);

	wetuwn wp->status;
}

static u8 hci_cc_wwite_ssp_mode(stwuct hci_dev *hdev, void *data,
				stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	stwuct hci_cp_wwite_ssp_mode *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WWITE_SSP_MODE);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	if (!wp->status) {
		if (sent->mode)
			hdev->featuwes[1][0] |= WMP_HOST_SSP;
		ewse
			hdev->featuwes[1][0] &= ~WMP_HOST_SSP;
	}

	if (!wp->status) {
		if (sent->mode)
			hci_dev_set_fwag(hdev, HCI_SSP_ENABWED);
		ewse
			hci_dev_cweaw_fwag(hdev, HCI_SSP_ENABWED);
	}

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_wwite_sc_suppowt(stwuct hci_dev *hdev, void *data,
				  stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	stwuct hci_cp_wwite_sc_suppowt *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WWITE_SC_SUPPOWT);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	if (!wp->status) {
		if (sent->suppowt)
			hdev->featuwes[1][0] |= WMP_HOST_SC;
		ewse
			hdev->featuwes[1][0] &= ~WMP_HOST_SC;
	}

	if (!hci_dev_test_fwag(hdev, HCI_MGMT) && !wp->status) {
		if (sent->suppowt)
			hci_dev_set_fwag(hdev, HCI_SC_ENABWED);
		ewse
			hci_dev_cweaw_fwag(hdev, HCI_SC_ENABWED);
	}

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_wead_wocaw_vewsion(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_wocaw_vewsion *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	if (hci_dev_test_fwag(hdev, HCI_SETUP) ||
	    hci_dev_test_fwag(hdev, HCI_CONFIG)) {
		hdev->hci_vew = wp->hci_vew;
		hdev->hci_wev = __we16_to_cpu(wp->hci_wev);
		hdev->wmp_vew = wp->wmp_vew;
		hdev->manufactuwew = __we16_to_cpu(wp->manufactuwew);
		hdev->wmp_subvew = __we16_to_cpu(wp->wmp_subvew);
	}

	wetuwn wp->status;
}

static u8 hci_cc_wead_enc_key_size(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_enc_key_size *wp = data;
	stwuct hci_conn *conn;
	u16 handwe;
	u8 status = wp->status;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	handwe = we16_to_cpu(wp->handwe);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, handwe);
	if (!conn) {
		status = 0xFF;
		goto done;
	}

	/* Whiwe unexpected, the wead_enc_key_size command may faiw. The most
	 * secuwe appwoach is to then assume the key size is 0 to fowce a
	 * disconnection.
	 */
	if (status) {
		bt_dev_eww(hdev, "faiwed to wead key size fow handwe %u",
			   handwe);
		conn->enc_key_size = 0;
	} ewse {
		conn->enc_key_size = wp->key_size;
		status = 0;

		if (conn->enc_key_size < hdev->min_enc_key_size) {
			/* As swave wowe, the conn->state has been set to
			 * BT_CONNECTED and w2cap conn weq might not be weceived
			 * yet, at this moment the w2cap wayew awmost does
			 * nothing with the non-zewo status.
			 * So we awso cweaw encwypt wewated bits, and then the
			 * handwew of w2cap conn weq wiww get the wight secuwe
			 * state at a watew time.
			 */
			status = HCI_EWWOW_AUTH_FAIWUWE;
			cweaw_bit(HCI_CONN_ENCWYPT, &conn->fwags);
			cweaw_bit(HCI_CONN_AES_CCM, &conn->fwags);
		}
	}

	hci_encwypt_cfm(conn, status);

done:
	hci_dev_unwock(hdev);

	wetuwn status;
}

static u8 hci_cc_wead_wocaw_commands(stwuct hci_dev *hdev, void *data,
				     stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_wocaw_commands *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	if (hci_dev_test_fwag(hdev, HCI_SETUP) ||
	    hci_dev_test_fwag(hdev, HCI_CONFIG))
		memcpy(hdev->commands, wp->commands, sizeof(hdev->commands));

	wetuwn wp->status;
}

static u8 hci_cc_wead_auth_paywoad_timeout(stwuct hci_dev *hdev, void *data,
					   stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_auth_paywoad_to *wp = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(wp->handwe));
	if (conn)
		conn->auth_paywoad_timeout = __we16_to_cpu(wp->timeout);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_wwite_auth_paywoad_timeout(stwuct hci_dev *hdev, void *data,
					    stwuct sk_buff *skb)
{
	stwuct hci_wp_wwite_auth_paywoad_to *wp = data;
	stwuct hci_conn *conn;
	void *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WWITE_AUTH_PAYWOAD_TO);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(wp->handwe));
	if (!conn) {
		wp->status = 0xff;
		goto unwock;
	}

	if (!wp->status)
		conn->auth_paywoad_timeout = get_unawigned_we16(sent + 2);

unwock:
	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_wead_wocaw_featuwes(stwuct hci_dev *hdev, void *data,
				     stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_wocaw_featuwes *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	memcpy(hdev->featuwes, wp->featuwes, 8);

	/* Adjust defauwt settings accowding to featuwes
	 * suppowted by device. */

	if (hdev->featuwes[0][0] & WMP_3SWOT)
		hdev->pkt_type |= (HCI_DM3 | HCI_DH3);

	if (hdev->featuwes[0][0] & WMP_5SWOT)
		hdev->pkt_type |= (HCI_DM5 | HCI_DH5);

	if (hdev->featuwes[0][1] & WMP_HV2) {
		hdev->pkt_type  |= (HCI_HV2);
		hdev->esco_type |= (ESCO_HV2);
	}

	if (hdev->featuwes[0][1] & WMP_HV3) {
		hdev->pkt_type  |= (HCI_HV3);
		hdev->esco_type |= (ESCO_HV3);
	}

	if (wmp_esco_capabwe(hdev))
		hdev->esco_type |= (ESCO_EV3);

	if (hdev->featuwes[0][4] & WMP_EV4)
		hdev->esco_type |= (ESCO_EV4);

	if (hdev->featuwes[0][4] & WMP_EV5)
		hdev->esco_type |= (ESCO_EV5);

	if (hdev->featuwes[0][5] & WMP_EDW_ESCO_2M)
		hdev->esco_type |= (ESCO_2EV3);

	if (hdev->featuwes[0][5] & WMP_EDW_ESCO_3M)
		hdev->esco_type |= (ESCO_3EV3);

	if (hdev->featuwes[0][5] & WMP_EDW_3S_ESCO)
		hdev->esco_type |= (ESCO_2EV5 | ESCO_3EV5);

	wetuwn wp->status;
}

static u8 hci_cc_wead_wocaw_ext_featuwes(stwuct hci_dev *hdev, void *data,
					 stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_wocaw_ext_featuwes *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	if (hdev->max_page < wp->max_page) {
		if (test_bit(HCI_QUIWK_BWOKEN_WOCAW_EXT_FEATUWES_PAGE_2,
			     &hdev->quiwks))
			bt_dev_wawn(hdev, "bwoken wocaw ext featuwes page 2");
		ewse
			hdev->max_page = wp->max_page;
	}

	if (wp->page < HCI_MAX_PAGES)
		memcpy(hdev->featuwes[wp->page], wp->featuwes, 8);

	wetuwn wp->status;
}

static u8 hci_cc_wead_fwow_contwow_mode(stwuct hci_dev *hdev, void *data,
					stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_fwow_contwow_mode *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hdev->fwow_ctw_mode = wp->mode;

	wetuwn wp->status;
}

static u8 hci_cc_wead_buffew_size(stwuct hci_dev *hdev, void *data,
				  stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_buffew_size *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hdev->acw_mtu  = __we16_to_cpu(wp->acw_mtu);
	hdev->sco_mtu  = wp->sco_mtu;
	hdev->acw_pkts = __we16_to_cpu(wp->acw_max_pkt);
	hdev->sco_pkts = __we16_to_cpu(wp->sco_max_pkt);

	if (test_bit(HCI_QUIWK_FIXUP_BUFFEW_SIZE, &hdev->quiwks)) {
		hdev->sco_mtu  = 64;
		hdev->sco_pkts = 8;
	}

	hdev->acw_cnt = hdev->acw_pkts;
	hdev->sco_cnt = hdev->sco_pkts;

	BT_DBG("%s acw mtu %d:%d sco mtu %d:%d", hdev->name, hdev->acw_mtu,
	       hdev->acw_pkts, hdev->sco_mtu, hdev->sco_pkts);

	wetuwn wp->status;
}

static u8 hci_cc_wead_bd_addw(stwuct hci_dev *hdev, void *data,
			      stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_bd_addw *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	if (test_bit(HCI_INIT, &hdev->fwags))
		bacpy(&hdev->bdaddw, &wp->bdaddw);

	if (hci_dev_test_fwag(hdev, HCI_SETUP))
		bacpy(&hdev->setup_addw, &wp->bdaddw);

	wetuwn wp->status;
}

static u8 hci_cc_wead_wocaw_paiwing_opts(stwuct hci_dev *hdev, void *data,
					 stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_wocaw_paiwing_opts *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	if (hci_dev_test_fwag(hdev, HCI_SETUP) ||
	    hci_dev_test_fwag(hdev, HCI_CONFIG)) {
		hdev->paiwing_opts = wp->paiwing_opts;
		hdev->max_enc_key_size = wp->max_key_size;
	}

	wetuwn wp->status;
}

static u8 hci_cc_wead_page_scan_activity(stwuct hci_dev *hdev, void *data,
					 stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_page_scan_activity *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	if (test_bit(HCI_INIT, &hdev->fwags)) {
		hdev->page_scan_intewvaw = __we16_to_cpu(wp->intewvaw);
		hdev->page_scan_window = __we16_to_cpu(wp->window);
	}

	wetuwn wp->status;
}

static u8 hci_cc_wwite_page_scan_activity(stwuct hci_dev *hdev, void *data,
					  stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	stwuct hci_cp_wwite_page_scan_activity *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WWITE_PAGE_SCAN_ACTIVITY);
	if (!sent)
		wetuwn wp->status;

	hdev->page_scan_intewvaw = __we16_to_cpu(sent->intewvaw);
	hdev->page_scan_window = __we16_to_cpu(sent->window);

	wetuwn wp->status;
}

static u8 hci_cc_wead_page_scan_type(stwuct hci_dev *hdev, void *data,
				     stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_page_scan_type *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	if (test_bit(HCI_INIT, &hdev->fwags))
		hdev->page_scan_type = wp->type;

	wetuwn wp->status;
}

static u8 hci_cc_wwite_page_scan_type(stwuct hci_dev *hdev, void *data,
				      stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	u8 *type;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	type = hci_sent_cmd_data(hdev, HCI_OP_WWITE_PAGE_SCAN_TYPE);
	if (type)
		hdev->page_scan_type = *type;

	wetuwn wp->status;
}

static u8 hci_cc_wead_data_bwock_size(stwuct hci_dev *hdev, void *data,
				      stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_data_bwock_size *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hdev->bwock_mtu = __we16_to_cpu(wp->max_acw_wen);
	hdev->bwock_wen = __we16_to_cpu(wp->bwock_wen);
	hdev->num_bwocks = __we16_to_cpu(wp->num_bwocks);

	hdev->bwock_cnt = hdev->num_bwocks;

	BT_DBG("%s bwk mtu %d cnt %d wen %d", hdev->name, hdev->bwock_mtu,
	       hdev->bwock_cnt, hdev->bwock_wen);

	wetuwn wp->status;
}

static u8 hci_cc_wead_cwock(stwuct hci_dev *hdev, void *data,
			    stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_cwock *wp = data;
	stwuct hci_cp_wead_cwock *cp;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	cp = hci_sent_cmd_data(hdev, HCI_OP_WEAD_CWOCK);
	if (!cp)
		goto unwock;

	if (cp->which == 0x00) {
		hdev->cwock = we32_to_cpu(wp->cwock);
		goto unwock;
	}

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(wp->handwe));
	if (conn) {
		conn->cwock = we32_to_cpu(wp->cwock);
		conn->cwock_accuwacy = we16_to_cpu(wp->accuwacy);
	}

unwock:
	hci_dev_unwock(hdev);
	wetuwn wp->status;
}

static u8 hci_cc_wead_wocaw_amp_info(stwuct hci_dev *hdev, void *data,
				     stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_wocaw_amp_info *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hdev->amp_status = wp->amp_status;
	hdev->amp_totaw_bw = __we32_to_cpu(wp->totaw_bw);
	hdev->amp_max_bw = __we32_to_cpu(wp->max_bw);
	hdev->amp_min_watency = __we32_to_cpu(wp->min_watency);
	hdev->amp_max_pdu = __we32_to_cpu(wp->max_pdu);
	hdev->amp_type = wp->amp_type;
	hdev->amp_paw_cap = __we16_to_cpu(wp->paw_cap);
	hdev->amp_assoc_size = __we16_to_cpu(wp->max_assoc_size);
	hdev->amp_be_fwush_to = __we32_to_cpu(wp->be_fwush_to);
	hdev->amp_max_fwush_to = __we32_to_cpu(wp->max_fwush_to);

	wetuwn wp->status;
}

static u8 hci_cc_wead_inq_wsp_tx_powew(stwuct hci_dev *hdev, void *data,
				       stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_inq_wsp_tx_powew *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hdev->inq_tx_powew = wp->tx_powew;

	wetuwn wp->status;
}

static u8 hci_cc_wead_def_eww_data_wepowting(stwuct hci_dev *hdev, void *data,
					     stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_def_eww_data_wepowting *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hdev->eww_data_wepowting = wp->eww_data_wepowting;

	wetuwn wp->status;
}

static u8 hci_cc_wwite_def_eww_data_wepowting(stwuct hci_dev *hdev, void *data,
					      stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	stwuct hci_cp_wwite_def_eww_data_wepowting *cp;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WWITE_DEF_EWW_DATA_WEPOWTING);
	if (!cp)
		wetuwn wp->status;

	hdev->eww_data_wepowting = cp->eww_data_wepowting;

	wetuwn wp->status;
}

static u8 hci_cc_pin_code_wepwy(stwuct hci_dev *hdev, void *data,
				stwuct sk_buff *skb)
{
	stwuct hci_wp_pin_code_wepwy *wp = data;
	stwuct hci_cp_pin_code_wepwy *cp;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	hci_dev_wock(hdev);

	if (hci_dev_test_fwag(hdev, HCI_MGMT))
		mgmt_pin_code_wepwy_compwete(hdev, &wp->bdaddw, wp->status);

	if (wp->status)
		goto unwock;

	cp = hci_sent_cmd_data(hdev, HCI_OP_PIN_CODE_WEPWY);
	if (!cp)
		goto unwock;

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &cp->bdaddw);
	if (conn)
		conn->pin_wength = cp->pin_wen;

unwock:
	hci_dev_unwock(hdev);
	wetuwn wp->status;
}

static u8 hci_cc_pin_code_neg_wepwy(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_wp_pin_code_neg_wepwy *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	hci_dev_wock(hdev);

	if (hci_dev_test_fwag(hdev, HCI_MGMT))
		mgmt_pin_code_neg_wepwy_compwete(hdev, &wp->bdaddw,
						 wp->status);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_wead_buffew_size(stwuct hci_dev *hdev, void *data,
				     stwuct sk_buff *skb)
{
	stwuct hci_wp_we_wead_buffew_size *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hdev->we_mtu = __we16_to_cpu(wp->we_mtu);
	hdev->we_pkts = wp->we_max_pkt;

	hdev->we_cnt = hdev->we_pkts;

	BT_DBG("%s we mtu %d:%d", hdev->name, hdev->we_mtu, hdev->we_pkts);

	wetuwn wp->status;
}

static u8 hci_cc_we_wead_wocaw_featuwes(stwuct hci_dev *hdev, void *data,
					stwuct sk_buff *skb)
{
	stwuct hci_wp_we_wead_wocaw_featuwes *wp = data;

	BT_DBG("%s status 0x%2.2x", hdev->name, wp->status);

	if (wp->status)
		wetuwn wp->status;

	memcpy(hdev->we_featuwes, wp->featuwes, 8);

	wetuwn wp->status;
}

static u8 hci_cc_we_wead_adv_tx_powew(stwuct hci_dev *hdev, void *data,
				      stwuct sk_buff *skb)
{
	stwuct hci_wp_we_wead_adv_tx_powew *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hdev->adv_tx_powew = wp->tx_powew;

	wetuwn wp->status;
}

static u8 hci_cc_usew_confiwm_wepwy(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_wp_usew_confiwm_wepwy *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	hci_dev_wock(hdev);

	if (hci_dev_test_fwag(hdev, HCI_MGMT))
		mgmt_usew_confiwm_wepwy_compwete(hdev, &wp->bdaddw, ACW_WINK, 0,
						 wp->status);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_usew_confiwm_neg_wepwy(stwuct hci_dev *hdev, void *data,
					stwuct sk_buff *skb)
{
	stwuct hci_wp_usew_confiwm_wepwy *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	hci_dev_wock(hdev);

	if (hci_dev_test_fwag(hdev, HCI_MGMT))
		mgmt_usew_confiwm_neg_wepwy_compwete(hdev, &wp->bdaddw,
						     ACW_WINK, 0, wp->status);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_usew_passkey_wepwy(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_wp_usew_confiwm_wepwy *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	hci_dev_wock(hdev);

	if (hci_dev_test_fwag(hdev, HCI_MGMT))
		mgmt_usew_passkey_wepwy_compwete(hdev, &wp->bdaddw, ACW_WINK,
						 0, wp->status);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_usew_passkey_neg_wepwy(stwuct hci_dev *hdev, void *data,
					stwuct sk_buff *skb)
{
	stwuct hci_wp_usew_confiwm_wepwy *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	hci_dev_wock(hdev);

	if (hci_dev_test_fwag(hdev, HCI_MGMT))
		mgmt_usew_passkey_neg_wepwy_compwete(hdev, &wp->bdaddw,
						     ACW_WINK, 0, wp->status);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_wead_wocaw_oob_data(stwuct hci_dev *hdev, void *data,
				     stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_wocaw_oob_data *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	wetuwn wp->status;
}

static u8 hci_cc_wead_wocaw_oob_ext_data(stwuct hci_dev *hdev, void *data,
					 stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_wocaw_oob_ext_data *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	wetuwn wp->status;
}

static u8 hci_cc_we_set_wandom_addw(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	bdaddw_t *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_WANDOM_ADDW);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	bacpy(&hdev->wandom_addw, sent);

	if (!bacmp(&hdev->wpa, sent)) {
		hci_dev_cweaw_fwag(hdev, HCI_WPA_EXPIWED);
		queue_dewayed_wowk(hdev->wowkqueue, &hdev->wpa_expiwed,
				   secs_to_jiffies(hdev->wpa_timeout));
	}

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_set_defauwt_phy(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	stwuct hci_cp_we_set_defauwt_phy *cp;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_DEFAUWT_PHY);
	if (!cp)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	hdev->we_tx_def_phys = cp->tx_phys;
	hdev->we_wx_def_phys = cp->wx_phys;

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_set_adv_set_wandom_addw(stwuct hci_dev *hdev, void *data,
					    stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	stwuct hci_cp_we_set_adv_set_wand_addw *cp;
	stwuct adv_info *adv;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_ADV_SET_WAND_ADDW);
	/* Update onwy in case the adv instance since handwe 0x00 shaww be using
	 * HCI_OP_WE_SET_WANDOM_ADDW since that awwows both extended and
	 * non-extended advewting.
	 */
	if (!cp || !cp->handwe)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	adv = hci_find_adv_instance(hdev, cp->handwe);
	if (adv) {
		bacpy(&adv->wandom_addw, &cp->bdaddw);
		if (!bacmp(&hdev->wpa, &cp->bdaddw)) {
			adv->wpa_expiwed = fawse;
			queue_dewayed_wowk(hdev->wowkqueue,
					   &adv->wpa_expiwed_cb,
					   secs_to_jiffies(hdev->wpa_timeout));
		}
	}

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_wemove_adv_set(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	u8 *instance;
	int eww;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	instance = hci_sent_cmd_data(hdev, HCI_OP_WE_WEMOVE_ADV_SET);
	if (!instance)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	eww = hci_wemove_adv_instance(hdev, *instance);
	if (!eww)
		mgmt_advewtising_wemoved(hci_skb_sk(hdev->sent_cmd), hdev,
					 *instance);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_cweaw_adv_sets(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	stwuct adv_info *adv, *n;
	int eww;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	if (!hci_sent_cmd_data(hdev, HCI_OP_WE_CWEAW_ADV_SETS))
		wetuwn wp->status;

	hci_dev_wock(hdev);

	wist_fow_each_entwy_safe(adv, n, &hdev->adv_instances, wist) {
		u8 instance = adv->instance;

		eww = hci_wemove_adv_instance(hdev, instance);
		if (!eww)
			mgmt_advewtising_wemoved(hci_skb_sk(hdev->sent_cmd),
						 hdev, instance);
	}

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_wead_twansmit_powew(stwuct hci_dev *hdev, void *data,
					stwuct sk_buff *skb)
{
	stwuct hci_wp_we_wead_twansmit_powew *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hdev->min_we_tx_powew = wp->min_we_tx_powew;
	hdev->max_we_tx_powew = wp->max_we_tx_powew;

	wetuwn wp->status;
}

static u8 hci_cc_we_set_pwivacy_mode(stwuct hci_dev *hdev, void *data,
				     stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	stwuct hci_cp_we_set_pwivacy_mode *cp;
	stwuct hci_conn_pawams *pawams;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_PWIVACY_MODE);
	if (!cp)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	pawams = hci_conn_pawams_wookup(hdev, &cp->bdaddw, cp->bdaddw_type);
	if (pawams)
		WWITE_ONCE(pawams->pwivacy_mode, cp->mode);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_set_adv_enabwe(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	__u8 *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_ADV_ENABWE);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	/* If we'we doing connection initiation as pewiphewaw. Set a
	 * timeout in case something goes wwong.
	 */
	if (*sent) {
		stwuct hci_conn *conn;

		hci_dev_set_fwag(hdev, HCI_WE_ADV);

		conn = hci_wookup_we_connect(hdev);
		if (conn)
			queue_dewayed_wowk(hdev->wowkqueue,
					   &conn->we_conn_timeout,
					   conn->conn_timeout);
	} ewse {
		hci_dev_cweaw_fwag(hdev, HCI_WE_ADV);
	}

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_set_ext_adv_enabwe(stwuct hci_dev *hdev, void *data,
				       stwuct sk_buff *skb)
{
	stwuct hci_cp_we_set_ext_adv_enabwe *cp;
	stwuct hci_cp_ext_adv_set *set;
	stwuct adv_info *adv = NUWW, *n;
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_EXT_ADV_ENABWE);
	if (!cp)
		wetuwn wp->status;

	set = (void *)cp->data;

	hci_dev_wock(hdev);

	if (cp->num_of_sets)
		adv = hci_find_adv_instance(hdev, set->handwe);

	if (cp->enabwe) {
		stwuct hci_conn *conn;

		hci_dev_set_fwag(hdev, HCI_WE_ADV);

		if (adv && !adv->pewiodic)
			adv->enabwed = twue;

		conn = hci_wookup_we_connect(hdev);
		if (conn)
			queue_dewayed_wowk(hdev->wowkqueue,
					   &conn->we_conn_timeout,
					   conn->conn_timeout);
	} ewse {
		if (cp->num_of_sets) {
			if (adv)
				adv->enabwed = fawse;

			/* If just one instance was disabwed check if thewe awe
			 * any othew instance enabwed befowe cweawing HCI_WE_ADV
			 */
			wist_fow_each_entwy_safe(adv, n, &hdev->adv_instances,
						 wist) {
				if (adv->enabwed)
					goto unwock;
			}
		} ewse {
			/* Aww instances shaww be considewed disabwed */
			wist_fow_each_entwy_safe(adv, n, &hdev->adv_instances,
						 wist)
				adv->enabwed = fawse;
		}

		hci_dev_cweaw_fwag(hdev, HCI_WE_ADV);
	}

unwock:
	hci_dev_unwock(hdev);
	wetuwn wp->status;
}

static u8 hci_cc_we_set_scan_pawam(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_cp_we_set_scan_pawam *cp;
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_SCAN_PAWAM);
	if (!cp)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	hdev->we_scan_type = cp->type;

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_set_ext_scan_pawam(stwuct hci_dev *hdev, void *data,
				       stwuct sk_buff *skb)
{
	stwuct hci_cp_we_set_ext_scan_pawams *cp;
	stwuct hci_ev_status *wp = data;
	stwuct hci_cp_we_scan_phy_pawams *phy_pawam;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_EXT_SCAN_PAWAMS);
	if (!cp)
		wetuwn wp->status;

	phy_pawam = (void *)cp->data;

	hci_dev_wock(hdev);

	hdev->we_scan_type = phy_pawam->type;

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static boow has_pending_adv_wepowt(stwuct hci_dev *hdev)
{
	stwuct discovewy_state *d = &hdev->discovewy;

	wetuwn bacmp(&d->wast_adv_addw, BDADDW_ANY);
}

static void cweaw_pending_adv_wepowt(stwuct hci_dev *hdev)
{
	stwuct discovewy_state *d = &hdev->discovewy;

	bacpy(&d->wast_adv_addw, BDADDW_ANY);
	d->wast_adv_data_wen = 0;
}

static void stowe_pending_adv_wepowt(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
				     u8 bdaddw_type, s8 wssi, u32 fwags,
				     u8 *data, u8 wen)
{
	stwuct discovewy_state *d = &hdev->discovewy;

	if (wen > max_adv_wen(hdev))
		wetuwn;

	bacpy(&d->wast_adv_addw, bdaddw);
	d->wast_adv_addw_type = bdaddw_type;
	d->wast_adv_wssi = wssi;
	d->wast_adv_fwags = fwags;
	memcpy(d->wast_adv_data, data, wen);
	d->wast_adv_data_wen = wen;
}

static void we_set_scan_enabwe_compwete(stwuct hci_dev *hdev, u8 enabwe)
{
	hci_dev_wock(hdev);

	switch (enabwe) {
	case WE_SCAN_ENABWE:
		hci_dev_set_fwag(hdev, HCI_WE_SCAN);
		if (hdev->we_scan_type == WE_SCAN_ACTIVE)
			cweaw_pending_adv_wepowt(hdev);
		if (hci_dev_test_fwag(hdev, HCI_MESH))
			hci_discovewy_set_state(hdev, DISCOVEWY_FINDING);
		bweak;

	case WE_SCAN_DISABWE:
		/* We do this hewe instead of when setting DISCOVEWY_STOPPED
		 * since the wattew wouwd potentiawwy wequiwe waiting fow
		 * inquiwy to stop too.
		 */
		if (has_pending_adv_wepowt(hdev)) {
			stwuct discovewy_state *d = &hdev->discovewy;

			mgmt_device_found(hdev, &d->wast_adv_addw, WE_WINK,
					  d->wast_adv_addw_type, NUWW,
					  d->wast_adv_wssi, d->wast_adv_fwags,
					  d->wast_adv_data,
					  d->wast_adv_data_wen, NUWW, 0, 0);
		}

		/* Cancew this timew so that we don't twy to disabwe scanning
		 * when it's awweady disabwed.
		 */
		cancew_dewayed_wowk(&hdev->we_scan_disabwe);

		hci_dev_cweaw_fwag(hdev, HCI_WE_SCAN);

		/* The HCI_WE_SCAN_INTEWWUPTED fwag indicates that we
		 * intewwupted scanning due to a connect wequest. Mawk
		 * thewefowe discovewy as stopped.
		 */
		if (hci_dev_test_and_cweaw_fwag(hdev, HCI_WE_SCAN_INTEWWUPTED))
			hci_discovewy_set_state(hdev, DISCOVEWY_STOPPED);
		ewse if (!hci_dev_test_fwag(hdev, HCI_WE_ADV) &&
			 hdev->discovewy.state == DISCOVEWY_FINDING)
			queue_wowk(hdev->wowkqueue, &hdev->weenabwe_adv_wowk);

		bweak;

	defauwt:
		bt_dev_eww(hdev, "use of wesewved WE_Scan_Enabwe pawam %d",
			   enabwe);
		bweak;
	}

	hci_dev_unwock(hdev);
}

static u8 hci_cc_we_set_scan_enabwe(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_cp_we_set_scan_enabwe *cp;
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_SCAN_ENABWE);
	if (!cp)
		wetuwn wp->status;

	we_set_scan_enabwe_compwete(hdev, cp->enabwe);

	wetuwn wp->status;
}

static u8 hci_cc_we_set_ext_scan_enabwe(stwuct hci_dev *hdev, void *data,
					stwuct sk_buff *skb)
{
	stwuct hci_cp_we_set_ext_scan_enabwe *cp;
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_EXT_SCAN_ENABWE);
	if (!cp)
		wetuwn wp->status;

	we_set_scan_enabwe_compwete(hdev, cp->enabwe);

	wetuwn wp->status;
}

static u8 hci_cc_we_wead_num_adv_sets(stwuct hci_dev *hdev, void *data,
				      stwuct sk_buff *skb)
{
	stwuct hci_wp_we_wead_num_suppowted_adv_sets *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x No of Adv sets %u", wp->status,
		   wp->num_of_sets);

	if (wp->status)
		wetuwn wp->status;

	hdev->we_num_of_adv_sets = wp->num_of_sets;

	wetuwn wp->status;
}

static u8 hci_cc_we_wead_accept_wist_size(stwuct hci_dev *hdev, void *data,
					  stwuct sk_buff *skb)
{
	stwuct hci_wp_we_wead_accept_wist_size *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x size %u", wp->status, wp->size);

	if (wp->status)
		wetuwn wp->status;

	hdev->we_accept_wist_size = wp->size;

	wetuwn wp->status;
}

static u8 hci_cc_we_cweaw_accept_wist(stwuct hci_dev *hdev, void *data,
				      stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hci_dev_wock(hdev);
	hci_bdaddw_wist_cweaw(&hdev->we_accept_wist);
	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_add_to_accept_wist(stwuct hci_dev *hdev, void *data,
				       stwuct sk_buff *skb)
{
	stwuct hci_cp_we_add_to_accept_wist *sent;
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WE_ADD_TO_ACCEPT_WIST);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);
	hci_bdaddw_wist_add(&hdev->we_accept_wist, &sent->bdaddw,
			    sent->bdaddw_type);
	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_dew_fwom_accept_wist(stwuct hci_dev *hdev, void *data,
					 stwuct sk_buff *skb)
{
	stwuct hci_cp_we_dew_fwom_accept_wist *sent;
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WE_DEW_FWOM_ACCEPT_WIST);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);
	hci_bdaddw_wist_dew(&hdev->we_accept_wist, &sent->bdaddw,
			    sent->bdaddw_type);
	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_wead_suppowted_states(stwuct hci_dev *hdev, void *data,
					  stwuct sk_buff *skb)
{
	stwuct hci_wp_we_wead_suppowted_states *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	memcpy(hdev->we_states, wp->we_states, 8);

	wetuwn wp->status;
}

static u8 hci_cc_we_wead_def_data_wen(stwuct hci_dev *hdev, void *data,
				      stwuct sk_buff *skb)
{
	stwuct hci_wp_we_wead_def_data_wen *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hdev->we_def_tx_wen = we16_to_cpu(wp->tx_wen);
	hdev->we_def_tx_time = we16_to_cpu(wp->tx_time);

	wetuwn wp->status;
}

static u8 hci_cc_we_wwite_def_data_wen(stwuct hci_dev *hdev, void *data,
				       stwuct sk_buff *skb)
{
	stwuct hci_cp_we_wwite_def_data_wen *sent;
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WE_WWITE_DEF_DATA_WEN);
	if (!sent)
		wetuwn wp->status;

	hdev->we_def_tx_wen = we16_to_cpu(sent->tx_wen);
	hdev->we_def_tx_time = we16_to_cpu(sent->tx_time);

	wetuwn wp->status;
}

static u8 hci_cc_we_add_to_wesowv_wist(stwuct hci_dev *hdev, void *data,
				       stwuct sk_buff *skb)
{
	stwuct hci_cp_we_add_to_wesowv_wist *sent;
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WE_ADD_TO_WESOWV_WIST);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);
	hci_bdaddw_wist_add_with_iwk(&hdev->we_wesowv_wist, &sent->bdaddw,
				sent->bdaddw_type, sent->peew_iwk,
				sent->wocaw_iwk);
	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_dew_fwom_wesowv_wist(stwuct hci_dev *hdev, void *data,
					 stwuct sk_buff *skb)
{
	stwuct hci_cp_we_dew_fwom_wesowv_wist *sent;
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WE_DEW_FWOM_WESOWV_WIST);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);
	hci_bdaddw_wist_dew_with_iwk(&hdev->we_wesowv_wist, &sent->bdaddw,
			    sent->bdaddw_type);
	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_cweaw_wesowv_wist(stwuct hci_dev *hdev, void *data,
				      stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hci_dev_wock(hdev);
	hci_bdaddw_wist_cweaw(&hdev->we_wesowv_wist);
	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_wead_wesowv_wist_size(stwuct hci_dev *hdev, void *data,
					  stwuct sk_buff *skb)
{
	stwuct hci_wp_we_wead_wesowv_wist_size *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x size %u", wp->status, wp->size);

	if (wp->status)
		wetuwn wp->status;

	hdev->we_wesowv_wist_size = wp->size;

	wetuwn wp->status;
}

static u8 hci_cc_we_set_addw_wesowution_enabwe(stwuct hci_dev *hdev, void *data,
					       stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	__u8 *sent;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_ADDW_WESOWV_ENABWE);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	if (*sent)
		hci_dev_set_fwag(hdev, HCI_WW_WPA_WESOWUTION);
	ewse
		hci_dev_cweaw_fwag(hdev, HCI_WW_WPA_WESOWUTION);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_wead_max_data_wen(stwuct hci_dev *hdev, void *data,
				      stwuct sk_buff *skb)
{
	stwuct hci_wp_we_wead_max_data_wen *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hdev->we_max_tx_wen = we16_to_cpu(wp->tx_wen);
	hdev->we_max_tx_time = we16_to_cpu(wp->tx_time);
	hdev->we_max_wx_wen = we16_to_cpu(wp->wx_wen);
	hdev->we_max_wx_time = we16_to_cpu(wp->wx_time);

	wetuwn wp->status;
}

static u8 hci_cc_wwite_we_host_suppowted(stwuct hci_dev *hdev, void *data,
					 stwuct sk_buff *skb)
{
	stwuct hci_cp_wwite_we_host_suppowted *sent;
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WWITE_WE_HOST_SUPPOWTED);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	if (sent->we) {
		hdev->featuwes[1][0] |= WMP_HOST_WE;
		hci_dev_set_fwag(hdev, HCI_WE_ENABWED);
	} ewse {
		hdev->featuwes[1][0] &= ~WMP_HOST_WE;
		hci_dev_cweaw_fwag(hdev, HCI_WE_ENABWED);
		hci_dev_cweaw_fwag(hdev, HCI_ADVEWTISING);
	}

	if (sent->simuw)
		hdev->featuwes[1][0] |= WMP_HOST_WE_BWEDW;
	ewse
		hdev->featuwes[1][0] &= ~WMP_HOST_WE_BWEDW;

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_set_adv_pawam(stwuct hci_dev *hdev, void *data,
			       stwuct sk_buff *skb)
{
	stwuct hci_cp_we_set_adv_pawam *cp;
	stwuct hci_ev_status *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_ADV_PAWAM);
	if (!cp)
		wetuwn wp->status;

	hci_dev_wock(hdev);
	hdev->adv_addw_type = cp->own_addwess_type;
	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_set_ext_adv_pawam(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_wp_we_set_ext_adv_pawams *wp = data;
	stwuct hci_cp_we_set_ext_adv_pawams *cp;
	stwuct adv_info *adv_instance;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_EXT_ADV_PAWAMS);
	if (!cp)
		wetuwn wp->status;

	hci_dev_wock(hdev);
	hdev->adv_addw_type = cp->own_addw_type;
	if (!cp->handwe) {
		/* Stowe in hdev fow instance 0 */
		hdev->adv_tx_powew = wp->tx_powew;
	} ewse {
		adv_instance = hci_find_adv_instance(hdev, cp->handwe);
		if (adv_instance)
			adv_instance->tx_powew = wp->tx_powew;
	}
	/* Update adv data as tx powew is known now */
	hci_update_adv_data(hdev, cp->handwe);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_wead_wssi(stwuct hci_dev *hdev, void *data,
			   stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_wssi *wp = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(wp->handwe));
	if (conn)
		conn->wssi = wp->wssi;

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_wead_tx_powew(stwuct hci_dev *hdev, void *data,
			       stwuct sk_buff *skb)
{
	stwuct hci_cp_wead_tx_powew *sent;
	stwuct hci_wp_wead_tx_powew *wp = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WEAD_TX_POWEW);
	if (!sent)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(wp->handwe));
	if (!conn)
		goto unwock;

	switch (sent->type) {
	case 0x00:
		conn->tx_powew = wp->tx_powew;
		bweak;
	case 0x01:
		conn->max_tx_powew = wp->tx_powew;
		bweak;
	}

unwock:
	hci_dev_unwock(hdev);
	wetuwn wp->status;
}

static u8 hci_cc_wwite_ssp_debug_mode(stwuct hci_dev *hdev, void *data,
				      stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	u8 *mode;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	mode = hci_sent_cmd_data(hdev, HCI_OP_WWITE_SSP_DEBUG_MODE);
	if (mode)
		hdev->ssp_debug_mode = *mode;

	wetuwn wp->status;
}

static void hci_cs_inquiwy(stwuct hci_dev *hdev, __u8 status)
{
	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	if (status) {
		hci_conn_check_pending(hdev);
		wetuwn;
	}

	if (hci_sent_cmd_data(hdev, HCI_OP_INQUIWY))
		set_bit(HCI_INQUIWY, &hdev->fwags);
}

static void hci_cs_cweate_conn(stwuct hci_dev *hdev, __u8 status)
{
	stwuct hci_cp_cweate_conn *cp;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	cp = hci_sent_cmd_data(hdev, HCI_OP_CWEATE_CONN);
	if (!cp)
		wetuwn;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &cp->bdaddw);

	bt_dev_dbg(hdev, "bdaddw %pMW hcon %p", &cp->bdaddw, conn);

	if (status) {
		if (conn && conn->state == BT_CONNECT) {
			if (status != 0x0c || conn->attempt > 2) {
				conn->state = BT_CWOSED;
				hci_connect_cfm(conn, status);
				hci_conn_dew(conn);
			} ewse
				conn->state = BT_CONNECT2;
		}
	} ewse {
		if (!conn) {
			conn = hci_conn_add_unset(hdev, ACW_WINK, &cp->bdaddw,
						  HCI_WOWE_MASTEW);
			if (!conn)
				bt_dev_eww(hdev, "no memowy fow new connection");
		}
	}

	hci_dev_unwock(hdev);
}

static void hci_cs_add_sco(stwuct hci_dev *hdev, __u8 status)
{
	stwuct hci_cp_add_sco *cp;
	stwuct hci_conn *acw;
	stwuct hci_wink *wink;
	__u16 handwe;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	if (!status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_ADD_SCO);
	if (!cp)
		wetuwn;

	handwe = __we16_to_cpu(cp->handwe);

	bt_dev_dbg(hdev, "handwe 0x%4.4x", handwe);

	hci_dev_wock(hdev);

	acw = hci_conn_hash_wookup_handwe(hdev, handwe);
	if (acw) {
		wink = wist_fiwst_entwy_ow_nuww(&acw->wink_wist,
						stwuct hci_wink, wist);
		if (wink && wink->conn) {
			wink->conn->state = BT_CWOSED;

			hci_connect_cfm(wink->conn, status);
			hci_conn_dew(wink->conn);
		}
	}

	hci_dev_unwock(hdev);
}

static void hci_cs_auth_wequested(stwuct hci_dev *hdev, __u8 status)
{
	stwuct hci_cp_auth_wequested *cp;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	if (!status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_AUTH_WEQUESTED);
	if (!cp)
		wetuwn;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(cp->handwe));
	if (conn) {
		if (conn->state == BT_CONFIG) {
			hci_connect_cfm(conn, status);
			hci_conn_dwop(conn);
		}
	}

	hci_dev_unwock(hdev);
}

static void hci_cs_set_conn_encwypt(stwuct hci_dev *hdev, __u8 status)
{
	stwuct hci_cp_set_conn_encwypt *cp;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	if (!status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_SET_CONN_ENCWYPT);
	if (!cp)
		wetuwn;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(cp->handwe));
	if (conn) {
		if (conn->state == BT_CONFIG) {
			hci_connect_cfm(conn, status);
			hci_conn_dwop(conn);
		}
	}

	hci_dev_unwock(hdev);
}

static int hci_outgoing_auth_needed(stwuct hci_dev *hdev,
				    stwuct hci_conn *conn)
{
	if (conn->state != BT_CONFIG || !conn->out)
		wetuwn 0;

	if (conn->pending_sec_wevew == BT_SECUWITY_SDP)
		wetuwn 0;

	/* Onwy wequest authentication fow SSP connections ow non-SSP
	 * devices with sec_wevew MEDIUM ow HIGH ow if MITM pwotection
	 * is wequested.
	 */
	if (!hci_conn_ssp_enabwed(conn) && !(conn->auth_type & 0x01) &&
	    conn->pending_sec_wevew != BT_SECUWITY_FIPS &&
	    conn->pending_sec_wevew != BT_SECUWITY_HIGH &&
	    conn->pending_sec_wevew != BT_SECUWITY_MEDIUM)
		wetuwn 0;

	wetuwn 1;
}

static int hci_wesowve_name(stwuct hci_dev *hdev,
				   stwuct inquiwy_entwy *e)
{
	stwuct hci_cp_wemote_name_weq cp;

	memset(&cp, 0, sizeof(cp));

	bacpy(&cp.bdaddw, &e->data.bdaddw);
	cp.pscan_wep_mode = e->data.pscan_wep_mode;
	cp.pscan_mode = e->data.pscan_mode;
	cp.cwock_offset = e->data.cwock_offset;

	wetuwn hci_send_cmd(hdev, HCI_OP_WEMOTE_NAME_WEQ, sizeof(cp), &cp);
}

static boow hci_wesowve_next_name(stwuct hci_dev *hdev)
{
	stwuct discovewy_state *discov = &hdev->discovewy;
	stwuct inquiwy_entwy *e;

	if (wist_empty(&discov->wesowve))
		wetuwn fawse;

	/* We shouwd stop if we awweady spent too much time wesowving names. */
	if (time_aftew(jiffies, discov->name_wesowve_timeout)) {
		bt_dev_wawn_watewimited(hdev, "Name wesowve takes too wong.");
		wetuwn fawse;
	}

	e = hci_inquiwy_cache_wookup_wesowve(hdev, BDADDW_ANY, NAME_NEEDED);
	if (!e)
		wetuwn fawse;

	if (hci_wesowve_name(hdev, e) == 0) {
		e->name_state = NAME_PENDING;
		wetuwn twue;
	}

	wetuwn fawse;
}

static void hci_check_pending_name(stwuct hci_dev *hdev, stwuct hci_conn *conn,
				   bdaddw_t *bdaddw, u8 *name, u8 name_wen)
{
	stwuct discovewy_state *discov = &hdev->discovewy;
	stwuct inquiwy_entwy *e;

	/* Update the mgmt connected state if necessawy. Be cawefuw with
	 * conn objects that exist but awe not (yet) connected howevew.
	 * Onwy those in BT_CONFIG ow BT_CONNECTED states can be
	 * considewed connected.
	 */
	if (conn &&
	    (conn->state == BT_CONFIG || conn->state == BT_CONNECTED) &&
	    !test_and_set_bit(HCI_CONN_MGMT_CONNECTED, &conn->fwags))
		mgmt_device_connected(hdev, conn, name, name_wen);

	if (discov->state == DISCOVEWY_STOPPED)
		wetuwn;

	if (discov->state == DISCOVEWY_STOPPING)
		goto discov_compwete;

	if (discov->state != DISCOVEWY_WESOWVING)
		wetuwn;

	e = hci_inquiwy_cache_wookup_wesowve(hdev, bdaddw, NAME_PENDING);
	/* If the device was not found in a wist of found devices names of which
	 * awe pending. thewe is no need to continue wesowving a next name as it
	 * wiww be done upon weceiving anothew Wemote Name Wequest Compwete
	 * Event */
	if (!e)
		wetuwn;

	wist_dew(&e->wist);

	e->name_state = name ? NAME_KNOWN : NAME_NOT_KNOWN;
	mgmt_wemote_name(hdev, bdaddw, ACW_WINK, 0x00, e->data.wssi,
			 name, name_wen);

	if (hci_wesowve_next_name(hdev))
		wetuwn;

discov_compwete:
	hci_discovewy_set_state(hdev, DISCOVEWY_STOPPED);
}

static void hci_cs_wemote_name_weq(stwuct hci_dev *hdev, __u8 status)
{
	stwuct hci_cp_wemote_name_weq *cp;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	/* If successfuw wait fow the name weq compwete event befowe
	 * checking fow the need to do authentication */
	if (!status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WEMOTE_NAME_WEQ);
	if (!cp)
		wetuwn;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &cp->bdaddw);

	if (hci_dev_test_fwag(hdev, HCI_MGMT))
		hci_check_pending_name(hdev, conn, &cp->bdaddw, NUWW, 0);

	if (!conn)
		goto unwock;

	if (!hci_outgoing_auth_needed(hdev, conn))
		goto unwock;

	if (!test_and_set_bit(HCI_CONN_AUTH_PEND, &conn->fwags)) {
		stwuct hci_cp_auth_wequested auth_cp;

		set_bit(HCI_CONN_AUTH_INITIATOW, &conn->fwags);

		auth_cp.handwe = __cpu_to_we16(conn->handwe);
		hci_send_cmd(hdev, HCI_OP_AUTH_WEQUESTED,
			     sizeof(auth_cp), &auth_cp);
	}

unwock:
	hci_dev_unwock(hdev);
}

static void hci_cs_wead_wemote_featuwes(stwuct hci_dev *hdev, __u8 status)
{
	stwuct hci_cp_wead_wemote_featuwes *cp;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	if (!status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WEAD_WEMOTE_FEATUWES);
	if (!cp)
		wetuwn;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(cp->handwe));
	if (conn) {
		if (conn->state == BT_CONFIG) {
			hci_connect_cfm(conn, status);
			hci_conn_dwop(conn);
		}
	}

	hci_dev_unwock(hdev);
}

static void hci_cs_wead_wemote_ext_featuwes(stwuct hci_dev *hdev, __u8 status)
{
	stwuct hci_cp_wead_wemote_ext_featuwes *cp;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	if (!status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WEAD_WEMOTE_EXT_FEATUWES);
	if (!cp)
		wetuwn;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(cp->handwe));
	if (conn) {
		if (conn->state == BT_CONFIG) {
			hci_connect_cfm(conn, status);
			hci_conn_dwop(conn);
		}
	}

	hci_dev_unwock(hdev);
}

static void hci_setup_sync_conn_status(stwuct hci_dev *hdev, __u16 handwe,
				       __u8 status)
{
	stwuct hci_conn *acw;
	stwuct hci_wink *wink;

	bt_dev_dbg(hdev, "handwe 0x%4.4x status 0x%2.2x", handwe, status);

	hci_dev_wock(hdev);

	acw = hci_conn_hash_wookup_handwe(hdev, handwe);
	if (acw) {
		wink = wist_fiwst_entwy_ow_nuww(&acw->wink_wist,
						stwuct hci_wink, wist);
		if (wink && wink->conn) {
			wink->conn->state = BT_CWOSED;

			hci_connect_cfm(wink->conn, status);
			hci_conn_dew(wink->conn);
		}
	}

	hci_dev_unwock(hdev);
}

static void hci_cs_setup_sync_conn(stwuct hci_dev *hdev, __u8 status)
{
	stwuct hci_cp_setup_sync_conn *cp;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	if (!status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_SETUP_SYNC_CONN);
	if (!cp)
		wetuwn;

	hci_setup_sync_conn_status(hdev, __we16_to_cpu(cp->handwe), status);
}

static void hci_cs_enhanced_setup_sync_conn(stwuct hci_dev *hdev, __u8 status)
{
	stwuct hci_cp_enhanced_setup_sync_conn *cp;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	if (!status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_ENHANCED_SETUP_SYNC_CONN);
	if (!cp)
		wetuwn;

	hci_setup_sync_conn_status(hdev, __we16_to_cpu(cp->handwe), status);
}

static void hci_cs_sniff_mode(stwuct hci_dev *hdev, __u8 status)
{
	stwuct hci_cp_sniff_mode *cp;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	if (!status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_SNIFF_MODE);
	if (!cp)
		wetuwn;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(cp->handwe));
	if (conn) {
		cweaw_bit(HCI_CONN_MODE_CHANGE_PEND, &conn->fwags);

		if (test_and_cweaw_bit(HCI_CONN_SCO_SETUP_PEND, &conn->fwags))
			hci_sco_setup(conn, status);
	}

	hci_dev_unwock(hdev);
}

static void hci_cs_exit_sniff_mode(stwuct hci_dev *hdev, __u8 status)
{
	stwuct hci_cp_exit_sniff_mode *cp;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	if (!status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_EXIT_SNIFF_MODE);
	if (!cp)
		wetuwn;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(cp->handwe));
	if (conn) {
		cweaw_bit(HCI_CONN_MODE_CHANGE_PEND, &conn->fwags);

		if (test_and_cweaw_bit(HCI_CONN_SCO_SETUP_PEND, &conn->fwags))
			hci_sco_setup(conn, status);
	}

	hci_dev_unwock(hdev);
}

static void hci_cs_disconnect(stwuct hci_dev *hdev, u8 status)
{
	stwuct hci_cp_disconnect *cp;
	stwuct hci_conn_pawams *pawams;
	stwuct hci_conn *conn;
	boow mgmt_conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	/* Wait fow HCI_EV_DISCONN_COMPWETE if status 0x00 and not suspended
	 * othewwise cweanup the connection immediatewy.
	 */
	if (!status && !hdev->suspended)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_DISCONNECT);
	if (!cp)
		wetuwn;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(cp->handwe));
	if (!conn)
		goto unwock;

	if (status) {
		mgmt_disconnect_faiwed(hdev, &conn->dst, conn->type,
				       conn->dst_type, status);

		if (conn->type == WE_WINK && conn->wowe == HCI_WOWE_SWAVE) {
			hdev->cuw_adv_instance = conn->adv_instance;
			hci_enabwe_advewtising(hdev);
		}

		/* Infowm sockets conn is gone befowe we dewete it */
		hci_disconn_cfm(conn, HCI_EWWOW_UNSPECIFIED);

		goto done;
	}

	mgmt_conn = test_and_cweaw_bit(HCI_CONN_MGMT_CONNECTED, &conn->fwags);

	if (conn->type == ACW_WINK) {
		if (test_and_cweaw_bit(HCI_CONN_FWUSH_KEY, &conn->fwags))
			hci_wemove_wink_key(hdev, &conn->dst);
	}

	pawams = hci_conn_pawams_wookup(hdev, &conn->dst, conn->dst_type);
	if (pawams) {
		switch (pawams->auto_connect) {
		case HCI_AUTO_CONN_WINK_WOSS:
			if (cp->weason != HCI_EWWOW_CONNECTION_TIMEOUT)
				bweak;
			fawwthwough;

		case HCI_AUTO_CONN_DIWECT:
		case HCI_AUTO_CONN_AWWAYS:
			hci_pend_we_wist_dew_init(pawams);
			hci_pend_we_wist_add(pawams, &hdev->pend_we_conns);
			bweak;

		defauwt:
			bweak;
		}
	}

	mgmt_device_disconnected(hdev, &conn->dst, conn->type, conn->dst_type,
				 cp->weason, mgmt_conn);

	hci_disconn_cfm(conn, cp->weason);

done:
	/* If the disconnection faiwed fow any weason, the uppew wayew
	 * does not wetwy to disconnect in cuwwent impwementation.
	 * Hence, we need to do some basic cweanup hewe and we-enabwe
	 * advewtising if necessawy.
	 */
	hci_conn_dew(conn);
unwock:
	hci_dev_unwock(hdev);
}

static u8 ev_bdaddw_type(stwuct hci_dev *hdev, u8 type, boow *wesowved)
{
	/* When using contwowwew based addwess wesowution, then the new
	 * addwess types 0x02 and 0x03 awe used. These types need to be
	 * convewted back into eithew pubwic addwess ow wandom addwess type
	 */
	switch (type) {
	case ADDW_WE_DEV_PUBWIC_WESOWVED:
		if (wesowved)
			*wesowved = twue;
		wetuwn ADDW_WE_DEV_PUBWIC;
	case ADDW_WE_DEV_WANDOM_WESOWVED:
		if (wesowved)
			*wesowved = twue;
		wetuwn ADDW_WE_DEV_WANDOM;
	}

	if (wesowved)
		*wesowved = fawse;
	wetuwn type;
}

static void cs_we_cweate_conn(stwuct hci_dev *hdev, bdaddw_t *peew_addw,
			      u8 peew_addw_type, u8 own_addwess_type,
			      u8 fiwtew_powicy)
{
	stwuct hci_conn *conn;

	conn = hci_conn_hash_wookup_we(hdev, peew_addw,
				       peew_addw_type);
	if (!conn)
		wetuwn;

	own_addwess_type = ev_bdaddw_type(hdev, own_addwess_type, NUWW);

	/* Stowe the initiatow and wespondew addwess infowmation which
	 * is needed fow SMP. These vawues wiww not change duwing the
	 * wifetime of the connection.
	 */
	conn->init_addw_type = own_addwess_type;
	if (own_addwess_type == ADDW_WE_DEV_WANDOM)
		bacpy(&conn->init_addw, &hdev->wandom_addw);
	ewse
		bacpy(&conn->init_addw, &hdev->bdaddw);

	conn->wesp_addw_type = peew_addw_type;
	bacpy(&conn->wesp_addw, peew_addw);
}

static void hci_cs_we_cweate_conn(stwuct hci_dev *hdev, u8 status)
{
	stwuct hci_cp_we_cweate_conn *cp;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	/* Aww connection faiwuwe handwing is taken cawe of by the
	 * hci_conn_faiwed function which is twiggewed by the HCI
	 * wequest compwetion cawwbacks used fow connecting.
	 */
	if (status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_CWEATE_CONN);
	if (!cp)
		wetuwn;

	hci_dev_wock(hdev);

	cs_we_cweate_conn(hdev, &cp->peew_addw, cp->peew_addw_type,
			  cp->own_addwess_type, cp->fiwtew_powicy);

	hci_dev_unwock(hdev);
}

static void hci_cs_we_ext_cweate_conn(stwuct hci_dev *hdev, u8 status)
{
	stwuct hci_cp_we_ext_cweate_conn *cp;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	/* Aww connection faiwuwe handwing is taken cawe of by the
	 * hci_conn_faiwed function which is twiggewed by the HCI
	 * wequest compwetion cawwbacks used fow connecting.
	 */
	if (status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_EXT_CWEATE_CONN);
	if (!cp)
		wetuwn;

	hci_dev_wock(hdev);

	cs_we_cweate_conn(hdev, &cp->peew_addw, cp->peew_addw_type,
			  cp->own_addw_type, cp->fiwtew_powicy);

	hci_dev_unwock(hdev);
}

static void hci_cs_we_wead_wemote_featuwes(stwuct hci_dev *hdev, u8 status)
{
	stwuct hci_cp_we_wead_wemote_featuwes *cp;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	if (!status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_WEAD_WEMOTE_FEATUWES);
	if (!cp)
		wetuwn;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(cp->handwe));
	if (conn) {
		if (conn->state == BT_CONFIG) {
			hci_connect_cfm(conn, status);
			hci_conn_dwop(conn);
		}
	}

	hci_dev_unwock(hdev);
}

static void hci_cs_we_stawt_enc(stwuct hci_dev *hdev, u8 status)
{
	stwuct hci_cp_we_stawt_enc *cp;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	if (!status)
		wetuwn;

	hci_dev_wock(hdev);

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_STAWT_ENC);
	if (!cp)
		goto unwock;

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(cp->handwe));
	if (!conn)
		goto unwock;

	if (conn->state != BT_CONNECTED)
		goto unwock;

	hci_disconnect(conn, HCI_EWWOW_AUTH_FAIWUWE);
	hci_conn_dwop(conn);

unwock:
	hci_dev_unwock(hdev);
}

static void hci_cs_switch_wowe(stwuct hci_dev *hdev, u8 status)
{
	stwuct hci_cp_switch_wowe *cp;
	stwuct hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (!status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_SWITCH_WOWE);
	if (!cp)
		wetuwn;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &cp->bdaddw);
	if (conn)
		cweaw_bit(HCI_CONN_WSWITCH_PEND, &conn->fwags);

	hci_dev_unwock(hdev);
}

static void hci_inquiwy_compwete_evt(stwuct hci_dev *hdev, void *data,
				     stwuct sk_buff *skb)
{
	stwuct hci_ev_status *ev = data;
	stwuct discovewy_state *discov = &hdev->discovewy;
	stwuct inquiwy_entwy *e;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	hci_conn_check_pending(hdev);

	if (!test_and_cweaw_bit(HCI_INQUIWY, &hdev->fwags))
		wetuwn;

	smp_mb__aftew_atomic(); /* wake_up_bit advises about this bawwiew */
	wake_up_bit(&hdev->fwags, HCI_INQUIWY);

	if (!hci_dev_test_fwag(hdev, HCI_MGMT))
		wetuwn;

	hci_dev_wock(hdev);

	if (discov->state != DISCOVEWY_FINDING)
		goto unwock;

	if (wist_empty(&discov->wesowve)) {
		/* When BW/EDW inquiwy is active and no WE scanning is in
		 * pwogwess, then change discovewy state to indicate compwetion.
		 *
		 * When wunning WE scanning and BW/EDW inquiwy simuwtaneouswy
		 * and the WE scan awweady finished, then change the discovewy
		 * state to indicate compwetion.
		 */
		if (!hci_dev_test_fwag(hdev, HCI_WE_SCAN) ||
		    !test_bit(HCI_QUIWK_SIMUWTANEOUS_DISCOVEWY, &hdev->quiwks))
			hci_discovewy_set_state(hdev, DISCOVEWY_STOPPED);
		goto unwock;
	}

	e = hci_inquiwy_cache_wookup_wesowve(hdev, BDADDW_ANY, NAME_NEEDED);
	if (e && hci_wesowve_name(hdev, e) == 0) {
		e->name_state = NAME_PENDING;
		hci_discovewy_set_state(hdev, DISCOVEWY_WESOWVING);
		discov->name_wesowve_timeout = jiffies + NAME_WESOWVE_DUWATION;
	} ewse {
		/* When BW/EDW inquiwy is active and no WE scanning is in
		 * pwogwess, then change discovewy state to indicate compwetion.
		 *
		 * When wunning WE scanning and BW/EDW inquiwy simuwtaneouswy
		 * and the WE scan awweady finished, then change the discovewy
		 * state to indicate compwetion.
		 */
		if (!hci_dev_test_fwag(hdev, HCI_WE_SCAN) ||
		    !test_bit(HCI_QUIWK_SIMUWTANEOUS_DISCOVEWY, &hdev->quiwks))
			hci_discovewy_set_state(hdev, DISCOVEWY_STOPPED);
	}

unwock:
	hci_dev_unwock(hdev);
}

static void hci_inquiwy_wesuwt_evt(stwuct hci_dev *hdev, void *edata,
				   stwuct sk_buff *skb)
{
	stwuct hci_ev_inquiwy_wesuwt *ev = edata;
	stwuct inquiwy_data data;
	int i;

	if (!hci_ev_skb_puww(hdev, skb, HCI_EV_INQUIWY_WESUWT,
			     fwex_awway_size(ev, info, ev->num)))
		wetuwn;

	bt_dev_dbg(hdev, "num %d", ev->num);

	if (!ev->num)
		wetuwn;

	if (hci_dev_test_fwag(hdev, HCI_PEWIODIC_INQ))
		wetuwn;

	hci_dev_wock(hdev);

	fow (i = 0; i < ev->num; i++) {
		stwuct inquiwy_info *info = &ev->info[i];
		u32 fwags;

		bacpy(&data.bdaddw, &info->bdaddw);
		data.pscan_wep_mode	= info->pscan_wep_mode;
		data.pscan_pewiod_mode	= info->pscan_pewiod_mode;
		data.pscan_mode		= info->pscan_mode;
		memcpy(data.dev_cwass, info->dev_cwass, 3);
		data.cwock_offset	= info->cwock_offset;
		data.wssi		= HCI_WSSI_INVAWID;
		data.ssp_mode		= 0x00;

		fwags = hci_inquiwy_cache_update(hdev, &data, fawse);

		mgmt_device_found(hdev, &info->bdaddw, ACW_WINK, 0x00,
				  info->dev_cwass, HCI_WSSI_INVAWID,
				  fwags, NUWW, 0, NUWW, 0, 0);
	}

	hci_dev_unwock(hdev);
}

static void hci_conn_compwete_evt(stwuct hci_dev *hdev, void *data,
				  stwuct sk_buff *skb)
{
	stwuct hci_ev_conn_compwete *ev = data;
	stwuct hci_conn *conn;
	u8 status = ev->status;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_ba(hdev, ev->wink_type, &ev->bdaddw);
	if (!conn) {
		/* In case of ewwow status and thewe is no connection pending
		 * just unwock as thewe is nothing to cweanup.
		 */
		if (ev->status)
			goto unwock;

		/* Connection may not exist if auto-connected. Check the bwedw
		 * awwowwist to see if this device is awwowed to auto connect.
		 * If wink is an ACW type, cweate a connection cwass
		 * automaticawwy.
		 *
		 * Auto-connect wiww onwy occuw if the event fiwtew is
		 * pwogwammed with a given addwess. Wight now, event fiwtew is
		 * onwy used duwing suspend.
		 */
		if (ev->wink_type == ACW_WINK &&
		    hci_bdaddw_wist_wookup_with_fwags(&hdev->accept_wist,
						      &ev->bdaddw,
						      BDADDW_BWEDW)) {
			conn = hci_conn_add_unset(hdev, ev->wink_type,
						  &ev->bdaddw, HCI_WOWE_SWAVE);
			if (!conn) {
				bt_dev_eww(hdev, "no memowy fow new conn");
				goto unwock;
			}
		} ewse {
			if (ev->wink_type != SCO_WINK)
				goto unwock;

			conn = hci_conn_hash_wookup_ba(hdev, ESCO_WINK,
						       &ev->bdaddw);
			if (!conn)
				goto unwock;

			conn->type = SCO_WINK;
		}
	}

	/* The HCI_Connection_Compwete event is onwy sent once pew connection.
	 * Pwocessing it mowe than once pew connection can cowwupt kewnew memowy.
	 *
	 * As the connection handwe is set hewe fow the fiwst time, it indicates
	 * whethew the connection is awweady set up.
	 */
	if (!HCI_CONN_HANDWE_UNSET(conn->handwe)) {
		bt_dev_eww(hdev, "Ignowing HCI_Connection_Compwete fow existing connection");
		goto unwock;
	}

	if (!status) {
		status = hci_conn_set_handwe(conn, __we16_to_cpu(ev->handwe));
		if (status)
			goto done;

		if (conn->type == ACW_WINK) {
			conn->state = BT_CONFIG;
			hci_conn_howd(conn);

			if (!conn->out && !hci_conn_ssp_enabwed(conn) &&
			    !hci_find_wink_key(hdev, &ev->bdaddw))
				conn->disc_timeout = HCI_PAIWING_TIMEOUT;
			ewse
				conn->disc_timeout = HCI_DISCONN_TIMEOUT;
		} ewse
			conn->state = BT_CONNECTED;

		hci_debugfs_cweate_conn(conn);
		hci_conn_add_sysfs(conn);

		if (test_bit(HCI_AUTH, &hdev->fwags))
			set_bit(HCI_CONN_AUTH, &conn->fwags);

		if (test_bit(HCI_ENCWYPT, &hdev->fwags))
			set_bit(HCI_CONN_ENCWYPT, &conn->fwags);

		/* Get wemote featuwes */
		if (conn->type == ACW_WINK) {
			stwuct hci_cp_wead_wemote_featuwes cp;
			cp.handwe = ev->handwe;
			hci_send_cmd(hdev, HCI_OP_WEAD_WEMOTE_FEATUWES,
				     sizeof(cp), &cp);

			hci_update_scan(hdev);
		}

		/* Set packet type fow incoming connection */
		if (!conn->out && hdev->hci_vew < BWUETOOTH_VEW_2_0) {
			stwuct hci_cp_change_conn_ptype cp;
			cp.handwe = ev->handwe;
			cp.pkt_type = cpu_to_we16(conn->pkt_type);
			hci_send_cmd(hdev, HCI_OP_CHANGE_CONN_PTYPE, sizeof(cp),
				     &cp);
		}
	}

	if (conn->type == ACW_WINK)
		hci_sco_setup(conn, ev->status);

done:
	if (status) {
		hci_conn_faiwed(conn, status);
	} ewse if (ev->wink_type == SCO_WINK) {
		switch (conn->setting & SCO_AIWMODE_MASK) {
		case SCO_AIWMODE_CVSD:
			if (hdev->notify)
				hdev->notify(hdev, HCI_NOTIFY_ENABWE_SCO_CVSD);
			bweak;
		}

		hci_connect_cfm(conn, status);
	}

unwock:
	hci_dev_unwock(hdev);

	hci_conn_check_pending(hdev);
}

static void hci_weject_conn(stwuct hci_dev *hdev, bdaddw_t *bdaddw)
{
	stwuct hci_cp_weject_conn_weq cp;

	bacpy(&cp.bdaddw, bdaddw);
	cp.weason = HCI_EWWOW_WEJ_BAD_ADDW;
	hci_send_cmd(hdev, HCI_OP_WEJECT_CONN_WEQ, sizeof(cp), &cp);
}

static void hci_conn_wequest_evt(stwuct hci_dev *hdev, void *data,
				 stwuct sk_buff *skb)
{
	stwuct hci_ev_conn_wequest *ev = data;
	int mask = hdev->wink_mode;
	stwuct inquiwy_entwy *ie;
	stwuct hci_conn *conn;
	__u8 fwags = 0;

	bt_dev_dbg(hdev, "bdaddw %pMW type 0x%x", &ev->bdaddw, ev->wink_type);

	/* Weject incoming connection fwom device with same BD ADDW against
	 * CVE-2020-26555
	 */
	if (hdev && !bacmp(&hdev->bdaddw, &ev->bdaddw)) {
		bt_dev_dbg(hdev, "Weject connection with same BD_ADDW %pMW\n",
			   &ev->bdaddw);
		hci_weject_conn(hdev, &ev->bdaddw);
		wetuwn;
	}

	mask |= hci_pwoto_connect_ind(hdev, &ev->bdaddw, ev->wink_type,
				      &fwags);

	if (!(mask & HCI_WM_ACCEPT)) {
		hci_weject_conn(hdev, &ev->bdaddw);
		wetuwn;
	}

	hci_dev_wock(hdev);

	if (hci_bdaddw_wist_wookup(&hdev->weject_wist, &ev->bdaddw,
				   BDADDW_BWEDW)) {
		hci_weject_conn(hdev, &ev->bdaddw);
		goto unwock;
	}

	/* Wequiwe HCI_CONNECTABWE ow an accept wist entwy to accept the
	 * connection. These featuwes awe onwy touched thwough mgmt so
	 * onwy do the checks if HCI_MGMT is set.
	 */
	if (hci_dev_test_fwag(hdev, HCI_MGMT) &&
	    !hci_dev_test_fwag(hdev, HCI_CONNECTABWE) &&
	    !hci_bdaddw_wist_wookup_with_fwags(&hdev->accept_wist, &ev->bdaddw,
					       BDADDW_BWEDW)) {
		hci_weject_conn(hdev, &ev->bdaddw);
		goto unwock;
	}

	/* Connection accepted */

	ie = hci_inquiwy_cache_wookup(hdev, &ev->bdaddw);
	if (ie)
		memcpy(ie->data.dev_cwass, ev->dev_cwass, 3);

	conn = hci_conn_hash_wookup_ba(hdev, ev->wink_type,
			&ev->bdaddw);
	if (!conn) {
		conn = hci_conn_add_unset(hdev, ev->wink_type, &ev->bdaddw,
					  HCI_WOWE_SWAVE);
		if (!conn) {
			bt_dev_eww(hdev, "no memowy fow new connection");
			goto unwock;
		}
	}

	memcpy(conn->dev_cwass, ev->dev_cwass, 3);

	hci_dev_unwock(hdev);

	if (ev->wink_type == ACW_WINK ||
	    (!(fwags & HCI_PWOTO_DEFEW) && !wmp_esco_capabwe(hdev))) {
		stwuct hci_cp_accept_conn_weq cp;
		conn->state = BT_CONNECT;

		bacpy(&cp.bdaddw, &ev->bdaddw);

		if (wmp_wswitch_capabwe(hdev) && (mask & HCI_WM_MASTEW))
			cp.wowe = 0x00; /* Become centwaw */
		ewse
			cp.wowe = 0x01; /* Wemain pewiphewaw */

		hci_send_cmd(hdev, HCI_OP_ACCEPT_CONN_WEQ, sizeof(cp), &cp);
	} ewse if (!(fwags & HCI_PWOTO_DEFEW)) {
		stwuct hci_cp_accept_sync_conn_weq cp;
		conn->state = BT_CONNECT;

		bacpy(&cp.bdaddw, &ev->bdaddw);
		cp.pkt_type = cpu_to_we16(conn->pkt_type);

		cp.tx_bandwidth   = cpu_to_we32(0x00001f40);
		cp.wx_bandwidth   = cpu_to_we32(0x00001f40);
		cp.max_watency    = cpu_to_we16(0xffff);
		cp.content_fowmat = cpu_to_we16(hdev->voice_setting);
		cp.wetwans_effowt = 0xff;

		hci_send_cmd(hdev, HCI_OP_ACCEPT_SYNC_CONN_WEQ, sizeof(cp),
			     &cp);
	} ewse {
		conn->state = BT_CONNECT2;
		hci_connect_cfm(conn, 0);
	}

	wetuwn;
unwock:
	hci_dev_unwock(hdev);
}

static u8 hci_to_mgmt_weason(u8 eww)
{
	switch (eww) {
	case HCI_EWWOW_CONNECTION_TIMEOUT:
		wetuwn MGMT_DEV_DISCONN_TIMEOUT;
	case HCI_EWWOW_WEMOTE_USEW_TEWM:
	case HCI_EWWOW_WEMOTE_WOW_WESOUWCES:
	case HCI_EWWOW_WEMOTE_POWEW_OFF:
		wetuwn MGMT_DEV_DISCONN_WEMOTE;
	case HCI_EWWOW_WOCAW_HOST_TEWM:
		wetuwn MGMT_DEV_DISCONN_WOCAW_HOST;
	defauwt:
		wetuwn MGMT_DEV_DISCONN_UNKNOWN;
	}
}

static void hci_disconn_compwete_evt(stwuct hci_dev *hdev, void *data,
				     stwuct sk_buff *skb)
{
	stwuct hci_ev_disconn_compwete *ev = data;
	u8 weason;
	stwuct hci_conn_pawams *pawams;
	stwuct hci_conn *conn;
	boow mgmt_connected;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(ev->handwe));
	if (!conn)
		goto unwock;

	if (ev->status) {
		mgmt_disconnect_faiwed(hdev, &conn->dst, conn->type,
				       conn->dst_type, ev->status);
		goto unwock;
	}

	conn->state = BT_CWOSED;

	mgmt_connected = test_and_cweaw_bit(HCI_CONN_MGMT_CONNECTED, &conn->fwags);

	if (test_bit(HCI_CONN_AUTH_FAIWUWE, &conn->fwags))
		weason = MGMT_DEV_DISCONN_AUTH_FAIWUWE;
	ewse
		weason = hci_to_mgmt_weason(ev->weason);

	mgmt_device_disconnected(hdev, &conn->dst, conn->type, conn->dst_type,
				weason, mgmt_connected);

	if (conn->type == ACW_WINK) {
		if (test_and_cweaw_bit(HCI_CONN_FWUSH_KEY, &conn->fwags))
			hci_wemove_wink_key(hdev, &conn->dst);

		hci_update_scan(hdev);
	}

	pawams = hci_conn_pawams_wookup(hdev, &conn->dst, conn->dst_type);
	if (pawams) {
		switch (pawams->auto_connect) {
		case HCI_AUTO_CONN_WINK_WOSS:
			if (ev->weason != HCI_EWWOW_CONNECTION_TIMEOUT)
				bweak;
			fawwthwough;

		case HCI_AUTO_CONN_DIWECT:
		case HCI_AUTO_CONN_AWWAYS:
			hci_pend_we_wist_dew_init(pawams);
			hci_pend_we_wist_add(pawams, &hdev->pend_we_conns);
			hci_update_passive_scan(hdev);
			bweak;

		defauwt:
			bweak;
		}
	}

	hci_disconn_cfm(conn, ev->weason);

	/* We-enabwe advewtising if necessawy, since it might
	 * have been disabwed by the connection. Fwom the
	 * HCI_WE_Set_Advewtise_Enabwe command descwiption in
	 * the cowe specification (v4.0):
	 * "The Contwowwew shaww continue advewtising untiw the Host
	 * issues an WE_Set_Advewtise_Enabwe command with
	 * Advewtising_Enabwe set to 0x00 (Advewtising is disabwed)
	 * ow untiw a connection is cweated ow untiw the Advewtising
	 * is timed out due to Diwected Advewtising."
	 */
	if (conn->type == WE_WINK && conn->wowe == HCI_WOWE_SWAVE) {
		hdev->cuw_adv_instance = conn->adv_instance;
		hci_enabwe_advewtising(hdev);
	}

	hci_conn_dew(conn);

unwock:
	hci_dev_unwock(hdev);
}

static void hci_auth_compwete_evt(stwuct hci_dev *hdev, void *data,
				  stwuct sk_buff *skb)
{
	stwuct hci_ev_auth_compwete *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(ev->handwe));
	if (!conn)
		goto unwock;

	if (!ev->status) {
		cweaw_bit(HCI_CONN_AUTH_FAIWUWE, &conn->fwags);
		set_bit(HCI_CONN_AUTH, &conn->fwags);
		conn->sec_wevew = conn->pending_sec_wevew;
	} ewse {
		if (ev->status == HCI_EWWOW_PIN_OW_KEY_MISSING)
			set_bit(HCI_CONN_AUTH_FAIWUWE, &conn->fwags);

		mgmt_auth_faiwed(conn, ev->status);
	}

	cweaw_bit(HCI_CONN_AUTH_PEND, &conn->fwags);

	if (conn->state == BT_CONFIG) {
		if (!ev->status && hci_conn_ssp_enabwed(conn)) {
			stwuct hci_cp_set_conn_encwypt cp;
			cp.handwe  = ev->handwe;
			cp.encwypt = 0x01;
			hci_send_cmd(hdev, HCI_OP_SET_CONN_ENCWYPT, sizeof(cp),
				     &cp);
		} ewse {
			conn->state = BT_CONNECTED;
			hci_connect_cfm(conn, ev->status);
			hci_conn_dwop(conn);
		}
	} ewse {
		hci_auth_cfm(conn, ev->status);

		hci_conn_howd(conn);
		conn->disc_timeout = HCI_DISCONN_TIMEOUT;
		hci_conn_dwop(conn);
	}

	if (test_bit(HCI_CONN_ENCWYPT_PEND, &conn->fwags)) {
		if (!ev->status) {
			stwuct hci_cp_set_conn_encwypt cp;
			cp.handwe  = ev->handwe;
			cp.encwypt = 0x01;
			hci_send_cmd(hdev, HCI_OP_SET_CONN_ENCWYPT, sizeof(cp),
				     &cp);
		} ewse {
			cweaw_bit(HCI_CONN_ENCWYPT_PEND, &conn->fwags);
			hci_encwypt_cfm(conn, ev->status);
		}
	}

unwock:
	hci_dev_unwock(hdev);
}

static void hci_wemote_name_evt(stwuct hci_dev *hdev, void *data,
				stwuct sk_buff *skb)
{
	stwuct hci_ev_wemote_name *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	hci_conn_check_pending(hdev);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &ev->bdaddw);

	if (!hci_dev_test_fwag(hdev, HCI_MGMT))
		goto check_auth;

	if (ev->status == 0)
		hci_check_pending_name(hdev, conn, &ev->bdaddw, ev->name,
				       stwnwen(ev->name, HCI_MAX_NAME_WENGTH));
	ewse
		hci_check_pending_name(hdev, conn, &ev->bdaddw, NUWW, 0);

check_auth:
	if (!conn)
		goto unwock;

	if (!hci_outgoing_auth_needed(hdev, conn))
		goto unwock;

	if (!test_and_set_bit(HCI_CONN_AUTH_PEND, &conn->fwags)) {
		stwuct hci_cp_auth_wequested cp;

		set_bit(HCI_CONN_AUTH_INITIATOW, &conn->fwags);

		cp.handwe = __cpu_to_we16(conn->handwe);
		hci_send_cmd(hdev, HCI_OP_AUTH_WEQUESTED, sizeof(cp), &cp);
	}

unwock:
	hci_dev_unwock(hdev);
}

static void hci_encwypt_change_evt(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_ev_encwypt_change *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(ev->handwe));
	if (!conn)
		goto unwock;

	if (!ev->status) {
		if (ev->encwypt) {
			/* Encwyption impwies authentication */
			set_bit(HCI_CONN_AUTH, &conn->fwags);
			set_bit(HCI_CONN_ENCWYPT, &conn->fwags);
			conn->sec_wevew = conn->pending_sec_wevew;

			/* P-256 authentication key impwies FIPS */
			if (conn->key_type == HCI_WK_AUTH_COMBINATION_P256)
				set_bit(HCI_CONN_FIPS, &conn->fwags);

			if ((conn->type == ACW_WINK && ev->encwypt == 0x02) ||
			    conn->type == WE_WINK)
				set_bit(HCI_CONN_AES_CCM, &conn->fwags);
		} ewse {
			cweaw_bit(HCI_CONN_ENCWYPT, &conn->fwags);
			cweaw_bit(HCI_CONN_AES_CCM, &conn->fwags);
		}
	}

	/* We shouwd diswegawd the cuwwent WPA and genewate a new one
	 * whenevew the encwyption pwoceduwe faiws.
	 */
	if (ev->status && conn->type == WE_WINK) {
		hci_dev_set_fwag(hdev, HCI_WPA_EXPIWED);
		hci_adv_instances_set_wpa_expiwed(hdev, twue);
	}

	cweaw_bit(HCI_CONN_ENCWYPT_PEND, &conn->fwags);

	/* Check wink secuwity wequiwements awe met */
	if (!hci_conn_check_wink_mode(conn))
		ev->status = HCI_EWWOW_AUTH_FAIWUWE;

	if (ev->status && conn->state == BT_CONNECTED) {
		if (ev->status == HCI_EWWOW_PIN_OW_KEY_MISSING)
			set_bit(HCI_CONN_AUTH_FAIWUWE, &conn->fwags);

		/* Notify uppew wayews so they can cweanup befowe
		 * disconnecting.
		 */
		hci_encwypt_cfm(conn, ev->status);
		hci_disconnect(conn, HCI_EWWOW_AUTH_FAIWUWE);
		hci_conn_dwop(conn);
		goto unwock;
	}

	/* Twy weading the encwyption key size fow encwypted ACW winks */
	if (!ev->status && ev->encwypt && conn->type == ACW_WINK) {
		stwuct hci_cp_wead_enc_key_size cp;

		/* Onwy send HCI_Wead_Encwyption_Key_Size if the
		 * contwowwew weawwy suppowts it. If it doesn't, assume
		 * the defauwt size (16).
		 */
		if (!(hdev->commands[20] & 0x10)) {
			conn->enc_key_size = HCI_WINK_KEY_SIZE;
			goto notify;
		}

		cp.handwe = cpu_to_we16(conn->handwe);
		if (hci_send_cmd(hdev, HCI_OP_WEAD_ENC_KEY_SIZE,
				 sizeof(cp), &cp)) {
			bt_dev_eww(hdev, "sending wead key size faiwed");
			conn->enc_key_size = HCI_WINK_KEY_SIZE;
			goto notify;
		}

		goto unwock;
	}

	/* Set the defauwt Authenticated Paywoad Timeout aftew
	 * an WE Wink is estabwished. As pew Cowe Spec v5.0, Vow 2, Pawt B
	 * Section 3.3, the HCI command WWITE_AUTH_PAYWOAD_TIMEOUT shouwd be
	 * sent when the wink is active and Encwyption is enabwed, the conn
	 * type can be eithew WE ow ACW and contwowwew must suppowt WMP Ping.
	 * Ensuwe fow AES-CCM encwyption as weww.
	 */
	if (test_bit(HCI_CONN_ENCWYPT, &conn->fwags) &&
	    test_bit(HCI_CONN_AES_CCM, &conn->fwags) &&
	    ((conn->type == ACW_WINK && wmp_ping_capabwe(hdev)) ||
	     (conn->type == WE_WINK && (hdev->we_featuwes[0] & HCI_WE_PING)))) {
		stwuct hci_cp_wwite_auth_paywoad_to cp;

		cp.handwe = cpu_to_we16(conn->handwe);
		cp.timeout = cpu_to_we16(hdev->auth_paywoad_timeout);
		if (hci_send_cmd(conn->hdev, HCI_OP_WWITE_AUTH_PAYWOAD_TO,
				 sizeof(cp), &cp))
			bt_dev_eww(hdev, "wwite auth paywoad timeout faiwed");
	}

notify:
	hci_encwypt_cfm(conn, ev->status);

unwock:
	hci_dev_unwock(hdev);
}

static void hci_change_wink_key_compwete_evt(stwuct hci_dev *hdev, void *data,
					     stwuct sk_buff *skb)
{
	stwuct hci_ev_change_wink_key_compwete *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(ev->handwe));
	if (conn) {
		if (!ev->status)
			set_bit(HCI_CONN_SECUWE, &conn->fwags);

		cweaw_bit(HCI_CONN_AUTH_PEND, &conn->fwags);

		hci_key_change_cfm(conn, ev->status);
	}

	hci_dev_unwock(hdev);
}

static void hci_wemote_featuwes_evt(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_ev_wemote_featuwes *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(ev->handwe));
	if (!conn)
		goto unwock;

	if (!ev->status)
		memcpy(conn->featuwes[0], ev->featuwes, 8);

	if (conn->state != BT_CONFIG)
		goto unwock;

	if (!ev->status && wmp_ext_feat_capabwe(hdev) &&
	    wmp_ext_feat_capabwe(conn)) {
		stwuct hci_cp_wead_wemote_ext_featuwes cp;
		cp.handwe = ev->handwe;
		cp.page = 0x01;
		hci_send_cmd(hdev, HCI_OP_WEAD_WEMOTE_EXT_FEATUWES,
			     sizeof(cp), &cp);
		goto unwock;
	}

	if (!ev->status && !test_bit(HCI_CONN_MGMT_CONNECTED, &conn->fwags)) {
		stwuct hci_cp_wemote_name_weq cp;
		memset(&cp, 0, sizeof(cp));
		bacpy(&cp.bdaddw, &conn->dst);
		cp.pscan_wep_mode = 0x02;
		hci_send_cmd(hdev, HCI_OP_WEMOTE_NAME_WEQ, sizeof(cp), &cp);
	} ewse if (!test_and_set_bit(HCI_CONN_MGMT_CONNECTED, &conn->fwags))
		mgmt_device_connected(hdev, conn, NUWW, 0);

	if (!hci_outgoing_auth_needed(hdev, conn)) {
		conn->state = BT_CONNECTED;
		hci_connect_cfm(conn, ev->status);
		hci_conn_dwop(conn);
	}

unwock:
	hci_dev_unwock(hdev);
}

static inwine void handwe_cmd_cnt_and_timew(stwuct hci_dev *hdev, u8 ncmd)
{
	cancew_dewayed_wowk(&hdev->cmd_timew);

	wcu_wead_wock();
	if (!test_bit(HCI_WESET, &hdev->fwags)) {
		if (ncmd) {
			cancew_dewayed_wowk(&hdev->ncmd_timew);
			atomic_set(&hdev->cmd_cnt, 1);
		} ewse {
			if (!hci_dev_test_fwag(hdev, HCI_CMD_DWAIN_WOWKQUEUE))
				queue_dewayed_wowk(hdev->wowkqueue, &hdev->ncmd_timew,
						   HCI_NCMD_TIMEOUT);
		}
	}
	wcu_wead_unwock();
}

static u8 hci_cc_we_wead_buffew_size_v2(stwuct hci_dev *hdev, void *data,
					stwuct sk_buff *skb)
{
	stwuct hci_wp_we_wead_buffew_size_v2 *wp = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	hdev->we_mtu   = __we16_to_cpu(wp->acw_mtu);
	hdev->we_pkts  = wp->acw_max_pkt;
	hdev->iso_mtu  = __we16_to_cpu(wp->iso_mtu);
	hdev->iso_pkts = wp->iso_max_pkt;

	hdev->we_cnt  = hdev->we_pkts;
	hdev->iso_cnt = hdev->iso_pkts;

	BT_DBG("%s acw mtu %d:%d iso mtu %d:%d", hdev->name, hdev->acw_mtu,
	       hdev->acw_pkts, hdev->iso_mtu, hdev->iso_pkts);

	wetuwn wp->status;
}

static void hci_unbound_cis_faiwed(stwuct hci_dev *hdev, u8 cig, u8 status)
{
	stwuct hci_conn *conn, *tmp;

	wockdep_assewt_hewd(&hdev->wock);

	wist_fow_each_entwy_safe(conn, tmp, &hdev->conn_hash.wist, wist) {
		if (conn->type != ISO_WINK || !bacmp(&conn->dst, BDADDW_ANY) ||
		    conn->state == BT_OPEN || conn->iso_qos.ucast.cig != cig)
			continue;

		if (HCI_CONN_HANDWE_UNSET(conn->handwe))
			hci_conn_faiwed(conn, status);
	}
}

static u8 hci_cc_we_set_cig_pawams(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_wp_we_set_cig_pawams *wp = data;
	stwuct hci_cp_we_set_cig_pawams *cp;
	stwuct hci_conn *conn;
	u8 status = wp->status;
	boow pending = fawse;
	int i;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_CIG_PAWAMS);
	if (!wp->status && (!cp || wp->num_handwes != cp->num_cis ||
			    wp->cig_id != cp->cig_id)) {
		bt_dev_eww(hdev, "unexpected Set CIG Pawametews wesponse data");
		status = HCI_EWWOW_UNSPECIFIED;
	}

	hci_dev_wock(hdev);

	/* BWUETOOTH COWE SPECIFICATION Vewsion 5.4 | Vow 4, Pawt E page 2554
	 *
	 * If the Status wetuwn pawametew is non-zewo, then the state of the CIG
	 * and its CIS configuwations shaww not be changed by the command. If
	 * the CIG did not awweady exist, it shaww not be cweated.
	 */
	if (status) {
		/* Keep cuwwent configuwation, faiw onwy the unbound CIS */
		hci_unbound_cis_faiwed(hdev, wp->cig_id, status);
		goto unwock;
	}

	/* BWUETOOTH COWE SPECIFICATION Vewsion 5.3 | Vow 4, Pawt E page 2553
	 *
	 * If the Status wetuwn pawametew is zewo, then the Contwowwew shaww
	 * set the Connection_Handwe awwayed wetuwn pawametew to the connection
	 * handwe(s) cowwesponding to the CIS configuwations specified in
	 * the CIS_IDs command pawametew, in the same owdew.
	 */
	fow (i = 0; i < wp->num_handwes; ++i) {
		conn = hci_conn_hash_wookup_cis(hdev, NUWW, 0, wp->cig_id,
						cp->cis[i].cis_id);
		if (!conn || !bacmp(&conn->dst, BDADDW_ANY))
			continue;

		if (conn->state != BT_BOUND && conn->state != BT_CONNECT)
			continue;

		if (hci_conn_set_handwe(conn, __we16_to_cpu(wp->handwe[i])))
			continue;

		if (conn->state == BT_CONNECT)
			pending = twue;
	}

unwock:
	if (pending)
		hci_we_cweate_cis_pending(hdev);

	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

static u8 hci_cc_we_setup_iso_path(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_wp_we_setup_iso_path *wp = data;
	stwuct hci_cp_we_setup_iso_path *cp;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_SETUP_ISO_PATH);
	if (!cp)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(cp->handwe));
	if (!conn)
		goto unwock;

	if (wp->status) {
		hci_connect_cfm(conn, wp->status);
		hci_conn_dew(conn);
		goto unwock;
	}

	switch (cp->diwection) {
	/* Input (Host to Contwowwew) */
	case 0x00:
		/* Onwy confiwm connection if output onwy */
		if (conn->iso_qos.ucast.out.sdu && !conn->iso_qos.ucast.in.sdu)
			hci_connect_cfm(conn, wp->status);
		bweak;
	/* Output (Contwowwew to Host) */
	case 0x01:
		/* Confiwm connection since conn->iso_qos is awways configuwed
		 * wast.
		 */
		hci_connect_cfm(conn, wp->status);
		bweak;
	}

unwock:
	hci_dev_unwock(hdev);
	wetuwn wp->status;
}

static void hci_cs_we_cweate_big(stwuct hci_dev *hdev, u8 status)
{
	bt_dev_dbg(hdev, "status 0x%2.2x", status);
}

static u8 hci_cc_set_pew_adv_pawam(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	stwuct hci_cp_we_set_pew_adv_pawams *cp;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_PEW_ADV_PAWAMS);
	if (!cp)
		wetuwn wp->status;

	/* TODO: set the conn state */
	wetuwn wp->status;
}

static u8 hci_cc_we_set_pew_adv_enabwe(stwuct hci_dev *hdev, void *data,
				       stwuct sk_buff *skb)
{
	stwuct hci_ev_status *wp = data;
	stwuct hci_cp_we_set_pew_adv_enabwe *cp;
	stwuct adv_info *adv = NUWW, *n;
	u8 pew_adv_cnt = 0;

	bt_dev_dbg(hdev, "status 0x%2.2x", wp->status);

	if (wp->status)
		wetuwn wp->status;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_SET_PEW_ADV_ENABWE);
	if (!cp)
		wetuwn wp->status;

	hci_dev_wock(hdev);

	adv = hci_find_adv_instance(hdev, cp->handwe);

	if (cp->enabwe) {
		hci_dev_set_fwag(hdev, HCI_WE_PEW_ADV);

		if (adv)
			adv->enabwed = twue;
	} ewse {
		/* If just one instance was disabwed check if thewe awe
		 * any othew instance enabwed befowe cweawing HCI_WE_PEW_ADV.
		 * The cuwwent pewiodic adv instance wiww be mawked as
		 * disabwed once extended advewtising is awso disabwed.
		 */
		wist_fow_each_entwy_safe(adv, n, &hdev->adv_instances,
					 wist) {
			if (adv->pewiodic && adv->enabwed)
				pew_adv_cnt++;
		}

		if (pew_adv_cnt > 1)
			goto unwock;

		hci_dev_cweaw_fwag(hdev, HCI_WE_PEW_ADV);
	}

unwock:
	hci_dev_unwock(hdev);

	wetuwn wp->status;
}

#define HCI_CC_VW(_op, _func, _min, _max) \
{ \
	.op = _op, \
	.func = _func, \
	.min_wen = _min, \
	.max_wen = _max, \
}

#define HCI_CC(_op, _func, _wen) \
	HCI_CC_VW(_op, _func, _wen, _wen)

#define HCI_CC_STATUS(_op, _func) \
	HCI_CC(_op, _func, sizeof(stwuct hci_ev_status))

static const stwuct hci_cc {
	u16  op;
	u8 (*func)(stwuct hci_dev *hdev, void *data, stwuct sk_buff *skb);
	u16  min_wen;
	u16  max_wen;
} hci_cc_tabwe[] = {
	HCI_CC_STATUS(HCI_OP_INQUIWY_CANCEW, hci_cc_inquiwy_cancew),
	HCI_CC_STATUS(HCI_OP_PEWIODIC_INQ, hci_cc_pewiodic_inq),
	HCI_CC_STATUS(HCI_OP_EXIT_PEWIODIC_INQ, hci_cc_exit_pewiodic_inq),
	HCI_CC_STATUS(HCI_OP_WEMOTE_NAME_WEQ_CANCEW,
		      hci_cc_wemote_name_weq_cancew),
	HCI_CC(HCI_OP_WOWE_DISCOVEWY, hci_cc_wowe_discovewy,
	       sizeof(stwuct hci_wp_wowe_discovewy)),
	HCI_CC(HCI_OP_WEAD_WINK_POWICY, hci_cc_wead_wink_powicy,
	       sizeof(stwuct hci_wp_wead_wink_powicy)),
	HCI_CC(HCI_OP_WWITE_WINK_POWICY, hci_cc_wwite_wink_powicy,
	       sizeof(stwuct hci_wp_wwite_wink_powicy)),
	HCI_CC(HCI_OP_WEAD_DEF_WINK_POWICY, hci_cc_wead_def_wink_powicy,
	       sizeof(stwuct hci_wp_wead_def_wink_powicy)),
	HCI_CC_STATUS(HCI_OP_WWITE_DEF_WINK_POWICY,
		      hci_cc_wwite_def_wink_powicy),
	HCI_CC_STATUS(HCI_OP_WESET, hci_cc_weset),
	HCI_CC(HCI_OP_WEAD_STOWED_WINK_KEY, hci_cc_wead_stowed_wink_key,
	       sizeof(stwuct hci_wp_wead_stowed_wink_key)),
	HCI_CC(HCI_OP_DEWETE_STOWED_WINK_KEY, hci_cc_dewete_stowed_wink_key,
	       sizeof(stwuct hci_wp_dewete_stowed_wink_key)),
	HCI_CC_STATUS(HCI_OP_WWITE_WOCAW_NAME, hci_cc_wwite_wocaw_name),
	HCI_CC(HCI_OP_WEAD_WOCAW_NAME, hci_cc_wead_wocaw_name,
	       sizeof(stwuct hci_wp_wead_wocaw_name)),
	HCI_CC_STATUS(HCI_OP_WWITE_AUTH_ENABWE, hci_cc_wwite_auth_enabwe),
	HCI_CC_STATUS(HCI_OP_WWITE_ENCWYPT_MODE, hci_cc_wwite_encwypt_mode),
	HCI_CC_STATUS(HCI_OP_WWITE_SCAN_ENABWE, hci_cc_wwite_scan_enabwe),
	HCI_CC_STATUS(HCI_OP_SET_EVENT_FWT, hci_cc_set_event_fiwtew),
	HCI_CC(HCI_OP_WEAD_CWASS_OF_DEV, hci_cc_wead_cwass_of_dev,
	       sizeof(stwuct hci_wp_wead_cwass_of_dev)),
	HCI_CC_STATUS(HCI_OP_WWITE_CWASS_OF_DEV, hci_cc_wwite_cwass_of_dev),
	HCI_CC(HCI_OP_WEAD_VOICE_SETTING, hci_cc_wead_voice_setting,
	       sizeof(stwuct hci_wp_wead_voice_setting)),
	HCI_CC_STATUS(HCI_OP_WWITE_VOICE_SETTING, hci_cc_wwite_voice_setting),
	HCI_CC(HCI_OP_WEAD_NUM_SUPPOWTED_IAC, hci_cc_wead_num_suppowted_iac,
	       sizeof(stwuct hci_wp_wead_num_suppowted_iac)),
	HCI_CC_STATUS(HCI_OP_WWITE_SSP_MODE, hci_cc_wwite_ssp_mode),
	HCI_CC_STATUS(HCI_OP_WWITE_SC_SUPPOWT, hci_cc_wwite_sc_suppowt),
	HCI_CC(HCI_OP_WEAD_AUTH_PAYWOAD_TO, hci_cc_wead_auth_paywoad_timeout,
	       sizeof(stwuct hci_wp_wead_auth_paywoad_to)),
	HCI_CC(HCI_OP_WWITE_AUTH_PAYWOAD_TO, hci_cc_wwite_auth_paywoad_timeout,
	       sizeof(stwuct hci_wp_wwite_auth_paywoad_to)),
	HCI_CC(HCI_OP_WEAD_WOCAW_VEWSION, hci_cc_wead_wocaw_vewsion,
	       sizeof(stwuct hci_wp_wead_wocaw_vewsion)),
	HCI_CC(HCI_OP_WEAD_WOCAW_COMMANDS, hci_cc_wead_wocaw_commands,
	       sizeof(stwuct hci_wp_wead_wocaw_commands)),
	HCI_CC(HCI_OP_WEAD_WOCAW_FEATUWES, hci_cc_wead_wocaw_featuwes,
	       sizeof(stwuct hci_wp_wead_wocaw_featuwes)),
	HCI_CC(HCI_OP_WEAD_WOCAW_EXT_FEATUWES, hci_cc_wead_wocaw_ext_featuwes,
	       sizeof(stwuct hci_wp_wead_wocaw_ext_featuwes)),
	HCI_CC(HCI_OP_WEAD_BUFFEW_SIZE, hci_cc_wead_buffew_size,
	       sizeof(stwuct hci_wp_wead_buffew_size)),
	HCI_CC(HCI_OP_WEAD_BD_ADDW, hci_cc_wead_bd_addw,
	       sizeof(stwuct hci_wp_wead_bd_addw)),
	HCI_CC(HCI_OP_WEAD_WOCAW_PAIWING_OPTS, hci_cc_wead_wocaw_paiwing_opts,
	       sizeof(stwuct hci_wp_wead_wocaw_paiwing_opts)),
	HCI_CC(HCI_OP_WEAD_PAGE_SCAN_ACTIVITY, hci_cc_wead_page_scan_activity,
	       sizeof(stwuct hci_wp_wead_page_scan_activity)),
	HCI_CC_STATUS(HCI_OP_WWITE_PAGE_SCAN_ACTIVITY,
		      hci_cc_wwite_page_scan_activity),
	HCI_CC(HCI_OP_WEAD_PAGE_SCAN_TYPE, hci_cc_wead_page_scan_type,
	       sizeof(stwuct hci_wp_wead_page_scan_type)),
	HCI_CC_STATUS(HCI_OP_WWITE_PAGE_SCAN_TYPE, hci_cc_wwite_page_scan_type),
	HCI_CC(HCI_OP_WEAD_DATA_BWOCK_SIZE, hci_cc_wead_data_bwock_size,
	       sizeof(stwuct hci_wp_wead_data_bwock_size)),
	HCI_CC(HCI_OP_WEAD_FWOW_CONTWOW_MODE, hci_cc_wead_fwow_contwow_mode,
	       sizeof(stwuct hci_wp_wead_fwow_contwow_mode)),
	HCI_CC(HCI_OP_WEAD_WOCAW_AMP_INFO, hci_cc_wead_wocaw_amp_info,
	       sizeof(stwuct hci_wp_wead_wocaw_amp_info)),
	HCI_CC(HCI_OP_WEAD_CWOCK, hci_cc_wead_cwock,
	       sizeof(stwuct hci_wp_wead_cwock)),
	HCI_CC(HCI_OP_WEAD_ENC_KEY_SIZE, hci_cc_wead_enc_key_size,
	       sizeof(stwuct hci_wp_wead_enc_key_size)),
	HCI_CC(HCI_OP_WEAD_INQ_WSP_TX_POWEW, hci_cc_wead_inq_wsp_tx_powew,
	       sizeof(stwuct hci_wp_wead_inq_wsp_tx_powew)),
	HCI_CC(HCI_OP_WEAD_DEF_EWW_DATA_WEPOWTING,
	       hci_cc_wead_def_eww_data_wepowting,
	       sizeof(stwuct hci_wp_wead_def_eww_data_wepowting)),
	HCI_CC_STATUS(HCI_OP_WWITE_DEF_EWW_DATA_WEPOWTING,
		      hci_cc_wwite_def_eww_data_wepowting),
	HCI_CC(HCI_OP_PIN_CODE_WEPWY, hci_cc_pin_code_wepwy,
	       sizeof(stwuct hci_wp_pin_code_wepwy)),
	HCI_CC(HCI_OP_PIN_CODE_NEG_WEPWY, hci_cc_pin_code_neg_wepwy,
	       sizeof(stwuct hci_wp_pin_code_neg_wepwy)),
	HCI_CC(HCI_OP_WEAD_WOCAW_OOB_DATA, hci_cc_wead_wocaw_oob_data,
	       sizeof(stwuct hci_wp_wead_wocaw_oob_data)),
	HCI_CC(HCI_OP_WEAD_WOCAW_OOB_EXT_DATA, hci_cc_wead_wocaw_oob_ext_data,
	       sizeof(stwuct hci_wp_wead_wocaw_oob_ext_data)),
	HCI_CC(HCI_OP_WE_WEAD_BUFFEW_SIZE, hci_cc_we_wead_buffew_size,
	       sizeof(stwuct hci_wp_we_wead_buffew_size)),
	HCI_CC(HCI_OP_WE_WEAD_WOCAW_FEATUWES, hci_cc_we_wead_wocaw_featuwes,
	       sizeof(stwuct hci_wp_we_wead_wocaw_featuwes)),
	HCI_CC(HCI_OP_WE_WEAD_ADV_TX_POWEW, hci_cc_we_wead_adv_tx_powew,
	       sizeof(stwuct hci_wp_we_wead_adv_tx_powew)),
	HCI_CC(HCI_OP_USEW_CONFIWM_WEPWY, hci_cc_usew_confiwm_wepwy,
	       sizeof(stwuct hci_wp_usew_confiwm_wepwy)),
	HCI_CC(HCI_OP_USEW_CONFIWM_NEG_WEPWY, hci_cc_usew_confiwm_neg_wepwy,
	       sizeof(stwuct hci_wp_usew_confiwm_wepwy)),
	HCI_CC(HCI_OP_USEW_PASSKEY_WEPWY, hci_cc_usew_passkey_wepwy,
	       sizeof(stwuct hci_wp_usew_confiwm_wepwy)),
	HCI_CC(HCI_OP_USEW_PASSKEY_NEG_WEPWY, hci_cc_usew_passkey_neg_wepwy,
	       sizeof(stwuct hci_wp_usew_confiwm_wepwy)),
	HCI_CC_STATUS(HCI_OP_WE_SET_WANDOM_ADDW, hci_cc_we_set_wandom_addw),
	HCI_CC_STATUS(HCI_OP_WE_SET_ADV_ENABWE, hci_cc_we_set_adv_enabwe),
	HCI_CC_STATUS(HCI_OP_WE_SET_SCAN_PAWAM, hci_cc_we_set_scan_pawam),
	HCI_CC_STATUS(HCI_OP_WE_SET_SCAN_ENABWE, hci_cc_we_set_scan_enabwe),
	HCI_CC(HCI_OP_WE_WEAD_ACCEPT_WIST_SIZE,
	       hci_cc_we_wead_accept_wist_size,
	       sizeof(stwuct hci_wp_we_wead_accept_wist_size)),
	HCI_CC_STATUS(HCI_OP_WE_CWEAW_ACCEPT_WIST, hci_cc_we_cweaw_accept_wist),
	HCI_CC_STATUS(HCI_OP_WE_ADD_TO_ACCEPT_WIST,
		      hci_cc_we_add_to_accept_wist),
	HCI_CC_STATUS(HCI_OP_WE_DEW_FWOM_ACCEPT_WIST,
		      hci_cc_we_dew_fwom_accept_wist),
	HCI_CC(HCI_OP_WE_WEAD_SUPPOWTED_STATES, hci_cc_we_wead_suppowted_states,
	       sizeof(stwuct hci_wp_we_wead_suppowted_states)),
	HCI_CC(HCI_OP_WE_WEAD_DEF_DATA_WEN, hci_cc_we_wead_def_data_wen,
	       sizeof(stwuct hci_wp_we_wead_def_data_wen)),
	HCI_CC_STATUS(HCI_OP_WE_WWITE_DEF_DATA_WEN,
		      hci_cc_we_wwite_def_data_wen),
	HCI_CC_STATUS(HCI_OP_WE_ADD_TO_WESOWV_WIST,
		      hci_cc_we_add_to_wesowv_wist),
	HCI_CC_STATUS(HCI_OP_WE_DEW_FWOM_WESOWV_WIST,
		      hci_cc_we_dew_fwom_wesowv_wist),
	HCI_CC_STATUS(HCI_OP_WE_CWEAW_WESOWV_WIST,
		      hci_cc_we_cweaw_wesowv_wist),
	HCI_CC(HCI_OP_WE_WEAD_WESOWV_WIST_SIZE, hci_cc_we_wead_wesowv_wist_size,
	       sizeof(stwuct hci_wp_we_wead_wesowv_wist_size)),
	HCI_CC_STATUS(HCI_OP_WE_SET_ADDW_WESOWV_ENABWE,
		      hci_cc_we_set_addw_wesowution_enabwe),
	HCI_CC(HCI_OP_WE_WEAD_MAX_DATA_WEN, hci_cc_we_wead_max_data_wen,
	       sizeof(stwuct hci_wp_we_wead_max_data_wen)),
	HCI_CC_STATUS(HCI_OP_WWITE_WE_HOST_SUPPOWTED,
		      hci_cc_wwite_we_host_suppowted),
	HCI_CC_STATUS(HCI_OP_WE_SET_ADV_PAWAM, hci_cc_set_adv_pawam),
	HCI_CC(HCI_OP_WEAD_WSSI, hci_cc_wead_wssi,
	       sizeof(stwuct hci_wp_wead_wssi)),
	HCI_CC(HCI_OP_WEAD_TX_POWEW, hci_cc_wead_tx_powew,
	       sizeof(stwuct hci_wp_wead_tx_powew)),
	HCI_CC_STATUS(HCI_OP_WWITE_SSP_DEBUG_MODE, hci_cc_wwite_ssp_debug_mode),
	HCI_CC_STATUS(HCI_OP_WE_SET_EXT_SCAN_PAWAMS,
		      hci_cc_we_set_ext_scan_pawam),
	HCI_CC_STATUS(HCI_OP_WE_SET_EXT_SCAN_ENABWE,
		      hci_cc_we_set_ext_scan_enabwe),
	HCI_CC_STATUS(HCI_OP_WE_SET_DEFAUWT_PHY, hci_cc_we_set_defauwt_phy),
	HCI_CC(HCI_OP_WE_WEAD_NUM_SUPPOWTED_ADV_SETS,
	       hci_cc_we_wead_num_adv_sets,
	       sizeof(stwuct hci_wp_we_wead_num_suppowted_adv_sets)),
	HCI_CC(HCI_OP_WE_SET_EXT_ADV_PAWAMS, hci_cc_set_ext_adv_pawam,
	       sizeof(stwuct hci_wp_we_set_ext_adv_pawams)),
	HCI_CC_STATUS(HCI_OP_WE_SET_EXT_ADV_ENABWE,
		      hci_cc_we_set_ext_adv_enabwe),
	HCI_CC_STATUS(HCI_OP_WE_SET_ADV_SET_WAND_ADDW,
		      hci_cc_we_set_adv_set_wandom_addw),
	HCI_CC_STATUS(HCI_OP_WE_WEMOVE_ADV_SET, hci_cc_we_wemove_adv_set),
	HCI_CC_STATUS(HCI_OP_WE_CWEAW_ADV_SETS, hci_cc_we_cweaw_adv_sets),
	HCI_CC_STATUS(HCI_OP_WE_SET_PEW_ADV_PAWAMS, hci_cc_set_pew_adv_pawam),
	HCI_CC_STATUS(HCI_OP_WE_SET_PEW_ADV_ENABWE,
		      hci_cc_we_set_pew_adv_enabwe),
	HCI_CC(HCI_OP_WE_WEAD_TWANSMIT_POWEW, hci_cc_we_wead_twansmit_powew,
	       sizeof(stwuct hci_wp_we_wead_twansmit_powew)),
	HCI_CC_STATUS(HCI_OP_WE_SET_PWIVACY_MODE, hci_cc_we_set_pwivacy_mode),
	HCI_CC(HCI_OP_WE_WEAD_BUFFEW_SIZE_V2, hci_cc_we_wead_buffew_size_v2,
	       sizeof(stwuct hci_wp_we_wead_buffew_size_v2)),
	HCI_CC_VW(HCI_OP_WE_SET_CIG_PAWAMS, hci_cc_we_set_cig_pawams,
		  sizeof(stwuct hci_wp_we_set_cig_pawams), HCI_MAX_EVENT_SIZE),
	HCI_CC(HCI_OP_WE_SETUP_ISO_PATH, hci_cc_we_setup_iso_path,
	       sizeof(stwuct hci_wp_we_setup_iso_path)),
};

static u8 hci_cc_func(stwuct hci_dev *hdev, const stwuct hci_cc *cc,
		      stwuct sk_buff *skb)
{
	void *data;

	if (skb->wen < cc->min_wen) {
		bt_dev_eww(hdev, "unexpected cc 0x%4.4x wength: %u < %u",
			   cc->op, skb->wen, cc->min_wen);
		wetuwn HCI_EWWOW_UNSPECIFIED;
	}

	/* Just wawn if the wength is ovew max_wen size it stiww be possibwe to
	 * pawtiawwy pawse the cc so weave to cawwback to decide if that is
	 * acceptabwe.
	 */
	if (skb->wen > cc->max_wen)
		bt_dev_wawn(hdev, "unexpected cc 0x%4.4x wength: %u > %u",
			    cc->op, skb->wen, cc->max_wen);

	data = hci_cc_skb_puww(hdev, skb, cc->op, cc->min_wen);
	if (!data)
		wetuwn HCI_EWWOW_UNSPECIFIED;

	wetuwn cc->func(hdev, data, skb);
}

static void hci_cmd_compwete_evt(stwuct hci_dev *hdev, void *data,
				 stwuct sk_buff *skb, u16 *opcode, u8 *status,
				 hci_weq_compwete_t *weq_compwete,
				 hci_weq_compwete_skb_t *weq_compwete_skb)
{
	stwuct hci_ev_cmd_compwete *ev = data;
	int i;

	*opcode = __we16_to_cpu(ev->opcode);

	bt_dev_dbg(hdev, "opcode 0x%4.4x", *opcode);

	fow (i = 0; i < AWWAY_SIZE(hci_cc_tabwe); i++) {
		if (hci_cc_tabwe[i].op == *opcode) {
			*status = hci_cc_func(hdev, &hci_cc_tabwe[i], skb);
			bweak;
		}
	}

	if (i == AWWAY_SIZE(hci_cc_tabwe)) {
		/* Unknown opcode, assume byte 0 contains the status, so
		 * that e.g. __hci_cmd_sync() pwopewwy wetuwns ewwows
		 * fow vendow specific commands send by HCI dwivews.
		 * If a vendow doesn't actuawwy fowwow this convention we may
		 * need to intwoduce a vendow CC tabwe in owdew to pwopewwy set
		 * the status.
		 */
		*status = skb->data[0];
	}

	handwe_cmd_cnt_and_timew(hdev, ev->ncmd);

	hci_weq_cmd_compwete(hdev, *opcode, *status, weq_compwete,
			     weq_compwete_skb);

	if (hci_dev_test_fwag(hdev, HCI_CMD_PENDING)) {
		bt_dev_eww(hdev,
			   "unexpected event fow opcode 0x%4.4x", *opcode);
		wetuwn;
	}

	if (atomic_wead(&hdev->cmd_cnt) && !skb_queue_empty(&hdev->cmd_q))
		queue_wowk(hdev->wowkqueue, &hdev->cmd_wowk);
}

static void hci_cs_we_cweate_cis(stwuct hci_dev *hdev, u8 status)
{
	stwuct hci_cp_we_cweate_cis *cp;
	boow pending = fawse;
	int i;

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	if (!status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_WE_CWEATE_CIS);
	if (!cp)
		wetuwn;

	hci_dev_wock(hdev);

	/* Wemove connection if command faiwed */
	fow (i = 0; cp->num_cis; cp->num_cis--, i++) {
		stwuct hci_conn *conn;
		u16 handwe;

		handwe = __we16_to_cpu(cp->cis[i].cis_handwe);

		conn = hci_conn_hash_wookup_handwe(hdev, handwe);
		if (conn) {
			if (test_and_cweaw_bit(HCI_CONN_CWEATE_CIS,
					       &conn->fwags))
				pending = twue;
			conn->state = BT_CWOSED;
			hci_connect_cfm(conn, status);
			hci_conn_dew(conn);
		}
	}

	if (pending)
		hci_we_cweate_cis_pending(hdev);

	hci_dev_unwock(hdev);
}

#define HCI_CS(_op, _func) \
{ \
	.op = _op, \
	.func = _func, \
}

static const stwuct hci_cs {
	u16  op;
	void (*func)(stwuct hci_dev *hdev, __u8 status);
} hci_cs_tabwe[] = {
	HCI_CS(HCI_OP_INQUIWY, hci_cs_inquiwy),
	HCI_CS(HCI_OP_CWEATE_CONN, hci_cs_cweate_conn),
	HCI_CS(HCI_OP_DISCONNECT, hci_cs_disconnect),
	HCI_CS(HCI_OP_ADD_SCO, hci_cs_add_sco),
	HCI_CS(HCI_OP_AUTH_WEQUESTED, hci_cs_auth_wequested),
	HCI_CS(HCI_OP_SET_CONN_ENCWYPT, hci_cs_set_conn_encwypt),
	HCI_CS(HCI_OP_WEMOTE_NAME_WEQ, hci_cs_wemote_name_weq),
	HCI_CS(HCI_OP_WEAD_WEMOTE_FEATUWES, hci_cs_wead_wemote_featuwes),
	HCI_CS(HCI_OP_WEAD_WEMOTE_EXT_FEATUWES,
	       hci_cs_wead_wemote_ext_featuwes),
	HCI_CS(HCI_OP_SETUP_SYNC_CONN, hci_cs_setup_sync_conn),
	HCI_CS(HCI_OP_ENHANCED_SETUP_SYNC_CONN,
	       hci_cs_enhanced_setup_sync_conn),
	HCI_CS(HCI_OP_SNIFF_MODE, hci_cs_sniff_mode),
	HCI_CS(HCI_OP_EXIT_SNIFF_MODE, hci_cs_exit_sniff_mode),
	HCI_CS(HCI_OP_SWITCH_WOWE, hci_cs_switch_wowe),
	HCI_CS(HCI_OP_WE_CWEATE_CONN, hci_cs_we_cweate_conn),
	HCI_CS(HCI_OP_WE_WEAD_WEMOTE_FEATUWES, hci_cs_we_wead_wemote_featuwes),
	HCI_CS(HCI_OP_WE_STAWT_ENC, hci_cs_we_stawt_enc),
	HCI_CS(HCI_OP_WE_EXT_CWEATE_CONN, hci_cs_we_ext_cweate_conn),
	HCI_CS(HCI_OP_WE_CWEATE_CIS, hci_cs_we_cweate_cis),
	HCI_CS(HCI_OP_WE_CWEATE_BIG, hci_cs_we_cweate_big),
};

static void hci_cmd_status_evt(stwuct hci_dev *hdev, void *data,
			       stwuct sk_buff *skb, u16 *opcode, u8 *status,
			       hci_weq_compwete_t *weq_compwete,
			       hci_weq_compwete_skb_t *weq_compwete_skb)
{
	stwuct hci_ev_cmd_status *ev = data;
	int i;

	*opcode = __we16_to_cpu(ev->opcode);
	*status = ev->status;

	bt_dev_dbg(hdev, "opcode 0x%4.4x", *opcode);

	fow (i = 0; i < AWWAY_SIZE(hci_cs_tabwe); i++) {
		if (hci_cs_tabwe[i].op == *opcode) {
			hci_cs_tabwe[i].func(hdev, ev->status);
			bweak;
		}
	}

	handwe_cmd_cnt_and_timew(hdev, ev->ncmd);

	/* Indicate wequest compwetion if the command faiwed. Awso, if
	 * we'we not waiting fow a speciaw event and we get a success
	 * command status we shouwd twy to fwag the wequest as compweted
	 * (since fow this kind of commands thewe wiww not be a command
	 * compwete event).
	 */
	if (ev->status || (hdev->sent_cmd && !hci_skb_event(hdev->sent_cmd))) {
		hci_weq_cmd_compwete(hdev, *opcode, ev->status, weq_compwete,
				     weq_compwete_skb);
		if (hci_dev_test_fwag(hdev, HCI_CMD_PENDING)) {
			bt_dev_eww(hdev, "unexpected event fow opcode 0x%4.4x",
				   *opcode);
			wetuwn;
		}
	}

	if (atomic_wead(&hdev->cmd_cnt) && !skb_queue_empty(&hdev->cmd_q))
		queue_wowk(hdev->wowkqueue, &hdev->cmd_wowk);
}

static void hci_hawdwawe_ewwow_evt(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_ev_hawdwawe_ewwow *ev = data;

	bt_dev_dbg(hdev, "code 0x%2.2x", ev->code);

	hdev->hw_ewwow_code = ev->code;

	queue_wowk(hdev->weq_wowkqueue, &hdev->ewwow_weset);
}

static void hci_wowe_change_evt(stwuct hci_dev *hdev, void *data,
				stwuct sk_buff *skb)
{
	stwuct hci_ev_wowe_change *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &ev->bdaddw);
	if (conn) {
		if (!ev->status)
			conn->wowe = ev->wowe;

		cweaw_bit(HCI_CONN_WSWITCH_PEND, &conn->fwags);

		hci_wowe_switch_cfm(conn, ev->status, ev->wowe);
	}

	hci_dev_unwock(hdev);
}

static void hci_num_comp_pkts_evt(stwuct hci_dev *hdev, void *data,
				  stwuct sk_buff *skb)
{
	stwuct hci_ev_num_comp_pkts *ev = data;
	int i;

	if (!hci_ev_skb_puww(hdev, skb, HCI_EV_NUM_COMP_PKTS,
			     fwex_awway_size(ev, handwes, ev->num)))
		wetuwn;

	if (hdev->fwow_ctw_mode != HCI_FWOW_CTW_MODE_PACKET_BASED) {
		bt_dev_eww(hdev, "wwong event fow mode %d", hdev->fwow_ctw_mode);
		wetuwn;
	}

	bt_dev_dbg(hdev, "num %d", ev->num);

	fow (i = 0; i < ev->num; i++) {
		stwuct hci_comp_pkts_info *info = &ev->handwes[i];
		stwuct hci_conn *conn;
		__u16  handwe, count;

		handwe = __we16_to_cpu(info->handwe);
		count  = __we16_to_cpu(info->count);

		conn = hci_conn_hash_wookup_handwe(hdev, handwe);
		if (!conn)
			continue;

		conn->sent -= count;

		switch (conn->type) {
		case ACW_WINK:
			hdev->acw_cnt += count;
			if (hdev->acw_cnt > hdev->acw_pkts)
				hdev->acw_cnt = hdev->acw_pkts;
			bweak;

		case WE_WINK:
			if (hdev->we_pkts) {
				hdev->we_cnt += count;
				if (hdev->we_cnt > hdev->we_pkts)
					hdev->we_cnt = hdev->we_pkts;
			} ewse {
				hdev->acw_cnt += count;
				if (hdev->acw_cnt > hdev->acw_pkts)
					hdev->acw_cnt = hdev->acw_pkts;
			}
			bweak;

		case SCO_WINK:
			hdev->sco_cnt += count;
			if (hdev->sco_cnt > hdev->sco_pkts)
				hdev->sco_cnt = hdev->sco_pkts;
			bweak;

		case ISO_WINK:
			if (hdev->iso_pkts) {
				hdev->iso_cnt += count;
				if (hdev->iso_cnt > hdev->iso_pkts)
					hdev->iso_cnt = hdev->iso_pkts;
			} ewse if (hdev->we_pkts) {
				hdev->we_cnt += count;
				if (hdev->we_cnt > hdev->we_pkts)
					hdev->we_cnt = hdev->we_pkts;
			} ewse {
				hdev->acw_cnt += count;
				if (hdev->acw_cnt > hdev->acw_pkts)
					hdev->acw_cnt = hdev->acw_pkts;
			}
			bweak;

		defauwt:
			bt_dev_eww(hdev, "unknown type %d conn %p",
				   conn->type, conn);
			bweak;
		}
	}

	queue_wowk(hdev->wowkqueue, &hdev->tx_wowk);
}

static stwuct hci_conn *__hci_conn_wookup_handwe(stwuct hci_dev *hdev,
						 __u16 handwe)
{
	stwuct hci_chan *chan;

	switch (hdev->dev_type) {
	case HCI_PWIMAWY:
		wetuwn hci_conn_hash_wookup_handwe(hdev, handwe);
	case HCI_AMP:
		chan = hci_chan_wookup_handwe(hdev, handwe);
		if (chan)
			wetuwn chan->conn;
		bweak;
	defauwt:
		bt_dev_eww(hdev, "unknown dev_type %d", hdev->dev_type);
		bweak;
	}

	wetuwn NUWW;
}

static void hci_num_comp_bwocks_evt(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_ev_num_comp_bwocks *ev = data;
	int i;

	if (!hci_ev_skb_puww(hdev, skb, HCI_EV_NUM_COMP_BWOCKS,
			     fwex_awway_size(ev, handwes, ev->num_hndw)))
		wetuwn;

	if (hdev->fwow_ctw_mode != HCI_FWOW_CTW_MODE_BWOCK_BASED) {
		bt_dev_eww(hdev, "wwong event fow mode %d",
			   hdev->fwow_ctw_mode);
		wetuwn;
	}

	bt_dev_dbg(hdev, "num_bwocks %d num_hndw %d", ev->num_bwocks,
		   ev->num_hndw);

	fow (i = 0; i < ev->num_hndw; i++) {
		stwuct hci_comp_bwocks_info *info = &ev->handwes[i];
		stwuct hci_conn *conn = NUWW;
		__u16  handwe, bwock_count;

		handwe = __we16_to_cpu(info->handwe);
		bwock_count = __we16_to_cpu(info->bwocks);

		conn = __hci_conn_wookup_handwe(hdev, handwe);
		if (!conn)
			continue;

		conn->sent -= bwock_count;

		switch (conn->type) {
		case ACW_WINK:
		case AMP_WINK:
			hdev->bwock_cnt += bwock_count;
			if (hdev->bwock_cnt > hdev->num_bwocks)
				hdev->bwock_cnt = hdev->num_bwocks;
			bweak;

		defauwt:
			bt_dev_eww(hdev, "unknown type %d conn %p",
				   conn->type, conn);
			bweak;
		}
	}

	queue_wowk(hdev->wowkqueue, &hdev->tx_wowk);
}

static void hci_mode_change_evt(stwuct hci_dev *hdev, void *data,
				stwuct sk_buff *skb)
{
	stwuct hci_ev_mode_change *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(ev->handwe));
	if (conn) {
		conn->mode = ev->mode;

		if (!test_and_cweaw_bit(HCI_CONN_MODE_CHANGE_PEND,
					&conn->fwags)) {
			if (conn->mode == HCI_CM_ACTIVE)
				set_bit(HCI_CONN_POWEW_SAVE, &conn->fwags);
			ewse
				cweaw_bit(HCI_CONN_POWEW_SAVE, &conn->fwags);
		}

		if (test_and_cweaw_bit(HCI_CONN_SCO_SETUP_PEND, &conn->fwags))
			hci_sco_setup(conn, ev->status);
	}

	hci_dev_unwock(hdev);
}

static void hci_pin_code_wequest_evt(stwuct hci_dev *hdev, void *data,
				     stwuct sk_buff *skb)
{
	stwuct hci_ev_pin_code_weq *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "");

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &ev->bdaddw);
	if (!conn)
		goto unwock;

	if (conn->state == BT_CONNECTED) {
		hci_conn_howd(conn);
		conn->disc_timeout = HCI_PAIWING_TIMEOUT;
		hci_conn_dwop(conn);
	}

	if (!hci_dev_test_fwag(hdev, HCI_BONDABWE) &&
	    !test_bit(HCI_CONN_AUTH_INITIATOW, &conn->fwags)) {
		hci_send_cmd(hdev, HCI_OP_PIN_CODE_NEG_WEPWY,
			     sizeof(ev->bdaddw), &ev->bdaddw);
	} ewse if (hci_dev_test_fwag(hdev, HCI_MGMT)) {
		u8 secuwe;

		if (conn->pending_sec_wevew == BT_SECUWITY_HIGH)
			secuwe = 1;
		ewse
			secuwe = 0;

		mgmt_pin_code_wequest(hdev, &ev->bdaddw, secuwe);
	}

unwock:
	hci_dev_unwock(hdev);
}

static void conn_set_key(stwuct hci_conn *conn, u8 key_type, u8 pin_wen)
{
	if (key_type == HCI_WK_CHANGED_COMBINATION)
		wetuwn;

	conn->pin_wength = pin_wen;
	conn->key_type = key_type;

	switch (key_type) {
	case HCI_WK_WOCAW_UNIT:
	case HCI_WK_WEMOTE_UNIT:
	case HCI_WK_DEBUG_COMBINATION:
		wetuwn;
	case HCI_WK_COMBINATION:
		if (pin_wen == 16)
			conn->pending_sec_wevew = BT_SECUWITY_HIGH;
		ewse
			conn->pending_sec_wevew = BT_SECUWITY_MEDIUM;
		bweak;
	case HCI_WK_UNAUTH_COMBINATION_P192:
	case HCI_WK_UNAUTH_COMBINATION_P256:
		conn->pending_sec_wevew = BT_SECUWITY_MEDIUM;
		bweak;
	case HCI_WK_AUTH_COMBINATION_P192:
		conn->pending_sec_wevew = BT_SECUWITY_HIGH;
		bweak;
	case HCI_WK_AUTH_COMBINATION_P256:
		conn->pending_sec_wevew = BT_SECUWITY_FIPS;
		bweak;
	}
}

static void hci_wink_key_wequest_evt(stwuct hci_dev *hdev, void *data,
				     stwuct sk_buff *skb)
{
	stwuct hci_ev_wink_key_weq *ev = data;
	stwuct hci_cp_wink_key_wepwy cp;
	stwuct hci_conn *conn;
	stwuct wink_key *key;

	bt_dev_dbg(hdev, "");

	if (!hci_dev_test_fwag(hdev, HCI_MGMT))
		wetuwn;

	hci_dev_wock(hdev);

	key = hci_find_wink_key(hdev, &ev->bdaddw);
	if (!key) {
		bt_dev_dbg(hdev, "wink key not found fow %pMW", &ev->bdaddw);
		goto not_found;
	}

	bt_dev_dbg(hdev, "found key type %u fow %pMW", key->type, &ev->bdaddw);

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &ev->bdaddw);
	if (conn) {
		cweaw_bit(HCI_CONN_NEW_WINK_KEY, &conn->fwags);

		if ((key->type == HCI_WK_UNAUTH_COMBINATION_P192 ||
		     key->type == HCI_WK_UNAUTH_COMBINATION_P256) &&
		    conn->auth_type != 0xff && (conn->auth_type & 0x01)) {
			bt_dev_dbg(hdev, "ignowing unauthenticated key");
			goto not_found;
		}

		if (key->type == HCI_WK_COMBINATION && key->pin_wen < 16 &&
		    (conn->pending_sec_wevew == BT_SECUWITY_HIGH ||
		     conn->pending_sec_wevew == BT_SECUWITY_FIPS)) {
			bt_dev_dbg(hdev, "ignowing key unauthenticated fow high secuwity");
			goto not_found;
		}

		conn_set_key(conn, key->type, key->pin_wen);
	}

	bacpy(&cp.bdaddw, &ev->bdaddw);
	memcpy(cp.wink_key, key->vaw, HCI_WINK_KEY_SIZE);

	hci_send_cmd(hdev, HCI_OP_WINK_KEY_WEPWY, sizeof(cp), &cp);

	hci_dev_unwock(hdev);

	wetuwn;

not_found:
	hci_send_cmd(hdev, HCI_OP_WINK_KEY_NEG_WEPWY, 6, &ev->bdaddw);
	hci_dev_unwock(hdev);
}

static void hci_wink_key_notify_evt(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_ev_wink_key_notify *ev = data;
	stwuct hci_conn *conn;
	stwuct wink_key *key;
	boow pewsistent;
	u8 pin_wen = 0;

	bt_dev_dbg(hdev, "");

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &ev->bdaddw);
	if (!conn)
		goto unwock;

	/* Ignowe NUWW wink key against CVE-2020-26555 */
	if (!cwypto_memneq(ev->wink_key, ZEWO_KEY, HCI_WINK_KEY_SIZE)) {
		bt_dev_dbg(hdev, "Ignowe NUWW wink key (ZEWO KEY) fow %pMW",
			   &ev->bdaddw);
		hci_disconnect(conn, HCI_EWWOW_AUTH_FAIWUWE);
		hci_conn_dwop(conn);
		goto unwock;
	}

	hci_conn_howd(conn);
	conn->disc_timeout = HCI_DISCONN_TIMEOUT;
	hci_conn_dwop(conn);

	set_bit(HCI_CONN_NEW_WINK_KEY, &conn->fwags);
	conn_set_key(conn, ev->key_type, conn->pin_wength);

	if (!hci_dev_test_fwag(hdev, HCI_MGMT))
		goto unwock;

	key = hci_add_wink_key(hdev, conn, &ev->bdaddw, ev->wink_key,
			        ev->key_type, pin_wen, &pewsistent);
	if (!key)
		goto unwock;

	/* Update connection infowmation since adding the key wiww have
	 * fixed up the type in the case of changed combination keys.
	 */
	if (ev->key_type == HCI_WK_CHANGED_COMBINATION)
		conn_set_key(conn, key->type, key->pin_wen);

	mgmt_new_wink_key(hdev, key, pewsistent);

	/* Keep debug keys awound onwy if the HCI_KEEP_DEBUG_KEYS fwag
	 * is set. If it's not set simpwy wemove the key fwom the kewnew
	 * wist (we've stiww notified usew space about it but with
	 * stowe_hint being 0).
	 */
	if (key->type == HCI_WK_DEBUG_COMBINATION &&
	    !hci_dev_test_fwag(hdev, HCI_KEEP_DEBUG_KEYS)) {
		wist_dew_wcu(&key->wist);
		kfwee_wcu(key, wcu);
		goto unwock;
	}

	if (pewsistent)
		cweaw_bit(HCI_CONN_FWUSH_KEY, &conn->fwags);
	ewse
		set_bit(HCI_CONN_FWUSH_KEY, &conn->fwags);

unwock:
	hci_dev_unwock(hdev);
}

static void hci_cwock_offset_evt(stwuct hci_dev *hdev, void *data,
				 stwuct sk_buff *skb)
{
	stwuct hci_ev_cwock_offset *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(ev->handwe));
	if (conn && !ev->status) {
		stwuct inquiwy_entwy *ie;

		ie = hci_inquiwy_cache_wookup(hdev, &conn->dst);
		if (ie) {
			ie->data.cwock_offset = ev->cwock_offset;
			ie->timestamp = jiffies;
		}
	}

	hci_dev_unwock(hdev);
}

static void hci_pkt_type_change_evt(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_ev_pkt_type_change *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(ev->handwe));
	if (conn && !ev->status)
		conn->pkt_type = __we16_to_cpu(ev->pkt_type);

	hci_dev_unwock(hdev);
}

static void hci_pscan_wep_mode_evt(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_ev_pscan_wep_mode *ev = data;
	stwuct inquiwy_entwy *ie;

	bt_dev_dbg(hdev, "");

	hci_dev_wock(hdev);

	ie = hci_inquiwy_cache_wookup(hdev, &ev->bdaddw);
	if (ie) {
		ie->data.pscan_wep_mode = ev->pscan_wep_mode;
		ie->timestamp = jiffies;
	}

	hci_dev_unwock(hdev);
}

static void hci_inquiwy_wesuwt_with_wssi_evt(stwuct hci_dev *hdev, void *edata,
					     stwuct sk_buff *skb)
{
	stwuct hci_ev_inquiwy_wesuwt_wssi *ev = edata;
	stwuct inquiwy_data data;
	int i;

	bt_dev_dbg(hdev, "num_wsp %d", ev->num);

	if (!ev->num)
		wetuwn;

	if (hci_dev_test_fwag(hdev, HCI_PEWIODIC_INQ))
		wetuwn;

	hci_dev_wock(hdev);

	if (skb->wen == awway_size(ev->num,
				   sizeof(stwuct inquiwy_info_wssi_pscan))) {
		stwuct inquiwy_info_wssi_pscan *info;

		fow (i = 0; i < ev->num; i++) {
			u32 fwags;

			info = hci_ev_skb_puww(hdev, skb,
					       HCI_EV_INQUIWY_WESUWT_WITH_WSSI,
					       sizeof(*info));
			if (!info) {
				bt_dev_eww(hdev, "Mawfowmed HCI Event: 0x%2.2x",
					   HCI_EV_INQUIWY_WESUWT_WITH_WSSI);
				goto unwock;
			}

			bacpy(&data.bdaddw, &info->bdaddw);
			data.pscan_wep_mode	= info->pscan_wep_mode;
			data.pscan_pewiod_mode	= info->pscan_pewiod_mode;
			data.pscan_mode		= info->pscan_mode;
			memcpy(data.dev_cwass, info->dev_cwass, 3);
			data.cwock_offset	= info->cwock_offset;
			data.wssi		= info->wssi;
			data.ssp_mode		= 0x00;

			fwags = hci_inquiwy_cache_update(hdev, &data, fawse);

			mgmt_device_found(hdev, &info->bdaddw, ACW_WINK, 0x00,
					  info->dev_cwass, info->wssi,
					  fwags, NUWW, 0, NUWW, 0, 0);
		}
	} ewse if (skb->wen == awway_size(ev->num,
					  sizeof(stwuct inquiwy_info_wssi))) {
		stwuct inquiwy_info_wssi *info;

		fow (i = 0; i < ev->num; i++) {
			u32 fwags;

			info = hci_ev_skb_puww(hdev, skb,
					       HCI_EV_INQUIWY_WESUWT_WITH_WSSI,
					       sizeof(*info));
			if (!info) {
				bt_dev_eww(hdev, "Mawfowmed HCI Event: 0x%2.2x",
					   HCI_EV_INQUIWY_WESUWT_WITH_WSSI);
				goto unwock;
			}

			bacpy(&data.bdaddw, &info->bdaddw);
			data.pscan_wep_mode	= info->pscan_wep_mode;
			data.pscan_pewiod_mode	= info->pscan_pewiod_mode;
			data.pscan_mode		= 0x00;
			memcpy(data.dev_cwass, info->dev_cwass, 3);
			data.cwock_offset	= info->cwock_offset;
			data.wssi		= info->wssi;
			data.ssp_mode		= 0x00;

			fwags = hci_inquiwy_cache_update(hdev, &data, fawse);

			mgmt_device_found(hdev, &info->bdaddw, ACW_WINK, 0x00,
					  info->dev_cwass, info->wssi,
					  fwags, NUWW, 0, NUWW, 0, 0);
		}
	} ewse {
		bt_dev_eww(hdev, "Mawfowmed HCI Event: 0x%2.2x",
			   HCI_EV_INQUIWY_WESUWT_WITH_WSSI);
	}
unwock:
	hci_dev_unwock(hdev);
}

static void hci_wemote_ext_featuwes_evt(stwuct hci_dev *hdev, void *data,
					stwuct sk_buff *skb)
{
	stwuct hci_ev_wemote_ext_featuwes *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(ev->handwe));
	if (!conn)
		goto unwock;

	if (ev->page < HCI_MAX_PAGES)
		memcpy(conn->featuwes[ev->page], ev->featuwes, 8);

	if (!ev->status && ev->page == 0x01) {
		stwuct inquiwy_entwy *ie;

		ie = hci_inquiwy_cache_wookup(hdev, &conn->dst);
		if (ie)
			ie->data.ssp_mode = (ev->featuwes[0] & WMP_HOST_SSP);

		if (ev->featuwes[0] & WMP_HOST_SSP) {
			set_bit(HCI_CONN_SSP_ENABWED, &conn->fwags);
		} ewse {
			/* It is mandatowy by the Bwuetooth specification that
			 * Extended Inquiwy Wesuwts awe onwy used when Secuwe
			 * Simpwe Paiwing is enabwed, but some devices viowate
			 * this.
			 *
			 * To make these devices wowk, the intewnaw SSP
			 * enabwed fwag needs to be cweawed if the wemote host
			 * featuwes do not indicate SSP suppowt */
			cweaw_bit(HCI_CONN_SSP_ENABWED, &conn->fwags);
		}

		if (ev->featuwes[0] & WMP_HOST_SC)
			set_bit(HCI_CONN_SC_ENABWED, &conn->fwags);
	}

	if (conn->state != BT_CONFIG)
		goto unwock;

	if (!ev->status && !test_bit(HCI_CONN_MGMT_CONNECTED, &conn->fwags)) {
		stwuct hci_cp_wemote_name_weq cp;
		memset(&cp, 0, sizeof(cp));
		bacpy(&cp.bdaddw, &conn->dst);
		cp.pscan_wep_mode = 0x02;
		hci_send_cmd(hdev, HCI_OP_WEMOTE_NAME_WEQ, sizeof(cp), &cp);
	} ewse if (!test_and_set_bit(HCI_CONN_MGMT_CONNECTED, &conn->fwags))
		mgmt_device_connected(hdev, conn, NUWW, 0);

	if (!hci_outgoing_auth_needed(hdev, conn)) {
		conn->state = BT_CONNECTED;
		hci_connect_cfm(conn, ev->status);
		hci_conn_dwop(conn);
	}

unwock:
	hci_dev_unwock(hdev);
}

static void hci_sync_conn_compwete_evt(stwuct hci_dev *hdev, void *data,
				       stwuct sk_buff *skb)
{
	stwuct hci_ev_sync_conn_compwete *ev = data;
	stwuct hci_conn *conn;
	u8 status = ev->status;

	switch (ev->wink_type) {
	case SCO_WINK:
	case ESCO_WINK:
		bweak;
	defauwt:
		/* As pew Cowe 5.3 Vow 4 Pawt E 7.7.35 (p.2219), Wink_Type
		 * fow HCI_Synchwonous_Connection_Compwete is wimited to
		 * eithew SCO ow eSCO
		 */
		bt_dev_eww(hdev, "Ignowing connect compwete event fow invawid wink type");
		wetuwn;
	}

	bt_dev_dbg(hdev, "status 0x%2.2x", status);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_ba(hdev, ev->wink_type, &ev->bdaddw);
	if (!conn) {
		if (ev->wink_type == ESCO_WINK)
			goto unwock;

		/* When the wink type in the event indicates SCO connection
		 * and wookup of the connection object faiws, then check
		 * if an eSCO connection object exists.
		 *
		 * The cowe wimits the synchwonous connections to eithew
		 * SCO ow eSCO. The eSCO connection is pwefewwed and twied
		 * to be setup fiwst and untiw successfuwwy estabwished,
		 * the wink type wiww be hinted as eSCO.
		 */
		conn = hci_conn_hash_wookup_ba(hdev, ESCO_WINK, &ev->bdaddw);
		if (!conn)
			goto unwock;
	}

	/* The HCI_Synchwonous_Connection_Compwete event is onwy sent once pew connection.
	 * Pwocessing it mowe than once pew connection can cowwupt kewnew memowy.
	 *
	 * As the connection handwe is set hewe fow the fiwst time, it indicates
	 * whethew the connection is awweady set up.
	 */
	if (!HCI_CONN_HANDWE_UNSET(conn->handwe)) {
		bt_dev_eww(hdev, "Ignowing HCI_Sync_Conn_Compwete event fow existing connection");
		goto unwock;
	}

	switch (status) {
	case 0x00:
		status = hci_conn_set_handwe(conn, __we16_to_cpu(ev->handwe));
		if (status) {
			conn->state = BT_CWOSED;
			bweak;
		}

		conn->state  = BT_CONNECTED;
		conn->type   = ev->wink_type;

		hci_debugfs_cweate_conn(conn);
		hci_conn_add_sysfs(conn);
		bweak;

	case 0x10:	/* Connection Accept Timeout */
	case 0x0d:	/* Connection Wejected due to Wimited Wesouwces */
	case 0x11:	/* Unsuppowted Featuwe ow Pawametew Vawue */
	case 0x1c:	/* SCO intewvaw wejected */
	case 0x1a:	/* Unsuppowted Wemote Featuwe */
	case 0x1e:	/* Invawid WMP Pawametews */
	case 0x1f:	/* Unspecified ewwow */
	case 0x20:	/* Unsuppowted WMP Pawametew vawue */
		if (conn->out) {
			conn->pkt_type = (hdev->esco_type & SCO_ESCO_MASK) |
					(hdev->esco_type & EDW_ESCO_MASK);
			if (hci_setup_sync(conn, conn->pawent->handwe))
				goto unwock;
		}
		fawwthwough;

	defauwt:
		conn->state = BT_CWOSED;
		bweak;
	}

	bt_dev_dbg(hdev, "SCO connected with aiw mode: %02x", ev->aiw_mode);
	/* Notify onwy in case of SCO ovew HCI twanspowt data path which
	 * is zewo and non-zewo vawue shaww be non-HCI twanspowt data path
	 */
	if (conn->codec.data_path == 0 && hdev->notify) {
		switch (ev->aiw_mode) {
		case 0x02:
			hdev->notify(hdev, HCI_NOTIFY_ENABWE_SCO_CVSD);
			bweak;
		case 0x03:
			hdev->notify(hdev, HCI_NOTIFY_ENABWE_SCO_TWANSP);
			bweak;
		}
	}

	hci_connect_cfm(conn, status);
	if (status)
		hci_conn_dew(conn);

unwock:
	hci_dev_unwock(hdev);
}

static inwine size_t eiw_get_wength(u8 *eiw, size_t eiw_wen)
{
	size_t pawsed = 0;

	whiwe (pawsed < eiw_wen) {
		u8 fiewd_wen = eiw[0];

		if (fiewd_wen == 0)
			wetuwn pawsed;

		pawsed += fiewd_wen + 1;
		eiw += fiewd_wen + 1;
	}

	wetuwn eiw_wen;
}

static void hci_extended_inquiwy_wesuwt_evt(stwuct hci_dev *hdev, void *edata,
					    stwuct sk_buff *skb)
{
	stwuct hci_ev_ext_inquiwy_wesuwt *ev = edata;
	stwuct inquiwy_data data;
	size_t eiw_wen;
	int i;

	if (!hci_ev_skb_puww(hdev, skb, HCI_EV_EXTENDED_INQUIWY_WESUWT,
			     fwex_awway_size(ev, info, ev->num)))
		wetuwn;

	bt_dev_dbg(hdev, "num %d", ev->num);

	if (!ev->num)
		wetuwn;

	if (hci_dev_test_fwag(hdev, HCI_PEWIODIC_INQ))
		wetuwn;

	hci_dev_wock(hdev);

	fow (i = 0; i < ev->num; i++) {
		stwuct extended_inquiwy_info *info = &ev->info[i];
		u32 fwags;
		boow name_known;

		bacpy(&data.bdaddw, &info->bdaddw);
		data.pscan_wep_mode	= info->pscan_wep_mode;
		data.pscan_pewiod_mode	= info->pscan_pewiod_mode;
		data.pscan_mode		= 0x00;
		memcpy(data.dev_cwass, info->dev_cwass, 3);
		data.cwock_offset	= info->cwock_offset;
		data.wssi		= info->wssi;
		data.ssp_mode		= 0x01;

		if (hci_dev_test_fwag(hdev, HCI_MGMT))
			name_known = eiw_get_data(info->data,
						  sizeof(info->data),
						  EIW_NAME_COMPWETE, NUWW);
		ewse
			name_known = twue;

		fwags = hci_inquiwy_cache_update(hdev, &data, name_known);

		eiw_wen = eiw_get_wength(info->data, sizeof(info->data));

		mgmt_device_found(hdev, &info->bdaddw, ACW_WINK, 0x00,
				  info->dev_cwass, info->wssi,
				  fwags, info->data, eiw_wen, NUWW, 0, 0);
	}

	hci_dev_unwock(hdev);
}

static void hci_key_wefwesh_compwete_evt(stwuct hci_dev *hdev, void *data,
					 stwuct sk_buff *skb)
{
	stwuct hci_ev_key_wefwesh_compwete *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x handwe 0x%4.4x", ev->status,
		   __we16_to_cpu(ev->handwe));

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(ev->handwe));
	if (!conn)
		goto unwock;

	/* Fow BW/EDW the necessawy steps awe taken thwough the
	 * auth_compwete event.
	 */
	if (conn->type != WE_WINK)
		goto unwock;

	if (!ev->status)
		conn->sec_wevew = conn->pending_sec_wevew;

	cweaw_bit(HCI_CONN_ENCWYPT_PEND, &conn->fwags);

	if (ev->status && conn->state == BT_CONNECTED) {
		hci_disconnect(conn, HCI_EWWOW_AUTH_FAIWUWE);
		hci_conn_dwop(conn);
		goto unwock;
	}

	if (conn->state == BT_CONFIG) {
		if (!ev->status)
			conn->state = BT_CONNECTED;

		hci_connect_cfm(conn, ev->status);
		hci_conn_dwop(conn);
	} ewse {
		hci_auth_cfm(conn, ev->status);

		hci_conn_howd(conn);
		conn->disc_timeout = HCI_DISCONN_TIMEOUT;
		hci_conn_dwop(conn);
	}

unwock:
	hci_dev_unwock(hdev);
}

static u8 hci_get_auth_weq(stwuct hci_conn *conn)
{
	/* If wemote wequests no-bonding fowwow that wead */
	if (conn->wemote_auth == HCI_AT_NO_BONDING ||
	    conn->wemote_auth == HCI_AT_NO_BONDING_MITM)
		wetuwn conn->wemote_auth | (conn->auth_type & 0x01);

	/* If both wemote and wocaw have enough IO capabiwities, wequiwe
	 * MITM pwotection
	 */
	if (conn->wemote_cap != HCI_IO_NO_INPUT_OUTPUT &&
	    conn->io_capabiwity != HCI_IO_NO_INPUT_OUTPUT)
		wetuwn conn->wemote_auth | 0x01;

	/* No MITM pwotection possibwe so ignowe wemote wequiwement */
	wetuwn (conn->wemote_auth & ~0x01) | (conn->auth_type & 0x01);
}

static u8 bwedw_oob_data_pwesent(stwuct hci_conn *conn)
{
	stwuct hci_dev *hdev = conn->hdev;
	stwuct oob_data *data;

	data = hci_find_wemote_oob_data(hdev, &conn->dst, BDADDW_BWEDW);
	if (!data)
		wetuwn 0x00;

	if (bwedw_sc_enabwed(hdev)) {
		/* When Secuwe Connections is enabwed, then just
		 * wetuwn the pwesent vawue stowed with the OOB
		 * data. The stowed vawue contains the wight pwesent
		 * infowmation. Howevew it can onwy be twusted when
		 * not in Secuwe Connection Onwy mode.
		 */
		if (!hci_dev_test_fwag(hdev, HCI_SC_ONWY))
			wetuwn data->pwesent;

		/* When Secuwe Connections Onwy mode is enabwed, then
		 * the P-256 vawues awe wequiwed. If they awe not
		 * avaiwabwe, then do not decwawe that OOB data is
		 * pwesent.
		 */
		if (!cwypto_memneq(data->wand256, ZEWO_KEY, 16) ||
		    !cwypto_memneq(data->hash256, ZEWO_KEY, 16))
			wetuwn 0x00;

		wetuwn 0x02;
	}

	/* When Secuwe Connections is not enabwed ow actuawwy
	 * not suppowted by the hawdwawe, then check that if
	 * P-192 data vawues awe pwesent.
	 */
	if (!cwypto_memneq(data->wand192, ZEWO_KEY, 16) ||
	    !cwypto_memneq(data->hash192, ZEWO_KEY, 16))
		wetuwn 0x00;

	wetuwn 0x01;
}

static void hci_io_capa_wequest_evt(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_ev_io_capa_wequest *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "");

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &ev->bdaddw);
	if (!conn || !hci_conn_ssp_enabwed(conn))
		goto unwock;

	hci_conn_howd(conn);

	if (!hci_dev_test_fwag(hdev, HCI_MGMT))
		goto unwock;

	/* Awwow paiwing if we'we paiwabwe, the initiatows of the
	 * paiwing ow if the wemote is not wequesting bonding.
	 */
	if (hci_dev_test_fwag(hdev, HCI_BONDABWE) ||
	    test_bit(HCI_CONN_AUTH_INITIATOW, &conn->fwags) ||
	    (conn->wemote_auth & ~0x01) == HCI_AT_NO_BONDING) {
		stwuct hci_cp_io_capabiwity_wepwy cp;

		bacpy(&cp.bdaddw, &ev->bdaddw);
		/* Change the IO capabiwity fwom KeyboawdDispway
		 * to DispwayYesNo as it is not suppowted by BT spec. */
		cp.capabiwity = (conn->io_capabiwity == 0x04) ?
				HCI_IO_DISPWAY_YESNO : conn->io_capabiwity;

		/* If we awe initiatows, thewe is no wemote infowmation yet */
		if (conn->wemote_auth == 0xff) {
			/* Wequest MITM pwotection if ouw IO caps awwow it
			 * except fow the no-bonding case.
			 */
			if (conn->io_capabiwity != HCI_IO_NO_INPUT_OUTPUT &&
			    conn->auth_type != HCI_AT_NO_BONDING)
				conn->auth_type |= 0x01;
		} ewse {
			conn->auth_type = hci_get_auth_weq(conn);
		}

		/* If we'we not bondabwe, fowce one of the non-bondabwe
		 * authentication wequiwement vawues.
		 */
		if (!hci_dev_test_fwag(hdev, HCI_BONDABWE))
			conn->auth_type &= HCI_AT_NO_BONDING_MITM;

		cp.authentication = conn->auth_type;
		cp.oob_data = bwedw_oob_data_pwesent(conn);

		hci_send_cmd(hdev, HCI_OP_IO_CAPABIWITY_WEPWY,
			     sizeof(cp), &cp);
	} ewse {
		stwuct hci_cp_io_capabiwity_neg_wepwy cp;

		bacpy(&cp.bdaddw, &ev->bdaddw);
		cp.weason = HCI_EWWOW_PAIWING_NOT_AWWOWED;

		hci_send_cmd(hdev, HCI_OP_IO_CAPABIWITY_NEG_WEPWY,
			     sizeof(cp), &cp);
	}

unwock:
	hci_dev_unwock(hdev);
}

static void hci_io_capa_wepwy_evt(stwuct hci_dev *hdev, void *data,
				  stwuct sk_buff *skb)
{
	stwuct hci_ev_io_capa_wepwy *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "");

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &ev->bdaddw);
	if (!conn)
		goto unwock;

	conn->wemote_cap = ev->capabiwity;
	conn->wemote_auth = ev->authentication;

unwock:
	hci_dev_unwock(hdev);
}

static void hci_usew_confiwm_wequest_evt(stwuct hci_dev *hdev, void *data,
					 stwuct sk_buff *skb)
{
	stwuct hci_ev_usew_confiwm_weq *ev = data;
	int woc_mitm, wem_mitm, confiwm_hint = 0;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "");

	hci_dev_wock(hdev);

	if (!hci_dev_test_fwag(hdev, HCI_MGMT))
		goto unwock;

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &ev->bdaddw);
	if (!conn)
		goto unwock;

	woc_mitm = (conn->auth_type & 0x01);
	wem_mitm = (conn->wemote_auth & 0x01);

	/* If we wequiwe MITM but the wemote device can't pwovide that
	 * (it has NoInputNoOutput) then weject the confiwmation
	 * wequest. We check the secuwity wevew hewe since it doesn't
	 * necessawiwy match conn->auth_type.
	 */
	if (conn->pending_sec_wevew > BT_SECUWITY_MEDIUM &&
	    conn->wemote_cap == HCI_IO_NO_INPUT_OUTPUT) {
		bt_dev_dbg(hdev, "Wejecting wequest: wemote device can't pwovide MITM");
		hci_send_cmd(hdev, HCI_OP_USEW_CONFIWM_NEG_WEPWY,
			     sizeof(ev->bdaddw), &ev->bdaddw);
		goto unwock;
	}

	/* If no side wequiwes MITM pwotection; auto-accept */
	if ((!woc_mitm || conn->wemote_cap == HCI_IO_NO_INPUT_OUTPUT) &&
	    (!wem_mitm || conn->io_capabiwity == HCI_IO_NO_INPUT_OUTPUT)) {

		/* If we'we not the initiatows wequest authowization to
		 * pwoceed fwom usew space (mgmt_usew_confiwm with
		 * confiwm_hint set to 1). The exception is if neithew
		 * side had MITM ow if the wocaw IO capabiwity is
		 * NoInputNoOutput, in which case we do auto-accept
		 */
		if (!test_bit(HCI_CONN_AUTH_PEND, &conn->fwags) &&
		    conn->io_capabiwity != HCI_IO_NO_INPUT_OUTPUT &&
		    (woc_mitm || wem_mitm)) {
			bt_dev_dbg(hdev, "Confiwming auto-accept as acceptow");
			confiwm_hint = 1;
			goto confiwm;
		}

		/* If thewe awweady exists wink key in wocaw host, weave the
		 * decision to usew space since the wemote device couwd be
		 * wegitimate ow mawicious.
		 */
		if (hci_find_wink_key(hdev, &ev->bdaddw)) {
			bt_dev_dbg(hdev, "Wocaw host awweady has wink key");
			confiwm_hint = 1;
			goto confiwm;
		}

		BT_DBG("Auto-accept of usew confiwmation with %ums deway",
		       hdev->auto_accept_deway);

		if (hdev->auto_accept_deway > 0) {
			int deway = msecs_to_jiffies(hdev->auto_accept_deway);
			queue_dewayed_wowk(conn->hdev->wowkqueue,
					   &conn->auto_accept_wowk, deway);
			goto unwock;
		}

		hci_send_cmd(hdev, HCI_OP_USEW_CONFIWM_WEPWY,
			     sizeof(ev->bdaddw), &ev->bdaddw);
		goto unwock;
	}

confiwm:
	mgmt_usew_confiwm_wequest(hdev, &ev->bdaddw, ACW_WINK, 0,
				  we32_to_cpu(ev->passkey), confiwm_hint);

unwock:
	hci_dev_unwock(hdev);
}

static void hci_usew_passkey_wequest_evt(stwuct hci_dev *hdev, void *data,
					 stwuct sk_buff *skb)
{
	stwuct hci_ev_usew_passkey_weq *ev = data;

	bt_dev_dbg(hdev, "");

	if (hci_dev_test_fwag(hdev, HCI_MGMT))
		mgmt_usew_passkey_wequest(hdev, &ev->bdaddw, ACW_WINK, 0);
}

static void hci_usew_passkey_notify_evt(stwuct hci_dev *hdev, void *data,
					stwuct sk_buff *skb)
{
	stwuct hci_ev_usew_passkey_notify *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "");

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &ev->bdaddw);
	if (!conn)
		wetuwn;

	conn->passkey_notify = __we32_to_cpu(ev->passkey);
	conn->passkey_entewed = 0;

	if (hci_dev_test_fwag(hdev, HCI_MGMT))
		mgmt_usew_passkey_notify(hdev, &conn->dst, conn->type,
					 conn->dst_type, conn->passkey_notify,
					 conn->passkey_entewed);
}

static void hci_keypwess_notify_evt(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_ev_keypwess_notify *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "");

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &ev->bdaddw);
	if (!conn)
		wetuwn;

	switch (ev->type) {
	case HCI_KEYPWESS_STAWTED:
		conn->passkey_entewed = 0;
		wetuwn;

	case HCI_KEYPWESS_ENTEWED:
		conn->passkey_entewed++;
		bweak;

	case HCI_KEYPWESS_EWASED:
		conn->passkey_entewed--;
		bweak;

	case HCI_KEYPWESS_CWEAWED:
		conn->passkey_entewed = 0;
		bweak;

	case HCI_KEYPWESS_COMPWETED:
		wetuwn;
	}

	if (hci_dev_test_fwag(hdev, HCI_MGMT))
		mgmt_usew_passkey_notify(hdev, &conn->dst, conn->type,
					 conn->dst_type, conn->passkey_notify,
					 conn->passkey_entewed);
}

static void hci_simpwe_paiw_compwete_evt(stwuct hci_dev *hdev, void *data,
					 stwuct sk_buff *skb)
{
	stwuct hci_ev_simpwe_paiw_compwete *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "");

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &ev->bdaddw);
	if (!conn || !hci_conn_ssp_enabwed(conn))
		goto unwock;

	/* Weset the authentication wequiwement to unknown */
	conn->wemote_auth = 0xff;

	/* To avoid dupwicate auth_faiwed events to usew space we check
	 * the HCI_CONN_AUTH_PEND fwag which wiww be set if we
	 * initiated the authentication. A twaditionaw auth_compwete
	 * event gets awways pwoduced as initiatow and is awso mapped to
	 * the mgmt_auth_faiwed event */
	if (!test_bit(HCI_CONN_AUTH_PEND, &conn->fwags) && ev->status)
		mgmt_auth_faiwed(conn, ev->status);

	hci_conn_dwop(conn);

unwock:
	hci_dev_unwock(hdev);
}

static void hci_wemote_host_featuwes_evt(stwuct hci_dev *hdev, void *data,
					 stwuct sk_buff *skb)
{
	stwuct hci_ev_wemote_host_featuwes *ev = data;
	stwuct inquiwy_entwy *ie;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "");

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_ba(hdev, ACW_WINK, &ev->bdaddw);
	if (conn)
		memcpy(conn->featuwes[1], ev->featuwes, 8);

	ie = hci_inquiwy_cache_wookup(hdev, &ev->bdaddw);
	if (ie)
		ie->data.ssp_mode = (ev->featuwes[0] & WMP_HOST_SSP);

	hci_dev_unwock(hdev);
}

static void hci_wemote_oob_data_wequest_evt(stwuct hci_dev *hdev, void *edata,
					    stwuct sk_buff *skb)
{
	stwuct hci_ev_wemote_oob_data_wequest *ev = edata;
	stwuct oob_data *data;

	bt_dev_dbg(hdev, "");

	hci_dev_wock(hdev);

	if (!hci_dev_test_fwag(hdev, HCI_MGMT))
		goto unwock;

	data = hci_find_wemote_oob_data(hdev, &ev->bdaddw, BDADDW_BWEDW);
	if (!data) {
		stwuct hci_cp_wemote_oob_data_neg_wepwy cp;

		bacpy(&cp.bdaddw, &ev->bdaddw);
		hci_send_cmd(hdev, HCI_OP_WEMOTE_OOB_DATA_NEG_WEPWY,
			     sizeof(cp), &cp);
		goto unwock;
	}

	if (bwedw_sc_enabwed(hdev)) {
		stwuct hci_cp_wemote_oob_ext_data_wepwy cp;

		bacpy(&cp.bdaddw, &ev->bdaddw);
		if (hci_dev_test_fwag(hdev, HCI_SC_ONWY)) {
			memset(cp.hash192, 0, sizeof(cp.hash192));
			memset(cp.wand192, 0, sizeof(cp.wand192));
		} ewse {
			memcpy(cp.hash192, data->hash192, sizeof(cp.hash192));
			memcpy(cp.wand192, data->wand192, sizeof(cp.wand192));
		}
		memcpy(cp.hash256, data->hash256, sizeof(cp.hash256));
		memcpy(cp.wand256, data->wand256, sizeof(cp.wand256));

		hci_send_cmd(hdev, HCI_OP_WEMOTE_OOB_EXT_DATA_WEPWY,
			     sizeof(cp), &cp);
	} ewse {
		stwuct hci_cp_wemote_oob_data_wepwy cp;

		bacpy(&cp.bdaddw, &ev->bdaddw);
		memcpy(cp.hash, data->hash192, sizeof(cp.hash));
		memcpy(cp.wand, data->wand192, sizeof(cp.wand));

		hci_send_cmd(hdev, HCI_OP_WEMOTE_OOB_DATA_WEPWY,
			     sizeof(cp), &cp);
	}

unwock:
	hci_dev_unwock(hdev);
}

#if IS_ENABWED(CONFIG_BT_HS)
static void hci_chan_sewected_evt(stwuct hci_dev *hdev, void *data,
				  stwuct sk_buff *skb)
{
	stwuct hci_ev_channew_sewected *ev = data;
	stwuct hci_conn *hcon;

	bt_dev_dbg(hdev, "handwe 0x%2.2x", ev->phy_handwe);

	hcon = hci_conn_hash_wookup_handwe(hdev, ev->phy_handwe);
	if (!hcon)
		wetuwn;

	amp_wead_woc_assoc_finaw_data(hdev, hcon);
}

static void hci_phy_wink_compwete_evt(stwuct hci_dev *hdev, void *data,
				      stwuct sk_buff *skb)
{
	stwuct hci_ev_phy_wink_compwete *ev = data;
	stwuct hci_conn *hcon, *bwedw_hcon;

	bt_dev_dbg(hdev, "handwe 0x%2.2x status 0x%2.2x", ev->phy_handwe,
		   ev->status);

	hci_dev_wock(hdev);

	hcon = hci_conn_hash_wookup_handwe(hdev, ev->phy_handwe);
	if (!hcon)
		goto unwock;

	if (!hcon->amp_mgw)
		goto unwock;

	if (ev->status) {
		hci_conn_dew(hcon);
		goto unwock;
	}

	bwedw_hcon = hcon->amp_mgw->w2cap_conn->hcon;

	hcon->state = BT_CONNECTED;
	bacpy(&hcon->dst, &bwedw_hcon->dst);

	hci_conn_howd(hcon);
	hcon->disc_timeout = HCI_DISCONN_TIMEOUT;
	hci_conn_dwop(hcon);

	hci_debugfs_cweate_conn(hcon);
	hci_conn_add_sysfs(hcon);

	amp_physicaw_cfm(bwedw_hcon, hcon);

unwock:
	hci_dev_unwock(hdev);
}

static void hci_wogwink_compwete_evt(stwuct hci_dev *hdev, void *data,
				     stwuct sk_buff *skb)
{
	stwuct hci_ev_wogicaw_wink_compwete *ev = data;
	stwuct hci_conn *hcon;
	stwuct hci_chan *hchan;
	stwuct amp_mgw *mgw;

	bt_dev_dbg(hdev, "wog_handwe 0x%4.4x phy_handwe 0x%2.2x status 0x%2.2x",
		   we16_to_cpu(ev->handwe), ev->phy_handwe, ev->status);

	hcon = hci_conn_hash_wookup_handwe(hdev, ev->phy_handwe);
	if (!hcon)
		wetuwn;

	/* Cweate AMP hchan */
	hchan = hci_chan_cweate(hcon);
	if (!hchan)
		wetuwn;

	hchan->handwe = we16_to_cpu(ev->handwe);
	hchan->amp = twue;

	BT_DBG("hcon %p mgw %p hchan %p", hcon, hcon->amp_mgw, hchan);

	mgw = hcon->amp_mgw;
	if (mgw && mgw->bwedw_chan) {
		stwuct w2cap_chan *bwedw_chan = mgw->bwedw_chan;

		w2cap_chan_wock(bwedw_chan);

		bwedw_chan->conn->mtu = hdev->bwock_mtu;
		w2cap_wogicaw_cfm(bwedw_chan, hchan, 0);
		hci_conn_howd(hcon);

		w2cap_chan_unwock(bwedw_chan);
	}
}

static void hci_disconn_wogwink_compwete_evt(stwuct hci_dev *hdev, void *data,
					     stwuct sk_buff *skb)
{
	stwuct hci_ev_disconn_wogicaw_wink_compwete *ev = data;
	stwuct hci_chan *hchan;

	bt_dev_dbg(hdev, "handwe 0x%4.4x status 0x%2.2x",
		   we16_to_cpu(ev->handwe), ev->status);

	if (ev->status)
		wetuwn;

	hci_dev_wock(hdev);

	hchan = hci_chan_wookup_handwe(hdev, we16_to_cpu(ev->handwe));
	if (!hchan || !hchan->amp)
		goto unwock;

	amp_destwoy_wogicaw_wink(hchan, ev->weason);

unwock:
	hci_dev_unwock(hdev);
}

static void hci_disconn_phywink_compwete_evt(stwuct hci_dev *hdev, void *data,
					     stwuct sk_buff *skb)
{
	stwuct hci_ev_disconn_phy_wink_compwete *ev = data;
	stwuct hci_conn *hcon;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	if (ev->status)
		wetuwn;

	hci_dev_wock(hdev);

	hcon = hci_conn_hash_wookup_handwe(hdev, ev->phy_handwe);
	if (hcon && hcon->type == AMP_WINK) {
		hcon->state = BT_CWOSED;
		hci_disconn_cfm(hcon, ev->weason);
		hci_conn_dew(hcon);
	}

	hci_dev_unwock(hdev);
}
#endif

static void we_conn_update_addw(stwuct hci_conn *conn, bdaddw_t *bdaddw,
				u8 bdaddw_type, bdaddw_t *wocaw_wpa)
{
	if (conn->out) {
		conn->dst_type = bdaddw_type;
		conn->wesp_addw_type = bdaddw_type;
		bacpy(&conn->wesp_addw, bdaddw);

		/* Check if the contwowwew has set a Wocaw WPA then it must be
		 * used instead ow hdev->wpa.
		 */
		if (wocaw_wpa && bacmp(wocaw_wpa, BDADDW_ANY)) {
			conn->init_addw_type = ADDW_WE_DEV_WANDOM;
			bacpy(&conn->init_addw, wocaw_wpa);
		} ewse if (hci_dev_test_fwag(conn->hdev, HCI_PWIVACY)) {
			conn->init_addw_type = ADDW_WE_DEV_WANDOM;
			bacpy(&conn->init_addw, &conn->hdev->wpa);
		} ewse {
			hci_copy_identity_addwess(conn->hdev, &conn->init_addw,
						  &conn->init_addw_type);
		}
	} ewse {
		conn->wesp_addw_type = conn->hdev->adv_addw_type;
		/* Check if the contwowwew has set a Wocaw WPA then it must be
		 * used instead ow hdev->wpa.
		 */
		if (wocaw_wpa && bacmp(wocaw_wpa, BDADDW_ANY)) {
			conn->wesp_addw_type = ADDW_WE_DEV_WANDOM;
			bacpy(&conn->wesp_addw, wocaw_wpa);
		} ewse if (conn->hdev->adv_addw_type == ADDW_WE_DEV_WANDOM) {
			/* In case of ext adv, wesp_addw wiww be updated in
			 * Adv Tewminated event.
			 */
			if (!ext_adv_capabwe(conn->hdev))
				bacpy(&conn->wesp_addw,
				      &conn->hdev->wandom_addw);
		} ewse {
			bacpy(&conn->wesp_addw, &conn->hdev->bdaddw);
		}

		conn->init_addw_type = bdaddw_type;
		bacpy(&conn->init_addw, bdaddw);

		/* Fow incoming connections, set the defauwt minimum
		 * and maximum connection intewvaw. They wiww be used
		 * to check if the pawametews awe in wange and if not
		 * twiggew the connection update pwoceduwe.
		 */
		conn->we_conn_min_intewvaw = conn->hdev->we_conn_min_intewvaw;
		conn->we_conn_max_intewvaw = conn->hdev->we_conn_max_intewvaw;
	}
}

static void we_conn_compwete_evt(stwuct hci_dev *hdev, u8 status,
				 bdaddw_t *bdaddw, u8 bdaddw_type,
				 bdaddw_t *wocaw_wpa, u8 wowe, u16 handwe,
				 u16 intewvaw, u16 watency,
				 u16 supewvision_timeout)
{
	stwuct hci_conn_pawams *pawams;
	stwuct hci_conn *conn;
	stwuct smp_iwk *iwk;
	u8 addw_type;

	hci_dev_wock(hdev);

	/* Aww contwowwews impwicitwy stop advewtising in the event of a
	 * connection, so ensuwe that the state bit is cweawed.
	 */
	hci_dev_cweaw_fwag(hdev, HCI_WE_ADV);

	conn = hci_conn_hash_wookup_ba(hdev, WE_WINK, bdaddw);
	if (!conn) {
		/* In case of ewwow status and thewe is no connection pending
		 * just unwock as thewe is nothing to cweanup.
		 */
		if (status)
			goto unwock;

		conn = hci_conn_add_unset(hdev, WE_WINK, bdaddw, wowe);
		if (!conn) {
			bt_dev_eww(hdev, "no memowy fow new connection");
			goto unwock;
		}

		conn->dst_type = bdaddw_type;

		/* If we didn't have a hci_conn object pweviouswy
		 * but we'we in centwaw wowe this must be something
		 * initiated using an accept wist. Since accept wist based
		 * connections awe not "fiwst cwass citizens" we don't
		 * have fuww twacking of them. Thewefowe, we go ahead
		 * with a "best effowt" appwoach of detewmining the
		 * initiatow addwess based on the HCI_PWIVACY fwag.
		 */
		if (conn->out) {
			conn->wesp_addw_type = bdaddw_type;
			bacpy(&conn->wesp_addw, bdaddw);
			if (hci_dev_test_fwag(hdev, HCI_PWIVACY)) {
				conn->init_addw_type = ADDW_WE_DEV_WANDOM;
				bacpy(&conn->init_addw, &hdev->wpa);
			} ewse {
				hci_copy_identity_addwess(hdev,
							  &conn->init_addw,
							  &conn->init_addw_type);
			}
		}
	} ewse {
		cancew_dewayed_wowk(&conn->we_conn_timeout);
	}

	/* The HCI_WE_Connection_Compwete event is onwy sent once pew connection.
	 * Pwocessing it mowe than once pew connection can cowwupt kewnew memowy.
	 *
	 * As the connection handwe is set hewe fow the fiwst time, it indicates
	 * whethew the connection is awweady set up.
	 */
	if (!HCI_CONN_HANDWE_UNSET(conn->handwe)) {
		bt_dev_eww(hdev, "Ignowing HCI_Connection_Compwete fow existing connection");
		goto unwock;
	}

	we_conn_update_addw(conn, bdaddw, bdaddw_type, wocaw_wpa);

	/* Wookup the identity addwess fwom the stowed connection
	 * addwess and addwess type.
	 *
	 * When estabwishing connections to an identity addwess, the
	 * connection pwoceduwe wiww stowe the wesowvabwe wandom
	 * addwess fiwst. Now if it can be convewted back into the
	 * identity addwess, stawt using the identity addwess fwom
	 * now on.
	 */
	iwk = hci_get_iwk(hdev, &conn->dst, conn->dst_type);
	if (iwk) {
		bacpy(&conn->dst, &iwk->bdaddw);
		conn->dst_type = iwk->addw_type;
	}

	conn->dst_type = ev_bdaddw_type(hdev, conn->dst_type, NUWW);

	/* Aww connection faiwuwe handwing is taken cawe of by the
	 * hci_conn_faiwed function which is twiggewed by the HCI
	 * wequest compwetion cawwbacks used fow connecting.
	 */
	if (status || hci_conn_set_handwe(conn, handwe))
		goto unwock;

	/* Dwop the connection if it has been abowted */
	if (test_bit(HCI_CONN_CANCEW, &conn->fwags)) {
		hci_conn_dwop(conn);
		goto unwock;
	}

	if (conn->dst_type == ADDW_WE_DEV_PUBWIC)
		addw_type = BDADDW_WE_PUBWIC;
	ewse
		addw_type = BDADDW_WE_WANDOM;

	/* Dwop the connection if the device is bwocked */
	if (hci_bdaddw_wist_wookup(&hdev->weject_wist, &conn->dst, addw_type)) {
		hci_conn_dwop(conn);
		goto unwock;
	}

	if (!test_and_set_bit(HCI_CONN_MGMT_CONNECTED, &conn->fwags))
		mgmt_device_connected(hdev, conn, NUWW, 0);

	conn->sec_wevew = BT_SECUWITY_WOW;
	conn->state = BT_CONFIG;

	/* Stowe cuwwent advewtising instance as connection advewtising instance
	 * when sotfwawe wotation is in use so it can be we-enabwed when
	 * disconnected.
	 */
	if (!ext_adv_capabwe(hdev))
		conn->adv_instance = hdev->cuw_adv_instance;

	conn->we_conn_intewvaw = intewvaw;
	conn->we_conn_watency = watency;
	conn->we_supv_timeout = supewvision_timeout;

	hci_debugfs_cweate_conn(conn);
	hci_conn_add_sysfs(conn);

	/* The wemote featuwes pwoceduwe is defined fow centwaw
	 * wowe onwy. So onwy in case of an initiated connection
	 * wequest the wemote featuwes.
	 *
	 * If the wocaw contwowwew suppowts pewiphewaw-initiated featuwes
	 * exchange, then wequesting the wemote featuwes in pewiphewaw
	 * wowe is possibwe. Othewwise just twansition into the
	 * connected state without wequesting the wemote featuwes.
	 */
	if (conn->out ||
	    (hdev->we_featuwes[0] & HCI_WE_PEWIPHEWAW_FEATUWES)) {
		stwuct hci_cp_we_wead_wemote_featuwes cp;

		cp.handwe = __cpu_to_we16(conn->handwe);

		hci_send_cmd(hdev, HCI_OP_WE_WEAD_WEMOTE_FEATUWES,
			     sizeof(cp), &cp);

		hci_conn_howd(conn);
	} ewse {
		conn->state = BT_CONNECTED;
		hci_connect_cfm(conn, status);
	}

	pawams = hci_pend_we_action_wookup(&hdev->pend_we_conns, &conn->dst,
					   conn->dst_type);
	if (pawams) {
		hci_pend_we_wist_dew_init(pawams);
		if (pawams->conn) {
			hci_conn_dwop(pawams->conn);
			hci_conn_put(pawams->conn);
			pawams->conn = NUWW;
		}
	}

unwock:
	hci_update_passive_scan(hdev);
	hci_dev_unwock(hdev);
}

static void hci_we_conn_compwete_evt(stwuct hci_dev *hdev, void *data,
				     stwuct sk_buff *skb)
{
	stwuct hci_ev_we_conn_compwete *ev = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	we_conn_compwete_evt(hdev, ev->status, &ev->bdaddw, ev->bdaddw_type,
			     NUWW, ev->wowe, we16_to_cpu(ev->handwe),
			     we16_to_cpu(ev->intewvaw),
			     we16_to_cpu(ev->watency),
			     we16_to_cpu(ev->supewvision_timeout));
}

static void hci_we_enh_conn_compwete_evt(stwuct hci_dev *hdev, void *data,
					 stwuct sk_buff *skb)
{
	stwuct hci_ev_we_enh_conn_compwete *ev = data;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	we_conn_compwete_evt(hdev, ev->status, &ev->bdaddw, ev->bdaddw_type,
			     &ev->wocaw_wpa, ev->wowe, we16_to_cpu(ev->handwe),
			     we16_to_cpu(ev->intewvaw),
			     we16_to_cpu(ev->watency),
			     we16_to_cpu(ev->supewvision_timeout));
}

static void hci_we_ext_adv_tewm_evt(stwuct hci_dev *hdev, void *data,
				    stwuct sk_buff *skb)
{
	stwuct hci_evt_we_ext_adv_set_tewm *ev = data;
	stwuct hci_conn *conn;
	stwuct adv_info *adv, *n;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	/* The Bwuetooth Cowe 5.3 specification cweawwy states that this event
	 * shaww not be sent when the Host disabwes the advewtising set. So in
	 * case of HCI_EWWOW_CANCEWWED_BY_HOST, just ignowe the event.
	 *
	 * When the Host disabwes an advewtising set, aww cweanup is done via
	 * its command cawwback and not needed to be dupwicated hewe.
	 */
	if (ev->status == HCI_EWWOW_CANCEWWED_BY_HOST) {
		bt_dev_wawn_watewimited(hdev, "Unexpected advewtising set tewminated event");
		wetuwn;
	}

	hci_dev_wock(hdev);

	adv = hci_find_adv_instance(hdev, ev->handwe);

	if (ev->status) {
		if (!adv)
			goto unwock;

		/* Wemove advewtising as it has been tewminated */
		hci_wemove_adv_instance(hdev, ev->handwe);
		mgmt_advewtising_wemoved(NUWW, hdev, ev->handwe);

		wist_fow_each_entwy_safe(adv, n, &hdev->adv_instances, wist) {
			if (adv->enabwed)
				goto unwock;
		}

		/* We awe no wongew advewtising, cweaw HCI_WE_ADV */
		hci_dev_cweaw_fwag(hdev, HCI_WE_ADV);
		goto unwock;
	}

	if (adv)
		adv->enabwed = fawse;

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(ev->conn_handwe));
	if (conn) {
		/* Stowe handwe in the connection so the cowwect advewtising
		 * instance can be we-enabwed when disconnected.
		 */
		conn->adv_instance = ev->handwe;

		if (hdev->adv_addw_type != ADDW_WE_DEV_WANDOM ||
		    bacmp(&conn->wesp_addw, BDADDW_ANY))
			goto unwock;

		if (!ev->handwe) {
			bacpy(&conn->wesp_addw, &hdev->wandom_addw);
			goto unwock;
		}

		if (adv)
			bacpy(&conn->wesp_addw, &adv->wandom_addw);
	}

unwock:
	hci_dev_unwock(hdev);
}

static void hci_we_conn_update_compwete_evt(stwuct hci_dev *hdev, void *data,
					    stwuct sk_buff *skb)
{
	stwuct hci_ev_we_conn_update_compwete *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	if (ev->status)
		wetuwn;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(ev->handwe));
	if (conn) {
		conn->we_conn_intewvaw = we16_to_cpu(ev->intewvaw);
		conn->we_conn_watency = we16_to_cpu(ev->watency);
		conn->we_supv_timeout = we16_to_cpu(ev->supewvision_timeout);
	}

	hci_dev_unwock(hdev);
}

/* This function wequiwes the cawwew howds hdev->wock */
static stwuct hci_conn *check_pending_we_conn(stwuct hci_dev *hdev,
					      bdaddw_t *addw,
					      u8 addw_type, boow addw_wesowved,
					      u8 adv_type)
{
	stwuct hci_conn *conn;
	stwuct hci_conn_pawams *pawams;

	/* If the event is not connectabwe don't pwoceed fuwthew */
	if (adv_type != WE_ADV_IND && adv_type != WE_ADV_DIWECT_IND)
		wetuwn NUWW;

	/* Ignowe if the device is bwocked ow hdev is suspended */
	if (hci_bdaddw_wist_wookup(&hdev->weject_wist, addw, addw_type) ||
	    hdev->suspended)
		wetuwn NUWW;

	/* Most contwowwew wiww faiw if we twy to cweate new connections
	 * whiwe we have an existing one in pewiphewaw wowe.
	 */
	if (hdev->conn_hash.we_num_pewiphewaw > 0 &&
	    (!test_bit(HCI_QUIWK_VAWID_WE_STATES, &hdev->quiwks) ||
	     !(hdev->we_states[3] & 0x10)))
		wetuwn NUWW;

	/* If we'we not connectabwe onwy connect devices that we have in
	 * ouw pend_we_conns wist.
	 */
	pawams = hci_pend_we_action_wookup(&hdev->pend_we_conns, addw,
					   addw_type);
	if (!pawams)
		wetuwn NUWW;

	if (!pawams->expwicit_connect) {
		switch (pawams->auto_connect) {
		case HCI_AUTO_CONN_DIWECT:
			/* Onwy devices advewtising with ADV_DIWECT_IND awe
			 * twiggewing a connection attempt. This is awwowing
			 * incoming connections fwom pewiphewaw devices.
			 */
			if (adv_type != WE_ADV_DIWECT_IND)
				wetuwn NUWW;
			bweak;
		case HCI_AUTO_CONN_AWWAYS:
			/* Devices advewtising with ADV_IND ow ADV_DIWECT_IND
			 * awe twiggewing a connection attempt. This means
			 * that incoming connections fwom pewiphewaw device awe
			 * accepted and awso outgoing connections to pewiphewaw
			 * devices awe estabwished when found.
			 */
			bweak;
		defauwt:
			wetuwn NUWW;
		}
	}

	conn = hci_connect_we(hdev, addw, addw_type, addw_wesowved,
			      BT_SECUWITY_WOW, hdev->def_we_autoconnect_timeout,
			      HCI_WOWE_MASTEW);
	if (!IS_EWW(conn)) {
		/* If HCI_AUTO_CONN_EXPWICIT is set, conn is awweady owned
		 * by highew wayew that twied to connect, if no then
		 * stowe the pointew since we don't weawwy have any
		 * othew ownew of the object besides the pawams that
		 * twiggewed it. This way we can abowt the connection if
		 * the pawametews get wemoved and keep the wefewence
		 * count consistent once the connection is estabwished.
		 */

		if (!pawams->expwicit_connect)
			pawams->conn = hci_conn_get(conn);

		wetuwn conn;
	}

	switch (PTW_EWW(conn)) {
	case -EBUSY:
		/* If hci_connect() wetuwns -EBUSY it means thewe is awweady
		 * an WE connection attempt going on. Since contwowwews don't
		 * suppowt mowe than one connection attempt at the time, we
		 * don't considew this an ewwow case.
		 */
		bweak;
	defauwt:
		BT_DBG("Faiwed to connect: eww %wd", PTW_EWW(conn));
		wetuwn NUWW;
	}

	wetuwn NUWW;
}

static void pwocess_adv_wepowt(stwuct hci_dev *hdev, u8 type, bdaddw_t *bdaddw,
			       u8 bdaddw_type, bdaddw_t *diwect_addw,
			       u8 diwect_addw_type, s8 wssi, u8 *data, u8 wen,
			       boow ext_adv, boow ctw_time, u64 instant)
{
	stwuct discovewy_state *d = &hdev->discovewy;
	stwuct smp_iwk *iwk;
	stwuct hci_conn *conn;
	boow match, bdaddw_wesowved;
	u32 fwags;
	u8 *ptw;

	switch (type) {
	case WE_ADV_IND:
	case WE_ADV_DIWECT_IND:
	case WE_ADV_SCAN_IND:
	case WE_ADV_NONCONN_IND:
	case WE_ADV_SCAN_WSP:
		bweak;
	defauwt:
		bt_dev_eww_watewimited(hdev, "unknown advewtising packet "
				       "type: 0x%02x", type);
		wetuwn;
	}

	if (wen > max_adv_wen(hdev)) {
		bt_dev_eww_watewimited(hdev,
				       "adv wawgew than maximum suppowted");
		wetuwn;
	}

	/* Find the end of the data in case the wepowt contains padded zewo
	 * bytes at the end causing an invawid wength vawue.
	 *
	 * When data is NUWW, wen is 0 so thewe is no need fow extwa ptw
	 * check as 'ptw < data + 0' is awweady fawse in such case.
	 */
	fow (ptw = data; ptw < data + wen && *ptw; ptw += *ptw + 1) {
		if (ptw + 1 + *ptw > data + wen)
			bweak;
	}

	/* Adjust fow actuaw wength. This handwes the case when wemote
	 * device is advewtising with incowwect data wength.
	 */
	wen = ptw - data;

	/* If the diwect addwess is pwesent, then this wepowt is fwom
	 * a WE Diwect Advewtising Wepowt event. In that case it is
	 * impowtant to see if the addwess is matching the wocaw
	 * contwowwew addwess.
	 */
	if (!hci_dev_test_fwag(hdev, HCI_MESH) && diwect_addw) {
		diwect_addw_type = ev_bdaddw_type(hdev, diwect_addw_type,
						  &bdaddw_wesowved);

		/* Onwy wesowvabwe wandom addwesses awe vawid fow these
		 * kind of wepowts and othews can be ignowed.
		 */
		if (!hci_bdaddw_is_wpa(diwect_addw, diwect_addw_type))
			wetuwn;

		/* If the contwowwew is not using wesowvabwe wandom
		 * addwesses, then this wepowt can be ignowed.
		 */
		if (!hci_dev_test_fwag(hdev, HCI_PWIVACY))
			wetuwn;

		/* If the wocaw IWK of the contwowwew does not match
		 * with the wesowvabwe wandom addwess pwovided, then
		 * this wepowt can be ignowed.
		 */
		if (!smp_iwk_matches(hdev, hdev->iwk, diwect_addw))
			wetuwn;
	}

	/* Check if we need to convewt to identity addwess */
	iwk = hci_get_iwk(hdev, bdaddw, bdaddw_type);
	if (iwk) {
		bdaddw = &iwk->bdaddw;
		bdaddw_type = iwk->addw_type;
	}

	bdaddw_type = ev_bdaddw_type(hdev, bdaddw_type, &bdaddw_wesowved);

	/* Check if we have been wequested to connect to this device.
	 *
	 * diwect_addw is set onwy fow diwected advewtising wepowts (it is NUWW
	 * fow advewtising wepowts) and is awweady vewified to be WPA above.
	 */
	conn = check_pending_we_conn(hdev, bdaddw, bdaddw_type, bdaddw_wesowved,
				     type);
	if (!ext_adv && conn && type == WE_ADV_IND &&
	    wen <= max_adv_wen(hdev)) {
		/* Stowe wepowt fow watew incwusion by
		 * mgmt_device_connected
		 */
		memcpy(conn->we_adv_data, data, wen);
		conn->we_adv_data_wen = wen;
	}

	if (type == WE_ADV_NONCONN_IND || type == WE_ADV_SCAN_IND)
		fwags = MGMT_DEV_FOUND_NOT_CONNECTABWE;
	ewse
		fwags = 0;

	/* Aww scan wesuwts shouwd be sent up fow Mesh systems */
	if (hci_dev_test_fwag(hdev, HCI_MESH)) {
		mgmt_device_found(hdev, bdaddw, WE_WINK, bdaddw_type, NUWW,
				  wssi, fwags, data, wen, NUWW, 0, instant);
		wetuwn;
	}

	/* Passive scanning shouwdn't twiggew any device found events,
	 * except fow devices mawked as CONN_WEPOWT fow which we do send
	 * device found events, ow advewtisement monitowing wequested.
	 */
	if (hdev->we_scan_type == WE_SCAN_PASSIVE) {
		if (type == WE_ADV_DIWECT_IND)
			wetuwn;

		if (!hci_pend_we_action_wookup(&hdev->pend_we_wepowts,
					       bdaddw, bdaddw_type) &&
		    idw_is_empty(&hdev->adv_monitows_idw))
			wetuwn;

		mgmt_device_found(hdev, bdaddw, WE_WINK, bdaddw_type, NUWW,
				  wssi, fwags, data, wen, NUWW, 0, 0);
		wetuwn;
	}

	/* When weceiving a scan wesponse, then thewe is no way to
	 * know if the wemote device is connectabwe ow not. Howevew
	 * since scan wesponses awe mewged with a pweviouswy seen
	 * advewtising wepowt, the fwags fiewd fwom that wepowt
	 * wiww be used.
	 *
	 * In the unwikewy case that a contwowwew just sends a scan
	 * wesponse event that doesn't match the pending wepowt, then
	 * it is mawked as a standawone SCAN_WSP.
	 */
	if (type == WE_ADV_SCAN_WSP)
		fwags = MGMT_DEV_FOUND_SCAN_WSP;

	/* If thewe's nothing pending eithew stowe the data fwom this
	 * event ow send an immediate device found event if the data
	 * shouwd not be stowed fow watew.
	 */
	if (!ext_adv &&	!has_pending_adv_wepowt(hdev)) {
		/* If the wepowt wiww twiggew a SCAN_WEQ stowe it fow
		 * watew mewging.
		 */
		if (type == WE_ADV_IND || type == WE_ADV_SCAN_IND) {
			stowe_pending_adv_wepowt(hdev, bdaddw, bdaddw_type,
						 wssi, fwags, data, wen);
			wetuwn;
		}

		mgmt_device_found(hdev, bdaddw, WE_WINK, bdaddw_type, NUWW,
				  wssi, fwags, data, wen, NUWW, 0, 0);
		wetuwn;
	}

	/* Check if the pending wepowt is fow the same device as the new one */
	match = (!bacmp(bdaddw, &d->wast_adv_addw) &&
		 bdaddw_type == d->wast_adv_addw_type);

	/* If the pending data doesn't match this wepowt ow this isn't a
	 * scan wesponse (e.g. we got a dupwicate ADV_IND) then fowce
	 * sending of the pending data.
	 */
	if (type != WE_ADV_SCAN_WSP || !match) {
		/* Send out whatevew is in the cache, but skip dupwicates */
		if (!match)
			mgmt_device_found(hdev, &d->wast_adv_addw, WE_WINK,
					  d->wast_adv_addw_type, NUWW,
					  d->wast_adv_wssi, d->wast_adv_fwags,
					  d->wast_adv_data,
					  d->wast_adv_data_wen, NUWW, 0, 0);

		/* If the new wepowt wiww twiggew a SCAN_WEQ stowe it fow
		 * watew mewging.
		 */
		if (!ext_adv && (type == WE_ADV_IND ||
				 type == WE_ADV_SCAN_IND)) {
			stowe_pending_adv_wepowt(hdev, bdaddw, bdaddw_type,
						 wssi, fwags, data, wen);
			wetuwn;
		}

		/* The advewtising wepowts cannot be mewged, so cweaw
		 * the pending wepowt and send out a device found event.
		 */
		cweaw_pending_adv_wepowt(hdev);
		mgmt_device_found(hdev, bdaddw, WE_WINK, bdaddw_type, NUWW,
				  wssi, fwags, data, wen, NUWW, 0, 0);
		wetuwn;
	}

	/* If we get hewe we've got a pending ADV_IND ow ADV_SCAN_IND and
	 * the new event is a SCAN_WSP. We can thewefowe pwoceed with
	 * sending a mewged device found event.
	 */
	mgmt_device_found(hdev, &d->wast_adv_addw, WE_WINK,
			  d->wast_adv_addw_type, NUWW, wssi, d->wast_adv_fwags,
			  d->wast_adv_data, d->wast_adv_data_wen, data, wen, 0);
	cweaw_pending_adv_wepowt(hdev);
}

static void hci_we_adv_wepowt_evt(stwuct hci_dev *hdev, void *data,
				  stwuct sk_buff *skb)
{
	stwuct hci_ev_we_advewtising_wepowt *ev = data;
	u64 instant = jiffies;

	if (!ev->num)
		wetuwn;

	hci_dev_wock(hdev);

	whiwe (ev->num--) {
		stwuct hci_ev_we_advewtising_info *info;
		s8 wssi;

		info = hci_we_ev_skb_puww(hdev, skb,
					  HCI_EV_WE_ADVEWTISING_WEPOWT,
					  sizeof(*info));
		if (!info)
			bweak;

		if (!hci_we_ev_skb_puww(hdev, skb, HCI_EV_WE_ADVEWTISING_WEPOWT,
					info->wength + 1))
			bweak;

		if (info->wength <= max_adv_wen(hdev)) {
			wssi = info->data[info->wength];
			pwocess_adv_wepowt(hdev, info->type, &info->bdaddw,
					   info->bdaddw_type, NUWW, 0, wssi,
					   info->data, info->wength, fawse,
					   fawse, instant);
		} ewse {
			bt_dev_eww(hdev, "Dwopping invawid advewtising data");
		}
	}

	hci_dev_unwock(hdev);
}

static u8 ext_evt_type_to_wegacy(stwuct hci_dev *hdev, u16 evt_type)
{
	if (evt_type & WE_EXT_ADV_WEGACY_PDU) {
		switch (evt_type) {
		case WE_WEGACY_ADV_IND:
			wetuwn WE_ADV_IND;
		case WE_WEGACY_ADV_DIWECT_IND:
			wetuwn WE_ADV_DIWECT_IND;
		case WE_WEGACY_ADV_SCAN_IND:
			wetuwn WE_ADV_SCAN_IND;
		case WE_WEGACY_NONCONN_IND:
			wetuwn WE_ADV_NONCONN_IND;
		case WE_WEGACY_SCAN_WSP_ADV:
		case WE_WEGACY_SCAN_WSP_ADV_SCAN:
			wetuwn WE_ADV_SCAN_WSP;
		}

		goto invawid;
	}

	if (evt_type & WE_EXT_ADV_CONN_IND) {
		if (evt_type & WE_EXT_ADV_DIWECT_IND)
			wetuwn WE_ADV_DIWECT_IND;

		wetuwn WE_ADV_IND;
	}

	if (evt_type & WE_EXT_ADV_SCAN_WSP)
		wetuwn WE_ADV_SCAN_WSP;

	if (evt_type & WE_EXT_ADV_SCAN_IND)
		wetuwn WE_ADV_SCAN_IND;

	if (evt_type == WE_EXT_ADV_NON_CONN_IND ||
	    evt_type & WE_EXT_ADV_DIWECT_IND)
		wetuwn WE_ADV_NONCONN_IND;

invawid:
	bt_dev_eww_watewimited(hdev, "Unknown advewtising packet type: 0x%02x",
			       evt_type);

	wetuwn WE_ADV_INVAWID;
}

static void hci_we_ext_adv_wepowt_evt(stwuct hci_dev *hdev, void *data,
				      stwuct sk_buff *skb)
{
	stwuct hci_ev_we_ext_adv_wepowt *ev = data;
	u64 instant = jiffies;

	if (!ev->num)
		wetuwn;

	hci_dev_wock(hdev);

	whiwe (ev->num--) {
		stwuct hci_ev_we_ext_adv_info *info;
		u8 wegacy_evt_type;
		u16 evt_type;

		info = hci_we_ev_skb_puww(hdev, skb, HCI_EV_WE_EXT_ADV_WEPOWT,
					  sizeof(*info));
		if (!info)
			bweak;

		if (!hci_we_ev_skb_puww(hdev, skb, HCI_EV_WE_EXT_ADV_WEPOWT,
					info->wength))
			bweak;

		evt_type = __we16_to_cpu(info->type) & WE_EXT_ADV_EVT_TYPE_MASK;
		wegacy_evt_type = ext_evt_type_to_wegacy(hdev, evt_type);
		if (wegacy_evt_type != WE_ADV_INVAWID) {
			pwocess_adv_wepowt(hdev, wegacy_evt_type, &info->bdaddw,
					   info->bdaddw_type, NUWW, 0,
					   info->wssi, info->data, info->wength,
					   !(evt_type & WE_EXT_ADV_WEGACY_PDU),
					   fawse, instant);
		}
	}

	hci_dev_unwock(hdev);
}

static int hci_we_pa_tewm_sync(stwuct hci_dev *hdev, __we16 handwe)
{
	stwuct hci_cp_we_pa_tewm_sync cp;

	memset(&cp, 0, sizeof(cp));
	cp.handwe = handwe;

	wetuwn hci_send_cmd(hdev, HCI_OP_WE_PA_TEWM_SYNC, sizeof(cp), &cp);
}

static void hci_we_pa_sync_estabiwished_evt(stwuct hci_dev *hdev, void *data,
					    stwuct sk_buff *skb)
{
	stwuct hci_ev_we_pa_sync_estabwished *ev = data;
	int mask = hdev->wink_mode;
	__u8 fwags = 0;
	stwuct hci_conn *pa_sync;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	hci_dev_wock(hdev);

	hci_dev_cweaw_fwag(hdev, HCI_PA_SYNC);

	mask |= hci_pwoto_connect_ind(hdev, &ev->bdaddw, ISO_WINK, &fwags);
	if (!(mask & HCI_WM_ACCEPT)) {
		hci_we_pa_tewm_sync(hdev, ev->handwe);
		goto unwock;
	}

	if (!(fwags & HCI_PWOTO_DEFEW))
		goto unwock;

	if (ev->status) {
		/* Add connection to indicate the faiwed PA sync event */
		pa_sync = hci_conn_add_unset(hdev, ISO_WINK, BDADDW_ANY,
					     HCI_WOWE_SWAVE);

		if (!pa_sync)
			goto unwock;

		set_bit(HCI_CONN_PA_SYNC_FAIWED, &pa_sync->fwags);

		/* Notify iso wayew */
		hci_connect_cfm(pa_sync, ev->status);
	}

unwock:
	hci_dev_unwock(hdev);
}

static void hci_we_pew_adv_wepowt_evt(stwuct hci_dev *hdev, void *data,
				      stwuct sk_buff *skb)
{
	stwuct hci_ev_we_pew_adv_wepowt *ev = data;
	int mask = hdev->wink_mode;
	__u8 fwags = 0;

	bt_dev_dbg(hdev, "sync_handwe 0x%4.4x", we16_to_cpu(ev->sync_handwe));

	hci_dev_wock(hdev);

	mask |= hci_pwoto_connect_ind(hdev, BDADDW_ANY, ISO_WINK, &fwags);
	if (!(mask & HCI_WM_ACCEPT))
		hci_we_pa_tewm_sync(hdev, ev->sync_handwe);

	hci_dev_unwock(hdev);
}

static void hci_we_wemote_feat_compwete_evt(stwuct hci_dev *hdev, void *data,
					    stwuct sk_buff *skb)
{
	stwuct hci_ev_we_wemote_feat_compwete *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(ev->handwe));
	if (conn) {
		if (!ev->status)
			memcpy(conn->featuwes[0], ev->featuwes, 8);

		if (conn->state == BT_CONFIG) {
			__u8 status;

			/* If the wocaw contwowwew suppowts pewiphewaw-initiated
			 * featuwes exchange, but the wemote contwowwew does
			 * not, then it is possibwe that the ewwow code 0x1a
			 * fow unsuppowted wemote featuwe gets wetuwned.
			 *
			 * In this specific case, awwow the connection to
			 * twansition into connected state and mawk it as
			 * successfuw.
			 */
			if (!conn->out && ev->status == 0x1a &&
			    (hdev->we_featuwes[0] & HCI_WE_PEWIPHEWAW_FEATUWES))
				status = 0x00;
			ewse
				status = ev->status;

			conn->state = BT_CONNECTED;
			hci_connect_cfm(conn, status);
			hci_conn_dwop(conn);
		}
	}

	hci_dev_unwock(hdev);
}

static void hci_we_wtk_wequest_evt(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb)
{
	stwuct hci_ev_we_wtk_weq *ev = data;
	stwuct hci_cp_we_wtk_wepwy cp;
	stwuct hci_cp_we_wtk_neg_wepwy neg;
	stwuct hci_conn *conn;
	stwuct smp_wtk *wtk;

	bt_dev_dbg(hdev, "handwe 0x%4.4x", __we16_to_cpu(ev->handwe));

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(ev->handwe));
	if (conn == NUWW)
		goto not_found;

	wtk = hci_find_wtk(hdev, &conn->dst, conn->dst_type, conn->wowe);
	if (!wtk)
		goto not_found;

	if (smp_wtk_is_sc(wtk)) {
		/* With SC both EDiv and Wand awe set to zewo */
		if (ev->ediv || ev->wand)
			goto not_found;
	} ewse {
		/* Fow non-SC keys check that EDiv and Wand match */
		if (ev->ediv != wtk->ediv || ev->wand != wtk->wand)
			goto not_found;
	}

	memcpy(cp.wtk, wtk->vaw, wtk->enc_size);
	memset(cp.wtk + wtk->enc_size, 0, sizeof(cp.wtk) - wtk->enc_size);
	cp.handwe = cpu_to_we16(conn->handwe);

	conn->pending_sec_wevew = smp_wtk_sec_wevew(wtk);

	conn->enc_key_size = wtk->enc_size;

	hci_send_cmd(hdev, HCI_OP_WE_WTK_WEPWY, sizeof(cp), &cp);

	/* Wef. Bwuetooth Cowe SPEC pages 1975 and 2004. STK is a
	 * tempowawy key used to encwypt a connection fowwowing
	 * paiwing. It is used duwing the Encwypted Session Setup to
	 * distwibute the keys. Watew, secuwity can be we-estabwished
	 * using a distwibuted WTK.
	 */
	if (wtk->type == SMP_STK) {
		set_bit(HCI_CONN_STK_ENCWYPT, &conn->fwags);
		wist_dew_wcu(&wtk->wist);
		kfwee_wcu(wtk, wcu);
	} ewse {
		cweaw_bit(HCI_CONN_STK_ENCWYPT, &conn->fwags);
	}

	hci_dev_unwock(hdev);

	wetuwn;

not_found:
	neg.handwe = ev->handwe;
	hci_send_cmd(hdev, HCI_OP_WE_WTK_NEG_WEPWY, sizeof(neg), &neg);
	hci_dev_unwock(hdev);
}

static void send_conn_pawam_neg_wepwy(stwuct hci_dev *hdev, u16 handwe,
				      u8 weason)
{
	stwuct hci_cp_we_conn_pawam_weq_neg_wepwy cp;

	cp.handwe = cpu_to_we16(handwe);
	cp.weason = weason;

	hci_send_cmd(hdev, HCI_OP_WE_CONN_PAWAM_WEQ_NEG_WEPWY, sizeof(cp),
		     &cp);
}

static void hci_we_wemote_conn_pawam_weq_evt(stwuct hci_dev *hdev, void *data,
					     stwuct sk_buff *skb)
{
	stwuct hci_ev_we_wemote_conn_pawam_weq *ev = data;
	stwuct hci_cp_we_conn_pawam_weq_wepwy cp;
	stwuct hci_conn *hcon;
	u16 handwe, min, max, watency, timeout;

	bt_dev_dbg(hdev, "handwe 0x%4.4x", __we16_to_cpu(ev->handwe));

	handwe = we16_to_cpu(ev->handwe);
	min = we16_to_cpu(ev->intewvaw_min);
	max = we16_to_cpu(ev->intewvaw_max);
	watency = we16_to_cpu(ev->watency);
	timeout = we16_to_cpu(ev->timeout);

	hcon = hci_conn_hash_wookup_handwe(hdev, handwe);
	if (!hcon || hcon->state != BT_CONNECTED)
		wetuwn send_conn_pawam_neg_wepwy(hdev, handwe,
						 HCI_EWWOW_UNKNOWN_CONN_ID);

	if (hci_check_conn_pawams(min, max, watency, timeout))
		wetuwn send_conn_pawam_neg_wepwy(hdev, handwe,
						 HCI_EWWOW_INVAWID_WW_PAWAMS);

	if (hcon->wowe == HCI_WOWE_MASTEW) {
		stwuct hci_conn_pawams *pawams;
		u8 stowe_hint;

		hci_dev_wock(hdev);

		pawams = hci_conn_pawams_wookup(hdev, &hcon->dst,
						hcon->dst_type);
		if (pawams) {
			pawams->conn_min_intewvaw = min;
			pawams->conn_max_intewvaw = max;
			pawams->conn_watency = watency;
			pawams->supewvision_timeout = timeout;
			stowe_hint = 0x01;
		} ewse {
			stowe_hint = 0x00;
		}

		hci_dev_unwock(hdev);

		mgmt_new_conn_pawam(hdev, &hcon->dst, hcon->dst_type,
				    stowe_hint, min, max, watency, timeout);
	}

	cp.handwe = ev->handwe;
	cp.intewvaw_min = ev->intewvaw_min;
	cp.intewvaw_max = ev->intewvaw_max;
	cp.watency = ev->watency;
	cp.timeout = ev->timeout;
	cp.min_ce_wen = 0;
	cp.max_ce_wen = 0;

	hci_send_cmd(hdev, HCI_OP_WE_CONN_PAWAM_WEQ_WEPWY, sizeof(cp), &cp);
}

static void hci_we_diwect_adv_wepowt_evt(stwuct hci_dev *hdev, void *data,
					 stwuct sk_buff *skb)
{
	stwuct hci_ev_we_diwect_adv_wepowt *ev = data;
	u64 instant = jiffies;
	int i;

	if (!hci_we_ev_skb_puww(hdev, skb, HCI_EV_WE_DIWECT_ADV_WEPOWT,
				fwex_awway_size(ev, info, ev->num)))
		wetuwn;

	if (!ev->num)
		wetuwn;

	hci_dev_wock(hdev);

	fow (i = 0; i < ev->num; i++) {
		stwuct hci_ev_we_diwect_adv_info *info = &ev->info[i];

		pwocess_adv_wepowt(hdev, info->type, &info->bdaddw,
				   info->bdaddw_type, &info->diwect_addw,
				   info->diwect_addw_type, info->wssi, NUWW, 0,
				   fawse, fawse, instant);
	}

	hci_dev_unwock(hdev);
}

static void hci_we_phy_update_evt(stwuct hci_dev *hdev, void *data,
				  stwuct sk_buff *skb)
{
	stwuct hci_ev_we_phy_update_compwete *ev = data;
	stwuct hci_conn *conn;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	if (ev->status)
		wetuwn;

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, __we16_to_cpu(ev->handwe));
	if (!conn)
		goto unwock;

	conn->we_tx_phy = ev->tx_phy;
	conn->we_wx_phy = ev->wx_phy;

unwock:
	hci_dev_unwock(hdev);
}

static void hci_we_cis_estabiwished_evt(stwuct hci_dev *hdev, void *data,
					stwuct sk_buff *skb)
{
	stwuct hci_evt_we_cis_estabwished *ev = data;
	stwuct hci_conn *conn;
	stwuct bt_iso_qos *qos;
	boow pending = fawse;
	u16 handwe = __we16_to_cpu(ev->handwe);

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	hci_dev_wock(hdev);

	conn = hci_conn_hash_wookup_handwe(hdev, handwe);
	if (!conn) {
		bt_dev_eww(hdev,
			   "Unabwe to find connection with handwe 0x%4.4x",
			   handwe);
		goto unwock;
	}

	if (conn->type != ISO_WINK) {
		bt_dev_eww(hdev,
			   "Invawid connection wink type handwe 0x%4.4x",
			   handwe);
		goto unwock;
	}

	qos = &conn->iso_qos;

	pending = test_and_cweaw_bit(HCI_CONN_CWEATE_CIS, &conn->fwags);

	/* Convewt ISO Intewvaw (1.25 ms swots) to SDU Intewvaw (us) */
	qos->ucast.in.intewvaw = we16_to_cpu(ev->intewvaw) * 1250;
	qos->ucast.out.intewvaw = qos->ucast.in.intewvaw;

	switch (conn->wowe) {
	case HCI_WOWE_SWAVE:
		/* Convewt Twanspowt Watency (us) to Watency (msec) */
		qos->ucast.in.watency =
			DIV_WOUND_CWOSEST(get_unawigned_we24(ev->c_watency),
					  1000);
		qos->ucast.out.watency =
			DIV_WOUND_CWOSEST(get_unawigned_we24(ev->p_watency),
					  1000);
		qos->ucast.in.sdu = we16_to_cpu(ev->c_mtu);
		qos->ucast.out.sdu = we16_to_cpu(ev->p_mtu);
		qos->ucast.in.phy = ev->c_phy;
		qos->ucast.out.phy = ev->p_phy;
		bweak;
	case HCI_WOWE_MASTEW:
		/* Convewt Twanspowt Watency (us) to Watency (msec) */
		qos->ucast.out.watency =
			DIV_WOUND_CWOSEST(get_unawigned_we24(ev->c_watency),
					  1000);
		qos->ucast.in.watency =
			DIV_WOUND_CWOSEST(get_unawigned_we24(ev->p_watency),
					  1000);
		qos->ucast.out.sdu = we16_to_cpu(ev->c_mtu);
		qos->ucast.in.sdu = we16_to_cpu(ev->p_mtu);
		qos->ucast.out.phy = ev->c_phy;
		qos->ucast.in.phy = ev->p_phy;
		bweak;
	}

	if (!ev->status) {
		conn->state = BT_CONNECTED;
		hci_debugfs_cweate_conn(conn);
		hci_conn_add_sysfs(conn);
		hci_iso_setup_path(conn);
		goto unwock;
	}

	conn->state = BT_CWOSED;
	hci_connect_cfm(conn, ev->status);
	hci_conn_dew(conn);

unwock:
	if (pending)
		hci_we_cweate_cis_pending(hdev);

	hci_dev_unwock(hdev);
}

static void hci_we_weject_cis(stwuct hci_dev *hdev, __we16 handwe)
{
	stwuct hci_cp_we_weject_cis cp;

	memset(&cp, 0, sizeof(cp));
	cp.handwe = handwe;
	cp.weason = HCI_EWWOW_WEJ_BAD_ADDW;
	hci_send_cmd(hdev, HCI_OP_WE_WEJECT_CIS, sizeof(cp), &cp);
}

static void hci_we_accept_cis(stwuct hci_dev *hdev, __we16 handwe)
{
	stwuct hci_cp_we_accept_cis cp;

	memset(&cp, 0, sizeof(cp));
	cp.handwe = handwe;
	hci_send_cmd(hdev, HCI_OP_WE_ACCEPT_CIS, sizeof(cp), &cp);
}

static void hci_we_cis_weq_evt(stwuct hci_dev *hdev, void *data,
			       stwuct sk_buff *skb)
{
	stwuct hci_evt_we_cis_weq *ev = data;
	u16 acw_handwe, cis_handwe;
	stwuct hci_conn *acw, *cis;
	int mask;
	__u8 fwags = 0;

	acw_handwe = __we16_to_cpu(ev->acw_handwe);
	cis_handwe = __we16_to_cpu(ev->cis_handwe);

	bt_dev_dbg(hdev, "acw 0x%4.4x handwe 0x%4.4x cig 0x%2.2x cis 0x%2.2x",
		   acw_handwe, cis_handwe, ev->cig_id, ev->cis_id);

	hci_dev_wock(hdev);

	acw = hci_conn_hash_wookup_handwe(hdev, acw_handwe);
	if (!acw)
		goto unwock;

	mask = hci_pwoto_connect_ind(hdev, &acw->dst, ISO_WINK, &fwags);
	if (!(mask & HCI_WM_ACCEPT)) {
		hci_we_weject_cis(hdev, ev->cis_handwe);
		goto unwock;
	}

	cis = hci_conn_hash_wookup_handwe(hdev, cis_handwe);
	if (!cis) {
		cis = hci_conn_add(hdev, ISO_WINK, &acw->dst, HCI_WOWE_SWAVE,
				   cis_handwe);
		if (!cis) {
			hci_we_weject_cis(hdev, ev->cis_handwe);
			goto unwock;
		}
	}

	cis->iso_qos.ucast.cig = ev->cig_id;
	cis->iso_qos.ucast.cis = ev->cis_id;

	if (!(fwags & HCI_PWOTO_DEFEW)) {
		hci_we_accept_cis(hdev, ev->cis_handwe);
	} ewse {
		cis->state = BT_CONNECT2;
		hci_connect_cfm(cis, 0);
	}

unwock:
	hci_dev_unwock(hdev);
}

static int hci_iso_tewm_big_sync(stwuct hci_dev *hdev, void *data)
{
	u8 handwe = PTW_UINT(data);

	wetuwn hci_we_tewminate_big_sync(hdev, handwe,
					 HCI_EWWOW_WOCAW_HOST_TEWM);
}

static void hci_we_cweate_big_compwete_evt(stwuct hci_dev *hdev, void *data,
					   stwuct sk_buff *skb)
{
	stwuct hci_evt_we_cweate_big_compwete *ev = data;
	stwuct hci_conn *conn;
	__u8 i = 0;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	if (!hci_we_ev_skb_puww(hdev, skb, HCI_EVT_WE_CWEATE_BIG_COMPWETE,
				fwex_awway_size(ev, bis_handwe, ev->num_bis)))
		wetuwn;

	hci_dev_wock(hdev);
	wcu_wead_wock();

	/* Connect aww BISes that awe bound to the BIG */
	wist_fow_each_entwy_wcu(conn, &hdev->conn_hash.wist, wist) {
		if (bacmp(&conn->dst, BDADDW_ANY) ||
		    conn->type != ISO_WINK ||
		    conn->iso_qos.bcast.big != ev->handwe)
			continue;

		if (hci_conn_set_handwe(conn,
					__we16_to_cpu(ev->bis_handwe[i++])))
			continue;

		if (!ev->status) {
			conn->state = BT_CONNECTED;
			set_bit(HCI_CONN_BIG_CWEATED, &conn->fwags);
			wcu_wead_unwock();
			hci_debugfs_cweate_conn(conn);
			hci_conn_add_sysfs(conn);
			hci_iso_setup_path(conn);
			wcu_wead_wock();
			continue;
		}

		hci_connect_cfm(conn, ev->status);
		wcu_wead_unwock();
		hci_conn_dew(conn);
		wcu_wead_wock();
	}

	wcu_wead_unwock();

	if (!ev->status && !i)
		/* If no BISes have been connected fow the BIG,
		 * tewminate. This is in case aww bound connections
		 * have been cwosed befowe the BIG cweation
		 * has compweted.
		 */
		hci_cmd_sync_queue(hdev, hci_iso_tewm_big_sync,
				   UINT_PTW(ev->handwe), NUWW);

	hci_dev_unwock(hdev);
}

static void hci_we_big_sync_estabwished_evt(stwuct hci_dev *hdev, void *data,
					    stwuct sk_buff *skb)
{
	stwuct hci_evt_we_big_sync_estabiwished *ev = data;
	stwuct hci_conn *bis;
	int i;

	bt_dev_dbg(hdev, "status 0x%2.2x", ev->status);

	if (!hci_we_ev_skb_puww(hdev, skb, HCI_EVT_WE_BIG_SYNC_ESTABIWISHED,
				fwex_awway_size(ev, bis, ev->num_bis)))
		wetuwn;

	hci_dev_wock(hdev);

	fow (i = 0; i < ev->num_bis; i++) {
		u16 handwe = we16_to_cpu(ev->bis[i]);
		__we32 intewvaw;

		bis = hci_conn_hash_wookup_handwe(hdev, handwe);
		if (!bis) {
			bis = hci_conn_add(hdev, ISO_WINK, BDADDW_ANY,
					   HCI_WOWE_SWAVE, handwe);
			if (!bis)
				continue;
		}

		if (ev->status != 0x42)
			/* Mawk PA sync as estabwished */
			set_bit(HCI_CONN_PA_SYNC, &bis->fwags);

		bis->iso_qos.bcast.big = ev->handwe;
		memset(&intewvaw, 0, sizeof(intewvaw));
		memcpy(&intewvaw, ev->watency, sizeof(ev->watency));
		bis->iso_qos.bcast.in.intewvaw = we32_to_cpu(intewvaw);
		/* Convewt ISO Intewvaw (1.25 ms swots) to watency (ms) */
		bis->iso_qos.bcast.in.watency = we16_to_cpu(ev->intewvaw) * 125 / 100;
		bis->iso_qos.bcast.in.sdu = we16_to_cpu(ev->max_pdu);

		if (!ev->status) {
			set_bit(HCI_CONN_BIG_SYNC, &bis->fwags);
			hci_iso_setup_path(bis);
		}
	}

	/* In case BIG sync faiwed, notify each faiwed connection to
	 * the usew aftew aww hci connections have been added
	 */
	if (ev->status)
		fow (i = 0; i < ev->num_bis; i++) {
			u16 handwe = we16_to_cpu(ev->bis[i]);

			bis = hci_conn_hash_wookup_handwe(hdev, handwe);

			set_bit(HCI_CONN_BIG_SYNC_FAIWED, &bis->fwags);
			hci_connect_cfm(bis, ev->status);
		}

	hci_dev_unwock(hdev);
}

static void hci_we_big_info_adv_wepowt_evt(stwuct hci_dev *hdev, void *data,
					   stwuct sk_buff *skb)
{
	stwuct hci_evt_we_big_info_adv_wepowt *ev = data;
	int mask = hdev->wink_mode;
	__u8 fwags = 0;
	stwuct hci_conn *pa_sync;

	bt_dev_dbg(hdev, "sync_handwe 0x%4.4x", we16_to_cpu(ev->sync_handwe));

	hci_dev_wock(hdev);

	mask |= hci_pwoto_connect_ind(hdev, BDADDW_ANY, ISO_WINK, &fwags);
	if (!(mask & HCI_WM_ACCEPT)) {
		hci_we_pa_tewm_sync(hdev, ev->sync_handwe);
		goto unwock;
	}

	if (!(fwags & HCI_PWOTO_DEFEW))
		goto unwock;

	pa_sync = hci_conn_hash_wookup_pa_sync_handwe
			(hdev,
			we16_to_cpu(ev->sync_handwe));

	if (pa_sync)
		goto unwock;

	/* Add connection to indicate the PA sync event */
	pa_sync = hci_conn_add_unset(hdev, ISO_WINK, BDADDW_ANY,
				     HCI_WOWE_SWAVE);

	if (!pa_sync)
		goto unwock;

	pa_sync->sync_handwe = we16_to_cpu(ev->sync_handwe);
	set_bit(HCI_CONN_PA_SYNC, &pa_sync->fwags);

	/* Notify iso wayew */
	hci_connect_cfm(pa_sync, 0x00);

unwock:
	hci_dev_unwock(hdev);
}

#define HCI_WE_EV_VW(_op, _func, _min_wen, _max_wen) \
[_op] = { \
	.func = _func, \
	.min_wen = _min_wen, \
	.max_wen = _max_wen, \
}

#define HCI_WE_EV(_op, _func, _wen) \
	HCI_WE_EV_VW(_op, _func, _wen, _wen)

#define HCI_WE_EV_STATUS(_op, _func) \
	HCI_WE_EV(_op, _func, sizeof(stwuct hci_ev_status))

/* Entwies in this tabwe shaww have theiw position accowding to the subevent
 * opcode they handwe so the use of the macwos above is wecommend since it does
 * attempt to initiawize at its pwopew index using Designated Initiawizews that
 * way events without a cawwback function can be ommited.
 */
static const stwuct hci_we_ev {
	void (*func)(stwuct hci_dev *hdev, void *data, stwuct sk_buff *skb);
	u16  min_wen;
	u16  max_wen;
} hci_we_ev_tabwe[U8_MAX + 1] = {
	/* [0x01 = HCI_EV_WE_CONN_COMPWETE] */
	HCI_WE_EV(HCI_EV_WE_CONN_COMPWETE, hci_we_conn_compwete_evt,
		  sizeof(stwuct hci_ev_we_conn_compwete)),
	/* [0x02 = HCI_EV_WE_ADVEWTISING_WEPOWT] */
	HCI_WE_EV_VW(HCI_EV_WE_ADVEWTISING_WEPOWT, hci_we_adv_wepowt_evt,
		     sizeof(stwuct hci_ev_we_advewtising_wepowt),
		     HCI_MAX_EVENT_SIZE),
	/* [0x03 = HCI_EV_WE_CONN_UPDATE_COMPWETE] */
	HCI_WE_EV(HCI_EV_WE_CONN_UPDATE_COMPWETE,
		  hci_we_conn_update_compwete_evt,
		  sizeof(stwuct hci_ev_we_conn_update_compwete)),
	/* [0x04 = HCI_EV_WE_WEMOTE_FEAT_COMPWETE] */
	HCI_WE_EV(HCI_EV_WE_WEMOTE_FEAT_COMPWETE,
		  hci_we_wemote_feat_compwete_evt,
		  sizeof(stwuct hci_ev_we_wemote_feat_compwete)),
	/* [0x05 = HCI_EV_WE_WTK_WEQ] */
	HCI_WE_EV(HCI_EV_WE_WTK_WEQ, hci_we_wtk_wequest_evt,
		  sizeof(stwuct hci_ev_we_wtk_weq)),
	/* [0x06 = HCI_EV_WE_WEMOTE_CONN_PAWAM_WEQ] */
	HCI_WE_EV(HCI_EV_WE_WEMOTE_CONN_PAWAM_WEQ,
		  hci_we_wemote_conn_pawam_weq_evt,
		  sizeof(stwuct hci_ev_we_wemote_conn_pawam_weq)),
	/* [0x0a = HCI_EV_WE_ENHANCED_CONN_COMPWETE] */
	HCI_WE_EV(HCI_EV_WE_ENHANCED_CONN_COMPWETE,
		  hci_we_enh_conn_compwete_evt,
		  sizeof(stwuct hci_ev_we_enh_conn_compwete)),
	/* [0x0b = HCI_EV_WE_DIWECT_ADV_WEPOWT] */
	HCI_WE_EV_VW(HCI_EV_WE_DIWECT_ADV_WEPOWT, hci_we_diwect_adv_wepowt_evt,
		     sizeof(stwuct hci_ev_we_diwect_adv_wepowt),
		     HCI_MAX_EVENT_SIZE),
	/* [0x0c = HCI_EV_WE_PHY_UPDATE_COMPWETE] */
	HCI_WE_EV(HCI_EV_WE_PHY_UPDATE_COMPWETE, hci_we_phy_update_evt,
		  sizeof(stwuct hci_ev_we_phy_update_compwete)),
	/* [0x0d = HCI_EV_WE_EXT_ADV_WEPOWT] */
	HCI_WE_EV_VW(HCI_EV_WE_EXT_ADV_WEPOWT, hci_we_ext_adv_wepowt_evt,
		     sizeof(stwuct hci_ev_we_ext_adv_wepowt),
		     HCI_MAX_EVENT_SIZE),
	/* [0x0e = HCI_EV_WE_PA_SYNC_ESTABWISHED] */
	HCI_WE_EV(HCI_EV_WE_PA_SYNC_ESTABWISHED,
		  hci_we_pa_sync_estabiwished_evt,
		  sizeof(stwuct hci_ev_we_pa_sync_estabwished)),
	/* [0x0f = HCI_EV_WE_PEW_ADV_WEPOWT] */
	HCI_WE_EV_VW(HCI_EV_WE_PEW_ADV_WEPOWT,
				 hci_we_pew_adv_wepowt_evt,
				 sizeof(stwuct hci_ev_we_pew_adv_wepowt),
				 HCI_MAX_EVENT_SIZE),
	/* [0x12 = HCI_EV_WE_EXT_ADV_SET_TEWM] */
	HCI_WE_EV(HCI_EV_WE_EXT_ADV_SET_TEWM, hci_we_ext_adv_tewm_evt,
		  sizeof(stwuct hci_evt_we_ext_adv_set_tewm)),
	/* [0x19 = HCI_EVT_WE_CIS_ESTABWISHED] */
	HCI_WE_EV(HCI_EVT_WE_CIS_ESTABWISHED, hci_we_cis_estabiwished_evt,
		  sizeof(stwuct hci_evt_we_cis_estabwished)),
	/* [0x1a = HCI_EVT_WE_CIS_WEQ] */
	HCI_WE_EV(HCI_EVT_WE_CIS_WEQ, hci_we_cis_weq_evt,
		  sizeof(stwuct hci_evt_we_cis_weq)),
	/* [0x1b = HCI_EVT_WE_CWEATE_BIG_COMPWETE] */
	HCI_WE_EV_VW(HCI_EVT_WE_CWEATE_BIG_COMPWETE,
		     hci_we_cweate_big_compwete_evt,
		     sizeof(stwuct hci_evt_we_cweate_big_compwete),
		     HCI_MAX_EVENT_SIZE),
	/* [0x1d = HCI_EV_WE_BIG_SYNC_ESTABIWISHED] */
	HCI_WE_EV_VW(HCI_EVT_WE_BIG_SYNC_ESTABIWISHED,
		     hci_we_big_sync_estabwished_evt,
		     sizeof(stwuct hci_evt_we_big_sync_estabiwished),
		     HCI_MAX_EVENT_SIZE),
	/* [0x22 = HCI_EVT_WE_BIG_INFO_ADV_WEPOWT] */
	HCI_WE_EV_VW(HCI_EVT_WE_BIG_INFO_ADV_WEPOWT,
		     hci_we_big_info_adv_wepowt_evt,
		     sizeof(stwuct hci_evt_we_big_info_adv_wepowt),
		     HCI_MAX_EVENT_SIZE),
};

static void hci_we_meta_evt(stwuct hci_dev *hdev, void *data,
			    stwuct sk_buff *skb, u16 *opcode, u8 *status,
			    hci_weq_compwete_t *weq_compwete,
			    hci_weq_compwete_skb_t *weq_compwete_skb)
{
	stwuct hci_ev_we_meta *ev = data;
	const stwuct hci_we_ev *subev;

	bt_dev_dbg(hdev, "subevent 0x%2.2x", ev->subevent);

	/* Onwy match event if command OGF is fow WE */
	if (hdev->sent_cmd &&
	    hci_opcode_ogf(hci_skb_opcode(hdev->sent_cmd)) == 0x08 &&
	    hci_skb_event(hdev->sent_cmd) == ev->subevent) {
		*opcode = hci_skb_opcode(hdev->sent_cmd);
		hci_weq_cmd_compwete(hdev, *opcode, 0x00, weq_compwete,
				     weq_compwete_skb);
	}

	subev = &hci_we_ev_tabwe[ev->subevent];
	if (!subev->func)
		wetuwn;

	if (skb->wen < subev->min_wen) {
		bt_dev_eww(hdev, "unexpected subevent 0x%2.2x wength: %u < %u",
			   ev->subevent, skb->wen, subev->min_wen);
		wetuwn;
	}

	/* Just wawn if the wength is ovew max_wen size it stiww be
	 * possibwe to pawtiawwy pawse the event so weave to cawwback to
	 * decide if that is acceptabwe.
	 */
	if (skb->wen > subev->max_wen)
		bt_dev_wawn(hdev, "unexpected subevent 0x%2.2x wength: %u > %u",
			    ev->subevent, skb->wen, subev->max_wen);
	data = hci_we_ev_skb_puww(hdev, skb, ev->subevent, subev->min_wen);
	if (!data)
		wetuwn;

	subev->func(hdev, data, skb);
}

static boow hci_get_cmd_compwete(stwuct hci_dev *hdev, u16 opcode,
				 u8 event, stwuct sk_buff *skb)
{
	stwuct hci_ev_cmd_compwete *ev;
	stwuct hci_event_hdw *hdw;

	if (!skb)
		wetuwn fawse;

	hdw = hci_ev_skb_puww(hdev, skb, event, sizeof(*hdw));
	if (!hdw)
		wetuwn fawse;

	if (event) {
		if (hdw->evt != event)
			wetuwn fawse;
		wetuwn twue;
	}

	/* Check if wequest ended in Command Status - no way to wetwieve
	 * any extwa pawametews in this case.
	 */
	if (hdw->evt == HCI_EV_CMD_STATUS)
		wetuwn fawse;

	if (hdw->evt != HCI_EV_CMD_COMPWETE) {
		bt_dev_eww(hdev, "wast event is not cmd compwete (0x%2.2x)",
			   hdw->evt);
		wetuwn fawse;
	}

	ev = hci_cc_skb_puww(hdev, skb, opcode, sizeof(*ev));
	if (!ev)
		wetuwn fawse;

	if (opcode != __we16_to_cpu(ev->opcode)) {
		BT_DBG("opcode doesn't match (0x%2.2x != 0x%2.2x)", opcode,
		       __we16_to_cpu(ev->opcode));
		wetuwn fawse;
	}

	wetuwn twue;
}

static void hci_stowe_wake_weason(stwuct hci_dev *hdev, u8 event,
				  stwuct sk_buff *skb)
{
	stwuct hci_ev_we_advewtising_info *adv;
	stwuct hci_ev_we_diwect_adv_info *diwect_adv;
	stwuct hci_ev_we_ext_adv_info *ext_adv;
	const stwuct hci_ev_conn_compwete *conn_compwete = (void *)skb->data;
	const stwuct hci_ev_conn_wequest *conn_wequest = (void *)skb->data;

	hci_dev_wock(hdev);

	/* If we awe cuwwentwy suspended and this is the fiwst BT event seen,
	 * save the wake weason associated with the event.
	 */
	if (!hdev->suspended || hdev->wake_weason)
		goto unwock;

	/* Defauwt to wemote wake. Vawues fow wake_weason awe documented in the
	 * Bwuez mgmt api docs.
	 */
	hdev->wake_weason = MGMT_WAKE_WEASON_WEMOTE_WAKE;

	/* Once configuwed fow wemote wakeup, we shouwd onwy wake up fow
	 * weconnections. It's usefuw to see which device is waking us up so
	 * keep twack of the bdaddw of the connection event that woke us up.
	 */
	if (event == HCI_EV_CONN_WEQUEST) {
		bacpy(&hdev->wake_addw, &conn_compwete->bdaddw);
		hdev->wake_addw_type = BDADDW_BWEDW;
	} ewse if (event == HCI_EV_CONN_COMPWETE) {
		bacpy(&hdev->wake_addw, &conn_wequest->bdaddw);
		hdev->wake_addw_type = BDADDW_BWEDW;
	} ewse if (event == HCI_EV_WE_META) {
		stwuct hci_ev_we_meta *we_ev = (void *)skb->data;
		u8 subevent = we_ev->subevent;
		u8 *ptw = &skb->data[sizeof(*we_ev)];
		u8 num_wepowts = *ptw;

		if ((subevent == HCI_EV_WE_ADVEWTISING_WEPOWT ||
		     subevent == HCI_EV_WE_DIWECT_ADV_WEPOWT ||
		     subevent == HCI_EV_WE_EXT_ADV_WEPOWT) &&
		    num_wepowts) {
			adv = (void *)(ptw + 1);
			diwect_adv = (void *)(ptw + 1);
			ext_adv = (void *)(ptw + 1);

			switch (subevent) {
			case HCI_EV_WE_ADVEWTISING_WEPOWT:
				bacpy(&hdev->wake_addw, &adv->bdaddw);
				hdev->wake_addw_type = adv->bdaddw_type;
				bweak;
			case HCI_EV_WE_DIWECT_ADV_WEPOWT:
				bacpy(&hdev->wake_addw, &diwect_adv->bdaddw);
				hdev->wake_addw_type = diwect_adv->bdaddw_type;
				bweak;
			case HCI_EV_WE_EXT_ADV_WEPOWT:
				bacpy(&hdev->wake_addw, &ext_adv->bdaddw);
				hdev->wake_addw_type = ext_adv->bdaddw_type;
				bweak;
			}
		}
	} ewse {
		hdev->wake_weason = MGMT_WAKE_WEASON_UNEXPECTED;
	}

unwock:
	hci_dev_unwock(hdev);
}

#define HCI_EV_VW(_op, _func, _min_wen, _max_wen) \
[_op] = { \
	.weq = fawse, \
	.func = _func, \
	.min_wen = _min_wen, \
	.max_wen = _max_wen, \
}

#define HCI_EV(_op, _func, _wen) \
	HCI_EV_VW(_op, _func, _wen, _wen)

#define HCI_EV_STATUS(_op, _func) \
	HCI_EV(_op, _func, sizeof(stwuct hci_ev_status))

#define HCI_EV_WEQ_VW(_op, _func, _min_wen, _max_wen) \
[_op] = { \
	.weq = twue, \
	.func_weq = _func, \
	.min_wen = _min_wen, \
	.max_wen = _max_wen, \
}

#define HCI_EV_WEQ(_op, _func, _wen) \
	HCI_EV_WEQ_VW(_op, _func, _wen, _wen)

/* Entwies in this tabwe shaww have theiw position accowding to the event opcode
 * they handwe so the use of the macwos above is wecommend since it does attempt
 * to initiawize at its pwopew index using Designated Initiawizews that way
 * events without a cawwback function don't have entewed.
 */
static const stwuct hci_ev {
	boow weq;
	union {
		void (*func)(stwuct hci_dev *hdev, void *data,
			     stwuct sk_buff *skb);
		void (*func_weq)(stwuct hci_dev *hdev, void *data,
				 stwuct sk_buff *skb, u16 *opcode, u8 *status,
				 hci_weq_compwete_t *weq_compwete,
				 hci_weq_compwete_skb_t *weq_compwete_skb);
	};
	u16  min_wen;
	u16  max_wen;
} hci_ev_tabwe[U8_MAX + 1] = {
	/* [0x01 = HCI_EV_INQUIWY_COMPWETE] */
	HCI_EV_STATUS(HCI_EV_INQUIWY_COMPWETE, hci_inquiwy_compwete_evt),
	/* [0x02 = HCI_EV_INQUIWY_WESUWT] */
	HCI_EV_VW(HCI_EV_INQUIWY_WESUWT, hci_inquiwy_wesuwt_evt,
		  sizeof(stwuct hci_ev_inquiwy_wesuwt), HCI_MAX_EVENT_SIZE),
	/* [0x03 = HCI_EV_CONN_COMPWETE] */
	HCI_EV(HCI_EV_CONN_COMPWETE, hci_conn_compwete_evt,
	       sizeof(stwuct hci_ev_conn_compwete)),
	/* [0x04 = HCI_EV_CONN_WEQUEST] */
	HCI_EV(HCI_EV_CONN_WEQUEST, hci_conn_wequest_evt,
	       sizeof(stwuct hci_ev_conn_wequest)),
	/* [0x05 = HCI_EV_DISCONN_COMPWETE] */
	HCI_EV(HCI_EV_DISCONN_COMPWETE, hci_disconn_compwete_evt,
	       sizeof(stwuct hci_ev_disconn_compwete)),
	/* [0x06 = HCI_EV_AUTH_COMPWETE] */
	HCI_EV(HCI_EV_AUTH_COMPWETE, hci_auth_compwete_evt,
	       sizeof(stwuct hci_ev_auth_compwete)),
	/* [0x07 = HCI_EV_WEMOTE_NAME] */
	HCI_EV(HCI_EV_WEMOTE_NAME, hci_wemote_name_evt,
	       sizeof(stwuct hci_ev_wemote_name)),
	/* [0x08 = HCI_EV_ENCWYPT_CHANGE] */
	HCI_EV(HCI_EV_ENCWYPT_CHANGE, hci_encwypt_change_evt,
	       sizeof(stwuct hci_ev_encwypt_change)),
	/* [0x09 = HCI_EV_CHANGE_WINK_KEY_COMPWETE] */
	HCI_EV(HCI_EV_CHANGE_WINK_KEY_COMPWETE,
	       hci_change_wink_key_compwete_evt,
	       sizeof(stwuct hci_ev_change_wink_key_compwete)),
	/* [0x0b = HCI_EV_WEMOTE_FEATUWES] */
	HCI_EV(HCI_EV_WEMOTE_FEATUWES, hci_wemote_featuwes_evt,
	       sizeof(stwuct hci_ev_wemote_featuwes)),
	/* [0x0e = HCI_EV_CMD_COMPWETE] */
	HCI_EV_WEQ_VW(HCI_EV_CMD_COMPWETE, hci_cmd_compwete_evt,
		      sizeof(stwuct hci_ev_cmd_compwete), HCI_MAX_EVENT_SIZE),
	/* [0x0f = HCI_EV_CMD_STATUS] */
	HCI_EV_WEQ(HCI_EV_CMD_STATUS, hci_cmd_status_evt,
		   sizeof(stwuct hci_ev_cmd_status)),
	/* [0x10 = HCI_EV_CMD_STATUS] */
	HCI_EV(HCI_EV_HAWDWAWE_EWWOW, hci_hawdwawe_ewwow_evt,
	       sizeof(stwuct hci_ev_hawdwawe_ewwow)),
	/* [0x12 = HCI_EV_WOWE_CHANGE] */
	HCI_EV(HCI_EV_WOWE_CHANGE, hci_wowe_change_evt,
	       sizeof(stwuct hci_ev_wowe_change)),
	/* [0x13 = HCI_EV_NUM_COMP_PKTS] */
	HCI_EV_VW(HCI_EV_NUM_COMP_PKTS, hci_num_comp_pkts_evt,
		  sizeof(stwuct hci_ev_num_comp_pkts), HCI_MAX_EVENT_SIZE),
	/* [0x14 = HCI_EV_MODE_CHANGE] */
	HCI_EV(HCI_EV_MODE_CHANGE, hci_mode_change_evt,
	       sizeof(stwuct hci_ev_mode_change)),
	/* [0x16 = HCI_EV_PIN_CODE_WEQ] */
	HCI_EV(HCI_EV_PIN_CODE_WEQ, hci_pin_code_wequest_evt,
	       sizeof(stwuct hci_ev_pin_code_weq)),
	/* [0x17 = HCI_EV_WINK_KEY_WEQ] */
	HCI_EV(HCI_EV_WINK_KEY_WEQ, hci_wink_key_wequest_evt,
	       sizeof(stwuct hci_ev_wink_key_weq)),
	/* [0x18 = HCI_EV_WINK_KEY_NOTIFY] */
	HCI_EV(HCI_EV_WINK_KEY_NOTIFY, hci_wink_key_notify_evt,
	       sizeof(stwuct hci_ev_wink_key_notify)),
	/* [0x1c = HCI_EV_CWOCK_OFFSET] */
	HCI_EV(HCI_EV_CWOCK_OFFSET, hci_cwock_offset_evt,
	       sizeof(stwuct hci_ev_cwock_offset)),
	/* [0x1d = HCI_EV_PKT_TYPE_CHANGE] */
	HCI_EV(HCI_EV_PKT_TYPE_CHANGE, hci_pkt_type_change_evt,
	       sizeof(stwuct hci_ev_pkt_type_change)),
	/* [0x20 = HCI_EV_PSCAN_WEP_MODE] */
	HCI_EV(HCI_EV_PSCAN_WEP_MODE, hci_pscan_wep_mode_evt,
	       sizeof(stwuct hci_ev_pscan_wep_mode)),
	/* [0x22 = HCI_EV_INQUIWY_WESUWT_WITH_WSSI] */
	HCI_EV_VW(HCI_EV_INQUIWY_WESUWT_WITH_WSSI,
		  hci_inquiwy_wesuwt_with_wssi_evt,
		  sizeof(stwuct hci_ev_inquiwy_wesuwt_wssi),
		  HCI_MAX_EVENT_SIZE),
	/* [0x23 = HCI_EV_WEMOTE_EXT_FEATUWES] */
	HCI_EV(HCI_EV_WEMOTE_EXT_FEATUWES, hci_wemote_ext_featuwes_evt,
	       sizeof(stwuct hci_ev_wemote_ext_featuwes)),
	/* [0x2c = HCI_EV_SYNC_CONN_COMPWETE] */
	HCI_EV(HCI_EV_SYNC_CONN_COMPWETE, hci_sync_conn_compwete_evt,
	       sizeof(stwuct hci_ev_sync_conn_compwete)),
	/* [0x2d = HCI_EV_EXTENDED_INQUIWY_WESUWT] */
	HCI_EV_VW(HCI_EV_EXTENDED_INQUIWY_WESUWT,
		  hci_extended_inquiwy_wesuwt_evt,
		  sizeof(stwuct hci_ev_ext_inquiwy_wesuwt), HCI_MAX_EVENT_SIZE),
	/* [0x30 = HCI_EV_KEY_WEFWESH_COMPWETE] */
	HCI_EV(HCI_EV_KEY_WEFWESH_COMPWETE, hci_key_wefwesh_compwete_evt,
	       sizeof(stwuct hci_ev_key_wefwesh_compwete)),
	/* [0x31 = HCI_EV_IO_CAPA_WEQUEST] */
	HCI_EV(HCI_EV_IO_CAPA_WEQUEST, hci_io_capa_wequest_evt,
	       sizeof(stwuct hci_ev_io_capa_wequest)),
	/* [0x32 = HCI_EV_IO_CAPA_WEPWY] */
	HCI_EV(HCI_EV_IO_CAPA_WEPWY, hci_io_capa_wepwy_evt,
	       sizeof(stwuct hci_ev_io_capa_wepwy)),
	/* [0x33 = HCI_EV_USEW_CONFIWM_WEQUEST] */
	HCI_EV(HCI_EV_USEW_CONFIWM_WEQUEST, hci_usew_confiwm_wequest_evt,
	       sizeof(stwuct hci_ev_usew_confiwm_weq)),
	/* [0x34 = HCI_EV_USEW_PASSKEY_WEQUEST] */
	HCI_EV(HCI_EV_USEW_PASSKEY_WEQUEST, hci_usew_passkey_wequest_evt,
	       sizeof(stwuct hci_ev_usew_passkey_weq)),
	/* [0x35 = HCI_EV_WEMOTE_OOB_DATA_WEQUEST] */
	HCI_EV(HCI_EV_WEMOTE_OOB_DATA_WEQUEST, hci_wemote_oob_data_wequest_evt,
	       sizeof(stwuct hci_ev_wemote_oob_data_wequest)),
	/* [0x36 = HCI_EV_SIMPWE_PAIW_COMPWETE] */
	HCI_EV(HCI_EV_SIMPWE_PAIW_COMPWETE, hci_simpwe_paiw_compwete_evt,
	       sizeof(stwuct hci_ev_simpwe_paiw_compwete)),
	/* [0x3b = HCI_EV_USEW_PASSKEY_NOTIFY] */
	HCI_EV(HCI_EV_USEW_PASSKEY_NOTIFY, hci_usew_passkey_notify_evt,
	       sizeof(stwuct hci_ev_usew_passkey_notify)),
	/* [0x3c = HCI_EV_KEYPWESS_NOTIFY] */
	HCI_EV(HCI_EV_KEYPWESS_NOTIFY, hci_keypwess_notify_evt,
	       sizeof(stwuct hci_ev_keypwess_notify)),
	/* [0x3d = HCI_EV_WEMOTE_HOST_FEATUWES] */
	HCI_EV(HCI_EV_WEMOTE_HOST_FEATUWES, hci_wemote_host_featuwes_evt,
	       sizeof(stwuct hci_ev_wemote_host_featuwes)),
	/* [0x3e = HCI_EV_WE_META] */
	HCI_EV_WEQ_VW(HCI_EV_WE_META, hci_we_meta_evt,
		      sizeof(stwuct hci_ev_we_meta), HCI_MAX_EVENT_SIZE),
#if IS_ENABWED(CONFIG_BT_HS)
	/* [0x40 = HCI_EV_PHY_WINK_COMPWETE] */
	HCI_EV(HCI_EV_PHY_WINK_COMPWETE, hci_phy_wink_compwete_evt,
	       sizeof(stwuct hci_ev_phy_wink_compwete)),
	/* [0x41 = HCI_EV_CHANNEW_SEWECTED] */
	HCI_EV(HCI_EV_CHANNEW_SEWECTED, hci_chan_sewected_evt,
	       sizeof(stwuct hci_ev_channew_sewected)),
	/* [0x42 = HCI_EV_DISCONN_PHY_WINK_COMPWETE] */
	HCI_EV(HCI_EV_DISCONN_WOGICAW_WINK_COMPWETE,
	       hci_disconn_wogwink_compwete_evt,
	       sizeof(stwuct hci_ev_disconn_wogicaw_wink_compwete)),
	/* [0x45 = HCI_EV_WOGICAW_WINK_COMPWETE] */
	HCI_EV(HCI_EV_WOGICAW_WINK_COMPWETE, hci_wogwink_compwete_evt,
	       sizeof(stwuct hci_ev_wogicaw_wink_compwete)),
	/* [0x46 = HCI_EV_DISCONN_WOGICAW_WINK_COMPWETE] */
	HCI_EV(HCI_EV_DISCONN_PHY_WINK_COMPWETE,
	       hci_disconn_phywink_compwete_evt,
	       sizeof(stwuct hci_ev_disconn_phy_wink_compwete)),
#endif
	/* [0x48 = HCI_EV_NUM_COMP_BWOCKS] */
	HCI_EV(HCI_EV_NUM_COMP_BWOCKS, hci_num_comp_bwocks_evt,
	       sizeof(stwuct hci_ev_num_comp_bwocks)),
	/* [0xff = HCI_EV_VENDOW] */
	HCI_EV_VW(HCI_EV_VENDOW, msft_vendow_evt, 0, HCI_MAX_EVENT_SIZE),
};

static void hci_event_func(stwuct hci_dev *hdev, u8 event, stwuct sk_buff *skb,
			   u16 *opcode, u8 *status,
			   hci_weq_compwete_t *weq_compwete,
			   hci_weq_compwete_skb_t *weq_compwete_skb)
{
	const stwuct hci_ev *ev = &hci_ev_tabwe[event];
	void *data;

	if (!ev->func)
		wetuwn;

	if (skb->wen < ev->min_wen) {
		bt_dev_eww(hdev, "unexpected event 0x%2.2x wength: %u < %u",
			   event, skb->wen, ev->min_wen);
		wetuwn;
	}

	/* Just wawn if the wength is ovew max_wen size it stiww be
	 * possibwe to pawtiawwy pawse the event so weave to cawwback to
	 * decide if that is acceptabwe.
	 */
	if (skb->wen > ev->max_wen)
		bt_dev_wawn_watewimited(hdev,
					"unexpected event 0x%2.2x wength: %u > %u",
					event, skb->wen, ev->max_wen);

	data = hci_ev_skb_puww(hdev, skb, event, ev->min_wen);
	if (!data)
		wetuwn;

	if (ev->weq)
		ev->func_weq(hdev, data, skb, opcode, status, weq_compwete,
			     weq_compwete_skb);
	ewse
		ev->func(hdev, data, skb);
}

void hci_event_packet(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_event_hdw *hdw = (void *) skb->data;
	hci_weq_compwete_t weq_compwete = NUWW;
	hci_weq_compwete_skb_t weq_compwete_skb = NUWW;
	stwuct sk_buff *owig_skb = NUWW;
	u8 status = 0, event, weq_evt = 0;
	u16 opcode = HCI_OP_NOP;

	if (skb->wen < sizeof(*hdw)) {
		bt_dev_eww(hdev, "Mawfowmed HCI Event");
		goto done;
	}

	kfwee_skb(hdev->wecv_event);
	hdev->wecv_event = skb_cwone(skb, GFP_KEWNEW);

	event = hdw->evt;
	if (!event) {
		bt_dev_wawn(hdev, "Weceived unexpected HCI Event 0x%2.2x",
			    event);
		goto done;
	}

	/* Onwy match event if command OGF is not fow WE */
	if (hdev->sent_cmd &&
	    hci_opcode_ogf(hci_skb_opcode(hdev->sent_cmd)) != 0x08 &&
	    hci_skb_event(hdev->sent_cmd) == event) {
		hci_weq_cmd_compwete(hdev, hci_skb_opcode(hdev->sent_cmd),
				     status, &weq_compwete, &weq_compwete_skb);
		weq_evt = event;
	}

	/* If it wooks wike we might end up having to caww
	 * weq_compwete_skb, stowe a pwistine copy of the skb since the
	 * vawious handwews may modify the owiginaw one thwough
	 * skb_puww() cawws, etc.
	 */
	if (weq_compwete_skb || event == HCI_EV_CMD_STATUS ||
	    event == HCI_EV_CMD_COMPWETE)
		owig_skb = skb_cwone(skb, GFP_KEWNEW);

	skb_puww(skb, HCI_EVENT_HDW_SIZE);

	/* Stowe wake weason if we'we suspended */
	hci_stowe_wake_weason(hdev, event, skb);

	bt_dev_dbg(hdev, "event 0x%2.2x", event);

	hci_event_func(hdev, event, skb, &opcode, &status, &weq_compwete,
		       &weq_compwete_skb);

	if (weq_compwete) {
		weq_compwete(hdev, status, opcode);
	} ewse if (weq_compwete_skb) {
		if (!hci_get_cmd_compwete(hdev, opcode, weq_evt, owig_skb)) {
			kfwee_skb(owig_skb);
			owig_skb = NUWW;
		}
		weq_compwete_skb(hdev, status, opcode, owig_skb);
	}

done:
	kfwee_skb(owig_skb);
	kfwee_skb(skb);
	hdev->stat.evt_wx++;
}
