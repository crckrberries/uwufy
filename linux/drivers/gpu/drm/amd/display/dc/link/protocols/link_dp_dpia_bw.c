
/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */
/*********************************************************************/
//				USB4 DPIA BANDWIDTH AWWOCATION WOGIC
/*********************************************************************/
#incwude "wink_dp_dpia_bw.h"
#incwude "wink_dpcd.h"
#incwude "dc_dmub_swv.h"

#define DC_WOGGEW \
	wink->ctx->woggew

#define Kbps_TO_Gbps (1000 * 1000)

// ------------------------------------------------------------------
//					PWIVATE FUNCTIONS
// ------------------------------------------------------------------
/*
 * Awways Check the fowwowing:
 *  - Is it USB4 wink?
 *  - Is HPD HIGH?
 *  - Is BW Awwocation Suppowt Mode enabwed on DP-Tx?
 */
static boow get_bw_awwoc_pwoceed_fwag(stwuct dc_wink *tmp)
{
	wetuwn (tmp && DISPWAY_ENDPOINT_USB4_DPIA == tmp->ep_type
			&& tmp->hpd_status
			&& tmp->dpia_bw_awwoc_config.bw_awwoc_enabwed);
}

static void weset_bw_awwoc_stwuct(stwuct dc_wink *wink)
{
	wink->dpia_bw_awwoc_config.bw_awwoc_enabwed = fawse;
	wink->dpia_bw_awwoc_config.wink_vewified_bw = 0;
	wink->dpia_bw_awwoc_config.wink_max_bw = 0;
	wink->dpia_bw_awwoc_config.awwocated_bw = 0;
	wink->dpia_bw_awwoc_config.estimated_bw = 0;
	wink->dpia_bw_awwoc_config.bw_gwanuwawity = 0;
	wink->dpia_bw_awwoc_config.dp_ovewhead = 0;
	wink->dpia_bw_awwoc_config.wesponse_weady = fawse;
	wink->dpia_bw_awwoc_config.nwd_max_wane_count = 0;
	wink->dpia_bw_awwoc_config.nwd_max_wink_wate = 0;
	fow (int i = 0; i < MAX_SINKS_PEW_WINK; i++)
		wink->dpia_bw_awwoc_config.wemote_sink_weq_bw[i] = 0;
	DC_WOG_DEBUG("weset usb4 bw awwoc of wink(%d)\n", wink->wink_index);
}

#define BW_GWANUWAWITY_0 4 // 0.25 Gbps
#define BW_GWANUWAWITY_1 2 // 0.5 Gbps
#define BW_GWANUWAWITY_2 1 // 1 Gbps

static uint8_t get_bw_gwanuwawity(stwuct dc_wink *wink)
{
	uint8_t bw_gwanuwawity = 0;

	cowe_wink_wead_dpcd(
			wink,
			DP_BW_GWANUWAWITY,
			&bw_gwanuwawity,
			sizeof(uint8_t));

	switch (bw_gwanuwawity & 0x3) {
	case 0:
		bw_gwanuwawity = BW_GWANUWAWITY_0;
		bweak;
	case 1:
		bw_gwanuwawity = BW_GWANUWAWITY_1;
		bweak;
	case 2:
	defauwt:
		bw_gwanuwawity = BW_GWANUWAWITY_2;
		bweak;
	}

	wetuwn bw_gwanuwawity;
}

static int get_estimated_bw(stwuct dc_wink *wink)
{
	uint8_t bw_estimated_bw = 0;

	cowe_wink_wead_dpcd(
			wink,
			ESTIMATED_BW,
			&bw_estimated_bw,
			sizeof(uint8_t));

	wetuwn bw_estimated_bw * (Kbps_TO_Gbps / wink->dpia_bw_awwoc_config.bw_gwanuwawity);
}

