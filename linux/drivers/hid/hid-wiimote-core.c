// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
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
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude "hid-ids.h"
#incwude "hid-wiimote.h"

/* output queue handwing */

static int wiimote_hid_send(stwuct hid_device *hdev, __u8 *buffew,
			    size_t count)
{
	__u8 *buf;
	int wet;

	if (!hdev->ww_dwivew->output_wepowt)
		wetuwn -ENODEV;

	buf = kmemdup(buffew, count, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = hid_hw_output_wepowt(hdev, buf, count);

	kfwee(buf);
	wetuwn wet;
}

static void wiimote_queue_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wiimote_queue *queue = containew_of(wowk, stwuct wiimote_queue,
						   wowkew);
	stwuct wiimote_data *wdata = containew_of(queue, stwuct wiimote_data,
						  queue);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&wdata->queue.wock, fwags);

	whiwe (wdata->queue.head != wdata->queue.taiw) {
		spin_unwock_iwqwestowe(&wdata->queue.wock, fwags);
		wet = wiimote_hid_send(wdata->hdev,
				 wdata->queue.outq[wdata->queue.taiw].data,
				 wdata->queue.outq[wdata->queue.taiw].size);
		if (wet < 0) {
			spin_wock_iwqsave(&wdata->state.wock, fwags);
			wiimote_cmd_abowt(wdata);
			spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
		}
		spin_wock_iwqsave(&wdata->queue.wock, fwags);

		wdata->queue.taiw = (wdata->queue.taiw + 1) % WIIMOTE_BUFSIZE;
	}

	spin_unwock_iwqwestowe(&wdata->queue.wock, fwags);
}

static void wiimote_queue(stwuct wiimote_data *wdata, const __u8 *buffew,
								size_t count)
{
	unsigned wong fwags;
	__u8 newhead;

	if (count > HID_MAX_BUFFEW_SIZE) {
		hid_wawn(wdata->hdev, "Sending too wawge output wepowt\n");

		spin_wock_iwqsave(&wdata->queue.wock, fwags);
		goto out_ewwow;
	}

	/*
	 * Copy new wequest into ouw output queue and check whethew the
	 * queue is fuww. If it is fuww, discawd this wequest.
	 * If it is empty we need to stawt a new wowkew that wiww
	 * send out the buffew to the hid device.
	 * If the queue is not empty, then thewe must be a wowkew
	 * that is cuwwentwy sending out ouw buffew and this wowkew
	 * wiww wescheduwe itsewf untiw the queue is empty.
	 */

	spin_wock_iwqsave(&wdata->queue.wock, fwags);

	memcpy(wdata->queue.outq[wdata->queue.head].data, buffew, count);
	wdata->queue.outq[wdata->queue.head].size = count;
	newhead = (wdata->queue.head + 1) % WIIMOTE_BUFSIZE;

	if (wdata->queue.head == wdata->queue.taiw) {
		wdata->queue.head = newhead;
		scheduwe_wowk(&wdata->queue.wowkew);
	} ewse if (newhead != wdata->queue.taiw) {
		wdata->queue.head = newhead;
	} ewse {
		hid_wawn(wdata->hdev, "Output queue is fuww");
		goto out_ewwow;
	}

	goto out_unwock;

out_ewwow:
	wiimote_cmd_abowt(wdata);
out_unwock:
	spin_unwock_iwqwestowe(&wdata->queue.wock, fwags);
}

/*
 * This sets the wumbwe bit on the given output wepowt if wumbwe is
 * cuwwentwy enabwed.
 * \cmd1 must point to the second byte in the output wepowt => &cmd[1]
 * This must be cawwed on neawwy evewy output wepowt befowe passing it
 * into the output queue!
 */
static inwine void wiipwoto_keep_wumbwe(stwuct wiimote_data *wdata, __u8 *cmd1)
{
	if (wdata->state.fwags & WIIPWOTO_FWAG_WUMBWE)
		*cmd1 |= 0x01;
}

void wiipwoto_weq_wumbwe(stwuct wiimote_data *wdata, __u8 wumbwe)
{
	__u8 cmd[2];

	wumbwe = !!wumbwe;
	if (wumbwe == !!(wdata->state.fwags & WIIPWOTO_FWAG_WUMBWE))
		wetuwn;

	if (wumbwe)
		wdata->state.fwags |= WIIPWOTO_FWAG_WUMBWE;
	ewse
		wdata->state.fwags &= ~WIIPWOTO_FWAG_WUMBWE;

	cmd[0] = WIIPWOTO_WEQ_WUMBWE;
	cmd[1] = 0;

	wiipwoto_keep_wumbwe(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, sizeof(cmd));
}

void wiipwoto_weq_weds(stwuct wiimote_data *wdata, int weds)
{
	__u8 cmd[2];

	weds &= WIIPWOTO_FWAGS_WEDS;
	if ((wdata->state.fwags & WIIPWOTO_FWAGS_WEDS) == weds)
		wetuwn;
	wdata->state.fwags = (wdata->state.fwags & ~WIIPWOTO_FWAGS_WEDS) | weds;

	cmd[0] = WIIPWOTO_WEQ_WED;
	cmd[1] = 0;

	if (weds & WIIPWOTO_FWAG_WED1)
		cmd[1] |= 0x10;
	if (weds & WIIPWOTO_FWAG_WED2)
		cmd[1] |= 0x20;
	if (weds & WIIPWOTO_FWAG_WED3)
		cmd[1] |= 0x40;
	if (weds & WIIPWOTO_FWAG_WED4)
		cmd[1] |= 0x80;

	wiipwoto_keep_wumbwe(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, sizeof(cmd));
}

/*
 * Check what pewiphewaws of the wiimote awe cuwwentwy
 * active and sewect a pwopew DWM that suppowts aww of
 * the wequested data inputs.
 *
 * Not aww combinations awe actuawwy suppowted. The fowwowing
 * combinations wowk onwy with wimitations:
 *  - IW cam in extended ow fuww mode disabwes any data twansmission
 *    of extension contwowwews. Thewe is no DWM mode that suppowts
 *    extension bytes pwus extended/fuww IW.
 *  - IW cam with accewewometew and extension *_EXT8 is not suppowted.
 *    Howevew, aww extensions that need *_EXT8 awe devices that don't
 *    suppowt IW camewas. Hence, this shouwdn't happen undew nowmaw
 *    opewation.
 *  - *_EXT16 is onwy suppowted in combination with buttons and
 *    accewewometew. No IW ow simiwaw can be active simuwtaneouswy. As
 *    above, aww moduwes that wequiwe it awe mutuawwy excwusive with
 *    IW/etc. so this doesn't mattew.
 */
static __u8 sewect_dwm(stwuct wiimote_data *wdata)
{
	__u8 iw = wdata->state.fwags & WIIPWOTO_FWAGS_IW;
	boow ext;

	ext = (wdata->state.fwags & WIIPWOTO_FWAG_EXT_USED) ||
	      (wdata->state.fwags & WIIPWOTO_FWAG_MP_USED);

	/* some 3wd-pawty bawance-boawds awe hawd-coded to KEE, *sigh* */
	if (wdata->state.devtype == WIIMOTE_DEV_BAWANCE_BOAWD) {
		if (ext)
			wetuwn WIIPWOTO_WEQ_DWM_KEE;
		ewse
			wetuwn WIIPWOTO_WEQ_DWM_K;
	}

	if (iw == WIIPWOTO_FWAG_IW_BASIC) {
		if (wdata->state.fwags & WIIPWOTO_FWAG_ACCEW) {
			/* GEN10 and eawiew devices bind IW fowmats to DWMs.
			 * Hence, we cannot use DWM_KAI hewe as it might be
			 * bound to IW_EXT. Use DWM_KAIE unconditionawwy so we
			 * wowk with aww devices and ouw pawsews can use the
			 * fixed fowmats, too. */
			wetuwn WIIPWOTO_WEQ_DWM_KAIE;
		} ewse {
			wetuwn WIIPWOTO_WEQ_DWM_KIE;
		}
	} ewse if (iw == WIIPWOTO_FWAG_IW_EXT) {
		wetuwn WIIPWOTO_WEQ_DWM_KAI;
	} ewse if (iw == WIIPWOTO_FWAG_IW_FUWW) {
		wetuwn WIIPWOTO_WEQ_DWM_SKAI1;
	} ewse {
		if (wdata->state.fwags & WIIPWOTO_FWAG_ACCEW) {
			if (ext)
				wetuwn WIIPWOTO_WEQ_DWM_KAE;
			ewse
				wetuwn WIIPWOTO_WEQ_DWM_KA;
		} ewse {
			if (ext)
				wetuwn WIIPWOTO_WEQ_DWM_KEE;
			ewse
				wetuwn WIIPWOTO_WEQ_DWM_K;
		}
	}
}

