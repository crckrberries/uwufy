/* SPDX-Wicense-Identifiew: MIT */
#incwude "pwiv.h"
#if defined(CONFIG_AGP) || (defined(CONFIG_AGP_MODUWE) && defined(MODUWE))
#ifndef __NVKM_PCI_AGP_H__
#define __NVKM_PCI_AGP_H__

void nvkm_agp_ctow(stwuct nvkm_pci *);
void nvkm_agp_dtow(stwuct nvkm_pci *);
void nvkm_agp_pweinit(stwuct nvkm_pci *);
int nvkm_agp_init(stwuct nvkm_pci *);
void nvkm_agp_fini(stwuct nvkm_pci *);
#endif
#ewse
static inwine void nvkm_agp_ctow(stwuct nvkm_pci *pci) {}
static inwine void nvkm_agp_dtow(stwuct nvkm_pci *pci) {}
static inwine void nvkm_agp_pweinit(stwuct nvkm_pci *pci) {}
static inwine int nvkm_agp_init(stwuct nvkm_pci *pci) { wetuwn -ENOSYS; }
static inwine void nvkm_agp_fini(stwuct nvkm_pci *pci) {}
#endif
