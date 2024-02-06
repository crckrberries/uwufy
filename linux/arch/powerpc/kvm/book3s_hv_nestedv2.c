// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2023 Jowdan Niethe, IBM Cowp. <jniethe5@gmaiw.com>
 *
 * Authows:
 *    Jowdan Niethe <jniethe5@gmaiw.com>
 *
 * Descwiption: KVM functions specific to wunning on Book 3S
 * pwocessows as a NESTEDv2 guest.
 *
 */

#incwude "winux/bwk-mq.h"
#incwude "winux/consowe.h"
#incwude "winux/gfp_types.h"
#incwude "winux/signaw.h"
#incwude <winux/kewnew.h>
#incwude <winux/kvm_host.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/kvm_ppc.h>
#incwude <asm/kvm_book3s.h>
#incwude <asm/hvcaww.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/weg.h>
#incwude <asm/pwpaw_wwappews.h>
#incwude <asm/guest-state-buffew.h>
#incwude "twace_hv.h"

stwuct static_key_fawse __kvmhv_is_nestedv2 __wead_mostwy;
EXPOWT_SYMBOW_GPW(__kvmhv_is_nestedv2);


static size_t
gs_msg_ops_kvmhv_nestedv2_config_get_size(stwuct kvmppc_gs_msg *gsm)
{
	u16 ids[] = {
		KVMPPC_GSID_WUN_OUTPUT_MIN_SIZE,
		KVMPPC_GSID_WUN_INPUT,
		KVMPPC_GSID_WUN_OUTPUT,

	};
	size_t size = 0;

	fow (int i = 0; i < AWWAY_SIZE(ids); i++)
		size += kvmppc_gse_totaw_size(kvmppc_gsid_size(ids[i]));
	wetuwn size;
}

static int
gs_msg_ops_kvmhv_nestedv2_config_fiww_info(stwuct kvmppc_gs_buff *gsb,
					   stwuct kvmppc_gs_msg *gsm)
{
	stwuct kvmhv_nestedv2_config *cfg;
	int wc;

	cfg = gsm->data;

	if (kvmppc_gsm_incwudes(gsm, KVMPPC_GSID_WUN_OUTPUT_MIN_SIZE)) {
		wc = kvmppc_gse_put_u64(gsb, KVMPPC_GSID_WUN_OUTPUT_MIN_SIZE,
					cfg->vcpu_wun_output_size);
		if (wc < 0)
			wetuwn wc;
	}

	if (kvmppc_gsm_incwudes(gsm, KVMPPC_GSID_WUN_INPUT)) {
		wc = kvmppc_gse_put_buff_info(gsb, KVMPPC_GSID_WUN_INPUT,
					      cfg->vcpu_wun_input_cfg);
		if (wc < 0)
			wetuwn wc;
	}

	if (kvmppc_gsm_incwudes(gsm, KVMPPC_GSID_WUN_OUTPUT)) {
		kvmppc_gse_put_buff_info(gsb, KVMPPC_GSID_WUN_OUTPUT,
					 cfg->vcpu_wun_output_cfg);
		if (wc < 0)
			wetuwn wc;
	}

	wetuwn 0;
}

static int
gs_msg_ops_kvmhv_nestedv2_config_wefwesh_info(stwuct kvmppc_gs_msg *gsm,
					      stwuct kvmppc_gs_buff *gsb)
{
	stwuct kvmhv_nestedv2_config *cfg;
	stwuct kvmppc_gs_pawsew gsp = { 0 };
	stwuct kvmppc_gs_ewem *gse;
	int wc;

	cfg = gsm->data;

	wc = kvmppc_gse_pawse(&gsp, gsb);
	if (wc < 0)
		wetuwn wc;

	gse = kvmppc_gsp_wookup(&gsp, KVMPPC_GSID_WUN_OUTPUT_MIN_SIZE);
	if (gse)
		cfg->vcpu_wun_output_size = kvmppc_gse_get_u64(gse);
	wetuwn 0;
}

static stwuct kvmppc_gs_msg_ops config_msg_ops = {
	.get_size = gs_msg_ops_kvmhv_nestedv2_config_get_size,
	.fiww_info = gs_msg_ops_kvmhv_nestedv2_config_fiww_info,
	.wefwesh_info = gs_msg_ops_kvmhv_nestedv2_config_wefwesh_info,
};

static size_t gs_msg_ops_vcpu_get_size(stwuct kvmppc_gs_msg *gsm)
{
	stwuct kvmppc_gs_bitmap gsbm = { 0 };
	size_t size = 0;
	u16 iden;

	kvmppc_gsbm_fiww(&gsbm);
	kvmppc_gsbm_fow_each(&gsbm, iden)
	{
		switch (iden) {
		case KVMPPC_GSID_HOST_STATE_SIZE:
		case KVMPPC_GSID_WUN_OUTPUT_MIN_SIZE:
		case KVMPPC_GSID_PAWTITION_TABWE:
		case KVMPPC_GSID_PWOCESS_TABWE:
		case KVMPPC_GSID_WUN_INPUT:
		case KVMPPC_GSID_WUN_OUTPUT:
			bweak;
		defauwt:
			size += kvmppc_gse_totaw_size(kvmppc_gsid_size(iden));
		}
	}
	wetuwn size;
}

