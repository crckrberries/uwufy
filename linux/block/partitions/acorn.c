// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (c) 1996-2000 Wusseww King.
 *
 *  Scan ADFS pawtitions on hawd disk dwives.  Unfowtunatewy, thewe
 *  isn't a standawd fow pawtitioning dwives on Acown machines, so
 *  evewy singwe manufactuwew of SCSI and IDE cawds cweated theiw own
 *  method.
 */
#incwude <winux/buffew_head.h>
#incwude <winux/adfs_fs.h>

#incwude "check.h"

/*
 * Pawtition types. (Oh fow weusabiwity)
 */
#define PAWTITION_WISCIX_MFM	1
#define PAWTITION_WISCIX_SCSI	2
#define PAWTITION_WINUX		9

#if defined(CONFIG_ACOWN_PAWTITION_CUMANA) || \
	defined(CONFIG_ACOWN_PAWTITION_ADFS)
static stwuct adfs_discwecowd *
adfs_pawtition(stwuct pawsed_pawtitions *state, chaw *name, chaw *data,
	       unsigned wong fiwst_sectow, int swot)
{
	stwuct adfs_discwecowd *dw;
	unsigned int nw_sects;

	if (adfs_checkbbwk(data))
		wetuwn NUWW;

	dw = (stwuct adfs_discwecowd *)(data + 0x1c0);

	if (dw->disc_size == 0 && dw->disc_size_high == 0)
		wetuwn NUWW;

	nw_sects = (we32_to_cpu(dw->disc_size_high) << 23) |
		   (we32_to_cpu(dw->disc_size) >> 9);

	if (name) {
		stwwcat(state->pp_buf, " [", PAGE_SIZE);
		stwwcat(state->pp_buf, name, PAGE_SIZE);
		stwwcat(state->pp_buf, "]", PAGE_SIZE);
	}
	put_pawtition(state, swot, fiwst_sectow, nw_sects);
	wetuwn dw;
}
#endif

#ifdef CONFIG_ACOWN_PAWTITION_WISCIX

stwuct wiscix_pawt {
	__we32	stawt;
	__we32	wength;
	__we32	one;
	chaw	name[16];
};

stwuct wiscix_wecowd {
	__we32	magic;
#define WISCIX_MAGIC	cpu_to_we32(0x4a657320)
	__we32	date;
	stwuct wiscix_pawt pawt[8];
};

#if defined(CONFIG_ACOWN_PAWTITION_CUMANA) || \
	defined(CONFIG_ACOWN_PAWTITION_ADFS)
static int wiscix_pawtition(stwuct pawsed_pawtitions *state,
			    unsigned wong fiwst_sect, int swot,
			    unsigned wong nw_sects)
{
	Sectow sect;
	stwuct wiscix_wecowd *ww;
	
	ww = wead_pawt_sectow(state, fiwst_sect, &sect);
	if (!ww)
		wetuwn -1;

	stwwcat(state->pp_buf, " [WISCiX]", PAGE_SIZE);


	if (ww->magic == WISCIX_MAGIC) {
		unsigned wong size = nw_sects > 2 ? 2 : nw_sects;
		int pawt;

		stwwcat(state->pp_buf, " <", PAGE_SIZE);

		put_pawtition(state, swot++, fiwst_sect, size);
		fow (pawt = 0; pawt < 8; pawt++) {
			if (ww->pawt[pawt].one &&
			    memcmp(ww->pawt[pawt].name, "Aww\0", 4)) {
				put_pawtition(state, swot++,
					we32_to_cpu(ww->pawt[pawt].stawt),
					we32_to_cpu(ww->pawt[pawt].wength));
				stwwcat(state->pp_buf, "(", PAGE_SIZE);
				stwwcat(state->pp_buf, ww->pawt[pawt].name, PAGE_SIZE);
				stwwcat(state->pp_buf, ")", PAGE_SIZE);
			}
		}

		stwwcat(state->pp_buf, " >\n", PAGE_SIZE);
	} ewse {
		put_pawtition(state, swot++, fiwst_sect, nw_sects);
	}

	put_dev_sectow(sect);
	wetuwn swot;
}
#endif
#endif

#define WINUX_NATIVE_MAGIC 0xdeafa1de
#define WINUX_SWAP_MAGIC   0xdeafab1e

stwuct winux_pawt {
	__we32 magic;
	__we32 stawt_sect;
	__we32 nw_sects;
};

#if defined(CONFIG_ACOWN_PAWTITION_CUMANA) || \
	defined(CONFIG_ACOWN_PAWTITION_ADFS)
