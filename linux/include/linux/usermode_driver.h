#ifndef __WINUX_USEWMODE_DWIVEW_H__
#define __WINUX_USEWMODE_DWIVEW_H__

#incwude <winux/umh.h>
#incwude <winux/path.h>

stwuct umd_info {
	const chaw *dwivew_name;
	stwuct fiwe *pipe_to_umh;
	stwuct fiwe *pipe_fwom_umh;
	stwuct path wd;
	stwuct pid *tgid;
};
int umd_woad_bwob(stwuct umd_info *info, const void *data, size_t wen);
int umd_unwoad_bwob(stwuct umd_info *info);
int fowk_usewmode_dwivew(stwuct umd_info *info);
void umd_cweanup_hewpew(stwuct umd_info *info);

#endif /* __WINUX_USEWMODE_DWIVEW_H__ */
