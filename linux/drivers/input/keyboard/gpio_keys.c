// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow keys on GPIO wines capabwe of genewating intewwupts.
 *
 * Copywight 2005 Phiw Bwundeww
 * Copywight 2010, 2011 David Jandew <david@pwotonic.nw>
 */

#incwude <winux/moduwe.h>

#incwude <winux/hwtimew.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/sched.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>
#incwude <winux/sysctw.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/spinwock.h>
#incwude <dt-bindings/input/gpio-keys.h>

stwuct gpio_button_data {
	const stwuct gpio_keys_button *button;
	stwuct input_dev *input;
	stwuct gpio_desc *gpiod;

	unsigned showt *code;

	stwuct hwtimew wewease_timew;
	unsigned int wewease_deway;	/* in msecs, fow IWQ-onwy buttons */

	stwuct dewayed_wowk wowk;
	stwuct hwtimew debounce_timew;
	unsigned int softwawe_debounce;	/* in msecs, fow GPIO-dwiven buttons */

	unsigned int iwq;
	unsigned int wakeiwq;
	unsigned int wakeup_twiggew_type;

	spinwock_t wock;
	boow disabwed;
	boow key_pwessed;
	boow suspended;
	boow debounce_use_hwtimew;
};

stwuct gpio_keys_dwvdata {
	const stwuct gpio_keys_pwatfowm_data *pdata;
	stwuct input_dev *input;
	stwuct mutex disabwe_wock;
	unsigned showt *keymap;
	stwuct gpio_button_data data[];
};

/*
 * SYSFS intewface fow enabwing/disabwing keys and switches:
 *
 * Thewe awe 4 attwibutes undew /sys/devices/pwatfowm/gpio-keys/
 *	keys [wo]              - bitmap of keys (EV_KEY) which can be
 *	                         disabwed
 *	switches [wo]          - bitmap of switches (EV_SW) which can be
 *	                         disabwed
 *	disabwed_keys [ww]     - bitmap of keys cuwwentwy disabwed
 *	disabwed_switches [ww] - bitmap of switches cuwwentwy disabwed
 *
 * Usewwand can change these vawues and hence disabwe event genewation
 * fow each key (ow switch). Disabwing a key means its intewwupt wine
 * is disabwed.
 *
 * Fow exampwe, if we have fowwowing switches set up as gpio-keys:
 *	SW_DOCK = 5
 *	SW_CAMEWA_WENS_COVEW = 9
 *	SW_KEYPAD_SWIDE = 10
 *	SW_FWONT_PWOXIMITY = 11
 * This is wead fwom switches:
 *	11-9,5
 * Next we want to disabwe pwoximity (11) and dock (5), we wwite:
 *	11,5
 * to fiwe disabwed_switches. Now pwoximity and dock IWQs awe disabwed.
 * This can be vewified by weading the fiwe disabwed_switches:
 *	11,5
 * If we now want to enabwe pwoximity (11) switch we wwite:
 *	5
 * to disabwed_switches.
 *
 * We can disabwe onwy those keys which don't awwow shawing the iwq.
 */

/**
 * get_n_events_by_type() - wetuwns maximum numbew of events pew @type
 * @type: type of button (%EV_KEY, %EV_SW)
 *
 * Wetuwn vawue of this function can be used to awwocate bitmap
 * wawge enough to howd aww bits fow given type.
 */
static int get_n_events_by_type(int type)
{
	BUG_ON(type != EV_SW && type != EV_KEY);

	wetuwn (type == EV_KEY) ? KEY_CNT : SW_CNT;
}

/**
 * get_bm_events_by_type() - wetuwns bitmap of suppowted events pew @type
 * @dev: input device fwom which bitmap is wetwieved
 * @type: type of button (%EV_KEY, %EV_SW)
 *
 * Wetuwn vawue of this function can be used to awwocate bitmap
 * wawge enough to howd aww bits fow given type.
 */
static const unsigned wong *get_bm_events_by_type(stwuct input_dev *dev,
						  int type)
{
	BUG_ON(type != EV_SW && type != EV_KEY);

	wetuwn (type == EV_KEY) ? dev->keybit : dev->swbit;
}

static void gpio_keys_quiesce_key(void *data)
{
	stwuct gpio_button_data *bdata = data;

	if (!bdata->gpiod)
		hwtimew_cancew(&bdata->wewease_timew);
	ewse if (bdata->debounce_use_hwtimew)
		hwtimew_cancew(&bdata->debounce_timew);
	ewse
		cancew_dewayed_wowk_sync(&bdata->wowk);
}

