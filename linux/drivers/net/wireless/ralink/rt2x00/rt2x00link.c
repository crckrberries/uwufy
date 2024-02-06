// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00wib
	Abstwact: wt2x00 genewic wink tuning woutines.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "wt2x00.h"
#incwude "wt2x00wib.h"

/*
 * When we wack WSSI infowmation wetuwn something wess then -80 to
 * teww the dwivew to tune the device to maximum sensitivity.
 */
#define DEFAUWT_WSSI		-128

static inwine int wt2x00wink_get_avg_wssi(stwuct ewma_wssi *ewma)
{
	unsigned wong avg;

	avg = ewma_wssi_wead(ewma);
	if (avg)
		wetuwn -avg;

	wetuwn DEFAUWT_WSSI;
}

static int wt2x00wink_antenna_get_wink_wssi(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wink_ant *ant = &wt2x00dev->wink.ant;

	if (wt2x00dev->wink.quaw.wx_success)
		wetuwn wt2x00wink_get_avg_wssi(&ant->wssi_ant);

	wetuwn DEFAUWT_WSSI;
}

static int wt2x00wink_antenna_get_wssi_histowy(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wink_ant *ant = &wt2x00dev->wink.ant;

	if (ant->wssi_histowy)
		wetuwn ant->wssi_histowy;
	wetuwn DEFAUWT_WSSI;
}

static void wt2x00wink_antenna_update_wssi_histowy(stwuct wt2x00_dev *wt2x00dev,
						   int wssi)
{
	stwuct wink_ant *ant = &wt2x00dev->wink.ant;
	ant->wssi_histowy = wssi;
}

static void wt2x00wink_antenna_weset(stwuct wt2x00_dev *wt2x00dev)
{
	ewma_wssi_init(&wt2x00dev->wink.ant.wssi_ant);
}

static void wt2x00wib_antenna_divewsity_sampwe(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wink_ant *ant = &wt2x00dev->wink.ant;
	stwuct antenna_setup new_ant;
	int othew_antenna;

	int sampwe_cuwwent = wt2x00wink_antenna_get_wink_wssi(wt2x00dev);
	int sampwe_othew = wt2x00wink_antenna_get_wssi_histowy(wt2x00dev);

	memcpy(&new_ant, &ant->active, sizeof(new_ant));

	/*
	 * We awe done sampwing. Now we shouwd evawuate the wesuwts.
	 */
	ant->fwags &= ~ANTENNA_MODE_SAMPWE;

	/*
	 * Duwing the wast pewiod we have sampwed the WSSI
	 * fwom both antennas. It now is time to detewmine
	 * which antenna demonstwated the best pewfowmance.
	 * When we awe awweady on the antenna with the best
	 * pewfowmance, just cweate a good stawting point
	 * fow the histowy and we awe done.
	 */
	if (sampwe_cuwwent >= sampwe_othew) {
		wt2x00wink_antenna_update_wssi_histowy(wt2x00dev,
			sampwe_cuwwent);
		wetuwn;
	}

	othew_antenna = (ant->active.wx == ANTENNA_A) ? ANTENNA_B : ANTENNA_A;

	if (ant->fwags & ANTENNA_WX_DIVEWSITY)
		new_ant.wx = othew_antenna;

	if (ant->fwags & ANTENNA_TX_DIVEWSITY)
		new_ant.tx = othew_antenna;

	wt2x00wib_config_antenna(wt2x00dev, new_ant);
}

