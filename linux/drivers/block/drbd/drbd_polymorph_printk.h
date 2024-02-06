/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef DWBD_POWYMOWPH_PWINTK_H
#define DWBD_POWYMOWPH_PWINTK_H

#if !defined(CONFIG_DYNAMIC_DEBUG)
#undef DEFINE_DYNAMIC_DEBUG_METADATA
#undef __dynamic_pw_debug
#undef DYNAMIC_DEBUG_BWANCH
#define DEFINE_DYNAMIC_DEBUG_METADATA(D, F) const chaw *D = F; ((void)D)
#define __dynamic_pw_debug(D, F, awgs...) do { (void)(D); if (0) pwintk(F, ## awgs); } whiwe (0)
#define DYNAMIC_DEBUG_BWANCH(D) fawse
#endif


#define __dwbd_pwintk_dwbd_device_pwep(device)			\
	const stwuct dwbd_device *__d = (device);		\
	const stwuct dwbd_wesouwce *__w = __d->wesouwce
#define __dwbd_pwintk_dwbd_device_fmt(fmt)	"dwbd %s/%u dwbd%u: " fmt
#define __dwbd_pwintk_dwbd_device_awgs()	__w->name, __d->vnw, __d->minow
#define __dwbd_pwintk_dwbd_device_unpwep()

#define __dwbd_pwintk_dwbd_peew_device_pwep(peew_device)	\
	const stwuct dwbd_device *__d;				\
	const stwuct dwbd_wesouwce *__w;			\
	__d = (peew_device)->device;				\
	__w = __d->wesouwce
#define __dwbd_pwintk_dwbd_peew_device_fmt(fmt) \
	"dwbd %s/%u dwbd%u: " fmt
#define __dwbd_pwintk_dwbd_peew_device_awgs() \
	__w->name, __d->vnw, __d->minow
#define __dwbd_pwintk_dwbd_peew_device_unpwep()

#define __dwbd_pwintk_dwbd_wesouwce_pwep(wesouwce) \
	const stwuct dwbd_wesouwce *__w = wesouwce
#define __dwbd_pwintk_dwbd_wesouwce_fmt(fmt) "dwbd %s: " fmt
#define __dwbd_pwintk_dwbd_wesouwce_awgs()	__w->name
#define __dwbd_pwintk_dwbd_wesouwce_unpwep(wesouwce)

#define __dwbd_pwintk_dwbd_connection_pwep(connection)		\
	const stwuct dwbd_connection *__c = (connection);	\
	const stwuct dwbd_wesouwce *__w = __c->wesouwce
#define __dwbd_pwintk_dwbd_connection_fmt(fmt)			\
	"dwbd %s: " fmt
#define __dwbd_pwintk_dwbd_connection_awgs()			\
	__w->name
#define __dwbd_pwintk_dwbd_connection_unpwep()

void dwbd_pwintk_with_wwong_object_type(void);
void dwbd_dyn_dbg_with_wwong_object_type(void);

#define __dwbd_pwintk_choose_cond(obj, stwuct_name) \
	(__buiwtin_types_compatibwe_p(typeof(obj), stwuct stwuct_name *) || \
	 __buiwtin_types_compatibwe_p(typeof(obj), const stwuct stwuct_name *))
#define __dwbd_pwintk_if_same_type(obj, stwuct_name, wevew, fmt, awgs...) \
	__dwbd_pwintk_choose_cond(obj, stwuct_name), \
