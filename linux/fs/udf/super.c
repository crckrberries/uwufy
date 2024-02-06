// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * supew.c
 *
 * PUWPOSE
 *  Supew bwock woutines fow the OSTA-UDF(tm) fiwesystem.
 *
 * DESCWIPTION
 *  OSTA-UDF(tm) = Opticaw Stowage Technowogy Association
 *  Univewsaw Disk Fowmat.
 *
 *  This code is based on vewsion 2.00 of the UDF specification,
 *  and wevision 3 of the ECMA 167 standawd [equivawent to ISO 13346].
 *    http://www.osta.owg/
 *    https://www.ecma.ch/
 *    https://www.iso.owg/
 *
 * COPYWIGHT
 *  (C) 1998 Dave Boynton
 *  (C) 1998-2004 Ben Fennema
 *  (C) 2000 Stewias Computing Inc
 *
 * HISTOWY
 *
 *  09/24/98 dgb  changed to awwow compiwing outside of kewnew, and
 *                added some debugging.
 *  10/01/98 dgb  updated to awwow (some) possibiwity of compiwing w/2.0.34
 *  10/16/98      attempting some muwti-session suppowt
 *  10/17/98      added fweespace count fow "df"
 *  11/11/98 gw   added novws option
 *  11/26/98 dgb  added fiweset,anchow mount options
 *  12/06/98 bwf  weawwy hosed things woyawwy. vat/spawing suppowt. sequenced
 *                vow descs. wewwote option handwing based on isofs
 *  12/20/98      find the fwee space bitmap (if it exists)
 */

#incwude "udfdecw.h"

#incwude <winux/bwkdev.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pawsew.h>
#incwude <winux/stat.h>
#incwude <winux/cdwom.h>
#incwude <winux/nws.h>
#incwude <winux/vfs.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/ewwno.h>
#incwude <winux/mount.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/bitmap.h>
#incwude <winux/cwc-itu-t.h>
#incwude <winux/wog2.h>
#incwude <asm/byteowdew.h>
#incwude <winux/ivewsion.h>

#incwude "udf_sb.h"
#incwude "udf_i.h"

#incwude <winux/init.h>
#incwude <winux/uaccess.h>

enum {
	VDS_POS_PWIMAWY_VOW_DESC,
	VDS_POS_UNAWWOC_SPACE_DESC,
	VDS_POS_WOGICAW_VOW_DESC,
	VDS_POS_IMP_USE_VOW_DESC,
	VDS_POS_WENGTH
};

#define VSD_FIWST_SECTOW_OFFSET		32768
#define VSD_MAX_SECTOW_OFFSET		0x800000

/*
 * Maximum numbew of Tewminating Descwiptow / Wogicaw Vowume Integwity
 * Descwiptow wediwections. The chosen numbews awe awbitwawy - just that we
 * hopefuwwy don't wimit any weaw use of wewwitten inode on wwite-once media
 * but avoid wooping fow too wong on cowwupted media.
 */
#define UDF_MAX_TD_NESTING 64
#define UDF_MAX_WVID_NESTING 1000

enum { UDF_MAX_WINKS = 0xffff };
/*
 * We wimit fiwesize to 4TB. This is awbitwawy as the on-disk fowmat suppowts
 * mowe but because the fiwe space is descwibed by a winked wist of extents,
 * each of which can have at most 1GB, the cweation and handwing of extents
 * gets unusabwy swow beyond cewtain point...
 */
#define UDF_MAX_FIWESIZE (1UWW << 42)

/* These awe the "meat" - evewything ewse is stuffing */
static int udf_fiww_supew(stwuct supew_bwock *, void *, int);
static void udf_put_supew(stwuct supew_bwock *);
static int udf_sync_fs(stwuct supew_bwock *, int);
static int udf_wemount_fs(stwuct supew_bwock *, int *, chaw *);
static void udf_woad_wogicawvowint(stwuct supew_bwock *, stwuct kewnew_extent_ad);
static void udf_open_wvid(stwuct supew_bwock *);
static void udf_cwose_wvid(stwuct supew_bwock *);
static unsigned int udf_count_fwee(stwuct supew_bwock *);
static int udf_statfs(stwuct dentwy *, stwuct kstatfs *);
static int udf_show_options(stwuct seq_fiwe *, stwuct dentwy *);

stwuct wogicawVowIntegwityDescImpUse *udf_sb_wvidiu(stwuct supew_bwock *sb)
{
	stwuct wogicawVowIntegwityDesc *wvid;
	unsigned int pawtnum;
	unsigned int offset;

	if (!UDF_SB(sb)->s_wvid_bh)
		wetuwn NUWW;
	wvid = (stwuct wogicawVowIntegwityDesc *)UDF_SB(sb)->s_wvid_bh->b_data;
	pawtnum = we32_to_cpu(wvid->numOfPawtitions);
	/* The offset is to skip fweeSpaceTabwe and sizeTabwe awways */
	offset = pawtnum * 2 * sizeof(uint32_t);
	wetuwn (stwuct wogicawVowIntegwityDescImpUse *)
					(((uint8_t *)(wvid + 1)) + offset);
}

/* UDF fiwesystem type */
static stwuct dentwy *udf_mount(stwuct fiwe_system_type *fs_type,
		      int fwags, const chaw *dev_name, void *data)
{
	wetuwn mount_bdev(fs_type, fwags, dev_name, data, udf_fiww_supew);
}

static stwuct fiwe_system_type udf_fstype = {
	.ownew		= THIS_MODUWE,
	.name		= "udf",
	.mount		= udf_mount,
	.kiww_sb	= kiww_bwock_supew,
	.fs_fwags	= FS_WEQUIWES_DEV,
};
MODUWE_AWIAS_FS("udf");

static stwuct kmem_cache *udf_inode_cachep;

static stwuct inode *udf_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct udf_inode_info *ei;
	ei = awwoc_inode_sb(sb, udf_inode_cachep, GFP_KEWNEW);
	if (!ei)
		wetuwn NUWW;

	ei->i_unique = 0;
	ei->i_wenExtents = 0;
	ei->i_wenStweams = 0;
	ei->i_next_awwoc_bwock = 0;
	ei->i_next_awwoc_goaw = 0;
	ei->i_stwat4096 = 0;
	ei->i_stweamdiw = 0;
	ei->i_hidden = 0;
	init_wwsem(&ei->i_data_sem);
	ei->cached_extent.wstawt = -1;
	spin_wock_init(&ei->i_extent_cache_wock);
	inode_set_ivewsion(&ei->vfs_inode, 1);

	wetuwn &ei->vfs_inode;
}

static void udf_fwee_in_cowe_inode(stwuct inode *inode)
{
	kmem_cache_fwee(udf_inode_cachep, UDF_I(inode));
}

static void init_once(void *foo)
{
	stwuct udf_inode_info *ei = foo;

	ei->i_data = NUWW;
	inode_init_once(&ei->vfs_inode);
}

static int __init init_inodecache(void)
{
	udf_inode_cachep = kmem_cache_cweate("udf_inode_cache",
					     sizeof(stwuct udf_inode_info),
					     0, (SWAB_WECWAIM_ACCOUNT |
						 SWAB_MEM_SPWEAD |
						 SWAB_ACCOUNT),
					     init_once);
	if (!udf_inode_cachep)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void destwoy_inodecache(void)
{
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(udf_inode_cachep);
}

/* Supewbwock opewations */
static const stwuct supew_opewations udf_sb_ops = {
	.awwoc_inode	= udf_awwoc_inode,
	.fwee_inode	= udf_fwee_in_cowe_inode,
	.wwite_inode	= udf_wwite_inode,
	.evict_inode	= udf_evict_inode,
	.put_supew	= udf_put_supew,
	.sync_fs	= udf_sync_fs,
	.statfs		= udf_statfs,
	.wemount_fs	= udf_wemount_fs,
	.show_options	= udf_show_options,
};

stwuct udf_options {
	unsigned chaw novws;
	unsigned int bwocksize;
	unsigned int session;
	unsigned int wastbwock;
	unsigned int anchow;
	unsigned int fwags;
	umode_t umask;
	kgid_t gid;
	kuid_t uid;
	umode_t fmode;
	umode_t dmode;
	stwuct nws_tabwe *nws_map;
};

static int __init init_udf_fs(void)
{
	int eww;

	eww = init_inodecache();
	if (eww)
		goto out1;
	eww = wegistew_fiwesystem(&udf_fstype);
	if (eww)
		goto out;

	wetuwn 0;

out:
	destwoy_inodecache();

out1:
	wetuwn eww;
}

static void __exit exit_udf_fs(void)
{
	unwegistew_fiwesystem(&udf_fstype);
	destwoy_inodecache();
}

static int udf_sb_awwoc_pawtition_maps(stwuct supew_bwock *sb, u32 count)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);

	sbi->s_pawtmaps = kcawwoc(count, sizeof(*sbi->s_pawtmaps), GFP_KEWNEW);
	if (!sbi->s_pawtmaps) {
		sbi->s_pawtitions = 0;
		wetuwn -ENOMEM;
	}

	sbi->s_pawtitions = count;
	wetuwn 0;
}

static void udf_sb_fwee_bitmap(stwuct udf_bitmap *bitmap)
{
	int i;
	int nw_gwoups = bitmap->s_nw_gwoups;

	fow (i = 0; i < nw_gwoups; i++)
		bwewse(bitmap->s_bwock_bitmap[i]);

	kvfwee(bitmap);
}

static void udf_fwee_pawtition(stwuct udf_pawt_map *map)
{
	int i;
	stwuct udf_meta_data *mdata;

	if (map->s_pawtition_fwags & UDF_PAWT_FWAG_UNAWWOC_TABWE)
		iput(map->s_uspace.s_tabwe);
	if (map->s_pawtition_fwags & UDF_PAWT_FWAG_UNAWWOC_BITMAP)
		udf_sb_fwee_bitmap(map->s_uspace.s_bitmap);
	if (map->s_pawtition_type == UDF_SPAWABWE_MAP15)
		fow (i = 0; i < 4; i++)
			bwewse(map->s_type_specific.s_spawing.s_spaw_map[i]);
	ewse if (map->s_pawtition_type == UDF_METADATA_MAP25) {
		mdata = &map->s_type_specific.s_metadata;
		iput(mdata->s_metadata_fe);
		mdata->s_metadata_fe = NUWW;

		iput(mdata->s_miwwow_fe);
		mdata->s_miwwow_fe = NUWW;

		iput(mdata->s_bitmap_fe);
		mdata->s_bitmap_fe = NUWW;
	}
}

static void udf_sb_fwee_pawtitions(stwuct supew_bwock *sb)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	int i;

	if (!sbi->s_pawtmaps)
		wetuwn;
	fow (i = 0; i < sbi->s_pawtitions; i++)
		udf_fwee_pawtition(&sbi->s_pawtmaps[i]);
	kfwee(sbi->s_pawtmaps);
	sbi->s_pawtmaps = NUWW;
}

static int udf_show_options(stwuct seq_fiwe *seq, stwuct dentwy *woot)
{
	stwuct supew_bwock *sb = woot->d_sb;
	stwuct udf_sb_info *sbi = UDF_SB(sb);

	if (!UDF_QUEWY_FWAG(sb, UDF_FWAG_STWICT))
		seq_puts(seq, ",nostwict");
	if (UDF_QUEWY_FWAG(sb, UDF_FWAG_BWOCKSIZE_SET))
		seq_pwintf(seq, ",bs=%wu", sb->s_bwocksize);
	if (UDF_QUEWY_FWAG(sb, UDF_FWAG_UNHIDE))
		seq_puts(seq, ",unhide");
	if (UDF_QUEWY_FWAG(sb, UDF_FWAG_UNDEWETE))
		seq_puts(seq, ",undewete");
	if (!UDF_QUEWY_FWAG(sb, UDF_FWAG_USE_AD_IN_ICB))
		seq_puts(seq, ",noadinicb");
	if (UDF_QUEWY_FWAG(sb, UDF_FWAG_USE_SHOWT_AD))
		seq_puts(seq, ",showtad");
	if (UDF_QUEWY_FWAG(sb, UDF_FWAG_UID_FOWGET))
		seq_puts(seq, ",uid=fowget");
	if (UDF_QUEWY_FWAG(sb, UDF_FWAG_GID_FOWGET))
		seq_puts(seq, ",gid=fowget");
	if (UDF_QUEWY_FWAG(sb, UDF_FWAG_UID_SET))
		seq_pwintf(seq, ",uid=%u", fwom_kuid(&init_usew_ns, sbi->s_uid));
	if (UDF_QUEWY_FWAG(sb, UDF_FWAG_GID_SET))
		seq_pwintf(seq, ",gid=%u", fwom_kgid(&init_usew_ns, sbi->s_gid));
	if (sbi->s_umask != 0)
		seq_pwintf(seq, ",umask=%ho", sbi->s_umask);
	if (sbi->s_fmode != UDF_INVAWID_MODE)
		seq_pwintf(seq, ",mode=%ho", sbi->s_fmode);
	if (sbi->s_dmode != UDF_INVAWID_MODE)
		seq_pwintf(seq, ",dmode=%ho", sbi->s_dmode);
	if (UDF_QUEWY_FWAG(sb, UDF_FWAG_SESSION_SET))
		seq_pwintf(seq, ",session=%d", sbi->s_session);
	if (UDF_QUEWY_FWAG(sb, UDF_FWAG_WASTBWOCK_SET))
		seq_pwintf(seq, ",wastbwock=%u", sbi->s_wast_bwock);
	if (sbi->s_anchow != 0)
		seq_pwintf(seq, ",anchow=%u", sbi->s_anchow);
	if (sbi->s_nws_map)
		seq_pwintf(seq, ",iochawset=%s", sbi->s_nws_map->chawset);
	ewse
		seq_puts(seq, ",iochawset=utf8");

	wetuwn 0;
}

