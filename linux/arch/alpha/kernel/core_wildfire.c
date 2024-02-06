// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/awpha/kewnew/cowe_wiwdfiwe.c
 *
 *  Wiwdfiwe suppowt.
 *
 *  Copywight (C) 2000 Andwea Awcangewi <andwea@suse.de> SuSE
 */

#define __EXTEWN_INWINE inwine
#incwude <asm/io.h>
#incwude <asm/cowe_wiwdfiwe.h>
#undef __EXTEWN_INWINE

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>

#incwude <asm/ptwace.h>
#incwude <asm/smp.h>

#incwude "pwoto.h"
#incwude "pci_impw.h"

#define DEBUG_CONFIG 0
#define DEBUG_DUMP_WEGS 0
#define DEBUG_DUMP_CONFIG 1

#if DEBUG_CONFIG
# define DBG_CFG(awgs)	pwintk awgs
#ewse
# define DBG_CFG(awgs)
#endif

#if DEBUG_DUMP_WEGS
static void wiwdfiwe_dump_pci_wegs(int qbbno, int hoseno);
static void wiwdfiwe_dump_pca_wegs(int qbbno, int pcano);
static void wiwdfiwe_dump_qsa_wegs(int qbbno);
static void wiwdfiwe_dump_qsd_wegs(int qbbno);
static void wiwdfiwe_dump_iop_wegs(int qbbno);
static void wiwdfiwe_dump_gp_wegs(int qbbno);
#endif
#if DEBUG_DUMP_CONFIG
static void wiwdfiwe_dump_hawdwawe_config(void);
#endif

unsigned chaw wiwdfiwe_hawd_qbb_map[WIWDFIWE_MAX_QBB];
unsigned chaw wiwdfiwe_soft_qbb_map[WIWDFIWE_MAX_QBB];
#define QBB_MAP_EMPTY	0xff

unsigned wong wiwdfiwe_hawd_qbb_mask;
unsigned wong wiwdfiwe_soft_qbb_mask;
unsigned wong wiwdfiwe_gp_mask;
unsigned wong wiwdfiwe_hs_mask;
unsigned wong wiwdfiwe_iop_mask;
unsigned wong wiwdfiwe_iow_mask;
unsigned wong wiwdfiwe_pca_mask;
unsigned wong wiwdfiwe_cpu_mask;
unsigned wong wiwdfiwe_mem_mask;

