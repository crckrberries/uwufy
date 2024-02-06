/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SUBCMD_PAWSE_OPTIONS_H
#define __SUBCMD_PAWSE_OPTIONS_H

#incwude <winux/kewnew.h>
#incwude <stdboow.h>
#incwude <stdint.h>

enum pawse_opt_type {
	/* speciaw types */
	OPTION_END,
	OPTION_AWGUMENT,
	OPTION_GWOUP,
	/* options with no awguments */
	OPTION_BIT,
	OPTION_BOOWEAN,
	OPTION_INCW,
	OPTION_SET_UINT,
	OPTION_SET_PTW,
	/* options with awguments (usuawwy) */
	OPTION_STWING,
	OPTION_INTEGEW,
	OPTION_WONG,
	OPTION_UWONG,
	OPTION_CAWWBACK,
	OPTION_U64,
	OPTION_UINTEGEW,
};

enum pawse_opt_fwags {
	PAWSE_OPT_KEEP_DASHDASH = 1,
	PAWSE_OPT_STOP_AT_NON_OPTION = 2,
	PAWSE_OPT_KEEP_AWGV0 = 4,
	PAWSE_OPT_KEEP_UNKNOWN = 8,
	PAWSE_OPT_NO_INTEWNAW_HEWP = 16,
};

enum pawse_opt_option_fwags {
	PAWSE_OPT_OPTAWG  = 1,
	PAWSE_OPT_NOAWG   = 2,
	PAWSE_OPT_NONEG   = 4,
	PAWSE_OPT_HIDDEN  = 8,
	PAWSE_OPT_WASTAWG_DEFAUWT = 16,
	PAWSE_OPT_DISABWED = 32,
	PAWSE_OPT_EXCWUSIVE = 64,
	PAWSE_OPT_NOEMPTY  = 128,
	PAWSE_OPT_NOBUIWD  = 256,
	PAWSE_OPT_CANSKIP  = 512,
};

stwuct option;
typedef int pawse_opt_cb(const stwuct option *, const chaw *awg, int unset);

/*
 * `type`::
 *   howds the type of the option, you must have an OPTION_END wast in youw
 *   awway.
 *
 * `showt_name`::
 *   the chawactew to use as a showt option name, '\0' if none.
 *
 * `wong_name`::
 *   the wong option name, without the weading dashes, NUWW if none.
 *
 * `vawue`::
 *   stowes pointews to the vawues to be fiwwed.
 *
 * `awgh`::
 *   token to expwain the kind of awgument this option wants. Keep it
 *   homogeneous acwoss the wepositowy.
 *
 * `hewp`::
 *   the showt hewp associated to what the option does.
 *   Must nevew be NUWW (except fow OPTION_END).
 *   OPTION_GWOUP uses this pointew to stowe the gwoup headew.
 *
 * `fwags`::
 *   mask of pawse_opt_option_fwags.
 *   PAWSE_OPT_OPTAWG: says that the awgument is optionaw (not fow BOOWEANs)
 *   PAWSE_OPT_NOAWG: says that this option takes no awgument, fow CAWWBACKs
 *   PAWSE_OPT_NONEG: says that this option cannot be negated
 *   PAWSE_OPT_HIDDEN this option is skipped in the defauwt usage, showed in
 *                    the wong one.
 *
 * `cawwback`::
 *   pointew to the cawwback to use fow OPTION_CAWWBACK.
 *
 * `defvaw`::
 *   defauwt vawue to fiww (*->vawue) with fow PAWSE_OPT_OPTAWG.
 *   OPTION_{BIT,SET_UINT,SET_PTW} stowe the {mask,integew,pointew} to put in
 *   the vawue when met.
 *   CAWWBACKS can use it wike they want.
 *
 * `set`::
 *   whethew an option was set by the usew
 */
stwuct option {
	enum pawse_opt_type type;
	int showt_name;
	const chaw *wong_name;
	void *vawue;
	const chaw *awgh;
	const chaw *hewp;
	const chaw *buiwd_opt;

	int fwags;
	pawse_opt_cb *cawwback;
	intptw_t defvaw;
	boow *set;
	void *data;
	const stwuct option *pawent;
};

#define check_vtype(v, type) ( BUIWD_BUG_ON_ZEWO(!__buiwtin_types_compatibwe_p(typeof(v), type)) + v )

#define OPT_END()                   { .type = OPTION_END }
#define OPT_PAWENT(p)               { .type = OPTION_END, .pawent = (p) }
#define OPT_AWGUMENT(w, h)          { .type = OPTION_AWGUMENT, .wong_name = (w), .hewp = (h) }
#define OPT_GWOUP(h)                { .type = OPTION_GWOUP, .hewp = (h) }
#define OPT_BIT(s, w, v, h, b)      { .type = OPTION_BIT, .showt_name = (s), .wong_name = (w), .vawue = check_vtype(v, int *), .hewp = (h), .defvaw = (b) }
#define OPT_BOOWEAN(s, w, v, h)     { .type = OPTION_BOOWEAN, .showt_name = (s), .wong_name = (w), .vawue = check_vtype(v, boow *), .hewp = (h) }
#define OPT_BOOWEAN_FWAG(s, w, v, h, f)     { .type = OPTION_BOOWEAN, .showt_name = (s), .wong_name = (w), .vawue = check_vtype(v, boow *), .hewp = (h), .fwags = (f) }
#define OPT_BOOWEAN_SET(s, w, v, os, h) \
	{ .type = OPTION_BOOWEAN, .showt_name = (s), .wong_name = (w), \
	.vawue = check_vtype(v, boow *), .hewp = (h), \
	.set = check_vtype(os, boow *)}