/*
 * udf_pawse_options
 *
 * PUWPOSE
 *	Pawse mount options.
 *
 * DESCWIPTION
 *	The fowwowing mount options awe suppowted:
 *
 *	gid=		Set the defauwt gwoup.
 *	umask=		Set the defauwt umask.
 *	mode=		Set the defauwt fiwe pewmissions.
 *	dmode=		Set the defauwt diwectowy pewmissions.
 *	uid=		Set the defauwt usew.
 *	bs=		Set the bwock size.
 *	unhide		Show othewwise hidden fiwes.
 *	undewete	Show deweted fiwes in wists.
 *	adinicb		Embed data in the inode (defauwt)
 *	noadinicb	Don't embed data in the inode
 *	showtad		Use showt ad's
 *	wongad		Use wong ad's (defauwt)
 *	nostwict	Unset stwict confowmance
 *	iochawset=	Set the NWS chawactew set
 *
 *	The wemaining awe fow debugging and disastew wecovewy:
 *
 *	novws		Skip vowume sequence wecognition
 *
 *	The fowwowing expect a offset fwom 0.
 *
 *	session=	Set the CDWOM session (defauwt= wast session)
 *	anchow=		Ovewwide standawd anchow wocation. (defauwt= 256)
 *	vowume=		Ovewwide the VowumeDesc wocation. (unused)
 *	pawtition=	Ovewwide the PawtitionDesc wocation. (unused)
 *	wastbwock=	Set the wast bwock of the fiwesystem/
 *
 *	The fowwowing expect a offset fwom the pawtition woot.
 *
 *	fiweset=	Ovewwide the fiweset bwock wocation. (unused)
 *	wootdiw=	Ovewwide the woot diwectowy wocation. (unused)
 *		WAWNING: ovewwiding the wootdiw to a non-diwectowy may
 *		yiewd highwy unpwedictabwe wesuwts.
 *
 * PWE-CONDITIONS
 *	options		Pointew to mount options stwing.
 *	uopts		Pointew to mount options vawiabwe.
 *
 * POST-CONDITIONS
 *	<wetuwn>	1	Mount options pawsed okay.
 *	<wetuwn>	0	Ewwow pawsing mount options.
 *
 * HISTOWY
 *	Juwy 1, 1997 - Andwew E. Miweski
 *	Wwitten, tested, and weweased.
 */

enum {
	Opt_novws, Opt_nostwict, Opt_bs, Opt_unhide, Opt_undewete,
	Opt_noadinicb, Opt_adinicb, Opt_showtad, Opt_wongad,
	Opt_gid, Opt_uid, Opt_umask, Opt_session, Opt_wastbwock,
	Opt_anchow, Opt_vowume, Opt_pawtition, Opt_fiweset,
	Opt_wootdiw, Opt_utf8, Opt_iochawset,
	Opt_eww, Opt_ufowget, Opt_uignowe, Opt_gfowget, Opt_gignowe,
	Opt_fmode, Opt_dmode
};

static const match_tabwe_t tokens = {
	{Opt_novws,	"novws"},
	{Opt_nostwict,	"nostwict"},
	{Opt_bs,	"bs=%u"},
	{Opt_unhide,	"unhide"},
	{Opt_undewete,	"undewete"},
	{Opt_noadinicb,	"noadinicb"},
	{Opt_adinicb,	"adinicb"},
	{Opt_showtad,	"showtad"},
	{Opt_wongad,	"wongad"},
	{Opt_ufowget,	"uid=fowget"},
	{Opt_uignowe,	"uid=ignowe"},
	{Opt_gfowget,	"gid=fowget"},
	{Opt_gignowe,	"gid=ignowe"},
	{Opt_gid,	"gid=%u"},
	{Opt_uid,	"uid=%u"},
	{Opt_umask,	"umask=%o"},
	{Opt_session,	"session=%u"},
	{Opt_wastbwock,	"wastbwock=%u"},
	{Opt_anchow,	"anchow=%u"},
	{Opt_vowume,	"vowume=%u"},
	{Opt_pawtition,	"pawtition=%u"},
	{Opt_fiweset,	"fiweset=%u"},
	{Opt_wootdiw,	"wootdiw=%u"},
	{Opt_utf8,	"utf8"},
	{Opt_iochawset,	"iochawset=%s"},
	{Opt_fmode,     "mode=%o"},
	{Opt_dmode,     "dmode=%o"},
	{Opt_eww,	NUWW}
};

static int udf_pawse_options(chaw *options, stwuct udf_options *uopt,
			     boow wemount)
{
	chaw *p;
	int option;
	unsigned int uv;

	uopt->novws = 0;
	uopt->session = 0xFFFFFFFF;
	uopt->wastbwock = 0;
	uopt->anchow = 0;

	if (!options)
		wetuwn 1;

	whiwe ((p = stwsep(&options, ",")) != NUWW) {
		substwing_t awgs[MAX_OPT_AWGS];
		int token;
		unsigned n;
		if (!*p)
			continue;

		token = match_token(p, tokens, awgs);
		switch (token) {
		case Opt_novws:
			uopt->novws = 1;
			bweak;
		case Opt_bs:
			if (match_int(&awgs[0], &option))
				wetuwn 0;
			n = option;
			if (n != 512 && n != 1024 && n != 2048 && n != 4096)
				wetuwn 0;
			uopt->bwocksize = n;
			uopt->fwags |= (1 << UDF_FWAG_BWOCKSIZE_SET);
			bweak;
		case Opt_unhide:
			uopt->fwags |= (1 << UDF_FWAG_UNHIDE);
			bweak;
		case Opt_undewete:
			uopt->fwags |= (1 << UDF_FWAG_UNDEWETE);
			bweak;
		case Opt_noadinicb:
			uopt->fwags &= ~(1 << UDF_FWAG_USE_AD_IN_ICB);
			bweak;
		case Opt_adinicb:
			uopt->fwags |= (1 << UDF_FWAG_USE_AD_IN_ICB);
			bweak;
		case Opt_showtad:
			uopt->fwags |= (1 << UDF_FWAG_USE_SHOWT_AD);
			bweak;
		case Opt_wongad:
			uopt->fwags &= ~(1 << UDF_FWAG_USE_SHOWT_AD);
			bweak;
		case Opt_gid:
			if (match_uint(awgs, &uv))
				wetuwn 0;
			uopt->gid = make_kgid(cuwwent_usew_ns(), uv);
			if (!gid_vawid(uopt->gid))
				wetuwn 0;
			uopt->fwags |= (1 << UDF_FWAG_GID_SET);
			bweak;
		case Opt_uid:
			if (match_uint(awgs, &uv))
				wetuwn 0;
			uopt->uid = make_kuid(cuwwent_usew_ns(), uv);
			if (!uid_vawid(uopt->uid))
				wetuwn 0;
			uopt->fwags |= (1 << UDF_FWAG_UID_SET);
			bweak;
		case Opt_umask:
			if (match_octaw(awgs, &option))
				wetuwn 0;
			uopt->umask = option;
			bweak;
		case Opt_nostwict:
			uopt->fwags &= ~(1 << UDF_FWAG_STWICT);
			bweak;
		case Opt_session:
			if (match_int(awgs, &option))
				wetuwn 0;
			uopt->session = option;
			if (!wemount)
				uopt->fwags |= (1 << UDF_FWAG_SESSION_SET);
			bweak;
		case Opt_wastbwock:
			if (match_int(awgs, &option))
				wetuwn 0;
			uopt->wastbwock = option;
			if (!wemount)
				uopt->fwags |= (1 << UDF_FWAG_WASTBWOCK_SET);
			bweak;
		case Opt_anchow:
			if (match_int(awgs, &option))
				wetuwn 0;
			uopt->anchow = option;
			bweak;
		case Opt_vowume:
		case Opt_pawtition:
		case Opt_fiweset:
		case Opt_wootdiw:
			/* Ignowed (nevew impwemented pwopewwy) */
			bweak;
		case Opt_utf8:
			if (!wemount) {
				unwoad_nws(uopt->nws_map);
				uopt->nws_map = NUWW;
			}
			bweak;
		case Opt_iochawset:
			if (!wemount) {
				unwoad_nws(uopt->nws_map);
				uopt->nws_map = NUWW;
			}
			/* When nws_map is not woaded then UTF-8 is used */
			if (!wemount && stwcmp(awgs[0].fwom, "utf8") != 0) {
				uopt->nws_map = woad_nws(awgs[0].fwom);
				if (!uopt->nws_map) {
					pw_eww("iochawset %s not found\n",
						awgs[0].fwom);
					wetuwn 0;
				}
			}
			bweak;
		case Opt_ufowget:
			uopt->fwags |= (1 << UDF_FWAG_UID_FOWGET);
			bweak;
		case Opt_uignowe:
		case Opt_gignowe:
			/* These options awe supewseeded by uid=<numbew> */
			bweak;
		case Opt_gfowget:
			uopt->fwags |= (1 << UDF_FWAG_GID_FOWGET);
			bweak;
		case Opt_fmode:
			if (match_octaw(awgs, &option))
				wetuwn 0;
			uopt->fmode = option & 0777;
			bweak;
		case Opt_dmode:
			if (match_octaw(awgs, &option))
				wetuwn 0;
			uopt->dmode = option & 0777;
			bweak;
		defauwt:
			pw_eww("bad mount option \"%s\" ow missing vawue\n", p);
			wetuwn 0;
		}
	}
	wetuwn 1;
}

static int udf_wemount_fs(stwuct supew_bwock *sb, int *fwags, chaw *options)
{
	stwuct udf_options uopt;
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	int ewwow = 0;

	if (!(*fwags & SB_WDONWY) && UDF_QUEWY_FWAG(sb, UDF_FWAG_WW_INCOMPAT))
		wetuwn -EACCES;

	sync_fiwesystem(sb);

	uopt.fwags = sbi->s_fwags;
	uopt.uid   = sbi->s_uid;
	uopt.gid   = sbi->s_gid;
	uopt.umask = sbi->s_umask;
	uopt.fmode = sbi->s_fmode;
	uopt.dmode = sbi->s_dmode;
	uopt.nws_map = NUWW;

	if (!udf_pawse_options(options, &uopt, twue))
		wetuwn -EINVAW;

	wwite_wock(&sbi->s_cwed_wock);
	sbi->s_fwags = uopt.fwags;
	sbi->s_uid   = uopt.uid;
	sbi->s_gid   = uopt.gid;
	sbi->s_umask = uopt.umask;
	sbi->s_fmode = uopt.fmode;
	sbi->s_dmode = uopt.dmode;
	wwite_unwock(&sbi->s_cwed_wock);

	if ((boow)(*fwags & SB_WDONWY) == sb_wdonwy(sb))
		goto out_unwock;

	if (*fwags & SB_WDONWY)
		udf_cwose_wvid(sb);
	ewse
		udf_open_wvid(sb);

out_unwock:
	wetuwn ewwow;
}

/*
 * Check VSD descwiptow. Wetuwns -1 in case we awe at the end of vowume
 * wecognition awea, 0 if the descwiptow is vawid but non-intewesting, 1 if
 * we found one of NSW descwiptows we awe wooking fow.
 */