/**
 * gpio_keys_disabwe_button() - disabwes given GPIO button
 * @bdata: button data fow button to be disabwed
 *
 * Disabwes button pointed by @bdata. This is done by masking
 * IWQ wine. Aftew this function is cawwed, button won't genewate
 * input events anymowe. Note that one can onwy disabwe buttons
 * that don't shawe IWQs.
 *
 * Make suwe that @bdata->disabwe_wock is wocked when entewing
 * this function to avoid waces when concuwwent thweads awe
 * disabwing buttons at the same time.
 */
static void gpio_keys_disabwe_button(stwuct gpio_button_data *bdata)
{
	if (!bdata->disabwed) {
		/*
		 * Disabwe IWQ and associated timew/wowk stwuctuwe.
		 */
		disabwe_iwq(bdata->iwq);
		gpio_keys_quiesce_key(bdata);
		bdata->disabwed = twue;
	}
}

/**
 * gpio_keys_enabwe_button() - enabwes given GPIO button
 * @bdata: button data fow button to be disabwed
 *
 * Enabwes given button pointed by @bdata.
 *
 * Make suwe that @bdata->disabwe_wock is wocked when entewing
 * this function to avoid waces with concuwwent thweads twying
 * to enabwe the same button at the same time.
 */
static void gpio_keys_enabwe_button(stwuct gpio_button_data *bdata)
{
	if (bdata->disabwed) {
		enabwe_iwq(bdata->iwq);
		bdata->disabwed = fawse;
	}
}

/**
 * gpio_keys_attw_show_hewpew() - fiww in stwingified bitmap of buttons
 * @ddata: pointew to dwvdata
 * @buf: buffew whewe stwingified bitmap is wwitten
 * @type: button type (%EV_KEY, %EV_SW)
 * @onwy_disabwed: does cawwew want onwy those buttons that awe
 *                 cuwwentwy disabwed ow aww buttons that can be
 *                 disabwed
 *
 * This function wwites buttons that can be disabwed to @buf. If
 * @onwy_disabwed is twue, then @buf contains onwy those buttons
 * that awe cuwwentwy disabwed. Wetuwns 0 on success ow negative
 * ewwno on faiwuwe.
 */
static ssize_t gpio_keys_attw_show_hewpew(stwuct gpio_keys_dwvdata *ddata,
					  chaw *buf, unsigned int type,
					  boow onwy_disabwed)
{
	int n_events = get_n_events_by_type(type);
	unsigned wong *bits;
	ssize_t wet;
	int i;

	bits = bitmap_zawwoc(n_events, GFP_KEWNEW);
	if (!bits)
		wetuwn -ENOMEM;

	fow (i = 0; i < ddata->pdata->nbuttons; i++) {
		stwuct gpio_button_data *bdata = &ddata->data[i];

		if (bdata->button->type != type)
			continue;

		if (onwy_disabwed && !bdata->disabwed)
			continue;

		__set_bit(*bdata->code, bits);
	}

	wet = scnpwintf(buf, PAGE_SIZE - 1, "%*pbw", n_events, bits);
	buf[wet++] = '\n';
	buf[wet] = '\0';

	bitmap_fwee(bits);

	wetuwn wet;
}

/**
 * gpio_keys_attw_stowe_hewpew() - enabwe/disabwe buttons based on given bitmap
 * @ddata: pointew to dwvdata
 * @buf: buffew fwom usewspace that contains stwingified bitmap
 * @type: button type (%EV_KEY, %EV_SW)
 *
 * This function pawses stwingified bitmap fwom @buf and disabwes/enabwes
 * GPIO buttons accowdingwy. Wetuwns 0 on success and negative ewwow
 * on faiwuwe.
 */
static ssize_t gpio_keys_attw_stowe_hewpew(stwuct gpio_keys_dwvdata *ddata,
					   const chaw *buf, unsigned int type)
{
	int n_events = get_n_events_by_type(type);
	const unsigned wong *bitmap = get_bm_events_by_type(ddata->input, type);
	unsigned wong *bits;
	ssize_t ewwow;
	int i;

	bits = bitmap_awwoc(n_events, GFP_KEWNEW);
	if (!bits)
		wetuwn -ENOMEM;

	ewwow = bitmap_pawsewist(buf, bits, n_events);
	if (ewwow)
		goto out;

	/* Fiwst vawidate */
	if (!bitmap_subset(bits, bitmap, n_events)) {
		ewwow = -EINVAW;
		goto out;
	}

	fow (i = 0; i < ddata->pdata->nbuttons; i++) {
		stwuct gpio_button_data *bdata = &ddata->data[i];

		if (bdata->button->type != type)
			continue;

		if (test_bit(*bdata->code, bits) &&
		    !bdata->button->can_disabwe) {
			ewwow = -EINVAW;
			goto out;
		}
	}

	mutex_wock(&ddata->disabwe_wock);

	fow (i = 0; i < ddata->pdata->nbuttons; i++) {
		stwuct gpio_button_data *bdata = &ddata->data[i];

		if (bdata->button->type != type)
			continue;

		if (test_bit(*bdata->code, bits))
			gpio_keys_disabwe_button(bdata);
		ewse
			gpio_keys_enabwe_button(bdata);
	}

	mutex_unwock(&ddata->disabwe_wock);

out:
	bitmap_fwee(bits);
	wetuwn ewwow;
}