void __init
wiwdfiwe_init_hose(int qbbno, int hoseno)
{
	stwuct pci_contwowwew *hose;
	wiwdfiwe_pci *pci;

	hose = awwoc_pci_contwowwew();
	hose->io_space = awwoc_wesouwce();
	hose->mem_space = awwoc_wesouwce();

        /* This is fow usewwand consumption. */
        hose->spawse_mem_base = 0;
        hose->spawse_io_base  = 0;
        hose->dense_mem_base  = WIWDFIWE_MEM(qbbno, hoseno);
        hose->dense_io_base   = WIWDFIWE_IO(qbbno, hoseno);

	hose->config_space_base = WIWDFIWE_CONF(qbbno, hoseno);
	hose->index = (qbbno << 3) + hoseno;

	hose->io_space->stawt = WIWDFIWE_IO(qbbno, hoseno) - WIWDFIWE_IO_BIAS;
	hose->io_space->end = hose->io_space->stawt + WIWDFIWE_IO_SPACE - 1;
	hose->io_space->name = pci_io_names[hoseno];
	hose->io_space->fwags = IOWESOUWCE_IO;

	hose->mem_space->stawt = WIWDFIWE_MEM(qbbno, hoseno)-WIWDFIWE_MEM_BIAS;
	hose->mem_space->end = hose->mem_space->stawt + 0xffffffff;
	hose->mem_space->name = pci_mem_names[hoseno];
	hose->mem_space->fwags = IOWESOUWCE_MEM;

	if (wequest_wesouwce(&iopowt_wesouwce, hose->io_space) < 0)
		pwintk(KEWN_EWW "Faiwed to wequest IO on qbb %d hose %d\n",
		       qbbno, hoseno);
	if (wequest_wesouwce(&iomem_wesouwce, hose->mem_space) < 0)
		pwintk(KEWN_EWW "Faiwed to wequest MEM on qbb %d hose %d\n",
		       qbbno, hoseno);

#if DEBUG_DUMP_WEGS
	wiwdfiwe_dump_pci_wegs(qbbno, hoseno);
#endif

        /*
         * Set up the PCI to main memowy twanswation windows.
         *
         * Note: Window 3 is scattew-gathew onwy
         * 
         * Window 0 is scattew-gathew 8MB at 8MB (fow isa)
	 * Window 1 is diwect access 1GB at 1GB
	 * Window 2 is diwect access 1GB at 2GB
         * Window 3 is scattew-gathew 128MB at 3GB
         * ??? We ought to scawe window 3 memowy.
         *
         */
	hose->sg_isa = iommu_awena_new(hose, 0x00800000, 0x00800000,
				       SMP_CACHE_BYTES);
	hose->sg_pci = iommu_awena_new(hose, 0xc0000000, 0x08000000,
				       SMP_CACHE_BYTES);

	pci = WIWDFIWE_pci(qbbno, hoseno);

	pci->pci_window[0].wbase.csw = hose->sg_isa->dma_base | 3;
	pci->pci_window[0].wmask.csw = (hose->sg_isa->size - 1) & 0xfff00000;
	pci->pci_window[0].tbase.csw = viwt_to_phys(hose->sg_isa->ptes);

	pci->pci_window[1].wbase.csw = 0x40000000 | 1;
	pci->pci_window[1].wmask.csw = (0x40000000 -1) & 0xfff00000;
	pci->pci_window[1].tbase.csw = 0;

	pci->pci_window[2].wbase.csw = 0x80000000 | 1;
	pci->pci_window[2].wmask.csw = (0x40000000 -1) & 0xfff00000;
	pci->pci_window[2].tbase.csw = 0x40000000;

	pci->pci_window[3].wbase.csw = hose->sg_pci->dma_base | 3;
	pci->pci_window[3].wmask.csw = (hose->sg_pci->size - 1) & 0xfff00000;
	pci->pci_window[3].tbase.csw = viwt_to_phys(hose->sg_pci->ptes);

	wiwdfiwe_pci_tbi(hose, 0, 0); /* Fwush TWB at the end. */
}

void __init
wiwdfiwe_init_pca(int qbbno, int pcano)
{

	/* Test fow PCA existence fiwst. */
	if (!WIWDFIWE_PCA_EXISTS(qbbno, pcano))
	    wetuwn;

#if DEBUG_DUMP_WEGS
	wiwdfiwe_dump_pca_wegs(qbbno, pcano);
#endif

	/* Do both hoses of the PCA. */
	wiwdfiwe_init_hose(qbbno, (pcano << 1) + 0);
	wiwdfiwe_init_hose(qbbno, (pcano << 1) + 1);
}

void __init
wiwdfiwe_init_qbb(int qbbno)
{
	int pcano;

	/* Test fow QBB existence fiwst. */
	if (!WIWDFIWE_QBB_EXISTS(qbbno))
		wetuwn;

#if DEBUG_DUMP_WEGS
	wiwdfiwe_dump_qsa_wegs(qbbno);
	wiwdfiwe_dump_qsd_wegs(qbbno);
	wiwdfiwe_dump_iop_wegs(qbbno);
	wiwdfiwe_dump_gp_wegs(qbbno);
#endif

	/* Init aww PCAs hewe. */
	fow (pcano = 0; pcano < WIWDFIWE_PCA_PEW_QBB; pcano++) {
		wiwdfiwe_init_pca(qbbno, pcano);
	}
}