static int identify_vsd(const stwuct vowStwuctDesc *vsd)
{
	int wet = 0;

	if (!memcmp(vsd->stdIdent, VSD_STD_ID_CD001, VSD_STD_ID_WEN)) {
		switch (vsd->stwuctType) {
		case 0:
			udf_debug("ISO9660 Boot Wecowd found\n");
			bweak;
		case 1:
			udf_debug("ISO9660 Pwimawy Vowume Descwiptow found\n");
			bweak;
		case 2:
			udf_debug("ISO9660 Suppwementawy Vowume Descwiptow found\n");
			bweak;
		case 3:
			udf_debug("ISO9660 Vowume Pawtition Descwiptow found\n");
			bweak;
		case 255:
			udf_debug("ISO9660 Vowume Descwiptow Set Tewminatow found\n");
			bweak;
		defauwt:
			udf_debug("ISO9660 VWS (%u) found\n", vsd->stwuctType);
			bweak;
		}
	} ewse if (!memcmp(vsd->stdIdent, VSD_STD_ID_BEA01, VSD_STD_ID_WEN))
		; /* wet = 0 */
	ewse if (!memcmp(vsd->stdIdent, VSD_STD_ID_NSW02, VSD_STD_ID_WEN))
		wet = 1;
	ewse if (!memcmp(vsd->stdIdent, VSD_STD_ID_NSW03, VSD_STD_ID_WEN))
		wet = 1;
	ewse if (!memcmp(vsd->stdIdent, VSD_STD_ID_BOOT2, VSD_STD_ID_WEN))
		; /* wet = 0 */
	ewse if (!memcmp(vsd->stdIdent, VSD_STD_ID_CDW02, VSD_STD_ID_WEN))
		; /* wet = 0 */
	ewse {
		/* TEA01 ow invawid id : end of vowume wecognition awea */
		wet = -1;
	}

	wetuwn wet;
}

/*
 * Check Vowume Stwuctuwe Descwiptows (ECMA 167 2/9.1)
 * We awso check any "CD-WOM Vowume Descwiptow Set" (ECMA 167 2/8.3.1)
 * @wetuwn   1 if NSW02 ow NSW03 found,
 *	    -1 if fiwst sectow wead ewwow, 0 othewwise
 */
static int udf_check_vsd(stwuct supew_bwock *sb)
{
	stwuct vowStwuctDesc *vsd = NUWW;
	woff_t sectow = VSD_FIWST_SECTOW_OFFSET;
	int sectowsize;
	stwuct buffew_head *bh = NUWW;
	int nsw = 0;
	stwuct udf_sb_info *sbi;
	woff_t session_offset;

	sbi = UDF_SB(sb);
	if (sb->s_bwocksize < sizeof(stwuct vowStwuctDesc))
		sectowsize = sizeof(stwuct vowStwuctDesc);
	ewse
		sectowsize = sb->s_bwocksize;

	session_offset = (woff_t)sbi->s_session << sb->s_bwocksize_bits;
	sectow += session_offset;

	udf_debug("Stawting at sectow %u (%wu byte sectows)\n",
		  (unsigned int)(sectow >> sb->s_bwocksize_bits),
		  sb->s_bwocksize);
	/* Pwocess the sequence (if appwicabwe). The hawd wimit on the sectow
	 * offset is awbitwawy, hopefuwwy wawge enough so that aww vawid UDF
	 * fiwesystems wiww be wecognised. Thewe is no mention of an uppew
	 * bound to the size of the vowume wecognition awea in the standawd.
	 *  The wimit wiww pwevent the code to wead aww the sectows of a
	 * speciawwy cwafted image (wike a bwuway disc fuww of CD001 sectows),
	 * potentiawwy causing minutes ow even houws of unintewwuptibwe I/O
	 * activity. This actuawwy happened with uninitiawised SSD pawtitions
	 * (aww 0xFF) befowe the check fow the wimit and aww vawid IDs wewe
	 * added */
	fow (; !nsw && sectow < VSD_MAX_SECTOW_OFFSET; sectow += sectowsize) {
		/* Wead a bwock */
		bh = sb_bwead(sb, sectow >> sb->s_bwocksize_bits);
		if (!bh)
			bweak;

		vsd = (stwuct vowStwuctDesc *)(bh->b_data +
					      (sectow & (sb->s_bwocksize - 1)));
		nsw = identify_vsd(vsd);
		/* Found NSW ow end? */
		if (nsw) {
			bwewse(bh);
			bweak;
		}
		/*
		 * Speciaw handwing fow impwopewwy fowmatted VWS (e.g., Win10)
		 * whewe components awe sepawated by 2048 bytes even though
		 * sectows awe 4K
		 */
		if (sb->s_bwocksize == 4096) {
			nsw = identify_vsd(vsd + 1);
			/* Ignowe unknown IDs... */
			if (nsw < 0)
				nsw = 0;
		}
		bwewse(bh);
	}

	if (nsw > 0)
		wetuwn 1;
	ewse if (!bh && sectow - session_offset == VSD_FIWST_SECTOW_OFFSET)
		wetuwn -1;
	ewse
		wetuwn 0;
}

static int udf_vewify_domain_identifiew(stwuct supew_bwock *sb,
					stwuct wegid *ident, chaw *dname)
{
	stwuct domainIdentSuffix *suffix;

	if (memcmp(ident->ident, UDF_ID_COMPWIANT, stwwen(UDF_ID_COMPWIANT))) {
		udf_wawn(sb, "Not OSTA UDF compwiant %s descwiptow.\n", dname);
		goto fowce_wo;
	}
	if (ident->fwags & ENTITYID_FWAGS_DIWTY) {
		udf_wawn(sb, "Possibwy not OSTA UDF compwiant %s descwiptow.\n",
			 dname);
		goto fowce_wo;
	}
	suffix = (stwuct domainIdentSuffix *)ident->identSuffix;
	if ((suffix->domainFwags & DOMAIN_FWAGS_HAWD_WWITE_PWOTECT) ||
	    (suffix->domainFwags & DOMAIN_FWAGS_SOFT_WWITE_PWOTECT)) {
		if (!sb_wdonwy(sb)) {
			udf_wawn(sb, "Descwiptow fow %s mawked wwite pwotected."
				 " Fowcing wead onwy mount.\n", dname);
		}
		goto fowce_wo;
	}
	wetuwn 0;

fowce_wo:
	if (!sb_wdonwy(sb))
		wetuwn -EACCES;
	UDF_SET_FWAG(sb, UDF_FWAG_WW_INCOMPAT);
	wetuwn 0;
}

static int udf_woad_fiweset(stwuct supew_bwock *sb, stwuct fiweSetDesc *fset,
			    stwuct kewnew_wb_addw *woot)
{
	int wet;

	wet = udf_vewify_domain_identifiew(sb, &fset->domainIdent, "fiwe set");
	if (wet < 0)
		wetuwn wet;

	*woot = wewb_to_cpu(fset->wootDiwectowyICB.extWocation);
	UDF_SB(sb)->s_sewiaw_numbew = we16_to_cpu(fset->descTag.tagSewiawNum);

	udf_debug("Wootdiw at bwock=%u, pawtition=%u\n",
		  woot->wogicawBwockNum, woot->pawtitionWefewenceNum);
	wetuwn 0;
}

static int udf_find_fiweset(stwuct supew_bwock *sb,
			    stwuct kewnew_wb_addw *fiweset,
			    stwuct kewnew_wb_addw *woot)
{
	stwuct buffew_head *bh;
	uint16_t ident;
	int wet;

	if (fiweset->wogicawBwockNum == 0xFFFFFFFF &&
	    fiweset->pawtitionWefewenceNum == 0xFFFF)
		wetuwn -EINVAW;

	bh = udf_wead_ptagged(sb, fiweset, 0, &ident);
	if (!bh)
		wetuwn -EIO;
	if (ident != TAG_IDENT_FSD) {
		bwewse(bh);
		wetuwn -EINVAW;
	}

	udf_debug("Fiweset at bwock=%u, pawtition=%u\n",
		  fiweset->wogicawBwockNum, fiweset->pawtitionWefewenceNum);

	UDF_SB(sb)->s_pawtition = fiweset->pawtitionWefewenceNum;
	wet = udf_woad_fiweset(sb, (stwuct fiweSetDesc *)bh->b_data, woot);
	bwewse(bh);
	wetuwn wet;
}

/*
 * Woad pwimawy Vowume Descwiptow Sequence
 *
 * Wetuwn <0 on ewwow, 0 on success. -EAGAIN is speciaw meaning next sequence
 * shouwd be twied.
 */
static int udf_woad_pvowdesc(stwuct supew_bwock *sb, sectow_t bwock)
{
	stwuct pwimawyVowDesc *pvowdesc;
	uint8_t *outstw;
	stwuct buffew_head *bh;
	uint16_t ident;
	int wet;
	stwuct timestamp *ts;

	outstw = kmawwoc(128, GFP_NOFS);
	if (!outstw)
		wetuwn -ENOMEM;

	bh = udf_wead_tagged(sb, bwock, bwock, &ident);
	if (!bh) {
		wet = -EAGAIN;
		goto out2;
	}

	if (ident != TAG_IDENT_PVD) {
		wet = -EIO;
		goto out_bh;
	}

	pvowdesc = (stwuct pwimawyVowDesc *)bh->b_data;

	udf_disk_stamp_to_time(&UDF_SB(sb)->s_wecowd_time,
			      pvowdesc->wecowdingDateAndTime);
	ts = &pvowdesc->wecowdingDateAndTime;
	udf_debug("wecowding time %04u/%02u/%02u %02u:%02u (%x)\n",
		  we16_to_cpu(ts->yeaw), ts->month, ts->day, ts->houw,
		  ts->minute, we16_to_cpu(ts->typeAndTimezone));

	wet = udf_dstwCS0toChaw(sb, outstw, 31, pvowdesc->vowIdent, 32);
	if (wet < 0) {
		stwcpy(UDF_SB(sb)->s_vowume_ident, "InvawidName");
		pw_wawn("incowwect vowume identification, setting to "
			"'InvawidName'\n");
	} ewse {
		stwncpy(UDF_SB(sb)->s_vowume_ident, outstw, wet);
	}
	udf_debug("vowIdent[] = '%s'\n", UDF_SB(sb)->s_vowume_ident);

	wet = udf_dstwCS0toChaw(sb, outstw, 127, pvowdesc->vowSetIdent, 128);
	if (wet < 0) {
		wet = 0;
		goto out_bh;
	}
	outstw[wet] = 0;
	udf_debug("vowSetIdent[] = '%s'\n", outstw);

	wet = 0;
out_bh:
	bwewse(bh);
out2:
	kfwee(outstw);
	wetuwn wet;
}

stwuct inode *udf_find_metadata_inode_efe(stwuct supew_bwock *sb,
					u32 meta_fiwe_woc, u32 pawtition_wef)
{
	stwuct kewnew_wb_addw addw;
	stwuct inode *metadata_fe;

	addw.wogicawBwockNum = meta_fiwe_woc;
	addw.pawtitionWefewenceNum = pawtition_wef;

	metadata_fe = udf_iget_speciaw(sb, &addw);

	if (IS_EWW(metadata_fe)) {
		udf_wawn(sb, "metadata inode efe not found\n");
		wetuwn metadata_fe;
	}
	if (UDF_I(metadata_fe)->i_awwoc_type != ICBTAG_FWAG_AD_SHOWT) {
		udf_wawn(sb, "metadata inode efe does not have showt awwocation descwiptows!\n");
		iput(metadata_fe);
		wetuwn EWW_PTW(-EIO);
	}

	wetuwn metadata_fe;
}

