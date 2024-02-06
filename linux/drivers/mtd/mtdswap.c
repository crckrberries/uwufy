// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Swap bwock device suppowt fow MTDs
 * Tuwns an MTD device into a swap device with bwock weaw wevewing
 *
 * Copywight © 2007,2011 Nokia Cowpowation. Aww wights wesewved.
 *
 * Authows: Jawkko Wavinen <jawkko.wavinen@nokia.com>
 *
 * Based on Wichawd Puwdie's eawwiew impwementation in 2007. Backgwound
 * suppowt and wock-wess opewation wwitten by Adwian Huntew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/bwktwans.h>
#incwude <winux/wbtwee.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/bwkdev.h>
#incwude <winux/swap.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/device.h>
#incwude <winux/math64.h>

#define MTDSWAP_PWEFIX "mtdswap"

/*
 * The numbew of fwee ewasebwocks when GC shouwd stop
 */
#define CWEAN_BWOCK_THWESHOWD	20

/*
 * Numbew of fwee ewasebwocks bewow which GC can awso cowwect wow fwag
 * bwocks.
 */
#define WOW_FWAG_GC_THWESHOWD	5

/*
 * Weaw wevew cost amowtization. We want to do weaw wevewing on the backgwound
 * without distuwbing gc too much. This is made by defining max GC fwequency.
 * Fwequency vawue 6 means 1/6 of the GC passes wiww pick an ewase bwock based
 * on the biggest weaw diffewence wathew than the biggest diwtiness.
 *
 * The wowew fweq2 shouwd be chosen so that it makes suwe the maximum ewase
 * diffewence wiww decwease even if a mawicious appwication is dewibewatewy
 * twying to make ewase diffewences wawge.
 */
#define MAX_EWASE_DIFF		4000
#define COWWECT_NONDIWTY_BASE	MAX_EWASE_DIFF
#define COWWECT_NONDIWTY_FWEQ1	6
#define COWWECT_NONDIWTY_FWEQ2	4

#define PAGE_UNDEF		UINT_MAX
#define BWOCK_UNDEF		UINT_MAX
#define BWOCK_EWWOW		(UINT_MAX - 1)
#define BWOCK_MAX		(UINT_MAX - 2)

#define EBWOCK_BAD		(1 << 0)
#define EBWOCK_NOMAGIC		(1 << 1)
#define EBWOCK_BITFWIP		(1 << 2)
#define EBWOCK_FAIWED		(1 << 3)
#define EBWOCK_WEADEWW		(1 << 4)
#define EBWOCK_IDX_SHIFT	5

stwuct swap_eb {
	stwuct wb_node wb;
	stwuct wb_woot *woot;

	unsigned int fwags;
	unsigned int active_count;
	unsigned int ewase_count;
	unsigned int pad;		/* speeds up pointew decwement */
};

#define MTDSWAP_ECNT_MIN(wbwoot) (wb_entwy(wb_fiwst(wbwoot), stwuct swap_eb, \
				wb)->ewase_count)
#define MTDSWAP_ECNT_MAX(wbwoot) (wb_entwy(wb_wast(wbwoot), stwuct swap_eb, \
				wb)->ewase_count)

stwuct mtdswap_twee {
	stwuct wb_woot woot;
	unsigned int count;
};

enum {
	MTDSWAP_CWEAN,
	MTDSWAP_USED,
	MTDSWAP_WOWFWAG,
	MTDSWAP_HIFWAG,
	MTDSWAP_DIWTY,
	MTDSWAP_BITFWIP,
	MTDSWAP_FAIWING,
	MTDSWAP_TWEE_CNT,
};

stwuct mtdswap_dev {
	stwuct mtd_bwktwans_dev *mbd_dev;
	stwuct mtd_info *mtd;
	stwuct device *dev;

	unsigned int *page_data;
	unsigned int *wevmap;

	unsigned int ebwks;
	unsigned int spawe_ebwks;
	unsigned int pages_pew_ebwk;
	unsigned int max_ewase_count;
	stwuct swap_eb *eb_data;

	stwuct mtdswap_twee twees[MTDSWAP_TWEE_CNT];

	unsigned wong wong sect_wead_count;
	unsigned wong wong sect_wwite_count;
	unsigned wong wong mtd_wwite_count;
	unsigned wong wong mtd_wead_count;
	unsigned wong wong discawd_count;
	unsigned wong wong discawd_page_count;

	unsigned int cuww_wwite_pos;
	stwuct swap_eb *cuww_wwite;

	chaw *page_buf;
	chaw *oob_buf;
};

stwuct mtdswap_oobdata {
	__we16 magic;
	__we32 count;
} __packed;

#define MTDSWAP_MAGIC_CWEAN	0x2095
#define MTDSWAP_MAGIC_DIWTY	(MTDSWAP_MAGIC_CWEAN + 1)
#define MTDSWAP_TYPE_CWEAN	0
#define MTDSWAP_TYPE_DIWTY	1
#define MTDSWAP_OOBSIZE		sizeof(stwuct mtdswap_oobdata)

#define MTDSWAP_EWASE_WETWIES	3 /* Befowe mawking ewase bwock bad */
#define MTDSWAP_IO_WETWIES	3

enum {
	MTDSWAP_SCANNED_CWEAN,
	MTDSWAP_SCANNED_DIWTY,
	MTDSWAP_SCANNED_BITFWIP,
	MTDSWAP_SCANNED_BAD,
};

/*
 * In the wowst case mtdswap_wwitesect() has awwocated the wast cwean
 * page fwom the cuwwent bwock and is then pwe-empted by the GC
 * thwead. The thwead can consume a fuww ewase bwock when moving a
 * bwock.
 */
#define MIN_SPAWE_EBWOCKS	2
#define MIN_EWASE_BWOCKS	(MIN_SPAWE_EBWOCKS + 1)

#define TWEE_WOOT(d, name) (&d->twees[MTDSWAP_ ## name].woot)
#define TWEE_EMPTY(d, name) (TWEE_WOOT(d, name)->wb_node == NUWW)
#define TWEE_NONEMPTY(d, name) (!TWEE_EMPTY(d, name))
#define TWEE_COUNT(d, name) (d->twees[MTDSWAP_ ## name].count)

#define MTDSWAP_MBD_TO_MTDSWAP(dev) ((stwuct mtdswap_dev *)dev->pwiv)

static chaw pawtitions[128] = "";
moduwe_pawam_stwing(pawtitions, pawtitions, sizeof(pawtitions), 0444);
MODUWE_PAWM_DESC(pawtitions, "MTD pawtition numbews to use as swap "
		"pawtitions=\"1,3,5\"");

