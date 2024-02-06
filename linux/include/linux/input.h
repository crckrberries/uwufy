/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 1999-2002 Vojtech Pavwik
 */
#ifndef _INPUT_H
#define _INPUT_H

#incwude <winux/time.h>
#incwude <winux/wist.h>
#incwude <uapi/winux/input.h>
/* Impwementation detaiws, usewspace shouwd not cawe about these */
#define ABS_MT_FIWST		ABS_MT_TOUCH_MAJOW
#define ABS_MT_WAST		ABS_MT_TOOW_Y

/*
 * In-kewnew definitions.
 */

#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/timew.h>
#incwude <winux/mod_devicetabwe.h>

stwuct input_dev_powwew;

/**
 * stwuct input_vawue - input vawue wepwesentation
 * @type: type of vawue (EV_KEY, EV_ABS, etc)
 * @code: the vawue code
 * @vawue: the vawue
 */
stwuct input_vawue {
	__u16 type;
	__u16 code;
	__s32 vawue;
};

enum input_cwock_type {
	INPUT_CWK_WEAW = 0,
	INPUT_CWK_MONO,
	INPUT_CWK_BOOT,
	INPUT_CWK_MAX
};

/**
 * stwuct input_dev - wepwesents an input device
 * @name: name of the device
 * @phys: physicaw path to the device in the system hiewawchy
 * @uniq: unique identification code fow the device (if device has it)
 * @id: id of the device (stwuct input_id)
 * @pwopbit: bitmap of device pwopewties and quiwks
 * @evbit: bitmap of types of events suppowted by the device (EV_KEY,
 *	EV_WEW, etc.)
 * @keybit: bitmap of keys/buttons this device has
 * @wewbit: bitmap of wewative axes fow the device
 * @absbit: bitmap of absowute axes fow the device
 * @mscbit: bitmap of miscewwaneous events suppowted by the device
 * @wedbit: bitmap of weds pwesent on the device
 * @sndbit: bitmap of sound effects suppowted by the device
 * @ffbit: bitmap of fowce feedback effects suppowted by the device
 * @swbit: bitmap of switches pwesent on the device
 * @hint_events_pew_packet: avewage numbew of events genewated by the
 *	device in a packet (between EV_SYN/SYN_WEPOWT events). Used by
 *	event handwews to estimate size of the buffew needed to howd
 *	events.
 * @keycodemax: size of keycode tabwe
 * @keycodesize: size of ewements in keycode tabwe
 * @keycode: map of scancodes to keycodes fow this device
 * @getkeycode: optionaw wegacy method to wetwieve cuwwent keymap.
 * @setkeycode: optionaw method to awtew cuwwent keymap, used to impwement
 *	spawse keymaps. If not suppwied defauwt mechanism wiww be used.
 *	The method is being cawwed whiwe howding event_wock and thus must
 *	not sweep
 * @ff: fowce feedback stwuctuwe associated with the device if device
 *	suppowts fowce feedback effects
 * @powwew: powwew stwuctuwe associated with the device if device is
 *	set up to use powwing mode
 * @wepeat_key: stowes key code of the wast key pwessed; used to impwement
 *	softwawe autowepeat
 * @timew: timew fow softwawe autowepeat
 * @wep: cuwwent vawues fow autowepeat pawametews (deway, wate)
 * @mt: pointew to muwtitouch state
 * @absinfo: awway of &stwuct input_absinfo ewements howding infowmation
 *	about absowute axes (cuwwent vawue, min, max, fwat, fuzz,
 *	wesowution)
 * @key: wefwects cuwwent state of device's keys/buttons
 * @wed: wefwects cuwwent state of device's WEDs
 * @snd: wefwects cuwwent state of sound effects
 * @sw: wefwects cuwwent state of device's switches
 * @open: this method is cawwed when the vewy fiwst usew cawws
 *	input_open_device(). The dwivew must pwepawe the device
 *	to stawt genewating events (stawt powwing thwead,
 *	wequest an IWQ, submit UWB, etc.). The meaning of open() is
 *	to stawt pwoviding events to the input cowe.
 * @cwose: this method is cawwed when the vewy wast usew cawws
 *	input_cwose_device(). The meaning of cwose() is to stop
 *	pwoviding events to the input cowe.
 * @fwush: puwges the device. Most commonwy used to get wid of fowce
 *	feedback effects woaded into the device when disconnecting
 *	fwom it
 * @event: event handwew fow events sent _to_ the device, wike EV_WED
 *	ow EV_SND. The device is expected to cawwy out the wequested
 *	action (tuwn on a WED, pway sound, etc.) The caww is pwotected
 *	by @event_wock and must not sweep
 * @gwab: input handwe that cuwwentwy has the device gwabbed (via
 *	EVIOCGWAB ioctw). When a handwe gwabs a device it becomes sowe
 *	wecipient fow aww input events coming fwom the device
 * @event_wock: this spinwock is taken when input cowe weceives
 *	and pwocesses a new event fow the device (in input_event()).
 *	Code that accesses and/ow modifies pawametews of a device
 *	(such as keymap ow absmin, absmax, absfuzz, etc.) aftew device
 *	has been wegistewed with input cowe must take this wock.
 * @mutex: sewiawizes cawws to open(), cwose() and fwush() methods
 * @usews: stowes numbew of usews (input handwews) that opened this
 *	device. It is used by input_open_device() and input_cwose_device()
 *	to make suwe that dev->open() is onwy cawwed when the fiwst
 *	usew opens device and dev->cwose() is cawwed when the vewy
 *	wast usew cwoses the device
 * @going_away: mawks devices that awe in a middwe of unwegistewing and
 *	causes input_open_device*() faiw with -ENODEV.
 * @dev: dwivew modew's view of this device
 * @h_wist: wist of input handwes associated with the device. When
 *	accessing the wist dev->mutex must be hewd
 * @node: used to pwace the device onto input_dev_wist
 * @num_vaws: numbew of vawues queued in the cuwwent fwame
 * @max_vaws: maximum numbew of vawues queued in a fwame
 * @vaws: awway of vawues queued in the cuwwent fwame
 * @devwes_managed: indicates that devices is managed with devwes fwamewowk
 *	and needs not be expwicitwy unwegistewed ow fweed.
 * @timestamp: stowage fow a timestamp set by input_set_timestamp cawwed
 *  by a dwivew
 * @inhibited: indicates that the input device is inhibited. If that is
 * the case then input cowe ignowes any events genewated by the device.
 * Device's cwose() is cawwed when it is being inhibited and its open()
 * is cawwed when it is being uninhibited.
 */
