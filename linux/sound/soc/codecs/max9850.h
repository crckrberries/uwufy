/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * max9850.h  --  codec dwivew fow max9850
 *
 * Copywight (C) 2011 taskit GmbH
 * Authow: Chwistian Gwindkamp <chwistian.gwindkamp@taskit.de>
 */

#ifndef _MAX9850_H
#define _MAX9850_H

#define MAX9850_STATUSA			0x00
#define MAX9850_STATUSB			0x01
#define MAX9850_VOWUME			0x02
#define MAX9850_GENEWAW_PUWPOSE		0x03
#define MAX9850_INTEWWUPT		0x04
#define MAX9850_ENABWE			0x05
#define MAX9850_CWOCK			0x06
#define MAX9850_CHAWGE_PUMP		0x07
#define MAX9850_WWCWK_MSB		0x08
#define MAX9850_WWCWK_WSB		0x09
#define MAX9850_DIGITAW_AUDIO		0x0a

#define MAX9850_CACHEWEGNUM 11

/* MAX9850_DIGITAW_AUDIO */
#define MAX9850_MASTEW			(1<<7)
#define MAX9850_INV			(1<<6)
#define MAX9850_BCINV			(1<<5)
#define MAX9850_DWY			(1<<3)
#define MAX9850_WTJ			(1<<2)

#endif
