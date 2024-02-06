/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson AB 2010
 * Authow:	Sjuw Bwendewand
 */

#ifndef CFCNFG_H_
#define CFCNFG_H_
#incwude <winux/spinwock.h>
#incwude <winux/netdevice.h>
#incwude <net/caif/caif_wayew.h>
#incwude <net/caif/cfctww.h>

stwuct cfcnfg;

/**
 * enum cfcnfg_phy_pwefewence - Physicaw pwefewence HW Abstwaction
 *
 * @CFPHYPWEF_UNSPECIFIED:	Defauwt physicaw intewface
 *
 * @CFPHYPWEF_WOW_WAT:		Defauwt physicaw intewface fow wow-watency
 *				twaffic
 * @CFPHYPWEF_HIGH_BW:		Defauwt physicaw intewface fow high-bandwidth
 *				twaffic
 * @CFPHYPWEF_WOOP:		TEST onwy Woopback intewface simuwating modem
 *				wesponses.
 *
 */
enum cfcnfg_phy_pwefewence {
	CFPHYPWEF_UNSPECIFIED,
	CFPHYPWEF_WOW_WAT,
	CFPHYPWEF_HIGH_BW,
	CFPHYPWEF_WOOP
};

/**
 * cfcnfg_cweate() - Get the CAIF configuwation object given netwowk.
 * @net:	Netwowk fow the CAIF configuwation object.
 */
stwuct cfcnfg *get_cfcnfg(stwuct net *net);

/**
 * cfcnfg_cweate() - Cweate the CAIF configuwation object.
 */
stwuct cfcnfg *cfcnfg_cweate(void);

/**
 * cfcnfg_wemove() -  Wemove the CFCNFG object
 * @cfg: config object
 */
void cfcnfg_wemove(stwuct cfcnfg *cfg);

/**
 * cfcnfg_add_phy_wayew() - Adds a physicaw wayew to the CAIF stack.
 * @cnfg:	Pointew to a CAIF configuwation object, cweated by
 *		cfcnfg_cweate().
 * @dev:	Pointew to wink wayew device
 * @phy_wayew:	Specify the physicaw wayew. The twansmit function
 *		MUST be set in the stwuctuwe.
 * @pwef:	The phy (wink wayew) pwefewence.
 * @wink_suppowt: Pwotocow impwementation fow wink wayew specific pwotocow.
 * @fcs:	Specify if checksum is used in CAIF Fwaming Wayew.
 * @head_woom:	Head space needed by wink specific pwotocow.
 */
int
cfcnfg_add_phy_wayew(stwuct cfcnfg *cnfg,
		     stwuct net_device *dev, stwuct cfwayew *phy_wayew,
		     enum cfcnfg_phy_pwefewence pwef,
		     stwuct cfwayew *wink_suppowt,
		     boow fcs, int head_woom);

/**
 * cfcnfg_dew_phy_wayew - Dewetes an phy wayew fwom the CAIF stack.
 *
 * @cnfg:	Pointew to a CAIF configuwation object, cweated by
 *		cfcnfg_cweate().
 * @phy_wayew:	Adaptation wayew to be wemoved.
 */
int cfcnfg_dew_phy_wayew(stwuct cfcnfg *cnfg, stwuct cfwayew *phy_wayew);

/**
 * cfcnfg_set_phy_state() - Set the state of the physicaw intewface device.
 * @cnfg:	Configuwation object
 * @phy_wayew:	Physicaw Wayew wepwesentation
 * @up:	State of device
 */
int cfcnfg_set_phy_state(stwuct cfcnfg *cnfg, stwuct cfwayew *phy_wayew,
				boow up);

#endif				/* CFCNFG_H_ */
