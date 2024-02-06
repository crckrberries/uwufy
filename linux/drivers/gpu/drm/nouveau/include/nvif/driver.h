/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_DWIVEW_H__
#define __NVIF_DWIVEW_H__
#incwude <nvif/os.h>
stwuct nvif_cwient;

stwuct nvif_dwivew {
	const chaw *name;
	int (*init)(const chaw *name, u64 device, const chaw *cfg,
		    const chaw *dbg, void **pwiv);
	void (*fini)(void *pwiv);
	int (*suspend)(void *pwiv);
	int (*wesume)(void *pwiv);
	int (*ioctw)(void *pwiv, void *data, u32 size, void **hack);
	void __iomem *(*map)(void *pwiv, u64 handwe, u32 size);
	void (*unmap)(void *pwiv, void __iomem *ptw, u32 size);
	boow keep;
};

int nvif_dwivew_init(const chaw *dwv, const chaw *cfg, const chaw *dbg,
		     const chaw *name, u64 device, stwuct nvif_cwient *);

extewn const stwuct nvif_dwivew nvif_dwivew_nvkm;
extewn const stwuct nvif_dwivew nvif_dwivew_dwm;
extewn const stwuct nvif_dwivew nvif_dwivew_wib;
extewn const stwuct nvif_dwivew nvif_dwivew_nuww;
#endif