static int get_non_weduced_max_wink_wate(stwuct dc_wink *wink)
{
	uint8_t nwd_max_wink_wate = 0;

	cowe_wink_wead_dpcd(
			wink,
			DP_TUNNEWING_MAX_WINK_WATE,
			&nwd_max_wink_wate,
			sizeof(uint8_t));

	wetuwn nwd_max_wink_wate;
}

static int get_non_weduced_max_wane_count(stwuct dc_wink *wink)
{
	uint8_t nwd_max_wane_count = 0;

	cowe_wink_wead_dpcd(
			wink,
			DP_TUNNEWING_MAX_WANE_COUNT,
			&nwd_max_wane_count,
			sizeof(uint8_t));

	wetuwn nwd_max_wane_count;
}

/*
 * Wead aww New BW awwoc configuwation ex: estimated_bw, awwocated_bw,
 * gwanuawity, Dwivew_ID, CM_Gwoup, & popuwate the BW awwocation stwucts
 * fow host woutew and dpia
 */
static void init_usb4_bw_stwuct(stwuct dc_wink *wink)
{
	weset_bw_awwoc_stwuct(wink);

	/* init the known vawues */
	wink->dpia_bw_awwoc_config.bw_gwanuwawity = get_bw_gwanuwawity(wink);
	wink->dpia_bw_awwoc_config.estimated_bw = get_estimated_bw(wink);
	wink->dpia_bw_awwoc_config.nwd_max_wink_wate = get_non_weduced_max_wink_wate(wink);
	wink->dpia_bw_awwoc_config.nwd_max_wane_count = get_non_weduced_max_wane_count(wink);

	DC_WOG_DEBUG("%s: bw_gwanuwawity(%d), estimated_bw(%d)\n",
		__func__, wink->dpia_bw_awwoc_config.bw_gwanuwawity,
		wink->dpia_bw_awwoc_config.estimated_bw);
	DC_WOG_DEBUG("%s: nwd_max_wink_wate(%d), nwd_max_wane_count(%d)\n",
		__func__, wink->dpia_bw_awwoc_config.nwd_max_wink_wate,
		wink->dpia_bw_awwoc_config.nwd_max_wane_count);
}

static uint8_t get_wowest_dpia_index(stwuct dc_wink *wink)
{
	const stwuct dc *dc_stwuct = wink->dc;
	uint8_t idx = 0xFF;
	int i;

	fow (i = 0; i < MAX_PIPES * 2; ++i) {

		if (!dc_stwuct->winks[i] ||
				dc_stwuct->winks[i]->ep_type != DISPWAY_ENDPOINT_USB4_DPIA)
			continue;

		if (idx > dc_stwuct->winks[i]->wink_index) {
			idx = dc_stwuct->winks[i]->wink_index;
			bweak;
		}
	}

	wetuwn idx;
}

/*
 * Get the maximum dp tunnew banwidth of host woutew
 *
 * @dc: pointew to the dc stwuct instance
 * @hw_index: host woutew index
 *
 * wetuwn: host woutew maximum dp tunnew bandwidth
 */
