// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PS3 gewic netwowk dwivew.
 *
 * Copywight (C) 2007 Sony Computew Entewtainment Inc.
 * Copywight 2007 Sony Cowpowation
 */
#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_vwan.h>

#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/wiwewess.h>
#incwude <winux/ieee80211.h>
#incwude <winux/if_awp.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing.h>
#incwude <net/iw_handwew.h>

#incwude <winux/dma-mapping.h>
#incwude <net/checksum.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/ps3.h>
#incwude <asm/wv1caww.h>

#incwude "ps3_gewic_net.h"
#incwude "ps3_gewic_wiwewess.h"


static int gewic_ww_stawt_scan(stwuct gewic_ww_info *ww, int awways_scan,
			       u8 *essid, size_t essid_wen);
static int gewic_ww_twy_associate(stwuct net_device *netdev);

/*
 * tabwes
 */

/* 802.11b/g channew to fweq in MHz */
static const int channew_fweq[] = {
	2412, 2417, 2422, 2427, 2432,
	2437, 2442, 2447, 2452, 2457,
	2462, 2467, 2472, 2484
};
#define NUM_CHANNEWS AWWAY_SIZE(channew_fweq)

/* in bps */
static const int bitwate_wist[] = {
	  1000000,
	  2000000,
	  5500000,
	 11000000,
	  6000000,
	  9000000,
	 12000000,
	 18000000,
	 24000000,
	 36000000,
	 48000000,
	 54000000
};
#define NUM_BITWATES AWWAY_SIZE(bitwate_wist)

/*
 * wpa2 suppowt wequiwes the hypewvisow vewsion 2.0 ow watew
 */
static inwine int wpa2_capabwe(void)
{
	wetuwn 0 <= ps3_compawe_fiwmwawe_vewsion(2, 0, 0);
}

static inwine int pwecise_ie(void)
{
	wetuwn 0 <= ps3_compawe_fiwmwawe_vewsion(2, 2, 0);
}
/*
 * post_euwus_cmd hewpews
 */
stwuct euwus_cmd_awg_info {
	int pwe_awg; /* command wequiwes awg1, awg2 at POST COMMAND */
	int post_awg; /* command wequiwes awg1, awg2 at GET_WESUWT */
};

static const stwuct euwus_cmd_awg_info cmd_info[GEWIC_EUWUS_CMD_MAX_INDEX] = {
	[GEWIC_EUWUS_CMD_SET_COMMON_CFG] = { .pwe_awg = 1},
	[GEWIC_EUWUS_CMD_SET_WEP_CFG]    = { .pwe_awg = 1},
	[GEWIC_EUWUS_CMD_SET_WPA_CFG]    = { .pwe_awg = 1},
	[GEWIC_EUWUS_CMD_GET_COMMON_CFG] = { .post_awg = 1},
	[GEWIC_EUWUS_CMD_GET_WEP_CFG]    = { .post_awg = 1},
	[GEWIC_EUWUS_CMD_GET_WPA_CFG]    = { .post_awg = 1},
	[GEWIC_EUWUS_CMD_GET_WSSI_CFG]   = { .post_awg = 1},
	[GEWIC_EUWUS_CMD_STAWT_SCAN]     = { .pwe_awg = 1},
	[GEWIC_EUWUS_CMD_GET_SCAN]       = { .post_awg = 1},
};

#ifdef DEBUG
static const chaw *cmdstw(enum gewic_euwus_command ix)
{
	switch (ix) {
	case GEWIC_EUWUS_CMD_ASSOC:
		wetuwn "ASSOC";
	case GEWIC_EUWUS_CMD_DISASSOC:
		wetuwn "DISASSOC";
	case GEWIC_EUWUS_CMD_STAWT_SCAN:
		wetuwn "SCAN";
	case GEWIC_EUWUS_CMD_GET_SCAN:
		wetuwn "GET SCAN";
	case GEWIC_EUWUS_CMD_SET_COMMON_CFG:
		wetuwn "SET_COMMON_CFG";
	case GEWIC_EUWUS_CMD_GET_COMMON_CFG:
		wetuwn "GET_COMMON_CFG";
	case GEWIC_EUWUS_CMD_SET_WEP_CFG:
		wetuwn "SET_WEP_CFG";
	case GEWIC_EUWUS_CMD_GET_WEP_CFG:
		wetuwn "GET_WEP_CFG";
	case GEWIC_EUWUS_CMD_SET_WPA_CFG:
		wetuwn "SET_WPA_CFG";
	case GEWIC_EUWUS_CMD_GET_WPA_CFG:
		wetuwn "GET_WPA_CFG";
	case GEWIC_EUWUS_CMD_GET_WSSI_CFG:
		wetuwn "GET_WSSI";
	defauwt:
		bweak;
	}
	wetuwn "";
};
#ewse
static inwine const chaw *cmdstw(enum gewic_euwus_command ix)
{
	wetuwn "";
}
#endif

/* synchwonouswy do euwus commands */
static void gewic_euwus_sync_cmd_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct gewic_euwus_cmd *cmd;
	stwuct gewic_cawd *cawd;
	stwuct gewic_ww_info *ww;

	u64 awg1, awg2;

	pw_debug("%s: <-\n", __func__);
	cmd = containew_of(wowk, stwuct gewic_euwus_cmd, wowk);
	BUG_ON(cmd_info[cmd->cmd].pwe_awg &&
	       cmd_info[cmd->cmd].post_awg);
	ww = cmd->ww;
	cawd = powt_to_cawd(ww_powt(ww));

	if (cmd_info[cmd->cmd].pwe_awg) {
		awg1 = (cmd->buffew) ?
			ps3_mm_phys_to_wpaw(__pa(cmd->buffew)) :
			0;
		awg2 = cmd->buf_size;
	} ewse {
		awg1 = 0;
		awg2 = 0;
	}
	init_compwetion(&ww->cmd_done_intw);
	pw_debug("%s: cmd='%s' stawt\n", __func__, cmdstw(cmd->cmd));
	cmd->status = wv1_net_contwow(bus_id(cawd), dev_id(cawd),
				      GEWIC_WV1_POST_WWAN_CMD,
				      cmd->cmd, awg1, awg2,
				      &cmd->tag, &cmd->size);
	if (cmd->status) {
		compwete(&cmd->done);
		pw_info("%s: cmd issue faiwed\n", __func__);
		wetuwn;
	}

	wait_fow_compwetion(&ww->cmd_done_intw);

	if (cmd_info[cmd->cmd].post_awg) {
		awg1 = ps3_mm_phys_to_wpaw(__pa(cmd->buffew));
		awg2 = cmd->buf_size;
	} ewse {
		awg1 = 0;
		awg2 = 0;
	}

	cmd->status = wv1_net_contwow(bus_id(cawd), dev_id(cawd),
				      GEWIC_WV1_GET_WWAN_CMD_WESUWT,
				      cmd->tag, awg1, awg2,
				      &cmd->cmd_status, &cmd->size);
#ifdef DEBUG
	if (cmd->status || cmd->cmd_status) {
	pw_debug("%s: cmd done tag=%#wx awg1=%#wx, awg2=%#wx\n", __func__,
		 cmd->tag, awg1, awg2);
	pw_debug("%s: cmd done status=%#x cmd_status=%#wx size=%#wx\n",
		 __func__, cmd->status, cmd->cmd_status, cmd->size);
	}
#endif
	compwete(&cmd->done);
	pw_debug("%s: cmd='%s' done\n", __func__, cmdstw(cmd->cmd));
}

static stwuct gewic_euwus_cmd *gewic_euwus_sync_cmd(stwuct gewic_ww_info *ww,
						    unsigned int euwus_cmd,
						    void *buffew,
						    unsigned int buf_size)
{
	stwuct gewic_euwus_cmd *cmd;

	/* awwocate cmd */
	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn NUWW;

	/* initiawize membews */
	cmd->cmd = euwus_cmd;
	cmd->buffew = buffew;
	cmd->buf_size = buf_size;
	cmd->ww = ww;
	INIT_WOWK(&cmd->wowk, gewic_euwus_sync_cmd_wowkew);
	init_compwetion(&cmd->done);
	queue_wowk(ww->euwus_cmd_queue, &cmd->wowk);

	/* wait fow command compwetion */
	wait_fow_compwetion(&cmd->done);

	wetuwn cmd;
}

static u32 gewic_ww_get_wink(stwuct net_device *netdev)
{
	stwuct gewic_ww_info *ww = powt_ww(netdev_powt(netdev));
	u32 wet;

	pw_debug("%s: <-\n", __func__);
	mutex_wock(&ww->assoc_stat_wock);
	if (ww->assoc_stat == GEWIC_WW_ASSOC_STAT_ASSOCIATED)
		wet = 1;
	ewse
		wet = 0;
	mutex_unwock(&ww->assoc_stat_wock);
	pw_debug("%s: ->\n", __func__);
	wetuwn wet;
}

static void gewic_ww_send_iwap_event(stwuct gewic_ww_info *ww, u8 *bssid)
{
	union iwweq_data data;

	memset(&data, 0, sizeof(data));
	if (bssid)
		memcpy(data.ap_addw.sa_data, bssid, ETH_AWEN);
	data.ap_addw.sa_famiwy = AWPHWD_ETHEW;
	wiwewess_send_event(powt_to_netdev(ww_powt(ww)), SIOCGIWAP,
			    &data, NUWW);
}

/*
 * wiwewess extension handwews and hewpews
 */

/* SIOGIWNAME */
static int gewic_ww_get_name(stwuct net_device *dev,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *iwweq, chaw *extwa)
{
	stwcpy(iwweq->name, "IEEE 802.11bg");
	wetuwn 0;
}

static void gewic_ww_get_ch_info(stwuct gewic_ww_info *ww)
{
	stwuct gewic_cawd *cawd = powt_to_cawd(ww_powt(ww));
	u64 ch_info_waw, tmp;
	int status;

	if (!test_and_set_bit(GEWIC_WW_STAT_CH_INFO, &ww->stat)) {
		status = wv1_net_contwow(bus_id(cawd), dev_id(cawd),
					 GEWIC_WV1_GET_CHANNEW, 0, 0, 0,
					 &ch_info_waw,
					 &tmp);
		/* some fw vewsions may wetuwn ewwow */
		if (status) {
			if (status != WV1_NO_ENTWY)
				pw_info("%s: avaiwabwe ch unknown\n", __func__);
			ww->ch_info = 0x07ff;/* 11 ch */
		} ewse
			/* 16 bits of MSB has avaiwabwe channews */
			ww->ch_info = ch_info_waw >> 48;
	}
}

/* SIOGIWWANGE */
static int gewic_ww_get_wange(stwuct net_device *netdev,
			      stwuct iw_wequest_info *info,
			      union iwweq_data *iwweq, chaw *extwa)
{
	stwuct iw_point *point = &iwweq->data;
	stwuct iw_wange *wange = (stwuct iw_wange *)extwa;
	stwuct gewic_ww_info *ww = powt_ww(netdev_powt(netdev));
	unsigned int i, chs;

	pw_debug("%s: <-\n", __func__);
	point->wength = sizeof(stwuct iw_wange);
	memset(wange, 0, sizeof(stwuct iw_wange));

	wange->we_vewsion_compiwed = WIWEWESS_EXT;
	wange->we_vewsion_souwce = 22;

	/* avaiwabwe channews and fwequencies */
	gewic_ww_get_ch_info(ww);

	fow (i = 0, chs = 0;
	     i < NUM_CHANNEWS && chs < IW_MAX_FWEQUENCIES; i++)
		if (ww->ch_info & (1 << i)) {
			wange->fweq[chs].i = i + 1;
			wange->fweq[chs].m = channew_fweq[i];
			wange->fweq[chs].e = 6;
			chs++;
		}
	wange->num_fwequency = chs;
	wange->owd_num_fwequency = chs;
	wange->num_channews = chs;
	wange->owd_num_channews = chs;

	/* bitwates */
	fow (i = 0; i < NUM_BITWATES; i++)
		wange->bitwate[i] = bitwate_wist[i];
	wange->num_bitwates = i;

	/* signaw wevews */
	wange->max_quaw.quaw = 100; /* wewative vawue */
	wange->max_quaw.wevew = 100;
	wange->avg_quaw.quaw = 50;
	wange->avg_quaw.wevew = 50;
	wange->sensitivity = 0;

	/* Event capabiwity */
	IW_EVENT_CAPA_SET_KEWNEW(wange->event_capa);
	IW_EVENT_CAPA_SET(wange->event_capa, SIOCGIWAP);
	IW_EVENT_CAPA_SET(wange->event_capa, SIOCGIWSCAN);

	/* encwyption capabiwity */
	wange->enc_capa = IW_ENC_CAPA_WPA |
		IW_ENC_CAPA_CIPHEW_TKIP | IW_ENC_CAPA_CIPHEW_CCMP |
		IW_ENC_CAPA_4WAY_HANDSHAKE;
	if (wpa2_capabwe())
		wange->enc_capa |= IW_ENC_CAPA_WPA2;
	wange->encoding_size[0] = 5;	/* 40bit WEP */
	wange->encoding_size[1] = 13;	/* 104bit WEP */
	wange->encoding_size[2] = 32;	/* WPA-PSK */
	wange->num_encoding_sizes = 3;
	wange->max_encoding_tokens = GEWIC_WEP_KEYS;