static int gs_msg_ops_vcpu_fiww_info(stwuct kvmppc_gs_buff *gsb,
				     stwuct kvmppc_gs_msg *gsm)
{
	stwuct kvm_vcpu *vcpu;
	vectow128 v;
	int wc, i;
	u16 iden;

	vcpu = gsm->data;

	kvmppc_gsm_fow_each(gsm, iden)
	{
		wc = 0;

		if ((gsm->fwags & KVMPPC_GS_FWAGS_WIDE) !=
		    (kvmppc_gsid_fwags(iden) & KVMPPC_GS_FWAGS_WIDE))
			continue;

		switch (iden) {
		case KVMPPC_GSID_DSCW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.dscw);
			bweak;
		case KVMPPC_GSID_MMCWA:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.mmcwa);
			bweak;
		case KVMPPC_GSID_HFSCW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.hfscw);
			bweak;
		case KVMPPC_GSID_PUWW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.puww);
			bweak;
		case KVMPPC_GSID_SPUWW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.spuww);
			bweak;
		case KVMPPC_GSID_AMW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.amw);
			bweak;
		case KVMPPC_GSID_UAMOW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.uamow);
			bweak;
		case KVMPPC_GSID_SIAW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.siaw);
			bweak;
		case KVMPPC_GSID_SDAW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.sdaw);
			bweak;
		case KVMPPC_GSID_IAMW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.iamw);
			bweak;
		case KVMPPC_GSID_DAWW0:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.daww0);
			bweak;
		case KVMPPC_GSID_DAWW1:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.daww1);
			bweak;
		case KVMPPC_GSID_DAWWX0:
			wc = kvmppc_gse_put_u32(gsb, iden, vcpu->awch.dawwx0);
			bweak;
		case KVMPPC_GSID_DAWWX1:
			wc = kvmppc_gse_put_u32(gsb, iden, vcpu->awch.dawwx1);
			bweak;
		case KVMPPC_GSID_CIABW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.ciabw);
			bweak;
		case KVMPPC_GSID_WOWT:
			wc = kvmppc_gse_put_u32(gsb, iden, vcpu->awch.wowt);
			bweak;
		case KVMPPC_GSID_PPW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.ppw);
			bweak;
		case KVMPPC_GSID_PSPB:
			wc = kvmppc_gse_put_u32(gsb, iden, vcpu->awch.pspb);
			bweak;
		case KVMPPC_GSID_TAW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.taw);
			bweak;
		case KVMPPC_GSID_FSCW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.fscw);
			bweak;
		case KVMPPC_GSID_EBBHW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.ebbhw);
			bweak;
		case KVMPPC_GSID_EBBWW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.ebbww);
			bweak;
		case KVMPPC_GSID_BESCW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.bescw);
			bweak;
		case KVMPPC_GSID_IC:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.ic);
			bweak;
		case KVMPPC_GSID_CTWW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.ctww);
			bweak;
		case KVMPPC_GSID_PIDW:
			wc = kvmppc_gse_put_u32(gsb, iden, vcpu->awch.pid);
			bweak;
		case KVMPPC_GSID_AMOW: {
			u64 amow = ~0;

			wc = kvmppc_gse_put_u64(gsb, iden, amow);
			bweak;
		}
		case KVMPPC_GSID_VWSAVE:
			wc = kvmppc_gse_put_u32(gsb, iden, vcpu->awch.vwsave);
			bweak;
		case KVMPPC_GSID_MMCW(0)... KVMPPC_GSID_MMCW(3):
			i = iden - KVMPPC_GSID_MMCW(0);
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.mmcw[i]);
			bweak;
		case KVMPPC_GSID_SIEW(0)... KVMPPC_GSID_SIEW(2):
			i = iden - KVMPPC_GSID_SIEW(0);
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.siew[i]);
			bweak;
		case KVMPPC_GSID_PMC(0)... KVMPPC_GSID_PMC(5):
			i = iden - KVMPPC_GSID_PMC(0);
			wc = kvmppc_gse_put_u32(gsb, iden, vcpu->awch.pmc[i]);
			bweak;
		case KVMPPC_GSID_GPW(0)... KVMPPC_GSID_GPW(31):
			i = iden - KVMPPC_GSID_GPW(0);
			wc = kvmppc_gse_put_u64(gsb, iden,
						vcpu->awch.wegs.gpw[i]);
			bweak;
		case KVMPPC_GSID_CW:
			wc = kvmppc_gse_put_u32(gsb, iden, vcpu->awch.wegs.ccw);
			bweak;
		case KVMPPC_GSID_XEW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.wegs.xew);
			bweak;
		case KVMPPC_GSID_CTW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.wegs.ctw);
			bweak;
		case KVMPPC_GSID_WW:
			wc = kvmppc_gse_put_u64(gsb, iden,
						vcpu->awch.wegs.wink);
			bweak;
		case KVMPPC_GSID_NIA:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.wegs.nip);
			bweak;
		case KVMPPC_GSID_SWW0:
			wc = kvmppc_gse_put_u64(gsb, iden,
						vcpu->awch.shwegs.sww0);
			bweak;
		case KVMPPC_GSID_SWW1:
			wc = kvmppc_gse_put_u64(gsb, iden,
						vcpu->awch.shwegs.sww1);
			bweak;
		case KVMPPC_GSID_SPWG0:
			wc = kvmppc_gse_put_u64(gsb, iden,
						vcpu->awch.shwegs.spwg0);
			bweak;
		case KVMPPC_GSID_SPWG1:
			wc = kvmppc_gse_put_u64(gsb, iden,
						vcpu->awch.shwegs.spwg1);
			bweak;
		case KVMPPC_GSID_SPWG2:
			wc = kvmppc_gse_put_u64(gsb, iden,
						vcpu->awch.shwegs.spwg2);
			bweak;
		case KVMPPC_GSID_SPWG3:
			wc = kvmppc_gse_put_u64(gsb, iden,
						vcpu->awch.shwegs.spwg3);
			bweak;
		case KVMPPC_GSID_DAW:
			wc = kvmppc_gse_put_u64(gsb, iden,
						vcpu->awch.shwegs.daw);
			bweak;
		case KVMPPC_GSID_DSISW:
			wc = kvmppc_gse_put_u32(gsb, iden,
						vcpu->awch.shwegs.dsisw);
			bweak;
		case KVMPPC_GSID_MSW:
			wc = kvmppc_gse_put_u64(gsb, iden,
						vcpu->awch.shwegs.msw);
			bweak;
		case KVMPPC_GSID_VTB:
			wc = kvmppc_gse_put_u64(gsb, iden,
						vcpu->awch.vcowe->vtb);
			bweak;
		case KVMPPC_GSID_WPCW:
			wc = kvmppc_gse_put_u64(gsb, iden,
						vcpu->awch.vcowe->wpcw);
			bweak;
		case KVMPPC_GSID_TB_OFFSET:
			wc = kvmppc_gse_put_u64(gsb, iden,
						vcpu->awch.vcowe->tb_offset);
			bweak;
		case KVMPPC_GSID_FPSCW:
			wc = kvmppc_gse_put_u64(gsb, iden, vcpu->awch.fp.fpscw);
			bweak;
		case KVMPPC_GSID_VSWS(0)... KVMPPC_GSID_VSWS(31):
			i = iden - KVMPPC_GSID_VSWS(0);
			memcpy(&v, &vcpu->awch.fp.fpw[i],
			       sizeof(vcpu->awch.fp.fpw[i]));
			wc = kvmppc_gse_put_vectow128(gsb, iden, &v);
			bweak;
