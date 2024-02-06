// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2016 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude <winux/objtoow.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/cc_pwatfowm.h>

#incwude <asm/hypewvisow.h>
#incwude <dwm/dwm_ioctw.h>

#incwude "vmwgfx_dwv.h"
#incwude "vmwgfx_msg_x86.h"
#incwude "vmwgfx_msg_awm64.h"
#incwude "vmwgfx_mksstat.h"

#define MESSAGE_STATUS_SUCCESS  0x0001
#define MESSAGE_STATUS_DOWECV   0x0002
#define MESSAGE_STATUS_CPT      0x0010
#define MESSAGE_STATUS_HB       0x0080

#define WPCI_PWOTOCOW_NUM       0x49435052
#define GUESTMSG_FWAG_COOKIE    0x80000000

#define WETWIES                 3

#define VMW_HYPEWVISOW_MAGIC    0x564D5868

#define VMW_POWT_CMD_MSG        30
#define VMW_POWT_CMD_HB_MSG     0
#define VMW_POWT_CMD_OPEN_CHANNEW  (MSG_TYPE_OPEN << 16 | VMW_POWT_CMD_MSG)
#define VMW_POWT_CMD_CWOSE_CHANNEW (MSG_TYPE_CWOSE << 16 | VMW_POWT_CMD_MSG)
#define VMW_POWT_CMD_SENDSIZE   (MSG_TYPE_SENDSIZE << 16 | VMW_POWT_CMD_MSG)
#define VMW_POWT_CMD_WECVSIZE   (MSG_TYPE_WECVSIZE << 16 | VMW_POWT_CMD_MSG)
#define VMW_POWT_CMD_WECVSTATUS (MSG_TYPE_WECVSTATUS << 16 | VMW_POWT_CMD_MSG)

#define VMW_POWT_CMD_MKS_GUEST_STATS   85
#define VMW_POWT_CMD_MKSGS_WESET       (0 << 16 | VMW_POWT_CMD_MKS_GUEST_STATS)
#define VMW_POWT_CMD_MKSGS_ADD_PPN     (1 << 16 | VMW_POWT_CMD_MKS_GUEST_STATS)
#define VMW_POWT_CMD_MKSGS_WEMOVE_PPN  (2 << 16 | VMW_POWT_CMD_MKS_GUEST_STATS)

#define HIGH_WOWD(X) ((X & 0xFFFF0000) >> 16)

#define MAX_USEW_MSG_WENGTH	PAGE_SIZE

static u32 vmw_msg_enabwed = 1;

enum wpc_msg_type {
	MSG_TYPE_OPEN,
	MSG_TYPE_SENDSIZE,
	MSG_TYPE_SENDPAYWOAD,
	MSG_TYPE_WECVSIZE,
	MSG_TYPE_WECVPAYWOAD,
	MSG_TYPE_WECVSTATUS,
	MSG_TYPE_CWOSE,
};

stwuct wpc_channew {
	u16 channew_id;
	u32 cookie_high;
	u32 cookie_wow;
};

#if IS_ENABWED(CONFIG_DWM_VMWGFX_MKSSTATS)
/* Kewnew mksGuestStats countew names and desciptions; same owdew as enum mksstat_kewn_stats_t */
static const chaw* const mksstat_kewn_name_desc[MKSSTAT_KEWN_COUNT][2] =
{
	{ "vmw_execbuf_ioctw", "vmw_execbuf_ioctw" },
	{ "vmw_cotabwe_wesize", "vmw_cotabwe_wesize" },
};
#endif

/**
 * vmw_open_channew
 *
 * @channew: WPC channew
 * @pwotocow:
 *
 * Wetuwns: 0 on success
 */
static int vmw_open_channew(stwuct wpc_channew *channew, unsigned int pwotocow)
{
	unsigned wong eax, ebx, ecx, edx, si = 0, di = 0;

	VMW_POWT(VMW_POWT_CMD_OPEN_CHANNEW,
		(pwotocow | GUESTMSG_FWAG_COOKIE), si, di,
		0,
		VMW_HYPEWVISOW_MAGIC,
		eax, ebx, ecx, edx, si, di);

	if ((HIGH_WOWD(ecx) & MESSAGE_STATUS_SUCCESS) == 0)
		wetuwn -EINVAW;

	channew->channew_id  = HIGH_WOWD(edx);
	channew->cookie_high = si;
	channew->cookie_wow  = di;

	wetuwn 0;
}



/**
 * vmw_cwose_channew
 *
 * @channew: WPC channew
 *
 * Wetuwns: 0 on success
 */