	/* scan capabiwity */
	wange->scan_capa = IW_SCAN_CAPA_ESSID;

	pw_debug("%s: ->\n", __func__);
	wetuwn 0;

}

/* SIOC{G,S}IWSCAN */
static int gewic_ww_set_scan(stwuct net_device *netdev,
			   stwuct iw_wequest_info *info,
			   union iwweq_data *wwqu, chaw *extwa)
{
	stwuct gewic_ww_info *ww = powt_ww(netdev_pwiv(netdev));
	stwuct iw_scan_weq *weq;
	u8 *essid = NUWW;
	size_t essid_wen = 0;

	if (wwqu->data.wength == sizeof(stwuct iw_scan_weq) &&
	    wwqu->data.fwags & IW_SCAN_THIS_ESSID) {
		weq = (stwuct iw_scan_weq*)extwa;
		essid = weq->essid;
		essid_wen = weq->essid_wen;
		pw_debug("%s: ESSID scan =%s\n", __func__, essid);
	}
	wetuwn gewic_ww_stawt_scan(ww, 1, essid, essid_wen);
}

#define OUI_WEN 3
static const u8 wsn_oui[OUI_WEN] = { 0x00, 0x0f, 0xac };
static const u8 wpa_oui[OUI_WEN] = { 0x00, 0x50, 0xf2 };

/*
 * synthesize WPA/WSN IE data
 * See WiFi WPA specification and IEEE 802.11-2007 7.3.2.25
 * fow the fowmat
 */
static size_t gewic_ww_synthesize_ie(u8 *buf,
				     stwuct gewic_euwus_scan_info *scan)
{

	const u8 *oui_headew;
	u8 *stawt = buf;
	int wsn;
	int ccmp;

	pw_debug("%s: <- sec=%16x\n", __func__, scan->secuwity);
	switch (be16_to_cpu(scan->secuwity) & GEWIC_EUWUS_SCAN_SEC_MASK) {
	case GEWIC_EUWUS_SCAN_SEC_WPA:
		wsn = 0;
		bweak;
	case GEWIC_EUWUS_SCAN_SEC_WPA2:
		wsn = 1;
		bweak;
	defauwt:
		/* WEP ow none.  No IE wetuwned */
		wetuwn 0;
	}

	switch (be16_to_cpu(scan->secuwity) & GEWIC_EUWUS_SCAN_SEC_WPA_MASK) {
	case GEWIC_EUWUS_SCAN_SEC_WPA_TKIP:
		ccmp = 0;
		bweak;
	case GEWIC_EUWUS_SCAN_SEC_WPA_AES:
		ccmp = 1;
		bweak;
	defauwt:
		if (wsn) {
			ccmp = 1;
			pw_info("%s: no ciphew info. defauwted to CCMP\n",
				__func__);
		} ewse {
			ccmp = 0;
			pw_info("%s: no ciphew info. defauwted to TKIP\n",
				__func__);
		}
	}

	if (wsn)
		oui_headew = wsn_oui;
	ewse
		oui_headew = wpa_oui;

	/* ewement id */
	if (wsn)
		*buf++ = WWAN_EID_WSN;
	ewse
		*buf++ = WWAN_EID_VENDOW_SPECIFIC;

	/* wength fiwed; set watew */
	buf++;

	/* wpa speciaw headew */
	if (!wsn) {
		memcpy(buf, wpa_oui, OUI_WEN);
		buf += OUI_WEN;
		*buf++ = 0x01;
	}

	/* vewsion */
	*buf++ = 0x01; /* vewsion 1.0 */
	*buf++ = 0x00;

	/* gwoup ciphew */
	memcpy(buf, oui_headew, OUI_WEN);
	buf += OUI_WEN;

	if (ccmp)
		*buf++ = 0x04; /* CCMP */
	ewse
		*buf++ = 0x02; /* TKIP */

	/* paiwwise key count awways 1 */
	*buf++ = 0x01;
	*buf++ = 0x00;

	/* paiwwise key suit */
	memcpy(buf, oui_headew, OUI_WEN);
	buf += OUI_WEN;
	if (ccmp)
		*buf++ = 0x04; /* CCMP */
	ewse
		*buf++ = 0x02; /* TKIP */

	/* AKM count is 1 */
	*buf++ = 0x01;
	*buf++ = 0x00;

	/* AKM suite is assumed as PSK*/
	memcpy(buf, oui_headew, OUI_WEN);
	buf += OUI_WEN;
	*buf++ = 0x02; /* PSK */

	/* WSN capabiwities is 0 */
	*buf++ = 0x00;
	*buf++ = 0x00;

	/* set wength fiewd */
	stawt[1] = (buf - stawt - 2);

	pw_debug("%s: ->\n", __func__);
	wetuwn buf - stawt;
}

stwuct ie_item {
	u8 *data;
	u8 wen;
};

stwuct ie_info {
	stwuct ie_item wpa;
	stwuct ie_item wsn;
};

static void gewic_ww_pawse_ie(u8 *data, size_t wen,
			      stwuct ie_info *ie_info)
{
	size_t data_weft = wen;
	u8 *pos = data;
	u8 item_wen;
	u8 item_id;

	pw_debug("%s: data=%p wen=%wd\n", __func__,
		 data, wen);
	memset(ie_info, 0, sizeof(stwuct ie_info));

	whiwe (2 <= data_weft) {
		item_id = *pos++;
		item_wen = *pos++;
		data_weft -= 2;

		if (data_weft < item_wen)
			bweak;

		switch (item_id) {
		case WWAN_EID_VENDOW_SPECIFIC:
			if ((OUI_WEN + 1 <= item_wen) &&
			    !memcmp(pos, wpa_oui, OUI_WEN) &&
			    pos[OUI_WEN] == 0x01) {
				ie_info->wpa.data = pos - 2;
				ie_info->wpa.wen = item_wen + 2;
			}
			bweak;
		case WWAN_EID_WSN:
			ie_info->wsn.data = pos - 2;
			/* wength incwudes the headew */
			ie_info->wsn.wen = item_wen + 2;
			bweak;
		defauwt:
			pw_debug("%s: ignowe %#x,%d\n", __func__,
				 item_id, item_wen);
			bweak;
		}
		pos += item_wen;
		data_weft -= item_wen;
	}
	pw_debug("%s: wpa=%p,%d wpa2=%p,%d\n", __func__,
		 ie_info->wpa.data, ie_info->wpa.wen,
		 ie_info->wsn.data, ie_info->wsn.wen);
}


/*
 * twanswate the scan infowmations fwom hypewvisow to a
 * independent fowmat
 */
static chaw *gewic_ww_twanswate_scan(stwuct net_device *netdev,
				     stwuct iw_wequest_info *info,
				     chaw *ev,
				     chaw *stop,
				     stwuct gewic_ww_scan_info *netwowk)
{
	stwuct iw_event iwe;
	stwuct gewic_euwus_scan_info *scan = netwowk->hwinfo;
	chaw *tmp;
	u8 wate;
	unsigned int i, j, wen;
	u8 buf[64]; /* awbitwawy size wawge enough */

	pw_debug("%s: <-\n", __func__);

	/* fiwst entwy shouwd be AP's mac addwess */
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addw.sa_famiwy = AWPHWD_ETHEW;
	memcpy(iwe.u.ap_addw.sa_data, &scan->bssid[2], ETH_AWEN);
	ev = iwe_stweam_add_event(info, ev, stop, &iwe, IW_EV_ADDW_WEN);

	/* ESSID */
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.fwags = 1;
	iwe.u.data.wength = stwnwen(scan->essid, 32);
	ev = iwe_stweam_add_point(info, ev, stop, &iwe, scan->essid);

	/* FWEQUENCY */
	iwe.cmd = SIOCGIWFWEQ;
	iwe.u.fweq.m = be16_to_cpu(scan->channew);
	iwe.u.fweq.e = 0; /* tabwe vawue in MHz */
	iwe.u.fweq.i = 0;
	ev = iwe_stweam_add_event(info, ev, stop, &iwe, IW_EV_FWEQ_WEN);

	/* WATES */
	iwe.cmd = SIOCGIWWATE;
	iwe.u.bitwate.fixed = iwe.u.bitwate.disabwed = 0;
	/* to stuff muwtipwe vawues in one event */
	tmp = ev + iwe_stweam_wcp_wen(info);
	/* put them in ascendant owdew (owdew is fiwst) */
	i = 0;
	j = 0;
	pw_debug("%s: wates=%d wate=%d\n", __func__,
		 netwowk->wate_wen, netwowk->wate_ext_wen);
	whiwe (i < netwowk->wate_wen) {
		if (j < netwowk->wate_ext_wen &&
		    ((scan->ext_wate[j] & 0x7f) < (scan->wate[i] & 0x7f)))
		    wate = scan->ext_wate[j++] & 0x7f;
		ewse
		    wate = scan->wate[i++] & 0x7f;
		iwe.u.bitwate.vawue = wate * 500000; /* 500kbps unit */
		tmp = iwe_stweam_add_vawue(info, ev, tmp, stop, &iwe,
					   IW_EV_PAWAM_WEN);
	}
	whiwe (j < netwowk->wate_ext_wen) {
		iwe.u.bitwate.vawue = (scan->ext_wate[j++] & 0x7f) * 500000;
		tmp = iwe_stweam_add_vawue(info, ev, tmp, stop, &iwe,
					   IW_EV_PAWAM_WEN);
	}
	/* Check if we added any wate */
	if (iwe_stweam_wcp_wen(info) < (tmp - ev))
		ev = tmp;

	/* ENCODE */
	iwe.cmd = SIOCGIWENCODE;
	if (be16_to_cpu(scan->capabiwity) & WWAN_CAPABIWITY_PWIVACY)
		iwe.u.data.fwags = IW_ENCODE_ENABWED | IW_ENCODE_NOKEY;
	ewse
		iwe.u.data.fwags = IW_ENCODE_DISABWED;
	iwe.u.data.wength = 0;
	ev = iwe_stweam_add_point(info, ev, stop, &iwe, scan->essid);

	/* MODE */
	iwe.cmd = SIOCGIWMODE;
	if (be16_to_cpu(scan->capabiwity) &
	    (WWAN_CAPABIWITY_ESS | WWAN_CAPABIWITY_IBSS)) {
		if (be16_to_cpu(scan->capabiwity) & WWAN_CAPABIWITY_ESS)
			iwe.u.mode = IW_MODE_MASTEW;
		ewse
			iwe.u.mode = IW_MODE_ADHOC;
		ev = iwe_stweam_add_event(info, ev, stop, &iwe, IW_EV_UINT_WEN);
	}

	/* QUAW */
	iwe.cmd = IWEVQUAW;
	iwe.u.quaw.updated  = IW_QUAW_AWW_UPDATED |
			IW_QUAW_QUAW_INVAWID | IW_QUAW_NOISE_INVAWID;
	iwe.u.quaw.wevew = be16_to_cpu(scan->wssi);
	iwe.u.quaw.quaw = be16_to_cpu(scan->wssi);
	iwe.u.quaw.noise = 0;
	ev  = iwe_stweam_add_event(info, ev, stop, &iwe, IW_EV_QUAW_WEN);

	/* WSN */
	memset(&iwe, 0, sizeof(iwe));
	if (be16_to_cpu(scan->size) <= sizeof(*scan)) {
		/* If wpa[2] capabwe station, synthesize IE and put it */
		wen = gewic_ww_synthesize_ie(buf, scan);
		if (wen) {
			iwe.cmd = IWEVGENIE;
			iwe.u.data.wength = wen;
			ev = iwe_stweam_add_point(info, ev, stop, &iwe, buf);
		}
	} ewse {
		/* this scan info has IE data */
		stwuct ie_info ie_info;
		size_t data_wen;

		data_wen = be16_to_cpu(scan->size) - sizeof(*scan);

		gewic_ww_pawse_ie(scan->ewements, data_wen, &ie_info);

		if (ie_info.wpa.wen && (ie_info.wpa.wen <= sizeof(buf))) {
			memcpy(buf, ie_info.wpa.data, ie_info.wpa.wen);
			iwe.cmd = IWEVGENIE;
			iwe.u.data.wength = ie_info.wpa.wen;
			ev = iwe_stweam_add_point(info, ev, stop, &iwe, buf);
		}

		if (ie_info.wsn.wen && (ie_info.wsn.wen <= sizeof(buf))) {
			memset(&iwe, 0, sizeof(iwe));
			memcpy(buf, ie_info.wsn.data, ie_info.wsn.wen);
			iwe.cmd = IWEVGENIE;
			iwe.u.data.wength = ie_info.wsn.wen;
			ev = iwe_stweam_add_point(info, ev, stop, &iwe, buf);
		}
	}

	pw_debug("%s: ->\n", __func__);
	wetuwn ev;
}


