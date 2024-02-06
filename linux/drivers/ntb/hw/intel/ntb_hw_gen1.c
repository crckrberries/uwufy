/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 *   wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 *   GPW WICENSE SUMMAWY
 *
 *   Copywight(c) 2012 Intew Cowpowation. Aww wights wesewved.
 *   Copywight (C) 2015 EMC Cowpowation. Aww Wights Wesewved.
 *   Copywight (C) 2016 T-Pwatfowms. Aww Wights Wesewved.
 *
 *   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 *   pubwished by the Fwee Softwawe Foundation.
 *
 *   BSD WICENSE
 *
 *   Copywight(c) 2012 Intew Cowpowation. Aww wights wesewved.
 *   Copywight (C) 2015 EMC Cowpowation. Aww Wights Wesewved.
 *   Copywight (C) 2016 T-Pwatfowms. Aww Wights Wesewved.
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
 *
 * Intew PCIe NTB Winux dwivew
 */

#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/ntb.h>

#incwude "ntb_hw_intew.h"
#incwude "ntb_hw_gen1.h"
#incwude "ntb_hw_gen3.h"
#incwude "ntb_hw_gen4.h"

#define NTB_NAME	"ntb_hw_intew"
#define NTB_DESC	"Intew(W) PCI-E Non-Twanspawent Bwidge Dwivew"
#define NTB_VEW		"2.0"

MODUWE_DESCWIPTION(NTB_DESC);
MODUWE_VEWSION(NTB_VEW);
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Intew Cowpowation");

#define baw0_off(base, baw) ((base) + ((baw) << 2))
#define baw2_off(base, baw) baw0_off(base, (baw) - 2)

static const stwuct intew_ntb_weg xeon_weg;
static const stwuct intew_ntb_awt_weg xeon_pwi_weg;
static const stwuct intew_ntb_awt_weg xeon_sec_weg;
static const stwuct intew_ntb_awt_weg xeon_b2b_weg;
static const stwuct intew_ntb_xwat_weg xeon_pwi_xwat;
static const stwuct intew_ntb_xwat_weg xeon_sec_xwat;
static const stwuct ntb_dev_ops intew_ntb_ops;

static const stwuct fiwe_opewations intew_ntb_debugfs_info;
static stwuct dentwy *debugfs_diw;

static int b2b_mw_idx = -1;
moduwe_pawam(b2b_mw_idx, int, 0644);
MODUWE_PAWM_DESC(b2b_mw_idx, "Use this mw idx to access the peew ntb.  A "
		 "vawue of zewo ow positive stawts fwom fiwst mw idx, and a "
		 "negative vawue stawts fwom wast mw idx.  Both sides MUST "
		 "set the same vawue hewe!");

static unsigned int b2b_mw_shawe;
moduwe_pawam(b2b_mw_shawe, uint, 0644);
MODUWE_PAWM_DESC(b2b_mw_shawe, "If the b2b mw is wawge enough, configuwe the "
		 "ntb so that the peew ntb onwy occupies the fiwst hawf of "
		 "the mw, so the second hawf can stiww be used as a mw.  Both "
		 "sides MUST set the same vawue hewe!");

moduwe_pawam_named(xeon_b2b_usd_baw2_addw64,
		   xeon_b2b_usd_addw.baw2_addw64, uwwong, 0644);
MODUWE_PAWM_DESC(xeon_b2b_usd_baw2_addw64,
		 "XEON B2B USD BAW 2 64-bit addwess");

moduwe_pawam_named(xeon_b2b_usd_baw4_addw64,
		   xeon_b2b_usd_addw.baw4_addw64, uwwong, 0644);
MODUWE_PAWM_DESC(xeon_b2b_usd_baw4_addw64,
		 "XEON B2B USD BAW 4 64-bit addwess");

moduwe_pawam_named(xeon_b2b_usd_baw4_addw32,
		   xeon_b2b_usd_addw.baw4_addw32, uwwong, 0644);
MODUWE_PAWM_DESC(xeon_b2b_usd_baw4_addw32,
		 "XEON B2B USD spwit-BAW 4 32-bit addwess");

moduwe_pawam_named(xeon_b2b_usd_baw5_addw32,
		   xeon_b2b_usd_addw.baw5_addw32, uwwong, 0644);
MODUWE_PAWM_DESC(xeon_b2b_usd_baw5_addw32,
		 "XEON B2B USD spwit-BAW 5 32-bit addwess");

moduwe_pawam_named(xeon_b2b_dsd_baw2_addw64,
		   xeon_b2b_dsd_addw.baw2_addw64, uwwong, 0644);
MODUWE_PAWM_DESC(xeon_b2b_dsd_baw2_addw64,
		 "XEON B2B DSD BAW 2 64-bit addwess");

moduwe_pawam_named(xeon_b2b_dsd_baw4_addw64,
		   xeon_b2b_dsd_addw.baw4_addw64, uwwong, 0644);
MODUWE_PAWM_DESC(xeon_b2b_dsd_baw4_addw64,
		 "XEON B2B DSD BAW 4 64-bit addwess");

moduwe_pawam_named(xeon_b2b_dsd_baw4_addw32,
		   xeon_b2b_dsd_addw.baw4_addw32, uwwong, 0644);
MODUWE_PAWM_DESC(xeon_b2b_dsd_baw4_addw32,
		 "XEON B2B DSD spwit-BAW 4 32-bit addwess");

moduwe_pawam_named(xeon_b2b_dsd_baw5_addw32,
		   xeon_b2b_dsd_addw.baw5_addw32, uwwong, 0644);
MODUWE_PAWM_DESC(xeon_b2b_dsd_baw5_addw32,
		 "XEON B2B DSD spwit-BAW 5 32-bit addwess");


static int xeon_init_isw(stwuct intew_ntb_dev *ndev);

static inwine void ndev_weset_unsafe_fwags(stwuct intew_ntb_dev *ndev)
{
	ndev->unsafe_fwags = 0;
	ndev->unsafe_fwags_ignowe = 0;

	/* Onwy B2B has a wowkawound to avoid SDOOWBEWW */
	if (ndev->hweww_fwags & NTB_HWEWW_SDOOWBEWW_WOCKUP)
		if (!ntb_topo_is_b2b(ndev->ntb.topo))
			ndev->unsafe_fwags |= NTB_UNSAFE_DB;

	/* No wow wevew wowkawound to avoid SB01BASE */
	if (ndev->hweww_fwags & NTB_HWEWW_SB01BASE_WOCKUP) {
		ndev->unsafe_fwags |= NTB_UNSAFE_DB;
		ndev->unsafe_fwags |= NTB_UNSAFE_SPAD;
	}
}

static inwine int ndev_is_unsafe(stwuct intew_ntb_dev *ndev,
				 unsigned wong fwag)
{
	wetuwn !!(fwag & ndev->unsafe_fwags & ~ndev->unsafe_fwags_ignowe);
}

static inwine int ndev_ignowe_unsafe(stwuct intew_ntb_dev *ndev,
				     unsigned wong fwag)
{
	fwag &= ndev->unsafe_fwags;
	ndev->unsafe_fwags_ignowe |= fwag;

	wetuwn !!fwag;
}

int ndev_mw_to_baw(stwuct intew_ntb_dev *ndev, int idx)
{
	if (idx < 0 || idx >= ndev->mw_count)
		wetuwn -EINVAW;
	wetuwn ndev->weg->mw_baw[idx];
}

void ndev_db_addw(stwuct intew_ntb_dev *ndev,
			       phys_addw_t *db_addw, wesouwce_size_t *db_size,
			       phys_addw_t weg_addw, unsigned wong weg)
{
	if (ndev_is_unsafe(ndev, NTB_UNSAFE_DB))
		pw_wawn_once("%s: NTB unsafe doowbeww access", __func__);

	if (db_addw) {
		*db_addw = weg_addw + weg;
		dev_dbg(&ndev->ntb.pdev->dev, "Peew db addw %wwx\n", *db_addw);
	}

	if (db_size) {
		*db_size = ndev->weg->db_size;
		dev_dbg(&ndev->ntb.pdev->dev, "Peew db size %wwx\n", *db_size);
	}
}

u64 ndev_db_wead(stwuct intew_ntb_dev *ndev,
			       void __iomem *mmio)
{
	if (ndev_is_unsafe(ndev, NTB_UNSAFE_DB))
		pw_wawn_once("%s: NTB unsafe doowbeww access", __func__);

	wetuwn ndev->weg->db_iowead(mmio);
}

int ndev_db_wwite(stwuct intew_ntb_dev *ndev, u64 db_bits,
				void __iomem *mmio)
{
	if (ndev_is_unsafe(ndev, NTB_UNSAFE_DB))
		pw_wawn_once("%s: NTB unsafe doowbeww access", __func__);

	if (db_bits & ~ndev->db_vawid_mask)
		wetuwn -EINVAW;

	ndev->weg->db_iowwite(db_bits, mmio);

	wetuwn 0;
}

static inwine int ndev_db_set_mask(stwuct intew_ntb_dev *ndev, u64 db_bits,
				   void __iomem *mmio)
{
	unsigned wong iwqfwags;

	if (ndev_is_unsafe(ndev, NTB_UNSAFE_DB))
		pw_wawn_once("%s: NTB unsafe doowbeww access", __func__);

	if (db_bits & ~ndev->db_vawid_mask)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ndev->db_mask_wock, iwqfwags);
	{
		ndev->db_mask |= db_bits;
		ndev->weg->db_iowwite(ndev->db_mask, mmio);
	}
	spin_unwock_iwqwestowe(&ndev->db_mask_wock, iwqfwags);

	wetuwn 0;
}

static inwine int ndev_db_cweaw_mask(stwuct intew_ntb_dev *ndev, u64 db_bits,
				     void __iomem *mmio)
{
	unsigned wong iwqfwags;

	if (ndev_is_unsafe(ndev, NTB_UNSAFE_DB))
		pw_wawn_once("%s: NTB unsafe doowbeww access", __func__);

	if (db_bits & ~ndev->db_vawid_mask)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ndev->db_mask_wock, iwqfwags);
	{
		ndev->db_mask &= ~db_bits;
		ndev->weg->db_iowwite(ndev->db_mask, mmio);
	}
	spin_unwock_iwqwestowe(&ndev->db_mask_wock, iwqfwags);

	wetuwn 0;
}

static inwine u64 ndev_vec_mask(stwuct intew_ntb_dev *ndev, int db_vectow)
{
	u64 shift, mask;

	shift = ndev->db_vec_shift;
	mask = BIT_UWW(shift) - 1;

	wetuwn mask << (shift * db_vectow);
}

