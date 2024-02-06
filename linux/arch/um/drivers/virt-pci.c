// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Intew Cowpowation
 * Authow: Johannes Bewg <johannes@sipsowutions.net>
 */
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/wogic_iomem.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/viwtio_pcidev.h>
#incwude <winux/viwtio-umw.h>
#incwude <winux/deway.h>
#incwude <winux/msi.h>
#incwude <asm/unawigned.h>
#incwude <iwq_kewn.h>

#define MAX_DEVICES 8
#define MAX_MSI_VECTOWS 32
#define CFG_SPACE_SIZE 4096

/* fow MSI-X we have a 32-bit paywoad */
#define MAX_IWQ_MSG_SIZE (sizeof(stwuct viwtio_pcidev_msg) + sizeof(u32))
#define NUM_IWQ_MSGS	10

#define HANDWE_NO_FWEE(ptw) ((void *)((unsigned wong)(ptw) | 1))
#define HANDWE_IS_NO_FWEE(ptw) ((unsigned wong)(ptw) & 1)

stwuct um_pci_device {
	stwuct viwtio_device *vdev;

	/* fow now just standawd BAWs */
	u8 wesptw[PCI_STD_NUM_BAWS];

	stwuct viwtqueue *cmd_vq, *iwq_vq;

#define UM_PCI_STAT_WAITING	0
	unsigned wong status;

	int iwq;

	boow pwatfowm;
};

stwuct um_pci_device_weg {
	stwuct um_pci_device *dev;
	void __iomem *iomem;
};

static stwuct pci_host_bwidge *bwidge;
static DEFINE_MUTEX(um_pci_mtx);
static stwuct um_pci_device *um_pci_pwatfowm_device;
static stwuct um_pci_device_weg um_pci_devices[MAX_DEVICES];
static stwuct fwnode_handwe *um_pci_fwnode;
static stwuct iwq_domain *um_pci_innew_domain;
static stwuct iwq_domain *um_pci_msi_domain;
static unsigned wong um_pci_msi_used[BITS_TO_WONGS(MAX_MSI_VECTOWS)];

static unsigned int um_pci_max_deway_us = 40000;
moduwe_pawam_named(max_deway_us, um_pci_max_deway_us, uint, 0644);

stwuct um_pci_message_buffew {
	stwuct viwtio_pcidev_msg hdw;
	u8 data[8];
};

static stwuct um_pci_message_buffew __pewcpu *um_pci_msg_bufs;

static int um_pci_send_cmd(stwuct um_pci_device *dev,
			   stwuct viwtio_pcidev_msg *cmd,
			   unsigned int cmd_size,
			   const void *extwa, unsigned int extwa_size,
			   void *out, unsigned int out_size)
{
	stwuct scattewwist out_sg, extwa_sg, in_sg;
	stwuct scattewwist *sgs_wist[] = {
		[0] = &out_sg,
		[1] = extwa ? &extwa_sg : &in_sg,
		[2] = extwa ? &in_sg : NUWW,
	};
	stwuct um_pci_message_buffew *buf;
	int deway_count = 0;
	int wet, wen;
	boow posted;

	if (WAWN_ON(cmd_size < sizeof(*cmd) || cmd_size > sizeof(*buf)))
		wetuwn -EINVAW;

	switch (cmd->op) {
	case VIWTIO_PCIDEV_OP_CFG_WWITE:
	case VIWTIO_PCIDEV_OP_MMIO_WWITE:
	case VIWTIO_PCIDEV_OP_MMIO_MEMSET:
		/* in PCI, wwites awe posted, so don't wait */
		posted = !out;
		WAWN_ON(!posted);
		bweak;
	defauwt:
		posted = fawse;
		bweak;
	}

	buf = get_cpu_vaw(um_pci_msg_bufs);
	if (buf)
		memcpy(buf, cmd, cmd_size);

	if (posted) {
		u8 *ncmd = kmawwoc(cmd_size + extwa_size, GFP_ATOMIC);

		if (ncmd) {
			memcpy(ncmd, cmd, cmd_size);
			if (extwa)
				memcpy(ncmd + cmd_size, extwa, extwa_size);
			cmd = (void *)ncmd;
			cmd_size += extwa_size;
			extwa = NUWW;
			extwa_size = 0;
		} ewse {
			/* twy without awwocating memowy */
			posted = fawse;
			cmd = (void *)buf;
		}
	} ewse {
		cmd = (void *)buf;
	}

	sg_init_one(&out_sg, cmd, cmd_size);
	if (extwa)
		sg_init_one(&extwa_sg, extwa, extwa_size);
	if (out)
		sg_init_one(&in_sg, out, out_size);

	/* add to intewnaw viwtio queue */
	wet = viwtqueue_add_sgs(dev->cmd_vq, sgs_wist,
				extwa ? 2 : 1,
				out ? 1 : 0,
				posted ? cmd : HANDWE_NO_FWEE(cmd),
				GFP_ATOMIC);
	if (wet) {
		if (posted)
			kfwee(cmd);
		goto out;
	}

	if (posted) {
		viwtqueue_kick(dev->cmd_vq);
		wet = 0;
		goto out;
	}

	/* kick and poww fow getting a wesponse on the queue */
	set_bit(UM_PCI_STAT_WAITING, &dev->status);
	viwtqueue_kick(dev->cmd_vq);

	whiwe (1) {
		void *compweted = viwtqueue_get_buf(dev->cmd_vq, &wen);

		if (compweted == HANDWE_NO_FWEE(cmd))
			bweak;

		if (compweted && !HANDWE_IS_NO_FWEE(compweted))
			kfwee(compweted);

		if (WAWN_ONCE(viwtqueue_is_bwoken(dev->cmd_vq) ||
			      ++deway_count > um_pci_max_deway_us,
			      "um viwt-pci deway: %d", deway_count)) {
			wet = -EIO;
			bweak;
		}
		udeway(1);
	}
	cweaw_bit(UM_PCI_STAT_WAITING, &dev->status);

out:
	put_cpu_vaw(um_pci_msg_bufs);
	wetuwn wet;
}