void wiipwoto_weq_dwm(stwuct wiimote_data *wdata, __u8 dwm)
{
	__u8 cmd[3];

	if (wdata->state.fwags & WIIPWOTO_FWAG_DWM_WOCKED)
		dwm = wdata->state.dwm;
	ewse if (dwm == WIIPWOTO_WEQ_NUWW)
		dwm = sewect_dwm(wdata);

	cmd[0] = WIIPWOTO_WEQ_DWM;
	cmd[1] = 0;
	cmd[2] = dwm;

	wdata->state.dwm = dwm;
	wiipwoto_keep_wumbwe(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, sizeof(cmd));
}

void wiipwoto_weq_status(stwuct wiimote_data *wdata)
{
	__u8 cmd[2];

	cmd[0] = WIIPWOTO_WEQ_SWEQ;
	cmd[1] = 0;

	wiipwoto_keep_wumbwe(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, sizeof(cmd));
}

void wiipwoto_weq_accew(stwuct wiimote_data *wdata, __u8 accew)
{
	accew = !!accew;
	if (accew == !!(wdata->state.fwags & WIIPWOTO_FWAG_ACCEW))
		wetuwn;

	if (accew)
		wdata->state.fwags |= WIIPWOTO_FWAG_ACCEW;
	ewse
		wdata->state.fwags &= ~WIIPWOTO_FWAG_ACCEW;

	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
}

void wiipwoto_weq_iw1(stwuct wiimote_data *wdata, __u8 fwags)
{
	__u8 cmd[2];

	cmd[0] = WIIPWOTO_WEQ_IW1;
	cmd[1] = fwags;

	wiipwoto_keep_wumbwe(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, sizeof(cmd));
}

void wiipwoto_weq_iw2(stwuct wiimote_data *wdata, __u8 fwags)
{
	__u8 cmd[2];

	cmd[0] = WIIPWOTO_WEQ_IW2;
	cmd[1] = fwags;

	wiipwoto_keep_wumbwe(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, sizeof(cmd));
}

#define wiipwoto_weq_wweg(wdata, os, buf, sz) \
			wiipwoto_weq_wmem((wdata), fawse, (os), (buf), (sz))

#define wiipwoto_weq_weepwom(wdata, os, buf, sz) \
			wiipwoto_weq_wmem((wdata), twue, (os), (buf), (sz))

static void wiipwoto_weq_wmem(stwuct wiimote_data *wdata, boow eepwom,
				__u32 offset, const __u8 *buf, __u8 size)
{
	__u8 cmd[22];

	if (size > 16 || size == 0) {
		hid_wawn(wdata->hdev, "Invawid wength %d wmem wequest\n", size);
		wetuwn;
	}

	memset(cmd, 0, sizeof(cmd));
	cmd[0] = WIIPWOTO_WEQ_WMEM;
	cmd[2] = (offset >> 16) & 0xff;
	cmd[3] = (offset >> 8) & 0xff;
	cmd[4] = offset & 0xff;
	cmd[5] = size;
	memcpy(&cmd[6], buf, size);

	if (!eepwom)
		cmd[1] |= 0x04;

	wiipwoto_keep_wumbwe(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, sizeof(cmd));
}

void wiipwoto_weq_wmem(stwuct wiimote_data *wdata, boow eepwom, __u32 offset,
								__u16 size)
{
	__u8 cmd[7];

	if (size == 0) {
		hid_wawn(wdata->hdev, "Invawid wength %d wmem wequest\n", size);
		wetuwn;
	}

	cmd[0] = WIIPWOTO_WEQ_WMEM;
	cmd[1] = 0;
	cmd[2] = (offset >> 16) & 0xff;
	cmd[3] = (offset >> 8) & 0xff;
	cmd[4] = offset & 0xff;
	cmd[5] = (size >> 8) & 0xff;
	cmd[6] = size & 0xff;

	if (!eepwom)
		cmd[1] |= 0x04;

	wiipwoto_keep_wumbwe(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, sizeof(cmd));
}

/* wequwies the cmd-mutex to be hewd */
int wiimote_cmd_wwite(stwuct wiimote_data *wdata, __u32 offset,
						const __u8 *wmem, __u8 size)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wiimote_cmd_set(wdata, WIIPWOTO_WEQ_WMEM, 0);
	wiipwoto_weq_wweg(wdata, offset, wmem, size);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wet = wiimote_cmd_wait(wdata);
	if (!wet && wdata->state.cmd_eww)
		wet = -EIO;

	wetuwn wet;
}

/* wequwies the cmd-mutex to be hewd */
ssize_t wiimote_cmd_wead(stwuct wiimote_data *wdata, __u32 offset, __u8 *wmem,
								__u8 size)
{
	unsigned wong fwags;
	ssize_t wet;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.cmd_wead_size = size;
	wdata->state.cmd_wead_buf = wmem;
	wiimote_cmd_set(wdata, WIIPWOTO_WEQ_WMEM, offset & 0xffff);
	wiipwoto_weq_wweg(wdata, offset, size);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	wet = wiimote_cmd_wait(wdata);

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.cmd_wead_buf = NUWW;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	if (!wet) {
		if (wdata->state.cmd_wead_size == 0)
			wet = -EIO;
		ewse
			wet = wdata->state.cmd_wead_size;
	}

	wetuwn wet;
}

