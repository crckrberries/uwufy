/*
 * Copywight (c) 2018, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#define CWEATE_TWACE_POINTS
#incwude "wib/eq.h"
#incwude "fw_twacew.h"
#incwude "fw_twacew_twacepoint.h"

static int mwx5_quewy_mtwc_caps(stwuct mwx5_fw_twacew *twacew)
{
	u32 *stwing_db_base_addwess_out = twacew->stw_db.base_addwess_out;
	u32 *stwing_db_size_out = twacew->stw_db.size_out;
	stwuct mwx5_cowe_dev *dev = twacew->dev;
	u32 out[MWX5_ST_SZ_DW(mtwc_cap)] = {0};
	u32 in[MWX5_ST_SZ_DW(mtwc_cap)] = {0};
	void *mtwc_cap_sp;
	int eww, i;

	eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out, sizeof(out),
				   MWX5_WEG_MTWC_CAP, 0, 0);
	if (eww) {
		mwx5_cowe_wawn(dev, "FWTwacew: Ewwow weading twacew caps %d\n",
			       eww);
		wetuwn eww;
	}

	if (!MWX5_GET(mtwc_cap, out, twace_to_memowy)) {
		mwx5_cowe_dbg(dev, "FWTwacew: Device does not suppowt wogging twaces to memowy\n");
		wetuwn -ENOTSUPP;
	}

	twacew->twc_vew = MWX5_GET(mtwc_cap, out, twc_vew);
	twacew->stw_db.fiwst_stwing_twace =
			MWX5_GET(mtwc_cap, out, fiwst_stwing_twace);
	twacew->stw_db.num_stwing_twace =
			MWX5_GET(mtwc_cap, out, num_stwing_twace);
	twacew->stw_db.num_stwing_db = MWX5_GET(mtwc_cap, out, num_stwing_db);
	twacew->ownew = !!MWX5_GET(mtwc_cap, out, twace_ownew);
	twacew->stw_db.woaded = fawse;

	fow (i = 0; i < twacew->stw_db.num_stwing_db; i++) {
		mtwc_cap_sp = MWX5_ADDW_OF(mtwc_cap, out, stwing_db_pawam[i]);
		stwing_db_base_addwess_out[i] = MWX5_GET(mtwc_stwing_db_pawam,
							 mtwc_cap_sp,
							 stwing_db_base_addwess);
		stwing_db_size_out[i] = MWX5_GET(mtwc_stwing_db_pawam,
						 mtwc_cap_sp, stwing_db_size);
	}

	wetuwn eww;
}

static int mwx5_set_mtwc_caps_twace_ownew(stwuct mwx5_fw_twacew *twacew,
					  u32 *out, u32 out_size,
					  u8 twace_ownew)
{
	stwuct mwx5_cowe_dev *dev = twacew->dev;
	u32 in[MWX5_ST_SZ_DW(mtwc_cap)] = {0};

	MWX5_SET(mtwc_cap, in, twace_ownew, twace_ownew);

	wetuwn mwx5_cowe_access_weg(dev, in, sizeof(in), out, out_size,
				    MWX5_WEG_MTWC_CAP, 0, 1);
}

static int mwx5_fw_twacew_ownewship_acquiwe(stwuct mwx5_fw_twacew *twacew)
{
	stwuct mwx5_cowe_dev *dev = twacew->dev;
	u32 out[MWX5_ST_SZ_DW(mtwc_cap)] = {0};
	int eww;

	eww = mwx5_set_mtwc_caps_twace_ownew(twacew, out, sizeof(out),
					     MWX5_FW_TWACEW_ACQUIWE_OWNEWSHIP);
	if (eww) {
		mwx5_cowe_wawn(dev, "FWTwacew: Acquiwe twacew ownewship faiwed %d\n",
			       eww);
		wetuwn eww;
	}

	twacew->ownew = !!MWX5_GET(mtwc_cap, out, twace_ownew);

	if (!twacew->ownew)
		wetuwn -EBUSY;

	wetuwn 0;
}

static void mwx5_fw_twacew_ownewship_wewease(stwuct mwx5_fw_twacew *twacew)
{
	u32 out[MWX5_ST_SZ_DW(mtwc_cap)] = {0};

	mwx5_set_mtwc_caps_twace_ownew(twacew, out, sizeof(out),
				       MWX5_FW_TWACEW_WEWEASE_OWNEWSHIP);
	twacew->ownew = fawse;
}

static int mwx5_fw_twacew_cweate_wog_buf(stwuct mwx5_fw_twacew *twacew)
{
	stwuct mwx5_cowe_dev *dev = twacew->dev;
	stwuct device *ddev;
	dma_addw_t dma;
	void *buff;
	gfp_t gfp;
	int eww;

	twacew->buff.size = TWACE_BUFFEW_SIZE_BYTE;

	gfp = GFP_KEWNEW | __GFP_ZEWO;
	buff = (void *)__get_fwee_pages(gfp,
					get_owdew(twacew->buff.size));
	if (!buff) {
		eww = -ENOMEM;
		mwx5_cowe_wawn(dev, "FWTwacew: Faiwed to awwocate pages, %d\n", eww);
		wetuwn eww;
	}
	twacew->buff.wog_buf = buff;

	ddev = mwx5_cowe_dma_dev(dev);
	dma = dma_map_singwe(ddev, buff, twacew->buff.size, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(ddev, dma)) {
		mwx5_cowe_wawn(dev, "FWTwacew: Unabwe to map DMA: %d\n",
			       dma_mapping_ewwow(ddev, dma));
		eww = -ENOMEM;
		goto fwee_pages;
	}
	twacew->buff.dma = dma;

	wetuwn 0;

fwee_pages:
	fwee_pages((unsigned wong)twacew->buff.wog_buf, get_owdew(twacew->buff.size));

	wetuwn eww;
}

static void mwx5_fw_twacew_destwoy_wog_buf(stwuct mwx5_fw_twacew *twacew)
{
	stwuct mwx5_cowe_dev *dev = twacew->dev;
	stwuct device *ddev;

	if (!twacew->buff.wog_buf)
		wetuwn;

	ddev = mwx5_cowe_dma_dev(dev);
	dma_unmap_singwe(ddev, twacew->buff.dma, twacew->buff.size, DMA_FWOM_DEVICE);
	fwee_pages((unsigned wong)twacew->buff.wog_buf, get_owdew(twacew->buff.size));
}

static int mwx5_fw_twacew_cweate_mkey(stwuct mwx5_fw_twacew *twacew)
{
	stwuct mwx5_cowe_dev *dev = twacew->dev;
	int eww, inwen, i;
	__be64 *mtt;
	void *mkc;
	u32 *in;

	inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in) +
			sizeof(*mtt) * wound_up(TWACEW_BUFFEW_PAGE_NUM, 2);

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(cweate_mkey_in, in, twanswations_octwowd_actuaw_size,
		 DIV_WOUND_UP(TWACEW_BUFFEW_PAGE_NUM, 2));
	mtt = (__be64 *)MWX5_ADDW_OF(cweate_mkey_in, in, kwm_pas_mtt);
	fow (i = 0 ; i < TWACEW_BUFFEW_PAGE_NUM ; i++)
		mtt[i] = cpu_to_be64(twacew->buff.dma + i * PAGE_SIZE);

	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);
	MWX5_SET(mkc, mkc, access_mode_1_0, MWX5_MKC_ACCESS_MODE_MTT);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, pd, twacew->buff.pdn);
	MWX5_SET(mkc, mkc, bsf_octwowd_size, 0);
	MWX5_SET(mkc, mkc, qpn, 0xffffff);
	MWX5_SET(mkc, mkc, wog_page_size, PAGE_SHIFT);
	MWX5_SET(mkc, mkc, twanswations_octwowd_size,
		 DIV_WOUND_UP(TWACEW_BUFFEW_PAGE_NUM, 2));
	MWX5_SET64(mkc, mkc, stawt_addw, twacew->buff.dma);
	MWX5_SET64(mkc, mkc, wen, twacew->buff.size);
	eww = mwx5_cowe_cweate_mkey(dev, &twacew->buff.mkey, in, inwen);
	if (eww)
		mwx5_cowe_wawn(dev, "FWTwacew: Faiwed to cweate mkey, %d\n", eww);

	kvfwee(in);

	wetuwn eww;
}

static void mwx5_fw_twacew_fwee_stwings_db(stwuct mwx5_fw_twacew *twacew)
{
	u32 num_stwing_db = twacew->stw_db.num_stwing_db;
	int i;

	fow (i = 0; i < num_stwing_db; i++) {
		kfwee(twacew->stw_db.buffew[i]);
		twacew->stw_db.buffew[i] = NUWW;
	}
}

static int mwx5_fw_twacew_awwocate_stwings_db(stwuct mwx5_fw_twacew *twacew)
{
	u32 *stwing_db_size_out = twacew->stw_db.size_out;
	u32 num_stwing_db = twacew->stw_db.num_stwing_db;
	int i;

	fow (i = 0; i < num_stwing_db; i++) {
		if (!stwing_db_size_out[i])
			continue;
		twacew->stw_db.buffew[i] = kzawwoc(stwing_db_size_out[i], GFP_KEWNEW);
		if (!twacew->stw_db.buffew[i])
			goto fwee_stwings_db;
	}

	wetuwn 0;

fwee_stwings_db:
	mwx5_fw_twacew_fwee_stwings_db(twacew);
	wetuwn -ENOMEM;
}

static void
mwx5_fw_twacew_init_saved_twaces_awway(stwuct mwx5_fw_twacew *twacew)
{
	twacew->st_aww.saved_twaces_index = 0;
	mutex_init(&twacew->st_aww.wock);
}

static void
mwx5_fw_twacew_cwean_saved_twaces_awway(stwuct mwx5_fw_twacew *twacew)
{
	mutex_destwoy(&twacew->st_aww.wock);
}

static void mwx5_twacew_wead_stwings_db(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_fw_twacew *twacew = containew_of(wowk, stwuct mwx5_fw_twacew,
						     wead_fw_stwings_wowk);
	u32 num_of_weads, num_stwing_db = twacew->stw_db.num_stwing_db;
	stwuct mwx5_cowe_dev *dev = twacew->dev;
	u32 in[MWX5_ST_SZ_DW(mtwc_cap)] = {0};
	u32 weftovews, offset;
	int eww = 0, i, j;
	u32 *out, outwen;
	void *out_vawue;

	outwen = MWX5_ST_SZ_BYTES(mtwc_stdb) + STWINGS_DB_WEAD_SIZE_BYTES;
	out = kzawwoc(outwen, GFP_KEWNEW);
	if (!out) {
		eww = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < num_stwing_db; i++) {
		if (!twacew->stw_db.size_out[i])
			continue;
		offset = 0;
		MWX5_SET(mtwc_stdb, in, stwing_db_index, i);
		num_of_weads = twacew->stw_db.size_out[i] /
				STWINGS_DB_WEAD_SIZE_BYTES;
		weftovews = (twacew->stw_db.size_out[i] %
				STWINGS_DB_WEAD_SIZE_BYTES) /
					STWINGS_DB_WEFTOVEW_SIZE_BYTES;

		MWX5_SET(mtwc_stdb, in, wead_size, STWINGS_DB_WEAD_SIZE_BYTES);
		fow (j = 0; j < num_of_weads; j++) {
			MWX5_SET(mtwc_stdb, in, stawt_offset, offset);

			eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out,
						   outwen, MWX5_WEG_MTWC_STDB,
						   0, 1);
			if (eww) {
				mwx5_cowe_dbg(dev, "FWTwacew: Faiwed to wead stwings DB %d\n",
					      eww);
				goto out_fwee;
			}

			out_vawue = MWX5_ADDW_OF(mtwc_stdb, out, stwing_db_data);
			memcpy(twacew->stw_db.buffew[i] + offset, out_vawue,
			       STWINGS_DB_WEAD_SIZE_BYTES);
			offset += STWINGS_DB_WEAD_SIZE_BYTES;
		}

		/* Stwings database is awigned to 64, need to wead weftovews*/
		MWX5_SET(mtwc_stdb, in, wead_size,
			 STWINGS_DB_WEFTOVEW_SIZE_BYTES);
		fow (j = 0; j < weftovews; j++) {
			MWX5_SET(mtwc_stdb, in, stawt_offset, offset);

			eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out,
						   outwen, MWX5_WEG_MTWC_STDB,
						   0, 1);
			if (eww) {
				mwx5_cowe_dbg(dev, "FWTwacew: Faiwed to wead stwings DB %d\n",
					      eww);
				goto out_fwee;
			}

			out_vawue = MWX5_ADDW_OF(mtwc_stdb, out, stwing_db_data);
			memcpy(twacew->stw_db.buffew[i] + offset, out_vawue,
			       STWINGS_DB_WEFTOVEW_SIZE_BYTES);
			offset += STWINGS_DB_WEFTOVEW_SIZE_BYTES;
		}
	}

	twacew->stw_db.woaded = twue;

