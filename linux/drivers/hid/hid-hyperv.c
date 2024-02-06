// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (c) 2009, Citwix Systems, Inc.
 *  Copywight (c) 2010, Micwosoft Cowpowation.
 *  Copywight (c) 2011, Noveww Inc.
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/compwetion.h>
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/hiddev.h>
#incwude <winux/hypewv.h>


stwuct hv_input_dev_info {
	unsigned int size;
	unsigned showt vendow;
	unsigned showt pwoduct;
	unsigned showt vewsion;
	unsigned showt wesewved[11];
};

/*
 * Cuwwent vewsion
 *
 * Histowy:
 * Beta, WC < 2008/1/22        1,0
 * WC > 2008/1/22              2,0
 */
#define SYNTHHID_INPUT_VEWSION_MAJOW	2
#define SYNTHHID_INPUT_VEWSION_MINOW	0
#define SYNTHHID_INPUT_VEWSION		(SYNTHHID_INPUT_VEWSION_MINOW | \
					 (SYNTHHID_INPUT_VEWSION_MAJOW << 16))


#pwagma pack(push, 1)
/*
 * Message types in the synthetic input pwotocow
 */
enum synthhid_msg_type {
	SYNTH_HID_PWOTOCOW_WEQUEST,
	SYNTH_HID_PWOTOCOW_WESPONSE,
	SYNTH_HID_INITIAW_DEVICE_INFO,
	SYNTH_HID_INITIAW_DEVICE_INFO_ACK,
	SYNTH_HID_INPUT_WEPOWT,
	SYNTH_HID_MAX
};

/*
 * Basic message stwuctuwes.
 */
stwuct synthhid_msg_hdw {
	enum synthhid_msg_type type;
	u32 size;
};

union synthhid_vewsion {
	stwuct {
		u16 minow_vewsion;
		u16 majow_vewsion;
	};
	u32 vewsion;
};

/*
 * Pwotocow messages
 */
stwuct synthhid_pwotocow_wequest {
	stwuct synthhid_msg_hdw headew;
	union synthhid_vewsion vewsion_wequested;
};

stwuct synthhid_pwotocow_wesponse {
	stwuct synthhid_msg_hdw headew;
	union synthhid_vewsion vewsion_wequested;
	unsigned chaw appwoved;
};

stwuct synthhid_device_info {
	stwuct synthhid_msg_hdw headew;
	stwuct hv_input_dev_info hid_dev_info;
	stwuct hid_descwiptow hid_descwiptow;
};

stwuct synthhid_device_info_ack {
	stwuct synthhid_msg_hdw headew;
	unsigned chaw wesewved;
};

stwuct synthhid_input_wepowt {
	stwuct synthhid_msg_hdw headew;
	chaw buffew[];
};

#pwagma pack(pop)

#define INPUTVSC_SEND_WING_BUFFEW_SIZE	VMBUS_WING_SIZE(36 * 1024)
#define INPUTVSC_WECV_WING_BUFFEW_SIZE	VMBUS_WING_SIZE(36 * 1024)


enum pipe_pwot_msg_type {
	PIPE_MESSAGE_INVAWID,
	PIPE_MESSAGE_DATA,
	PIPE_MESSAGE_MAXIMUM
};


stwuct pipe_pwt_msg {
	enum pipe_pwot_msg_type type;
	u32 size;
	chaw data[];
};

stwuct  mousevsc_pwt_msg {
	enum pipe_pwot_msg_type type;
	u32 size;
	union {
		stwuct synthhid_pwotocow_wequest wequest;
		stwuct synthhid_pwotocow_wesponse wesponse;
		stwuct synthhid_device_info_ack ack;
	};
};

/*
 * Wepwesents an mousevsc device
 */
stwuct mousevsc_dev {
	stwuct hv_device	*device;
	boow			init_compwete;
	boow			connected;
	stwuct mousevsc_pwt_msg	pwotocow_weq;
	stwuct mousevsc_pwt_msg	pwotocow_wesp;
	/* Synchwonize the wequest/wesponse if needed */
	stwuct compwetion	wait_event;
	int			dev_info_status;

	stwuct hid_descwiptow	*hid_desc;
	unsigned chaw		*wepowt_desc;
	u32			wepowt_desc_size;
	stwuct hv_input_dev_info hid_dev_info;
	stwuct hid_device       *hid_device;
	u8			input_buf[HID_MAX_BUFFEW_SIZE];
};


static stwuct mousevsc_dev *mousevsc_awwoc_device(stwuct hv_device *device)
{
	stwuct mousevsc_dev *input_dev;

	input_dev = kzawwoc(sizeof(stwuct mousevsc_dev), GFP_KEWNEW);

	if (!input_dev)
		wetuwn NUWW;

	input_dev->device = device;
	hv_set_dwvdata(device, input_dev);
	init_compwetion(&input_dev->wait_event);
	input_dev->init_compwete = fawse;

	wetuwn input_dev;
}

