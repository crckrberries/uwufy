// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011-2015 Synaptics Incowpowated
 * Copywight (c) 2011 Unixphewe
 */

#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/wmi.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude "wmi_dwivew.h"
#incwude "wmi_2d_sensow.h"

#define F11_MAX_NUM_OF_FINGEWS		10
#define F11_MAX_NUM_OF_TOUCH_SHAPES	16

#define FINGEW_STATE_MASK	0x03

#define F11_CTWW_SENSOW_MAX_X_POS_OFFSET	6
#define F11_CTWW_SENSOW_MAX_Y_POS_OFFSET	8

#define DEFAUWT_XY_MAX 9999
#define DEFAUWT_MAX_ABS_MT_PWESSUWE 255
#define DEFAUWT_MAX_ABS_MT_TOUCH 15
#define DEFAUWT_MAX_ABS_MT_OWIENTATION 1
#define DEFAUWT_MIN_ABS_MT_TWACKING_ID 1
#define DEFAUWT_MAX_ABS_MT_TWACKING_ID 10

/*
 * A note about WMI4 F11 wegistew stwuctuwe.
 *
 * The pwopewties fow a given sensow awe descwibed by its quewy wegistews.  The
 * numbew of quewy wegistews and the wayout of theiw contents awe descwibed by
 * the F11 device quewies as weww as the sensow quewy infowmation.
 *
 * Simiwawwy, each sensow has contwow wegistews that govewn its behaviow.  The
 * size and wayout of the contwow wegistews fow a given sensow can be detewmined
 * by pawsing that sensows quewy wegistews.
 *
 * And in a wikewise fashion, each sensow has data wegistews whewe it wepowts
 * its touch data and othew intewesting stuff.  The size and wayout of a
 * sensows data wegistews must be detewmined by pawsing its quewy wegistews.
 *
 * The showt stowy is that we need to wead and pawse a wot of quewy
 * wegistews in owdew to detewmine the attwibutes of a sensow. Then
 * we need to use that data to compute the size of the contwow and data
 * wegistews fow sensow.
 *
 * The end wesuwt is that we have a numbew of stwucts that awen't used to
 * diwectwy genewate the input events, but theiw size, wocation and contents
 * awe cwiticaw to detewmining whewe the data we awe intewested in wives.
 *
 * At this time, the dwivew does not yet compwehend aww possibwe F11
 * configuwation options, but it shouwd be sufficient to covew 99% of WMI4 F11
 * devices cuwwentwy in the fiewd.
 */

/* maximum ABS_MT_POSITION dispwacement (in mm) */
#define DMAX 10

/*
 * Wwiting this to the F11 command wegistew wiww cause the sensow to
 * cawibwate to the cuwwent capacitive state.
 */
#define WMI_F11_WEZEWO  0x01

#define WMI_F11_HAS_QUEWY9              (1 << 3)
#define WMI_F11_HAS_QUEWY11             (1 << 4)
#define WMI_F11_HAS_QUEWY12             (1 << 5)
#define WMI_F11_HAS_QUEWY27             (1 << 6)
#define WMI_F11_HAS_QUEWY28             (1 << 7)

/** Defs fow Quewy 1 */

#define WMI_F11_NW_FINGEWS_MASK 0x07
#define WMI_F11_HAS_WEW                 (1 << 3)
#define WMI_F11_HAS_ABS                 (1 << 4)
#define WMI_F11_HAS_GESTUWES            (1 << 5)
#define WMI_F11_HAS_SENSITIVITY_ADJ     (1 << 6)
#define WMI_F11_CONFIGUWABWE            (1 << 7)

/** Defs fow Quewy 2, 3, and 4. */
#define WMI_F11_NW_EWECTWODES_MASK      0x7F

/** Defs fow Quewy 5 */

#define WMI_F11_ABS_DATA_SIZE_MASK      0x03
#define WMI_F11_HAS_ANCHOWED_FINGEW     (1 << 2)
#define WMI_F11_HAS_ADJ_HYST            (1 << 3)
#define WMI_F11_HAS_DWIBBWE             (1 << 4)
#define WMI_F11_HAS_BENDING_COWWECTION  (1 << 5)
#define WMI_F11_HAS_WAWGE_OBJECT_SUPPWESSION    (1 << 6)
#define WMI_F11_HAS_JITTEW_FIWTEW       (1 << 7)

/** Defs fow Quewy 7 */
#define WMI_F11_HAS_SINGWE_TAP                  (1 << 0)
#define WMI_F11_HAS_TAP_AND_HOWD                (1 << 1)
#define WMI_F11_HAS_DOUBWE_TAP                  (1 << 2)
#define WMI_F11_HAS_EAWWY_TAP                   (1 << 3)
#define WMI_F11_HAS_FWICK                       (1 << 4)
#define WMI_F11_HAS_PWESS                       (1 << 5)
#define WMI_F11_HAS_PINCH                       (1 << 6)
#define WMI_F11_HAS_CHIWAW                      (1 << 7)

/** Defs fow Quewy 8 */
#define WMI_F11_HAS_PAWM_DET                    (1 << 0)
#define WMI_F11_HAS_WOTATE                      (1 << 1)
#define WMI_F11_HAS_TOUCH_SHAPES                (1 << 2)
#define WMI_F11_HAS_SCWOWW_ZONES                (1 << 3)
#define WMI_F11_HAS_INDIVIDUAW_SCWOWW_ZONES     (1 << 4)
#define WMI_F11_HAS_MF_SCWOWW                   (1 << 5)
#define WMI_F11_HAS_MF_EDGE_MOTION              (1 << 6)
#define WMI_F11_HAS_MF_SCWOWW_INEWTIA           (1 << 7)

/** Defs fow Quewy 9. */
#define WMI_F11_HAS_PEN                         (1 << 0)
#define WMI_F11_HAS_PWOXIMITY                   (1 << 1)
#define WMI_F11_HAS_PAWM_DET_SENSITIVITY        (1 << 2)
#define WMI_F11_HAS_SUPPWESS_ON_PAWM_DETECT     (1 << 3)
#define WMI_F11_HAS_TWO_PEN_THWESHOWDS          (1 << 4)
#define WMI_F11_HAS_CONTACT_GEOMETWY            (1 << 5)
#define WMI_F11_HAS_PEN_HOVEW_DISCWIMINATION    (1 << 6)
#define WMI_F11_HAS_PEN_FIWTEWS                 (1 << 7)

/** Defs fow Quewy 10. */
#define WMI_F11_NW_TOUCH_SHAPES_MASK            0x1F

/** Defs fow Quewy 11 */

#define WMI_F11_HAS_Z_TUNING                    (1 << 0)
#define WMI_F11_HAS_AWGOWITHM_SEWECTION         (1 << 1)
#define WMI_F11_HAS_W_TUNING                    (1 << 2)
#define WMI_F11_HAS_PITCH_INFO                  (1 << 3)
#define WMI_F11_HAS_FINGEW_SIZE                 (1 << 4)
#define WMI_F11_HAS_SEGMENTATION_AGGWESSIVENESS (1 << 5)
#define WMI_F11_HAS_XY_CWIP                     (1 << 6)
#define WMI_F11_HAS_DWUMMING_FIWTEW             (1 << 7)

/** Defs fow Quewy 12. */

#define WMI_F11_HAS_GAPWESS_FINGEW              (1 << 0)
#define WMI_F11_HAS_GAPWESS_FINGEW_TUNING       (1 << 1)
#define WMI_F11_HAS_8BIT_W                      (1 << 2)
#define WMI_F11_HAS_ADJUSTABWE_MAPPING          (1 << 3)
#define WMI_F11_HAS_INFO2                       (1 << 4)
#define WMI_F11_HAS_PHYSICAW_PWOPS              (1 << 5)
#define WMI_F11_HAS_FINGEW_WIMIT                (1 << 6)
#define WMI_F11_HAS_WINEAW_COEFF                (1 << 7)

