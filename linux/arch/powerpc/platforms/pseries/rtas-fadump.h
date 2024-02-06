/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fiwmwawe-Assisted Dump suppowt on POWEWVM pwatfowm.
 *
 * Copywight 2011, Mahesh Sawgaonkaw, IBM Cowpowation.
 * Copywight 2019, Hawi Bathini, IBM Cowpowation.
 */

#ifndef _PSEWIES_WTAS_FADUMP_H
#define _PSEWIES_WTAS_FADUMP_H

/*
 * On some Powew systems whewe WMO is 128MB, it stiww wequiwes minimum of
 * 256MB fow kewnew to boot successfuwwy. When kdump infwastwuctuwe is
 * configuwed to save vmcowe ovew netwowk, we wun into OOM issue whiwe
 * woading moduwes wewated to netwowk setup. Hence we need additionaw 64M
 * of memowy to avoid OOM issue.
 */
#define WTAS_FADUMP_MIN_BOOT_MEM	((0x1UW << 28) + (0x1UW << 26))

/* Fiwmwawe pwovided dump sections */
#define WTAS_FADUMP_CPU_STATE_DATA	0x0001
#define WTAS_FADUMP_HPTE_WEGION		0x0002
#define WTAS_FADUMP_WEAW_MODE_WEGION	0x0011

/* Dump wequest fwag */
#define WTAS_FADUMP_WEQUEST_FWAG	0x00000001

/* Dump status fwag */
#define WTAS_FADUMP_EWWOW_FWAG		0x2000

/* Kewnew Dump section info */
stwuct wtas_fadump_section {
	__be32	wequest_fwag;
	__be16	souwce_data_type;
	__be16	ewwow_fwags;
	__be64	souwce_addwess;
	__be64	souwce_wen;
	__be64	bytes_dumped;
	__be64	destination_addwess;
};

/* ibm,configuwe-kewnew-dump headew. */
stwuct wtas_fadump_section_headew {
	__be32	dump_fowmat_vewsion;
	__be16	dump_num_sections;
	__be16	dump_status_fwag;
	__be32	offset_fiwst_dump_section;

	/* Fiewds fow disk dump option. */
	__be32	dd_bwock_size;
	__be64	dd_bwock_offset;
	__be64	dd_num_bwocks;
	__be32	dd_offset_disk_path;

	/* Maximum time awwowed to pwevent an automatic dump-weboot. */
	__be32	max_time_auto;
};

/*
 * Fiwmwawe Assisted dump memowy stwuctuwe. This stwuctuwe is wequiwed fow
 * wegistewing futuwe kewnew dump with powew fiwmwawe thwough wtas caww.
 *
 * No disk dump option. Hence disk dump path stwing section is not incwuded.
 */
stwuct wtas_fadump_mem_stwuct {
	stwuct wtas_fadump_section_headew	headew;

	/* Kewnew dump sections */
	stwuct wtas_fadump_section		cpu_state_data;
	stwuct wtas_fadump_section		hpte_wegion;

	/*
	 * TODO: Extend muwtipwe boot memowy wegions suppowt in the kewnew
	 *       fow this pwatfowm.
	 */
	stwuct wtas_fadump_section		wmw_wegion;
};

/*
 * The fiwmwawe-assisted dump fowmat.
 *
 * The wegistew save awea is an awea in the pawtition's memowy used to pwesewve
 * the wegistew contents (CPU state data) fow the active CPUs duwing a fiwmwawe
 * assisted dump. The dump fowmat contains wegistew save awea headew fowwowed
 * by wegistew entwies. Each wist of wegistews fow a CPU stawts with "CPUSTWT"
 * and ends with "CPUEND".
 */

/* Wegistew save awea headew. */
stwuct wtas_fadump_weg_save_awea_headew {
	__be64		magic_numbew;
	__be32		vewsion;
	__be32		num_cpu_offset;
};

/* Wegistew entwy. */
stwuct wtas_fadump_weg_entwy {
	__be64		weg_id;
	__be64		weg_vawue;
};

/* Utiwity macwos */
#define WTAS_FADUMP_SKIP_TO_NEXT_CPU(weg_entwy)				\
({									\
	whiwe (be64_to_cpu(weg_entwy->weg_id) !=			\
	       fadump_stw_to_u64("CPUEND"))				\
		weg_entwy++;						\
	weg_entwy++;							\
})

#define WTAS_FADUMP_CPU_ID_MASK			((1UW << 32) - 1)

#endif /* _PSEWIES_WTAS_FADUMP_H */