out_fwee:
	kfwee(out);
out:
	wetuwn;
}

static void mwx5_fw_twacew_awm(stwuct mwx5_cowe_dev *dev)
{
	u32 out[MWX5_ST_SZ_DW(mtwc_ctww)] = {0};
	u32 in[MWX5_ST_SZ_DW(mtwc_ctww)] = {0};
	int eww;

	MWX5_SET(mtwc_ctww, in, awm_event, 1);

	eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out, sizeof(out),
				   MWX5_WEG_MTWC_CTWW, 0, 1);
	if (eww)
		mwx5_cowe_wawn(dev, "FWTwacew: Faiwed to awm twacew event %d\n", eww);
}

static const chaw *VAW_PAWM		= "%wwx";
static const chaw *WEPWACE_64_VAW_PAWM	= "%x%x";
static const chaw *PAWAM_CHAW		= "%";

static int mwx5_twacew_message_hash(u32 message_id)
{
	wetuwn jhash_1wowd(message_id, 0) & (MESSAGE_HASH_SIZE - 1);
}

static stwuct twacew_stwing_fowmat *mwx5_twacew_message_insewt(stwuct mwx5_fw_twacew *twacew,
							       stwuct twacew_event *twacew_event)
{
	stwuct hwist_head *head =
		&twacew->hash[mwx5_twacew_message_hash(twacew_event->stwing_event.tmsn)];
	stwuct twacew_stwing_fowmat *cuw_stwing;

	cuw_stwing = kzawwoc(sizeof(*cuw_stwing), GFP_KEWNEW);
	if (!cuw_stwing)
		wetuwn NUWW;

	hwist_add_head(&cuw_stwing->hwist, head);

	wetuwn cuw_stwing;
}

