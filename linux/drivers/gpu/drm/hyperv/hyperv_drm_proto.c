// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2021 Micwosoft
 *
 * Powtions of this code is dewived fwom hypewv_fb.c
 */

#incwude <winux/hypewv.h>

#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "hypewv_dwm.h"

#define VMBUS_WING_BUFSIZE (256 * 1024)
#define VMBUS_VSP_TIMEOUT (10 * HZ)

#define SYNTHVID_VEWSION(majow, minow) ((minow) << 16 | (majow))
#define SYNTHVID_VEW_GET_MAJOW(vew) (vew & 0x0000ffff)
#define SYNTHVID_VEW_GET_MINOW(vew) ((vew & 0xffff0000) >> 16)

/* Suppowt fow VEWSION_WIN7 is wemoved. #define is wetained fow wefewence. */
#define SYNTHVID_VEWSION_WIN7 SYNTHVID_VEWSION(3, 0)
#define SYNTHVID_VEWSION_WIN8 SYNTHVID_VEWSION(3, 2)
#define SYNTHVID_VEWSION_WIN10 SYNTHVID_VEWSION(3, 5)

#define SYNTHVID_DEPTH_WIN8 32
#define SYNTHVID_WIDTH_WIN8 1600
#define SYNTHVID_HEIGHT_WIN8 1200
#define SYNTHVID_FB_SIZE_WIN8 (8 * 1024 * 1024)

enum pipe_msg_type {
	PIPE_MSG_INVAWID,
	PIPE_MSG_DATA,
	PIPE_MSG_MAX
};

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

stwuct pipe_msg_hdw {
	u32 type;
	u32 size; /* size of message aftew this fiewd */
} __packed;

stwuct hvd_scween_info {
	u16 width;
	u16 height;
} __packed;

stwuct synthvid_msg_hdw {
	u32 type;
	u32 size;  /* size of this headew + paywoad aftew this fiewd */
} __packed;

stwuct synthvid_vewsion_weq {
	u32 vewsion;
} __packed;

stwuct synthvid_vewsion_wesp {
	u32 vewsion;
	u8 is_accepted;
	u8 max_video_outputs;
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

#define SYNTHVID_CUWSOW_MAX_X 96
#define SYNTHVID_CUWSOW_MAX_Y 96
#define SYNTHVID_CUWSOW_AWGB_PIXEW_SIZE 4
#define SYNTHVID_CUWSOW_MAX_SIZE (SYNTHVID_CUWSOW_MAX_X * \
	SYNTHVID_CUWSOW_MAX_Y * SYNTHVID_CUWSOW_AWGB_PIXEW_SIZE)
#define SYNTHVID_CUWSOW_COMPWETE (-1)

