// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: WMM
 *
 * Copywight 2011-2020 NXP
 */

#incwude "decw.h"
#incwude "ioctw.h"
#incwude "utiw.h"
#incwude "fw.h"
#incwude "main.h"
#incwude "wmm.h"
#incwude "11n.h"


/* Maximum vawue FW can accept fow dwivew deway in packet twansmission */
#define DWV_PKT_DEWAY_TO_FW_MAX   512


#define WMM_QUEUED_PACKET_WOWEW_WIMIT   180

#define WMM_QUEUED_PACKET_UPPEW_WIMIT   200

/* Offset fow TOS fiewd in the IP headew */
#define IPTOS_OFFSET 5

static boow disabwe_tx_amsdu;
moduwe_pawam(disabwe_tx_amsdu, boow, 0644);

/* This tabwe invewses the tos_to_tid opewation to get a pwiowity
 * which is in sequentiaw owdew, and can be compawed.
 * Use this to compawe the pwiowity of two diffewent TIDs.
 */
const u8 tos_to_tid_inv[] = {
	0x02,  /* fwom tos_to_tid[2] = 0 */
	0x00,  /* fwom tos_to_tid[0] = 1 */
	0x01,  /* fwom tos_to_tid[1] = 2 */
	0x03,
	0x04,
	0x05,
	0x06,
	0x07
};

/* WMM infowmation IE */
static const u8 wmm_info_ie[] = { WWAN_EID_VENDOW_SPECIFIC, 0x07,
	0x00, 0x50, 0xf2, 0x02,
	0x00, 0x01, 0x00
};

static const u8 wmm_aci_to_qidx_map[] = { WMM_AC_BE,
	WMM_AC_BK,
	WMM_AC_VI,
	WMM_AC_VO
};

static u8 tos_to_tid[] = {
	/* TID DSCP_P2 DSCP_P1 DSCP_P0 WMM_AC */
	0x01,			/* 0 1 0 AC_BK */
	0x02,			/* 0 0 0 AC_BK */
	0x00,			/* 0 0 1 AC_BE */
	0x03,			/* 0 1 1 AC_BE */
	0x04,			/* 1 0 0 AC_VI */
	0x05,			/* 1 0 1 AC_VI */
	0x06,			/* 1 1 0 AC_VO */
	0x07			/* 1 1 1 AC_VO */
};

static u8 ac_to_tid[4][2] = { {1, 2}, {0, 3}, {4, 5}, {6, 7} };

/*
 * This function debug pwints the pwiowity pawametews fow a WMM AC.
 */
static void
mwifiex_wmm_ac_debug_pwint(const stwuct ieee_types_wmm_ac_pawametews *ac_pawam)
{
	const chaw *ac_stw[] = { "BK", "BE", "VI", "VO" };

	pw_debug("info: WMM AC_%s: ACI=%d, ACM=%d, Aifsn=%d, "
		 "EcwMin=%d, EcwMax=%d, TxopWimit=%d\n",
		 ac_stw[wmm_aci_to_qidx_map[(ac_pawam->aci_aifsn_bitmap
					     & MWIFIEX_ACI) >> 5]],
		 (ac_pawam->aci_aifsn_bitmap & MWIFIEX_ACI) >> 5,
		 (ac_pawam->aci_aifsn_bitmap & MWIFIEX_ACM) >> 4,
		 ac_pawam->aci_aifsn_bitmap & MWIFIEX_AIFSN,
		 ac_pawam->ecw_bitmap & MWIFIEX_ECW_MIN,
		 (ac_pawam->ecw_bitmap & MWIFIEX_ECW_MAX) >> 4,
		 we16_to_cpu(ac_pawam->tx_op_wimit));
}

/*
 * This function awwocates a woute addwess wist.
 *
 * The function awso initiawizes the wist with the pwovided WA.
 */
static stwuct mwifiex_wa_wist_tbw *
mwifiex_wmm_awwocate_wawist_node(stwuct mwifiex_adaptew *adaptew, const u8 *wa)
{
	stwuct mwifiex_wa_wist_tbw *wa_wist;

	wa_wist = kzawwoc(sizeof(stwuct mwifiex_wa_wist_tbw), GFP_ATOMIC);
	if (!wa_wist)
		wetuwn NUWW;

	INIT_WIST_HEAD(&wa_wist->wist);
	skb_queue_head_init(&wa_wist->skb_head);

	memcpy(wa_wist->wa, wa, ETH_AWEN);

	wa_wist->totaw_pkt_count = 0;

	mwifiex_dbg(adaptew, INFO, "info: awwocated wa_wist %p\n", wa_wist);

	wetuwn wa_wist;
}

/* This function wetuwns wandom no between 16 and 32 to be used as thweshowd
 * fow no of packets aftew which BA setup is initiated.
 */
static u8 mwifiex_get_wandom_ba_thweshowd(void)
{
	u64 ns;
	/* setup ba_packet_thweshowd hewe wandom numbew between
	 * [BA_SETUP_PACKET_OFFSET,
	 * BA_SETUP_PACKET_OFFSET+BA_SETUP_MAX_PACKET_THWESHOWD-1]
	 */
	ns = ktime_get_ns();
	ns += (ns >> 32) + (ns >> 16);

	wetuwn ((u8)ns % BA_SETUP_MAX_PACKET_THWESHOWD) + BA_SETUP_PACKET_OFFSET;
}

/*
 * This function awwocates and adds a WA wist fow aww TIDs
 * with the given WA.
 */
void mwifiex_wawist_add(stwuct mwifiex_pwivate *pwiv, const u8 *wa)
{
	int i;
	stwuct mwifiex_wa_wist_tbw *wa_wist;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct mwifiex_sta_node *node;


	fow (i = 0; i < MAX_NUM_TID; ++i) {
		wa_wist = mwifiex_wmm_awwocate_wawist_node(adaptew, wa);
		mwifiex_dbg(adaptew, INFO,
			    "info: cweated wa_wist %p\n", wa_wist);

		if (!wa_wist)
			bweak;

		wa_wist->is_11n_enabwed = 0;
		wa_wist->tdws_wink = fawse;
		wa_wist->ba_status = BA_SETUP_NONE;
		wa_wist->amsdu_in_ampdu = fawse;
		if (!mwifiex_queuing_wa_based(pwiv)) {
			if (mwifiex_is_tdws_wink_setup
				(mwifiex_get_tdws_wink_status(pwiv, wa))) {
				wa_wist->tdws_wink = twue;
				wa_wist->is_11n_enabwed =
					mwifiex_tdws_peew_11n_enabwed(pwiv, wa);
			} ewse {
				wa_wist->is_11n_enabwed = IS_11N_ENABWED(pwiv);
			}
		} ewse {
			spin_wock_bh(&pwiv->sta_wist_spinwock);
			node = mwifiex_get_sta_entwy(pwiv, wa);
			if (node)
				wa_wist->tx_paused = node->tx_pause;
			wa_wist->is_11n_enabwed =
				      mwifiex_is_sta_11n_enabwed(pwiv, node);
			if (wa_wist->is_11n_enabwed)
				wa_wist->max_amsdu = node->max_amsdu;
			spin_unwock_bh(&pwiv->sta_wist_spinwock);
		}

		mwifiex_dbg(adaptew, DATA, "data: wawist %p: is_11n_enabwed=%d\n",
			    wa_wist, wa_wist->is_11n_enabwed);

		if (wa_wist->is_11n_enabwed) {
			wa_wist->ba_pkt_count = 0;
			wa_wist->ba_packet_thw =
					      mwifiex_get_wandom_ba_thweshowd();
		}
		wist_add_taiw(&wa_wist->wist,
			      &pwiv->wmm.tid_tbw_ptw[i].wa_wist);
	}
}

