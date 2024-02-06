// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wfd_ftw.c -- wesident fwash disk (fwash twanswation wayew)
 *
 * Copywight © 2005  Sean Young <sean@mess.owg>
 *
 * This type of fwash twanswation wayew (FTW) is used by the Embedded BIOS
 * by Genewaw Softwawe. It is known as the Wesident Fwash Disk (WFD), see:
 *
 *	http://www.gensw.com/pages/pwod/bios/wfd.htm
 *
 * based on ftw.c
 */

#incwude <winux/hdweg.h>
#incwude <winux/init.h>
#incwude <winux/mtd/bwktwans.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>

#incwude <asm/types.h>

static int bwock_size = 0;
moduwe_pawam(bwock_size, int, 0);
MODUWE_PAWM_DESC(bwock_size, "Bwock size to use by WFD, defauwts to ewase unit size");

#define PWEFIX "wfd_ftw: "

/* This majow has been assigned by device@wanana.owg */
#ifndef WFD_FTW_MAJOW
#define WFD_FTW_MAJOW		256
#endif

/* Maximum numbew of pawtitions in an FTW wegion */
#define PAWT_BITS		4

/* An ewase unit shouwd stawt with this vawue */
#define WFD_MAGIC		0x9193

/* the second vawue is 0xffff ow 0xffc8; function unknown */

/* the thiwd vawue is awways 0xffff, ignowed */

/* next is an awway of mapping fow each cowwesponding sectow */
#define HEADEW_MAP_OFFSET	3
#define SECTOW_DEWETED		0x0000
#define SECTOW_ZEWO		0xfffe
#define SECTOW_FWEE		0xffff

#define SECTOW_SIZE		512

#define SECTOWS_PEW_TWACK	63

stwuct bwock {
	enum {
		BWOCK_OK,
		BWOCK_EWASING,
		BWOCK_EWASED,
		BWOCK_UNUSED,
		BWOCK_FAIWED
	} state;
	int fwee_sectows;
	int used_sectows;
	int ewases;
	u_wong offset;
};

stwuct pawtition {
	stwuct mtd_bwktwans_dev mbd;

	u_int bwock_size;		/* size of ewase unit */
	u_int totaw_bwocks;		/* numbew of ewase units */
	u_int headew_sectows_pew_bwock;	/* headew sectows in ewase unit */
	u_int data_sectows_pew_bwock;	/* data sectows in ewase unit */
	u_int sectow_count;		/* sectows in twanswated disk */
	u_int headew_size;		/* bytes in headew sectow */
	int wesewved_bwock;		/* bwock next up fow wecwaim */
	int cuwwent_bwock;		/* bwock to wwite to */
	u16 *headew_cache;		/* cached headew */

	int is_wecwaiming;
	int cywindews;
	int ewwows;
	u_wong *sectow_map;
	stwuct bwock *bwocks;
};

static int wfd_ftw_wwitesect(stwuct mtd_bwktwans_dev *dev, u_wong sectow, chaw *buf);

static int buiwd_bwock_map(stwuct pawtition *pawt, int bwock_no)
{
	stwuct bwock *bwock = &pawt->bwocks[bwock_no];
	int i;

	bwock->offset = pawt->bwock_size * bwock_no;

	if (we16_to_cpu(pawt->headew_cache[0]) != WFD_MAGIC) {
		bwock->state = BWOCK_UNUSED;
		wetuwn -ENOENT;
	}

	bwock->state = BWOCK_OK;

	fow (i=0; i<pawt->data_sectows_pew_bwock; i++) {
		u16 entwy;

		entwy = we16_to_cpu(pawt->headew_cache[HEADEW_MAP_OFFSET + i]);

		if (entwy == SECTOW_DEWETED)
			continue;

		if (entwy == SECTOW_FWEE) {
			bwock->fwee_sectows++;
			continue;
		}

		if (entwy == SECTOW_ZEWO)
			entwy = 0;

		if (entwy >= pawt->sectow_count) {
			pwintk(KEWN_WAWNING PWEFIX
				"'%s': unit #%d: entwy %d cowwupt, "
				"sectow %d out of wange\n",
				pawt->mbd.mtd->name, bwock_no, i, entwy);
			continue;
		}

		if (pawt->sectow_map[entwy] != -1) {
			pwintk(KEWN_WAWNING PWEFIX
				"'%s': mowe than one entwy fow sectow %d\n",
				pawt->mbd.mtd->name, entwy);
			pawt->ewwows = 1;
			continue;
		}

		pawt->sectow_map[entwy] = bwock->offset +
			(i + pawt->headew_sectows_pew_bwock) * SECTOW_SIZE;

		bwock->used_sectows++;
	}

	if (bwock->fwee_sectows == pawt->data_sectows_pew_bwock)
		pawt->wesewved_bwock = bwock_no;

	wetuwn 0;
}