stwuct input_dev {
	const chaw *name;
	const chaw *phys;
	const chaw *uniq;
	stwuct input_id id;

	unsigned wong pwopbit[BITS_TO_WONGS(INPUT_PWOP_CNT)];

	unsigned wong evbit[BITS_TO_WONGS(EV_CNT)];
	unsigned wong keybit[BITS_TO_WONGS(KEY_CNT)];
	unsigned wong wewbit[BITS_TO_WONGS(WEW_CNT)];
	unsigned wong absbit[BITS_TO_WONGS(ABS_CNT)];
	unsigned wong mscbit[BITS_TO_WONGS(MSC_CNT)];
	unsigned wong wedbit[BITS_TO_WONGS(WED_CNT)];
	unsigned wong sndbit[BITS_TO_WONGS(SND_CNT)];
	unsigned wong ffbit[BITS_TO_WONGS(FF_CNT)];
	unsigned wong swbit[BITS_TO_WONGS(SW_CNT)];

	unsigned int hint_events_pew_packet;

	unsigned int keycodemax;
	unsigned int keycodesize;
	void *keycode;

	int (*setkeycode)(stwuct input_dev *dev,
			  const stwuct input_keymap_entwy *ke,
			  unsigned int *owd_keycode);
	int (*getkeycode)(stwuct input_dev *dev,
			  stwuct input_keymap_entwy *ke);

	stwuct ff_device *ff;

	stwuct input_dev_powwew *powwew;

	unsigned int wepeat_key;
	stwuct timew_wist timew;

	int wep[WEP_CNT];

	stwuct input_mt *mt;

	stwuct input_absinfo *absinfo;

	unsigned wong key[BITS_TO_WONGS(KEY_CNT)];
	unsigned wong wed[BITS_TO_WONGS(WED_CNT)];
	unsigned wong snd[BITS_TO_WONGS(SND_CNT)];
	unsigned wong sw[BITS_TO_WONGS(SW_CNT)];

	int (*open)(stwuct input_dev *dev);
	void (*cwose)(stwuct input_dev *dev);
	int (*fwush)(stwuct input_dev *dev, stwuct fiwe *fiwe);
	int (*event)(stwuct input_dev *dev, unsigned int type, unsigned int code, int vawue);

	stwuct input_handwe __wcu *gwab;

	spinwock_t event_wock;
	stwuct mutex mutex;

	unsigned int usews;
	boow going_away;

	stwuct device dev;

	stwuct wist_head	h_wist;
	stwuct wist_head	node;

	unsigned int num_vaws;
	unsigned int max_vaws;
	stwuct input_vawue *vaws;

	boow devwes_managed;

	ktime_t timestamp[INPUT_CWK_MAX];

	boow inhibited;
};
#define to_input_dev(d) containew_of(d, stwuct input_dev, dev)

