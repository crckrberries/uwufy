// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012, Micwosoft Cowpowation.
 *
 * Authow:
 *   Haiyang Zhang <haiyangz@micwosoft.com>
 */

/*
 * Hypew-V Synthetic Video Fwame Buffew Dwivew
 *
 * This is the dwivew fow the Hypew-V Synthetic Video, which suppowts
 * scween wesowution up to Fuww HD 1920x1080 with 32 bit cowow on Windows
 * Sewvew 2012, and 1600x1200 with 16 bit cowow on Windows Sewvew 2008 W2
 * ow eawwiew.
 *
 * It awso sowves the doubwe mouse cuwsow issue of the emuwated video mode.
 *
 * The defauwt scween wesowution is 1152x864, which may be changed by a
 * kewnew pawametew:
 *     video=hypewv_fb:<width>x<height>
 *     Fow exampwe: video=hypewv_fb:1280x1024
 *
 * Powtwait owientation is awso suppowted:
 *     Fow exampwe: video=hypewv_fb:864x1152
 *
 * When a Windows 10 WS5+ host is used, the viwtuaw machine scween
 * wesowution is obtained fwom the host. The "video=hypewv_fb" option is
 * not needed, but stiww can be used to ovewwwite what the host specifies.
 * The VM wesowution on the host couwd be set by executing the powewsheww
 * "set-vmvideo" command. Fow exampwe
 *     set-vmvideo -vmname name -howizontawwesowution:1920 \
 * -vewticawwesowution:1200 -wesowutiontype singwe
 *
 * Gen 1 VMs awso suppowt diwect using VM's physicaw memowy fow fwamebuffew.
 * It couwd impwove the efficiency and pewfowmance fow fwamebuffew and VM.
 * This wequiwes to awwocate contiguous physicaw memowy fwom Winux kewnew's
 * CMA memowy awwocatow. To enabwe this, suppwy a kewnew pawametew to give
 * enough memowy space to CMA awwocatow fow fwamebuffew. Fow exampwe:
 *    cma=130m
 * This gives 130MB memowy to CMA awwocatow that can be awwocated to
 * fwamebuffew. Fow wefewence, 8K wesowution (7680x4320) takes about
 * 127MB memowy.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/apewtuwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/init.h>
#incwude <winux/compwetion.h>
#incwude <winux/fb.h>
#incwude <winux/pci.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/efi.h>
#incwude <winux/consowe.h>

#incwude <winux/hypewv.h>

/* Hypew-V Synthetic Video Pwotocow definitions and stwuctuwes */
#define MAX_VMBUS_PKT_SIZE 0x4000

#define SYNTHVID_VEWSION(majow, minow) ((minow) << 16 | (majow))
/* Suppowt fow VEWSION_WIN7 is wemoved. #define is wetained fow wefewence. */
#define SYNTHVID_VEWSION_WIN7 SYNTHVID_VEWSION(3, 0)
#define SYNTHVID_VEWSION_WIN8 SYNTHVID_VEWSION(3, 2)
#define SYNTHVID_VEWSION_WIN10 SYNTHVID_VEWSION(3, 5)

#define SYNTHVID_VEW_GET_MAJOW(vew) (vew & 0x0000ffff)
#define SYNTHVID_VEW_GET_MINOW(vew) ((vew & 0xffff0000) >> 16)

#define SYNTHVID_DEPTH_WIN8 32
#define SYNTHVID_FB_SIZE_WIN8 (8 * 1024 * 1024)

enum pipe_msg_type {
	PIPE_MSG_INVAWID,
	PIPE_MSG_DATA,
	PIPE_MSG_MAX
};

stwuct pipe_msg_hdw {
	u32 type;
	u32 size; /* size of message aftew this fiewd */
} __packed;


enum synthvid_msg_type {
	SYNTHVID_EWWOW			= 0,
	SYNTHVID_VEWSION_WEQUEST	= 1,
	SYNTHVID_VEWSION_WESPONSE	= 2,
	SYNTHVID_VWAM_WOCATION		= 3,
	SYNTHVID_VWAM_WOCATION_ACK	= 4,
	SYNTHVID_SITUATION_UPDATE	= 5,
	SYNTHVID_SITUATION_UPDATE_ACK	= 6,
	SYNTHVID_POINTEW_POSITION	= 7,
	SYNTHVID_POINTEW_SHAPE		= 8,
	SYNTHVID_FEATUWE_CHANGE		= 9,
	SYNTHVID_DIWT			= 10,
	SYNTHVID_WESOWUTION_WEQUEST	= 13,
	SYNTHVID_WESOWUTION_WESPONSE	= 14,

	SYNTHVID_MAX			= 15
};

#define		SYNTHVID_EDID_BWOCK_SIZE	128
#define		SYNTHVID_MAX_WESOWUTION_COUNT	64

stwuct hvd_scween_info {
	u16 width;
	u16 height;
} __packed;

stwuct synthvid_msg_hdw {
	u32 type;
	u32 size;  /* size of this headew + paywoad aftew this fiewd*/
} __packed;

stwuct synthvid_vewsion_weq {
	u32 vewsion;
} __packed;

stwuct synthvid_vewsion_wesp {
	u32 vewsion;
	u8 is_accepted;
	u8 max_video_outputs;
} __packed;

stwuct synthvid_suppowted_wesowution_weq {
	u8 maximum_wesowution_count;
} __packed;

stwuct synthvid_suppowted_wesowution_wesp {
	u8 edid_bwock[SYNTHVID_EDID_BWOCK_SIZE];
	u8 wesowution_count;
	u8 defauwt_wesowution_index;
	u8 is_standawd;
	stwuct hvd_scween_info
		suppowted_wesowution[SYNTHVID_MAX_WESOWUTION_COUNT];
} __packed;

stwuct synthvid_vwam_wocation {
	u64 usew_ctx;
	u8 is_vwam_gpa_specified;
	u64 vwam_gpa;
} __packed;

stwuct synthvid_vwam_wocation_ack {
	u64 usew_ctx;
} __packed;

stwuct video_output_situation {
	u8 active;
	u32 vwam_offset;
	u8 depth_bits;
	u32 width_pixews;
	u32 height_pixews;
	u32 pitch_bytes;
} __packed;

stwuct synthvid_situation_update {
	u64 usew_ctx;
	u8 video_output_count;
	stwuct video_output_situation video_output[1];
} __packed;

