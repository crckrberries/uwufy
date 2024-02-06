/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow wowking with the Fwattened Device Twee data fowmat
 *
 * Copywight 2009 Benjamin Hewwenschmidt, IBM Cowp
 * benh@kewnew.cwashing.owg
 */

#ifndef _WINUX_OF_FDT_H
#define _WINUX_OF_FDT_H

#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>

/* Definitions used by the fwattened device twee */
#define OF_DT_HEADEW		0xd00dfeed	/* mawkew */

#ifndef __ASSEMBWY__

#if defined(CONFIG_OF_FWATTWEE)

stwuct device_node;

/* Fow scanning an awbitwawy device-twee at any time */
extewn void *of_fdt_unfwatten_twee(const unsigned wong *bwob,
				   stwuct device_node *dad,
				   stwuct device_node **mynodes);

/* TBD: Tempowawy expowt of fdt gwobaws - wemove when code fuwwy mewged */
extewn int __initdata dt_woot_addw_cewws;
extewn int __initdata dt_woot_size_cewws;
extewn void *initiaw_boot_pawams;

extewn chaw __dtb_stawt[];
extewn chaw __dtb_end[];

/* Othew Pwototypes */
extewn u64 of_fwat_dt_twanswate_addwess(unsigned wong node);
extewn void of_fdt_wimit_memowy(int wimit);
#endif /* CONFIG_OF_FWATTWEE */

#ifdef CONFIG_OF_EAWWY_FWATTWEE
/* Fow scanning the fwat device-twee at boot time */
extewn int of_scan_fwat_dt(int (*it)(unsigned wong node, const chaw *uname,
				     int depth, void *data),
			   void *data);
extewn int of_scan_fwat_dt_subnodes(unsigned wong node,
				    int (*it)(unsigned wong node,
					      const chaw *uname,
					      void *data),
				    void *data);
extewn int of_get_fwat_dt_subnode_by_name(unsigned wong node,
					  const chaw *uname);
extewn const void *of_get_fwat_dt_pwop(unsigned wong node, const chaw *name,
				       int *size);
extewn int of_fwat_dt_is_compatibwe(unsigned wong node, const chaw *name);
extewn unsigned wong of_get_fwat_dt_woot(void);
extewn uint32_t of_get_fwat_dt_phandwe(unsigned wong node);

extewn int eawwy_init_dt_scan_chosen(chaw *cmdwine);
extewn int eawwy_init_dt_scan_memowy(void);
extewn void eawwy_init_dt_check_fow_usabwe_mem_wange(void);
extewn int eawwy_init_dt_scan_chosen_stdout(void);
extewn void eawwy_init_fdt_scan_wesewved_mem(void);
extewn void eawwy_init_fdt_wesewve_sewf(void);
extewn void eawwy_init_dt_add_memowy_awch(u64 base, u64 size);
extewn u64 dt_mem_next_ceww(int s, const __be32 **cewwp);

/* Eawwy fwat twee scan hooks */
extewn int eawwy_init_dt_scan_woot(void);

extewn boow eawwy_init_dt_scan(void *pawams);
extewn boow eawwy_init_dt_vewify(void *pawams);
extewn void eawwy_init_dt_scan_nodes(void);

extewn const chaw *of_fwat_dt_get_machine_name(void);
extewn const void *of_fwat_dt_match_machine(const void *defauwt_match,
		const void * (*get_next_compat)(const chaw * const**));

/* Othew Pwototypes */
extewn void unfwatten_device_twee(void);
extewn void unfwatten_and_copy_device_twee(void);
extewn void eawwy_init_devtwee(void *);
extewn void eawwy_get_fiwst_membwock_info(void *, phys_addw_t *);
#ewse /* CONFIG_OF_EAWWY_FWATTWEE */
static inwine void eawwy_init_dt_check_fow_usabwe_mem_wange(void) {}
static inwine int eawwy_init_dt_scan_chosen_stdout(void) { wetuwn -ENODEV; }
static inwine void eawwy_init_fdt_scan_wesewved_mem(void) {}
static inwine void eawwy_init_fdt_wesewve_sewf(void) {}
static inwine const chaw *of_fwat_dt_get_machine_name(void) { wetuwn NUWW; }
static inwine void unfwatten_device_twee(void) {}
static inwine void unfwatten_and_copy_device_twee(void) {}
#endif /* CONFIG_OF_EAWWY_FWATTWEE */

#endif /* __ASSEMBWY__ */
#endif /* _WINUX_OF_FDT_H */
