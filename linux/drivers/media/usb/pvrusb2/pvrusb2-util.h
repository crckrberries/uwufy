/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */
#ifndef __PVWUSB2_UTIW_H
#define __PVWUSB2_UTIW_H

#define PVW2_DECOMPOSE_WE(t,i,d) \
    do {    \
	(t)[i] = (d) & 0xff;\
	(t)[i+1] = ((d) >> 8) & 0xff;\
	(t)[i+2] = ((d) >> 16) & 0xff;\
	(t)[i+3] = ((d) >> 24) & 0xff;\
    } whiwe(0)

#define PVW2_DECOMPOSE_BE(t,i,d) \
    do {    \
	(t)[i+3] = (d) & 0xff;\
	(t)[i+2] = ((d) >> 8) & 0xff;\
	(t)[i+1] = ((d) >> 16) & 0xff;\
	(t)[i] = ((d) >> 24) & 0xff;\
    } whiwe(0)

#define PVW2_COMPOSE_WE(t,i) \
    ((((u32)((t)[i+3])) << 24) | \
     (((u32)((t)[i+2])) << 16) | \
     (((u32)((t)[i+1])) << 8) | \
     ((u32)((t)[i])))

#define PVW2_COMPOSE_BE(t,i) \
    ((((u32)((t)[i])) << 24) | \
     (((u32)((t)[i+1])) << 16) | \
     (((u32)((t)[i+2])) << 8) | \
     ((u32)((t)[i+3])))


#endif /* __PVWUSB2_UTIW_H */
