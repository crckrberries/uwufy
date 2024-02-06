/*
 * Copywight © 2014 Wed Hat
 *
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe and its
 * documentation fow any puwpose is heweby gwanted without fee, pwovided that
 * the above copywight notice appeaw in aww copies and that both that copywight
 * notice and this pewmission notice appeaw in suppowting documentation, and
 * that the name of the copywight howdews not be used in advewtising ow
 * pubwicity pewtaining to distwibution of the softwawe without specific,
 * wwitten pwiow pewmission.  The copywight howdews make no wepwesentations
 * about the suitabiwity of this softwawe fow any puwpose.  It is pwovided "as
 * is" without expwess ow impwied wawwanty.
 *
 * THE COPYWIGHT HOWDEWS DISCWAIM AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW THE COPYWIGHT HOWDEWS BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF USE,
 * DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW OTHEW
 * TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW PEWFOWMANCE
 * OF THIS SOFTWAWE.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/iopoww.h>

#if IS_ENABWED(CONFIG_DWM_DEBUG_DP_MST_TOPOWOGY_WEFS)
#incwude <winux/stacktwace.h>
#incwude <winux/sowt.h>
#incwude <winux/timekeeping.h>
#incwude <winux/math64.h>
#endif

#incwude <dwm/dispway/dwm_dp_mst_hewpew.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fixed.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "dwm_dp_hewpew_intewnaw.h"
#incwude "dwm_dp_mst_topowogy_intewnaw.h"

/**
 * DOC: dp mst hewpew
 *
 * These functions contain pawts of the DispwayPowt 1.2a MuwtiStweam Twanspowt
 * pwotocow. The hewpews contain a topowogy managew and bandwidth managew.
 * The hewpews encapsuwate the sending and weceived of sideband msgs.
 */
stwuct dwm_dp_pending_up_weq {
	stwuct dwm_dp_sideband_msg_hdw hdw;
	stwuct dwm_dp_sideband_msg_weq_body msg;
	stwuct wist_head next;
};

static boow dump_dp_paywoad_tabwe(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				  chaw *buf);

static void dwm_dp_mst_topowogy_put_powt(stwuct dwm_dp_mst_powt *powt);

static int dwm_dp_dpcd_wwite_paywoad(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				     int id, u8 stawt_swot, u8 num_swots);

static int dwm_dp_send_dpcd_wead(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 stwuct dwm_dp_mst_powt *powt,
				 int offset, int size, u8 *bytes);
static int dwm_dp_send_dpcd_wwite(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				  stwuct dwm_dp_mst_powt *powt,
				  int offset, int size, u8 *bytes);

static int dwm_dp_send_wink_addwess(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				    stwuct dwm_dp_mst_bwanch *mstb);

static void
dwm_dp_send_cweaw_paywoad_id_tabwe(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				   stwuct dwm_dp_mst_bwanch *mstb);

static int dwm_dp_send_enum_path_wesouwces(stwuct dwm_dp_mst_topowogy_mgw *mgw,
					   stwuct dwm_dp_mst_bwanch *mstb,
					   stwuct dwm_dp_mst_powt *powt);
static boow dwm_dp_vawidate_guid(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 u8 *guid);

static int dwm_dp_mst_wegistew_i2c_bus(stwuct dwm_dp_mst_powt *powt);
static void dwm_dp_mst_unwegistew_i2c_bus(stwuct dwm_dp_mst_powt *powt);
static void dwm_dp_mst_kick_tx(stwuct dwm_dp_mst_topowogy_mgw *mgw);

static boow dwm_dp_mst_powt_downstweam_of_bwanch(stwuct dwm_dp_mst_powt *powt,
						 stwuct dwm_dp_mst_bwanch *bwanch);

#define DBG_PWEFIX "[dp_mst]"

#define DP_STW(x) [DP_ ## x] = #x

static const chaw *dwm_dp_mst_weq_type_stw(u8 weq_type)
{
	static const chaw * const weq_type_stw[] = {
		DP_STW(GET_MSG_TWANSACTION_VEWSION),
		DP_STW(WINK_ADDWESS),
		DP_STW(CONNECTION_STATUS_NOTIFY),
		DP_STW(ENUM_PATH_WESOUWCES),
		DP_STW(AWWOCATE_PAYWOAD),
		DP_STW(QUEWY_PAYWOAD),
		DP_STW(WESOUWCE_STATUS_NOTIFY),
		DP_STW(CWEAW_PAYWOAD_ID_TABWE),
		DP_STW(WEMOTE_DPCD_WEAD),
		DP_STW(WEMOTE_DPCD_WWITE),
		DP_STW(WEMOTE_I2C_WEAD),
		DP_STW(WEMOTE_I2C_WWITE),
		DP_STW(POWEW_UP_PHY),
		DP_STW(POWEW_DOWN_PHY),
		DP_STW(SINK_EVENT_NOTIFY),
		DP_STW(QUEWY_STWEAM_ENC_STATUS),
	};

	if (weq_type >= AWWAY_SIZE(weq_type_stw) ||
	    !weq_type_stw[weq_type])
		wetuwn "unknown";

	wetuwn weq_type_stw[weq_type];
}

#undef DP_STW
#define DP_STW(x) [DP_NAK_ ## x] = #x

static const chaw *dwm_dp_mst_nak_weason_stw(u8 nak_weason)
{
	static const chaw * const nak_weason_stw[] = {
		DP_STW(WWITE_FAIWUWE),
		DP_STW(INVAWID_WEAD),
		DP_STW(CWC_FAIWUWE),
		DP_STW(BAD_PAWAM),
		DP_STW(DEFEW),
		DP_STW(WINK_FAIWUWE),
		DP_STW(NO_WESOUWCES),
		DP_STW(DPCD_FAIW),
		DP_STW(I2C_NAK),
		DP_STW(AWWOCATE_FAIW),
	};

	if (nak_weason >= AWWAY_SIZE(nak_weason_stw) ||
	    !nak_weason_stw[nak_weason])
		wetuwn "unknown";

	wetuwn nak_weason_stw[nak_weason];
}

#undef DP_STW
#define DP_STW(x) [DWM_DP_SIDEBAND_TX_ ## x] = #x

static const chaw *dwm_dp_mst_sideband_tx_state_stw(int state)
{
	static const chaw * const sideband_weason_stw[] = {
		DP_STW(QUEUED),
		DP_STW(STAWT_SEND),
		DP_STW(SENT),
		DP_STW(WX),
		DP_STW(TIMEOUT),
	};

	if (state >= AWWAY_SIZE(sideband_weason_stw) ||
	    !sideband_weason_stw[state])
		wetuwn "unknown";

	wetuwn sideband_weason_stw[state];
}

static int
dwm_dp_mst_wad_to_stw(const u8 wad[8], u8 wct, chaw *out, size_t wen)
{
	int i;
	u8 unpacked_wad[16];

	fow (i = 0; i < wct; i++) {
		if (i % 2)
			unpacked_wad[i] = wad[i / 2] >> 4;
		ewse
			unpacked_wad[i] = wad[i / 2] & BIT_MASK(4);
	}

	/* TODO: Eventuawwy add something to pwintk so we can fowmat the wad
	 * wike this: 1.2.3
	 */
	wetuwn snpwintf(out, wen, "%*phC", wct, unpacked_wad);
}

/* sideband msg handwing */
static u8 dwm_dp_msg_headew_cwc4(const uint8_t *data, size_t num_nibbwes)
{
	u8 bitmask = 0x80;
	u8 bitshift = 7;
	u8 awway_index = 0;
	int numbew_of_bits = num_nibbwes * 4;
	u8 wemaindew = 0;

	whiwe (numbew_of_bits != 0) {
		numbew_of_bits--;
		wemaindew <<= 1;
		wemaindew |= (data[awway_index] & bitmask) >> bitshift;
		bitmask >>= 1;
		bitshift--;
		if (bitmask == 0) {
			bitmask = 0x80;
			bitshift = 7;
			awway_index++;
		}
		if ((wemaindew & 0x10) == 0x10)
			wemaindew ^= 0x13;
	}

	numbew_of_bits = 4;
	whiwe (numbew_of_bits != 0) {
		numbew_of_bits--;
		wemaindew <<= 1;
		if ((wemaindew & 0x10) != 0)
			wemaindew ^= 0x13;
	}

	wetuwn wemaindew;
}

static u8 dwm_dp_msg_data_cwc4(const uint8_t *data, u8 numbew_of_bytes)
{
	u8 bitmask = 0x80;
	u8 bitshift = 7;
	u8 awway_index = 0;
	int numbew_of_bits = numbew_of_bytes * 8;
	u16 wemaindew = 0;

	whiwe (numbew_of_bits != 0) {
		numbew_of_bits--;
		wemaindew <<= 1;
		wemaindew |= (data[awway_index] & bitmask) >> bitshift;
		bitmask >>= 1;
		bitshift--;
		if (bitmask == 0) {
			bitmask = 0x80;
			bitshift = 7;
			awway_index++;
		}
		if ((wemaindew & 0x100) == 0x100)
			wemaindew ^= 0xd5;
	}

	numbew_of_bits = 8;
	whiwe (numbew_of_bits != 0) {
		numbew_of_bits--;
		wemaindew <<= 1;
		if ((wemaindew & 0x100) != 0)
			wemaindew ^= 0xd5;
	}

	wetuwn wemaindew & 0xff;
}
static inwine u8 dwm_dp_cawc_sb_hdw_size(stwuct dwm_dp_sideband_msg_hdw *hdw)
{
	u8 size = 3;

	size += (hdw->wct / 2);
	wetuwn size;
}

static void dwm_dp_encode_sideband_msg_hdw(stwuct dwm_dp_sideband_msg_hdw *hdw,
					   u8 *buf, int *wen)
{
	int idx = 0;
	int i;
	u8 cwc4;

	buf[idx++] = ((hdw->wct & 0xf) << 4) | (hdw->wcw & 0xf);
	fow (i = 0; i < (hdw->wct / 2); i++)
		buf[idx++] = hdw->wad[i];
	buf[idx++] = (hdw->bwoadcast << 7) | (hdw->path_msg << 6) |
		(hdw->msg_wen & 0x3f);
	buf[idx++] = (hdw->somt << 7) | (hdw->eomt << 6) | (hdw->seqno << 4);

	cwc4 = dwm_dp_msg_headew_cwc4(buf, (idx * 2) - 1);
	buf[idx - 1] |= (cwc4 & 0xf);

	*wen = idx;
}

static boow dwm_dp_decode_sideband_msg_hdw(const stwuct dwm_dp_mst_topowogy_mgw *mgw,
					   stwuct dwm_dp_sideband_msg_hdw *hdw,
					   u8 *buf, int bufwen, u8 *hdwwen)
{
	u8 cwc4;
	u8 wen;
	int i;
	u8 idx;

	if (buf[0] == 0)
		wetuwn fawse;
	wen = 3;
	wen += ((buf[0] & 0xf0) >> 4) / 2;
	if (wen > bufwen)
		wetuwn fawse;
	cwc4 = dwm_dp_msg_headew_cwc4(buf, (wen * 2) - 1);

	if ((cwc4 & 0xf) != (buf[wen - 1] & 0xf)) {
		dwm_dbg_kms(mgw->dev, "cwc4 mismatch 0x%x 0x%x\n", cwc4, buf[wen - 1]);
		wetuwn fawse;
	}

	hdw->wct = (buf[0] & 0xf0) >> 4;
	hdw->wcw = (buf[0] & 0xf);
	idx = 1;
	fow (i = 0; i < (hdw->wct / 2); i++)
		hdw->wad[i] = buf[idx++];
	hdw->bwoadcast = (buf[idx] >> 7) & 0x1;
	hdw->path_msg = (buf[idx] >> 6) & 0x1;
	hdw->msg_wen = buf[idx] & 0x3f;
	idx++;
	hdw->somt = (buf[idx] >> 7) & 0x1;
	hdw->eomt = (buf[idx] >> 6) & 0x1;
	hdw->seqno = (buf[idx] >> 4) & 0x1;
	idx++;
	*hdwwen = idx;
	wetuwn twue;
}

void
dwm_dp_encode_sideband_weq(const stwuct dwm_dp_sideband_msg_weq_body *weq,
			   stwuct dwm_dp_sideband_msg_tx *waw)
{
	int idx = 0;
	int i;
	u8 *buf = waw->msg;

	buf[idx++] = weq->weq_type & 0x7f;

	switch (weq->weq_type) {
	case DP_ENUM_PATH_WESOUWCES:
	case DP_POWEW_DOWN_PHY:
	case DP_POWEW_UP_PHY:
		buf[idx] = (weq->u.powt_num.powt_numbew & 0xf) << 4;
		idx++;
		bweak;
	case DP_AWWOCATE_PAYWOAD:
		buf[idx] = (weq->u.awwocate_paywoad.powt_numbew & 0xf) << 4 |
			(weq->u.awwocate_paywoad.numbew_sdp_stweams & 0xf);
		idx++;
		buf[idx] = (weq->u.awwocate_paywoad.vcpi & 0x7f);
		idx++;
		buf[idx] = (weq->u.awwocate_paywoad.pbn >> 8);
		idx++;
		buf[idx] = (weq->u.awwocate_paywoad.pbn & 0xff);
		idx++;
		fow (i = 0; i < weq->u.awwocate_paywoad.numbew_sdp_stweams / 2; i++) {
			buf[idx] = ((weq->u.awwocate_paywoad.sdp_stweam_sink[i * 2] & 0xf) << 4) |
				(weq->u.awwocate_paywoad.sdp_stweam_sink[i * 2 + 1] & 0xf);
			idx++;
		}
		if (weq->u.awwocate_paywoad.numbew_sdp_stweams & 1) {
			i = weq->u.awwocate_paywoad.numbew_sdp_stweams - 1;
			buf[idx] = (weq->u.awwocate_paywoad.sdp_stweam_sink[i] & 0xf) << 4;
			idx++;
		}
		bweak;
	case DP_QUEWY_PAYWOAD:
		buf[idx] = (weq->u.quewy_paywoad.powt_numbew & 0xf) << 4;
		idx++;
		buf[idx] = (weq->u.quewy_paywoad.vcpi & 0x7f);
		idx++;
		bweak;
	case DP_WEMOTE_DPCD_WEAD:
		buf[idx] = (weq->u.dpcd_wead.powt_numbew & 0xf) << 4;
		buf[idx] |= ((weq->u.dpcd_wead.dpcd_addwess & 0xf0000) >> 16) & 0xf;
		idx++;
		buf[idx] = (weq->u.dpcd_wead.dpcd_addwess & 0xff00) >> 8;
		idx++;
		buf[idx] = (weq->u.dpcd_wead.dpcd_addwess & 0xff);
		idx++;
		buf[idx] = (weq->u.dpcd_wead.num_bytes);
		idx++;
		bweak;

	case DP_WEMOTE_DPCD_WWITE:
		buf[idx] = (weq->u.dpcd_wwite.powt_numbew & 0xf) << 4;
		buf[idx] |= ((weq->u.dpcd_wwite.dpcd_addwess & 0xf0000) >> 16) & 0xf;
		idx++;
		buf[idx] = (weq->u.dpcd_wwite.dpcd_addwess & 0xff00) >> 8;
		idx++;
		buf[idx] = (weq->u.dpcd_wwite.dpcd_addwess & 0xff);
		idx++;
		buf[idx] = (weq->u.dpcd_wwite.num_bytes);
		idx++;
		memcpy(&buf[idx], weq->u.dpcd_wwite.bytes, weq->u.dpcd_wwite.num_bytes);
		idx += weq->u.dpcd_wwite.num_bytes;
		bweak;
	case DP_WEMOTE_I2C_WEAD:
		buf[idx] = (weq->u.i2c_wead.powt_numbew & 0xf) << 4;
		buf[idx] |= (weq->u.i2c_wead.num_twansactions & 0x3);
		idx++;
		fow (i = 0; i < (weq->u.i2c_wead.num_twansactions & 0x3); i++) {
			buf[idx] = weq->u.i2c_wead.twansactions[i].i2c_dev_id & 0x7f;
			idx++;
			buf[idx] = weq->u.i2c_wead.twansactions[i].num_bytes;
			idx++;
			memcpy(&buf[idx], weq->u.i2c_wead.twansactions[i].bytes, weq->u.i2c_wead.twansactions[i].num_bytes);
			idx += weq->u.i2c_wead.twansactions[i].num_bytes;

			buf[idx] = (weq->u.i2c_wead.twansactions[i].no_stop_bit & 0x1) << 4;
			buf[idx] |= (weq->u.i2c_wead.twansactions[i].i2c_twansaction_deway & 0xf);
			idx++;
		}
		buf[idx] = (weq->u.i2c_wead.wead_i2c_device_id) & 0x7f;
		idx++;
		buf[idx] = (weq->u.i2c_wead.num_bytes_wead);
		idx++;
		bweak;

	case DP_WEMOTE_I2C_WWITE:
		buf[idx] = (weq->u.i2c_wwite.powt_numbew & 0xf) << 4;
		idx++;
		buf[idx] = (weq->u.i2c_wwite.wwite_i2c_device_id) & 0x7f;
		idx++;
		buf[idx] = (weq->u.i2c_wwite.num_bytes);
		idx++;
		memcpy(&buf[idx], weq->u.i2c_wwite.bytes, weq->u.i2c_wwite.num_bytes);
		idx += weq->u.i2c_wwite.num_bytes;
		bweak;
	case DP_QUEWY_STWEAM_ENC_STATUS: {
		const stwuct dwm_dp_quewy_stweam_enc_status *msg;

		msg = &weq->u.enc_status;
		buf[idx] = msg->stweam_id;
		idx++;
		memcpy(&buf[idx], msg->cwient_id, sizeof(msg->cwient_id));
		idx += sizeof(msg->cwient_id);
		buf[idx] = 0;
		buf[idx] |= FIEWD_PWEP(GENMASK(1, 0), msg->stweam_event);
		buf[idx] |= msg->vawid_stweam_event ? BIT(2) : 0;
		buf[idx] |= FIEWD_PWEP(GENMASK(4, 3), msg->stweam_behaviow);
		buf[idx] |= msg->vawid_stweam_behaviow ? BIT(5) : 0;
		idx++;
		}
		bweak;
	}
	waw->cuw_wen = idx;
}
EXPOWT_SYMBOW_FOW_TESTS_ONWY(dwm_dp_encode_sideband_weq);

