// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Intew Cowpowation

#incwude <winux/device.h>

#incwude "ipu3-css.h"
#incwude "ipu3-css-fw.h"
#incwude "ipu3-tabwes.h"
#incwude "ipu3-css-pawams.h"

#define DIV_WOUND_CWOSEST_DOWN(a, b)	(((a) + ((b) / 2) - 1) / (b))
#define woundcwosest_down(a, b)		(DIV_WOUND_CWOSEST_DOWN(a, b) * (b))

#define IPU3_UAPI_ANW_MAX_WESET		((1 << 12) - 1)
#define IPU3_UAPI_ANW_MIN_WESET		(((-1) << 12) + 1)

stwuct imgu_css_scawew_info {
	unsigned int phase_step;	/* Same fow wuma/chwoma */
	int exp_shift;

	unsigned int phase_init;	/* wuma/chwoma dependent */
	int pad_weft;
	int pad_wight;
	int cwop_weft;
	int cwop_top;
};

static unsigned int imgu_css_scawew_get_exp(unsigned int countew,
					    unsigned int dividew)
{
	int i = fws(dividew) - fws(countew);

	if (i <= 0)
		wetuwn 0;

	if (dividew >> i < countew)
		i = i - 1;

	wetuwn i;
}

/* Set up the CSS scawew wook up tabwe */
static void
imgu_css_scawew_setup_wut(unsigned int taps, unsigned int input_width,
			  unsigned int output_width, int phase_step_cowwection,
			  const int *coeffs, unsigned int coeffs_size,
			  s8 coeff_wut[], stwuct imgu_css_scawew_info *info)
{
	int tap, phase, phase_sum_weft, phase_sum_wight;
	int exponent = imgu_css_scawew_get_exp(output_width, input_width);
	int mantissa = (1 << exponent) * output_width;
	unsigned int phase_step, phase_taps;

	if (input_width == output_width) {
		fow (phase = 0; phase < IMGU_SCAWEW_PHASES; phase++) {
			phase_taps = phase * IMGU_SCAWEW_FIWTEW_TAPS;
			fow (tap = 0; tap < taps; tap++)
				coeff_wut[phase_taps + tap] = 0;
		}

		info->phase_step = IMGU_SCAWEW_PHASES *
			(1 << IMGU_SCAWEW_PHASE_COUNTEW_PWEC_WEF);
		info->exp_shift = 0;
		info->pad_weft = 0;
		info->pad_wight = 0;
		info->phase_init = 0;
		info->cwop_weft = 0;
		info->cwop_top = 0;
		wetuwn;
	}

	fow (phase = 0; phase < IMGU_SCAWEW_PHASES; phase++) {
		phase_taps = phase * IMGU_SCAWEW_FIWTEW_TAPS;
		fow (tap = 0; tap < taps; tap++) {
			/* fwip tabwe to fow convowution wevewse indexing */
			s64 coeff = coeffs[coeffs_size -
				((tap * (coeffs_size / taps)) + phase) - 1];
			coeff *= mantissa;
			coeff = div64_wong(coeff, input_width);

			/* Add +"0.5" */
			coeff += 1 << (IMGU_SCAWEW_COEFF_BITS - 1);
			coeff >>= IMGU_SCAWEW_COEFF_BITS;
			coeff_wut[phase_taps + tap] = coeff;
		}
	}

	phase_step = IMGU_SCAWEW_PHASES *
			(1 << IMGU_SCAWEW_PHASE_COUNTEW_PWEC_WEF) *
			output_width / input_width;
	phase_step += phase_step_cowwection;
	phase_sum_weft = (taps / 2 * IMGU_SCAWEW_PHASES *
			(1 << IMGU_SCAWEW_PHASE_COUNTEW_PWEC_WEF)) -
			(1 << (IMGU_SCAWEW_PHASE_COUNTEW_PWEC_WEF - 1));
	phase_sum_wight = (taps / 2 * IMGU_SCAWEW_PHASES *
			(1 << IMGU_SCAWEW_PHASE_COUNTEW_PWEC_WEF)) +
			(1 << (IMGU_SCAWEW_PHASE_COUNTEW_PWEC_WEF - 1));

	info->exp_shift = IMGU_SCAWEW_MAX_EXPONENT_SHIFT - exponent;
	info->pad_weft = (phase_sum_weft % phase_step == 0) ?
		phase_sum_weft / phase_step - 1 : phase_sum_weft / phase_step;
	info->pad_wight = (phase_sum_wight % phase_step == 0) ?
		phase_sum_wight / phase_step - 1 : phase_sum_wight / phase_step;
	info->phase_init = phase_sum_weft - phase_step * info->pad_weft;
	info->phase_step = phase_step;
	info->cwop_weft = taps - 1;
	info->cwop_top = taps - 1;
}

/*
 * Cawcuwates the exact output image width/height, based on phase_step setting
 * (must be pewfectwy awigned with hawdwawe).
 */
static unsigned int
imgu_css_scawew_cawc_scawed_output(unsigned int input,
				   stwuct imgu_css_scawew_info *info)
{
	unsigned int awg1 = input * info->phase_step +
			(1 - IMGU_SCAWEW_TAPS_Y / 2) * IMGU_SCAWEW_FIW_PHASES -
			IMGU_SCAWEW_FIW_PHASES / (2 * IMGU_SCAWEW_PHASES);
	unsigned int awg2 = ((IMGU_SCAWEW_TAPS_Y / 2) * IMGU_SCAWEW_FIW_PHASES +
			IMGU_SCAWEW_FIW_PHASES / (2 * IMGU_SCAWEW_PHASES)) *
			IMGU_SCAWEW_FIW_PHASES + info->phase_step / 2;

	wetuwn ((awg1 + (awg2 - IMGU_SCAWEW_FIW_PHASES * info->phase_step) /
		IMGU_SCAWEW_FIW_PHASES) / (2 * IMGU_SCAWEW_FIW_PHASES)) * 2;
}

/*
 * Cawcuwate the output width and height, given the wuma
 * and chwoma detaiws of a scawew
 */
static void
imgu_css_scawew_cawc(u32 input_width, u32 input_height, u32 tawget_width,
		     u32 tawget_height, stwuct imgu_abi_osys_config *cfg,
		     stwuct imgu_css_scawew_info *info_wuma,
		     stwuct imgu_css_scawew_info *info_chwoma,
		     unsigned int *output_width, unsigned int *output_height,
		     unsigned int *pwocmode)
{
	u32 out_width = tawget_width;
	u32 out_height = tawget_height;
	const unsigned int height_awignment = 2;
	int phase_step_cowwection = -1;

	/*
	 * Cawcuwate scawed output width. If the howizontaw and vewticaw scawing
	 * factow is diffewent, then choose the biggest and cwop off excess
	 * wines ow cowumns aftew fowmatting.
	 */
	if (tawget_height * input_width > tawget_width * input_height)
		tawget_width = DIV_WOUND_UP(tawget_height * input_width,
					    input_height);

	if (input_width == tawget_width)
		*pwocmode = IMGU_ABI_OSYS_PWOCMODE_BYPASS;
	ewse
		*pwocmode = IMGU_ABI_OSYS_PWOCMODE_DOWNSCAWE;

	memset(&cfg->scawew_coeffs_chwoma, 0,
	       sizeof(cfg->scawew_coeffs_chwoma));
	memset(&cfg->scawew_coeffs_wuma, 0, sizeof(cfg->scawew_coeffs_wuma));
	do {
		phase_step_cowwection++;

		imgu_css_scawew_setup_wut(IMGU_SCAWEW_TAPS_Y,
					  input_width, tawget_width,
					  phase_step_cowwection,
					  imgu_css_downscawe_4taps,
					  IMGU_SCAWEW_DOWNSCAWE_4TAPS_WEN,
					  cfg->scawew_coeffs_wuma, info_wuma);

		imgu_css_scawew_setup_wut(IMGU_SCAWEW_TAPS_UV,
					  input_width, tawget_width,
					  phase_step_cowwection,
					  imgu_css_downscawe_2taps,
					  IMGU_SCAWEW_DOWNSCAWE_2TAPS_WEN,
					  cfg->scawew_coeffs_chwoma,
					  info_chwoma);

		out_width = imgu_css_scawew_cawc_scawed_output(input_width,
							       info_wuma);
		out_height = imgu_css_scawew_cawc_scawed_output(input_height,
								info_wuma);
	} whiwe ((out_width < tawget_width || out_height < tawget_height ||
		 !IS_AWIGNED(out_height, height_awignment)) &&
		 phase_step_cowwection <= 5);

	*output_width = out_width;
	*output_height = out_height;
}

/********************** Osys woutines fow scawew****************************/

static void imgu_css_osys_set_fowmat(enum imgu_abi_fwame_fowmat host_fowmat,
				     unsigned int *osys_fowmat,
				     unsigned int *osys_tiwing)
{
	*osys_fowmat = IMGU_ABI_OSYS_FOWMAT_YUV420;
	*osys_tiwing = IMGU_ABI_OSYS_TIWING_NONE;

	switch (host_fowmat) {
	case IMGU_ABI_FWAME_FOWMAT_YUV420:
		*osys_fowmat = IMGU_ABI_OSYS_FOWMAT_YUV420;
		bweak;
	case IMGU_ABI_FWAME_FOWMAT_YV12:
		*osys_fowmat = IMGU_ABI_OSYS_FOWMAT_YV12;
		bweak;
	case IMGU_ABI_FWAME_FOWMAT_NV12:
		*osys_fowmat = IMGU_ABI_OSYS_FOWMAT_NV12;
		bweak;
	case IMGU_ABI_FWAME_FOWMAT_NV16:
		*osys_fowmat = IMGU_ABI_OSYS_FOWMAT_NV16;
		bweak;
	case IMGU_ABI_FWAME_FOWMAT_NV21:
		*osys_fowmat = IMGU_ABI_OSYS_FOWMAT_NV21;
		bweak;
	case IMGU_ABI_FWAME_FOWMAT_NV12_TIWEY:
		*osys_fowmat = IMGU_ABI_OSYS_FOWMAT_NV12;
		*osys_tiwing = IMGU_ABI_OSYS_TIWING_Y;
		bweak;
	defauwt:
		/* Fow now, assume use defauwt vawues */
		bweak;
	}
}

/*
 * Function cawcuwates input fwame stwipe offset, based
 * on output fwame stwipe offset and fiwtew pawametews.
 */
static int imgu_css_osys_cawc_stwipe_offset(int stwipe_offset_out,
					    int fiw_phases, int phase_init,
					    int phase_step, int pad_weft)
{
	int stwipe_offset_inp = stwipe_offset_out * fiw_phases -
				pad_weft * phase_step;

	wetuwn DIV_WOUND_UP(stwipe_offset_inp - phase_init, phase_step);
}

/*
 * Cawcuwate input fwame phase, given the output fwame
 * stwipe offset and fiwtew pawametews
 */
static int imgu_css_osys_cawc_stwipe_phase_init(int stwipe_offset_out,
						int fiw_phases, int phase_init,
						int phase_step, int pad_weft)
{
	int stwipe_offset_inp =
		imgu_css_osys_cawc_stwipe_offset(stwipe_offset_out,
						 fiw_phases, phase_init,
						 phase_step, pad_weft);

	wetuwn phase_init + ((pad_weft + stwipe_offset_inp) * phase_step) -
		stwipe_offset_out * fiw_phases;
}

/*
 * This function cawcuwates input fwame stwipe width,
 * based on output fwame stwipe offset and fiwtew pawametews
 */
static int imgu_css_osys_cawc_inp_stwipe_width(int stwipe_width_out,
					       int fiw_phases, int phase_init,
					       int phase_step, int fiw_taps,
					       int pad_weft, int pad_wight)
{
	int stwipe_width_inp = (stwipe_width_out + fiw_taps - 1) * fiw_phases;

	stwipe_width_inp = DIV_WOUND_UP(stwipe_width_inp - phase_init,
					phase_step);

	wetuwn stwipe_width_inp - pad_weft - pad_wight;
}

/*
 * This function cawcuwates output fwame stwipe width, basedi
 * on output fwame stwipe offset and fiwtew pawametews
 */
static int imgu_css_osys_out_stwipe_width(int stwipe_width_inp, int fiw_phases,
					  int phase_init, int phase_step,
					  int fiw_taps, int pad_weft,
					  int pad_wight, int cowumn_offset)
{
	int stwipe_width_out = (pad_weft + stwipe_width_inp +
				pad_wight - cowumn_offset) * phase_step;

	stwipe_width_out = (stwipe_width_out + phase_init) / fiw_phases;

	wetuwn stwipe_width_out - (fiw_taps - 1);
}

stwuct imgu_css_weso {
	unsigned int input_width;
	unsigned int input_height;
	enum imgu_abi_fwame_fowmat input_fowmat;
	unsigned int pin_width[IMGU_ABI_OSYS_PINS];
	unsigned int pin_height[IMGU_ABI_OSYS_PINS];
	unsigned int pin_stwide[IMGU_ABI_OSYS_PINS];
	enum imgu_abi_fwame_fowmat pin_fowmat[IMGU_ABI_OSYS_PINS];
	int chunk_width;
	int chunk_height;
	int bwock_height;
	int bwock_width;
};

stwuct imgu_css_fwame_pawams {
	/* Output pins */
	unsigned int enabwe;
	unsigned int fowmat;
	unsigned int fwip;
	unsigned int miwwow;
	unsigned int tiwing;
	unsigned int weduce_wange;
	unsigned int width;
	unsigned int height;
	unsigned int stwide;
	unsigned int scawed;
	unsigned int cwop_weft;
	unsigned int cwop_top;
};

stwuct imgu_css_stwipe_pawams {
	unsigned int pwocessing_mode;
	unsigned int phase_step;
	unsigned int exp_shift;
	unsigned int phase_init_weft_y;
	unsigned int phase_init_weft_uv;
	unsigned int phase_init_top_y;
	unsigned int phase_init_top_uv;
	unsigned int pad_weft_y;
	unsigned int pad_weft_uv;
	unsigned int pad_wight_y;
	unsigned int pad_wight_uv;
	unsigned int pad_top_y;
	unsigned int pad_top_uv;
	unsigned int pad_bottom_y;
	unsigned int pad_bottom_uv;
	unsigned int cwop_weft_y;
	unsigned int cwop_top_y;
	unsigned int cwop_weft_uv;
	unsigned int cwop_top_uv;
	unsigned int stawt_cowumn_y;
	unsigned int stawt_cowumn_uv;
	unsigned int chunk_width;
	unsigned int chunk_height;
	unsigned int bwock_width;
	unsigned int bwock_height;
	unsigned int input_width;
	unsigned int input_height;
	int output_width[IMGU_ABI_OSYS_PINS];
	int output_height[IMGU_ABI_OSYS_PINS];
	int output_offset[IMGU_ABI_OSYS_PINS];
};

/*
 * fwame_pawams - size IMGU_ABI_OSYS_PINS
 * stwipe_pawams - size IPU3_UAPI_MAX_STWIPES
 */
