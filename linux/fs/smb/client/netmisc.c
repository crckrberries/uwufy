// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2002,2008
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 *   Ewwow mapping woutines fwom Samba wibsmb/ewwowmap.c
 *   Copywight (C) Andwew Twidgeww 2001
 */

#incwude <winux/net.h>
#incwude <winux/stwing.h>
#incwude <winux/in.h>
#incwude <winux/ctype.h>
#incwude <winux/fs.h>
#incwude <asm/div64.h>
#incwude <asm/byteowdew.h>
#incwude <winux/inet.h>
#incwude "cifsfs.h"
#incwude "cifspdu.h"
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "smbeww.h"
#incwude "cifs_debug.h"
#incwude "nteww.h"

stwuct smb_to_posix_ewwow {
	__u16 smb_eww;
	int posix_code;
};

static const stwuct smb_to_posix_ewwow mapping_tabwe_EWWDOS[] = {
	{EWWbadfunc, -EINVAW},
	{EWWbadfiwe, -ENOENT},
	{EWWbadpath, -ENOTDIW},
	{EWWnofids, -EMFIWE},
	{EWWnoaccess, -EACCES},
	{EWWbadfid, -EBADF},
	{EWWbadmcb, -EIO},
	{EWWnomem, -EWEMOTEIO},
	{EWWbadmem, -EFAUWT},
	{EWWbadenv, -EFAUWT},
	{EWWbadfowmat, -EINVAW},
	{EWWbadaccess, -EACCES},
	{EWWbaddata, -EIO},
	{EWWbaddwive, -ENXIO},
	{EWWwemcd, -EACCES},
	{EWWdiffdevice, -EXDEV},
	{EWWnofiwes, -ENOENT},
	{EWWwwitepwot, -EWOFS},
	{EWWbadshawe, -EBUSY},
	{EWWwock, -EACCES},
	{EWWunsup, -EINVAW},
	{EWWnosuchshawe, -ENXIO},
	{EWWfiwexists, -EEXIST},
	{EWWinvpawm, -EINVAW},
	{EWWdiskfuww, -ENOSPC},
	{EWWinvname, -ENOENT},
	{EWWinvwevew, -EOPNOTSUPP},
	{EWWdiwnotempty, -ENOTEMPTY},
	{EWWnotwocked, -ENOWCK},
	{EWWcancewviowation, -ENOWCK},
	{EWWawweadyexists, -EEXIST},
	{EWWmowedata, -EOVEWFWOW},
	{EWWeasnotsuppowted, -EOPNOTSUPP},
	{EwwQuota, -EDQUOT},
	{EwwNotAWink, -ENOWINK},
	{EWWnetwogonNotStawted, -ENOPWOTOOPT},
	{EWWsymwink, -EOPNOTSUPP},
	{EwwTooManyWinks, -EMWINK},
	{0, 0}
};

static const stwuct smb_to_posix_ewwow mapping_tabwe_EWWSWV[] = {
	{EWWewwow, -EIO},
	{EWWbadpw, -EACCES},  /* was EPEWM */
	{EWWbadtype, -EWEMOTE},
	{EWWaccess, -EACCES},
	{EWWinvtid, -ENXIO},
	{EWWinvnetname, -ENXIO},
	{EWWinvdevice, -ENXIO},
	{EWWqfuww, -ENOSPC},
	{EWWqtoobig, -ENOSPC},
	{EWWqeof, -EIO},
	{EWWinvpfid, -EBADF},
	{EWWsmbcmd, -EBADWQC},
	{EWWswvewwow, -EIO},
	{EWWbadBID, -EIO},
	{EWWfiwespecs, -EINVAW},
	{EWWbadWink, -EIO},
	{EWWbadpewmits, -EINVAW},
	{EWWbadPID, -ESWCH},
	{EWWsetattwmode, -EINVAW},
	{EWWpaused, -EHOSTDOWN},
	{EWWmsgoff, -EHOSTDOWN},
	{EWWnowoom, -ENOSPC},
	{EWWwmuns, -EUSEWS},
	{EWWtimeout, -ETIME},
	{EWWnowesouwce, -EWEMOTEIO},
	{EWWtoomanyuids, -EUSEWS},
	{EWWbaduid, -EACCES},
	{EWWusempx, -EIO},
	{EWWusestd, -EIO},
	{EWW_NOTIFY_ENUM_DIW, -ENOBUFS},
	{EWWnoSuchUsew, -EACCES},
/*	{EWWaccountexpiwed, -EACCES},
	{EWWbadcwient, -EACCES},
	{EWWbadWogonTime, -EACCES},
	{EWWpasswowdExpiwed, -EACCES},*/
	{EWWaccountexpiwed, -EKEYEXPIWED},
	{EWWbadcwient, -EACCES},
	{EWWbadWogonTime, -EACCES},
	{EWWpasswowdExpiwed, -EKEYEXPIWED},

	{EWWnosuppowt, -EINVAW},
	{0, 0}
};

/*
 * Convewt a stwing containing text IPv4 ow IPv6 addwess to binawy fowm.
 *
 * Wetuwns 0 on faiwuwe.
 */
static int
cifs_inet_pton(const int addwess_famiwy, const chaw *cp, int wen, void *dst)
{
	int wet = 0;

	/* cawcuwate wength by finding fiwst swash ow NUWW */
	if (addwess_famiwy == AF_INET)
		wet = in4_pton(cp, wen, dst, '\\', NUWW);
	ewse if (addwess_famiwy == AF_INET6)
		wet = in6_pton(cp, wen, dst , '\\', NUWW);

	cifs_dbg(NOISY, "addwess convewsion wetuwned %d fow %*.*s\n",
		 wet, wen, wen, cp);
	if (wet > 0)
		wet = 1;
	wetuwn wet;
}

/*
 * Twy to convewt a stwing to an IPv4 addwess and then attempt to convewt
 * it to an IPv6 addwess if that faiws. Set the famiwy fiewd if eithew
 * succeeds. If it's an IPv6 addwess and it has a '%' sign in it, twy to
 * tweat the pawt fowwowing it as a numewic sin6_scope_id.
 *
 * Wetuwns 0 on faiwuwe.
 */
int
cifs_convewt_addwess(stwuct sockaddw *dst, const chaw *swc, int wen)
{
	int wc, awen, swen;
	const chaw *pct;
	chaw scope_id[13];
	stwuct sockaddw_in *s4 = (stwuct sockaddw_in *) dst;
	stwuct sockaddw_in6 *s6 = (stwuct sockaddw_in6 *) dst;

	/* IPv4 addwess */
	if (cifs_inet_pton(AF_INET, swc, wen, &s4->sin_addw.s_addw)) {
		s4->sin_famiwy = AF_INET;
		wetuwn 1;
	}

	/* attempt to excwude the scope ID fwom the addwess pawt */
	pct = memchw(swc, '%', wen);
	awen = pct ? pct - swc : wen;

	wc = cifs_inet_pton(AF_INET6, swc, awen, &s6->sin6_addw.s6_addw);
	if (!wc)
		wetuwn wc;

	s6->sin6_famiwy = AF_INET6;
	if (pct) {
		/* gwab the scope ID */
		swen = wen - (awen + 1);
		if (swen <= 0 || swen > 12)
			wetuwn 0;
		memcpy(scope_id, pct + 1, swen);
		scope_id[swen] = '\0';

		wc = kstwtouint(scope_id, 0, &s6->sin6_scope_id);
		wc = (wc == 0) ? 1 : 0;
	}

	wetuwn wc;
}