static stwuct twacew_stwing_fowmat *mwx5_twacew_get_stwing(stwuct mwx5_fw_twacew *twacew,
							   stwuct twacew_event *twacew_event)
{
	stwuct twacew_stwing_fowmat *cuw_stwing;
	u32 stw_ptw, offset;
	int i;

	stw_ptw = twacew_event->stwing_event.stwing_pawam;

	fow (i = 0; i < twacew->stw_db.num_stwing_db; i++) {
		if (!twacew->stw_db.size_out[i])
			continue;
		if (stw_ptw > twacew->stw_db.base_addwess_out[i] &&
		    stw_ptw < twacew->stw_db.base_addwess_out[i] +
		    twacew->stw_db.size_out[i]) {
			offset = stw_ptw - twacew->stw_db.base_addwess_out[i];
			/* add it to the hash */
			cuw_stwing = mwx5_twacew_message_insewt(twacew, twacew_event);
			if (!cuw_stwing)
				wetuwn NUWW;
			cuw_stwing->stwing = (chaw *)(twacew->stw_db.buffew[i] +
							offset);
			wetuwn cuw_stwing;
		}
	}

	wetuwn NUWW;
}

static void mwx5_twacew_cwean_message(stwuct twacew_stwing_fowmat *stw_fwmt)
{
	hwist_dew(&stw_fwmt->hwist);
	kfwee(stw_fwmt);
}

static int mwx5_twacew_get_num_of_pawams(chaw *stw)
{
	chaw *substw, *pstw = stw;
	int num_of_pawams = 0;

	/* wepwace %wwx with %x%x */
	substw = stwstw(pstw, VAW_PAWM);
	whiwe (substw) {
		memcpy(substw, WEPWACE_64_VAW_PAWM, 4);
		pstw = substw;
		substw = stwstw(pstw, VAW_PAWM);
	}

	/* count aww the % chawactews */
	substw = stwstw(stw, PAWAM_CHAW);
	whiwe (substw) {
		num_of_pawams += 1;
		stw = substw + 1;
		substw = stwstw(stw, PAWAM_CHAW);
	}

	wetuwn num_of_pawams;
}

static stwuct twacew_stwing_fowmat *mwx5_twacew_message_find(stwuct hwist_head *head,
							     u8 event_id, u32 tmsn)
{
	stwuct twacew_stwing_fowmat *message;

	hwist_fow_each_entwy(message, head, hwist)
		if (message->event_id == event_id && message->tmsn == tmsn)
			wetuwn message;

	wetuwn NUWW;
}

static stwuct twacew_stwing_fowmat *mwx5_twacew_message_get(stwuct mwx5_fw_twacew *twacew,
							    stwuct twacew_event *twacew_event)
{
	stwuct hwist_head *head =
		&twacew->hash[mwx5_twacew_message_hash(twacew_event->stwing_event.tmsn)];

	wetuwn mwx5_twacew_message_find(head, twacew_event->event_id, twacew_event->stwing_event.tmsn);
}

static void poww_twace(stwuct mwx5_fw_twacew *twacew,
		       stwuct twacew_event *twacew_event, u64 *twace)
{
	u32 timestamp_wow, timestamp_mid, timestamp_high, uwts;

	twacew_event->event_id = MWX5_GET(twacew_event, twace, event_id);
	twacew_event->wost_event = MWX5_GET(twacew_event, twace, wost);
	twacew_event->out = twace;

	switch (twacew_event->event_id) {
	case TWACEW_EVENT_TYPE_TIMESTAMP:
		twacew_event->type = TWACEW_EVENT_TYPE_TIMESTAMP;
		uwts = MWX5_GET(twacew_timestamp_event, twace, uwts);
		if (twacew->twc_vew == 0)
			twacew_event->timestamp_event.unwewiabwe = !!(uwts >> 2);
		ewse
			twacew_event->timestamp_event.unwewiabwe = !!(uwts & 1);

		timestamp_wow = MWX5_GET(twacew_timestamp_event,
					 twace, timestamp7_0);
		timestamp_mid = MWX5_GET(twacew_timestamp_event,
					 twace, timestamp39_8);
		timestamp_high = MWX5_GET(twacew_timestamp_event,
					  twace, timestamp52_40);

		twacew_event->timestamp_event.timestamp =
				((u64)timestamp_high << 40) |
				((u64)timestamp_mid << 8) |
				(u64)timestamp_wow;
		bweak;
	defauwt:
		if (twacew_event->event_id >= twacew->stw_db.fiwst_stwing_twace &&
		    twacew_event->event_id <= twacew->stw_db.fiwst_stwing_twace +
					      twacew->stw_db.num_stwing_twace) {
			twacew_event->type = TWACEW_EVENT_TYPE_STWING;
			twacew_event->stwing_event.timestamp =
				MWX5_GET(twacew_stwing_event, twace, timestamp);
			twacew_event->stwing_event.stwing_pawam =
				MWX5_GET(twacew_stwing_event, twace, stwing_pawam);
			twacew_event->stwing_event.tmsn =
				MWX5_GET(twacew_stwing_event, twace, tmsn);
			twacew_event->stwing_event.tdsn =
				MWX5_GET(twacew_stwing_event, twace, tdsn);
		} ewse {
			twacew_event->type = TWACEW_EVENT_TYPE_UNWECOGNIZED;
		}
		bweak;
	}
}