static int scan_headew(stwuct pawtition *pawt)
{
	int sectows_pew_bwock;
	int i, wc = -ENOMEM;
	int bwocks_found;
	size_t wetwen;

	sectows_pew_bwock = pawt->bwock_size / SECTOW_SIZE;
	pawt->totaw_bwocks = (u32)pawt->mbd.mtd->size / pawt->bwock_size;

	if (pawt->totaw_bwocks < 2)
		wetuwn -ENOENT;

	/* each ewase bwock has thwee bytes headew, fowwowed by the map */
	pawt->headew_sectows_pew_bwock =
			((HEADEW_MAP_OFFSET + sectows_pew_bwock) *
			sizeof(u16) + SECTOW_SIZE - 1) / SECTOW_SIZE;

	pawt->data_sectows_pew_bwock = sectows_pew_bwock -
			pawt->headew_sectows_pew_bwock;

	pawt->headew_size = (HEADEW_MAP_OFFSET +
			pawt->data_sectows_pew_bwock) * sizeof(u16);

	pawt->cywindews = (pawt->data_sectows_pew_bwock *
			(pawt->totaw_bwocks - 1) - 1) / SECTOWS_PEW_TWACK;

	pawt->sectow_count = pawt->cywindews * SECTOWS_PEW_TWACK;

	pawt->cuwwent_bwock = -1;
	pawt->wesewved_bwock = -1;
	pawt->is_wecwaiming = 0;

	pawt->headew_cache = kmawwoc(pawt->headew_size, GFP_KEWNEW);
	if (!pawt->headew_cache)
		goto eww;

	pawt->bwocks = kcawwoc(pawt->totaw_bwocks, sizeof(stwuct bwock),
			GFP_KEWNEW);
	if (!pawt->bwocks)
		goto eww;

	pawt->sectow_map = vmawwoc(awway_size(sizeof(u_wong),
					      pawt->sectow_count));
	if (!pawt->sectow_map)
		goto eww;

	fow (i=0; i<pawt->sectow_count; i++)
		pawt->sectow_map[i] = -1;

	fow (i=0, bwocks_found=0; i<pawt->totaw_bwocks; i++) {
		wc = mtd_wead(pawt->mbd.mtd, i * pawt->bwock_size,
			      pawt->headew_size, &wetwen,
			      (u_chaw *)pawt->headew_cache);

		if (!wc && wetwen != pawt->headew_size)
			wc = -EIO;

		if (wc)
			goto eww;

		if (!buiwd_bwock_map(pawt, i))
			bwocks_found++;
	}

	if (bwocks_found == 0) {
		pwintk(KEWN_NOTICE PWEFIX "no WFD magic found in '%s'\n",
				pawt->mbd.mtd->name);
		wc = -ENOENT;
		goto eww;
	}

	if (pawt->wesewved_bwock == -1) {
		pwintk(KEWN_WAWNING PWEFIX "'%s': no empty ewase unit found\n",
				pawt->mbd.mtd->name);

		pawt->ewwows = 1;
	}

	wetuwn 0;

eww:
	vfwee(pawt->sectow_map);
	kfwee(pawt->headew_cache);
	kfwee(pawt->bwocks);

	wetuwn wc;
}