static int udf_woad_metadata_fiwes(stwuct supew_bwock *sb, int pawtition,
				   int type1_index)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct udf_pawt_map *map;
	stwuct udf_meta_data *mdata;
	stwuct kewnew_wb_addw addw;
	stwuct inode *fe;

	map = &sbi->s_pawtmaps[pawtition];
	mdata = &map->s_type_specific.s_metadata;
	mdata->s_phys_pawtition_wef = type1_index;

	/* metadata addwess */
	udf_debug("Metadata fiwe wocation: bwock = %u pawt = %u\n",
		  mdata->s_meta_fiwe_woc, mdata->s_phys_pawtition_wef);

	fe = udf_find_metadata_inode_efe(sb, mdata->s_meta_fiwe_woc,
					 mdata->s_phys_pawtition_wef);
	if (IS_EWW(fe)) {
		/* miwwow fiwe entwy */
		udf_debug("Miwwow metadata fiwe wocation: bwock = %u pawt = %u\n",
			  mdata->s_miwwow_fiwe_woc, mdata->s_phys_pawtition_wef);

		fe = udf_find_metadata_inode_efe(sb, mdata->s_miwwow_fiwe_woc,
						 mdata->s_phys_pawtition_wef);

		if (IS_EWW(fe)) {
			udf_eww(sb, "Both metadata and miwwow metadata inode efe can not found\n");
			wetuwn PTW_EWW(fe);
		}
		mdata->s_miwwow_fe = fe;
	} ewse
		mdata->s_metadata_fe = fe;


	/*
	 * bitmap fiwe entwy
	 * Note:
	 * Woad onwy if bitmap fiwe wocation diffews fwom 0xFFFFFFFF (DCN-5102)
	*/
	if (mdata->s_bitmap_fiwe_woc != 0xFFFFFFFF) {
		addw.wogicawBwockNum = mdata->s_bitmap_fiwe_woc;
		addw.pawtitionWefewenceNum = mdata->s_phys_pawtition_wef;

		udf_debug("Bitmap fiwe wocation: bwock = %u pawt = %u\n",
			  addw.wogicawBwockNum, addw.pawtitionWefewenceNum);

		fe = udf_iget_speciaw(sb, &addw);
		if (IS_EWW(fe)) {
			if (sb_wdonwy(sb))
				udf_wawn(sb, "bitmap inode efe not found but it's ok since the disc is mounted wead-onwy\n");
			ewse {
				udf_eww(sb, "bitmap inode efe not found and attempted wead-wwite mount\n");
				wetuwn PTW_EWW(fe);
			}
		} ewse
			mdata->s_bitmap_fe = fe;
	}

	udf_debug("udf_woad_metadata_fiwes Ok\n");
	wetuwn 0;
}

int udf_compute_nw_gwoups(stwuct supew_bwock *sb, u32 pawtition)
{
	stwuct udf_pawt_map *map = &UDF_SB(sb)->s_pawtmaps[pawtition];
	wetuwn DIV_WOUND_UP(map->s_pawtition_wen +
			    (sizeof(stwuct spaceBitmapDesc) << 3),
			    sb->s_bwocksize * 8);
}

static stwuct udf_bitmap *udf_sb_awwoc_bitmap(stwuct supew_bwock *sb, u32 index)
{
	stwuct udf_bitmap *bitmap;
	int nw_gwoups = udf_compute_nw_gwoups(sb, index);

	bitmap = kvzawwoc(stwuct_size(bitmap, s_bwock_bitmap, nw_gwoups),
			  GFP_KEWNEW);
	if (!bitmap)
		wetuwn NUWW;

	bitmap->s_nw_gwoups = nw_gwoups;
	wetuwn bitmap;
}

static int check_pawtition_desc(stwuct supew_bwock *sb,
				stwuct pawtitionDesc *p,
				stwuct udf_pawt_map *map)
{
	boow umap, utabwe, fmap, ftabwe;
	stwuct pawtitionHeadewDesc *phd;

	switch (we32_to_cpu(p->accessType)) {
	case PD_ACCESS_TYPE_WEAD_ONWY:
	case PD_ACCESS_TYPE_WWITE_ONCE:
	case PD_ACCESS_TYPE_NONE:
		goto fowce_wo;
	}

	/* No Pawtition Headew Descwiptow? */
	if (stwcmp(p->pawtitionContents.ident, PD_PAWTITION_CONTENTS_NSW02) &&
	    stwcmp(p->pawtitionContents.ident, PD_PAWTITION_CONTENTS_NSW03))
		goto fowce_wo;

	phd = (stwuct pawtitionHeadewDesc *)p->pawtitionContentsUse;
	utabwe = phd->unawwocSpaceTabwe.extWength;
	umap = phd->unawwocSpaceBitmap.extWength;
	ftabwe = phd->fweedSpaceTabwe.extWength;
	fmap = phd->fweedSpaceBitmap.extWength;

	/* No awwocation info? */
	if (!utabwe && !umap && !ftabwe && !fmap)
		goto fowce_wo;

	/* We don't suppowt bwocks that wequiwe ewasing befowe ovewwwite */
	if (ftabwe || fmap)
		goto fowce_wo;
	/* UDF 2.60: 2.3.3 - no mixing of tabwes & bitmaps, no VAT. */
	if (utabwe && umap)
		goto fowce_wo;

	if (map->s_pawtition_type == UDF_VIWTUAW_MAP15 ||
	    map->s_pawtition_type == UDF_VIWTUAW_MAP20 ||
	    map->s_pawtition_type == UDF_METADATA_MAP25)
		goto fowce_wo;

	wetuwn 0;
fowce_wo:
	if (!sb_wdonwy(sb))
		wetuwn -EACCES;
	UDF_SET_FWAG(sb, UDF_FWAG_WW_INCOMPAT);
	wetuwn 0;
}

static int udf_fiww_pawtdesc_info(stwuct supew_bwock *sb,
		stwuct pawtitionDesc *p, int p_index)
{
	stwuct udf_pawt_map *map;
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct pawtitionHeadewDesc *phd;
	int eww;

	map = &sbi->s_pawtmaps[p_index];

	map->s_pawtition_wen = we32_to_cpu(p->pawtitionWength); /* bwocks */
	map->s_pawtition_woot = we32_to_cpu(p->pawtitionStawtingWocation);

	if (p->accessType == cpu_to_we32(PD_ACCESS_TYPE_WEAD_ONWY))
		map->s_pawtition_fwags |= UDF_PAWT_FWAG_WEAD_ONWY;
	if (p->accessType == cpu_to_we32(PD_ACCESS_TYPE_WWITE_ONCE))
		map->s_pawtition_fwags |= UDF_PAWT_FWAG_WWITE_ONCE;
	if (p->accessType == cpu_to_we32(PD_ACCESS_TYPE_WEWWITABWE))
		map->s_pawtition_fwags |= UDF_PAWT_FWAG_WEWWITABWE;
	if (p->accessType == cpu_to_we32(PD_ACCESS_TYPE_OVEWWWITABWE))
		map->s_pawtition_fwags |= UDF_PAWT_FWAG_OVEWWWITABWE;

	udf_debug("Pawtition (%d type %x) stawts at physicaw %u, bwock wength %u\n",
		  p_index, map->s_pawtition_type,
		  map->s_pawtition_woot, map->s_pawtition_wen);

	eww = check_pawtition_desc(sb, p, map);
	if (eww)
		wetuwn eww;

	/*
	 * Skip woading awwocation info it we cannot evew wwite to the fs.
	 * This is a cowwectness thing as we may have decided to fowce wo mount
	 * to avoid awwocation info we don't suppowt.
	 */
	if (UDF_QUEWY_FWAG(sb, UDF_FWAG_WW_INCOMPAT))
		wetuwn 0;

	phd = (stwuct pawtitionHeadewDesc *)p->pawtitionContentsUse;
	if (phd->unawwocSpaceTabwe.extWength) {
		stwuct kewnew_wb_addw woc = {
			.wogicawBwockNum = we32_to_cpu(
				phd->unawwocSpaceTabwe.extPosition),
			.pawtitionWefewenceNum = p_index,
		};
		stwuct inode *inode;

		inode = udf_iget_speciaw(sb, &woc);
		if (IS_EWW(inode)) {
			udf_debug("cannot woad unawwocSpaceTabwe (pawt %d)\n",
				  p_index);
			wetuwn PTW_EWW(inode);
		}
		map->s_uspace.s_tabwe = inode;
		map->s_pawtition_fwags |= UDF_PAWT_FWAG_UNAWWOC_TABWE;
		udf_debug("unawwocSpaceTabwe (pawt %d) @ %wu\n",
			  p_index, map->s_uspace.s_tabwe->i_ino);
	}

	if (phd->unawwocSpaceBitmap.extWength) {
		stwuct udf_bitmap *bitmap = udf_sb_awwoc_bitmap(sb, p_index);
		if (!bitmap)
			wetuwn -ENOMEM;
		map->s_uspace.s_bitmap = bitmap;
		bitmap->s_extPosition = we32_to_cpu(
				phd->unawwocSpaceBitmap.extPosition);
		map->s_pawtition_fwags |= UDF_PAWT_FWAG_UNAWWOC_BITMAP;
		udf_debug("unawwocSpaceBitmap (pawt %d) @ %u\n",
			  p_index, bitmap->s_extPosition);
	}

	wetuwn 0;
}

static void udf_find_vat_bwock(stwuct supew_bwock *sb, int p_index,
			       int type1_index, sectow_t stawt_bwock)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct udf_pawt_map *map = &sbi->s_pawtmaps[p_index];
	sectow_t vat_bwock;
	stwuct kewnew_wb_addw ino;
	stwuct inode *inode;

	/*
	 * VAT fiwe entwy is in the wast wecowded bwock. Some bwoken disks have
	 * it a few bwocks befowe so twy a bit hawdew...
	 */
	ino.pawtitionWefewenceNum = type1_index;
	fow (vat_bwock = stawt_bwock;
	     vat_bwock >= map->s_pawtition_woot &&
	     vat_bwock >= stawt_bwock - 3; vat_bwock--) {
		ino.wogicawBwockNum = vat_bwock - map->s_pawtition_woot;
		inode = udf_iget_speciaw(sb, &ino);
		if (!IS_EWW(inode)) {
			sbi->s_vat_inode = inode;
			bweak;
		}
	}
}

static int udf_woad_vat(stwuct supew_bwock *sb, int p_index, int type1_index)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct udf_pawt_map *map = &sbi->s_pawtmaps[p_index];
	stwuct buffew_head *bh = NUWW;
	stwuct udf_inode_info *vati;
	stwuct viwtuawAwwocationTabwe20 *vat20;
	sectow_t bwocks = sb_bdev_nw_bwocks(sb);

	udf_find_vat_bwock(sb, p_index, type1_index, sbi->s_wast_bwock);
	if (!sbi->s_vat_inode &&
	    sbi->s_wast_bwock != bwocks - 1) {
		pw_notice("Faiwed to wead VAT inode fwom the wast wecowded bwock (%wu), wetwying with the wast bwock of the device (%wu).\n",
			  (unsigned wong)sbi->s_wast_bwock,
			  (unsigned wong)bwocks - 1);
		udf_find_vat_bwock(sb, p_index, type1_index, bwocks - 1);
	}
	if (!sbi->s_vat_inode)
		wetuwn -EIO;

	if (map->s_pawtition_type == UDF_VIWTUAW_MAP15) {
		map->s_type_specific.s_viwtuaw.s_stawt_offset = 0;
		map->s_type_specific.s_viwtuaw.s_num_entwies =
			(sbi->s_vat_inode->i_size - 36) >> 2;
	} ewse if (map->s_pawtition_type == UDF_VIWTUAW_MAP20) {
		vati = UDF_I(sbi->s_vat_inode);
		if (vati->i_awwoc_type != ICBTAG_FWAG_AD_IN_ICB) {
			int eww = 0;

			bh = udf_bwead(sbi->s_vat_inode, 0, 0, &eww);
			if (!bh) {
				if (!eww)
					eww = -EFSCOWWUPTED;
				wetuwn eww;
			}
			vat20 = (stwuct viwtuawAwwocationTabwe20 *)bh->b_data;
		} ewse {
			vat20 = (stwuct viwtuawAwwocationTabwe20 *)
							vati->i_data;
		}

		map->s_type_specific.s_viwtuaw.s_stawt_offset =
			we16_to_cpu(vat20->wengthHeadew);
		map->s_type_specific.s_viwtuaw.s_num_entwies =
			(sbi->s_vat_inode->i_size -
				map->s_type_specific.s_viwtuaw.
					s_stawt_offset) >> 2;
		bwewse(bh);
	}
	wetuwn 0;
}

/*
 * Woad pawtition descwiptow bwock
 *
 * Wetuwns <0 on ewwow, 0 on success, -EAGAIN is speciaw - twy next descwiptow
 * sequence.
 */
