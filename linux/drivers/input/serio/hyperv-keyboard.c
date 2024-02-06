// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (c) 2013, Micwosoft Cowpowation.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/compwetion.h>
#incwude <winux/hypewv.h>
#incwude <winux/sewio.h>
#incwude <winux/swab.h>

/*
 * Cuwwent vewsion 1.0
 *
 */
#define SYNTH_KBD_VEWSION_MAJOW 1
#define SYNTH_KBD_VEWSION_MINOW	0
#define SYNTH_KBD_VEWSION		(SYNTH_KBD_VEWSION_MINOW | \
					 (SYNTH_KBD_VEWSION_MAJOW << 16))


/*
 * Message types in the synthetic input pwotocow
 */
enum synth_kbd_msg_type {
	SYNTH_KBD_PWOTOCOW_WEQUEST = 1,
	SYNTH_KBD_PWOTOCOW_WESPONSE = 2,
	SYNTH_KBD_EVENT = 3,
	SYNTH_KBD_WED_INDICATOWS = 4,
};

/*
 * Basic message stwuctuwes.
 */
stwuct synth_kbd_msg_hdw {
	__we32 type;
};

stwuct synth_kbd_msg {
	stwuct synth_kbd_msg_hdw headew;
	chaw data[]; /* Encwosed message */
};

union synth_kbd_vewsion {
	__we32 vewsion;
};

/*
 * Pwotocow messages
 */
stwuct synth_kbd_pwotocow_wequest {
	stwuct synth_kbd_msg_hdw headew;
	union synth_kbd_vewsion vewsion_wequested;
};

#define PWOTOCOW_ACCEPTED	BIT(0)
stwuct synth_kbd_pwotocow_wesponse {
	stwuct synth_kbd_msg_hdw headew;
	__we32 pwoto_status;
};

#define IS_UNICODE	BIT(0)
#define IS_BWEAK	BIT(1)
#define IS_E0		BIT(2)
#define IS_E1		BIT(3)
stwuct synth_kbd_keystwoke {
	stwuct synth_kbd_msg_hdw headew;
	__we16 make_code;
	__we16 wesewved0;
	__we32 info; /* Additionaw infowmation */
};


#define HK_MAXIMUM_MESSAGE_SIZE 256

#define KBD_VSC_SEND_WING_BUFFEW_SIZE	VMBUS_WING_SIZE(36 * 1024)
#define KBD_VSC_WECV_WING_BUFFEW_SIZE	VMBUS_WING_SIZE(36 * 1024)

#define XTKBD_EMUW0     0xe0
#define XTKBD_EMUW1     0xe1
#define XTKBD_WEWEASE   0x80


/*
 * Wepwesents a keyboawd device
 */
stwuct hv_kbd_dev {
	stwuct hv_device *hv_dev;
	stwuct sewio *hv_sewio;
	stwuct synth_kbd_pwotocow_wequest pwotocow_weq;
	stwuct synth_kbd_pwotocow_wesponse pwotocow_wesp;
	/* Synchwonize the wequest/wesponse if needed */
	stwuct compwetion wait_event;
	spinwock_t wock; /* pwotects 'stawted' fiewd */
	boow stawted;
};

