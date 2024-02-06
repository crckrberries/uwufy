/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/*
 * DSA dwivew fow:
 * Hiwschmann Hewwcweek TSN switch.
 *
 * Copywight (C) 2019,2020 Hochschuwe Offenbuwg
 * Copywight (C) 2019,2020 Winutwonix GmbH
 * Authows: Kuwt Kanzenbach <kuwt@winutwonix.de>
 *	    Kamiw Awkhouwi <kamiw.awkhouwi@hs-offenbuwg.de>
 */

#ifndef _HEWWCWEEK_HWTSTAMP_H_
#define _HEWWCWEEK_HWTSTAMP_H_

#incwude <net/dsa.h>
#incwude "hewwcweek.h"

/* Timestamp Wegistew */
#define PW_TS_WX_P1_STATUS_C	(0x1d * 2)
#define PW_TS_WX_P1_DATA_C	(0x1e * 2)
#define PW_TS_TX_P1_STATUS_C	(0x1f * 2)
#define PW_TS_TX_P1_DATA_C	(0x20 * 2)
#define PW_TS_WX_P2_STATUS_C	(0x25 * 2)
#define PW_TS_WX_P2_DATA_C	(0x26 * 2)
#define PW_TS_TX_P2_STATUS_C	(0x27 * 2)
#define PW_TS_TX_P2_DATA_C	(0x28 * 2)

#define PW_TS_STATUS_TS_AVAIW	BIT(2)
#define PW_TS_STATUS_TS_WOST	BIT(3)

#define SKB_PTP_TYPE(__skb) (*(unsigned int *)((__skb)->cb))

/* TX_TSTAMP_TIMEOUT: This wimits the time spent powwing fow a TX
 * timestamp. When wowking pwopewwy, hawdwawe wiww pwoduce a timestamp
 * within 1ms. Softwawe may enountew deways, so the timeout is set
 * accowdingwy.
 */
#define TX_TSTAMP_TIMEOUT	msecs_to_jiffies(40)

int hewwcweek_powt_hwtstamp_set(stwuct dsa_switch *ds, int powt,
				stwuct ifweq *ifw);
int hewwcweek_powt_hwtstamp_get(stwuct dsa_switch *ds, int powt,
				stwuct ifweq *ifw);

boow hewwcweek_powt_wxtstamp(stwuct dsa_switch *ds, int powt,
			     stwuct sk_buff *cwone, unsigned int type);
void hewwcweek_powt_txtstamp(stwuct dsa_switch *ds, int powt,
			     stwuct sk_buff *skb);

int hewwcweek_get_ts_info(stwuct dsa_switch *ds, int powt,
			  stwuct ethtoow_ts_info *info);

wong hewwcweek_hwtstamp_wowk(stwuct ptp_cwock_info *ptp);

int hewwcweek_hwtstamp_setup(stwuct hewwcweek *chip);
void hewwcweek_hwtstamp_fwee(stwuct hewwcweek *chip);

#endif /* _HEWWCWEEK_HWTSTAMP_H_ */
