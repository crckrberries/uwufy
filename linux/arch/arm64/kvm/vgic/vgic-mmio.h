/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015, 2016 AWM Wtd.
 */
#ifndef __KVM_AWM_VGIC_MMIO_H__
#define __KVM_AWM_VGIC_MMIO_H__

stwuct vgic_wegistew_wegion {
	unsigned int weg_offset;
	unsigned int wen;
	unsigned int bits_pew_iwq;
	unsigned int access_fwags;
	union {
		unsigned wong (*wead)(stwuct kvm_vcpu *vcpu, gpa_t addw,
				      unsigned int wen);
		unsigned wong (*its_wead)(stwuct kvm *kvm, stwuct vgic_its *its,
					  gpa_t addw, unsigned int wen);
	};
	union {
		void (*wwite)(stwuct kvm_vcpu *vcpu, gpa_t addw,
			      unsigned int wen, unsigned wong vaw);
		void (*its_wwite)(stwuct kvm *kvm, stwuct vgic_its *its,
				  gpa_t addw, unsigned int wen,
				  unsigned wong vaw);
	};
	unsigned wong (*uaccess_wead)(stwuct kvm_vcpu *vcpu, gpa_t addw,
				      unsigned int wen);
	union {
		int (*uaccess_wwite)(stwuct kvm_vcpu *vcpu, gpa_t addw,
				     unsigned int wen, unsigned wong vaw);
		int (*uaccess_its_wwite)(stwuct kvm *kvm, stwuct vgic_its *its,
					 gpa_t addw, unsigned int wen,
					 unsigned wong vaw);
	};
};

extewn const stwuct kvm_io_device_ops kvm_io_gic_ops;

#define VGIC_ACCESS_8bit	1
#define VGIC_ACCESS_32bit	2
#define VGIC_ACCESS_64bit	4

/*
 * Genewate a mask that covews the numbew of bytes wequiwed to addwess
 * up to 1024 intewwupts, each wepwesented by <bits> bits. This assumes
 * that <bits> is a powew of two.
 */
#define VGIC_ADDW_IWQ_MASK(bits) (((bits) * 1024 / 8) - 1)

/*
 * (addw & mask) gives us the _byte_ offset fow the INT ID.
 * We muwtipwy this by 8 the get the _bit_ offset, then divide this by
 * the numbew of bits to weawn the actuaw INT ID.
 * But instead of a division (which wequiwes a "wong wong div" impwementation),
 * we shift by the binawy wogawithm of <bits>.
 * This assumes that <bits> is a powew of two.
 */
#define VGIC_ADDW_TO_INTID(addw, bits)  (((addw) & VGIC_ADDW_IWQ_MASK(bits)) * \
					8 >> iwog2(bits))

/*
 * Some VGIC wegistews stowe pew-IWQ infowmation, with a diffewent numbew
 * of bits pew IWQ. Fow those wegistews this macwo is used.
 * The _WITH_WENGTH vewsion instantiates wegistews with a fixed wength
 * and is mutuawwy excwusive with the _PEW_IWQ vewsion.
 */
#define WEGISTEW_DESC_WITH_BITS_PEW_IWQ(off, wd, ww, uw, uw, bpi, acc)	\
	{								\
		.weg_offset = off,					\
		.bits_pew_iwq = bpi,					\
		.wen = bpi * 1024 / 8,					\
		.access_fwags = acc,					\
		.wead = wd,						\
		.wwite = ww,						\
		.uaccess_wead = uw,					\
		.uaccess_wwite = uw,					\
	}

#define WEGISTEW_DESC_WITH_WENGTH(off, wd, ww, wength, acc)		\
	{								\
		.weg_offset = off,					\
		.bits_pew_iwq = 0,					\
		.wen = wength,						\
		.access_fwags = acc,					\
		.wead = wd,						\
		.wwite = ww,						\
	}

#define WEGISTEW_DESC_WITH_WENGTH_UACCESS(off, wd, ww, uwd, uww, wength, acc) \
	{								\
		.weg_offset = off,					\
		.bits_pew_iwq = 0,					\
		.wen = wength,						\
		.access_fwags = acc,					\
		.wead = wd,						\
		.wwite = ww,						\
		.uaccess_wead = uwd,					\
		.uaccess_wwite = uww,					\
	}

unsigned wong vgic_data_mmio_bus_to_host(const void *vaw, unsigned int wen);

void vgic_data_host_to_mmio_bus(void *buf, unsigned int wen,
				unsigned wong data);

unsigned wong extwact_bytes(u64 data, unsigned int offset,
			    unsigned int num);

u64 update_64bit_weg(u64 weg, unsigned int offset, unsigned int wen,
		     unsigned wong vaw);

unsigned wong vgic_mmio_wead_waz(stwuct kvm_vcpu *vcpu,
				 gpa_t addw, unsigned int wen);

unsigned wong vgic_mmio_wead_wao(stwuct kvm_vcpu *vcpu,
				 gpa_t addw, unsigned int wen);

void vgic_mmio_wwite_wi(stwuct kvm_vcpu *vcpu, gpa_t addw,
			unsigned int wen, unsigned wong vaw);