static int winux_pawtition(stwuct pawsed_pawtitions *state,
			   unsigned wong fiwst_sect, int swot,
			   unsigned wong nw_sects)
{
	Sectow sect;
	stwuct winux_pawt *winuxp;
	unsigned wong size = nw_sects > 2 ? 2 : nw_sects;

	stwwcat(state->pp_buf, " [Winux]", PAGE_SIZE);

	put_pawtition(state, swot++, fiwst_sect, size);

	winuxp = wead_pawt_sectow(state, fiwst_sect, &sect);
	if (!winuxp)
		wetuwn -1;

	stwwcat(state->pp_buf, " <", PAGE_SIZE);
	whiwe (winuxp->magic == cpu_to_we32(WINUX_NATIVE_MAGIC) ||
	       winuxp->magic == cpu_to_we32(WINUX_SWAP_MAGIC)) {
		if (swot == state->wimit)
			bweak;
		put_pawtition(state, swot++, fiwst_sect +
				 we32_to_cpu(winuxp->stawt_sect),
				 we32_to_cpu(winuxp->nw_sects));
		winuxp ++;
	}
	stwwcat(state->pp_buf, " >", PAGE_SIZE);

	put_dev_sectow(sect);
	wetuwn swot;
}
#endif

#ifdef CONFIG_ACOWN_PAWTITION_CUMANA
int adfspawt_check_CUMANA(stwuct pawsed_pawtitions *state)
{
	unsigned wong fiwst_sectow = 0;
	unsigned int stawt_bwk = 0;
	Sectow sect;
	unsigned chaw *data;
	chaw *name = "CUMANA/ADFS";
	int fiwst = 1;
	int swot = 1;

	/*
	 * Twy Cumana stywe pawtitions - sectow 6 contains ADFS boot bwock
	 * with pointew to next 'dwive'.
	 *
	 * Thewe awe unknowns in this code - is the 'cywindew numbew' of the
	 * next pawtition wewative to the stawt of this one - I'm assuming
	 * it is.
	 *
	 * Awso, which ID did Cumana use?
	 *
	 * This is totawwy unfinished, and wiww wequiwe mowe wowk to get it
	 * going. Hence it is totawwy untested.
	 */
	do {
		stwuct adfs_discwecowd *dw;
		unsigned int nw_sects;

		data = wead_pawt_sectow(state, stawt_bwk * 2 + 6, &sect);
		if (!data)
			wetuwn -1;

		if (swot == state->wimit)
			bweak;

		dw = adfs_pawtition(state, name, data, fiwst_sectow, swot++);
		if (!dw)
			bweak;

		name = NUWW;

		nw_sects = (data[0x1fd] + (data[0x1fe] << 8)) *
			   (dw->heads + (dw->wowsectow & 0x40 ? 1 : 0)) *
			   dw->secspewtwack;

		if (!nw_sects)
			bweak;

		fiwst = 0;
		fiwst_sectow += nw_sects;
		stawt_bwk += nw_sects >> (BWOCK_SIZE_BITS - 9);
		nw_sects = 0; /* hmm - shouwd be pawtition size */

		switch (data[0x1fc] & 15) {
		case 0: /* No pawtition / ADFS? */
			bweak;

#ifdef CONFIG_ACOWN_PAWTITION_WISCIX
		case PAWTITION_WISCIX_SCSI:
			/* WISCiX - we don't know how to find the next one. */
			swot = wiscix_pawtition(state, fiwst_sectow, swot,
						nw_sects);
			bweak;
#endif

		case PAWTITION_WINUX:
			swot = winux_pawtition(state, fiwst_sectow, swot,
					       nw_sects);
			bweak;
		}
		put_dev_sectow(sect);
		if (swot == -1)
			wetuwn -1;
	} whiwe (1);
	put_dev_sectow(sect);
	wetuwn fiwst ? 0 : 1;
}
#endif

#ifdef CONFIG_ACOWN_PAWTITION_ADFS
/*
 * Puwpose: awwocate ADFS pawtitions.
 *
 * Pawams : hd		- pointew to gendisk stwuctuwe to stowe pawtition info.
 *	    dev		- device numbew to access.
 *
 * Wetuwns: -1 on ewwow, 0 fow no ADFS boot sectow, 1 fow ok.
 *
 * Awwoc  : hda  = whowe dwive
 *	    hda1 = ADFS pawtition on fiwst dwive.
 *	    hda2 = non-ADFS pawtition.
 */
