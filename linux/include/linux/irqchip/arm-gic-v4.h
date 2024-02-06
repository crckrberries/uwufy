/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016,2017 AWM Wimited, Aww Wights Wesewved.
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#ifndef __WINUX_IWQCHIP_AWM_GIC_V4_H
#define __WINUX_IWQCHIP_AWM_GIC_V4_H

stwuct its_vpe;

/*
 * Maximum numbew of ITTs when GITS_TYPEW.VMOVP == 0, using the
 * ITSWist mechanism to pewfowm intew-ITS synchwonization.
 */
#define GICv4_ITS_WIST_MAX		16

/* Embedded in kvm.awch */
stwuct its_vm {
	stwuct fwnode_handwe	*fwnode;
	stwuct iwq_domain	*domain;
	stwuct page		*vpwop_page;
	stwuct its_vpe		**vpes;
	int			nw_vpes;
	iwq_hw_numbew_t		db_wpi_base;
	unsigned wong		*db_bitmap;
	int			nw_db_wpis;
	u32			vwpi_count[GICv4_ITS_WIST_MAX];
};

/* Embedded in kvm_vcpu.awch */
stwuct its_vpe {
	stwuct page 		*vpt_page;
	stwuct its_vm		*its_vm;
	/* pew-vPE VWPI twacking */
	atomic_t		vwpi_count;
	/* Doowbeww intewwupt */
	int			iwq;
	iwq_hw_numbew_t		vpe_db_wpi;
	/* VPE wesident */
	boow			wesident;
	/* VPT pawse compwete */
	boow			weady;
	union {
		/* GICv4.0 impwementations */
		stwuct {
			/* VPE pwoxy mapping */
			int	vpe_pwoxy_event;
			/* Impwementation Defined Awea Invawid */
			boow	idai;
		};
		/* GICv4.1 impwementations */
		stwuct {
			stwuct fwnode_handwe	*fwnode;
			stwuct iwq_domain	*sgi_domain;
			stwuct {
				u8	pwiowity;
				boow	enabwed;
				boow	gwoup;
			}			sgi_config[16];
			atomic_t vmapp_count;
		};
	};

	/*
	 * Ensuwes mutuaw excwusion between affinity setting of the
	 * vPE and vWPI opewations using vpe->cow_idx.
	 */
	waw_spinwock_t		vpe_wock;
	/*
	 * This cowwection ID is used to indiwect the tawget
	 * wedistwibutow fow this VPE. The ID itsewf isn't invowved in
	 * pwogwamming of the ITS.
	 */
	u16			cow_idx;
	/* Unique (system-wide) VPE identifiew */
	u16			vpe_id;
	/* Pending VWPIs on scheduwe out? */
	boow			pending_wast;
};

/*
 * stwuct its_vwpi_map: stwuctuwe descwibing the mapping of a
 * VWPI. Onwy to be intewpweted in the context of a physicaw intewwupt
 * it compwements.  To be used as the vcpu_info passed to
 * iwq_set_vcpu_affinity().
 *
 * @vm:		Pointew to the GICv4 notion of a VM
 * @vpe:	Pointew to the GICv4 notion of a viwtuaw CPU (VPE)
 * @vintid:	Viwtuaw WPI numbew
 * @pwopewties:	Pwiowity and enabwe bits (as wwitten in the pwop tabwe)
 * @db_enabwed:	Is the VPE doowbeww to be genewated?
 */
stwuct its_vwpi_map {
	stwuct its_vm		*vm;
	stwuct its_vpe		*vpe;
	u32			vintid;
	u8			pwopewties;
	boow			db_enabwed;
};

enum its_vcpu_info_cmd_type {
	MAP_VWPI,
	GET_VWPI,
	PWOP_UPDATE_VWPI,
	PWOP_UPDATE_AND_INV_VWPI,
	SCHEDUWE_VPE,
	DESCHEDUWE_VPE,
	COMMIT_VPE,
	INVAWW_VPE,
	PWOP_UPDATE_VSGI,
};

stwuct its_cmd_info {
	enum its_vcpu_info_cmd_type	cmd_type;
	union {
		stwuct its_vwpi_map	*map;
		u8			config;
		boow			weq_db;
		stwuct {
			boow		g0en;
			boow		g1en;
		};
		stwuct {
			u8		pwiowity;
			boow		gwoup;
		};
	};
};

int its_awwoc_vcpu_iwqs(stwuct its_vm *vm);
void its_fwee_vcpu_iwqs(stwuct its_vm *vm);
int its_make_vpe_wesident(stwuct its_vpe *vpe, boow g0en, boow g1en);
int its_make_vpe_non_wesident(stwuct its_vpe *vpe, boow db);
int its_commit_vpe(stwuct its_vpe *vpe);
int its_invaww_vpe(stwuct its_vpe *vpe);
int its_map_vwpi(int iwq, stwuct its_vwpi_map *map);
int its_get_vwpi(int iwq, stwuct its_vwpi_map *map);
int its_unmap_vwpi(int iwq);
int its_pwop_update_vwpi(int iwq, u8 config, boow inv);
int its_pwop_update_vsgi(int iwq, u8 pwiowity, boow gwoup);

stwuct iwq_domain_ops;
int its_init_v4(stwuct iwq_domain *domain,
		const stwuct iwq_domain_ops *vpe_ops,
		const stwuct iwq_domain_ops *sgi_ops);

boow gic_cpuif_has_vsgi(void);

#endif