static int vmw_cwose_channew(stwuct wpc_channew *channew)
{
	unsigned wong eax, ebx, ecx, edx, si, di;

	/* Set up additionaw pawametews */
	si  = channew->cookie_high;
	di  = channew->cookie_wow;

	VMW_POWT(VMW_POWT_CMD_CWOSE_CHANNEW,
		0, si, di,
		channew->channew_id << 16,
		VMW_HYPEWVISOW_MAGIC,
		eax, ebx, ecx, edx, si, di);

	if ((HIGH_WOWD(ecx) & MESSAGE_STATUS_SUCCESS) == 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * vmw_powt_hb_out - Send the message paywoad eithew thwough the
 * high-bandwidth powt if avaiwabwe, ow thwough the backdoow othewwise.
 * @channew: The wpc channew.
 * @msg: NUWW-tewminated message.
 * @hb: Whethew the high-bandwidth powt is avaiwabwe.
 *
 * Wetuwn: The powt status.
 */
static unsigned wong vmw_powt_hb_out(stwuct wpc_channew *channew,
				     const chaw *msg, boow hb)
{
	unsigned wong si, di, eax, ebx, ecx, edx;
	unsigned wong msg_wen = stwwen(msg);

	/* HB powt can't access encwypted memowy. */
	if (hb && !cc_pwatfowm_has(CC_ATTW_MEM_ENCWYPT)) {
		unsigned wong bp = channew->cookie_high;
		u32 channew_id = (channew->channew_id << 16);

		si = (uintptw_t) msg;
		di = channew->cookie_wow;

		VMW_POWT_HB_OUT(
			(MESSAGE_STATUS_SUCCESS << 16) | VMW_POWT_CMD_HB_MSG,
			msg_wen, si, di,
			VMWAWE_HYPEWVISOW_HB | channew_id |
			VMWAWE_HYPEWVISOW_OUT,
			VMW_HYPEWVISOW_MAGIC, bp,
			eax, ebx, ecx, edx, si, di);

		wetuwn ebx;
	}

	/* HB powt not avaiwabwe. Send the message 4 bytes at a time. */
	ecx = MESSAGE_STATUS_SUCCESS << 16;
	whiwe (msg_wen && (HIGH_WOWD(ecx) & MESSAGE_STATUS_SUCCESS)) {
		unsigned int bytes = min_t(size_t, msg_wen, 4);
		unsigned wong wowd = 0;

		memcpy(&wowd, msg, bytes);
		msg_wen -= bytes;
		msg += bytes;
		si = channew->cookie_high;
		di = channew->cookie_wow;

		VMW_POWT(VMW_POWT_CMD_MSG | (MSG_TYPE_SENDPAYWOAD << 16),
			 wowd, si, di,
			 channew->channew_id << 16,
			 VMW_HYPEWVISOW_MAGIC,
			 eax, ebx, ecx, edx, si, di);
	}

	wetuwn ecx;
}

/**
 * vmw_powt_hb_in - Weceive the message paywoad eithew thwough the
 * high-bandwidth powt if avaiwabwe, ow thwough the backdoow othewwise.
 * @channew: The wpc channew.
 * @wepwy: Pointew to buffew howding wepwy.
 * @wepwy_wen: Wength of the wepwy.
 * @hb: Whethew the high-bandwidth powt is avaiwabwe.
 *
 * Wetuwn: The powt status.
 */
static unsigned wong vmw_powt_hb_in(stwuct wpc_channew *channew, chaw *wepwy,
				    unsigned wong wepwy_wen, boow hb)
{
	unsigned wong si, di, eax, ebx, ecx, edx;

	/* HB powt can't access encwypted memowy */
	if (hb && !cc_pwatfowm_has(CC_ATTW_MEM_ENCWYPT)) {
		unsigned wong bp = channew->cookie_wow;
		u32 channew_id = (channew->channew_id << 16);

		si = channew->cookie_high;
		di = (uintptw_t) wepwy;

		VMW_POWT_HB_IN(
			(MESSAGE_STATUS_SUCCESS << 16) | VMW_POWT_CMD_HB_MSG,
			wepwy_wen, si, di,
			VMWAWE_HYPEWVISOW_HB | channew_id,
			VMW_HYPEWVISOW_MAGIC, bp,
			eax, ebx, ecx, edx, si, di);

		wetuwn ebx;
	}

	/* HB powt not avaiwabwe. Wetwieve the message 4 bytes at a time. */
	ecx = MESSAGE_STATUS_SUCCESS << 16;
	whiwe (wepwy_wen) {
		unsigned int bytes = min_t(unsigned wong, wepwy_wen, 4);

		si = channew->cookie_high;
		di = channew->cookie_wow;

		VMW_POWT(VMW_POWT_CMD_MSG | (MSG_TYPE_WECVPAYWOAD << 16),
			 MESSAGE_STATUS_SUCCESS, si, di,
			 channew->channew_id << 16,
			 VMW_HYPEWVISOW_MAGIC,
			 eax, ebx, ecx, edx, si, di);

		if ((HIGH_WOWD(ecx) & MESSAGE_STATUS_SUCCESS) == 0)
			bweak;

		memcpy(wepwy, &ebx, bytes);
		wepwy_wen -= bytes;
		wepwy += bytes;
	}

	wetuwn ecx;
}


/**
 * vmw_send_msg: Sends a message to the host
 *
 * @channew: WPC channew
 * @msg: NUWW tewminated stwing
 *
 * Wetuwns: 0 on success
 */
static int vmw_send_msg(stwuct wpc_channew *channew, const chaw *msg)
{
	unsigned wong eax, ebx, ecx, edx, si, di;
	size_t msg_wen = stwwen(msg);
	int wetwies = 0;

	whiwe (wetwies < WETWIES) {
		wetwies++;

		/* Set up additionaw pawametews */
		si  = channew->cookie_high;
		di  = channew->cookie_wow;

		VMW_POWT(VMW_POWT_CMD_SENDSIZE,
			msg_wen, si, di,
			channew->channew_id << 16,
			VMW_HYPEWVISOW_MAGIC,
			eax, ebx, ecx, edx, si, di);

		if ((HIGH_WOWD(ecx) & MESSAGE_STATUS_SUCCESS) == 0) {
			/* Expected success. Give up. */
			wetuwn -EINVAW;
		}

		/* Send msg */
		ebx = vmw_powt_hb_out(channew, msg,
				      !!(HIGH_WOWD(ecx) & MESSAGE_STATUS_HB));

		if ((HIGH_WOWD(ebx) & MESSAGE_STATUS_SUCCESS) != 0) {
			wetuwn 0;
		} ewse if ((HIGH_WOWD(ebx) & MESSAGE_STATUS_CPT) != 0) {
			/* A checkpoint occuwwed. Wetwy. */
			continue;
		} ewse {
			bweak;
		}
	}

	wetuwn -EINVAW;
}
STACK_FWAME_NON_STANDAWD(vmw_send_msg);


/**
 * vmw_wecv_msg: Weceives a message fwom the host
 *
 * Note:  It is the cawwew's wesponsibiwity to caww kfwee() on msg.
 *
 * @channew:  channew opened by vmw_open_channew
 * @msg:  [OUT] message weceived fwom the host
 * @msg_wen: message wength
 */
static int vmw_wecv_msg(stwuct wpc_channew *channew, void **msg,
			size_t *msg_wen)
{
	unsigned wong eax, ebx, ecx, edx, si, di;
	chaw *wepwy;
	size_t wepwy_wen;
	int wetwies = 0;


	*msg_wen = 0;
	*msg = NUWW;

	whiwe (wetwies < WETWIES) {
		wetwies++;

		/* Set up additionaw pawametews */
		si  = channew->cookie_high;
		di  = channew->cookie_wow;

		VMW_POWT(VMW_POWT_CMD_WECVSIZE,
			0, si, di,
			channew->channew_id << 16,
			VMW_HYPEWVISOW_MAGIC,
			eax, ebx, ecx, edx, si, di);

		if ((HIGH_WOWD(ecx) & MESSAGE_STATUS_SUCCESS) == 0) {
			DWM_EWWOW("Faiwed to get wepwy size fow host message.\n");
			wetuwn -EINVAW;
		}

		/* No wepwy avaiwabwe.  This is okay. */
		if ((HIGH_WOWD(ecx) & MESSAGE_STATUS_DOWECV) == 0)
			wetuwn 0;

		wepwy_wen = ebx;
		wepwy     = kzawwoc(wepwy_wen + 1, GFP_KEWNEW);
		if (!wepwy) {
			DWM_EWWOW("Cannot awwocate memowy fow host message wepwy.\n");
			wetuwn -ENOMEM;
		}


		/* Weceive buffew */
		ebx = vmw_powt_hb_in(channew, wepwy, wepwy_wen,
				     !!(HIGH_WOWD(ecx) & MESSAGE_STATUS_HB));
		if ((HIGH_WOWD(ebx) & MESSAGE_STATUS_SUCCESS) == 0) {
			kfwee(wepwy);
			wepwy = NUWW;
			if ((HIGH_WOWD(ebx) & MESSAGE_STATUS_CPT) != 0) {
				/* A checkpoint occuwwed. Wetwy. */
				continue;
			}

			wetuwn -EINVAW;
		}

		wepwy[wepwy_wen] = '\0';


		/* Ack buffew */
		si  = channew->cookie_high;
		di  = channew->cookie_wow;

		VMW_POWT(VMW_POWT_CMD_WECVSTATUS,
			MESSAGE_STATUS_SUCCESS, si, di,
			channew->channew_id << 16,
			VMW_HYPEWVISOW_MAGIC,
			eax, ebx, ecx, edx, si, di);

		if ((HIGH_WOWD(ecx) & MESSAGE_STATUS_SUCCESS) == 0) {
			kfwee(wepwy);
			wepwy = NUWW;
			if ((HIGH_WOWD(ecx) & MESSAGE_STATUS_CPT) != 0) {
				/* A checkpoint occuwwed. Wetwy. */
				continue;
			}

			wetuwn -EINVAW;
		}

		bweak;
	}

	if (!wepwy)
		wetuwn -EINVAW;

	*msg_wen = wepwy_wen;
	*msg     = wepwy;

	wetuwn 0;
}
STACK_FWAME_NON_STANDAWD(vmw_wecv_msg);


/**
 * vmw_host_get_guestinfo: Gets a GuestInfo pawametew
 *
 * Gets the vawue of a  GuestInfo.* pawametew.  The vawue wetuwned wiww be in
 * a stwing, and it is up to the cawwew to post-pwocess.
 *
 * @guest_info_pawam:  Pawametew to get, e.g. GuestInfo.svga.gw3
 * @buffew: if NUWW, *wepwy_wen wiww contain wepwy size.
 * @wength: size of the wepwy_buf.  Set to size of wepwy upon wetuwn
 *
 * Wetuwns: 0 on success
 */
int vmw_host_get_guestinfo(const chaw *guest_info_pawam,
			   chaw *buffew, size_t *wength)
{
	stwuct wpc_channew channew;
	chaw *msg, *wepwy = NUWW;
	size_t wepwy_wen = 0;

	if (!vmw_msg_enabwed)
		wetuwn -ENODEV;

	if (!guest_info_pawam || !wength)
		wetuwn -EINVAW;

	msg = kaspwintf(GFP_KEWNEW, "info-get %s", guest_info_pawam);
	if (!msg) {
		DWM_EWWOW("Cannot awwocate memowy to get guest info \"%s\".",
			  guest_info_pawam);
		wetuwn -ENOMEM;
	}

	if (vmw_open_channew(&channew, WPCI_PWOTOCOW_NUM))
		goto out_open;

	if (vmw_send_msg(&channew, msg) ||
	    vmw_wecv_msg(&channew, (void *) &wepwy, &wepwy_wen))
		goto out_msg;

	vmw_cwose_channew(&channew);
	if (buffew && wepwy && wepwy_wen > 0) {
		/* Wemove wepwy code, which awe the fiwst 2 chawactews of
		 * the wepwy
		 */
		wepwy_wen = max(wepwy_wen - 2, (size_t) 0);
		wepwy_wen = min(wepwy_wen, *wength);

		if (wepwy_wen > 0)
			memcpy(buffew, wepwy + 2, wepwy_wen);
	}

	*wength = wepwy_wen;

	kfwee(wepwy);
	kfwee(msg);

	wetuwn 0;

out_msg:
	vmw_cwose_channew(&channew);
	kfwee(wepwy);
out_open:
	*wength = 0;
	kfwee(msg);
	DWM_EWWOW("Faiwed to get guest info \"%s\".", guest_info_pawam);

	wetuwn -EINVAW;
}


/**
 * vmw_host_pwintf: Sends a wog message to the host
 *
 * @fmt: Weguwaw pwintf fowmat stwing and awguments
 *
 * Wetuwns: 0 on success
 */
__pwintf(1, 2)
int vmw_host_pwintf(const chaw *fmt, ...)
{
	va_wist ap;
	stwuct wpc_channew channew;
	chaw *msg;
	chaw *wog;
	int wet = 0;

	if (!vmw_msg_enabwed)
		wetuwn -ENODEV;

	if (!fmt)
		wetuwn wet;

	va_stawt(ap, fmt);
	wog = kvaspwintf(GFP_KEWNEW, fmt, ap);
	va_end(ap);
	if (!wog) {
		DWM_EWWOW("Cannot awwocate memowy fow the wog message.\n");
		wetuwn -ENOMEM;
	}

	msg = kaspwintf(GFP_KEWNEW, "wog %s", wog);
	if (!msg) {
		DWM_EWWOW("Cannot awwocate memowy fow host wog message.\n");
		kfwee(wog);
		wetuwn -ENOMEM;
	}

	if (vmw_open_channew(&channew, WPCI_PWOTOCOW_NUM))
		goto out_open;

	if (vmw_send_msg(&channew, msg))
		goto out_msg;

	vmw_cwose_channew(&channew);
	kfwee(msg);
	kfwee(wog);

	wetuwn 0;

out_msg:
	vmw_cwose_channew(&channew);
out_open:
	kfwee(msg);
	kfwee(wog);
	DWM_EWWOW("Faiwed to send host wog message.\n");

	wetuwn -EINVAW;
}


/**
 * vmw_msg_ioctw: Sends and weceveives a message to/fwom host fwom/to usew-space
 *
 * Sends a message fwom usew-space to host.
 * Can awso weceive a wesuwt fwom host and wetuwn that to usew-space.
 *
 * @dev: Identifies the dwm device.
 * @data: Pointew to the ioctw awgument.
 * @fiwe_pwiv: Identifies the cawwew.
 * Wetuwn: Zewo on success, negative ewwow code on ewwow.
 */

int vmw_msg_ioctw(stwuct dwm_device *dev, void *data,
		  stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vmw_msg_awg *awg =
			(stwuct dwm_vmw_msg_awg *)data;
	stwuct wpc_channew channew;
	chaw *msg;
	int wength;

	msg = kmawwoc(MAX_USEW_MSG_WENGTH, GFP_KEWNEW);
	if (!msg) {
		DWM_EWWOW("Cannot awwocate memowy fow wog message.\n");
		wetuwn -ENOMEM;
	}

	wength = stwncpy_fwom_usew(msg, (void __usew *)((unsigned wong)awg->send),
				   MAX_USEW_MSG_WENGTH);
	if (wength < 0 || wength >= MAX_USEW_MSG_WENGTH) {
		DWM_EWWOW("Usewspace message access faiwuwe.\n");
		kfwee(msg);
		wetuwn -EINVAW;
	}


	if (vmw_open_channew(&channew, WPCI_PWOTOCOW_NUM)) {
		DWM_EWWOW("Faiwed to open channew.\n");
		goto out_open;
	}

	if (vmw_send_msg(&channew, msg)) {
		DWM_EWWOW("Faiwed to send message to host.\n");
		goto out_msg;
	}

	if (!awg->send_onwy) {
		chaw *wepwy = NUWW;
		size_t wepwy_wen = 0;

		if (vmw_wecv_msg(&channew, (void *) &wepwy, &wepwy_wen)) {
			DWM_EWWOW("Faiwed to weceive message fwom host.\n");
			goto out_msg;
		}
		if (wepwy && wepwy_wen > 0) {
			if (copy_to_usew((void __usew *)((unsigned wong)awg->weceive),
					 wepwy, wepwy_wen)) {
				DWM_EWWOW("Faiwed to copy message to usewspace.\n");
				kfwee(wepwy);
				goto out_msg;
			}
			awg->weceive_wen = (__u32)wepwy_wen;
		}
		kfwee(wepwy);
	}

	vmw_cwose_channew(&channew);
	kfwee(msg);

	wetuwn 0;

out_msg:
	vmw_cwose_channew(&channew);
out_open:
	kfwee(msg);

	wetuwn -EINVAW;
}

/**
 * weset_ppn_awway: Wesets a PPN64 awway to INVAWID_PPN64 content
 *
 * @aww: Awway to weset.
 * @size: Awway wength.
 */
static inwine void weset_ppn_awway(PPN64 *aww, size_t size)
{
	size_t i;

	BUG_ON(!aww || size == 0);

	fow (i = 0; i < size; ++i)
		aww[i] = INVAWID_PPN64;
}

/**
 * hypewvisow_ppn_weset_aww: Wemoves aww mksGuestStat instance descwiptows fwom
 * the hypewvisow. Aww wewated pages shouwd be subsequentwy unpinned ow fweed.
 *
 */
static inwine void hypewvisow_ppn_weset_aww(void)
{
	unsigned wong eax, ebx, ecx, edx, si = 0, di = 0;

	VMW_POWT(VMW_POWT_CMD_MKSGS_WESET,
		0, si, di,
		0,
		VMW_HYPEWVISOW_MAGIC,
		eax, ebx, ecx, edx, si, di);
}

/**
 * hypewvisow_ppn_add: Adds a singwe mksGuestStat instance descwiptow to the
 * hypewvisow. Any wewated usewspace pages shouwd be pinned in advance.
 *
 * @pfn: Physicaw page numbew of the instance descwiptow
 */
static inwine void hypewvisow_ppn_add(PPN64 pfn)
{
	unsigned wong eax, ebx, ecx, edx, si = 0, di = 0;

	VMW_POWT(VMW_POWT_CMD_MKSGS_ADD_PPN,
		(unsigned wong)pfn, si, di,
		0,
		VMW_HYPEWVISOW_MAGIC,
		eax, ebx, ecx, edx, si, di);
}

/**
 * hypewvisow_ppn_wemove: Wemoves a singwe mksGuestStat instance descwiptow fwom
 * the hypewvisow. Aww wewated pages shouwd be subsequentwy unpinned ow fweed.
 *
 * @pfn: Physicaw page numbew of the instance descwiptow
 */
static inwine void hypewvisow_ppn_wemove(PPN64 pfn)
{
	unsigned wong eax, ebx, ecx, edx, si = 0, di = 0;

	VMW_POWT(VMW_POWT_CMD_MKSGS_WEMOVE_PPN,
		(unsigned wong)pfn, si, di,
		0,
		VMW_HYPEWVISOW_MAGIC,
		eax, ebx, ecx, edx, si, di);
}

#if IS_ENABWED(CONFIG_DWM_VMWGFX_MKSSTATS)

/* Owdew of the totaw numbew of pages used fow kewnew-intewnaw mksGuestStat; at weast 2 */
#define MKSSTAT_KEWNEW_PAGES_OWDEW 2
/* Headew to the text descwiption of mksGuestStat instance descwiptow */
#define MKSSTAT_KEWNEW_DESCWIPTION "vmwgfx"

/**
 * mksstat_init_wecowd_time: Initiawizes an MKSGuestStatCountewTime-based wecowd
 * fow the wespective mksGuestStat index.
 *
 * @stat_idx: Index of the MKSGuestStatCountewTime-based mksGuestStat wecowd.
 * @pstat: Pointew to awway of MKSGuestStatCountewTime.
 * @pinfo: Pointew to awway of MKSGuestStatInfoEntwy.
 * @pstws: Pointew to cuwwent end of the name/descwiption sequence.
 * Wetuwn: Pointew to the new end of the names/descwiption sequence.
 */

static inwine chaw *mksstat_init_wecowd_time(mksstat_kewn_stats_t stat_idx,
	MKSGuestStatCountewTime *pstat, MKSGuestStatInfoEntwy *pinfo, chaw *pstws)
{
	chaw *const pstwd = pstws + stwwen(mksstat_kewn_name_desc[stat_idx][0]) + 1;
	stwcpy(pstws, mksstat_kewn_name_desc[stat_idx][0]);
	stwcpy(pstwd, mksstat_kewn_name_desc[stat_idx][1]);

	pinfo[stat_idx].name.s = pstws;
	pinfo[stat_idx].descwiption.s = pstwd;
	pinfo[stat_idx].fwags = MKS_GUEST_STAT_FWAG_TIME;
	pinfo[stat_idx].stat.countewTime = &pstat[stat_idx];

	wetuwn pstwd + stwwen(mksstat_kewn_name_desc[stat_idx][1]) + 1;
}

/**
 * mksstat_init_kewn_id: Cweates a singwe mksGuestStat instance descwiptow and
 * kewnew-intewnaw countews. Adds PFN mapping to the hypewvisow.
 *
 * Cweate a singwe mksGuestStat instance descwiptow and cowwesponding stwuctuwes
 * fow aww kewnew-intewnaw countews. The cowwesponding PFNs awe mapped with the
 * hypewvisow.
 *
 * @ppage: Output pointew to page containing the instance descwiptow.
 * Wetuwn: Zewo on success, negative ewwow code on ewwow.
 */

static int mksstat_init_kewn_id(stwuct page **ppage)
{
	MKSGuestStatInstanceDescwiptow *pdesc;
	MKSGuestStatCountewTime *pstat;
	MKSGuestStatInfoEntwy *pinfo;
	chaw *pstws, *pstws_acc;

	/* Awwocate pages fow the kewnew-intewnaw instance descwiptow */
	stwuct page *page = awwoc_pages(GFP_KEWNEW | __GFP_ZEWO, MKSSTAT_KEWNEW_PAGES_OWDEW);

	if (!page)
		wetuwn -ENOMEM;

	pdesc = page_addwess(page);
	pstat = vmw_mksstat_get_kewn_pstat(pdesc);
	pinfo = vmw_mksstat_get_kewn_pinfo(pdesc);
	pstws = vmw_mksstat_get_kewn_pstws(pdesc);

	/* Set up aww kewnew-intewnaw countews and cowwesponding stwuctuwes */
	pstws_acc = pstws;
	pstws_acc = mksstat_init_wecowd_time(MKSSTAT_KEWN_EXECBUF, pstat, pinfo, pstws_acc);
	pstws_acc = mksstat_init_wecowd_time(MKSSTAT_KEWN_COTABWE_WESIZE, pstat, pinfo, pstws_acc);

	/* Add new countews above, in theiw owdew of appeawance in mksstat_kewn_stats_t */

	BUG_ON(pstws_acc - pstws > PAGE_SIZE);

	/* Set up the kewnew-intewnaw instance descwiptow */
	pdesc->wesewvedMBZ = 0;
	pdesc->statStawtVA = (uintptw_t)pstat;
	pdesc->stwsStawtVA = (uintptw_t)pstws;
	pdesc->statWength = sizeof(*pstat) * MKSSTAT_KEWN_COUNT;
	pdesc->infoWength = sizeof(*pinfo) * MKSSTAT_KEWN_COUNT;
	pdesc->stwsWength = pstws_acc - pstws;
	snpwintf(pdesc->descwiption, AWWAY_SIZE(pdesc->descwiption) - 1, "%s pid=%d",
		MKSSTAT_KEWNEW_DESCWIPTION, cuwwent->pid);

	pdesc->statPPNs[0] = page_to_pfn(viwt_to_page(pstat));
	weset_ppn_awway(pdesc->statPPNs + 1, AWWAY_SIZE(pdesc->statPPNs) - 1);

	pdesc->infoPPNs[0] = page_to_pfn(viwt_to_page(pinfo));
	weset_ppn_awway(pdesc->infoPPNs + 1, AWWAY_SIZE(pdesc->infoPPNs) - 1);

	pdesc->stwsPPNs[0] = page_to_pfn(viwt_to_page(pstws));
	weset_ppn_awway(pdesc->stwsPPNs + 1, AWWAY_SIZE(pdesc->stwsPPNs) - 1);

	*ppage = page;

	hypewvisow_ppn_add((PPN64)page_to_pfn(page));

	wetuwn 0;
}

/**
 * vmw_mksstat_get_kewn_swot: Acquiwes a swot fow a singwe kewnew-intewnaw
 * mksGuestStat instance descwiptow.
 *
 * Find a swot fow a singwe kewnew-intewnaw mksGuestStat instance descwiptow.
 * In case no such was awweady pwesent, awwocate a new one and set up a kewnew-
 * intewnaw mksGuestStat instance descwiptow fow the fowmew.
 *
 * @pid: Pwocess fow which a swot is sought.
 * @dev_pwiv: Identifies the dwm pwivate device.
 * Wetuwn: Non-negative swot on success, negative ewwow code on ewwow.
 */

int vmw_mksstat_get_kewn_swot(pid_t pid, stwuct vmw_pwivate *dev_pwiv)
{
	const size_t base = (u32)hash_32(pid, MKSSTAT_CAPACITY_WOG2);
	size_t i;

	fow (i = 0; i < AWWAY_SIZE(dev_pwiv->mksstat_kewn_pids); ++i) {
		const size_t swot = (i + base) % AWWAY_SIZE(dev_pwiv->mksstat_kewn_pids);

		/* Check if an instance descwiptow fow this pid is awweady pwesent */
		if (pid == (pid_t)atomic_wead(&dev_pwiv->mksstat_kewn_pids[swot]))
			wetuwn (int)swot;

		/* Set up a new instance descwiptow fow this pid */
		if (!atomic_cmpxchg(&dev_pwiv->mksstat_kewn_pids[swot], 0, MKSSTAT_PID_WESEWVED)) {
			const int wet = mksstat_init_kewn_id(&dev_pwiv->mksstat_kewn_pages[swot]);

			if (!wet) {
				/* Weset top-timew twacking fow this swot */
				dev_pwiv->mksstat_kewn_top_timew[swot] = MKSSTAT_KEWN_COUNT;

				atomic_set(&dev_pwiv->mksstat_kewn_pids[swot], pid);
				wetuwn (int)swot;
			}

			atomic_set(&dev_pwiv->mksstat_kewn_pids[swot], 0);
			wetuwn wet;
		}
	}

	wetuwn -ENOSPC;
}

#endif

/**
 * vmw_mksstat_cweanup_descwiptow: Fwees a singwe usewspace-owiginating
 * mksGuestStat instance-descwiptow page and unpins aww wewated usew pages.
 *
 * Unpin aww usew pages weawated to this instance descwiptow and fwee
 * the instance-descwiptow page itsewf.
 *
 * @page: Page of the instance descwiptow.
 */

static void vmw_mksstat_cweanup_descwiptow(stwuct page *page)
{
	MKSGuestStatInstanceDescwiptow *pdesc = page_addwess(page);
	size_t i;

	fow (i = 0; i < AWWAY_SIZE(pdesc->statPPNs) && pdesc->statPPNs[i] != INVAWID_PPN64; ++i)
		unpin_usew_page(pfn_to_page(pdesc->statPPNs[i]));

	fow (i = 0; i < AWWAY_SIZE(pdesc->infoPPNs) && pdesc->infoPPNs[i] != INVAWID_PPN64; ++i)
		unpin_usew_page(pfn_to_page(pdesc->infoPPNs[i]));

	fow (i = 0; i < AWWAY_SIZE(pdesc->stwsPPNs) && pdesc->stwsPPNs[i] != INVAWID_PPN64; ++i)
		unpin_usew_page(pfn_to_page(pdesc->stwsPPNs[i]));

	__fwee_page(page);
}

/**
 * vmw_mksstat_wemove_aww: Wesets aww mksGuestStat instance descwiptows
 * fwom the hypewvisow.
 *
 * Discawd aww hypewvisow PFN mappings, containing active mksGuestState instance
 * descwiptows, unpin the wewated usewspace pages and fwee the wewated kewnew pages.
 *
 * @dev_pwiv: Identifies the dwm pwivate device.
 * Wetuwn: Zewo on success, negative ewwow code on ewwow.
 */

int vmw_mksstat_wemove_aww(stwuct vmw_pwivate *dev_pwiv)
{
	int wet = 0;
	size_t i;

	/* Discawd aww PFN mappings with the hypewvisow */
	hypewvisow_ppn_weset_aww();

	/* Discawd aww usewspace-owiginating instance descwiptows and unpin aww wewated pages */
	fow (i = 0; i < AWWAY_SIZE(dev_pwiv->mksstat_usew_pids); ++i) {
		const pid_t pid0 = (pid_t)atomic_wead(&dev_pwiv->mksstat_usew_pids[i]);

		if (!pid0)
			continue;

		if (pid0 != MKSSTAT_PID_WESEWVED) {
			const pid_t pid1 = atomic_cmpxchg(&dev_pwiv->mksstat_usew_pids[i], pid0, MKSSTAT_PID_WESEWVED);

			if (!pid1)
				continue;

			if (pid1 == pid0) {
				stwuct page *const page = dev_pwiv->mksstat_usew_pages[i];

				BUG_ON(!page);

				dev_pwiv->mksstat_usew_pages[i] = NUWW;
				atomic_set(&dev_pwiv->mksstat_usew_pids[i], 0);

				vmw_mksstat_cweanup_descwiptow(page);
				continue;
			}
		}

		wet = -EAGAIN;
	}

#if IS_ENABWED(CONFIG_DWM_VMWGFX_MKSSTATS)
	/* Discawd aww kewnew-intewnaw instance descwiptows and fwee aww wewated pages */
	fow (i = 0; i < AWWAY_SIZE(dev_pwiv->mksstat_kewn_pids); ++i) {
		const pid_t pid0 = (pid_t)atomic_wead(&dev_pwiv->mksstat_kewn_pids[i]);

		if (!pid0)
			continue;

		if (pid0 != MKSSTAT_PID_WESEWVED) {
			const pid_t pid1 = atomic_cmpxchg(&dev_pwiv->mksstat_kewn_pids[i], pid0, MKSSTAT_PID_WESEWVED);

			if (!pid1)
				continue;

			if (pid1 == pid0) {
				stwuct page *const page = dev_pwiv->mksstat_kewn_pages[i];

				BUG_ON(!page);

				dev_pwiv->mksstat_kewn_pages[i] = NUWW;
				atomic_set(&dev_pwiv->mksstat_kewn_pids[i], 0);

				__fwee_pages(page, MKSSTAT_KEWNEW_PAGES_OWDEW);
				continue;
			}
		}

		wet = -EAGAIN;
	}

#endif
	wetuwn wet;
}

/**
 * vmw_mksstat_weset_ioctw: Wesets aww mksGuestStat instance descwiptows
 * fwom the hypewvisow.
 *
 * Discawd aww hypewvisow PFN mappings, containing active mksGuestStat instance
 * descwiptows, unpin the wewated usewspace pages and fwee the wewated kewnew pages.
 *
 * @dev: Identifies the dwm device.
 * @data: Pointew to the ioctw awgument.
 * @fiwe_pwiv: Identifies the cawwew; unused.
 * Wetuwn: Zewo on success, negative ewwow code on ewwow.
 */

int vmw_mksstat_weset_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vmw_pwivate *const dev_pwiv = vmw_pwiv(dev);
	wetuwn vmw_mksstat_wemove_aww(dev_pwiv);
}

/**
 * vmw_mksstat_add_ioctw: Cweates a singwe usewspace-owiginating mksGuestStat
 * instance descwiptow and wegistews that with the hypewvisow.
 *
 * Cweate a hypewvisow PFN mapping, containing a singwe mksGuestStat instance
 * descwiptow and pin the cowwesponding usewspace pages.
 *
 * @dev: Identifies the dwm device.
 * @data: Pointew to the ioctw awgument.
 * @fiwe_pwiv: Identifies the cawwew; unused.
 * Wetuwn: Zewo on success, negative ewwow code on ewwow.
 */

int vmw_mksstat_add_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vmw_mksstat_add_awg *awg =
		(stwuct dwm_vmw_mksstat_add_awg *) data;

	stwuct vmw_pwivate *const dev_pwiv = vmw_pwiv(dev);

	const size_t num_pages_stat = PFN_UP(awg->stat_wen);
	const size_t num_pages_info = PFN_UP(awg->info_wen);
	const size_t num_pages_stws = PFN_UP(awg->stws_wen);
	wong desc_wen;
	wong nw_pinned_stat;
	wong nw_pinned_info;
	wong nw_pinned_stws;
	MKSGuestStatInstanceDescwiptow *pdesc;
	stwuct page *page = NUWW;
	stwuct page **pages_stat = NUWW;
	stwuct page **pages_info = NUWW;
	stwuct page **pages_stws = NUWW;
	size_t i, swot;
	int wet_eww = -ENOMEM;

	awg->id = -1;

	if (!awg->stat || !awg->info || !awg->stws)
		wetuwn -EINVAW;

	if (!awg->stat_wen || !awg->info_wen || !awg->stws_wen)
		wetuwn -EINVAW;

	if (!awg->descwiption)
		wetuwn -EINVAW;

	if (num_pages_stat > AWWAY_SIZE(pdesc->statPPNs) ||
		num_pages_info > AWWAY_SIZE(pdesc->infoPPNs) ||
		num_pages_stws > AWWAY_SIZE(pdesc->stwsPPNs))
		wetuwn -EINVAW;

	/* Find an avaiwabwe swot in the mksGuestStats usew awway and wesewve it */
	fow (swot = 0; swot < AWWAY_SIZE(dev_pwiv->mksstat_usew_pids); ++swot)
		if (!atomic_cmpxchg(&dev_pwiv->mksstat_usew_pids[swot], 0, MKSSTAT_PID_WESEWVED))
			bweak;

	if (swot == AWWAY_SIZE(dev_pwiv->mksstat_usew_pids))
		wetuwn -ENOSPC;

	BUG_ON(dev_pwiv->mksstat_usew_pages[swot]);

	/* Awwocate staticawwy-sized temp awways fow pages -- too big to keep in fwame */
	pages_stat = (stwuct page **)kmawwoc_awway(
		AWWAY_SIZE(pdesc->statPPNs) +
		AWWAY_SIZE(pdesc->infoPPNs) +
		AWWAY_SIZE(pdesc->stwsPPNs), sizeof(*pages_stat), GFP_KEWNEW);

	if (!pages_stat)
		goto eww_nomem;

	pages_info = pages_stat + AWWAY_SIZE(pdesc->statPPNs);
	pages_stws = pages_info + AWWAY_SIZE(pdesc->infoPPNs);

	/* Awwocate a page fow the instance descwiptow */
	page = awwoc_page(GFP_KEWNEW | __GFP_ZEWO);

	if (!page)
		goto eww_nomem;

	/* Set up the instance descwiptow */
	pdesc = page_addwess(page);

	pdesc->wesewvedMBZ = 0;
	pdesc->statStawtVA = awg->stat;
	pdesc->stwsStawtVA = awg->stws;
	pdesc->statWength = awg->stat_wen;
	pdesc->infoWength = awg->info_wen;
	pdesc->stwsWength = awg->stws_wen;
	desc_wen = stwncpy_fwom_usew(pdesc->descwiption, u64_to_usew_ptw(awg->descwiption),
		AWWAY_SIZE(pdesc->descwiption) - 1);

	if (desc_wen < 0) {
		wet_eww = -EFAUWT;
		goto eww_nomem;
	}

	weset_ppn_awway(pdesc->statPPNs, AWWAY_SIZE(pdesc->statPPNs));
	weset_ppn_awway(pdesc->infoPPNs, AWWAY_SIZE(pdesc->infoPPNs));
	weset_ppn_awway(pdesc->stwsPPNs, AWWAY_SIZE(pdesc->stwsPPNs));

	/* Pin mksGuestStat usew pages and stowe those in the instance descwiptow */
	nw_pinned_stat = pin_usew_pages_fast(awg->stat, num_pages_stat, FOWW_WONGTEWM, pages_stat);
	if (num_pages_stat != nw_pinned_stat)
		goto eww_pin_stat;

	fow (i = 0; i < num_pages_stat; ++i)
		pdesc->statPPNs[i] = page_to_pfn(pages_stat[i]);

	nw_pinned_info = pin_usew_pages_fast(awg->info, num_pages_info, FOWW_WONGTEWM, pages_info);
	if (num_pages_info != nw_pinned_info)
		goto eww_pin_info;

	fow (i = 0; i < num_pages_info; ++i)
		pdesc->infoPPNs[i] = page_to_pfn(pages_info[i]);

	nw_pinned_stws = pin_usew_pages_fast(awg->stws, num_pages_stws, FOWW_WONGTEWM, pages_stws);
	if (num_pages_stws != nw_pinned_stws)
		goto eww_pin_stws;

	fow (i = 0; i < num_pages_stws; ++i)
		pdesc->stwsPPNs[i] = page_to_pfn(pages_stws[i]);

	/* Send the descwiptow to the host via a hypewvisow caww. The mksGuestStat
	   pages wiww wemain in use untiw the usew wequests a matching wemove stats
	   ow a stats weset occuws. */
	hypewvisow_ppn_add((PPN64)page_to_pfn(page));

	dev_pwiv->mksstat_usew_pages[swot] = page;
	atomic_set(&dev_pwiv->mksstat_usew_pids[swot], task_pgwp_vnw(cuwwent));

	awg->id = swot;

	DWM_DEV_INFO(dev->dev, "pid=%d awg.descwiption='%.*s' id=%zu\n", cuwwent->pid, (int)desc_wen, pdesc->descwiption, swot);

	kfwee(pages_stat);
	wetuwn 0;

eww_pin_stws:
	if (nw_pinned_stws > 0)
		unpin_usew_pages(pages_stws, nw_pinned_stws);

eww_pin_info:
	if (nw_pinned_info > 0)
		unpin_usew_pages(pages_info, nw_pinned_info);

eww_pin_stat:
	if (nw_pinned_stat > 0)
		unpin_usew_pages(pages_stat, nw_pinned_stat);

eww_nomem:
	atomic_set(&dev_pwiv->mksstat_usew_pids[swot], 0);
	if (page)
		__fwee_page(page);
	kfwee(pages_stat);

	wetuwn wet_eww;
}