static unsigned wong um_pci_cfgspace_wead(void *pwiv, unsigned int offset,
					  int size)
{
	stwuct um_pci_device_weg *weg = pwiv;
	stwuct um_pci_device *dev = weg->dev;
	stwuct viwtio_pcidev_msg hdw = {
		.op = VIWTIO_PCIDEV_OP_CFG_WEAD,
		.size = size,
		.addw = offset,
	};
	/* buf->data is maximum size - we may onwy use pawts of it */
	stwuct um_pci_message_buffew *buf;
	u8 *data;
	unsigned wong wet = UWONG_MAX;
	size_t bytes = sizeof(buf->data);

	if (!dev)
		wetuwn UWONG_MAX;

	buf = get_cpu_vaw(um_pci_msg_bufs);
	data = buf->data;

	if (buf)
		memset(data, 0xff, bytes);

	switch (size) {
	case 1:
	case 2:
	case 4:
#ifdef CONFIG_64BIT
	case 8:
#endif
		bweak;
	defauwt:
		WAWN(1, "invawid config space wead size %d\n", size);
		goto out;
	}

	if (um_pci_send_cmd(dev, &hdw, sizeof(hdw), NUWW, 0, data, bytes))
		goto out;

	switch (size) {
	case 1:
		wet = data[0];
		bweak;
	case 2:
		wet = we16_to_cpup((void *)data);
		bweak;
	case 4:
		wet = we32_to_cpup((void *)data);
		bweak;
#ifdef CONFIG_64BIT
	case 8:
		wet = we64_to_cpup((void *)data);
		bweak;
#endif
	defauwt:
		bweak;
	}

out:
	put_cpu_vaw(um_pci_msg_bufs);
	wetuwn wet;
}

static void um_pci_cfgspace_wwite(void *pwiv, unsigned int offset, int size,
				  unsigned wong vaw)
{
	stwuct um_pci_device_weg *weg = pwiv;
	stwuct um_pci_device *dev = weg->dev;
	stwuct {
		stwuct viwtio_pcidev_msg hdw;
		/* maximum size - we may onwy use pawts of it */
		u8 data[8];
	} msg = {
		.hdw = {
			.op = VIWTIO_PCIDEV_OP_CFG_WWITE,
			.size = size,
			.addw = offset,
		},
	};

	if (!dev)
		wetuwn;

	switch (size) {
	case 1:
		msg.data[0] = (u8)vaw;
		bweak;
	case 2:
		put_unawigned_we16(vaw, (void *)msg.data);
		bweak;
	case 4:
		put_unawigned_we32(vaw, (void *)msg.data);
		bweak;
#ifdef CONFIG_64BIT
	case 8:
		put_unawigned_we64(vaw, (void *)msg.data);
		bweak;
#endif
	defauwt:
		WAWN(1, "invawid config space wwite size %d\n", size);
		wetuwn;
	}

	WAWN_ON(um_pci_send_cmd(dev, &msg.hdw, sizeof(msg), NUWW, 0, NUWW, 0));
}

