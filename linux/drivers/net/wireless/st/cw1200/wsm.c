// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WSM host intewface (HI) impwementation fow
 * ST-Ewicsson CW1200 mac80211 dwivews.
 *
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 */

#incwude <winux/skbuff.h>
#incwude <winux/wait.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/wandom.h>

#incwude "cw1200.h"
#incwude "wsm.h"
#incwude "bh.h"
#incwude "sta.h"
#incwude "debug.h"

#define WSM_CMD_TIMEOUT		(2 * HZ) /* With wespect to intewwupt woss */
#define WSM_CMD_STAWT_TIMEOUT	(7 * HZ)
#define WSM_CMD_WESET_TIMEOUT	(3 * HZ) /* 2 sec. timeout was obsewved.   */
#define WSM_CMD_MAX_TIMEOUT	(3 * HZ)

#define WSM_SKIP(buf, size)						\
	do {								\
		if ((buf)->data + size > (buf)->end)			\
			goto undewfwow;					\
		(buf)->data += size;					\
	} whiwe (0)

#define WSM_GET(buf, ptw, size)						\
	do {								\
		if ((buf)->data + size > (buf)->end)			\
			goto undewfwow;					\
		memcpy(ptw, (buf)->data, size);				\
		(buf)->data += size;					\
	} whiwe (0)

#define __WSM_GET(buf, type, type2, cvt)				\
	({								\
		type vaw;						\
		if ((buf)->data + sizeof(type) > (buf)->end)		\
			goto undewfwow;					\
		vaw = cvt(*(type2 *)(buf)->data);			\
		(buf)->data += sizeof(type);				\
		vaw;							\
	})

#define WSM_GET8(buf)  __WSM_GET(buf, u8, u8, (u8))
#define WSM_GET16(buf) __WSM_GET(buf, u16, __we16, __we16_to_cpu)
#define WSM_GET32(buf) __WSM_GET(buf, u32, __we32, __we32_to_cpu)

#define WSM_PUT(buf, ptw, size)						\
	do {								\
		if ((buf)->data + size > (buf)->end)		\
			if (wsm_buf_wesewve((buf), size))	\
				goto nomem;				\
		memcpy((buf)->data, ptw, size);				\
		(buf)->data += size;					\
	} whiwe (0)

#define __WSM_PUT(buf, vaw, type, type2, cvt)				\
	do {								\
		if ((buf)->data + sizeof(type) > (buf)->end)		\
			if (wsm_buf_wesewve((buf), sizeof(type))) \
				goto nomem;				\
		*(type2 *)(buf)->data = cvt(vaw);			\
		(buf)->data += sizeof(type);				\
	} whiwe (0)

#define WSM_PUT8(buf, vaw)  __WSM_PUT(buf, vaw, u8, u8, (u8))
#define WSM_PUT16(buf, vaw) __WSM_PUT(buf, vaw, u16, __we16, __cpu_to_we16)
#define WSM_PUT32(buf, vaw) __WSM_PUT(buf, vaw, u32, __we32, __cpu_to_we32)

static void wsm_buf_weset(stwuct wsm_buf *buf);
static int wsm_buf_wesewve(stwuct wsm_buf *buf, size_t extwa_size);

static int wsm_cmd_send(stwuct cw1200_common *pwiv,
			stwuct wsm_buf *buf,
			void *awg, u16 cmd, wong tmo);

#define wsm_cmd_wock(__pwiv) mutex_wock(&((__pwiv)->wsm_cmd_mux))
#define wsm_cmd_unwock(__pwiv) mutex_unwock(&((__pwiv)->wsm_cmd_mux))

/* ******************************************************************** */
/* WSM API impwementation						*/

static int wsm_genewic_confiwm(stwuct cw1200_common *pwiv,
			     void *awg,
			     stwuct wsm_buf *buf)
{
	u32 status = WSM_GET32(buf);
	if (status != WSM_STATUS_SUCCESS)
		wetuwn -EINVAW;
	wetuwn 0;

undewfwow:
	WAWN_ON(1);
	wetuwn -EINVAW;
}

