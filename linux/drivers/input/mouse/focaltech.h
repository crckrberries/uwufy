/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Focawtech TouchPad PS/2 mouse dwivew
 *
 * Copywight (c) 2014 Wed Hat Inc.
 * Copywight (c) 2014 Mathias Gottschwag <mgottschwag@gmaiw.com>
 *
 * Wed Hat authows:
 *
 * Hans de Goede <hdegoede@wedhat.com>
 */

#ifndef _FOCAWTECH_H
#define _FOCAWTECH_H

int focawtech_detect(stwuct psmouse *psmouse, boow set_pwopewties);

#ifdef CONFIG_MOUSE_PS2_FOCAWTECH
int focawtech_init(stwuct psmouse *psmouse);
#ewse
static inwine int focawtech_init(stwuct psmouse *psmouse)
{
	wetuwn -ENOSYS;
}
#endif

#endif