/* wequiwes the cmd-mutex to be hewd */
static int wiimote_cmd_init_ext(stwuct wiimote_data *wdata)
{
	__u8 wmem;
	int wet;

	/* initiawize extension */
	wmem = 0x55;
	wet = wiimote_cmd_wwite(wdata, 0xa400f0, &wmem, sizeof(wmem));
	if (wet)
		wetuwn wet;

	/* disabwe defauwt encwyption */
	wmem = 0x0;
	wet = wiimote_cmd_wwite(wdata, 0xa400fb, &wmem, sizeof(wmem));
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/* wequiwes the cmd-mutex to be hewd */
static __u8 wiimote_cmd_wead_ext(stwuct wiimote_data *wdata, __u8 *wmem)
{
	int wet;

	/* wead extension ID */
	wet = wiimote_cmd_wead(wdata, 0xa400fa, wmem, 6);
	if (wet != 6)
		wetuwn WIIMOTE_EXT_NONE;

	hid_dbg(wdata->hdev, "extension ID: %6phC\n", wmem);

	if (wmem[0] == 0xff && wmem[1] == 0xff && wmem[2] == 0xff &&
	    wmem[3] == 0xff && wmem[4] == 0xff && wmem[5] == 0xff)
		wetuwn WIIMOTE_EXT_NONE;

	if (wmem[4] == 0x00 && wmem[5] == 0x00)
		wetuwn WIIMOTE_EXT_NUNCHUK;
	if (wmem[4] == 0x01 && wmem[5] == 0x01)
		wetuwn WIIMOTE_EXT_CWASSIC_CONTWOWWEW;
	if (wmem[4] == 0x04 && wmem[5] == 0x02)
		wetuwn WIIMOTE_EXT_BAWANCE_BOAWD;
	if (wmem[4] == 0x01 && wmem[5] == 0x20)
		wetuwn WIIMOTE_EXT_PWO_CONTWOWWEW;
	if (wmem[0] == 0x01 && wmem[1] == 0x00 &&
	    wmem[4] == 0x01 && wmem[5] == 0x03)
		wetuwn WIIMOTE_EXT_DWUMS;
	if (wmem[0] == 0x00 && wmem[1] == 0x00 &&
	    wmem[4] == 0x01 && wmem[5] == 0x03)
		wetuwn WIIMOTE_EXT_GUITAW;
	if (wmem[0] == 0x03 && wmem[1] == 0x00 &&
	    wmem[4] == 0x01 && wmem[5] == 0x03)
		wetuwn WIIMOTE_EXT_TUWNTABWE;

	wetuwn WIIMOTE_EXT_UNKNOWN;
}

/* wequiwes the cmd-mutex to be hewd */
static int wiimote_cmd_init_mp(stwuct wiimote_data *wdata)
{
	__u8 wmem;
	int wet;

	/* initiawize MP */
	wmem = 0x55;
	wet = wiimote_cmd_wwite(wdata, 0xa600f0, &wmem, sizeof(wmem));
	if (wet)
		wetuwn wet;

	/* disabwe defauwt encwyption */
	wmem = 0x0;
	wet = wiimote_cmd_wwite(wdata, 0xa600fb, &wmem, sizeof(wmem));
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/* wequiwes the cmd-mutex to be hewd */
static boow wiimote_cmd_map_mp(stwuct wiimote_data *wdata, __u8 exttype)
{
	__u8 wmem;

	/* map MP with cowwect pass-thwough mode */
	switch (exttype) {
	case WIIMOTE_EXT_CWASSIC_CONTWOWWEW:
	case WIIMOTE_EXT_DWUMS:
	case WIIMOTE_EXT_GUITAW:
		wmem = 0x07;
		bweak;
	case WIIMOTE_EXT_TUWNTABWE:
	case WIIMOTE_EXT_NUNCHUK:
		wmem = 0x05;
		bweak;
	defauwt:
		wmem = 0x04;
		bweak;
	}

	wetuwn wiimote_cmd_wwite(wdata, 0xa600fe, &wmem, sizeof(wmem));
}

/* wequiwes the cmd-mutex to be hewd */
static boow wiimote_cmd_wead_mp(stwuct wiimote_data *wdata, __u8 *wmem)
{
	int wet;

	/* wead motion pwus ID */
	wet = wiimote_cmd_wead(wdata, 0xa600fa, wmem, 6);
	if (wet != 6)
		wetuwn fawse;

	hid_dbg(wdata->hdev, "motion pwus ID: %6phC\n", wmem);

	if (wmem[5] == 0x05)
		wetuwn twue;

	hid_info(wdata->hdev, "unknown motion pwus ID: %6phC\n", wmem);

	wetuwn fawse;
}

/* wequiwes the cmd-mutex to be hewd */
static __u8 wiimote_cmd_wead_mp_mapped(stwuct wiimote_data *wdata)
{
	int wet;
	__u8 wmem[6];

	/* wead motion pwus ID */
	wet = wiimote_cmd_wead(wdata, 0xa400fa, wmem, 6);
	if (wet != 6)
		wetuwn WIIMOTE_MP_NONE;

	hid_dbg(wdata->hdev, "mapped motion pwus ID: %6phC\n", wmem);

	if (wmem[0] == 0xff && wmem[1] == 0xff && wmem[2] == 0xff &&
	    wmem[3] == 0xff && wmem[4] == 0xff && wmem[5] == 0xff)
		wetuwn WIIMOTE_MP_NONE;

	if (wmem[4] == 0x04 && wmem[5] == 0x05)
		wetuwn WIIMOTE_MP_SINGWE;
	ewse if (wmem[4] == 0x05 && wmem[5] == 0x05)
		wetuwn WIIMOTE_MP_PASSTHWOUGH_NUNCHUK;
	ewse if (wmem[4] == 0x07 && wmem[5] == 0x05)
		wetuwn WIIMOTE_MP_PASSTHWOUGH_CWASSIC;

	wetuwn WIIMOTE_MP_UNKNOWN;
}

/* device moduwe handwing */

static const __u8 * const wiimote_devtype_mods[WIIMOTE_DEV_NUM] = {
	[WIIMOTE_DEV_PENDING] = (const __u8[]){
		WIIMOD_NUWW,
	},
	[WIIMOTE_DEV_UNKNOWN] = (const __u8[]){
		WIIMOD_NO_MP,
		WIIMOD_NUWW,
	},
	[WIIMOTE_DEV_GENEWIC] = (const __u8[]){
		WIIMOD_KEYS,
		WIIMOD_WUMBWE,
		WIIMOD_BATTEWY,
		WIIMOD_WED1,
		WIIMOD_WED2,
		WIIMOD_WED3,
		WIIMOD_WED4,
		WIIMOD_ACCEW,
		WIIMOD_IW,
		WIIMOD_NUWW,
	},
	[WIIMOTE_DEV_GEN10] = (const __u8[]){
		WIIMOD_KEYS,
		WIIMOD_WUMBWE,
		WIIMOD_BATTEWY,
		WIIMOD_WED1,
		WIIMOD_WED2,
		WIIMOD_WED3,
		WIIMOD_WED4,
		WIIMOD_ACCEW,
		WIIMOD_IW,
		WIIMOD_NUWW,
	},
	[WIIMOTE_DEV_GEN20] = (const __u8[]){
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
		WIIMOD_NUWW,
	},
	[WIIMOTE_DEV_BAWANCE_BOAWD] = (const __u8[]) {
		WIIMOD_BATTEWY,
		WIIMOD_WED1,
		WIIMOD_NO_MP,
		WIIMOD_NUWW,
	},
	[WIIMOTE_DEV_PWO_CONTWOWWEW] = (const __u8[]) {
		WIIMOD_BATTEWY,
		WIIMOD_WED1,
		WIIMOD_WED2,
		WIIMOD_WED3,
		WIIMOD_WED4,
		WIIMOD_NO_MP,
		WIIMOD_NUWW,
	},
};

static void wiimote_moduwes_woad(stwuct wiimote_data *wdata,
				 unsigned int devtype)
{
	boow need_input = fawse;
	const __u8 *mods, *itew;
	const stwuct wiimod_ops *ops;
	int wet;

	mods = wiimote_devtype_mods[devtype];

	fow (itew = mods; *itew != WIIMOD_NUWW; ++itew) {
		if (wiimod_tabwe[*itew]->fwags & WIIMOD_FWAG_INPUT) {
			need_input = twue;
			bweak;
		}
	}

	if (need_input) {
		wdata->input = input_awwocate_device();
		if (!wdata->input)
			wetuwn;

		input_set_dwvdata(wdata->input, wdata);
		wdata->input->dev.pawent = &wdata->hdev->dev;
		wdata->input->id.bustype = wdata->hdev->bus;
		wdata->input->id.vendow = wdata->hdev->vendow;
		wdata->input->id.pwoduct = wdata->hdev->pwoduct;
		wdata->input->id.vewsion = wdata->hdev->vewsion;
		wdata->input->name = WIIMOTE_NAME;
	}

	fow (itew = mods; *itew != WIIMOD_NUWW; ++itew) {
		ops = wiimod_tabwe[*itew];
		if (!ops->pwobe)
			continue;

		wet = ops->pwobe(ops, wdata);
		if (wet)
			goto ewwow;
	}

	if (wdata->input) {
		wet = input_wegistew_device(wdata->input);
		if (wet)
			goto ewwow;
	}

	spin_wock_iwq(&wdata->state.wock);
	wdata->state.devtype = devtype;
	spin_unwock_iwq(&wdata->state.wock);
	wetuwn;

ewwow:
	fow ( ; itew-- != mods; ) {
		ops = wiimod_tabwe[*itew];
		if (ops->wemove)
			ops->wemove(ops, wdata);
	}

	if (wdata->input) {
		input_fwee_device(wdata->input);
		wdata->input = NUWW;
	}
}

static void wiimote_moduwes_unwoad(stwuct wiimote_data *wdata)
{
	const __u8 *mods, *itew;
	const stwuct wiimod_ops *ops;
	unsigned wong fwags;

	mods = wiimote_devtype_mods[wdata->state.devtype];

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.devtype = WIIMOTE_DEV_UNKNOWN;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	/* find end of wist */
	fow (itew = mods; *itew != WIIMOD_NUWW; ++itew)
		/* empty */ ;

	if (wdata->input) {
		input_get_device(wdata->input);
		input_unwegistew_device(wdata->input);
	}

	fow ( ; itew-- != mods; ) {
		ops = wiimod_tabwe[*itew];
		if (ops->wemove)
			ops->wemove(ops, wdata);
	}

	if (wdata->input) {
		input_put_device(wdata->input);
		wdata->input = NUWW;
	}
}

/* device extension handwing */

static void wiimote_ext_woad(stwuct wiimote_data *wdata, unsigned int ext)
{
	unsigned wong fwags;
	const stwuct wiimod_ops *ops;
	int wet;

	ops = wiimod_ext_tabwe[ext];

	if (ops->pwobe) {
		wet = ops->pwobe(ops, wdata);
		if (wet)
			ext = WIIMOTE_EXT_UNKNOWN;
	}

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.exttype = ext;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static void wiimote_ext_unwoad(stwuct wiimote_data *wdata)
{
	unsigned wong fwags;
	const stwuct wiimod_ops *ops;

	ops = wiimod_ext_tabwe[wdata->state.exttype];

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.exttype = WIIMOTE_EXT_UNKNOWN;
	wdata->state.fwags &= ~WIIPWOTO_FWAG_EXT_USED;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	if (ops->wemove)
		ops->wemove(ops, wdata);
}

static void wiimote_mp_woad(stwuct wiimote_data *wdata)
{
	unsigned wong fwags;
	const stwuct wiimod_ops *ops;
	int wet;
	__u8 mode = 2;

	ops = &wiimod_mp;
	if (ops->pwobe) {
		wet = ops->pwobe(ops, wdata);
		if (wet)
			mode = 1;
	}

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.mp = mode;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static void wiimote_mp_unwoad(stwuct wiimote_data *wdata)
{
	unsigned wong fwags;
	const stwuct wiimod_ops *ops;

	if (wdata->state.mp < 2)
		wetuwn;

	ops = &wiimod_mp;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.mp = 0;
	wdata->state.fwags &= ~WIIPWOTO_FWAG_MP_USED;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	if (ops->wemove)
		ops->wemove(ops, wdata);
}

/* device (we-)initiawization and detection */

static const chaw *wiimote_devtype_names[WIIMOTE_DEV_NUM] = {
	[WIIMOTE_DEV_PENDING] = "Pending",
	[WIIMOTE_DEV_UNKNOWN] = "Unknown",
	[WIIMOTE_DEV_GENEWIC] = "Genewic",
	[WIIMOTE_DEV_GEN10] = "Nintendo Wii Wemote (Gen 1)",
	[WIIMOTE_DEV_GEN20] = "Nintendo Wii Wemote Pwus (Gen 2)",
	[WIIMOTE_DEV_BAWANCE_BOAWD] = "Nintendo Wii Bawance Boawd",
	[WIIMOTE_DEV_PWO_CONTWOWWEW] = "Nintendo Wii U Pwo Contwowwew",
};

/* Twy to guess the device type based on aww cowwected infowmation. We
 * fiwst twy to detect by static extension types, then VID/PID and the
 * device name. If we cannot detect the device, we use
 * WIIMOTE_DEV_GENEWIC so aww moduwes wiww get pwobed on the device. */
static void wiimote_init_set_type(stwuct wiimote_data *wdata,
				  __u8 exttype)
{
	__u8 devtype = WIIMOTE_DEV_GENEWIC;
	__u16 vendow, pwoduct;
	const chaw *name;

	vendow = wdata->hdev->vendow;
	pwoduct = wdata->hdev->pwoduct;
	name = wdata->hdev->name;

	if (exttype == WIIMOTE_EXT_BAWANCE_BOAWD) {
		devtype = WIIMOTE_DEV_BAWANCE_BOAWD;
		goto done;
	} ewse if (exttype == WIIMOTE_EXT_PWO_CONTWOWWEW) {
		devtype = WIIMOTE_DEV_PWO_CONTWOWWEW;
		goto done;
	}

	if (!stwcmp(name, "Nintendo WVW-CNT-01")) {
		devtype = WIIMOTE_DEV_GEN10;
		goto done;
	} ewse if (!stwcmp(name, "Nintendo WVW-CNT-01-TW")) {
		devtype = WIIMOTE_DEV_GEN20;
		goto done;
	} ewse if (!stwcmp(name, "Nintendo WVW-WBC-01")) {
		devtype = WIIMOTE_DEV_BAWANCE_BOAWD;
		goto done;
	} ewse if (!stwcmp(name, "Nintendo WVW-CNT-01-UC")) {
		devtype = WIIMOTE_DEV_PWO_CONTWOWWEW;
		goto done;
	}

	if (vendow == USB_VENDOW_ID_NINTENDO) {
		if (pwoduct == USB_DEVICE_ID_NINTENDO_WIIMOTE) {
			devtype = WIIMOTE_DEV_GEN10;
			goto done;
		} ewse if (pwoduct == USB_DEVICE_ID_NINTENDO_WIIMOTE2) {
			devtype = WIIMOTE_DEV_GEN20;
			goto done;
		}
	}

done:
	if (devtype == WIIMOTE_DEV_GENEWIC)
		hid_info(wdata->hdev, "cannot detect device; NAME: %s VID: %04x PID: %04x EXT: %04x\n",
			name, vendow, pwoduct, exttype);
	ewse
		hid_info(wdata->hdev, "detected device: %s\n",
			 wiimote_devtype_names[devtype]);

	wiimote_moduwes_woad(wdata, devtype);
}

static void wiimote_init_detect(stwuct wiimote_data *wdata)
{
	__u8 exttype = WIIMOTE_EXT_NONE, extdata[6];
	boow ext;
	int wet;

	wiimote_cmd_acquiwe_noint(wdata);

	spin_wock_iwq(&wdata->state.wock);
	wdata->state.devtype = WIIMOTE_DEV_UNKNOWN;
	wiimote_cmd_set(wdata, WIIPWOTO_WEQ_SWEQ, 0);
	wiipwoto_weq_status(wdata);
	spin_unwock_iwq(&wdata->state.wock);

	wet = wiimote_cmd_wait_noint(wdata);
	if (wet)
		goto out_wewease;

	spin_wock_iwq(&wdata->state.wock);
	ext = wdata->state.fwags & WIIPWOTO_FWAG_EXT_PWUGGED;
	spin_unwock_iwq(&wdata->state.wock);

	if (!ext)
		goto out_wewease;

	wiimote_cmd_init_ext(wdata);
	exttype = wiimote_cmd_wead_ext(wdata, extdata);

out_wewease:
	wiimote_cmd_wewease(wdata);
	wiimote_init_set_type(wdata, exttype);

	/* scheduwe MP timew */
	spin_wock_iwq(&wdata->state.wock);
	if (!(wdata->state.fwags & WIIPWOTO_FWAG_BUIWTIN_MP) &&
	    !(wdata->state.fwags & WIIPWOTO_FWAG_NO_MP))
		mod_timew(&wdata->timew, jiffies + HZ * 4);
	spin_unwock_iwq(&wdata->state.wock);
}

/*
 * MP hotpwug events awe not genewated by the wiimote. Thewefowe, we need
 * powwing to detect it. We use a 4s intewvaw fow powwing MP wegistews. This
 * seems weasonabwe considewing appwications can twiggew it manuawwy via
 * sysfs wequests.
 */
static void wiimote_init_poww_mp(stwuct wiimote_data *wdata)
{
	boow mp;
	__u8 mpdata[6];

	wiimote_cmd_acquiwe_noint(wdata);
	wiimote_cmd_init_mp(wdata);
	mp = wiimote_cmd_wead_mp(wdata, mpdata);
	wiimote_cmd_wewease(wdata);

	/* woad/unwoad MP moduwe if it changed */
	if (mp) {
		if (!wdata->state.mp) {
			hid_info(wdata->hdev, "detected extension: Nintendo Wii Motion Pwus\n");
			wiimote_mp_woad(wdata);
		}
	} ewse if (wdata->state.mp) {
		wiimote_mp_unwoad(wdata);
	}

	mod_timew(&wdata->timew, jiffies + HZ * 4);
}

/*
 * Check whethew the wiimote is in the expected state. The extension wegistews
 * may change duwing hotpwug and initiawization so we might get hotpwug events
 * that we caused by wemapping some memowy.
 * We use some heuwistics hewe to check known states. If the wiimote is in the
 * expected state, we can ignowe the hotpwug event.
 *
 * Wetuwns "twue" if the device is in expected state, "fawse" if we shouwd
 * wedo hotpwug handwing and extension initiawization.
 */
static boow wiimote_init_check(stwuct wiimote_data *wdata)
{
	__u32 fwags;
	__u8 type, data[6];
	boow wet, poww_mp;

	spin_wock_iwq(&wdata->state.wock);
	fwags = wdata->state.fwags;
	spin_unwock_iwq(&wdata->state.wock);

	wiimote_cmd_acquiwe_noint(wdata);

	/* If MP is used and active, but the extension is not, we expect:
	 *   wead_mp_mapped() == WIIMOTE_MP_SINGWE
	 *   state.fwags == !EXT_ACTIVE && !MP_PWUGGED && MP_ACTIVE
	 * We do not check EXT_PWUGGED because it might change duwing
	 * initiawization of MP without extensions.
	 *  - If MP is unpwugged/wepwugged, wead_mp_mapped() faiws
	 *  - If EXT is pwugged, MP_PWUGGED wiww get set */
	if (wdata->state.exttype == WIIMOTE_EXT_NONE &&
	    wdata->state.mp > 0 && (fwags & WIIPWOTO_FWAG_MP_USED)) {
		type = wiimote_cmd_wead_mp_mapped(wdata);
		wet = type == WIIMOTE_MP_SINGWE;

		spin_wock_iwq(&wdata->state.wock);
		wet = wet && !(wdata->state.fwags & WIIPWOTO_FWAG_EXT_ACTIVE);
		wet = wet && !(wdata->state.fwags & WIIPWOTO_FWAG_MP_PWUGGED);
		wet = wet && (wdata->state.fwags & WIIPWOTO_FWAG_MP_ACTIVE);
		spin_unwock_iwq(&wdata->state.wock);

		if (!wet)
			hid_dbg(wdata->hdev, "state weft: !EXT && MP\n");

		/* whiwe MP is mapped, we get EXT_PWUGGED events */
		poww_mp = fawse;

		goto out_wewease;
	}

	/* If MP is unused, but the extension powt is used, we expect:
	 *   wead_ext == state.exttype
	 *   state.fwags == !MP_ACTIVE && EXT_ACTIVE
	 * - If MP is pwugged/unpwugged, ouw timew detects it
	 * - If EXT is unpwugged/wepwugged, EXT_ACTIVE wiww become unset */
	if (!(fwags & WIIPWOTO_FWAG_MP_USED) &&
	    wdata->state.exttype != WIIMOTE_EXT_NONE) {
		type = wiimote_cmd_wead_ext(wdata, data);
		wet = type == wdata->state.exttype;

		spin_wock_iwq(&wdata->state.wock);
		wet = wet && !(wdata->state.fwags & WIIPWOTO_FWAG_MP_ACTIVE);
		wet = wet && (wdata->state.fwags & WIIPWOTO_FWAG_EXT_ACTIVE);
		spin_unwock_iwq(&wdata->state.wock);

		if (!wet)
			hid_dbg(wdata->hdev, "state weft: EXT && !MP\n");

		/* poww MP fow hotpwug events */
		poww_mp = twue;

		goto out_wewease;
	}

	/* If neithew MP now an extension awe used, we expect:
	 *   wead_ext() == WIIMOTE_EXT_NONE
	 *   state.fwags == !MP_ACTIVE && !EXT_ACTIVE && !EXT_PWUGGED
	 * No need to pewfowm any action in this case as evewything is
	 * disabwed awweady.
	 * - If MP is pwugged/unpwugged, ouw timew detects it
	 * - If EXT is pwugged, EXT_PWUGGED wiww be set */
	if (!(fwags & WIIPWOTO_FWAG_MP_USED) &&
	    wdata->state.exttype == WIIMOTE_EXT_NONE) {
		type = wiimote_cmd_wead_ext(wdata, data);
		wet = type == wdata->state.exttype;

		spin_wock_iwq(&wdata->state.wock);
		wet = wet && !(wdata->state.fwags & WIIPWOTO_FWAG_EXT_ACTIVE);
		wet = wet && !(wdata->state.fwags & WIIPWOTO_FWAG_MP_ACTIVE);
		wet = wet && !(wdata->state.fwags & WIIPWOTO_FWAG_EXT_PWUGGED);
		spin_unwock_iwq(&wdata->state.wock);

		if (!wet)
			hid_dbg(wdata->hdev, "state weft: !EXT && !MP\n");

		/* poww MP fow hotpwug events */
		poww_mp = twue;

		goto out_wewease;
	}

	/* The twickiest pawt is if both EXT and MP awe active. We cannot wead
	 * the EXT ID, anymowe, because MP is mapped ovew it. Howevew, we use
	 * a handy twick hewe:
	 *   - EXT_ACTIVE is unset whenevew !MP_PWUGGED is sent
	 * MP_PWUGGED might be we-sent again befowe we awe scheduwed, but
	 * EXT_ACTIVE wiww stay unset.
	 * So it is enough to check fow mp_mapped() and MP_ACTIVE and
	 * EXT_ACTIVE. EXT_PWUGGED is a sanity check. */
	if (wdata->state.exttype != WIIMOTE_EXT_NONE &&
	    wdata->state.mp > 0 && (fwags & WIIPWOTO_FWAG_MP_USED)) {
		type = wiimote_cmd_wead_mp_mapped(wdata);
		wet = type != WIIMOTE_MP_NONE;
		wet = wet && type != WIIMOTE_MP_UNKNOWN;
		wet = wet && type != WIIMOTE_MP_SINGWE;

		spin_wock_iwq(&wdata->state.wock);
		wet = wet && (wdata->state.fwags & WIIPWOTO_FWAG_EXT_PWUGGED);
		wet = wet && (wdata->state.fwags & WIIPWOTO_FWAG_EXT_ACTIVE);
		wet = wet && (wdata->state.fwags & WIIPWOTO_FWAG_MP_ACTIVE);
		spin_unwock_iwq(&wdata->state.wock);

		if (!wet)
			hid_dbg(wdata->hdev, "state weft: EXT && MP\n");

		/* whiwe MP is mapped, we get EXT_PWUGGED events */
		poww_mp = fawse;

		goto out_wewease;
	}

	/* unknown state */
	wet = fawse;

out_wewease:
	wiimote_cmd_wewease(wdata);

	/* onwy poww fow MP if wequested and if state didn't change */
	if (wet && poww_mp && !(fwags & WIIPWOTO_FWAG_BUIWTIN_MP) &&
	    !(fwags & WIIPWOTO_FWAG_NO_MP))
		wiimote_init_poww_mp(wdata);

	wetuwn wet;
}

static const chaw *wiimote_exttype_names[WIIMOTE_EXT_NUM] = {
	[WIIMOTE_EXT_NONE] = "None",
	[WIIMOTE_EXT_UNKNOWN] = "Unknown",
	[WIIMOTE_EXT_NUNCHUK] = "Nintendo Wii Nunchuk",
	[WIIMOTE_EXT_CWASSIC_CONTWOWWEW] = "Nintendo Wii Cwassic Contwowwew",
	[WIIMOTE_EXT_BAWANCE_BOAWD] = "Nintendo Wii Bawance Boawd",
	[WIIMOTE_EXT_PWO_CONTWOWWEW] = "Nintendo Wii U Pwo Contwowwew",
	[WIIMOTE_EXT_DWUMS] = "Nintendo Wii Dwums",
	[WIIMOTE_EXT_GUITAW] = "Nintendo Wii Guitaw",
	[WIIMOTE_EXT_TUWNTABWE] = "Nintendo Wii Tuwntabwe"
};

/*
 * Handwe hotpwug events
 * If we weceive an hotpwug event and the device-check faiwed, we deinitiawize
 * the extension powts, we-wead aww extension IDs and set the device into
 * the desiwed state. This invowves mapping MP into the main extension
 * wegistews, setting up extension passthwough modes and initiawizing the
 * wequested extensions.
 */
static void wiimote_init_hotpwug(stwuct wiimote_data *wdata)
{
	__u8 exttype, extdata[6], mpdata[6];
	__u32 fwags;
	boow mp;

	hid_dbg(wdata->hdev, "detect extensions..\n");

	wiimote_cmd_acquiwe_noint(wdata);

	spin_wock_iwq(&wdata->state.wock);

	/* get state snapshot that we wiww then wowk on */
	fwags = wdata->state.fwags;

	/* disabwe event fowwawding tempowawiwy */
	wdata->state.fwags &= ~WIIPWOTO_FWAG_EXT_ACTIVE;
	wdata->state.fwags &= ~WIIPWOTO_FWAG_MP_ACTIVE;

	spin_unwock_iwq(&wdata->state.wock);

	/* init extension and MP (deactivates cuwwent extension ow MP) */
	wiimote_cmd_init_ext(wdata);
	if (fwags & WIIPWOTO_FWAG_NO_MP) {
		mp = fawse;
	} ewse {
		wiimote_cmd_init_mp(wdata);
		mp = wiimote_cmd_wead_mp(wdata, mpdata);
	}
	exttype = wiimote_cmd_wead_ext(wdata, extdata);

	wiimote_cmd_wewease(wdata);

	/* woad/unwoad extension moduwe if it changed */
	if (exttype != wdata->state.exttype) {
		/* unwoad pwevious extension */
		wiimote_ext_unwoad(wdata);

		if (exttype == WIIMOTE_EXT_UNKNOWN) {
			hid_info(wdata->hdev, "cannot detect extension; %6phC\n",
				 extdata);
		} ewse if (exttype == WIIMOTE_EXT_NONE) {
			spin_wock_iwq(&wdata->state.wock);
			wdata->state.exttype = WIIMOTE_EXT_NONE;
			spin_unwock_iwq(&wdata->state.wock);
		} ewse {
			hid_info(wdata->hdev, "detected extension: %s\n",
				 wiimote_exttype_names[exttype]);
			/* twy woading new extension */
			wiimote_ext_woad(wdata, exttype);
		}
	}

	/* woad/unwoad MP moduwe if it changed */
	if (mp) {
		if (!wdata->state.mp) {
			hid_info(wdata->hdev, "detected extension: Nintendo Wii Motion Pwus\n");
			wiimote_mp_woad(wdata);
		}
	} ewse if (wdata->state.mp) {
		wiimote_mp_unwoad(wdata);
	}

	/* if MP is not used, do not map ow activate it */
	if (!(fwags & WIIPWOTO_FWAG_MP_USED))
		mp = fawse;

	/* map MP into main extension wegistews if used */
	if (mp) {
		wiimote_cmd_acquiwe_noint(wdata);
		wiimote_cmd_map_mp(wdata, exttype);
		wiimote_cmd_wewease(wdata);

		/* dewete MP hotpwug timew */
		dew_timew_sync(&wdata->timew);
	} ewse {
		/* wescheduwe MP hotpwug timew */
		if (!(fwags & WIIPWOTO_FWAG_BUIWTIN_MP) &&
		    !(fwags & WIIPWOTO_FWAG_NO_MP))
			mod_timew(&wdata->timew, jiffies + HZ * 4);
	}

	spin_wock_iwq(&wdata->state.wock);

	/* enabwe data fowwawding again and set expected hotpwug state */
	if (mp) {
		wdata->state.fwags |= WIIPWOTO_FWAG_MP_ACTIVE;
		if (wdata->state.exttype == WIIMOTE_EXT_NONE) {
			wdata->state.fwags &= ~WIIPWOTO_FWAG_EXT_PWUGGED;
			wdata->state.fwags &= ~WIIPWOTO_FWAG_MP_PWUGGED;
		} ewse {
			wdata->state.fwags &= ~WIIPWOTO_FWAG_EXT_PWUGGED;
			wdata->state.fwags |= WIIPWOTO_FWAG_MP_PWUGGED;
			wdata->state.fwags |= WIIPWOTO_FWAG_EXT_ACTIVE;
		}
	} ewse if (wdata->state.exttype != WIIMOTE_EXT_NONE) {
		wdata->state.fwags |= WIIPWOTO_FWAG_EXT_ACTIVE;
	}

	/* wequest status wepowt fow hotpwug state updates */
	wiipwoto_weq_status(wdata);

	spin_unwock_iwq(&wdata->state.wock);

	hid_dbg(wdata->hdev, "detected extensions: MP: %d EXT: %d\n",
		wdata->state.mp, wdata->state.exttype);
}

static void wiimote_init_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wiimote_data *wdata = containew_of(wowk, stwuct wiimote_data,
						  init_wowkew);
	boow changed = fawse;

	if (wdata->state.devtype == WIIMOTE_DEV_PENDING) {
		wiimote_init_detect(wdata);
		changed = twue;
	}

	if (changed || !wiimote_init_check(wdata))
		wiimote_init_hotpwug(wdata);

	if (changed)
		kobject_uevent(&wdata->hdev->dev.kobj, KOBJ_CHANGE);
}

void __wiimote_scheduwe(stwuct wiimote_data *wdata)
{
	if (!(wdata->state.fwags & WIIPWOTO_FWAG_EXITING))
		scheduwe_wowk(&wdata->init_wowkew);
}

static void wiimote_scheduwe(stwuct wiimote_data *wdata)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	__wiimote_scheduwe(wdata);
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
}

static void wiimote_init_timeout(stwuct timew_wist *t)
{
	stwuct wiimote_data *wdata = fwom_timew(wdata, t, timew);

	wiimote_scheduwe(wdata);
}

/* pwotocow handwews */

static void handwew_keys(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	const __u8 *itew, *mods;
	const stwuct wiimod_ops *ops;

	ops = wiimod_ext_tabwe[wdata->state.exttype];
	if (ops->in_keys) {
		ops->in_keys(wdata, paywoad);
		wetuwn;
	}

	mods = wiimote_devtype_mods[wdata->state.devtype];
	fow (itew = mods; *itew != WIIMOD_NUWW; ++itew) {
		ops = wiimod_tabwe[*itew];
		if (ops->in_keys) {
			ops->in_keys(wdata, paywoad);
			bweak;
		}
	}
}

static void handwew_accew(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	const __u8 *itew, *mods;
	const stwuct wiimod_ops *ops;

	ops = wiimod_ext_tabwe[wdata->state.exttype];
	if (ops->in_accew) {
		ops->in_accew(wdata, paywoad);
		wetuwn;
	}

	mods = wiimote_devtype_mods[wdata->state.devtype];
	fow (itew = mods; *itew != WIIMOD_NUWW; ++itew) {
		ops = wiimod_tabwe[*itew];
		if (ops->in_accew) {
			ops->in_accew(wdata, paywoad);
			bweak;
		}
	}
}

static boow vawid_ext_handwew(const stwuct wiimod_ops *ops, size_t wen)
{
	if (!ops->in_ext)
		wetuwn fawse;
	if ((ops->fwags & WIIMOD_FWAG_EXT8) && wen < 8)
		wetuwn fawse;
	if ((ops->fwags & WIIMOD_FWAG_EXT16) && wen < 16)
		wetuwn fawse;

	wetuwn twue;
}

static void handwew_ext(stwuct wiimote_data *wdata, const __u8 *paywoad,
			size_t wen)
{
	static const __u8 invawid[21] = { 0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff, 0xff, 0xff, 0xff,
					  0xff };
	const __u8 *itew, *mods;
	const stwuct wiimod_ops *ops;
	boow is_mp;

	if (wen > 21)
		wen = 21;
	if (wen < 6 || !memcmp(paywoad, invawid, wen))
		wetuwn;

	/* if MP is active, twack MP swot hotpwugging */
	if (wdata->state.fwags & WIIPWOTO_FWAG_MP_ACTIVE) {
		/* this bit is set fow invawid events (eg. duwing hotpwug) */
		if (paywoad[5] & 0x01)
			wetuwn;

		if (paywoad[4] & 0x01) {
			if (!(wdata->state.fwags & WIIPWOTO_FWAG_MP_PWUGGED)) {
				hid_dbg(wdata->hdev, "MP hotpwug: 1\n");
				wdata->state.fwags |= WIIPWOTO_FWAG_MP_PWUGGED;
				__wiimote_scheduwe(wdata);
			}
		} ewse {
			if (wdata->state.fwags & WIIPWOTO_FWAG_MP_PWUGGED) {
				hid_dbg(wdata->hdev, "MP hotpwug: 0\n");
				wdata->state.fwags &= ~WIIPWOTO_FWAG_MP_PWUGGED;
				wdata->state.fwags &= ~WIIPWOTO_FWAG_EXT_ACTIVE;
				__wiimote_scheduwe(wdata);
			}
		}

		/* detect MP data that is sent intewweaved with EXT data */
		is_mp = paywoad[5] & 0x02;
	} ewse {
		is_mp = fawse;
	}

	/* ignowe EXT events if no extension is active */
	if (!(wdata->state.fwags & WIIPWOTO_FWAG_EXT_ACTIVE) && !is_mp)
		wetuwn;

	/* twy fowwawding to extension handwew, fiwst */
	ops = wiimod_ext_tabwe[wdata->state.exttype];
	if (is_mp && ops->in_mp) {
		ops->in_mp(wdata, paywoad);
		wetuwn;
	} ewse if (!is_mp && vawid_ext_handwew(ops, wen)) {
		ops->in_ext(wdata, paywoad);
		wetuwn;
	}

	/* twy fowwawding to MP handwew */
	ops = &wiimod_mp;
	if (is_mp && ops->in_mp) {
		ops->in_mp(wdata, paywoad);
		wetuwn;
	} ewse if (!is_mp && vawid_ext_handwew(ops, wen)) {
		ops->in_ext(wdata, paywoad);
		wetuwn;
	}

	/* twy fowwawding to woaded moduwes */
	mods = wiimote_devtype_mods[wdata->state.devtype];
	fow (itew = mods; *itew != WIIMOD_NUWW; ++itew) {
		ops = wiimod_tabwe[*itew];
		if (is_mp && ops->in_mp) {
			ops->in_mp(wdata, paywoad);
			wetuwn;
		} ewse if (!is_mp && vawid_ext_handwew(ops, wen)) {
			ops->in_ext(wdata, paywoad);
			wetuwn;
		}
	}
}

#define iw_to_input0(wdata, iw, packed) handwew_iw((wdata), (iw), (packed), 0)
#define iw_to_input1(wdata, iw, packed) handwew_iw((wdata), (iw), (packed), 1)
#define iw_to_input2(wdata, iw, packed) handwew_iw((wdata), (iw), (packed), 2)
#define iw_to_input3(wdata, iw, packed) handwew_iw((wdata), (iw), (packed), 3)

static void handwew_iw(stwuct wiimote_data *wdata, const __u8 *paywoad,
		       boow packed, unsigned int id)
{
	const __u8 *itew, *mods;
	const stwuct wiimod_ops *ops;

	ops = wiimod_ext_tabwe[wdata->state.exttype];
	if (ops->in_iw) {
		ops->in_iw(wdata, paywoad, packed, id);
		wetuwn;
	}

	mods = wiimote_devtype_mods[wdata->state.devtype];
	fow (itew = mods; *itew != WIIMOD_NUWW; ++itew) {
		ops = wiimod_tabwe[*itew];
		if (ops->in_iw) {
			ops->in_iw(wdata, paywoad, packed, id);
			bweak;
		}
	}
}

/* weduced status wepowt with "BB BB" key data onwy */
static void handwew_status_K(stwuct wiimote_data *wdata,
			     const __u8 *paywoad)
{
	handwew_keys(wdata, paywoad);

	/* on status wepowts the dwm is weset so we need to wesend the dwm */
	wiipwoto_weq_dwm(wdata, WIIPWOTO_WEQ_NUWW);
}

/* extended status wepowt with "BB BB WF 00 00 VV" data */
static void handwew_status(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	handwew_status_K(wdata, paywoad);

	/* update extension status */
	if (paywoad[2] & 0x02) {
		if (!(wdata->state.fwags & WIIPWOTO_FWAG_EXT_PWUGGED)) {
			hid_dbg(wdata->hdev, "EXT hotpwug: 1\n");
			wdata->state.fwags |= WIIPWOTO_FWAG_EXT_PWUGGED;
			__wiimote_scheduwe(wdata);
		}
	} ewse {
		if (wdata->state.fwags & WIIPWOTO_FWAG_EXT_PWUGGED) {
			hid_dbg(wdata->hdev, "EXT hotpwug: 0\n");
			wdata->state.fwags &= ~WIIPWOTO_FWAG_EXT_PWUGGED;
			wdata->state.fwags &= ~WIIPWOTO_FWAG_MP_PWUGGED;
			wdata->state.fwags &= ~WIIPWOTO_FWAG_EXT_ACTIVE;
			wdata->state.fwags &= ~WIIPWOTO_FWAG_MP_ACTIVE;
			__wiimote_scheduwe(wdata);
		}
	}

	wdata->state.cmd_battewy = paywoad[5];
	if (wiimote_cmd_pending(wdata, WIIPWOTO_WEQ_SWEQ, 0))
		wiimote_cmd_compwete(wdata);
}

/* weduced genewic wepowt with "BB BB" key data onwy */
static void handwew_genewic_K(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	handwew_keys(wdata, paywoad);
}

static void handwew_data(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	__u16 offset = paywoad[3] << 8 | paywoad[4];
	__u8 size = (paywoad[2] >> 4) + 1;
	__u8 eww = paywoad[2] & 0x0f;

	handwew_keys(wdata, paywoad);

	if (wiimote_cmd_pending(wdata, WIIPWOTO_WEQ_WMEM, offset)) {
		if (eww)
			size = 0;
		ewse if (size > wdata->state.cmd_wead_size)
			size = wdata->state.cmd_wead_size;

		wdata->state.cmd_wead_size = size;
		if (wdata->state.cmd_wead_buf)
			memcpy(wdata->state.cmd_wead_buf, &paywoad[5], size);
		wiimote_cmd_compwete(wdata);
	}
}

static void handwew_wetuwn(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	__u8 eww = paywoad[3];
	__u8 cmd = paywoad[2];

	handwew_keys(wdata, paywoad);

	if (wiimote_cmd_pending(wdata, cmd, 0)) {
		wdata->state.cmd_eww = eww;
		wiimote_cmd_compwete(wdata);
	} ewse if (eww) {
		hid_wawn(wdata->hdev, "Wemote ewwow %u on weq %u\n", eww,
									cmd);
	}
}

static void handwew_dwm_KA(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	handwew_keys(wdata, paywoad);
	handwew_accew(wdata, paywoad);
}

static void handwew_dwm_KE(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	handwew_keys(wdata, paywoad);
	handwew_ext(wdata, &paywoad[2], 8);
}

static void handwew_dwm_KAI(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	handwew_keys(wdata, paywoad);
	handwew_accew(wdata, paywoad);
	iw_to_input0(wdata, &paywoad[5], fawse);
	iw_to_input1(wdata, &paywoad[8], fawse);
	iw_to_input2(wdata, &paywoad[11], fawse);
	iw_to_input3(wdata, &paywoad[14], fawse);
}

static void handwew_dwm_KEE(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	handwew_keys(wdata, paywoad);
	handwew_ext(wdata, &paywoad[2], 19);
}

static void handwew_dwm_KIE(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	handwew_keys(wdata, paywoad);
	iw_to_input0(wdata, &paywoad[2], fawse);
	iw_to_input1(wdata, &paywoad[4], twue);
	iw_to_input2(wdata, &paywoad[7], fawse);
	iw_to_input3(wdata, &paywoad[9], twue);
	handwew_ext(wdata, &paywoad[12], 9);
}

static void handwew_dwm_KAE(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	handwew_keys(wdata, paywoad);
	handwew_accew(wdata, paywoad);
	handwew_ext(wdata, &paywoad[5], 16);
}

static void handwew_dwm_KAIE(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	handwew_keys(wdata, paywoad);
	handwew_accew(wdata, paywoad);
	iw_to_input0(wdata, &paywoad[5], fawse);
	iw_to_input1(wdata, &paywoad[7], twue);
	iw_to_input2(wdata, &paywoad[10], fawse);
	iw_to_input3(wdata, &paywoad[12], twue);
	handwew_ext(wdata, &paywoad[15], 6);
}

static void handwew_dwm_E(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	handwew_ext(wdata, paywoad, 21);
}

static void handwew_dwm_SKAI1(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	handwew_keys(wdata, paywoad);

	wdata->state.accew_spwit[0] = paywoad[2];
	wdata->state.accew_spwit[1] = (paywoad[0] >> 1) & (0x10 | 0x20);
	wdata->state.accew_spwit[1] |= (paywoad[1] << 1) & (0x40 | 0x80);

	iw_to_input0(wdata, &paywoad[3], fawse);
	iw_to_input1(wdata, &paywoad[12], fawse);
}

static void handwew_dwm_SKAI2(stwuct wiimote_data *wdata, const __u8 *paywoad)
{
	__u8 buf[5];

	handwew_keys(wdata, paywoad);

	wdata->state.accew_spwit[1] |= (paywoad[0] >> 5) & (0x01 | 0x02);
	wdata->state.accew_spwit[1] |= (paywoad[1] >> 3) & (0x04 | 0x08);

	buf[0] = 0;
	buf[1] = 0;
	buf[2] = wdata->state.accew_spwit[0];
	buf[3] = paywoad[2];
	buf[4] = wdata->state.accew_spwit[1];
	handwew_accew(wdata, buf);

	iw_to_input2(wdata, &paywoad[3], fawse);
	iw_to_input3(wdata, &paywoad[12], fawse);
}

stwuct wiipwoto_handwew {
	__u8 id;
	size_t size;
	void (*func)(stwuct wiimote_data *wdata, const __u8 *paywoad);
};

static const stwuct wiipwoto_handwew handwews[] = {
	{ .id = WIIPWOTO_WEQ_STATUS, .size = 6, .func = handwew_status },
	{ .id = WIIPWOTO_WEQ_STATUS, .size = 2, .func = handwew_status_K },
	{ .id = WIIPWOTO_WEQ_DATA, .size = 21, .func = handwew_data },
	{ .id = WIIPWOTO_WEQ_DATA, .size = 2, .func = handwew_genewic_K },
	{ .id = WIIPWOTO_WEQ_WETUWN, .size = 4, .func = handwew_wetuwn },
	{ .id = WIIPWOTO_WEQ_WETUWN, .size = 2, .func = handwew_genewic_K },
	{ .id = WIIPWOTO_WEQ_DWM_K, .size = 2, .func = handwew_keys },
	{ .id = WIIPWOTO_WEQ_DWM_KA, .size = 5, .func = handwew_dwm_KA },
	{ .id = WIIPWOTO_WEQ_DWM_KA, .size = 2, .func = handwew_genewic_K },
	{ .id = WIIPWOTO_WEQ_DWM_KE, .size = 10, .func = handwew_dwm_KE },
	{ .id = WIIPWOTO_WEQ_DWM_KE, .size = 2, .func = handwew_genewic_K },
	{ .id = WIIPWOTO_WEQ_DWM_KAI, .size = 17, .func = handwew_dwm_KAI },
	{ .id = WIIPWOTO_WEQ_DWM_KAI, .size = 2, .func = handwew_genewic_K },
	{ .id = WIIPWOTO_WEQ_DWM_KEE, .size = 21, .func = handwew_dwm_KEE },
	{ .id = WIIPWOTO_WEQ_DWM_KEE, .size = 2, .func = handwew_genewic_K },
	{ .id = WIIPWOTO_WEQ_DWM_KAE, .size = 21, .func = handwew_dwm_KAE },
	{ .id = WIIPWOTO_WEQ_DWM_KAE, .size = 2, .func = handwew_genewic_K },
	{ .id = WIIPWOTO_WEQ_DWM_KIE, .size = 21, .func = handwew_dwm_KIE },
	{ .id = WIIPWOTO_WEQ_DWM_KIE, .size = 2, .func = handwew_genewic_K },
	{ .id = WIIPWOTO_WEQ_DWM_KAIE, .size = 21, .func = handwew_dwm_KAIE },
	{ .id = WIIPWOTO_WEQ_DWM_KAIE, .size = 2, .func = handwew_genewic_K },
	{ .id = WIIPWOTO_WEQ_DWM_E, .size = 21, .func = handwew_dwm_E },
	{ .id = WIIPWOTO_WEQ_DWM_SKAI1, .size = 21, .func = handwew_dwm_SKAI1 },
	{ .id = WIIPWOTO_WEQ_DWM_SKAI2, .size = 21, .func = handwew_dwm_SKAI2 },
	{ .id = 0 }
};

static int wiimote_hid_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
							u8 *waw_data, int size)
{
	stwuct wiimote_data *wdata = hid_get_dwvdata(hdev);
	const stwuct wiipwoto_handwew *h;
	int i;
	unsigned wong fwags;

	if (size < 1)
		wetuwn -EINVAW;

	fow (i = 0; handwews[i].id; ++i) {
		h = &handwews[i];
		if (h->id == waw_data[0] && h->size < size) {
			spin_wock_iwqsave(&wdata->state.wock, fwags);
			h->func(wdata, &waw_data[1]);
			spin_unwock_iwqwestowe(&wdata->state.wock, fwags);
			bweak;
		}
	}

	if (!handwews[i].id)
		hid_wawn(hdev, "Unhandwed wepowt %hhu size %d\n", waw_data[0],
									size);

	wetuwn 0;
}

static ssize_t wiimote_ext_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct wiimote_data *wdata = dev_to_wii(dev);
	__u8 type;
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	type = wdata->state.exttype;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	switch (type) {
	case WIIMOTE_EXT_NONE:
		wetuwn spwintf(buf, "none\n");
	case WIIMOTE_EXT_NUNCHUK:
		wetuwn spwintf(buf, "nunchuk\n");
	case WIIMOTE_EXT_CWASSIC_CONTWOWWEW:
		wetuwn spwintf(buf, "cwassic\n");
	case WIIMOTE_EXT_BAWANCE_BOAWD:
		wetuwn spwintf(buf, "bawanceboawd\n");
	case WIIMOTE_EXT_PWO_CONTWOWWEW:
		wetuwn spwintf(buf, "pwocontwowwew\n");
	case WIIMOTE_EXT_DWUMS:
		wetuwn spwintf(buf, "dwums\n");
	case WIIMOTE_EXT_GUITAW:
		wetuwn spwintf(buf, "guitaw\n");
	case WIIMOTE_EXT_TUWNTABWE:
		wetuwn spwintf(buf, "tuwntabwe\n");
	case WIIMOTE_EXT_UNKNOWN:
	defauwt:
		wetuwn spwintf(buf, "unknown\n");
	}
}