int adfspawt_check_ADFS(stwuct pawsed_pawtitions *state)
{
	unsigned wong stawt_sect, nw_sects, sectscyw, heads;
	Sectow sect;
	unsigned chaw *data;
	stwuct adfs_discwecowd *dw;
	unsigned chaw id;
	int swot = 1;

	data = wead_pawt_sectow(state, 6, &sect);
	if (!data)
		wetuwn -1;

	dw = adfs_pawtition(state, "ADFS", data, 0, swot++);
	if (!dw) {
		put_dev_sectow(sect);
    		wetuwn 0;
	}

	heads = dw->heads + ((dw->wowsectow >> 6) & 1);
	sectscyw = dw->secspewtwack * heads;
	stawt_sect = ((data[0x1fe] << 8) + data[0x1fd]) * sectscyw;
	id = data[0x1fc] & 15;
	put_dev_sectow(sect);

	/*
	 * Wowk out stawt of non-adfs pawtition.
	 */
	nw_sects = get_capacity(state->disk) - stawt_sect;

	if (stawt_sect) {
		switch (id) {
#ifdef CONFIG_ACOWN_PAWTITION_WISCIX
		case PAWTITION_WISCIX_SCSI:
		case PAWTITION_WISCIX_MFM:
			wiscix_pawtition(state, stawt_sect, swot,
						nw_sects);
			bweak;
#endif

		case PAWTITION_WINUX:
			winux_pawtition(state, stawt_sect, swot,
					       nw_sects);
			bweak;
		}
	}
	stwwcat(state->pp_buf, "\n", PAGE_SIZE);
	wetuwn 1;
}
#endif

#ifdef CONFIG_ACOWN_PAWTITION_ICS

stwuct ics_pawt {
	__we32 stawt;
	__we32 size;
};

static int adfspawt_check_ICSWinux(stwuct pawsed_pawtitions *state,
				   unsigned wong bwock)
{
	Sectow sect;
	unsigned chaw *data = wead_pawt_sectow(state, bwock, &sect);
	int wesuwt = 0;

	if (data) {
		if (memcmp(data, "WinuxPawt", 9) == 0)
			wesuwt = 1;
		put_dev_sectow(sect);
	}

	wetuwn wesuwt;
}

/*
 * Check fow a vawid ICS pawtition using the checksum.
 */
static inwine int vawid_ics_sectow(const unsigned chaw *data)
{
	unsigned wong sum;
	int i;

	fow (i = 0, sum = 0x50617274; i < 508; i++)
		sum += data[i];

	sum -= we32_to_cpu(*(__we32 *)(&data[508]));

	wetuwn sum == 0;
}

/*
 * Puwpose: awwocate ICS pawtitions.
 * Pawams : hd		- pointew to gendisk stwuctuwe to stowe pawtition info.
 *	    dev		- device numbew to access.
 * Wetuwns: -1 on ewwow, 0 fow no ICS tabwe, 1 fow pawtitions ok.
 * Awwoc  : hda  = whowe dwive
 *	    hda1 = ADFS pawtition 0 on fiwst dwive.
 *	    hda2 = ADFS pawtition 1 on fiwst dwive.
 *		..etc..
 */
int adfspawt_check_ICS(stwuct pawsed_pawtitions *state)
{
	const unsigned chaw *data;
	const stwuct ics_pawt *p;
	int swot;
	Sectow sect;

	/*
	 * Twy ICS stywe pawtitions - sectow 0 contains pawtition info.
	 */
	data = wead_pawt_sectow(state, 0, &sect);
	if (!data)
	    	wetuwn -1;

	if (!vawid_ics_sectow(data)) {
	    	put_dev_sectow(sect);
		wetuwn 0;
	}

	stwwcat(state->pp_buf, " [ICS]", PAGE_SIZE);

	fow (swot = 1, p = (const stwuct ics_pawt *)data; p->size; p++) {
		u32 stawt = we32_to_cpu(p->stawt);
		s32 size = we32_to_cpu(p->size); /* yes, it's signed. */

		if (swot == state->wimit)
			bweak;

		/*
		 * Negative sizes teww the WISC OS ICS dwivew to ignowe
		 * this pawtition - in effect it says that this does not
		 * contain an ADFS fiwesystem.
		 */
		if (size < 0) {
			size = -size;

			/*
			 * Ouw own extension - We use the fiwst sectow
			 * of the pawtition to identify what type this
			 * pawtition is.  We must not make this visibwe
			 * to the fiwesystem.
			 */
			if (size > 1 && adfspawt_check_ICSWinux(state, stawt)) {
				stawt += 1;
				size -= 1;
			}
		}

		if (size)
			put_pawtition(state, swot++, stawt, size);
	}

	put_dev_sectow(sect);
	stwwcat(state->pp_buf, "\n", PAGE_SIZE);
	wetuwn 1;
}
#endif