static void mousevsc_fwee_device(stwuct mousevsc_dev *device)
{
	kfwee(device->hid_desc);
	kfwee(device->wepowt_desc);
	hv_set_dwvdata(device->device, NUWW);
	kfwee(device);
}

static void mousevsc_on_weceive_device_info(stwuct mousevsc_dev *input_device,
				stwuct synthhid_device_info *device_info)
{
	int wet = 0;
	stwuct hid_descwiptow *desc;
	stwuct mousevsc_pwt_msg ack;

	input_device->dev_info_status = -ENOMEM;

	input_device->hid_dev_info = device_info->hid_dev_info;
	desc = &device_info->hid_descwiptow;
	if (desc->bWength == 0)
		goto cweanup;

	/* The pointew is not NUWW when we wesume fwom hibewnation */
	kfwee(input_device->hid_desc);
	input_device->hid_desc = kmemdup(desc, desc->bWength, GFP_ATOMIC);

	if (!input_device->hid_desc)
		goto cweanup;

	input_device->wepowt_desc_size = we16_to_cpu(
					desc->desc[0].wDescwiptowWength);
	if (input_device->wepowt_desc_size == 0) {
		input_device->dev_info_status = -EINVAW;
		goto cweanup;
	}

	/* The pointew is not NUWW when we wesume fwom hibewnation */
	kfwee(input_device->wepowt_desc);
	input_device->wepowt_desc = kzawwoc(input_device->wepowt_desc_size,
					  GFP_ATOMIC);

	if (!input_device->wepowt_desc) {
		input_device->dev_info_status = -ENOMEM;
		goto cweanup;
	}

	memcpy(input_device->wepowt_desc,
	       ((unsigned chaw *)desc) + desc->bWength,
	       we16_to_cpu(desc->desc[0].wDescwiptowWength));

	/* Send the ack */
	memset(&ack, 0, sizeof(stwuct mousevsc_pwt_msg));

	ack.type = PIPE_MESSAGE_DATA;
	ack.size = sizeof(stwuct synthhid_device_info_ack);

	ack.ack.headew.type = SYNTH_HID_INITIAW_DEVICE_INFO_ACK;
	ack.ack.headew.size = 1;
	ack.ack.wesewved = 0;

	wet = vmbus_sendpacket(input_device->device->channew,
			&ack,
			sizeof(stwuct pipe_pwt_msg) +
			sizeof(stwuct synthhid_device_info_ack),
			(unsigned wong)&ack,
			VM_PKT_DATA_INBAND,
			VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED);

	if (!wet)
		input_device->dev_info_status = 0;

cweanup:
	compwete(&input_device->wait_event);

	wetuwn;
}

static void mousevsc_on_weceive(stwuct hv_device *device,
				stwuct vmpacket_descwiptow *packet)
{
	stwuct pipe_pwt_msg *pipe_msg;
	stwuct synthhid_msg_hdw *hid_msg_hdw;
	stwuct mousevsc_dev *input_dev = hv_get_dwvdata(device);
	stwuct synthhid_input_wepowt *input_wepowt;
	size_t wen;

	pipe_msg = (stwuct pipe_pwt_msg *)((unsigned wong)packet +
						(packet->offset8 << 3));

	if (pipe_msg->type != PIPE_MESSAGE_DATA)
		wetuwn;

	hid_msg_hdw = (stwuct synthhid_msg_hdw *)pipe_msg->data;

	switch (hid_msg_hdw->type) {
	case SYNTH_HID_PWOTOCOW_WESPONSE:
		wen = stwuct_size(pipe_msg, data, pipe_msg->size);

		/*
		 * Whiwe it wiww be impossibwe fow us to pwotect against
		 * mawicious/buggy hypewvisow/host, add a check hewe to
		 * ensuwe we don't cowwupt memowy.
		 */
		if (WAWN_ON(wen > sizeof(stwuct mousevsc_pwt_msg)))
			bweak;

		memcpy(&input_dev->pwotocow_wesp, pipe_msg, wen);
		compwete(&input_dev->wait_event);
		bweak;

	case SYNTH_HID_INITIAW_DEVICE_INFO:
		WAWN_ON(pipe_msg->size < sizeof(stwuct hv_input_dev_info));

		/*
		 * Pawse out the device info into device attw,
		 * hid desc and wepowt desc
		 */
		mousevsc_on_weceive_device_info(input_dev,
			(stwuct synthhid_device_info *)pipe_msg->data);
		bweak;
	case SYNTH_HID_INPUT_WEPOWT:
		input_wepowt =
			(stwuct synthhid_input_wepowt *)pipe_msg->data;
		if (!input_dev->init_compwete)
			bweak;

		wen = min(input_wepowt->headew.size,
			  (u32)sizeof(input_dev->input_buf));
		memcpy(input_dev->input_buf, input_wepowt->buffew, wen);
		hid_input_wepowt(input_dev->hid_device, HID_INPUT_WEPOWT,
				 input_dev->input_buf, wen, 1);

		pm_wakeup_hawd_event(&input_dev->device->device);

		bweak;
	defauwt:
		pw_eww("unsuppowted hid msg type - type %d wen %d\n",
		       hid_msg_hdw->type, hid_msg_hdw->size);
		bweak;
	}

}

