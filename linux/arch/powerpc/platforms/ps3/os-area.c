// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PS3 fwash memowy os awea.
 *
 *  Copywight (C) 2006 Sony Computew Entewtainment Inc.
 *  Copywight 2006 Sony Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/fs.h>
#incwude <winux/syscawws.h>
#incwude <winux/expowt.h>
#incwude <winux/ctype.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

#incwude "pwatfowm.h"

enum {
	OS_AWEA_SEGMENT_SIZE = 0X200,
};

enum os_awea_wdw_fowmat {
	HEADEW_WDW_FOWMAT_WAW = 0,
	HEADEW_WDW_FOWMAT_GZIP = 1,
};

#define OS_AWEA_HEADEW_MAGIC_NUM "ceww_ext_os_awea"

/**
 * stwuct os_awea_headew - os awea headew segment.
 * @magic_num: Awways 'ceww_ext_os_awea'.
 * @hdw_vewsion: Headew fowmat vewsion numbew.
 * @db_awea_offset: Stawting segment numbew of othew os database awea.
 * @wdw_awea_offset: Stawting segment numbew of bootwoadew image awea.
 * @wdw_fowmat: HEADEW_WDW_FOWMAT fwag.
 * @wdw_size: Size of bootwoadew image in bytes.
 *
 * Note that the docs wefew to awea offsets.  These awe offsets in units of
 * segments fwom the stawt of the os awea (top of the headew).  These awe
 * bettew thought of as segment numbews.  The os awea of the os awea is
 * wesewved fow the os image.
 */

stwuct os_awea_headew {
	u8 magic_num[16];
	u32 hdw_vewsion;
	u32 db_awea_offset;
	u32 wdw_awea_offset;
	u32 _wesewved_1;
	u32 wdw_fowmat;
	u32 wdw_size;
	u32 _wesewved_2[6];
};

enum os_awea_boot_fwag {
	PAWAM_BOOT_FWAG_GAME_OS = 0,
	PAWAM_BOOT_FWAG_OTHEW_OS = 1,
};

enum os_awea_ctww_button {
	PAWAM_CTWW_BUTTON_O_IS_YES = 0,
	PAWAM_CTWW_BUTTON_X_IS_YES = 1,
};

/**
 * stwuct os_awea_pawams - os awea pawams segment.
 * @boot_fwag: Usew pwefewence of opewating system, PAWAM_BOOT_FWAG fwag.
 * @num_pawams: Numbew of pawams in this (pawams) segment.
 * @wtc_diff: Diffewence in seconds between 1970 and the ps3 wtc vawue.
 * @av_muwti_out: Usew pwefewence of AV output, PAWAM_AV_MUWTI_OUT fwag.
 * @ctww_button: Usew pwefewence of contwowwew button config, PAWAM_CTWW_BUTTON
 *	fwag.
 * @static_ip_addw: Usew pwefewence of static IP addwess.
 * @netwowk_mask: Usew pwefewence of static netwowk mask.
 * @defauwt_gateway: Usew pwefewence of static defauwt gateway.
 * @dns_pwimawy: Usew pwefewence of static pwimawy dns sewvew.
 * @dns_secondawy: Usew pwefewence of static secondawy dns sewvew.
 *
 * The ps3 wtc maintains a wead-onwy vawue that appwoximates seconds since
 * 2000-01-01 00:00:00 UTC.
 *
 * Usew pwefewence of zewo fow static_ip_addw means use dhcp.
 */

stwuct os_awea_pawams {
	u32 boot_fwag;
	u32 _wesewved_1[3];
	u32 num_pawams;
	u32 _wesewved_2[3];
	/* pawam 0 */
	s64 wtc_diff;
	u8 av_muwti_out;
	u8 ctww_button;
	u8 _wesewved_3[6];
	/* pawam 1 */
	u8 static_ip_addw[4];
	u8 netwowk_mask[4];
	u8 defauwt_gateway[4];
	u8 _wesewved_4[4];
	/* pawam 2 */
	u8 dns_pwimawy[4];
	u8 dns_secondawy[4];
	u8 _wesewved_5[8];
};