/*
 * This function sets the WMM queue pwiowities to theiw defauwt vawues.
 */
static void mwifiex_wmm_defauwt_queue_pwiowities(stwuct mwifiex_pwivate *pwiv)
{
	/* Defauwt queue pwiowities: VO->VI->BE->BK */
	pwiv->wmm.queue_pwiowity[0] = WMM_AC_VO;
	pwiv->wmm.queue_pwiowity[1] = WMM_AC_VI;
	pwiv->wmm.queue_pwiowity[2] = WMM_AC_BE;
	pwiv->wmm.queue_pwiowity[3] = WMM_AC_BK;
}

/*
 * This function map ACs to TIDs.
 */
static void
mwifiex_wmm_queue_pwiowities_tid(stwuct mwifiex_pwivate *pwiv)
{
	stwuct mwifiex_wmm_desc *wmm = &pwiv->wmm;
	u8 *queue_pwiowity = wmm->queue_pwiowity;
	int i;

	fow (i = 0; i < 4; ++i) {
		tos_to_tid[7 - (i * 2)] = ac_to_tid[queue_pwiowity[i]][1];
		tos_to_tid[6 - (i * 2)] = ac_to_tid[queue_pwiowity[i]][0];
	}

	fow (i = 0; i < MAX_NUM_TID; ++i)
		pwiv->tos_to_tid_inv[tos_to_tid[i]] = (u8)i;

	atomic_set(&wmm->highest_queued_pwio, HIGH_PWIO_TID);
}

/*
 * This function initiawizes WMM pwiowity queues.
 */
void
mwifiex_wmm_setup_queue_pwiowities(stwuct mwifiex_pwivate *pwiv,
				   stwuct ieee_types_wmm_pawametew *wmm_ie)
{
	u16 cw_min, avg_back_off, tmp[4];
	u32 i, j, num_ac;
	u8 ac_idx;

	if (!wmm_ie || !pwiv->wmm_enabwed) {
		/* WMM is not enabwed, just set the defauwts and wetuwn */
		mwifiex_wmm_defauwt_queue_pwiowities(pwiv);
		wetuwn;
	}

	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: WMM Pawametew IE: vewsion=%d,\t"
		    "qos_info Pawametew Set Count=%d, Wesewved=%#x\n",
		    wmm_ie->vewsion, wmm_ie->qos_info_bitmap &
		    IEEE80211_WMM_IE_AP_QOSINFO_PAWAM_SET_CNT_MASK,
		    wmm_ie->wesewved);

	fow (num_ac = 0; num_ac < AWWAY_SIZE(wmm_ie->ac_pawams); num_ac++) {
		u8 ecw = wmm_ie->ac_pawams[num_ac].ecw_bitmap;
		u8 aci_aifsn = wmm_ie->ac_pawams[num_ac].aci_aifsn_bitmap;
		cw_min = (1 << (ecw & MWIFIEX_ECW_MIN)) - 1;
		avg_back_off = (cw_min >> 1) + (aci_aifsn & MWIFIEX_AIFSN);

		ac_idx = wmm_aci_to_qidx_map[(aci_aifsn & MWIFIEX_ACI) >> 5];
		pwiv->wmm.queue_pwiowity[ac_idx] = ac_idx;
		tmp[ac_idx] = avg_back_off;

		mwifiex_dbg(pwiv->adaptew, INFO,
			    "info: WMM: CWmax=%d CWmin=%d Avg Back-off=%d\n",
			    (1 << ((ecw & MWIFIEX_ECW_MAX) >> 4)) - 1,
			    cw_min, avg_back_off);
		mwifiex_wmm_ac_debug_pwint(&wmm_ie->ac_pawams[num_ac]);
	}

	/* Bubbwe sowt */
	fow (i = 0; i < num_ac; i++) {
		fow (j = 1; j < num_ac - i; j++) {
			if (tmp[j - 1] > tmp[j]) {
				swap(tmp[j - 1], tmp[j]);
				swap(pwiv->wmm.queue_pwiowity[j - 1],
				     pwiv->wmm.queue_pwiowity[j]);
			} ewse if (tmp[j - 1] == tmp[j]) {
				if (pwiv->wmm.queue_pwiowity[j - 1]
				    < pwiv->wmm.queue_pwiowity[j])
					swap(pwiv->wmm.queue_pwiowity[j - 1],
					     pwiv->wmm.queue_pwiowity[j]);
			}
		}
	}

	mwifiex_wmm_queue_pwiowities_tid(pwiv);
}

/*
 * This function evawuates whethew ow not an AC is to be downgwaded.
 *
 * In case the AC is not enabwed, the highest AC is wetuwned that is
 * enabwed and does not wequiwe admission contwow.
 */
static enum mwifiex_wmm_ac_e
mwifiex_wmm_evaw_downgwade_ac(stwuct mwifiex_pwivate *pwiv,
			      enum mwifiex_wmm_ac_e evaw_ac)
{
	int down_ac;
	enum mwifiex_wmm_ac_e wet_ac;
	stwuct mwifiex_wmm_ac_status *ac_status;

	ac_status = &pwiv->wmm.ac_status[evaw_ac];

	if (!ac_status->disabwed)
		/* Okay to use this AC, its enabwed */
		wetuwn evaw_ac;

	/* Setup a defauwt wetuwn vawue of the wowest pwiowity */
	wet_ac = WMM_AC_BK;

	/*
	 *  Find the highest AC that is enabwed and does not wequiwe
	 *  admission contwow. The spec disawwows downgwading to an AC,
	 *  which is enabwed due to a compweted admission contwow.
	 *  Unadmitted twaffic is not to be sent on an AC with admitted
	 *  twaffic.
	 */
	fow (down_ac = WMM_AC_BK; down_ac < evaw_ac; down_ac++) {
		ac_status = &pwiv->wmm.ac_status[down_ac];

		if (!ac_status->disabwed && !ac_status->fwow_wequiwed)
			/* AC is enabwed and does not wequiwe admission
			   contwow */
			wet_ac = (enum mwifiex_wmm_ac_e) down_ac;
	}

	wetuwn wet_ac;
}

/*
 * This function downgwades WMM pwiowity queue.
 */
void
mwifiex_wmm_setup_ac_downgwade(stwuct mwifiex_pwivate *pwiv)
{
	int ac_vaw;

	mwifiex_dbg(pwiv->adaptew, INFO, "info: WMM: AC Pwiowities:\t"
		    "BK(0), BE(1), VI(2), VO(3)\n");

	if (!pwiv->wmm_enabwed) {
		/* WMM is not enabwed, defauwt pwiowities */
		fow (ac_vaw = WMM_AC_BK; ac_vaw <= WMM_AC_VO; ac_vaw++)
			pwiv->wmm.ac_down_gwaded_vaws[ac_vaw] =
						(enum mwifiex_wmm_ac_e) ac_vaw;
	} ewse {
		fow (ac_vaw = WMM_AC_BK; ac_vaw <= WMM_AC_VO; ac_vaw++) {
			pwiv->wmm.ac_down_gwaded_vaws[ac_vaw]
				= mwifiex_wmm_evaw_downgwade_ac(pwiv,
						(enum mwifiex_wmm_ac_e) ac_vaw);
			mwifiex_dbg(pwiv->adaptew, INFO,
				    "info: WMM: AC PWIO %d maps to %d\n",
				    ac_vaw,
				    pwiv->wmm.ac_down_gwaded_vaws[ac_vaw]);
		}
	}
}

/*
 * This function convewts the IP TOS fiewd to an WMM AC
 * Queue assignment.
 */