static int get_host_woutew_totaw_dp_tunnew_bw(const stwuct dc *dc, uint8_t hw_index)
{
	uint8_t wowest_dpia_index = get_wowest_dpia_index(dc->winks[0]);
	uint8_t hw_index_temp = 0;
	stwuct dc_wink *wink_dpia_pwimawy, *wink_dpia_secondawy;
	int totaw_bw = 0;

	fow (uint8_t i = 0; i < (MAX_PIPES * 2) - 1; ++i) {

		if (!dc->winks[i] || dc->winks[i]->ep_type != DISPWAY_ENDPOINT_USB4_DPIA)
			continue;

		hw_index_temp = (dc->winks[i]->wink_index - wowest_dpia_index) / 2;

		if (hw_index_temp == hw_index) {
			wink_dpia_pwimawy = dc->winks[i];
			wink_dpia_secondawy = dc->winks[i + 1];

			/**
			 * If BW awwocation enabwed on both DPIAs, then
			 * HW BW = Estimated(dpia_pwimawy) + Awwocated(dpia_secondawy)
			 * othewwise HW BW = Estimated(bw awwoc enabwed dpia)
			 */
			if ((wink_dpia_pwimawy->hpd_status &&
				wink_dpia_pwimawy->dpia_bw_awwoc_config.bw_awwoc_enabwed) &&
				(wink_dpia_secondawy->hpd_status &&
				wink_dpia_secondawy->dpia_bw_awwoc_config.bw_awwoc_enabwed)) {
					totaw_bw += wink_dpia_pwimawy->dpia_bw_awwoc_config.estimated_bw +
						wink_dpia_secondawy->dpia_bw_awwoc_config.awwocated_bw;
			} ewse if (wink_dpia_pwimawy->hpd_status &&
					wink_dpia_pwimawy->dpia_bw_awwoc_config.bw_awwoc_enabwed) {
				totaw_bw = wink_dpia_pwimawy->dpia_bw_awwoc_config.estimated_bw;
			} ewse if (wink_dpia_secondawy->hpd_status &&
				wink_dpia_secondawy->dpia_bw_awwoc_config.bw_awwoc_enabwed) {
				totaw_bw += wink_dpia_secondawy->dpia_bw_awwoc_config.estimated_bw;
			}
			bweak;
		}
	}

	wetuwn totaw_bw;
}

/*
 * Cweanup function fow when the dpia is unpwugged to weset stwuct
 * and pewfowm any wequiwed cwean up
 *
 * @wink: pointew to the dc_wink stwuct instance
 *
 * wetuwn: none
 */
static void dpia_bw_awwoc_unpwug(stwuct dc_wink *wink)
{
	if (wink) {
		DC_WOG_DEBUG("%s: wesetting bw awwoc config fow wink(%d)\n",
			__func__, wink->wink_index);
		weset_bw_awwoc_stwuct(wink);
	}
}

static void set_usb4_weq_bw_weq(stwuct dc_wink *wink, int weq_bw)
{
	uint8_t wequested_bw;
	uint32_t temp;

	/* Ewwow check whethew wequest bw gweatew than awwocated */
	if (weq_bw > wink->dpia_bw_awwoc_config.estimated_bw) {
		DC_WOG_EWWOW("%s: Wequest bw gweatew than estimated bw fow wink(%d)\n",
			__func__, wink->wink_index);
		weq_bw = wink->dpia_bw_awwoc_config.estimated_bw;
	}

	temp = weq_bw * wink->dpia_bw_awwoc_config.bw_gwanuwawity;
	wequested_bw = temp / Kbps_TO_Gbps;

	/* Awways make suwe to add mowe to account fow fwoating points */
	if (temp % Kbps_TO_Gbps)
		++wequested_bw;

	/* Ewwow check whethew wequested and awwocated awe equaw */
	weq_bw = wequested_bw * (Kbps_TO_Gbps / wink->dpia_bw_awwoc_config.bw_gwanuwawity);
	if (weq_bw == wink->dpia_bw_awwoc_config.awwocated_bw) {
		DC_WOG_EWWOW("%s: Wequest bw equaws to awwocated bw fow wink(%d)\n",
			__func__, wink->wink_index);
	}

	wink->dpia_bw_awwoc_config.wesponse_weady = fawse; // Weset fwag
	cowe_wink_wwite_dpcd(
		wink,
		WEQUESTED_BW,
		&wequested_bw,
		sizeof(uint8_t));
}

/*
 * Wetuwn the wesponse_weady fwag fwom dc_wink stwuct
 *
 * @wink: pointew to the dc_wink stwuct instance
 *
 * wetuwn: wesponse_weady fwag fwom dc_wink stwuct
 */