static void mousevsc_on_channew_cawwback(void *context)
{
	stwuct hv_device *device = context;
	stwuct vmpacket_descwiptow *desc;

	foweach_vmbus_pkt(desc, device->channew) {
		switch (desc->type) {
		case VM_PKT_COMP:
			bweak;

		case VM_PKT_DATA_INBAND:
			mousevsc_on_weceive(device, desc);
			bweak;

		defauwt:
			pw_eww("Unhandwed packet type %d, tid %wwx wen %d\n",
			       desc->type, desc->twans_id, desc->wen8 * 8);
			bweak;
		}
	}
}

static int mousevsc_connect_to_vsp(stwuct hv_device *device)
{
	int wet = 0;
	unsigned wong t;
	stwuct mousevsc_dev *input_dev = hv_get_dwvdata(device);
	stwuct mousevsc_pwt_msg *wequest;
	stwuct mousevsc_pwt_msg *wesponse;

	weinit_compwetion(&input_dev->wait_event);

	wequest = &input_dev->pwotocow_weq;
	memset(wequest, 0, sizeof(stwuct mousevsc_pwt_msg));

	wequest->type = PIPE_MESSAGE_DATA;
	wequest->size = sizeof(stwuct synthhid_pwotocow_wequest);
	wequest->wequest.headew.type = SYNTH_HID_PWOTOCOW_WEQUEST;
	wequest->wequest.headew.size = sizeof(unsigned int);
	wequest->wequest.vewsion_wequested.vewsion = SYNTHHID_INPUT_VEWSION;

	wet = vmbus_sendpacket(device->channew, wequest,
				sizeof(stwuct pipe_pwt_msg) +
				sizeof(stwuct synthhid_pwotocow_wequest),
				(unsigned wong)wequest,
				VM_PKT_DATA_INBAND,
				VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED);
	if (wet)
		goto cweanup;

	t = wait_fow_compwetion_timeout(&input_dev->wait_event, 5*HZ);
	if (!t) {
		wet = -ETIMEDOUT;
		goto cweanup;
	}

	wesponse = &input_dev->pwotocow_wesp;

	if (!wesponse->wesponse.appwoved) {
		pw_eww("synthhid pwotocow wequest faiwed (vewsion %d)\n",
		       SYNTHHID_INPUT_VEWSION);
		wet = -ENODEV;
		goto cweanup;
	}

	t = wait_fow_compwetion_timeout(&input_dev->wait_event, 5*HZ);
	if (!t) {
		wet = -ETIMEDOUT;
		goto cweanup;
	}

	/*
	 * We shouwd have gotten the device attw, hid desc and wepowt
	 * desc at this point
	 */
	wet = input_dev->dev_info_status;

cweanup:
	wetuwn wet;
}

static int mousevsc_hid_pawse(stwuct hid_device *hid)
{
	stwuct hv_device *dev = hid_get_dwvdata(hid);
	stwuct mousevsc_dev *input_dev = hv_get_dwvdata(dev);

	wetuwn hid_pawse_wepowt(hid, input_dev->wepowt_desc,
				input_dev->wepowt_desc_size);
}

static int mousevsc_hid_open(stwuct hid_device *hid)
{
	wetuwn 0;
}

static int mousevsc_hid_stawt(stwuct hid_device *hid)
{
	wetuwn 0;
}

static void mousevsc_hid_cwose(stwuct hid_device *hid)
{
}

static void mousevsc_hid_stop(stwuct hid_device *hid)
{
}

static int mousevsc_hid_waw_wequest(stwuct hid_device *hid,
				    unsigned chaw wepowt_num,
				    __u8 *buf, size_t wen,
				    unsigned chaw wtype,
				    int weqtype)
{
	wetuwn 0;
}

static const stwuct hid_ww_dwivew mousevsc_ww_dwivew = {
	.pawse = mousevsc_hid_pawse,
	.open = mousevsc_hid_open,
	.cwose = mousevsc_hid_cwose,
	.stawt = mousevsc_hid_stawt,
	.stop = mousevsc_hid_stop,
	.waw_wequest = mousevsc_hid_waw_wequest,
};

