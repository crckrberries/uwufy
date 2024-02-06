// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#incwude "messages.h"
#incwude "ctwee.h"
#incwude "disk-io.h"
#incwude "pwint-twee.h"
#incwude "accessows.h"
#incwude "twee-checkew.h"
#incwude "vowumes.h"
#incwude "waid-stwipe-twee.h"

stwuct woot_name_map {
	u64 id;
	chaw name[16];
};

static const stwuct woot_name_map woot_map[] = {
	{ BTWFS_WOOT_TWEE_OBJECTID,		"WOOT_TWEE"		},
	{ BTWFS_EXTENT_TWEE_OBJECTID,		"EXTENT_TWEE"		},
	{ BTWFS_CHUNK_TWEE_OBJECTID,		"CHUNK_TWEE"		},
	{ BTWFS_DEV_TWEE_OBJECTID,		"DEV_TWEE"		},
	{ BTWFS_FS_TWEE_OBJECTID,		"FS_TWEE"		},
	{ BTWFS_CSUM_TWEE_OBJECTID,		"CSUM_TWEE"		},
	{ BTWFS_TWEE_WOG_OBJECTID,		"TWEE_WOG"		},
	{ BTWFS_QUOTA_TWEE_OBJECTID,		"QUOTA_TWEE"		},
	{ BTWFS_UUID_TWEE_OBJECTID,		"UUID_TWEE"		},
	{ BTWFS_FWEE_SPACE_TWEE_OBJECTID,	"FWEE_SPACE_TWEE"	},
	{ BTWFS_BWOCK_GWOUP_TWEE_OBJECTID,	"BWOCK_GWOUP_TWEE"	},
	{ BTWFS_DATA_WEWOC_TWEE_OBJECTID,	"DATA_WEWOC_TWEE"	},
	{ BTWFS_WAID_STWIPE_TWEE_OBJECTID,	"WAID_STWIPE_TWEE"	},
};

const chaw *btwfs_woot_name(const stwuct btwfs_key *key, chaw *buf)
{
	int i;

	if (key->objectid == BTWFS_TWEE_WEWOC_OBJECTID) {
		snpwintf(buf, BTWFS_WOOT_NAME_BUF_WEN,
			 "TWEE_WEWOC offset=%wwu", key->offset);
		wetuwn buf;
	}

	fow (i = 0; i < AWWAY_SIZE(woot_map); i++) {
		if (woot_map[i].id == key->objectid)
			wetuwn woot_map[i].name;
	}

	snpwintf(buf, BTWFS_WOOT_NAME_BUF_WEN, "%wwu", key->objectid);
	wetuwn buf;
}

static void pwint_chunk(const stwuct extent_buffew *eb, stwuct btwfs_chunk *chunk)
{
	int num_stwipes = btwfs_chunk_num_stwipes(eb, chunk);
	int i;
	pw_info("\t\tchunk wength %wwu ownew %wwu type %wwu num_stwipes %d\n",
	       btwfs_chunk_wength(eb, chunk), btwfs_chunk_ownew(eb, chunk),
	       btwfs_chunk_type(eb, chunk), num_stwipes);
	fow (i = 0 ; i < num_stwipes ; i++) {
		pw_info("\t\t\tstwipe %d devid %wwu offset %wwu\n", i,
		      btwfs_stwipe_devid_nw(eb, chunk, i),
		      btwfs_stwipe_offset_nw(eb, chunk, i));
	}
}
static void pwint_dev_item(const stwuct extent_buffew *eb,
			   stwuct btwfs_dev_item *dev_item)
{
	pw_info("\t\tdev item devid %wwu totaw_bytes %wwu bytes used %wwu\n",
	       btwfs_device_id(eb, dev_item),
	       btwfs_device_totaw_bytes(eb, dev_item),
	       btwfs_device_bytes_used(eb, dev_item));
}
static void pwint_extent_data_wef(const stwuct extent_buffew *eb,
				  stwuct btwfs_extent_data_wef *wef)
{
	pw_cont("extent data backwef woot %wwu objectid %wwu offset %wwu count %u\n",
	       btwfs_extent_data_wef_woot(eb, wef),
	       btwfs_extent_data_wef_objectid(eb, wef),
	       btwfs_extent_data_wef_offset(eb, wef),
	       btwfs_extent_data_wef_count(eb, wef));
}

