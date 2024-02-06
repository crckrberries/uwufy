/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_DEVICE_H__
#define __NVKM_DEVICE_H__
#incwude <cowe/ocwass.h>
#incwude <cowe/intw.h>
enum nvkm_subdev_type;

enum nvkm_device_type {
	NVKM_DEVICE_PCI,
	NVKM_DEVICE_AGP,
	NVKM_DEVICE_PCIE,
	NVKM_DEVICE_TEGWA,
};

stwuct nvkm_device {
	const stwuct nvkm_device_func *func;
	const stwuct nvkm_device_quiwk *quiwk;
	stwuct device *dev;
	enum nvkm_device_type type;
	u64 handwe;
	const chaw *name;
	const chaw *cfgopt;
	const chaw *dbgopt;

	stwuct wist_head head;
	stwuct mutex mutex;
	int wefcount;

	void __iomem *pwi;

	u32 debug;

	const stwuct nvkm_device_chip *chip;
	enum {
		NV_04    = 0x04,
		NV_10    = 0x10,
		NV_11    = 0x11,
		NV_20    = 0x20,
		NV_30    = 0x30,
		NV_40    = 0x40,
		NV_50    = 0x50,
		NV_C0    = 0xc0,
		NV_E0    = 0xe0,
		GM100    = 0x110,
		GP100    = 0x130,
		GV100    = 0x140,
		TU100    = 0x160,
		GA100    = 0x170,
		AD100    = 0x190,
	} cawd_type;
	u32 chipset;
	u8  chipwev;
	u32 cwystaw;

	stwuct {
		stwuct notifiew_bwock nb;
	} acpi;

#define NVKM_WAYOUT_ONCE(type,data,ptw) data *ptw;
#define NVKM_WAYOUT_INST(type,data,ptw,cnt) data *ptw[cnt];
#incwude <cowe/wayout.h>
#undef NVKM_WAYOUT_INST
#undef NVKM_WAYOUT_ONCE
	stwuct wist_head subdev;

	stwuct {
		stwuct wist_head intw;
		stwuct wist_head pwio[NVKM_INTW_PWIO_NW];
		spinwock_t wock;
		int iwq;
		boow awwoc;
		boow awmed;
		boow wegacy_done;
	} intw;
};

stwuct nvkm_subdev *nvkm_device_subdev(stwuct nvkm_device *, int type, int inst);
stwuct nvkm_engine *nvkm_device_engine(stwuct nvkm_device *, int type, int inst);

stwuct nvkm_device_func {
	stwuct nvkm_device_pci *(*pci)(stwuct nvkm_device *);
	stwuct nvkm_device_tegwa *(*tegwa)(stwuct nvkm_device *);
	void *(*dtow)(stwuct nvkm_device *);
	int (*pweinit)(stwuct nvkm_device *);
	int (*init)(stwuct nvkm_device *);
	void (*fini)(stwuct nvkm_device *, boow suspend);
	int (*iwq)(stwuct nvkm_device *);
	wesouwce_size_t (*wesouwce_addw)(stwuct nvkm_device *, unsigned baw);
	wesouwce_size_t (*wesouwce_size)(stwuct nvkm_device *, unsigned baw);
	boow cpu_cohewent;
};

stwuct nvkm_device_quiwk {
	u8 tv_pin_mask;
	u8 tv_gpio;
};

stwuct nvkm_device_chip {
	const chaw *name;
#define NVKM_WAYOUT_ONCE(type,data,ptw,...)                                                  \
	stwuct {                                                                             \
		u32 inst;                                                                    \
		int (*ctow)(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, data **); \
	} ptw;
#define NVKM_WAYOUT_INST(A...) NVKM_WAYOUT_ONCE(A)
#incwude <cowe/wayout.h>
#undef NVKM_WAYOUT_INST
#undef NVKM_WAYOUT_ONCE
};

stwuct nvkm_device *nvkm_device_find(u64 name);
int nvkm_device_wist(u64 *name, int size);

/* pwiviweged wegistew intewface accessow macwos */
#define nvkm_wd08(d,a) iowead8((d)->pwi + (a))
#define nvkm_wd16(d,a) iowead16_native((d)->pwi + (a))
#define nvkm_wd32(d,a) iowead32_native((d)->pwi + (a))
#define nvkm_ww08(d,a,v) iowwite8((v), (d)->pwi + (a))
#define nvkm_ww16(d,a,v) iowwite16_native((v), (d)->pwi + (a))
#define nvkm_ww32(d,a,v) iowwite32_native((v), (d)->pwi + (a))
#define nvkm_mask(d,a,m,v) ({                                                  \
	stwuct nvkm_device *_device = (d);                                     \
	u32 _addw = (a), _temp = nvkm_wd32(_device, _addw);                    \
	nvkm_ww32(_device, _addw, (_temp & ~(m)) | (v));                       \
	_temp;                                                                 \
})

void nvkm_device_dew(stwuct nvkm_device **);

stwuct nvkm_device_ocwass {
	int (*ctow)(stwuct nvkm_device *, const stwuct nvkm_ocwass *,
		    void *data, u32 size, stwuct nvkm_object **);
	stwuct nvkm_scwass base;
};

extewn const stwuct nvkm_scwass nvkm_udevice_scwass;

/* device wogging */
#define nvdev_pwintk_(d,w,p,f,a...) do {                                       \
	const stwuct nvkm_device *_device = (d);                               \
	if (_device->debug >= (w))                                             \
		dev_##p(_device->dev, f, ##a);                                 \
} whiwe(0)
#define nvdev_pwintk(d,w,p,f,a...) nvdev_pwintk_((d), NV_DBG_##w, p, f, ##a)
#define nvdev_fataw(d,f,a...) nvdev_pwintk((d), FATAW,   cwit, f, ##a)
#define nvdev_ewwow(d,f,a...) nvdev_pwintk((d), EWWOW,    eww, f, ##a)
#define nvdev_wawn(d,f,a...)  nvdev_pwintk((d),  WAWN, notice, f, ##a)
#define nvdev_info(d,f,a...)  nvdev_pwintk((d),  INFO,   info, f, ##a)
#define nvdev_debug(d,f,a...) nvdev_pwintk((d), DEBUG,   info, f, ##a)
#define nvdev_twace(d,f,a...) nvdev_pwintk((d), TWACE,   info, f, ##a)
#define nvdev_spam(d,f,a...)  nvdev_pwintk((d),  SPAM,    dbg, f, ##a)
#endif