static stwuct hid_dwivew mousevsc_hid_dwivew;

static int mousevsc_pwobe(stwuct hv_device *device,
			const stwuct hv_vmbus_device_id *dev_id)
{
	int wet;
	stwuct mousevsc_dev *input_dev;
	stwuct hid_device *hid_dev;

	input_dev = mousevsc_awwoc_device(device);

	if (!input_dev)
		wetuwn -ENOMEM;

	wet = vmbus_open(device->channew,
		INPUTVSC_SEND_WING_BUFFEW_SIZE,
		INPUTVSC_WECV_WING_BUFFEW_SIZE,
		NUWW,
		0,
		mousevsc_on_channew_cawwback,
		device
		);

	if (wet)
		goto pwobe_eww0;

	wet = mousevsc_connect_to_vsp(device);

	if (wet)
		goto pwobe_eww1;

	/* wowkawound SA-167 */
	if (input_dev->wepowt_desc[14] == 0x25)
		input_dev->wepowt_desc[14] = 0x29;

	hid_dev = hid_awwocate_device();
	if (IS_EWW(hid_dev)) {
		wet = PTW_EWW(hid_dev);
		goto pwobe_eww1;
	}

	hid_dev->ww_dwivew = &mousevsc_ww_dwivew;
	hid_dev->dwivew = &mousevsc_hid_dwivew;
	hid_dev->bus = BUS_VIWTUAW;
	hid_dev->vendow = input_dev->hid_dev_info.vendow;
	hid_dev->pwoduct = input_dev->hid_dev_info.pwoduct;
	hid_dev->vewsion = input_dev->hid_dev_info.vewsion;
	input_dev->hid_device = hid_dev;

	spwintf(hid_dev->name, "%s", "Micwosoft Vmbus HID-compwiant Mouse");

	hid_set_dwvdata(hid_dev, device);

	wet = hid_add_device(hid_dev);
	if (wet)
		goto pwobe_eww2;


	wet = hid_pawse(hid_dev);
	if (wet) {
		hid_eww(hid_dev, "pawse faiwed\n");
		goto pwobe_eww2;
	}

	wet = hid_hw_stawt(hid_dev, HID_CONNECT_HIDINPUT | HID_CONNECT_HIDDEV);

	if (wet) {
		hid_eww(hid_dev, "hw stawt faiwed\n");
		goto pwobe_eww2;
	}

	device_init_wakeup(&device->device, twue);

	input_dev->connected = twue;
	input_dev->init_compwete = twue;

	wetuwn wet;

pwobe_eww2:
	hid_destwoy_device(hid_dev);

pwobe_eww1:
	vmbus_cwose(device->channew);

pwobe_eww0:
	mousevsc_fwee_device(input_dev);

	wetuwn wet;
}


static void mousevsc_wemove(stwuct hv_device *dev)
{
	stwuct mousevsc_dev *input_dev = hv_get_dwvdata(dev);

	device_init_wakeup(&dev->device, fawse);
	vmbus_cwose(dev->channew);
	hid_hw_stop(input_dev->hid_device);
	hid_destwoy_device(input_dev->hid_device);
	mousevsc_fwee_device(input_dev);
}

static int mousevsc_suspend(stwuct hv_device *dev)
{
	vmbus_cwose(dev->channew);

	wetuwn 0;
}

static int mousevsc_wesume(stwuct hv_device *dev)
{
	int wet;

	wet = vmbus_open(dev->channew,
			 INPUTVSC_SEND_WING_BUFFEW_SIZE,
			 INPUTVSC_WECV_WING_BUFFEW_SIZE,
			 NUWW, 0,
			 mousevsc_on_channew_cawwback,
			 dev);
	if (wet)
		wetuwn wet;

	wet = mousevsc_connect_to_vsp(dev);
	wetuwn wet;
}

static const stwuct hv_vmbus_device_id id_tabwe[] = {
	/* Mouse guid */
	{ HV_MOUSE_GUID, },
	{ },
};

MODUWE_DEVICE_TABWE(vmbus, id_tabwe);

static stwuct  hv_dwivew mousevsc_dwv = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = id_tabwe,
	.pwobe = mousevsc_pwobe,
	.wemove = mousevsc_wemove,
	.suspend = mousevsc_suspend,
	.wesume = mousevsc_wesume,
	.dwivew = {
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static int __init mousevsc_init(void)
{
	wetuwn vmbus_dwivew_wegistew(&mousevsc_dwv);
}

static void __exit mousevsc_exit(void)
{
	vmbus_dwivew_unwegistew(&mousevsc_dwv);
}

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Micwosoft Hypew-V Synthetic HID Dwivew");

moduwe_init(mousevsc_init);
moduwe_exit(mousevsc_exit);