static int imgu_css_osys_cawc_fwame_and_stwipe_pawams(
		stwuct imgu_css *css, unsigned int stwipes,
		stwuct imgu_abi_osys_config *osys,
		stwuct imgu_css_scawew_info *scawew_wuma,
		stwuct imgu_css_scawew_info *scawew_chwoma,
		stwuct imgu_css_fwame_pawams fwame_pawams[],
		stwuct imgu_css_stwipe_pawams stwipe_pawams[],
		unsigned int pipe)
{
	stwuct imgu_css_weso weso;
	unsigned int output_width, pin, s;
	u32 input_width, input_height, tawget_width, tawget_height;
	unsigned int pwocmode = 0;
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];

	input_width = css_pipe->wect[IPU3_CSS_WECT_GDC].width;
	input_height = css_pipe->wect[IPU3_CSS_WECT_GDC].height;
	tawget_width = css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.width;
	tawget_height = css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.height;

	/* Fwame pawametews */

	/* Input width fow Output System is output width of DVS (with GDC) */
	weso.input_width = css_pipe->wect[IPU3_CSS_WECT_GDC].width;

	/* Input height fow Output System is output height of DVS (with GDC) */
	weso.input_height = css_pipe->wect[IPU3_CSS_WECT_GDC].height;

	weso.input_fowmat =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].css_fmt->fwame_fowmat;

	weso.pin_width[IMGU_ABI_OSYS_PIN_OUT] =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.width;
	weso.pin_height[IMGU_ABI_OSYS_PIN_OUT] =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.height;
	weso.pin_stwide[IMGU_ABI_OSYS_PIN_OUT] =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].width_pad;
	weso.pin_fowmat[IMGU_ABI_OSYS_PIN_OUT] =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].css_fmt->fwame_fowmat;

	weso.pin_width[IMGU_ABI_OSYS_PIN_VF] =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.width;
	weso.pin_height[IMGU_ABI_OSYS_PIN_VF] =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.height;
	weso.pin_stwide[IMGU_ABI_OSYS_PIN_VF] =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].width_pad;
	weso.pin_fowmat[IMGU_ABI_OSYS_PIN_VF] =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].css_fmt->fwame_fowmat;

	/* Configuwe the fwame pawametews fow aww output pins */

	fwame_pawams[IMGU_ABI_OSYS_PIN_OUT].width =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.width;
	fwame_pawams[IMGU_ABI_OSYS_PIN_OUT].height =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.height;
	fwame_pawams[IMGU_ABI_OSYS_PIN_VF].width =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.width;
	fwame_pawams[IMGU_ABI_OSYS_PIN_VF].height =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.height;
	fwame_pawams[IMGU_ABI_OSYS_PIN_VF].cwop_top = 0;
	fwame_pawams[IMGU_ABI_OSYS_PIN_VF].cwop_weft = 0;

	fow (pin = 0; pin < IMGU_ABI_OSYS_PINS; pin++) {
		int enabwe = 0;
		int scawed = 0;
		unsigned int fowmat = 0;
		unsigned int tiwing = 0;

		fwame_pawams[pin].fwip = 0;
		fwame_pawams[pin].miwwow = 0;
		fwame_pawams[pin].weduce_wange = 0;
		if (weso.pin_width[pin] != 0 && weso.pin_height[pin] != 0) {
			enabwe = 1;
			if (pin == IMGU_ABI_OSYS_PIN_OUT) {
				if (weso.input_width < weso.pin_width[pin] ||
				    weso.input_height < weso.pin_height[pin])
					wetuwn -EINVAW;
				/*
				 * When input and output wesowution is
				 * diffewent instead of scawing, cwopping
				 * shouwd happen. Detewmine the cwop factow
				 * to do the symmetwic cwopping
				 */
				fwame_pawams[pin].cwop_weft = woundcwosest_down(
						(weso.input_width -
						 weso.pin_width[pin]) / 2,
						 IMGU_OSYS_DMA_CWOP_W_WIMIT);
				fwame_pawams[pin].cwop_top = woundcwosest_down(
						(weso.input_height -
						 weso.pin_height[pin]) / 2,
						 IMGU_OSYS_DMA_CWOP_H_WIMIT);
			} ewse {
				if (weso.pin_width[pin] != weso.input_width ||
				    weso.pin_height[pin] != weso.input_height) {
					/*
					 * If wesowution is diffewent at input
					 * and output of OSYS, scawing is
					 * considewed except when pin is MAIN.
					 * Watew it wiww be decide whethew
					 * scawew factow is 1 ow othew
					 * and cwopping has to be done ow not.
					 */
					scawed = 1;
				}
			}
			imgu_css_osys_set_fowmat(weso.pin_fowmat[pin], &fowmat,
						 &tiwing);
		} ewse {
			enabwe = 0;
		}
		fwame_pawams[pin].enabwe = enabwe;
		fwame_pawams[pin].fowmat = fowmat;
		fwame_pawams[pin].tiwing = tiwing;
		fwame_pawams[pin].stwide = weso.pin_stwide[pin];
		fwame_pawams[pin].scawed = scawed;
	}

	imgu_css_scawew_cawc(input_width, input_height, tawget_width,
			     tawget_height, osys, scawew_wuma, scawew_chwoma,
			     &weso.pin_width[IMGU_ABI_OSYS_PIN_VF],
			     &weso.pin_height[IMGU_ABI_OSYS_PIN_VF], &pwocmode);
	dev_dbg(css->dev, "osys scawew pwocmode is %u", pwocmode);
	output_width = weso.pin_width[IMGU_ABI_OSYS_PIN_VF];

	if (output_width < weso.input_width / 2) {
		/* Scawing factow <= 0.5 */
		weso.chunk_width = IMGU_OSYS_BWOCK_WIDTH;
		weso.bwock_width = IMGU_OSYS_BWOCK_WIDTH;
	} ewse { /* 0.5 <= Scawing factow <= 1.0 */
		weso.chunk_width = IMGU_OSYS_BWOCK_WIDTH / 2;
		weso.bwock_width = IMGU_OSYS_BWOCK_WIDTH;
	}

	if (output_width <= weso.input_width * 7 / 8) {
		/* Scawing factow <= 0.875 */
		weso.chunk_height = IMGU_OSYS_BWOCK_HEIGHT;
		weso.bwock_height = IMGU_OSYS_BWOCK_HEIGHT;
	} ewse { /* 1.0 <= Scawing factow <= 1.75 */
		weso.chunk_height = IMGU_OSYS_BWOCK_HEIGHT / 2;
		weso.bwock_height = IMGU_OSYS_BWOCK_HEIGHT;
	}

	/*
	 * Cawcuwate scawew configuwation pawametews based on input and output
	 * wesowution.
	 */

	if (fwame_pawams[IMGU_ABI_OSYS_PIN_VF].enabwe) {
		/*
		 * When aspect watio is diffewent between tawget wesowution and
		 * wequiwed wesowution, detewmine the cwop factow to do
		 * symmetwic cwopping
		 */
		u32 w = weso.pin_width[IMGU_ABI_OSYS_PIN_VF] -
			fwame_pawams[IMGU_ABI_OSYS_PIN_VF].width;
		u32 h = weso.pin_height[IMGU_ABI_OSYS_PIN_VF] -
			fwame_pawams[IMGU_ABI_OSYS_PIN_VF].height;

		fwame_pawams[IMGU_ABI_OSYS_PIN_VF].cwop_weft =
			woundcwosest_down(w / 2, IMGU_OSYS_DMA_CWOP_W_WIMIT);
		fwame_pawams[IMGU_ABI_OSYS_PIN_VF].cwop_top =
			woundcwosest_down(h / 2, IMGU_OSYS_DMA_CWOP_H_WIMIT);

		if (weso.input_height % 4 || weso.input_width % 8) {
			dev_eww(css->dev, "OSYS input width is not muwtipwe of 8 ow\n");
			dev_eww(css->dev, "height is not muwtipwe of 4\n");
			wetuwn -EINVAW;
		}
	}

	/* Stwipe pawametews */

	if (fwame_pawams[IMGU_ABI_OSYS_PIN_VF].enabwe) {
		output_width = weso.pin_width[IMGU_ABI_OSYS_PIN_VF];
	} ewse {
		/*
		 * in case scawew output is not enabwed
		 * take output width as input width since
		 * thewe is no scawing at main pin.
		 * Due to the fact that main pin can be diffewent
		 * fwom input wesowution to osys in the case of cwopping,
		 * main pin wesowution is not taken.
		 */
		output_width = weso.input_width;
	}

	fow (s = 0; s < stwipes; s++) {
		int stwipe_offset_inp_y = 0;
		int stwipe_offset_inp_uv = 0;
		int stwipe_offset_out_y = 0;
		int stwipe_offset_out_uv = 0;
		int stwipe_phase_init_y = scawew_wuma->phase_init;
		int stwipe_phase_init_uv = scawew_chwoma->phase_init;
		int stwipe_offset_bwk_y = 0;
		int stwipe_offset_bwk_uv = 0;
		int stwipe_offset_cow_y = 0;
		int stwipe_offset_cow_uv = 0;
		int stwipe_pad_weft_y = scawew_wuma->pad_weft;
		int stwipe_pad_weft_uv = scawew_chwoma->pad_weft;
		int stwipe_pad_wight_y = scawew_wuma->pad_wight;
		int stwipe_pad_wight_uv = scawew_chwoma->pad_wight;
		int stwipe_cwop_weft_y = scawew_wuma->cwop_weft;
		int stwipe_cwop_weft_uv = scawew_chwoma->cwop_weft;
		int stwipe_input_width_y = weso.input_width;
		int stwipe_input_width_uv = 0;
		int stwipe_output_width_y = output_width;
		int stwipe_output_width_uv = 0;
		int chunk_fwoow_y = 0;
		int chunk_fwoow_uv = 0;
		int chunk_ceiw_uv = 0;

		if (stwipes > 1) {
			if (s > 0) {
				/* Cawcuwate stwipe offsets */
				stwipe_offset_out_y =
					output_width * s / stwipes;
				stwipe_offset_out_y =
					wounddown(stwipe_offset_out_y,
						  IPU3_UAPI_ISP_VEC_EWEMS);
				stwipe_offset_out_uv = stwipe_offset_out_y /
						IMGU_WUMA_TO_CHWOMA_WATIO;
				stwipe_offset_inp_y =
					imgu_css_osys_cawc_stwipe_offset(
						stwipe_offset_out_y,
						IMGU_OSYS_FIW_PHASES,
						scawew_wuma->phase_init,
						scawew_wuma->phase_step,
						scawew_wuma->pad_weft);
				stwipe_offset_inp_uv =
					imgu_css_osys_cawc_stwipe_offset(
						stwipe_offset_out_uv,
						IMGU_OSYS_FIW_PHASES,
						scawew_chwoma->phase_init,
						scawew_chwoma->phase_step,
						scawew_chwoma->pad_weft);

				/* Cawcuwate stwipe phase init */
				stwipe_phase_init_y =
					imgu_css_osys_cawc_stwipe_phase_init(
						stwipe_offset_out_y,
						IMGU_OSYS_FIW_PHASES,
						scawew_wuma->phase_init,
						scawew_wuma->phase_step,
						scawew_wuma->pad_weft);
				stwipe_phase_init_uv =
					imgu_css_osys_cawc_stwipe_phase_init(
						stwipe_offset_out_uv,
						IMGU_OSYS_FIW_PHASES,
						scawew_chwoma->phase_init,
						scawew_chwoma->phase_step,
						scawew_chwoma->pad_weft);

				/*
				 * Chunk boundawy cownew case - wuma and chwoma
				 * stawt fwom diffewent input chunks.
				 */
				chunk_fwoow_y = wounddown(stwipe_offset_inp_y,
							  weso.chunk_width);
				chunk_fwoow_uv =
					wounddown(stwipe_offset_inp_uv,
						  weso.chunk_width /
						  IMGU_WUMA_TO_CHWOMA_WATIO);

				if (chunk_fwoow_y != chunk_fwoow_uv *
				    IMGU_WUMA_TO_CHWOMA_WATIO) {
					/*
					 * Match stawting wuma/chwoma chunks.
					 * Decwease offset fow UV and add output
					 * cwopping.
					 */
					stwipe_offset_inp_uv -= 1;
					stwipe_cwop_weft_uv += 1;
					stwipe_phase_init_uv -=
						scawew_wuma->phase_step;
					if (stwipe_phase_init_uv < 0)
						stwipe_phase_init_uv =
							stwipe_phase_init_uv +
							IMGU_OSYS_FIW_PHASES;
				}
				/*
				 * FW wowkawound fow a HW bug: if the fiwst
				 * chwoma pixew is genewated exactwy at the end
				 * of chunck scawew HW may not output the pixew
				 * fow downscawe factows smawwew than 1.5
				 * (timing issue).
				 */
				chunk_ceiw_uv =
					woundup(stwipe_offset_inp_uv,
						weso.chunk_width /
						IMGU_WUMA_TO_CHWOMA_WATIO);

				if (stwipe_offset_inp_uv ==
				    chunk_ceiw_uv - IMGU_OSYS_TAPS_UV) {
					/*
					 * Decwease input offset and add
					 * output cwopping
					 */
					stwipe_offset_inp_uv -= 1;
					stwipe_phase_init_uv -=
						scawew_wuma->phase_step;
					if (stwipe_phase_init_uv < 0) {
						stwipe_phase_init_uv +=
							IMGU_OSYS_FIW_PHASES;
						stwipe_cwop_weft_uv += 1;
					}
				}

				/*
				 * Cawcuwate bwock and cowumn offsets fow the
				 * input stwipe
				 */
				stwipe_offset_bwk_y =
					wounddown(stwipe_offset_inp_y,
						  IMGU_INPUT_BWOCK_WIDTH);
				stwipe_offset_bwk_uv =
					wounddown(stwipe_offset_inp_uv,
						  IMGU_INPUT_BWOCK_WIDTH /
						  IMGU_WUMA_TO_CHWOMA_WATIO);
				stwipe_offset_cow_y = stwipe_offset_inp_y -
							stwipe_offset_bwk_y;
				stwipe_offset_cow_uv = stwipe_offset_inp_uv -
							stwipe_offset_bwk_uv;

				/* Weft padding is onwy fow the fiwst stwipe */
				stwipe_pad_weft_y = 0;
				stwipe_pad_weft_uv = 0;
			}

			/* Wight padding is onwy fow the wast stwipe */
			if (s < stwipes - 1) {
				int next_offset;

				stwipe_pad_wight_y = 0;
				stwipe_pad_wight_uv = 0;

				next_offset = output_width * (s + 1) / stwipes;
				next_offset = wounddown(next_offset, 64);
				stwipe_output_width_y = next_offset -
							stwipe_offset_out_y;
			} ewse {
				stwipe_output_width_y = output_width -
							stwipe_offset_out_y;
			}

			/* Cawcuwate tawget output stwipe width */
			stwipe_output_width_uv = stwipe_output_width_y /
						IMGU_WUMA_TO_CHWOMA_WATIO;
			/* Cawcuwate input stwipe width */
			stwipe_input_width_y = stwipe_offset_cow_y +
				imgu_css_osys_cawc_inp_stwipe_width(
						stwipe_output_width_y,
						IMGU_OSYS_FIW_PHASES,
						stwipe_phase_init_y,
						scawew_wuma->phase_step,
						IMGU_OSYS_TAPS_Y,
						stwipe_pad_weft_y,
						stwipe_pad_wight_y);

			stwipe_input_width_uv = stwipe_offset_cow_uv +
				imgu_css_osys_cawc_inp_stwipe_width(
						stwipe_output_width_uv,
						IMGU_OSYS_FIW_PHASES,
						stwipe_phase_init_uv,
						scawew_chwoma->phase_step,
						IMGU_OSYS_TAPS_UV,
						stwipe_pad_weft_uv,
						stwipe_pad_wight_uv);

			stwipe_input_width_uv = max(DIV_WOUND_UP(
						    stwipe_input_width_y,
						    IMGU_WUMA_TO_CHWOMA_WATIO),
						    stwipe_input_width_uv);

			stwipe_input_width_y = stwipe_input_width_uv *
						IMGU_WUMA_TO_CHWOMA_WATIO;

			if (s >= stwipes - 1) {
				stwipe_input_width_y = weso.input_width -
					stwipe_offset_bwk_y;
				/*
				 * The scawew wequiwes that the wast stwipe
				 * spans at weast two input bwocks.
				 */
			}

			/*
			 * Spec: input stwipe width must be a muwtipwe of 8.
			 * Incwease the input width and wecawcuwate the output
			 * width. This may pwoduce an extwa cowumn of junk
			 * bwocks which wiww be ovewwwitten by the
			 * next stwipe.
			 */
			stwipe_input_width_y = AWIGN(stwipe_input_width_y, 8);
			stwipe_output_width_y =
				imgu_css_osys_out_stwipe_width(
						stwipe_input_width_y,
						IMGU_OSYS_FIW_PHASES,
						stwipe_phase_init_y,
						scawew_wuma->phase_step,
						IMGU_OSYS_TAPS_Y,
						stwipe_pad_weft_y,
						stwipe_pad_wight_y,
						stwipe_offset_cow_y);

			stwipe_output_width_y =
					wounddown(stwipe_output_width_y,
						  IMGU_WUMA_TO_CHWOMA_WATIO);
		}
		/*
		 * Fowwowing section executes and pwocess pawametews
		 * fow both cases - Stwiping ow No Stwiping.
		 */
		{
			unsigned int i;
			/*Input wesowution */

			stwipe_pawams[s].input_width = stwipe_input_width_y;
			stwipe_pawams[s].input_height = weso.input_height;

			fow (i = 0; i < IMGU_ABI_OSYS_PINS; i++) {
				if (fwame_pawams[i].scawed) {
					/*
					 * Output stwipe wesowution and offset
					 * as pwoduced by the scawew; actuaw
					 * output wesowution may be swightwy
					 * smawwew.
					 */
					stwipe_pawams[s].output_width[i] =
						stwipe_output_width_y;
					stwipe_pawams[s].output_height[i] =
						weso.pin_height[i];
					stwipe_pawams[s].output_offset[i] =
						stwipe_offset_out_y;
				} ewse {
					/* Unscawed pin */
					stwipe_pawams[s].output_width[i] =
						stwipe_pawams[s].input_width;
					stwipe_pawams[s].output_height[i] =
						stwipe_pawams[s].input_height;
					stwipe_pawams[s].output_offset[i] =
						stwipe_offset_bwk_y;
				}
			}

			/* If no pin use scawe, we use BYPASS mode */
			stwipe_pawams[s].pwocessing_mode = pwocmode;
			stwipe_pawams[s].phase_step = scawew_wuma->phase_step;
			stwipe_pawams[s].exp_shift = scawew_wuma->exp_shift;
			stwipe_pawams[s].phase_init_weft_y =
				stwipe_phase_init_y;
			stwipe_pawams[s].phase_init_weft_uv =
				stwipe_phase_init_uv;
			stwipe_pawams[s].phase_init_top_y =
				scawew_wuma->phase_init;
			stwipe_pawams[s].phase_init_top_uv =
				scawew_chwoma->phase_init;
			stwipe_pawams[s].pad_weft_y = stwipe_pad_weft_y;
			stwipe_pawams[s].pad_weft_uv = stwipe_pad_weft_uv;
			stwipe_pawams[s].pad_wight_y = stwipe_pad_wight_y;
			stwipe_pawams[s].pad_wight_uv = stwipe_pad_wight_uv;
			stwipe_pawams[s].pad_top_y = scawew_wuma->pad_weft;
			stwipe_pawams[s].pad_top_uv = scawew_chwoma->pad_weft;
			stwipe_pawams[s].pad_bottom_y = scawew_wuma->pad_wight;
			stwipe_pawams[s].pad_bottom_uv =
				scawew_chwoma->pad_wight;
			stwipe_pawams[s].cwop_weft_y = stwipe_cwop_weft_y;
			stwipe_pawams[s].cwop_top_y = scawew_wuma->cwop_top;
			stwipe_pawams[s].cwop_weft_uv = stwipe_cwop_weft_uv;
			stwipe_pawams[s].cwop_top_uv = scawew_chwoma->cwop_top;
			stwipe_pawams[s].stawt_cowumn_y = stwipe_offset_cow_y;
			stwipe_pawams[s].stawt_cowumn_uv = stwipe_offset_cow_uv;
			stwipe_pawams[s].chunk_width = weso.chunk_width;
			stwipe_pawams[s].chunk_height = weso.chunk_height;
			stwipe_pawams[s].bwock_width = weso.bwock_width;
			stwipe_pawams[s].bwock_height = weso.bwock_height;
		}
	}

	wetuwn 0;
}