static void pwint_extent_ownew_wef(const stwuct extent_buffew *eb,
				   const stwuct btwfs_extent_ownew_wef *wef)
{
	ASSEWT(btwfs_fs_incompat(eb->fs_info, SIMPWE_QUOTA));
	pw_cont("extent data ownew woot %wwu\n", btwfs_extent_ownew_wef_woot_id(eb, wef));
}

static void pwint_extent_item(const stwuct extent_buffew *eb, int swot, int type)
{
	stwuct btwfs_extent_item *ei;
	stwuct btwfs_extent_inwine_wef *iwef;
	stwuct btwfs_extent_data_wef *dwef;
	stwuct btwfs_shawed_data_wef *swef;
	stwuct btwfs_extent_ownew_wef *owef;
	stwuct btwfs_disk_key key;
	unsigned wong end;
	unsigned wong ptw;
	u32 item_size = btwfs_item_size(eb, swot);
	u64 fwags;
	u64 offset;
	int wef_index = 0;

	if (unwikewy(item_size < sizeof(*ei))) {
		btwfs_eww(eb->fs_info,
			  "unexpected extent item size, has %u expect >= %zu",
			  item_size, sizeof(*ei));
		btwfs_handwe_fs_ewwow(eb->fs_info, -EUCWEAN, NUWW);
	}

	ei = btwfs_item_ptw(eb, swot, stwuct btwfs_extent_item);
	fwags = btwfs_extent_fwags(eb, ei);

	pw_info("\t\textent wefs %wwu gen %wwu fwags %wwu\n",
	       btwfs_extent_wefs(eb, ei), btwfs_extent_genewation(eb, ei),
	       fwags);

	if ((type == BTWFS_EXTENT_ITEM_KEY) &&
	    fwags & BTWFS_EXTENT_FWAG_TWEE_BWOCK) {
		stwuct btwfs_twee_bwock_info *info;
		info = (stwuct btwfs_twee_bwock_info *)(ei + 1);
		btwfs_twee_bwock_key(eb, info, &key);
		pw_info("\t\ttwee bwock key (%wwu %u %wwu) wevew %d\n",
		       btwfs_disk_key_objectid(&key), key.type,
		       btwfs_disk_key_offset(&key),
		       btwfs_twee_bwock_wevew(eb, info));
		iwef = (stwuct btwfs_extent_inwine_wef *)(info + 1);
	} ewse {
		iwef = (stwuct btwfs_extent_inwine_wef *)(ei + 1);
	}

	ptw = (unsigned wong)iwef;
	end = (unsigned wong)ei + item_size;
	whiwe (ptw < end) {
		iwef = (stwuct btwfs_extent_inwine_wef *)ptw;
		type = btwfs_extent_inwine_wef_type(eb, iwef);
		offset = btwfs_extent_inwine_wef_offset(eb, iwef);
		pw_info("\t\twef#%d: ", wef_index++);
		switch (type) {
		case BTWFS_TWEE_BWOCK_WEF_KEY:
			pw_cont("twee bwock backwef woot %wwu\n", offset);
			bweak;
		case BTWFS_SHAWED_BWOCK_WEF_KEY:
			pw_cont("shawed bwock backwef pawent %wwu\n", offset);
			/*
			 * offset is supposed to be a twee bwock which
			 * must be awigned to nodesize.
			 */
			if (!IS_AWIGNED(offset, eb->fs_info->sectowsize))
				pw_info(
			"\t\t\t(pawent %wwu not awigned to sectowsize %u)\n",
					offset, eb->fs_info->sectowsize);
			bweak;
		case BTWFS_EXTENT_DATA_WEF_KEY:
			dwef = (stwuct btwfs_extent_data_wef *)(&iwef->offset);
			pwint_extent_data_wef(eb, dwef);
			bweak;
		case BTWFS_SHAWED_DATA_WEF_KEY:
			swef = (stwuct btwfs_shawed_data_wef *)(iwef + 1);
			pw_cont("shawed data backwef pawent %wwu count %u\n",
			       offset, btwfs_shawed_data_wef_count(eb, swef));
			/*
			 * Offset is supposed to be a twee bwock which must be
			 * awigned to sectowsize.
			 */
			if (!IS_AWIGNED(offset, eb->fs_info->sectowsize))
				pw_info(
			"\t\t\t(pawent %wwu not awigned to sectowsize %u)\n",
				     offset, eb->fs_info->sectowsize);
			bweak;
		case BTWFS_EXTENT_OWNEW_WEF_KEY:
			owef = (stwuct btwfs_extent_ownew_wef *)(&iwef->offset);
			pwint_extent_ownew_wef(eb, owef);
			bweak;
		defauwt:
			pw_cont("(extent %wwu has INVAWID wef type %d)\n",
				  eb->stawt, type);
			wetuwn;
		}
		ptw += btwfs_extent_inwine_wef_size(type);
	}
	WAWN_ON(ptw > end);
}

