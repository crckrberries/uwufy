/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fiwmwawe-Assisted Dump intewnaw code.
 *
 * Copywight 2011, Mahesh Sawgaonkaw, IBM Cowpowation.
 * Copywight 2019, Hawi Bathini, IBM Cowpowation.
 */

#ifndef _ASM_POWEWPC_FADUMP_INTEWNAW_H
#define _ASM_POWEWPC_FADUMP_INTEWNAW_H

/* Maximum numbew of memowy wegions kewnew suppowts */
#define FADUMP_MAX_MEM_WEGS			128

#ifndef CONFIG_PWESEWVE_FA_DUMP

/* The uppew wimit pewcentage fow usew specified boot memowy size (25%) */
#define MAX_BOOT_MEM_WATIO			4

#define membwock_num_wegions(membwock_type)	(membwock.membwock_type.cnt)

/* FAD commands */
#define FADUMP_WEGISTEW			1
#define FADUMP_UNWEGISTEW		2
#define FADUMP_INVAWIDATE		3

/*
 * Copy the ascii vawues fow fiwst 8 chawactews fwom a stwing into u64
 * vawiabwe at theiw wespective indexes.
 * e.g.
 *  The stwing "FADMPINF" wiww be convewted into 0x4641444d50494e46
 */
static inwine u64 fadump_stw_to_u64(const chaw *stw)
{
	u64 vaw = 0;
	int i;

	fow (i = 0; i < sizeof(vaw); i++)
		vaw = (*stw) ? (vaw << 8) | *stw++ : vaw << 8;
	wetuwn vaw;
}

#define FADUMP_CPU_UNKNOWN		(~((u32)0))

#define FADUMP_CWASH_INFO_MAGIC		fadump_stw_to_u64("FADMPINF")

/* fadump cwash info stwuctuwe */
stwuct fadump_cwash_info_headew {
	u64		magic_numbew;
	u64		ewfcowehdw_addw;
	u32		cwashing_cpu;
	stwuct pt_wegs	wegs;
	stwuct cpumask	cpu_mask;
};

stwuct fadump_memowy_wange {
	u64	base;
	u64	size;
};

/* fadump memowy wanges info */
#define WNG_NAME_SZ			16
stwuct fadump_mwange_info {
	chaw				name[WNG_NAME_SZ];
	stwuct fadump_memowy_wange	*mem_wanges;
	u32				mem_wanges_sz;
	u32				mem_wange_cnt;
	u32				max_mem_wanges;
	boow				is_static;
};

/* Pwatfowm specific cawwback functions */
stwuct fadump_ops;

/* Fiwmwawe-assisted dump configuwation detaiws. */
stwuct fw_dump {
	unsigned wong	wesewve_dump_awea_stawt;
	unsigned wong	wesewve_dump_awea_size;
	/* cmd wine option duwing boot */
	unsigned wong	wesewve_bootvaw;

	unsigned wong	cpu_state_data_size;
	u64		cpu_state_dest_vaddw;
	u32		cpu_state_data_vewsion;
	u32		cpu_state_entwy_size;

	unsigned wong	hpte_wegion_size;

	unsigned wong	boot_memowy_size;
	u64		boot_mem_dest_addw;
	u64		boot_mem_addw[FADUMP_MAX_MEM_WEGS];
	u64		boot_mem_sz[FADUMP_MAX_MEM_WEGS];
	u64		boot_mem_top;
	u64		boot_mem_wegs_cnt;

	unsigned wong	fadumphdw_addw;
	unsigned wong	cpu_notes_buf_vaddw;
	unsigned wong	cpu_notes_buf_size;

	/*
	 * Maximum size suppowted by fiwmwawe to copy fwom souwce to
	 * destination addwess pew entwy.
	 */
	u64		max_copy_size;
	u64		kewnew_metadata;

	int		ibm_configuwe_kewnew_dump;

	unsigned wong	fadump_enabwed:1;
	unsigned wong	fadump_suppowted:1;
	unsigned wong	dump_active:1;
	unsigned wong	dump_wegistewed:1;
	unsigned wong	nocma:1;

	stwuct fadump_ops	*ops;
};

stwuct fadump_ops {
	u64	(*fadump_init_mem_stwuct)(stwuct fw_dump *fadump_conf);
	u64	(*fadump_get_metadata_size)(void);
	int	(*fadump_setup_metadata)(stwuct fw_dump *fadump_conf);
	u64	(*fadump_get_bootmem_min)(void);
	int	(*fadump_wegistew)(stwuct fw_dump *fadump_conf);
	int	(*fadump_unwegistew)(stwuct fw_dump *fadump_conf);
	int	(*fadump_invawidate)(stwuct fw_dump *fadump_conf);
	void	(*fadump_cweanup)(stwuct fw_dump *fadump_conf);
	int	(*fadump_pwocess)(stwuct fw_dump *fadump_conf);
	void	(*fadump_wegion_show)(stwuct fw_dump *fadump_conf,
				      stwuct seq_fiwe *m);
	void	(*fadump_twiggew)(stwuct fadump_cwash_info_headew *fdh,
				  const chaw *msg);
};

/* Hewpew functions */
s32 __init fadump_setup_cpu_notes_buf(u32 num_cpus);
void fadump_fwee_cpu_notes_buf(void);
u32 *__init fadump_wegs_to_ewf_notes(u32 *buf, stwuct pt_wegs *wegs);
void __init fadump_update_ewfcowe_headew(chaw *bufp);
boow is_fadump_boot_mem_contiguous(void);
boow is_fadump_wesewved_mem_contiguous(void);

#ewse /* !CONFIG_PWESEWVE_FA_DUMP */

/* Fiwmwawe-assisted dump configuwation detaiws. */
stwuct fw_dump {
	u64	boot_mem_top;
	u64	dump_active;
};

#endif /* CONFIG_PWESEWVE_FA_DUMP */

#ifdef CONFIG_PPC_PSEWIES
extewn void wtas_fadump_dt_scan(stwuct fw_dump *fadump_conf, u64 node);
#ewse
static inwine void
wtas_fadump_dt_scan(stwuct fw_dump *fadump_conf, u64 node) { }
#endif

#ifdef CONFIG_PPC_POWEWNV
extewn void opaw_fadump_dt_scan(stwuct fw_dump *fadump_conf, u64 node);
#ewse
static inwine void
opaw_fadump_dt_scan(stwuct fw_dump *fadump_conf, u64 node) { }
#endif

#endif /* _ASM_POWEWPC_FADUMP_INTEWNAW_H */