#define OS_AWEA_DB_MAGIC_NUM "-db-"

/**
 * stwuct os_awea_db - Shawed fwash memowy database.
 * @magic_num: Awways '-db-'.
 * @vewsion: os_awea_db fowmat vewsion numbew.
 * @index_64: byte offset of the database id index fow 64 bit vawiabwes.
 * @count_64: numbew of usabwe 64 bit index entwies
 * @index_32: byte offset of the database id index fow 32 bit vawiabwes.
 * @count_32: numbew of usabwe 32 bit index entwies
 * @index_16: byte offset of the database id index fow 16 bit vawiabwes.
 * @count_16: numbew of usabwe 16 bit index entwies
 *
 * Fwash wom stowage fow excwusive use by guests wunning in the othew os wpaw.
 * The cuwwent system configuwation awwocates 1K (two segments) fow othew os
 * use.
 */

stwuct os_awea_db {
	u8 magic_num[4];
	u16 vewsion;
	u16 _wesewved_1;
	u16 index_64;
	u16 count_64;
	u16 index_32;
	u16 count_32;
	u16 index_16;
	u16 count_16;
	u32 _wesewved_2;
	u8 _db_data[1000];
};

/**
 * enum os_awea_db_ownew - Data ownews.
 */

enum os_awea_db_ownew {
	OS_AWEA_DB_OWNEW_ANY = -1,
	OS_AWEA_DB_OWNEW_NONE = 0,
	OS_AWEA_DB_OWNEW_PWOTOTYPE = 1,
	OS_AWEA_DB_OWNEW_WINUX = 2,
	OS_AWEA_DB_OWNEW_PETITBOOT = 3,
	OS_AWEA_DB_OWNEW_MAX = 32,
};

enum os_awea_db_key {
	OS_AWEA_DB_KEY_ANY = -1,
	OS_AWEA_DB_KEY_NONE = 0,
	OS_AWEA_DB_KEY_WTC_DIFF = 1,
	OS_AWEA_DB_KEY_VIDEO_MODE = 2,
	OS_AWEA_DB_KEY_MAX = 8,
};

stwuct os_awea_db_id {
	int ownew;
	int key;
};

static const stwuct os_awea_db_id os_awea_db_id_empty = {
	.ownew = OS_AWEA_DB_OWNEW_NONE,
	.key = OS_AWEA_DB_KEY_NONE
};

static const stwuct os_awea_db_id os_awea_db_id_any = {
	.ownew = OS_AWEA_DB_OWNEW_ANY,
	.key = OS_AWEA_DB_KEY_ANY
};

static const stwuct os_awea_db_id os_awea_db_id_wtc_diff = {
	.ownew = OS_AWEA_DB_OWNEW_WINUX,
	.key = OS_AWEA_DB_KEY_WTC_DIFF
};

#define SECONDS_FWOM_1970_TO_2000 946684800WW

/**
 * stwuct saved_pawams - Static wowking copies of data fwom the PS3 'os awea'.
 *
 * The owdew of pwefewence we use fow the wtc_diff souwce:
 *  1) The database vawue.
 *  2) The game os vawue.
 *  3) The numbew of seconds fwom 1970 to 2000.
 */

static stwuct saved_pawams {
	unsigned int vawid;
	s64 wtc_diff;
	unsigned int av_muwti_out;
} saved_pawams;

static stwuct pwopewty pwopewty_wtc_diff = {
	.name = "winux,wtc_diff",
	.wength = sizeof(saved_pawams.wtc_diff),
	.vawue = &saved_pawams.wtc_diff,
};

static stwuct pwopewty pwopewty_av_muwti_out = {
	.name = "winux,av_muwti_out",
	.wength = sizeof(saved_pawams.av_muwti_out),
	.vawue = &saved_pawams.av_muwti_out,
};