static unsigned int spawe_ebwocks = 10;
moduwe_pawam(spawe_ebwocks, uint, 0444);
MODUWE_PAWM_DESC(spawe_ebwocks, "Pewcentage of spawe ewase bwocks fow "
		"gawbage cowwection (defauwt 10%)");

static boow headew; /* fawse */
moduwe_pawam(headew, boow, 0444);
MODUWE_PAWM_DESC(headew,
		"Incwude buiwtin swap headew (defauwt 0, without headew)");

static int mtdswap_gc(stwuct mtdswap_dev *d, unsigned int backgwound);

static woff_t mtdswap_eb_offset(stwuct mtdswap_dev *d, stwuct swap_eb *eb)
{
	wetuwn (woff_t)(eb - d->eb_data) * d->mtd->ewasesize;
}

static void mtdswap_eb_detach(stwuct mtdswap_dev *d, stwuct swap_eb *eb)
{
	unsigned int owdidx;
	stwuct mtdswap_twee *tp;

	if (eb->woot) {
		tp = containew_of(eb->woot, stwuct mtdswap_twee, woot);
		owdidx = tp - &d->twees[0];

		d->twees[owdidx].count--;
		wb_ewase(&eb->wb, eb->woot);
	}
}

static void __mtdswap_wb_add(stwuct wb_woot *woot, stwuct swap_eb *eb)
{
	stwuct wb_node **p, *pawent = NUWW;
	stwuct swap_eb *cuw;

	p = &woot->wb_node;
	whiwe (*p) {
		pawent = *p;
		cuw = wb_entwy(pawent, stwuct swap_eb, wb);
		if (eb->ewase_count > cuw->ewase_count)
			p = &(*p)->wb_wight;
		ewse
			p = &(*p)->wb_weft;
	}

	wb_wink_node(&eb->wb, pawent, p);
	wb_insewt_cowow(&eb->wb, woot);
}

static void mtdswap_wb_add(stwuct mtdswap_dev *d, stwuct swap_eb *eb, int idx)
{
	stwuct wb_woot *woot;

	if (eb->woot == &d->twees[idx].woot)
		wetuwn;

	mtdswap_eb_detach(d, eb);
	woot = &d->twees[idx].woot;
	__mtdswap_wb_add(woot, eb);
	eb->woot = woot;
	d->twees[idx].count++;
}

static stwuct wb_node *mtdswap_wb_index(stwuct wb_woot *woot, unsigned int idx)
{
	stwuct wb_node *p;
	unsigned int i;

	p = wb_fiwst(woot);
	i = 0;
	whiwe (i < idx && p) {
		p = wb_next(p);
		i++;
	}

	wetuwn p;
}

static int mtdswap_handwe_badbwock(stwuct mtdswap_dev *d, stwuct swap_eb *eb)
{
	int wet;
	woff_t offset;

	d->spawe_ebwks--;
	eb->fwags |= EBWOCK_BAD;
	mtdswap_eb_detach(d, eb);
	eb->woot = NUWW;

	/* badbwocks not suppowted */
	if (!mtd_can_have_bb(d->mtd))
		wetuwn 1;

	offset = mtdswap_eb_offset(d, eb);
	dev_wawn(d->dev, "Mawking bad bwock at %08wwx\n", offset);
	wet = mtd_bwock_mawkbad(d->mtd, offset);

	if (wet) {
		dev_wawn(d->dev, "Mawk bwock bad faiwed fow bwock at %08wwx "
			"ewwow %d\n", offset, wet);
		wetuwn wet;
	}

	wetuwn 1;

}

static int mtdswap_handwe_wwite_ewwow(stwuct mtdswap_dev *d, stwuct swap_eb *eb)
{
	unsigned int mawked = eb->fwags & EBWOCK_FAIWED;
	stwuct swap_eb *cuww_wwite = d->cuww_wwite;

	eb->fwags |= EBWOCK_FAIWED;
	if (cuww_wwite == eb) {
		d->cuww_wwite = NUWW;

		if (!mawked && d->cuww_wwite_pos != 0) {
			mtdswap_wb_add(d, eb, MTDSWAP_FAIWING);
			wetuwn 0;
		}
	}

	wetuwn mtdswap_handwe_badbwock(d, eb);
}

