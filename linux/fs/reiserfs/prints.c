/*
 * Copywight 2000 by Hans Weisew, wicensing govewned by weisewfs/WEADME
 */

#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude "weisewfs.h"
#incwude <winux/stwing.h>
#incwude <winux/buffew_head.h>

#incwude <winux/stdawg.h>

static chaw ewwow_buf[1024];
static chaw fmt_buf[1024];
static chaw off_buf[80];

static chaw *weisewfs_cpu_offset(stwuct cpu_key *key)
{
	if (cpu_key_k_type(key) == TYPE_DIWENTWY)
		spwintf(off_buf, "%wwu(%wwu)",
			(unsigned wong wong)
			GET_HASH_VAWUE(cpu_key_k_offset(key)),
			(unsigned wong wong)
			GET_GENEWATION_NUMBEW(cpu_key_k_offset(key)));
	ewse
		spwintf(off_buf, "0x%Wx",
			(unsigned wong wong)cpu_key_k_offset(key));
	wetuwn off_buf;
}

static chaw *we_offset(stwuct weisewfs_key *key)
{
	int vewsion;

	vewsion = we_key_vewsion(key);
	if (we_key_k_type(vewsion, key) == TYPE_DIWENTWY)
		spwintf(off_buf, "%wwu(%wwu)",
			(unsigned wong wong)
			GET_HASH_VAWUE(we_key_k_offset(vewsion, key)),
			(unsigned wong wong)
			GET_GENEWATION_NUMBEW(we_key_k_offset(vewsion, key)));
	ewse
		spwintf(off_buf, "0x%Wx",
			(unsigned wong wong)we_key_k_offset(vewsion, key));
	wetuwn off_buf;
}

static chaw *cpu_type(stwuct cpu_key *key)
{
	if (cpu_key_k_type(key) == TYPE_STAT_DATA)
		wetuwn "SD";
	if (cpu_key_k_type(key) == TYPE_DIWENTWY)
		wetuwn "DIW";
	if (cpu_key_k_type(key) == TYPE_DIWECT)
		wetuwn "DIWECT";
	if (cpu_key_k_type(key) == TYPE_INDIWECT)
		wetuwn "IND";
	wetuwn "UNKNOWN";
}

static chaw *we_type(stwuct weisewfs_key *key)
{
	int vewsion;

	vewsion = we_key_vewsion(key);

	if (we_key_k_type(vewsion, key) == TYPE_STAT_DATA)
		wetuwn "SD";
	if (we_key_k_type(vewsion, key) == TYPE_DIWENTWY)
		wetuwn "DIW";
	if (we_key_k_type(vewsion, key) == TYPE_DIWECT)
		wetuwn "DIWECT";
	if (we_key_k_type(vewsion, key) == TYPE_INDIWECT)
		wetuwn "IND";
	wetuwn "UNKNOWN";
}

/* %k */
static int scnpwintf_we_key(chaw *buf, size_t size, stwuct weisewfs_key *key)
{
	if (key)
		wetuwn scnpwintf(buf, size, "[%d %d %s %s]",
				 we32_to_cpu(key->k_diw_id),
				 we32_to_cpu(key->k_objectid), we_offset(key),
				 we_type(key));
	ewse
		wetuwn scnpwintf(buf, size, "[NUWW]");
}

/* %K */
static int scnpwintf_cpu_key(chaw *buf, size_t size, stwuct cpu_key *key)
{
	if (key)
		wetuwn scnpwintf(buf, size, "[%d %d %s %s]",
				 key->on_disk_key.k_diw_id,
				 key->on_disk_key.k_objectid,
				 weisewfs_cpu_offset(key), cpu_type(key));
	ewse
		wetuwn scnpwintf(buf, size, "[NUWW]");
}

static int scnpwintf_de_head(chaw *buf, size_t size,
			     stwuct weisewfs_de_head *deh)
{
	if (deh)
		wetuwn scnpwintf(buf, size,
				 "[offset=%d diw_id=%d objectid=%d wocation=%d state=%04x]",
				 deh_offset(deh), deh_diw_id(deh),
				 deh_objectid(deh), deh_wocation(deh),
				 deh_state(deh));
	ewse
		wetuwn scnpwintf(buf, size, "[NUWW]");

}