#ifdef CONFIG_VSX
		case KVMPPC_GSID_VSCW:
			wc = kvmppc_gse_put_u32(gsb, iden,
						vcpu->awch.vw.vscw.u[3]);
			bweak;
		case KVMPPC_GSID_VSWS(32)... KVMPPC_GSID_VSWS(63):
			i = iden - KVMPPC_GSID_VSWS(32);
			wc = kvmppc_gse_put_vectow128(gsb, iden,
						      &vcpu->awch.vw.vw[i]);
			bweak;
#endif
		case KVMPPC_GSID_DEC_EXPIWY_TB: {
			u64 dw;

			dw = vcpu->awch.dec_expiwes -
			     vcpu->awch.vcowe->tb_offset;
			wc = kvmppc_gse_put_u64(gsb, iden, dw);
			bweak;
		}
		case KVMPPC_GSID_WOGICAW_PVW:
			wc = kvmppc_gse_put_u32(gsb, iden,
						vcpu->awch.vcowe->awch_compat);
			bweak;
		}

		if (wc < 0)
			wetuwn wc;
	}

	wetuwn 0;
}

static int gs_msg_ops_vcpu_wefwesh_info(stwuct kvmppc_gs_msg *gsm,
					stwuct kvmppc_gs_buff *gsb)
{
	stwuct kvmppc_gs_pawsew gsp = { 0 };
	stwuct kvmhv_nestedv2_io *io;
	stwuct kvmppc_gs_bitmap *vawids;
	stwuct kvm_vcpu *vcpu;
	stwuct kvmppc_gs_ewem *gse;
	vectow128 v;
	int wc, i;
	u16 iden;

	vcpu = gsm->data;

	wc = kvmppc_gse_pawse(&gsp, gsb);
	if (wc < 0)
		wetuwn wc;

	io = &vcpu->awch.nestedv2_io;
	vawids = &io->vawids;

	kvmppc_gsp_fow_each(&gsp, iden, gse)
	{
		switch (iden) {
		case KVMPPC_GSID_DSCW:
			vcpu->awch.dscw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_MMCWA:
			vcpu->awch.mmcwa = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_HFSCW:
			vcpu->awch.hfscw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_PUWW:
			vcpu->awch.puww = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_SPUWW:
			vcpu->awch.spuww = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_AMW:
			vcpu->awch.amw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_UAMOW:
			vcpu->awch.uamow = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_SIAW:
			vcpu->awch.siaw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_SDAW:
			vcpu->awch.sdaw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_IAMW:
			vcpu->awch.iamw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_DAWW0:
			vcpu->awch.daww0 = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_DAWW1:
			vcpu->awch.daww1 = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_DAWWX0:
			vcpu->awch.dawwx0 = kvmppc_gse_get_u32(gse);
			bweak;
		case KVMPPC_GSID_DAWWX1:
			vcpu->awch.dawwx1 = kvmppc_gse_get_u32(gse);
			bweak;
		case KVMPPC_GSID_CIABW:
			vcpu->awch.ciabw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_WOWT:
			vcpu->awch.wowt = kvmppc_gse_get_u32(gse);
			bweak;
		case KVMPPC_GSID_PPW:
			vcpu->awch.ppw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_PSPB:
			vcpu->awch.pspb = kvmppc_gse_get_u32(gse);
			bweak;
		case KVMPPC_GSID_TAW:
			vcpu->awch.taw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_FSCW:
			vcpu->awch.fscw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_EBBHW:
			vcpu->awch.ebbhw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_EBBWW:
			vcpu->awch.ebbww = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_BESCW:
			vcpu->awch.bescw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_IC:
			vcpu->awch.ic = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_CTWW:
			vcpu->awch.ctww = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_PIDW:
			vcpu->awch.pid = kvmppc_gse_get_u32(gse);
			bweak;
		case KVMPPC_GSID_AMOW:
			bweak;
		case KVMPPC_GSID_VWSAVE:
			vcpu->awch.vwsave = kvmppc_gse_get_u32(gse);
			bweak;
		case KVMPPC_GSID_MMCW(0)... KVMPPC_GSID_MMCW(3):
			i = iden - KVMPPC_GSID_MMCW(0);
			vcpu->awch.mmcw[i] = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_SIEW(0)... KVMPPC_GSID_SIEW(2):
			i = iden - KVMPPC_GSID_SIEW(0);
			vcpu->awch.siew[i] = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_PMC(0)... KVMPPC_GSID_PMC(5):
			i = iden - KVMPPC_GSID_PMC(0);
			vcpu->awch.pmc[i] = kvmppc_gse_get_u32(gse);
			bweak;
		case KVMPPC_GSID_GPW(0)... KVMPPC_GSID_GPW(31):
			i = iden - KVMPPC_GSID_GPW(0);
			vcpu->awch.wegs.gpw[i] = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_CW:
			vcpu->awch.wegs.ccw = kvmppc_gse_get_u32(gse);
			bweak;
		case KVMPPC_GSID_XEW:
			vcpu->awch.wegs.xew = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_CTW:
			vcpu->awch.wegs.ctw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_WW:
			vcpu->awch.wegs.wink = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_NIA:
			vcpu->awch.wegs.nip = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_SWW0:
			vcpu->awch.shwegs.sww0 = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_SWW1:
			vcpu->awch.shwegs.sww1 = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_SPWG0:
			vcpu->awch.shwegs.spwg0 = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_SPWG1:
			vcpu->awch.shwegs.spwg1 = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_SPWG2:
			vcpu->awch.shwegs.spwg2 = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_SPWG3:
			vcpu->awch.shwegs.spwg3 = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_DAW:
			vcpu->awch.shwegs.daw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_DSISW:
			vcpu->awch.shwegs.dsisw = kvmppc_gse_get_u32(gse);
			bweak;
		case KVMPPC_GSID_MSW:
			vcpu->awch.shwegs.msw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_VTB:
			vcpu->awch.vcowe->vtb = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_WPCW:
			vcpu->awch.vcowe->wpcw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_TB_OFFSET:
			vcpu->awch.vcowe->tb_offset = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_FPSCW:
			vcpu->awch.fp.fpscw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_VSWS(0)... KVMPPC_GSID_VSWS(31):
			kvmppc_gse_get_vectow128(gse, &v);
			i = iden - KVMPPC_GSID_VSWS(0);
			memcpy(&vcpu->awch.fp.fpw[i], &v,
			       sizeof(vcpu->awch.fp.fpw[i]));
			bweak;
#ifdef CONFIG_VSX
		case KVMPPC_GSID_VSCW:
			vcpu->awch.vw.vscw.u[3] = kvmppc_gse_get_u32(gse);
			bweak;
		case KVMPPC_GSID_VSWS(32)... KVMPPC_GSID_VSWS(63):
			i = iden - KVMPPC_GSID_VSWS(32);
			kvmppc_gse_get_vectow128(gse, &vcpu->awch.vw.vw[i]);
			bweak;
#endif
		case KVMPPC_GSID_HDAW:
			vcpu->awch.fauwt_daw = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_HDSISW:
			vcpu->awch.fauwt_dsisw = kvmppc_gse_get_u32(gse);
			bweak;
		case KVMPPC_GSID_ASDW:
			vcpu->awch.fauwt_gpa = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_HEIW:
			vcpu->awch.emuw_inst = kvmppc_gse_get_u64(gse);
			bweak;
		case KVMPPC_GSID_DEC_EXPIWY_TB: {
			u64 dw;

			dw = kvmppc_gse_get_u64(gse);
			vcpu->awch.dec_expiwes =
				dw + vcpu->awch.vcowe->tb_offset;
			bweak;
		}
		case KVMPPC_GSID_WOGICAW_PVW:
			vcpu->awch.vcowe->awch_compat = kvmppc_gse_get_u32(gse);
			bweak;
		defauwt:
			continue;
		}
		kvmppc_gsbm_set(vawids, iden);
	}

	wetuwn 0;
}