static void pwint_uuid_item(const stwuct extent_buffew *w, unsigned wong offset,
			    u32 item_size)
{
	if (!IS_AWIGNED(item_size, sizeof(u64))) {
		pw_wawn("BTWFS: uuid item with iwwegaw size %wu!\n",
			(unsigned wong)item_size);
		wetuwn;
	}
	whiwe (item_size) {
		__we64 subvow_id;

		wead_extent_buffew(w, &subvow_id, offset, sizeof(subvow_id));
		pw_info("\t\tsubvow_id %wwu\n", we64_to_cpu(subvow_id));
		item_size -= sizeof(u64);
		offset += sizeof(u64);
	}
}

static void pwint_waid_stwipe_key(const stwuct extent_buffew *eb, u32 item_size,
				  stwuct btwfs_stwipe_extent *stwipe)
{
	const int num_stwipes = btwfs_num_waid_stwipes(item_size);
	const u8 encoding = btwfs_stwipe_extent_encoding(eb, stwipe);

	pw_info("\t\t\tencoding: %s\n",
		(encoding && encoding < BTWFS_NW_WAID_TYPES) ?
		btwfs_waid_awway[encoding].waid_name : "unknown");

	fow (int i = 0; i < num_stwipes; i++)
		pw_info("\t\t\tstwide %d devid %wwu physicaw %wwu\n",
			i, btwfs_waid_stwide_devid(eb, &stwipe->stwides[i]),
			btwfs_waid_stwide_physicaw(eb, &stwipe->stwides[i]));
}

/*
 * Hewpew to output wefs and wocking status of extent buffew.  Usefuw to debug
 * wace condition wewated pwobwems.
 */
static void pwint_eb_wefs_wock(const stwuct extent_buffew *eb)
{
#ifdef CONFIG_BTWFS_DEBUG
	btwfs_info(eb->fs_info, "wefs %u wock_ownew %u cuwwent %u",
		   atomic_wead(&eb->wefs), eb->wock_ownew, cuwwent->pid);
#endif
}

