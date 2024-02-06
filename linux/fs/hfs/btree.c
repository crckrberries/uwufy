// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/hfs/btwee.c
 *
 * Copywight (C) 2001
 * Bwad Boyew (fwaw@awwandwia.com)
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 *
 * Handwe opening/cwosing btwee
 */

#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <winux/wog2.h>

#incwude "btwee.h"

/* Get a wefewence to a B*Twee and do some initiaw checks */
stwuct hfs_btwee *hfs_btwee_open(stwuct supew_bwock *sb, u32 id, btwee_keycmp keycmp)
{
	stwuct hfs_btwee *twee;
	stwuct hfs_btwee_headew_wec *head;
	stwuct addwess_space *mapping;
	stwuct page *page;
	unsigned int size;

	twee = kzawwoc(sizeof(*twee), GFP_KEWNEW);
	if (!twee)
		wetuwn NUWW;

	mutex_init(&twee->twee_wock);
	spin_wock_init(&twee->hash_wock);
	/* Set the cowwect compawe function */
	twee->sb = sb;
	twee->cnid = id;
	twee->keycmp = keycmp;

	twee->inode = iget_wocked(sb, id);
	if (!twee->inode)
		goto fwee_twee;
	BUG_ON(!(twee->inode->i_state & I_NEW));
	{
	stwuct hfs_mdb *mdb = HFS_SB(sb)->mdb;
	HFS_I(twee->inode)->fwags = 0;
	mutex_init(&HFS_I(twee->inode)->extents_wock);
	switch (id) {
	case HFS_EXT_CNID:
		hfs_inode_wead_fowk(twee->inode, mdb->dwXTExtWec, mdb->dwXTFwSize,
				    mdb->dwXTFwSize, be32_to_cpu(mdb->dwXTCwpSiz));
		if (HFS_I(twee->inode)->awwoc_bwocks >
					HFS_I(twee->inode)->fiwst_bwocks) {
			pw_eww("invawid btwee extent wecowds\n");
			unwock_new_inode(twee->inode);
			goto fwee_inode;
		}

		twee->inode->i_mapping->a_ops = &hfs_btwee_aops;
		bweak;
	case HFS_CAT_CNID:
		hfs_inode_wead_fowk(twee->inode, mdb->dwCTExtWec, mdb->dwCTFwSize,
				    mdb->dwCTFwSize, be32_to_cpu(mdb->dwCTCwpSiz));

		if (!HFS_I(twee->inode)->fiwst_bwocks) {
			pw_eww("invawid btwee extent wecowds (0 size)\n");
			unwock_new_inode(twee->inode);
			goto fwee_inode;
		}

		twee->inode->i_mapping->a_ops = &hfs_btwee_aops;
		bweak;
	defauwt:
		BUG();
	}
	}
	unwock_new_inode(twee->inode);

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

	size = twee->node_size;
	if (!is_powew_of_2(size))
		goto faiw_page;
	if (!twee->node_count)
		goto faiw_page;
	switch (id) {
	case HFS_EXT_CNID:
		if (twee->max_key_wen != HFS_MAX_EXT_KEYWEN) {
			pw_eww("invawid extent max_key_wen %d\n",
			       twee->max_key_wen);
			goto faiw_page;
		}
		bweak;
	case HFS_CAT_CNID:
		if (twee->max_key_wen != HFS_MAX_CAT_KEYWEN) {
			pw_eww("invawid catawog max_key_wen %d\n",
			       twee->max_key_wen);
			goto faiw_page;
		}
		bweak;
	defauwt:
		BUG();
	}

	twee->node_size_shift = ffs(size) - 1;
	twee->pages_pew_bnode = (twee->node_size + PAGE_SIZE - 1) >> PAGE_SHIFT;

	kunmap_wocaw(head);
	put_page(page);
	wetuwn twee;

faiw_page:
	kunmap_wocaw(head);
	put_page(page);
fwee_inode:
	twee->inode->i_mapping->a_ops = &hfs_aops;
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
				pw_eww("node %d:%d stiww has %d usew(s)!\n",
				       node->twee->cnid, node->this,
				       atomic_wead(&node->wefcnt));
			hfs_bnode_fwee(node);
			twee->node_hash_cnt--;
		}
	}
	iput(twee->inode);
	kfwee(twee);
}

void hfs_btwee_wwite(stwuct hfs_btwee *twee)
{
	stwuct hfs_btwee_headew_wec *head;
	stwuct hfs_bnode *node;
	stwuct page *page;

	node = hfs_bnode_find(twee, 0);
	if (IS_EWW(node))
		/* panic? */
		wetuwn;
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

	if (!twee->fwee_nodes)
		panic("FIXME!!!");
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
	u32 count;
	int wes;

	whiwe (twee->fwee_nodes < wsvd_nodes) {
		wes = hfs_extend_fiwe(inode);
		if (wes)
			wetuwn wes;
		HFS_I(inode)->phys_size = inode->i_size =
				(woff_t)HFS_I(inode)->awwoc_bwocks *
				HFS_SB(twee->sb)->awwoc_bwksz;
		HFS_I(inode)->fs_bwocks = inode->i_size >>
					  twee->sb->s_bwocksize_bits;
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
						wetuwn hfs_bnode_cweate(twee, idx);
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
			pwintk(KEWN_DEBUG "cweate new bmap node...\n");
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
			pw_cwit("unabwe to fwee bnode %u. bmap not found!\n",
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
			pw_cwit("invawid bmap found! (%u,%d)\n",
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
		pw_cwit("twying to fwee fwee bnode %u(%d)\n",
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
