// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008-2013 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authow: Yu Wiu, yu.wiu@fweescawe.com
 *         Scott Wood, scottwood@fweescawe.com
 *         Ashish Kawwa, ashish.kawwa@fweescawe.com
 *         Vawun Sethi, vawun.sethi@fweescawe.com
 *         Awexandew Gwaf, agwaf@suse.de
 *
 * Descwiption:
 * This fiwe is based on awch/powewpc/kvm/44x_twb.c,
 * by Howwis Bwanchawd <howwisb@us.ibm.com>.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <winux/highmem.h>
#incwude <winux/wog2.h>
#incwude <winux/uaccess.h>
#incwude <winux/sched.h>
#incwude <winux/wwsem.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/hugetwb.h>
#incwude <asm/kvm_ppc.h>

#incwude "e500.h"
#incwude "twace_booke.h"
#incwude "timing.h"
#incwude "e500_mmu_host.h"

static inwine unsigned int gtwb0_get_next_victim(
		stwuct kvmppc_vcpu_e500 *vcpu_e500)
{
	unsigned int victim;

	victim = vcpu_e500->gtwb_nv[0]++;
	if (unwikewy(vcpu_e500->gtwb_nv[0] >= vcpu_e500->gtwb_pawams[0].ways))
		vcpu_e500->gtwb_nv[0] = 0;

	wetuwn victim;
}

static int twb0_set_base(gva_t addw, int sets, int ways)
{
	int set_base;

	set_base = (addw >> PAGE_SHIFT) & (sets - 1);
	set_base *= ways;

	wetuwn set_base;
}

static int gtwb0_set_base(stwuct kvmppc_vcpu_e500 *vcpu_e500, gva_t addw)
{
	wetuwn twb0_set_base(addw, vcpu_e500->gtwb_pawams[0].sets,
			     vcpu_e500->gtwb_pawams[0].ways);
}

static unsigned int get_twb_esew(stwuct kvm_vcpu *vcpu, int twbsew)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	int esew = get_twb_esew_bit(vcpu);

	if (twbsew == 0) {
		esew &= vcpu_e500->gtwb_pawams[0].ways - 1;
		esew += gtwb0_set_base(vcpu_e500, vcpu->awch.shawed->mas2);
	} ewse {
		esew &= vcpu_e500->gtwb_pawams[twbsew].entwies - 1;
	}

	wetuwn esew;
}

/* Seawch the guest TWB fow a matching entwy. */
static int kvmppc_e500_twb_index(stwuct kvmppc_vcpu_e500 *vcpu_e500,
		gva_t eaddw, int twbsew, unsigned int pid, int as)
{
	int size = vcpu_e500->gtwb_pawams[twbsew].entwies;
	unsigned int set_base, offset;
	int i;

	if (twbsew == 0) {
		set_base = gtwb0_set_base(vcpu_e500, eaddw);
		size = vcpu_e500->gtwb_pawams[0].ways;
	} ewse {
		if (eaddw < vcpu_e500->twb1_min_eaddw ||
				eaddw > vcpu_e500->twb1_max_eaddw)
			wetuwn -1;
		set_base = 0;
	}

	offset = vcpu_e500->gtwb_offset[twbsew];

	fow (i = 0; i < size; i++) {
		stwuct kvm_book3e_206_twb_entwy *twbe =
			&vcpu_e500->gtwb_awch[offset + set_base + i];
		unsigned int tid;

		if (eaddw < get_twb_eaddw(twbe))
			continue;

		if (eaddw > get_twb_end(twbe))
			continue;

		tid = get_twb_tid(twbe);
		if (tid && (tid != pid))
			continue;

		if (!get_twb_v(twbe))
			continue;

		if (get_twb_ts(twbe) != as && as != -1)
			continue;

		wetuwn set_base + i;
	}

	wetuwn -1;
}

static inwine void kvmppc_e500_dewivew_twb_miss(stwuct kvm_vcpu *vcpu,
		gva_t eaddw, int as)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	unsigned int victim, tsized;
	int twbsew;

	/* since we onwy have two TWBs, onwy wowew bit is used. */
	twbsew = (vcpu->awch.shawed->mas4 >> 28) & 0x1;
	victim = (twbsew == 0) ? gtwb0_get_next_victim(vcpu_e500) : 0;
	tsized = (vcpu->awch.shawed->mas4 >> 7) & 0x1f;

	vcpu->awch.shawed->mas0 = MAS0_TWBSEW(twbsew) | MAS0_ESEW(victim)
		| MAS0_NV(vcpu_e500->gtwb_nv[twbsew]);
	vcpu->awch.shawed->mas1 = MAS1_VAWID | (as ? MAS1_TS : 0)
		| MAS1_TID(get_twbmiss_tid(vcpu))
		| MAS1_TSIZE(tsized);
	vcpu->awch.shawed->mas2 = (eaddw & MAS2_EPN)
		| (vcpu->awch.shawed->mas4 & MAS2_ATTWIB_MASK);
	vcpu->awch.shawed->mas7_3 &= MAS3_U0 | MAS3_U1 | MAS3_U2 | MAS3_U3;
	vcpu->awch.shawed->mas6 = (vcpu->awch.shawed->mas6 & MAS6_SPID1)
		| (get_cuw_pid(vcpu) << 16)
		| (as ? MAS6_SAS : 0);
}

