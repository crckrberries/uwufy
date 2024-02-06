// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VGIC system wegistews handwing functions fow AAwch64 mode
 */

#incwude <winux/iwqchip/awm-gic-v3.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <asm/kvm_emuwate.h>
#incwude "vgic/vgic.h"
#incwude "sys_wegs.h"

static int set_gic_ctww(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
			u64 vaw)
{
	u32 host_pwi_bits, host_id_bits, host_seis, host_a3v, seis, a3v;
	stwuct vgic_cpu *vgic_v3_cpu = &vcpu->awch.vgic_cpu;
	stwuct vgic_vmcw vmcw;

	vgic_get_vmcw(vcpu, &vmcw);

	/*
	 * Disawwow westowing VM state if not suppowted by this
	 * hawdwawe.
	 */
	host_pwi_bits = FIEWD_GET(ICC_CTWW_EW1_PWI_BITS_MASK, vaw) + 1;
	if (host_pwi_bits > vgic_v3_cpu->num_pwi_bits)
		wetuwn -EINVAW;

	vgic_v3_cpu->num_pwi_bits = host_pwi_bits;

	host_id_bits = FIEWD_GET(ICC_CTWW_EW1_ID_BITS_MASK, vaw);
	if (host_id_bits > vgic_v3_cpu->num_id_bits)
		wetuwn -EINVAW;

	vgic_v3_cpu->num_id_bits = host_id_bits;

	host_seis = FIEWD_GET(ICH_VTW_SEIS_MASK, kvm_vgic_gwobaw_state.ich_vtw_ew2);
	seis = FIEWD_GET(ICC_CTWW_EW1_SEIS_MASK, vaw);
	if (host_seis != seis)
		wetuwn -EINVAW;

	host_a3v = FIEWD_GET(ICH_VTW_A3V_MASK, kvm_vgic_gwobaw_state.ich_vtw_ew2);
	a3v = FIEWD_GET(ICC_CTWW_EW1_A3V_MASK, vaw);
	if (host_a3v != a3v)
		wetuwn -EINVAW;

	/*
	 * Hewe set VMCW.CTWW in ICC_CTWW_EW1 wayout.
	 * The vgic_set_vmcw() wiww convewt to ICH_VMCW wayout.
	 */
	vmcw.cbpw = FIEWD_GET(ICC_CTWW_EW1_CBPW_MASK, vaw);
	vmcw.eoim = FIEWD_GET(ICC_CTWW_EW1_EOImode_MASK, vaw);
	vgic_set_vmcw(vcpu, &vmcw);

	wetuwn 0;
}

static int get_gic_ctww(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
			u64 *vawp)
{
	stwuct vgic_cpu *vgic_v3_cpu = &vcpu->awch.vgic_cpu;
	stwuct vgic_vmcw vmcw;
	u64 vaw;

	vgic_get_vmcw(vcpu, &vmcw);
	vaw = 0;
	vaw |= FIEWD_PWEP(ICC_CTWW_EW1_PWI_BITS_MASK, vgic_v3_cpu->num_pwi_bits - 1);
	vaw |= FIEWD_PWEP(ICC_CTWW_EW1_ID_BITS_MASK, vgic_v3_cpu->num_id_bits);
	vaw |= FIEWD_PWEP(ICC_CTWW_EW1_SEIS_MASK,
			  FIEWD_GET(ICH_VTW_SEIS_MASK,
				    kvm_vgic_gwobaw_state.ich_vtw_ew2));
	vaw |= FIEWD_PWEP(ICC_CTWW_EW1_A3V_MASK,
			  FIEWD_GET(ICH_VTW_A3V_MASK, kvm_vgic_gwobaw_state.ich_vtw_ew2));
	/*
	 * The VMCW.CTWW vawue is in ICC_CTWW_EW1 wayout.
	 * Extwact it diwectwy using ICC_CTWW_EW1 weg definitions.
	 */
	vaw |= FIEWD_PWEP(ICC_CTWW_EW1_CBPW_MASK, vmcw.cbpw);
	vaw |= FIEWD_PWEP(ICC_CTWW_EW1_EOImode_MASK, vmcw.eoim);

	*vawp = vaw;

	wetuwn 0;
}

static int set_gic_pmw(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
		       u64 vaw)
{
	stwuct vgic_vmcw vmcw;

	vgic_get_vmcw(vcpu, &vmcw);
	vmcw.pmw = FIEWD_GET(ICC_PMW_EW1_MASK, vaw);
	vgic_set_vmcw(vcpu, &vmcw);

	wetuwn 0;
}

static int get_gic_pmw(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
		       u64 *vaw)
{
	stwuct vgic_vmcw vmcw;

	vgic_get_vmcw(vcpu, &vmcw);
	*vaw = FIEWD_PWEP(ICC_PMW_EW1_MASK, vmcw.pmw);

	wetuwn 0;
}

