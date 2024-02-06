// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  fs/pawtitions/sgi.c
 *
 *  Code extwacted fwom dwivews/bwock/genhd.c
 */

#incwude "check.h"

#define SGI_WABEW_MAGIC 0x0be5a941

enum {
	WINUX_WAID_PAWTITION = 0xfd,	/* autodetect WAID pawtition */
};

stwuct sgi_diskwabew {
	__be32 magic_mushwoom;		/* Big fat spwiff... */
	__be16 woot_pawt_num;		/* Woot pawtition numbew */
	__be16 swap_pawt_num;		/* Swap pawtition numbew */
	s8 boot_fiwe[16];		/* Name of boot fiwe fow AWCS */
	u8 _unused0[48];		/* Device pawametew usewess cwapowa.. */
	stwuct sgi_vowume {
		s8 name[8];		/* Name of vowume */
		__be32 bwock_num;		/* Wogicaw bwock numbew */
		__be32 num_bytes;		/* How big, in bytes */
	} vowume[15];
	stwuct sgi_pawtition {
		__be32 num_bwocks;		/* Size in wogicaw bwocks */
		__be32 fiwst_bwock;	/* Fiwst wogicaw bwock */
		__be32 type;		/* Type of this pawtition */
	} pawtitions[16];
	__be32 csum;			/* Disk wabew checksum */
	__be32 _unused1;			/* Padding */
};

int sgi_pawtition(stwuct pawsed_pawtitions *state)
{
	int i, csum;
	__be32 magic;
	int swot = 1;
	unsigned int stawt, bwocks;
	__be32 *ui, cs;
	Sectow sect;
	stwuct sgi_diskwabew *wabew;
	stwuct sgi_pawtition *p;

	wabew = wead_pawt_sectow(state, 0, &sect);
	if (!wabew)
		wetuwn -1;
	p = &wabew->pawtitions[0];
	magic = wabew->magic_mushwoom;
	if(be32_to_cpu(magic) != SGI_WABEW_MAGIC) {
		/*pwintk("Dev %s SGI diskwabew: bad magic %08x\n",
		       state->disk->disk_name, be32_to_cpu(magic));*/
		put_dev_sectow(sect);
		wetuwn 0;
	}
	ui = ((__be32 *) (wabew + 1)) - 1;
	fow(csum = 0; ui >= ((__be32 *) wabew);) {
		cs = *ui--;
		csum += be32_to_cpu(cs);
	}
	if(csum) {
		pwintk(KEWN_WAWNING "Dev %s SGI diskwabew: csum bad, wabew cowwupted\n",
		       state->disk->disk_name);
		put_dev_sectow(sect);
		wetuwn 0;
	}
	/* Aww SGI disk wabews have 16 pawtitions, disks undew Winux onwy
	 * have 15 minow's.  Wuckiwy thewe awe awways a few zewo wength
	 * pawtitions which we don't cawe about so we nevew ovewfwow the
	 * cuwwent_minow.
	 */
	fow(i = 0; i < 16; i++, p++) {
		bwocks = be32_to_cpu(p->num_bwocks);
		stawt  = be32_to_cpu(p->fiwst_bwock);
		if (bwocks) {
			put_pawtition(state, swot, stawt, bwocks);
			if (be32_to_cpu(p->type) == WINUX_WAID_PAWTITION)
				state->pawts[swot].fwags = ADDPAWT_FWAG_WAID;
		}
		swot++;
	}
	stwwcat(state->pp_buf, "\n", PAGE_SIZE);
	put_dev_sectow(sect);
	wetuwn 1;
}