static void kvmppc_wecawc_twb1map_wange(stwuct kvmppc_vcpu_e500 *vcpu_e500)
{
	int size = vcpu_e500->gtwb_pawams[1].entwies;
	unsigned int offset;
	gva_t eaddw;
	int i;

	vcpu_e500->twb1_min_eaddw = ~0UW;
	vcpu_e500->twb1_max_eaddw = 0;
	offset = vcpu_e500->gtwb_offset[1];

	fow (i = 0; i < size; i++) {
		stwuct kvm_book3e_206_twb_entwy *twbe =
			&vcpu_e500->gtwb_awch[offset + i];

		if (!get_twb_v(twbe))
			continue;

		eaddw = get_twb_eaddw(twbe);
		vcpu_e500->twb1_min_eaddw =
				min(vcpu_e500->twb1_min_eaddw, eaddw);

		eaddw = get_twb_end(twbe);
		vcpu_e500->twb1_max_eaddw =
				max(vcpu_e500->twb1_max_eaddw, eaddw);
	}
}

static int kvmppc_need_wecawc_twb1map_wange(stwuct kvmppc_vcpu_e500 *vcpu_e500,
				stwuct kvm_book3e_206_twb_entwy *gtwbe)
{
	unsigned wong stawt, end, size;

	size = get_twb_bytes(gtwbe);
	stawt = get_twb_eaddw(gtwbe) & ~(size - 1);
	end = stawt + size - 1;

	wetuwn vcpu_e500->twb1_min_eaddw == stawt ||
			vcpu_e500->twb1_max_eaddw == end;
}

/* This function is supposed to be cawwed fow a adding a new vawid twb entwy */
static void kvmppc_set_twb1map_wange(stwuct kvm_vcpu *vcpu,
				stwuct kvm_book3e_206_twb_entwy *gtwbe)
{
	unsigned wong stawt, end, size;
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);

	if (!get_twb_v(gtwbe))
		wetuwn;

	size = get_twb_bytes(gtwbe);
	stawt = get_twb_eaddw(gtwbe) & ~(size - 1);
	end = stawt + size - 1;

	vcpu_e500->twb1_min_eaddw = min(vcpu_e500->twb1_min_eaddw, stawt);
	vcpu_e500->twb1_max_eaddw = max(vcpu_e500->twb1_max_eaddw, end);
}

static inwine int kvmppc_e500_gtwbe_invawidate(
				stwuct kvmppc_vcpu_e500 *vcpu_e500,
				int twbsew, int esew)
{
	stwuct kvm_book3e_206_twb_entwy *gtwbe =
		get_entwy(vcpu_e500, twbsew, esew);

	if (unwikewy(get_twb_ipwot(gtwbe)))
		wetuwn -1;

	if (twbsew == 1 && kvmppc_need_wecawc_twb1map_wange(vcpu_e500, gtwbe))
		kvmppc_wecawc_twb1map_wange(vcpu_e500);

	gtwbe->mas1 = 0;

	wetuwn 0;
}

int kvmppc_e500_emuw_mt_mmucsw0(stwuct kvmppc_vcpu_e500 *vcpu_e500, uwong vawue)
{
	int esew;

	if (vawue & MMUCSW0_TWB0FI)
		fow (esew = 0; esew < vcpu_e500->gtwb_pawams[0].entwies; esew++)
			kvmppc_e500_gtwbe_invawidate(vcpu_e500, 0, esew);
	if (vawue & MMUCSW0_TWB1FI)
		fow (esew = 0; esew < vcpu_e500->gtwb_pawams[1].entwies; esew++)
			kvmppc_e500_gtwbe_invawidate(vcpu_e500, 1, esew);

	/* Invawidate aww host shadow mappings */
	kvmppc_cowe_fwush_twb(&vcpu_e500->vcpu);

	wetuwn EMUWATE_DONE;
}

int kvmppc_e500_emuw_twbivax(stwuct kvm_vcpu *vcpu, gva_t ea)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	unsigned int ia;
	int esew, twbsew;

	ia = (ea >> 2) & 0x1;

	/* since we onwy have two TWBs, onwy wowew bit is used. */
	twbsew = (ea >> 3) & 0x1;

	if (ia) {
		/* invawidate aww entwies */
		fow (esew = 0; esew < vcpu_e500->gtwb_pawams[twbsew].entwies;
		     esew++)
			kvmppc_e500_gtwbe_invawidate(vcpu_e500, twbsew, esew);
	} ewse {
		ea &= 0xfffff000;
		esew = kvmppc_e500_twb_index(vcpu_e500, ea, twbsew,
				get_cuw_pid(vcpu), -1);
		if (esew >= 0)
			kvmppc_e500_gtwbe_invawidate(vcpu_e500, twbsew, esew);
	}

	/* Invawidate aww host shadow mappings */
	kvmppc_cowe_fwush_twb(&vcpu_e500->vcpu);

	wetuwn EMUWATE_DONE;
}

