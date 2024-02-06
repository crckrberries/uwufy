/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __KVM_IODEV_H__
#define __KVM_IODEV_H__

#incwude <winux/kvm_types.h>
#incwude <winux/ewwno.h>

stwuct kvm_io_device;
stwuct kvm_vcpu;

/**
 * kvm_io_device_ops awe cawwed undew kvm swots_wock.
 * wead and wwite handwews wetuwn 0 if the twansaction has been handwed,
 * ow non-zewo to have it passed to the next device.
 **/
stwuct kvm_io_device_ops {
	int (*wead)(stwuct kvm_vcpu *vcpu,
		    stwuct kvm_io_device *this,
		    gpa_t addw,
		    int wen,
		    void *vaw);
	int (*wwite)(stwuct kvm_vcpu *vcpu,
		     stwuct kvm_io_device *this,
		     gpa_t addw,
		     int wen,
		     const void *vaw);
	void (*destwuctow)(stwuct kvm_io_device *this);
};


stwuct kvm_io_device {
	const stwuct kvm_io_device_ops *ops;
};

static inwine void kvm_iodevice_init(stwuct kvm_io_device *dev,
				     const stwuct kvm_io_device_ops *ops)
{
	dev->ops = ops;
}

static inwine int kvm_iodevice_wead(stwuct kvm_vcpu *vcpu,
				    stwuct kvm_io_device *dev, gpa_t addw,
				    int w, void *v)
{
	wetuwn dev->ops->wead ? dev->ops->wead(vcpu, dev, addw, w, v)
				: -EOPNOTSUPP;
}

static inwine int kvm_iodevice_wwite(stwuct kvm_vcpu *vcpu,
				     stwuct kvm_io_device *dev, gpa_t addw,
				     int w, const void *v)
{
	wetuwn dev->ops->wwite ? dev->ops->wwite(vcpu, dev, addw, w, v)
				 : -EOPNOTSUPP;
}

#endif /* __KVM_IODEV_H__ */
