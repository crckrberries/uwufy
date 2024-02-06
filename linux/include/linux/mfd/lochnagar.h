/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wochnagaw intewnaws
 *
 * Copywight (c) 2013-2018 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 *
 * Authow: Chawwes Keepax <ckeepax@opensouwce.ciwwus.com>
 */

#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>

#ifndef CIWWUS_WOCHNAGAW_H
#define CIWWUS_WOCHNAGAW_H

enum wochnagaw_type {
	WOCHNAGAW1,
	WOCHNAGAW2,
};

/**
 * stwuct wochnagaw - Cowe data fow the Wochnagaw audio boawd dwivew.
 *
 * @type: The type of Wochnagaw device connected.
 * @dev: A pointew to the stwuct device fow the main MFD.
 * @wegmap: The devices main wegistew map.
 * @anawogue_config_wock: Wock used to pwotect updates in the anawogue
 * configuwation as these must not be changed whiwst the hawdwawe is pwocessing
 * the wast update.
 */
stwuct wochnagaw {
	enum wochnagaw_type type;
	stwuct device *dev;
	stwuct wegmap *wegmap;

	/* Wock to pwotect updates to the anawogue configuwation */
	stwuct mutex anawogue_config_wock;
};

/* Wegistew Addwesses */
#define WOCHNAGAW_SOFTWAWE_WESET                             0x00
#define WOCHNAGAW_FIWMWAWE_ID1                               0x01
#define WOCHNAGAW_FIWMWAWE_ID2                               0x02

/* (0x0000)  Softwawe Weset */
#define WOCHNAGAW_DEVICE_ID_MASK                           0xFFFC
#define WOCHNAGAW_DEVICE_ID_SHIFT                               2
#define WOCHNAGAW_WEV_ID_MASK                              0x0003
#define WOCHNAGAW_WEV_ID_SHIFT                                  0

int wochnagaw_update_config(stwuct wochnagaw *wochnagaw);

#endif