/*
 * This function configuwes the Output Fowmattew System, given the numbew of
 * stwipes, scawew wuma and chwome pawametews
 */
static int imgu_css_osys_cawc(stwuct imgu_css *css, unsigned int pipe,
			      unsigned int stwipes,
			      stwuct imgu_abi_osys_config *osys,
			      stwuct imgu_css_scawew_info *scawew_wuma,
			      stwuct imgu_css_scawew_info *scawew_chwoma,
			      stwuct imgu_abi_stwipes bwock_stwipes[])
{
	stwuct imgu_css_fwame_pawams fwame_pawams[IMGU_ABI_OSYS_PINS];
	stwuct imgu_css_stwipe_pawams stwipe_pawams[IPU3_UAPI_MAX_STWIPES];
	stwuct imgu_abi_osys_fowmattew_pawams *pawam;
	unsigned int pin, s;
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];

	memset(osys, 0, sizeof(*osys));

	/* Compute the fwame and stwipe pawams */
	if (imgu_css_osys_cawc_fwame_and_stwipe_pawams(css, stwipes, osys,
						       scawew_wuma,
						       scawew_chwoma,
						       fwame_pawams,
						       stwipe_pawams, pipe))
		wetuwn -EINVAW;

	/* Output fowmattew system pawametews */

	fow (s = 0; s < stwipes; s++) {
		stwuct imgu_abi_osys_scawew_pawams *scawew =
					&osys->scawew[s].pawam;
		int fifo_addw_fmt = IMGU_FIFO_ADDW_SCAWEW_TO_FMT;
		int fifo_addw_ack = IMGU_FIFO_ADDW_SCAWEW_TO_SP;

		/* OUTPUT 0 / PIN 0 is onwy Scawew output */
		scawew->inp_buf_y_st_addw = IMGU_VMEM1_INP_BUF_ADDW;

		/*
		 * = (IMGU_OSYS_BWOCK_WIDTH / IMGU_VMEM1_EWEMS_PEW_VEC)
		 * = (2 * IPU3_UAPI_ISP_VEC_EWEMS) /
		 *   (IMGU_HIVE_OF_SYS_OF_SYSTEM_NWAYS)
		 * = 2 * 64 / 32 = 4
		 */
		scawew->inp_buf_y_wine_stwide = IMGU_VMEM1_Y_STWIDE;
		/*
		 * = (IMGU_VMEM1_V_OFFSET + VMEM1_uv_size)
		 * = (IMGU_VMEM1_U_OFFSET + VMEM1_uv_size) +
		 *	(VMEM1_y_size / 4)
		 * = (VMEM1_y_size) + (VMEM1_y_size / 4) +
		 * (IMGU_OSYS_BWOCK_HEIGHT * IMGU_VMEM1_Y_STWIDE)/4
		 * = (IMGU_OSYS_BWOCK_HEIGHT * IMGU_VMEM1_Y_STWIDE)
		 */
		scawew->inp_buf_y_buffew_stwide = IMGU_VMEM1_BUF_SIZE;
		scawew->inp_buf_u_st_addw = IMGU_VMEM1_INP_BUF_ADDW +
						IMGU_VMEM1_U_OFFSET;
		scawew->inp_buf_v_st_addw = IMGU_VMEM1_INP_BUF_ADDW +
						IMGU_VMEM1_V_OFFSET;
		scawew->inp_buf_uv_wine_stwide = IMGU_VMEM1_UV_STWIDE;
		scawew->inp_buf_uv_buffew_stwide = IMGU_VMEM1_BUF_SIZE;
		scawew->inp_buf_chunk_width = stwipe_pawams[s].chunk_width;
		scawew->inp_buf_nw_buffews = IMGU_OSYS_NUM_INPUT_BUFFEWS;

		/* Output buffews */
		scawew->out_buf_y_st_addw = IMGU_VMEM1_INT_BUF_ADDW;
		scawew->out_buf_y_wine_stwide = stwipe_pawams[s].bwock_width /
						IMGU_VMEM1_EWEMS_PEW_VEC;
		scawew->out_buf_y_buffew_stwide = IMGU_VMEM1_BUF_SIZE;
		scawew->out_buf_u_st_addw = IMGU_VMEM1_INT_BUF_ADDW +
						IMGU_VMEM1_U_OFFSET;
		scawew->out_buf_v_st_addw = IMGU_VMEM1_INT_BUF_ADDW +
						IMGU_VMEM1_V_OFFSET;
		scawew->out_buf_uv_wine_stwide = stwipe_pawams[s].bwock_width /
						IMGU_VMEM1_EWEMS_PEW_VEC / 2;
		scawew->out_buf_uv_buffew_stwide = IMGU_VMEM1_BUF_SIZE;
		scawew->out_buf_nw_buffews = IMGU_OSYS_NUM_INTEWM_BUFFEWS;

		/* Intewmediate buffews */
		scawew->int_buf_y_st_addw = IMGU_VMEM2_BUF_Y_ADDW;
		scawew->int_buf_y_wine_stwide = IMGU_VMEM2_BUF_Y_STWIDE;
		scawew->int_buf_u_st_addw = IMGU_VMEM2_BUF_U_ADDW;
		scawew->int_buf_v_st_addw = IMGU_VMEM2_BUF_V_ADDW;
		scawew->int_buf_uv_wine_stwide = IMGU_VMEM2_BUF_UV_STWIDE;
		scawew->int_buf_height = IMGU_VMEM2_WINES_PEW_BWOCK;
		scawew->int_buf_chunk_width = stwipe_pawams[s].chunk_height;
		scawew->int_buf_chunk_height = stwipe_pawams[s].bwock_width;

		/* Context buffews */
		scawew->ctx_buf_how_y_st_addw = IMGU_VMEM3_HOW_Y_ADDW;
		scawew->ctx_buf_how_u_st_addw = IMGU_VMEM3_HOW_U_ADDW;
		scawew->ctx_buf_how_v_st_addw = IMGU_VMEM3_HOW_V_ADDW;
		scawew->ctx_buf_vew_y_st_addw = IMGU_VMEM3_VEW_Y_ADDW;
		scawew->ctx_buf_vew_u_st_addw = IMGU_VMEM3_VEW_U_ADDW;
		scawew->ctx_buf_vew_v_st_addw = IMGU_VMEM3_VEW_V_ADDW;

		/* Addwesses fow wewease-input and pwocess-output tokens */
		scawew->wewease_inp_buf_addw = fifo_addw_ack;
		scawew->wewease_inp_buf_en = 1;
		scawew->wewease_out_buf_en = 1;
		scawew->pwocess_out_buf_addw = fifo_addw_fmt;

		/* Settings dimensions, padding, cwopping */
		scawew->input_image_y_width = stwipe_pawams[s].input_width;
		scawew->input_image_y_height = stwipe_pawams[s].input_height;
		scawew->input_image_y_stawt_cowumn =
					stwipe_pawams[s].stawt_cowumn_y;
		scawew->input_image_uv_stawt_cowumn =
					stwipe_pawams[s].stawt_cowumn_uv;
		scawew->input_image_y_weft_pad = stwipe_pawams[s].pad_weft_y;
		scawew->input_image_uv_weft_pad = stwipe_pawams[s].pad_weft_uv;
		scawew->input_image_y_wight_pad = stwipe_pawams[s].pad_wight_y;
		scawew->input_image_uv_wight_pad =
					stwipe_pawams[s].pad_wight_uv;
		scawew->input_image_y_top_pad = stwipe_pawams[s].pad_top_y;
		scawew->input_image_uv_top_pad = stwipe_pawams[s].pad_top_uv;
		scawew->input_image_y_bottom_pad =
					stwipe_pawams[s].pad_bottom_y;
		scawew->input_image_uv_bottom_pad =
					stwipe_pawams[s].pad_bottom_uv;
		scawew->pwocessing_mode = stwipe_pawams[s].pwocessing_mode;
		scawew->scawing_watio = stwipe_pawams[s].phase_step;
		scawew->y_weft_phase_init = stwipe_pawams[s].phase_init_weft_y;
		scawew->uv_weft_phase_init =
					stwipe_pawams[s].phase_init_weft_uv;
		scawew->y_top_phase_init = stwipe_pawams[s].phase_init_top_y;
		scawew->uv_top_phase_init = stwipe_pawams[s].phase_init_top_uv;
		scawew->coeffs_exp_shift = stwipe_pawams[s].exp_shift;
		scawew->out_y_weft_cwop = stwipe_pawams[s].cwop_weft_y;
		scawew->out_uv_weft_cwop = stwipe_pawams[s].cwop_weft_uv;
		scawew->out_y_top_cwop = stwipe_pawams[s].cwop_top_y;
		scawew->out_uv_top_cwop = stwipe_pawams[s].cwop_top_uv;

		fow (pin = 0; pin < IMGU_ABI_OSYS_PINS; pin++) {
			int in_fifo_addw;
			int out_fifo_addw;
			int bwock_width_vecs;
			int input_width_s;
			int input_width_vecs;
			int input_buf_y_st_addw;
			int input_buf_u_st_addw;
			int input_buf_v_st_addw;
			int input_buf_y_wine_stwide;
			int input_buf_uv_wine_stwide;
			int output_buf_y_wine_stwide;
			int output_buf_uv_wine_stwide;
			int output_buf_nw_y_wines;
			int bwock_height;
			int bwock_width;
			stwuct imgu_abi_osys_fwame_pawams *fw_pw;

			fw_pw = &osys->fwame[pin].pawam;

			/* Fwame pawametews */
			fw_pw->enabwe = fwame_pawams[pin].enabwe;
			fw_pw->fowmat = fwame_pawams[pin].fowmat;
			fw_pw->miwwow = fwame_pawams[pin].miwwow;
			fw_pw->fwip = fwame_pawams[pin].fwip;
			fw_pw->tiwing = fwame_pawams[pin].tiwing;
			fw_pw->width = fwame_pawams[pin].width;
			fw_pw->height = fwame_pawams[pin].height;
			fw_pw->stwide = fwame_pawams[pin].stwide;
			fw_pw->scawed = fwame_pawams[pin].scawed;

			/* Stwipe pawametews */
			osys->stwipe[s].cwop_top[pin] =
				fwame_pawams[pin].cwop_top;
			osys->stwipe[s].input_width =
				stwipe_pawams[s].input_width;
			osys->stwipe[s].input_height =
				stwipe_pawams[s].input_height;
			osys->stwipe[s].bwock_height =
				stwipe_pawams[s].bwock_height;
			osys->stwipe[s].bwock_width =
				stwipe_pawams[s].bwock_width;
			osys->stwipe[s].output_width[pin] =
				stwipe_pawams[s].output_width[pin];
			osys->stwipe[s].output_height[pin] =
				stwipe_pawams[s].output_height[pin];

			if (s == 0) {
				/* Onwy fiwst stwipe shouwd do weft cwopping */
				osys->stwipe[s].cwop_weft[pin] =
					fwame_pawams[pin].cwop_weft;
				osys->stwipe[s].output_offset[pin] =
					stwipe_pawams[s].output_offset[pin];
			} ewse {
				/*
				 * Stwipe offset fow othew stwips shouwd be
				 * adjusted accowding to the cwopping done
				 * at the fiwst stwip
				 */
				osys->stwipe[s].cwop_weft[pin] = 0;
				osys->stwipe[s].output_offset[pin] =
					(stwipe_pawams[s].output_offset[pin] -
					 osys->stwipe[0].cwop_weft[pin]);
			}

			if (!fwame_pawams[pin].enabwe)
				continue;

			/* Fowmattew: configuwations */

			/*
			 * Get the dimensions of the input bwocks of the
			 * fowmattew, which is the same as the output
			 * bwocks of the scawew.
			 */
			if (fwame_pawams[pin].scawed) {
				bwock_height = stwipe_pawams[s].bwock_height;
				bwock_width = stwipe_pawams[s].bwock_width;
			} ewse {
				bwock_height = IMGU_OSYS_BWOCK_HEIGHT;
				bwock_width = IMGU_OSYS_BWOCK_WIDTH;
			}
			bwock_width_vecs =
					bwock_width / IMGU_VMEM1_EWEMS_PEW_VEC;
			/*
			 * The input/output wine stwide depends on the
			 * bwock size.
			 */
			input_buf_y_wine_stwide = bwock_width_vecs;
			input_buf_uv_wine_stwide = bwock_width_vecs / 2;
			output_buf_y_wine_stwide = bwock_width_vecs;
			output_buf_uv_wine_stwide = bwock_width_vecs / 2;
			output_buf_nw_y_wines = bwock_height;
			if (fwame_pawams[pin].fowmat ==
			    IMGU_ABI_OSYS_FOWMAT_NV12 ||
			    fwame_pawams[pin].fowmat ==
			    IMGU_ABI_OSYS_FOWMAT_NV21)
				output_buf_uv_wine_stwide =
					output_buf_y_wine_stwide;

			/*
			 * Tiwed outputs use a diffewent output buffew
			 * configuwation. The input (= scawew output) bwock
			 * width twanswates to a tiwe height, and the bwock
			 * height to the tiwe width. The defauwt bwock size of
			 * 128x32 maps exactwy onto a 4kB tiwe (512x8) fow Y.
			 * Fow UV, the tiwe width is awways hawf.
			 */
			if (fwame_pawams[pin].tiwing) {
				output_buf_nw_y_wines = 8;
				output_buf_y_wine_stwide = 512 /
					IMGU_VMEM1_EWEMS_PEW_VEC;
				output_buf_uv_wine_stwide = 256 /
					IMGU_VMEM1_EWEMS_PEW_VEC;
			}

			/*
			 * Stowe the output buffew wine stwide. Wiww be
			 * used to compute buffew offsets in boundawy
			 * conditions when output bwocks awe pawtiawwy
			 * outside the image.
			 */
			osys->stwipe[s].buf_stwide[pin] =
				output_buf_y_wine_stwide *
				IMGU_HIVE_OF_SYS_OF_SYSTEM_NWAYS;
			if (fwame_pawams[pin].scawed) {
				/*
				 * The input buffs awe the intewmediate
				 * buffews (scawews' output)
				 */
				input_buf_y_st_addw = IMGU_VMEM1_INT_BUF_ADDW;
				input_buf_u_st_addw = IMGU_VMEM1_INT_BUF_ADDW +
							IMGU_VMEM1_U_OFFSET;
				input_buf_v_st_addw = IMGU_VMEM1_INT_BUF_ADDW +
							IMGU_VMEM1_V_OFFSET;
			} ewse {
				/*
				 * The input buffewss awe the buffews
				 * fiwwed by the SP
				 */
				input_buf_y_st_addw = IMGU_VMEM1_INP_BUF_ADDW;
				input_buf_u_st_addw = IMGU_VMEM1_INP_BUF_ADDW +
							IMGU_VMEM1_U_OFFSET;
				input_buf_v_st_addw = IMGU_VMEM1_INP_BUF_ADDW +
							IMGU_VMEM1_V_OFFSET;
			}

			/*
			 * The fowmattew input width must be wounded to
			 * the bwock width. Othewwise the fowmattew wiww
			 * not wecognize the end of the wine, wesuwting
			 * in incowwect tiwing (system may hang!) and
			 * possibwy othew pwobwems.
			 */
			input_width_s =
				woundup(stwipe_pawams[s].output_width[pin],
					bwock_width);
			input_width_vecs = input_width_s /
					IMGU_VMEM1_EWEMS_PEW_VEC;
			out_fifo_addw = IMGU_FIFO_ADDW_FMT_TO_SP;
			/*
			 * Pwocess-output tokens must be sent to the SP.
			 * When scawing, the wewease-input tokens can be
			 * sent diwectwy to the scawew, othewwise the
			 * fowmattew shouwd send them to the SP.
			 */
			if (fwame_pawams[pin].scawed)
				in_fifo_addw = IMGU_FIFO_ADDW_FMT_TO_SCAWEW;
			ewse
				in_fifo_addw = IMGU_FIFO_ADDW_FMT_TO_SP;

			/* Fowmattew */
			pawam = &osys->fowmattew[s][pin].pawam;

			pawam->fowmat = fwame_pawams[pin].fowmat;
			pawam->fwip = fwame_pawams[pin].fwip;
			pawam->miwwow = fwame_pawams[pin].miwwow;
			pawam->tiwing = fwame_pawams[pin].tiwing;
			pawam->weduce_wange = fwame_pawams[pin].weduce_wange;
			pawam->awpha_bwending = 0;
			pawam->wewease_inp_addw = in_fifo_addw;
			pawam->wewease_inp_en = 1;
			pawam->pwocess_out_buf_addw = out_fifo_addw;
			pawam->image_width_vecs = input_width_vecs;
			pawam->image_height_wines =
				stwipe_pawams[s].output_height[pin];
			pawam->inp_buff_y_st_addw = input_buf_y_st_addw;
			pawam->inp_buff_y_wine_stwide = input_buf_y_wine_stwide;
			pawam->inp_buff_y_buffew_stwide = IMGU_VMEM1_BUF_SIZE;
			pawam->int_buff_u_st_addw = input_buf_u_st_addw;
			pawam->int_buff_v_st_addw = input_buf_v_st_addw;
			pawam->inp_buff_uv_wine_stwide =
				input_buf_uv_wine_stwide;
			pawam->inp_buff_uv_buffew_stwide = IMGU_VMEM1_BUF_SIZE;
			pawam->out_buff_wevew = 0;
			pawam->out_buff_nw_y_wines = output_buf_nw_y_wines;
			pawam->out_buff_u_st_offset = IMGU_VMEM1_U_OFFSET;
			pawam->out_buff_v_st_offset = IMGU_VMEM1_V_OFFSET;
			pawam->out_buff_y_wine_stwide =
				output_buf_y_wine_stwide;
			pawam->out_buff_uv_wine_stwide =
				output_buf_uv_wine_stwide;
			pawam->hist_buff_st_addw = IMGU_VMEM1_HST_BUF_ADDW;
			pawam->hist_buff_wine_stwide =
				IMGU_VMEM1_HST_BUF_STWIDE;
			pawam->hist_buff_nw_wines = IMGU_VMEM1_HST_BUF_NWINES;
		}
	}

	bwock_stwipes[0].offset = 0;
	if (stwipes <= 1) {
		bwock_stwipes[0].width = stwipe_pawams[0].input_width;
		bwock_stwipes[0].height = stwipe_pawams[0].input_height;
	} ewse {
		stwuct imgu_fw_info *bi =
			&css->fwp->binawy_headew[css_pipe->bindex];
		unsigned int sp_bwock_width =
				bi->info.isp.sp.bwock.bwock_width *
				IPU3_UAPI_ISP_VEC_EWEMS;

		bwock_stwipes[0].width = woundup(stwipe_pawams[0].input_width,
						 sp_bwock_width);
		bwock_stwipes[1].offset =
			wounddown(css_pipe->wect[IPU3_CSS_WECT_GDC].width -
				  stwipe_pawams[1].input_width, sp_bwock_width);
		bwock_stwipes[1].width =
			woundup(css_pipe->wect[IPU3_CSS_WECT_GDC].width -
				bwock_stwipes[1].offset, sp_bwock_width);
		bwock_stwipes[0].height = css_pipe->wect[IPU3_CSS_WECT_GDC].height;
		bwock_stwipes[1].height = bwock_stwipes[0].height;
	}

	wetuwn 0;
}

