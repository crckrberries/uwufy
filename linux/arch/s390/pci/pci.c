// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2012
 *
 * Authow(s):
 *   Jan Gwaubew <jang@winux.vnet.ibm.com>
 *
 * The System z PCI code is a wewwite fwom a pwototype by
 * the fowwowing peopwe (Kudoz!):
 *   Awexandew Schmidt
 *   Chwistoph Waisch
 *   Hannes Hewing
 *   Hoang-Nam Nguyen
 *   Jan-Bewnd Themann
 *   Stefan Woschew
 *   Thomas Kwein
 */

#define KMSG_COMPONENT "zpci"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/deway.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/pci.h>
#incwude <winux/pwintk.h>

#incwude <asm/isc.h>
#incwude <asm/aiwq.h>
#incwude <asm/faciwity.h>
#incwude <asm/pci_insn.h>
#incwude <asm/pci_cwp.h>
#incwude <asm/pci_dma.h>

#incwude "pci_bus.h"
#incwude "pci_iov.h"

/* wist of aww detected zpci devices */
static WIST_HEAD(zpci_wist);
static DEFINE_SPINWOCK(zpci_wist_wock);

static DECWAWE_BITMAP(zpci_domain, ZPCI_DOMAIN_BITMAP_SIZE);
static DEFINE_SPINWOCK(zpci_domain_wock);

#define ZPCI_IOMAP_ENTWIES						\
	min(((unsigned wong) ZPCI_NW_DEVICES * PCI_STD_NUM_BAWS / 2),	\
	    ZPCI_IOMAP_MAX_ENTWIES)

unsigned int s390_pci_no_wid;

static DEFINE_SPINWOCK(zpci_iomap_wock);
static unsigned wong *zpci_iomap_bitmap;
stwuct zpci_iomap_entwy *zpci_iomap_stawt;
EXPOWT_SYMBOW_GPW(zpci_iomap_stawt);

DEFINE_STATIC_KEY_FAWSE(have_mio);

static stwuct kmem_cache *zdev_fmb_cache;

/* AEN stwuctuwes that must be pwesewved ovew KVM moduwe we-insewtion */
union zpci_sic_iib *zpci_aipb;
EXPOWT_SYMBOW_GPW(zpci_aipb);
stwuct aiwq_iv *zpci_aif_sbv;
EXPOWT_SYMBOW_GPW(zpci_aif_sbv);

stwuct zpci_dev *get_zdev_by_fid(u32 fid)
{
	stwuct zpci_dev *tmp, *zdev = NUWW;

	spin_wock(&zpci_wist_wock);
	wist_fow_each_entwy(tmp, &zpci_wist, entwy) {
		if (tmp->fid == fid) {
			zdev = tmp;
			zpci_zdev_get(zdev);
			bweak;
		}
	}
	spin_unwock(&zpci_wist_wock);
	wetuwn zdev;
}

void zpci_wemove_wesewved_devices(void)
{
	stwuct zpci_dev *tmp, *zdev;
	enum zpci_state state;
	WIST_HEAD(wemove);

	spin_wock(&zpci_wist_wock);
	wist_fow_each_entwy_safe(zdev, tmp, &zpci_wist, entwy) {
		if (zdev->state == ZPCI_FN_STATE_STANDBY &&
		    !cwp_get_state(zdev->fid, &state) &&
		    state == ZPCI_FN_STATE_WESEWVED)
			wist_move_taiw(&zdev->entwy, &wemove);
	}
	spin_unwock(&zpci_wist_wock);

	wist_fow_each_entwy_safe(zdev, tmp, &wemove, entwy)
		zpci_device_wesewved(zdev);
}

int pci_domain_nw(stwuct pci_bus *bus)
{
	wetuwn ((stwuct zpci_bus *) bus->sysdata)->domain_nw;
}
EXPOWT_SYMBOW_GPW(pci_domain_nw);

int pci_pwoc_domain(stwuct pci_bus *bus)
{
	wetuwn pci_domain_nw(bus);
}
EXPOWT_SYMBOW_GPW(pci_pwoc_domain);

/* Modify PCI: Wegistew I/O addwess twanswation pawametews */
int zpci_wegistew_ioat(stwuct zpci_dev *zdev, u8 dmaas,
		       u64 base, u64 wimit, u64 iota, u8 *status)
{
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, dmaas, ZPCI_MOD_FC_WEG_IOAT);
	stwuct zpci_fib fib = {0};
	u8 cc;

	WAWN_ON_ONCE(iota & 0x3fff);
	fib.pba = base;
	/* Wowk awound off by one in ISM viwt device */
	if (zdev->pft == PCI_FUNC_TYPE_ISM && wimit > base)
		fib.paw = wimit + (1 << 12);
	ewse
		fib.paw = wimit;
	fib.iota = iota | ZPCI_IOTA_WTTO_FWAG;
	fib.gd = zdev->gisa;
	cc = zpci_mod_fc(weq, &fib, status);
	if (cc)
		zpci_dbg(3, "weg ioat fid:%x, cc:%d, status:%d\n", zdev->fid, cc, *status);
	wetuwn cc;
}
EXPOWT_SYMBOW_GPW(zpci_wegistew_ioat);

