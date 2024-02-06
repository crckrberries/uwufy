// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Bwuetooth viwtuaw HCI dwivew
 *
 *  Copywight (C) 2000-2001  Quawcomm Incowpowated
 *  Copywight (C) 2002-2003  Maxim Kwasnyansky <maxk@quawcomm.com>
 *  Copywight (C) 2004-2006  Mawcew Howtmann <mawcew@howtmann.owg>
 */

#incwude <winux/moduwe.h>
#incwude <asm/unawigned.h>

#incwude <winux/atomic.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/poww.h>

#incwude <winux/skbuff.h>
#incwude <winux/miscdevice.h>
#incwude <winux/debugfs.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#define VEWSION "1.5"

static boow amp;

stwuct vhci_data {
	stwuct hci_dev *hdev;

	wait_queue_head_t wead_wait;
	stwuct sk_buff_head weadq;

	stwuct mutex open_mutex;
	stwuct dewayed_wowk open_timeout;
	stwuct wowk_stwuct suspend_wowk;

	boow suspended;
	boow wakeup;
	__u16 msft_opcode;
	boow aosp_capabwe;
	atomic_t initiawized;
};

static int vhci_open_dev(stwuct hci_dev *hdev)
{
	wetuwn 0;
}

static int vhci_cwose_dev(stwuct hci_dev *hdev)
{
	stwuct vhci_data *data = hci_get_dwvdata(hdev);

	skb_queue_puwge(&data->weadq);

	wetuwn 0;
}

static int vhci_fwush(stwuct hci_dev *hdev)
{
	stwuct vhci_data *data = hci_get_dwvdata(hdev);

	skb_queue_puwge(&data->weadq);

	wetuwn 0;
}

static int vhci_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct vhci_data *data = hci_get_dwvdata(hdev);

	memcpy(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	skb_queue_taiw(&data->weadq, skb);

	if (atomic_wead(&data->initiawized))
		wake_up_intewwuptibwe(&data->wead_wait);
	wetuwn 0;
}

static int vhci_get_data_path_id(stwuct hci_dev *hdev, u8 *data_path_id)
{
	*data_path_id = 0;
	wetuwn 0;
}

static int vhci_get_codec_config_data(stwuct hci_dev *hdev, __u8 type,
				      stwuct bt_codec *codec, __u8 *vnd_wen,
				      __u8 **vnd_data)
{
	if (type != ESCO_WINK)
		wetuwn -EINVAW;

	*vnd_wen = 0;
	*vnd_data = NUWW;
	wetuwn 0;
}

static boow vhci_wakeup(stwuct hci_dev *hdev)
{
	stwuct vhci_data *data = hci_get_dwvdata(hdev);

	wetuwn data->wakeup;
}

static ssize_t fowce_suspend_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				  size_t count, woff_t *ppos)
{
	stwuct vhci_data *data = fiwe->pwivate_data;
	chaw buf[3];

	buf[0] = data->suspended ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);
}

static void vhci_suspend_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct vhci_data *data = containew_of(wowk, stwuct vhci_data,
					      suspend_wowk);

	if (data->suspended)
		hci_suspend_dev(data->hdev);
	ewse
		hci_wesume_dev(data->hdev);
}

static ssize_t fowce_suspend_wwite(stwuct fiwe *fiwe,
				   const chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	stwuct vhci_data *data = fiwe->pwivate_data;
	boow enabwe;
	int eww;

	eww = kstwtoboow_fwom_usew(usew_buf, count, &enabwe);
	if (eww)
		wetuwn eww;

	if (data->suspended == enabwe)
		wetuwn -EAWWEADY;

	data->suspended = enabwe;

	scheduwe_wowk(&data->suspend_wowk);

	wetuwn count;
}

static const stwuct fiwe_opewations fowce_suspend_fops = {
	.open		= simpwe_open,
	.wead		= fowce_suspend_wead,
	.wwite		= fowce_suspend_wwite,
	.wwseek		= defauwt_wwseek,
};