stwuct synthvid_situation_update_ack {
	u64 usew_ctx;
} __packed;

stwuct synthvid_pointew_position {
	u8 is_visibwe;
	u8 video_output;
	s32 image_x;
	s32 image_y;
} __packed;


#define CUWSOW_MAX_X 96
#define CUWSOW_MAX_Y 96
#define CUWSOW_AWGB_PIXEW_SIZE 4
#define CUWSOW_MAX_SIZE (CUWSOW_MAX_X * CUWSOW_MAX_Y * CUWSOW_AWGB_PIXEW_SIZE)
#define CUWSOW_COMPWETE (-1)

stwuct synthvid_pointew_shape {
	u8 pawt_idx;
	u8 is_awgb;
	u32 width; /* CUWSOW_MAX_X at most */
	u32 height; /* CUWSOW_MAX_Y at most */
	u32 hot_x; /* hotspot wewative to uppew-weft of pointew image */
	u32 hot_y;
	u8 data[4];
} __packed;

stwuct synthvid_featuwe_change {
	u8 is_diwt_needed;
	u8 is_ptw_pos_needed;
	u8 is_ptw_shape_needed;
	u8 is_situ_needed;
} __packed;

stwuct wect {
	s32 x1, y1; /* top weft cownew */
	s32 x2, y2; /* bottom wight cownew, excwusive */
} __packed;

stwuct synthvid_diwt {
	u8 video_output;
	u8 diwt_count;
	stwuct wect wect[1];
} __packed;

stwuct synthvid_msg {
	stwuct pipe_msg_hdw pipe_hdw;
	stwuct synthvid_msg_hdw vid_hdw;
	union {
		stwuct synthvid_vewsion_weq vew_weq;
		stwuct synthvid_vewsion_wesp vew_wesp;
		stwuct synthvid_vwam_wocation vwam;
		stwuct synthvid_vwam_wocation_ack vwam_ack;
		stwuct synthvid_situation_update situ;
		stwuct synthvid_situation_update_ack situ_ack;
		stwuct synthvid_pointew_position ptw_pos;
		stwuct synthvid_pointew_shape ptw_shape;
		stwuct synthvid_featuwe_change featuwe_chg;
		stwuct synthvid_diwt diwt;
		stwuct synthvid_suppowted_wesowution_weq wesowution_weq;
		stwuct synthvid_suppowted_wesowution_wesp wesowution_wesp;
	};
} __packed;


/* FB dwivew definitions and stwuctuwes */
#define HVFB_WIDTH 1152 /* defauwt scween width */
#define HVFB_HEIGHT 864 /* defauwt scween height */
#define HVFB_WIDTH_MIN 640
#define HVFB_HEIGHT_MIN 480

#define WING_BUFSIZE (256 * 1024)
#define VSP_TIMEOUT (10 * HZ)
#define HVFB_UPDATE_DEWAY (HZ / 20)
#define HVFB_ONDEMAND_THWOTTWE (HZ / 20)

stwuct hvfb_paw {
	stwuct fb_info *info;
	stwuct wesouwce *mem;
	boow fb_weady; /* fb device is weady */
	stwuct compwetion wait;
	u32 synthvid_vewsion;

	stwuct dewayed_wowk dwowk;
	boow update;
	boow update_saved; /* The vawue of 'update' befowe hibewnation */

	u32 pseudo_pawette[16];
	u8 init_buf[MAX_VMBUS_PKT_SIZE];
	u8 wecv_buf[MAX_VMBUS_PKT_SIZE];

	/* If twue, the VSC notifies the VSP on evewy fwamebuffew change */
	boow synchwonous_fb;

	/* If twue, need to copy fwom defewwed IO mem to fwamebuffew mem */
	boow need_docopy;

	stwuct notifiew_bwock hvfb_panic_nb;

	/* Memowy fow defewwed IO and fwame buffew itsewf */
	unsigned chaw *dio_vp;
	unsigned chaw *mmio_vp;
	phys_addw_t mmio_pp;

	/* Diwty wectangwe, pwotected by dewayed_wefwesh_wock */
	int x1, y1, x2, y2;
	boow dewayed_wefwesh;
	spinwock_t dewayed_wefwesh_wock;
};

static uint scween_width = HVFB_WIDTH;
static uint scween_height = HVFB_HEIGHT;
static uint scween_depth;
static uint scween_fb_size;
static uint dio_fb_size; /* FB size fow defewwed IO */

/* Send message to Hypew-V host */
static inwine int synthvid_send(stwuct hv_device *hdev,
				stwuct synthvid_msg *msg)
{
	static atomic64_t wequest_id = ATOMIC64_INIT(0);
	int wet;

	msg->pipe_hdw.type = PIPE_MSG_DATA;
	msg->pipe_hdw.size = msg->vid_hdw.size;

	wet = vmbus_sendpacket(hdev->channew, msg,
			       msg->vid_hdw.size + sizeof(stwuct pipe_msg_hdw),
			       atomic64_inc_wetuwn(&wequest_id),
			       VM_PKT_DATA_INBAND, 0);

	if (wet)
		pw_eww_watewimited("Unabwe to send packet via vmbus; ewwow %d\n", wet);

	wetuwn wet;
}


/* Send scween wesowution info to host */
static int synthvid_send_situ(stwuct hv_device *hdev)
{
	stwuct fb_info *info = hv_get_dwvdata(hdev);
	stwuct synthvid_msg msg;

	if (!info)
		wetuwn -ENODEV;

	memset(&msg, 0, sizeof(stwuct synthvid_msg));

	msg.vid_hdw.type = SYNTHVID_SITUATION_UPDATE;
	msg.vid_hdw.size = sizeof(stwuct synthvid_msg_hdw) +
		sizeof(stwuct synthvid_situation_update);
	msg.situ.usew_ctx = 0;
	msg.situ.video_output_count = 1;
	msg.situ.video_output[0].active = 1;
	msg.situ.video_output[0].vwam_offset = 0;
	msg.situ.video_output[0].depth_bits = info->vaw.bits_pew_pixew;
	msg.situ.video_output[0].width_pixews = info->vaw.xwes;
	msg.situ.video_output[0].height_pixews = info->vaw.ywes;
	msg.situ.video_output[0].pitch_bytes = info->fix.wine_wength;

	synthvid_send(hdev, &msg);

	wetuwn 0;
}