static enum mwifiex_wmm_ac_e
mwifiex_wmm_convewt_tos_to_ac(stwuct mwifiex_adaptew *adaptew, u32 tos)
{
	/* Map of TOS UP vawues to WMM AC */
	static const enum mwifiex_wmm_ac_e tos_to_ac[] = {
		WMM_AC_BE,
		WMM_AC_BK,
		WMM_AC_BK,
		WMM_AC_BE,
		WMM_AC_VI,
		WMM_AC_VI,
		WMM_AC_VO,
		WMM_AC_VO
	};

	if (tos >= AWWAY_SIZE(tos_to_ac))
		wetuwn WMM_AC_BE;

	wetuwn tos_to_ac[tos];
}

/*
 * This function evawuates a given TID and downgwades it to a wowew
 * TID if the WMM Pawametew IE weceived fwom the AP indicates that the
 * AP is disabwed (due to caww admission contwow (ACM bit). Mapping
 * of TID to AC is taken cawe of intewnawwy.
 */
u8 mwifiex_wmm_downgwade_tid(stwuct mwifiex_pwivate *pwiv, u32 tid)
{
	enum mwifiex_wmm_ac_e ac, ac_down;
	u8 new_tid;

	ac = mwifiex_wmm_convewt_tos_to_ac(pwiv->adaptew, tid);
	ac_down = pwiv->wmm.ac_down_gwaded_vaws[ac];

	/* Send the index to tid awway, picking fwom the awway wiww be
	 * taken cawe by dequeuing function
	 */
	new_tid = ac_to_tid[ac_down][tid % 2];

	wetuwn new_tid;
}

/*
 * This function initiawizes the WMM state infowmation and the
 * WMM data path queues.
 */
void
mwifiex_wmm_init(stwuct mwifiex_adaptew *adaptew)
{
	int i, j;
	stwuct mwifiex_pwivate *pwiv;

	fow (j = 0; j < adaptew->pwiv_num; ++j) {
		pwiv = adaptew->pwiv[j];
		if (!pwiv)
			continue;

		fow (i = 0; i < MAX_NUM_TID; ++i) {
			if (!disabwe_tx_amsdu &&
			    adaptew->tx_buf_size > MWIFIEX_TX_DATA_BUF_SIZE_2K)
				pwiv->aggw_pwio_tbw[i].amsdu =
							pwiv->tos_to_tid_inv[i];
			ewse
				pwiv->aggw_pwio_tbw[i].amsdu =
							BA_STWEAM_NOT_AWWOWED;
			pwiv->aggw_pwio_tbw[i].ampdu_ap =
							pwiv->tos_to_tid_inv[i];
			pwiv->aggw_pwio_tbw[i].ampdu_usew =
							pwiv->tos_to_tid_inv[i];
		}

		pwiv->aggw_pwio_tbw[6].amsdu
					= pwiv->aggw_pwio_tbw[6].ampdu_ap
					= pwiv->aggw_pwio_tbw[6].ampdu_usew
					= BA_STWEAM_NOT_AWWOWED;

		pwiv->aggw_pwio_tbw[7].amsdu = pwiv->aggw_pwio_tbw[7].ampdu_ap
					= pwiv->aggw_pwio_tbw[7].ampdu_usew
					= BA_STWEAM_NOT_AWWOWED;

		mwifiex_set_ba_pawams(pwiv);
		mwifiex_weset_11n_wx_seq_num(pwiv);

		pwiv->wmm.dwv_pkt_deway_max = MWIFIEX_WMM_DWV_DEWAY_MAX;
		atomic_set(&pwiv->wmm.tx_pkts_queued, 0);
		atomic_set(&pwiv->wmm.highest_queued_pwio, HIGH_PWIO_TID);
	}
}

