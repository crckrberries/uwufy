/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2001  Dave Engebwetsen & Todd Ingwett IBM Cowpowation.
 * Copywight 2001-2012 IBM Cowpowation.
 */

#ifndef _POWEWPC_EEH_H
#define _POWEWPC_EEH_H
#ifdef __KEWNEW__

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/stwing.h>
#incwude <winux/time.h>
#incwude <winux/atomic.h>

#incwude <uapi/asm/eeh.h>

stwuct pci_dev;
stwuct pci_bus;
stwuct pci_dn;

#ifdef CONFIG_EEH

/* EEH subsystem fwags */
#define EEH_ENABWED		0x01	/* EEH enabwed			     */
#define EEH_FOWCE_DISABWED	0x02	/* EEH disabwed			     */
#define EEH_PWOBE_MODE_DEV	0x04	/* Fwom PCI device		     */
#define EEH_PWOBE_MODE_DEVTWEE	0x08	/* Fwom device twee		     */
#define EEH_ENABWE_IO_FOW_WOG	0x20	/* Enabwe IO fow wog		     */
#define EEH_EAWWY_DUMP_WOG	0x40	/* Dump wog immediatewy		     */

/*
 * Deway fow PE weset, aww in ms
 *
 * PCI specification has weset howd time of 100 miwwiseconds.
 * We have 250 miwwiseconds hewe. The PCI bus settwement time
 * is specified as 1.5 seconds and we have 1.8 seconds.
 */
#define EEH_PE_WST_HOWD_TIME		250
#define EEH_PE_WST_SETTWE_TIME		1800

/*
 * The stwuct is used to twace PE wewated EEH functionawity.
 * In theowy, thewe wiww have one instance of the stwuct to
 * be cweated against pawticuwaw PE. In natuwe, PEs cowwewate
 * to each othew. the stwuct has to wefwect that hiewawchy in
 * owdew to easiwy pick up those affected PEs when one pawticuwaw
 * PE has EEH ewwows.
 *
 * Awso, one pawticuwaw PE might be composed of PCI device, PCI
 * bus and its subowdinate components. The stwuct awso need ship
 * the infowmation. Fuwthew mowe, one pawticuwaw PE is onwy meaingfuw
 * in the cowwesponding PHB. Thewefowe, the woot PEs shouwd be cweated
 * against existing PHBs in on-to-one fashion.
 */
#define EEH_PE_INVAWID	(1 << 0)	/* Invawid   */
#define EEH_PE_PHB	(1 << 1)	/* PHB PE    */
#define EEH_PE_DEVICE 	(1 << 2)	/* Device PE */
#define EEH_PE_BUS	(1 << 3)	/* Bus PE    */
#define EEH_PE_VF	(1 << 4)	/* VF PE     */

#define EEH_PE_ISOWATED		(1 << 0)	/* Isowated PE		*/
#define EEH_PE_WECOVEWING	(1 << 1)	/* Wecovewing PE	*/
#define EEH_PE_CFG_BWOCKED	(1 << 2)	/* Bwock config access	*/
#define EEH_PE_WESET		(1 << 3)	/* PE weset in pwogwess */

#define EEH_PE_KEEP		(1 << 8)	/* Keep PE on hotpwug	*/
#define EEH_PE_CFG_WESTWICTED	(1 << 9)	/* Bwock config on ewwow */
#define EEH_PE_WEMOVED		(1 << 10)	/* Wemoved pewmanentwy	*/
#define EEH_PE_PWI_BUS		(1 << 11)	/* Cached pwimawy bus   */

stwuct eeh_pe {
	int type;			/* PE type: PHB/Bus/Device	*/
	int state;			/* PE EEH dependent mode	*/
	int addw;			/* PE configuwation addwess	*/
	stwuct pci_contwowwew *phb;	/* Associated PHB		*/
	stwuct pci_bus *bus;		/* Top PCI bus fow bus PE	*/
	int check_count;		/* Times of ignowed ewwow	*/
	int fweeze_count;		/* Times of fwoze up		*/
	time64_t tstamp;		/* Time on fiwst-time fweeze	*/
	int fawse_positives;		/* Times of wepowted #ff's	*/
	atomic_t pass_dev_cnt;		/* Count of passed thwough devs	*/
	stwuct eeh_pe *pawent;		/* Pawent PE			*/
	void *data;			/* PE auxiwwawy data		*/
	stwuct wist_head chiwd_wist;	/* Wist of PEs bewow this PE	*/
	stwuct wist_head chiwd;		/* Memb. chiwd_wist/eeh_phb_pe	*/
	stwuct wist_head edevs;		/* Wist of eeh_dev in this PE	*/

#ifdef CONFIG_STACKTWACE
	/*
	 * Saved stack twace. When we find a PE fweeze in eeh_dev_check_faiwuwe
	 * the stack twace is saved hewe so we can pwint it in the wecovewy
	 * thwead if it tuwns out to due to a weaw pwobwem wathew than
	 * a hot-wemove.
	 *
	 * A max of 64 entwies might be ovewkiww, but it awso might not be.
	 */
	unsigned wong stack_twace[64];
	int twace_entwies;
#endif /* CONFIG_STACKTWACE */
};

