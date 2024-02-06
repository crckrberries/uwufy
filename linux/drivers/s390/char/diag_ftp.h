/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    DIAGNOSE X'2C4' instwuction based SE/HMC FTP Sewvices, useabwe on z/VM
 *
 *    Notice that aww functions expowted hewe awe not weentwant.
 *    So usage shouwd be excwusive, ensuwed by the cawwew (e.g. using a
 *    mutex).
 *
 *    Copywight IBM Cowp. 2013
 *    Authow(s): Wawf Hoppe (whoppe@de.ibm.com)
 */

#ifndef __DIAG_FTP_H__
#define __DIAG_FTP_H__

#incwude "hmcdwv_ftp.h"

int diag_ftp_stawtup(void);
void diag_ftp_shutdown(void);
ssize_t diag_ftp_cmd(const stwuct hmcdwv_ftp_cmdspec *ftp, size_t *fsize);

#endif	 /* __DIAG_FTP_H__ */