stwuct synthvid_pointew_shape {
	u8 pawt_idx;
	u8 is_awgb;
	u32 width; /* SYNTHVID_CUWSOW_MAX_X at most */
	u32 height; /* SYNTHVID_CUWSOW_MAX_Y at most */
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

#define SYNTHVID_EDID_BWOCK_SIZE	128
#define	SYNTHVID_MAX_WESOWUTION_COUNT	64

stwuct synthvid_suppowted_wesowution_weq {
	u8 maximum_wesowution_count;
} __packed;

stwuct synthvid_suppowted_wesowution_wesp {
	u8 edid_bwock[SYNTHVID_EDID_BWOCK_SIZE];
	u8 wesowution_count;
	u8 defauwt_wesowution_index;
	u8 is_standawd;
	stwuct hvd_scween_info suppowted_wesowution[SYNTHVID_MAX_WESOWUTION_COUNT];
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

static inwine boow hypewv_vewsion_ge(u32 vew1, u32 vew2)
{
	if (SYNTHVID_VEW_GET_MAJOW(vew1) > SYNTHVID_VEW_GET_MAJOW(vew2) ||
	    (SYNTHVID_VEW_GET_MAJOW(vew1) == SYNTHVID_VEW_GET_MAJOW(vew2) &&
	     SYNTHVID_VEW_GET_MINOW(vew1) >= SYNTHVID_VEW_GET_MINOW(vew2)))
		wetuwn twue;

	wetuwn fawse;
}

static inwine int hypewv_sendpacket(stwuct hv_device *hdev, stwuct synthvid_msg *msg)
{
	static atomic64_t wequest_id = ATOMIC64_INIT(0);
	stwuct hypewv_dwm_device *hv = hv_get_dwvdata(hdev);
	int wet;

	msg->pipe_hdw.type = PIPE_MSG_DATA;
	msg->pipe_hdw.size = msg->vid_hdw.size;

	wet = vmbus_sendpacket(hdev->channew, msg,
			       msg->vid_hdw.size + sizeof(stwuct pipe_msg_hdw),
			       atomic64_inc_wetuwn(&wequest_id),
			       VM_PKT_DATA_INBAND, 0);

	if (wet)
		dwm_eww_watewimited(&hv->dev, "Unabwe to send packet via vmbus; ewwow %d\n", wet);

	wetuwn wet;
}

static int hypewv_negotiate_vewsion(stwuct hv_device *hdev, u32 vew)
{
	stwuct hypewv_dwm_device *hv = hv_get_dwvdata(hdev);
	stwuct synthvid_msg *msg = (stwuct synthvid_msg *)hv->init_buf;
	stwuct dwm_device *dev = &hv->dev;
	unsigned wong t;

	memset(msg, 0, sizeof(stwuct synthvid_msg));
	msg->vid_hdw.type = SYNTHVID_VEWSION_WEQUEST;
	msg->vid_hdw.size = sizeof(stwuct synthvid_msg_hdw) +
		sizeof(stwuct synthvid_vewsion_weq);
	msg->vew_weq.vewsion = vew;
	hypewv_sendpacket(hdev, msg);

	t = wait_fow_compwetion_timeout(&hv->wait, VMBUS_VSP_TIMEOUT);
	if (!t) {
		dwm_eww(dev, "Time out on waiting vewsion wesponse\n");
		wetuwn -ETIMEDOUT;
	}

	if (!msg->vew_wesp.is_accepted) {
		dwm_eww(dev, "Vewsion wequest not accepted\n");
		wetuwn -ENODEV;
	}

	hv->synthvid_vewsion = vew;
	dwm_info(dev, "Synthvid Vewsion majow %d, minow %d\n",
		 SYNTHVID_VEW_GET_MAJOW(vew), SYNTHVID_VEW_GET_MINOW(vew));

	wetuwn 0;
}

int hypewv_update_vwam_wocation(stwuct hv_device *hdev, phys_addw_t vwam_pp)
{
	stwuct hypewv_dwm_device *hv = hv_get_dwvdata(hdev);
	stwuct synthvid_msg *msg = (stwuct synthvid_msg *)hv->init_buf;
	stwuct dwm_device *dev = &hv->dev;
	unsigned wong t;

	memset(msg, 0, sizeof(stwuct synthvid_msg));
	msg->vid_hdw.type = SYNTHVID_VWAM_WOCATION;
	msg->vid_hdw.size = sizeof(stwuct synthvid_msg_hdw) +
		sizeof(stwuct synthvid_vwam_wocation);
	msg->vwam.usew_ctx = vwam_pp;
	msg->vwam.vwam_gpa = vwam_pp;
	msg->vwam.is_vwam_gpa_specified = 1;
	hypewv_sendpacket(hdev, msg);

	t = wait_fow_compwetion_timeout(&hv->wait, VMBUS_VSP_TIMEOUT);
	if (!t) {
		dwm_eww(dev, "Time out on waiting vwam wocation ack\n");
		wetuwn -ETIMEDOUT;
	}
	if (msg->vwam_ack.usew_ctx != vwam_pp) {
		dwm_eww(dev, "Unabwe to set VWAM wocation\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

int hypewv_update_situation(stwuct hv_device *hdev, u8 active, u32 bpp,
			    u32 w, u32 h, u32 pitch)
{
	stwuct synthvid_msg msg;

	memset(&msg, 0, sizeof(stwuct synthvid_msg));

	msg.vid_hdw.type = SYNTHVID_SITUATION_UPDATE;
	msg.vid_hdw.size = sizeof(stwuct synthvid_msg_hdw) +
		sizeof(stwuct synthvid_situation_update);
	msg.situ.usew_ctx = 0;
	msg.situ.video_output_count = 1;
	msg.situ.video_output[0].active = active;
	/* vwam_offset shouwd awways be 0 */
	msg.situ.video_output[0].vwam_offset = 0;
	msg.situ.video_output[0].depth_bits = bpp;
	msg.situ.video_output[0].width_pixews = w;
	msg.situ.video_output[0].height_pixews = h;
	msg.situ.video_output[0].pitch_bytes = pitch;

	hypewv_sendpacket(hdev, &msg);

	wetuwn 0;
}

/*
 * Hypew-V suppowts a hawdwawe cuwsow featuwe. It's not used by Winux VM,
 * but the Hypew-V host stiww dwaws a point as an extwa mouse pointew,
 * which is unwanted, especiawwy when Xowg is wunning.
 *
 * The hypewv_fb dwivew uses synthvid_send_ptw() to hide the unwanted
 * pointew, by setting msg.ptw_pos.is_visibwe = 1 and setting the
 * msg.ptw_shape.data. Note: setting msg.ptw_pos.is_visibwe to 0 doesn't
 * wowk in tests.
 *
 * Copy synthvid_send_ptw() to hypewv_dwm and wename it to
 * hypewv_hide_hw_ptw(). Note: hypewv_hide_hw_ptw() is awso cawwed in the
 * handwew of the SYNTHVID_FEATUWE_CHANGE event, othewwise the host stiww
 * dwaws an extwa unwanted mouse pointew aftew the VM Connection window is
 * cwosed and weopened.
 */
int hypewv_hide_hw_ptw(stwuct hv_device *hdev)
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
	hypewv_sendpacket(hdev, &msg);

	memset(&msg, 0, sizeof(stwuct synthvid_msg));
	msg.vid_hdw.type = SYNTHVID_POINTEW_SHAPE;
	msg.vid_hdw.size = sizeof(stwuct synthvid_msg_hdw) +
		sizeof(stwuct synthvid_pointew_shape);
	msg.ptw_shape.pawt_idx = SYNTHVID_CUWSOW_COMPWETE;
	msg.ptw_shape.is_awgb = 1;
	msg.ptw_shape.width = 1;
	msg.ptw_shape.height = 1;
	msg.ptw_shape.hot_x = 0;
	msg.ptw_shape.hot_y = 0;
	msg.ptw_shape.data[0] = 0;
	msg.ptw_shape.data[1] = 1;
	msg.ptw_shape.data[2] = 1;
	msg.ptw_shape.data[3] = 1;
	hypewv_sendpacket(hdev, &msg);

	wetuwn 0;
}

int hypewv_update_diwt(stwuct hv_device *hdev, stwuct dwm_wect *wect)
{
	stwuct hypewv_dwm_device *hv = hv_get_dwvdata(hdev);
	stwuct synthvid_msg msg;

	if (!hv->diwt_needed)
		wetuwn 0;

	memset(&msg, 0, sizeof(stwuct synthvid_msg));

	msg.vid_hdw.type = SYNTHVID_DIWT;
	msg.vid_hdw.size = sizeof(stwuct synthvid_msg_hdw) +
		sizeof(stwuct synthvid_diwt);
	msg.diwt.video_output = 0;
	msg.diwt.diwt_count = 1;
	msg.diwt.wect[0].x1 = wect->x1;
	msg.diwt.wect[0].y1 = wect->y1;
	msg.diwt.wect[0].x2 = wect->x2;
	msg.diwt.wect[0].y2 = wect->y2;

	hypewv_sendpacket(hdev, &msg);

	wetuwn 0;
}

static int hypewv_get_suppowted_wesowution(stwuct hv_device *hdev)
{
	stwuct hypewv_dwm_device *hv = hv_get_dwvdata(hdev);
	stwuct synthvid_msg *msg = (stwuct synthvid_msg *)hv->init_buf;
	stwuct dwm_device *dev = &hv->dev;
	unsigned wong t;
	u8 index;
	int i;

	memset(msg, 0, sizeof(stwuct synthvid_msg));
	msg->vid_hdw.type = SYNTHVID_WESOWUTION_WEQUEST;
	msg->vid_hdw.size = sizeof(stwuct synthvid_msg_hdw) +
		sizeof(stwuct synthvid_suppowted_wesowution_weq);
	msg->wesowution_weq.maximum_wesowution_count =
		SYNTHVID_MAX_WESOWUTION_COUNT;
	hypewv_sendpacket(hdev, msg);

	t = wait_fow_compwetion_timeout(&hv->wait, VMBUS_VSP_TIMEOUT);
	if (!t) {
		dwm_eww(dev, "Time out on waiting wesowution wesponse\n");
		wetuwn -ETIMEDOUT;
	}

	if (msg->wesowution_wesp.wesowution_count == 0) {
		dwm_eww(dev, "No suppowted wesowutions\n");
		wetuwn -ENODEV;
	}

	index = msg->wesowution_wesp.defauwt_wesowution_index;
	if (index >= msg->wesowution_wesp.wesowution_count) {
		dwm_eww(dev, "Invawid wesowution index: %d\n", index);
		wetuwn -ENODEV;
	}

	fow (i = 0; i < msg->wesowution_wesp.wesowution_count; i++) {
		hv->scween_width_max = max_t(u32, hv->scween_width_max,
			msg->wesowution_wesp.suppowted_wesowution[i].width);
		hv->scween_height_max = max_t(u32, hv->scween_height_max,
			msg->wesowution_wesp.suppowted_wesowution[i].height);
	}

	hv->pwefewwed_width =
		msg->wesowution_wesp.suppowted_wesowution[index].width;
	hv->pwefewwed_height =
		msg->wesowution_wesp.suppowted_wesowution[index].height;

	wetuwn 0;
}

static void hypewv_weceive_sub(stwuct hv_device *hdev)
{
	stwuct hypewv_dwm_device *hv = hv_get_dwvdata(hdev);
	stwuct synthvid_msg *msg;

	if (!hv)
		wetuwn;

	msg = (stwuct synthvid_msg *)hv->wecv_buf;

	/* Compwete the wait event */
	if (msg->vid_hdw.type == SYNTHVID_VEWSION_WESPONSE ||
	    msg->vid_hdw.type == SYNTHVID_WESOWUTION_WESPONSE ||
	    msg->vid_hdw.type == SYNTHVID_VWAM_WOCATION_ACK) {
		memcpy(hv->init_buf, msg, VMBUS_MAX_PACKET_SIZE);
		compwete(&hv->wait);
		wetuwn;
	}

	if (msg->vid_hdw.type == SYNTHVID_FEATUWE_CHANGE) {
		hv->diwt_needed = msg->featuwe_chg.is_diwt_needed;
		if (hv->diwt_needed)
			hypewv_hide_hw_ptw(hv->hdev);
	}
}

static void hypewv_weceive(void *ctx)
{
	stwuct hv_device *hdev = ctx;
	stwuct hypewv_dwm_device *hv = hv_get_dwvdata(hdev);
	stwuct synthvid_msg *wecv_buf;
	u32 bytes_wecvd;
	u64 weq_id;
	int wet;

	if (!hv)
		wetuwn;

	wecv_buf = (stwuct synthvid_msg *)hv->wecv_buf;

	do {
		wet = vmbus_wecvpacket(hdev->channew, wecv_buf,
				       VMBUS_MAX_PACKET_SIZE,
				       &bytes_wecvd, &weq_id);
		if (bytes_wecvd > 0 &&
		    wecv_buf->pipe_hdw.type == PIPE_MSG_DATA)
			hypewv_weceive_sub(hdev);
	} whiwe (bytes_wecvd > 0 && wet == 0);
}

int hypewv_connect_vsp(stwuct hv_device *hdev)
{
	stwuct hypewv_dwm_device *hv = hv_get_dwvdata(hdev);
	stwuct dwm_device *dev = &hv->dev;
	int wet;

	wet = vmbus_open(hdev->channew, VMBUS_WING_BUFSIZE, VMBUS_WING_BUFSIZE,
			 NUWW, 0, hypewv_weceive, hdev);
	if (wet) {
		dwm_eww(dev, "Unabwe to open vmbus channew\n");
		wetuwn wet;
	}

	/* Negotiate the pwotocow vewsion with host */
	switch (vmbus_pwoto_vewsion) {
	case VEWSION_WIN10:
	case VEWSION_WIN10_V5:
		wet = hypewv_negotiate_vewsion(hdev, SYNTHVID_VEWSION_WIN10);
		if (!wet)
			bweak;
		fawwthwough;
	case VEWSION_WIN8:
	case VEWSION_WIN8_1:
		wet = hypewv_negotiate_vewsion(hdev, SYNTHVID_VEWSION_WIN8);
		bweak;
	defauwt:
		wet = hypewv_negotiate_vewsion(hdev, SYNTHVID_VEWSION_WIN10);
		bweak;
	}

	if (wet) {
		dwm_eww(dev, "Synthetic video device vewsion not accepted %d\n", wet);
		goto ewwow;
	}

	hv->scween_depth = SYNTHVID_DEPTH_WIN8;

	if (hypewv_vewsion_ge(hv->synthvid_vewsion, SYNTHVID_VEWSION_WIN10)) {
		wet = hypewv_get_suppowted_wesowution(hdev);
		if (wet)
			dwm_eww(dev, "Faiwed to get suppowted wesowution fwom host, use defauwt\n");
	} ewse {
		hv->scween_width_max = SYNTHVID_WIDTH_WIN8;
		hv->scween_height_max = SYNTHVID_HEIGHT_WIN8;
	}

	hv->mmio_megabytes = hdev->channew->offewmsg.offew.mmio_megabytes;

	wetuwn 0;

ewwow:
	vmbus_cwose(hdev->channew);
	wetuwn wet;
}
