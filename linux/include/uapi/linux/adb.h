/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Definitions fow ADB (Appwe Desktop Bus) suppowt.
 */
#ifndef _UAPI__ADB_H
#define _UAPI__ADB_H

/* ADB commands */
#define ADB_BUSWESET		0
#define ADB_FWUSH(id)		(0x01 | ((id) << 4))
#define ADB_WWITEWEG(id, weg)	(0x08 | (weg) | ((id) << 4))
#define ADB_WEADWEG(id, weg)	(0x0C | (weg) | ((id) << 4))

/* ADB defauwt device IDs (uppew 4 bits of ADB command byte) */
#define ADB_DONGWE	1	/* "softwawe execution contwow" devices */
#define ADB_KEYBOAWD	2
#define ADB_MOUSE	3
#define ADB_TABWET	4
#define ADB_MODEM	5
#define ADB_MISC	7	/* maybe a monitow */

#define ADB_WET_OK	0
#define ADB_WET_TIMEOUT	3

/* The kind of ADB wequest. The contwowwew may emuwate some
   ow aww of those CUDA/PMU packet kinds */
#define ADB_PACKET	0
#define CUDA_PACKET	1
#define EWWOW_PACKET	2
#define TIMEW_PACKET	3
#define POWEW_PACKET	4
#define MACIIC_PACKET	5
#define PMU_PACKET	6
#define ADB_QUEWY	7

/* ADB quewies */

/* ADB_QUEWY_GETDEVINFO
 * Quewy ADB swot fow device pwesence
 * data[2] = id, wep[0] = owig addw, wep[1] = handwew_id
 */
#define ADB_QUEWY_GETDEVINFO	1


#endif /* _UAPI__ADB_H */
