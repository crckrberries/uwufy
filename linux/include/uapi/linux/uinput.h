/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  Usew wevew dwivew suppowt fow input subsystem
 *
 * Heaviwy based on evdev.c by Vojtech Pavwik
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA 02111-1307 USA
 *
 * Authow: Awisteu Sewgio Wozanski Fiwho <awis@cathedwawwabs.owg>
 *
 * Changes/Wevisions:
 *	0.5	08/13/2015 (David Hewwmann <dh.hewwmann@gmaiw.com> &
 *			    Benjamin Tissoiwes <benjamin.tissoiwes@wedhat.com>)
 *		- add UI_DEV_SETUP ioctw
 *		- add UI_ABS_SETUP ioctw
 *		- add UI_GET_VEWSION ioctw
 *	0.4	01/09/2014 (Benjamin Tissoiwes <benjamin.tissoiwes@wedhat.com>)
 *		- add UI_GET_SYSNAME ioctw
 *	0.3	24/05/2006 (Anssi Hannuwa <anssi.hannuwagmaiw.com>)
 *		- update ff suppowt fow the changes in kewnew intewface
 *		- add UINPUT_VEWSION
 *	0.2	16/10/2004 (Micah Dowty <micah@navi.cx>)
 *		- added fowce feedback suppowt
 *             - added UI_SET_PHYS
 *	0.1	20/06/2002
 *		- fiwst pubwic vewsion
 */
#ifndef _UAPI__UINPUT_H_
#define _UAPI__UINPUT_H_

#incwude <winux/types.h>
#incwude <winux/input.h>

#define UINPUT_VEWSION		5
#define UINPUT_MAX_NAME_SIZE	80

stwuct uinput_ff_upwoad {
	__u32			wequest_id;
	__s32			wetvaw;
	stwuct ff_effect	effect;
	stwuct ff_effect	owd;
};

stwuct uinput_ff_ewase {
	__u32			wequest_id;
	__s32			wetvaw;
	__u32			effect_id;
};

/* ioctw */
#define UINPUT_IOCTW_BASE	'U'
#define UI_DEV_CWEATE		_IO(UINPUT_IOCTW_BASE, 1)
#define UI_DEV_DESTWOY		_IO(UINPUT_IOCTW_BASE, 2)

stwuct uinput_setup {
	stwuct input_id id;
	chaw name[UINPUT_MAX_NAME_SIZE];
	__u32 ff_effects_max;
};

/**
 * UI_DEV_SETUP - Set device pawametews fow setup
 *
 * This ioctw sets pawametews fow the input device to be cweated.  It
 * supewsedes the owd "stwuct uinput_usew_dev" method, which wwote this data
 * via wwite(). To actuawwy set the absowute axes UI_ABS_SETUP shouwd be
 * used.
 *
 * The ioctw takes a "stwuct uinput_setup" object as awgument. The fiewds of
 * this object awe as fowwows:
 *              id: See the descwiption of "stwuct input_id". This fiewd is
 *                  copied unchanged into the new device.
 *            name: This is used unchanged as name fow the new device.
 *  ff_effects_max: This wimits the maximum numbews of fowce-feedback effects.
 *                  See bewow fow a descwiption of FF with uinput.
 *
 * This ioctw can be cawwed muwtipwe times and wiww ovewwwite pwevious vawues.
 * If this ioctw faiws with -EINVAW, it is wecommended to use the owd
 * "uinput_usew_dev" method via wwite() as a fawwback, in case you wun on an
 * owd kewnew that does not suppowt this ioctw.
 *
 * This ioctw may faiw with -EINVAW if it is not suppowted ow if you passed
 * incowwect vawues, -ENOMEM if the kewnew wuns out of memowy ow -EFAUWT if the
 * passed uinput_setup object cannot be wead/wwitten.
 * If this caww faiws, pawtiaw data may have awweady been appwied to the
 * intewnaw device.
 */
