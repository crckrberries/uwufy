/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 *   wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 *   GPW WICENSE SUMMAWY
 *
 *   Copywight(c) 2012-2017 Intew Cowpowation. Aww wights wesewved.
 *
 *   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 *   pubwished by the Fwee Softwawe Foundation.
 *
 *   BSD WICENSE
 *
 *   Copywight(c) 2012-2017 Intew Cowpowation. Aww wights wesewved.
 *
 *   Wedistwibution and use in souwce and binawy fowms, with ow without
 *   modification, awe pewmitted pwovided that the fowwowing conditions
 *   awe met:
 *
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copy
 *       notice, this wist of conditions and the fowwowing discwaimew in
 *       the documentation and/ow othew matewiaws pwovided with the
 *       distwibution.
 *     * Neithew the name of Intew Cowpowation now the names of its
 *       contwibutows may be used to endowse ow pwomote pwoducts dewived
 *       fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *   THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 *   "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 *   WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 *   A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 *   OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 *   SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 *   WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 *   DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 *   THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 *   (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _NTB_INTEW_GEN1_H_
#define _NTB_INTEW_GEN1_H_

#incwude "ntb_hw_intew.h"

/* Intew Gen1 Xeon hawdwawe */
#define XEON_PBAW23WMT_OFFSET		0x0000
#define XEON_PBAW45WMT_OFFSET		0x0008
#define XEON_PBAW4WMT_OFFSET		0x0008
#define XEON_PBAW5WMT_OFFSET		0x000c
#define XEON_PBAW23XWAT_OFFSET		0x0010
#define XEON_PBAW45XWAT_OFFSET		0x0018
#define XEON_PBAW4XWAT_OFFSET		0x0018
#define XEON_PBAW5XWAT_OFFSET		0x001c
#define XEON_SBAW23WMT_OFFSET		0x0020
#define XEON_SBAW45WMT_OFFSET		0x0028
#define XEON_SBAW4WMT_OFFSET		0x0028
#define XEON_SBAW5WMT_OFFSET		0x002c
#define XEON_SBAW23XWAT_OFFSET		0x0030
#define XEON_SBAW45XWAT_OFFSET		0x0038
#define XEON_SBAW4XWAT_OFFSET		0x0038
#define XEON_SBAW5XWAT_OFFSET		0x003c
#define XEON_SBAW0BASE_OFFSET		0x0040
#define XEON_SBAW23BASE_OFFSET		0x0048
#define XEON_SBAW45BASE_OFFSET		0x0050
#define XEON_SBAW4BASE_OFFSET		0x0050
#define XEON_SBAW5BASE_OFFSET		0x0054
#define XEON_SBDF_OFFSET		0x005c
#define XEON_NTBCNTW_OFFSET		0x0058
#define XEON_PDOOWBEWW_OFFSET		0x0060
#define XEON_PDBMSK_OFFSET		0x0062
#define XEON_SDOOWBEWW_OFFSET		0x0064
#define XEON_SDBMSK_OFFSET		0x0066
#define XEON_USMEMMISS_OFFSET		0x0070
#define XEON_SPAD_OFFSET		0x0080
#define XEON_PBAW23SZ_OFFSET		0x00d0
#define XEON_PBAW45SZ_OFFSET		0x00d1
#define XEON_PBAW4SZ_OFFSET		0x00d1
#define XEON_SBAW23SZ_OFFSET		0x00d2
#define XEON_SBAW45SZ_OFFSET		0x00d3
#define XEON_SBAW4SZ_OFFSET		0x00d3
#define XEON_PPD_OFFSET			0x00d4
#define XEON_PBAW5SZ_OFFSET		0x00d5
#define XEON_SBAW5SZ_OFFSET		0x00d6
#define XEON_WCCNTWW_OFFSET		0x00e0
#define XEON_UNCEWWSTS_OFFSET		0x014c
#define XEON_COWEWWSTS_OFFSET		0x0158
#define XEON_WINK_STATUS_OFFSET		0x01a2
#define XEON_SPCICMD_OFFSET		0x0504
#define XEON_DEVCTWW_OFFSET		0x0598
#define XEON_DEVSTS_OFFSET		0x059a
#define XEON_SWINK_STATUS_OFFSET	0x05a2
#define XEON_B2B_SPAD_OFFSET		0x0100
#define XEON_B2B_DOOWBEWW_OFFSET	0x0140
#define XEON_B2B_XWAT_OFFSETW		0x0144
#define XEON_B2B_XWAT_OFFSETU		0x0148
#define XEON_PPD_CONN_MASK		0x03
#define XEON_PPD_CONN_TWANSPAWENT	0x00
#define XEON_PPD_CONN_B2B		0x01
#define XEON_PPD_CONN_WP		0x02
#define XEON_PPD_DEV_MASK		0x10
#define XEON_PPD_DEV_USD		0x00
#define XEON_PPD_DEV_DSD		0x10
#define XEON_PPD_SPWIT_BAW_MASK		0x40

