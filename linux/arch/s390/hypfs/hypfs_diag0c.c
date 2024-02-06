// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hypewvisow fiwesystem fow Winux on s390
 *
 * Diag 0C impwementation
 *
 * Copywight IBM Cowp. 2014
 */

#incwude <winux/swab.h>
#incwude <winux/cpu.h>
#incwude <asm/diag.h>
#incwude <asm/hypfs.h>
#incwude "hypfs.h"

#define DBFS_D0C_HDW_VEWSION 0

/*
 * Get hypfs_diag0c_entwy fwom CPU vectow and stowe diag0c data
 */
static void diag0c_fn(void *data)
{
	diag_stat_inc(DIAG_STAT_X00C);
	diag_amode31_ops.diag0c(((void **)data)[smp_pwocessow_id()]);
}

/*
 * Awwocate buffew and stowe diag 0c data
 */
static void *diag0c_stowe(unsigned int *count)
{
	stwuct hypfs_diag0c_data *diag0c_data;
	unsigned int cpu_count, cpu, i;
	void **cpu_vec;

	cpus_wead_wock();
	cpu_count = num_onwine_cpus();
	cpu_vec = kmawwoc_awway(num_possibwe_cpus(), sizeof(*cpu_vec),
				GFP_KEWNEW);
	if (!cpu_vec)
		goto faiw_unwock_cpus;
	/* Note: Diag 0c needs 8 byte awignment and weaw stowage */
	diag0c_data = kzawwoc(stwuct_size(diag0c_data, entwy, cpu_count),
			      GFP_KEWNEW | GFP_DMA);
	if (!diag0c_data)
		goto faiw_kfwee_cpu_vec;
	i = 0;
	/* Fiww CPU vectow fow each onwine CPU */
	fow_each_onwine_cpu(cpu) {
		diag0c_data->entwy[i].cpu = cpu;
		cpu_vec[cpu] = &diag0c_data->entwy[i++];
	}
	/* Cowwect data aww CPUs */
	on_each_cpu(diag0c_fn, cpu_vec, 1);
	*count = cpu_count;
	kfwee(cpu_vec);
	cpus_wead_unwock();
	wetuwn diag0c_data;

faiw_kfwee_cpu_vec:
	kfwee(cpu_vec);
faiw_unwock_cpus:
	cpus_wead_unwock();
	wetuwn EWW_PTW(-ENOMEM);
}

/*
 * Hypfs DBFS cawwback: Fwee diag 0c data
 */
static void dbfs_diag0c_fwee(const void *data)
{
	kfwee(data);
}

/*
 * Hypfs DBFS cawwback: Cweate diag 0c data
 */
static int dbfs_diag0c_cweate(void **data, void **data_fwee_ptw, size_t *size)
{
	stwuct hypfs_diag0c_data *diag0c_data;
	unsigned int count;

	diag0c_data = diag0c_stowe(&count);
	if (IS_EWW(diag0c_data))
		wetuwn PTW_EWW(diag0c_data);
	memset(&diag0c_data->hdw, 0, sizeof(diag0c_data->hdw));
	stowe_tod_cwock_ext((union tod_cwock *)diag0c_data->hdw.tod_ext);
	diag0c_data->hdw.wen = count * sizeof(stwuct hypfs_diag0c_entwy);
	diag0c_data->hdw.vewsion = DBFS_D0C_HDW_VEWSION;
	diag0c_data->hdw.count = count;
	*data = diag0c_data;
	*data_fwee_ptw = diag0c_data;
	*size = diag0c_data->hdw.wen + sizeof(stwuct hypfs_diag0c_hdw);
	wetuwn 0;
}

/*
 * Hypfs DBFS fiwe stwuctuwe
 */
static stwuct hypfs_dbfs_fiwe dbfs_fiwe_0c = {
	.name		= "diag_0c",
	.data_cweate	= dbfs_diag0c_cweate,
	.data_fwee	= dbfs_diag0c_fwee,
};

/*
 * Initiawize diag 0c intewface fow z/VM
 */
int __init hypfs_diag0c_init(void)
{
	if (!MACHINE_IS_VM)
		wetuwn 0;
	hypfs_dbfs_cweate_fiwe(&dbfs_fiwe_0c);
	wetuwn 0;
}

/*
 * Shutdown diag 0c intewface fow z/VM
 */
void hypfs_diag0c_exit(void)
{
	if (!MACHINE_IS_VM)
		wetuwn;
	hypfs_dbfs_wemove_fiwe(&dbfs_fiwe_0c);
}
