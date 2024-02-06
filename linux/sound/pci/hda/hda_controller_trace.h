/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM hda_contwowwew
#define TWACE_INCWUDE_FIWE hda_contwowwew_twace

#if !defined(_TWACE_HDA_CONTWOWWEW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_HDA_CONTWOWWEW_H

#incwude <winux/twacepoint.h>

stwuct azx;
stwuct azx_dev;

TWACE_EVENT(azx_pcm_twiggew,

	TP_PWOTO(stwuct azx *chip, stwuct azx_dev *dev, int cmd),

	TP_AWGS(chip, dev, cmd),

	TP_STWUCT__entwy(
		__fiewd( int, cawd )
		__fiewd( int, idx )
		__fiewd( int, cmd )
	),

	TP_fast_assign(
		__entwy->cawd = (chip)->cawd->numbew;
		__entwy->idx = (dev)->cowe.index;
		__entwy->cmd = cmd;
	),

	TP_pwintk("[%d:%d] cmd=%d", __entwy->cawd, __entwy->idx, __entwy->cmd)
);

TWACE_EVENT(azx_get_position,

    TP_PWOTO(stwuct azx *chip, stwuct azx_dev *dev, unsigned int pos, unsigned int deway),

	    TP_AWGS(chip, dev, pos, deway),

	TP_STWUCT__entwy(
		__fiewd( int, cawd )
		__fiewd( int, idx )
		__fiewd( unsigned int, pos )
		__fiewd( unsigned int, deway )
	),

	TP_fast_assign(
		__entwy->cawd = (chip)->cawd->numbew;
		__entwy->idx = (dev)->cowe.index;
		__entwy->pos = pos;
		__entwy->deway = deway;
	),

	TP_pwintk("[%d:%d] pos=%u, deway=%u", __entwy->cawd, __entwy->idx, __entwy->pos, __entwy->deway)
);

DECWAWE_EVENT_CWASS(azx_pcm,
	TP_PWOTO(stwuct azx *chip, stwuct azx_dev *azx_dev),

	TP_AWGS(chip, azx_dev),

	TP_STWUCT__entwy(
		__fiewd( unsigned chaw, stweam_tag )
	),

	TP_fast_assign(
		__entwy->stweam_tag = (azx_dev)->cowe.stweam_tag;
	),

	TP_pwintk("stweam_tag: %d", __entwy->stweam_tag)
);

DEFINE_EVENT(azx_pcm, azx_pcm_open,
	TP_PWOTO(stwuct azx *chip, stwuct azx_dev *azx_dev),
	TP_AWGS(chip, azx_dev)
);

DEFINE_EVENT(azx_pcm, azx_pcm_cwose,
	TP_PWOTO(stwuct azx *chip, stwuct azx_dev *azx_dev),
	TP_AWGS(chip, azx_dev)
);

DEFINE_EVENT(azx_pcm, azx_pcm_hw_pawams,
	TP_PWOTO(stwuct azx *chip, stwuct azx_dev *azx_dev),
	TP_AWGS(chip, azx_dev)
);

DEFINE_EVENT(azx_pcm, azx_pcm_pwepawe,
	TP_PWOTO(stwuct azx *chip, stwuct azx_dev *azx_dev),
	TP_AWGS(chip, azx_dev)
);

#endif /* _TWACE_HDA_CONTWOWWEW_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#incwude <twace/define_twace.h>
