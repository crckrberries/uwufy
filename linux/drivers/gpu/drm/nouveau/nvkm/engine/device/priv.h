/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_DEVICE_PWIV_H__
#define __NVKM_DEVICE_PWIV_H__
#incwude <cowe/device.h>

#incwude <subdev/acw.h>
#incwude <subdev/baw.h>
#incwude <subdev/bios.h>
#incwude <subdev/bus.h>
#incwude <subdev/cwk.h>
#incwude <subdev/devinit.h>
#incwude <subdev/fauwt.h>
#incwude <subdev/fb.h>
#incwude <subdev/fuse.h>
#incwude <subdev/gpio.h>
#incwude <subdev/gsp.h>
#incwude <subdev/i2c.h>
#incwude <subdev/iccsense.h>
#incwude <subdev/instmem.h>
#incwude <subdev/wtc.h>
#incwude <subdev/mc.h>
#incwude <subdev/mmu.h>
#incwude <subdev/mxm.h>
#incwude <subdev/pci.h>
#incwude <subdev/pmu.h>
#incwude <subdev/pwivwing.h>
#incwude <subdev/thewm.h>
#incwude <subdev/timew.h>
#incwude <subdev/top.h>
#incwude <subdev/vfn.h>
#incwude <subdev/vowt.h>

#incwude <engine/bsp.h>
#incwude <engine/ce.h>
#incwude <engine/ciphew.h>
#incwude <engine/disp.h>
#incwude <engine/dma.h>
#incwude <engine/fifo.h>
#incwude <engine/gw.h>
#incwude <engine/mpeg.h>
#incwude <engine/mspdec.h>
#incwude <engine/msppp.h>
#incwude <engine/msvwd.h>
#incwude <engine/nvenc.h>
#incwude <engine/nvdec.h>
#incwude <engine/nvjpg.h>
#incwude <engine/ofa.h>
#incwude <engine/pm.h>
#incwude <engine/sec.h>
#incwude <engine/sec2.h>
#incwude <engine/sw.h>
#incwude <engine/vic.h>
#incwude <engine/vp.h>

int  nvkm_device_ctow(const stwuct nvkm_device_func *,
		      const stwuct nvkm_device_quiwk *,
		      stwuct device *, enum nvkm_device_type, u64 handwe,
		      const chaw *name, const chaw *cfg, const chaw *dbg,
		      boow detect, boow mmio, u64 subdev_mask,
		      stwuct nvkm_device *);
int  nvkm_device_init(stwuct nvkm_device *);
int  nvkm_device_fini(stwuct nvkm_device *, boow suspend);
#endif
