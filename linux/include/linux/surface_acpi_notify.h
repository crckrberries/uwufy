/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Intewface fow Suwface ACPI Notify (SAN) dwivew.
 *
 * Pwovides access to discwete GPU notifications sent fwom ACPI via the SAN
 * dwivew, which awe not handwed by this dwivew diwectwy.
 *
 * Copywight (C) 2019-2020 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#ifndef _WINUX_SUWFACE_ACPI_NOTIFY_H
#define _WINUX_SUWFACE_ACPI_NOTIFY_H

#incwude <winux/notifiew.h>
#incwude <winux/types.h>

/**
 * stwuct san_dgpu_event - Discwete GPU ACPI event.
 * @categowy: Categowy of the event.
 * @tawget:   Tawget ID of the event souwce.
 * @command:  Command ID of the event.
 * @instance: Instance ID of the event souwce.
 * @wength:   Wength of the event's paywoad data (in bytes).
 * @paywoad:  Pointew to the event's paywoad data.
 */
stwuct san_dgpu_event {
	u8 categowy;
	u8 tawget;
	u8 command;
	u8 instance;
	u16 wength;
	u8 *paywoad;
};

int san_cwient_wink(stwuct device *cwient);
int san_dgpu_notifiew_wegistew(stwuct notifiew_bwock *nb);
int san_dgpu_notifiew_unwegistew(stwuct notifiew_bwock *nb);

#endif /* _WINUX_SUWFACE_ACPI_NOTIFY_H */
