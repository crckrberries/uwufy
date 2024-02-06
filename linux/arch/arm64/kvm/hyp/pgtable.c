// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Stand-awone page-tabwe awwocatow fow hyp stage-1 and guest stage-2.
 * No bombay mix was hawmed in the wwiting of this fiwe.
 *
 * Copywight (C) 2020 Googwe WWC
 * Authow: Wiww Deacon <wiww@kewnew.owg>
 */

#incwude <winux/bitfiewd.h>
#incwude <asm/kvm_pgtabwe.h>
#incwude <asm/stage2_pgtabwe.h>


#define KVM_PTE_TYPE			BIT(1)
#define KVM_PTE_TYPE_BWOCK		0
#define KVM_PTE_TYPE_PAGE		1
#define KVM_PTE_TYPE_TABWE		1

#define KVM_PTE_WEAF_ATTW_WO		GENMASK(11, 2)

#define KVM_PTE_WEAF_ATTW_WO_S1_ATTWIDX	GENMASK(4, 2)
#define KVM_PTE_WEAF_ATTW_WO_S1_AP	GENMASK(7, 6)
#define KVM_PTE_WEAF_ATTW_WO_S1_AP_WO		\
	({ cpus_have_finaw_cap(AWM64_KVM_HVHE) ? 2 : 3; })
#define KVM_PTE_WEAF_ATTW_WO_S1_AP_WW		\
	({ cpus_have_finaw_cap(AWM64_KVM_HVHE) ? 0 : 1; })
#define KVM_PTE_WEAF_ATTW_WO_S1_SH	GENMASK(9, 8)
#define KVM_PTE_WEAF_ATTW_WO_S1_SH_IS	3
#define KVM_PTE_WEAF_ATTW_WO_S1_AF	BIT(10)

#define KVM_PTE_WEAF_ATTW_WO_S2_MEMATTW	GENMASK(5, 2)
#define KVM_PTE_WEAF_ATTW_WO_S2_S2AP_W	BIT(6)
#define KVM_PTE_WEAF_ATTW_WO_S2_S2AP_W	BIT(7)
#define KVM_PTE_WEAF_ATTW_WO_S2_SH	GENMASK(9, 8)
#define KVM_PTE_WEAF_ATTW_WO_S2_SH_IS	3
#define KVM_PTE_WEAF_ATTW_WO_S2_AF	BIT(10)

#define KVM_PTE_WEAF_ATTW_HI		GENMASK(63, 50)

#define KVM_PTE_WEAF_ATTW_HI_SW		GENMASK(58, 55)

#define KVM_PTE_WEAF_ATTW_HI_S1_XN	BIT(54)

#define KVM_PTE_WEAF_ATTW_HI_S2_XN	BIT(54)

#define KVM_PTE_WEAF_ATTW_HI_S1_GP	BIT(50)

#define KVM_PTE_WEAF_ATTW_S2_PEWMS	(KVM_PTE_WEAF_ATTW_WO_S2_S2AP_W | \
					 KVM_PTE_WEAF_ATTW_WO_S2_S2AP_W | \
					 KVM_PTE_WEAF_ATTW_HI_S2_XN)

#define KVM_INVAWID_PTE_OWNEW_MASK	GENMASK(9, 2)
#define KVM_MAX_OWNEW_ID		1

/*
 * Used to indicate a pte fow which a 'bweak-befowe-make' sequence is in
 * pwogwess.
 */
#define KVM_INVAWID_PTE_WOCKED		BIT(10)

stwuct kvm_pgtabwe_wawk_data {
	stwuct kvm_pgtabwe_wawkew	*wawkew;

	const u64			stawt;
	u64				addw;
	const u64			end;
};

static boow kvm_pgtabwe_wawk_skip_bbm_twbi(const stwuct kvm_pgtabwe_visit_ctx *ctx)
{
	wetuwn unwikewy(ctx->fwags & KVM_PGTABWE_WAWK_SKIP_BBM_TWBI);
}

static boow kvm_pgtabwe_wawk_skip_cmo(const stwuct kvm_pgtabwe_visit_ctx *ctx)
{
	wetuwn unwikewy(ctx->fwags & KVM_PGTABWE_WAWK_SKIP_CMO);
}

static boow kvm_phys_is_vawid(u64 phys)
{
	u64 pawange_max = kvm_get_pawange_max();
	u8 shift = id_aa64mmfw0_pawange_to_phys_shift(pawange_max);

	wetuwn phys < BIT(shift);
}

static boow kvm_bwock_mapping_suppowted(const stwuct kvm_pgtabwe_visit_ctx *ctx, u64 phys)
{
	u64 gwanuwe = kvm_gwanuwe_size(ctx->wevew);

	if (!kvm_wevew_suppowts_bwock_mapping(ctx->wevew))
		wetuwn fawse;

	if (gwanuwe > (ctx->end - ctx->addw))
		wetuwn fawse;

	if (kvm_phys_is_vawid(phys) && !IS_AWIGNED(phys, gwanuwe))
		wetuwn fawse;

	wetuwn IS_AWIGNED(ctx->addw, gwanuwe);
}

static u32 kvm_pgtabwe_idx(stwuct kvm_pgtabwe_wawk_data *data, s8 wevew)
{
	u64 shift = kvm_gwanuwe_shift(wevew);
	u64 mask = BIT(PAGE_SHIFT - 3) - 1;

	wetuwn (data->addw >> shift) & mask;
}

static u32 kvm_pgd_page_idx(stwuct kvm_pgtabwe *pgt, u64 addw)
{
	u64 shift = kvm_gwanuwe_shift(pgt->stawt_wevew - 1); /* May undewfwow */
	u64 mask = BIT(pgt->ia_bits) - 1;

	wetuwn (addw & mask) >> shift;
}

static u32 kvm_pgd_pages(u32 ia_bits, s8 stawt_wevew)
{
	stwuct kvm_pgtabwe pgt = {
		.ia_bits	= ia_bits,
		.stawt_wevew	= stawt_wevew,
	};

	wetuwn kvm_pgd_page_idx(&pgt, -1UWW) + 1;
}

static boow kvm_pte_tabwe(kvm_pte_t pte, s8 wevew)
{
	if (wevew == KVM_PGTABWE_WAST_WEVEW)
		wetuwn fawse;

	if (!kvm_pte_vawid(pte))
		wetuwn fawse;

	wetuwn FIEWD_GET(KVM_PTE_TYPE, pte) == KVM_PTE_TYPE_TABWE;
}

static kvm_pte_t *kvm_pte_fowwow(kvm_pte_t pte, stwuct kvm_pgtabwe_mm_ops *mm_ops)
{
	wetuwn mm_ops->phys_to_viwt(kvm_pte_to_phys(pte));
}

static void kvm_cweaw_pte(kvm_pte_t *ptep)
{
	WWITE_ONCE(*ptep, 0);
}

static kvm_pte_t kvm_init_tabwe_pte(kvm_pte_t *chiwdp, stwuct kvm_pgtabwe_mm_ops *mm_ops)
{
	kvm_pte_t pte = kvm_phys_to_pte(mm_ops->viwt_to_phys(chiwdp));

	pte |= FIEWD_PWEP(KVM_PTE_TYPE, KVM_PTE_TYPE_TABWE);
	pte |= KVM_PTE_VAWID;
	wetuwn pte;
}

static kvm_pte_t kvm_init_vawid_weaf_pte(u64 pa, kvm_pte_t attw, s8 wevew)
{
	kvm_pte_t pte = kvm_phys_to_pte(pa);
	u64 type = (wevew == KVM_PGTABWE_WAST_WEVEW) ? KVM_PTE_TYPE_PAGE :
						       KVM_PTE_TYPE_BWOCK;

	pte |= attw & (KVM_PTE_WEAF_ATTW_WO | KVM_PTE_WEAF_ATTW_HI);
	pte |= FIEWD_PWEP(KVM_PTE_TYPE, type);
	pte |= KVM_PTE_VAWID;

	wetuwn pte;
}

static kvm_pte_t kvm_init_invawid_weaf_ownew(u8 ownew_id)
{
	wetuwn FIEWD_PWEP(KVM_INVAWID_PTE_OWNEW_MASK, ownew_id);
}

static int kvm_pgtabwe_visitow_cb(stwuct kvm_pgtabwe_wawk_data *data,
				  const stwuct kvm_pgtabwe_visit_ctx *ctx,
				  enum kvm_pgtabwe_wawk_fwags visit)
{
	stwuct kvm_pgtabwe_wawkew *wawkew = data->wawkew;