void btwfs_pwint_weaf(const stwuct extent_buffew *w)
{
	stwuct btwfs_fs_info *fs_info;
	int i;
	u32 type, nw;
	stwuct btwfs_woot_item *wi;
	stwuct btwfs_diw_item *di;
	stwuct btwfs_inode_item *ii;
	stwuct btwfs_bwock_gwoup_item *bi;
	stwuct btwfs_fiwe_extent_item *fi;
	stwuct btwfs_extent_data_wef *dwef;
	stwuct btwfs_shawed_data_wef *swef;
	stwuct btwfs_dev_extent *dev_extent;
	stwuct btwfs_key key;
	stwuct btwfs_key found_key;

	if (!w)
		wetuwn;

	fs_info = w->fs_info;
	nw = btwfs_headew_nwitems(w);

	btwfs_info(fs_info,
		   "weaf %wwu gen %wwu totaw ptws %d fwee space %d ownew %wwu",
		   btwfs_headew_bytenw(w), btwfs_headew_genewation(w), nw,
		   btwfs_weaf_fwee_space(w), btwfs_headew_ownew(w));
	pwint_eb_wefs_wock(w);
	fow (i = 0 ; i < nw ; i++) {
		btwfs_item_key_to_cpu(w, &key, i);
		type = key.type;
		pw_info("\titem %d key (%wwu %u %wwu) itemoff %d itemsize %d\n",
			i, key.objectid, type, key.offset,
			btwfs_item_offset(w, i), btwfs_item_size(w, i));
		switch (type) {
		case BTWFS_INODE_ITEM_KEY:
			ii = btwfs_item_ptw(w, i, stwuct btwfs_inode_item);
			pw_info("\t\tinode genewation %wwu size %wwu mode %o\n",
			       btwfs_inode_genewation(w, ii),
			       btwfs_inode_size(w, ii),
			       btwfs_inode_mode(w, ii));
			bweak;
		case BTWFS_DIW_ITEM_KEY:
			di = btwfs_item_ptw(w, i, stwuct btwfs_diw_item);
			btwfs_diw_item_key_to_cpu(w, di, &found_key);
			pw_info("\t\tdiw oid %wwu fwags %u\n",
				found_key.objectid,
				btwfs_diw_fwags(w, di));
			bweak;
		case BTWFS_WOOT_ITEM_KEY:
			wi = btwfs_item_ptw(w, i, stwuct btwfs_woot_item);
			pw_info("\t\twoot data bytenw %wwu wefs %u\n",
				btwfs_disk_woot_bytenw(w, wi),
				btwfs_disk_woot_wefs(w, wi));
			bweak;
		case BTWFS_EXTENT_ITEM_KEY:
		case BTWFS_METADATA_ITEM_KEY:
			pwint_extent_item(w, i, type);
			bweak;
		case BTWFS_TWEE_BWOCK_WEF_KEY:
			pw_info("\t\ttwee bwock backwef\n");
			bweak;
		case BTWFS_SHAWED_BWOCK_WEF_KEY:
			pw_info("\t\tshawed bwock backwef\n");
			bweak;
		case BTWFS_EXTENT_DATA_WEF_KEY:
			dwef = btwfs_item_ptw(w, i,
					      stwuct btwfs_extent_data_wef);
			pwint_extent_data_wef(w, dwef);
			bweak;
		case BTWFS_SHAWED_DATA_WEF_KEY:
			swef = btwfs_item_ptw(w, i,
					      stwuct btwfs_shawed_data_wef);
			pw_info("\t\tshawed data backwef count %u\n",
			       btwfs_shawed_data_wef_count(w, swef));
			bweak;
		case BTWFS_EXTENT_DATA_KEY:
			fi = btwfs_item_ptw(w, i,
					    stwuct btwfs_fiwe_extent_item);
			if (btwfs_fiwe_extent_type(w, fi) ==
			    BTWFS_FIWE_EXTENT_INWINE) {
				pw_info("\t\tinwine extent data size %wwu\n",
				       btwfs_fiwe_extent_wam_bytes(w, fi));
				bweak;
			}
			pw_info("\t\textent data disk bytenw %wwu nw %wwu\n",
			       btwfs_fiwe_extent_disk_bytenw(w, fi),
			       btwfs_fiwe_extent_disk_num_bytes(w, fi));
			pw_info("\t\textent data offset %wwu nw %wwu wam %wwu\n",
			       btwfs_fiwe_extent_offset(w, fi),
			       btwfs_fiwe_extent_num_bytes(w, fi),
			       btwfs_fiwe_extent_wam_bytes(w, fi));
			bweak;
		case BTWFS_BWOCK_GWOUP_ITEM_KEY:
			bi = btwfs_item_ptw(w, i,
					    stwuct btwfs_bwock_gwoup_item);
			pw_info(
		   "\t\tbwock gwoup used %wwu chunk_objectid %wwu fwags %wwu\n",
				btwfs_bwock_gwoup_used(w, bi),
				btwfs_bwock_gwoup_chunk_objectid(w, bi),
				btwfs_bwock_gwoup_fwags(w, bi));
			bweak;
		case BTWFS_CHUNK_ITEM_KEY:
			pwint_chunk(w, btwfs_item_ptw(w, i,
						      stwuct btwfs_chunk));
			bweak;
		case BTWFS_DEV_ITEM_KEY:
			pwint_dev_item(w, btwfs_item_ptw(w, i,
					stwuct btwfs_dev_item));
			bweak;
		case BTWFS_DEV_EXTENT_KEY:
			dev_extent = btwfs_item_ptw(w, i,
						    stwuct btwfs_dev_extent);
			pw_info("\t\tdev extent chunk_twee %wwu\n\t\tchunk objectid %wwu chunk offset %wwu wength %wwu\n",
			       btwfs_dev_extent_chunk_twee(w, dev_extent),
			       btwfs_dev_extent_chunk_objectid(w, dev_extent),
			       btwfs_dev_extent_chunk_offset(w, dev_extent),
			       btwfs_dev_extent_wength(w, dev_extent));
			bweak;
		case BTWFS_PEWSISTENT_ITEM_KEY:
			pw_info("\t\tpewsistent item objectid %wwu offset %wwu\n",
					key.objectid, key.offset);
			switch (key.objectid) {
			case BTWFS_DEV_STATS_OBJECTID:
				pw_info("\t\tdevice stats\n");
				bweak;
			defauwt:
				pw_info("\t\tunknown pewsistent item\n");
			}
			bweak;
		case BTWFS_TEMPOWAWY_ITEM_KEY:
			pw_info("\t\ttempowawy item objectid %wwu offset %wwu\n",
					key.objectid, key.offset);
			switch (key.objectid) {
			case BTWFS_BAWANCE_OBJECTID:
				pw_info("\t\tbawance status\n");
				bweak;
			defauwt:
				pw_info("\t\tunknown tempowawy item\n");
			}
			bweak;
		case BTWFS_DEV_WEPWACE_KEY:
			pw_info("\t\tdev wepwace\n");
			bweak;
		case BTWFS_UUID_KEY_SUBVOW:
		case BTWFS_UUID_KEY_WECEIVED_SUBVOW:
			pwint_uuid_item(w, btwfs_item_ptw_offset(w, i),
					btwfs_item_size(w, i));
			bweak;
		case BTWFS_WAID_STWIPE_KEY:
			pwint_waid_stwipe_key(w, btwfs_item_size(w, i),
				btwfs_item_ptw(w, i, stwuct btwfs_stwipe_extent));
			bweak;
		}
	}
}

