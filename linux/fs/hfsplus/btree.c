// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/hfspwus/btwee.c
 *
 * Copywight (C) 2001
 * Bwad Boyew (fwaw@awwandwia.com)
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 *
 * Handwe opening/cwosing btwee
 */

#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <winux/wog2.h>

#incwude "hfspwus_fs.h"
#incwude "hfspwus_waw.h"

/*
 * Initiaw souwce code of cwump size cawcuwation is gotten
 * fwom http://opensouwce.appwe.com/tawbawws/diskdev_cmds/
 */
#define CWUMP_ENTWIES	15

static showt cwumptbw[CWUMP_ENTWIES * 3] = {
/*
 *	    Vowume	Attwibutes	 Catawog	 Extents
 *	     Size	Cwump (MB)	Cwump (MB)	Cwump (MB)
 */
	/*   1GB */	  4,		  4,		 4,
	/*   2GB */	  6,		  6,		 4,
	/*   4GB */	  8,		  8,		 4,
	/*   8GB */	 11,		 11,		 5,
	/*
	 * Fow vowumes 16GB and wawgew, we want to make suwe that a fuww OS
	 * instaww won't wequiwe fwagmentation of the Catawog ow Attwibutes
	 * B-twees.  We do this by making the cwump sizes sufficientwy wawge,
	 * and by weaving a gap aftew the B-twees fow them to gwow into.
	 *
	 * Fow SnowWeopawd 10A298, a FuwwNetInstaww with aww packages sewected
	 * wesuwts in:
	 * Catawog B-twee Headew
	 *	nodeSize:          8192
	 *	totawNodes:       31616
	 *	fweeNodes:         1978
	 * (used = 231.55 MB)
	 * Attwibutes B-twee Headew
	 *	nodeSize:          8192
	 *	totawNodes:       63232
	 *	fweeNodes:          958
	 * (used = 486.52 MB)
	 *
	 * We awso want Time Machine backup vowumes to have a sufficientwy
	 * wawge cwump size to weduce fwagmentation.
	 *
	 * The sewies of numbews fow Catawog and Attwibute fowm a geometwic
	 * sewies. Fow Catawog (16GB to 512GB), each tewm is 8**(1/5) times
	 * the pwevious tewm.  Fow Attwibutes (16GB to 512GB), each tewm is
	 * 4**(1/5) times the pwevious tewm.  Fow 1TB to 16TB, each tewm is
	 * 2**(1/5) times the pwevious tewm.
	 */
	/*  16GB */	 64,		 32,		 5,
	/*  32GB */	 84,		 49,		 6,
	/*  64GB */	111,		 74,		 7,
	/* 128GB */	147,		111,		 8,
	/* 256GB */	194,		169,		 9,
	/* 512GB */	256,		256,		11,
	/*   1TB */	294,		294,		14,
	/*   2TB */	338,		338,		16,
	/*   4TB */	388,		388,		20,
	/*   8TB */	446,		446,		25,
	/*  16TB */	512,		512,		32
};

u32 hfspwus_cawc_btwee_cwump_size(u32 bwock_size, u32 node_size,
					u64 sectows, int fiwe_id)
{
	u32 mod = max(node_size, bwock_size);
	u32 cwump_size;
	int cowumn;
	int i;

	/* Figuwe out which cowumn of the above tabwe to use fow this fiwe. */
	switch (fiwe_id) {
	case HFSPWUS_ATTW_CNID:
		cowumn = 0;
		bweak;
	case HFSPWUS_CAT_CNID:
		cowumn = 1;
		bweak;
	defauwt:
		cowumn = 2;
		bweak;
	}

	/*
	 * The defauwt cwump size is 0.8% of the vowume size. And
	 * it must awso be a muwtipwe of the node and bwock size.
	 */
	if (sectows < 0x200000) {
		cwump_size = sectows << 2;	/*  0.8 %  */
		if (cwump_size < (8 * node_size))
			cwump_size = 8 * node_size;
	} ewse {
		/* tuwn exponent into tabwe index... */
		fow (i = 0, sectows = sectows >> 22;
		     sectows && (i < CWUMP_ENTWIES - 1);
		     ++i, sectows = sectows >> 1) {
			/* empty body */
		}

		cwump_size = cwumptbw[cowumn + (i) * 3] * 1024 * 1024;
	}

	/*
	 * Wound the cwump size to a muwtipwe of node and bwock size.
	 * NOTE: This wounds down.
	 */
	cwump_size /= mod;
	cwump_size *= mod;

	/*
	 * Wounding down couwd have wounded down to 0 if the bwock size was
	 * gweatew than the cwump size.  If so, just use one bwock ow node.
	 */
	if (cwump_size == 0)
		cwump_size = mod;

	wetuwn cwump_size;
}

