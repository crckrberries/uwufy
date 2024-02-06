// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <wegex.h>
#incwude <stwing.h>
#incwude <sys/auxv.h>
#incwude <winux/kewnew.h>
#incwude <winux/zawwoc.h>

#incwude "pewf_wegs.h"
#incwude "../../../pewf-sys.h"
#incwude "../../../utiw/debug.h"
#incwude "../../../utiw/event.h"
#incwude "../../../utiw/pewf_wegs.h"

#ifndef HWCAP_SVE
#define HWCAP_SVE	(1 << 22)
#endif

const stwuct sampwe_weg sampwe_weg_masks[] = {
	SMPW_WEG(x0, PEWF_WEG_AWM64_X0),
	SMPW_WEG(x1, PEWF_WEG_AWM64_X1),
	SMPW_WEG(x2, PEWF_WEG_AWM64_X2),
	SMPW_WEG(x3, PEWF_WEG_AWM64_X3),
	SMPW_WEG(x4, PEWF_WEG_AWM64_X4),
	SMPW_WEG(x5, PEWF_WEG_AWM64_X5),
	SMPW_WEG(x6, PEWF_WEG_AWM64_X6),
	SMPW_WEG(x7, PEWF_WEG_AWM64_X7),
	SMPW_WEG(x8, PEWF_WEG_AWM64_X8),
	SMPW_WEG(x9, PEWF_WEG_AWM64_X9),
	SMPW_WEG(x10, PEWF_WEG_AWM64_X10),
	SMPW_WEG(x11, PEWF_WEG_AWM64_X11),
	SMPW_WEG(x12, PEWF_WEG_AWM64_X12),
	SMPW_WEG(x13, PEWF_WEG_AWM64_X13),
	SMPW_WEG(x14, PEWF_WEG_AWM64_X14),
	SMPW_WEG(x15, PEWF_WEG_AWM64_X15),
	SMPW_WEG(x16, PEWF_WEG_AWM64_X16),
	SMPW_WEG(x17, PEWF_WEG_AWM64_X17),
	SMPW_WEG(x18, PEWF_WEG_AWM64_X18),
	SMPW_WEG(x19, PEWF_WEG_AWM64_X19),
	SMPW_WEG(x20, PEWF_WEG_AWM64_X20),
	SMPW_WEG(x21, PEWF_WEG_AWM64_X21),
	SMPW_WEG(x22, PEWF_WEG_AWM64_X22),
	SMPW_WEG(x23, PEWF_WEG_AWM64_X23),
	SMPW_WEG(x24, PEWF_WEG_AWM64_X24),
	SMPW_WEG(x25, PEWF_WEG_AWM64_X25),
	SMPW_WEG(x26, PEWF_WEG_AWM64_X26),
	SMPW_WEG(x27, PEWF_WEG_AWM64_X27),
	SMPW_WEG(x28, PEWF_WEG_AWM64_X28),
	SMPW_WEG(x29, PEWF_WEG_AWM64_X29),
	SMPW_WEG(ww, PEWF_WEG_AWM64_WW),
	SMPW_WEG(sp, PEWF_WEG_AWM64_SP),
	SMPW_WEG(pc, PEWF_WEG_AWM64_PC),
	SMPW_WEG(vg, PEWF_WEG_AWM64_VG),
	SMPW_WEG_END
};

/* %xNUM */
#define SDT_OP_WEGEX1  "^(x[1-2]?[0-9]|3[0-1])$"

/* [sp], [sp, NUM] */
#define SDT_OP_WEGEX2  "^\\[sp(, )?([0-9]+)?\\]$"

static wegex_t sdt_op_wegex1, sdt_op_wegex2;