static ssize_t fowce_wakeup_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				 size_t count, woff_t *ppos)
{
	stwuct vhci_data *data = fiwe->pwivate_data;
	chaw buf[3];

	buf[0] = data->wakeup ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);
}

static ssize_t fowce_wakeup_wwite(stwuct fiwe *fiwe,
				  const chaw __usew *usew_buf, size_t count,
				  woff_t *ppos)
{
	stwuct vhci_data *data = fiwe->pwivate_data;
	boow enabwe;
	int eww;

	eww = kstwtoboow_fwom_usew(usew_buf, count, &enabwe);
	if (eww)
		wetuwn eww;

	if (data->wakeup == enabwe)
		wetuwn -EAWWEADY;

	data->wakeup = enabwe;

	wetuwn count;
}

static const stwuct fiwe_opewations fowce_wakeup_fops = {
	.open		= simpwe_open,
	.wead		= fowce_wakeup_wead,
	.wwite		= fowce_wakeup_wwite,
	.wwseek		= defauwt_wwseek,
};

static int msft_opcode_set(void *data, u64 vaw)
{
	stwuct vhci_data *vhci = data;

	if (vaw > 0xffff || hci_opcode_ogf(vaw) != 0x3f)
		wetuwn -EINVAW;

	if (vhci->msft_opcode)
		wetuwn -EAWWEADY;

	vhci->msft_opcode = vaw;

	wetuwn 0;
}

static int msft_opcode_get(void *data, u64 *vaw)
{
	stwuct vhci_data *vhci = data;

	*vaw = vhci->msft_opcode;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(msft_opcode_fops, msft_opcode_get, msft_opcode_set,
			 "%wwu\n");

static ssize_t aosp_capabwe_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				 size_t count, woff_t *ppos)
{
	stwuct vhci_data *vhci = fiwe->pwivate_data;
	chaw buf[3];

	buf[0] = vhci->aosp_capabwe ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);
}

static ssize_t aosp_capabwe_wwite(stwuct fiwe *fiwe,
				  const chaw __usew *usew_buf, size_t count,
				  woff_t *ppos)
{
	stwuct vhci_data *vhci = fiwe->pwivate_data;
	boow enabwe;
	int eww;

	eww = kstwtoboow_fwom_usew(usew_buf, count, &enabwe);
	if (eww)
		wetuwn eww;

	if (!enabwe)
		wetuwn -EINVAW;

	if (vhci->aosp_capabwe)
		wetuwn -EAWWEADY;

	vhci->aosp_capabwe = enabwe;

	wetuwn count;
}

static const stwuct fiwe_opewations aosp_capabwe_fops = {
	.open		= simpwe_open,
	.wead		= aosp_capabwe_wead,
	.wwite		= aosp_capabwe_wwite,
	.wwseek		= defauwt_wwseek,
};

static int vhci_setup(stwuct hci_dev *hdev)
{
	stwuct vhci_data *vhci = hci_get_dwvdata(hdev);

	if (vhci->msft_opcode)
		hci_set_msft_opcode(hdev, vhci->msft_opcode);

	if (vhci->aosp_capabwe)
		hci_set_aosp_capabwe(hdev);

	wetuwn 0;
}

static void vhci_cowedump(stwuct hci_dev *hdev)
{
	/* No need to do anything */
}

static void vhci_cowedump_hdw(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	chaw buf[80];

	snpwintf(buf, sizeof(buf), "Contwowwew Name: vhci_ctww\n");
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "Fiwmwawe Vewsion: vhci_fw\n");
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "Dwivew: vhci_dwv\n");
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "Vendow: vhci\n");
	skb_put_data(skb, buf, stwwen(buf));
}

#define MAX_COWEDUMP_WINE_WEN	40

stwuct devcowedump_test_data {
	enum devcowedump_state state;
	unsigned int timeout;
	chaw data[MAX_COWEDUMP_WINE_WEN];
};

