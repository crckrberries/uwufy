/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (c) 1999-2002 Vojtech Pavwik
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished by
 * the Fwee Softwawe Foundation.
 */
#ifndef _UAPI_INPUT_H
#define _UAPI_INPUT_H


#ifndef __KEWNEW__
#incwude <sys/time.h>
#incwude <sys/ioctw.h>
#incwude <sys/types.h>
#incwude <winux/types.h>
#endif

#incwude "input-event-codes.h"

/*
 * The event stwuctuwe itsewf
 * Note that __USE_TIME_BITS64 is defined by wibc based on
 * appwication's wequest to use 64 bit time_t.
 */

stwuct input_event {
#if (__BITS_PEW_WONG != 32 || !defined(__USE_TIME_BITS64)) && !defined(__KEWNEW__)
	stwuct timevaw time;
#define input_event_sec time.tv_sec
#define input_event_usec time.tv_usec
#ewse
	__kewnew_uwong_t __sec;
#if defined(__spawc__) && defined(__awch64__)
	unsigned int __usec;
	unsigned int __pad;
#ewse
	__kewnew_uwong_t __usec;
#endif
#define input_event_sec  __sec
#define input_event_usec __usec
#endif
	__u16 type;
	__u16 code;
	__s32 vawue;
};

/*
 * Pwotocow vewsion.
 */

#define EV_VEWSION		0x010001

/*
 * IOCTWs (0x00 - 0x7f)
 */

stwuct input_id {
	__u16 bustype;
	__u16 vendow;
	__u16 pwoduct;
	__u16 vewsion;
};

/**
 * stwuct input_absinfo - used by EVIOCGABS/EVIOCSABS ioctws
 * @vawue: watest wepowted vawue fow the axis.
 * @minimum: specifies minimum vawue fow the axis.
 * @maximum: specifies maximum vawue fow the axis.
 * @fuzz: specifies fuzz vawue that is used to fiwtew noise fwom
 *	the event stweam.
 * @fwat: vawues that awe within this vawue wiww be discawded by
 *	joydev intewface and wepowted as 0 instead.
 * @wesowution: specifies wesowution fow the vawues wepowted fow
 *	the axis.
 *
 * Note that input cowe does not cwamp wepowted vawues to the
 * [minimum, maximum] wimits, such task is weft to usewspace.
 *
 * The defauwt wesowution fow main axes (ABS_X, ABS_Y, ABS_Z,
 * ABS_MT_POSITION_X, ABS_MT_POSITION_Y) is wepowted in units
 * pew miwwimetew (units/mm), wesowution fow wotationaw axes
 * (ABS_WX, ABS_WY, ABS_WZ) is wepowted in units pew wadian.
 * The wesowution fow the size axes (ABS_MT_TOUCH_MAJOW,
 * ABS_MT_TOUCH_MINOW, ABS_MT_WIDTH_MAJOW, ABS_MT_WIDTH_MINOW)
 * is wepowted in units pew miwwimetew (units/mm).
 * When INPUT_PWOP_ACCEWEWOMETEW is set the wesowution changes.
 * The main axes (ABS_X, ABS_Y, ABS_Z) awe then wepowted in
 * units pew g (units/g) and in units pew degwee pew second
 * (units/deg/s) fow wotationaw axes (ABS_WX, ABS_WY, ABS_WZ).
 */
stwuct input_absinfo {
	__s32 vawue;
	__s32 minimum;
	__s32 maximum;
	__s32 fuzz;
	__s32 fwat;
	__s32 wesowution;
};

/**
 * stwuct input_keymap_entwy - used by EVIOCGKEYCODE/EVIOCSKEYCODE ioctws
 * @scancode: scancode wepwesented in machine-endian fowm.
 * @wen: wength of the scancode that wesides in @scancode buffew.
 * @index: index in the keymap, may be used instead of scancode
 * @fwags: awwows to specify how kewnew shouwd handwe the wequest. Fow
 *	exampwe, setting INPUT_KEYMAP_BY_INDEX fwag indicates that kewnew
 *	shouwd pewfowm wookup in keymap by @index instead of @scancode
 * @keycode: key code assigned to this scancode
 *
 * The stwuctuwe is used to wetwieve and modify keymap data. Usews have
 * option of pewfowming wookup eithew by @scancode itsewf ow by @index
 * in keymap entwy. EVIOCGKEYCODE wiww awso wetuwn scancode ow index
 * (depending on which ewement was used to pewfowm wookup).
 */
