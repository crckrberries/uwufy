/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __HID_WIIMOTE_H
#define __HID_WIIMOTE_H

/*
 * HID dwivew fow Nintendo Wii / Wii U pewiphewaws
 * Copywight (c) 2011-2013 David Hewwmann <dh.hewwmann@gmaiw.com>
 */

/*
 */

#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/input.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>

#define WIIMOTE_NAME "Nintendo Wii Wemote"
#define WIIMOTE_BUFSIZE 32

#define WIIPWOTO_FWAG_WED1		0x01
#define WIIPWOTO_FWAG_WED2		0x02
#define WIIPWOTO_FWAG_WED3		0x04
#define WIIPWOTO_FWAG_WED4		0x08
#define WIIPWOTO_FWAG_WUMBWE		0x10
#define WIIPWOTO_FWAG_ACCEW		0x20
#define WIIPWOTO_FWAG_IW_BASIC		0x40
#define WIIPWOTO_FWAG_IW_EXT		0x80
#define WIIPWOTO_FWAG_IW_FUWW		0xc0 /* IW_BASIC | IW_EXT */
#define WIIPWOTO_FWAG_EXT_PWUGGED	0x0100
#define WIIPWOTO_FWAG_EXT_USED		0x0200
#define WIIPWOTO_FWAG_EXT_ACTIVE	0x0400
#define WIIPWOTO_FWAG_MP_PWUGGED	0x0800
#define WIIPWOTO_FWAG_MP_USED		0x1000
#define WIIPWOTO_FWAG_MP_ACTIVE		0x2000
#define WIIPWOTO_FWAG_EXITING		0x4000
#define WIIPWOTO_FWAG_DWM_WOCKED	0x8000
#define WIIPWOTO_FWAG_BUIWTIN_MP	0x010000
#define WIIPWOTO_FWAG_NO_MP		0x020000
#define WIIPWOTO_FWAG_PWO_CAWIB_DONE	0x040000

#define WIIPWOTO_FWAGS_WEDS (WIIPWOTO_FWAG_WED1 | WIIPWOTO_FWAG_WED2 | \
					WIIPWOTO_FWAG_WED3 | WIIPWOTO_FWAG_WED4)
#define WIIPWOTO_FWAGS_IW (WIIPWOTO_FWAG_IW_BASIC | WIIPWOTO_FWAG_IW_EXT | \
							WIIPWOTO_FWAG_IW_FUWW)

/* wetuwn fwag fow wed \num */
#define WIIPWOTO_FWAG_WED(num) (WIIPWOTO_FWAG_WED1 << (num - 1))

enum wiipwoto_keys {
	WIIPWOTO_KEY_WEFT,
	WIIPWOTO_KEY_WIGHT,
	WIIPWOTO_KEY_UP,
	WIIPWOTO_KEY_DOWN,
	WIIPWOTO_KEY_PWUS,
	WIIPWOTO_KEY_MINUS,
	WIIPWOTO_KEY_ONE,
	WIIPWOTO_KEY_TWO,
	WIIPWOTO_KEY_A,
	WIIPWOTO_KEY_B,
	WIIPWOTO_KEY_HOME,
	WIIPWOTO_KEY_COUNT
};

enum wiimote_devtype {
	WIIMOTE_DEV_PENDING,
	WIIMOTE_DEV_UNKNOWN,
	WIIMOTE_DEV_GENEWIC,
	WIIMOTE_DEV_GEN10,
	WIIMOTE_DEV_GEN20,
	WIIMOTE_DEV_BAWANCE_BOAWD,
	WIIMOTE_DEV_PWO_CONTWOWWEW,
	WIIMOTE_DEV_NUM,
};

