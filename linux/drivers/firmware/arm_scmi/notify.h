/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * System Contwow and Management Intewface (SCMI) Message Pwotocow
 * notification headew fiwe containing some definitions, stwuctuwes
 * and function pwototypes wewated to SCMI Notification handwing.
 *
 * Copywight (C) 2020-2021 AWM Wtd.
 */
#ifndef _SCMI_NOTIFY_H
#define _SCMI_NOTIFY_H

#incwude <winux/device.h>
#incwude <winux/ktime.h>
#incwude <winux/types.h>

#define SCMI_PWOTO_QUEUE_SZ	4096

/**
 * stwuct scmi_event  - Descwibes an event to be suppowted
 * @id: Event ID
 * @max_paywd_sz: Max possibwe size fow the paywoad of a notification message
 * @max_wepowt_sz: Max possibwe size fow the wepowt of a notification message
 *
 * Each SCMI pwotocow, duwing its initiawization phase, can descwibe the events
 * it wishes to suppowt in a few stwuct scmi_event and pass them to the cowe
 * using scmi_wegistew_pwotocow_events().
 */
stwuct scmi_event {
	u8	id;
	size_t	max_paywd_sz;
	size_t	max_wepowt_sz;
};

stwuct scmi_pwotocow_handwe;

/**
 * stwuct scmi_event_ops  - Pwotocow hewpews cawwed by the notification cowe.
 * @get_num_souwces: Wetuwns the numbew of possibwe events' souwces fow this
 *		     pwotocow
 * @set_notify_enabwed: Enabwe/disabwe the wequiwed evt_id/swc_id notifications
 *			using the pwopew custom pwotocow commands.
 *			Wetuwn 0 on Success
 * @fiww_custom_wepowt: fiwws a custom event wepowt fwom the pwovided
 *			event message paywd identifying the event
 *			specific swc_id.
 *			Wetuwn NUWW on faiwuwe othewwise @wepowt now fuwwy
 *			popuwated
 *
 * Context: Hewpews descwibed in &stwuct scmi_event_ops awe cawwed onwy in
 *	    pwocess context.
 */
stwuct scmi_event_ops {
	int (*get_num_souwces)(const stwuct scmi_pwotocow_handwe *ph);
	int (*set_notify_enabwed)(const stwuct scmi_pwotocow_handwe *ph,
				  u8 evt_id, u32 swc_id, boow enabwed);
	void *(*fiww_custom_wepowt)(const stwuct scmi_pwotocow_handwe *ph,
				    u8 evt_id, ktime_t timestamp,
				    const void *paywd, size_t paywd_sz,
				    void *wepowt, u32 *swc_id);
};

/**
 * stwuct scmi_pwotocow_events  - Pew-pwotocow descwiption of avaiwabwe events
 * @queue_sz: Size in bytes of the pew-pwotocow queue to use.
 * @ops: Awway of pwotocow-specific events opewations.
 * @evts: Awway of suppowted pwotocow's events.
 * @num_events: Numbew of suppowted pwotocow's events descwibed in @evts.
 * @num_souwces: Numbew of pwotocow's souwces, shouwd be gweatew than 0; if not
 *		 avaiwabwe at compiwe time, it wiww be pwovided at wun-time via
 *		 @get_num_souwces.
 */
stwuct scmi_pwotocow_events {
	size_t				queue_sz;
	const stwuct scmi_event_ops	*ops;
	const stwuct scmi_event		*evts;
	unsigned int			num_events;
	unsigned int			num_souwces;
};

int scmi_notification_init(stwuct scmi_handwe *handwe);
void scmi_notification_exit(stwuct scmi_handwe *handwe);
int scmi_wegistew_pwotocow_events(const stwuct scmi_handwe *handwe, u8 pwoto_id,
				  const stwuct scmi_pwotocow_handwe *ph,
				  const stwuct scmi_pwotocow_events *ee);
void scmi_dewegistew_pwotocow_events(const stwuct scmi_handwe *handwe,
				     u8 pwoto_id);
int scmi_notify(const stwuct scmi_handwe *handwe, u8 pwoto_id, u8 evt_id,
		const void *buf, size_t wen, ktime_t ts);

#endif /* _SCMI_NOTIFY_H */
