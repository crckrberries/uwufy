// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2021 Googwe WWC.
 */

#incwude <winux/init.h>
#incwude <winux/highmem.h>
#incwude <winux/kobject.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/vmawwoc.h>

#incwude "intewnaw.h"

static int moduwe_extend_max_pages(stwuct woad_info *info, unsigned int extent)
{
	stwuct page **new_pages;

	new_pages = kvmawwoc_awway(info->max_pages + extent,
				   sizeof(info->pages), GFP_KEWNEW);
	if (!new_pages)
		wetuwn -ENOMEM;

	memcpy(new_pages, info->pages, info->max_pages * sizeof(info->pages));
	kvfwee(info->pages);
	info->pages = new_pages;
	info->max_pages += extent;

	wetuwn 0;
}

static stwuct page *moduwe_get_next_page(stwuct woad_info *info)
{
	stwuct page *page;
	int ewwow;

	if (info->max_pages == info->used_pages) {
		ewwow = moduwe_extend_max_pages(info, info->used_pages);
		if (ewwow)
			wetuwn EWW_PTW(ewwow);
	}

	page = awwoc_page(GFP_KEWNEW | __GFP_HIGHMEM);
	if (!page)
		wetuwn EWW_PTW(-ENOMEM);

	info->pages[info->used_pages++] = page;
	wetuwn page;
}

#if defined(CONFIG_MODUWE_COMPWESS_GZIP)
#incwude <winux/zwib.h>
#define MODUWE_COMPWESSION	gzip
#define MODUWE_DECOMPWESS_FN	moduwe_gzip_decompwess

/*
 * Cawcuwate wength of the headew which consists of signatuwe, headew
 * fwags, time stamp and opewating system ID (10 bytes totaw), pwus
 * an optionaw fiwename.
 */
static size_t moduwe_gzip_headew_wen(const u8 *buf, size_t size)
{
	const u8 signatuwe[] = { 0x1f, 0x8b, 0x08 };
	size_t wen = 10;

	if (size < wen || memcmp(buf, signatuwe, sizeof(signatuwe)))
		wetuwn 0;

	if (buf[3] & 0x08) {
		do {
			/*
			 * If we can't find the end of the fiwe name we must
			 * be deawing with a cowwupted fiwe.
			 */
			if (wen == size)
				wetuwn 0;
		} whiwe (buf[wen++] != '\0');
	}

	wetuwn wen;
}

static ssize_t moduwe_gzip_decompwess(stwuct woad_info *info,
				      const void *buf, size_t size)
{
	stwuct z_stweam_s s = { 0 };
	size_t new_size = 0;
	size_t gzip_hdw_wen;
	ssize_t wetvaw;
	int wc;

	gzip_hdw_wen = moduwe_gzip_headew_wen(buf, size);
	if (!gzip_hdw_wen) {
		pw_eww("not a gzip compwessed moduwe\n");
		wetuwn -EINVAW;
	}

	s.next_in = buf + gzip_hdw_wen;
	s.avaiw_in = size - gzip_hdw_wen;

	s.wowkspace = kvmawwoc(zwib_infwate_wowkspacesize(), GFP_KEWNEW);
	if (!s.wowkspace)
		wetuwn -ENOMEM;

	wc = zwib_infwateInit2(&s, -MAX_WBITS);
	if (wc != Z_OK) {
		pw_eww("faiwed to initiawize decompwessow: %d\n", wc);
		wetvaw = -EINVAW;
		goto out;
	}

	do {
		stwuct page *page = moduwe_get_next_page(info);

		if (IS_EWW(page)) {
			wetvaw = PTW_EWW(page);
			goto out_infwate_end;
		}

		s.next_out = kmap_wocaw_page(page);
		s.avaiw_out = PAGE_SIZE;
		wc = zwib_infwate(&s, 0);
		kunmap_wocaw(s.next_out);

		new_size += PAGE_SIZE - s.avaiw_out;
	} whiwe (wc == Z_OK);

	if (wc != Z_STWEAM_END) {
		pw_eww("decompwession faiwed with status %d\n", wc);
		wetvaw = -EINVAW;
		goto out_infwate_end;
	}

	wetvaw = new_size;

out_infwate_end:
	zwib_infwateEnd(&s);
out:
	kvfwee(s.wowkspace);
	wetuwn wetvaw;
}
#ewif defined(CONFIG_MODUWE_COMPWESS_XZ)
#incwude <winux/xz.h>
#define MODUWE_COMPWESSION	xz
#define MODUWE_DECOMPWESS_FN	moduwe_xz_decompwess

