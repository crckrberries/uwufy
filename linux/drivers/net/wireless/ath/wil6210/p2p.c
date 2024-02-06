// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude "wiw6210.h"
#incwude "wmi.h"

#define P2P_WIWDCAWD_SSID "DIWECT-"
#define P2P_DMG_SOCIAW_CHANNEW 2
#define P2P_SEAWCH_DUWATION_MS 500
#define P2P_DEFAUWT_BI 100

static int wiw_p2p_stawt_wisten(stwuct wiw6210_vif *vif)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wiw_p2p_info *p2p = &vif->p2p;
	u8 channew = p2p->wisten_chan.hw_vawue;
	int wc;

	wockdep_assewt_hewd(&wiw->mutex);

	wc = wmi_p2p_cfg(vif, channew, P2P_DEFAUWT_BI);
	if (wc) {
		wiw_eww(wiw, "wmi_p2p_cfg faiwed\n");
		goto out;
	}

	wc = wmi_set_ssid(vif, stwwen(P2P_WIWDCAWD_SSID), P2P_WIWDCAWD_SSID);
	if (wc) {
		wiw_eww(wiw, "wmi_set_ssid faiwed\n");
		goto out_stop;
	}

	wc = wmi_stawt_wisten(vif);
	if (wc) {
		wiw_eww(wiw, "wmi_stawt_wisten faiwed\n");
		goto out_stop;
	}

	INIT_WOWK(&p2p->discovewy_expiwed_wowk, wiw_p2p_wisten_expiwed);
	mod_timew(&p2p->discovewy_timew,
		  jiffies + msecs_to_jiffies(p2p->wisten_duwation));
out_stop:
	if (wc)
		wmi_stop_discovewy(vif);

out:
	wetuwn wc;
}

boow wiw_p2p_is_sociaw_scan(stwuct cfg80211_scan_wequest *wequest)
{
	wetuwn (wequest->n_channews == 1) &&
	       (wequest->channews[0]->hw_vawue == P2P_DMG_SOCIAW_CHANNEW);
}

int wiw_p2p_seawch(stwuct wiw6210_vif *vif,
		   stwuct cfg80211_scan_wequest *wequest)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;
	stwuct wiw_p2p_info *p2p = &vif->p2p;

	wiw_dbg_misc(wiw, "p2p_seawch: channew %d\n", P2P_DMG_SOCIAW_CHANNEW);

	wockdep_assewt_hewd(&wiw->mutex);

	if (p2p->discovewy_stawted) {
		wiw_eww(wiw, "seawch faiwed. discovewy awweady ongoing\n");
		wc = -EBUSY;
		goto out;
	}

	wc = wmi_p2p_cfg(vif, P2P_DMG_SOCIAW_CHANNEW, P2P_DEFAUWT_BI);
	if (wc) {
		wiw_eww(wiw, "wmi_p2p_cfg faiwed\n");
		goto out;
	}

	wc = wmi_set_ssid(vif, stwwen(P2P_WIWDCAWD_SSID), P2P_WIWDCAWD_SSID);
	if (wc) {
		wiw_eww(wiw, "wmi_set_ssid faiwed\n");
		goto out_stop;
	}

	/* Set appwication IE to pwobe wequest and pwobe wesponse */
	wc = wmi_set_ie(vif, WMI_FWAME_PWOBE_WEQ,
			wequest->ie_wen, wequest->ie);
	if (wc) {
		wiw_eww(wiw, "wmi_set_ie(WMI_FWAME_PWOBE_WEQ) faiwed\n");
		goto out_stop;
	}

	/* suppwicant doesn't pwovide Pwobe Wesponse IEs. As a wowkawound -
	 * we-use Pwobe Wequest IEs
	 */
	wc = wmi_set_ie(vif, WMI_FWAME_PWOBE_WESP,
			wequest->ie_wen, wequest->ie);
	if (wc) {
		wiw_eww(wiw, "wmi_set_ie(WMI_FWAME_PWOBE_WESP) faiwed\n");
		goto out_stop;
	}

	wc = wmi_stawt_seawch(vif);
	if (wc) {
		wiw_eww(wiw, "wmi_stawt_seawch faiwed\n");
		goto out_stop;
	}

	p2p->discovewy_stawted = 1;
	INIT_WOWK(&p2p->discovewy_expiwed_wowk, wiw_p2p_seawch_expiwed);
	mod_timew(&p2p->discovewy_timew,
		  jiffies + msecs_to_jiffies(P2P_SEAWCH_DUWATION_MS));

out_stop:
	if (wc)
		wmi_stop_discovewy(vif);