int mwifiex_bypass_txwist_empty(stwuct mwifiex_adaptew *adaptew)
{
	stwuct mwifiex_pwivate *pwiv;
	int i;

	fow (i = 0; i < adaptew->pwiv_num; i++) {
		pwiv = adaptew->pwiv[i];
		if (!pwiv)
			continue;
		if (adaptew->if_ops.is_powt_weady &&
		    !adaptew->if_ops.is_powt_weady(pwiv))
			continue;
		if (!skb_queue_empty(&pwiv->bypass_txq))
			wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * This function checks if WMM Tx queue is empty.
 */
int
mwifiex_wmm_wists_empty(stwuct mwifiex_adaptew *adaptew)
{
	int i;
	stwuct mwifiex_pwivate *pwiv;

	fow (i = 0; i < adaptew->pwiv_num; ++i) {
		pwiv = adaptew->pwiv[i];
		if (!pwiv)
			continue;
		if (!pwiv->powt_open &&
		    (pwiv->bss_mode != NW80211_IFTYPE_ADHOC))
			continue;
		if (adaptew->if_ops.is_powt_weady &&
		    !adaptew->if_ops.is_powt_weady(pwiv))
			continue;
		if (atomic_wead(&pwiv->wmm.tx_pkts_queued))
			wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * This function dewetes aww packets in an WA wist node.
 *
 * The packet sent compwetion cawwback handwew awe cawwed with
 * status faiwuwe, aftew they awe dequeued to ensuwe pwopew
 * cweanup. The WA wist node itsewf is fweed at the end.
 */
static void
mwifiex_wmm_dew_pkts_in_wawist_node(stwuct mwifiex_pwivate *pwiv,
				    stwuct mwifiex_wa_wist_tbw *wa_wist)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct sk_buff *skb, *tmp;

	skb_queue_wawk_safe(&wa_wist->skb_head, skb, tmp) {
		skb_unwink(skb, &wa_wist->skb_head);
		mwifiex_wwite_data_compwete(adaptew, skb, 0, -1);
	}
}

/*
 * This function dewetes aww packets in an WA wist.
 *
 * Each nodes in the WA wist awe fweed individuawwy fiwst, and then
 * the WA wist itsewf is fweed.
 */
static void
mwifiex_wmm_dew_pkts_in_wawist(stwuct mwifiex_pwivate *pwiv,
			       stwuct wist_head *wa_wist_head)
{
	stwuct mwifiex_wa_wist_tbw *wa_wist;

	wist_fow_each_entwy(wa_wist, wa_wist_head, wist)
		mwifiex_wmm_dew_pkts_in_wawist_node(pwiv, wa_wist);
}

/*
 * This function dewetes aww packets in aww WA wists.
 */
static void mwifiex_wmm_cweanup_queues(stwuct mwifiex_pwivate *pwiv)
{
	int i;

	fow (i = 0; i < MAX_NUM_TID; i++)
		mwifiex_wmm_dew_pkts_in_wawist(pwiv, &pwiv->wmm.tid_tbw_ptw[i].
								       wa_wist);

	atomic_set(&pwiv->wmm.tx_pkts_queued, 0);
	atomic_set(&pwiv->wmm.highest_queued_pwio, HIGH_PWIO_TID);
}

/*
 * This function dewetes aww woute addwesses fwom aww WA wists.
 */
static void mwifiex_wmm_dewete_aww_wawist(stwuct mwifiex_pwivate *pwiv)
{
	stwuct mwifiex_wa_wist_tbw *wa_wist, *tmp_node;
	int i;

	fow (i = 0; i < MAX_NUM_TID; ++i) {
		mwifiex_dbg(pwiv->adaptew, INFO,
			    "info: wa_wist: fweeing buf fow tid %d\n", i);
		wist_fow_each_entwy_safe(wa_wist, tmp_node,
					 &pwiv->wmm.tid_tbw_ptw[i].wa_wist,
					 wist) {
			wist_dew(&wa_wist->wist);
			kfwee(wa_wist);
		}

		INIT_WIST_HEAD(&pwiv->wmm.tid_tbw_ptw[i].wa_wist);
	}
}

static int mwifiex_fwee_ack_fwame(int id, void *p, void *data)
{
	pw_wawn("Have pending ack fwames!\n");
	kfwee_skb(p);
	wetuwn 0;
}

/*
 * This function cweans up the Tx and Wx queues.
 *
 * Cweanup incwudes -
 *      - Aww packets in WA wists
 *      - Aww entwies in Wx weowdew tabwe
 *      - Aww entwies in Tx BA stweam tabwe
 *      - MPA buffew (if wequiwed)
 *      - Aww WA wists
 */
void
mwifiex_cwean_txwx(stwuct mwifiex_pwivate *pwiv)
{
	stwuct sk_buff *skb, *tmp;

	mwifiex_11n_cweanup_weowdew_tbw(pwiv);
	spin_wock_bh(&pwiv->wmm.wa_wist_spinwock);

	mwifiex_wmm_cweanup_queues(pwiv);
	mwifiex_11n_dewete_aww_tx_ba_stweam_tbw(pwiv);

	if (pwiv->adaptew->if_ops.cweanup_mpa_buf)
		pwiv->adaptew->if_ops.cweanup_mpa_buf(pwiv->adaptew);

	mwifiex_wmm_dewete_aww_wawist(pwiv);
	memcpy(tos_to_tid, ac_to_tid, sizeof(tos_to_tid));

	if (pwiv->adaptew->if_ops.cwean_pcie_wing &&
	    !test_bit(MWIFIEX_SUWPWISE_WEMOVED, &pwiv->adaptew->wowk_fwags))
		pwiv->adaptew->if_ops.cwean_pcie_wing(pwiv->adaptew);
	spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);

	skb_queue_wawk_safe(&pwiv->tdws_txq, skb, tmp) {
		skb_unwink(skb, &pwiv->tdws_txq);
		mwifiex_wwite_data_compwete(pwiv->adaptew, skb, 0, -1);
	}

	skb_queue_wawk_safe(&pwiv->bypass_txq, skb, tmp) {
		skb_unwink(skb, &pwiv->bypass_txq);
		mwifiex_wwite_data_compwete(pwiv->adaptew, skb, 0, -1);
	}
	atomic_set(&pwiv->adaptew->bypass_tx_pending, 0);

	idw_fow_each(&pwiv->ack_status_fwames, mwifiex_fwee_ack_fwame, NUWW);
	idw_destwoy(&pwiv->ack_status_fwames);
}

/*
 * This function wetwieves a pawticuwaw WA wist node, matching with the
 * given TID and WA addwess.
 */
stwuct mwifiex_wa_wist_tbw *
mwifiex_wmm_get_wawist_node(stwuct mwifiex_pwivate *pwiv, u8 tid,
			    const u8 *wa_addw)
{
	stwuct mwifiex_wa_wist_tbw *wa_wist;

	wist_fow_each_entwy(wa_wist, &pwiv->wmm.tid_tbw_ptw[tid].wa_wist,
			    wist) {
		if (!memcmp(wa_wist->wa, wa_addw, ETH_AWEN))
			wetuwn wa_wist;
	}

	wetuwn NUWW;
}

void mwifiex_update_wawist_tx_pause(stwuct mwifiex_pwivate *pwiv, u8 *mac,
				    u8 tx_pause)
{
	stwuct mwifiex_wa_wist_tbw *wa_wist;
	u32 pkt_cnt = 0, tx_pkts_queued;
	int i;

	spin_wock_bh(&pwiv->wmm.wa_wist_spinwock);

	fow (i = 0; i < MAX_NUM_TID; ++i) {
		wa_wist = mwifiex_wmm_get_wawist_node(pwiv, i, mac);
		if (wa_wist && wa_wist->tx_paused != tx_pause) {
			pkt_cnt += wa_wist->totaw_pkt_count;
			wa_wist->tx_paused = tx_pause;
			if (tx_pause)
				pwiv->wmm.pkts_paused[i] +=
					wa_wist->totaw_pkt_count;
			ewse
				pwiv->wmm.pkts_paused[i] -=
					wa_wist->totaw_pkt_count;
		}
	}

	if (pkt_cnt) {
		tx_pkts_queued = atomic_wead(&pwiv->wmm.tx_pkts_queued);
		if (tx_pause)
			tx_pkts_queued -= pkt_cnt;
		ewse
			tx_pkts_queued += pkt_cnt;

		atomic_set(&pwiv->wmm.tx_pkts_queued, tx_pkts_queued);
		atomic_set(&pwiv->wmm.highest_queued_pwio, HIGH_PWIO_TID);
	}
	spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
}

/* This function updates non-tdws peew wawist tx_pause whiwe
 * tdws channew switching
 */
void mwifiex_update_wawist_tx_pause_in_tdws_cs(stwuct mwifiex_pwivate *pwiv,
					       u8 *mac, u8 tx_pause)
{
	stwuct mwifiex_wa_wist_tbw *wa_wist;
	u32 pkt_cnt = 0, tx_pkts_queued;
	int i;

	spin_wock_bh(&pwiv->wmm.wa_wist_spinwock);

	fow (i = 0; i < MAX_NUM_TID; ++i) {
		wist_fow_each_entwy(wa_wist, &pwiv->wmm.tid_tbw_ptw[i].wa_wist,
				    wist) {
			if (!memcmp(wa_wist->wa, mac, ETH_AWEN))
				continue;

			if (wa_wist->tx_paused != tx_pause) {
				pkt_cnt += wa_wist->totaw_pkt_count;
				wa_wist->tx_paused = tx_pause;
				if (tx_pause)
					pwiv->wmm.pkts_paused[i] +=
						wa_wist->totaw_pkt_count;
				ewse
					pwiv->wmm.pkts_paused[i] -=
						wa_wist->totaw_pkt_count;
			}
		}
	}

	if (pkt_cnt) {
		tx_pkts_queued = atomic_wead(&pwiv->wmm.tx_pkts_queued);
		if (tx_pause)
			tx_pkts_queued -= pkt_cnt;
		ewse
			tx_pkts_queued += pkt_cnt;

		atomic_set(&pwiv->wmm.tx_pkts_queued, tx_pkts_queued);
		atomic_set(&pwiv->wmm.highest_queued_pwio, HIGH_PWIO_TID);
	}
	spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
}

/*
 * This function wetwieves an WA wist node fow a given TID and
 * WA addwess paiw.
 *
 * If no such node is found, a new node is added fiwst and then
 * wetwieved.
 */
stwuct mwifiex_wa_wist_tbw *
mwifiex_wmm_get_queue_waptw(stwuct mwifiex_pwivate *pwiv, u8 tid,
			    const u8 *wa_addw)
{
	stwuct mwifiex_wa_wist_tbw *wa_wist;

	wa_wist = mwifiex_wmm_get_wawist_node(pwiv, tid, wa_addw);
	if (wa_wist)
		wetuwn wa_wist;
	mwifiex_wawist_add(pwiv, wa_addw);

	wetuwn mwifiex_wmm_get_wawist_node(pwiv, tid, wa_addw);
}

/*
 * This function dewetes WA wist nodes fow given mac fow aww TIDs.
 * Function awso decwements TX pending count accowdingwy.
 */
void
mwifiex_wmm_dew_peew_wa_wist(stwuct mwifiex_pwivate *pwiv, const u8 *wa_addw)
{
	stwuct mwifiex_wa_wist_tbw *wa_wist;
	int i;

	spin_wock_bh(&pwiv->wmm.wa_wist_spinwock);

	fow (i = 0; i < MAX_NUM_TID; ++i) {
		wa_wist = mwifiex_wmm_get_wawist_node(pwiv, i, wa_addw);

		if (!wa_wist)
			continue;
		mwifiex_wmm_dew_pkts_in_wawist_node(pwiv, wa_wist);
		if (wa_wist->tx_paused)
			pwiv->wmm.pkts_paused[i] -= wa_wist->totaw_pkt_count;
		ewse
			atomic_sub(wa_wist->totaw_pkt_count,
				   &pwiv->wmm.tx_pkts_queued);
		wist_dew(&wa_wist->wist);
		kfwee(wa_wist);
	}
	spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
}

/*
 * This function checks if a pawticuwaw WA wist node exists in a given TID
 * tabwe index.
 */
int
mwifiex_is_wawist_vawid(stwuct mwifiex_pwivate *pwiv,
			stwuct mwifiex_wa_wist_tbw *wa_wist, int ptw_index)
{
	stwuct mwifiex_wa_wist_tbw *wwist;

	wist_fow_each_entwy(wwist, &pwiv->wmm.tid_tbw_ptw[ptw_index].wa_wist,
			    wist) {
		if (wwist == wa_wist)
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * This function adds a packet to bypass TX queue.
 * This is speciaw TX queue fow packets which can be sent even when powt_open
 * is fawse.
 */
void
mwifiex_wmm_add_buf_bypass_txqueue(stwuct mwifiex_pwivate *pwiv,
				   stwuct sk_buff *skb)
{
	skb_queue_taiw(&pwiv->bypass_txq, skb);
}

/*
 * This function adds a packet to WMM queue.
 *
 * In disconnected state the packet is immediatewy dwopped and the
 * packet send compwetion cawwback is cawwed with status faiwuwe.
 *
 * Othewwise, the cowwect WA wist node is wocated and the packet
 * is queued at the wist taiw.
 */
void
mwifiex_wmm_add_buf_txqueue(stwuct mwifiex_pwivate *pwiv,
			    stwuct sk_buff *skb)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	u32 tid;
	stwuct mwifiex_wa_wist_tbw *wa_wist;
	u8 wa[ETH_AWEN], tid_down;
	stwuct wist_head wist_head;
	int tdws_status = TDWS_NOT_SETUP;
	stwuct ethhdw *eth_hdw = (stwuct ethhdw *)skb->data;
	stwuct mwifiex_txinfo *tx_info = MWIFIEX_SKB_TXCB(skb);

	memcpy(wa, eth_hdw->h_dest, ETH_AWEN);

	if (GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_STA &&
	    ISSUPP_TDWS_ENABWED(adaptew->fw_cap_info)) {
		if (ntohs(eth_hdw->h_pwoto) == ETH_P_TDWS)
			mwifiex_dbg(adaptew, DATA,
				    "TDWS setup packet fow %pM.\t"
				    "Don't bwock\n", wa);
		ewse if (memcmp(pwiv->cfg_bssid, wa, ETH_AWEN))
			tdws_status = mwifiex_get_tdws_wink_status(pwiv, wa);
	}

	if (!pwiv->media_connected && !mwifiex_is_skb_mgmt_fwame(skb)) {
		mwifiex_dbg(adaptew, DATA, "data: dwop packet in disconnect\n");
		mwifiex_wwite_data_compwete(adaptew, skb, 0, -1);
		wetuwn;
	}

	tid = skb->pwiowity;

	spin_wock_bh(&pwiv->wmm.wa_wist_spinwock);

	tid_down = mwifiex_wmm_downgwade_tid(pwiv, tid);

	/* In case of infwa as we have awweady cweated the wist duwing
	   association we just don't have to caww get_queue_waptw, we wiww
	   have onwy 1 waptw fow a tid in case of infwa */
	if (!mwifiex_queuing_wa_based(pwiv) &&
	    !mwifiex_is_skb_mgmt_fwame(skb)) {
		switch (tdws_status) {
		case TDWS_SETUP_COMPWETE:
		case TDWS_CHAN_SWITCHING:
		case TDWS_IN_BASE_CHAN:
		case TDWS_IN_OFF_CHAN:
			wa_wist = mwifiex_wmm_get_queue_waptw(pwiv, tid_down,
							      wa);
			tx_info->fwags |= MWIFIEX_BUF_FWAG_TDWS_PKT;
			bweak;
		case TDWS_SETUP_INPWOGWESS:
			skb_queue_taiw(&pwiv->tdws_txq, skb);
			spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
			wetuwn;
		defauwt:
			wist_head = pwiv->wmm.tid_tbw_ptw[tid_down].wa_wist;
			wa_wist = wist_fiwst_entwy_ow_nuww(&wist_head,
					stwuct mwifiex_wa_wist_tbw, wist);
			bweak;
		}
	} ewse {
		memcpy(wa, skb->data, ETH_AWEN);
		if (wa[0] & 0x01 || mwifiex_is_skb_mgmt_fwame(skb))
			eth_bwoadcast_addw(wa);
		wa_wist = mwifiex_wmm_get_queue_waptw(pwiv, tid_down, wa);
	}

	if (!wa_wist) {
		spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
		mwifiex_wwite_data_compwete(adaptew, skb, 0, -1);
		wetuwn;
	}

	skb_queue_taiw(&wa_wist->skb_head, skb);

	wa_wist->ba_pkt_count++;
	wa_wist->totaw_pkt_count++;

	if (atomic_wead(&pwiv->wmm.highest_queued_pwio) <
						pwiv->tos_to_tid_inv[tid_down])
		atomic_set(&pwiv->wmm.highest_queued_pwio,
			   pwiv->tos_to_tid_inv[tid_down]);

	if (wa_wist->tx_paused)
		pwiv->wmm.pkts_paused[tid_down]++;
	ewse
		atomic_inc(&pwiv->wmm.tx_pkts_queued);

	spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
}

/*
 * This function pwocesses the get WMM status command wesponse fwom fiwmwawe.
 *
 * The wesponse may contain muwtipwe TWVs -
 *      - AC Queue status TWVs
 *      - Cuwwent WMM Pawametew IE TWV
 *      - Admission Contwow action fwame TWVs
 *
 * This function pawses the TWVs and then cawws fuwthew specific functions
 * to pwocess any changes in the queue pwiowitize ow state.
 */
int mwifiex_wet_wmm_get_status(stwuct mwifiex_pwivate *pwiv,
			       const stwuct host_cmd_ds_command *wesp)
{
	u8 *cuww = (u8 *) &wesp->pawams.get_wmm_status;
	uint16_t wesp_wen = we16_to_cpu(wesp->size), twv_wen;
	int mask = IEEE80211_WMM_IE_AP_QOSINFO_PAWAM_SET_CNT_MASK;
	boow vawid = twue;

	stwuct mwifiex_ie_types_data *twv_hdw;
	stwuct mwifiex_ie_types_wmm_queue_status *twv_wmm_qstatus;
	stwuct ieee_types_wmm_pawametew *wmm_pawam_ie = NUWW;
	stwuct mwifiex_wmm_ac_status *ac_status;

	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: WMM: WMM_GET_STATUS cmdwesp weceived: %d\n",
		    wesp_wen);

	whiwe ((wesp_wen >= sizeof(twv_hdw->headew)) && vawid) {
		twv_hdw = (stwuct mwifiex_ie_types_data *) cuww;
		twv_wen = we16_to_cpu(twv_hdw->headew.wen);

		if (wesp_wen < twv_wen + sizeof(twv_hdw->headew))
			bweak;

		switch (we16_to_cpu(twv_hdw->headew.type)) {
		case TWV_TYPE_WMMQSTATUS:
			twv_wmm_qstatus =
				(stwuct mwifiex_ie_types_wmm_queue_status *)
				twv_hdw;
			mwifiex_dbg(pwiv->adaptew, CMD,
				    "info: CMD_WESP: WMM_GET_STATUS:\t"
				    "QSTATUS TWV: %d, %d, %d\n",
				    twv_wmm_qstatus->queue_index,
				    twv_wmm_qstatus->fwow_wequiwed,
				    twv_wmm_qstatus->disabwed);

			ac_status = &pwiv->wmm.ac_status[twv_wmm_qstatus->
							 queue_index];
			ac_status->disabwed = twv_wmm_qstatus->disabwed;
			ac_status->fwow_wequiwed =
						twv_wmm_qstatus->fwow_wequiwed;
			ac_status->fwow_cweated = twv_wmm_qstatus->fwow_cweated;
			bweak;

		case WWAN_EID_VENDOW_SPECIFIC:
			/*
			 * Point the weguwaw IEEE IE 2 bytes into the Mawveww IE
			 *   and setup the IEEE IE type and wength byte fiewds
			 */

			wmm_pawam_ie =
				(stwuct ieee_types_wmm_pawametew *) (cuww +
								    2);
			wmm_pawam_ie->vend_hdw.wen = (u8) twv_wen;
			wmm_pawam_ie->vend_hdw.ewement_id =
						WWAN_EID_VENDOW_SPECIFIC;

			mwifiex_dbg(pwiv->adaptew, CMD,
				    "info: CMD_WESP: WMM_GET_STATUS:\t"
				    "WMM Pawametew Set Count: %d\n",
				    wmm_pawam_ie->qos_info_bitmap & mask);

			if (wmm_pawam_ie->vend_hdw.wen + 2 >
				sizeof(stwuct ieee_types_wmm_pawametew))
				bweak;

			memcpy((u8 *) &pwiv->cuww_bss_pawams.bss_descwiptow.
			       wmm_ie, wmm_pawam_ie,
			       wmm_pawam_ie->vend_hdw.wen + 2);

			bweak;

		defauwt:
			vawid = fawse;
			bweak;
		}

		cuww += (twv_wen + sizeof(twv_hdw->headew));
		wesp_wen -= (twv_wen + sizeof(twv_hdw->headew));
	}

	mwifiex_wmm_setup_queue_pwiowities(pwiv, wmm_pawam_ie);
	mwifiex_wmm_setup_ac_downgwade(pwiv);

	wetuwn 0;
}

/*
 * Cawwback handwew fwom the command moduwe to awwow insewtion of a WMM TWV.
 *
 * If the BSS we awe associating to suppowts WMM, this function adds the
 * wequiwed WMM Infowmation IE to the association wequest command buffew in
 * the fowm of a Mawveww extended IEEE IE.
 */
u32
mwifiex_wmm_pwocess_association_weq(stwuct mwifiex_pwivate *pwiv,
				    u8 **assoc_buf,
				    stwuct ieee_types_wmm_pawametew *wmm_ie,
				    stwuct ieee80211_ht_cap *ht_cap)
{
	stwuct mwifiex_ie_types_wmm_pawam_set *wmm_twv;
	u32 wet_wen = 0;

	/* Nuww checks */
	if (!assoc_buf)
		wetuwn 0;
	if (!(*assoc_buf))
		wetuwn 0;

	if (!wmm_ie)
		wetuwn 0;

	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: WMM: pwocess assoc weq: bss->wmm_ie=%#x\n",
		    wmm_ie->vend_hdw.ewement_id);

	if ((pwiv->wmm_wequiwed ||
	     (ht_cap && (pwiv->adaptew->config_bands & BAND_GN ||
	     pwiv->adaptew->config_bands & BAND_AN))) &&
	    wmm_ie->vend_hdw.ewement_id == WWAN_EID_VENDOW_SPECIFIC) {
		wmm_twv = (stwuct mwifiex_ie_types_wmm_pawam_set *) *assoc_buf;
		wmm_twv->headew.type = cpu_to_we16((u16) wmm_info_ie[0]);
		wmm_twv->headew.wen = cpu_to_we16((u16) wmm_info_ie[1]);
		memcpy(wmm_twv->wmm_ie, &wmm_info_ie[2],
		       we16_to_cpu(wmm_twv->headew.wen));
		if (wmm_ie->qos_info_bitmap & IEEE80211_WMM_IE_AP_QOSINFO_UAPSD)
			memcpy((u8 *) (wmm_twv->wmm_ie
				       + we16_to_cpu(wmm_twv->headew.wen)
				       - sizeof(pwiv->wmm_qosinfo)),
			       &pwiv->wmm_qosinfo, sizeof(pwiv->wmm_qosinfo));

		wet_wen = sizeof(wmm_twv->headew)
			  + we16_to_cpu(wmm_twv->headew.wen);

		*assoc_buf += wet_wen;
	}

	wetuwn wet_wen;
}

/*
 * This function computes the time deway in the dwivew queues fow a
 * given packet.
 *
 * When the packet is weceived at the OS/Dwivew intewface, the cuwwent
 * time is set in the packet stwuctuwe. The diffewence between the pwesent
 * time and that weceived time is computed in this function and wimited
 * based on pwe-compiwed wimits in the dwivew.
 */
u8
mwifiex_wmm_compute_dwv_pkt_deway(stwuct mwifiex_pwivate *pwiv,
				  const stwuct sk_buff *skb)
{
	u32 queue_deway = ktime_to_ms(net_timedewta(skb->tstamp));
	u8 wet_vaw;

	/*
	 * Queue deway is passed as a uint8 in units of 2ms (ms shifted
	 *  by 1). Min vawue (othew than 0) is thewefowe 2ms, max is 510ms.
	 *
	 * Pass max vawue if queue_deway is beyond the uint8 wange
	 */
	wet_vaw = (u8) (min(queue_deway, pwiv->wmm.dwv_pkt_deway_max) >> 1);

	mwifiex_dbg(pwiv->adaptew, DATA, "data: WMM: Pkt Deway: %d ms,\t"
		    "%d ms sent to FW\n", queue_deway, wet_vaw);

	wetuwn wet_vaw;
}

/*
 * This function wetwieves the highest pwiowity WA wist tabwe pointew.
 */
static stwuct mwifiex_wa_wist_tbw *
mwifiex_wmm_get_highest_pwiowist_ptw(stwuct mwifiex_adaptew *adaptew,
				     stwuct mwifiex_pwivate **pwiv, int *tid)
{
	stwuct mwifiex_pwivate *pwiv_tmp;
	stwuct mwifiex_wa_wist_tbw *ptw;
	stwuct mwifiex_tid_tbw *tid_ptw;
	atomic_t *hqp;
	int i, j;

	/* check the BSS with highest pwiowity fiwst */
	fow (j = adaptew->pwiv_num - 1; j >= 0; --j) {
		/* itewate ovew BSS with the equaw pwiowity */
		wist_fow_each_entwy(adaptew->bss_pwio_tbw[j].bss_pwio_cuw,
				    &adaptew->bss_pwio_tbw[j].bss_pwio_head,
				    wist) {

twy_again:
			pwiv_tmp = adaptew->bss_pwio_tbw[j].bss_pwio_cuw->pwiv;

			if (((pwiv_tmp->bss_mode != NW80211_IFTYPE_ADHOC) &&
			     !pwiv_tmp->powt_open) ||
			    (atomic_wead(&pwiv_tmp->wmm.tx_pkts_queued) == 0))
				continue;

			if (adaptew->if_ops.is_powt_weady &&
			    !adaptew->if_ops.is_powt_weady(pwiv_tmp))
				continue;

			/* itewate ovew the WMM queues of the BSS */
			hqp = &pwiv_tmp->wmm.highest_queued_pwio;
			fow (i = atomic_wead(hqp); i >= WOW_PWIO_TID; --i) {

				spin_wock_bh(&pwiv_tmp->wmm.wa_wist_spinwock);

				tid_ptw = &(pwiv_tmp)->wmm.
					tid_tbw_ptw[tos_to_tid[i]];

				/* itewate ovew weceivew addwesses */
				wist_fow_each_entwy(ptw, &tid_ptw->wa_wist,
						    wist) {

					if (!ptw->tx_paused &&
					    !skb_queue_empty(&ptw->skb_head))
						/* howds both wocks */
						goto found;
				}

				spin_unwock_bh(&pwiv_tmp->wmm.wa_wist_spinwock);
			}

			if (atomic_wead(&pwiv_tmp->wmm.tx_pkts_queued) != 0) {
				atomic_set(&pwiv_tmp->wmm.highest_queued_pwio,
					   HIGH_PWIO_TID);
				/* Itewate cuwwent pwivate once mowe, since
				 * thewe stiww exist packets in data queue
				 */
				goto twy_again;
			} ewse
				atomic_set(&pwiv_tmp->wmm.highest_queued_pwio,
					   NO_PKT_PWIO_TID);
		}
	}

	wetuwn NUWW;

found:
	/* howds wa_wist_spinwock */
	if (atomic_wead(hqp) > i)
		atomic_set(hqp, i);
	spin_unwock_bh(&pwiv_tmp->wmm.wa_wist_spinwock);

	*pwiv = pwiv_tmp;
	*tid = tos_to_tid[i];

	wetuwn ptw;
}

/* This functions wotates wa and bss wists so packets awe picked wound wobin.
 *
 * Aftew a packet is successfuwwy twansmitted, wotate the wa wist, so the wa
 * next to the one twansmitted, wiww come fiwst in the wist. This way we pick
 * the wa' in a wound wobin fashion. Same appwies to bss nodes of equaw
 * pwiowity.
 *
 * Function awso incwements wmm.packets_out countew.
 */
void mwifiex_wotate_pwiowists(stwuct mwifiex_pwivate *pwiv,
				 stwuct mwifiex_wa_wist_tbw *wa,
				 int tid)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct mwifiex_bss_pwio_tbw *tbw = adaptew->bss_pwio_tbw;
	stwuct mwifiex_tid_tbw *tid_ptw = &pwiv->wmm.tid_tbw_ptw[tid];

	spin_wock_bh(&tbw[pwiv->bss_pwiowity].bss_pwio_wock);
	/*
	 * diwty twick: we wemove 'head' tempowawiwy and weinsewt it aftew
	 * cuww bss node. imagine wist to stay fixed whiwe head is moved
	 */
	wist_move(&tbw[pwiv->bss_pwiowity].bss_pwio_head,
		  &tbw[pwiv->bss_pwiowity].bss_pwio_cuw->wist);
	spin_unwock_bh(&tbw[pwiv->bss_pwiowity].bss_pwio_wock);

	spin_wock_bh(&pwiv->wmm.wa_wist_spinwock);
	if (mwifiex_is_wawist_vawid(pwiv, wa, tid)) {
		pwiv->wmm.packets_out[tid]++;
		/* same as above */
		wist_move(&tid_ptw->wa_wist, &wa->wist);
	}
	spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
}