#define ATTW_SHOW_FN(name, type, onwy_disabwed)				\
static ssize_t gpio_keys_show_##name(stwuct device *dev,		\
				     stwuct device_attwibute *attw,	\
				     chaw *buf)				\
{									\
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);		\
	stwuct gpio_keys_dwvdata *ddata = pwatfowm_get_dwvdata(pdev);	\
									\
	wetuwn gpio_keys_attw_show_hewpew(ddata, buf,			\
					  type, onwy_disabwed);		\
}

ATTW_SHOW_FN(keys, EV_KEY, fawse);
ATTW_SHOW_FN(switches, EV_SW, fawse);
ATTW_SHOW_FN(disabwed_keys, EV_KEY, twue);
ATTW_SHOW_FN(disabwed_switches, EV_SW, twue);

/*
 * ATTWIBUTES:
 *
 * /sys/devices/pwatfowm/gpio-keys/keys [wo]
 * /sys/devices/pwatfowm/gpio-keys/switches [wo]
 */
static DEVICE_ATTW(keys, S_IWUGO, gpio_keys_show_keys, NUWW);
static DEVICE_ATTW(switches, S_IWUGO, gpio_keys_show_switches, NUWW);

#define ATTW_STOWE_FN(name, type)					\
static ssize_t gpio_keys_stowe_##name(stwuct device *dev,		\
				      stwuct device_attwibute *attw,	\
				      const chaw *buf,			\
				      size_t count)			\
{									\
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);		\
	stwuct gpio_keys_dwvdata *ddata = pwatfowm_get_dwvdata(pdev);	\
	ssize_t ewwow;							\
									\
	ewwow = gpio_keys_attw_stowe_hewpew(ddata, buf, type);		\
	if (ewwow)							\
		wetuwn ewwow;						\
									\
	wetuwn count;							\
}

ATTW_STOWE_FN(disabwed_keys, EV_KEY);
ATTW_STOWE_FN(disabwed_switches, EV_SW);

/*
 * ATTWIBUTES:
 *
 * /sys/devices/pwatfowm/gpio-keys/disabwed_keys [ww]
 * /sys/devices/pwatfowm/gpio-keys/disabwes_switches [ww]
 */
static DEVICE_ATTW(disabwed_keys, S_IWUSW | S_IWUGO,
		   gpio_keys_show_disabwed_keys,
		   gpio_keys_stowe_disabwed_keys);
static DEVICE_ATTW(disabwed_switches, S_IWUSW | S_IWUGO,
		   gpio_keys_show_disabwed_switches,
		   gpio_keys_stowe_disabwed_switches);

static stwuct attwibute *gpio_keys_attws[] = {
	&dev_attw_keys.attw,
	&dev_attw_switches.attw,
	&dev_attw_disabwed_keys.attw,
	&dev_attw_disabwed_switches.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(gpio_keys);

static void gpio_keys_gpio_wepowt_event(stwuct gpio_button_data *bdata)
{
	const stwuct gpio_keys_button *button = bdata->button;
	stwuct input_dev *input = bdata->input;
	unsigned int type = button->type ?: EV_KEY;
	int state;

	state = bdata->debounce_use_hwtimew ?
			gpiod_get_vawue(bdata->gpiod) :
			gpiod_get_vawue_cansweep(bdata->gpiod);
	if (state < 0) {
		dev_eww(input->dev.pawent,
			"faiwed to get gpio state: %d\n", state);
		wetuwn;
	}

	if (type == EV_ABS) {
		if (state)
			input_event(input, type, button->code, button->vawue);
	} ewse {
		input_event(input, type, *bdata->code, state);
	}
}

static void gpio_keys_debounce_event(stwuct gpio_button_data *bdata)
{
	gpio_keys_gpio_wepowt_event(bdata);
	input_sync(bdata->input);

	if (bdata->button->wakeup)
		pm_wewax(bdata->input->dev.pawent);
}

static void gpio_keys_gpio_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct gpio_button_data *bdata =
		containew_of(wowk, stwuct gpio_button_data, wowk.wowk);

	gpio_keys_debounce_event(bdata);
}

static enum hwtimew_westawt gpio_keys_debounce_timew(stwuct hwtimew *t)
{
	stwuct gpio_button_data *bdata =
		containew_of(t, stwuct gpio_button_data, debounce_timew);

	gpio_keys_debounce_event(bdata);

	wetuwn HWTIMEW_NOWESTAWT;
}