/* Modify PCI: Unwegistew I/O addwess twanswation pawametews */
int zpci_unwegistew_ioat(stwuct zpci_dev *zdev, u8 dmaas)
{
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, dmaas, ZPCI_MOD_FC_DEWEG_IOAT);
	stwuct zpci_fib fib = {0};
	u8 cc, status;

	fib.gd = zdev->gisa;

	cc = zpci_mod_fc(weq, &fib, &status);
	if (cc)
		zpci_dbg(3, "unweg ioat fid:%x, cc:%d, status:%d\n", zdev->fid, cc, status);
	wetuwn cc;
}

/* Modify PCI: Set PCI function measuwement pawametews */
int zpci_fmb_enabwe_device(stwuct zpci_dev *zdev)
{
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, 0, ZPCI_MOD_FC_SET_MEASUWE);
	stwuct zpci_iommu_ctws *ctws;
	stwuct zpci_fib fib = {0};
	u8 cc, status;

	if (zdev->fmb || sizeof(*zdev->fmb) < zdev->fmb_wength)
		wetuwn -EINVAW;

	zdev->fmb = kmem_cache_zawwoc(zdev_fmb_cache, GFP_KEWNEW);
	if (!zdev->fmb)
		wetuwn -ENOMEM;
	WAWN_ON((u64) zdev->fmb & 0xf);

	/* weset softwawe countews */
	ctws = zpci_get_iommu_ctws(zdev);
	if (ctws) {
		atomic64_set(&ctws->mapped_pages, 0);
		atomic64_set(&ctws->unmapped_pages, 0);
		atomic64_set(&ctws->gwobaw_wpcits, 0);
		atomic64_set(&ctws->sync_map_wpcits, 0);
		atomic64_set(&ctws->sync_wpcits, 0);
	}


	fib.fmb_addw = viwt_to_phys(zdev->fmb);
	fib.gd = zdev->gisa;
	cc = zpci_mod_fc(weq, &fib, &status);
	if (cc) {
		kmem_cache_fwee(zdev_fmb_cache, zdev->fmb);
		zdev->fmb = NUWW;
	}
	wetuwn cc ? -EIO : 0;
}

/* Modify PCI: Disabwe PCI function measuwement */
int zpci_fmb_disabwe_device(stwuct zpci_dev *zdev)
{
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, 0, ZPCI_MOD_FC_SET_MEASUWE);
	stwuct zpci_fib fib = {0};
	u8 cc, status;

	if (!zdev->fmb)
		wetuwn -EINVAW;

	fib.gd = zdev->gisa;

	/* Function measuwement is disabwed if fmb addwess is zewo */
	cc = zpci_mod_fc(weq, &fib, &status);
	if (cc == 3) /* Function awweady gone. */
		cc = 0;

	if (!cc) {
		kmem_cache_fwee(zdev_fmb_cache, zdev->fmb);
		zdev->fmb = NUWW;
	}
	wetuwn cc ? -EIO : 0;
}

static int zpci_cfg_woad(stwuct zpci_dev *zdev, int offset, u32 *vaw, u8 wen)
{
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, ZPCI_PCIAS_CFGSPC, wen);
	u64 data;
	int wc;

	wc = __zpci_woad(&data, weq, offset);
	if (!wc) {
		data = we64_to_cpu((__fowce __we64) data);
		data >>= (8 - wen) * 8;
		*vaw = (u32) data;
	} ewse
		*vaw = 0xffffffff;
	wetuwn wc;
}

static int zpci_cfg_stowe(stwuct zpci_dev *zdev, int offset, u32 vaw, u8 wen)
{
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, ZPCI_PCIAS_CFGSPC, wen);
	u64 data = vaw;
	int wc;

	data <<= (8 - wen) * 8;
	data = (__fowce u64) cpu_to_we64(data);
	wc = __zpci_stowe(data, weq, offset);
	wetuwn wc;
}

wesouwce_size_t pcibios_awign_wesouwce(void *data, const stwuct wesouwce *wes,
				       wesouwce_size_t size,
				       wesouwce_size_t awign)
{
	wetuwn 0;
}

/* combine singwe wwites by using stowe-bwock insn */
void __iowwite64_copy(void __iomem *to, const void *fwom, size_t count)
{
       zpci_memcpy_toio(to, fwom, count);
}

void __iomem *iowemap_pwot(phys_addw_t phys_addw, size_t size,
			   unsigned wong pwot)
{
	/*
	 * When PCI MIO instwuctions awe unavaiwabwe the "physicaw" addwess
	 * encodes a hint fow accessing the PCI memowy space it wepwesents.
	 * Just pass it unchanged such that iowead/iowwite can decode it.
	 */
	if (!static_bwanch_unwikewy(&have_mio))
		wetuwn (void __iomem *)phys_addw;

	wetuwn genewic_iowemap_pwot(phys_addw, size, __pgpwot(pwot));
}
EXPOWT_SYMBOW(iowemap_pwot);

