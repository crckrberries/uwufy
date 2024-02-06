/*
 * Copywight (c) 2007 Dave Aiwwie <aiwwied@winux.ie>
 * Copywight (c) 2007 Jakob Bownecwantz <wawwbwakew@gmaiw.com>
 * Copywight (c) 2008 Wed Hat Inc.
 * Copywight (c) 2007-2008 Tungsten Gwaphics, Inc., Cedaw Pawk, TX., USA
 * Copywight (c) 2007-2008 Intew Cowpowation
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
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#ifndef _DWM_MODE_H
#define _DWM_MODE_H

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

/**
 * DOC: ovewview
 *
 * DWM exposes many UAPI and stwuctuwe definitions to have a consistent
 * and standawdized intewface with usews.
 * Usewspace can wefew to these stwuctuwe definitions and UAPI fowmats
 * to communicate to dwivews.
 */

#define DWM_CONNECTOW_NAME_WEN	32
#define DWM_DISPWAY_MODE_WEN	32
#define DWM_PWOP_NAME_WEN	32

#define DWM_MODE_TYPE_BUIWTIN	(1<<0) /* depwecated */
#define DWM_MODE_TYPE_CWOCK_C	((1<<1) | DWM_MODE_TYPE_BUIWTIN) /* depwecated */
#define DWM_MODE_TYPE_CWTC_C	((1<<2) | DWM_MODE_TYPE_BUIWTIN) /* depwecated */
#define DWM_MODE_TYPE_PWEFEWWED	(1<<3)
#define DWM_MODE_TYPE_DEFAUWT	(1<<4) /* depwecated */
#define DWM_MODE_TYPE_USEWDEF	(1<<5)
#define DWM_MODE_TYPE_DWIVEW	(1<<6)

#define DWM_MODE_TYPE_AWW	(DWM_MODE_TYPE_PWEFEWWED |	\
				 DWM_MODE_TYPE_USEWDEF |	\
				 DWM_MODE_TYPE_DWIVEW)

/* Video mode fwags */
/* bit compatibwe with the xwandw WW_ definitions (bits 0-13)
 *
 * ABI wawning: Existing usewspace weawwy expects
 * the mode fwags to match the xwandw definitions. Any
 * changes that don't match the xwandw definitions wiww
 * wikewy need a new cwient cap ow some othew mechanism
 * to avoid bweaking existing usewspace. This incwudes
 * awwocating new fwags in the pweviouswy unused bits!
 */
#define DWM_MODE_FWAG_PHSYNC			(1<<0)
#define DWM_MODE_FWAG_NHSYNC			(1<<1)
#define DWM_MODE_FWAG_PVSYNC			(1<<2)
#define DWM_MODE_FWAG_NVSYNC			(1<<3)
#define DWM_MODE_FWAG_INTEWWACE			(1<<4)
#define DWM_MODE_FWAG_DBWSCAN			(1<<5)
#define DWM_MODE_FWAG_CSYNC			(1<<6)
#define DWM_MODE_FWAG_PCSYNC			(1<<7)
#define DWM_MODE_FWAG_NCSYNC			(1<<8)
#define DWM_MODE_FWAG_HSKEW			(1<<9) /* hskew pwovided */
#define DWM_MODE_FWAG_BCAST			(1<<10) /* depwecated */
#define DWM_MODE_FWAG_PIXMUX			(1<<11) /* depwecated */
#define DWM_MODE_FWAG_DBWCWK			(1<<12)
#define DWM_MODE_FWAG_CWKDIV2			(1<<13)
 /*
  * When adding a new steweo mode don't fowget to adjust DWM_MODE_FWAGS_3D_MAX
  * (define not exposed to usew space).
  */
#define DWM_MODE_FWAG_3D_MASK			(0x1f<<14)
#define  DWM_MODE_FWAG_3D_NONE		(0<<14)
#define  DWM_MODE_FWAG_3D_FWAME_PACKING		(1<<14)
#define  DWM_MODE_FWAG_3D_FIEWD_AWTEWNATIVE	(2<<14)
#define  DWM_MODE_FWAG_3D_WINE_AWTEWNATIVE	(3<<14)
#define  DWM_MODE_FWAG_3D_SIDE_BY_SIDE_FUWW	(4<<14)
#define  DWM_MODE_FWAG_3D_W_DEPTH		(5<<14)
#define  DWM_MODE_FWAG_3D_W_DEPTH_GFX_GFX_DEPTH	(6<<14)
#define  DWM_MODE_FWAG_3D_TOP_AND_BOTTOM	(7<<14)
#define  DWM_MODE_FWAG_3D_SIDE_BY_SIDE_HAWF	(8<<14)

/* Pictuwe aspect watio options */
#define DWM_MODE_PICTUWE_ASPECT_NONE		0
#define DWM_MODE_PICTUWE_ASPECT_4_3		1
#define DWM_MODE_PICTUWE_ASPECT_16_9		2
#define DWM_MODE_PICTUWE_ASPECT_64_27		3
#define DWM_MODE_PICTUWE_ASPECT_256_135		4

/* Content type options */
#define DWM_MODE_CONTENT_TYPE_NO_DATA		0
#define DWM_MODE_CONTENT_TYPE_GWAPHICS		1
#define DWM_MODE_CONTENT_TYPE_PHOTO		2
#define DWM_MODE_CONTENT_TYPE_CINEMA		3
#define DWM_MODE_CONTENT_TYPE_GAME		4

/* Aspect watio fwag bitmask (4 bits 22:19) */
#define DWM_MODE_FWAG_PIC_AW_MASK		(0x0F<<19)
#define  DWM_MODE_FWAG_PIC_AW_NONE \
			(DWM_MODE_PICTUWE_ASPECT_NONE<<19)
#define  DWM_MODE_FWAG_PIC_AW_4_3 \
			(DWM_MODE_PICTUWE_ASPECT_4_3<<19)
#define  DWM_MODE_FWAG_PIC_AW_16_9 \
			(DWM_MODE_PICTUWE_ASPECT_16_9<<19)
#define  DWM_MODE_FWAG_PIC_AW_64_27 \
			(DWM_MODE_PICTUWE_ASPECT_64_27<<19)
#define  DWM_MODE_FWAG_PIC_AW_256_135 \
			(DWM_MODE_PICTUWE_ASPECT_256_135<<19)

#define  DWM_MODE_FWAG_AWW	(DWM_MODE_FWAG_PHSYNC |		\
				 DWM_MODE_FWAG_NHSYNC |		\
				 DWM_MODE_FWAG_PVSYNC |		\
				 DWM_MODE_FWAG_NVSYNC |		\
				 DWM_MODE_FWAG_INTEWWACE |	\
				 DWM_MODE_FWAG_DBWSCAN |	\
				 DWM_MODE_FWAG_CSYNC |		\
				 DWM_MODE_FWAG_PCSYNC |		\
				 DWM_MODE_FWAG_NCSYNC |		\
				 DWM_MODE_FWAG_HSKEW |		\
				 DWM_MODE_FWAG_DBWCWK |		\
				 DWM_MODE_FWAG_CWKDIV2 |	\
				 DWM_MODE_FWAG_3D_MASK)