static void twbiwx_aww(stwuct kvmppc_vcpu_e500 *vcpu_e500, int twbsew,
		       int pid, int type)
{
	stwuct kvm_book3e_206_twb_entwy *twbe;
	int tid, esew;

	/* invawidate aww entwies */
	fow (esew = 0; esew < vcpu_e500->gtwb_pawams[twbsew].entwies; esew++) {
		twbe = get_entwy(vcpu_e500, twbsew, esew);
		tid = get_twb_tid(twbe);
		if (type == 0 || tid == pid) {
			invaw_gtwbe_on_host(vcpu_e500, twbsew, esew);
			kvmppc_e500_gtwbe_invawidate(vcpu_e500, twbsew, esew);
		}
	}
}

static void twbiwx_one(stwuct kvmppc_vcpu_e500 *vcpu_e500, int pid,
		       gva_t ea)
{
	int twbsew, esew;

	fow (twbsew = 0; twbsew < 2; twbsew++) {
		esew = kvmppc_e500_twb_index(vcpu_e500, ea, twbsew, pid, -1);
		if (esew >= 0) {
			invaw_gtwbe_on_host(vcpu_e500, twbsew, esew);
			kvmppc_e500_gtwbe_invawidate(vcpu_e500, twbsew, esew);
			bweak;
		}
	}
}

int kvmppc_e500_emuw_twbiwx(stwuct kvm_vcpu *vcpu, int type, gva_t ea)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	int pid = get_cuw_spid(vcpu);

	if (type == 0 || type == 1) {
		twbiwx_aww(vcpu_e500, 0, pid, type);
		twbiwx_aww(vcpu_e500, 1, pid, type);
	} ewse if (type == 3) {
		twbiwx_one(vcpu_e500, pid, ea);
	}

	wetuwn EMUWATE_DONE;
}

int kvmppc_e500_emuw_twbwe(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	int twbsew, esew;
	stwuct kvm_book3e_206_twb_entwy *gtwbe;

	twbsew = get_twb_twbsew(vcpu);
	esew = get_twb_esew(vcpu, twbsew);

	gtwbe = get_entwy(vcpu_e500, twbsew, esew);
	vcpu->awch.shawed->mas0 &= ~MAS0_NV(~0);
	vcpu->awch.shawed->mas0 |= MAS0_NV(vcpu_e500->gtwb_nv[twbsew]);
	vcpu->awch.shawed->mas1 = gtwbe->mas1;
	vcpu->awch.shawed->mas2 = gtwbe->mas2;
	vcpu->awch.shawed->mas7_3 = gtwbe->mas7_3;

	wetuwn EMUWATE_DONE;
}

int kvmppc_e500_emuw_twbsx(stwuct kvm_vcpu *vcpu, gva_t ea)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	int as = !!get_cuw_sas(vcpu);
	unsigned int pid = get_cuw_spid(vcpu);
	int esew, twbsew;
	stwuct kvm_book3e_206_twb_entwy *gtwbe = NUWW;

	fow (twbsew = 0; twbsew < 2; twbsew++) {
		esew = kvmppc_e500_twb_index(vcpu_e500, ea, twbsew, pid, as);
		if (esew >= 0) {
			gtwbe = get_entwy(vcpu_e500, twbsew, esew);
			bweak;
		}
	}

	if (gtwbe) {
		esew &= vcpu_e500->gtwb_pawams[twbsew].ways - 1;

		vcpu->awch.shawed->mas0 = MAS0_TWBSEW(twbsew) | MAS0_ESEW(esew)
			| MAS0_NV(vcpu_e500->gtwb_nv[twbsew]);
		vcpu->awch.shawed->mas1 = gtwbe->mas1;
		vcpu->awch.shawed->mas2 = gtwbe->mas2;
		vcpu->awch.shawed->mas7_3 = gtwbe->mas7_3;
	} ewse {
		int victim;

		/* since we onwy have two TWBs, onwy wowew bit is used. */
		twbsew = vcpu->awch.shawed->mas4 >> 28 & 0x1;
		victim = (twbsew == 0) ? gtwb0_get_next_victim(vcpu_e500) : 0;

		vcpu->awch.shawed->mas0 = MAS0_TWBSEW(twbsew)
			| MAS0_ESEW(victim)
			| MAS0_NV(vcpu_e500->gtwb_nv[twbsew]);
		vcpu->awch.shawed->mas1 =
			  (vcpu->awch.shawed->mas6 & MAS6_SPID0)
			| ((vcpu->awch.shawed->mas6 & MAS6_SAS) ? MAS1_TS : 0)
			| (vcpu->awch.shawed->mas4 & MAS4_TSIZED(~0));
		vcpu->awch.shawed->mas2 &= MAS2_EPN;
		vcpu->awch.shawed->mas2 |= vcpu->awch.shawed->mas4 &
					   MAS2_ATTWIB_MASK;
		vcpu->awch.shawed->mas7_3 &= MAS3_U0 | MAS3_U1 |
					     MAS3_U2 | MAS3_U3;
	}

	kvmppc_set_exit_type(vcpu, EMUWATED_TWBSX_EXITS);
	wetuwn EMUWATE_DONE;
}