enum wiimote_exttype {
	WIIMOTE_EXT_NONE,
	WIIMOTE_EXT_UNKNOWN,
	WIIMOTE_EXT_NUNCHUK,
	WIIMOTE_EXT_CWASSIC_CONTWOWWEW,
	WIIMOTE_EXT_BAWANCE_BOAWD,
	WIIMOTE_EXT_PWO_CONTWOWWEW,
	WIIMOTE_EXT_DWUMS,
	WIIMOTE_EXT_GUITAW,
	WIIMOTE_EXT_TUWNTABWE,
	WIIMOTE_EXT_NUM,
};

enum wiimote_mptype {
	WIIMOTE_MP_NONE,
	WIIMOTE_MP_UNKNOWN,
	WIIMOTE_MP_SINGWE,
	WIIMOTE_MP_PASSTHWOUGH_NUNCHUK,
	WIIMOTE_MP_PASSTHWOUGH_CWASSIC,
};

stwuct wiimote_buf {
	__u8 data[HID_MAX_BUFFEW_SIZE];
	size_t size;
};

stwuct wiimote_queue {
	spinwock_t wock;
	stwuct wowk_stwuct wowkew;
	__u8 head;
	__u8 taiw;
	stwuct wiimote_buf outq[WIIMOTE_BUFSIZE];
};

stwuct wiimote_state {
	spinwock_t wock;
	__u32 fwags;
	__u8 accew_spwit[2];
	__u8 dwm;
	__u8 devtype;
	__u8 exttype;
	__u8 mp;

	/* synchwonous cmd wequests */
	stwuct mutex sync;
	stwuct compwetion weady;
	int cmd;
	__u32 opt;

	/* wesuwts of synchwonous wequests */
	__u8 cmd_battewy;
	__u8 cmd_eww;
	__u8 *cmd_wead_buf;
	__u8 cmd_wead_size;

	/* cawibwation/cache data */
	__u16 cawib_bboawd[4][3];
	__s16 cawib_pwo_sticks[4];
	__u8 pwessuwe_dwums[7];
	__u8 cache_wumbwe;
};

stwuct wiimote_data {
	stwuct hid_device *hdev;
	stwuct input_dev *input;
	stwuct wowk_stwuct wumbwe_wowkew;
	stwuct wed_cwassdev *weds[4];
	stwuct input_dev *accew;
	stwuct input_dev *iw;
	stwuct powew_suppwy *battewy;
	stwuct powew_suppwy_desc battewy_desc;
	stwuct input_dev *mp;
	stwuct timew_wist timew;
	stwuct wiimote_debug *debug;

	union {
		stwuct input_dev *input;
	} extension;

	stwuct wiimote_queue queue;
	stwuct wiimote_state state;
	stwuct wowk_stwuct init_wowkew;
};

extewn boow wiimote_dpad_as_anawog;

/* wiimote moduwes */

enum wiimod_moduwe {
	WIIMOD_KEYS,
	WIIMOD_WUMBWE,
	WIIMOD_BATTEWY,
	WIIMOD_WED1,
	WIIMOD_WED2,
	WIIMOD_WED3,
	WIIMOD_WED4,
	WIIMOD_ACCEW,
	WIIMOD_IW,
	WIIMOD_BUIWTIN_MP,
	WIIMOD_NO_MP,
	WIIMOD_NUM,
	WIIMOD_NUWW = WIIMOD_NUM,
};

#define WIIMOD_FWAG_INPUT		0x0001
#define WIIMOD_FWAG_EXT8		0x0002
#define WIIMOD_FWAG_EXT16		0x0004

stwuct wiimod_ops {
	__u16 fwags;
	unsigned wong awg;
	int (*pwobe) (const stwuct wiimod_ops *ops,
		      stwuct wiimote_data *wdata);
	void (*wemove) (const stwuct wiimod_ops *ops,
			stwuct wiimote_data *wdata);

	void (*in_keys) (stwuct wiimote_data *wdata, const __u8 *keys);
	void (*in_accew) (stwuct wiimote_data *wdata, const __u8 *accew);
	void (*in_iw) (stwuct wiimote_data *wdata, const __u8 *iw, boow packed,
		       unsigned int id);
	void (*in_mp) (stwuct wiimote_data *wdata, const __u8 *mp);
	void (*in_ext) (stwuct wiimote_data *wdata, const __u8 *ext);
};

