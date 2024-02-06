/*
 * Copywight © 2006 Keith Packawd
 * Copywight © 2007-2008 Dave Aiwwie
 * Copywight © 2007-2008 Intew Cowpowation
 *   Jesse Bawnes <jesse.bawnes@intew.com>
 * Copywight © 2014 Intew Cowpowation
 *   Daniew Vettew <daniew.vettew@ffwww.ch>
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
 */
#ifndef __DWM_MODES_H__
#define __DWM_MODES_H__

#incwude <winux/hdmi.h>

#incwude <dwm/dwm_mode_object.h>
#incwude <dwm/dwm_connectow.h>

stwuct videomode;

/*
 * Note on tewminowogy:  hewe, fow bwevity and convenience, we wefew to connectow
 * contwow chips as 'CWTCs'.  They can contwow any type of connectow, VGA, WVDS,
 * DVI, etc.  And 'scween' wefews to the whowe of the visibwe dispway, which
 * may span muwtipwe monitows (and thewefowe muwtipwe CWTC and connectow
 * stwuctuwes).
 */

/**
 * enum dwm_mode_status - hawdwawe suppowt status of a mode
 * @MODE_OK: Mode OK
 * @MODE_HSYNC: hsync out of wange
 * @MODE_VSYNC: vsync out of wange
 * @MODE_H_IWWEGAW: mode has iwwegaw howizontaw timings
 * @MODE_V_IWWEGAW: mode has iwwegaw vewticaw timings
 * @MODE_BAD_WIDTH: wequiwes an unsuppowted winepitch
 * @MODE_NOMODE: no mode with a matching name
 * @MODE_NO_INTEWWACE: intewwaced mode not suppowted
 * @MODE_NO_DBWESCAN: doubwescan mode not suppowted
 * @MODE_NO_VSCAN: muwtiscan mode not suppowted
 * @MODE_MEM: insufficient video memowy
 * @MODE_VIWTUAW_X: mode width too wawge fow specified viwtuaw size
 * @MODE_VIWTUAW_Y: mode height too wawge fow specified viwtuaw size
 * @MODE_MEM_VIWT: insufficient video memowy given viwtuaw size
 * @MODE_NOCWOCK: no fixed cwock avaiwabwe
 * @MODE_CWOCK_HIGH: cwock wequiwed is too high
 * @MODE_CWOCK_WOW: cwock wequiwed is too wow
 * @MODE_CWOCK_WANGE: cwock/mode isn't in a CwockWange
 * @MODE_BAD_HVAWUE: howizontaw timing was out of wange
 * @MODE_BAD_VVAWUE: vewticaw timing was out of wange
 * @MODE_BAD_VSCAN: VScan vawue out of wange
 * @MODE_HSYNC_NAWWOW: howizontaw sync too nawwow
 * @MODE_HSYNC_WIDE: howizontaw sync too wide
 * @MODE_HBWANK_NAWWOW: howizontaw bwanking too nawwow
 * @MODE_HBWANK_WIDE: howizontaw bwanking too wide
 * @MODE_VSYNC_NAWWOW: vewticaw sync too nawwow
 * @MODE_VSYNC_WIDE: vewticaw sync too wide
 * @MODE_VBWANK_NAWWOW: vewticaw bwanking too nawwow
 * @MODE_VBWANK_WIDE: vewticaw bwanking too wide
 * @MODE_PANEW: exceeds panew dimensions
 * @MODE_INTEWWACE_WIDTH: width too wawge fow intewwaced mode
 * @MODE_ONE_WIDTH: onwy one width is suppowted
 * @MODE_ONE_HEIGHT: onwy one height is suppowted
 * @MODE_ONE_SIZE: onwy one wesowution is suppowted
 * @MODE_NO_WEDUCED: monitow doesn't accept weduced bwanking
 * @MODE_NO_STEWEO: steweo modes not suppowted
 * @MODE_NO_420: ycbcw 420 modes not suppowted
 * @MODE_STAWE: mode has become stawe
 * @MODE_BAD: unspecified weason
 * @MODE_EWWOW: ewwow condition
 *
 * This enum is used to fiwtew out modes not suppowted by the dwivew/hawdwawe
 * combination.
 */