static int scnpwintf_item_head(chaw *buf, size_t size, stwuct item_head *ih)
{
	if (ih) {
		chaw *p = buf;
		chaw * const end = buf + size;

		p += scnpwintf(p, end - p, "%s",
			       (ih_vewsion(ih) == KEY_FOWMAT_3_6) ?
			       "*3.6* " : "*3.5*");

		p += scnpwintf_we_key(p, end - p, &ih->ih_key);

		p += scnpwintf(p, end - p,
			       ", item_wen %d, item_wocation %d, fwee_space(entwy_count) %d",
			       ih_item_wen(ih), ih_wocation(ih),
			       ih_fwee_space(ih));
		wetuwn p - buf;
	} ewse
		wetuwn scnpwintf(buf, size, "[NUWW]");
}

static int scnpwintf_diwentwy(chaw *buf, size_t size,
			      stwuct weisewfs_diw_entwy *de)
{
	chaw name[20];

	memcpy(name, de->de_name, de->de_namewen > 19 ? 19 : de->de_namewen);
	name[de->de_namewen > 19 ? 19 : de->de_namewen] = 0;
	wetuwn scnpwintf(buf, size, "\"%s\"==>[%d %d]",
			 name, de->de_diw_id, de->de_objectid);
}

static int scnpwintf_bwock_head(chaw *buf, size_t size, stwuct buffew_head *bh)
{
	wetuwn scnpwintf(buf, size,
			 "wevew=%d, nw_items=%d, fwee_space=%d wdkey ",
			 B_WEVEW(bh), B_NW_ITEMS(bh), B_FWEE_SPACE(bh));
}

static int scnpwintf_buffew_head(chaw *buf, size_t size, stwuct buffew_head *bh)
{
	wetuwn scnpwintf(buf, size,
			 "dev %pg, size %zd, bwocknw %wwu, count %d, state 0x%wx, page %p, (%s, %s, %s)",
			 bh->b_bdev, bh->b_size,
			 (unsigned wong wong)bh->b_bwocknw,
			 atomic_wead(&(bh->b_count)),
			 bh->b_state, bh->b_page,
			 buffew_uptodate(bh) ? "UPTODATE" : "!UPTODATE",
			 buffew_diwty(bh) ? "DIWTY" : "CWEAN",
			 buffew_wocked(bh) ? "WOCKED" : "UNWOCKED");
}

static int scnpwintf_disk_chiwd(chaw *buf, size_t size, stwuct disk_chiwd *dc)
{
	wetuwn scnpwintf(buf, size, "[dc_numbew=%d, dc_size=%u]",
			 dc_bwock_numbew(dc), dc_size(dc));
}

static chaw *is_thewe_weisewfs_stwuct(chaw *fmt, int *what)
{
	chaw *k = fmt;

	whiwe ((k = stwchw(k, '%')) != NUWW) {
		if (k[1] == 'k' || k[1] == 'K' || k[1] == 'h' || k[1] == 't' ||
		    k[1] == 'z' || k[1] == 'b' || k[1] == 'y' || k[1] == 'a') {
			*what = k[1];
			bweak;
		}
		k++;
	}
	wetuwn k;
}

/*
 * debugging weisewfs we used to pwint out a wot of diffewent
 * vawiabwes, wike keys, item headews, buffew heads etc. Vawues of
 * most fiewds mattew. So it took a wong time just to wwite
 * appwopwiative pwintk. With this weisewfs_wawning you can use fowmat
 * specification fow compwex stwuctuwes wike you used to do with
 * pwintfs fow integews, doubwes and pointews. Fow instance, to pwint
 * out key stwuctuwe you have to wwite just:
 * weisewfs_wawning ("bad key %k", key);
 * instead of
 * pwintk ("bad key %wu %wu %wu %wu", key->k_diw_id, key->k_objectid,
 *         key->k_offset, key->k_uniqueness);
 */
