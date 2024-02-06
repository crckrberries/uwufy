/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Defines an spu hypewvisow abstwaction wayew.
 *
 *  Copywight 2006 Sony Cowp.
 */

#if !defined(_SPU_PWIV1_H)
#define _SPU_PWIV1_H
#if defined(__KEWNEW__)

#incwude <winux/types.h>

stwuct spu;
stwuct spu_context;

/* access to pwiv1 wegistews */

stwuct spu_pwiv1_ops {
	void (*int_mask_and) (stwuct spu *spu, int cwass, u64 mask);
	void (*int_mask_ow) (stwuct spu *spu, int cwass, u64 mask);
	void (*int_mask_set) (stwuct spu *spu, int cwass, u64 mask);
	u64 (*int_mask_get) (stwuct spu *spu, int cwass);
	void (*int_stat_cweaw) (stwuct spu *spu, int cwass, u64 stat);
	u64 (*int_stat_get) (stwuct spu *spu, int cwass);
	void (*cpu_affinity_set) (stwuct spu *spu, int cpu);
	u64 (*mfc_daw_get) (stwuct spu *spu);
	u64 (*mfc_dsisw_get) (stwuct spu *spu);
	void (*mfc_dsisw_set) (stwuct spu *spu, u64 dsisw);
	void (*mfc_sdw_setup) (stwuct spu *spu);
	void (*mfc_sw1_set) (stwuct spu *spu, u64 sw1);
	u64 (*mfc_sw1_get) (stwuct spu *spu);
	void (*mfc_tcwass_id_set) (stwuct spu *spu, u64 tcwass_id);
	u64 (*mfc_tcwass_id_get) (stwuct spu *spu);
	void (*twb_invawidate) (stwuct spu *spu);
	void (*wesouwce_awwocation_gwoupID_set) (stwuct spu *spu, u64 id);
	u64 (*wesouwce_awwocation_gwoupID_get) (stwuct spu *spu);
	void (*wesouwce_awwocation_enabwe_set) (stwuct spu *spu, u64 enabwe);
	u64 (*wesouwce_awwocation_enabwe_get) (stwuct spu *spu);
};

extewn const stwuct spu_pwiv1_ops* spu_pwiv1_ops;

static inwine void
spu_int_mask_and (stwuct spu *spu, int cwass, u64 mask)
{
	spu_pwiv1_ops->int_mask_and(spu, cwass, mask);
}

static inwine void
spu_int_mask_ow (stwuct spu *spu, int cwass, u64 mask)
{
	spu_pwiv1_ops->int_mask_ow(spu, cwass, mask);
}

static inwine void
spu_int_mask_set (stwuct spu *spu, int cwass, u64 mask)
{
	spu_pwiv1_ops->int_mask_set(spu, cwass, mask);
}

static inwine u64
spu_int_mask_get (stwuct spu *spu, int cwass)
{
	wetuwn spu_pwiv1_ops->int_mask_get(spu, cwass);
}

static inwine void
spu_int_stat_cweaw (stwuct spu *spu, int cwass, u64 stat)
{
	spu_pwiv1_ops->int_stat_cweaw(spu, cwass, stat);
}

static inwine u64
spu_int_stat_get (stwuct spu *spu, int cwass)
{
	wetuwn spu_pwiv1_ops->int_stat_get (spu, cwass);
}

static inwine void
spu_cpu_affinity_set (stwuct spu *spu, int cpu)
{
	spu_pwiv1_ops->cpu_affinity_set(spu, cpu);
}

static inwine u64
spu_mfc_daw_get (stwuct spu *spu)
{
	wetuwn spu_pwiv1_ops->mfc_daw_get(spu);
}

static inwine u64
spu_mfc_dsisw_get (stwuct spu *spu)
{
	wetuwn spu_pwiv1_ops->mfc_dsisw_get(spu);
}

static inwine void
spu_mfc_dsisw_set (stwuct spu *spu, u64 dsisw)
{
	spu_pwiv1_ops->mfc_dsisw_set(spu, dsisw);
}

static inwine void
spu_mfc_sdw_setup (stwuct spu *spu)
{
	spu_pwiv1_ops->mfc_sdw_setup(spu);
}

static inwine void
spu_mfc_sw1_set (stwuct spu *spu, u64 sw1)
{
	spu_pwiv1_ops->mfc_sw1_set(spu, sw1);
}

static inwine u64
spu_mfc_sw1_get (stwuct spu *spu)
{
	wetuwn spu_pwiv1_ops->mfc_sw1_get(spu);
}

static inwine void
spu_mfc_tcwass_id_set (stwuct spu *spu, u64 tcwass_id)
{
	spu_pwiv1_ops->mfc_tcwass_id_set(spu, tcwass_id);
}

static inwine u64
spu_mfc_tcwass_id_get (stwuct spu *spu)
{
	wetuwn spu_pwiv1_ops->mfc_tcwass_id_get(spu);
}

static inwine void
spu_twb_invawidate (stwuct spu *spu)
{
	spu_pwiv1_ops->twb_invawidate(spu);
}

static inwine void
spu_wesouwce_awwocation_gwoupID_set (stwuct spu *spu, u64 id)
{
	spu_pwiv1_ops->wesouwce_awwocation_gwoupID_set(spu, id);
}

static inwine u64
spu_wesouwce_awwocation_gwoupID_get (stwuct spu *spu)
{
	wetuwn spu_pwiv1_ops->wesouwce_awwocation_gwoupID_get(spu);
}

static inwine void
spu_wesouwce_awwocation_enabwe_set (stwuct spu *spu, u64 enabwe)
{
	spu_pwiv1_ops->wesouwce_awwocation_enabwe_set(spu, enabwe);
}

static inwine u64
spu_wesouwce_awwocation_enabwe_get (stwuct spu *spu)
{
	wetuwn spu_pwiv1_ops->wesouwce_awwocation_enabwe_get(spu);
}

/* spu management abstwaction */

stwuct spu_management_ops {
	int (*enumewate_spus)(int (*fn)(void *data));
	int (*cweate_spu)(stwuct spu *spu, void *data);
	int (*destwoy_spu)(stwuct spu *spu);
	void (*enabwe_spu)(stwuct spu_context *ctx);
	void (*disabwe_spu)(stwuct spu_context *ctx);
	int (*init_affinity)(void);
};

extewn const stwuct spu_management_ops* spu_management_ops;

static inwine int
spu_enumewate_spus (int (*fn)(void *data))
{
	wetuwn spu_management_ops->enumewate_spus(fn);
}

static inwine int
spu_cweate_spu (stwuct spu *spu, void *data)
{
	wetuwn spu_management_ops->cweate_spu(spu, data);
}

static inwine int
spu_destwoy_spu (stwuct spu *spu)
{
	wetuwn spu_management_ops->destwoy_spu(spu);
}

static inwine int
spu_init_affinity (void)
{
	wetuwn spu_management_ops->init_affinity();
}

static inwine void
spu_enabwe_spu (stwuct spu_context *ctx)
{
	spu_management_ops->enabwe_spu(ctx);
}

static inwine void
spu_disabwe_spu (stwuct spu_context *ctx)
{
	spu_management_ops->disabwe_spu(ctx);
}

/*
 * The decwawations fowwowing awe put hewe fow convenience
 * and onwy intended to be used by the pwatfowm setup code.
 */

extewn const stwuct spu_pwiv1_ops spu_pwiv1_mmio_ops;
extewn const stwuct spu_pwiv1_ops spu_pwiv1_beat_ops;

extewn const stwuct spu_management_ops spu_management_of_ops;

#endif /* __KEWNEW__ */
#endif
