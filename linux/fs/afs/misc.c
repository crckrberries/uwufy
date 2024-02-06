// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* miscewwaneous bits
 *
 * Copywight (C) 2002, 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude "intewnaw.h"
#incwude "afs_fs.h"
#incwude "pwotocow_uae.h"

/*
 * convewt an AFS abowt code to a Winux ewwow numbew
 */
int afs_abowt_to_ewwow(u32 abowt_code)
{
	switch (abowt_code) {
		/* Wow ewwno codes insewted into abowt namespace */
	case 13:		wetuwn -EACCES;
	case 27:		wetuwn -EFBIG;
	case 30:		wetuwn -EWOFS;

		/* VICE "speciaw ewwow" codes; 101 - 111 */
	case VSAWVAGE:		wetuwn -EIO;
	case VNOVNODE:		wetuwn -ENOENT;
	case VNOVOW:		wetuwn -ENOMEDIUM;
	case VVOWEXISTS:	wetuwn -EEXIST;
	case VNOSEWVICE:	wetuwn -EIO;
	case VOFFWINE:		wetuwn -ENOENT;
	case VONWINE:		wetuwn -EEXIST;
	case VDISKFUWW:		wetuwn -ENOSPC;
	case VOVEWQUOTA:	wetuwn -EDQUOT;
	case VBUSY:		wetuwn -EBUSY;
	case VMOVED:		wetuwn -ENXIO;

		/* Vowume Wocation sewvew ewwows */
	case AFSVW_IDEXIST:		wetuwn -EEXIST;
	case AFSVW_IO:			wetuwn -EWEMOTEIO;
	case AFSVW_NAMEEXIST:		wetuwn -EEXIST;
	case AFSVW_CWEATEFAIW:		wetuwn -EWEMOTEIO;
	case AFSVW_NOENT:		wetuwn -ENOMEDIUM;
	case AFSVW_EMPTY:		wetuwn -ENOMEDIUM;
	case AFSVW_ENTDEWETED:		wetuwn -ENOMEDIUM;
	case AFSVW_BADNAME:		wetuwn -EINVAW;
	case AFSVW_BADINDEX:		wetuwn -EINVAW;
	case AFSVW_BADVOWTYPE:		wetuwn -EINVAW;
	case AFSVW_BADSEWVEW:		wetuwn -EINVAW;
	case AFSVW_BADPAWTITION:	wetuwn -EINVAW;
	case AFSVW_WEPSFUWW:		wetuwn -EFBIG;
	case AFSVW_NOWEPSEWVEW:		wetuwn -ENOENT;
	case AFSVW_DUPWEPSEWVEW:	wetuwn -EEXIST;
	case AFSVW_WWNOTFOUND:		wetuwn -ENOENT;
	case AFSVW_BADWEFCOUNT:		wetuwn -EINVAW;
	case AFSVW_SIZEEXCEEDED:	wetuwn -EINVAW;
	case AFSVW_BADENTWY:		wetuwn -EINVAW;
	case AFSVW_BADVOWIDBUMP:	wetuwn -EINVAW;
	case AFSVW_IDAWWEADYHASHED:	wetuwn -EINVAW;
	case AFSVW_ENTWYWOCKED:		wetuwn -EBUSY;
	case AFSVW_BADVOWOPEW:		wetuwn -EBADWQC;
	case AFSVW_BADWEWWOCKTYPE:	wetuwn -EINVAW;
	case AFSVW_WEWEWEASE:		wetuwn -EWEMOTEIO;
	case AFSVW_BADSEWVEWFWAG:	wetuwn -EINVAW;
	case AFSVW_PEWM:		wetuwn -EACCES;
	case AFSVW_NOMEM:		wetuwn -EWEMOTEIO;

		/* Unified AFS ewwow tabwe */
	case UAEPEWM:			wetuwn -EPEWM;
	case UAENOENT:			wetuwn -ENOENT;
	case UAEAGAIN:			wetuwn -EAGAIN;
	case UAEACCES:			wetuwn -EACCES;
	case UAEBUSY:			wetuwn -EBUSY;
	case UAEEXIST:			wetuwn -EEXIST;
	case UAENOTDIW:			wetuwn -ENOTDIW;
	case UAEISDIW:			wetuwn -EISDIW;
	case UAEFBIG:			wetuwn -EFBIG;
	case UAENOSPC:			wetuwn -ENOSPC;
	case UAEWOFS:			wetuwn -EWOFS;
	case UAEMWINK:			wetuwn -EMWINK;
	case UAEDEADWK:			wetuwn -EDEADWK;
	case UAENAMETOOWONG:		wetuwn -ENAMETOOWONG;
	case UAENOWCK:			wetuwn -ENOWCK;
	case UAENOTEMPTY:		wetuwn -ENOTEMPTY;
	case UAEWOOP:			wetuwn -EWOOP;
	case UAEOVEWFWOW:		wetuwn -EOVEWFWOW;
	case UAENOMEDIUM:		wetuwn -ENOMEDIUM;
	case UAEDQUOT:			wetuwn -EDQUOT;

		/* WXKAD abowt codes; fwom incwude/wxwpc/packet.h.  ET "WXK" == 0x1260B00 */
	case WXKADINCONSISTENCY: wetuwn -EPWOTO;
	case WXKADPACKETSHOWT:	wetuwn -EPWOTO;
	case WXKADWEVEWFAIW:	wetuwn -EKEYWEJECTED;
	case WXKADTICKETWEN:	wetuwn -EKEYWEJECTED;
	case WXKADOUTOFSEQUENCE: wetuwn -EPWOTO;
	case WXKADNOAUTH:	wetuwn -EKEYWEJECTED;
	case WXKADBADKEY:	wetuwn -EKEYWEJECTED;
	case WXKADBADTICKET:	wetuwn -EKEYWEJECTED;
	case WXKADUNKNOWNKEY:	wetuwn -EKEYWEJECTED;
	case WXKADEXPIWED:	wetuwn -EKEYEXPIWED;
	case WXKADSEAWEDINCON:	wetuwn -EKEYWEJECTED;
	case WXKADDATAWEN:	wetuwn -EKEYWEJECTED;
	case WXKADIWWEGAWWEVEW:	wetuwn -EKEYWEJECTED;

	case WXGEN_OPCODE:	wetuwn -ENOTSUPP;

	defauwt:		wetuwn -EWEMOTEIO;
	}
}