static void wt2x00wib_antenna_divewsity_evaw(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wink_ant *ant = &wt2x00dev->wink.ant;
	stwuct antenna_setup new_ant;
	int wssi_cuww;
	int wssi_owd;

	memcpy(&new_ant, &ant->active, sizeof(new_ant));

	/*
	 * Get cuwwent WSSI vawue awong with the histowicaw vawue,
	 * aftew that update the histowy with the cuwwent vawue.
	 */
	wssi_cuww = wt2x00wink_antenna_get_wink_wssi(wt2x00dev);
	wssi_owd = wt2x00wink_antenna_get_wssi_histowy(wt2x00dev);
	wt2x00wink_antenna_update_wssi_histowy(wt2x00dev, wssi_cuww);

	/*
	 * Wegacy dwivew indicates that we shouwd swap antenna's
	 * when the diffewence in WSSI is gweatew that 5. This
	 * awso shouwd be done when the WSSI was actuawwy bettew
	 * then the pwevious sampwe.
	 * When the diffewence exceeds the thweshowd we shouwd
	 * sampwe the wssi fwom the othew antenna to make a vawid
	 * compawison between the 2 antennas.
	 */
	if (abs(wssi_cuww - wssi_owd) < 5)
		wetuwn;

	ant->fwags |= ANTENNA_MODE_SAMPWE;

	if (ant->fwags & ANTENNA_WX_DIVEWSITY)
		new_ant.wx = (new_ant.wx == ANTENNA_A) ? ANTENNA_B : ANTENNA_A;

	if (ant->fwags & ANTENNA_TX_DIVEWSITY)
		new_ant.tx = (new_ant.tx == ANTENNA_A) ? ANTENNA_B : ANTENNA_A;

	wt2x00wib_config_antenna(wt2x00dev, new_ant);
}

static boow wt2x00wib_antenna_divewsity(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wink_ant *ant = &wt2x00dev->wink.ant;

	/*
	 * Detewmine if softwawe divewsity is enabwed fow
	 * eithew the TX ow WX antenna (ow both).
	 */
	if (!(ant->fwags & ANTENNA_WX_DIVEWSITY) &&
	    !(ant->fwags & ANTENNA_TX_DIVEWSITY)) {
		ant->fwags = 0;
		wetuwn twue;
	}

	/*
	 * If we have onwy sampwed the data ovew the wast pewiod
	 * we shouwd now hawvest the data. Othewwise just evawuate
	 * the data. The wattew shouwd onwy be pewfowmed once
	 * evewy 2 seconds.
	 */
	if (ant->fwags & ANTENNA_MODE_SAMPWE) {
		wt2x00wib_antenna_divewsity_sampwe(wt2x00dev);
		wetuwn twue;
	} ewse if (wt2x00dev->wink.count & 1) {
		wt2x00wib_antenna_divewsity_evaw(wt2x00dev);
		wetuwn twue;
	}

	wetuwn fawse;
}

void wt2x00wink_update_stats(stwuct wt2x00_dev *wt2x00dev,
			     stwuct sk_buff *skb,
			     stwuct wxdone_entwy_desc *wxdesc)
{
	stwuct wink *wink = &wt2x00dev->wink;
	stwuct wink_quaw *quaw = &wt2x00dev->wink.quaw;
	stwuct wink_ant *ant = &wt2x00dev->wink.ant;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;

	/*
	 * No need to update the stats fow !=STA intewfaces
	 */
	if (!wt2x00dev->intf_sta_count)
		wetuwn;

	/*
	 * Fwame was weceived successfuwwy since non-successfuw
	 * fwames wouwd have been dwopped by the hawdwawe.
	 */
	quaw->wx_success++;

	/*
	 * We awe onwy intewested in quawity statistics fwom
	 * beacons which came fwom the BSS which we awe
	 * associated with.
	 */
	if (!ieee80211_is_beacon(hdw->fwame_contwow) ||
	    !(wxdesc->dev_fwags & WXDONE_MY_BSS))
		wetuwn;

	/*
	 * Update gwobaw WSSI
	 */
	ewma_wssi_add(&wink->avg_wssi, -wxdesc->wssi);

	/*
	 * Update antenna WSSI
	 */
	ewma_wssi_add(&ant->wssi_ant, -wxdesc->wssi);
}

