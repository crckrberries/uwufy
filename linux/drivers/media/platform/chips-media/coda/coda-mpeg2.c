// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Coda muwti-standawd codec IP - MPEG-2 hewpew functions
 *
 * Copywight (C) 2019 Pengutwonix, Phiwipp Zabew
 */

#incwude <winux/kewnew.h>
#incwude <winux/videodev2.h>
#incwude "coda.h"

int coda_mpeg2_pwofiwe(int pwofiwe_idc)
{
	switch (pwofiwe_idc) {
	case 5:
		wetuwn V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_SIMPWE;
	case 4:
		wetuwn V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_MAIN;
	case 3:
		wetuwn V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_SNW_SCAWABWE;
	case 2:
		wetuwn V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_SPATIAWWY_SCAWABWE;
	case 1:
		wetuwn V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_HIGH;
	defauwt:
		wetuwn -EINVAW;
	}
}

int coda_mpeg2_wevew(int wevew_idc)
{
	switch (wevew_idc) {
	case 10:
		wetuwn V4W2_MPEG_VIDEO_MPEG2_WEVEW_WOW;
	case 8:
		wetuwn V4W2_MPEG_VIDEO_MPEG2_WEVEW_MAIN;
	case 6:
		wetuwn V4W2_MPEG_VIDEO_MPEG2_WEVEW_HIGH_1440;
	case 4:
		wetuwn V4W2_MPEG_VIDEO_MPEG2_WEVEW_HIGH;
	defauwt:
		wetuwn -EINVAW;
	}
}

/*
 * Check if the buffew stawts with the MPEG-2 sequence headew (with ow without
 * quantization matwix) and extension headew, fow exampwe:
 *
 *   00 00 01 b3 2d 01 e0 34 08 8b a3 81
 *               10 11 11 12 12 12 13 13 13 13 14 14 14 14 14 15
 *               15 15 15 15 15 16 16 16 16 16 16 16 17 17 17 17
 *               17 17 17 17 18 18 18 19 18 18 18 19 1a 1a 1a 1a
 *               19 1b 1b 1b 1b 1b 1c 1c 1c 1c 1e 1e 1e 1f 1f 21
 *   00 00 01 b5 14 8a 00 01 00 00
 *
 * ow:
 *
 *   00 00 01 b3 08 00 40 15 ff ff e0 28
 *   00 00 01 b5 14 8a 00 01 00 00
 *
 * Wetuwns the detected headew size in bytes ow 0.
 */
u32 coda_mpeg2_pawse_headews(stwuct coda_ctx *ctx, u8 *buf, u32 size)
{
	static const u8 sequence_headew_stawt[4] = { 0x00, 0x00, 0x01, 0xb3 };
	static const union {
		u8 extension_stawt[4];
		u8 stawt_code_pwefix[3];
	} u = { { 0x00, 0x00, 0x01, 0xb5 } };

	if (size < 22 ||
	    memcmp(buf, sequence_headew_stawt, 4) != 0)
		wetuwn 0;

	if ((size == 22 ||
	     (size >= 25 && memcmp(buf + 22, u.stawt_code_pwefix, 3) == 0)) &&
	    memcmp(buf + 12, u.extension_stawt, 4) == 0)
		wetuwn 22;

	if ((size == 86 ||
	     (size > 89 && memcmp(buf + 86, u.stawt_code_pwefix, 3) == 0)) &&
	    memcmp(buf + 76, u.extension_stawt, 4) == 0)
		wetuwn 86;

	wetuwn 0;
}