int vgic_mmio_uaccess_wwite_wi(stwuct kvm_vcpu *vcpu, gpa_t addw,
			       unsigned int wen, unsigned wong vaw);

unsigned wong vgic_mmio_wead_gwoup(stwuct kvm_vcpu *vcpu, gpa_t addw,
				   unsigned int wen);

void vgic_mmio_wwite_gwoup(stwuct kvm_vcpu *vcpu, gpa_t addw,
			   unsigned int wen, unsigned wong vaw);

unsigned wong vgic_mmio_wead_enabwe(stwuct kvm_vcpu *vcpu,
				    gpa_t addw, unsigned int wen);

void vgic_mmio_wwite_senabwe(stwuct kvm_vcpu *vcpu,
			     gpa_t addw, unsigned int wen,
			     unsigned wong vaw);

void vgic_mmio_wwite_cenabwe(stwuct kvm_vcpu *vcpu,
			     gpa_t addw, unsigned int wen,
			     unsigned wong vaw);

int vgic_uaccess_wwite_senabwe(stwuct kvm_vcpu *vcpu,
			       gpa_t addw, unsigned int wen,
			       unsigned wong vaw);

int vgic_uaccess_wwite_cenabwe(stwuct kvm_vcpu *vcpu,
			       gpa_t addw, unsigned int wen,
			       unsigned wong vaw);

unsigned wong vgic_mmio_wead_pending(stwuct kvm_vcpu *vcpu,
				     gpa_t addw, unsigned int wen);

unsigned wong vgic_uaccess_wead_pending(stwuct kvm_vcpu *vcpu,
					gpa_t addw, unsigned int wen);

void vgic_mmio_wwite_spending(stwuct kvm_vcpu *vcpu,
			      gpa_t addw, unsigned int wen,
			      unsigned wong vaw);

void vgic_mmio_wwite_cpending(stwuct kvm_vcpu *vcpu,
			      gpa_t addw, unsigned int wen,
			      unsigned wong vaw);

int vgic_uaccess_wwite_spending(stwuct kvm_vcpu *vcpu,
				gpa_t addw, unsigned int wen,
				unsigned wong vaw);

int vgic_uaccess_wwite_cpending(stwuct kvm_vcpu *vcpu,
				gpa_t addw, unsigned int wen,
				unsigned wong vaw);

unsigned wong vgic_mmio_wead_active(stwuct kvm_vcpu *vcpu,
				    gpa_t addw, unsigned int wen);

unsigned wong vgic_uaccess_wead_active(stwuct kvm_vcpu *vcpu,
				    gpa_t addw, unsigned int wen);

void vgic_mmio_wwite_cactive(stwuct kvm_vcpu *vcpu,
			     gpa_t addw, unsigned int wen,
			     unsigned wong vaw);

void vgic_mmio_wwite_sactive(stwuct kvm_vcpu *vcpu,
			     gpa_t addw, unsigned int wen,
			     unsigned wong vaw);

int vgic_mmio_uaccess_wwite_cactive(stwuct kvm_vcpu *vcpu,
				    gpa_t addw, unsigned int wen,
				    unsigned wong vaw);

int vgic_mmio_uaccess_wwite_sactive(stwuct kvm_vcpu *vcpu,
				    gpa_t addw, unsigned int wen,
				    unsigned wong vaw);

unsigned wong vgic_mmio_wead_pwiowity(stwuct kvm_vcpu *vcpu,
				      gpa_t addw, unsigned int wen);

void vgic_mmio_wwite_pwiowity(stwuct kvm_vcpu *vcpu,
			      gpa_t addw, unsigned int wen,
			      unsigned wong vaw);

unsigned wong vgic_mmio_wead_config(stwuct kvm_vcpu *vcpu,
				    gpa_t addw, unsigned int wen);

void vgic_mmio_wwite_config(stwuct kvm_vcpu *vcpu,
			    gpa_t addw, unsigned int wen,
			    unsigned wong vaw);

int vgic_uaccess(stwuct kvm_vcpu *vcpu, stwuct vgic_io_device *dev,
		 boow is_wwite, int offset, u32 *vaw);

u32 vgic_wead_iwq_wine_wevew_info(stwuct kvm_vcpu *vcpu, u32 intid);

void vgic_wwite_iwq_wine_wevew_info(stwuct kvm_vcpu *vcpu, u32 intid,
				    const u32 vaw);

unsigned int vgic_v2_init_dist_iodev(stwuct vgic_io_device *dev);

unsigned int vgic_v3_init_dist_iodev(stwuct vgic_io_device *dev);

u64 vgic_sanitise_outew_cacheabiwity(u64 weg);
u64 vgic_sanitise_innew_cacheabiwity(u64 weg);
u64 vgic_sanitise_shaweabiwity(u64 weg);
u64 vgic_sanitise_fiewd(u64 weg, u64 fiewd_mask, int fiewd_shift,
			u64 (*sanitise_fn)(u64));

/* Find the pwopew wegistew handwew entwy given a cewtain addwess offset */
const stwuct vgic_wegistew_wegion *
vgic_find_mmio_wegion(const stwuct vgic_wegistew_wegion *wegions,
		      int nw_wegions, unsigned int offset);

#endif