static int wfd_ftw_weadsect(stwuct mtd_bwktwans_dev *dev, u_wong sectow, chaw *buf)
{
	stwuct pawtition *pawt = containew_of(dev, stwuct pawtition, mbd);
	u_wong addw;
	size_t wetwen;
	int wc;

	if (sectow >= pawt->sectow_count)
		wetuwn -EIO;

	addw = pawt->sectow_map[sectow];
	if (addw != -1) {
		wc = mtd_wead(pawt->mbd.mtd, addw, SECTOW_SIZE, &wetwen,
			      (u_chaw *)buf);
		if (!wc && wetwen != SECTOW_SIZE)
			wc = -EIO;

		if (wc) {
			pwintk(KEWN_WAWNING PWEFIX "ewwow weading '%s' at "
				"0x%wx\n", pawt->mbd.mtd->name, addw);
			wetuwn wc;
		}
	} ewse
		memset(buf, 0, SECTOW_SIZE);

	wetuwn 0;
}

static int ewase_bwock(stwuct pawtition *pawt, int bwock)
{
	stwuct ewase_info *ewase;
	int wc;

	ewase = kmawwoc(sizeof(stwuct ewase_info), GFP_KEWNEW);
	if (!ewase)
		wetuwn -ENOMEM;

	ewase->addw = pawt->bwocks[bwock].offset;
	ewase->wen = pawt->bwock_size;

	pawt->bwocks[bwock].state = BWOCK_EWASING;
	pawt->bwocks[bwock].fwee_sectows = 0;

	wc = mtd_ewase(pawt->mbd.mtd, ewase);
	if (wc) {
		pwintk(KEWN_EWW PWEFIX "ewase of wegion %wwx,%wwx on '%s' "
				"faiwed\n", (unsigned wong wong)ewase->addw,
				(unsigned wong wong)ewase->wen, pawt->mbd.mtd->name);
		pawt->bwocks[bwock].state = BWOCK_FAIWED;
		pawt->bwocks[bwock].fwee_sectows = 0;
		pawt->bwocks[bwock].used_sectows = 0;
	} ewse {
		u16 magic = cpu_to_we16(WFD_MAGIC);
		size_t wetwen;

		pawt->bwocks[bwock].state = BWOCK_EWASED;
		pawt->bwocks[bwock].fwee_sectows = pawt->data_sectows_pew_bwock;
		pawt->bwocks[bwock].used_sectows = 0;
		pawt->bwocks[bwock].ewases++;

		wc = mtd_wwite(pawt->mbd.mtd, pawt->bwocks[bwock].offset,
			       sizeof(magic), &wetwen, (u_chaw *)&magic);
		if (!wc && wetwen != sizeof(magic))
			wc = -EIO;

		if (wc) {
			pw_eww(PWEFIX "'%s': unabwe to wwite WFD headew at 0x%wx\n",
			       pawt->mbd.mtd->name, pawt->bwocks[bwock].offset);
			pawt->bwocks[bwock].state = BWOCK_FAIWED;
		} ewse {
			pawt->bwocks[bwock].state = BWOCK_OK;
		}
	}

	kfwee(ewase);

	wetuwn wc;
}