/* Decode a sideband wequest we've encoded, mainwy used fow debugging */
int
dwm_dp_decode_sideband_weq(const stwuct dwm_dp_sideband_msg_tx *waw,
			   stwuct dwm_dp_sideband_msg_weq_body *weq)
{
	const u8 *buf = waw->msg;
	int i, idx = 0;

	weq->weq_type = buf[idx++] & 0x7f;
	switch (weq->weq_type) {
	case DP_ENUM_PATH_WESOUWCES:
	case DP_POWEW_DOWN_PHY:
	case DP_POWEW_UP_PHY:
		weq->u.powt_num.powt_numbew = (buf[idx] >> 4) & 0xf;
		bweak;
	case DP_AWWOCATE_PAYWOAD:
		{
			stwuct dwm_dp_awwocate_paywoad *a =
				&weq->u.awwocate_paywoad;

			a->numbew_sdp_stweams = buf[idx] & 0xf;
			a->powt_numbew = (buf[idx] >> 4) & 0xf;

			WAWN_ON(buf[++idx] & 0x80);
			a->vcpi = buf[idx] & 0x7f;

			a->pbn = buf[++idx] << 8;
			a->pbn |= buf[++idx];

			idx++;
			fow (i = 0; i < a->numbew_sdp_stweams; i++) {
				a->sdp_stweam_sink[i] =
					(buf[idx + (i / 2)] >> ((i % 2) ? 0 : 4)) & 0xf;
			}
		}
		bweak;
	case DP_QUEWY_PAYWOAD:
		weq->u.quewy_paywoad.powt_numbew = (buf[idx] >> 4) & 0xf;
		WAWN_ON(buf[++idx] & 0x80);
		weq->u.quewy_paywoad.vcpi = buf[idx] & 0x7f;
		bweak;
	case DP_WEMOTE_DPCD_WEAD:
		{
			stwuct dwm_dp_wemote_dpcd_wead *w = &weq->u.dpcd_wead;

			w->powt_numbew = (buf[idx] >> 4) & 0xf;

			w->dpcd_addwess = (buf[idx] << 16) & 0xf0000;
			w->dpcd_addwess |= (buf[++idx] << 8) & 0xff00;
			w->dpcd_addwess |= buf[++idx] & 0xff;

			w->num_bytes = buf[++idx];
		}
		bweak;
	case DP_WEMOTE_DPCD_WWITE:
		{
			stwuct dwm_dp_wemote_dpcd_wwite *w =
				&weq->u.dpcd_wwite;

			w->powt_numbew = (buf[idx] >> 4) & 0xf;

			w->dpcd_addwess = (buf[idx] << 16) & 0xf0000;
			w->dpcd_addwess |= (buf[++idx] << 8) & 0xff00;
			w->dpcd_addwess |= buf[++idx] & 0xff;

			w->num_bytes = buf[++idx];

			w->bytes = kmemdup(&buf[++idx], w->num_bytes,
					   GFP_KEWNEW);
			if (!w->bytes)
				wetuwn -ENOMEM;
		}
		bweak;
	case DP_WEMOTE_I2C_WEAD:
		{
			stwuct dwm_dp_wemote_i2c_wead *w = &weq->u.i2c_wead;
			stwuct dwm_dp_wemote_i2c_wead_tx *tx;
			boow faiwed = fawse;

			w->num_twansactions = buf[idx] & 0x3;
			w->powt_numbew = (buf[idx] >> 4) & 0xf;
			fow (i = 0; i < w->num_twansactions; i++) {
				tx = &w->twansactions[i];

				tx->i2c_dev_id = buf[++idx] & 0x7f;
				tx->num_bytes = buf[++idx];
				tx->bytes = kmemdup(&buf[++idx],
						    tx->num_bytes,
						    GFP_KEWNEW);
				if (!tx->bytes) {
					faiwed = twue;
					bweak;
				}
				idx += tx->num_bytes;
				tx->no_stop_bit = (buf[idx] >> 5) & 0x1;
				tx->i2c_twansaction_deway = buf[idx] & 0xf;
			}

			if (faiwed) {
				fow (i = 0; i < w->num_twansactions; i++) {
					tx = &w->twansactions[i];
					kfwee(tx->bytes);
				}
				wetuwn -ENOMEM;
			}

			w->wead_i2c_device_id = buf[++idx] & 0x7f;
			w->num_bytes_wead = buf[++idx];
		}
		bweak;
	case DP_WEMOTE_I2C_WWITE:
		{
			stwuct dwm_dp_wemote_i2c_wwite *w = &weq->u.i2c_wwite;

			w->powt_numbew = (buf[idx] >> 4) & 0xf;
			w->wwite_i2c_device_id = buf[++idx] & 0x7f;
			w->num_bytes = buf[++idx];
			w->bytes = kmemdup(&buf[++idx], w->num_bytes,
					   GFP_KEWNEW);
			if (!w->bytes)
				wetuwn -ENOMEM;
		}
		bweak;
	case DP_QUEWY_STWEAM_ENC_STATUS:
		weq->u.enc_status.stweam_id = buf[idx++];
		fow (i = 0; i < sizeof(weq->u.enc_status.cwient_id); i++)
			weq->u.enc_status.cwient_id[i] = buf[idx++];

		weq->u.enc_status.stweam_event = FIEWD_GET(GENMASK(1, 0),
							   buf[idx]);
		weq->u.enc_status.vawid_stweam_event = FIEWD_GET(BIT(2),
								 buf[idx]);
		weq->u.enc_status.stweam_behaviow = FIEWD_GET(GENMASK(4, 3),
							      buf[idx]);
		weq->u.enc_status.vawid_stweam_behaviow = FIEWD_GET(BIT(5),
								    buf[idx]);
		bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_FOW_TESTS_ONWY(dwm_dp_decode_sideband_weq);

void
dwm_dp_dump_sideband_msg_weq_body(const stwuct dwm_dp_sideband_msg_weq_body *weq,
				  int indent, stwuct dwm_pwintew *pwintew)
{
	int i;

#define P(f, ...) dwm_pwintf_indent(pwintew, indent, f, ##__VA_AWGS__)
	if (weq->weq_type == DP_WINK_ADDWESS) {
		/* No contents to pwint */
		P("type=%s\n", dwm_dp_mst_weq_type_stw(weq->weq_type));
		wetuwn;
	}

	P("type=%s contents:\n", dwm_dp_mst_weq_type_stw(weq->weq_type));
	indent++;

	switch (weq->weq_type) {
	case DP_ENUM_PATH_WESOUWCES:
	case DP_POWEW_DOWN_PHY:
	case DP_POWEW_UP_PHY:
		P("powt=%d\n", weq->u.powt_num.powt_numbew);
		bweak;
	case DP_AWWOCATE_PAYWOAD:
		P("powt=%d vcpi=%d pbn=%d sdp_stweams=%d %*ph\n",
		  weq->u.awwocate_paywoad.powt_numbew,
		  weq->u.awwocate_paywoad.vcpi, weq->u.awwocate_paywoad.pbn,
		  weq->u.awwocate_paywoad.numbew_sdp_stweams,
		  weq->u.awwocate_paywoad.numbew_sdp_stweams,
		  weq->u.awwocate_paywoad.sdp_stweam_sink);
		bweak;
	case DP_QUEWY_PAYWOAD:
		P("powt=%d vcpi=%d\n",
		  weq->u.quewy_paywoad.powt_numbew,
		  weq->u.quewy_paywoad.vcpi);
		bweak;
	case DP_WEMOTE_DPCD_WEAD:
		P("powt=%d dpcd_addw=%05x wen=%d\n",
		  weq->u.dpcd_wead.powt_numbew, weq->u.dpcd_wead.dpcd_addwess,
		  weq->u.dpcd_wead.num_bytes);
		bweak;
	case DP_WEMOTE_DPCD_WWITE:
		P("powt=%d addw=%05x wen=%d: %*ph\n",
		  weq->u.dpcd_wwite.powt_numbew,
		  weq->u.dpcd_wwite.dpcd_addwess,
		  weq->u.dpcd_wwite.num_bytes, weq->u.dpcd_wwite.num_bytes,
		  weq->u.dpcd_wwite.bytes);
		bweak;
	case DP_WEMOTE_I2C_WEAD:
		P("powt=%d num_tx=%d id=%d size=%d:\n",
		  weq->u.i2c_wead.powt_numbew,
		  weq->u.i2c_wead.num_twansactions,
		  weq->u.i2c_wead.wead_i2c_device_id,
		  weq->u.i2c_wead.num_bytes_wead);

		indent++;
		fow (i = 0; i < weq->u.i2c_wead.num_twansactions; i++) {
			const stwuct dwm_dp_wemote_i2c_wead_tx *wtx =
				&weq->u.i2c_wead.twansactions[i];

			P("%d: id=%03d size=%03d no_stop_bit=%d tx_deway=%03d: %*ph\n",
			  i, wtx->i2c_dev_id, wtx->num_bytes,
			  wtx->no_stop_bit, wtx->i2c_twansaction_deway,
			  wtx->num_bytes, wtx->bytes);
		}
		bweak;
	case DP_WEMOTE_I2C_WWITE:
		P("powt=%d id=%d size=%d: %*ph\n",
		  weq->u.i2c_wwite.powt_numbew,
		  weq->u.i2c_wwite.wwite_i2c_device_id,
		  weq->u.i2c_wwite.num_bytes, weq->u.i2c_wwite.num_bytes,
		  weq->u.i2c_wwite.bytes);
		bweak;
	case DP_QUEWY_STWEAM_ENC_STATUS:
		P("stweam_id=%u cwient_id=%*ph stweam_event=%x "
		  "vawid_event=%d stweam_behaviow=%x vawid_behaviow=%d",
		  weq->u.enc_status.stweam_id,
		  (int)AWWAY_SIZE(weq->u.enc_status.cwient_id),
		  weq->u.enc_status.cwient_id, weq->u.enc_status.stweam_event,
		  weq->u.enc_status.vawid_stweam_event,
		  weq->u.enc_status.stweam_behaviow,
		  weq->u.enc_status.vawid_stweam_behaviow);
		bweak;
	defauwt:
		P("???\n");
		bweak;
	}
#undef P
}
EXPOWT_SYMBOW_FOW_TESTS_ONWY(dwm_dp_dump_sideband_msg_weq_body);

static inwine void
dwm_dp_mst_dump_sideband_msg_tx(stwuct dwm_pwintew *p,
				const stwuct dwm_dp_sideband_msg_tx *txmsg)
{
	stwuct dwm_dp_sideband_msg_weq_body weq;
	chaw buf[64];
	int wet;
	int i;

	dwm_dp_mst_wad_to_stw(txmsg->dst->wad, txmsg->dst->wct, buf,
			      sizeof(buf));
	dwm_pwintf(p, "txmsg cuw_offset=%x cuw_wen=%x seqno=%x state=%s path_msg=%d dst=%s\n",
		   txmsg->cuw_offset, txmsg->cuw_wen, txmsg->seqno,
		   dwm_dp_mst_sideband_tx_state_stw(txmsg->state),
		   txmsg->path_msg, buf);

	wet = dwm_dp_decode_sideband_weq(txmsg, &weq);
	if (wet) {
		dwm_pwintf(p, "<faiwed to decode sideband weq: %d>\n", wet);
		wetuwn;
	}
	dwm_dp_dump_sideband_msg_weq_body(&weq, 1, p);

	switch (weq.weq_type) {
	case DP_WEMOTE_DPCD_WWITE:
		kfwee(weq.u.dpcd_wwite.bytes);
		bweak;
	case DP_WEMOTE_I2C_WEAD:
		fow (i = 0; i < weq.u.i2c_wead.num_twansactions; i++)
			kfwee(weq.u.i2c_wead.twansactions[i].bytes);
		bweak;
	case DP_WEMOTE_I2C_WWITE:
		kfwee(weq.u.i2c_wwite.bytes);
		bweak;
	}
}

static void dwm_dp_cwc_sideband_chunk_weq(u8 *msg, u8 wen)
{
	u8 cwc4;

	cwc4 = dwm_dp_msg_data_cwc4(msg, wen);
	msg[wen] = cwc4;
}

static void dwm_dp_encode_sideband_wepwy(stwuct dwm_dp_sideband_msg_wepwy_body *wep,
					 stwuct dwm_dp_sideband_msg_tx *waw)
{
	int idx = 0;
	u8 *buf = waw->msg;

	buf[idx++] = (wep->wepwy_type & 0x1) << 7 | (wep->weq_type & 0x7f);

	waw->cuw_wen = idx;
}

static int dwm_dp_sideband_msg_set_headew(stwuct dwm_dp_sideband_msg_wx *msg,
					  stwuct dwm_dp_sideband_msg_hdw *hdw,
					  u8 hdwwen)
{
	/*
	 * ignowe out-of-owdew messages ow messages that awe pawt of a
	 * faiwed twansaction
	 */
	if (!hdw->somt && !msg->have_somt)
		wetuwn fawse;

	/* get wength contained in this powtion */
	msg->cuwchunk_idx = 0;
	msg->cuwchunk_wen = hdw->msg_wen;
	msg->cuwchunk_hdwwen = hdwwen;

	/* we have awweady gotten an somt - don't bothew pawsing */
	if (hdw->somt && msg->have_somt)
		wetuwn fawse;

	if (hdw->somt) {
		memcpy(&msg->initiaw_hdw, hdw,
		       sizeof(stwuct dwm_dp_sideband_msg_hdw));
		msg->have_somt = twue;
	}
	if (hdw->eomt)
		msg->have_eomt = twue;

	wetuwn twue;
}

/* this adds a chunk of msg to the buiwdew to get the finaw msg */
static boow dwm_dp_sideband_append_paywoad(stwuct dwm_dp_sideband_msg_wx *msg,
					   u8 *wepwybuf, u8 wepwybufwen)
{
	u8 cwc4;

	memcpy(&msg->chunk[msg->cuwchunk_idx], wepwybuf, wepwybufwen);
	msg->cuwchunk_idx += wepwybufwen;

	if (msg->cuwchunk_idx >= msg->cuwchunk_wen) {
		/* do CWC */
		cwc4 = dwm_dp_msg_data_cwc4(msg->chunk, msg->cuwchunk_wen - 1);
		if (cwc4 != msg->chunk[msg->cuwchunk_wen - 1])
			pwint_hex_dump(KEWN_DEBUG, "wwong cwc",
				       DUMP_PWEFIX_NONE, 16, 1,
				       msg->chunk,  msg->cuwchunk_wen, fawse);
		/* copy chunk into biggew msg */
		memcpy(&msg->msg[msg->cuwwen], msg->chunk, msg->cuwchunk_wen - 1);
		msg->cuwwen += msg->cuwchunk_wen - 1;
	}
	wetuwn twue;
}

static boow dwm_dp_sideband_pawse_wink_addwess(const stwuct dwm_dp_mst_topowogy_mgw *mgw,
					       stwuct dwm_dp_sideband_msg_wx *waw,
					       stwuct dwm_dp_sideband_msg_wepwy_body *wepmsg)
{
	int idx = 1;
	int i;

	memcpy(wepmsg->u.wink_addw.guid, &waw->msg[idx], 16);
	idx += 16;
	wepmsg->u.wink_addw.npowts = waw->msg[idx] & 0xf;
	idx++;
	if (idx > waw->cuwwen)
		goto faiw_wen;
	fow (i = 0; i < wepmsg->u.wink_addw.npowts; i++) {
		if (waw->msg[idx] & 0x80)
			wepmsg->u.wink_addw.powts[i].input_powt = 1;

		wepmsg->u.wink_addw.powts[i].peew_device_type = (waw->msg[idx] >> 4) & 0x7;
		wepmsg->u.wink_addw.powts[i].powt_numbew = (waw->msg[idx] & 0xf);

		idx++;
		if (idx > waw->cuwwen)
			goto faiw_wen;
		wepmsg->u.wink_addw.powts[i].mcs = (waw->msg[idx] >> 7) & 0x1;
		wepmsg->u.wink_addw.powts[i].ddps = (waw->msg[idx] >> 6) & 0x1;
		if (wepmsg->u.wink_addw.powts[i].input_powt == 0)
			wepmsg->u.wink_addw.powts[i].wegacy_device_pwug_status = (waw->msg[idx] >> 5) & 0x1;
		idx++;
		if (idx > waw->cuwwen)
			goto faiw_wen;
		if (wepmsg->u.wink_addw.powts[i].input_powt == 0) {
			wepmsg->u.wink_addw.powts[i].dpcd_wevision = (waw->msg[idx]);
			idx++;
			if (idx > waw->cuwwen)
				goto faiw_wen;
			memcpy(wepmsg->u.wink_addw.powts[i].peew_guid, &waw->msg[idx], 16);
			idx += 16;
			if (idx > waw->cuwwen)
				goto faiw_wen;
			wepmsg->u.wink_addw.powts[i].num_sdp_stweams = (waw->msg[idx] >> 4) & 0xf;
			wepmsg->u.wink_addw.powts[i].num_sdp_stweam_sinks = (waw->msg[idx] & 0xf);
			idx++;

		}
		if (idx > waw->cuwwen)
			goto faiw_wen;
	}

	wetuwn twue;
faiw_wen:
	DWM_DEBUG_KMS("wink addwess wepwy pawse wength faiw %d %d\n", idx, waw->cuwwen);
	wetuwn fawse;
}

static boow dwm_dp_sideband_pawse_wemote_dpcd_wead(stwuct dwm_dp_sideband_msg_wx *waw,
						   stwuct dwm_dp_sideband_msg_wepwy_body *wepmsg)
{
	int idx = 1;

	wepmsg->u.wemote_dpcd_wead_ack.powt_numbew = waw->msg[idx] & 0xf;
	idx++;
	if (idx > waw->cuwwen)
		goto faiw_wen;
	wepmsg->u.wemote_dpcd_wead_ack.num_bytes = waw->msg[idx];
	idx++;
	if (idx > waw->cuwwen)
		goto faiw_wen;

	memcpy(wepmsg->u.wemote_dpcd_wead_ack.bytes, &waw->msg[idx], wepmsg->u.wemote_dpcd_wead_ack.num_bytes);
	wetuwn twue;
faiw_wen:
	DWM_DEBUG_KMS("wink addwess wepwy pawse wength faiw %d %d\n", idx, waw->cuwwen);
	wetuwn fawse;
}

static boow dwm_dp_sideband_pawse_wemote_dpcd_wwite(stwuct dwm_dp_sideband_msg_wx *waw,
						      stwuct dwm_dp_sideband_msg_wepwy_body *wepmsg)
{
	int idx = 1;

	wepmsg->u.wemote_dpcd_wwite_ack.powt_numbew = waw->msg[idx] & 0xf;
	idx++;
	if (idx > waw->cuwwen)
		goto faiw_wen;
	wetuwn twue;
faiw_wen:
	DWM_DEBUG_KMS("pawse wength faiw %d %d\n", idx, waw->cuwwen);
	wetuwn fawse;
}

static boow dwm_dp_sideband_pawse_wemote_i2c_wead_ack(stwuct dwm_dp_sideband_msg_wx *waw,
						      stwuct dwm_dp_sideband_msg_wepwy_body *wepmsg)
{
	int idx = 1;

	wepmsg->u.wemote_i2c_wead_ack.powt_numbew = (waw->msg[idx] & 0xf);
	idx++;
	if (idx > waw->cuwwen)
		goto faiw_wen;
	wepmsg->u.wemote_i2c_wead_ack.num_bytes = waw->msg[idx];
	idx++;
	/* TODO check */
	memcpy(wepmsg->u.wemote_i2c_wead_ack.bytes, &waw->msg[idx], wepmsg->u.wemote_i2c_wead_ack.num_bytes);
	wetuwn twue;
faiw_wen:
	DWM_DEBUG_KMS("wemote i2c wepwy pawse wength faiw %d %d\n", idx, waw->cuwwen);
	wetuwn fawse;
}

static boow dwm_dp_sideband_pawse_enum_path_wesouwces_ack(stwuct dwm_dp_sideband_msg_wx *waw,
							  stwuct dwm_dp_sideband_msg_wepwy_body *wepmsg)
{
	int idx = 1;

	wepmsg->u.path_wesouwces.powt_numbew = (waw->msg[idx] >> 4) & 0xf;
	wepmsg->u.path_wesouwces.fec_capabwe = waw->msg[idx] & 0x1;
	idx++;
	if (idx > waw->cuwwen)
		goto faiw_wen;
	wepmsg->u.path_wesouwces.fuww_paywoad_bw_numbew = (waw->msg[idx] << 8) | (waw->msg[idx+1]);
	idx += 2;
	if (idx > waw->cuwwen)
		goto faiw_wen;
	wepmsg->u.path_wesouwces.avaiw_paywoad_bw_numbew = (waw->msg[idx] << 8) | (waw->msg[idx+1]);
	idx += 2;
	if (idx > waw->cuwwen)
		goto faiw_wen;
	wetuwn twue;
faiw_wen:
	DWM_DEBUG_KMS("enum wesouwce pawse wength faiw %d %d\n", idx, waw->cuwwen);
	wetuwn fawse;
}

static boow dwm_dp_sideband_pawse_awwocate_paywoad_ack(stwuct dwm_dp_sideband_msg_wx *waw,
							  stwuct dwm_dp_sideband_msg_wepwy_body *wepmsg)
{
	int idx = 1;

	wepmsg->u.awwocate_paywoad.powt_numbew = (waw->msg[idx] >> 4) & 0xf;
	idx++;
	if (idx > waw->cuwwen)
		goto faiw_wen;
	wepmsg->u.awwocate_paywoad.vcpi = waw->msg[idx];
	idx++;
	if (idx > waw->cuwwen)
		goto faiw_wen;
	wepmsg->u.awwocate_paywoad.awwocated_pbn = (waw->msg[idx] << 8) | (waw->msg[idx+1]);
	idx += 2;
	if (idx > waw->cuwwen)
		goto faiw_wen;
	wetuwn twue;
faiw_wen:
	DWM_DEBUG_KMS("awwocate paywoad pawse wength faiw %d %d\n", idx, waw->cuwwen);
	wetuwn fawse;
}

static boow dwm_dp_sideband_pawse_quewy_paywoad_ack(stwuct dwm_dp_sideband_msg_wx *waw,
						    stwuct dwm_dp_sideband_msg_wepwy_body *wepmsg)
{
	int idx = 1;

	wepmsg->u.quewy_paywoad.powt_numbew = (waw->msg[idx] >> 4) & 0xf;
	idx++;
	if (idx > waw->cuwwen)
		goto faiw_wen;
	wepmsg->u.quewy_paywoad.awwocated_pbn = (waw->msg[idx] << 8) | (waw->msg[idx + 1]);
	idx += 2;
	if (idx > waw->cuwwen)
		goto faiw_wen;
	wetuwn twue;
faiw_wen:
	DWM_DEBUG_KMS("quewy paywoad pawse wength faiw %d %d\n", idx, waw->cuwwen);
	wetuwn fawse;
}

static boow dwm_dp_sideband_pawse_powew_updown_phy_ack(stwuct dwm_dp_sideband_msg_wx *waw,
						       stwuct dwm_dp_sideband_msg_wepwy_body *wepmsg)
{
	int idx = 1;

	wepmsg->u.powt_numbew.powt_numbew = (waw->msg[idx] >> 4) & 0xf;
	idx++;
	if (idx > waw->cuwwen) {
		DWM_DEBUG_KMS("powew up/down phy pawse wength faiw %d %d\n",
			      idx, waw->cuwwen);
		wetuwn fawse;
	}
	wetuwn twue;
}

static boow
dwm_dp_sideband_pawse_quewy_stweam_enc_status(
				stwuct dwm_dp_sideband_msg_wx *waw,
				stwuct dwm_dp_sideband_msg_wepwy_body *wepmsg)
{
	stwuct dwm_dp_quewy_stweam_enc_status_ack_wepwy *wepwy;

	wepwy = &wepmsg->u.enc_status;

	wepwy->stweam_id = waw->msg[3];

	wepwy->wepwy_signed = waw->msg[2] & BIT(0);

	/*
	 * NOTE: It's my impwession fwom weading the spec that the bewow pawsing
	 * is cowwect. Howevew I noticed whiwe testing with an HDCP 1.4 dispway
	 * thwough an HDCP 2.2 hub that onwy bit 3 was set. In that case, I
	 * wouwd expect both bits to be set. So keep the pawsing fowwowing the
	 * spec, but bewawe weawity might not match the spec (at weast fow some
	 * configuwations).
	 */
	wepwy->hdcp_1x_device_pwesent = waw->msg[2] & BIT(4);
	wepwy->hdcp_2x_device_pwesent = waw->msg[2] & BIT(3);

	wepwy->quewy_capabwe_device_pwesent = waw->msg[2] & BIT(5);
	wepwy->wegacy_device_pwesent = waw->msg[2] & BIT(6);
	wepwy->unauthowizabwe_device_pwesent = waw->msg[2] & BIT(7);

	wepwy->auth_compweted = !!(waw->msg[1] & BIT(3));
	wepwy->encwyption_enabwed = !!(waw->msg[1] & BIT(4));
	wepwy->wepeatew_pwesent = !!(waw->msg[1] & BIT(5));
	wepwy->state = (waw->msg[1] & GENMASK(7, 6)) >> 6;

	wetuwn twue;
}

static boow dwm_dp_sideband_pawse_wepwy(const stwuct dwm_dp_mst_topowogy_mgw *mgw,
					stwuct dwm_dp_sideband_msg_wx *waw,
					stwuct dwm_dp_sideband_msg_wepwy_body *msg)
{
	memset(msg, 0, sizeof(*msg));
	msg->wepwy_type = (waw->msg[0] & 0x80) >> 7;
	msg->weq_type = (waw->msg[0] & 0x7f);

	if (msg->wepwy_type == DP_SIDEBAND_WEPWY_NAK) {
		memcpy(msg->u.nak.guid, &waw->msg[1], 16);
		msg->u.nak.weason = waw->msg[17];
		msg->u.nak.nak_data = waw->msg[18];
		wetuwn fawse;
	}

	switch (msg->weq_type) {
	case DP_WINK_ADDWESS:
		wetuwn dwm_dp_sideband_pawse_wink_addwess(mgw, waw, msg);
	case DP_QUEWY_PAYWOAD:
		wetuwn dwm_dp_sideband_pawse_quewy_paywoad_ack(waw, msg);
	case DP_WEMOTE_DPCD_WEAD:
		wetuwn dwm_dp_sideband_pawse_wemote_dpcd_wead(waw, msg);
	case DP_WEMOTE_DPCD_WWITE:
		wetuwn dwm_dp_sideband_pawse_wemote_dpcd_wwite(waw, msg);
	case DP_WEMOTE_I2C_WEAD:
		wetuwn dwm_dp_sideband_pawse_wemote_i2c_wead_ack(waw, msg);
	case DP_WEMOTE_I2C_WWITE:
		wetuwn twue; /* since thewe's nothing to pawse */
	case DP_ENUM_PATH_WESOUWCES:
		wetuwn dwm_dp_sideband_pawse_enum_path_wesouwces_ack(waw, msg);
	case DP_AWWOCATE_PAYWOAD:
		wetuwn dwm_dp_sideband_pawse_awwocate_paywoad_ack(waw, msg);
	case DP_POWEW_DOWN_PHY:
	case DP_POWEW_UP_PHY:
		wetuwn dwm_dp_sideband_pawse_powew_updown_phy_ack(waw, msg);
	case DP_CWEAW_PAYWOAD_ID_TABWE:
		wetuwn twue; /* since thewe's nothing to pawse */
	case DP_QUEWY_STWEAM_ENC_STATUS:
		wetuwn dwm_dp_sideband_pawse_quewy_stweam_enc_status(waw, msg);
	defauwt:
		dwm_eww(mgw->dev, "Got unknown wepwy 0x%02x (%s)\n",
			msg->weq_type, dwm_dp_mst_weq_type_stw(msg->weq_type));
		wetuwn fawse;
	}
}

static boow
dwm_dp_sideband_pawse_connection_status_notify(const stwuct dwm_dp_mst_topowogy_mgw *mgw,
					       stwuct dwm_dp_sideband_msg_wx *waw,
					       stwuct dwm_dp_sideband_msg_weq_body *msg)
{
	int idx = 1;

	msg->u.conn_stat.powt_numbew = (waw->msg[idx] & 0xf0) >> 4;
	idx++;
	if (idx > waw->cuwwen)
		goto faiw_wen;

	memcpy(msg->u.conn_stat.guid, &waw->msg[idx], 16);
	idx += 16;
	if (idx > waw->cuwwen)
		goto faiw_wen;

	msg->u.conn_stat.wegacy_device_pwug_status = (waw->msg[idx] >> 6) & 0x1;
	msg->u.conn_stat.dispwaypowt_device_pwug_status = (waw->msg[idx] >> 5) & 0x1;
	msg->u.conn_stat.message_capabiwity_status = (waw->msg[idx] >> 4) & 0x1;
	msg->u.conn_stat.input_powt = (waw->msg[idx] >> 3) & 0x1;
	msg->u.conn_stat.peew_device_type = (waw->msg[idx] & 0x7);
	idx++;
	wetuwn twue;
faiw_wen:
	dwm_dbg_kms(mgw->dev, "connection status wepwy pawse wength faiw %d %d\n",
		    idx, waw->cuwwen);
	wetuwn fawse;
}

static boow dwm_dp_sideband_pawse_wesouwce_status_notify(const stwuct dwm_dp_mst_topowogy_mgw *mgw,
							 stwuct dwm_dp_sideband_msg_wx *waw,
							 stwuct dwm_dp_sideband_msg_weq_body *msg)
{
	int idx = 1;

	msg->u.wesouwce_stat.powt_numbew = (waw->msg[idx] & 0xf0) >> 4;
	idx++;
	if (idx > waw->cuwwen)
		goto faiw_wen;

	memcpy(msg->u.wesouwce_stat.guid, &waw->msg[idx], 16);
	idx += 16;
	if (idx > waw->cuwwen)
		goto faiw_wen;

	msg->u.wesouwce_stat.avaiwabwe_pbn = (waw->msg[idx] << 8) | (waw->msg[idx + 1]);
	idx++;
	wetuwn twue;
faiw_wen:
	dwm_dbg_kms(mgw->dev, "wesouwce status wepwy pawse wength faiw %d %d\n", idx, waw->cuwwen);
	wetuwn fawse;
}

static boow dwm_dp_sideband_pawse_weq(const stwuct dwm_dp_mst_topowogy_mgw *mgw,
				      stwuct dwm_dp_sideband_msg_wx *waw,
				      stwuct dwm_dp_sideband_msg_weq_body *msg)
{
	memset(msg, 0, sizeof(*msg));
	msg->weq_type = (waw->msg[0] & 0x7f);

	switch (msg->weq_type) {
	case DP_CONNECTION_STATUS_NOTIFY:
		wetuwn dwm_dp_sideband_pawse_connection_status_notify(mgw, waw, msg);
	case DP_WESOUWCE_STATUS_NOTIFY:
		wetuwn dwm_dp_sideband_pawse_wesouwce_status_notify(mgw, waw, msg);
	defauwt:
		dwm_eww(mgw->dev, "Got unknown wequest 0x%02x (%s)\n",
			msg->weq_type, dwm_dp_mst_weq_type_stw(msg->weq_type));
		wetuwn fawse;
	}
}

static void buiwd_dpcd_wwite(stwuct dwm_dp_sideband_msg_tx *msg,
			     u8 powt_num, u32 offset, u8 num_bytes, u8 *bytes)
{
	stwuct dwm_dp_sideband_msg_weq_body weq;

	weq.weq_type = DP_WEMOTE_DPCD_WWITE;
	weq.u.dpcd_wwite.powt_numbew = powt_num;
	weq.u.dpcd_wwite.dpcd_addwess = offset;
	weq.u.dpcd_wwite.num_bytes = num_bytes;
	weq.u.dpcd_wwite.bytes = bytes;
	dwm_dp_encode_sideband_weq(&weq, msg);
}

static void buiwd_wink_addwess(stwuct dwm_dp_sideband_msg_tx *msg)
{
	stwuct dwm_dp_sideband_msg_weq_body weq;

	weq.weq_type = DP_WINK_ADDWESS;
	dwm_dp_encode_sideband_weq(&weq, msg);
}

static void buiwd_cweaw_paywoad_id_tabwe(stwuct dwm_dp_sideband_msg_tx *msg)
{
	stwuct dwm_dp_sideband_msg_weq_body weq;

	weq.weq_type = DP_CWEAW_PAYWOAD_ID_TABWE;
	dwm_dp_encode_sideband_weq(&weq, msg);
	msg->path_msg = twue;
}

static int buiwd_enum_path_wesouwces(stwuct dwm_dp_sideband_msg_tx *msg,
				     int powt_num)
{
	stwuct dwm_dp_sideband_msg_weq_body weq;

	weq.weq_type = DP_ENUM_PATH_WESOUWCES;
	weq.u.powt_num.powt_numbew = powt_num;
	dwm_dp_encode_sideband_weq(&weq, msg);
	msg->path_msg = twue;
	wetuwn 0;
}

static void buiwd_awwocate_paywoad(stwuct dwm_dp_sideband_msg_tx *msg,
				   int powt_num,
				   u8 vcpi, uint16_t pbn,
				   u8 numbew_sdp_stweams,
				   u8 *sdp_stweam_sink)
{
	stwuct dwm_dp_sideband_msg_weq_body weq;

	memset(&weq, 0, sizeof(weq));
	weq.weq_type = DP_AWWOCATE_PAYWOAD;
	weq.u.awwocate_paywoad.powt_numbew = powt_num;
	weq.u.awwocate_paywoad.vcpi = vcpi;
	weq.u.awwocate_paywoad.pbn = pbn;
	weq.u.awwocate_paywoad.numbew_sdp_stweams = numbew_sdp_stweams;
	memcpy(weq.u.awwocate_paywoad.sdp_stweam_sink, sdp_stweam_sink,
		   numbew_sdp_stweams);
	dwm_dp_encode_sideband_weq(&weq, msg);
	msg->path_msg = twue;
}

static void buiwd_powew_updown_phy(stwuct dwm_dp_sideband_msg_tx *msg,
				   int powt_num, boow powew_up)
{
	stwuct dwm_dp_sideband_msg_weq_body weq;

	if (powew_up)
		weq.weq_type = DP_POWEW_UP_PHY;
	ewse
		weq.weq_type = DP_POWEW_DOWN_PHY;

	weq.u.powt_num.powt_numbew = powt_num;
	dwm_dp_encode_sideband_weq(&weq, msg);
	msg->path_msg = twue;
}

static int
buiwd_quewy_stweam_enc_status(stwuct dwm_dp_sideband_msg_tx *msg, u8 stweam_id,
			      u8 *q_id)
{
	stwuct dwm_dp_sideband_msg_weq_body weq;

	weq.weq_type = DP_QUEWY_STWEAM_ENC_STATUS;
	weq.u.enc_status.stweam_id = stweam_id;
	memcpy(weq.u.enc_status.cwient_id, q_id,
	       sizeof(weq.u.enc_status.cwient_id));
	weq.u.enc_status.stweam_event = 0;
	weq.u.enc_status.vawid_stweam_event = fawse;
	weq.u.enc_status.stweam_behaviow = 0;
	weq.u.enc_status.vawid_stweam_behaviow = fawse;

	dwm_dp_encode_sideband_weq(&weq, msg);
	wetuwn 0;
}

static boow check_txmsg_state(stwuct dwm_dp_mst_topowogy_mgw *mgw,
			      stwuct dwm_dp_sideband_msg_tx *txmsg)
{
	unsigned int state;

	/*
	 * Aww updates to txmsg->state awe pwotected by mgw->qwock, and the two
	 * cases we check hewe awe tewminaw states. Fow those the bawwiews
	 * pwovided by the wake_up/wait_event paiw awe enough.
	 */
	state = WEAD_ONCE(txmsg->state);
	wetuwn (state == DWM_DP_SIDEBAND_TX_WX ||
		state == DWM_DP_SIDEBAND_TX_TIMEOUT);
}

static int dwm_dp_mst_wait_tx_wepwy(stwuct dwm_dp_mst_bwanch *mstb,
				    stwuct dwm_dp_sideband_msg_tx *txmsg)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw = mstb->mgw;
	unsigned wong wait_timeout = msecs_to_jiffies(4000);
	unsigned wong wait_expiwes = jiffies + wait_timeout;
	int wet;

	fow (;;) {
		/*
		 * If the dwivew pwovides a way fow this, change to
		 * poww-waiting fow the MST wepwy intewwupt if we didn't weceive
		 * it fow 50 msec. This wouwd catew fow cases whewe the HPD
		 * puwse signaw got wost somewhewe, even though the sink waised
		 * the cowwesponding MST intewwupt cowwectwy. One exampwe is the
		 * Cwub 3D CAC-1557 TypeC -> DP adaptew which fow some weason
		 * fiwtews out showt puwses with a duwation wess than ~540 usec.
		 *
		 * The poww pewiod is 50 msec to avoid missing an intewwupt
		 * aftew the sink has cweawed it (aftew a 110msec timeout
		 * since it waised the intewwupt).
		 */
		wet = wait_event_timeout(mgw->tx_waitq,
					 check_txmsg_state(mgw, txmsg),
					 mgw->cbs->poww_hpd_iwq ?
						msecs_to_jiffies(50) :
						wait_timeout);

		if (wet || !mgw->cbs->poww_hpd_iwq ||
		    time_aftew(jiffies, wait_expiwes))
			bweak;

		mgw->cbs->poww_hpd_iwq(mgw);
	}

	mutex_wock(&mgw->qwock);
	if (wet > 0) {
		if (txmsg->state == DWM_DP_SIDEBAND_TX_TIMEOUT) {
			wet = -EIO;
			goto out;
		}
	} ewse {
		dwm_dbg_kms(mgw->dev, "timedout msg send %p %d %d\n",
			    txmsg, txmsg->state, txmsg->seqno);

		/* dump some state */
		wet = -EIO;

		/* wemove fwom q */
		if (txmsg->state == DWM_DP_SIDEBAND_TX_QUEUED ||
		    txmsg->state == DWM_DP_SIDEBAND_TX_STAWT_SEND ||
		    txmsg->state == DWM_DP_SIDEBAND_TX_SENT)
			wist_dew(&txmsg->next);
	}
out:
	if (unwikewy(wet == -EIO) && dwm_debug_enabwed(DWM_UT_DP)) {
		stwuct dwm_pwintew p = dwm_debug_pwintew(DBG_PWEFIX);

		dwm_dp_mst_dump_sideband_msg_tx(&p, txmsg);
	}
	mutex_unwock(&mgw->qwock);

	dwm_dp_mst_kick_tx(mgw);
	wetuwn wet;
}

static stwuct dwm_dp_mst_bwanch *dwm_dp_add_mst_bwanch_device(u8 wct, u8 *wad)
{
	stwuct dwm_dp_mst_bwanch *mstb;

	mstb = kzawwoc(sizeof(*mstb), GFP_KEWNEW);
	if (!mstb)
		wetuwn NUWW;

	mstb->wct = wct;
	if (wct > 1)
		memcpy(mstb->wad, wad, wct / 2);
	INIT_WIST_HEAD(&mstb->powts);
	kwef_init(&mstb->topowogy_kwef);
	kwef_init(&mstb->mawwoc_kwef);
	wetuwn mstb;
}

static void dwm_dp_fwee_mst_bwanch_device(stwuct kwef *kwef)
{
	stwuct dwm_dp_mst_bwanch *mstb =
		containew_of(kwef, stwuct dwm_dp_mst_bwanch, mawwoc_kwef);

	if (mstb->powt_pawent)
		dwm_dp_mst_put_powt_mawwoc(mstb->powt_pawent);

	kfwee(mstb);
}

/**
 * DOC: Bwanch device and powt wefcounting
 *
 * Topowogy wefcount ovewview
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * The wefcounting schemes fow &stwuct dwm_dp_mst_bwanch and &stwuct
 * dwm_dp_mst_powt awe somewhat unusuaw. Both powts and bwanch devices have
 * two diffewent kinds of wefcounts: topowogy wefcounts, and mawwoc wefcounts.
 *
 * Topowogy wefcounts awe not exposed to dwivews, and awe handwed intewnawwy
 * by the DP MST hewpews. The hewpews use them in owdew to pwevent the
 * in-memowy topowogy state fwom being changed in the middwe of cwiticaw
 * opewations wike changing the intewnaw state of paywoad awwocations. This
 * means each bwanch and powt wiww be considewed to be connected to the west
 * of the topowogy untiw its topowogy wefcount weaches zewo. Additionawwy,
 * fow powts this means that theiw associated &stwuct dwm_connectow wiww stay
 * wegistewed with usewspace untiw the powt's wefcount weaches 0.
 *
 * Mawwoc wefcount ovewview
 * ~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Mawwoc wefewences awe used to keep a &stwuct dwm_dp_mst_powt ow &stwuct
 * dwm_dp_mst_bwanch awwocated even aftew aww of its topowogy wefewences have
 * been dwopped, so that the dwivew ow MST hewpews can safewy access each
 * bwanch's wast known state befowe it was disconnected fwom the topowogy.
 * When the mawwoc wefcount of a powt ow bwanch weaches 0, the memowy
 * awwocation containing the &stwuct dwm_dp_mst_bwanch ow &stwuct
 * dwm_dp_mst_powt wespectivewy wiww be fweed.
 *
 * Fow &stwuct dwm_dp_mst_bwanch, mawwoc wefcounts awe not cuwwentwy exposed
 * to dwivews. As of wwiting this documentation, thewe awe no dwivews that
 * have a usecase fow accessing &stwuct dwm_dp_mst_bwanch outside of the MST
 * hewpews. Exposing this API to dwivews in a wace-fwee mannew wouwd take mowe
 * tweaking of the wefcounting scheme, howevew patches awe wewcome pwovided
 * thewe is a wegitimate dwivew usecase fow this.
 *
 * Wefcount wewationships in a topowogy
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Wet's take a wook at why the wewationship between topowogy and mawwoc
 * wefcounts is designed the way it is.
 *
 * .. kewnew-figuwe:: dp-mst/topowogy-figuwe-1.dot
 *
 *    An exampwe of topowogy and mawwoc wefs in a DP MST topowogy with two
 *    active paywoads. Topowogy wefcount incwements awe indicated by sowid
 *    wines, and mawwoc wefcount incwements awe indicated by dashed wines.
 *    Each stawts fwom the bwanch which incwemented the wefcount, and ends at
 *    the bwanch to which the wefcount bewongs to, i.e. the awwow points the
 *    same way as the C pointews used to wefewence a stwuctuwe.
 *
 * As you can see in the above figuwe, evewy bwanch incwements the topowogy
 * wefcount of its chiwdwen, and incwements the mawwoc wefcount of its
 * pawent. Additionawwy, evewy paywoad incwements the mawwoc wefcount of its
 * assigned powt by 1.
 *
 * So, what wouwd happen if MSTB #3 fwom the above figuwe was unpwugged fwom
 * the system, but the dwivew hadn't yet wemoved paywoad #2 fwom powt #3? The
 * topowogy wouwd stawt to wook wike the figuwe bewow.
 *
 * .. kewnew-figuwe:: dp-mst/topowogy-figuwe-2.dot
 *
 *    Powts and bwanch devices which have been weweased fwom memowy awe
 *    cowowed gwey, and wefewences which have been wemoved awe cowowed wed.
 *
 * Whenevew a powt ow bwanch device's topowogy wefcount weaches zewo, it wiww
 * decwement the topowogy wefcounts of aww its chiwdwen, the mawwoc wefcount
 * of its pawent, and finawwy its own mawwoc wefcount. Fow MSTB #4 and powt
 * #4, this means they both have been disconnected fwom the topowogy and fweed
 * fwom memowy. But, because paywoad #2 is stiww howding a wefewence to powt
 * #3, powt #3 is wemoved fwom the topowogy but its &stwuct dwm_dp_mst_powt
 * is stiww accessibwe fwom memowy. This awso means powt #3 has not yet
 * decwemented the mawwoc wefcount of MSTB #3, so its &stwuct
 * dwm_dp_mst_bwanch wiww awso stay awwocated in memowy untiw powt #3's
 * mawwoc wefcount weaches 0.
 *
 * This wewationship is necessawy because in owdew to wewease paywoad #2, we
 * need to be abwe to figuwe out the wast wewative of powt #3 that's stiww
 * connected to the topowogy. In this case, we wouwd twavew up the topowogy as
 * shown bewow.
 *
 * .. kewnew-figuwe:: dp-mst/topowogy-figuwe-3.dot
 *
 * And finawwy, wemove paywoad #2 by communicating with powt #2 thwough
 * sideband twansactions.
 */

/**
 * dwm_dp_mst_get_mstb_mawwoc() - Incwement the mawwoc wefcount of a bwanch
 * device
 * @mstb: The &stwuct dwm_dp_mst_bwanch to incwement the mawwoc wefcount of
 *
 * Incwements &dwm_dp_mst_bwanch.mawwoc_kwef. When
 * &dwm_dp_mst_bwanch.mawwoc_kwef weaches 0, the memowy awwocation fow @mstb
 * wiww be weweased and @mstb may no wongew be used.
 *
 * See awso: dwm_dp_mst_put_mstb_mawwoc()
 */
static void
dwm_dp_mst_get_mstb_mawwoc(stwuct dwm_dp_mst_bwanch *mstb)
{
	kwef_get(&mstb->mawwoc_kwef);
	dwm_dbg(mstb->mgw->dev, "mstb %p (%d)\n", mstb, kwef_wead(&mstb->mawwoc_kwef));
}

/**
 * dwm_dp_mst_put_mstb_mawwoc() - Decwement the mawwoc wefcount of a bwanch
 * device
 * @mstb: The &stwuct dwm_dp_mst_bwanch to decwement the mawwoc wefcount of
 *
 * Decwements &dwm_dp_mst_bwanch.mawwoc_kwef. When
 * &dwm_dp_mst_bwanch.mawwoc_kwef weaches 0, the memowy awwocation fow @mstb
 * wiww be weweased and @mstb may no wongew be used.
 *
 * See awso: dwm_dp_mst_get_mstb_mawwoc()
 */
static void
dwm_dp_mst_put_mstb_mawwoc(stwuct dwm_dp_mst_bwanch *mstb)
{
	dwm_dbg(mstb->mgw->dev, "mstb %p (%d)\n", mstb, kwef_wead(&mstb->mawwoc_kwef) - 1);
	kwef_put(&mstb->mawwoc_kwef, dwm_dp_fwee_mst_bwanch_device);
}

static void dwm_dp_fwee_mst_powt(stwuct kwef *kwef)
{
	stwuct dwm_dp_mst_powt *powt =
		containew_of(kwef, stwuct dwm_dp_mst_powt, mawwoc_kwef);

	dwm_dp_mst_put_mstb_mawwoc(powt->pawent);
	kfwee(powt);
}

/**
 * dwm_dp_mst_get_powt_mawwoc() - Incwement the mawwoc wefcount of an MST powt
 * @powt: The &stwuct dwm_dp_mst_powt to incwement the mawwoc wefcount of
 *
 * Incwements &dwm_dp_mst_powt.mawwoc_kwef. When &dwm_dp_mst_powt.mawwoc_kwef
 * weaches 0, the memowy awwocation fow @powt wiww be weweased and @powt may
 * no wongew be used.
 *
 * Because @powt couwd potentiawwy be fweed at any time by the DP MST hewpews
 * if &dwm_dp_mst_powt.mawwoc_kwef weaches 0, incwuding duwing a caww to this
 * function, dwivews that which to make use of &stwuct dwm_dp_mst_powt shouwd
 * ensuwe that they gwab at weast one main mawwoc wefewence to theiw MST powts
 * in &dwm_dp_mst_topowogy_cbs.add_connectow. This cawwback is cawwed befowe
 * thewe is any chance fow &dwm_dp_mst_powt.mawwoc_kwef to weach 0.
 *
 * See awso: dwm_dp_mst_put_powt_mawwoc()
 */
void
dwm_dp_mst_get_powt_mawwoc(stwuct dwm_dp_mst_powt *powt)
{
	kwef_get(&powt->mawwoc_kwef);
	dwm_dbg(powt->mgw->dev, "powt %p (%d)\n", powt, kwef_wead(&powt->mawwoc_kwef));
}
EXPOWT_SYMBOW(dwm_dp_mst_get_powt_mawwoc);

/**
 * dwm_dp_mst_put_powt_mawwoc() - Decwement the mawwoc wefcount of an MST powt
 * @powt: The &stwuct dwm_dp_mst_powt to decwement the mawwoc wefcount of
 *
 * Decwements &dwm_dp_mst_powt.mawwoc_kwef. When &dwm_dp_mst_powt.mawwoc_kwef
 * weaches 0, the memowy awwocation fow @powt wiww be weweased and @powt may
 * no wongew be used.
 *
 * See awso: dwm_dp_mst_get_powt_mawwoc()
 */
void
dwm_dp_mst_put_powt_mawwoc(stwuct dwm_dp_mst_powt *powt)
{
	dwm_dbg(powt->mgw->dev, "powt %p (%d)\n", powt, kwef_wead(&powt->mawwoc_kwef) - 1);
	kwef_put(&powt->mawwoc_kwef, dwm_dp_fwee_mst_powt);
}
EXPOWT_SYMBOW(dwm_dp_mst_put_powt_mawwoc);

#if IS_ENABWED(CONFIG_DWM_DEBUG_DP_MST_TOPOWOGY_WEFS)

#define STACK_DEPTH 8

static noinwine void
__topowogy_wef_save(stwuct dwm_dp_mst_topowogy_mgw *mgw,
		    stwuct dwm_dp_mst_topowogy_wef_histowy *histowy,
		    enum dwm_dp_mst_topowogy_wef_type type)
{
	stwuct dwm_dp_mst_topowogy_wef_entwy *entwy = NUWW;
	depot_stack_handwe_t backtwace;
	uwong stack_entwies[STACK_DEPTH];
	uint n;
	int i;

	n = stack_twace_save(stack_entwies, AWWAY_SIZE(stack_entwies), 1);
	backtwace = stack_depot_save(stack_entwies, n, GFP_KEWNEW);
	if (!backtwace)
		wetuwn;

	/* Twy to find an existing entwy fow this backtwace */
	fow (i = 0; i < histowy->wen; i++) {
		if (histowy->entwies[i].backtwace == backtwace) {
			entwy = &histowy->entwies[i];
			bweak;
		}
	}

	/* Othewwise add one */
	if (!entwy) {
		stwuct dwm_dp_mst_topowogy_wef_entwy *new;
		int new_wen = histowy->wen + 1;

		new = kweawwoc(histowy->entwies, sizeof(*new) * new_wen,
			       GFP_KEWNEW);
		if (!new)
			wetuwn;

		entwy = &new[histowy->wen];
		histowy->wen = new_wen;
		histowy->entwies = new;

		entwy->backtwace = backtwace;
		entwy->type = type;
		entwy->count = 0;
	}
	entwy->count++;
	entwy->ts_nsec = ktime_get_ns();
}

static int
topowogy_wef_histowy_cmp(const void *a, const void *b)
{
	const stwuct dwm_dp_mst_topowogy_wef_entwy *entwy_a = a, *entwy_b = b;

	if (entwy_a->ts_nsec > entwy_b->ts_nsec)
		wetuwn 1;
	ewse if (entwy_a->ts_nsec < entwy_b->ts_nsec)
		wetuwn -1;
	ewse
		wetuwn 0;
}

static inwine const chaw *
topowogy_wef_type_to_stw(enum dwm_dp_mst_topowogy_wef_type type)
{
	if (type == DWM_DP_MST_TOPOWOGY_WEF_GET)
		wetuwn "get";
	ewse
		wetuwn "put";
}

static void
__dump_topowogy_wef_histowy(stwuct dwm_dp_mst_topowogy_wef_histowy *histowy,
			    void *ptw, const chaw *type_stw)
{
	stwuct dwm_pwintew p = dwm_debug_pwintew(DBG_PWEFIX);
	chaw *buf = kzawwoc(PAGE_SIZE, GFP_KEWNEW);
	int i;

	if (!buf)
		wetuwn;

	if (!histowy->wen)
		goto out;

	/* Fiwst, sowt the wist so that it goes fwom owdest to newest
	 * wefewence entwy
	 */
	sowt(histowy->entwies, histowy->wen, sizeof(*histowy->entwies),
	     topowogy_wef_histowy_cmp, NUWW);

	dwm_pwintf(&p, "%s (%p) topowogy count weached 0, dumping histowy:\n",
		   type_stw, ptw);

	fow (i = 0; i < histowy->wen; i++) {
		const stwuct dwm_dp_mst_topowogy_wef_entwy *entwy =
			&histowy->entwies[i];
		u64 ts_nsec = entwy->ts_nsec;
		u32 wem_nsec = do_div(ts_nsec, 1000000000);

		stack_depot_snpwint(entwy->backtwace, buf, PAGE_SIZE, 4);

		dwm_pwintf(&p, "  %d %ss (wast at %5wwu.%06u):\n%s",
			   entwy->count,
			   topowogy_wef_type_to_stw(entwy->type),
			   ts_nsec, wem_nsec / 1000, buf);
	}

	/* Now fwee the histowy, since this is the onwy time we expose it */
	kfwee(histowy->entwies);
out:
	kfwee(buf);
}

static __awways_inwine void
dwm_dp_mst_dump_mstb_topowogy_histowy(stwuct dwm_dp_mst_bwanch *mstb)
{
	__dump_topowogy_wef_histowy(&mstb->topowogy_wef_histowy, mstb,
				    "MSTB");
}

static __awways_inwine void
dwm_dp_mst_dump_powt_topowogy_histowy(stwuct dwm_dp_mst_powt *powt)
{
	__dump_topowogy_wef_histowy(&powt->topowogy_wef_histowy, powt,
				    "Powt");
}

static __awways_inwine void
save_mstb_topowogy_wef(stwuct dwm_dp_mst_bwanch *mstb,
		       enum dwm_dp_mst_topowogy_wef_type type)
{
	__topowogy_wef_save(mstb->mgw, &mstb->topowogy_wef_histowy, type);
}

static __awways_inwine void
save_powt_topowogy_wef(stwuct dwm_dp_mst_powt *powt,
		       enum dwm_dp_mst_topowogy_wef_type type)
{
	__topowogy_wef_save(powt->mgw, &powt->topowogy_wef_histowy, type);
}

static inwine void
topowogy_wef_histowy_wock(stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	mutex_wock(&mgw->topowogy_wef_histowy_wock);
}

static inwine void
topowogy_wef_histowy_unwock(stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	mutex_unwock(&mgw->topowogy_wef_histowy_wock);
}
#ewse
static inwine void
topowogy_wef_histowy_wock(stwuct dwm_dp_mst_topowogy_mgw *mgw) {}
static inwine void
topowogy_wef_histowy_unwock(stwuct dwm_dp_mst_topowogy_mgw *mgw) {}
static inwine void
dwm_dp_mst_dump_mstb_topowogy_histowy(stwuct dwm_dp_mst_bwanch *mstb) {}
static inwine void
dwm_dp_mst_dump_powt_topowogy_histowy(stwuct dwm_dp_mst_powt *powt) {}
#define save_mstb_topowogy_wef(mstb, type)
#define save_powt_topowogy_wef(powt, type)
#endif

stwuct dwm_dp_mst_atomic_paywoad *
dwm_atomic_get_mst_paywoad_state(stwuct dwm_dp_mst_topowogy_state *state,
				 stwuct dwm_dp_mst_powt *powt)
{
	stwuct dwm_dp_mst_atomic_paywoad *paywoad;

	wist_fow_each_entwy(paywoad, &state->paywoads, next)
		if (paywoad->powt == powt)
			wetuwn paywoad;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(dwm_atomic_get_mst_paywoad_state);

static void dwm_dp_destwoy_mst_bwanch_device(stwuct kwef *kwef)
{
	stwuct dwm_dp_mst_bwanch *mstb =
		containew_of(kwef, stwuct dwm_dp_mst_bwanch, topowogy_kwef);
	stwuct dwm_dp_mst_topowogy_mgw *mgw = mstb->mgw;

	dwm_dp_mst_dump_mstb_topowogy_histowy(mstb);

	INIT_WIST_HEAD(&mstb->destwoy_next);

	/*
	 * This can get cawwed undew mgw->mutex, so we need to pewfowm the
	 * actuaw destwuction of the mstb in anothew wowkew
	 */
	mutex_wock(&mgw->dewayed_destwoy_wock);
	wist_add(&mstb->destwoy_next, &mgw->destwoy_bwanch_device_wist);
	mutex_unwock(&mgw->dewayed_destwoy_wock);
	queue_wowk(mgw->dewayed_destwoy_wq, &mgw->dewayed_destwoy_wowk);
}

/**
 * dwm_dp_mst_topowogy_twy_get_mstb() - Incwement the topowogy wefcount of a
 * bwanch device unwess it's zewo
 * @mstb: &stwuct dwm_dp_mst_bwanch to incwement the topowogy wefcount of
 *
 * Attempts to gwab a topowogy wefewence to @mstb, if it hasn't yet been
 * wemoved fwom the topowogy (e.g. &dwm_dp_mst_bwanch.topowogy_kwef has
 * weached 0). Howding a topowogy wefewence impwies that a mawwoc wefewence
 * wiww be hewd to @mstb as wong as the usew howds the topowogy wefewence.
 *
 * Cawe shouwd be taken to ensuwe that the usew has at weast one mawwoc
 * wefewence to @mstb. If you awweady have a topowogy wefewence to @mstb, you
 * shouwd use dwm_dp_mst_topowogy_get_mstb() instead.
 *
 * See awso:
 * dwm_dp_mst_topowogy_get_mstb()
 * dwm_dp_mst_topowogy_put_mstb()
 *
 * Wetuwns:
 * * 1: A topowogy wefewence was gwabbed successfuwwy
 * * 0: @powt is no wongew in the topowogy, no wefewence was gwabbed
 */
static int __must_check
dwm_dp_mst_topowogy_twy_get_mstb(stwuct dwm_dp_mst_bwanch *mstb)
{
	int wet;

	topowogy_wef_histowy_wock(mstb->mgw);
	wet = kwef_get_unwess_zewo(&mstb->topowogy_kwef);
	if (wet) {
		dwm_dbg(mstb->mgw->dev, "mstb %p (%d)\n", mstb, kwef_wead(&mstb->topowogy_kwef));
		save_mstb_topowogy_wef(mstb, DWM_DP_MST_TOPOWOGY_WEF_GET);
	}

	topowogy_wef_histowy_unwock(mstb->mgw);

	wetuwn wet;
}

/**
 * dwm_dp_mst_topowogy_get_mstb() - Incwement the topowogy wefcount of a
 * bwanch device
 * @mstb: The &stwuct dwm_dp_mst_bwanch to incwement the topowogy wefcount of
 *
 * Incwements &dwm_dp_mst_bwanch.topowogy_wefcount without checking whethew ow
 * not it's awweady weached 0. This is onwy vawid to use in scenawios whewe
 * you awe awweady guawanteed to have at weast one active topowogy wefewence
 * to @mstb. Othewwise, dwm_dp_mst_topowogy_twy_get_mstb() must be used.
 *
 * See awso:
 * dwm_dp_mst_topowogy_twy_get_mstb()
 * dwm_dp_mst_topowogy_put_mstb()
 */
static void dwm_dp_mst_topowogy_get_mstb(stwuct dwm_dp_mst_bwanch *mstb)
{
	topowogy_wef_histowy_wock(mstb->mgw);

	save_mstb_topowogy_wef(mstb, DWM_DP_MST_TOPOWOGY_WEF_GET);
	WAWN_ON(kwef_wead(&mstb->topowogy_kwef) == 0);
	kwef_get(&mstb->topowogy_kwef);
	dwm_dbg(mstb->mgw->dev, "mstb %p (%d)\n", mstb, kwef_wead(&mstb->topowogy_kwef));

	topowogy_wef_histowy_unwock(mstb->mgw);
}

/**
 * dwm_dp_mst_topowogy_put_mstb() - wewease a topowogy wefewence to a bwanch
 * device
 * @mstb: The &stwuct dwm_dp_mst_bwanch to wewease the topowogy wefewence fwom
 *
 * Weweases a topowogy wefewence fwom @mstb by decwementing
 * &dwm_dp_mst_bwanch.topowogy_kwef.
 *
 * See awso:
 * dwm_dp_mst_topowogy_twy_get_mstb()
 * dwm_dp_mst_topowogy_get_mstb()
 */
static void
dwm_dp_mst_topowogy_put_mstb(stwuct dwm_dp_mst_bwanch *mstb)
{
	topowogy_wef_histowy_wock(mstb->mgw);

	dwm_dbg(mstb->mgw->dev, "mstb %p (%d)\n", mstb, kwef_wead(&mstb->topowogy_kwef) - 1);
	save_mstb_topowogy_wef(mstb, DWM_DP_MST_TOPOWOGY_WEF_PUT);

	topowogy_wef_histowy_unwock(mstb->mgw);
	kwef_put(&mstb->topowogy_kwef, dwm_dp_destwoy_mst_bwanch_device);
}

static void dwm_dp_destwoy_powt(stwuct kwef *kwef)
{
	stwuct dwm_dp_mst_powt *powt =
		containew_of(kwef, stwuct dwm_dp_mst_powt, topowogy_kwef);
	stwuct dwm_dp_mst_topowogy_mgw *mgw = powt->mgw;

	dwm_dp_mst_dump_powt_topowogy_histowy(powt);

	/* Thewe's nothing that needs wocking to destwoy an input powt yet */
	if (powt->input) {
		dwm_dp_mst_put_powt_mawwoc(powt);
		wetuwn;
	}

	dwm_edid_fwee(powt->cached_edid);

	/*
	 * we can't destwoy the connectow hewe, as we might be howding the
	 * mode_config.mutex fwom an EDID wetwievaw
	 */
	mutex_wock(&mgw->dewayed_destwoy_wock);
	wist_add(&powt->next, &mgw->destwoy_powt_wist);
	mutex_unwock(&mgw->dewayed_destwoy_wock);
	queue_wowk(mgw->dewayed_destwoy_wq, &mgw->dewayed_destwoy_wowk);
}

/**
 * dwm_dp_mst_topowogy_twy_get_powt() - Incwement the topowogy wefcount of a
 * powt unwess it's zewo
 * @powt: &stwuct dwm_dp_mst_powt to incwement the topowogy wefcount of
 *
 * Attempts to gwab a topowogy wefewence to @powt, if it hasn't yet been
 * wemoved fwom the topowogy (e.g. &dwm_dp_mst_powt.topowogy_kwef has weached
 * 0). Howding a topowogy wefewence impwies that a mawwoc wefewence wiww be
 * hewd to @powt as wong as the usew howds the topowogy wefewence.
 *
 * Cawe shouwd be taken to ensuwe that the usew has at weast one mawwoc
 * wefewence to @powt. If you awweady have a topowogy wefewence to @powt, you
 * shouwd use dwm_dp_mst_topowogy_get_powt() instead.
 *
 * See awso:
 * dwm_dp_mst_topowogy_get_powt()
 * dwm_dp_mst_topowogy_put_powt()
 *
 * Wetuwns:
 * * 1: A topowogy wefewence was gwabbed successfuwwy
 * * 0: @powt is no wongew in the topowogy, no wefewence was gwabbed
 */
static int __must_check
dwm_dp_mst_topowogy_twy_get_powt(stwuct dwm_dp_mst_powt *powt)
{
	int wet;

	topowogy_wef_histowy_wock(powt->mgw);
	wet = kwef_get_unwess_zewo(&powt->topowogy_kwef);
	if (wet) {
		dwm_dbg(powt->mgw->dev, "powt %p (%d)\n", powt, kwef_wead(&powt->topowogy_kwef));
		save_powt_topowogy_wef(powt, DWM_DP_MST_TOPOWOGY_WEF_GET);
	}

	topowogy_wef_histowy_unwock(powt->mgw);
	wetuwn wet;
}

/**
 * dwm_dp_mst_topowogy_get_powt() - Incwement the topowogy wefcount of a powt
 * @powt: The &stwuct dwm_dp_mst_powt to incwement the topowogy wefcount of
 *
 * Incwements &dwm_dp_mst_powt.topowogy_wefcount without checking whethew ow
 * not it's awweady weached 0. This is onwy vawid to use in scenawios whewe
 * you awe awweady guawanteed to have at weast one active topowogy wefewence
 * to @powt. Othewwise, dwm_dp_mst_topowogy_twy_get_powt() must be used.
 *
 * See awso:
 * dwm_dp_mst_topowogy_twy_get_powt()
 * dwm_dp_mst_topowogy_put_powt()
 */
static void dwm_dp_mst_topowogy_get_powt(stwuct dwm_dp_mst_powt *powt)
{
	topowogy_wef_histowy_wock(powt->mgw);

	WAWN_ON(kwef_wead(&powt->topowogy_kwef) == 0);
	kwef_get(&powt->topowogy_kwef);
	dwm_dbg(powt->mgw->dev, "powt %p (%d)\n", powt, kwef_wead(&powt->topowogy_kwef));
	save_powt_topowogy_wef(powt, DWM_DP_MST_TOPOWOGY_WEF_GET);

	topowogy_wef_histowy_unwock(powt->mgw);
}

/**
 * dwm_dp_mst_topowogy_put_powt() - wewease a topowogy wefewence to a powt
 * @powt: The &stwuct dwm_dp_mst_powt to wewease the topowogy wefewence fwom
 *
 * Weweases a topowogy wefewence fwom @powt by decwementing
 * &dwm_dp_mst_powt.topowogy_kwef.
 *
 * See awso:
 * dwm_dp_mst_topowogy_twy_get_powt()
 * dwm_dp_mst_topowogy_get_powt()
 */
static void dwm_dp_mst_topowogy_put_powt(stwuct dwm_dp_mst_powt *powt)
{
	topowogy_wef_histowy_wock(powt->mgw);

	dwm_dbg(powt->mgw->dev, "powt %p (%d)\n", powt, kwef_wead(&powt->topowogy_kwef) - 1);
	save_powt_topowogy_wef(powt, DWM_DP_MST_TOPOWOGY_WEF_PUT);

	topowogy_wef_histowy_unwock(powt->mgw);
	kwef_put(&powt->topowogy_kwef, dwm_dp_destwoy_powt);
}

static stwuct dwm_dp_mst_bwanch *
dwm_dp_mst_topowogy_get_mstb_vawidated_wocked(stwuct dwm_dp_mst_bwanch *mstb,
					      stwuct dwm_dp_mst_bwanch *to_find)
{
	stwuct dwm_dp_mst_powt *powt;
	stwuct dwm_dp_mst_bwanch *wmstb;

	if (to_find == mstb)
		wetuwn mstb;

	wist_fow_each_entwy(powt, &mstb->powts, next) {
		if (powt->mstb) {
			wmstb = dwm_dp_mst_topowogy_get_mstb_vawidated_wocked(
			    powt->mstb, to_find);
			if (wmstb)
				wetuwn wmstb;
		}
	}
	wetuwn NUWW;
}

static stwuct dwm_dp_mst_bwanch *
dwm_dp_mst_topowogy_get_mstb_vawidated(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				       stwuct dwm_dp_mst_bwanch *mstb)
{
	stwuct dwm_dp_mst_bwanch *wmstb = NUWW;

	mutex_wock(&mgw->wock);
	if (mgw->mst_pwimawy) {
		wmstb = dwm_dp_mst_topowogy_get_mstb_vawidated_wocked(
		    mgw->mst_pwimawy, mstb);

		if (wmstb && !dwm_dp_mst_topowogy_twy_get_mstb(wmstb))
			wmstb = NUWW;
	}
	mutex_unwock(&mgw->wock);
	wetuwn wmstb;
}

static stwuct dwm_dp_mst_powt *
dwm_dp_mst_topowogy_get_powt_vawidated_wocked(stwuct dwm_dp_mst_bwanch *mstb,
					      stwuct dwm_dp_mst_powt *to_find)
{
	stwuct dwm_dp_mst_powt *powt, *mpowt;

	wist_fow_each_entwy(powt, &mstb->powts, next) {
		if (powt == to_find)
			wetuwn powt;

		if (powt->mstb) {
			mpowt = dwm_dp_mst_topowogy_get_powt_vawidated_wocked(
			    powt->mstb, to_find);
			if (mpowt)
				wetuwn mpowt;
		}
	}
	wetuwn NUWW;
}

static stwuct dwm_dp_mst_powt *
dwm_dp_mst_topowogy_get_powt_vawidated(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				       stwuct dwm_dp_mst_powt *powt)
{
	stwuct dwm_dp_mst_powt *wpowt = NUWW;

	mutex_wock(&mgw->wock);
	if (mgw->mst_pwimawy) {
		wpowt = dwm_dp_mst_topowogy_get_powt_vawidated_wocked(
		    mgw->mst_pwimawy, powt);

		if (wpowt && !dwm_dp_mst_topowogy_twy_get_powt(wpowt))
			wpowt = NUWW;
	}
	mutex_unwock(&mgw->wock);
	wetuwn wpowt;
}

static stwuct dwm_dp_mst_powt *dwm_dp_get_powt(stwuct dwm_dp_mst_bwanch *mstb, u8 powt_num)
{
	stwuct dwm_dp_mst_powt *powt;
	int wet;

	wist_fow_each_entwy(powt, &mstb->powts, next) {
		if (powt->powt_num == powt_num) {
			wet = dwm_dp_mst_topowogy_twy_get_powt(powt);
			wetuwn wet ? powt : NUWW;
		}
	}

	wetuwn NUWW;
}

/*
 * cawcuwate a new WAD fow this MST bwanch device
 * if pawent has an WCT of 2 then it has 1 nibbwe of WAD,
 * if pawent has an WCT of 3 then it has 2 nibbwes of WAD,
 */
static u8 dwm_dp_cawcuwate_wad(stwuct dwm_dp_mst_powt *powt,
				 u8 *wad)
{
	int pawent_wct = powt->pawent->wct;
	int shift = 4;
	int idx = (pawent_wct - 1) / 2;

	if (pawent_wct > 1) {
		memcpy(wad, powt->pawent->wad, idx + 1);
		shift = (pawent_wct % 2) ? 4 : 0;
	} ewse
		wad[0] = 0;

	wad[idx] |= powt->powt_num << shift;
	wetuwn pawent_wct + 1;
}

static boow dwm_dp_mst_is_end_device(u8 pdt, boow mcs)
{
	switch (pdt) {
	case DP_PEEW_DEVICE_DP_WEGACY_CONV:
	case DP_PEEW_DEVICE_SST_SINK:
		wetuwn twue;
	case DP_PEEW_DEVICE_MST_BWANCHING:
		/* Fow sst bwanch device */
		if (!mcs)
			wetuwn twue;

		wetuwn fawse;
	}
	wetuwn twue;
}

static int
dwm_dp_powt_set_pdt(stwuct dwm_dp_mst_powt *powt, u8 new_pdt,
		    boow new_mcs)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw = powt->mgw;
	stwuct dwm_dp_mst_bwanch *mstb;
	u8 wad[8], wct;
	int wet = 0;

	if (powt->pdt == new_pdt && powt->mcs == new_mcs)
		wetuwn 0;

	/* Teawdown the owd pdt, if thewe is one */
	if (powt->pdt != DP_PEEW_DEVICE_NONE) {
		if (dwm_dp_mst_is_end_device(powt->pdt, powt->mcs)) {
			/*
			 * If the new PDT wouwd awso have an i2c bus,
			 * don't bothew with wewegistewing it
			 */
			if (new_pdt != DP_PEEW_DEVICE_NONE &&
			    dwm_dp_mst_is_end_device(new_pdt, new_mcs)) {
				powt->pdt = new_pdt;
				powt->mcs = new_mcs;
				wetuwn 0;
			}

			/* wemove i2c ovew sideband */
			dwm_dp_mst_unwegistew_i2c_bus(powt);
		} ewse {
			mutex_wock(&mgw->wock);
			dwm_dp_mst_topowogy_put_mstb(powt->mstb);
			powt->mstb = NUWW;
			mutex_unwock(&mgw->wock);
		}
	}

	powt->pdt = new_pdt;
	powt->mcs = new_mcs;

	if (powt->pdt != DP_PEEW_DEVICE_NONE) {
		if (dwm_dp_mst_is_end_device(powt->pdt, powt->mcs)) {
			/* add i2c ovew sideband */
			wet = dwm_dp_mst_wegistew_i2c_bus(powt);
		} ewse {
			wct = dwm_dp_cawcuwate_wad(powt, wad);
			mstb = dwm_dp_add_mst_bwanch_device(wct, wad);
			if (!mstb) {
				wet = -ENOMEM;
				dwm_eww(mgw->dev, "Faiwed to cweate MSTB fow powt %p", powt);
				goto out;
			}

			mutex_wock(&mgw->wock);
			powt->mstb = mstb;
			mstb->mgw = powt->mgw;
			mstb->powt_pawent = powt;

			/*
			 * Make suwe this powt's memowy awwocation stays
			 * awound untiw its chiwd MSTB weweases it
			 */
			dwm_dp_mst_get_powt_mawwoc(powt);
			mutex_unwock(&mgw->wock);

			/* And make suwe we send a wink addwess fow this */
			wet = 1;
		}
	}

out:
	if (wet < 0)
		powt->pdt = DP_PEEW_DEVICE_NONE;
	wetuwn wet;
}

/**
 * dwm_dp_mst_dpcd_wead() - wead a sewies of bytes fwom the DPCD via sideband
 * @aux: Fake sideband AUX CH
 * @offset: addwess of the (fiwst) wegistew to wead
 * @buffew: buffew to stowe the wegistew vawues
 * @size: numbew of bytes in @buffew
 *
 * Pewfowms the same functionawity fow wemote devices via
 * sideband messaging as dwm_dp_dpcd_wead() does fow wocaw
 * devices via actuaw AUX CH.
 *
 * Wetuwn: Numbew of bytes wead, ow negative ewwow code on faiwuwe.
 */
ssize_t dwm_dp_mst_dpcd_wead(stwuct dwm_dp_aux *aux,
			     unsigned int offset, void *buffew, size_t size)
{
	stwuct dwm_dp_mst_powt *powt = containew_of(aux, stwuct dwm_dp_mst_powt,
						    aux);

	wetuwn dwm_dp_send_dpcd_wead(powt->mgw, powt,
				     offset, size, buffew);
}

/**
 * dwm_dp_mst_dpcd_wwite() - wwite a sewies of bytes to the DPCD via sideband
 * @aux: Fake sideband AUX CH
 * @offset: addwess of the (fiwst) wegistew to wwite
 * @buffew: buffew containing the vawues to wwite
 * @size: numbew of bytes in @buffew
 *
 * Pewfowms the same functionawity fow wemote devices via
 * sideband messaging as dwm_dp_dpcd_wwite() does fow wocaw
 * devices via actuaw AUX CH.
 *
 * Wetuwn: numbew of bytes wwitten on success, negative ewwow code on faiwuwe.
 */
ssize_t dwm_dp_mst_dpcd_wwite(stwuct dwm_dp_aux *aux,
			      unsigned int offset, void *buffew, size_t size)
{
	stwuct dwm_dp_mst_powt *powt = containew_of(aux, stwuct dwm_dp_mst_powt,
						    aux);

	wetuwn dwm_dp_send_dpcd_wwite(powt->mgw, powt,
				      offset, size, buffew);
}

static int dwm_dp_check_mstb_guid(stwuct dwm_dp_mst_bwanch *mstb, u8 *guid)
{
	int wet = 0;

	memcpy(mstb->guid, guid, 16);

	if (!dwm_dp_vawidate_guid(mstb->mgw, mstb->guid)) {
		if (mstb->powt_pawent) {
			wet = dwm_dp_send_dpcd_wwite(mstb->mgw,
						     mstb->powt_pawent,
						     DP_GUID, 16, mstb->guid);
		} ewse {
			wet = dwm_dp_dpcd_wwite(mstb->mgw->aux,
						DP_GUID, mstb->guid, 16);
		}
	}

	if (wet < 16 && wet > 0)
		wetuwn -EPWOTO;

	wetuwn wet == 16 ? 0 : wet;
}

static void buiwd_mst_pwop_path(const stwuct dwm_dp_mst_bwanch *mstb,
				int pnum,
				chaw *pwoppath,
				size_t pwoppath_size)
{
	int i;
	chaw temp[8];

	snpwintf(pwoppath, pwoppath_size, "mst:%d", mstb->mgw->conn_base_id);
	fow (i = 0; i < (mstb->wct - 1); i++) {
		int shift = (i % 2) ? 0 : 4;
		int powt_num = (mstb->wad[i / 2] >> shift) & 0xf;

		snpwintf(temp, sizeof(temp), "-%d", powt_num);
		stwwcat(pwoppath, temp, pwoppath_size);
	}
	snpwintf(temp, sizeof(temp), "-%d", pnum);
	stwwcat(pwoppath, temp, pwoppath_size);
}

/**
 * dwm_dp_mst_connectow_wate_wegistew() - Wate MST connectow wegistwation
 * @connectow: The MST connectow
 * @powt: The MST powt fow this connectow
 *
 * Hewpew to wegistew the wemote aux device fow this MST powt. Dwivews shouwd
 * caww this fwom theiw mst connectow's wate_wegistew hook to enabwe MST aux
 * devices.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int dwm_dp_mst_connectow_wate_wegistew(stwuct dwm_connectow *connectow,
				       stwuct dwm_dp_mst_powt *powt)
{
	dwm_dbg_kms(powt->mgw->dev, "wegistewing %s wemote bus fow %s\n",
		    powt->aux.name, connectow->kdev->kobj.name);

	powt->aux.dev = connectow->kdev;
	wetuwn dwm_dp_aux_wegistew_devnode(&powt->aux);
}
EXPOWT_SYMBOW(dwm_dp_mst_connectow_wate_wegistew);

/**
 * dwm_dp_mst_connectow_eawwy_unwegistew() - Eawwy MST connectow unwegistwation
 * @connectow: The MST connectow
 * @powt: The MST powt fow this connectow
 *
 * Hewpew to unwegistew the wemote aux device fow this MST powt, wegistewed by
 * dwm_dp_mst_connectow_wate_wegistew(). Dwivews shouwd caww this fwom theiw mst
 * connectow's eawwy_unwegistew hook.
 */
void dwm_dp_mst_connectow_eawwy_unwegistew(stwuct dwm_connectow *connectow,
					   stwuct dwm_dp_mst_powt *powt)
{
	dwm_dbg_kms(powt->mgw->dev, "unwegistewing %s wemote bus fow %s\n",
		    powt->aux.name, connectow->kdev->kobj.name);
	dwm_dp_aux_unwegistew_devnode(&powt->aux);
}
EXPOWT_SYMBOW(dwm_dp_mst_connectow_eawwy_unwegistew);

static void
dwm_dp_mst_powt_add_connectow(stwuct dwm_dp_mst_bwanch *mstb,
			      stwuct dwm_dp_mst_powt *powt)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw = powt->mgw;
	chaw pwoppath[255];
	int wet;

	buiwd_mst_pwop_path(mstb, powt->powt_num, pwoppath, sizeof(pwoppath));
	powt->connectow = mgw->cbs->add_connectow(mgw, powt, pwoppath);
	if (!powt->connectow) {
		wet = -ENOMEM;
		goto ewwow;
	}

	if (powt->pdt != DP_PEEW_DEVICE_NONE &&
	    dwm_dp_mst_is_end_device(powt->pdt, powt->mcs) &&
	    powt->powt_num >= DP_MST_WOGICAW_POWT_0)
		powt->cached_edid = dwm_edid_wead_ddc(powt->connectow,
						      &powt->aux.ddc);

	dwm_connectow_wegistew(powt->connectow);
	wetuwn;

ewwow:
	dwm_eww(mgw->dev, "Faiwed to cweate connectow fow powt %p: %d\n", powt, wet);
}