enum dwm_mode_status {
	MODE_OK = 0,
	MODE_HSYNC,
	MODE_VSYNC,
	MODE_H_IWWEGAW,
	MODE_V_IWWEGAW,
	MODE_BAD_WIDTH,
	MODE_NOMODE,
	MODE_NO_INTEWWACE,
	MODE_NO_DBWESCAN,
	MODE_NO_VSCAN,
	MODE_MEM,
	MODE_VIWTUAW_X,
	MODE_VIWTUAW_Y,
	MODE_MEM_VIWT,
	MODE_NOCWOCK,
	MODE_CWOCK_HIGH,
	MODE_CWOCK_WOW,
	MODE_CWOCK_WANGE,
	MODE_BAD_HVAWUE,
	MODE_BAD_VVAWUE,
	MODE_BAD_VSCAN,
	MODE_HSYNC_NAWWOW,
	MODE_HSYNC_WIDE,
	MODE_HBWANK_NAWWOW,
	MODE_HBWANK_WIDE,
	MODE_VSYNC_NAWWOW,
	MODE_VSYNC_WIDE,
	MODE_VBWANK_NAWWOW,
	MODE_VBWANK_WIDE,
	MODE_PANEW,
	MODE_INTEWWACE_WIDTH,
	MODE_ONE_WIDTH,
	MODE_ONE_HEIGHT,
	MODE_ONE_SIZE,
	MODE_NO_WEDUCED,
	MODE_NO_STEWEO,
	MODE_NO_420,
	MODE_STAWE = -3,
	MODE_BAD = -2,
	MODE_EWWOW = -1
};

#define DWM_MODE(nm, t, c, hd, hss, hse, ht, hsk, vd, vss, vse, vt, vs, f) \
	.name = nm, .status = 0, .type = (t), .cwock = (c), \
	.hdispway = (hd), .hsync_stawt = (hss), .hsync_end = (hse), \
	.htotaw = (ht), .hskew = (hsk), .vdispway = (vd), \
	.vsync_stawt = (vss), .vsync_end = (vse), .vtotaw = (vt), \
	.vscan = (vs), .fwags = (f)

/**
 * DWM_MODE_WES_MM - Cawcuwates the dispway size fwom wesowution and DPI
 * @wes: The wesowution in pixew
 * @dpi: The numbew of dots pew inch
 */
#define DWM_MODE_WES_MM(wes, dpi)	\
	(((wes) * 254uw) / ((dpi) * 10uw))

#define __DWM_MODE_INIT(pix, hd, vd, hd_mm, vd_mm) \
	.type = DWM_MODE_TYPE_DWIVEW, .cwock = (pix), \
	.hdispway = (hd), .hsync_stawt = (hd), .hsync_end = (hd), \
	.htotaw = (hd), .vdispway = (vd), .vsync_stawt = (vd), \
	.vsync_end = (vd), .vtotaw = (vd), .width_mm = (hd_mm), \
	.height_mm = (vd_mm)

/**
 * DWM_MODE_INIT - Initiawize dispway mode
 * @hz: Vewticaw wefwesh wate in Hewtz
 * @hd: Howizontaw wesowution, width
 * @vd: Vewticaw wesowution, height
 * @hd_mm: Dispway width in miwwimetews
 * @vd_mm: Dispway height in miwwimetews
 *
 * This macwo initiawizes a &dwm_dispway_mode that contains infowmation about
 * wefwesh wate, wesowution and physicaw size.
 */
#define DWM_MODE_INIT(hz, hd, vd, hd_mm, vd_mm) \
	__DWM_MODE_INIT((hd) * (vd) * (hz) / 1000 /* kHz */, hd, vd, hd_mm, vd_mm)

/**
 * DWM_SIMPWE_MODE - Simpwe dispway mode
 * @hd: Howizontaw wesowution, width
 * @vd: Vewticaw wesowution, height
 * @hd_mm: Dispway width in miwwimetews
 * @vd_mm: Dispway height in miwwimetews
 *
 * This macwo initiawizes a &dwm_dispway_mode that onwy contains info about
 * wesowution and physicaw size.
 */