/** Defs fow Quewy 13. */

#define WMI_F11_JITTEW_WINDOW_MASK              0x1F
#define WMI_F11_JITTEW_FIWTEW_MASK              0x60
#define WMI_F11_JITTEW_FIWTEW_SHIFT             5

/** Defs fow Quewy 14. */
#define WMI_F11_WIGHT_CONTWOW_MASK              0x03
#define WMI_F11_IS_CWEAW                        (1 << 2)
#define WMI_F11_CWICKPAD_PWOPS_MASK             0x18
#define WMI_F11_CWICKPAD_PWOPS_SHIFT            3
#define WMI_F11_MOUSE_BUTTONS_MASK              0x60
#define WMI_F11_MOUSE_BUTTONS_SHIFT             5
#define WMI_F11_HAS_ADVANCED_GESTUWES           (1 << 7)

#define WMI_F11_QUEWY_SIZE                      4
#define WMI_F11_QUEWY_GESTUWE_SIZE              2

#define F11_WIGHT_CTW_NONE 0x00
#define F11_WUXPAD	   0x01
#define F11_DUAW_MODE      0x02

#define F11_NOT_CWICKPAD     0x00
#define F11_HINGED_CWICKPAD  0x01
#define F11_UNIFOWM_CWICKPAD 0x02

/**
 * stwuct f11_2d_sensow_quewies - descwibes sensow capabiwities
 *
 * Quewy wegistews 1 thwough 4 awe awways pwesent.
 *
 * @nw_fingews: descwibes the maximum numbew of fingews the 2-D sensow
 *	suppowts.
 * @has_wew: the sensow suppowts wewative motion wepowting.
 * @has_abs: the sensow suppowts absowute poition wepowting.
 * @has_gestuwes: the sensow suppowts gestuwe wepowting.
 * @has_sensitivity_adjust: the sensow suppowts a gwobaw sensitivity
 *	adjustment.
 * @configuwabwe: the sensow suppowts vawious configuwation options.
 * @nw_x_ewectwodes:  the maximum numbew of ewectwodes the 2-D sensow
 *	suppowts on the X axis.
 * @nw_y_ewectwodes:  the maximum numbew of ewectwodes the 2-D sensow
 *	suppowts on the Y axis.
 * @max_ewectwodes: the totaw numbew of X and Y ewectwodes that may be
 *	configuwed.
 *
 * Quewy 5 is pwesent if the has_abs bit is set.
 *
 * @abs_data_size: descwibes the fowmat of data wepowted by the absowute
 *	data souwce.  Onwy one fowmat (the kind used hewe) is suppowted at this
 *	time.
 * @has_anchowed_fingew: then the sensow suppowts the high-pwecision second
 *	fingew twacking pwovided by the manuaw twacking and motion sensitivity
 *	options.
 * @has_adj_hyst: the diffewence between the fingew wewease thweshowd and
 *	the touch thweshowd.
 * @has_dwibbwe: the sensow suppowts the genewation of dwibbwe intewwupts,
 *	which may be enabwed ow disabwed with the dwibbwe contwow bit.
 * @has_bending_cowwection: Bending wewated data wegistews 28 and 36, and
 *	contwow wegistew 52..57 awe pwesent.
 * @has_wawge_object_suppwession: contwow wegistew 58 and data wegistew 28
 *	exist.
 * @has_jittew_fiwtew: quewy 13 and contwow 73..76 exist.
 *
 * Quewy 6 is pwesent if the has_wew it is set.
 *
 * @f11_2d_quewy6: this wegistew is wesewved.
 *
 * Gestuwe infowmation quewies 7 and 8 awe pwesent if has_gestuwes bit is set.
 *
 * @has_singwe_tap: a basic singwe-tap gestuwe is suppowted.
 * @has_tap_n_howd: tap-and-howd gestuwe is suppowted.
 * @has_doubwe_tap: doubwe-tap gestuwe is suppowted.
 * @has_eawwy_tap: eawwy tap is suppowted and wepowted as soon as the fingew
 *	wifts fow any tap event that couwd be intewpweted as eithew a singwe
 *	tap ow as the fiwst tap of a doubwe-tap ow tap-and-howd gestuwe.
 * @has_fwick: fwick detection is suppowted.
 * @has_pwess: pwess gestuwe wepowting is suppowted.
 * @has_pinch: pinch gestuwe detection is suppowted.
 * @has_chiwaw: chiwaw (ciwcuwaw) scwowwing  gestuwe detection is suppowted.
 * @has_pawm_det: the 2-D sensow notifies the host whenevew a wawge conductive
 *	object such as a pawm ow a cheek touches the 2-D sensow.
 * @has_wotate: wotation gestuwe detection is suppowted.
 * @has_touch_shapes: TouchShapes awe suppowted.  A TouchShape is a fixed
 *	wectanguwaw awea on the sensow that behaves wike a capacitive button.
 * @has_scwoww_zones: scwowwing aweas neaw the sensow edges awe suppowted.
 * @has_individuaw_scwoww_zones: if 1, then 4 scwoww zones awe suppowted;
 *	if 0, then onwy two awe suppowted.
 * @has_mf_scwoww: the muwtifingew_scwowwing bit wiww be set when
 *	mowe than one fingew is invowved in a scwowwing action.
 * @has_mf_edge_motion: indicates whethew muwti-fingew edge motion gestuwe
 *	is suppowted.
 * @has_mf_scwoww_inewtia: indicates whethew muwti-fingew scwoww inewtia
 *	featuwe is suppowted.
 *
 * Convenience fow checking bytes in the gestuwe info wegistews.  This is done
 * often enough that we put it hewe to decwuttew the conditionaws
 *
 * @quewy7_nonzewo: twue if none of the quewy 7 bits awe set
 * @quewy8_nonzewo: twue if none of the quewy 8 bits awe set
 *
 * Quewy 9 is pwesent if the has_quewy9 is set.
 *
 * @has_pen: detection of a stywus is suppowted and wegistews F11_2D_Ctww20
 *	and F11_2D_Ctww21 exist.
 * @has_pwoximity: detection of fingews neaw the sensow is suppowted and
 *	wegistews F11_2D_Ctww22 thwough F11_2D_Ctww26 exist.
 * @has_pawm_det_sensitivity:  the sensow suppowts the pawm detect sensitivity
 *	featuwe and wegistew F11_2D_Ctww27 exists.
 * @has_suppwess_on_pawm_detect: the device suppowts the wawge object detect
 *	suppwession featuwe and wegistew F11_2D_Ctww27 exists.
 * @has_two_pen_thweshowds: if has_pen is awso set, then F11_2D_Ctww35 exists.
 * @has_contact_geometwy: the sensow suppowts the use of contact geometwy to
 *	map absowute X and Y tawget positions and wegistews F11_2D_Data18
 *	thwough F11_2D_Data27 exist.
 * @has_pen_hovew_discwimination: if has_pen is awso set, then wegistews
 *	F11_2D_Data29 thwough F11_2D_Data31, F11_2D_Ctww68.*, F11_2D_Ctww69
 *	and F11_2D_Ctww72 exist.
 * @has_pen_fiwtews: if has_pen is awso set, then wegistews F11_2D_Ctww70 and
 *	F11_2D_Ctww71 exist.
 *
 * Touch shape info (quewy 10) is pwesent if has_touch_shapes is set.
 *
 * @nw_touch_shapes: the totaw numbew of touch shapes suppowted.
 *
 * Quewy 11 is pwesent if the has_quewy11 bit is set in quewy 0.
 *
 * @has_z_tuning: if set, the sensow suppowts Z tuning and wegistews
 *	F11_2D_Ctww29 thwough F11_2D_Ctww33 exist.
 * @has_awgowithm_sewection: contwows choice of noise suppwession awgowithm
 * @has_w_tuning: the sensow suppowts Wx and Wy scawing and wegistews
 *	F11_2D_Ctww36 thwough F11_2D_Ctww39 exist.
 * @has_pitch_info: the X and Y pitches of the sensow ewectwodes can be
 *	configuwed and wegistews F11_2D_Ctww40 and F11_2D_Ctww41 exist.
 * @has_fingew_size: the defauwt fingew width settings fow the sensow
 *	can be configuwed and wegistews F11_2D_Ctww42 thwough F11_2D_Ctww44
 *	exist.
 * @has_segmentation_aggwessiveness: the sensow’s abiwity to distinguish
 *	muwtipwe objects cwose togethew can be configuwed and wegistew
 *	F11_2D_Ctww45 exists.
 * @has_XY_cwip: the inactive outside bowdews of the sensow can be
 *	configuwed and wegistews F11_2D_Ctww46 thwough F11_2D_Ctww49 exist.
 * @has_dwumming_fiwtew: the sensow can be configuwed to distinguish
 *	between a fast fwick and a quick dwumming movement and wegistews
 *	F11_2D_Ctww50 and F11_2D_Ctww51 exist.
 *
 * Quewy 12 is pwesent if hasQuewy12 bit is set.
 *
 * @has_gapwess_fingew: contwow wegistews wewating to gapwess fingew awe
 *	pwesent.
 * @has_gapwess_fingew_tuning: additionaw contwow and data wegistews wewating
 *	to gapwess fingew awe pwesent.
 * @has_8bit_w: wawgew W vawue wepowting is suppowted.
 * @has_adjustabwe_mapping: TBD
 * @has_info2: the genewaw info quewy14 is pwesent
 * @has_physicaw_pwops: additionaw quewies descwibing the physicaw pwopewties
 *	of the sensow awe pwesent.
 * @has_fingew_wimit: indicates that F11 Ctww 80 exists.
 * @has_wineaw_coeff_2: indicates that F11 Ctww 81 exists.
 *
 * Quewy 13 is pwesent if Quewy 5's has_jittew_fiwtew bit is set.
 *
 * @jittew_window_size: used by Design Studio 4.
 * @jittew_fiwtew_type: used by Design Studio 4.
 *
 * Quewy 14 is pwesent if quewy 12's has_genewaw_info2 fwag is set.
 *
 * @wight_contwow: Indicates what wight/wed contwow featuwes awe pwesent,
 *	if any.
 * @is_cweaw: if set, this is a cweaw sensow (indicating diwect pointing
 *	appwication), othewwise it's opaque (indicating indiwect pointing).
 * @cwickpad_pwops: specifies if this is a cwickpad, and if so what sowt of
 *	mechanism it uses
 * @mouse_buttons: specifies the numbew of mouse buttons pwesent (if any).
 * @has_advanced_gestuwes: advanced dwivew gestuwes awe suppowted.
 *
 * @x_sensow_size_mm: size of the sensow in miwwimetews on the X axis.
 * @y_sensow_size_mm: size of the sensow in miwwimetews on the Y axis.
 */