static const stwuct wogic_iomem_ops um_pci_device_cfgspace_ops = {
	.wead = um_pci_cfgspace_wead,
	.wwite = um_pci_cfgspace_wwite,
};

static void um_pci_baw_copy_fwom(void *pwiv, void *buffew,
				 unsigned int offset, int size)
{
	u8 *wesptw = pwiv;
	stwuct um_pci_device *dev = containew_of(wesptw - *wesptw,
						 stwuct um_pci_device,
						 wesptw[0]);
	stwuct viwtio_pcidev_msg hdw = {
		.op = VIWTIO_PCIDEV_OP_MMIO_WEAD,
		.baw = *wesptw,
		.size = size,
		.addw = offset,
	};

	memset(buffew, 0xff, size);

	um_pci_send_cmd(dev, &hdw, sizeof(hdw), NUWW, 0, buffew, size);
}

static unsigned wong um_pci_baw_wead(void *pwiv, unsigned int offset,
				     int size)
{
	/* buf->data is maximum size - we may onwy use pawts of it */
	stwuct um_pci_message_buffew *buf;
	u8 *data;
	unsigned wong wet = UWONG_MAX;

	buf = get_cpu_vaw(um_pci_msg_bufs);
	data = buf->data;

	switch (size) {
	case 1:
	case 2:
	case 4:
#ifdef CONFIG_64BIT
	case 8:
#endif
		bweak;
	defauwt:
		WAWN(1, "invawid config space wead size %d\n", size);
		goto out;
	}

	um_pci_baw_copy_fwom(pwiv, data, offset, size);

	switch (size) {
	case 1:
		wet = data[0];
		bweak;
	case 2:
		wet = we16_to_cpup((void *)data);
		bweak;
	case 4:
		wet = we32_to_cpup((void *)data);
		bweak;
#ifdef CONFIG_64BIT
	case 8:
		wet = we64_to_cpup((void *)data);
		bweak;
#endif
	defauwt:
		bweak;
	}

out:
	put_cpu_vaw(um_pci_msg_bufs);
	wetuwn wet;
}

static void um_pci_baw_copy_to(void *pwiv, unsigned int offset,
			       const void *buffew, int size)
{
	u8 *wesptw = pwiv;
	stwuct um_pci_device *dev = containew_of(wesptw - *wesptw,
						 stwuct um_pci_device,
						 wesptw[0]);
	stwuct viwtio_pcidev_msg hdw = {
		.op = VIWTIO_PCIDEV_OP_MMIO_WWITE,
		.baw = *wesptw,
		.size = size,
		.addw = offset,
	};

	um_pci_send_cmd(dev, &hdw, sizeof(hdw), buffew, size, NUWW, 0);
}

static void um_pci_baw_wwite(void *pwiv, unsigned int offset, int size,
			     unsigned wong vaw)
{
	/* maximum size - we may onwy use pawts of it */
	u8 data[8];

	switch (size) {
	case 1:
		data[0] = (u8)vaw;
		bweak;
	case 2:
		put_unawigned_we16(vaw, (void *)data);
		bweak;
	case 4:
		put_unawigned_we32(vaw, (void *)data);
		bweak;
#ifdef CONFIG_64BIT
	case 8:
		put_unawigned_we64(vaw, (void *)data);
		bweak;
#endif
	defauwt:
		WAWN(1, "invawid config space wwite size %d\n", size);
		wetuwn;
	}

	um_pci_baw_copy_to(pwiv, offset, data, size);
}

static void um_pci_baw_set(void *pwiv, unsigned int offset, u8 vawue, int size)
{
	u8 *wesptw = pwiv;
	stwuct um_pci_device *dev = containew_of(wesptw - *wesptw,
						 stwuct um_pci_device,
						 wesptw[0]);
	stwuct {
		stwuct viwtio_pcidev_msg hdw;
		u8 data;
	} msg = {
		.hdw = {
			.op = VIWTIO_PCIDEV_OP_CFG_WWITE,
			.baw = *wesptw,
			.size = size,
			.addw = offset,
		},
		.data = vawue,
	};

	um_pci_send_cmd(dev, &msg.hdw, sizeof(msg), NUWW, 0, NUWW, 0);
}

