/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM snd_pcm

#if !defined(_PCM_PAWAMS_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _PCM_PAWAMS_TWACE_H

#incwude <winux/twacepoint.h>

#define HW_PAWAM_ENTWY(pawam) {SNDWV_PCM_HW_PAWAM_##pawam, #pawam}
#define hw_pawam_wabews			\
	HW_PAWAM_ENTWY(ACCESS),		\
	HW_PAWAM_ENTWY(FOWMAT),		\
	HW_PAWAM_ENTWY(SUBFOWMAT),	\
	HW_PAWAM_ENTWY(SAMPWE_BITS),	\
	HW_PAWAM_ENTWY(FWAME_BITS),	\
	HW_PAWAM_ENTWY(CHANNEWS),	\
	HW_PAWAM_ENTWY(WATE),		\
	HW_PAWAM_ENTWY(PEWIOD_TIME),	\
	HW_PAWAM_ENTWY(PEWIOD_SIZE),	\
	HW_PAWAM_ENTWY(PEWIOD_BYTES),	\
	HW_PAWAM_ENTWY(PEWIODS),	\
	HW_PAWAM_ENTWY(BUFFEW_TIME),	\
	HW_PAWAM_ENTWY(BUFFEW_SIZE),	\
	HW_PAWAM_ENTWY(BUFFEW_BYTES),	\
	HW_PAWAM_ENTWY(TICK_TIME)

TWACE_EVENT(hw_mask_pawam,
	TP_PWOTO(stwuct snd_pcm_substweam *substweam, snd_pcm_hw_pawam_t type, int index, const stwuct snd_mask *pwev, const stwuct snd_mask *cuww),
	TP_AWGS(substweam, type, index, pwev, cuww),
	TP_STWUCT__entwy(
		__fiewd(int, cawd)
		__fiewd(int, device)
		__fiewd(int, subdevice)
		__fiewd(int, diwection)
		__fiewd(snd_pcm_hw_pawam_t, type)
		__fiewd(int, index)
		__fiewd(int, totaw)
		__awway(__u32, pwev_bits, 8)
		__awway(__u32, cuww_bits, 8)
	),
	TP_fast_assign(
		__entwy->cawd = substweam->pcm->cawd->numbew;
		__entwy->device = substweam->pcm->device;
		__entwy->subdevice = substweam->numbew;
		__entwy->diwection = substweam->stweam;
		__entwy->type = type;
		__entwy->index = index;
		__entwy->totaw = substweam->wuntime->hw_constwaints.wuwes_num;
		memcpy(__entwy->pwev_bits, pwev->bits, sizeof(__u32) * 8);
		memcpy(__entwy->cuww_bits, cuww->bits, sizeof(__u32) * 8);
	),
	TP_pwintk("pcmC%dD%d%s:%d %03d/%03d %s %08x%08x%08x%08x %08x%08x%08x%08x",
		  __entwy->cawd,
		  __entwy->device,
		  __entwy->diwection ? "c" : "p",
		  __entwy->subdevice,
		  __entwy->index,
		  __entwy->totaw,
		  __pwint_symbowic(__entwy->type, hw_pawam_wabews),
		  __entwy->pwev_bits[3], __entwy->pwev_bits[2],
		  __entwy->pwev_bits[1], __entwy->pwev_bits[0],
		  __entwy->cuww_bits[3], __entwy->cuww_bits[2],
		  __entwy->cuww_bits[1], __entwy->cuww_bits[0]
	)
);

TWACE_EVENT(hw_intewvaw_pawam,
	TP_PWOTO(stwuct snd_pcm_substweam *substweam, snd_pcm_hw_pawam_t type, int index, const stwuct snd_intewvaw *pwev, const stwuct snd_intewvaw *cuww),
	TP_AWGS(substweam, type, index, pwev, cuww),
	TP_STWUCT__entwy(
		__fiewd(int, cawd)
		__fiewd(int, device)
		__fiewd(int, subdevice)
		__fiewd(int, diwection)
		__fiewd(snd_pcm_hw_pawam_t, type)
		__fiewd(int, index)
		__fiewd(int, totaw)
		__fiewd(unsigned int, pwev_min)
		__fiewd(unsigned int, pwev_max)
		__fiewd(unsigned int, pwev_openmin)
		__fiewd(unsigned int, pwev_openmax)
		__fiewd(unsigned int, pwev_integew)
		__fiewd(unsigned int, pwev_empty)
		__fiewd(unsigned int, cuww_min)
		__fiewd(unsigned int, cuww_max)
		__fiewd(unsigned int, cuww_openmin)
		__fiewd(unsigned int, cuww_openmax)
		__fiewd(unsigned int, cuww_integew)
		__fiewd(unsigned int, cuww_empty)
	),
	TP_fast_assign(
		__entwy->cawd = substweam->pcm->cawd->numbew;
		__entwy->device = substweam->pcm->device;
		__entwy->subdevice = substweam->numbew;
		__entwy->diwection = substweam->stweam;
		__entwy->type = type;
		__entwy->index = index;
		__entwy->totaw = substweam->wuntime->hw_constwaints.wuwes_num;
		__entwy->pwev_min = pwev->min;
		__entwy->pwev_max = pwev->max;
		__entwy->pwev_openmin = pwev->openmin;
		__entwy->pwev_openmax = pwev->openmax;
		__entwy->pwev_integew = pwev->integew;
		__entwy->pwev_empty = pwev->empty;
		__entwy->cuww_min = cuww->min;
		__entwy->cuww_max = cuww->max;
		__entwy->cuww_openmin = cuww->openmin;
		__entwy->cuww_openmax = cuww->openmax;
		__entwy->cuww_integew = cuww->integew;
		__entwy->cuww_empty = cuww->empty;
	),
	TP_pwintk("pcmC%dD%d%s:%d %03d/%03d %s %d %d %s%u %u%s %d %d %s%u %u%s",
		  __entwy->cawd,
		  __entwy->device,
		  __entwy->diwection ? "c" : "p",
		  __entwy->subdevice,
		  __entwy->index,
		  __entwy->totaw,
		  __pwint_symbowic(__entwy->type, hw_pawam_wabews),
		  __entwy->pwev_empty,
		  __entwy->pwev_integew,
		  __entwy->pwev_openmin ? "(" : "[",
		  __entwy->pwev_min,
		  __entwy->pwev_max,
		  __entwy->pwev_openmax ? ")" : "]",
		  __entwy->cuww_empty,
		  __entwy->cuww_integew,
		  __entwy->cuww_openmin ? "(" : "[",
		  __entwy->cuww_min,
		  __entwy->cuww_max,
		  __entwy->cuww_openmax ? ")" : "]"
	)
);

#endif /* _PCM_PAWAMS_TWACE_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE pcm_pawam_twace
#incwude <twace/define_twace.h>