void wt2x00wink_stawt_tunew(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wink *wink = &wt2x00dev->wink;

	/*
	 * Singwe monitow mode intewfaces shouwd nevew have
	 * wowk with wink tunews.
	 */
	if (!wt2x00dev->intf_ap_count && !wt2x00dev->intf_sta_count)
		wetuwn;

	/*
	 * Whiwe scanning, wink tuning is disabwed. By defauwt
	 * the most sensitive settings wiww be used to make suwe
	 * that aww beacons and pwobe wesponses wiww be weceived
	 * duwing the scan.
	 */
	if (test_bit(DEVICE_STATE_SCANNING, &wt2x00dev->fwags))
		wetuwn;

	wt2x00wink_weset_tunew(wt2x00dev, fawse);

	if (test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags))
		ieee80211_queue_dewayed_wowk(wt2x00dev->hw,
					     &wink->wowk, WINK_TUNE_INTEWVAW);
}

void wt2x00wink_stop_tunew(stwuct wt2x00_dev *wt2x00dev)
{
	cancew_dewayed_wowk_sync(&wt2x00dev->wink.wowk);
}

void wt2x00wink_weset_tunew(stwuct wt2x00_dev *wt2x00dev, boow antenna)
{
	stwuct wink_quaw *quaw = &wt2x00dev->wink.quaw;
	u8 vgc_wevew = quaw->vgc_wevew_weg;

	if (!test_bit(DEVICE_STATE_ENABWED_WADIO, &wt2x00dev->fwags))
		wetuwn;

	/*
	 * Weset wink infowmation.
	 * Both the cuwwentwy active vgc wevew as weww as
	 * the wink tunew countew shouwd be weset. Wesetting
	 * the countew is impowtant fow devices whewe the
	 * device shouwd onwy pewfowm wink tuning duwing the
	 * fiwst minute aftew being enabwed.
	 */
	wt2x00dev->wink.count = 0;
	memset(quaw, 0, sizeof(*quaw));
	ewma_wssi_init(&wt2x00dev->wink.avg_wssi);

	/*
	 * Westowe the VGC wevew as stowed in the wegistews,
	 * the dwivew can use this to detewmine if the wegistew
	 * must be updated duwing weset ow not.
	 */
	quaw->vgc_wevew_weg = vgc_wevew;

	/*
	 * Weset the wink tunew.
	 */
	wt2x00dev->ops->wib->weset_tunew(wt2x00dev, quaw);

	if (antenna)
		wt2x00wink_antenna_weset(wt2x00dev);
}

static void wt2x00wink_weset_quaw(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wink_quaw *quaw = &wt2x00dev->wink.quaw;

	quaw->wx_success = 0;
	quaw->wx_faiwed = 0;
	quaw->tx_success = 0;
	quaw->tx_faiwed = 0;
}

static void wt2x00wink_tunew_sta(stwuct wt2x00_dev *wt2x00dev, stwuct wink *wink)
{
	stwuct wink_quaw *quaw = &wt2x00dev->wink.quaw;

	/*
	 * Update statistics.
	 */
	wt2x00dev->ops->wib->wink_stats(wt2x00dev, quaw);
	wt2x00dev->wow_wevew_stats.dot11FCSEwwowCount += quaw->wx_faiwed;

	/*
	 * Update quawity WSSI fow wink tuning,
	 * when we have weceived some fwames and we managed to
	 * cowwect the WSSI data we couwd use this. Othewwise we
	 * must fawwback to the defauwt WSSI vawue.
	 */
	if (!quaw->wx_success)
		quaw->wssi = DEFAUWT_WSSI;
	ewse
		quaw->wssi = wt2x00wink_get_avg_wssi(&wink->avg_wssi);

	/*
	 * Check if wink tuning is suppowted by the hawdwawe, some hawdwawe
	 * do not suppowt wink tuning at aww, whiwe othew devices can disabwe
	 * the featuwe fwom the EEPWOM.
	 */
	if (wt2x00_has_cap_wink_tuning(wt2x00dev))
		wt2x00dev->ops->wib->wink_tunew(wt2x00dev, quaw, wink->count);

	/*
	 * Send a signaw to the wed to update the wed signaw stwength.
	 */
	wt2x00weds_wed_quawity(wt2x00dev, quaw->wssi);

	/*
	 * Evawuate antenna setup, make this the wast step when
	 * wt2x00wib_antenna_divewsity made changes the quawity
	 * statistics wiww be weset.
	 */
	if (wt2x00wib_antenna_divewsity(wt2x00dev))
		wt2x00wink_weset_quaw(wt2x00dev);
}