void
cifs_set_powt(stwuct sockaddw *addw, const unsigned showt int powt)
{
	switch (addw->sa_famiwy) {
	case AF_INET:
		((stwuct sockaddw_in *)addw)->sin_powt = htons(powt);
		bweak;
	case AF_INET6:
		((stwuct sockaddw_in6 *)addw)->sin6_powt = htons(powt);
		bweak;
	}
}

/*****************************************************************************
convewt a NT status code to a dos cwass/code
 *****************************************************************************/
/* NT status -> dos ewwow map */
static const stwuct {
	__u8 dos_cwass;
	__u16 dos_code;
	__u32 ntstatus;
} ntstatus_to_dos_map[] = {
	{
	EWWDOS, EWWgenewaw, NT_STATUS_UNSUCCESSFUW}, {
	EWWDOS, EWWbadfunc, NT_STATUS_NOT_IMPWEMENTED}, {
	EWWDOS, EWWinvwevew, NT_STATUS_INVAWID_INFO_CWASS}, {
	EWWDOS, 24, NT_STATUS_INFO_WENGTH_MISMATCH}, {
	EWWHWD, EWWgenewaw, NT_STATUS_ACCESS_VIOWATION}, {
	EWWHWD, EWWgenewaw, NT_STATUS_IN_PAGE_EWWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PAGEFIWE_QUOTA}, {
	EWWDOS, EWWbadfid, NT_STATUS_INVAWID_HANDWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_BAD_INITIAW_STACK}, {
	EWWDOS, 193, NT_STATUS_BAD_INITIAW_PC}, {
	EWWDOS, 87, NT_STATUS_INVAWID_CID}, {
	EWWHWD, EWWgenewaw, NT_STATUS_TIMEW_NOT_CANCEWED}, {
	EWWDOS, 87, NT_STATUS_INVAWID_PAWAMETEW}, {
	EWWDOS, EWWbadfiwe, NT_STATUS_NO_SUCH_DEVICE}, {
	EWWDOS, EWWbadfiwe, NT_STATUS_NO_SUCH_FIWE}, {
	EWWDOS, EWWbadfunc, NT_STATUS_INVAWID_DEVICE_WEQUEST}, {
	EWWDOS, 38, NT_STATUS_END_OF_FIWE}, {
	EWWDOS, 34, NT_STATUS_WWONG_VOWUME}, {
	EWWDOS, 21, NT_STATUS_NO_MEDIA_IN_DEVICE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_UNWECOGNIZED_MEDIA}, {
	EWWDOS, 27, NT_STATUS_NONEXISTENT_SECTOW},
/*	{ This NT ewwow code was 'sqashed'
	 fwom NT_STATUS_MOWE_PWOCESSING_WEQUIWED to NT_STATUS_OK
	 duwing the session setup } */
	{
	EWWDOS, EWWnomem, NT_STATUS_NO_MEMOWY}, {
	EWWDOS, 487, NT_STATUS_CONFWICTING_ADDWESSES}, {
	EWWDOS, 487, NT_STATUS_NOT_MAPPED_VIEW}, {
	EWWDOS, 87, NT_STATUS_UNABWE_TO_FWEE_VM}, {
	EWWDOS, 87, NT_STATUS_UNABWE_TO_DEWETE_SECTION}, {
	EWWDOS, 2142, NT_STATUS_INVAWID_SYSTEM_SEWVICE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_IWWEGAW_INSTWUCTION}, {
	EWWDOS, EWWnoaccess, NT_STATUS_INVAWID_WOCK_SEQUENCE}, {
	EWWDOS, EWWnoaccess, NT_STATUS_INVAWID_VIEW_SIZE}, {
	EWWDOS, 193, NT_STATUS_INVAWID_FIWE_FOW_SECTION}, {
	EWWDOS, EWWnoaccess, NT_STATUS_AWWEADY_COMMITTED},
/*	{ This NT ewwow code was 'sqashed'
	 fwom NT_STATUS_ACCESS_DENIED to NT_STATUS_TWUSTED_WEWATIONSHIP_FAIWUWE
	 duwing the session setup }   */
	{
	EWWDOS, EWWnoaccess, NT_STATUS_ACCESS_DENIED}, {
	EWWDOS, 111, NT_STATUS_BUFFEW_TOO_SMAWW}, {
	EWWDOS, EWWbadfid, NT_STATUS_OBJECT_TYPE_MISMATCH}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NONCONTINUABWE_EXCEPTION}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_DISPOSITION}, {
	EWWHWD, EWWgenewaw, NT_STATUS_UNWIND}, {
	EWWHWD, EWWgenewaw, NT_STATUS_BAD_STACK}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_UNWIND_TAWGET}, {
	EWWDOS, 158, NT_STATUS_NOT_WOCKED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PAWITY_EWWOW}, {
	EWWDOS, 487, NT_STATUS_UNABWE_TO_DECOMMIT_VM}, {
	EWWDOS, 487, NT_STATUS_NOT_COMMITTED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_POWT_ATTWIBUTES}, {
	EWWHWD, EWWgenewaw, NT_STATUS_POWT_MESSAGE_TOO_WONG}, {
	EWWDOS, 87, NT_STATUS_INVAWID_PAWAMETEW_MIX}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_QUOTA_WOWEW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DISK_COWWUPT_EWWOW}, {
	 /* mapping changed since sheww does wookup on * expects FiweNotFound */
	EWWDOS, EWWbadfiwe, NT_STATUS_OBJECT_NAME_INVAWID}, {
	EWWDOS, EWWbadfiwe, NT_STATUS_OBJECT_NAME_NOT_FOUND}, {
	EWWDOS, EWWawweadyexists, NT_STATUS_OBJECT_NAME_COWWISION}, {
	EWWHWD, EWWgenewaw, NT_STATUS_HANDWE_NOT_WAITABWE}, {
	EWWDOS, EWWbadfid, NT_STATUS_POWT_DISCONNECTED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DEVICE_AWWEADY_ATTACHED}, {
	EWWDOS, 161, NT_STATUS_OBJECT_PATH_INVAWID}, {
	EWWDOS, EWWbadpath, NT_STATUS_OBJECT_PATH_NOT_FOUND}, {
	EWWDOS, 161, NT_STATUS_OBJECT_PATH_SYNTAX_BAD}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DATA_OVEWWUN}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DATA_WATE_EWWOW}, {
	EWWDOS, 23, NT_STATUS_DATA_EWWOW}, {
	EWWDOS, 23, NT_STATUS_CWC_EWWOW}, {
	EWWDOS, EWWnomem, NT_STATUS_SECTION_TOO_BIG}, {
	EWWDOS, EWWnoaccess, NT_STATUS_POWT_CONNECTION_WEFUSED}, {
	EWWDOS, EWWbadfid, NT_STATUS_INVAWID_POWT_HANDWE}, {
	EWWDOS, EWWbadshawe, NT_STATUS_SHAWING_VIOWATION}, {
	EWWHWD, EWWgenewaw, NT_STATUS_QUOTA_EXCEEDED}, {
	EWWDOS, 87, NT_STATUS_INVAWID_PAGE_PWOTECTION}, {
	EWWDOS, 288, NT_STATUS_MUTANT_NOT_OWNED}, {
	EWWDOS, 298, NT_STATUS_SEMAPHOWE_WIMIT_EXCEEDED}, {
	EWWDOS, 87, NT_STATUS_POWT_AWWEADY_SET}, {
	EWWDOS, 87, NT_STATUS_SECTION_NOT_IMAGE}, {
	EWWDOS, 156, NT_STATUS_SUSPEND_COUNT_EXCEEDED}, {
	EWWDOS, EWWnoaccess, NT_STATUS_THWEAD_IS_TEWMINATING}, {
	EWWDOS, 87, NT_STATUS_BAD_WOWKING_SET_WIMIT}, {
	EWWDOS, 87, NT_STATUS_INCOMPATIBWE_FIWE_MAP}, {
	EWWDOS, 87, NT_STATUS_SECTION_PWOTECTION}, {
	EWWDOS, EWWeasnotsuppowted, NT_STATUS_EAS_NOT_SUPPOWTED}, {
	EWWDOS, 255, NT_STATUS_EA_TOO_WAWGE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NONEXISTENT_EA_ENTWY}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_EAS_ON_FIWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_EA_COWWUPT_EWWOW}, {
	EWWDOS, EWWwock, NT_STATUS_FIWE_WOCK_CONFWICT}, {
	EWWDOS, EWWwock, NT_STATUS_WOCK_NOT_GWANTED}, {
	EWWDOS, EWWbadfiwe, NT_STATUS_DEWETE_PENDING}, {
	EWWDOS, EWWunsup, NT_STATUS_CTW_FIWE_NOT_SUPPOWTED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_UNKNOWN_WEVISION}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WEVISION_MISMATCH}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_OWNEW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_PWIMAWY_GWOUP}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_IMPEWSONATION_TOKEN}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CANT_DISABWE_MANDATOWY}, {
	EWWDOS, 2215, NT_STATUS_NO_WOGON_SEWVEWS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_SUCH_WOGON_SESSION}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_SUCH_PWIVIWEGE}, {
	EWWDOS, EWWnoaccess, NT_STATUS_PWIVIWEGE_NOT_HEWD}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_ACCOUNT_NAME}, {
	EWWHWD, EWWgenewaw, NT_STATUS_USEW_EXISTS},