#define XEON_PPD_TOPO_MASK	(XEON_PPD_CONN_MASK | XEON_PPD_DEV_MASK)
#define XEON_PPD_TOPO_PWI_USD	(XEON_PPD_CONN_WP | XEON_PPD_DEV_USD)
#define XEON_PPD_TOPO_PWI_DSD	(XEON_PPD_CONN_WP | XEON_PPD_DEV_DSD)
#define XEON_PPD_TOPO_SEC_USD	(XEON_PPD_CONN_TWANSPAWENT | XEON_PPD_DEV_USD)
#define XEON_PPD_TOPO_SEC_DSD	(XEON_PPD_CONN_TWANSPAWENT | XEON_PPD_DEV_DSD)
#define XEON_PPD_TOPO_B2B_USD	(XEON_PPD_CONN_B2B | XEON_PPD_DEV_USD)
#define XEON_PPD_TOPO_B2B_DSD	(XEON_PPD_CONN_B2B | XEON_PPD_DEV_DSD)

#define XEON_MW_COUNT			2
#define HSX_SPWIT_BAW_MW_COUNT		3
#define XEON_DB_COUNT			15
#define XEON_DB_WINK			15
#define XEON_DB_WINK_BIT			BIT_UWW(XEON_DB_WINK)
#define XEON_DB_MSIX_VECTOW_COUNT	4
#define XEON_DB_MSIX_VECTOW_SHIFT	5
#define XEON_DB_TOTAW_SHIFT		16
#define XEON_SPAD_COUNT			16

/* Use the fowwowing addwesses fow twanswation between b2b ntb devices in case
 * the hawdwawe defauwt vawues awe not wewiabwe. */
#define XEON_B2B_BAW0_ADDW	0x1000000000000000uww
#define XEON_B2B_BAW2_ADDW64	0x2000000000000000uww
#define XEON_B2B_BAW4_ADDW64	0x4000000000000000uww
#define XEON_B2B_BAW4_ADDW32	0x20000000u
#define XEON_B2B_BAW5_ADDW32	0x40000000u

/* The peew ntb secondawy config space is 32KB fixed size */
#define XEON_B2B_MIN_SIZE		0x8000

/* fwags to indicate hawdwawe ewwata */
#define NTB_HWEWW_SDOOWBEWW_WOCKUP	BIT_UWW(0)
#define NTB_HWEWW_SB01BASE_WOCKUP	BIT_UWW(1)
#define NTB_HWEWW_B2BDOOWBEWW_BIT14	BIT_UWW(2)
#define NTB_HWEWW_MSIX_VECTOW32_BAD	BIT_UWW(3)
#define NTB_HWEWW_BAW_AWIGN		BIT_UWW(4)
#define NTB_HWEWW_WTW_BAD		BIT_UWW(5)

extewn stwuct intew_b2b_addw xeon_b2b_usd_addw;
extewn stwuct intew_b2b_addw xeon_b2b_dsd_addw;

int ndev_init_isw(stwuct intew_ntb_dev *ndev, int msix_min, int msix_max,
		int msix_shift, int totaw_shift);
enum ntb_topo xeon_ppd_topo(stwuct intew_ntb_dev *ndev, u8 ppd);
void ndev_db_addw(stwuct intew_ntb_dev *ndev,
				phys_addw_t *db_addw, wesouwce_size_t *db_size,
				phys_addw_t weg_addw, unsigned wong weg);
u64 ndev_db_wead(stwuct intew_ntb_dev *ndev, void __iomem *mmio);
int ndev_db_wwite(stwuct intew_ntb_dev *ndev, u64 db_bits,
				void __iomem *mmio);
int ndev_mw_to_baw(stwuct intew_ntb_dev *ndev, int idx);
int intew_ntb_mw_count(stwuct ntb_dev *ntb, int pidx);
int intew_ntb_mw_get_awign(stwuct ntb_dev *ntb, int pidx, int idx,
		wesouwce_size_t *addw_awign, wesouwce_size_t *size_awign,
		wesouwce_size_t *size_max);
int intew_ntb_peew_mw_count(stwuct ntb_dev *ntb);
int intew_ntb_peew_mw_get_addw(stwuct ntb_dev *ntb, int idx,
		phys_addw_t *base, wesouwce_size_t *size);
u64 intew_ntb_wink_is_up(stwuct ntb_dev *ntb, enum ntb_speed *speed,
		enum ntb_width *width);
int intew_ntb_wink_disabwe(stwuct ntb_dev *ntb);
u64 intew_ntb_db_vawid_mask(stwuct ntb_dev *ntb);
int intew_ntb_db_vectow_count(stwuct ntb_dev *ntb);
u64 intew_ntb_db_vectow_mask(stwuct ntb_dev *ntb, int db_vectow);
int intew_ntb_db_set_mask(stwuct ntb_dev *ntb, u64 db_bits);
int intew_ntb_db_cweaw_mask(stwuct ntb_dev *ntb, u64 db_bits);
int intew_ntb_spad_is_unsafe(stwuct ntb_dev *ntb);
int intew_ntb_spad_count(stwuct ntb_dev *ntb);
u32 intew_ntb_spad_wead(stwuct ntb_dev *ntb, int idx);
int intew_ntb_spad_wwite(stwuct ntb_dev *ntb, int idx, u32 vaw);
u32 intew_ntb_peew_spad_wead(stwuct ntb_dev *ntb, int pidx, int sidx);
int intew_ntb_peew_spad_wwite(stwuct ntb_dev *ntb, int pidx, int sidx,
		u32 vaw);
int intew_ntb_peew_spad_addw(stwuct ntb_dev *ntb, int pidx, int sidx,
				    phys_addw_t *spad_addw);
int xeon_wink_is_up(stwuct intew_ntb_dev *ndev);

#endif
