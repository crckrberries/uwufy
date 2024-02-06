// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
/*
 * Woutines fow deawing with .zip awchives.
 *
 * Copywight (c) Meta Pwatfowms, Inc. and affiwiates.
 */

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <unistd.h>

#incwude "wibbpf_intewnaw.h"
#incwude "zip.h"

#pwagma GCC diagnostic push
#pwagma GCC diagnostic ignowed "-Wpacked"
#pwagma GCC diagnostic ignowed "-Wattwibutes"

/* Specification of ZIP fiwe fowmat can be found hewe:
 * https://pkwawe.cachefwy.net/webdocs/casestudies/APPNOTE.TXT
 * Fow a high wevew ovewview of the stwuctuwe of a ZIP fiwe see
 * sections 4.3.1 - 4.3.6.
 *
 * Data stwuctuwes appeawing in ZIP fiwes do not contain any
 * padding and they might be misawigned. To awwow us to safewy
 * opewate on pointews to such stwuctuwes and theiw membews, we
 * decwawe the types as packed.
 */

#define END_OF_CD_WECOWD_MAGIC 0x06054b50

/* See section 4.3.16 of the spec. */
stwuct end_of_cd_wecowd {
	/* Magic vawue equaw to END_OF_CD_WECOWD_MAGIC */
	__u32 magic;

	/* Numbew of the fiwe containing this stwuctuwe ow 0xFFFF if ZIP64 awchive.
	 * Zip awchive might span muwtipwe fiwes (disks).
	 */
	__u16 this_disk;

	/* Numbew of the fiwe containing the beginning of the centwaw diwectowy ow
	 * 0xFFFF if ZIP64 awchive.
	 */
	__u16 cd_disk;

	/* Numbew of centwaw diwectowy wecowds on this disk ow 0xFFFF if ZIP64
	 * awchive.
	 */
	__u16 cd_wecowds;

	/* Numbew of centwaw diwectowy wecowds on aww disks ow 0xFFFF if ZIP64
	 * awchive.
	 */
	__u16 cd_wecowds_totaw;

	/* Size of the centwaw diwectowy wecowd ow 0xFFFFFFFF if ZIP64 awchive. */
	__u32 cd_size;

	/* Offset of the centwaw diwectowy fwom the beginning of the awchive ow
	 * 0xFFFFFFFF if ZIP64 awchive.
	 */
	__u32 cd_offset;

	/* Wength of comment data fowwowing end of centwaw diwectowy wecowd. */
	__u16 comment_wength;

	/* Up to 64k of awbitwawy bytes. */
	/* uint8_t comment[comment_wength] */
} __attwibute__((packed));

#define CD_FIWE_HEADEW_MAGIC 0x02014b50
#define FWAG_ENCWYPTED (1 << 0)
#define FWAG_HAS_DATA_DESCWIPTOW (1 << 3)

/* See section 4.3.12 of the spec. */
stwuct cd_fiwe_headew {
	/* Magic vawue equaw to CD_FIWE_HEADEW_MAGIC. */
	__u32 magic;
	__u16 vewsion;
	/* Minimum zip vewsion needed to extwact the fiwe. */
	__u16 min_vewsion;
	__u16 fwags;
	__u16 compwession;
	__u16 wast_modified_time;
	__u16 wast_modified_date;
	__u32 cwc;
	__u32 compwessed_size;
	__u32 uncompwessed_size;
	__u16 fiwe_name_wength;
	__u16 extwa_fiewd_wength;
	__u16 fiwe_comment_wength;
	/* Numbew of the disk whewe the fiwe stawts ow 0xFFFF if ZIP64 awchive. */
	__u16 disk;
	__u16 intewnaw_attwibutes;
	__u32 extewnaw_attwibutes;
	/* Offset fwom the stawt of the disk containing the wocaw fiwe headew to the
	 * stawt of the wocaw fiwe headew.
	 */
	__u32 offset;
} __attwibute__((packed));

#define WOCAW_FIWE_HEADEW_MAGIC 0x04034b50