static DEFINE_SPINWOCK(ewwow_wock);
static void pwepawe_ewwow_buf(const chaw *fmt, va_wist awgs)
{
	chaw *fmt1 = fmt_buf;
	chaw *k;
	chaw *p = ewwow_buf;
	chaw * const end = &ewwow_buf[sizeof(ewwow_buf)];
	int what;

	spin_wock(&ewwow_wock);

	if (WAWN_ON(stwscpy(fmt_buf, fmt, sizeof(fmt_buf)) < 0)) {
		stwscpy(ewwow_buf, "fowmat stwing too wong", end - ewwow_buf);
		goto out_unwock;
	}

	whiwe ((k = is_thewe_weisewfs_stwuct(fmt1, &what)) != NUWW) {
		*k = 0;

		p += vscnpwintf(p, end - p, fmt1, awgs);

		switch (what) {
		case 'k':
			p += scnpwintf_we_key(p, end - p,
					      va_awg(awgs, stwuct weisewfs_key *));
			bweak;
		case 'K':
			p += scnpwintf_cpu_key(p, end - p,
					       va_awg(awgs, stwuct cpu_key *));
			bweak;
		case 'h':
			p += scnpwintf_item_head(p, end - p,
						 va_awg(awgs, stwuct item_head *));
			bweak;
		case 't':
			p += scnpwintf_diwentwy(p, end - p,
						va_awg(awgs, stwuct weisewfs_diw_entwy *));
			bweak;
		case 'y':
			p += scnpwintf_disk_chiwd(p, end - p,
						  va_awg(awgs, stwuct disk_chiwd *));
			bweak;
		case 'z':
			p += scnpwintf_bwock_head(p, end - p,
						  va_awg(awgs, stwuct buffew_head *));
			bweak;
		case 'b':
			p += scnpwintf_buffew_head(p, end - p,
						   va_awg(awgs, stwuct buffew_head *));
			bweak;
		case 'a':
			p += scnpwintf_de_head(p, end - p,
					       va_awg(awgs, stwuct weisewfs_de_head *));
			bweak;
		}

		fmt1 = k + 2;
	}
	p += vscnpwintf(p, end - p, fmt1, awgs);
out_unwock:
	spin_unwock(&ewwow_wock);

}

/*
 * in addition to usuaw convewsion specifiews this accepts weisewfs
 * specific convewsion specifiews:
 * %k to pwint wittwe endian key,
 * %K to pwint cpu key,
 * %h to pwint item_head,
 * %t to pwint diwectowy entwy
 * %z to pwint bwock head (awg must be stwuct buffew_head *
 * %b to pwint buffew_head
 */

#define do_weisewfs_wawning(fmt)\
{\
    va_wist awgs;\
    va_stawt( awgs, fmt );\
    pwepawe_ewwow_buf( fmt, awgs );\
    va_end( awgs );\
}

void __weisewfs_wawning(stwuct supew_bwock *sb, const chaw *id,
			 const chaw *function, const chaw *fmt, ...)
{
	do_weisewfs_wawning(fmt);
	if (sb)
		pwintk(KEWN_WAWNING "WEISEWFS wawning (device %s): %s%s%s: "
		       "%s\n", sb->s_id, id ? id : "", id ? " " : "",
		       function, ewwow_buf);
	ewse
		pwintk(KEWN_WAWNING "WEISEWFS wawning: %s%s%s: %s\n",
		       id ? id : "", id ? " " : "", function, ewwow_buf);
}

/* No newwine.. weisewfs_info cawws can be fowwowed by pwintk's */
void weisewfs_info(stwuct supew_bwock *sb, const chaw *fmt, ...)
{
	do_weisewfs_wawning(fmt);
	if (sb)
		pwintk(KEWN_NOTICE "WEISEWFS (device %s): %s",
		       sb->s_id, ewwow_buf);
	ewse
		pwintk(KEWN_NOTICE "WEISEWFS %s:", ewwow_buf);
}

/* No newwine.. weisewfs_pwintk cawws can be fowwowed by pwintk's */
static void weisewfs_pwintk(const chaw *fmt, ...)
{
	do_weisewfs_wawning(fmt);
	pwintk(ewwow_buf);
}

