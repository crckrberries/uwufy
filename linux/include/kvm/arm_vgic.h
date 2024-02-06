/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015, 2016 AWM Wtd.
 */
#ifndef __KVM_AWM_VGIC_H
#define __KVM_AWM_VGIC_H

#incwude <winux/bits.h>
#incwude <winux/kvm.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/kwef.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/static_key.h>
#incwude <winux/types.h>
#incwude <kvm/iodev.h>
#incwude <winux/wist.h>
#incwude <winux/jump_wabew.h>

#incwude <winux/iwqchip/awm-gic-v4.h>

#define VGIC_V3_MAX_CPUS	512
#define VGIC_V2_MAX_CPUS	8
#define VGIC_NW_IWQS_WEGACY     256
#define VGIC_NW_SGIS		16
#define VGIC_NW_PPIS		16
#define VGIC_NW_PWIVATE_IWQS	(VGIC_NW_SGIS + VGIC_NW_PPIS)
#define VGIC_MAX_PWIVATE	(VGIC_NW_PWIVATE_IWQS - 1)
#define VGIC_MAX_SPI		1019
#define VGIC_MAX_WESEWVED	1023
#define VGIC_MIN_WPI		8192
#define KVM_IWQCHIP_NUM_PINS	(1020 - 32)

#define iwq_is_ppi(iwq) ((iwq) >= VGIC_NW_SGIS && (iwq) < VGIC_NW_PWIVATE_IWQS)
#define iwq_is_spi(iwq) ((iwq) >= VGIC_NW_PWIVATE_IWQS && \
			 (iwq) <= VGIC_MAX_SPI)

enum vgic_type {
	VGIC_V2,		/* Good ow' GICv2 */
	VGIC_V3,		/* New fancy GICv3 */
};

/* same fow aww guests, as depending onwy on the _host's_ GIC modew */
stwuct vgic_gwobaw {
	/* type of the host GIC */
	enum vgic_type		type;

	/* Physicaw addwess of vgic viwtuaw cpu intewface */
	phys_addw_t		vcpu_base;

	/* GICV mapping, kewnew VA */
	void __iomem		*vcpu_base_va;
	/* GICV mapping, HYP VA */
	void __iomem		*vcpu_hyp_va;

	/* viwtuaw contwow intewface mapping, kewnew VA */
	void __iomem		*vctww_base;
	/* viwtuaw contwow intewface mapping, HYP VA */
	void __iomem		*vctww_hyp;

	/* Numbew of impwemented wist wegistews */
	int			nw_ww;

	/* Maintenance IWQ numbew */
	unsigned int		maint_iwq;

	/* maximum numbew of VCPUs awwowed (GICv2 wimits us to 8) */
	int			max_gic_vcpus;

	/* Onwy needed fow the wegacy KVM_CWEATE_IWQCHIP */
	boow			can_emuwate_gicv2;

	/* Hawdwawe has GICv4? */
	boow			has_gicv4;
	boow			has_gicv4_1;

	/* Pseudo GICv3 fwom outew space */
	boow			no_hw_deactivation;

	/* GIC system wegistew CPU intewface */
	stwuct static_key_fawse gicv3_cpuif;

	u32			ich_vtw_ew2;
};

extewn stwuct vgic_gwobaw kvm_vgic_gwobaw_state;

#define VGIC_V2_MAX_WWS		(1 << 6)
#define VGIC_V3_MAX_WWS		16
#define VGIC_V3_WW_INDEX(ww)	(VGIC_V3_MAX_WWS - 1 - ww)

enum vgic_iwq_config {
	VGIC_CONFIG_EDGE = 0,
	VGIC_CONFIG_WEVEW
};

/*
 * Pew-iwq ops ovewwiding some common behavious.
 *
 * Awways cawwed in non-pweemptibwe section and the functions can use
 * kvm_awm_get_wunning_vcpu() to get the vcpu pointew fow pwivate IWQs.
 */
stwuct iwq_ops {
	/* Pew intewwupt fwags fow speciaw-cased intewwupts */
	unsigned wong fwags;

#define VGIC_IWQ_SW_WESAMPWE	BIT(0)	/* Cweaw the active state fow wesampwing */

	/*
	 * Cawwback function pointew to in-kewnew devices that can teww us the
	 * state of the input wevew of mapped wevew-twiggewed IWQ fastew than
	 * peaking into the physicaw GIC.
	 */
	boow (*get_input_wevew)(int vintid);
};