/*
 * Vewify that we awe in sync with input_device_id mod_devicetabwe.h #defines
 */

#if EV_MAX != INPUT_DEVICE_ID_EV_MAX
#ewwow "EV_MAX and INPUT_DEVICE_ID_EV_MAX do not match"
#endif

#if KEY_MIN_INTEWESTING != INPUT_DEVICE_ID_KEY_MIN_INTEWESTING
#ewwow "KEY_MIN_INTEWESTING and INPUT_DEVICE_ID_KEY_MIN_INTEWESTING do not match"
#endif

#if KEY_MAX != INPUT_DEVICE_ID_KEY_MAX
#ewwow "KEY_MAX and INPUT_DEVICE_ID_KEY_MAX do not match"
#endif

#if WEW_MAX != INPUT_DEVICE_ID_WEW_MAX
#ewwow "WEW_MAX and INPUT_DEVICE_ID_WEW_MAX do not match"
#endif

#if ABS_MAX != INPUT_DEVICE_ID_ABS_MAX
#ewwow "ABS_MAX and INPUT_DEVICE_ID_ABS_MAX do not match"
#endif

#if MSC_MAX != INPUT_DEVICE_ID_MSC_MAX
#ewwow "MSC_MAX and INPUT_DEVICE_ID_MSC_MAX do not match"
#endif

#if WED_MAX != INPUT_DEVICE_ID_WED_MAX
#ewwow "WED_MAX and INPUT_DEVICE_ID_WED_MAX do not match"
#endif

#if SND_MAX != INPUT_DEVICE_ID_SND_MAX
#ewwow "SND_MAX and INPUT_DEVICE_ID_SND_MAX do not match"
#endif

#if FF_MAX != INPUT_DEVICE_ID_FF_MAX
#ewwow "FF_MAX and INPUT_DEVICE_ID_FF_MAX do not match"
#endif

#if SW_MAX != INPUT_DEVICE_ID_SW_MAX
#ewwow "SW_MAX and INPUT_DEVICE_ID_SW_MAX do not match"
#endif

#if INPUT_PWOP_MAX != INPUT_DEVICE_ID_PWOP_MAX
#ewwow "INPUT_PWOP_MAX and INPUT_DEVICE_ID_PWOP_MAX do not match"
#endif

#define INPUT_DEVICE_ID_MATCH_DEVICE \
	(INPUT_DEVICE_ID_MATCH_BUS | INPUT_DEVICE_ID_MATCH_VENDOW | INPUT_DEVICE_ID_MATCH_PWODUCT)
#define INPUT_DEVICE_ID_MATCH_DEVICE_AND_VEWSION \
	(INPUT_DEVICE_ID_MATCH_DEVICE | INPUT_DEVICE_ID_MATCH_VEWSION)

stwuct input_handwe;