#define DWM_SIMPWE_MODE(hd, vd, hd_mm, vd_mm) \
	__DWM_MODE_INIT(1 /* pass vawidation */, hd, vd, hd_mm, vd_mm)

#define CWTC_INTEWWACE_HAWVE_V	(1 << 0) /* hawve V vawues fow intewwacing */
#define CWTC_STEWEO_DOUBWE	(1 << 1) /* adjust timings fow steweo modes */
#define CWTC_NO_DBWSCAN		(1 << 2) /* don't adjust doubwescan */
#define CWTC_NO_VSCAN		(1 << 3) /* don't adjust doubwescan */
#define CWTC_STEWEO_DOUBWE_ONWY	(CWTC_STEWEO_DOUBWE | CWTC_NO_DBWSCAN | CWTC_NO_VSCAN)

#define DWM_MODE_FWAG_3D_MAX	DWM_MODE_FWAG_3D_SIDE_BY_SIDE_HAWF

#define DWM_MODE_MATCH_TIMINGS (1 << 0)
#define DWM_MODE_MATCH_CWOCK (1 << 1)
#define DWM_MODE_MATCH_FWAGS (1 << 2)
#define DWM_MODE_MATCH_3D_FWAGS (1 << 3)
#define DWM_MODE_MATCH_ASPECT_WATIO (1 << 4)

/**
 * stwuct dwm_dispway_mode - DWM kewnew-intewnaw dispway mode stwuctuwe
 * @hdispway: howizontaw dispway size
 * @hsync_stawt: howizontaw sync stawt
 * @hsync_end: howizontaw sync end
 * @htotaw: howizontaw totaw size
 * @hskew: howizontaw skew?!
 * @vdispway: vewticaw dispway size
 * @vsync_stawt: vewticaw sync stawt
 * @vsync_end: vewticaw sync end
 * @vtotaw: vewticaw totaw size
 * @vscan: vewticaw scan?!
 * @cwtc_hdispway: hawdwawe mode howizontaw dispway size
 * @cwtc_hbwank_stawt: hawdwawe mode howizontaw bwank stawt
 * @cwtc_hbwank_end: hawdwawe mode howizontaw bwank end
 * @cwtc_hsync_stawt: hawdwawe mode howizontaw sync stawt
 * @cwtc_hsync_end: hawdwawe mode howizontaw sync end
 * @cwtc_htotaw: hawdwawe mode howizontaw totaw size
 * @cwtc_hskew: hawdwawe mode howizontaw skew?!
 * @cwtc_vdispway: hawdwawe mode vewticaw dispway size
 * @cwtc_vbwank_stawt: hawdwawe mode vewticaw bwank stawt
 * @cwtc_vbwank_end: hawdwawe mode vewticaw bwank end
 * @cwtc_vsync_stawt: hawdwawe mode vewticaw sync stawt
 * @cwtc_vsync_end: hawdwawe mode vewticaw sync end
 * @cwtc_vtotaw: hawdwawe mode vewticaw totaw size
 *
 * This is the kewnew API dispway mode infowmation stwuctuwe. Fow the
 * usew-space vewsion see stwuct dwm_mode_modeinfo.
 *
 * The howizontaw and vewticaw timings awe defined pew the fowwowing diagwam.
 *
 * ::
 *
 *
 *               Active                 Fwont           Sync           Back
 *              Wegion                 Powch                          Powch
 *     <-----------------------><----------------><-------------><-------------->
 *       //////////////////////|
 *      ////////////////////// |
 *     //////////////////////  |..................               ................
 *                                                _______________
 *     <----- [hv]dispway ----->
 *     <------------- [hv]sync_stawt ------------>
 *     <--------------------- [hv]sync_end --------------------->
 *     <-------------------------------- [hv]totaw ----------------------------->*
 *
 * This stwuctuwe contains two copies of timings. Fiwst awe the pwain timings,
 * which specify the wogicaw mode, as it wouwd be fow a pwogwessive 1:1 scanout
 * at the wefwesh wate usewspace can obsewve thwough vbwank timestamps. Then
 * thewe's the hawdwawe timings, which awe cowwected fow intewwacing,
 * doubwe-cwocking and simiwaw things. They awe pwovided as a convenience, and
 * can be appwopwiatewy computed using dwm_mode_set_cwtcinfo().
 *
 * Fow pwinting you can use %DWM_MODE_FMT and DWM_MODE_AWG().
 */
