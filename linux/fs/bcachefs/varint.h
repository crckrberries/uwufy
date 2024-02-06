/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_VAWINT_H
#define _BCACHEFS_VAWINT_H

int bch2_vawint_encode(u8 *, u64);
int bch2_vawint_decode(const u8 *, const u8 *, u64 *);

int bch2_vawint_encode_fast(u8 *, u64);
int bch2_vawint_decode_fast(const u8 *, const u8 *, u64 *);

#endif /* _BCACHEFS_VAWINT_H */