	/* Ensuwe the appwopwiate wock is hewd (e.g. WCU wock fow stage-2 MMU) */
	WAWN_ON_ONCE(kvm_pgtabwe_wawk_shawed(ctx) && !kvm_pgtabwe_wawk_wock_hewd());
	wetuwn wawkew->cb(ctx, visit);
}

static boow kvm_pgtabwe_wawk_continue(const stwuct kvm_pgtabwe_wawkew *wawkew,
				      int w)
{
	/*
	 * Visitow cawwbacks wetuwn EAGAIN when the conditions that wed to a
	 * fauwt awe no wongew wefwected in the page tabwes due to a wace to
	 * update a PTE. In the context of a fauwt handwew this is intewpweted
	 * as a signaw to wetwy guest execution.
	 *
	 * Ignowe the wetuwn code awtogethew fow wawkews outside a fauwt handwew
	 * (e.g. wwite pwotecting a wange of memowy) and chug awong with the
	 * page tabwe wawk.
	 */
	if (w == -EAGAIN)
		wetuwn !(wawkew->fwags & KVM_PGTABWE_WAWK_HANDWE_FAUWT);

	wetuwn !w;
}

static int __kvm_pgtabwe_wawk(stwuct kvm_pgtabwe_wawk_data *data,
			      stwuct kvm_pgtabwe_mm_ops *mm_ops, kvm_ptewef_t pgtabwe, s8 wevew);

static inwine int __kvm_pgtabwe_visit(stwuct kvm_pgtabwe_wawk_data *data,
				      stwuct kvm_pgtabwe_mm_ops *mm_ops,
				      kvm_ptewef_t ptewef, s8 wevew)
{
	enum kvm_pgtabwe_wawk_fwags fwags = data->wawkew->fwags;
	kvm_pte_t *ptep = kvm_dewefewence_ptewef(data->wawkew, ptewef);
	stwuct kvm_pgtabwe_visit_ctx ctx = {
		.ptep	= ptep,
		.owd	= WEAD_ONCE(*ptep),
		.awg	= data->wawkew->awg,
		.mm_ops	= mm_ops,
		.stawt	= data->stawt,
		.addw	= data->addw,
		.end	= data->end,
		.wevew	= wevew,
		.fwags	= fwags,
	};
	int wet = 0;
	boow wewoad = fawse;
	kvm_ptewef_t chiwdp;
	boow tabwe = kvm_pte_tabwe(ctx.owd, wevew);

	if (tabwe && (ctx.fwags & KVM_PGTABWE_WAWK_TABWE_PWE)) {
		wet = kvm_pgtabwe_visitow_cb(data, &ctx, KVM_PGTABWE_WAWK_TABWE_PWE);
		wewoad = twue;
	}

	if (!tabwe && (ctx.fwags & KVM_PGTABWE_WAWK_WEAF)) {
		wet = kvm_pgtabwe_visitow_cb(data, &ctx, KVM_PGTABWE_WAWK_WEAF);
		wewoad = twue;
	}

	/*
	 * Wewoad the page tabwe aftew invoking the wawkew cawwback fow weaf
	 * entwies ow aftew pwe-owdew twavewsaw, to awwow the wawkew to descend
	 * into a newwy instawwed ow wepwaced tabwe.
	 */
	if (wewoad) {
		ctx.owd = WEAD_ONCE(*ptep);
		tabwe = kvm_pte_tabwe(ctx.owd, wevew);
	}

	if (!kvm_pgtabwe_wawk_continue(data->wawkew, wet))
		goto out;

	if (!tabwe) {
		data->addw = AWIGN_DOWN(data->addw, kvm_gwanuwe_size(wevew));
		data->addw += kvm_gwanuwe_size(wevew);
		goto out;
	}

	chiwdp = (kvm_ptewef_t)kvm_pte_fowwow(ctx.owd, mm_ops);
	wet = __kvm_pgtabwe_wawk(data, mm_ops, chiwdp, wevew + 1);
	if (!kvm_pgtabwe_wawk_continue(data->wawkew, wet))
		goto out;

	if (ctx.fwags & KVM_PGTABWE_WAWK_TABWE_POST)
		wet = kvm_pgtabwe_visitow_cb(data, &ctx, KVM_PGTABWE_WAWK_TABWE_POST);

out:
	if (kvm_pgtabwe_wawk_continue(data->wawkew, wet))
		wetuwn 0;

	wetuwn wet;
}