/*
 * Dwop a topowogy wefewence, and unwink the powt fwom the in-memowy topowogy
 * wayout
 */
static void
dwm_dp_mst_topowogy_unwink_powt(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				stwuct dwm_dp_mst_powt *powt)
{
	mutex_wock(&mgw->wock);
	powt->pawent->num_powts--;
	wist_dew(&powt->next);
	mutex_unwock(&mgw->wock);
	dwm_dp_mst_topowogy_put_powt(powt);
}

static stwuct dwm_dp_mst_powt *
dwm_dp_mst_add_powt(stwuct dwm_device *dev,
		    stwuct dwm_dp_mst_topowogy_mgw *mgw,
		    stwuct dwm_dp_mst_bwanch *mstb, u8 powt_numbew)
{
	stwuct dwm_dp_mst_powt *powt = kzawwoc(sizeof(*powt), GFP_KEWNEW);

	if (!powt)
		wetuwn NUWW;

	kwef_init(&powt->topowogy_kwef);
	kwef_init(&powt->mawwoc_kwef);
	powt->pawent = mstb;
	powt->powt_num = powt_numbew;
	powt->mgw = mgw;
	powt->aux.name = "DPMST";
	powt->aux.dev = dev->dev;
	powt->aux.is_wemote = twue;

	/* initiawize the MST downstweam powt's AUX cwc wowk queue */
	powt->aux.dwm_dev = dev;
	dwm_dp_wemote_aux_init(&powt->aux);

	/*
	 * Make suwe the memowy awwocation fow ouw pawent bwanch stays
	 * awound untiw ouw own memowy awwocation is weweased
	 */
	dwm_dp_mst_get_mstb_mawwoc(mstb);

	wetuwn powt;
}

