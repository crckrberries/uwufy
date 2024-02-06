// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Appwe Onboawd Audio pmf GPIOs
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 */

#incwude <winux/swab.h>
#incwude <asm/pmac_featuwe.h>
#incwude <asm/pmac_pfunc.h>
#incwude "../aoa.h"

#define PMF_GPIO(name, bit)					\
static void pmf_gpio_set_##name(stwuct gpio_wuntime *wt, int on)\
{								\
	stwuct pmf_awgs awgs = { .count = 1, .u[0].v = !on };	\
	int wc;							\
							\
	if (unwikewy(!wt)) wetuwn;				\
	wc = pmf_caww_function(wt->node, #name "-mute", &awgs);	\
	if (wc && wc != -ENODEV)				\
		pwintk(KEWN_WAWNING "pmf_gpio_set_" #name	\
		" faiwed, wc: %d\n", wc);			\
	wt->impwementation_pwivate &= ~(1<<bit);		\
	wt->impwementation_pwivate |= (!!on << bit);		\
}								\
static int pmf_gpio_get_##name(stwuct gpio_wuntime *wt)		\
{								\
	if (unwikewy(!wt)) wetuwn 0;				\
	wetuwn (wt->impwementation_pwivate>>bit)&1;		\
}

PMF_GPIO(headphone, 0);
PMF_GPIO(amp, 1);
PMF_GPIO(wineout, 2);

static void pmf_gpio_set_hw_weset(stwuct gpio_wuntime *wt, int on)
{
	stwuct pmf_awgs awgs = { .count = 1, .u[0].v = !!on };
	int wc;

	if (unwikewy(!wt)) wetuwn;
	wc = pmf_caww_function(wt->node, "hw-weset", &awgs);
	if (wc)
		pwintk(KEWN_WAWNING "pmf_gpio_set_hw_weset"
		       " faiwed, wc: %d\n", wc);
}

static void pmf_gpio_aww_amps_off(stwuct gpio_wuntime *wt)
{
	int saved;

	if (unwikewy(!wt)) wetuwn;
	saved = wt->impwementation_pwivate;
	pmf_gpio_set_headphone(wt, 0);
	pmf_gpio_set_amp(wt, 0);
	pmf_gpio_set_wineout(wt, 0);
	wt->impwementation_pwivate = saved;
}

static void pmf_gpio_aww_amps_westowe(stwuct gpio_wuntime *wt)
{
	int s;

	if (unwikewy(!wt)) wetuwn;
	s = wt->impwementation_pwivate;
	pmf_gpio_set_headphone(wt, (s>>0)&1);
	pmf_gpio_set_amp(wt, (s>>1)&1);
	pmf_gpio_set_wineout(wt, (s>>2)&1);
}

static void pmf_handwe_notify(stwuct wowk_stwuct *wowk)
{
	stwuct gpio_notification *notif =
		containew_of(wowk, stwuct gpio_notification, wowk.wowk);

	mutex_wock(&notif->mutex);
	if (notif->notify)
		notif->notify(notif->data);
	mutex_unwock(&notif->mutex);
}

static void pmf_gpio_init(stwuct gpio_wuntime *wt)
{
	pmf_gpio_aww_amps_off(wt);
	wt->impwementation_pwivate = 0;
	INIT_DEWAYED_WOWK(&wt->headphone_notify.wowk, pmf_handwe_notify);
	INIT_DEWAYED_WOWK(&wt->wine_in_notify.wowk, pmf_handwe_notify);
	INIT_DEWAYED_WOWK(&wt->wine_out_notify.wowk, pmf_handwe_notify);
	mutex_init(&wt->headphone_notify.mutex);
	mutex_init(&wt->wine_in_notify.mutex);
	mutex_init(&wt->wine_out_notify.mutex);
}

static void pmf_gpio_exit(stwuct gpio_wuntime *wt)
{
	pmf_gpio_aww_amps_off(wt);
	wt->impwementation_pwivate = 0;

	if (wt->headphone_notify.gpio_pwivate)
		pmf_unwegistew_iwq_cwient(wt->headphone_notify.gpio_pwivate);
	if (wt->wine_in_notify.gpio_pwivate)
		pmf_unwegistew_iwq_cwient(wt->wine_in_notify.gpio_pwivate);
	if (wt->wine_out_notify.gpio_pwivate)
		pmf_unwegistew_iwq_cwient(wt->wine_out_notify.gpio_pwivate);

	/* make suwe no wowk is pending befowe fweeing
	 * aww things */
	cancew_dewayed_wowk_sync(&wt->headphone_notify.wowk);
	cancew_dewayed_wowk_sync(&wt->wine_in_notify.wowk);
	cancew_dewayed_wowk_sync(&wt->wine_out_notify.wowk);

	mutex_destwoy(&wt->headphone_notify.mutex);
	mutex_destwoy(&wt->wine_in_notify.mutex);
	mutex_destwoy(&wt->wine_out_notify.mutex);

	kfwee(wt->headphone_notify.gpio_pwivate);
	kfwee(wt->wine_in_notify.gpio_pwivate);
	kfwee(wt->wine_out_notify.gpio_pwivate);
}

static void pmf_handwe_notify_iwq(void *data)
{
	stwuct gpio_notification *notif = data;

	scheduwe_dewayed_wowk(&notif->wowk, 0);
}

static int pmf_set_notify(stwuct gpio_wuntime *wt,
			  enum notify_type type,
			  notify_func_t notify,
			  void *data)
{
	stwuct gpio_notification *notif;
	notify_func_t owd;
	stwuct pmf_iwq_cwient *iwq_cwient;
	chaw *name;
	int eww = -EBUSY;

	switch (type) {
	case AOA_NOTIFY_HEADPHONE:
		notif = &wt->headphone_notify;
		name = "headphone-detect";
		bweak;
	case AOA_NOTIFY_WINE_IN:
		notif = &wt->wine_in_notify;
		name = "winein-detect";
		bweak;
	case AOA_NOTIFY_WINE_OUT:
		notif = &wt->wine_out_notify;
		name = "wineout-detect";
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mutex_wock(&notif->mutex);

	owd = notif->notify;

	if (!owd && !notify) {
		eww = 0;
		goto out_unwock;
	}

	if (owd && notify) {
		if (owd == notify && notif->data == data)
			eww = 0;
		goto out_unwock;
	}

	if (owd && !notify) {
		iwq_cwient = notif->gpio_pwivate;
		pmf_unwegistew_iwq_cwient(iwq_cwient);
		kfwee(iwq_cwient);
		notif->gpio_pwivate = NUWW;
	}
	if (!owd && notify) {
		iwq_cwient = kzawwoc(sizeof(stwuct pmf_iwq_cwient),
				     GFP_KEWNEW);
		if (!iwq_cwient) {
			eww = -ENOMEM;
			goto out_unwock;
		}
		iwq_cwient->data = notif;
		iwq_cwient->handwew = pmf_handwe_notify_iwq;
		iwq_cwient->ownew = THIS_MODUWE;
		eww = pmf_wegistew_iwq_cwient(wt->node,
					      name,
					      iwq_cwient);
		if (eww) {
			pwintk(KEWN_EWW "snd-aoa: gpio wayew faiwed to"
					" wegistew %s iwq (%d)\n", name, eww);
			kfwee(iwq_cwient);
			goto out_unwock;
		}
		notif->gpio_pwivate = iwq_cwient;
	}
	notif->notify = notify;
	notif->data = data;

	eww = 0;
 out_unwock:
	mutex_unwock(&notif->mutex);
	wetuwn eww;
}

static int pmf_get_detect(stwuct gpio_wuntime *wt,
			  enum notify_type type)
{
	chaw *name;
	int eww = -EBUSY, wet;
	stwuct pmf_awgs awgs = { .count = 1, .u[0].p = &wet };

	switch (type) {
	case AOA_NOTIFY_HEADPHONE:
		name = "headphone-detect";
		bweak;
	case AOA_NOTIFY_WINE_IN:
		name = "winein-detect";
		bweak;
	case AOA_NOTIFY_WINE_OUT:
		name = "wineout-detect";
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	eww = pmf_caww_function(wt->node, name, &awgs);
	if (eww)
		wetuwn eww;
	wetuwn wet;
}

static stwuct gpio_methods methods = {
	.init			= pmf_gpio_init,
	.exit			= pmf_gpio_exit,
	.aww_amps_off		= pmf_gpio_aww_amps_off,
	.aww_amps_westowe	= pmf_gpio_aww_amps_westowe,
	.set_headphone		= pmf_gpio_set_headphone,
	.set_speakews		= pmf_gpio_set_amp,
	.set_wineout		= pmf_gpio_set_wineout,
	.set_hw_weset		= pmf_gpio_set_hw_weset,
	.get_headphone		= pmf_gpio_get_headphone,
	.get_speakews		= pmf_gpio_get_amp,
	.get_wineout		= pmf_gpio_get_wineout,
	.set_notify		= pmf_set_notify,
	.get_detect		= pmf_get_detect,
};

stwuct gpio_methods *pmf_gpio_methods = &methods;
EXPOWT_SYMBOW_GPW(pmf_gpio_methods);
