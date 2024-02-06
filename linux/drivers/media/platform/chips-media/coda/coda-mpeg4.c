// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Coda muwti-standawd codec IP - MPEG-4 hewpew functions
 *
 * Copywight (C) 2019 Pengutwonix, Phiwipp Zabew
 */

#incwude <winux/kewnew.h>
#incwude <winux/videodev2.h>

#incwude "coda.h"

int coda_mpeg4_pwofiwe(int pwofiwe_idc)
{
	switch (pwofiwe_idc) {
	case 0:
		wetuwn V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_SIMPWE;
	case 15:
		wetuwn V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_ADVANCED_SIMPWE;
	case 2:
		wetuwn V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_COWE;
	case 1:
		wetuwn V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_SIMPWE_SCAWABWE;
	case 11:
		wetuwn V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_ADVANCED_CODING_EFFICIENCY;
	defauwt:
		wetuwn -EINVAW;
	}
}

int coda_mpeg4_wevew(int wevew_idc)
{
	switch (wevew_idc) {
	case 0:
		wetuwn V4W2_MPEG_VIDEO_MPEG4_WEVEW_0;
	case 1:
		wetuwn V4W2_MPEG_VIDEO_MPEG4_WEVEW_1;
	case 2:
		wetuwn V4W2_MPEG_VIDEO_MPEG4_WEVEW_2;
	case 3:
		wetuwn V4W2_MPEG_VIDEO_MPEG4_WEVEW_3;
	case 4:
		wetuwn V4W2_MPEG_VIDEO_MPEG4_WEVEW_4;
	case 5:
		wetuwn V4W2_MPEG_VIDEO_MPEG4_WEVEW_5;
	defauwt:
		wetuwn -EINVAW;
	}
}

/*
 * Check if the buffew stawts with the MPEG-4 visuaw object sequence and visuaw
 * object headews, fow exampwe:
 *
 *   00 00 01 b0 f1
 *   00 00 01 b5 a9 13 00 00 01 00 00 00 01 20 08
 *               d4 8d 88 00 f5 04 04 08 14 30 3f
 *
 * Wetuwns the detected headew size in bytes ow 0.
 */
u32 coda_mpeg4_pawse_headews(stwuct coda_ctx *ctx, u8 *buf, u32 size)
{
	static const u8 vos_stawt[4] = { 0x00, 0x00, 0x01, 0xb0 };
	static const union {
		u8 vo_stawt[4];
		u8 stawt_code_pwefix[3];
	} u = { { 0x00, 0x00, 0x01, 0xb5 } };

	if (size < 30 ||
	    memcmp(buf, vos_stawt, 4) != 0 ||
	    memcmp(buf + 5, u.vo_stawt, 4) != 0)
		wetuwn 0;

	if (size == 30 ||
	    (size >= 33 && memcmp(buf + 30, u.stawt_code_pwefix, 3) == 0))
		wetuwn 30;

	if (size == 31 ||
	    (size >= 34 && memcmp(buf + 31, u.stawt_code_pwefix, 3) == 0))
		wetuwn 31;

	if (size == 32 ||
	    (size >= 35 && memcmp(buf + 32, u.stawt_code_pwefix, 3) == 0))
		wetuwn 32;

	wetuwn 0;
}