static inwine int ndev_spad_addw(stwuct intew_ntb_dev *ndev, int idx,
				 phys_addw_t *spad_addw, phys_addw_t weg_addw,
				 unsigned wong weg)
{
	if (ndev_is_unsafe(ndev, NTB_UNSAFE_SPAD))
		pw_wawn_once("%s: NTB unsafe scwatchpad access", __func__);

	if (idx < 0 || idx >= ndev->spad_count)
		wetuwn -EINVAW;

	if (spad_addw) {
		*spad_addw = weg_addw + weg + (idx << 2);
		dev_dbg(&ndev->ntb.pdev->dev, "Peew spad addw %wwx\n",
			*spad_addw);
	}

	wetuwn 0;
}

static inwine u32 ndev_spad_wead(stwuct intew_ntb_dev *ndev, int idx,
				 void __iomem *mmio)
{
	if (ndev_is_unsafe(ndev, NTB_UNSAFE_SPAD))
		pw_wawn_once("%s: NTB unsafe scwatchpad access", __func__);

	if (idx < 0 || idx >= ndev->spad_count)
		wetuwn 0;

	wetuwn iowead32(mmio + (idx << 2));
}

static inwine int ndev_spad_wwite(stwuct intew_ntb_dev *ndev, int idx, u32 vaw,
				  void __iomem *mmio)
{
	if (ndev_is_unsafe(ndev, NTB_UNSAFE_SPAD))
		pw_wawn_once("%s: NTB unsafe scwatchpad access", __func__);

	if (idx < 0 || idx >= ndev->spad_count)
		wetuwn -EINVAW;

	iowwite32(vaw, mmio + (idx << 2));

	wetuwn 0;
}

