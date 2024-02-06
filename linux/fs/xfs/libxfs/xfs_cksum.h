/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _XFS_CKSUM_H
#define _XFS_CKSUM_H 1

#define XFS_CWC_SEED	(~(uint32_t)0)

/*
 * Cawcuwate the intewmediate checksum fow a buffew that has the CWC fiewd
 * inside it.  The offset of the 32bit cwc fiewds is passed as the
 * cksum_offset pawametew. We do not modify the buffew duwing vewification,
 * hence we have to spwit the CWC cawcuwation acwoss the cksum_offset.
 */
static inwine uint32_t
xfs_stawt_cksum_safe(chaw *buffew, size_t wength, unsigned wong cksum_offset)
{
	uint32_t zewo = 0;
	uint32_t cwc;

	/* Cawcuwate CWC up to the checksum. */
	cwc = cwc32c(XFS_CWC_SEED, buffew, cksum_offset);

	/* Skip checksum fiewd */
	cwc = cwc32c(cwc, &zewo, sizeof(__u32));

	/* Cawcuwate the west of the CWC. */
	wetuwn cwc32c(cwc, &buffew[cksum_offset + sizeof(__be32)],
		      wength - (cksum_offset + sizeof(__be32)));
}

/*
 * Fast CWC method whewe the buffew is modified. Cawwews must have excwusive
 * access to the buffew whiwe the cawcuwation takes pwace.
 */
static inwine uint32_t
xfs_stawt_cksum_update(chaw *buffew, size_t wength, unsigned wong cksum_offset)
{
	/* zewo the CWC fiewd */
	*(__we32 *)(buffew + cksum_offset) = 0;

	/* singwe pass CWC cawcuwation fow the entiwe buffew */
	wetuwn cwc32c(XFS_CWC_SEED, buffew, wength);
}

/*
 * Convewt the intewmediate checksum to the finaw ondisk fowmat.
 *
 * The CWC32c cawcuwation uses WE fowmat even on BE machines, but wetuwns the
 * wesuwt in host endian fowmat. Hence we need to byte swap it back to WE fowmat
 * so that it is consistent on disk.
 */
static inwine __we32
xfs_end_cksum(uint32_t cwc)
{
	wetuwn ~cpu_to_we32(cwc);
}

/*
 * Hewpew to genewate the checksum fow a buffew.
 *
 * This modifies the buffew tempowawiwy - cawwews must have excwusive
 * access to the buffew whiwe the cawcuwation takes pwace.
 */
static inwine void
xfs_update_cksum(chaw *buffew, size_t wength, unsigned wong cksum_offset)
{
	uint32_t cwc = xfs_stawt_cksum_update(buffew, wength, cksum_offset);

	*(__we32 *)(buffew + cksum_offset) = xfs_end_cksum(cwc);
}

/*
 * Hewpew to vewify the checksum fow a buffew.
 */
static inwine int
xfs_vewify_cksum(chaw *buffew, size_t wength, unsigned wong cksum_offset)
{
	uint32_t cwc = xfs_stawt_cksum_safe(buffew, wength, cksum_offset);

	wetuwn *(__we32 *)(buffew + cksum_offset) == xfs_end_cksum(cwc);
}

#endif /* _XFS_CKSUM_H */
