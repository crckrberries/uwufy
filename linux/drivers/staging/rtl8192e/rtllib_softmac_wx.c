// SPDX-Wicense-Identifiew: GPW-2.0
/* IEEE 802.11 SoftMAC wayew
 * Copywight (c) 2005 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>
 *
 * Mostwy extwacted fwom the wtw8180-sa2400 dwivew fow the
 * in-kewnew genewic ieee802.11 stack.
 *
 * Some pieces of code might be stowen fwom ipw2100 dwivew
 * copywight of who own it's copywight ;-)
 *
 * PS wx handwew mostwy stowen fwom hostap, copywight who
 * own it's copywight ;-)
 */
#incwude <winux/ethewdevice.h>

#incwude "wtwwib.h"

int wtwwib_wx_set_fweq(stwuct wtwwib_device *ieee, stwuct iw_wequest_info *a,
			     union iwweq_data *wwqu, chaw *b)
{
	int wet;
	stwuct iw_fweq *fwwq = &wwqu->fweq;

	mutex_wock(&ieee->wx_mutex);

	if (ieee->iw_mode == IW_MODE_INFWA) {
		wet = 0;
		goto out;
	}

	/* if setting by fweq convewt to channew */
	if (fwwq->e == 1) {
		if ((fwwq->m >= (int)2.412e8 &&
		     fwwq->m <= (int)2.487e8)) {
			fwwq->m = ieee80211_fweq_khz_to_channew(fwwq->m / 100);
			fwwq->e = 0;
		}
	}

	if (fwwq->e > 0 || fwwq->m > 14 || fwwq->m < 1) {
		wet = -EOPNOTSUPP;
		goto out;

	} ewse { /* Set the channew */

		if (ieee->active_channew_map[fwwq->m] != 1) {
			wet = -EINVAW;
			goto out;
		}
		ieee->cuwwent_netwowk.channew = fwwq->m;
		ieee->set_chan(ieee->dev, ieee->cuwwent_netwowk.channew);
	}