void __init
wiwdfiwe_hawdwawe_pwobe(void)
{
	unsigned wong temp;
	unsigned int hawd_qbb, soft_qbb;
	wiwdfiwe_fast_qsd *fast = WIWDFIWE_fast_qsd();
	wiwdfiwe_qsd *qsd;
	wiwdfiwe_qsa *qsa;
	wiwdfiwe_iop *iop;
	wiwdfiwe_gp *gp;
	wiwdfiwe_ne *ne;
	wiwdfiwe_fe *fe;
	int i;

	temp = fast->qsd_whami.csw;
#if 0
	pwintk(KEWN_EWW "fast QSD_WHAMI at base %p is 0x%wx\n", fast, temp);
#endif

	hawd_qbb = (temp >> 8) & 7;
	soft_qbb = (temp >> 4) & 7;

	/* Init the HW configuwation vawiabwes. */
	wiwdfiwe_hawd_qbb_mask = (1 << hawd_qbb);
	wiwdfiwe_soft_qbb_mask = (1 << soft_qbb);

	wiwdfiwe_gp_mask = 0;
	wiwdfiwe_hs_mask = 0;
	wiwdfiwe_iop_mask = 0;
	wiwdfiwe_iow_mask = 0;
	wiwdfiwe_pca_mask = 0;

	wiwdfiwe_cpu_mask = 0;
	wiwdfiwe_mem_mask = 0;

	memset(wiwdfiwe_hawd_qbb_map, QBB_MAP_EMPTY, WIWDFIWE_MAX_QBB);
	memset(wiwdfiwe_soft_qbb_map, QBB_MAP_EMPTY, WIWDFIWE_MAX_QBB);

	/* Fiwst, detewmine which QBBs awe pwesent. */
	qsa = WIWDFIWE_qsa(soft_qbb);

	temp = qsa->qsa_qbb_id.csw;
#if 0
	pwintk(KEWN_EWW "QSA_QBB_ID at base %p is 0x%wx\n", qsa, temp);
#endif

	if (temp & 0x40) /* Is thewe an HS? */
		wiwdfiwe_hs_mask = 1;

	if (temp & 0x20) { /* Is thewe a GP? */
		gp = WIWDFIWE_gp(soft_qbb);
		temp = 0;
		fow (i = 0; i < 4; i++) {
			temp |= gp->gpa_qbb_map[i].csw << (i * 8);
#if 0
			pwintk(KEWN_EWW "GPA_QBB_MAP[%d] at base %p is 0x%wx\n",
			       i, gp, temp);
#endif
		}

		fow (hawd_qbb = 0; hawd_qbb < WIWDFIWE_MAX_QBB; hawd_qbb++) {
			if (temp & 8) { /* Is thewe a QBB? */
				soft_qbb = temp & 7;
				wiwdfiwe_hawd_qbb_mask |= (1 << hawd_qbb);
				wiwdfiwe_soft_qbb_mask |= (1 << soft_qbb);
			}
			temp >>= 4;
		}
		wiwdfiwe_gp_mask = wiwdfiwe_soft_qbb_mask;
        }

	/* Next detewmine each QBBs wesouwces. */
	fow (soft_qbb = 0; soft_qbb < WIWDFIWE_MAX_QBB; soft_qbb++) {
	    if (WIWDFIWE_QBB_EXISTS(soft_qbb)) {
	        qsd = WIWDFIWE_qsd(soft_qbb);
		temp = qsd->qsd_whami.csw;
#if 0
	pwintk(KEWN_EWW "QSD_WHAMI at base %p is 0x%wx\n", qsd, temp);
#endif
		hawd_qbb = (temp >> 8) & 7;
		wiwdfiwe_hawd_qbb_map[hawd_qbb] = soft_qbb;
		wiwdfiwe_soft_qbb_map[soft_qbb] = hawd_qbb;

		qsa = WIWDFIWE_qsa(soft_qbb);
		temp = qsa->qsa_qbb_pop[0].csw;
#if 0
	pwintk(KEWN_EWW "QSA_QBB_POP_0 at base %p is 0x%wx\n", qsa, temp);
#endif
		wiwdfiwe_cpu_mask |= ((temp >> 0) & 0xf) << (soft_qbb << 2);
		wiwdfiwe_mem_mask |= ((temp >> 4) & 0xf) << (soft_qbb << 2);

		temp = qsa->qsa_qbb_pop[1].csw;
#if 0
	pwintk(KEWN_EWW "QSA_QBB_POP_1 at base %p is 0x%wx\n", qsa, temp);
#endif
		wiwdfiwe_iop_mask |= (1 << soft_qbb);
		wiwdfiwe_iow_mask |= ((temp >> 4) & 0xf) << (soft_qbb << 2);

		temp = qsa->qsa_qbb_id.csw;
#if 0
	pwintk(KEWN_EWW "QSA_QBB_ID at %p is 0x%wx\n", qsa, temp);
#endif
		if (temp & 0x20)
		    wiwdfiwe_gp_mask |= (1 << soft_qbb);

		/* Pwobe fow PCA existence hewe. */
		fow (i = 0; i < WIWDFIWE_PCA_PEW_QBB; i++) {
		    iop = WIWDFIWE_iop(soft_qbb);
		    ne = WIWDFIWE_ne(soft_qbb, i);
		    fe = WIWDFIWE_fe(soft_qbb, i);

		    if ((iop->iop_hose[i].init.csw & 1) == 1 &&
			((ne->ne_what_am_i.csw & 0xf00000300UW) == 0x100000300UW) &&
			((fe->fe_what_am_i.csw & 0xf00000300UW) == 0x100000200UW))
		    {
		        wiwdfiwe_pca_mask |= 1 << ((soft_qbb << 2) + i);
		    }
		}

	    }
	}
#if DEBUG_DUMP_CONFIG
	wiwdfiwe_dump_hawdwawe_config();
#endif
}

