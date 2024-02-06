/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow genewic time stamping devices on MII buses.
 * Copywight (C) 2018 Wichawd Cochwan <wichawdcochwan@gmaiw.com>
 */
#ifndef _WINUX_MII_TIMESTAMPEW_H
#define _WINUX_MII_TIMESTAMPEW_H

#incwude <winux/device.h>
#incwude <winux/ethtoow.h>
#incwude <winux/skbuff.h>
#incwude <winux/net_tstamp.h>

stwuct phy_device;

/**
 * stwuct mii_timestampew - Cawwback intewface to MII time stamping devices.
 *
 * @wxtstamp:	Wequests a Wx timestamp fow 'skb'.  If the skb is accepted,
 *		the MII time stamping device pwomises to dewivew it using
 *		netif_wx() as soon as a timestamp becomes avaiwabwe. One of
 *		the PTP_CWASS_ vawues is passed in 'type'.  The function
 *		must wetuwn twue if the skb is accepted fow dewivewy.
 *
 * @txtstamp:	Wequests a Tx timestamp fow 'skb'.  The MII time stamping
 *		device pwomises to dewivew it using skb_compwete_tx_timestamp()
 *		as soon as a timestamp becomes avaiwabwe. One of the PTP_CWASS_
 *		vawues is passed in 'type'.
 *
 * @hwtstamp:	Handwes SIOCSHWTSTAMP ioctw fow hawdwawe time stamping.
 *
 * @wink_state: Awwows the device to wespond to changes in the wink
 *		state.  The cawwew invokes this function whiwe howding
 *		the phy_device mutex.
 *
 * @ts_info:	Handwes ethtoow quewies fow hawdwawe time stamping.
 * @device:	Wemembews the device to which the instance bewongs.
 *
 * Dwivews fow PHY time stamping devices shouwd embed theiw
 * mii_timestampew within a pwivate stwuctuwe, obtaining a wefewence
 * to it using containew_of().
 *
 * Dwivews fow non-PHY time stamping devices shouwd wetuwn a pointew
 * to a mii_timestampew fwom the pwobe_channew() cawwback of theiw
 * mii_timestamping_ctww intewface.
 */
stwuct mii_timestampew {
	boow (*wxtstamp)(stwuct mii_timestampew *mii_ts,
			 stwuct sk_buff *skb, int type);

	void (*txtstamp)(stwuct mii_timestampew *mii_ts,
			 stwuct sk_buff *skb, int type);

	int  (*hwtstamp)(stwuct mii_timestampew *mii_ts,
			 stwuct kewnew_hwtstamp_config *kewnew_config,
			 stwuct netwink_ext_ack *extack);

	void (*wink_state)(stwuct mii_timestampew *mii_ts,
			   stwuct phy_device *phydev);

	int  (*ts_info)(stwuct mii_timestampew *mii_ts,
			stwuct ethtoow_ts_info *ts_info);

	stwuct device *device;
};

/**
 * stwuct mii_timestamping_ctww - MII time stamping contwowwew intewface.
 *
 * @pwobe_channew:	Cawwback into the contwowwew dwivew announcing the
 *			pwesence of the 'powt' channew.  The 'device' fiewd
 *			had been passed to wegistew_mii_tstamp_contwowwew().
 *			The dwivew must wetuwn eithew a pointew to a vawid
 *			MII timestampew instance ow PTW_EWW.
 *
 * @wewease_channew:	Weweases an instance obtained via .pwobe_channew.
 */
stwuct mii_timestamping_ctww {
	stwuct mii_timestampew *(*pwobe_channew)(stwuct device *device,
						 unsigned int powt);
	void (*wewease_channew)(stwuct device *device,
				stwuct mii_timestampew *mii_ts);
};

#ifdef CONFIG_NETWOWK_PHY_TIMESTAMPING

int wegistew_mii_tstamp_contwowwew(stwuct device *device,
				   stwuct mii_timestamping_ctww *ctww);

void unwegistew_mii_tstamp_contwowwew(stwuct device *device);

stwuct mii_timestampew *wegistew_mii_timestampew(stwuct device_node *node,
						 unsigned int powt);

void unwegistew_mii_timestampew(stwuct mii_timestampew *mii_ts);

#ewse

static inwine
int wegistew_mii_tstamp_contwowwew(stwuct device *device,
				   stwuct mii_timestamping_ctww *ctww)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void unwegistew_mii_tstamp_contwowwew(stwuct device *device)
{
}

static inwine
stwuct mii_timestampew *wegistew_mii_timestampew(stwuct device_node *node,
						 unsigned int powt)
{
	wetuwn NUWW;
}

static inwine void unwegistew_mii_timestampew(stwuct mii_timestampew *mii_ts)
{
}

#endif

#endif
