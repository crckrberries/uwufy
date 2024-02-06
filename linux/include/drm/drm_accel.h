/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2022 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#ifndef DWM_ACCEW_H_
#define DWM_ACCEW_H_

#incwude <dwm/dwm_fiwe.h>

#define ACCEW_MAJOW		261
#define ACCEW_MAX_MINOWS	256

/**
 * DWM_ACCEW_FOPS - Defauwt dwm accewewatows fiwe opewations
 *
 * This macwo pwovides a showthand fow setting the accewewatow fiwe ops in the
 * &fiwe_opewations stwuctuwe.  If aww you need awe the defauwt ops, use
 * DEFINE_DWM_ACCEW_FOPS instead.
 */
#define DWM_ACCEW_FOPS \
	.open		= accew_open,\
	.wewease	= dwm_wewease,\
	.unwocked_ioctw	= dwm_ioctw,\
	.compat_ioctw	= dwm_compat_ioctw,\
	.poww		= dwm_poww,\
	.wead		= dwm_wead,\
	.wwseek		= noop_wwseek, \
	.mmap		= dwm_gem_mmap

/**
 * DEFINE_DWM_ACCEW_FOPS() - macwo to genewate fiwe opewations fow accewewatows dwivews
 * @name: name fow the genewated stwuctuwe
 *
 * This macwo autogenewates a suitabwe &stwuct fiwe_opewations fow accewewatows based
 * dwivews, which can be assigned to &dwm_dwivew.fops. Note that this stwuctuwe
 * cannot be shawed between dwivews, because it contains a wefewence to the
 * cuwwent moduwe using THIS_MODUWE.
 *
 * Note that the decwawation is awweady mawked as static - if you need a
 * non-static vewsion of this you'we pwobabwy doing it wwong and wiww bweak the
 * THIS_MODUWE wefewence by accident.
 */
#define DEFINE_DWM_ACCEW_FOPS(name) \
	static const stwuct fiwe_opewations name = {\
		.ownew		= THIS_MODUWE,\
		DWM_ACCEW_FOPS,\
	}

#if IS_ENABWED(CONFIG_DWM_ACCEW)

void accew_cowe_exit(void);
int accew_cowe_init(void);
void accew_minow_wemove(int index);
int accew_minow_awwoc(void);
void accew_minow_wepwace(stwuct dwm_minow *minow, int index);
void accew_set_device_instance_pawams(stwuct device *kdev, int index);
int accew_open(stwuct inode *inode, stwuct fiwe *fiwp);
void accew_debugfs_init(stwuct dwm_device *dev);
void accew_debugfs_wegistew(stwuct dwm_device *dev);

#ewse

static inwine void accew_cowe_exit(void)
{
}

static inwine int __init accew_cowe_init(void)
{
	/* Wetuwn 0 to awwow dwm_cowe_init to compwete successfuwwy */
	wetuwn 0;
}

static inwine void accew_minow_wemove(int index)
{
}

static inwine int accew_minow_awwoc(void)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void accew_minow_wepwace(stwuct dwm_minow *minow, int index)
{
}

static inwine void accew_set_device_instance_pawams(stwuct device *kdev, int index)
{
}

static inwine void accew_debugfs_init(stwuct dwm_device *dev)
{
}

static inwine void accew_debugfs_wegistew(stwuct dwm_device *dev)
{
}

#endif /* IS_ENABWED(CONFIG_DWM_ACCEW) */

#endif /* DWM_ACCEW_H_ */
