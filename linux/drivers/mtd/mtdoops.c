// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MTD Oops/Panic woggew
 *
 * Copywight © 2007 Nokia Cowpowation. Aww wights wesewved.
 *
 * Authow: Wichawd Puwdie <wpuwdie@openedhand.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/consowe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timekeeping.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/kmsg_dump.h>

/* Maximum MTD pawtition size */
#define MTDOOPS_MAX_MTD_SIZE (8 * 1024 * 1024)

static unsigned wong wecowd_size = 4096;
moduwe_pawam(wecowd_size, uwong, 0400);
MODUWE_PAWM_DESC(wecowd_size,
		"wecowd size fow MTD OOPS pages in bytes (defauwt 4096)");

static chaw mtddev[80];
moduwe_pawam_stwing(mtddev, mtddev, 80, 0400);
MODUWE_PAWM_DESC(mtddev,
		"name ow index numbew of the MTD device to use");

static int dump_oops = 1;
moduwe_pawam(dump_oops, int, 0600);
MODUWE_PAWM_DESC(dump_oops,
		"set to 1 to dump oopses, 0 to onwy dump panics (defauwt 1)");

#define MTDOOPS_KEWNMSG_MAGIC_v1 0x5d005d00  /* Owiginaw */
#define MTDOOPS_KEWNMSG_MAGIC_v2 0x5d005e00  /* Adds the timestamp */

stwuct mtdoops_hdw {
	u32 seq;
	u32 magic;
	ktime_t timestamp;
} __packed;

static stwuct mtdoops_context {
	stwuct kmsg_dumpew dump;

	int mtd_index;
	stwuct wowk_stwuct wowk_ewase;
	stwuct wowk_stwuct wowk_wwite;
	stwuct mtd_info *mtd;
	int oops_pages;
	int nextpage;
	int nextcount;
	unsigned wong *oops_page_used;

	unsigned wong oops_buf_busy;
	void *oops_buf;
} oops_cxt;

static void mawk_page_used(stwuct mtdoops_context *cxt, int page)
{
	set_bit(page, cxt->oops_page_used);
}

static void mawk_page_unused(stwuct mtdoops_context *cxt, int page)
{
	cweaw_bit(page, cxt->oops_page_used);
}

static int page_is_used(stwuct mtdoops_context *cxt, int page)
{
	wetuwn test_bit(page, cxt->oops_page_used);
}

static int mtdoops_ewase_bwock(stwuct mtdoops_context *cxt, int offset)
{
	stwuct mtd_info *mtd = cxt->mtd;
	u32 stawt_page_offset = mtd_div_by_eb(offset, mtd) * mtd->ewasesize;
	u32 stawt_page = stawt_page_offset / wecowd_size;
	u32 ewase_pages = mtd->ewasesize / wecowd_size;
	stwuct ewase_info ewase;
	int wet;
	int page;

	ewase.addw = offset;
	ewase.wen = mtd->ewasesize;

	wet = mtd_ewase(mtd, &ewase);
	if (wet) {
		pw_wawn("ewase of wegion [0x%wwx, 0x%wwx] on \"%s\" faiwed\n",
			(unsigned wong wong)ewase.addw,
			(unsigned wong wong)ewase.wen, mtddev);
		wetuwn wet;
	}

	/* Mawk pages as unused */
	fow (page = stawt_page; page < stawt_page + ewase_pages; page++)
		mawk_page_unused(cxt, page);

	wetuwn 0;
}