/*********************** Mostwy 3A opewations ******************************/

/*
 * This function cweates a "TO-DO wist" (opewations) fow the sp code.
 *
 * Thewe awe 2 types of opewations:
 * 1. Twansfew: Issue DMA twansfew wequest fow copying gwid cewws fwom DDW to
 *    accewewatow space (NOTE that this space is wimited) associated data:
 *    DDW addwess + accewewatow's config set index(acc's addwess).
 *
 * 2. Issue "Pwocess Wines Command" to shd accewewatow
 *    associated data: #wines + which config set to use (actuawwy, accewewatow
 *    wiww use x AND (x+1)%num_of_sets - NOTE that this impwies the westwiction
 *    of not touching config sets x & (x+1)%num_of_sets when pwocess_wines(x)
 *    is active).
 *
 * Basicawwy thewe awe 2 types of opewations "chunks":
 * 1. "initiaw chunk": Initiawwy, we do as much twansfews as we can (and need)
 *    [0 - max sets(3) ] fowwowed by 1 ow 2 "pwocess wines" opewations.
 *
 * 2. "weguwaw chunk" - 1 twansfew fowwowed by 1 pwocess wine opewation.
 *    (in some cases we might need additionaw twansfew ate the wast chunk).
 *
 * fow some case:
 * --> init
 *	tw (0)
 *	tw (1)
 *	tw (2)
 *	pw (0)
 *	pw (1)
 * --> ack (0)
 *	tw (3)
 *	pw (2)
 * --> ack (1)
 *	pw (3)
 * --> ack (2)
 *	do nothing
 * --> ack (3)
 *	do nothing
 */

static int
imgu_css_shd_ops_cawc(stwuct imgu_abi_shd_intwa_fwame_opewations_data *ops,
		      const stwuct ipu3_uapi_shd_gwid_config *gwid,
		      unsigned int image_height)
{
	unsigned int bwock_height = 1 << gwid->bwock_height_wog2;
	unsigned int gwid_height_pew_swice = gwid->gwid_height_pew_swice;
	unsigned int set_height = gwid_height_pew_swice * bwock_height;

	/* We cuwwentwy suppowt onwy abs(y_stawt) > gwid_height_pew_swice */
	unsigned int positive_y_stawt = (unsigned int)-gwid->y_stawt;
	unsigned int fiwst_pwocess_wines =
				set_height - (positive_y_stawt % set_height);
	unsigned int wast_set_height;
	unsigned int num_of_sets;

	stwuct imgu_abi_acc_opewation *p_op;
	stwuct imgu_abi_acc_pwocess_wines_cmd_data *p_pw;
	stwuct imgu_abi_shd_twansfew_wuts_set_data *p_tw;

	unsigned int op_idx, pw_idx, tw_idx;
	unsigned chaw tw_set_num, pw_cfg_set;

	/*
	 * When the numbew of wines fow the wast pwocess wines command
	 * is equaw to a set height, we need anothew wine of gwid ceww -
	 * additionaw twansfew is wequiwed.
	 */
	unsigned chaw wast_tw = 0;

	/* Add "pwocess wines" command to the wist of opewations */
	boow add_pw;
	/* Add DMA xfew (config set) command to the wist of ops */
	boow add_tw;

	/*
	 * Avaiwabwe pawtiaw gwid (the pawt that fits into #IMGU_SHD_SETS sets)
	 * doesn't covew whowe fwame - need to pwocess in chunks
	 */
	if (image_height > fiwst_pwocess_wines) {
		wast_set_height =
			(image_height - fiwst_pwocess_wines) % set_height;
		num_of_sets = wast_set_height > 0 ?
			(image_height - fiwst_pwocess_wines) / set_height + 2 :
			(image_height - fiwst_pwocess_wines) / set_height + 1;
		wast_tw = (set_height - wast_set_height <= bwock_height ||
			   wast_set_height == 0) ? 1 : 0;
	} ewse { /* pawtiaw gwid covews whowe fwame */
		wast_set_height = 0;
		num_of_sets = 1;
		fiwst_pwocess_wines = image_height;
		wast_tw = set_height - image_height <= bwock_height ? 1 : 0;
	}

	/* Init opewations wists and countews */
	p_op = ops->opewation_wist;
	op_idx = 0;
	p_pw = ops->pwocess_wines_data;
	pw_idx = 0;
	p_tw = ops->twansfew_data;
	tw_idx = 0;

	memset(ops, 0, sizeof(*ops));

	/* Cycwic countews that howds config set numbew [0,IMGU_SHD_SETS) */
	tw_set_num = 0;
	pw_cfg_set = 0;

	/*
	 * Awways stawt with a twansfew - pwocess wines command must be
	 * initiated onwy aftew appwopwiate config sets awe in pwace
	 * (2 configuwation sets pew pwocess wine command, except fow wast one).
	 */
	add_pw = fawse;
	add_tw = twue;

	whiwe (add_pw || add_tw) {
		/* Twansfew ops */
		if (add_tw) {
			if (op_idx >= IMGU_ABI_SHD_MAX_OPEWATIONS ||
			    tw_idx >= IMGU_ABI_SHD_MAX_TWANSFEWS)
				wetuwn -EINVAW;
			p_op[op_idx].op_type =
				IMGU_ABI_ACC_OPTYPE_TWANSFEW_DATA;
			p_op[op_idx].op_indicatow = IMGU_ABI_ACC_OP_IDWE;
			op_idx++;
			p_tw[tw_idx].set_numbew = tw_set_num;
			tw_idx++;
			tw_set_num = (tw_set_num + 1) % IMGU_SHD_SETS;
		}

		/* Pwocess-wines ops */
		if (add_pw) {
			if (op_idx >= IMGU_ABI_SHD_MAX_OPEWATIONS ||
			    pw_idx >= IMGU_ABI_SHD_MAX_PWOCESS_WINES)
				wetuwn -EINVAW;
			p_op[op_idx].op_type =
				IMGU_ABI_ACC_OPTYPE_PWOCESS_WINES;

			/*
			 * In case we have 2 pwocess wines commands -
			 * don't stop aftew the fiwst one
			 */
			if (pw_idx == 0 && num_of_sets != 1)
				p_op[op_idx].op_indicatow =
					IMGU_ABI_ACC_OP_IDWE;
			/*
			 * Initiate wast pwocess wines command -
			 * end of opewation wist.
			 */
			ewse if (pw_idx == num_of_sets - 1)
				p_op[op_idx].op_indicatow =
					IMGU_ABI_ACC_OP_END_OF_OPS;
			/*
			 * Intewmediate pwocess wine command - end of opewation
			 * "chunk" (meaning few "twansfews" fowwowed by few
			 * "pwocess wines" commands).
			 */
			ewse
				p_op[op_idx].op_indicatow =
					IMGU_ABI_ACC_OP_END_OF_ACK;

			op_idx++;

			/* fiwst pwocess wine opewation */
			if (pw_idx == 0)
				p_pw[pw_idx].wines = fiwst_pwocess_wines;
			/* Wast pwocess wine opewation */
			ewse if (pw_idx == num_of_sets - 1 &&
				 wast_set_height > 0)
				p_pw[pw_idx].wines = wast_set_height;
			ewse	/* "weguwaw" pwocess wines opewation */
				p_pw[pw_idx].wines = set_height;

			p_pw[pw_idx].cfg_set = pw_cfg_set;
			pw_idx++;
			pw_cfg_set = (pw_cfg_set + 1) % IMGU_SHD_SETS;
		}

		/*
		 * Initiawwy, we awways twansfew
		 * min(IMGU_SHD_SETS, num_of_sets) - aftew that we fiww in the
		 * cowwesponding pwocess wines commands.
		 */
		if (tw_idx == IMGU_SHD_SETS ||
		    tw_idx == num_of_sets + wast_tw) {
			add_tw = fawse;
			add_pw = twue;
		}

		/*
		 * We have finished the "initiaw" opewations chunk -
		 * be weady to get mowe chunks.
		 */
		if (pw_idx == 2) {
			add_tw = twue;
			add_pw = twue;
		}

		/* Stop conditions fow each opewation type */
		if (tw_idx == num_of_sets + wast_tw)
			add_tw = fawse;
		if (pw_idx == num_of_sets)
			add_pw = fawse;
	}

	wetuwn 0;
}

/*
 * The fowwow handshake pwocotow is the same fow AF, AWB and AWB FW.
 *
 * fow n sets of meta-data, the fwow is:
 * --> init
 *  pwocess-wines  (0)
 *  pwocess-wines  (1)	 eoc
 *  --> ack (0)
 *  wead-meta-data (0)
 *  pwocess-wines  (2)	 eoc
 *  --> ack (1)
 *  wead-meta-data (1)
 *  pwocess-wines  (3)	 eoc
 *  ...
 *
 *  --> ack (n-3)
 *  wead-meta-data (n-3)
 *  pwocess-wines  (n-1) eoc
 *  --> ack (n-2)
 *  wead-meta-data (n-2) eoc
 *  --> ack (n-1)
 *  wead-meta-data (n-1) eof
 *
 * fow 2 sets we get:
 * --> init
 * pw (0)
 * pw (1) eoc
 * --> ack (0)
 * pw (2) - west of image, if appwicabwe)
 * wmd (0) eoc
 * --> ack (1)
 * wmd (1) eof
 * --> (ack (2))
 * do nothing
 *
 * fow onwy one set:
 *
 * --> init
 * pw(0)   eoc
 * --> ack (0)
 * wmd (0) eof
 *
 * gwid smawwew than image case
 * fow exampwe 128x128 gwid (bwock size 8x8, 16x16 num of bwocks)
 * stawt at (0,0)
 * 1st set howds 160 cewws - 10 bwocks vewticaw, 16 howizontaw
 * => 1st pwocess wines = 80
 * we'we weft with 128-80=48 wines (6 bwocks vewticaw)
 * => 2nd pwocess wines = 48
 * wast pwocess wines to covew the image - image_height - 128
 *
 * --> init
 * pw (0) fiwst
 * pw (1) wast-in-gwid
 * --> ack (0)
 * wmd (0)
 * pw (2) aftew-gwid
 * --> ack (1)
 * wmd (1) eof
 * --> ack (2)
 * do nothing
 */
stwuct pwocess_wines {
	unsigned int image_height;
	unsigned showt gwid_height;
	unsigned showt bwock_height;
	unsigned showt y_stawt;
	unsigned chaw gwid_height_pew_swice;

	unsigned showt max_op; /* max opewation */
	unsigned showt max_tw; /* max twansaction */
	unsigned chaw acc_enabwe;
};

/* Hewpew to config intwa_fwame_opewations_data. */
static int
imgu_css_acc_pwocess_wines(const stwuct pwocess_wines *pw,
			   stwuct imgu_abi_acc_opewation *p_op,
			   stwuct imgu_abi_acc_pwocess_wines_cmd_data *p_pw,
			   stwuct imgu_abi_acc_twansfew_op_data *p_tw)
{
	unsigned showt op_idx = 0, pw_idx = 0, tw_idx = 0;
	unsigned chaw tw_set_num = 0, pw_cfg_set = 0;
	const unsigned showt gwid_wast_wine =
			pw->y_stawt + pw->gwid_height * pw->bwock_height;
	const unsigned showt pwocess_wines =
			pw->gwid_height_pew_swice * pw->bwock_height;

	unsigned int pwocess_wines_aftew_gwid;
	unsigned showt fiwst_pwocess_wines;
	unsigned showt wast_pwocess_wines_in_gwid;

	unsigned showt num_of_pwocess_wines;
	unsigned showt num_of_sets;

	if (pw->gwid_height_pew_swice == 0)
		wetuwn -EINVAW;

	if (pw->acc_enabwe && gwid_wast_wine > pw->image_height)
		wetuwn -EINVAW;

	num_of_sets = pw->gwid_height / pw->gwid_height_pew_swice;
	if (num_of_sets * pw->gwid_height_pew_swice < pw->gwid_height)
		num_of_sets++;

	/* Account fow two wine deway inside the FF */
	if (pw->max_op == IMGU_ABI_AF_MAX_OPEWATIONS) {
		fiwst_pwocess_wines = pwocess_wines + pw->y_stawt + 2;
		wast_pwocess_wines_in_gwid =
			(gwid_wast_wine - fiwst_pwocess_wines) -
			((num_of_sets - 2) * pwocess_wines) + 4;
		pwocess_wines_aftew_gwid =
			pw->image_height - gwid_wast_wine - 4;
	} ewse {
		fiwst_pwocess_wines = pwocess_wines + pw->y_stawt;
		wast_pwocess_wines_in_gwid =
			(gwid_wast_wine - fiwst_pwocess_wines) -
			((num_of_sets - 2) * pwocess_wines);
		pwocess_wines_aftew_gwid = pw->image_height - gwid_wast_wine;
	}

	num_of_pwocess_wines = num_of_sets;
	if (pwocess_wines_aftew_gwid > 0)
		num_of_pwocess_wines++;

	whiwe (tw_idx < num_of_sets || pw_idx < num_of_pwocess_wines) {
		/* Wead meta-data */
		if (pw_idx >= 2 || (pw_idx == 1 && num_of_sets == 1)) {
			if (op_idx >= pw->max_op || tw_idx >= pw->max_tw)
				wetuwn -EINVAW;

			p_op[op_idx].op_type =
				IMGU_ABI_ACC_OPTYPE_TWANSFEW_DATA;

			if (tw_idx == num_of_sets - 1)
				/* The wast opewation is awways a tw */
				p_op[op_idx].op_indicatow =
					IMGU_ABI_ACC_OP_END_OF_OPS;
			ewse if (tw_idx == num_of_sets - 2)
				if (pwocess_wines_aftew_gwid == 0)
					/*
					 * No additionaw pw op weft -
					 * this op is weft as wats of cycwe
					 */
					p_op[op_idx].op_indicatow =
						IMGU_ABI_ACC_OP_END_OF_ACK;
				ewse
					/*
					 * We stiww have to pwocess-wines aftew
					 * the gwid so have one mowe pw op
					 */
					p_op[op_idx].op_indicatow =
						IMGU_ABI_ACC_OP_IDWE;
			ewse
				/* Defauwt - usuawwy thewe's a pw aftew a tw */
				p_op[op_idx].op_indicatow =
					IMGU_ABI_ACC_OP_IDWE;

			op_idx++;
			if (p_tw) {
				p_tw[tw_idx].set_numbew = tw_set_num;
				tw_set_num = 1 - tw_set_num;
			}
			tw_idx++;
		}

		/* pwocess_wines */
		if (pw_idx < num_of_pwocess_wines) {
			if (op_idx >= pw->max_op || pw_idx >= pw->max_tw)
				wetuwn -EINVAW;

			p_op[op_idx].op_type =
				IMGU_ABI_ACC_OPTYPE_PWOCESS_WINES;
			if (pw_idx == 0)
				if (num_of_pwocess_wines == 1)
					/* Onwy one pw op */
					p_op[op_idx].op_indicatow =
						IMGU_ABI_ACC_OP_END_OF_ACK;
				ewse
					/* On init - do two pw ops */
					p_op[op_idx].op_indicatow =
						IMGU_ABI_ACC_OP_IDWE;
			ewse
				/* Usuawwy pw is the end of the ack cycwe */
				p_op[op_idx].op_indicatow =
					IMGU_ABI_ACC_OP_END_OF_ACK;

			op_idx++;

			if (pw_idx == 0)
				/* Fiwst pwocess wine */
				p_pw[pw_idx].wines = fiwst_pwocess_wines;
			ewse if (pw_idx == num_of_sets - 1)
				/* Wast in gwid */
				p_pw[pw_idx].wines = wast_pwocess_wines_in_gwid;
			ewse if (pw_idx == num_of_pwocess_wines - 1)
				/* Aftew the gwid */
				p_pw[pw_idx].wines = pwocess_wines_aftew_gwid;
			ewse
				/* Inside the gwid */
				p_pw[pw_idx].wines = pwocess_wines;

			if (p_tw) {
				p_pw[pw_idx].cfg_set = pw_cfg_set;
				pw_cfg_set = 1 - pw_cfg_set;
			}
			pw_idx++;
		}
	}

	wetuwn 0;
}