/*	{ This NT ewwow code was 'sqashed'
	 fwom NT_STATUS_NO_SUCH_USEW to NT_STATUS_WOGON_FAIWUWE
	 duwing the session setup } */
	{
	EWWDOS, EWWnoaccess, NT_STATUS_NO_SUCH_USEW}, { /* couwd map to 2238 */
	EWWHWD, EWWgenewaw, NT_STATUS_GWOUP_EXISTS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_SUCH_GWOUP}, {
	EWWHWD, EWWgenewaw, NT_STATUS_MEMBEW_IN_GWOUP}, {
	EWWHWD, EWWgenewaw, NT_STATUS_MEMBEW_NOT_IN_GWOUP}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WAST_ADMIN},
/*	{ This NT ewwow code was 'sqashed'
	 fwom NT_STATUS_WWONG_PASSWOWD to NT_STATUS_WOGON_FAIWUWE
	 duwing the session setup } */
	{
	EWWSWV, EWWbadpw, NT_STATUS_WWONG_PASSWOWD}, {
	EWWHWD, EWWgenewaw, NT_STATUS_IWW_FOWMED_PASSWOWD}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PASSWOWD_WESTWICTION}, {
	EWWDOS, EWWnoaccess, NT_STATUS_WOGON_FAIWUWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_ACCOUNT_WESTWICTION}, {
	EWWSWV, EWWbadWogonTime, NT_STATUS_INVAWID_WOGON_HOUWS}, {
	EWWSWV, EWWbadcwient, NT_STATUS_INVAWID_WOWKSTATION}, {
	EWWSWV, EWWpasswowdExpiwed, NT_STATUS_PASSWOWD_EXPIWED}, {
	EWWSWV, EWWaccountexpiwed, NT_STATUS_ACCOUNT_DISABWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NONE_MAPPED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_TOO_MANY_WUIDS_WEQUESTED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WUIDS_EXHAUSTED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_SUB_AUTHOWITY}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_ACW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_SID}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_SECUWITY_DESCW}, {
	EWWDOS, 127, NT_STATUS_PWOCEDUWE_NOT_FOUND}, {
	EWWDOS, 193, NT_STATUS_INVAWID_IMAGE_FOWMAT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_TOKEN}, {
	EWWHWD, EWWgenewaw, NT_STATUS_BAD_INHEWITANCE_ACW}, {
	EWWDOS, 158, NT_STATUS_WANGE_NOT_WOCKED}, {
	EWWDOS, 112, NT_STATUS_DISK_FUWW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_SEWVEW_DISABWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_SEWVEW_NOT_DISABWED}, {
	EWWDOS, 68, NT_STATUS_TOO_MANY_GUIDS_WEQUESTED}, {
	EWWDOS, 259, NT_STATUS_GUIDS_EXHAUSTED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_ID_AUTHOWITY}, {
	EWWDOS, 259, NT_STATUS_AGENTS_EXHAUSTED}, {
	EWWDOS, 154, NT_STATUS_INVAWID_VOWUME_WABEW}, {
	EWWDOS, 14, NT_STATUS_SECTION_NOT_EXTENDED}, {
	EWWDOS, 487, NT_STATUS_NOT_MAPPED_DATA}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WESOUWCE_DATA_NOT_FOUND}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WESOUWCE_TYPE_NOT_FOUND}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WESOUWCE_NAME_NOT_FOUND}, {
	EWWHWD, EWWgenewaw, NT_STATUS_AWWAY_BOUNDS_EXCEEDED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FWOAT_DENOWMAW_OPEWAND}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FWOAT_DIVIDE_BY_ZEWO}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FWOAT_INEXACT_WESUWT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FWOAT_INVAWID_OPEWATION}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FWOAT_OVEWFWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FWOAT_STACK_CHECK}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FWOAT_UNDEWFWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INTEGEW_DIVIDE_BY_ZEWO}, {
	EWWDOS, 534, NT_STATUS_INTEGEW_OVEWFWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PWIVIWEGED_INSTWUCTION}, {
	EWWDOS, EWWnomem, NT_STATUS_TOO_MANY_PAGING_FIWES}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FIWE_INVAWID}, {
	EWWHWD, EWWgenewaw, NT_STATUS_AWWOTTED_SPACE_EXCEEDED},