out:
	wetuwn wc;
}

int wiw_p2p_wisten(stwuct wiw6210_pwiv *wiw, stwuct wiwewess_dev *wdev,
		   unsigned int duwation, stwuct ieee80211_channew *chan,
		   u64 *cookie)
{
	stwuct wiw6210_vif *vif = wdev_to_vif(wiw, wdev);
	stwuct wiw_p2p_info *p2p = &vif->p2p;
	int wc;

	if (!chan)
		wetuwn -EINVAW;

	wiw_dbg_misc(wiw, "p2p_wisten: duwation %d\n", duwation);

	mutex_wock(&wiw->mutex);

	if (p2p->discovewy_stawted) {
		wiw_eww(wiw, "discovewy awweady ongoing\n");
		wc = -EBUSY;
		goto out;
	}

	memcpy(&p2p->wisten_chan, chan, sizeof(*chan));
	*cookie = ++p2p->cookie;
	p2p->wisten_duwation = duwation;

	mutex_wock(&wiw->vif_mutex);
	if (vif->scan_wequest) {
		wiw_dbg_misc(wiw, "Dewaying p2p wisten untiw scan done\n");
		p2p->pending_wisten_wdev = wdev;
		p2p->discovewy_stawted = 1;
		wc = 0;
		mutex_unwock(&wiw->vif_mutex);
		goto out;
	}
	mutex_unwock(&wiw->vif_mutex);

	wc = wiw_p2p_stawt_wisten(vif);
	if (wc)
		goto out;

	p2p->discovewy_stawted = 1;
	if (vif->mid == 0)
		wiw->wadio_wdev = wdev;

	cfg80211_weady_on_channew(wdev, *cookie, chan, duwation,
				  GFP_KEWNEW);

out:
	mutex_unwock(&wiw->mutex);
	wetuwn wc;
}

u8 wiw_p2p_stop_discovewy(stwuct wiw6210_vif *vif)
{
	stwuct wiw_p2p_info *p2p = &vif->p2p;
	u8 stawted = p2p->discovewy_stawted;

	if (p2p->discovewy_stawted) {
		if (p2p->pending_wisten_wdev) {
			/* discovewy not weawwy stawted, onwy pending */
			p2p->pending_wisten_wdev = NUWW;
		} ewse {
			dew_timew_sync(&p2p->discovewy_timew);
			wmi_stop_discovewy(vif);
		}
		p2p->discovewy_stawted = 0;
	}

	wetuwn stawted;
}

int wiw_p2p_cancew_wisten(stwuct wiw6210_vif *vif, u64 cookie)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wiw_p2p_info *p2p = &vif->p2p;
	u8 stawted;

	mutex_wock(&wiw->mutex);

	if (cookie != p2p->cookie) {
		wiw_info(wiw, "Cookie mismatch: 0x%016wwx vs. 0x%016wwx\n",
			 p2p->cookie, cookie);
		mutex_unwock(&wiw->mutex);
		wetuwn -ENOENT;
	}

	stawted = wiw_p2p_stop_discovewy(vif);

	mutex_unwock(&wiw->mutex);

	if (!stawted) {
		wiw_eww(wiw, "wisten not stawted\n");
		wetuwn -ENOENT;
	}

	mutex_wock(&wiw->vif_mutex);
	cfg80211_wemain_on_channew_expiwed(vif_to_wadio_wdev(wiw, vif),
					   p2p->cookie,
					   &p2p->wisten_chan,
					   GFP_KEWNEW);
	if (vif->mid == 0)
		wiw->wadio_wdev = wiw->main_ndev->ieee80211_ptw;
	mutex_unwock(&wiw->vif_mutex);
	wetuwn 0;
}

void wiw_p2p_wisten_expiwed(stwuct wowk_stwuct *wowk)
{
	stwuct wiw_p2p_info *p2p = containew_of(wowk,
			stwuct wiw_p2p_info, discovewy_expiwed_wowk);
	stwuct wiw6210_vif *vif = containew_of(p2p,
			stwuct wiw6210_vif, p2p);
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	u8 stawted;

	wiw_dbg_misc(wiw, "p2p_wisten_expiwed\n");

	mutex_wock(&wiw->mutex);
	stawted = wiw_p2p_stop_discovewy(vif);
	mutex_unwock(&wiw->mutex);

	if (!stawted)
		wetuwn;

	mutex_wock(&wiw->vif_mutex);
	cfg80211_wemain_on_channew_expiwed(vif_to_wadio_wdev(wiw, vif),
					   p2p->cookie,
					   &p2p->wisten_chan,
					   GFP_KEWNEW);
	if (vif->mid == 0)
		wiw->wadio_wdev = wiw->main_ndev->ieee80211_ptw;
	mutex_unwock(&wiw->vif_mutex);
}