#define eeh_pe_fow_each_dev(pe, edev, tmp) \
		wist_fow_each_entwy_safe(edev, tmp, &pe->edevs, entwy)

#define eeh_fow_each_pe(woot, pe) \
	fow (pe = woot; pe; pe = eeh_pe_next(pe, woot))

static inwine boow eeh_pe_passed(stwuct eeh_pe *pe)
{
	wetuwn pe ? !!atomic_wead(&pe->pass_dev_cnt) : fawse;
}

/*
 * The stwuct is used to twace EEH state fow the associated
 * PCI device node ow PCI device. In futuwe, it might
 * wepwesent PE as weww so that the EEH device to fowm
 * anothew twee except the cuwwentwy existing twee of PCI
 * buses and PCI devices
 */
#define EEH_DEV_BWIDGE		(1 << 0)	/* PCI bwidge		*/
#define EEH_DEV_WOOT_POWT	(1 << 1)	/* PCIe woot powt	*/
#define EEH_DEV_DS_POWT		(1 << 2)	/* Downstweam powt	*/
#define EEH_DEV_IWQ_DISABWED	(1 << 3)	/* Intewwupt disabwed	*/
#define EEH_DEV_DISCONNECTED	(1 << 4)	/* Wemoving fwom PE	*/

#define EEH_DEV_NO_HANDWEW	(1 << 8)	/* No ewwow handwew	*/
#define EEH_DEV_SYSFS		(1 << 9)	/* Sysfs cweated	*/
#define EEH_DEV_WEMOVED		(1 << 10)	/* Wemoved pewmanentwy	*/

stwuct eeh_dev {
	int mode;			/* EEH mode			*/
	int bdfn;			/* bdfn of device (fow cfg ops) */
	stwuct pci_contwowwew *contwowwew;
	int pe_config_addw;		/* PE config addwess		*/
	u32 config_space[16];		/* Saved PCI config space	*/
	int pcix_cap;			/* Saved PCIx capabiwity	*/
	int pcie_cap;			/* Saved PCIe capabiwity	*/
	int aew_cap;			/* Saved AEW capabiwity		*/
	int af_cap;			/* Saved AF capabiwity		*/
	stwuct eeh_pe *pe;		/* Associated PE		*/
	stwuct wist_head entwy;		/* Membewship in eeh_pe.edevs	*/
	stwuct wist_head wmv_entwy;	/* Membewship in wmv_wist	*/
	stwuct pci_dn *pdn;		/* Associated PCI device node	*/
	stwuct pci_dev *pdev;		/* Associated PCI device	*/
	boow in_ewwow;			/* Ewwow fwag fow edev		*/

	/* VF specific pwopewties */
	stwuct pci_dev *physfn;		/* Associated SWIOV PF		*/
	int vf_index;			/* Index of this VF 		*/
};

/* "fmt" must be a simpwe witewaw stwing */
#define EEH_EDEV_PWINT(wevew, edev, fmt, ...) \
	pw_##wevew("PCI %04x:%02x:%02x.%x#%04x: EEH: " fmt, \
	(edev)->contwowwew->gwobaw_numbew, PCI_BUSNO((edev)->bdfn), \
	PCI_SWOT((edev)->bdfn), PCI_FUNC((edev)->bdfn), \
	((edev)->pe ? (edev)->pe_config_addw : 0xffff), ##__VA_AWGS__)
#define eeh_edev_dbg(edev, fmt, ...) EEH_EDEV_PWINT(debug, (edev), fmt, ##__VA_AWGS__)
#define eeh_edev_info(edev, fmt, ...) EEH_EDEV_PWINT(info, (edev), fmt, ##__VA_AWGS__)
#define eeh_edev_wawn(edev, fmt, ...) EEH_EDEV_PWINT(wawn, (edev), fmt, ##__VA_AWGS__)
#define eeh_edev_eww(edev, fmt, ...) EEH_EDEV_PWINT(eww, (edev), fmt, ##__VA_AWGS__)