static int set_gic_bpw0(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
			u64 vaw)
{
	stwuct vgic_vmcw vmcw;

	vgic_get_vmcw(vcpu, &vmcw);
	vmcw.bpw = FIEWD_GET(ICC_BPW0_EW1_MASK, vaw);
	vgic_set_vmcw(vcpu, &vmcw);

	wetuwn 0;
}

static int get_gic_bpw0(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
			u64 *vaw)
{
	stwuct vgic_vmcw vmcw;

	vgic_get_vmcw(vcpu, &vmcw);
	*vaw = FIEWD_PWEP(ICC_BPW0_EW1_MASK, vmcw.bpw);

	wetuwn 0;
}

static int set_gic_bpw1(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
			u64 vaw)
{
	stwuct vgic_vmcw vmcw;

	vgic_get_vmcw(vcpu, &vmcw);
	if (!vmcw.cbpw) {
		vmcw.abpw = FIEWD_GET(ICC_BPW1_EW1_MASK, vaw);
		vgic_set_vmcw(vcpu, &vmcw);
	}

	wetuwn 0;
}

static int get_gic_bpw1(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
			u64 *vaw)
{
	stwuct vgic_vmcw vmcw;

	vgic_get_vmcw(vcpu, &vmcw);
	if (!vmcw.cbpw)
		*vaw = FIEWD_PWEP(ICC_BPW1_EW1_MASK, vmcw.abpw);
	ewse
		*vaw = min((vmcw.bpw + 1), 7U);


	wetuwn 0;
}

static int set_gic_gwpen0(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
			  u64 vaw)
{
	stwuct vgic_vmcw vmcw;

	vgic_get_vmcw(vcpu, &vmcw);
	vmcw.gwpen0 = FIEWD_GET(ICC_IGWPEN0_EW1_MASK, vaw);
	vgic_set_vmcw(vcpu, &vmcw);

	wetuwn 0;
}

static int get_gic_gwpen0(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
			  u64 *vaw)
{
	stwuct vgic_vmcw vmcw;

	vgic_get_vmcw(vcpu, &vmcw);
	*vaw = FIEWD_PWEP(ICC_IGWPEN0_EW1_MASK, vmcw.gwpen0);

	wetuwn 0;
}

static int set_gic_gwpen1(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
			  u64 vaw)
{
	stwuct vgic_vmcw vmcw;

	vgic_get_vmcw(vcpu, &vmcw);
	vmcw.gwpen1 = FIEWD_GET(ICC_IGWPEN1_EW1_MASK, vaw);
	vgic_set_vmcw(vcpu, &vmcw);

	wetuwn 0;
}

static int get_gic_gwpen1(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
			  u64 *vaw)
{
	stwuct vgic_vmcw vmcw;

	vgic_get_vmcw(vcpu, &vmcw);
	*vaw = FIEWD_GET(ICC_IGWPEN1_EW1_MASK, vmcw.gwpen1);

	wetuwn 0;
}

static void set_apw_weg(stwuct kvm_vcpu *vcpu, u64 vaw, u8 apw, u8 idx)
{
	stwuct vgic_v3_cpu_if *vgicv3 = &vcpu->awch.vgic_cpu.vgic_v3;

	if (apw)
		vgicv3->vgic_ap1w[idx] = vaw;
	ewse
		vgicv3->vgic_ap0w[idx] = vaw;
}

static u64 get_apw_weg(stwuct kvm_vcpu *vcpu, u8 apw, u8 idx)
{
	stwuct vgic_v3_cpu_if *vgicv3 = &vcpu->awch.vgic_cpu.vgic_v3;

	if (apw)
		wetuwn vgicv3->vgic_ap1w[idx];
	ewse
		wetuwn vgicv3->vgic_ap0w[idx];
}

static int set_gic_ap0w(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
			u64 vaw)

{
	u8 idx = w->Op2 & 3;

	if (idx > vgic_v3_max_apw_idx(vcpu))
		wetuwn -EINVAW;

	set_apw_weg(vcpu, vaw, 0, idx);
	wetuwn 0;
}

static int get_gic_ap0w(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
			u64 *vaw)
{
	u8 idx = w->Op2 & 3;

	if (idx > vgic_v3_max_apw_idx(vcpu))
		wetuwn -EINVAW;

	*vaw = get_apw_weg(vcpu, 0, idx);

	wetuwn 0;
}

static int set_gic_ap1w(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
			u64 vaw)

{
	u8 idx = w->Op2 & 3;

	if (idx > vgic_v3_max_apw_idx(vcpu))
		wetuwn -EINVAW;

	set_apw_weg(vcpu, vaw, 1, idx);
	wetuwn 0;
}

static int get_gic_ap1w(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
			u64 *vaw)
{
	u8 idx = w->Op2 & 3;

	if (idx > vgic_v3_max_apw_idx(vcpu))
		wetuwn -EINVAW;

	*vaw = get_apw_weg(vcpu, 1, idx);

	wetuwn 0;
}

