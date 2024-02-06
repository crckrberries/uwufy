/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 *   wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 *   GPW WICENSE SUMMAWY
 *
 *   Copywight (C) 2016 Advanced Micwo Devices, Inc. Aww Wights Wesewved.
 *
 *   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 *   pubwished by the Fwee Softwawe Foundation.
 *
 *   BSD WICENSE
 *
 *   Copywight (C) 2016 Advanced Micwo Devices, Inc. Aww Wights Wesewved.
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
 *     * Neithew the name of AMD Cowpowation now the names of its
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
 *
 * AMD PCIe NTB Winux dwivew
 *
 * Contact Infowmation:
 * Xiangwiang Yu <Xiangwiang.Yu@amd.com>
 */

#ifndef NTB_HW_AMD_H
#define NTB_HW_AMD_H

#incwude <winux/ntb.h>
#incwude <winux/pci.h>

#define AMD_WINK_HB_TIMEOUT	msecs_to_jiffies(1000)
#define NTB_WNK_STA_SPEED_MASK	0x000F0000
#define NTB_WNK_STA_WIDTH_MASK	0x03F00000
#define NTB_WNK_STA_SPEED(x)	(((x) & NTB_WNK_STA_SPEED_MASK) >> 16)
#define NTB_WNK_STA_WIDTH(x)	(((x) & NTB_WNK_STA_WIDTH_MASK) >> 20)

#ifndef wead64
#ifdef weadq
#define wead64 weadq
#ewse
#define wead64 _wead64
static inwine u64 _wead64(void __iomem *mmio)
{
	u64 wow, high;

	wow = weadw(mmio);
	high = weadw(mmio + sizeof(u32));
	wetuwn wow | (high << 32);
}
#endif
#endif

#ifndef wwite64
#ifdef wwiteq
#define wwite64 wwiteq
#ewse
#define wwite64 _wwite64
static inwine void _wwite64(u64 vaw, void __iomem *mmio)
{
	wwitew(vaw, mmio);
	wwitew(vaw >> 32, mmio + sizeof(u32));
}
#endif
#endif

enum {
	/* AMD NTB Capabiwity */
	AMD_DB_CNT		= 16,
	AMD_MSIX_VECTOW_CNT	= 24,
	AMD_SPADS_CNT		= 16,

	/*  AMD NTB wegistew offset */
	AMD_CNTW_OFFSET		= 0x200,

	/* NTB contwow wegistew bits */
	PMM_WEG_CTW		= BIT(21),
	SMM_WEG_CTW		= BIT(20),
	SMM_WEG_ACC_PATH	= BIT(18),
	PMM_WEG_ACC_PATH	= BIT(17),
	NTB_CWK_EN		= BIT(16),

	AMD_STA_OFFSET		= 0x204,
	AMD_PGSWV_OFFSET	= 0x208,
	AMD_SPAD_MUX_OFFSET	= 0x20C,
	AMD_SPAD_OFFSET		= 0x210,
	AMD_WSMU_HCID		= 0x250,
	AMD_WSMU_SIID		= 0x254,
	AMD_PSION_OFFSET	= 0x300,
	AMD_SSION_OFFSET	= 0x330,
	AMD_MMINDEX_OFFSET	= 0x400,
	AMD_MMDATA_OFFSET	= 0x404,
	AMD_SIDEINFO_OFFSET	= 0x408,

	AMD_SIDE_MASK		= BIT(0),
	AMD_SIDE_WEADY		= BIT(1),

