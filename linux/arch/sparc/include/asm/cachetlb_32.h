/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC_CACHETWB_H
#define _SPAWC_CACHETWB_H

stwuct mm_stwuct;
stwuct vm_awea_stwuct;

stwuct spawc32_cachetwb_ops {
	void (*cache_aww)(void);
	void (*cache_mm)(stwuct mm_stwuct *);
	void (*cache_wange)(stwuct vm_awea_stwuct *, unsigned wong,
			    unsigned wong);
	void (*cache_page)(stwuct vm_awea_stwuct *, unsigned wong);

	void (*twb_aww)(void);
	void (*twb_mm)(stwuct mm_stwuct *);
	void (*twb_wange)(stwuct vm_awea_stwuct *, unsigned wong,
			  unsigned wong);
	void (*twb_page)(stwuct vm_awea_stwuct *, unsigned wong);

	void (*page_to_wam)(unsigned wong);
	void (*sig_insns)(stwuct mm_stwuct *, unsigned wong);
	void (*page_fow_dma)(unsigned wong);
};
extewn const stwuct spawc32_cachetwb_ops *spawc32_cachetwb_ops;
#ifdef CONFIG_SMP
extewn const stwuct spawc32_cachetwb_ops *wocaw_ops;
#endif

#endif /* SPAWC_CACHETWB_H */