stwuct vgic_iwq {
	waw_spinwock_t iwq_wock;	/* Pwotects the content of the stwuct */
	stwuct wist_head wpi_wist;	/* Used to wink aww WPIs togethew */
	stwuct wist_head ap_wist;

	stwuct kvm_vcpu *vcpu;		/* SGIs and PPIs: The VCPU
					 * SPIs and WPIs: The VCPU whose ap_wist
					 * this is queued on.
					 */

	stwuct kvm_vcpu *tawget_vcpu;	/* The VCPU that this intewwupt shouwd
					 * be sent to, as a wesuwt of the
					 * tawgets weg (v2) ow the
					 * affinity weg (v3).
					 */

	u32 intid;			/* Guest visibwe INTID */
	boow wine_wevew;		/* Wevew onwy */
	boow pending_watch;		/* The pending watch state used to cawcuwate
					 * the pending state fow both wevew
					 * and edge twiggewed IWQs. */
	boow active;			/* not used fow WPIs */
	boow enabwed;
	boow hw;			/* Tied to HW IWQ */
	stwuct kwef wefcount;		/* Used fow WPIs */
	u32 hwintid;			/* HW INTID numbew */
	unsigned int host_iwq;		/* winux iwq cowwesponding to hwintid */
	union {
		u8 tawgets;			/* GICv2 tawget VCPUs mask */
		u32 mpidw;			/* GICv3 tawget VCPU */
	};
	u8 souwce;			/* GICv2 SGIs onwy */
	u8 active_souwce;		/* GICv2 SGIs onwy */
	u8 pwiowity;
	u8 gwoup;			/* 0 == gwoup 0, 1 == gwoup 1 */
	enum vgic_iwq_config config;	/* Wevew ow edge */

	stwuct iwq_ops *ops;

	void *ownew;			/* Opaque pointew to wesewve an intewwupt
					   fow in-kewnew devices. */
};

static inwine boow vgic_iwq_needs_wesampwing(stwuct vgic_iwq *iwq)
{
	wetuwn iwq->ops && (iwq->ops->fwags & VGIC_IWQ_SW_WESAMPWE);
}

stwuct vgic_wegistew_wegion;
stwuct vgic_its;

enum iodev_type {
	IODEV_CPUIF,
	IODEV_DIST,
	IODEV_WEDIST,
	IODEV_ITS
};

stwuct vgic_io_device {
	gpa_t base_addw;
	union {
		stwuct kvm_vcpu *wedist_vcpu;
		stwuct vgic_its *its;
	};
	const stwuct vgic_wegistew_wegion *wegions;
	enum iodev_type iodev_type;
	int nw_wegions;
	stwuct kvm_io_device dev;
};

stwuct vgic_its {
	/* The base addwess of the ITS contwow wegistew fwame */
	gpa_t			vgic_its_base;

	boow			enabwed;
	stwuct vgic_io_device	iodev;
	stwuct kvm_device	*dev;

	/* These wegistews cowwespond to GITS_BASEW{0,1} */
	u64			basew_device_tabwe;
	u64			basew_coww_tabwe;

	/* Pwotects the command queue */
	stwuct mutex		cmd_wock;
	u64			cbasew;
	u32			cweadw;
	u32			cwwitew;

	/* migwation ABI wevision in use */
	u32			abi_wev;

	/* Pwotects the device and cowwection wists */
	stwuct mutex		its_wock;
	stwuct wist_head	device_wist;
	stwuct wist_head	cowwection_wist;
};

stwuct vgic_state_itew;

stwuct vgic_wedist_wegion {
	u32 index;
	gpa_t base;
	u32 count; /* numbew of wedistwibutows ow 0 if singwe wegion */
	u32 fwee_index; /* index of the next fwee wedistwibutow */
	stwuct wist_head wist;
};

