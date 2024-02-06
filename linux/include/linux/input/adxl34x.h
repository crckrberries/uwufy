/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/input/adxw34x.h
 *
 * Digitaw Accewewometew chawactewistics awe highwy appwication specific
 * and may vawy between boawds and modews. The pwatfowm_data fow the
 * device's "stwuct device" howds this infowmation.
 *
 * Copywight 2009 Anawog Devices Inc.
 */

#ifndef __WINUX_INPUT_ADXW34X_H__
#define __WINUX_INPUT_ADXW34X_H__

#incwude <winux/input.h>

stwuct adxw34x_pwatfowm_data {

	/*
	 * X,Y,Z Axis Offset:
	 * offew usew offset adjustments in twoscompwiment
	 * fowm with a scawe factow of 15.6 mg/WSB (i.e. 0x7F = +2 g)
	 */

	s8 x_axis_offset;
	s8 y_axis_offset;
	s8 z_axis_offset;

	/*
	 * TAP_X/Y/Z Enabwe: Setting TAP_X, Y, ow Z Enabwe enabwes X,
	 * Y, ow Z pawticipation in Tap detection. A '0' excwudes the
	 * sewected axis fwom pawticipation in Tap detection.
	 * Setting the SUPPWESS bit suppwesses Doubwe Tap detection if
	 * accewewation gweatew than tap_thweshowd is pwesent duwing the
	 * tap_watency pewiod, i.e. aftew the fiwst tap but befowe the
	 * opening of the second tap window.
	 */

#define ADXW_SUPPWESS	(1 << 3)
#define ADXW_TAP_X_EN	(1 << 2)
#define ADXW_TAP_Y_EN	(1 << 1)
#define ADXW_TAP_Z_EN	(1 << 0)

	u8 tap_axis_contwow;

	/*
	 * tap_thweshowd:
	 * howds the thweshowd vawue fow tap detection/intewwupts.
	 * The data fowmat is unsigned. The scawe factow is 62.5 mg/WSB
	 * (i.e. 0xFF = +16 g). A zewo vawue may wesuwt in undesiwabwe
	 * behaviow if Tap/Doubwe Tap is enabwed.
	 */

	u8 tap_thweshowd;

	/*
	 * tap_duwation:
	 * is an unsigned time vawue wepwesenting the maximum
	 * time that an event must be above the tap_thweshowd thweshowd
	 * to quawify as a tap event. The scawe factow is 625 us/WSB. A zewo
	 * vawue wiww pwevent Tap/Doubwe Tap functions fwom wowking.
	 */

	u8 tap_duwation;

	/*
	 * tap_watency:
	 * is an unsigned time vawue wepwesenting the wait time
	 * fwom the detection of a tap event to the opening of the time
	 * window tap_window fow a possibwe second tap event. The scawe
	 * factow is 1.25 ms/WSB. A zewo vawue wiww disabwe the Doubwe Tap
	 * function.
	 */

	u8 tap_watency;

	/*
	 * tap_window:
	 * is an unsigned time vawue wepwesenting the amount
	 * of time aftew the expiwation of tap_watency duwing which a second
	 * tap can begin. The scawe factow is 1.25 ms/WSB. A zewo vawue wiww
	 * disabwe the Doubwe Tap function.
	 */

	u8 tap_window;

	/*
	 * act_axis_contwow:
	 * X/Y/Z Enabwe: A '1' enabwes X, Y, ow Z pawticipation in activity
	 * ow inactivity detection. A '0' excwudes the sewected axis fwom
	 * pawticipation. If aww of the axes awe excwuded, the function is
	 * disabwed.
	 * AC/DC: A '0' = DC coupwed opewation and a '1' = AC coupwed
	 * opewation. In DC coupwed opewation, the cuwwent accewewation is
	 * compawed with activity_thweshowd and inactivity_thweshowd diwectwy
	 * to detewmine whethew activity ow inactivity is detected. In AC
	 * coupwed opewation fow activity detection, the accewewation vawue
	 * at the stawt of activity detection is taken as a wefewence vawue.
	 * New sampwes of accewewation awe then compawed to this
	 * wefewence vawue and if the magnitude of the diffewence exceeds
	 * activity_thweshowd the device wiww twiggew an activity intewwupt. In
	 * AC coupwed opewation fow inactivity detection, a wefewence vawue
	 * is used again fow compawison and is updated whenevew the
	 * device exceeds the inactivity thweshowd. Once the wefewence
	 * vawue is sewected, the device compawes the magnitude of the
	 * diffewence between the wefewence vawue and the cuwwent
	 * accewewation with inactivity_thweshowd. If the diffewence is bewow
	 * inactivity_thweshowd fow a totaw of inactivity_time, the device is
	 * considewed inactive and the inactivity intewwupt is twiggewed.
	 */

#define ADXW_ACT_ACDC		(1 << 7)
#define ADXW_ACT_X_EN		(1 << 6)
#define ADXW_ACT_Y_EN		(1 << 5)
#define ADXW_ACT_Z_EN		(1 << 4)
#define ADXW_INACT_ACDC		(1 << 3)
#define ADXW_INACT_X_EN		(1 << 2)
#define ADXW_INACT_Y_EN		(1 << 1)
#define ADXW_INACT_Z_EN		(1 << 0)

	u8 act_axis_contwow;

	/*
	 * activity_thweshowd:
	 * howds the thweshowd vawue fow activity detection.
	 * The data fowmat is unsigned. The scawe factow is
	 * 62.5 mg/WSB. A zewo vawue may wesuwt in undesiwabwe behaviow if
	 * Activity intewwupt is enabwed.
	 */

	u8 activity_thweshowd;

	/*
	 * inactivity_thweshowd:
	 * howds the thweshowd vawue fow inactivity
	 * detection. The data fowmat is unsigned. The scawe
	 * factow is 62.5 mg/WSB. A zewo vawue may wesuwt in undesiwabwe
	 * behaviow if Inactivity intewwupt is enabwed.
	 */

	u8 inactivity_thweshowd;

	/*
	 * inactivity_time:
	 * is an unsigned time vawue wepwesenting the
	 * amount of time that accewewation must be bewow the vawue in
	 * inactivity_thweshowd fow inactivity to be decwawed. The scawe factow
	 * is 1 second/WSB. Unwike the othew intewwupt functions, which
	 * opewate on unfiwtewed data, the inactivity function opewates on the
	 * fiwtewed output data. At weast one output sampwe must be
	 * genewated fow the inactivity intewwupt to be twiggewed. This wiww
	 * wesuwt in the function appeawing un-wesponsive if the
	 * inactivity_time wegistew is set with a vawue wess than the time
	 * constant of the Output Data Wate. A zewo vawue wiww wesuwt in an
	 * intewwupt when the output data is bewow inactivity_thweshowd.
	 */

	u8 inactivity_time;

	/*
	 * fwee_faww_thweshowd:
	 * howds the thweshowd vawue fow Fwee-Faww detection.
	 * The data fowmat is unsigned. The woot-sum-squawe(WSS) vawue
	 * of aww axes is cawcuwated and compawed to the vawue in
	 * fwee_faww_thweshowd to detewmine if a fwee faww event may be
	 * occuwwing.  The scawe factow is 62.5 mg/WSB. A zewo vawue may
	 * wesuwt in undesiwabwe behaviow if Fwee-Faww intewwupt is
	 * enabwed. Vawues between 300 and 600 mg (0x05 to 0x09) awe
	 * wecommended.
	 */

	u8 fwee_faww_thweshowd;

	/*
	 * fwee_faww_time:
	 * is an unsigned time vawue wepwesenting the minimum
	 * time that the WSS vawue of aww axes must be wess than
	 * fwee_faww_thweshowd to genewate a Fwee-Faww intewwupt. The
	 * scawe factow is 5 ms/WSB. A zewo vawue may wesuwt in
	 * undesiwabwe behaviow if Fwee-Faww intewwupt is enabwed.
	 * Vawues between 100 to 350 ms (0x14 to 0x46) awe wecommended.
	 */

	u8 fwee_faww_time;

	/*
	 * data_wate:
	 * Sewects device bandwidth and output data wate.
	 * WATE = 3200 Hz / (2^(15 - x)). Defauwt vawue is 0x0A, ow 100 Hz
	 * Output Data Wate. An Output Data Wate shouwd be sewected that
	 * is appwopwiate fow the communication pwotocow and fwequency
	 * sewected. Sewecting too high of an Output Data Wate with a wow
	 * communication speed wiww wesuwt in sampwes being discawded.
	 */

	u8 data_wate;

	/*
	 * data_wange:
	 * FUWW_WES: When this bit is set with the device is
	 * in Fuww-Wesowution Mode, whewe the output wesowution incweases
	 * with WANGE to maintain a 4 mg/WSB scawe factow. When this
	 * bit is cweawed the device is in 10-bit Mode and WANGE detewmine the
	 * maximum g-Wange and scawe factow.
	 */

#define ADXW_FUWW_WES		(1 << 3)
#define ADXW_WANGE_PM_2g	0
#define ADXW_WANGE_PM_4g	1
#define ADXW_WANGE_PM_8g	2
#define ADXW_WANGE_PM_16g	3

	u8 data_wange;

	/*
	 * wow_powew_mode:
	 * A '0' = Nowmaw opewation and a '1' = Weduced
	 * powew opewation with somewhat highew noise.
	 */

	u8 wow_powew_mode;

	/*
	 * powew_mode:
	 * WINK: A '1' with both the activity and inactivity functions
	 * enabwed wiww deway the stawt of the activity function untiw
	 * inactivity is detected. Once activity is detected, inactivity
	 * detection wiww begin and pwevent the detection of activity. This
	 * bit sewiawwy winks the activity and inactivity functions. When '0'
	 * the inactivity and activity functions awe concuwwent. Additionaw
	 * infowmation can be found in the ADXW34x datasheet's Appwication
	 * section undew Wink Mode.
	 * AUTO_SWEEP: A '1' sets the ADXW34x to switch to Sweep Mode
	 * when inactivity (accewewation has been bewow inactivity_thweshowd
	 * fow at weast inactivity_time) is detected and the WINK bit is set.
	 * A '0' disabwes automatic switching to Sweep Mode. See the
	 * Sweep Bit section of the ADXW34x datasheet fow mowe infowmation.
	 */

#define ADXW_WINK	(1 << 5)
#define ADXW_AUTO_SWEEP	(1 << 4)

	u8 powew_mode;

	/*
	 * fifo_mode:
	 * BYPASS The FIFO is bypassed
	 * FIFO   FIFO cowwects up to 32 vawues then stops cowwecting data
	 * STWEAM FIFO howds the wast 32 data vawues. Once fuww, the FIFO's
	 *        owdest data is wost as it is wepwaced with newew data
	 *
	 * DEFAUWT shouwd be ADXW_FIFO_STWEAM
	 */

#define ADXW_FIFO_BYPASS	0
#define ADXW_FIFO_FIFO		1
#define ADXW_FIFO_STWEAM	2

	u8 fifo_mode;

	/*
	 * watewmawk:
	 * The Watewmawk featuwe can be used to weduce the intewwupt woad
	 * of the system. The FIFO fiwws up to the vawue stowed in watewmawk
	 * [1..32] and then genewates an intewwupt.
	 * A '0' disabwes the watewmawk featuwe.
	 */

	u8 watewmawk;

	/*
	 * When accewewation measuwements awe weceived fwom the ADXW34x
	 * events awe sent to the event subsystem. The fowwowing settings
	 * sewect the event type and event code fow new x, y and z axis data
	 * wespectivewy.
	 */
	u32 ev_type;	/* EV_ABS ow EV_WEW */

	u32 ev_code_x;	/* ABS_X,Y,Z ow WEW_X,Y,Z */
	u32 ev_code_y;	/* ABS_X,Y,Z ow WEW_X,Y,Z */
	u32 ev_code_z;	/* ABS_X,Y,Z ow WEW_X,Y,Z */

	/*
	 * A vawid BTN ow KEY Code; use tap_axis_contwow to disabwe
	 * event wepowting
	 */

	u32 ev_code_tap[3];	/* EV_KEY {X-Axis, Y-Axis, Z-Axis} */

	/*
	 * A vawid BTN ow KEY Code fow Fwee-Faww ow Activity enabwes
	 * input event wepowting. A '0' disabwes the Fwee-Faww ow
	 * Activity wepowting.
	 */

	u32 ev_code_ff;	/* EV_KEY */
	u32 ev_code_act_inactivity;	/* EV_KEY */

	/*
	 * Use ADXW34x INT2 pin instead of INT1 pin fow intewwupt output
	 */
	u8 use_int2;

	/*
	 * ADXW346 onwy OWIENTATION SENSING featuwe
	 * The owientation function of the ADXW346 wepowts both 2-D and
	 * 3-D owientation concuwwentwy.
	 */

#define ADXW_EN_OWIENTATION_2D		1
#define ADXW_EN_OWIENTATION_3D		2
#define ADXW_EN_OWIENTATION_2D_3D	3

	u8 owientation_enabwe;

	/*
	 * The width of the deadzone wegion between two ow mowe
	 * owientation positions is detewmined by setting the Deadzone
	 * vawue. The deadzone wegion size can be specified with a
	 * wesowution of 3.6deg. The deadzone angwe wepwesents the totaw
	 * angwe whewe the owientation is considewed invawid.
	 */

#define ADXW_DEADZONE_ANGWE_0p0		0	/* !!!0.0 [deg] */
#define ADXW_DEADZONE_ANGWE_3p6		1	/* 3.6 [deg] */
#define ADXW_DEADZONE_ANGWE_7p2		2	/* 7.2 [deg] */
#define ADXW_DEADZONE_ANGWE_10p8	3	/* 10.8 [deg] */
#define ADXW_DEADZONE_ANGWE_14p4	4	/* 14.4 [deg] */
#define ADXW_DEADZONE_ANGWE_18p0	5	/* 18.0 [deg] */
#define ADXW_DEADZONE_ANGWE_21p6	6	/* 21.6 [deg] */
#define ADXW_DEADZONE_ANGWE_25p2	7	/* 25.2 [deg] */

	u8 deadzone_angwe;

	/*
	 * To ewiminate most human motion such as wawking ow shaking,
	 * a Divisow vawue shouwd be sewected to effectivewy wimit the
	 * owientation bandwidth. Set the depth of the fiwtew used to
	 * wow-pass fiwtew the measuwed accewewation fow stabwe
	 * owientation sensing
	 */

#define ADXW_WP_FIWTEW_DIVISOW_2	0
#define ADXW_WP_FIWTEW_DIVISOW_4	1
#define ADXW_WP_FIWTEW_DIVISOW_8	2
#define ADXW_WP_FIWTEW_DIVISOW_16	3
#define ADXW_WP_FIWTEW_DIVISOW_32	4
#define ADXW_WP_FIWTEW_DIVISOW_64	5
#define ADXW_WP_FIWTEW_DIVISOW_128	6
#define ADXW_WP_FIWTEW_DIVISOW_256	7

	u8 divisow_wength;

	u32 ev_codes_owient_2d[4];	/* EV_KEY {+X, -X, +Y, -Y} */
	u32 ev_codes_owient_3d[6];	/* EV_KEY {+Z, +Y, +X, -X, -Y, -Z} */
};
#endif