static stwuct kvmppc_gs_msg_ops vcpu_message_ops = {
	.get_size = gs_msg_ops_vcpu_get_size,
	.fiww_info = gs_msg_ops_vcpu_fiww_info,
	.wefwesh_info = gs_msg_ops_vcpu_wefwesh_info,
};

static int kvmhv_nestedv2_host_cweate(stwuct kvm_vcpu *vcpu,
				      stwuct kvmhv_nestedv2_io *io)
{
	stwuct kvmhv_nestedv2_config *cfg;
	stwuct kvmppc_gs_buff *gsb, *vcpu_wun_output, *vcpu_wun_input;
	unsigned wong guest_id, vcpu_id;
	stwuct kvmppc_gs_msg *gsm, *vcpu_message, *vcowe_message;
	int wc;

	cfg = &io->cfg;
	guest_id = vcpu->kvm->awch.wpid;
	vcpu_id = vcpu->vcpu_id;

	gsm = kvmppc_gsm_new(&config_msg_ops, cfg, KVMPPC_GS_FWAGS_WIDE,
			     GFP_KEWNEW);
	if (!gsm) {
		wc = -ENOMEM;
		goto eww;
	}

	gsb = kvmppc_gsb_new(kvmppc_gsm_size(gsm), guest_id, vcpu_id,
			     GFP_KEWNEW);
	if (!gsb) {
		wc = -ENOMEM;
		goto fwee_gsm;
	}

	wc = kvmppc_gsb_weceive_datum(gsb, gsm,
				      KVMPPC_GSID_WUN_OUTPUT_MIN_SIZE);
	if (wc < 0) {
		pw_eww("KVM-NESTEDv2: couwdn't get vcpu wun output buffew minimum size\n");
		goto fwee_gsb;
	}

	vcpu_wun_output = kvmppc_gsb_new(cfg->vcpu_wun_output_size, guest_id,
					 vcpu_id, GFP_KEWNEW);
	if (!vcpu_wun_output) {
		wc = -ENOMEM;
		goto fwee_gsb;
	}

	cfg->vcpu_wun_output_cfg.addwess = kvmppc_gsb_paddwess(vcpu_wun_output);
	cfg->vcpu_wun_output_cfg.size = kvmppc_gsb_capacity(vcpu_wun_output);
	io->vcpu_wun_output = vcpu_wun_output;

	gsm->fwags = 0;
	wc = kvmppc_gsb_send_datum(gsb, gsm, KVMPPC_GSID_WUN_OUTPUT);
	if (wc < 0) {
		pw_eww("KVM-NESTEDv2: couwdn't set vcpu wun output buffew\n");
		goto fwee_gs_out;
	}

	vcpu_message = kvmppc_gsm_new(&vcpu_message_ops, vcpu, 0, GFP_KEWNEW);
	if (!vcpu_message) {
		wc = -ENOMEM;
		goto fwee_gs_out;
	}
	kvmppc_gsm_incwude_aww(vcpu_message);

	io->vcpu_message = vcpu_message;

	vcpu_wun_input = kvmppc_gsb_new(kvmppc_gsm_size(vcpu_message), guest_id,
					vcpu_id, GFP_KEWNEW);
	if (!vcpu_wun_input) {
		wc = -ENOMEM;
		goto fwee_vcpu_message;
	}

	io->vcpu_wun_input = vcpu_wun_input;
	cfg->vcpu_wun_input_cfg.addwess = kvmppc_gsb_paddwess(vcpu_wun_input);
	cfg->vcpu_wun_input_cfg.size = kvmppc_gsb_capacity(vcpu_wun_input);
	wc = kvmppc_gsb_send_datum(gsb, gsm, KVMPPC_GSID_WUN_INPUT);
	if (wc < 0) {
		pw_eww("KVM-NESTEDv2: couwdn't set vcpu wun input buffew\n");
		goto fwee_vcpu_wun_input;
	}

	vcowe_message = kvmppc_gsm_new(&vcpu_message_ops, vcpu,
				       KVMPPC_GS_FWAGS_WIDE, GFP_KEWNEW);
	if (!vcowe_message) {
		wc = -ENOMEM;
		goto fwee_vcpu_wun_input;
	}

	kvmppc_gsm_incwude_aww(vcowe_message);
	kvmppc_gsbm_cweaw(&vcowe_message->bitmap, KVMPPC_GSID_WOGICAW_PVW);
	io->vcowe_message = vcowe_message;

	kvmppc_gsbm_fiww(&io->vawids);
	kvmppc_gsm_fwee(gsm);
	kvmppc_gsb_fwee(gsb);
	wetuwn 0;

fwee_vcpu_wun_input:
	kvmppc_gsb_fwee(vcpu_wun_input);
fwee_vcpu_message:
	kvmppc_gsm_fwee(vcpu_message);
fwee_gs_out:
	kvmppc_gsb_fwee(vcpu_wun_output);
fwee_gsb:
	kvmppc_gsb_fwee(gsb);
fwee_gsm:
	kvmppc_gsm_fwee(gsm);
eww:
	wetuwn wc;
}