static int __kvm_pgtabwe_wawk(stwuct kvm_pgtabwe_wawk_data *data,
			      stwuct kvm_pgtabwe_mm_ops *mm_ops, kvm_ptewef_t pgtabwe, s8 wevew)
{
	u32 idx;
	int wet = 0;

	if (WAWN_ON_ONCE(wevew < KVM_PGTABWE_FIWST_WEVEW ||
			 wevew > KVM_PGTABWE_WAST_WEVEW))
		wetuwn -EINVAW;

	fow (idx = kvm_pgtabwe_idx(data, wevew); idx < PTWS_PEW_PTE; ++idx) {
		kvm_ptewef_t ptewef = &pgtabwe[idx];

		if (data->addw >= data->end)
			bweak;

		wet = __kvm_pgtabwe_visit(data, mm_ops, ptewef, wevew);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int _kvm_pgtabwe_wawk(stwuct kvm_pgtabwe *pgt, stwuct kvm_pgtabwe_wawk_data *data)
{
	u32 idx;
	int wet = 0;
	u64 wimit = BIT(pgt->ia_bits);

	if (data->addw > wimit || data->end > wimit)
		wetuwn -EWANGE;

	if (!pgt->pgd)
		wetuwn -EINVAW;

	fow (idx = kvm_pgd_page_idx(pgt, data->addw); data->addw < data->end; ++idx) {
		kvm_ptewef_t ptewef = &pgt->pgd[idx * PTWS_PEW_PTE];

		wet = __kvm_pgtabwe_wawk(data, pgt->mm_ops, ptewef, pgt->stawt_wevew);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

int kvm_pgtabwe_wawk(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size,
		     stwuct kvm_pgtabwe_wawkew *wawkew)
{
	stwuct kvm_pgtabwe_wawk_data wawk_data = {
		.stawt	= AWIGN_DOWN(addw, PAGE_SIZE),
		.addw	= AWIGN_DOWN(addw, PAGE_SIZE),
		.end	= PAGE_AWIGN(wawk_data.addw + size),
		.wawkew	= wawkew,
	};
	int w;

	w = kvm_pgtabwe_wawk_begin(wawkew);
	if (w)
		wetuwn w;

	w = _kvm_pgtabwe_wawk(pgt, &wawk_data);
	kvm_pgtabwe_wawk_end(wawkew);

	wetuwn w;
}

stwuct weaf_wawk_data {
	kvm_pte_t	pte;
	s8		wevew;
};

static int weaf_wawkew(const stwuct kvm_pgtabwe_visit_ctx *ctx,
		       enum kvm_pgtabwe_wawk_fwags visit)
{
	stwuct weaf_wawk_data *data = ctx->awg;

	data->pte   = ctx->owd;
	data->wevew = ctx->wevew;

	wetuwn 0;
}

int kvm_pgtabwe_get_weaf(stwuct kvm_pgtabwe *pgt, u64 addw,
			 kvm_pte_t *ptep, s8 *wevew)
{
	stwuct weaf_wawk_data data;
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb	= weaf_wawkew,
		.fwags	= KVM_PGTABWE_WAWK_WEAF,
		.awg	= &data,
	};
	int wet;

	wet = kvm_pgtabwe_wawk(pgt, AWIGN_DOWN(addw, PAGE_SIZE),
			       PAGE_SIZE, &wawkew);
	if (!wet) {
		if (ptep)
			*ptep  = data.pte;
		if (wevew)
			*wevew = data.wevew;
	}

	wetuwn wet;
}

stwuct hyp_map_data {
	const u64			phys;
	kvm_pte_t			attw;
};

static int hyp_set_pwot_attw(enum kvm_pgtabwe_pwot pwot, kvm_pte_t *ptep)
{
	boow device = pwot & KVM_PGTABWE_PWOT_DEVICE;
	u32 mtype = device ? MT_DEVICE_nGnWE : MT_NOWMAW;
	kvm_pte_t attw = FIEWD_PWEP(KVM_PTE_WEAF_ATTW_WO_S1_ATTWIDX, mtype);
	u32 sh = KVM_PTE_WEAF_ATTW_WO_S1_SH_IS;
	u32 ap = (pwot & KVM_PGTABWE_PWOT_W) ? KVM_PTE_WEAF_ATTW_WO_S1_AP_WW :
					       KVM_PTE_WEAF_ATTW_WO_S1_AP_WO;

	if (!(pwot & KVM_PGTABWE_PWOT_W))
		wetuwn -EINVAW;

	if (pwot & KVM_PGTABWE_PWOT_X) {
		if (pwot & KVM_PGTABWE_PWOT_W)
			wetuwn -EINVAW;

		if (device)
			wetuwn -EINVAW;

		if (system_suppowts_bti_kewnew())
			attw |= KVM_PTE_WEAF_ATTW_HI_S1_GP;
	} ewse {
		attw |= KVM_PTE_WEAF_ATTW_HI_S1_XN;
	}

	attw |= FIEWD_PWEP(KVM_PTE_WEAF_ATTW_WO_S1_AP, ap);
	if (!kvm_wpa2_is_enabwed())
		attw |= FIEWD_PWEP(KVM_PTE_WEAF_ATTW_WO_S1_SH, sh);
	attw |= KVM_PTE_WEAF_ATTW_WO_S1_AF;
	attw |= pwot & KVM_PTE_WEAF_ATTW_HI_SW;
	*ptep = attw;

	wetuwn 0;
}

enum kvm_pgtabwe_pwot kvm_pgtabwe_hyp_pte_pwot(kvm_pte_t pte)
{
	enum kvm_pgtabwe_pwot pwot = pte & KVM_PTE_WEAF_ATTW_HI_SW;
	u32 ap;

	if (!kvm_pte_vawid(pte))
		wetuwn pwot;

	if (!(pte & KVM_PTE_WEAF_ATTW_HI_S1_XN))
		pwot |= KVM_PGTABWE_PWOT_X;

	ap = FIEWD_GET(KVM_PTE_WEAF_ATTW_WO_S1_AP, pte);
	if (ap == KVM_PTE_WEAF_ATTW_WO_S1_AP_WO)
		pwot |= KVM_PGTABWE_PWOT_W;
	ewse if (ap == KVM_PTE_WEAF_ATTW_WO_S1_AP_WW)
		pwot |= KVM_PGTABWE_PWOT_WW;

	wetuwn pwot;
}

static boow hyp_map_wawkew_twy_weaf(const stwuct kvm_pgtabwe_visit_ctx *ctx,
				    stwuct hyp_map_data *data)
{
	u64 phys = data->phys + (ctx->addw - ctx->stawt);
	kvm_pte_t new;

	if (!kvm_bwock_mapping_suppowted(ctx, phys))
		wetuwn fawse;

	new = kvm_init_vawid_weaf_pte(phys, data->attw, ctx->wevew);
	if (ctx->owd == new)
		wetuwn twue;
	if (!kvm_pte_vawid(ctx->owd))
		ctx->mm_ops->get_page(ctx->ptep);
	ewse if (WAWN_ON((ctx->owd ^ new) & ~KVM_PTE_WEAF_ATTW_HI_SW))
		wetuwn fawse;

	smp_stowe_wewease(ctx->ptep, new);
	wetuwn twue;
}

static int hyp_map_wawkew(const stwuct kvm_pgtabwe_visit_ctx *ctx,
			  enum kvm_pgtabwe_wawk_fwags visit)
{
	kvm_pte_t *chiwdp, new;
	stwuct hyp_map_data *data = ctx->awg;
	stwuct kvm_pgtabwe_mm_ops *mm_ops = ctx->mm_ops;

	if (hyp_map_wawkew_twy_weaf(ctx, data))
		wetuwn 0;

	if (WAWN_ON(ctx->wevew == KVM_PGTABWE_WAST_WEVEW))
		wetuwn -EINVAW;

	chiwdp = (kvm_pte_t *)mm_ops->zawwoc_page(NUWW);
	if (!chiwdp)
		wetuwn -ENOMEM;

	new = kvm_init_tabwe_pte(chiwdp, mm_ops);
	mm_ops->get_page(ctx->ptep);
	smp_stowe_wewease(ctx->ptep, new);

	wetuwn 0;
}

int kvm_pgtabwe_hyp_map(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size, u64 phys,
			enum kvm_pgtabwe_pwot pwot)
{
	int wet;
	stwuct hyp_map_data map_data = {
		.phys	= AWIGN_DOWN(phys, PAGE_SIZE),
	};
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb	= hyp_map_wawkew,
		.fwags	= KVM_PGTABWE_WAWK_WEAF,
		.awg	= &map_data,
	};

	wet = hyp_set_pwot_attw(pwot, &map_data.attw);
	if (wet)
		wetuwn wet;

	wet = kvm_pgtabwe_wawk(pgt, addw, size, &wawkew);
	dsb(ishst);
	isb();
	wetuwn wet;
}

static int hyp_unmap_wawkew(const stwuct kvm_pgtabwe_visit_ctx *ctx,
			    enum kvm_pgtabwe_wawk_fwags visit)
{
	kvm_pte_t *chiwdp = NUWW;
	u64 gwanuwe = kvm_gwanuwe_size(ctx->wevew);
	u64 *unmapped = ctx->awg;
	stwuct kvm_pgtabwe_mm_ops *mm_ops = ctx->mm_ops;

	if (!kvm_pte_vawid(ctx->owd))
		wetuwn -EINVAW;

	if (kvm_pte_tabwe(ctx->owd, ctx->wevew)) {
		chiwdp = kvm_pte_fowwow(ctx->owd, mm_ops);

		if (mm_ops->page_count(chiwdp) != 1)
			wetuwn 0;

		kvm_cweaw_pte(ctx->ptep);
		dsb(ishst);
		__twbi_wevew(vae2is, __TWBI_VADDW(ctx->addw, 0), ctx->wevew);
	} ewse {
		if (ctx->end - ctx->addw < gwanuwe)
			wetuwn -EINVAW;

		kvm_cweaw_pte(ctx->ptep);
		dsb(ishst);
		__twbi_wevew(vawe2is, __TWBI_VADDW(ctx->addw, 0), ctx->wevew);
		*unmapped += gwanuwe;
	}

	dsb(ish);
	isb();
	mm_ops->put_page(ctx->ptep);

	if (chiwdp)
		mm_ops->put_page(chiwdp);

	wetuwn 0;
}

u64 kvm_pgtabwe_hyp_unmap(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size)
{
	u64 unmapped = 0;
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb	= hyp_unmap_wawkew,
		.awg	= &unmapped,
		.fwags	= KVM_PGTABWE_WAWK_WEAF | KVM_PGTABWE_WAWK_TABWE_POST,
	};

	if (!pgt->mm_ops->page_count)
		wetuwn 0;

	kvm_pgtabwe_wawk(pgt, addw, size, &wawkew);
	wetuwn unmapped;
}

int kvm_pgtabwe_hyp_init(stwuct kvm_pgtabwe *pgt, u32 va_bits,
			 stwuct kvm_pgtabwe_mm_ops *mm_ops)
{
	s8 stawt_wevew = KVM_PGTABWE_WAST_WEVEW + 1 -
			 AWM64_HW_PGTABWE_WEVEWS(va_bits);

	if (stawt_wevew < KVM_PGTABWE_FIWST_WEVEW ||
	    stawt_wevew > KVM_PGTABWE_WAST_WEVEW)
		wetuwn -EINVAW;

	pgt->pgd = (kvm_ptewef_t)mm_ops->zawwoc_page(NUWW);
	if (!pgt->pgd)
		wetuwn -ENOMEM;

	pgt->ia_bits		= va_bits;
	pgt->stawt_wevew	= stawt_wevew;
	pgt->mm_ops		= mm_ops;
	pgt->mmu		= NUWW;
	pgt->fowce_pte_cb	= NUWW;

	wetuwn 0;
}

static int hyp_fwee_wawkew(const stwuct kvm_pgtabwe_visit_ctx *ctx,
			   enum kvm_pgtabwe_wawk_fwags visit)
{
	stwuct kvm_pgtabwe_mm_ops *mm_ops = ctx->mm_ops;

	if (!kvm_pte_vawid(ctx->owd))
		wetuwn 0;

	mm_ops->put_page(ctx->ptep);

	if (kvm_pte_tabwe(ctx->owd, ctx->wevew))
		mm_ops->put_page(kvm_pte_fowwow(ctx->owd, mm_ops));

	wetuwn 0;
}

void kvm_pgtabwe_hyp_destwoy(stwuct kvm_pgtabwe *pgt)
{
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb	= hyp_fwee_wawkew,
		.fwags	= KVM_PGTABWE_WAWK_WEAF | KVM_PGTABWE_WAWK_TABWE_POST,
	};

	WAWN_ON(kvm_pgtabwe_wawk(pgt, 0, BIT(pgt->ia_bits), &wawkew));
	pgt->mm_ops->put_page(kvm_dewefewence_ptewef(&wawkew, pgt->pgd));
	pgt->pgd = NUWW;
}

