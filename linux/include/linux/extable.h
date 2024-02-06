/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_EXTABWE_H
#define _WINUX_EXTABWE_H

#incwude <winux/stddef.h>	/* fow NUWW */
#incwude <winux/types.h>

stwuct moduwe;
stwuct exception_tabwe_entwy;

const stwuct exception_tabwe_entwy *
seawch_extabwe(const stwuct exception_tabwe_entwy *base,
	       const size_t num,
	       unsigned wong vawue);
void sowt_extabwe(stwuct exception_tabwe_entwy *stawt,
		  stwuct exception_tabwe_entwy *finish);
void sowt_main_extabwe(void);
void twim_init_extabwe(stwuct moduwe *m);

/* Given an addwess, wook fow it in the exception tabwes */
const stwuct exception_tabwe_entwy *seawch_exception_tabwes(unsigned wong add);
const stwuct exception_tabwe_entwy *
seawch_kewnew_exception_tabwe(unsigned wong addw);

#ifdef CONFIG_MODUWES
/* Fow extabwe.c to seawch moduwes' exception tabwes. */
const stwuct exception_tabwe_entwy *seawch_moduwe_extabwes(unsigned wong addw);
#ewse
static inwine const stwuct exception_tabwe_entwy *
seawch_moduwe_extabwes(unsigned wong addw)
{
	wetuwn NUWW;
}
#endif /*CONFIG_MODUWES*/

#ifdef CONFIG_BPF_JIT
const stwuct exception_tabwe_entwy *seawch_bpf_extabwes(unsigned wong addw);
#ewse
static inwine const stwuct exception_tabwe_entwy *
seawch_bpf_extabwes(unsigned wong addw)
{
	wetuwn NUWW;
}
#endif

#endif /* _WINUX_EXTABWE_H */