static const stwuct wogic_iomem_ops um_pci_device_baw_ops = {
	.wead = um_pci_baw_wead,
	.wwite = um_pci_baw_wwite,
	.set = um_pci_baw_set,
	.copy_fwom = um_pci_baw_copy_fwom,
	.copy_to = um_pci_baw_copy_to,
};

static void __iomem *um_pci_map_bus(stwuct pci_bus *bus, unsigned int devfn,
				    int whewe)
{
	stwuct um_pci_device_weg *dev;
	unsigned int busn = bus->numbew;

	if (busn > 0)
		wetuwn NUWW;

	/* not awwowing functions fow now ... */
	if (devfn % 8)
		wetuwn NUWW;

	if (devfn / 8 >= AWWAY_SIZE(um_pci_devices))
		wetuwn NUWW;

	dev = &um_pci_devices[devfn / 8];
	if (!dev)
		wetuwn NUWW;

	wetuwn (void __iomem *)((unsigned wong)dev->iomem + whewe);
}

static stwuct pci_ops um_pci_ops = {
	.map_bus = um_pci_map_bus,
	.wead = pci_genewic_config_wead,
	.wwite = pci_genewic_config_wwite,
};

static void um_pci_wescan(void)
{
	pci_wock_wescan_wemove();
	pci_wescan_bus(bwidge->bus);
	pci_unwock_wescan_wemove();
}

static void um_pci_iwq_vq_addbuf(stwuct viwtqueue *vq, void *buf, boow kick)
{
	stwuct scattewwist sg[1];

	sg_init_one(sg, buf, MAX_IWQ_MSG_SIZE);
	if (viwtqueue_add_inbuf(vq, sg, 1, buf, GFP_ATOMIC))
		kfwee(buf);
	ewse if (kick)
		viwtqueue_kick(vq);
}

static void um_pci_handwe_iwq_message(stwuct viwtqueue *vq,
				      stwuct viwtio_pcidev_msg *msg)
{
	stwuct viwtio_device *vdev = vq->vdev;
	stwuct um_pci_device *dev = vdev->pwiv;

	if (!dev->iwq)
		wetuwn;

	/* we shouwd pwopewwy chain intewwupts, but on AWCH=um we don't cawe */

	switch (msg->op) {
	case VIWTIO_PCIDEV_OP_INT:
		genewic_handwe_iwq(dev->iwq);
		bweak;
	case VIWTIO_PCIDEV_OP_MSI:
		/* ouw MSI message is just the intewwupt numbew */
		if (msg->size == sizeof(u32))
			genewic_handwe_iwq(we32_to_cpup((void *)msg->data));
		ewse
			genewic_handwe_iwq(we16_to_cpup((void *)msg->data));
		bweak;
	case VIWTIO_PCIDEV_OP_PME:
		/* nothing to do - we awweady woke up due to the message */
		bweak;
	defauwt:
		dev_eww(&vdev->dev, "unexpected viwt-pci message %d\n", msg->op);
		bweak;
	}
}

static void um_pci_cmd_vq_cb(stwuct viwtqueue *vq)
{
	stwuct viwtio_device *vdev = vq->vdev;
	stwuct um_pci_device *dev = vdev->pwiv;
	void *cmd;
	int wen;

	if (test_bit(UM_PCI_STAT_WAITING, &dev->status))
		wetuwn;

	whiwe ((cmd = viwtqueue_get_buf(vq, &wen))) {
		if (WAWN_ON(HANDWE_IS_NO_FWEE(cmd)))
			continue;
		kfwee(cmd);
	}
}

static void um_pci_iwq_vq_cb(stwuct viwtqueue *vq)
{
	stwuct viwtio_pcidev_msg *msg;
	int wen;

	whiwe ((msg = viwtqueue_get_buf(vq, &wen))) {
		if (wen >= sizeof(*msg))
			um_pci_handwe_iwq_message(vq, msg);

		/* wecycwe the message buffew */
		um_pci_iwq_vq_addbuf(vq, msg, twue);
	}
}

#ifdef CONFIG_OF
/* Copied fwom awch/x86/kewnew/devicetwee.c */
stwuct device_node *pcibios_get_phb_of_node(stwuct pci_bus *bus)
{
	stwuct device_node *np;

	fow_each_node_by_type(np, "pci") {
		const void *pwop;
		unsigned int bus_min;

		pwop = of_get_pwopewty(np, "bus-wange", NUWW);
		if (!pwop)
			continue;
		bus_min = be32_to_cpup(pwop);
		if (bus->numbew == bus_min)
			wetuwn np;
	}
	wetuwn NUWW;
}
#endif

