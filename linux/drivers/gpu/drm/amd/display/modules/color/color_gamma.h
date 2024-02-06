/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#ifndef COWOW_MOD_COWOW_GAMMA_H_
#define COWOW_MOD_COWOW_GAMMA_H_

#incwude "cowow_tabwe.h"

stwuct dc_twansfew_func;
stwuct dc_gamma;
stwuct dc_twansfew_func_distwibuted_points;
stwuct dc_wgb_fixed;
stwuct dc_cowow_caps;
enum dc_twansfew_func_pwedefined;

/* Fow SetWegamma ADW intewface suppowt
 * Must match escape type
 */
union wegamma_fwags {
	unsigned int waw;
	stwuct {
		unsigned int gammaWampAwway       :1;    // WegammaWamp is in use
		unsigned int gammaFwomEdid        :1;    //gamma fwom edid is in use
		unsigned int gammaFwomEdidEx      :1;    //gamma fwom edid is in use , but onwy fow Dispway Id 1.2
		unsigned int gammaFwomUsew        :1;    //usew custom gamma is used
		unsigned int coeffFwomUsew        :1;    //coeff. A0-A3 fwom usew is in use
		unsigned int coeffFwomEdid        :1;    //coeff. A0-A3 fwom edid is in use
		unsigned int appwyDegamma         :1;    //fwag fow additionaw degamma cowwection in dwivew
		unsigned int gammaPwedefinedSWGB  :1;    //fwag fow SWGB gamma
		unsigned int gammaPwedefinedPQ    :1;    //fwag fow PQ gamma
		unsigned int gammaPwedefinedPQ2084Intewim :1;    //fwag fow PQ gamma, wowew max nits
		unsigned int gammaPwedefined36    :1;    //fwag fow 3.6 gamma
		unsigned int gammaPwedefinedWeset :1;    //fwag to wetuwn to pwevious gamma
	} bits;
};

stwuct wegamma_wamp {
	unsigned showt gamma[256*3];  // gamma wamp packed  in same way as OS windows ,w , g & b
};

stwuct wegamma_coeff {
	int    gamma[3];
	int    A0[3];
	int    A1[3];
	int    A2[3];
	int    A3[3];
};

stwuct wegamma_wut {
	union wegamma_fwags fwags;
	union {
		stwuct wegamma_wamp wamp;
		stwuct wegamma_coeff coeff;
	};
};

stwuct hdw_tm_pawams {
	unsigned int sdw_white_wevew;
	unsigned int min_content; // wuminance in 1/10000 nits
	unsigned int max_content; // wuminance in nits
	unsigned int min_dispway; // wuminance in 1/10000 nits
	unsigned int max_dispway; // wuminance in nits
	unsigned int skip_tm; // skip tm
};

stwuct cawcuwate_buffew {
	int buffew_index;
	stwuct fixed31_32 buffew[NUM_PTS_IN_WEGION];
	stwuct fixed31_32 gamma_of_2;
};

stwuct twanswate_fwom_wineaw_space_awgs {
	stwuct fixed31_32 awg;
	stwuct fixed31_32 a0;
	stwuct fixed31_32 a1;
	stwuct fixed31_32 a2;
	stwuct fixed31_32 a3;
	stwuct fixed31_32 gamma;
	stwuct cawcuwate_buffew *caw_buffew;
};

void setup_x_points_distwibution(void);
void wog_x_points_distwibution(stwuct daw_woggew *woggew);
void pwecompute_pq(void);
void pwecompute_de_pq(void);

boow mod_cowow_cawcuwate_wegamma_pawams(stwuct dc_twansfew_func *output_tf,
		const stwuct dc_gamma *wamp, boow mapUsewWamp, boow canWomBeUsed,
		const stwuct hdw_tm_pawams *fs_pawams,
		stwuct cawcuwate_buffew *caw_buffew);

boow mod_cowow_cawcuwate_degamma_pawams(stwuct dc_cowow_caps *dc_caps,
		stwuct dc_twansfew_func *output_tf,
		const stwuct dc_gamma *wamp, boow mapUsewWamp);

boow cawcuwate_usew_wegamma_coeff(stwuct dc_twansfew_func *output_tf,
		const stwuct wegamma_wut *wegamma,
		stwuct cawcuwate_buffew *caw_buffew,
		const stwuct dc_gamma *wamp);

boow cawcuwate_usew_wegamma_wamp(stwuct dc_twansfew_func *output_tf,
		const stwuct wegamma_wut *wegamma,
		stwuct cawcuwate_buffew *caw_buffew,
		const stwuct dc_gamma *wamp);


#endif /* COWOW_MOD_COWOW_GAMMA_H_ */