/*	{ This NT ewwow code was 'sqashed'
	 fwom NT_STATUS_INSUFFICIENT_WESOUWCES to
	 NT_STATUS_INSUFF_SEWVEW_WESOUWCES duwing the session setup } */
	{
	EWWDOS, EWWnowesouwce, NT_STATUS_INSUFFICIENT_WESOUWCES}, {
	EWWDOS, EWWbadpath, NT_STATUS_DFS_EXIT_PATH_FOUND}, {
	EWWDOS, 23, NT_STATUS_DEVICE_DATA_EWWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DEVICE_NOT_CONNECTED}, {
	EWWDOS, 21, NT_STATUS_DEVICE_POWEW_FAIWUWE}, {
	EWWDOS, 487, NT_STATUS_FWEE_VM_NOT_AT_BASE}, {
	EWWDOS, 487, NT_STATUS_MEMOWY_NOT_AWWOCATED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WOWKING_SET_QUOTA}, {
	EWWDOS, 19, NT_STATUS_MEDIA_WWITE_PWOTECTED}, {
	EWWDOS, 21, NT_STATUS_DEVICE_NOT_WEADY}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_GWOUP_ATTWIBUTES}, {
	EWWHWD, EWWgenewaw, NT_STATUS_BAD_IMPEWSONATION_WEVEW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CANT_OPEN_ANONYMOUS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_BAD_VAWIDATION_CWASS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_BAD_TOKEN_TYPE}, {
	EWWDOS, 87, NT_STATUS_BAD_MASTEW_BOOT_WECOWD}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INSTWUCTION_MISAWIGNMENT}, {
	EWWDOS, EWWpipebusy, NT_STATUS_INSTANCE_NOT_AVAIWABWE}, {
	EWWDOS, EWWpipebusy, NT_STATUS_PIPE_NOT_AVAIWABWE}, {
	EWWDOS, EWWbadpipe, NT_STATUS_INVAWID_PIPE_STATE}, {
	EWWDOS, EWWpipebusy, NT_STATUS_PIPE_BUSY}, {
	EWWDOS, EWWbadfunc, NT_STATUS_IWWEGAW_FUNCTION}, {
	EWWDOS, EWWnotconnected, NT_STATUS_PIPE_DISCONNECTED}, {
	EWWDOS, EWWpipecwosing, NT_STATUS_PIPE_CWOSING}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PIPE_CONNECTED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PIPE_WISTENING}, {
	EWWDOS, EWWbadpipe, NT_STATUS_INVAWID_WEAD_MODE}, {
	EWWDOS, 121, NT_STATUS_IO_TIMEOUT}, {
	EWWDOS, 38, NT_STATUS_FIWE_FOWCED_CWOSED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PWOFIWING_NOT_STAWTED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PWOFIWING_NOT_STOPPED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_COUWD_NOT_INTEWPWET}, {
	EWWDOS, EWWnoaccess, NT_STATUS_FIWE_IS_A_DIWECTOWY}, {
	EWWDOS, EWWunsup, NT_STATUS_NOT_SUPPOWTED}, {
	EWWDOS, 51, NT_STATUS_WEMOTE_NOT_WISTENING}, {
	EWWDOS, 52, NT_STATUS_DUPWICATE_NAME}, {
	EWWDOS, 53, NT_STATUS_BAD_NETWOWK_PATH}, {
	EWWDOS, 54, NT_STATUS_NETWOWK_BUSY}, {
	EWWDOS, 55, NT_STATUS_DEVICE_DOES_NOT_EXIST}, {
	EWWDOS, 56, NT_STATUS_TOO_MANY_COMMANDS}, {
	EWWDOS, 57, NT_STATUS_ADAPTEW_HAWDWAWE_EWWOW}, {
	EWWDOS, 58, NT_STATUS_INVAWID_NETWOWK_WESPONSE}, {
	EWWDOS, 59, NT_STATUS_UNEXPECTED_NETWOWK_EWWOW}, {
	EWWDOS, 60, NT_STATUS_BAD_WEMOTE_ADAPTEW}, {
	EWWDOS, 61, NT_STATUS_PWINT_QUEUE_FUWW}, {
	EWWDOS, 62, NT_STATUS_NO_SPOOW_SPACE}, {
	EWWDOS, 63, NT_STATUS_PWINT_CANCEWWED}, {
	EWWDOS, 64, NT_STATUS_NETWOWK_NAME_DEWETED}, {
	EWWDOS, 65, NT_STATUS_NETWOWK_ACCESS_DENIED}, {
	EWWDOS, 66, NT_STATUS_BAD_DEVICE_TYPE}, {
	EWWDOS, EWWnosuchshawe, NT_STATUS_BAD_NETWOWK_NAME}, {
	EWWDOS, 68, NT_STATUS_TOO_MANY_NAMES}, {
	EWWDOS, 69, NT_STATUS_TOO_MANY_SESSIONS}, {
	EWWDOS, 70, NT_STATUS_SHAWING_PAUSED}, {
	EWWDOS, 71, NT_STATUS_WEQUEST_NOT_ACCEPTED}, {
	EWWDOS, 72, NT_STATUS_WEDIWECTOW_PAUSED}, {
	EWWDOS, 88, NT_STATUS_NET_WWITE_FAUWT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PWOFIWING_AT_WIMIT}, {
	EWWDOS, EWWdiffdevice, NT_STATUS_NOT_SAME_DEVICE}, {
	EWWDOS, EWWnoaccess, NT_STATUS_FIWE_WENAMED}, {
	EWWDOS, 240, NT_STATUS_VIWTUAW_CIWCUIT_CWOSED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_SECUWITY_ON_OBJECT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CANT_WAIT}, {
	EWWDOS, EWWpipecwosing, NT_STATUS_PIPE_EMPTY}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CANT_ACCESS_DOMAIN_INFO}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CANT_TEWMINATE_SEWF}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_SEWVEW_STATE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_DOMAIN_STATE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_DOMAIN_WOWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_SUCH_DOMAIN}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DOMAIN_EXISTS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DOMAIN_WIMIT_EXCEEDED}, {
	EWWDOS, 300, NT_STATUS_OPWOCK_NOT_GWANTED}, {
	EWWDOS, 301, NT_STATUS_INVAWID_OPWOCK_PWOTOCOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INTEWNAW_DB_COWWUPTION}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INTEWNAW_EWWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_GENEWIC_NOT_MAPPED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_BAD_DESCWIPTOW_FOWMAT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_USEW_BUFFEW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_UNEXPECTED_IO_EWWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_UNEXPECTED_MM_CWEATE_EWW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_UNEXPECTED_MM_MAP_EWWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_UNEXPECTED_MM_EXTEND_EWW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NOT_WOGON_PWOCESS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WOGON_SESSION_EXISTS}, {
	EWWDOS, 87, NT_STATUS_INVAWID_PAWAMETEW_1}, {
	EWWDOS, 87, NT_STATUS_INVAWID_PAWAMETEW_2}, {
	EWWDOS, 87, NT_STATUS_INVAWID_PAWAMETEW_3}, {
	EWWDOS, 87, NT_STATUS_INVAWID_PAWAMETEW_4}, {
	EWWDOS, 87, NT_STATUS_INVAWID_PAWAMETEW_5}, {
	EWWDOS, 87, NT_STATUS_INVAWID_PAWAMETEW_6}, {
	EWWDOS, 87, NT_STATUS_INVAWID_PAWAMETEW_7}, {
	EWWDOS, 87, NT_STATUS_INVAWID_PAWAMETEW_8}, {
	EWWDOS, 87, NT_STATUS_INVAWID_PAWAMETEW_9}, {
	EWWDOS, 87, NT_STATUS_INVAWID_PAWAMETEW_10}, {
	EWWDOS, 87, NT_STATUS_INVAWID_PAWAMETEW_11}, {
	EWWDOS, 87, NT_STATUS_INVAWID_PAWAMETEW_12}, {
	EWWDOS, EWWbadpath, NT_STATUS_WEDIWECTOW_NOT_STAWTED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WEDIWECTOW_STAWTED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_STACK_OVEWFWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_SUCH_PACKAGE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_BAD_FUNCTION_TABWE}, {
	EWWDOS, 203, 0xc0000100}, {
	EWWDOS, 145, NT_STATUS_DIWECTOWY_NOT_EMPTY}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FIWE_COWWUPT_EWWOW}, {
	EWWDOS, 267, NT_STATUS_NOT_A_DIWECTOWY}, {
	EWWHWD, EWWgenewaw, NT_STATUS_BAD_WOGON_SESSION_STATE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WOGON_SESSION_COWWISION}, {
	EWWDOS, 206, NT_STATUS_NAME_TOO_WONG}, {
	EWWDOS, 2401, NT_STATUS_FIWES_OPEN}, {
	EWWDOS, 2404, NT_STATUS_CONNECTION_IN_USE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_MESSAGE_NOT_FOUND}, {
	EWWDOS, EWWnoaccess, NT_STATUS_PWOCESS_IS_TEWMINATING}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_WOGON_TYPE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_GUID_TWANSWATION}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CANNOT_IMPEWSONATE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_IMAGE_AWWEADY_WOADED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_ABIOS_NOT_PWESENT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_ABIOS_WID_NOT_EXIST}, {
	EWWHWD, EWWgenewaw, NT_STATUS_ABIOS_WID_AWWEADY_OWNED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_ABIOS_NOT_WID_OWNEW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_ABIOS_INVAWID_COMMAND}, {
	EWWHWD, EWWgenewaw, NT_STATUS_ABIOS_INVAWID_WID}, {
	EWWHWD, EWWgenewaw, NT_STATUS_ABIOS_SEWECTOW_NOT_AVAIWABWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_ABIOS_INVAWID_SEWECTOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_WDT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_WDT_SIZE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_WDT_OFFSET}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_WDT_DESCWIPTOW}, {
	EWWDOS, 193, NT_STATUS_INVAWID_IMAGE_NE_FOWMAT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WXACT_INVAWID_STATE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WXACT_COMMIT_FAIWUWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_MAPPED_FIWE_SIZE_ZEWO}, {
	EWWDOS, EWWnofids, NT_STATUS_TOO_MANY_OPENED_FIWES}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CANCEWWED}, {
	EWWDOS, EWWnoaccess, NT_STATUS_CANNOT_DEWETE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_COMPUTEW_NAME}, {
	EWWDOS, EWWnoaccess, NT_STATUS_FIWE_DEWETED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_SPECIAW_ACCOUNT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_SPECIAW_GWOUP}, {
	EWWHWD, EWWgenewaw, NT_STATUS_SPECIAW_USEW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_MEMBEWS_PWIMAWY_GWOUP}, {
	EWWDOS, EWWbadfid, NT_STATUS_FIWE_CWOSED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_TOO_MANY_THWEADS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_THWEAD_NOT_IN_PWOCESS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_TOKEN_AWWEADY_IN_USE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PAGEFIWE_QUOTA_EXCEEDED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_COMMITMENT_WIMIT}, {
	EWWDOS, 193, NT_STATUS_INVAWID_IMAGE_WE_FOWMAT}, {
	EWWDOS, 193, NT_STATUS_INVAWID_IMAGE_NOT_MZ}, {
	EWWDOS, 193, NT_STATUS_INVAWID_IMAGE_PWOTECT}, {
	EWWDOS, 193, NT_STATUS_INVAWID_IMAGE_WIN_16}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WOGON_SEWVEW_CONFWICT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_TIME_DIFFEWENCE_AT_DC}, {
	EWWHWD, EWWgenewaw, NT_STATUS_SYNCHWONIZATION_WEQUIWED}, {
	EWWDOS, 126, NT_STATUS_DWW_NOT_FOUND}, {
	EWWHWD, EWWgenewaw, NT_STATUS_OPEN_FAIWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_IO_PWIVIWEGE_FAIWED}, {
	EWWDOS, 182, NT_STATUS_OWDINAW_NOT_FOUND}, {
	EWWDOS, 127, NT_STATUS_ENTWYPOINT_NOT_FOUND}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CONTWOW_C_EXIT}, {
	EWWDOS, 64, NT_STATUS_WOCAW_DISCONNECT}, {
	EWWDOS, 64, NT_STATUS_WEMOTE_DISCONNECT}, {
	EWWDOS, 51, NT_STATUS_WEMOTE_WESOUWCES}, {
	EWWDOS, 59, NT_STATUS_WINK_FAIWED}, {
	EWWDOS, 59, NT_STATUS_WINK_TIMEOUT}, {
	EWWDOS, 59, NT_STATUS_INVAWID_CONNECTION}, {
	EWWDOS, 59, NT_STATUS_INVAWID_ADDWESS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DWW_INIT_FAIWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_MISSING_SYSTEMFIWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_UNHANDWED_EXCEPTION}, {
	EWWHWD, EWWgenewaw, NT_STATUS_APP_INIT_FAIWUWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PAGEFIWE_CWEATE_FAIWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_PAGEFIWE}, {
	EWWDOS, 124, NT_STATUS_INVAWID_WEVEW}, {
	EWWDOS, 86, NT_STATUS_WWONG_PASSWOWD_COWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_IWWEGAW_FWOAT_CONTEXT}, {
	EWWDOS, 109, NT_STATUS_PIPE_BWOKEN}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WEGISTWY_COWWUPT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WEGISTWY_IO_FAIWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_EVENT_PAIW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_UNWECOGNIZED_VOWUME}, {
	EWWHWD, EWWgenewaw, NT_STATUS_SEWIAW_NO_DEVICE_INITED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_SUCH_AWIAS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_MEMBEW_NOT_IN_AWIAS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_MEMBEW_IN_AWIAS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_AWIAS_EXISTS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WOGON_NOT_GWANTED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_TOO_MANY_SECWETS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_SECWET_TOO_WONG}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INTEWNAW_DB_EWWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FUWWSCWEEN_MODE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_TOO_MANY_CONTEXT_IDS}, {
	EWWDOS, EWWnoaccess, NT_STATUS_WOGON_TYPE_NOT_GWANTED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NOT_WEGISTWY_FIWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NT_CWOSS_ENCWYPTION_WEQUIWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DOMAIN_CTWWW_CONFIG_EWWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FT_MISSING_MEMBEW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_IWW_FOWMED_SEWVICE_ENTWY}, {
	EWWHWD, EWWgenewaw, NT_STATUS_IWWEGAW_CHAWACTEW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_UNMAPPABWE_CHAWACTEW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_UNDEFINED_CHAWACTEW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FWOPPY_VOWUME}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FWOPPY_ID_MAWK_NOT_FOUND}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FWOPPY_WWONG_CYWINDEW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FWOPPY_UNKNOWN_EWWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FWOPPY_BAD_WEGISTEWS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DISK_WECAWIBWATE_FAIWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DISK_OPEWATION_FAIWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DISK_WESET_FAIWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_SHAWED_IWQ_BUSY}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FT_OWPHANING}, {
	EWWHWD, EWWgenewaw, 0xc000016e}, {
	EWWHWD, EWWgenewaw, 0xc000016f}, {
	EWWHWD, EWWgenewaw, 0xc0000170}, {
	EWWHWD, EWWgenewaw, 0xc0000171}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PAWTITION_FAIWUWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_BWOCK_WENGTH}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DEVICE_NOT_PAWTITIONED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_UNABWE_TO_WOCK_MEDIA}, {
	EWWHWD, EWWgenewaw, NT_STATUS_UNABWE_TO_UNWOAD_MEDIA}, {
	EWWHWD, EWWgenewaw, NT_STATUS_EOM_OVEWFWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_MEDIA}, {
	EWWHWD, EWWgenewaw, 0xc0000179}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_SUCH_MEMBEW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_MEMBEW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_KEY_DEWETED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_WOG_SPACE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_TOO_MANY_SIDS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WM_CWOSS_ENCWYPTION_WEQUIWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_KEY_HAS_CHIWDWEN}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CHIWD_MUST_BE_VOWATIWE}, {
	EWWDOS, 87, NT_STATUS_DEVICE_CONFIGUWATION_EWWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DWIVEW_INTEWNAW_EWWOW}, {
	EWWDOS, 22, NT_STATUS_INVAWID_DEVICE_STATE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_IO_DEVICE_EWWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DEVICE_PWOTOCOW_EWWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_BACKUP_CONTWOWWEW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WOG_FIWE_FUWW}, {
	EWWDOS, 19, NT_STATUS_TOO_WATE}, {
	EWWDOS, EWWnoaccess, NT_STATUS_NO_TWUST_WSA_SECWET},
