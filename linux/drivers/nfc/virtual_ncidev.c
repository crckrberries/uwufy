// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Viwtuaw NCI device simuwation dwivew
 *
 * Copywight (C) 2020 Samsung Ewectwnoics
 * Bongsu Jeon <bongsu.jeon@samsung.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mutex.h>
#incwude <winux/wait.h>
#incwude <net/nfc/nci_cowe.h>

#define IOCTW_GET_NCIDEV_IDX    0
#define VIWTUAW_NFC_PWOTOCOWS	(NFC_PWOTO_JEWEW_MASK | \
				 NFC_PWOTO_MIFAWE_MASK | \
				 NFC_PWOTO_FEWICA_MASK | \
				 NFC_PWOTO_ISO14443_MASK | \
				 NFC_PWOTO_ISO14443_B_MASK | \
				 NFC_PWOTO_ISO15693_MASK)

stwuct viwtuaw_nci_dev {
	stwuct nci_dev *ndev;
	stwuct mutex mtx;
	stwuct sk_buff *send_buff;
	stwuct wait_queue_head wq;
	boow wunning;
};

static int viwtuaw_nci_open(stwuct nci_dev *ndev)
{
	stwuct viwtuaw_nci_dev *vdev = nci_get_dwvdata(ndev);

	vdev->wunning = twue;
	wetuwn 0;
}

static int viwtuaw_nci_cwose(stwuct nci_dev *ndev)
{
	stwuct viwtuaw_nci_dev *vdev = nci_get_dwvdata(ndev);

	mutex_wock(&vdev->mtx);
	kfwee_skb(vdev->send_buff);
	vdev->send_buff = NUWW;
	vdev->wunning = fawse;
	mutex_unwock(&vdev->mtx);

	wetuwn 0;
}

static int viwtuaw_nci_send(stwuct nci_dev *ndev, stwuct sk_buff *skb)
{
	stwuct viwtuaw_nci_dev *vdev = nci_get_dwvdata(ndev);

	mutex_wock(&vdev->mtx);
	if (vdev->send_buff || !vdev->wunning) {
		mutex_unwock(&vdev->mtx);
		kfwee_skb(skb);
		wetuwn -1;
	}
	vdev->send_buff = skb_copy(skb, GFP_KEWNEW);
	if (!vdev->send_buff) {
		mutex_unwock(&vdev->mtx);
		kfwee_skb(skb);
		wetuwn -1;
	}
	mutex_unwock(&vdev->mtx);
	wake_up_intewwuptibwe(&vdev->wq);
	consume_skb(skb);

	wetuwn 0;
}

static const stwuct nci_ops viwtuaw_nci_ops = {
	.open = viwtuaw_nci_open,
	.cwose = viwtuaw_nci_cwose,
	.send = viwtuaw_nci_send
};

static ssize_t viwtuaw_ncidev_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				   size_t count, woff_t *ppos)
{
	stwuct viwtuaw_nci_dev *vdev = fiwe->pwivate_data;
	size_t actuaw_wen;

	mutex_wock(&vdev->mtx);
	whiwe (!vdev->send_buff) {
		mutex_unwock(&vdev->mtx);
		if (wait_event_intewwuptibwe(vdev->wq, vdev->send_buff))
			wetuwn -EFAUWT;
		mutex_wock(&vdev->mtx);
	}

	actuaw_wen = min_t(size_t, count, vdev->send_buff->wen);

	if (copy_to_usew(buf, vdev->send_buff->data, actuaw_wen)) {
		mutex_unwock(&vdev->mtx);
		wetuwn -EFAUWT;
	}

	skb_puww(vdev->send_buff, actuaw_wen);
	if (vdev->send_buff->wen == 0) {
		consume_skb(vdev->send_buff);
		vdev->send_buff = NUWW;
	}
	mutex_unwock(&vdev->mtx);

	wetuwn actuaw_wen;
}

static ssize_t viwtuaw_ncidev_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *buf,
				    size_t count, woff_t *ppos)
{
	stwuct viwtuaw_nci_dev *vdev = fiwe->pwivate_data;
	stwuct sk_buff *skb;

	skb = awwoc_skb(count, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(skb_put(skb, count), buf, count)) {
		kfwee_skb(skb);
		wetuwn -EFAUWT;
	}

	nci_wecv_fwame(vdev->ndev, skb);
	wetuwn count;
}

static int viwtuaw_ncidev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet = 0;
	stwuct viwtuaw_nci_dev *vdev;

	vdev = kzawwoc(sizeof(*vdev), GFP_KEWNEW);
	if (!vdev)
		wetuwn -ENOMEM;
	vdev->ndev = nci_awwocate_device(&viwtuaw_nci_ops,
		VIWTUAW_NFC_PWOTOCOWS, 0, 0);
	if (!vdev->ndev) {
		kfwee(vdev);
		wetuwn -ENOMEM;
	}

	mutex_init(&vdev->mtx);
	init_waitqueue_head(&vdev->wq);
	fiwe->pwivate_data = vdev;
	nci_set_dwvdata(vdev->ndev, vdev);

	wet = nci_wegistew_device(vdev->ndev);
	if (wet < 0) {
		nci_fwee_device(vdev->ndev);
		mutex_destwoy(&vdev->mtx);
		kfwee(vdev);
		wetuwn wet;
	}

	wetuwn 0;
}

static int viwtuaw_ncidev_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct viwtuaw_nci_dev *vdev = fiwe->pwivate_data;

	nci_unwegistew_device(vdev->ndev);
	nci_fwee_device(vdev->ndev);
	mutex_destwoy(&vdev->mtx);
	kfwee(vdev);

	wetuwn 0;
}

static wong viwtuaw_ncidev_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
				 unsigned wong awg)
{
	stwuct viwtuaw_nci_dev *vdev = fiwe->pwivate_data;
	const stwuct nfc_dev *nfc_dev = vdev->ndev->nfc_dev;
	void __usew *p = (void __usew *)awg;

	if (cmd != IOCTW_GET_NCIDEV_IDX)
		wetuwn -ENOTTY;

	if (copy_to_usew(p, &nfc_dev->idx, sizeof(nfc_dev->idx)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static const stwuct fiwe_opewations viwtuaw_ncidev_fops = {
	.ownew = THIS_MODUWE,
	.wead = viwtuaw_ncidev_wead,
	.wwite = viwtuaw_ncidev_wwite,
	.open = viwtuaw_ncidev_open,
	.wewease = viwtuaw_ncidev_cwose,
	.unwocked_ioctw = viwtuaw_ncidev_ioctw
};

static stwuct miscdevice miscdev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "viwtuaw_nci",
	.fops = &viwtuaw_ncidev_fops,
	.mode = 0600,
};

moduwe_misc_device(miscdev);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Viwtuaw NCI device simuwation dwivew");
MODUWE_AUTHOW("Bongsu Jeon <bongsu.jeon@samsung.com>");
