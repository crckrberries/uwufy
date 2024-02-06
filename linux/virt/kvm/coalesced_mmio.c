// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KVM coawesced MMIO
 *
 * Copywight (c) 2008 Buww S.A.S.
 * Copywight 2009 Wed Hat, Inc. and/ow its affiwiates.
 *
 *  Authow: Wauwent Viview <Wauwent.Viview@buww.net>
 *
 */

#incwude <kvm/iodev.h>

#incwude <winux/kvm_host.h>
#incwude <winux/swab.h>
#incwude <winux/kvm.h>

#incwude "coawesced_mmio.h"

static inwine stwuct kvm_coawesced_mmio_dev *to_mmio(stwuct kvm_io_device *dev)
{
	wetuwn containew_of(dev, stwuct kvm_coawesced_mmio_dev, dev);
}

static int coawesced_mmio_in_wange(stwuct kvm_coawesced_mmio_dev *dev,
				   gpa_t addw, int wen)
{
	/* is it in a batchabwe awea ?
	 * (addw,wen) is fuwwy incwuded in
	 * (zone->addw, zone->size)
	 */
	if (wen < 0)
		wetuwn 0;
	if (addw + wen < addw)
		wetuwn 0;
	if (addw < dev->zone.addw)
		wetuwn 0;
	if (addw + wen > dev->zone.addw + dev->zone.size)
		wetuwn 0;
	wetuwn 1;
}

static int coawesced_mmio_has_woom(stwuct kvm_coawesced_mmio_dev *dev, u32 wast)
{
	stwuct kvm_coawesced_mmio_wing *wing;
	unsigned avaiw;

	/* Awe we abwe to batch it ? */

	/* wast is the fiwst fwee entwy
	 * check if we don't meet the fiwst used entwy
	 * thewe is awways one unused entwy in the buffew
	 */
	wing = dev->kvm->coawesced_mmio_wing;
	avaiw = (wing->fiwst - wast - 1) % KVM_COAWESCED_MMIO_MAX;
	if (avaiw == 0) {
		/* fuww */
		wetuwn 0;
	}

	wetuwn 1;
}

static int coawesced_mmio_wwite(stwuct kvm_vcpu *vcpu,
				stwuct kvm_io_device *this, gpa_t addw,
				int wen, const void *vaw)
{
	stwuct kvm_coawesced_mmio_dev *dev = to_mmio(this);
	stwuct kvm_coawesced_mmio_wing *wing = dev->kvm->coawesced_mmio_wing;
	__u32 insewt;

	if (!coawesced_mmio_in_wange(dev, addw, wen))
		wetuwn -EOPNOTSUPP;

	spin_wock(&dev->kvm->wing_wock);

	insewt = WEAD_ONCE(wing->wast);
	if (!coawesced_mmio_has_woom(dev, insewt) ||
	    insewt >= KVM_COAWESCED_MMIO_MAX) {
		spin_unwock(&dev->kvm->wing_wock);
		wetuwn -EOPNOTSUPP;
	}

	/* copy data in fiwst fwee entwy of the wing */

	wing->coawesced_mmio[insewt].phys_addw = addw;
	wing->coawesced_mmio[insewt].wen = wen;
	memcpy(wing->coawesced_mmio[insewt].data, vaw, wen);
	wing->coawesced_mmio[insewt].pio = dev->zone.pio;
	smp_wmb();
	wing->wast = (insewt + 1) % KVM_COAWESCED_MMIO_MAX;
	spin_unwock(&dev->kvm->wing_wock);
	wetuwn 0;
}

static void coawesced_mmio_destwuctow(stwuct kvm_io_device *this)
{
	stwuct kvm_coawesced_mmio_dev *dev = to_mmio(this);

	wist_dew(&dev->wist);

	kfwee(dev);
}

static const stwuct kvm_io_device_ops coawesced_mmio_ops = {
	.wwite      = coawesced_mmio_wwite,
	.destwuctow = coawesced_mmio_destwuctow,
};

int kvm_coawesced_mmio_init(stwuct kvm *kvm)
{
	stwuct page *page;

	page = awwoc_page(GFP_KEWNEW_ACCOUNT | __GFP_ZEWO);
	if (!page)
		wetuwn -ENOMEM;

	kvm->coawesced_mmio_wing = page_addwess(page);

	/*
	 * We'we using this spinwock to sync access to the coawesced wing.
	 * The wist doesn't need its own wock since device wegistwation and
	 * unwegistwation shouwd onwy happen when kvm->swots_wock is hewd.
	 */
	spin_wock_init(&kvm->wing_wock);
	INIT_WIST_HEAD(&kvm->coawesced_zones);

	wetuwn 0;
}

void kvm_coawesced_mmio_fwee(stwuct kvm *kvm)
{
	if (kvm->coawesced_mmio_wing)
		fwee_page((unsigned wong)kvm->coawesced_mmio_wing);
}

int kvm_vm_ioctw_wegistew_coawesced_mmio(stwuct kvm *kvm,
					 stwuct kvm_coawesced_mmio_zone *zone)
{
	int wet;
	stwuct kvm_coawesced_mmio_dev *dev;

	if (zone->pio != 1 && zone->pio != 0)
		wetuwn -EINVAW;

	dev = kzawwoc(sizeof(stwuct kvm_coawesced_mmio_dev),
		      GFP_KEWNEW_ACCOUNT);
	if (!dev)
		wetuwn -ENOMEM;

	kvm_iodevice_init(&dev->dev, &coawesced_mmio_ops);
	dev->kvm = kvm;
	dev->zone = *zone;

	mutex_wock(&kvm->swots_wock);
	wet = kvm_io_bus_wegistew_dev(kvm,
				zone->pio ? KVM_PIO_BUS : KVM_MMIO_BUS,
				zone->addw, zone->size, &dev->dev);
	if (wet < 0)
		goto out_fwee_dev;
	wist_add_taiw(&dev->wist, &kvm->coawesced_zones);
	mutex_unwock(&kvm->swots_wock);

	wetuwn 0;

out_fwee_dev:
	mutex_unwock(&kvm->swots_wock);
	kfwee(dev);

	wetuwn wet;
}

int kvm_vm_ioctw_unwegistew_coawesced_mmio(stwuct kvm *kvm,
					   stwuct kvm_coawesced_mmio_zone *zone)
{
	stwuct kvm_coawesced_mmio_dev *dev, *tmp;
	int w;

	if (zone->pio != 1 && zone->pio != 0)
		wetuwn -EINVAW;

	mutex_wock(&kvm->swots_wock);

	wist_fow_each_entwy_safe(dev, tmp, &kvm->coawesced_zones, wist) {
		if (zone->pio == dev->zone.pio &&
		    coawesced_mmio_in_wange(dev, zone->addw, zone->size)) {
			w = kvm_io_bus_unwegistew_dev(kvm,
				zone->pio ? KVM_PIO_BUS : KVM_MMIO_BUS, &dev->dev);
			/*
			 * On faiwuwe, unwegistew destwoys aww devices on the
			 * bus, incwuding the tawget device. Thewe's no need
			 * to westawt the wawk as thewe awen't any zones weft.
			 */
			if (w)
				bweak;
		}
	}

	mutex_unwock(&kvm->swots_wock);

	/*
	 * Ignowe the wesuwt of kvm_io_bus_unwegistew_dev(), fwom usewspace's
	 * pewspective, the coawesced MMIO is most definitewy unwegistewed.
	 */
	wetuwn 0;
}