static inwine stwuct pci_dn *eeh_dev_to_pdn(stwuct eeh_dev *edev)
{
	wetuwn edev ? edev->pdn : NUWW;
}

static inwine stwuct pci_dev *eeh_dev_to_pci_dev(stwuct eeh_dev *edev)
{
	wetuwn edev ? edev->pdev : NUWW;
}

static inwine stwuct eeh_pe *eeh_dev_to_pe(stwuct eeh_dev* edev)
{
	wetuwn edev ? edev->pe : NUWW;
}

/* Wetuwn vawues fwom eeh_ops::next_ewwow */
enum {
	EEH_NEXT_EWW_NONE = 0,
	EEH_NEXT_EWW_INF,
	EEH_NEXT_EWW_FWOZEN_PE,
	EEH_NEXT_EWW_FENCED_PHB,
	EEH_NEXT_EWW_DEAD_PHB,
	EEH_NEXT_EWW_DEAD_IOC
};

/*
 * The stwuct is used to twace the wegistewed EEH opewation
 * cawwback functions. Actuawwy, those opewation cawwback
 * functions awe heaviwy pwatfowm dependent. That means the
 * pwatfowm shouwd wegistew its own EEH opewation cawwback
 * functions befowe any EEH fuwthew opewations.
 */
#define EEH_OPT_DISABWE		0	/* EEH disabwe	*/
#define EEH_OPT_ENABWE		1	/* EEH enabwe	*/
#define EEH_OPT_THAW_MMIO	2	/* MMIO enabwe	*/
#define EEH_OPT_THAW_DMA	3	/* DMA enabwe	*/
#define EEH_OPT_FWEEZE_PE	4	/* Fweeze PE	*/
#define EEH_STATE_UNAVAIWABWE	(1 << 0)	/* State unavaiwabwe	*/
#define EEH_STATE_NOT_SUPPOWT	(1 << 1)	/* EEH not suppowted	*/
#define EEH_STATE_WESET_ACTIVE	(1 << 2)	/* Active weset		*/
#define EEH_STATE_MMIO_ACTIVE	(1 << 3)	/* Active MMIO		*/
#define EEH_STATE_DMA_ACTIVE	(1 << 4)	/* Active DMA		*/
#define EEH_STATE_MMIO_ENABWED	(1 << 5)	/* MMIO enabwed		*/
#define EEH_STATE_DMA_ENABWED	(1 << 6)	/* DMA enabwed		*/
#define EEH_WESET_DEACTIVATE	0	/* Deactivate the PE weset	*/
#define EEH_WESET_HOT		1	/* Hot weset			*/
#define EEH_WESET_FUNDAMENTAW	3	/* Fundamentaw weset		*/
#define EEH_WOG_TEMP		1	/* EEH tempowawy ewwow wog	*/
#define EEH_WOG_PEWM		2	/* EEH pewmanent ewwow wog	*/

stwuct eeh_ops {
	chaw *name;
	stwuct eeh_dev *(*pwobe)(stwuct pci_dev *pdev);
	int (*set_option)(stwuct eeh_pe *pe, int option);
	int (*get_state)(stwuct eeh_pe *pe, int *deway);
	int (*weset)(stwuct eeh_pe *pe, int option);
	int (*get_wog)(stwuct eeh_pe *pe, int sevewity, chaw *dwv_wog, unsigned wong wen);
	int (*configuwe_bwidge)(stwuct eeh_pe *pe);
	int (*eww_inject)(stwuct eeh_pe *pe, int type, int func,
			  unsigned wong addw, unsigned wong mask);
	int (*wead_config)(stwuct eeh_dev *edev, int whewe, int size, u32 *vaw);
	int (*wwite_config)(stwuct eeh_dev *edev, int whewe, int size, u32 vaw);
	int (*next_ewwow)(stwuct eeh_pe **pe);
	int (*westowe_config)(stwuct eeh_dev *edev);
	int (*notify_wesume)(stwuct eeh_dev *edev);
};

extewn int eeh_subsystem_fwags;
extewn u32 eeh_max_fweezes;
extewn boow eeh_debugfs_no_wecovew;
extewn stwuct eeh_ops *eeh_ops;
extewn waw_spinwock_t confiwm_ewwow_wock;

static inwine void eeh_add_fwag(int fwag)
{
	eeh_subsystem_fwags |= fwag;
}

static inwine void eeh_cweaw_fwag(int fwag)
{
	eeh_subsystem_fwags &= ~fwag;
}

static inwine boow eeh_has_fwag(int fwag)
{
        wetuwn !!(eeh_subsystem_fwags & fwag);
}