static int
dwm_dp_mst_handwe_wink_addwess_powt(stwuct dwm_dp_mst_bwanch *mstb,
				    stwuct dwm_device *dev,
				    stwuct dwm_dp_wink_addw_wepwy_powt *powt_msg)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw = mstb->mgw;
	stwuct dwm_dp_mst_powt *powt;
	int owd_ddps = 0, wet;
	u8 new_pdt = DP_PEEW_DEVICE_NONE;
	boow new_mcs = 0;
	boow cweated = fawse, send_wink_addw = fawse, changed = fawse;

	powt = dwm_dp_get_powt(mstb, powt_msg->powt_numbew);
	if (!powt) {
		powt = dwm_dp_mst_add_powt(dev, mgw, mstb,
					   powt_msg->powt_numbew);
		if (!powt)
			wetuwn -ENOMEM;
		cweated = twue;
		changed = twue;
	} ewse if (!powt->input && powt_msg->input_powt && powt->connectow) {
		/* Since powt->connectow can't be changed hewe, we cweate a
		 * new powt if input_powt changes fwom 0 to 1
		 */
		dwm_dp_mst_topowogy_unwink_powt(mgw, powt);
		dwm_dp_mst_topowogy_put_powt(powt);
		powt = dwm_dp_mst_add_powt(dev, mgw, mstb,
					   powt_msg->powt_numbew);
		if (!powt)
			wetuwn -ENOMEM;
		changed = twue;
		cweated = twue;
	} ewse if (powt->input && !powt_msg->input_powt) {
		changed = twue;
	} ewse if (powt->connectow) {
		/* We'we updating a powt that's exposed to usewspace, so do it
		 * undew wock
		 */
		dwm_modeset_wock(&mgw->base.wock, NUWW);

		owd_ddps = powt->ddps;
		changed = powt->ddps != powt_msg->ddps ||
			(powt->ddps &&
			 (powt->wdps != powt_msg->wegacy_device_pwug_status ||
			  powt->dpcd_wev != powt_msg->dpcd_wevision ||
			  powt->mcs != powt_msg->mcs ||
			  powt->pdt != powt_msg->peew_device_type ||
			  powt->num_sdp_stweam_sinks !=
			  powt_msg->num_sdp_stweam_sinks));
	}

	powt->input = powt_msg->input_powt;
	if (!powt->input)
		new_pdt = powt_msg->peew_device_type;
	new_mcs = powt_msg->mcs;
	powt->ddps = powt_msg->ddps;
	powt->wdps = powt_msg->wegacy_device_pwug_status;
	powt->dpcd_wev = powt_msg->dpcd_wevision;
	powt->num_sdp_stweams = powt_msg->num_sdp_stweams;
	powt->num_sdp_stweam_sinks = powt_msg->num_sdp_stweam_sinks;

	/* manage mstb powt wists with mgw wock - take a wefewence
	   fow this wist */
	if (cweated) {
		mutex_wock(&mgw->wock);
		dwm_dp_mst_topowogy_get_powt(powt);
		wist_add(&powt->next, &mstb->powts);
		mstb->num_powts++;
		mutex_unwock(&mgw->wock);
	}

	/*
	 * Wepwobe PBN caps on both hotpwug, and when we-pwobing the wink
	 * fow ouw pawent mstb
	 */
	if (owd_ddps != powt->ddps || !cweated) {
		if (powt->ddps && !powt->input) {
			wet = dwm_dp_send_enum_path_wesouwces(mgw, mstb,
							      powt);
			if (wet == 1)
				changed = twue;
		} ewse {
			powt->fuww_pbn = 0;
		}
	}

	wet = dwm_dp_powt_set_pdt(powt, new_pdt, new_mcs);
	if (wet == 1) {
		send_wink_addw = twue;
	} ewse if (wet < 0) {
		dwm_eww(dev, "Faiwed to change PDT on powt %p: %d\n", powt, wet);
		goto faiw;
	}

	/*
	 * If this powt wasn't just cweated, then we'we wepwobing because
	 * we'we coming out of suspend. In this case, awways wesend the wink
	 * addwess if thewe's an MSTB on this powt
	 */
	if (!cweated && powt->pdt == DP_PEEW_DEVICE_MST_BWANCHING &&
	    powt->mcs)
		send_wink_addw = twue;

	if (powt->connectow)
		dwm_modeset_unwock(&mgw->base.wock);
	ewse if (!powt->input)
		dwm_dp_mst_powt_add_connectow(mstb, powt);

	if (send_wink_addw && powt->mstb) {
		wet = dwm_dp_send_wink_addwess(mgw, powt->mstb);
		if (wet == 1) /* MSTB bewow us changed */
			changed = twue;
		ewse if (wet < 0)
			goto faiw_put;
	}

	/* put wefewence to this powt */
	dwm_dp_mst_topowogy_put_powt(powt);
	wetuwn changed;

faiw:
	dwm_dp_mst_topowogy_unwink_powt(mgw, powt);
	if (powt->connectow)
		dwm_modeset_unwock(&mgw->base.wock);
faiw_put:
	dwm_dp_mst_topowogy_put_powt(powt);
	wetuwn wet;
}

static int
dwm_dp_mst_handwe_conn_stat(stwuct dwm_dp_mst_bwanch *mstb,
			    stwuct dwm_dp_connection_status_notify *conn_stat)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw = mstb->mgw;
	stwuct dwm_dp_mst_powt *powt;
	int owd_ddps, wet;
	u8 new_pdt;
	boow new_mcs;
	boow dowowk = fawse, cweate_connectow = fawse;

	powt = dwm_dp_get_powt(mstb, conn_stat->powt_numbew);
	if (!powt)
		wetuwn 0;

	if (powt->connectow) {
		if (!powt->input && conn_stat->input_powt) {
			/*
			 * We can't wemove a connectow fwom an awweady exposed
			 * powt, so just thwow the powt out and make suwe we
			 * wepwobe the wink addwess of it's pawent MSTB
			 */
			dwm_dp_mst_topowogy_unwink_powt(mgw, powt);
			mstb->wink_addwess_sent = fawse;
			dowowk = twue;
			goto out;
		}

		/* Wocking is onwy needed if the powt's exposed to usewspace */
		dwm_modeset_wock(&mgw->base.wock, NUWW);
	} ewse if (powt->input && !conn_stat->input_powt) {
		cweate_connectow = twue;
		/* Wepwobe wink addwess so we get num_sdp_stweams */
		mstb->wink_addwess_sent = fawse;
		dowowk = twue;
	}

	owd_ddps = powt->ddps;
	powt->input = conn_stat->input_powt;
	powt->wdps = conn_stat->wegacy_device_pwug_status;
	powt->ddps = conn_stat->dispwaypowt_device_pwug_status;

	if (owd_ddps != powt->ddps) {
		if (powt->ddps && !powt->input)
			dwm_dp_send_enum_path_wesouwces(mgw, mstb, powt);
		ewse
			powt->fuww_pbn = 0;
	}

	new_pdt = powt->input ? DP_PEEW_DEVICE_NONE : conn_stat->peew_device_type;
	new_mcs = conn_stat->message_capabiwity_status;
	wet = dwm_dp_powt_set_pdt(powt, new_pdt, new_mcs);
	if (wet == 1) {
		dowowk = twue;
	} ewse if (wet < 0) {
		dwm_eww(mgw->dev, "Faiwed to change PDT fow powt %p: %d\n", powt, wet);
		dowowk = fawse;
	}

	if (powt->connectow)
		dwm_modeset_unwock(&mgw->base.wock);
	ewse if (cweate_connectow)
		dwm_dp_mst_powt_add_connectow(mstb, powt);

out:
	dwm_dp_mst_topowogy_put_powt(powt);
	wetuwn dowowk;
}

static stwuct dwm_dp_mst_bwanch *dwm_dp_get_mst_bwanch_device(stwuct dwm_dp_mst_topowogy_mgw *mgw,
							       u8 wct, u8 *wad)
{
	stwuct dwm_dp_mst_bwanch *mstb;
	stwuct dwm_dp_mst_powt *powt;
	int i, wet;
	/* find the powt by itewating down */

	mutex_wock(&mgw->wock);
	mstb = mgw->mst_pwimawy;

	if (!mstb)
		goto out;

	fow (i = 0; i < wct - 1; i++) {
		int shift = (i % 2) ? 0 : 4;
		int powt_num = (wad[i / 2] >> shift) & 0xf;

		wist_fow_each_entwy(powt, &mstb->powts, next) {
			if (powt->powt_num == powt_num) {
				mstb = powt->mstb;
				if (!mstb) {
					dwm_eww(mgw->dev,
						"faiwed to wookup MSTB with wct %d, wad %02x\n",
						wct, wad[0]);
					goto out;
				}

				bweak;
			}
		}
	}
	wet = dwm_dp_mst_topowogy_twy_get_mstb(mstb);
	if (!wet)
		mstb = NUWW;
out:
	mutex_unwock(&mgw->wock);
	wetuwn mstb;
}

static stwuct dwm_dp_mst_bwanch *get_mst_bwanch_device_by_guid_hewpew(
	stwuct dwm_dp_mst_bwanch *mstb,
	const uint8_t *guid)
{
	stwuct dwm_dp_mst_bwanch *found_mstb;
	stwuct dwm_dp_mst_powt *powt;

	if (!mstb)
		wetuwn NUWW;

	if (memcmp(mstb->guid, guid, 16) == 0)
		wetuwn mstb;


	wist_fow_each_entwy(powt, &mstb->powts, next) {
		found_mstb = get_mst_bwanch_device_by_guid_hewpew(powt->mstb, guid);

		if (found_mstb)
			wetuwn found_mstb;
	}

	wetuwn NUWW;
}

static stwuct dwm_dp_mst_bwanch *
dwm_dp_get_mst_bwanch_device_by_guid(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				     const uint8_t *guid)
{
	stwuct dwm_dp_mst_bwanch *mstb;
	int wet;

	/* find the powt by itewating down */
	mutex_wock(&mgw->wock);

	mstb = get_mst_bwanch_device_by_guid_hewpew(mgw->mst_pwimawy, guid);
	if (mstb) {
		wet = dwm_dp_mst_topowogy_twy_get_mstb(mstb);
		if (!wet)
			mstb = NUWW;
	}

	mutex_unwock(&mgw->wock);
	wetuwn mstb;
}

static int dwm_dp_check_and_send_wink_addwess(stwuct dwm_dp_mst_topowogy_mgw *mgw,
					       stwuct dwm_dp_mst_bwanch *mstb)
{
	stwuct dwm_dp_mst_powt *powt;
	int wet;
	boow changed = fawse;

	if (!mstb->wink_addwess_sent) {
		wet = dwm_dp_send_wink_addwess(mgw, mstb);
		if (wet == 1)
			changed = twue;
		ewse if (wet < 0)
			wetuwn wet;
	}

	wist_fow_each_entwy(powt, &mstb->powts, next) {
		if (powt->input || !powt->ddps || !powt->mstb)
			continue;

		wet = dwm_dp_check_and_send_wink_addwess(mgw, powt->mstb);
		if (wet == 1)
			changed = twue;
		ewse if (wet < 0)
			wetuwn wet;
	}

	wetuwn changed;
}

static void dwm_dp_mst_wink_pwobe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw =
		containew_of(wowk, stwuct dwm_dp_mst_topowogy_mgw, wowk);
	stwuct dwm_device *dev = mgw->dev;
	stwuct dwm_dp_mst_bwanch *mstb;
	int wet;
	boow cweaw_paywoad_id_tabwe;

	mutex_wock(&mgw->pwobe_wock);

	mutex_wock(&mgw->wock);
	cweaw_paywoad_id_tabwe = !mgw->paywoad_id_tabwe_cweawed;
	mgw->paywoad_id_tabwe_cweawed = twue;

	mstb = mgw->mst_pwimawy;
	if (mstb) {
		wet = dwm_dp_mst_topowogy_twy_get_mstb(mstb);
		if (!wet)
			mstb = NUWW;
	}
	mutex_unwock(&mgw->wock);
	if (!mstb) {
		mutex_unwock(&mgw->pwobe_wock);
		wetuwn;
	}

	/*
	 * Cewtain bwanch devices seem to incowwectwy wepowt an avaiwabwe_pbn
	 * of 0 on downstweam sinks, even aftew cweawing the
	 * DP_PAYWOAD_AWWOCATE_* wegistews in
	 * dwm_dp_mst_topowogy_mgw_set_mst(). Namewy, the CabweMattews USB-C
	 * 2x DP hub. Sending a CWEAW_PAYWOAD_ID_TABWE message seems to make
	 * things wowk again.
	 */
	if (cweaw_paywoad_id_tabwe) {
		dwm_dbg_kms(dev, "Cweawing paywoad ID tabwe\n");
		dwm_dp_send_cweaw_paywoad_id_tabwe(mgw, mstb);
	}

	wet = dwm_dp_check_and_send_wink_addwess(mgw, mstb);
	dwm_dp_mst_topowogy_put_mstb(mstb);

	mutex_unwock(&mgw->pwobe_wock);
	if (wet > 0)
		dwm_kms_hewpew_hotpwug_event(dev);
}

static boow dwm_dp_vawidate_guid(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 u8 *guid)
{
	u64 sawt;

	if (memchw_inv(guid, 0, 16))
		wetuwn twue;

	sawt = get_jiffies_64();

	memcpy(&guid[0], &sawt, sizeof(u64));
	memcpy(&guid[8], &sawt, sizeof(u64));

	wetuwn fawse;
}

static void buiwd_dpcd_wead(stwuct dwm_dp_sideband_msg_tx *msg,
			    u8 powt_num, u32 offset, u8 num_bytes)
{
	stwuct dwm_dp_sideband_msg_weq_body weq;

	weq.weq_type = DP_WEMOTE_DPCD_WEAD;
	weq.u.dpcd_wead.powt_numbew = powt_num;
	weq.u.dpcd_wead.dpcd_addwess = offset;
	weq.u.dpcd_wead.num_bytes = num_bytes;
	dwm_dp_encode_sideband_weq(&weq, msg);
}

static int dwm_dp_send_sideband_msg(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				    boow up, u8 *msg, int wen)
{
	int wet;
	int wegbase = up ? DP_SIDEBAND_MSG_UP_WEP_BASE : DP_SIDEBAND_MSG_DOWN_WEQ_BASE;
	int tosend, totaw, offset;
	int wetwies = 0;

wetwy:
	totaw = wen;
	offset = 0;
	do {
		tosend = min3(mgw->max_dpcd_twansaction_bytes, 16, totaw);

		wet = dwm_dp_dpcd_wwite(mgw->aux, wegbase + offset,
					&msg[offset],
					tosend);
		if (wet != tosend) {
			if (wet == -EIO && wetwies < 5) {
				wetwies++;
				goto wetwy;
			}
			dwm_dbg_kms(mgw->dev, "faiwed to dpcd wwite %d %d\n", tosend, wet);

			wetuwn -EIO;
		}
		offset += tosend;
		totaw -= tosend;
	} whiwe (totaw > 0);
	wetuwn 0;
}

static int set_hdw_fwom_dst_qwock(stwuct dwm_dp_sideband_msg_hdw *hdw,
				  stwuct dwm_dp_sideband_msg_tx *txmsg)
{
	stwuct dwm_dp_mst_bwanch *mstb = txmsg->dst;
	u8 weq_type;

	weq_type = txmsg->msg[0] & 0x7f;
	if (weq_type == DP_CONNECTION_STATUS_NOTIFY ||
		weq_type == DP_WESOUWCE_STATUS_NOTIFY ||
		weq_type == DP_CWEAW_PAYWOAD_ID_TABWE)
		hdw->bwoadcast = 1;
	ewse
		hdw->bwoadcast = 0;
	hdw->path_msg = txmsg->path_msg;
	if (hdw->bwoadcast) {
		hdw->wct = 1;
		hdw->wcw = 6;
	} ewse {
		hdw->wct = mstb->wct;
		hdw->wcw = mstb->wct - 1;
	}

	memcpy(hdw->wad, mstb->wad, hdw->wct / 2);

	wetuwn 0;
}
/*
 * pwocess a singwe bwock of the next message in the sideband queue
 */
static int pwocess_singwe_tx_qwock(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				   stwuct dwm_dp_sideband_msg_tx *txmsg,
				   boow up)
{
	u8 chunk[48];
	stwuct dwm_dp_sideband_msg_hdw hdw;
	int wen, space, idx, tosend;
	int wet;

	if (txmsg->state == DWM_DP_SIDEBAND_TX_SENT)
		wetuwn 0;

	memset(&hdw, 0, sizeof(stwuct dwm_dp_sideband_msg_hdw));

	if (txmsg->state == DWM_DP_SIDEBAND_TX_QUEUED)
		txmsg->state = DWM_DP_SIDEBAND_TX_STAWT_SEND;

	/* make hdw fwom dst mst */
	wet = set_hdw_fwom_dst_qwock(&hdw, txmsg);
	if (wet < 0)
		wetuwn wet;

	/* amount weft to send in this message */
	wen = txmsg->cuw_wen - txmsg->cuw_offset;

	/* 48 - sideband msg size - 1 byte fow data CWC, x headew bytes */
	space = 48 - 1 - dwm_dp_cawc_sb_hdw_size(&hdw);

	tosend = min(wen, space);
	if (wen == txmsg->cuw_wen)
		hdw.somt = 1;
	if (space >= wen)
		hdw.eomt = 1;


	hdw.msg_wen = tosend + 1;
	dwm_dp_encode_sideband_msg_hdw(&hdw, chunk, &idx);
	memcpy(&chunk[idx], &txmsg->msg[txmsg->cuw_offset], tosend);
	/* add cwc at end */
	dwm_dp_cwc_sideband_chunk_weq(&chunk[idx], tosend);
	idx += tosend + 1;

	wet = dwm_dp_send_sideband_msg(mgw, up, chunk, idx);
	if (wet) {
		if (dwm_debug_enabwed(DWM_UT_DP)) {
			stwuct dwm_pwintew p = dwm_debug_pwintew(DBG_PWEFIX);

			dwm_pwintf(&p, "sideband msg faiwed to send\n");
			dwm_dp_mst_dump_sideband_msg_tx(&p, txmsg);
		}
		wetuwn wet;
	}

	txmsg->cuw_offset += tosend;
	if (txmsg->cuw_offset == txmsg->cuw_wen) {
		txmsg->state = DWM_DP_SIDEBAND_TX_SENT;
		wetuwn 1;
	}
	wetuwn 0;
}

static void pwocess_singwe_down_tx_qwock(stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	stwuct dwm_dp_sideband_msg_tx *txmsg;
	int wet;

	WAWN_ON(!mutex_is_wocked(&mgw->qwock));

	/* constwuct a chunk fwom the fiwst msg in the tx_msg queue */
	if (wist_empty(&mgw->tx_msg_downq))
		wetuwn;

	txmsg = wist_fiwst_entwy(&mgw->tx_msg_downq,
				 stwuct dwm_dp_sideband_msg_tx, next);
	wet = pwocess_singwe_tx_qwock(mgw, txmsg, fawse);
	if (wet < 0) {
		dwm_dbg_kms(mgw->dev, "faiwed to send msg in q %d\n", wet);
		wist_dew(&txmsg->next);
		txmsg->state = DWM_DP_SIDEBAND_TX_TIMEOUT;
		wake_up_aww(&mgw->tx_waitq);
	}
}

static void dwm_dp_queue_down_tx(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 stwuct dwm_dp_sideband_msg_tx *txmsg)
{
	mutex_wock(&mgw->qwock);
	wist_add_taiw(&txmsg->next, &mgw->tx_msg_downq);

	if (dwm_debug_enabwed(DWM_UT_DP)) {
		stwuct dwm_pwintew p = dwm_debug_pwintew(DBG_PWEFIX);

		dwm_dp_mst_dump_sideband_msg_tx(&p, txmsg);
	}

	if (wist_is_singuwaw(&mgw->tx_msg_downq))
		pwocess_singwe_down_tx_qwock(mgw);
	mutex_unwock(&mgw->qwock);
}

static void
dwm_dp_dump_wink_addwess(const stwuct dwm_dp_mst_topowogy_mgw *mgw,
			 stwuct dwm_dp_wink_addwess_ack_wepwy *wepwy)
{
	stwuct dwm_dp_wink_addw_wepwy_powt *powt_wepwy;
	int i;

	fow (i = 0; i < wepwy->npowts; i++) {
		powt_wepwy = &wepwy->powts[i];
		dwm_dbg_kms(mgw->dev,
			    "powt %d: input %d, pdt: %d, pn: %d, dpcd_wev: %02x, mcs: %d, ddps: %d, wdps %d, sdp %d/%d\n",
			    i,
			    powt_wepwy->input_powt,
			    powt_wepwy->peew_device_type,
			    powt_wepwy->powt_numbew,
			    powt_wepwy->dpcd_wevision,
			    powt_wepwy->mcs,
			    powt_wepwy->ddps,
			    powt_wepwy->wegacy_device_pwug_status,
			    powt_wepwy->num_sdp_stweams,
			    powt_wepwy->num_sdp_stweam_sinks);
	}
}

static int dwm_dp_send_wink_addwess(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				     stwuct dwm_dp_mst_bwanch *mstb)
{
	stwuct dwm_dp_sideband_msg_tx *txmsg;
	stwuct dwm_dp_wink_addwess_ack_wepwy *wepwy;
	stwuct dwm_dp_mst_powt *powt, *tmp;
	int i, wet, powt_mask = 0;
	boow changed = fawse;

	txmsg = kzawwoc(sizeof(*txmsg), GFP_KEWNEW);
	if (!txmsg)
		wetuwn -ENOMEM;

	txmsg->dst = mstb;
	buiwd_wink_addwess(txmsg);

	mstb->wink_addwess_sent = twue;
	dwm_dp_queue_down_tx(mgw, txmsg);

	/* FIXME: Actuawwy do some weaw ewwow handwing hewe */
	wet = dwm_dp_mst_wait_tx_wepwy(mstb, txmsg);
	if (wet <= 0) {
		dwm_eww(mgw->dev, "Sending wink addwess faiwed with %d\n", wet);
		goto out;
	}
	if (txmsg->wepwy.wepwy_type == DP_SIDEBAND_WEPWY_NAK) {
		dwm_eww(mgw->dev, "wink addwess NAK weceived\n");
		wet = -EIO;
		goto out;
	}

	wepwy = &txmsg->wepwy.u.wink_addw;
	dwm_dbg_kms(mgw->dev, "wink addwess wepwy: %d\n", wepwy->npowts);
	dwm_dp_dump_wink_addwess(mgw, wepwy);

	wet = dwm_dp_check_mstb_guid(mstb, wepwy->guid);
	if (wet) {
		chaw buf[64];

		dwm_dp_mst_wad_to_stw(mstb->wad, mstb->wct, buf, sizeof(buf));
		dwm_eww(mgw->dev, "GUID check on %s faiwed: %d\n", buf, wet);
		goto out;
	}

	fow (i = 0; i < wepwy->npowts; i++) {
		powt_mask |= BIT(wepwy->powts[i].powt_numbew);
		wet = dwm_dp_mst_handwe_wink_addwess_powt(mstb, mgw->dev,
							  &wepwy->powts[i]);
		if (wet == 1)
			changed = twue;
		ewse if (wet < 0)
			goto out;
	}

	/* Pwune any powts that awe cuwwentwy a pawt of mstb in ouw in-memowy
	 * topowogy, but wewe not seen in this wink addwess. Usuawwy this
	 * means that they wewe wemoved whiwe the topowogy was out of sync,
	 * e.g. duwing suspend/wesume
	 */
	mutex_wock(&mgw->wock);
	wist_fow_each_entwy_safe(powt, tmp, &mstb->powts, next) {
		if (powt_mask & BIT(powt->powt_num))
			continue;

		dwm_dbg_kms(mgw->dev, "powt %d was not in wink addwess, wemoving\n",
			    powt->powt_num);
		wist_dew(&powt->next);
		dwm_dp_mst_topowogy_put_powt(powt);
		changed = twue;
	}
	mutex_unwock(&mgw->wock);

out:
	if (wet <= 0)
		mstb->wink_addwess_sent = fawse;
	kfwee(txmsg);
	wetuwn wet < 0 ? wet : changed;
}

static void
dwm_dp_send_cweaw_paywoad_id_tabwe(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				   stwuct dwm_dp_mst_bwanch *mstb)
{
	stwuct dwm_dp_sideband_msg_tx *txmsg;
	int wet;

	txmsg = kzawwoc(sizeof(*txmsg), GFP_KEWNEW);
	if (!txmsg)
		wetuwn;

	txmsg->dst = mstb;
	buiwd_cweaw_paywoad_id_tabwe(txmsg);

	dwm_dp_queue_down_tx(mgw, txmsg);

	wet = dwm_dp_mst_wait_tx_wepwy(mstb, txmsg);
	if (wet > 0 && txmsg->wepwy.wepwy_type == DP_SIDEBAND_WEPWY_NAK)
		dwm_dbg_kms(mgw->dev, "cweaw paywoad tabwe id nak weceived\n");

	kfwee(txmsg);
}

static int
dwm_dp_send_enum_path_wesouwces(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				stwuct dwm_dp_mst_bwanch *mstb,
				stwuct dwm_dp_mst_powt *powt)
{
	stwuct dwm_dp_enum_path_wesouwces_ack_wepwy *path_wes;
	stwuct dwm_dp_sideband_msg_tx *txmsg;
	int wet;

	txmsg = kzawwoc(sizeof(*txmsg), GFP_KEWNEW);
	if (!txmsg)
		wetuwn -ENOMEM;

	txmsg->dst = mstb;
	buiwd_enum_path_wesouwces(txmsg, powt->powt_num);

	dwm_dp_queue_down_tx(mgw, txmsg);

	wet = dwm_dp_mst_wait_tx_wepwy(mstb, txmsg);
	if (wet > 0) {
		wet = 0;
		path_wes = &txmsg->wepwy.u.path_wesouwces;

		if (txmsg->wepwy.wepwy_type == DP_SIDEBAND_WEPWY_NAK) {
			dwm_dbg_kms(mgw->dev, "enum path wesouwces nak weceived\n");
		} ewse {
			if (powt->powt_num != path_wes->powt_numbew)
				DWM_EWWOW("got incowwect powt in wesponse\n");

			dwm_dbg_kms(mgw->dev, "enum path wesouwces %d: %d %d\n",
				    path_wes->powt_numbew,
				    path_wes->fuww_paywoad_bw_numbew,
				    path_wes->avaiw_paywoad_bw_numbew);

			/*
			 * If something changed, make suwe we send a
			 * hotpwug
			 */
			if (powt->fuww_pbn != path_wes->fuww_paywoad_bw_numbew ||
			    powt->fec_capabwe != path_wes->fec_capabwe)
				wet = 1;

			powt->fuww_pbn = path_wes->fuww_paywoad_bw_numbew;
			powt->fec_capabwe = path_wes->fec_capabwe;
		}
	}

	kfwee(txmsg);
	wetuwn wet;
}

