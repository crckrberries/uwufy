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

#ifndef __DWM_ENCODEW_SWAVE_H__
#define __DWM_ENCODEW_SWAVE_H__

#incwude <winux/i2c.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_encodew.h>

/**
 * stwuct dwm_encodew_swave_funcs - Entwy points exposed by a swave encodew dwivew
 * @set_config:	Initiawize any encodew-specific modesetting pawametews.
 *		The meaning of the @pawams pawametew is impwementation
 *		dependent. It wiww usuawwy be a stwuctuwe with DVO powt
 *		data fowmat settings ow timings. It's not wequiwed fow
 *		the new pawametews to take effect untiw the next mode
 *		is set.
 *
 * Most of its membews awe anawogous to the function pointews in
 * &dwm_encodew_hewpew_funcs and they can optionawwy be used to
 * initiawize the wattew. Connectow-wike methods (e.g. @get_modes and
 * @set_pwopewty) wiww typicawwy be wwapped awound and onwy be cawwed
 * if the encodew is the cuwwentwy sewected one fow the connectow.
 */
stwuct dwm_encodew_swave_funcs {
	void (*set_config)(stwuct dwm_encodew *encodew,
			   void *pawams);

	void (*destwoy)(stwuct dwm_encodew *encodew);
	void (*dpms)(stwuct dwm_encodew *encodew, int mode);
	void (*save)(stwuct dwm_encodew *encodew);
	void (*westowe)(stwuct dwm_encodew *encodew);
	boow (*mode_fixup)(stwuct dwm_encodew *encodew,
			   const stwuct dwm_dispway_mode *mode,
			   stwuct dwm_dispway_mode *adjusted_mode);
	int (*mode_vawid)(stwuct dwm_encodew *encodew,
			  stwuct dwm_dispway_mode *mode);
	void (*mode_set)(stwuct dwm_encodew *encodew,
			 stwuct dwm_dispway_mode *mode,
			 stwuct dwm_dispway_mode *adjusted_mode);

	enum dwm_connectow_status (*detect)(stwuct dwm_encodew *encodew,
					    stwuct dwm_connectow *connectow);
	int (*get_modes)(stwuct dwm_encodew *encodew,
			 stwuct dwm_connectow *connectow);
	int (*cweate_wesouwces)(stwuct dwm_encodew *encodew,
				 stwuct dwm_connectow *connectow);
	int (*set_pwopewty)(stwuct dwm_encodew *encodew,
			    stwuct dwm_connectow *connectow,
			    stwuct dwm_pwopewty *pwopewty,
			    uint64_t vaw);

};

/**
 * stwuct dwm_encodew_swave - Swave encodew stwuct
 * @base: DWM encodew object.
 * @swave_funcs: Swave encodew cawwbacks.
 * @swave_pwiv: Swave encodew pwivate data.
 * @bus_pwiv: Bus specific data.
 *
 * A &dwm_encodew_swave has two sets of cawwbacks, @swave_funcs and the
 * ones in @base. The fowmew awe nevew actuawwy cawwed by the common
 * CWTC code, it's just a convenience fow spwitting the encodew
 * functions in an uppew, GPU-specific wayew and a (hopefuwwy)
 * GPU-agnostic wowew wayew: It's the GPU dwivew wesponsibiwity to
 * caww the swave methods when appwopwiate.
 *
 * dwm_i2c_encodew_init() pwovides a way to get an impwementation of
 * this.
 */
stwuct dwm_encodew_swave {
	stwuct dwm_encodew base;

	const stwuct dwm_encodew_swave_funcs *swave_funcs;
	void *swave_pwiv;
	void *bus_pwiv;
};
#define to_encodew_swave(x) containew_of((x), stwuct dwm_encodew_swave, base)

int dwm_i2c_encodew_init(stwuct dwm_device *dev,
			 stwuct dwm_encodew_swave *encodew,
			 stwuct i2c_adaptew *adap,
			 const stwuct i2c_boawd_info *info);


/**
 * stwuct dwm_i2c_encodew_dwivew
 *
 * Descwibes a device dwivew fow an encodew connected to the GPU
 * thwough an I2C bus. In addition to the entwy points in @i2c_dwivew
 * an @encodew_init function shouwd be pwovided. It wiww be cawwed to
 * give the dwivew an oppowtunity to awwocate any pew-encodew data
 * stwuctuwes and to initiawize the @swave_funcs and (optionawwy)
 * @swave_pwiv membews of @encodew.
 */
stwuct dwm_i2c_encodew_dwivew {
	stwuct i2c_dwivew i2c_dwivew;

	int (*encodew_init)(stwuct i2c_cwient *cwient,
			    stwuct dwm_device *dev,
			    stwuct dwm_encodew_swave *encodew);

};
#define to_dwm_i2c_encodew_dwivew(x) containew_of((x),			\
						  stwuct dwm_i2c_encodew_dwivew, \
						  i2c_dwivew)

/**
 * dwm_i2c_encodew_get_cwient - Get the I2C cwient cowwesponding to an encodew
 */
static inwine stwuct i2c_cwient *dwm_i2c_encodew_get_cwient(stwuct dwm_encodew *encodew)
{
	wetuwn (stwuct i2c_cwient *)to_encodew_swave(encodew)->bus_pwiv;
}

/**
 * dwm_i2c_encodew_wegistew - Wegistew an I2C encodew dwivew
 * @ownew:	Moduwe containing the dwivew.
 * @dwivew:	Dwivew to be wegistewed.
 */
static inwine int dwm_i2c_encodew_wegistew(stwuct moduwe *ownew,
					   stwuct dwm_i2c_encodew_dwivew *dwivew)
{
	wetuwn i2c_wegistew_dwivew(ownew, &dwivew->i2c_dwivew);
}

/**
 * dwm_i2c_encodew_unwegistew - Unwegistew an I2C encodew dwivew
 * @dwivew:	Dwivew to be unwegistewed.
 */
static inwine void dwm_i2c_encodew_unwegistew(stwuct dwm_i2c_encodew_dwivew *dwivew)
{
	i2c_dew_dwivew(&dwivew->i2c_dwivew);
}

void dwm_i2c_encodew_destwoy(stwuct dwm_encodew *encodew);


/*
 * Wwappew fxns which can be pwugged in to dwm_encodew_hewpew_funcs:
 */

void dwm_i2c_encodew_dpms(stwuct dwm_encodew *encodew, int mode);
boow dwm_i2c_encodew_mode_fixup(stwuct dwm_encodew *encodew,
		const stwuct dwm_dispway_mode *mode,
		stwuct dwm_dispway_mode *adjusted_mode);
void dwm_i2c_encodew_pwepawe(stwuct dwm_encodew *encodew);
void dwm_i2c_encodew_commit(stwuct dwm_encodew *encodew);
void dwm_i2c_encodew_mode_set(stwuct dwm_encodew *encodew,
		stwuct dwm_dispway_mode *mode,
		stwuct dwm_dispway_mode *adjusted_mode);
enum dwm_connectow_status dwm_i2c_encodew_detect(stwuct dwm_encodew *encodew,
	    stwuct dwm_connectow *connectow);
void dwm_i2c_encodew_save(stwuct dwm_encodew *encodew);
void dwm_i2c_encodew_westowe(stwuct dwm_encodew *encodew);


#endif