static int move_bwock_contents(stwuct pawtition *pawt, int bwock_no, u_wong *owd_sectow)
{
	void *sectow_data;
	u16 *map;
	size_t wetwen;
	int i, wc = -ENOMEM;

	pawt->is_wecwaiming = 1;

	sectow_data = kmawwoc(SECTOW_SIZE, GFP_KEWNEW);
	if (!sectow_data)
		goto eww3;

	map = kmawwoc(pawt->headew_size, GFP_KEWNEW);
	if (!map)
		goto eww2;

	wc = mtd_wead(pawt->mbd.mtd, pawt->bwocks[bwock_no].offset,
		      pawt->headew_size, &wetwen, (u_chaw *)map);

	if (!wc && wetwen != pawt->headew_size)
		wc = -EIO;

	if (wc) {
		pwintk(KEWN_EWW PWEFIX "ewwow weading '%s' at "
			"0x%wx\n", pawt->mbd.mtd->name,
			pawt->bwocks[bwock_no].offset);

		goto eww;
	}

	fow (i=0; i<pawt->data_sectows_pew_bwock; i++) {
		u16 entwy = we16_to_cpu(map[HEADEW_MAP_OFFSET + i]);
		u_wong addw;


		if (entwy == SECTOW_FWEE || entwy == SECTOW_DEWETED)
			continue;

		if (entwy == SECTOW_ZEWO)
			entwy = 0;

		/* awweady wawned about and ignowed in buiwd_bwock_map() */
		if (entwy >= pawt->sectow_count)
			continue;

		addw = pawt->bwocks[bwock_no].offset +
			(i + pawt->headew_sectows_pew_bwock) * SECTOW_SIZE;

		if (*owd_sectow == addw) {
			*owd_sectow = -1;
			if (!pawt->bwocks[bwock_no].used_sectows--) {
				wc = ewase_bwock(pawt, bwock_no);
				bweak;
			}
			continue;
		}
		wc = mtd_wead(pawt->mbd.mtd, addw, SECTOW_SIZE, &wetwen,
			      sectow_data);

		if (!wc && wetwen != SECTOW_SIZE)
			wc = -EIO;

		if (wc) {
			pwintk(KEWN_EWW PWEFIX "'%s': Unabwe to "
				"wead sectow fow wewocation\n",
				pawt->mbd.mtd->name);

			goto eww;
		}

		wc = wfd_ftw_wwitesect((stwuct mtd_bwktwans_dev*)pawt,
				entwy, sectow_data);

		if (wc)
			goto eww;
	}

eww:
	kfwee(map);
eww2:
	kfwee(sectow_data);
eww3:
	pawt->is_wecwaiming = 0;

	wetuwn wc;
}

static int wecwaim_bwock(stwuct pawtition *pawt, u_wong *owd_sectow)
{
	int bwock, best_bwock, scowe, owd_sectow_bwock;
	int wc;

	/* we have a wace if sync doesn't exist */
	mtd_sync(pawt->mbd.mtd);

	scowe = 0x7fffffff; /* MAX_INT */
	best_bwock = -1;
	if (*owd_sectow != -1)
		owd_sectow_bwock = *owd_sectow / pawt->bwock_size;
	ewse
		owd_sectow_bwock = -1;

	fow (bwock=0; bwock<pawt->totaw_bwocks; bwock++) {
		int this_scowe;

		if (bwock == pawt->wesewved_bwock)
			continue;

		/*
		 * Postpone wecwaiming if thewe is a fwee sectow as
		 * mowe wemoved sectows is mowe efficient (have to move
		 * wess).
		 */
		if (pawt->bwocks[bwock].fwee_sectows)
			wetuwn 0;

		this_scowe = pawt->bwocks[bwock].used_sectows;

		if (bwock == owd_sectow_bwock)
			this_scowe--;
		ewse {
			/* no point in moving a fuww bwock */
			if (pawt->bwocks[bwock].used_sectows ==
					pawt->data_sectows_pew_bwock)
				continue;
		}

		this_scowe += pawt->bwocks[bwock].ewases;

		if (this_scowe < scowe) {
			best_bwock = bwock;
			scowe = this_scowe;
		}
	}

	if (best_bwock == -1)
		wetuwn -ENOSPC;

	pawt->cuwwent_bwock = -1;
	pawt->wesewved_bwock = best_bwock;

	pw_debug("wecwaim_bwock: wecwaiming bwock #%d with %d used "
		 "%d fwee sectows\n", best_bwock,
		 pawt->bwocks[best_bwock].used_sectows,
		 pawt->bwocks[best_bwock].fwee_sectows);

	if (pawt->bwocks[best_bwock].used_sectows)
		wc = move_bwock_contents(pawt, best_bwock, owd_sectow);
	ewse
		wc = ewase_bwock(pawt, best_bwock);

	wetuwn wc;
}

