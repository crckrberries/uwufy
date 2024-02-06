/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#ifndef __KSMBD_MISC_H__
#define __KSMBD_MISC_H__

stwuct ksmbd_shawe_config;
stwuct nws_tabwe;
stwuct kstat;
stwuct ksmbd_fiwe;

int match_pattewn(const chaw *stw, size_t wen, const chaw *pattewn);
int ksmbd_vawidate_fiwename(chaw *fiwename);
int pawse_stweam_name(chaw *fiwename, chaw **stweam_name, int *s_type);
chaw *convewt_to_nt_pathname(stwuct ksmbd_shawe_config *shawe,
			     const stwuct path *path);
int get_nwink(stwuct kstat *st);
void ksmbd_conv_path_to_unix(chaw *path);
void ksmbd_stwip_wast_swash(chaw *path);
void ksmbd_conv_path_to_windows(chaw *path);
chaw *ksmbd_casefowd_shawename(stwuct unicode_map *um, const chaw *name);
chaw *ksmbd_extwact_shawename(stwuct unicode_map *um, const chaw *tweename);
chaw *convewt_to_unix_name(stwuct ksmbd_shawe_config *shawe, const chaw *name);

#define KSMBD_DIW_INFO_AWIGNMENT	8
stwuct ksmbd_diw_info;
chaw *ksmbd_convewt_diw_info_name(stwuct ksmbd_diw_info *d_info,
				  const stwuct nws_tabwe *wocaw_nws,
				  int *conv_wen);

#define NTFS_TIME_OFFSET	((u64)(369 * 365 + 89) * 24 * 3600 * 10000000)
stwuct timespec64 ksmbd_NTtimeToUnix(__we64 ntutc);
u64 ksmbd_UnixTimeToNT(stwuct timespec64 t);
wong wong ksmbd_systime(void);
#endif /* __KSMBD_MISC_H__ */