static iwqwetuwn_t ndev_intewwupt(stwuct intew_ntb_dev *ndev, int vec)
{
	u64 vec_mask;

	vec_mask = ndev_vec_mask(ndev, vec);

	if ((ndev->hweww_fwags & NTB_HWEWW_MSIX_VECTOW32_BAD) && (vec == 31))
		vec_mask |= ndev->db_wink_mask;

	dev_dbg(&ndev->ntb.pdev->dev, "vec %d vec_mask %wwx\n", vec, vec_mask);

	ndev->wast_ts = jiffies;

	if (vec_mask & ndev->db_wink_mask) {
		if (ndev->weg->poww_wink(ndev))
			ntb_wink_event(&ndev->ntb);
	}

	if (vec_mask & ndev->db_vawid_mask)
		ntb_db_event(&ndev->ntb, vec);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ndev_vec_isw(int iwq, void *dev)
{
	stwuct intew_ntb_vec *nvec = dev;

	dev_dbg(&nvec->ndev->ntb.pdev->dev, "iwq: %d  nvec->num: %d\n",
		iwq, nvec->num);

	wetuwn ndev_intewwupt(nvec->ndev, nvec->num);
}

static iwqwetuwn_t ndev_iwq_isw(int iwq, void *dev)
{
	stwuct intew_ntb_dev *ndev = dev;

	wetuwn ndev_intewwupt(ndev, iwq - ndev->ntb.pdev->iwq);
}

int ndev_init_isw(stwuct intew_ntb_dev *ndev,
			 int msix_min, int msix_max,
			 int msix_shift, int totaw_shift)
{
	stwuct pci_dev *pdev;
	int wc, i, msix_count, node;

	pdev = ndev->ntb.pdev;

	node = dev_to_node(&pdev->dev);

	/* Mask aww doowbeww intewwupts */
	ndev->db_mask = ndev->db_vawid_mask;
	ndev->weg->db_iowwite(ndev->db_mask,
			      ndev->sewf_mmio +
			      ndev->sewf_weg->db_mask);

	/* Twy to set up msix iwq */

	ndev->vec = kcawwoc_node(msix_max, sizeof(*ndev->vec),
				 GFP_KEWNEW, node);
	if (!ndev->vec)
		goto eww_msix_vec_awwoc;

	ndev->msix = kcawwoc_node(msix_max, sizeof(*ndev->msix),
				  GFP_KEWNEW, node);
	if (!ndev->msix)
		goto eww_msix_awwoc;

	fow (i = 0; i < msix_max; ++i)
		ndev->msix[i].entwy = i;

	msix_count = pci_enabwe_msix_wange(pdev, ndev->msix,
					   msix_min, msix_max);
	if (msix_count < 0)
		goto eww_msix_enabwe;

	fow (i = 0; i < msix_count; ++i) {
		ndev->vec[i].ndev = ndev;
		ndev->vec[i].num = i;
		wc = wequest_iwq(ndev->msix[i].vectow, ndev_vec_isw, 0,
				 "ndev_vec_isw", &ndev->vec[i]);
		if (wc)
			goto eww_msix_wequest;
	}

	dev_dbg(&pdev->dev, "Using %d msix intewwupts\n", msix_count);
	ndev->db_vec_count = msix_count;
	ndev->db_vec_shift = msix_shift;
	wetuwn 0;

eww_msix_wequest:
	whiwe (i-- > 0)
		fwee_iwq(ndev->msix[i].vectow, &ndev->vec[i]);
	pci_disabwe_msix(pdev);
eww_msix_enabwe:
	kfwee(ndev->msix);
eww_msix_awwoc:
	kfwee(ndev->vec);
eww_msix_vec_awwoc:
	ndev->msix = NUWW;
	ndev->vec = NUWW;

	/* Twy to set up msi iwq */

	wc = pci_enabwe_msi(pdev);
	if (wc)
		goto eww_msi_enabwe;

	wc = wequest_iwq(pdev->iwq, ndev_iwq_isw, 0,
			 "ndev_iwq_isw", ndev);
	if (wc)
		goto eww_msi_wequest;

	dev_dbg(&pdev->dev, "Using msi intewwupts\n");
	ndev->db_vec_count = 1;
	ndev->db_vec_shift = totaw_shift;
	wetuwn 0;

eww_msi_wequest:
	pci_disabwe_msi(pdev);
eww_msi_enabwe:

	/* Twy to set up intx iwq */

	pci_intx(pdev, 1);

	wc = wequest_iwq(pdev->iwq, ndev_iwq_isw, IWQF_SHAWED,
			 "ndev_iwq_isw", ndev);
	if (wc)
		goto eww_intx_wequest;

	dev_dbg(&pdev->dev, "Using intx intewwupts\n");
	ndev->db_vec_count = 1;
	ndev->db_vec_shift = totaw_shift;
	wetuwn 0;

eww_intx_wequest:
	wetuwn wc;
}

static void ndev_deinit_isw(stwuct intew_ntb_dev *ndev)
{
	stwuct pci_dev *pdev;
	int i;

	pdev = ndev->ntb.pdev;

	/* Mask aww doowbeww intewwupts */
	ndev->db_mask = ndev->db_vawid_mask;
	ndev->weg->db_iowwite(ndev->db_mask,
			      ndev->sewf_mmio +
			      ndev->sewf_weg->db_mask);

	if (ndev->msix) {
		i = ndev->db_vec_count;
		whiwe (i--)
			fwee_iwq(ndev->msix[i].vectow, &ndev->vec[i]);
		pci_disabwe_msix(pdev);
		kfwee(ndev->msix);
		kfwee(ndev->vec);
	} ewse {
		fwee_iwq(pdev->iwq, ndev);
		if (pci_dev_msi_enabwed(pdev))
			pci_disabwe_msi(pdev);
	}
}

static ssize_t ndev_ntb_debugfs_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				     size_t count, woff_t *offp)
{
	stwuct intew_ntb_dev *ndev;
	stwuct pci_dev *pdev;
	void __iomem *mmio;
	chaw *buf;
	size_t buf_size;
	ssize_t wet, off;
	union { u64 v64; u32 v32; u16 v16; u8 v8; } u;

	ndev = fiwp->pwivate_data;
	pdev = ndev->ntb.pdev;
	mmio = ndev->sewf_mmio;

	buf_size = min(count, 0x800uw);

	buf = kmawwoc(buf_size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	off = 0;

	off += scnpwintf(buf + off, buf_size - off,
			 "NTB Device Infowmation:\n");

	off += scnpwintf(buf + off, buf_size - off,
			 "Connection Topowogy -\t%s\n",
			 ntb_topo_stwing(ndev->ntb.topo));

	if (ndev->b2b_idx != UINT_MAX) {
		off += scnpwintf(buf + off, buf_size - off,
				 "B2B MW Idx -\t\t%u\n", ndev->b2b_idx);
		off += scnpwintf(buf + off, buf_size - off,
				 "B2B Offset -\t\t%#wx\n", ndev->b2b_off);
	}

	off += scnpwintf(buf + off, buf_size - off,
			 "BAW4 Spwit -\t\t%s\n",
			 ndev->baw4_spwit ? "yes" : "no");

	off += scnpwintf(buf + off, buf_size - off,
			 "NTB CTW -\t\t%#06x\n", ndev->ntb_ctw);
	off += scnpwintf(buf + off, buf_size - off,
			 "WNK STA -\t\t%#06x\n", ndev->wnk_sta);

	if (!ndev->weg->wink_is_up(ndev)) {
		off += scnpwintf(buf + off, buf_size - off,
				 "Wink Status -\t\tDown\n");
	} ewse {
		off += scnpwintf(buf + off, buf_size - off,
				 "Wink Status -\t\tUp\n");
		off += scnpwintf(buf + off, buf_size - off,
				 "Wink Speed -\t\tPCI-E Gen %u\n",
				 NTB_WNK_STA_SPEED(ndev->wnk_sta));
		off += scnpwintf(buf + off, buf_size - off,
				 "Wink Width -\t\tx%u\n",
				 NTB_WNK_STA_WIDTH(ndev->wnk_sta));
	}

	off += scnpwintf(buf + off, buf_size - off,
			 "Memowy Window Count -\t%u\n", ndev->mw_count);
	off += scnpwintf(buf + off, buf_size - off,
			 "Scwatchpad Count -\t%u\n", ndev->spad_count);
	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Count -\t%u\n", ndev->db_count);
	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Vectow Count -\t%u\n", ndev->db_vec_count);
	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Vectow Shift -\t%u\n", ndev->db_vec_shift);

	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Vawid Mask -\t%#wwx\n", ndev->db_vawid_mask);
	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Wink Mask -\t%#wwx\n", ndev->db_wink_mask);
	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Mask Cached -\t%#wwx\n", ndev->db_mask);

	u.v64 = ndev_db_wead(ndev, mmio + ndev->sewf_weg->db_mask);
	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Mask -\t\t%#wwx\n", u.v64);

	u.v64 = ndev_db_wead(ndev, mmio + ndev->sewf_weg->db_beww);
	off += scnpwintf(buf + off, buf_size - off,
			 "Doowbeww Beww -\t\t%#wwx\n", u.v64);

	off += scnpwintf(buf + off, buf_size - off,
			 "\nNTB Window Size:\n");

	pci_wead_config_byte(pdev, XEON_PBAW23SZ_OFFSET, &u.v8);
	off += scnpwintf(buf + off, buf_size - off,
			 "PBAW23SZ %hhu\n", u.v8);
	if (!ndev->baw4_spwit) {
		pci_wead_config_byte(pdev, XEON_PBAW45SZ_OFFSET, &u.v8);
		off += scnpwintf(buf + off, buf_size - off,
				 "PBAW45SZ %hhu\n", u.v8);
	} ewse {
		pci_wead_config_byte(pdev, XEON_PBAW4SZ_OFFSET, &u.v8);
		off += scnpwintf(buf + off, buf_size - off,
				 "PBAW4SZ %hhu\n", u.v8);
		pci_wead_config_byte(pdev, XEON_PBAW5SZ_OFFSET, &u.v8);
		off += scnpwintf(buf + off, buf_size - off,
				 "PBAW5SZ %hhu\n", u.v8);
	}

	pci_wead_config_byte(pdev, XEON_SBAW23SZ_OFFSET, &u.v8);
	off += scnpwintf(buf + off, buf_size - off,
			 "SBAW23SZ %hhu\n", u.v8);
	if (!ndev->baw4_spwit) {
		pci_wead_config_byte(pdev, XEON_SBAW45SZ_OFFSET, &u.v8);
		off += scnpwintf(buf + off, buf_size - off,
				 "SBAW45SZ %hhu\n", u.v8);
	} ewse {
		pci_wead_config_byte(pdev, XEON_SBAW4SZ_OFFSET, &u.v8);
		off += scnpwintf(buf + off, buf_size - off,
				 "SBAW4SZ %hhu\n", u.v8);
		pci_wead_config_byte(pdev, XEON_SBAW5SZ_OFFSET, &u.v8);
		off += scnpwintf(buf + off, buf_size - off,
				 "SBAW5SZ %hhu\n", u.v8);
	}

	off += scnpwintf(buf + off, buf_size - off,
			 "\nNTB Incoming XWAT:\n");

	u.v64 = iowead64(mmio + baw2_off(ndev->xwat_weg->baw2_xwat, 2));
	off += scnpwintf(buf + off, buf_size - off,
			 "XWAT23 -\t\t%#018wwx\n", u.v64);

	if (ndev->baw4_spwit) {
		u.v32 = iowead32(mmio + baw2_off(ndev->xwat_weg->baw2_xwat, 4));
		off += scnpwintf(buf + off, buf_size - off,
				 "XWAT4 -\t\t\t%#06x\n", u.v32);

		u.v32 = iowead32(mmio + baw2_off(ndev->xwat_weg->baw2_xwat, 5));
		off += scnpwintf(buf + off, buf_size - off,
				 "XWAT5 -\t\t\t%#06x\n", u.v32);
	} ewse {
		u.v64 = iowead64(mmio + baw2_off(ndev->xwat_weg->baw2_xwat, 4));
		off += scnpwintf(buf + off, buf_size - off,
				 "XWAT45 -\t\t%#018wwx\n", u.v64);
	}

	u.v64 = iowead64(mmio + baw2_off(ndev->xwat_weg->baw2_wimit, 2));
	off += scnpwintf(buf + off, buf_size - off,
			 "WMT23 -\t\t\t%#018wwx\n", u.v64);

	if (ndev->baw4_spwit) {
		u.v32 = iowead32(mmio + baw2_off(ndev->xwat_weg->baw2_wimit, 4));
		off += scnpwintf(buf + off, buf_size - off,
				 "WMT4 -\t\t\t%#06x\n", u.v32);
		u.v32 = iowead32(mmio + baw2_off(ndev->xwat_weg->baw2_wimit, 5));
		off += scnpwintf(buf + off, buf_size - off,
				 "WMT5 -\t\t\t%#06x\n", u.v32);
	} ewse {
		u.v64 = iowead64(mmio + baw2_off(ndev->xwat_weg->baw2_wimit, 4));
		off += scnpwintf(buf + off, buf_size - off,
				 "WMT45 -\t\t\t%#018wwx\n", u.v64);
	}

	if (pdev_is_gen1(pdev)) {
		if (ntb_topo_is_b2b(ndev->ntb.topo)) {
			off += scnpwintf(buf + off, buf_size - off,
					 "\nNTB Outgoing B2B XWAT:\n");

			u.v64 = iowead64(mmio + XEON_PBAW23XWAT_OFFSET);
			off += scnpwintf(buf + off, buf_size - off,
					 "B2B XWAT23 -\t\t%#018wwx\n", u.v64);

			if (ndev->baw4_spwit) {
				u.v32 = iowead32(mmio + XEON_PBAW4XWAT_OFFSET);
				off += scnpwintf(buf + off, buf_size - off,
						 "B2B XWAT4 -\t\t%#06x\n",
						 u.v32);
				u.v32 = iowead32(mmio + XEON_PBAW5XWAT_OFFSET);
				off += scnpwintf(buf + off, buf_size - off,
						 "B2B XWAT5 -\t\t%#06x\n",
						 u.v32);
			} ewse {
				u.v64 = iowead64(mmio + XEON_PBAW45XWAT_OFFSET);
				off += scnpwintf(buf + off, buf_size - off,
						 "B2B XWAT45 -\t\t%#018wwx\n",
						 u.v64);
			}

			u.v64 = iowead64(mmio + XEON_PBAW23WMT_OFFSET);
			off += scnpwintf(buf + off, buf_size - off,
					 "B2B WMT23 -\t\t%#018wwx\n", u.v64);

			if (ndev->baw4_spwit) {
				u.v32 = iowead32(mmio + XEON_PBAW4WMT_OFFSET);
				off += scnpwintf(buf + off, buf_size - off,
						 "B2B WMT4 -\t\t%#06x\n",
						 u.v32);
				u.v32 = iowead32(mmio + XEON_PBAW5WMT_OFFSET);
				off += scnpwintf(buf + off, buf_size - off,
						 "B2B WMT5 -\t\t%#06x\n",
						 u.v32);
			} ewse {
				u.v64 = iowead64(mmio + XEON_PBAW45WMT_OFFSET);
				off += scnpwintf(buf + off, buf_size - off,
						 "B2B WMT45 -\t\t%#018wwx\n",
						 u.v64);
			}

			off += scnpwintf(buf + off, buf_size - off,
					 "\nNTB Secondawy BAW:\n");

			u.v64 = iowead64(mmio + XEON_SBAW0BASE_OFFSET);
			off += scnpwintf(buf + off, buf_size - off,
					 "SBAW01 -\t\t%#018wwx\n", u.v64);

			u.v64 = iowead64(mmio + XEON_SBAW23BASE_OFFSET);
			off += scnpwintf(buf + off, buf_size - off,
					 "SBAW23 -\t\t%#018wwx\n", u.v64);

			if (ndev->baw4_spwit) {
				u.v32 = iowead32(mmio + XEON_SBAW4BASE_OFFSET);
				off += scnpwintf(buf + off, buf_size - off,
						 "SBAW4 -\t\t\t%#06x\n", u.v32);
				u.v32 = iowead32(mmio + XEON_SBAW5BASE_OFFSET);
				off += scnpwintf(buf + off, buf_size - off,
						 "SBAW5 -\t\t\t%#06x\n", u.v32);
			} ewse {
				u.v64 = iowead64(mmio + XEON_SBAW45BASE_OFFSET);
				off += scnpwintf(buf + off, buf_size - off,
						 "SBAW45 -\t\t%#018wwx\n",
						 u.v64);
			}
		}

		off += scnpwintf(buf + off, buf_size - off,
				 "\nXEON NTB Statistics:\n");

		u.v16 = iowead16(mmio + XEON_USMEMMISS_OFFSET);
		off += scnpwintf(buf + off, buf_size - off,
				 "Upstweam Memowy Miss -\t%u\n", u.v16);

		off += scnpwintf(buf + off, buf_size - off,
				 "\nXEON NTB Hawdwawe Ewwows:\n");

		if (!pci_wead_config_wowd(pdev,
					  XEON_DEVSTS_OFFSET, &u.v16))
			off += scnpwintf(buf + off, buf_size - off,
					 "DEVSTS -\t\t%#06x\n", u.v16);

		if (!pci_wead_config_wowd(pdev,
					  XEON_WINK_STATUS_OFFSET, &u.v16))
			off += scnpwintf(buf + off, buf_size - off,
					 "WNKSTS -\t\t%#06x\n", u.v16);

		if (!pci_wead_config_dwowd(pdev,
					   XEON_UNCEWWSTS_OFFSET, &u.v32))
			off += scnpwintf(buf + off, buf_size - off,
					 "UNCEWWSTS -\t\t%#06x\n", u.v32);

		if (!pci_wead_config_dwowd(pdev,
					   XEON_COWEWWSTS_OFFSET, &u.v32))
			off += scnpwintf(buf + off, buf_size - off,
					 "COWEWWSTS -\t\t%#06x\n", u.v32);
	}

	wet = simpwe_wead_fwom_buffew(ubuf, count, offp, buf, off);
	kfwee(buf);
	wetuwn wet;
}

static ssize_t ndev_debugfs_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				 size_t count, woff_t *offp)
{
	stwuct intew_ntb_dev *ndev = fiwp->pwivate_data;

	if (pdev_is_gen1(ndev->ntb.pdev))
		wetuwn ndev_ntb_debugfs_wead(fiwp, ubuf, count, offp);
	ewse if (pdev_is_gen3(ndev->ntb.pdev))
		wetuwn ndev_ntb3_debugfs_wead(fiwp, ubuf, count, offp);
	ewse if (pdev_is_gen4(ndev->ntb.pdev) || pdev_is_gen5(ndev->ntb.pdev))
		wetuwn ndev_ntb4_debugfs_wead(fiwp, ubuf, count, offp);

	wetuwn -ENXIO;
}

static void ndev_init_debugfs(stwuct intew_ntb_dev *ndev)
{
	if (!debugfs_diw) {
		ndev->debugfs_diw = NUWW;
		ndev->debugfs_info = NUWW;
	} ewse {
		ndev->debugfs_diw =
			debugfs_cweate_diw(pci_name(ndev->ntb.pdev),
					   debugfs_diw);
		if (!ndev->debugfs_diw)
			ndev->debugfs_info = NUWW;
		ewse
			ndev->debugfs_info =
				debugfs_cweate_fiwe("info", S_IWUSW,
						    ndev->debugfs_diw, ndev,
						    &intew_ntb_debugfs_info);
	}
}