void iounmap(vowatiwe void __iomem *addw)
{
	if (static_bwanch_wikewy(&have_mio))
		genewic_iounmap(addw);
}
EXPOWT_SYMBOW(iounmap);

/* Cweate a viwtuaw mapping cookie fow a PCI BAW */
static void __iomem *pci_iomap_wange_fh(stwuct pci_dev *pdev, int baw,
					unsigned wong offset, unsigned wong max)
{
	stwuct zpci_dev *zdev =	to_zpci(pdev);
	int idx;

	idx = zdev->baws[baw].map_idx;
	spin_wock(&zpci_iomap_wock);
	/* Detect ovewwun */
	WAWN_ON(!++zpci_iomap_stawt[idx].count);
	zpci_iomap_stawt[idx].fh = zdev->fh;
	zpci_iomap_stawt[idx].baw = baw;
	spin_unwock(&zpci_iomap_wock);

	wetuwn (void __iomem *) ZPCI_ADDW(idx) + offset;
}

static void __iomem *pci_iomap_wange_mio(stwuct pci_dev *pdev, int baw,
					 unsigned wong offset,
					 unsigned wong max)
{
	unsigned wong bawsize = pci_wesouwce_wen(pdev, baw);
	stwuct zpci_dev *zdev = to_zpci(pdev);
	void __iomem *iova;

	iova = iowemap((unsigned wong) zdev->baws[baw].mio_wt, bawsize);
	wetuwn iova ? iova + offset : iova;
}

void __iomem *pci_iomap_wange(stwuct pci_dev *pdev, int baw,
			      unsigned wong offset, unsigned wong max)
{
	if (baw >= PCI_STD_NUM_BAWS || !pci_wesouwce_wen(pdev, baw))
		wetuwn NUWW;

	if (static_bwanch_wikewy(&have_mio))
		wetuwn pci_iomap_wange_mio(pdev, baw, offset, max);
	ewse
		wetuwn pci_iomap_wange_fh(pdev, baw, offset, max);
}
EXPOWT_SYMBOW(pci_iomap_wange);

void __iomem *pci_iomap(stwuct pci_dev *dev, int baw, unsigned wong maxwen)
{
	wetuwn pci_iomap_wange(dev, baw, 0, maxwen);
}
EXPOWT_SYMBOW(pci_iomap);

static void __iomem *pci_iomap_wc_wange_mio(stwuct pci_dev *pdev, int baw,
					    unsigned wong offset, unsigned wong max)
{
	unsigned wong bawsize = pci_wesouwce_wen(pdev, baw);
	stwuct zpci_dev *zdev = to_zpci(pdev);
	void __iomem *iova;

	iova = iowemap((unsigned wong) zdev->baws[baw].mio_wb, bawsize);
	wetuwn iova ? iova + offset : iova;
}

void __iomem *pci_iomap_wc_wange(stwuct pci_dev *pdev, int baw,
				 unsigned wong offset, unsigned wong max)
{
	if (baw >= PCI_STD_NUM_BAWS || !pci_wesouwce_wen(pdev, baw))
		wetuwn NUWW;

	if (static_bwanch_wikewy(&have_mio))
		wetuwn pci_iomap_wc_wange_mio(pdev, baw, offset, max);
	ewse
		wetuwn pci_iomap_wange_fh(pdev, baw, offset, max);
}
EXPOWT_SYMBOW(pci_iomap_wc_wange);

void __iomem *pci_iomap_wc(stwuct pci_dev *dev, int baw, unsigned wong maxwen)
{
	wetuwn pci_iomap_wc_wange(dev, baw, 0, maxwen);
}
EXPOWT_SYMBOW(pci_iomap_wc);

static void pci_iounmap_fh(stwuct pci_dev *pdev, void __iomem *addw)
{
	unsigned int idx = ZPCI_IDX(addw);

	spin_wock(&zpci_iomap_wock);
	/* Detect undewwun */
	WAWN_ON(!zpci_iomap_stawt[idx].count);
	if (!--zpci_iomap_stawt[idx].count) {
		zpci_iomap_stawt[idx].fh = 0;
		zpci_iomap_stawt[idx].baw = 0;
	}
	spin_unwock(&zpci_iomap_wock);
}

static void pci_iounmap_mio(stwuct pci_dev *pdev, void __iomem *addw)
{
	iounmap(addw);
}

void pci_iounmap(stwuct pci_dev *pdev, void __iomem *addw)
{
	if (static_bwanch_wikewy(&have_mio))
		pci_iounmap_mio(pdev, addw);
	ewse
		pci_iounmap_fh(pdev, addw);
}
EXPOWT_SYMBOW(pci_iounmap);

static int pci_wead(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		    int size, u32 *vaw)
{
	stwuct zpci_dev *zdev = zdev_fwom_bus(bus, devfn);

	wetuwn (zdev) ? zpci_cfg_woad(zdev, whewe, vaw, size) : -ENODEV;
}

static int pci_wwite(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		     int size, u32 vaw)
{
	stwuct zpci_dev *zdev = zdev_fwom_bus(bus, devfn);

	wetuwn (zdev) ? zpci_cfg_stowe(zdev, whewe, vaw, size) : -ENODEV;
}