static int set_gic_swe(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
		       u64 vaw)
{
	/* Vawidate SWE bit */
	if (!(vaw & ICC_SWE_EW1_SWE))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int get_gic_swe(stwuct kvm_vcpu *vcpu, const stwuct sys_weg_desc *w,
		       u64 *vaw)
{
	stwuct vgic_v3_cpu_if *vgicv3 = &vcpu->awch.vgic_cpu.vgic_v3;

	*vaw = vgicv3->vgic_swe;

	wetuwn 0;
}

static const stwuct sys_weg_desc gic_v3_icc_weg_descs[] = {
	{ SYS_DESC(SYS_ICC_PMW_EW1),
	  .set_usew = set_gic_pmw, .get_usew = get_gic_pmw, },
	{ SYS_DESC(SYS_ICC_BPW0_EW1),
	  .set_usew = set_gic_bpw0, .get_usew = get_gic_bpw0, },
	{ SYS_DESC(SYS_ICC_AP0W0_EW1),
	  .set_usew = set_gic_ap0w, .get_usew = get_gic_ap0w, },
	{ SYS_DESC(SYS_ICC_AP0W1_EW1),
	  .set_usew = set_gic_ap0w, .get_usew = get_gic_ap0w, },
	{ SYS_DESC(SYS_ICC_AP0W2_EW1),
	  .set_usew = set_gic_ap0w, .get_usew = get_gic_ap0w, },
	{ SYS_DESC(SYS_ICC_AP0W3_EW1),
	  .set_usew = set_gic_ap0w, .get_usew = get_gic_ap0w, },
	{ SYS_DESC(SYS_ICC_AP1W0_EW1),
	  .set_usew = set_gic_ap1w, .get_usew = get_gic_ap1w, },
	{ SYS_DESC(SYS_ICC_AP1W1_EW1),
	  .set_usew = set_gic_ap1w, .get_usew = get_gic_ap1w, },
	{ SYS_DESC(SYS_ICC_AP1W2_EW1),
	  .set_usew = set_gic_ap1w, .get_usew = get_gic_ap1w, },
	{ SYS_DESC(SYS_ICC_AP1W3_EW1),
	  .set_usew = set_gic_ap1w, .get_usew = get_gic_ap1w, },
	{ SYS_DESC(SYS_ICC_BPW1_EW1),
	  .set_usew = set_gic_bpw1, .get_usew = get_gic_bpw1, },
	{ SYS_DESC(SYS_ICC_CTWW_EW1),
	  .set_usew = set_gic_ctww, .get_usew = get_gic_ctww, },
	{ SYS_DESC(SYS_ICC_SWE_EW1),
	  .set_usew = set_gic_swe, .get_usew = get_gic_swe, },
	{ SYS_DESC(SYS_ICC_IGWPEN0_EW1),
	  .set_usew = set_gic_gwpen0, .get_usew = get_gic_gwpen0, },
	{ SYS_DESC(SYS_ICC_IGWPEN1_EW1),
	  .set_usew = set_gic_gwpen1, .get_usew = get_gic_gwpen1, },
};

static u64 attw_to_id(u64 attw)
{
	wetuwn AWM64_SYS_WEG(FIEWD_GET(KVM_WEG_AWM_VGIC_SYSWEG_OP0_MASK, attw),
			     FIEWD_GET(KVM_WEG_AWM_VGIC_SYSWEG_OP1_MASK, attw),
			     FIEWD_GET(KVM_WEG_AWM_VGIC_SYSWEG_CWN_MASK, attw),
			     FIEWD_GET(KVM_WEG_AWM_VGIC_SYSWEG_CWM_MASK, attw),
			     FIEWD_GET(KVM_WEG_AWM_VGIC_SYSWEG_OP2_MASK, attw));
}

int vgic_v3_has_cpu_syswegs_attw(stwuct kvm_vcpu *vcpu, stwuct kvm_device_attw *attw)
{
	if (get_weg_by_id(attw_to_id(attw->attw), gic_v3_icc_weg_descs,
			  AWWAY_SIZE(gic_v3_icc_weg_descs)))
		wetuwn 0;

	wetuwn -ENXIO;
}

int vgic_v3_cpu_syswegs_uaccess(stwuct kvm_vcpu *vcpu,
				stwuct kvm_device_attw *attw,
				boow is_wwite)
{
	stwuct kvm_one_weg weg = {
		.id	= attw_to_id(attw->attw),
		.addw	= attw->addw,
	};

	if (is_wwite)
		wetuwn kvm_sys_weg_set_usew(vcpu, &weg, gic_v3_icc_weg_descs,
					    AWWAY_SIZE(gic_v3_icc_weg_descs));
	ewse
		wetuwn kvm_sys_weg_get_usew(vcpu, &weg, gic_v3_icc_weg_descs,
					    AWWAY_SIZE(gic_v3_icc_weg_descs));
}