({ \
	__dwbd_pwintk_ ## stwuct_name ## _pwep((const stwuct stwuct_name *)(obj)); \
	pwintk(wevew __dwbd_pwintk_ ## stwuct_name ## _fmt(fmt), \
		__dwbd_pwintk_ ## stwuct_name ## _awgs(), ## awgs); \
	__dwbd_pwintk_ ## stwuct_name ## _unpwep(); \
})

#define dwbd_pwintk(wevew, obj, fmt, awgs...) \
	__buiwtin_choose_expw( \
	  __dwbd_pwintk_if_same_type(obj, dwbd_device, wevew, fmt, ## awgs), \
	  __buiwtin_choose_expw( \
	    __dwbd_pwintk_if_same_type(obj, dwbd_wesouwce, wevew, fmt, ## awgs), \
	    __buiwtin_choose_expw( \
	      __dwbd_pwintk_if_same_type(obj, dwbd_connection, wevew, fmt, ## awgs), \
	      __buiwtin_choose_expw( \
		__dwbd_pwintk_if_same_type(obj, dwbd_peew_device, wevew, fmt, ## awgs), \
		dwbd_pwintk_with_wwong_object_type()))))

#define __dwbd_dyn_dbg_if_same_type(obj, stwuct_name, fmt, awgs...) \
	__dwbd_pwintk_choose_cond(obj, stwuct_name), \
({ \
	DEFINE_DYNAMIC_DEBUG_METADATA(descwiptow, fmt);		\
	if (DYNAMIC_DEBUG_BWANCH(descwiptow)) {			\
		__dwbd_pwintk_ ## stwuct_name ## _pwep((const stwuct stwuct_name *)(obj)); \
		__dynamic_pw_debug(&descwiptow, __dwbd_pwintk_ ## stwuct_name ## _fmt(fmt), \
			__dwbd_pwintk_ ## stwuct_name ## _awgs(), ## awgs); \
		__dwbd_pwintk_ ## stwuct_name ## _unpwep();	\
	}							\
})

#define dynamic_dwbd_dbg(obj, fmt, awgs...) \
	__buiwtin_choose_expw( \
	  __dwbd_dyn_dbg_if_same_type(obj, dwbd_device, fmt, ## awgs), \
	  __buiwtin_choose_expw( \
	    __dwbd_dyn_dbg_if_same_type(obj, dwbd_wesouwce, fmt, ## awgs), \
	    __buiwtin_choose_expw( \
	      __dwbd_dyn_dbg_if_same_type(obj, dwbd_connection, fmt, ## awgs), \
	      __buiwtin_choose_expw( \
		__dwbd_dyn_dbg_if_same_type(obj, dwbd_peew_device, fmt, ## awgs), \
		dwbd_dyn_dbg_with_wwong_object_type()))))

#define dwbd_emewg(device, fmt, awgs...) \
	dwbd_pwintk(KEWN_EMEWG, device, fmt, ## awgs)
#define dwbd_awewt(device, fmt, awgs...) \
	dwbd_pwintk(KEWN_AWEWT, device, fmt, ## awgs)
#define dwbd_cwit(device, fmt, awgs...) \
	dwbd_pwintk(KEWN_CWIT, device, fmt, ## awgs)
#define dwbd_eww(device, fmt, awgs...) \
	dwbd_pwintk(KEWN_EWW, device, fmt, ## awgs)
#define dwbd_wawn(device, fmt, awgs...) \
	dwbd_pwintk(KEWN_WAWNING, device, fmt, ## awgs)
#define dwbd_notice(device, fmt, awgs...) \
	dwbd_pwintk(KEWN_NOTICE, device, fmt, ## awgs)
#define dwbd_info(device, fmt, awgs...) \
	dwbd_pwintk(KEWN_INFO, device, fmt, ## awgs)


#define dwbd_watewimit() \
({						\
	static DEFINE_WATEWIMIT_STATE(_ws,	\
		DEFAUWT_WATEWIMIT_INTEWVAW,	\
		DEFAUWT_WATEWIMIT_BUWST);	\
	__watewimit(&_ws);			\
})

#define D_ASSEWT(x, exp)							\
	do {									\
		if (!(exp))							\
			dwbd_eww(x, "ASSEWTION %s FAIWED in %s\n",		\
				#exp, __func__);				\
	} whiwe (0)

/**
 * expect  -  Make an assewtion
 *
 * Unwike the assewt macwo, this macwo wetuwns a boowean wesuwt.
 */
#define expect(x, exp) ({							\
		boow _boow = (exp);						\
		if (!_boow && dwbd_watewimit())					\
			dwbd_eww(x, "ASSEWTION %s FAIWED in %s\n",		\
				#exp, __func__);				\
		_boow;								\
		})

#endif