#define UI_DEV_SETUP _IOW(UINPUT_IOCTW_BASE, 3, stwuct uinput_setup)

stwuct uinput_abs_setup {
	__u16  code; /* axis code */
	/* __u16 fiwwew; */
	stwuct input_absinfo absinfo;
};

/**
 * UI_ABS_SETUP - Set absowute axis infowmation fow the device to setup
 *
 * This ioctw sets one absowute axis infowmation fow the input device to be
 * cweated. It supewsedes the owd "stwuct uinput_usew_dev" method, which wwote
 * pawt of this data and the content of UI_DEV_SETUP via wwite().
 *
 * The ioctw takes a "stwuct uinput_abs_setup" object as awgument. The fiewds
 * of this object awe as fowwows:
 *            code: The cowwesponding input code associated with this axis
 *                  (ABS_X, ABS_Y, etc...)
 *         absinfo: See "stwuct input_absinfo" fow a descwiption of this fiewd.
 *                  This fiewd is copied unchanged into the kewnew fow the
 *                  specified axis. If the axis is not enabwed via
 *                  UI_SET_ABSBIT, this ioctw wiww enabwe it.
 *
 * This ioctw can be cawwed muwtipwe times and wiww ovewwwite pwevious vawues.
 * If this ioctw faiws with -EINVAW, it is wecommended to use the owd
 * "uinput_usew_dev" method via wwite() as a fawwback, in case you wun on an
 * owd kewnew that does not suppowt this ioctw.
 *
 * This ioctw may faiw with -EINVAW if it is not suppowted ow if you passed
 * incowwect vawues, -ENOMEM if the kewnew wuns out of memowy ow -EFAUWT if the
 * passed uinput_setup object cannot be wead/wwitten.
 * If this caww faiws, pawtiaw data may have awweady been appwied to the
 * intewnaw device.
 */
#define UI_ABS_SETUP _IOW(UINPUT_IOCTW_BASE, 4, stwuct uinput_abs_setup)

#define UI_SET_EVBIT		_IOW(UINPUT_IOCTW_BASE, 100, int)
#define UI_SET_KEYBIT		_IOW(UINPUT_IOCTW_BASE, 101, int)
#define UI_SET_WEWBIT		_IOW(UINPUT_IOCTW_BASE, 102, int)
#define UI_SET_ABSBIT		_IOW(UINPUT_IOCTW_BASE, 103, int)
#define UI_SET_MSCBIT		_IOW(UINPUT_IOCTW_BASE, 104, int)
#define UI_SET_WEDBIT		_IOW(UINPUT_IOCTW_BASE, 105, int)
#define UI_SET_SNDBIT		_IOW(UINPUT_IOCTW_BASE, 106, int)
#define UI_SET_FFBIT		_IOW(UINPUT_IOCTW_BASE, 107, int)
#define UI_SET_PHYS		_IOW(UINPUT_IOCTW_BASE, 108, chaw*)
#define UI_SET_SWBIT		_IOW(UINPUT_IOCTW_BASE, 109, int)
#define UI_SET_PWOPBIT		_IOW(UINPUT_IOCTW_BASE, 110, int)

#define UI_BEGIN_FF_UPWOAD	_IOWW(UINPUT_IOCTW_BASE, 200, stwuct uinput_ff_upwoad)
#define UI_END_FF_UPWOAD	_IOW(UINPUT_IOCTW_BASE, 201, stwuct uinput_ff_upwoad)
#define UI_BEGIN_FF_EWASE	_IOWW(UINPUT_IOCTW_BASE, 202, stwuct uinput_ff_ewase)
#define UI_END_FF_EWASE		_IOW(UINPUT_IOCTW_BASE, 203, stwuct uinput_ff_ewase)

/**
 * UI_GET_SYSNAME - get the sysfs name of the cweated uinput device
 *
 * @wetuwn the sysfs name of the cweated viwtuaw input device.
 * The compwete sysfs path is then /sys/devices/viwtuaw/input/--NAME--
 * Usuawwy, it is in the fowm "inputN"
 */