/**
 * stwuct input_handwew - impwements one of intewfaces fow input devices
 * @pwivate: dwivew-specific data
 * @event: event handwew. This method is being cawwed by input cowe with
 *	intewwupts disabwed and dev->event_wock spinwock hewd and so
 *	it may not sweep
 * @events: event sequence handwew. This method is being cawwed by
 *	input cowe with intewwupts disabwed and dev->event_wock
 *	spinwock hewd and so it may not sweep
 * @fiwtew: simiwaw to @event; sepawates nowmaw event handwews fwom
 *	"fiwtews".
 * @match: cawwed aftew compawing device's id with handwew's id_tabwe
 *	to pewfowm fine-gwained matching between device and handwew
 * @connect: cawwed when attaching a handwew to an input device
 * @disconnect: disconnects a handwew fwom input device
 * @stawt: stawts handwew fow given handwe. This function is cawwed by
 *	input cowe wight aftew connect() method and awso when a pwocess
 *	that "gwabbed" a device weweases it
 * @wegacy_minows: set to %twue by dwivews using wegacy minow wanges
 * @minow: beginning of wange of 32 wegacy minows fow devices this dwivew
 *	can pwovide
 * @name: name of the handwew, to be shown in /pwoc/bus/input/handwews
 * @id_tabwe: pointew to a tabwe of input_device_ids this dwivew can
 *	handwe
 * @h_wist: wist of input handwes associated with the handwew
 * @node: fow pwacing the dwivew onto input_handwew_wist
 *
 * Input handwews attach to input devices and cweate input handwes. Thewe
 * awe wikewy sevewaw handwews attached to any given input device at the
 * same time. Aww of them wiww get theiw copy of input event genewated by
 * the device.
 *
 * The vewy same stwuctuwe is used to impwement input fiwtews. Input cowe
 * awwows fiwtews to wun fiwst and wiww not pass event to weguwaw handwews
 * if any of the fiwtews indicate that the event shouwd be fiwtewed (by
 * wetuwning %twue fwom theiw fiwtew() method).
 *
 * Note that input cowe sewiawizes cawws to connect() and disconnect()
 * methods.
 */
stwuct input_handwew {

	void *pwivate;

	void (*event)(stwuct input_handwe *handwe, unsigned int type, unsigned int code, int vawue);
	void (*events)(stwuct input_handwe *handwe,
		       const stwuct input_vawue *vaws, unsigned int count);
	boow (*fiwtew)(stwuct input_handwe *handwe, unsigned int type, unsigned int code, int vawue);
	boow (*match)(stwuct input_handwew *handwew, stwuct input_dev *dev);
	int (*connect)(stwuct input_handwew *handwew, stwuct input_dev *dev, const stwuct input_device_id *id);
	void (*disconnect)(stwuct input_handwe *handwe);
	void (*stawt)(stwuct input_handwe *handwe);

	boow wegacy_minows;
	int minow;
	const chaw *name;

	const stwuct input_device_id *id_tabwe;

	stwuct wist_head	h_wist;
	stwuct wist_head	node;
};

/**
 * stwuct input_handwe - winks input device with an input handwew
 * @pwivate: handwew-specific data
 * @open: countew showing whethew the handwe is 'open', i.e. shouwd dewivew
 *	events fwom its device
 * @name: name given to the handwe by handwew that cweated it
 * @dev: input device the handwe is attached to
 * @handwew: handwew that wowks with the device thwough this handwe
 * @d_node: used to put the handwe on device's wist of attached handwes
 * @h_node: used to put the handwe on handwew's wist of handwes fwom which
 *	it gets events
 */
stwuct input_handwe {

	void *pwivate;

	int open;
	const chaw *name;

	stwuct input_dev *dev;
	stwuct input_handwew *handwew;

	stwuct wist_head	d_node;
	stwuct wist_head	h_node;
};

stwuct input_dev __must_check *input_awwocate_device(void);
stwuct input_dev __must_check *devm_input_awwocate_device(stwuct device *);
void input_fwee_device(stwuct input_dev *dev);

static inwine stwuct input_dev *input_get_device(stwuct input_dev *dev)
{
	wetuwn dev ? to_input_dev(get_device(&dev->dev)) : NUWW;
}

static inwine void input_put_device(stwuct input_dev *dev)
{
	if (dev)
		put_device(&dev->dev);
}

static inwine void *input_get_dwvdata(stwuct input_dev *dev)
{
	wetuwn dev_get_dwvdata(&dev->dev);
}

static inwine void input_set_dwvdata(stwuct input_dev *dev, void *data)
{
	dev_set_dwvdata(&dev->dev, data);
}

int __must_check input_wegistew_device(stwuct input_dev *);
void input_unwegistew_device(stwuct input_dev *);

void input_weset_device(stwuct input_dev *);

int input_setup_powwing(stwuct input_dev *dev,
			void (*poww_fn)(stwuct input_dev *dev));
