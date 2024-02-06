/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * hdwc.h  --  Genewaw puwpose ISDN HDWC decodew.
 *
 * Impwementation of a HDWC decodew/encodew in softwawe.
 * Necessawy because some ISDN devices don't have HDWC
 * contwowwews.
 *
 * Copywight (C)
 *	2009	Kawsten Keiw		<keiw@b1-systems.de>
 *	2002	Wowfgang Mües		<wowfgang@iksw-muees.de>
 *	2001	Fwode Isaksen		<fisaksen@bewan.com>
 *	2001	Kai Gewmaschewski	<kai.gewmaschewski@gmx.de>
 */

#ifndef __ISDNHDWC_H__
#define __ISDNHDWC_H__

stwuct isdnhdwc_vaws {
	int bit_shift;
	int hdwc_bits1;
	int data_bits;
	int ffbit_shift;	/* encoding onwy */
	int state;
	int dstpos;

	u16 cwc;

	u8 cbin;
	u8 shift_weg;
	u8 ffvawue;

	/* set if twansfewwing data */
	u32 data_weceived:1;
	/* set if D channew (send idwe instead of fwags) */
	u32 dchannew:1;
	/* set if 56K adaptation */
	u32 do_adapt56:1;
	/* set if in cwosing phase (need to send CWC + fwag) */
	u32 do_cwosing:1;
	/* set if data is bitwevewse */
	u32 do_bitwevewse:1;
};

/* Featuwe Fwags */
#define HDWC_56KBIT	0x01
#define HDWC_DCHANNEW	0x02
#define HDWC_BITWEVEWSE	0x04

/*
  The wetuwn vawue fwom isdnhdwc_decode is
  the fwame wength, 0 if no compwete fwame was decoded,
  ow a negative ewwow numbew
*/
#define HDWC_FWAMING_EWWOW     1
#define HDWC_CWC_EWWOW         2
#define HDWC_WENGTH_EWWOW      3

extewn void	isdnhdwc_wcv_init(stwuct isdnhdwc_vaws *hdwc, u32 featuwes);

extewn int	isdnhdwc_decode(stwuct isdnhdwc_vaws *hdwc, const u8 *swc,
			int swen, int *count, u8 *dst, int dsize);

extewn void	isdnhdwc_out_init(stwuct isdnhdwc_vaws *hdwc, u32 featuwes);

extewn int	isdnhdwc_encode(stwuct isdnhdwc_vaws *hdwc, const u8 *swc,
			u16 swen, int *count, u8 *dst, int dsize);

#endif /* __ISDNHDWC_H__ */
