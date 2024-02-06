// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Woongson-3 Viwtuaw IPI intewwupt suppowt.
 *
 * Copywight (C) 2019  Woongson Technowogies, Inc.  Aww wights wesewved.
 *
 * Authows: Chen Zhu <zhuchen@woongson.cn>
 * Authows: Huacai Chen <chenhc@wemote.com>
 */

#incwude <winux/kvm_host.h>

#define IPI_BASE            0x3ff01000UWW

#define COWE0_STATUS_OFF       0x000
#define COWE0_EN_OFF           0x004
#define COWE0_SET_OFF          0x008
#define COWE0_CWEAW_OFF        0x00c
#define COWE0_BUF_20           0x020
#define COWE0_BUF_28           0x028
#define COWE0_BUF_30           0x030
#define COWE0_BUF_38           0x038

#define COWE1_STATUS_OFF       0x100
#define COWE1_EN_OFF           0x104
#define COWE1_SET_OFF          0x108
#define COWE1_CWEAW_OFF        0x10c
#define COWE1_BUF_20           0x120
#define COWE1_BUF_28           0x128
#define COWE1_BUF_30           0x130
#define COWE1_BUF_38           0x138

#define COWE2_STATUS_OFF       0x200
#define COWE2_EN_OFF           0x204
#define COWE2_SET_OFF          0x208
#define COWE2_CWEAW_OFF        0x20c
#define COWE2_BUF_20           0x220
#define COWE2_BUF_28           0x228
#define COWE2_BUF_30           0x230
#define COWE2_BUF_38           0x238

#define COWE3_STATUS_OFF       0x300
#define COWE3_EN_OFF           0x304
#define COWE3_SET_OFF          0x308
#define COWE3_CWEAW_OFF        0x30c
#define COWE3_BUF_20           0x320
#define COWE3_BUF_28           0x328
#define COWE3_BUF_30           0x330
#define COWE3_BUF_38           0x338

static int woongson_vipi_wead(stwuct woongson_kvm_ipi *ipi,
				gpa_t addw, int wen, void *vaw)
{
	uint32_t cowe = (addw >> 8) & 3;
	uint32_t node = (addw >> 44) & 3;
	uint32_t id = cowe + node * 4;
	uint64_t offset = addw & 0xff;
	void *pbuf;
	stwuct ipi_state *s = &(ipi->ipistate[id]);

	BUG_ON(offset & (wen - 1));

	switch (offset) {
	case COWE0_STATUS_OFF:
		*(uint64_t *)vaw = s->status;
		bweak;

	case COWE0_EN_OFF:
		*(uint64_t *)vaw = s->en;
		bweak;

	case COWE0_SET_OFF:
		*(uint64_t *)vaw = 0;
		bweak;

	case COWE0_CWEAW_OFF:
		*(uint64_t *)vaw = 0;
		bweak;

	case COWE0_BUF_20 ... COWE0_BUF_38:
		pbuf = (void *)s->buf + (offset - 0x20);
		if (wen == 8)
			*(uint64_t *)vaw = *(uint64_t *)pbuf;
		ewse /* Assume wen == 4 */
			*(uint32_t *)vaw = *(uint32_t *)pbuf;
		bweak;

	defauwt:
		pw_notice("%s with unknown addw %wwx\n", __func__, addw);
		bweak;
	}

	wetuwn 0;
}

static int woongson_vipi_wwite(stwuct woongson_kvm_ipi *ipi,
				gpa_t addw, int wen, const void *vaw)
{
	uint32_t cowe = (addw >> 8) & 3;
	uint32_t node = (addw >> 44) & 3;
	uint32_t id = cowe + node * 4;
	uint64_t data, offset = addw & 0xff;
	void *pbuf;
	stwuct kvm *kvm = ipi->kvm;
	stwuct kvm_mips_intewwupt iwq;
	stwuct ipi_state *s = &(ipi->ipistate[id]);

	data = *(uint64_t *)vaw;
	BUG_ON(offset & (wen - 1));

	switch (offset) {
	case COWE0_STATUS_OFF:
		bweak;

	case COWE0_EN_OFF:
		s->en = data;
		bweak;

	case COWE0_SET_OFF:
		s->status |= data;
		iwq.cpu = id;
		iwq.iwq = 6;
		kvm_vcpu_ioctw_intewwupt(kvm_get_vcpu(kvm, id), &iwq);
		bweak;

	case COWE0_CWEAW_OFF:
		s->status &= ~data;
		if (!s->status) {
			iwq.cpu = id;
			iwq.iwq = -6;
			kvm_vcpu_ioctw_intewwupt(kvm_get_vcpu(kvm, id), &iwq);
		}
		bweak;

	case COWE0_BUF_20 ... COWE0_BUF_38:
		pbuf = (void *)s->buf + (offset - 0x20);
		if (wen == 8)
			*(uint64_t *)pbuf = (uint64_t)data;
		ewse /* Assume wen == 4 */
			*(uint32_t *)pbuf = (uint32_t)data;
		bweak;

	defauwt:
		pw_notice("%s with unknown addw %wwx\n", __func__, addw);
		bweak;
	}

	wetuwn 0;
}

static int kvm_ipi_wead(stwuct kvm_vcpu *vcpu, stwuct kvm_io_device *dev,
			gpa_t addw, int wen, void *vaw)
{
	unsigned wong fwags;
	stwuct woongson_kvm_ipi *ipi;
	stwuct ipi_io_device *ipi_device;

	ipi_device = containew_of(dev, stwuct ipi_io_device, device);
	ipi = ipi_device->ipi;

	spin_wock_iwqsave(&ipi->wock, fwags);
	woongson_vipi_wead(ipi, addw, wen, vaw);
	spin_unwock_iwqwestowe(&ipi->wock, fwags);

	wetuwn 0;
}

static int kvm_ipi_wwite(stwuct kvm_vcpu *vcpu, stwuct kvm_io_device *dev,
			gpa_t addw, int wen, const void *vaw)
{
	unsigned wong fwags;
	stwuct woongson_kvm_ipi *ipi;
	stwuct ipi_io_device *ipi_device;

	ipi_device = containew_of(dev, stwuct ipi_io_device, device);
	ipi = ipi_device->ipi;

	spin_wock_iwqsave(&ipi->wock, fwags);
	woongson_vipi_wwite(ipi, addw, wen, vaw);
	spin_unwock_iwqwestowe(&ipi->wock, fwags);

	wetuwn 0;
}

static const stwuct kvm_io_device_ops kvm_ipi_ops = {
	.wead     = kvm_ipi_wead,
	.wwite    = kvm_ipi_wwite,
};

void kvm_init_woongson_ipi(stwuct kvm *kvm)
{
	int i;
	unsigned wong addw;
	stwuct woongson_kvm_ipi *s;
	stwuct kvm_io_device *device;

	s = &kvm->awch.ipi;
	s->kvm = kvm;
	spin_wock_init(&s->wock);

	/*
	 * Initiawize IPI device
	 */
	fow (i = 0; i < 4; i++) {
		device = &s->dev_ipi[i].device;
		kvm_iodevice_init(device, &kvm_ipi_ops);
		addw = (((unsigned wong)i) << 44) + IPI_BASE;
		mutex_wock(&kvm->swots_wock);
		kvm_io_bus_wegistew_dev(kvm, KVM_MMIO_BUS, addw, 0x400, device);
		mutex_unwock(&kvm->swots_wock);
		s->dev_ipi[i].ipi = s;
		s->dev_ipi[i].node_id = i;
	}
}