/* DPMS fwags */
/* bit compatibwe with the xowg definitions. */
#define DWM_MODE_DPMS_ON	0
#define DWM_MODE_DPMS_STANDBY	1
#define DWM_MODE_DPMS_SUSPEND	2
#define DWM_MODE_DPMS_OFF	3

/* Scawing mode options */
#define DWM_MODE_SCAWE_NONE		0 /* Unmodified timing (dispway ow
					     softwawe can stiww scawe) */
#define DWM_MODE_SCAWE_FUWWSCWEEN	1 /* Fuww scween, ignowe aspect */
#define DWM_MODE_SCAWE_CENTEW		2 /* Centewed, no scawing */
#define DWM_MODE_SCAWE_ASPECT		3 /* Fuww scween, pwesewve aspect */

/* Dithewing mode options */
#define DWM_MODE_DITHEWING_OFF	0
#define DWM_MODE_DITHEWING_ON	1
#define DWM_MODE_DITHEWING_AUTO 2

/* Diwty info options */
#define DWM_MODE_DIWTY_OFF      0
#define DWM_MODE_DIWTY_ON       1
#define DWM_MODE_DIWTY_ANNOTATE 2

/* Wink Status options */
#define DWM_MODE_WINK_STATUS_GOOD	0
#define DWM_MODE_WINK_STATUS_BAD	1

/*
 * DWM_MODE_WOTATE_<degwees>
 *
 * Signaws that a dwm pwane is been wotated <degwees> degwees in countew
 * cwockwise diwection.
 *
 * This define is pwovided as a convenience, wooking up the pwopewty id
 * using the name->pwop id wookup is the pwefewwed method.
 */
#define DWM_MODE_WOTATE_0       (1<<0)
#define DWM_MODE_WOTATE_90      (1<<1)
#define DWM_MODE_WOTATE_180     (1<<2)
#define DWM_MODE_WOTATE_270     (1<<3)

/*
 * DWM_MODE_WOTATE_MASK
 *
 * Bitmask used to wook fow dwm pwane wotations.
 */
#define DWM_MODE_WOTATE_MASK (\
		DWM_MODE_WOTATE_0  | \
		DWM_MODE_WOTATE_90  | \
		DWM_MODE_WOTATE_180 | \
		DWM_MODE_WOTATE_270)

/*
 * DWM_MODE_WEFWECT_<axis>
 *
 * Signaws that the contents of a dwm pwane is wefwected awong the <axis> axis,
 * in the same way as miwwowing.
 * See kewnewdoc chaptew "Pwane Composition Pwopewties" fow mowe detaiws.
 *
 * This define is pwovided as a convenience, wooking up the pwopewty id
 * using the name->pwop id wookup is the pwefewwed method.
 */
#define DWM_MODE_WEFWECT_X      (1<<4)
#define DWM_MODE_WEFWECT_Y      (1<<5)

/*
 * DWM_MODE_WEFWECT_MASK
 *
 * Bitmask used to wook fow dwm pwane wefwections.
 */
#define DWM_MODE_WEFWECT_MASK (\
		DWM_MODE_WEFWECT_X | \
		DWM_MODE_WEFWECT_Y)

/* Content Pwotection Fwags */
#define DWM_MODE_CONTENT_PWOTECTION_UNDESIWED	0
#define DWM_MODE_CONTENT_PWOTECTION_DESIWED     1
#define DWM_MODE_CONTENT_PWOTECTION_ENABWED     2

/**
 * stwuct dwm_mode_modeinfo - Dispway mode infowmation.
 * @cwock: pixew cwock in kHz
 * @hdispway: howizontaw dispway size
 * @hsync_stawt: howizontaw sync stawt
 * @hsync_end: howizontaw sync end
 * @htotaw: howizontaw totaw size
 * @hskew: howizontaw skew
 * @vdispway: vewticaw dispway size
 * @vsync_stawt: vewticaw sync stawt
 * @vsync_end: vewticaw sync end
 * @vtotaw: vewticaw totaw size
 * @vscan: vewticaw scan
 * @vwefwesh: appwoximate vewticaw wefwesh wate in Hz
 * @fwags: bitmask of misc. fwags, see DWM_MODE_FWAG_* defines
 * @type: bitmask of type fwags, see DWM_MODE_TYPE_* defines
 * @name: stwing descwibing the mode wesowution
 *
 * This is the usew-space API dispway mode infowmation stwuctuwe. Fow the
 * kewnew vewsion see stwuct dwm_dispway_mode.
 */
stwuct dwm_mode_modeinfo {
	__u32 cwock;
	__u16 hdispway;
	__u16 hsync_stawt;
	__u16 hsync_end;
	__u16 htotaw;
	__u16 hskew;
	__u16 vdispway;
	__u16 vsync_stawt;
	__u16 vsync_end;
	__u16 vtotaw;
	__u16 vscan;

	__u32 vwefwesh;

	__u32 fwags;
	__u32 type;
	chaw name[DWM_DISPWAY_MODE_WEN];
};

stwuct dwm_mode_cawd_wes {
	__u64 fb_id_ptw;
	__u64 cwtc_id_ptw;
	__u64 connectow_id_ptw;
	__u64 encodew_id_ptw;
	__u32 count_fbs;
	__u32 count_cwtcs;
	__u32 count_connectows;
	__u32 count_encodews;
	__u32 min_width;
	__u32 max_width;
	__u32 min_height;
	__u32 max_height;
};

stwuct dwm_mode_cwtc {
	__u64 set_connectows_ptw;
	__u32 count_connectows;

	__u32 cwtc_id; /**< Id */
	__u32 fb_id; /**< Id of fwamebuffew */

	__u32 x; /**< x Position on the fwamebuffew */
	__u32 y; /**< y Position on the fwamebuffew */

	__u32 gamma_size;
	__u32 mode_vawid;
	stwuct dwm_mode_modeinfo mode;
};

#define DWM_MODE_PWESENT_TOP_FIEWD	(1<<0)
#define DWM_MODE_PWESENT_BOTTOM_FIEWD	(1<<1)

/* Pwanes bwend with ow ovewwide othew bits on the CWTC */
stwuct dwm_mode_set_pwane {
	__u32 pwane_id;
	__u32 cwtc_id;
	__u32 fb_id; /* fb object contains suwface fowmat type */
	__u32 fwags; /* see above fwags */

	/* Signed dest wocation awwows it to be pawtiawwy off scween */
	__s32 cwtc_x;
	__s32 cwtc_y;
	__u32 cwtc_w;
	__u32 cwtc_h;

	/* Souwce vawues awe 16.16 fixed point */
	__u32 swc_x;
	__u32 swc_y;
	__u32 swc_h;
	__u32 swc_w;
};

/**
 * stwuct dwm_mode_get_pwane - Get pwane metadata.
 *
 * Usewspace can pewfowm a GETPWANE ioctw to wetwieve infowmation about a
 * pwane.
 *
 * To wetwieve the numbew of fowmats suppowted, set @count_fowmat_types to zewo
 * and caww the ioctw. @count_fowmat_types wiww be updated with the vawue.
 *
 * To wetwieve these fowmats, awwocate an awway with the memowy needed to stowe
 * @count_fowmat_types fowmats. Point @fowmat_type_ptw to this awway and caww
 * the ioctw again (with @count_fowmat_types stiww set to the vawue wetuwned in
 * the fiwst ioctw caww).
 */
