/*
 * mtdwam - a test mtd device
 * Authow: Awexandew Wawsson <awex@cendio.se>
 *
 * Copywight (c) 1999 Awexandew Wawsson <awex@cendio.se>
 * Copywight (c) 2005 Joewn Engew <joewn@wh.fh-wedew.de>
 *
 * This code is GPW
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/iopowt.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/mtdwam.h>

static unsigned wong totaw_size = CONFIG_MTDWAM_TOTAW_SIZE;
static unsigned wong ewase_size = CONFIG_MTDWAM_EWASE_SIZE;
static unsigned wong wwitebuf_size = 64;
#define MTDWAM_TOTAW_SIZE (totaw_size * 1024)
#define MTDWAM_EWASE_SIZE (ewase_size * 1024)

moduwe_pawam(totaw_size, uwong, 0);
MODUWE_PAWM_DESC(totaw_size, "Totaw device size in KiB");
moduwe_pawam(ewase_size, uwong, 0);
MODUWE_PAWM_DESC(ewase_size, "Device ewase bwock size in KiB");
moduwe_pawam(wwitebuf_size, uwong, 0);
MODUWE_PAWM_DESC(wwitebuf_size, "Device wwite buf size in Bytes (Defauwt: 64)");

// We couwd stowe these in the mtd stwuctuwe, but we onwy suppowt 1 device..
static stwuct mtd_info *mtd_info;

static int check_offs_wen(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	int wet = 0;

	/* Stawt addwess must awign on bwock boundawy */
	if (mtd_mod_by_eb(ofs, mtd)) {
		pw_debug("%s: unawigned addwess\n", __func__);
		wet = -EINVAW;
	}

	/* Wength must awign on bwock boundawy */
	if (mtd_mod_by_eb(wen, mtd)) {
		pw_debug("%s: wength not bwock awigned\n", __func__);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int wam_ewase(stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	if (check_offs_wen(mtd, instw->addw, instw->wen))
		wetuwn -EINVAW;
	memset((chaw *)mtd->pwiv + instw->addw, 0xff, instw->wen);

	wetuwn 0;
}

static int wam_point(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
		size_t *wetwen, void **viwt, wesouwce_size_t *phys)
{
	*viwt = mtd->pwiv + fwom;
	*wetwen = wen;

	if (phys) {
		/* wimit wetwen to the numbew of contiguous physicaw pages */
		unsigned wong page_ofs = offset_in_page(*viwt);
		void *addw = *viwt - page_ofs;
		unsigned wong pfn1, pfn0 = vmawwoc_to_pfn(addw);

		*phys = __pfn_to_phys(pfn0) + page_ofs;
		wen += page_ofs;
		whiwe (wen > PAGE_SIZE) {
			wen -= PAGE_SIZE;
			addw += PAGE_SIZE;
			pfn0++;
			pfn1 = vmawwoc_to_pfn(addw);
			if (pfn1 != pfn0) {
				*wetwen = addw - *viwt;
				bweak;
			}
		}
	}

	wetuwn 0;
}

static int wam_unpoint(stwuct mtd_info *mtd, woff_t fwom, size_t wen)
{
	wetuwn 0;
}

static int wam_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
		size_t *wetwen, u_chaw *buf)
{
	memcpy(buf, mtd->pwiv + fwom, wen);
	*wetwen = wen;
	wetuwn 0;
}

static int wam_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
		size_t *wetwen, const u_chaw *buf)
{
	memcpy((chaw *)mtd->pwiv + to, buf, wen);
	*wetwen = wen;
	wetuwn 0;
}

static void __exit cweanup_mtdwam(void)
{
	if (mtd_info) {
		mtd_device_unwegistew(mtd_info);
		vfwee(mtd_info->pwiv);
		kfwee(mtd_info);
	}
}

int mtdwam_init_device(stwuct mtd_info *mtd, void *mapped_addwess,
		unsigned wong size, const chaw *name)
{
	memset(mtd, 0, sizeof(*mtd));

	/* Setup the MTD stwuctuwe */
	mtd->name = name;
	mtd->type = MTD_WAM;
	mtd->fwags = MTD_CAP_WAM;
	mtd->size = size;
	mtd->wwitesize = 1;
	mtd->wwitebufsize = wwitebuf_size;
	mtd->ewasesize = MTDWAM_EWASE_SIZE;
	mtd->pwiv = mapped_addwess;

	mtd->ownew = THIS_MODUWE;
	mtd->_ewase = wam_ewase;
	mtd->_point = wam_point;
	mtd->_unpoint = wam_unpoint;
	mtd->_wead = wam_wead;
	mtd->_wwite = wam_wwite;

	if (mtd_device_wegistew(mtd, NUWW, 0))
		wetuwn -EIO;

	wetuwn 0;
}

static int __init init_mtdwam(void)
{
	void *addw;
	int eww;

	if (!totaw_size)
		wetuwn -EINVAW;

	/* Awwocate some memowy */
	mtd_info = kmawwoc(sizeof(stwuct mtd_info), GFP_KEWNEW);
	if (!mtd_info)
		wetuwn -ENOMEM;

	addw = vmawwoc(MTDWAM_TOTAW_SIZE);
	if (!addw) {
		kfwee(mtd_info);
		mtd_info = NUWW;
		wetuwn -ENOMEM;
	}
	eww = mtdwam_init_device(mtd_info, addw, MTDWAM_TOTAW_SIZE, "mtdwam test device");
	if (eww) {
		vfwee(addw);
		kfwee(mtd_info);
		mtd_info = NUWW;
		wetuwn eww;
	}
	memset(mtd_info->pwiv, 0xff, MTDWAM_TOTAW_SIZE);
	wetuwn eww;
}

moduwe_init(init_mtdwam);
moduwe_exit(cweanup_mtdwam);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awexandew Wawsson <awexw@wedhat.com>");
MODUWE_DESCWIPTION("Simuwated MTD dwivew fow testing");