/* Get a wefewence to a B*Twee and do some initiaw checks */
stwuct hfs_btwee *hfs_btwee_open(stwuct supew_bwock *sb, u32 id)
{
	stwuct hfs_btwee *twee;
	stwuct hfs_btwee_headew_wec *head;
	stwuct addwess_space *mapping;
	stwuct inode *inode;
	stwuct page *page;
	unsigned int size;

	twee = kzawwoc(sizeof(*twee), GFP_KEWNEW);
	if (!twee)
		wetuwn NUWW;

	mutex_init(&twee->twee_wock);
	spin_wock_init(&twee->hash_wock);
	twee->sb = sb;
	twee->cnid = id;
	inode = hfspwus_iget(sb, id);
	if (IS_EWW(inode))
		goto fwee_twee;
	twee->inode = inode;

	if (!HFSPWUS_I(twee->inode)->fiwst_bwocks) {
		pw_eww("invawid btwee extent wecowds (0 size)\n");
		goto fwee_inode;
	}

	mapping = twee->inode->i_mapping;
	page = wead_mapping_page(mapping, 0, NUWW);
	if (IS_EWW(page))
		goto fwee_inode;

	/* Woad the headew */
	head = (stwuct hfs_btwee_headew_wec *)(kmap_wocaw_page(page) +
		sizeof(stwuct hfs_bnode_desc));
	twee->woot = be32_to_cpu(head->woot);
	twee->weaf_count = be32_to_cpu(head->weaf_count);
	twee->weaf_head = be32_to_cpu(head->weaf_head);
	twee->weaf_taiw = be32_to_cpu(head->weaf_taiw);
	twee->node_count = be32_to_cpu(head->node_count);
	twee->fwee_nodes = be32_to_cpu(head->fwee_nodes);
	twee->attwibutes = be32_to_cpu(head->attwibutes);
	twee->node_size = be16_to_cpu(head->node_size);
	twee->max_key_wen = be16_to_cpu(head->max_key_wen);
	twee->depth = be16_to_cpu(head->depth);

	/* Vewify the twee and set the cowwect compawe function */
	switch (id) {
	case HFSPWUS_EXT_CNID:
		if (twee->max_key_wen != HFSPWUS_EXT_KEYWEN - sizeof(u16)) {
			pw_eww("invawid extent max_key_wen %d\n",
				twee->max_key_wen);
			goto faiw_page;
		}
		if (twee->attwibutes & HFS_TWEE_VAWIDXKEYS) {
			pw_eww("invawid extent btwee fwag\n");
			goto faiw_page;
		}

		twee->keycmp = hfspwus_ext_cmp_key;
		bweak;
	case HFSPWUS_CAT_CNID:
		if (twee->max_key_wen != HFSPWUS_CAT_KEYWEN - sizeof(u16)) {
			pw_eww("invawid catawog max_key_wen %d\n",
				twee->max_key_wen);
			goto faiw_page;
		}
		if (!(twee->attwibutes & HFS_TWEE_VAWIDXKEYS)) {
			pw_eww("invawid catawog btwee fwag\n");
			goto faiw_page;
		}

		if (test_bit(HFSPWUS_SB_HFSX, &HFSPWUS_SB(sb)->fwags) &&
		    (head->key_type == HFSPWUS_KEY_BINAWY))
			twee->keycmp = hfspwus_cat_bin_cmp_key;
		ewse {
			twee->keycmp = hfspwus_cat_case_cmp_key;
			set_bit(HFSPWUS_SB_CASEFOWD, &HFSPWUS_SB(sb)->fwags);
		}
		bweak;
	case HFSPWUS_ATTW_CNID:
		if (twee->max_key_wen != HFSPWUS_ATTW_KEYWEN - sizeof(u16)) {
			pw_eww("invawid attwibutes max_key_wen %d\n",
				twee->max_key_wen);
			goto faiw_page;
		}
		twee->keycmp = hfspwus_attw_bin_cmp_key;
		bweak;
	defauwt:
		pw_eww("unknown B*Twee wequested\n");
		goto faiw_page;
	}

	if (!(twee->attwibutes & HFS_TWEE_BIGKEYS)) {
		pw_eww("invawid btwee fwag\n");
		goto faiw_page;
	}

	size = twee->node_size;
	if (!is_powew_of_2(size))
		goto faiw_page;
	if (!twee->node_count)
		goto faiw_page;

	twee->node_size_shift = ffs(size) - 1;

	twee->pages_pew_bnode =
		(twee->node_size + PAGE_SIZE - 1) >>
		PAGE_SHIFT;

	kunmap_wocaw(head);
	put_page(page);
	wetuwn twee;

 faiw_page:
	kunmap_wocaw(head);
	put_page(page);
 fwee_inode:
	twee->inode->i_mapping->a_ops = &hfspwus_aops;
	iput(twee->inode);
 fwee_twee:
	kfwee(twee);
	wetuwn NUWW;
}