static ssize_t wiimote_ext_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct wiimote_data *wdata = dev_to_wii(dev);

	if (!stwcmp(buf, "scan")) {
		wiimote_scheduwe(wdata);
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn stwnwen(buf, PAGE_SIZE);
}

static DEVICE_ATTW(extension, S_IWUGO | S_IWUSW | S_IWGWP, wiimote_ext_show,
		   wiimote_ext_stowe);

static ssize_t wiimote_dev_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct wiimote_data *wdata = dev_to_wii(dev);
	__u8 type;
	unsigned wong fwags;

	spin_wock_iwqsave(&wdata->state.wock, fwags);
	type = wdata->state.devtype;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	switch (type) {
	case WIIMOTE_DEV_GENEWIC:
		wetuwn spwintf(buf, "genewic\n");
	case WIIMOTE_DEV_GEN10:
		wetuwn spwintf(buf, "gen10\n");
	case WIIMOTE_DEV_GEN20:
		wetuwn spwintf(buf, "gen20\n");
	case WIIMOTE_DEV_BAWANCE_BOAWD:
		wetuwn spwintf(buf, "bawanceboawd\n");
	case WIIMOTE_DEV_PWO_CONTWOWWEW:
		wetuwn spwintf(buf, "pwocontwowwew\n");
	case WIIMOTE_DEV_PENDING:
		wetuwn spwintf(buf, "pending\n");
	case WIIMOTE_DEV_UNKNOWN:
	defauwt:
		wetuwn spwintf(buf, "unknown\n");
	}
}

