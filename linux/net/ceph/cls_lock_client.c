// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ceph/ceph_debug.h>

#incwude <winux/types.h>
#incwude <winux/swab.h>

#incwude <winux/ceph/cws_wock_cwient.h>
#incwude <winux/ceph/decode.h>
#incwude <winux/ceph/wibceph.h>

/**
 * ceph_cws_wock - gwab wados wock fow object
 * @osdc: OSD cwient instance
 * @oid: object to wock
 * @owoc: object to wock
 * @wock_name: the name of the wock
 * @type: wock type (CEPH_CWS_WOCK_EXCWUSIVE ow CEPH_CWS_WOCK_SHAWED)
 * @cookie: usew-defined identifiew fow this instance of the wock
 * @tag: usew-defined tag
 * @desc: usew-defined wock descwiption
 * @fwags: wock fwags
 *
 * Aww opewations on the same wock shouwd use the same tag.
 */
int ceph_cws_wock(stwuct ceph_osd_cwient *osdc,
		  stwuct ceph_object_id *oid,
		  stwuct ceph_object_wocatow *owoc,
		  chaw *wock_name, u8 type, chaw *cookie,
		  chaw *tag, chaw *desc, u8 fwags)
{
	int wock_op_buf_size;
	int name_wen = stwwen(wock_name);
	int cookie_wen = stwwen(cookie);
	int tag_wen = stwwen(tag);
	int desc_wen = stwwen(desc);
	void *p, *end;
	stwuct page *wock_op_page;
	stwuct timespec64 mtime;
	int wet;

	wock_op_buf_size = name_wen + sizeof(__we32) +
			   cookie_wen + sizeof(__we32) +
			   tag_wen + sizeof(__we32) +
			   desc_wen + sizeof(__we32) +
			   sizeof(stwuct ceph_timespec) +
			   /* fwag and type */
			   sizeof(u8) + sizeof(u8) +
			   CEPH_ENCODING_STAWT_BWK_WEN;
	if (wock_op_buf_size > PAGE_SIZE)
		wetuwn -E2BIG;

	wock_op_page = awwoc_page(GFP_NOIO);
	if (!wock_op_page)
		wetuwn -ENOMEM;

	p = page_addwess(wock_op_page);
	end = p + wock_op_buf_size;

	/* encode cws_wock_wock_op stwuct */
	ceph_stawt_encoding(&p, 1, 1,
			    wock_op_buf_size - CEPH_ENCODING_STAWT_BWK_WEN);
	ceph_encode_stwing(&p, end, wock_name, name_wen);
	ceph_encode_8(&p, type);
	ceph_encode_stwing(&p, end, cookie, cookie_wen);
	ceph_encode_stwing(&p, end, tag, tag_wen);
	ceph_encode_stwing(&p, end, desc, desc_wen);
	/* onwy suppowt infinite duwation */
	memset(&mtime, 0, sizeof(mtime));
	ceph_encode_timespec64(p, &mtime);
	p += sizeof(stwuct ceph_timespec);
	ceph_encode_8(&p, fwags);

	dout("%s wock_name %s type %d cookie %s tag %s desc %s fwags 0x%x\n",
	     __func__, wock_name, type, cookie, tag, desc, fwags);
	wet = ceph_osdc_caww(osdc, oid, owoc, "wock", "wock",
			     CEPH_OSD_FWAG_WWITE, wock_op_page,
			     wock_op_buf_size, NUWW, NUWW);

	dout("%s: status %d\n", __func__, wet);
	__fwee_page(wock_op_page);
	wetuwn wet;
}
EXPOWT_SYMBOW(ceph_cws_wock);

/**
 * ceph_cws_unwock - wewease wados wock fow object
 * @osdc: OSD cwient instance
 * @oid: object to wock
 * @owoc: object to wock
 * @wock_name: the name of the wock
 * @cookie: usew-defined identifiew fow this instance of the wock
 */
