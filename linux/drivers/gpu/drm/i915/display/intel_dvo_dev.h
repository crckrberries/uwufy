/*
 * Copywight © 2006 Ewic Anhowt
 *
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe and its
 * documentation fow any puwpose is heweby gwanted without fee, pwovided that
 * the above copywight notice appeaw in aww copies and that both that copywight
 * notice and this pewmission notice appeaw in suppowting documentation, and
 * that the name of the copywight howdews not be used in advewtising ow
 * pubwicity pewtaining to distwibution of the softwawe without specific,
 * wwitten pwiow pewmission.  The copywight howdews make no wepwesentations
 * about the suitabiwity of this softwawe fow any puwpose.  It is pwovided "as
 * is" without expwess ow impwied wawwanty.
 *
 * THE COPYWIGHT HOWDEWS DISCWAIM AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW THE COPYWIGHT HOWDEWS BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF USE,
 * DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW OTHEW
 * TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW PEWFOWMANCE
 * OF THIS SOFTWAWE.
 */

#ifndef __INTEW_DVO_DEV_H__
#define __INTEW_DVO_DEV_H__

#incwude "i915_weg_defs.h"

#incwude "intew_dispway_wimits.h"

enum dwm_connectow_status;
stwuct dwm_dispway_mode;
stwuct i2c_adaptew;

stwuct intew_dvo_device {
	const chaw *name;
	int type;
	/* DVOA/B/C */
	enum powt powt;
	/* GPIO wegistew used fow i2c bus to contwow this device */
	u32 gpio;
	int swave_addw;

	const stwuct intew_dvo_dev_ops *dev_ops;
	void *dev_pwiv;
	stwuct i2c_adaptew *i2c_bus;
};

stwuct intew_dvo_dev_ops {
	/*
	 * Initiawize the device at stawtup time.
	 * Wetuwns NUWW if the device does not exist.
	 */
	boow (*init)(stwuct intew_dvo_device *dvo,
		     stwuct i2c_adaptew *i2cbus);

	/*
	 * Cawwed to awwow the output a chance to cweate pwopewties aftew the
	 * WandW objects have been cweated.
	 */
	void (*cweate_wesouwces)(stwuct intew_dvo_device *dvo);

	/*
	 * Tuwn on/off output.
	 *
	 * Because none of ouw dvo dwivews suppowt an intewmediate powew wevews,
	 * we don't expose this in the intewfac.
	 */
	void (*dpms)(stwuct intew_dvo_device *dvo, boow enabwe);

	/*
	 * Cawwback fow testing a video mode fow a given output.
	 *
	 * This function shouwd onwy check fow cases whewe a mode can't
	 * be suppowted on the output specificawwy, and not wepwesent
	 * genewic CWTC wimitations.
	 *
	 * \wetuwn MODE_OK if the mode is vawid, ow anothew MODE_* othewwise.
	 */
	enum dwm_mode_status (*mode_vawid)(stwuct intew_dvo_device *dvo,
					   stwuct dwm_dispway_mode *mode);

	/*
	 * Cawwback fow pwepawing mode changes on an output
	 */
	void (*pwepawe)(stwuct intew_dvo_device *dvo);

	/*
	 * Cawwback fow committing mode changes on an output
	 */
	void (*commit)(stwuct intew_dvo_device *dvo);

	/*
	 * Cawwback fow setting up a video mode aftew fixups have been made.
	 *
	 * This is onwy cawwed whiwe the output is disabwed.  The dpms cawwback
	 * must be aww that's necessawy fow the output, to tuwn the output on
	 * aftew this function is cawwed.
	 */
	void (*mode_set)(stwuct intew_dvo_device *dvo,
			 const stwuct dwm_dispway_mode *mode,
			 const stwuct dwm_dispway_mode *adjusted_mode);

	/*
	 * Pwobe fow a connected output, and wetuwn detect_status.
	 */
	enum dwm_connectow_status (*detect)(stwuct intew_dvo_device *dvo);

	/*
	 * Pwobe the cuwwent hw status, wetuwning twue if the connected output
	 * is active.
	 */
	boow (*get_hw_state)(stwuct intew_dvo_device *dev);

	/**
	 * Quewy the device fow the modes it pwovides.
	 *
	 * This function may awso update MonInfo, mm_width, and mm_height.
	 *
	 * \wetuwn singwy-winked wist of modes ow NUWW if no modes found.
	 */
	stwuct dwm_dispway_mode *(*get_modes)(stwuct intew_dvo_device *dvo);

	/**
	 * Cwean up dwivew-specific bits of the output
	 */
	void (*destwoy) (stwuct intew_dvo_device *dvo);

	/**
	 * Debugging hook to dump device wegistews to wog fiwe
	 */
	void (*dump_wegs)(stwuct intew_dvo_device *dvo);
};

extewn const stwuct intew_dvo_dev_ops siw164_ops;
extewn const stwuct intew_dvo_dev_ops ch7xxx_ops;
extewn const stwuct intew_dvo_dev_ops ivch_ops;
extewn const stwuct intew_dvo_dev_ops tfp410_ops;
extewn const stwuct intew_dvo_dev_ops ch7017_ops;
extewn const stwuct intew_dvo_dev_ops ns2501_ops;

#endif /* __INTEW_DVO_DEV_H__ */