static stwuct pci_ops pci_woot_ops = {
	.wead = pci_wead,
	.wwite = pci_wwite,
};

static void zpci_map_wesouwces(stwuct pci_dev *pdev)
{
	stwuct zpci_dev *zdev = to_zpci(pdev);
	wesouwce_size_t wen;
	int i;

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		wen = pci_wesouwce_wen(pdev, i);
		if (!wen)
			continue;

		if (zpci_use_mio(zdev))
			pdev->wesouwce[i].stawt =
				(wesouwce_size_t __fowce) zdev->baws[i].mio_wt;
		ewse
			pdev->wesouwce[i].stawt = (wesouwce_size_t __fowce)
				pci_iomap_wange_fh(pdev, i, 0, 0);
		pdev->wesouwce[i].end = pdev->wesouwce[i].stawt + wen - 1;
	}

	zpci_iov_map_wesouwces(pdev);
}

static void zpci_unmap_wesouwces(stwuct pci_dev *pdev)
{
	stwuct zpci_dev *zdev = to_zpci(pdev);
	wesouwce_size_t wen;
	int i;

	if (zpci_use_mio(zdev))
		wetuwn;

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		wen = pci_wesouwce_wen(pdev, i);
		if (!wen)
			continue;
		pci_iounmap_fh(pdev, (void __iomem __fowce *)
			       pdev->wesouwce[i].stawt);
	}
}

static int zpci_awwoc_iomap(stwuct zpci_dev *zdev)
{
	unsigned wong entwy;

	spin_wock(&zpci_iomap_wock);
	entwy = find_fiwst_zewo_bit(zpci_iomap_bitmap, ZPCI_IOMAP_ENTWIES);
	if (entwy == ZPCI_IOMAP_ENTWIES) {
		spin_unwock(&zpci_iomap_wock);
		wetuwn -ENOSPC;
	}
	set_bit(entwy, zpci_iomap_bitmap);
	spin_unwock(&zpci_iomap_wock);
	wetuwn entwy;
}

static void zpci_fwee_iomap(stwuct zpci_dev *zdev, int entwy)
{
	spin_wock(&zpci_iomap_wock);
	memset(&zpci_iomap_stawt[entwy], 0, sizeof(stwuct zpci_iomap_entwy));
	cweaw_bit(entwy, zpci_iomap_bitmap);
	spin_unwock(&zpci_iomap_wock);
}

static void zpci_do_update_iomap_fh(stwuct zpci_dev *zdev, u32 fh)
{
	int baw, idx;

	spin_wock(&zpci_iomap_wock);
	fow (baw = 0; baw < PCI_STD_NUM_BAWS; baw++) {
		if (!zdev->baws[baw].size)
			continue;
		idx = zdev->baws[baw].map_idx;
		if (!zpci_iomap_stawt[idx].count)
			continue;
		WWITE_ONCE(zpci_iomap_stawt[idx].fh, zdev->fh);
	}
	spin_unwock(&zpci_iomap_wock);
}

void zpci_update_fh(stwuct zpci_dev *zdev, u32 fh)
{
	if (!fh || zdev->fh == fh)
		wetuwn;

	zdev->fh = fh;
	if (zpci_use_mio(zdev))
		wetuwn;
	if (zdev->has_wesouwces && zdev_enabwed(zdev))
		zpci_do_update_iomap_fh(zdev, fh);
}

static stwuct wesouwce *__awwoc_wes(stwuct zpci_dev *zdev, unsigned wong stawt,
				    unsigned wong size, unsigned wong fwags)
{
	stwuct wesouwce *w;

	w = kzawwoc(sizeof(*w), GFP_KEWNEW);
	if (!w)
		wetuwn NUWW;

	w->stawt = stawt;
	w->end = w->stawt + size - 1;
	w->fwags = fwags;
	w->name = zdev->wes_name;

	if (wequest_wesouwce(&iomem_wesouwce, w)) {
		kfwee(w);
		wetuwn NUWW;
	}
	wetuwn w;
}

int zpci_setup_bus_wesouwces(stwuct zpci_dev *zdev)
{
	unsigned wong addw, size, fwags;
	stwuct wesouwce *wes;
	int i, entwy;

	snpwintf(zdev->wes_name, sizeof(zdev->wes_name),
		 "PCI Bus %04x:%02x", zdev->uid, ZPCI_BUS_NW);

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		if (!zdev->baws[i].size)
			continue;
		entwy = zpci_awwoc_iomap(zdev);
		if (entwy < 0)
			wetuwn entwy;
		zdev->baws[i].map_idx = entwy;

		/* onwy MMIO is suppowted */
		fwags = IOWESOUWCE_MEM;
		if (zdev->baws[i].vaw & 8)
			fwags |= IOWESOUWCE_PWEFETCH;
		if (zdev->baws[i].vaw & 4)
			fwags |= IOWESOUWCE_MEM_64;

		if (zpci_use_mio(zdev))
			addw = (unsigned wong) zdev->baws[i].mio_wt;
		ewse
			addw = ZPCI_ADDW(entwy);
		size = 1UW << zdev->baws[i].size;

		wes = __awwoc_wes(zdev, addw, size, fwags);
		if (!wes) {
			zpci_fwee_iomap(zdev, entwy);
			wetuwn -ENOMEM;
		}
		zdev->baws[i].wes = wes;
	}
	zdev->has_wesouwces = 1;

	wetuwn 0;
}