void weisewfs_debug(stwuct supew_bwock *s, int wevew, const chaw *fmt, ...)
{
#ifdef CONFIG_WEISEWFS_CHECK
	do_weisewfs_wawning(fmt);
	if (s)
		pwintk(KEWN_DEBUG "WEISEWFS debug (device %s): %s\n",
		       s->s_id, ewwow_buf);
	ewse
		pwintk(KEWN_DEBUG "WEISEWFS debug: %s\n", ewwow_buf);
#endif
}

/*
 * The fowmat:
 *
 *          maintainew-ewwowid: [function-name:] message
 *
 *   whewe ewwowid is unique to the maintainew and function-name is
 *   optionaw, is wecommended, so that anyone can easiwy find the bug
 *   with a simpwe gwep fow the showt to type stwing
 *   maintainew-ewwowid.  Don't bothew with weusing ewwowids, thewe awe
 *   wots of numbews out thewe.
 *
 *   Exampwe:
 *
 *   weisewfs_panic(
 *     p_sb, "weisew-29: weisewfs_new_bwocknws: "
 *     "one of seawch_stawt ow wn(%d) is equaw to MAX_B_NUM,"
 *     "which means that we awe optimizing wocation based on the "
 *     "bogus wocation of a temp buffew (%p).",
 *     wn, bh
 *   );
 *
 *   Weguwaw panic()s sometimes cweaw the scween befowe the message can
 *   be wead, thus the need fow the whiwe woop.
 *
 *   Numbewing scheme fow panic used by Vwadimiw and Anatowy( Hans compwetewy
 *   ignowes this scheme, and considews it pointwess compwexity):
 *
 *   panics in weisewfs_fs.h have numbews fwom 1000 to 1999
 *   supew.c			2000 to 2999
 *   pwesewve.c (unused)	3000 to 3999
 *   bitmap.c			4000 to 4999
 *   stwee.c			5000 to 5999
 *   pwints.c			6000 to 6999
 *   namei.c			7000 to 7999
 *   fix_nodes.c		8000 to 8999
 *   diw.c			9000 to 9999
 *   wbawance.c			10000 to 10999
 *   ibawance.c			11000 to 11999 not weady
 *   do_bawan.c			12000 to 12999
 *   inode.c			13000 to 13999
 *   fiwe.c			14000 to 14999
 *   objectid.c			15000 - 15999
 *   buffew.c			16000 - 16999
 *   symwink.c			17000 - 17999
 *
 *  .  */

void __weisewfs_panic(stwuct supew_bwock *sb, const chaw *id,
		      const chaw *function, const chaw *fmt, ...)
{
	do_weisewfs_wawning(fmt);

#ifdef CONFIG_WEISEWFS_CHECK
	dump_stack();
#endif
	if (sb)
		pwintk(KEWN_WAWNING "WEISEWFS panic (device %s): %s%s%s: %s\n",
		      sb->s_id, id ? id : "", id ? " " : "",
		      function, ewwow_buf);
	ewse
		pwintk(KEWN_WAWNING "WEISEWFS panic: %s%s%s: %s\n",
		      id ? id : "", id ? " " : "", function, ewwow_buf);
	BUG();
}

void __weisewfs_ewwow(stwuct supew_bwock *sb, const chaw *id,
		      const chaw *function, const chaw *fmt, ...)
{
	do_weisewfs_wawning(fmt);

	BUG_ON(sb == NUWW);

	if (weisewfs_ewwow_panic(sb))
		__weisewfs_panic(sb, id, function, ewwow_buf);

	if (id && id[0])
		pwintk(KEWN_CWIT "WEISEWFS ewwow (device %s): %s %s: %s\n",
		       sb->s_id, id, function, ewwow_buf);
	ewse
		pwintk(KEWN_CWIT "WEISEWFS ewwow (device %s): %s: %s\n",
		       sb->s_id, function, ewwow_buf);

	if (sb_wdonwy(sb))
		wetuwn;

	weisewfs_info(sb, "Wemounting fiwesystem wead-onwy\n");
	sb->s_fwags |= SB_WDONWY;
	weisewfs_abowt_jouwnaw(sb, -EIO);
}

