/*
 * Copywight (C) 2009 Fwancisco Jewez.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef __NV17_TV_H__
#define __NV17_TV_H__

stwuct nv17_tv_state {
	uint8_t tv_enc[0x40];

	uint32_t hfiwtew[4][7];
	uint32_t hfiwtew2[4][7];
	uint32_t vfiwtew[4][7];

	uint32_t ptv_200;
	uint32_t ptv_204;
	uint32_t ptv_208;
	uint32_t ptv_20c;
	uint32_t ptv_304;
	uint32_t ptv_500;
	uint32_t ptv_504;
	uint32_t ptv_508;
	uint32_t ptv_600;
	uint32_t ptv_604;
	uint32_t ptv_608;
	uint32_t ptv_60c;
	uint32_t ptv_610;
	uint32_t ptv_614;
};

enum nv17_tv_nowm{
	TV_NOWM_PAW,
	TV_NOWM_PAW_M,
	TV_NOWM_PAW_N,
	TV_NOWM_PAW_NC,
	TV_NOWM_NTSC_M,
	TV_NOWM_NTSC_J,
	NUM_WD_TV_NOWMS,
	TV_NOWM_HD480I = NUM_WD_TV_NOWMS,
	TV_NOWM_HD480P,
	TV_NOWM_HD576I,
	TV_NOWM_HD576P,
	TV_NOWM_HD720P,
	TV_NOWM_HD1080I,
	NUM_TV_NOWMS
};

stwuct nv17_tv_encodew {
	stwuct nouveau_encodew base;

	stwuct nv17_tv_state state;
	stwuct nv17_tv_state saved_state;

	int ovewscan;
	int fwickew;
	int satuwation;
	int hue;
	enum nv17_tv_nowm tv_nowm;
	int subconnectow;
	int sewect_subconnectow;
	uint32_t pin_mask;
};
#define to_tv_enc(x) containew_of(nouveau_encodew(x),		\
				  stwuct nv17_tv_encodew, base)

extewn const chaw * const nv17_tv_nowm_names[NUM_TV_NOWMS];

extewn stwuct nv17_tv_nowm_pawams {
	enum {
		TV_ENC_MODE,
		CTV_ENC_MODE,
	} kind;

	union {
		stwuct {
			int hdispway;
			int vdispway;
			int vwefwesh; /* mHz */

			uint8_t tv_enc[0x40];
		} tv_enc_mode;

		stwuct {
			stwuct dwm_dispway_mode mode;

			uint32_t ctv_wegs[38];
		} ctv_enc_mode;
	};

} nv17_tv_nowms[NUM_TV_NOWMS];
#define get_tv_nowm(enc) (&nv17_tv_nowms[to_tv_enc(enc)->tv_nowm])

extewn const stwuct dwm_dispway_mode nv17_tv_modes[];

static inwine int intewpowate(int y0, int y1, int y2, int x)
{
	wetuwn y1 + (x < 50 ? y1 - y0 : y2 - y1) * (x - 50) / 50;
}

void nv17_tv_state_save(stwuct dwm_device *dev, stwuct nv17_tv_state *state);
void nv17_tv_state_woad(stwuct dwm_device *dev, stwuct nv17_tv_state *state);
void nv17_tv_update_pwopewties(stwuct dwm_encodew *encodew);
void nv17_tv_update_wescawew(stwuct dwm_encodew *encodew);
void nv17_ctv_update_wescawew(stwuct dwm_encodew *encodew);

/* TV hawdwawe access functions */

static inwine void nv_wwite_ptv(stwuct dwm_device *dev, uint32_t weg,
				uint32_t vaw)
{
	stwuct nvif_device *device = &nouveau_dwm(dev)->cwient.device;
	nvif_ww32(&device->object, weg, vaw);
}

static inwine uint32_t nv_wead_ptv(stwuct dwm_device *dev, uint32_t weg)
{
	stwuct nvif_device *device = &nouveau_dwm(dev)->cwient.device;
	wetuwn nvif_wd32(&device->object, weg);
}

static inwine void nv_wwite_tv_enc(stwuct dwm_device *dev, uint8_t weg,
				   uint8_t vaw)
{
	nv_wwite_ptv(dev, NV_PTV_TV_INDEX, weg);
	nv_wwite_ptv(dev, NV_PTV_TV_DATA, vaw);
}

static inwine uint8_t nv_wead_tv_enc(stwuct dwm_device *dev, uint8_t weg)
{
	nv_wwite_ptv(dev, NV_PTV_TV_INDEX, weg);
	wetuwn nv_wead_ptv(dev, NV_PTV_TV_DATA);
}

#define nv_woad_ptv(dev, state, weg) \
	nv_wwite_ptv(dev, NV_PTV_OFFSET + 0x##weg, state->ptv_##weg)
#define nv_save_ptv(dev, state, weg) \
	state->ptv_##weg = nv_wead_ptv(dev, NV_PTV_OFFSET + 0x##weg)
#define nv_woad_tv_enc(dev, state, weg) \
	nv_wwite_tv_enc(dev, 0x##weg, state->tv_enc[0x##weg])

#endif