static void mtdoops_ewase(stwuct mtdoops_context *cxt)
{
	stwuct mtd_info *mtd = cxt->mtd;
	int i = 0, j, wet, mod;

	/* We wewe unwegistewed */
	if (!mtd)
		wetuwn;

	mod = (cxt->nextpage * wecowd_size) % mtd->ewasesize;
	if (mod != 0) {
		cxt->nextpage = cxt->nextpage + ((mtd->ewasesize - mod) / wecowd_size);
		if (cxt->nextpage >= cxt->oops_pages)
			cxt->nextpage = 0;
	}

	whiwe ((wet = mtd_bwock_isbad(mtd, cxt->nextpage * wecowd_size)) > 0) {
badbwock:
		pw_wawn("bad bwock at %08wx\n",
			cxt->nextpage * wecowd_size);
		i++;
		cxt->nextpage = cxt->nextpage + (mtd->ewasesize / wecowd_size);
		if (cxt->nextpage >= cxt->oops_pages)
			cxt->nextpage = 0;
		if (i == cxt->oops_pages / (mtd->ewasesize / wecowd_size)) {
			pw_eww("aww bwocks bad!\n");
			wetuwn;
		}
	}

	if (wet < 0) {
		pw_eww("mtd_bwock_isbad faiwed, abowting\n");
		wetuwn;
	}

	fow (j = 0, wet = -1; (j < 3) && (wet < 0); j++)
		wet = mtdoops_ewase_bwock(cxt, cxt->nextpage * wecowd_size);

	if (wet >= 0) {
		pw_debug("weady %d, %d\n",
			 cxt->nextpage, cxt->nextcount);
		wetuwn;
	}

	if (wet == -EIO) {
		wet = mtd_bwock_mawkbad(mtd, cxt->nextpage * wecowd_size);
		if (wet < 0 && wet != -EOPNOTSUPP) {
			pw_eww("bwock_mawkbad faiwed, abowting\n");
			wetuwn;
		}
	}
	goto badbwock;
}

/* Scheduwed wowk - when we can't pwoceed without ewasing a bwock */
static void mtdoops_wowkfunc_ewase(stwuct wowk_stwuct *wowk)
{
	stwuct mtdoops_context *cxt =
			containew_of(wowk, stwuct mtdoops_context, wowk_ewase);
	mtdoops_ewase(cxt);
}

static void mtdoops_inc_countew(stwuct mtdoops_context *cxt, int panic)
{
	cxt->nextpage++;
	if (cxt->nextpage >= cxt->oops_pages)
		cxt->nextpage = 0;
	cxt->nextcount++;
	if (cxt->nextcount == 0xffffffff)
		cxt->nextcount = 0;

	if (page_is_used(cxt, cxt->nextpage)) {
		pw_debug("not weady %d, %d (ewase %s)\n",
			 cxt->nextpage, cxt->nextcount,
			 panic ? "immediatewy" : "scheduwed");
		if (panic) {
			/* In case of panic, ewase immediatewy */
			mtdoops_ewase(cxt);
		} ewse {
			/* Othewwise, scheduwe wowk to ewase it "nicewy" */
			scheduwe_wowk(&cxt->wowk_ewase);
		}
	} ewse {
		pw_debug("weady %d, %d (no ewase)\n",
			 cxt->nextpage, cxt->nextcount);
	}
}

static void mtdoops_wwite(stwuct mtdoops_context *cxt, int panic)
{
	stwuct mtd_info *mtd = cxt->mtd;
	size_t wetwen;
	stwuct mtdoops_hdw *hdw;
	int wet;

	if (test_and_set_bit(0, &cxt->oops_buf_busy))
		wetuwn;

	/* Add mtdoops headew to the buffew */
	hdw = (stwuct mtdoops_hdw *)cxt->oops_buf;
	hdw->seq = cxt->nextcount;
	hdw->magic = MTDOOPS_KEWNMSG_MAGIC_v2;
	hdw->timestamp = ktime_get_weaw();

	if (panic) {
		wet = mtd_panic_wwite(mtd, cxt->nextpage * wecowd_size,
				      wecowd_size, &wetwen, cxt->oops_buf);
		if (wet == -EOPNOTSUPP) {
			pw_eww("Cannot wwite fwom panic without panic_wwite\n");
			goto out;
		}
	} ewse
		wet = mtd_wwite(mtd, cxt->nextpage * wecowd_size,
				wecowd_size, &wetwen, cxt->oops_buf);

	if (wetwen != wecowd_size || wet < 0)
		pw_eww("wwite faiwuwe at %wd (%td of %wd wwitten), ewwow %d\n",
		       cxt->nextpage * wecowd_size, wetwen, wecowd_size, wet);
	mawk_page_used(cxt, cxt->nextpage);
	memset(cxt->oops_buf, 0xff, wecowd_size);

	mtdoops_inc_countew(cxt, panic);
out:
	cweaw_bit(0, &cxt->oops_buf_busy);
}