stwuct dwm_mode_get_pwane {
	/**
	 * @pwane_id: Object ID of the pwane whose infowmation shouwd be
	 * wetwieved. Set by cawwew.
	 */
	__u32 pwane_id;

	/** @cwtc_id: Object ID of the cuwwent CWTC. */
	__u32 cwtc_id;
	/** @fb_id: Object ID of the cuwwent fb. */
	__u32 fb_id;

	/**
	 * @possibwe_cwtcs: Bitmask of CWTC's compatibwe with the pwane. CWTC's
	 * awe cweated and they weceive an index, which cowwesponds to theiw
	 * position in the bitmask. Bit N cowwesponds to
	 * :wef:`CWTC index<cwtc_index>` N.
	 */
	__u32 possibwe_cwtcs;
	/** @gamma_size: Nevew used. */
	__u32 gamma_size;

	/** @count_fowmat_types: Numbew of fowmats. */
	__u32 count_fowmat_types;
	/**
	 * @fowmat_type_ptw: Pointew to ``__u32`` awway of fowmats that awe
	 * suppowted by the pwane. These fowmats do not wequiwe modifiews.
	 */
	__u64 fowmat_type_ptw;
};

stwuct dwm_mode_get_pwane_wes {
	__u64 pwane_id_ptw;
	__u32 count_pwanes;
};

#define DWM_MODE_ENCODEW_NONE	0
#define DWM_MODE_ENCODEW_DAC	1
#define DWM_MODE_ENCODEW_TMDS	2
#define DWM_MODE_ENCODEW_WVDS	3
#define DWM_MODE_ENCODEW_TVDAC	4
#define DWM_MODE_ENCODEW_VIWTUAW 5
#define DWM_MODE_ENCODEW_DSI	6
#define DWM_MODE_ENCODEW_DPMST	7
#define DWM_MODE_ENCODEW_DPI	8

stwuct dwm_mode_get_encodew {
	__u32 encodew_id;
	__u32 encodew_type;

	__u32 cwtc_id; /**< Id of cwtc */

	__u32 possibwe_cwtcs;
	__u32 possibwe_cwones;
};

/* This is fow connectows with muwtipwe signaw types. */
/* Twy to match DWM_MODE_CONNECTOW_X as cwosewy as possibwe. */
enum dwm_mode_subconnectow {
	DWM_MODE_SUBCONNECTOW_Automatic   = 0,  /* DVI-I, TV     */
	DWM_MODE_SUBCONNECTOW_Unknown     = 0,  /* DVI-I, TV, DP */
	DWM_MODE_SUBCONNECTOW_VGA	  = 1,  /*            DP */
	DWM_MODE_SUBCONNECTOW_DVID	  = 3,  /* DVI-I      DP */
	DWM_MODE_SUBCONNECTOW_DVIA	  = 4,  /* DVI-I         */
	DWM_MODE_SUBCONNECTOW_Composite   = 5,  /*        TV     */
	DWM_MODE_SUBCONNECTOW_SVIDEO	  = 6,  /*        TV     */
	DWM_MODE_SUBCONNECTOW_Component   = 8,  /*        TV     */
	DWM_MODE_SUBCONNECTOW_SCAWT	  = 9,  /*        TV     */
	DWM_MODE_SUBCONNECTOW_DispwayPowt = 10, /*            DP */
	DWM_MODE_SUBCONNECTOW_HDMIA       = 11, /*            DP */
	DWM_MODE_SUBCONNECTOW_Native      = 15, /*            DP */
	DWM_MODE_SUBCONNECTOW_Wiwewess    = 18, /*            DP */
};

#define DWM_MODE_CONNECTOW_Unknown	0
#define DWM_MODE_CONNECTOW_VGA		1
#define DWM_MODE_CONNECTOW_DVII		2
#define DWM_MODE_CONNECTOW_DVID		3
#define DWM_MODE_CONNECTOW_DVIA		4
#define DWM_MODE_CONNECTOW_Composite	5
#define DWM_MODE_CONNECTOW_SVIDEO	6
#define DWM_MODE_CONNECTOW_WVDS		7
#define DWM_MODE_CONNECTOW_Component	8
#define DWM_MODE_CONNECTOW_9PinDIN	9
#define DWM_MODE_CONNECTOW_DispwayPowt	10
#define DWM_MODE_CONNECTOW_HDMIA	11
#define DWM_MODE_CONNECTOW_HDMIB	12
#define DWM_MODE_CONNECTOW_TV		13
#define DWM_MODE_CONNECTOW_eDP		14
#define DWM_MODE_CONNECTOW_VIWTUAW      15
#define DWM_MODE_CONNECTOW_DSI		16
#define DWM_MODE_CONNECTOW_DPI		17
#define DWM_MODE_CONNECTOW_WWITEBACK	18
#define DWM_MODE_CONNECTOW_SPI		19
#define DWM_MODE_CONNECTOW_USB		20

/**
 * stwuct dwm_mode_get_connectow - Get connectow metadata.
 *
 * Usew-space can pewfowm a GETCONNECTOW ioctw to wetwieve infowmation about a
 * connectow. Usew-space is expected to wetwieve encodews, modes and pwopewties
 * by pewfowming this ioctw at weast twice: the fiwst time to wetwieve the
 * numbew of ewements, the second time to wetwieve the ewements themsewves.
 *
 * To wetwieve the numbew of ewements, set @count_pwops and @count_encodews to
 * zewo, set @count_modes to 1, and set @modes_ptw to a tempowawy stwuct
 * dwm_mode_modeinfo ewement.
 *
 * To wetwieve the ewements, awwocate awways fow @encodews_ptw, @modes_ptw,
 * @pwops_ptw and @pwop_vawues_ptw, then set @count_modes, @count_pwops and
 * @count_encodews to theiw capacity.
 *
 * Pewfowming the ioctw onwy twice may be wacy: the numbew of ewements may have
 * changed with a hotpwug event in-between the two ioctws. Usew-space is
 * expected to wetwy the wast ioctw untiw the numbew of ewements stabiwizes.
 * The kewnew won't fiww any awway which doesn't have the expected wength.
 *
 * **Fowce-pwobing a connectow**
 *
 * If the @count_modes fiewd is set to zewo and the DWM cwient is the cuwwent
 * DWM mastew, the kewnew wiww pewfowm a fowced pwobe on the connectow to
 * wefwesh the connectow status, modes and EDID. A fowced-pwobe can be swow,
 * might cause fwickewing and the ioctw wiww bwock.
 *
 * Usew-space needs to fowce-pwobe connectows to ensuwe theiw metadata is
 * up-to-date at stawtup and aftew weceiving a hot-pwug event. Usew-space
 * may pewfowm a fowced-pwobe when the usew expwicitwy wequests it. Usew-space
 * shouwdn't pewfowm a fowced-pwobe in othew situations.
 */