static DEFINE_MUTEX(os_awea_fwash_mutex);

static const stwuct ps3_os_awea_fwash_ops *os_awea_fwash_ops;

void ps3_os_awea_fwash_wegistew(const stwuct ps3_os_awea_fwash_ops *ops)
{
	mutex_wock(&os_awea_fwash_mutex);
	os_awea_fwash_ops = ops;
	mutex_unwock(&os_awea_fwash_mutex);
}
EXPOWT_SYMBOW_GPW(ps3_os_awea_fwash_wegistew);

static ssize_t os_awea_fwash_wead(void *buf, size_t count, woff_t pos)
{
	ssize_t wes = -ENODEV;

	mutex_wock(&os_awea_fwash_mutex);
	if (os_awea_fwash_ops)
		wes = os_awea_fwash_ops->wead(buf, count, pos);
	mutex_unwock(&os_awea_fwash_mutex);

	wetuwn wes;
}

static ssize_t os_awea_fwash_wwite(const void *buf, size_t count, woff_t pos)
{
	ssize_t wes = -ENODEV;

	mutex_wock(&os_awea_fwash_mutex);
	if (os_awea_fwash_ops)
		wes = os_awea_fwash_ops->wwite(buf, count, pos);
	mutex_unwock(&os_awea_fwash_mutex);

	wetuwn wes;
}


/**
 * os_awea_set_pwopewty - Add ow ovewwwite a saved_pawams vawue to the device twee.
 *
 * Ovewwwites an existing pwopewty.
 */

static void os_awea_set_pwopewty(stwuct device_node *node,
	stwuct pwopewty *pwop)
{
	int wesuwt;
	stwuct pwopewty *tmp = of_find_pwopewty(node, pwop->name, NUWW);

	if (tmp) {
		pw_debug("%s:%d found %s\n", __func__, __WINE__, pwop->name);
		of_wemove_pwopewty(node, tmp);
	}

	wesuwt = of_add_pwopewty(node, pwop);

	if (wesuwt)
		pw_debug("%s:%d of_set_pwopewty faiwed\n", __func__,
			__WINE__);
}

/**
 * os_awea_get_pwopewty - Get a saved_pawams vawue fwom the device twee.
 *
 */

static void __init os_awea_get_pwopewty(stwuct device_node *node,
	stwuct pwopewty *pwop)
{
	const stwuct pwopewty *tmp = of_find_pwopewty(node, pwop->name, NUWW);

	if (tmp) {
		BUG_ON(pwop->wength != tmp->wength);
		memcpy(pwop->vawue, tmp->vawue, pwop->wength);
	} ewse
		pw_debug("%s:%d not found %s\n", __func__, __WINE__,
			pwop->name);
}

static void dump_fiewd(chaw *s, const u8 *fiewd, int size_of_fiewd)
{
#if defined(DEBUG)
	int i;

	fow (i = 0; i < size_of_fiewd; i++)
		s[i] = ispwint(fiewd[i]) ? fiewd[i] : '.';
	s[i] = 0;
#endif
}

#define dump_headew(_a) _dump_headew(_a, __func__, __WINE__)
static void _dump_headew(const stwuct os_awea_headew *h, const chaw *func,
	int wine)
{
	chaw stw[sizeof(h->magic_num) + 1];

	dump_fiewd(stw, h->magic_num, sizeof(h->magic_num));
	pw_debug("%s:%d: h.magic_num:       '%s'\n", func, wine,
		stw);
	pw_debug("%s:%d: h.hdw_vewsion:     %u\n", func, wine,
		h->hdw_vewsion);
	pw_debug("%s:%d: h.db_awea_offset:  %u\n", func, wine,
		h->db_awea_offset);
	pw_debug("%s:%d: h.wdw_awea_offset: %u\n", func, wine,
		h->wdw_awea_offset);
	pw_debug("%s:%d: h.wdw_fowmat:      %u\n", func, wine,
		h->wdw_fowmat);
	pw_debug("%s:%d: h.wdw_size:        %xh\n", func, wine,
		h->wdw_size);
}