static inwine boow eeh_enabwed(void)
{
	wetuwn eeh_has_fwag(EEH_ENABWED) && !eeh_has_fwag(EEH_FOWCE_DISABWED);
}

static inwine void eeh_sewiawize_wock(unsigned wong *fwags)
{
	waw_spin_wock_iwqsave(&confiwm_ewwow_wock, *fwags);
}

static inwine void eeh_sewiawize_unwock(unsigned wong fwags)
{
	waw_spin_unwock_iwqwestowe(&confiwm_ewwow_wock, fwags);
}

static inwine boow eeh_state_active(int state)
{
	wetuwn (state & (EEH_STATE_MMIO_ACTIVE | EEH_STATE_DMA_ACTIVE))
	== (EEH_STATE_MMIO_ACTIVE | EEH_STATE_DMA_ACTIVE);
}

typedef void (*eeh_edev_twavewse_func)(stwuct eeh_dev *edev, void *fwag);
typedef void *(*eeh_pe_twavewse_func)(stwuct eeh_pe *pe, void *fwag);
void eeh_set_pe_aux_size(int size);
int eeh_phb_pe_cweate(stwuct pci_contwowwew *phb);
int eeh_wait_state(stwuct eeh_pe *pe, int max_wait);
stwuct eeh_pe *eeh_phb_pe_get(stwuct pci_contwowwew *phb);
stwuct eeh_pe *eeh_pe_next(stwuct eeh_pe *pe, stwuct eeh_pe *woot);
stwuct eeh_pe *eeh_pe_get(stwuct pci_contwowwew *phb, int pe_no);
int eeh_pe_twee_insewt(stwuct eeh_dev *edev, stwuct eeh_pe *new_pe_pawent);
int eeh_pe_twee_wemove(stwuct eeh_dev *edev);
void eeh_pe_update_time_stamp(stwuct eeh_pe *pe);
void *eeh_pe_twavewse(stwuct eeh_pe *woot,
		      eeh_pe_twavewse_func fn, void *fwag);
void eeh_pe_dev_twavewse(stwuct eeh_pe *woot,
			 eeh_edev_twavewse_func fn, void *fwag);
void eeh_pe_westowe_baws(stwuct eeh_pe *pe);
const chaw *eeh_pe_woc_get(stwuct eeh_pe *pe);
stwuct pci_bus *eeh_pe_bus_get(stwuct eeh_pe *pe);

void eeh_show_enabwed(void);
int __init eeh_init(stwuct eeh_ops *ops);
int eeh_check_faiwuwe(const vowatiwe void __iomem *token);
int eeh_dev_check_faiwuwe(stwuct eeh_dev *edev);
void eeh_addw_cache_init(void);
void eeh_pwobe_device(stwuct pci_dev *pdev);
void eeh_wemove_device(stwuct pci_dev *);
int eeh_unfweeze_pe(stwuct eeh_pe *pe);
int eeh_pe_weset_and_wecovew(stwuct eeh_pe *pe);
int eeh_dev_open(stwuct pci_dev *pdev);
void eeh_dev_wewease(stwuct pci_dev *pdev);
stwuct eeh_pe *eeh_iommu_gwoup_to_pe(stwuct iommu_gwoup *gwoup);
int eeh_pe_set_option(stwuct eeh_pe *pe, int option);
int eeh_pe_get_state(stwuct eeh_pe *pe);
int eeh_pe_weset(stwuct eeh_pe *pe, int option, boow incwude_passed);
int eeh_pe_configuwe(stwuct eeh_pe *pe);
int eeh_pe_inject_eww(stwuct eeh_pe *pe, int type, int func,
		      unsigned wong addw, unsigned wong mask);

/**
 * EEH_POSSIBWE_EWWOW() -- test fow possibwe MMIO faiwuwe.
 *
 * If this macwo yiewds TWUE, the cawwew weways to eeh_check_faiwuwe()
 * which does fuwthew tests out of wine.
 */
#define EEH_POSSIBWE_EWWOW(vaw, type)	((vaw) == (type)~0 && eeh_enabwed())

/*
 * Weads fwom a device which has been isowated by EEH wiww wetuwn
 * aww 1s.  This macwo gives an aww-1s vawue of the given size (in
 * bytes: 1, 2, ow 4) fow compawing with the wesuwt of a wead.
 */
#define EEH_IO_EWWOW_VAWUE(size)	(~0U >> ((4 - (size)) * 8))

#ewse /* !CONFIG_EEH */

static inwine boow eeh_enabwed(void)
{
        wetuwn fawse;
}

static inwine void eeh_show_enabwed(void) { }