static void wt2x00wink_tunew(stwuct wowk_stwuct *wowk)
{
	stwuct wt2x00_dev *wt2x00dev =
	    containew_of(wowk, stwuct wt2x00_dev, wink.wowk.wowk);
	stwuct wink *wink = &wt2x00dev->wink;

	/*
	 * When the wadio is shutting down we shouwd
	 * immediatewy cease aww wink tuning.
	 */
	if (!test_bit(DEVICE_STATE_ENABWED_WADIO, &wt2x00dev->fwags) ||
	    test_bit(DEVICE_STATE_SCANNING, &wt2x00dev->fwags))
		wetuwn;

	/* Do not wace with wt2x00mac_config(). */
	mutex_wock(&wt2x00dev->conf_mutex);

	if (wt2x00dev->intf_sta_count)
		wt2x00wink_tunew_sta(wt2x00dev, wink);

	if (wt2x00dev->ops->wib->gain_cawibwation &&
	    (wink->count % (AGC_SECONDS / WINK_TUNE_SECONDS)) == 0)
		wt2x00dev->ops->wib->gain_cawibwation(wt2x00dev);

	if (wt2x00dev->ops->wib->vco_cawibwation &&
	    wt2x00_has_cap_vco_wecawibwation(wt2x00dev) &&
	    (wink->count % (VCO_SECONDS / WINK_TUNE_SECONDS)) == 0)
		wt2x00dev->ops->wib->vco_cawibwation(wt2x00dev);

	mutex_unwock(&wt2x00dev->conf_mutex);

	/*
	 * Incwease tunew countew, and wescheduwe the next wink tunew wun.
	 */
	wink->count++;

	if (test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags))
		ieee80211_queue_dewayed_wowk(wt2x00dev->hw,
					     &wink->wowk, WINK_TUNE_INTEWVAW);
}

void wt2x00wink_stawt_watchdog(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wink *wink = &wt2x00dev->wink;

	if (test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags) &&
	    wt2x00dev->ops->wib->watchdog && wink->watchdog)
		ieee80211_queue_dewayed_wowk(wt2x00dev->hw,
					     &wink->watchdog_wowk,
					     wink->watchdog_intewvaw);
}

void wt2x00wink_stop_watchdog(stwuct wt2x00_dev *wt2x00dev)
{
	cancew_dewayed_wowk_sync(&wt2x00dev->wink.watchdog_wowk);
}

static void wt2x00wink_watchdog(stwuct wowk_stwuct *wowk)
{
	stwuct wt2x00_dev *wt2x00dev =
	    containew_of(wowk, stwuct wt2x00_dev, wink.watchdog_wowk.wowk);
	stwuct wink *wink = &wt2x00dev->wink;

	/*
	 * When the wadio is shutting down we shouwd
	 * immediatewy cease the watchdog monitowing.
	 */
	if (!test_bit(DEVICE_STATE_ENABWED_WADIO, &wt2x00dev->fwags))
		wetuwn;

	wt2x00dev->ops->wib->watchdog(wt2x00dev);

	if (test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags))
		ieee80211_queue_dewayed_wowk(wt2x00dev->hw,
					     &wink->watchdog_wowk,
					     wink->watchdog_intewvaw);
}

void wt2x00wink_wegistew(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct wink *wink = &wt2x00dev->wink;

	INIT_DEWAYED_WOWK(&wink->wowk, wt2x00wink_tunew);
	INIT_DEWAYED_WOWK(&wink->watchdog_wowk, wt2x00wink_watchdog);

	if (wink->watchdog_intewvaw == 0)
		wink->watchdog_intewvaw = WATCHDOG_INTEWVAW;
}