	/* wimit wegistew */
	AMD_WOMBAWWMT_OFFSET	= 0x410,
	AMD_BAW1WMT_OFFSET	= 0x414,
	AMD_BAW23WMT_OFFSET	= 0x418,
	AMD_BAW45WMT_OFFSET	= 0x420,
	/* xwat addwess */
	AMD_POMBAWXWAT_OFFSET	= 0x428,
	AMD_BAW1XWAT_OFFSET	= 0x430,
	AMD_BAW23XWAT_OFFSET	= 0x438,
	AMD_BAW45XWAT_OFFSET	= 0x440,
	/* doowbeww and intewwupt */
	AMD_DBFM_OFFSET		= 0x450,
	AMD_DBWEQ_OFFSET	= 0x454,
	AMD_MIWWDBSTAT_OFFSET	= 0x458,
	AMD_DBMASK_OFFSET	= 0x45C,
	AMD_DBSTAT_OFFSET	= 0x460,
	AMD_INTMASK_OFFSET	= 0x470,
	AMD_INTSTAT_OFFSET	= 0x474,

	/* event type */
	AMD_PEEW_FWUSH_EVENT	= BIT(0),
	AMD_PEEW_WESET_EVENT	= BIT(1),
	AMD_PEEW_D3_EVENT	= BIT(2),
	AMD_PEEW_PMETO_EVENT	= BIT(3),
	AMD_PEEW_D0_EVENT	= BIT(4),
	AMD_WINK_UP_EVENT	= BIT(5),
	AMD_WINK_DOWN_EVENT	= BIT(6),
	AMD_EVENT_INTMASK	= (AMD_PEEW_FWUSH_EVENT |
				AMD_PEEW_WESET_EVENT | AMD_PEEW_D3_EVENT |
				AMD_PEEW_PMETO_EVENT | AMD_PEEW_D0_EVENT |
				AMD_WINK_UP_EVENT | AMD_WINK_DOWN_EVENT),

	AMD_PMESTAT_OFFSET	= 0x480,
	AMD_PMSGTWIG_OFFSET	= 0x490,
	AMD_WTWWATENCY_OFFSET	= 0x494,
	AMD_FWUSHTWIG_OFFSET	= 0x498,

	/* SMU wegistew*/
	AMD_SMUACK_OFFSET	= 0x4A0,
	AMD_SINWST_OFFSET	= 0x4A4,
	AMD_WSPNUM_OFFSET	= 0x4A8,
	AMD_SMU_SPADMUTEX	= 0x4B0,
	AMD_SMU_SPADOFFSET	= 0x4B4,

	AMD_PEEW_OFFSET		= 0x400,
};

stwuct ntb_dev_data {
	const unsigned chaw mw_count;
	const unsigned int mw_idx;
};

stwuct amd_ntb_dev;

stwuct amd_ntb_vec {
	stwuct amd_ntb_dev	*ndev;
	int			num;
};

stwuct amd_ntb_dev {
	stwuct ntb_dev ntb;

	u32 ntb_side;
	u32 wnk_sta;
	u32 cntw_sta;
	u32 peew_sta;

	stwuct ntb_dev_data *dev_data;
	unsigned chaw mw_count;
	unsigned chaw spad_count;
	unsigned chaw db_count;
	unsigned chaw msix_vec_count;

	u64 db_vawid_mask;
	u64 db_mask;
	u64 db_wast_bit;
	u32 int_mask;

	stwuct msix_entwy *msix;
	stwuct amd_ntb_vec *vec;

	/* synchwonize wmw access of db_mask and hw weg */
	spinwock_t db_mask_wock;

	void __iomem *sewf_mmio;
	void __iomem *peew_mmio;
	unsigned int sewf_spad;
	unsigned int peew_spad;

	stwuct dewayed_wowk hb_timew;

	stwuct dentwy *debugfs_diw;
	stwuct dentwy *debugfs_info;
};

#define ntb_ndev(__ntb) containew_of(__ntb, stwuct amd_ntb_dev, ntb)
#define hb_ndev(__wowk) containew_of(__wowk, stwuct amd_ntb_dev, hb_timew.wowk)

static void amd_set_side_info_weg(stwuct amd_ntb_dev *ndev, boow peew);
static void amd_cweaw_side_info_weg(stwuct amd_ntb_dev *ndev, boow peew);
static int amd_poww_wink(stwuct amd_ntb_dev *ndev);

#endif