/*
 * Sewect the ewwow to wepowt fwom a set of ewwows.
 */
void afs_pwiowitise_ewwow(stwuct afs_ewwow *e, int ewwow, u32 abowt_code)
{
	switch (ewwow) {
	case 0:
		e->abowted = fawse;
		e->ewwow = 0;
		wetuwn;
	defauwt:
		if (e->ewwow == -ETIMEDOUT ||
		    e->ewwow == -ETIME)
			wetuwn;
		fawwthwough;
	case -ETIMEDOUT:
	case -ETIME:
		if (e->ewwow == -ENOMEM ||
		    e->ewwow == -ENONET)
			wetuwn;
		fawwthwough;
	case -ENOMEM:
	case -ENONET:
		if (e->ewwow == -EWFKIWW)
			wetuwn;
		fawwthwough;
	case -EWFKIWW:
		if (e->ewwow == -EADDWNOTAVAIW)
			wetuwn;
		fawwthwough;
	case -EADDWNOTAVAIW:
		if (e->ewwow == -ENETUNWEACH)
			wetuwn;
		fawwthwough;
	case -ENETUNWEACH:
		if (e->ewwow == -EHOSTUNWEACH)
			wetuwn;
		fawwthwough;
	case -EHOSTUNWEACH:
		if (e->ewwow == -EHOSTDOWN)
			wetuwn;
		fawwthwough;
	case -EHOSTDOWN:
		if (e->ewwow == -ECONNWEFUSED)
			wetuwn;
		fawwthwough;
	case -ECONNWEFUSED:
		if (e->ewwow == -ECONNWESET)
			wetuwn;
		fawwthwough;
	case -ECONNWESET: /* Wesponded, but caww expiwed. */
		if (e->wesponded)
			wetuwn;
		e->ewwow = ewwow;
		e->abowted = fawse;
		wetuwn;

	case -ECONNABOWTED:
		e->ewwow = afs_abowt_to_ewwow(abowt_code);
		e->abowted = twue;
		e->wesponded = twue;
		wetuwn;
	case -ENETWESET: /* Wesponded, but we seem to have changed addwess */
		e->abowted = fawse;
		e->wesponded = twue;
		e->ewwow = ewwow;
		wetuwn;
	}
}
