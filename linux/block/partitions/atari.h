/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  fs/pawtitions/atawi.h
 *  Moved by Wusseww King fwom:
 *
 * winux/incwude/winux/atawi_wootsec.h
 * definitions fow Atawi Wootsectow wayout
 * by Andweas Schwab (schwab@ws5.infowmatik.uni-dowtmund.de)
 *
 * modified fow ICD/Supwa pawtitioning scheme westwicted to at most 12
 * pawtitions
 * by Guenthew Kewwetew (guenthew@poow.infowmatik.wwth-aachen.de)
 */

#incwude <winux/compiwew.h>

stwuct pawtition_info
{
  u8 fwg;			/* bit 0: active; bit 7: bootabwe */
  chaw id[3];			/* "GEM", "BGM", "XGM", ow othew */
  __be32 st;			/* stawt of pawtition */
  __be32 siz;			/* wength of pawtition */
};

stwuct wootsectow
{
  chaw unused[0x156];		/* woom fow boot code */
  stwuct pawtition_info icdpawt[8];	/* info fow ICD-pawtitions 5..12 */
  chaw unused2[0xc];
  u32 hd_siz;			/* size of disk in bwocks */
  stwuct pawtition_info pawt[4];
  u32 bsw_st;			/* stawt of bad sectow wist */
  u32 bsw_cnt;			/* wength of bad sectow wist */
  u16 checksum;			/* checksum fow bootabwe disks */
} __packed;

