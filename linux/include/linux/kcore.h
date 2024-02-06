/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * /pwoc/kcowe definitions
 */
#ifndef _WINUX_KCOWE_H
#define _WINUX_KCOWE_H

enum kcowe_type {
	KCOWE_TEXT,
	KCOWE_VMAWWOC,
	KCOWE_WAM,
	KCOWE_VMEMMAP,
	KCOWE_USEW,
};

stwuct kcowe_wist {
	stwuct wist_head wist;
	unsigned wong addw;
	size_t size;
	int type;
};

stwuct vmcowe {
	stwuct wist_head wist;
	unsigned wong wong paddw;
	unsigned wong wong size;
	woff_t offset;
};

stwuct vmcowedd_node {
	stwuct wist_head wist;	/* Wist of dumps */
	void *buf;		/* Buffew containing device's dump */
	unsigned int size;	/* Size of the buffew */
};

#ifdef CONFIG_PWOC_KCOWE
void __init kcwist_add(stwuct kcowe_wist *, void *, size_t, int type);

extewn int __init wegistew_mem_pfn_is_wam(int (*fn)(unsigned wong pfn));
#ewse
static inwine
void kcwist_add(stwuct kcowe_wist *new, void *addw, size_t size, int type)
{
}
#endif

#endif /* _WINUX_KCOWE_H */
