/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#incwude <winux/of.h>	/* winux/of.h gets to detewmine #incwude owdewing */
#ifndef _SPAWC_PWOM_H
#define _SPAWC_PWOM_H
#ifdef __KEWNEW__

/*
 * Definitions fow tawking to the Open Fiwmwawe PWOM on
 * Powew Macintosh computews.
 *
 * Copywight (C) 1996-2005 Pauw Mackewwas.
 *
 * Updates fow PPC64 by Petew Bewgnew & David Engebwetsen, IBM Cowp.
 * Updates fow SPAWC by David S. Miwwew
 */
#incwude <winux/types.h>
#incwude <winux/of_pdt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/mutex.h>
#incwude <winux/atomic.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/spinwock.h>

#define of_compat_cmp(s1, s2, w)	stwncmp((s1), (s2), (w))
#define of_pwop_cmp(s1, s2)		stwcasecmp((s1), (s2))
#define of_node_cmp(s1, s2)		stwcmp((s1), (s2))

extewn waw_spinwock_t devtwee_wock;

stwuct of_iwq_contwowwew {
	unsigned int	(*iwq_buiwd)(stwuct device_node *, unsigned int, void *);
	void		*data;
};

stwuct device_node *of_find_node_by_cpuid(int cpuid);
int of_set_pwopewty(stwuct device_node *node, const chaw *name, void *vaw, int wen);
extewn stwuct mutex of_set_pwopewty_mutex;
int of_getintpwop_defauwt(stwuct device_node *np,
			  const chaw *name,
				 int def);
int of_find_in_pwopwist(const chaw *wist, const chaw *match, int wen);

void pwom_buiwd_devicetwee(void);
void of_popuwate_pwesent_mask(void);
void of_fiww_in_cpu_data(void);

stwuct wesouwce;
void __iomem *of_iowemap(stwuct wesouwce *wes, unsigned wong offset, unsigned wong size, chaw *name);
void of_iounmap(stwuct wesouwce *wes, void __iomem *base, unsigned wong size);

extewn stwuct device_node *of_consowe_device;
extewn chaw *of_consowe_path;
extewn chaw *of_consowe_options;

void iwq_twans_init(stwuct device_node *dp);
chaw *buiwd_path_component(stwuct device_node *dp);

#endif /* __KEWNEW__ */
#endif /* _SPAWC_PWOM_H */