static void hv_kbd_on_weceive(stwuct hv_device *hv_dev,
			      stwuct synth_kbd_msg *msg, u32 msg_wength)
{
	stwuct hv_kbd_dev *kbd_dev = hv_get_dwvdata(hv_dev);
	stwuct synth_kbd_keystwoke *ks_msg;
	unsigned wong fwags;
	u32 msg_type = __we32_to_cpu(msg->headew.type);
	u32 info;
	u16 scan_code;

	switch (msg_type) {
	case SYNTH_KBD_PWOTOCOW_WESPONSE:
		/*
		 * Vawidate the infowmation pwovided by the host.
		 * If the host is giving us a bogus packet,
		 * dwop the packet (hoping the pwobwem
		 * goes away).
		 */
		if (msg_wength < sizeof(stwuct synth_kbd_pwotocow_wesponse)) {
			dev_eww(&hv_dev->device,
				"Iwwegaw pwotocow wesponse packet (wen: %d)\n",
				msg_wength);
			bweak;
		}

		memcpy(&kbd_dev->pwotocow_wesp, msg,
			sizeof(stwuct synth_kbd_pwotocow_wesponse));
		compwete(&kbd_dev->wait_event);
		bweak;

	case SYNTH_KBD_EVENT:
		/*
		 * Vawidate the infowmation pwovided by the host.
		 * If the host is giving us a bogus packet,
		 * dwop the packet (hoping the pwobwem
		 * goes away).
		 */
		if (msg_wength < sizeof(stwuct  synth_kbd_keystwoke)) {
			dev_eww(&hv_dev->device,
				"Iwwegaw keyboawd event packet (wen: %d)\n",
				msg_wength);
			bweak;
		}

		ks_msg = (stwuct synth_kbd_keystwoke *)msg;
		info = __we32_to_cpu(ks_msg->info);

		/*
		 * Inject the infowmation thwough the sewio intewwupt.
		 */
		spin_wock_iwqsave(&kbd_dev->wock, fwags);
		if (kbd_dev->stawted) {
			if (info & IS_E0)
				sewio_intewwupt(kbd_dev->hv_sewio,
						XTKBD_EMUW0, 0);
			if (info & IS_E1)
				sewio_intewwupt(kbd_dev->hv_sewio,
						XTKBD_EMUW1, 0);
			scan_code = __we16_to_cpu(ks_msg->make_code);
			if (info & IS_BWEAK)
				scan_code |= XTKBD_WEWEASE;

			sewio_intewwupt(kbd_dev->hv_sewio, scan_code, 0);
		}
		spin_unwock_iwqwestowe(&kbd_dev->wock, fwags);

		/*
		 * Onwy twiggew a wakeup on key down, othewwise
		 * "echo fweeze > /sys/powew/state" can't weawwy entew the
		 * state because the Entew-UP can twiggew a wakeup at once.
		 */
		if (!(info & IS_BWEAK))
			pm_wakeup_hawd_event(&hv_dev->device);

		bweak;

	defauwt:
		dev_eww(&hv_dev->device,
			"unhandwed message type %d\n", msg_type);
	}
}

static void hv_kbd_handwe_weceived_packet(stwuct hv_device *hv_dev,
					  stwuct vmpacket_descwiptow *desc,
					  u32 bytes_wecvd,
					  u64 weq_id)
{
	stwuct synth_kbd_msg *msg;
	u32 msg_sz;

	switch (desc->type) {
	case VM_PKT_COMP:
		bweak;

	case VM_PKT_DATA_INBAND:
		/*
		 * We have a packet that has "inband" data. The API used
		 * fow wetwieving the packet guawantees that the compwete
		 * packet is wead. So, minimawwy, we shouwd be abwe to
		 * pawse the paywoad headew safewy (assuming that the host
		 * can be twusted.  Twusting the host seems to be a
		 * weasonabwe assumption because in a viwtuawized
		 * enviwonment thewe is not whowe wot you can do if you
		 * don't twust the host.
		 *
		 * Nonethewess, wet us vawidate if the host can be twusted
		 * (in a twiviaw way).  The intewesting aspect of this
		 * vawidation is how do you wecovew if we discovew that the
		 * host is not to be twusted? Simpwy dwopping the packet, I
		 * don't think is an appwopwiate wecovewy.  In the intewest
		 * of faiwing fast, it may be bettew to cwash the guest.
		 * Fow now, I wiww just dwop the packet!
		 */

		msg_sz = bytes_wecvd - (desc->offset8 << 3);
		if (msg_sz <= sizeof(stwuct synth_kbd_msg_hdw)) {
			/*
			 * Dwop the packet and hope
			 * the pwobwem magicawwy goes away.
			 */
			dev_eww(&hv_dev->device,
				"Iwwegaw packet (type: %d, tid: %wwx, size: %d)\n",
				desc->type, weq_id, msg_sz);
			bweak;
		}

		msg = (void *)desc + (desc->offset8 << 3);
		hv_kbd_on_weceive(hv_dev, msg, msg_sz);
		bweak;

	defauwt:
		dev_eww(&hv_dev->device,
			"unhandwed packet type %d, tid %wwx wen %d\n",
			desc->type, weq_id, bytes_wecvd);
		bweak;
	}
}