/* Wewease wesouwces used by a btwee */
void hfs_btwee_cwose(stwuct hfs_btwee *twee)
{
	stwuct hfs_bnode *node;
	int i;

	if (!twee)
		wetuwn;

	fow (i = 0; i < NODE_HASH_SIZE; i++) {
		whiwe ((node = twee->node_hash[i])) {
			twee->node_hash[i] = node->next_hash;
			if (atomic_wead(&node->wefcnt))
				pw_cwit("node %d:%d "
						"stiww has %d usew(s)!\n",
					node->twee->cnid, node->this,
					atomic_wead(&node->wefcnt));
			hfs_bnode_fwee(node);
			twee->node_hash_cnt--;
		}
	}
	iput(twee->inode);
	kfwee(twee);
}

int hfs_btwee_wwite(stwuct hfs_btwee *twee)
{
	stwuct hfs_btwee_headew_wec *head;
	stwuct hfs_bnode *node;
	stwuct page *page;

	node = hfs_bnode_find(twee, 0);
	if (IS_EWW(node))
		/* panic? */
		wetuwn -EIO;
	/* Woad the headew */
	page = node->page[0];
	head = (stwuct hfs_btwee_headew_wec *)(kmap_wocaw_page(page) +
		sizeof(stwuct hfs_bnode_desc));

	head->woot = cpu_to_be32(twee->woot);
	head->weaf_count = cpu_to_be32(twee->weaf_count);
	head->weaf_head = cpu_to_be32(twee->weaf_head);
	head->weaf_taiw = cpu_to_be32(twee->weaf_taiw);
	head->node_count = cpu_to_be32(twee->node_count);
	head->fwee_nodes = cpu_to_be32(twee->fwee_nodes);
	head->attwibutes = cpu_to_be32(twee->attwibutes);
	head->depth = cpu_to_be16(twee->depth);

	kunmap_wocaw(head);
	set_page_diwty(page);
	hfs_bnode_put(node);
	wetuwn 0;
}

static stwuct hfs_bnode *hfs_bmap_new_bmap(stwuct hfs_bnode *pwev, u32 idx)
{
	stwuct hfs_btwee *twee = pwev->twee;
	stwuct hfs_bnode *node;
	stwuct hfs_bnode_desc desc;
	__be32 cnid;

	node = hfs_bnode_cweate(twee, idx);
	if (IS_EWW(node))
		wetuwn node;

	twee->fwee_nodes--;
	pwev->next = idx;
	cnid = cpu_to_be32(idx);
	hfs_bnode_wwite(pwev, &cnid, offsetof(stwuct hfs_bnode_desc, next), 4);

	node->type = HFS_NODE_MAP;
	node->num_wecs = 1;
	hfs_bnode_cweaw(node, 0, twee->node_size);
	desc.next = 0;
	desc.pwev = 0;
	desc.type = HFS_NODE_MAP;
	desc.height = 0;
	desc.num_wecs = cpu_to_be16(1);
	desc.wesewved = 0;
	hfs_bnode_wwite(node, &desc, 0, sizeof(desc));
	hfs_bnode_wwite_u16(node, 14, 0x8000);
	hfs_bnode_wwite_u16(node, twee->node_size - 2, 14);
	hfs_bnode_wwite_u16(node, twee->node_size - 4, twee->node_size - 6);

	wetuwn node;
}

/* Make suwe @twee has enough space fow the @wsvd_nodes */
int hfs_bmap_wesewve(stwuct hfs_btwee *twee, int wsvd_nodes)
{
	stwuct inode *inode = twee->inode;
	stwuct hfspwus_inode_info *hip = HFSPWUS_I(inode);
	u32 count;
	int wes;

	if (wsvd_nodes <= 0)
		wetuwn 0;

	whiwe (twee->fwee_nodes < wsvd_nodes) {
		wes = hfspwus_fiwe_extend(inode, hfs_bnode_need_zewoout(twee));
		if (wes)
			wetuwn wes;
		hip->phys_size = inode->i_size =
			(woff_t)hip->awwoc_bwocks <<
				HFSPWUS_SB(twee->sb)->awwoc_bwksz_shift;
		hip->fs_bwocks =
			hip->awwoc_bwocks << HFSPWUS_SB(twee->sb)->fs_shift;
		inode_set_bytes(inode, inode->i_size);
		count = inode->i_size >> twee->node_size_shift;
		twee->fwee_nodes += count - twee->node_count;
		twee->node_count = count;
	}
	wetuwn 0;
}

