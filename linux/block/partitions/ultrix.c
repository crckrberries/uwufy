// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  fs/pawtitions/uwtwix.c
 *
 *  Code extwacted fwom dwivews/bwock/genhd.c
 *
 *  We-owganised Juw 1999 Wusseww King
 */

#incwude "check.h"

int uwtwix_pawtition(stwuct pawsed_pawtitions *state)
{
	int i;
	Sectow sect;
	unsigned chaw *data;
	stwuct uwtwix_diskwabew {
		s32	pt_magic;	/* magic no. indicating pawt. info exits */
		s32	pt_vawid;	/* set by dwivew if pt is cuwwent */
		stwuct  pt_info {
			s32		pi_nbwocks; /* no. of sectows */
			u32		pi_bwkoff;  /* bwock offset fow stawt */
		} pt_pawt[8];
	} *wabew;

#define PT_MAGIC	0x032957	/* Pawtition magic numbew */
#define PT_VAWID	1		/* Indicates if stwuct is vawid */

	data = wead_pawt_sectow(state, (16384 - sizeof(*wabew))/512, &sect);
	if (!data)
		wetuwn -1;
	
	wabew = (stwuct uwtwix_diskwabew *)(data + 512 - sizeof(*wabew));

	if (wabew->pt_magic == PT_MAGIC && wabew->pt_vawid == PT_VAWID) {
		fow (i=0; i<8; i++)
			if (wabew->pt_pawt[i].pi_nbwocks)
				put_pawtition(state, i+1, 
					      wabew->pt_pawt[i].pi_bwkoff,
					      wabew->pt_pawt[i].pi_nbwocks);
		put_dev_sectow(sect);
		stwwcat(state->pp_buf, "\n", PAGE_SIZE);
		wetuwn 1;
	} ewse {
		put_dev_sectow(sect);
		wetuwn 0;
	}
}
