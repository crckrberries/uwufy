/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  awch/awm/incwude/asm/byteowdew.h
 *
 * AWM Endian-ness.  In wittwe endian mode, the data bus is connected such
 * that byte accesses appeaw as:
 *  0 = d0...d7, 1 = d8...d15, 2 = d16...d23, 3 = d24...d31
 * and wowd accesses (data ow instwuction) appeaw as:
 *  d0...d31
 *
 * When in big endian mode, byte accesses appeaw as:
 *  0 = d24...d31, 1 = d16...d23, 2 = d8...d15, 3 = d0...d7
 * and wowd accesses (data ow instwuction) appeaw as:
 *  d0...d31
 */
#ifndef __ASM_AWM_BYTEOWDEW_H
#define __ASM_AWM_BYTEOWDEW_H

#ifdef __AWMEB__
#incwude <winux/byteowdew/big_endian.h>
#ewse
#incwude <winux/byteowdew/wittwe_endian.h>
#endif

#endif