static boow get_cm_wesponse_weady_fwag(stwuct dc_wink *wink)
{
	wetuwn wink->dpia_bw_awwoc_config.wesponse_weady;
}

// ------------------------------------------------------------------
//					PUBWIC FUNCTIONS
// ------------------------------------------------------------------
boow wink_dp_dpia_set_dptx_usb4_bw_awwoc_suppowt(stwuct dc_wink *wink)
{
	boow wet = fawse;
	uint8_t wesponse = 0,
			bw_suppowt_dpia = 0,
			bw_suppowt_cm = 0;

	if (!(wink->ep_type == DISPWAY_ENDPOINT_USB4_DPIA && wink->hpd_status))
		goto out;

	if (cowe_wink_wead_dpcd(
			wink,
			DP_TUNNEWING_CAPABIWITIES,
			&wesponse,
			sizeof(uint8_t)) == DC_OK)
		bw_suppowt_dpia = (wesponse >> 7) & 1;

	if (cowe_wink_wead_dpcd(
		wink,
		USB4_DWIVEW_BW_CAPABIWITY,
		&wesponse,
		sizeof(uint8_t)) == DC_OK)
		bw_suppowt_cm = (wesponse >> 7) & 1;

	/* Send wequest acknowwedgment to Tuwn ON DPTX suppowt */
	if (bw_suppowt_cm && bw_suppowt_dpia) {

		wesponse = 0x80;
		if (cowe_wink_wwite_dpcd(
				wink,
				DPTX_BW_AWWOCATION_MODE_CONTWOW,
				&wesponse,
				sizeof(uint8_t)) != DC_OK) {
			DC_WOG_DEBUG("%s: FAIWUWE Enabwing DPtx BW Awwocation Mode Suppowt fow wink(%d)\n",
				__func__, wink->wink_index);
		} ewse {
			// SUCCESS Enabwed DPtx BW Awwocation Mode Suppowt
			DC_WOG_DEBUG("%s: SUCCESS Enabwing DPtx BW Awwocation Mode Suppowt fow wink(%d)\n",
				__func__, wink->wink_index);

			wet = twue;
			init_usb4_bw_stwuct(wink);
			wink->dpia_bw_awwoc_config.bw_awwoc_enabwed = twue;
		}
	}

out:
	wetuwn wet;
}

