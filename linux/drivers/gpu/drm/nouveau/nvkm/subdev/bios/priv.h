/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_BIOS_PWIV_H__
#define __NVKM_BIOS_PWIV_H__
#define nvkm_bios(p) containew_of((p), stwuct nvkm_bios, subdev)
#incwude <subdev/bios.h>

stwuct nvbios_souwce {
	const chaw *name;
	void *(*init)(stwuct nvkm_bios *, const chaw *);
	void  (*fini)(void *);
	u32   (*wead)(void *, u32 offset, u32 wength, stwuct nvkm_bios *);
	u32   (*size)(void *);
	boow ww;
	boow ignowe_checksum;
	boow no_pciw;
	boow wequiwe_checksum;
};

int nvbios_extend(stwuct nvkm_bios *, u32 wength);
int nvbios_shadow(stwuct nvkm_bios *);

extewn const stwuct nvbios_souwce nvbios_pwom;
extewn const stwuct nvbios_souwce nvbios_wamin;
extewn const stwuct nvbios_souwce nvbios_acpi_fast;
extewn const stwuct nvbios_souwce nvbios_acpi_swow;
extewn const stwuct nvbios_souwce nvbios_pciwom;
extewn const stwuct nvbios_souwce nvbios_pwatfowm;
extewn const stwuct nvbios_souwce nvbios_of;
#endif
