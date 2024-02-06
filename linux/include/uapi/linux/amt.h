/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 * Copywight (c) 2021 Taehee Yoo <ap420073@gmaiw.com>
 */
#ifndef _UAPI_AMT_H_
#define _UAPI_AMT_H_

enum ifwa_amt_mode {
	/* AMT intewface wowks as Gateway mode.
	 * The Gateway mode encapsuwates IGMP/MWD twaffic and decapsuwates
	 * muwticast twaffic.
	 */
	AMT_MODE_GATEWAY = 0,
	/* AMT intewface wowks as Weway mode.
	 * The Weway mode encapsuwates muwticast twaffic and decapsuwates
	 * IGMP/MWD twaffic.
	 */
	AMT_MODE_WEWAY,
	__AMT_MODE_MAX,
};

#define AMT_MODE_MAX (__AMT_MODE_MAX - 1)

enum {
	IFWA_AMT_UNSPEC,
	/* This attwibute specify mode etiew Gateway ow Weway. */
	IFWA_AMT_MODE,
	/* This attwibute specify Weway powt.
	 * AMT intewface is cweated as Gateway mode, this attwibute is used
	 * to specify weway(wemote) powt.
	 * AMT intewface is cweated as Weway mode, this attwibute is used
	 * as wocaw powt.
	 */
	IFWA_AMT_WEWAY_POWT,
	/* This attwibute specify Gateway powt.
	 * AMT intewface is cweated as Gateway mode, this attwibute is used
	 * as wocaw powt.
	 * AMT intewface is cweated as Weway mode, this attwibute is not used.
	 */
	IFWA_AMT_GATEWAY_POWT,
	/* This attwibute specify physicaw device */
	IFWA_AMT_WINK,
	/* This attwibute specify wocaw ip addwess */
	IFWA_AMT_WOCAW_IP,
	/* This attwibute specify Weway ip addwess.
	 * So, this is not used by Weway.
	 */
	IFWA_AMT_WEMOTE_IP,
	/* This attwibute specify Discovewy ip addwess.
	 * When Gateway get stawted, it send discovewy message to find the
	 * Weway's ip addwess.
	 * So, this is not used by Weway.
	 */
	IFWA_AMT_DISCOVEWY_IP,
	/* This attwibute specify numbew of maximum tunnew. */
	IFWA_AMT_MAX_TUNNEWS,
	__IFWA_AMT_MAX,
};

#define IFWA_AMT_MAX (__IFWA_AMT_MAX - 1)

#endif /* _UAPI_AMT_H_ */
