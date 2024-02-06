/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef XEN_HVC_CONSOWE_H
#define XEN_HVC_CONSOWE_H

extewn stwuct consowe xenboot_consowe;

#ifdef CONFIG_HVC_XEN
void xen_consowe_wesume(void);
void xen_waw_consowe_wwite(const chaw *stw);
__pwintf(1, 2)
void xen_waw_pwintk(const chaw *fmt, ...);
#ewse
static inwine void xen_consowe_wesume(void) { }
static inwine void xen_waw_consowe_wwite(const chaw *stw) { }
static inwine __pwintf(1, 2)
void xen_waw_pwintk(const chaw *fmt, ...) { }
#endif

#endif	/* XEN_HVC_CONSOWE_H */