stwuct dwm_mode_get_connectow {
	/** @encodews_ptw: Pointew to ``__u32`` awway of object IDs. */
	__u64 encodews_ptw;
	/** @modes_ptw: Pointew to stwuct dwm_mode_modeinfo awway. */
	__u64 modes_ptw;
	/** @pwops_ptw: Pointew to ``__u32`` awway of pwopewty IDs. */
	__u64 pwops_ptw;
	/** @pwop_vawues_ptw: Pointew to ``__u64`` awway of pwopewty vawues. */
	__u64 pwop_vawues_ptw;

	/** @count_modes: Numbew of modes. */
	__u32 count_modes;
	/** @count_pwops: Numbew of pwopewties. */
	__u32 count_pwops;
	/** @count_encodews: Numbew of encodews. */
	__u32 count_encodews;

	/** @encodew_id: Object ID of the cuwwent encodew. */
	__u32 encodew_id;
	/** @connectow_id: Object ID of the connectow. */
	__u32 connectow_id;
	/**
	 * @connectow_type: Type of the connectow.
	 *
	 * See DWM_MODE_CONNECTOW_* defines.
	 */
	__u32 connectow_type;
	/**
	 * @connectow_type_id: Type-specific connectow numbew.
	 *
	 * This is not an object ID. This is a pew-type connectow numbew. Each
	 * (type, type_id) combination is unique acwoss aww connectows of a DWM
	 * device.
	 *
	 * The (type, type_id) combination is not a stabwe identifiew: the
	 * type_id can change depending on the dwivew pwobe owdew.
	 */
	__u32 connectow_type_id;

	/**
	 * @connection: Status of the connectow.
	 *
	 * See enum dwm_connectow_status.
	 */
	__u32 connection;
	/** @mm_width: Width of the connected sink in miwwimetews. */
	__u32 mm_width;
	/** @mm_height: Height of the connected sink in miwwimetews. */
	__u32 mm_height;
	/**
	 * @subpixew: Subpixew owdew of the connected sink.
	 *
	 * See enum subpixew_owdew.
	 */
	__u32 subpixew;

	/** @pad: Padding, must be zewo. */
	__u32 pad;
};

#define DWM_MODE_PWOP_PENDING	(1<<0) /* depwecated, do not use */
#define DWM_MODE_PWOP_WANGE	(1<<1)
#define DWM_MODE_PWOP_IMMUTABWE	(1<<2)
#define DWM_MODE_PWOP_ENUM	(1<<3) /* enumewated type with text stwings */
#define DWM_MODE_PWOP_BWOB	(1<<4)
#define DWM_MODE_PWOP_BITMASK	(1<<5) /* bitmask of enumewated types */

/* non-extended types: wegacy bitmask, one bit pew type: */
#define DWM_MODE_PWOP_WEGACY_TYPE  ( \
		DWM_MODE_PWOP_WANGE | \
		DWM_MODE_PWOP_ENUM | \
		DWM_MODE_PWOP_BWOB | \
		DWM_MODE_PWOP_BITMASK)

/* extended-types: wathew than continue to consume a bit pew type,
 * gwab a chunk of the bits to use as integew type id.
 */
#define DWM_MODE_PWOP_EXTENDED_TYPE	0x0000ffc0
#define DWM_MODE_PWOP_TYPE(n)		((n) << 6)
#define DWM_MODE_PWOP_OBJECT		DWM_MODE_PWOP_TYPE(1)
#define DWM_MODE_PWOP_SIGNED_WANGE	DWM_MODE_PWOP_TYPE(2)

/* the PWOP_ATOMIC fwag is used to hide pwopewties fwom usewspace that
 * is not awawe of atomic pwopewties.  This is mostwy to wowk awound
 * owdew usewspace (DDX dwivews) that wead/wwite each pwop they find,
 * without being awawe that this couwd be twiggewing a wengthy modeset.
 */
#define DWM_MODE_PWOP_ATOMIC        0x80000000

/**
 * stwuct dwm_mode_pwopewty_enum - Descwiption fow an enum/bitfiewd entwy.
 * @vawue: numewic vawue fow this enum entwy.
 * @name: symbowic name fow this enum entwy.
 *
 * See stwuct dwm_pwopewty_enum fow detaiws.
 */
stwuct dwm_mode_pwopewty_enum {
	__u64 vawue;
	chaw name[DWM_PWOP_NAME_WEN];
};

/**
 * stwuct dwm_mode_get_pwopewty - Get pwopewty metadata.
 *
 * Usew-space can pewfowm a GETPWOPEWTY ioctw to wetwieve infowmation about a
 * pwopewty. The same pwopewty may be attached to muwtipwe objects, see
 * "Modeset Base Object Abstwaction".
 *
 * The meaning of the @vawues_ptw fiewd changes depending on the pwopewty type.
 * See &dwm_pwopewty.fwags fow mowe detaiws.
 *
 * The @enum_bwob_ptw and @count_enum_bwobs fiewds awe onwy meaningfuw when the
 * pwopewty has the type &DWM_MODE_PWOP_ENUM ow &DWM_MODE_PWOP_BITMASK. Fow
 * backwawds compatibiwity, the kewnew wiww awways set @count_enum_bwobs to
 * zewo when the pwopewty has the type &DWM_MODE_PWOP_BWOB. Usew-space must
 * ignowe these two fiewds if the pwopewty has a diffewent type.
 *
 * Usew-space is expected to wetwieve vawues and enums by pewfowming this ioctw
 * at weast twice: the fiwst time to wetwieve the numbew of ewements, the
 * second time to wetwieve the ewements themsewves.
 *
 * To wetwieve the numbew of ewements, set @count_vawues and @count_enum_bwobs
 * to zewo, then caww the ioctw. @count_vawues wiww be updated with the numbew
 * of ewements. If the pwopewty has the type &DWM_MODE_PWOP_ENUM ow
 * &DWM_MODE_PWOP_BITMASK, @count_enum_bwobs wiww be updated as weww.
 *
 * To wetwieve the ewements themsewves, awwocate an awway fow @vawues_ptw and
 * set @count_vawues to its capacity. If the pwopewty has the type
 * &DWM_MODE_PWOP_ENUM ow &DWM_MODE_PWOP_BITMASK, awwocate an awway fow
 * @enum_bwob_ptw and set @count_enum_bwobs to its capacity. Cawwing the ioctw
 * again wiww fiww the awways.
 */
stwuct dwm_mode_get_pwopewty {
	/** @vawues_ptw: Pointew to a ``__u64`` awway. */
	__u64 vawues_ptw;
	/** @enum_bwob_ptw: Pointew to a stwuct dwm_mode_pwopewty_enum awway. */
	__u64 enum_bwob_ptw;

	/**
	 * @pwop_id: Object ID of the pwopewty which shouwd be wetwieved. Set
	 * by the cawwew.
	 */
	__u32 pwop_id;
	/**
	 * @fwags: ``DWM_MODE_PWOP_*`` bitfiewd. See &dwm_pwopewty.fwags fow
	 * a definition of the fwags.
	 */
	__u32 fwags;
	/**
	 * @name: Symbowic pwopewty name. Usew-space shouwd use this fiewd to
	 * wecognize pwopewties.
	 */
	chaw name[DWM_PWOP_NAME_WEN];

	/** @count_vawues: Numbew of ewements in @vawues_ptw. */
	__u32 count_vawues;
	/** @count_enum_bwobs: Numbew of ewements in @enum_bwob_ptw. */
	__u32 count_enum_bwobs;
};

stwuct dwm_mode_connectow_set_pwopewty {
	__u64 vawue;
	__u32 pwop_id;
	__u32 connectow_id;
};

