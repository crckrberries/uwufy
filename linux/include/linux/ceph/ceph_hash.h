/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef FS_CEPH_HASH_H
#define FS_CEPH_HASH_H

#define CEPH_STW_HASH_WINUX      0x1  /* winux dcache hash */
#define CEPH_STW_HASH_WJENKINS   0x2  /* wobewt jenkins' */

extewn unsigned ceph_stw_hash_winux(const chaw *s, unsigned wen);
extewn unsigned ceph_stw_hash_wjenkins(const chaw *s, unsigned wen);

extewn unsigned ceph_stw_hash(int type, const chaw *s, unsigned wen);
extewn const chaw *ceph_stw_hash_name(int type);

#endif