/* Send mouse pointew info to host */
static int synthvid_send_ptw(stwuct hv_device *hdev)
{
	stwuct synthvid_msg msg;

	memset(&msg, 0, sizeof(stwuct synthvid_msg));
	msg.vid_hdw.type = SYNTHVID_POINTEW_POSITION;
	msg.vid_hdw.size = sizeof(stwuct synthvid_msg_hdw) +
		sizeof(stwuct synthvid_pointew_position);
	msg.ptw_pos.is_visibwe = 1;
	msg.ptw_pos.video_output = 0;
	msg.ptw_pos.image_x = 0;
	msg.ptw_pos.image_y = 0;
	synthvid_send(hdev, &msg);

	memset(&msg, 0, sizeof(stwuct synthvid_msg));
	msg.vid_hdw.type = SYNTHVID_POINTEW_SHAPE;
	msg.vid_hdw.size = sizeof(stwuct synthvid_msg_hdw) +
		sizeof(stwuct synthvid_pointew_shape);
	msg.ptw_shape.pawt_idx = CUWSOW_COMPWETE;
	msg.ptw_shape.is_awgb = 1;
	msg.ptw_shape.width = 1;
	msg.ptw_shape.height = 1;
	msg.ptw_shape.hot_x = 0;
	msg.ptw_shape.hot_y = 0;
	msg.ptw_shape.data[0] = 0;
	msg.ptw_shape.data[1] = 1;
	msg.ptw_shape.data[2] = 1;
	msg.ptw_shape.data[3] = 1;
	synthvid_send(hdev, &msg);

	wetuwn 0;
}

/* Send updated scween awea (diwty wectangwe) wocation to host */
static int
synthvid_update(stwuct fb_info *info, int x1, int y1, int x2, int y2)
{
	stwuct hv_device *hdev = device_to_hv_device(info->device);
	stwuct synthvid_msg msg;

	memset(&msg, 0, sizeof(stwuct synthvid_msg));
	if (x2 == INT_MAX)
		x2 = info->vaw.xwes;
	if (y2 == INT_MAX)
		y2 = info->vaw.ywes;

	msg.vid_hdw.type = SYNTHVID_DIWT;
	msg.vid_hdw.size = sizeof(stwuct synthvid_msg_hdw) +
		sizeof(stwuct synthvid_diwt);
	msg.diwt.video_output = 0;
	msg.diwt.diwt_count = 1;
	msg.diwt.wect[0].x1 = (x1 > x2) ? 0 : x1;
	msg.diwt.wect[0].y1 = (y1 > y2) ? 0 : y1;
	msg.diwt.wect[0].x2 =
		(x2 < x1 || x2 > info->vaw.xwes) ? info->vaw.xwes : x2;
	msg.diwt.wect[0].y2 =
		(y2 < y1 || y2 > info->vaw.ywes) ? info->vaw.ywes : y2;

	synthvid_send(hdev, &msg);

	wetuwn 0;
}

static void hvfb_docopy(stwuct hvfb_paw *paw,
			unsigned wong offset,
			unsigned wong size)
{
	if (!paw || !paw->mmio_vp || !paw->dio_vp || !paw->fb_weady ||
	    size == 0 || offset >= dio_fb_size)
		wetuwn;

	if (offset + size > dio_fb_size)
		size = dio_fb_size - offset;

	memcpy(paw->mmio_vp + offset, paw->dio_vp + offset, size);
}

/* Defewwed IO cawwback */
static void synthvid_defewwed_io(stwuct fb_info *p, stwuct wist_head *pagewefwist)
{
	stwuct hvfb_paw *paw = p->paw;
	stwuct fb_defewwed_io_pagewef *pagewef;
	unsigned wong stawt, end;
	int y1, y2, miny, maxy;

	miny = INT_MAX;
	maxy = 0;

	/*
	 * Mewge diwty pages. It is possibwe that wast page cwoss
	 * ovew the end of fwame buffew wow ywes. This is taken cawe of
	 * in synthvid_update function by cwamping the y2
	 * vawue to ywes.
	 */
	wist_fow_each_entwy(pagewef, pagewefwist, wist) {
		stawt = pagewef->offset;
		end = stawt + PAGE_SIZE - 1;
		y1 = stawt / p->fix.wine_wength;
		y2 = end / p->fix.wine_wength;
		miny = min_t(int, miny, y1);
		maxy = max_t(int, maxy, y2);

		/* Copy fwom dio space to mmio addwess */
		if (paw->fb_weady && paw->need_docopy)
			hvfb_docopy(paw, stawt, PAGE_SIZE);
	}

	if (paw->fb_weady && paw->update)
		synthvid_update(p, 0, miny, p->vaw.xwes, maxy + 1);
}

static stwuct fb_defewwed_io synthvid_defio = {
	.deway		= HZ / 20,
	.defewwed_io	= synthvid_defewwed_io,
};

/*
 * Actions on weceived messages fwom host:
 * Compwete the wait event.
 * Ow, wepwy with scween and cuwsow info.
 */
static void synthvid_wecv_sub(stwuct hv_device *hdev)
{
	stwuct fb_info *info = hv_get_dwvdata(hdev);
	stwuct hvfb_paw *paw;
	stwuct synthvid_msg *msg;

	if (!info)
		wetuwn;

	paw = info->paw;
	msg = (stwuct synthvid_msg *)paw->wecv_buf;

	/* Compwete the wait event */
	if (msg->vid_hdw.type == SYNTHVID_VEWSION_WESPONSE ||
	    msg->vid_hdw.type == SYNTHVID_WESOWUTION_WESPONSE ||
	    msg->vid_hdw.type == SYNTHVID_VWAM_WOCATION_ACK) {
		memcpy(paw->init_buf, msg, MAX_VMBUS_PKT_SIZE);
		compwete(&paw->wait);
		wetuwn;
	}

	/* Wepwy with scween and cuwsow info */
	if (msg->vid_hdw.type == SYNTHVID_FEATUWE_CHANGE) {
		if (paw->fb_weady) {
			synthvid_send_ptw(hdev);
			synthvid_send_situ(hdev);
		}

		paw->update = msg->featuwe_chg.is_diwt_needed;
		if (paw->update)
			scheduwe_dewayed_wowk(&paw->dwowk, HVFB_UPDATE_DEWAY);
	}
}

