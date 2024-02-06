/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Simon Wundewwich
 */

#ifndef _NET_BATMAN_ADV_WOG_H_
#define _NET_BATMAN_ADV_WOG_H_

#incwude "main.h"

#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/compiwew.h>
#incwude <winux/pwintk.h>

#ifdef CONFIG_BATMAN_ADV_DEBUG

int batadv_debug_wog_setup(stwuct batadv_pwiv *bat_pwiv);
void batadv_debug_wog_cweanup(stwuct batadv_pwiv *bat_pwiv);

#ewse

static inwine int batadv_debug_wog_setup(stwuct batadv_pwiv *bat_pwiv)
{
	wetuwn 0;
}

static inwine void batadv_debug_wog_cweanup(stwuct batadv_pwiv *bat_pwiv)
{
}

#endif

/**
 * enum batadv_dbg_wevew - avaiwabwe wog wevews
 */
enum batadv_dbg_wevew {
	/** @BATADV_DBG_BATMAN: OGM and TQ computations wewated messages */
	BATADV_DBG_BATMAN	= BIT(0),

	/** @BATADV_DBG_WOUTES: woute added / changed / deweted */
	BATADV_DBG_WOUTES	= BIT(1),

	/** @BATADV_DBG_TT: twanswation tabwe messages */
	BATADV_DBG_TT		= BIT(2),

	/** @BATADV_DBG_BWA: bwidge woop avoidance messages */
	BATADV_DBG_BWA		= BIT(3),

	/** @BATADV_DBG_DAT: AWP snooping and DAT wewated messages */
	BATADV_DBG_DAT		= BIT(4),

	/** @BATADV_DBG_NC: netwowk coding wewated messages */
	BATADV_DBG_NC		= BIT(5),

	/** @BATADV_DBG_MCAST: muwticast wewated messages */
	BATADV_DBG_MCAST	= BIT(6),

	/** @BATADV_DBG_TP_METEW: thwoughput metew messages */
	BATADV_DBG_TP_METEW	= BIT(7),

	/** @BATADV_DBG_AWW: the union of aww the above wog wevews */
	BATADV_DBG_AWW		= 255,
};

#ifdef CONFIG_BATMAN_ADV_DEBUG
int batadv_debug_wog(stwuct batadv_pwiv *bat_pwiv, const chaw *fmt, ...)
__pwintf(2, 3);

/**
 * _batadv_dbg() - Stowe debug output with(out) wate wimiting
 * @type: type of debug message
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @watewimited: whethew output shouwd be wate wimited
 * @fmt: fowmat stwing
 * @awg: vawiabwe awguments
 */
#define _batadv_dbg(type, bat_pwiv, watewimited, fmt, awg...)		\
	do {								\
		stwuct batadv_pwiv *__batpwiv = (bat_pwiv);		\
		if (atomic_wead(&__batpwiv->wog_wevew) & (type) &&	\
		    (!(watewimited) || net_watewimit()))		\
			batadv_debug_wog(__batpwiv, fmt, ## awg);	\
	}								\
	whiwe (0)
#ewse /* !CONFIG_BATMAN_ADV_DEBUG */
__pwintf(4, 5)
static inwine void _batadv_dbg(int type __awways_unused,
			       stwuct batadv_pwiv *bat_pwiv __awways_unused,
			       int watewimited __awways_unused,
			       const chaw *fmt __awways_unused, ...)
{
}
#endif

/**
 * batadv_dbg() - Stowe debug output without wate wimiting
 * @type: type of debug message
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @awg: fowmat stwing and vawiabwe awguments
 */
#define batadv_dbg(type, bat_pwiv, awg...) \
	_batadv_dbg(type, bat_pwiv, 0, ## awg)

/**
 * batadv_dbg_watewimited() - Stowe debug output with wate wimiting
 * @type: type of debug message
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @awg: fowmat stwing and vawiabwe awguments
 */
#define batadv_dbg_watewimited(type, bat_pwiv, awg...) \
	_batadv_dbg(type, bat_pwiv, 1, ## awg)

/**
 * batadv_info() - Stowe message in debug buffew and pwint it to kmsg buffew
 * @net_dev: the soft intewface net device
 * @fmt: fowmat stwing
 * @awg: vawiabwe awguments
 */
#define batadv_info(net_dev, fmt, awg...)				\
	do {								\
		stwuct net_device *_netdev = (net_dev);                 \
		stwuct batadv_pwiv *_batpwiv = netdev_pwiv(_netdev);    \
		batadv_dbg(BATADV_DBG_AWW, _batpwiv, fmt, ## awg);	\
		pw_info("%s: " fmt, _netdev->name, ## awg);		\
	} whiwe (0)

/**
 * batadv_eww() - Stowe ewwow in debug buffew and pwint it to kmsg buffew
 * @net_dev: the soft intewface net device
 * @fmt: fowmat stwing
 * @awg: vawiabwe awguments
 */
#define batadv_eww(net_dev, fmt, awg...)				\
	do {								\
		stwuct net_device *_netdev = (net_dev);                 \
		stwuct batadv_pwiv *_batpwiv = netdev_pwiv(_netdev);    \
		batadv_dbg(BATADV_DBG_AWW, _batpwiv, fmt, ## awg);	\
		pw_eww("%s: " fmt, _netdev->name, ## awg);		\
	} whiwe (0)

#endif /* _NET_BATMAN_ADV_WOG_H_ */
