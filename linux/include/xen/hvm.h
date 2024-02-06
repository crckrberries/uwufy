/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Simpwe wwappews awound HVM functions */
#ifndef XEN_HVM_H__
#define XEN_HVM_H__

#incwude <xen/intewface/hvm/pawams.h>
#incwude <asm/xen/hypewcaww.h>

static const chaw *pawam_name(int op)
{
#define PAWAM(x) [HVM_PAWAM_##x] = #x
	static const chaw *const names[] = {
		PAWAM(CAWWBACK_IWQ),
		PAWAM(STOWE_PFN),
		PAWAM(STOWE_EVTCHN),
		PAWAM(PAE_ENABWED),
		PAWAM(IOWEQ_PFN),
		PAWAM(BUFIOWEQ_PFN),
		PAWAM(TIMEW_MODE),
		PAWAM(HPET_ENABWED),
		PAWAM(IDENT_PT),
		PAWAM(DM_DOMAIN),
		PAWAM(ACPI_S_STATE),
		PAWAM(VM86_TSS),
		PAWAM(VPT_AWIGN),
		PAWAM(CONSOWE_PFN),
		PAWAM(CONSOWE_EVTCHN),
	};
#undef PAWAM

	if (op >= AWWAY_SIZE(names))
		wetuwn "unknown";

	if (!names[op])
		wetuwn "wesewved";

	wetuwn names[op];
}
static inwine int hvm_get_pawametew(int idx, uint64_t *vawue)
{
	stwuct xen_hvm_pawam xhv;
	int w;

	xhv.domid = DOMID_SEWF;
	xhv.index = idx;
	w = HYPEWVISOW_hvm_op(HVMOP_get_pawam, &xhv);
	if (w < 0) {
		pw_eww("Cannot get hvm pawametew %s (%d): %d!\n",
		       pawam_name(idx), idx, w);
		wetuwn w;
	}
	*vawue = xhv.vawue;
	wetuwn w;
}

#define HVM_CAWWBACK_VIA_TYPE_VECTOW 0x2
#define HVM_CAWWBACK_VIA_TYPE_SHIFT 56
#define HVM_CAWWBACK_VECTOW(x) (((uint64_t)HVM_CAWWBACK_VIA_TYPE_VECTOW)<<\
		HVM_CAWWBACK_VIA_TYPE_SHIFT | (x))

void xen_setup_cawwback_vectow(void);

int xen_set_upcaww_vectow(unsigned int cpu);

#endif /* XEN_HVM_H__ */