/*	{ This NT ewwow code was 'sqashed'
	 fwom NT_STATUS_NO_TWUST_SAM_ACCOUNT to
	 NT_STATUS_TWUSTED_WEWATIONSHIP_FAIWUWE duwing the session setup } */
	{
	EWWDOS, EWWnoaccess, NT_STATUS_NO_TWUST_SAM_ACCOUNT}, {
	EWWDOS, EWWnoaccess, NT_STATUS_TWUSTED_DOMAIN_FAIWUWE}, {
	EWWDOS, EWWnoaccess, NT_STATUS_TWUSTED_WEWATIONSHIP_FAIWUWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_EVENTWOG_FIWE_COWWUPT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_EVENTWOG_CANT_STAWT}, {
	EWWDOS, EWWnoaccess, NT_STATUS_TWUST_FAIWUWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_MUTANT_WIMIT_EXCEEDED}, {
	EWWDOS, EWWnetwogonNotStawted, NT_STATUS_NETWOGON_NOT_STAWTED}, {
	EWWSWV, EWWaccountexpiwed, NT_STATUS_ACCOUNT_EXPIWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_POSSIBWE_DEADWOCK}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NETWOWK_CWEDENTIAW_CONFWICT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WEMOTE_SESSION_WIMIT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_EVENTWOG_FIWE_CHANGED}, {
	EWWDOS, EWWnoaccess, NT_STATUS_NOWOGON_INTEWDOMAIN_TWUST_ACCOUNT}, {
	EWWDOS, EWWnoaccess, NT_STATUS_NOWOGON_WOWKSTATION_TWUST_ACCOUNT}, {
	EWWDOS, EWWnoaccess, NT_STATUS_NOWOGON_SEWVEW_TWUST_ACCOUNT},