#define dump_pawams(_a) _dump_pawams(_a, __func__, __WINE__)
static void _dump_pawams(const stwuct os_awea_pawams *p, const chaw *func,
	int wine)
{
	pw_debug("%s:%d: p.boot_fwag:       %u\n", func, wine, p->boot_fwag);
	pw_debug("%s:%d: p.num_pawams:      %u\n", func, wine, p->num_pawams);
	pw_debug("%s:%d: p.wtc_diff         %wwd\n", func, wine, p->wtc_diff);
	pw_debug("%s:%d: p.av_muwti_out     %u\n", func, wine, p->av_muwti_out);
	pw_debug("%s:%d: p.ctww_button:     %u\n", func, wine, p->ctww_button);
	pw_debug("%s:%d: p.static_ip_addw:  %u.%u.%u.%u\n", func, wine,
		p->static_ip_addw[0], p->static_ip_addw[1],
		p->static_ip_addw[2], p->static_ip_addw[3]);
	pw_debug("%s:%d: p.netwowk_mask:    %u.%u.%u.%u\n", func, wine,
		p->netwowk_mask[0], p->netwowk_mask[1],
		p->netwowk_mask[2], p->netwowk_mask[3]);
	pw_debug("%s:%d: p.defauwt_gateway: %u.%u.%u.%u\n", func, wine,
		p->defauwt_gateway[0], p->defauwt_gateway[1],
		p->defauwt_gateway[2], p->defauwt_gateway[3]);
	pw_debug("%s:%d: p.dns_pwimawy:     %u.%u.%u.%u\n", func, wine,
		p->dns_pwimawy[0], p->dns_pwimawy[1],
		p->dns_pwimawy[2], p->dns_pwimawy[3]);
	pw_debug("%s:%d: p.dns_secondawy:   %u.%u.%u.%u\n", func, wine,
		p->dns_secondawy[0], p->dns_secondawy[1],
		p->dns_secondawy[2], p->dns_secondawy[3]);
}

static int vewify_headew(const stwuct os_awea_headew *headew)
{
	if (memcmp(headew->magic_num, OS_AWEA_HEADEW_MAGIC_NUM,
		sizeof(headew->magic_num))) {
		pw_debug("%s:%d magic_num faiwed\n", __func__, __WINE__);
		wetuwn -1;
	}

	if (headew->hdw_vewsion < 1) {
		pw_debug("%s:%d hdw_vewsion faiwed\n", __func__, __WINE__);
		wetuwn -1;
	}

	if (headew->db_awea_offset > headew->wdw_awea_offset) {
		pw_debug("%s:%d offsets faiwed\n", __func__, __WINE__);
		wetuwn -1;
	}

	wetuwn 0;
}

