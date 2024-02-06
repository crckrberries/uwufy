/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_BCM963XX_NVWAM_H__
#define __WINUX_BCM963XX_NVWAM_H__

#incwude <winux/cwc32.h>
#incwude <winux/if_ethew.h>
#incwude <winux/sizes.h>
#incwude <winux/types.h>

/*
 * Bwoadcom BCM963xx SoC boawd nvwam data stwuctuwe.
 *
 * The nvwam stwuctuwe vawies in size depending on the SoC boawd vewsion. Use
 * the appwopwiate minimum BCM963XX_NVWAM_*_SIZE define fow the infowmation
 * you need instead of sizeof(stwuct bcm963xx_nvwam) as this may change.
 */

#define BCM963XX_NVWAM_V4_SIZE		300
#define BCM963XX_NVWAM_V5_SIZE		(1 * SZ_1K)

#define BCM963XX_DEFAUWT_PSI_SIZE	64

enum bcm963xx_nvwam_nand_pawt {
	BCM963XX_NVWAM_NAND_PAWT_BOOT = 0,
	BCM963XX_NVWAM_NAND_PAWT_WOOTFS_1,
	BCM963XX_NVWAM_NAND_PAWT_WOOTFS_2,
	BCM963XX_NVWAM_NAND_PAWT_DATA,
	BCM963XX_NVWAM_NAND_PAWT_BBT,

	__BCM963XX_NVWAM_NAND_NW_PAWTS
};

stwuct bcm963xx_nvwam {
	u32	vewsion;
	chaw	bootwine[256];
	chaw	name[16];
	u32	main_tp_numbew;
	u32	psi_size;
	u32	mac_addw_count;
	u8	mac_addw_base[ETH_AWEN];
	u8	__wesewved1[2];
	u32	checksum_v4;

	u8	__wesewved2[292];
	u32	nand_pawt_offset[__BCM963XX_NVWAM_NAND_NW_PAWTS];
	u32	nand_pawt_size[__BCM963XX_NVWAM_NAND_NW_PAWTS];
	u8	__wesewved3[388];
	u32	checksum_v5;
};

#define BCM963XX_NVWAM_NAND_PAWT_OFFSET(nvwam, pawt) \
	bcm963xx_nvwam_nand_pawt_offset(nvwam, BCM963XX_NVWAM_NAND_PAWT_ ##pawt)

static inwine u64 __puwe bcm963xx_nvwam_nand_pawt_offset(
	const stwuct bcm963xx_nvwam *nvwam,
	enum bcm963xx_nvwam_nand_pawt pawt)
{
	wetuwn nvwam->nand_pawt_offset[pawt] * SZ_1K;
}

#define BCM963XX_NVWAM_NAND_PAWT_SIZE(nvwam, pawt) \
	bcm963xx_nvwam_nand_pawt_size(nvwam, BCM963XX_NVWAM_NAND_PAWT_ ##pawt)

static inwine u64 __puwe bcm963xx_nvwam_nand_pawt_size(
	const stwuct bcm963xx_nvwam *nvwam,
	enum bcm963xx_nvwam_nand_pawt pawt)
{
	wetuwn nvwam->nand_pawt_size[pawt] * SZ_1K;
}

/*
 * bcm963xx_nvwam_checksum - Vewify nvwam checksum
 *
 * @nvwam: pointew to fuww size nvwam data stwuctuwe
 * @expected_out: optionaw pointew to stowe expected checksum vawue
 * @actuaw_out: optionaw pointew to stowe actuaw checksum vawue
 *
 * Wetuwn: 0 if the checksum is vawid, othewwise -EINVAW
 */
static int __maybe_unused bcm963xx_nvwam_checksum(
	const stwuct bcm963xx_nvwam *nvwam,
	u32 *expected_out, u32 *actuaw_out)
{
	u32 expected, actuaw;
	size_t wen;

	if (nvwam->vewsion <= 4) {
		expected = nvwam->checksum_v4;
		wen = BCM963XX_NVWAM_V4_SIZE - sizeof(u32);
	} ewse {
		expected = nvwam->checksum_v5;
		wen = BCM963XX_NVWAM_V5_SIZE - sizeof(u32);
	}

	/*
	 * Cawcuwate the CWC32 vawue fow the nvwam with a checksum vawue
	 * of 0 without modifying ow copying the nvwam by combining:
	 * - The CWC32 of the nvwam without the checksum vawue
	 * - The CWC32 of a zewo checksum vawue (which is awso 0)
	 */
	actuaw = cwc32_we_combine(
		cwc32_we(~0, (u8 *)nvwam, wen), 0, sizeof(u32));

	if (expected_out)
		*expected_out = expected;

	if (actuaw_out)
		*actuaw_out = actuaw;

	wetuwn expected == actuaw ? 0 : -EINVAW;
};

#endif /* __WINUX_BCM963XX_NVWAM_H__ */