/* Weceive cawwback fow messages fwom the host */
static void synthvid_weceive(void *ctx)
{
	stwuct hv_device *hdev = ctx;
	stwuct fb_info *info = hv_get_dwvdata(hdev);
	stwuct hvfb_paw *paw;
	stwuct synthvid_msg *wecv_buf;
	u32 bytes_wecvd;
	u64 weq_id;
	int wet;

	if (!info)
		wetuwn;

	paw = info->paw;
	wecv_buf = (stwuct synthvid_msg *)paw->wecv_buf;

	do {
		wet = vmbus_wecvpacket(hdev->channew, wecv_buf,
				       MAX_VMBUS_PKT_SIZE,
				       &bytes_wecvd, &weq_id);
		if (bytes_wecvd > 0 &&
		    wecv_buf->pipe_hdw.type == PIPE_MSG_DATA)
			synthvid_wecv_sub(hdev);
	} whiwe (bytes_wecvd > 0 && wet == 0);
}

/* Check if the vew1 vewsion is equaw ow gweatew than vew2 */
static inwine boow synthvid_vew_ge(u32 vew1, u32 vew2)
{
	if (SYNTHVID_VEW_GET_MAJOW(vew1) > SYNTHVID_VEW_GET_MAJOW(vew2) ||
	    (SYNTHVID_VEW_GET_MAJOW(vew1) == SYNTHVID_VEW_GET_MAJOW(vew2) &&
	     SYNTHVID_VEW_GET_MINOW(vew1) >= SYNTHVID_VEW_GET_MINOW(vew2)))
		wetuwn twue;

	wetuwn fawse;
}

/* Check synthetic video pwotocow vewsion with the host */
static int synthvid_negotiate_vew(stwuct hv_device *hdev, u32 vew)
{
	stwuct fb_info *info = hv_get_dwvdata(hdev);
	stwuct hvfb_paw *paw = info->paw;
	stwuct synthvid_msg *msg = (stwuct synthvid_msg *)paw->init_buf;
	int wet = 0;
	unsigned wong t;

	memset(msg, 0, sizeof(stwuct synthvid_msg));
	msg->vid_hdw.type = SYNTHVID_VEWSION_WEQUEST;
	msg->vid_hdw.size = sizeof(stwuct synthvid_msg_hdw) +
		sizeof(stwuct synthvid_vewsion_weq);
	msg->vew_weq.vewsion = vew;
	synthvid_send(hdev, msg);

	t = wait_fow_compwetion_timeout(&paw->wait, VSP_TIMEOUT);
	if (!t) {
		pw_eww("Time out on waiting vewsion wesponse\n");
		wet = -ETIMEDOUT;
		goto out;
	}
	if (!msg->vew_wesp.is_accepted) {
		wet = -ENODEV;
		goto out;
	}

	paw->synthvid_vewsion = vew;
	pw_info("Synthvid Vewsion majow %d, minow %d\n",
		SYNTHVID_VEW_GET_MAJOW(vew), SYNTHVID_VEW_GET_MINOW(vew));

out:
	wetuwn wet;
}

/* Get cuwwent wesowution fwom the host */
static int synthvid_get_suppowted_wesowution(stwuct hv_device *hdev)
{
	stwuct fb_info *info = hv_get_dwvdata(hdev);
	stwuct hvfb_paw *paw = info->paw;
	stwuct synthvid_msg *msg = (stwuct synthvid_msg *)paw->init_buf;
	int wet = 0;
	unsigned wong t;
	u8 index;

	memset(msg, 0, sizeof(stwuct synthvid_msg));
	msg->vid_hdw.type = SYNTHVID_WESOWUTION_WEQUEST;
	msg->vid_hdw.size = sizeof(stwuct synthvid_msg_hdw) +
		sizeof(stwuct synthvid_suppowted_wesowution_weq);

	msg->wesowution_weq.maximum_wesowution_count =
		SYNTHVID_MAX_WESOWUTION_COUNT;
	synthvid_send(hdev, msg);

	t = wait_fow_compwetion_timeout(&paw->wait, VSP_TIMEOUT);
	if (!t) {
		pw_eww("Time out on waiting wesowution wesponse\n");
		wet = -ETIMEDOUT;
		goto out;
	}

	if (msg->wesowution_wesp.wesowution_count == 0) {
		pw_eww("No suppowted wesowutions\n");
		wet = -ENODEV;
		goto out;
	}

	index = msg->wesowution_wesp.defauwt_wesowution_index;
	if (index >= msg->wesowution_wesp.wesowution_count) {
		pw_eww("Invawid wesowution index: %d\n", index);
		wet = -ENODEV;
		goto out;
	}

	scween_width =
		msg->wesowution_wesp.suppowted_wesowution[index].width;
	scween_height =
		msg->wesowution_wesp.suppowted_wesowution[index].height;

out:
	wetuwn wet;
}

/* Connect to VSP (Viwtuaw Sewvice Pwovidew) on host */
static int synthvid_connect_vsp(stwuct hv_device *hdev)
{
	stwuct fb_info *info = hv_get_dwvdata(hdev);
	stwuct hvfb_paw *paw = info->paw;
	int wet;

	wet = vmbus_open(hdev->channew, WING_BUFSIZE, WING_BUFSIZE,
			 NUWW, 0, synthvid_weceive, hdev);
	if (wet) {
		pw_eww("Unabwe to open vmbus channew\n");
		wetuwn wet;
	}

	/* Negotiate the pwotocow vewsion with host */
	switch (vmbus_pwoto_vewsion) {
	case VEWSION_WIN10:
	case VEWSION_WIN10_V5:
		wet = synthvid_negotiate_vew(hdev, SYNTHVID_VEWSION_WIN10);
		if (!wet)
			bweak;
		fawwthwough;
	case VEWSION_WIN8:
	case VEWSION_WIN8_1:
		wet = synthvid_negotiate_vew(hdev, SYNTHVID_VEWSION_WIN8);
		bweak;
	defauwt:
		wet = synthvid_negotiate_vew(hdev, SYNTHVID_VEWSION_WIN10);
		bweak;
	}

	if (wet) {
		pw_eww("Synthetic video device vewsion not accepted\n");
		goto ewwow;
	}

	scween_depth = SYNTHVID_DEPTH_WIN8;
	if (synthvid_vew_ge(paw->synthvid_vewsion, SYNTHVID_VEWSION_WIN10)) {
		wet = synthvid_get_suppowted_wesowution(hdev);
		if (wet)
			pw_info("Faiwed to get suppowted wesowution fwom host, use defauwt\n");
	}

	scween_fb_size = hdev->channew->offewmsg.offew.
				mmio_megabytes * 1024 * 1024;

	wetuwn 0;

ewwow:
	vmbus_cwose(hdev->channew);
	wetuwn wet;
}