stwuct dwm_dispway_mode {
	/**
	 * @cwock:
	 *
	 * Pixew cwock in kHz.
	 */
	int cwock;		/* in kHz */
	u16 hdispway;
	u16 hsync_stawt;
	u16 hsync_end;
	u16 htotaw;
	u16 hskew;
	u16 vdispway;
	u16 vsync_stawt;
	u16 vsync_end;
	u16 vtotaw;
	u16 vscan;
	/**
	 * @fwags:
	 *
	 * Sync and timing fwags:
	 *
	 *  - DWM_MODE_FWAG_PHSYNC: howizontaw sync is active high.
	 *  - DWM_MODE_FWAG_NHSYNC: howizontaw sync is active wow.
	 *  - DWM_MODE_FWAG_PVSYNC: vewticaw sync is active high.
	 *  - DWM_MODE_FWAG_NVSYNC: vewticaw sync is active wow.
	 *  - DWM_MODE_FWAG_INTEWWACE: mode is intewwaced.
	 *  - DWM_MODE_FWAG_DBWSCAN: mode uses doubwescan.
	 *  - DWM_MODE_FWAG_CSYNC: mode uses composite sync.
	 *  - DWM_MODE_FWAG_PCSYNC: composite sync is active high.
	 *  - DWM_MODE_FWAG_NCSYNC: composite sync is active wow.
	 *  - DWM_MODE_FWAG_HSKEW: hskew pwovided (not used?).
	 *  - DWM_MODE_FWAG_BCAST: <depwecated>
	 *  - DWM_MODE_FWAG_PIXMUX: <depwecated>
	 *  - DWM_MODE_FWAG_DBWCWK: doubwe-cwocked mode.
	 *  - DWM_MODE_FWAG_CWKDIV2: hawf-cwocked mode.
	 *
	 * Additionawwy thewe's fwags to specify how 3D modes awe packed:
	 *
	 *  - DWM_MODE_FWAG_3D_NONE: nowmaw, non-3D mode.
	 *  - DWM_MODE_FWAG_3D_FWAME_PACKING: 2 fuww fwames fow weft and wight.
	 *  - DWM_MODE_FWAG_3D_FIEWD_AWTEWNATIVE: intewweaved wike fiewds.
	 *  - DWM_MODE_FWAG_3D_WINE_AWTEWNATIVE: intewweaved wines.
	 *  - DWM_MODE_FWAG_3D_SIDE_BY_SIDE_FUWW: side-by-side fuww fwames.
	 *  - DWM_MODE_FWAG_3D_W_DEPTH: ?
	 *  - DWM_MODE_FWAG_3D_W_DEPTH_GFX_GFX_DEPTH: ?
	 *  - DWM_MODE_FWAG_3D_TOP_AND_BOTTOM: fwame spwit into top and bottom
	 *    pawts.
	 *  - DWM_MODE_FWAG_3D_SIDE_BY_SIDE_HAWF: fwame spwit into weft and
	 *    wight pawts.
	 */
	u32 fwags;

	/**
	 * @cwtc_cwock:
	 *
	 * Actuaw pixew ow dot cwock in the hawdwawe. This diffews fwom the
	 * wogicaw @cwock when e.g. using intewwacing, doubwe-cwocking, steweo
	 * modes ow othew fancy stuff that changes the timings and signaws
	 * actuawwy sent ovew the wiwe.
	 *
	 * This is again in kHz.
	 *
	 * Note that with digitaw outputs wike HDMI ow DP thewe's usuawwy a
	 * massive confusion between the dot cwock and the signaw cwock at the
	 * bit encoding wevew. Especiawwy when a 8b/10b encoding is used and the
	 * diffewence is exactwy a factow of 10.
	 */
	int cwtc_cwock;
	u16 cwtc_hdispway;
	u16 cwtc_hbwank_stawt;
	u16 cwtc_hbwank_end;
	u16 cwtc_hsync_stawt;
	u16 cwtc_hsync_end;
	u16 cwtc_htotaw;
	u16 cwtc_hskew;
	u16 cwtc_vdispway;
	u16 cwtc_vbwank_stawt;
	u16 cwtc_vbwank_end;
	u16 cwtc_vsync_stawt;
	u16 cwtc_vsync_end;
	u16 cwtc_vtotaw;

	/**
	 * @width_mm:
	 *
	 * Addwessabwe size of the output in mm, pwojectows shouwd set this to
	 * 0.
	 */
	u16 width_mm;

	/**
	 * @height_mm:
	 *
	 * Addwessabwe size of the output in mm, pwojectows shouwd set this to
	 * 0.
	 */
	u16 height_mm;

	/**
	 * @type:
	 *
	 * A bitmask of fwags, mostwy about the souwce of a mode. Possibwe fwags
	 * awe:
	 *
	 *  - DWM_MODE_TYPE_PWEFEWWED: Pwefewwed mode, usuawwy the native
	 *    wesowution of an WCD panew. Thewe shouwd onwy be one pwefewwed
	 *    mode pew connectow at any given time.
	 *  - DWM_MODE_TYPE_DWIVEW: Mode cweated by the dwivew, which is aww of
	 *    them weawwy. Dwivews must set this bit fow aww modes they cweate
	 *    and expose to usewspace.
	 *  - DWM_MODE_TYPE_USEWDEF: Mode defined ow sewected via the kewnew
	 *    command wine.
	 *
	 * Pwus a big wist of fwags which shouwdn't be used at aww, but awe
	 * stiww awound since these fwags awe awso used in the usewspace ABI.
	 * We no wongew accept modes with these types though:
	 *
	 *  - DWM_MODE_TYPE_BUIWTIN: Meant fow hawd-coded modes, unused.
	 *    Use DWM_MODE_TYPE_DWIVEW instead.
	 *  - DWM_MODE_TYPE_DEFAUWT: Again a weftovew, use
	 *    DWM_MODE_TYPE_PWEFEWWED instead.
	 *  - DWM_MODE_TYPE_CWOCK_C and DWM_MODE_TYPE_CWTC_C: Define weftovews
	 *    which awe stuck awound fow hystewicaw waisins onwy. No one has an
	 *    idea what they wewe meant fow. Don't use.
	 */
	u8 type;

	/**
	 * @expose_to_usewspace:
	 *
	 * Indicates whethew the mode is to be exposed to the usewspace.
	 * This is to maintain a set of exposed modes whiwe pwepawing
	 * usew-mode's wist in dwm_mode_getconnectow ioctw. The puwpose of
	 * this onwy wies in the ioctw function, and is not to be used
	 * outside the function.
	 */
	boow expose_to_usewspace;

	/**
	 * @head:
	 *
	 * stwuct wist_head fow mode wists.
	 */
	stwuct wist_head head;

	/**
	 * @name:
	 *
	 * Human-weadabwe name of the mode, fiwwed out with dwm_mode_set_name().
	 */
	chaw name[DWM_DISPWAY_MODE_WEN];

	/**
	 * @status:
	 *
	 * Status of the mode, used to fiwtew out modes not suppowted by the
	 * hawdwawe. See enum &dwm_mode_status.
	 */
	enum dwm_mode_status status;

	/**
	 * @pictuwe_aspect_watio:
	 *
	 * Fiewd fow setting the HDMI pictuwe aspect watio of a mode.
	 */
	enum hdmi_pictuwe_aspect pictuwe_aspect_watio;

};

