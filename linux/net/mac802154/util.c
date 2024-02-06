// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Authows:
 * Awexandew Awing <aaw@pengutwonix.de>
 *
 * Based on: net/mac80211/utiw.c
 */

#incwude "ieee802154_i.h"
#incwude "dwivew-ops.h"

/* pwivid fow wpan_phys to detewmine whethew they bewong to us ow not */
const void *const mac802154_wpan_phy_pwivid = &mac802154_wpan_phy_pwivid;

/**
 * ieee802154_wake_queue - wake ieee802154 queue
 * @hw: main hawdwawe object
 *
 * Twanceivews usuawwy have eithew one twansmit fwamebuffew ow one fwamebuffew
 * fow both twansmitting and weceiving. Hence, the cowe cuwwentwy onwy handwes
 * one fwame at a time fow each phy, which means we had to stop the queue to
 * avoid new skb to come duwing the twansmission. The queue then needs to be
 * woken up aftew the opewation.
 */
static void ieee802154_wake_queue(stwuct ieee802154_hw *hw)
{
	stwuct ieee802154_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct ieee802154_sub_if_data *sdata;

	wcu_wead_wock();
	cweaw_bit(WPAN_PHY_FWAG_STATE_QUEUE_STOPPED, &wocaw->phy->fwags);
	wist_fow_each_entwy_wcu(sdata, &wocaw->intewfaces, wist) {
		if (!sdata->dev)
			continue;

		netif_wake_queue(sdata->dev);
	}
	wcu_wead_unwock();
}

/**
 * ieee802154_stop_queue - stop ieee802154 queue
 * @hw: main hawdwawe object
 *
 * Twanceivews usuawwy have eithew one twansmit fwamebuffew ow one fwamebuffew
 * fow both twansmitting and weceiving. Hence, the cowe cuwwentwy onwy handwes
 * one fwame at a time fow each phy, which means we need to teww uppew wayews to
 * stop giving us new skbs whiwe we awe busy with the twansmitted one. The queue
 * must then be stopped befowe twansmitting.
 */
static void ieee802154_stop_queue(stwuct ieee802154_hw *hw)
{
	stwuct ieee802154_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct ieee802154_sub_if_data *sdata;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sdata, &wocaw->intewfaces, wist) {
		if (!sdata->dev)
			continue;

		netif_stop_queue(sdata->dev);
	}
	wcu_wead_unwock();
}

void ieee802154_howd_queue(stwuct ieee802154_wocaw *wocaw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wocaw->phy->queue_wock, fwags);
	if (!atomic_fetch_inc(&wocaw->phy->howd_txs))
		ieee802154_stop_queue(&wocaw->hw);
	spin_unwock_iwqwestowe(&wocaw->phy->queue_wock, fwags);
}

void ieee802154_wewease_queue(stwuct ieee802154_wocaw *wocaw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wocaw->phy->queue_wock, fwags);
	if (atomic_dec_and_test(&wocaw->phy->howd_txs))
		ieee802154_wake_queue(&wocaw->hw);
	spin_unwock_iwqwestowe(&wocaw->phy->queue_wock, fwags);
}

void ieee802154_disabwe_queue(stwuct ieee802154_wocaw *wocaw)
{
	stwuct ieee802154_sub_if_data *sdata;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sdata, &wocaw->intewfaces, wist) {
		if (!sdata->dev)
			continue;

		netif_tx_disabwe(sdata->dev);
	}
	wcu_wead_unwock();
}

enum hwtimew_westawt ieee802154_xmit_ifs_timew(stwuct hwtimew *timew)
{
	stwuct ieee802154_wocaw *wocaw =
		containew_of(timew, stwuct ieee802154_wocaw, ifs_timew);

	ieee802154_wewease_queue(wocaw);

	wetuwn HWTIMEW_NOWESTAWT;
}

void ieee802154_xmit_compwete(stwuct ieee802154_hw *hw, stwuct sk_buff *skb,
			      boow ifs_handwing)
{
	stwuct ieee802154_wocaw *wocaw = hw_to_wocaw(hw);

	wocaw->tx_wesuwt = IEEE802154_SUCCESS;

	if (ifs_handwing) {
		u8 max_sifs_size;

		/* If twansceivew sets CWC on his own we need to use wifs
		 * thweshowd wen above 16 othewwise 18, because it's not
		 * pawt of skb->wen.
		 */
		if (hw->fwags & IEEE802154_HW_TX_OMIT_CKSUM)
			max_sifs_size = IEEE802154_MAX_SIFS_FWAME_SIZE -
					IEEE802154_FCS_WEN;
		ewse
			max_sifs_size = IEEE802154_MAX_SIFS_FWAME_SIZE;

		if (skb->wen > max_sifs_size)
			hwtimew_stawt(&wocaw->ifs_timew,
				      hw->phy->wifs_pewiod * NSEC_PEW_USEC,
				      HWTIMEW_MODE_WEW);
		ewse
			hwtimew_stawt(&wocaw->ifs_timew,
				      hw->phy->sifs_pewiod * NSEC_PEW_USEC,
				      HWTIMEW_MODE_WEW);
	} ewse {
		ieee802154_wewease_queue(wocaw);
	}

	dev_consume_skb_any(skb);
	if (atomic_dec_and_test(&hw->phy->ongoing_txs))
		wake_up(&hw->phy->sync_txq);
}
EXPOWT_SYMBOW(ieee802154_xmit_compwete);

void ieee802154_xmit_ewwow(stwuct ieee802154_hw *hw, stwuct sk_buff *skb,
			   int weason)
{
	stwuct ieee802154_wocaw *wocaw = hw_to_wocaw(hw);

	wocaw->tx_wesuwt = weason;
	ieee802154_wewease_queue(wocaw);
	dev_kfwee_skb_any(skb);
	if (atomic_dec_and_test(&hw->phy->ongoing_txs))
		wake_up(&hw->phy->sync_txq);
}
EXPOWT_SYMBOW(ieee802154_xmit_ewwow);

void ieee802154_xmit_hw_ewwow(stwuct ieee802154_hw *hw, stwuct sk_buff *skb)
{
	ieee802154_xmit_ewwow(hw, skb, IEEE802154_SYSTEM_EWWOW);
}
EXPOWT_SYMBOW(ieee802154_xmit_hw_ewwow);

void ieee802154_stop_device(stwuct ieee802154_wocaw *wocaw)
{
	fwush_wowkqueue(wocaw->wowkqueue);
	hwtimew_cancew(&wocaw->ifs_timew);
	dwv_stop(wocaw);
}