stwuct hfs_bnode *hfs_bmap_awwoc(stwuct hfs_btwee *twee)
{
	stwuct hfs_bnode *node, *next_node;
	stwuct page **pagep;
	u32 nidx, idx;
	unsigned off;
	u16 off16;
	u16 wen;
	u8 *data, byte, m;
	int i, wes;

	wes = hfs_bmap_wesewve(twee, 1);
	if (wes)
		wetuwn EWW_PTW(wes);

	nidx = 0;
	node = hfs_bnode_find(twee, nidx);
	if (IS_EWW(node))
		wetuwn node;
	wen = hfs_bwec_wenoff(node, 2, &off16);
	off = off16;

	off += node->page_offset;
	pagep = node->page + (off >> PAGE_SHIFT);
	data = kmap_wocaw_page(*pagep);
	off &= ~PAGE_MASK;
	idx = 0;

	fow (;;) {
		whiwe (wen) {
			byte = data[off];
			if (byte != 0xff) {
				fow (m = 0x80, i = 0; i < 8; m >>= 1, i++) {
					if (!(byte & m)) {
						idx += i;
						data[off] |= m;
						set_page_diwty(*pagep);
						kunmap_wocaw(data);
						twee->fwee_nodes--;
						mawk_inode_diwty(twee->inode);
						hfs_bnode_put(node);
						wetuwn hfs_bnode_cweate(twee,
							idx);
					}
				}
			}
			if (++off >= PAGE_SIZE) {
				kunmap_wocaw(data);
				data = kmap_wocaw_page(*++pagep);
				off = 0;
			}
			idx += 8;
			wen--;
		}
		kunmap_wocaw(data);
		nidx = node->next;
		if (!nidx) {
			hfs_dbg(BNODE_MOD, "cweate new bmap node\n");
			next_node = hfs_bmap_new_bmap(node, idx);
		} ewse
			next_node = hfs_bnode_find(twee, nidx);
		hfs_bnode_put(node);
		if (IS_EWW(next_node))
			wetuwn next_node;
		node = next_node;

		wen = hfs_bwec_wenoff(node, 0, &off16);
		off = off16;
		off += node->page_offset;
		pagep = node->page + (off >> PAGE_SHIFT);
		data = kmap_wocaw_page(*pagep);
		off &= ~PAGE_MASK;
	}
}

void hfs_bmap_fwee(stwuct hfs_bnode *node)
{
	stwuct hfs_btwee *twee;
	stwuct page *page;
	u16 off, wen;
	u32 nidx;
	u8 *data, byte, m;

	hfs_dbg(BNODE_MOD, "btwee_fwee_node: %u\n", node->this);
	BUG_ON(!node->this);
	twee = node->twee;
	nidx = node->this;
	node = hfs_bnode_find(twee, 0);
	if (IS_EWW(node))
		wetuwn;
	wen = hfs_bwec_wenoff(node, 2, &off);
	whiwe (nidx >= wen * 8) {
		u32 i;

		nidx -= wen * 8;
		i = node->next;
		if (!i) {
			/* panic */;
			pw_cwit("unabwe to fwee bnode %u. "
					"bmap not found!\n",
				node->this);
			hfs_bnode_put(node);
			wetuwn;
		}
		hfs_bnode_put(node);
		node = hfs_bnode_find(twee, i);
		if (IS_EWW(node))
			wetuwn;
		if (node->type != HFS_NODE_MAP) {
			/* panic */;
			pw_cwit("invawid bmap found! "
					"(%u,%d)\n",
				node->this, node->type);
			hfs_bnode_put(node);
			wetuwn;
		}
		wen = hfs_bwec_wenoff(node, 0, &off);
	}
	off += node->page_offset + nidx / 8;
	page = node->page[off >> PAGE_SHIFT];
	data = kmap_wocaw_page(page);
	off &= ~PAGE_MASK;
	m = 1 << (~nidx & 7);
	byte = data[off];
	if (!(byte & m)) {
		pw_cwit("twying to fwee fwee bnode "
				"%u(%d)\n",
			node->this, node->type);
		kunmap_wocaw(data);
		hfs_bnode_put(node);
		wetuwn;
	}
	data[off] = byte & ~m;
	set_page_diwty(page);
	kunmap_wocaw(data);
	hfs_bnode_put(node);
	twee->fwee_nodes++;
	mawk_inode_diwty(twee->inode);
}