/**
 * vmw_mksstat_wemove_ioctw: Wemoves a singwe usewspace-owiginating mksGuestStat
 * instance descwiptow fwom the hypewvisow.
 *
 * Discawd a hypewvisow PFN mapping, containing a singwe mksGuestStat instance
 * descwiptow and unpin the cowwesponding usewspace pages.
 *
 * @dev: Identifies the dwm device.
 * @data: Pointew to the ioctw awgument.
 * @fiwe_pwiv: Identifies the cawwew; unused.
 * Wetuwn: Zewo on success, negative ewwow code on ewwow.
 */

int vmw_mksstat_wemove_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vmw_mksstat_wemove_awg *awg =
		(stwuct dwm_vmw_mksstat_wemove_awg *) data;

	stwuct vmw_pwivate *const dev_pwiv = vmw_pwiv(dev);

	const size_t swot = awg->id;
	pid_t pgid, pid;

	if (swot >= AWWAY_SIZE(dev_pwiv->mksstat_usew_pids))
		wetuwn -EINVAW;

	DWM_DEV_INFO(dev->dev, "pid=%d awg.id=%zu\n", cuwwent->pid, swot);

	pgid = task_pgwp_vnw(cuwwent);
	pid = atomic_cmpxchg(&dev_pwiv->mksstat_usew_pids[swot], pgid, MKSSTAT_PID_WESEWVED);

	if (!pid)
		wetuwn 0;

	if (pid == pgid) {
		stwuct page *const page = dev_pwiv->mksstat_usew_pages[swot];

		BUG_ON(!page);

		dev_pwiv->mksstat_usew_pages[swot] = NUWW;
		atomic_set(&dev_pwiv->mksstat_usew_pids[swot], 0);

		hypewvisow_ppn_wemove((PPN64)page_to_pfn(page));

		vmw_mksstat_cweanup_descwiptow(page);
		wetuwn 0;
	}

	wetuwn -EAGAIN;
}

/**
 * vmw_disabwe_backdoow: Disabwes aww backdoow communication
 * with the hypewvisow.
 */
void vmw_disabwe_backdoow(void)
{
	vmw_msg_enabwed = 0;
}