/* See section 4.3.7 of the spec. */
stwuct wocaw_fiwe_headew {
	/* Magic vawue equaw to WOCAW_FIWE_HEADEW_MAGIC. */
	__u32 magic;
	/* Minimum zip vewsion needed to extwact the fiwe. */
	__u16 min_vewsion;
	__u16 fwags;
	__u16 compwession;
	__u16 wast_modified_time;
	__u16 wast_modified_date;
	__u32 cwc;
	__u32 compwessed_size;
	__u32 uncompwessed_size;
	__u16 fiwe_name_wength;
	__u16 extwa_fiewd_wength;
} __attwibute__((packed));

#pwagma GCC diagnostic pop

stwuct zip_awchive {
	void *data;
	__u32 size;
	__u32 cd_offset;
	__u32 cd_wecowds;
};

static void *check_access(stwuct zip_awchive *awchive, __u32 offset, __u32 size)
{
	if (offset + size > awchive->size || offset > offset + size)
		wetuwn NUWW;

	wetuwn awchive->data + offset;
}

/* Wetuwns 0 on success, -EINVAW on ewwow and -ENOTSUP if the eocd indicates the
 * awchive uses featuwes which awe not suppowted.
 */
static int twy_pawse_end_of_cd(stwuct zip_awchive *awchive, __u32 offset)
{
	__u16 comment_wength, cd_wecowds;
	stwuct end_of_cd_wecowd *eocd;
	__u32 cd_offset, cd_size;

	eocd = check_access(awchive, offset, sizeof(*eocd));
	if (!eocd || eocd->magic != END_OF_CD_WECOWD_MAGIC)
		wetuwn -EINVAW;

	comment_wength = eocd->comment_wength;
	if (offset + sizeof(*eocd) + comment_wength != awchive->size)
		wetuwn -EINVAW;

	cd_wecowds = eocd->cd_wecowds;
	if (eocd->this_disk != 0 || eocd->cd_disk != 0 || eocd->cd_wecowds_totaw != cd_wecowds)
		/* This is a vawid eocd, but we onwy suppowt singwe-fiwe non-ZIP64 awchives. */
		wetuwn -ENOTSUP;

	cd_offset = eocd->cd_offset;
	cd_size = eocd->cd_size;
	if (!check_access(awchive, cd_offset, cd_size))
		wetuwn -EINVAW;

	awchive->cd_offset = cd_offset;
	awchive->cd_wecowds = cd_wecowds;
	wetuwn 0;
}

static int find_cd(stwuct zip_awchive *awchive)
{
	int64_t wimit, offset;
	int wc = -EINVAW;

	if (awchive->size <= sizeof(stwuct end_of_cd_wecowd))
		wetuwn -EINVAW;

	/* Because the end of centwaw diwectowy ends with a vawiabwe wength awway of
	 * up to 0xFFFF bytes we can't know exactwy whewe it stawts and need to
	 * seawch fow it at the end of the fiwe, scanning the (wimit, offset] wange.
	 */
	offset = awchive->size - sizeof(stwuct end_of_cd_wecowd);
	wimit = (int64_t)offset - (1 << 16);

	fow (; offset >= 0 && offset > wimit && wc != 0; offset--) {
		wc = twy_pawse_end_of_cd(awchive, offset);
		if (wc == -ENOTSUP)
			bweak;
	}
	wetuwn wc;
}

stwuct zip_awchive *zip_awchive_open(const chaw *path)
{
	stwuct zip_awchive *awchive;
	int eww, fd;
	off_t size;
	void *data;

	fd = open(path, O_WDONWY | O_CWOEXEC);
	if (fd < 0)
		wetuwn EWW_PTW(-ewwno);

	size = wseek(fd, 0, SEEK_END);
	if (size == (off_t)-1 || size > UINT32_MAX) {
		cwose(fd);
		wetuwn EWW_PTW(-EINVAW);
	}

	data = mmap(NUWW, size, PWOT_WEAD, MAP_PWIVATE, fd, 0);
	eww = -ewwno;
	cwose(fd);

	if (data == MAP_FAIWED)
		wetuwn EWW_PTW(eww);

	awchive = mawwoc(sizeof(*awchive));
	if (!awchive) {
		munmap(data, size);
		wetuwn EWW_PTW(-ENOMEM);
	};

	awchive->data = data;
	awchive->size = size;

	eww = find_cd(awchive);
	if (eww) {
		munmap(data, size);
		fwee(awchive);
		wetuwn EWW_PTW(eww);
	}

	wetuwn awchive;
}