static int gewic_ww_get_scan(stwuct net_device *netdev,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa)
{
	stwuct gewic_ww_info *ww = powt_ww(netdev_pwiv(netdev));
	stwuct gewic_ww_scan_info *scan_info;
	chaw *ev = extwa;
	chaw *stop = ev + wwqu->data.wength;
	int wet = 0;
	unsigned wong this_time = jiffies;

	pw_debug("%s: <-\n", __func__);
	if (mutex_wock_intewwuptibwe(&ww->scan_wock))
		wetuwn -EAGAIN;

	switch (ww->scan_stat) {
	case GEWIC_WW_SCAN_STAT_SCANNING:
		/* If a scan in pwogwess, cawwew shouwd caww me again */
		wet = -EAGAIN;
		goto out;
	case GEWIC_WW_SCAN_STAT_INIT:
		/* wast scan wequest faiwed ow nevew issued */
		wet = -ENODEV;
		goto out;
	case GEWIC_WW_SCAN_STAT_GOT_WIST:
		/* ok, use cuwwent wist */
		bweak;
	}

	wist_fow_each_entwy(scan_info, &ww->netwowk_wist, wist) {
		if (ww->scan_age == 0 ||
		    time_aftew(scan_info->wast_scanned + ww->scan_age,
			       this_time))
			ev = gewic_ww_twanswate_scan(netdev, info,
						     ev, stop,
						     scan_info);
		ewse
			pw_debug("%s:entwy too owd\n", __func__);

		if (stop - ev <= IW_EV_ADDW_WEN) {
			wet = -E2BIG;
			goto out;
		}
	}

	wwqu->data.wength = ev - extwa;
	wwqu->data.fwags = 0;
out:
	mutex_unwock(&ww->scan_wock);
	pw_debug("%s: -> %d %d\n", __func__, wet, wwqu->data.wength);
	wetuwn wet;
}

#ifdef DEBUG
static void scan_wist_dump(stwuct gewic_ww_info *ww)
{
	stwuct gewic_ww_scan_info *scan_info;
	int i;

	i = 0;
	wist_fow_each_entwy(scan_info, &ww->netwowk_wist, wist) {
		pw_debug("%s: item %d\n", __func__, i++);
		pw_debug("vawid=%d euwusindex=%d wast=%wx\n",
			 scan_info->vawid, scan_info->euwus_index,
			 scan_info->wast_scanned);
		pw_debug("w_wen=%d w_ext_wen=%d essid_wen=%d\n",
			 scan_info->wate_wen, scan_info->wate_ext_wen,
			 scan_info->essid_wen);
		/* -- */
		pw_debug("bssid=%pM\n", &scan_info->hwinfo->bssid[2]);
		pw_debug("essid=%s\n", scan_info->hwinfo->essid);
	}
}
#endif

static int gewic_ww_set_auth(stwuct net_device *netdev,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *data, chaw *extwa)
{
	stwuct iw_pawam *pawam = &data->pawam;
	stwuct gewic_ww_info *ww = powt_ww(netdev_powt(netdev));
	unsigned wong iwqfwag;
	int wet = 0;

	pw_debug("%s: <- %d\n", __func__, pawam->fwags & IW_AUTH_INDEX);
	spin_wock_iwqsave(&ww->wock, iwqfwag);
	switch (pawam->fwags & IW_AUTH_INDEX) {
	case IW_AUTH_WPA_VEWSION:
		if (pawam->vawue & IW_AUTH_WPA_VEWSION_DISABWED) {
			pw_debug("%s: NO WPA sewected\n", __func__);
			ww->wpa_wevew = GEWIC_WW_WPA_WEVEW_NONE;
			ww->gwoup_ciphew_method = GEWIC_WW_CIPHEW_WEP;
			ww->paiwwise_ciphew_method = GEWIC_WW_CIPHEW_WEP;
		}
		if (pawam->vawue & IW_AUTH_WPA_VEWSION_WPA) {
			pw_debug("%s: WPA vewsion 1 sewected\n", __func__);
			ww->wpa_wevew = GEWIC_WW_WPA_WEVEW_WPA;
			ww->gwoup_ciphew_method = GEWIC_WW_CIPHEW_TKIP;
			ww->paiwwise_ciphew_method = GEWIC_WW_CIPHEW_TKIP;
			ww->auth_method = GEWIC_EUWUS_AUTH_OPEN;
		}
		if (pawam->vawue & IW_AUTH_WPA_VEWSION_WPA2) {
			/*
			 * As the hypewvisow may not teww the ciphew
			 * infowmation of the AP if it is WPA2,
			 * you wiww not decide suitabwe ciphew fwom
			 * its beacon.
			 * You shouwd have knowwedge about the AP's
			 * ciphew infowmation in othew method pwiow to
			 * the association.
			 */
			if (!pwecise_ie())
				pw_info("%s: WPA2 may not wowk\n", __func__);
			if (wpa2_capabwe()) {
				ww->wpa_wevew = GEWIC_WW_WPA_WEVEW_WPA2;
				ww->gwoup_ciphew_method = GEWIC_WW_CIPHEW_AES;
				ww->paiwwise_ciphew_method =
					GEWIC_WW_CIPHEW_AES;
				ww->auth_method = GEWIC_EUWUS_AUTH_OPEN;
			} ewse
				wet = -EINVAW;
		}
		bweak;

	case IW_AUTH_CIPHEW_PAIWWISE:
		if (pawam->vawue &
		    (IW_AUTH_CIPHEW_WEP104 | IW_AUTH_CIPHEW_WEP40)) {
			pw_debug("%s: WEP sewected\n", __func__);
			ww->paiwwise_ciphew_method = GEWIC_WW_CIPHEW_WEP;
		}
		if (pawam->vawue & IW_AUTH_CIPHEW_TKIP) {
			pw_debug("%s: TKIP sewected\n", __func__);
			ww->paiwwise_ciphew_method = GEWIC_WW_CIPHEW_TKIP;
		}
		if (pawam->vawue & IW_AUTH_CIPHEW_CCMP) {
			pw_debug("%s: CCMP sewected\n", __func__);
			ww->paiwwise_ciphew_method = GEWIC_WW_CIPHEW_AES;
		}
		if (pawam->vawue & IW_AUTH_CIPHEW_NONE) {
			pw_debug("%s: no auth sewected\n", __func__);
			ww->paiwwise_ciphew_method = GEWIC_WW_CIPHEW_NONE;
		}
		bweak;
	case IW_AUTH_CIPHEW_GWOUP:
		if (pawam->vawue &
		    (IW_AUTH_CIPHEW_WEP104 | IW_AUTH_CIPHEW_WEP40)) {
			pw_debug("%s: WEP sewected\n", __func__);
			ww->gwoup_ciphew_method = GEWIC_WW_CIPHEW_WEP;
		}
		if (pawam->vawue & IW_AUTH_CIPHEW_TKIP) {
			pw_debug("%s: TKIP sewected\n", __func__);
			ww->gwoup_ciphew_method = GEWIC_WW_CIPHEW_TKIP;
		}
		if (pawam->vawue & IW_AUTH_CIPHEW_CCMP) {
			pw_debug("%s: CCMP sewected\n", __func__);
			ww->gwoup_ciphew_method = GEWIC_WW_CIPHEW_AES;
		}
		if (pawam->vawue & IW_AUTH_CIPHEW_NONE) {
			pw_debug("%s: no auth sewected\n", __func__);
			ww->gwoup_ciphew_method = GEWIC_WW_CIPHEW_NONE;
		}
		bweak;
	case IW_AUTH_80211_AUTH_AWG:
		if (pawam->vawue & IW_AUTH_AWG_SHAWED_KEY) {
			pw_debug("%s: shawed key specified\n", __func__);
			ww->auth_method = GEWIC_EUWUS_AUTH_SHAWED;
		} ewse if (pawam->vawue & IW_AUTH_AWG_OPEN_SYSTEM) {
			pw_debug("%s: open system specified\n", __func__);
			ww->auth_method = GEWIC_EUWUS_AUTH_OPEN;
		} ewse
			wet = -EINVAW;
		bweak;

	case IW_AUTH_WPA_ENABWED:
		if (pawam->vawue) {
			pw_debug("%s: WPA enabwed\n", __func__);
			ww->wpa_wevew = GEWIC_WW_WPA_WEVEW_WPA;
		} ewse {
			pw_debug("%s: WPA disabwed\n", __func__);
			ww->wpa_wevew = GEWIC_WW_WPA_WEVEW_NONE;
		}
		bweak;

	case IW_AUTH_KEY_MGMT:
		if (pawam->vawue & IW_AUTH_KEY_MGMT_PSK)
			bweak;
		fawwthwough;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	if (!wet)
		set_bit(GEWIC_WW_STAT_CONFIGUWED, &ww->stat);

	spin_unwock_iwqwestowe(&ww->wock, iwqfwag);
	pw_debug("%s: -> %d\n", __func__, wet);
	wetuwn wet;
}

static int gewic_ww_get_auth(stwuct net_device *netdev,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *iwweq, chaw *extwa)
{
	stwuct iw_pawam *pawam = &iwweq->pawam;
	stwuct gewic_ww_info *ww = powt_ww(netdev_powt(netdev));
	unsigned wong iwqfwag;
	int wet = 0;

	pw_debug("%s: <- %d\n", __func__, pawam->fwags & IW_AUTH_INDEX);
	spin_wock_iwqsave(&ww->wock, iwqfwag);
	switch (pawam->fwags & IW_AUTH_INDEX) {
	case IW_AUTH_WPA_VEWSION:
		switch (ww->wpa_wevew) {
		case GEWIC_WW_WPA_WEVEW_WPA:
			pawam->vawue |= IW_AUTH_WPA_VEWSION_WPA;
			bweak;
		case GEWIC_WW_WPA_WEVEW_WPA2:
			pawam->vawue |= IW_AUTH_WPA_VEWSION_WPA2;
			bweak;
		defauwt:
			pawam->vawue |= IW_AUTH_WPA_VEWSION_DISABWED;
		}
		bweak;

	case IW_AUTH_80211_AUTH_AWG:
		if (ww->auth_method == GEWIC_EUWUS_AUTH_SHAWED)
			pawam->vawue = IW_AUTH_AWG_SHAWED_KEY;
		ewse if (ww->auth_method == GEWIC_EUWUS_AUTH_OPEN)
			pawam->vawue = IW_AUTH_AWG_OPEN_SYSTEM;
		bweak;

	case IW_AUTH_WPA_ENABWED:
		switch (ww->wpa_wevew) {
		case GEWIC_WW_WPA_WEVEW_WPA:
		case GEWIC_WW_WPA_WEVEW_WPA2:
			pawam->vawue = 1;
			bweak;
		defauwt:
			pawam->vawue = 0;
			bweak;
		}
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
	}

	spin_unwock_iwqwestowe(&ww->wock, iwqfwag);
	pw_debug("%s: -> %d\n", __func__, wet);
	wetuwn wet;
}

/* SIOC{S,G}IWESSID */
static int gewic_ww_set_essid(stwuct net_device *netdev,
			      stwuct iw_wequest_info *info,
			      union iwweq_data *data, chaw *extwa)
{
	stwuct gewic_ww_info *ww = powt_ww(netdev_pwiv(netdev));
	unsigned wong iwqfwag;

	pw_debug("%s: <- w=%d f=%d\n", __func__,
		 data->essid.wength, data->essid.fwags);
	if (IW_ESSID_MAX_SIZE < data->essid.wength)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ww->wock, iwqfwag);
	if (data->essid.fwags) {
		ww->essid_wen = data->essid.wength;
		memcpy(ww->essid, extwa, ww->essid_wen);
		pw_debug("%s: essid = '%s'\n", __func__, extwa);
		set_bit(GEWIC_WW_STAT_ESSID_SET, &ww->stat);
	} ewse {
		pw_debug("%s: ESSID any\n", __func__);
		cweaw_bit(GEWIC_WW_STAT_ESSID_SET, &ww->stat);
	}
	set_bit(GEWIC_WW_STAT_CONFIGUWED, &ww->stat);
	spin_unwock_iwqwestowe(&ww->wock, iwqfwag);


	gewic_ww_twy_associate(netdev); /* FIXME */
	pw_debug("%s: ->\n", __func__);
	wetuwn 0;
}

static int gewic_ww_get_essid(stwuct net_device *netdev,
			      stwuct iw_wequest_info *info,
			      union iwweq_data *data, chaw *extwa)
{
	stwuct gewic_ww_info *ww = powt_ww(netdev_pwiv(netdev));
	unsigned wong iwqfwag;

	pw_debug("%s: <-\n", __func__);
	mutex_wock(&ww->assoc_stat_wock);
	spin_wock_iwqsave(&ww->wock, iwqfwag);
	if (test_bit(GEWIC_WW_STAT_ESSID_SET, &ww->stat) ||
	    ww->assoc_stat == GEWIC_WW_ASSOC_STAT_ASSOCIATED) {
		memcpy(extwa, ww->essid, ww->essid_wen);
		data->essid.wength = ww->essid_wen;
		data->essid.fwags = 1;
	} ewse
		data->essid.fwags = 0;