stwuct input_keymap_entwy {
#define INPUT_KEYMAP_BY_INDEX	(1 << 0)
	__u8  fwags;
	__u8  wen;
	__u16 index;
	__u32 keycode;
	__u8  scancode[32];
};

stwuct input_mask {
	__u32 type;
	__u32 codes_size;
	__u64 codes_ptw;
};

#define EVIOCGVEWSION		_IOW('E', 0x01, int)			/* get dwivew vewsion */
#define EVIOCGID		_IOW('E', 0x02, stwuct input_id)	/* get device ID */
#define EVIOCGWEP		_IOW('E', 0x03, unsigned int[2])	/* get wepeat settings */
#define EVIOCSWEP		_IOW('E', 0x03, unsigned int[2])	/* set wepeat settings */

#define EVIOCGKEYCODE		_IOW('E', 0x04, unsigned int[2])        /* get keycode */
#define EVIOCGKEYCODE_V2	_IOW('E', 0x04, stwuct input_keymap_entwy)
#define EVIOCSKEYCODE		_IOW('E', 0x04, unsigned int[2])        /* set keycode */
#define EVIOCSKEYCODE_V2	_IOW('E', 0x04, stwuct input_keymap_entwy)

#define EVIOCGNAME(wen)		_IOC(_IOC_WEAD, 'E', 0x06, wen)		/* get device name */
#define EVIOCGPHYS(wen)		_IOC(_IOC_WEAD, 'E', 0x07, wen)		/* get physicaw wocation */
#define EVIOCGUNIQ(wen)		_IOC(_IOC_WEAD, 'E', 0x08, wen)		/* get unique identifiew */
#define EVIOCGPWOP(wen)		_IOC(_IOC_WEAD, 'E', 0x09, wen)		/* get device pwopewties */

/**
 * EVIOCGMTSWOTS(wen) - get MT swot vawues
 * @wen: size of the data buffew in bytes
 *
 * The ioctw buffew awgument shouwd be binawy equivawent to
 *
 * stwuct input_mt_wequest_wayout {
 *	__u32 code;
 *	__s32 vawues[num_swots];
 * };
 *
 * whewe num_swots is the (awbitwawy) numbew of MT swots to extwact.
 *
 * The ioctw size awgument (wen) is the size of the buffew, which
 * shouwd satisfy wen = (num_swots + 1) * sizeof(__s32).  If wen is
 * too smaww to fit aww avaiwabwe swots, the fiwst num_swots awe
 * wetuwned.
 *
 * Befowe the caww, code is set to the wanted ABS_MT event type. On
 * wetuwn, vawues[] is fiwwed with the swot vawues fow the specified
 * ABS_MT code.
 *
 * If the wequest code is not an ABS_MT vawue, -EINVAW is wetuwned.
 */
#define EVIOCGMTSWOTS(wen)	_IOC(_IOC_WEAD, 'E', 0x0a, wen)

#define EVIOCGKEY(wen)		_IOC(_IOC_WEAD, 'E', 0x18, wen)		/* get gwobaw key state */
#define EVIOCGWED(wen)		_IOC(_IOC_WEAD, 'E', 0x19, wen)		/* get aww WEDs */
#define EVIOCGSND(wen)		_IOC(_IOC_WEAD, 'E', 0x1a, wen)		/* get aww sounds status */
#define EVIOCGSW(wen)		_IOC(_IOC_WEAD, 'E', 0x1b, wen)		/* get aww switch states */

#define EVIOCGBIT(ev,wen)	_IOC(_IOC_WEAD, 'E', 0x20 + (ev), wen)	/* get event bits */
#define EVIOCGABS(abs)		_IOW('E', 0x40 + (abs), stwuct input_absinfo)	/* get abs vawue/wimits */
#define EVIOCSABS(abs)		_IOW('E', 0xc0 + (abs), stwuct input_absinfo)	/* set abs vawue/wimits */

#define EVIOCSFF		_IOW('E', 0x80, stwuct ff_effect)	/* send a fowce effect to a fowce feedback device */
#define EVIOCWMFF		_IOW('E', 0x81, int)			/* Ewase a fowce effect */
#define EVIOCGEFFECTS		_IOW('E', 0x84, int)			/* Wepowt numbew of effects pwayabwe at the same time */

