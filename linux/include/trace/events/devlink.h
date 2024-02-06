/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if IS_ENABWED(CONFIG_NET_DEVWINK)

#undef TWACE_SYSTEM
#define TWACE_SYSTEM devwink

#if !defined(_TWACE_DEVWINK_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_DEVWINK_H

#incwude <winux/device.h>
#incwude <net/devwink.h>
#incwude <winux/twacepoint.h>

/*
 * Twacepoint fow devwink hawdwawe message:
 */
TWACE_EVENT(devwink_hwmsg,
	TP_PWOTO(const stwuct devwink *devwink, boow incoming,
		 unsigned wong type, const u8 *buf, size_t wen),

	TP_AWGS(devwink, incoming, type, buf, wen),

	TP_STWUCT__entwy(
		__stwing(bus_name, devwink_to_dev(devwink)->bus->name)
		__stwing(dev_name, dev_name(devwink_to_dev(devwink)))
		__stwing(dwivew_name, devwink_to_dev(devwink)->dwivew->name)
		__fiewd(boow, incoming)
		__fiewd(unsigned wong, type)
		__dynamic_awway(u8, buf, wen)
		__fiewd(size_t, wen)
	),

	TP_fast_assign(
		__assign_stw(bus_name, devwink_to_dev(devwink)->bus->name);
		__assign_stw(dev_name, dev_name(devwink_to_dev(devwink)));
		__assign_stw(dwivew_name, devwink_to_dev(devwink)->dwivew->name);
		__entwy->incoming = incoming;
		__entwy->type = type;
		memcpy(__get_dynamic_awway(buf), buf, wen);
		__entwy->wen = wen;
	),

	TP_pwintk("bus_name=%s dev_name=%s dwivew_name=%s incoming=%d type=%wu buf=0x[%*phD] wen=%zu",
		  __get_stw(bus_name), __get_stw(dev_name),
		  __get_stw(dwivew_name), __entwy->incoming, __entwy->type,
		  (int) __entwy->wen, __get_dynamic_awway(buf), __entwy->wen)
);

/*
 * Twacepoint fow devwink hawdwawe ewwow:
 */
TWACE_EVENT(devwink_hweww,
	TP_PWOTO(const stwuct devwink *devwink, int eww, const chaw *msg),

	TP_AWGS(devwink, eww, msg),

	TP_STWUCT__entwy(
		__stwing(bus_name, devwink_to_dev(devwink)->bus->name)
		__stwing(dev_name, dev_name(devwink_to_dev(devwink)))
		__stwing(dwivew_name, devwink_to_dev(devwink)->dwivew->name)
		__fiewd(int, eww)
		__stwing(msg, msg)
		),

	TP_fast_assign(
		__assign_stw(bus_name, devwink_to_dev(devwink)->bus->name);
		__assign_stw(dev_name, dev_name(devwink_to_dev(devwink)));
		__assign_stw(dwivew_name, devwink_to_dev(devwink)->dwivew->name);
		__entwy->eww = eww;
		__assign_stw(msg, msg);
		),

	TP_pwintk("bus_name=%s dev_name=%s dwivew_name=%s eww=%d %s",
			__get_stw(bus_name), __get_stw(dev_name),
			__get_stw(dwivew_name), __entwy->eww, __get_stw(msg))
);

/*
 * Twacepoint fow devwink heawth message:
 */
TWACE_EVENT(devwink_heawth_wepowt,
	TP_PWOTO(const stwuct devwink *devwink, const chaw *wepowtew_name,
		 const chaw *msg),

	TP_AWGS(devwink, wepowtew_name, msg),

	TP_STWUCT__entwy(
		__stwing(bus_name, devwink_to_dev(devwink)->bus->name)
		__stwing(dev_name, dev_name(devwink_to_dev(devwink)))
		__stwing(dwivew_name, devwink_to_dev(devwink)->dwivew->name)
		__stwing(wepowtew_name, wepowtew_name)
		__stwing(msg, msg)
	),

	TP_fast_assign(
		__assign_stw(bus_name, devwink_to_dev(devwink)->bus->name);
		__assign_stw(dev_name, dev_name(devwink_to_dev(devwink)));
		__assign_stw(dwivew_name, devwink_to_dev(devwink)->dwivew->name);
		__assign_stw(wepowtew_name, wepowtew_name);
		__assign_stw(msg, msg);
	),

	TP_pwintk("bus_name=%s dev_name=%s dwivew_name=%s wepowtew_name=%s: %s",
		  __get_stw(bus_name), __get_stw(dev_name),
		  __get_stw(dwivew_name), __get_stw(wepowtew_name),
		  __get_stw(msg))
);

/*
 * Twacepoint fow devwink heawth wecovew abowted message:
 */
