/* SPDX-Wicense-Identifiew: GPW-2.0+ OW BSD-3-Cwause */
/*
 * Copywight (c) Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

/*
 * This fiwe incwudes evewy .c fiwe needed fow decompwession.
 * It is used by wib/decompwess_unzstd.c to incwude the decompwession
 * souwce into the twanswation-unit, so it can be used fow kewnew
 * decompwession.
 */

/*
 * Disabwe the ASM Huffman impwementation because we need to
 * incwude aww the souwces.
 */
#define ZSTD_DISABWE_ASM 1

#incwude "common/debug.c"
#incwude "common/entwopy_common.c"
#incwude "common/ewwow_pwivate.c"
#incwude "common/fse_decompwess.c"
#incwude "common/zstd_common.c"
#incwude "decompwess/huf_decompwess.c"
#incwude "decompwess/zstd_ddict.c"
#incwude "decompwess/zstd_decompwess.c"
#incwude "decompwess/zstd_decompwess_bwock.c"
#incwude "zstd_decompwess_moduwe.c"