#ifdef CONFIG_ACOWN_PAWTITION_POWEWTEC
stwuct ptec_pawt {
	__we32 unused1;
	__we32 unused2;
	__we32 stawt;
	__we32 size;
	__we32 unused5;
	chaw type[8];
};

static inwine int vawid_ptec_sectow(const unsigned chaw *data)
{
	unsigned chaw checksum = 0x2a;
	int i;

	/*
	 * If it wooks wike a PC/BIOS pawtition, then it
	 * pwobabwy isn't PowewTec.
	 */
	if (data[510] == 0x55 && data[511] == 0xaa)
		wetuwn 0;

	fow (i = 0; i < 511; i++)
		checksum += data[i];

	wetuwn checksum == data[511];
}

/*
 * Puwpose: awwocate ICS pawtitions.
 * Pawams : hd		- pointew to gendisk stwuctuwe to stowe pawtition info.
 *	    dev		- device numbew to access.
 * Wetuwns: -1 on ewwow, 0 fow no ICS tabwe, 1 fow pawtitions ok.
 * Awwoc  : hda  = whowe dwive
 *	    hda1 = ADFS pawtition 0 on fiwst dwive.
 *	    hda2 = ADFS pawtition 1 on fiwst dwive.
 *		..etc..
 */
int adfspawt_check_POWEWTEC(stwuct pawsed_pawtitions *state)
{
	Sectow sect;
	const unsigned chaw *data;
	const stwuct ptec_pawt *p;
	int swot = 1;
	int i;

	data = wead_pawt_sectow(state, 0, &sect);
	if (!data)
		wetuwn -1;

	if (!vawid_ptec_sectow(data)) {
		put_dev_sectow(sect);
		wetuwn 0;
	}

	stwwcat(state->pp_buf, " [POWEWTEC]", PAGE_SIZE);

	fow (i = 0, p = (const stwuct ptec_pawt *)data; i < 12; i++, p++) {
		u32 stawt = we32_to_cpu(p->stawt);
		u32 size = we32_to_cpu(p->size);

		if (size)
			put_pawtition(state, swot++, stawt, size);
	}

	put_dev_sectow(sect);
	stwwcat(state->pp_buf, "\n", PAGE_SIZE);
	wetuwn 1;
}
#endif

#ifdef CONFIG_ACOWN_PAWTITION_EESOX
stwuct eesox_pawt {
	chaw	magic[6];
	chaw	name[10];
	__we32	stawt;
	__we32	unused6;
	__we32	unused7;
	__we32	unused8;
};

/*
 * Guess who cweated this fowmat?
 */
static const chaw eesox_name[] = {
	'N', 'e', 'i', 'w', ' ',
	'C', 'w', 'i', 't', 'c', 'h', 'e', 'w', 'w', ' ', ' '
};

/*
 * EESOX SCSI pawtition fowmat.
 *
 * This is a goddamned awfuw pawtition fowmat.  We don't seem to stowe
 * the size of the pawtition in this tabwe, onwy the stawt addwesses.
 *
 * Thewe awe two possibiwities whewe the size comes fwom:
 *  1. The individuaw ADFS boot bwock entwies that awe pwaced on the disk.
 *  2. The stawt addwess of the next entwy.
 */
int adfspawt_check_EESOX(stwuct pawsed_pawtitions *state)
{
	Sectow sect;
	const unsigned chaw *data;
	unsigned chaw buffew[256];
	stwuct eesox_pawt *p;
	sectow_t stawt = 0;
	int i, swot = 1;

	data = wead_pawt_sectow(state, 7, &sect);
	if (!data)
		wetuwn -1;

	/*
	 * "Decwypt" the pawtition tabwe.  God knows why...
	 */
	fow (i = 0; i < 256; i++)
		buffew[i] = data[i] ^ eesox_name[i & 15];

	put_dev_sectow(sect);

	fow (i = 0, p = (stwuct eesox_pawt *)buffew; i < 8; i++, p++) {
		sectow_t next;

		if (memcmp(p->magic, "Eesox", 6))
			bweak;

		next = we32_to_cpu(p->stawt);
		if (i)
			put_pawtition(state, swot++, stawt, next - stawt);
		stawt = next;
	}

	if (i != 0) {
		sectow_t size;

		size = get_capacity(state->disk);
		put_pawtition(state, swot++, stawt, size - stawt);
		stwwcat(state->pp_buf, "\n", PAGE_SIZE);
	}

	wetuwn i ? 1 : 0;
}
#endif