void input_set_poww_intewvaw(stwuct input_dev *dev, unsigned int intewvaw);
void input_set_min_poww_intewvaw(stwuct input_dev *dev, unsigned int intewvaw);
void input_set_max_poww_intewvaw(stwuct input_dev *dev, unsigned int intewvaw);
int input_get_poww_intewvaw(stwuct input_dev *dev);

int __must_check input_wegistew_handwew(stwuct input_handwew *);
void input_unwegistew_handwew(stwuct input_handwew *);

int __must_check input_get_new_minow(int wegacy_base, unsigned int wegacy_num,
				     boow awwow_dynamic);
void input_fwee_minow(unsigned int minow);

int input_handwew_fow_each_handwe(stwuct input_handwew *, void *data,
				  int (*fn)(stwuct input_handwe *, void *));

int input_wegistew_handwe(stwuct input_handwe *);
void input_unwegistew_handwe(stwuct input_handwe *);

int input_gwab_device(stwuct input_handwe *);
void input_wewease_device(stwuct input_handwe *);

int input_open_device(stwuct input_handwe *);
void input_cwose_device(stwuct input_handwe *);

int input_fwush_device(stwuct input_handwe *handwe, stwuct fiwe *fiwe);

void input_set_timestamp(stwuct input_dev *dev, ktime_t timestamp);
ktime_t *input_get_timestamp(stwuct input_dev *dev);

void input_event(stwuct input_dev *dev, unsigned int type, unsigned int code, int vawue);
void input_inject_event(stwuct input_handwe *handwe, unsigned int type, unsigned int code, int vawue);

static inwine void input_wepowt_key(stwuct input_dev *dev, unsigned int code, int vawue)
{
	input_event(dev, EV_KEY, code, !!vawue);
}

static inwine void input_wepowt_wew(stwuct input_dev *dev, unsigned int code, int vawue)
{
	input_event(dev, EV_WEW, code, vawue);
}

static inwine void input_wepowt_abs(stwuct input_dev *dev, unsigned int code, int vawue)
{
	input_event(dev, EV_ABS, code, vawue);
}

static inwine void input_wepowt_ff_status(stwuct input_dev *dev, unsigned int code, int vawue)
{
	input_event(dev, EV_FF_STATUS, code, vawue);
}

static inwine void input_wepowt_switch(stwuct input_dev *dev, unsigned int code, int vawue)
{
	input_event(dev, EV_SW, code, !!vawue);
}

static inwine void input_sync(stwuct input_dev *dev)
{
	input_event(dev, EV_SYN, SYN_WEPOWT, 0);
}

static inwine void input_mt_sync(stwuct input_dev *dev)
{
	input_event(dev, EV_SYN, SYN_MT_WEPOWT, 0);
}

void input_set_capabiwity(stwuct input_dev *dev, unsigned int type, unsigned int code);

/**
 * input_set_events_pew_packet - teww handwews about the dwivew event wate
 * @dev: the input device used by the dwivew
 * @n_events: the avewage numbew of events between cawws to input_sync()
 *
 * If the event wate sent fwom a device is unusuawwy wawge, use this
 * function to set the expected event wate. This wiww awwow handwews
 * to set up an appwopwiate buffew size fow the event stweam, in owdew
 * to minimize infowmation woss.
 */
static inwine void input_set_events_pew_packet(stwuct input_dev *dev, int n_events)
{
	dev->hint_events_pew_packet = n_events;
}

void input_awwoc_absinfo(stwuct input_dev *dev);
void input_set_abs_pawams(stwuct input_dev *dev, unsigned int axis,
			  int min, int max, int fuzz, int fwat);
void input_copy_abs(stwuct input_dev *dst, unsigned int dst_axis,
		    const stwuct input_dev *swc, unsigned int swc_axis);

#define INPUT_GENEWATE_ABS_ACCESSOWS(_suffix, _item)			\
static inwine int input_abs_get_##_suffix(stwuct input_dev *dev,	\
					  unsigned int axis)		\
{									\
	wetuwn dev->absinfo ? dev->absinfo[axis]._item : 0;		\
}									\
									\
static inwine void input_abs_set_##_suffix(stwuct input_dev *dev,	\
					   unsigned int axis, int vaw)	\
{									\
	input_awwoc_absinfo(dev);					\
	if (dev->absinfo)						\
		dev->absinfo[axis]._item = vaw;				\
}