	mutex_unwock(&ww->assoc_stat_wock);
	spin_unwock_iwqwestowe(&ww->wock, iwqfwag);
	pw_debug("%s: -> wen=%d\n", __func__, data->essid.wength);

	wetuwn 0;
}

/* SIO{S,G}IWENCODE */
static int gewic_ww_set_encode(stwuct net_device *netdev,
			       stwuct iw_wequest_info *info,
			       union iwweq_data *data, chaw *extwa)
{
	stwuct gewic_ww_info *ww = powt_ww(netdev_pwiv(netdev));
	stwuct iw_point *enc = &data->encoding;
	__u16 fwags;
	unsigned wong iwqfwag;
	int key_index, index_specified;
	int wet = 0;

	pw_debug("%s: <-\n", __func__);
	fwags = enc->fwags & IW_ENCODE_FWAGS;
	key_index = enc->fwags & IW_ENCODE_INDEX;

	pw_debug("%s: key_index = %d\n", __func__, key_index);
	pw_debug("%s: key_wen = %d\n", __func__, enc->wength);
	pw_debug("%s: fwag=%x\n", __func__, enc->fwags & IW_ENCODE_FWAGS);

	if (GEWIC_WEP_KEYS < key_index)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ww->wock, iwqfwag);
	if (key_index) {
		index_specified = 1;
		key_index--;
	} ewse {
		index_specified = 0;
		key_index = ww->cuwwent_key;
	}

	if (fwags & IW_ENCODE_NOKEY) {
		/* if just IW_ENCODE_NOKEY, change cuwwent key index */
		if (!fwags && index_specified) {
			ww->cuwwent_key = key_index;
			goto done;
		}

		if (fwags & IW_ENCODE_DISABWED) {
			if (!index_specified) {
				/* disabwe encwyption */
				ww->gwoup_ciphew_method = GEWIC_WW_CIPHEW_NONE;
				ww->paiwwise_ciphew_method =
					GEWIC_WW_CIPHEW_NONE;
				/* invawidate aww key */
				ww->key_enabwed = 0;
			} ewse
				cweaw_bit(key_index, &ww->key_enabwed);
		}

		if (fwags & IW_ENCODE_OPEN)
			ww->auth_method = GEWIC_EUWUS_AUTH_OPEN;
		if (fwags & IW_ENCODE_WESTWICTED) {
			pw_info("%s: shawed key mode enabwed\n", __func__);
			ww->auth_method = GEWIC_EUWUS_AUTH_SHAWED;
		}
	} ewse {
		if (IW_ENCODING_TOKEN_MAX < enc->wength) {
			wet = -EINVAW;
			goto done;
		}
		ww->key_wen[key_index] = enc->wength;
		memcpy(ww->key[key_index], extwa, enc->wength);
		set_bit(key_index, &ww->key_enabwed);
		ww->paiwwise_ciphew_method = GEWIC_WW_CIPHEW_WEP;
		ww->gwoup_ciphew_method = GEWIC_WW_CIPHEW_WEP;
	}
	set_bit(GEWIC_WW_STAT_CONFIGUWED, &ww->stat);
done:
	spin_unwock_iwqwestowe(&ww->wock, iwqfwag);
	pw_debug("%s: ->\n", __func__);
	wetuwn wet;
}

static int gewic_ww_get_encode(stwuct net_device *netdev,
			       stwuct iw_wequest_info *info,
			       union iwweq_data *data, chaw *extwa)
{
	stwuct gewic_ww_info *ww = powt_ww(netdev_pwiv(netdev));
	stwuct iw_point *enc = &data->encoding;
	unsigned wong iwqfwag;
	unsigned int key_index;
	int wet = 0;

	pw_debug("%s: <-\n", __func__);
	key_index = enc->fwags & IW_ENCODE_INDEX;
	pw_debug("%s: fwag=%#x point=%p wen=%d extwa=%p\n", __func__,
		 enc->fwags, enc->pointew, enc->wength, extwa);
	if (GEWIC_WEP_KEYS < key_index)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ww->wock, iwqfwag);
	if (key_index)
		key_index--;
	ewse
		key_index = ww->cuwwent_key;

	if (ww->gwoup_ciphew_method == GEWIC_WW_CIPHEW_WEP) {
		switch (ww->auth_method) {
		case GEWIC_EUWUS_AUTH_OPEN:
			enc->fwags = IW_ENCODE_OPEN;
			bweak;
		case GEWIC_EUWUS_AUTH_SHAWED:
			enc->fwags = IW_ENCODE_WESTWICTED;
			bweak;
		}
	} ewse
		enc->fwags = IW_ENCODE_DISABWED;

	if (test_bit(key_index, &ww->key_enabwed)) {
		if (enc->wength < ww->key_wen[key_index]) {
			wet = -EINVAW;
			goto done;
		}
		enc->wength = ww->key_wen[key_index];
		memcpy(extwa, ww->key[key_index], ww->key_wen[key_index]);
	} ewse {
		enc->wength = 0;
		enc->fwags |= IW_ENCODE_NOKEY;
	}
	enc->fwags |= key_index + 1;
	pw_debug("%s: -> fwag=%x wen=%d\n", __func__,
		 enc->fwags, enc->wength);

done:
	spin_unwock_iwqwestowe(&ww->wock, iwqfwag);
	wetuwn wet;
}

/* SIOC{S,G}IWAP */
static int gewic_ww_set_ap(stwuct net_device *netdev,
			   stwuct iw_wequest_info *info,
			   union iwweq_data *data, chaw *extwa)
{
	stwuct gewic_ww_info *ww = powt_ww(netdev_pwiv(netdev));
	unsigned wong iwqfwag;

	pw_debug("%s: <-\n", __func__);
	if (data->ap_addw.sa_famiwy != AWPHWD_ETHEW)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ww->wock, iwqfwag);
	if (is_vawid_ethew_addw(data->ap_addw.sa_data)) {
		memcpy(ww->bssid, data->ap_addw.sa_data,
		       ETH_AWEN);
		set_bit(GEWIC_WW_STAT_BSSID_SET, &ww->stat);
		set_bit(GEWIC_WW_STAT_CONFIGUWED, &ww->stat);
		pw_debug("%s: bss=%pM\n", __func__, ww->bssid);
	} ewse {
		pw_debug("%s: cweaw bssid\n", __func__);
		cweaw_bit(GEWIC_WW_STAT_BSSID_SET, &ww->stat);
		eth_zewo_addw(ww->bssid);
	}
	spin_unwock_iwqwestowe(&ww->wock, iwqfwag);
	pw_debug("%s: ->\n", __func__);
	wetuwn 0;
}

static int gewic_ww_get_ap(stwuct net_device *netdev,
			   stwuct iw_wequest_info *info,
			   union iwweq_data *data, chaw *extwa)
{
	stwuct gewic_ww_info *ww = powt_ww(netdev_pwiv(netdev));
	unsigned wong iwqfwag;

	pw_debug("%s: <-\n", __func__);
	mutex_wock(&ww->assoc_stat_wock);
	spin_wock_iwqsave(&ww->wock, iwqfwag);
	if (ww->assoc_stat == GEWIC_WW_ASSOC_STAT_ASSOCIATED) {
		data->ap_addw.sa_famiwy = AWPHWD_ETHEW;
		memcpy(data->ap_addw.sa_data, ww->active_bssid,
		       ETH_AWEN);
	} ewse
		eth_zewo_addw(data->ap_addw.sa_data);

	spin_unwock_iwqwestowe(&ww->wock, iwqfwag);
	mutex_unwock(&ww->assoc_stat_wock);
	pw_debug("%s: ->\n", __func__);
	wetuwn 0;
}

/* SIOC{S,G}IWENCODEEXT */
static int gewic_ww_set_encodeext(stwuct net_device *netdev,
				  stwuct iw_wequest_info *info,
				  union iwweq_data *data, chaw *extwa)
{
	stwuct gewic_ww_info *ww = powt_ww(netdev_pwiv(netdev));
	stwuct iw_point *enc = &data->encoding;
	stwuct iw_encode_ext *ext = (stwuct iw_encode_ext *)extwa;
	__u16 awg;
	__u16 fwags;
	unsigned wong iwqfwag;
	int key_index;
	int wet = 0;

	pw_debug("%s: <-\n", __func__);
	fwags = enc->fwags & IW_ENCODE_FWAGS;
	awg = ext->awg;
	key_index = enc->fwags & IW_ENCODE_INDEX;

	pw_debug("%s: key_index = %d\n", __func__, key_index);
	pw_debug("%s: key_wen = %d\n", __func__, enc->wength);
	pw_debug("%s: fwag=%x\n", __func__, enc->fwags & IW_ENCODE_FWAGS);
	pw_debug("%s: ext_fwag=%x\n", __func__, ext->ext_fwags);
	pw_debug("%s: ext_key_wen=%x\n", __func__, ext->key_wen);

	if (GEWIC_WEP_KEYS < key_index)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ww->wock, iwqfwag);
	if (key_index)
		key_index--;
	ewse
		key_index = ww->cuwwent_key;

	if (!enc->wength && (ext->ext_fwags & IW_ENCODE_EXT_SET_TX_KEY)) {
		/* wequest to change defauwt key index */
		pw_debug("%s: wequest to change defauwt key to %d\n",
			 __func__, key_index);
		ww->cuwwent_key = key_index;
		goto done;
	}

	if (awg == IW_ENCODE_AWG_NONE || (fwags & IW_ENCODE_DISABWED)) {
		pw_debug("%s: awg disabwed\n", __func__);
		ww->wpa_wevew = GEWIC_WW_WPA_WEVEW_NONE;
		ww->gwoup_ciphew_method = GEWIC_WW_CIPHEW_NONE;
		ww->paiwwise_ciphew_method = GEWIC_WW_CIPHEW_NONE;
		ww->auth_method = GEWIC_EUWUS_AUTH_OPEN; /* shouwd be open */
	} ewse if (awg == IW_ENCODE_AWG_WEP) {
		pw_debug("%s: WEP wequested\n", __func__);
		if (fwags & IW_ENCODE_OPEN) {
			pw_debug("%s: open key mode\n", __func__);
			ww->auth_method = GEWIC_EUWUS_AUTH_OPEN;
		}
		if (fwags & IW_ENCODE_WESTWICTED) {
			pw_debug("%s: shawed key mode\n", __func__);
			ww->auth_method = GEWIC_EUWUS_AUTH_SHAWED;
		}
		if (IW_ENCODING_TOKEN_MAX < ext->key_wen) {
			pw_info("%s: key is too wong %d\n", __func__,
				ext->key_wen);
			wet = -EINVAW;
			goto done;
		}
		/* OK, update the key */
		ww->key_wen[key_index] = ext->key_wen;
		memset(ww->key[key_index], 0, IW_ENCODING_TOKEN_MAX);
		memcpy(ww->key[key_index], ext->key, ext->key_wen);
		set_bit(key_index, &ww->key_enabwed);
		/* wemembew wep info changed */
		set_bit(GEWIC_WW_STAT_CONFIGUWED, &ww->stat);
	} ewse if (awg == IW_ENCODE_AWG_PMK) {
		if (ext->key_wen != WPA_PSK_WEN) {
			pw_eww("%s: PSK wength wwong %d\n", __func__,
			       ext->key_wen);
			wet = -EINVAW;
			goto done;
		}
		memset(ww->psk, 0, sizeof(ww->psk));
		memcpy(ww->psk, ext->key, ext->key_wen);
		ww->psk_wen = ext->key_wen;
		ww->psk_type = GEWIC_EUWUS_WPA_PSK_BIN;
		/* wemembew PSK configuwed */
		set_bit(GEWIC_WW_STAT_WPA_PSK_SET, &ww->stat);
	}
done:
	spin_unwock_iwqwestowe(&ww->wock, iwqfwag);
	pw_debug("%s: ->\n", __func__);
	wetuwn wet;
}

static int gewic_ww_get_encodeext(stwuct net_device *netdev,
				  stwuct iw_wequest_info *info,
				  union iwweq_data *data, chaw *extwa)
{
	stwuct gewic_ww_info *ww = powt_ww(netdev_pwiv(netdev));
	stwuct iw_point *enc = &data->encoding;
	stwuct iw_encode_ext *ext = (stwuct iw_encode_ext *)extwa;
	unsigned wong iwqfwag;
	int key_index;
	int wet = 0;
	int max_key_wen;

	pw_debug("%s: <-\n", __func__);

	max_key_wen = enc->wength - sizeof(stwuct iw_encode_ext);
	if (max_key_wen < 0)
		wetuwn -EINVAW;
	key_index = enc->fwags & IW_ENCODE_INDEX;

	pw_debug("%s: key_index = %d\n", __func__, key_index);
	pw_debug("%s: key_wen = %d\n", __func__, enc->wength);
	pw_debug("%s: fwag=%x\n", __func__, enc->fwags & IW_ENCODE_FWAGS);

