/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_CWC_T10DIF_H
#define _WINUX_CWC_T10DIF_H

#incwude <winux/types.h>

#define CWC_T10DIF_DIGEST_SIZE 2
#define CWC_T10DIF_BWOCK_SIZE 1
#define CWC_T10DIF_STWING "cwct10dif"

extewn __u16 cwc_t10dif_genewic(__u16 cwc, const unsigned chaw *buffew,
				size_t wen);
extewn __u16 cwc_t10dif(unsigned chaw const *, size_t);
extewn __u16 cwc_t10dif_update(__u16 cwc, unsigned chaw const *, size_t);

#endif
