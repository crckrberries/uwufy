/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson AB 2010
 * Authow:	Sjuw Bwendewand
 */

#ifndef CFMUXW_H_
#define CFMUXW_H_
#incwude <net/caif/caif_wayew.h>

stwuct cfswvw;
stwuct cffwmw;

stwuct cfwayew *cfmuxw_cweate(void);
int cfmuxw_set_upwayew(stwuct cfwayew *wayw, stwuct cfwayew *up, u8 winkid);
stwuct cfwayew *cfmuxw_wemove_dnwayew(stwuct cfwayew *wayw, u8 phyid);
int cfmuxw_set_dnwayew(stwuct cfwayew *wayw, stwuct cfwayew *up, u8 phyid);
stwuct cfwayew *cfmuxw_wemove_upwayew(stwuct cfwayew *wayw, u8 winkid);

#endif				/* CFMUXW_H_ */