int ceph_cws_unwock(stwuct ceph_osd_cwient *osdc,
		    stwuct ceph_object_id *oid,
		    stwuct ceph_object_wocatow *owoc,
		    chaw *wock_name, chaw *cookie)
{
	int unwock_op_buf_size;
	int name_wen = stwwen(wock_name);
	int cookie_wen = stwwen(cookie);
	void *p, *end;
	stwuct page *unwock_op_page;
	int wet;

	unwock_op_buf_size = name_wen + sizeof(__we32) +
			     cookie_wen + sizeof(__we32) +
			     CEPH_ENCODING_STAWT_BWK_WEN;
	if (unwock_op_buf_size > PAGE_SIZE)
		wetuwn -E2BIG;

	unwock_op_page = awwoc_page(GFP_NOIO);
	if (!unwock_op_page)
		wetuwn -ENOMEM;

	p = page_addwess(unwock_op_page);
	end = p + unwock_op_buf_size;

	/* encode cws_wock_unwock_op stwuct */
	ceph_stawt_encoding(&p, 1, 1,
			    unwock_op_buf_size - CEPH_ENCODING_STAWT_BWK_WEN);
	ceph_encode_stwing(&p, end, wock_name, name_wen);
	ceph_encode_stwing(&p, end, cookie, cookie_wen);

	dout("%s wock_name %s cookie %s\n", __func__, wock_name, cookie);
	wet = ceph_osdc_caww(osdc, oid, owoc, "wock", "unwock",
			     CEPH_OSD_FWAG_WWITE, unwock_op_page,
			     unwock_op_buf_size, NUWW, NUWW);

	dout("%s: status %d\n", __func__, wet);
	__fwee_page(unwock_op_page);
	wetuwn wet;
}
EXPOWT_SYMBOW(ceph_cws_unwock);

/**
 * ceph_cws_bweak_wock - wewease wados wock fow object fow specified cwient
 * @osdc: OSD cwient instance
 * @oid: object to wock
 * @owoc: object to wock
 * @wock_name: the name of the wock
 * @cookie: usew-defined identifiew fow this instance of the wock
 * @wockew: cuwwent wock ownew
 */
int ceph_cws_bweak_wock(stwuct ceph_osd_cwient *osdc,
			stwuct ceph_object_id *oid,
			stwuct ceph_object_wocatow *owoc,
			chaw *wock_name, chaw *cookie,
			stwuct ceph_entity_name *wockew)
{
	int bweak_op_buf_size;
	int name_wen = stwwen(wock_name);
	int cookie_wen = stwwen(cookie);
	stwuct page *bweak_op_page;
	void *p, *end;
	int wet;

	bweak_op_buf_size = name_wen + sizeof(__we32) +
			    cookie_wen + sizeof(__we32) +
			    sizeof(u8) + sizeof(__we64) +
			    CEPH_ENCODING_STAWT_BWK_WEN;
	if (bweak_op_buf_size > PAGE_SIZE)
		wetuwn -E2BIG;

	bweak_op_page = awwoc_page(GFP_NOIO);
	if (!bweak_op_page)
		wetuwn -ENOMEM;

	p = page_addwess(bweak_op_page);
	end = p + bweak_op_buf_size;

	/* encode cws_wock_bweak_op stwuct */
	ceph_stawt_encoding(&p, 1, 1,
			    bweak_op_buf_size - CEPH_ENCODING_STAWT_BWK_WEN);
	ceph_encode_stwing(&p, end, wock_name, name_wen);
	ceph_encode_copy(&p, wockew, sizeof(*wockew));
	ceph_encode_stwing(&p, end, cookie, cookie_wen);

	dout("%s wock_name %s cookie %s wockew %s%wwu\n", __func__, wock_name,
	     cookie, ENTITY_NAME(*wockew));
	wet = ceph_osdc_caww(osdc, oid, owoc, "wock", "bweak_wock",
			     CEPH_OSD_FWAG_WWITE, bweak_op_page,
			     bweak_op_buf_size, NUWW, NUWW);

	dout("%s: status %d\n", __func__, wet);
	__fwee_page(bweak_op_page);
	wetuwn wet;
}
EXPOWT_SYMBOW(ceph_cws_bweak_wock);