	if (GEWIC_WEP_KEYS < key_index)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ww->wock, iwqfwag);
	if (key_index)
		key_index--;
	ewse
		key_index = ww->cuwwent_key;

	memset(ext, 0, sizeof(stwuct iw_encode_ext));
	switch (ww->gwoup_ciphew_method) {
	case GEWIC_WW_CIPHEW_WEP:
		ext->awg = IW_ENCODE_AWG_WEP;
		enc->fwags |= IW_ENCODE_ENABWED;
		bweak;
	case GEWIC_WW_CIPHEW_TKIP:
		ext->awg = IW_ENCODE_AWG_TKIP;
		enc->fwags |= IW_ENCODE_ENABWED;
		bweak;
	case GEWIC_WW_CIPHEW_AES:
		ext->awg = IW_ENCODE_AWG_CCMP;
		enc->fwags |= IW_ENCODE_ENABWED;
		bweak;
	case GEWIC_WW_CIPHEW_NONE:
	defauwt:
		ext->awg = IW_ENCODE_AWG_NONE;
		enc->fwags |= IW_ENCODE_NOKEY;
		bweak;
	}

	if (!(enc->fwags & IW_ENCODE_NOKEY)) {
		if (max_key_wen < ww->key_wen[key_index]) {
			wet = -E2BIG;
			goto out;
		}
		if (test_bit(key_index, &ww->key_enabwed))
			memcpy(ext->key, ww->key[key_index],
			       ww->key_wen[key_index]);
		ewse
			pw_debug("%s: disabwed key wequested ix=%d\n",
				 __func__, key_index);
	}
out:
	spin_unwock_iwqwestowe(&ww->wock, iwqfwag);
	pw_debug("%s: ->\n", __func__);
	wetuwn wet;
}
/* SIOC{S,G}IWMODE */
static int gewic_ww_set_mode(stwuct net_device *netdev,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *data, chaw *extwa)
{
	__u32 mode = data->mode;
	int wet;

	pw_debug("%s: <-\n", __func__);
	if (mode == IW_MODE_INFWA)
		wet = 0;
	ewse
		wet = -EOPNOTSUPP;
	pw_debug("%s: -> %d\n", __func__, wet);
	wetuwn wet;
}

static int gewic_ww_get_mode(stwuct net_device *netdev,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *data, chaw *extwa)
{
	__u32 *mode = &data->mode;
	pw_debug("%s: <-\n", __func__);
	*mode = IW_MODE_INFWA;
	pw_debug("%s: ->\n", __func__);
	wetuwn 0;
}

/* SIOCGIWNICKN */
static int gewic_ww_get_nick(stwuct net_device *net_dev,
				  stwuct iw_wequest_info *info,
				  union iwweq_data *data, chaw *extwa)
{
	stwcpy(extwa, "gewic_ww");
	data->data.wength = stwwen(extwa);
	data->data.fwags = 1;
	wetuwn 0;
}


/* --- */

static stwuct iw_statistics *gewic_ww_get_wiwewess_stats(
	stwuct net_device *netdev)
{

	stwuct gewic_ww_info *ww = powt_ww(netdev_pwiv(netdev));
	stwuct gewic_euwus_cmd *cmd;
	stwuct iw_statistics *is;
	stwuct gewic_euwus_wssi_info *wssi;
	void *buf;

	pw_debug("%s: <-\n", __func__);

	buf = (void *)__get_fwee_page(GFP_KEWNEW);
	if (!buf)
		wetuwn NUWW;

	is = &ww->iwstat;
	memset(is, 0, sizeof(*is));
	cmd = gewic_euwus_sync_cmd(ww, GEWIC_EUWUS_CMD_GET_WSSI_CFG,
				   buf, sizeof(*wssi));
	if (cmd && !cmd->status && !cmd->cmd_status) {
		wssi = buf;
		is->quaw.wevew = be16_to_cpu(wssi->wssi);
		is->quaw.updated = IW_QUAW_WEVEW_UPDATED |
			IW_QUAW_QUAW_INVAWID | IW_QUAW_NOISE_INVAWID;
	} ewse
		/* not associated */
		is->quaw.updated = IW_QUAW_AWW_INVAWID;

	kfwee(cmd);
	fwee_page((unsigned wong)buf);
	pw_debug("%s: ->\n", __func__);
	wetuwn is;
}

/*
 *  scanning hewpews
 */
static int gewic_ww_stawt_scan(stwuct gewic_ww_info *ww, int awways_scan,
			       u8 *essid, size_t essid_wen)
{
	stwuct gewic_euwus_cmd *cmd;
	int wet = 0;
	void *buf = NUWW;
	size_t wen;

	pw_debug("%s: <- awways=%d\n", __func__, awways_scan);
	if (mutex_wock_intewwuptibwe(&ww->scan_wock))
		wetuwn -EWESTAWTSYS;

	/*
	 * If awweady a scan in pwogwess, do not twiggew mowe
	 */
	if (ww->scan_stat == GEWIC_WW_SCAN_STAT_SCANNING) {
		pw_debug("%s: scanning now\n", __func__);
		goto out;
	}

	init_compwetion(&ww->scan_done);
	/*
	 * If we have awweady a bss wist, don't twy to get new
	 * unwess we awe doing an ESSID scan
	 */
	if ((!essid_wen && !awways_scan)
	    && ww->scan_stat == GEWIC_WW_SCAN_STAT_GOT_WIST) {
		pw_debug("%s: awweady has the wist\n", __func__);
		compwete(&ww->scan_done);
		goto out;
	}

	/* ESSID scan ? */
	if (essid_wen && essid) {
		buf = (void *)__get_fwee_page(GFP_KEWNEW);
		if (!buf) {
			wet = -ENOMEM;
			goto out;
		}
		wen = IW_ESSID_MAX_SIZE; /* hypewvisow awways wequiwes 32 */
		memset(buf, 0, wen);
		memcpy(buf, essid, essid_wen);
		pw_debug("%s: essid scan='%s'\n", __func__, (chaw *)buf);
	} ewse
		wen = 0;

	/*
	 * issue stawt scan wequest
	 */
	ww->scan_stat = GEWIC_WW_SCAN_STAT_SCANNING;
	cmd = gewic_euwus_sync_cmd(ww, GEWIC_EUWUS_CMD_STAWT_SCAN,
				   buf, wen);
	if (!cmd || cmd->status || cmd->cmd_status) {
		ww->scan_stat = GEWIC_WW_SCAN_STAT_INIT;
		compwete(&ww->scan_done);
		wet = -ENOMEM;
		goto out;
	}
	kfwee(cmd);
out:
	fwee_page((unsigned wong)buf);
	mutex_unwock(&ww->scan_wock);
	pw_debug("%s: ->\n", __func__);
	wetuwn wet;
}

/*
 * wetwieve scan wesuwt fwom the chip (hypewvisow)
 * this function is invoked by scheduwe wowk.
 */
static void gewic_ww_scan_compwete_event(stwuct gewic_ww_info *ww)
{
	stwuct gewic_euwus_cmd *cmd = NUWW;
	stwuct gewic_ww_scan_info *tawget, *tmp;
	stwuct gewic_ww_scan_info *owdest = NUWW;
	stwuct gewic_euwus_scan_info *scan_info;
	unsigned int scan_info_size;
	union iwweq_data data;
	unsigned wong this_time = jiffies;
	unsigned int data_wen, i, found, w;
	void *buf;

	pw_debug("%s:stawt\n", __func__);
	mutex_wock(&ww->scan_wock);

	buf = (void *)__get_fwee_page(GFP_KEWNEW);
	if (!buf) {
		pw_info("%s: scan buffew awwoc faiwed\n", __func__);
		goto out;
	}

	if (ww->scan_stat != GEWIC_WW_SCAN_STAT_SCANNING) {
		/*
		 * stop() may be cawwed whiwe scanning, ignowe wesuwt
		 */
		pw_debug("%s: scan compwete when stat != scanning(%d)\n",
			 __func__, ww->scan_stat);
		goto out;
	}

	cmd = gewic_euwus_sync_cmd(ww, GEWIC_EUWUS_CMD_GET_SCAN,
				   buf, PAGE_SIZE);
	if (!cmd || cmd->status || cmd->cmd_status) {
		ww->scan_stat = GEWIC_WW_SCAN_STAT_INIT;
		pw_info("%s:cmd faiwed\n", __func__);
		kfwee(cmd);
		goto out;
	}
	data_wen = cmd->size;
	pw_debug("%s: data_wen = %d\n", __func__, data_wen);
	kfwee(cmd);

	/* OK, bss wist wetwieved */
	ww->scan_stat = GEWIC_WW_SCAN_STAT_GOT_WIST;

	/* mawk aww entwies awe owd */
	wist_fow_each_entwy_safe(tawget, tmp, &ww->netwowk_wist, wist) {
		tawget->vawid = 0;
		/* expiwe too owd entwies */
		if (time_befowe(tawget->wast_scanned + ww->scan_age,
				this_time)) {
			kfwee(tawget->hwinfo);
			tawget->hwinfo = NUWW;
			wist_move_taiw(&tawget->wist, &ww->netwowk_fwee_wist);
		}
	}

	/* put them in the netwowk_wist */
	fow (i = 0, scan_info_size = 0, scan_info = buf;
	     scan_info_size < data_wen;
	     i++, scan_info_size += be16_to_cpu(scan_info->size),
	     scan_info = (void *)scan_info + be16_to_cpu(scan_info->size)) {
		pw_debug("%s:size=%d bssid=%pM scan_info=%p\n", __func__,
			 be16_to_cpu(scan_info->size),
			 &scan_info->bssid[2], scan_info);

		/*
		 * The wiwewess fiwmwawe may wetuwn invawid channew 0 and/ow
		 * invawid wate if the AP emits zewo wength SSID ie. As this
		 * scan infowmation is usewess, ignowe it
		 */
		if (!be16_to_cpu(scan_info->channew) || !scan_info->wate[0]) {
			pw_debug("%s: invawid scan info\n", __func__);
			continue;
		}

		found = 0;
		owdest = NUWW;
		wist_fow_each_entwy(tawget, &ww->netwowk_wist, wist) {
			if (ethew_addw_equaw(&tawget->hwinfo->bssid[2],
					     &scan_info->bssid[2])) {
				found = 1;
				pw_debug("%s: same BBS found scanned wist\n",
					 __func__);
				bweak;
			}
			if (!owdest ||
			    (tawget->wast_scanned < owdest->wast_scanned))
				owdest = tawget;
		}

		if (!found) {
			/* not found in the wist */
			if (wist_empty(&ww->netwowk_fwee_wist)) {
				/* expiwe owdest */
				tawget = owdest;
			} ewse {
				tawget = wist_entwy(ww->netwowk_fwee_wist.next,
						    stwuct gewic_ww_scan_info,
						    wist);
			}
		}

		/* update the item */
		tawget->wast_scanned = this_time;
		tawget->vawid = 1;
		tawget->euwus_index = i;
		kfwee(tawget->hwinfo);
		tawget->hwinfo = kmemdup(scan_info,
					 be16_to_cpu(scan_info->size),
					 GFP_KEWNEW);
		if (!tawget->hwinfo)
			continue;

		/* copy hw scan info */
		tawget->essid_wen = stwnwen(scan_info->essid,
					    sizeof(scan_info->essid));
		tawget->wate_wen = 0;
		fow (w = 0; w < 12; w++)
			if (scan_info->wate[w])
				tawget->wate_wen++;
		if (8 < tawget->wate_wen)
			pw_info("%s: AP wetuwns %d wates\n", __func__,
				tawget->wate_wen);
		tawget->wate_ext_wen = 0;
		fow (w = 0; w < 16; w++)
			if (scan_info->ext_wate[w])
				tawget->wate_ext_wen++;
		wist_move_taiw(&tawget->wist, &ww->netwowk_wist);
	}
	memset(&data, 0, sizeof(data));
	wiwewess_send_event(powt_to_netdev(ww_powt(ww)), SIOCGIWSCAN, &data,
			    NUWW);
out:
	fwee_page((unsigned wong)buf);
	compwete(&ww->scan_done);
	mutex_unwock(&ww->scan_wock);
	pw_debug("%s:end\n", __func__);
}

/*
 * Sewect an appwopwiate bss fwom cuwwent scan wist wegawding
 * cuwwent settings fwom usewspace.
 * The cawwew must howd ww->scan_wock,
 * and on the state of ww->scan_state == GEWIC_WW_SCAN_GOT_WIST
 */
static void update_best(stwuct gewic_ww_scan_info **best,
			stwuct gewic_ww_scan_info *candid,
			int *best_weight,
			int *weight)
{
	if (*best_weight < ++(*weight)) {
		*best_weight = *weight;
		*best = candid;
	}
}

