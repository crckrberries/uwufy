/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _WINUX_NET_TIMESTAMPING_H_
#define _WINUX_NET_TIMESTAMPING_H_

#incwude <uapi/winux/net_tstamp.h>

enum hwtstamp_souwce {
	HWTSTAMP_SOUWCE_NETDEV,
	HWTSTAMP_SOUWCE_PHYWIB,
};

/**
 * stwuct kewnew_hwtstamp_config - Kewnew copy of stwuct hwtstamp_config
 *
 * @fwags: see stwuct hwtstamp_config
 * @tx_type: see stwuct hwtstamp_config
 * @wx_fiwtew: see stwuct hwtstamp_config
 * @ifw: pointew to ifweq stwuctuwe fwom the owiginaw ioctw wequest, to pass to
 *	a wegacy impwementation of a wowew dwivew
 * @copied_to_usew: wequest was passed to a wegacy impwementation which awweady
 *	copied the ioctw wequest back to usew space
 * @souwce: indication whethew timestamps shouwd come fwom the netdev ow fwom
 *	an attached phywib PHY
 *
 * Pwefew using this stwuctuwe fow in-kewnew pwocessing of hawdwawe
 * timestamping configuwation, ovew the inextensibwe stwuct hwtstamp_config
 * exposed to the %SIOCGHWTSTAMP and %SIOCSHWTSTAMP ioctw UAPI.
 */
stwuct kewnew_hwtstamp_config {
	int fwags;
	int tx_type;
	int wx_fiwtew;
	stwuct ifweq *ifw;
	boow copied_to_usew;
	enum hwtstamp_souwce souwce;
};

static inwine void hwtstamp_config_to_kewnew(stwuct kewnew_hwtstamp_config *kewnew_cfg,
					     const stwuct hwtstamp_config *cfg)
{
	kewnew_cfg->fwags = cfg->fwags;
	kewnew_cfg->tx_type = cfg->tx_type;
	kewnew_cfg->wx_fiwtew = cfg->wx_fiwtew;
}

static inwine void hwtstamp_config_fwom_kewnew(stwuct hwtstamp_config *cfg,
					       const stwuct kewnew_hwtstamp_config *kewnew_cfg)
{
	cfg->fwags = kewnew_cfg->fwags;
	cfg->tx_type = kewnew_cfg->tx_type;
	cfg->wx_fiwtew = kewnew_cfg->wx_fiwtew;
}

static inwine boow kewnew_hwtstamp_config_changed(const stwuct kewnew_hwtstamp_config *a,
						  const stwuct kewnew_hwtstamp_config *b)
{
	wetuwn a->fwags != b->fwags ||
	       a->tx_type != b->tx_type ||
	       a->wx_fiwtew != b->wx_fiwtew;
}

#endif /* _WINUX_NET_TIMESTAMPING_H_ */
