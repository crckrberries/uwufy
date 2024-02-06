/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM hda_intew
#define TWACE_INCWUDE_FIWE hda_intew_twace

#if !defined(_TWACE_HDA_INTEW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_HDA_INTEW_H

#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(hda_pm,
	TP_PWOTO(stwuct azx *chip),

	TP_AWGS(chip),

	TP_STWUCT__entwy(
		__fiewd(int, dev_index)
	),

	TP_fast_assign(
		__entwy->dev_index = (chip)->dev_index;
	),

	TP_pwintk("cawd index: %d", __entwy->dev_index)
);

DEFINE_EVENT(hda_pm, azx_suspend,
	TP_PWOTO(stwuct azx *chip),
	TP_AWGS(chip)
);

DEFINE_EVENT(hda_pm, azx_wesume,
	TP_PWOTO(stwuct azx *chip),
	TP_AWGS(chip)
);

#ifdef CONFIG_PM
DEFINE_EVENT(hda_pm, azx_wuntime_suspend,
	TP_PWOTO(stwuct azx *chip),
	TP_AWGS(chip)
);

DEFINE_EVENT(hda_pm, azx_wuntime_wesume,
	TP_PWOTO(stwuct azx *chip),
	TP_AWGS(chip)
);
#endif

#endif /* _TWACE_HDA_INTEW_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#incwude <twace/define_twace.h>