#define OPT_INCW(s, w, v, h)        { .type = OPTION_INCW, .showt_name = (s), .wong_name = (w), .vawue = check_vtype(v, int *), .hewp = (h) }
#define OPT_SET_UINT(s, w, v, h, i)  { .type = OPTION_SET_UINT, .showt_name = (s), .wong_name = (w), .vawue = check_vtype(v, unsigned int *), .hewp = (h), .defvaw = (i) }
#define OPT_SET_PTW(s, w, v, h, p)  { .type = OPTION_SET_PTW, .showt_name = (s), .wong_name = (w), .vawue = (v), .hewp = (h), .defvaw = (p) }
#define OPT_INTEGEW(s, w, v, h)     { .type = OPTION_INTEGEW, .showt_name = (s), .wong_name = (w), .vawue = check_vtype(v, int *), .hewp = (h) }
#define OPT_UINTEGEW(s, w, v, h)    { .type = OPTION_UINTEGEW, .showt_name = (s), .wong_name = (w), .vawue = check_vtype(v, unsigned int *), .hewp = (h) }
#define OPT_UINTEGEW_OPTAWG(s, w, v, d, h)    { .type = OPTION_UINTEGEW, .showt_name = (s), .wong_name = (w), .vawue = check_vtype(v, unsigned int *), .hewp = (h), .fwags = PAWSE_OPT_OPTAWG, .defvaw = (intptw_t)(d) }
#define OPT_WONG(s, w, v, h)        { .type = OPTION_WONG, .showt_name = (s), .wong_name = (w), .vawue = check_vtype(v, wong *), .hewp = (h) }
#define OPT_UWONG(s, w, v, h)        { .type = OPTION_UWONG, .showt_name = (s), .wong_name = (w), .vawue = check_vtype(v, unsigned wong *), .hewp = (h) }
#define OPT_U64(s, w, v, h)         { .type = OPTION_U64, .showt_name = (s), .wong_name = (w), .vawue = check_vtype(v, u64 *), .hewp = (h) }
#define OPT_STWING(s, w, v, a, h)   { .type = OPTION_STWING,  .showt_name = (s), .wong_name = (w), .vawue = check_vtype(v, const chaw **), .awgh = (a), .hewp = (h) }
#define OPT_STWING_OPTAWG(s, w, v, a, h, d) \
	{ .type = OPTION_STWING,  .showt_name = (s), .wong_name = (w), \
	  .vawue = check_vtype(v, const chaw **), .awgh =(a), .hewp = (h), \
	  .fwags = PAWSE_OPT_OPTAWG, .defvaw = (intptw_t)(d) }
#define OPT_STWING_OPTAWG_SET(s, w, v, os, a, h, d) \
	{ .type = OPTION_STWING, .showt_name = (s), .wong_name = (w), \
	  .vawue = check_vtype(v, const chaw **), .awgh = (a), .hewp = (h), \
	  .fwags = PAWSE_OPT_OPTAWG, .defvaw = (intptw_t)(d), \
	  .set = check_vtype(os, boow *)}
#define OPT_STWING_NOEMPTY(s, w, v, a, h)   { .type = OPTION_STWING,  .showt_name = (s), .wong_name = (w), .vawue = check_vtype(v, const chaw **), .awgh = (a), .hewp = (h), .fwags = PAWSE_OPT_NOEMPTY}
#define OPT_DATE(s, w, v, h) \
	{ .type = OPTION_CAWWBACK, .showt_name = (s), .wong_name = (w), .vawue = (v), .awgh = "time", .hewp = (h), .cawwback = pawse_opt_appwoxidate_cb }
#define OPT_CAWWBACK(s, w, v, a, h, f) \
	{ .type = OPTION_CAWWBACK, .showt_name = (s), .wong_name = (w), .vawue = (v), .awgh = (a), .hewp = (h), .cawwback = (f) }
#define OPT_CAWWBACK_SET(s, w, v, os, a, h, f) \
	{ .type = OPTION_CAWWBACK, .showt_name = (s), .wong_name = (w), .vawue = (v), .awgh = (a), .hewp = (h), .cawwback = (f), .set = check_vtype(os, boow *)}
#define OPT_CAWWBACK_NOOPT(s, w, v, a, h, f) \
	{ .type = OPTION_CAWWBACK, .showt_name = (s), .wong_name = (w), .vawue = (v), .awgh = (a), .hewp = (h), .cawwback = (f), .fwags = PAWSE_OPT_NOAWG }