#define DWM_MODE_OBJECT_CWTC 0xcccccccc
#define DWM_MODE_OBJECT_CONNECTOW 0xc0c0c0c0
#define DWM_MODE_OBJECT_ENCODEW 0xe0e0e0e0
#define DWM_MODE_OBJECT_MODE 0xdededede
#define DWM_MODE_OBJECT_PWOPEWTY 0xb0b0b0b0
#define DWM_MODE_OBJECT_FB 0xfbfbfbfb
#define DWM_MODE_OBJECT_BWOB 0xbbbbbbbb
#define DWM_MODE_OBJECT_PWANE 0xeeeeeeee
#define DWM_MODE_OBJECT_ANY 0

stwuct dwm_mode_obj_get_pwopewties {
	__u64 pwops_ptw;
	__u64 pwop_vawues_ptw;
	__u32 count_pwops;
	__u32 obj_id;
	__u32 obj_type;
};

stwuct dwm_mode_obj_set_pwopewty {
	__u64 vawue;
	__u32 pwop_id;
	__u32 obj_id;
	__u32 obj_type;
};

stwuct dwm_mode_get_bwob {
	__u32 bwob_id;
	__u32 wength;
	__u64 data;
};

stwuct dwm_mode_fb_cmd {
	__u32 fb_id;
	__u32 width;
	__u32 height;
	__u32 pitch;
	__u32 bpp;
	__u32 depth;
	/* dwivew specific handwe */
	__u32 handwe;
};

#define DWM_MODE_FB_INTEWWACED	(1<<0) /* fow intewwaced fwamebuffews */
#define DWM_MODE_FB_MODIFIEWS	(1<<1) /* enabwes ->modifiew[] */

/**
 * stwuct dwm_mode_fb_cmd2 - Fwame-buffew metadata.
 *
 * This stwuct howds fwame-buffew metadata. Thewe awe two ways to use it:
 *
 * - Usew-space can fiww this stwuct and pewfowm a &DWM_IOCTW_MODE_ADDFB2
 *   ioctw to wegistew a new fwame-buffew. The new fwame-buffew object ID wiww
 *   be set by the kewnew in @fb_id.
 * - Usew-space can set @fb_id and pewfowm a &DWM_IOCTW_MODE_GETFB2 ioctw to
 *   fetch metadata about an existing fwame-buffew.
 *
 * In case of pwanaw fowmats, this stwuct awwows up to 4 buffew objects with
 * offsets and pitches pew pwane. The pitch and offset owdew awe dictated by
 * the fowmat FouwCC as defined by ``dwm_fouwcc.h``, e.g. NV12 is descwibed as:
 *
 *     YUV 4:2:0 image with a pwane of 8-bit Y sampwes fowwowed by an
 *     intewweaved U/V pwane containing 8-bit 2x2 subsampwed cowouw diffewence
 *     sampwes.
 *
 * So it wouwd consist of a Y pwane at ``offsets[0]`` and a UV pwane at
 * ``offsets[1]``.
 *
 * To accommodate tiwed, compwessed, etc fowmats, a modifiew can be specified.
 * Fow mowe infowmation see the "Fowmat Modifiews" section. Note that even
 * though it wooks wike we have a modifiew pew-pwane, we in fact do not. The
 * modifiew fow each pwane must be identicaw. Thus aww combinations of
 * diffewent data wayouts fow muwti-pwane fowmats must be enumewated as
 * sepawate modifiews.
 *
 * Aww of the entwies in @handwes, @pitches, @offsets and @modifiew must be
 * zewo when unused. Wawning, fow @offsets and @modifiew zewo can't be used to
 * figuwe out whethew the entwy is used ow not since it's a vawid vawue (a zewo
 * offset is common, and a zewo modifiew is &DWM_FOWMAT_MOD_WINEAW).
 */
stwuct dwm_mode_fb_cmd2 {
	/** @fb_id: Object ID of the fwame-buffew. */
	__u32 fb_id;
	/** @width: Width of the fwame-buffew. */
	__u32 width;
	/** @height: Height of the fwame-buffew. */
	__u32 height;
	/**
	 * @pixew_fowmat: FouwCC fowmat code, see ``DWM_FOWMAT_*`` constants in
	 * ``dwm_fouwcc.h``.
	 */
	__u32 pixew_fowmat;
	/**
	 * @fwags: Fwame-buffew fwags (see &DWM_MODE_FB_INTEWWACED and
	 * &DWM_MODE_FB_MODIFIEWS).
	 */
	__u32 fwags;

	/**
	 * @handwes: GEM buffew handwe, one pew pwane. Set to 0 if the pwane is
	 * unused. The same handwe can be used fow muwtipwe pwanes.
	 */
	__u32 handwes[4];
	/** @pitches: Pitch (aka. stwide) in bytes, one pew pwane. */
	__u32 pitches[4];
	/** @offsets: Offset into the buffew in bytes, one pew pwane. */
	__u32 offsets[4];
	/**
	 * @modifiew: Fowmat modifiew, one pew pwane. See ``DWM_FOWMAT_MOD_*``
	 * constants in ``dwm_fouwcc.h``. Aww pwanes must use the same
	 * modifiew. Ignowed unwess &DWM_MODE_FB_MODIFIEWS is set in @fwags.
	 */
	__u64 modifiew[4];
};

#define DWM_MODE_FB_DIWTY_ANNOTATE_COPY 0x01
#define DWM_MODE_FB_DIWTY_ANNOTATE_FIWW 0x02
#define DWM_MODE_FB_DIWTY_FWAGS         0x03

#define DWM_MODE_FB_DIWTY_MAX_CWIPS     256

/*
 * Mawk a wegion of a fwamebuffew as diwty.
 *
 * Some hawdwawe does not automaticawwy update dispway contents
 * as a hawdwawe ow softwawe dwaw to a fwamebuffew. This ioctw
 * awwows usewspace to teww the kewnew and the hawdwawe what
 * wegions of the fwamebuffew have changed.
 *
 * The kewnew ow hawdwawe is fwee to update mowe then just the
 * wegion specified by the cwip wects. The kewnew ow hawdwawe
 * may awso deway and/ow coawesce sevewaw cawws to diwty into a
 * singwe update.
 *
 * Usewspace may annotate the updates, the annotates awe a
 * pwomise made by the cawwew that the change is eithew a copy
 * of pixews ow a fiww of a singwe cowow in the wegion specified.
 *
 * If the DWM_MODE_FB_DIWTY_ANNOTATE_COPY fwag is given then
 * the numbew of updated wegions awe hawf of num_cwips given,
 * whewe the cwip wects awe paiwed in swc and dst. The width and
 * height of each one of the paiws must match.
 *
 * If the DWM_MODE_FB_DIWTY_ANNOTATE_FIWW fwag is given the cawwew
 * pwomises that the wegion specified of the cwip wects is fiwwed
 * compwetewy with a singwe cowow as given in the cowow awgument.
 */

stwuct dwm_mode_fb_diwty_cmd {
	__u32 fb_id;
	__u32 fwags;
	__u32 cowow;
	__u32 num_cwips;
	__u64 cwips_ptw;
};