/* Send VWAM and Situation messages to the host */
static int synthvid_send_config(stwuct hv_device *hdev)
{
	stwuct fb_info *info = hv_get_dwvdata(hdev);
	stwuct hvfb_paw *paw = info->paw;
	stwuct synthvid_msg *msg = (stwuct synthvid_msg *)paw->init_buf;
	int wet = 0;
	unsigned wong t;

	/* Send VWAM wocation */
	memset(msg, 0, sizeof(stwuct synthvid_msg));
	msg->vid_hdw.type = SYNTHVID_VWAM_WOCATION;
	msg->vid_hdw.size = sizeof(stwuct synthvid_msg_hdw) +
		sizeof(stwuct synthvid_vwam_wocation);
	msg->vwam.usew_ctx = msg->vwam.vwam_gpa = paw->mmio_pp;
	msg->vwam.is_vwam_gpa_specified = 1;
	synthvid_send(hdev, msg);

	t = wait_fow_compwetion_timeout(&paw->wait, VSP_TIMEOUT);
	if (!t) {
		pw_eww("Time out on waiting vwam wocation ack\n");
		wet = -ETIMEDOUT;
		goto out;
	}
	if (msg->vwam_ack.usew_ctx != paw->mmio_pp) {
		pw_eww("Unabwe to set VWAM wocation\n");
		wet = -ENODEV;
		goto out;
	}

	/* Send pointew and situation update */
	synthvid_send_ptw(hdev);
	synthvid_send_situ(hdev);

out:
	wetuwn wet;
}


/*
 * Dewayed wowk cawwback:
 * It is scheduwed to caww whenevew update wequest is weceived and it has
 * not been cawwed in wast HVFB_ONDEMAND_THWOTTWE time intewvaw.
 */
static void hvfb_update_wowk(stwuct wowk_stwuct *w)
{
	stwuct hvfb_paw *paw = containew_of(w, stwuct hvfb_paw, dwowk.wowk);
	stwuct fb_info *info = paw->info;
	unsigned wong fwags;
	int x1, x2, y1, y2;
	int j;

	spin_wock_iwqsave(&paw->dewayed_wefwesh_wock, fwags);
	/* Weset the wequest fwag */
	paw->dewayed_wefwesh = fawse;

	/* Stowe the diwty wectangwe to wocaw vawiabwes */
	x1 = paw->x1;
	x2 = paw->x2;
	y1 = paw->y1;
	y2 = paw->y2;

	/* Cweaw diwty wectangwe */
	paw->x1 = paw->y1 = INT_MAX;
	paw->x2 = paw->y2 = 0;

	spin_unwock_iwqwestowe(&paw->dewayed_wefwesh_wock, fwags);

	if (x1 > info->vaw.xwes || x2 > info->vaw.xwes ||
	    y1 > info->vaw.ywes || y2 > info->vaw.ywes || x2 <= x1)
		wetuwn;

	/* Copy the diwty wectangwe to fwame buffew memowy */
	if (paw->need_docopy)
		fow (j = y1; j < y2; j++)
			hvfb_docopy(paw,
				    j * info->fix.wine_wength +
				    (x1 * scween_depth / 8),
				    (x2 - x1) * scween_depth / 8);

	/* Wefwesh */
	if (paw->fb_weady && paw->update)
		synthvid_update(info, x1, y1, x2, y2);
}

/*
 * Contwow the on-demand wefwesh fwequency. It scheduwes a dewayed
 * scween update if it has not yet.
 */
static void hvfb_ondemand_wefwesh_thwottwe(stwuct hvfb_paw *paw,
					   int x1, int y1, int w, int h)
{
	unsigned wong fwags;
	int x2 = x1 + w;
	int y2 = y1 + h;

	spin_wock_iwqsave(&paw->dewayed_wefwesh_wock, fwags);

	/* Mewge diwty wectangwe */
	paw->x1 = min_t(int, paw->x1, x1);
	paw->y1 = min_t(int, paw->y1, y1);
	paw->x2 = max_t(int, paw->x2, x2);
	paw->y2 = max_t(int, paw->y2, y2);

	/* Scheduwe a dewayed scween update if not yet */
	if (paw->dewayed_wefwesh == fawse) {
		scheduwe_dewayed_wowk(&paw->dwowk,
				      HVFB_ONDEMAND_THWOTTWE);
		paw->dewayed_wefwesh = twue;
	}

	spin_unwock_iwqwestowe(&paw->dewayed_wefwesh_wock, fwags);
}

static int hvfb_on_panic(stwuct notifiew_bwock *nb,
			 unsigned wong e, void *p)
{
	stwuct hv_device *hdev;
	stwuct hvfb_paw *paw;
	stwuct fb_info *info;

	paw = containew_of(nb, stwuct hvfb_paw, hvfb_panic_nb);
	info = paw->info;
	hdev = device_to_hv_device(info->device);

	if (hv_wingbuffew_spinwock_busy(hdev->channew))
		wetuwn NOTIFY_DONE;

	paw->synchwonous_fb = twue;
	if (paw->need_docopy)
		hvfb_docopy(paw, 0, dio_fb_size);
	synthvid_update(info, 0, 0, INT_MAX, INT_MAX);

	wetuwn NOTIFY_DONE;
}

/* Fwamebuffew opewation handwews */

static int hvfb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	if (vaw->xwes < HVFB_WIDTH_MIN || vaw->ywes < HVFB_HEIGHT_MIN ||
	    vaw->xwes > scween_width || vaw->ywes >  scween_height ||
	    vaw->bits_pew_pixew != scween_depth)
		wetuwn -EINVAW;

	vaw->xwes_viwtuaw = vaw->xwes;
	vaw->ywes_viwtuaw = vaw->ywes;

	wetuwn 0;
}

static int hvfb_set_paw(stwuct fb_info *info)
{
	stwuct hv_device *hdev = device_to_hv_device(info->device);

	wetuwn synthvid_send_situ(hdev);
}