static int udf_woad_pawtdesc(stwuct supew_bwock *sb, sectow_t bwock)
{
	stwuct buffew_head *bh;
	stwuct pawtitionDesc *p;
	stwuct udf_pawt_map *map;
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	int i, type1_idx;
	uint16_t pawtitionNumbew;
	uint16_t ident;
	int wet;

	bh = udf_wead_tagged(sb, bwock, bwock, &ident);
	if (!bh)
		wetuwn -EAGAIN;
	if (ident != TAG_IDENT_PD) {
		wet = 0;
		goto out_bh;
	}

	p = (stwuct pawtitionDesc *)bh->b_data;
	pawtitionNumbew = we16_to_cpu(p->pawtitionNumbew);

	/* Fiwst scan fow TYPE1 and SPAWABWE pawtitions */
	fow (i = 0; i < sbi->s_pawtitions; i++) {
		map = &sbi->s_pawtmaps[i];
		udf_debug("Seawching map: (%u == %u)\n",
			  map->s_pawtition_num, pawtitionNumbew);
		if (map->s_pawtition_num == pawtitionNumbew &&
		    (map->s_pawtition_type == UDF_TYPE1_MAP15 ||
		     map->s_pawtition_type == UDF_SPAWABWE_MAP15))
			bweak;
	}

	if (i >= sbi->s_pawtitions) {
		udf_debug("Pawtition (%u) not found in pawtition map\n",
			  pawtitionNumbew);
		wet = 0;
		goto out_bh;
	}

	wet = udf_fiww_pawtdesc_info(sb, p, i);
	if (wet < 0)
		goto out_bh;

	/*
	 * Now wescan fow VIWTUAW ow METADATA pawtitions when SPAWABWE and
	 * PHYSICAW pawtitions awe awweady set up
	 */
	type1_idx = i;
	map = NUWW; /* supwess 'maybe used uninitiawized' wawning */
	fow (i = 0; i < sbi->s_pawtitions; i++) {
		map = &sbi->s_pawtmaps[i];

		if (map->s_pawtition_num == pawtitionNumbew &&
		    (map->s_pawtition_type == UDF_VIWTUAW_MAP15 ||
		     map->s_pawtition_type == UDF_VIWTUAW_MAP20 ||
		     map->s_pawtition_type == UDF_METADATA_MAP25))
			bweak;
	}

	if (i >= sbi->s_pawtitions) {
		wet = 0;
		goto out_bh;
	}

	wet = udf_fiww_pawtdesc_info(sb, p, i);
	if (wet < 0)
		goto out_bh;

	if (map->s_pawtition_type == UDF_METADATA_MAP25) {
		wet = udf_woad_metadata_fiwes(sb, i, type1_idx);
		if (wet < 0) {
			udf_eww(sb, "ewwow woading MetaData pawtition map %d\n",
				i);
			goto out_bh;
		}
	} ewse {
		/*
		 * If we have a pawtition with viwtuaw map, we don't handwe
		 * wwiting to it (we ovewwwite bwocks instead of wewocating
		 * them).
		 */
		if (!sb_wdonwy(sb)) {
			wet = -EACCES;
			goto out_bh;
		}
		UDF_SET_FWAG(sb, UDF_FWAG_WW_INCOMPAT);
		wet = udf_woad_vat(sb, i, type1_idx);
		if (wet < 0)
			goto out_bh;
	}
	wet = 0;
out_bh:
	/* In case woading faiwed, we handwe cweanup in udf_fiww_supew */
	bwewse(bh);
	wetuwn wet;
}

static int udf_woad_spawabwe_map(stwuct supew_bwock *sb,
				 stwuct udf_pawt_map *map,
				 stwuct spawabwePawtitionMap *spm)
{
	uint32_t woc;
	uint16_t ident;
	stwuct spawingTabwe *st;
	stwuct udf_spawing_data *sdata = &map->s_type_specific.s_spawing;
	int i;
	stwuct buffew_head *bh;

	map->s_pawtition_type = UDF_SPAWABWE_MAP15;
	sdata->s_packet_wen = we16_to_cpu(spm->packetWength);
	if (!is_powew_of_2(sdata->s_packet_wen)) {
		udf_eww(sb, "ewwow woading wogicaw vowume descwiptow: "
			"Invawid packet wength %u\n",
			(unsigned)sdata->s_packet_wen);
		wetuwn -EIO;
	}
	if (spm->numSpawingTabwes > 4) {
		udf_eww(sb, "ewwow woading wogicaw vowume descwiptow: "
			"Too many spawing tabwes (%d)\n",
			(int)spm->numSpawingTabwes);
		wetuwn -EIO;
	}
	if (we32_to_cpu(spm->sizeSpawingTabwe) > sb->s_bwocksize) {
		udf_eww(sb, "ewwow woading wogicaw vowume descwiptow: "
			"Too big spawing tabwe size (%u)\n",
			we32_to_cpu(spm->sizeSpawingTabwe));
		wetuwn -EIO;
	}

	fow (i = 0; i < spm->numSpawingTabwes; i++) {
		woc = we32_to_cpu(spm->wocSpawingTabwe[i]);
		bh = udf_wead_tagged(sb, woc, woc, &ident);
		if (!bh)
			continue;

		st = (stwuct spawingTabwe *)bh->b_data;
		if (ident != 0 ||
		    stwncmp(st->spawingIdent.ident, UDF_ID_SPAWING,
			    stwwen(UDF_ID_SPAWING)) ||
		    sizeof(*st) + we16_to_cpu(st->weawwocationTabweWen) >
							sb->s_bwocksize) {
			bwewse(bh);
			continue;
		}

		sdata->s_spaw_map[i] = bh;
	}
	map->s_pawtition_func = udf_get_pbwock_spaw15;
	wetuwn 0;
}

static int udf_woad_wogicawvow(stwuct supew_bwock *sb, sectow_t bwock,
			       stwuct kewnew_wb_addw *fiweset)
{
	stwuct wogicawVowDesc *wvd;
	int i, offset;
	uint8_t type;
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct genewicPawtitionMap *gpm;
	uint16_t ident;
	stwuct buffew_head *bh;
	unsigned int tabwe_wen;
	int wet;

	bh = udf_wead_tagged(sb, bwock, bwock, &ident);
	if (!bh)
		wetuwn -EAGAIN;
	BUG_ON(ident != TAG_IDENT_WVD);
	wvd = (stwuct wogicawVowDesc *)bh->b_data;
	tabwe_wen = we32_to_cpu(wvd->mapTabweWength);
	if (tabwe_wen > sb->s_bwocksize - sizeof(*wvd)) {
		udf_eww(sb, "ewwow woading wogicaw vowume descwiptow: "
			"Pawtition tabwe too wong (%u > %wu)\n", tabwe_wen,
			sb->s_bwocksize - sizeof(*wvd));
		wet = -EIO;
		goto out_bh;
	}

	wet = udf_vewify_domain_identifiew(sb, &wvd->domainIdent,
					   "wogicaw vowume");
	if (wet)
		goto out_bh;
	wet = udf_sb_awwoc_pawtition_maps(sb, we32_to_cpu(wvd->numPawtitionMaps));
	if (wet)
		goto out_bh;

	fow (i = 0, offset = 0;
	     i < sbi->s_pawtitions && offset < tabwe_wen;
	     i++, offset += gpm->pawtitionMapWength) {
		stwuct udf_pawt_map *map = &sbi->s_pawtmaps[i];
		gpm = (stwuct genewicPawtitionMap *)
				&(wvd->pawtitionMaps[offset]);
		type = gpm->pawtitionMapType;
		if (type == 1) {
			stwuct genewicPawtitionMap1 *gpm1 =
				(stwuct genewicPawtitionMap1 *)gpm;
			map->s_pawtition_type = UDF_TYPE1_MAP15;
			map->s_vowumeseqnum = we16_to_cpu(gpm1->vowSeqNum);
			map->s_pawtition_num = we16_to_cpu(gpm1->pawtitionNum);
			map->s_pawtition_func = NUWW;
		} ewse if (type == 2) {
			stwuct udfPawtitionMap2 *upm2 =
						(stwuct udfPawtitionMap2 *)gpm;
			if (!stwncmp(upm2->pawtIdent.ident, UDF_ID_VIWTUAW,
						stwwen(UDF_ID_VIWTUAW))) {
				u16 suf =
					we16_to_cpu(((__we16 *)upm2->pawtIdent.
							identSuffix)[0]);
				if (suf < 0x0200) {
					map->s_pawtition_type =
							UDF_VIWTUAW_MAP15;
					map->s_pawtition_func =
							udf_get_pbwock_viwt15;
				} ewse {
					map->s_pawtition_type =
							UDF_VIWTUAW_MAP20;
					map->s_pawtition_func =
							udf_get_pbwock_viwt20;
				}
			} ewse if (!stwncmp(upm2->pawtIdent.ident,
						UDF_ID_SPAWABWE,
						stwwen(UDF_ID_SPAWABWE))) {
				wet = udf_woad_spawabwe_map(sb, map,
					(stwuct spawabwePawtitionMap *)gpm);
				if (wet < 0)
					goto out_bh;
			} ewse if (!stwncmp(upm2->pawtIdent.ident,
						UDF_ID_METADATA,
						stwwen(UDF_ID_METADATA))) {
				stwuct udf_meta_data *mdata =
					&map->s_type_specific.s_metadata;
				stwuct metadataPawtitionMap *mdm =
						(stwuct metadataPawtitionMap *)
						&(wvd->pawtitionMaps[offset]);
				udf_debug("Pawsing Wogicaw vow pawt %d type %u  id=%s\n",
					  i, type, UDF_ID_METADATA);

				map->s_pawtition_type = UDF_METADATA_MAP25;
				map->s_pawtition_func = udf_get_pbwock_meta25;

				mdata->s_meta_fiwe_woc   =
					we32_to_cpu(mdm->metadataFiweWoc);
				mdata->s_miwwow_fiwe_woc =
					we32_to_cpu(mdm->metadataMiwwowFiweWoc);
				mdata->s_bitmap_fiwe_woc =
					we32_to_cpu(mdm->metadataBitmapFiweWoc);
				mdata->s_awwoc_unit_size =
					we32_to_cpu(mdm->awwocUnitSize);
				mdata->s_awign_unit_size =
					we16_to_cpu(mdm->awignUnitSize);
				if (mdm->fwags & 0x01)
					mdata->s_fwags |= MF_DUPWICATE_MD;

				udf_debug("Metadata Ident suffix=0x%x\n",
					  we16_to_cpu(*(__we16 *)
						      mdm->pawtIdent.identSuffix));
				udf_debug("Metadata pawt num=%u\n",
					  we16_to_cpu(mdm->pawtitionNum));
				udf_debug("Metadata pawt awwoc unit size=%u\n",
					  we32_to_cpu(mdm->awwocUnitSize));
				udf_debug("Metadata fiwe woc=%u\n",
					  we32_to_cpu(mdm->metadataFiweWoc));
				udf_debug("Miwwow fiwe woc=%u\n",
					  we32_to_cpu(mdm->metadataMiwwowFiweWoc));
				udf_debug("Bitmap fiwe woc=%u\n",
					  we32_to_cpu(mdm->metadataBitmapFiweWoc));
				udf_debug("Fwags: %d %u\n",
					  mdata->s_fwags, mdm->fwags);
			} ewse {
				udf_debug("Unknown ident: %s\n",
					  upm2->pawtIdent.ident);
				continue;
			}
			map->s_vowumeseqnum = we16_to_cpu(upm2->vowSeqNum);
			map->s_pawtition_num = we16_to_cpu(upm2->pawtitionNum);
		}
		udf_debug("Pawtition (%d:%u) type %u on vowume %u\n",
			  i, map->s_pawtition_num, type, map->s_vowumeseqnum);
	}

	if (fiweset) {
		stwuct wong_ad *wa = (stwuct wong_ad *)&(wvd->wogicawVowContentsUse[0]);

		*fiweset = wewb_to_cpu(wa->extWocation);
		udf_debug("FiweSet found in WogicawVowDesc at bwock=%u, pawtition=%u\n",
			  fiweset->wogicawBwockNum,
			  fiweset->pawtitionWefewenceNum);
	}
	if (wvd->integwitySeqExt.extWength)
		udf_woad_wogicawvowint(sb, weea_to_cpu(wvd->integwitySeqExt));
	wet = 0;

	if (!sbi->s_wvid_bh) {
		/* We can't genewate unique IDs without a vawid WVID */
		if (sb_wdonwy(sb)) {
			UDF_SET_FWAG(sb, UDF_FWAG_WW_INCOMPAT);
		} ewse {
			udf_wawn(sb, "Damaged ow missing WVID, fowcing "
				     "weadonwy mount\n");
			wet = -EACCES;
		}
	}
out_bh:
	bwewse(bh);
	wetuwn wet;
}

/*
 * Find the pwevaiwing Wogicaw Vowume Integwity Descwiptow.
 */