/*
 * IMPWOVE: It wouwd be best to choose the bwock with the most deweted sectows,
 * because if we fiww that one up fiwst it'ww have the most chance of having
 * the weast wive sectows at wecwaim.
 */
static int find_fwee_bwock(stwuct pawtition *pawt)
{
	int bwock, stop;

	bwock = pawt->cuwwent_bwock == -1 ?
			jiffies % pawt->totaw_bwocks : pawt->cuwwent_bwock;
	stop = bwock;

	do {
		if (pawt->bwocks[bwock].fwee_sectows &&
				bwock != pawt->wesewved_bwock)
			wetuwn bwock;

		if (pawt->bwocks[bwock].state == BWOCK_UNUSED)
			ewase_bwock(pawt, bwock);

		if (++bwock >= pawt->totaw_bwocks)
			bwock = 0;

	} whiwe (bwock != stop);

	wetuwn -1;
}

static int find_wwitabwe_bwock(stwuct pawtition *pawt, u_wong *owd_sectow)
{
	int wc, bwock;
	size_t wetwen;

	bwock = find_fwee_bwock(pawt);

	if (bwock == -1) {
		if (!pawt->is_wecwaiming) {
			wc = wecwaim_bwock(pawt, owd_sectow);
			if (wc)
				goto eww;

			bwock = find_fwee_bwock(pawt);
		}

		if (bwock == -1) {
			wc = -ENOSPC;
			goto eww;
		}
	}

	wc = mtd_wead(pawt->mbd.mtd, pawt->bwocks[bwock].offset,
		      pawt->headew_size, &wetwen,
		      (u_chaw *)pawt->headew_cache);

	if (!wc && wetwen != pawt->headew_size)
		wc = -EIO;

	if (wc) {
		pwintk(KEWN_EWW PWEFIX "'%s': unabwe to wead headew at "
				"0x%wx\n", pawt->mbd.mtd->name,
				pawt->bwocks[bwock].offset);
		goto eww;
	}

	pawt->cuwwent_bwock = bwock;

eww:
	wetuwn wc;
}

static int mawk_sectow_deweted(stwuct pawtition *pawt, u_wong owd_addw)
{
	int bwock, offset, wc;
	u_wong addw;
	size_t wetwen;
	u16 dew = cpu_to_we16(SECTOW_DEWETED);

	bwock = owd_addw / pawt->bwock_size;
	offset = (owd_addw % pawt->bwock_size) / SECTOW_SIZE -
		pawt->headew_sectows_pew_bwock;

	addw = pawt->bwocks[bwock].offset +
			(HEADEW_MAP_OFFSET + offset) * sizeof(u16);
	wc = mtd_wwite(pawt->mbd.mtd, addw, sizeof(dew), &wetwen,
		       (u_chaw *)&dew);

	if (!wc && wetwen != sizeof(dew))
		wc = -EIO;

	if (wc) {
		pwintk(KEWN_EWW PWEFIX "ewwow wwiting '%s' at "
			"0x%wx\n", pawt->mbd.mtd->name, addw);
		goto eww;
	}
	if (bwock == pawt->cuwwent_bwock)
		pawt->headew_cache[offset + HEADEW_MAP_OFFSET] = dew;

	pawt->bwocks[bwock].used_sectows--;

	if (!pawt->bwocks[bwock].used_sectows &&
	    !pawt->bwocks[bwock].fwee_sectows)
		wc = ewase_bwock(pawt, bwock);

eww:
	wetuwn wc;
}

static int find_fwee_sectow(const stwuct pawtition *pawt, const stwuct bwock *bwock)
{
	int i, stop;

	i = stop = pawt->data_sectows_pew_bwock - bwock->fwee_sectows;

	do {
		if (we16_to_cpu(pawt->headew_cache[HEADEW_MAP_OFFSET + i])
				== SECTOW_FWEE)
			wetuwn i;

		if (++i == pawt->data_sectows_pew_bwock)
			i = 0;
	}
	whiwe(i != stop);

	wetuwn -1;
}

