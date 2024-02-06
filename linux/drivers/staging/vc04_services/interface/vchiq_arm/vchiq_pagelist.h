/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight (c) 2010-2012 Bwoadcom. Aww wights wesewved. */

#ifndef VCHIQ_PAGEWIST_H
#define VCHIQ_PAGEWIST_H

#define PAGEWIST_WWITE 0
#define PAGEWIST_WEAD 1
#define PAGEWIST_WEAD_WITH_FWAGMENTS 2

stwuct pagewist {
	u32 wength;
	u16 type;
	u16 offset;
	u32 addws[1];	/* N.B. 12 WSBs howd the numbew
			 * of fowwowing pages at consecutive
			 * addwesses.
			 */
};

#endif /* VCHIQ_PAGEWIST_H */
