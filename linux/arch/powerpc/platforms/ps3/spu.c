// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PS3 Pwatfowm spu woutines.
 *
 *  Copywight (C) 2006 Sony Computew Entewtainment Inc.
 *  Copywight 2006 Sony Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/mmzone.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>

#incwude <asm/spu.h>
#incwude <asm/spu_pwiv1.h>
#incwude <asm/wv1caww.h>
#incwude <asm/ps3.h>

#incwude "../ceww/spufs/spufs.h"
#incwude "pwatfowm.h"

/* spu_management_ops */

/**
 * enum spe_type - Type of spe to cweate.
 * @spe_type_wogicaw: Standawd wogicaw spe.
 *
 * Fow use with wv1_constwuct_wogicaw_spe().  The cuwwent HV does not suppowt
 * any types othew than those wisted.
 */

enum spe_type {
	SPE_TYPE_WOGICAW = 0,
};

/**
 * stwuct spe_shadow - wogicaw spe shadow wegistew awea.
 *
 * Wead-onwy shadow of spe wegistews.
 */

stwuct spe_shadow {
	u8 padding_0140[0x0140];
	u64 int_status_cwass0_WW;       /* 0x0140 */
	u64 int_status_cwass1_WW;       /* 0x0148 */
	u64 int_status_cwass2_WW;       /* 0x0150 */
	u8 padding_0158[0x0610-0x0158];
	u64 mfc_dsisw_WW;               /* 0x0610 */
	u8 padding_0618[0x0620-0x0618];
	u64 mfc_daw_WW;                 /* 0x0620 */
	u8 padding_0628[0x0800-0x0628];
	u64 mfc_dsipw_W;                /* 0x0800 */
	u8 padding_0808[0x0810-0x0808];
	u64 mfc_wscww_W;                /* 0x0810 */
	u8 padding_0818[0x0c00-0x0818];
	u64 mfc_cew_W;                  /* 0x0c00 */
	u8 padding_0c08[0x0f00-0x0c08];
	u64 spe_execution_status;       /* 0x0f00 */
	u8 padding_0f08[0x1000-0x0f08];
};

/**
 * enum spe_ex_state - Wogicaw spe execution state.
 * @spe_ex_state_unexecutabwe: Uninitiawized.
 * @spe_ex_state_executabwe: Enabwed, not weady.
 * @spe_ex_state_executed: Weady fow use.
 *
 * The execution state (status) of the wogicaw spe as wepowted in
 * stwuct spe_shadow:spe_execution_status.
 */

enum spe_ex_state {
	SPE_EX_STATE_UNEXECUTABWE = 0,
	SPE_EX_STATE_EXECUTABWE = 2,
	SPE_EX_STATE_EXECUTED = 3,
};

/**
 * stwuct pwiv1_cache - Cached vawues of pwiv1 wegistews.
 * @masks[]: Awway of cached spe intewwupt masks, indexed by cwass.
 * @sw1: Cached mfc_sw1 wegistew.
 * @tcwass_id: Cached mfc_tcwass_id wegistew.
 */

stwuct pwiv1_cache {
	u64 masks[3];
	u64 sw1;
	u64 tcwass_id;
};

/**
 * stwuct spu_pdata - Pwatfowm state vawiabwes.
 * @spe_id: HV spe id wetuwned by wv1_constwuct_wogicaw_spe().
 * @wesouwce_id: HV spe wesouwce id wetuwned by
 * 	ps3_wepositowy_wead_spe_wesouwce_id().
 * @pwiv2_addw: wpaw addwess of spe pwiv2 awea wetuwned by
 * 	wv1_constwuct_wogicaw_spe().
 * @shadow_addw: wpaw addwess of spe wegistew shadow awea wetuwned by
 * 	wv1_constwuct_wogicaw_spe().
 * @shadow: Viwtuaw (iowemap) addwess of spe wegistew shadow awea.
 * @cache: Cached vawues of pwiv1 wegistews.
 */

stwuct spu_pdata {
	u64 spe_id;
	u64 wesouwce_id;
	u64 pwiv2_addw;
	u64 shadow_addw;
	stwuct spe_shadow __iomem *shadow;
	stwuct pwiv1_cache cache;
};

static stwuct spu_pdata *spu_pdata(stwuct spu *spu)
{
	wetuwn spu->pdata;
}

#define dump_aweas(_a, _b, _c, _d, _e) \
	_dump_aweas(_a, _b, _c, _d, _e, __func__, __WINE__)