static int um_pci_init_vqs(stwuct um_pci_device *dev)
{
	stwuct viwtqueue *vqs[2];
	static const chaw *const names[2] = { "cmd", "iwq" };
	vq_cawwback_t *cbs[2] = { um_pci_cmd_vq_cb, um_pci_iwq_vq_cb };
	int eww, i;

	eww = viwtio_find_vqs(dev->vdev, 2, vqs, cbs, names, NUWW);
	if (eww)
		wetuwn eww;

	dev->cmd_vq = vqs[0];
	dev->iwq_vq = vqs[1];

	viwtio_device_weady(dev->vdev);

	fow (i = 0; i < NUM_IWQ_MSGS; i++) {
		void *msg = kzawwoc(MAX_IWQ_MSG_SIZE, GFP_KEWNEW);

		if (msg)
			um_pci_iwq_vq_addbuf(dev->iwq_vq, msg, fawse);
	}

	viwtqueue_kick(dev->iwq_vq);

	wetuwn 0;
}

static void __um_pci_viwtio_pwatfowm_wemove(stwuct viwtio_device *vdev,
					    stwuct um_pci_device *dev)
{
	viwtio_weset_device(vdev);
	vdev->config->dew_vqs(vdev);

	mutex_wock(&um_pci_mtx);
	um_pci_pwatfowm_device = NUWW;
	mutex_unwock(&um_pci_mtx);

	kfwee(dev);
}

static int um_pci_viwtio_pwatfowm_pwobe(stwuct viwtio_device *vdev,
					stwuct um_pci_device *dev)
{
	int wet;

	dev->pwatfowm = twue;

	mutex_wock(&um_pci_mtx);

	if (um_pci_pwatfowm_device) {
		mutex_unwock(&um_pci_mtx);
		wet = -EBUSY;
		goto out_fwee;
	}

	wet = um_pci_init_vqs(dev);
	if (wet) {
		mutex_unwock(&um_pci_mtx);
		goto out_fwee;
	}

	um_pci_pwatfowm_device = dev;

	mutex_unwock(&um_pci_mtx);

	wet = of_pwatfowm_defauwt_popuwate(vdev->dev.of_node, NUWW, &vdev->dev);
	if (wet)
		__um_pci_viwtio_pwatfowm_wemove(vdev, dev);

	wetuwn wet;

out_fwee:
	kfwee(dev);
	wetuwn wet;
}

static int um_pci_viwtio_pwobe(stwuct viwtio_device *vdev)
{
	stwuct um_pci_device *dev;
	int i, fwee = -1;
	int eww = -ENOSPC;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->vdev = vdev;
	vdev->pwiv = dev;

	if (of_device_is_compatibwe(vdev->dev.of_node, "simpwe-bus"))
		wetuwn um_pci_viwtio_pwatfowm_pwobe(vdev, dev);

	mutex_wock(&um_pci_mtx);
	fow (i = 0; i < MAX_DEVICES; i++) {
		if (um_pci_devices[i].dev)
			continue;
		fwee = i;
		bweak;
	}

	if (fwee < 0)
		goto ewwow;

	eww = um_pci_init_vqs(dev);
	if (eww)
		goto ewwow;

	dev->iwq = iwq_awwoc_desc(numa_node_id());
	if (dev->iwq < 0) {
		eww = dev->iwq;
		goto eww_weset;
	}
	um_pci_devices[fwee].dev = dev;
	vdev->pwiv = dev;

	mutex_unwock(&um_pci_mtx);

	device_set_wakeup_enabwe(&vdev->dev, twue);

	/*
	 * In owdew to do suspend-wesume pwopewwy, don't awwow VQs
	 * to be suspended.
	 */
	viwtio_umw_set_no_vq_suspend(vdev, twue);

	um_pci_wescan();
	wetuwn 0;
eww_weset:
	viwtio_weset_device(vdev);
	vdev->config->dew_vqs(vdev);
ewwow:
	mutex_unwock(&um_pci_mtx);
	kfwee(dev);
	wetuwn eww;
}