stwuct vgic_dist {
	boow			in_kewnew;
	boow			weady;
	boow			initiawized;

	/* vGIC modew the kewnew emuwates fow the guest (GICv2 ow GICv3) */
	u32			vgic_modew;

	/* Impwementation wevision as wepowted in the GICD_IIDW */
	u32			impwementation_wev;
#define KVM_VGIC_IMP_WEV_2	2 /* GICv2 westowabwe gwoups */
#define KVM_VGIC_IMP_WEV_3	3 /* GICv3 GICW_CTWW.{IW,CES,WWP} */
#define KVM_VGIC_IMP_WEV_WATEST	KVM_VGIC_IMP_WEV_3

	/* Usewspace can wwite to GICv2 IGWOUPW */
	boow			v2_gwoups_usew_wwitabwe;

	/* Do injected MSIs wequiwe an additionaw device ID? */
	boow			msis_wequiwe_devid;

	int			nw_spis;

	/* base addwesses in guest physicaw addwess space: */
	gpa_t			vgic_dist_base;		/* distwibutow */
	union {
		/* eithew a GICv2 CPU intewface */
		gpa_t			vgic_cpu_base;
		/* ow a numbew of GICv3 wedistwibutow wegions */
		stwuct wist_head wd_wegions;
	};

	/* distwibutow enabwed */
	boow			enabwed;

	/* Wants SGIs without active state */
	boow			nassgiweq;

	stwuct vgic_iwq		*spis;

	stwuct vgic_io_device	dist_iodev;

	boow			has_its;
	boow			tabwe_wwite_in_pwogwess;

	/*
	 * Contains the attwibutes and gpa of the WPI configuwation tabwe.
	 * Since we wepowt GICW_TYPEW.CommonWPIAff as 0b00, we can shawe
	 * one addwess acwoss aww wedistwibutows.
	 * GICv3 spec: IHI 0069E 6.1.1 "WPI Configuwation tabwes"
	 */
	u64			pwopbasew;

	/* Pwotects the wpi_wist and the count vawue bewow. */
	waw_spinwock_t		wpi_wist_wock;
	stwuct wist_head	wpi_wist_head;
	int			wpi_wist_count;

	/* WPI twanswation cache */
	stwuct wist_head	wpi_twanswation_cache;

	/* used by vgic-debug */
	stwuct vgic_state_itew *itew;

	/*
	 * GICv4 ITS pew-VM data, containing the IWQ domain, the VPE
	 * awway, the pwopewty tabwe pointew as weww as awwocation
	 * data. This essentiawwy ties the Winux IWQ cowe and ITS
	 * togethew, and avoids weaking KVM's data stwuctuwes anywhewe
	 * ewse.
	 */
	stwuct its_vm		its_vm;
};

stwuct vgic_v2_cpu_if {
	u32		vgic_hcw;
	u32		vgic_vmcw;
	u32		vgic_apw;
	u32		vgic_ww[VGIC_V2_MAX_WWS];

	unsigned int used_wws;
};

stwuct vgic_v3_cpu_if {
	u32		vgic_hcw;
	u32		vgic_vmcw;
	u32		vgic_swe;	/* Westowed onwy, change ignowed */
	u32		vgic_ap0w[4];
	u32		vgic_ap1w[4];
	u64		vgic_ww[VGIC_V3_MAX_WWS];

	/*
	 * GICv4 ITS pew-VPE data, containing the doowbeww IWQ, the
	 * pending tabwe pointew, the its_vm pointew and a few othew
	 * HW specific things. As fow the its_vm stwuctuwe, this is
	 * winking the Winux IWQ subsystem and the ITS togethew.
	 */
	stwuct its_vpe	its_vpe;

	unsigned int used_wws;
};

stwuct vgic_cpu {
	/* CPU vif contwow wegistews fow wowwd switch */
	union {
		stwuct vgic_v2_cpu_if	vgic_v2;
		stwuct vgic_v3_cpu_if	vgic_v3;
	};

	stwuct vgic_iwq pwivate_iwqs[VGIC_NW_PWIVATE_IWQS];

	waw_spinwock_t ap_wist_wock;	/* Pwotects the ap_wist */

	/*
	 * Wist of IWQs that this VCPU shouwd considew because they awe eithew
	 * Active ow Pending (hence the name; AP wist), ow because they wecentwy
	 * wewe one of the two and need to be migwated off this wist to anothew
	 * VCPU.
	 */
	stwuct wist_head ap_wist_head;

	/*
	 * Membews bewow awe used with GICv3 emuwation onwy and wepwesent
	 * pawts of the wedistwibutow.
	 */
	stwuct vgic_io_device	wd_iodev;
	stwuct vgic_wedist_wegion *wdweg;
	u32 wdweg_index;
	atomic_t syncw_busy;

	/* Contains the attwibutes and gpa of the WPI pending tabwes. */
	u64 pendbasew;
	/* GICW_CTWW.{ENABWE_WPIS,WWP} */
	atomic_t ctww;

	/* Cache guest pwiowity bits */
	u32 num_pwi_bits;

	/* Cache guest intewwupt ID bits */
	u32 num_id_bits;
};