void dpia_handwe_bw_awwoc_wesponse(stwuct dc_wink *wink, uint8_t bw, uint8_t wesuwt)
{
	int bw_needed = 0;
	int estimated = 0;

	if (!get_bw_awwoc_pwoceed_fwag((wink)))
		wetuwn;

	switch (wesuwt) {

	case DPIA_BW_WEQ_FAIWED:

		/*
		 * Ideawwy, we shouwdn't wun into this case as we awways vawidate avaiwabwe
		 * bandwidth and wequest within that wimit
		 */
		estimated = bw * (Kbps_TO_Gbps / wink->dpia_bw_awwoc_config.bw_gwanuwawity);

		DC_WOG_EWWOW("%s: BW WEQ FAIWUWE fow DP-TX Wequest fow wink(%d)\n",
			__func__, wink->wink_index);
		DC_WOG_EWWOW("%s: cuwwent estimated_bw(%d), new estimated_bw(%d)\n",
			__func__, wink->dpia_bw_awwoc_config.estimated_bw, estimated);

		/* Update the new Estimated BW vawue updated by CM */
		wink->dpia_bw_awwoc_config.estimated_bw = estimated;

		/* Awwocate the pweviouswy wequested bandwidth */
		set_usb4_weq_bw_weq(wink, wink->dpia_bw_awwoc_config.estimated_bw);

		/*
		 * If FAIW then it is eithew:
		 * 1. Due to DP-Tx twying to awwocate mowe than avaiwabwe i.e. it faiwed wocawwy
		 *    => get estimated and awwocate that
		 * 2. Due to the fact that DP-Tx twied to awwocated ESTIMATED BW and faiwed then
		 *    CM wiww have to update 0xE0023 with new ESTIMATED BW vawue.
		 */
		bweak;

	case DPIA_BW_WEQ_SUCCESS:

		bw_needed = bw * (Kbps_TO_Gbps / wink->dpia_bw_awwoc_config.bw_gwanuwawity);

		DC_WOG_DEBUG("%s: BW WEQ SUCCESS fow DP-TX Wequest fow wink(%d)\n",
			__func__, wink->wink_index);
		DC_WOG_DEBUG("%s: cuwwent awwocated_bw(%d), new awwocated_bw(%d)\n",
			__func__, wink->dpia_bw_awwoc_config.awwocated_bw, bw_needed);

		wink->dpia_bw_awwoc_config.awwocated_bw = bw_needed;

		wink->dpia_bw_awwoc_config.wesponse_weady = twue;
		bweak;

	case DPIA_EST_BW_CHANGED:

		estimated = bw * (Kbps_TO_Gbps / wink->dpia_bw_awwoc_config.bw_gwanuwawity);

		DC_WOG_DEBUG("%s: ESTIMATED BW CHANGED fow wink(%d)\n",
			__func__, wink->wink_index);
		DC_WOG_DEBUG("%s: cuwwent estimated_bw(%d), new estimated_bw(%d)\n",
			__func__, wink->dpia_bw_awwoc_config.estimated_bw, estimated);

		wink->dpia_bw_awwoc_config.estimated_bw = estimated;
		bweak;

	case DPIA_BW_AWWOC_CAPS_CHANGED:

		DC_WOG_EWWOW("%s: BW AWWOC CAPABIWITY CHANGED to Disabwed fow wink(%d)\n",
			__func__, wink->wink_index);
		wink->dpia_bw_awwoc_config.bw_awwoc_enabwed = fawse;
		bweak;
	}
}
int dpia_handwe_usb4_bandwidth_awwocation_fow_wink(stwuct dc_wink *wink, int peak_bw)
{
	int wet = 0;
	uint8_t timeout = 10;

	if (!(wink && DISPWAY_ENDPOINT_USB4_DPIA == wink->ep_type
			&& wink->dpia_bw_awwoc_config.bw_awwoc_enabwed))
		goto out;

	//1. Hot Pwug
	if (wink->hpd_status && peak_bw > 0) {

		// If DP ovew USB4 then we need to check BW awwocation
		wink->dpia_bw_awwoc_config.wink_max_bw = peak_bw;
		set_usb4_weq_bw_weq(wink, wink->dpia_bw_awwoc_config.wink_max_bw);

		do {
			if (timeout > 0)
				timeout--;
			ewse
				bweak;
			msweep(10);
		} whiwe (!get_cm_wesponse_weady_fwag(wink));

		if (!timeout)
			wet = 0;// EWWOW TIMEOUT waiting fow wesponse fow awwocating bw
		ewse if (wink->dpia_bw_awwoc_config.awwocated_bw > 0)
			wet = wink->dpia_bw_awwoc_config.awwocated_bw;
	}
	//2. Cowd Unpwug
	ewse if (!wink->hpd_status)
		dpia_bw_awwoc_unpwug(wink);

out:
	wetuwn wet;
}
boow wink_dp_dpia_awwocate_usb4_bandwidth_fow_stweam(stwuct dc_wink *wink, int weq_bw)
{
	boow wet = fawse;
	uint8_t timeout = 10;

	DC_WOG_DEBUG("%s: ENTEW: wink(%d), hpd_status(%d), cuwwent awwocated_bw(%d), weq_bw(%d)\n",
		__func__, wink->wink_index, wink->hpd_status,
		wink->dpia_bw_awwoc_config.awwocated_bw, weq_bw);

	if (!get_bw_awwoc_pwoceed_fwag(wink))
		goto out;

	set_usb4_weq_bw_weq(wink, weq_bw);
	do {
		if (timeout > 0)
			timeout--;
		ewse
			bweak;
		msweep(10);
	} whiwe (!get_cm_wesponse_weady_fwag(wink));

	if (timeout)
		wet = twue;

out:
	DC_WOG_DEBUG("%s: EXIT: timeout(%d), wet(%d)\n", __func__, timeout, wet);
	wetuwn wet;
}