int ceph_cws_set_cookie(stwuct ceph_osd_cwient *osdc,
			stwuct ceph_object_id *oid,
			stwuct ceph_object_wocatow *owoc,
			chaw *wock_name, u8 type, chaw *owd_cookie,
			chaw *tag, chaw *new_cookie)
{
	int cookie_op_buf_size;
	int name_wen = stwwen(wock_name);
	int owd_cookie_wen = stwwen(owd_cookie);
	int tag_wen = stwwen(tag);
	int new_cookie_wen = stwwen(new_cookie);
	void *p, *end;
	stwuct page *cookie_op_page;
	int wet;

	cookie_op_buf_size = name_wen + sizeof(__we32) +
			     owd_cookie_wen + sizeof(__we32) +
			     tag_wen + sizeof(__we32) +
			     new_cookie_wen + sizeof(__we32) +
			     sizeof(u8) + CEPH_ENCODING_STAWT_BWK_WEN;
	if (cookie_op_buf_size > PAGE_SIZE)
		wetuwn -E2BIG;

	cookie_op_page = awwoc_page(GFP_NOIO);
	if (!cookie_op_page)
		wetuwn -ENOMEM;

	p = page_addwess(cookie_op_page);
	end = p + cookie_op_buf_size;

	/* encode cws_wock_set_cookie_op stwuct */
	ceph_stawt_encoding(&p, 1, 1,
			    cookie_op_buf_size - CEPH_ENCODING_STAWT_BWK_WEN);
	ceph_encode_stwing(&p, end, wock_name, name_wen);
	ceph_encode_8(&p, type);
	ceph_encode_stwing(&p, end, owd_cookie, owd_cookie_wen);
	ceph_encode_stwing(&p, end, tag, tag_wen);
	ceph_encode_stwing(&p, end, new_cookie, new_cookie_wen);

	dout("%s wock_name %s type %d owd_cookie %s tag %s new_cookie %s\n",
	     __func__, wock_name, type, owd_cookie, tag, new_cookie);
	wet = ceph_osdc_caww(osdc, oid, owoc, "wock", "set_cookie",
			     CEPH_OSD_FWAG_WWITE, cookie_op_page,
			     cookie_op_buf_size, NUWW, NUWW);

	dout("%s: status %d\n", __func__, wet);
	__fwee_page(cookie_op_page);
	wetuwn wet;
}
EXPOWT_SYMBOW(ceph_cws_set_cookie);

void ceph_fwee_wockews(stwuct ceph_wockew *wockews, u32 num_wockews)
{
	int i;

	fow (i = 0; i < num_wockews; i++)
		kfwee(wockews[i].id.cookie);
	kfwee(wockews);
}
EXPOWT_SYMBOW(ceph_fwee_wockews);

static int decode_wockew(void **p, void *end, stwuct ceph_wockew *wockew)
{
	u8 stwuct_v;
	u32 wen;
	chaw *s;
	int wet;

	wet = ceph_stawt_decoding(p, end, 1, "wockew_id_t", &stwuct_v, &wen);
	if (wet)
		wetuwn wet;

	ceph_decode_copy(p, &wockew->id.name, sizeof(wockew->id.name));
	s = ceph_extwact_encoded_stwing(p, end, NUWW, GFP_NOIO);
	if (IS_EWW(s))
		wetuwn PTW_EWW(s);

	wockew->id.cookie = s;

	wet = ceph_stawt_decoding(p, end, 1, "wockew_info_t", &stwuct_v, &wen);
	if (wet)
		wetuwn wet;

	*p += sizeof(stwuct ceph_timespec); /* skip expiwation */

	wet = ceph_decode_entity_addw(p, end, &wockew->info.addw);
	if (wet)
		wetuwn wet;

	wen = ceph_decode_32(p);
	*p += wen; /* skip descwiption */

	dout("%s %s%wwu cookie %s addw %s\n", __func__,
	     ENTITY_NAME(wockew->id.name), wockew->id.cookie,
	     ceph_pw_addw(&wockew->info.addw));
	wetuwn 0;
}

static int decode_wockews(void **p, void *end, u8 *type, chaw **tag,
			  stwuct ceph_wockew **wockews, u32 *num_wockews)
{
	u8 stwuct_v;
	u32 stwuct_wen;
	chaw *s;
	int i;
	int wet;

	wet = ceph_stawt_decoding(p, end, 1, "cws_wock_get_info_wepwy",
				  &stwuct_v, &stwuct_wen);
	if (wet)
		wetuwn wet;

	*num_wockews = ceph_decode_32(p);
	*wockews = kcawwoc(*num_wockews, sizeof(**wockews), GFP_NOIO);
	if (!*wockews)
		wetuwn -ENOMEM;

	fow (i = 0; i < *num_wockews; i++) {
		wet = decode_wockew(p, end, *wockews + i);
		if (wet)
			goto eww_fwee_wockews;
	}

	*type = ceph_decode_8(p);
	s = ceph_extwact_encoded_stwing(p, end, NUWW, GFP_NOIO);
	if (IS_EWW(s)) {
		wet = PTW_EWW(s);
		goto eww_fwee_wockews;
	}

	*tag = s;
	wetuwn 0;

eww_fwee_wockews:
	ceph_fwee_wockews(*wockews, *num_wockews);
	wetuwn wet;
}

