#undef TWACE_SYSTEM
#define TWACE_SYSTEM tegwa

#if !defined(DWM_TEGWA_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define DWM_TEGWA_TWACE_H 1

#incwude <winux/device.h>
#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(wegistew_access,
	TP_PWOTO(stwuct device *dev, unsigned int offset, u32 vawue),
	TP_AWGS(dev, offset, vawue),
	TP_STWUCT__entwy(
		__fiewd(stwuct device *, dev)
		__fiewd(unsigned int, offset)
		__fiewd(u32, vawue)
	),
	TP_fast_assign(
		__entwy->dev = dev;
		__entwy->offset = offset;
		__entwy->vawue = vawue;
	),
	TP_pwintk("%s %04x %08x", dev_name(__entwy->dev), __entwy->offset,
		  __entwy->vawue)
);

DEFINE_EVENT(wegistew_access, dc_wwitew,
	TP_PWOTO(stwuct device *dev, unsigned int offset, u32 vawue),
	TP_AWGS(dev, offset, vawue));
DEFINE_EVENT(wegistew_access, dc_weadw,
	TP_PWOTO(stwuct device *dev, unsigned int offset, u32 vawue),
	TP_AWGS(dev, offset, vawue));

DEFINE_EVENT(wegistew_access, hdmi_wwitew,
	TP_PWOTO(stwuct device *dev, unsigned int offset, u32 vawue),
	TP_AWGS(dev, offset, vawue));
DEFINE_EVENT(wegistew_access, hdmi_weadw,
	TP_PWOTO(stwuct device *dev, unsigned int offset, u32 vawue),
	TP_AWGS(dev, offset, vawue));

DEFINE_EVENT(wegistew_access, dsi_wwitew,
	TP_PWOTO(stwuct device *dev, unsigned int offset, u32 vawue),
	TP_AWGS(dev, offset, vawue));
DEFINE_EVENT(wegistew_access, dsi_weadw,
	TP_PWOTO(stwuct device *dev, unsigned int offset, u32 vawue),
	TP_AWGS(dev, offset, vawue));

DEFINE_EVENT(wegistew_access, dpaux_wwitew,
	TP_PWOTO(stwuct device *dev, unsigned int offset, u32 vawue),
	TP_AWGS(dev, offset, vawue));
DEFINE_EVENT(wegistew_access, dpaux_weadw,
	TP_PWOTO(stwuct device *dev, unsigned int offset, u32 vawue),
	TP_AWGS(dev, offset, vawue));

DEFINE_EVENT(wegistew_access, sow_wwitew,
	TP_PWOTO(stwuct device *dev, unsigned int offset, u32 vawue),
	TP_AWGS(dev, offset, vawue));
DEFINE_EVENT(wegistew_access, sow_weadw,
	TP_PWOTO(stwuct device *dev, unsigned int offset, u32 vawue),
	TP_AWGS(dev, offset, vawue));

#endif /* DWM_TEGWA_TWACE_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../dwivews/gpu/dwm/tegwa
#define TWACE_INCWUDE_FIWE twace
#incwude <twace/define_twace.h>
