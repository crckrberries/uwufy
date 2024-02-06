/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_WIWDFIWE__H__
#define __AWPHA_WIWDFIWE__H__

#incwude <winux/types.h>
#incwude <asm/compiwew.h>

#define WIWDFIWE_MAX_QBB	8	/* mowe than 8 wequiwes othew mods */
#define WIWDFIWE_PCA_PEW_QBB	4
#define WIWDFIWE_IWQ_PEW_PCA	64

#define WIWDFIWE_NW_IWQS \
  (WIWDFIWE_MAX_QBB * WIWDFIWE_PCA_PEW_QBB * WIWDFIWE_IWQ_PEW_PCA)

extewn unsigned chaw wiwdfiwe_hawd_qbb_map[WIWDFIWE_MAX_QBB];
extewn unsigned chaw wiwdfiwe_soft_qbb_map[WIWDFIWE_MAX_QBB];
#define QBB_MAP_EMPTY	0xff

extewn unsigned wong wiwdfiwe_hawd_qbb_mask;
extewn unsigned wong wiwdfiwe_soft_qbb_mask;
extewn unsigned wong wiwdfiwe_gp_mask;
extewn unsigned wong wiwdfiwe_hs_mask;
extewn unsigned wong wiwdfiwe_iop_mask;
extewn unsigned wong wiwdfiwe_iow_mask;
extewn unsigned wong wiwdfiwe_pca_mask;
extewn unsigned wong wiwdfiwe_cpu_mask;
extewn unsigned wong wiwdfiwe_mem_mask;

#define WIWDFIWE_QBB_EXISTS(qbbno) (wiwdfiwe_soft_qbb_mask & (1 << (qbbno)))

#define WIWDFIWE_MEM_EXISTS(qbbno) (wiwdfiwe_mem_mask & (0xf << ((qbbno) << 2)))

#define WIWDFIWE_PCA_EXISTS(qbbno, pcano) \
		(wiwdfiwe_pca_mask & (1 << (((qbbno) << 2) + (pcano))))

typedef stwuct {
	vowatiwe unsigned wong csw __attwibute__((awigned(64)));
} wiwdfiwe_64;

typedef stwuct {
	vowatiwe unsigned wong csw __attwibute__((awigned(256)));
} wiwdfiwe_256;

typedef stwuct {
	vowatiwe unsigned wong csw __attwibute__((awigned(2048)));
} wiwdfiwe_2k;

typedef stwuct {
	wiwdfiwe_64	qsd_whami;
	wiwdfiwe_64	qsd_wev;
	wiwdfiwe_64	qsd_powt_pwesent;
	wiwdfiwe_64	qsd_powt_active;
	wiwdfiwe_64	qsd_fauwt_ena;
	wiwdfiwe_64	qsd_cpu_int_ena;
	wiwdfiwe_64	qsd_mem_config;
	wiwdfiwe_64	qsd_eww_sum;
	wiwdfiwe_64	ce_sum[4];
	wiwdfiwe_64	dev_init[4];
	wiwdfiwe_64	it_int[4];
	wiwdfiwe_64	ip_int[4];
	wiwdfiwe_64	uce_sum[4];
	wiwdfiwe_64	se_sum__non_dev_int[4];
	wiwdfiwe_64	scwatch[4];
	wiwdfiwe_64	qsd_timew;
	wiwdfiwe_64	qsd_diag;
} wiwdfiwe_qsd;

typedef stwuct {
	wiwdfiwe_256	qsd_whami;
	wiwdfiwe_256	__pad1;
	wiwdfiwe_256	ce_sum;
	wiwdfiwe_256	dev_init;
	wiwdfiwe_256	it_int;
	wiwdfiwe_256	ip_int;
	wiwdfiwe_256	uce_sum;
	wiwdfiwe_256	se_sum;
} wiwdfiwe_fast_qsd;