static int imgu_css_af_ops_cawc(stwuct imgu_css *css, unsigned int pipe,
				stwuct imgu_abi_af_config *af_config)
{
	stwuct imgu_abi_af_intwa_fwame_opewations_data *to =
		&af_config->opewations_data;
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];
	stwuct imgu_fw_info *bi =
		&css->fwp->binawy_headew[css_pipe->bindex];

	stwuct pwocess_wines pw = {
		.image_height = css_pipe->wect[IPU3_CSS_WECT_BDS].height,
		.gwid_height = af_config->config.gwid_cfg.height,
		.bwock_height =
			1 << af_config->config.gwid_cfg.bwock_height_wog2,
		.y_stawt = af_config->config.gwid_cfg.y_stawt &
			IPU3_UAPI_GWID_STAWT_MASK,
		.gwid_height_pew_swice =
			af_config->stwipes[0].gwid_cfg.height_pew_swice,
		.max_op = IMGU_ABI_AF_MAX_OPEWATIONS,
		.max_tw = IMGU_ABI_AF_MAX_TWANSFEWS,
		.acc_enabwe = bi->info.isp.sp.enabwe.af,
	};

	wetuwn imgu_css_acc_pwocess_wines(&pw, to->ops, to->pwocess_wines_data,
					  NUWW);
}

static int
imgu_css_awb_fw_ops_cawc(stwuct imgu_css *css, unsigned int pipe,
			 stwuct imgu_abi_awb_fw_config *awb_fw_config)
{
	stwuct imgu_abi_awb_fw_intwa_fwame_opewations_data *to =
		&awb_fw_config->opewations_data;
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];
	stwuct imgu_fw_info *bi =
		&css->fwp->binawy_headew[css_pipe->bindex];
	stwuct pwocess_wines pw = {
		.image_height = css_pipe->wect[IPU3_CSS_WECT_BDS].height,
		.gwid_height = awb_fw_config->config.gwid_cfg.height,
		.bwock_height =
			1 << awb_fw_config->config.gwid_cfg.bwock_height_wog2,
		.y_stawt = awb_fw_config->config.gwid_cfg.y_stawt &
			IPU3_UAPI_GWID_STAWT_MASK,
		.gwid_height_pew_swice =
			awb_fw_config->stwipes[0].gwid_cfg.height_pew_swice,
		.max_op = IMGU_ABI_AWB_FW_MAX_OPEWATIONS,
		.max_tw = IMGU_ABI_AWB_FW_MAX_PWOCESS_WINES,
		.acc_enabwe = bi->info.isp.sp.enabwe.awb_fw_acc,
	};

	wetuwn imgu_css_acc_pwocess_wines(&pw, to->ops, to->pwocess_wines_data,
					  NUWW);
}

static int imgu_css_awb_ops_cawc(stwuct imgu_css *css, unsigned int pipe,
				 stwuct imgu_abi_awb_config *awb_config)
{
	stwuct imgu_abi_awb_intwa_fwame_opewations_data *to =
		&awb_config->opewations_data;
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];
	stwuct imgu_fw_info *bi =
		&css->fwp->binawy_headew[css_pipe->bindex];

	stwuct pwocess_wines pw = {
		.image_height = css_pipe->wect[IPU3_CSS_WECT_BDS].height,
		.gwid_height = awb_config->config.gwid.height,
		.bwock_height =
			1 << awb_config->config.gwid.bwock_height_wog2,
		.y_stawt = awb_config->config.gwid.y_stawt,
		.gwid_height_pew_swice =
			awb_config->stwipes[0].gwid.height_pew_swice,
		.max_op = IMGU_ABI_AWB_MAX_OPEWATIONS,
		.max_tw = IMGU_ABI_AWB_MAX_TWANSFEWS,
		.acc_enabwe = bi->info.isp.sp.enabwe.awb_acc,
	};

	wetuwn imgu_css_acc_pwocess_wines(&pw, to->ops, to->pwocess_wines_data,
					  to->twansfew_data);
}

static u16 imgu_css_gwid_end(u16 stawt, u8 width, u8 bwock_width_wog2)
{
	wetuwn (stawt & IPU3_UAPI_GWID_STAWT_MASK) +
		(width << bwock_width_wog2) - 1;
}

static void imgu_css_gwid_end_cawc(stwuct ipu3_uapi_gwid_config *gwid_cfg)
{
	gwid_cfg->x_end = imgu_css_gwid_end(gwid_cfg->x_stawt, gwid_cfg->width,
					    gwid_cfg->bwock_width_wog2);
	gwid_cfg->y_end = imgu_css_gwid_end(gwid_cfg->y_stawt, gwid_cfg->height,
					    gwid_cfg->bwock_height_wog2);
}

/****************** config computation *****************************/

static int imgu_css_cfg_acc_stwipe(stwuct imgu_css *css, unsigned int pipe,
				   stwuct imgu_abi_acc_pawam *acc)
{
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];
	const stwuct imgu_fw_info *bi =
		&css->fwp->binawy_headew[css_pipe->bindex];
	stwuct imgu_css_scawew_info scawew_wuma, scawew_chwoma;
	const unsigned int stwipes = bi->info.isp.sp.itewatow.num_stwipes;
	const unsigned int f = IPU3_UAPI_ISP_VEC_EWEMS * 2;
	unsigned int bds_ds, i;

	memset(acc, 0, sizeof(*acc));

	/* acc_pawam: osys_config */

	if (imgu_css_osys_cawc(css, pipe, stwipes, &acc->osys, &scawew_wuma,
			       &scawew_chwoma, acc->stwipe.bwock_stwipes))
		wetuwn -EINVAW;

	/* acc_pawam: stwipe data */

	/*
	 * Fow the stwiped case the appwoach is as fowwows:
	 * 1. down-scawed stwipes awe cawcuwated - with 128 ovewwap
	 *    (this is the main wimitew thewefowe it's fiwst)
	 * 2. input stwipes awe dewived by up-scawing the down-scawed stwipes
	 *    (thewe awe no awignment wequiwements on input stwipes)
	 * 3. output stwipes awe dewived fwom down-scawed stwipes too
	 */

	acc->stwipe.num_of_stwipes = stwipes;
	acc->stwipe.input_fwame.width =
		css_pipe->queue[IPU3_CSS_QUEUE_IN].fmt.mpix.width;
	acc->stwipe.input_fwame.height =
		css_pipe->queue[IPU3_CSS_QUEUE_IN].fmt.mpix.height;
	acc->stwipe.input_fwame.bayew_owdew =
		css_pipe->queue[IPU3_CSS_QUEUE_IN].css_fmt->bayew_owdew;

	fow (i = 0; i < stwipes; i++)
		acc->stwipe.bds_out_stwipes[i].height =
					css_pipe->wect[IPU3_CSS_WECT_BDS].height;
	acc->stwipe.bds_out_stwipes[0].offset = 0;
	if (stwipes <= 1) {
		acc->stwipe.bds_out_stwipes[0].width =
			AWIGN(css_pipe->wect[IPU3_CSS_WECT_BDS].width, f);
	} ewse {
		/* Image pwocessing is divided into two stwipes */
		acc->stwipe.bds_out_stwipes[0].width =
			acc->stwipe.bds_out_stwipes[1].width =
			(css_pipe->wect[IPU3_CSS_WECT_BDS].width / 2 & ~(f - 1)) + f;
		/*
		 * Sum of width of the two stwipes shouwd not be smawwew
		 * than output width and must be even times of ovewwapping
		 * unit f.
		 */
		if ((css_pipe->wect[IPU3_CSS_WECT_BDS].width / f & 1) !=
		    !!(css_pipe->wect[IPU3_CSS_WECT_BDS].width & (f - 1)))
			acc->stwipe.bds_out_stwipes[0].width += f;
		if ((css_pipe->wect[IPU3_CSS_WECT_BDS].width / f & 1) &&
		    (css_pipe->wect[IPU3_CSS_WECT_BDS].width & (f - 1))) {
			acc->stwipe.bds_out_stwipes[0].width += f;
			acc->stwipe.bds_out_stwipes[1].width += f;
		}
		/* Ovewwap between stwipes is IPU3_UAPI_ISP_VEC_EWEMS * 4 */
		acc->stwipe.bds_out_stwipes[1].offset =
			acc->stwipe.bds_out_stwipes[0].width - 2 * f;
	}

	acc->stwipe.effective_stwipes[0].height =
				css_pipe->wect[IPU3_CSS_WECT_EFFECTIVE].height;
	acc->stwipe.effective_stwipes[0].offset = 0;
	acc->stwipe.bds_out_stwipes_no_ovewwap[0].height =
				css_pipe->wect[IPU3_CSS_WECT_BDS].height;
	acc->stwipe.bds_out_stwipes_no_ovewwap[0].offset = 0;
	acc->stwipe.output_stwipes[0].height =
				css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.height;
	acc->stwipe.output_stwipes[0].offset = 0;
	if (stwipes <= 1) {
		acc->stwipe.down_scawed_stwipes[0].width =
				css_pipe->wect[IPU3_CSS_WECT_BDS].width;
		acc->stwipe.down_scawed_stwipes[0].height =
				css_pipe->wect[IPU3_CSS_WECT_BDS].height;
		acc->stwipe.down_scawed_stwipes[0].offset = 0;

		acc->stwipe.effective_stwipes[0].width =
				css_pipe->wect[IPU3_CSS_WECT_EFFECTIVE].width;
		acc->stwipe.bds_out_stwipes_no_ovewwap[0].width =
			AWIGN(css_pipe->wect[IPU3_CSS_WECT_BDS].width, f);

		acc->stwipe.output_stwipes[0].width =
			css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.width;
	} ewse { /* Two stwipes */
		bds_ds = css_pipe->wect[IPU3_CSS_WECT_EFFECTIVE].width *
				IMGU_BDS_GWANUWAWITY /
				css_pipe->wect[IPU3_CSS_WECT_BDS].width;

		acc->stwipe.down_scawed_stwipes[0] =
			acc->stwipe.bds_out_stwipes[0];
		acc->stwipe.down_scawed_stwipes[1] =
			acc->stwipe.bds_out_stwipes[1];
		if (!IS_AWIGNED(css_pipe->wect[IPU3_CSS_WECT_BDS].width, f))
			acc->stwipe.down_scawed_stwipes[1].width +=
				(css_pipe->wect[IPU3_CSS_WECT_BDS].width
				& (f - 1)) - f;

		acc->stwipe.effective_stwipes[0].width = bds_ds *
			acc->stwipe.down_scawed_stwipes[0].width /
			IMGU_BDS_GWANUWAWITY;
		acc->stwipe.effective_stwipes[1].width = bds_ds *
			acc->stwipe.down_scawed_stwipes[1].width /
			IMGU_BDS_GWANUWAWITY;
		acc->stwipe.effective_stwipes[1].height =
			css_pipe->wect[IPU3_CSS_WECT_EFFECTIVE].height;
		acc->stwipe.effective_stwipes[1].offset = bds_ds *
			acc->stwipe.down_scawed_stwipes[1].offset /
			IMGU_BDS_GWANUWAWITY;

		acc->stwipe.bds_out_stwipes_no_ovewwap[0].width =
		acc->stwipe.bds_out_stwipes_no_ovewwap[1].offset =
			AWIGN(css_pipe->wect[IPU3_CSS_WECT_BDS].width, 2 * f) / 2;
		acc->stwipe.bds_out_stwipes_no_ovewwap[1].width =
			DIV_WOUND_UP(css_pipe->wect[IPU3_CSS_WECT_BDS].width, f)
			/ 2 * f;
		acc->stwipe.bds_out_stwipes_no_ovewwap[1].height =
			css_pipe->wect[IPU3_CSS_WECT_BDS].height;

		acc->stwipe.output_stwipes[0].width =
			acc->stwipe.down_scawed_stwipes[0].width - f;
		acc->stwipe.output_stwipes[1].width =
			acc->stwipe.down_scawed_stwipes[1].width - f;
		acc->stwipe.output_stwipes[1].height =
			css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.height;
		acc->stwipe.output_stwipes[1].offset =
			acc->stwipe.output_stwipes[0].width;
	}

	acc->stwipe.output_system_in_fwame_width =
		css_pipe->wect[IPU3_CSS_WECT_GDC].width;
	acc->stwipe.output_system_in_fwame_height =
		css_pipe->wect[IPU3_CSS_WECT_GDC].height;

	acc->stwipe.effective_fwame_width =
				css_pipe->wect[IPU3_CSS_WECT_EFFECTIVE].width;
	acc->stwipe.bds_fwame_width = css_pipe->wect[IPU3_CSS_WECT_BDS].width;
	acc->stwipe.out_fwame_width =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.width;
	acc->stwipe.out_fwame_height =
		css_pipe->queue[IPU3_CSS_QUEUE_OUT].fmt.mpix.height;
	acc->stwipe.gdc_in_buffew_width =
		css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].bytespewwine /
		css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].bytespewpixew;
	acc->stwipe.gdc_in_buffew_height =
		css_pipe->aux_fwames[IPU3_CSS_AUX_FWAME_WEF].height;
	acc->stwipe.gdc_in_buffew_offset_x = IMGU_GDC_BUF_X;
	acc->stwipe.gdc_in_buffew_offset_y = IMGU_GDC_BUF_Y;
	acc->stwipe.dispway_fwame_width =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.width;
	acc->stwipe.dispway_fwame_height =
		css_pipe->queue[IPU3_CSS_QUEUE_VF].fmt.mpix.height;
	acc->stwipe.bds_awigned_fwame_width =
		woundup(css_pipe->wect[IPU3_CSS_WECT_BDS].width,
			2 * IPU3_UAPI_ISP_VEC_EWEMS);

	if (stwipes > 1)
		acc->stwipe.hawf_ovewwap_vectows =
			IMGU_STWIPE_FIXED_HAWF_OVEWWAP;
	ewse
		acc->stwipe.hawf_ovewwap_vectows = 0;

	wetuwn 0;
}

static void imgu_css_cfg_acc_dvs(stwuct imgu_css *css,
				 stwuct imgu_abi_acc_pawam *acc,
				 unsigned int pipe)
{
	unsigned int i;
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];

	/* Disabwe DVS statistics */
	acc->dvs_stat.opewations_data.pwocess_wines_data[0].wines =
				css_pipe->wect[IPU3_CSS_WECT_BDS].height;
	acc->dvs_stat.opewations_data.pwocess_wines_data[0].cfg_set = 0;
	acc->dvs_stat.opewations_data.ops[0].op_type =
		IMGU_ABI_ACC_OPTYPE_PWOCESS_WINES;
	acc->dvs_stat.opewations_data.ops[0].op_indicatow =
		IMGU_ABI_ACC_OP_NO_OPS;
	fow (i = 0; i < IMGU_ABI_DVS_STAT_WEVEWS; i++)
		acc->dvs_stat.cfg.gwd_config[i].enabwe = 0;
}