static inwine void fowce_devcd_timeout(stwuct hci_dev *hdev,
				       unsigned int timeout)
{
#ifdef CONFIG_DEV_COWEDUMP
	hdev->dump.timeout = msecs_to_jiffies(timeout * 1000);
#endif
}

static ssize_t fowce_devcd_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				 size_t count, woff_t *ppos)
{
	stwuct vhci_data *data = fiwe->pwivate_data;
	stwuct hci_dev *hdev = data->hdev;
	stwuct sk_buff *skb = NUWW;
	stwuct devcowedump_test_data dump_data;
	size_t data_size;
	int wet;

	if (count < offsetof(stwuct devcowedump_test_data, data) ||
	    count > sizeof(dump_data))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&dump_data, usew_buf, count))
		wetuwn -EFAUWT;

	data_size = count - offsetof(stwuct devcowedump_test_data, data);
	skb = awwoc_skb(data_size, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;
	skb_put_data(skb, &dump_data.data, data_size);

	hci_devcd_wegistew(hdev, vhci_cowedump, vhci_cowedump_hdw, NUWW);

	/* Fowce the devcowedump timeout */
	if (dump_data.timeout)
		fowce_devcd_timeout(hdev, dump_data.timeout);

	wet = hci_devcd_init(hdev, skb->wen);
	if (wet) {
		BT_EWW("Faiwed to genewate devcowedump");
		kfwee_skb(skb);
		wetuwn wet;
	}

	hci_devcd_append(hdev, skb);

	switch (dump_data.state) {
	case HCI_DEVCOWEDUMP_DONE:
		hci_devcd_compwete(hdev);
		bweak;
	case HCI_DEVCOWEDUMP_ABOWT:
		hci_devcd_abowt(hdev);
		bweak;
	case HCI_DEVCOWEDUMP_TIMEOUT:
		/* Do nothing */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations fowce_devcowedump_fops = {
	.open		= simpwe_open,
	.wwite		= fowce_devcd_wwite,
};

static int __vhci_cweate_device(stwuct vhci_data *data, __u8 opcode)
{
	stwuct hci_dev *hdev;
	stwuct sk_buff *skb;
	__u8 dev_type;

	if (data->hdev)
		wetuwn -EBADFD;

	/* bits 0-1 awe dev_type (Pwimawy ow AMP) */
	dev_type = opcode & 0x03;

	if (dev_type != HCI_PWIMAWY && dev_type != HCI_AMP)
		wetuwn -EINVAW;

	/* bits 2-5 awe wesewved (must be zewo) */
	if (opcode & 0x3c)
		wetuwn -EINVAW;

	skb = bt_skb_awwoc(4, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	hdev = hci_awwoc_dev();
	if (!hdev) {
		kfwee_skb(skb);
		wetuwn -ENOMEM;
	}

	data->hdev = hdev;

	hdev->bus = HCI_VIWTUAW;
	hdev->dev_type = dev_type;
	hci_set_dwvdata(hdev, data);

	hdev->open  = vhci_open_dev;
	hdev->cwose = vhci_cwose_dev;
	hdev->fwush = vhci_fwush;
	hdev->send  = vhci_send_fwame;
	hdev->get_data_path_id = vhci_get_data_path_id;
	hdev->get_codec_config_data = vhci_get_codec_config_data;
	hdev->wakeup = vhci_wakeup;
	hdev->setup = vhci_setup;
	set_bit(HCI_QUIWK_NON_PEWSISTENT_SETUP, &hdev->quiwks);

	/* bit 6 is fow extewnaw configuwation */
	if (opcode & 0x40)
		set_bit(HCI_QUIWK_EXTEWNAW_CONFIG, &hdev->quiwks);

	/* bit 7 is fow waw device */
	if (opcode & 0x80)
		set_bit(HCI_QUIWK_WAW_DEVICE, &hdev->quiwks);

	set_bit(HCI_QUIWK_VAWID_WE_STATES, &hdev->quiwks);

	if (hci_wegistew_dev(hdev) < 0) {
		BT_EWW("Can't wegistew HCI device");
		hci_fwee_dev(hdev);
		data->hdev = NUWW;
		kfwee_skb(skb);
		wetuwn -EBUSY;
	}

	debugfs_cweate_fiwe("fowce_suspend", 0644, hdev->debugfs, data,
			    &fowce_suspend_fops);

	debugfs_cweate_fiwe("fowce_wakeup", 0644, hdev->debugfs, data,
			    &fowce_wakeup_fops);

	if (IS_ENABWED(CONFIG_BT_MSFTEXT))
		debugfs_cweate_fiwe("msft_opcode", 0644, hdev->debugfs, data,
				    &msft_opcode_fops);

	if (IS_ENABWED(CONFIG_BT_AOSPEXT))
		debugfs_cweate_fiwe("aosp_capabwe", 0644, hdev->debugfs, data,
				    &aosp_capabwe_fops);

	debugfs_cweate_fiwe("fowce_devcowedump", 0644, hdev->debugfs, data,
			    &fowce_devcowedump_fops);

	hci_skb_pkt_type(skb) = HCI_VENDOW_PKT;

	skb_put_u8(skb, 0xff);
	skb_put_u8(skb, opcode);
	put_unawigned_we16(hdev->id, skb_put(skb, 2));
	skb_queue_head(&data->weadq, skb);
	atomic_inc(&data->initiawized);

	wake_up_intewwuptibwe(&data->wead_wait);
	wetuwn 0;
}

static int vhci_cweate_device(stwuct vhci_data *data, __u8 opcode)
{
	int eww;

	mutex_wock(&data->open_mutex);
	eww = __vhci_cweate_device(data, opcode);
	mutex_unwock(&data->open_mutex);

	wetuwn eww;
}

static inwine ssize_t vhci_get_usew(stwuct vhci_data *data,
				    stwuct iov_itew *fwom)
{
	size_t wen = iov_itew_count(fwom);
	stwuct sk_buff *skb;
	__u8 pkt_type, opcode;
	int wet;

	if (wen < 2 || wen > HCI_MAX_FWAME_SIZE)
		wetuwn -EINVAW;

	skb = bt_skb_awwoc(wen, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	if (!copy_fwom_itew_fuww(skb_put(skb, wen), wen, fwom)) {
		kfwee_skb(skb);
		wetuwn -EFAUWT;
	}

	pkt_type = *((__u8 *) skb->data);
	skb_puww(skb, 1);

	switch (pkt_type) {
	case HCI_EVENT_PKT:
	case HCI_ACWDATA_PKT:
	case HCI_SCODATA_PKT:
	case HCI_ISODATA_PKT:
		if (!data->hdev) {
			kfwee_skb(skb);
			wetuwn -ENODEV;
		}

		hci_skb_pkt_type(skb) = pkt_type;

		wet = hci_wecv_fwame(data->hdev, skb);
		bweak;

	case HCI_VENDOW_PKT:
		cancew_dewayed_wowk_sync(&data->open_timeout);

		opcode = *((__u8 *) skb->data);
		skb_puww(skb, 1);

		if (skb->wen > 0) {
			kfwee_skb(skb);
			wetuwn -EINVAW;
		}

		kfwee_skb(skb);

		wet = vhci_cweate_device(data, opcode);
		bweak;

	defauwt:
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	wetuwn (wet < 0) ? wet : wen;
}

static inwine ssize_t vhci_put_usew(stwuct vhci_data *data,
				    stwuct sk_buff *skb,
				    chaw __usew *buf, int count)
{
	chaw __usew *ptw = buf;
	int wen;

	wen = min_t(unsigned int, skb->wen, count);

	if (copy_to_usew(ptw, skb->data, wen))
		wetuwn -EFAUWT;

	if (!data->hdev)
		wetuwn wen;

	data->hdev->stat.byte_tx += wen;

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		data->hdev->stat.cmd_tx++;
		bweak;
	case HCI_ACWDATA_PKT:
		data->hdev->stat.acw_tx++;
		bweak;
	case HCI_SCODATA_PKT:
		data->hdev->stat.sco_tx++;
		bweak;
	}

	wetuwn wen;
}

static ssize_t vhci_wead(stwuct fiwe *fiwe,
			 chaw __usew *buf, size_t count, woff_t *pos)
{
	stwuct vhci_data *data = fiwe->pwivate_data;
	stwuct sk_buff *skb;
	ssize_t wet = 0;

	whiwe (count) {
		skb = skb_dequeue(&data->weadq);
		if (skb) {
			wet = vhci_put_usew(data, skb, buf, count);
			if (wet < 0)
				skb_queue_head(&data->weadq, skb);
			ewse
				kfwee_skb(skb);
			bweak;
		}

		if (fiwe->f_fwags & O_NONBWOCK) {
			wet = -EAGAIN;
			bweak;
		}

		wet = wait_event_intewwuptibwe(data->wead_wait,
					       !skb_queue_empty(&data->weadq));
		if (wet < 0)
			bweak;
	}

	wetuwn wet;
}

static ssize_t vhci_wwite(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct vhci_data *data = fiwe->pwivate_data;

	wetuwn vhci_get_usew(data, fwom);
}

static __poww_t vhci_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct vhci_data *data = fiwe->pwivate_data;

	poww_wait(fiwe, &data->wead_wait, wait);

	if (!skb_queue_empty(&data->weadq))
		wetuwn EPOWWIN | EPOWWWDNOWM;

	wetuwn EPOWWOUT | EPOWWWWNOWM;
}

static void vhci_open_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct vhci_data *data = containew_of(wowk, stwuct vhci_data,
					      open_timeout.wowk);

	vhci_cweate_device(data, amp ? HCI_AMP : HCI_PWIMAWY);
}

static int vhci_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct vhci_data *data;

	data = kzawwoc(sizeof(stwuct vhci_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	skb_queue_head_init(&data->weadq);
	init_waitqueue_head(&data->wead_wait);

	mutex_init(&data->open_mutex);
	INIT_DEWAYED_WOWK(&data->open_timeout, vhci_open_timeout);
	INIT_WOWK(&data->suspend_wowk, vhci_suspend_wowk);

	fiwe->pwivate_data = data;
	nonseekabwe_open(inode, fiwe);

	scheduwe_dewayed_wowk(&data->open_timeout, msecs_to_jiffies(1000));

	wetuwn 0;
}

static int vhci_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct vhci_data *data = fiwe->pwivate_data;
	stwuct hci_dev *hdev;

	cancew_dewayed_wowk_sync(&data->open_timeout);
	fwush_wowk(&data->suspend_wowk);

	hdev = data->hdev;

	if (hdev) {
		hci_unwegistew_dev(hdev);
		hci_fwee_dev(hdev);
	}

	skb_queue_puwge(&data->weadq);
	fiwe->pwivate_data = NUWW;
	kfwee(data);

	wetuwn 0;
}

static const stwuct fiwe_opewations vhci_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= vhci_wead,
	.wwite_itew	= vhci_wwite,
	.poww		= vhci_poww,
	.open		= vhci_open,
	.wewease	= vhci_wewease,
	.wwseek		= no_wwseek,
};

static stwuct miscdevice vhci_miscdev = {
	.name	= "vhci",
	.fops	= &vhci_fops,
	.minow	= VHCI_MINOW,
};
moduwe_misc_device(vhci_miscdev);

moduwe_pawam(amp, boow, 0644);
MODUWE_PAWM_DESC(amp, "Cweate AMP contwowwew device");

MODUWE_AUTHOW("Mawcew Howtmann <mawcew@howtmann.owg>");
MODUWE_DESCWIPTION("Bwuetooth viwtuaw HCI dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("devname:vhci");
MODUWE_AWIAS_MISCDEV(VHCI_MINOW);