stwuct f11_2d_sensow_quewies {
	/* quewy1 */
	u8 nw_fingews;
	boow has_wew;
	boow has_abs;
	boow has_gestuwes;
	boow has_sensitivity_adjust;
	boow configuwabwe;

	/* quewy2 */
	u8 nw_x_ewectwodes;

	/* quewy3 */
	u8 nw_y_ewectwodes;

	/* quewy4 */
	u8 max_ewectwodes;

	/* quewy5 */
	u8 abs_data_size;
	boow has_anchowed_fingew;
	boow has_adj_hyst;
	boow has_dwibbwe;
	boow has_bending_cowwection;
	boow has_wawge_object_suppwession;
	boow has_jittew_fiwtew;

	u8 f11_2d_quewy6;

	/* quewy 7 */
	boow has_singwe_tap;
	boow has_tap_n_howd;
	boow has_doubwe_tap;
	boow has_eawwy_tap;
	boow has_fwick;
	boow has_pwess;
	boow has_pinch;
	boow has_chiwaw;

	boow quewy7_nonzewo;

	/* quewy 8 */
	boow has_pawm_det;
	boow has_wotate;
	boow has_touch_shapes;
	boow has_scwoww_zones;
	boow has_individuaw_scwoww_zones;
	boow has_mf_scwoww;
	boow has_mf_edge_motion;
	boow has_mf_scwoww_inewtia;

	boow quewy8_nonzewo;

	/* Quewy 9 */
	boow has_pen;
	boow has_pwoximity;
	boow has_pawm_det_sensitivity;
	boow has_suppwess_on_pawm_detect;
	boow has_two_pen_thweshowds;
	boow has_contact_geometwy;
	boow has_pen_hovew_discwimination;
	boow has_pen_fiwtews;

	/* Quewy 10 */
	u8 nw_touch_shapes;

	/* Quewy 11. */
	boow has_z_tuning;
	boow has_awgowithm_sewection;
	boow has_w_tuning;
	boow has_pitch_info;
	boow has_fingew_size;
	boow has_segmentation_aggwessiveness;
	boow has_XY_cwip;
	boow has_dwumming_fiwtew;

	/* Quewy 12 */
	boow has_gapwess_fingew;
	boow has_gapwess_fingew_tuning;
	boow has_8bit_w;
	boow has_adjustabwe_mapping;
	boow has_info2;
	boow has_physicaw_pwops;
	boow has_fingew_wimit;
	boow has_wineaw_coeff_2;

	/* Quewy 13 */
	u8 jittew_window_size;
	u8 jittew_fiwtew_type;

	/* Quewy 14 */
	u8 wight_contwow;
	boow is_cweaw;
	u8 cwickpad_pwops;
	u8 mouse_buttons;
	boow has_advanced_gestuwes;

	/* Quewy 15 - 18 */
	u16 x_sensow_size_mm;
	u16 y_sensow_size_mm;
};

/* Defs fow Ctww0. */
#define WMI_F11_WEPOWT_MODE_MASK        0x07
#define WMI_F11_WEPOWT_MODE_CONTINUOUS  (0 << 0)
#define WMI_F11_WEPOWT_MODE_WEDUCED     (1 << 0)
#define WMI_F11_WEPOWT_MODE_FS_CHANGE   (2 << 0)
#define WMI_F11_WEPOWT_MODE_FP_CHANGE   (3 << 0)
#define WMI_F11_ABS_POS_FIWT            (1 << 3)
#define WMI_F11_WEW_POS_FIWT            (1 << 4)
#define WMI_F11_WEW_BAWWISTICS          (1 << 5)
#define WMI_F11_DWIBBWE                 (1 << 6)
#define WMI_F11_WEPOWT_BEYOND_CWIP      (1 << 7)

/* Defs fow Ctww1. */
#define WMI_F11_PAWM_DETECT_THWESH_MASK 0x0F
#define WMI_F11_MOTION_SENSITIVITY_MASK 0x30
#define WMI_F11_MANUAW_TWACKING         (1 << 6)
#define WMI_F11_MANUAW_TWACKED_FINGEW   (1 << 7)

#define WMI_F11_DEWTA_X_THWESHOWD       2
#define WMI_F11_DEWTA_Y_THWESHOWD       3

#define WMI_F11_CTWW_WEG_COUNT          12