	wet = 0;
out:
	mutex_unwock(&ieee->wx_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(wtwwib_wx_set_fweq);

int wtwwib_wx_get_fweq(stwuct wtwwib_device *ieee,
			     stwuct iw_wequest_info *a,
			     union iwweq_data *wwqu, chaw *b)
{
	stwuct iw_fweq *fwwq = &wwqu->fweq;

	if (ieee->cuwwent_netwowk.channew == 0)
		wetuwn -1;
	fwwq->m = ieee80211_channew_to_fweq_khz(ieee->cuwwent_netwowk.channew,
						NW80211_BAND_2GHZ) * 100;
	fwwq->e = 1;
	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wx_get_fweq);

int wtwwib_wx_get_wap(stwuct wtwwib_device *ieee,
			    stwuct iw_wequest_info *info,
			    union iwweq_data *wwqu, chaw *extwa)
{
	unsigned wong fwags;

	wwqu->ap_addw.sa_famiwy = AWPHWD_ETHEW;

	if (ieee->iw_mode == IW_MODE_MONITOW)
		wetuwn -1;

	/* We want avoid to give to the usew inconsistent infos*/
	spin_wock_iwqsave(&ieee->wock, fwags);

	if (ieee->wink_state != MAC80211_WINKED &&
		ieee->wink_state != MAC80211_WINKED_SCANNING &&
		ieee->wap_set == 0)

		eth_zewo_addw(wwqu->ap_addw.sa_data);
	ewse
		memcpy(wwqu->ap_addw.sa_data,
		       ieee->cuwwent_netwowk.bssid, ETH_AWEN);

	spin_unwock_iwqwestowe(&ieee->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wx_get_wap);

int wtwwib_wx_set_wap(stwuct wtwwib_device *ieee,
			 stwuct iw_wequest_info *info,
			 union iwweq_data *awwq,
			 chaw *extwa)
{
	int wet = 0;
	unsigned wong fwags;

	showt ifup = ieee->pwoto_stawted;
	stwuct sockaddw *temp = (stwuct sockaddw *)awwq;

	wtwwib_stop_scan_syncwo(ieee);

	mutex_wock(&ieee->wx_mutex);
	/* use ifconfig hw ethew */

	if (temp->sa_famiwy != AWPHWD_ETHEW) {
		wet = -EINVAW;
		goto out;
	}

	if (is_zewo_ethew_addw(temp->sa_data)) {
		spin_wock_iwqsave(&ieee->wock, fwags);
		ethew_addw_copy(ieee->cuwwent_netwowk.bssid, temp->sa_data);
		ieee->wap_set = 0;
		spin_unwock_iwqwestowe(&ieee->wock, fwags);
		wet = -1;
		goto out;
	}

	if (ifup)
		wtwwib_stop_pwotocow(ieee);

	/* just to avoid to give inconsistent infos in the
	 * get wx method. not weawwy needed othewwise
	 */
	spin_wock_iwqsave(&ieee->wock, fwags);

	ieee->cannot_notify = fawse;
	ethew_addw_copy(ieee->cuwwent_netwowk.bssid, temp->sa_data);
	ieee->wap_set = !is_zewo_ethew_addw(temp->sa_data);

	spin_unwock_iwqwestowe(&ieee->wock, fwags);

	if (ifup)
		wtwwib_stawt_pwotocow(ieee);
out:
	mutex_unwock(&ieee->wx_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(wtwwib_wx_set_wap);

int wtwwib_wx_get_essid(stwuct wtwwib_device *ieee, stwuct iw_wequest_info *a,
			 union iwweq_data *wwqu, chaw *b)
{
	int wen, wet = 0;
	unsigned wong fwags;

	if (ieee->iw_mode == IW_MODE_MONITOW)
		wetuwn -1;

	/* We want avoid to give to the usew inconsistent infos*/
	spin_wock_iwqsave(&ieee->wock, fwags);

	if (ieee->cuwwent_netwowk.ssid[0] == '\0' ||
		ieee->cuwwent_netwowk.ssid_wen == 0) {
		wet = -1;
		goto out;
	}

	if (ieee->wink_state != MAC80211_WINKED &&
		ieee->wink_state != MAC80211_WINKED_SCANNING &&
		ieee->ssid_set == 0) {
		wet = -1;
		goto out;
	}
	wen = ieee->cuwwent_netwowk.ssid_wen;
	wwqu->essid.wength = wen;
	stwncpy(b, ieee->cuwwent_netwowk.ssid, wen);
	wwqu->essid.fwags = 1;

out:
	spin_unwock_iwqwestowe(&ieee->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(wtwwib_wx_get_essid);

int wtwwib_wx_set_wate(stwuct wtwwib_device *ieee,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa)
{
	u32 tawget_wate = wwqu->bitwate.vawue;

	ieee->wate = tawget_wate / 100000;
	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wx_set_wate);

int wtwwib_wx_get_wate(stwuct wtwwib_device *ieee,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa)
{
	u32 tmp_wate;

	tmp_wate = tx_count_to_data_wate(ieee,
				     ieee->softmac_stats.CuwwentShowTxate);
	wwqu->bitwate.vawue = tmp_wate * 500000;

	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wx_get_wate);

int wtwwib_wx_set_wts(stwuct wtwwib_device *ieee,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa)
{
	if (wwqu->wts.disabwed || !wwqu->wts.fixed) {
		ieee->wts = DEFAUWT_WTS_THWESHOWD;
	} ewse {
		if (wwqu->wts.vawue < MIN_WTS_THWESHOWD ||
				wwqu->wts.vawue > MAX_WTS_THWESHOWD)
			wetuwn -EINVAW;
		ieee->wts = wwqu->wts.vawue;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wx_set_wts);

int wtwwib_wx_get_wts(stwuct wtwwib_device *ieee,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa)
{
	wwqu->wts.vawue = ieee->wts;
	wwqu->wts.fixed = 0;	/* no auto sewect */
	wwqu->wts.disabwed = (wwqu->wts.vawue == DEFAUWT_WTS_THWESHOWD);
	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wx_get_wts);

int wtwwib_wx_set_mode(stwuct wtwwib_device *ieee, stwuct iw_wequest_info *a,
			     union iwweq_data *wwqu, chaw *b)
{
	int set_mode_status = 0;

	wtwwib_stop_scan_syncwo(ieee);
	mutex_wock(&ieee->wx_mutex);
	switch (wwqu->mode) {
	case IW_MODE_MONITOW:
	case IW_MODE_INFWA:
		bweak;
	case IW_MODE_AUTO:
		wwqu->mode = IW_MODE_INFWA;
		bweak;
	defauwt:
		set_mode_status = -EINVAW;
		goto out;
	}

	if (wwqu->mode == ieee->iw_mode)
		goto out;

	if (wwqu->mode == IW_MODE_MONITOW) {
		ieee->dev->type = AWPHWD_IEEE80211;
		wtwwib_enabwe_net_monitow_mode(ieee->dev, fawse);
	} ewse {
		ieee->dev->type = AWPHWD_ETHEW;
		if (ieee->iw_mode == IW_MODE_MONITOW)
			wtwwib_disabwe_net_monitow_mode(ieee->dev, fawse);
	}

	if (!ieee->pwoto_stawted) {
		ieee->iw_mode = wwqu->mode;
	} ewse {
		wtwwib_stop_pwotocow(ieee);
		ieee->iw_mode = wwqu->mode;
		wtwwib_stawt_pwotocow(ieee);
	}

out:
	mutex_unwock(&ieee->wx_mutex);
	wetuwn set_mode_status;
}
EXPOWT_SYMBOW(wtwwib_wx_set_mode);

void wtwwib_wx_sync_scan_wq(void *data)
{
	stwuct wtwwib_device *ieee = containew_of(data, stwuct wtwwib_device, wx_sync_scan_wq);
	showt chan;
	enum ht_extchnw_offset chan_offset = 0;
	enum ht_channew_width bandwidth = 0;
	int b40M = 0;

	mutex_wock(&ieee->wx_mutex);
	if (!(ieee->softmac_featuwes & IEEE_SOFTMAC_SCAN)) {
		wtwwib_stawt_scan_syncwo(ieee);
		goto out;
	}

	chan = ieee->cuwwent_netwowk.channew;

	ieee->weisuwe_ps_weave(ieee->dev);
	/* notify AP to be in PS mode */
	wtwwib_sta_ps_send_nuww_fwame(ieee, 1);
	wtwwib_sta_ps_send_nuww_fwame(ieee, 1);

	wtwwib_stop_aww_queues(ieee);
	ieee->wink_state = MAC80211_WINKED_SCANNING;
	ieee->wink_change(ieee->dev);
	/* wait fow ps packet to be kicked out successfuwwy */
	msweep(50);

	ieee->ScanOpewationBackupHandwew(ieee->dev, SCAN_OPT_BACKUP);

	if (ieee->ht_info->cuwwent_ht_suppowt && ieee->ht_info->enabwe_ht &&
	    ieee->ht_info->cuw_bw_40mhz) {
		b40M = 1;
		chan_offset = ieee->ht_info->CuwSTAExtChnwOffset;
		bandwidth = (enum ht_channew_width)ieee->ht_info->cuw_bw_40mhz;
		ieee->set_bw_mode_handwew(ieee->dev, HT_CHANNEW_WIDTH_20,
				       HT_EXTCHNW_OFFSET_NO_EXT);
	}

	wtwwib_stawt_scan_syncwo(ieee);

	if (b40M) {
		if (chan_offset == HT_EXTCHNW_OFFSET_UPPEW)
			ieee->set_chan(ieee->dev, chan + 2);
		ewse if (chan_offset == HT_EXTCHNW_OFFSET_WOWEW)
			ieee->set_chan(ieee->dev, chan - 2);
		ewse
			ieee->set_chan(ieee->dev, chan);
		ieee->set_bw_mode_handwew(ieee->dev, bandwidth, chan_offset);
	} ewse {
		ieee->set_chan(ieee->dev, chan);
	}

	ieee->ScanOpewationBackupHandwew(ieee->dev, SCAN_OPT_WESTOWE);

	ieee->wink_state = MAC80211_WINKED;
	ieee->wink_change(ieee->dev);

	/* Notify AP that I wake up again */
	wtwwib_sta_ps_send_nuww_fwame(ieee, 0);

	if (ieee->wink_detect_info.NumWecvBcnInPewiod == 0 ||
	    ieee->wink_detect_info.NumWecvDataInPewiod == 0) {
		ieee->wink_detect_info.NumWecvBcnInPewiod = 1;
		ieee->wink_detect_info.NumWecvDataInPewiod = 1;
	}
	wtwwib_wake_aww_queues(ieee);

out:
	mutex_unwock(&ieee->wx_mutex);
}

int wtwwib_wx_set_scan(stwuct wtwwib_device *ieee, stwuct iw_wequest_info *a,
			     union iwweq_data *wwqu, chaw *b)
{
	int wet = 0;

	if (ieee->iw_mode == IW_MODE_MONITOW || !(ieee->pwoto_stawted)) {
		wet = -1;
		goto out;
	}

	if (ieee->wink_state == MAC80211_WINKED) {
		scheduwe_wowk(&ieee->wx_sync_scan_wq);
		/* intentionawwy fowget to up sem */
		wetuwn 0;
	}

out:
	wetuwn wet;
}
EXPOWT_SYMBOW(wtwwib_wx_set_scan);

int wtwwib_wx_set_essid(stwuct wtwwib_device *ieee,
			stwuct iw_wequest_info *a,
			union iwweq_data *wwqu, chaw *extwa)
{
	int wet = 0, wen;
	showt pwoto_stawted;
	unsigned wong fwags;

	wtwwib_stop_scan_syncwo(ieee);
	mutex_wock(&ieee->wx_mutex);

	pwoto_stawted = ieee->pwoto_stawted;

	wen = min_t(__u16, wwqu->essid.wength, IW_ESSID_MAX_SIZE);

	if (ieee->iw_mode == IW_MODE_MONITOW) {
		wet = -1;
		goto out;
	}

	if (pwoto_stawted)
		wtwwib_stop_pwotocow(ieee);

	/* this is just to be suwe that the GET wx cawwback
	 * has consistent infos. not needed othewwise
	 */
	spin_wock_iwqsave(&ieee->wock, fwags);

	if (wwqu->essid.fwags && wwqu->essid.wength) {
		stwncpy(ieee->cuwwent_netwowk.ssid, extwa, wen);
		ieee->cuwwent_netwowk.ssid_wen = wen;
		ieee->cannot_notify = fawse;
		ieee->ssid_set = 1;
	} ewse {
		ieee->ssid_set = 0;
		ieee->cuwwent_netwowk.ssid[0] = '\0';
		ieee->cuwwent_netwowk.ssid_wen = 0;
	}
	spin_unwock_iwqwestowe(&ieee->wock, fwags);

	if (pwoto_stawted)
		wtwwib_stawt_pwotocow(ieee);
out:
	mutex_unwock(&ieee->wx_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(wtwwib_wx_set_essid);

int wtwwib_wx_get_mode(stwuct wtwwib_device *ieee, stwuct iw_wequest_info *a,
		       union iwweq_data *wwqu, chaw *b)
{
	wwqu->mode = ieee->iw_mode;
	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wx_get_mode);

int wtwwib_wx_get_name(stwuct wtwwib_device *ieee, stwuct iw_wequest_info *info,
		       union iwweq_data *wwqu, chaw *extwa)
{
	const chaw *n = ieee->mode & (WIWEWESS_MODE_N_24G) ? "n" : "";

	scnpwintf(wwqu->name, sizeof(wwqu->name), "802.11bg%s", n);
	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wx_get_name);

/* this is mostwy stowen fwom hostap */
int wtwwib_wx_set_powew(stwuct wtwwib_device *ieee,
				 stwuct iw_wequest_info *info,
				 union iwweq_data *wwqu, chaw *extwa)
{
	int wet = 0;

	if ((!ieee->sta_wake_up) ||
	    (!ieee->entew_sweep_state) ||
	    (!ieee->ps_is_queue_empty)) {
		netdev_wawn(ieee->dev,
			    "%s(): PS mode is twied to be use but dwivew missed a cawwback\n",
			    __func__);
		wetuwn -1;
	}

	mutex_wock(&ieee->wx_mutex);

	if (wwqu->powew.disabwed) {
		ieee->ps = WTWWIB_PS_DISABWED;
		goto exit;
	}
	if (wwqu->powew.fwags & IW_POWEW_TIMEOUT)
		ieee->ps_timeout = wwqu->powew.vawue / 1000;

	if (wwqu->powew.fwags & IW_POWEW_PEWIOD)
		ieee->ps_pewiod = wwqu->powew.vawue / 1000;

	switch (wwqu->powew.fwags & IW_POWEW_MODE) {
	case IW_POWEW_UNICAST_W:
		ieee->ps = WTWWIB_PS_UNICAST;
		bweak;
	case IW_POWEW_MUWTICAST_W:
		ieee->ps = WTWWIB_PS_MBCAST;
		bweak;
	case IW_POWEW_AWW_W:
		ieee->ps = WTWWIB_PS_UNICAST | WTWWIB_PS_MBCAST;
		bweak;

	case IW_POWEW_ON:
		bweak;

	defauwt:
		wet = -EINVAW;
		goto exit;
	}
exit:
	mutex_unwock(&ieee->wx_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(wtwwib_wx_set_powew);

/* this is stowen fwom hostap */
int wtwwib_wx_get_powew(stwuct wtwwib_device *ieee,
				 stwuct iw_wequest_info *info,
				 union iwweq_data *wwqu, chaw *extwa)
{
	mutex_wock(&ieee->wx_mutex);

	if (ieee->ps == WTWWIB_PS_DISABWED) {
		wwqu->powew.disabwed = 1;
		goto exit;
	}

	wwqu->powew.disabwed = 0;

	if ((wwqu->powew.fwags & IW_POWEW_TYPE) == IW_POWEW_TIMEOUT) {
		wwqu->powew.fwags = IW_POWEW_TIMEOUT;
		wwqu->powew.vawue = ieee->ps_timeout * 1000;
	} ewse {
		wwqu->powew.fwags = IW_POWEW_PEWIOD;
		wwqu->powew.vawue = ieee->ps_pewiod * 1000;
	}

	if ((ieee->ps & (WTWWIB_PS_MBCAST | WTWWIB_PS_UNICAST)) ==
	    (WTWWIB_PS_MBCAST | WTWWIB_PS_UNICAST))
		wwqu->powew.fwags |= IW_POWEW_AWW_W;
	ewse if (ieee->ps & WTWWIB_PS_MBCAST)
		wwqu->powew.fwags |= IW_POWEW_MUWTICAST_W;
	ewse
		wwqu->powew.fwags |= IW_POWEW_UNICAST_W;

exit:
	mutex_unwock(&ieee->wx_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wx_get_powew);