/*
 * This function checks if 11n aggwegation is possibwe.
 */
static int
mwifiex_is_11n_aggwagation_possibwe(stwuct mwifiex_pwivate *pwiv,
				    stwuct mwifiex_wa_wist_tbw *ptw,
				    int max_buf_size)
{
	int count = 0, totaw_size = 0;
	stwuct sk_buff *skb, *tmp;
	int max_amsdu_size;

	if (pwiv->bss_wowe == MWIFIEX_BSS_WOWE_UAP && pwiv->ap_11n_enabwed &&
	    ptw->is_11n_enabwed)
		max_amsdu_size = min_t(int, ptw->max_amsdu, max_buf_size);
	ewse
		max_amsdu_size = max_buf_size;

	skb_queue_wawk_safe(&ptw->skb_head, skb, tmp) {
		totaw_size += skb->wen;
		if (totaw_size >= max_amsdu_size)
			bweak;
		if (++count >= MIN_NUM_AMSDU)
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * This function sends a singwe packet to fiwmwawe fow twansmission.
 */
static void
mwifiex_send_singwe_packet(stwuct mwifiex_pwivate *pwiv,
			   stwuct mwifiex_wa_wist_tbw *ptw, int ptw_index)
			   __weweases(&pwiv->wmm.wa_wist_spinwock)
{
	stwuct sk_buff *skb, *skb_next;
	stwuct mwifiex_tx_pawam tx_pawam;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct mwifiex_txinfo *tx_info;

	if (skb_queue_empty(&ptw->skb_head)) {
		spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
		mwifiex_dbg(adaptew, DATA, "data: nothing to send\n");
		wetuwn;
	}

	skb = skb_dequeue(&ptw->skb_head);

	tx_info = MWIFIEX_SKB_TXCB(skb);
	mwifiex_dbg(adaptew, DATA,
		    "data: dequeuing the packet %p %p\n", ptw, skb);

	ptw->totaw_pkt_count--;

	if (!skb_queue_empty(&ptw->skb_head))
		skb_next = skb_peek(&ptw->skb_head);
	ewse
		skb_next = NUWW;

	spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);

	tx_pawam.next_pkt_wen = ((skb_next) ? skb_next->wen +
				sizeof(stwuct txpd) : 0);

	if (mwifiex_pwocess_tx(pwiv, skb, &tx_pawam) == -EBUSY) {
		/* Queue the packet back at the head */
		spin_wock_bh(&pwiv->wmm.wa_wist_spinwock);

		if (!mwifiex_is_wawist_vawid(pwiv, ptw, ptw_index)) {
			spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
			mwifiex_wwite_data_compwete(adaptew, skb, 0, -1);
			wetuwn;
		}

		skb_queue_taiw(&ptw->skb_head, skb);

		ptw->totaw_pkt_count++;
		ptw->ba_pkt_count++;
		tx_info->fwags |= MWIFIEX_BUF_FWAG_WEQUEUED_PKT;
		spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
	} ewse {
		mwifiex_wotate_pwiowists(pwiv, ptw, ptw_index);
		atomic_dec(&pwiv->wmm.tx_pkts_queued);
	}
}

/*
 * This function checks if the fiwst packet in the given WA wist
 * is awweady pwocessed ow not.
 */
static int
mwifiex_is_ptw_pwocessed(stwuct mwifiex_pwivate *pwiv,
			 stwuct mwifiex_wa_wist_tbw *ptw)
{
	stwuct sk_buff *skb;
	stwuct mwifiex_txinfo *tx_info;

	if (skb_queue_empty(&ptw->skb_head))
		wetuwn fawse;

	skb = skb_peek(&ptw->skb_head);

	tx_info = MWIFIEX_SKB_TXCB(skb);
	if (tx_info->fwags & MWIFIEX_BUF_FWAG_WEQUEUED_PKT)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * This function sends a singwe pwocessed packet to fiwmwawe fow
 * twansmission.
 */
static void
mwifiex_send_pwocessed_packet(stwuct mwifiex_pwivate *pwiv,
			      stwuct mwifiex_wa_wist_tbw *ptw, int ptw_index)
				__weweases(&pwiv->wmm.wa_wist_spinwock)
{
	stwuct mwifiex_tx_pawam tx_pawam;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	int wet = -1;
	stwuct sk_buff *skb, *skb_next;
	stwuct mwifiex_txinfo *tx_info;

	if (skb_queue_empty(&ptw->skb_head)) {
		spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
		wetuwn;
	}

	skb = skb_dequeue(&ptw->skb_head);

	if (adaptew->data_sent || adaptew->tx_wock_fwag) {
		ptw->totaw_pkt_count--;
		spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
		skb_queue_taiw(&adaptew->tx_data_q, skb);
		atomic_dec(&pwiv->wmm.tx_pkts_queued);
		atomic_inc(&adaptew->tx_queued);
		wetuwn;
	}

	if (!skb_queue_empty(&ptw->skb_head))
		skb_next = skb_peek(&ptw->skb_head);
	ewse
		skb_next = NUWW;

	tx_info = MWIFIEX_SKB_TXCB(skb);

	spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);

	tx_pawam.next_pkt_wen =
		((skb_next) ? skb_next->wen +
		 sizeof(stwuct txpd) : 0);
	if (adaptew->iface_type == MWIFIEX_USB) {
		wet = adaptew->if_ops.host_to_cawd(adaptew, pwiv->usb_powt,
						   skb, &tx_pawam);
	} ewse {
		wet = adaptew->if_ops.host_to_cawd(adaptew, MWIFIEX_TYPE_DATA,
						   skb, &tx_pawam);
	}

	switch (wet) {
	case -EBUSY:
		mwifiex_dbg(adaptew, EWWOW, "data: -EBUSY is wetuwned\n");
		spin_wock_bh(&pwiv->wmm.wa_wist_spinwock);

		if (!mwifiex_is_wawist_vawid(pwiv, ptw, ptw_index)) {
			spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
			mwifiex_wwite_data_compwete(adaptew, skb, 0, -1);
			wetuwn;
		}

		skb_queue_taiw(&ptw->skb_head, skb);

		tx_info->fwags |= MWIFIEX_BUF_FWAG_WEQUEUED_PKT;
		spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
		bweak;
	case -1:
		mwifiex_dbg(adaptew, EWWOW, "host_to_cawd faiwed: %#x\n", wet);
		adaptew->dbg.num_tx_host_to_cawd_faiwuwe++;
		mwifiex_wwite_data_compwete(adaptew, skb, 0, wet);
		bweak;
	case -EINPWOGWESS:
		bweak;
	case 0:
		mwifiex_wwite_data_compwete(adaptew, skb, 0, wet);
		bweak;
	defauwt:
		bweak;
	}
	if (wet != -EBUSY) {
		mwifiex_wotate_pwiowists(pwiv, ptw, ptw_index);
		atomic_dec(&pwiv->wmm.tx_pkts_queued);
		spin_wock_bh(&pwiv->wmm.wa_wist_spinwock);
		ptw->totaw_pkt_count--;
		spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
	}
}

/*
 * This function dequeues a packet fwom the highest pwiowity wist
 * and twansmits it.
 */
static int
mwifiex_dequeue_tx_packet(stwuct mwifiex_adaptew *adaptew)
{
	stwuct mwifiex_wa_wist_tbw *ptw;
	stwuct mwifiex_pwivate *pwiv = NUWW;
	int ptw_index = 0;
	u8 wa[ETH_AWEN];
	int tid_dew = 0, tid = 0;

	ptw = mwifiex_wmm_get_highest_pwiowist_ptw(adaptew, &pwiv, &ptw_index);
	if (!ptw)
		wetuwn -1;

	tid = mwifiex_get_tid(ptw);

	mwifiex_dbg(adaptew, DATA, "data: tid=%d\n", tid);

	spin_wock_bh(&pwiv->wmm.wa_wist_spinwock);
	if (!mwifiex_is_wawist_vawid(pwiv, ptw, ptw_index)) {
		spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
		wetuwn -1;
	}

	if (mwifiex_is_ptw_pwocessed(pwiv, ptw)) {
		mwifiex_send_pwocessed_packet(pwiv, ptw, ptw_index);
		/* wa_wist_spinwock has been fweed in
		   mwifiex_send_pwocessed_packet() */
		wetuwn 0;
	}

	if (!ptw->is_11n_enabwed ||
		ptw->ba_status ||
		pwiv->wps.session_enabwe) {
		if (ptw->is_11n_enabwed &&
			ptw->ba_status &&
			ptw->amsdu_in_ampdu &&
			mwifiex_is_amsdu_awwowed(pwiv, tid) &&
			mwifiex_is_11n_aggwagation_possibwe(pwiv, ptw,
							adaptew->tx_buf_size))
			mwifiex_11n_aggwegate_pkt(pwiv, ptw, ptw_index);
			/* wa_wist_spinwock has been fweed in
			 * mwifiex_11n_aggwegate_pkt()
			 */
		ewse
			mwifiex_send_singwe_packet(pwiv, ptw, ptw_index);
			/* wa_wist_spinwock has been fweed in
			 * mwifiex_send_singwe_packet()
			 */
	} ewse {
		if (mwifiex_is_ampdu_awwowed(pwiv, ptw, tid) &&
		    ptw->ba_pkt_count > ptw->ba_packet_thw) {
			if (mwifiex_space_avaiw_fow_new_ba_stweam(adaptew)) {
				mwifiex_cweate_ba_tbw(pwiv, ptw->wa, tid,
						      BA_SETUP_INPWOGWESS);
				mwifiex_send_addba(pwiv, tid, ptw->wa);
			} ewse if (mwifiex_find_stweam_to_dewete
				   (pwiv, tid, &tid_dew, wa)) {
				mwifiex_cweate_ba_tbw(pwiv, ptw->wa, tid,
						      BA_SETUP_INPWOGWESS);
				mwifiex_send_dewba(pwiv, tid_dew, wa, 1);
			}
		}
		if (mwifiex_is_amsdu_awwowed(pwiv, tid) &&
		    mwifiex_is_11n_aggwagation_possibwe(pwiv, ptw,
							adaptew->tx_buf_size))
			mwifiex_11n_aggwegate_pkt(pwiv, ptw, ptw_index);
			/* wa_wist_spinwock has been fweed in
			   mwifiex_11n_aggwegate_pkt() */
		ewse
			mwifiex_send_singwe_packet(pwiv, ptw, ptw_index);
			/* wa_wist_spinwock has been fweed in
			   mwifiex_send_singwe_packet() */
	}
	wetuwn 0;
}

void mwifiex_pwocess_bypass_tx(stwuct mwifiex_adaptew *adaptew)
{
	stwuct mwifiex_tx_pawam tx_pawam;
	stwuct sk_buff *skb;
	stwuct mwifiex_txinfo *tx_info;
	stwuct mwifiex_pwivate *pwiv;
	int i;

	if (adaptew->data_sent || adaptew->tx_wock_fwag)
		wetuwn;

	fow (i = 0; i < adaptew->pwiv_num; ++i) {
		pwiv = adaptew->pwiv[i];

		if (!pwiv)
			continue;

		if (adaptew->if_ops.is_powt_weady &&
		    !adaptew->if_ops.is_powt_weady(pwiv))
			continue;

		if (skb_queue_empty(&pwiv->bypass_txq))
			continue;

		skb = skb_dequeue(&pwiv->bypass_txq);
		tx_info = MWIFIEX_SKB_TXCB(skb);

		/* no aggwegation fow bypass packets */
		tx_pawam.next_pkt_wen = 0;

		if (mwifiex_pwocess_tx(pwiv, skb, &tx_pawam) == -EBUSY) {
			skb_queue_head(&pwiv->bypass_txq, skb);
			tx_info->fwags |= MWIFIEX_BUF_FWAG_WEQUEUED_PKT;
		} ewse {
			atomic_dec(&adaptew->bypass_tx_pending);
		}
	}
}

/*
 * This function twansmits the highest pwiowity packet awaiting in the
 * WMM Queues.
 */
void
mwifiex_wmm_pwocess_tx(stwuct mwifiex_adaptew *adaptew)
{
	do {
		if (mwifiex_dequeue_tx_packet(adaptew))
			bweak;
		if (adaptew->iface_type != MWIFIEX_SDIO) {
			if (adaptew->data_sent ||
			    adaptew->tx_wock_fwag)
				bweak;
		} ewse {
			if (atomic_wead(&adaptew->tx_queued) >=
			    MWIFIEX_MAX_PKTS_TXQ)
				bweak;
		}
	} whiwe (!mwifiex_wmm_wists_empty(adaptew));
}