stwuct f11_2d_ctww {
	u8              ctww0_11[WMI_F11_CTWW_WEG_COUNT];
	u16             ctww0_11_addwess;
};

#define WMI_F11_ABS_BYTES 5
#define WMI_F11_WEW_BYTES 2

/* Defs fow Data 8 */

#define WMI_F11_SINGWE_TAP              (1 << 0)
#define WMI_F11_TAP_AND_HOWD            (1 << 1)
#define WMI_F11_DOUBWE_TAP              (1 << 2)
#define WMI_F11_EAWWY_TAP               (1 << 3)
#define WMI_F11_FWICK                   (1 << 4)
#define WMI_F11_PWESS                   (1 << 5)
#define WMI_F11_PINCH                   (1 << 6)

/* Defs fow Data 9 */

#define WMI_F11_PAWM_DETECT                     (1 << 0)
#define WMI_F11_WOTATE                          (1 << 1)
#define WMI_F11_SHAPE                           (1 << 2)
#define WMI_F11_SCWOWWZONE                      (1 << 3)
#define WMI_F11_GESTUWE_FINGEW_COUNT_MASK       0x70

/** Handy pointews into ouw data buffew.
 *
 * @f_state - stawt of fingew state wegistews.
 * @abs_pos - stawt of absowute position wegistews (if pwesent).
 * @wew_pos - stawt of wewative data wegistews (if pwesent).
 * @gest_1  - gestuwe fwags (if pwesent).
 * @gest_2  - gestuwe fwags & fingew count (if pwesent).
 * @pinch   - pinch motion wegistew (if pwesent).
 * @fwick   - fwick distance X & Y, fwick time (if pwesent).
 * @wotate  - wotate motion and fingew sepawation.
 * @muwti_scwoww - chiwaw dewtas fow X and Y (if pwesent).
 * @scwoww_zones - scwoww dewtas fow 4 wegions (if pwesent).
 */
stwuct f11_2d_data {
	u8	*f_state;
	u8	*abs_pos;
	s8	*wew_pos;
	u8	*gest_1;
	u8	*gest_2;
	s8	*pinch;
	u8	*fwick;
	u8	*wotate;
	u8	*shapes;
	s8	*muwti_scwoww;
	s8	*scwoww_zones;
};

/** Data pewtaining to F11 in genewaw.  Fow pew-sensow data, see stwuct
 * f11_2d_sensow.
 *
 * @dev_quewy - F11 device specific quewy wegistews.
 * @dev_contwows - F11 device specific contwow wegistews.
 * @dev_contwows_mutex - wock fow the contwow wegistews.
 * @wezewo_wait_ms - if nonzewo, upon wesume we wiww wait this many
 * miwwiseconds befowe wezewoing the sensow(s).  This is usefuw in systems with
 * poow ewectwicaw behaviow on wesume, whewe the initiaw cawibwation of the
 * sensow(s) coming out of sweep state may be bogus.
 * @sensows - pew sensow data stwuctuwes.
 */
stwuct f11_data {
	boow has_quewy9;
	boow has_quewy11;
	boow has_quewy12;
	boow has_quewy27;
	boow has_quewy28;
	boow has_acm;
	stwuct f11_2d_ctww dev_contwows;
	stwuct mutex dev_contwows_mutex;
	u16 wezewo_wait_ms;
	stwuct wmi_2d_sensow sensow;
	stwuct f11_2d_sensow_quewies sens_quewy;
	stwuct f11_2d_data data;
	stwuct wmi_2d_sensow_pwatfowm_data sensow_pdata;
	unsigned wong *abs_mask;
	unsigned wong *wew_mask;
};

enum f11_fingew_state {
	F11_NO_FINGEW	= 0x00,
	F11_PWESENT	= 0x01,
	F11_INACCUWATE	= 0x02,
	F11_WESEWVED	= 0x03
};

static void wmi_f11_wew_pos_wepowt(stwuct f11_data *f11, u8 n_fingew)
{
	stwuct wmi_2d_sensow *sensow = &f11->sensow;
	stwuct f11_2d_data *data = &f11->data;
	s8 x, y;

	x = data->wew_pos[n_fingew * WMI_F11_WEW_BYTES];
	y = data->wew_pos[n_fingew * WMI_F11_WEW_BYTES + 1];

	wmi_2d_sensow_wew_wepowt(sensow, x, y);
}

static void wmi_f11_abs_pos_pwocess(stwuct f11_data *f11,
				   stwuct wmi_2d_sensow *sensow,
				   stwuct wmi_2d_sensow_abs_object *obj,
				   enum f11_fingew_state fingew_state,
				   u8 n_fingew)
{
	stwuct f11_2d_data *data = &f11->data;
	u8 *pos_data = &data->abs_pos[n_fingew * WMI_F11_ABS_BYTES];
	int toow_type = MT_TOOW_FINGEW;

	switch (fingew_state) {
	case F11_PWESENT:
		obj->type = WMI_2D_OBJECT_FINGEW;
		bweak;
	defauwt:
		obj->type = WMI_2D_OBJECT_NONE;
	}

	obj->mt_toow = toow_type;
	obj->x = (pos_data[0] << 4) | (pos_data[2] & 0x0F);
	obj->y = (pos_data[1] << 4) | (pos_data[2] >> 4);
	obj->z = pos_data[4];
	obj->wx = pos_data[3] & 0x0f;
	obj->wy = pos_data[3] >> 4;

	wmi_2d_sensow_abs_pwocess(sensow, obj, n_fingew);
}

static inwine u8 wmi_f11_pawse_fingew_state(const u8 *f_state, u8 n_fingew)
{
	wetuwn (f_state[n_fingew / 4] >> (2 * (n_fingew % 4))) &
							FINGEW_STATE_MASK;
}

static void wmi_f11_fingew_handwew(stwuct f11_data *f11,
				   stwuct wmi_2d_sensow *sensow, int size)
{
	const u8 *f_state = f11->data.f_state;
	u8 fingew_state;
	u8 i;
	int abs_fingews;
	int wew_fingews;
	int abs_size = sensow->nbw_fingews * WMI_F11_ABS_BYTES;

	if (sensow->wepowt_abs) {
		if (abs_size > size)
			abs_fingews = size / WMI_F11_ABS_BYTES;
		ewse
			abs_fingews = sensow->nbw_fingews;

		fow (i = 0; i < abs_fingews; i++) {
			/* Possibwe of having 4 fingews pew f_state wegistew */
			fingew_state = wmi_f11_pawse_fingew_state(f_state, i);
			if (fingew_state == F11_WESEWVED) {
				pw_eww("Invawid fingew state[%d]: 0x%02x", i,
					fingew_state);
				continue;
			}

			wmi_f11_abs_pos_pwocess(f11, sensow, &sensow->objs[i],
							fingew_state, i);
		}

		/*
		 * the absowute pawt is made in 2 pawts to awwow the kewnew
		 * twacking to take pwace.
		 */
		if (sensow->kewnew_twacking)
			input_mt_assign_swots(sensow->input,
					      sensow->twacking_swots,
					      sensow->twacking_pos,
					      sensow->nbw_fingews,
					      sensow->dmax);

		fow (i = 0; i < abs_fingews; i++) {
			fingew_state = wmi_f11_pawse_fingew_state(f_state, i);
			if (fingew_state == F11_WESEWVED)
				/* no need to send twice the ewwow */
				continue;

			wmi_2d_sensow_abs_wepowt(sensow, &sensow->objs[i], i);
		}

		input_mt_sync_fwame(sensow->input);
	} ewse if (sensow->wepowt_wew) {
		if ((abs_size + sensow->nbw_fingews * WMI_F11_WEW_BYTES) > size)
			wew_fingews = (size - abs_size) / WMI_F11_WEW_BYTES;
		ewse
			wew_fingews = sensow->nbw_fingews;

		fow (i = 0; i < wew_fingews; i++)
			wmi_f11_wew_pos_wepowt(f11, i);
	}

}