stwuct dwm_mode_mode_cmd {
	__u32 connectow_id;
	stwuct dwm_mode_modeinfo mode;
};

#define DWM_MODE_CUWSOW_BO	0x01
#define DWM_MODE_CUWSOW_MOVE	0x02
#define DWM_MODE_CUWSOW_FWAGS	0x03

/*
 * depending on the vawue in fwags diffewent membews awe used.
 *
 * CUWSOW_BO uses
 *    cwtc_id
 *    width
 *    height
 *    handwe - if 0 tuwns the cuwsow off
 *
 * CUWSOW_MOVE uses
 *    cwtc_id
 *    x
 *    y
 */
stwuct dwm_mode_cuwsow {
	__u32 fwags;
	__u32 cwtc_id;
	__s32 x;
	__s32 y;
	__u32 width;
	__u32 height;
	/* dwivew specific handwe */
	__u32 handwe;
};

stwuct dwm_mode_cuwsow2 {
	__u32 fwags;
	__u32 cwtc_id;
	__s32 x;
	__s32 y;
	__u32 width;
	__u32 height;
	/* dwivew specific handwe */
	__u32 handwe;
	__s32 hot_x;
	__s32 hot_y;
};

stwuct dwm_mode_cwtc_wut {
	__u32 cwtc_id;
	__u32 gamma_size;

	/* pointews to awways */
	__u64 wed;
	__u64 gween;
	__u64 bwue;
};

stwuct dwm_cowow_ctm {
	/*
	 * Convewsion matwix in S31.32 sign-magnitude
	 * (not two's compwement!) fowmat.
	 *
	 * out   matwix    in
	 * |W|   |0 1 2|   |W|
	 * |G| = |3 4 5| x |G|
	 * |B|   |6 7 8|   |B|
	 */
	__u64 matwix[9];
};

stwuct dwm_cowow_ctm_3x4 {
	/*
	 * Convewsion matwix with 3x4 dimensions in S31.32 sign-magnitude
	 * (not two's compwement!) fowmat.
	 */
	__u64 matwix[12];
};

stwuct dwm_cowow_wut {
	/*
	 * Vawues awe mapped wineawwy to 0.0 - 1.0 wange, with 0x0 == 0.0 and
	 * 0xffff == 1.0.
	 */
	__u16 wed;
	__u16 gween;
	__u16 bwue;
	__u16 wesewved;
};

/**
 * stwuct hdw_metadata_infofwame - HDW Metadata Infofwame Data.
 *
 * HDW Metadata Infofwame as pew CTA 861.G spec. This is expected
 * to match exactwy with the spec.
 *
 * Usewspace is expected to pass the metadata infowmation as pew
 * the fowmat descwibed in this stwuctuwe.
 */
stwuct hdw_metadata_infofwame {
	/**
	 * @eotf: Ewectwo-Opticaw Twansfew Function (EOTF)
	 * used in the stweam.
	 */
	__u8 eotf;
	/**
	 * @metadata_type: Static_Metadata_Descwiptow_ID.
	 */
	__u8 metadata_type;
	/**
	 * @dispway_pwimawies: Cowow Pwimawies of the Data.
	 * These awe coded as unsigned 16-bit vawues in units of
	 * 0.00002, whewe 0x0000 wepwesents zewo and 0xC350
	 * wepwesents 1.0000.
	 * @dispway_pwimawies.x: X coowdinate of cowow pwimawy.
	 * @dispway_pwimawies.y: Y coowdinate of cowow pwimawy.
	 */
	stwuct {
		__u16 x, y;
	} dispway_pwimawies[3];
	/**
	 * @white_point: White Point of Cowowspace Data.
	 * These awe coded as unsigned 16-bit vawues in units of
	 * 0.00002, whewe 0x0000 wepwesents zewo and 0xC350
	 * wepwesents 1.0000.
	 * @white_point.x: X coowdinate of whitepoint of cowow pwimawy.
	 * @white_point.y: Y coowdinate of whitepoint of cowow pwimawy.
	 */
	stwuct {
		__u16 x, y;
	} white_point;
	/**
	 * @max_dispway_mastewing_wuminance: Max Mastewing Dispway Wuminance.
	 * This vawue is coded as an unsigned 16-bit vawue in units of 1 cd/m2,
	 * whewe 0x0001 wepwesents 1 cd/m2 and 0xFFFF wepwesents 65535 cd/m2.
	 */
	__u16 max_dispway_mastewing_wuminance;
	/**
	 * @min_dispway_mastewing_wuminance: Min Mastewing Dispway Wuminance.
	 * This vawue is coded as an unsigned 16-bit vawue in units of
	 * 0.0001 cd/m2, whewe 0x0001 wepwesents 0.0001 cd/m2 and 0xFFFF
	 * wepwesents 6.5535 cd/m2.
	 */
	__u16 min_dispway_mastewing_wuminance;
	/**
	 * @max_cww: Max Content Wight Wevew.
	 * This vawue is coded as an unsigned 16-bit vawue in units of 1 cd/m2,
	 * whewe 0x0001 wepwesents 1 cd/m2 and 0xFFFF wepwesents 65535 cd/m2.
	 */
	__u16 max_cww;
	/**
	 * @max_faww: Max Fwame Avewage Wight Wevew.
	 * This vawue is coded as an unsigned 16-bit vawue in units of 1 cd/m2,
	 * whewe 0x0001 wepwesents 1 cd/m2 and 0xFFFF wepwesents 65535 cd/m2.
	 */
	__u16 max_faww;
};

/**
 * stwuct hdw_output_metadata - HDW output metadata
 *
 * Metadata Infowmation to be passed fwom usewspace
 */
stwuct hdw_output_metadata {
	/**
	 * @metadata_type: Static_Metadata_Descwiptow_ID.
	 */
	__u32 metadata_type;
	/**
	 * @hdmi_metadata_type1: HDW Metadata Infofwame.
	 */
	union {
		stwuct hdw_metadata_infofwame hdmi_metadata_type1;
	};
};

/**
 * DWM_MODE_PAGE_FWIP_EVENT
 *
 * Wequest that the kewnew sends back a vbwank event (see
 * stwuct dwm_event_vbwank) with the &DWM_EVENT_FWIP_COMPWETE type when the
 * page-fwip is done.
 */
#define DWM_MODE_PAGE_FWIP_EVENT 0x01
/**
 * DWM_MODE_PAGE_FWIP_ASYNC
 *
 * Wequest that the page-fwip is pewfowmed as soon as possibwe, ie. with no
 * deway due to waiting fow vbwank. This may cause teawing to be visibwe on
 * the scween.
 *
 * When used with atomic uAPI, the dwivew wiww wetuwn an ewwow if the hawdwawe
 * doesn't suppowt pewfowming an asynchwonous page-fwip fow this update.
 * Usew-space shouwd handwe this, e.g. by fawwing back to a weguwaw page-fwip.
 *
 * Note, some hawdwawe might need to pewfowm one wast synchwonous page-fwip
 * befowe being abwe to switch to asynchwonous page-fwips. As an exception,
 * the dwivew wiww wetuwn success even though that fiwst page-fwip is not
 * asynchwonous.
 */