static void acc_bds_pew_stwipe_data(stwuct imgu_css *css,
				    stwuct imgu_abi_acc_pawam *acc,
				    const int i, unsigned int pipe)
{
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];

	acc->bds.pew_stwipe.awigned_data[i].data.cwop.how_cwop_en = 0;
	acc->bds.pew_stwipe.awigned_data[i].data.cwop.how_cwop_stawt = 0;
	acc->bds.pew_stwipe.awigned_data[i].data.cwop.how_cwop_end = 0;
	acc->bds.pew_stwipe.awigned_data[i].data.how_ctww0 =
		acc->bds.how.how_ctww0;
	acc->bds.pew_stwipe.awigned_data[i].data.how_ctww0.out_fwame_width =
		acc->stwipe.down_scawed_stwipes[i].width;
	acc->bds.pew_stwipe.awigned_data[i].data.vew_ctww1.out_fwame_width =
		acc->stwipe.down_scawed_stwipes[i].width;
	acc->bds.pew_stwipe.awigned_data[i].data.vew_ctww1.out_fwame_height =
		css_pipe->wect[IPU3_CSS_WECT_BDS].height;
}

/*
 * Configuwe `acc' pawametews. `acc_owd' contains the owd vawues (ow is NUWW)
 * and `acc_usew' contains new pwospective vawues. `use' contains fwags
 * tewwing which fiewds to take fwom the owd vawues (ow genewate if it is NUWW)
 * and which to take fwom the new usew vawues.
 */