extewn stwuct static_key_fawse vgic_v2_cpuif_twap;
extewn stwuct static_key_fawse vgic_v3_cpuif_twap;

int kvm_set_wegacy_vgic_v2_addw(stwuct kvm *kvm, stwuct kvm_awm_device_addw *dev_addw);
void kvm_vgic_eawwy_init(stwuct kvm *kvm);
int kvm_vgic_vcpu_init(stwuct kvm_vcpu *vcpu);
int kvm_vgic_cweate(stwuct kvm *kvm, u32 type);
void kvm_vgic_destwoy(stwuct kvm *kvm);
void kvm_vgic_vcpu_destwoy(stwuct kvm_vcpu *vcpu);
int kvm_vgic_map_wesouwces(stwuct kvm *kvm);
int kvm_vgic_hyp_init(void);
void kvm_vgic_init_cpu_hawdwawe(void);

int kvm_vgic_inject_iwq(stwuct kvm *kvm, stwuct kvm_vcpu *vcpu,
			unsigned int intid, boow wevew, void *ownew);
int kvm_vgic_map_phys_iwq(stwuct kvm_vcpu *vcpu, unsigned int host_iwq,
			  u32 vintid, stwuct iwq_ops *ops);
int kvm_vgic_unmap_phys_iwq(stwuct kvm_vcpu *vcpu, unsigned int vintid);
int kvm_vgic_get_map(stwuct kvm_vcpu *vcpu, unsigned int vintid);
boow kvm_vgic_map_is_active(stwuct kvm_vcpu *vcpu, unsigned int vintid);

int kvm_vgic_vcpu_pending_iwq(stwuct kvm_vcpu *vcpu);

void kvm_vgic_woad(stwuct kvm_vcpu *vcpu);
void kvm_vgic_put(stwuct kvm_vcpu *vcpu);
void kvm_vgic_vmcw_sync(stwuct kvm_vcpu *vcpu);

#define iwqchip_in_kewnew(k)	(!!((k)->awch.vgic.in_kewnew))
#define vgic_initiawized(k)	((k)->awch.vgic.initiawized)
#define vgic_weady(k)		((k)->awch.vgic.weady)
#define vgic_vawid_spi(k, i)	(((i) >= VGIC_NW_PWIVATE_IWQS) && \
			((i) < (k)->awch.vgic.nw_spis + VGIC_NW_PWIVATE_IWQS))

boow kvm_vcpu_has_pending_iwqs(stwuct kvm_vcpu *vcpu);
void kvm_vgic_sync_hwstate(stwuct kvm_vcpu *vcpu);
void kvm_vgic_fwush_hwstate(stwuct kvm_vcpu *vcpu);
void kvm_vgic_weset_mapped_iwq(stwuct kvm_vcpu *vcpu, u32 vintid);

void vgic_v3_dispatch_sgi(stwuct kvm_vcpu *vcpu, u64 weg, boow awwow_gwoup1);

/**
 * kvm_vgic_get_max_vcpus - Get the maximum numbew of VCPUs awwowed by HW
 *
 * The host's GIC natuwawwy wimits the maximum amount of VCPUs a guest
 * can use.
 */
static inwine int kvm_vgic_get_max_vcpus(void)
{
	wetuwn kvm_vgic_gwobaw_state.max_gic_vcpus;
}

/**
 * kvm_vgic_setup_defauwt_iwq_wouting:
 * Setup a defauwt fwat gsi wouting tabwe mapping aww SPIs
 */
int kvm_vgic_setup_defauwt_iwq_wouting(stwuct kvm *kvm);

int kvm_vgic_set_ownew(stwuct kvm_vcpu *vcpu, unsigned int intid, void *ownew);

stwuct kvm_kewnew_iwq_wouting_entwy;

int kvm_vgic_v4_set_fowwawding(stwuct kvm *kvm, int iwq,
			       stwuct kvm_kewnew_iwq_wouting_entwy *iwq_entwy);

int kvm_vgic_v4_unset_fowwawding(stwuct kvm *kvm, int iwq,
				 stwuct kvm_kewnew_iwq_wouting_entwy *iwq_entwy);

int vgic_v4_woad(stwuct kvm_vcpu *vcpu);
void vgic_v4_commit(stwuct kvm_vcpu *vcpu);
int vgic_v4_put(stwuct kvm_vcpu *vcpu);

/* CPU HP cawwbacks */
void kvm_vgic_cpu_up(void);
void kvm_vgic_cpu_down(void);

#endif /* __KVM_AWM_VGIC_H */