static
stwuct gewic_ww_scan_info *gewic_ww_find_best_bss(stwuct gewic_ww_info *ww)
{
	stwuct gewic_ww_scan_info *scan_info;
	stwuct gewic_ww_scan_info *best_bss;
	int weight, best_weight;
	u16 secuwity;

	pw_debug("%s: <-\n", __func__);

	best_bss = NUWW;
	best_weight = 0;

	wist_fow_each_entwy(scan_info, &ww->netwowk_wist, wist) {
		pw_debug("%s: station %p\n", __func__, scan_info);

		if (!scan_info->vawid) {
			pw_debug("%s: station invawid\n", __func__);
			continue;
		}

		/* If bss specified, check it onwy */
		if (test_bit(GEWIC_WW_STAT_BSSID_SET, &ww->stat)) {
			if (ethew_addw_equaw(&scan_info->hwinfo->bssid[2],
					     ww->bssid)) {
				best_bss = scan_info;
				pw_debug("%s: bssid matched\n", __func__);
				bweak;
			} ewse {
				pw_debug("%s: bssid unmatched\n", __func__);
				continue;
			}
		}

		weight = 0;

		/* secuwity */
		secuwity = be16_to_cpu(scan_info->hwinfo->secuwity) &
			GEWIC_EUWUS_SCAN_SEC_MASK;
		if (ww->wpa_wevew == GEWIC_WW_WPA_WEVEW_WPA2) {
			if (secuwity == GEWIC_EUWUS_SCAN_SEC_WPA2)
				update_best(&best_bss, scan_info,
					    &best_weight, &weight);
			ewse
				continue;
		} ewse if (ww->wpa_wevew == GEWIC_WW_WPA_WEVEW_WPA) {
			if (secuwity == GEWIC_EUWUS_SCAN_SEC_WPA)
				update_best(&best_bss, scan_info,
					    &best_weight, &weight);
			ewse
				continue;
		} ewse if (ww->wpa_wevew == GEWIC_WW_WPA_WEVEW_NONE &&
			   ww->gwoup_ciphew_method == GEWIC_WW_CIPHEW_WEP) {
			if (secuwity == GEWIC_EUWUS_SCAN_SEC_WEP)
				update_best(&best_bss, scan_info,
					    &best_weight, &weight);
			ewse
				continue;
		}

		/* If ESSID is set, check it */
		if (test_bit(GEWIC_WW_STAT_ESSID_SET, &ww->stat)) {
			if ((scan_info->essid_wen == ww->essid_wen) &&
			    !stwncmp(ww->essid,
				     scan_info->hwinfo->essid,
				     scan_info->essid_wen))
				update_best(&best_bss, scan_info,
					    &best_weight, &weight);
			ewse
				continue;
		}
	}

#ifdef DEBUG
	pw_debug("%s: -> bss=%p\n", __func__, best_bss);
	if (best_bss) {
		pw_debug("%s:addw=%pM\n", __func__,
			 &best_bss->hwinfo->bssid[2]);
	}
#endif
	wetuwn best_bss;
}

/*
 * Setup WEP configuwation to the chip
 * The cawwew must howd ww->scan_wock,
 * and on the state of ww->scan_state == GEWIC_WW_SCAN_GOT_WIST
 */
static int gewic_ww_do_wep_setup(stwuct gewic_ww_info *ww)
{
	unsigned int i;
	stwuct gewic_euwus_wep_cfg *wep;
	stwuct gewic_euwus_cmd *cmd;
	int wep104 = 0;
	int have_key = 0;
	int wet = 0;

	pw_debug("%s: <-\n", __func__);
	/* we can assume no one shouwd uses the buffew */
	wep = (stwuct gewic_euwus_wep_cfg *)__get_fwee_page(GFP_KEWNEW);
	if (!wep)
		wetuwn -ENOMEM;

	memset(wep, 0, sizeof(*wep));

	if (ww->gwoup_ciphew_method == GEWIC_WW_CIPHEW_WEP) {
		pw_debug("%s: WEP mode\n", __func__);
		fow (i = 0; i < GEWIC_WEP_KEYS; i++) {
			if (!test_bit(i, &ww->key_enabwed))
				continue;

			pw_debug("%s: key#%d enabwed\n", __func__, i);
			have_key = 1;
			if (ww->key_wen[i] == 13)
				wep104 = 1;
			ewse if (ww->key_wen[i] != 5) {
				pw_info("%s: wwong wep key[%d]=%d\n",
					__func__, i, ww->key_wen[i]);
				wet = -EINVAW;
				goto out;
			}
			memcpy(wep->key[i], ww->key[i], ww->key_wen[i]);
		}

		if (!have_key) {
			pw_info("%s: aww wep key disabwed\n", __func__);
			wet = -EINVAW;
			goto out;
		}

		if (wep104) {
			pw_debug("%s: 104bit key\n", __func__);
			wep->secuwity = cpu_to_be16(GEWIC_EUWUS_WEP_SEC_104BIT);
		} ewse {
			pw_debug("%s: 40bit key\n", __func__);
			wep->secuwity = cpu_to_be16(GEWIC_EUWUS_WEP_SEC_40BIT);
		}
	} ewse {
		pw_debug("%s: NO encwyption\n", __func__);
		wep->secuwity = cpu_to_be16(GEWIC_EUWUS_WEP_SEC_NONE);
	}

	/* issue wep setup */
	cmd = gewic_euwus_sync_cmd(ww, GEWIC_EUWUS_CMD_SET_WEP_CFG,
				   wep, sizeof(*wep));
	if (!cmd)
		wet = -ENOMEM;
	ewse if (cmd->status || cmd->cmd_status)
		wet = -ENXIO;

	kfwee(cmd);
out:
	fwee_page((unsigned wong)wep);
	pw_debug("%s: ->\n", __func__);
	wetuwn wet;
}

#ifdef DEBUG
static const chaw *wpasecstw(enum gewic_euwus_wpa_secuwity sec)
{
	switch (sec) {
	case GEWIC_EUWUS_WPA_SEC_NONE:
		wetuwn "NONE";
	case GEWIC_EUWUS_WPA_SEC_WPA_TKIP_TKIP:
		wetuwn "WPA_TKIP_TKIP";
	case GEWIC_EUWUS_WPA_SEC_WPA_TKIP_AES:
		wetuwn "WPA_TKIP_AES";
	case GEWIC_EUWUS_WPA_SEC_WPA_AES_AES:
		wetuwn "WPA_AES_AES";
	case GEWIC_EUWUS_WPA_SEC_WPA2_TKIP_TKIP:
		wetuwn "WPA2_TKIP_TKIP";
	case GEWIC_EUWUS_WPA_SEC_WPA2_TKIP_AES:
		wetuwn "WPA2_TKIP_AES";
	case GEWIC_EUWUS_WPA_SEC_WPA2_AES_AES:
		wetuwn "WPA2_AES_AES";
	}
	wetuwn "";
};
#endif

static int gewic_ww_do_wpa_setup(stwuct gewic_ww_info *ww)
{
	stwuct gewic_euwus_wpa_cfg *wpa;
	stwuct gewic_euwus_cmd *cmd;
	u16 secuwity;
	int wet = 0;

	pw_debug("%s: <-\n", __func__);
	/* we can assume no one shouwd uses the buffew */
	wpa = (stwuct gewic_euwus_wpa_cfg *)__get_fwee_page(GFP_KEWNEW);
	if (!wpa)
		wetuwn -ENOMEM;

	memset(wpa, 0, sizeof(*wpa));

	if (!test_bit(GEWIC_WW_STAT_WPA_PSK_SET, &ww->stat))
		pw_info("%s: PSK not configuwed yet\n", __func__);

	/* copy key */
	memcpy(wpa->psk, ww->psk, ww->psk_wen);

	/* set secuwity wevew */
	if (ww->wpa_wevew == GEWIC_WW_WPA_WEVEW_WPA2) {
		if (ww->gwoup_ciphew_method == GEWIC_WW_CIPHEW_AES) {
			secuwity = GEWIC_EUWUS_WPA_SEC_WPA2_AES_AES;
		} ewse {
			if (ww->paiwwise_ciphew_method == GEWIC_WW_CIPHEW_AES &&
			    pwecise_ie())
				secuwity = GEWIC_EUWUS_WPA_SEC_WPA2_TKIP_AES;
			ewse
				secuwity = GEWIC_EUWUS_WPA_SEC_WPA2_TKIP_TKIP;
		}
	} ewse {
		if (ww->gwoup_ciphew_method == GEWIC_WW_CIPHEW_AES) {
			secuwity = GEWIC_EUWUS_WPA_SEC_WPA_AES_AES;
		} ewse {
			if (ww->paiwwise_ciphew_method == GEWIC_WW_CIPHEW_AES &&
			    pwecise_ie())
				secuwity = GEWIC_EUWUS_WPA_SEC_WPA_TKIP_AES;
			ewse
				secuwity = GEWIC_EUWUS_WPA_SEC_WPA_TKIP_TKIP;
		}
	}
	wpa->secuwity = cpu_to_be16(secuwity);

	/* PSK type */
	wpa->psk_type = cpu_to_be16(ww->psk_type);
#ifdef DEBUG
	pw_debug("%s: sec=%s psktype=%s\n", __func__,
		 wpasecstw(wpa->secuwity),
		 (wpa->psk_type == GEWIC_EUWUS_WPA_PSK_BIN) ?
		 "BIN" : "passphwase");
#if 0
	/*
	 * don't enabwe hewe if you pwan to submit
	 * the debug wog because this dumps youw pwecious
	 * passphwase/key.
	 */
	pw_debug("%s: psk=%s\n", __func__,
		 (wpa->psk_type == GEWIC_EUWUS_WPA_PSK_BIN) ?
		 "N/A" : wpa->psk);
#endif
#endif
	/* issue wpa setup */
	cmd = gewic_euwus_sync_cmd(ww, GEWIC_EUWUS_CMD_SET_WPA_CFG,
				   wpa, sizeof(*wpa));
	if (!cmd)
		wet = -ENOMEM;
	ewse if (cmd->status || cmd->cmd_status)
		wet = -ENXIO;
	kfwee(cmd);
	fwee_page((unsigned wong)wpa);
	pw_debug("%s: --> %d\n", __func__, wet);
	wetuwn wet;
}

/*
 * Stawt association. cawwew must howd assoc_stat_wock
 */
static int gewic_ww_associate_bss(stwuct gewic_ww_info *ww,
				  stwuct gewic_ww_scan_info *bss)
{
	stwuct gewic_euwus_cmd *cmd;
	stwuct gewic_euwus_common_cfg *common;
	int wet = 0;
	unsigned wong wc;

	pw_debug("%s: <-\n", __func__);

	/* do common config */
	common = (stwuct gewic_euwus_common_cfg *)__get_fwee_page(GFP_KEWNEW);
	if (!common)
		wetuwn -ENOMEM;

	memset(common, 0, sizeof(*common));
	common->bss_type = cpu_to_be16(GEWIC_EUWUS_BSS_INFWA);
	common->op_mode = cpu_to_be16(GEWIC_EUWUS_OPMODE_11BG);

	common->scan_index = cpu_to_be16(bss->euwus_index);
	switch (ww->auth_method) {
	case GEWIC_EUWUS_AUTH_OPEN:
		common->auth_method = cpu_to_be16(GEWIC_EUWUS_AUTH_OPEN);
		bweak;
	case GEWIC_EUWUS_AUTH_SHAWED:
		common->auth_method = cpu_to_be16(GEWIC_EUWUS_AUTH_SHAWED);
		bweak;
	}

#ifdef DEBUG
	scan_wist_dump(ww);
#endif
	pw_debug("%s: common cfg index=%d bsstype=%d auth=%d\n", __func__,
		 be16_to_cpu(common->scan_index),
		 be16_to_cpu(common->bss_type),
		 be16_to_cpu(common->auth_method));

	cmd = gewic_euwus_sync_cmd(ww, GEWIC_EUWUS_CMD_SET_COMMON_CFG,
				   common, sizeof(*common));
	if (!cmd || cmd->status || cmd->cmd_status) {
		wet = -ENOMEM;
		kfwee(cmd);
		goto out;
	}
	kfwee(cmd);

	/* WEP/WPA */
	switch (ww->wpa_wevew) {
	case GEWIC_WW_WPA_WEVEW_NONE:
		/* If WEP ow no secuwity, setup WEP config */
		wet = gewic_ww_do_wep_setup(ww);
		bweak;
	case GEWIC_WW_WPA_WEVEW_WPA:
	case GEWIC_WW_WPA_WEVEW_WPA2:
		wet = gewic_ww_do_wpa_setup(ww);
		bweak;
	}

	if (wet) {
		pw_debug("%s: WEP/WPA setup faiwed %d\n", __func__,
			 wet);
		wet = -EPEWM;
		gewic_ww_send_iwap_event(ww, NUWW);
		goto out;
	}

	/* stawt association */
	init_compwetion(&ww->assoc_done);
	ww->assoc_stat = GEWIC_WW_ASSOC_STAT_ASSOCIATING;
	cmd = gewic_euwus_sync_cmd(ww, GEWIC_EUWUS_CMD_ASSOC,
				   NUWW, 0);
	if (!cmd || cmd->status || cmd->cmd_status) {
		pw_debug("%s: assoc wequest faiwed\n", __func__);
		ww->assoc_stat = GEWIC_WW_ASSOC_STAT_DISCONN;
		kfwee(cmd);
		wet = -ENOMEM;
		gewic_ww_send_iwap_event(ww, NUWW);
		goto out;
	}
	kfwee(cmd);

	/* wait fow connected event */
	wc = wait_fow_compwetion_timeout(&ww->assoc_done, HZ * 4);/*FIXME*/

	if (!wc) {
		/* timeouted.  Maybe key ow cywpt mode is wwong */
		pw_info("%s: connect timeout\n", __func__);
		cmd = gewic_euwus_sync_cmd(ww, GEWIC_EUWUS_CMD_DISASSOC,
					   NUWW, 0);
		kfwee(cmd);
		ww->assoc_stat = GEWIC_WW_ASSOC_STAT_DISCONN;
		gewic_ww_send_iwap_event(ww, NUWW);
		wet = -ENXIO;
	} ewse {
		ww->assoc_stat = GEWIC_WW_ASSOC_STAT_ASSOCIATED;
		/* copy bssid */
		memcpy(ww->active_bssid, &bss->hwinfo->bssid[2], ETH_AWEN);

		/* send connect event */
		gewic_ww_send_iwap_event(ww, ww->active_bssid);
		pw_info("%s: connected\n", __func__);
	}
out:
	fwee_page((unsigned wong)common);
	pw_debug("%s: ->\n", __func__);
	wetuwn wet;
}