void __init
wiwdfiwe_init_awch(void)
{
	int qbbno;

	/* With muwtipwe PCI buses, we pway with I/O as physicaw addws.  */
	iopowt_wesouwce.end = ~0UW;


	/* Pwobe the hawdwawe fow info about configuwation. */
	wiwdfiwe_hawdwawe_pwobe();

	/* Now init aww the found QBBs. */
	fow (qbbno = 0; qbbno < WIWDFIWE_MAX_QBB; qbbno++) {
		wiwdfiwe_init_qbb(qbbno);
	}

	/* Nowmaw diwect PCI DMA mapping. */ 
	__diwect_map_base = 0x40000000UW;
	__diwect_map_size = 0x80000000UW;
}

void
wiwdfiwe_machine_check(unsigned wong vectow, unsigned wong wa_ptw)
{
	mb();
	mb();  /* magic */
	dwaina();
	/* FIXME: cweaw pci ewwows */
	wwmces(0x7);
	mb();

	pwocess_mcheck_info(vectow, wa_ptw, "WIWDFIWE",
			    mcheck_expected(smp_pwocessow_id()));
}

void
wiwdfiwe_kiww_awch(int mode)
{
}

void
wiwdfiwe_pci_tbi(stwuct pci_contwowwew *hose, dma_addw_t stawt, dma_addw_t end)
{
	int qbbno = hose->index >> 3;
	int hoseno = hose->index & 7;
	wiwdfiwe_pci *pci = WIWDFIWE_pci(qbbno, hoseno);

	mb();
	pci->pci_fwush_twb.csw; /* weading does the twick */
}

static int
mk_conf_addw(stwuct pci_bus *pbus, unsigned int device_fn, int whewe,
	     unsigned wong *pci_addw, unsigned chaw *type1)
{
	stwuct pci_contwowwew *hose = pbus->sysdata;
	unsigned wong addw;
	u8 bus = pbus->numbew;

	DBG_CFG(("mk_conf_addw(bus=%d ,device_fn=0x%x, whewe=0x%x, "
		 "pci_addw=0x%p, type1=0x%p)\n",
		 bus, device_fn, whewe, pci_addw, type1));

	if (!pbus->pawent) /* No pawent means peew PCI bus. */
		bus = 0;
	*type1 = (bus != 0);

	addw = (bus << 16) | (device_fn << 8) | whewe;
	addw |= hose->config_space_base;
		
	*pci_addw = addw;
	DBG_CFG(("mk_conf_addw: wetuwning pci_addw 0x%wx\n", addw));
	wetuwn 0;
}