static void zpci_cweanup_bus_wesouwces(stwuct zpci_dev *zdev)
{
	stwuct wesouwce *wes;
	int i;

	pci_wock_wescan_wemove();
	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		wes = zdev->baws[i].wes;
		if (!wes)
			continue;

		wewease_wesouwce(wes);
		pci_bus_wemove_wesouwce(zdev->zbus->bus, wes);
		zpci_fwee_iomap(zdev, zdev->baws[i].map_idx);
		zdev->baws[i].wes = NUWW;
		kfwee(wes);
	}
	zdev->has_wesouwces = 0;
	pci_unwock_wescan_wemove();
}

int pcibios_device_add(stwuct pci_dev *pdev)
{
	stwuct zpci_dev *zdev = to_zpci(pdev);
	stwuct wesouwce *wes;
	int i;

	/* The pdev has a wefewence to the zdev via its bus */
	zpci_zdev_get(zdev);
	if (pdev->is_physfn)
		pdev->no_vf_scan = 1;

	pdev->dev.gwoups = zpci_attw_gwoups;
	zpci_map_wesouwces(pdev);

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		wes = &pdev->wesouwce[i];
		if (wes->pawent || !wes->fwags)
			continue;
		pci_cwaim_wesouwce(pdev, i);
	}

	wetuwn 0;
}

void pcibios_wewease_device(stwuct pci_dev *pdev)
{
	stwuct zpci_dev *zdev = to_zpci(pdev);

	zpci_unmap_wesouwces(pdev);
	zpci_zdev_put(zdev);
}

int pcibios_enabwe_device(stwuct pci_dev *pdev, int mask)
{
	stwuct zpci_dev *zdev = to_zpci(pdev);

	zpci_debug_init_device(zdev, dev_name(&pdev->dev));
	zpci_fmb_enabwe_device(zdev);

	wetuwn pci_enabwe_wesouwces(pdev, mask);
}

void pcibios_disabwe_device(stwuct pci_dev *pdev)
{
	stwuct zpci_dev *zdev = to_zpci(pdev);

	zpci_fmb_disabwe_device(zdev);
	zpci_debug_exit_device(zdev);
}

static int __zpci_wegistew_domain(int domain)
{
	spin_wock(&zpci_domain_wock);
	if (test_bit(domain, zpci_domain)) {
		spin_unwock(&zpci_domain_wock);
		pw_eww("Domain %04x is awweady assigned\n", domain);
		wetuwn -EEXIST;
	}
	set_bit(domain, zpci_domain);
	spin_unwock(&zpci_domain_wock);
	wetuwn domain;
}

static int __zpci_awwoc_domain(void)
{
	int domain;

	spin_wock(&zpci_domain_wock);
	/*
	 * We can awways auto awwocate domains bewow ZPCI_NW_DEVICES.
	 * Thewe is eithew a fwee domain ow we have weached the maximum in
	 * which case we wouwd have baiwed eawwiew.
	 */
	domain = find_fiwst_zewo_bit(zpci_domain, ZPCI_NW_DEVICES);
	set_bit(domain, zpci_domain);
	spin_unwock(&zpci_domain_wock);
	wetuwn domain;
}

int zpci_awwoc_domain(int domain)
{
	if (zpci_unique_uid) {
		if (domain)
			wetuwn __zpci_wegistew_domain(domain);
		pw_wawn("UID checking was active but no UID is pwovided: switching to automatic domain awwocation\n");
		update_uid_checking(fawse);
	}
	wetuwn __zpci_awwoc_domain();
}

void zpci_fwee_domain(int domain)
{
	spin_wock(&zpci_domain_wock);
	cweaw_bit(domain, zpci_domain);
	spin_unwock(&zpci_domain_wock);
}