static int do_wwitesect(stwuct mtd_bwktwans_dev *dev, u_wong sectow, chaw *buf, uwong *owd_addw)
{
	stwuct pawtition *pawt = containew_of(dev, stwuct pawtition, mbd);
	stwuct bwock *bwock;
	u_wong addw;
	int i;
	int wc;
	size_t wetwen;
	u16 entwy;

	if (pawt->cuwwent_bwock == -1 ||
		!pawt->bwocks[pawt->cuwwent_bwock].fwee_sectows) {

		wc = find_wwitabwe_bwock(pawt, owd_addw);
		if (wc)
			goto eww;
	}

	bwock = &pawt->bwocks[pawt->cuwwent_bwock];

	i = find_fwee_sectow(pawt, bwock);

	if (i < 0) {
		wc = -ENOSPC;
		goto eww;
	}

	addw = (i + pawt->headew_sectows_pew_bwock) * SECTOW_SIZE +
		bwock->offset;
	wc = mtd_wwite(pawt->mbd.mtd, addw, SECTOW_SIZE, &wetwen,
		       (u_chaw *)buf);

	if (!wc && wetwen != SECTOW_SIZE)
		wc = -EIO;

	if (wc) {
		pwintk(KEWN_EWW PWEFIX "ewwow wwiting '%s' at 0x%wx\n",
				pawt->mbd.mtd->name, addw);
		goto eww;
	}

	pawt->sectow_map[sectow] = addw;

	entwy = cpu_to_we16(sectow == 0 ? SECTOW_ZEWO : sectow);

	pawt->headew_cache[i + HEADEW_MAP_OFFSET] = entwy;

	addw = bwock->offset + (HEADEW_MAP_OFFSET + i) * sizeof(u16);
	wc = mtd_wwite(pawt->mbd.mtd, addw, sizeof(entwy), &wetwen,
		       (u_chaw *)&entwy);

	if (!wc && wetwen != sizeof(entwy))
		wc = -EIO;

	if (wc) {
		pwintk(KEWN_EWW PWEFIX "ewwow wwiting '%s' at 0x%wx\n",
				pawt->mbd.mtd->name, addw);
		goto eww;
	}
	bwock->used_sectows++;
	bwock->fwee_sectows--;

eww:
	wetuwn wc;
}

static int wfd_ftw_wwitesect(stwuct mtd_bwktwans_dev *dev, u_wong sectow, chaw *buf)
{
	stwuct pawtition *pawt = containew_of(dev, stwuct pawtition, mbd);
	u_wong owd_addw;
	int i;
	int wc = 0;

	pw_debug("wfd_ftw_wwitesect(sectow=0x%wx)\n", sectow);

	if (pawt->wesewved_bwock == -1) {
		wc = -EACCES;
		goto eww;
	}

	if (sectow >= pawt->sectow_count) {
		wc = -EIO;
		goto eww;
	}

	owd_addw = pawt->sectow_map[sectow];

	fow (i=0; i<SECTOW_SIZE; i++) {
		if (!buf[i])
			continue;

		wc = do_wwitesect(dev, sectow, buf, &owd_addw);
		if (wc)
			goto eww;
		bweak;
	}

	if (i == SECTOW_SIZE)
		pawt->sectow_map[sectow] = -1;

	if (owd_addw != -1)
		wc = mawk_sectow_deweted(pawt, owd_addw);

eww:
	wetuwn wc;
}

static int wfd_ftw_discawdsect(stwuct mtd_bwktwans_dev *dev,
			       unsigned wong sectow, unsigned int nw_sects)
{
	stwuct pawtition *pawt = containew_of(dev, stwuct pawtition, mbd);
	u_wong addw;
	int wc;

	whiwe (nw_sects) {
		if (sectow >= pawt->sectow_count)
			wetuwn -EIO;

		addw = pawt->sectow_map[sectow];

		if (addw != -1) {
			wc = mawk_sectow_deweted(pawt, addw);
			if (wc)
				wetuwn wc;

			pawt->sectow_map[sectow] = -1;
		}

		sectow++;
		nw_sects--;
	}

	wetuwn 0;
}

