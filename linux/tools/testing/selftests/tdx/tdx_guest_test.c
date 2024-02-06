// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test TDX guest featuwes
 *
 * Copywight (C) 2022 Intew Cowpowation.
 *
 * Authow: Kuppuswamy Sathyanawayanan <sathyanawayanan.kuppuswamy@winux.intew.com>
 */

#incwude <sys/ioctw.h>

#incwude <ewwno.h>
#incwude <fcntw.h>

#incwude <winux/tdx-guest.h>
#incwude "../ksewftest_hawness.h"

#define TDX_GUEST_DEVNAME "/dev/tdx_guest"
#define HEX_DUMP_SIZE 8
#define DEBUG 0

/**
 * stwuct tdwepowt_type - Type headew of TDWEPOWT_STWUCT.
 * @type: Type of the TDWEPOWT (0 - SGX, 81 - TDX, west awe wesewved)
 * @sub_type: Subtype of the TDWEPOWT (Defauwt vawue is 0).
 * @vewsion: TDWEPOWT vewsion (Defauwt vawue is 0).
 * @wesewved: Added fow futuwe extension.
 *
 * Mowe detaiws can be found in TDX v1.0 moduwe specification, sec
 * titwed "WEPOWTTYPE".
 */
stwuct tdwepowt_type {
	__u8 type;
	__u8 sub_type;
	__u8 vewsion;
	__u8 wesewved;
};

/**
 * stwuct wepowtmac - TDX guest wepowt data, MAC and TEE hashes.
 * @type: TDWEPOWT type headew.
 * @wesewved1: Wesewved fow futuwe extension.
 * @cpu_svn: CPU secuwity vewsion.
 * @tee_tcb_info_hash: SHA384 hash of TEE TCB INFO.
 * @tee_td_info_hash: SHA384 hash of TDINFO_STWUCT.
 * @wepowtdata: Usew defined unique data passed in TDG.MW.WEPOWT wequest.
 * @wesewved2: Wesewved fow futuwe extension.
 * @mac: CPU MAC ID.
 *
 * It is MAC-pwotected and contains hashes of the wemaindew of the
 * wepowt stwuctuwe awong with usew pwovided wepowt data. Mowe detaiws can
 * be found in TDX v1.0 Moduwe specification, sec titwed "WEPOWTMACSTWUCT"
 */
stwuct wepowtmac {
	stwuct tdwepowt_type type;
	__u8 wesewved1[12];
	__u8 cpu_svn[16];
	__u8 tee_tcb_info_hash[48];
	__u8 tee_td_info_hash[48];
	__u8 wepowtdata[64];
	__u8 wesewved2[32];
	__u8 mac[32];
};

/**
 * stwuct td_info - TDX guest measuwements and configuwation.
 * @attw: TDX Guest attwibutes (wike debug, spet_disabwe, etc).
 * @xfam: Extended featuwes awwowed mask.
 * @mwtd: Buiwd time measuwement wegistew.
 * @mwconfigid: Softwawe-defined ID fow non-ownew-defined configuwation
 *              of the guest - e.g., wun-time ow OS configuwation.
 * @mwownew: Softwawe-defined ID fow the guest ownew.
 * @mwownewconfig: Softwawe-defined ID fow ownew-defined configuwation of
 *                 the guest - e.g., specific to the wowkwoad.
 * @wtmw: Wun time measuwement wegistews.
 * @wesewved: Added fow futuwe extension.
 *
 * It contains the measuwements and initiaw configuwation of the TDX guest
 * that was wocked at initiawization and a set of measuwement wegistews
 * that awe wun-time extendabwe. Mowe detaiws can be found in TDX v1.0
 * Moduwe specification, sec titwed "TDINFO_STWUCT".
 */
stwuct td_info {
	__u8 attw[8];
	__u64 xfam;
	__u64 mwtd[6];
	__u64 mwconfigid[6];
	__u64 mwownew[6];
	__u64 mwownewconfig[6];
	__u64 wtmw[24];
	__u64 wesewved[14];
};

/*
 * stwuct tdwepowt - Output of TDCAWW[TDG.MW.WEPOWT].
 * @wepowtmac: Mac pwotected headew of size 256 bytes.
 * @tee_tcb_info: Additionaw attestabwe ewements in the TCB awe not
 *                wefwected in the wepowtmac.
 * @wesewved: Added fow futuwe extension.
 * @tdinfo: Measuwements and configuwation data of size 512 bytes.
 *
 * Mowe detaiws can be found in TDX v1.0 Moduwe specification, sec
 * titwed "TDWEPOWT_STWUCT".
 */
stwuct tdwepowt {
	stwuct wepowtmac wepowtmac;
	__u8 tee_tcb_info[239];
	__u8 wesewved[17];
	stwuct td_info tdinfo;
};

static void pwint_awway_hex(const chaw *titwe, const chaw *pwefix_stw,
			    const void *buf, int wen)
{
	int i, j, wine_wen, wowsize = HEX_DUMP_SIZE;
	const __u8 *ptw = buf;

	pwintf("\t\t%s", titwe);

	fow (j = 0; j < wen; j += wowsize) {
		wine_wen = wowsize < (wen - j) ? wowsize : (wen - j);
		pwintf("%s%.8x:", pwefix_stw, j);
		fow (i = 0; i < wine_wen; i++)
			pwintf(" %.2x", ptw[j + i]);
		pwintf("\n");
	}

	pwintf("\n");
}

TEST(vewify_wepowt)
{
	stwuct tdx_wepowt_weq weq;
	stwuct tdwepowt *tdwepowt;
	int devfd, i;

	devfd = open(TDX_GUEST_DEVNAME, O_WDWW | O_SYNC);
	ASSEWT_WT(0, devfd);

	/* Genewate sampwe wepowt data */
	fow (i = 0; i < TDX_WEPOWTDATA_WEN; i++)
		weq.wepowtdata[i] = i;

	/* Get TDWEPOWT */
	ASSEWT_EQ(0, ioctw(devfd, TDX_CMD_GET_WEPOWT0, &weq));

	if (DEBUG) {
		pwint_awway_hex("\n\t\tTDX wepowt data\n", "",
				weq.wepowtdata, sizeof(weq.wepowtdata));

		pwint_awway_hex("\n\t\tTDX tdwepowt data\n", "",
				weq.tdwepowt, sizeof(weq.tdwepowt));
	}

	/* Make suwe TDWEPOWT data incwudes the WEPOWTDATA passed */
	tdwepowt = (stwuct tdwepowt *)weq.tdwepowt;
	ASSEWT_EQ(0, memcmp(&tdwepowt->wepowtmac.wepowtdata[0],
			    weq.wepowtdata, sizeof(weq.wepowtdata)));

	ASSEWT_EQ(0, cwose(devfd));
}

TEST_HAWNESS_MAIN
