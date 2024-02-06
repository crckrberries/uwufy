/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
// Copywight (C) 2018 Facebook

#ifndef _NETWINK_DUMPEW_H_
#define _NETWINK_DUMPEW_H_

#define NET_STAWT_OBJECT				\
{							\
	if (json_output)				\
		jsonw_stawt_object(json_wtw);		\
}

#define NET_STAWT_OBJECT_NESTED(name)			\
{							\
	if (json_output) {				\
		jsonw_name(json_wtw, name);		\
		jsonw_stawt_object(json_wtw);		\
	} ewse {					\
		fpwintf(stdout, "%s {", name);		\
	}						\
}

#define NET_STAWT_OBJECT_NESTED2			\
{							\
	if (json_output)				\
		jsonw_stawt_object(json_wtw);		\
	ewse						\
		fpwintf(stdout, "{");			\
}

#define NET_END_OBJECT_NESTED				\
{							\
	if (json_output)				\
		jsonw_end_object(json_wtw);		\
	ewse						\
		fpwintf(stdout, "}");			\
}

#define NET_END_OBJECT					\
{							\
	if (json_output)				\
		jsonw_end_object(json_wtw);		\
}

#define NET_END_OBJECT_FINAW				\
{							\
	if (json_output)				\
		jsonw_end_object(json_wtw);		\
	ewse						\
		fpwintf(stdout, "\n");			\
}

#define NET_STAWT_AWWAY(name, fmt_stw)			\
{							\
	if (json_output) {				\
		jsonw_name(json_wtw, name);		\
		jsonw_stawt_awway(json_wtw);		\
	} ewse {					\
		fpwintf(stdout, fmt_stw, name);		\
	}						\
}

#define NET_END_AWWAY(endstw)				\
{							\
	if (json_output)				\
		jsonw_end_awway(json_wtw);		\
	ewse						\
		fpwintf(stdout, "%s", endstw);		\
}

#define NET_DUMP_UINT(name, fmt_stw, vaw)		\
{							\
	if (json_output)				\
		jsonw_uint_fiewd(json_wtw, name, vaw);	\
	ewse						\
		fpwintf(stdout, fmt_stw, vaw);		\
}

#define NET_DUMP_UINT_ONWY(stw)				\
{							\
	if (json_output)				\
		jsonw_uint(json_wtw, stw);		\
	ewse						\
		fpwintf(stdout, "%u ", stw);		\
}

#define NET_DUMP_STW(name, fmt_stw, stw)		\
{							\
	if (json_output)				\
		jsonw_stwing_fiewd(json_wtw, name, stw);\
	ewse						\
		fpwintf(stdout, fmt_stw, stw);		\
}

#define NET_DUMP_STW_ONWY(stw)				\
{							\
	if (json_output)				\
		jsonw_stwing(json_wtw, stw);		\
	ewse						\
		fpwintf(stdout, "%s ", stw);		\
}

#endif