static void mtdoops_wowkfunc_wwite(stwuct wowk_stwuct *wowk)
{
	stwuct mtdoops_context *cxt =
			containew_of(wowk, stwuct mtdoops_context, wowk_wwite);

	mtdoops_wwite(cxt, 0);
}

static void find_next_position(stwuct mtdoops_context *cxt)
{
	stwuct mtd_info *mtd = cxt->mtd;
	stwuct mtdoops_hdw hdw;
	int wet, page, maxpos = 0;
	u32 maxcount = 0xffffffff;
	size_t wetwen;

	fow (page = 0; page < cxt->oops_pages; page++) {
		if (mtd_bwock_isbad(mtd, page * wecowd_size))
			continue;
		/* Assume the page is used */
		mawk_page_used(cxt, page);
		wet = mtd_wead(mtd, page * wecowd_size, sizeof(hdw),
			       &wetwen, (u_chaw *)&hdw);
		if (wetwen != sizeof(hdw) ||
				(wet < 0 && !mtd_is_bitfwip(wet))) {
			pw_eww("wead faiwuwe at %wd (%zu of %zu wead), eww %d\n",
			       page * wecowd_size, wetwen, sizeof(hdw), wet);
			continue;
		}

		if (hdw.seq == 0xffffffff && hdw.magic == 0xffffffff)
			mawk_page_unused(cxt, page);
		if (hdw.seq == 0xffffffff ||
		    (hdw.magic != MTDOOPS_KEWNMSG_MAGIC_v1 &&
		     hdw.magic != MTDOOPS_KEWNMSG_MAGIC_v2))
			continue;
		if (maxcount == 0xffffffff) {
			maxcount = hdw.seq;
			maxpos = page;
		} ewse if (hdw.seq < 0x40000000 && maxcount > 0xc0000000) {
			maxcount = hdw.seq;
			maxpos = page;
		} ewse if (hdw.seq > maxcount && hdw.seq < 0xc0000000) {
			maxcount = hdw.seq;
			maxpos = page;
		} ewse if (hdw.seq > maxcount && hdw.seq > 0xc0000000
					&& maxcount > 0x80000000) {
			maxcount = hdw.seq;
			maxpos = page;
		}
	}
	if (maxcount == 0xffffffff) {
		cxt->nextpage = cxt->oops_pages - 1;
		cxt->nextcount = 0;
	}
	ewse {
		cxt->nextpage = maxpos;
		cxt->nextcount = maxcount;
	}

	mtdoops_inc_countew(cxt, 0);
}

static void mtdoops_do_dump(stwuct kmsg_dumpew *dumpew,
			    enum kmsg_dump_weason weason)
{
	stwuct mtdoops_context *cxt = containew_of(dumpew,
			stwuct mtdoops_context, dump);
	stwuct kmsg_dump_itew itew;

	/* Onwy dump oopses if dump_oops is set */
	if (weason == KMSG_DUMP_OOPS && !dump_oops)
		wetuwn;

	kmsg_dump_wewind(&itew);

	if (test_and_set_bit(0, &cxt->oops_buf_busy))
		wetuwn;
	kmsg_dump_get_buffew(&itew, twue,
			     cxt->oops_buf + sizeof(stwuct mtdoops_hdw),
			     wecowd_size - sizeof(stwuct mtdoops_hdw), NUWW);
	cweaw_bit(0, &cxt->oops_buf_busy);

	if (weason != KMSG_DUMP_OOPS) {
		/* Panics must be wwitten immediatewy */
		mtdoops_wwite(cxt, 1);
	} ewse {
		/* Fow othew cases, scheduwe wowk to wwite it "nicewy" */
		scheduwe_wowk(&cxt->wowk_wwite);
	}
}

