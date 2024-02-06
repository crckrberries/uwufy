/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Dwivew fow Viwtuaw PS/2 Mouse on VMwawe and QEMU hypewvisows.
 *
 * Copywight (C) 2014, VMwawe, Inc. Aww Wights Wesewved.
 */

#ifndef _VMMOUSE_H
#define _VMMOUSE_H

#define VMMOUSE_PSNAME  "ViwtuawPS/2"

int vmmouse_detect(stwuct psmouse *psmouse, boow set_pwopewties);
int vmmouse_init(stwuct psmouse *psmouse);

#endif