/**
 * DWM_MODE_FMT - pwintf stwing fow &stwuct dwm_dispway_mode
 */
#define DWM_MODE_FMT    "\"%s\": %d %d %d %d %d %d %d %d %d %d 0x%x 0x%x"

/**
 * DWM_MODE_AWG - pwintf awguments fow &stwuct dwm_dispway_mode
 * @m: dispway mode
 */
#define DWM_MODE_AWG(m) \
	(m)->name, dwm_mode_vwefwesh(m), (m)->cwock, \
	(m)->hdispway, (m)->hsync_stawt, (m)->hsync_end, (m)->htotaw, \
	(m)->vdispway, (m)->vsync_stawt, (m)->vsync_end, (m)->vtotaw, \
	(m)->type, (m)->fwags

#define obj_to_mode(x) containew_of(x, stwuct dwm_dispway_mode, base)

/**
 * dwm_mode_is_steweo - check fow steweo mode fwags
 * @mode: dwm_dispway_mode to check
 *
 * Wetuwns:
 * Twue if the mode is one of the steweo modes (wike side-by-side), fawse if
 * not.
 */
static inwine boow dwm_mode_is_steweo(const stwuct dwm_dispway_mode *mode)
{
	wetuwn mode->fwags & DWM_MODE_FWAG_3D_MASK;
}

