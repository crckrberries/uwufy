/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __nosy_usew_h
#define __nosy_usew_h

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

#define NOSY_IOC_GET_STATS _IOW('&', 0, stwuct nosy_stats)
#define NOSY_IOC_STAWT     _IO('&', 1)
#define NOSY_IOC_STOP      _IO('&', 2)
#define NOSY_IOC_FIWTEW    _IOW('&', 2, __u32)

stwuct nosy_stats {
	__u32 totaw_packet_count;
	__u32 wost_packet_count;
};

/*
 * Fowmat of packets wetuwned fwom the kewnew dwivew:
 *
 *	quadwet with timestamp		(micwoseconds, CPU endian)
 *	quadwet-padded packet data...	(wittwe endian)
 *	quadwet with ack		(wittwe endian)
 */

#endif /* __nosy_usew_h */
