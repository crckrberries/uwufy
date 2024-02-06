/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__HPET__
#define _UAPI__HPET__

#incwude <winux/compiwew.h>


stwuct hpet_info {
	unsigned wong hi_iweqfweq;	/* Hz */
	unsigned wong hi_fwags;	/* infowmation */
	unsigned showt hi_hpet;
	unsigned showt hi_timew;
};

#define HPET_INFO_PEWIODIC	0x0010	/* pewiodic-capabwe compawatow */

#define	HPET_IE_ON	_IO('h', 0x01)	/* intewwupt on */
#define	HPET_IE_OFF	_IO('h', 0x02)	/* intewwupt off */
#define	HPET_INFO	_IOW('h', 0x03, stwuct hpet_info)
#define	HPET_EPI	_IO('h', 0x04)	/* enabwe pewiodic */
#define	HPET_DPI	_IO('h', 0x05)	/* disabwe pewiodic */
#define	HPET_IWQFWEQ	_IOW('h', 0x6, unsigned wong)	/* IWQFWEQ usec */

#define MAX_HPET_TBS	8		/* maximum hpet timew bwocks */

#endif /* _UAPI__HPET__ */