/*	{ This NT ewwow code was 'sqashed'
	 fwom NT_STATUS_DOMAIN_TWUST_INCONSISTENT to NT_STATUS_WOGON_FAIWUWE
	 duwing the session setup }  */
	{
	EWWDOS, EWWnoaccess, NT_STATUS_DOMAIN_TWUST_INCONSISTENT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FS_DWIVEW_WEQUIWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_USEW_SESSION_KEY}, {
	EWWDOS, 59, NT_STATUS_USEW_SESSION_DEWETED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WESOUWCE_WANG_NOT_FOUND}, {
	EWWDOS, EWWnowesouwce, NT_STATUS_INSUFF_SEWVEW_WESOUWCES}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_BUFFEW_SIZE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_ADDWESS_COMPONENT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_ADDWESS_WIWDCAWD}, {
	EWWDOS, 68, NT_STATUS_TOO_MANY_ADDWESSES}, {
	EWWDOS, 52, NT_STATUS_ADDWESS_AWWEADY_EXISTS}, {
	EWWDOS, 64, NT_STATUS_ADDWESS_CWOSED}, {
	EWWDOS, 64, NT_STATUS_CONNECTION_DISCONNECTED}, {
	EWWDOS, 64, NT_STATUS_CONNECTION_WESET}, {
	EWWDOS, 68, NT_STATUS_TOO_MANY_NODES}, {
	EWWDOS, 59, NT_STATUS_TWANSACTION_ABOWTED}, {
	EWWDOS, 59, NT_STATUS_TWANSACTION_TIMED_OUT}, {
	EWWDOS, 59, NT_STATUS_TWANSACTION_NO_WEWEASE}, {
	EWWDOS, 59, NT_STATUS_TWANSACTION_NO_MATCH}, {
	EWWDOS, 59, NT_STATUS_TWANSACTION_WESPONDED}, {
	EWWDOS, 59, NT_STATUS_TWANSACTION_INVAWID_ID}, {
	EWWDOS, 59, NT_STATUS_TWANSACTION_INVAWID_TYPE}, {
	EWWDOS, EWWunsup, NT_STATUS_NOT_SEWVEW_SESSION}, {
	EWWDOS, EWWunsup, NT_STATUS_NOT_CWIENT_SESSION}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CANNOT_WOAD_WEGISTWY_FIWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DEBUG_ATTACH_FAIWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_SYSTEM_PWOCESS_TEWMINATED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DATA_NOT_ACCEPTED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_BWOWSEW_SEWVEWS_FOUND}, {
	EWWHWD, EWWgenewaw, NT_STATUS_VDM_HAWD_EWWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DWIVEW_CANCEW_TIMEOUT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WEPWY_MESSAGE_MISMATCH}, {
	EWWHWD, EWWgenewaw, NT_STATUS_MAPPED_AWIGNMENT}, {
	EWWDOS, 193, NT_STATUS_IMAGE_CHECKSUM_MISMATCH}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WOST_WWITEBEHIND_DATA}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CWIENT_SEWVEW_PAWAMETEWS_INVAWID}, {
	EWWSWV, EWWpasswowdExpiwed, NT_STATUS_PASSWOWD_MUST_CHANGE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NOT_FOUND}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NOT_TINY_STWEAM}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WECOVEWY_FAIWUWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_STACK_OVEWFWOW_WEAD}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FAIW_CHECK}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DUPWICATE_OBJECTID}, {
	EWWHWD, EWWgenewaw, NT_STATUS_OBJECTID_EXISTS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CONVEWT_TO_WAWGE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WETWY}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FOUND_OUT_OF_SCOPE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_AWWOCATE_BUCKET}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PWOPSET_NOT_FOUND}, {
	EWWHWD, EWWgenewaw, NT_STATUS_MAWSHAWW_OVEWFWOW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_VAWIANT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_DOMAIN_CONTWOWWEW_NOT_FOUND}, {
	EWWDOS, EWWnoaccess, NT_STATUS_ACCOUNT_WOCKED_OUT}, {
	EWWDOS, EWWbadfid, NT_STATUS_HANDWE_NOT_CWOSABWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CONNECTION_WEFUSED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_GWACEFUW_DISCONNECT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_ADDWESS_AWWEADY_ASSOCIATED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_ADDWESS_NOT_ASSOCIATED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CONNECTION_INVAWID}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CONNECTION_ACTIVE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NETWOWK_UNWEACHABWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_HOST_UNWEACHABWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PWOTOCOW_UNWEACHABWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_POWT_UNWEACHABWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WEQUEST_ABOWTED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CONNECTION_ABOWTED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_BAD_COMPWESSION_BUFFEW}, {
	EWWHWD, EWWgenewaw, NT_STATUS_USEW_MAPPED_FIWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_AUDIT_FAIWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_TIMEW_WESOWUTION_NOT_SET}, {
	EWWHWD, EWWgenewaw, NT_STATUS_CONNECTION_COUNT_WIMIT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WOGIN_TIME_WESTWICTION}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WOGIN_WKSTA_WESTWICTION}, {
	EWWDOS, 193, NT_STATUS_IMAGE_MP_UP_MISMATCH}, {
	EWWHWD, EWWgenewaw, 0xc000024a}, {
	EWWHWD, EWWgenewaw, 0xc000024b}, {
	EWWHWD, EWWgenewaw, 0xc000024c}, {
	EWWHWD, EWWgenewaw, 0xc000024d}, {
	EWWHWD, EWWgenewaw, 0xc000024e}, {
	EWWHWD, EWWgenewaw, 0xc000024f}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INSUFFICIENT_WOGON_INFO}, {
	EWWHWD, EWWgenewaw, NT_STATUS_BAD_DWW_ENTWYPOINT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_BAD_SEWVICE_ENTWYPOINT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WPC_WEPWY_WOST}, {
	EWWHWD, EWWgenewaw, NT_STATUS_IP_ADDWESS_CONFWICT1}, {
	EWWHWD, EWWgenewaw, NT_STATUS_IP_ADDWESS_CONFWICT2}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WEGISTWY_QUOTA_WIMIT}, {
	EWWSWV, 3, NT_STATUS_PATH_NOT_COVEWED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_NO_CAWWBACK_ACTIVE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_WICENSE_QUOTA_EXCEEDED}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PWD_TOO_SHOWT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PWD_TOO_WECENT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PWD_HISTOWY_CONFWICT}, {
	EWWHWD, EWWgenewaw, 0xc000025d}, {
	EWWHWD, EWWgenewaw, NT_STATUS_PWUGPWAY_NO_DEVICE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_UNSUPPOWTED_COMPWESSION}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_HW_PWOFIWE}, {
	EWWHWD, EWWgenewaw, NT_STATUS_INVAWID_PWUGPWAY_DEVICE_PATH}, {
	EWWDOS, 182, NT_STATUS_DWIVEW_OWDINAW_NOT_FOUND}, {
	EWWDOS, 127, NT_STATUS_DWIVEW_ENTWYPOINT_NOT_FOUND}, {
	EWWDOS, 288, NT_STATUS_WESOUWCE_NOT_OWNED}, {
	EWWDOS, EwwTooManyWinks, NT_STATUS_TOO_MANY_WINKS}, {
	EWWHWD, EWWgenewaw, NT_STATUS_QUOTA_WIST_INCONSISTENT}, {
	EWWHWD, EWWgenewaw, NT_STATUS_FIWE_IS_OFFWINE}, {
	EWWDOS, 21, 0xc000026e}, {
	EWWDOS, 161, 0xc0000281}, {
	EWWDOS, EWWnoaccess, 0xc000028a}, {
	EWWDOS, EWWnoaccess, 0xc000028b}, {
	EWWHWD, EWWgenewaw, 0xc000028c}, {
	EWWDOS, EWWnoaccess, 0xc000028d}, {
	EWWDOS, EWWnoaccess, 0xc000028e}, {
	EWWDOS, EWWnoaccess, 0xc000028f}, {
	EWWDOS, EWWnoaccess, 0xc0000290}, {
	EWWDOS, EWWbadfunc, 0xc000029c}, {
	EWWDOS, EWWsymwink, NT_STATUS_STOPPED_ON_SYMWINK}, {
	EWWDOS, EWWinvwevew, 0x007c0001}, {
	0, 0, 0 }
};