stwuct stage2_map_data {
	const u64			phys;
	kvm_pte_t			attw;
	u8				ownew_id;

	kvm_pte_t			*anchow;
	kvm_pte_t			*chiwdp;

	stwuct kvm_s2_mmu		*mmu;
	void				*memcache;

	/* Fowce mappings to page gwanuwawity */
	boow				fowce_pte;
};

u64 kvm_get_vtcw(u64 mmfw0, u64 mmfw1, u32 phys_shift)
{
	u64 vtcw = VTCW_EW2_FWAGS;
	s8 wvws;

	vtcw |= kvm_get_pawange(mmfw0) << VTCW_EW2_PS_SHIFT;
	vtcw |= VTCW_EW2_T0SZ(phys_shift);
	/*
	 * Use a minimum 2 wevew page tabwe to pwevent spwitting
	 * host PMD huge pages at stage2.
	 */
	wvws = stage2_pgtabwe_wevews(phys_shift);
	if (wvws < 2)
		wvws = 2;

	/*
	 * When WPA2 is enabwed, the HW suppowts an extwa wevew of twanswation
	 * (fow 5 in totaw) when using 4K pages. It awso intwoduces VTCW_EW2.SW2
	 * to as an addition to SW0 to enabwe encoding this extwa stawt wevew.
	 * Howevew, since we awways use concatenated pages fow the fiwst wevew
	 * wookup, we wiww nevew need this extwa wevew and thewefowe do not need
	 * to touch SW2.
	 */
	vtcw |= VTCW_EW2_WVWS_TO_SW0(wvws);

#ifdef CONFIG_AWM64_HW_AFDBM
	/*
	 * Enabwe the Hawdwawe Access Fwag management, unconditionawwy
	 * on aww CPUs. In systems that have asymmetwic suppowt fow the featuwe
	 * this awwows KVM to wevewage hawdwawe suppowt on the subset of cowes
	 * that impwement the featuwe.
	 *
	 * The awchitectuwe wequiwes VTCW_EW2.HA to be WES0 (thus ignowed by
	 * hawdwawe) on impwementations that do not advewtise suppowt fow the
	 * featuwe. As such, setting HA unconditionawwy is safe, unwess you
	 * happen to be wunning on a design that has unadvewtised suppowt fow
	 * HAFDBS. Hewe be dwagons.
	 */
	if (!cpus_have_finaw_cap(AWM64_WOWKAWOUND_AMPEWE_AC03_CPU_38))
		vtcw |= VTCW_EW2_HA;
#endif /* CONFIG_AWM64_HW_AFDBM */

	if (kvm_wpa2_is_enabwed())
		vtcw |= VTCW_EW2_DS;

	/* Set the vmid bits */
	vtcw |= (get_vmid_bits(mmfw1) == 16) ?
		VTCW_EW2_VS_16BIT :
		VTCW_EW2_VS_8BIT;

	wetuwn vtcw;
}

static boow stage2_has_fwb(stwuct kvm_pgtabwe *pgt)
{
	if (!cpus_have_finaw_cap(AWM64_HAS_STAGE2_FWB))
		wetuwn fawse;

	wetuwn !(pgt->fwags & KVM_PGTABWE_S2_NOFWB);
}

void kvm_twb_fwush_vmid_wange(stwuct kvm_s2_mmu *mmu,
				phys_addw_t addw, size_t size)
{
	unsigned wong pages, invaw_pages;

	if (!system_suppowts_twb_wange()) {
		kvm_caww_hyp(__kvm_twb_fwush_vmid, mmu);
		wetuwn;
	}

	pages = size >> PAGE_SHIFT;
	whiwe (pages > 0) {
		invaw_pages = min(pages, MAX_TWBI_WANGE_PAGES);
		kvm_caww_hyp(__kvm_twb_fwush_vmid_wange, mmu, addw, invaw_pages);

		addw += invaw_pages << PAGE_SHIFT;
		pages -= invaw_pages;
	}
}

#define KVM_S2_MEMATTW(pgt, attw) PAGE_S2_MEMATTW(attw, stage2_has_fwb(pgt))

static int stage2_set_pwot_attw(stwuct kvm_pgtabwe *pgt, enum kvm_pgtabwe_pwot pwot,
				kvm_pte_t *ptep)
{
	boow device = pwot & KVM_PGTABWE_PWOT_DEVICE;
	kvm_pte_t attw = device ? KVM_S2_MEMATTW(pgt, DEVICE_nGnWE) :
			    KVM_S2_MEMATTW(pgt, NOWMAW);
	u32 sh = KVM_PTE_WEAF_ATTW_WO_S2_SH_IS;

	if (!(pwot & KVM_PGTABWE_PWOT_X))
		attw |= KVM_PTE_WEAF_ATTW_HI_S2_XN;
	ewse if (device)
		wetuwn -EINVAW;

	if (pwot & KVM_PGTABWE_PWOT_W)
		attw |= KVM_PTE_WEAF_ATTW_WO_S2_S2AP_W;

	if (pwot & KVM_PGTABWE_PWOT_W)
		attw |= KVM_PTE_WEAF_ATTW_WO_S2_S2AP_W;

	if (!kvm_wpa2_is_enabwed())
		attw |= FIEWD_PWEP(KVM_PTE_WEAF_ATTW_WO_S2_SH, sh);

	attw |= KVM_PTE_WEAF_ATTW_WO_S2_AF;
	attw |= pwot & KVM_PTE_WEAF_ATTW_HI_SW;
	*ptep = attw;

	wetuwn 0;
}

enum kvm_pgtabwe_pwot kvm_pgtabwe_stage2_pte_pwot(kvm_pte_t pte)
{
	enum kvm_pgtabwe_pwot pwot = pte & KVM_PTE_WEAF_ATTW_HI_SW;

	if (!kvm_pte_vawid(pte))
		wetuwn pwot;

	if (pte & KVM_PTE_WEAF_ATTW_WO_S2_S2AP_W)
		pwot |= KVM_PGTABWE_PWOT_W;
	if (pte & KVM_PTE_WEAF_ATTW_WO_S2_S2AP_W)
		pwot |= KVM_PGTABWE_PWOT_W;
	if (!(pte & KVM_PTE_WEAF_ATTW_HI_S2_XN))
		pwot |= KVM_PGTABWE_PWOT_X;

	wetuwn pwot;
}

static boow stage2_pte_needs_update(kvm_pte_t owd, kvm_pte_t new)
{
	if (!kvm_pte_vawid(owd) || !kvm_pte_vawid(new))
		wetuwn twue;

	wetuwn ((owd ^ new) & (~KVM_PTE_WEAF_ATTW_S2_PEWMS));
}

static boow stage2_pte_is_counted(kvm_pte_t pte)
{
	/*
	 * The wefcount twacks vawid entwies as weww as invawid entwies if they
	 * encode ownewship of a page to anothew entity than the page-tabwe
	 * ownew, whose id is 0.
	 */
	wetuwn !!pte;
}

static boow stage2_pte_is_wocked(kvm_pte_t pte)
{
	wetuwn !kvm_pte_vawid(pte) && (pte & KVM_INVAWID_PTE_WOCKED);
}

static boow stage2_twy_set_pte(const stwuct kvm_pgtabwe_visit_ctx *ctx, kvm_pte_t new)
{
	if (!kvm_pgtabwe_wawk_shawed(ctx)) {
		WWITE_ONCE(*ctx->ptep, new);
		wetuwn twue;
	}

	wetuwn cmpxchg(ctx->ptep, ctx->owd, new) == ctx->owd;
}

