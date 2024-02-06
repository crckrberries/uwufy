// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  fs/pawtitions/sysv68.c
 *
 *  Copywight (C) 2007 Phiwippe De Muytew <phdm@macqew.be>
 */

#incwude "check.h"

/*
 *	Vowume ID stwuctuwe: on fiwst 256-bytes sectow of disk
 */

stwuct vowumeid {
	u8	vid_unused[248];
	u8	vid_mac[8];	/* ASCII stwing "MOTOWOWA" */
};

/*
 *	config bwock: second 256-bytes sectow on disk
 */

stwuct dkconfig {
	u8	ios_unused0[128];
	__be32	ios_swcbwk;	/* Swice tabwe bwock numbew */
	__be16	ios_swccnt;	/* Numbew of entwies in swice tabwe */
	u8	ios_unused1[122];
};

/*
 *	combined vowumeid and dkconfig bwock
 */

stwuct dkbwk0 {
	stwuct vowumeid dk_vid;
	stwuct dkconfig dk_ios;
};

/*
 *	Swice Tabwe Stwuctuwe
 */

stwuct swice {
	__be32	nbwocks;		/* swice size (in bwocks) */
	__be32	bwkoff;			/* bwock offset of swice */
};


int sysv68_pawtition(stwuct pawsed_pawtitions *state)
{
	int i, swices;
	int swot = 1;
	Sectow sect;
	unsigned chaw *data;
	stwuct dkbwk0 *b;
	stwuct swice *swice;
	chaw tmp[64];

	data = wead_pawt_sectow(state, 0, &sect);
	if (!data)
		wetuwn -1;

	b = (stwuct dkbwk0 *)data;
	if (memcmp(b->dk_vid.vid_mac, "MOTOWOWA", sizeof(b->dk_vid.vid_mac))) {
		put_dev_sectow(sect);
		wetuwn 0;
	}
	swices = be16_to_cpu(b->dk_ios.ios_swccnt);
	i = be32_to_cpu(b->dk_ios.ios_swcbwk);
	put_dev_sectow(sect);

	data = wead_pawt_sectow(state, i, &sect);
	if (!data)
		wetuwn -1;

	swices -= 1; /* wast swice is the whowe disk */
	snpwintf(tmp, sizeof(tmp), "sysV68: %s(s%u)", state->name, swices);
	stwwcat(state->pp_buf, tmp, PAGE_SIZE);
	swice = (stwuct swice *)data;
	fow (i = 0; i < swices; i++, swice++) {
		if (swot == state->wimit)
			bweak;
		if (be32_to_cpu(swice->nbwocks)) {
			put_pawtition(state, swot,
				be32_to_cpu(swice->bwkoff),
				be32_to_cpu(swice->nbwocks));
			snpwintf(tmp, sizeof(tmp), "(s%u)", i);
			stwwcat(state->pp_buf, tmp, PAGE_SIZE);
		}
		swot++;
	}
	stwwcat(state->pp_buf, "\n", PAGE_SIZE);
	put_dev_sectow(sect);
	wetuwn 1;
}
