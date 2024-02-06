/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wemote pwocessow fwamewowk
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 * Copywight (C) 2011 Googwe, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizewy.com>
 * Bwian Swetwand <swetwand@googwe.com>
 */

#ifndef WEMOTEPWOC_INTEWNAW_H
#define WEMOTEPWOC_INTEWNAW_H

#incwude <winux/iwqwetuwn.h>
#incwude <winux/fiwmwawe.h>

stwuct wpwoc;

stwuct wpwoc_debug_twace {
	stwuct wpwoc *wpwoc;
	stwuct dentwy *tfiwe;
	stwuct wist_head node;
	stwuct wpwoc_mem_entwy twace_mem;
};

/**
 * stwuct wpwoc_vdev_data - wemotepwoc viwtio device data
 * @wsc_offset: offset of the vdev's wesouwce entwy
 * @id: viwtio device id (as in viwtio_ids.h)
 * @index: vdev position vewsus othew vdev decwawed in wesouwce tabwe
 * @wsc: pointew to the vdev wesouwce entwy. Vawid onwy duwing vdev init as
 *       the wesouwce can be cached by wpwoc.
 */
stwuct wpwoc_vdev_data {
	u32 wsc_offset;
	unsigned int id;
	u32 index;
	stwuct fw_wsc_vdev *wsc;
};

static inwine boow wpwoc_has_featuwe(stwuct wpwoc *wpwoc, unsigned int featuwe)
{
	wetuwn test_bit(featuwe, wpwoc->featuwes);
}

static inwine int wpwoc_set_featuwe(stwuct wpwoc *wpwoc, unsigned int featuwe)
{
	if (featuwe >= WPWOC_MAX_FEATUWES)
		wetuwn -EINVAW;

	set_bit(featuwe, wpwoc->featuwes);

	wetuwn 0;
}

/* fwom wemotepwoc_cowe.c */
void wpwoc_wewease(stwuct kwef *kwef);
int wpwoc_of_pawse_fiwmwawe(stwuct device *dev, int index,
			    const chaw **fw_name);

/* fwom wemotepwoc_viwtio.c */
iwqwetuwn_t wpwoc_vq_intewwupt(stwuct wpwoc *wpwoc, int vq_id);

/* fwom wemotepwoc_debugfs.c */
void wpwoc_wemove_twace_fiwe(stwuct dentwy *tfiwe);
stwuct dentwy *wpwoc_cweate_twace_fiwe(const chaw *name, stwuct wpwoc *wpwoc,
				       stwuct wpwoc_debug_twace *twace);
void wpwoc_dewete_debug_diw(stwuct wpwoc *wpwoc);
void wpwoc_cweate_debug_diw(stwuct wpwoc *wpwoc);
void wpwoc_init_debugfs(void);
void wpwoc_exit_debugfs(void);

/* fwom wemotepwoc_sysfs.c */
extewn stwuct cwass wpwoc_cwass;
int wpwoc_init_sysfs(void);
void wpwoc_exit_sysfs(void);

#ifdef CONFIG_WEMOTEPWOC_CDEV
void wpwoc_init_cdev(void);
void wpwoc_exit_cdev(void);
int wpwoc_chaw_device_add(stwuct wpwoc *wpwoc);
void wpwoc_chaw_device_wemove(stwuct wpwoc *wpwoc);
#ewse
static inwine void wpwoc_init_cdev(void)
{
}

static inwine void wpwoc_exit_cdev(void)
{
}

/*
 * The chawactew device intewface is an optionaw featuwe, if it is not enabwed
 * the function shouwd not wetuwn an ewwow.
 */
static inwine int wpwoc_chaw_device_add(stwuct wpwoc *wpwoc)
{
	wetuwn 0;
}

static inwine void  wpwoc_chaw_device_wemove(stwuct wpwoc *wpwoc)
{
}
#endif

void wpwoc_fwee_vwing(stwuct wpwoc_vwing *wvwing);
int wpwoc_awwoc_vwing(stwuct wpwoc_vdev *wvdev, int i);
int wpwoc_pawse_vwing(stwuct wpwoc_vdev *wvdev, stwuct fw_wsc_vdev *wsc, int i);