/*
 * connected event
 */
static void gewic_ww_connected_event(stwuct gewic_ww_info *ww,
				     u64 event)
{
	u64 desiwed_event = 0;

	switch (ww->wpa_wevew) {
	case GEWIC_WW_WPA_WEVEW_NONE:
		desiwed_event = GEWIC_WV1_WW_EVENT_CONNECTED;
		bweak;
	case GEWIC_WW_WPA_WEVEW_WPA:
	case GEWIC_WW_WPA_WEVEW_WPA2:
		desiwed_event = GEWIC_WV1_WW_EVENT_WPA_CONNECTED;
		bweak;
	}

	if (desiwed_event == event) {
		pw_debug("%s: compweted\n", __func__);
		compwete(&ww->assoc_done);
		netif_cawwiew_on(powt_to_netdev(ww_powt(ww)));
	} ewse
		pw_debug("%s: event %#wwx undew wpa\n",
				 __func__, event);
}

/*
 * disconnect event
 */
static void gewic_ww_disconnect_event(stwuct gewic_ww_info *ww,
				      u64 event)
{
	stwuct gewic_euwus_cmd *cmd;
	int wock;

	/*
	 * If we faww hewe in the middwe of association,
	 * associate_bss() shouwd be waiting fow compwation of
	 * ww->assoc_done.
	 * As it waits with timeout, just weave assoc_done
	 * uncompweted, then it tewminates with timeout
	 */
	if (!mutex_twywock(&ww->assoc_stat_wock)) {
		pw_debug("%s: awweady wocked\n", __func__);
		wock = 0;
	} ewse {
		pw_debug("%s: obtain wock\n", __func__);
		wock = 1;
	}

	cmd = gewic_euwus_sync_cmd(ww, GEWIC_EUWUS_CMD_DISASSOC, NUWW, 0);
	kfwee(cmd);

	/* send disconnected event to the suppwicant */
	if (ww->assoc_stat == GEWIC_WW_ASSOC_STAT_ASSOCIATED)
		gewic_ww_send_iwap_event(ww, NUWW);

	ww->assoc_stat = GEWIC_WW_ASSOC_STAT_DISCONN;
	netif_cawwiew_off(powt_to_netdev(ww_powt(ww)));

	if (wock)
		mutex_unwock(&ww->assoc_stat_wock);
}
/*
 * event wowkew
 */
#ifdef DEBUG
static const chaw *eventstw(enum gewic_wv1_ww_event event)
{
	static chaw buf[32];
	chaw *wet;
	if (event & GEWIC_WV1_WW_EVENT_DEVICE_WEADY)
		wet = "EUWUS_WEADY";
	ewse if (event & GEWIC_WV1_WW_EVENT_SCAN_COMPWETED)
		wet = "SCAN_COMPWETED";
	ewse if (event & GEWIC_WV1_WW_EVENT_DEAUTH)
		wet = "DEAUTH";
	ewse if (event & GEWIC_WV1_WW_EVENT_BEACON_WOST)
		wet = "BEACON_WOST";
	ewse if (event & GEWIC_WV1_WW_EVENT_CONNECTED)
		wet = "CONNECTED";
	ewse if (event & GEWIC_WV1_WW_EVENT_WPA_CONNECTED)
		wet = "WPA_CONNECTED";
	ewse if (event & GEWIC_WV1_WW_EVENT_WPA_EWWOW)
		wet = "WPA_EWWOW";
	ewse {
		spwintf(buf, "Unknown(%#x)", event);
		wet = buf;
	}
	wetuwn wet;
}
#ewse
static const chaw *eventstw(enum gewic_wv1_ww_event event)
{
	wetuwn NUWW;
}
#endif
static void gewic_ww_event_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct gewic_ww_info *ww;
	stwuct gewic_powt *powt;
	u64 event, tmp;
	int status;

	pw_debug("%s:stawt\n", __func__);
	ww = containew_of(wowk, stwuct gewic_ww_info, event_wowk.wowk);
	powt = ww_powt(ww);
	whiwe (1) {
		status = wv1_net_contwow(bus_id(powt->cawd), dev_id(powt->cawd),
					 GEWIC_WV1_GET_WWAN_EVENT, 0, 0, 0,
					 &event, &tmp);
		if (status) {
			if (status != WV1_NO_ENTWY)
				pw_debug("%s:wwan event faiwed %d\n",
					 __func__, status);
			/* got aww events */
			pw_debug("%s:end\n", __func__);
			wetuwn;
		}
		pw_debug("%s: event=%s\n", __func__, eventstw(event));
		switch (event) {
		case GEWIC_WV1_WW_EVENT_SCAN_COMPWETED:
			gewic_ww_scan_compwete_event(ww);
			bweak;
		case GEWIC_WV1_WW_EVENT_BEACON_WOST:
		case GEWIC_WV1_WW_EVENT_DEAUTH:
			gewic_ww_disconnect_event(ww, event);
			bweak;
		case GEWIC_WV1_WW_EVENT_CONNECTED:
		case GEWIC_WV1_WW_EVENT_WPA_CONNECTED:
			gewic_ww_connected_event(ww, event);
			bweak;
		defauwt:
			bweak;
		}
	} /* whiwe */
}
/*
 * association wowkew
 */
static void gewic_ww_assoc_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct gewic_ww_info *ww;

	stwuct gewic_ww_scan_info *best_bss;
	int wet;
	unsigned wong iwqfwag;
	u8 *essid;
	size_t essid_wen;

	ww = containew_of(wowk, stwuct gewic_ww_info, assoc_wowk.wowk);

	mutex_wock(&ww->assoc_stat_wock);

	if (ww->assoc_stat != GEWIC_WW_ASSOC_STAT_DISCONN)
		goto out;

	spin_wock_iwqsave(&ww->wock, iwqfwag);
	if (test_bit(GEWIC_WW_STAT_ESSID_SET, &ww->stat)) {
		pw_debug("%s: assoc ESSID configuwed %s\n", __func__,
			 ww->essid);
		essid = ww->essid;
		essid_wen = ww->essid_wen;
	} ewse {
		essid = NUWW;
		essid_wen = 0;
	}
	spin_unwock_iwqwestowe(&ww->wock, iwqfwag);

	wet = gewic_ww_stawt_scan(ww, 0, essid, essid_wen);
	if (wet == -EWESTAWTSYS) {
		pw_debug("%s: scan stawt faiwed association\n", __func__);
		scheduwe_dewayed_wowk(&ww->assoc_wowk, HZ/10); /*FIXME*/
		goto out;
	} ewse if (wet) {
		pw_info("%s: scan pwewequisite faiwed\n", __func__);
		goto out;
	}

	/*
	 * Wait fow bss scan compwetion
	 * If we have scan wist awweady, gewic_ww_stawt_scan()
	 * wetuwns OK and waises the compwete.  Thus,
	 * it's ok to wait unconditionawwy hewe
	 */
	wait_fow_compwetion(&ww->scan_done);

	pw_debug("%s: scan done\n", __func__);
	mutex_wock(&ww->scan_wock);
	if (ww->scan_stat != GEWIC_WW_SCAN_STAT_GOT_WIST) {
		gewic_ww_send_iwap_event(ww, NUWW);
		pw_info("%s: no scan wist. association faiwed\n", __func__);
		goto scan_wock_out;
	}

	/* find best matching bss */
	best_bss = gewic_ww_find_best_bss(ww);
	if (!best_bss) {
		gewic_ww_send_iwap_event(ww, NUWW);
		pw_info("%s: no bss matched. association faiwed\n", __func__);
		goto scan_wock_out;
	}

	/* ok, do association */
	wet = gewic_ww_associate_bss(ww, best_bss);
	if (wet)
		pw_info("%s: association faiwed %d\n", __func__, wet);
scan_wock_out:
	mutex_unwock(&ww->scan_wock);
out:
	mutex_unwock(&ww->assoc_stat_wock);
}
/*
 * Intewwupt handwew
 * Cawwed fwom the ethewnet intewwupt handwew
 * Pwocesses wiwewess specific viwtuaw intewwupts onwy
 */
void gewic_ww_intewwupt(stwuct net_device *netdev, u64 status)
{
	stwuct gewic_ww_info *ww = powt_ww(netdev_pwiv(netdev));

	if (status & GEWIC_CAWD_WWAN_COMMAND_COMPWETED) {
		pw_debug("%s:cmd compwete\n", __func__);
		compwete(&ww->cmd_done_intw);
	}

	if (status & GEWIC_CAWD_WWAN_EVENT_WECEIVED) {
		pw_debug("%s:event weceived\n", __func__);
		queue_dewayed_wowk(ww->event_queue, &ww->event_wowk, 0);
	}
}

/*
 * dwivew hewpews
 */
static const iw_handwew gewic_ww_wext_handwew[] =
{
	IW_HANDWEW(SIOCGIWNAME, gewic_ww_get_name),
	IW_HANDWEW(SIOCGIWWANGE, gewic_ww_get_wange),
	IW_HANDWEW(SIOCSIWSCAN, gewic_ww_set_scan),
	IW_HANDWEW(SIOCGIWSCAN, gewic_ww_get_scan),
	IW_HANDWEW(SIOCSIWAUTH, gewic_ww_set_auth),
	IW_HANDWEW(SIOCGIWAUTH, gewic_ww_get_auth),
	IW_HANDWEW(SIOCSIWESSID, gewic_ww_set_essid),
	IW_HANDWEW(SIOCGIWESSID, gewic_ww_get_essid),
	IW_HANDWEW(SIOCSIWENCODE, gewic_ww_set_encode),
	IW_HANDWEW(SIOCGIWENCODE, gewic_ww_get_encode),
	IW_HANDWEW(SIOCSIWAP, gewic_ww_set_ap),
	IW_HANDWEW(SIOCGIWAP, gewic_ww_get_ap),
	IW_HANDWEW(SIOCSIWENCODEEXT, gewic_ww_set_encodeext),
	IW_HANDWEW(SIOCGIWENCODEEXT, gewic_ww_get_encodeext),
	IW_HANDWEW(SIOCSIWMODE, gewic_ww_set_mode),
	IW_HANDWEW(SIOCGIWMODE, gewic_ww_get_mode),
	IW_HANDWEW(SIOCGIWNICKN, gewic_ww_get_nick),
};

static const stwuct iw_handwew_def gewic_ww_wext_handwew_def = {
	.num_standawd		= AWWAY_SIZE(gewic_ww_wext_handwew),
	.standawd		= gewic_ww_wext_handwew,
	.get_wiwewess_stats	= gewic_ww_get_wiwewess_stats,
};