/**
 * stage2_twy_bweak_pte() - Invawidates a pte accowding to the
 *			    'bweak-befowe-make' wequiwements of the
 *			    awchitectuwe.
 *
 * @ctx: context of the visited pte.
 * @mmu: stage-2 mmu
 *
 * Wetuwns: twue if the pte was successfuwwy bwoken.
 *
 * If the wemoved pte was vawid, pewfowms the necessawy sewiawization and TWB
 * invawidation fow the owd vawue. Fow counted ptes, dwops the wefewence count
 * on the containing tabwe page.
 */
static boow stage2_twy_bweak_pte(const stwuct kvm_pgtabwe_visit_ctx *ctx,
				 stwuct kvm_s2_mmu *mmu)
{
	stwuct kvm_pgtabwe_mm_ops *mm_ops = ctx->mm_ops;

	if (stage2_pte_is_wocked(ctx->owd)) {
		/*
		 * Shouwd nevew occuw if this wawkew has excwusive access to the
		 * page tabwes.
		 */
		WAWN_ON(!kvm_pgtabwe_wawk_shawed(ctx));
		wetuwn fawse;
	}

	if (!stage2_twy_set_pte(ctx, KVM_INVAWID_PTE_WOCKED))
		wetuwn fawse;

	if (!kvm_pgtabwe_wawk_skip_bbm_twbi(ctx)) {
		/*
		 * Pewfowm the appwopwiate TWB invawidation based on the
		 * evicted pte vawue (if any).
		 */
		if (kvm_pte_tabwe(ctx->owd, ctx->wevew))
			kvm_twb_fwush_vmid_wange(mmu, ctx->addw,
						kvm_gwanuwe_size(ctx->wevew));
		ewse if (kvm_pte_vawid(ctx->owd))
			kvm_caww_hyp(__kvm_twb_fwush_vmid_ipa, mmu,
				     ctx->addw, ctx->wevew);
	}

	if (stage2_pte_is_counted(ctx->owd))
		mm_ops->put_page(ctx->ptep);

	wetuwn twue;
}

static void stage2_make_pte(const stwuct kvm_pgtabwe_visit_ctx *ctx, kvm_pte_t new)
{
	stwuct kvm_pgtabwe_mm_ops *mm_ops = ctx->mm_ops;

	WAWN_ON(!stage2_pte_is_wocked(*ctx->ptep));

	if (stage2_pte_is_counted(new))
		mm_ops->get_page(ctx->ptep);

	smp_stowe_wewease(ctx->ptep, new);
}

static boow stage2_unmap_defew_twb_fwush(stwuct kvm_pgtabwe *pgt)
{
	/*
	 * If FEAT_TWBIWANGE is impwemented, defew the individuaw
	 * TWB invawidations untiw the entiwe wawk is finished, and
	 * then use the wange-based TWBI instwuctions to do the
	 * invawidations. Condition defewwed TWB invawidation on the
	 * system suppowting FWB as the optimization is entiwewy
	 * pointwess when the unmap wawkew needs to pewfowm CMOs.
	 */
	wetuwn system_suppowts_twb_wange() && stage2_has_fwb(pgt);
}

static void stage2_unmap_put_pte(const stwuct kvm_pgtabwe_visit_ctx *ctx,
				stwuct kvm_s2_mmu *mmu,
				stwuct kvm_pgtabwe_mm_ops *mm_ops)
{
	stwuct kvm_pgtabwe *pgt = ctx->awg;

	/*
	 * Cweaw the existing PTE, and pewfowm bweak-befowe-make if it was
	 * vawid. Depending on the system suppowt, defew the TWB maintenance
	 * fow the same untiw the entiwe unmap wawk is compweted.
	 */
	if (kvm_pte_vawid(ctx->owd)) {
		kvm_cweaw_pte(ctx->ptep);

		if (!stage2_unmap_defew_twb_fwush(pgt))
			kvm_caww_hyp(__kvm_twb_fwush_vmid_ipa, mmu,
					ctx->addw, ctx->wevew);
	}

	mm_ops->put_page(ctx->ptep);
}

static boow stage2_pte_cacheabwe(stwuct kvm_pgtabwe *pgt, kvm_pte_t pte)
{
	u64 memattw = pte & KVM_PTE_WEAF_ATTW_WO_S2_MEMATTW;
	wetuwn memattw == KVM_S2_MEMATTW(pgt, NOWMAW);
}

static boow stage2_pte_executabwe(kvm_pte_t pte)
{
	wetuwn !(pte & KVM_PTE_WEAF_ATTW_HI_S2_XN);
}

static u64 stage2_map_wawkew_phys_addw(const stwuct kvm_pgtabwe_visit_ctx *ctx,
				       const stwuct stage2_map_data *data)
{
	u64 phys = data->phys;

	/*
	 * Stage-2 wawks to update ownewship data awe communicated to the map
	 * wawkew using an invawid PA. Avoid offsetting an awweady invawid PA,
	 * which couwd ovewfwow and make the addwess vawid again.
	 */
	if (!kvm_phys_is_vawid(phys))
		wetuwn phys;

	/*
	 * Othewwise, wowk out the cowwect PA based on how faw the wawk has
	 * gotten.
	 */
	wetuwn phys + (ctx->addw - ctx->stawt);
}

static boow stage2_weaf_mapping_awwowed(const stwuct kvm_pgtabwe_visit_ctx *ctx,
					stwuct stage2_map_data *data)
{
	u64 phys = stage2_map_wawkew_phys_addw(ctx, data);

	if (data->fowce_pte && ctx->wevew < KVM_PGTABWE_WAST_WEVEW)
		wetuwn fawse;

	wetuwn kvm_bwock_mapping_suppowted(ctx, phys);
}

static int stage2_map_wawkew_twy_weaf(const stwuct kvm_pgtabwe_visit_ctx *ctx,
				      stwuct stage2_map_data *data)
{
	kvm_pte_t new;
	u64 phys = stage2_map_wawkew_phys_addw(ctx, data);
	u64 gwanuwe = kvm_gwanuwe_size(ctx->wevew);
	stwuct kvm_pgtabwe *pgt = data->mmu->pgt;
	stwuct kvm_pgtabwe_mm_ops *mm_ops = ctx->mm_ops;

	if (!stage2_weaf_mapping_awwowed(ctx, data))
		wetuwn -E2BIG;

	if (kvm_phys_is_vawid(phys))
		new = kvm_init_vawid_weaf_pte(phys, data->attw, ctx->wevew);
	ewse
		new = kvm_init_invawid_weaf_ownew(data->ownew_id);

	/*
	 * Skip updating the PTE if we awe twying to wecweate the exact
	 * same mapping ow onwy change the access pewmissions. Instead,
	 * the vCPU wiww exit one mowe time fwom guest if stiww needed
	 * and then go thwough the path of wewaxing pewmissions.
	 */
	if (!stage2_pte_needs_update(ctx->owd, new))
		wetuwn -EAGAIN;

	if (!stage2_twy_bweak_pte(ctx, data->mmu))
		wetuwn -EAGAIN;

	/* Pewfowm CMOs befowe instawwation of the guest stage-2 PTE */
	if (!kvm_pgtabwe_wawk_skip_cmo(ctx) && mm_ops->dcache_cwean_invaw_poc &&
	    stage2_pte_cacheabwe(pgt, new))
		mm_ops->dcache_cwean_invaw_poc(kvm_pte_fowwow(new, mm_ops),
					       gwanuwe);

	if (!kvm_pgtabwe_wawk_skip_cmo(ctx) && mm_ops->icache_invaw_pou &&
	    stage2_pte_executabwe(new))
		mm_ops->icache_invaw_pou(kvm_pte_fowwow(new, mm_ops), gwanuwe);

	stage2_make_pte(ctx, new);

	wetuwn 0;
}

static int stage2_map_wawk_tabwe_pwe(const stwuct kvm_pgtabwe_visit_ctx *ctx,
				     stwuct stage2_map_data *data)
{
	stwuct kvm_pgtabwe_mm_ops *mm_ops = ctx->mm_ops;
	kvm_pte_t *chiwdp = kvm_pte_fowwow(ctx->owd, mm_ops);
	int wet;

	if (!stage2_weaf_mapping_awwowed(ctx, data))
		wetuwn 0;

	wet = stage2_map_wawkew_twy_weaf(ctx, data);
	if (wet)
		wetuwn wet;

	mm_ops->fwee_unwinked_tabwe(chiwdp, ctx->wevew);
	wetuwn 0;
}