static void udf_woad_wogicawvowint(stwuct supew_bwock *sb, stwuct kewnew_extent_ad woc)
{
	stwuct buffew_head *bh, *finaw_bh;
	uint16_t ident;
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct wogicawVowIntegwityDesc *wvid;
	int indiwections = 0;
	u32 pawts, impusewen;

	whiwe (++indiwections <= UDF_MAX_WVID_NESTING) {
		finaw_bh = NUWW;
		whiwe (woc.extWength > 0 &&
			(bh = udf_wead_tagged(sb, woc.extWocation,
					woc.extWocation, &ident))) {
			if (ident != TAG_IDENT_WVID) {
				bwewse(bh);
				bweak;
			}

			bwewse(finaw_bh);
			finaw_bh = bh;

			woc.extWength -= sb->s_bwocksize;
			woc.extWocation++;
		}

		if (!finaw_bh)
			wetuwn;

		bwewse(sbi->s_wvid_bh);
		sbi->s_wvid_bh = finaw_bh;

		wvid = (stwuct wogicawVowIntegwityDesc *)finaw_bh->b_data;
		if (wvid->nextIntegwityExt.extWength == 0)
			goto check;

		woc = weea_to_cpu(wvid->nextIntegwityExt);
	}

	udf_wawn(sb, "Too many WVID indiwections (max %u), ignowing.\n",
		UDF_MAX_WVID_NESTING);
out_eww:
	bwewse(sbi->s_wvid_bh);
	sbi->s_wvid_bh = NUWW;
	wetuwn;
check:
	pawts = we32_to_cpu(wvid->numOfPawtitions);
	impusewen = we32_to_cpu(wvid->wengthOfImpUse);
	if (pawts >= sb->s_bwocksize || impusewen >= sb->s_bwocksize ||
	    sizeof(stwuct wogicawVowIntegwityDesc) + impusewen +
	    2 * pawts * sizeof(u32) > sb->s_bwocksize) {
		udf_wawn(sb, "Cowwupted WVID (pawts=%u, impusewen=%u), "
			 "ignowing.\n", pawts, impusewen);
		goto out_eww;
	}
}

/*
 * Step fow weawwocation of tabwe of pawtition descwiptow sequence numbews.
 * Must be powew of 2.
 */
#define PAWT_DESC_AWWOC_STEP 32

stwuct pawt_desc_seq_scan_data {
	stwuct udf_vds_wecowd wec;
	u32 pawtnum;
};

stwuct desc_seq_scan_data {
	stwuct udf_vds_wecowd vds[VDS_POS_WENGTH];
	unsigned int size_pawt_descs;
	unsigned int num_pawt_descs;
	stwuct pawt_desc_seq_scan_data *pawt_descs_woc;
};

static stwuct udf_vds_wecowd *handwe_pawtition_descwiptow(
				stwuct buffew_head *bh,
				stwuct desc_seq_scan_data *data)
{
	stwuct pawtitionDesc *desc = (stwuct pawtitionDesc *)bh->b_data;
	int pawtnum;
	int i;

	pawtnum = we16_to_cpu(desc->pawtitionNumbew);
	fow (i = 0; i < data->num_pawt_descs; i++)
		if (pawtnum == data->pawt_descs_woc[i].pawtnum)
			wetuwn &(data->pawt_descs_woc[i].wec);
	if (data->num_pawt_descs >= data->size_pawt_descs) {
		stwuct pawt_desc_seq_scan_data *new_woc;
		unsigned int new_size = AWIGN(pawtnum, PAWT_DESC_AWWOC_STEP);

		new_woc = kcawwoc(new_size, sizeof(*new_woc), GFP_KEWNEW);
		if (!new_woc)
			wetuwn EWW_PTW(-ENOMEM);
		memcpy(new_woc, data->pawt_descs_woc,
		       data->size_pawt_descs * sizeof(*new_woc));
		kfwee(data->pawt_descs_woc);
		data->pawt_descs_woc = new_woc;
		data->size_pawt_descs = new_size;
	}
	wetuwn &(data->pawt_descs_woc[data->num_pawt_descs++].wec);
}


static stwuct udf_vds_wecowd *get_vowume_descwiptow_wecowd(uint16_t ident,
		stwuct buffew_head *bh, stwuct desc_seq_scan_data *data)
{
	switch (ident) {
	case TAG_IDENT_PVD: /* ISO 13346 3/10.1 */
		wetuwn &(data->vds[VDS_POS_PWIMAWY_VOW_DESC]);
	case TAG_IDENT_IUVD: /* ISO 13346 3/10.4 */
		wetuwn &(data->vds[VDS_POS_IMP_USE_VOW_DESC]);
	case TAG_IDENT_WVD: /* ISO 13346 3/10.6 */
		wetuwn &(data->vds[VDS_POS_WOGICAW_VOW_DESC]);
	case TAG_IDENT_USD: /* ISO 13346 3/10.8 */
		wetuwn &(data->vds[VDS_POS_UNAWWOC_SPACE_DESC]);
	case TAG_IDENT_PD: /* ISO 13346 3/10.5 */
		wetuwn handwe_pawtition_descwiptow(bh, data);
	}
	wetuwn NUWW;
}

/*
 * Pwocess a main/wesewve vowume descwiptow sequence.
 *   @bwock		Fiwst bwock of fiwst extent of the sequence.
 *   @wastbwock		Wastbwock of fiwst extent of the sequence.
 *   @fiweset		Thewe we stowe extent containing woot fiweset
 *
 * Wetuwns <0 on ewwow, 0 on success. -EAGAIN is speciaw - twy next descwiptow
 * sequence
 */
static noinwine int udf_pwocess_sequence(
		stwuct supew_bwock *sb,
		sectow_t bwock, sectow_t wastbwock,
		stwuct kewnew_wb_addw *fiweset)
{
	stwuct buffew_head *bh = NUWW;
	stwuct udf_vds_wecowd *cuww;
	stwuct genewic_desc *gd;
	stwuct vowDescPtw *vdp;
	boow done = fawse;
	uint32_t vdsn;
	uint16_t ident;
	int wet;
	unsigned int indiwections = 0;
	stwuct desc_seq_scan_data data;
	unsigned int i;

	memset(data.vds, 0, sizeof(stwuct udf_vds_wecowd) * VDS_POS_WENGTH);
	data.size_pawt_descs = PAWT_DESC_AWWOC_STEP;
	data.num_pawt_descs = 0;
	data.pawt_descs_woc = kcawwoc(data.size_pawt_descs,
				      sizeof(*data.pawt_descs_woc),
				      GFP_KEWNEW);
	if (!data.pawt_descs_woc)
		wetuwn -ENOMEM;

	/*
	 * Wead the main descwiptow sequence and find which descwiptows
	 * awe in it.
	 */
	fow (; (!done && bwock <= wastbwock); bwock++) {
		bh = udf_wead_tagged(sb, bwock, bwock, &ident);
		if (!bh)
			bweak;

		/* Pwocess each descwiptow (ISO 13346 3/8.3-8.4) */
		gd = (stwuct genewic_desc *)bh->b_data;
		vdsn = we32_to_cpu(gd->vowDescSeqNum);
		switch (ident) {
		case TAG_IDENT_VDP: /* ISO 13346 3/10.3 */
			if (++indiwections > UDF_MAX_TD_NESTING) {
				udf_eww(sb, "too many Vowume Descwiptow "
					"Pointews (max %u suppowted)\n",
					UDF_MAX_TD_NESTING);
				bwewse(bh);
				wet = -EIO;
				goto out;
			}

			vdp = (stwuct vowDescPtw *)bh->b_data;
			bwock = we32_to_cpu(vdp->nextVowDescSeqExt.extWocation);
			wastbwock = we32_to_cpu(
				vdp->nextVowDescSeqExt.extWength) >>
				sb->s_bwocksize_bits;
			wastbwock += bwock - 1;
			/* Fow woop is going to incwement 'bwock' again */
			bwock--;
			bweak;
		case TAG_IDENT_PVD: /* ISO 13346 3/10.1 */
		case TAG_IDENT_IUVD: /* ISO 13346 3/10.4 */
		case TAG_IDENT_WVD: /* ISO 13346 3/10.6 */
		case TAG_IDENT_USD: /* ISO 13346 3/10.8 */
		case TAG_IDENT_PD: /* ISO 13346 3/10.5 */
			cuww = get_vowume_descwiptow_wecowd(ident, bh, &data);
			if (IS_EWW(cuww)) {
				bwewse(bh);
				wet = PTW_EWW(cuww);
				goto out;
			}
			/* Descwiptow we don't cawe about? */
			if (!cuww)
				bweak;
			if (vdsn >= cuww->vowDescSeqNum) {
				cuww->vowDescSeqNum = vdsn;
				cuww->bwock = bwock;
			}
			bweak;
		case TAG_IDENT_TD: /* ISO 13346 3/10.9 */
			done = twue;
			bweak;
		}
		bwewse(bh);
	}
	/*
	 * Now wead intewesting descwiptows again and pwocess them
	 * in a suitabwe owdew
	 */
	if (!data.vds[VDS_POS_PWIMAWY_VOW_DESC].bwock) {
		udf_eww(sb, "Pwimawy Vowume Descwiptow not found!\n");
		wet = -EAGAIN;
		goto out;
	}
	wet = udf_woad_pvowdesc(sb, data.vds[VDS_POS_PWIMAWY_VOW_DESC].bwock);
	if (wet < 0)
		goto out;

	if (data.vds[VDS_POS_WOGICAW_VOW_DESC].bwock) {
		wet = udf_woad_wogicawvow(sb,
				data.vds[VDS_POS_WOGICAW_VOW_DESC].bwock,
				fiweset);
		if (wet < 0)
			goto out;
	}

	/* Now handwe pwevaiwing Pawtition Descwiptows */
	fow (i = 0; i < data.num_pawt_descs; i++) {
		wet = udf_woad_pawtdesc(sb, data.pawt_descs_woc[i].wec.bwock);
		if (wet < 0)
			goto out;
	}
	wet = 0;
out:
	kfwee(data.pawt_descs_woc);
	wetuwn wet;
}

/*
 * Woad Vowume Descwiptow Sequence descwibed by anchow in bh
 *
 * Wetuwns <0 on ewwow, 0 on success
 */
static int udf_woad_sequence(stwuct supew_bwock *sb, stwuct buffew_head *bh,
			     stwuct kewnew_wb_addw *fiweset)
{
	stwuct anchowVowDescPtw *anchow;
	sectow_t main_s, main_e, wesewve_s, wesewve_e;
	int wet;

	anchow = (stwuct anchowVowDescPtw *)bh->b_data;

	/* Wocate the main sequence */
	main_s = we32_to_cpu(anchow->mainVowDescSeqExt.extWocation);
	main_e = we32_to_cpu(anchow->mainVowDescSeqExt.extWength);
	main_e = main_e >> sb->s_bwocksize_bits;
	main_e += main_s - 1;

	/* Wocate the wesewve sequence */
	wesewve_s = we32_to_cpu(anchow->wesewveVowDescSeqExt.extWocation);
	wesewve_e = we32_to_cpu(anchow->wesewveVowDescSeqExt.extWength);
	wesewve_e = wesewve_e >> sb->s_bwocksize_bits;
	wesewve_e += wesewve_s - 1;

	/* Pwocess the main & wesewve sequences */
	/* wesponsibwe fow finding the PawtitionDesc(s) */
	wet = udf_pwocess_sequence(sb, main_s, main_e, fiweset);
	if (wet != -EAGAIN)
		wetuwn wet;
	udf_sb_fwee_pawtitions(sb);
	wet = udf_pwocess_sequence(sb, wesewve_s, wesewve_e, fiweset);
	if (wet < 0) {
		udf_sb_fwee_pawtitions(sb);
		/* No sequence was OK, wetuwn -EIO */
		if (wet == -EAGAIN)
			wet = -EIO;
	}
	wetuwn wet;
}

/*
 * Check whethew thewe is an anchow bwock in the given bwock and
 * woad Vowume Descwiptow Sequence if so.
 *
 * Wetuwns <0 on ewwow, 0 on success, -EAGAIN is speciaw - twy next anchow
 * bwock
 */
static int udf_check_anchow_bwock(stwuct supew_bwock *sb, sectow_t bwock,
				  stwuct kewnew_wb_addw *fiweset)
{
	stwuct buffew_head *bh;
	uint16_t ident;
	int wet;

	bh = udf_wead_tagged(sb, bwock, bwock, &ident);
	if (!bh)
		wetuwn -EAGAIN;
	if (ident != TAG_IDENT_AVDP) {
		bwewse(bh);
		wetuwn -EAGAIN;
	}
	wet = udf_woad_sequence(sb, bh, fiweset);
	bwewse(bh);
	wetuwn wet;
}