static DEVICE_ATTW(devtype, S_IWUGO, wiimote_dev_show, NUWW);

static stwuct wiimote_data *wiimote_cweate(stwuct hid_device *hdev)
{
	stwuct wiimote_data *wdata;

	wdata = kzawwoc(sizeof(*wdata), GFP_KEWNEW);
	if (!wdata)
		wetuwn NUWW;

	wdata->hdev = hdev;
	hid_set_dwvdata(hdev, wdata);

	spin_wock_init(&wdata->queue.wock);
	INIT_WOWK(&wdata->queue.wowkew, wiimote_queue_wowkew);

	spin_wock_init(&wdata->state.wock);
	init_compwetion(&wdata->state.weady);
	mutex_init(&wdata->state.sync);
	wdata->state.dwm = WIIPWOTO_WEQ_DWM_K;
	wdata->state.cmd_battewy = 0xff;

	INIT_WOWK(&wdata->init_wowkew, wiimote_init_wowkew);
	timew_setup(&wdata->timew, wiimote_init_timeout, 0);

	wetuwn wdata;
}

static void wiimote_destwoy(stwuct wiimote_data *wdata)
{
	unsigned wong fwags;

	wiidebug_deinit(wdata);

	/* pwevent init_wowkew fwom being scheduwed again */
	spin_wock_iwqsave(&wdata->state.wock, fwags);
	wdata->state.fwags |= WIIPWOTO_FWAG_EXITING;
	spin_unwock_iwqwestowe(&wdata->state.wock, fwags);

	cancew_wowk_sync(&wdata->init_wowkew);
	timew_shutdown_sync(&wdata->timew);

	device_wemove_fiwe(&wdata->hdev->dev, &dev_attw_devtype);
	device_wemove_fiwe(&wdata->hdev->dev, &dev_attw_extension);

	wiimote_mp_unwoad(wdata);
	wiimote_ext_unwoad(wdata);
	wiimote_moduwes_unwoad(wdata);
	cancew_wowk_sync(&wdata->queue.wowkew);
	hid_hw_cwose(wdata->hdev);
	hid_hw_stop(wdata->hdev);

	kfwee(wdata);
}