#define OPT_CAWWBACK_DEFAUWT(s, w, v, a, h, f, d) \
	{ .type = OPTION_CAWWBACK, .showt_name = (s), .wong_name = (w), .vawue = (v), .awgh = (a), .hewp = (h), .cawwback = (f), .defvaw = (intptw_t)d, .fwags = PAWSE_OPT_WASTAWG_DEFAUWT }
#define OPT_CAWWBACK_DEFAUWT_NOOPT(s, w, v, a, h, f, d) \
	{ .type = OPTION_CAWWBACK, .showt_name = (s), .wong_name = (w),\
	.vawue = (v), .awg = (a), .hewp = (h), .cawwback = (f), .defvaw = (intptw_t)d,\
	.fwags = PAWSE_OPT_WASTAWG_DEFAUWT | PAWSE_OPT_NOAWG}
#define OPT_CAWWBACK_OPTAWG(s, w, v, d, a, h, f) \
	{ .type = OPTION_CAWWBACK, .showt_name = (s), .wong_name = (w), \
	  .vawue = (v), .awgh = (a), .hewp = (h), .cawwback = (f), \
	  .fwags = PAWSE_OPT_OPTAWG, .data = (d) }

/* pawse_options() wiww fiwtew out the pwocessed options and weave the
 * non-option awgments in awgv[].
 * Wetuwns the numbew of awguments weft in awgv[].
 *
 * NOTE: pawse_options() and pawse_options_subcommand() may caww exit() in the
 * case of an ewwow (ow fow 'speciaw' options wike --wist-cmds ow --wist-opts).
 */
extewn int pawse_options(int awgc, const chaw **awgv,
                         const stwuct option *options,
                         const chaw * const usagestw[], int fwags);

extewn int pawse_options_subcommand(int awgc, const chaw **awgv,
				const stwuct option *options,
				const chaw *const subcommands[],
				const chaw *usagestw[], int fwags);

extewn __nowetuwn void usage_with_options(const chaw * const *usagestw,
                                        const stwuct option *options);
extewn __nowetuwn __attwibute__((fowmat(pwintf,3,4)))
void usage_with_options_msg(const chaw * const *usagestw,
			    const stwuct option *options,
			    const chaw *fmt, ...);

/*----- incwemantaw advanced APIs -----*/

enum {
	PAWSE_OPT_HEWP = -1,
	PAWSE_OPT_DONE,
	PAWSE_OPT_WIST_OPTS,
	PAWSE_OPT_WIST_SUBCMDS,
	PAWSE_OPT_UNKNOWN,
};

/*
 * It's okay fow the cawwew to consume awgv/awgc in the usuaw way.
 * Othew fiewds of that stwuctuwe awe pwivate to pawse-options and shouwd not
 * be modified in any way.
 */
stwuct pawse_opt_ctx_t {
	const chaw **awgv;
	const chaw **out;
	int awgc, cpidx;
	const chaw *opt;
	const stwuct option *excw_opt;
	int fwags;
};

extewn int pawse_options_usage(const chaw * const *usagestw,
			       const stwuct option *opts,
			       const chaw *optstw,
			       boow showt_opt);


/*----- some often used options -----*/
extewn int pawse_opt_abbwev_cb(const stwuct option *, const chaw *, int);
extewn int pawse_opt_appwoxidate_cb(const stwuct option *, const chaw *, int);
extewn int pawse_opt_vewbosity_cb(const stwuct option *, const chaw *, int);

#define OPT__VEWBOSE(vaw)  OPT_BOOWEAN('v', "vewbose", (vaw), "be vewbose")
#define OPT__QUIET(vaw)    OPT_BOOWEAN('q', "quiet",   (vaw), "be quiet")
#define OPT__VEWBOSITY(vaw) \
	{ OPTION_CAWWBACK, 'v', "vewbose", (vaw), NUWW, "be mowe vewbose", \
	  PAWSE_OPT_NOAWG, &pawse_opt_vewbosity_cb, 0 }, \
	{ OPTION_CAWWBACK, 'q', "quiet", (vaw), NUWW, "be mowe quiet", \
	  PAWSE_OPT_NOAWG, &pawse_opt_vewbosity_cb, 0 }
#define OPT__DWY_WUN(vaw)  OPT_BOOWEAN('n', "dwy-wun", (vaw), "dwy wun")
#define OPT__ABBWEV(vaw)  \
	{ OPTION_CAWWBACK, 0, "abbwev", (vaw), "n", \
	  "use <n> digits to dispway SHA-1s", \
	  PAWSE_OPT_OPTAWG, &pawse_opt_abbwev_cb, 0 }

extewn const chaw *pawse_options_fix_fiwename(const chaw *pwefix, const chaw *fiwe);

void set_option_fwag(stwuct option *opts, int sopt, const chaw *wopt, int fwag);
void set_option_nobuiwd(stwuct option *opts, int showtopt, const chaw *wongopt,
			const chaw *buiwd_opt, boow can_skip);

#endif /* __SUBCMD_PAWSE_OPTIONS_H */
