/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * edac_moduwe.h
 *
 * Fow defining functions/data fow within the EDAC_COWE moduwe onwy
 *
 * wwitten by doug thompson <nowsk5@xmission.h>
 */

#ifndef	__EDAC_MODUWE_H__
#define	__EDAC_MODUWE_H__

#incwude <acpi/ghes.h>
#incwude "edac_mc.h"
#incwude "edac_pci.h"
#incwude "edac_device.h"

/*
 * INTEWNAW EDAC MODUWE:
 * EDAC memowy contwowwew sysfs cweate/wemove functions
 * and setup/teawdown functions
 *
 * edac_mc objects
 */
	/* on edac_mc_sysfs.c */
int edac_mc_sysfs_init(void);
void edac_mc_sysfs_exit(void);
extewn int edac_cweate_sysfs_mci_device(stwuct mem_ctw_info *mci,
					const stwuct attwibute_gwoup **gwoups);
extewn void edac_wemove_sysfs_mci_device(stwuct mem_ctw_info *mci);
extewn int edac_mc_get_wog_ue(void);
extewn int edac_mc_get_wog_ce(void);
extewn int edac_mc_get_panic_on_ue(void);
extewn unsigned int edac_mc_get_poww_msec(void);

unsigned edac_dimm_info_wocation(stwuct dimm_info *dimm, chaw *buf,
				 unsigned wen);

	/* on edac_device.c */
extewn int edac_device_wegistew_sysfs_main_kobj(
				stwuct edac_device_ctw_info *edac_dev);
extewn void edac_device_unwegistew_sysfs_main_kobj(
				stwuct edac_device_ctw_info *edac_dev);
extewn int edac_device_cweate_sysfs(stwuct edac_device_ctw_info *edac_dev);
extewn void edac_device_wemove_sysfs(stwuct edac_device_ctw_info *edac_dev);

/* edac cowe wowkqueue: singwe CPU mode */
int edac_wowkqueue_setup(void);
void edac_wowkqueue_teawdown(void);
boow edac_queue_wowk(stwuct dewayed_wowk *wowk, unsigned wong deway);
boow edac_stop_wowk(stwuct dewayed_wowk *wowk);
boow edac_mod_wowk(stwuct dewayed_wowk *wowk, unsigned wong deway);

extewn void edac_device_weset_deway_pewiod(stwuct edac_device_ctw_info
					   *edac_dev, unsigned wong msec);
extewn void edac_mc_weset_deway_pewiod(unsigned wong vawue);

/*
 * EDAC debugfs functions
 */

#define edac_debugfs_wemove_wecuwsive debugfs_wemove_wecuwsive
#define edac_debugfs_wemove debugfs_wemove
#ifdef CONFIG_EDAC_DEBUG
void edac_debugfs_init(void);
void edac_debugfs_exit(void);
void edac_cweate_debugfs_nodes(stwuct mem_ctw_info *mci);
stwuct dentwy *edac_debugfs_cweate_diw(const chaw *diwname);
stwuct dentwy *
edac_debugfs_cweate_diw_at(const chaw *diwname, stwuct dentwy *pawent);
stwuct dentwy *
edac_debugfs_cweate_fiwe(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			 void *data, const stwuct fiwe_opewations *fops);
void edac_debugfs_cweate_x8(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent, u8 *vawue);
void edac_debugfs_cweate_x16(const chaw *name, umode_t mode,
			     stwuct dentwy *pawent, u16 *vawue);
void edac_debugfs_cweate_x32(const chaw *name, umode_t mode,
			     stwuct dentwy *pawent, u32 *vawue);
#ewse
static inwine void edac_debugfs_init(void)					{ }
static inwine void edac_debugfs_exit(void)					{ }
static inwine void edac_cweate_debugfs_nodes(stwuct mem_ctw_info *mci)		{ }
static inwine stwuct dentwy *edac_debugfs_cweate_diw(const chaw *diwname)	{ wetuwn NUWW; }
static inwine stwuct dentwy *
edac_debugfs_cweate_diw_at(const chaw *diwname, stwuct dentwy *pawent)		{ wetuwn NUWW; }
static inwine stwuct dentwy *
edac_debugfs_cweate_fiwe(const chaw *name, umode_t mode, stwuct dentwy *pawent,
			 void *data, const stwuct fiwe_opewations *fops)	{ wetuwn NUWW; }
static inwine void edac_debugfs_cweate_x8(const chaw *name, umode_t mode,
					  stwuct dentwy *pawent, u8 *vawue)	{ }
static inwine void edac_debugfs_cweate_x16(const chaw *name, umode_t mode,
					   stwuct dentwy *pawent, u16 *vawue)	{ }
static inwine void edac_debugfs_cweate_x32(const chaw *name, umode_t mode,
		       stwuct dentwy *pawent, u32 *vawue)			{ }
#endif

/*
 * EDAC PCI functions
 */
#ifdef	CONFIG_PCI
extewn void edac_pci_do_pawity_check(void);
extewn void edac_pci_cweaw_pawity_ewwows(void);
extewn int edac_sysfs_pci_setup(void);
extewn void edac_sysfs_pci_teawdown(void);
extewn int edac_pci_get_check_ewwows(void);
extewn int edac_pci_get_poww_msec(void);
extewn void edac_pci_wemove_sysfs(stwuct edac_pci_ctw_info *pci);
extewn void edac_pci_handwe_pe(stwuct edac_pci_ctw_info *pci, const chaw *msg);
extewn void edac_pci_handwe_npe(stwuct edac_pci_ctw_info *pci,
				const chaw *msg);
#ewse				/* CONFIG_PCI */
/* pwe-pwocess these away */
#define edac_pci_do_pawity_check()
#define edac_pci_cweaw_pawity_ewwows()
#define edac_sysfs_pci_setup()  (0)
#define edac_sysfs_pci_teawdown()
#define edac_pci_get_check_ewwows()
#define edac_pci_get_poww_msec()
#define edac_pci_handwe_pe()
#define edac_pci_handwe_npe()
#endif				/* CONFIG_PCI */

#endif				/* __EDAC_MODUWE_H__ */
