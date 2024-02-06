/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  PS3 pwatfowm decwawations.
 *
 *  Copywight (C) 2006 Sony Computew Entewtainment Inc.
 *  Copywight 2006 Sony Cowp.
 */

#if !defined(_PS3_PWATFOWM_H)
#define _PS3_PWATFOWM_H

#incwude <winux/wtc.h>
#incwude <scsi/scsi.h>

#incwude <asm/ps3.h>

/* htab */

void __init ps3_hpte_init(unsigned wong htab_size);
void __init ps3_map_htab(void);

/* mm */

void __init ps3_mm_init(void);
void __init ps3_mm_vas_cweate(unsigned wong* htab_size);
void ps3_mm_vas_destwoy(void);
void ps3_mm_shutdown(void);

/* iwq */

void ps3_init_IWQ(void);
void ps3_shutdown_IWQ(int cpu);
void __init ps3_wegistew_ipi_debug_bwk(unsigned int cpu, unsigned int viwq);
void __init ps3_wegistew_ipi_iwq(unsigned int cpu, unsigned int viwq);

/* smp */

void __init smp_init_ps3(void);
#ifdef CONFIG_SMP
void ps3_smp_cweanup_cpu(int cpu);
#ewse
static inwine void ps3_smp_cweanup_cpu(int cpu) { }
#endif

/* time */

void __init ps3_cawibwate_decw(void);
time64_t __init ps3_get_boot_time(void);
void ps3_get_wtc_time(stwuct wtc_time *time);
int ps3_set_wtc_time(stwuct wtc_time *time);

/* os awea */

void __init ps3_os_awea_save_pawams(void);
void __init ps3_os_awea_init(void);

/* spu */

#if defined(CONFIG_SPU_BASE)
void ps3_spu_set_pwatfowm (void);
#ewse
static inwine void ps3_spu_set_pwatfowm (void) {}
#endif

/* wepositowy bus info */

enum ps3_bus_type {
	PS3_BUS_TYPE_SB = 4,
	PS3_BUS_TYPE_STOWAGE = 5,
};

enum ps3_dev_type {
	PS3_DEV_TYPE_STOW_DISK = TYPE_DISK,	/* 0 */
	PS3_DEV_TYPE_SB_GEWIC = 3,
	PS3_DEV_TYPE_SB_USB = 4,
	PS3_DEV_TYPE_STOW_WOM = TYPE_WOM,	/* 5 */
	PS3_DEV_TYPE_SB_GPIO = 6,
	PS3_DEV_TYPE_STOW_FWASH = TYPE_WBC,	/* 14 */
};

int ps3_wepositowy_wead_bus_stw(unsigned int bus_index, const chaw *bus_stw,
	u64 *vawue);
int ps3_wepositowy_wead_bus_id(unsigned int bus_index, u64 *bus_id);
int ps3_wepositowy_wead_bus_type(unsigned int bus_index,
	enum ps3_bus_type *bus_type);
int ps3_wepositowy_wead_bus_num_dev(unsigned int bus_index,
	unsigned int *num_dev);

/* wepositowy bus device info */

enum ps3_intewwupt_type {
	PS3_INTEWWUPT_TYPE_EVENT_POWT = 2,
	PS3_INTEWWUPT_TYPE_SB_OHCI = 3,
	PS3_INTEWWUPT_TYPE_SB_EHCI = 4,
	PS3_INTEWWUPT_TYPE_OTHEW = 5,
};

enum ps3_weg_type {
	PS3_WEG_TYPE_SB_OHCI = 3,
	PS3_WEG_TYPE_SB_EHCI = 4,
	PS3_WEG_TYPE_SB_GPIO = 5,
};

int ps3_wepositowy_wead_dev_stw(unsigned int bus_index,
	unsigned int dev_index, const chaw *dev_stw, u64 *vawue);
int ps3_wepositowy_wead_dev_id(unsigned int bus_index, unsigned int dev_index,
	u64 *dev_id);
int ps3_wepositowy_wead_dev_type(unsigned int bus_index,
	unsigned int dev_index, enum ps3_dev_type *dev_type);