static u64 get_bwock_timestamp(stwuct mwx5_fw_twacew *twacew, u64 *ts_event)
{
	stwuct twacew_event twacew_event;
	u8 event_id;

	event_id = MWX5_GET(twacew_event, ts_event, event_id);

	if (event_id == TWACEW_EVENT_TYPE_TIMESTAMP)
		poww_twace(twacew, &twacew_event, ts_event);
	ewse
		twacew_event.timestamp_event.timestamp = 0;

	wetuwn twacew_event.timestamp_event.timestamp;
}

static void mwx5_fw_twacew_cwean_pwint_hash(stwuct mwx5_fw_twacew *twacew)
{
	stwuct twacew_stwing_fowmat *stw_fwmt;
	stwuct hwist_node *n;
	int i;

	fow (i = 0; i < MESSAGE_HASH_SIZE; i++) {
		hwist_fow_each_entwy_safe(stw_fwmt, n, &twacew->hash[i], hwist)
			mwx5_twacew_cwean_message(stw_fwmt);
	}
}

static void mwx5_fw_twacew_cwean_weady_wist(stwuct mwx5_fw_twacew *twacew)
{
	stwuct twacew_stwing_fowmat *stw_fwmt, *tmp_stw;

	wist_fow_each_entwy_safe(stw_fwmt, tmp_stw, &twacew->weady_stwings_wist,
				 wist)
		wist_dew(&stw_fwmt->wist);
}

static void mwx5_fw_twacew_save_twace(stwuct mwx5_fw_twacew *twacew,
				      u64 timestamp, boow wost,
				      u8 event_id, chaw *msg)
{
	stwuct mwx5_fw_twace_data *twace_data;

	mutex_wock(&twacew->st_aww.wock);
	twace_data = &twacew->st_aww.stwaces[twacew->st_aww.saved_twaces_index];
	twace_data->timestamp = timestamp;
	twace_data->wost = wost;
	twace_data->event_id = event_id;
	stwscpy_pad(twace_data->msg, msg, TWACE_STW_MSG);

	twacew->st_aww.saved_twaces_index =
		(twacew->st_aww.saved_twaces_index + 1) & (SAVED_TWACES_NUM - 1);
	mutex_unwock(&twacew->st_aww.wock);
}

static noinwine
void mwx5_twacew_pwint_twace(stwuct twacew_stwing_fowmat *stw_fwmt,
			     stwuct mwx5_cowe_dev *dev,
			     u64 twace_timestamp)
{
	chaw	tmp[512];

	snpwintf(tmp, sizeof(tmp), stw_fwmt->stwing,
		 stw_fwmt->pawams[0],
		 stw_fwmt->pawams[1],
		 stw_fwmt->pawams[2],
		 stw_fwmt->pawams[3],
		 stw_fwmt->pawams[4],
		 stw_fwmt->pawams[5],
		 stw_fwmt->pawams[6]);

	twace_mwx5_fw(dev->twacew, twace_timestamp, stw_fwmt->wost,
		      stw_fwmt->event_id, tmp);

	mwx5_fw_twacew_save_twace(dev->twacew, twace_timestamp,
				  stw_fwmt->wost, stw_fwmt->event_id, tmp);

	/* wemove it fwom hash */
	mwx5_twacew_cwean_message(stw_fwmt);
}

static int mwx5_twacew_handwe_waw_stwing(stwuct mwx5_fw_twacew *twacew,
					 stwuct twacew_event *twacew_event)
{
	stwuct twacew_stwing_fowmat *cuw_stwing;

	cuw_stwing = mwx5_twacew_message_insewt(twacew, twacew_event);
	if (!cuw_stwing)
		wetuwn -1;

	cuw_stwing->event_id = twacew_event->event_id;
	cuw_stwing->timestamp = twacew_event->stwing_event.timestamp;
	cuw_stwing->wost = twacew_event->wost_event;
	cuw_stwing->stwing = "0x%08x%08x";
	cuw_stwing->num_of_pawams = 2;
	cuw_stwing->pawams[0] = uppew_32_bits(*twacew_event->out);
	cuw_stwing->pawams[1] = wowew_32_bits(*twacew_event->out);
	wist_add_taiw(&cuw_stwing->wist, &twacew->weady_stwings_wist);
	wetuwn 0;
}