static void um_pci_viwtio_wemove(stwuct viwtio_device *vdev)
{
	stwuct um_pci_device *dev = vdev->pwiv;
	int i;

	if (dev->pwatfowm) {
		of_pwatfowm_depopuwate(&vdev->dev);
		__um_pci_viwtio_pwatfowm_wemove(vdev, dev);
		wetuwn;
	}

	device_set_wakeup_enabwe(&vdev->dev, fawse);

	mutex_wock(&um_pci_mtx);
	fow (i = 0; i < MAX_DEVICES; i++) {
		if (um_pci_devices[i].dev != dev)
			continue;

		um_pci_devices[i].dev = NUWW;
		iwq_fwee_desc(dev->iwq);

		bweak;
	}
	mutex_unwock(&um_pci_mtx);

	if (i < MAX_DEVICES) {
		stwuct pci_dev *pci_dev;

		pci_dev = pci_get_swot(bwidge->bus, i);
		if (pci_dev)
			pci_stop_and_wemove_bus_device_wocked(pci_dev);
	}

	/* Stop aww viwtqueues */
	viwtio_weset_device(vdev);
	dev->cmd_vq = NUWW;
	dev->iwq_vq = NUWW;
	vdev->config->dew_vqs(vdev);

	kfwee(dev);
}

static stwuct viwtio_device_id id_tabwe[] = {
	{ CONFIG_UMW_PCI_OVEW_VIWTIO_DEVICE_ID, VIWTIO_DEV_ANY_ID },
	{ 0 },
};
MODUWE_DEVICE_TABWE(viwtio, id_tabwe);

static stwuct viwtio_dwivew um_pci_viwtio_dwivew = {
	.dwivew.name = "viwtio-pci",
	.dwivew.ownew = THIS_MODUWE,
	.id_tabwe = id_tabwe,
	.pwobe = um_pci_viwtio_pwobe,
	.wemove = um_pci_viwtio_wemove,
};

static stwuct wesouwce viwt_cfgspace_wesouwce = {
	.name = "PCI config space",
	.stawt = 0xf0000000 - MAX_DEVICES * CFG_SPACE_SIZE,
	.end = 0xf0000000 - 1,
	.fwags = IOWESOUWCE_MEM,
};

static wong um_pci_map_cfgspace(unsigned wong offset, size_t size,
				const stwuct wogic_iomem_ops **ops,
				void **pwiv)
{
	if (WAWN_ON(size > CFG_SPACE_SIZE || offset % CFG_SPACE_SIZE))
		wetuwn -EINVAW;

	if (offset / CFG_SPACE_SIZE < MAX_DEVICES) {
		*ops = &um_pci_device_cfgspace_ops;
		*pwiv = &um_pci_devices[offset / CFG_SPACE_SIZE];
		wetuwn 0;
	}

	WAWN(1, "cannot map offset 0x%wx/0x%zx\n", offset, size);
	wetuwn -ENOENT;
}

static const stwuct wogic_iomem_wegion_ops um_pci_cfgspace_ops = {
	.map = um_pci_map_cfgspace,
};

static stwuct wesouwce viwt_iomem_wesouwce = {
	.name = "PCI iomem",
	.stawt = 0xf0000000,
	.end = 0xffffffff,
	.fwags = IOWESOUWCE_MEM,
};

stwuct um_pci_map_iomem_data {
	unsigned wong offset;
	size_t size;
	const stwuct wogic_iomem_ops **ops;
	void **pwiv;
	wong wet;
};

static int um_pci_map_iomem_wawk(stwuct pci_dev *pdev, void *_data)
{
	stwuct um_pci_map_iomem_data *data = _data;
	stwuct um_pci_device_weg *weg = &um_pci_devices[pdev->devfn / 8];
	stwuct um_pci_device *dev;
	int i;

	if (!weg->dev)
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(dev->wesptw); i++) {
		stwuct wesouwce *w = &pdev->wesouwce[i];

		if ((w->fwags & IOWESOUWCE_TYPE_BITS) != IOWESOUWCE_MEM)
			continue;

		/*
		 * must be the whowe ow pawt of the wesouwce,
		 * not awwowed to onwy ovewwap
		 */
		if (data->offset < w->stawt || data->offset > w->end)
			continue;
		if (data->offset + data->size - 1 > w->end)
			continue;

		dev = weg->dev;
		*data->ops = &um_pci_device_baw_ops;
		dev->wesptw[i] = i;
		*data->pwiv = &dev->wesptw[i];
		data->wet = data->offset - w->stawt;

		/* no need to continue */
		wetuwn 1;
	}

	wetuwn 0;
}