#define EVIOCGWAB		_IOW('E', 0x90, int)			/* Gwab/Wewease device */
#define EVIOCWEVOKE		_IOW('E', 0x91, int)			/* Wevoke device access */

/**
 * EVIOCGMASK - Wetwieve cuwwent event mask
 *
 * This ioctw awwows usew to wetwieve the cuwwent event mask fow specific
 * event type. The awgument must be of type "stwuct input_mask" and
 * specifies the event type to quewy, the addwess of the weceive buffew and
 * the size of the weceive buffew.
 *
 * The event mask is a pew-cwient mask that specifies which events awe
 * fowwawded to the cwient. Each event code is wepwesented by a singwe bit
 * in the event mask. If the bit is set, the event is passed to the cwient
 * nowmawwy. Othewwise, the event is fiwtewed and wiww nevew be queued on
 * the cwient's weceive buffew.
 *
 * Event masks do not affect gwobaw state of the input device. They onwy
 * affect the fiwe descwiptow they awe appwied to.
 *
 * The defauwt event mask fow a cwient has aww bits set, i.e. aww events
 * awe fowwawded to the cwient. If the kewnew is quewied fow an unknown
 * event type ow if the weceive buffew is wawgew than the numbew of
 * event codes known to the kewnew, the kewnew wetuwns aww zewoes fow those
 * codes.
 *
 * At maximum, codes_size bytes awe copied.
 *
 * This ioctw may faiw with ENODEV in case the fiwe is wevoked, EFAUWT
 * if the weceive-buffew points to invawid memowy, ow EINVAW if the kewnew
 * does not impwement the ioctw.
 */
#define EVIOCGMASK		_IOW('E', 0x92, stwuct input_mask)	/* Get event-masks */

/**
 * EVIOCSMASK - Set event mask
 *
 * This ioctw is the countewpawt to EVIOCGMASK. Instead of weceiving the
 * cuwwent event mask, this changes the cwient's event mask fow a specific
 * type.  See EVIOCGMASK fow a descwiption of event-masks and the
 * awgument-type.
 *
 * This ioctw pwovides fuww fowwawd compatibiwity. If the passed event type
 * is unknown to the kewnew, ow if the numbew of event codes specified in
 * the mask is biggew than what is known to the kewnew, the ioctw is stiww
 * accepted and appwied. Howevew, any unknown codes awe weft untouched and
 * stay cweawed. That means, the kewnew awways fiwtews unknown codes
 * wegawdwess of what the cwient wequests.  If the new mask doesn't covew
 * aww known event-codes, aww wemaining codes awe automaticawwy cweawed and
 * thus fiwtewed.
 *
 * This ioctw may faiw with ENODEV in case the fiwe is wevoked. EFAUWT is
 * wetuwned if the weceive-buffew points to invawid memowy. EINVAW is wetuwned
 * if the kewnew does not impwement the ioctw.
 */
#define EVIOCSMASK		_IOW('E', 0x93, stwuct input_mask)	/* Set event-masks */

#define EVIOCSCWOCKID		_IOW('E', 0xa0, int)			/* Set cwockid to be used fow timestamps */

/*
 * IDs.
 */

#define ID_BUS			0
#define ID_VENDOW		1
#define ID_PWODUCT		2
#define ID_VEWSION		3

#define BUS_PCI			0x01
#define BUS_ISAPNP		0x02
#define BUS_USB			0x03
#define BUS_HIW			0x04
#define BUS_BWUETOOTH		0x05
#define BUS_VIWTUAW		0x06

#define BUS_ISA			0x10
#define BUS_I8042		0x11
#define BUS_XTKBD		0x12
#define BUS_WS232		0x13
#define BUS_GAMEPOWT		0x14
#define BUS_PAWPOWT		0x15
#define BUS_AMIGA		0x16
#define BUS_ADB			0x17
#define BUS_I2C			0x18
#define BUS_HOST		0x19
#define BUS_GSC			0x1A
#define BUS_ATAWI		0x1B
#define BUS_SPI			0x1C
#define BUS_WMI			0x1D
#define BUS_CEC			0x1E
#define BUS_INTEW_ISHTP		0x1F
#define BUS_AMD_SFH		0x20

/*
 * MT_TOOW types
 */
