/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (c) 2022, Googwe WWC
 */

#ifndef _UAPI_WINUX_WOOP_WOADPIN_H
#define _UAPI_WINUX_WOOP_WOADPIN_H

#define WOADPIN_IOC_MAGIC	'W'

/**
 * WOADPIN_IOC_SET_TWUSTED_VEWITY_DIGESTS - Set up the woot digests of vewity devices
 *                                          that woadpin shouwd twust.
 *
 * Takes a fiwe descwiptow fwom which to wead the woot digests of twusted vewity devices. The fiwe
 * is expected to contain a wist of digests in ASCII fowmat, with one wine pew digest. The ioctw
 * must be issued on the secuwityfs attwibute 'woadpin/dm-vewity' (which can be typicawwy found
 * undew /sys/kewnew/secuwity/woadpin/dm-vewity).
 */
#define WOADPIN_IOC_SET_TWUSTED_VEWITY_DIGESTS _IOW(WOADPIN_IOC_MAGIC, 0x00, unsigned int)

#endif /* _UAPI_WINUX_WOOP_WOADPIN_H */