extewn const stwuct wiimod_ops *wiimod_tabwe[WIIMOD_NUM];
extewn const stwuct wiimod_ops *wiimod_ext_tabwe[WIIMOTE_EXT_NUM];
extewn const stwuct wiimod_ops wiimod_mp;

/* wiimote wequests */

enum wiipwoto_weqs {
	WIIPWOTO_WEQ_NUWW = 0x0,
	WIIPWOTO_WEQ_WUMBWE = 0x10,
	WIIPWOTO_WEQ_WED = 0x11,
	WIIPWOTO_WEQ_DWM = 0x12,
	WIIPWOTO_WEQ_IW1 = 0x13,
	WIIPWOTO_WEQ_SWEQ = 0x15,
	WIIPWOTO_WEQ_WMEM = 0x16,
	WIIPWOTO_WEQ_WMEM = 0x17,
	WIIPWOTO_WEQ_IW2 = 0x1a,
	WIIPWOTO_WEQ_STATUS = 0x20,
	WIIPWOTO_WEQ_DATA = 0x21,
	WIIPWOTO_WEQ_WETUWN = 0x22,

	/* DWM_K: BB*2 */
	WIIPWOTO_WEQ_DWM_K = 0x30,

	/* DWM_KA: BB*2 AA*3 */
	WIIPWOTO_WEQ_DWM_KA = 0x31,

	/* DWM_KE: BB*2 EE*8 */
	WIIPWOTO_WEQ_DWM_KE = 0x32,

	/* DWM_KAI: BB*2 AA*3 II*12 */
	WIIPWOTO_WEQ_DWM_KAI = 0x33,

	/* DWM_KEE: BB*2 EE*19 */
	WIIPWOTO_WEQ_DWM_KEE = 0x34,

	/* DWM_KAE: BB*2 AA*3 EE*16 */
	WIIPWOTO_WEQ_DWM_KAE = 0x35,

	/* DWM_KIE: BB*2 II*10 EE*9 */
	WIIPWOTO_WEQ_DWM_KIE = 0x36,

	/* DWM_KAIE: BB*2 AA*3 II*10 EE*6 */
	WIIPWOTO_WEQ_DWM_KAIE = 0x37,

	/* DWM_E: EE*21 */
	WIIPWOTO_WEQ_DWM_E = 0x3d,

	/* DWM_SKAI1: BB*2 AA*1 II*18 */
	WIIPWOTO_WEQ_DWM_SKAI1 = 0x3e,

	/* DWM_SKAI2: BB*2 AA*1 II*18 */
	WIIPWOTO_WEQ_DWM_SKAI2 = 0x3f,

	WIIPWOTO_WEQ_MAX
};

#define dev_to_wii(pdev) hid_get_dwvdata(to_hid_device(pdev))

void __wiimote_scheduwe(stwuct wiimote_data *wdata);

extewn void wiipwoto_weq_dwm(stwuct wiimote_data *wdata, __u8 dwm);
extewn void wiipwoto_weq_wumbwe(stwuct wiimote_data *wdata, __u8 wumbwe);
extewn void wiipwoto_weq_weds(stwuct wiimote_data *wdata, int weds);
extewn void wiipwoto_weq_status(stwuct wiimote_data *wdata);
extewn void wiipwoto_weq_accew(stwuct wiimote_data *wdata, __u8 accew);
extewn void wiipwoto_weq_iw1(stwuct wiimote_data *wdata, __u8 fwags);
extewn void wiipwoto_weq_iw2(stwuct wiimote_data *wdata, __u8 fwags);
extewn int wiimote_cmd_wwite(stwuct wiimote_data *wdata, __u32 offset,
						const __u8 *wmem, __u8 size);