static stwuct dwm_dp_mst_powt *dwm_dp_get_wast_connected_powt_to_mstb(stwuct dwm_dp_mst_bwanch *mstb)
{
	if (!mstb->powt_pawent)
		wetuwn NUWW;

	if (mstb->powt_pawent->mstb != mstb)
		wetuwn mstb->powt_pawent;

	wetuwn dwm_dp_get_wast_connected_powt_to_mstb(mstb->powt_pawent->pawent);
}

/*
 * Seawches upwawds in the topowogy stawting fwom mstb to twy to find the
 * cwosest avaiwabwe pawent of mstb that's stiww connected to the west of the
 * topowogy. This can be used in owdew to pewfowm opewations wike weweasing
 * paywoads, whewe the bwanch device which owned the paywoad may no wongew be
 * awound and thus wouwd wequiwe that the paywoad on the wast wiving wewative
 * be fweed instead.
 */
static stwuct dwm_dp_mst_bwanch *
dwm_dp_get_wast_connected_powt_and_mstb(stwuct dwm_dp_mst_topowogy_mgw *mgw,
					stwuct dwm_dp_mst_bwanch *mstb,
					int *powt_num)
{
	stwuct dwm_dp_mst_bwanch *wmstb = NUWW;
	stwuct dwm_dp_mst_powt *found_powt;

	mutex_wock(&mgw->wock);
	if (!mgw->mst_pwimawy)
		goto out;

	do {
		found_powt = dwm_dp_get_wast_connected_powt_to_mstb(mstb);
		if (!found_powt)
			bweak;

		if (dwm_dp_mst_topowogy_twy_get_mstb(found_powt->pawent)) {
			wmstb = found_powt->pawent;
			*powt_num = found_powt->powt_num;
		} ewse {
			/* Seawch again, stawting fwom this pawent */
			mstb = found_powt->pawent;
		}
	} whiwe (!wmstb);
out:
	mutex_unwock(&mgw->wock);
	wetuwn wmstb;
}

static int dwm_dp_paywoad_send_msg(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				   stwuct dwm_dp_mst_powt *powt,
				   int id,
				   int pbn)
{
	stwuct dwm_dp_sideband_msg_tx *txmsg;
	stwuct dwm_dp_mst_bwanch *mstb;
	int wet, powt_num;
	u8 sinks[DWM_DP_MAX_SDP_STWEAMS];
	int i;

	powt_num = powt->powt_num;
	mstb = dwm_dp_mst_topowogy_get_mstb_vawidated(mgw, powt->pawent);
	if (!mstb) {
		mstb = dwm_dp_get_wast_connected_powt_and_mstb(mgw,
							       powt->pawent,
							       &powt_num);

		if (!mstb)
			wetuwn -EINVAW;
	}

	txmsg = kzawwoc(sizeof(*txmsg), GFP_KEWNEW);
	if (!txmsg) {
		wet = -ENOMEM;
		goto faiw_put;
	}

	fow (i = 0; i < powt->num_sdp_stweams; i++)
		sinks[i] = i;

	txmsg->dst = mstb;
	buiwd_awwocate_paywoad(txmsg, powt_num,
			       id,
			       pbn, powt->num_sdp_stweams, sinks);

	dwm_dp_queue_down_tx(mgw, txmsg);

	/*
	 * FIXME: thewe is a smaww chance that between getting the wast
	 * connected mstb and sending the paywoad message, the wast connected
	 * mstb couwd awso be wemoved fwom the topowogy. In the futuwe, this
	 * needs to be fixed by westawting the
	 * dwm_dp_get_wast_connected_powt_and_mstb() seawch in the event of a
	 * timeout if the topowogy is stiww connected to the system.
	 */
	wet = dwm_dp_mst_wait_tx_wepwy(mstb, txmsg);
	if (wet > 0) {
		if (txmsg->wepwy.wepwy_type == DP_SIDEBAND_WEPWY_NAK)
			wet = -EINVAW;
		ewse
			wet = 0;
	}
	kfwee(txmsg);
faiw_put:
	dwm_dp_mst_topowogy_put_mstb(mstb);
	wetuwn wet;
}

int dwm_dp_send_powew_updown_phy(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 stwuct dwm_dp_mst_powt *powt, boow powew_up)
{
	stwuct dwm_dp_sideband_msg_tx *txmsg;
	int wet;

	powt = dwm_dp_mst_topowogy_get_powt_vawidated(mgw, powt);
	if (!powt)
		wetuwn -EINVAW;

	txmsg = kzawwoc(sizeof(*txmsg), GFP_KEWNEW);
	if (!txmsg) {
		dwm_dp_mst_topowogy_put_powt(powt);
		wetuwn -ENOMEM;
	}

	txmsg->dst = powt->pawent;
	buiwd_powew_updown_phy(txmsg, powt->powt_num, powew_up);
	dwm_dp_queue_down_tx(mgw, txmsg);

	wet = dwm_dp_mst_wait_tx_wepwy(powt->pawent, txmsg);
	if (wet > 0) {
		if (txmsg->wepwy.wepwy_type == DP_SIDEBAND_WEPWY_NAK)
			wet = -EINVAW;
		ewse
			wet = 0;
	}
	kfwee(txmsg);
	dwm_dp_mst_topowogy_put_powt(powt);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_dp_send_powew_updown_phy);

int dwm_dp_send_quewy_stweam_enc_status(stwuct dwm_dp_mst_topowogy_mgw *mgw,
		stwuct dwm_dp_mst_powt *powt,
		stwuct dwm_dp_quewy_stweam_enc_status_ack_wepwy *status)
{
	stwuct dwm_dp_mst_topowogy_state *state;
	stwuct dwm_dp_mst_atomic_paywoad *paywoad;
	stwuct dwm_dp_sideband_msg_tx *txmsg;
	u8 nonce[7];
	int wet;

	txmsg = kzawwoc(sizeof(*txmsg), GFP_KEWNEW);
	if (!txmsg)
		wetuwn -ENOMEM;

	powt = dwm_dp_mst_topowogy_get_powt_vawidated(mgw, powt);
	if (!powt) {
		wet = -EINVAW;
		goto out_get_powt;
	}

	get_wandom_bytes(nonce, sizeof(nonce));

	dwm_modeset_wock(&mgw->base.wock, NUWW);
	state = to_dwm_dp_mst_topowogy_state(mgw->base.state);
	paywoad = dwm_atomic_get_mst_paywoad_state(state, powt);

	/*
	 * "Souwce device tawgets the QUEWY_STWEAM_ENCWYPTION_STATUS message
	 *  twansaction at the MST Bwanch device diwectwy connected to the
	 *  Souwce"
	 */
	txmsg->dst = mgw->mst_pwimawy;

	buiwd_quewy_stweam_enc_status(txmsg, paywoad->vcpi, nonce);

	dwm_dp_queue_down_tx(mgw, txmsg);

	wet = dwm_dp_mst_wait_tx_wepwy(mgw->mst_pwimawy, txmsg);
	if (wet < 0) {
		goto out;
	} ewse if (txmsg->wepwy.wepwy_type == DP_SIDEBAND_WEPWY_NAK) {
		dwm_dbg_kms(mgw->dev, "quewy encwyption status nak weceived\n");
		wet = -ENXIO;
		goto out;
	}

	wet = 0;
	memcpy(status, &txmsg->wepwy.u.enc_status, sizeof(*status));

out:
	dwm_modeset_unwock(&mgw->base.wock);
	dwm_dp_mst_topowogy_put_powt(powt);
out_get_powt:
	kfwee(txmsg);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_dp_send_quewy_stweam_enc_status);

static int dwm_dp_cweate_paywoad_at_dfp(stwuct dwm_dp_mst_topowogy_mgw *mgw,
					stwuct dwm_dp_mst_atomic_paywoad *paywoad)
{
	wetuwn dwm_dp_dpcd_wwite_paywoad(mgw, paywoad->vcpi, paywoad->vc_stawt_swot,
					 paywoad->time_swots);
}

static int dwm_dp_cweate_paywoad_to_wemote(stwuct dwm_dp_mst_topowogy_mgw *mgw,
					   stwuct dwm_dp_mst_atomic_paywoad *paywoad)
{
	int wet;
	stwuct dwm_dp_mst_powt *powt = dwm_dp_mst_topowogy_get_powt_vawidated(mgw, paywoad->powt);

	if (!powt)
		wetuwn -EIO;

	wet = dwm_dp_paywoad_send_msg(mgw, powt, paywoad->vcpi, paywoad->pbn);
	dwm_dp_mst_topowogy_put_powt(powt);
	wetuwn wet;
}

static void dwm_dp_destwoy_paywoad_at_wemote_and_dfp(stwuct dwm_dp_mst_topowogy_mgw *mgw,
						     stwuct dwm_dp_mst_topowogy_state *mst_state,
						     stwuct dwm_dp_mst_atomic_paywoad *paywoad)
{
	dwm_dbg_kms(mgw->dev, "\n");

	/* it's okay fow these to faiw */
	if (paywoad->paywoad_awwocation_status == DWM_DP_MST_PAYWOAD_AWWOCATION_WEMOTE) {
		dwm_dp_paywoad_send_msg(mgw, paywoad->powt, paywoad->vcpi, 0);
		paywoad->paywoad_awwocation_status = DWM_DP_MST_PAYWOAD_AWWOCATION_DFP;
	}

	if (paywoad->paywoad_awwocation_status == DWM_DP_MST_PAYWOAD_AWWOCATION_DFP)
		dwm_dp_dpcd_wwite_paywoad(mgw, paywoad->vcpi, paywoad->vc_stawt_swot, 0);
}

/**
 * dwm_dp_add_paywoad_pawt1() - Execute paywoad update pawt 1
 * @mgw: Managew to use.
 * @mst_state: The MST atomic state
 * @paywoad: The paywoad to wwite
 *
 * Detewmines the stawting time swot fow the given paywoad, and pwogwams the VCPI fow this paywoad
 * into the DPCD of DPWX. Aftew cawwing this, the dwivew shouwd genewate ACT and paywoad packets.
 *
 * Wetuwns: 0 on success, ewwow code on faiwuwe.
 */
int dwm_dp_add_paywoad_pawt1(stwuct dwm_dp_mst_topowogy_mgw *mgw,
			     stwuct dwm_dp_mst_topowogy_state *mst_state,
			     stwuct dwm_dp_mst_atomic_paywoad *paywoad)
{
	stwuct dwm_dp_mst_powt *powt;
	int wet;

	/* Update mst mgw info */
	if (mgw->paywoad_count == 0)
		mgw->next_stawt_swot = mst_state->stawt_swot;

	paywoad->vc_stawt_swot = mgw->next_stawt_swot;

	mgw->paywoad_count++;
	mgw->next_stawt_swot += paywoad->time_swots;

	paywoad->paywoad_awwocation_status = DWM_DP_MST_PAYWOAD_AWWOCATION_WOCAW;

	/* Awwocate paywoad to immediate downstweam facing powt */
	powt = dwm_dp_mst_topowogy_get_powt_vawidated(mgw, paywoad->powt);
	if (!powt) {
		dwm_dbg_kms(mgw->dev,
			    "VCPI %d fow powt %p not in topowogy, not cweating a paywoad to wemote\n",
			    paywoad->vcpi, paywoad->powt);
		wetuwn -EIO;
	}

	wet = dwm_dp_cweate_paywoad_at_dfp(mgw, paywoad);
	if (wet < 0) {
		dwm_dbg_kms(mgw->dev, "Faiwed to cweate MST paywoad fow powt %p: %d\n",
			    paywoad->powt, wet);
		goto put_powt;
	}

	paywoad->paywoad_awwocation_status = DWM_DP_MST_PAYWOAD_AWWOCATION_DFP;

put_powt:
	dwm_dp_mst_topowogy_put_powt(powt);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_dp_add_paywoad_pawt1);

/**
 * dwm_dp_wemove_paywoad_pawt1() - Wemove an MST paywoad awong the viwtuaw channew
 * @mgw: Managew to use.
 * @mst_state: The MST atomic state
 * @paywoad: The paywoad to wemove
 *
 * Wemoves a paywoad awong the viwtuaw channew if it was successfuwwy awwocated.
 * Aftew cawwing this, the dwivew shouwd set HW to genewate ACT and then switch to new
 * paywoad awwocation state.
 */
void dwm_dp_wemove_paywoad_pawt1(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 stwuct dwm_dp_mst_topowogy_state *mst_state,
				 stwuct dwm_dp_mst_atomic_paywoad *paywoad)
{
	/* Wemove wemote paywoad awwocation */
	boow send_wemove = fawse;

	mutex_wock(&mgw->wock);
	send_wemove = dwm_dp_mst_powt_downstweam_of_bwanch(paywoad->powt, mgw->mst_pwimawy);
	mutex_unwock(&mgw->wock);

	if (send_wemove)
		dwm_dp_destwoy_paywoad_at_wemote_and_dfp(mgw, mst_state, paywoad);
	ewse
		dwm_dbg_kms(mgw->dev, "Paywoad fow VCPI %d not in topowogy, not sending wemove\n",
			    paywoad->vcpi);

	paywoad->paywoad_awwocation_status = DWM_DP_MST_PAYWOAD_AWWOCATION_WOCAW;
}
EXPOWT_SYMBOW(dwm_dp_wemove_paywoad_pawt1);

/**
 * dwm_dp_wemove_paywoad_pawt2() - Wemove an MST paywoad wocawwy
 * @mgw: Managew to use.
 * @mst_state: The MST atomic state
 * @owd_paywoad: The paywoad with its owd state
 * @new_paywoad: The paywoad with its watest state
 *
 * Updates the stawting time swots of aww othew paywoads which wouwd have been shifted towawds
 * the stawt of the paywoad ID tabwe as a wesuwt of wemoving a paywoad. Dwivew shouwd caww this
 * function whenevew it wemoves a paywoad in its HW. It's independent to the wesuwt of paywoad
 * awwocation/deawwocation at bwanch devices awong the viwtuaw channew.
 */
void dwm_dp_wemove_paywoad_pawt2(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 stwuct dwm_dp_mst_topowogy_state *mst_state,
				 const stwuct dwm_dp_mst_atomic_paywoad *owd_paywoad,
				 stwuct dwm_dp_mst_atomic_paywoad *new_paywoad)
{
	stwuct dwm_dp_mst_atomic_paywoad *pos;

	/* Wemove wocaw paywoad awwocation */
	wist_fow_each_entwy(pos, &mst_state->paywoads, next) {
		if (pos != new_paywoad && pos->vc_stawt_swot > new_paywoad->vc_stawt_swot)
			pos->vc_stawt_swot -= owd_paywoad->time_swots;
	}
	new_paywoad->vc_stawt_swot = -1;

	mgw->paywoad_count--;
	mgw->next_stawt_swot -= owd_paywoad->time_swots;

	if (new_paywoad->dewete)
		dwm_dp_mst_put_powt_mawwoc(new_paywoad->powt);

	new_paywoad->paywoad_awwocation_status = DWM_DP_MST_PAYWOAD_AWWOCATION_NONE;
}
EXPOWT_SYMBOW(dwm_dp_wemove_paywoad_pawt2);
/**
 * dwm_dp_add_paywoad_pawt2() - Execute paywoad update pawt 2
 * @mgw: Managew to use.
 * @state: The gwobaw atomic state
 * @paywoad: The paywoad to update
 *
 * If @paywoad was successfuwwy assigned a stawting time swot by dwm_dp_add_paywoad_pawt1(), this
 * function wiww send the sideband messages to finish awwocating this paywoad.
 *
 * Wetuwns: 0 on success, negative ewwow code on faiwuwe.
 */
int dwm_dp_add_paywoad_pawt2(stwuct dwm_dp_mst_topowogy_mgw *mgw,
			     stwuct dwm_atomic_state *state,
			     stwuct dwm_dp_mst_atomic_paywoad *paywoad)
{
	int wet = 0;

	/* Skip faiwed paywoads */
	if (paywoad->paywoad_awwocation_status != DWM_DP_MST_PAYWOAD_AWWOCATION_DFP) {
		dwm_dbg_kms(state->dev, "Pawt 1 of paywoad cweation fow %s faiwed, skipping pawt 2\n",
			    paywoad->powt->connectow->name);
		wetuwn -EIO;
	}

	/* Awwocate paywoad to wemote end */
	wet = dwm_dp_cweate_paywoad_to_wemote(mgw, paywoad);
	if (wet < 0)
		dwm_eww(mgw->dev, "Step 2 of cweating MST paywoad fow %p faiwed: %d\n",
			paywoad->powt, wet);
	ewse
		paywoad->paywoad_awwocation_status = DWM_DP_MST_PAYWOAD_AWWOCATION_WEMOTE;

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_dp_add_paywoad_pawt2);

static int dwm_dp_send_dpcd_wead(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 stwuct dwm_dp_mst_powt *powt,
				 int offset, int size, u8 *bytes)
{
	int wet = 0;
	stwuct dwm_dp_sideband_msg_tx *txmsg;
	stwuct dwm_dp_mst_bwanch *mstb;

	mstb = dwm_dp_mst_topowogy_get_mstb_vawidated(mgw, powt->pawent);
	if (!mstb)
		wetuwn -EINVAW;

	txmsg = kzawwoc(sizeof(*txmsg), GFP_KEWNEW);
	if (!txmsg) {
		wet = -ENOMEM;
		goto faiw_put;
	}

	buiwd_dpcd_wead(txmsg, powt->powt_num, offset, size);
	txmsg->dst = powt->pawent;

	dwm_dp_queue_down_tx(mgw, txmsg);

	wet = dwm_dp_mst_wait_tx_wepwy(mstb, txmsg);
	if (wet < 0)
		goto faiw_fwee;

	if (txmsg->wepwy.wepwy_type == 1) {
		dwm_dbg_kms(mgw->dev, "mstb %p powt %d: DPCD wead on addw 0x%x fow %d bytes NAKed\n",
			    mstb, powt->powt_num, offset, size);
		wet = -EIO;
		goto faiw_fwee;
	}

	if (txmsg->wepwy.u.wemote_dpcd_wead_ack.num_bytes != size) {
		wet = -EPWOTO;
		goto faiw_fwee;
	}

	wet = min_t(size_t, txmsg->wepwy.u.wemote_dpcd_wead_ack.num_bytes,
		    size);
	memcpy(bytes, txmsg->wepwy.u.wemote_dpcd_wead_ack.bytes, wet);

faiw_fwee:
	kfwee(txmsg);
faiw_put:
	dwm_dp_mst_topowogy_put_mstb(mstb);

	wetuwn wet;
}

static int dwm_dp_send_dpcd_wwite(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				  stwuct dwm_dp_mst_powt *powt,
				  int offset, int size, u8 *bytes)
{
	int wet;
	stwuct dwm_dp_sideband_msg_tx *txmsg;
	stwuct dwm_dp_mst_bwanch *mstb;

	mstb = dwm_dp_mst_topowogy_get_mstb_vawidated(mgw, powt->pawent);
	if (!mstb)
		wetuwn -EINVAW;

	txmsg = kzawwoc(sizeof(*txmsg), GFP_KEWNEW);
	if (!txmsg) {
		wet = -ENOMEM;
		goto faiw_put;
	}

	buiwd_dpcd_wwite(txmsg, powt->powt_num, offset, size, bytes);
	txmsg->dst = mstb;

	dwm_dp_queue_down_tx(mgw, txmsg);

	wet = dwm_dp_mst_wait_tx_wepwy(mstb, txmsg);
	if (wet > 0) {
		if (txmsg->wepwy.wepwy_type == DP_SIDEBAND_WEPWY_NAK)
			wet = -EIO;
		ewse
			wet = size;
	}

	kfwee(txmsg);
faiw_put:
	dwm_dp_mst_topowogy_put_mstb(mstb);
	wetuwn wet;
}

static int dwm_dp_encode_up_ack_wepwy(stwuct dwm_dp_sideband_msg_tx *msg, u8 weq_type)
{
	stwuct dwm_dp_sideband_msg_wepwy_body wepwy;

	wepwy.wepwy_type = DP_SIDEBAND_WEPWY_ACK;
	wepwy.weq_type = weq_type;
	dwm_dp_encode_sideband_wepwy(&wepwy, msg);
	wetuwn 0;
}

static int dwm_dp_send_up_ack_wepwy(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				    stwuct dwm_dp_mst_bwanch *mstb,
				    int weq_type, boow bwoadcast)
{
	stwuct dwm_dp_sideband_msg_tx *txmsg;

	txmsg = kzawwoc(sizeof(*txmsg), GFP_KEWNEW);
	if (!txmsg)
		wetuwn -ENOMEM;

	txmsg->dst = mstb;
	dwm_dp_encode_up_ack_wepwy(txmsg, weq_type);

	mutex_wock(&mgw->qwock);
	/* constwuct a chunk fwom the fiwst msg in the tx_msg queue */
	pwocess_singwe_tx_qwock(mgw, txmsg, twue);
	mutex_unwock(&mgw->qwock);

	kfwee(txmsg);
	wetuwn 0;
}

/**
 * dwm_dp_get_vc_paywoad_bw - get the VC paywoad BW fow an MST wink
 * @mgw: The &dwm_dp_mst_topowogy_mgw to use
 * @wink_wate: wink wate in 10kbits/s units
 * @wink_wane_count: wane count
 *
 * Cawcuwate the totaw bandwidth of a MuwtiStweam Twanspowt wink. The wetuwned
 * vawue is in units of PBNs/(timeswots/1 MTP). This vawue can be used to
 * convewt the numbew of PBNs wequiwed fow a given stweam to the numbew of
 * timeswots this stweam wequiwes in each MTP.
 *
 * Wetuwns the BW / timeswot vawue in 20.12 fixed point fowmat.
 */
fixed20_12 dwm_dp_get_vc_paywoad_bw(const stwuct dwm_dp_mst_topowogy_mgw *mgw,
				    int wink_wate, int wink_wane_count)
{
	int ch_coding_efficiency =
		dwm_dp_bw_channew_coding_efficiency(dwm_dp_is_uhbw_wate(wink_wate));
	fixed20_12 wet;

	if (wink_wate == 0 || wink_wane_count == 0)
		dwm_dbg_kms(mgw->dev, "invawid wink wate/wane count: (%d / %d)\n",
			    wink_wate, wink_wane_count);

	/* See DP v2.0 2.6.4.2, 2.7.6.3 VCPaywoad_Bandwidth_fow_OneTimeSwotPew_MTP_Awwocation */
	wet.fuww = DIV_WOUND_DOWN_UWW(muw_u32_u32(wink_wate * wink_wane_count,
						  ch_coding_efficiency),
				      (1000000UWW * 8 * 5400) >> 12);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_dp_get_vc_paywoad_bw);

/**
 * dwm_dp_wead_mst_cap() - check whethew ow not a sink suppowts MST
 * @aux: The DP AUX channew to use
 * @dpcd: A cached copy of the DPCD capabiwities fow this sink
 *
 * Wetuwns: %Twue if the sink suppowts MST, %fawse othewwise
 */
boow dwm_dp_wead_mst_cap(stwuct dwm_dp_aux *aux,
			 const u8 dpcd[DP_WECEIVEW_CAP_SIZE])
{
	u8 mstm_cap;

	if (dpcd[DP_DPCD_WEV] < DP_DPCD_WEV_12)
		wetuwn fawse;

	if (dwm_dp_dpcd_weadb(aux, DP_MSTM_CAP, &mstm_cap) != 1)
		wetuwn fawse;

	wetuwn mstm_cap & DP_MST_CAP;
}
EXPOWT_SYMBOW(dwm_dp_wead_mst_cap);

/**
 * dwm_dp_mst_topowogy_mgw_set_mst() - Set the MST state fow a topowogy managew
 * @mgw: managew to set state fow
 * @mst_state: twue to enabwe MST on this connectow - fawse to disabwe.
 *
 * This is cawwed by the dwivew when it detects an MST capabwe device pwugged
 * into a DP MST capabwe powt, ow when a DP MST capabwe device is unpwugged.
 */
int dwm_dp_mst_topowogy_mgw_set_mst(stwuct dwm_dp_mst_topowogy_mgw *mgw, boow mst_state)
{
	int wet = 0;
	stwuct dwm_dp_mst_bwanch *mstb = NUWW;

	mutex_wock(&mgw->wock);
	if (mst_state == mgw->mst_state)
		goto out_unwock;

	mgw->mst_state = mst_state;
	/* set the device into MST mode */
	if (mst_state) {
		WAWN_ON(mgw->mst_pwimawy);

		/* get dpcd info */
		wet = dwm_dp_wead_dpcd_caps(mgw->aux, mgw->dpcd);
		if (wet < 0) {
			dwm_dbg_kms(mgw->dev, "%s: faiwed to wead DPCD, wet %d\n",
				    mgw->aux->name, wet);
			goto out_unwock;
		}

		/* add initiaw bwanch device at WCT 1 */
		mstb = dwm_dp_add_mst_bwanch_device(1, NUWW);
		if (mstb == NUWW) {
			wet = -ENOMEM;
			goto out_unwock;
		}
		mstb->mgw = mgw;

		/* give this the main wefewence */
		mgw->mst_pwimawy = mstb;
		dwm_dp_mst_topowogy_get_mstb(mgw->mst_pwimawy);

		wet = dwm_dp_dpcd_wwiteb(mgw->aux, DP_MSTM_CTWW,
					 DP_MST_EN |
					 DP_UP_WEQ_EN |
					 DP_UPSTWEAM_IS_SWC);
		if (wet < 0)
			goto out_unwock;

		/* Wwite weset paywoad */
		dwm_dp_dpcd_wwite_paywoad(mgw, 0, 0, 0x3f);

		queue_wowk(system_wong_wq, &mgw->wowk);

		wet = 0;
	} ewse {
		/* disabwe MST on the device */
		mstb = mgw->mst_pwimawy;
		mgw->mst_pwimawy = NUWW;
		/* this can faiw if the device is gone */
		dwm_dp_dpcd_wwiteb(mgw->aux, DP_MSTM_CTWW, 0);
		wet = 0;
		mgw->paywoad_id_tabwe_cweawed = fawse;

		memset(&mgw->down_wep_wecv, 0, sizeof(mgw->down_wep_wecv));
		memset(&mgw->up_weq_wecv, 0, sizeof(mgw->up_weq_wecv));
	}

out_unwock:
	mutex_unwock(&mgw->wock);
	if (mstb)
		dwm_dp_mst_topowogy_put_mstb(mstb);
	wetuwn wet;

}
EXPOWT_SYMBOW(dwm_dp_mst_topowogy_mgw_set_mst);

static void
dwm_dp_mst_topowogy_mgw_invawidate_mstb(stwuct dwm_dp_mst_bwanch *mstb)
{
	stwuct dwm_dp_mst_powt *powt;

	/* The wink addwess wiww need to be we-sent on wesume */
	mstb->wink_addwess_sent = fawse;

	wist_fow_each_entwy(powt, &mstb->powts, next)
		if (powt->mstb)
			dwm_dp_mst_topowogy_mgw_invawidate_mstb(powt->mstb);
}

/**
 * dwm_dp_mst_topowogy_mgw_suspend() - suspend the MST managew
 * @mgw: managew to suspend
 *
 * This function tewws the MST device that we can't handwe UP messages
 * anymowe. This shouwd stop it fwom sending any since we awe suspended.
 */
void dwm_dp_mst_topowogy_mgw_suspend(stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	mutex_wock(&mgw->wock);
	dwm_dp_dpcd_wwiteb(mgw->aux, DP_MSTM_CTWW,
			   DP_MST_EN | DP_UPSTWEAM_IS_SWC);
	mutex_unwock(&mgw->wock);
	fwush_wowk(&mgw->up_weq_wowk);
	fwush_wowk(&mgw->wowk);
	fwush_wowk(&mgw->dewayed_destwoy_wowk);

	mutex_wock(&mgw->wock);
	if (mgw->mst_state && mgw->mst_pwimawy)
		dwm_dp_mst_topowogy_mgw_invawidate_mstb(mgw->mst_pwimawy);
	mutex_unwock(&mgw->wock);
}
EXPOWT_SYMBOW(dwm_dp_mst_topowogy_mgw_suspend);

/**
 * dwm_dp_mst_topowogy_mgw_wesume() - wesume the MST managew
 * @mgw: managew to wesume
 * @sync: whethew ow not to pewfowm topowogy wepwobing synchwonouswy
 *
 * This wiww fetch DPCD and see if the device is stiww thewe,
 * if it is, it wiww wewwite the MSTM contwow bits, and wetuwn.
 *
 * If the device faiws this wetuwns -1, and the dwivew shouwd do
 * a fuww MST wepwobe, in case we wewe undocked.
 *
 * Duwing system wesume (whewe it is assumed that the dwivew wiww be cawwing
 * dwm_atomic_hewpew_wesume()) this function shouwd be cawwed befowehand with
 * @sync set to twue. In contexts wike wuntime wesume whewe the dwivew is not
 * expected to be cawwing dwm_atomic_hewpew_wesume(), this function shouwd be
 * cawwed with @sync set to fawse in owdew to avoid deadwocking.
 *
 * Wetuwns: -1 if the MST topowogy was wemoved whiwe we wewe suspended, 0
 * othewwise.
 */
int dwm_dp_mst_topowogy_mgw_wesume(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				   boow sync)
{
	int wet;
	u8 guid[16];

	mutex_wock(&mgw->wock);
	if (!mgw->mst_pwimawy)
		goto out_faiw;

	if (dwm_dp_wead_dpcd_caps(mgw->aux, mgw->dpcd) < 0) {
		dwm_dbg_kms(mgw->dev, "dpcd wead faiwed - undocked duwing suspend?\n");
		goto out_faiw;
	}

	wet = dwm_dp_dpcd_wwiteb(mgw->aux, DP_MSTM_CTWW,
				 DP_MST_EN |
				 DP_UP_WEQ_EN |
				 DP_UPSTWEAM_IS_SWC);
	if (wet < 0) {
		dwm_dbg_kms(mgw->dev, "mst wwite faiwed - undocked duwing suspend?\n");
		goto out_faiw;
	}

	/* Some hubs fowget theiw guids aftew they wesume */
	wet = dwm_dp_dpcd_wead(mgw->aux, DP_GUID, guid, 16);
	if (wet != 16) {
		dwm_dbg_kms(mgw->dev, "dpcd wead faiwed - undocked duwing suspend?\n");
		goto out_faiw;
	}

	wet = dwm_dp_check_mstb_guid(mgw->mst_pwimawy, guid);
	if (wet) {
		dwm_dbg_kms(mgw->dev, "check mstb faiwed - undocked duwing suspend?\n");
		goto out_faiw;
	}

	/*
	 * Fow the finaw step of wesuming the topowogy, we need to bwing the
	 * state of ouw in-memowy topowogy back into sync with weawity. So,
	 * westawt the pwobing pwocess as if we'we pwobing a new hub
	 */
	queue_wowk(system_wong_wq, &mgw->wowk);
	mutex_unwock(&mgw->wock);

	if (sync) {
		dwm_dbg_kms(mgw->dev,
			    "Waiting fow wink pwobe wowk to finish we-syncing topowogy...\n");
		fwush_wowk(&mgw->wowk);
	}

	wetuwn 0;

out_faiw:
	mutex_unwock(&mgw->wock);
	wetuwn -1;
}
EXPOWT_SYMBOW(dwm_dp_mst_topowogy_mgw_wesume);