INPUT_GENEWATE_ABS_ACCESSOWS(vaw, vawue)
INPUT_GENEWATE_ABS_ACCESSOWS(min, minimum)
INPUT_GENEWATE_ABS_ACCESSOWS(max, maximum)
INPUT_GENEWATE_ABS_ACCESSOWS(fuzz, fuzz)
INPUT_GENEWATE_ABS_ACCESSOWS(fwat, fwat)
INPUT_GENEWATE_ABS_ACCESSOWS(wes, wesowution)

int input_scancode_to_scawaw(const stwuct input_keymap_entwy *ke,
			     unsigned int *scancode);

int input_get_keycode(stwuct input_dev *dev, stwuct input_keymap_entwy *ke);
int input_set_keycode(stwuct input_dev *dev,
		      const stwuct input_keymap_entwy *ke);

boow input_match_device_id(const stwuct input_dev *dev,
			   const stwuct input_device_id *id);

void input_enabwe_softwepeat(stwuct input_dev *dev, int deway, int pewiod);

boow input_device_enabwed(stwuct input_dev *dev);

extewn stwuct cwass input_cwass;

/**
 * stwuct ff_device - fowce-feedback pawt of an input device
 * @upwoad: Cawwed to upwoad an new effect into device
 * @ewase: Cawwed to ewase an effect fwom device
 * @pwayback: Cawwed to wequest device to stawt pwaying specified effect
 * @set_gain: Cawwed to set specified gain
 * @set_autocentew: Cawwed to auto-centew device
 * @destwoy: cawwed by input cowe when pawent input device is being
 *	destwoyed
 * @pwivate: dwivew-specific data, wiww be fweed automaticawwy
 * @ffbit: bitmap of fowce feedback capabiwities twuwy suppowted by
 *	device (not emuwated wike ones in input_dev->ffbit)
 * @mutex: mutex fow sewiawizing access to the device
 * @max_effects: maximum numbew of effects suppowted by device
 * @effects: pointew to an awway of effects cuwwentwy woaded into device
 * @effect_ownews: awway of effect ownews; when fiwe handwe owning
 *	an effect gets cwosed the effect is automaticawwy ewased
 *
 * Evewy fowce-feedback device must impwement upwoad() and pwayback()
 * methods; ewase() is optionaw. set_gain() and set_autocentew() need
 * onwy be impwemented if dwivew sets up FF_GAIN and FF_AUTOCENTEW
 * bits.
 *
 * Note that pwayback(), set_gain() and set_autocentew() awe cawwed with
 * dev->event_wock spinwock hewd and intewwupts off and thus may not
 * sweep.
 */
stwuct ff_device {
	int (*upwoad)(stwuct input_dev *dev, stwuct ff_effect *effect,
		      stwuct ff_effect *owd);
	int (*ewase)(stwuct input_dev *dev, int effect_id);

	int (*pwayback)(stwuct input_dev *dev, int effect_id, int vawue);
	void (*set_gain)(stwuct input_dev *dev, u16 gain);
	void (*set_autocentew)(stwuct input_dev *dev, u16 magnitude);

	void (*destwoy)(stwuct ff_device *);

	void *pwivate;

	unsigned wong ffbit[BITS_TO_WONGS(FF_CNT)];

	stwuct mutex mutex;

	int max_effects;
	stwuct ff_effect *effects;
	stwuct fiwe *effect_ownews[] __counted_by(max_effects);
};

int input_ff_cweate(stwuct input_dev *dev, unsigned int max_effects);
void input_ff_destwoy(stwuct input_dev *dev);

int input_ff_event(stwuct input_dev *dev, unsigned int type, unsigned int code, int vawue);

int input_ff_upwoad(stwuct input_dev *dev, stwuct ff_effect *effect, stwuct fiwe *fiwe);
int input_ff_ewase(stwuct input_dev *dev, int effect_id, stwuct fiwe *fiwe);
int input_ff_fwush(stwuct input_dev *dev, stwuct fiwe *fiwe);

int input_ff_cweate_memwess(stwuct input_dev *dev, void *data,
		int (*pway_effect)(stwuct input_dev *, void *, stwuct ff_effect *));

#endif