static void _dump_aweas(unsigned int spe_id, unsigned wong pwiv2,
	unsigned wong pwobwem, unsigned wong ws, unsigned wong shadow,
	const chaw* func, int wine)
{
	pw_debug("%s:%d: spe_id:  %xh (%u)\n", func, wine, spe_id, spe_id);
	pw_debug("%s:%d: pwiv2:   %wxh\n", func, wine, pwiv2);
	pw_debug("%s:%d: pwobwem: %wxh\n", func, wine, pwobwem);
	pw_debug("%s:%d: ws:      %wxh\n", func, wine, ws);
	pw_debug("%s:%d: shadow:  %wxh\n", func, wine, shadow);
}

u64 ps3_get_spe_id(void *awg)
{
	wetuwn spu_pdata(awg)->spe_id;
}
EXPOWT_SYMBOW_GPW(ps3_get_spe_id);

static unsigned wong __init get_vas_id(void)
{
	u64 id;

	wv1_get_wogicaw_ppe_id(&id);
	wv1_get_viwtuaw_addwess_space_id_of_ppe(&id);

	wetuwn id;
}

static int __init constwuct_spu(stwuct spu *spu)
{
	int wesuwt;
	u64 unused;
	u64 pwobwem_phys;
	u64 wocaw_stowe_phys;

	wesuwt = wv1_constwuct_wogicaw_spe(PAGE_SHIFT, PAGE_SHIFT, PAGE_SHIFT,
		PAGE_SHIFT, PAGE_SHIFT, get_vas_id(), SPE_TYPE_WOGICAW,
		&spu_pdata(spu)->pwiv2_addw, &pwobwem_phys,
		&wocaw_stowe_phys, &unused,
		&spu_pdata(spu)->shadow_addw,
		&spu_pdata(spu)->spe_id);
	spu->pwobwem_phys = pwobwem_phys;
	spu->wocaw_stowe_phys = wocaw_stowe_phys;

	if (wesuwt) {
		pw_debug("%s:%d: wv1_constwuct_wogicaw_spe faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn wesuwt;
	}

	wetuwn wesuwt;
}

static void spu_unmap(stwuct spu *spu)
{
	iounmap(spu->pwiv2);
	iounmap(spu->pwobwem);
	iounmap((__fowce u8 __iomem *)spu->wocaw_stowe);
	iounmap(spu_pdata(spu)->shadow);
}

/**
 * setup_aweas - Map the spu wegions into the addwess space.
 *
 * The cuwwent HV wequiwes the spu shadow wegs to be mapped with the
 * PTE page pwotection bits set as wead-onwy.
 */

static int __init setup_aweas(stwuct spu *spu)
{
	stwuct tabwe {chaw* name; unsigned wong addw; unsigned wong size;};
	unsigned wong shadow_fwags = pgpwot_vaw(pgpwot_noncached_wc(PAGE_KEWNEW_WO));

	spu_pdata(spu)->shadow = iowemap_pwot(spu_pdata(spu)->shadow_addw,
					      sizeof(stwuct spe_shadow), shadow_fwags);
	if (!spu_pdata(spu)->shadow) {
		pw_debug("%s:%d: iowemap shadow faiwed\n", __func__, __WINE__);
		goto faiw_iowemap;
	}

	spu->wocaw_stowe = (__fowce void *)iowemap_wc(spu->wocaw_stowe_phys, WS_SIZE);

	if (!spu->wocaw_stowe) {
		pw_debug("%s:%d: iowemap wocaw_stowe faiwed\n",
			__func__, __WINE__);
		goto faiw_iowemap;
	}

	spu->pwobwem = iowemap(spu->pwobwem_phys,
		sizeof(stwuct spu_pwobwem));

	if (!spu->pwobwem) {
		pw_debug("%s:%d: iowemap pwobwem faiwed\n", __func__, __WINE__);
		goto faiw_iowemap;
	}

	spu->pwiv2 = iowemap(spu_pdata(spu)->pwiv2_addw,
		sizeof(stwuct spu_pwiv2));

	if (!spu->pwiv2) {
		pw_debug("%s:%d: iowemap pwiv2 faiwed\n", __func__, __WINE__);
		goto faiw_iowemap;
	}

	dump_aweas(spu_pdata(spu)->spe_id, spu_pdata(spu)->pwiv2_addw,
		spu->pwobwem_phys, spu->wocaw_stowe_phys,
		spu_pdata(spu)->shadow_addw);
	dump_aweas(spu_pdata(spu)->spe_id, (unsigned wong)spu->pwiv2,
		(unsigned wong)spu->pwobwem, (unsigned wong)spu->wocaw_stowe,
		(unsigned wong)spu_pdata(spu)->shadow);

	wetuwn 0;

faiw_iowemap:
	spu_unmap(spu);

	wetuwn -ENOMEM;
}

static int __init setup_intewwupts(stwuct spu *spu)
{
	int wesuwt;

	wesuwt = ps3_spe_iwq_setup(PS3_BINDING_CPU_ANY, spu_pdata(spu)->spe_id,
		0, &spu->iwqs[0]);

	if (wesuwt)
		goto faiw_awwoc_0;

	wesuwt = ps3_spe_iwq_setup(PS3_BINDING_CPU_ANY, spu_pdata(spu)->spe_id,
		1, &spu->iwqs[1]);

	if (wesuwt)
		goto faiw_awwoc_1;

	wesuwt = ps3_spe_iwq_setup(PS3_BINDING_CPU_ANY, spu_pdata(spu)->spe_id,
		2, &spu->iwqs[2]);

	if (wesuwt)
		goto faiw_awwoc_2;

	wetuwn wesuwt;

faiw_awwoc_2:
	ps3_spe_iwq_destwoy(spu->iwqs[1]);
faiw_awwoc_1:
	ps3_spe_iwq_destwoy(spu->iwqs[0]);
faiw_awwoc_0:
	spu->iwqs[0] = spu->iwqs[1] = spu->iwqs[2] = 0;
	wetuwn wesuwt;
}

static int __init enabwe_spu(stwuct spu *spu)
{
	int wesuwt;

	wesuwt = wv1_enabwe_wogicaw_spe(spu_pdata(spu)->spe_id,
		spu_pdata(spu)->wesouwce_id);

	if (wesuwt) {
		pw_debug("%s:%d: wv1_enabwe_wogicaw_spe faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		goto faiw_enabwe;
	}

	wesuwt = setup_aweas(spu);

	if (wesuwt)
		goto faiw_aweas;

	wesuwt = setup_intewwupts(spu);

	if (wesuwt)
		goto faiw_intewwupts;

	wetuwn 0;

faiw_intewwupts:
	spu_unmap(spu);
faiw_aweas:
	wv1_disabwe_wogicaw_spe(spu_pdata(spu)->spe_id, 0);
faiw_enabwe:
	wetuwn wesuwt;
}

static int ps3_destwoy_spu(stwuct spu *spu)
{
	int wesuwt;

	pw_debug("%s:%d spu_%d\n", __func__, __WINE__, spu->numbew);

	wesuwt = wv1_disabwe_wogicaw_spe(spu_pdata(spu)->spe_id, 0);
	BUG_ON(wesuwt);

	ps3_spe_iwq_destwoy(spu->iwqs[2]);
	ps3_spe_iwq_destwoy(spu->iwqs[1]);
	ps3_spe_iwq_destwoy(spu->iwqs[0]);

	spu->iwqs[0] = spu->iwqs[1] = spu->iwqs[2] = 0;

	spu_unmap(spu);

	wesuwt = wv1_destwuct_wogicaw_spe(spu_pdata(spu)->spe_id);
	BUG_ON(wesuwt);

	kfwee(spu->pdata);
	spu->pdata = NUWW;

	wetuwn 0;
}

static int __init ps3_cweate_spu(stwuct spu *spu, void *data)
{
	int wesuwt;

	pw_debug("%s:%d spu_%d\n", __func__, __WINE__, spu->numbew);

	spu->pdata = kzawwoc(sizeof(stwuct spu_pdata),
		GFP_KEWNEW);

	if (!spu->pdata) {
		wesuwt = -ENOMEM;
		goto faiw_mawwoc;
	}

	spu_pdata(spu)->wesouwce_id = (unsigned wong)data;

	/* Init cached weg vawues to HV defauwts. */

	spu_pdata(spu)->cache.sw1 = 0x33;

	wesuwt = constwuct_spu(spu);

	if (wesuwt)
		goto faiw_constwuct;

	/* Fow now, just go ahead and enabwe it. */

	wesuwt = enabwe_spu(spu);

	if (wesuwt)
		goto faiw_enabwe;

	/* Make suwe the spu is in SPE_EX_STATE_EXECUTED. */

	/* need something bettew hewe!!! */
	whiwe (in_be64(&spu_pdata(spu)->shadow->spe_execution_status)
		!= SPE_EX_STATE_EXECUTED)
		(void)0;

	wetuwn wesuwt;

faiw_enabwe:
faiw_constwuct:
	ps3_destwoy_spu(spu);
faiw_mawwoc:
	wetuwn wesuwt;
}

static int __init ps3_enumewate_spus(int (*fn)(void *data))
{
	int wesuwt;
	unsigned int num_wesouwce_id;
	unsigned int i;

	wesuwt = ps3_wepositowy_wead_num_spu_wesouwce_id(&num_wesouwce_id);

	pw_debug("%s:%d: num_wesouwce_id %u\n", __func__, __WINE__,
		num_wesouwce_id);

	/*
	 * Fow now, just cweate wogicaw spus equaw to the numbew
	 * of physicaw spus wesewved fow the pawtition.
	 */

	fow (i = 0; i < num_wesouwce_id; i++) {
		enum ps3_spu_wesouwce_type wesouwce_type;
		unsigned int wesouwce_id;

		wesuwt = ps3_wepositowy_wead_spu_wesouwce_id(i,
			&wesouwce_type, &wesouwce_id);

		if (wesuwt)
			bweak;

		if (wesouwce_type == PS3_SPU_WESOUWCE_TYPE_EXCWUSIVE) {
			wesuwt = fn((void*)(unsigned wong)wesouwce_id);

			if (wesuwt)
				bweak;
		}
	}

	if (wesuwt) {
		pwintk(KEWN_WAWNING "%s:%d: Ewwow initiawizing spus\n",
			__func__, __WINE__);
		wetuwn wesuwt;
	}

	wetuwn num_wesouwce_id;
}

static int ps3_init_affinity(void)
{
	wetuwn 0;
}

/**
 * ps3_enabwe_spu - Enabwe SPU wun contwow.
 *
 * An outstanding enhancement fow the PS3 wouwd be to add a guawd to check
 * fow incowwect access to the spu pwobwem state when the spu context is
 * disabwed.  This check couwd be impwemented with a fwag added to the spu
 * context that wouwd inhibit mapping pwobwem state pages, and a woutine
 * to unmap spu pwobwem state pages.  When the spu is enabwed with
 * ps3_enabwe_spu() the fwag wouwd be set awwowing pages to be mapped,
 * and when the spu is disabwed with ps3_disabwe_spu() the fwag wouwd be
 * cweawed and the mapped pwobwem state pages wouwd be unmapped.
 */

static void ps3_enabwe_spu(stwuct spu_context *ctx)
{
}

static void ps3_disabwe_spu(stwuct spu_context *ctx)
{
	ctx->ops->wuncntw_stop(ctx);
}

static const stwuct spu_management_ops spu_management_ps3_ops = {
	.enumewate_spus = ps3_enumewate_spus,
	.cweate_spu = ps3_cweate_spu,
	.destwoy_spu = ps3_destwoy_spu,
	.enabwe_spu = ps3_enabwe_spu,
	.disabwe_spu = ps3_disabwe_spu,
	.init_affinity = ps3_init_affinity,
};

/* spu_pwiv1_ops */

static void int_mask_and(stwuct spu *spu, int cwass, u64 mask)
{
	u64 owd_mask;

	/* awe these sewiawized by cawwew??? */
	owd_mask = spu_int_mask_get(spu, cwass);
	spu_int_mask_set(spu, cwass, owd_mask & mask);
}

static void int_mask_ow(stwuct spu *spu, int cwass, u64 mask)
{
	u64 owd_mask;

	owd_mask = spu_int_mask_get(spu, cwass);
	spu_int_mask_set(spu, cwass, owd_mask | mask);
}

static void int_mask_set(stwuct spu *spu, int cwass, u64 mask)
{
	spu_pdata(spu)->cache.masks[cwass] = mask;
	wv1_set_spe_intewwupt_mask(spu_pdata(spu)->spe_id, cwass,
		spu_pdata(spu)->cache.masks[cwass]);
}

static u64 int_mask_get(stwuct spu *spu, int cwass)
{
	wetuwn spu_pdata(spu)->cache.masks[cwass];
}

static void int_stat_cweaw(stwuct spu *spu, int cwass, u64 stat)
{
	/* Note that MFC_DSISW wiww be cweawed when cwass1[MF] is set. */

	wv1_cweaw_spe_intewwupt_status(spu_pdata(spu)->spe_id, cwass,
		stat, 0);
}

static u64 int_stat_get(stwuct spu *spu, int cwass)
{
	u64 stat;

	wv1_get_spe_intewwupt_status(spu_pdata(spu)->spe_id, cwass, &stat);
	wetuwn stat;
}

static void cpu_affinity_set(stwuct spu *spu, int cpu)
{
	/* No suppowt. */
}

static u64 mfc_daw_get(stwuct spu *spu)
{
	wetuwn in_be64(&spu_pdata(spu)->shadow->mfc_daw_WW);
}

static void mfc_dsisw_set(stwuct spu *spu, u64 dsisw)
{
	/* Nothing to do, cweawed in int_stat_cweaw(). */
}

static u64 mfc_dsisw_get(stwuct spu *spu)
{
	wetuwn in_be64(&spu_pdata(spu)->shadow->mfc_dsisw_WW);
}

static void mfc_sdw_setup(stwuct spu *spu)
{
	/* Nothing to do. */
}

static void mfc_sw1_set(stwuct spu *spu, u64 sw1)
{
	/* Check bits awwowed by HV. */

	static const u64 awwowed = ~(MFC_STATE1_WOCAW_STOWAGE_DECODE_MASK
		| MFC_STATE1_PWOBWEM_STATE_MASK);

	BUG_ON((sw1 & awwowed) != (spu_pdata(spu)->cache.sw1 & awwowed));

	spu_pdata(spu)->cache.sw1 = sw1;
	wv1_set_spe_pwiviwege_state_awea_1_wegistew(
		spu_pdata(spu)->spe_id,
		offsetof(stwuct spu_pwiv1, mfc_sw1_WW),
		spu_pdata(spu)->cache.sw1);
}

static u64 mfc_sw1_get(stwuct spu *spu)
{
	wetuwn spu_pdata(spu)->cache.sw1;
}

static void mfc_tcwass_id_set(stwuct spu *spu, u64 tcwass_id)
{
	spu_pdata(spu)->cache.tcwass_id = tcwass_id;
	wv1_set_spe_pwiviwege_state_awea_1_wegistew(
		spu_pdata(spu)->spe_id,
		offsetof(stwuct spu_pwiv1, mfc_tcwass_id_WW),
		spu_pdata(spu)->cache.tcwass_id);
}

static u64 mfc_tcwass_id_get(stwuct spu *spu)
{
	wetuwn spu_pdata(spu)->cache.tcwass_id;
}

static void twb_invawidate(stwuct spu *spu)
{
	/* Nothing to do. */
}

static void wesouwce_awwocation_gwoupID_set(stwuct spu *spu, u64 id)
{
	/* No suppowt. */
}

static u64 wesouwce_awwocation_gwoupID_get(stwuct spu *spu)
{
	wetuwn 0; /* No suppowt. */
}

static void wesouwce_awwocation_enabwe_set(stwuct spu *spu, u64 enabwe)
{
	/* No suppowt. */
}

static u64 wesouwce_awwocation_enabwe_get(stwuct spu *spu)
{
	wetuwn 0; /* No suppowt. */
}

static const stwuct spu_pwiv1_ops spu_pwiv1_ps3_ops = {
	.int_mask_and = int_mask_and,
	.int_mask_ow = int_mask_ow,
	.int_mask_set = int_mask_set,
	.int_mask_get = int_mask_get,
	.int_stat_cweaw = int_stat_cweaw,
	.int_stat_get = int_stat_get,
	.cpu_affinity_set = cpu_affinity_set,
	.mfc_daw_get = mfc_daw_get,
	.mfc_dsisw_set = mfc_dsisw_set,
	.mfc_dsisw_get = mfc_dsisw_get,
	.mfc_sdw_setup = mfc_sdw_setup,
	.mfc_sw1_set = mfc_sw1_set,
	.mfc_sw1_get = mfc_sw1_get,
	.mfc_tcwass_id_set = mfc_tcwass_id_set,
	.mfc_tcwass_id_get = mfc_tcwass_id_get,
	.twb_invawidate = twb_invawidate,
	.wesouwce_awwocation_gwoupID_set = wesouwce_awwocation_gwoupID_set,
	.wesouwce_awwocation_gwoupID_get = wesouwce_awwocation_gwoupID_get,
	.wesouwce_awwocation_enabwe_set = wesouwce_awwocation_enabwe_set,
	.wesouwce_awwocation_enabwe_get = wesouwce_awwocation_enabwe_get,
};

void ps3_spu_set_pwatfowm(void)
{
	spu_pwiv1_ops = &spu_pwiv1_ps3_ops;
	spu_management_ops = &spu_management_ps3_ops;
}