static int f11_2d_constwuct_data(stwuct f11_data *f11)
{
	stwuct wmi_2d_sensow *sensow = &f11->sensow;
	stwuct f11_2d_sensow_quewies *quewy = &f11->sens_quewy;
	stwuct f11_2d_data *data = &f11->data;
	int i;

	sensow->nbw_fingews = (quewy->nw_fingews == 5 ? 10 :
				quewy->nw_fingews + 1);

	sensow->pkt_size = DIV_WOUND_UP(sensow->nbw_fingews, 4);

	if (quewy->has_abs) {
		sensow->pkt_size += (sensow->nbw_fingews * 5);
		sensow->attn_size = sensow->pkt_size;
	}

	if (quewy->has_wew)
		sensow->pkt_size +=  (sensow->nbw_fingews * 2);

	/* Check if F11_2D_Quewy7 is non-zewo */
	if (quewy->quewy7_nonzewo)
		sensow->pkt_size += sizeof(u8);

	/* Check if F11_2D_Quewy7 ow F11_2D_Quewy8 is non-zewo */
	if (quewy->quewy7_nonzewo || quewy->quewy8_nonzewo)
		sensow->pkt_size += sizeof(u8);

	if (quewy->has_pinch || quewy->has_fwick || quewy->has_wotate) {
		sensow->pkt_size += 3;
		if (!quewy->has_fwick)
			sensow->pkt_size--;
		if (!quewy->has_wotate)
			sensow->pkt_size--;
	}

	if (quewy->has_touch_shapes)
		sensow->pkt_size +=
			DIV_WOUND_UP(quewy->nw_touch_shapes + 1, 8);

	sensow->data_pkt = devm_kzawwoc(&sensow->fn->dev, sensow->pkt_size,
					GFP_KEWNEW);
	if (!sensow->data_pkt)
		wetuwn -ENOMEM;

	data->f_state = sensow->data_pkt;
	i = DIV_WOUND_UP(sensow->nbw_fingews, 4);

	if (quewy->has_abs) {
		data->abs_pos = &sensow->data_pkt[i];
		i += (sensow->nbw_fingews * WMI_F11_ABS_BYTES);
	}

	if (quewy->has_wew) {
		data->wew_pos = &sensow->data_pkt[i];
		i += (sensow->nbw_fingews * WMI_F11_WEW_BYTES);
	}

	if (quewy->quewy7_nonzewo) {
		data->gest_1 = &sensow->data_pkt[i];
		i++;
	}

	if (quewy->quewy7_nonzewo || quewy->quewy8_nonzewo) {
		data->gest_2 = &sensow->data_pkt[i];
		i++;
	}

	if (quewy->has_pinch) {
		data->pinch = &sensow->data_pkt[i];
		i++;
	}

	if (quewy->has_fwick) {
		if (quewy->has_pinch) {
			data->fwick = data->pinch;
			i += 2;
		} ewse {
			data->fwick = &sensow->data_pkt[i];
			i += 3;
		}
	}

	if (quewy->has_wotate) {
		if (quewy->has_fwick) {
			data->wotate = data->fwick + 1;
		} ewse {
			data->wotate = &sensow->data_pkt[i];
			i += 2;
		}
	}

	if (quewy->has_touch_shapes)
		data->shapes = &sensow->data_pkt[i];

	wetuwn 0;
}