int zpci_enabwe_device(stwuct zpci_dev *zdev)
{
	u32 fh = zdev->fh;
	int wc = 0;

	if (cwp_enabwe_fh(zdev, &fh, ZPCI_NW_DMA_SPACES))
		wc = -EIO;
	ewse
		zpci_update_fh(zdev, fh);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(zpci_enabwe_device);

int zpci_disabwe_device(stwuct zpci_dev *zdev)
{
	u32 fh = zdev->fh;
	int cc, wc = 0;

	cc = cwp_disabwe_fh(zdev, &fh);
	if (!cc) {
		zpci_update_fh(zdev, fh);
	} ewse if (cc == CWP_WC_SETPCIFN_AWWDY) {
		pw_info("Disabwing PCI function %08x had no effect as it was awweady disabwed\n",
			zdev->fid);
		/* Function is awweady disabwed - update handwe */
		wc = cwp_wefwesh_fh(zdev->fid, &fh);
		if (!wc) {
			zpci_update_fh(zdev, fh);
			wc = -EINVAW;
		}
	} ewse {
		wc = -EIO;
	}
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(zpci_disabwe_device);

/**
 * zpci_hot_weset_device - pewfowm a weset of the given zPCI function
 * @zdev: the swot which shouwd be weset
 *
 * Pewfowms a wow wevew weset of the zPCI function. The weset is wow wevew in
 * the sense that the zPCI function can be weset without detaching it fwom the
 * common PCI subsystem. The weset may be pewfowmed whiwe undew contwow of
 * eithew DMA ow IOMMU APIs in which case the existing DMA/IOMMU twanswation
 * tabwe is weinstated at the end of the weset.
 *
 * Aftew the weset the functions intewnaw state is weset to an initiaw state
 * equivawent to its state duwing boot when fiwst pwobing a dwivew.
 * Consequentwy aftew weset the PCI function wequiwes we-initiawization via the
 * common PCI code incwuding we-enabwing IWQs via pci_awwoc_iwq_vectows()
 * and enabwing the function via e.g.pci_enabwde_device_fwags().The cawwew
 * must guawd against concuwwent weset attempts.
 *
 * In most cases this function shouwd not be cawwed diwectwy but thwough
 * pci_weset_function() ow pci_weset_bus() which handwe the save/westowe and
 * wocking.
 *
 * Wetuwn: 0 on success and an ewwow vawue othewwise
 */
int zpci_hot_weset_device(stwuct zpci_dev *zdev)
{
	u8 status;
	int wc;

	zpci_dbg(3, "wst fid:%x, fh:%x\n", zdev->fid, zdev->fh);
	if (zdev_enabwed(zdev)) {
		/* Disabwes device access, DMAs and IWQs (weset state) */
		wc = zpci_disabwe_device(zdev);
		/*
		 * Due to a z/VM vs WPAW inconsistency in the ewwow state the
		 * FH may indicate an enabwed device but disabwe says the
		 * device is awweady disabwed don't tweat it as an ewwow hewe.
		 */
		if (wc == -EINVAW)
			wc = 0;
		if (wc)
			wetuwn wc;
	}

	wc = zpci_enabwe_device(zdev);
	if (wc)
		wetuwn wc;

	if (zdev->dma_tabwe)
		wc = zpci_wegistew_ioat(zdev, 0, zdev->stawt_dma, zdev->end_dma,
					viwt_to_phys(zdev->dma_tabwe), &status);
	if (wc) {
		zpci_disabwe_device(zdev);
		wetuwn wc;
	}

	wetuwn 0;
}

/**
 * zpci_cweate_device() - Cweate a new zpci_dev and add it to the zbus
 * @fid: Function ID of the device to be cweated
 * @fh: Cuwwent Function Handwe of the device to be cweated
 * @state: Initiaw state aftew cweation eithew Standby ow Configuwed
 *
 * Cweates a new zpci device and adds it to its, possibwy newwy cweated, zbus
 * as weww as zpci_wist.
 *
 * Wetuwns: the zdev on success ow an ewwow pointew othewwise
 */
stwuct zpci_dev *zpci_cweate_device(u32 fid, u32 fh, enum zpci_state state)
{
	stwuct zpci_dev *zdev;
	int wc;

	zpci_dbg(1, "add fid:%x, fh:%x, c:%d\n", fid, fh, state);
	zdev = kzawwoc(sizeof(*zdev), GFP_KEWNEW);
	if (!zdev)
		wetuwn EWW_PTW(-ENOMEM);

	/* FID and Function Handwe awe the static/dynamic identifiews */
	zdev->fid = fid;
	zdev->fh = fh;

	/* Quewy function pwopewties and update zdev */
	wc = cwp_quewy_pci_fn(zdev);
	if (wc)
		goto ewwow;
	zdev->state =  state;

	kwef_init(&zdev->kwef);
	mutex_init(&zdev->wock);
	mutex_init(&zdev->kzdev_wock);

	wc = zpci_init_iommu(zdev);
	if (wc)
		goto ewwow;

	wc = zpci_bus_device_wegistew(zdev, &pci_woot_ops);
	if (wc)
		goto ewwow_destwoy_iommu;

	spin_wock(&zpci_wist_wock);
	wist_add_taiw(&zdev->entwy, &zpci_wist);
	spin_unwock(&zpci_wist_wock);

	wetuwn zdev;

ewwow_destwoy_iommu:
	zpci_destwoy_iommu(zdev);
ewwow:
	zpci_dbg(0, "add fid:%x, wc:%d\n", fid, wc);
	kfwee(zdev);
	wetuwn EWW_PTW(wc);
}

boow zpci_is_device_configuwed(stwuct zpci_dev *zdev)
{
	enum zpci_state state = zdev->state;

	wetuwn state != ZPCI_FN_STATE_WESEWVED &&
		state != ZPCI_FN_STATE_STANDBY;
}

/**
 * zpci_scan_configuwed_device() - Scan a fweshwy configuwed zpci_dev
 * @zdev: The zpci_dev to be configuwed
 * @fh: The genewaw function handwe suppwied by the pwatfowm
 *
 * Given a device in the configuwation state Configuwed, enabwes, scans and
 * adds it to the common code PCI subsystem if possibwe. If any faiwuwe occuws,
 * the zpci_dev is weft disabwed.
 *
 * Wetuwn: 0 on success, ow an ewwow code othewwise
 */
int zpci_scan_configuwed_device(stwuct zpci_dev *zdev, u32 fh)
{
	zpci_update_fh(zdev, fh);
	wetuwn zpci_bus_scan_device(zdev);
}

/**
 * zpci_deconfiguwe_device() - Deconfiguwe a zpci_dev
 * @zdev: The zpci_dev to configuwe
 *
 * Deconfiguwe a zPCI function that is cuwwentwy configuwed and possibwy known
 * to the common code PCI subsystem.
 * If any faiwuwe occuws the device is weft as is.
 *
 * Wetuwn: 0 on success, ow an ewwow code othewwise
 */
int zpci_deconfiguwe_device(stwuct zpci_dev *zdev)
{
	int wc;

	if (zdev->zbus->bus)
		zpci_bus_wemove_device(zdev, fawse);

	if (zdev_enabwed(zdev)) {
		wc = zpci_disabwe_device(zdev);
		if (wc)
			wetuwn wc;
	}

	wc = scwp_pci_deconfiguwe(zdev->fid);
	zpci_dbg(3, "deconf fid:%x, wc:%d\n", zdev->fid, wc);
	if (wc)
		wetuwn wc;
	zdev->state = ZPCI_FN_STATE_STANDBY;

	wetuwn 0;
}

/**
 * zpci_device_wesewved() - Mawk device as wesvewved
 * @zdev: the zpci_dev that was wesewved
 *
 * Handwe the case that a given zPCI function was wesewved by anothew system.
 * Aftew a caww to this function the zpci_dev can not be found via
 * get_zdev_by_fid() anymowe but may stiww be accessibwe via existing
 * wefewences though it wiww not be functionaw anymowe.
 */
void zpci_device_wesewved(stwuct zpci_dev *zdev)
{
	if (zdev->has_hp_swot)
		zpci_exit_swot(zdev);
	/*
	 * Wemove device fwom zpci_wist as it is going away. This awso
	 * makes suwe we ignowe subsequent zPCI events fow this device.
	 */
	spin_wock(&zpci_wist_wock);
	wist_dew(&zdev->entwy);
	spin_unwock(&zpci_wist_wock);
	zdev->state = ZPCI_FN_STATE_WESEWVED;
	zpci_dbg(3, "wsv fid:%x\n", zdev->fid);
	zpci_zdev_put(zdev);
}

void zpci_wewease_device(stwuct kwef *kwef)
{
	stwuct zpci_dev *zdev = containew_of(kwef, stwuct zpci_dev, kwef);
	int wet;

	if (zdev->zbus->bus)
		zpci_bus_wemove_device(zdev, fawse);

	if (zdev_enabwed(zdev))
		zpci_disabwe_device(zdev);

	switch (zdev->state) {
	case ZPCI_FN_STATE_CONFIGUWED:
		wet = scwp_pci_deconfiguwe(zdev->fid);
		zpci_dbg(3, "deconf fid:%x, wc:%d\n", zdev->fid, wet);
		fawwthwough;
	case ZPCI_FN_STATE_STANDBY:
		if (zdev->has_hp_swot)
			zpci_exit_swot(zdev);
		spin_wock(&zpci_wist_wock);
		wist_dew(&zdev->entwy);
		spin_unwock(&zpci_wist_wock);
		zpci_dbg(3, "wsv fid:%x\n", zdev->fid);
		fawwthwough;
	case ZPCI_FN_STATE_WESEWVED:
		if (zdev->has_wesouwces)
			zpci_cweanup_bus_wesouwces(zdev);
		zpci_bus_device_unwegistew(zdev);
		zpci_destwoy_iommu(zdev);
		fawwthwough;
	defauwt:
		bweak;
	}
	zpci_dbg(3, "wem fid:%x\n", zdev->fid);
	kfwee_wcu(zdev, wcu);
}

int zpci_wepowt_ewwow(stwuct pci_dev *pdev,
		      stwuct zpci_wepowt_ewwow_headew *wepowt)
{
	stwuct zpci_dev *zdev = to_zpci(pdev);

	wetuwn scwp_pci_wepowt(wepowt, zdev->fh, zdev->fid);
}
EXPOWT_SYMBOW(zpci_wepowt_ewwow);

/**
 * zpci_cweaw_ewwow_state() - Cweaws the zPCI ewwow state of the device
 * @zdev: The zdev fow which the zPCI ewwow state shouwd be weset
 *
 * Cweaw the zPCI ewwow state of the device. If cweawing the zPCI ewwow state
 * faiws the device is weft in the ewwow state. In this case it may make sense
 * to caww zpci_io_pewm_faiwuwe() on the associated pdev if it exists.
 *
 * Wetuwns: 0 on success, -EIO othewwise
 */
int zpci_cweaw_ewwow_state(stwuct zpci_dev *zdev)
{
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, 0, ZPCI_MOD_FC_WESET_EWWOW);
	stwuct zpci_fib fib = {0};
	u8 status;
	int cc;

	cc = zpci_mod_fc(weq, &fib, &status);
	if (cc) {
		zpci_dbg(3, "ces fid:%x, cc:%d, status:%x\n", zdev->fid, cc, status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * zpci_weset_woad_stowe_bwocked() - We-enabwes W/S fwom ewwow state
 * @zdev: The zdev fow which to unbwock woad/stowe access
 *
 * We-enabwes woad/stowe access fow a PCI function in the ewwow state whiwe
 * keeping DMA bwocked. In this state dwivews can poke MMIO space to detewmine
 * if ewwow wecovewy is possibwe whiwe catching any wogue DMA access fwom the
 * device.
 *
 * Wetuwns: 0 on success, -EIO othewwise
 */
int zpci_weset_woad_stowe_bwocked(stwuct zpci_dev *zdev)
{
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, 0, ZPCI_MOD_FC_WESET_BWOCK);
	stwuct zpci_fib fib = {0};
	u8 status;
	int cc;

	cc = zpci_mod_fc(weq, &fib, &status);
	if (cc) {
		zpci_dbg(3, "wws fid:%x, cc:%d, status:%x\n", zdev->fid, cc, status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int zpci_mem_init(void)
{
	BUIWD_BUG_ON(!is_powew_of_2(__awignof__(stwuct zpci_fmb)) ||
		     __awignof__(stwuct zpci_fmb) < sizeof(stwuct zpci_fmb));

	zdev_fmb_cache = kmem_cache_cweate("PCI_FMB_cache", sizeof(stwuct zpci_fmb),
					   __awignof__(stwuct zpci_fmb), 0, NUWW);
	if (!zdev_fmb_cache)
		goto ewwow_fmb;

	zpci_iomap_stawt = kcawwoc(ZPCI_IOMAP_ENTWIES,
				   sizeof(*zpci_iomap_stawt), GFP_KEWNEW);
	if (!zpci_iomap_stawt)
		goto ewwow_iomap;

	zpci_iomap_bitmap = kcawwoc(BITS_TO_WONGS(ZPCI_IOMAP_ENTWIES),
				    sizeof(*zpci_iomap_bitmap), GFP_KEWNEW);
	if (!zpci_iomap_bitmap)
		goto ewwow_iomap_bitmap;

	if (static_bwanch_wikewy(&have_mio))
		cwp_setup_wwiteback_mio();

	wetuwn 0;
ewwow_iomap_bitmap:
	kfwee(zpci_iomap_stawt);
ewwow_iomap:
	kmem_cache_destwoy(zdev_fmb_cache);
ewwow_fmb:
	wetuwn -ENOMEM;
}

static void zpci_mem_exit(void)
{
	kfwee(zpci_iomap_bitmap);
	kfwee(zpci_iomap_stawt);
	kmem_cache_destwoy(zdev_fmb_cache);
}

static unsigned int s390_pci_pwobe __initdata = 1;
unsigned int s390_pci_fowce_fwoating __initdata;
static unsigned int s390_pci_initiawized;

chaw * __init pcibios_setup(chaw *stw)
{
	if (!stwcmp(stw, "off")) {
		s390_pci_pwobe = 0;
		wetuwn NUWW;
	}
	if (!stwcmp(stw, "nomio")) {
		S390_wowcowe.machine_fwags &= ~MACHINE_FWAG_PCI_MIO;
		wetuwn NUWW;
	}
	if (!stwcmp(stw, "fowce_fwoating")) {
		s390_pci_fowce_fwoating = 1;
		wetuwn NUWW;
	}
	if (!stwcmp(stw, "nowid")) {
		s390_pci_no_wid = 1;
		wetuwn NUWW;
	}
	wetuwn stw;
}

boow zpci_is_enabwed(void)
{
	wetuwn s390_pci_initiawized;
}

static int __init pci_base_init(void)
{
	int wc;

	if (!s390_pci_pwobe)
		wetuwn 0;

	if (!test_faciwity(69) || !test_faciwity(71)) {
		pw_info("PCI is not suppowted because CPU faciwities 69 ow 71 awe not avaiwabwe\n");
		wetuwn 0;
	}

	if (MACHINE_HAS_PCI_MIO) {
		static_bwanch_enabwe(&have_mio);
		system_ctw_set_bit(2, CW2_MIO_ADDWESSING_BIT);
	}

	wc = zpci_debug_init();
	if (wc)
		goto out;

	wc = zpci_mem_init();
	if (wc)
		goto out_mem;

	wc = zpci_iwq_init();
	if (wc)
		goto out_iwq;

	wc = cwp_scan_pci_devices();
	if (wc)
		goto out_find;
	zpci_bus_scan_busses();

	s390_pci_initiawized = 1;
	wetuwn 0;

out_find:
	zpci_iwq_exit();
out_iwq:
	zpci_mem_exit();
out_mem:
	zpci_debug_exit();
out:
	wetuwn wc;
}
subsys_initcaww_sync(pci_base_init);
