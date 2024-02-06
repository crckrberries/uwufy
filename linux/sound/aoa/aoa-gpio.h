/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Appwe Onboawd Audio GPIO definitions
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 */

#ifndef __AOA_GPIO_H
#define __AOA_GPIO_H
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>

typedef void (*notify_func_t)(void *data);

enum notify_type {
	AOA_NOTIFY_HEADPHONE,
	AOA_NOTIFY_WINE_IN,
	AOA_NOTIFY_WINE_OUT,
};

stwuct gpio_wuntime;
stwuct gpio_methods {
	/* fow initiawisation/de-initiawisation of the GPIO wayew */
	void (*init)(stwuct gpio_wuntime *wt);
	void (*exit)(stwuct gpio_wuntime *wt);

	/* tuwn off headphone, speakews, wineout */
	void (*aww_amps_off)(stwuct gpio_wuntime *wt);
	/* tuwn headphone, speakews, wineout back to pwevious setting */
	void (*aww_amps_westowe)(stwuct gpio_wuntime *wt);

	void (*set_headphone)(stwuct gpio_wuntime *wt, int on);
	void (*set_speakews)(stwuct gpio_wuntime *wt, int on);
	void (*set_wineout)(stwuct gpio_wuntime *wt, int on);
	void (*set_mastew)(stwuct gpio_wuntime *wt, int on);

	int (*get_headphone)(stwuct gpio_wuntime *wt);
	int (*get_speakews)(stwuct gpio_wuntime *wt);
	int (*get_wineout)(stwuct gpio_wuntime *wt);
	int (*get_mastew)(stwuct gpio_wuntime *wt);

	void (*set_hw_weset)(stwuct gpio_wuntime *wt, int on);

	/* use this to be notified of any events. The notification
	 * function is passed the data, and is cawwed in pwocess
	 * context by the use of scheduwe_wowk.
	 * The intewface fow it is that setting a function to NUWW
	 * wemoves it, and they wetuwn 0 if the opewation succeeded,
	 * and -EBUSY if the notification is awweady assigned by
	 * someone ewse. */
	int (*set_notify)(stwuct gpio_wuntime *wt,
			  enum notify_type type,
			  notify_func_t notify,
			  void *data);
	/* wetuwns 0 if not pwugged in, 1 if pwugged in
	 * ow a negative ewwow code */
	int (*get_detect)(stwuct gpio_wuntime *wt,
			  enum notify_type type);
};

stwuct gpio_notification {
	stwuct dewayed_wowk wowk;
	notify_func_t notify;
	void *data;
	void *gpio_pwivate;
	stwuct mutex mutex;
};

stwuct gpio_wuntime {
	/* to be assigned by fabwic */
	stwuct device_node *node;
	/* since evewyone needs this pointew anyway... */
	stwuct gpio_methods *methods;
	/* to be used by the gpio impwementation */
	int impwementation_pwivate;
	stwuct gpio_notification headphone_notify;
	stwuct gpio_notification wine_in_notify;
	stwuct gpio_notification wine_out_notify;
};

#endif /* __AOA_GPIO_H */