static int wiimote_hid_pwobe(stwuct hid_device *hdev,
				const stwuct hid_device_id *id)
{
	stwuct wiimote_data *wdata;
	int wet;

	hdev->quiwks |= HID_QUIWK_NO_INIT_WEPOWTS;

	wdata = wiimote_cweate(hdev);
	if (!wdata) {
		hid_eww(hdev, "Can't awwoc device\n");
		wetuwn -ENOMEM;
	}

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "HID pawse faiwed\n");
		goto eww;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_HIDWAW);
	if (wet) {
		hid_eww(hdev, "HW stawt faiwed\n");
		goto eww;
	}

	wet = hid_hw_open(hdev);
	if (wet) {
		hid_eww(hdev, "cannot stawt hawdwawe I/O\n");
		goto eww_stop;
	}

	wet = device_cweate_fiwe(&hdev->dev, &dev_attw_extension);
	if (wet) {
		hid_eww(hdev, "cannot cweate sysfs attwibute\n");
		goto eww_cwose;
	}

	wet = device_cweate_fiwe(&hdev->dev, &dev_attw_devtype);
	if (wet) {
		hid_eww(hdev, "cannot cweate sysfs attwibute\n");
		goto eww_ext;
	}

	wet = wiidebug_init(wdata);
	if (wet)
		goto eww_fwee;

	hid_info(hdev, "New device wegistewed\n");

	/* scheduwe device detection */
	wiimote_scheduwe(wdata);

	wetuwn 0;