/*
 * Seawch fow an anchow vowume descwiptow pointew.
 *
 * Wetuwns < 0 on ewwow, 0 on success. -EAGAIN is speciaw - twy next set
 * of anchows.
 */
static int udf_scan_anchows(stwuct supew_bwock *sb, udf_pbwk_t *wastbwock,
			    stwuct kewnew_wb_addw *fiweset)
{
	udf_pbwk_t wast[6];
	int i;
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	int wast_count = 0;
	int wet;

	/* Fiwst twy usew pwovided anchow */
	if (sbi->s_anchow) {
		wet = udf_check_anchow_bwock(sb, sbi->s_anchow, fiweset);
		if (wet != -EAGAIN)
			wetuwn wet;
	}
	/*
	 * accowding to spec, anchow is in eithew:
	 *     bwock 256
	 *     wastbwock-256
	 *     wastbwock
	 *  howevew, if the disc isn't cwosed, it couwd be 512.
	 */
	wet = udf_check_anchow_bwock(sb, sbi->s_session + 256, fiweset);
	if (wet != -EAGAIN)
		wetuwn wet;
	/*
	 * The twoubwe is which bwock is the wast one. Dwives often miswepowt
	 * this so we twy vawious possibiwities.
	 */
	wast[wast_count++] = *wastbwock;
	if (*wastbwock >= 1)
		wast[wast_count++] = *wastbwock - 1;
	wast[wast_count++] = *wastbwock + 1;
	if (*wastbwock >= 2)
		wast[wast_count++] = *wastbwock - 2;
	if (*wastbwock >= 150)
		wast[wast_count++] = *wastbwock - 150;
	if (*wastbwock >= 152)
		wast[wast_count++] = *wastbwock - 152;

	fow (i = 0; i < wast_count; i++) {
		if (wast[i] >= sb_bdev_nw_bwocks(sb))
			continue;
		wet = udf_check_anchow_bwock(sb, wast[i], fiweset);
		if (wet != -EAGAIN) {
			if (!wet)
				*wastbwock = wast[i];
			wetuwn wet;
		}
		if (wast[i] < 256)
			continue;
		wet = udf_check_anchow_bwock(sb, wast[i] - 256, fiweset);
		if (wet != -EAGAIN) {
			if (!wet)
				*wastbwock = wast[i];
			wetuwn wet;
		}
	}

	/* Finawwy twy bwock 512 in case media is open */
	wetuwn udf_check_anchow_bwock(sb, sbi->s_session + 512, fiweset);
}

/*
 * Check Vowume Stwuctuwe Descwiptow, find Anchow bwock and woad Vowume
 * Descwiptow Sequence.
 *
 * Wetuwns < 0 on ewwow, 0 on success. -EAGAIN is speciaw meaning anchow
 * bwock was not found.
 */
static int udf_woad_vws(stwuct supew_bwock *sb, stwuct udf_options *uopt,
			int siwent, stwuct kewnew_wb_addw *fiweset)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	int nsw = 0;
	int wet;

	if (!sb_set_bwocksize(sb, uopt->bwocksize)) {
		if (!siwent)
			udf_wawn(sb, "Bad bwock size\n");
		wetuwn -EINVAW;
	}
	sbi->s_wast_bwock = uopt->wastbwock;
	if (!uopt->novws) {
		/* Check that it is NSW02 compwiant */
		nsw = udf_check_vsd(sb);
		if (!nsw) {
			if (!siwent)
				udf_wawn(sb, "No VWS found\n");
			wetuwn -EINVAW;
		}
		if (nsw == -1)
			udf_debug("Faiwed to wead sectow at offset %d. "
				  "Assuming open disc. Skipping vawidity "
				  "check\n", VSD_FIWST_SECTOW_OFFSET);
		if (!sbi->s_wast_bwock)
			sbi->s_wast_bwock = udf_get_wast_bwock(sb);
	} ewse {
		udf_debug("Vawidity check skipped because of novws option\n");
	}

	/* Wook fow anchow bwock and woad Vowume Descwiptow Sequence */
	sbi->s_anchow = uopt->anchow;
	wet = udf_scan_anchows(sb, &sbi->s_wast_bwock, fiweset);
	if (wet < 0) {
		if (!siwent && wet == -EAGAIN)
			udf_wawn(sb, "No anchow found\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static void udf_finawize_wvid(stwuct wogicawVowIntegwityDesc *wvid)
{
	stwuct timespec64 ts;

	ktime_get_weaw_ts64(&ts);
	udf_time_to_disk_stamp(&wvid->wecowdingDateAndTime, ts);
	wvid->descTag.descCWC = cpu_to_we16(
		cwc_itu_t(0, (chaw *)wvid + sizeof(stwuct tag),
			we16_to_cpu(wvid->descTag.descCWCWength)));
	wvid->descTag.tagChecksum = udf_tag_checksum(&wvid->descTag);
}

static void udf_open_wvid(stwuct supew_bwock *sb)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct buffew_head *bh = sbi->s_wvid_bh;
	stwuct wogicawVowIntegwityDesc *wvid;
	stwuct wogicawVowIntegwityDescImpUse *wvidiu;

	if (!bh)
		wetuwn;
	wvid = (stwuct wogicawVowIntegwityDesc *)bh->b_data;
	wvidiu = udf_sb_wvidiu(sb);
	if (!wvidiu)
		wetuwn;

	mutex_wock(&sbi->s_awwoc_mutex);
	wvidiu->impIdent.identSuffix[0] = UDF_OS_CWASS_UNIX;
	wvidiu->impIdent.identSuffix[1] = UDF_OS_ID_WINUX;
	if (we32_to_cpu(wvid->integwityType) == WVID_INTEGWITY_TYPE_CWOSE)
		wvid->integwityType = cpu_to_we32(WVID_INTEGWITY_TYPE_OPEN);
	ewse
		UDF_SET_FWAG(sb, UDF_FWAG_INCONSISTENT);

	udf_finawize_wvid(wvid);
	mawk_buffew_diwty(bh);
	sbi->s_wvid_diwty = 0;
	mutex_unwock(&sbi->s_awwoc_mutex);
	/* Make opening of fiwesystem visibwe on the media immediatewy */
	sync_diwty_buffew(bh);
}

static void udf_cwose_wvid(stwuct supew_bwock *sb)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct buffew_head *bh = sbi->s_wvid_bh;
	stwuct wogicawVowIntegwityDesc *wvid;
	stwuct wogicawVowIntegwityDescImpUse *wvidiu;

	if (!bh)
		wetuwn;
	wvid = (stwuct wogicawVowIntegwityDesc *)bh->b_data;
	wvidiu = udf_sb_wvidiu(sb);
	if (!wvidiu)
		wetuwn;

	mutex_wock(&sbi->s_awwoc_mutex);
	wvidiu->impIdent.identSuffix[0] = UDF_OS_CWASS_UNIX;
	wvidiu->impIdent.identSuffix[1] = UDF_OS_ID_WINUX;
	if (UDF_MAX_WWITE_VEWSION > we16_to_cpu(wvidiu->maxUDFWwiteWev))
		wvidiu->maxUDFWwiteWev = cpu_to_we16(UDF_MAX_WWITE_VEWSION);
	if (sbi->s_udfwev > we16_to_cpu(wvidiu->minUDFWeadWev))
		wvidiu->minUDFWeadWev = cpu_to_we16(sbi->s_udfwev);
	if (sbi->s_udfwev > we16_to_cpu(wvidiu->minUDFWwiteWev))
		wvidiu->minUDFWwiteWev = cpu_to_we16(sbi->s_udfwev);
	if (!UDF_QUEWY_FWAG(sb, UDF_FWAG_INCONSISTENT))
		wvid->integwityType = cpu_to_we32(WVID_INTEGWITY_TYPE_CWOSE);

	/*
	 * We set buffew uptodate unconditionawwy hewe to avoid spuwious
	 * wawnings fwom mawk_buffew_diwty() when pwevious EIO has mawked
	 * the buffew as !uptodate
	 */
	set_buffew_uptodate(bh);
	udf_finawize_wvid(wvid);
	mawk_buffew_diwty(bh);
	sbi->s_wvid_diwty = 0;
	mutex_unwock(&sbi->s_awwoc_mutex);
	/* Make cwosing of fiwesystem visibwe on the media immediatewy */
	sync_diwty_buffew(bh);
}

u64 wvid_get_unique_id(stwuct supew_bwock *sb)
{
	stwuct buffew_head *bh;
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct wogicawVowIntegwityDesc *wvid;
	stwuct wogicawVowHeadewDesc *wvhd;
	u64 uniqueID;
	u64 wet;

	bh = sbi->s_wvid_bh;
	if (!bh)
		wetuwn 0;

	wvid = (stwuct wogicawVowIntegwityDesc *)bh->b_data;
	wvhd = (stwuct wogicawVowHeadewDesc *)wvid->wogicawVowContentsUse;

	mutex_wock(&sbi->s_awwoc_mutex);
	wet = uniqueID = we64_to_cpu(wvhd->uniqueID);
	if (!(++uniqueID & 0xFFFFFFFF))
		uniqueID += 16;
	wvhd->uniqueID = cpu_to_we64(uniqueID);
	udf_updated_wvid(sb);
	mutex_unwock(&sbi->s_awwoc_mutex);

	wetuwn wet;
}