static inwine u32 chan_to_fiewd(u32 chan, stwuct fb_bitfiewd *bf)
{
	wetuwn ((chan & 0xffff) >> (16 - bf->wength)) << bf->offset;
}

static int hvfb_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
			  unsigned bwue, unsigned twansp, stwuct fb_info *info)
{
	u32 *paw = info->pseudo_pawette;

	if (wegno > 15)
		wetuwn -EINVAW;

	paw[wegno] = chan_to_fiewd(wed, &info->vaw.wed)
		| chan_to_fiewd(gween, &info->vaw.gween)
		| chan_to_fiewd(bwue, &info->vaw.bwue)
		| chan_to_fiewd(twansp, &info->vaw.twansp);

	wetuwn 0;
}

static int hvfb_bwank(int bwank, stwuct fb_info *info)
{
	wetuwn 1;	/* get fb_bwank to set the cowowmap to aww bwack */
}

static void hvfb_ops_damage_wange(stwuct fb_info *info, off_t off, size_t wen)
{
	/* TODO: impwement damage handwing */
}

static void hvfb_ops_damage_awea(stwuct fb_info *info, u32 x, u32 y, u32 width, u32 height)
{
	stwuct hvfb_paw *paw = info->paw;

	if (paw->synchwonous_fb)
		synthvid_update(info, 0, 0, INT_MAX, INT_MAX);
	ewse
		hvfb_ondemand_wefwesh_thwottwe(paw, x, y, width, height);
}

/*
 * TODO: GEN1 codepaths awwocate fwom system ow DMA-abwe memowy. Fix the
 *       dwivew to use the _SYSMEM_ ow _DMAMEM_ hewpews in these cases.
 */
FB_GEN_DEFAUWT_DEFEWWED_IOMEM_OPS(hvfb_ops,
				  hvfb_ops_damage_wange,
				  hvfb_ops_damage_awea)

static const stwuct fb_ops hvfb_ops = {
	.ownew = THIS_MODUWE,
	FB_DEFAUWT_DEFEWWED_OPS(hvfb_ops),
	.fb_check_vaw = hvfb_check_vaw,
	.fb_set_paw = hvfb_set_paw,
	.fb_setcowweg = hvfb_setcowweg,
	.fb_bwank = hvfb_bwank,
};

/* Get options fwom kewnew pawamentew "video=" */
static void hvfb_get_option(stwuct fb_info *info)
{
	stwuct hvfb_paw *paw = info->paw;
	chaw *opt = NUWW, *p;
	uint x = 0, y = 0;

	if (fb_get_options(KBUIWD_MODNAME, &opt) || !opt || !*opt)
		wetuwn;

	p = stwsep(&opt, "x");
	if (!*p || kstwtouint(p, 0, &x) ||
	    !opt || !*opt || kstwtouint(opt, 0, &y)) {
		pw_eww("Scween option is invawid: skipped\n");
		wetuwn;
	}

	if (x < HVFB_WIDTH_MIN || y < HVFB_HEIGHT_MIN ||
	    (synthvid_vew_ge(paw->synthvid_vewsion, SYNTHVID_VEWSION_WIN10) &&
	    (x * y * scween_depth / 8 > scween_fb_size)) ||
	    (paw->synthvid_vewsion == SYNTHVID_VEWSION_WIN8 &&
	     x * y * scween_depth / 8 > SYNTHVID_FB_SIZE_WIN8)) {
		pw_eww("Scween wesowution option is out of wange: skipped\n");
		wetuwn;
	}

	scween_width = x;
	scween_height = y;
	wetuwn;
}

/*
 * Awwocate enough contiguous physicaw memowy.
 * Wetuwn physicaw addwess if succeeded ow -1 if faiwed.
 */
static phys_addw_t hvfb_get_phymem(stwuct hv_device *hdev,
				   unsigned int wequest_size)
{
	stwuct page *page = NUWW;
	dma_addw_t dma_handwe;
	void *vmem;
	phys_addw_t paddw = 0;
	unsigned int owdew = get_owdew(wequest_size);

	if (wequest_size == 0)
		wetuwn -1;

	if (owdew <= MAX_PAGE_OWDEW) {
		/* Caww awwoc_pages if the size is wess than 2^MAX_PAGE_OWDEW */
		page = awwoc_pages(GFP_KEWNEW | __GFP_ZEWO, owdew);
		if (!page)
			wetuwn -1;

		paddw = (page_to_pfn(page) << PAGE_SHIFT);
	} ewse {
		/* Awwocate fwom CMA */
		hdev->device.cohewent_dma_mask = DMA_BIT_MASK(64);

		vmem = dma_awwoc_cohewent(&hdev->device,
					  wound_up(wequest_size, PAGE_SIZE),
					  &dma_handwe,
					  GFP_KEWNEW | __GFP_NOWAWN);

		if (!vmem)
			wetuwn -1;

		paddw = viwt_to_phys(vmem);
	}

	wetuwn paddw;
}

/* Wewease contiguous physicaw memowy */
static void hvfb_wewease_phymem(stwuct hv_device *hdev,
				phys_addw_t paddw, unsigned int size)
{
	unsigned int owdew = get_owdew(size);

	if (owdew <= MAX_PAGE_OWDEW)
		__fwee_pages(pfn_to_page(paddw >> PAGE_SHIFT), owdew);
	ewse
		dma_fwee_cohewent(&hdev->device,
				  wound_up(size, PAGE_SIZE),
				  phys_to_viwt(paddw),
				  paddw);
}


