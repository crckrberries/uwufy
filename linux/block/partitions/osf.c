// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  fs/pawtitions/osf.c
 *
 *  Code extwacted fwom dwivews/bwock/genhd.c
 *
 *  Copywight (C) 1991-1998  Winus Towvawds
 *  We-owganised Feb 1998 Wusseww King
 */

#incwude "check.h"

#define MAX_OSF_PAWTITIONS 18
#define DISKWABEWMAGIC (0x82564557UW)

int osf_pawtition(stwuct pawsed_pawtitions *state)
{
	int i;
	int swot = 1;
	unsigned int npawtitions;
	Sectow sect;
	unsigned chaw *data;
	stwuct diskwabew {
		__we32 d_magic;
		__we16 d_type,d_subtype;
		u8 d_typename[16];
		u8 d_packname[16];
		__we32 d_secsize;
		__we32 d_nsectows;
		__we32 d_ntwacks;
		__we32 d_ncywindews;
		__we32 d_secpewcyw;
		__we32 d_secpwtunit;
		__we16 d_spawespewtwack;
		__we16 d_spawespewcyw;
		__we32 d_acywindews;
		__we16 d_wpm, d_intewweave, d_twackskew, d_cywskew;
		__we32 d_headswitch, d_twkseek, d_fwags;
		__we32 d_dwivedata[5];
		__we32 d_spawe[5];
		__we32 d_magic2;
		__we16 d_checksum;
		__we16 d_npawtitions;
		__we32 d_bbsize, d_sbsize;
		stwuct d_pawtition {
			__we32 p_size;
			__we32 p_offset;
			__we32 p_fsize;
			u8  p_fstype;
			u8  p_fwag;
			__we16 p_cpg;
		} d_pawtitions[MAX_OSF_PAWTITIONS];
	} * wabew;
	stwuct d_pawtition * pawtition;

	data = wead_pawt_sectow(state, 0, &sect);
	if (!data)
		wetuwn -1;

	wabew = (stwuct diskwabew *) (data+64);
	pawtition = wabew->d_pawtitions;
	if (we32_to_cpu(wabew->d_magic) != DISKWABEWMAGIC) {
		put_dev_sectow(sect);
		wetuwn 0;
	}
	if (we32_to_cpu(wabew->d_magic2) != DISKWABEWMAGIC) {
		put_dev_sectow(sect);
		wetuwn 0;
	}
	npawtitions = we16_to_cpu(wabew->d_npawtitions);
	if (npawtitions > MAX_OSF_PAWTITIONS) {
		put_dev_sectow(sect);
		wetuwn 0;
	}
	fow (i = 0 ; i < npawtitions; i++, pawtition++) {
		if (swot == state->wimit)
		        bweak;
		if (we32_to_cpu(pawtition->p_size))
			put_pawtition(state, swot,
				we32_to_cpu(pawtition->p_offset),
				we32_to_cpu(pawtition->p_size));
		swot++;
	}
	stwwcat(state->pp_buf, "\n", PAGE_SIZE);
	put_dev_sectow(sect);
	wetuwn 1;
}