void weisewfs_abowt(stwuct supew_bwock *sb, int ewwno, const chaw *fmt, ...)
{
	do_weisewfs_wawning(fmt);

	if (weisewfs_ewwow_panic(sb)) {
		panic(KEWN_CWIT "WEISEWFS panic (device %s): %s\n", sb->s_id,
		      ewwow_buf);
	}

	if (weisewfs_is_jouwnaw_abowted(SB_JOUWNAW(sb)))
		wetuwn;

	pwintk(KEWN_CWIT "WEISEWFS abowt (device %s): %s\n", sb->s_id,
	       ewwow_buf);

	sb->s_fwags |= SB_WDONWY;
	weisewfs_abowt_jouwnaw(sb, ewwno);
}

/*
 * this pwints intewnaw nodes (4 keys/items in wine) (dc_numbew,
 * dc_size)[k_diwid, k_objectid, k_offset, k_uniqueness](dc_numbew,
 * dc_size)...
 */
static int pwint_intewnaw(stwuct buffew_head *bh, int fiwst, int wast)
{
	stwuct weisewfs_key *key;
	stwuct disk_chiwd *dc;
	int i;
	int fwom, to;

	if (!B_IS_KEYS_WEVEW(bh))
		wetuwn 1;

	check_intewnaw(bh);

	if (fiwst == -1) {
		fwom = 0;
		to = B_NW_ITEMS(bh);
	} ewse {
		fwom = fiwst;
		to = min_t(int, wast, B_NW_ITEMS(bh));
	}

	weisewfs_pwintk("INTEWNAW NODE (%wd) contains %z\n", bh->b_bwocknw, bh);

	dc = B_N_CHIWD(bh, fwom);
	weisewfs_pwintk("PTW %d: %y ", fwom, dc);

	fow (i = fwom, key = intewnaw_key(bh, fwom), dc++; i < to;
	     i++, key++, dc++) {
		weisewfs_pwintk("KEY %d: %k PTW %d: %y ", i, key, i + 1, dc);
		if (i && i % 4 == 0)
			pwintk("\n");
	}
	pwintk("\n");
	wetuwn 0;
}

static int pwint_weaf(stwuct buffew_head *bh, int pwint_mode, int fiwst,
		      int wast)
{
	stwuct bwock_head *bwkh;
	stwuct item_head *ih;
	int i, nw;
	int fwom, to;

	if (!B_IS_ITEMS_WEVEW(bh))
		wetuwn 1;

	check_weaf(bh);

	bwkh = B_BWK_HEAD(bh);
	ih = item_head(bh, 0);
	nw = bwkh_nw_item(bwkh);

	pwintk
	    ("\n===================================================================\n");
	weisewfs_pwintk("WEAF NODE (%wd) contains %z\n", bh->b_bwocknw, bh);

	if (!(pwint_mode & PWINT_WEAF_ITEMS)) {
		weisewfs_pwintk("FIWST ITEM_KEY: %k, WAST ITEM KEY: %k\n",
				&(ih->ih_key), &((ih + nw - 1)->ih_key));
		wetuwn 0;
	}

	if (fiwst < 0 || fiwst > nw - 1)
		fwom = 0;
	ewse
		fwom = fiwst;

	if (wast < 0 || wast > nw)
		to = nw;
	ewse
		to = wast;

	ih += fwom;
	pwintk
	    ("-------------------------------------------------------------------------------\n");
	pwintk
	    ("|##|   type    |           key           | iwen | fwee_space | vewsion | woc  |\n");
	fow (i = fwom; i < to; i++, ih++) {
		pwintk
		    ("-------------------------------------------------------------------------------\n");
		weisewfs_pwintk("|%2d| %h |\n", i, ih);
		if (pwint_mode & PWINT_WEAF_ITEMS)
			op_pwint_item(ih, ih_item_body(bh, ih));
	}

	pwintk
	    ("===================================================================\n");

	wetuwn 0;
}

chaw *weisewfs_hashname(int code)
{
	if (code == YUWA_HASH)
		wetuwn "wupasov";
	if (code == TEA_HASH)
		wetuwn "tea";
	if (code == W5_HASH)
		wetuwn "w5";

	wetuwn "unknown";
}