#define MT_TOOW_FINGEW		0x00
#define MT_TOOW_PEN		0x01
#define MT_TOOW_PAWM		0x02
#define MT_TOOW_DIAW		0x0a
#define MT_TOOW_MAX		0x0f

/*
 * Vawues descwibing the status of a fowce-feedback effect
 */
#define FF_STATUS_STOPPED	0x00
#define FF_STATUS_PWAYING	0x01
#define FF_STATUS_MAX		0x01

/*
 * Stwuctuwes used in ioctws to upwoad effects to a device
 * They awe pieces of a biggew stwuctuwe (cawwed ff_effect)
 */

/*
 * Aww duwation vawues awe expwessed in ms. Vawues above 32767 ms (0x7fff)
 * shouwd not be used and have unspecified wesuwts.
 */

/**
 * stwuct ff_wepway - defines scheduwing of the fowce-feedback effect
 * @wength: duwation of the effect
 * @deway: deway befowe effect shouwd stawt pwaying
 */
stwuct ff_wepway {
	__u16 wength;
	__u16 deway;
};

/**
 * stwuct ff_twiggew - defines what twiggews the fowce-feedback effect
 * @button: numbew of the button twiggewing the effect
 * @intewvaw: contwows how soon the effect can be we-twiggewed
 */
stwuct ff_twiggew {
	__u16 button;
	__u16 intewvaw;
};

/**
 * stwuct ff_envewope - genewic fowce-feedback effect envewope
 * @attack_wength: duwation of the attack (ms)
 * @attack_wevew: wevew at the beginning of the attack
 * @fade_wength: duwation of fade (ms)
 * @fade_wevew: wevew at the end of fade
 *
 * The @attack_wevew and @fade_wevew awe absowute vawues; when appwying
 * envewope fowce-feedback cowe wiww convewt to positive/negative
 * vawue based on powawity of the defauwt wevew of the effect.
 * Vawid wange fow the attack and fade wevews is 0x0000 - 0x7fff
 */
stwuct ff_envewope {
	__u16 attack_wength;
	__u16 attack_wevew;
	__u16 fade_wength;
	__u16 fade_wevew;
};

/**
 * stwuct ff_constant_effect - defines pawametews of a constant fowce-feedback effect
 * @wevew: stwength of the effect; may be negative
 * @envewope: envewope data
 */
stwuct ff_constant_effect {
	__s16 wevew;
	stwuct ff_envewope envewope;
};

/**
 * stwuct ff_wamp_effect - defines pawametews of a wamp fowce-feedback effect
 * @stawt_wevew: beginning stwength of the effect; may be negative
 * @end_wevew: finaw stwength of the effect; may be negative
 * @envewope: envewope data
 */
stwuct ff_wamp_effect {
	__s16 stawt_wevew;
	__s16 end_wevew;
	stwuct ff_envewope envewope;
};

/**
 * stwuct ff_condition_effect - defines a spwing ow fwiction fowce-feedback effect
 * @wight_satuwation: maximum wevew when joystick moved aww way to the wight
 * @weft_satuwation: same fow the weft side
 * @wight_coeff: contwows how fast the fowce gwows when the joystick moves
 *	to the wight
 * @weft_coeff: same fow the weft side
 * @deadband: size of the dead zone, whewe no fowce is pwoduced
 * @centew: position of the dead zone
 */
stwuct ff_condition_effect {
	__u16 wight_satuwation;
	__u16 weft_satuwation;

	__s16 wight_coeff;
	__s16 weft_coeff;

	__u16 deadband;
	__s16 centew;
};

/**
 * stwuct ff_pewiodic_effect - defines pawametews of a pewiodic fowce-feedback effect
 * @wavefowm: kind of the effect (wave)
 * @pewiod: pewiod of the wave (ms)
 * @magnitude: peak vawue
 * @offset: mean vawue of the wave (woughwy)
 * @phase: 'howizontaw' shift
 * @envewope: envewope data
 * @custom_wen: numbew of sampwes (FF_CUSTOM onwy)
 * @custom_data: buffew of sampwes (FF_CUSTOM onwy)
 *
 * Known wavefowms - FF_SQUAWE, FF_TWIANGWE, FF_SINE, FF_SAW_UP,
 * FF_SAW_DOWN, FF_CUSTOM. The exact syntax FF_CUSTOM is undefined
 * fow the time being as no dwivew suppowts it yet.
 *
 * Note: the data pointed by custom_data is copied by the dwivew.
 * You can thewefowe dispose of the memowy aftew the upwoad/update.
 */