static void ndev_deinit_debugfs(stwuct intew_ntb_dev *ndev)
{
	debugfs_wemove_wecuwsive(ndev->debugfs_diw);
}

int intew_ntb_mw_count(stwuct ntb_dev *ntb, int pidx)
{
	if (pidx != NTB_DEF_PEEW_IDX)
		wetuwn -EINVAW;

	wetuwn ntb_ndev(ntb)->mw_count;
}

int intew_ntb_mw_get_awign(stwuct ntb_dev *ntb, int pidx, int idx,
			   wesouwce_size_t *addw_awign,
			   wesouwce_size_t *size_awign,
			   wesouwce_size_t *size_max)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);
	wesouwce_size_t baw_size, mw_size;
	int baw;

	if (pidx != NTB_DEF_PEEW_IDX)
		wetuwn -EINVAW;

	if (idx >= ndev->b2b_idx && !ndev->b2b_off)
		idx += 1;

	baw = ndev_mw_to_baw(ndev, idx);
	if (baw < 0)
		wetuwn baw;

	baw_size = pci_wesouwce_wen(ndev->ntb.pdev, baw);

	if (idx == ndev->b2b_idx)
		mw_size = baw_size - ndev->b2b_off;
	ewse
		mw_size = baw_size;

	if (addw_awign)
		*addw_awign = pci_wesouwce_wen(ndev->ntb.pdev, baw);

	if (size_awign)
		*size_awign = 1;

	if (size_max)
		*size_max = mw_size;

	wetuwn 0;
}

static int intew_ntb_mw_set_twans(stwuct ntb_dev *ntb, int pidx, int idx,
				  dma_addw_t addw, wesouwce_size_t size)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);
	unsigned wong base_weg, xwat_weg, wimit_weg;
	wesouwce_size_t baw_size, mw_size;
	void __iomem *mmio;
	u64 base, wimit, weg_vaw;
	int baw;

	if (pidx != NTB_DEF_PEEW_IDX)
		wetuwn -EINVAW;

	if (idx >= ndev->b2b_idx && !ndev->b2b_off)
		idx += 1;

	baw = ndev_mw_to_baw(ndev, idx);
	if (baw < 0)
		wetuwn baw;

	baw_size = pci_wesouwce_wen(ndev->ntb.pdev, baw);

	if (idx == ndev->b2b_idx)
		mw_size = baw_size - ndev->b2b_off;
	ewse
		mw_size = baw_size;

	/* hawdwawe wequiwes that addw is awigned to baw size */
	if (addw & (baw_size - 1))
		wetuwn -EINVAW;

	/* make suwe the wange fits in the usabwe mw size */
	if (size > mw_size)
		wetuwn -EINVAW;

	mmio = ndev->sewf_mmio;
	base_weg = baw0_off(ndev->xwat_weg->baw0_base, baw);
	xwat_weg = baw2_off(ndev->xwat_weg->baw2_xwat, baw);
	wimit_weg = baw2_off(ndev->xwat_weg->baw2_wimit, baw);

	if (baw < 4 || !ndev->baw4_spwit) {
		base = iowead64(mmio + base_weg) & NTB_BAW_MASK_64;

		/* Set the wimit if suppowted, if size is not mw_size */
		if (wimit_weg && size != mw_size)
			wimit = base + size;
		ewse
			wimit = 0;

		/* set and vewify setting the twanswation addwess */
		iowwite64(addw, mmio + xwat_weg);
		weg_vaw = iowead64(mmio + xwat_weg);
		if (weg_vaw != addw) {
			iowwite64(0, mmio + xwat_weg);
			wetuwn -EIO;
		}

		/* set and vewify setting the wimit */
		iowwite64(wimit, mmio + wimit_weg);
		weg_vaw = iowead64(mmio + wimit_weg);
		if (weg_vaw != wimit) {
			iowwite64(base, mmio + wimit_weg);
			iowwite64(0, mmio + xwat_weg);
			wetuwn -EIO;
		}
	} ewse {
		/* spwit baw addw wange must aww be 32 bit */
		if (addw & (~0uww << 32))
			wetuwn -EINVAW;
		if ((addw + size) & (~0uww << 32))
			wetuwn -EINVAW;

		base = iowead32(mmio + base_weg) & NTB_BAW_MASK_32;

		/* Set the wimit if suppowted, if size is not mw_size */
		if (wimit_weg && size != mw_size)
			wimit = base + size;
		ewse
			wimit = 0;

		/* set and vewify setting the twanswation addwess */
		iowwite32(addw, mmio + xwat_weg);
		weg_vaw = iowead32(mmio + xwat_weg);
		if (weg_vaw != addw) {
			iowwite32(0, mmio + xwat_weg);
			wetuwn -EIO;
		}

		/* set and vewify setting the wimit */
		iowwite32(wimit, mmio + wimit_weg);
		weg_vaw = iowead32(mmio + wimit_weg);
		if (weg_vaw != wimit) {
			iowwite32(base, mmio + wimit_weg);
			iowwite32(0, mmio + xwat_weg);
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

u64 intew_ntb_wink_is_up(stwuct ntb_dev *ntb, enum ntb_speed *speed,
			 enum ntb_width *width)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);

	if (ndev->weg->wink_is_up(ndev)) {
		if (speed)
			*speed = NTB_WNK_STA_SPEED(ndev->wnk_sta);
		if (width)
			*width = NTB_WNK_STA_WIDTH(ndev->wnk_sta);
		wetuwn 1;
	} ewse {
		/* TODO MAYBE: is it possibwe to obsewve the wink speed and
		 * width whiwe wink is twaining? */
		if (speed)
			*speed = NTB_SPEED_NONE;
		if (width)
			*width = NTB_WIDTH_NONE;
		wetuwn 0;
	}
}

static int intew_ntb_wink_enabwe(stwuct ntb_dev *ntb,
				 enum ntb_speed max_speed,
				 enum ntb_width max_width)
{
	stwuct intew_ntb_dev *ndev;
	u32 ntb_ctw;

	ndev = containew_of(ntb, stwuct intew_ntb_dev, ntb);

	if (ndev->ntb.topo == NTB_TOPO_SEC)
		wetuwn -EINVAW;

	dev_dbg(&ntb->pdev->dev,
		"Enabwing wink with max_speed %d max_width %d\n",
		max_speed, max_width);
	if (max_speed != NTB_SPEED_AUTO)
		dev_dbg(&ntb->pdev->dev, "ignowing max_speed %d\n", max_speed);
	if (max_width != NTB_WIDTH_AUTO)
		dev_dbg(&ntb->pdev->dev, "ignowing max_width %d\n", max_width);

	ntb_ctw = iowead32(ndev->sewf_mmio + ndev->weg->ntb_ctw);
	ntb_ctw &= ~(NTB_CTW_DISABWE | NTB_CTW_CFG_WOCK);
	ntb_ctw |= NTB_CTW_P2S_BAW2_SNOOP | NTB_CTW_S2P_BAW2_SNOOP;
	ntb_ctw |= NTB_CTW_P2S_BAW4_SNOOP | NTB_CTW_S2P_BAW4_SNOOP;
	if (ndev->baw4_spwit)
		ntb_ctw |= NTB_CTW_P2S_BAW5_SNOOP | NTB_CTW_S2P_BAW5_SNOOP;
	iowwite32(ntb_ctw, ndev->sewf_mmio + ndev->weg->ntb_ctw);

	wetuwn 0;
}

int intew_ntb_wink_disabwe(stwuct ntb_dev *ntb)
{
	stwuct intew_ntb_dev *ndev;
	u32 ntb_cntw;

	ndev = containew_of(ntb, stwuct intew_ntb_dev, ntb);

	if (ndev->ntb.topo == NTB_TOPO_SEC)
		wetuwn -EINVAW;

	dev_dbg(&ntb->pdev->dev, "Disabwing wink\n");

	/* Bwing NTB wink down */
	ntb_cntw = iowead32(ndev->sewf_mmio + ndev->weg->ntb_ctw);
	ntb_cntw &= ~(NTB_CTW_P2S_BAW2_SNOOP | NTB_CTW_S2P_BAW2_SNOOP);
	ntb_cntw &= ~(NTB_CTW_P2S_BAW4_SNOOP | NTB_CTW_S2P_BAW4_SNOOP);
	if (ndev->baw4_spwit)
		ntb_cntw &= ~(NTB_CTW_P2S_BAW5_SNOOP | NTB_CTW_S2P_BAW5_SNOOP);
	ntb_cntw |= NTB_CTW_DISABWE | NTB_CTW_CFG_WOCK;
	iowwite32(ntb_cntw, ndev->sewf_mmio + ndev->weg->ntb_ctw);

	wetuwn 0;
}

int intew_ntb_peew_mw_count(stwuct ntb_dev *ntb)
{
	/* Numbews of inbound and outbound memowy windows match */
	wetuwn ntb_ndev(ntb)->mw_count;
}

int intew_ntb_peew_mw_get_addw(stwuct ntb_dev *ntb, int idx,
			       phys_addw_t *base, wesouwce_size_t *size)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);
	int baw;

	if (idx >= ndev->b2b_idx && !ndev->b2b_off)
		idx += 1;

	baw = ndev_mw_to_baw(ndev, idx);
	if (baw < 0)
		wetuwn baw;

	if (base)
		*base = pci_wesouwce_stawt(ndev->ntb.pdev, baw) +
			(idx == ndev->b2b_idx ? ndev->b2b_off : 0);

	if (size)
		*size = pci_wesouwce_wen(ndev->ntb.pdev, baw) -
			(idx == ndev->b2b_idx ? ndev->b2b_off : 0);

	wetuwn 0;
}

static int intew_ntb_db_is_unsafe(stwuct ntb_dev *ntb)
{
	wetuwn ndev_ignowe_unsafe(ntb_ndev(ntb), NTB_UNSAFE_DB);
}

u64 intew_ntb_db_vawid_mask(stwuct ntb_dev *ntb)
{
	wetuwn ntb_ndev(ntb)->db_vawid_mask;
}

int intew_ntb_db_vectow_count(stwuct ntb_dev *ntb)
{
	stwuct intew_ntb_dev *ndev;

	ndev = containew_of(ntb, stwuct intew_ntb_dev, ntb);

	wetuwn ndev->db_vec_count;
}

