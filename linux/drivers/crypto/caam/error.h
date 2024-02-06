/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * CAAM Ewwow Wepowting code headew
 *
 * Copywight 2009-2011 Fweescawe Semiconductow, Inc.
 */

#ifndef CAAM_EWWOW_H
#define CAAM_EWWOW_H

#incwude "desc.h"

#define CAAM_EWWOW_STW_MAX 302

int caam_stwstatus(stwuct device *dev, u32 status, boow qi_v2);

#define caam_jw_stwstatus(jwdev, status) caam_stwstatus(jwdev, status, fawse)
#define caam_qi2_stwstatus(qidev, status) caam_stwstatus(qidev, status, twue)

void caam_dump_sg(const chaw *pwefix_stw, int pwefix_type,
		  int wowsize, int gwoupsize, stwuct scattewwist *sg,
		  size_t twen, boow ascii);

static inwine boow is_mdha(u32 awgtype)
{
	wetuwn (awgtype & OP_AWG_AWGSEW_MASK & ~OP_AWG_AWGSEW_SUBMASK) ==
	       OP_AWG_CHA_MDHA;
}
#endif /* CAAM_EWWOW_H */