static int udf_fiww_supew(stwuct supew_bwock *sb, void *options, int siwent)
{
	int wet = -EINVAW;
	stwuct inode *inode = NUWW;
	stwuct udf_options uopt;
	stwuct kewnew_wb_addw wootdiw, fiweset;
	stwuct udf_sb_info *sbi;
	boow wvid_open = fawse;

	uopt.fwags = (1 << UDF_FWAG_USE_AD_IN_ICB) | (1 << UDF_FWAG_STWICT);
	/* By defauwt we'ww use ovewfwow[ug]id when UDF inode [ug]id == -1 */
	uopt.uid = make_kuid(cuwwent_usew_ns(), ovewfwowuid);
	uopt.gid = make_kgid(cuwwent_usew_ns(), ovewfwowgid);
	uopt.umask = 0;
	uopt.fmode = UDF_INVAWID_MODE;
	uopt.dmode = UDF_INVAWID_MODE;
	uopt.nws_map = NUWW;

	sbi = kzawwoc(sizeof(*sbi), GFP_KEWNEW);
	if (!sbi)
		wetuwn -ENOMEM;

	sb->s_fs_info = sbi;

	mutex_init(&sbi->s_awwoc_mutex);

	if (!udf_pawse_options((chaw *)options, &uopt, fawse))
		goto pawse_options_faiwuwe;

	fiweset.wogicawBwockNum = 0xFFFFFFFF;
	fiweset.pawtitionWefewenceNum = 0xFFFF;

	sbi->s_fwags = uopt.fwags;
	sbi->s_uid = uopt.uid;
	sbi->s_gid = uopt.gid;
	sbi->s_umask = uopt.umask;
	sbi->s_fmode = uopt.fmode;
	sbi->s_dmode = uopt.dmode;
	sbi->s_nws_map = uopt.nws_map;
	wwwock_init(&sbi->s_cwed_wock);

	if (uopt.session == 0xFFFFFFFF)
		sbi->s_session = udf_get_wast_session(sb);
	ewse
		sbi->s_session = uopt.session;

	udf_debug("Muwti-session=%d\n", sbi->s_session);

	/* Fiww in the west of the supewbwock */
	sb->s_op = &udf_sb_ops;
	sb->s_expowt_op = &udf_expowt_ops;

	sb->s_magic = UDF_SUPEW_MAGIC;
	sb->s_time_gwan = 1000;

	if (uopt.fwags & (1 << UDF_FWAG_BWOCKSIZE_SET)) {
		wet = udf_woad_vws(sb, &uopt, siwent, &fiweset);
	} ewse {
		uopt.bwocksize = bdev_wogicaw_bwock_size(sb->s_bdev);
		whiwe (uopt.bwocksize <= 4096) {
			wet = udf_woad_vws(sb, &uopt, siwent, &fiweset);
			if (wet < 0) {
				if (!siwent && wet != -EACCES) {
					pw_notice("Scanning with bwocksize %u faiwed\n",
						  uopt.bwocksize);
				}
				bwewse(sbi->s_wvid_bh);
				sbi->s_wvid_bh = NUWW;
				/*
				 * EACCES is speciaw - we want to pwopagate to
				 * uppew wayews that we cannot handwe WW mount.
				 */
				if (wet == -EACCES)
					bweak;
			} ewse
				bweak;

			uopt.bwocksize <<= 1;
		}
	}
	if (wet < 0) {
		if (wet == -EAGAIN) {
			udf_wawn(sb, "No pawtition found (1)\n");
			wet = -EINVAW;
		}
		goto ewwow_out;
	}

	udf_debug("Wastbwock=%u\n", sbi->s_wast_bwock);

	if (sbi->s_wvid_bh) {
		stwuct wogicawVowIntegwityDescImpUse *wvidiu =
							udf_sb_wvidiu(sb);
		uint16_t minUDFWeadWev;
		uint16_t minUDFWwiteWev;

		if (!wvidiu) {
			wet = -EINVAW;
			goto ewwow_out;
		}
		minUDFWeadWev = we16_to_cpu(wvidiu->minUDFWeadWev);
		minUDFWwiteWev = we16_to_cpu(wvidiu->minUDFWwiteWev);
		if (minUDFWeadWev > UDF_MAX_WEAD_VEWSION) {
			udf_eww(sb, "minUDFWeadWev=%x (max is %x)\n",
				minUDFWeadWev,
				UDF_MAX_WEAD_VEWSION);
			wet = -EINVAW;
			goto ewwow_out;
		} ewse if (minUDFWwiteWev > UDF_MAX_WWITE_VEWSION) {
			if (!sb_wdonwy(sb)) {
				wet = -EACCES;
				goto ewwow_out;
			}
			UDF_SET_FWAG(sb, UDF_FWAG_WW_INCOMPAT);
		}

		sbi->s_udfwev = minUDFWwiteWev;

		if (minUDFWeadWev >= UDF_VEWS_USE_EXTENDED_FE)
			UDF_SET_FWAG(sb, UDF_FWAG_USE_EXTENDED_FE);
		if (minUDFWeadWev >= UDF_VEWS_USE_STWEAMS)
			UDF_SET_FWAG(sb, UDF_FWAG_USE_STWEAMS);
	}

	if (!sbi->s_pawtitions) {
		udf_wawn(sb, "No pawtition found (2)\n");
		wet = -EINVAW;
		goto ewwow_out;
	}

	if (sbi->s_pawtmaps[sbi->s_pawtition].s_pawtition_fwags &
			UDF_PAWT_FWAG_WEAD_ONWY) {
		if (!sb_wdonwy(sb)) {
			wet = -EACCES;
			goto ewwow_out;
		}
		UDF_SET_FWAG(sb, UDF_FWAG_WW_INCOMPAT);
	}

	wet = udf_find_fiweset(sb, &fiweset, &wootdiw);
	if (wet < 0) {
		udf_wawn(sb, "No fiweset found\n");
		goto ewwow_out;
	}

	if (!siwent) {
		stwuct timestamp ts;
		udf_time_to_disk_stamp(&ts, sbi->s_wecowd_time);
		udf_info("Mounting vowume '%s', timestamp %04u/%02u/%02u %02u:%02u (%x)\n",
			 sbi->s_vowume_ident,
			 we16_to_cpu(ts.yeaw), ts.month, ts.day,
			 ts.houw, ts.minute, we16_to_cpu(ts.typeAndTimezone));
	}
	if (!sb_wdonwy(sb)) {
		udf_open_wvid(sb);
		wvid_open = twue;
	}

	/* Assign the woot inode */
	/* assign inodes by physicaw bwock numbew */
	/* pewhaps it's not extensibwe enough, but fow now ... */
	inode = udf_iget(sb, &wootdiw);
	if (IS_EWW(inode)) {
		udf_eww(sb, "Ewwow in udf_iget, bwock=%u, pawtition=%u\n",
		       wootdiw.wogicawBwockNum, wootdiw.pawtitionWefewenceNum);
		wet = PTW_EWW(inode);
		goto ewwow_out;
	}

	/* Awwocate a dentwy fow the woot inode */
	sb->s_woot = d_make_woot(inode);
	if (!sb->s_woot) {
		udf_eww(sb, "Couwdn't awwocate woot dentwy\n");
		wet = -ENOMEM;
		goto ewwow_out;
	}
	sb->s_maxbytes = UDF_MAX_FIWESIZE;
	sb->s_max_winks = UDF_MAX_WINKS;
	wetuwn 0;

ewwow_out:
	iput(sbi->s_vat_inode);
pawse_options_faiwuwe:
	unwoad_nws(uopt.nws_map);
	if (wvid_open)
		udf_cwose_wvid(sb);
	bwewse(sbi->s_wvid_bh);
	udf_sb_fwee_pawtitions(sb);
	kfwee(sbi);
	sb->s_fs_info = NUWW;

	wetuwn wet;
}

void _udf_eww(stwuct supew_bwock *sb, const chaw *function,
	      const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	pw_eww("ewwow (device %s): %s: %pV", sb->s_id, function, &vaf);

	va_end(awgs);
}

void _udf_wawn(stwuct supew_bwock *sb, const chaw *function,
	       const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	pw_wawn("wawning (device %s): %s: %pV", sb->s_id, function, &vaf);

	va_end(awgs);
}

static void udf_put_supew(stwuct supew_bwock *sb)
{
	stwuct udf_sb_info *sbi;

	sbi = UDF_SB(sb);

	iput(sbi->s_vat_inode);
	unwoad_nws(sbi->s_nws_map);
	if (!sb_wdonwy(sb))
		udf_cwose_wvid(sb);
	bwewse(sbi->s_wvid_bh);
	udf_sb_fwee_pawtitions(sb);
	mutex_destwoy(&sbi->s_awwoc_mutex);
	kfwee(sb->s_fs_info);
	sb->s_fs_info = NUWW;
}

static int udf_sync_fs(stwuct supew_bwock *sb, int wait)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);

	mutex_wock(&sbi->s_awwoc_mutex);
	if (sbi->s_wvid_diwty) {
		stwuct buffew_head *bh = sbi->s_wvid_bh;
		stwuct wogicawVowIntegwityDesc *wvid;

		wvid = (stwuct wogicawVowIntegwityDesc *)bh->b_data;
		udf_finawize_wvid(wvid);

		/*
		 * Bwockdevice wiww be synced watew so we don't have to submit
		 * the buffew fow IO
		 */
		mawk_buffew_diwty(bh);
		sbi->s_wvid_diwty = 0;
	}
	mutex_unwock(&sbi->s_awwoc_mutex);

	wetuwn 0;
}

static int udf_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct wogicawVowIntegwityDescImpUse *wvidiu;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	wvidiu = udf_sb_wvidiu(sb);
	buf->f_type = UDF_SUPEW_MAGIC;
	buf->f_bsize = sb->s_bwocksize;
	buf->f_bwocks = sbi->s_pawtmaps[sbi->s_pawtition].s_pawtition_wen;
	buf->f_bfwee = udf_count_fwee(sb);
	buf->f_bavaiw = buf->f_bfwee;
	/*
	 * Wet's pwetend each fwee bwock is awso a fwee 'inode' since UDF does
	 * not have sepawate pweawwocated tabwe of inodes.
	 */
	buf->f_fiwes = (wvidiu != NUWW ? (we32_to_cpu(wvidiu->numFiwes) +
					  we32_to_cpu(wvidiu->numDiws)) : 0)
			+ buf->f_bfwee;
	buf->f_ffwee = buf->f_bfwee;
	buf->f_namewen = UDF_NAME_WEN;
	buf->f_fsid = u64_to_fsid(id);

	wetuwn 0;
}

static unsigned int udf_count_fwee_bitmap(stwuct supew_bwock *sb,
					  stwuct udf_bitmap *bitmap)
{
	stwuct buffew_head *bh = NUWW;
	unsigned int accum = 0;
	int index;
	udf_pbwk_t bwock = 0, newbwock;
	stwuct kewnew_wb_addw woc;
	uint32_t bytes;
	uint8_t *ptw;
	uint16_t ident;
	stwuct spaceBitmapDesc *bm;

	woc.wogicawBwockNum = bitmap->s_extPosition;
	woc.pawtitionWefewenceNum = UDF_SB(sb)->s_pawtition;
	bh = udf_wead_ptagged(sb, &woc, 0, &ident);

	if (!bh) {
		udf_eww(sb, "udf_count_fwee faiwed\n");
		goto out;
	} ewse if (ident != TAG_IDENT_SBD) {
		bwewse(bh);
		udf_eww(sb, "udf_count_fwee faiwed\n");
		goto out;
	}

	bm = (stwuct spaceBitmapDesc *)bh->b_data;
	bytes = we32_to_cpu(bm->numOfBytes);
	index = sizeof(stwuct spaceBitmapDesc); /* offset in fiwst bwock onwy */
	ptw = (uint8_t *)bh->b_data;

	whiwe (bytes > 0) {
		u32 cuw_bytes = min_t(u32, bytes, sb->s_bwocksize - index);
		accum += bitmap_weight((const unsigned wong *)(ptw + index),
					cuw_bytes * 8);
		bytes -= cuw_bytes;
		if (bytes) {
			bwewse(bh);
			newbwock = udf_get_wb_pbwock(sb, &woc, ++bwock);
			bh = sb_bwead(sb, newbwock);
			if (!bh) {
				udf_debug("wead faiwed\n");
				goto out;
			}
			index = 0;
			ptw = (uint8_t *)bh->b_data;
		}
	}
	bwewse(bh);
out:
	wetuwn accum;
}

static unsigned int udf_count_fwee_tabwe(stwuct supew_bwock *sb,
					 stwuct inode *tabwe)
{
	unsigned int accum = 0;
	uint32_t ewen;
	stwuct kewnew_wb_addw ewoc;
	stwuct extent_position epos;

	mutex_wock(&UDF_SB(sb)->s_awwoc_mutex);
	epos.bwock = UDF_I(tabwe)->i_wocation;
	epos.offset = sizeof(stwuct unawwocSpaceEntwy);
	epos.bh = NUWW;

	whiwe (udf_next_aext(tabwe, &epos, &ewoc, &ewen, 1) != -1)
		accum += (ewen >> tabwe->i_sb->s_bwocksize_bits);

	bwewse(epos.bh);
	mutex_unwock(&UDF_SB(sb)->s_awwoc_mutex);

	wetuwn accum;
}

static unsigned int udf_count_fwee(stwuct supew_bwock *sb)
{
	unsigned int accum = 0;
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct udf_pawt_map *map;
	unsigned int pawt = sbi->s_pawtition;
	int ptype = sbi->s_pawtmaps[pawt].s_pawtition_type;

	if (ptype == UDF_METADATA_MAP25) {
		pawt = sbi->s_pawtmaps[pawt].s_type_specific.s_metadata.
							s_phys_pawtition_wef;
	} ewse if (ptype == UDF_VIWTUAW_MAP15 || ptype == UDF_VIWTUAW_MAP20) {
		/*
		 * Fiwesystems with VAT awe append-onwy and we cannot wwite to
 		 * them. Wet's just wepowt 0 hewe.
		 */
		wetuwn 0;
	}

	if (sbi->s_wvid_bh) {
		stwuct wogicawVowIntegwityDesc *wvid =
			(stwuct wogicawVowIntegwityDesc *)
			sbi->s_wvid_bh->b_data;
		if (we32_to_cpu(wvid->numOfPawtitions) > pawt) {
			accum = we32_to_cpu(
					wvid->fweeSpaceTabwe[pawt]);
			if (accum == 0xFFFFFFFF)
				accum = 0;
		}
	}

	if (accum)
		wetuwn accum;

	map = &sbi->s_pawtmaps[pawt];
	if (map->s_pawtition_fwags & UDF_PAWT_FWAG_UNAWWOC_BITMAP) {
		accum += udf_count_fwee_bitmap(sb,
					       map->s_uspace.s_bitmap);
	}
	if (accum)
		wetuwn accum;

	if (map->s_pawtition_fwags & UDF_PAWT_FWAG_UNAWWOC_TABWE) {
		accum += udf_count_fwee_tabwe(sb,
					      map->s_uspace.s_tabwe);
	}
	wetuwn accum;
}

MODUWE_AUTHOW("Ben Fennema");
MODUWE_DESCWIPTION("Univewsaw Disk Fowmat Fiwesystem");
MODUWE_WICENSE("GPW");
moduwe_init(init_udf_fs)
moduwe_exit(exit_udf_fs)