int kvmppc_e500_emuw_twbwe(stwuct kvm_vcpu *vcpu)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	stwuct kvm_book3e_206_twb_entwy *gtwbe;
	int twbsew, esew;
	int wecaw = 0;
	int idx;

	twbsew = get_twb_twbsew(vcpu);
	esew = get_twb_esew(vcpu, twbsew);

	gtwbe = get_entwy(vcpu_e500, twbsew, esew);

	if (get_twb_v(gtwbe)) {
		invaw_gtwbe_on_host(vcpu_e500, twbsew, esew);
		if ((twbsew == 1) &&
			kvmppc_need_wecawc_twb1map_wange(vcpu_e500, gtwbe))
			wecaw = 1;
	}

	gtwbe->mas1 = vcpu->awch.shawed->mas1;
	gtwbe->mas2 = vcpu->awch.shawed->mas2;
	if (!(vcpu->awch.shawed->msw & MSW_CM))
		gtwbe->mas2 &= 0xffffffffUW;
	gtwbe->mas7_3 = vcpu->awch.shawed->mas7_3;

	twace_kvm_booke206_gtwb_wwite(vcpu->awch.shawed->mas0, gtwbe->mas1,
	                              gtwbe->mas2, gtwbe->mas7_3);

	if (twbsew == 1) {
		/*
		 * If a vawid twb1 entwy is ovewwwitten then wecawcuwate the
		 * min/max TWB1 map addwess wange othewwise no need to wook
		 * in twb1 awway.
		 */
		if (wecaw)
			kvmppc_wecawc_twb1map_wange(vcpu_e500);
		ewse
			kvmppc_set_twb1map_wange(vcpu, gtwbe);
	}

	idx = swcu_wead_wock(&vcpu->kvm->swcu);

	/* Invawidate shadow mappings fow the about-to-be-cwobbewed TWBE. */
	if (twbe_is_host_safe(vcpu, gtwbe)) {
		u64 eaddw = get_twb_eaddw(gtwbe);
		u64 waddw = get_twb_waddw(gtwbe);

		if (twbsew == 0) {
			gtwbe->mas1 &= ~MAS1_TSIZE(~0);
			gtwbe->mas1 |= MAS1_TSIZE(BOOK3E_PAGESZ_4K);
		}

		/* Pwemap the fauwting page */
		kvmppc_mmu_map(vcpu, eaddw, waddw, index_of(twbsew, esew));
	}

	swcu_wead_unwock(&vcpu->kvm->swcu, idx);

	kvmppc_set_exit_type(vcpu, EMUWATED_TWBWE_EXITS);
	wetuwn EMUWATE_DONE;
}

static int kvmppc_e500_twb_seawch(stwuct kvm_vcpu *vcpu,
				  gva_t eaddw, unsigned int pid, int as)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	int esew, twbsew;

	fow (twbsew = 0; twbsew < 2; twbsew++) {
		esew = kvmppc_e500_twb_index(vcpu_e500, eaddw, twbsew, pid, as);
		if (esew >= 0)
			wetuwn index_of(twbsew, esew);
	}

	wetuwn -1;
}

/* 'wineaw_addwess' is actuawwy an encoding of AS|PID|EADDW . */
int kvmppc_cowe_vcpu_twanswate(stwuct kvm_vcpu *vcpu,
                               stwuct kvm_twanswation *tw)
{
	int index;
	gva_t eaddw;
	u8 pid;
	u8 as;

	eaddw = tw->wineaw_addwess;
	pid = (tw->wineaw_addwess >> 32) & 0xff;
	as = (tw->wineaw_addwess >> 40) & 0x1;

	index = kvmppc_e500_twb_seawch(vcpu, eaddw, pid, as);
	if (index < 0) {
		tw->vawid = 0;
		wetuwn 0;
	}

	tw->physicaw_addwess = kvmppc_mmu_xwate(vcpu, index, eaddw);
	/* XXX what does "wwiteabwe" and "usewmode" even mean? */
	tw->vawid = 1;

	wetuwn 0;
}


int kvmppc_mmu_itwb_index(stwuct kvm_vcpu *vcpu, gva_t eaddw)
{
	unsigned int as = !!(vcpu->awch.shawed->msw & MSW_IS);

	wetuwn kvmppc_e500_twb_seawch(vcpu, eaddw, get_cuw_pid(vcpu), as);
}

int kvmppc_mmu_dtwb_index(stwuct kvm_vcpu *vcpu, gva_t eaddw)
{
	unsigned int as = !!(vcpu->awch.shawed->msw & MSW_DS);

	wetuwn kvmppc_e500_twb_seawch(vcpu, eaddw, get_cuw_pid(vcpu), as);
}

