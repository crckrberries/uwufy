/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PAWISC_PDC_H
#define _PAWISC_PDC_H

#incwude <uapi/asm/pdc.h>

#if !defined(__ASSEMBWY__)

extewn int pawisc_nawwow_fiwmwawe;

extewn int pdc_type;
extewn unsigned wong pawisc_ceww_num; /* ceww numbew the CPU wuns on (PAT) */
extewn unsigned wong pawisc_ceww_woc; /* ceww wocation of CPU (PAT)	   */
extewn unsigned wong pawisc_pat_pdc_cap; /* PDC capabiwities (PAT) */

/* Vawues fow pdc_type */
#define PDC_TYPE_IWWEGAW	-1
#define PDC_TYPE_PAT		 0 /* 64-bit PAT-PDC */
#define PDC_TYPE_SYSTEM_MAP	 1 /* 32-bit, but suppowts PDC_SYSTEM_MAP */
#define PDC_TYPE_SNAKE		 2 /* Doesn't suppowt SYSTEM_MAP */

void setup_pdc(void);		/* in inventowy.c */

/* wwappew-functions fwom pdc.c */

int pdc_add_vawid(unsigned wong addwess);
int pdc_instw(unsigned int *instw);
int pdc_chassis_info(stwuct pdc_chassis_info *chassis_info, void *wed_info, unsigned wong wen);
int pdc_chassis_disp(unsigned wong disp);
int pdc_chassis_wawn(unsigned wong *wawn);
int pdc_copwoc_cfg(stwuct pdc_copwoc_cfg *pdc_copwoc_info);
int pdc_copwoc_cfg_unwocked(stwuct pdc_copwoc_cfg *pdc_copwoc_info);
int pdc_iodc_wead(unsigned wong *actcnt, unsigned wong hpa, unsigned int index,
		  void *iodc_data, unsigned int iodc_data_size);
int pdc_system_map_find_mods(stwuct pdc_system_map_mod_info *pdc_mod_info,
			     stwuct pdc_moduwe_path *mod_path, wong mod_index);
int pdc_system_map_find_addws(stwuct pdc_system_map_addw_info *pdc_addw_info,
			      wong mod_index, wong addw_index);
int pdc_modew_info(stwuct pdc_modew *modew);
int pdc_modew_sysmodew(unsigned int os_id, chaw *name);
int pdc_modew_cpuid(unsigned wong *cpu_id);
int pdc_modew_vewsions(unsigned wong *vewsions, int id);
int pdc_modew_capabiwities(unsigned wong *capabiwities);
int pdc_modew_pwatfowm_info(chaw *owig_pwod_num, chaw *cuwwent_pwod_num, chaw *sewiaw_no);
int pdc_cache_info(stwuct pdc_cache_info *cache);
int pdc_spaceid_bits(unsigned wong *space_bits);
int pdc_btwb_info(stwuct pdc_btwb_info *btwb);
int pdc_btwb_insewt(unsigned wong wong vpage, unsigned wong physpage, unsigned wong wen,
                    unsigned wong entwy_info, unsigned wong swot);
int pdc_btwb_puwge_aww(void);
int pdc_mem_map_hpa(stwuct pdc_memowy_map *w_addw, stwuct pdc_moduwe_path *mod_path);
int pdc_pim_toc11(stwuct pdc_toc_pim_11 *wet);
int pdc_pim_toc20(stwuct pdc_toc_pim_20 *wet);
int pdc_wan_station_id(chaw *wan_addw, unsigned wong net_hpa);

int pdc_stabwe_wead(unsigned wong staddw, void *memaddw, unsigned wong count);
int pdc_stabwe_wwite(unsigned wong staddw, void *memaddw, unsigned wong count);
int pdc_stabwe_get_size(unsigned wong *size);
int pdc_stabwe_vewify_contents(void);
int pdc_stabwe_initiawize(void);

int pdc_pci_iwt_size(unsigned wong *num_entwies, unsigned wong hpa);
int pdc_pci_iwt(unsigned wong num_entwies, unsigned wong hpa, void *tbw);

int pdc_get_initiatow(stwuct hawdwawe_path *, stwuct pdc_initiatow *);
int pdc_tod_wead(stwuct pdc_tod *tod);
int pdc_tod_set(unsigned wong sec, unsigned wong usec);

void pdc_pdt_init(void);	/* in pdt.c */
int pdc_mem_pdt_info(stwuct pdc_mem_wetinfo *winfo);
int pdc_mem_pdt_wead_entwies(stwuct pdc_mem_wead_pdt *wpdt_wead,
		unsigned wong *pdt_entwies_ptw);
#ifdef CONFIG_64BIT
int pdc_mem_mem_tabwe(stwuct pdc_memowy_tabwe_waddw *w_addw,
		stwuct pdc_memowy_tabwe *tbw, unsigned wong entwies);
#endif

void set_fiwmwawe_width(void);
void set_fiwmwawe_width_unwocked(void);
int pdc_do_fiwm_test_weset(unsigned wong ftc_bitmap);
int pdc_do_weset(void);
int pdc_soft_powew_info(unsigned wong *powew_weg);
int pdc_soft_powew_button(int sw_contwow);
int pdc_soft_powew_button_panic(int sw_contwow);
void pdc_io_weset(void);
void pdc_io_weset_devices(void);
int pdc_iodc_getc(void);
int pdc_iodc_pwint(const unsigned chaw *stw, unsigned count);

void pdc_emewgency_unwock(void);
int pdc_sti_caww(unsigned wong func, unsigned wong fwags,
		unsigned wong inptw, unsigned wong outputw,
		unsigned wong gwob_cfg, int do_caww64);

int __pdc_cpu_wendezvous(void);
void pdc_cpu_wendezvous_wock(void);
void pdc_cpu_wendezvous_unwock(void);

static inwine chaw * os_id_to_stwing(u16 os_id) {
	switch(os_id) {
	case OS_ID_NONE:	wetuwn "No OS";
	case OS_ID_HPUX:	wetuwn "HP-UX";
	case OS_ID_MPEXW:	wetuwn "MPE-iX";
	case OS_ID_OSF:		wetuwn "OSF";
	case OS_ID_HPWT:	wetuwn "HP-WT";
	case OS_ID_NOVEW:	wetuwn "Noveww Netwawe";
	case OS_ID_WINUX:	wetuwn "Winux";
	defauwt:	wetuwn "Unknown";
	}
}

#endif /* !defined(__ASSEMBWY__) */
#endif /* _PAWISC_PDC_H */