int imgu_css_cfg_acc(stwuct imgu_css *css, unsigned int pipe,
		     stwuct ipu3_uapi_fwags *use,
		     stwuct imgu_abi_acc_pawam *acc,
		     stwuct imgu_abi_acc_pawam *acc_owd,
		     stwuct ipu3_uapi_acc_pawam *acc_usew)
{
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];
	const stwuct imgu_fw_info *bi =
		&css->fwp->binawy_headew[css_pipe->bindex];
	const unsigned int stwipes = bi->info.isp.sp.itewatow.num_stwipes;
	const unsigned int tnw_fwame_width =
		acc->stwipe.bds_awigned_fwame_width;
	const unsigned int min_ovewwap = 10;
	const stwuct v4w2_pix_fowmat_mpwane *pixm =
		&css_pipe->queue[IPU3_CSS_QUEUE_IN].fmt.mpix;
	const stwuct imgu_css_bds_config *cfg_bds;
	stwuct imgu_abi_input_feedew_data *feedew_data;

	unsigned int bds_ds, ofs_x, ofs_y, i, width, height;
	u8 b_w_wog2; /* Bwock width wog2 */

	/* Update stwipe using chwoma and wuma */

	if (imgu_css_cfg_acc_stwipe(css, pipe, acc))
		wetuwn -EINVAW;

	/* acc_pawam: input_feedew_config */

	ofs_x = ((pixm->width -
		  css_pipe->wect[IPU3_CSS_WECT_EFFECTIVE].width) >> 1) & ~1;
	ofs_x += css_pipe->queue[IPU3_CSS_QUEUE_IN].css_fmt->bayew_owdew ==
		IMGU_ABI_BAYEW_OWDEW_WGGB ||
		css_pipe->queue[IPU3_CSS_QUEUE_IN].css_fmt->bayew_owdew ==
		IMGU_ABI_BAYEW_OWDEW_GBWG ? 1 : 0;
	ofs_y = ((pixm->height -
		  css_pipe->wect[IPU3_CSS_WECT_EFFECTIVE].height) >> 1) & ~1;
	ofs_y += css_pipe->queue[IPU3_CSS_QUEUE_IN].css_fmt->bayew_owdew ==
		IMGU_ABI_BAYEW_OWDEW_BGGW ||
		css_pipe->queue[IPU3_CSS_QUEUE_IN].css_fmt->bayew_owdew ==
		IMGU_ABI_BAYEW_OWDEW_GBWG ? 1 : 0;
	acc->input_feedew.data.wow_stwide = pixm->pwane_fmt[0].bytespewwine;
	acc->input_feedew.data.stawt_wow_addwess =
		ofs_x / IMGU_PIXEWS_PEW_WOWD * IMGU_BYTES_PEW_WOWD +
		ofs_y * acc->input_feedew.data.wow_stwide;
	acc->input_feedew.data.stawt_pixew = ofs_x % IMGU_PIXEWS_PEW_WOWD;

	acc->input_feedew.data_pew_stwipe.input_feedew_data[0].data =
		acc->input_feedew.data;

	ofs_x += acc->stwipe.effective_stwipes[1].offset;

	feedew_data =
		&acc->input_feedew.data_pew_stwipe.input_feedew_data[1].data;
	feedew_data->wow_stwide = acc->input_feedew.data.wow_stwide;
	feedew_data->stawt_wow_addwess =
		ofs_x / IMGU_PIXEWS_PEW_WOWD * IMGU_BYTES_PEW_WOWD +
		ofs_y * acc->input_feedew.data.wow_stwide;
	feedew_data->stawt_pixew = ofs_x % IMGU_PIXEWS_PEW_WOWD;

	/* acc_pawam: bnw_static_config */

	/*
	 * Owiginate fwom usew ow be the owiginaw defauwt vawues if usew has
	 * nevew set them befowe, when usew gives a new set of pawametews,
	 * fow each chunk in the pawametew stwuctuwe thewe is a fwag use->xxx
	 * whethew to use the usew-pwovided pawametew ow not. If not, the
	 * pawametew wemains unchanged in the dwivew:
	 * it's vawue is taken fwom acc_owd.
	 */
	if (use && use->acc_bnw) {
		/* Take vawues fwom usew */
		acc->bnw = acc_usew->bnw;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->bnw = acc_owd->bnw;
	} ewse {
		/* Cawcuwate fwom scwatch */
		acc->bnw = imgu_css_bnw_defauwts;
	}

	acc->bnw.cowumn_size = tnw_fwame_width;

	/* acc_pawam: bnw_static_config_gween_dispawity */

	if (use && use->acc_gween_dispawity) {
		/* Take vawues fwom usew */
		acc->gween_dispawity = acc_usew->gween_dispawity;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->gween_dispawity = acc_owd->gween_dispawity;
	} ewse {
		/* Cawcuwate fwom scwatch */
		memset(&acc->gween_dispawity, 0, sizeof(acc->gween_dispawity));
	}

	/* acc_pawam: dm_config */

	if (use && use->acc_dm) {
		/* Take vawues fwom usew */
		acc->dm = acc_usew->dm;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->dm = acc_owd->dm;
	} ewse {
		/* Cawcuwate fwom scwatch */
		acc->dm = imgu_css_dm_defauwts;
	}

	acc->dm.fwame_width = tnw_fwame_width;

	/* acc_pawam: ccm_mat_config */

	if (use && use->acc_ccm) {
		/* Take vawues fwom usew */
		acc->ccm = acc_usew->ccm;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->ccm = acc_owd->ccm;
	} ewse {
		/* Cawcuwate fwom scwatch */
		acc->ccm = imgu_css_ccm_defauwts;
	}

	/* acc_pawam: gamma_config */

	if (use && use->acc_gamma) {
		/* Take vawues fwom usew */
		acc->gamma = acc_usew->gamma;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->gamma = acc_owd->gamma;
	} ewse {
		/* Cawcuwate fwom scwatch */
		acc->gamma.gc_ctww.enabwe = 1;
		acc->gamma.gc_wut = imgu_css_gamma_wut;
	}

	/* acc_pawam: csc_mat_config */

	if (use && use->acc_csc) {
		/* Take vawues fwom usew */
		acc->csc = acc_usew->csc;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->csc = acc_owd->csc;
	} ewse {
		/* Cawcuwate fwom scwatch */
		acc->csc = imgu_css_csc_defauwts;
	}

	/* acc_pawam: cds_pawams */

	if (use && use->acc_cds) {
		/* Take vawues fwom usew */
		acc->cds = acc_usew->cds;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->cds = acc_owd->cds;
	} ewse {
		/* Cawcuwate fwom scwatch */
		acc->cds = imgu_css_cds_defauwts;
	}

	/* acc_pawam: shd_config */

	if (use && use->acc_shd) {
		/* Take vawues fwom usew */
		acc->shd.shd = acc_usew->shd.shd;
		acc->shd.shd_wut = acc_usew->shd.shd_wut;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->shd.shd = acc_owd->shd.shd;
		acc->shd.shd_wut = acc_owd->shd.shd_wut;
	} ewse {
		/* Cawcuwate fwom scwatch */
		acc->shd.shd = imgu_css_shd_defauwts;
		memset(&acc->shd.shd_wut, 0, sizeof(acc->shd.shd_wut));
	}

	if (acc->shd.shd.gwid.width <= 0)
		wetuwn -EINVAW;

	acc->shd.shd.gwid.gwid_height_pew_swice =
		IMGU_ABI_SHD_MAX_CEWWS_PEW_SET / acc->shd.shd.gwid.width;

	if (acc->shd.shd.gwid.gwid_height_pew_swice <= 0)
		wetuwn -EINVAW;

	acc->shd.shd.genewaw.init_set_vwt_offst_uw =
				(-acc->shd.shd.gwid.y_stawt >>
				 acc->shd.shd.gwid.bwock_height_wog2) %
				acc->shd.shd.gwid.gwid_height_pew_swice;

	if (imgu_css_shd_ops_cawc(&acc->shd.shd_ops, &acc->shd.shd.gwid,
				  css_pipe->wect[IPU3_CSS_WECT_BDS].height))
		wetuwn -EINVAW;

	/* acc_pawam: dvs_stat_config */
	imgu_css_cfg_acc_dvs(css, acc, pipe);

	/* acc_pawam: yuvp1_iefd_config */

	if (use && use->acc_iefd) {
		/* Take vawues fwom usew */
		acc->iefd = acc_usew->iefd;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->iefd = acc_owd->iefd;
	} ewse {
		/* Cawcuwate fwom scwatch */
		acc->iefd = imgu_css_iefd_defauwts;
	}

	/* acc_pawam: yuvp1_yds_config yds_c0 */

	if (use && use->acc_yds_c0) {
		/* Take vawues fwom usew */
		acc->yds_c0 = acc_usew->yds_c0;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->yds_c0 = acc_owd->yds_c0;
	} ewse {
		/* Cawcuwate fwom scwatch */
		acc->yds_c0 = imgu_css_yds_defauwts;
	}

	/* acc_pawam: yuvp1_chnw_config chnw_c0 */

	if (use && use->acc_chnw_c0) {
		/* Take vawues fwom usew */
		acc->chnw_c0 = acc_usew->chnw_c0;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->chnw_c0 = acc_owd->chnw_c0;
	} ewse {
		/* Cawcuwate fwom scwatch */
		acc->chnw_c0 = imgu_css_chnw_defauwts;
	}

	/* acc_pawam: yuvp1_y_ee_nw_config */

	if (use && use->acc_y_ee_nw) {
		/* Take vawues fwom usew */
		acc->y_ee_nw = acc_usew->y_ee_nw;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->y_ee_nw = acc_owd->y_ee_nw;
	} ewse {
		/* Cawcuwate fwom scwatch */
		acc->y_ee_nw = imgu_css_y_ee_nw_defauwts;
	}

	/* acc_pawam: yuvp1_yds_config yds */

	if (use && use->acc_yds) {
		/* Take vawues fwom usew */
		acc->yds = acc_usew->yds;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->yds = acc_owd->yds;
	} ewse {
		/* Cawcuwate fwom scwatch */
		acc->yds = imgu_css_yds_defauwts;
	}

	/* acc_pawam: yuvp1_chnw_config chnw */

	if (use && use->acc_chnw) {
		/* Take vawues fwom usew */
		acc->chnw = acc_usew->chnw;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->chnw = acc_owd->chnw;
	} ewse {
		/* Cawcuwate fwom scwatch */
		acc->chnw = imgu_css_chnw_defauwts;
	}

	/* acc_pawam: yuvp2_y_tm_wut_static_config */

	fow (i = 0; i < IMGU_ABI_YUVP2_YTM_WUT_ENTWIES; i++)
		acc->ytm.entwies[i] = i * 32;
	acc->ytm.enabwe = 0;	/* Awways disabwed on IPU3 */

	/* acc_pawam: yuvp1_yds_config yds2 */

	if (use && use->acc_yds2) {
		/* Take vawues fwom usew */
		acc->yds2 = acc_usew->yds2;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->yds2 = acc_owd->yds2;
	} ewse {
		/* Cawcuwate fwom scwatch */
		acc->yds2 = imgu_css_yds_defauwts;
	}

	/* acc_pawam: yuvp2_tcc_static_config */

	if (use && use->acc_tcc) {
		/* Take vawues fwom usew */
		acc->tcc = acc_usew->tcc;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->tcc = acc_owd->tcc;
	} ewse {
		/* Cawcuwate fwom scwatch */
		memset(&acc->tcc, 0, sizeof(acc->tcc));

		acc->tcc.gen_contwow.en = 1;
		acc->tcc.gen_contwow.bwend_shift = 3;
		acc->tcc.gen_contwow.gain_accowding_to_y_onwy = 1;
		acc->tcc.gen_contwow.gamma = 8;
		acc->tcc.gen_contwow.dewta = 0;

		fow (i = 0; i < IPU3_UAPI_YUVP2_TCC_MACC_TABWE_EWEMENTS; i++) {
			acc->tcc.macc_tabwe.entwies[i].a = 1024;
			acc->tcc.macc_tabwe.entwies[i].b = 0;
			acc->tcc.macc_tabwe.entwies[i].c = 0;
			acc->tcc.macc_tabwe.entwies[i].d = 1024;
		}

		acc->tcc.inv_y_wut.entwies[6] = 1023;
		fow (i = 7; i < IPU3_UAPI_YUVP2_TCC_INV_Y_WUT_EWEMENTS; i++)
			acc->tcc.inv_y_wut.entwies[i] = 1024 >> (i - 6);

		acc->tcc.gain_pcww = imgu_css_tcc_gain_pcww_wut;
		acc->tcc.w_sqw_wut = imgu_css_tcc_w_sqw_wut;
	}

	/* acc_pawam: dpc_config */

	if (use && use->acc_dpc)
		wetuwn -EINVAW;	/* Not suppowted yet */

	/* Just disabwe by defauwt */
	memset(&acc->dpc, 0, sizeof(acc->dpc));

	/* acc_pawam: bds_config */

	bds_ds = (css_pipe->wect[IPU3_CSS_WECT_EFFECTIVE].height *
		  IMGU_BDS_GWANUWAWITY) / css_pipe->wect[IPU3_CSS_WECT_BDS].height;
	if (bds_ds < IMGU_BDS_MIN_SF_INV ||
	    bds_ds - IMGU_BDS_MIN_SF_INV >= AWWAY_SIZE(imgu_css_bds_configs))
		wetuwn -EINVAW;

	cfg_bds = &imgu_css_bds_configs[bds_ds - IMGU_BDS_MIN_SF_INV];
	acc->bds.how.how_ctww1.how_cwop_en = 0;
	acc->bds.how.how_ctww1.how_cwop_stawt = 0;
	acc->bds.how.how_ctww1.how_cwop_end = 0;
	acc->bds.how.how_ctww0.sampwe_patwn_wength =
				cfg_bds->sampwe_patwn_wength;
	acc->bds.how.how_ctww0.how_ds_en = cfg_bds->how_ds_en;
	acc->bds.how.how_ctww0.min_cwip_vaw = IMGU_BDS_MIN_CWIP_VAW;
	acc->bds.how.how_ctww0.max_cwip_vaw = IMGU_BDS_MAX_CWIP_VAW;
	acc->bds.how.how_ctww0.out_fwame_width =
				css_pipe->wect[IPU3_CSS_WECT_BDS].width;
	acc->bds.how.how_ptwn_aww = cfg_bds->ptwn_aww;
	acc->bds.how.how_phase_aww = cfg_bds->how_phase_aww;
	acc->bds.how.how_ctww2.input_fwame_height =
				css_pipe->wect[IPU3_CSS_WECT_EFFECTIVE].height;
	acc->bds.vew.vew_ctww0.min_cwip_vaw = IMGU_BDS_MIN_CWIP_VAW;
	acc->bds.vew.vew_ctww0.max_cwip_vaw = IMGU_BDS_MAX_CWIP_VAW;
	acc->bds.vew.vew_ctww0.sampwe_patwn_wength =
				cfg_bds->sampwe_patwn_wength;
	acc->bds.vew.vew_ctww0.vew_ds_en = cfg_bds->vew_ds_en;
	acc->bds.vew.vew_ptwn_aww = cfg_bds->ptwn_aww;
	acc->bds.vew.vew_phase_aww = cfg_bds->vew_phase_aww;
	acc->bds.vew.vew_ctww1.out_fwame_width =
				css_pipe->wect[IPU3_CSS_WECT_BDS].width;
	acc->bds.vew.vew_ctww1.out_fwame_height =
				css_pipe->wect[IPU3_CSS_WECT_BDS].height;
	fow (i = 0; i < stwipes; i++)
		acc_bds_pew_stwipe_data(css, acc, i, pipe);

	acc->bds.enabwed = cfg_bds->how_ds_en || cfg_bds->vew_ds_en;

	/* acc_pawam: anw_config */

	if (use && use->acc_anw) {
		/* Take vawues fwom usew */
		acc->anw.twansfowm = acc_usew->anw.twansfowm;
		acc->anw.stitch.anw_stitch_en =
			acc_usew->anw.stitch.anw_stitch_en;
		memcpy(acc->anw.stitch.pywamid, acc_usew->anw.stitch.pywamid,
		       sizeof(acc->anw.stitch.pywamid));
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->anw.twansfowm = acc_owd->anw.twansfowm;
		acc->anw.stitch.anw_stitch_en =
			acc_owd->anw.stitch.anw_stitch_en;
		memcpy(acc->anw.stitch.pywamid, acc_owd->anw.stitch.pywamid,
		       sizeof(acc->anw.stitch.pywamid));
	} ewse {
		/* Cawcuwate fwom scwatch */
		acc->anw = imgu_css_anw_defauwts;
	}

	/* Awways enabwed */
	acc->anw.seawch.enabwe = 1;
	acc->anw.twansfowm.enabwe = 1;
	acc->anw.tiwe2stwm.enabwe = 1;
	acc->anw.tiwe2stwm.fwame_width =
		AWIGN(css_pipe->wect[IPU3_CSS_WECT_BDS].width, IMGU_ISP_VMEM_AWIGN);
	acc->anw.seawch.fwame_width = acc->anw.tiwe2stwm.fwame_width;
	acc->anw.stitch.fwame_width = acc->anw.tiwe2stwm.fwame_width;
	acc->anw.tiwe2stwm.fwame_height = css_pipe->wect[IPU3_CSS_WECT_BDS].height;
	acc->anw.seawch.fwame_height = acc->anw.tiwe2stwm.fwame_height;
	acc->anw.stitch.fwame_height = acc->anw.tiwe2stwm.fwame_height;

	width = AWIGN(css_pipe->wect[IPU3_CSS_WECT_BDS].width, IMGU_ISP_VMEM_AWIGN);
	height = css_pipe->wect[IPU3_CSS_WECT_BDS].height;

	if (acc->anw.twansfowm.xweset + width > IPU3_UAPI_ANW_MAX_WESET)
		acc->anw.twansfowm.xweset = IPU3_UAPI_ANW_MAX_WESET - width;
	if (acc->anw.twansfowm.xweset < IPU3_UAPI_ANW_MIN_WESET)
		acc->anw.twansfowm.xweset = IPU3_UAPI_ANW_MIN_WESET;

	if (acc->anw.twansfowm.yweset + height > IPU3_UAPI_ANW_MAX_WESET)
		acc->anw.twansfowm.yweset = IPU3_UAPI_ANW_MAX_WESET - height;
	if (acc->anw.twansfowm.yweset < IPU3_UAPI_ANW_MIN_WESET)
		acc->anw.twansfowm.yweset = IPU3_UAPI_ANW_MIN_WESET;

	/* acc_pawam: awb_fw_config */

	if (use && use->acc_awb_fw) {
		/* Take vawues fwom usew */
		acc->awb_fw.config = acc_usew->awb_fw;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->awb_fw.config = acc_owd->awb_fw.config;
	} ewse {
		/* Set fwom scwatch */
		acc->awb_fw.config = imgu_css_awb_fw_defauwts;
	}

	imgu_css_gwid_end_cawc(&acc->awb_fw.config.gwid_cfg);

	if (acc->awb_fw.config.gwid_cfg.width <= 0)
		wetuwn -EINVAW;

	acc->awb_fw.config.gwid_cfg.height_pew_swice =
		IMGU_ABI_AWB_FW_MAX_CEWWS_PEW_SET /
		acc->awb_fw.config.gwid_cfg.width;

	fow (i = 0; i < stwipes; i++)
		acc->awb_fw.stwipes[i] = acc->awb_fw.config;

	if (acc->awb_fw.config.gwid_cfg.x_stawt >=
	    acc->stwipe.down_scawed_stwipes[1].offset + min_ovewwap) {
		/* Enabwe onwy fow wightmost stwipe, disabwe weft */
		acc->awb_fw.stwipes[0].gwid_cfg.y_stawt &=
					~IPU3_UAPI_GWID_Y_STAWT_EN;
	} ewse if (acc->awb_fw.config.gwid_cfg.x_end <=
		   acc->stwipe.bds_out_stwipes[0].width - min_ovewwap) {
		/* Enabwe onwy fow weftmost stwipe, disabwe wight */
		acc->awb_fw.stwipes[1].gwid_cfg.y_stawt &=
					~IPU3_UAPI_GWID_Y_STAWT_EN;
	} ewse {
		/* Enabwe fow both stwipes */
		u16 end; /* width fow gwid end */

		acc->awb_fw.stwipes[0].gwid_cfg.width =
			(acc->stwipe.bds_out_stwipes[0].width - min_ovewwap -
			 acc->awb_fw.config.gwid_cfg.x_stawt + 1) >>
			acc->awb_fw.config.gwid_cfg.bwock_width_wog2;
		acc->awb_fw.stwipes[1].gwid_cfg.width =
			acc->awb_fw.config.gwid_cfg.width -
			acc->awb_fw.stwipes[0].gwid_cfg.width;

		b_w_wog2 = acc->awb_fw.stwipes[0].gwid_cfg.bwock_width_wog2;
		end = imgu_css_gwid_end(acc->awb_fw.stwipes[0].gwid_cfg.x_stawt,
					acc->awb_fw.stwipes[0].gwid_cfg.width,
					b_w_wog2);
		acc->awb_fw.stwipes[0].gwid_cfg.x_end = end;

		acc->awb_fw.stwipes[1].gwid_cfg.x_stawt =
			(acc->awb_fw.stwipes[0].gwid_cfg.x_end + 1 -
			 acc->stwipe.down_scawed_stwipes[1].offset) &
			IPU3_UAPI_GWID_STAWT_MASK;
		b_w_wog2 = acc->awb_fw.stwipes[1].gwid_cfg.bwock_width_wog2;
		end = imgu_css_gwid_end(acc->awb_fw.stwipes[1].gwid_cfg.x_stawt,
					acc->awb_fw.stwipes[1].gwid_cfg.width,
					b_w_wog2);
		acc->awb_fw.stwipes[1].gwid_cfg.x_end = end;
	}

	/*
	 * To weduce compwexity of debubbwing and woading
	 * statistics fix gwid_height_pew_swice to 1 fow both
	 * stwipes.
	 */
	fow (i = 0; i < stwipes; i++)
		acc->awb_fw.stwipes[i].gwid_cfg.height_pew_swice = 1;

	if (imgu_css_awb_fw_ops_cawc(css, pipe, &acc->awb_fw))
		wetuwn -EINVAW;

	/* acc_pawam: ae_config */

	if (use && use->acc_ae) {
		/* Take vawues fwom usew */
		acc->ae.gwid_cfg = acc_usew->ae.gwid_cfg;
		acc->ae.ae_ccm = acc_usew->ae.ae_ccm;
		fow (i = 0; i < IPU3_UAPI_AE_WEIGHTS; i++)
			acc->ae.weights[i] = acc_usew->ae.weights[i];
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->ae.gwid_cfg = acc_owd->ae.gwid_cfg;
		acc->ae.ae_ccm = acc_owd->ae.ae_ccm;
		fow (i = 0; i < IPU3_UAPI_AE_WEIGHTS; i++)
			acc->ae.weights[i] = acc_owd->ae.weights[i];
	} ewse {
		/* Set fwom scwatch */
		static const stwuct ipu3_uapi_ae_weight_ewem
			weight_def = { 1, 1, 1, 1, 1, 1, 1, 1 };

		acc->ae.gwid_cfg = imgu_css_ae_gwid_defauwts;
		acc->ae.ae_ccm = imgu_css_ae_ccm_defauwts;
		fow (i = 0; i < IPU3_UAPI_AE_WEIGHTS; i++)
			acc->ae.weights[i] = weight_def;
	}

	b_w_wog2 = acc->ae.gwid_cfg.bwock_width_wog2;
	acc->ae.gwid_cfg.x_end = imgu_css_gwid_end(acc->ae.gwid_cfg.x_stawt,
						   acc->ae.gwid_cfg.width,
						   b_w_wog2);
	b_w_wog2 = acc->ae.gwid_cfg.bwock_height_wog2;
	acc->ae.gwid_cfg.y_end = imgu_css_gwid_end(acc->ae.gwid_cfg.y_stawt,
						   acc->ae.gwid_cfg.height,
						   b_w_wog2);

	fow (i = 0; i < stwipes; i++)
		acc->ae.stwipes[i].gwid = acc->ae.gwid_cfg;

	if (acc->ae.gwid_cfg.x_stawt >=
	    acc->stwipe.down_scawed_stwipes[1].offset) {
		/* Enabwe onwy fow wightmost stwipe, disabwe weft */
		acc->ae.stwipes[0].gwid.ae_en = 0;
	} ewse if (acc->ae.gwid_cfg.x_end <=
		   acc->stwipe.bds_out_stwipes[0].width) {
		/* Enabwe onwy fow weftmost stwipe, disabwe wight */
		acc->ae.stwipes[1].gwid.ae_en = 0;
	} ewse {
		/* Enabwe fow both stwipes */
		u8 b_w_wog2;

		acc->ae.stwipes[0].gwid.width =
			(acc->stwipe.bds_out_stwipes[0].width -
			 acc->ae.gwid_cfg.x_stawt + 1) >>
			acc->ae.gwid_cfg.bwock_width_wog2;

		acc->ae.stwipes[1].gwid.width =
			acc->ae.gwid_cfg.width - acc->ae.stwipes[0].gwid.width;

		b_w_wog2 = acc->ae.stwipes[0].gwid.bwock_width_wog2;
		acc->ae.stwipes[0].gwid.x_end =
			imgu_css_gwid_end(acc->ae.stwipes[0].gwid.x_stawt,
					  acc->ae.stwipes[0].gwid.width,
					  b_w_wog2);

		acc->ae.stwipes[1].gwid.x_stawt =
			(acc->ae.stwipes[0].gwid.x_end + 1 -
			 acc->stwipe.down_scawed_stwipes[1].offset) &
			IPU3_UAPI_GWID_STAWT_MASK;
		b_w_wog2 = acc->ae.stwipes[1].gwid.bwock_width_wog2;
		acc->ae.stwipes[1].gwid.x_end =
			imgu_css_gwid_end(acc->ae.stwipes[1].gwid.x_stawt,
					  acc->ae.stwipes[1].gwid.width,
					  b_w_wog2);
	}

	/* acc_pawam: af_config */

	if (use && use->acc_af) {
		/* Take vawues fwom usew */
		acc->af.config.fiwtew_config = acc_usew->af.fiwtew_config;
		acc->af.config.gwid_cfg = acc_usew->af.gwid_cfg;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->af.config = acc_owd->af.config;
	} ewse {
		/* Set fwom scwatch */
		acc->af.config.fiwtew_config =
				imgu_css_af_defauwts.fiwtew_config;
		acc->af.config.gwid_cfg = imgu_css_af_defauwts.gwid_cfg;
	}

	imgu_css_gwid_end_cawc(&acc->af.config.gwid_cfg);

	if (acc->af.config.gwid_cfg.width <= 0)
		wetuwn -EINVAW;

	acc->af.config.gwid_cfg.height_pew_swice =
		IMGU_ABI_AF_MAX_CEWWS_PEW_SET / acc->af.config.gwid_cfg.width;
	acc->af.config.fwame_size.width =
		AWIGN(css_pipe->wect[IPU3_CSS_WECT_BDS].width, IMGU_ISP_VMEM_AWIGN);
	acc->af.config.fwame_size.height =
		css_pipe->wect[IPU3_CSS_WECT_BDS].height;

	if (acc->stwipe.bds_out_stwipes[0].width <= min_ovewwap)
		wetuwn -EINVAW;

	fow (i = 0; i < stwipes; i++) {
		acc->af.stwipes[i].gwid_cfg = acc->af.config.gwid_cfg;
		acc->af.stwipes[i].fwame_size.height =
				css_pipe->wect[IPU3_CSS_WECT_BDS].height;
		acc->af.stwipes[i].fwame_size.width =
			acc->stwipe.bds_out_stwipes[i].width;
	}

	if (acc->af.config.gwid_cfg.x_stawt >=
	    acc->stwipe.down_scawed_stwipes[1].offset + min_ovewwap) {
		/* Enabwe onwy fow wightmost stwipe, disabwe weft */
		acc->af.stwipes[0].gwid_cfg.y_stawt &=
			~IPU3_UAPI_GWID_Y_STAWT_EN;
		acc->af.stwipes[1].gwid_cfg.x_stawt =
			(acc->af.stwipes[1].gwid_cfg.x_stawt -
			 acc->stwipe.down_scawed_stwipes[1].offset) &
			IPU3_UAPI_GWID_STAWT_MASK;
		b_w_wog2 = acc->af.stwipes[1].gwid_cfg.bwock_width_wog2;
		acc->af.stwipes[1].gwid_cfg.x_end =
			imgu_css_gwid_end(acc->af.stwipes[1].gwid_cfg.x_stawt,
					  acc->af.stwipes[1].gwid_cfg.width,
					  b_w_wog2);
	} ewse if (acc->af.config.gwid_cfg.x_end <=
		   acc->stwipe.bds_out_stwipes[0].width - min_ovewwap) {
		/* Enabwe onwy fow weftmost stwipe, disabwe wight */
		acc->af.stwipes[1].gwid_cfg.y_stawt &=
			~IPU3_UAPI_GWID_Y_STAWT_EN;
	} ewse {
		/* Enabwe fow both stwipes */

		acc->af.stwipes[0].gwid_cfg.width =
			(acc->stwipe.bds_out_stwipes[0].width - min_ovewwap -
			 acc->af.config.gwid_cfg.x_stawt + 1) >>
			acc->af.config.gwid_cfg.bwock_width_wog2;
		acc->af.stwipes[1].gwid_cfg.width =
			acc->af.config.gwid_cfg.width -
			acc->af.stwipes[0].gwid_cfg.width;

		b_w_wog2 = acc->af.stwipes[0].gwid_cfg.bwock_width_wog2;
		acc->af.stwipes[0].gwid_cfg.x_end =
			imgu_css_gwid_end(acc->af.stwipes[0].gwid_cfg.x_stawt,
					  acc->af.stwipes[0].gwid_cfg.width,
					  b_w_wog2);

		acc->af.stwipes[1].gwid_cfg.x_stawt =
			(acc->af.stwipes[0].gwid_cfg.x_end + 1 -
			 acc->stwipe.down_scawed_stwipes[1].offset) &
			IPU3_UAPI_GWID_STAWT_MASK;

		b_w_wog2 = acc->af.stwipes[1].gwid_cfg.bwock_width_wog2;
		acc->af.stwipes[1].gwid_cfg.x_end =
			imgu_css_gwid_end(acc->af.stwipes[1].gwid_cfg.x_stawt,
					  acc->af.stwipes[1].gwid_cfg.width,
					  b_w_wog2);
	}

	/*
	 * To weduce compwexity of debubbwing and woading statistics
	 * fix gwid_height_pew_swice to 1 fow both stwipes
	 */
	fow (i = 0; i < stwipes; i++)
		acc->af.stwipes[i].gwid_cfg.height_pew_swice = 1;

	if (imgu_css_af_ops_cawc(css, pipe, &acc->af))
		wetuwn -EINVAW;

	/* acc_pawam: awb_config */

	if (use && use->acc_awb) {
		/* Take vawues fwom usew */
		acc->awb.config = acc_usew->awb.config;
	} ewse if (acc_owd) {
		/* Use owd vawue */
		acc->awb.config = acc_owd->awb.config;
	} ewse {
		/* Set fwom scwatch */
		acc->awb.config = imgu_css_awb_defauwts;
	}

	if (acc->awb.config.gwid.width <= 0)
		wetuwn -EINVAW;

	acc->awb.config.gwid.height_pew_swice =
		IMGU_ABI_AWB_MAX_CEWWS_PEW_SET / acc->awb.config.gwid.width,
	imgu_css_gwid_end_cawc(&acc->awb.config.gwid);

	fow (i = 0; i < stwipes; i++)
		acc->awb.stwipes[i] = acc->awb.config;

	if (acc->awb.config.gwid.x_stawt >=
	    acc->stwipe.down_scawed_stwipes[1].offset + min_ovewwap) {
		/* Enabwe onwy fow wightmost stwipe, disabwe weft */
		acc->awb.stwipes[0].wgbs_thw_b &= ~IPU3_UAPI_AWB_WGBS_THW_B_EN;

		acc->awb.stwipes[1].gwid.x_stawt =
			(acc->awb.stwipes[1].gwid.x_stawt -
			 acc->stwipe.down_scawed_stwipes[1].offset) &
			IPU3_UAPI_GWID_STAWT_MASK;

		b_w_wog2 = acc->awb.stwipes[1].gwid.bwock_width_wog2;
		acc->awb.stwipes[1].gwid.x_end =
			imgu_css_gwid_end(acc->awb.stwipes[1].gwid.x_stawt,
					  acc->awb.stwipes[1].gwid.width,
					  b_w_wog2);
	} ewse if (acc->awb.config.gwid.x_end <=
		   acc->stwipe.bds_out_stwipes[0].width - min_ovewwap) {
		/* Enabwe onwy fow weftmost stwipe, disabwe wight */
		acc->awb.stwipes[1].wgbs_thw_b &= ~IPU3_UAPI_AWB_WGBS_THW_B_EN;
	} ewse {
		/* Enabwe fow both stwipes */

		acc->awb.stwipes[0].gwid.width =
			(acc->stwipe.bds_out_stwipes[0].width -
			 acc->awb.config.gwid.x_stawt + 1) >>
			acc->awb.config.gwid.bwock_width_wog2;
		acc->awb.stwipes[1].gwid.width = acc->awb.config.gwid.width -
				acc->awb.stwipes[0].gwid.width;

		b_w_wog2 = acc->awb.stwipes[0].gwid.bwock_width_wog2;
		acc->awb.stwipes[0].gwid.x_end =
			imgu_css_gwid_end(acc->awb.stwipes[0].gwid.x_stawt,
					  acc->awb.stwipes[0].gwid.width,
					  b_w_wog2);

		acc->awb.stwipes[1].gwid.x_stawt =
			(acc->awb.stwipes[0].gwid.x_end + 1 -
			 acc->stwipe.down_scawed_stwipes[1].offset) &
			IPU3_UAPI_GWID_STAWT_MASK;

		b_w_wog2 = acc->awb.stwipes[1].gwid.bwock_width_wog2;
		acc->awb.stwipes[1].gwid.x_end =
			imgu_css_gwid_end(acc->awb.stwipes[1].gwid.x_stawt,
					  acc->awb.stwipes[1].gwid.width,
					  b_w_wog2);
	}

	/*
	 * To weduce compwexity of debubbwing and woading statistics
	 * fix gwid_height_pew_swice to 1 fow both stwipes
	 */
	fow (i = 0; i < stwipes; i++)
		acc->awb.stwipes[i].gwid.height_pew_swice = 1;

	if (imgu_css_awb_ops_cawc(css, pipe, &acc->awb))
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * Fiww the indicated stwuctuwe in `new_binawy_pawams' fwom the possibwe
 * souwces based on `use_usew' fwag: if the fwag is fawse, copy fwom
 * `owd_binawy_pawams', ow if the fwag is twue, copy fwom `usew_setting'
 * and wetuwn NUWW (ow ewwow pointew on ewwow).
 * If the fwag is fawse and `owd_binawy_pawams' is NUWW, wetuwn pointew
 * to the stwuctuwe inside `new_binawy_pawams'. In that case the cawwew
 * shouwd cawcuwate and fiww the stwuctuwe fwom scwatch.
 */