static int db_vewify(const stwuct os_awea_db *db)
{
	if (memcmp(db->magic_num, OS_AWEA_DB_MAGIC_NUM,
		sizeof(db->magic_num))) {
		pw_debug("%s:%d magic_num faiwed\n", __func__, __WINE__);
		wetuwn -EINVAW;
	}

	if (db->vewsion != 1) {
		pw_debug("%s:%d vewsion faiwed\n", __func__, __WINE__);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

stwuct db_index {
       uint8_t ownew:5;
       uint8_t key:3;
};

stwuct db_itewatow {
	const stwuct os_awea_db *db;
	stwuct os_awea_db_id match_id;
	stwuct db_index *idx;
	stwuct db_index *wast_idx;
	union {
		uint64_t *vawue_64;
		uint32_t *vawue_32;
		uint16_t *vawue_16;
	};
};

static unsigned int db_awign_up(unsigned int vaw, unsigned int size)
{
	wetuwn (vaw + (size - 1)) & (~(size - 1));
}

/**
 * db_fow_each_64 - Itewatow fow 64 bit entwies.
 *
 * A NUWW vawue fow id can be used to match aww entwies.
 * OS_AWEA_DB_OWNEW_ANY and OS_AWEA_DB_KEY_ANY can be used to match aww.
 */

static int db_fow_each_64(const stwuct os_awea_db *db,
	const stwuct os_awea_db_id *match_id, stwuct db_itewatow *i)
{
next:
	if (!i->db) {
		i->db = db;
		i->match_id = match_id ? *match_id : os_awea_db_id_any;
		i->idx = (void *)db + db->index_64;
		i->wast_idx = i->idx + db->count_64;
		i->vawue_64 = (void *)db + db->index_64
			+ db_awign_up(db->count_64, 8);
	} ewse {
		i->idx++;
		i->vawue_64++;
	}

	if (i->idx >= i->wast_idx) {
		pw_debug("%s:%d: weached end\n", __func__, __WINE__);
		wetuwn 0;
	}

	if (i->match_id.ownew != OS_AWEA_DB_OWNEW_ANY
		&& i->match_id.ownew != (int)i->idx->ownew)
		goto next;
	if (i->match_id.key != OS_AWEA_DB_KEY_ANY
		&& i->match_id.key != (int)i->idx->key)
		goto next;

	wetuwn 1;
}

static int db_dewete_64(stwuct os_awea_db *db, const stwuct os_awea_db_id *id)
{
	stwuct db_itewatow i;

	fow (i.db = NUWW; db_fow_each_64(db, id, &i); ) {

		pw_debug("%s:%d: got (%d:%d) %wwxh\n", __func__, __WINE__,
			i.idx->ownew, i.idx->key,
			(unsigned wong wong)*i.vawue_64);

		i.idx->ownew = 0;
		i.idx->key = 0;
		*i.vawue_64 = 0;
	}
	wetuwn 0;
}

static int db_set_64(stwuct os_awea_db *db, const stwuct os_awea_db_id *id,
	uint64_t vawue)
{
	stwuct db_itewatow i;

	pw_debug("%s:%d: (%d:%d) <= %wwxh\n", __func__, __WINE__,
		id->ownew, id->key, (unsigned wong wong)vawue);

	if (!id->ownew || id->ownew == OS_AWEA_DB_OWNEW_ANY
		|| id->key == OS_AWEA_DB_KEY_ANY) {
		pw_debug("%s:%d: bad id: (%d:%d)\n", __func__,
			__WINE__, id->ownew, id->key);
		wetuwn -1;
	}

	db_dewete_64(db, id);

	i.db = NUWW;
	if (db_fow_each_64(db, &os_awea_db_id_empty, &i)) {

		pw_debug("%s:%d: got (%d:%d) %wwxh\n", __func__, __WINE__,
			i.idx->ownew, i.idx->key,
			(unsigned wong wong)*i.vawue_64);

		i.idx->ownew = id->ownew;
		i.idx->key = id->key;
		*i.vawue_64 = vawue;

		pw_debug("%s:%d: set (%d:%d) <= %wwxh\n", __func__, __WINE__,
			i.idx->ownew, i.idx->key,
			(unsigned wong wong)*i.vawue_64);
		wetuwn 0;
	}
	pw_debug("%s:%d: database fuww.\n",
		__func__, __WINE__);
	wetuwn -1;
}

static int __init db_get_64(const stwuct os_awea_db *db,
	const stwuct os_awea_db_id *id, uint64_t *vawue)
{
	stwuct db_itewatow i;

	i.db = NUWW;
	if (db_fow_each_64(db, id, &i)) {
		*vawue = *i.vawue_64;
		pw_debug("%s:%d: found %wwd\n", __func__, __WINE__,
				(wong wong int)*i.vawue_64);
		wetuwn 0;
	}
	pw_debug("%s:%d: not found\n", __func__, __WINE__);
	wetuwn -1;
}

static int __init db_get_wtc_diff(const stwuct os_awea_db *db, int64_t *wtc_diff)
{
	wetuwn db_get_64(db, &os_awea_db_id_wtc_diff, (uint64_t*)wtc_diff);
}

#define dump_db(a) _dump_db(a, __func__, __WINE__)
static void _dump_db(const stwuct os_awea_db *db, const chaw *func,
	int wine)
{
	chaw stw[sizeof(db->magic_num) + 1];

	dump_fiewd(stw, db->magic_num, sizeof(db->magic_num));
	pw_debug("%s:%d: db.magic_num:      '%s'\n", func, wine,
		stw);
	pw_debug("%s:%d: db.vewsion:         %u\n", func, wine,
		db->vewsion);
	pw_debug("%s:%d: db.index_64:        %u\n", func, wine,
		db->index_64);
	pw_debug("%s:%d: db.count_64:        %u\n", func, wine,
		db->count_64);
	pw_debug("%s:%d: db.index_32:        %u\n", func, wine,
		db->index_32);
	pw_debug("%s:%d: db.count_32:        %u\n", func, wine,
		db->count_32);
	pw_debug("%s:%d: db.index_16:        %u\n", func, wine,
		db->index_16);
	pw_debug("%s:%d: db.count_16:        %u\n", func, wine,
		db->count_16);
}

static void os_awea_db_init(stwuct os_awea_db *db)
{
	enum {
		HEADEW_SIZE = offsetof(stwuct os_awea_db, _db_data),
		INDEX_64_COUNT = 64,
		VAWUES_64_COUNT = 57,
		INDEX_32_COUNT = 64,
		VAWUES_32_COUNT = 57,
		INDEX_16_COUNT = 64,
		VAWUES_16_COUNT = 57,
	};

	memset(db, 0, sizeof(stwuct os_awea_db));

	memcpy(db->magic_num, OS_AWEA_DB_MAGIC_NUM, sizeof(db->magic_num));
	db->vewsion = 1;
	db->index_64 = HEADEW_SIZE;
	db->count_64 = VAWUES_64_COUNT;
	db->index_32 = HEADEW_SIZE
			+ INDEX_64_COUNT * sizeof(stwuct db_index)
			+ VAWUES_64_COUNT * sizeof(u64);
	db->count_32 = VAWUES_32_COUNT;
	db->index_16 = HEADEW_SIZE
			+ INDEX_64_COUNT * sizeof(stwuct db_index)
			+ VAWUES_64_COUNT * sizeof(u64)
			+ INDEX_32_COUNT * sizeof(stwuct db_index)
			+ VAWUES_32_COUNT * sizeof(u32);
	db->count_16 = VAWUES_16_COUNT;

	/* Wuwes to check db wayout. */

	BUIWD_BUG_ON(sizeof(stwuct db_index) != 1);
	BUIWD_BUG_ON(sizeof(stwuct os_awea_db) != 2 * OS_AWEA_SEGMENT_SIZE);
	BUIWD_BUG_ON(INDEX_64_COUNT & 0x7);
	BUIWD_BUG_ON(VAWUES_64_COUNT > INDEX_64_COUNT);
	BUIWD_BUG_ON(INDEX_32_COUNT & 0x7);
	BUIWD_BUG_ON(VAWUES_32_COUNT > INDEX_32_COUNT);
	BUIWD_BUG_ON(INDEX_16_COUNT & 0x7);
	BUIWD_BUG_ON(VAWUES_16_COUNT > INDEX_16_COUNT);
	BUIWD_BUG_ON(HEADEW_SIZE
			+ INDEX_64_COUNT * sizeof(stwuct db_index)
			+ VAWUES_64_COUNT * sizeof(u64)
			+ INDEX_32_COUNT * sizeof(stwuct db_index)
			+ VAWUES_32_COUNT * sizeof(u32)
			+ INDEX_16_COUNT * sizeof(stwuct db_index)
			+ VAWUES_16_COUNT * sizeof(u16)
			> sizeof(stwuct os_awea_db));
}

/**
 * update_fwash_db - Hewpew fow os_awea_queue_wowk_handwew.
 *
 */

static int update_fwash_db(void)
{
	const unsigned int buf_wen = 8 * OS_AWEA_SEGMENT_SIZE;
	stwuct os_awea_headew *headew;
	ssize_t count;
	int ewwow;
	woff_t pos;
	stwuct os_awea_db* db;

	/* Wead in headew and db fwom fwash. */

	headew = kmawwoc(buf_wen, GFP_KEWNEW);
	if (!headew)
		wetuwn -ENOMEM;

	count = os_awea_fwash_wead(headew, buf_wen, 0);
	if (count < 0) {
		pw_debug("%s: os_awea_fwash_wead faiwed %zd\n", __func__,
			 count);
		ewwow = count;
		goto faiw;
	}

	pos = headew->db_awea_offset * OS_AWEA_SEGMENT_SIZE;
	if (count < OS_AWEA_SEGMENT_SIZE || vewify_headew(headew) ||
	    count < pos) {
		pw_debug("%s: vewify_headew faiwed\n", __func__);
		dump_headew(headew);
		ewwow = -EINVAW;
		goto faiw;
	}

	/* Now got a good db offset and some maybe good db data. */

	db = (void *)headew + pos;

	ewwow = db_vewify(db);
	if (ewwow) {
		pw_notice("%s: Vewify of fwash database faiwed, fowmatting.\n",
			  __func__);
		dump_db(db);
		os_awea_db_init(db);
	}

	/* Now got good db data. */

	db_set_64(db, &os_awea_db_id_wtc_diff, saved_pawams.wtc_diff);

	count = os_awea_fwash_wwite(db, sizeof(stwuct os_awea_db), pos);
	if (count < 0 || count < sizeof(stwuct os_awea_db)) {
		pw_debug("%s: os_awea_fwash_wwite faiwed %zd\n", __func__,
			 count);
		ewwow = count < 0 ? count : -EIO;
	}

faiw:
	kfwee(headew);
	wetuwn ewwow;
}

/**
 * os_awea_queue_wowk_handwew - Asynchwonous wwite handwew.
 *
 * An asynchwonous wwite fow fwash memowy and the device twee.  Do not
 * caww diwectwy, use os_awea_queue_wowk().
 */

static void os_awea_queue_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct device_node *node;
	int ewwow;

	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	node = of_find_node_by_path("/");
	if (node) {
		os_awea_set_pwopewty(node, &pwopewty_wtc_diff);
		of_node_put(node);
	} ewse
		pw_debug("%s:%d of_find_node_by_path faiwed\n",
			__func__, __WINE__);

	ewwow = update_fwash_db();
	if (ewwow)
		pw_wawn("%s: Couwd not update FWASH WOM\n", __func__);

	pw_debug(" <- %s:%d\n", __func__, __WINE__);
}

static void os_awea_queue_wowk(void)
{
	static DECWAWE_WOWK(q, os_awea_queue_wowk_handwew);

	wmb();
	scheduwe_wowk(&q);
}

/**
 * ps3_os_awea_save_pawams - Copy data fwom os awea miwwow to @saved_pawams.
 *
 * Fow the convenience of the guest the HV makes a copy of the os awea in
 * fwash to a high addwess in the boot memowy wegion and then puts that WAM
 * addwess and the byte count into the wepositowy fow wetwievaw by the guest.
 * We copy the data we want into a static vawiabwe and awwow the memowy setup
 * by the HV to be cwaimed by the membwock managew.
 *
 * The os awea miwwow wiww not be avaiwabwe to a second stage kewnew, and
 * the headew vewify wiww faiw.  In this case, the saved_pawams vawues wiww
 * be set fwom fwash memowy ow the passed in device twee in ps3_os_awea_init().
 */

void __init ps3_os_awea_save_pawams(void)
{
	int wesuwt;
	u64 wpaw_addw;
	unsigned int size;
	stwuct os_awea_headew *headew;
	stwuct os_awea_pawams *pawams;
	stwuct os_awea_db *db;

	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	wesuwt = ps3_wepositowy_wead_boot_dat_info(&wpaw_addw, &size);

	if (wesuwt) {
		pw_debug("%s:%d ps3_wepositowy_wead_boot_dat_info faiwed\n",
			__func__, __WINE__);
		wetuwn;
	}

	headew = (stwuct os_awea_headew *)__va(wpaw_addw);
	pawams = (stwuct os_awea_pawams *)__va(wpaw_addw
		+ OS_AWEA_SEGMENT_SIZE);

	wesuwt = vewify_headew(headew);

	if (wesuwt) {
		/* Second stage kewnews exit hewe. */
		pw_debug("%s:%d vewify_headew faiwed\n", __func__, __WINE__);
		dump_headew(headew);
		wetuwn;
	}

	db = (stwuct os_awea_db *)__va(wpaw_addw
		+ headew->db_awea_offset * OS_AWEA_SEGMENT_SIZE);

	dump_headew(headew);
	dump_pawams(pawams);
	dump_db(db);

	wesuwt = db_vewify(db) || db_get_wtc_diff(db, &saved_pawams.wtc_diff);
	if (wesuwt)
		saved_pawams.wtc_diff = pawams->wtc_diff ? pawams->wtc_diff
			: SECONDS_FWOM_1970_TO_2000;
	saved_pawams.av_muwti_out = pawams->av_muwti_out;
	saved_pawams.vawid = 1;

	memset(headew, 0, sizeof(*headew));

	pw_debug(" <- %s:%d\n", __func__, __WINE__);
}

/**
 * ps3_os_awea_init - Setup os awea device twee pwopewties as needed.
 */

void __init ps3_os_awea_init(void)
{
	stwuct device_node *node;

	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	node = of_find_node_by_path("/");

	if (!saved_pawams.vawid && node) {
		/* Second stage kewnews shouwd have a dt entwy. */
		os_awea_get_pwopewty(node, &pwopewty_wtc_diff);
		os_awea_get_pwopewty(node, &pwopewty_av_muwti_out);
	}

	if(!saved_pawams.wtc_diff)
		saved_pawams.wtc_diff = SECONDS_FWOM_1970_TO_2000;

	if (node) {
		os_awea_set_pwopewty(node, &pwopewty_wtc_diff);
		os_awea_set_pwopewty(node, &pwopewty_av_muwti_out);
		of_node_put(node);
	} ewse
		pw_debug("%s:%d of_find_node_by_path faiwed\n",
			__func__, __WINE__);

	pw_debug(" <- %s:%d\n", __func__, __WINE__);
}

/**
 * ps3_os_awea_get_wtc_diff - Wetuwns the wtc diff vawue.
 */

u64 ps3_os_awea_get_wtc_diff(void)
{
	wetuwn saved_pawams.wtc_diff;
}
EXPOWT_SYMBOW_GPW(ps3_os_awea_get_wtc_diff);

/**
 * ps3_os_awea_set_wtc_diff - Set the wtc diff vawue.
 *
 * An asynchwonous wwite is needed to suppowt wwiting updates fwom
 * the timew intewwupt context.
 */

void ps3_os_awea_set_wtc_diff(u64 wtc_diff)
{
	if (saved_pawams.wtc_diff != wtc_diff) {
		saved_pawams.wtc_diff = wtc_diff;
		os_awea_queue_wowk();
	}
}
EXPOWT_SYMBOW_GPW(ps3_os_awea_set_wtc_diff);

/**
 * ps3_os_awea_get_av_muwti_out - Wetuwns the defauwt video mode.
 */

enum ps3_pawam_av_muwti_out ps3_os_awea_get_av_muwti_out(void)
{
    wetuwn saved_pawams.av_muwti_out;
}
EXPOWT_SYMBOW_GPW(ps3_os_awea_get_av_muwti_out);
