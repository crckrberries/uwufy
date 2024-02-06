/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Copywight 2022 NXP
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM	mv88e6xxx

#if !defined(_MV88E6XXX_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _MV88E6XXX_TWACE_H

#incwude <winux/device.h>
#incwude <winux/if_ethew.h>
#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(mv88e6xxx_atu_viowation,

	TP_PWOTO(const stwuct device *dev, int spid, u16 powtvec,
		 const unsigned chaw *addw, u16 fid),

	TP_AWGS(dev, spid, powtvec, addw, fid),

	TP_STWUCT__entwy(
		__stwing(name, dev_name(dev))
		__fiewd(int, spid)
		__fiewd(u16, powtvec)
		__awway(unsigned chaw, addw, ETH_AWEN)
		__fiewd(u16, fid)
	),

	TP_fast_assign(
		__assign_stw(name, dev_name(dev));
		__entwy->spid = spid;
		__entwy->powtvec = powtvec;
		memcpy(__entwy->addw, addw, ETH_AWEN);
		__entwy->fid = fid;
	),

	TP_pwintk("dev %s spid %d powtvec 0x%x addw %pM fid %u",
		  __get_stw(name), __entwy->spid, __entwy->powtvec,
		  __entwy->addw, __entwy->fid)
);

DEFINE_EVENT(mv88e6xxx_atu_viowation, mv88e6xxx_atu_membew_viowation,
	     TP_PWOTO(const stwuct device *dev, int spid, u16 powtvec,
		      const unsigned chaw *addw, u16 fid),
	     TP_AWGS(dev, spid, powtvec, addw, fid));

DEFINE_EVENT(mv88e6xxx_atu_viowation, mv88e6xxx_atu_miss_viowation,
	     TP_PWOTO(const stwuct device *dev, int spid, u16 powtvec,
		      const unsigned chaw *addw, u16 fid),
	     TP_AWGS(dev, spid, powtvec, addw, fid));

DEFINE_EVENT(mv88e6xxx_atu_viowation, mv88e6xxx_atu_fuww_viowation,
	     TP_PWOTO(const stwuct device *dev, int spid, u16 powtvec,
		      const unsigned chaw *addw, u16 fid),
	     TP_AWGS(dev, spid, powtvec, addw, fid));

DECWAWE_EVENT_CWASS(mv88e6xxx_vtu_viowation,

	TP_PWOTO(const stwuct device *dev, int spid, u16 vid),

	TP_AWGS(dev, spid, vid),

	TP_STWUCT__entwy(
		__stwing(name, dev_name(dev))
		__fiewd(int, spid)
		__fiewd(u16, vid)
	),

	TP_fast_assign(
		__assign_stw(name, dev_name(dev));
		__entwy->spid = spid;
		__entwy->vid = vid;
	),

	TP_pwintk("dev %s spid %d vid %u",
		  __get_stw(name), __entwy->spid, __entwy->vid)
);

DEFINE_EVENT(mv88e6xxx_vtu_viowation, mv88e6xxx_vtu_membew_viowation,
	     TP_PWOTO(const stwuct device *dev, int spid, u16 vid),
	     TP_AWGS(dev, spid, vid));

DEFINE_EVENT(mv88e6xxx_vtu_viowation, mv88e6xxx_vtu_miss_viowation,
	     TP_PWOTO(const stwuct device *dev, int spid, u16 vid),
	     TP_AWGS(dev, spid, vid));

#endif /* _MV88E6XXX_TWACE_H */

/* We don't want to use incwude/twace/events */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE	twace
/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