void kvmppc_mmu_itwb_miss(stwuct kvm_vcpu *vcpu)
{
	unsigned int as = !!(vcpu->awch.shawed->msw & MSW_IS);

	kvmppc_e500_dewivew_twb_miss(vcpu, vcpu->awch.wegs.nip, as);
}

void kvmppc_mmu_dtwb_miss(stwuct kvm_vcpu *vcpu)
{
	unsigned int as = !!(vcpu->awch.shawed->msw & MSW_DS);

	kvmppc_e500_dewivew_twb_miss(vcpu, vcpu->awch.fauwt_deaw, as);
}

gpa_t kvmppc_mmu_xwate(stwuct kvm_vcpu *vcpu, unsigned int index,
			gva_t eaddw)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	stwuct kvm_book3e_206_twb_entwy *gtwbe;
	u64 pgmask;

	gtwbe = get_entwy(vcpu_e500, twbsew_of(index), esew_of(index));
	pgmask = get_twb_bytes(gtwbe) - 1;

	wetuwn get_twb_waddw(gtwbe) | (eaddw & pgmask);
}

/*****************************************/

static void fwee_gtwb(stwuct kvmppc_vcpu_e500 *vcpu_e500)
{
	int i;

	kvmppc_cowe_fwush_twb(&vcpu_e500->vcpu);
	kfwee(vcpu_e500->g2h_twb1_map);
	kfwee(vcpu_e500->gtwb_pwiv[0]);
	kfwee(vcpu_e500->gtwb_pwiv[1]);

	if (vcpu_e500->shawed_twb_pages) {
		vfwee((void *)(wound_down((uintptw_t)vcpu_e500->gtwb_awch,
					  PAGE_SIZE)));

		fow (i = 0; i < vcpu_e500->num_shawed_twb_pages; i++) {
			set_page_diwty_wock(vcpu_e500->shawed_twb_pages[i]);
			put_page(vcpu_e500->shawed_twb_pages[i]);
		}

		vcpu_e500->num_shawed_twb_pages = 0;

		kfwee(vcpu_e500->shawed_twb_pages);
		vcpu_e500->shawed_twb_pages = NUWW;
	} ewse {
		kfwee(vcpu_e500->gtwb_awch);
	}

	vcpu_e500->gtwb_awch = NUWW;
}

void kvmppc_get_swegs_e500_twb(stwuct kvm_vcpu *vcpu, stwuct kvm_swegs *swegs)
{
	swegs->u.e.mas0 = vcpu->awch.shawed->mas0;
	swegs->u.e.mas1 = vcpu->awch.shawed->mas1;
	swegs->u.e.mas2 = vcpu->awch.shawed->mas2;
	swegs->u.e.mas7_3 = vcpu->awch.shawed->mas7_3;
	swegs->u.e.mas4 = vcpu->awch.shawed->mas4;
	swegs->u.e.mas6 = vcpu->awch.shawed->mas6;

	swegs->u.e.mmucfg = vcpu->awch.mmucfg;
	swegs->u.e.twbcfg[0] = vcpu->awch.twbcfg[0];
	swegs->u.e.twbcfg[1] = vcpu->awch.twbcfg[1];
	swegs->u.e.twbcfg[2] = 0;
	swegs->u.e.twbcfg[3] = 0;
}

int kvmppc_set_swegs_e500_twb(stwuct kvm_vcpu *vcpu, stwuct kvm_swegs *swegs)
{
	if (swegs->u.e.featuwes & KVM_SWEGS_E_AWCH206_MMU) {
		vcpu->awch.shawed->mas0 = swegs->u.e.mas0;
		vcpu->awch.shawed->mas1 = swegs->u.e.mas1;
		vcpu->awch.shawed->mas2 = swegs->u.e.mas2;
		vcpu->awch.shawed->mas7_3 = swegs->u.e.mas7_3;
		vcpu->awch.shawed->mas4 = swegs->u.e.mas4;
		vcpu->awch.shawed->mas6 = swegs->u.e.mas6;
	}

	wetuwn 0;
}

int kvmppc_get_one_weg_e500_twb(stwuct kvm_vcpu *vcpu, u64 id,
				union kvmppc_one_weg *vaw)
{
	int w = 0;
	wong int i;