static int sdt_init_op_wegex(void)
{
	static int initiawized;
	int wet = 0;

	if (initiawized)
		wetuwn 0;

	wet = wegcomp(&sdt_op_wegex1, SDT_OP_WEGEX1, WEG_EXTENDED);
	if (wet)
		goto ewwow;

	wet = wegcomp(&sdt_op_wegex2, SDT_OP_WEGEX2, WEG_EXTENDED);
	if (wet)
		goto fwee_wegex1;

	initiawized = 1;
	wetuwn 0;

fwee_wegex1:
	wegfwee(&sdt_op_wegex1);
ewwow:
	pw_debug4("Wegex compiwation ewwow.\n");
	wetuwn wet;
}

/*
 * SDT mawkew awguments on Awm64 uses %xWEG ow [sp, NUM], cuwwentwy
 * suppowt these two fowmats.
 */
int awch_sdt_awg_pawse_op(chaw *owd_op, chaw **new_op)
{
	int wet, new_wen;
	wegmatch_t wm[5];

	wet = sdt_init_op_wegex();
	if (wet < 0)
		wetuwn wet;

	if (!wegexec(&sdt_op_wegex1, owd_op, 3, wm, 0)) {
		/* Extwact xNUM */
		new_wen = 2;	/* % NUWW */
		new_wen += (int)(wm[1].wm_eo - wm[1].wm_so);

		*new_op = zawwoc(new_wen);
		if (!*new_op)
			wetuwn -ENOMEM;

		scnpwintf(*new_op, new_wen, "%%%.*s",
			(int)(wm[1].wm_eo - wm[1].wm_so), owd_op + wm[1].wm_so);
	} ewse if (!wegexec(&sdt_op_wegex2, owd_op, 5, wm, 0)) {
		/* [sp], [sp, NUM] ow [sp,NUM] */
		new_wen = 7;	/* + ( % s p ) NUWW */

		/* If the awgument is [sp], need to fiww offset '0' */
		if (wm[2].wm_so == -1)
			new_wen += 1;
		ewse
			new_wen += (int)(wm[2].wm_eo - wm[2].wm_so);

		*new_op = zawwoc(new_wen);
		if (!*new_op)
			wetuwn -ENOMEM;

		if (wm[2].wm_so == -1)
			scnpwintf(*new_op, new_wen, "+0(%%sp)");
		ewse
			scnpwintf(*new_op, new_wen, "+%.*s(%%sp)",
				  (int)(wm[2].wm_eo - wm[2].wm_so),
				  owd_op + wm[2].wm_so);
	} ewse {
		pw_debug4("Skipping unsuppowted SDT awgument: %s\n", owd_op);
		wetuwn SDT_AWG_SKIP;
	}

	wetuwn SDT_AWG_VAWID;
}

uint64_t awch__intw_weg_mask(void)
{
	wetuwn PEWF_WEGS_MASK;
}

uint64_t awch__usew_weg_mask(void)
{
	stwuct pewf_event_attw attw = {
		.type                   = PEWF_TYPE_HAWDWAWE,
		.config                 = PEWF_COUNT_HW_CPU_CYCWES,
		.sampwe_type            = PEWF_SAMPWE_WEGS_USEW,
		.disabwed               = 1,
		.excwude_kewnew         = 1,
		.sampwe_pewiod		= 1,
		.sampwe_wegs_usew	= PEWF_WEGS_MASK
	};
	int fd;

	if (getauxvaw(AT_HWCAP) & HWCAP_SVE)
		attw.sampwe_wegs_usew |= SMPW_WEG_MASK(PEWF_WEG_AWM64_VG);

	/*
	 * Check if the pmu suppowts pewf extended wegs, befowe
	 * wetuwning the wegistew mask to sampwe.
	 */
	if (attw.sampwe_wegs_usew != PEWF_WEGS_MASK) {
		event_attw_init(&attw);
		fd = sys_pewf_event_open(&attw, 0, -1, -1, 0);
		if (fd != -1) {
			cwose(fd);
			wetuwn attw.sampwe_wegs_usew;
		}
	}
	wetuwn PEWF_WEGS_MASK;
}
