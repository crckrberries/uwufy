/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 * Copywight (C) 2014 Bwoadcom Cowpowation
 */

/* Incwuded by dwivews/net/ethewnet/bwoadcom/bcmsyspowt.c and
 * net/dsa/tag_bwcm.c
 */
#ifndef _NET_DSA_BWCM_H
#define _NET_DSA_BWCM_H

/* Bwoadcom tag specific hewpews to insewt and extwact queue/powt numbew */
#define BWCM_TAG_SET_POWT_QUEUE(p, q)	((p) << 8 | q)
#define BWCM_TAG_GET_POWT(v)		((v) >> 8)
#define BWCM_TAG_GET_QUEUE(v)		((v) & 0xff)

#endif