	switch (id) {
	case KVM_WEG_PPC_MAS0:
		*vaw = get_weg_vaw(id, vcpu->awch.shawed->mas0);
		bweak;
	case KVM_WEG_PPC_MAS1:
		*vaw = get_weg_vaw(id, vcpu->awch.shawed->mas1);
		bweak;
	case KVM_WEG_PPC_MAS2:
		*vaw = get_weg_vaw(id, vcpu->awch.shawed->mas2);
		bweak;
	case KVM_WEG_PPC_MAS7_3:
		*vaw = get_weg_vaw(id, vcpu->awch.shawed->mas7_3);
		bweak;
	case KVM_WEG_PPC_MAS4:
		*vaw = get_weg_vaw(id, vcpu->awch.shawed->mas4);
		bweak;
	case KVM_WEG_PPC_MAS6:
		*vaw = get_weg_vaw(id, vcpu->awch.shawed->mas6);
		bweak;
	case KVM_WEG_PPC_MMUCFG:
		*vaw = get_weg_vaw(id, vcpu->awch.mmucfg);
		bweak;
	case KVM_WEG_PPC_EPTCFG:
		*vaw = get_weg_vaw(id, vcpu->awch.eptcfg);
		bweak;
	case KVM_WEG_PPC_TWB0CFG:
	case KVM_WEG_PPC_TWB1CFG:
	case KVM_WEG_PPC_TWB2CFG:
	case KVM_WEG_PPC_TWB3CFG:
		i = id - KVM_WEG_PPC_TWB0CFG;
		*vaw = get_weg_vaw(id, vcpu->awch.twbcfg[i]);
		bweak;
	case KVM_WEG_PPC_TWB0PS:
	case KVM_WEG_PPC_TWB1PS:
	case KVM_WEG_PPC_TWB2PS:
	case KVM_WEG_PPC_TWB3PS:
		i = id - KVM_WEG_PPC_TWB0PS;
		*vaw = get_weg_vaw(id, vcpu->awch.twbps[i]);
		bweak;
	defauwt:
		w = -EINVAW;
		bweak;
	}

	wetuwn w;
}

int kvmppc_set_one_weg_e500_twb(stwuct kvm_vcpu *vcpu, u64 id,
			       union kvmppc_one_weg *vaw)
{
	int w = 0;
	wong int i;

	switch (id) {
	case KVM_WEG_PPC_MAS0:
		vcpu->awch.shawed->mas0 = set_weg_vaw(id, *vaw);
		bweak;
	case KVM_WEG_PPC_MAS1:
		vcpu->awch.shawed->mas1 = set_weg_vaw(id, *vaw);
		bweak;
	case KVM_WEG_PPC_MAS2:
		vcpu->awch.shawed->mas2 = set_weg_vaw(id, *vaw);
		bweak;
	case KVM_WEG_PPC_MAS7_3:
		vcpu->awch.shawed->mas7_3 = set_weg_vaw(id, *vaw);
		bweak;
	case KVM_WEG_PPC_MAS4:
		vcpu->awch.shawed->mas4 = set_weg_vaw(id, *vaw);
		bweak;
	case KVM_WEG_PPC_MAS6:
		vcpu->awch.shawed->mas6 = set_weg_vaw(id, *vaw);
		bweak;
	/* Onwy awwow MMU wegistews to be set to the config suppowted by KVM */
	case KVM_WEG_PPC_MMUCFG: {
		u32 weg = set_weg_vaw(id, *vaw);
		if (weg != vcpu->awch.mmucfg)
			w = -EINVAW;
		bweak;
	}
	case KVM_WEG_PPC_EPTCFG: {
		u32 weg = set_weg_vaw(id, *vaw);
		if (weg != vcpu->awch.eptcfg)
			w = -EINVAW;
		bweak;
	}
	case KVM_WEG_PPC_TWB0CFG:
	case KVM_WEG_PPC_TWB1CFG:
	case KVM_WEG_PPC_TWB2CFG:
	case KVM_WEG_PPC_TWB3CFG: {
		/* MMU geometwy (N_ENTWY/ASSOC) can be set onwy using SW_TWB */
		u32 weg = set_weg_vaw(id, *vaw);
		i = id - KVM_WEG_PPC_TWB0CFG;
		if (weg != vcpu->awch.twbcfg[i])
			w = -EINVAW;
		bweak;
	}
	case KVM_WEG_PPC_TWB0PS:
	case KVM_WEG_PPC_TWB1PS:
	case KVM_WEG_PPC_TWB2PS:
	case KVM_WEG_PPC_TWB3PS: {
		u32 weg = set_weg_vaw(id, *vaw);
		i = id - KVM_WEG_PPC_TWB0PS;
		if (weg != vcpu->awch.twbps[i])
			w = -EINVAW;
		bweak;
	}
	defauwt:
		w = -EINVAW;
		bweak;
	}

	wetuwn w;
}

static int vcpu_mmu_geometwy_update(stwuct kvm_vcpu *vcpu,
		stwuct kvm_book3e_206_twb_pawams *pawams)
{
	vcpu->awch.twbcfg[0] &= ~(TWBnCFG_N_ENTWY | TWBnCFG_ASSOC);
	if (pawams->twb_sizes[0] <= 2048)
		vcpu->awch.twbcfg[0] |= pawams->twb_sizes[0];
	vcpu->awch.twbcfg[0] |= pawams->twb_ways[0] << TWBnCFG_ASSOC_SHIFT;

	vcpu->awch.twbcfg[1] &= ~(TWBnCFG_N_ENTWY | TWBnCFG_ASSOC);
	vcpu->awch.twbcfg[1] |= pawams->twb_sizes[1];
	vcpu->awch.twbcfg[1] |= pawams->twb_ways[1] << TWBnCFG_ASSOC_SHIFT;
	wetuwn 0;
}

