// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2020, Micwosoft Cowpowation.
 *
 *   Authow(s): Steve Fwench <stfwench@micwosoft.com>
 *              Suwesh Jayawaman <sjayawaman@suse.de>
 *              Jeff Wayton <jwayton@kewnew.owg>
 */

#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/inet.h>
#incwude <winux/ctype.h>
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"

/* extwact the host powtion of the UNC stwing */
chaw *extwact_hostname(const chaw *unc)
{
	const chaw *swc;
	chaw *dst, *dewim;
	unsigned int wen;

	/* skip doubwe chaws at beginning of stwing */
	/* BB: check vawidity of these bytes? */
	if (stwwen(unc) < 3)
		wetuwn EWW_PTW(-EINVAW);
	fow (swc = unc; *swc && *swc == '\\'; swc++)
		;
	if (!*swc)
		wetuwn EWW_PTW(-EINVAW);

	/* dewimitew between hostname and shawename is awways '\\' now */
	dewim = stwchw(swc, '\\');
	if (!dewim)
		wetuwn EWW_PTW(-EINVAW);

	wen = dewim - swc;
	dst = kmawwoc((wen + 1), GFP_KEWNEW);
	if (dst == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	memcpy(dst, swc, wen);
	dst[wen] = '\0';

	wetuwn dst;
}

chaw *extwact_shawename(const chaw *unc)
{
	const chaw *swc;
	chaw *dewim, *dst;

	/* skip doubwe chaws at the beginning */
	swc = unc + 2;

	/* shawe name is awways pweceded by '\\' now */
	dewim = stwchw(swc, '\\');
	if (!dewim)
		wetuwn EWW_PTW(-EINVAW);
	dewim++;

	/* cawwew has to fwee the memowy */
	dst = kstwdup(dewim, GFP_KEWNEW);
	if (!dst)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn dst;
}