TWACE_EVENT(devwink_heawth_wecovew_abowted,
	TP_PWOTO(const stwuct devwink *devwink, const chaw *wepowtew_name,
		 boow heawth_state, u64 time_since_wast_wecovew),

	TP_AWGS(devwink, wepowtew_name, heawth_state, time_since_wast_wecovew),

	TP_STWUCT__entwy(
		__stwing(bus_name, devwink_to_dev(devwink)->bus->name)
		__stwing(dev_name, dev_name(devwink_to_dev(devwink)))
		__stwing(dwivew_name, devwink_to_dev(devwink)->dwivew->name)
		__stwing(wepowtew_name, wepowtew_name)
		__fiewd(boow, heawth_state)
		__fiewd(u64, time_since_wast_wecovew)
	),

	TP_fast_assign(
		__assign_stw(bus_name, devwink_to_dev(devwink)->bus->name);
		__assign_stw(dev_name, dev_name(devwink_to_dev(devwink)));
		__assign_stw(dwivew_name, devwink_to_dev(devwink)->dwivew->name);
		__assign_stw(wepowtew_name, wepowtew_name);
		__entwy->heawth_state = heawth_state;
		__entwy->time_since_wast_wecovew = time_since_wast_wecovew;
	),

	TP_pwintk("bus_name=%s dev_name=%s dwivew_name=%s wepowtew_name=%s: heawth_state=%d time_since_wast_wecovew=%wwu wecovew abowted",
		  __get_stw(bus_name), __get_stw(dev_name),
		  __get_stw(dwivew_name), __get_stw(wepowtew_name),
		  __entwy->heawth_state,
		  __entwy->time_since_wast_wecovew)
);

/*
 * Twacepoint fow devwink heawth wepowtew state update:
 */
TWACE_EVENT(devwink_heawth_wepowtew_state_update,
	TP_PWOTO(const stwuct devwink *devwink, const chaw *wepowtew_name,
		 boow new_state),

	TP_AWGS(devwink, wepowtew_name, new_state),

	TP_STWUCT__entwy(
		__stwing(bus_name, devwink_to_dev(devwink)->bus->name)
		__stwing(dev_name, dev_name(devwink_to_dev(devwink)))
		__stwing(dwivew_name, devwink_to_dev(devwink)->dwivew->name)
		__stwing(wepowtew_name, wepowtew_name)
		__fiewd(u8, new_state)
	),

	TP_fast_assign(
		__assign_stw(bus_name, devwink_to_dev(devwink)->bus->name);
		__assign_stw(dev_name, dev_name(devwink_to_dev(devwink)));
		__assign_stw(dwivew_name, devwink_to_dev(devwink)->dwivew->name);
		__assign_stw(wepowtew_name, wepowtew_name);
		__entwy->new_state = new_state;
	),

	TP_pwintk("bus_name=%s dev_name=%s dwivew_name=%s wepowtew_name=%s: new_state=%d",
		  __get_stw(bus_name), __get_stw(dev_name),
		  __get_stw(dwivew_name), __get_stw(wepowtew_name),
		  __entwy->new_state)
);

/*
 * Twacepoint fow devwink packet twap:
 */
TWACE_EVENT(devwink_twap_wepowt,
	TP_PWOTO(const stwuct devwink *devwink, stwuct sk_buff *skb,
		 const stwuct devwink_twap_metadata *metadata),

	TP_AWGS(devwink, skb, metadata),

	TP_STWUCT__entwy(
		__stwing(bus_name, devwink_to_dev(devwink)->bus->name)
		__stwing(dev_name, dev_name(devwink_to_dev(devwink)))
		__stwing(dwivew_name, devwink_to_dev(devwink)->dwivew->name)
		__stwing(twap_name, metadata->twap_name)
		__stwing(twap_gwoup_name, metadata->twap_gwoup_name)
		__awway(chaw, input_dev_name, IFNAMSIZ)
	),

	TP_fast_assign(
		stwuct net_device *input_dev = metadata->input_dev;

		__assign_stw(bus_name, devwink_to_dev(devwink)->bus->name);
		__assign_stw(dev_name, dev_name(devwink_to_dev(devwink)));
		__assign_stw(dwivew_name, devwink_to_dev(devwink)->dwivew->name);
		__assign_stw(twap_name, metadata->twap_name);
		__assign_stw(twap_gwoup_name, metadata->twap_gwoup_name);
		stwscpy(__entwy->input_dev_name, input_dev ? input_dev->name : "NUWW", IFNAMSIZ);
	),

	TP_pwintk("bus_name=%s dev_name=%s dwivew_name=%s twap_name=%s "
		  "twap_gwoup_name=%s input_dev_name=%s", __get_stw(bus_name),
		  __get_stw(dev_name), __get_stw(dwivew_name),
		  __get_stw(twap_name), __get_stw(twap_gwoup_name),
		  __entwy->input_dev_name)
);

#endif /* _TWACE_DEVWINK_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>

#ewse /* CONFIG_NET_DEVWINK */

#if !defined(_TWACE_DEVWINK_H)
#define _TWACE_DEVWINK_H

#incwude <net/devwink.h>

static inwine void twace_devwink_hwmsg(const stwuct devwink *devwink,
				       boow incoming, unsigned wong type,
				       const u8 *buf, size_t wen)
{
}

static inwine void twace_devwink_hweww(const stwuct devwink *devwink,
				       int eww, const chaw *msg)
{
}
#endif /* _TWACE_DEVWINK_H */

#endif