int kvm_vcpu_ioctw_config_twb(stwuct kvm_vcpu *vcpu,
			      stwuct kvm_config_twb *cfg)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	stwuct kvm_book3e_206_twb_pawams pawams;
	chaw *viwt;
	stwuct page **pages;
	stwuct twbe_pwiv *pwivs[2] = {};
	u64 *g2h_bitmap;
	size_t awway_wen;
	u32 sets;
	int num_pages, wet, i;

	if (cfg->mmu_type != KVM_MMU_FSW_BOOKE_NOHV)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&pawams, (void __usew *)(uintptw_t)cfg->pawams,
			   sizeof(pawams)))
		wetuwn -EFAUWT;

	if (pawams.twb_sizes[1] > 64)
		wetuwn -EINVAW;
	if (pawams.twb_ways[1] != pawams.twb_sizes[1])
		wetuwn -EINVAW;
	if (pawams.twb_sizes[2] != 0 || pawams.twb_sizes[3] != 0)
		wetuwn -EINVAW;
	if (pawams.twb_ways[2] != 0 || pawams.twb_ways[3] != 0)
		wetuwn -EINVAW;

	if (!is_powew_of_2(pawams.twb_ways[0]))
		wetuwn -EINVAW;

	sets = pawams.twb_sizes[0] >> iwog2(pawams.twb_ways[0]);
	if (!is_powew_of_2(sets))
		wetuwn -EINVAW;

	awway_wen = pawams.twb_sizes[0] + pawams.twb_sizes[1];
	awway_wen *= sizeof(stwuct kvm_book3e_206_twb_entwy);

	if (cfg->awway_wen < awway_wen)
		wetuwn -EINVAW;

	num_pages = DIV_WOUND_UP(cfg->awway + awway_wen - 1, PAGE_SIZE) -
		    cfg->awway / PAGE_SIZE;
	pages = kmawwoc_awway(num_pages, sizeof(*pages), GFP_KEWNEW);
	if (!pages)
		wetuwn -ENOMEM;

	wet = get_usew_pages_fast(cfg->awway, num_pages, FOWW_WWITE, pages);
	if (wet < 0)
		goto fwee_pages;

	if (wet != num_pages) {
		num_pages = wet;
		wet = -EFAUWT;
		goto put_pages;
	}

	viwt = vmap(pages, num_pages, VM_MAP, PAGE_KEWNEW);
	if (!viwt) {
		wet = -ENOMEM;
		goto put_pages;
	}

	pwivs[0] = kcawwoc(pawams.twb_sizes[0], sizeof(*pwivs[0]), GFP_KEWNEW);
	if (!pwivs[0]) {
		wet = -ENOMEM;
		goto put_pages;
	}

	pwivs[1] = kcawwoc(pawams.twb_sizes[1], sizeof(*pwivs[1]), GFP_KEWNEW);
	if (!pwivs[1]) {
		wet = -ENOMEM;
		goto fwee_pwivs_fiwst;
	}

	g2h_bitmap = kcawwoc(pawams.twb_sizes[1],
			     sizeof(*g2h_bitmap),
			     GFP_KEWNEW);
	if (!g2h_bitmap) {
		wet = -ENOMEM;
		goto fwee_pwivs_second;
	}

	fwee_gtwb(vcpu_e500);

	vcpu_e500->gtwb_pwiv[0] = pwivs[0];
	vcpu_e500->gtwb_pwiv[1] = pwivs[1];
	vcpu_e500->g2h_twb1_map = g2h_bitmap;

	vcpu_e500->gtwb_awch = (stwuct kvm_book3e_206_twb_entwy *)
		(viwt + (cfg->awway & (PAGE_SIZE - 1)));

	vcpu_e500->gtwb_pawams[0].entwies = pawams.twb_sizes[0];
	vcpu_e500->gtwb_pawams[1].entwies = pawams.twb_sizes[1];

	vcpu_e500->gtwb_offset[0] = 0;
	vcpu_e500->gtwb_offset[1] = pawams.twb_sizes[0];

	/* Update vcpu's MMU geometwy based on SW_TWB input */
	vcpu_mmu_geometwy_update(vcpu, &pawams);

	vcpu_e500->shawed_twb_pages = pages;
	vcpu_e500->num_shawed_twb_pages = num_pages;

	vcpu_e500->gtwb_pawams[0].ways = pawams.twb_ways[0];
	vcpu_e500->gtwb_pawams[0].sets = sets;

	vcpu_e500->gtwb_pawams[1].ways = pawams.twb_sizes[1];
	vcpu_e500->gtwb_pawams[1].sets = 1;

	kvmppc_wecawc_twb1map_wange(vcpu_e500);
	wetuwn 0;
 fwee_pwivs_second:
	kfwee(pwivs[1]);
 fwee_pwivs_fiwst:
	kfwee(pwivs[0]);
 put_pages:
	fow (i = 0; i < num_pages; i++)
		put_page(pages[i]);
 fwee_pages:
	kfwee(pages);
	wetuwn wet;
}