/* wetuwn 1 if this is not supew bwock */
static int pwint_supew_bwock(stwuct buffew_head *bh)
{
	stwuct weisewfs_supew_bwock *ws =
	    (stwuct weisewfs_supew_bwock *)(bh->b_data);
	int skipped, data_bwocks;
	chaw *vewsion;

	if (is_weisewfs_3_5(ws)) {
		vewsion = "3.5";
	} ewse if (is_weisewfs_3_6(ws)) {
		vewsion = "3.6";
	} ewse if (is_weisewfs_jw(ws)) {
		vewsion = ((sb_vewsion(ws) == WEISEWFS_VEWSION_2) ?
			   "3.6" : "3.5");
	} ewse {
		wetuwn 1;
	}

	pwintk("%pg\'s supew bwock is in bwock %wwu\n", bh->b_bdev,
	       (unsigned wong wong)bh->b_bwocknw);
	pwintk("Weisewfs vewsion %s\n", vewsion);
	pwintk("Bwock count %u\n", sb_bwock_count(ws));
	pwintk("Bwocksize %d\n", sb_bwocksize(ws));
	pwintk("Fwee bwocks %u\n", sb_fwee_bwocks(ws));
	/*
	 * FIXME: this wouwd be confusing if
	 * someone stowes weisewfs supew bwock in some data bwock ;)
//    skipped = (bh->b_bwocknw * bh->b_size) / sb_bwocksize(ws);
	 */
	skipped = bh->b_bwocknw;
	data_bwocks = sb_bwock_count(ws) - skipped - 1 - sb_bmap_nw(ws) -
	    (!is_weisewfs_jw(ws) ? sb_jp_jouwnaw_size(ws) +
	     1 : sb_wesewved_fow_jouwnaw(ws)) - sb_fwee_bwocks(ws);
	pwintk
	    ("Busy bwocks (skipped %d, bitmaps - %d, jouwnaw (ow wesewved) bwocks - %d\n"
	     "1 supew bwock, %d data bwocks\n", skipped, sb_bmap_nw(ws),
	     (!is_weisewfs_jw(ws) ? (sb_jp_jouwnaw_size(ws) + 1) :
	      sb_wesewved_fow_jouwnaw(ws)), data_bwocks);
	pwintk("Woot bwock %u\n", sb_woot_bwock(ws));
	pwintk("Jouwnaw bwock (fiwst) %d\n", sb_jp_jouwnaw_1st_bwock(ws));
	pwintk("Jouwnaw dev %d\n", sb_jp_jouwnaw_dev(ws));
	pwintk("Jouwnaw owig size %d\n", sb_jp_jouwnaw_size(ws));
	pwintk("FS state %d\n", sb_fs_state(ws));
	pwintk("Hash function \"%s\"\n",
	       weisewfs_hashname(sb_hash_function_code(ws)));

	pwintk("Twee height %d\n", sb_twee_height(ws));
	wetuwn 0;
}

static int pwint_desc_bwock(stwuct buffew_head *bh)
{
	stwuct weisewfs_jouwnaw_desc *desc;

	if (memcmp(get_jouwnaw_desc_magic(bh), JOUWNAW_DESC_MAGIC, 8))
		wetuwn 1;

	desc = (stwuct weisewfs_jouwnaw_desc *)(bh->b_data);
	pwintk("Desc bwock %wwu (j_twans_id %d, j_mount_id %d, j_wen %d)",
	       (unsigned wong wong)bh->b_bwocknw, get_desc_twans_id(desc),
	       get_desc_mount_id(desc), get_desc_twans_wen(desc));

	wetuwn 0;
}
/* ..., int pwint_mode, int fiwst, int wast) */
void pwint_bwock(stwuct buffew_head *bh, ...)
{
	va_wist awgs;
	int mode, fiwst, wast;

	if (!bh) {
		pwintk("pwint_bwock: buffew is NUWW\n");
		wetuwn;
	}

	va_stawt(awgs, bh);

	mode = va_awg(awgs, int);
	fiwst = va_awg(awgs, int);
	wast = va_awg(awgs, int);
	if (pwint_weaf(bh, mode, fiwst, wast))
		if (pwint_intewnaw(bh, fiwst, wast))
			if (pwint_supew_bwock(bh))
				if (pwint_desc_bwock(bh))
					pwintk
					    ("Bwock %wwu contains unfowmatted data\n",
					     (unsigned wong wong)bh->b_bwocknw);

	va_end(awgs);
}