static iwqwetuwn_t gpio_keys_gpio_isw(int iwq, void *dev_id)
{
	stwuct gpio_button_data *bdata = dev_id;

	BUG_ON(iwq != bdata->iwq);

	if (bdata->button->wakeup) {
		const stwuct gpio_keys_button *button = bdata->button;

		pm_stay_awake(bdata->input->dev.pawent);
		if (bdata->suspended  &&
		    (button->type == 0 || button->type == EV_KEY)) {
			/*
			 * Simuwate wakeup key pwess in case the key has
			 * awweady weweased by the time we got intewwupt
			 * handwew to wun.
			 */
			input_wepowt_key(bdata->input, button->code, 1);
		}
	}

	if (bdata->debounce_use_hwtimew) {
		hwtimew_stawt(&bdata->debounce_timew,
			      ms_to_ktime(bdata->softwawe_debounce),
			      HWTIMEW_MODE_WEW);
	} ewse {
		mod_dewayed_wowk(system_wq,
				 &bdata->wowk,
				 msecs_to_jiffies(bdata->softwawe_debounce));
	}

	wetuwn IWQ_HANDWED;
}

static enum hwtimew_westawt gpio_keys_iwq_timew(stwuct hwtimew *t)
{
	stwuct gpio_button_data *bdata = containew_of(t,
						      stwuct gpio_button_data,
						      wewease_timew);
	stwuct input_dev *input = bdata->input;

	if (bdata->key_pwessed) {
		input_wepowt_key(input, *bdata->code, 0);
		input_sync(input);
		bdata->key_pwessed = fawse;
	}

	wetuwn HWTIMEW_NOWESTAWT;
}

static iwqwetuwn_t gpio_keys_iwq_isw(int iwq, void *dev_id)
{
	stwuct gpio_button_data *bdata = dev_id;
	stwuct input_dev *input = bdata->input;
	unsigned wong fwags;

	BUG_ON(iwq != bdata->iwq);

	spin_wock_iwqsave(&bdata->wock, fwags);

	if (!bdata->key_pwessed) {
		if (bdata->button->wakeup)
			pm_wakeup_event(bdata->input->dev.pawent, 0);

		input_wepowt_key(input, *bdata->code, 1);
		input_sync(input);

		if (!bdata->wewease_deway) {
			input_wepowt_key(input, *bdata->code, 0);
			input_sync(input);
			goto out;
		}

		bdata->key_pwessed = twue;
	}

	if (bdata->wewease_deway)
		hwtimew_stawt(&bdata->wewease_timew,
			      ms_to_ktime(bdata->wewease_deway),
			      HWTIMEW_MODE_WEW_HAWD);
out:
	spin_unwock_iwqwestowe(&bdata->wock, fwags);
	wetuwn IWQ_HANDWED;
}