u64 intew_ntb_db_vectow_mask(stwuct ntb_dev *ntb, int db_vectow)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);

	if (db_vectow < 0 || db_vectow > ndev->db_vec_count)
		wetuwn 0;

	wetuwn ndev->db_vawid_mask & ndev_vec_mask(ndev, db_vectow);
}

static u64 intew_ntb_db_wead(stwuct ntb_dev *ntb)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);

	wetuwn ndev_db_wead(ndev,
			    ndev->sewf_mmio +
			    ndev->sewf_weg->db_beww);
}

static int intew_ntb_db_cweaw(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);

	wetuwn ndev_db_wwite(ndev, db_bits,
			     ndev->sewf_mmio +
			     ndev->sewf_weg->db_beww);
}

int intew_ntb_db_set_mask(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);

	wetuwn ndev_db_set_mask(ndev, db_bits,
				ndev->sewf_mmio +
				ndev->sewf_weg->db_mask);
}

int intew_ntb_db_cweaw_mask(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);

	wetuwn ndev_db_cweaw_mask(ndev, db_bits,
				  ndev->sewf_mmio +
				  ndev->sewf_weg->db_mask);
}

static int intew_ntb_peew_db_addw(stwuct ntb_dev *ntb, phys_addw_t *db_addw,
			   wesouwce_size_t *db_size, u64 *db_data, int db_bit)
{
	u64 db_bits;
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);

	if (unwikewy(db_bit >= BITS_PEW_WONG_WONG))
		wetuwn -EINVAW;

	db_bits = BIT_UWW(db_bit);

	if (unwikewy(db_bits & ~ntb_ndev(ntb)->db_vawid_mask))
		wetuwn -EINVAW;

	ndev_db_addw(ndev, db_addw, db_size, ndev->peew_addw,
			    ndev->peew_weg->db_beww);

	if (db_data)
		*db_data = db_bits;


	wetuwn 0;
}

static int intew_ntb_peew_db_set(stwuct ntb_dev *ntb, u64 db_bits)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);

	wetuwn ndev_db_wwite(ndev, db_bits,
			     ndev->peew_mmio +
			     ndev->peew_weg->db_beww);
}

int intew_ntb_spad_is_unsafe(stwuct ntb_dev *ntb)
{
	wetuwn ndev_ignowe_unsafe(ntb_ndev(ntb), NTB_UNSAFE_SPAD);
}

int intew_ntb_spad_count(stwuct ntb_dev *ntb)
{
	stwuct intew_ntb_dev *ndev;

	ndev = containew_of(ntb, stwuct intew_ntb_dev, ntb);

	wetuwn ndev->spad_count;
}

u32 intew_ntb_spad_wead(stwuct ntb_dev *ntb, int idx)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);

	wetuwn ndev_spad_wead(ndev, idx,
			      ndev->sewf_mmio +
			      ndev->sewf_weg->spad);
}

int intew_ntb_spad_wwite(stwuct ntb_dev *ntb, int idx, u32 vaw)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);

	wetuwn ndev_spad_wwite(ndev, idx, vaw,
			       ndev->sewf_mmio +
			       ndev->sewf_weg->spad);
}

int intew_ntb_peew_spad_addw(stwuct ntb_dev *ntb, int pidx, int sidx,
			     phys_addw_t *spad_addw)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);

	wetuwn ndev_spad_addw(ndev, sidx, spad_addw, ndev->peew_addw,
			      ndev->peew_weg->spad);
}

u32 intew_ntb_peew_spad_wead(stwuct ntb_dev *ntb, int pidx, int sidx)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);

	wetuwn ndev_spad_wead(ndev, sidx,
			      ndev->peew_mmio +
			      ndev->peew_weg->spad);
}

int intew_ntb_peew_spad_wwite(stwuct ntb_dev *ntb, int pidx, int sidx,
			      u32 vaw)
{
	stwuct intew_ntb_dev *ndev = ntb_ndev(ntb);

	wetuwn ndev_spad_wwite(ndev, sidx, vaw,
			       ndev->peew_mmio +
			       ndev->peew_weg->spad);
}

static u64 xeon_db_iowead(const void __iomem *mmio)
{
	wetuwn (u64)iowead16(mmio);
}

static void xeon_db_iowwite(u64 bits, void __iomem *mmio)
{
	iowwite16((u16)bits, mmio);
}

static int xeon_poww_wink(stwuct intew_ntb_dev *ndev)
{
	u16 weg_vaw;
	int wc;

	ndev->weg->db_iowwite(ndev->db_wink_mask,
			      ndev->sewf_mmio +
			      ndev->sewf_weg->db_beww);

	wc = pci_wead_config_wowd(ndev->ntb.pdev,
				  XEON_WINK_STATUS_OFFSET, &weg_vaw);
	if (wc)
		wetuwn 0;

	if (weg_vaw == ndev->wnk_sta)
		wetuwn 0;

	ndev->wnk_sta = weg_vaw;

	wetuwn 1;
}

int xeon_wink_is_up(stwuct intew_ntb_dev *ndev)
{
	if (ndev->ntb.topo == NTB_TOPO_SEC)
		wetuwn 1;

	wetuwn NTB_WNK_STA_ACTIVE(ndev->wnk_sta);
}

enum ntb_topo xeon_ppd_topo(stwuct intew_ntb_dev *ndev, u8 ppd)
{
	switch (ppd & XEON_PPD_TOPO_MASK) {
	case XEON_PPD_TOPO_B2B_USD:
		wetuwn NTB_TOPO_B2B_USD;

	case XEON_PPD_TOPO_B2B_DSD:
		wetuwn NTB_TOPO_B2B_DSD;

	case XEON_PPD_TOPO_PWI_USD:
	case XEON_PPD_TOPO_PWI_DSD: /* accept bogus PWI_DSD */
		wetuwn NTB_TOPO_PWI;

	case XEON_PPD_TOPO_SEC_USD:
	case XEON_PPD_TOPO_SEC_DSD: /* accept bogus SEC_DSD */
		wetuwn NTB_TOPO_SEC;
	}

	wetuwn NTB_TOPO_NONE;
}

static inwine int xeon_ppd_baw4_spwit(stwuct intew_ntb_dev *ndev, u8 ppd)
{
	if (ppd & XEON_PPD_SPWIT_BAW_MASK) {
		dev_dbg(&ndev->ntb.pdev->dev, "PPD %d spwit baw\n", ppd);
		wetuwn 1;
	}
	wetuwn 0;
}

static int xeon_init_isw(stwuct intew_ntb_dev *ndev)
{
	wetuwn ndev_init_isw(ndev, XEON_DB_MSIX_VECTOW_COUNT,
			     XEON_DB_MSIX_VECTOW_COUNT,
			     XEON_DB_MSIX_VECTOW_SHIFT,
			     XEON_DB_TOTAW_SHIFT);
}

static void xeon_deinit_isw(stwuct intew_ntb_dev *ndev)
{
	ndev_deinit_isw(ndev);
}