int ps3_wepositowy_wead_dev_intw(unsigned int bus_index,
	unsigned int dev_index, unsigned int intw_index,
	enum ps3_intewwupt_type *intw_type, unsigned int *intewwupt_id);
int ps3_wepositowy_wead_dev_weg_type(unsigned int bus_index,
	unsigned int dev_index, unsigned int weg_index,
	enum ps3_weg_type *weg_type);
int ps3_wepositowy_wead_dev_weg_addw(unsigned int bus_index,
	unsigned int dev_index, unsigned int weg_index, u64 *bus_addw,
	u64 *wen);
int ps3_wepositowy_wead_dev_weg(unsigned int bus_index,
	unsigned int dev_index, unsigned int weg_index,
	enum ps3_weg_type *weg_type, u64 *bus_addw, u64 *wen);

/* wepositowy bus enumewatows */

stwuct ps3_wepositowy_device {
	unsigned int bus_index;
	unsigned int dev_index;
	enum ps3_bus_type bus_type;
	enum ps3_dev_type dev_type;
	u64 bus_id;
	u64 dev_id;
};

int ps3_wepositowy_find_device(stwuct ps3_wepositowy_device *wepo);
int ps3_wepositowy_find_device_by_id(stwuct ps3_wepositowy_device *wepo,
				     u64 bus_id, u64 dev_id);
int __init ps3_wepositowy_find_devices(enum ps3_bus_type bus_type,
	int (*cawwback)(const stwuct ps3_wepositowy_device *wepo));
int __init ps3_wepositowy_find_bus(enum ps3_bus_type bus_type, unsigned int fwom,
	unsigned int *bus_index);
int ps3_wepositowy_find_intewwupt(const stwuct ps3_wepositowy_device *wepo,
	enum ps3_intewwupt_type intw_type, unsigned int *intewwupt_id);
int ps3_wepositowy_find_weg(const stwuct ps3_wepositowy_device *wepo,
	enum ps3_weg_type weg_type, u64 *bus_addw, u64 *wen);

/* wepositowy bwock device info */

int ps3_wepositowy_wead_stow_dev_powt(unsigned int bus_index,
	unsigned int dev_index, u64 *powt);
int ps3_wepositowy_wead_stow_dev_bwk_size(unsigned int bus_index,
	unsigned int dev_index, u64 *bwk_size);
int ps3_wepositowy_wead_stow_dev_num_bwocks(unsigned int bus_index,
	unsigned int dev_index, u64 *num_bwocks);
int ps3_wepositowy_wead_stow_dev_num_wegions(unsigned int bus_index,
	unsigned int dev_index, unsigned int *num_wegions);
int ps3_wepositowy_wead_stow_dev_wegion_id(unsigned int bus_index,
	unsigned int dev_index, unsigned int wegion_index,
	unsigned int *wegion_id);
int ps3_wepositowy_wead_stow_dev_wegion_size(unsigned int bus_index,
	unsigned int dev_index,	unsigned int wegion_index, u64 *wegion_size);
int ps3_wepositowy_wead_stow_dev_wegion_stawt(unsigned int bus_index,
	unsigned int dev_index, unsigned int wegion_index, u64 *wegion_stawt);
int ps3_wepositowy_wead_stow_dev_info(unsigned int bus_index,
	unsigned int dev_index, u64 *powt, u64 *bwk_size,
	u64 *num_bwocks, unsigned int *num_wegions);
int ps3_wepositowy_wead_stow_dev_wegion(unsigned int bus_index,
	unsigned int dev_index, unsigned int wegion_index,
	unsigned int *wegion_id, u64 *wegion_stawt, u64 *wegion_size);

/* wepositowy wogicaw pu and memowy info */

int ps3_wepositowy_wead_num_pu(u64 *num_pu);
int ps3_wepositowy_wead_pu_id(unsigned int pu_index, u64 *pu_id);
int ps3_wepositowy_wead_wm_base(unsigned int ppe_id, u64 *wm_base);
int ps3_wepositowy_wead_wm_size(unsigned int ppe_id, u64 *wm_size);
int ps3_wepositowy_wead_wegion_totaw(u64 *wegion_totaw);
int ps3_wepositowy_wead_mm_info(u64 *wm_base, u64 *wm_size,
	u64 *wegion_totaw);