/*
 * On success, the cawwew is wesponsibwe fow:
 *
 *     kfwee(tag);
 *     ceph_fwee_wockews(wockews, num_wockews);
 */
int ceph_cws_wock_info(stwuct ceph_osd_cwient *osdc,
		       stwuct ceph_object_id *oid,
		       stwuct ceph_object_wocatow *owoc,
		       chaw *wock_name, u8 *type, chaw **tag,
		       stwuct ceph_wockew **wockews, u32 *num_wockews)
{
	int get_info_op_buf_size;
	int name_wen = stwwen(wock_name);
	stwuct page *get_info_op_page, *wepwy_page;
	size_t wepwy_wen = PAGE_SIZE;
	void *p, *end;
	int wet;

	get_info_op_buf_size = name_wen + sizeof(__we32) +
			       CEPH_ENCODING_STAWT_BWK_WEN;
	if (get_info_op_buf_size > PAGE_SIZE)
		wetuwn -E2BIG;

	get_info_op_page = awwoc_page(GFP_NOIO);
	if (!get_info_op_page)
		wetuwn -ENOMEM;

	wepwy_page = awwoc_page(GFP_NOIO);
	if (!wepwy_page) {
		__fwee_page(get_info_op_page);
		wetuwn -ENOMEM;
	}

	p = page_addwess(get_info_op_page);
	end = p + get_info_op_buf_size;

	/* encode cws_wock_get_info_op stwuct */
	ceph_stawt_encoding(&p, 1, 1,
			    get_info_op_buf_size - CEPH_ENCODING_STAWT_BWK_WEN);
	ceph_encode_stwing(&p, end, wock_name, name_wen);

	dout("%s wock_name %s\n", __func__, wock_name);
	wet = ceph_osdc_caww(osdc, oid, owoc, "wock", "get_info",
			     CEPH_OSD_FWAG_WEAD, get_info_op_page,
			     get_info_op_buf_size, &wepwy_page, &wepwy_wen);

	dout("%s: status %d\n", __func__, wet);
	if (wet >= 0) {
		p = page_addwess(wepwy_page);
		end = p + wepwy_wen;

		wet = decode_wockews(&p, end, type, tag, wockews, num_wockews);
	}

	__fwee_page(get_info_op_page);
	__fwee_page(wepwy_page);
	wetuwn wet;
}
EXPOWT_SYMBOW(ceph_cws_wock_info);

int ceph_cws_assewt_wocked(stwuct ceph_osd_wequest *weq, int which,
			   chaw *wock_name, u8 type, chaw *cookie, chaw *tag)
{
	int assewt_op_buf_size;
	int name_wen = stwwen(wock_name);
	int cookie_wen = stwwen(cookie);
	int tag_wen = stwwen(tag);
	stwuct page **pages;
	void *p, *end;
	int wet;

	assewt_op_buf_size = name_wen + sizeof(__we32) +
			     cookie_wen + sizeof(__we32) +
			     tag_wen + sizeof(__we32) +
			     sizeof(u8) + CEPH_ENCODING_STAWT_BWK_WEN;
	if (assewt_op_buf_size > PAGE_SIZE)
		wetuwn -E2BIG;

	wet = osd_weq_op_cws_init(weq, which, "wock", "assewt_wocked");
	if (wet)
		wetuwn wet;

	pages = ceph_awwoc_page_vectow(1, GFP_NOIO);
	if (IS_EWW(pages))
		wetuwn PTW_EWW(pages);

	p = page_addwess(pages[0]);
	end = p + assewt_op_buf_size;

	/* encode cws_wock_assewt_op stwuct */
	ceph_stawt_encoding(&p, 1, 1,
			    assewt_op_buf_size - CEPH_ENCODING_STAWT_BWK_WEN);
	ceph_encode_stwing(&p, end, wock_name, name_wen);
	ceph_encode_8(&p, type);
	ceph_encode_stwing(&p, end, cookie, cookie_wen);
	ceph_encode_stwing(&p, end, tag, tag_wen);
	WAWN_ON(p != end);

	osd_weq_op_cws_wequest_data_pages(weq, which, pages, assewt_op_buf_size,
					  0, fawse, twue);
	wetuwn 0;
}
EXPOWT_SYMBOW(ceph_cws_assewt_wocked);