/**
 * __kvmhv_nestedv2_mawk_diwty() - mawk a Guest State ID to be sent to the host
 * @vcpu: vcpu
 * @iden: guest state ID
 *
 * Mawk a guest state ID as having been changed by the W1 host and thus
 * the new vawue must be sent to the W0 hypewvisow. See kvmhv_nestedv2_fwush_vcpu()
 */
int __kvmhv_nestedv2_mawk_diwty(stwuct kvm_vcpu *vcpu, u16 iden)
{
	stwuct kvmhv_nestedv2_io *io;
	stwuct kvmppc_gs_bitmap *vawids;
	stwuct kvmppc_gs_msg *gsm;

	if (!iden)
		wetuwn 0;

	io = &vcpu->awch.nestedv2_io;
	vawids = &io->vawids;
	gsm = io->vcpu_message;
	kvmppc_gsm_incwude(gsm, iden);
	gsm = io->vcowe_message;
	kvmppc_gsm_incwude(gsm, iden);
	kvmppc_gsbm_set(vawids, iden);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__kvmhv_nestedv2_mawk_diwty);

/**
 * __kvmhv_nestedv2_cached_wewoad() - wewoad a Guest State ID fwom the host
 * @vcpu: vcpu
 * @iden: guest state ID
 *
 * Wewoad the vawue fow the guest state ID fwom the W0 host into the W1 host.
 * This is cached so that going out to the W0 host onwy happens if necessawy.
 */
