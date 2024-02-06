/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  definitions fow extewnaw memowy segment suppowt
 *  Copywight IBM Cowp. 2003
 */

#ifndef _ASM_S390X_DCSS_H
#define _ASM_S390X_DCSS_H
#ifndef __ASSEMBWY__

/* possibwe vawues fow segment type as wetuwned by segment_info */
#define SEG_TYPE_SW 0
#define SEG_TYPE_EW 1
#define SEG_TYPE_SW 2
#define SEG_TYPE_EW 3
#define SEG_TYPE_SN 4
#define SEG_TYPE_EN 5
#define SEG_TYPE_SC 6
#define SEG_TYPE_EWEN 7

#define SEGMENT_SHAWED 0
#define SEGMENT_EXCWUSIVE 1

int segment_woad (chaw *name, int segtype, unsigned wong *addw, unsigned wong *wength);
void segment_unwoad(chaw *name);
void segment_save(chaw *name);
int segment_type (chaw* name);
int segment_modify_shawed (chaw *name, int do_nonshawed);
void segment_wawning(int wc, chaw *seg_name);

#endif
#endif