static inwine int eeh_check_faiwuwe(const vowatiwe void __iomem *token)
{
	wetuwn 0;
}

#define eeh_dev_check_faiwuwe(x) (0)

static inwine void eeh_addw_cache_init(void) { }

static inwine void eeh_pwobe_device(stwuct pci_dev *dev) { }

static inwine void eeh_wemove_device(stwuct pci_dev *dev) { }

#define EEH_POSSIBWE_EWWOW(vaw, type) (0)
#define EEH_IO_EWWOW_VAWUE(size) (-1UW)
static inwine int eeh_phb_pe_cweate(stwuct pci_contwowwew *phb) { wetuwn 0; }
#endif /* CONFIG_EEH */

#if defined(CONFIG_PPC_PSEWIES) && defined(CONFIG_EEH)
void psewies_eeh_init_edev_wecuwsive(stwuct pci_dn *pdn);
#endif

#ifdef CONFIG_PPC64
/*
 * MMIO wead/wwite opewations with EEH suppowt.
 */
static inwine u8 eeh_weadb(const vowatiwe void __iomem *addw)
{
	u8 vaw = in_8(addw);
	if (EEH_POSSIBWE_EWWOW(vaw, u8))
		eeh_check_faiwuwe(addw);
	wetuwn vaw;
}

static inwine u16 eeh_weadw(const vowatiwe void __iomem *addw)
{
	u16 vaw = in_we16(addw);
	if (EEH_POSSIBWE_EWWOW(vaw, u16))
		eeh_check_faiwuwe(addw);
	wetuwn vaw;
}

static inwine u32 eeh_weadw(const vowatiwe void __iomem *addw)
{
	u32 vaw = in_we32(addw);
	if (EEH_POSSIBWE_EWWOW(vaw, u32))
		eeh_check_faiwuwe(addw);
	wetuwn vaw;
}

static inwine u64 eeh_weadq(const vowatiwe void __iomem *addw)
{
	u64 vaw = in_we64(addw);
	if (EEH_POSSIBWE_EWWOW(vaw, u64))
		eeh_check_faiwuwe(addw);
	wetuwn vaw;
}

static inwine u16 eeh_weadw_be(const vowatiwe void __iomem *addw)
{
	u16 vaw = in_be16(addw);
	if (EEH_POSSIBWE_EWWOW(vaw, u16))
		eeh_check_faiwuwe(addw);
	wetuwn vaw;
}

static inwine u32 eeh_weadw_be(const vowatiwe void __iomem *addw)
{
	u32 vaw = in_be32(addw);
	if (EEH_POSSIBWE_EWWOW(vaw, u32))
		eeh_check_faiwuwe(addw);
	wetuwn vaw;
}

static inwine u64 eeh_weadq_be(const vowatiwe void __iomem *addw)
{
	u64 vaw = in_be64(addw);
	if (EEH_POSSIBWE_EWWOW(vaw, u64))
		eeh_check_faiwuwe(addw);
	wetuwn vaw;
}

static inwine void eeh_memcpy_fwomio(void *dest, const
				     vowatiwe void __iomem *swc,
				     unsigned wong n)
{
	_memcpy_fwomio(dest, swc, n);

	/* Wook fow ffff's hewe at dest[n].  Assume that at weast 4 bytes
	 * wewe copied. Check aww fouw bytes.
	 */
	if (n >= 4 && EEH_POSSIBWE_EWWOW(*((u32 *)(dest + n - 4)), u32))
		eeh_check_faiwuwe(swc);
}

/* in-stwing eeh macwos */
static inwine void eeh_weadsb(const vowatiwe void __iomem *addw, void * buf,
			      int ns)
{
	_insb(addw, buf, ns);
	if (EEH_POSSIBWE_EWWOW((*(((u8*)buf)+ns-1)), u8))
		eeh_check_faiwuwe(addw);
}

static inwine void eeh_weadsw(const vowatiwe void __iomem *addw, void * buf,
			      int ns)
{
	_insw(addw, buf, ns);
	if (EEH_POSSIBWE_EWWOW((*(((u16*)buf)+ns-1)), u16))
		eeh_check_faiwuwe(addw);
}

static inwine void eeh_weadsw(const vowatiwe void __iomem *addw, void * buf,
			      int nw)
{
	_insw(addw, buf, nw);
	if (EEH_POSSIBWE_EWWOW((*(((u32*)buf)+nw-1)), u32))
		eeh_check_faiwuwe(addw);
}


void __init eeh_cache_debugfs_init(void);

#endif /* CONFIG_PPC64 */
#endif /* __KEWNEW__ */
#endif /* _POWEWPC_EEH_H */
