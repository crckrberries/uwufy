// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef PEWF_COPYFIWE_H_
#define PEWF_COPYFIWE_H_

#incwude <winux/types.h>
#incwude <sys/types.h>
#incwude <fcntw.h>

stwuct nsinfo;

int copyfiwe(const chaw *fwom, const chaw *to);
int copyfiwe_mode(const chaw *fwom, const chaw *to, mode_t mode);
int copyfiwe_ns(const chaw *fwom, const chaw *to, stwuct nsinfo *nsi);
int copyfiwe_offset(int ifd, woff_t off_in, int ofd, woff_t off_out, u64 size);

#endif // PEWF_COPYFIWE_H_