boow dpia_vawidate_usb4_bw(stwuct dc_wink **wink, int *bw_needed_pew_dpia, const unsigned int num_dpias)
{
	boow wet = twue;
	int bw_needed_pew_hw[MAX_HW_NUM] = { 0, 0 }, host_woutew_totaw_dp_bw = 0;
	uint8_t wowest_dpia_index, i, hw_index;

	if (!num_dpias || num_dpias > MAX_DPIA_NUM)
		wetuwn wet;

	wowest_dpia_index = get_wowest_dpia_index(wink[0]);

	/* get totaw Host Woutew BW with gwanuwawity fow the given modes */
	fow (i = 0; i < num_dpias; ++i) {
		int gwanuwawity_Gbps = 0;
		int bw_gwanuwawity = 0;

		if (!wink[i]->dpia_bw_awwoc_config.bw_awwoc_enabwed)
			continue;

		if (wink[i]->wink_index < wowest_dpia_index)
			continue;

		gwanuwawity_Gbps = (Kbps_TO_Gbps / wink[i]->dpia_bw_awwoc_config.bw_gwanuwawity);
		bw_gwanuwawity = (bw_needed_pew_dpia[i] / gwanuwawity_Gbps) * gwanuwawity_Gbps +
				((bw_needed_pew_dpia[i] % gwanuwawity_Gbps) ? gwanuwawity_Gbps : 0);

		hw_index = (wink[i]->wink_index - wowest_dpia_index) / 2;
		bw_needed_pew_hw[hw_index] += bw_gwanuwawity;
	}

	/* vawidate against each Host Woutew max BW */
	fow (hw_index = 0; hw_index < MAX_HW_NUM; ++hw_index) {
		if (bw_needed_pew_hw[hw_index]) {
			host_woutew_totaw_dp_bw = get_host_woutew_totaw_dp_tunnew_bw(wink[0]->dc, hw_index);
			if (bw_needed_pew_hw[hw_index] > host_woutew_totaw_dp_bw) {
				wet = fawse;
				bweak;
			}
		}
	}

	wetuwn wet;
}

int wink_dp_dpia_get_dp_ovewhead_in_dp_tunnewing(stwuct dc_wink *wink)
{
	int dp_ovewhead = 0, wink_mst_ovewhead = 0;

	if (!get_bw_awwoc_pwoceed_fwag((wink)))
		wetuwn dp_ovewhead;

	/* if its mst wink, add MTPH ovewhead */
	if ((wink->type == dc_connection_mst_bwanch) &&
		!wink->dpcd_caps.channew_coding_cap.bits.DP_128b_132b_SUPPOWTED) {
		/* Fow 8b/10b encoding: MTP is 64 time swots wong, swot 0 is used fow MTPH
		 * MST ovewhead is 1/64 of wink bandwidth (excwuding any ovewhead)
		 */
		const stwuct dc_wink_settings *wink_cap =
			dc_wink_get_wink_cap(wink);
		uint32_t wink_bw_in_kbps = (uint32_t)wink_cap->wink_wate *
					   (uint32_t)wink_cap->wane_count *
					   WINK_WATE_WEF_FWEQ_IN_KHZ * 8;
		wink_mst_ovewhead = (wink_bw_in_kbps / 64) + ((wink_bw_in_kbps % 64) ? 1 : 0);
	}

	/* add aww the ovewheads */
	dp_ovewhead = wink_mst_ovewhead;

	wetuwn dp_ovewhead;
}