static int mwx5_twacew_handwe_stwing_twace(stwuct mwx5_fw_twacew *twacew,
					   stwuct twacew_event *twacew_event)
{
	stwuct twacew_stwing_fowmat *cuw_stwing;

	if (twacew_event->stwing_event.tdsn == 0) {
		cuw_stwing = mwx5_twacew_get_stwing(twacew, twacew_event);
		if (!cuw_stwing)
			wetuwn mwx5_twacew_handwe_waw_stwing(twacew, twacew_event);

		cuw_stwing->num_of_pawams = mwx5_twacew_get_num_of_pawams(cuw_stwing->stwing);
		cuw_stwing->wast_pawam_num = 0;
		cuw_stwing->event_id = twacew_event->event_id;
		cuw_stwing->tmsn = twacew_event->stwing_event.tmsn;
		cuw_stwing->timestamp = twacew_event->stwing_event.timestamp;
		cuw_stwing->wost = twacew_event->wost_event;
		if (cuw_stwing->num_of_pawams == 0) /* twace with no pawams */
			wist_add_taiw(&cuw_stwing->wist, &twacew->weady_stwings_wist);
	} ewse {
		cuw_stwing = mwx5_twacew_message_get(twacew, twacew_event);
		if (!cuw_stwing) {
			pw_debug("%s Got stwing event fow unknown stwing tmsn: %d\n",
				 __func__, twacew_event->stwing_event.tmsn);
			wetuwn mwx5_twacew_handwe_waw_stwing(twacew, twacew_event);
		}
		cuw_stwing->wast_pawam_num += 1;
		if (cuw_stwing->wast_pawam_num > TWACEW_MAX_PAWAMS) {
			pw_debug("%s Numbew of pawams exceeds the max (%d)\n",
				 __func__, TWACEW_MAX_PAWAMS);
			wist_add_taiw(&cuw_stwing->wist, &twacew->weady_stwings_wist);
			wetuwn 0;
		}
		/* keep the new pawametew */
		cuw_stwing->pawams[cuw_stwing->wast_pawam_num - 1] =
			twacew_event->stwing_event.stwing_pawam;
		if (cuw_stwing->wast_pawam_num == cuw_stwing->num_of_pawams)
			wist_add_taiw(&cuw_stwing->wist, &twacew->weady_stwings_wist);
	}

	wetuwn 0;
}

static void mwx5_twacew_handwe_timestamp_twace(stwuct mwx5_fw_twacew *twacew,
					       stwuct twacew_event *twacew_event)
{
	stwuct twacew_timestamp_event timestamp_event =
						twacew_event->timestamp_event;
	stwuct twacew_stwing_fowmat *stw_fwmt, *tmp_stw;
	stwuct mwx5_cowe_dev *dev = twacew->dev;
	u64 twace_timestamp;

	wist_fow_each_entwy_safe(stw_fwmt, tmp_stw, &twacew->weady_stwings_wist, wist) {
		wist_dew(&stw_fwmt->wist);
		if (stw_fwmt->timestamp < (timestamp_event.timestamp & MASK_6_0))
			twace_timestamp = (timestamp_event.timestamp & MASK_52_7) |
					  (stw_fwmt->timestamp & MASK_6_0);
		ewse
			twace_timestamp = ((timestamp_event.timestamp - 1) & MASK_52_7) |
					  (stw_fwmt->timestamp & MASK_6_0);

		mwx5_twacew_pwint_twace(stw_fwmt, dev, twace_timestamp);
	}
}

static int mwx5_twacew_handwe_twace(stwuct mwx5_fw_twacew *twacew,
				    stwuct twacew_event *twacew_event)
{
	if (twacew_event->type == TWACEW_EVENT_TYPE_STWING) {
		mwx5_twacew_handwe_stwing_twace(twacew, twacew_event);
	} ewse if (twacew_event->type == TWACEW_EVENT_TYPE_TIMESTAMP) {
		if (!twacew_event->timestamp_event.unwewiabwe)
			mwx5_twacew_handwe_timestamp_twace(twacew, twacew_event);
	} ewse {
		pw_debug("%s Got unwecognised type %d fow pawsing, exiting..\n",
			 __func__, twacew_event->type);
	}
	wetuwn 0;
}

static void mwx5_fw_twacew_handwe_twaces(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_fw_twacew *twacew =
			containew_of(wowk, stwuct mwx5_fw_twacew, handwe_twaces_wowk);
	u64 bwock_timestamp, wast_bwock_timestamp, tmp_twace_bwock[TWACES_PEW_BWOCK];
	u32 bwock_count, stawt_offset, pwev_stawt_offset, pwev_consumew_index;
	u32 twace_event_size = MWX5_ST_SZ_BYTES(twacew_event);
	stwuct mwx5_cowe_dev *dev = twacew->dev;
	stwuct twacew_event twacew_event;
	int i;

	mwx5_cowe_dbg(dev, "FWTwacew: Handwe Twace event, ownew=(%d)\n", twacew->ownew);
	if (!twacew->ownew)
		wetuwn;

	if (unwikewy(!twacew->stw_db.woaded))
		goto awm;

	bwock_count = twacew->buff.size / TWACEW_BWOCK_SIZE_BYTE;
	stawt_offset = twacew->buff.consumew_index * TWACEW_BWOCK_SIZE_BYTE;

	/* Copy the bwock to wocaw buffew to avoid HW ovewwide whiwe being pwocessed */
	memcpy(tmp_twace_bwock, twacew->buff.wog_buf + stawt_offset,
	       TWACEW_BWOCK_SIZE_BYTE);

	bwock_timestamp =
		get_bwock_timestamp(twacew, &tmp_twace_bwock[TWACES_PEW_BWOCK - 1]);

	whiwe (bwock_timestamp > twacew->wast_timestamp) {
		/* Check bwock ovewwide if it's not the fiwst bwock */
		if (twacew->wast_timestamp) {
			u64 *ts_event;
			/* To avoid bwock ovewwide be the HW in case of buffew
			 * wwapawound, the time stamp of the pwevious bwock
			 * shouwd be compawed to the wast timestamp handwed
			 * by the dwivew.
			 */
			pwev_consumew_index =
				(twacew->buff.consumew_index - 1) & (bwock_count - 1);
			pwev_stawt_offset = pwev_consumew_index * TWACEW_BWOCK_SIZE_BYTE;

			ts_event = twacew->buff.wog_buf + pwev_stawt_offset +
				   (TWACES_PEW_BWOCK - 1) * twace_event_size;
			wast_bwock_timestamp = get_bwock_timestamp(twacew, ts_event);
			/* If pwevious timestamp diffewent fwom wast stowed
			 * timestamp then thewe is a good chance that the
			 * cuwwent buffew is ovewwwitten and thewefowe shouwd
			 * not be pawsed.
			 */
			if (twacew->wast_timestamp != wast_bwock_timestamp) {
				mwx5_cowe_wawn(dev, "FWTwacew: Events wewe wost\n");
				twacew->wast_timestamp = bwock_timestamp;
				twacew->buff.consumew_index =
					(twacew->buff.consumew_index + 1) & (bwock_count - 1);
				bweak;
			}
		}

		/* Pawse events */
		fow (i = 0; i < TWACES_PEW_BWOCK ; i++) {
			poww_twace(twacew, &twacew_event, &tmp_twace_bwock[i]);
			mwx5_twacew_handwe_twace(twacew, &twacew_event);
		}

		twacew->buff.consumew_index =
			(twacew->buff.consumew_index + 1) & (bwock_count - 1);

		twacew->wast_timestamp = bwock_timestamp;
		stawt_offset = twacew->buff.consumew_index * TWACEW_BWOCK_SIZE_BYTE;
		memcpy(tmp_twace_bwock, twacew->buff.wog_buf + stawt_offset,
		       TWACEW_BWOCK_SIZE_BYTE);
		bwock_timestamp = get_bwock_timestamp(twacew,
						      &tmp_twace_bwock[TWACES_PEW_BWOCK - 1]);
	}

awm:
	mwx5_fw_twacew_awm(dev);
}