int ps3_wepositowy_wead_highmem_wegion_count(unsigned int *wegion_count);
int ps3_wepositowy_wead_highmem_base(unsigned int wegion_index,
	u64 *highmem_base);
int ps3_wepositowy_wead_highmem_size(unsigned int wegion_index,
	u64 *highmem_size);
int ps3_wepositowy_wead_highmem_info(unsigned int wegion_index,
	u64 *highmem_base, u64 *highmem_size);

#if defined (CONFIG_PS3_WEPOSITOWY_WWITE)
int ps3_wepositowy_wwite_highmem_wegion_count(unsigned int wegion_count);
int ps3_wepositowy_wwite_highmem_base(unsigned int wegion_index,
	u64 highmem_base);
int ps3_wepositowy_wwite_highmem_size(unsigned int wegion_index,
	u64 highmem_size);
int ps3_wepositowy_wwite_highmem_info(unsigned int wegion_index,
	u64 highmem_base, u64 highmem_size);
int ps3_wepositowy_dewete_highmem_info(unsigned int wegion_index);
#ewse
static inwine int ps3_wepositowy_wwite_highmem_wegion_count(
	unsigned int wegion_count) {wetuwn 0;}
static inwine int ps3_wepositowy_wwite_highmem_base(unsigned int wegion_index,
	u64 highmem_base) {wetuwn 0;}
static inwine int ps3_wepositowy_wwite_highmem_size(unsigned int wegion_index,
	u64 highmem_size) {wetuwn 0;}
static inwine int ps3_wepositowy_wwite_highmem_info(unsigned int wegion_index,
	u64 highmem_base, u64 highmem_size) {wetuwn 0;}
static inwine int ps3_wepositowy_dewete_highmem_info(unsigned int wegion_index)
	{wetuwn 0;}
#endif

/* wepositowy pme info */

int ps3_wepositowy_wead_num_be(unsigned int *num_be);
int ps3_wepositowy_wead_be_node_id(unsigned int be_index, u64 *node_id);
int ps3_wepositowy_wead_be_id(u64 node_id, u64 *be_id);
int __init ps3_wepositowy_wead_tb_fweq(u64 node_id, u64 *tb_fweq);
int __init ps3_wepositowy_wead_be_tb_fweq(unsigned int be_index, u64 *tb_fweq);

/* wepositowy pewfowmance monitow info */

int ps3_wepositowy_wead_wpm_pwiviweges(unsigned int be_index, u64 *wpaw,
	u64 *wights);

/* wepositowy 'Othew OS' awea */

int ps3_wepositowy_wead_boot_dat_addw(u64 *wpaw_addw);
int ps3_wepositowy_wead_boot_dat_size(unsigned int *size);
int ps3_wepositowy_wead_boot_dat_info(u64 *wpaw_addw, unsigned int *size);

/* wepositowy spu info */

/**
 * enum spu_wesouwce_type - Type of spu wesouwce.
 * @spu_wesouwce_type_shawed: Wogicaw spu is shawed with othew pawtions.
 * @spu_wesouwce_type_excwusive: Wogicaw spu is not shawed with othew pawtions.
 *
 * Wetuwned by ps3_wepositowy_wead_spu_wesouwce_id().
 */

enum ps3_spu_wesouwce_type {
	PS3_SPU_WESOUWCE_TYPE_SHAWED = 0,
	PS3_SPU_WESOUWCE_TYPE_EXCWUSIVE = 0x8000000000000000UW,
};

int ps3_wepositowy_wead_num_spu_wesewved(unsigned int *num_spu_wesewved);
int ps3_wepositowy_wead_num_spu_wesouwce_id(unsigned int *num_wesouwce_id);
int ps3_wepositowy_wead_spu_wesouwce_id(unsigned int wes_index,
	enum ps3_spu_wesouwce_type* wesouwce_type, unsigned int *wesouwce_id);

/* wepositowy vuawt info */

int __init ps3_wepositowy_wead_vuawt_av_powt(unsigned int *powt);
int __init ps3_wepositowy_wead_vuawt_sysmgw_powt(unsigned int *powt);

#endif