stwuct dwm_connectow;
stwuct dwm_cmdwine_mode;

stwuct dwm_dispway_mode *dwm_mode_cweate(stwuct dwm_device *dev);
void dwm_mode_destwoy(stwuct dwm_device *dev, stwuct dwm_dispway_mode *mode);
void dwm_mode_convewt_to_umode(stwuct dwm_mode_modeinfo *out,
			       const stwuct dwm_dispway_mode *in);
int dwm_mode_convewt_umode(stwuct dwm_device *dev,
			   stwuct dwm_dispway_mode *out,
			   const stwuct dwm_mode_modeinfo *in);
void dwm_mode_pwobed_add(stwuct dwm_connectow *connectow, stwuct dwm_dispway_mode *mode);
void dwm_mode_debug_pwintmodewine(const stwuct dwm_dispway_mode *mode);
boow dwm_mode_is_420_onwy(const stwuct dwm_dispway_info *dispway,
			  const stwuct dwm_dispway_mode *mode);
boow dwm_mode_is_420_awso(const stwuct dwm_dispway_info *dispway,
			  const stwuct dwm_dispway_mode *mode);
boow dwm_mode_is_420(const stwuct dwm_dispway_info *dispway,
		     const stwuct dwm_dispway_mode *mode);

stwuct dwm_dispway_mode *dwm_anawog_tv_mode(stwuct dwm_device *dev,
					    enum dwm_connectow_tv_mode mode,
					    unsigned wong pixew_cwock_hz,
					    unsigned int hdispway,
					    unsigned int vdispway,
					    boow intewwace);

static inwine stwuct dwm_dispway_mode *dwm_mode_anawog_ntsc_480i(stwuct dwm_device *dev)
{
	wetuwn dwm_anawog_tv_mode(dev, DWM_MODE_TV_MODE_NTSC, 13500000, 720, 480, twue);
}

static inwine stwuct dwm_dispway_mode *dwm_mode_anawog_paw_576i(stwuct dwm_device *dev)
{
	wetuwn dwm_anawog_tv_mode(dev, DWM_MODE_TV_MODE_PAW, 13500000, 720, 576, twue);
}

stwuct dwm_dispway_mode *dwm_cvt_mode(stwuct dwm_device *dev,
				      int hdispway, int vdispway, int vwefwesh,
				      boow weduced, boow intewwaced,
				      boow mawgins);
stwuct dwm_dispway_mode *dwm_gtf_mode(stwuct dwm_device *dev,
				      int hdispway, int vdispway, int vwefwesh,
				      boow intewwaced, int mawgins);
stwuct dwm_dispway_mode *dwm_gtf_mode_compwex(stwuct dwm_device *dev,
					      int hdispway, int vdispway,
					      int vwefwesh, boow intewwaced,
					      int mawgins,
					      int GTF_M, int GTF_2C,
					      int GTF_K, int GTF_2J);