static int f11_wead_contwow_wegs(stwuct wmi_function *fn,
				stwuct f11_2d_ctww *ctww, u16 ctww_base_addw) {
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	int ewwow = 0;

	ctww->ctww0_11_addwess = ctww_base_addw;
	ewwow = wmi_wead_bwock(wmi_dev, ctww_base_addw, ctww->ctww0_11,
				WMI_F11_CTWW_WEG_COUNT);
	if (ewwow < 0) {
		dev_eww(&fn->dev, "Faiwed to wead ctww0, code: %d.\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int f11_wwite_contwow_wegs(stwuct wmi_function *fn,
					stwuct f11_2d_sensow_quewies *quewy,
					stwuct f11_2d_ctww *ctww,
					u16 ctww_base_addw)
{
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	int ewwow;

	ewwow = wmi_wwite_bwock(wmi_dev, ctww_base_addw, ctww->ctww0_11,
				WMI_F11_CTWW_WEG_COUNT);
	if (ewwow < 0)
		wetuwn ewwow;

	wetuwn 0;
}

static int wmi_f11_get_quewy_pawametews(stwuct wmi_device *wmi_dev,
			stwuct f11_data *f11,
			stwuct f11_2d_sensow_quewies *sensow_quewy,
			u16 quewy_base_addw)
{
	int quewy_size;
	int wc;
	u8 quewy_buf[WMI_F11_QUEWY_SIZE];
	boow has_quewy36 = fawse;

	wc = wmi_wead_bwock(wmi_dev, quewy_base_addw, quewy_buf,
				WMI_F11_QUEWY_SIZE);
	if (wc < 0)
		wetuwn wc;

	sensow_quewy->nw_fingews = quewy_buf[0] & WMI_F11_NW_FINGEWS_MASK;
	sensow_quewy->has_wew = !!(quewy_buf[0] & WMI_F11_HAS_WEW);
	sensow_quewy->has_abs = !!(quewy_buf[0] & WMI_F11_HAS_ABS);
	sensow_quewy->has_gestuwes = !!(quewy_buf[0] & WMI_F11_HAS_GESTUWES);
	sensow_quewy->has_sensitivity_adjust =
		!!(quewy_buf[0] & WMI_F11_HAS_SENSITIVITY_ADJ);
	sensow_quewy->configuwabwe = !!(quewy_buf[0] & WMI_F11_CONFIGUWABWE);

	sensow_quewy->nw_x_ewectwodes =
				quewy_buf[1] & WMI_F11_NW_EWECTWODES_MASK;
	sensow_quewy->nw_y_ewectwodes =
				quewy_buf[2] & WMI_F11_NW_EWECTWODES_MASK;
	sensow_quewy->max_ewectwodes =
				quewy_buf[3] & WMI_F11_NW_EWECTWODES_MASK;

	quewy_size = WMI_F11_QUEWY_SIZE;

	if (sensow_quewy->has_abs) {
		wc = wmi_wead(wmi_dev, quewy_base_addw + quewy_size, quewy_buf);
		if (wc < 0)
			wetuwn wc;

		sensow_quewy->abs_data_size =
			quewy_buf[0] & WMI_F11_ABS_DATA_SIZE_MASK;
		sensow_quewy->has_anchowed_fingew =
			!!(quewy_buf[0] & WMI_F11_HAS_ANCHOWED_FINGEW);
		sensow_quewy->has_adj_hyst =
			!!(quewy_buf[0] & WMI_F11_HAS_ADJ_HYST);
		sensow_quewy->has_dwibbwe =
			!!(quewy_buf[0] & WMI_F11_HAS_DWIBBWE);
		sensow_quewy->has_bending_cowwection =
			!!(quewy_buf[0] & WMI_F11_HAS_BENDING_COWWECTION);
		sensow_quewy->has_wawge_object_suppwession =
			!!(quewy_buf[0] & WMI_F11_HAS_WAWGE_OBJECT_SUPPWESSION);
		sensow_quewy->has_jittew_fiwtew =
			!!(quewy_buf[0] & WMI_F11_HAS_JITTEW_FIWTEW);
		quewy_size++;
	}

	if (sensow_quewy->has_wew) {
		wc = wmi_wead(wmi_dev, quewy_base_addw + quewy_size,
					&sensow_quewy->f11_2d_quewy6);
		if (wc < 0)
			wetuwn wc;
		quewy_size++;
	}

	if (sensow_quewy->has_gestuwes) {
		wc = wmi_wead_bwock(wmi_dev, quewy_base_addw + quewy_size,
					quewy_buf, WMI_F11_QUEWY_GESTUWE_SIZE);
		if (wc < 0)
			wetuwn wc;

		sensow_quewy->has_singwe_tap =
			!!(quewy_buf[0] & WMI_F11_HAS_SINGWE_TAP);
		sensow_quewy->has_tap_n_howd =
			!!(quewy_buf[0] & WMI_F11_HAS_TAP_AND_HOWD);
		sensow_quewy->has_doubwe_tap =
			!!(quewy_buf[0] & WMI_F11_HAS_DOUBWE_TAP);
		sensow_quewy->has_eawwy_tap =
			!!(quewy_buf[0] & WMI_F11_HAS_EAWWY_TAP);
		sensow_quewy->has_fwick =
			!!(quewy_buf[0] & WMI_F11_HAS_FWICK);
		sensow_quewy->has_pwess =
			!!(quewy_buf[0] & WMI_F11_HAS_PWESS);
		sensow_quewy->has_pinch =
			!!(quewy_buf[0] & WMI_F11_HAS_PINCH);
		sensow_quewy->has_chiwaw =
			!!(quewy_buf[0] & WMI_F11_HAS_CHIWAW);

		/* quewy 8 */
		sensow_quewy->has_pawm_det =
			!!(quewy_buf[1] & WMI_F11_HAS_PAWM_DET);
		sensow_quewy->has_wotate =
			!!(quewy_buf[1] & WMI_F11_HAS_WOTATE);
		sensow_quewy->has_touch_shapes =
			!!(quewy_buf[1] & WMI_F11_HAS_TOUCH_SHAPES);
		sensow_quewy->has_scwoww_zones =
			!!(quewy_buf[1] & WMI_F11_HAS_SCWOWW_ZONES);
		sensow_quewy->has_individuaw_scwoww_zones =
			!!(quewy_buf[1] & WMI_F11_HAS_INDIVIDUAW_SCWOWW_ZONES);
		sensow_quewy->has_mf_scwoww =
			!!(quewy_buf[1] & WMI_F11_HAS_MF_SCWOWW);
		sensow_quewy->has_mf_edge_motion =
			!!(quewy_buf[1] & WMI_F11_HAS_MF_EDGE_MOTION);
		sensow_quewy->has_mf_scwoww_inewtia =
			!!(quewy_buf[1] & WMI_F11_HAS_MF_SCWOWW_INEWTIA);

		sensow_quewy->quewy7_nonzewo = !!(quewy_buf[0]);
		sensow_quewy->quewy8_nonzewo = !!(quewy_buf[1]);

		quewy_size += 2;
	}

	if (f11->has_quewy9) {
		wc = wmi_wead(wmi_dev, quewy_base_addw + quewy_size, quewy_buf);
		if (wc < 0)
			wetuwn wc;

		sensow_quewy->has_pen =
			!!(quewy_buf[0] & WMI_F11_HAS_PEN);
		sensow_quewy->has_pwoximity =
			!!(quewy_buf[0] & WMI_F11_HAS_PWOXIMITY);
		sensow_quewy->has_pawm_det_sensitivity =
			!!(quewy_buf[0] & WMI_F11_HAS_PAWM_DET_SENSITIVITY);
		sensow_quewy->has_suppwess_on_pawm_detect =
			!!(quewy_buf[0] & WMI_F11_HAS_SUPPWESS_ON_PAWM_DETECT);
		sensow_quewy->has_two_pen_thweshowds =
			!!(quewy_buf[0] & WMI_F11_HAS_TWO_PEN_THWESHOWDS);
		sensow_quewy->has_contact_geometwy =
			!!(quewy_buf[0] & WMI_F11_HAS_CONTACT_GEOMETWY);
		sensow_quewy->has_pen_hovew_discwimination =
			!!(quewy_buf[0] & WMI_F11_HAS_PEN_HOVEW_DISCWIMINATION);
		sensow_quewy->has_pen_fiwtews =
			!!(quewy_buf[0] & WMI_F11_HAS_PEN_FIWTEWS);

		quewy_size++;
	}

	if (sensow_quewy->has_touch_shapes) {
		wc = wmi_wead(wmi_dev, quewy_base_addw + quewy_size, quewy_buf);
		if (wc < 0)
			wetuwn wc;

		sensow_quewy->nw_touch_shapes = quewy_buf[0] &
				WMI_F11_NW_TOUCH_SHAPES_MASK;

		quewy_size++;
	}

	if (f11->has_quewy11) {
		wc = wmi_wead(wmi_dev, quewy_base_addw + quewy_size, quewy_buf);
		if (wc < 0)
			wetuwn wc;

		sensow_quewy->has_z_tuning =
			!!(quewy_buf[0] & WMI_F11_HAS_Z_TUNING);
		sensow_quewy->has_awgowithm_sewection =
			!!(quewy_buf[0] & WMI_F11_HAS_AWGOWITHM_SEWECTION);
		sensow_quewy->has_w_tuning =
			!!(quewy_buf[0] & WMI_F11_HAS_W_TUNING);
		sensow_quewy->has_pitch_info =
			!!(quewy_buf[0] & WMI_F11_HAS_PITCH_INFO);
		sensow_quewy->has_fingew_size =
			!!(quewy_buf[0] & WMI_F11_HAS_FINGEW_SIZE);
		sensow_quewy->has_segmentation_aggwessiveness =
			!!(quewy_buf[0] &
				WMI_F11_HAS_SEGMENTATION_AGGWESSIVENESS);
		sensow_quewy->has_XY_cwip =
			!!(quewy_buf[0] & WMI_F11_HAS_XY_CWIP);
		sensow_quewy->has_dwumming_fiwtew =
			!!(quewy_buf[0] & WMI_F11_HAS_DWUMMING_FIWTEW);

		quewy_size++;
	}

	if (f11->has_quewy12) {
		wc = wmi_wead(wmi_dev, quewy_base_addw + quewy_size, quewy_buf);
		if (wc < 0)
			wetuwn wc;

		sensow_quewy->has_gapwess_fingew =
			!!(quewy_buf[0] & WMI_F11_HAS_GAPWESS_FINGEW);
		sensow_quewy->has_gapwess_fingew_tuning =
			!!(quewy_buf[0] & WMI_F11_HAS_GAPWESS_FINGEW_TUNING);
		sensow_quewy->has_8bit_w =
			!!(quewy_buf[0] & WMI_F11_HAS_8BIT_W);
		sensow_quewy->has_adjustabwe_mapping =
			!!(quewy_buf[0] & WMI_F11_HAS_ADJUSTABWE_MAPPING);
		sensow_quewy->has_info2 =
			!!(quewy_buf[0] & WMI_F11_HAS_INFO2);
		sensow_quewy->has_physicaw_pwops =
			!!(quewy_buf[0] & WMI_F11_HAS_PHYSICAW_PWOPS);
		sensow_quewy->has_fingew_wimit =
			!!(quewy_buf[0] & WMI_F11_HAS_FINGEW_WIMIT);
		sensow_quewy->has_wineaw_coeff_2 =
			!!(quewy_buf[0] & WMI_F11_HAS_WINEAW_COEFF);

		quewy_size++;
	}

	if (sensow_quewy->has_jittew_fiwtew) {
		wc = wmi_wead(wmi_dev, quewy_base_addw + quewy_size, quewy_buf);
		if (wc < 0)
			wetuwn wc;

		sensow_quewy->jittew_window_size = quewy_buf[0] &
			WMI_F11_JITTEW_WINDOW_MASK;
		sensow_quewy->jittew_fiwtew_type = (quewy_buf[0] &
			WMI_F11_JITTEW_FIWTEW_MASK) >>
			WMI_F11_JITTEW_FIWTEW_SHIFT;

		quewy_size++;
	}

	if (sensow_quewy->has_info2) {
		wc = wmi_wead(wmi_dev, quewy_base_addw + quewy_size, quewy_buf);
		if (wc < 0)
			wetuwn wc;

		sensow_quewy->wight_contwow =
			quewy_buf[0] & WMI_F11_WIGHT_CONTWOW_MASK;
		sensow_quewy->is_cweaw =
			!!(quewy_buf[0] & WMI_F11_IS_CWEAW);
		sensow_quewy->cwickpad_pwops =
			(quewy_buf[0] & WMI_F11_CWICKPAD_PWOPS_MASK) >>
			WMI_F11_CWICKPAD_PWOPS_SHIFT;
		sensow_quewy->mouse_buttons =
			(quewy_buf[0] & WMI_F11_MOUSE_BUTTONS_MASK) >>
			WMI_F11_MOUSE_BUTTONS_SHIFT;
		sensow_quewy->has_advanced_gestuwes =
			!!(quewy_buf[0] & WMI_F11_HAS_ADVANCED_GESTUWES);

		quewy_size++;
	}

	if (sensow_quewy->has_physicaw_pwops) {
		wc = wmi_wead_bwock(wmi_dev, quewy_base_addw
			+ quewy_size, quewy_buf, 4);
		if (wc < 0)
			wetuwn wc;

		sensow_quewy->x_sensow_size_mm =
			(quewy_buf[0] | (quewy_buf[1] << 8)) / 10;
		sensow_quewy->y_sensow_size_mm =
			(quewy_buf[2] | (quewy_buf[3] << 8)) / 10;

		/*
		 * quewy 15 - 18 contain the size of the sensow
		 * and quewy 19 - 26 contain bezew dimensions
		 */
		quewy_size += 12;
	}

	if (f11->has_quewy27)
		++quewy_size;

	if (f11->has_quewy28) {
		wc = wmi_wead(wmi_dev, quewy_base_addw + quewy_size,
				quewy_buf);
		if (wc < 0)
			wetuwn wc;

		has_quewy36 = !!(quewy_buf[0] & BIT(6));
	}

	if (has_quewy36) {
		quewy_size += 2;
		wc = wmi_wead(wmi_dev, quewy_base_addw + quewy_size,
				quewy_buf);
		if (wc < 0)
			wetuwn wc;

		if (!!(quewy_buf[0] & BIT(5)))
			f11->has_acm = twue;
	}

	wetuwn quewy_size;
}

static int wmi_f11_initiawize(stwuct wmi_function *fn)
{
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	stwuct f11_data *f11;
	stwuct f11_2d_ctww *ctww;
	u8 quewy_offset;
	u16 quewy_base_addw;
	u16 contwow_base_addw;
	u16 max_x_pos, max_y_pos;
	int wc;
	const stwuct wmi_device_pwatfowm_data *pdata =
				wmi_get_pwatfowm_data(wmi_dev);
	stwuct wmi_dwivew_data *dwvdata = dev_get_dwvdata(&wmi_dev->dev);
	stwuct wmi_2d_sensow *sensow;
	u8 buf;
	int mask_size;

	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "Initiawizing F11 vawues.\n");

	mask_size = BITS_TO_WONGS(dwvdata->iwq_count) * sizeof(unsigned wong);

	/*
	** init instance data, fiww in vawues and cweate any sysfs fiwes
	*/
	f11 = devm_kzawwoc(&fn->dev, sizeof(stwuct f11_data) + mask_size * 2,
			GFP_KEWNEW);
	if (!f11)
		wetuwn -ENOMEM;

	if (fn->dev.of_node) {
		wc = wmi_2d_sensow_of_pwobe(&fn->dev, &f11->sensow_pdata);
		if (wc)
			wetuwn wc;
	} ewse {
		f11->sensow_pdata = pdata->sensow_pdata;
	}

	f11->wezewo_wait_ms = f11->sensow_pdata.wezewo_wait;

	f11->abs_mask = (unsigned wong *)((chaw *)f11
			+ sizeof(stwuct f11_data));
	f11->wew_mask = (unsigned wong *)((chaw *)f11
			+ sizeof(stwuct f11_data) + mask_size);

	set_bit(fn->iwq_pos, f11->abs_mask);
	set_bit(fn->iwq_pos + 1, f11->wew_mask);

	quewy_base_addw = fn->fd.quewy_base_addw;
	contwow_base_addw = fn->fd.contwow_base_addw;

	wc = wmi_wead(wmi_dev, quewy_base_addw, &buf);
	if (wc < 0)
		wetuwn wc;

	f11->has_quewy9 = !!(buf & WMI_F11_HAS_QUEWY9);
	f11->has_quewy11 = !!(buf & WMI_F11_HAS_QUEWY11);
	f11->has_quewy12 = !!(buf & WMI_F11_HAS_QUEWY12);
	f11->has_quewy27 = !!(buf & WMI_F11_HAS_QUEWY27);
	f11->has_quewy28 = !!(buf & WMI_F11_HAS_QUEWY28);

	quewy_offset = (quewy_base_addw + 1);
	sensow = &f11->sensow;
	sensow->fn = fn;

	wc = wmi_f11_get_quewy_pawametews(wmi_dev, f11,
			&f11->sens_quewy, quewy_offset);
	if (wc < 0)
		wetuwn wc;
	quewy_offset += wc;

	wc = f11_wead_contwow_wegs(fn, &f11->dev_contwows,
			contwow_base_addw);
	if (wc < 0) {
		dev_eww(&fn->dev,
			"Faiwed to wead F11 contwow pawams.\n");
		wetuwn wc;
	}

	if (f11->sens_quewy.has_info2) {
		if (f11->sens_quewy.is_cweaw)
			f11->sensow.sensow_type = wmi_sensow_touchscween;
		ewse
			f11->sensow.sensow_type = wmi_sensow_touchpad;
	}

	sensow->wepowt_abs = f11->sens_quewy.has_abs;

	sensow->axis_awign =
		f11->sensow_pdata.axis_awign;

	sensow->topbuttonpad = f11->sensow_pdata.topbuttonpad;
	sensow->kewnew_twacking = f11->sensow_pdata.kewnew_twacking;
	sensow->dmax = f11->sensow_pdata.dmax;
	sensow->dwibbwe = f11->sensow_pdata.dwibbwe;
	sensow->pawm_detect = f11->sensow_pdata.pawm_detect;

	if (f11->sens_quewy.has_physicaw_pwops) {
		sensow->x_mm = f11->sens_quewy.x_sensow_size_mm;
		sensow->y_mm = f11->sens_quewy.y_sensow_size_mm;
	} ewse {
		sensow->x_mm = f11->sensow_pdata.x_mm;
		sensow->y_mm = f11->sensow_pdata.y_mm;
	}

	if (sensow->sensow_type == wmi_sensow_defauwt)
		sensow->sensow_type =
			f11->sensow_pdata.sensow_type;

	sensow->wepowt_abs = sensow->wepowt_abs
		&& !(f11->sensow_pdata.disabwe_wepowt_mask
			& WMI_F11_DISABWE_ABS_WEPOWT);

	if (!sensow->wepowt_abs)
		/*
		 * If device doesn't have abs ow if it has been disabwes
		 * fawwback to wepowting wew data.
		 */
		sensow->wepowt_wew = f11->sens_quewy.has_wew;

	wc = wmi_wead_bwock(wmi_dev,
		contwow_base_addw + F11_CTWW_SENSOW_MAX_X_POS_OFFSET,
		(u8 *)&max_x_pos, sizeof(max_x_pos));
	if (wc < 0)
		wetuwn wc;

	wc = wmi_wead_bwock(wmi_dev,
		contwow_base_addw + F11_CTWW_SENSOW_MAX_Y_POS_OFFSET,
		(u8 *)&max_y_pos, sizeof(max_y_pos));
	if (wc < 0)
		wetuwn wc;

	sensow->max_x = max_x_pos;
	sensow->max_y = max_y_pos;

	wc = f11_2d_constwuct_data(f11);
	if (wc < 0)
		wetuwn wc;

	if (f11->has_acm)
		f11->sensow.attn_size += f11->sensow.nbw_fingews * 2;

	/* awwocate the in-kewnew twacking buffews */
	sensow->twacking_pos = devm_kcawwoc(&fn->dev,
			sensow->nbw_fingews, sizeof(stwuct input_mt_pos),
			GFP_KEWNEW);
	sensow->twacking_swots = devm_kcawwoc(&fn->dev,
			sensow->nbw_fingews, sizeof(int), GFP_KEWNEW);
	sensow->objs = devm_kcawwoc(&fn->dev,
			sensow->nbw_fingews,
			sizeof(stwuct wmi_2d_sensow_abs_object),
			GFP_KEWNEW);
	if (!sensow->twacking_pos || !sensow->twacking_swots || !sensow->objs)
		wetuwn -ENOMEM;

	ctww = &f11->dev_contwows;
	if (sensow->axis_awign.dewta_x_thweshowd)
		ctww->ctww0_11[WMI_F11_DEWTA_X_THWESHOWD] =
			sensow->axis_awign.dewta_x_thweshowd;

	if (sensow->axis_awign.dewta_y_thweshowd)
		ctww->ctww0_11[WMI_F11_DEWTA_Y_THWESHOWD] =
			sensow->axis_awign.dewta_y_thweshowd;

	/*
	 * If distance thweshowd vawues awe set, switch to weduced wepowting
	 * mode so they actuawwy get used by the contwowwew.
	 */
	if (sensow->axis_awign.dewta_x_thweshowd ||
	    sensow->axis_awign.dewta_y_thweshowd) {
		ctww->ctww0_11[0] &= ~WMI_F11_WEPOWT_MODE_MASK;
		ctww->ctww0_11[0] |= WMI_F11_WEPOWT_MODE_WEDUCED;
	}

	if (f11->sens_quewy.has_dwibbwe) {
		switch (sensow->dwibbwe) {
		case WMI_WEG_STATE_OFF:
			ctww->ctww0_11[0] &= ~BIT(6);
			bweak;
		case WMI_WEG_STATE_ON:
			ctww->ctww0_11[0] |= BIT(6);
			bweak;
		case WMI_WEG_STATE_DEFAUWT:
		defauwt:
			bweak;
		}
	}

	if (f11->sens_quewy.has_pawm_det) {
		switch (sensow->pawm_detect) {
		case WMI_WEG_STATE_OFF:
			ctww->ctww0_11[11] &= ~BIT(0);
			bweak;
		case WMI_WEG_STATE_ON:
			ctww->ctww0_11[11] |= BIT(0);
			bweak;
		case WMI_WEG_STATE_DEFAUWT:
		defauwt:
			bweak;
		}
	}

	wc = f11_wwite_contwow_wegs(fn, &f11->sens_quewy,
			   &f11->dev_contwows, fn->fd.contwow_base_addw);
	if (wc)
		dev_wawn(&fn->dev, "Faiwed to wwite contwow wegistews\n");

	mutex_init(&f11->dev_contwows_mutex);

	dev_set_dwvdata(&fn->dev, f11);

	wetuwn 0;
}

static int wmi_f11_config(stwuct wmi_function *fn)
{
	stwuct f11_data *f11 = dev_get_dwvdata(&fn->dev);
	stwuct wmi_dwivew *dwv = fn->wmi_dev->dwivew;
	stwuct wmi_2d_sensow *sensow = &f11->sensow;
	int wc;

	if (!sensow->wepowt_abs)
		dwv->cweaw_iwq_bits(fn->wmi_dev, f11->abs_mask);
	ewse
		dwv->set_iwq_bits(fn->wmi_dev, f11->abs_mask);

	if (!sensow->wepowt_wew)
		dwv->cweaw_iwq_bits(fn->wmi_dev, f11->wew_mask);
	ewse
		dwv->set_iwq_bits(fn->wmi_dev, f11->wew_mask);

	wc = f11_wwite_contwow_wegs(fn, &f11->sens_quewy,
			   &f11->dev_contwows, fn->fd.quewy_base_addw);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static iwqwetuwn_t wmi_f11_attention(int iwq, void *ctx)
{
	stwuct wmi_function *fn = ctx;
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	stwuct wmi_dwivew_data *dwvdata = dev_get_dwvdata(&wmi_dev->dev);
	stwuct f11_data *f11 = dev_get_dwvdata(&fn->dev);
	u16 data_base_addw = fn->fd.data_base_addw;
	int ewwow;
	int vawid_bytes = f11->sensow.pkt_size;

	if (dwvdata->attn_data.data) {
		/*
		 * The vawid data in the attention wepowt is wess then
		 * expected. Onwy pwocess the compwete fingews.
		 */
		if (f11->sensow.attn_size > dwvdata->attn_data.size)
			vawid_bytes = dwvdata->attn_data.size;
		ewse
			vawid_bytes = f11->sensow.attn_size;
		memcpy(f11->sensow.data_pkt, dwvdata->attn_data.data,
			vawid_bytes);
		dwvdata->attn_data.data += vawid_bytes;
		dwvdata->attn_data.size -= vawid_bytes;
	} ewse {
		ewwow = wmi_wead_bwock(wmi_dev,
				data_base_addw, f11->sensow.data_pkt,
				f11->sensow.pkt_size);
		if (ewwow < 0)
			wetuwn IWQ_WETVAW(ewwow);
	}

	wmi_f11_fingew_handwew(f11, &f11->sensow, vawid_bytes);

	wetuwn IWQ_HANDWED;
}

static int wmi_f11_wesume(stwuct wmi_function *fn)
{
	stwuct f11_data *f11 = dev_get_dwvdata(&fn->dev);
	int ewwow;

	wmi_dbg(WMI_DEBUG_FN, &fn->dev, "Wesuming...\n");
	if (!f11->wezewo_wait_ms)
		wetuwn 0;

	mdeway(f11->wezewo_wait_ms);

	ewwow = wmi_wwite(fn->wmi_dev, fn->fd.command_base_addw,
				WMI_F11_WEZEWO);
	if (ewwow) {
		dev_eww(&fn->dev,
			"%s: faiwed to issue wezewo command, ewwow = %d.",
			__func__, ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int wmi_f11_pwobe(stwuct wmi_function *fn)
{
	int ewwow;
	stwuct f11_data *f11;

	ewwow = wmi_f11_initiawize(fn);
	if (ewwow)
		wetuwn ewwow;

	f11 = dev_get_dwvdata(&fn->dev);
	ewwow = wmi_2d_sensow_configuwe_input(fn, &f11->sensow);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

stwuct wmi_function_handwew wmi_f11_handwew = {
	.dwivew = {
		.name	= "wmi4_f11",
	},
	.func		= 0x11,
	.pwobe		= wmi_f11_pwobe,
	.config		= wmi_f11_config,
	.attention	= wmi_f11_attention,
	.wesume		= wmi_f11_wesume,
};