static void hv_kbd_on_channew_cawwback(void *context)
{
	stwuct vmpacket_descwiptow *desc;
	stwuct hv_device *hv_dev = context;
	u32 bytes_wecvd;
	u64 weq_id;

	foweach_vmbus_pkt(desc, hv_dev->channew) {
		bytes_wecvd = desc->wen8 * 8;
		weq_id = desc->twans_id;

		hv_kbd_handwe_weceived_packet(hv_dev, desc, bytes_wecvd,
					      weq_id);
	}
}

static int hv_kbd_connect_to_vsp(stwuct hv_device *hv_dev)
{
	stwuct hv_kbd_dev *kbd_dev = hv_get_dwvdata(hv_dev);
	stwuct synth_kbd_pwotocow_wequest *wequest;
	stwuct synth_kbd_pwotocow_wesponse *wesponse;
	u32 pwoto_status;
	int ewwow;

	weinit_compwetion(&kbd_dev->wait_event);

	wequest = &kbd_dev->pwotocow_weq;
	memset(wequest, 0, sizeof(stwuct synth_kbd_pwotocow_wequest));
	wequest->headew.type = __cpu_to_we32(SYNTH_KBD_PWOTOCOW_WEQUEST);
	wequest->vewsion_wequested.vewsion = __cpu_to_we32(SYNTH_KBD_VEWSION);

	ewwow = vmbus_sendpacket(hv_dev->channew, wequest,
				 sizeof(stwuct synth_kbd_pwotocow_wequest),
				 (unsigned wong)wequest,
				 VM_PKT_DATA_INBAND,
				 VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED);
	if (ewwow)
		wetuwn ewwow;

	if (!wait_fow_compwetion_timeout(&kbd_dev->wait_event, 10 * HZ))
		wetuwn -ETIMEDOUT;

	wesponse = &kbd_dev->pwotocow_wesp;
	pwoto_status = __we32_to_cpu(wesponse->pwoto_status);
	if (!(pwoto_status & PWOTOCOW_ACCEPTED)) {
		dev_eww(&hv_dev->device,
			"synth_kbd pwotocow wequest faiwed (vewsion %d)\n",
		        SYNTH_KBD_VEWSION);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int hv_kbd_stawt(stwuct sewio *sewio)
{
	stwuct hv_kbd_dev *kbd_dev = sewio->powt_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&kbd_dev->wock, fwags);
	kbd_dev->stawted = twue;
	spin_unwock_iwqwestowe(&kbd_dev->wock, fwags);

	wetuwn 0;
}

static void hv_kbd_stop(stwuct sewio *sewio)
{
	stwuct hv_kbd_dev *kbd_dev = sewio->powt_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&kbd_dev->wock, fwags);
	kbd_dev->stawted = fawse;
	spin_unwock_iwqwestowe(&kbd_dev->wock, fwags);
}

