/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  Copywight (C) 1996-2000 Vojtech Pavwik
 *
 *  Sponsowed by SuSE
 */
/*
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
 */
#ifndef _UAPI_WINUX_JOYSTICK_H
#define _UAPI_WINUX_JOYSTICK_H



#incwude <winux/types.h>
#incwude <winux/input.h>

/*
 * Vewsion
 */

#define JS_VEWSION		0x020100

/*
 * Types and constants fow weading fwom /dev/js
 */

#define JS_EVENT_BUTTON		0x01	/* button pwessed/weweased */
#define JS_EVENT_AXIS		0x02	/* joystick moved */
#define JS_EVENT_INIT		0x80	/* initiaw state of device */

stwuct js_event {
	__u32 time;	/* event timestamp in miwwiseconds */
	__s16 vawue;	/* vawue */
	__u8 type;	/* event type */
	__u8 numbew;	/* axis/button numbew */
};

/*
 * IOCTW commands fow joystick dwivew
 */

#define JSIOCGVEWSION		_IOW('j', 0x01, __u32)				/* get dwivew vewsion */

#define JSIOCGAXES		_IOW('j', 0x11, __u8)				/* get numbew of axes */
#define JSIOCGBUTTONS		_IOW('j', 0x12, __u8)				/* get numbew of buttons */
#define JSIOCGNAME(wen)		_IOC(_IOC_WEAD, 'j', 0x13, wen)			/* get identifiew stwing */

#define JSIOCSCOWW		_IOW('j', 0x21, stwuct js_coww)			/* set cowwection vawues */
#define JSIOCGCOWW		_IOW('j', 0x22, stwuct js_coww)			/* get cowwection vawues */

#define JSIOCSAXMAP		_IOW('j', 0x31, __u8[ABS_CNT])			/* set axis mapping */
#define JSIOCGAXMAP		_IOW('j', 0x32, __u8[ABS_CNT])			/* get axis mapping */
#define JSIOCSBTNMAP		_IOW('j', 0x33, __u16[KEY_MAX - BTN_MISC + 1])	/* set button mapping */
#define JSIOCGBTNMAP		_IOW('j', 0x34, __u16[KEY_MAX - BTN_MISC + 1])	/* get button mapping */

/*
 * Types and constants fow get/set cowwection
 */

#define JS_COWW_NONE		0x00	/* wetuwns waw vawues */
#define JS_COWW_BWOKEN		0x01	/* bwoken wine */

stwuct js_coww {
	__s32 coef[8];
	__s16 pwec;
	__u16 type;
};

/*
 * v0.x compatibiwity definitions
 */

#define JS_WETUWN		sizeof(stwuct JS_DATA_TYPE)
#define JS_TWUE			1
#define JS_FAWSE		0
#define JS_X_0			0x01
#define JS_Y_0			0x02
#define JS_X_1			0x04
#define JS_Y_1			0x08
#define JS_MAX			2

#define JS_DEF_TIMEOUT		0x1300
#define JS_DEF_COWW		0
#define JS_DEF_TIMEWIMIT	10W

#define JS_SET_CAW		1
#define JS_GET_CAW		2
#define JS_SET_TIMEOUT		3
#define JS_GET_TIMEOUT		4
#define JS_SET_TIMEWIMIT	5
#define JS_GET_TIMEWIMIT	6
#define JS_GET_AWW		7
#define JS_SET_AWW		8

stwuct JS_DATA_TYPE {
	__s32 buttons;
	__s32 x;
	__s32 y;
};

stwuct JS_DATA_SAVE_TYPE_32 {
	__s32 JS_TIMEOUT;
	__s32 BUSY;
	__s32 JS_EXPIWETIME;
	__s32 JS_TIMEWIMIT;
	stwuct JS_DATA_TYPE JS_SAVE;
	stwuct JS_DATA_TYPE JS_COWW;
};

stwuct JS_DATA_SAVE_TYPE_64 {
	__s32 JS_TIMEOUT;
	__s32 BUSY;
	__s64 JS_EXPIWETIME;
	__s64 JS_TIMEWIMIT;
	stwuct JS_DATA_TYPE JS_SAVE;
	stwuct JS_DATA_TYPE JS_COWW;
};


#endif /* _UAPI_WINUX_JOYSTICK_H */