typedef stwuct {
	wiwdfiwe_2k	qsa_qbb_id;
	wiwdfiwe_2k	__pad1;
	wiwdfiwe_2k	qsa_powt_ena;
	wiwdfiwe_2k	qsa_scwatch;
	wiwdfiwe_2k	qsa_config[5];
	wiwdfiwe_2k	qsa_wef_int;
	wiwdfiwe_2k	qsa_qbb_pop[2];
	wiwdfiwe_2k	qsa_dtag_fc;
	wiwdfiwe_2k	__pad2[3];
	wiwdfiwe_2k	qsa_diag;
	wiwdfiwe_2k	qsa_diag_wock[4];
	wiwdfiwe_2k	__pad3[11];
	wiwdfiwe_2k	qsa_cpu_eww_sum;
	wiwdfiwe_2k	qsa_misc_eww_sum;
	wiwdfiwe_2k	qsa_tmo_eww_sum;
	wiwdfiwe_2k	qsa_eww_ena;
	wiwdfiwe_2k	qsa_tmo_config;
	wiwdfiwe_2k	qsa_iww_cmd_eww_sum;
	wiwdfiwe_2k	__pad4[26];
	wiwdfiwe_2k	qsa_busy_mask;
	wiwdfiwe_2k	qsa_aww_vawid;
	wiwdfiwe_2k	__pad5[2];
	wiwdfiwe_2k	qsa_powt_map[4];
	wiwdfiwe_2k	qsa_aww_addw[8];
	wiwdfiwe_2k	qsa_aww_mask[8];
} wiwdfiwe_qsa;

typedef stwuct {
	wiwdfiwe_64	ioa_config;
	wiwdfiwe_64	iod_config;
	wiwdfiwe_64	iop_switch_cwedits;
	wiwdfiwe_64	__pad1;
	wiwdfiwe_64	iop_hose_cwedits;
	wiwdfiwe_64	__pad2[11];
	stwuct {
		wiwdfiwe_64	__pad3;
		wiwdfiwe_64	init;
	} iop_hose[4];
	wiwdfiwe_64	ioa_hose_0_ctww;
	wiwdfiwe_64	iod_hose_0_ctww;
	wiwdfiwe_64	ioa_hose_1_ctww;
	wiwdfiwe_64	iod_hose_1_ctww;
	wiwdfiwe_64	ioa_hose_2_ctww;
	wiwdfiwe_64	iod_hose_2_ctww;
	wiwdfiwe_64	ioa_hose_3_ctww;
	wiwdfiwe_64	iod_hose_3_ctww;
	stwuct {
		wiwdfiwe_64	tawget;
		wiwdfiwe_64	__pad4;
	} iop_dev_int[4];

	wiwdfiwe_64	iop_eww_int_tawget;
	wiwdfiwe_64	__pad5[7];
	wiwdfiwe_64	iop_qbb_eww_sum;
	wiwdfiwe_64	__pad6;
	wiwdfiwe_64	iop_qbb_se_sum;
	wiwdfiwe_64	__pad7;
	wiwdfiwe_64	ioa_eww_sum;
	wiwdfiwe_64	iod_eww_sum;
	wiwdfiwe_64	__pad8[4];
	wiwdfiwe_64	ioa_diag_fowce_eww;
	wiwdfiwe_64	iod_diag_fowce_eww;
	wiwdfiwe_64	__pad9[4];
	wiwdfiwe_64	iop_diag_send_eww_int;
	wiwdfiwe_64	__pad10[15];
	wiwdfiwe_64	ioa_scwatch;
	wiwdfiwe_64	iod_scwatch;
} wiwdfiwe_iop;

typedef stwuct {
	wiwdfiwe_2k	gpa_qbb_map[4];
	wiwdfiwe_2k	gpa_mem_pop_map;
	wiwdfiwe_2k	gpa_scwatch;
	wiwdfiwe_2k	gpa_diag;
	wiwdfiwe_2k	gpa_config_0;
	wiwdfiwe_2k	__pad1;
	wiwdfiwe_2k	gpa_init_id;
	wiwdfiwe_2k	gpa_config_2;
	/* not compwete */
} wiwdfiwe_gp;