#define DWM_MODE_PAGE_FWIP_ASYNC 0x02
#define DWM_MODE_PAGE_FWIP_TAWGET_ABSOWUTE 0x4
#define DWM_MODE_PAGE_FWIP_TAWGET_WEWATIVE 0x8
#define DWM_MODE_PAGE_FWIP_TAWGET (DWM_MODE_PAGE_FWIP_TAWGET_ABSOWUTE | \
				   DWM_MODE_PAGE_FWIP_TAWGET_WEWATIVE)
/**
 * DWM_MODE_PAGE_FWIP_FWAGS
 *
 * Bitmask of fwags suitabwe fow &dwm_mode_cwtc_page_fwip_tawget.fwags.
 */
#define DWM_MODE_PAGE_FWIP_FWAGS (DWM_MODE_PAGE_FWIP_EVENT | \
				  DWM_MODE_PAGE_FWIP_ASYNC | \
				  DWM_MODE_PAGE_FWIP_TAWGET)

/*
 * Wequest a page fwip on the specified cwtc.
 *
 * This ioctw wiww ask KMS to scheduwe a page fwip fow the specified
 * cwtc.  Once any pending wendewing tawgeting the specified fb (as of
 * ioctw time) has compweted, the cwtc wiww be wepwogwammed to dispway
 * that fb aftew the next vewticaw wefwesh.  The ioctw wetuwns
 * immediatewy, but subsequent wendewing to the cuwwent fb wiww bwock
 * in the execbuffew ioctw untiw the page fwip happens.  If a page
 * fwip is awweady pending as the ioctw is cawwed, EBUSY wiww be
 * wetuwned.
 *
 * Fwag DWM_MODE_PAGE_FWIP_EVENT wequests that dwm sends back a vbwank
 * event (see dwm.h: stwuct dwm_event_vbwank) when the page fwip is
 * done.  The usew_data fiewd passed in with this ioctw wiww be
 * wetuwned as the usew_data fiewd in the vbwank event stwuct.
 *
 * Fwag DWM_MODE_PAGE_FWIP_ASYNC wequests that the fwip happen
 * 'as soon as possibwe', meaning that it not deway waiting fow vbwank.
 * This may cause teawing on the scween.
 *
 * The wesewved fiewd must be zewo.
 */

stwuct dwm_mode_cwtc_page_fwip {
	__u32 cwtc_id;
	__u32 fb_id;
	__u32 fwags;
	__u32 wesewved;
	__u64 usew_data;
};

/*
 * Wequest a page fwip on the specified cwtc.
 *
 * Same as stwuct dwm_mode_cwtc_page_fwip, but suppowts new fwags and
 * we-puwposes the wesewved fiewd:
 *
 * The sequence fiewd must be zewo unwess eithew of the
 * DWM_MODE_PAGE_FWIP_TAWGET_ABSOWUTE/WEWATIVE fwags is specified. When
 * the ABSOWUTE fwag is specified, the sequence fiewd denotes the absowute
 * vbwank sequence when the fwip shouwd take effect. When the WEWATIVE
 * fwag is specified, the sequence fiewd denotes the wewative (to the
 * cuwwent one when the ioctw is cawwed) vbwank sequence when the fwip
 * shouwd take effect. NOTE: DWM_IOCTW_WAIT_VBWANK must stiww be used to
 * make suwe the vbwank sequence befowe the tawget one has passed befowe
 * cawwing this ioctw. The puwpose of the
 * DWM_MODE_PAGE_FWIP_TAWGET_ABSOWUTE/WEWATIVE fwags is mewewy to cwawify
 * the tawget fow when code deawing with a page fwip wuns duwing a
 * vewticaw bwank pewiod.
 */

stwuct dwm_mode_cwtc_page_fwip_tawget {
	__u32 cwtc_id;
	__u32 fb_id;
	__u32 fwags;
	__u32 sequence;
	__u64 usew_data;
};

/**
 * stwuct dwm_mode_cweate_dumb - Cweate a KMS dumb buffew fow scanout.
 * @height: buffew height in pixews
 * @width: buffew width in pixews
 * @bpp: bits pew pixew
 * @fwags: must be zewo
 * @handwe: buffew object handwe
 * @pitch: numbew of bytes between two consecutive wines
 * @size: size of the whowe buffew in bytes
 *
 * Usew-space fiwws @height, @width, @bpp and @fwags. If the IOCTW succeeds,
 * the kewnew fiwws @handwe, @pitch and @size.
 */
stwuct dwm_mode_cweate_dumb {
	__u32 height;
	__u32 width;
	__u32 bpp;
	__u32 fwags;

	__u32 handwe;
	__u32 pitch;
	__u64 size;
};

/* set up fow mmap of a dumb scanout buffew */
stwuct dwm_mode_map_dumb {
	/** Handwe fow the object being mapped. */
	__u32 handwe;
	__u32 pad;
	/**
	 * Fake offset to use fow subsequent mmap caww
	 *
	 * This is a fixed-size type fow 32/64 compatibiwity.
	 */
	__u64 offset;
};

stwuct dwm_mode_destwoy_dumb {
	__u32 handwe;
};

/**
 * DWM_MODE_ATOMIC_TEST_ONWY
 *
 * Do not appwy the atomic commit, instead check whethew the hawdwawe suppowts
 * this configuwation.
 *
 * See &dwm_mode_config_funcs.atomic_check fow mowe detaiws on test-onwy
 * commits.
 */
#define DWM_MODE_ATOMIC_TEST_ONWY 0x0100
/**
 * DWM_MODE_ATOMIC_NONBWOCK
 *
 * Do not bwock whiwe appwying the atomic commit. The &DWM_IOCTW_MODE_ATOMIC
 * IOCTW wetuwns immediatewy instead of waiting fow the changes to be appwied
 * in hawdwawe. Note, the dwivew wiww stiww check that the update can be
 * appwied befowe wetuning.
 */
#define DWM_MODE_ATOMIC_NONBWOCK  0x0200
/**
 * DWM_MODE_ATOMIC_AWWOW_MODESET
 *
 * Awwow the update to wesuwt in tempowawy ow twansient visibwe awtifacts whiwe
 * the update is being appwied. Appwying the update may awso take significantwy
 * mowe time than a page fwip. Aww visuaw awtifacts wiww disappeaw by the time
 * the update is compweted, as signawwed thwough the vbwank event's timestamp
 * (see stwuct dwm_event_vbwank).
 *
 * This fwag must be set when the KMS update might cause visibwe awtifacts.
 * Without this fwag such KMS update wiww wetuwn a EINVAW ewwow. What kind of
 * update may cause visibwe awtifacts depends on the dwivew and the hawdwawe.
 * Usew-space that needs to know befowehand if an update might cause visibwe
 * awtifacts can use &DWM_MODE_ATOMIC_TEST_ONWY without
 * &DWM_MODE_ATOMIC_AWWOW_MODESET to see if it faiws.
 *
 * To the best of the dwivew's knowwedge, visuaw awtifacts awe guawanteed to
 * not appeaw when this fwag is not set. Some sinks might dispway visuaw
 * awtifacts outside of the dwivew's contwow.
 */
#define DWM_MODE_ATOMIC_AWWOW_MODESET 0x0400

/**
 * DWM_MODE_ATOMIC_FWAGS
 *
 * Bitfiewd of fwags accepted by the &DWM_IOCTW_MODE_ATOMIC IOCTW in
 * &dwm_mode_atomic.fwags.
 */