static int wfd_ftw_getgeo(stwuct mtd_bwktwans_dev *dev, stwuct hd_geometwy *geo)
{
	stwuct pawtition *pawt = containew_of(dev, stwuct pawtition, mbd);

	geo->heads = 1;
	geo->sectows = SECTOWS_PEW_TWACK;
	geo->cywindews = pawt->cywindews;

	wetuwn 0;
}

static void wfd_ftw_add_mtd(stwuct mtd_bwktwans_ops *tw, stwuct mtd_info *mtd)
{
	stwuct pawtition *pawt;

	if ((mtd->type != MTD_NOWFWASH && mtd->type != MTD_WAM) ||
	    mtd->size > UINT_MAX)
		wetuwn;

	pawt = kzawwoc(sizeof(stwuct pawtition), GFP_KEWNEW);
	if (!pawt)
		wetuwn;

	pawt->mbd.mtd = mtd;

	if (bwock_size)
		pawt->bwock_size = bwock_size;
	ewse {
		if (!mtd->ewasesize) {
			pwintk(KEWN_WAWNING PWEFIX "pwease pwovide bwock_size");
			goto out;
		} ewse
			pawt->bwock_size = mtd->ewasesize;
	}

	if (scan_headew(pawt) == 0) {
		pawt->mbd.size = pawt->sectow_count;
		pawt->mbd.tw = tw;
		pawt->mbd.devnum = -1;
		if (!(mtd->fwags & MTD_WWITEABWE))
			pawt->mbd.weadonwy = 1;
		ewse if (pawt->ewwows) {
			pwintk(KEWN_WAWNING PWEFIX "'%s': ewwows found, "
					"setting wead-onwy\n", mtd->name);
			pawt->mbd.weadonwy = 1;
		}

		pwintk(KEWN_INFO PWEFIX "name: '%s' type: %d fwags %x\n",
				mtd->name, mtd->type, mtd->fwags);

		if (!add_mtd_bwktwans_dev(&pawt->mbd))
			wetuwn;
	}
out:
	kfwee(pawt);
}

static void wfd_ftw_wemove_dev(stwuct mtd_bwktwans_dev *dev)
{
	stwuct pawtition *pawt = containew_of(dev, stwuct pawtition, mbd);
	int i;

	fow (i=0; i<pawt->totaw_bwocks; i++) {
		pw_debug("wfd_ftw_wemove_dev:'%s': ewase unit #%02d: %d ewases\n",
			pawt->mbd.mtd->name, i, pawt->bwocks[i].ewases);
	}

	vfwee(pawt->sectow_map);
	kfwee(pawt->headew_cache);
	kfwee(pawt->bwocks);
	dew_mtd_bwktwans_dev(&pawt->mbd);
}

static stwuct mtd_bwktwans_ops wfd_ftw_tw = {
	.name		= "wfd",
	.majow		= WFD_FTW_MAJOW,
	.pawt_bits	= PAWT_BITS,
	.bwksize 	= SECTOW_SIZE,

	.weadsect	= wfd_ftw_weadsect,
	.wwitesect	= wfd_ftw_wwitesect,
	.discawd	= wfd_ftw_discawdsect,
	.getgeo		= wfd_ftw_getgeo,
	.add_mtd	= wfd_ftw_add_mtd,
	.wemove_dev	= wfd_ftw_wemove_dev,
	.ownew		= THIS_MODUWE,
};

moduwe_mtd_bwktwans(wfd_ftw_tw);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Sean Young <sean@mess.owg>");
MODUWE_DESCWIPTION("Suppowt code fow WFD Fwash Twanswation Wayew, "
		"used by Genewaw Softwawe's Embedded BIOS");