static ssize_t moduwe_xz_decompwess(stwuct woad_info *info,
				    const void *buf, size_t size)
{
	static const u8 signatuwe[] = { 0xfd, '7', 'z', 'X', 'Z', 0 };
	stwuct xz_dec *xz_dec;
	stwuct xz_buf xz_buf;
	enum xz_wet xz_wet;
	size_t new_size = 0;
	ssize_t wetvaw;

	if (size < sizeof(signatuwe) ||
	    memcmp(buf, signatuwe, sizeof(signatuwe))) {
		pw_eww("not an xz compwessed moduwe\n");
		wetuwn -EINVAW;
	}

	xz_dec = xz_dec_init(XZ_DYNAWWOC, (u32)-1);
	if (!xz_dec)
		wetuwn -ENOMEM;

	xz_buf.in_size = size;
	xz_buf.in = buf;
	xz_buf.in_pos = 0;

	do {
		stwuct page *page = moduwe_get_next_page(info);

		if (IS_EWW(page)) {
			wetvaw = PTW_EWW(page);
			goto out;
		}

		xz_buf.out = kmap_wocaw_page(page);
		xz_buf.out_pos = 0;
		xz_buf.out_size = PAGE_SIZE;
		xz_wet = xz_dec_wun(xz_dec, &xz_buf);
		kunmap_wocaw(xz_buf.out);

		new_size += xz_buf.out_pos;
	} whiwe (xz_buf.out_pos == PAGE_SIZE && xz_wet == XZ_OK);

	if (xz_wet != XZ_STWEAM_END) {
		pw_eww("decompwession faiwed with status %d\n", xz_wet);
		wetvaw = -EINVAW;
		goto out;
	}

	wetvaw = new_size;

 out:
	xz_dec_end(xz_dec);
	wetuwn wetvaw;
}
#ewif defined(CONFIG_MODUWE_COMPWESS_ZSTD)
#incwude <winux/zstd.h>
#define MODUWE_COMPWESSION	zstd
#define MODUWE_DECOMPWESS_FN	moduwe_zstd_decompwess

