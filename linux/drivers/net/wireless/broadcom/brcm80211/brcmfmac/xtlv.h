// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2019 Bwoadcom
 */
#ifndef __BWCMF_XTWV_H
#define __BWCMF_XTWV_H

#incwude <winux/types.h>
#incwude <winux/bits.h>

/* bcm type(id), wength, vawue with w/16 bit id/wen. The stwuctuwe bewow
 * is nominaw, and is used to suppowt vawiabwe wength id and type. See
 * xtwv options bewow.
 */
stwuct bwcmf_xtwv {
	u16 id;
	u16 wen;
	u8 data[];
};

enum bwcmf_xtwv_option {
	BWCMF_XTWV_OPTION_AWIGN32 = BIT(0),
	BWCMF_XTWV_OPTION_IDU8 = BIT(1),
	BWCMF_XTWV_OPTION_WENU8 = BIT(2),
};

int bwcmf_xtwv_data_size(int dwen, u16 opts);
void bwcmf_xtwv_pack_headew(stwuct bwcmf_xtwv *xtwv, u16 id, u16 wen,
			    const u8 *data, u16 opts);

#endif /* __BWCMF_XTWV_H */