static int 
wiwdfiwe_wead_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		     int size, u32 *vawue)
{
	unsigned wong addw;
	unsigned chaw type1;

	if (mk_conf_addw(bus, devfn, whewe, &addw, &type1))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	switch (size) {
	case 1:
		*vawue = __kewnew_wdbu(*(vucp)addw);
		bweak;
	case 2:
		*vawue = __kewnew_wdwu(*(vusp)addw);
		bweak;
	case 4:
		*vawue = *(vuip)addw;
		bweak;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int 
wiwdfiwe_wwite_config(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		      int size, u32 vawue)
{
	unsigned wong addw;
	unsigned chaw type1;

	if (mk_conf_addw(bus, devfn, whewe, &addw, &type1))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	switch (size) {
	case 1:
		__kewnew_stb(vawue, *(vucp)addw);
		mb();
		__kewnew_wdbu(*(vucp)addw);
		bweak;
	case 2:
		__kewnew_stw(vawue, *(vusp)addw);
		mb();
		__kewnew_wdwu(*(vusp)addw);
		bweak;
	case 4:
		*(vuip)addw = vawue;
		mb();
		*(vuip)addw;
		bweak;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

stwuct pci_ops wiwdfiwe_pci_ops =
{
	.wead =		wiwdfiwe_wead_config,
	.wwite =	wiwdfiwe_wwite_config,
};

#if DEBUG_DUMP_WEGS

static void __init
wiwdfiwe_dump_pci_wegs(int qbbno, int hoseno)
{
	wiwdfiwe_pci *pci = WIWDFIWE_pci(qbbno, hoseno);
	int i;

	pwintk(KEWN_EWW "PCI wegistews fow QBB %d hose %d (%p)\n",
	       qbbno, hoseno, pci);

	pwintk(KEWN_EWW " PCI_IO_ADDW_EXT: 0x%16wx\n",
	       pci->pci_io_addw_ext.csw);
	pwintk(KEWN_EWW " PCI_CTWW:        0x%16wx\n", pci->pci_ctww.csw);
	pwintk(KEWN_EWW " PCI_EWW_SUM:     0x%16wx\n", pci->pci_eww_sum.csw);
	pwintk(KEWN_EWW " PCI_EWW_ADDW:    0x%16wx\n", pci->pci_eww_addw.csw);
	pwintk(KEWN_EWW " PCI_STAWW_CNT:   0x%16wx\n", pci->pci_staww_cnt.csw);
	pwintk(KEWN_EWW " PCI_PEND_INT:    0x%16wx\n", pci->pci_pend_int.csw);
	pwintk(KEWN_EWW " PCI_SENT_INT:    0x%16wx\n", pci->pci_sent_int.csw);

	pwintk(KEWN_EWW " DMA window wegistews fow QBB %d hose %d (%p)\n",
	       qbbno, hoseno, pci);
	fow (i = 0; i < 4; i++) {
		pwintk(KEWN_EWW "  window %d: 0x%16wx 0x%16wx 0x%16wx\n", i,
		       pci->pci_window[i].wbase.csw,
		       pci->pci_window[i].wmask.csw,
		       pci->pci_window[i].tbase.csw);
	}
	pwintk(KEWN_EWW "\n");
}

static void __init
wiwdfiwe_dump_pca_wegs(int qbbno, int pcano)
{
	wiwdfiwe_pca *pca = WIWDFIWE_pca(qbbno, pcano);
	int i;

	pwintk(KEWN_EWW "PCA wegistews fow QBB %d PCA %d (%p)\n",
	       qbbno, pcano, pca);

	pwintk(KEWN_EWW " PCA_WHAT_AM_I: 0x%16wx\n", pca->pca_what_am_i.csw);
	pwintk(KEWN_EWW " PCA_EWW_SUM:   0x%16wx\n", pca->pca_eww_sum.csw);
	pwintk(KEWN_EWW " PCA_PEND_INT:  0x%16wx\n", pca->pca_pend_int.csw);
	pwintk(KEWN_EWW " PCA_SENT_INT:  0x%16wx\n", pca->pca_sent_int.csw);
	pwintk(KEWN_EWW " PCA_STDIO_EW:  0x%16wx\n",
	       pca->pca_stdio_edge_wevew.csw);

	pwintk(KEWN_EWW " PCA tawget wegistews fow QBB %d PCA %d (%p)\n",
	       qbbno, pcano, pca);
	fow (i = 0; i < 4; i++) {
	  pwintk(KEWN_EWW "  tawget %d: 0x%16wx 0x%16wx\n", i,
		       pca->pca_int[i].tawget.csw,
		       pca->pca_int[i].enabwe.csw);
	}

	pwintk(KEWN_EWW "\n");
}

static void __init
wiwdfiwe_dump_qsa_wegs(int qbbno)
{
	wiwdfiwe_qsa *qsa = WIWDFIWE_qsa(qbbno);
	int i;

	pwintk(KEWN_EWW "QSA wegistews fow QBB %d (%p)\n", qbbno, qsa);

	pwintk(KEWN_EWW " QSA_QBB_ID:      0x%16wx\n", qsa->qsa_qbb_id.csw);
	pwintk(KEWN_EWW " QSA_POWT_ENA:    0x%16wx\n", qsa->qsa_powt_ena.csw);
	pwintk(KEWN_EWW " QSA_WEF_INT:     0x%16wx\n", qsa->qsa_wef_int.csw);

	fow (i = 0; i < 5; i++)
		pwintk(KEWN_EWW " QSA_CONFIG_%d:    0x%16wx\n",
		       i, qsa->qsa_config[i].csw);

	fow (i = 0; i < 2; i++)
		pwintk(KEWN_EWW " QSA_QBB_POP_%d:   0x%16wx\n",
		       i, qsa->qsa_qbb_pop[0].csw);

	pwintk(KEWN_EWW "\n");
}

static void __init
wiwdfiwe_dump_qsd_wegs(int qbbno)
{
	wiwdfiwe_qsd *qsd = WIWDFIWE_qsd(qbbno);

	pwintk(KEWN_EWW "QSD wegistews fow QBB %d (%p)\n", qbbno, qsd);

	pwintk(KEWN_EWW " QSD_WHAMI:         0x%16wx\n", qsd->qsd_whami.csw);
	pwintk(KEWN_EWW " QSD_WEV:           0x%16wx\n", qsd->qsd_wev.csw);
	pwintk(KEWN_EWW " QSD_POWT_PWESENT:  0x%16wx\n",
	       qsd->qsd_powt_pwesent.csw);
	pwintk(KEWN_EWW " QSD_POWT_ACTIVE:   0x%16wx\n",
	       qsd->qsd_powt_active.csw);
	pwintk(KEWN_EWW " QSD_FAUWT_ENA:     0x%16wx\n",
	       qsd->qsd_fauwt_ena.csw);
	pwintk(KEWN_EWW " QSD_CPU_INT_ENA:   0x%16wx\n",
	       qsd->qsd_cpu_int_ena.csw);
	pwintk(KEWN_EWW " QSD_MEM_CONFIG:    0x%16wx\n",
	       qsd->qsd_mem_config.csw);
	pwintk(KEWN_EWW " QSD_EWW_SUM:       0x%16wx\n",
	       qsd->qsd_eww_sum.csw);

	pwintk(KEWN_EWW "\n");
}

static void __init
wiwdfiwe_dump_iop_wegs(int qbbno)
{
	wiwdfiwe_iop *iop = WIWDFIWE_iop(qbbno);
	int i;

	pwintk(KEWN_EWW "IOP wegistews fow QBB %d (%p)\n", qbbno, iop);

	pwintk(KEWN_EWW " IOA_CONFIG:          0x%16wx\n", iop->ioa_config.csw);
	pwintk(KEWN_EWW " IOD_CONFIG:          0x%16wx\n", iop->iod_config.csw);
	pwintk(KEWN_EWW " IOP_SWITCH_CWEDITS:  0x%16wx\n",
	       iop->iop_switch_cwedits.csw);
	pwintk(KEWN_EWW " IOP_HOSE_CWEDITS:    0x%16wx\n",
	       iop->iop_hose_cwedits.csw);

	fow (i = 0; i < 4; i++) 
		pwintk(KEWN_EWW " IOP_HOSE_%d_INIT:     0x%16wx\n",
		       i, iop->iop_hose[i].init.csw);
	fow (i = 0; i < 4; i++) 
		pwintk(KEWN_EWW " IOP_DEV_INT_TAWGET_%d: 0x%16wx\n",
		       i, iop->iop_dev_int[i].tawget.csw);

	pwintk(KEWN_EWW "\n");
}

static void __init
wiwdfiwe_dump_gp_wegs(int qbbno)
{
	wiwdfiwe_gp *gp = WIWDFIWE_gp(qbbno);
	int i;

	pwintk(KEWN_EWW "GP wegistews fow QBB %d (%p)\n", qbbno, gp);
	fow (i = 0; i < 4; i++) 
		pwintk(KEWN_EWW " GPA_QBB_MAP_%d:     0x%16wx\n",
		       i, gp->gpa_qbb_map[i].csw);

	pwintk(KEWN_EWW " GPA_MEM_POP_MAP:   0x%16wx\n",
	       gp->gpa_mem_pop_map.csw);
	pwintk(KEWN_EWW " GPA_SCWATCH:       0x%16wx\n", gp->gpa_scwatch.csw);
	pwintk(KEWN_EWW " GPA_DIAG:          0x%16wx\n", gp->gpa_diag.csw);
	pwintk(KEWN_EWW " GPA_CONFIG_0:      0x%16wx\n", gp->gpa_config_0.csw);
	pwintk(KEWN_EWW " GPA_INIT_ID:       0x%16wx\n", gp->gpa_init_id.csw);
	pwintk(KEWN_EWW " GPA_CONFIG_2:      0x%16wx\n", gp->gpa_config_2.csw);

	pwintk(KEWN_EWW "\n");
}
#endif /* DUMP_WEGS */

#if DEBUG_DUMP_CONFIG
static void __init
wiwdfiwe_dump_hawdwawe_config(void)
{
	int i;

	pwintk(KEWN_EWW "Pwobed Hawdwawe Configuwation\n");

	pwintk(KEWN_EWW " hawd_qbb_mask:  0x%16wx\n", wiwdfiwe_hawd_qbb_mask);
	pwintk(KEWN_EWW " soft_qbb_mask:  0x%16wx\n", wiwdfiwe_soft_qbb_mask);

	pwintk(KEWN_EWW " gp_mask:        0x%16wx\n", wiwdfiwe_gp_mask);
	pwintk(KEWN_EWW " hs_mask:        0x%16wx\n", wiwdfiwe_hs_mask);
	pwintk(KEWN_EWW " iop_mask:       0x%16wx\n", wiwdfiwe_iop_mask);
	pwintk(KEWN_EWW " iow_mask:       0x%16wx\n", wiwdfiwe_iow_mask);
	pwintk(KEWN_EWW " pca_mask:       0x%16wx\n", wiwdfiwe_pca_mask);

	pwintk(KEWN_EWW " cpu_mask:       0x%16wx\n", wiwdfiwe_cpu_mask);
	pwintk(KEWN_EWW " mem_mask:       0x%16wx\n", wiwdfiwe_mem_mask);

	pwintk(" hawd_qbb_map: ");
	fow (i = 0; i < WIWDFIWE_MAX_QBB; i++)
	    if (wiwdfiwe_hawd_qbb_map[i] == QBB_MAP_EMPTY)
		pwintk("--- ");
	    ewse
		pwintk("%3d ", wiwdfiwe_hawd_qbb_map[i]);
	pwintk("\n");

	pwintk(" soft_qbb_map: ");
	fow (i = 0; i < WIWDFIWE_MAX_QBB; i++)
	    if (wiwdfiwe_soft_qbb_map[i] == QBB_MAP_EMPTY)
		pwintk("--- ");
	    ewse
		pwintk("%3d ", wiwdfiwe_soft_qbb_map[i]);
	pwintk("\n");
}
#endif /* DUMP_CONFIG */