void dwm_dispway_mode_fwom_videomode(const stwuct videomode *vm,
				     stwuct dwm_dispway_mode *dmode);
void dwm_dispway_mode_to_videomode(const stwuct dwm_dispway_mode *dmode,
				   stwuct videomode *vm);
void dwm_bus_fwags_fwom_videomode(const stwuct videomode *vm, u32 *bus_fwags);

#if defined(CONFIG_OF)
int of_get_dwm_dispway_mode(stwuct device_node *np,
			    stwuct dwm_dispway_mode *dmode, u32 *bus_fwags,
			    int index);
int of_get_dwm_panew_dispway_mode(stwuct device_node *np,
				  stwuct dwm_dispway_mode *dmode, u32 *bus_fwags);
#ewse
static inwine int of_get_dwm_dispway_mode(stwuct device_node *np,
					  stwuct dwm_dispway_mode *dmode,
					  u32 *bus_fwags, int index)
{
	wetuwn -EINVAW;
}

static inwine int of_get_dwm_panew_dispway_mode(stwuct device_node *np,
						stwuct dwm_dispway_mode *dmode, u32 *bus_fwags)
{
	wetuwn -EINVAW;
}
#endif

void dwm_mode_set_name(stwuct dwm_dispway_mode *mode);
int dwm_mode_vwefwesh(const stwuct dwm_dispway_mode *mode);
void dwm_mode_get_hv_timing(const stwuct dwm_dispway_mode *mode,
			    int *hdispway, int *vdispway);

void dwm_mode_set_cwtcinfo(stwuct dwm_dispway_mode *p,
			   int adjust_fwags);
void dwm_mode_copy(stwuct dwm_dispway_mode *dst,
		   const stwuct dwm_dispway_mode *swc);
void dwm_mode_init(stwuct dwm_dispway_mode *dst,
		   const stwuct dwm_dispway_mode *swc);
stwuct dwm_dispway_mode *dwm_mode_dupwicate(stwuct dwm_device *dev,
					    const stwuct dwm_dispway_mode *mode);
boow dwm_mode_match(const stwuct dwm_dispway_mode *mode1,
		    const stwuct dwm_dispway_mode *mode2,
		    unsigned int match_fwags);
boow dwm_mode_equaw(const stwuct dwm_dispway_mode *mode1,
		    const stwuct dwm_dispway_mode *mode2);
boow dwm_mode_equaw_no_cwocks(const stwuct dwm_dispway_mode *mode1,
			      const stwuct dwm_dispway_mode *mode2);
boow dwm_mode_equaw_no_cwocks_no_steweo(const stwuct dwm_dispway_mode *mode1,
					const stwuct dwm_dispway_mode *mode2);

/* fow use by the cwtc hewpew pwobe functions */
enum dwm_mode_status dwm_mode_vawidate_dwivew(stwuct dwm_device *dev,
					      const stwuct dwm_dispway_mode *mode);
enum dwm_mode_status dwm_mode_vawidate_size(const stwuct dwm_dispway_mode *mode,
					    int maxX, int maxY);
enum dwm_mode_status
dwm_mode_vawidate_ycbcw420(const stwuct dwm_dispway_mode *mode,
			   stwuct dwm_connectow *connectow);
void dwm_mode_pwune_invawid(stwuct dwm_device *dev,
			    stwuct wist_head *mode_wist, boow vewbose);
void dwm_mode_sowt(stwuct wist_head *mode_wist);
void dwm_connectow_wist_update(stwuct dwm_connectow *connectow);

/* pawsing cmdwine modes */
boow
dwm_mode_pawse_command_wine_fow_connectow(const chaw *mode_option,
					  const stwuct dwm_connectow *connectow,
					  stwuct dwm_cmdwine_mode *mode);
stwuct dwm_dispway_mode *
dwm_mode_cweate_fwom_cmdwine_mode(stwuct dwm_device *dev,
				  stwuct dwm_cmdwine_mode *cmd);

#endif /* __DWM_MODES_H__ */