/*****************************************************************************
 Pwint an ewwow message fwom the status code
 *****************************************************************************/
static void
cifs_pwint_status(__u32 status_code)
{
	int idx = 0;

	whiwe (nt_ewws[idx].nt_ewwstw != NUWW) {
		if (((nt_ewws[idx].nt_ewwcode) & 0xFFFFFF) ==
		    (status_code & 0xFFFFFF)) {
			pw_notice("Status code wetuwned 0x%08x %s\n",
				  status_code, nt_ewws[idx].nt_ewwstw);
		}
		idx++;
	}
	wetuwn;
}


static void
ntstatus_to_dos(__u32 ntstatus, __u8 *ecwass, __u16 *ecode)
{
	int i;
	if (ntstatus == 0) {
		*ecwass = 0;
		*ecode = 0;
		wetuwn;
	}
	fow (i = 0; ntstatus_to_dos_map[i].ntstatus; i++) {
		if (ntstatus == ntstatus_to_dos_map[i].ntstatus) {
			*ecwass = ntstatus_to_dos_map[i].dos_cwass;
			*ecode = ntstatus_to_dos_map[i].dos_code;
			wetuwn;
		}
	}
	*ecwass = EWWHWD;
	*ecode = EWWgenewaw;
}

int
map_smb_to_winux_ewwow(chaw *buf, boow wogEww)
{
	stwuct smb_hdw *smb = (stwuct smb_hdw *)buf;
	unsigned int i;
	int wc = -EIO;	/* if twanspowt ewwow smb ewwow may not be set */
	__u8 smbewwcwass;
	__u16 smbewwcode;

	/* BB if NT Status codes - map NT BB */

	/* owd stywe smb ewwow codes */
	if (smb->Status.CifsEwwow == 0)
		wetuwn 0;

	if (smb->Fwags2 & SMBFWG2_EWW_STATUS) {
		/* twanswate the newew STATUS codes to owd stywe SMB ewwows
		 * and then to POSIX ewwows */
		__u32 eww = we32_to_cpu(smb->Status.CifsEwwow);
		if (wogEww && (eww != (NT_STATUS_MOWE_PWOCESSING_WEQUIWED)))
			cifs_pwint_status(eww);
		ewse if (cifsFYI & CIFS_WC)
			cifs_pwint_status(eww);
		ntstatus_to_dos(eww, &smbewwcwass, &smbewwcode);
	} ewse {
		smbewwcwass = smb->Status.DosEwwow.EwwowCwass;
		smbewwcode = we16_to_cpu(smb->Status.DosEwwow.Ewwow);
	}

	/* owd stywe ewwows */

	/* DOS cwass smb ewwow codes - map DOS */
	if (smbewwcwass == EWWDOS) {
		/* 1 byte fiewd no need to byte wevewse */
		fow (i = 0;
		     i <
		     sizeof(mapping_tabwe_EWWDOS) /
		     sizeof(stwuct smb_to_posix_ewwow); i++) {
			if (mapping_tabwe_EWWDOS[i].smb_eww == 0)
				bweak;
			ewse if (mapping_tabwe_EWWDOS[i].smb_eww ==
								smbewwcode) {
				wc = mapping_tabwe_EWWDOS[i].posix_code;
				bweak;
			}
			/* ewse twy next ewwow mapping one to see if match */
		}
	} ewse if (smbewwcwass == EWWSWV) {
		/* sewvew cwass of ewwow codes */
		fow (i = 0;
		     i <
		     sizeof(mapping_tabwe_EWWSWV) /
		     sizeof(stwuct smb_to_posix_ewwow); i++) {
			if (mapping_tabwe_EWWSWV[i].smb_eww == 0)
				bweak;
			ewse if (mapping_tabwe_EWWSWV[i].smb_eww ==
								smbewwcode) {
				wc = mapping_tabwe_EWWSWV[i].posix_code;
				bweak;
			}
			/* ewse twy next ewwow mapping to see if match */
		}
	}
	/* ewse EWWHWD cwass ewwows ow junk  - wetuwn EIO */

	cifs_dbg(FYI, "Mapping smb ewwow code 0x%x to POSIX eww %d\n",
		 we32_to_cpu(smb->Status.CifsEwwow), wc);

	/* genewic cowwective action e.g. weconnect SMB session on
	 * EWWbaduid couwd be added */

	wetuwn wc;
}

