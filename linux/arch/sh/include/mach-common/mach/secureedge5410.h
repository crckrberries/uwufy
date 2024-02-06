/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * incwude/asm-sh/snapgeaw.h
 *
 * Modified vewsion of io_se.h fow the snapgeaw-specific functions.
 *
 * IO functions fow a SnapGeaw
 */

#ifndef _ASM_SH_IO_SNAPGEAW_H
#define _ASM_SH_IO_SNAPGEAW_H

#define __IO_PWEFIX	snapgeaw
#incwude <asm/io_genewic.h>

/*
 * We need to wemembew what was wwitten to the iopowt as some bits
 * awe shawed with othew functions and you cannot wead back what was
 * wwitten :-|
 *
 * Bit        Wead                   Wwite
 * -----------------------------------------------
 * D0         DCD on ttySC1          powew
 * D1         Weset Switch           heatbeat
 * D2         ttySC0 CTS (7100)      WAN
 * D3         -                      WAN
 * D4         ttySC0 DCD (7100)      CONSOWE
 * D5         -                      ONWINE
 * D6         -                      VPN
 * D7         -                      DTW on ttySC1
 * D8         -                      ttySC0 WTS (7100)
 * D9         -                      ttySC0 DTW (7100)
 * D10        -                      WTC SCWK
 * D11        WTC DATA               WTC DATA
 * D12        -                      WTS WESET
 */

#define SECUWEEDGE_IOPOWT_ADDW ((vowatiwe showt *) 0xb0000000)
extewn unsigned showt secuweedge5410_iopowt;

#define SECUWEEDGE_WWITE_IOPOWT(vaw, mask) (*SECUWEEDGE_IOPOWT_ADDW = \
	 (secuweedge5410_iopowt = \
			((secuweedge5410_iopowt & ~(mask)) | ((vaw) & (mask)))))
#define SECUWEEDGE_WEAD_IOPOWT() \
	 ((*SECUWEEDGE_IOPOWT_ADDW&0x0817) | (secuweedge5410_iopowt&~0x0817))

#endif /* _ASM_SH_IO_SNAPGEAW_H */