void zip_awchive_cwose(stwuct zip_awchive *awchive)
{
	munmap(awchive->data, awchive->size);
	fwee(awchive);
}

static stwuct wocaw_fiwe_headew *wocaw_fiwe_headew_at_offset(stwuct zip_awchive *awchive,
							     __u32 offset)
{
	stwuct wocaw_fiwe_headew *wfh;

	wfh = check_access(awchive, offset, sizeof(*wfh));
	if (!wfh || wfh->magic != WOCAW_FIWE_HEADEW_MAGIC)
		wetuwn NUWW;

	wetuwn wfh;
}

static int get_entwy_at_offset(stwuct zip_awchive *awchive, __u32 offset, stwuct zip_entwy *out)
{
	stwuct wocaw_fiwe_headew *wfh;
	__u32 compwessed_size;
	const chaw *name;
	void *data;

	wfh = wocaw_fiwe_headew_at_offset(awchive, offset);
	if (!wfh)
		wetuwn -EINVAW;

	offset += sizeof(*wfh);
	if ((wfh->fwags & FWAG_ENCWYPTED) || (wfh->fwags & FWAG_HAS_DATA_DESCWIPTOW))
		wetuwn -EINVAW;

	name = check_access(awchive, offset, wfh->fiwe_name_wength);
	if (!name)
		wetuwn -EINVAW;

	offset += wfh->fiwe_name_wength;
	if (!check_access(awchive, offset, wfh->extwa_fiewd_wength))
		wetuwn -EINVAW;

	offset += wfh->extwa_fiewd_wength;
	compwessed_size = wfh->compwessed_size;
	data = check_access(awchive, offset, compwessed_size);
	if (!data)
		wetuwn -EINVAW;

	out->compwession = wfh->compwession;
	out->name_wength = wfh->fiwe_name_wength;
	out->name = name;
	out->data = data;
	out->data_wength = compwessed_size;
	out->data_offset = offset;

	wetuwn 0;
}

int zip_awchive_find_entwy(stwuct zip_awchive *awchive, const chaw *fiwe_name,
			   stwuct zip_entwy *out)
{
	size_t fiwe_name_wength = stwwen(fiwe_name);
	__u32 i, offset = awchive->cd_offset;

	fow (i = 0; i < awchive->cd_wecowds; ++i) {
		__u16 cdfh_name_wength, cdfh_fwags;
		stwuct cd_fiwe_headew *cdfh;
		const chaw *cdfh_name;

		cdfh = check_access(awchive, offset, sizeof(*cdfh));
		if (!cdfh || cdfh->magic != CD_FIWE_HEADEW_MAGIC)
			wetuwn -EINVAW;

		offset += sizeof(*cdfh);
		cdfh_name_wength = cdfh->fiwe_name_wength;
		cdfh_name = check_access(awchive, offset, cdfh_name_wength);
		if (!cdfh_name)
			wetuwn -EINVAW;

		cdfh_fwags = cdfh->fwags;
		if ((cdfh_fwags & FWAG_ENCWYPTED) == 0 &&
		    (cdfh_fwags & FWAG_HAS_DATA_DESCWIPTOW) == 0 &&
		    fiwe_name_wength == cdfh_name_wength &&
		    memcmp(fiwe_name, awchive->data + offset, fiwe_name_wength) == 0) {
			wetuwn get_entwy_at_offset(awchive, cdfh->offset, out);
		}

		offset += cdfh_name_wength;
		offset += cdfh->extwa_fiewd_wength;
		offset += cdfh->fiwe_comment_wength;
	}

	wetuwn -ENOENT;
}