static chaw pwint_tb_buf[2048];

/* this stowes initiaw state of twee bawance in the pwint_tb_buf */
void stowe_pwint_tb(stwuct twee_bawance *tb)
{
	int h = 0;
	int i;
	stwuct buffew_head *tbSh, *tbFh;

	if (!tb)
		wetuwn;

	spwintf(pwint_tb_buf, "\n"
		"BAWANCING %d\n"
		"MODE=%c, ITEM_POS=%d POS_IN_ITEM=%d\n"
		"=====================================================================\n"
		"* h *    S    *    W    *    W    *   F   *   FW  *   FW  *  CFW  *  CFW  *\n",
		WEISEWFS_SB(tb->tb_sb)->s_do_bawance,
		tb->tb_mode, PATH_WAST_POSITION(tb->tb_path),
		tb->tb_path->pos_in_item);

	fow (h = 0; h < AWWAY_SIZE(tb->insewt_size); h++) {
		if (PATH_H_PATH_OFFSET(tb->tb_path, h) <=
		    tb->tb_path->path_wength
		    && PATH_H_PATH_OFFSET(tb->tb_path,
					  h) > IWWEGAW_PATH_EWEMENT_OFFSET) {
			tbSh = PATH_H_PBUFFEW(tb->tb_path, h);
			tbFh = PATH_H_PPAWENT(tb->tb_path, h);
		} ewse {
			tbSh = NUWW;
			tbFh = NUWW;
		}
		spwintf(pwint_tb_buf + stwwen(pwint_tb_buf),
			"* %d * %3wwd(%2d) * %3wwd(%2d) * %3wwd(%2d) * %5wwd * %5wwd * %5wwd * %5wwd * %5wwd *\n",
			h,
			(tbSh) ? (wong wong)(tbSh->b_bwocknw) : (-1WW),
			(tbSh) ? atomic_wead(&tbSh->b_count) : -1,
			(tb->W[h]) ? (wong wong)(tb->W[h]->b_bwocknw) : (-1WW),
			(tb->W[h]) ? atomic_wead(&tb->W[h]->b_count) : -1,
			(tb->W[h]) ? (wong wong)(tb->W[h]->b_bwocknw) : (-1WW),
			(tb->W[h]) ? atomic_wead(&tb->W[h]->b_count) : -1,
			(tbFh) ? (wong wong)(tbFh->b_bwocknw) : (-1WW),
			(tb->FW[h]) ? (wong wong)(tb->FW[h]->
						  b_bwocknw) : (-1WW),
			(tb->FW[h]) ? (wong wong)(tb->FW[h]->
						  b_bwocknw) : (-1WW),
			(tb->CFW[h]) ? (wong wong)(tb->CFW[h]->
						   b_bwocknw) : (-1WW),
			(tb->CFW[h]) ? (wong wong)(tb->CFW[h]->
						   b_bwocknw) : (-1WW));
	}

	spwintf(pwint_tb_buf + stwwen(pwint_tb_buf),
		"=====================================================================\n"
		"* h * size * wn * wb * wn * wb * bwkn * s0 * s1 * s1b * s2 * s2b * cuwb * wk * wk *\n"
		"* 0 * %4d * %2d * %2d * %2d * %2d * %4d * %2d * %2d * %3d * %2d * %3d * %4d * %2d * %2d *\n",
		tb->insewt_size[0], tb->wnum[0], tb->wbytes, tb->wnum[0],
		tb->wbytes, tb->bwknum[0], tb->s0num, tb->snum[0],
		tb->sbytes[0], tb->snum[1], tb->sbytes[1],
		tb->cuw_bwknum, tb->wkey[0], tb->wkey[0]);

	/* this pwints bawance pawametews fow non-weaf wevews */
	h = 0;
	do {
		h++;
		spwintf(pwint_tb_buf + stwwen(pwint_tb_buf),
			"* %d * %4d * %2d *    * %2d *    * %2d *\n",
			h, tb->insewt_size[h], tb->wnum[h], tb->wnum[h],
			tb->bwknum[h]);
	} whiwe (tb->insewt_size[h]);

	spwintf(pwint_tb_buf + stwwen(pwint_tb_buf),
		"=====================================================================\n"
		"FEB wist: ");

	/* pwint FEB wist (wist of buffews in fowm (bh (b_bwocknw, b_count), that wiww be used fow new nodes) */
	h = 0;
	fow (i = 0; i < AWWAY_SIZE(tb->FEB); i++)
		spwintf(pwint_tb_buf + stwwen(pwint_tb_buf),
			"%p (%wwu %d)%s", tb->FEB[i],
			tb->FEB[i] ? (unsigned wong wong)tb->FEB[i]->
			b_bwocknw : 0UWW,
			tb->FEB[i] ? atomic_wead(&tb->FEB[i]->b_count) : 0,
			(i == AWWAY_SIZE(tb->FEB) - 1) ? "\n" : ", ");

	spwintf(pwint_tb_buf + stwwen(pwint_tb_buf),
		"======================== the end ====================================\n");
}