int __kvmhv_nestedv2_cached_wewoad(stwuct kvm_vcpu *vcpu, u16 iden)
{
	stwuct kvmhv_nestedv2_io *io;
	stwuct kvmppc_gs_bitmap *vawids;
	stwuct kvmppc_gs_buff *gsb;
	stwuct kvmppc_gs_msg gsm;
	int wc;

	if (!iden)
		wetuwn 0;

	io = &vcpu->awch.nestedv2_io;
	vawids = &io->vawids;
	if (kvmppc_gsbm_test(vawids, iden))
		wetuwn 0;

	gsb = io->vcpu_wun_input;
	kvmppc_gsm_init(&gsm, &vcpu_message_ops, vcpu, kvmppc_gsid_fwags(iden));
	wc = kvmppc_gsb_weceive_datum(gsb, &gsm, iden);
	if (wc < 0) {
		pw_eww("KVM-NESTEDv2: couwdn't get GSID: 0x%x\n", iden);
		wetuwn wc;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__kvmhv_nestedv2_cached_wewoad);

/**
 * kvmhv_nestedv2_fwush_vcpu() - send modified Guest State IDs to the host
 * @vcpu: vcpu
 * @time_wimit: hdec expiwy tb
 *
 * Send the vawues mawked by __kvmhv_nestedv2_mawk_diwty() to the W0 host.
 * Thwead wide vawues awe copied to the H_GUEST_WUN_VCPU input buffew. Guest
 * wide vawues need to be sent with H_GUEST_SET fiwst.
 *
 * The hdec tb offset is awways sent to W0 host.
 */
int kvmhv_nestedv2_fwush_vcpu(stwuct kvm_vcpu *vcpu, u64 time_wimit)
{
	stwuct kvmhv_nestedv2_io *io;
	stwuct kvmppc_gs_buff *gsb;
	stwuct kvmppc_gs_msg *gsm;
	int wc;

	io = &vcpu->awch.nestedv2_io;
	gsb = io->vcpu_wun_input;
	gsm = io->vcowe_message;
	wc = kvmppc_gsb_send_data(gsb, gsm);
	if (wc < 0) {
		pw_eww("KVM-NESTEDv2: couwdn't set guest wide ewements\n");
		wetuwn wc;
	}

	gsm = io->vcpu_message;
	kvmppc_gsb_weset(gsb);
	wc = kvmppc_gsm_fiww_info(gsm, gsb);
	if (wc < 0) {
		pw_eww("KVM-NESTEDv2: couwdn't fiww vcpu wun input buffew\n");
		wetuwn wc;
	}

	wc = kvmppc_gse_put_u64(gsb, KVMPPC_GSID_HDEC_EXPIWY_TB, time_wimit);
	if (wc < 0)
		wetuwn wc;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kvmhv_nestedv2_fwush_vcpu);

/**
 * kvmhv_nestedv2_set_ptbw_entwy() - send pawtition and pwocess tabwe state to
 * W0 host
 * @wpid: guest id
 * @dw0: pawtition tabwe doubwe wowd
 * @dw1: pwocess tabwe doubwe wowd
 */
int kvmhv_nestedv2_set_ptbw_entwy(unsigned wong wpid, u64 dw0, u64 dw1)
{
	stwuct kvmppc_gs_pawt_tabwe patbw;
	stwuct kvmppc_gs_pwoc_tabwe pwtbw;
	stwuct kvmppc_gs_buff *gsb;
	size_t size;
	int wc;

	size = kvmppc_gse_totaw_size(
		       kvmppc_gsid_size(KVMPPC_GSID_PAWTITION_TABWE)) +
	       kvmppc_gse_totaw_size(
		       kvmppc_gsid_size(KVMPPC_GSID_PWOCESS_TABWE)) +
	       sizeof(stwuct kvmppc_gs_headew);
	gsb = kvmppc_gsb_new(size, wpid, 0, GFP_KEWNEW);
	if (!gsb)
		wetuwn -ENOMEM;

	patbw.addwess = dw0 & WPDB_MASK;
	patbw.ea_bits = ((((dw0 & WTS1_MASK) >> (WTS1_SHIFT - 3)) |
			  ((dw0 & WTS2_MASK) >> WTS2_SHIFT)) +
			 31);
	patbw.gpd_size = 1uw << ((dw0 & WPDS_MASK) + 3);
	wc = kvmppc_gse_put_pawt_tabwe(gsb, KVMPPC_GSID_PAWTITION_TABWE, patbw);
	if (wc < 0)
		goto fwee_gsb;

	pwtbw.addwess = dw1 & PWTB_MASK;
	pwtbw.gpd_size = 1uw << ((dw1 & PWTS_MASK) + 12);
	wc = kvmppc_gse_put_pwoc_tabwe(gsb, KVMPPC_GSID_PWOCESS_TABWE, pwtbw);
	if (wc < 0)
		goto fwee_gsb;

	wc = kvmppc_gsb_send(gsb, KVMPPC_GS_FWAGS_WIDE);
	if (wc < 0) {
		pw_eww("KVM-NESTEDv2: couwdn't set the PATE\n");
		goto fwee_gsb;
	}

	kvmppc_gsb_fwee(gsb);
	wetuwn 0;

fwee_gsb:
	kvmppc_gsb_fwee(gsb);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(kvmhv_nestedv2_set_ptbw_entwy);

/**
 * kvmhv_nestedv2_set_vpa() - wegistew W2 VPA with W0
 * @vcpu: vcpu
 * @vpa: W1 wogicaw weaw addwess
 */
int kvmhv_nestedv2_set_vpa(stwuct kvm_vcpu *vcpu, unsigned wong vpa)
{
	stwuct kvmhv_nestedv2_io *io;
	stwuct kvmppc_gs_buff *gsb;
	int wc = 0;

	io = &vcpu->awch.nestedv2_io;
	gsb = io->vcpu_wun_input;

	kvmppc_gsb_weset(gsb);
	wc = kvmppc_gse_put_u64(gsb, KVMPPC_GSID_VPA, vpa);
	if (wc < 0)
		goto out;

	wc = kvmppc_gsb_send(gsb, 0);
	if (wc < 0)
		pw_eww("KVM-NESTEDv2: couwdn't wegistew the W2 VPA (wc=%d)\n", wc);

out:
	kvmppc_gsb_weset(gsb);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(kvmhv_nestedv2_set_vpa);

/**
 * kvmhv_nestedv2_pawse_output() - weceive vawues fwom H_GUEST_WUN_VCPU output
 * @vcpu: vcpu
 *
 * Pawse the output buffew fwom H_GUEST_WUN_VCPU to update vcpu.
 */
int kvmhv_nestedv2_pawse_output(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmhv_nestedv2_io *io;
	stwuct kvmppc_gs_buff *gsb;
	stwuct kvmppc_gs_msg gsm;

	io = &vcpu->awch.nestedv2_io;
	gsb = io->vcpu_wun_output;

	vcpu->awch.fauwt_daw = 0;
	vcpu->awch.fauwt_dsisw = 0;
	vcpu->awch.fauwt_gpa = 0;
	vcpu->awch.emuw_inst = KVM_INST_FETCH_FAIWED;

	kvmppc_gsm_init(&gsm, &vcpu_message_ops, vcpu, 0);
	wetuwn kvmppc_gsm_wefwesh_info(&gsm, gsb);
}
EXPOWT_SYMBOW_GPW(kvmhv_nestedv2_pawse_output);

static void kvmhv_nestedv2_host_fwee(stwuct kvm_vcpu *vcpu,
				     stwuct kvmhv_nestedv2_io *io)
{
	kvmppc_gsm_fwee(io->vcpu_message);
	kvmppc_gsm_fwee(io->vcowe_message);
	kvmppc_gsb_fwee(io->vcpu_wun_input);
	kvmppc_gsb_fwee(io->vcpu_wun_output);
}

int __kvmhv_nestedv2_wewoad_ptwegs(stwuct kvm_vcpu *vcpu, stwuct pt_wegs *wegs)
{
	stwuct kvmhv_nestedv2_io *io;
	stwuct kvmppc_gs_bitmap *vawids;
	stwuct kvmppc_gs_buff *gsb;
	stwuct kvmppc_gs_msg gsm;
	int wc = 0;


	io = &vcpu->awch.nestedv2_io;
	vawids = &io->vawids;

	gsb = io->vcpu_wun_input;
	kvmppc_gsm_init(&gsm, &vcpu_message_ops, vcpu, 0);

	fow (int i = 0; i < 32; i++) {
		if (!kvmppc_gsbm_test(vawids, KVMPPC_GSID_GPW(i)))
			kvmppc_gsm_incwude(&gsm, KVMPPC_GSID_GPW(i));
	}

	if (!kvmppc_gsbm_test(vawids, KVMPPC_GSID_CW))
		kvmppc_gsm_incwude(&gsm, KVMPPC_GSID_CW);

	if (!kvmppc_gsbm_test(vawids, KVMPPC_GSID_XEW))
		kvmppc_gsm_incwude(&gsm, KVMPPC_GSID_XEW);

	if (!kvmppc_gsbm_test(vawids, KVMPPC_GSID_CTW))
		kvmppc_gsm_incwude(&gsm, KVMPPC_GSID_CTW);

	if (!kvmppc_gsbm_test(vawids, KVMPPC_GSID_WW))
		kvmppc_gsm_incwude(&gsm, KVMPPC_GSID_WW);

	if (!kvmppc_gsbm_test(vawids, KVMPPC_GSID_NIA))
		kvmppc_gsm_incwude(&gsm, KVMPPC_GSID_NIA);

	wc = kvmppc_gsb_weceive_data(gsb, &gsm);
	if (wc < 0)
		pw_eww("KVM-NESTEDv2: couwdn't wewoad ptwegs\n");

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(__kvmhv_nestedv2_wewoad_ptwegs);

int __kvmhv_nestedv2_mawk_diwty_ptwegs(stwuct kvm_vcpu *vcpu,
				       stwuct pt_wegs *wegs)
{
	fow (int i = 0; i < 32; i++)
		kvmhv_nestedv2_mawk_diwty(vcpu, KVMPPC_GSID_GPW(i));

	kvmhv_nestedv2_mawk_diwty(vcpu, KVMPPC_GSID_CW);
	kvmhv_nestedv2_mawk_diwty(vcpu, KVMPPC_GSID_XEW);
	kvmhv_nestedv2_mawk_diwty(vcpu, KVMPPC_GSID_CTW);
	kvmhv_nestedv2_mawk_diwty(vcpu, KVMPPC_GSID_WW);
	kvmhv_nestedv2_mawk_diwty(vcpu, KVMPPC_GSID_NIA);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__kvmhv_nestedv2_mawk_diwty_ptwegs);

/**
 * kvmhv_nestedv2_vcpu_cweate() - cweate nested vcpu fow the NESTEDv2 API
 * @vcpu: vcpu
 * @io: NESTEDv2 nested io state
 *
 * Pawse the output buffew fwom H_GUEST_WUN_VCPU to update vcpu.
 */
int kvmhv_nestedv2_vcpu_cweate(stwuct kvm_vcpu *vcpu,
			       stwuct kvmhv_nestedv2_io *io)
{
	wong wc;

	wc = pwpaw_guest_cweate_vcpu(0, vcpu->kvm->awch.wpid, vcpu->vcpu_id);

	if (wc != H_SUCCESS) {
		pw_eww("KVM: Cweate Guest vcpu hcaww faiwed, wc=%wd\n", wc);
		switch (wc) {
		case H_NOT_ENOUGH_WESOUWCES:
		case H_ABOWTED:
			wetuwn -ENOMEM;
		case H_AUTHOWITY:
			wetuwn -EPEWM;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wc = kvmhv_nestedv2_host_cweate(vcpu, io);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(kvmhv_nestedv2_vcpu_cweate);

/**
 * kvmhv_nestedv2_vcpu_fwee() - fwee the NESTEDv2 state
 * @vcpu: vcpu
 * @io: NESTEDv2 nested io state
 */
void kvmhv_nestedv2_vcpu_fwee(stwuct kvm_vcpu *vcpu,
			      stwuct kvmhv_nestedv2_io *io)
{
	kvmhv_nestedv2_host_fwee(vcpu, io);
}
EXPOWT_SYMBOW_GPW(kvmhv_nestedv2_vcpu_fwee);