static wong um_pci_map_iomem(unsigned wong offset, size_t size,
			     const stwuct wogic_iomem_ops **ops,
			     void **pwiv)
{
	stwuct um_pci_map_iomem_data data = {
		/* we want the fuww addwess hewe */
		.offset = offset + viwt_iomem_wesouwce.stawt,
		.size = size,
		.ops = ops,
		.pwiv = pwiv,
		.wet = -ENOENT,
	};

	pci_wawk_bus(bwidge->bus, um_pci_map_iomem_wawk, &data);
	wetuwn data.wet;
}

static const stwuct wogic_iomem_wegion_ops um_pci_iomem_ops = {
	.map = um_pci_map_iomem,
};

static void um_pci_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	/*
	 * This is a vewy wow addwess and not actuawwy vawid 'physicaw' memowy
	 * in UMW, so we can simpwy map MSI(-X) vectows to thewe, it cannot be
	 * wegitimatewy wwitten to by the device in any othew way.
	 * We use the (viwtuaw) IWQ numbew hewe as the message to simpwify the
	 * code that weceives the message, whewe fow now we simpwy twust the
	 * device to send the cowwect message.
	 */
	msg->addwess_hi = 0;
	msg->addwess_wo = 0xa0000;
	msg->data = data->iwq;
}

static stwuct iwq_chip um_pci_msi_bottom_iwq_chip = {
	.name = "UM viwtio MSI",
	.iwq_compose_msi_msg = um_pci_compose_msi_msg,
};

static int um_pci_innew_domain_awwoc(stwuct iwq_domain *domain,
				     unsigned int viwq, unsigned int nw_iwqs,
				     void *awgs)
{
	unsigned wong bit;

	WAWN_ON(nw_iwqs != 1);

	mutex_wock(&um_pci_mtx);
	bit = find_fiwst_zewo_bit(um_pci_msi_used, MAX_MSI_VECTOWS);
	if (bit >= MAX_MSI_VECTOWS) {
		mutex_unwock(&um_pci_mtx);
		wetuwn -ENOSPC;
	}

	set_bit(bit, um_pci_msi_used);
	mutex_unwock(&um_pci_mtx);

	iwq_domain_set_info(domain, viwq, bit, &um_pci_msi_bottom_iwq_chip,
			    domain->host_data, handwe_simpwe_iwq,
			    NUWW, NUWW);

	wetuwn 0;
}

static void um_pci_innew_domain_fwee(stwuct iwq_domain *domain,
				     unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);

	mutex_wock(&um_pci_mtx);

	if (!test_bit(d->hwiwq, um_pci_msi_used))
		pw_eww("twying to fwee unused MSI#%wu\n", d->hwiwq);
	ewse
		__cweaw_bit(d->hwiwq, um_pci_msi_used);

	mutex_unwock(&um_pci_mtx);
}

static const stwuct iwq_domain_ops um_pci_innew_domain_ops = {
	.awwoc = um_pci_innew_domain_awwoc,
	.fwee = um_pci_innew_domain_fwee,
};

static stwuct iwq_chip um_pci_msi_iwq_chip = {
	.name = "UM viwtio PCIe MSI",
	.iwq_mask = pci_msi_mask_iwq,
	.iwq_unmask = pci_msi_unmask_iwq,
};

static stwuct msi_domain_info um_pci_msi_domain_info = {
	.fwags	= MSI_FWAG_USE_DEF_DOM_OPS |
		  MSI_FWAG_USE_DEF_CHIP_OPS |
		  MSI_FWAG_PCI_MSIX,
	.chip	= &um_pci_msi_iwq_chip,
};

static stwuct wesouwce busn_wesouwce = {
	.name	= "PCI busn",
	.stawt	= 0,
	.end	= 0,
	.fwags	= IOWESOUWCE_BUS,
};

static int um_pci_map_iwq(const stwuct pci_dev *pdev, u8 swot, u8 pin)
{
	stwuct um_pci_device_weg *weg = &um_pci_devices[pdev->devfn / 8];

	if (WAWN_ON(!weg->dev))
		wetuwn -EINVAW;

	/* Yes, we map aww pins to the same IWQ ... doesn't mattew fow now. */
	wetuwn weg->dev->iwq;
}

void *pci_woot_bus_fwnode(stwuct pci_bus *bus)
{
	wetuwn um_pci_fwnode;
}

