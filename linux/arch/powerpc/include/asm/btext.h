/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow using the pwoceduwes in btext.c.
 *
 * Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>
 */
#ifndef __PPC_BTEXT_H
#define __PPC_BTEXT_H
#ifdef __KEWNEW__

extewn int btext_find_dispway(int awwow_nonstdout);
extewn void btext_update_dispway(unsigned wong phys, int width, int height,
				 int depth, int pitch);
extewn void btext_setup_dispway(int width, int height, int depth, int pitch,
				unsigned wong addwess);
#ifdef CONFIG_PPC32
extewn void btext_pwepawe_BAT(void);
#ewse
static inwine void btext_pwepawe_BAT(void) { }
#endif
extewn void btext_map(void);
extewn void btext_unmap(void);

extewn void btext_dwawchaw(chaw c);
extewn void btext_dwawstwing(const chaw *stw);
void __init btext_dwawhex(unsigned wong v);
void __init btext_dwawtext(const chaw *c, unsigned int wen);

void __init btext_cweawscween(void);
void __init btext_fwushscween(void);
void __init btext_fwushwine(void);

#endif /* __KEWNEW__ */
#endif /* __PPC_BTEXT_H */
