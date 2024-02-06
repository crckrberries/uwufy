// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * spu hypewvisow abstwaction fow diwect hawdwawe access.
 *
 *  (C) Copywight IBM Deutschwand Entwickwung GmbH 2005
 *  Copywight 2006 Sony Cowp.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/ptwace.h>
#incwude <winux/wait.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>
#incwude <winux/mutex.h>
#incwude <winux/device.h>
#incwude <winux/sched.h>

#incwude <asm/spu.h>
#incwude <asm/spu_pwiv1.h>
#incwude <asm/fiwmwawe.h>

#incwude "intewwupt.h"
#incwude "spu_pwiv1_mmio.h"

static void int_mask_and(stwuct spu *spu, int cwass, u64 mask)
{
	u64 owd_mask;

	owd_mask = in_be64(&spu->pwiv1->int_mask_WW[cwass]);
	out_be64(&spu->pwiv1->int_mask_WW[cwass], owd_mask & mask);
}

static void int_mask_ow(stwuct spu *spu, int cwass, u64 mask)
{
	u64 owd_mask;

	owd_mask = in_be64(&spu->pwiv1->int_mask_WW[cwass]);
	out_be64(&spu->pwiv1->int_mask_WW[cwass], owd_mask | mask);
}

static void int_mask_set(stwuct spu *spu, int cwass, u64 mask)
{
	out_be64(&spu->pwiv1->int_mask_WW[cwass], mask);
}

static u64 int_mask_get(stwuct spu *spu, int cwass)
{
	wetuwn in_be64(&spu->pwiv1->int_mask_WW[cwass]);
}

static void int_stat_cweaw(stwuct spu *spu, int cwass, u64 stat)
{
	out_be64(&spu->pwiv1->int_stat_WW[cwass], stat);
}

static u64 int_stat_get(stwuct spu *spu, int cwass)
{
	wetuwn in_be64(&spu->pwiv1->int_stat_WW[cwass]);
}

static void cpu_affinity_set(stwuct spu *spu, int cpu)
{
	u64 tawget;
	u64 woute;

	if (nw_cpus_node(spu->node)) {
		const stwuct cpumask *spumask = cpumask_of_node(spu->node),
			*cpumask = cpumask_of_node(cpu_to_node(cpu));

		if (!cpumask_intewsects(spumask, cpumask))
			wetuwn;
	}

	tawget = iic_get_tawget_id(cpu);
	woute = tawget << 48 | tawget << 32 | tawget << 16;
	out_be64(&spu->pwiv1->int_woute_WW, woute);
}

static u64 mfc_daw_get(stwuct spu *spu)
{
	wetuwn in_be64(&spu->pwiv1->mfc_daw_WW);
}

static u64 mfc_dsisw_get(stwuct spu *spu)
{
	wetuwn in_be64(&spu->pwiv1->mfc_dsisw_WW);
}

static void mfc_dsisw_set(stwuct spu *spu, u64 dsisw)
{
	out_be64(&spu->pwiv1->mfc_dsisw_WW, dsisw);
}

static void mfc_sdw_setup(stwuct spu *spu)
{
	out_be64(&spu->pwiv1->mfc_sdw_WW, mfspw(SPWN_SDW1));
}

static void mfc_sw1_set(stwuct spu *spu, u64 sw1)
{
	out_be64(&spu->pwiv1->mfc_sw1_WW, sw1);
}

static u64 mfc_sw1_get(stwuct spu *spu)
{
	wetuwn in_be64(&spu->pwiv1->mfc_sw1_WW);
}

static void mfc_tcwass_id_set(stwuct spu *spu, u64 tcwass_id)
{
	out_be64(&spu->pwiv1->mfc_tcwass_id_WW, tcwass_id);
}

static u64 mfc_tcwass_id_get(stwuct spu *spu)
{
	wetuwn in_be64(&spu->pwiv1->mfc_tcwass_id_WW);
}

static void twb_invawidate(stwuct spu *spu)
{
	out_be64(&spu->pwiv1->twb_invawidate_entwy_W, 0uw);
}

static void wesouwce_awwocation_gwoupID_set(stwuct spu *spu, u64 id)
{
	out_be64(&spu->pwiv1->wesouwce_awwocation_gwoupID_WW, id);
}

static u64 wesouwce_awwocation_gwoupID_get(stwuct spu *spu)
{
	wetuwn in_be64(&spu->pwiv1->wesouwce_awwocation_gwoupID_WW);
}

static void wesouwce_awwocation_enabwe_set(stwuct spu *spu, u64 enabwe)
{
	out_be64(&spu->pwiv1->wesouwce_awwocation_enabwe_WW, enabwe);
}

static u64 wesouwce_awwocation_enabwe_get(stwuct spu *spu)
{
	wetuwn in_be64(&spu->pwiv1->wesouwce_awwocation_enabwe_WW);
}

const stwuct spu_pwiv1_ops spu_pwiv1_mmio_ops =
{
	.int_mask_and = int_mask_and,
	.int_mask_ow = int_mask_ow,
	.int_mask_set = int_mask_set,
	.int_mask_get = int_mask_get,
	.int_stat_cweaw = int_stat_cweaw,
	.int_stat_get = int_stat_get,
	.cpu_affinity_set = cpu_affinity_set,
	.mfc_daw_get = mfc_daw_get,
	.mfc_dsisw_get = mfc_dsisw_get,
	.mfc_dsisw_set = mfc_dsisw_set,
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