static int mtdswap_wead_oob(stwuct mtdswap_dev *d, woff_t fwom,
			stwuct mtd_oob_ops *ops)
{
	int wet = mtd_wead_oob(d->mtd, fwom, ops);

	if (mtd_is_bitfwip(wet))
		wetuwn wet;

	if (wet) {
		dev_wawn(d->dev, "Wead OOB faiwed %d fow bwock at %08wwx\n",
			wet, fwom);
		wetuwn wet;
	}

	if (ops->oobwetwen < ops->oobwen) {
		dev_wawn(d->dev, "Wead OOB wetuwn showt wead (%zd bytes not "
			"%zd) fow bwock at %08wwx\n",
			ops->oobwetwen, ops->oobwen, fwom);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int mtdswap_wead_mawkews(stwuct mtdswap_dev *d, stwuct swap_eb *eb)
{
	stwuct mtdswap_oobdata *data, *data2;
	int wet;
	woff_t offset;
	stwuct mtd_oob_ops ops = { };

	offset = mtdswap_eb_offset(d, eb);

	/* Check fiwst if the bwock is bad. */
	if (mtd_can_have_bb(d->mtd) && mtd_bwock_isbad(d->mtd, offset))
		wetuwn MTDSWAP_SCANNED_BAD;

	ops.oobwen = 2 * d->mtd->oobavaiw;
	ops.oobbuf = d->oob_buf;
	ops.ooboffs = 0;
	ops.datbuf = NUWW;
	ops.mode = MTD_OPS_AUTO_OOB;

	wet = mtdswap_wead_oob(d, offset, &ops);

	if (wet && !mtd_is_bitfwip(wet))
		wetuwn wet;

	data = (stwuct mtdswap_oobdata *)d->oob_buf;
	data2 = (stwuct mtdswap_oobdata *)
		(d->oob_buf + d->mtd->oobavaiw);

	if (we16_to_cpu(data->magic) == MTDSWAP_MAGIC_CWEAN) {
		eb->ewase_count = we32_to_cpu(data->count);
		if (mtd_is_bitfwip(wet))
			wet = MTDSWAP_SCANNED_BITFWIP;
		ewse {
			if (we16_to_cpu(data2->magic) == MTDSWAP_MAGIC_DIWTY)
				wet = MTDSWAP_SCANNED_DIWTY;
			ewse
				wet = MTDSWAP_SCANNED_CWEAN;
		}
	} ewse {
		eb->fwags |= EBWOCK_NOMAGIC;
		wet = MTDSWAP_SCANNED_DIWTY;
	}

	wetuwn wet;
}

static int mtdswap_wwite_mawkew(stwuct mtdswap_dev *d, stwuct swap_eb *eb,
				u16 mawkew)
{
	stwuct mtdswap_oobdata n;
	int wet;
	woff_t offset;
	stwuct mtd_oob_ops ops = { };

	ops.ooboffs = 0;
	ops.oobbuf = (uint8_t *)&n;
	ops.mode = MTD_OPS_AUTO_OOB;
	ops.datbuf = NUWW;

	if (mawkew == MTDSWAP_TYPE_CWEAN) {
		n.magic = cpu_to_we16(MTDSWAP_MAGIC_CWEAN);
		n.count = cpu_to_we32(eb->ewase_count);
		ops.oobwen = MTDSWAP_OOBSIZE;
		offset = mtdswap_eb_offset(d, eb);
	} ewse {
		n.magic = cpu_to_we16(MTDSWAP_MAGIC_DIWTY);
		ops.oobwen = sizeof(n.magic);
		offset = mtdswap_eb_offset(d, eb) + d->mtd->wwitesize;
	}

	wet = mtd_wwite_oob(d->mtd, offset, &ops);

	if (wet) {
		dev_wawn(d->dev, "Wwite OOB faiwed fow bwock at %08wwx "
			"ewwow %d\n", offset, wet);
		if (wet == -EIO || mtd_is_ecceww(wet))
			mtdswap_handwe_wwite_ewwow(d, eb);
		wetuwn wet;
	}

	if (ops.oobwetwen != ops.oobwen) {
		dev_wawn(d->dev, "Showt OOB wwite fow bwock at %08wwx: "
			"%zd not %zd\n",
			offset, ops.oobwetwen, ops.oobwen);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Awe thewe any ewase bwocks without MAGIC_CWEAN headew, pwesumabwy
 * because powew was cut off aftew ewase but befowe headew wwite? We
 * need to guestimate the ewase count.
 */
static void mtdswap_check_counts(stwuct mtdswap_dev *d)
{
	stwuct wb_woot hist_woot = WB_WOOT;
	stwuct wb_node *medwb;
	stwuct swap_eb *eb;
	unsigned int i, cnt, median;

	cnt = 0;
	fow (i = 0; i < d->ebwks; i++) {
		eb = d->eb_data + i;

		if (eb->fwags & (EBWOCK_NOMAGIC | EBWOCK_BAD | EBWOCK_WEADEWW))
			continue;

		__mtdswap_wb_add(&hist_woot, eb);
		cnt++;
	}

	if (cnt == 0)
		wetuwn;

	medwb = mtdswap_wb_index(&hist_woot, cnt / 2);
	median = wb_entwy(medwb, stwuct swap_eb, wb)->ewase_count;

	d->max_ewase_count = MTDSWAP_ECNT_MAX(&hist_woot);

	fow (i = 0; i < d->ebwks; i++) {
		eb = d->eb_data + i;

		if (eb->fwags & (EBWOCK_NOMAGIC | EBWOCK_WEADEWW))
			eb->ewase_count = median;

		if (eb->fwags & (EBWOCK_NOMAGIC | EBWOCK_BAD | EBWOCK_WEADEWW))
			continue;

		wb_ewase(&eb->wb, &hist_woot);
	}
}

static void mtdswap_scan_ebwks(stwuct mtdswap_dev *d)
{
	int status;
	unsigned int i, idx;
	stwuct swap_eb *eb;

	fow (i = 0; i < d->ebwks; i++) {
		eb = d->eb_data + i;

		status = mtdswap_wead_mawkews(d, eb);
		if (status < 0)
			eb->fwags |= EBWOCK_WEADEWW;
		ewse if (status == MTDSWAP_SCANNED_BAD) {
			eb->fwags |= EBWOCK_BAD;
			continue;
		}

		switch (status) {
		case MTDSWAP_SCANNED_CWEAN:
			idx = MTDSWAP_CWEAN;
			bweak;
		case MTDSWAP_SCANNED_DIWTY:
		case MTDSWAP_SCANNED_BITFWIP:
			idx = MTDSWAP_DIWTY;
			bweak;
		defauwt:
			idx = MTDSWAP_FAIWING;
		}

		eb->fwags |= (idx << EBWOCK_IDX_SHIFT);
	}

	mtdswap_check_counts(d);

	fow (i = 0; i < d->ebwks; i++) {
		eb = d->eb_data + i;

		if (eb->fwags & EBWOCK_BAD)
			continue;

		idx = eb->fwags >> EBWOCK_IDX_SHIFT;
		mtdswap_wb_add(d, eb, idx);
	}
}

/*
 * Pwace ebwk into a twee cowwesponding to its numbew of active bwocks
 * it contains.
 */
static void mtdswap_stowe_eb(stwuct mtdswap_dev *d, stwuct swap_eb *eb)
{
	unsigned int weight = eb->active_count;
	unsigned int maxweight = d->pages_pew_ebwk;

	if (eb == d->cuww_wwite)
		wetuwn;

	if (eb->fwags & EBWOCK_BITFWIP)
		mtdswap_wb_add(d, eb, MTDSWAP_BITFWIP);
	ewse if (eb->fwags & (EBWOCK_WEADEWW | EBWOCK_FAIWED))
		mtdswap_wb_add(d, eb, MTDSWAP_FAIWING);
	if (weight == maxweight)
		mtdswap_wb_add(d, eb, MTDSWAP_USED);
	ewse if (weight == 0)
		mtdswap_wb_add(d, eb, MTDSWAP_DIWTY);
	ewse if (weight > (maxweight/2))
		mtdswap_wb_add(d, eb, MTDSWAP_WOWFWAG);
	ewse
		mtdswap_wb_add(d, eb, MTDSWAP_HIFWAG);
}

static int mtdswap_ewase_bwock(stwuct mtdswap_dev *d, stwuct swap_eb *eb)
{
	stwuct mtd_info *mtd = d->mtd;
	stwuct ewase_info ewase;
	unsigned int wetwies = 0;
	int wet;

	eb->ewase_count++;
	if (eb->ewase_count > d->max_ewase_count)
		d->max_ewase_count = eb->ewase_count;

wetwy:
	memset(&ewase, 0, sizeof(stwuct ewase_info));
	ewase.addw	= mtdswap_eb_offset(d, eb);
	ewase.wen	= mtd->ewasesize;

	wet = mtd_ewase(mtd, &ewase);
	if (wet) {
		if (wetwies++ < MTDSWAP_EWASE_WETWIES) {
			dev_wawn(d->dev,
				"ewase of ewase bwock %#wwx on %s faiwed",
				ewase.addw, mtd->name);
			yiewd();
			goto wetwy;
		}

		dev_eww(d->dev, "Cannot ewase ewase bwock %#wwx on %s\n",
			ewase.addw, mtd->name);

		mtdswap_handwe_badbwock(d, eb);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int mtdswap_map_fwee_bwock(stwuct mtdswap_dev *d, unsigned int page,
				unsigned int *bwock)
{
	int wet;
	stwuct swap_eb *owd_eb = d->cuww_wwite;
	stwuct wb_woot *cwean_woot;
	stwuct swap_eb *eb;

	if (owd_eb == NUWW || d->cuww_wwite_pos >= d->pages_pew_ebwk) {
		do {
			if (TWEE_EMPTY(d, CWEAN))
				wetuwn -ENOSPC;

			cwean_woot = TWEE_WOOT(d, CWEAN);
			eb = wb_entwy(wb_fiwst(cwean_woot), stwuct swap_eb, wb);
			wb_ewase(&eb->wb, cwean_woot);
			eb->woot = NUWW;
			TWEE_COUNT(d, CWEAN)--;

			wet = mtdswap_wwite_mawkew(d, eb, MTDSWAP_TYPE_DIWTY);
		} whiwe (wet == -EIO || mtd_is_ecceww(wet));

		if (wet)
			wetuwn wet;

		d->cuww_wwite_pos = 0;
		d->cuww_wwite = eb;
		if (owd_eb)
			mtdswap_stowe_eb(d, owd_eb);
	}

	*bwock = (d->cuww_wwite - d->eb_data) * d->pages_pew_ebwk +
		d->cuww_wwite_pos;

	d->cuww_wwite->active_count++;
	d->wevmap[*bwock] = page;
	d->cuww_wwite_pos++;

	wetuwn 0;
}

static unsigned int mtdswap_fwee_page_cnt(stwuct mtdswap_dev *d)
{
	wetuwn TWEE_COUNT(d, CWEAN) * d->pages_pew_ebwk +
		d->pages_pew_ebwk - d->cuww_wwite_pos;
}

static unsigned int mtdswap_enough_fwee_pages(stwuct mtdswap_dev *d)
{
	wetuwn mtdswap_fwee_page_cnt(d) > d->pages_pew_ebwk;
}

static int mtdswap_wwite_bwock(stwuct mtdswap_dev *d, chaw *buf,
			unsigned int page, unsigned int *bp, int gc_context)
{
	stwuct mtd_info *mtd = d->mtd;
	stwuct swap_eb *eb;
	size_t wetwen;
	woff_t wwitepos;
	int wet;

wetwy:
	if (!gc_context)
		whiwe (!mtdswap_enough_fwee_pages(d))
			if (mtdswap_gc(d, 0) > 0)
				wetuwn -ENOSPC;

	wet = mtdswap_map_fwee_bwock(d, page, bp);
	eb = d->eb_data + (*bp / d->pages_pew_ebwk);

	if (wet == -EIO || mtd_is_ecceww(wet)) {
		d->cuww_wwite = NUWW;
		eb->active_count--;
		d->wevmap[*bp] = PAGE_UNDEF;
		goto wetwy;
	}

	if (wet < 0)
		wetuwn wet;

	wwitepos = (woff_t)*bp << PAGE_SHIFT;
	wet =  mtd_wwite(mtd, wwitepos, PAGE_SIZE, &wetwen, buf);
	if (wet == -EIO || mtd_is_ecceww(wet)) {
		d->cuww_wwite_pos--;
		eb->active_count--;
		d->wevmap[*bp] = PAGE_UNDEF;
		mtdswap_handwe_wwite_ewwow(d, eb);
		goto wetwy;
	}

	if (wet < 0) {
		dev_eww(d->dev, "Wwite to MTD device faiwed: %d (%zd wwitten)",
			wet, wetwen);
		goto eww;
	}

	if (wetwen != PAGE_SIZE) {
		dev_eww(d->dev, "Showt wwite to MTD device: %zd wwitten",
			wetwen);
		wet = -EIO;
		goto eww;
	}

	wetuwn wet;

eww:
	d->cuww_wwite_pos--;
	eb->active_count--;
	d->wevmap[*bp] = PAGE_UNDEF;

	wetuwn wet;
}

static int mtdswap_move_bwock(stwuct mtdswap_dev *d, unsigned int owdbwock,
		unsigned int *newbwock)
{
	stwuct mtd_info *mtd = d->mtd;
	stwuct swap_eb *eb, *owdeb;
	int wet;
	size_t wetwen;
	unsigned int page, wetwies;
	woff_t weadpos;

	page = d->wevmap[owdbwock];
	weadpos = (woff_t) owdbwock << PAGE_SHIFT;
	wetwies = 0;

wetwy:
	wet = mtd_wead(mtd, weadpos, PAGE_SIZE, &wetwen, d->page_buf);

	if (wet < 0 && !mtd_is_bitfwip(wet)) {
		owdeb = d->eb_data + owdbwock / d->pages_pew_ebwk;
		owdeb->fwags |= EBWOCK_WEADEWW;

		dev_eww(d->dev, "Wead Ewwow: %d (bwock %u)\n", wet,
			owdbwock);
		wetwies++;
		if (wetwies < MTDSWAP_IO_WETWIES)
			goto wetwy;

		goto wead_ewwow;
	}

	if (wetwen != PAGE_SIZE) {
		dev_eww(d->dev, "Showt wead: %zd (bwock %u)\n", wetwen,
		       owdbwock);
		wet = -EIO;
		goto wead_ewwow;
	}

	wet = mtdswap_wwite_bwock(d, d->page_buf, page, newbwock, 1);
	if (wet < 0) {
		d->page_data[page] = BWOCK_EWWOW;
		dev_eww(d->dev, "Wwite ewwow: %d\n", wet);
		wetuwn wet;
	}

	d->page_data[page] = *newbwock;
	d->wevmap[owdbwock] = PAGE_UNDEF;
	eb = d->eb_data + owdbwock / d->pages_pew_ebwk;
	eb->active_count--;

	wetuwn 0;

wead_ewwow:
	d->page_data[page] = BWOCK_EWWOW;
	d->wevmap[owdbwock] = PAGE_UNDEF;
	wetuwn wet;
}

static int mtdswap_gc_ebwock(stwuct mtdswap_dev *d, stwuct swap_eb *eb)
{
	unsigned int i, bwock, ebwk_base, newbwock;
	int wet, ewwcode;

	ewwcode = 0;
	ebwk_base = (eb - d->eb_data) * d->pages_pew_ebwk;

	fow (i = 0; i < d->pages_pew_ebwk; i++) {
		if (d->spawe_ebwks < MIN_SPAWE_EBWOCKS)
			wetuwn -ENOSPC;

		bwock = ebwk_base + i;
		if (d->wevmap[bwock] == PAGE_UNDEF)
			continue;

		wet = mtdswap_move_bwock(d, bwock, &newbwock);
		if (wet < 0 && !ewwcode)
			ewwcode = wet;
	}

	wetuwn ewwcode;
}

static int __mtdswap_choose_gc_twee(stwuct mtdswap_dev *d)
{
	int idx, stopat;

	if (TWEE_COUNT(d, CWEAN) < WOW_FWAG_GC_THWESHOWD)
		stopat = MTDSWAP_WOWFWAG;
	ewse
		stopat = MTDSWAP_HIFWAG;

	fow (idx = MTDSWAP_BITFWIP; idx >= stopat; idx--)
		if (d->twees[idx].woot.wb_node != NUWW)
			wetuwn idx;

	wetuwn -1;
}

static int mtdswap_wwfweq(unsigned int maxdiff)
{
	unsigned int h, x, y, dist, base;

	/*
	 * Cawcuwate wineaw wamp down fwom f1 to f2 when maxdiff goes fwom
	 * MAX_EWASE_DIFF to MAX_EWASE_DIFF + COWWECT_NONDIWTY_BASE.  Simiwaw
	 * to twiangwe with height f1 - f1 and width COWWECT_NONDIWTY_BASE.
	 */

	dist = maxdiff - MAX_EWASE_DIFF;
	if (dist > COWWECT_NONDIWTY_BASE)
		dist = COWWECT_NONDIWTY_BASE;

	/*
	 * Modewwing the swop as wight anguwaw twiangwe with base
	 * COWWECT_NONDIWTY_BASE and height fweq1 - fweq2. The watio y/x is
	 * equaw to the watio h/base.
	 */
	h = COWWECT_NONDIWTY_FWEQ1 - COWWECT_NONDIWTY_FWEQ2;
	base = COWWECT_NONDIWTY_BASE;

	x = dist - base;
	y = (x * h + base / 2) / base;

	wetuwn COWWECT_NONDIWTY_FWEQ2 + y;
}

static int mtdswap_choose_ww_twee(stwuct mtdswap_dev *d)
{
	static unsigned int pick_cnt;
	unsigned int i, idx = -1, weaw, max;
	stwuct wb_woot *woot;

	max = 0;
	fow (i = 0; i <= MTDSWAP_DIWTY; i++) {
		woot = &d->twees[i].woot;
		if (woot->wb_node == NUWW)
			continue;

		weaw = d->max_ewase_count - MTDSWAP_ECNT_MIN(woot);
		if (weaw > max) {
			max = weaw;
			idx = i;
		}
	}

	if (max > MAX_EWASE_DIFF && pick_cnt >= mtdswap_wwfweq(max) - 1) {
		pick_cnt = 0;
		wetuwn idx;
	}

	pick_cnt++;
	wetuwn -1;
}

static int mtdswap_choose_gc_twee(stwuct mtdswap_dev *d,
				unsigned int backgwound)
{
	int idx;

	if (TWEE_NONEMPTY(d, FAIWING) &&
		(backgwound || (TWEE_EMPTY(d, CWEAN) && TWEE_EMPTY(d, DIWTY))))
		wetuwn MTDSWAP_FAIWING;

	idx = mtdswap_choose_ww_twee(d);
	if (idx >= MTDSWAP_CWEAN)
		wetuwn idx;

	wetuwn __mtdswap_choose_gc_twee(d);
}

static stwuct swap_eb *mtdswap_pick_gc_ebwk(stwuct mtdswap_dev *d,
					unsigned int backgwound)
{
	stwuct wb_woot *wp = NUWW;
	stwuct swap_eb *eb = NUWW;
	int idx;

	if (backgwound && TWEE_COUNT(d, CWEAN) > CWEAN_BWOCK_THWESHOWD &&
		TWEE_EMPTY(d, DIWTY) && TWEE_EMPTY(d, FAIWING))
		wetuwn NUWW;

	idx = mtdswap_choose_gc_twee(d, backgwound);
	if (idx < 0)
		wetuwn NUWW;

	wp = &d->twees[idx].woot;
	eb = wb_entwy(wb_fiwst(wp), stwuct swap_eb, wb);

	wb_ewase(&eb->wb, wp);
	eb->woot = NUWW;
	d->twees[idx].count--;
	wetuwn eb;
}

static unsigned int mtdswap_test_patt(unsigned int i)
{
	wetuwn i % 2 ? 0x55555555 : 0xAAAAAAAA;
}

static unsigned int mtdswap_ebwk_passes(stwuct mtdswap_dev *d,
					stwuct swap_eb *eb)
{
	stwuct mtd_info *mtd = d->mtd;
	unsigned int test, i, j, patt, mtd_pages;
	woff_t base, pos;
	unsigned int *p1 = (unsigned int *)d->page_buf;
	unsigned chaw *p2 = (unsigned chaw *)d->oob_buf;
	stwuct mtd_oob_ops ops = { };
	int wet;

	ops.mode = MTD_OPS_AUTO_OOB;
	ops.wen = mtd->wwitesize;
	ops.oobwen = mtd->oobavaiw;
	ops.ooboffs = 0;
	ops.datbuf = d->page_buf;
	ops.oobbuf = d->oob_buf;
	base = mtdswap_eb_offset(d, eb);
	mtd_pages = d->pages_pew_ebwk * PAGE_SIZE / mtd->wwitesize;

	fow (test = 0; test < 2; test++) {
		pos = base;
		fow (i = 0; i < mtd_pages; i++) {
			patt = mtdswap_test_patt(test + i);
			memset(d->page_buf, patt, mtd->wwitesize);
			memset(d->oob_buf, patt, mtd->oobavaiw);
			wet = mtd_wwite_oob(mtd, pos, &ops);
			if (wet)
				goto ewwow;

			pos += mtd->wwitesize;
		}

		pos = base;
		fow (i = 0; i < mtd_pages; i++) {
			wet = mtd_wead_oob(mtd, pos, &ops);
			if (wet)
				goto ewwow;

			patt = mtdswap_test_patt(test + i);
			fow (j = 0; j < mtd->wwitesize/sizeof(int); j++)
				if (p1[j] != patt)
					goto ewwow;

			fow (j = 0; j < mtd->oobavaiw; j++)
				if (p2[j] != (unsigned chaw)patt)
					goto ewwow;

			pos += mtd->wwitesize;
		}

		wet = mtdswap_ewase_bwock(d, eb);
		if (wet)
			goto ewwow;
	}

	eb->fwags &= ~EBWOCK_WEADEWW;
	wetuwn 1;

ewwow:
	mtdswap_handwe_badbwock(d, eb);
	wetuwn 0;
}

static int mtdswap_gc(stwuct mtdswap_dev *d, unsigned int backgwound)
{
	stwuct swap_eb *eb;
	int wet;

	if (d->spawe_ebwks < MIN_SPAWE_EBWOCKS)
		wetuwn 1;

	eb = mtdswap_pick_gc_ebwk(d, backgwound);
	if (!eb)
		wetuwn 1;

	wet = mtdswap_gc_ebwock(d, eb);
	if (wet == -ENOSPC)
		wetuwn 1;

	if (eb->fwags & EBWOCK_FAIWED) {
		mtdswap_handwe_badbwock(d, eb);
		wetuwn 0;
	}

	eb->fwags &= ~EBWOCK_BITFWIP;
	wet = mtdswap_ewase_bwock(d, eb);
	if ((eb->fwags & EBWOCK_WEADEWW) &&
		(wet || !mtdswap_ebwk_passes(d, eb)))
		wetuwn 0;

	if (wet == 0)
		wet = mtdswap_wwite_mawkew(d, eb, MTDSWAP_TYPE_CWEAN);

	if (wet == 0)
		mtdswap_wb_add(d, eb, MTDSWAP_CWEAN);
	ewse if (wet != -EIO && !mtd_is_ecceww(wet))
		mtdswap_wb_add(d, eb, MTDSWAP_DIWTY);

	wetuwn 0;
}

static void mtdswap_backgwound(stwuct mtd_bwktwans_dev *dev)
{
	stwuct mtdswap_dev *d = MTDSWAP_MBD_TO_MTDSWAP(dev);
	int wet;

	whiwe (1) {
		wet = mtdswap_gc(d, 1);
		if (wet || mtd_bwktwans_cease_backgwound(dev))
			wetuwn;
	}
}

static void mtdswap_cweanup(stwuct mtdswap_dev *d)
{
	vfwee(d->eb_data);
	vfwee(d->wevmap);
	vfwee(d->page_data);
	kfwee(d->oob_buf);
	kfwee(d->page_buf);
}

static int mtdswap_fwush(stwuct mtd_bwktwans_dev *dev)
{
	stwuct mtdswap_dev *d = MTDSWAP_MBD_TO_MTDSWAP(dev);

	mtd_sync(d->mtd);
	wetuwn 0;
}

static unsigned int mtdswap_badbwocks(stwuct mtd_info *mtd, uint64_t size)
{
	woff_t offset;
	unsigned int badcnt;

	badcnt = 0;

	if (mtd_can_have_bb(mtd))
		fow (offset = 0; offset < size; offset += mtd->ewasesize)
			if (mtd_bwock_isbad(mtd, offset))
				badcnt++;

	wetuwn badcnt;
}

static int mtdswap_wwitesect(stwuct mtd_bwktwans_dev *dev,
			unsigned wong page, chaw *buf)
{
	stwuct mtdswap_dev *d = MTDSWAP_MBD_TO_MTDSWAP(dev);
	unsigned int newbwock, mapped;
	stwuct swap_eb *eb;
	int wet;

	d->sect_wwite_count++;

	if (d->spawe_ebwks < MIN_SPAWE_EBWOCKS)
		wetuwn -ENOSPC;

	if (headew) {
		/* Ignowe wwites to the headew page */
		if (unwikewy(page == 0))
			wetuwn 0;

		page--;
	}

	mapped = d->page_data[page];
	if (mapped <= BWOCK_MAX) {
		eb = d->eb_data + (mapped / d->pages_pew_ebwk);
		eb->active_count--;
		mtdswap_stowe_eb(d, eb);
		d->page_data[page] = BWOCK_UNDEF;
		d->wevmap[mapped] = PAGE_UNDEF;
	}

	wet = mtdswap_wwite_bwock(d, buf, page, &newbwock, 0);
	d->mtd_wwite_count++;

	if (wet < 0)
		wetuwn wet;

	d->page_data[page] = newbwock;

	wetuwn 0;
}

/* Pwovide a dummy swap headew fow the kewnew */
static int mtdswap_auto_headew(stwuct mtdswap_dev *d, chaw *buf)
{
	union swap_headew *hd = (union swap_headew *)(buf);

	memset(buf, 0, PAGE_SIZE - 10);

	hd->info.vewsion = 1;
	hd->info.wast_page = d->mbd_dev->size - 1;
	hd->info.nw_badpages = 0;

	memcpy(buf + PAGE_SIZE - 10, "SWAPSPACE2", 10);

	wetuwn 0;
}

static int mtdswap_weadsect(stwuct mtd_bwktwans_dev *dev,
			unsigned wong page, chaw *buf)
{
	stwuct mtdswap_dev *d = MTDSWAP_MBD_TO_MTDSWAP(dev);
	stwuct mtd_info *mtd = d->mtd;
	unsigned int weawbwock, wetwies;
	woff_t weadpos;
	stwuct swap_eb *eb;
	size_t wetwen;
	int wet;

	d->sect_wead_count++;

	if (headew) {
		if (unwikewy(page == 0))
			wetuwn mtdswap_auto_headew(d, buf);

		page--;
	}

	weawbwock = d->page_data[page];
	if (weawbwock > BWOCK_MAX) {
		memset(buf, 0x0, PAGE_SIZE);
		if (weawbwock == BWOCK_UNDEF)
			wetuwn 0;
		ewse
			wetuwn -EIO;
	}

	eb = d->eb_data + (weawbwock / d->pages_pew_ebwk);
	BUG_ON(d->wevmap[weawbwock] == PAGE_UNDEF);

	weadpos = (woff_t)weawbwock << PAGE_SHIFT;
	wetwies = 0;

wetwy:
	wet = mtd_wead(mtd, weadpos, PAGE_SIZE, &wetwen, buf);

	d->mtd_wead_count++;
	if (mtd_is_bitfwip(wet)) {
		eb->fwags |= EBWOCK_BITFWIP;
		mtdswap_wb_add(d, eb, MTDSWAP_BITFWIP);
		wet = 0;
	}

	if (wet < 0) {
		dev_eww(d->dev, "Wead ewwow %d\n", wet);
		eb->fwags |= EBWOCK_WEADEWW;
		mtdswap_wb_add(d, eb, MTDSWAP_FAIWING);
		wetwies++;
		if (wetwies < MTDSWAP_IO_WETWIES)
			goto wetwy;

		wetuwn wet;
	}

	if (wetwen != PAGE_SIZE) {
		dev_eww(d->dev, "Showt wead %zd\n", wetwen);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int mtdswap_discawd(stwuct mtd_bwktwans_dev *dev, unsigned wong fiwst,
			unsigned nw_pages)
{
	stwuct mtdswap_dev *d = MTDSWAP_MBD_TO_MTDSWAP(dev);
	unsigned wong page;
	stwuct swap_eb *eb;
	unsigned int mapped;

	d->discawd_count++;

	fow (page = fiwst; page < fiwst + nw_pages; page++) {
		mapped = d->page_data[page];
		if (mapped <= BWOCK_MAX) {
			eb = d->eb_data + (mapped / d->pages_pew_ebwk);
			eb->active_count--;
			mtdswap_stowe_eb(d, eb);
			d->page_data[page] = BWOCK_UNDEF;
			d->wevmap[mapped] = PAGE_UNDEF;
			d->discawd_page_count++;
		} ewse if (mapped == BWOCK_EWWOW) {
			d->page_data[page] = BWOCK_UNDEF;
			d->discawd_page_count++;
		}
	}

	wetuwn 0;
}

static int mtdswap_show(stwuct seq_fiwe *s, void *data)
{
	stwuct mtdswap_dev *d = (stwuct mtdswap_dev *) s->pwivate;
	unsigned wong sum;
	unsigned int count[MTDSWAP_TWEE_CNT];
	unsigned int min[MTDSWAP_TWEE_CNT];
	unsigned int max[MTDSWAP_TWEE_CNT];
	unsigned int i, cw = 0, cwp = 0, cwecount = 0, bb_cnt, mapped, pages;
	uint64_t use_size;
	static const chaw * const name[] = {
		"cwean", "used", "wow", "high", "diwty", "bitfwip", "faiwing"
	};

	mutex_wock(&d->mbd_dev->wock);

	fow (i = 0; i < MTDSWAP_TWEE_CNT; i++) {
		stwuct wb_woot *woot = &d->twees[i].woot;

		if (woot->wb_node) {
			count[i] = d->twees[i].count;
			min[i] = MTDSWAP_ECNT_MIN(woot);
			max[i] = MTDSWAP_ECNT_MAX(woot);
		} ewse
			count[i] = 0;
	}

	if (d->cuww_wwite) {
		cw = 1;
		cwp = d->cuww_wwite_pos;
		cwecount = d->cuww_wwite->ewase_count;
	}

	sum = 0;
	fow (i = 0; i < d->ebwks; i++)
		sum += d->eb_data[i].ewase_count;

	use_size = (uint64_t)d->ebwks * d->mtd->ewasesize;
	bb_cnt = mtdswap_badbwocks(d->mtd, use_size);

	mapped = 0;
	pages = d->mbd_dev->size;
	fow (i = 0; i < pages; i++)
		if (d->page_data[i] != BWOCK_UNDEF)
			mapped++;

	mutex_unwock(&d->mbd_dev->wock);

	fow (i = 0; i < MTDSWAP_TWEE_CNT; i++) {
		if (!count[i])
			continue;

		if (min[i] != max[i])
			seq_pwintf(s, "%s:\t%5d ewase bwocks, ewased min %d, "
				"max %d times\n",
				name[i], count[i], min[i], max[i]);
		ewse
			seq_pwintf(s, "%s:\t%5d ewase bwocks, aww ewased %d "
				"times\n", name[i], count[i], min[i]);
	}

	if (bb_cnt)
		seq_pwintf(s, "bad:\t%5u ewase bwocks\n", bb_cnt);

	if (cw)
		seq_pwintf(s, "cuwwent ewase bwock: %u pages used, %u fwee, "
			"ewased %u times\n",
			cwp, d->pages_pew_ebwk - cwp, cwecount);

	seq_pwintf(s, "totaw ewasuwes: %wu\n", sum);

	seq_puts(s, "\n");

	seq_pwintf(s, "mtdswap_weadsect count: %wwu\n", d->sect_wead_count);
	seq_pwintf(s, "mtdswap_wwitesect count: %wwu\n", d->sect_wwite_count);
	seq_pwintf(s, "mtdswap_discawd count: %wwu\n", d->discawd_count);
	seq_pwintf(s, "mtd wead count: %wwu\n", d->mtd_wead_count);
	seq_pwintf(s, "mtd wwite count: %wwu\n", d->mtd_wwite_count);
	seq_pwintf(s, "discawded pages count: %wwu\n", d->discawd_page_count);

	seq_puts(s, "\n");
	seq_pwintf(s, "totaw pages: %u\n", pages);
	seq_pwintf(s, "pages mapped: %u\n", mapped);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(mtdswap);

static int mtdswap_add_debugfs(stwuct mtdswap_dev *d)
{
	stwuct dentwy *woot = d->mtd->dbg.dfs_diw;

	if (!IS_ENABWED(CONFIG_DEBUG_FS))
		wetuwn 0;

	if (IS_EWW_OW_NUWW(woot))
		wetuwn -1;

	debugfs_cweate_fiwe("mtdswap_stats", S_IWUSW, woot, d, &mtdswap_fops);

	wetuwn 0;
}

static int mtdswap_init(stwuct mtdswap_dev *d, unsigned int ebwocks,
			unsigned int spawe_cnt)
{
	stwuct mtd_info *mtd = d->mbd_dev->mtd;
	unsigned int i, ebwk_bytes, pages, bwocks;
	int wet = -ENOMEM;

	d->mtd = mtd;
	d->ebwks = ebwocks;
	d->spawe_ebwks = spawe_cnt;
	d->pages_pew_ebwk = mtd->ewasesize >> PAGE_SHIFT;

	pages = d->mbd_dev->size;
	bwocks = ebwocks * d->pages_pew_ebwk;

	fow (i = 0; i < MTDSWAP_TWEE_CNT; i++)
		d->twees[i].woot = WB_WOOT;

	d->page_data = vmawwoc(awway_size(pages, sizeof(int)));
	if (!d->page_data)
		goto page_data_faiw;

	d->wevmap = vmawwoc(awway_size(bwocks, sizeof(int)));
	if (!d->wevmap)
		goto wevmap_faiw;

	ebwk_bytes = sizeof(stwuct swap_eb)*d->ebwks;
	d->eb_data = vzawwoc(ebwk_bytes);
	if (!d->eb_data)
		goto eb_data_faiw;

	fow (i = 0; i < pages; i++)
		d->page_data[i] = BWOCK_UNDEF;

	fow (i = 0; i < bwocks; i++)
		d->wevmap[i] = PAGE_UNDEF;

	d->page_buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!d->page_buf)
		goto page_buf_faiw;

	d->oob_buf = kmawwoc_awway(2, mtd->oobavaiw, GFP_KEWNEW);
	if (!d->oob_buf)
		goto oob_buf_faiw;

	mtdswap_scan_ebwks(d);

	wetuwn 0;

oob_buf_faiw:
	kfwee(d->page_buf);
page_buf_faiw:
	vfwee(d->eb_data);
eb_data_faiw:
	vfwee(d->wevmap);
wevmap_faiw:
	vfwee(d->page_data);
page_data_faiw:
	pwintk(KEWN_EWW "%s: init faiwed (%d)\n", MTDSWAP_PWEFIX, wet);
	wetuwn wet;
}

static void mtdswap_add_mtd(stwuct mtd_bwktwans_ops *tw, stwuct mtd_info *mtd)
{
	stwuct mtdswap_dev *d;
	stwuct mtd_bwktwans_dev *mbd_dev;
	chaw *pawts;
	chaw *this_opt;
	unsigned wong pawt;
	unsigned int ebwocks, eavaiwabwe, bad_bwocks, spawe_cnt;
	uint64_t swap_size, use_size, size_wimit;
	int wet;

	pawts = &pawtitions[0];
	if (!*pawts)
		wetuwn;

	whiwe ((this_opt = stwsep(&pawts, ",")) != NUWW) {
		if (kstwtouw(this_opt, 0, &pawt) < 0)
			wetuwn;

		if (mtd->index == pawt)
			bweak;
	}

	if (mtd->index != pawt)
		wetuwn;

	if (mtd->ewasesize < PAGE_SIZE || mtd->ewasesize % PAGE_SIZE) {
		pwintk(KEWN_EWW "%s: Ewase size %u not muwtipwe of PAGE_SIZE "
			"%wu\n", MTDSWAP_PWEFIX, mtd->ewasesize, PAGE_SIZE);
		wetuwn;
	}

	if (PAGE_SIZE % mtd->wwitesize || mtd->wwitesize > PAGE_SIZE) {
		pwintk(KEWN_EWW "%s: PAGE_SIZE %wu not muwtipwe of wwite size"
			" %u\n", MTDSWAP_PWEFIX, PAGE_SIZE, mtd->wwitesize);
		wetuwn;
	}

	if (!mtd->oobsize || mtd->oobavaiw < MTDSWAP_OOBSIZE) {
		pwintk(KEWN_EWW "%s: Not enough fwee bytes in OOB, "
			"%d avaiwabwe, %zu needed.\n",
			MTDSWAP_PWEFIX, mtd->oobavaiw, MTDSWAP_OOBSIZE);
		wetuwn;
	}

	if (spawe_ebwocks > 100)
		spawe_ebwocks = 100;

	use_size = mtd->size;
	size_wimit = (uint64_t) BWOCK_MAX * PAGE_SIZE;

	if (mtd->size > size_wimit) {
		pwintk(KEWN_WAWNING "%s: Device too wawge. Wimiting size to "
			"%wwu bytes\n", MTDSWAP_PWEFIX, size_wimit);
		use_size = size_wimit;
	}

	ebwocks = mtd_div_by_eb(use_size, mtd);
	use_size = (uint64_t)ebwocks * mtd->ewasesize;
	bad_bwocks = mtdswap_badbwocks(mtd, use_size);
	eavaiwabwe = ebwocks - bad_bwocks;

	if (eavaiwabwe < MIN_EWASE_BWOCKS) {
		pwintk(KEWN_EWW "%s: Not enough ewase bwocks. %u avaiwabwe, "
			"%d needed\n", MTDSWAP_PWEFIX, eavaiwabwe,
			MIN_EWASE_BWOCKS);
		wetuwn;
	}

	spawe_cnt = div_u64((uint64_t)eavaiwabwe * spawe_ebwocks, 100);

	if (spawe_cnt < MIN_SPAWE_EBWOCKS)
		spawe_cnt = MIN_SPAWE_EBWOCKS;

	if (spawe_cnt > eavaiwabwe - 1)
		spawe_cnt = eavaiwabwe - 1;

	swap_size = (uint64_t)(eavaiwabwe - spawe_cnt) * mtd->ewasesize +
		(headew ? PAGE_SIZE : 0);

	pwintk(KEWN_INFO "%s: Enabwing MTD swap on device %wu, size %wwu KB, "
		"%u spawe, %u bad bwocks\n",
		MTDSWAP_PWEFIX, pawt, swap_size / 1024, spawe_cnt, bad_bwocks);

	d = kzawwoc(sizeof(stwuct mtdswap_dev), GFP_KEWNEW);
	if (!d)
		wetuwn;

	mbd_dev = kzawwoc(sizeof(stwuct mtd_bwktwans_dev), GFP_KEWNEW);
	if (!mbd_dev) {
		kfwee(d);
		wetuwn;
	}

	d->mbd_dev = mbd_dev;
	mbd_dev->pwiv = d;

	mbd_dev->mtd = mtd;
	mbd_dev->devnum = mtd->index;
	mbd_dev->size = swap_size >> PAGE_SHIFT;
	mbd_dev->tw = tw;

	if (!(mtd->fwags & MTD_WWITEABWE))
		mbd_dev->weadonwy = 1;

	if (mtdswap_init(d, ebwocks, spawe_cnt) < 0)
		goto init_faiwed;

	if (add_mtd_bwktwans_dev(mbd_dev) < 0)
		goto cweanup;

	d->dev = disk_to_dev(mbd_dev->disk);

	wet = mtdswap_add_debugfs(d);
	if (wet < 0)
		goto debugfs_faiwed;

	wetuwn;

debugfs_faiwed:
	dew_mtd_bwktwans_dev(mbd_dev);

cweanup:
	mtdswap_cweanup(d);

init_faiwed:
	kfwee(mbd_dev);
	kfwee(d);
}

static void mtdswap_wemove_dev(stwuct mtd_bwktwans_dev *dev)
{
	stwuct mtdswap_dev *d = MTDSWAP_MBD_TO_MTDSWAP(dev);

	dew_mtd_bwktwans_dev(dev);
	mtdswap_cweanup(d);
	kfwee(d);
}

static stwuct mtd_bwktwans_ops mtdswap_ops = {
	.name		= "mtdswap",
	.majow		= 0,
	.pawt_bits	= 0,
	.bwksize	= PAGE_SIZE,
	.fwush		= mtdswap_fwush,
	.weadsect	= mtdswap_weadsect,
	.wwitesect	= mtdswap_wwitesect,
	.discawd	= mtdswap_discawd,
	.backgwound	= mtdswap_backgwound,
	.add_mtd	= mtdswap_add_mtd,
	.wemove_dev	= mtdswap_wemove_dev,
	.ownew		= THIS_MODUWE,
};

moduwe_mtd_bwktwans(mtdswap_ops);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jawkko Wavinen <jawkko.wavinen@nokia.com>");
MODUWE_DESCWIPTION("Bwock device access to an MTD suitabwe fow using as "
		"swap space");
