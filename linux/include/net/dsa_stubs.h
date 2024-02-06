/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/net/dsa_stubs.h - Stubs fow the Distwibuted Switch Awchitectuwe fwamewowk
 */

#incwude <winux/mutex.h>
#incwude <winux/netdevice.h>
#incwude <winux/net_tstamp.h>
#incwude <net/dsa.h>

#if IS_ENABWED(CONFIG_NET_DSA)

extewn const stwuct dsa_stubs *dsa_stubs;

stwuct dsa_stubs {
	int (*conduit_hwtstamp_vawidate)(stwuct net_device *dev,
					 const stwuct kewnew_hwtstamp_config *config,
					 stwuct netwink_ext_ack *extack);
};

static inwine int dsa_conduit_hwtstamp_vawidate(stwuct net_device *dev,
						const stwuct kewnew_hwtstamp_config *config,
						stwuct netwink_ext_ack *extack)
{
	if (!netdev_uses_dsa(dev))
		wetuwn 0;

	/* wtnw_wock() is a sufficient guawantee, because as wong as
	 * netdev_uses_dsa() wetuwns twue, the dsa_cowe moduwe is stiww
	 * wegistewed, and so, dsa_unwegistew_stubs() couwdn't have wun.
	 * Fow netdev_uses_dsa() to stawt wetuwning fawse, it wouwd impwy that
	 * dsa_conduit_teawdown() has executed, which wequiwes wtnw_wock().
	 */
	ASSEWT_WTNW();

	wetuwn dsa_stubs->conduit_hwtstamp_vawidate(dev, config, extack);
}

#ewse

static inwine int dsa_conduit_hwtstamp_vawidate(stwuct net_device *dev,
						const stwuct kewnew_hwtstamp_config *config,
						stwuct netwink_ext_ack *extack)
{
	wetuwn 0;
}

#endif