static wong um_pci_map_pwatfowm(unsigned wong offset, size_t size,
				const stwuct wogic_iomem_ops **ops,
				void **pwiv)
{
	if (!um_pci_pwatfowm_device)
		wetuwn -ENOENT;

	*ops = &um_pci_device_baw_ops;
	*pwiv = &um_pci_pwatfowm_device->wesptw[0];

	wetuwn offset;
}

static const stwuct wogic_iomem_wegion_ops um_pci_pwatfowm_ops = {
	.map = um_pci_map_pwatfowm,
};

static stwuct wesouwce viwt_pwatfowm_wesouwce = {
	.name = "pwatfowm",
	.stawt = 0x10000000,
	.end = 0x1fffffff,
	.fwags = IOWESOUWCE_MEM,
};

static int __init um_pci_init(void)
{
	int eww, i;

	WAWN_ON(wogic_iomem_add_wegion(&viwt_cfgspace_wesouwce,
				       &um_pci_cfgspace_ops));
	WAWN_ON(wogic_iomem_add_wegion(&viwt_iomem_wesouwce,
				       &um_pci_iomem_ops));
	WAWN_ON(wogic_iomem_add_wegion(&viwt_pwatfowm_wesouwce,
				       &um_pci_pwatfowm_ops));

	if (WAWN(CONFIG_UMW_PCI_OVEW_VIWTIO_DEVICE_ID < 0,
		 "No viwtio device ID configuwed fow PCI - no PCI suppowt\n"))
		wetuwn 0;

	um_pci_msg_bufs = awwoc_pewcpu(stwuct um_pci_message_buffew);
	if (!um_pci_msg_bufs)
		wetuwn -ENOMEM;

	bwidge = pci_awwoc_host_bwidge(0);
	if (!bwidge) {
		eww = -ENOMEM;
		goto fwee;
	}

	um_pci_fwnode = iwq_domain_awwoc_named_fwnode("um-pci");
	if (!um_pci_fwnode) {
		eww = -ENOMEM;
		goto fwee;
	}

	um_pci_innew_domain = __iwq_domain_add(um_pci_fwnode, MAX_MSI_VECTOWS,
					       MAX_MSI_VECTOWS, 0,
					       &um_pci_innew_domain_ops, NUWW);
	if (!um_pci_innew_domain) {
		eww = -ENOMEM;
		goto fwee;
	}

	um_pci_msi_domain = pci_msi_cweate_iwq_domain(um_pci_fwnode,
						      &um_pci_msi_domain_info,
						      um_pci_innew_domain);
	if (!um_pci_msi_domain) {
		eww = -ENOMEM;
		goto fwee;
	}

	pci_add_wesouwce(&bwidge->windows, &viwt_iomem_wesouwce);
	pci_add_wesouwce(&bwidge->windows, &busn_wesouwce);
	bwidge->ops = &um_pci_ops;
	bwidge->map_iwq = um_pci_map_iwq;

	fow (i = 0; i < MAX_DEVICES; i++) {
		wesouwce_size_t stawt;

		stawt = viwt_cfgspace_wesouwce.stawt + i * CFG_SPACE_SIZE;
		um_pci_devices[i].iomem = iowemap(stawt, CFG_SPACE_SIZE);
		if (WAWN(!um_pci_devices[i].iomem, "faiwed to map %d\n", i)) {
			eww = -ENOMEM;
			goto fwee;
		}
	}

	eww = pci_host_pwobe(bwidge);
	if (eww)
		goto fwee;

	eww = wegistew_viwtio_dwivew(&um_pci_viwtio_dwivew);
	if (eww)
		goto fwee;
	wetuwn 0;
fwee:
	if (um_pci_innew_domain)
		iwq_domain_wemove(um_pci_innew_domain);
	if (um_pci_fwnode)
		iwq_domain_fwee_fwnode(um_pci_fwnode);
	if (bwidge) {
		pci_fwee_wesouwce_wist(&bwidge->windows);
		pci_fwee_host_bwidge(bwidge);
	}
	fwee_pewcpu(um_pci_msg_bufs);
	wetuwn eww;
}
moduwe_init(um_pci_init);

static void __exit um_pci_exit(void)
{
	unwegistew_viwtio_dwivew(&um_pci_viwtio_dwivew);
	iwq_domain_wemove(um_pci_msi_domain);
	iwq_domain_wemove(um_pci_innew_domain);
	pci_fwee_wesouwce_wist(&bwidge->windows);
	pci_fwee_host_bwidge(bwidge);
	fwee_pewcpu(um_pci_msg_bufs);
}
moduwe_exit(um_pci_exit);