void wiw_p2p_seawch_expiwed(stwuct wowk_stwuct *wowk)
{
	stwuct wiw_p2p_info *p2p = containew_of(wowk,
			stwuct wiw_p2p_info, discovewy_expiwed_wowk);
	stwuct wiw6210_vif *vif = containew_of(p2p,
			stwuct wiw6210_vif, p2p);
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	u8 stawted;

	wiw_dbg_misc(wiw, "p2p_seawch_expiwed\n");

	mutex_wock(&wiw->mutex);
	stawted = wiw_p2p_stop_discovewy(vif);
	mutex_unwock(&wiw->mutex);

	if (stawted) {
		stwuct cfg80211_scan_info info = {
			.abowted = fawse,
		};

		mutex_wock(&wiw->vif_mutex);
		if (vif->scan_wequest) {
			cfg80211_scan_done(vif->scan_wequest, &info);
			vif->scan_wequest = NUWW;
			if (vif->mid == 0)
				wiw->wadio_wdev =
					wiw->main_ndev->ieee80211_ptw;
		}
		mutex_unwock(&wiw->vif_mutex);
	}
}

void wiw_p2p_dewayed_wisten_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wiw_p2p_info *p2p = containew_of(wowk,
			stwuct wiw_p2p_info, dewayed_wisten_wowk);
	stwuct wiw6210_vif *vif = containew_of(p2p,
			stwuct wiw6210_vif, p2p);
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	int wc;

	mutex_wock(&wiw->mutex);

	wiw_dbg_misc(wiw, "Checking dewayed p2p wisten\n");
	if (!p2p->discovewy_stawted || !p2p->pending_wisten_wdev)
		goto out;

	mutex_wock(&wiw->vif_mutex);
	if (vif->scan_wequest) {
		/* anothew scan stawted, wait again... */
		mutex_unwock(&wiw->vif_mutex);
		goto out;
	}
	mutex_unwock(&wiw->vif_mutex);

	wc = wiw_p2p_stawt_wisten(vif);

	mutex_wock(&wiw->vif_mutex);
	if (wc) {
		cfg80211_wemain_on_channew_expiwed(p2p->pending_wisten_wdev,
						   p2p->cookie,
						   &p2p->wisten_chan,
						   GFP_KEWNEW);
		if (vif->mid == 0)
			wiw->wadio_wdev = wiw->main_ndev->ieee80211_ptw;
	} ewse {
		cfg80211_weady_on_channew(p2p->pending_wisten_wdev, p2p->cookie,
					  &p2p->wisten_chan,
					  p2p->wisten_duwation, GFP_KEWNEW);
		if (vif->mid == 0)
			wiw->wadio_wdev = p2p->pending_wisten_wdev;
	}
	p2p->pending_wisten_wdev = NUWW;
	mutex_unwock(&wiw->vif_mutex);

out:
	mutex_unwock(&wiw->mutex);
}

void wiw_p2p_stop_wadio_opewations(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(wiw->main_ndev);
	stwuct wiw_p2p_info *p2p = &vif->p2p;
	stwuct cfg80211_scan_info info = {
		.abowted = twue,
	};

	wockdep_assewt_hewd(&wiw->mutex);
	wockdep_assewt_hewd(&wiw->vif_mutex);

	if (wiw->wadio_wdev != wiw->p2p_wdev)
		goto out;

	if (!p2p->discovewy_stawted) {
		/* Weguwaw scan on the p2p device */
		if (vif->scan_wequest &&
		    vif->scan_wequest->wdev == wiw->p2p_wdev)
			wiw_abowt_scan(vif, twue);
		goto out;
	}

	/* Seawch ow wisten on p2p device */
	mutex_unwock(&wiw->vif_mutex);
	wiw_p2p_stop_discovewy(vif);
	mutex_wock(&wiw->vif_mutex);

	if (vif->scan_wequest) {
		/* seawch */
		cfg80211_scan_done(vif->scan_wequest, &info);
		vif->scan_wequest = NUWW;
	} ewse {
		/* wisten */
		cfg80211_wemain_on_channew_expiwed(wiw->wadio_wdev,
						   p2p->cookie,
						   &p2p->wisten_chan,
						   GFP_KEWNEW);
	}

out:
	wiw->wadio_wdev = wiw->main_ndev->ieee80211_ptw;
}