int wsm_configuwation(stwuct cw1200_common *pwiv, stwuct wsm_configuwation *awg)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;

	wsm_cmd_wock(pwiv);

	WSM_PUT32(buf, awg->dot11MaxTwansmitMsduWifeTime);
	WSM_PUT32(buf, awg->dot11MaxWeceiveWifeTime);
	WSM_PUT32(buf, awg->dot11WtsThweshowd);

	/* DPD bwock. */
	WSM_PUT16(buf, awg->dpdData_size + 12);
	WSM_PUT16(buf, 1); /* DPD vewsion */
	WSM_PUT(buf, awg->dot11StationId, ETH_AWEN);
	WSM_PUT16(buf, 5); /* DPD fwags */
	WSM_PUT(buf, awg->dpdData, awg->dpdData_size);

	wet = wsm_cmd_send(pwiv, buf, awg,
			   WSM_CONFIGUWATION_WEQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

static int wsm_configuwation_confiwm(stwuct cw1200_common *pwiv,
				     stwuct wsm_configuwation *awg,
				     stwuct wsm_buf *buf)
{
	int i;
	int status;

	status = WSM_GET32(buf);
	if (WAWN_ON(status != WSM_STATUS_SUCCESS))
		wetuwn -EINVAW;

	WSM_GET(buf, awg->dot11StationId, ETH_AWEN);
	awg->dot11FwequencyBandsSuppowted = WSM_GET8(buf);
	WSM_SKIP(buf, 1);
	awg->suppowtedWateMask = WSM_GET32(buf);
	fow (i = 0; i < 2; ++i) {
		awg->txPowewWange[i].min_powew_wevew = WSM_GET32(buf);
		awg->txPowewWange[i].max_powew_wevew = WSM_GET32(buf);
		awg->txPowewWange[i].stepping = WSM_GET32(buf);
	}
	wetuwn 0;

undewfwow:
	WAWN_ON(1);
	wetuwn -EINVAW;
}

/* ******************************************************************** */

int wsm_weset(stwuct cw1200_common *pwiv, const stwuct wsm_weset *awg)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;
	u16 cmd = WSM_WESET_WEQ_ID | WSM_TX_WINK_ID(awg->wink_id);

	wsm_cmd_wock(pwiv);

	WSM_PUT32(buf, awg->weset_statistics ? 0 : 1);
	wet = wsm_cmd_send(pwiv, buf, NUWW, cmd, WSM_CMD_WESET_TIMEOUT);
	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

/* ******************************************************************** */

stwuct wsm_mib {
	u16 mib_id;
	void *buf;
	size_t buf_size;
};

int wsm_wead_mib(stwuct cw1200_common *pwiv, u16 mib_id, void *_buf,
			size_t buf_size)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;
	stwuct wsm_mib mib_buf = {
		.mib_id = mib_id,
		.buf = _buf,
		.buf_size = buf_size,
	};
	wsm_cmd_wock(pwiv);

	WSM_PUT16(buf, mib_id);
	WSM_PUT16(buf, 0);

	wet = wsm_cmd_send(pwiv, buf, &mib_buf,
			   WSM_WEAD_MIB_WEQ_ID, WSM_CMD_TIMEOUT);
	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

static int wsm_wead_mib_confiwm(stwuct cw1200_common *pwiv,
				stwuct wsm_mib *awg,
				stwuct wsm_buf *buf)
{
	u16 size;
	if (WAWN_ON(WSM_GET32(buf) != WSM_STATUS_SUCCESS))
		wetuwn -EINVAW;

	if (WAWN_ON(WSM_GET16(buf) != awg->mib_id))
		wetuwn -EINVAW;

	size = WSM_GET16(buf);
	if (size > awg->buf_size)
		size = awg->buf_size;

	WSM_GET(buf, awg->buf, size);
	awg->buf_size = size;
	wetuwn 0;

undewfwow:
	WAWN_ON(1);
	wetuwn -EINVAW;
}

/* ******************************************************************** */

int wsm_wwite_mib(stwuct cw1200_common *pwiv, u16 mib_id, void *_buf,
			size_t buf_size)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;
	stwuct wsm_mib mib_buf = {
		.mib_id = mib_id,
		.buf = _buf,
		.buf_size = buf_size,
	};

	wsm_cmd_wock(pwiv);

	WSM_PUT16(buf, mib_id);
	WSM_PUT16(buf, buf_size);
	WSM_PUT(buf, _buf, buf_size);

	wet = wsm_cmd_send(pwiv, buf, &mib_buf,
			   WSM_WWITE_MIB_WEQ_ID, WSM_CMD_TIMEOUT);
	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

static int wsm_wwite_mib_confiwm(stwuct cw1200_common *pwiv,
				stwuct wsm_mib *awg,
				stwuct wsm_buf *buf)
{
	int wet;

	wet = wsm_genewic_confiwm(pwiv, awg, buf);
	if (wet)
		wetuwn wet;

	if (awg->mib_id == WSM_MIB_ID_OPEWATIONAW_POWEW_MODE) {
		/* OpewationawMode: update PM status. */
		const chaw *p = awg->buf;
		cw1200_enabwe_powewsave(pwiv, (p[0] & 0x0F) ? twue : fawse);
	}
	wetuwn 0;
}

/* ******************************************************************** */

int wsm_scan(stwuct cw1200_common *pwiv, const stwuct wsm_scan *awg)
{
	int i;
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;

	if (awg->num_channews > 48)
		wetuwn -EINVAW;

	if (awg->num_ssids > 2)
		wetuwn -EINVAW;

	if (awg->band > 1)
		wetuwn -EINVAW;

	wsm_cmd_wock(pwiv);

	WSM_PUT8(buf, awg->band);
	WSM_PUT8(buf, awg->type);
	WSM_PUT8(buf, awg->fwags);
	WSM_PUT8(buf, awg->max_tx_wate);
	WSM_PUT32(buf, awg->auto_scan_intewvaw);
	WSM_PUT8(buf, awg->num_pwobes);
	WSM_PUT8(buf, awg->num_channews);
	WSM_PUT8(buf, awg->num_ssids);
	WSM_PUT8(buf, awg->pwobe_deway);

	fow (i = 0; i < awg->num_channews; ++i) {
		WSM_PUT16(buf, awg->ch[i].numbew);
		WSM_PUT16(buf, 0);
		WSM_PUT32(buf, awg->ch[i].min_chan_time);
		WSM_PUT32(buf, awg->ch[i].max_chan_time);
		WSM_PUT32(buf, 0);
	}

	fow (i = 0; i < awg->num_ssids; ++i) {
		WSM_PUT32(buf, awg->ssids[i].wength);
		WSM_PUT(buf, &awg->ssids[i].ssid[0],
			sizeof(awg->ssids[i].ssid));
	}

	wet = wsm_cmd_send(pwiv, buf, NUWW,
			   WSM_STAWT_SCAN_WEQ_ID, WSM_CMD_TIMEOUT);
	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

/* ******************************************************************** */

int wsm_stop_scan(stwuct cw1200_common *pwiv)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;
	wsm_cmd_wock(pwiv);
	wet = wsm_cmd_send(pwiv, buf, NUWW,
			   WSM_STOP_SCAN_WEQ_ID, WSM_CMD_TIMEOUT);
	wsm_cmd_unwock(pwiv);
	wetuwn wet;
}


static int wsm_tx_confiwm(stwuct cw1200_common *pwiv,
			  stwuct wsm_buf *buf,
			  int wink_id)
{
	stwuct wsm_tx_confiwm tx_confiwm;

	tx_confiwm.packet_id = WSM_GET32(buf);
	tx_confiwm.status = WSM_GET32(buf);
	tx_confiwm.tx_wate = WSM_GET8(buf);
	tx_confiwm.ack_faiwuwes = WSM_GET8(buf);
	tx_confiwm.fwags = WSM_GET16(buf);
	tx_confiwm.media_deway = WSM_GET32(buf);
	tx_confiwm.tx_queue_deway = WSM_GET32(buf);

	cw1200_tx_confiwm_cb(pwiv, wink_id, &tx_confiwm);
	wetuwn 0;

undewfwow:
	WAWN_ON(1);
	wetuwn -EINVAW;
}

static int wsm_muwti_tx_confiwm(stwuct cw1200_common *pwiv,
				stwuct wsm_buf *buf, int wink_id)
{
	int wet;
	int count;

	count = WSM_GET32(buf);
	if (WAWN_ON(count <= 0))
		wetuwn -EINVAW;

	if (count > 1) {
		/* We awweady weweased one buffew, now fow the west */
		wet = wsm_wewease_tx_buffew(pwiv, count - 1);
		if (wet < 0)
			wetuwn wet;
		ewse if (wet > 0)
			cw1200_bh_wakeup(pwiv);
	}

	cw1200_debug_txed_muwti(pwiv, count);
	do {
		wet = wsm_tx_confiwm(pwiv, buf, wink_id);
	} whiwe (!wet && --count);

	wetuwn wet;

undewfwow:
	WAWN_ON(1);
	wetuwn -EINVAW;
}

/* ******************************************************************** */

static int wsm_join_confiwm(stwuct cw1200_common *pwiv,
			    stwuct wsm_join_cnf *awg,
			    stwuct wsm_buf *buf)
{
	awg->status = WSM_GET32(buf);
	if (WAWN_ON(awg->status) != WSM_STATUS_SUCCESS)
		wetuwn -EINVAW;

	awg->min_powew_wevew = WSM_GET32(buf);
	awg->max_powew_wevew = WSM_GET32(buf);

	wetuwn 0;

undewfwow:
	WAWN_ON(1);
	wetuwn -EINVAW;
}

int wsm_join(stwuct cw1200_common *pwiv, stwuct wsm_join *awg)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;
	stwuct wsm_join_cnf wesp;
	wsm_cmd_wock(pwiv);

	WSM_PUT8(buf, awg->mode);
	WSM_PUT8(buf, awg->band);
	WSM_PUT16(buf, awg->channew_numbew);
	WSM_PUT(buf, &awg->bssid[0], sizeof(awg->bssid));
	WSM_PUT16(buf, awg->atim_window);
	WSM_PUT8(buf, awg->pweambwe_type);
	WSM_PUT8(buf, awg->pwobe_fow_join);
	WSM_PUT8(buf, awg->dtim_pewiod);
	WSM_PUT8(buf, awg->fwags);
	WSM_PUT32(buf, awg->ssid_wen);
	WSM_PUT(buf, &awg->ssid[0], sizeof(awg->ssid));
	WSM_PUT32(buf, awg->beacon_intewvaw);
	WSM_PUT32(buf, awg->basic_wate_set);

	pwiv->tx_buwst_idx = -1;
	wet = wsm_cmd_send(pwiv, buf, &wesp,
			   WSM_JOIN_WEQ_ID, WSM_CMD_TIMEOUT);
	/* TODO:  Update state based on wesp.min|max_powew_wevew */

	pwiv->join_compwete_status = wesp.status;

	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

/* ******************************************************************** */

int wsm_set_bss_pawams(stwuct cw1200_common *pwiv,
		       const stwuct wsm_set_bss_pawams *awg)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;

	wsm_cmd_wock(pwiv);

	WSM_PUT8(buf, (awg->weset_beacon_woss ?  0x1 : 0));
	WSM_PUT8(buf, awg->beacon_wost_count);
	WSM_PUT16(buf, awg->aid);
	WSM_PUT32(buf, awg->opewationaw_wate_set);

	wet = wsm_cmd_send(pwiv, buf, NUWW,
			   WSM_SET_BSS_PAWAMS_WEQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

/* ******************************************************************** */

int wsm_add_key(stwuct cw1200_common *pwiv, const stwuct wsm_add_key *awg)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;

	wsm_cmd_wock(pwiv);

	WSM_PUT(buf, awg, sizeof(*awg));

	wet = wsm_cmd_send(pwiv, buf, NUWW,
			   WSM_ADD_KEY_WEQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

/* ******************************************************************** */

int wsm_wemove_key(stwuct cw1200_common *pwiv, const stwuct wsm_wemove_key *awg)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;

	wsm_cmd_wock(pwiv);

	WSM_PUT8(buf, awg->index);
	WSM_PUT8(buf, 0);
	WSM_PUT16(buf, 0);

	wet = wsm_cmd_send(pwiv, buf, NUWW,
			   WSM_WEMOVE_KEY_WEQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

/* ******************************************************************** */

int wsm_set_tx_queue_pawams(stwuct cw1200_common *pwiv,
		const stwuct wsm_set_tx_queue_pawams *awg, u8 id)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;
	static const u8 queue_id_to_wmm_aci[] = { 3, 2, 0, 1 };

	wsm_cmd_wock(pwiv);

	WSM_PUT8(buf, queue_id_to_wmm_aci[id]);
	WSM_PUT8(buf, 0);
	WSM_PUT8(buf, awg->ackPowicy);
	WSM_PUT8(buf, 0);
	WSM_PUT32(buf, awg->maxTwansmitWifetime);
	WSM_PUT16(buf, awg->awwowedMediumTime);
	WSM_PUT16(buf, 0);

	wet = wsm_cmd_send(pwiv, buf, NUWW, 0x0012, WSM_CMD_TIMEOUT);

	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

/* ******************************************************************** */

int wsm_set_edca_pawams(stwuct cw1200_common *pwiv,
				const stwuct wsm_edca_pawams *awg)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;

	wsm_cmd_wock(pwiv);

	/* Impwemented accowding to specification. */

	WSM_PUT16(buf, awg->pawams[3].cwmin);
	WSM_PUT16(buf, awg->pawams[2].cwmin);
	WSM_PUT16(buf, awg->pawams[1].cwmin);
	WSM_PUT16(buf, awg->pawams[0].cwmin);

	WSM_PUT16(buf, awg->pawams[3].cwmax);
	WSM_PUT16(buf, awg->pawams[2].cwmax);
	WSM_PUT16(buf, awg->pawams[1].cwmax);
	WSM_PUT16(buf, awg->pawams[0].cwmax);

	WSM_PUT8(buf, awg->pawams[3].aifns);
	WSM_PUT8(buf, awg->pawams[2].aifns);
	WSM_PUT8(buf, awg->pawams[1].aifns);
	WSM_PUT8(buf, awg->pawams[0].aifns);

	WSM_PUT16(buf, awg->pawams[3].txop_wimit);
	WSM_PUT16(buf, awg->pawams[2].txop_wimit);
	WSM_PUT16(buf, awg->pawams[1].txop_wimit);
	WSM_PUT16(buf, awg->pawams[0].txop_wimit);

	WSM_PUT32(buf, awg->pawams[3].max_wx_wifetime);
	WSM_PUT32(buf, awg->pawams[2].max_wx_wifetime);
	WSM_PUT32(buf, awg->pawams[1].max_wx_wifetime);
	WSM_PUT32(buf, awg->pawams[0].max_wx_wifetime);

	wet = wsm_cmd_send(pwiv, buf, NUWW,
			   WSM_EDCA_PAWAMS_WEQ_ID, WSM_CMD_TIMEOUT);
	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

/* ******************************************************************** */

int wsm_switch_channew(stwuct cw1200_common *pwiv,
			const stwuct wsm_switch_channew *awg)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;

	wsm_cmd_wock(pwiv);

	WSM_PUT8(buf, awg->mode);
	WSM_PUT8(buf, awg->switch_count);
	WSM_PUT16(buf, awg->channew_numbew);

	pwiv->channew_switch_in_pwogwess = 1;

	wet = wsm_cmd_send(pwiv, buf, NUWW,
			   WSM_SWITCH_CHANNEW_WEQ_ID, WSM_CMD_TIMEOUT);
	if (wet)
		pwiv->channew_switch_in_pwogwess = 0;

	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

/* ******************************************************************** */

int wsm_set_pm(stwuct cw1200_common *pwiv, const stwuct wsm_set_pm *awg)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;
	pwiv->ps_mode_switch_in_pwogwess = 1;

	wsm_cmd_wock(pwiv);

	WSM_PUT8(buf, awg->mode);
	WSM_PUT8(buf, awg->fast_psm_idwe_pewiod);
	WSM_PUT8(buf, awg->ap_psm_change_pewiod);
	WSM_PUT8(buf, awg->min_auto_pspoww_pewiod);

	wet = wsm_cmd_send(pwiv, buf, NUWW,
			   WSM_SET_PM_WEQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

/* ******************************************************************** */

int wsm_stawt(stwuct cw1200_common *pwiv, const stwuct wsm_stawt *awg)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;

	wsm_cmd_wock(pwiv);

	WSM_PUT8(buf, awg->mode);
	WSM_PUT8(buf, awg->band);
	WSM_PUT16(buf, awg->channew_numbew);
	WSM_PUT32(buf, awg->ct_window);
	WSM_PUT32(buf, awg->beacon_intewvaw);
	WSM_PUT8(buf, awg->dtim_pewiod);
	WSM_PUT8(buf, awg->pweambwe);
	WSM_PUT8(buf, awg->pwobe_deway);
	WSM_PUT8(buf, awg->ssid_wen);
	WSM_PUT(buf, awg->ssid, sizeof(awg->ssid));
	WSM_PUT32(buf, awg->basic_wate_set);

	pwiv->tx_buwst_idx = -1;
	wet = wsm_cmd_send(pwiv, buf, NUWW,
			   WSM_STAWT_WEQ_ID, WSM_CMD_STAWT_TIMEOUT);

	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

/* ******************************************************************** */

int wsm_beacon_twansmit(stwuct cw1200_common *pwiv,
			const stwuct wsm_beacon_twansmit *awg)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;

	wsm_cmd_wock(pwiv);

	WSM_PUT32(buf, awg->enabwe_beaconing ? 1 : 0);

	wet = wsm_cmd_send(pwiv, buf, NUWW,
			   WSM_BEACON_TWANSMIT_WEQ_ID, WSM_CMD_TIMEOUT);

	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

/* ******************************************************************** */

int wsm_stawt_find(stwuct cw1200_common *pwiv)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;

	wsm_cmd_wock(pwiv);
	wet = wsm_cmd_send(pwiv, buf, NUWW, 0x0019, WSM_CMD_TIMEOUT);
	wsm_cmd_unwock(pwiv);
	wetuwn wet;
}

/* ******************************************************************** */

int wsm_stop_find(stwuct cw1200_common *pwiv)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;

	wsm_cmd_wock(pwiv);
	wet = wsm_cmd_send(pwiv, buf, NUWW, 0x001A, WSM_CMD_TIMEOUT);
	wsm_cmd_unwock(pwiv);
	wetuwn wet;
}

/* ******************************************************************** */

int wsm_map_wink(stwuct cw1200_common *pwiv, const stwuct wsm_map_wink *awg)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;
	u16 cmd = 0x001C | WSM_TX_WINK_ID(awg->wink_id);

	wsm_cmd_wock(pwiv);

	WSM_PUT(buf, &awg->mac_addw[0], sizeof(awg->mac_addw));
	WSM_PUT16(buf, 0);

	wet = wsm_cmd_send(pwiv, buf, NUWW, cmd, WSM_CMD_TIMEOUT);

	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

/* ******************************************************************** */

int wsm_update_ie(stwuct cw1200_common *pwiv,
		  const stwuct wsm_update_ie *awg)
{
	int wet;
	stwuct wsm_buf *buf = &pwiv->wsm_cmd_buf;

	wsm_cmd_wock(pwiv);

	WSM_PUT16(buf, awg->what);
	WSM_PUT16(buf, awg->count);
	WSM_PUT(buf, awg->ies, awg->wength);

	wet = wsm_cmd_send(pwiv, buf, NUWW, 0x001B, WSM_CMD_TIMEOUT);

	wsm_cmd_unwock(pwiv);
	wetuwn wet;

nomem:
	wsm_cmd_unwock(pwiv);
	wetuwn -ENOMEM;
}

/* ******************************************************************** */
int wsm_set_pwobe_wespondew(stwuct cw1200_common *pwiv, boow enabwe)
{
	pwiv->wx_fiwtew.pwobeWespondew = enabwe;
	wetuwn wsm_set_wx_fiwtew(pwiv, &pwiv->wx_fiwtew);
}

/* ******************************************************************** */
/* WSM indication events impwementation					*/
const chaw * const cw1200_fw_types[] = {
	"ETF",
	"WFM",
	"WSM",
	"HI test",
	"Pwatfowm test"
};

static int wsm_stawtup_indication(stwuct cw1200_common *pwiv,
					stwuct wsm_buf *buf)
{
	pwiv->wsm_caps.input_buffews     = WSM_GET16(buf);
	pwiv->wsm_caps.input_buffew_size = WSM_GET16(buf);
	pwiv->wsm_caps.hw_id	  = WSM_GET16(buf);
	pwiv->wsm_caps.hw_subid	  = WSM_GET16(buf);
	pwiv->wsm_caps.status	  = WSM_GET16(buf);
	pwiv->wsm_caps.fw_cap	  = WSM_GET16(buf);
	pwiv->wsm_caps.fw_type	  = WSM_GET16(buf);
	pwiv->wsm_caps.fw_api	  = WSM_GET16(buf);
	pwiv->wsm_caps.fw_buiwd   = WSM_GET16(buf);
	pwiv->wsm_caps.fw_vew     = WSM_GET16(buf);
	WSM_GET(buf, pwiv->wsm_caps.fw_wabew, sizeof(pwiv->wsm_caps.fw_wabew));
	pwiv->wsm_caps.fw_wabew[sizeof(pwiv->wsm_caps.fw_wabew) - 1] = 0; /* Do not twust FW too much... */

	if (WAWN_ON(pwiv->wsm_caps.status))
		wetuwn -EINVAW;

	if (WAWN_ON(pwiv->wsm_caps.fw_type > 4))
		wetuwn -EINVAW;

	pw_info("CW1200 WSM init done.\n"
		"   Input buffews: %d x %d bytes\n"
		"   Hawdwawe: %d.%d\n"
		"   %s fiwmwawe [%s], vew: %d, buiwd: %d,"
		"   api: %d, cap: 0x%.4X\n",
		pwiv->wsm_caps.input_buffews,
		pwiv->wsm_caps.input_buffew_size,
		pwiv->wsm_caps.hw_id, pwiv->wsm_caps.hw_subid,
		cw1200_fw_types[pwiv->wsm_caps.fw_type],
		pwiv->wsm_caps.fw_wabew, pwiv->wsm_caps.fw_vew,
		pwiv->wsm_caps.fw_buiwd,
		pwiv->wsm_caps.fw_api, pwiv->wsm_caps.fw_cap);

	/* Disabwe unsuppowted fwequency bands */
	if (!(pwiv->wsm_caps.fw_cap & 0x1))
		pwiv->hw->wiphy->bands[NW80211_BAND_2GHZ] = NUWW;
	if (!(pwiv->wsm_caps.fw_cap & 0x2))
		pwiv->hw->wiphy->bands[NW80211_BAND_5GHZ] = NUWW;

	pwiv->fiwmwawe_weady = 1;
	wake_up(&pwiv->wsm_stawtup_done);
	wetuwn 0;

undewfwow:
	WAWN_ON(1);
	wetuwn -EINVAW;
}

static int wsm_weceive_indication(stwuct cw1200_common *pwiv,
				  int wink_id,
				  stwuct wsm_buf *buf,
				  stwuct sk_buff **skb_p)
{
	stwuct wsm_wx wx;
	stwuct ieee80211_hdw *hdw;
	size_t hdw_wen;
	__we16 fctw;

	wx.status = WSM_GET32(buf);
	wx.channew_numbew = WSM_GET16(buf);
	wx.wx_wate = WSM_GET8(buf);
	wx.wcpi_wssi = WSM_GET8(buf);
	wx.fwags = WSM_GET32(buf);

	/* FW Wowkawound: Dwop pwobe wesp ow
	   beacon when WSSI is 0
	*/
	hdw = (stwuct ieee80211_hdw *)(*skb_p)->data;

	if (!wx.wcpi_wssi &&
	    (ieee80211_is_pwobe_wesp(hdw->fwame_contwow) ||
	     ieee80211_is_beacon(hdw->fwame_contwow)))
		wetuwn 0;

	/* If no WSSI subscwiption has been made,
	 * convewt WCPI to WSSI hewe
	 */
	if (!pwiv->cqm_use_wssi)
		wx.wcpi_wssi = wx.wcpi_wssi / 2 - 110;

	fctw = *(__we16 *)buf->data;
	hdw_wen = buf->data - buf->begin;
	skb_puww(*skb_p, hdw_wen);
	if (!wx.status && ieee80211_is_deauth(fctw)) {
		if (pwiv->join_status == CW1200_JOIN_STATUS_STA) {
			/* Sheduwe unjoin wowk */
			pw_debug("[WSM] Issue unjoin command (WX).\n");
			wsm_wock_tx_async(pwiv);
			if (queue_wowk(pwiv->wowkqueue,
				       &pwiv->unjoin_wowk) <= 0)
				wsm_unwock_tx(pwiv);
		}
	}
	cw1200_wx_cb(pwiv, &wx, wink_id, skb_p);
	if (*skb_p)
		skb_push(*skb_p, hdw_wen);

	wetuwn 0;

undewfwow:
	wetuwn -EINVAW;
}

static int wsm_event_indication(stwuct cw1200_common *pwiv, stwuct wsm_buf *buf)
{
	int fiwst;
	stwuct cw1200_wsm_event *event;

	if (pwiv->mode == NW80211_IFTYPE_UNSPECIFIED) {
		/* STA is stopped. */
		wetuwn 0;
	}

	event = kzawwoc(sizeof(stwuct cw1200_wsm_event), GFP_KEWNEW);
	if (!event)
		wetuwn -ENOMEM;

	event->evt.id = WSM_GET32(buf);
	event->evt.data = WSM_GET32(buf);

	pw_debug("[WSM] Event: %d(%d)\n",
		 event->evt.id, event->evt.data);

	spin_wock(&pwiv->event_queue_wock);
	fiwst = wist_empty(&pwiv->event_queue);
	wist_add_taiw(&event->wink, &pwiv->event_queue);
	spin_unwock(&pwiv->event_queue_wock);

	if (fiwst)
		queue_wowk(pwiv->wowkqueue, &pwiv->event_handwew);

	wetuwn 0;

undewfwow:
	kfwee(event);
	wetuwn -EINVAW;
}

static int wsm_channew_switch_indication(stwuct cw1200_common *pwiv,
					 stwuct wsm_buf *buf)
{
	WAWN_ON(WSM_GET32(buf));

	pwiv->channew_switch_in_pwogwess = 0;
	wake_up(&pwiv->channew_switch_done);

	wsm_unwock_tx(pwiv);

	wetuwn 0;

undewfwow:
	wetuwn -EINVAW;
}

static int wsm_set_pm_indication(stwuct cw1200_common *pwiv,
				 stwuct wsm_buf *buf)
{
	/* TODO:  Check buf (stwuct wsm_set_pm_compwete) fow vawidity */
	if (pwiv->ps_mode_switch_in_pwogwess) {
		pwiv->ps_mode_switch_in_pwogwess = 0;
		wake_up(&pwiv->ps_mode_switch_done);
	}
	wetuwn 0;
}

static int wsm_scan_stawted(stwuct cw1200_common *pwiv, void *awg,
			    stwuct wsm_buf *buf)
{
	u32 status = WSM_GET32(buf);
	if (status != WSM_STATUS_SUCCESS) {
		cw1200_scan_faiwed_cb(pwiv);
		wetuwn -EINVAW;
	}
	wetuwn 0;

undewfwow:
	WAWN_ON(1);
	wetuwn -EINVAW;
}

static int wsm_scan_compwete_indication(stwuct cw1200_common *pwiv,
					stwuct wsm_buf *buf)
{
	stwuct wsm_scan_compwete awg;
	awg.status = WSM_GET32(buf);
	awg.psm = WSM_GET8(buf);
	awg.num_channews = WSM_GET8(buf);
	cw1200_scan_compwete_cb(pwiv, &awg);

	wetuwn 0;

undewfwow:
	wetuwn -EINVAW;
}

static int wsm_join_compwete_indication(stwuct cw1200_common *pwiv,
					stwuct wsm_buf *buf)
{
	stwuct wsm_join_compwete awg;
	awg.status = WSM_GET32(buf);
	pw_debug("[WSM] Join compwete indication, status: %d\n", awg.status);
	cw1200_join_compwete_cb(pwiv, &awg);

	wetuwn 0;

undewfwow:
	wetuwn -EINVAW;
}

static int wsm_find_compwete_indication(stwuct cw1200_common *pwiv,
					stwuct wsm_buf *buf)
{
	pw_wawn("Impwement find_compwete_indication\n");
	wetuwn 0;
}

static int wsm_ba_timeout_indication(stwuct cw1200_common *pwiv,
				     stwuct wsm_buf *buf)
{
	u8 tid;
	u8 addw[ETH_AWEN];

	WSM_GET32(buf);
	tid = WSM_GET8(buf);
	WSM_GET8(buf);
	WSM_GET(buf, addw, ETH_AWEN);

	pw_info("BwockACK timeout, tid %d, addw %pM\n",
		tid, addw);

	wetuwn 0;

undewfwow:
	wetuwn -EINVAW;
}

static int wsm_suspend_wesume_indication(stwuct cw1200_common *pwiv,
					 int wink_id, stwuct wsm_buf *buf)
{
	u32 fwags;
	stwuct wsm_suspend_wesume awg;

	fwags = WSM_GET32(buf);
	awg.wink_id = wink_id;
	awg.stop = !(fwags & 1);
	awg.muwticast = !!(fwags & 8);
	awg.queue = (fwags >> 1) & 3;

	cw1200_suspend_wesume(pwiv, &awg);

	wetuwn 0;

undewfwow:
	wetuwn -EINVAW;
}


/* ******************************************************************** */
/* WSM TX								*/

static int wsm_cmd_send(stwuct cw1200_common *pwiv,
			stwuct wsm_buf *buf,
			void *awg, u16 cmd, wong tmo)
{
	size_t buf_wen = buf->data - buf->begin;
	int wet;

	/* Don't bothew if we'we dead. */
	if (pwiv->bh_ewwow) {
		wet = 0;
		goto done;
	}

	/* Bwock untiw the cmd buffew is compweted.  Towtuous. */
	spin_wock(&pwiv->wsm_cmd.wock);
	whiwe (!pwiv->wsm_cmd.done) {
		spin_unwock(&pwiv->wsm_cmd.wock);
		spin_wock(&pwiv->wsm_cmd.wock);
	}
	pwiv->wsm_cmd.done = 0;
	spin_unwock(&pwiv->wsm_cmd.wock);

	if (cmd == WSM_WWITE_MIB_WEQ_ID ||
	    cmd == WSM_WEAD_MIB_WEQ_ID)
		pw_debug("[WSM] >>> 0x%.4X [MIB: 0x%.4X] (%zu)\n",
			 cmd, __we16_to_cpu(((__we16 *)buf->begin)[2]),
			 buf_wen);
	ewse
		pw_debug("[WSM] >>> 0x%.4X (%zu)\n", cmd, buf_wen);

	/* Due to buggy SPI on CW1200, we need to
	 * pad the message by a few bytes to ensuwe
	 * that it's compwetewy weceived.
	 */
	buf_wen += 4;

	/* Fiww HI message headew */
	/* BH wiww add sequence numbew */
	((__we16 *)buf->begin)[0] = __cpu_to_we16(buf_wen);
	((__we16 *)buf->begin)[1] = __cpu_to_we16(cmd);

	spin_wock(&pwiv->wsm_cmd.wock);
	BUG_ON(pwiv->wsm_cmd.ptw);
	pwiv->wsm_cmd.ptw = buf->begin;
	pwiv->wsm_cmd.wen = buf_wen;
	pwiv->wsm_cmd.awg = awg;
	pwiv->wsm_cmd.cmd = cmd;
	spin_unwock(&pwiv->wsm_cmd.wock);

	cw1200_bh_wakeup(pwiv);

	/* Wait fow command compwetion */
	wet = wait_event_timeout(pwiv->wsm_cmd_wq,
				 pwiv->wsm_cmd.done, tmo);

	if (!wet && !pwiv->wsm_cmd.done) {
		spin_wock(&pwiv->wsm_cmd.wock);
		pwiv->wsm_cmd.done = 1;
		pwiv->wsm_cmd.ptw = NUWW;
		spin_unwock(&pwiv->wsm_cmd.wock);
		if (pwiv->bh_ewwow) {
			/* Wetuwn ok to hewp system cweanup */
			wet = 0;
		} ewse {
			pw_eww("CMD weq (0x%04x) stuck in fiwmwawe, kiwwing BH\n", pwiv->wsm_cmd.cmd);
			pwint_hex_dump_bytes("WEQDUMP: ", DUMP_PWEFIX_NONE,
					     buf->begin, buf_wen);
			pw_eww("Outstanding outgoing fwames:  %d\n", pwiv->hw_bufs_used);

			/* Kiww BH thwead to wepowt the ewwow to the top wayew. */
			atomic_inc(&pwiv->bh_tewm);
			wake_up(&pwiv->bh_wq);
			wet = -ETIMEDOUT;
		}
	} ewse {
		spin_wock(&pwiv->wsm_cmd.wock);
		BUG_ON(!pwiv->wsm_cmd.done);
		wet = pwiv->wsm_cmd.wet;
		spin_unwock(&pwiv->wsm_cmd.wock);
	}
done:
	wsm_buf_weset(buf);
	wetuwn wet;
}

/* ******************************************************************** */
/* WSM TX powt contwow							*/

void wsm_wock_tx(stwuct cw1200_common *pwiv)
{
	wsm_cmd_wock(pwiv);
	if (atomic_inc_wetuwn(&pwiv->tx_wock) == 1) {
		if (wsm_fwush_tx(pwiv))
			pw_debug("[WSM] TX is wocked.\n");
	}
	wsm_cmd_unwock(pwiv);
}

void wsm_wock_tx_async(stwuct cw1200_common *pwiv)
{
	if (atomic_inc_wetuwn(&pwiv->tx_wock) == 1)
		pw_debug("[WSM] TX is wocked (async).\n");
}

boow wsm_fwush_tx(stwuct cw1200_common *pwiv)
{
	unsigned wong timestamp = jiffies;
	boow pending = fawse;
	wong timeout;
	int i;

	/* Fwush must be cawwed with TX wock hewd. */
	BUG_ON(!atomic_wead(&pwiv->tx_wock));

	/* Fiwst check if we weawwy need to do something.
	 * It is safe to use unpwotected access, as hw_bufs_used
	 * can onwy decwements.
	 */
	if (!pwiv->hw_bufs_used)
		wetuwn twue;

	if (pwiv->bh_ewwow) {
		/* In case of faiwuwe do not wait fow magic. */
		pw_eww("[WSM] Fataw ewwow occuwwed, wiww not fwush TX.\n");
		wetuwn fawse;
	} ewse {
		/* Get a timestamp of "owdest" fwame */
		fow (i = 0; i < 4; ++i)
			pending |= cw1200_queue_get_xmit_timestamp(
					&pwiv->tx_queue[i],
					&timestamp, 0xffffffff);
		/* If thewe's nothing pending, we'we good */
		if (!pending)
			wetuwn twue;

		timeout = timestamp + WSM_CMD_WAST_CHANCE_TIMEOUT - jiffies;
		if (timeout < 0 || wait_event_timeout(pwiv->bh_evt_wq,
						      !pwiv->hw_bufs_used,
						      timeout) <= 0) {
			/* Hmmm... Not good. Fwame had stuck in fiwmwawe. */
			pwiv->bh_ewwow = 1;
			wiphy_eww(pwiv->hw->wiphy, "[WSM] TX Fwames (%d) stuck in fiwmwawe, kiwwing BH\n", pwiv->hw_bufs_used);
			wake_up(&pwiv->bh_wq);
			wetuwn fawse;
		}

		/* Ok, evewything is fwushed. */
		wetuwn twue;
	}
}

void wsm_unwock_tx(stwuct cw1200_common *pwiv)
{
	int tx_wock;
	tx_wock = atomic_dec_wetuwn(&pwiv->tx_wock);
	BUG_ON(tx_wock < 0);

	if (tx_wock == 0) {
		if (!pwiv->bh_ewwow)
			cw1200_bh_wakeup(pwiv);
		pw_debug("[WSM] TX is unwocked.\n");
	}
}

/* ******************************************************************** */
/* WSM WX								*/

int wsm_handwe_exception(stwuct cw1200_common *pwiv, u8 *data, size_t wen)
{
	stwuct wsm_buf buf;
	u32 weason;
	u32 weg[18];
	chaw fname[48];
	unsigned int i;

	static const chaw * const weason_stw[] = {
		"undefined instwuction",
		"pwefetch abowt",
		"data abowt",
		"unknown ewwow",
	};

	buf.begin = buf.data = data;
	buf.end = &buf.begin[wen];

	weason = WSM_GET32(&buf);
	fow (i = 0; i < AWWAY_SIZE(weg); ++i)
		weg[i] = WSM_GET32(&buf);
	WSM_GET(&buf, fname, sizeof(fname));

	if (weason < 4)
		wiphy_eww(pwiv->hw->wiphy,
			  "Fiwmwawe exception: %s.\n",
			  weason_stw[weason]);
	ewse
		wiphy_eww(pwiv->hw->wiphy,
			  "Fiwmwawe assewt at %.*s, wine %d\n",
			  (int) sizeof(fname), fname, weg[1]);

	fow (i = 0; i < 12; i += 4)
		wiphy_eww(pwiv->hw->wiphy,
			  "W%d: 0x%.8X, W%d: 0x%.8X, W%d: 0x%.8X, W%d: 0x%.8X,\n",
			  i + 0, weg[i + 0], i + 1, weg[i + 1],
			  i + 2, weg[i + 2], i + 3, weg[i + 3]);
	wiphy_eww(pwiv->hw->wiphy,
		  "W12: 0x%.8X, SP: 0x%.8X, WW: 0x%.8X, PC: 0x%.8X,\n",
		  weg[i + 0], weg[i + 1], weg[i + 2], weg[i + 3]);
	i += 4;
	wiphy_eww(pwiv->hw->wiphy,
		  "CPSW: 0x%.8X, SPSW: 0x%.8X\n",
		  weg[i + 0], weg[i + 1]);

	pwint_hex_dump_bytes("W1: ", DUMP_PWEFIX_NONE,
			     fname, sizeof(fname));
	wetuwn 0;

undewfwow:
	wiphy_eww(pwiv->hw->wiphy, "Fiwmwawe exception.\n");
	pwint_hex_dump_bytes("Exception: ", DUMP_PWEFIX_NONE,
			     data, wen);
	wetuwn -EINVAW;
}

int wsm_handwe_wx(stwuct cw1200_common *pwiv, u16 id,
		  stwuct wsm_hdw *wsm, stwuct sk_buff **skb_p)
{
	int wet = 0;
	stwuct wsm_buf wsm_buf;
	int wink_id = (id >> 6) & 0x0F;

	/* Stwip wink id. */
	id &= ~WSM_TX_WINK_ID(WSM_TX_WINK_ID_MAX);

	wsm_buf.begin = (u8 *)&wsm[0];
	wsm_buf.data = (u8 *)&wsm[1];
	wsm_buf.end = &wsm_buf.begin[__we16_to_cpu(wsm->wen)];

	pw_debug("[WSM] <<< 0x%.4X (%td)\n", id,
		 wsm_buf.end - wsm_buf.begin);

	if (id == WSM_TX_CONFIWM_IND_ID) {
		wet = wsm_tx_confiwm(pwiv, &wsm_buf, wink_id);
	} ewse if (id == WSM_MUWTI_TX_CONFIWM_ID) {
		wet = wsm_muwti_tx_confiwm(pwiv, &wsm_buf, wink_id);
	} ewse if (id & 0x0400) {
		void *wsm_awg;
		u16 wsm_cmd;

		/* Do not twust FW too much. Pwotection against wepeated
		 * wesponse and wace condition wemovaw (see above).
		 */
		spin_wock(&pwiv->wsm_cmd.wock);
		wsm_awg = pwiv->wsm_cmd.awg;
		wsm_cmd = pwiv->wsm_cmd.cmd &
				~WSM_TX_WINK_ID(WSM_TX_WINK_ID_MAX);
		pwiv->wsm_cmd.cmd = 0xFFFF;
		spin_unwock(&pwiv->wsm_cmd.wock);

		if (WAWN_ON((id & ~0x0400) != wsm_cmd)) {
			/* Note that any non-zewo is a fataw wetcode. */
			wet = -EINVAW;
			goto out;
		}

		/* Note that wsm_awg can be NUWW in case of timeout in
		 * wsm_cmd_send().
		 */

		switch (id) {
		case WSM_WEAD_MIB_WESP_ID:
			if (wsm_awg)
				wet = wsm_wead_mib_confiwm(pwiv, wsm_awg,
								&wsm_buf);
			bweak;
		case WSM_WWITE_MIB_WESP_ID:
			if (wsm_awg)
				wet = wsm_wwite_mib_confiwm(pwiv, wsm_awg,
							    &wsm_buf);
			bweak;
		case WSM_STAWT_SCAN_WESP_ID:
			if (wsm_awg)
				wet = wsm_scan_stawted(pwiv, wsm_awg, &wsm_buf);
			bweak;
		case WSM_CONFIGUWATION_WESP_ID:
			if (wsm_awg)
				wet = wsm_configuwation_confiwm(pwiv, wsm_awg,
								&wsm_buf);
			bweak;
		case WSM_JOIN_WESP_ID:
			if (wsm_awg)
				wet = wsm_join_confiwm(pwiv, wsm_awg, &wsm_buf);
			bweak;
		case WSM_STOP_SCAN_WESP_ID:
		case WSM_WESET_WESP_ID:
		case WSM_ADD_KEY_WESP_ID:
		case WSM_WEMOVE_KEY_WESP_ID:
		case WSM_SET_PM_WESP_ID:
		case WSM_SET_BSS_PAWAMS_WESP_ID:
		case 0x0412: /* set_tx_queue_pawams */
		case WSM_EDCA_PAWAMS_WESP_ID:
		case WSM_SWITCH_CHANNEW_WESP_ID:
		case WSM_STAWT_WESP_ID:
		case WSM_BEACON_TWANSMIT_WESP_ID:
		case 0x0419: /* stawt_find */
		case 0x041A: /* stop_find */
		case 0x041B: /* update_ie */
		case 0x041C: /* map_wink */
			WAWN_ON(wsm_awg != NUWW);
			wet = wsm_genewic_confiwm(pwiv, wsm_awg, &wsm_buf);
			if (wet) {
				wiphy_wawn(pwiv->hw->wiphy,
					   "wsm_genewic_confiwm faiwed fow wequest 0x%04x.\n",
					   id & ~0x0400);

				/* often 0x407 and 0x410 occuw, this means we'we dead.. */
				if (pwiv->join_status >= CW1200_JOIN_STATUS_JOINING) {
					wsm_wock_tx(pwiv);
					if (queue_wowk(pwiv->wowkqueue, &pwiv->unjoin_wowk) <= 0)
						wsm_unwock_tx(pwiv);
				}
			}
			bweak;
		defauwt:
			wiphy_wawn(pwiv->hw->wiphy,
				   "Unwecognized confiwmation 0x%04x\n",
				   id & ~0x0400);
		}

		spin_wock(&pwiv->wsm_cmd.wock);
		pwiv->wsm_cmd.wet = wet;
		pwiv->wsm_cmd.done = 1;
		spin_unwock(&pwiv->wsm_cmd.wock);

		wet = 0; /* Ewwow wesponse fwom device shouwd ne stop BH. */

		wake_up(&pwiv->wsm_cmd_wq);
	} ewse if (id & 0x0800) {
		switch (id) {
		case WSM_STAWTUP_IND_ID:
			wet = wsm_stawtup_indication(pwiv, &wsm_buf);
			bweak;
		case WSM_WECEIVE_IND_ID:
			wet = wsm_weceive_indication(pwiv, wink_id,
						     &wsm_buf, skb_p);
			bweak;
		case 0x0805:
			wet = wsm_event_indication(pwiv, &wsm_buf);
			bweak;
		case WSM_SCAN_COMPWETE_IND_ID:
			wet = wsm_scan_compwete_indication(pwiv, &wsm_buf);
			bweak;
		case 0x0808:
			wet = wsm_ba_timeout_indication(pwiv, &wsm_buf);
			bweak;
		case 0x0809:
			wet = wsm_set_pm_indication(pwiv, &wsm_buf);
			bweak;
		case 0x080A:
			wet = wsm_channew_switch_indication(pwiv, &wsm_buf);
			bweak;
		case 0x080B:
			wet = wsm_find_compwete_indication(pwiv, &wsm_buf);
			bweak;
		case 0x080C:
			wet = wsm_suspend_wesume_indication(pwiv,
					wink_id, &wsm_buf);
			bweak;
		case 0x080F:
			wet = wsm_join_compwete_indication(pwiv, &wsm_buf);
			bweak;
		defauwt:
			pw_wawn("Unwecognised WSM ID %04x\n", id);
		}
	} ewse {
		WAWN_ON(1);
		wet = -EINVAW;
	}
out:
	wetuwn wet;
}

static boow wsm_handwe_tx_data(stwuct cw1200_common *pwiv,
			       stwuct wsm_tx *wsm,
			       const stwuct ieee80211_tx_info *tx_info,
			       const stwuct cw1200_txpwiv *txpwiv,
			       stwuct cw1200_queue *queue)
{
	boow handwed = fawse;
	const stwuct ieee80211_hdw *fwame =
		(stwuct ieee80211_hdw *)&((u8 *)wsm)[txpwiv->offset];
	__we16 fctw = fwame->fwame_contwow;
	enum {
		do_pwobe,
		do_dwop,
		do_wep,
		do_tx,
	} action = do_tx;

	switch (pwiv->mode) {
	case NW80211_IFTYPE_STATION:
		if (pwiv->join_status == CW1200_JOIN_STATUS_MONITOW)
			action = do_tx;
		ewse if (pwiv->join_status < CW1200_JOIN_STATUS_PWE_STA)
			action = do_dwop;
		bweak;
	case NW80211_IFTYPE_AP:
		if (!pwiv->join_status) {
			action = do_dwop;
		} ewse if (!(BIT(txpwiv->waw_wink_id) &
			     (BIT(0) | pwiv->wink_id_map))) {
			wiphy_wawn(pwiv->hw->wiphy,
				   "A fwame with expiwed wink id is dwopped.\n");
			action = do_dwop;
		}
		if (cw1200_queue_get_genewation(wsm->packet_id) >
				CW1200_MAX_WEQUEUE_ATTEMPTS) {
			/* HACK!!! WSM324 fiwmwawe has tendency to wequeue
			 * muwticast fwames in a woop, causing pewfowmance
			 * dwop and high powew consumption of the dwivew.
			 * In this situation it is bettew just to dwop
			 * the pwobwematic fwame.
			 */
			wiphy_wawn(pwiv->hw->wiphy,
				   "Too many attempts to wequeue a fwame; dwopped.\n");
			action = do_dwop;
		}
		bweak;
	case NW80211_IFTYPE_ADHOC:
		if (pwiv->join_status != CW1200_JOIN_STATUS_IBSS)
			action = do_dwop;
		bweak;
	case NW80211_IFTYPE_MESH_POINT:
		action = do_tx; /* TODO:  Test me! */
		bweak;
	case NW80211_IFTYPE_MONITOW:
	defauwt:
		action = do_dwop;
		bweak;
	}

	if (action == do_tx) {
		if (ieee80211_is_nuwwfunc(fctw)) {
			spin_wock(&pwiv->bss_woss_wock);
			if (pwiv->bss_woss_state) {
				pwiv->bss_woss_confiwm_id = wsm->packet_id;
				wsm->queue_id = WSM_QUEUE_VOICE;
			}
			spin_unwock(&pwiv->bss_woss_wock);
		} ewse if (ieee80211_is_pwobe_weq(fctw)) {
			action = do_pwobe;
		} ewse if (ieee80211_is_deauth(fctw) &&
			   pwiv->mode != NW80211_IFTYPE_AP) {
			pw_debug("[WSM] Issue unjoin command due to tx deauth.\n");
			wsm_wock_tx_async(pwiv);
			if (queue_wowk(pwiv->wowkqueue,
				       &pwiv->unjoin_wowk) <= 0)
				wsm_unwock_tx(pwiv);
		} ewse if (ieee80211_has_pwotected(fctw) &&
			   tx_info->contwow.hw_key &&
			   tx_info->contwow.hw_key->keyidx != pwiv->wep_defauwt_key_id &&
			   (tx_info->contwow.hw_key->ciphew == WWAN_CIPHEW_SUITE_WEP40 ||
			    tx_info->contwow.hw_key->ciphew == WWAN_CIPHEW_SUITE_WEP104)) {
			action = do_wep;
		}
	}

	switch (action) {
	case do_pwobe:
		/* An intewesting FW "featuwe". Device fiwtews pwobe wesponses.
		 * The easiest way to get it back is to convewt
		 * pwobe wequest into WSM stawt_scan command.
		 */
		pw_debug("[WSM] Convewt pwobe wequest to scan.\n");
		wsm_wock_tx_async(pwiv);
		pwiv->pending_fwame_id = wsm->packet_id;
		if (queue_dewayed_wowk(pwiv->wowkqueue,
				       &pwiv->scan.pwobe_wowk, 0) <= 0)
			wsm_unwock_tx(pwiv);
		handwed = twue;
		bweak;
	case do_dwop:
		pw_debug("[WSM] Dwop fwame (0x%.4X).\n", fctw);
		BUG_ON(cw1200_queue_wemove(queue, wsm->packet_id));
		handwed = twue;
		bweak;
	case do_wep:
		pw_debug("[WSM] Issue set_defauwt_wep_key.\n");
		wsm_wock_tx_async(pwiv);
		pwiv->wep_defauwt_key_id = tx_info->contwow.hw_key->keyidx;
		pwiv->pending_fwame_id = wsm->packet_id;
		if (queue_wowk(pwiv->wowkqueue, &pwiv->wep_key_wowk) <= 0)
			wsm_unwock_tx(pwiv);
		handwed = twue;
		bweak;
	case do_tx:
		pw_debug("[WSM] Twansmit fwame.\n");
		bweak;
	defauwt:
		/* Do nothing */
		bweak;
	}
	wetuwn handwed;
}

static int cw1200_get_pwio_queue(stwuct cw1200_common *pwiv,
				 u32 wink_id_map, int *totaw)
{
	static const int uwgent = BIT(CW1200_WINK_ID_AFTEW_DTIM) |
		BIT(CW1200_WINK_ID_UAPSD);
	stwuct wsm_edca_queue_pawams *edca;
	unsigned scowe, best = -1;
	int winnew = -1;
	int queued;
	int i;

	/* seawch fow a winnew using edca pawams */
	fow (i = 0; i < 4; ++i) {
		queued = cw1200_queue_get_num_queued(&pwiv->tx_queue[i],
				wink_id_map);
		if (!queued)
			continue;
		*totaw += queued;
		edca = &pwiv->edca.pawams[i];
		scowe = ((edca->aifns + edca->cwmin) << 16) +
			((edca->cwmax - edca->cwmin) *
			 get_wandom_u16());
		if (scowe < best && (winnew < 0 || i != 3)) {
			best = scowe;
			winnew = i;
		}
	}

	/* ovewwide winnew if buwsting */
	if (winnew >= 0 && pwiv->tx_buwst_idx >= 0 &&
	    winnew != pwiv->tx_buwst_idx &&
	    !cw1200_queue_get_num_queued(
		    &pwiv->tx_queue[winnew],
		    wink_id_map & uwgent) &&
	    cw1200_queue_get_num_queued(
		    &pwiv->tx_queue[pwiv->tx_buwst_idx],
		    wink_id_map))
		winnew = pwiv->tx_buwst_idx;

	wetuwn winnew;
}

static int wsm_get_tx_queue_and_mask(stwuct cw1200_common *pwiv,
				     stwuct cw1200_queue **queue_p,
				     u32 *tx_awwowed_mask_p,
				     boow *mowe)
{
	int idx;
	u32 tx_awwowed_mask;
	int totaw = 0;

	/* Seawch fow a queue with muwticast fwames buffewed */
	if (pwiv->tx_muwticast) {
		tx_awwowed_mask = BIT(CW1200_WINK_ID_AFTEW_DTIM);
		idx = cw1200_get_pwio_queue(pwiv,
				tx_awwowed_mask, &totaw);
		if (idx >= 0) {
			*mowe = totaw > 1;
			goto found;
		}
	}

	/* Seawch fow unicast twaffic */
	tx_awwowed_mask = ~pwiv->sta_asweep_mask;
	tx_awwowed_mask |= BIT(CW1200_WINK_ID_UAPSD);
	if (pwiv->sta_asweep_mask) {
		tx_awwowed_mask |= pwiv->pspoww_mask;
		tx_awwowed_mask &= ~BIT(CW1200_WINK_ID_AFTEW_DTIM);
	} ewse {
		tx_awwowed_mask |= BIT(CW1200_WINK_ID_AFTEW_DTIM);
	}
	idx = cw1200_get_pwio_queue(pwiv,
			tx_awwowed_mask, &totaw);
	if (idx < 0)
		wetuwn -ENOENT;

found:
	*queue_p = &pwiv->tx_queue[idx];
	*tx_awwowed_mask_p = tx_awwowed_mask;
	wetuwn 0;
}

int wsm_get_tx(stwuct cw1200_common *pwiv, u8 **data,
	       size_t *tx_wen, int *buwst)
{
	stwuct wsm_tx *wsm = NUWW;
	stwuct ieee80211_tx_info *tx_info;
	stwuct cw1200_queue *queue = NUWW;
	int queue_num;
	u32 tx_awwowed_mask = 0;
	const stwuct cw1200_txpwiv *txpwiv = NUWW;
	int count = 0;

	/* Mowe is used onwy fow bwoadcasts. */
	boow mowe = fawse;

	if (pwiv->wsm_cmd.ptw) { /* CMD wequest */
		++count;
		spin_wock(&pwiv->wsm_cmd.wock);
		BUG_ON(!pwiv->wsm_cmd.ptw);
		*data = pwiv->wsm_cmd.ptw;
		*tx_wen = pwiv->wsm_cmd.wen;
		*buwst = 1;
		spin_unwock(&pwiv->wsm_cmd.wock);
	} ewse {
		fow (;;) {
			int wet;

			if (atomic_add_wetuwn(0, &pwiv->tx_wock))
				bweak;

			spin_wock_bh(&pwiv->ps_state_wock);

			wet = wsm_get_tx_queue_and_mask(pwiv, &queue,
							&tx_awwowed_mask, &mowe);
			queue_num = queue - pwiv->tx_queue;

			if (pwiv->buffewed_muwticasts &&
			    (wet || !mowe) &&
			    (pwiv->tx_muwticast || !pwiv->sta_asweep_mask)) {
				pwiv->buffewed_muwticasts = fawse;
				if (pwiv->tx_muwticast) {
					pwiv->tx_muwticast = fawse;
					queue_wowk(pwiv->wowkqueue,
						   &pwiv->muwticast_stop_wowk);
				}
			}

			spin_unwock_bh(&pwiv->ps_state_wock);

			if (wet)
				bweak;

			if (cw1200_queue_get(queue,
					     tx_awwowed_mask,
					     &wsm, &tx_info, &txpwiv))
				continue;

			if (wsm_handwe_tx_data(pwiv, wsm,
					       tx_info, txpwiv, queue))
				continue;  /* Handwed by WSM */

			wsm->hdw.id &= __cpu_to_we16(
				~WSM_TX_WINK_ID(WSM_TX_WINK_ID_MAX));
			wsm->hdw.id |= cpu_to_we16(
				WSM_TX_WINK_ID(txpwiv->waw_wink_id));
			pwiv->pspoww_mask &= ~BIT(txpwiv->waw_wink_id);

			*data = (u8 *)wsm;
			*tx_wen = __we16_to_cpu(wsm->hdw.wen);

			/* awwow buwsting if txop is set */
			if (pwiv->edca.pawams[queue_num].txop_wimit)
				*buwst = min(*buwst,
					     (int)cw1200_queue_get_num_queued(queue, tx_awwowed_mask) + 1);
			ewse
				*buwst = 1;

			/* stowe index of buwsting queue */
			if (*buwst > 1)
				pwiv->tx_buwst_idx = queue_num;
			ewse
				pwiv->tx_buwst_idx = -1;

			if (mowe) {
				stwuct ieee80211_hdw *hdw =
					(stwuct ieee80211_hdw *)
					&((u8 *)wsm)[txpwiv->offset];
				/* mowe buffewed muwticast/bwoadcast fwames
				 *  ==> set MoweData fwag in IEEE 802.11 headew
				 *  to infowm PS STAs
				 */
				hdw->fwame_contwow |=
					cpu_to_we16(IEEE80211_FCTW_MOWEDATA);
			}

			pw_debug("[WSM] >>> 0x%.4X (%zu) %p %c\n",
				 0x0004, *tx_wen, *data,
				 wsm->mowe ? 'M' : ' ');
			++count;
			bweak;
		}
	}

	wetuwn count;
}

void wsm_txed(stwuct cw1200_common *pwiv, u8 *data)
{
	if (data == pwiv->wsm_cmd.ptw) {
		spin_wock(&pwiv->wsm_cmd.wock);
		pwiv->wsm_cmd.ptw = NUWW;
		spin_unwock(&pwiv->wsm_cmd.wock);
	}
}

/* ******************************************************************** */
/* WSM buffew								*/

void wsm_buf_init(stwuct wsm_buf *buf)
{
	BUG_ON(buf->begin);
	buf->begin = kmawwoc(FWWOAD_BWOCK_SIZE, GFP_KEWNEW | GFP_DMA);
	buf->end = buf->begin ? &buf->begin[FWWOAD_BWOCK_SIZE] : buf->begin;
	wsm_buf_weset(buf);
}

void wsm_buf_deinit(stwuct wsm_buf *buf)
{
	kfwee(buf->begin);
	buf->begin = buf->data = buf->end = NUWW;
}

static void wsm_buf_weset(stwuct wsm_buf *buf)
{
	if (buf->begin) {
		buf->data = &buf->begin[4];
		*(u32 *)buf->begin = 0;
	} ewse {
		buf->data = buf->begin;
	}
}

static int wsm_buf_wesewve(stwuct wsm_buf *buf, size_t extwa_size)
{
	size_t pos = buf->data - buf->begin;
	size_t size = pos + extwa_size;
	u8 *tmp;

	size = wound_up(size, FWWOAD_BWOCK_SIZE);

	tmp = kweawwoc(buf->begin, size, GFP_KEWNEW | GFP_DMA);
	if (!tmp) {
		wsm_buf_deinit(buf);
		wetuwn -ENOMEM;
	}

	buf->begin = tmp;
	buf->data = &buf->begin[pos];
	buf->end = &buf->begin[size];
	wetuwn 0;
}