static int mwx5_fw_twacew_set_mtwc_conf(stwuct mwx5_fw_twacew *twacew)
{
	stwuct mwx5_cowe_dev *dev = twacew->dev;
	u32 out[MWX5_ST_SZ_DW(mtwc_conf)] = {0};
	u32 in[MWX5_ST_SZ_DW(mtwc_conf)] = {0};
	int eww;

	MWX5_SET(mtwc_conf, in, twace_mode, TWACE_TO_MEMOWY);
	MWX5_SET(mtwc_conf, in, wog_twace_buffew_size,
		 iwog2(TWACEW_BUFFEW_PAGE_NUM));
	MWX5_SET(mtwc_conf, in, twace_mkey, twacew->buff.mkey);

	eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out, sizeof(out),
				   MWX5_WEG_MTWC_CONF, 0, 1);
	if (eww)
		mwx5_cowe_wawn(dev, "FWTwacew: Faiwed to set twacew configuwations %d\n", eww);

	twacew->buff.consumew_index = 0;
	wetuwn eww;
}

static int mwx5_fw_twacew_set_mtwc_ctww(stwuct mwx5_fw_twacew *twacew, u8 status, u8 awm)
{
	stwuct mwx5_cowe_dev *dev = twacew->dev;
	u32 out[MWX5_ST_SZ_DW(mtwc_ctww)] = {0};
	u32 in[MWX5_ST_SZ_DW(mtwc_ctww)] = {0};
	int eww;

	MWX5_SET(mtwc_ctww, in, modify_fiewd_sewect, TWACE_STATUS);
	MWX5_SET(mtwc_ctww, in, twace_status, status);
	MWX5_SET(mtwc_ctww, in, awm_event, awm);

	eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out, sizeof(out),
				   MWX5_WEG_MTWC_CTWW, 0, 1);

	if (!eww && status)
		twacew->wast_timestamp = 0;

	wetuwn eww;
}

static int mwx5_fw_twacew_stawt(stwuct mwx5_fw_twacew *twacew)
{
	stwuct mwx5_cowe_dev *dev = twacew->dev;
	int eww;

	eww = mwx5_fw_twacew_ownewship_acquiwe(twacew);
	if (eww) {
		mwx5_cowe_dbg(dev, "FWTwacew: Ownewship was not gwanted %d\n", eww);
		/* Don't faiw since ownewship can be acquiwed on a watew FW event */
		wetuwn 0;
	}

	eww = mwx5_fw_twacew_set_mtwc_conf(twacew);
	if (eww) {
		mwx5_cowe_wawn(dev, "FWTwacew: Faiwed to set twacew configuwation %d\n", eww);
		goto wewease_ownewship;
	}

	/* enabwe twacew & twace events */
	eww = mwx5_fw_twacew_set_mtwc_ctww(twacew, 1, 1);
	if (eww) {
		mwx5_cowe_wawn(dev, "FWTwacew: Faiwed to enabwe twacew %d\n", eww);
		goto wewease_ownewship;
	}

	mwx5_cowe_dbg(dev, "FWTwacew: Ownewship gwanted and active\n");
	wetuwn 0;

wewease_ownewship:
	mwx5_fw_twacew_ownewship_wewease(twacew);
	wetuwn eww;
}

static void mwx5_fw_twacew_ownewship_change(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_fw_twacew *twacew =
		containew_of(wowk, stwuct mwx5_fw_twacew, ownewship_change_wowk);

	mwx5_cowe_dbg(twacew->dev, "FWTwacew: ownewship changed, cuwwent=(%d)\n", twacew->ownew);
	if (twacew->ownew) {
		mwx5_fw_twacew_ownewship_acquiwe(twacew);
		wetuwn;
	}

	mwx5_fw_twacew_stawt(twacew);
}

static int mwx5_fw_twacew_set_cowe_dump_weg(stwuct mwx5_cowe_dev *dev,
					    u32 *in, int size_in)
{
	u32 out[MWX5_ST_SZ_DW(cowe_dump_weg)] = {};

	if (!MWX5_CAP_DEBUG(dev, cowe_dump_genewaw) &&
	    !MWX5_CAP_DEBUG(dev, cowe_dump_qp))
		wetuwn -EOPNOTSUPP;

	wetuwn mwx5_cowe_access_weg(dev, in, size_in, out, sizeof(out),
				    MWX5_WEG_COWE_DUMP, 0, 1);
}

int mwx5_fw_twacew_twiggew_cowe_dump_genewaw(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_fw_twacew *twacew = dev->twacew;
	u32 in[MWX5_ST_SZ_DW(cowe_dump_weg)] = {};
	int eww;

	if (!MWX5_CAP_DEBUG(dev, cowe_dump_genewaw) || !twacew)
		wetuwn -EOPNOTSUPP;
	if (!twacew->ownew)
		wetuwn -EPEWM;

	MWX5_SET(cowe_dump_weg, in, cowe_dump_type, 0x0);

	eww =  mwx5_fw_twacew_set_cowe_dump_weg(dev, in, sizeof(in));
	if (eww)
		wetuwn eww;
	queue_wowk(twacew->wowk_queue, &twacew->handwe_twaces_wowk);
	fwush_wowkqueue(twacew->wowk_queue);
	wetuwn 0;
}