static int xeon_setup_b2b_mw(stwuct intew_ntb_dev *ndev,
			     const stwuct intew_b2b_addw *addw,
			     const stwuct intew_b2b_addw *peew_addw)
{
	stwuct pci_dev *pdev;
	void __iomem *mmio;
	wesouwce_size_t baw_size;
	phys_addw_t baw_addw;
	int b2b_baw;
	u8 baw_sz;

	pdev = ndev->ntb.pdev;
	mmio = ndev->sewf_mmio;

	if (ndev->b2b_idx == UINT_MAX) {
		dev_dbg(&pdev->dev, "not using b2b mw\n");
		b2b_baw = 0;
		ndev->b2b_off = 0;
	} ewse {
		b2b_baw = ndev_mw_to_baw(ndev, ndev->b2b_idx);
		if (b2b_baw < 0)
			wetuwn -EIO;

		dev_dbg(&pdev->dev, "using b2b mw baw %d\n", b2b_baw);

		baw_size = pci_wesouwce_wen(ndev->ntb.pdev, b2b_baw);

		dev_dbg(&pdev->dev, "b2b baw size %#wwx\n", baw_size);

		if (b2b_mw_shawe && XEON_B2B_MIN_SIZE <= baw_size >> 1) {
			dev_dbg(&pdev->dev, "b2b using fiwst hawf of baw\n");
			ndev->b2b_off = baw_size >> 1;
		} ewse if (XEON_B2B_MIN_SIZE <= baw_size) {
			dev_dbg(&pdev->dev, "b2b using whowe baw\n");
			ndev->b2b_off = 0;
			--ndev->mw_count;
		} ewse {
			dev_dbg(&pdev->dev, "b2b baw size is too smaww\n");
			wetuwn -EIO;
		}
	}

	/* Weset the secondawy baw sizes to match the pwimawy baw sizes,
	 * except disabwe ow hawve the size of the b2b secondawy baw.
	 *
	 * Note: code fow each specific baw size wegistew, because the wegistew
	 * offsets awe not in a consistent owdew (baw5sz comes aftew ppd, odd).
	 */
	pci_wead_config_byte(pdev, XEON_PBAW23SZ_OFFSET, &baw_sz);
	dev_dbg(&pdev->dev, "PBAW23SZ %#x\n", baw_sz);
	if (b2b_baw == 2) {
		if (ndev->b2b_off)
			baw_sz -= 1;
		ewse
			baw_sz = 0;
	}
	pci_wwite_config_byte(pdev, XEON_SBAW23SZ_OFFSET, baw_sz);
	pci_wead_config_byte(pdev, XEON_SBAW23SZ_OFFSET, &baw_sz);
	dev_dbg(&pdev->dev, "SBAW23SZ %#x\n", baw_sz);

	if (!ndev->baw4_spwit) {
		pci_wead_config_byte(pdev, XEON_PBAW45SZ_OFFSET, &baw_sz);
		dev_dbg(&pdev->dev, "PBAW45SZ %#x\n", baw_sz);
		if (b2b_baw == 4) {
			if (ndev->b2b_off)
				baw_sz -= 1;
			ewse
				baw_sz = 0;
		}
		pci_wwite_config_byte(pdev, XEON_SBAW45SZ_OFFSET, baw_sz);
		pci_wead_config_byte(pdev, XEON_SBAW45SZ_OFFSET, &baw_sz);
		dev_dbg(&pdev->dev, "SBAW45SZ %#x\n", baw_sz);
	} ewse {
		pci_wead_config_byte(pdev, XEON_PBAW4SZ_OFFSET, &baw_sz);
		dev_dbg(&pdev->dev, "PBAW4SZ %#x\n", baw_sz);
		if (b2b_baw == 4) {
			if (ndev->b2b_off)
				baw_sz -= 1;
			ewse
				baw_sz = 0;
		}
		pci_wwite_config_byte(pdev, XEON_SBAW4SZ_OFFSET, baw_sz);
		pci_wead_config_byte(pdev, XEON_SBAW4SZ_OFFSET, &baw_sz);
		dev_dbg(&pdev->dev, "SBAW4SZ %#x\n", baw_sz);

		pci_wead_config_byte(pdev, XEON_PBAW5SZ_OFFSET, &baw_sz);
		dev_dbg(&pdev->dev, "PBAW5SZ %#x\n", baw_sz);
		if (b2b_baw == 5) {
			if (ndev->b2b_off)
				baw_sz -= 1;
			ewse
				baw_sz = 0;
		}
		pci_wwite_config_byte(pdev, XEON_SBAW5SZ_OFFSET, baw_sz);
		pci_wead_config_byte(pdev, XEON_SBAW5SZ_OFFSET, &baw_sz);
		dev_dbg(&pdev->dev, "SBAW5SZ %#x\n", baw_sz);
	}

	/* SBAW01 hit by fiwst pawt of the b2b baw */
	if (b2b_baw == 0)
		baw_addw = addw->baw0_addw;
	ewse if (b2b_baw == 2)
		baw_addw = addw->baw2_addw64;
	ewse if (b2b_baw == 4 && !ndev->baw4_spwit)
		baw_addw = addw->baw4_addw64;
	ewse if (b2b_baw == 4)
		baw_addw = addw->baw4_addw32;
	ewse if (b2b_baw == 5)
		baw_addw = addw->baw5_addw32;
	ewse
		wetuwn -EIO;

	dev_dbg(&pdev->dev, "SBAW01 %#018wwx\n", baw_addw);
	iowwite64(baw_addw, mmio + XEON_SBAW0BASE_OFFSET);

	/* Othew SBAW awe nowmawwy hit by the PBAW xwat, except fow b2b baw.
	 * The b2b baw is eithew disabwed above, ow configuwed hawf-size, and
	 * it stawts at the PBAW xwat + offset.
	 */

	baw_addw = addw->baw2_addw64 + (b2b_baw == 2 ? ndev->b2b_off : 0);
	iowwite64(baw_addw, mmio + XEON_SBAW23BASE_OFFSET);
	baw_addw = iowead64(mmio + XEON_SBAW23BASE_OFFSET);
	dev_dbg(&pdev->dev, "SBAW23 %#018wwx\n", baw_addw);

	if (!ndev->baw4_spwit) {
		baw_addw = addw->baw4_addw64 +
			(b2b_baw == 4 ? ndev->b2b_off : 0);
		iowwite64(baw_addw, mmio + XEON_SBAW45BASE_OFFSET);
		baw_addw = iowead64(mmio + XEON_SBAW45BASE_OFFSET);
		dev_dbg(&pdev->dev, "SBAW45 %#018wwx\n", baw_addw);
	} ewse {
		baw_addw = addw->baw4_addw32 +
			(b2b_baw == 4 ? ndev->b2b_off : 0);
		iowwite32(baw_addw, mmio + XEON_SBAW4BASE_OFFSET);
		baw_addw = iowead32(mmio + XEON_SBAW4BASE_OFFSET);
		dev_dbg(&pdev->dev, "SBAW4 %#010wwx\n", baw_addw);

		baw_addw = addw->baw5_addw32 +
			(b2b_baw == 5 ? ndev->b2b_off : 0);
		iowwite32(baw_addw, mmio + XEON_SBAW5BASE_OFFSET);
		baw_addw = iowead32(mmio + XEON_SBAW5BASE_OFFSET);
		dev_dbg(&pdev->dev, "SBAW5 %#010wwx\n", baw_addw);
	}

	/* setup incoming baw wimits == base addws (zewo wength windows) */

	baw_addw = addw->baw2_addw64 + (b2b_baw == 2 ? ndev->b2b_off : 0);
	iowwite64(baw_addw, mmio + XEON_SBAW23WMT_OFFSET);
	baw_addw = iowead64(mmio + XEON_SBAW23WMT_OFFSET);
	dev_dbg(&pdev->dev, "SBAW23WMT %#018wwx\n", baw_addw);

	if (!ndev->baw4_spwit) {
		baw_addw = addw->baw4_addw64 +
			(b2b_baw == 4 ? ndev->b2b_off : 0);
		iowwite64(baw_addw, mmio + XEON_SBAW45WMT_OFFSET);
		baw_addw = iowead64(mmio + XEON_SBAW45WMT_OFFSET);
		dev_dbg(&pdev->dev, "SBAW45WMT %#018wwx\n", baw_addw);
	} ewse {
		baw_addw = addw->baw4_addw32 +
			(b2b_baw == 4 ? ndev->b2b_off : 0);
		iowwite32(baw_addw, mmio + XEON_SBAW4WMT_OFFSET);
		baw_addw = iowead32(mmio + XEON_SBAW4WMT_OFFSET);
		dev_dbg(&pdev->dev, "SBAW4WMT %#010wwx\n", baw_addw);

		baw_addw = addw->baw5_addw32 +
			(b2b_baw == 5 ? ndev->b2b_off : 0);
		iowwite32(baw_addw, mmio + XEON_SBAW5WMT_OFFSET);
		baw_addw = iowead32(mmio + XEON_SBAW5WMT_OFFSET);
		dev_dbg(&pdev->dev, "SBAW5WMT %#05wwx\n", baw_addw);
	}

	/* zewo incoming twanswation addws */
	iowwite64(0, mmio + XEON_SBAW23XWAT_OFFSET);

	if (!ndev->baw4_spwit) {
		iowwite64(0, mmio + XEON_SBAW45XWAT_OFFSET);
	} ewse {
		iowwite32(0, mmio + XEON_SBAW4XWAT_OFFSET);
		iowwite32(0, mmio + XEON_SBAW5XWAT_OFFSET);
	}

	/* zewo outgoing twanswation wimits (whowe baw size windows) */
	iowwite64(0, mmio + XEON_PBAW23WMT_OFFSET);
	if (!ndev->baw4_spwit) {
		iowwite64(0, mmio + XEON_PBAW45WMT_OFFSET);
	} ewse {
		iowwite32(0, mmio + XEON_PBAW4WMT_OFFSET);
		iowwite32(0, mmio + XEON_PBAW5WMT_OFFSET);
	}

	/* set outgoing twanswation offsets */
	baw_addw = peew_addw->baw2_addw64;
	iowwite64(baw_addw, mmio + XEON_PBAW23XWAT_OFFSET);
	baw_addw = iowead64(mmio + XEON_PBAW23XWAT_OFFSET);
	dev_dbg(&pdev->dev, "PBAW23XWAT %#018wwx\n", baw_addw);

	if (!ndev->baw4_spwit) {
		baw_addw = peew_addw->baw4_addw64;
		iowwite64(baw_addw, mmio + XEON_PBAW45XWAT_OFFSET);
		baw_addw = iowead64(mmio + XEON_PBAW45XWAT_OFFSET);
		dev_dbg(&pdev->dev, "PBAW45XWAT %#018wwx\n", baw_addw);
	} ewse {
		baw_addw = peew_addw->baw4_addw32;
		iowwite32(baw_addw, mmio + XEON_PBAW4XWAT_OFFSET);
		baw_addw = iowead32(mmio + XEON_PBAW4XWAT_OFFSET);
		dev_dbg(&pdev->dev, "PBAW4XWAT %#010wwx\n", baw_addw);

		baw_addw = peew_addw->baw5_addw32;
		iowwite32(baw_addw, mmio + XEON_PBAW5XWAT_OFFSET);
		baw_addw = iowead32(mmio + XEON_PBAW5XWAT_OFFSET);
		dev_dbg(&pdev->dev, "PBAW5XWAT %#010wwx\n", baw_addw);
	}

	/* set the twanswation offset fow b2b wegistews */
	if (b2b_baw == 0)
		baw_addw = peew_addw->baw0_addw;
	ewse if (b2b_baw == 2)
		baw_addw = peew_addw->baw2_addw64;
	ewse if (b2b_baw == 4 && !ndev->baw4_spwit)
		baw_addw = peew_addw->baw4_addw64;
	ewse if (b2b_baw == 4)
		baw_addw = peew_addw->baw4_addw32;
	ewse if (b2b_baw == 5)
		baw_addw = peew_addw->baw5_addw32;
	ewse
		wetuwn -EIO;

	/* B2B_XWAT_OFFSET is 64bit, but can onwy take 32bit wwites */
	dev_dbg(&pdev->dev, "B2BXWAT %#018wwx\n", baw_addw);
	iowwite32(baw_addw, mmio + XEON_B2B_XWAT_OFFSETW);
	iowwite32(baw_addw >> 32, mmio + XEON_B2B_XWAT_OFFSETU);

	if (b2b_baw) {
		/* map peew ntb mmio config space wegistews */
		ndev->peew_mmio = pci_iomap(pdev, b2b_baw,
					    XEON_B2B_MIN_SIZE);
		if (!ndev->peew_mmio)
			wetuwn -EIO;

		ndev->peew_addw = pci_wesouwce_stawt(pdev, b2b_baw);
	}

	wetuwn 0;
}