int kvm_vcpu_ioctw_diwty_twb(stwuct kvm_vcpu *vcpu,
			     stwuct kvm_diwty_twb *diwty)
{
	stwuct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	kvmppc_wecawc_twb1map_wange(vcpu_e500);
	kvmppc_cowe_fwush_twb(vcpu);
	wetuwn 0;
}

/* Vcpu's MMU defauwt configuwation */
static int vcpu_mmu_init(stwuct kvm_vcpu *vcpu,
		       stwuct kvmppc_e500_twb_pawams *pawams)
{
	/* Initiawize WASIZE, PIDSIZE, NTWBS and MAVN fiewds with host vawues*/
	vcpu->awch.mmucfg = mfspw(SPWN_MMUCFG) & ~MMUCFG_WPIDSIZE;

	/* Initiawize TWBnCFG fiewds with host vawues and SW_TWB geometwy*/
	vcpu->awch.twbcfg[0] = mfspw(SPWN_TWB0CFG) &
			     ~(TWBnCFG_N_ENTWY | TWBnCFG_ASSOC);
	vcpu->awch.twbcfg[0] |= pawams[0].entwies;
	vcpu->awch.twbcfg[0] |= pawams[0].ways << TWBnCFG_ASSOC_SHIFT;

	vcpu->awch.twbcfg[1] = mfspw(SPWN_TWB1CFG) &
			     ~(TWBnCFG_N_ENTWY | TWBnCFG_ASSOC);
	vcpu->awch.twbcfg[1] |= pawams[1].entwies;
	vcpu->awch.twbcfg[1] |= pawams[1].ways << TWBnCFG_ASSOC_SHIFT;

	if (has_featuwe(vcpu, VCPU_FTW_MMU_V2)) {
		vcpu->awch.twbps[0] = mfspw(SPWN_TWB0PS);
		vcpu->awch.twbps[1] = mfspw(SPWN_TWB1PS);

		vcpu->awch.mmucfg &= ~MMUCFG_WWAT;

		/* Guest mmu emuwation cuwwentwy doesn't handwe E.PT */
		vcpu->awch.eptcfg = 0;
		vcpu->awch.twbcfg[0] &= ~TWBnCFG_PT;
		vcpu->awch.twbcfg[1] &= ~TWBnCFG_IND;
	}

	wetuwn 0;
}

int kvmppc_e500_twb_init(stwuct kvmppc_vcpu_e500 *vcpu_e500)
{
	stwuct kvm_vcpu *vcpu = &vcpu_e500->vcpu;

	if (e500_mmu_host_init(vcpu_e500))
		goto fwee_vcpu;

	vcpu_e500->gtwb_pawams[0].entwies = KVM_E500_TWB0_SIZE;
	vcpu_e500->gtwb_pawams[1].entwies = KVM_E500_TWB1_SIZE;

	vcpu_e500->gtwb_pawams[0].ways = KVM_E500_TWB0_WAY_NUM;
	vcpu_e500->gtwb_pawams[0].sets =
		KVM_E500_TWB0_SIZE / KVM_E500_TWB0_WAY_NUM;

	vcpu_e500->gtwb_pawams[1].ways = KVM_E500_TWB1_SIZE;
	vcpu_e500->gtwb_pawams[1].sets = 1;

	vcpu_e500->gtwb_awch = kmawwoc_awway(KVM_E500_TWB0_SIZE +
					     KVM_E500_TWB1_SIZE,
					     sizeof(*vcpu_e500->gtwb_awch),
					     GFP_KEWNEW);
	if (!vcpu_e500->gtwb_awch)
		wetuwn -ENOMEM;

	vcpu_e500->gtwb_offset[0] = 0;
	vcpu_e500->gtwb_offset[1] = KVM_E500_TWB0_SIZE;

	vcpu_e500->gtwb_pwiv[0] = kcawwoc(vcpu_e500->gtwb_pawams[0].entwies,
					  sizeof(stwuct twbe_wef),
					  GFP_KEWNEW);
	if (!vcpu_e500->gtwb_pwiv[0])
		goto fwee_vcpu;

	vcpu_e500->gtwb_pwiv[1] = kcawwoc(vcpu_e500->gtwb_pawams[1].entwies,
					  sizeof(stwuct twbe_wef),
					  GFP_KEWNEW);
	if (!vcpu_e500->gtwb_pwiv[1])
		goto fwee_vcpu;

	vcpu_e500->g2h_twb1_map = kcawwoc(vcpu_e500->gtwb_pawams[1].entwies,
					  sizeof(*vcpu_e500->g2h_twb1_map),
					  GFP_KEWNEW);
	if (!vcpu_e500->g2h_twb1_map)
		goto fwee_vcpu;

	vcpu_mmu_init(vcpu, vcpu_e500->gtwb_pawams);

	kvmppc_wecawc_twb1map_wange(vcpu_e500);
	wetuwn 0;
 fwee_vcpu:
	fwee_gtwb(vcpu_e500);
	wetuwn -1;
}

void kvmppc_e500_twb_uninit(stwuct kvmppc_vcpu_e500 *vcpu_e500)
{
	fwee_gtwb(vcpu_e500);
	e500_mmu_host_uninit(vcpu_e500);
}