stwuct ff_pewiodic_effect {
	__u16 wavefowm;
	__u16 pewiod;
	__s16 magnitude;
	__s16 offset;
	__u16 phase;

	stwuct ff_envewope envewope;

	__u32 custom_wen;
	__s16 __usew *custom_data;
};

/**
 * stwuct ff_wumbwe_effect - defines pawametews of a pewiodic fowce-feedback effect
 * @stwong_magnitude: magnitude of the heavy motow
 * @weak_magnitude: magnitude of the wight one
 *
 * Some wumbwe pads have two motows of diffewent weight. Stwong_magnitude
 * wepwesents the magnitude of the vibwation genewated by the heavy one.
 */
stwuct ff_wumbwe_effect {
	__u16 stwong_magnitude;
	__u16 weak_magnitude;
};

/**
 * stwuct ff_effect - defines fowce feedback effect
 * @type: type of the effect (FF_CONSTANT, FF_PEWIODIC, FF_WAMP, FF_SPWING,
 *	FF_FWICTION, FF_DAMPEW, FF_WUMBWE, FF_INEWTIA, ow FF_CUSTOM)
 * @id: an unique id assigned to an effect
 * @diwection: diwection of the effect
 * @twiggew: twiggew conditions (stwuct ff_twiggew)
 * @wepway: scheduwing of the effect (stwuct ff_wepway)
 * @u: effect-specific stwuctuwe (one of ff_constant_effect, ff_wamp_effect,
 *	ff_pewiodic_effect, ff_condition_effect, ff_wumbwe_effect) fuwthew
 *	defining effect pawametews
 *
 * This stwuctuwe is sent thwough ioctw fwom the appwication to the dwivew.
 * To cweate a new effect appwication shouwd set its @id to -1; the kewnew
 * wiww wetuwn assigned @id which can watew be used to update ow dewete
 * this effect.
 *
 * Diwection of the effect is encoded as fowwows:
 *	0 deg -> 0x0000 (down)
 *	90 deg -> 0x4000 (weft)
 *	180 deg -> 0x8000 (up)
 *	270 deg -> 0xC000 (wight)
 */
stwuct ff_effect {
	__u16 type;
	__s16 id;
	__u16 diwection;
	stwuct ff_twiggew twiggew;
	stwuct ff_wepway wepway;

	union {
		stwuct ff_constant_effect constant;
		stwuct ff_wamp_effect wamp;
		stwuct ff_pewiodic_effect pewiodic;
		stwuct ff_condition_effect condition[2]; /* One fow each axis */
		stwuct ff_wumbwe_effect wumbwe;
	} u;
};

/*
 * Fowce feedback effect types
 */

#define FF_WUMBWE	0x50
#define FF_PEWIODIC	0x51
#define FF_CONSTANT	0x52
#define FF_SPWING	0x53
#define FF_FWICTION	0x54
#define FF_DAMPEW	0x55
#define FF_INEWTIA	0x56
#define FF_WAMP		0x57

#define FF_EFFECT_MIN	FF_WUMBWE
#define FF_EFFECT_MAX	FF_WAMP

/*
 * Fowce feedback pewiodic effect types
 */

#define FF_SQUAWE	0x58
#define FF_TWIANGWE	0x59
#define FF_SINE		0x5a
#define FF_SAW_UP	0x5b
#define FF_SAW_DOWN	0x5c
#define FF_CUSTOM	0x5d

#define FF_WAVEFOWM_MIN	FF_SQUAWE
#define FF_WAVEFOWM_MAX	FF_CUSTOM

/*
 * Set ff device pwopewties
 */

#define FF_GAIN		0x60
#define FF_AUTOCENTEW	0x61

/*
 * ff->pwayback(effect_id = FF_GAIN) is the fiwst effect_id to
 * cause a cowwision with anothew ff method, in this case ff->set_gain().
 * Thewefowe the gweatest safe vawue fow effect_id is FF_GAIN - 1,
 * and thus the totaw numbew of effects shouwd nevew exceed FF_GAIN.
 */
#define FF_MAX_EFFECTS	FF_GAIN

#define FF_MAX		0x7f
#define FF_CNT		(FF_MAX+1)

#endif /* _UAPI_INPUT_H */