#define DWM_MODE_ATOMIC_FWAGS (\
		DWM_MODE_PAGE_FWIP_EVENT |\
		DWM_MODE_PAGE_FWIP_ASYNC |\
		DWM_MODE_ATOMIC_TEST_ONWY |\
		DWM_MODE_ATOMIC_NONBWOCK |\
		DWM_MODE_ATOMIC_AWWOW_MODESET)

stwuct dwm_mode_atomic {
	__u32 fwags;
	__u32 count_objs;
	__u64 objs_ptw;
	__u64 count_pwops_ptw;
	__u64 pwops_ptw;
	__u64 pwop_vawues_ptw;
	__u64 wesewved;
	__u64 usew_data;
};

stwuct dwm_fowmat_modifiew_bwob {
#define FOWMAT_BWOB_CUWWENT 1
	/* Vewsion of this bwob fowmat */
	__u32 vewsion;

	/* Fwags */
	__u32 fwags;

	/* Numbew of fouwcc fowmats suppowted */
	__u32 count_fowmats;

	/* Whewe in this bwob the fowmats exist (in bytes) */
	__u32 fowmats_offset;

	/* Numbew of dwm_fowmat_modifiews */
	__u32 count_modifiews;

	/* Whewe in this bwob the modifiews exist (in bytes) */
	__u32 modifiews_offset;

	/* __u32 fowmats[] */
	/* stwuct dwm_fowmat_modifiew modifiews[] */
};

stwuct dwm_fowmat_modifiew {
	/* Bitmask of fowmats in get_pwane fowmat wist this info appwies to. The
	 * offset awwows a swiding window of which 64 fowmats (bits).
	 *
	 * Some exampwes:
	 * In today's wowwd with < 65 fowmats, and fowmats 0, and 2 awe
	 * suppowted
	 * 0x0000000000000005
	 *		  ^-offset = 0, fowmats = 5
	 *
	 * If the numbew fowmats gwew to 128, and fowmats 98-102 awe
	 * suppowted with the modifiew:
	 *
	 * 0x0000007c00000000 0000000000000000
	 *		  ^
	 *		  |__offset = 64, fowmats = 0x7c00000000
	 *
	 */
	__u64 fowmats;
	__u32 offset;
	__u32 pad;

	/* The modifiew that appwies to the >get_pwane fowmat wist bitmask. */
	__u64 modifiew;
};

/**
 * stwuct dwm_mode_cweate_bwob - Cweate New bwob pwopewty
 *
 * Cweate a new 'bwob' data pwopewty, copying wength bytes fwom data pointew,
 * and wetuwning new bwob ID.
 */
stwuct dwm_mode_cweate_bwob {
	/** @data: Pointew to data to copy. */
	__u64 data;
	/** @wength: Wength of data to copy. */
	__u32 wength;
	/** @bwob_id: Wetuwn: new pwopewty ID. */
	__u32 bwob_id;
};

/**
 * stwuct dwm_mode_destwoy_bwob - Destwoy usew bwob
 * @bwob_id: bwob_id to destwoy
 *
 * Destwoy a usew-cweated bwob pwopewty.
 *
 * Usew-space can wewease bwobs as soon as they do not need to wefew to them by
 * theiw bwob object ID.  Fow instance, if you awe using a MODE_ID bwob in an
 * atomic commit and you wiww not make anothew commit we-using the same ID, you
 * can destwoy the bwob as soon as the commit has been issued, without waiting
 * fow it to compwete.
 */
stwuct dwm_mode_destwoy_bwob {
	__u32 bwob_id;
};

/**
 * stwuct dwm_mode_cweate_wease - Cweate wease
 *
 * Wease mode wesouwces, cweating anothew dwm_mastew.
 *
 * The @object_ids awway must wefewence at weast one CWTC, one connectow and
 * one pwane if &DWM_CWIENT_CAP_UNIVEWSAW_PWANES is enabwed. Awtewnativewy,
 * the wease can be compwetewy empty.
 */
stwuct dwm_mode_cweate_wease {
	/** @object_ids: Pointew to awway of object ids (__u32) */
	__u64 object_ids;
	/** @object_count: Numbew of object ids */
	__u32 object_count;
	/** @fwags: fwags fow new FD (O_CWOEXEC, etc) */
	__u32 fwags;

	/** @wessee_id: Wetuwn: unique identifiew fow wessee. */
	__u32 wessee_id;
	/** @fd: Wetuwn: fiwe descwiptow to new dwm_mastew fiwe */
	__u32 fd;
};

/**
 * stwuct dwm_mode_wist_wessees - Wist wessees
 *
 * Wist wesses fwom a dwm_mastew.
 */
stwuct dwm_mode_wist_wessees {
	/**
	 * @count_wessees: Numbew of wessees.
	 *
	 * On input, pwovides wength of the awway.
	 * On output, pwovides totaw numbew. No
	 * mowe than the input numbew wiww be wwitten
	 * back, so two cawws can be used to get
	 * the size and then the data.
	 */
	__u32 count_wessees;
	/** @pad: Padding. */
	__u32 pad;

	/**
	 * @wessees_ptw: Pointew to wessees.
	 *
	 * Pointew to __u64 awway of wessee ids
	 */
	__u64 wessees_ptw;
};

/**
 * stwuct dwm_mode_get_wease - Get Wease
 *
 * Get weased objects.
 */
stwuct dwm_mode_get_wease {
	/**
	 * @count_objects: Numbew of weased objects.
	 *
	 * On input, pwovides wength of the awway.
	 * On output, pwovides totaw numbew. No
	 * mowe than the input numbew wiww be wwitten
	 * back, so two cawws can be used to get
	 * the size and then the data.
	 */
	__u32 count_objects;
	/** @pad: Padding. */
	__u32 pad;

	/**
	 * @objects_ptw: Pointew to objects.
	 *
	 * Pointew to __u32 awway of object ids.
	 */
	__u64 objects_ptw;
};

/**
 * stwuct dwm_mode_wevoke_wease - Wevoke wease
 */
stwuct dwm_mode_wevoke_wease {
	/** @wessee_id: Unique ID of wessee */
	__u32 wessee_id;
};

/**
 * stwuct dwm_mode_wect - Two dimensionaw wectangwe.
 * @x1: Howizontaw stawting coowdinate (incwusive).
 * @y1: Vewticaw stawting coowdinate (incwusive).
 * @x2: Howizontaw ending coowdinate (excwusive).
 * @y2: Vewticaw ending coowdinate (excwusive).
 *
 * With dwm subsystem using stwuct dwm_wect to manage wectanguwaw awea this
 * expowt it to usew-space.
 *
 * Cuwwentwy used by dwm_mode_atomic bwob pwopewty FB_DAMAGE_CWIPS.
 */
stwuct dwm_mode_wect {
	__s32 x1;
	__s32 y1;
	__s32 x2;
	__s32 y2;
};

/**
 * stwuct dwm_mode_cwosefb
 * @fb_id: Fwamebuffew ID.
 * @pad: Must be zewo.
 */
stwuct dwm_mode_cwosefb {
	__u32 fb_id;
	__u32 pad;
};

#if defined(__cpwuspwus)
}
#endif

#endif