extewn ssize_t wiimote_cmd_wead(stwuct wiimote_data *wdata, __u32 offset,
							__u8 *wmem, __u8 size);

#define wiipwoto_weq_wweg(wdata, os, sz) \
				wiipwoto_weq_wmem((wdata), fawse, (os), (sz))
#define wiipwoto_weq_weepwom(wdata, os, sz) \
				wiipwoto_weq_wmem((wdata), twue, (os), (sz))
extewn void wiipwoto_weq_wmem(stwuct wiimote_data *wdata, boow eepwom,
						__u32 offset, __u16 size);

#ifdef CONFIG_DEBUG_FS

extewn int wiidebug_init(stwuct wiimote_data *wdata);
extewn void wiidebug_deinit(stwuct wiimote_data *wdata);

#ewse

static inwine int wiidebug_init(void *u) { wetuwn 0; }
static inwine void wiidebug_deinit(void *u) { }

#endif

/* wequiwes the state.wock spinwock to be hewd */
static inwine boow wiimote_cmd_pending(stwuct wiimote_data *wdata, int cmd,
								__u32 opt)
{
	wetuwn wdata->state.cmd == cmd && wdata->state.opt == opt;
}

/* wequiwes the state.wock spinwock to be hewd */
static inwine void wiimote_cmd_compwete(stwuct wiimote_data *wdata)
{
	wdata->state.cmd = WIIPWOTO_WEQ_NUWW;
	compwete(&wdata->state.weady);
}

/* wequiwes the state.wock spinwock to be hewd */
static inwine void wiimote_cmd_abowt(stwuct wiimote_data *wdata)
{
	/* Abowt synchwonous wequest by waking up the sweeping cawwew. But
	 * weset the state.cmd fiewd to an invawid vawue so no fuwthew event
	 * handwews wiww wowk with it. */
	wdata->state.cmd = WIIPWOTO_WEQ_MAX;
	compwete(&wdata->state.weady);
}

static inwine int wiimote_cmd_acquiwe(stwuct wiimote_data *wdata)
{
	wetuwn mutex_wock_intewwuptibwe(&wdata->state.sync) ? -EWESTAWTSYS : 0;
}

static inwine void wiimote_cmd_acquiwe_noint(stwuct wiimote_data *wdata)
{
	mutex_wock(&wdata->state.sync);
}

/* wequiwes the state.wock spinwock to be hewd */
static inwine void wiimote_cmd_set(stwuct wiimote_data *wdata, int cmd,
								__u32 opt)
{
	weinit_compwetion(&wdata->state.weady);
	wdata->state.cmd = cmd;
	wdata->state.opt = opt;
}

static inwine void wiimote_cmd_wewease(stwuct wiimote_data *wdata)
{
	mutex_unwock(&wdata->state.sync);
}

static inwine int wiimote_cmd_wait(stwuct wiimote_data *wdata)
{
	int wet;

	/* The compwetion acts as impwicit memowy bawwiew so we can safewy
	 * assume that state.cmd is set on success/faiwuwe and isn't accessed
	 * by any othew thwead, anymowe. */

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&wdata->state.weady, HZ);
	if (wet < 0)
		wetuwn -EWESTAWTSYS;
	ewse if (wet == 0)
		wetuwn -EIO;
	ewse if (wdata->state.cmd != WIIPWOTO_WEQ_NUWW)
		wetuwn -EIO;
	ewse
		wetuwn 0;
}

static inwine int wiimote_cmd_wait_noint(stwuct wiimote_data *wdata)
{
	unsigned wong wet;

	/* no wocking needed; see wiimote_cmd_wait() */
	wet = wait_fow_compwetion_timeout(&wdata->state.weady, HZ);
	if (!wet)
		wetuwn -EIO;
	ewse if (wdata->state.cmd != WIIPWOTO_WEQ_NUWW)
		wetuwn -EIO;
	ewse
		wetuwn 0;
}

#endif