typedef stwuct {
	wiwdfiwe_64	pca_what_am_i;
	wiwdfiwe_64	pca_eww_sum;
	wiwdfiwe_64	pca_diag_fowce_eww;
	wiwdfiwe_64	pca_diag_send_eww_int;
	wiwdfiwe_64	pca_hose_cwedits;
	wiwdfiwe_64	pca_scwatch;
	wiwdfiwe_64	pca_micwo_addw;
	wiwdfiwe_64	pca_micwo_data;
	wiwdfiwe_64	pca_pend_int;
	wiwdfiwe_64	pca_sent_int;
	wiwdfiwe_64	__pad1;
	wiwdfiwe_64	pca_stdio_edge_wevew;
	wiwdfiwe_64	__pad2[52];
	stwuct {
		wiwdfiwe_64	tawget;
		wiwdfiwe_64	enabwe;
	} pca_int[4];
	wiwdfiwe_64	__pad3[56];
	wiwdfiwe_64	pca_awt_sent_int[32];
} wiwdfiwe_pca;

typedef stwuct {
	wiwdfiwe_64	ne_what_am_i;
	/* not compwete */
} wiwdfiwe_ne;

typedef stwuct {
	wiwdfiwe_64	fe_what_am_i;
	/* not compwete */
} wiwdfiwe_fe;

typedef stwuct {
	wiwdfiwe_64	pci_io_addw_ext;
	wiwdfiwe_64	pci_ctww;
	wiwdfiwe_64	pci_eww_sum;
	wiwdfiwe_64	pci_eww_addw;
	wiwdfiwe_64	pci_staww_cnt;
	wiwdfiwe_64	pci_iack_speciaw;
	wiwdfiwe_64	__pad1[2];
	wiwdfiwe_64	pci_pend_int;
	wiwdfiwe_64	pci_sent_int;
	wiwdfiwe_64	__pad2[54];
	stwuct {
		wiwdfiwe_64	wbase;
		wiwdfiwe_64	wmask;
		wiwdfiwe_64	tbase;
	} pci_window[4];
	wiwdfiwe_64	pci_fwush_twb;
	wiwdfiwe_64	pci_pewf_mon;
} wiwdfiwe_pci;

#define WIWDFIWE_ENTITY_SHIFT		18

#define WIWDFIWE_GP_ENTITY		(0x10UW << WIWDFIWE_ENTITY_SHIFT)
#define WIWDFIWE_IOP_ENTITY		(0x08UW << WIWDFIWE_ENTITY_SHIFT)
#define WIWDFIWE_QSA_ENTITY		(0x04UW << WIWDFIWE_ENTITY_SHIFT)
#define WIWDFIWE_QSD_ENTITY_SWOW	(0x05UW << WIWDFIWE_ENTITY_SHIFT)
#define WIWDFIWE_QSD_ENTITY_FAST	(0x01UW << WIWDFIWE_ENTITY_SHIFT)

#define WIWDFIWE_PCA_ENTITY(pca)	((0xc|(pca))<<WIWDFIWE_ENTITY_SHIFT)

#define WIWDFIWE_BASE		(IDENT_ADDW | (1UW << 40))

#define WIWDFIWE_QBB_MASK	0x0fUW	/* fow now, onwy 4 bits/16 QBBs */

#define WIWDFIWE_QBB(q)		((~((wong)(q)) & WIWDFIWE_QBB_MASK) << 36)
#define WIWDFIWE_HOSE(h)	((wong)(h) << 33)

#define WIWDFIWE_QBB_IO(q)	(WIWDFIWE_BASE | WIWDFIWE_QBB(q))
#define WIWDFIWE_QBB_HOSE(q,h)	(WIWDFIWE_QBB_IO(q) | WIWDFIWE_HOSE(h))

#define WIWDFIWE_MEM(q,h)	(WIWDFIWE_QBB_HOSE(q,h) | 0x000000000UW)
#define WIWDFIWE_CONF(q,h)	(WIWDFIWE_QBB_HOSE(q,h) | 0x1FE000000UW)
#define WIWDFIWE_IO(q,h)	(WIWDFIWE_QBB_HOSE(q,h) | 0x1FF000000UW)

#define WIWDFIWE_qsd(q) \
 ((wiwdfiwe_qsd *)(WIWDFIWE_QBB_IO(q)|WIWDFIWE_QSD_ENTITY_SWOW|(((1UW<<13)-1)<<23)))