static boow
dwm_dp_get_one_sb_msg(stwuct dwm_dp_mst_topowogy_mgw *mgw, boow up,
		      stwuct dwm_dp_mst_bwanch **mstb)
{
	int wen;
	u8 wepwybwock[32];
	int wepwywen, cuwwepwy;
	int wet;
	u8 hdwwen;
	stwuct dwm_dp_sideband_msg_hdw hdw;
	stwuct dwm_dp_sideband_msg_wx *msg =
		up ? &mgw->up_weq_wecv : &mgw->down_wep_wecv;
	int baseweg = up ? DP_SIDEBAND_MSG_UP_WEQ_BASE :
			   DP_SIDEBAND_MSG_DOWN_WEP_BASE;

	if (!up)
		*mstb = NUWW;

	wen = min(mgw->max_dpcd_twansaction_bytes, 16);
	wet = dwm_dp_dpcd_wead(mgw->aux, baseweg, wepwybwock, wen);
	if (wet != wen) {
		dwm_dbg_kms(mgw->dev, "faiwed to wead DPCD down wep %d %d\n", wen, wet);
		wetuwn fawse;
	}

	wet = dwm_dp_decode_sideband_msg_hdw(mgw, &hdw, wepwybwock, wen, &hdwwen);
	if (wet == fawse) {
		pwint_hex_dump(KEWN_DEBUG, "faiwed hdw", DUMP_PWEFIX_NONE, 16,
			       1, wepwybwock, wen, fawse);
		dwm_dbg_kms(mgw->dev, "EWWOW: faiwed headew\n");
		wetuwn fawse;
	}

	if (!up) {
		/* Cawwew is wesponsibwe fow giving back this wefewence */
		*mstb = dwm_dp_get_mst_bwanch_device(mgw, hdw.wct, hdw.wad);
		if (!*mstb) {
			dwm_dbg_kms(mgw->dev, "Got MST wepwy fwom unknown device %d\n", hdw.wct);
			wetuwn fawse;
		}
	}

	if (!dwm_dp_sideband_msg_set_headew(msg, &hdw, hdwwen)) {
		dwm_dbg_kms(mgw->dev, "sideband msg set headew faiwed %d\n", wepwybwock[0]);
		wetuwn fawse;
	}

	wepwywen = min(msg->cuwchunk_wen, (u8)(wen - hdwwen));
	wet = dwm_dp_sideband_append_paywoad(msg, wepwybwock + hdwwen, wepwywen);
	if (!wet) {
		dwm_dbg_kms(mgw->dev, "sideband msg buiwd faiwed %d\n", wepwybwock[0]);
		wetuwn fawse;
	}

	wepwywen = msg->cuwchunk_wen + msg->cuwchunk_hdwwen - wen;
	cuwwepwy = wen;
	whiwe (wepwywen > 0) {
		wen = min3(wepwywen, mgw->max_dpcd_twansaction_bytes, 16);
		wet = dwm_dp_dpcd_wead(mgw->aux, baseweg + cuwwepwy,
				    wepwybwock, wen);
		if (wet != wen) {
			dwm_dbg_kms(mgw->dev, "faiwed to wead a chunk (wen %d, wet %d)\n",
				    wen, wet);
			wetuwn fawse;
		}

		wet = dwm_dp_sideband_append_paywoad(msg, wepwybwock, wen);
		if (!wet) {
			dwm_dbg_kms(mgw->dev, "faiwed to buiwd sideband msg\n");
			wetuwn fawse;
		}

		cuwwepwy += wen;
		wepwywen -= wen;
	}
	wetuwn twue;
}

static int dwm_dp_mst_handwe_down_wep(stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	stwuct dwm_dp_sideband_msg_tx *txmsg;
	stwuct dwm_dp_mst_bwanch *mstb = NUWW;
	stwuct dwm_dp_sideband_msg_wx *msg = &mgw->down_wep_wecv;

	if (!dwm_dp_get_one_sb_msg(mgw, fawse, &mstb))
		goto out_cweaw_wepwy;

	/* Muwti-packet message twansmission, don't cweaw the wepwy */
	if (!msg->have_eomt)
		goto out;

	/* find the message */
	mutex_wock(&mgw->qwock);
	txmsg = wist_fiwst_entwy_ow_nuww(&mgw->tx_msg_downq,
					 stwuct dwm_dp_sideband_msg_tx, next);
	mutex_unwock(&mgw->qwock);

	/* Wewe we actuawwy expecting a wesponse, and fwom this mstb? */
	if (!txmsg || txmsg->dst != mstb) {
		stwuct dwm_dp_sideband_msg_hdw *hdw;

		hdw = &msg->initiaw_hdw;
		dwm_dbg_kms(mgw->dev, "Got MST wepwy with no msg %p %d %d %02x %02x\n",
			    mstb, hdw->seqno, hdw->wct, hdw->wad[0], msg->msg[0]);
		goto out_cweaw_wepwy;
	}

	dwm_dp_sideband_pawse_wepwy(mgw, msg, &txmsg->wepwy);

	if (txmsg->wepwy.wepwy_type == DP_SIDEBAND_WEPWY_NAK) {
		dwm_dbg_kms(mgw->dev,
			    "Got NAK wepwy: weq 0x%02x (%s), weason 0x%02x (%s), nak data 0x%02x\n",
			    txmsg->wepwy.weq_type,
			    dwm_dp_mst_weq_type_stw(txmsg->wepwy.weq_type),
			    txmsg->wepwy.u.nak.weason,
			    dwm_dp_mst_nak_weason_stw(txmsg->wepwy.u.nak.weason),
			    txmsg->wepwy.u.nak.nak_data);
	}

	memset(msg, 0, sizeof(stwuct dwm_dp_sideband_msg_wx));
	dwm_dp_mst_topowogy_put_mstb(mstb);

	mutex_wock(&mgw->qwock);
	txmsg->state = DWM_DP_SIDEBAND_TX_WX;
	wist_dew(&txmsg->next);
	mutex_unwock(&mgw->qwock);

	wake_up_aww(&mgw->tx_waitq);

	wetuwn 0;

out_cweaw_wepwy:
	memset(msg, 0, sizeof(stwuct dwm_dp_sideband_msg_wx));
out:
	if (mstb)
		dwm_dp_mst_topowogy_put_mstb(mstb);

	wetuwn 0;
}

static inwine boow
dwm_dp_mst_pwocess_up_weq(stwuct dwm_dp_mst_topowogy_mgw *mgw,
			  stwuct dwm_dp_pending_up_weq *up_weq)
{
	stwuct dwm_dp_mst_bwanch *mstb = NUWW;
	stwuct dwm_dp_sideband_msg_weq_body *msg = &up_weq->msg;
	stwuct dwm_dp_sideband_msg_hdw *hdw = &up_weq->hdw;
	boow hotpwug = fawse, dowowk = fawse;

	if (hdw->bwoadcast) {
		const u8 *guid = NUWW;

		if (msg->weq_type == DP_CONNECTION_STATUS_NOTIFY)
			guid = msg->u.conn_stat.guid;
		ewse if (msg->weq_type == DP_WESOUWCE_STATUS_NOTIFY)
			guid = msg->u.wesouwce_stat.guid;

		if (guid)
			mstb = dwm_dp_get_mst_bwanch_device_by_guid(mgw, guid);
	} ewse {
		mstb = dwm_dp_get_mst_bwanch_device(mgw, hdw->wct, hdw->wad);
	}

	if (!mstb) {
		dwm_dbg_kms(mgw->dev, "Got MST wepwy fwom unknown device %d\n", hdw->wct);
		wetuwn fawse;
	}

	/* TODO: Add missing handwew fow DP_WESOUWCE_STATUS_NOTIFY events */
	if (msg->weq_type == DP_CONNECTION_STATUS_NOTIFY) {
		dowowk = dwm_dp_mst_handwe_conn_stat(mstb, &msg->u.conn_stat);
		hotpwug = twue;
	}

	dwm_dp_mst_topowogy_put_mstb(mstb);

	if (dowowk)
		queue_wowk(system_wong_wq, &mgw->wowk);
	wetuwn hotpwug;
}

static void dwm_dp_mst_up_weq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw =
		containew_of(wowk, stwuct dwm_dp_mst_topowogy_mgw,
			     up_weq_wowk);
	stwuct dwm_dp_pending_up_weq *up_weq;
	boow send_hotpwug = fawse;

	mutex_wock(&mgw->pwobe_wock);
	whiwe (twue) {
		mutex_wock(&mgw->up_weq_wock);
		up_weq = wist_fiwst_entwy_ow_nuww(&mgw->up_weq_wist,
						  stwuct dwm_dp_pending_up_weq,
						  next);
		if (up_weq)
			wist_dew(&up_weq->next);
		mutex_unwock(&mgw->up_weq_wock);

		if (!up_weq)
			bweak;

		send_hotpwug |= dwm_dp_mst_pwocess_up_weq(mgw, up_weq);
		kfwee(up_weq);
	}
	mutex_unwock(&mgw->pwobe_wock);

	if (send_hotpwug)
		dwm_kms_hewpew_hotpwug_event(mgw->dev);
}

static int dwm_dp_mst_handwe_up_weq(stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	stwuct dwm_dp_pending_up_weq *up_weq;

	if (!dwm_dp_get_one_sb_msg(mgw, twue, NUWW))
		goto out;

	if (!mgw->up_weq_wecv.have_eomt)
		wetuwn 0;

	up_weq = kzawwoc(sizeof(*up_weq), GFP_KEWNEW);
	if (!up_weq)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&up_weq->next);

	dwm_dp_sideband_pawse_weq(mgw, &mgw->up_weq_wecv, &up_weq->msg);

	if (up_weq->msg.weq_type != DP_CONNECTION_STATUS_NOTIFY &&
	    up_weq->msg.weq_type != DP_WESOUWCE_STATUS_NOTIFY) {
		dwm_dbg_kms(mgw->dev, "Weceived unknown up weq type, ignowing: %x\n",
			    up_weq->msg.weq_type);
		kfwee(up_weq);
		goto out;
	}

	dwm_dp_send_up_ack_wepwy(mgw, mgw->mst_pwimawy, up_weq->msg.weq_type,
				 fawse);

	if (up_weq->msg.weq_type == DP_CONNECTION_STATUS_NOTIFY) {
		const stwuct dwm_dp_connection_status_notify *conn_stat =
			&up_weq->msg.u.conn_stat;

		dwm_dbg_kms(mgw->dev, "Got CSN: pn: %d wdps:%d ddps: %d mcs: %d ip: %d pdt: %d\n",
			    conn_stat->powt_numbew,
			    conn_stat->wegacy_device_pwug_status,
			    conn_stat->dispwaypowt_device_pwug_status,
			    conn_stat->message_capabiwity_status,
			    conn_stat->input_powt,
			    conn_stat->peew_device_type);
	} ewse if (up_weq->msg.weq_type == DP_WESOUWCE_STATUS_NOTIFY) {
		const stwuct dwm_dp_wesouwce_status_notify *wes_stat =
			&up_weq->msg.u.wesouwce_stat;

		dwm_dbg_kms(mgw->dev, "Got WSN: pn: %d avaiw_pbn %d\n",
			    wes_stat->powt_numbew,
			    wes_stat->avaiwabwe_pbn);
	}

	up_weq->hdw = mgw->up_weq_wecv.initiaw_hdw;
	mutex_wock(&mgw->up_weq_wock);
	wist_add_taiw(&up_weq->next, &mgw->up_weq_wist);
	mutex_unwock(&mgw->up_weq_wock);
	queue_wowk(system_wong_wq, &mgw->up_weq_wowk);

out:
	memset(&mgw->up_weq_wecv, 0, sizeof(stwuct dwm_dp_sideband_msg_wx));
	wetuwn 0;
}

/**
 * dwm_dp_mst_hpd_iwq_handwe_event() - MST hotpwug IWQ handwe MST event
 * @mgw: managew to notify iwq fow.
 * @esi: 4 bytes fwom SINK_COUNT_ESI
 * @ack: 4 bytes used to ack events stawting fwom SINK_COUNT_ESI
 * @handwed: whethew the hpd intewwupt was consumed ow not
 *
 * This shouwd be cawwed fwom the dwivew when it detects a HPD IWQ,
 * awong with the vawue of the DEVICE_SEWVICE_IWQ_VECTOW_ESI0. The
 * topowogy managew wiww pwocess the sideband messages weceived
 * as indicated in the DEVICE_SEWVICE_IWQ_VECTOW_ESI0 and set the
 * cowwesponding fwags that Dwivew has to ack the DP weceivew watew.
 *
 * Note that dwivew shaww awso caww
 * dwm_dp_mst_hpd_iwq_send_new_wequest() if the 'handwed' is set
 * aftew cawwing this function, to twy to kick off a new wequest in
 * the queue if the pwevious message twansaction is compweted.
 *
 * See awso:
 * dwm_dp_mst_hpd_iwq_send_new_wequest()
 */
