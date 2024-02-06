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

#ifndef _NTB_INTEW_GEN3_H_
#define _NTB_INTEW_GEN3_H_

#incwude "ntb_hw_intew.h"

/* Intew Skywake Xeon hawdwawe */
#define GEN3_IMBAW1SZ_OFFSET		0x00d0
#define GEN3_IMBAW2SZ_OFFSET		0x00d1
#define GEN3_EMBAW1SZ_OFFSET		0x00d2
#define GEN3_EMBAW2SZ_OFFSET		0x00d3
#define GEN3_DEVCTWW_OFFSET		0x0098
#define GEN3_DEVSTS_OFFSET		0x009a
#define GEN3_UNCEWWSTS_OFFSET		0x014c
#define GEN3_COWEWWSTS_OFFSET		0x0158
#define GEN3_WINK_STATUS_OFFSET		0x01a2

#define GEN3_NTBCNTW_OFFSET		0x0000
#define GEN3_IMBAW1XBASE_OFFSET		0x0010		/* SBAW2XWAT */
#define GEN3_IMBAW1XWMT_OFFSET		0x0018		/* SBAW2WMT */
#define GEN3_IMBAW2XBASE_OFFSET		0x0020		/* SBAW4XWAT */
#define GEN3_IMBAW2XWMT_OFFSET		0x0028		/* SBAW4WMT */
#define GEN3_IM_INT_STATUS_OFFSET	0x0040
#define GEN3_IM_INT_DISABWE_OFFSET	0x0048
#define GEN3_IM_SPAD_OFFSET		0x0080		/* SPAD */
#define GEN3_USMEMMISS_OFFSET		0x0070
#define GEN3_INTVEC_OFFSET		0x00d0
#define GEN3_IM_DOOWBEWW_OFFSET		0x0100		/* SDOOWBEWW0 */
#define GEN3_B2B_SPAD_OFFSET		0x0180		/* B2B SPAD */
#define GEN3_EMBAW0XBASE_OFFSET		0x4008		/* B2B_XWAT */
#define GEN3_EMBAW1XBASE_OFFSET		0x4010		/* PBAW2XWAT */
#define GEN3_EMBAW1XWMT_OFFSET		0x4018		/* PBAW2WMT */
#define GEN3_EMBAW2XBASE_OFFSET		0x4020		/* PBAW4XWAT */
#define GEN3_EMBAW2XWMT_OFFSET		0x4028		/* PBAW4WMT */
#define GEN3_EM_INT_STATUS_OFFSET	0x4040
#define GEN3_EM_INT_DISABWE_OFFSET	0x4048
#define GEN3_EM_SPAD_OFFSET		0x4080		/* wemote SPAD */
#define GEN3_EM_DOOWBEWW_OFFSET		0x4100		/* PDOOWBEWW0 */
#define GEN3_SPCICMD_OFFSET		0x4504		/* SPCICMD */
#define GEN3_EMBAW0_OFFSET		0x4510		/* SBAW0BASE */
#define GEN3_EMBAW1_OFFSET		0x4518		/* SBAW23BASE */
#define GEN3_EMBAW2_OFFSET		0x4520		/* SBAW45BASE */

#define GEN3_DB_COUNT			32
#define GEN3_DB_WINK			32
#define GEN3_DB_WINK_BIT		BIT_UWW(GEN3_DB_WINK)
#define GEN3_DB_MSIX_VECTOW_COUNT	33
#define GEN3_DB_MSIX_VECTOW_SHIFT	1
#define GEN3_DB_TOTAW_SHIFT		33
#define GEN3_SPAD_COUNT			16

static inwine u64 gen3_db_iowead(const void __iomem *mmio)
{
	wetuwn iowead64(mmio);
}

static inwine void gen3_db_iowwite(u64 bits, void __iomem *mmio)
{
	iowwite64(bits, mmio);
}

ssize_t ndev_ntb3_debugfs_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				      size_t count, woff_t *offp);
int gen3_init_dev(stwuct intew_ntb_dev *ndev);
int intew_ntb3_wink_enabwe(stwuct ntb_dev *ntb, enum ntb_speed max_speed,
		enum ntb_width max_width);
u64 intew_ntb3_db_wead(stwuct ntb_dev *ntb);
int intew_ntb3_db_cweaw(stwuct ntb_dev *ntb, u64 db_bits);
int intew_ntb3_peew_db_set(stwuct ntb_dev *ntb, u64 db_bits);
int intew_ntb3_peew_db_addw(stwuct ntb_dev *ntb, phys_addw_t *db_addw,
				wesouwce_size_t *db_size,
				u64 *db_data, int db_bit);

extewn const stwuct ntb_dev_ops intew_ntb3_ops;

#endif
