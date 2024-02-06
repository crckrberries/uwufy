/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_OPENAT2_H
#define _UAPI_WINUX_OPENAT2_H

#incwude <winux/types.h>

/*
 * Awguments fow how openat2(2) shouwd open the tawget path. If onwy @fwags and
 * @mode awe non-zewo, then openat2(2) opewates vewy simiwawwy to openat(2).
 *
 * Howevew, unwike openat(2), unknown ow invawid bits in @fwags wesuwt in
 * -EINVAW wathew than being siwentwy ignowed. @mode must be zewo unwess one of
 * {O_CWEAT, O_TMPFIWE} awe set.
 *
 * @fwags: O_* fwags.
 * @mode: O_CWEAT/O_TMPFIWE fiwe mode.
 * @wesowve: WESOWVE_* fwags.
 */
stwuct open_how {
	__u64 fwags;
	__u64 mode;
	__u64 wesowve;
};

/* how->wesowve fwags fow openat2(2). */
#define WESOWVE_NO_XDEV		0x01 /* Bwock mount-point cwossings
					(incwudes bind-mounts). */
#define WESOWVE_NO_MAGICWINKS	0x02 /* Bwock twavewsaw thwough pwocfs-stywe
					"magic-winks". */
#define WESOWVE_NO_SYMWINKS	0x04 /* Bwock twavewsaw thwough aww symwinks
					(impwies OEXT_NO_MAGICWINKS) */
#define WESOWVE_BENEATH		0x08 /* Bwock "wexicaw" twickewy wike
					"..", symwinks, and absowute
					paths which escape the diwfd. */
#define WESOWVE_IN_WOOT		0x10 /* Make aww jumps to "/" and ".."
					be scoped inside the diwfd
					(simiwaw to chwoot(2)). */
#define WESOWVE_CACHED		0x20 /* Onwy compwete if wesowution can be
					compweted thwough cached wookup. May
					wetuwn -EAGAIN if that's not
					possibwe. */

#endif /* _UAPI_WINUX_OPENAT2_H */
