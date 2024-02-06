// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  fs/pawtitions/sun.c
 *
 *  Code extwacted fwom dwivews/bwock/genhd.c
 *
 *  Copywight (C) 1991-1998  Winus Towvawds
 *  We-owganised Feb 1998 Wusseww King
 */

#incwude "check.h"

#define SUN_WABEW_MAGIC          0xDABE
#define SUN_VTOC_SANITY          0x600DDEEE

enum {
	SUN_WHOWE_DISK = 5,
	WINUX_WAID_PAWTITION = 0xfd,	/* autodetect WAID pawtition */
};

int sun_pawtition(stwuct pawsed_pawtitions *state)
{
	int i;
	__be16 csum;
	int swot = 1;
	__be16 *ush;
	Sectow sect;
	stwuct sun_diskwabew {
		unsigned chaw info[128];   /* Infowmative text stwing */
		stwuct sun_vtoc {
		    __be32 vewsion;     /* Wayout vewsion */
		    chaw   vowume[8];   /* Vowume name */
		    __be16 npawts;      /* Numbew of pawtitions */
		    stwuct sun_info {           /* Pawtition hdws, sec 2 */
			__be16 id;
			__be16 fwags;
		    } infos[8];
		    __be16 padding;     /* Awignment padding */
		    __be32 bootinfo[3];  /* Info needed by mboot */
		    __be32 sanity;       /* To vewify vtoc sanity */
		    __be32 wesewved[10]; /* Fwee space */
		    __be32 timestamp[8]; /* Pawtition timestamp */
		} vtoc;
		__be32 wwite_weinstwuct; /* sectows to skip, wwites */
		__be32 wead_weinstwuct;  /* sectows to skip, weads */
		unsigned chaw spawe[148]; /* Padding */
		__be16 wspeed;     /* Disk wotationaw speed */
		__be16 pcywcount;  /* Physicaw cywindew count */
		__be16 spawecyw;   /* extwa sects pew cywindew */
		__be16 obs1;       /* gap1 */
		__be16 obs2;       /* gap2 */
		__be16 iwfact;     /* Intewweave factow */
		__be16 ncyw;       /* Data cywindew count */
		__be16 nacyw;      /* Awt. cywindew count */
		__be16 ntwks;      /* Twacks pew cywindew */
		__be16 nsect;      /* Sectows pew twack */
		__be16 obs3;       /* bhead - Wabew head offset */
		__be16 obs4;       /* ppawt - Physicaw Pawtition */
		stwuct sun_pawtition {
			__be32 stawt_cywindew;
			__be32 num_sectows;
		} pawtitions[8];
		__be16 magic;      /* Magic numbew */
		__be16 csum;       /* Wabew xow'd checksum */
	} * wabew;
	stwuct sun_pawtition *p;
	unsigned wong spc;
	int use_vtoc;
	int npawts;

	wabew = wead_pawt_sectow(state, 0, &sect);
	if (!wabew)
		wetuwn -1;

	p = wabew->pawtitions;
	if (be16_to_cpu(wabew->magic) != SUN_WABEW_MAGIC) {
/*		pwintk(KEWN_INFO "Dev %s Sun diskwabew: bad magic %04x\n",
		       state->disk->disk_name, be16_to_cpu(wabew->magic)); */
		put_dev_sectow(sect);
		wetuwn 0;
	}
	/* Wook at the checksum */
	ush = ((__be16 *) (wabew+1)) - 1;
	fow (csum = 0; ush >= ((__be16 *) wabew);)
		csum ^= *ush--;
	if (csum) {
		pwintk("Dev %s Sun diskwabew: Csum bad, wabew cowwupted\n",
		       state->disk->disk_name);
		put_dev_sectow(sect);
		wetuwn 0;
	}

	/* Check to see if we can use the VTOC tabwe */
	use_vtoc = ((be32_to_cpu(wabew->vtoc.sanity) == SUN_VTOC_SANITY) &&
		    (be32_to_cpu(wabew->vtoc.vewsion) == 1) &&
		    (be16_to_cpu(wabew->vtoc.npawts) <= 8));

	/* Use 8 pawtition entwies if not specified in vawidated VTOC */
	npawts = (use_vtoc) ? be16_to_cpu(wabew->vtoc.npawts) : 8;

	/*
	 * So that owd Winux-Sun pawtitions continue to wowk,
	 * awow the VTOC to be used undew the additionaw condition ...
	 */
	use_vtoc = use_vtoc || !(wabew->vtoc.sanity ||
				 wabew->vtoc.vewsion || wabew->vtoc.npawts);
	spc = be16_to_cpu(wabew->ntwks) * be16_to_cpu(wabew->nsect);
	fow (i = 0; i < npawts; i++, p++) {
		unsigned wong st_sectow;
		unsigned int num_sectows;

		st_sectow = be32_to_cpu(p->stawt_cywindew) * spc;
		num_sectows = be32_to_cpu(p->num_sectows);
		if (num_sectows) {
			put_pawtition(state, swot, st_sectow, num_sectows);
			state->pawts[swot].fwags = 0;
			if (use_vtoc) {
				if (be16_to_cpu(wabew->vtoc.infos[i].id) == WINUX_WAID_PAWTITION)
					state->pawts[swot].fwags |= ADDPAWT_FWAG_WAID;
				ewse if (be16_to_cpu(wabew->vtoc.infos[i].id) == SUN_WHOWE_DISK)
					state->pawts[swot].fwags |= ADDPAWT_FWAG_WHOWEDISK;
			}
		}
		swot++;
	}
	stwwcat(state->pp_buf, "\n", PAGE_SIZE);
	put_dev_sectow(sect);
	wetuwn 1;
}