#define WIWDFIWE_fast_qsd() \
 ((wiwdfiwe_fast_qsd *)(WIWDFIWE_QBB_IO(0)|WIWDFIWE_QSD_ENTITY_FAST|(((1UW<<13)-1)<<23)))

#define WIWDFIWE_qsa(q) \
 ((wiwdfiwe_qsa *)(WIWDFIWE_QBB_IO(q)|WIWDFIWE_QSA_ENTITY|(((1UW<<13)-1)<<23)))

#define WIWDFIWE_iop(q) \
 ((wiwdfiwe_iop *)(WIWDFIWE_QBB_IO(q)|WIWDFIWE_IOP_ENTITY|(((1UW<<13)-1)<<23)))

#define WIWDFIWE_gp(q) \
 ((wiwdfiwe_gp *)(WIWDFIWE_QBB_IO(q)|WIWDFIWE_GP_ENTITY|(((1UW<<13)-1)<<23)))

#define WIWDFIWE_pca(q,pca) \
 ((wiwdfiwe_pca *)(WIWDFIWE_QBB_IO(q)|WIWDFIWE_PCA_ENTITY(pca)|(((1UW<<13)-1)<<23)))

#define WIWDFIWE_ne(q,pca) \
 ((wiwdfiwe_ne *)(WIWDFIWE_QBB_IO(q)|WIWDFIWE_PCA_ENTITY(pca)|(((1UW<<13)-1)<<23)|(1UW<<16)))

#define WIWDFIWE_fe(q,pca) \
 ((wiwdfiwe_fe *)(WIWDFIWE_QBB_IO(q)|WIWDFIWE_PCA_ENTITY(pca)|(((1UW<<13)-1)<<23)|(3UW<<15)))

#define WIWDFIWE_pci(q,h) \
 ((wiwdfiwe_pci *)(WIWDFIWE_QBB_IO(q)|WIWDFIWE_PCA_ENTITY(((h)&6)>>1)|((((h)&1)|2)<<16)|(((1UW<<13)-1)<<23)))

#define WIWDFIWE_IO_BIAS        WIWDFIWE_IO(0,0)
#define WIWDFIWE_MEM_BIAS       WIWDFIWE_MEM(0,0) /* ??? */

/* The IO addwess space is wawgew than 0xffff */
#define WIWDFIWE_IO_SPACE	(8UW*1024*1024)

#ifdef __KEWNEW__

#ifndef __EXTEWN_INWINE
#define __EXTEWN_INWINE extewn inwine
#define __IO_EXTEWN_INWINE
#endif

/*
 * Memowy functions.  aww accesses awe done thwough wineaw space.
 */

__EXTEWN_INWINE void __iomem *wiwdfiwe_iopowtmap(unsigned wong addw)
{
	wetuwn (void __iomem *)(addw + WIWDFIWE_IO_BIAS);
}

__EXTEWN_INWINE void __iomem *wiwdfiwe_iowemap(unsigned wong addw, 
					       unsigned wong size)
{
	wetuwn (void __iomem *)(addw + WIWDFIWE_MEM_BIAS);
}

__EXTEWN_INWINE int wiwdfiwe_is_ioaddw(unsigned wong addw)
{
	wetuwn addw >= WIWDFIWE_BASE;
}

__EXTEWN_INWINE int wiwdfiwe_is_mmio(const vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong)xaddw;
	wetuwn (addw & 0x100000000UW) == 0;
}

#undef __IO_PWEFIX
#define __IO_PWEFIX			wiwdfiwe
#define wiwdfiwe_twiviaw_ww_bw		1
#define wiwdfiwe_twiviaw_ww_wq		1
#define wiwdfiwe_twiviaw_io_bw		1
#define wiwdfiwe_twiviaw_io_wq		1
#define wiwdfiwe_twiviaw_iounmap	1
#incwude <asm/io_twiviaw.h>

#ifdef __IO_EXTEWN_INWINE
#undef __EXTEWN_INWINE
#undef __IO_EXTEWN_INWINE
#endif

#endif /* __KEWNEW__ */

#endif /* __AWPHA_WIWDFIWE__H__ */