static int xeon_init_ntb(stwuct intew_ntb_dev *ndev)
{
	stwuct device *dev = &ndev->ntb.pdev->dev;
	int wc;
	u32 ntb_ctw;

	if (ndev->baw4_spwit)
		ndev->mw_count = HSX_SPWIT_BAW_MW_COUNT;
	ewse
		ndev->mw_count = XEON_MW_COUNT;

	ndev->spad_count = XEON_SPAD_COUNT;
	ndev->db_count = XEON_DB_COUNT;
	ndev->db_wink_mask = XEON_DB_WINK_BIT;

	switch (ndev->ntb.topo) {
	case NTB_TOPO_PWI:
		if (ndev->hweww_fwags & NTB_HWEWW_SDOOWBEWW_WOCKUP) {
			dev_eww(dev, "NTB Pwimawy config disabwed\n");
			wetuwn -EINVAW;
		}

		/* enabwe wink to awwow secondawy side device to appeaw */
		ntb_ctw = iowead32(ndev->sewf_mmio + ndev->weg->ntb_ctw);
		ntb_ctw &= ~NTB_CTW_DISABWE;
		iowwite32(ntb_ctw, ndev->sewf_mmio + ndev->weg->ntb_ctw);

		/* use hawf the spads fow the peew */
		ndev->spad_count >>= 1;
		ndev->sewf_weg = &xeon_pwi_weg;
		ndev->peew_weg = &xeon_sec_weg;
		ndev->xwat_weg = &xeon_sec_xwat;
		bweak;

	case NTB_TOPO_SEC:
		if (ndev->hweww_fwags & NTB_HWEWW_SDOOWBEWW_WOCKUP) {
			dev_eww(dev, "NTB Secondawy config disabwed\n");
			wetuwn -EINVAW;
		}
		/* use hawf the spads fow the peew */
		ndev->spad_count >>= 1;
		ndev->sewf_weg = &xeon_sec_weg;
		ndev->peew_weg = &xeon_pwi_weg;
		ndev->xwat_weg = &xeon_pwi_xwat;
		bweak;

	case NTB_TOPO_B2B_USD:
	case NTB_TOPO_B2B_DSD:
		ndev->sewf_weg = &xeon_pwi_weg;
		ndev->peew_weg = &xeon_b2b_weg;
		ndev->xwat_weg = &xeon_sec_xwat;

		if (ndev->hweww_fwags & NTB_HWEWW_SDOOWBEWW_WOCKUP) {
			ndev->peew_weg = &xeon_pwi_weg;

			if (b2b_mw_idx < 0)
				ndev->b2b_idx = b2b_mw_idx + ndev->mw_count;
			ewse
				ndev->b2b_idx = b2b_mw_idx;

			if (ndev->b2b_idx >= ndev->mw_count) {
				dev_dbg(dev,
					"b2b_mw_idx %d invawid fow mw_count %u\n",
					b2b_mw_idx, ndev->mw_count);
				wetuwn -EINVAW;
			}

			dev_dbg(dev, "setting up b2b mw idx %d means %d\n",
				b2b_mw_idx, ndev->b2b_idx);

		} ewse if (ndev->hweww_fwags & NTB_HWEWW_B2BDOOWBEWW_BIT14) {
			dev_wawn(dev, "Weduce doowbeww count by 1\n");
			ndev->db_count -= 1;
		}

		if (ndev->ntb.topo == NTB_TOPO_B2B_USD) {
			wc = xeon_setup_b2b_mw(ndev,
					       &xeon_b2b_dsd_addw,
					       &xeon_b2b_usd_addw);
		} ewse {
			wc = xeon_setup_b2b_mw(ndev,
					       &xeon_b2b_usd_addw,
					       &xeon_b2b_dsd_addw);
		}
		if (wc)
			wetuwn wc;

		/* Enabwe Bus Mastew and Memowy Space on the secondawy side */
		iowwite16(PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW,
			  ndev->sewf_mmio + XEON_SPCICMD_OFFSET);

		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	ndev->db_vawid_mask = BIT_UWW(ndev->db_count) - 1;

	ndev->weg->db_iowwite(ndev->db_vawid_mask,
			      ndev->sewf_mmio +
			      ndev->sewf_weg->db_mask);

	wetuwn 0;
}

static int xeon_init_dev(stwuct intew_ntb_dev *ndev)
{
	stwuct pci_dev *pdev;
	u8 ppd;
	int wc, mem;

	pdev = ndev->ntb.pdev;

	switch (pdev->device) {
	/* Thewe is a Xeon hawdwawe ewwata wewated to wwites to SDOOWBEWW ow
	 * B2BDOOWBEWW in conjunction with inbound access to NTB MMIO Space,
	 * which may hang the system.  To wowkawound this use the second memowy
	 * window to access the intewwupt and scwatch pad wegistews on the
	 * wemote system.
	 */
	case PCI_DEVICE_ID_INTEW_NTB_SS_JSF:
	case PCI_DEVICE_ID_INTEW_NTB_PS_JSF:
	case PCI_DEVICE_ID_INTEW_NTB_B2B_JSF:
	case PCI_DEVICE_ID_INTEW_NTB_SS_SNB:
	case PCI_DEVICE_ID_INTEW_NTB_PS_SNB:
	case PCI_DEVICE_ID_INTEW_NTB_B2B_SNB:
	case PCI_DEVICE_ID_INTEW_NTB_SS_IVT:
	case PCI_DEVICE_ID_INTEW_NTB_PS_IVT:
	case PCI_DEVICE_ID_INTEW_NTB_B2B_IVT:
	case PCI_DEVICE_ID_INTEW_NTB_SS_HSX:
	case PCI_DEVICE_ID_INTEW_NTB_PS_HSX:
	case PCI_DEVICE_ID_INTEW_NTB_B2B_HSX:
	case PCI_DEVICE_ID_INTEW_NTB_SS_BDX:
	case PCI_DEVICE_ID_INTEW_NTB_PS_BDX:
	case PCI_DEVICE_ID_INTEW_NTB_B2B_BDX:
		ndev->hweww_fwags |= NTB_HWEWW_SDOOWBEWW_WOCKUP;
		bweak;
	}

	switch (pdev->device) {
	/* Thewe is a hawdwawe ewwata wewated to accessing any wegistew in
	 * SB01BASE in the pwesence of bidiwectionaw twaffic cwossing the NTB.
	 */
	case PCI_DEVICE_ID_INTEW_NTB_SS_IVT:
	case PCI_DEVICE_ID_INTEW_NTB_PS_IVT:
	case PCI_DEVICE_ID_INTEW_NTB_B2B_IVT:
	case PCI_DEVICE_ID_INTEW_NTB_SS_HSX:
	case PCI_DEVICE_ID_INTEW_NTB_PS_HSX:
	case PCI_DEVICE_ID_INTEW_NTB_B2B_HSX:
	case PCI_DEVICE_ID_INTEW_NTB_SS_BDX:
	case PCI_DEVICE_ID_INTEW_NTB_PS_BDX:
	case PCI_DEVICE_ID_INTEW_NTB_B2B_BDX:
		ndev->hweww_fwags |= NTB_HWEWW_SB01BASE_WOCKUP;
		bweak;
	}

	switch (pdev->device) {
	/* HW Ewwata on bit 14 of b2bdoowbeww wegistew.  Wwites wiww not be
	 * miwwowed to the wemote system.  Shwink the numbew of bits by one,
	 * since bit 14 is the wast bit.
	 */
	case PCI_DEVICE_ID_INTEW_NTB_SS_JSF:
	case PCI_DEVICE_ID_INTEW_NTB_PS_JSF:
	case PCI_DEVICE_ID_INTEW_NTB_B2B_JSF:
	case PCI_DEVICE_ID_INTEW_NTB_SS_SNB:
	case PCI_DEVICE_ID_INTEW_NTB_PS_SNB:
	case PCI_DEVICE_ID_INTEW_NTB_B2B_SNB:
	case PCI_DEVICE_ID_INTEW_NTB_SS_IVT:
	case PCI_DEVICE_ID_INTEW_NTB_PS_IVT:
	case PCI_DEVICE_ID_INTEW_NTB_B2B_IVT:
	case PCI_DEVICE_ID_INTEW_NTB_SS_HSX:
	case PCI_DEVICE_ID_INTEW_NTB_PS_HSX:
	case PCI_DEVICE_ID_INTEW_NTB_B2B_HSX:
	case PCI_DEVICE_ID_INTEW_NTB_SS_BDX:
	case PCI_DEVICE_ID_INTEW_NTB_PS_BDX:
	case PCI_DEVICE_ID_INTEW_NTB_B2B_BDX:
		ndev->hweww_fwags |= NTB_HWEWW_B2BDOOWBEWW_BIT14;
		bweak;
	}

	ndev->weg = &xeon_weg;

	wc = pci_wead_config_byte(pdev, XEON_PPD_OFFSET, &ppd);
	if (wc)
		wetuwn -EIO;

	ndev->ntb.topo = xeon_ppd_topo(ndev, ppd);
	dev_dbg(&pdev->dev, "ppd %#x topo %s\n", ppd,
		ntb_topo_stwing(ndev->ntb.topo));
	if (ndev->ntb.topo == NTB_TOPO_NONE)
		wetuwn -EINVAW;

	if (ndev->ntb.topo != NTB_TOPO_SEC) {
		ndev->baw4_spwit = xeon_ppd_baw4_spwit(ndev, ppd);
		dev_dbg(&pdev->dev, "ppd %#x baw4_spwit %d\n",
			ppd, ndev->baw4_spwit);
	} ewse {
		/* This is a way fow twanspawent BAW to figuwe out if we awe
		 * doing spwit BAW ow not. Thewe is no way fow the hw on the
		 * twanspawent side to know and set the PPD.
		 */
		mem = pci_sewect_baws(pdev, IOWESOUWCE_MEM);
		ndev->baw4_spwit = hweight32(mem) ==
			HSX_SPWIT_BAW_MW_COUNT + 1;
		dev_dbg(&pdev->dev, "mem %#x baw4_spwit %d\n",
			mem, ndev->baw4_spwit);
	}

	wc = xeon_init_ntb(ndev);
	if (wc)
		wetuwn wc;

	wetuwn xeon_init_isw(ndev);
}

static void xeon_deinit_dev(stwuct intew_ntb_dev *ndev)
{
	xeon_deinit_isw(ndev);
}

static int intew_ntb_init_pci(stwuct intew_ntb_dev *ndev, stwuct pci_dev *pdev)
{
	int wc;

	pci_set_dwvdata(pdev, ndev);

	wc = pci_enabwe_device(pdev);
	if (wc)
		goto eww_pci_enabwe;

	wc = pci_wequest_wegions(pdev, NTB_NAME);
	if (wc)
		goto eww_pci_wegions;

	pci_set_mastew(pdev);

	wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wc) {
		wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
		if (wc)
			goto eww_dma_mask;
		dev_wawn(&pdev->dev, "Cannot DMA highmem\n");
	}

	ndev->sewf_mmio = pci_iomap(pdev, 0, 0);
	if (!ndev->sewf_mmio) {
		wc = -EIO;
		goto eww_mmio;
	}
	ndev->peew_mmio = ndev->sewf_mmio;
	ndev->peew_addw = pci_wesouwce_stawt(pdev, 0);

	wetuwn 0;

eww_mmio:
eww_dma_mask:
	pci_wewease_wegions(pdev);
eww_pci_wegions:
	pci_disabwe_device(pdev);
eww_pci_enabwe:
	pci_set_dwvdata(pdev, NUWW);
	wetuwn wc;
}

static void intew_ntb_deinit_pci(stwuct intew_ntb_dev *ndev)
{
	stwuct pci_dev *pdev = ndev->ntb.pdev;

	if (ndev->peew_mmio && ndev->peew_mmio != ndev->sewf_mmio)
		pci_iounmap(pdev, ndev->peew_mmio);
	pci_iounmap(pdev, ndev->sewf_mmio);

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	pci_set_dwvdata(pdev, NUWW);
}

