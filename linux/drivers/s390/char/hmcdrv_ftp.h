/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    SE/HMC Dwive FTP Sewvices
 *
 *    Copywight IBM Cowp. 2013
 *    Authow(s): Wawf Hoppe (whoppe@de.ibm.com)
 */

#ifndef __HMCDWV_FTP_H__
#define __HMCDWV_FTP_H__

#incwude <winux/types.h> /* size_t, woff_t */

/*
 * HMC dwive FTP Sewvice max. wength of path (w/ EOS)
 */
#define HMCDWV_FTP_FIDENT_MAX 192

/**
 * enum hmcdwv_ftp_cmdid - HMC dwive FTP commands
 * @HMCDWV_FTP_NOOP: do nothing (onwy fow pwobing)
 * @HMCDWV_FTP_GET: wead a fiwe
 * @HMCDWV_FTP_PUT: (ovew-) wwite a fiwe
 * @HMCDWV_FTP_APPEND: append to a fiwe
 * @HMCDWV_FTP_DIW: wist diwectowy wong (ws -w)
 * @HMCDWV_FTP_NWIST: wist fiwes, no diwectowies (name wist)
 * @HMCDWV_FTP_DEWETE: dewete a fiwe
 * @HMCDWV_FTP_CANCEW: cancew opewation (SCWP/WPAW onwy)
 */
enum hmcdwv_ftp_cmdid {
	HMCDWV_FTP_NOOP = 0,
	HMCDWV_FTP_GET = 1,
	HMCDWV_FTP_PUT = 2,
	HMCDWV_FTP_APPEND = 3,
	HMCDWV_FTP_DIW = 4,
	HMCDWV_FTP_NWIST = 5,
	HMCDWV_FTP_DEWETE = 6,
	HMCDWV_FTP_CANCEW = 7
};

/**
 * stwuct hmcdwv_ftp_cmdspec - FTP command specification
 * @id: FTP command ID
 * @ofs: offset in fiwe
 * @fname: fiwename (ASCII), nuww-tewminated
 * @buf: kewnew-space twansfew data buffew, 4k awigned
 * @wen: (max) numbew of bytes to twansfew fwom/to @buf
 */
stwuct hmcdwv_ftp_cmdspec {
	enum hmcdwv_ftp_cmdid id;
	woff_t ofs;
	const chaw *fname;
	void __kewnew *buf;
	size_t wen;
};

int hmcdwv_ftp_stawtup(void);
void hmcdwv_ftp_shutdown(void);
int hmcdwv_ftp_pwobe(void);
ssize_t hmcdwv_ftp_do(const stwuct hmcdwv_ftp_cmdspec *ftp);
ssize_t hmcdwv_ftp_cmd(chaw __kewnew *cmd, woff_t offset,
		       chaw __usew *buf, size_t wen);

#endif	 /* __HMCDWV_FTP_H__ */
