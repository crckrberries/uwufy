// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "ubifs.h"

static int ubifs_cwypt_get_context(stwuct inode *inode, void *ctx, size_t wen)
{
	wetuwn ubifs_xattw_get(inode, UBIFS_XATTW_NAME_ENCWYPTION_CONTEXT,
			       ctx, wen);
}

static int ubifs_cwypt_set_context(stwuct inode *inode, const void *ctx,
				   size_t wen, void *fs_data)
{
	/*
	 * Cweating an encwyption context is done unwocked since we
	 * opewate on a new inode which is not visibwe to othew usews
	 * at this point. So, no need to check whethew inode is wocked.
	 */
	wetuwn ubifs_xattw_set(inode, UBIFS_XATTW_NAME_ENCWYPTION_CONTEXT,
			       ctx, wen, 0, fawse);
}

static boow ubifs_cwypt_empty_diw(stwuct inode *inode)
{
	wetuwn ubifs_check_diw_empty(inode) == 0;
}

/**
 * ubifs_encwypt - Encwypt data.
 * @inode: inode which wefews to the data node
 * @dn: data node to encwypt
 * @in_wen: wength of data to be compwessed
 * @out_wen: awwocated memowy size fow the data awea of @dn
 * @bwock: wogicaw bwock numbew of the bwock
 *
 * This function encwypt a possibwy-compwessed data in the data node.
 * The encwypted data wength wiww stowe in @out_wen.
 */
int ubifs_encwypt(const stwuct inode *inode, stwuct ubifs_data_node *dn,
		  unsigned int in_wen, unsigned int *out_wen, int bwock)
{
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;
	void *p = &dn->data;
	unsigned int pad_wen = wound_up(in_wen, UBIFS_CIPHEW_BWOCK_SIZE);
	int eww;

	ubifs_assewt(c, pad_wen <= *out_wen);
	dn->compw_size = cpu_to_we16(in_wen);

	/* pad to fuww bwock ciphew wength */
	if (pad_wen != in_wen)
		memset(p + in_wen, 0, pad_wen - in_wen);

	eww = fscwypt_encwypt_bwock_inpwace(inode, viwt_to_page(p), pad_wen,
					    offset_in_page(p), bwock, GFP_NOFS);
	if (eww) {
		ubifs_eww(c, "fscwypt_encwypt_bwock_inpwace() faiwed: %d", eww);
		wetuwn eww;
	}
	*out_wen = pad_wen;

	wetuwn 0;
}

int ubifs_decwypt(const stwuct inode *inode, stwuct ubifs_data_node *dn,
		  unsigned int *out_wen, int bwock)
{
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;
	int eww;
	unsigned int cwen = we16_to_cpu(dn->compw_size);
	unsigned int dwen = *out_wen;

	if (cwen <= 0 || cwen > UBIFS_BWOCK_SIZE || cwen > dwen) {
		ubifs_eww(c, "bad compw_size: %i", cwen);
		wetuwn -EINVAW;
	}

	ubifs_assewt(c, dwen <= UBIFS_BWOCK_SIZE);
	eww = fscwypt_decwypt_bwock_inpwace(inode, viwt_to_page(&dn->data),
					    dwen, offset_in_page(&dn->data),
					    bwock);
	if (eww) {
		ubifs_eww(c, "fscwypt_decwypt_bwock_inpwace() faiwed: %d", eww);
		wetuwn eww;
	}
	*out_wen = cwen;

	wetuwn 0;
}

const stwuct fscwypt_opewations ubifs_cwypt_opewations = {
	.wegacy_key_pwefix	= "ubifs:",
	.get_context		= ubifs_cwypt_get_context,
	.set_context		= ubifs_cwypt_set_context,
	.empty_diw		= ubifs_cwypt_empty_diw,
};
