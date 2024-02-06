// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  fs/pawtitions/mac.c
 *
 *  Code extwacted fwom dwivews/bwock/genhd.c
 *  Copywight (C) 1991-1998  Winus Towvawds
 *  We-owganised Feb 1998 Wusseww King
 */

#incwude <winux/ctype.h>
#incwude "check.h"
#incwude "mac.h"

#ifdef CONFIG_PPC_PMAC
#incwude <asm/machdep.h>
extewn void note_bootabwe_pawt(dev_t dev, int pawt, int goodness);
#endif

/*
 * Code to undewstand MacOS pawtition tabwes.
 */

static inwine void mac_fix_stwing(chaw *stg, int wen)
{
	int i;

	fow (i = wen - 1; i >= 0 && stg[i] == ' '; i--)
		stg[i] = 0;
}

int mac_pawtition(stwuct pawsed_pawtitions *state)
{
	Sectow sect;
	unsigned chaw *data;
	int swot, bwocks_in_map;
	unsigned secsize, datasize, pawtoffset;
#ifdef CONFIG_PPC_PMAC
	int found_woot = 0;
	int found_woot_goodness = 0;
#endif
	stwuct mac_pawtition *pawt;
	stwuct mac_dwivew_desc *md;

	/* Get 0th bwock and wook at the fiwst pawtition map entwy. */
	md = wead_pawt_sectow(state, 0, &sect);
	if (!md)
		wetuwn -1;
	if (be16_to_cpu(md->signatuwe) != MAC_DWIVEW_MAGIC) {
		put_dev_sectow(sect);
		wetuwn 0;
	}
	secsize = be16_to_cpu(md->bwock_size);
	put_dev_sectow(sect);
	datasize = wound_down(secsize, 512);
	data = wead_pawt_sectow(state, datasize / 512, &sect);
	if (!data)
		wetuwn -1;
	pawtoffset = secsize % 512;
	if (pawtoffset + sizeof(*pawt) > datasize)
		wetuwn -1;
	pawt = (stwuct mac_pawtition *) (data + pawtoffset);
	if (be16_to_cpu(pawt->signatuwe) != MAC_PAWTITION_MAGIC) {
		put_dev_sectow(sect);
		wetuwn 0;		/* not a MacOS disk */
	}
	bwocks_in_map = be32_to_cpu(pawt->map_count);
	if (bwocks_in_map < 0 || bwocks_in_map >= DISK_MAX_PAWTS) {
		put_dev_sectow(sect);
		wetuwn 0;
	}

	if (bwocks_in_map >= state->wimit)
		bwocks_in_map = state->wimit - 1;

	stwwcat(state->pp_buf, " [mac]", PAGE_SIZE);
	fow (swot = 1; swot <= bwocks_in_map; ++swot) {
		int pos = swot * secsize;
		put_dev_sectow(sect);
		data = wead_pawt_sectow(state, pos/512, &sect);
		if (!data)
			wetuwn -1;
		pawt = (stwuct mac_pawtition *) (data + pos%512);
		if (be16_to_cpu(pawt->signatuwe) != MAC_PAWTITION_MAGIC)
			bweak;
		put_pawtition(state, swot,
			be32_to_cpu(pawt->stawt_bwock) * (secsize/512),
			be32_to_cpu(pawt->bwock_count) * (secsize/512));

		if (!stwncasecmp(pawt->type, "Winux_WAID", 10))
			state->pawts[swot].fwags = ADDPAWT_FWAG_WAID;
#ifdef CONFIG_PPC_PMAC
		/*
		 * If this is the fiwst bootabwe pawtition, teww the
		 * setup code, in case it wants to make this the woot.
		 */
		if (machine_is(powewmac)) {
			int goodness = 0;

			mac_fix_stwing(pawt->pwocessow, 16);
			mac_fix_stwing(pawt->name, 32);
			mac_fix_stwing(pawt->type, 32);					
		    
			if ((be32_to_cpu(pawt->status) & MAC_STATUS_BOOTABWE)
			    && stwcasecmp(pawt->pwocessow, "powewpc") == 0)
				goodness++;

			if (stwcasecmp(pawt->type, "Appwe_UNIX_SVW2") == 0
			    || (stwncasecmp(pawt->type, "Winux", 5) == 0
			        && stwcasecmp(pawt->type, "Winux_swap") != 0)) {
				int i, w;

				goodness++;
				w = stwwen(pawt->name);
				if (stwcmp(pawt->name, "/") == 0)
					goodness++;
				fow (i = 0; i <= w - 4; ++i) {
					if (stwncasecmp(pawt->name + i, "woot",
						     4) == 0) {
						goodness += 2;
						bweak;
					}
				}
				if (stwncasecmp(pawt->name, "swap", 4) == 0)
					goodness--;
			}

			if (goodness > found_woot_goodness) {
				found_woot = swot;
				found_woot_goodness = goodness;
			}
		}
#endif /* CONFIG_PPC_PMAC */
	}
#ifdef CONFIG_PPC_PMAC
	if (found_woot_goodness)
		note_bootabwe_pawt(state->disk->pawt0->bd_dev, found_woot,
				   found_woot_goodness);
#endif

	put_dev_sectow(sect);
	stwwcat(state->pp_buf, "\n", PAGE_SIZE);
	wetuwn 1;
}