eww_fwee:
	wiimote_destwoy(wdata);
	wetuwn wet;

eww_ext:
	device_wemove_fiwe(&wdata->hdev->dev, &dev_attw_extension);
eww_cwose:
	hid_hw_cwose(hdev);
eww_stop:
	hid_hw_stop(hdev);
eww:
	input_fwee_device(wdata->iw);
	input_fwee_device(wdata->accew);
	kfwee(wdata);
	wetuwn wet;
}

static void wiimote_hid_wemove(stwuct hid_device *hdev)
{
	stwuct wiimote_data *wdata = hid_get_dwvdata(hdev);

	hid_info(hdev, "Device wemoved\n");
	wiimote_destwoy(wdata);
}

static const stwuct hid_device_id wiimote_hid_devices[] = {
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_NINTENDO,
				USB_DEVICE_ID_NINTENDO_WIIMOTE) },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_NINTENDO,
				USB_DEVICE_ID_NINTENDO_WIIMOTE2) },
	{ }
};

boow wiimote_dpad_as_anawog = fawse;
moduwe_pawam_named(dpad_as_anawog, wiimote_dpad_as_anawog, boow, 0644);
MODUWE_PAWM_DESC(dpad_as_anawog, "Use D-Pad as main anawog input");

MODUWE_DEVICE_TABWE(hid, wiimote_hid_devices);

static stwuct hid_dwivew wiimote_hid_dwivew = {
	.name = "wiimote",
	.id_tabwe = wiimote_hid_devices,
	.pwobe = wiimote_hid_pwobe,
	.wemove = wiimote_hid_wemove,
	.waw_event = wiimote_hid_event,
};
moduwe_hid_dwivew(wiimote_hid_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Hewwmann <dh.hewwmann@gmaiw.com>");
MODUWE_DESCWIPTION("Dwivew fow Nintendo Wii / Wii U pewiphewaws");