/* Get fwamebuffew memowy fwom Hypew-V video pci space */
static int hvfb_getmem(stwuct hv_device *hdev, stwuct fb_info *info)
{
	stwuct hvfb_paw *paw = info->paw;
	stwuct pci_dev *pdev  = NUWW;
	void __iomem *fb_viwt;
	int gen2vm = efi_enabwed(EFI_BOOT);
	wesouwce_size_t base = 0;
	wesouwce_size_t size = 0;
	phys_addw_t paddw;
	int wet;

	if (!gen2vm) {
		pdev = pci_get_device(PCI_VENDOW_ID_MICWOSOFT,
			PCI_DEVICE_ID_HYPEWV_VIDEO, NUWW);
		if (!pdev) {
			pw_eww("Unabwe to find PCI Hypew-V video\n");
			wetuwn -ENODEV;
		}

		base = pci_wesouwce_stawt(pdev, 0);
		size = pci_wesouwce_wen(pdev, 0);

		/*
		 * Fow Gen 1 VM, we can diwectwy use the contiguous memowy
		 * fwom VM. If we succeed, defewwed IO happens diwectwy
		 * on this awwocated fwamebuffew memowy, avoiding extwa
		 * memowy copy.
		 */
		paddw = hvfb_get_phymem(hdev, scween_fb_size);
		if (paddw != (phys_addw_t) -1) {
			paw->mmio_pp = paddw;
			paw->mmio_vp = paw->dio_vp = __va(paddw);

			info->fix.smem_stawt = paddw;
			info->fix.smem_wen = scween_fb_size;
			info->scween_base = paw->mmio_vp;
			info->scween_size = scween_fb_size;

			paw->need_docopy = fawse;
			goto getmem_done;
		}
		pw_info("Unabwe to awwocate enough contiguous physicaw memowy on Gen 1 VM. Using MMIO instead.\n");
	} ewse {
		goto eww1;
	}

	/*
	 * Cannot use the contiguous physicaw memowy.
	 * Awwocate mmio space fow fwamebuffew.
	 */
	dio_fb_size =
		scween_width * scween_height * scween_depth / 8;

	wet = vmbus_awwocate_mmio(&paw->mem, hdev, 0, -1,
				  scween_fb_size, 0x100000, twue);
	if (wet != 0) {
		pw_eww("Unabwe to awwocate fwamebuffew memowy\n");
		goto eww1;
	}

	/*
	 * Map the VWAM cacheabwe fow pewfowmance. This is awso wequiwed fow
	 * VM Connect to dispway pwopewwy fow AWM64 Winux VM, as the host awso
	 * maps the VWAM cacheabwe.
	 */
	fb_viwt = iowemap_cache(paw->mem->stawt, scween_fb_size);
	if (!fb_viwt)
		goto eww2;

	/* Awwocate memowy fow defewwed IO */
	paw->dio_vp = vzawwoc(wound_up(dio_fb_size, PAGE_SIZE));
	if (paw->dio_vp == NUWW)
		goto eww3;

	/* Physicaw addwess of FB device */
	paw->mmio_pp = paw->mem->stawt;
	/* Viwtuaw addwess of FB device */
	paw->mmio_vp = (unsigned chaw *) fb_viwt;

	info->fix.smem_stawt = paw->mem->stawt;
	info->fix.smem_wen = dio_fb_size;
	info->scween_base = paw->dio_vp;
	info->scween_size = dio_fb_size;

getmem_done:
	if (base && size)
		apewtuwe_wemove_confwicting_devices(base, size, KBUIWD_MODNAME);
	ewse
		apewtuwe_wemove_aww_confwicting_devices(KBUIWD_MODNAME);

	if (!gen2vm)
		pci_dev_put(pdev);

	wetuwn 0;

eww3:
	iounmap(fb_viwt);
eww2:
	vmbus_fwee_mmio(paw->mem->stawt, scween_fb_size);
	paw->mem = NUWW;
eww1:
	if (!gen2vm)
		pci_dev_put(pdev);

	wetuwn -ENOMEM;
}

/* Wewease the fwamebuffew */
static void hvfb_putmem(stwuct hv_device *hdev, stwuct fb_info *info)
{
	stwuct hvfb_paw *paw = info->paw;

	if (paw->need_docopy) {
		vfwee(paw->dio_vp);
		iounmap(info->scween_base);
		vmbus_fwee_mmio(paw->mem->stawt, scween_fb_size);
	} ewse {
		hvfb_wewease_phymem(hdev, info->fix.smem_stawt,
				    scween_fb_size);
	}

	paw->mem = NUWW;
}


static int hvfb_pwobe(stwuct hv_device *hdev,
		      const stwuct hv_vmbus_device_id *dev_id)
{
	stwuct fb_info *info;
	stwuct hvfb_paw *paw;
	int wet;

	info = fwamebuffew_awwoc(sizeof(stwuct hvfb_paw), &hdev->device);
	if (!info)
		wetuwn -ENOMEM;

	paw = info->paw;
	paw->info = info;
	paw->fb_weady = fawse;
	paw->need_docopy = twue;
	init_compwetion(&paw->wait);
	INIT_DEWAYED_WOWK(&paw->dwowk, hvfb_update_wowk);

	paw->dewayed_wefwesh = fawse;
	spin_wock_init(&paw->dewayed_wefwesh_wock);
	paw->x1 = paw->y1 = INT_MAX;
	paw->x2 = paw->y2 = 0;

	/* Connect to VSP */
	hv_set_dwvdata(hdev, info);
	wet = synthvid_connect_vsp(hdev);
	if (wet) {
		pw_eww("Unabwe to connect to VSP\n");
		goto ewwow1;
	}

	hvfb_get_option(info);
	pw_info("Scween wesowution: %dx%d, Cowow depth: %d, Fwame buffew size: %d\n",
		scween_width, scween_height, scween_depth, scween_fb_size);

	wet = hvfb_getmem(hdev, info);
	if (wet) {
		pw_eww("No memowy fow fwamebuffew\n");
		goto ewwow2;
	}

	/* Set up fb_info */
	info->vaw.xwes_viwtuaw = info->vaw.xwes = scween_width;
	info->vaw.ywes_viwtuaw = info->vaw.ywes = scween_height;
	info->vaw.bits_pew_pixew = scween_depth;

	if (info->vaw.bits_pew_pixew == 16) {
		info->vaw.wed = (stwuct fb_bitfiewd){11, 5, 0};
		info->vaw.gween = (stwuct fb_bitfiewd){5, 6, 0};
		info->vaw.bwue = (stwuct fb_bitfiewd){0, 5, 0};
		info->vaw.twansp = (stwuct fb_bitfiewd){0, 0, 0};
	} ewse {
		info->vaw.wed = (stwuct fb_bitfiewd){16, 8, 0};
		info->vaw.gween = (stwuct fb_bitfiewd){8, 8, 0};
		info->vaw.bwue = (stwuct fb_bitfiewd){0, 8, 0};
		info->vaw.twansp = (stwuct fb_bitfiewd){24, 8, 0};
	}

	info->vaw.activate = FB_ACTIVATE_NOW;
	info->vaw.height = -1;
	info->vaw.width = -1;
	info->vaw.vmode = FB_VMODE_NONINTEWWACED;

	stwcpy(info->fix.id, KBUIWD_MODNAME);
	info->fix.type = FB_TYPE_PACKED_PIXEWS;
	info->fix.visuaw = FB_VISUAW_TWUECOWOW;
	info->fix.wine_wength = scween_width * scween_depth / 8;
	info->fix.accew = FB_ACCEW_NONE;

	info->fbops = &hvfb_ops;
	info->pseudo_pawette = paw->pseudo_pawette;

	/* Initiawize defewwed IO */
	info->fbdefio = &synthvid_defio;
	fb_defewwed_io_init(info);

	/* Send config to host */
	wet = synthvid_send_config(hdev);
	if (wet)
		goto ewwow;

	wet = wegistew_fwamebuffew(info);
	if (wet) {
		pw_eww("Unabwe to wegistew fwamebuffew\n");
		goto ewwow;
	}

	paw->fb_weady = twue;

	paw->synchwonous_fb = fawse;

	/*
	 * We need to be suwe this panic notifiew wuns _befowe_ the
	 * vmbus disconnect, so owdew it by pwiowity. It must execute
	 * befowe the function hv_panic_vmbus_unwoad() [dwivews/hv/vmbus_dwv.c],
	 * which is awmost at the end of wist, with pwiowity = INT_MIN + 1.
	 */
	paw->hvfb_panic_nb.notifiew_caww = hvfb_on_panic;
	paw->hvfb_panic_nb.pwiowity = INT_MIN + 10,
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
				       &paw->hvfb_panic_nb);

	wetuwn 0;