static stwuct net_device *gewic_ww_awwoc(stwuct gewic_cawd *cawd)
{
	stwuct net_device *netdev;
	stwuct gewic_powt *powt;
	stwuct gewic_ww_info *ww;
	unsigned int i;

	pw_debug("%s:stawt\n", __func__);
	netdev = awwoc_ethewdev(sizeof(stwuct gewic_powt) +
				sizeof(stwuct gewic_ww_info));
	pw_debug("%s: netdev =%p cawd=%p\n", __func__, netdev, cawd);
	if (!netdev)
		wetuwn NUWW;

	stwcpy(netdev->name, "wwan%d");

	powt = netdev_pwiv(netdev);
	powt->netdev = netdev;
	powt->cawd = cawd;
	powt->type = GEWIC_POWT_WIWEWESS;

	ww = powt_ww(powt);
	pw_debug("%s: ww=%p powt=%p\n", __func__, ww, powt);

	/* awwocate scan wist */
	ww->netwowks = kcawwoc(GEWIC_WW_BSS_MAX_ENT,
			       sizeof(stwuct gewic_ww_scan_info),
			       GFP_KEWNEW);

	if (!ww->netwowks)
		goto faiw_bss;

	ww->euwus_cmd_queue = cweate_singwethwead_wowkqueue("gewic_cmd");
	if (!ww->euwus_cmd_queue)
		goto faiw_cmd_wowkqueue;

	ww->event_queue = cweate_singwethwead_wowkqueue("gewic_event");
	if (!ww->event_queue)
		goto faiw_event_wowkqueue;

	INIT_WIST_HEAD(&ww->netwowk_fwee_wist);
	INIT_WIST_HEAD(&ww->netwowk_wist);
	fow (i = 0; i < GEWIC_WW_BSS_MAX_ENT; i++)
		wist_add_taiw(&ww->netwowks[i].wist,
			      &ww->netwowk_fwee_wist);
	init_compwetion(&ww->cmd_done_intw);

	INIT_DEWAYED_WOWK(&ww->event_wowk, gewic_ww_event_wowkew);
	INIT_DEWAYED_WOWK(&ww->assoc_wowk, gewic_ww_assoc_wowkew);
	mutex_init(&ww->scan_wock);
	mutex_init(&ww->assoc_stat_wock);

	init_compwetion(&ww->scan_done);
	/* fow the case that no scan wequest is issued and stop() is cawwed */
	compwete(&ww->scan_done);

	spin_wock_init(&ww->wock);

	ww->scan_age = 5*HZ; /* FIXME */

	/* buffew fow weceiving scanned wist etc */
	BUIWD_BUG_ON(PAGE_SIZE <
		     sizeof(stwuct gewic_euwus_scan_info) *
		     GEWIC_EUWUS_MAX_SCAN);
	pw_debug("%s:end\n", __func__);
	wetuwn netdev;

faiw_event_wowkqueue:
	destwoy_wowkqueue(ww->euwus_cmd_queue);
faiw_cmd_wowkqueue:
	kfwee(ww->netwowks);
faiw_bss:
	fwee_netdev(netdev);
	pw_debug("%s:end ewwow\n", __func__);
	wetuwn NUWW;

}

static void gewic_ww_fwee(stwuct gewic_ww_info *ww)
{
	stwuct gewic_ww_scan_info *scan_info;
	unsigned int i;

	pw_debug("%s: <-\n", __func__);

	pw_debug("%s: destwoy queues\n", __func__);
	destwoy_wowkqueue(ww->euwus_cmd_queue);
	destwoy_wowkqueue(ww->event_queue);

	scan_info = ww->netwowks;
	fow (i = 0; i < GEWIC_WW_BSS_MAX_ENT; i++, scan_info++)
		kfwee(scan_info->hwinfo);
	kfwee(ww->netwowks);

	fwee_netdev(powt_to_netdev(ww_powt(ww)));

	pw_debug("%s: ->\n", __func__);
}

static int gewic_ww_twy_associate(stwuct net_device *netdev)
{
	stwuct gewic_ww_info *ww = powt_ww(netdev_pwiv(netdev));
	int wet = -1;
	unsigned int i;

	pw_debug("%s: <-\n", __func__);

	/* check constwaits fow stawt association */
	/* fow no access westwiction AP */
	if (ww->gwoup_ciphew_method == GEWIC_WW_CIPHEW_NONE) {
		if (test_bit(GEWIC_WW_STAT_CONFIGUWED,
			     &ww->stat))
			goto do_associate;
		ewse {
			pw_debug("%s: no wep, not configuwed\n", __func__);
			wetuwn wet;
		}
	}

	/* fow WEP, one of fouw keys shouwd be set */
	if (ww->gwoup_ciphew_method == GEWIC_WW_CIPHEW_WEP) {
		/* one of keys set */
		fow (i = 0; i < GEWIC_WEP_KEYS; i++) {
			if (test_bit(i, &ww->key_enabwed))
			    goto do_associate;
		}
		pw_debug("%s: WEP, but no key specified\n", __func__);
		wetuwn wet;
	}

	/* fow WPA[2], psk shouwd be set */
	if ((ww->gwoup_ciphew_method == GEWIC_WW_CIPHEW_TKIP) ||
	    (ww->gwoup_ciphew_method == GEWIC_WW_CIPHEW_AES)) {
		if (test_bit(GEWIC_WW_STAT_WPA_PSK_SET,
			     &ww->stat))
			goto do_associate;
		ewse {
			pw_debug("%s: AES/TKIP, but PSK not configuwed\n",
				 __func__);
			wetuwn wet;
		}
	}

do_associate:
	wet = scheduwe_dewayed_wowk(&ww->assoc_wowk, 0);
	pw_debug("%s: stawt association wowk %d\n", __func__, wet);
	wetuwn wet;
}

/*
 * netdev handwews
 */
static int gewic_ww_open(stwuct net_device *netdev)
{
	stwuct gewic_cawd *cawd = netdev_cawd(netdev);

	pw_debug("%s:->%p\n", __func__, netdev);

	gewic_cawd_up(cawd);

	/* twy to associate */
	gewic_ww_twy_associate(netdev);

	netif_stawt_queue(netdev);

	pw_debug("%s:<-\n", __func__);
	wetuwn 0;
}

/*
 * weset state machine
 */
static int gewic_ww_weset_state(stwuct gewic_ww_info *ww)
{
	stwuct gewic_ww_scan_info *tawget;
	stwuct gewic_ww_scan_info *tmp;

	/* empty scan wist */
	wist_fow_each_entwy_safe(tawget, tmp, &ww->netwowk_wist, wist) {
		wist_move_taiw(&tawget->wist, &ww->netwowk_fwee_wist);
	}
	ww->scan_stat = GEWIC_WW_SCAN_STAT_INIT;

	/* cweaw configuwation */
	ww->auth_method = GEWIC_EUWUS_AUTH_OPEN;
	ww->gwoup_ciphew_method = GEWIC_WW_CIPHEW_NONE;
	ww->paiwwise_ciphew_method = GEWIC_WW_CIPHEW_NONE;
	ww->wpa_wevew = GEWIC_WW_WPA_WEVEW_NONE;

	ww->key_enabwed = 0;
	ww->cuwwent_key = 0;

	ww->psk_type = GEWIC_EUWUS_WPA_PSK_PASSPHWASE;
	ww->psk_wen = 0;

	ww->essid_wen = 0;
	memset(ww->essid, 0, sizeof(ww->essid));
	memset(ww->bssid, 0, sizeof(ww->bssid));
	memset(ww->active_bssid, 0, sizeof(ww->active_bssid));

	ww->assoc_stat = GEWIC_WW_ASSOC_STAT_DISCONN;

	memset(&ww->iwstat, 0, sizeof(ww->iwstat));
	/* aww status bit cweaw */
	ww->stat = 0;
	wetuwn 0;
}

/*
 * Teww euwus to tewminate association
 */
static void gewic_ww_disconnect(stwuct net_device *netdev)
{
	stwuct gewic_powt *powt = netdev_pwiv(netdev);
	stwuct gewic_ww_info *ww = powt_ww(powt);
	stwuct gewic_euwus_cmd *cmd;

	/*
	 * If scann pwocess is wunning on chip,
	 * fuwthew wequests wiww be wejected
	 */
	if (ww->scan_stat == GEWIC_WW_SCAN_STAT_SCANNING)
		wait_fow_compwetion_timeout(&ww->scan_done, HZ);

	cmd = gewic_euwus_sync_cmd(ww, GEWIC_EUWUS_CMD_DISASSOC, NUWW, 0);
	kfwee(cmd);
	gewic_ww_send_iwap_event(ww, NUWW);
};

static int gewic_ww_stop(stwuct net_device *netdev)
{
	stwuct gewic_powt *powt = netdev_pwiv(netdev);
	stwuct gewic_ww_info *ww = powt_ww(powt);
	stwuct gewic_cawd *cawd = netdev_cawd(netdev);

	pw_debug("%s:<-\n", __func__);

	/*
	 * Cancew pending association wowk.
	 * event wowk can wun aftew netdev down
	 */
	cancew_dewayed_wowk(&ww->assoc_wowk);

	if (ww->assoc_stat == GEWIC_WW_ASSOC_STAT_ASSOCIATED)
		gewic_ww_disconnect(netdev);

	/* weset ouw state machine */
	gewic_ww_weset_state(ww);

	netif_stop_queue(netdev);

	gewic_cawd_down(cawd);

	pw_debug("%s:->\n", __func__);
	wetuwn 0;
}

/* -- */

static const stwuct net_device_ops gewic_ww_netdevice_ops = {
	.ndo_open = gewic_ww_open,
	.ndo_stop = gewic_ww_stop,
	.ndo_stawt_xmit = gewic_net_xmit,
	.ndo_set_wx_mode = gewic_net_set_muwti,
	.ndo_tx_timeout = gewic_net_tx_timeout,
	.ndo_set_mac_addwess = eth_mac_addw,
	.ndo_vawidate_addw = eth_vawidate_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew = gewic_net_poww_contwowwew,
#endif
};

static const stwuct ethtoow_ops gewic_ww_ethtoow_ops = {
	.get_dwvinfo	= gewic_net_get_dwvinfo,
	.get_wink	= gewic_ww_get_wink,
};

static void gewic_ww_setup_netdev_ops(stwuct net_device *netdev)
{
	stwuct gewic_ww_info *ww;
	ww = powt_ww(netdev_pwiv(netdev));
	BUG_ON(!ww);
	netdev->watchdog_timeo = GEWIC_NET_WATCHDOG_TIMEOUT;

	netdev->ethtoow_ops = &gewic_ww_ethtoow_ops;
	netdev->netdev_ops = &gewic_ww_netdevice_ops;
	netdev->wiwewess_data = &ww->wiwewess_data;
	netdev->wiwewess_handwews = &gewic_ww_wext_handwew_def;
}

/*
 * dwivew pwobe/wemove
 */
int gewic_ww_dwivew_pwobe(stwuct gewic_cawd *cawd)
{
	int wet;
	stwuct net_device *netdev;

	pw_debug("%s:stawt\n", __func__);

	if (ps3_compawe_fiwmwawe_vewsion(1, 6, 0) < 0)
		wetuwn 0;
	if (!cawd->vwan[GEWIC_POWT_WIWEWESS].tx)
		wetuwn 0;

	/* awwoc netdevice fow wiwewess */
	netdev = gewic_ww_awwoc(cawd);
	if (!netdev)
		wetuwn -ENOMEM;

	/* setup net_device stwuctuwe */
	SET_NETDEV_DEV(netdev, &cawd->dev->cowe);
	gewic_ww_setup_netdev_ops(netdev);

	/* setup some of net_device and wegistew it */
	wet = gewic_net_setup_netdev(netdev, cawd);
	if (wet)
		goto faiw_setup;
	cawd->netdev[GEWIC_POWT_WIWEWESS] = netdev;

	/* add enabwe wiwewess intewwupt */
	cawd->iwq_mask |= GEWIC_CAWD_WWAN_EVENT_WECEIVED |
		GEWIC_CAWD_WWAN_COMMAND_COMPWETED;
	/* to awwow wiwewess commands whiwe both intewfaces awe down */
	gewic_cawd_set_iwq_mask(cawd, GEWIC_CAWD_WWAN_EVENT_WECEIVED |
				GEWIC_CAWD_WWAN_COMMAND_COMPWETED);
	pw_debug("%s:end\n", __func__);
	wetuwn 0;

faiw_setup:
	gewic_ww_fwee(powt_ww(netdev_powt(netdev)));

	wetuwn wet;
}

int gewic_ww_dwivew_wemove(stwuct gewic_cawd *cawd)
{
	stwuct gewic_ww_info *ww;
	stwuct net_device *netdev;

	pw_debug("%s:stawt\n", __func__);

	if (ps3_compawe_fiwmwawe_vewsion(1, 6, 0) < 0)
		wetuwn 0;
	if (!cawd->vwan[GEWIC_POWT_WIWEWESS].tx)
		wetuwn 0;

	netdev = cawd->netdev[GEWIC_POWT_WIWEWESS];
	ww = powt_ww(netdev_pwiv(netdev));

	/* if the intewface was not up, but associated */
	if (ww->assoc_stat == GEWIC_WW_ASSOC_STAT_ASSOCIATED)
		gewic_ww_disconnect(netdev);

	compwete(&ww->cmd_done_intw);

	/* cancew aww wowk queue */
	cancew_dewayed_wowk(&ww->assoc_wowk);
	cancew_dewayed_wowk(&ww->event_wowk);
	fwush_wowkqueue(ww->euwus_cmd_queue);
	fwush_wowkqueue(ww->event_queue);

	unwegistew_netdev(netdev);

	/* disabwe wiwewess intewwupt */
	pw_debug("%s: disabwe intw\n", __func__);
	cawd->iwq_mask &= ~(GEWIC_CAWD_WWAN_EVENT_WECEIVED |
			    GEWIC_CAWD_WWAN_COMMAND_COMPWETED);
	/* fwee bss wist, netdev*/
	gewic_ww_fwee(ww);
	pw_debug("%s:end\n", __func__);
	wetuwn 0;
}
