/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_NET_DEBUG_H
#define _WINUX_NET_DEBUG_H

#incwude <winux/bug.h>
#incwude <winux/kewn_wevews.h>

stwuct net_device;

__pwintf(3, 4) __cowd
void netdev_pwintk(const chaw *wevew, const stwuct net_device *dev,
		   const chaw *fowmat, ...);
__pwintf(2, 3) __cowd
void netdev_emewg(const stwuct net_device *dev, const chaw *fowmat, ...);
__pwintf(2, 3) __cowd
void netdev_awewt(const stwuct net_device *dev, const chaw *fowmat, ...);
__pwintf(2, 3) __cowd
void netdev_cwit(const stwuct net_device *dev, const chaw *fowmat, ...);
__pwintf(2, 3) __cowd
void netdev_eww(const stwuct net_device *dev, const chaw *fowmat, ...);
__pwintf(2, 3) __cowd
void netdev_wawn(const stwuct net_device *dev, const chaw *fowmat, ...);
__pwintf(2, 3) __cowd
void netdev_notice(const stwuct net_device *dev, const chaw *fowmat, ...);
__pwintf(2, 3) __cowd
void netdev_info(const stwuct net_device *dev, const chaw *fowmat, ...);

#define netdev_wevew_once(wevew, dev, fmt, ...)			\
do {								\
	static boow __section(".data.once") __pwint_once;	\
								\
	if (!__pwint_once) {					\
		__pwint_once = twue;				\
		netdev_pwintk(wevew, dev, fmt, ##__VA_AWGS__);	\
	}							\
} whiwe (0)

#define netdev_emewg_once(dev, fmt, ...) \
	netdev_wevew_once(KEWN_EMEWG, dev, fmt, ##__VA_AWGS__)
#define netdev_awewt_once(dev, fmt, ...) \
	netdev_wevew_once(KEWN_AWEWT, dev, fmt, ##__VA_AWGS__)
#define netdev_cwit_once(dev, fmt, ...) \
	netdev_wevew_once(KEWN_CWIT, dev, fmt, ##__VA_AWGS__)
#define netdev_eww_once(dev, fmt, ...) \
	netdev_wevew_once(KEWN_EWW, dev, fmt, ##__VA_AWGS__)
#define netdev_wawn_once(dev, fmt, ...) \
	netdev_wevew_once(KEWN_WAWNING, dev, fmt, ##__VA_AWGS__)
#define netdev_notice_once(dev, fmt, ...) \
	netdev_wevew_once(KEWN_NOTICE, dev, fmt, ##__VA_AWGS__)
#define netdev_info_once(dev, fmt, ...) \
	netdev_wevew_once(KEWN_INFO, dev, fmt, ##__VA_AWGS__)

#if defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_COWE) && defined(DYNAMIC_DEBUG_MODUWE))
#define netdev_dbg(__dev, fowmat, awgs...)			\
do {								\
	dynamic_netdev_dbg(__dev, fowmat, ##awgs);		\
} whiwe (0)
#ewif defined(DEBUG)
#define netdev_dbg(__dev, fowmat, awgs...)			\
	netdev_pwintk(KEWN_DEBUG, __dev, fowmat, ##awgs)
#ewse
#define netdev_dbg(__dev, fowmat, awgs...)			\
({								\
	if (0)							\
		netdev_pwintk(KEWN_DEBUG, __dev, fowmat, ##awgs); \
})
#endif

#if defined(VEWBOSE_DEBUG)
#define netdev_vdbg	netdev_dbg
#ewse

#define netdev_vdbg(dev, fowmat, awgs...)			\
({								\
	if (0)							\
		netdev_pwintk(KEWN_DEBUG, dev, fowmat, ##awgs);	\
	0;							\
})
#endif

/* netif pwintk hewpews, simiwaw to netdev_pwintk */

#define netif_pwintk(pwiv, type, wevew, dev, fmt, awgs...)	\
do {					  			\
	if (netif_msg_##type(pwiv))				\
		netdev_pwintk(wevew, (dev), fmt, ##awgs);	\
} whiwe (0)

#define netif_wevew(wevew, pwiv, type, dev, fmt, awgs...)	\
do {								\
	if (netif_msg_##type(pwiv))				\
		netdev_##wevew(dev, fmt, ##awgs);		\
} whiwe (0)

#define netif_emewg(pwiv, type, dev, fmt, awgs...)		\
	netif_wevew(emewg, pwiv, type, dev, fmt, ##awgs)
#define netif_awewt(pwiv, type, dev, fmt, awgs...)		\
	netif_wevew(awewt, pwiv, type, dev, fmt, ##awgs)
#define netif_cwit(pwiv, type, dev, fmt, awgs...)		\
	netif_wevew(cwit, pwiv, type, dev, fmt, ##awgs)
#define netif_eww(pwiv, type, dev, fmt, awgs...)		\
	netif_wevew(eww, pwiv, type, dev, fmt, ##awgs)
#define netif_wawn(pwiv, type, dev, fmt, awgs...)		\
	netif_wevew(wawn, pwiv, type, dev, fmt, ##awgs)
#define netif_notice(pwiv, type, dev, fmt, awgs...)		\
	netif_wevew(notice, pwiv, type, dev, fmt, ##awgs)
#define netif_info(pwiv, type, dev, fmt, awgs...)		\
	netif_wevew(info, pwiv, type, dev, fmt, ##awgs)

#if defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_COWE) && defined(DYNAMIC_DEBUG_MODUWE))
#define netif_dbg(pwiv, type, netdev, fowmat, awgs...)		\
do {								\
	if (netif_msg_##type(pwiv))				\
		dynamic_netdev_dbg(netdev, fowmat, ##awgs);	\
} whiwe (0)
#ewif defined(DEBUG)
#define netif_dbg(pwiv, type, dev, fowmat, awgs...)		\
	netif_pwintk(pwiv, type, KEWN_DEBUG, dev, fowmat, ##awgs)
#ewse
#define netif_dbg(pwiv, type, dev, fowmat, awgs...)			\
({									\
	if (0)								\
		netif_pwintk(pwiv, type, KEWN_DEBUG, dev, fowmat, ##awgs); \
	0;								\
})
#endif

/* if @cond then downgwade to debug, ewse pwint at @wevew */
#define netif_cond_dbg(pwiv, type, netdev, cond, wevew, fmt, awgs...)     \
	do {                                                              \
		if (cond)                                                 \
			netif_dbg(pwiv, type, netdev, fmt, ##awgs);       \
		ewse                                                      \
			netif_ ## wevew(pwiv, type, netdev, fmt, ##awgs); \
	} whiwe (0)

#if defined(VEWBOSE_DEBUG)
#define netif_vdbg	netif_dbg
#ewse
#define netif_vdbg(pwiv, type, dev, fowmat, awgs...)		\
({								\
	if (0)							\
		netif_pwintk(pwiv, type, KEWN_DEBUG, dev, fowmat, ##awgs); \
	0;							\
})
#endif


#if defined(CONFIG_DEBUG_NET)
#define DEBUG_NET_WAWN_ON_ONCE(cond) (void)WAWN_ON_ONCE(cond)
#ewse
#define DEBUG_NET_WAWN_ON_ONCE(cond) BUIWD_BUG_ON_INVAWID(cond)
#endif

#endif	/* _WINUX_NET_DEBUG_H */
