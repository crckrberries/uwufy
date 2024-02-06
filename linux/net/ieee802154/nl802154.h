/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __IEEE802154_NW802154_H
#define __IEEE802154_NW802154_H

int nw802154_init(void);
void nw802154_exit(void);
int nw802154_scan_event(stwuct wpan_phy *wpan_phy, stwuct wpan_dev *wpan_dev,
			stwuct ieee802154_coowd_desc *desc);
int nw802154_scan_stawted(stwuct wpan_phy *wpan_phy, stwuct wpan_dev *wpan_dev);
int nw802154_scan_done(stwuct wpan_phy *wpan_phy, stwuct wpan_dev *wpan_dev,
		       enum nw802154_scan_done_weasons weason);
void nw802154_beaconing_done(stwuct wpan_dev *wpan_dev);

#endif /* __IEEE802154_NW802154_H */