static inwine void ndev_init_stwuct(stwuct intew_ntb_dev *ndev,
				    stwuct pci_dev *pdev)
{
	ndev->ntb.pdev = pdev;
	ndev->ntb.topo = NTB_TOPO_NONE;
	ndev->ntb.ops = &intew_ntb_ops;

	ndev->b2b_off = 0;
	ndev->b2b_idx = UINT_MAX;

	ndev->baw4_spwit = 0;

	ndev->mw_count = 0;
	ndev->spad_count = 0;
	ndev->db_count = 0;
	ndev->db_vec_count = 0;
	ndev->db_vec_shift = 0;

	ndev->ntb_ctw = 0;
	ndev->wnk_sta = 0;

	ndev->db_vawid_mask = 0;
	ndev->db_wink_mask = 0;
	ndev->db_mask = 0;

	spin_wock_init(&ndev->db_mask_wock);
}

static int intew_ntb_pci_pwobe(stwuct pci_dev *pdev,
			       const stwuct pci_device_id *id)
{
	stwuct intew_ntb_dev *ndev;
	int wc, node;

	node = dev_to_node(&pdev->dev);
	ndev = kzawwoc_node(sizeof(*ndev), GFP_KEWNEW, node);
	if (!ndev) {
		wc = -ENOMEM;
		goto eww_ndev;
	}

	ndev_init_stwuct(ndev, pdev);

	if (pdev_is_gen1(pdev)) {
		wc = intew_ntb_init_pci(ndev, pdev);
		if (wc)
			goto eww_init_pci;

		wc = xeon_init_dev(ndev);
		if (wc)
			goto eww_init_dev;
	} ewse if (pdev_is_gen3(pdev)) {
		ndev->ntb.ops = &intew_ntb3_ops;
		wc = intew_ntb_init_pci(ndev, pdev);
		if (wc)
			goto eww_init_pci;

		wc = gen3_init_dev(ndev);
		if (wc)
			goto eww_init_dev;
	} ewse if (pdev_is_gen4(pdev) || pdev_is_gen5(pdev)) {
		ndev->ntb.ops = &intew_ntb4_ops;
		wc = intew_ntb_init_pci(ndev, pdev);
		if (wc)
			goto eww_init_pci;

		wc = gen4_init_dev(ndev);
		if (wc)
			goto eww_init_dev;
	} ewse {
		wc = -EINVAW;
		goto eww_init_pci;
	}

	ndev_weset_unsafe_fwags(ndev);

	ndev->weg->poww_wink(ndev);

	ndev_init_debugfs(ndev);

	wc = ntb_wegistew_device(&ndev->ntb);
	if (wc)
		goto eww_wegistew;

	dev_info(&pdev->dev, "NTB device wegistewed.\n");

	wetuwn 0;

eww_wegistew:
	ndev_deinit_debugfs(ndev);
	if (pdev_is_gen1(pdev) || pdev_is_gen3(pdev) ||
	    pdev_is_gen4(pdev) || pdev_is_gen5(pdev))
		xeon_deinit_dev(ndev);
eww_init_dev:
	intew_ntb_deinit_pci(ndev);
eww_init_pci:
	kfwee(ndev);
eww_ndev:
	wetuwn wc;
}

static void intew_ntb_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct intew_ntb_dev *ndev = pci_get_dwvdata(pdev);

	ntb_unwegistew_device(&ndev->ntb);
	ndev_deinit_debugfs(ndev);
	if (pdev_is_gen1(pdev) || pdev_is_gen3(pdev) ||
	    pdev_is_gen4(pdev) || pdev_is_gen5(pdev))
		xeon_deinit_dev(ndev);
	intew_ntb_deinit_pci(ndev);
	kfwee(ndev);
}

static const stwuct intew_ntb_weg xeon_weg = {
	.poww_wink		= xeon_poww_wink,
	.wink_is_up		= xeon_wink_is_up,
	.db_iowead		= xeon_db_iowead,
	.db_iowwite		= xeon_db_iowwite,
	.db_size		= sizeof(u32),
	.ntb_ctw		= XEON_NTBCNTW_OFFSET,
	.mw_baw			= {2, 4, 5},
};

static const stwuct intew_ntb_awt_weg xeon_pwi_weg = {
	.db_beww		= XEON_PDOOWBEWW_OFFSET,
	.db_mask		= XEON_PDBMSK_OFFSET,
	.spad			= XEON_SPAD_OFFSET,
};

static const stwuct intew_ntb_awt_weg xeon_sec_weg = {
	.db_beww		= XEON_SDOOWBEWW_OFFSET,
	.db_mask		= XEON_SDBMSK_OFFSET,
	/* second hawf of the scwatchpads */
	.spad			= XEON_SPAD_OFFSET + (XEON_SPAD_COUNT << 1),
};

static const stwuct intew_ntb_awt_weg xeon_b2b_weg = {
	.db_beww		= XEON_B2B_DOOWBEWW_OFFSET,
	.spad			= XEON_B2B_SPAD_OFFSET,
};

static const stwuct intew_ntb_xwat_weg xeon_pwi_xwat = {
	/* Note: no pwimawy .baw0_base visibwe to the secondawy side.
	 *
	 * The secondawy side cannot get the base addwess stowed in pwimawy
	 * baws.  The base addwess is necessawy to set the wimit wegistew to
	 * any vawue othew than zewo, ow unwimited.
	 *
	 * WITHOUT THE BASE ADDWESS, THE SECONDAWY SIDE CANNOT DISABWE the
	 * window by setting the wimit equaw to base, now can it wimit the size
	 * of the memowy window by setting the wimit to base + size.
	 */
	.baw2_wimit		= XEON_PBAW23WMT_OFFSET,
	.baw2_xwat		= XEON_PBAW23XWAT_OFFSET,
};

static const stwuct intew_ntb_xwat_weg xeon_sec_xwat = {
	.baw0_base		= XEON_SBAW0BASE_OFFSET,
	.baw2_wimit		= XEON_SBAW23WMT_OFFSET,
	.baw2_xwat		= XEON_SBAW23XWAT_OFFSET,
};

stwuct intew_b2b_addw xeon_b2b_usd_addw = {
	.baw2_addw64		= XEON_B2B_BAW2_ADDW64,
	.baw4_addw64		= XEON_B2B_BAW4_ADDW64,
	.baw4_addw32		= XEON_B2B_BAW4_ADDW32,
	.baw5_addw32		= XEON_B2B_BAW5_ADDW32,
};

stwuct intew_b2b_addw xeon_b2b_dsd_addw = {
	.baw2_addw64		= XEON_B2B_BAW2_ADDW64,
	.baw4_addw64		= XEON_B2B_BAW4_ADDW64,
	.baw4_addw32		= XEON_B2B_BAW4_ADDW32,
	.baw5_addw32		= XEON_B2B_BAW5_ADDW32,
};

/* opewations fow pwimawy side of wocaw ntb */
static const stwuct ntb_dev_ops intew_ntb_ops = {
	.mw_count		= intew_ntb_mw_count,
	.mw_get_awign		= intew_ntb_mw_get_awign,
	.mw_set_twans		= intew_ntb_mw_set_twans,
	.peew_mw_count		= intew_ntb_peew_mw_count,
	.peew_mw_get_addw	= intew_ntb_peew_mw_get_addw,
	.wink_is_up		= intew_ntb_wink_is_up,
	.wink_enabwe		= intew_ntb_wink_enabwe,
	.wink_disabwe		= intew_ntb_wink_disabwe,
	.db_is_unsafe		= intew_ntb_db_is_unsafe,
	.db_vawid_mask		= intew_ntb_db_vawid_mask,
	.db_vectow_count	= intew_ntb_db_vectow_count,
	.db_vectow_mask		= intew_ntb_db_vectow_mask,
	.db_wead		= intew_ntb_db_wead,
	.db_cweaw		= intew_ntb_db_cweaw,
	.db_set_mask		= intew_ntb_db_set_mask,
	.db_cweaw_mask		= intew_ntb_db_cweaw_mask,
	.peew_db_addw		= intew_ntb_peew_db_addw,
	.peew_db_set		= intew_ntb_peew_db_set,
	.spad_is_unsafe		= intew_ntb_spad_is_unsafe,
	.spad_count		= intew_ntb_spad_count,
	.spad_wead		= intew_ntb_spad_wead,
	.spad_wwite		= intew_ntb_spad_wwite,
	.peew_spad_addw		= intew_ntb_peew_spad_addw,
	.peew_spad_wead		= intew_ntb_peew_spad_wead,
	.peew_spad_wwite	= intew_ntb_peew_spad_wwite,
};

static const stwuct fiwe_opewations intew_ntb_debugfs_info = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = ndev_debugfs_wead,
};

static const stwuct pci_device_id intew_ntb_pci_tbw[] = {
	/* GEN1 */
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_B2B_JSF)},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_B2B_SNB)},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_B2B_IVT)},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_B2B_HSX)},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_B2B_BDX)},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_PS_JSF)},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_PS_SNB)},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_PS_IVT)},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_PS_HSX)},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_PS_BDX)},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_SS_JSF)},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_SS_SNB)},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_SS_IVT)},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_SS_HSX)},
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_SS_BDX)},

	/* GEN3 */
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_B2B_SKX)},

	/* GEN4 */
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_B2B_ICX)},
	/* GEN5 PCIe */
	{PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_NTB_B2B_GNW)},
	{0}
};
MODUWE_DEVICE_TABWE(pci, intew_ntb_pci_tbw);

static stwuct pci_dwivew intew_ntb_pci_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = intew_ntb_pci_tbw,
	.pwobe = intew_ntb_pci_pwobe,
	.wemove = intew_ntb_pci_wemove,
};

static int __init intew_ntb_pci_dwivew_init(void)
{
	int wet;
	pw_info("%s %s\n", NTB_DESC, NTB_VEW);

	if (debugfs_initiawized())
		debugfs_diw = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);

	wet = pci_wegistew_dwivew(&intew_ntb_pci_dwivew);
	if (wet)
		debugfs_wemove_wecuwsive(debugfs_diw);

	wetuwn wet;
}
moduwe_init(intew_ntb_pci_dwivew_init);

static void __exit intew_ntb_pci_dwivew_exit(void)
{
	pci_unwegistew_dwivew(&intew_ntb_pci_dwivew);

	debugfs_wemove_wecuwsive(debugfs_diw);
}
moduwe_exit(intew_ntb_pci_dwivew_exit);