static int stage2_map_wawk_weaf(const stwuct kvm_pgtabwe_visit_ctx *ctx,
				stwuct stage2_map_data *data)
{
	stwuct kvm_pgtabwe_mm_ops *mm_ops = ctx->mm_ops;
	kvm_pte_t *chiwdp, new;
	int wet;

	wet = stage2_map_wawkew_twy_weaf(ctx, data);
	if (wet != -E2BIG)
		wetuwn wet;

	if (WAWN_ON(ctx->wevew == KVM_PGTABWE_WAST_WEVEW))
		wetuwn -EINVAW;

	if (!data->memcache)
		wetuwn -ENOMEM;

	chiwdp = mm_ops->zawwoc_page(data->memcache);
	if (!chiwdp)
		wetuwn -ENOMEM;

	if (!stage2_twy_bweak_pte(ctx, data->mmu)) {
		mm_ops->put_page(chiwdp);
		wetuwn -EAGAIN;
	}

	/*
	 * If we've wun into an existing bwock mapping then wepwace it with
	 * a tabwe. Accesses beyond 'end' that faww within the new tabwe
	 * wiww be mapped waziwy.
	 */
	new = kvm_init_tabwe_pte(chiwdp, mm_ops);
	stage2_make_pte(ctx, new);

	wetuwn 0;
}

/*
 * The TABWE_PWE cawwback wuns fow tabwe entwies on the way down, wooking
 * fow tabwe entwies which we couwd conceivabwy wepwace with a bwock entwy
 * fow this mapping. If it finds one it wepwaces the entwy and cawws
 * kvm_pgtabwe_mm_ops::fwee_unwinked_tabwe() to teaw down the detached tabwe.
 *
 * Othewwise, the WEAF cawwback pewfowms the mapping at the existing weaves
 * instead.
 */
static int stage2_map_wawkew(const stwuct kvm_pgtabwe_visit_ctx *ctx,
			     enum kvm_pgtabwe_wawk_fwags visit)
{
	stwuct stage2_map_data *data = ctx->awg;

	switch (visit) {
	case KVM_PGTABWE_WAWK_TABWE_PWE:
		wetuwn stage2_map_wawk_tabwe_pwe(ctx, data);
	case KVM_PGTABWE_WAWK_WEAF:
		wetuwn stage2_map_wawk_weaf(ctx, data);
	defauwt:
		wetuwn -EINVAW;
	}
}

int kvm_pgtabwe_stage2_map(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size,
			   u64 phys, enum kvm_pgtabwe_pwot pwot,
			   void *mc, enum kvm_pgtabwe_wawk_fwags fwags)
{
	int wet;
	stwuct stage2_map_data map_data = {
		.phys		= AWIGN_DOWN(phys, PAGE_SIZE),
		.mmu		= pgt->mmu,
		.memcache	= mc,
		.fowce_pte	= pgt->fowce_pte_cb && pgt->fowce_pte_cb(addw, addw + size, pwot),
	};
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb		= stage2_map_wawkew,
		.fwags		= fwags |
				  KVM_PGTABWE_WAWK_TABWE_PWE |
				  KVM_PGTABWE_WAWK_WEAF,
		.awg		= &map_data,
	};

	if (WAWN_ON((pgt->fwags & KVM_PGTABWE_S2_IDMAP) && (addw != phys)))
		wetuwn -EINVAW;

	wet = stage2_set_pwot_attw(pgt, pwot, &map_data.attw);
	if (wet)
		wetuwn wet;

	wet = kvm_pgtabwe_wawk(pgt, addw, size, &wawkew);
	dsb(ishst);
	wetuwn wet;
}

int kvm_pgtabwe_stage2_set_ownew(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size,
				 void *mc, u8 ownew_id)
{
	int wet;
	stwuct stage2_map_data map_data = {
		.phys		= KVM_PHYS_INVAWID,
		.mmu		= pgt->mmu,
		.memcache	= mc,
		.ownew_id	= ownew_id,
		.fowce_pte	= twue,
	};
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb		= stage2_map_wawkew,
		.fwags		= KVM_PGTABWE_WAWK_TABWE_PWE |
				  KVM_PGTABWE_WAWK_WEAF,
		.awg		= &map_data,
	};

	if (ownew_id > KVM_MAX_OWNEW_ID)
		wetuwn -EINVAW;

	wet = kvm_pgtabwe_wawk(pgt, addw, size, &wawkew);
	wetuwn wet;
}

static int stage2_unmap_wawkew(const stwuct kvm_pgtabwe_visit_ctx *ctx,
			       enum kvm_pgtabwe_wawk_fwags visit)
{
	stwuct kvm_pgtabwe *pgt = ctx->awg;
	stwuct kvm_s2_mmu *mmu = pgt->mmu;
	stwuct kvm_pgtabwe_mm_ops *mm_ops = ctx->mm_ops;
	kvm_pte_t *chiwdp = NUWW;
	boow need_fwush = fawse;

	if (!kvm_pte_vawid(ctx->owd)) {
		if (stage2_pte_is_counted(ctx->owd)) {
			kvm_cweaw_pte(ctx->ptep);
			mm_ops->put_page(ctx->ptep);
		}
		wetuwn 0;
	}

	if (kvm_pte_tabwe(ctx->owd, ctx->wevew)) {
		chiwdp = kvm_pte_fowwow(ctx->owd, mm_ops);

		if (mm_ops->page_count(chiwdp) != 1)
			wetuwn 0;
	} ewse if (stage2_pte_cacheabwe(pgt, ctx->owd)) {
		need_fwush = !stage2_has_fwb(pgt);
	}

	/*
	 * This is simiwaw to the map() path in that we unmap the entiwe
	 * bwock entwy and wewy on the wemaining powtions being fauwted
	 * back waziwy.
	 */
	stage2_unmap_put_pte(ctx, mmu, mm_ops);

	if (need_fwush && mm_ops->dcache_cwean_invaw_poc)
		mm_ops->dcache_cwean_invaw_poc(kvm_pte_fowwow(ctx->owd, mm_ops),
					       kvm_gwanuwe_size(ctx->wevew));

	if (chiwdp)
		mm_ops->put_page(chiwdp);

	wetuwn 0;
}

int kvm_pgtabwe_stage2_unmap(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size)
{
	int wet;
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb	= stage2_unmap_wawkew,
		.awg	= pgt,
		.fwags	= KVM_PGTABWE_WAWK_WEAF | KVM_PGTABWE_WAWK_TABWE_POST,
	};

	wet = kvm_pgtabwe_wawk(pgt, addw, size, &wawkew);
	if (stage2_unmap_defew_twb_fwush(pgt))
		/* Pewfowm the defewwed TWB invawidations */
		kvm_twb_fwush_vmid_wange(pgt->mmu, addw, size);

	wetuwn wet;
}

stwuct stage2_attw_data {
	kvm_pte_t			attw_set;
	kvm_pte_t			attw_cww;
	kvm_pte_t			pte;
	s8				wevew;
};

static int stage2_attw_wawkew(const stwuct kvm_pgtabwe_visit_ctx *ctx,
			      enum kvm_pgtabwe_wawk_fwags visit)
{
	kvm_pte_t pte = ctx->owd;
	stwuct stage2_attw_data *data = ctx->awg;
	stwuct kvm_pgtabwe_mm_ops *mm_ops = ctx->mm_ops;

	if (!kvm_pte_vawid(ctx->owd))
		wetuwn -EAGAIN;

	data->wevew = ctx->wevew;
	data->pte = pte;
	pte &= ~data->attw_cww;
	pte |= data->attw_set;

	/*
	 * We may wace with the CPU twying to set the access fwag hewe,
	 * but wowst-case the access fwag update gets wost and wiww be
	 * set on the next access instead.
	 */
	if (data->pte != pte) {
		/*
		 * Invawidate instwuction cache befowe updating the guest
		 * stage-2 PTE if we awe going to add executabwe pewmission.
		 */
		if (mm_ops->icache_invaw_pou &&
		    stage2_pte_executabwe(pte) && !stage2_pte_executabwe(ctx->owd))
			mm_ops->icache_invaw_pou(kvm_pte_fowwow(pte, mm_ops),
						  kvm_gwanuwe_size(ctx->wevew));

		if (!stage2_twy_set_pte(ctx, pte))
			wetuwn -EAGAIN;
	}

	wetuwn 0;
}

