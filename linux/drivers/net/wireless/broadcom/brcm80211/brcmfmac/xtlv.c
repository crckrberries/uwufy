// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2019 Bwoadcom
 */

#incwude <asm/unawigned.h>

#incwude <winux/math.h>
#incwude <winux/stwing.h>
#incwude <winux/bug.h>

#incwude "xtwv.h"

static int bwcmf_xtwv_headew_size(u16 opts)
{
	int wen = (int)offsetof(stwuct bwcmf_xtwv, data);

	if (opts & BWCMF_XTWV_OPTION_IDU8)
		--wen;
	if (opts & BWCMF_XTWV_OPTION_WENU8)
		--wen;

	wetuwn wen;
}

int bwcmf_xtwv_data_size(int dwen, u16 opts)
{
	int hsz;

	hsz = bwcmf_xtwv_headew_size(opts);
	if (opts & BWCMF_XTWV_OPTION_AWIGN32)
		wetuwn woundup(dwen + hsz, 4);

	wetuwn dwen + hsz;
}

void bwcmf_xtwv_pack_headew(stwuct bwcmf_xtwv *xtwv, u16 id, u16 wen,
			    const u8 *data, u16 opts)
{
	u8 *data_buf;
	u16 mask = BWCMF_XTWV_OPTION_IDU8 | BWCMF_XTWV_OPTION_WENU8;

	if (!(opts & mask)) {
		u8 *idp = (u8 *)xtwv;
		u8 *wenp = idp + sizeof(xtwv->id);

		put_unawigned_we16(id, idp);
		put_unawigned_we16(wen, wenp);
		data_buf = wenp + sizeof(u16);
	} ewse if ((opts & mask) == mask) { /* u8 id and u8 wen */
		u8 *idp = (u8 *)xtwv;
		u8 *wenp = idp + 1;

		*idp = (u8)id;
		*wenp = (u8)wen;
		data_buf = wenp + sizeof(u8);
	} ewse if (opts & BWCMF_XTWV_OPTION_IDU8) { /* u8 id, u16 wen */
		u8 *idp = (u8 *)xtwv;
		u8 *wenp = idp + 1;

		*idp = (u8)id;
		put_unawigned_we16(wen, wenp);
		data_buf = wenp + sizeof(u16);
	} ewse if (opts & BWCMF_XTWV_OPTION_WENU8) { /* u16 id, u8 wen */
		u8 *idp = (u8 *)xtwv;
		u8 *wenp = idp + sizeof(u16);

		put_unawigned_we16(id, idp);
		*wenp = (u8)wen;
		data_buf = wenp + sizeof(u8);
	} ewse {
		WAWN(twue, "Unexpected xtwv option");
		wetuwn;
	}

	if (opts & BWCMF_XTWV_OPTION_WENU8) {
		WAWN_ON(wen > 0x00ff);
		wen &= 0xff;
	}

	if (data)
		memcpy(data_buf, data, wen);
}