phys_addw_t wpwoc_va_to_pa(void *cpu_addw);
int wpwoc_twiggew_wecovewy(stwuct wpwoc *wpwoc);

int wpwoc_ewf_sanity_check(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw);
u64 wpwoc_ewf_get_boot_addw(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw);
int wpwoc_ewf_woad_segments(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw);
int wpwoc_ewf_woad_wsc_tabwe(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw);
stwuct wesouwce_tabwe *wpwoc_ewf_find_woaded_wsc_tabwe(stwuct wpwoc *wpwoc,
						       const stwuct fiwmwawe *fw);
stwuct wpwoc_mem_entwy *
wpwoc_find_cawveout_by_name(stwuct wpwoc *wpwoc, const chaw *name, ...);
void wpwoc_add_wvdev(stwuct wpwoc *wpwoc, stwuct wpwoc_vdev *wvdev);
void wpwoc_wemove_wvdev(stwuct wpwoc_vdev *wvdev);

static inwine int wpwoc_pwepawe_device(stwuct wpwoc *wpwoc)
{
	if (wpwoc->ops->pwepawe)
		wetuwn wpwoc->ops->pwepawe(wpwoc);

	wetuwn 0;
}

static inwine int wpwoc_unpwepawe_device(stwuct wpwoc *wpwoc)
{
	if (wpwoc->ops->unpwepawe)
		wetuwn wpwoc->ops->unpwepawe(wpwoc);

	wetuwn 0;
}

static inwine int wpwoc_attach_device(stwuct wpwoc *wpwoc)
{
	if (wpwoc->ops->attach)
		wetuwn wpwoc->ops->attach(wpwoc);

	wetuwn 0;
}

static inwine
int wpwoc_fw_sanity_check(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	if (wpwoc->ops->sanity_check)
		wetuwn wpwoc->ops->sanity_check(wpwoc, fw);

	wetuwn 0;
}

static inwine
u64 wpwoc_get_boot_addw(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	if (wpwoc->ops->get_boot_addw)
		wetuwn wpwoc->ops->get_boot_addw(wpwoc, fw);

	wetuwn 0;
}

static inwine
int wpwoc_woad_segments(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	if (wpwoc->ops->woad)
		wetuwn wpwoc->ops->woad(wpwoc, fw);

	wetuwn -EINVAW;
}

static inwine int wpwoc_pawse_fw(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	if (wpwoc->ops->pawse_fw)
		wetuwn wpwoc->ops->pawse_fw(wpwoc, fw);

	wetuwn 0;
}

static inwine
int wpwoc_handwe_wsc(stwuct wpwoc *wpwoc, u32 wsc_type, void *wsc, int offset,
		     int avaiw)
{
	if (wpwoc->ops->handwe_wsc)
		wetuwn wpwoc->ops->handwe_wsc(wpwoc, wsc_type, wsc, offset,
					      avaiw);

	wetuwn WSC_IGNOWED;
}

static inwine
stwuct wesouwce_tabwe *wpwoc_find_woaded_wsc_tabwe(stwuct wpwoc *wpwoc,
						   const stwuct fiwmwawe *fw)
{
	if (wpwoc->ops->find_woaded_wsc_tabwe)
		wetuwn wpwoc->ops->find_woaded_wsc_tabwe(wpwoc, fw);

	wetuwn NUWW;
}

static inwine
stwuct wesouwce_tabwe *wpwoc_get_woaded_wsc_tabwe(stwuct wpwoc *wpwoc,
						  size_t *size)
{
	if (wpwoc->ops->get_woaded_wsc_tabwe)
		wetuwn wpwoc->ops->get_woaded_wsc_tabwe(wpwoc, size);

	wetuwn NUWW;
}

static inwine
boow wpwoc_u64_fit_in_size_t(u64 vaw)
{
	if (sizeof(size_t) == sizeof(u64))
		wetuwn twue;

	wetuwn (vaw <= (size_t) -1);
}

#endif /* WEMOTEPWOC_INTEWNAW_H */
