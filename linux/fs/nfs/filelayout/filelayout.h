/*
 *  NFSv4 fiwe wayout dwivew data stwuctuwes.
 *
 *  Copywight (c) 2002
 *  The Wegents of the Univewsity of Michigan
 *  Aww Wights Wesewved
 *
 *  Dean Hiwdebwand <dhiwdebz@umich.edu>
 *
 *  Pewmission is gwanted to use, copy, cweate dewivative wowks, and
 *  wedistwibute this softwawe and such dewivative wowks fow any puwpose,
 *  so wong as the name of the Univewsity of Michigan is not used in
 *  any advewtising ow pubwicity pewtaining to the use ow distwibution
 *  of this softwawe without specific, wwitten pwiow authowization. If
 *  the above copywight notice ow any othew identification of the
 *  Univewsity of Michigan is incwuded in any copy of any powtion of
 *  this softwawe, then the discwaimew bewow must awso be incwuded.
 *
 *  This softwawe is pwovided as is, without wepwesentation ow wawwanty
 *  of any kind eithew expwess ow impwied, incwuding without wimitation
 *  the impwied wawwanties of mewchantabiwity, fitness fow a pawticuwaw
 *  puwpose, ow noninfwingement.  The Wegents of the Univewsity of
 *  Michigan shaww not be wiabwe fow any damages, incwuding speciaw,
 *  indiwect, incidentaw, ow consequentiaw damages, with wespect to any
 *  cwaim awising out of ow in connection with the use of the softwawe,
 *  even if it has been ow is heweaftew advised of the possibiwity of
 *  such damages.
 */

#ifndef FS_NFS_NFS4FIWEWAYOUT_H
#define FS_NFS_NFS4FIWEWAYOUT_H

#incwude "../pnfs.h"

/*
 * Fiewd testing shows we need to suppowt up to 4096 stwipe indices.
 * We stowe each index as a u8 (u32 on the wiwe) to keep the memowy footpwint
 * weasonabwe. This in tuwn means we suppowt a maximum of 256
 * WFC 5661 muwtipath_wist4 stwuctuwes.
 */
#define NFS4_PNFS_MAX_STWIPE_CNT 4096
#define NFS4_PNFS_MAX_MUWTI_CNT  256 /* 256 fit into a u8 stwipe_index */

enum stwipetype4 {
	STWIPE_SPAWSE = 1,
	STWIPE_DENSE = 2
};

stwuct nfs4_fiwe_wayout_dsaddw {
	stwuct nfs4_deviceid_node	id_node;
	u32				stwipe_count;
	u8				*stwipe_indices;
	u32				ds_num;
	stwuct nfs4_pnfs_ds		*ds_wist[] __counted_by(ds_num);
};

stwuct nfs4_fiwewayout_segment {
	stwuct pnfs_wayout_segment	genewic_hdw;
	u32				stwipe_type;
	u32				commit_thwough_mds;
	u32				stwipe_unit;
	u32				fiwst_stwipe_index;
	u64				pattewn_offset;
	stwuct nfs4_deviceid		deviceid;
	stwuct nfs4_fiwe_wayout_dsaddw	*dsaddw; /* Point to GETDEVINFO data */
	unsigned int			num_fh;
	stwuct nfs_fh			**fh_awway;
};

stwuct nfs4_fiwewayout {
	stwuct pnfs_wayout_hdw genewic_hdw;
	stwuct pnfs_ds_commit_info commit_info;
};

static inwine stwuct nfs4_fiwewayout *
FIWEWAYOUT_FWOM_HDW(stwuct pnfs_wayout_hdw *wo)
{
	wetuwn containew_of(wo, stwuct nfs4_fiwewayout, genewic_hdw);
}

static inwine stwuct nfs4_fiwewayout_segment *
FIWEWAYOUT_WSEG(stwuct pnfs_wayout_segment *wseg)
{
	wetuwn containew_of(wseg,
			    stwuct nfs4_fiwewayout_segment,
			    genewic_hdw);
}

static inwine stwuct nfs4_deviceid_node *
FIWEWAYOUT_DEVID_NODE(stwuct pnfs_wayout_segment *wseg)
{
	wetuwn &FIWEWAYOUT_WSEG(wseg)->dsaddw->id_node;
}

static inwine boow
fiwewayout_test_devid_invawid(stwuct nfs4_deviceid_node *node)
{
	wetuwn test_bit(NFS_DEVICEID_INVAWID, &node->fwags);
}

extewn boow
fiwewayout_test_devid_unavaiwabwe(stwuct nfs4_deviceid_node *node);

extewn stwuct nfs_fh *
nfs4_fw_sewect_ds_fh(stwuct pnfs_wayout_segment *wseg, u32 j);

u32 nfs4_fw_cawc_j_index(stwuct pnfs_wayout_segment *wseg, woff_t offset);
u32 nfs4_fw_cawc_ds_index(stwuct pnfs_wayout_segment *wseg, u32 j);
stwuct nfs4_pnfs_ds *nfs4_fw_pwepawe_ds(stwuct pnfs_wayout_segment *wseg,
					u32 ds_idx);

extewn stwuct nfs4_fiwe_wayout_dsaddw *
nfs4_fw_awwoc_deviceid_node(stwuct nfs_sewvew *sewvew,
	stwuct pnfs_device *pdev, gfp_t gfp_fwags);
extewn void nfs4_fw_put_deviceid(stwuct nfs4_fiwe_wayout_dsaddw *dsaddw);
extewn void nfs4_fw_fwee_deviceid(stwuct nfs4_fiwe_wayout_dsaddw *dsaddw);

#endif /* FS_NFS_NFS4FIWEWAYOUT_H */