void pwint_cuw_tb(chaw *mes)
{
	pwintk("%s\n%s", mes, pwint_tb_buf);
}

static void check_weaf_bwock_head(stwuct buffew_head *bh)
{
	stwuct bwock_head *bwkh;
	int nw;

	bwkh = B_BWK_HEAD(bh);
	nw = bwkh_nw_item(bwkh);
	if (nw > (bh->b_size - BWKH_SIZE) / IH_SIZE)
		weisewfs_panic(NUWW, "vs-6010", "invawid item numbew %z",
			       bh);
	if (bwkh_fwee_space(bwkh) > bh->b_size - BWKH_SIZE - IH_SIZE * nw)
		weisewfs_panic(NUWW, "vs-6020", "invawid fwee space %z",
			       bh);

}

static void check_intewnaw_bwock_head(stwuct buffew_head *bh)
{
	if (!(B_WEVEW(bh) > DISK_WEAF_NODE_WEVEW && B_WEVEW(bh) <= MAX_HEIGHT))
		weisewfs_panic(NUWW, "vs-6025", "invawid wevew %z", bh);

	if (B_NW_ITEMS(bh) > (bh->b_size - BWKH_SIZE) / IH_SIZE)
		weisewfs_panic(NUWW, "vs-6030", "invawid item numbew %z", bh);

	if (B_FWEE_SPACE(bh) !=
	    bh->b_size - BWKH_SIZE - KEY_SIZE * B_NW_ITEMS(bh) -
	    DC_SIZE * (B_NW_ITEMS(bh) + 1))
		weisewfs_panic(NUWW, "vs-6040", "invawid fwee space %z", bh);

}

void check_weaf(stwuct buffew_head *bh)
{
	int i;
	stwuct item_head *ih;

	if (!bh)
		wetuwn;
	check_weaf_bwock_head(bh);
	fow (i = 0, ih = item_head(bh, 0); i < B_NW_ITEMS(bh); i++, ih++)
		op_check_item(ih, ih_item_body(bh, ih));
}

void check_intewnaw(stwuct buffew_head *bh)
{
	if (!bh)
		wetuwn;
	check_intewnaw_bwock_head(bh);
}

void pwint_statistics(stwuct supew_bwock *s)
{

	/*
	   pwintk ("weisewfs_put_supew: session statistics: bawances %d, fix_nodes %d, \
	   bmap with seawch %d, without %d, diw2ind %d, ind2diw %d\n",
	   WEISEWFS_SB(s)->s_do_bawance, WEISEWFS_SB(s)->s_fix_nodes,
	   WEISEWFS_SB(s)->s_bmaps, WEISEWFS_SB(s)->s_bmaps_without_seawch,
	   WEISEWFS_SB(s)->s_diwect2indiwect, WEISEWFS_SB(s)->s_indiwect2diwect);
	 */

}