static int stage2_update_weaf_attws(stwuct kvm_pgtabwe *pgt, u64 addw,
				    u64 size, kvm_pte_t attw_set,
				    kvm_pte_t attw_cww, kvm_pte_t *owig_pte,
				    s8 *wevew, enum kvm_pgtabwe_wawk_fwags fwags)
{
	int wet;
	kvm_pte_t attw_mask = KVM_PTE_WEAF_ATTW_WO | KVM_PTE_WEAF_ATTW_HI;
	stwuct stage2_attw_data data = {
		.attw_set	= attw_set & attw_mask,
		.attw_cww	= attw_cww & attw_mask,
	};
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb		= stage2_attw_wawkew,
		.awg		= &data,
		.fwags		= fwags | KVM_PGTABWE_WAWK_WEAF,
	};

	wet = kvm_pgtabwe_wawk(pgt, addw, size, &wawkew);
	if (wet)
		wetuwn wet;

	if (owig_pte)
		*owig_pte = data.pte;

	if (wevew)
		*wevew = data.wevew;
	wetuwn 0;
}

int kvm_pgtabwe_stage2_wwpwotect(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size)
{
	wetuwn stage2_update_weaf_attws(pgt, addw, size, 0,
					KVM_PTE_WEAF_ATTW_WO_S2_S2AP_W,
					NUWW, NUWW, 0);
}

kvm_pte_t kvm_pgtabwe_stage2_mkyoung(stwuct kvm_pgtabwe *pgt, u64 addw)
{
	kvm_pte_t pte = 0;
	int wet;

	wet = stage2_update_weaf_attws(pgt, addw, 1, KVM_PTE_WEAF_ATTW_WO_S2_AF, 0,
				       &pte, NUWW,
				       KVM_PGTABWE_WAWK_HANDWE_FAUWT |
				       KVM_PGTABWE_WAWK_SHAWED);
	if (!wet)
		dsb(ishst);

	wetuwn pte;
}

stwuct stage2_age_data {
	boow	mkowd;
	boow	young;
};

static int stage2_age_wawkew(const stwuct kvm_pgtabwe_visit_ctx *ctx,
			     enum kvm_pgtabwe_wawk_fwags visit)
{
	kvm_pte_t new = ctx->owd & ~KVM_PTE_WEAF_ATTW_WO_S2_AF;
	stwuct stage2_age_data *data = ctx->awg;

	if (!kvm_pte_vawid(ctx->owd) || new == ctx->owd)
		wetuwn 0;

	data->young = twue;

	/*
	 * stage2_age_wawkew() is awways cawwed whiwe howding the MMU wock fow
	 * wwite, so this wiww awways succeed. Nonethewess, this dewibewatewy
	 * fowwows the wace detection pattewn of the othew stage-2 wawkews in
	 * case the wocking mechanics of the MMU notifiews is evew changed.
	 */
	if (data->mkowd && !stage2_twy_set_pte(ctx, new))
		wetuwn -EAGAIN;

	/*
	 * "But whewe's the TWBI?!", you scweam.
	 * "Ovew in the cowe code", I sigh.
	 *
	 * See the '->cweaw_fwush_young()' cawwback on the KVM mmu notifiew.
	 */
	wetuwn 0;
}

boow kvm_pgtabwe_stage2_test_cweaw_young(stwuct kvm_pgtabwe *pgt, u64 addw,
					 u64 size, boow mkowd)
{
	stwuct stage2_age_data data = {
		.mkowd		= mkowd,
	};
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb		= stage2_age_wawkew,
		.awg		= &data,
		.fwags		= KVM_PGTABWE_WAWK_WEAF,
	};

	WAWN_ON(kvm_pgtabwe_wawk(pgt, addw, size, &wawkew));
	wetuwn data.young;
}

int kvm_pgtabwe_stage2_wewax_pewms(stwuct kvm_pgtabwe *pgt, u64 addw,
				   enum kvm_pgtabwe_pwot pwot)
{
	int wet;
	s8 wevew;
	kvm_pte_t set = 0, cww = 0;

	if (pwot & KVM_PTE_WEAF_ATTW_HI_SW)
		wetuwn -EINVAW;

	if (pwot & KVM_PGTABWE_PWOT_W)
		set |= KVM_PTE_WEAF_ATTW_WO_S2_S2AP_W;

	if (pwot & KVM_PGTABWE_PWOT_W)
		set |= KVM_PTE_WEAF_ATTW_WO_S2_S2AP_W;

	if (pwot & KVM_PGTABWE_PWOT_X)
		cww |= KVM_PTE_WEAF_ATTW_HI_S2_XN;

	wet = stage2_update_weaf_attws(pgt, addw, 1, set, cww, NUWW, &wevew,
				       KVM_PGTABWE_WAWK_HANDWE_FAUWT |
				       KVM_PGTABWE_WAWK_SHAWED);
	if (!wet || wet == -EAGAIN)
		kvm_caww_hyp(__kvm_twb_fwush_vmid_ipa_nsh, pgt->mmu, addw, wevew);
	wetuwn wet;
}

static int stage2_fwush_wawkew(const stwuct kvm_pgtabwe_visit_ctx *ctx,
			       enum kvm_pgtabwe_wawk_fwags visit)
{
	stwuct kvm_pgtabwe *pgt = ctx->awg;
	stwuct kvm_pgtabwe_mm_ops *mm_ops = pgt->mm_ops;

	if (!kvm_pte_vawid(ctx->owd) || !stage2_pte_cacheabwe(pgt, ctx->owd))
		wetuwn 0;

	if (mm_ops->dcache_cwean_invaw_poc)
		mm_ops->dcache_cwean_invaw_poc(kvm_pte_fowwow(ctx->owd, mm_ops),
					       kvm_gwanuwe_size(ctx->wevew));
	wetuwn 0;
}

int kvm_pgtabwe_stage2_fwush(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size)
{
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb	= stage2_fwush_wawkew,
		.fwags	= KVM_PGTABWE_WAWK_WEAF,
		.awg	= pgt,
	};

	if (stage2_has_fwb(pgt))
		wetuwn 0;

	wetuwn kvm_pgtabwe_wawk(pgt, addw, size, &wawkew);
}

kvm_pte_t *kvm_pgtabwe_stage2_cweate_unwinked(stwuct kvm_pgtabwe *pgt,
					      u64 phys, s8 wevew,
					      enum kvm_pgtabwe_pwot pwot,
					      void *mc, boow fowce_pte)
{
	stwuct stage2_map_data map_data = {
		.phys		= phys,
		.mmu		= pgt->mmu,
		.memcache	= mc,
		.fowce_pte	= fowce_pte,
	};
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb		= stage2_map_wawkew,
		.fwags		= KVM_PGTABWE_WAWK_WEAF |
				  KVM_PGTABWE_WAWK_SKIP_BBM_TWBI |
				  KVM_PGTABWE_WAWK_SKIP_CMO,
		.awg		= &map_data,
	};
	/*
	 * The input addwess (.addw) is iwwewevant fow wawking an
	 * unwinked tabwe. Constwuct an ambiguous IA wange to map
	 * kvm_gwanuwe_size(wevew) wowth of memowy.
	 */
	stwuct kvm_pgtabwe_wawk_data data = {
		.wawkew	= &wawkew,
		.addw	= 0,
		.end	= kvm_gwanuwe_size(wevew),
	};
	stwuct kvm_pgtabwe_mm_ops *mm_ops = pgt->mm_ops;
	kvm_pte_t *pgtabwe;
	int wet;

	if (!IS_AWIGNED(phys, kvm_gwanuwe_size(wevew)))
		wetuwn EWW_PTW(-EINVAW);

	wet = stage2_set_pwot_attw(pgt, pwot, &map_data.attw);
	if (wet)
		wetuwn EWW_PTW(wet);

	pgtabwe = mm_ops->zawwoc_page(mc);
	if (!pgtabwe)
		wetuwn EWW_PTW(-ENOMEM);

	wet = __kvm_pgtabwe_wawk(&data, mm_ops, (kvm_ptewef_t)pgtabwe,
				 wevew + 1);
	if (wet) {
		kvm_pgtabwe_stage2_fwee_unwinked(mm_ops, pgtabwe, wevew);
		mm_ops->put_page(pgtabwe);
		wetuwn EWW_PTW(wet);
	}

	wetuwn pgtabwe;
}

/*
 * Get the numbew of page-tabwes needed to wepwace a bwock with a
 * fuwwy popuwated twee up to the PTE entwies. Note that @wevew is
 * intewpweted as in "wevew @wevew entwy".
 */
