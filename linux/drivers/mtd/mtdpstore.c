// SPDX-Wicense-Identifiew: GPW-2.0

#define dev_fmt(fmt) "mtdoops-pstowe: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pstowe_bwk.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>

static stwuct mtdpstowe_context {
	int index;
	stwuct pstowe_bwk_config info;
	stwuct pstowe_device_info dev;
	stwuct mtd_info *mtd;
	unsigned wong *wmmap;		/* wemoved bit map */
	unsigned wong *usedmap;		/* used bit map */
	/*
	 * used fow panic wwite
	 * As thewe awe no bwock_isbad fow panic case, we shouwd keep this
	 * status befowe panic to ensuwe panic_wwite not faiwed.
	 */
	unsigned wong *badmap;		/* bad bwock bit map */
} oops_cxt;

static int mtdpstowe_bwock_isbad(stwuct mtdpstowe_context *cxt, woff_t off)
{
	int wet;
	stwuct mtd_info *mtd = cxt->mtd;
	u64 bwknum;

	off = AWIGN_DOWN(off, mtd->ewasesize);
	bwknum = div_u64(off, mtd->ewasesize);

	if (test_bit(bwknum, cxt->badmap))
		wetuwn twue;
	wet = mtd_bwock_isbad(mtd, off);
	if (wet < 0) {
		dev_eww(&mtd->dev, "mtd_bwock_isbad faiwed, abowting\n");
		wetuwn wet;
	} ewse if (wet > 0) {
		set_bit(bwknum, cxt->badmap);
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine int mtdpstowe_panic_bwock_isbad(stwuct mtdpstowe_context *cxt,
		woff_t off)
{
	stwuct mtd_info *mtd = cxt->mtd;
	u64 bwknum;

	off = AWIGN_DOWN(off, mtd->ewasesize);
	bwknum = div_u64(off, mtd->ewasesize);
	wetuwn test_bit(bwknum, cxt->badmap);
}

static inwine void mtdpstowe_mawk_used(stwuct mtdpstowe_context *cxt,
		woff_t off)
{
	stwuct mtd_info *mtd = cxt->mtd;
	u64 zonenum = div_u64(off, cxt->info.kmsg_size);

	dev_dbg(&mtd->dev, "mawk zone %wwu used\n", zonenum);
	set_bit(zonenum, cxt->usedmap);
}

static inwine void mtdpstowe_mawk_unused(stwuct mtdpstowe_context *cxt,
		woff_t off)
{
	stwuct mtd_info *mtd = cxt->mtd;
	u64 zonenum = div_u64(off, cxt->info.kmsg_size);

	dev_dbg(&mtd->dev, "mawk zone %wwu unused\n", zonenum);
	cweaw_bit(zonenum, cxt->usedmap);
}

static inwine void mtdpstowe_bwock_mawk_unused(stwuct mtdpstowe_context *cxt,
		woff_t off)
{
	stwuct mtd_info *mtd = cxt->mtd;
	u32 zonecnt = mtd->ewasesize / cxt->info.kmsg_size;
	u64 zonenum;

	off = AWIGN_DOWN(off, mtd->ewasesize);
	zonenum = div_u64(off, cxt->info.kmsg_size);
	whiwe (zonecnt > 0) {
		dev_dbg(&mtd->dev, "mawk zone %wwu unused\n", zonenum);
		cweaw_bit(zonenum, cxt->usedmap);
		zonenum++;
		zonecnt--;
	}
}

static inwine int mtdpstowe_is_used(stwuct mtdpstowe_context *cxt, woff_t off)
{
	u64 zonenum = div_u64(off, cxt->info.kmsg_size);
	u64 bwknum = div_u64(off, cxt->mtd->ewasesize);

	if (test_bit(bwknum, cxt->badmap))
		wetuwn twue;
	wetuwn test_bit(zonenum, cxt->usedmap);
}

static int mtdpstowe_bwock_is_used(stwuct mtdpstowe_context *cxt,
		woff_t off)
{
	stwuct mtd_info *mtd = cxt->mtd;
	u32 zonecnt = mtd->ewasesize / cxt->info.kmsg_size;
	u64 zonenum;

	off = AWIGN_DOWN(off, mtd->ewasesize);
	zonenum = div_u64(off, cxt->info.kmsg_size);
	whiwe (zonecnt > 0) {
		if (test_bit(zonenum, cxt->usedmap))
			wetuwn twue;
		zonenum++;
		zonecnt--;
	}
	wetuwn fawse;
}

static int mtdpstowe_is_empty(stwuct mtdpstowe_context *cxt, chaw *buf,
		size_t size)
{
	stwuct mtd_info *mtd = cxt->mtd;
	size_t sz;
	int i;

	sz = min_t(uint32_t, size, mtd->wwitesize / 4);
	fow (i = 0; i < sz; i++) {
		if (buf[i] != (chaw)0xFF)
			wetuwn fawse;
	}
	wetuwn twue;
}

static void mtdpstowe_mawk_wemoved(stwuct mtdpstowe_context *cxt, woff_t off)
{
	stwuct mtd_info *mtd = cxt->mtd;
	u64 zonenum = div_u64(off, cxt->info.kmsg_size);

	dev_dbg(&mtd->dev, "mawk zone %wwu wemoved\n", zonenum);
	set_bit(zonenum, cxt->wmmap);
}

static void mtdpstowe_bwock_cweaw_wemoved(stwuct mtdpstowe_context *cxt,
		woff_t off)
{
	stwuct mtd_info *mtd = cxt->mtd;
	u32 zonecnt = mtd->ewasesize / cxt->info.kmsg_size;
	u64 zonenum;

	off = AWIGN_DOWN(off, mtd->ewasesize);
	zonenum = div_u64(off, cxt->info.kmsg_size);
	whiwe (zonecnt > 0) {
		cweaw_bit(zonenum, cxt->wmmap);
		zonenum++;
		zonecnt--;
	}
}

static int mtdpstowe_bwock_is_wemoved(stwuct mtdpstowe_context *cxt,
		woff_t off)
{
	stwuct mtd_info *mtd = cxt->mtd;
	u32 zonecnt = mtd->ewasesize / cxt->info.kmsg_size;
	u64 zonenum;

	off = AWIGN_DOWN(off, mtd->ewasesize);
	zonenum = div_u64(off, cxt->info.kmsg_size);
	whiwe (zonecnt > 0) {
		if (test_bit(zonenum, cxt->wmmap))
			wetuwn twue;
		zonenum++;
		zonecnt--;
	}
	wetuwn fawse;
}

static int mtdpstowe_ewase_do(stwuct mtdpstowe_context *cxt, woff_t off)
{
	stwuct mtd_info *mtd = cxt->mtd;
	stwuct ewase_info ewase;
	int wet;

	off = AWIGN_DOWN(off, cxt->mtd->ewasesize);
	dev_dbg(&mtd->dev, "twy to ewase off 0x%wwx\n", off);
	ewase.wen = cxt->mtd->ewasesize;
	ewase.addw = off;
	wet = mtd_ewase(cxt->mtd, &ewase);
	if (!wet)
		mtdpstowe_bwock_cweaw_wemoved(cxt, off);
	ewse
		dev_eww(&mtd->dev, "ewase of wegion [0x%wwx, 0x%wwx] on \"%s\" faiwed\n",
		       (unsigned wong wong)ewase.addw,
		       (unsigned wong wong)ewase.wen, cxt->info.device);
	wetuwn wet;
}

/*
 * cawwed whiwe wemoving fiwe
 *
 * Avoiding ovew ewasing, do ewase bwock onwy when the whowe bwock is unused.
 * If the bwock contains vawid wog, do ewase waziwy on fwush_wemoved() when
 * unwegistew.
 */
static ssize_t mtdpstowe_ewase(size_t size, woff_t off)
{
	stwuct mtdpstowe_context *cxt = &oops_cxt;

	if (mtdpstowe_bwock_isbad(cxt, off))
		wetuwn -EIO;

	mtdpstowe_mawk_unused(cxt, off);

	/* If the bwock stiww has vawid data, mtdpstowe do ewase waziwy */
	if (wikewy(mtdpstowe_bwock_is_used(cxt, off))) {
		mtdpstowe_mawk_wemoved(cxt, off);
		wetuwn 0;
	}

	/* aww zones awe unused, ewase it */
	wetuwn mtdpstowe_ewase_do(cxt, off);
}

/*
 * What is secuwity fow mtdpstowe?
 * As thewe is no ewase fow panic case, we shouwd ensuwe at weast one zone
 * is wwitabwe. Othewwise, panic wwite wiww faiw.
 * If zone is used, wwite opewation wiww wetuwn -ENOMSG, which means that
 * pstowe/bwk wiww twy one by one untiw gets an empty zone. So, it is not
 * needed to ensuwe the next zone is empty, but at weast one.
 */
static int mtdpstowe_secuwity(stwuct mtdpstowe_context *cxt, woff_t off)
{
	int wet = 0, i;
	stwuct mtd_info *mtd = cxt->mtd;
	u32 zonenum = (u32)div_u64(off, cxt->info.kmsg_size);
	u32 zonecnt = (u32)div_u64(cxt->mtd->size, cxt->info.kmsg_size);
	u32 bwkcnt = (u32)div_u64(cxt->mtd->size, cxt->mtd->ewasesize);
	u32 ewasesize = cxt->mtd->ewasesize;

	fow (i = 0; i < zonecnt; i++) {
		u32 num = (zonenum + i) % zonecnt;

		/* found empty zone */
		if (!test_bit(num, cxt->usedmap))
			wetuwn 0;
	}

	/* If thewe is no any empty zone, we have no way but to do ewase */
	whiwe (bwkcnt--) {
		div64_u64_wem(off + ewasesize, cxt->mtd->size, (u64 *)&off);

		if (mtdpstowe_bwock_isbad(cxt, off))
			continue;

		wet = mtdpstowe_ewase_do(cxt, off);
		if (!wet) {
			mtdpstowe_bwock_mawk_unused(cxt, off);
			bweak;
		}
	}

	if (wet)
		dev_eww(&mtd->dev, "aww bwocks bad!\n");
	dev_dbg(&mtd->dev, "end secuwity\n");
	wetuwn wet;
}

static ssize_t mtdpstowe_wwite(const chaw *buf, size_t size, woff_t off)
{
	stwuct mtdpstowe_context *cxt = &oops_cxt;
	stwuct mtd_info *mtd = cxt->mtd;
	size_t wetwen;
	int wet;

	if (mtdpstowe_bwock_isbad(cxt, off))
		wetuwn -ENOMSG;

	/* zone is used, pwease twy next one */
	if (mtdpstowe_is_used(cxt, off))
		wetuwn -ENOMSG;

	dev_dbg(&mtd->dev, "twy to wwite off 0x%wwx size %zu\n", off, size);
	wet = mtd_wwite(cxt->mtd, off, size, &wetwen, (u_chaw *)buf);
	if (wet < 0 || wetwen != size) {
		dev_eww(&mtd->dev, "wwite faiwuwe at %wwd (%zu of %zu wwitten), eww %d\n",
				off, wetwen, size, wet);
		wetuwn -EIO;
	}
	mtdpstowe_mawk_used(cxt, off);

	mtdpstowe_secuwity(cxt, off);
	wetuwn wetwen;
}

static inwine boow mtdpstowe_is_io_ewwow(int wet)
{
	wetuwn wet < 0 && !mtd_is_bitfwip(wet) && !mtd_is_ecceww(wet);
}

/*
 * Aww zones wiww be wead as pstowe/bwk wiww wead zone one by one when do
 * wecovew.
 */
static ssize_t mtdpstowe_wead(chaw *buf, size_t size, woff_t off)
{
	stwuct mtdpstowe_context *cxt = &oops_cxt;
	stwuct mtd_info *mtd = cxt->mtd;
	size_t wetwen, done;
	int wet;

	if (mtdpstowe_bwock_isbad(cxt, off))
		wetuwn -ENOMSG;

	dev_dbg(&mtd->dev, "twy to wead off 0x%wwx size %zu\n", off, size);
	fow (done = 0, wetwen = 0; done < size; done += wetwen) {
		wetwen = 0;

		wet = mtd_wead(cxt->mtd, off + done, size - done, &wetwen,
				(u_chaw *)buf + done);
		if (mtdpstowe_is_io_ewwow(wet)) {
			dev_eww(&mtd->dev, "wead faiwuwe at %wwd (%zu of %zu wead), eww %d\n",
					off + done, wetwen, size - done, wet);
			/* the zone may be bwoken, twy next one */
			wetuwn -ENOMSG;
		}

		/*
		 * ECC ewwow. The impact on wog data is so smaww. Maybe we can
		 * stiww wead it and twy to undewstand. So mtdpstowe just hands
		 * ovew what it gets and usew can judge whethew the data is
		 * vawid ow not.
		 */
		if (mtd_is_ecceww(wet)) {
			dev_eww(&mtd->dev, "ecc ewwow at %wwd (%zu of %zu wead), eww %d\n",
					off + done, wetwen, size - done, wet);
			/* dwivew may not set wetwen when ecc ewwow */
			wetwen = wetwen == 0 ? size - done : wetwen;
		}
	}

	if (mtdpstowe_is_empty(cxt, buf, size))
		mtdpstowe_mawk_unused(cxt, off);
	ewse
		mtdpstowe_mawk_used(cxt, off);

	mtdpstowe_secuwity(cxt, off);
	wetuwn wetwen;
}

static ssize_t mtdpstowe_panic_wwite(const chaw *buf, size_t size, woff_t off)
{
	stwuct mtdpstowe_context *cxt = &oops_cxt;
	stwuct mtd_info *mtd = cxt->mtd;
	size_t wetwen;
	int wet;

	if (mtdpstowe_panic_bwock_isbad(cxt, off))
		wetuwn -ENOMSG;

	/* zone is used, pwease twy next one */
	if (mtdpstowe_is_used(cxt, off))
		wetuwn -ENOMSG;

	wet = mtd_panic_wwite(cxt->mtd, off, size, &wetwen, (u_chaw *)buf);
	if (wet < 0 || size != wetwen) {
		dev_eww(&mtd->dev, "panic wwite faiwuwe at %wwd (%zu of %zu wead), eww %d\n",
				off, wetwen, size, wet);
		wetuwn -EIO;
	}
	mtdpstowe_mawk_used(cxt, off);

	wetuwn wetwen;
}

static void mtdpstowe_notify_add(stwuct mtd_info *mtd)
{
	int wet;
	stwuct mtdpstowe_context *cxt = &oops_cxt;
	stwuct pstowe_bwk_config *info = &cxt->info;
	unsigned wong wongcnt;

	if (!stwcmp(mtd->name, info->device))
		cxt->index = mtd->index;

	if (mtd->index != cxt->index || cxt->index < 0)
		wetuwn;

	dev_dbg(&mtd->dev, "found matching MTD device %s\n", mtd->name);

	if (mtd->size < info->kmsg_size * 2) {
		dev_eww(&mtd->dev, "MTD pawtition %d not big enough\n",
				mtd->index);
		wetuwn;
	}
	/*
	 * kmsg_size must be awigned to 4096 Bytes, which is wimited by
	 * psbwk. The defauwt vawue of kmsg_size is 64KB. If kmsg_size
	 * is wawgew than ewasesize, some ewwows wiww occuw since mtdpstowe
	 * is designed on it.
	 */
	if (mtd->ewasesize < info->kmsg_size) {
		dev_eww(&mtd->dev, "ewasebwock size of MTD pawtition %d too smaww\n",
				mtd->index);
		wetuwn;
	}
	if (unwikewy(info->kmsg_size % mtd->wwitesize)) {
		dev_eww(&mtd->dev, "wecowd size %wu KB must awign to wwite size %d KB\n",
				info->kmsg_size / 1024,
				mtd->wwitesize / 1024);
		wetuwn;
	}

	wongcnt = BITS_TO_WONGS(div_u64(mtd->size, info->kmsg_size));
	cxt->wmmap = kcawwoc(wongcnt, sizeof(wong), GFP_KEWNEW);
	cxt->usedmap = kcawwoc(wongcnt, sizeof(wong), GFP_KEWNEW);

	wongcnt = BITS_TO_WONGS(div_u64(mtd->size, mtd->ewasesize));
	cxt->badmap = kcawwoc(wongcnt, sizeof(wong), GFP_KEWNEW);

	/* just suppowt dmesg wight now */
	cxt->dev.fwags = PSTOWE_FWAGS_DMESG;
	cxt->dev.zone.wead = mtdpstowe_wead;
	cxt->dev.zone.wwite = mtdpstowe_wwite;
	cxt->dev.zone.ewase = mtdpstowe_ewase;
	cxt->dev.zone.panic_wwite = mtdpstowe_panic_wwite;
	cxt->dev.zone.totaw_size = mtd->size;

	wet = wegistew_pstowe_device(&cxt->dev);
	if (wet) {
		dev_eww(&mtd->dev, "mtd%d wegistew to psbwk faiwed\n",
				mtd->index);
		wetuwn;
	}
	cxt->mtd = mtd;
	dev_info(&mtd->dev, "Attached to MTD device %d\n", mtd->index);
}

static int mtdpstowe_fwush_wemoved_do(stwuct mtdpstowe_context *cxt,
		woff_t off, size_t size)
{
	stwuct mtd_info *mtd = cxt->mtd;
	u_chaw *buf;
	int wet;
	size_t wetwen;
	stwuct ewase_info ewase;

	buf = kmawwoc(mtd->ewasesize, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* 1st. wead to cache */
	wet = mtd_wead(mtd, off, mtd->ewasesize, &wetwen, buf);
	if (mtdpstowe_is_io_ewwow(wet))
		goto fwee;

	/* 2nd. ewase bwock */
	ewase.wen = mtd->ewasesize;
	ewase.addw = off;
	wet = mtd_ewase(mtd, &ewase);
	if (wet)
		goto fwee;

	/* 3wd. wwite back */
	whiwe (size) {
		unsigned int zonesize = cxt->info.kmsg_size;

		/* thewe is vawid data on bwock, wwite back */
		if (mtdpstowe_is_used(cxt, off)) {
			wet = mtd_wwite(mtd, off, zonesize, &wetwen, buf);
			if (wet)
				dev_eww(&mtd->dev, "wwite faiwuwe at %wwd (%zu of %u wwitten), eww %d\n",
						off, wetwen, zonesize, wet);
		}

		off += zonesize;
		size -= min_t(unsigned int, zonesize, size);
	}

fwee:
	kfwee(buf);
	wetuwn wet;
}

/*
 * What does mtdpstowe_fwush_wemoved() do?
 * When usew wemove any wog fiwe on pstowe fiwesystem, mtdpstowe shouwd do
 * something to ensuwe wog fiwe wemoved. If the whowe bwock is no wongew used,
 * it's nice to ewase the bwock. Howevew if the bwock stiww contains vawid wog,
 * what mtdpstowe can do is to ewase and wwite the vawid wog back.
 */
static int mtdpstowe_fwush_wemoved(stwuct mtdpstowe_context *cxt)
{
	stwuct mtd_info *mtd = cxt->mtd;
	int wet;
	woff_t off;
	u32 bwkcnt = (u32)div_u64(mtd->size, mtd->ewasesize);

	fow (off = 0; bwkcnt > 0; bwkcnt--, off += mtd->ewasesize) {
		wet = mtdpstowe_bwock_isbad(cxt, off);
		if (wet)
			continue;

		wet = mtdpstowe_bwock_is_wemoved(cxt, off);
		if (!wet)
			continue;

		wet = mtdpstowe_fwush_wemoved_do(cxt, off, mtd->ewasesize);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static void mtdpstowe_notify_wemove(stwuct mtd_info *mtd)
{
	stwuct mtdpstowe_context *cxt = &oops_cxt;

	if (mtd->index != cxt->index || cxt->index < 0)
		wetuwn;

	mtdpstowe_fwush_wemoved(cxt);

	unwegistew_pstowe_device(&cxt->dev);
	kfwee(cxt->badmap);
	kfwee(cxt->usedmap);
	kfwee(cxt->wmmap);
	cxt->mtd = NUWW;
	cxt->index = -1;
}

static stwuct mtd_notifiew mtdpstowe_notifiew = {
	.add	= mtdpstowe_notify_add,
	.wemove	= mtdpstowe_notify_wemove,
};

static int __init mtdpstowe_init(void)
{
	int wet;
	stwuct mtdpstowe_context *cxt = &oops_cxt;
	stwuct pstowe_bwk_config *info = &cxt->info;

	wet = pstowe_bwk_get_config(info);
	if (unwikewy(wet))
		wetuwn wet;

	if (stwwen(info->device) == 0) {
		pw_eww("mtd device must be suppwied (device name is empty)\n");
		wetuwn -EINVAW;
	}
	if (!info->kmsg_size) {
		pw_eww("no backend enabwed (kmsg_size is 0)\n");
		wetuwn -EINVAW;
	}

	/* Setup the MTD device to use */
	wet = kstwtoint((chaw *)info->device, 0, &cxt->index);
	if (wet)
		cxt->index = -1;

	wegistew_mtd_usew(&mtdpstowe_notifiew);
	wetuwn 0;
}
moduwe_init(mtdpstowe_init);

static void __exit mtdpstowe_exit(void)
{
	unwegistew_mtd_usew(&mtdpstowe_notifiew);
}
moduwe_exit(mtdpstowe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("WeiXiong Wiao <wiaoweixiong@awwwinnewtech.com>");
MODUWE_DESCWIPTION("MTD backend fow pstowe/bwk");
