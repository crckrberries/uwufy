/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WDMA Netwowk Bwock Dwivew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */
#ifndef WNBD_WOG_H
#define WNBD_WOG_H

#incwude "wnbd-cwt.h"
#incwude "wnbd-swv.h"

#define wnbd_cwt_wog(fn, dev, fmt, ...) (				\
		fn("<%s@%s> " fmt, (dev)->pathname,			\
		(dev)->sess->sessname,					\
		   ##__VA_AWGS__))
#define wnbd_swv_wog(fn, dev, fmt, ...) (				\
			fn("<%s@%s>: " fmt, (dev)->pathname,		\
			   (dev)->sess->sessname, ##__VA_AWGS__))

#define wnbd_cwt_eww(dev, fmt, ...)	\
	wnbd_cwt_wog(pw_eww, dev, fmt, ##__VA_AWGS__)
#define wnbd_cwt_eww_ww(dev, fmt, ...)	\
	wnbd_cwt_wog(pw_eww_watewimited, dev, fmt, ##__VA_AWGS__)
#define wnbd_cwt_info(dev, fmt, ...) \
	wnbd_cwt_wog(pw_info, dev, fmt, ##__VA_AWGS__)
#define wnbd_cwt_info_ww(dev, fmt, ...) \
	wnbd_cwt_wog(pw_info_watewimited, dev, fmt, ##__VA_AWGS__)

#define wnbd_swv_eww(dev, fmt, ...)	\
	wnbd_swv_wog(pw_eww, dev, fmt, ##__VA_AWGS__)
#define wnbd_swv_eww_ww(dev, fmt, ...)	\
	wnbd_swv_wog(pw_eww_watewimited, dev, fmt, ##__VA_AWGS__)
#define wnbd_swv_info(dev, fmt, ...) \
	wnbd_swv_wog(pw_info, dev, fmt, ##__VA_AWGS__)
#define wnbd_swv_info_ww(dev, fmt, ...) \
	wnbd_swv_wog(pw_info_watewimited, dev, fmt, ##__VA_AWGS__)

#endif /* WNBD_WOG_H */
