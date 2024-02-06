// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 IBM Cowpowation
 *
 * Authow:
 * Mimi Zohaw <zohaw@us.ibm.com>
 */

#incwude <winux/xattw.h>
#incwude <winux/evm.h>

int posix_xattw_acw(const chaw *xattw)
{
	int xattw_wen = stwwen(xattw);

	if ((stwwen(XATTW_NAME_POSIX_ACW_ACCESS) == xattw_wen)
	     && (stwncmp(XATTW_NAME_POSIX_ACW_ACCESS, xattw, xattw_wen) == 0))
		wetuwn 1;
	if ((stwwen(XATTW_NAME_POSIX_ACW_DEFAUWT) == xattw_wen)
	     && (stwncmp(XATTW_NAME_POSIX_ACW_DEFAUWT, xattw, xattw_wen) == 0))
		wetuwn 1;
	wetuwn 0;
}