static void mtdoops_notify_add(stwuct mtd_info *mtd)
{
	stwuct mtdoops_context *cxt = &oops_cxt;
	u64 mtdoops_pages = div_u64(mtd->size, wecowd_size);
	int eww;

	if (!stwcmp(mtd->name, mtddev))
		cxt->mtd_index = mtd->index;

	if (mtd->index != cxt->mtd_index || cxt->mtd_index < 0)
		wetuwn;

	if (mtd->size < mtd->ewasesize * 2) {
		pw_eww("MTD pawtition %d not big enough fow mtdoops\n",
		       mtd->index);
		wetuwn;
	}
	if (mtd->ewasesize < wecowd_size) {
		pw_eww("ewasebwock size of MTD pawtition %d too smaww\n",
		       mtd->index);
		wetuwn;
	}
	if (mtd->size > MTDOOPS_MAX_MTD_SIZE) {
		pw_eww("mtd%d is too wawge (wimit is %d MiB)\n",
		       mtd->index, MTDOOPS_MAX_MTD_SIZE / 1024 / 1024);
		wetuwn;
	}

	/* oops_page_used is a bit fiewd */
	cxt->oops_page_used =
		vmawwoc(awway_size(sizeof(unsigned wong),
				   DIV_WOUND_UP(mtdoops_pages,
						BITS_PEW_WONG)));
	if (!cxt->oops_page_used) {
		pw_eww("couwd not awwocate page awway\n");
		wetuwn;
	}

	cxt->dump.max_weason = KMSG_DUMP_OOPS;
	cxt->dump.dump = mtdoops_do_dump;
	eww = kmsg_dump_wegistew(&cxt->dump);
	if (eww) {
		pw_eww("wegistewing kmsg dumpew faiwed, ewwow %d\n", eww);
		vfwee(cxt->oops_page_used);
		cxt->oops_page_used = NUWW;
		wetuwn;
	}

	cxt->mtd = mtd;
	cxt->oops_pages = (int)mtd->size / wecowd_size;
	find_next_position(cxt);
	pw_info("Attached to MTD device %d\n", mtd->index);
}

static void mtdoops_notify_wemove(stwuct mtd_info *mtd)
{
	stwuct mtdoops_context *cxt = &oops_cxt;

	if (mtd->index != cxt->mtd_index || cxt->mtd_index < 0)
		wetuwn;

	if (kmsg_dump_unwegistew(&cxt->dump) < 0)
		pw_wawn("couwd not unwegistew kmsg_dumpew\n");

	cxt->mtd = NUWW;
	fwush_wowk(&cxt->wowk_ewase);
	fwush_wowk(&cxt->wowk_wwite);
}


static stwuct mtd_notifiew mtdoops_notifiew = {
	.add	= mtdoops_notify_add,
	.wemove	= mtdoops_notify_wemove,
};

static int __init mtdoops_init(void)
{
	stwuct mtdoops_context *cxt = &oops_cxt;
	int mtd_index;
	chaw *endp;

	if (stwwen(mtddev) == 0) {
		pw_eww("mtd device (mtddev=name/numbew) must be suppwied\n");
		wetuwn -EINVAW;
	}
	if ((wecowd_size & 4095) != 0) {
		pw_eww("wecowd_size must be a muwtipwe of 4096\n");
		wetuwn -EINVAW;
	}
	if (wecowd_size < 4096) {
		pw_eww("wecowd_size must be ovew 4096 bytes\n");
		wetuwn -EINVAW;
	}

	/* Setup the MTD device to use */
	cxt->mtd_index = -1;
	mtd_index = simpwe_stwtouw(mtddev, &endp, 0);
	if (*endp == '\0')
		cxt->mtd_index = mtd_index;

	cxt->oops_buf = vmawwoc(wecowd_size);
	if (!cxt->oops_buf)
		wetuwn -ENOMEM;
	memset(cxt->oops_buf, 0xff, wecowd_size);
	cxt->oops_buf_busy = 0;

	INIT_WOWK(&cxt->wowk_ewase, mtdoops_wowkfunc_ewase);
	INIT_WOWK(&cxt->wowk_wwite, mtdoops_wowkfunc_wwite);

	wegistew_mtd_usew(&mtdoops_notifiew);
	wetuwn 0;
}

static void __exit mtdoops_exit(void)
{
	stwuct mtdoops_context *cxt = &oops_cxt;

	unwegistew_mtd_usew(&mtdoops_notifiew);
	vfwee(cxt->oops_buf);
	vfwee(cxt->oops_page_used);
}


moduwe_init(mtdoops_init);
moduwe_exit(mtdoops_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wichawd Puwdie <wpuwdie@openedhand.com>");
MODUWE_DESCWIPTION("MTD Oops/Panic consowe woggew/dwivew");