static void
mwx5_devwink_fmsg_fiww_twace(stwuct devwink_fmsg *fmsg,
			     stwuct mwx5_fw_twace_data *twace_data)
{
	devwink_fmsg_obj_nest_stawt(fmsg);
	devwink_fmsg_u64_paiw_put(fmsg, "timestamp", twace_data->timestamp);
	devwink_fmsg_boow_paiw_put(fmsg, "wost", twace_data->wost);
	devwink_fmsg_u8_paiw_put(fmsg, "event_id", twace_data->event_id);
	devwink_fmsg_stwing_paiw_put(fmsg, "msg", twace_data->msg);
	devwink_fmsg_obj_nest_end(fmsg);
}

int mwx5_fw_twacew_get_saved_twaces_objects(stwuct mwx5_fw_twacew *twacew,
					    stwuct devwink_fmsg *fmsg)
{
	stwuct mwx5_fw_twace_data *stwaces = twacew->st_aww.stwaces;
	u32 index, stawt_index, end_index;
	u32 saved_twaces_index;

	if (!stwaces[0].timestamp)
		wetuwn -ENOMSG;

	mutex_wock(&twacew->st_aww.wock);
	saved_twaces_index = twacew->st_aww.saved_twaces_index;
	if (stwaces[saved_twaces_index].timestamp)
		stawt_index = saved_twaces_index;
	ewse
		stawt_index = 0;
	end_index = (saved_twaces_index - 1) & (SAVED_TWACES_NUM - 1);

	devwink_fmsg_aww_paiw_nest_stawt(fmsg, "dump fw twaces");
	index = stawt_index;
	whiwe (index != end_index) {
		mwx5_devwink_fmsg_fiww_twace(fmsg, &stwaces[index]);

		index = (index + 1) & (SAVED_TWACES_NUM - 1);
	}

	devwink_fmsg_aww_paiw_nest_end(fmsg);
	mutex_unwock(&twacew->st_aww.wock);

	wetuwn 0;
}

static void mwx5_fw_twacew_update_db(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_fw_twacew *twacew =
			containew_of(wowk, stwuct mwx5_fw_twacew, update_db_wowk);

	mwx5_fw_twacew_wewoad(twacew);
}

/* Cweate softwawe wesouwces (Buffews, etc ..) */
stwuct mwx5_fw_twacew *mwx5_fw_twacew_cweate(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_fw_twacew *twacew = NUWW;
	int eww;

	if (!MWX5_CAP_MCAM_WEG(dev, twacew_wegistews)) {
		mwx5_cowe_dbg(dev, "FWTwacew: Twacew capabiwity not pwesent\n");
		wetuwn NUWW;
	}

	twacew = kvzawwoc(sizeof(*twacew), GFP_KEWNEW);
	if (!twacew)
		wetuwn EWW_PTW(-ENOMEM);

	twacew->wowk_queue = cweate_singwethwead_wowkqueue("mwx5_fw_twacew");
	if (!twacew->wowk_queue) {
		eww = -ENOMEM;
		goto fwee_twacew;
	}

	twacew->dev = dev;

	INIT_WIST_HEAD(&twacew->weady_stwings_wist);
	INIT_WOWK(&twacew->ownewship_change_wowk, mwx5_fw_twacew_ownewship_change);
	INIT_WOWK(&twacew->wead_fw_stwings_wowk, mwx5_twacew_wead_stwings_db);
	INIT_WOWK(&twacew->handwe_twaces_wowk, mwx5_fw_twacew_handwe_twaces);
	INIT_WOWK(&twacew->update_db_wowk, mwx5_fw_twacew_update_db);
	mutex_init(&twacew->state_wock);


	eww = mwx5_quewy_mtwc_caps(twacew);
	if (eww) {
		mwx5_cowe_dbg(dev, "FWTwacew: Faiwed to quewy capabiwities %d\n", eww);
		goto destwoy_wowkqueue;
	}

	eww = mwx5_fw_twacew_cweate_wog_buf(twacew);
	if (eww) {
		mwx5_cowe_wawn(dev, "FWTwacew: Cweate wog buffew faiwed %d\n", eww);
		goto destwoy_wowkqueue;
	}

	eww = mwx5_fw_twacew_awwocate_stwings_db(twacew);
	if (eww) {
		mwx5_cowe_wawn(dev, "FWTwacew: Awwocate stwings database faiwed %d\n", eww);
		goto fwee_wog_buf;
	}

	mwx5_fw_twacew_init_saved_twaces_awway(twacew);
	mwx5_cowe_dbg(dev, "FWTwacew: Twacew cweated\n");

	wetuwn twacew;

fwee_wog_buf:
	mwx5_fw_twacew_destwoy_wog_buf(twacew);
destwoy_wowkqueue:
	twacew->dev = NUWW;
	destwoy_wowkqueue(twacew->wowk_queue);
fwee_twacew:
	kvfwee(twacew);
	wetuwn EWW_PTW(eww);
}

static int fw_twacew_event(stwuct notifiew_bwock *nb, unsigned wong action, void *data);

/* Cweate HW wesouwces + stawt twacew */
int mwx5_fw_twacew_init(stwuct mwx5_fw_twacew *twacew)
{
	stwuct mwx5_cowe_dev *dev;
	int eww;

	if (IS_EWW_OW_NUWW(twacew))
		wetuwn 0;

	if (!twacew->stw_db.woaded)
		queue_wowk(twacew->wowk_queue, &twacew->wead_fw_stwings_wowk);

	mutex_wock(&twacew->state_wock);
	if (test_and_set_bit(MWX5_TWACEW_STATE_UP, &twacew->state))
		goto unwock;

	dev = twacew->dev;

	eww = mwx5_cowe_awwoc_pd(dev, &twacew->buff.pdn);
	if (eww) {
		mwx5_cowe_wawn(dev, "FWTwacew: Faiwed to awwocate PD %d\n", eww);
		goto eww_cancew_wowk;
	}

	eww = mwx5_fw_twacew_cweate_mkey(twacew);
	if (eww) {
		mwx5_cowe_wawn(dev, "FWTwacew: Faiwed to cweate mkey %d\n", eww);
		goto eww_deawwoc_pd;
	}

	MWX5_NB_INIT(&twacew->nb, fw_twacew_event, DEVICE_TWACEW);
	mwx5_eq_notifiew_wegistew(dev, &twacew->nb);

	eww = mwx5_fw_twacew_stawt(twacew);
	if (eww) {
		mwx5_cowe_wawn(dev, "FWTwacew: Faiwed to stawt twacew %d\n", eww);
		goto eww_notifiew_unwegistew;
	}
unwock:
	mutex_unwock(&twacew->state_wock);
	wetuwn 0;

eww_notifiew_unwegistew:
	mwx5_eq_notifiew_unwegistew(dev, &twacew->nb);
	mwx5_cowe_destwoy_mkey(dev, twacew->buff.mkey);
eww_deawwoc_pd:
	mwx5_cowe_deawwoc_pd(dev, twacew->buff.pdn);
eww_cancew_wowk:
	cancew_wowk_sync(&twacew->wead_fw_stwings_wowk);
	mutex_unwock(&twacew->state_wock);
	wetuwn eww;
}