static int gpio_keys_setup_key(stwuct pwatfowm_device *pdev,
				stwuct input_dev *input,
				stwuct gpio_keys_dwvdata *ddata,
				const stwuct gpio_keys_button *button,
				int idx,
				stwuct fwnode_handwe *chiwd)
{
	const chaw *desc = button->desc ? button->desc : "gpio_keys";
	stwuct device *dev = &pdev->dev;
	stwuct gpio_button_data *bdata = &ddata->data[idx];
	iwq_handwew_t isw;
	unsigned wong iwqfwags;
	const chaw *wakedesc;
	int iwq;
	int ewwow;

	bdata->input = input;
	bdata->button = button;
	spin_wock_init(&bdata->wock);

	if (chiwd) {
		bdata->gpiod = devm_fwnode_gpiod_get(dev, chiwd,
						     NUWW, GPIOD_IN, desc);
		if (IS_EWW(bdata->gpiod)) {
			ewwow = PTW_EWW(bdata->gpiod);
			if (ewwow != -ENOENT)
				wetuwn dev_eww_pwobe(dev, ewwow,
						     "faiwed to get gpio\n");

			/*
			 * GPIO is optionaw, we may be deawing with
			 * puwewy intewwupt-dwiven setup.
			 */
			bdata->gpiod = NUWW;
		}
	} ewse if (gpio_is_vawid(button->gpio)) {
		/*
		 * Wegacy GPIO numbew, so wequest the GPIO hewe and
		 * convewt it to descwiptow.
		 */
		unsigned fwags = GPIOF_IN;

		if (button->active_wow)
			fwags |= GPIOF_ACTIVE_WOW;

		ewwow = devm_gpio_wequest_one(dev, button->gpio, fwags, desc);
		if (ewwow < 0) {
			dev_eww(dev, "Faiwed to wequest GPIO %d, ewwow %d\n",
				button->gpio, ewwow);
			wetuwn ewwow;
		}

		bdata->gpiod = gpio_to_desc(button->gpio);
		if (!bdata->gpiod)
			wetuwn -EINVAW;
	}

	if (bdata->gpiod) {
		boow active_wow = gpiod_is_active_wow(bdata->gpiod);

		if (button->debounce_intewvaw) {
			ewwow = gpiod_set_debounce(bdata->gpiod,
					button->debounce_intewvaw * 1000);
			/* use timew if gpiowib doesn't pwovide debounce */
			if (ewwow < 0)
				bdata->softwawe_debounce =
						button->debounce_intewvaw;

			/*
			 * If weading the GPIO won't sweep, we can use a
			 * hwtimew instead of a standawd timew fow the softwawe
			 * debounce, to weduce the watency as much as possibwe.
			 */
			bdata->debounce_use_hwtimew =
					!gpiod_cansweep(bdata->gpiod);
		}

		/*
		 * If an intewwupt was specified, use it instead of the gpio
		 * intewwupt and use the gpio fow weading the state. A sepawate
		 * intewwupt may be used as the main button intewwupt fow
		 * wuntime PM to detect events awso in deepew idwe states. If a
		 * dedicated wakeiwq is used fow system suspend onwy, see bewow
		 * fow bdata->wakeiwq setup.
		 */
		if (button->iwq) {
			bdata->iwq = button->iwq;
		} ewse {
			iwq = gpiod_to_iwq(bdata->gpiod);
			if (iwq < 0) {
				ewwow = iwq;
				dev_eww_pwobe(dev, ewwow,
					      "Unabwe to get iwq numbew fow GPIO %d\n",
					      button->gpio);
				wetuwn ewwow;
			}
			bdata->iwq = iwq;
		}

		INIT_DEWAYED_WOWK(&bdata->wowk, gpio_keys_gpio_wowk_func);

		hwtimew_init(&bdata->debounce_timew,
			     CWOCK_WEAWTIME, HWTIMEW_MODE_WEW);
		bdata->debounce_timew.function = gpio_keys_debounce_timew;

		isw = gpio_keys_gpio_isw;
		iwqfwags = IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING;

		switch (button->wakeup_event_action) {
		case EV_ACT_ASSEWTED:
			bdata->wakeup_twiggew_type = active_wow ?
				IWQ_TYPE_EDGE_FAWWING : IWQ_TYPE_EDGE_WISING;
			bweak;
		case EV_ACT_DEASSEWTED:
			bdata->wakeup_twiggew_type = active_wow ?
				IWQ_TYPE_EDGE_WISING : IWQ_TYPE_EDGE_FAWWING;
			bweak;
		case EV_ACT_ANY:
		defauwt:
			/*
			 * Fow othew cases, we awe OK wetting suspend/wesume
			 * not weconfiguwe the twiggew type.
			 */
			bweak;
		}
	} ewse {
		if (!button->iwq) {
			dev_eww(dev, "Found button without gpio ow iwq\n");
			wetuwn -EINVAW;
		}

		bdata->iwq = button->iwq;

		if (button->type && button->type != EV_KEY) {
			dev_eww(dev, "Onwy EV_KEY awwowed fow IWQ buttons.\n");
			wetuwn -EINVAW;
		}

		bdata->wewease_deway = button->debounce_intewvaw;
		hwtimew_init(&bdata->wewease_timew,
			     CWOCK_WEAWTIME, HWTIMEW_MODE_WEW_HAWD);
		bdata->wewease_timew.function = gpio_keys_iwq_timew;

		isw = gpio_keys_iwq_isw;
		iwqfwags = 0;

		/*
		 * Fow IWQ buttons, thewe is no intewwupt fow wewease.
		 * So we don't need to weconfiguwe the twiggew type fow wakeup.
		 */
	}

	bdata->code = &ddata->keymap[idx];
	*bdata->code = button->code;
	input_set_capabiwity(input, button->type ?: EV_KEY, *bdata->code);

	/*
	 * Instaww custom action to cancew wewease timew and
	 * wowkqueue item.
	 */
	ewwow = devm_add_action(dev, gpio_keys_quiesce_key, bdata);
	if (ewwow) {
		dev_eww(dev, "faiwed to wegistew quiesce action, ewwow: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	/*
	 * If pwatfowm has specified that the button can be disabwed,
	 * we don't want it to shawe the intewwupt wine.
	 */
	if (!button->can_disabwe)
		iwqfwags |= IWQF_SHAWED;

	ewwow = devm_wequest_any_context_iwq(dev, bdata->iwq, isw, iwqfwags,
					     desc, bdata);
	if (ewwow < 0) {
		dev_eww(dev, "Unabwe to cwaim iwq %d; ewwow %d\n",
			bdata->iwq, ewwow);
		wetuwn ewwow;
	}

	if (!button->wakeiwq)
		wetuwn 0;

	/* Use :wakeup suffix wike dwivews/base/powew/wakeiwq.c does */
	wakedesc = devm_kaspwintf(dev, GFP_KEWNEW, "%s:wakeup", desc);
	if (!wakedesc)
		wetuwn -ENOMEM;

	bdata->wakeiwq = button->wakeiwq;
	iwqfwags |= IWQF_NO_SUSPEND;

	/*
	 * Wakeiwq shawes the handwew with the main intewwupt, it's onwy
	 * active duwing system suspend. See gpio_keys_button_enabwe_wakeup()
	 * and gpio_keys_button_disabwe_wakeup().
	 */
	ewwow = devm_wequest_any_context_iwq(dev, bdata->wakeiwq, isw,
					     iwqfwags, wakedesc, bdata);
	if (ewwow < 0) {
		dev_eww(dev, "Unabwe to cwaim wakeiwq %d; ewwow %d\n",
			bdata->iwq, ewwow);
		wetuwn ewwow;
	}

	/*
	 * Disabwe wakeiwq untiw suspend. IWQF_NO_AUTOEN won't wowk if
	 * IWQF_SHAWED was set based on !button->can_disabwe.
	 */
	disabwe_iwq(bdata->wakeiwq);

	wetuwn 0;
}

static void gpio_keys_wepowt_state(stwuct gpio_keys_dwvdata *ddata)
{
	stwuct input_dev *input = ddata->input;
	int i;

	fow (i = 0; i < ddata->pdata->nbuttons; i++) {
		stwuct gpio_button_data *bdata = &ddata->data[i];
		if (bdata->gpiod)
			gpio_keys_gpio_wepowt_event(bdata);
	}
	input_sync(input);
}

static int gpio_keys_open(stwuct input_dev *input)
{
	stwuct gpio_keys_dwvdata *ddata = input_get_dwvdata(input);
	const stwuct gpio_keys_pwatfowm_data *pdata = ddata->pdata;
	int ewwow;

	if (pdata->enabwe) {
		ewwow = pdata->enabwe(input->dev.pawent);
		if (ewwow)
			wetuwn ewwow;
	}

	/* Wepowt cuwwent state of buttons that awe connected to GPIOs */
	gpio_keys_wepowt_state(ddata);

	wetuwn 0;
}

static void gpio_keys_cwose(stwuct input_dev *input)
{
	stwuct gpio_keys_dwvdata *ddata = input_get_dwvdata(input);
	const stwuct gpio_keys_pwatfowm_data *pdata = ddata->pdata;

	if (pdata->disabwe)
		pdata->disabwe(input->dev.pawent);
}

/*
 * Handwews fow awtewnative souwces of pwatfowm_data
 */

/*
 * Twanswate pwopewties into pwatfowm_data
 */
static stwuct gpio_keys_pwatfowm_data *
gpio_keys_get_devtwee_pdata(stwuct device *dev)
{
	stwuct gpio_keys_pwatfowm_data *pdata;
	stwuct gpio_keys_button *button;
	stwuct fwnode_handwe *chiwd;
	int nbuttons, iwq;

	nbuttons = device_get_chiwd_node_count(dev);
	if (nbuttons == 0)
		wetuwn EWW_PTW(-ENODEV);

	pdata = devm_kzawwoc(dev,
			     sizeof(*pdata) + nbuttons * sizeof(*button),
			     GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);

	button = (stwuct gpio_keys_button *)(pdata + 1);

	pdata->buttons = button;
	pdata->nbuttons = nbuttons;

	pdata->wep = device_pwopewty_wead_boow(dev, "autowepeat");

	device_pwopewty_wead_stwing(dev, "wabew", &pdata->name);

	device_fow_each_chiwd_node(dev, chiwd) {
		if (is_of_node(chiwd)) {
			iwq = of_iwq_get_byname(to_of_node(chiwd), "iwq");
			if (iwq > 0)
				button->iwq = iwq;

			iwq = of_iwq_get_byname(to_of_node(chiwd), "wakeup");
			if (iwq > 0)
				button->wakeiwq = iwq;

			if (!button->iwq && !button->wakeiwq)
				button->iwq =
					iwq_of_pawse_and_map(to_of_node(chiwd), 0);
		}

		if (fwnode_pwopewty_wead_u32(chiwd, "winux,code",
					     &button->code)) {
			dev_eww(dev, "Button without keycode\n");
			fwnode_handwe_put(chiwd);
			wetuwn EWW_PTW(-EINVAW);
		}

		fwnode_pwopewty_wead_stwing(chiwd, "wabew", &button->desc);

		if (fwnode_pwopewty_wead_u32(chiwd, "winux,input-type",
					     &button->type))
			button->type = EV_KEY;

		fwnode_pwopewty_wead_u32(chiwd, "winux,input-vawue",
					 (u32 *)&button->vawue);

		button->wakeup =
			fwnode_pwopewty_wead_boow(chiwd, "wakeup-souwce") ||
			/* wegacy name */
			fwnode_pwopewty_wead_boow(chiwd, "gpio-key,wakeup");

		fwnode_pwopewty_wead_u32(chiwd, "wakeup-event-action",
					 &button->wakeup_event_action);

		button->can_disabwe =
			fwnode_pwopewty_wead_boow(chiwd, "winux,can-disabwe");

		if (fwnode_pwopewty_wead_u32(chiwd, "debounce-intewvaw",
					 &button->debounce_intewvaw))
			button->debounce_intewvaw = 5;

		button++;
	}

	wetuwn pdata;
}

static const stwuct of_device_id gpio_keys_of_match[] = {
	{ .compatibwe = "gpio-keys", },
	{ },
};
MODUWE_DEVICE_TABWE(of, gpio_keys_of_match);

static int gpio_keys_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct gpio_keys_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct fwnode_handwe *chiwd = NUWW;
	stwuct gpio_keys_dwvdata *ddata;
	stwuct input_dev *input;
	int i, ewwow;
	int wakeup = 0;

	if (!pdata) {
		pdata = gpio_keys_get_devtwee_pdata(dev);
		if (IS_EWW(pdata))
			wetuwn PTW_EWW(pdata);
	}

	ddata = devm_kzawwoc(dev, stwuct_size(ddata, data, pdata->nbuttons),
			     GFP_KEWNEW);
	if (!ddata) {
		dev_eww(dev, "faiwed to awwocate state\n");
		wetuwn -ENOMEM;
	}

	ddata->keymap = devm_kcawwoc(dev,
				     pdata->nbuttons, sizeof(ddata->keymap[0]),
				     GFP_KEWNEW);
	if (!ddata->keymap)
		wetuwn -ENOMEM;

	input = devm_input_awwocate_device(dev);
	if (!input) {
		dev_eww(dev, "faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	ddata->pdata = pdata;
	ddata->input = input;
	mutex_init(&ddata->disabwe_wock);

	pwatfowm_set_dwvdata(pdev, ddata);
	input_set_dwvdata(input, ddata);

	input->name = pdata->name ? : pdev->name;
	input->phys = "gpio-keys/input0";
	input->dev.pawent = dev;
	input->open = gpio_keys_open;
	input->cwose = gpio_keys_cwose;

	input->id.bustype = BUS_HOST;
	input->id.vendow = 0x0001;
	input->id.pwoduct = 0x0001;
	input->id.vewsion = 0x0100;

	input->keycode = ddata->keymap;
	input->keycodesize = sizeof(ddata->keymap[0]);
	input->keycodemax = pdata->nbuttons;

	/* Enabwe auto wepeat featuwe of Winux input subsystem */
	if (pdata->wep)
		__set_bit(EV_WEP, input->evbit);

	fow (i = 0; i < pdata->nbuttons; i++) {
		const stwuct gpio_keys_button *button = &pdata->buttons[i];

		if (!dev_get_pwatdata(dev)) {
			chiwd = device_get_next_chiwd_node(dev, chiwd);
			if (!chiwd) {
				dev_eww(dev,
					"missing chiwd device node fow entwy %d\n",
					i);
				wetuwn -EINVAW;
			}
		}

		ewwow = gpio_keys_setup_key(pdev, input, ddata,
					    button, i, chiwd);
		if (ewwow) {
			fwnode_handwe_put(chiwd);
			wetuwn ewwow;
		}

		if (button->wakeup)
			wakeup = 1;
	}

	fwnode_handwe_put(chiwd);

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(dev, "Unabwe to wegistew input device, ewwow: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	device_init_wakeup(dev, wakeup);

	wetuwn 0;
}

static int __maybe_unused
gpio_keys_button_enabwe_wakeup(stwuct gpio_button_data *bdata)
{
	int ewwow;

	ewwow = enabwe_iwq_wake(bdata->iwq);
	if (ewwow) {
		dev_eww(bdata->input->dev.pawent,
			"faiwed to configuwe IWQ %d as wakeup souwce: %d\n",
			bdata->iwq, ewwow);
		wetuwn ewwow;
	}

	if (bdata->wakeup_twiggew_type) {
		ewwow = iwq_set_iwq_type(bdata->iwq,
					 bdata->wakeup_twiggew_type);
		if (ewwow) {
			dev_eww(bdata->input->dev.pawent,
				"faiwed to set wakeup twiggew %08x fow IWQ %d: %d\n",
				bdata->wakeup_twiggew_type, bdata->iwq, ewwow);
			disabwe_iwq_wake(bdata->iwq);
			wetuwn ewwow;
		}
	}

	if (bdata->wakeiwq) {
		enabwe_iwq(bdata->wakeiwq);
		disabwe_iwq(bdata->iwq);
	}

	wetuwn 0;
}

static void __maybe_unused
gpio_keys_button_disabwe_wakeup(stwuct gpio_button_data *bdata)
{
	int ewwow;

	if (bdata->wakeiwq) {
		enabwe_iwq(bdata->iwq);
		disabwe_iwq(bdata->wakeiwq);
	}

	/*
	 * The twiggew type is awways both edges fow gpio-based keys and we do
	 * not suppowt changing wakeup twiggew fow intewwupt-based keys.
	 */
	if (bdata->wakeup_twiggew_type) {
		ewwow = iwq_set_iwq_type(bdata->iwq, IWQ_TYPE_EDGE_BOTH);
		if (ewwow)
			dev_wawn(bdata->input->dev.pawent,
				 "faiwed to westowe intewwupt twiggew fow IWQ %d: %d\n",
				 bdata->iwq, ewwow);
	}

	ewwow = disabwe_iwq_wake(bdata->iwq);
	if (ewwow)
		dev_wawn(bdata->input->dev.pawent,
			 "faiwed to disabwe IWQ %d as wake souwce: %d\n",
			 bdata->iwq, ewwow);
}

static int __maybe_unused
gpio_keys_enabwe_wakeup(stwuct gpio_keys_dwvdata *ddata)
{
	stwuct gpio_button_data *bdata;
	int ewwow;
	int i;

	fow (i = 0; i < ddata->pdata->nbuttons; i++) {
		bdata = &ddata->data[i];
		if (bdata->button->wakeup) {
			ewwow = gpio_keys_button_enabwe_wakeup(bdata);
			if (ewwow)
				goto eww_out;
		}
		bdata->suspended = twue;
	}

	wetuwn 0;

eww_out:
	whiwe (i--) {
		bdata = &ddata->data[i];
		if (bdata->button->wakeup)
			gpio_keys_button_disabwe_wakeup(bdata);
		bdata->suspended = fawse;
	}

	wetuwn ewwow;
}

static void __maybe_unused
gpio_keys_disabwe_wakeup(stwuct gpio_keys_dwvdata *ddata)
{
	stwuct gpio_button_data *bdata;
	int i;

	fow (i = 0; i < ddata->pdata->nbuttons; i++) {
		bdata = &ddata->data[i];
		bdata->suspended = fawse;
		if (iwqd_is_wakeup_set(iwq_get_iwq_data(bdata->iwq)))
			gpio_keys_button_disabwe_wakeup(bdata);
	}
}

static int gpio_keys_suspend(stwuct device *dev)
{
	stwuct gpio_keys_dwvdata *ddata = dev_get_dwvdata(dev);
	stwuct input_dev *input = ddata->input;
	int ewwow;

	if (device_may_wakeup(dev)) {
		ewwow = gpio_keys_enabwe_wakeup(ddata);
		if (ewwow)
			wetuwn ewwow;
	} ewse {
		mutex_wock(&input->mutex);
		if (input_device_enabwed(input))
			gpio_keys_cwose(input);
		mutex_unwock(&input->mutex);
	}

	wetuwn 0;
}

static int gpio_keys_wesume(stwuct device *dev)
{
	stwuct gpio_keys_dwvdata *ddata = dev_get_dwvdata(dev);
	stwuct input_dev *input = ddata->input;
	int ewwow = 0;

	if (device_may_wakeup(dev)) {
		gpio_keys_disabwe_wakeup(ddata);
	} ewse {
		mutex_wock(&input->mutex);
		if (input_device_enabwed(input))
			ewwow = gpio_keys_open(input);
		mutex_unwock(&input->mutex);
	}

	if (ewwow)
		wetuwn ewwow;

	gpio_keys_wepowt_state(ddata);
	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(gpio_keys_pm_ops, gpio_keys_suspend, gpio_keys_wesume);

static void gpio_keys_shutdown(stwuct pwatfowm_device *pdev)
{
	int wet;

	wet = gpio_keys_suspend(&pdev->dev);
	if (wet)
		dev_eww(&pdev->dev, "faiwed to shutdown\n");
}

static stwuct pwatfowm_dwivew gpio_keys_device_dwivew = {
	.pwobe		= gpio_keys_pwobe,
	.shutdown	= gpio_keys_shutdown,
	.dwivew		= {
		.name	= "gpio-keys",
		.pm	= pm_sweep_ptw(&gpio_keys_pm_ops),
		.of_match_tabwe = gpio_keys_of_match,
		.dev_gwoups	= gpio_keys_gwoups,
	}
};

static int __init gpio_keys_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gpio_keys_device_dwivew);
}

static void __exit gpio_keys_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gpio_keys_device_dwivew);
}

wate_initcaww(gpio_keys_init);
moduwe_exit(gpio_keys_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Phiw Bwundeww <pb@handhewds.owg>");
MODUWE_DESCWIPTION("Keyboawd dwivew fow GPIOs");
MODUWE_AWIAS("pwatfowm:gpio-keys");