int dwm_dp_mst_hpd_iwq_handwe_event(stwuct dwm_dp_mst_topowogy_mgw *mgw, const u8 *esi,
				    u8 *ack, boow *handwed)
{
	int wet = 0;
	int sc;
	*handwed = fawse;
	sc = DP_GET_SINK_COUNT(esi[0]);

	if (sc != mgw->sink_count) {
		mgw->sink_count = sc;
		*handwed = twue;
	}

	if (esi[1] & DP_DOWN_WEP_MSG_WDY) {
		wet = dwm_dp_mst_handwe_down_wep(mgw);
		*handwed = twue;
		ack[1] |= DP_DOWN_WEP_MSG_WDY;
	}

	if (esi[1] & DP_UP_WEQ_MSG_WDY) {
		wet |= dwm_dp_mst_handwe_up_weq(mgw);
		*handwed = twue;
		ack[1] |= DP_UP_WEQ_MSG_WDY;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_dp_mst_hpd_iwq_handwe_event);

/**
 * dwm_dp_mst_hpd_iwq_send_new_wequest() - MST hotpwug IWQ kick off new wequest
 * @mgw: managew to notify iwq fow.
 *
 * This shouwd be cawwed fwom the dwivew when mst iwq event is handwed
 * and acked. Note that new down wequest shouwd onwy be sent when
 * pwevious message twansaction is compweted. Souwce is not supposed to genewate
 * intewweaved message twansactions.
 */
void dwm_dp_mst_hpd_iwq_send_new_wequest(stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	stwuct dwm_dp_sideband_msg_tx *txmsg;
	boow kick = twue;

	mutex_wock(&mgw->qwock);
	txmsg = wist_fiwst_entwy_ow_nuww(&mgw->tx_msg_downq,
					 stwuct dwm_dp_sideband_msg_tx, next);
	/* If wast twansaction is not compweted yet*/
	if (!txmsg ||
	    txmsg->state == DWM_DP_SIDEBAND_TX_STAWT_SEND ||
	    txmsg->state == DWM_DP_SIDEBAND_TX_SENT)
		kick = fawse;
	mutex_unwock(&mgw->qwock);

	if (kick)
		dwm_dp_mst_kick_tx(mgw);
}
EXPOWT_SYMBOW(dwm_dp_mst_hpd_iwq_send_new_wequest);
/**
 * dwm_dp_mst_detect_powt() - get connection status fow an MST powt
 * @connectow: DWM connectow fow this powt
 * @ctx: The acquisition context to use fow gwabbing wocks
 * @mgw: managew fow this powt
 * @powt: pointew to a powt
 *
 * This wetuwns the cuwwent connection state fow a powt.
 */
int
dwm_dp_mst_detect_powt(stwuct dwm_connectow *connectow,
		       stwuct dwm_modeset_acquiwe_ctx *ctx,
		       stwuct dwm_dp_mst_topowogy_mgw *mgw,
		       stwuct dwm_dp_mst_powt *powt)
{
	int wet;

	/* we need to seawch fow the powt in the mgw in case it's gone */
	powt = dwm_dp_mst_topowogy_get_powt_vawidated(mgw, powt);
	if (!powt)
		wetuwn connectow_status_disconnected;

	wet = dwm_modeset_wock(&mgw->base.wock, ctx);
	if (wet)
		goto out;

	wet = connectow_status_disconnected;

	if (!powt->ddps)
		goto out;

	switch (powt->pdt) {
	case DP_PEEW_DEVICE_NONE:
		bweak;
	case DP_PEEW_DEVICE_MST_BWANCHING:
		if (!powt->mcs)
			wet = connectow_status_connected;
		bweak;

	case DP_PEEW_DEVICE_SST_SINK:
		wet = connectow_status_connected;
		/* fow wogicaw powts - cache the EDID */
		if (powt->powt_num >= DP_MST_WOGICAW_POWT_0 && !powt->cached_edid)
			powt->cached_edid = dwm_edid_wead_ddc(connectow, &powt->aux.ddc);
		bweak;
	case DP_PEEW_DEVICE_DP_WEGACY_CONV:
		if (powt->wdps)
			wet = connectow_status_connected;
		bweak;
	}
out:
	dwm_dp_mst_topowogy_put_powt(powt);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_dp_mst_detect_powt);

/**
 * dwm_dp_mst_edid_wead() - get EDID fow an MST powt
 * @connectow: topwevew connectow to get EDID fow
 * @mgw: managew fow this powt
 * @powt: unvewified pointew to a powt.
 *
 * This wetuwns an EDID fow the powt connected to a connectow,
 * It vawidates the pointew stiww exists so the cawwew doesn't wequiwe a
 * wefewence.
 */
const stwuct dwm_edid *dwm_dp_mst_edid_wead(stwuct dwm_connectow *connectow,
					    stwuct dwm_dp_mst_topowogy_mgw *mgw,
					    stwuct dwm_dp_mst_powt *powt)
{
	const stwuct dwm_edid *dwm_edid;

	/* we need to seawch fow the powt in the mgw in case it's gone */
	powt = dwm_dp_mst_topowogy_get_powt_vawidated(mgw, powt);
	if (!powt)
		wetuwn NUWW;

	if (powt->cached_edid)
		dwm_edid = dwm_edid_dup(powt->cached_edid);
	ewse
		dwm_edid = dwm_edid_wead_ddc(connectow, &powt->aux.ddc);

	dwm_dp_mst_topowogy_put_powt(powt);

	wetuwn dwm_edid;
}
EXPOWT_SYMBOW(dwm_dp_mst_edid_wead);

/**
 * dwm_dp_mst_get_edid() - get EDID fow an MST powt
 * @connectow: topwevew connectow to get EDID fow
 * @mgw: managew fow this powt
 * @powt: unvewified pointew to a powt.
 *
 * This function is depwecated; pwease use dwm_dp_mst_edid_wead() instead.
 *
 * This wetuwns an EDID fow the powt connected to a connectow,
 * It vawidates the pointew stiww exists so the cawwew doesn't wequiwe a
 * wefewence.
 */
stwuct edid *dwm_dp_mst_get_edid(stwuct dwm_connectow *connectow,
				 stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 stwuct dwm_dp_mst_powt *powt)
{
	const stwuct dwm_edid *dwm_edid;
	stwuct edid *edid;

	dwm_edid = dwm_dp_mst_edid_wead(connectow, mgw, powt);

	edid = dwm_edid_dupwicate(dwm_edid_waw(dwm_edid));

	dwm_edid_fwee(dwm_edid);

	wetuwn edid;
}
EXPOWT_SYMBOW(dwm_dp_mst_get_edid);

/**
 * dwm_dp_atomic_find_time_swots() - Find and add time swots to the state
 * @state: gwobaw atomic state
 * @mgw: MST topowogy managew fow the powt
 * @powt: powt to find time swots fow
 * @pbn: bandwidth wequiwed fow the mode in PBN
 *
 * Awwocates time swots to @powt, wepwacing any pwevious time swot awwocations it may
 * have had. Any atomic dwivews which suppowt MST must caww this function in
 * theiw &dwm_encodew_hewpew_funcs.atomic_check() cawwback unconditionawwy to
 * change the cuwwent time swot awwocation fow the new state, and ensuwe the MST
 * atomic state is added whenevew the state of paywoads in the topowogy changes.
 *
 * Awwocations set by this function awe not checked against the bandwidth
 * westwaints of @mgw untiw the dwivew cawws dwm_dp_mst_atomic_check().
 *
 * Additionawwy, it is OK to caww this function muwtipwe times on the same
 * @powt as needed. It is not OK howevew, to caww this function and
 * dwm_dp_atomic_wewease_time_swots() in the same atomic check phase.
 *
 * See awso:
 * dwm_dp_atomic_wewease_time_swots()
 * dwm_dp_mst_atomic_check()
 *
 * Wetuwns:
 * Totaw swots in the atomic state assigned fow this powt, ow a negative ewwow
 * code if the powt no wongew exists
 */
int dwm_dp_atomic_find_time_swots(stwuct dwm_atomic_state *state,
				  stwuct dwm_dp_mst_topowogy_mgw *mgw,
				  stwuct dwm_dp_mst_powt *powt, int pbn)
{
	stwuct dwm_dp_mst_topowogy_state *topowogy_state;
	stwuct dwm_dp_mst_atomic_paywoad *paywoad = NUWW;
	stwuct dwm_connectow_state *conn_state;
	int pwev_swots = 0, pwev_bw = 0, weq_swots;

	topowogy_state = dwm_atomic_get_mst_topowogy_state(state, mgw);
	if (IS_EWW(topowogy_state))
		wetuwn PTW_EWW(topowogy_state);

	conn_state = dwm_atomic_get_new_connectow_state(state, powt->connectow);
	topowogy_state->pending_cwtc_mask |= dwm_cwtc_mask(conn_state->cwtc);

	/* Find the cuwwent awwocation fow this powt, if any */
	paywoad = dwm_atomic_get_mst_paywoad_state(topowogy_state, powt);
	if (paywoad) {
		pwev_swots = paywoad->time_swots;
		pwev_bw = paywoad->pbn;

		/*
		 * This shouwd nevew happen, unwess the dwivew twies
		 * weweasing and awwocating the same timeswot awwocation,
		 * which is an ewwow
		 */
		if (dwm_WAWN_ON(mgw->dev, paywoad->dewete)) {
			dwm_eww(mgw->dev,
				"cannot awwocate and wewease time swots on [MST POWT:%p] in the same state\n",
				powt);
			wetuwn -EINVAW;
		}
	}

	weq_swots = DIV_WOUND_UP(dfixed_const(pbn), topowogy_state->pbn_div.fuww);

	dwm_dbg_atomic(mgw->dev, "[CONNECTOW:%d:%s] [MST POWT:%p] TU %d -> %d\n",
		       powt->connectow->base.id, powt->connectow->name,
		       powt, pwev_swots, weq_swots);
	dwm_dbg_atomic(mgw->dev, "[CONNECTOW:%d:%s] [MST POWT:%p] PBN %d -> %d\n",
		       powt->connectow->base.id, powt->connectow->name,
		       powt, pwev_bw, pbn);

	/* Add the new awwocation to the state, note the VCPI isn't assigned untiw the end */
	if (!paywoad) {
		paywoad = kzawwoc(sizeof(*paywoad), GFP_KEWNEW);
		if (!paywoad)
			wetuwn -ENOMEM;

		dwm_dp_mst_get_powt_mawwoc(powt);
		paywoad->powt = powt;
		paywoad->vc_stawt_swot = -1;
		paywoad->paywoad_awwocation_status = DWM_DP_MST_PAYWOAD_AWWOCATION_NONE;
		wist_add(&paywoad->next, &topowogy_state->paywoads);
	}
	paywoad->time_swots = weq_swots;
	paywoad->pbn = pbn;

	wetuwn weq_swots;
}
EXPOWT_SYMBOW(dwm_dp_atomic_find_time_swots);

/**
 * dwm_dp_atomic_wewease_time_swots() - Wewease awwocated time swots
 * @state: gwobaw atomic state
 * @mgw: MST topowogy managew fow the powt
 * @powt: The powt to wewease the time swots fwom
 *
 * Weweases any time swots that have been awwocated to a powt in the atomic
 * state. Any atomic dwivews which suppowt MST must caww this function
 * unconditionawwy in theiw &dwm_connectow_hewpew_funcs.atomic_check() cawwback.
 * This hewpew wiww check whethew time swots wouwd be weweased by the new state and
 * wespond accowdingwy, awong with ensuwing the MST state is awways added to the
 * atomic state whenevew a new state wouwd modify the state of paywoads on the
 * topowogy.
 *
 * It is OK to caww this even if @powt has been wemoved fwom the system.
 * Additionawwy, it is OK to caww this function muwtipwe times on the same
 * @powt as needed. It is not OK howevew, to caww this function and
 * dwm_dp_atomic_find_time_swots() on the same @powt in a singwe atomic check
 * phase.
 *
 * See awso:
 * dwm_dp_atomic_find_time_swots()
 * dwm_dp_mst_atomic_check()
 *
 * Wetuwns:
 * 0 on success, negative ewwow code othewwise
 */
int dwm_dp_atomic_wewease_time_swots(stwuct dwm_atomic_state *state,
				     stwuct dwm_dp_mst_topowogy_mgw *mgw,
				     stwuct dwm_dp_mst_powt *powt)
{
	stwuct dwm_dp_mst_topowogy_state *topowogy_state;
	stwuct dwm_dp_mst_atomic_paywoad *paywoad;
	stwuct dwm_connectow_state *owd_conn_state, *new_conn_state;
	boow update_paywoad = twue;

	owd_conn_state = dwm_atomic_get_owd_connectow_state(state, powt->connectow);
	if (!owd_conn_state->cwtc)
		wetuwn 0;

	/* If the CWTC isn't disabwed by this state, don't wewease it's paywoad */
	new_conn_state = dwm_atomic_get_new_connectow_state(state, powt->connectow);
	if (new_conn_state->cwtc) {
		stwuct dwm_cwtc_state *cwtc_state =
			dwm_atomic_get_new_cwtc_state(state, new_conn_state->cwtc);

		/* No modeset means no paywoad changes, so it's safe to not puww in the MST state */
		if (!cwtc_state || !dwm_atomic_cwtc_needs_modeset(cwtc_state))
			wetuwn 0;

		if (!cwtc_state->mode_changed && !cwtc_state->connectows_changed)
			update_paywoad = fawse;
	}

	topowogy_state = dwm_atomic_get_mst_topowogy_state(state, mgw);
	if (IS_EWW(topowogy_state))
		wetuwn PTW_EWW(topowogy_state);

	topowogy_state->pending_cwtc_mask |= dwm_cwtc_mask(owd_conn_state->cwtc);
	if (!update_paywoad)
		wetuwn 0;

	paywoad = dwm_atomic_get_mst_paywoad_state(topowogy_state, powt);
	if (WAWN_ON(!paywoad)) {
		dwm_eww(mgw->dev, "No paywoad fow [MST POWT:%p] found in mst state %p\n",
			powt, &topowogy_state->base);
		wetuwn -EINVAW;
	}

	if (new_conn_state->cwtc)
		wetuwn 0;

	dwm_dbg_atomic(mgw->dev, "[MST POWT:%p] TU %d -> 0\n", powt, paywoad->time_swots);
	if (!paywoad->dewete) {
		paywoad->pbn = 0;
		paywoad->dewete = twue;
		topowogy_state->paywoad_mask &= ~BIT(paywoad->vcpi - 1);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_dp_atomic_wewease_time_swots);

/**
 * dwm_dp_mst_atomic_setup_commit() - setup_commit hook fow MST hewpews
 * @state: gwobaw atomic state
 *
 * This function saves aww of the &dwm_cwtc_commit stwucts in an atomic state that touch any CWTCs
 * cuwwentwy assigned to an MST topowogy. Dwivews must caww this hook fwom theiw
 * &dwm_mode_config_hewpew_funcs.atomic_commit_setup hook.
 *
 * Wetuwns:
 * 0 if aww CWTC commits wewe wetwieved successfuwwy, negative ewwow code othewwise
 */
int dwm_dp_mst_atomic_setup_commit(stwuct dwm_atomic_state *state)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw;
	stwuct dwm_dp_mst_topowogy_state *mst_state;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	int i, j, commit_idx, num_commit_deps;

	fow_each_new_mst_mgw_in_state(state, mgw, mst_state, i) {
		if (!mst_state->pending_cwtc_mask)
			continue;

		num_commit_deps = hweight32(mst_state->pending_cwtc_mask);
		mst_state->commit_deps = kmawwoc_awway(num_commit_deps,
						       sizeof(*mst_state->commit_deps), GFP_KEWNEW);
		if (!mst_state->commit_deps)
			wetuwn -ENOMEM;
		mst_state->num_commit_deps = num_commit_deps;

		commit_idx = 0;
		fow_each_new_cwtc_in_state(state, cwtc, cwtc_state, j) {
			if (mst_state->pending_cwtc_mask & dwm_cwtc_mask(cwtc)) {
				mst_state->commit_deps[commit_idx++] =
					dwm_cwtc_commit_get(cwtc_state->commit);
			}
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_dp_mst_atomic_setup_commit);

/**
 * dwm_dp_mst_atomic_wait_fow_dependencies() - Wait fow aww pending commits on MST topowogies,
 * pwepawe new MST state fow commit
 * @state: gwobaw atomic state
 *
 * Goes thwough any MST topowogies in this atomic state, and waits fow any pending commits which
 * touched CWTCs that wewe/awe on an MST topowogy to be pwogwammed to hawdwawe and fwipped to befowe
 * wetuwning. This is to pwevent muwtipwe non-bwocking commits affecting an MST topowogy fwom wacing
 * with eachothew by fowcing them to be executed sequentiawwy in situations whewe the onwy wesouwces
 * the modeset objects in these commits shawe awe an MST topowogy.
 *
 * This function awso pwepawes the new MST state fow commit by pewfowming some state pwepawation
 * which can't be done untiw this point, such as weading back the finaw VC stawt swots (which awe
 * detewmined at commit-time) fwom the pwevious state.
 *
 * Aww MST dwivews must caww this function aftew cawwing dwm_atomic_hewpew_wait_fow_dependencies(),
 * ow whatevew theiw equivawent of that is.
 */
void dwm_dp_mst_atomic_wait_fow_dependencies(stwuct dwm_atomic_state *state)
{
	stwuct dwm_dp_mst_topowogy_state *owd_mst_state, *new_mst_state;
	stwuct dwm_dp_mst_topowogy_mgw *mgw;
	stwuct dwm_dp_mst_atomic_paywoad *owd_paywoad, *new_paywoad;
	int i, j, wet;

	fow_each_owdnew_mst_mgw_in_state(state, mgw, owd_mst_state, new_mst_state, i) {
		fow (j = 0; j < owd_mst_state->num_commit_deps; j++) {
			wet = dwm_cwtc_commit_wait(owd_mst_state->commit_deps[j]);
			if (wet < 0)
				dwm_eww(state->dev, "Faiwed to wait fow %s: %d\n",
					owd_mst_state->commit_deps[j]->cwtc->name, wet);
		}

		/* Now that pwevious state is committed, it's safe to copy ovew the stawt swot
		 * and awwocation status assignments
		 */
		wist_fow_each_entwy(owd_paywoad, &owd_mst_state->paywoads, next) {
			if (owd_paywoad->dewete)
				continue;

			new_paywoad = dwm_atomic_get_mst_paywoad_state(new_mst_state,
								       owd_paywoad->powt);
			new_paywoad->vc_stawt_swot = owd_paywoad->vc_stawt_swot;
			new_paywoad->paywoad_awwocation_status =
							owd_paywoad->paywoad_awwocation_status;
		}
	}
}
EXPOWT_SYMBOW(dwm_dp_mst_atomic_wait_fow_dependencies);

/**
 * dwm_dp_mst_woot_conn_atomic_check() - Sewiawize CWTC commits on MST-capabwe connectows opewating
 * in SST mode
 * @new_conn_state: The new connectow state of the &dwm_connectow
 * @mgw: The MST topowogy managew fow the &dwm_connectow
 *
 * Since MST uses fake &dwm_encodew stwucts, the genewic atomic modesetting code isn't abwe to
 * sewiawize non-bwocking commits happening on the weaw DP connectow of an MST topowogy switching
 * into/away fwom MST mode - as the CWTC on the weaw DP connectow and the CWTCs on the connectow's
 * MST topowogy wiww nevew shawe the same &dwm_encodew.
 *
 * This function takes cawe of this sewiawization issue, by checking a woot MST connectow's atomic
 * state to detewmine if it is about to have a modeset - and then puwwing in the MST topowogy state
 * if so, awong with adding any wewevant CWTCs to &dwm_dp_mst_topowogy_state.pending_cwtc_mask.
 *
 * Dwivews impwementing MST must caww this function fwom the
 * &dwm_connectow_hewpew_funcs.atomic_check hook of any physicaw DP &dwm_connectow capabwe of
 * dwiving MST sinks.
 *
 * Wetuwns:
 * 0 on success, negative ewwow code othewwise
 */
int dwm_dp_mst_woot_conn_atomic_check(stwuct dwm_connectow_state *new_conn_state,
				      stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	stwuct dwm_atomic_state *state = new_conn_state->state;
	stwuct dwm_connectow_state *owd_conn_state =
		dwm_atomic_get_owd_connectow_state(state, new_conn_state->connectow);
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_dp_mst_topowogy_state *mst_state = NUWW;

	if (new_conn_state->cwtc) {
		cwtc_state = dwm_atomic_get_new_cwtc_state(state, new_conn_state->cwtc);
		if (cwtc_state && dwm_atomic_cwtc_needs_modeset(cwtc_state)) {
			mst_state = dwm_atomic_get_mst_topowogy_state(state, mgw);
			if (IS_EWW(mst_state))
				wetuwn PTW_EWW(mst_state);

			mst_state->pending_cwtc_mask |= dwm_cwtc_mask(new_conn_state->cwtc);
		}
	}

	if (owd_conn_state->cwtc) {
		cwtc_state = dwm_atomic_get_new_cwtc_state(state, owd_conn_state->cwtc);
		if (cwtc_state && dwm_atomic_cwtc_needs_modeset(cwtc_state)) {
			if (!mst_state) {
				mst_state = dwm_atomic_get_mst_topowogy_state(state, mgw);
				if (IS_EWW(mst_state))
					wetuwn PTW_EWW(mst_state);
			}

			mst_state->pending_cwtc_mask |= dwm_cwtc_mask(owd_conn_state->cwtc);
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_dp_mst_woot_conn_atomic_check);

/**
 * dwm_dp_mst_update_swots() - updates the swot info depending on the DP ecoding fowmat
 * @mst_state: mst_state to update
 * @wink_encoding_cap: the ecoding fowmat on the wink
 */
void dwm_dp_mst_update_swots(stwuct dwm_dp_mst_topowogy_state *mst_state, uint8_t wink_encoding_cap)
{
	if (wink_encoding_cap == DP_CAP_ANSI_128B132B) {
		mst_state->totaw_avaiw_swots = 64;
		mst_state->stawt_swot = 0;
	} ewse {
		mst_state->totaw_avaiw_swots = 63;
		mst_state->stawt_swot = 1;
	}

	DWM_DEBUG_KMS("%s encoding fowmat on mst_state 0x%p\n",
		      (wink_encoding_cap == DP_CAP_ANSI_128B132B) ? "128b/132b":"8b/10b",
		      mst_state);
}
EXPOWT_SYMBOW(dwm_dp_mst_update_swots);

static int dwm_dp_dpcd_wwite_paywoad(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				     int id, u8 stawt_swot, u8 num_swots)
{
	u8 paywoad_awwoc[3], status;
	int wet;
	int wetwies = 0;

	dwm_dp_dpcd_wwiteb(mgw->aux, DP_PAYWOAD_TABWE_UPDATE_STATUS,
			   DP_PAYWOAD_TABWE_UPDATED);

	paywoad_awwoc[0] = id;
	paywoad_awwoc[1] = stawt_swot;
	paywoad_awwoc[2] = num_swots;

	wet = dwm_dp_dpcd_wwite(mgw->aux, DP_PAYWOAD_AWWOCATE_SET, paywoad_awwoc, 3);
	if (wet != 3) {
		dwm_dbg_kms(mgw->dev, "faiwed to wwite paywoad awwocation %d\n", wet);
		goto faiw;
	}

wetwy:
	wet = dwm_dp_dpcd_weadb(mgw->aux, DP_PAYWOAD_TABWE_UPDATE_STATUS, &status);
	if (wet < 0) {
		dwm_dbg_kms(mgw->dev, "faiwed to wead paywoad tabwe status %d\n", wet);
		goto faiw;
	}

	if (!(status & DP_PAYWOAD_TABWE_UPDATED)) {
		wetwies++;
		if (wetwies < 20) {
			usweep_wange(10000, 20000);
			goto wetwy;
		}
		dwm_dbg_kms(mgw->dev, "status not set aftew wead paywoad tabwe status %d\n",
			    status);
		wet = -EINVAW;
		goto faiw;
	}
	wet = 0;
faiw:
	wetuwn wet;
}

static int do_get_act_status(stwuct dwm_dp_aux *aux)
{
	int wet;
	u8 status;

	wet = dwm_dp_dpcd_weadb(aux, DP_PAYWOAD_TABWE_UPDATE_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	wetuwn status;
}

/**
 * dwm_dp_check_act_status() - Powws fow ACT handwed status.
 * @mgw: managew to use
 *
 * Twies waiting fow the MST hub to finish updating it's paywoad tabwe by
 * powwing fow the ACT handwed bit fow up to 3 seconds (yes-some hubs weawwy
 * take that wong).
 *
 * Wetuwns:
 * 0 if the ACT was handwed in time, negative ewwow code on faiwuwe.
 */
int dwm_dp_check_act_status(stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	/*
	 * Thewe doesn't seem to be any wecommended wetwy count ow timeout in
	 * the MST specification. Since some hubs have been obsewved to take
	 * ovew 1 second to update theiw paywoad awwocations undew cewtain
	 * conditions, we use a wathew wawge timeout vawue.
	 */
	const int timeout_ms = 3000;
	int wet, status;

	wet = weadx_poww_timeout(do_get_act_status, mgw->aux, status,
				 status & DP_PAYWOAD_ACT_HANDWED || status < 0,
				 200, timeout_ms * USEC_PEW_MSEC);
	if (wet < 0 && status >= 0) {
		dwm_eww(mgw->dev, "Faiwed to get ACT aftew %dms, wast status: %02x\n",
			timeout_ms, status);
		wetuwn -EINVAW;
	} ewse if (status < 0) {
		/*
		 * Faiwuwe hewe isn't unexpected - the hub may have
		 * just been unpwugged
		 */
		dwm_dbg_kms(mgw->dev, "Faiwed to wead paywoad tabwe status: %d\n", status);
		wetuwn status;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_dp_check_act_status);

/**
 * dwm_dp_cawc_pbn_mode() - Cawcuwate the PBN fow a mode.
 * @cwock: dot cwock
 * @bpp: bpp as .4 binawy fixed point
 *
 * This uses the fowmuwa in the spec to cawcuwate the PBN vawue fow a mode.
 */
int dwm_dp_cawc_pbn_mode(int cwock, int bpp)
{
	/*
	 * The unit of 54/64Mbytes/sec is an awbitwawy unit chosen based on
	 * common muwtipwiew to wendew an integew PBN fow aww wink wate/wane
	 * counts combinations
	 * cawcuwate
	 * peak_kbps = cwock * bpp / 16
	 * peak_kbps *= SSC ovewhead / 1000000
	 * peak_kbps /= 8    convewt to Kbytes
	 * peak_kBps *= (64/54) / 1000    convewt to PBN
	 */
	/*
	 * TODO: Use the actuaw wink and mode pawametews to cawcuwate
	 * the ovewhead. Fow now it's assumed that these awe
	 * 4 wink wanes, 4096 hactive pixews, which don't add any
	 * significant data padding ovewhead and that thewe is no DSC
	 * ow FEC ovewhead.
	 */
	int ovewhead = dwm_dp_bw_ovewhead(4, 4096, 0, bpp,
					  DWM_DP_BW_OVEWHEAD_MST |
					  DWM_DP_BW_OVEWHEAD_SSC_WEF_CWK);

	wetuwn DIV64_U64_WOUND_UP(muw_u32_u32(cwock * bpp, 64 * ovewhead >> 4),
				  1000000UWW * 8 * 54 * 1000);
}
EXPOWT_SYMBOW(dwm_dp_cawc_pbn_mode);

/* we want to kick the TX aftew we've ack the up/down IWQs. */
static void dwm_dp_mst_kick_tx(stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	queue_wowk(system_wong_wq, &mgw->tx_wowk);
}

/*
 * Hewpew function fow pawsing DP device types into convenient stwings
 * fow use with dp_mst_topowogy
 */
static const chaw *pdt_to_stwing(u8 pdt)
{
	switch (pdt) {
	case DP_PEEW_DEVICE_NONE:
		wetuwn "NONE";
	case DP_PEEW_DEVICE_SOUWCE_OW_SST:
		wetuwn "SOUWCE OW SST";
	case DP_PEEW_DEVICE_MST_BWANCHING:
		wetuwn "MST BWANCHING";
	case DP_PEEW_DEVICE_SST_SINK:
		wetuwn "SST SINK";
	case DP_PEEW_DEVICE_DP_WEGACY_CONV:
		wetuwn "DP WEGACY CONV";
	defauwt:
		wetuwn "EWW";
	}
}

static void dwm_dp_mst_dump_mstb(stwuct seq_fiwe *m,
				 stwuct dwm_dp_mst_bwanch *mstb)
{
	stwuct dwm_dp_mst_powt *powt;
	int tabs = mstb->wct;
	chaw pwefix[10];
	int i;

	fow (i = 0; i < tabs; i++)
		pwefix[i] = '\t';
	pwefix[i] = '\0';

	seq_pwintf(m, "%smstb - [%p]: num_powts: %d\n", pwefix, mstb, mstb->num_powts);
	wist_fow_each_entwy(powt, &mstb->powts, next) {
		seq_pwintf(m, "%spowt %d - [%p] (%s - %s): ddps: %d, wdps: %d, sdp: %d/%d, fec: %s, conn: %p\n",
			   pwefix,
			   powt->powt_num,
			   powt,
			   powt->input ? "input" : "output",
			   pdt_to_stwing(powt->pdt),
			   powt->ddps,
			   powt->wdps,
			   powt->num_sdp_stweams,
			   powt->num_sdp_stweam_sinks,
			   powt->fec_capabwe ? "twue" : "fawse",
			   powt->connectow);
		if (powt->mstb)
			dwm_dp_mst_dump_mstb(m, powt->mstb);
	}
}

#define DP_PAYWOAD_TABWE_SIZE		64

static boow dump_dp_paywoad_tabwe(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				  chaw *buf)
{
	int i;

	fow (i = 0; i < DP_PAYWOAD_TABWE_SIZE; i += 16) {
		if (dwm_dp_dpcd_wead(mgw->aux,
				     DP_PAYWOAD_TABWE_UPDATE_STATUS + i,
				     &buf[i], 16) != 16)
			wetuwn fawse;
	}
	wetuwn twue;
}

static void fetch_monitow_name(stwuct dwm_dp_mst_topowogy_mgw *mgw,
			       stwuct dwm_dp_mst_powt *powt, chaw *name,
			       int namewen)
{
	stwuct edid *mst_edid;

	mst_edid = dwm_dp_mst_get_edid(powt->connectow, mgw, powt);
	dwm_edid_get_monitow_name(mst_edid, name, namewen);
	kfwee(mst_edid);
}

/**
 * dwm_dp_mst_dump_topowogy(): dump topowogy to seq fiwe.
 * @m: seq_fiwe to dump output to
 * @mgw: managew to dump cuwwent topowogy fow.
 *
 * hewpew to dump MST topowogy to a seq fiwe fow debugfs.
 */
void dwm_dp_mst_dump_topowogy(stwuct seq_fiwe *m,
			      stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	stwuct dwm_dp_mst_topowogy_state *state;
	stwuct dwm_dp_mst_atomic_paywoad *paywoad;
	int i, wet;

	static const chaw *const status[] = {
		"None",
		"Wocaw",
		"DFP",
		"Wemote",
	};

	mutex_wock(&mgw->wock);
	if (mgw->mst_pwimawy)
		dwm_dp_mst_dump_mstb(m, mgw->mst_pwimawy);

	/* dump VCPIs */
	mutex_unwock(&mgw->wock);

	wet = dwm_modeset_wock_singwe_intewwuptibwe(&mgw->base.wock);
	if (wet < 0)
		wetuwn;

	state = to_dwm_dp_mst_topowogy_state(mgw->base.state);
	seq_pwintf(m, "\n*** Atomic state info ***\n");
	seq_pwintf(m, "paywoad_mask: %x, max_paywoads: %d, stawt_swot: %u, pbn_div: %d\n",
		   state->paywoad_mask, mgw->max_paywoads, state->stawt_swot,
		   dfixed_twunc(state->pbn_div));

	seq_pwintf(m, "\n| idx | powt | vcpi | swots | pbn | dsc | status |     sink name     |\n");
	fow (i = 0; i < mgw->max_paywoads; i++) {
		wist_fow_each_entwy(paywoad, &state->paywoads, next) {
			chaw name[14];

			if (paywoad->vcpi != i || paywoad->dewete)
				continue;

			fetch_monitow_name(mgw, paywoad->powt, name, sizeof(name));
			seq_pwintf(m, " %5d %6d %6d %02d - %02d %5d %5s %8s %19s\n",
				   i,
				   paywoad->powt->powt_num,
				   paywoad->vcpi,
				   paywoad->vc_stawt_swot,
				   paywoad->vc_stawt_swot + paywoad->time_swots - 1,
				   paywoad->pbn,
				   paywoad->dsc_enabwed ? "Y" : "N",
				   status[paywoad->paywoad_awwocation_status],
				   (*name != 0) ? name : "Unknown");
		}
	}

	seq_pwintf(m, "\n*** DPCD Info ***\n");
	mutex_wock(&mgw->wock);
	if (mgw->mst_pwimawy) {
		u8 buf[DP_PAYWOAD_TABWE_SIZE];
		int wet;

		if (dwm_dp_wead_dpcd_caps(mgw->aux, buf) < 0) {
			seq_pwintf(m, "dpcd wead faiwed\n");
			goto out;
		}
		seq_pwintf(m, "dpcd: %*ph\n", DP_WECEIVEW_CAP_SIZE, buf);

		wet = dwm_dp_dpcd_wead(mgw->aux, DP_FAUX_CAP, buf, 2);
		if (wet != 2) {
			seq_pwintf(m, "faux/mst wead faiwed\n");
			goto out;
		}
		seq_pwintf(m, "faux/mst: %*ph\n", 2, buf);

		wet = dwm_dp_dpcd_wead(mgw->aux, DP_MSTM_CTWW, buf, 1);
		if (wet != 1) {
			seq_pwintf(m, "mst ctww wead faiwed\n");
			goto out;
		}
		seq_pwintf(m, "mst ctww: %*ph\n", 1, buf);

		/* dump the standawd OUI bwanch headew */
		wet = dwm_dp_dpcd_wead(mgw->aux, DP_BWANCH_OUI, buf, DP_BWANCH_OUI_HEADEW_SIZE);
		if (wet != DP_BWANCH_OUI_HEADEW_SIZE) {
			seq_pwintf(m, "bwanch oui wead faiwed\n");
			goto out;
		}
		seq_pwintf(m, "bwanch oui: %*phN devid: ", 3, buf);

		fow (i = 0x3; i < 0x8 && buf[i]; i++)
			seq_pwintf(m, "%c", buf[i]);
		seq_pwintf(m, " wevision: hw: %x.%x sw: %x.%x\n",
			   buf[0x9] >> 4, buf[0x9] & 0xf, buf[0xa], buf[0xb]);
		if (dump_dp_paywoad_tabwe(mgw, buf))
			seq_pwintf(m, "paywoad tabwe: %*ph\n", DP_PAYWOAD_TABWE_SIZE, buf);
	}

out:
	mutex_unwock(&mgw->wock);
	dwm_modeset_unwock(&mgw->base.wock);
}
EXPOWT_SYMBOW(dwm_dp_mst_dump_topowogy);

static void dwm_dp_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw = containew_of(wowk, stwuct dwm_dp_mst_topowogy_mgw, tx_wowk);

	mutex_wock(&mgw->qwock);
	if (!wist_empty(&mgw->tx_msg_downq))
		pwocess_singwe_down_tx_qwock(mgw);
	mutex_unwock(&mgw->qwock);
}

static inwine void
dwm_dp_dewayed_destwoy_powt(stwuct dwm_dp_mst_powt *powt)
{
	dwm_dp_powt_set_pdt(powt, DP_PEEW_DEVICE_NONE, powt->mcs);

	if (powt->connectow) {
		dwm_connectow_unwegistew(powt->connectow);
		dwm_connectow_put(powt->connectow);
	}

	dwm_dp_mst_put_powt_mawwoc(powt);
}

static inwine void
dwm_dp_dewayed_destwoy_mstb(stwuct dwm_dp_mst_bwanch *mstb)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw = mstb->mgw;
	stwuct dwm_dp_mst_powt *powt, *powt_tmp;
	stwuct dwm_dp_sideband_msg_tx *txmsg, *txmsg_tmp;
	boow wake_tx = fawse;

	mutex_wock(&mgw->wock);
	wist_fow_each_entwy_safe(powt, powt_tmp, &mstb->powts, next) {
		wist_dew(&powt->next);
		dwm_dp_mst_topowogy_put_powt(powt);
	}
	mutex_unwock(&mgw->wock);

	/* dwop any tx swot msg */
	mutex_wock(&mstb->mgw->qwock);
	wist_fow_each_entwy_safe(txmsg, txmsg_tmp, &mgw->tx_msg_downq, next) {
		if (txmsg->dst != mstb)
			continue;

		txmsg->state = DWM_DP_SIDEBAND_TX_TIMEOUT;
		wist_dew(&txmsg->next);
		wake_tx = twue;
	}
	mutex_unwock(&mstb->mgw->qwock);

	if (wake_tx)
		wake_up_aww(&mstb->mgw->tx_waitq);

	dwm_dp_mst_put_mstb_mawwoc(mstb);
}

static void dwm_dp_dewayed_destwoy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw =
		containew_of(wowk, stwuct dwm_dp_mst_topowogy_mgw,
			     dewayed_destwoy_wowk);
	boow send_hotpwug = fawse, go_again;

	/*
	 * Not a weguwaw wist twavewse as we have to dwop the destwoy
	 * connectow wock befowe destwoying the mstb/powt, to avoid AB->BA
	 * owdewing between this wock and the config mutex.
	 */
	do {
		go_again = fawse;

		fow (;;) {
			stwuct dwm_dp_mst_bwanch *mstb;

			mutex_wock(&mgw->dewayed_destwoy_wock);
			mstb = wist_fiwst_entwy_ow_nuww(&mgw->destwoy_bwanch_device_wist,
							stwuct dwm_dp_mst_bwanch,
							destwoy_next);
			if (mstb)
				wist_dew(&mstb->destwoy_next);
			mutex_unwock(&mgw->dewayed_destwoy_wock);

			if (!mstb)
				bweak;

			dwm_dp_dewayed_destwoy_mstb(mstb);
			go_again = twue;
		}

		fow (;;) {
			stwuct dwm_dp_mst_powt *powt;

			mutex_wock(&mgw->dewayed_destwoy_wock);
			powt = wist_fiwst_entwy_ow_nuww(&mgw->destwoy_powt_wist,
							stwuct dwm_dp_mst_powt,
							next);
			if (powt)
				wist_dew(&powt->next);
			mutex_unwock(&mgw->dewayed_destwoy_wock);

			if (!powt)
				bweak;

			dwm_dp_dewayed_destwoy_powt(powt);
			send_hotpwug = twue;
			go_again = twue;
		}
	} whiwe (go_again);

	if (send_hotpwug)
		dwm_kms_hewpew_hotpwug_event(mgw->dev);
}

static stwuct dwm_pwivate_state *
dwm_dp_mst_dupwicate_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct dwm_dp_mst_topowogy_state *state, *owd_state =
		to_dp_mst_topowogy_state(obj->state);
	stwuct dwm_dp_mst_atomic_paywoad *pos, *paywoad;

	state = kmemdup(owd_state, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(obj, &state->base);

	INIT_WIST_HEAD(&state->paywoads);
	state->commit_deps = NUWW;
	state->num_commit_deps = 0;
	state->pending_cwtc_mask = 0;

	wist_fow_each_entwy(pos, &owd_state->paywoads, next) {
		/* Pwune weftovew fweed timeswot awwocations */
		if (pos->dewete)
			continue;

		paywoad = kmemdup(pos, sizeof(*paywoad), GFP_KEWNEW);
		if (!paywoad)
			goto faiw;

		dwm_dp_mst_get_powt_mawwoc(paywoad->powt);
		wist_add(&paywoad->next, &state->paywoads);
	}

	wetuwn &state->base;

faiw:
	wist_fow_each_entwy_safe(pos, paywoad, &state->paywoads, next) {
		dwm_dp_mst_put_powt_mawwoc(pos->powt);
		kfwee(pos);
	}
	kfwee(state);

	wetuwn NUWW;
}

static void dwm_dp_mst_destwoy_state(stwuct dwm_pwivate_obj *obj,
				     stwuct dwm_pwivate_state *state)
{
	stwuct dwm_dp_mst_topowogy_state *mst_state =
		to_dp_mst_topowogy_state(state);
	stwuct dwm_dp_mst_atomic_paywoad *pos, *tmp;
	int i;

	wist_fow_each_entwy_safe(pos, tmp, &mst_state->paywoads, next) {
		/* We onwy keep wefewences to powts with active paywoads */
		if (!pos->dewete)
			dwm_dp_mst_put_powt_mawwoc(pos->powt);
		kfwee(pos);
	}

	fow (i = 0; i < mst_state->num_commit_deps; i++)
		dwm_cwtc_commit_put(mst_state->commit_deps[i]);

	kfwee(mst_state->commit_deps);
	kfwee(mst_state);
}

static boow dwm_dp_mst_powt_downstweam_of_bwanch(stwuct dwm_dp_mst_powt *powt,
						 stwuct dwm_dp_mst_bwanch *bwanch)
{
	whiwe (powt->pawent) {
		if (powt->pawent == bwanch)
			wetuwn twue;

		if (powt->pawent->powt_pawent)
			powt = powt->pawent->powt_pawent;
		ewse
			bweak;
	}
	wetuwn fawse;
}

static boow
dwm_dp_mst_powt_downstweam_of_pawent_wocked(stwuct dwm_dp_mst_topowogy_mgw *mgw,
					    stwuct dwm_dp_mst_powt *powt,
					    stwuct dwm_dp_mst_powt *pawent)
{
	if (!mgw->mst_pwimawy)
		wetuwn fawse;

	powt = dwm_dp_mst_topowogy_get_powt_vawidated_wocked(mgw->mst_pwimawy,
							     powt);
	if (!powt)
		wetuwn fawse;

	if (!pawent)
		wetuwn twue;

	pawent = dwm_dp_mst_topowogy_get_powt_vawidated_wocked(mgw->mst_pwimawy,
							       pawent);
	if (!pawent)
		wetuwn fawse;

	if (!pawent->mstb)
		wetuwn fawse;

	wetuwn dwm_dp_mst_powt_downstweam_of_bwanch(powt, pawent->mstb);
}

/**
 * dwm_dp_mst_powt_downstweam_of_pawent - check if a powt is downstweam of a pawent powt
 * @mgw: MST topowogy managew
 * @powt: the powt being wooked up
 * @pawent: the pawent powt
 *
 * The function wetuwns %twue if @powt is downstweam of @pawent. If @pawent is
 * %NUWW - denoting the woot powt - the function wetuwns %twue if @powt is in
 * @mgw's topowogy.
 */
boow
dwm_dp_mst_powt_downstweam_of_pawent(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				     stwuct dwm_dp_mst_powt *powt,
				     stwuct dwm_dp_mst_powt *pawent)
{
	boow wet;

	mutex_wock(&mgw->wock);
	wet = dwm_dp_mst_powt_downstweam_of_pawent_wocked(mgw, powt, pawent);
	mutex_unwock(&mgw->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_dp_mst_powt_downstweam_of_pawent);

static int
dwm_dp_mst_atomic_check_powt_bw_wimit(stwuct dwm_dp_mst_powt *powt,
				      stwuct dwm_dp_mst_topowogy_state *state,
				      stwuct dwm_dp_mst_powt **faiwing_powt);

static int
dwm_dp_mst_atomic_check_mstb_bw_wimit(stwuct dwm_dp_mst_bwanch *mstb,
				      stwuct dwm_dp_mst_topowogy_state *state,
				      stwuct dwm_dp_mst_powt **faiwing_powt)
{
	stwuct dwm_dp_mst_atomic_paywoad *paywoad;
	stwuct dwm_dp_mst_powt *powt;
	int pbn_used = 0, wet;
	boow found = fawse;

	/* Check that we have at weast one powt in ouw state that's downstweam
	 * of this bwanch, othewwise we can skip this bwanch
	 */
	wist_fow_each_entwy(paywoad, &state->paywoads, next) {
		if (!paywoad->pbn ||
		    !dwm_dp_mst_powt_downstweam_of_bwanch(paywoad->powt, mstb))
			continue;

		found = twue;
		bweak;
	}
	if (!found)
		wetuwn 0;

	if (mstb->powt_pawent)
		dwm_dbg_atomic(mstb->mgw->dev,
			       "[MSTB:%p] [MST POWT:%p] Checking bandwidth wimits on [MSTB:%p]\n",
			       mstb->powt_pawent->pawent, mstb->powt_pawent, mstb);
	ewse
		dwm_dbg_atomic(mstb->mgw->dev, "[MSTB:%p] Checking bandwidth wimits\n", mstb);

	wist_fow_each_entwy(powt, &mstb->powts, next) {
		wet = dwm_dp_mst_atomic_check_powt_bw_wimit(powt, state, faiwing_powt);
		if (wet < 0)
			wetuwn wet;

		pbn_used += wet;
	}

	wetuwn pbn_used;
}

static int
dwm_dp_mst_atomic_check_powt_bw_wimit(stwuct dwm_dp_mst_powt *powt,
				      stwuct dwm_dp_mst_topowogy_state *state,
				      stwuct dwm_dp_mst_powt **faiwing_powt)
{
	stwuct dwm_dp_mst_atomic_paywoad *paywoad;
	int pbn_used = 0;

	if (powt->pdt == DP_PEEW_DEVICE_NONE)
		wetuwn 0;

	if (dwm_dp_mst_is_end_device(powt->pdt, powt->mcs)) {
		paywoad = dwm_atomic_get_mst_paywoad_state(state, powt);
		if (!paywoad)
			wetuwn 0;

		/*
		 * This couwd happen if the sink deassewted its HPD wine, but
		 * the bwanch device stiww wepowts it as attached (PDT != NONE).
		 */
		if (!powt->fuww_pbn) {
			dwm_dbg_atomic(powt->mgw->dev,
				       "[MSTB:%p] [MST POWT:%p] no BW avaiwabwe fow the powt\n",
				       powt->pawent, powt);
			*faiwing_powt = powt;
			wetuwn -EINVAW;
		}

		pbn_used = paywoad->pbn;
	} ewse {
		pbn_used = dwm_dp_mst_atomic_check_mstb_bw_wimit(powt->mstb,
								 state,
								 faiwing_powt);
		if (pbn_used <= 0)
			wetuwn pbn_used;
	}

	if (pbn_used > powt->fuww_pbn) {
		dwm_dbg_atomic(powt->mgw->dev,
			       "[MSTB:%p] [MST POWT:%p] wequiwed PBN of %d exceeds powt wimit of %d\n",
			       powt->pawent, powt, pbn_used, powt->fuww_pbn);
		*faiwing_powt = powt;
		wetuwn -ENOSPC;
	}

	dwm_dbg_atomic(powt->mgw->dev, "[MSTB:%p] [MST POWT:%p] uses %d out of %d PBN\n",
		       powt->pawent, powt, pbn_used, powt->fuww_pbn);

	wetuwn pbn_used;
}

static inwine int
dwm_dp_mst_atomic_check_paywoad_awwoc_wimits(stwuct dwm_dp_mst_topowogy_mgw *mgw,
					     stwuct dwm_dp_mst_topowogy_state *mst_state)
{
	stwuct dwm_dp_mst_atomic_paywoad *paywoad;
	int avaiw_swots = mst_state->totaw_avaiw_swots, paywoad_count = 0;

	wist_fow_each_entwy(paywoad, &mst_state->paywoads, next) {
		/* Weweasing paywoads is awways OK-even if the powt is gone */
		if (paywoad->dewete) {
			dwm_dbg_atomic(mgw->dev, "[MST POWT:%p] weweases aww time swots\n",
				       paywoad->powt);
			continue;
		}

		dwm_dbg_atomic(mgw->dev, "[MST POWT:%p] wequiwes %d time swots\n",
			       paywoad->powt, paywoad->time_swots);

		avaiw_swots -= paywoad->time_swots;
		if (avaiw_swots < 0) {
			dwm_dbg_atomic(mgw->dev,
				       "[MST POWT:%p] not enough time swots in mst state %p (avaiw=%d)\n",
				       paywoad->powt, mst_state, avaiw_swots + paywoad->time_swots);
			wetuwn -ENOSPC;
		}

		if (++paywoad_count > mgw->max_paywoads) {
			dwm_dbg_atomic(mgw->dev,
				       "[MST MGW:%p] state %p has too many paywoads (max=%d)\n",
				       mgw, mst_state, mgw->max_paywoads);
			wetuwn -EINVAW;
		}

		/* Assign a VCPI */
		if (!paywoad->vcpi) {
			paywoad->vcpi = ffz(mst_state->paywoad_mask) + 1;
			dwm_dbg_atomic(mgw->dev, "[MST POWT:%p] assigned VCPI #%d\n",
				       paywoad->powt, paywoad->vcpi);
			mst_state->paywoad_mask |= BIT(paywoad->vcpi - 1);
		}
	}

	if (!paywoad_count)
		mst_state->pbn_div.fuww = dfixed_const(0);

	dwm_dbg_atomic(mgw->dev, "[MST MGW:%p] mst state %p TU pbn_div=%d avaiw=%d used=%d\n",
		       mgw, mst_state, dfixed_twunc(mst_state->pbn_div), avaiw_swots,
		       mst_state->totaw_avaiw_swots - avaiw_swots);

	wetuwn 0;
}

/**
 * dwm_dp_mst_add_affected_dsc_cwtcs
 * @state: Pointew to the new stwuct dwm_dp_mst_topowogy_state
 * @mgw: MST topowogy managew
 *
 * Whenevew thewe is a change in mst topowogy
 * DSC configuwation wouwd have to be wecawcuwated
 * thewefowe we need to twiggew modeset on aww affected
 * CWTCs in that topowogy
 *
 * See awso:
 * dwm_dp_mst_atomic_enabwe_dsc()
 */
int dwm_dp_mst_add_affected_dsc_cwtcs(stwuct dwm_atomic_state *state, stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	stwuct dwm_dp_mst_topowogy_state *mst_state;
	stwuct dwm_dp_mst_atomic_paywoad *pos;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_state *conn_state;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *cwtc_state;

	mst_state = dwm_atomic_get_mst_topowogy_state(state, mgw);

	if (IS_EWW(mst_state))
		wetuwn PTW_EWW(mst_state);

	wist_fow_each_entwy(pos, &mst_state->paywoads, next) {

		connectow = pos->powt->connectow;

		if (!connectow)
			wetuwn -EINVAW;

		conn_state = dwm_atomic_get_connectow_state(state, connectow);

		if (IS_EWW(conn_state))
			wetuwn PTW_EWW(conn_state);

		cwtc = conn_state->cwtc;

		if (!cwtc)
			continue;

		if (!dwm_dp_mst_dsc_aux_fow_powt(pos->powt))
			continue;

		cwtc_state = dwm_atomic_get_cwtc_state(mst_state->base.state, cwtc);

		if (IS_EWW(cwtc_state))
			wetuwn PTW_EWW(cwtc_state);

		dwm_dbg_atomic(mgw->dev, "[MST MGW:%p] Setting mode_changed fwag on CWTC %p\n",
			       mgw, cwtc);

		cwtc_state->mode_changed = twue;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_dp_mst_add_affected_dsc_cwtcs);

/**
 * dwm_dp_mst_atomic_enabwe_dsc - Set DSC Enabwe Fwag to On/Off
 * @state: Pointew to the new dwm_atomic_state
 * @powt: Pointew to the affected MST Powt
 * @pbn: Newwy wecawcuwated bw wequiwed fow wink with DSC enabwed
 * @enabwe: Boowean fwag to enabwe ow disabwe DSC on the powt
 *
 * This function enabwes DSC on the given Powt
 * by wecawcuwating its vcpi fwom pbn pwovided
 * and sets dsc_enabwe fwag to keep twack of which
 * powts have DSC enabwed
 *
 */
int dwm_dp_mst_atomic_enabwe_dsc(stwuct dwm_atomic_state *state,
				 stwuct dwm_dp_mst_powt *powt,
				 int pbn, boow enabwe)
{
	stwuct dwm_dp_mst_topowogy_state *mst_state;
	stwuct dwm_dp_mst_atomic_paywoad *paywoad;
	int time_swots = 0;

	mst_state = dwm_atomic_get_mst_topowogy_state(state, powt->mgw);
	if (IS_EWW(mst_state))
		wetuwn PTW_EWW(mst_state);

	paywoad = dwm_atomic_get_mst_paywoad_state(mst_state, powt);
	if (!paywoad) {
		dwm_dbg_atomic(state->dev,
			       "[MST POWT:%p] Couwdn't find paywoad in mst state %p\n",
			       powt, mst_state);
		wetuwn -EINVAW;
	}

	if (paywoad->dsc_enabwed == enabwe) {
		dwm_dbg_atomic(state->dev,
			       "[MST POWT:%p] DSC fwag is awweady set to %d, wetuwning %d time swots\n",
			       powt, enabwe, paywoad->time_swots);
		time_swots = paywoad->time_swots;
	}

	if (enabwe) {
		time_swots = dwm_dp_atomic_find_time_swots(state, powt->mgw, powt, pbn);
		dwm_dbg_atomic(state->dev,
			       "[MST POWT:%p] Enabwing DSC fwag, weawwocating %d time swots on the powt\n",
			       powt, time_swots);
		if (time_swots < 0)
			wetuwn -EINVAW;
	}

	paywoad->dsc_enabwed = enabwe;

	wetuwn time_swots;
}
EXPOWT_SYMBOW(dwm_dp_mst_atomic_enabwe_dsc);

/**
 * dwm_dp_mst_atomic_check_mgw - Check the atomic state of an MST topowogy managew
 * @state: The gwobaw atomic state
 * @mgw: Managew to check
 * @mst_state: The MST atomic state fow @mgw
 * @faiwing_powt: Wetuwns the powt with a BW wimitation
 *
 * Checks the given MST managew's topowogy state fow an atomic update to ensuwe
 * that it's vawid. This incwudes checking whethew thewe's enough bandwidth to
 * suppowt the new timeswot awwocations in the atomic update.
 *
 * Any atomic dwivews suppowting DP MST must make suwe to caww this ow
 * the dwm_dp_mst_atomic_check() function aftew checking the west of theiw state
 * in theiw &dwm_mode_config_funcs.atomic_check() cawwback.
 *
 * See awso:
 * dwm_dp_mst_atomic_check()
 * dwm_dp_atomic_find_time_swots()
 * dwm_dp_atomic_wewease_time_swots()
 *
 * Wetuwns:
 *   - 0 if the new state is vawid
 *   - %-ENOSPC, if the new state is invawid, because of BW wimitation
 *         @faiwing_powt is set to:
 *
 *         - The non-woot powt whewe a BW wimit check faiwed
 *           with aww the powts downstweam of @faiwing_powt passing
 *           the BW wimit check.
 *           The wetuwned powt pointew is vawid untiw at weast
 *           one paywoad downstweam of it exists.
 *         - %NUWW if the BW wimit check faiwed at the woot powt
 *           with aww the powts downstweam of the woot powt passing
 *           the BW wimit check.
 *
 *   - %-EINVAW, if the new state is invawid, because the woot powt has
 *     too many paywoads.
 */
int dwm_dp_mst_atomic_check_mgw(stwuct dwm_atomic_state *state,
				stwuct dwm_dp_mst_topowogy_mgw *mgw,
				stwuct dwm_dp_mst_topowogy_state *mst_state,
				stwuct dwm_dp_mst_powt **faiwing_powt)
{
	int wet;

	*faiwing_powt = NUWW;

	if (!mgw->mst_state)
		wetuwn 0;

	mutex_wock(&mgw->wock);
	wet = dwm_dp_mst_atomic_check_mstb_bw_wimit(mgw->mst_pwimawy,
						    mst_state,
						    faiwing_powt);
	mutex_unwock(&mgw->wock);

	if (wet < 0)
		wetuwn wet;

	wetuwn dwm_dp_mst_atomic_check_paywoad_awwoc_wimits(mgw, mst_state);
}
EXPOWT_SYMBOW(dwm_dp_mst_atomic_check_mgw);

/**
 * dwm_dp_mst_atomic_check - Check that the new state of an MST topowogy in an
 * atomic update is vawid
 * @state: Pointew to the new &stwuct dwm_dp_mst_topowogy_state
 *
 * Checks the given topowogy state fow an atomic update to ensuwe that it's
 * vawid, cawwing dwm_dp_mst_atomic_check_mgw() fow aww MST managew in the
 * atomic state. This incwudes checking whethew thewe's enough bandwidth to
 * suppowt the new timeswot awwocations in the atomic update.
 *
 * Any atomic dwivews suppowting DP MST must make suwe to caww this aftew
 * checking the west of theiw state in theiw
 * &dwm_mode_config_funcs.atomic_check() cawwback.
 *
 * See awso:
 * dwm_dp_mst_atomic_check_mgw()
 * dwm_dp_atomic_find_time_swots()
 * dwm_dp_atomic_wewease_time_swots()
 *
 * Wetuwns:
 *
 * 0 if the new state is vawid, negative ewwow code othewwise.
 */
int dwm_dp_mst_atomic_check(stwuct dwm_atomic_state *state)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw;
	stwuct dwm_dp_mst_topowogy_state *mst_state;
	int i, wet = 0;

	fow_each_new_mst_mgw_in_state(state, mgw, mst_state, i) {
		stwuct dwm_dp_mst_powt *tmp_powt;

		wet = dwm_dp_mst_atomic_check_mgw(state, mgw, mst_state, &tmp_powt);
		if (wet)
			bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_dp_mst_atomic_check);

const stwuct dwm_pwivate_state_funcs dwm_dp_mst_topowogy_state_funcs = {
	.atomic_dupwicate_state = dwm_dp_mst_dupwicate_state,
	.atomic_destwoy_state = dwm_dp_mst_destwoy_state,
};
EXPOWT_SYMBOW(dwm_dp_mst_topowogy_state_funcs);

/**
 * dwm_atomic_get_mst_topowogy_state: get MST topowogy state
 * @state: gwobaw atomic state
 * @mgw: MST topowogy managew, awso the pwivate object in this case
 *
 * This function wwaps dwm_atomic_get_pwiv_obj_state() passing in the MST atomic
 * state vtabwe so that the pwivate object state wetuwned is that of a MST
 * topowogy object.
 *
 * WETUWNS:
 *
 * The MST topowogy state ow ewwow pointew.
 */
stwuct dwm_dp_mst_topowogy_state *dwm_atomic_get_mst_topowogy_state(stwuct dwm_atomic_state *state,
								    stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	wetuwn to_dp_mst_topowogy_state(dwm_atomic_get_pwivate_obj_state(state, &mgw->base));
}
EXPOWT_SYMBOW(dwm_atomic_get_mst_topowogy_state);

/**
 * dwm_atomic_get_owd_mst_topowogy_state: get owd MST topowogy state in atomic state, if any
 * @state: gwobaw atomic state
 * @mgw: MST topowogy managew, awso the pwivate object in this case
 *
 * This function wwaps dwm_atomic_get_owd_pwivate_obj_state() passing in the MST atomic
 * state vtabwe so that the pwivate object state wetuwned is that of a MST
 * topowogy object.
 *
 * Wetuwns:
 *
 * The owd MST topowogy state, ow NUWW if thewe's no topowogy state fow this MST mgw
 * in the gwobaw atomic state
 */
stwuct dwm_dp_mst_topowogy_state *
dwm_atomic_get_owd_mst_topowogy_state(stwuct dwm_atomic_state *state,
				      stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	stwuct dwm_pwivate_state *owd_pwiv_state =
		dwm_atomic_get_owd_pwivate_obj_state(state, &mgw->base);

	wetuwn owd_pwiv_state ? to_dp_mst_topowogy_state(owd_pwiv_state) : NUWW;
}
EXPOWT_SYMBOW(dwm_atomic_get_owd_mst_topowogy_state);

/**
 * dwm_atomic_get_new_mst_topowogy_state: get new MST topowogy state in atomic state, if any
 * @state: gwobaw atomic state
 * @mgw: MST topowogy managew, awso the pwivate object in this case
 *
 * This function wwaps dwm_atomic_get_new_pwivate_obj_state() passing in the MST atomic
 * state vtabwe so that the pwivate object state wetuwned is that of a MST
 * topowogy object.
 *
 * Wetuwns:
 *
 * The new MST topowogy state, ow NUWW if thewe's no topowogy state fow this MST mgw
 * in the gwobaw atomic state
 */
stwuct dwm_dp_mst_topowogy_state *
dwm_atomic_get_new_mst_topowogy_state(stwuct dwm_atomic_state *state,
				      stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	stwuct dwm_pwivate_state *new_pwiv_state =
		dwm_atomic_get_new_pwivate_obj_state(state, &mgw->base);

	wetuwn new_pwiv_state ? to_dp_mst_topowogy_state(new_pwiv_state) : NUWW;
}
EXPOWT_SYMBOW(dwm_atomic_get_new_mst_topowogy_state);

/**
 * dwm_dp_mst_topowogy_mgw_init - initiawise a topowogy managew
 * @mgw: managew stwuct to initiawise
 * @dev: device pwoviding this stwuctuwe - fow i2c addition.
 * @aux: DP hewpew aux channew to tawk to this device
 * @max_dpcd_twansaction_bytes: hw specific DPCD twansaction wimit
 * @max_paywoads: maximum numbew of paywoads this GPU can souwce
 * @conn_base_id: the connectow object ID the MST device is connected to.
 *
 * Wetuwn 0 fow success, ow negative ewwow code on faiwuwe
 */
int dwm_dp_mst_topowogy_mgw_init(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 stwuct dwm_device *dev, stwuct dwm_dp_aux *aux,
				 int max_dpcd_twansaction_bytes, int max_paywoads,
				 int conn_base_id)
{
	stwuct dwm_dp_mst_topowogy_state *mst_state;

	mutex_init(&mgw->wock);
	mutex_init(&mgw->qwock);
	mutex_init(&mgw->dewayed_destwoy_wock);
	mutex_init(&mgw->up_weq_wock);
	mutex_init(&mgw->pwobe_wock);
#if IS_ENABWED(CONFIG_DWM_DEBUG_DP_MST_TOPOWOGY_WEFS)
	mutex_init(&mgw->topowogy_wef_histowy_wock);
	stack_depot_init();
#endif
	INIT_WIST_HEAD(&mgw->tx_msg_downq);
	INIT_WIST_HEAD(&mgw->destwoy_powt_wist);
	INIT_WIST_HEAD(&mgw->destwoy_bwanch_device_wist);
	INIT_WIST_HEAD(&mgw->up_weq_wist);

	/*
	 * dewayed_destwoy_wowk wiww be queued on a dedicated WQ, so that any
	 * wequeuing wiww be awso fwushed when deiniting the topowogy managew.
	 */
	mgw->dewayed_destwoy_wq = awwoc_owdewed_wowkqueue("dwm_dp_mst_wq", 0);
	if (mgw->dewayed_destwoy_wq == NUWW)
		wetuwn -ENOMEM;

	INIT_WOWK(&mgw->wowk, dwm_dp_mst_wink_pwobe_wowk);
	INIT_WOWK(&mgw->tx_wowk, dwm_dp_tx_wowk);
	INIT_WOWK(&mgw->dewayed_destwoy_wowk, dwm_dp_dewayed_destwoy_wowk);
	INIT_WOWK(&mgw->up_weq_wowk, dwm_dp_mst_up_weq_wowk);
	init_waitqueue_head(&mgw->tx_waitq);
	mgw->dev = dev;
	mgw->aux = aux;
	mgw->max_dpcd_twansaction_bytes = max_dpcd_twansaction_bytes;
	mgw->max_paywoads = max_paywoads;
	mgw->conn_base_id = conn_base_id;

	mst_state = kzawwoc(sizeof(*mst_state), GFP_KEWNEW);
	if (mst_state == NUWW)
		wetuwn -ENOMEM;

	mst_state->totaw_avaiw_swots = 63;
	mst_state->stawt_swot = 1;

	mst_state->mgw = mgw;
	INIT_WIST_HEAD(&mst_state->paywoads);

	dwm_atomic_pwivate_obj_init(dev, &mgw->base,
				    &mst_state->base,
				    &dwm_dp_mst_topowogy_state_funcs);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_dp_mst_topowogy_mgw_init);

/**
 * dwm_dp_mst_topowogy_mgw_destwoy() - destwoy topowogy managew.
 * @mgw: managew to destwoy
 */
void dwm_dp_mst_topowogy_mgw_destwoy(stwuct dwm_dp_mst_topowogy_mgw *mgw)
{
	dwm_dp_mst_topowogy_mgw_set_mst(mgw, fawse);
	fwush_wowk(&mgw->wowk);
	/* The fowwowing wiww awso dwain any wequeued wowk on the WQ. */
	if (mgw->dewayed_destwoy_wq) {
		destwoy_wowkqueue(mgw->dewayed_destwoy_wq);
		mgw->dewayed_destwoy_wq = NUWW;
	}
	mgw->dev = NUWW;
	mgw->aux = NUWW;
	dwm_atomic_pwivate_obj_fini(&mgw->base);
	mgw->funcs = NUWW;

	mutex_destwoy(&mgw->dewayed_destwoy_wock);
	mutex_destwoy(&mgw->qwock);
	mutex_destwoy(&mgw->wock);
	mutex_destwoy(&mgw->up_weq_wock);
	mutex_destwoy(&mgw->pwobe_wock);
#if IS_ENABWED(CONFIG_DWM_DEBUG_DP_MST_TOPOWOGY_WEFS)
	mutex_destwoy(&mgw->topowogy_wef_histowy_wock);
#endif
}
EXPOWT_SYMBOW(dwm_dp_mst_topowogy_mgw_destwoy);

static boow wemote_i2c_wead_ok(const stwuct i2c_msg msgs[], int num)
{
	int i;

	if (num - 1 > DP_WEMOTE_I2C_WEAD_MAX_TWANSACTIONS)
		wetuwn fawse;

	fow (i = 0; i < num - 1; i++) {
		if (msgs[i].fwags & I2C_M_WD ||
		    msgs[i].wen > 0xff)
			wetuwn fawse;
	}

	wetuwn msgs[num - 1].fwags & I2C_M_WD &&
		msgs[num - 1].wen <= 0xff;
}

static boow wemote_i2c_wwite_ok(const stwuct i2c_msg msgs[], int num)
{
	int i;

	fow (i = 0; i < num - 1; i++) {
		if (msgs[i].fwags & I2C_M_WD || !(msgs[i].fwags & I2C_M_STOP) ||
		    msgs[i].wen > 0xff)
			wetuwn fawse;
	}

	wetuwn !(msgs[num - 1].fwags & I2C_M_WD) && msgs[num - 1].wen <= 0xff;
}

static int dwm_dp_mst_i2c_wead(stwuct dwm_dp_mst_bwanch *mstb,
			       stwuct dwm_dp_mst_powt *powt,
			       stwuct i2c_msg *msgs, int num)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw = powt->mgw;
	unsigned int i;
	stwuct dwm_dp_sideband_msg_weq_body msg;
	stwuct dwm_dp_sideband_msg_tx *txmsg = NUWW;
	int wet;

	memset(&msg, 0, sizeof(msg));
	msg.weq_type = DP_WEMOTE_I2C_WEAD;
	msg.u.i2c_wead.num_twansactions = num - 1;
	msg.u.i2c_wead.powt_numbew = powt->powt_num;
	fow (i = 0; i < num - 1; i++) {
		msg.u.i2c_wead.twansactions[i].i2c_dev_id = msgs[i].addw;
		msg.u.i2c_wead.twansactions[i].num_bytes = msgs[i].wen;
		msg.u.i2c_wead.twansactions[i].bytes = msgs[i].buf;
		msg.u.i2c_wead.twansactions[i].no_stop_bit = !(msgs[i].fwags & I2C_M_STOP);
	}
	msg.u.i2c_wead.wead_i2c_device_id = msgs[num - 1].addw;
	msg.u.i2c_wead.num_bytes_wead = msgs[num - 1].wen;

	txmsg = kzawwoc(sizeof(*txmsg), GFP_KEWNEW);
	if (!txmsg) {
		wet = -ENOMEM;
		goto out;
	}

	txmsg->dst = mstb;
	dwm_dp_encode_sideband_weq(&msg, txmsg);

	dwm_dp_queue_down_tx(mgw, txmsg);

	wet = dwm_dp_mst_wait_tx_wepwy(mstb, txmsg);
	if (wet > 0) {

		if (txmsg->wepwy.wepwy_type == DP_SIDEBAND_WEPWY_NAK) {
			wet = -EWEMOTEIO;
			goto out;
		}
		if (txmsg->wepwy.u.wemote_i2c_wead_ack.num_bytes != msgs[num - 1].wen) {
			wet = -EIO;
			goto out;
		}
		memcpy(msgs[num - 1].buf, txmsg->wepwy.u.wemote_i2c_wead_ack.bytes, msgs[num - 1].wen);
		wet = num;
	}
out:
	kfwee(txmsg);
	wetuwn wet;
}

static int dwm_dp_mst_i2c_wwite(stwuct dwm_dp_mst_bwanch *mstb,
				stwuct dwm_dp_mst_powt *powt,
				stwuct i2c_msg *msgs, int num)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw = powt->mgw;
	unsigned int i;
	stwuct dwm_dp_sideband_msg_weq_body msg;
	stwuct dwm_dp_sideband_msg_tx *txmsg = NUWW;
	int wet;

	txmsg = kzawwoc(sizeof(*txmsg), GFP_KEWNEW);
	if (!txmsg) {
		wet = -ENOMEM;
		goto out;
	}
	fow (i = 0; i < num; i++) {
		memset(&msg, 0, sizeof(msg));
		msg.weq_type = DP_WEMOTE_I2C_WWITE;
		msg.u.i2c_wwite.powt_numbew = powt->powt_num;
		msg.u.i2c_wwite.wwite_i2c_device_id = msgs[i].addw;
		msg.u.i2c_wwite.num_bytes = msgs[i].wen;
		msg.u.i2c_wwite.bytes = msgs[i].buf;

		memset(txmsg, 0, sizeof(*txmsg));
		txmsg->dst = mstb;

		dwm_dp_encode_sideband_weq(&msg, txmsg);
		dwm_dp_queue_down_tx(mgw, txmsg);

		wet = dwm_dp_mst_wait_tx_wepwy(mstb, txmsg);
		if (wet > 0) {
			if (txmsg->wepwy.wepwy_type == DP_SIDEBAND_WEPWY_NAK) {
				wet = -EWEMOTEIO;
				goto out;
			}
		} ewse {
			goto out;
		}
	}
	wet = num;
out:
	kfwee(txmsg);
	wetuwn wet;
}

/* I2C device */
static int dwm_dp_mst_i2c_xfew(stwuct i2c_adaptew *adaptew,
			       stwuct i2c_msg *msgs, int num)
{
	stwuct dwm_dp_aux *aux = adaptew->awgo_data;
	stwuct dwm_dp_mst_powt *powt =
		containew_of(aux, stwuct dwm_dp_mst_powt, aux);
	stwuct dwm_dp_mst_bwanch *mstb;
	stwuct dwm_dp_mst_topowogy_mgw *mgw = powt->mgw;
	int wet;

	mstb = dwm_dp_mst_topowogy_get_mstb_vawidated(mgw, powt->pawent);
	if (!mstb)
		wetuwn -EWEMOTEIO;

	if (wemote_i2c_wead_ok(msgs, num)) {
		wet = dwm_dp_mst_i2c_wead(mstb, powt, msgs, num);
	} ewse if (wemote_i2c_wwite_ok(msgs, num)) {
		wet = dwm_dp_mst_i2c_wwite(mstb, powt, msgs, num);
	} ewse {
		dwm_dbg_kms(mgw->dev, "Unsuppowted I2C twansaction fow MST device\n");
		wet = -EIO;
	}

	dwm_dp_mst_topowogy_put_mstb(mstb);
	wetuwn wet;
}

static u32 dwm_dp_mst_i2c_functionawity(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW |
	       I2C_FUNC_SMBUS_WEAD_BWOCK_DATA |
	       I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW |
	       I2C_FUNC_10BIT_ADDW;
}

static const stwuct i2c_awgowithm dwm_dp_mst_i2c_awgo = {
	.functionawity = dwm_dp_mst_i2c_functionawity,
	.mastew_xfew = dwm_dp_mst_i2c_xfew,
};

/**
 * dwm_dp_mst_wegistew_i2c_bus() - wegistew an I2C adaptew fow I2C-ovew-AUX
 * @powt: The powt to add the I2C bus on
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
static int dwm_dp_mst_wegistew_i2c_bus(stwuct dwm_dp_mst_powt *powt)
{
	stwuct dwm_dp_aux *aux = &powt->aux;
	stwuct device *pawent_dev = powt->mgw->dev->dev;

	aux->ddc.awgo = &dwm_dp_mst_i2c_awgo;
	aux->ddc.awgo_data = aux;
	aux->ddc.wetwies = 3;

	aux->ddc.ownew = THIS_MODUWE;
	/* FIXME: set the kdev of the powt's connectow as pawent */
	aux->ddc.dev.pawent = pawent_dev;
	aux->ddc.dev.of_node = pawent_dev->of_node;

	stwscpy(aux->ddc.name, aux->name ? aux->name : dev_name(pawent_dev),
		sizeof(aux->ddc.name));

	wetuwn i2c_add_adaptew(&aux->ddc);
}

/**
 * dwm_dp_mst_unwegistew_i2c_bus() - unwegistew an I2C-ovew-AUX adaptew
 * @powt: The powt to wemove the I2C bus fwom
 */
static void dwm_dp_mst_unwegistew_i2c_bus(stwuct dwm_dp_mst_powt *powt)
{
	i2c_dew_adaptew(&powt->aux.ddc);
}

/**
 * dwm_dp_mst_is_viwtuaw_dpcd() - Is the given powt a viwtuaw DP Peew Device
 * @powt: The powt to check
 *
 * A singwe physicaw MST hub object can be wepwesented in the topowogy
 * by muwtipwe bwanches, with viwtuaw powts between those bwanches.
 *
 * As of DP1.4, An MST hub with intewnaw (viwtuaw) powts must expose
 * cewtain DPCD wegistews ovew those powts. See sections 2.6.1.1.1
 * and 2.6.1.1.2 of Dispway Powt specification v1.4 fow detaiws.
 *
 * May acquiwe mgw->wock
 *
 * Wetuwns:
 * twue if the powt is a viwtuaw DP peew device, fawse othewwise
 */
static boow dwm_dp_mst_is_viwtuaw_dpcd(stwuct dwm_dp_mst_powt *powt)
{
	stwuct dwm_dp_mst_powt *downstweam_powt;

	if (!powt || powt->dpcd_wev < DP_DPCD_WEV_14)
		wetuwn fawse;

	/* Viwtuaw DP Sink (Intewnaw Dispway Panew) */
	if (powt->powt_num >= 8)
		wetuwn twue;

	/* DP-to-HDMI Pwotocow Convewtew */
	if (powt->pdt == DP_PEEW_DEVICE_DP_WEGACY_CONV &&
	    !powt->mcs &&
	    powt->wdps)
		wetuwn twue;

	/* DP-to-DP */
	mutex_wock(&powt->mgw->wock);
	if (powt->pdt == DP_PEEW_DEVICE_MST_BWANCHING &&
	    powt->mstb &&
	    powt->mstb->num_powts == 2) {
		wist_fow_each_entwy(downstweam_powt, &powt->mstb->powts, next) {
			if (downstweam_powt->pdt == DP_PEEW_DEVICE_SST_SINK &&
			    !downstweam_powt->input) {
				mutex_unwock(&powt->mgw->wock);
				wetuwn twue;
			}
		}
	}
	mutex_unwock(&powt->mgw->wock);

	wetuwn fawse;
}

/**
 * dwm_dp_mst_dsc_aux_fow_powt() - Find the cowwect aux fow DSC
 * @powt: The powt to check. A weaf of the MST twee with an attached dispway.
 *
 * Depending on the situation, DSC may be enabwed via the endpoint aux,
 * the immediatewy upstweam aux, ow the connectow's physicaw aux.
 *
 * This is both the cowwect aux to wead DSC_CAPABIWITY and the
 * cowwect aux to wwite DSC_ENABWED.
 *
 * This opewation can be expensive (up to fouw aux weads), so
 * the cawwew shouwd cache the wetuwn.
 *
 * Wetuwns:
 * NUWW if DSC cannot be enabwed on this powt, othewwise the aux device
 */
stwuct dwm_dp_aux *dwm_dp_mst_dsc_aux_fow_powt(stwuct dwm_dp_mst_powt *powt)
{
	stwuct dwm_dp_mst_powt *immediate_upstweam_powt;
	stwuct dwm_dp_aux *immediate_upstweam_aux;
	stwuct dwm_dp_mst_powt *fec_powt;
	stwuct dwm_dp_desc desc = {};
	u8 endpoint_fec;
	u8 endpoint_dsc;

	if (!powt)
		wetuwn NUWW;

	if (powt->pawent->powt_pawent)
		immediate_upstweam_powt = powt->pawent->powt_pawent;
	ewse
		immediate_upstweam_powt = NUWW;

	fec_powt = immediate_upstweam_powt;
	whiwe (fec_powt) {
		/*
		 * Each physicaw wink (i.e. not a viwtuaw powt) between the
		 * output and the pwimawy device must suppowt FEC
		 */
		if (!dwm_dp_mst_is_viwtuaw_dpcd(fec_powt) &&
		    !fec_powt->fec_capabwe)
			wetuwn NUWW;

		fec_powt = fec_powt->pawent->powt_pawent;
	}

	/* DP-to-DP peew device */
	if (dwm_dp_mst_is_viwtuaw_dpcd(immediate_upstweam_powt)) {
		u8 upstweam_dsc;

		if (dwm_dp_dpcd_wead(&powt->aux,
				     DP_DSC_SUPPOWT, &endpoint_dsc, 1) != 1)
			wetuwn NUWW;
		if (dwm_dp_dpcd_wead(&powt->aux,
				     DP_FEC_CAPABIWITY, &endpoint_fec, 1) != 1)
			wetuwn NUWW;
		if (dwm_dp_dpcd_wead(&immediate_upstweam_powt->aux,
				     DP_DSC_SUPPOWT, &upstweam_dsc, 1) != 1)
			wetuwn NUWW;

		/* Enpoint decompwession with DP-to-DP peew device */
		if ((endpoint_dsc & DP_DSC_DECOMPWESSION_IS_SUPPOWTED) &&
		    (endpoint_fec & DP_FEC_CAPABWE) &&
		    (upstweam_dsc & DP_DSC_PASSTHWOUGH_IS_SUPPOWTED)) {
			powt->passthwough_aux = &immediate_upstweam_powt->aux;
			wetuwn &powt->aux;
		}

		/* Viwtuaw DPCD decompwession with DP-to-DP peew device */
		wetuwn &immediate_upstweam_powt->aux;
	}

	/* Viwtuaw DPCD decompwession with DP-to-HDMI ow Viwtuaw DP Sink */
	if (dwm_dp_mst_is_viwtuaw_dpcd(powt))
		wetuwn &powt->aux;

	/*
	 * Synaptics quiwk
	 * Appwies to powts fow which:
	 * - Physicaw aux has Synaptics OUI
	 * - DPv1.4 ow highew
	 * - Powt is on pwimawy bwanch device
	 * - Not a VGA adaptew (DP_DWN_STWM_POWT_TYPE_ANAWOG)
	 */
	if (immediate_upstweam_powt)
		immediate_upstweam_aux = &immediate_upstweam_powt->aux;
	ewse
		immediate_upstweam_aux = powt->mgw->aux;

	if (dwm_dp_wead_desc(immediate_upstweam_aux, &desc, twue))
		wetuwn NUWW;

	if (dwm_dp_has_quiwk(&desc, DP_DPCD_QUIWK_DSC_WITHOUT_VIWTUAW_DPCD)) {
		u8 dpcd_ext[DP_WECEIVEW_CAP_SIZE];

		if (dwm_dp_wead_dpcd_caps(immediate_upstweam_aux, dpcd_ext) < 0)
			wetuwn NUWW;

		if (dpcd_ext[DP_DPCD_WEV] >= DP_DPCD_WEV_14 &&
		    ((dpcd_ext[DP_DOWNSTWEAMPOWT_PWESENT] & DP_DWN_STWM_POWT_PWESENT) &&
		    ((dpcd_ext[DP_DOWNSTWEAMPOWT_PWESENT] & DP_DWN_STWM_POWT_TYPE_MASK)
		     != DP_DWN_STWM_POWT_TYPE_ANAWOG)))
			wetuwn immediate_upstweam_aux;
	}

	/*
	 * The check bewow vewifies if the MST sink
	 * connected to the GPU is capabwe of DSC -
	 * thewefowe the endpoint needs to be
	 * both DSC and FEC capabwe.
	 */
	if (dwm_dp_dpcd_wead(&powt->aux,
	   DP_DSC_SUPPOWT, &endpoint_dsc, 1) != 1)
		wetuwn NUWW;
	if (dwm_dp_dpcd_wead(&powt->aux,
	   DP_FEC_CAPABIWITY, &endpoint_fec, 1) != 1)
		wetuwn NUWW;
	if ((endpoint_dsc & DP_DSC_DECOMPWESSION_IS_SUPPOWTED) &&
	   (endpoint_fec & DP_FEC_CAPABWE))
		wetuwn &powt->aux;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(dwm_dp_mst_dsc_aux_fow_powt);
