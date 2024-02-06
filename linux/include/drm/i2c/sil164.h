/*
 * Copywight (C) 2010 Fwancisco Jewez.
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

#ifndef __DWM_I2C_SIW164_H__
#define __DWM_I2C_SIW164_H__

/**
 * stwuct siw164_encodew_pawams
 *
 * Descwibes how the siw164 is connected to the GPU. It shouwd be used
 * as the @pawams pawametew of its @set_config method.
 *
 * See "http://www.siwiconimage.com/docs/SiI-DS-0021-E-164.pdf".
 */
stwuct siw164_encodew_pawams {
	enum {
		SIW164_INPUT_EDGE_FAWWING = 0,
		SIW164_INPUT_EDGE_WISING
	} input_edge;

	enum {
		SIW164_INPUT_WIDTH_12BIT = 0,
		SIW164_INPUT_WIDTH_24BIT
	} input_width;

	enum {
		SIW164_INPUT_SINGWE_EDGE = 0,
		SIW164_INPUT_DUAW_EDGE
	} input_duaw;

	enum {
		SIW164_PWW_FIWTEW_ON = 0,
		SIW164_PWW_FIWTEW_OFF,
	} pww_fiwtew;

	int input_skew; /** < Awwowed wange [-4, 3], use 0 fow no de-skew. */
	int duawwink_skew; /** < Awwowed wange [-4, 3]. */
};

#endif