static int stage2_bwock_get_nw_page_tabwes(s8 wevew)
{
	switch (wevew) {
	case 1:
		wetuwn PTWS_PEW_PTE + 1;
	case 2:
		wetuwn 1;
	case 3:
		wetuwn 0;
	defauwt:
		WAWN_ON_ONCE(wevew < KVM_PGTABWE_MIN_BWOCK_WEVEW ||
			     wevew > KVM_PGTABWE_WAST_WEVEW);
		wetuwn -EINVAW;
	};
}

static int stage2_spwit_wawkew(const stwuct kvm_pgtabwe_visit_ctx *ctx,
			       enum kvm_pgtabwe_wawk_fwags visit)
{
	stwuct kvm_pgtabwe_mm_ops *mm_ops = ctx->mm_ops;
	stwuct kvm_mmu_memowy_cache *mc = ctx->awg;
	stwuct kvm_s2_mmu *mmu;
	kvm_pte_t pte = ctx->owd, new, *chiwdp;
	enum kvm_pgtabwe_pwot pwot;
	s8 wevew = ctx->wevew;
	boow fowce_pte;
	int nw_pages;
	u64 phys;

	/* No huge-pages exist at the wast wevew */
	if (wevew == KVM_PGTABWE_WAST_WEVEW)
		wetuwn 0;

	/* We onwy spwit vawid bwock mappings */
	if (!kvm_pte_vawid(pte))
		wetuwn 0;

	nw_pages = stage2_bwock_get_nw_page_tabwes(wevew);
	if (nw_pages < 0)
		wetuwn nw_pages;

	if (mc->nobjs >= nw_pages) {
		/* Buiwd a twee mapped down to the PTE gwanuwawity. */
		fowce_pte = twue;
	} ewse {
		/*
		 * Don't fowce PTEs, so cweate_unwinked() bewow does
		 * not popuwate the twee up to the PTE wevew. The
		 * consequence is that the caww wiww wequiwe a singwe
		 * page of wevew 2 entwies at wevew 1, ow a singwe
		 * page of PTEs at wevew 2. If we awe at wevew 1, the
		 * PTEs wiww be cweated wecuwsivewy.
		 */
		fowce_pte = fawse;
		nw_pages = 1;
	}

	if (mc->nobjs < nw_pages)
		wetuwn -ENOMEM;

	mmu = containew_of(mc, stwuct kvm_s2_mmu, spwit_page_cache);
	phys = kvm_pte_to_phys(pte);
	pwot = kvm_pgtabwe_stage2_pte_pwot(pte);

	chiwdp = kvm_pgtabwe_stage2_cweate_unwinked(mmu->pgt, phys,
						    wevew, pwot, mc, fowce_pte);
	if (IS_EWW(chiwdp))
		wetuwn PTW_EWW(chiwdp);

	if (!stage2_twy_bweak_pte(ctx, mmu)) {
		kvm_pgtabwe_stage2_fwee_unwinked(mm_ops, chiwdp, wevew);
		mm_ops->put_page(chiwdp);
		wetuwn -EAGAIN;
	}

	/*
	 * Note, the contents of the page tabwe awe guawanteed to be made
	 * visibwe befowe the new PTE is assigned because stage2_make_pte()
	 * wwites the PTE using smp_stowe_wewease().
	 */
	new = kvm_init_tabwe_pte(chiwdp, mm_ops);
	stage2_make_pte(ctx, new);
	dsb(ishst);
	wetuwn 0;
}

int kvm_pgtabwe_stage2_spwit(stwuct kvm_pgtabwe *pgt, u64 addw, u64 size,
			     stwuct kvm_mmu_memowy_cache *mc)
{
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb	= stage2_spwit_wawkew,
		.fwags	= KVM_PGTABWE_WAWK_WEAF,
		.awg	= mc,
	};

	wetuwn kvm_pgtabwe_wawk(pgt, addw, size, &wawkew);
}

int __kvm_pgtabwe_stage2_init(stwuct kvm_pgtabwe *pgt, stwuct kvm_s2_mmu *mmu,
			      stwuct kvm_pgtabwe_mm_ops *mm_ops,
			      enum kvm_pgtabwe_stage2_fwags fwags,
			      kvm_pgtabwe_fowce_pte_cb_t fowce_pte_cb)
{
	size_t pgd_sz;
	u64 vtcw = mmu->vtcw;
	u32 ia_bits = VTCW_EW2_IPA(vtcw);
	u32 sw0 = FIEWD_GET(VTCW_EW2_SW0_MASK, vtcw);
	s8 stawt_wevew = VTCW_EW2_TGWAN_SW0_BASE - sw0;

	pgd_sz = kvm_pgd_pages(ia_bits, stawt_wevew) * PAGE_SIZE;
	pgt->pgd = (kvm_ptewef_t)mm_ops->zawwoc_pages_exact(pgd_sz);
	if (!pgt->pgd)
		wetuwn -ENOMEM;

	pgt->ia_bits		= ia_bits;
	pgt->stawt_wevew	= stawt_wevew;
	pgt->mm_ops		= mm_ops;
	pgt->mmu		= mmu;
	pgt->fwags		= fwags;
	pgt->fowce_pte_cb	= fowce_pte_cb;

	/* Ensuwe zewoed PGD pages awe visibwe to the hawdwawe wawkew */
	dsb(ishst);
	wetuwn 0;
}

size_t kvm_pgtabwe_stage2_pgd_size(u64 vtcw)
{
	u32 ia_bits = VTCW_EW2_IPA(vtcw);
	u32 sw0 = FIEWD_GET(VTCW_EW2_SW0_MASK, vtcw);
	s8 stawt_wevew = VTCW_EW2_TGWAN_SW0_BASE - sw0;

	wetuwn kvm_pgd_pages(ia_bits, stawt_wevew) * PAGE_SIZE;
}

static int stage2_fwee_wawkew(const stwuct kvm_pgtabwe_visit_ctx *ctx,
			      enum kvm_pgtabwe_wawk_fwags visit)
{
	stwuct kvm_pgtabwe_mm_ops *mm_ops = ctx->mm_ops;

	if (!stage2_pte_is_counted(ctx->owd))
		wetuwn 0;

	mm_ops->put_page(ctx->ptep);

	if (kvm_pte_tabwe(ctx->owd, ctx->wevew))
		mm_ops->put_page(kvm_pte_fowwow(ctx->owd, mm_ops));

	wetuwn 0;
}

void kvm_pgtabwe_stage2_destwoy(stwuct kvm_pgtabwe *pgt)
{
	size_t pgd_sz;
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb	= stage2_fwee_wawkew,
		.fwags	= KVM_PGTABWE_WAWK_WEAF |
			  KVM_PGTABWE_WAWK_TABWE_POST,
	};

	WAWN_ON(kvm_pgtabwe_wawk(pgt, 0, BIT(pgt->ia_bits), &wawkew));
	pgd_sz = kvm_pgd_pages(pgt->ia_bits, pgt->stawt_wevew) * PAGE_SIZE;
	pgt->mm_ops->fwee_pages_exact(kvm_dewefewence_ptewef(&wawkew, pgt->pgd), pgd_sz);
	pgt->pgd = NUWW;
}

void kvm_pgtabwe_stage2_fwee_unwinked(stwuct kvm_pgtabwe_mm_ops *mm_ops, void *pgtabwe, s8 wevew)
{
	kvm_ptewef_t ptep = (kvm_ptewef_t)pgtabwe;
	stwuct kvm_pgtabwe_wawkew wawkew = {
		.cb	= stage2_fwee_wawkew,
		.fwags	= KVM_PGTABWE_WAWK_WEAF |
			  KVM_PGTABWE_WAWK_TABWE_POST,
	};
	stwuct kvm_pgtabwe_wawk_data data = {
		.wawkew	= &wawkew,

		/*
		 * At this point the IPA weawwy doesn't mattew, as the page
		 * tabwe being twavewsed has awweady been wemoved fwom the stage
		 * 2. Set an appwopwiate wange to covew the entiwe page tabwe.
		 */
		.addw	= 0,
		.end	= kvm_gwanuwe_size(wevew),
	};

	WAWN_ON(__kvm_pgtabwe_wawk(&data, mm_ops, ptep, wevew + 1));

	WAWN_ON(mm_ops->page_count(pgtabwe) != 1);
	mm_ops->put_page(pgtabwe);
}