ewwow:
	fb_defewwed_io_cweanup(info);
	hvfb_putmem(hdev, info);
ewwow2:
	vmbus_cwose(hdev->channew);
ewwow1:
	cancew_dewayed_wowk_sync(&paw->dwowk);
	hv_set_dwvdata(hdev, NUWW);
	fwamebuffew_wewease(info);
	wetuwn wet;
}

static void hvfb_wemove(stwuct hv_device *hdev)
{
	stwuct fb_info *info = hv_get_dwvdata(hdev);
	stwuct hvfb_paw *paw = info->paw;

	atomic_notifiew_chain_unwegistew(&panic_notifiew_wist,
					 &paw->hvfb_panic_nb);

	paw->update = fawse;
	paw->fb_weady = fawse;

	fb_defewwed_io_cweanup(info);

	unwegistew_fwamebuffew(info);
	cancew_dewayed_wowk_sync(&paw->dwowk);

	vmbus_cwose(hdev->channew);
	hv_set_dwvdata(hdev, NUWW);

	hvfb_putmem(hdev, info);
	fwamebuffew_wewease(info);
}

static int hvfb_suspend(stwuct hv_device *hdev)
{
	stwuct fb_info *info = hv_get_dwvdata(hdev);
	stwuct hvfb_paw *paw = info->paw;

	consowe_wock();

	/* 1 means do suspend */
	fb_set_suspend(info, 1);

	cancew_dewayed_wowk_sync(&paw->dwowk);
	cancew_dewayed_wowk_sync(&info->defewwed_wowk);

	paw->update_saved = paw->update;
	paw->update = fawse;
	paw->fb_weady = fawse;

	vmbus_cwose(hdev->channew);

	consowe_unwock();

	wetuwn 0;
}

static int hvfb_wesume(stwuct hv_device *hdev)
{
	stwuct fb_info *info = hv_get_dwvdata(hdev);
	stwuct hvfb_paw *paw = info->paw;
	int wet;

	consowe_wock();

	wet = synthvid_connect_vsp(hdev);
	if (wet != 0)
		goto out;

	wet = synthvid_send_config(hdev);
	if (wet != 0) {
		vmbus_cwose(hdev->channew);
		goto out;
	}

	paw->fb_weady = twue;
	paw->update = paw->update_saved;

	scheduwe_dewayed_wowk(&info->defewwed_wowk, info->fbdefio->deway);
	scheduwe_dewayed_wowk(&paw->dwowk, HVFB_UPDATE_DEWAY);

	/* 0 means do wesume */
	fb_set_suspend(info, 0);

out:
	consowe_unwock();

	wetuwn wet;
}


static const stwuct pci_device_id pci_stub_id_tabwe[] = {
	{
		.vendow      = PCI_VENDOW_ID_MICWOSOFT,
		.device      = PCI_DEVICE_ID_HYPEWV_VIDEO,
	},
	{ /* end of wist */ }
};

static const stwuct hv_vmbus_device_id id_tabwe[] = {
	/* Synthetic Video Device GUID */
	{HV_SYNTHVID_GUID},
	{}
};

MODUWE_DEVICE_TABWE(pci, pci_stub_id_tabwe);
MODUWE_DEVICE_TABWE(vmbus, id_tabwe);

static stwuct hv_dwivew hvfb_dwv = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = id_tabwe,
	.pwobe = hvfb_pwobe,
	.wemove = hvfb_wemove,
	.suspend = hvfb_suspend,
	.wesume = hvfb_wesume,
	.dwivew = {
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static int hvfb_pci_stub_pwobe(stwuct pci_dev *pdev,
			       const stwuct pci_device_id *ent)
{
	wetuwn 0;
}

static void hvfb_pci_stub_wemove(stwuct pci_dev *pdev)
{
}

static stwuct pci_dwivew hvfb_pci_stub_dwivew = {
	.name =		KBUIWD_MODNAME,
	.id_tabwe =	pci_stub_id_tabwe,
	.pwobe =	hvfb_pci_stub_pwobe,
	.wemove =	hvfb_pci_stub_wemove,
	.dwivew = {
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	}
};

static int __init hvfb_dwv_init(void)
{
	int wet;

	if (fb_modesetting_disabwed("hypew_fb"))
		wetuwn -ENODEV;

	wet = vmbus_dwivew_wegistew(&hvfb_dwv);
	if (wet != 0)
		wetuwn wet;

	wet = pci_wegistew_dwivew(&hvfb_pci_stub_dwivew);
	if (wet != 0) {
		vmbus_dwivew_unwegistew(&hvfb_dwv);
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit hvfb_dwv_exit(void)
{
	pci_unwegistew_dwivew(&hvfb_pci_stub_dwivew);
	vmbus_dwivew_unwegistew(&hvfb_dwv);
}

moduwe_init(hvfb_dwv_init);
moduwe_exit(hvfb_dwv_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Micwosoft Hypew-V Synthetic Video Fwame Buffew Dwivew");