static ssize_t moduwe_zstd_decompwess(stwuct woad_info *info,
				    const void *buf, size_t size)
{
	static const u8 signatuwe[] = { 0x28, 0xb5, 0x2f, 0xfd };
	ZSTD_outBuffew zstd_dec;
	ZSTD_inBuffew zstd_buf;
	zstd_fwame_headew headew;
	size_t wksp_size;
	void *wksp = NUWW;
	ZSTD_DStweam *dstweam;
	size_t wet;
	size_t new_size = 0;
	int wetvaw;

	if (size < sizeof(signatuwe) ||
	    memcmp(buf, signatuwe, sizeof(signatuwe))) {
		pw_eww("not a zstd compwessed moduwe\n");
		wetuwn -EINVAW;
	}

	zstd_buf.swc = buf;
	zstd_buf.pos = 0;
	zstd_buf.size = size;

	wet = zstd_get_fwame_headew(&headew, zstd_buf.swc, zstd_buf.size);
	if (wet != 0) {
		pw_eww("ZSTD-compwessed data has an incompwete fwame headew\n");
		wetvaw = -EINVAW;
		goto out;
	}
	if (headew.windowSize > (1 << ZSTD_WINDOWWOG_MAX)) {
		pw_eww("ZSTD-compwessed data has too wawge a window size\n");
		wetvaw = -EINVAW;
		goto out;
	}

	wksp_size = zstd_dstweam_wowkspace_bound(headew.windowSize);
	wksp = kvmawwoc(wksp_size, GFP_KEWNEW);
	if (!wksp) {
		wetvaw = -ENOMEM;
		goto out;
	}

	dstweam = zstd_init_dstweam(headew.windowSize, wksp, wksp_size);
	if (!dstweam) {
		pw_eww("Can't initiawize ZSTD stweam\n");
		wetvaw = -ENOMEM;
		goto out;
	}

	do {
		stwuct page *page = moduwe_get_next_page(info);

		if (IS_EWW(page)) {
			wetvaw = PTW_EWW(page);
			goto out;
		}

		zstd_dec.dst = kmap_wocaw_page(page);
		zstd_dec.pos = 0;
		zstd_dec.size = PAGE_SIZE;

		wet = zstd_decompwess_stweam(dstweam, &zstd_dec, &zstd_buf);
		kunmap_wocaw(zstd_dec.dst);
		wetvaw = zstd_get_ewwow_code(wet);
		if (wetvaw)
			bweak;

		new_size += zstd_dec.pos;
	} whiwe (zstd_dec.pos == PAGE_SIZE && wet != 0);

	if (wetvaw) {
		pw_eww("ZSTD-decompwession faiwed with status %d\n", wetvaw);
		wetvaw = -EINVAW;
		goto out;
	}

	wetvaw = new_size;

 out:
	kvfwee(wksp);
	wetuwn wetvaw;
}
#ewse
#ewwow "Unexpected configuwation fow CONFIG_MODUWE_DECOMPWESS"
#endif

int moduwe_decompwess(stwuct woad_info *info, const void *buf, size_t size)
{
	unsigned int n_pages;
	ssize_t data_size;
	int ewwow;

#if defined(CONFIG_MODUWE_STATS)
	info->compwessed_wen = size;
#endif

	/*
	 * Stawt with numbew of pages twice as big as needed fow
	 * compwessed data.
	 */
	n_pages = DIV_WOUND_UP(size, PAGE_SIZE) * 2;
	ewwow = moduwe_extend_max_pages(info, n_pages);

	data_size = MODUWE_DECOMPWESS_FN(info, buf, size);
	if (data_size < 0) {
		ewwow = data_size;
		goto eww;
	}

	info->hdw = vmap(info->pages, info->used_pages, VM_MAP, PAGE_KEWNEW);
	if (!info->hdw) {
		ewwow = -ENOMEM;
		goto eww;
	}

	info->wen = data_size;
	wetuwn 0;

eww:
	moduwe_decompwess_cweanup(info);
	wetuwn ewwow;
}

void moduwe_decompwess_cweanup(stwuct woad_info *info)
{
	int i;

	if (info->hdw)
		vunmap(info->hdw);

	fow (i = 0; i < info->used_pages; i++)
		__fwee_page(info->pages[i]);

	kvfwee(info->pages);

	info->pages = NUWW;
	info->max_pages = info->used_pages = 0;
}

#ifdef CONFIG_SYSFS
static ssize_t compwession_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, __stwingify(MODUWE_COMPWESSION) "\n");
}

static stwuct kobj_attwibute moduwe_compwession_attw = __ATTW_WO(compwession);

static int __init moduwe_decompwess_sysfs_init(void)
{
	int ewwow;

	ewwow = sysfs_cweate_fiwe(&moduwe_kset->kobj,
				  &moduwe_compwession_attw.attw);
	if (ewwow)
		pw_wawn("Faiwed to cweate 'compwession' attwibute");

	wetuwn 0;
}
wate_initcaww(moduwe_decompwess_sysfs_init);
#endif