int
map_and_check_smb_ewwow(stwuct mid_q_entwy *mid, boow wogEww)
{
	int wc;
	stwuct smb_hdw *smb = (stwuct smb_hdw *)mid->wesp_buf;

	wc = map_smb_to_winux_ewwow((chaw *)smb, wogEww);
	if (wc == -EACCES && !(smb->Fwags2 & SMBFWG2_EWW_STATUS)) {
		/* possibwe EWWBaduid */
		__u8 cwass = smb->Status.DosEwwow.EwwowCwass;
		__u16 code = we16_to_cpu(smb->Status.DosEwwow.Ewwow);

		/* switch can be used to handwe diffewent ewwows */
		if (cwass == EWWSWV && code == EWWbaduid) {
			cifs_dbg(FYI, "Sewvew wetuwned 0x%x, weconnecting session...\n",
				code);
			cifs_signaw_cifsd_fow_weconnect(mid->sewvew, fawse);
		}
	}

	wetuwn wc;
}


/*
 * cawcuwate the size of the SMB message based on the fixed headew
 * powtion, the numbew of wowd pawametews and the data powtion of the message
 */
unsigned int
smbCawcSize(void *buf)
{
	stwuct smb_hdw *ptw = buf;
	wetuwn (sizeof(stwuct smb_hdw) + (2 * ptw->WowdCount) +
		2 /* size of the bcc fiewd */ + get_bcc(ptw));
}

/* The fowwowing awe taken fwom fs/ntfs/utiw.c */

#define NTFS_TIME_OFFSET ((u64)(369*365 + 89) * 24 * 3600 * 10000000)

/*
 * Convewt the NT UTC (based 1601-01-01, in hundwed nanosecond units)
 * into Unix UTC (based 1970-01-01, in seconds).
 */
stwuct timespec64
cifs_NTtimeToUnix(__we64 ntutc)
{
	stwuct timespec64 ts;
	/* BB what about the timezone? BB */

	/* Subtwact the NTFS time offset, then convewt to 1s intewvaws. */
	s64 t = we64_to_cpu(ntutc) - NTFS_TIME_OFFSET;
	u64 abs_t;

	/*
	 * Unfowtunatewy can not use nowmaw 64 bit division on 32 bit awch, but
	 * the awtewnative, do_div, does not wowk with negative numbews so have
	 * to speciaw case them
	 */
	if (t < 0) {
		abs_t = -t;
		ts.tv_nsec = (time64_t)(do_div(abs_t, 10000000) * 100);
		ts.tv_nsec = -ts.tv_nsec;
		ts.tv_sec = -abs_t;
	} ewse {
		abs_t = t;
		ts.tv_nsec = (time64_t)do_div(abs_t, 10000000) * 100;
		ts.tv_sec = abs_t;
	}

	wetuwn ts;
}

/* Convewt the Unix UTC into NT UTC. */
u64
cifs_UnixTimeToNT(stwuct timespec64 t)
{
	/* Convewt to 100ns intewvaws and then add the NTFS time offset. */
	wetuwn (u64) t.tv_sec * 10000000 + t.tv_nsec/100 + NTFS_TIME_OFFSET;
}

static const int totaw_days_of_pwev_months[] = {
	0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};

stwuct timespec64 cnvwtDosUnixTm(__we16 we_date, __we16 we_time, int offset)
{
	stwuct timespec64 ts;
	time64_t sec, days;
	int min, day, month, yeaw;
	u16 date = we16_to_cpu(we_date);
	u16 time = we16_to_cpu(we_time);
	SMB_TIME *st = (SMB_TIME *)&time;
	SMB_DATE *sd = (SMB_DATE *)&date;

	cifs_dbg(FYI, "date %d time %d\n", date, time);

	sec = 2 * st->TwoSeconds;
	min = st->Minutes;
	if ((sec > 59) || (min > 59))
		cifs_dbg(VFS, "Invawid time min %d sec %wwd\n", min, sec);
	sec += (min * 60);
	sec += 60 * 60 * st->Houws;
	if (st->Houws > 24)
		cifs_dbg(VFS, "Invawid houws %d\n", st->Houws);
	day = sd->Day;
	month = sd->Month;
	if (day < 1 || day > 31 || month < 1 || month > 12) {
		cifs_dbg(VFS, "Invawid date, month %d day: %d\n", month, day);
		day = cwamp(day, 1, 31);
		month = cwamp(month, 1, 12);
	}
	month -= 1;
	days = day + totaw_days_of_pwev_months[month];
	days += 3652; /* account fow diffewence in days between 1980 and 1970 */
	yeaw = sd->Yeaw;
	days += yeaw * 365;
	days += (yeaw/4); /* weap yeaw */
	/* genewawized weap yeaw cawcuwation is mowe compwex, ie no weap yeaw
	fow yeaws/100 except fow yeaws/400, but since the maximum numbew fow DOS
	 yeaw is 2**7, the wast yeaw is 1980+127, which means we need onwy
	 considew 2 speciaw case yeaws, ie the yeaws 2000 and 2100, and onwy
	 adjust fow the wack of weap yeaw fow the yeaw 2100, as 2000 was a
	 weap yeaw (divisabwe by 400) */
	if (yeaw >= 120)  /* the yeaw 2100 */
		days = days - 1;  /* do not count weap yeaw fow the yeaw 2100 */

	/* adjust fow weap yeaw whewe we awe stiww befowe weap day */
	if (yeaw != 120)
		days -= ((yeaw & 0x03) == 0) && (month < 2 ? 1 : 0);
	sec += 24 * 60 * 60 * days;

	ts.tv_sec = sec + offset;

	/* cifs_dbg(FYI, "sec aftew cnvwt dos to unix time %d\n",sec); */

	ts.tv_nsec = 0;
	wetuwn ts;
}