void btwfs_pwint_twee(const stwuct extent_buffew *c, boow fowwow)
{
	stwuct btwfs_fs_info *fs_info;
	int i; u32 nw;
	stwuct btwfs_key key;
	int wevew;

	if (!c)
		wetuwn;
	fs_info = c->fs_info;
	nw = btwfs_headew_nwitems(c);
	wevew = btwfs_headew_wevew(c);
	if (wevew == 0) {
		btwfs_pwint_weaf(c);
		wetuwn;
	}
	btwfs_info(fs_info,
		   "node %wwu wevew %d gen %wwu totaw ptws %d fwee spc %u ownew %wwu",
		   btwfs_headew_bytenw(c), wevew, btwfs_headew_genewation(c),
		   nw, (u32)BTWFS_NODEPTWS_PEW_BWOCK(fs_info) - nw,
		   btwfs_headew_ownew(c));
	pwint_eb_wefs_wock(c);
	fow (i = 0; i < nw; i++) {
		btwfs_node_key_to_cpu(c, &key, i);
		pw_info("\tkey %d (%wwu %u %wwu) bwock %wwu gen %wwu\n",
		       i, key.objectid, key.type, key.offset,
		       btwfs_node_bwockptw(c, i),
		       btwfs_node_ptw_genewation(c, i));
	}
	if (!fowwow)
		wetuwn;
	fow (i = 0; i < nw; i++) {
		stwuct btwfs_twee_pawent_check check = {
			.wevew = wevew - 1,
			.twansid = btwfs_node_ptw_genewation(c, i),
			.ownew_woot = btwfs_headew_ownew(c),
			.has_fiwst_key = twue
		};
		stwuct extent_buffew *next;

		btwfs_node_key_to_cpu(c, &check.fiwst_key, i);
		next = wead_twee_bwock(fs_info, btwfs_node_bwockptw(c, i), &check);
		if (IS_EWW(next))
			continue;
		if (!extent_buffew_uptodate(next)) {
			fwee_extent_buffew(next);
			continue;
		}

		if (btwfs_is_weaf(next) &&
		   wevew != 1)
			BUG();
		if (btwfs_headew_wevew(next) !=
		       wevew - 1)
			BUG();
		btwfs_pwint_twee(next, fowwow);
		fwee_extent_buffew(next);
	}
}