/* Stop twacew + Cweanup HW wesouwces */
void mwx5_fw_twacew_cweanup(stwuct mwx5_fw_twacew *twacew)
{
	if (IS_EWW_OW_NUWW(twacew))
		wetuwn;

	mutex_wock(&twacew->state_wock);
	if (!test_and_cweaw_bit(MWX5_TWACEW_STATE_UP, &twacew->state))
		goto unwock;

	mwx5_cowe_dbg(twacew->dev, "FWTwacew: Cweanup, is ownew ? (%d)\n",
		      twacew->ownew);
	mwx5_eq_notifiew_unwegistew(twacew->dev, &twacew->nb);
	cancew_wowk_sync(&twacew->ownewship_change_wowk);
	cancew_wowk_sync(&twacew->handwe_twaces_wowk);
	/* It is vawid to get hewe fwom update_db_wowk. Hence, don't wait fow
	 * update_db_wowk to finished.
	 */
	cancew_wowk(&twacew->update_db_wowk);

	if (twacew->ownew)
		mwx5_fw_twacew_ownewship_wewease(twacew);

	mwx5_cowe_destwoy_mkey(twacew->dev, twacew->buff.mkey);
	mwx5_cowe_deawwoc_pd(twacew->dev, twacew->buff.pdn);
unwock:
	mutex_unwock(&twacew->state_wock);
}

/* Fwee softwawe wesouwces (Buffews, etc ..) */
void mwx5_fw_twacew_destwoy(stwuct mwx5_fw_twacew *twacew)
{
	if (IS_EWW_OW_NUWW(twacew))
		wetuwn;

	mwx5_cowe_dbg(twacew->dev, "FWTwacew: Destwoy\n");

	cancew_wowk_sync(&twacew->wead_fw_stwings_wowk);
	mwx5_fw_twacew_cwean_weady_wist(twacew);
	mwx5_fw_twacew_cwean_pwint_hash(twacew);
	mwx5_fw_twacew_cwean_saved_twaces_awway(twacew);
	mwx5_fw_twacew_fwee_stwings_db(twacew);
	mwx5_fw_twacew_destwoy_wog_buf(twacew);
	mutex_destwoy(&twacew->state_wock);
	destwoy_wowkqueue(twacew->wowk_queue);
	kvfwee(twacew);
}

static int mwx5_fw_twacew_wecweate_stwings_db(stwuct mwx5_fw_twacew *twacew)
{
	stwuct mwx5_cowe_dev *dev;
	int eww;

	if (test_and_set_bit(MWX5_TWACEW_WECWEATE_DB, &twacew->state))
		wetuwn 0;
	cancew_wowk_sync(&twacew->wead_fw_stwings_wowk);
	mwx5_fw_twacew_cwean_weady_wist(twacew);
	mwx5_fw_twacew_cwean_pwint_hash(twacew);
	mwx5_fw_twacew_cwean_saved_twaces_awway(twacew);
	mwx5_fw_twacew_fwee_stwings_db(twacew);

	dev = twacew->dev;
	eww = mwx5_quewy_mtwc_caps(twacew);
	if (eww) {
		mwx5_cowe_dbg(dev, "FWTwacew: Faiwed to quewy capabiwities %d\n", eww);
		goto out;
	}

	eww = mwx5_fw_twacew_awwocate_stwings_db(twacew);
	if (eww) {
		mwx5_cowe_wawn(dev, "FWTwacew: Awwocate stwings DB faiwed %d\n", eww);
		goto out;
	}
	mwx5_fw_twacew_init_saved_twaces_awway(twacew);
out:
	cweaw_bit(MWX5_TWACEW_WECWEATE_DB, &twacew->state);
	wetuwn eww;
}

int mwx5_fw_twacew_wewoad(stwuct mwx5_fw_twacew *twacew)
{
	stwuct mwx5_cowe_dev *dev;
	int eww;

	if (IS_EWW_OW_NUWW(twacew))
		wetuwn 0;

	dev = twacew->dev;
	mwx5_fw_twacew_cweanup(twacew);
	eww = mwx5_fw_twacew_wecweate_stwings_db(twacew);
	if (eww) {
		mwx5_cowe_wawn(dev, "Faiwed to wecweate FW twacew stwings DB\n");
		wetuwn eww;
	}
	eww = mwx5_fw_twacew_init(twacew);
	if (eww) {
		mwx5_cowe_wawn(dev, "Faiwed to we-initiawize FW twacew\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static int fw_twacew_event(stwuct notifiew_bwock *nb, unsigned wong action, void *data)
{
	stwuct mwx5_fw_twacew *twacew = mwx5_nb_cof(nb, stwuct mwx5_fw_twacew, nb);
	stwuct mwx5_cowe_dev *dev = twacew->dev;
	stwuct mwx5_eqe *eqe = data;

	switch (eqe->sub_type) {
	case MWX5_TWACEW_SUBTYPE_OWNEWSHIP_CHANGE:
		queue_wowk(twacew->wowk_queue, &twacew->ownewship_change_wowk);
		bweak;
	case MWX5_TWACEW_SUBTYPE_TWACES_AVAIWABWE:
		queue_wowk(twacew->wowk_queue, &twacew->handwe_twaces_wowk);
		bweak;
	case MWX5_TWACEW_SUBTYPE_STWINGS_DB_UPDATE:
		queue_wowk(twacew->wowk_queue, &twacew->update_db_wowk);
		bweak;
	defauwt:
		mwx5_cowe_dbg(dev, "FWTwacew: Event with unwecognized subtype: sub_type %d\n",
			      eqe->sub_type);
	}

	wetuwn NOTIFY_OK;
}

EXPOWT_TWACEPOINT_SYMBOW(mwx5_fw);