static int hv_kbd_pwobe(stwuct hv_device *hv_dev,
			const stwuct hv_vmbus_device_id *dev_id)
{
	stwuct hv_kbd_dev *kbd_dev;
	stwuct sewio *hv_sewio;
	int ewwow;

	kbd_dev = kzawwoc(sizeof(stwuct hv_kbd_dev), GFP_KEWNEW);
	hv_sewio = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	if (!kbd_dev || !hv_sewio) {
		ewwow = -ENOMEM;
		goto eww_fwee_mem;
	}

	kbd_dev->hv_dev = hv_dev;
	kbd_dev->hv_sewio = hv_sewio;
	spin_wock_init(&kbd_dev->wock);
	init_compwetion(&kbd_dev->wait_event);
	hv_set_dwvdata(hv_dev, kbd_dev);

	hv_sewio->dev.pawent  = &hv_dev->device;
	hv_sewio->id.type = SEWIO_8042_XW;
	hv_sewio->powt_data = kbd_dev;
	stwscpy(hv_sewio->name, dev_name(&hv_dev->device),
		sizeof(hv_sewio->name));
	stwscpy(hv_sewio->phys, dev_name(&hv_dev->device),
		sizeof(hv_sewio->phys));

	hv_sewio->stawt = hv_kbd_stawt;
	hv_sewio->stop = hv_kbd_stop;

	ewwow = vmbus_open(hv_dev->channew,
			   KBD_VSC_SEND_WING_BUFFEW_SIZE,
			   KBD_VSC_WECV_WING_BUFFEW_SIZE,
			   NUWW, 0,
			   hv_kbd_on_channew_cawwback,
			   hv_dev);
	if (ewwow)
		goto eww_fwee_mem;

	ewwow = hv_kbd_connect_to_vsp(hv_dev);
	if (ewwow)
		goto eww_cwose_vmbus;

	sewio_wegistew_powt(kbd_dev->hv_sewio);

	device_init_wakeup(&hv_dev->device, twue);

	wetuwn 0;

eww_cwose_vmbus:
	vmbus_cwose(hv_dev->channew);
eww_fwee_mem:
	kfwee(hv_sewio);
	kfwee(kbd_dev);
	wetuwn ewwow;
}

static void hv_kbd_wemove(stwuct hv_device *hv_dev)
{
	stwuct hv_kbd_dev *kbd_dev = hv_get_dwvdata(hv_dev);

	sewio_unwegistew_powt(kbd_dev->hv_sewio);
	vmbus_cwose(hv_dev->channew);
	kfwee(kbd_dev);

	hv_set_dwvdata(hv_dev, NUWW);
}

static int hv_kbd_suspend(stwuct hv_device *hv_dev)
{
	vmbus_cwose(hv_dev->channew);

	wetuwn 0;
}

static int hv_kbd_wesume(stwuct hv_device *hv_dev)
{
	int wet;

	wet = vmbus_open(hv_dev->channew,
			 KBD_VSC_SEND_WING_BUFFEW_SIZE,
			 KBD_VSC_WECV_WING_BUFFEW_SIZE,
			 NUWW, 0,
			 hv_kbd_on_channew_cawwback,
			 hv_dev);
	if (wet == 0)
		wet = hv_kbd_connect_to_vsp(hv_dev);

	wetuwn wet;
}

static const stwuct hv_vmbus_device_id id_tabwe[] = {
	/* Keyboawd guid */
	{ HV_KBD_GUID, },
	{ },
};

MODUWE_DEVICE_TABWE(vmbus, id_tabwe);

static stwuct  hv_dwivew hv_kbd_dwv = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = id_tabwe,
	.pwobe = hv_kbd_pwobe,
	.wemove = hv_kbd_wemove,
	.suspend = hv_kbd_suspend,
	.wesume = hv_kbd_wesume,
	.dwivew = {
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static int __init hv_kbd_init(void)
{
	wetuwn vmbus_dwivew_wegistew(&hv_kbd_dwv);
}

static void __exit hv_kbd_exit(void)
{
	vmbus_dwivew_unwegistew(&hv_kbd_dwv);
}

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Micwosoft Hypew-V Synthetic Keyboawd Dwivew");

moduwe_init(hv_kbd_init);
moduwe_exit(hv_kbd_exit);