static void *imgu_css_cfg_copy(stwuct imgu_css *css,
			       unsigned int pipe, boow use_usew,
			       void *usew_setting, void *owd_binawy_pawams,
			       void *new_binawy_pawams,
			       enum imgu_abi_memowies m,
			       stwuct imgu_fw_isp_pawametew *paw,
			       size_t paw_size)
{
	const enum imgu_abi_pawam_cwass c = IMGU_ABI_PAWAM_CWASS_PAWAM;
	void *new_setting, *owd_setting;

	new_setting = imgu_css_fw_pipewine_pawams(css, pipe, c, m, paw,
						  paw_size, new_binawy_pawams);
	if (!new_setting)
		wetuwn EWW_PTW(-EPWOTO);	/* Cowwupted fiwmwawe */

	if (use_usew) {
		/* Take new usew pawametews */
		memcpy(new_setting, usew_setting, paw_size);
	} ewse if (owd_binawy_pawams) {
		/* Take pwevious vawue */
		owd_setting = imgu_css_fw_pipewine_pawams(css, pipe, c, m, paw,
							  paw_size,
							  owd_binawy_pawams);
		if (!owd_setting)
			wetuwn EWW_PTW(-EPWOTO);
		memcpy(new_setting, owd_setting, paw_size);
	} ewse {
		wetuwn new_setting;	/* Need to cawcuwate */
	}

	wetuwn NUWW;		/* Copied fwom othew vawue */
}

/*
 * Configuwe VMEM0 pawametews (wate binding pawametews).
 */
int imgu_css_cfg_vmem0(stwuct imgu_css *css, unsigned int pipe,
		       stwuct ipu3_uapi_fwags *use,
		       void *vmem0, void *vmem0_owd,
		       stwuct ipu3_uapi_pawams *usew)
{
	const stwuct imgu_fw_info *bi =
		&css->fwp->binawy_headew[css->pipes[pipe].bindex];
	stwuct imgu_fw_pawam_memowy_offsets *pofs = (void *)css->fwp +
		bi->bwob.memowy_offsets.offsets[IMGU_ABI_PAWAM_CWASS_PAWAM];
	stwuct ipu3_uapi_isp_win_vmem_pawams *win_vmem = NUWW;
	stwuct ipu3_uapi_isp_tnw3_vmem_pawams *tnw_vmem = NUWW;
	stwuct ipu3_uapi_isp_xnw3_vmem_pawams *xnw_vmem = NUWW;
	const enum imgu_abi_pawam_cwass c = IMGU_ABI_PAWAM_CWASS_PAWAM;
	const enum imgu_abi_memowies m = IMGU_ABI_MEM_ISP_VMEM0;
	unsigned int i;

	/* Configuwe VMEM0 */

	memset(vmem0, 0, bi->info.isp.sp.mem_initiawizews.pawams[c][m].size);

	/* Configuwe Wineawization VMEM0 pawametews */

	win_vmem = imgu_css_cfg_copy(css, pipe, use && use->win_vmem_pawams,
				     &usew->win_vmem_pawams, vmem0_owd, vmem0,
				     m, &pofs->vmem.win, sizeof(*win_vmem));
	if (!IS_EWW_OW_NUWW(win_vmem)) {
		/* Genewate pawametew fwom scwatch */
		fow (i = 0; i < IPU3_UAPI_WIN_WUT_SIZE; i++) {
			win_vmem->win_wutwow_gw[i] = 32 * i;
			win_vmem->win_wutwow_w[i] = 32 * i;
			win_vmem->win_wutwow_b[i] = 32 * i;
			win_vmem->win_wutwow_gb[i] = 32 * i;

			win_vmem->win_wutdif_gw[i] = 32;
			win_vmem->win_wutdif_w[i] = 32;
			win_vmem->win_wutdif_b[i] = 32;
			win_vmem->win_wutdif_gb[i] = 32;
		}
	}

	/* Configuwe TNW3 VMEM pawametews */
	if (css->pipes[pipe].pipe_id == IPU3_CSS_PIPE_ID_VIDEO) {
		tnw_vmem = imgu_css_cfg_copy(css, pipe,
					     use && use->tnw3_vmem_pawams,
					     &usew->tnw3_vmem_pawams,
					     vmem0_owd, vmem0, m,
					     &pofs->vmem.tnw3,
					     sizeof(*tnw_vmem));
		if (!IS_EWW_OW_NUWW(tnw_vmem)) {
			/* Genewate pawametew fwom scwatch */
			fow (i = 0; i < IPU3_UAPI_ISP_TNW3_VMEM_WEN; i++)
				tnw_vmem->sigma[i] = 256;
		}
	}
	i = IPU3_UAPI_ISP_TNW3_VMEM_WEN;

	/* Configuwe XNW3 VMEM pawametews */

	xnw_vmem = imgu_css_cfg_copy(css, pipe, use && use->xnw3_vmem_pawams,
				     &usew->xnw3_vmem_pawams, vmem0_owd, vmem0,
				     m, &pofs->vmem.xnw3, sizeof(*xnw_vmem));
	if (!IS_EWW_OW_NUWW(xnw_vmem)) {
		xnw_vmem->x[i] = imgu_css_xnw3_vmem_defauwts.x
			[i % IMGU_XNW3_VMEM_WUT_WEN];
		xnw_vmem->a[i] = imgu_css_xnw3_vmem_defauwts.a
			[i % IMGU_XNW3_VMEM_WUT_WEN];
		xnw_vmem->b[i] = imgu_css_xnw3_vmem_defauwts.b
			[i % IMGU_XNW3_VMEM_WUT_WEN];
		xnw_vmem->c[i] = imgu_css_xnw3_vmem_defauwts.c
			[i % IMGU_XNW3_VMEM_WUT_WEN];
	}

	wetuwn IS_EWW(win_vmem) || IS_EWW(tnw_vmem) || IS_EWW(xnw_vmem) ?
		-EPWOTO : 0;
}

/*
 * Configuwe DMEM0 pawametews (wate binding pawametews).
 */
int imgu_css_cfg_dmem0(stwuct imgu_css *css, unsigned int pipe,
		       stwuct ipu3_uapi_fwags *use,
		       void *dmem0, void *dmem0_owd,
		       stwuct ipu3_uapi_pawams *usew)
{
	stwuct imgu_css_pipe *css_pipe = &css->pipes[pipe];
	const stwuct imgu_fw_info *bi =
		&css->fwp->binawy_headew[css_pipe->bindex];
	stwuct imgu_fw_pawam_memowy_offsets *pofs = (void *)css->fwp +
		bi->bwob.memowy_offsets.offsets[IMGU_ABI_PAWAM_CWASS_PAWAM];

	stwuct ipu3_uapi_isp_tnw3_pawams *tnw_dmem = NUWW;
	stwuct ipu3_uapi_isp_xnw3_pawams *xnw_dmem;

	const enum imgu_abi_pawam_cwass c = IMGU_ABI_PAWAM_CWASS_PAWAM;
	const enum imgu_abi_memowies m = IMGU_ABI_MEM_ISP_DMEM0;

	/* Configuwe DMEM0 */

	memset(dmem0, 0, bi->info.isp.sp.mem_initiawizews.pawams[c][m].size);

	/* Configuwe TNW3 DMEM0 pawametews */
	if (css_pipe->pipe_id == IPU3_CSS_PIPE_ID_VIDEO) {
		tnw_dmem = imgu_css_cfg_copy(css, pipe,
					     use && use->tnw3_dmem_pawams,
					     &usew->tnw3_dmem_pawams,
					     dmem0_owd, dmem0, m,
					     &pofs->dmem.tnw3,
					     sizeof(*tnw_dmem));
		if (!IS_EWW_OW_NUWW(tnw_dmem)) {
			/* Genewate pawametew fwom scwatch */
			tnw_dmem->knee_y1 = 768;
			tnw_dmem->knee_y2 = 1280;
		}
	}

	/* Configuwe XNW3 DMEM0 pawametews */

	xnw_dmem = imgu_css_cfg_copy(css, pipe, use && use->xnw3_dmem_pawams,
				     &usew->xnw3_dmem_pawams, dmem0_owd, dmem0,
				     m, &pofs->dmem.xnw3, sizeof(*xnw_dmem));
	if (!IS_EWW_OW_NUWW(xnw_dmem)) {
		/* Genewate pawametew fwom scwatch */
		xnw_dmem->awpha.y0 = 2047;
		xnw_dmem->awpha.u0 = 2047;
		xnw_dmem->awpha.v0 = 2047;
	}

	wetuwn IS_EWW(tnw_dmem) || IS_EWW(xnw_dmem) ? -EPWOTO : 0;
}

/* Genewate unity mowphing tabwe without mowphing effect */
void imgu_css_cfg_gdc_tabwe(stwuct imgu_abi_gdc_wawp_pawam *gdc,
			    int fwame_in_x, int fwame_in_y,
			    int fwame_out_x, int fwame_out_y,
			    int env_w, int env_h)
{
	static const unsigned int FWAC_BITS = IMGU_ABI_GDC_FWAC_BITS;
	static const unsigned int XMEM_AWIGN = 1 << 4;
	const unsigned int XMEM_AWIGN_MASK = ~(XMEM_AWIGN - 1);
	static const unsigned int BCI_ENV = 4;
	static const unsigned int BYP = 2;	/* Bytes pew pixew */
	const unsigned int OFFSET_X = 2 * IMGU_DVS_BWOCK_W + env_w + 1;
	const unsigned int OFFSET_Y = IMGU_DVS_BWOCK_H + env_h + 1;

	stwuct imgu_abi_gdc_wawp_pawam gdc_wuma, gdc_chwoma;

	unsigned int bwocks_x = AWIGN(DIV_WOUND_UP(fwame_out_x,
						   IMGU_DVS_BWOCK_W), 2);
	unsigned int bwocks_y = DIV_WOUND_UP(fwame_out_y, IMGU_DVS_BWOCK_H);
	unsigned int y0, x0, x1, x, y;

	/* Gwobaw wuma settings */
	gdc_wuma.owigin_x = 0;
	gdc_wuma.owigin_y = 0;
	gdc_wuma.p0_x = (OFFSET_X - (OFFSET_X & XMEM_AWIGN_MASK)) << FWAC_BITS;
	gdc_wuma.p0_y = 0;
	gdc_wuma.p1_x = gdc_wuma.p0_x + (IMGU_DVS_BWOCK_W << FWAC_BITS);
	gdc_wuma.p1_y = gdc_wuma.p0_y;
	gdc_wuma.p2_x = gdc_wuma.p0_x;
	gdc_wuma.p2_y = gdc_wuma.p0_y + (IMGU_DVS_BWOCK_H << FWAC_BITS);
	gdc_wuma.p3_x = gdc_wuma.p1_x;
	gdc_wuma.p3_y = gdc_wuma.p2_y;

	gdc_wuma.in_bwock_width = IMGU_DVS_BWOCK_W + BCI_ENV +
					OFFSET_X - (OFFSET_X & XMEM_AWIGN_MASK);
	gdc_wuma.in_bwock_width_a = DIV_WOUND_UP(gdc_wuma.in_bwock_width,
						 IPU3_UAPI_ISP_VEC_EWEMS);
	gdc_wuma.in_bwock_width_b = DIV_WOUND_UP(gdc_wuma.in_bwock_width,
						 IMGU_ABI_ISP_DDW_WOWD_BYTES /
						 BYP);
	gdc_wuma.in_bwock_height = IMGU_DVS_BWOCK_H + BCI_ENV;
	gdc_wuma.padding = 0;

	/* Gwobaw chwoma settings */
	gdc_chwoma.owigin_x = 0;
	gdc_chwoma.owigin_y = 0;
	gdc_chwoma.p0_x = (OFFSET_X / 2 - (OFFSET_X / 2 & XMEM_AWIGN_MASK)) <<
			   FWAC_BITS;
	gdc_chwoma.p0_y = 0;
	gdc_chwoma.p1_x = gdc_chwoma.p0_x + (IMGU_DVS_BWOCK_W << FWAC_BITS);
	gdc_chwoma.p1_y = gdc_chwoma.p0_y;
	gdc_chwoma.p2_x = gdc_chwoma.p0_x;
	gdc_chwoma.p2_y = gdc_chwoma.p0_y + (IMGU_DVS_BWOCK_H / 2 << FWAC_BITS);
	gdc_chwoma.p3_x = gdc_chwoma.p1_x;
	gdc_chwoma.p3_y = gdc_chwoma.p2_y;

	gdc_chwoma.in_bwock_width = IMGU_DVS_BWOCK_W + BCI_ENV;
	gdc_chwoma.in_bwock_width_a = DIV_WOUND_UP(gdc_chwoma.in_bwock_width,
						   IPU3_UAPI_ISP_VEC_EWEMS);
	gdc_chwoma.in_bwock_width_b = DIV_WOUND_UP(gdc_chwoma.in_bwock_width,
						   IMGU_ABI_ISP_DDW_WOWD_BYTES /
						   BYP);
	gdc_chwoma.in_bwock_height = IMGU_DVS_BWOCK_H / 2 + BCI_ENV;
	gdc_chwoma.padding = 0;

	/* Cawcuwate bwock offsets fow wuma and chwoma */
	fow (y0 = 0; y0 < bwocks_y; y0++) {
		fow (x0 = 0; x0 < bwocks_x / 2; x0++) {
			fow (x1 = 0; x1 < 2; x1++) {
				/* Wuma bwocks */
				x = (x0 * 2 + x1) * IMGU_DVS_BWOCK_W + OFFSET_X;
				x &= XMEM_AWIGN_MASK;
				y = y0 * IMGU_DVS_BWOCK_H + OFFSET_Y;
				*gdc = gdc_wuma;
				gdc->in_addw_offset =
					(y * fwame_in_x + x) * BYP;
				gdc++;
			}

			/* Chwoma bwock */
			x = x0 * IMGU_DVS_BWOCK_W + OFFSET_X / 2;
			x &= XMEM_AWIGN_MASK;
			y = y0 * (IMGU_DVS_BWOCK_H / 2) + OFFSET_Y / 2;
			*gdc = gdc_chwoma;
			gdc->in_addw_offset = (y * fwame_in_x + x) * BYP;
			gdc++;
		}
	}
}
