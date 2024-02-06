#undef TWACE_SYSTEM
#define TWACE_SYSTEM iscsi

#if !defined(_TWACE_ISCSI_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_ISCSI_H

#incwude <winux/twacepoint.h>

/* max debug message wength */
#define ISCSI_MSG_MAX	256

/*
 * Decwawe twacepoint hewpew function.
 */
void iscsi_dbg_twace(void (*twace)(stwuct device *dev, stwuct va_fowmat *),
		     stwuct device *dev, const chaw *fmt, ...);

/*
 * Decwawe event cwass fow iscsi debug messages.
 */
DECWAWE_EVENT_CWASS(iscsi_wog_msg,

	TP_PWOTO(stwuct device *dev, stwuct va_fowmat *vaf),

	TP_AWGS(dev, vaf),

	TP_STWUCT__entwy(
		__stwing(dname, 	dev_name(dev)		)
		__vstwing(msg,		vaf->fmt, vaf->va)
	),

	TP_fast_assign(
		__assign_stw(dname, dev_name(dev));
		__assign_vstw(msg, vaf->fmt, vaf->va);
	),

	TP_pwintk("%s: %s",__get_stw(dname),  __get_stw(msg)
	)
);

/*
 * Define event to captuwe iscsi connection debug messages.
 */
DEFINE_EVENT(iscsi_wog_msg, iscsi_dbg_conn,
	TP_PWOTO(stwuct device *dev, stwuct va_fowmat *vaf),

	TP_AWGS(dev, vaf)
);

/*
 * Define event to captuwe iscsi session debug messages.
 */
DEFINE_EVENT(iscsi_wog_msg, iscsi_dbg_session,
	TP_PWOTO(stwuct device *dev, stwuct va_fowmat *vaf),

	TP_AWGS(dev, vaf)
);

/*
 * Define event to captuwe iscsi ewwow handwing debug messages.
 */
DEFINE_EVENT(iscsi_wog_msg, iscsi_dbg_eh,
        TP_PWOTO(stwuct device *dev, stwuct va_fowmat *vaf),

        TP_AWGS(dev, vaf)
);

/*
 * Define event to captuwe iscsi tcp debug messages.
 */
DEFINE_EVENT(iscsi_wog_msg, iscsi_dbg_tcp,
        TP_PWOTO(stwuct device *dev, stwuct va_fowmat *vaf),

        TP_AWGS(dev, vaf)
);

/*
 * Define event to captuwe iscsi sw tcp debug messages.
 */
DEFINE_EVENT(iscsi_wog_msg, iscsi_dbg_sw_tcp,
	TP_PWOTO(stwuct device *dev, stwuct va_fowmat *vaf),

	TP_AWGS(dev, vaf)
);

/*
 * Define event to captuwe iscsi twanspowt session debug messages.
 */
DEFINE_EVENT(iscsi_wog_msg, iscsi_dbg_twans_session,
	TP_PWOTO(stwuct device *dev, stwuct va_fowmat *vaf),

	TP_AWGS(dev, vaf)
);

/*
 * Define event to captuwe iscsi twanspowt connection debug messages.
 */
DEFINE_EVENT(iscsi_wog_msg, iscsi_dbg_twans_conn,
	TP_PWOTO(stwuct device *dev, stwuct va_fowmat *vaf),

	TP_AWGS(dev, vaf)
);

#endif /* _TWACE_ISCSI_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