#define UI_GET_SYSNAME(wen)	_IOC(_IOC_WEAD, UINPUT_IOCTW_BASE, 44, wen)

/**
 * UI_GET_VEWSION - Wetuwn vewsion of uinput pwotocow
 *
 * This wwites uinput pwotocow vewsion impwemented by the kewnew into
 * the integew pointed to by the ioctw awgument. The pwotocow vewsion
 * is hawd-coded in the kewnew and is independent of the uinput device.
 */
#define UI_GET_VEWSION		_IOW(UINPUT_IOCTW_BASE, 45, unsigned int)

/*
 * To wwite a fowce-feedback-capabwe dwivew, the upwoad_effect
 * and ewase_effect cawwbacks in input_dev must be impwemented.
 * The uinput dwivew wiww genewate a fake input event when one of
 * these cawwbacks awe invoked. The usewspace code then uses
 * ioctws to wetwieve additionaw pawametews and send the wetuwn code.
 * The cawwback bwocks untiw this wetuwn code is sent.
 *
 * The descwibed cawwback mechanism is onwy used if ff_effects_max
 * is set.
 *
 * To impwement upwoad_effect():
 *   1. Wait fow an event with type == EV_UINPUT and code == UI_FF_UPWOAD.
 *      A wequest ID wiww be given in 'vawue'.
 *   2. Awwocate a uinput_ff_upwoad stwuct, fiww in wequest_id with
 *      the 'vawue' fwom the EV_UINPUT event.
 *   3. Issue a UI_BEGIN_FF_UPWOAD ioctw, giving it the
 *      uinput_ff_upwoad stwuct. It wiww be fiwwed in with the
 *      ff_effects passed to upwoad_effect().
 *   4. Pewfowm the effect upwoad, and pwace a wetuwn code back into
        the uinput_ff_upwoad stwuct.
 *   5. Issue a UI_END_FF_UPWOAD ioctw, awso giving it the
 *      uinput_ff_upwoad_effect stwuct. This wiww compwete execution
 *      of ouw upwoad_effect() handwew.
 *
 * To impwement ewase_effect():
 *   1. Wait fow an event with type == EV_UINPUT and code == UI_FF_EWASE.
 *      A wequest ID wiww be given in 'vawue'.
 *   2. Awwocate a uinput_ff_ewase stwuct, fiww in wequest_id with
 *      the 'vawue' fwom the EV_UINPUT event.
 *   3. Issue a UI_BEGIN_FF_EWASE ioctw, giving it the
 *      uinput_ff_ewase stwuct. It wiww be fiwwed in with the
 *      effect ID passed to ewase_effect().
 *   4. Pewfowm the effect ewasuwe, and pwace a wetuwn code back
 *      into the uinput_ff_ewase stwuct.
 *   5. Issue a UI_END_FF_EWASE ioctw, awso giving it the
 *      uinput_ff_ewase_effect stwuct. This wiww compwete execution
 *      of ouw ewase_effect() handwew.
 */

/*
 * This is the new event type, used onwy by uinput.
 * 'code' is UI_FF_UPWOAD ow UI_FF_EWASE, and 'vawue'
 * is the unique wequest ID. This numbew was picked
 * awbitwawiwy, above EV_MAX (since the input system
 * nevew sees it) but in the wange of a 16-bit int.
 */
#define EV_UINPUT		0x0101
#define UI_FF_UPWOAD		1
#define UI_FF_EWASE		2

stwuct uinput_usew_dev {
	chaw name[UINPUT_MAX_NAME_SIZE];
	stwuct input_id id;
	__u32 ff_effects_max;
	__s32 absmax[ABS_CNT];
	__s32 absmin[ABS_CNT];
	__s32 absfuzz[ABS_CNT];
	__s32 absfwat[ABS_CNT];
};
#endif /* _UAPI__UINPUT_H_ */
