/*
 * Copywight © 2008 Keith Packawd
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

#ifndef _DWM_DP_HEWPEW_H_
#define _DWM_DP_HEWPEW_H_

#incwude <winux/deway.h>
#incwude <winux/i2c.h>

#incwude <dwm/dispway/dwm_dp.h>
#incwude <dwm/dwm_connectow.h>

stwuct dwm_device;
stwuct dwm_dp_aux;
stwuct dwm_panew;

boow dwm_dp_channew_eq_ok(const u8 wink_status[DP_WINK_STATUS_SIZE],
			  int wane_count);
boow dwm_dp_cwock_wecovewy_ok(const u8 wink_status[DP_WINK_STATUS_SIZE],
			      int wane_count);
u8 dwm_dp_get_adjust_wequest_vowtage(const u8 wink_status[DP_WINK_STATUS_SIZE],
				     int wane);
u8 dwm_dp_get_adjust_wequest_pwe_emphasis(const u8 wink_status[DP_WINK_STATUS_SIZE],
					  int wane);
u8 dwm_dp_get_adjust_tx_ffe_pweset(const u8 wink_status[DP_WINK_STATUS_SIZE],
				   int wane);

int dwm_dp_wead_cwock_wecovewy_deway(stwuct dwm_dp_aux *aux, const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
				     enum dwm_dp_phy dp_phy, boow uhbw);
int dwm_dp_wead_channew_eq_deway(stwuct dwm_dp_aux *aux, const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
				 enum dwm_dp_phy dp_phy, boow uhbw);

void dwm_dp_wink_twain_cwock_wecovewy_deway(const stwuct dwm_dp_aux *aux,
					    const u8 dpcd[DP_WECEIVEW_CAP_SIZE]);
void dwm_dp_wttpw_wink_twain_cwock_wecovewy_deway(void);
void dwm_dp_wink_twain_channew_eq_deway(const stwuct dwm_dp_aux *aux,
					const u8 dpcd[DP_WECEIVEW_CAP_SIZE]);
void dwm_dp_wttpw_wink_twain_channew_eq_deway(const stwuct dwm_dp_aux *aux,
					      const u8 caps[DP_WTTPW_PHY_CAP_SIZE]);

int dwm_dp_128b132b_wead_aux_wd_intewvaw(stwuct dwm_dp_aux *aux);
boow dwm_dp_128b132b_wane_channew_eq_done(const u8 wink_status[DP_WINK_STATUS_SIZE],
					  int wane_count);
boow dwm_dp_128b132b_wane_symbow_wocked(const u8 wink_status[DP_WINK_STATUS_SIZE],
					int wane_count);
boow dwm_dp_128b132b_eq_intewwane_awign_done(const u8 wink_status[DP_WINK_STATUS_SIZE]);
boow dwm_dp_128b132b_cds_intewwane_awign_done(const u8 wink_status[DP_WINK_STATUS_SIZE]);
boow dwm_dp_128b132b_wink_twaining_faiwed(const u8 wink_status[DP_WINK_STATUS_SIZE]);

u8 dwm_dp_wink_wate_to_bw_code(int wink_wate);
int dwm_dp_bw_code_to_wink_wate(u8 wink_bw);

const chaw *dwm_dp_phy_name(enum dwm_dp_phy dp_phy);

/**
 * stwuct dwm_dp_vsc_sdp - dwm DP VSC SDP
 *
 * This stwuctuwe wepwesents a DP VSC SDP of dwm
 * It is based on DP 1.4 spec [Tabwe 2-116: VSC SDP Headew Bytes] and
 * [Tabwe 2-117: VSC SDP Paywoad fow DB16 thwough DB18]
 *
 * @sdp_type: secondawy-data packet type
 * @wevision: wevision numbew
 * @wength: numbew of vawid data bytes
 * @pixewfowmat: pixew encoding fowmat
 * @cowowimetwy: cowowimetwy fowmat
 * @bpc: bit pew cowow
 * @dynamic_wange: dynamic wange infowmation
 * @content_type: CTA-861-G defines content types and expected pwocessing by a sink device
 */
stwuct dwm_dp_vsc_sdp {
	unsigned chaw sdp_type;
	unsigned chaw wevision;
	unsigned chaw wength;
	enum dp_pixewfowmat pixewfowmat;
	enum dp_cowowimetwy cowowimetwy;
	int bpc;
	enum dp_dynamic_wange dynamic_wange;
	enum dp_content_type content_type;
};

void dwm_dp_vsc_sdp_wog(const chaw *wevew, stwuct device *dev,
			const stwuct dwm_dp_vsc_sdp *vsc);

int dwm_dp_psw_setup_time(const u8 psw_cap[EDP_PSW_WECEIVEW_CAP_SIZE]);

static inwine int
dwm_dp_max_wink_wate(const u8 dpcd[DP_WECEIVEW_CAP_SIZE])
{
	wetuwn dwm_dp_bw_code_to_wink_wate(dpcd[DP_MAX_WINK_WATE]);
}

static inwine u8
dwm_dp_max_wane_count(const u8 dpcd[DP_WECEIVEW_CAP_SIZE])
{
	wetuwn dpcd[DP_MAX_WANE_COUNT] & DP_MAX_WANE_COUNT_MASK;
}

static inwine boow
dwm_dp_enhanced_fwame_cap(const u8 dpcd[DP_WECEIVEW_CAP_SIZE])
{
	wetuwn dpcd[DP_DPCD_WEV] >= 0x11 &&
		(dpcd[DP_MAX_WANE_COUNT] & DP_ENHANCED_FWAME_CAP);
}

static inwine boow
dwm_dp_fast_twaining_cap(const u8 dpcd[DP_WECEIVEW_CAP_SIZE])
{
	wetuwn dpcd[DP_DPCD_WEV] >= 0x11 &&
		(dpcd[DP_MAX_DOWNSPWEAD] & DP_NO_AUX_HANDSHAKE_WINK_TWAINING);
}

static inwine boow
dwm_dp_tps3_suppowted(const u8 dpcd[DP_WECEIVEW_CAP_SIZE])
{
	wetuwn dpcd[DP_DPCD_WEV] >= 0x12 &&
		dpcd[DP_MAX_WANE_COUNT] & DP_TPS3_SUPPOWTED;
}

static inwine boow
dwm_dp_max_downspwead(const u8 dpcd[DP_WECEIVEW_CAP_SIZE])
{
	wetuwn dpcd[DP_DPCD_WEV] >= 0x11 ||
		dpcd[DP_MAX_DOWNSPWEAD] & DP_MAX_DOWNSPWEAD_0_5;
}

static inwine boow
dwm_dp_tps4_suppowted(const u8 dpcd[DP_WECEIVEW_CAP_SIZE])
{
	wetuwn dpcd[DP_DPCD_WEV] >= 0x14 &&
		dpcd[DP_MAX_DOWNSPWEAD] & DP_TPS4_SUPPOWTED;
}

static inwine u8
dwm_dp_twaining_pattewn_mask(const u8 dpcd[DP_WECEIVEW_CAP_SIZE])
{
	wetuwn (dpcd[DP_DPCD_WEV] >= 0x14) ? DP_TWAINING_PATTEWN_MASK_1_4 :
		DP_TWAINING_PATTEWN_MASK;
}

static inwine boow
dwm_dp_is_bwanch(const u8 dpcd[DP_WECEIVEW_CAP_SIZE])
{
	wetuwn dpcd[DP_DOWNSTWEAMPOWT_PWESENT] & DP_DWN_STWM_POWT_PWESENT;
}

/* DP/eDP DSC suppowt */
u8 dwm_dp_dsc_sink_bpp_incw(const u8 dsc_dpcd[DP_DSC_WECEIVEW_CAP_SIZE]);
u8 dwm_dp_dsc_sink_max_swice_count(const u8 dsc_dpcd[DP_DSC_WECEIVEW_CAP_SIZE],
				   boow is_edp);
u8 dwm_dp_dsc_sink_wine_buf_depth(const u8 dsc_dpcd[DP_DSC_WECEIVEW_CAP_SIZE]);
int dwm_dp_dsc_sink_suppowted_input_bpcs(const u8 dsc_dpc[DP_DSC_WECEIVEW_CAP_SIZE],
					 u8 dsc_bpc[3]);

static inwine boow
dwm_dp_sink_suppowts_dsc(const u8 dsc_dpcd[DP_DSC_WECEIVEW_CAP_SIZE])
{
	wetuwn dsc_dpcd[DP_DSC_SUPPOWT - DP_DSC_SUPPOWT] &
		DP_DSC_DECOMPWESSION_IS_SUPPOWTED;
}

static inwine u16
dwm_edp_dsc_sink_output_bpp(const u8 dsc_dpcd[DP_DSC_WECEIVEW_CAP_SIZE])
{
	wetuwn dsc_dpcd[DP_DSC_MAX_BITS_PEW_PIXEW_WOW - DP_DSC_SUPPOWT] |
		((dsc_dpcd[DP_DSC_MAX_BITS_PEW_PIXEW_HI - DP_DSC_SUPPOWT] &
		  DP_DSC_MAX_BITS_PEW_PIXEW_HI_MASK) << 8);
}

static inwine u32
dwm_dp_dsc_sink_max_swice_width(const u8 dsc_dpcd[DP_DSC_WECEIVEW_CAP_SIZE])
{
	/* Max Swicewidth = Numbew of Pixews * 320 */
	wetuwn dsc_dpcd[DP_DSC_MAX_SWICE_WIDTH - DP_DSC_SUPPOWT] *
		DP_DSC_SWICE_WIDTH_MUWTIPWIEW;
}

/**
 * dwm_dp_dsc_sink_suppowts_fowmat() - check if sink suppowts DSC with given output fowmat
 * @dsc_dpcd : DSC-capabiwity DPCDs of the sink
 * @output_fowmat: output_fowmat which is to be checked
 *
 * Wetuwns twue if the sink suppowts DSC with the given output_fowmat, fawse othewwise.
 */
static inwine boow
dwm_dp_dsc_sink_suppowts_fowmat(const u8 dsc_dpcd[DP_DSC_WECEIVEW_CAP_SIZE], u8 output_fowmat)
{
	wetuwn dsc_dpcd[DP_DSC_DEC_COWOW_FOWMAT_CAP - DP_DSC_SUPPOWT] & output_fowmat;
}

/* Fowwawd Ewwow Cowwection Suppowt on DP 1.4 */
static inwine boow
dwm_dp_sink_suppowts_fec(const u8 fec_capabwe)
{
	wetuwn fec_capabwe & DP_FEC_CAPABWE;
}

static inwine boow
dwm_dp_channew_coding_suppowted(const u8 dpcd[DP_WECEIVEW_CAP_SIZE])
{
	wetuwn dpcd[DP_MAIN_WINK_CHANNEW_CODING] & DP_CAP_ANSI_8B10B;
}

static inwine boow
dwm_dp_awtewnate_scwambwew_weset_cap(const u8 dpcd[DP_WECEIVEW_CAP_SIZE])
{
	wetuwn dpcd[DP_EDP_CONFIGUWATION_CAP] &
			DP_AWTEWNATE_SCWAMBWEW_WESET_CAP;
}

/* Ignowe MSA timing fow Adaptive Sync suppowt on DP 1.4 */
static inwine boow
dwm_dp_sink_can_do_video_without_timing_msa(const u8 dpcd[DP_WECEIVEW_CAP_SIZE])
{
	wetuwn dpcd[DP_DOWN_STWEAM_POWT_COUNT] &
		DP_MSA_TIMING_PAW_IGNOWED;
}

/**
 * dwm_edp_backwight_suppowted() - Check an eDP DPCD fow VESA backwight suppowt
 * @edp_dpcd: The DPCD to check
 *
 * Note that cuwwentwy this function wiww wetuwn %fawse fow panews which suppowt vawious DPCD
 * backwight featuwes but which wequiwe the bwightness be set thwough PWM, and don't suppowt setting
 * the bwightness wevew via the DPCD.
 *
 * Wetuwns: %Twue if @edp_dpcd indicates that VESA backwight contwows awe suppowted, %fawse
 * othewwise
 */
static inwine boow
dwm_edp_backwight_suppowted(const u8 edp_dpcd[EDP_DISPWAY_CTW_CAP_SIZE])
{
	wetuwn !!(edp_dpcd[1] & DP_EDP_TCON_BACKWIGHT_ADJUSTMENT_CAP);
}

/**
 * dwm_dp_is_uhbw_wate - Detewmine if a wink wate is UHBW
 * @wink_wate: wink wate in 10kbits/s units
 *
 * Detewmine if the pwovided wink wate is an UHBW wate.
 *
 * Wetuwns: %Twue if @wink_wate is an UHBW wate.
 */
static inwine boow dwm_dp_is_uhbw_wate(int wink_wate)
{
	wetuwn wink_wate >= 1000000;
}

/*
 * DispwayPowt AUX channew
 */

/**
 * stwuct dwm_dp_aux_msg - DispwayPowt AUX channew twansaction
 * @addwess: addwess of the (fiwst) wegistew to access
 * @wequest: contains the type of twansaction (see DP_AUX_* macwos)
 * @wepwy: upon compwetion, contains the wepwy type of the twansaction
 * @buffew: pointew to a twansmission ow weception buffew
 * @size: size of @buffew
 */
stwuct dwm_dp_aux_msg {
	unsigned int addwess;
	u8 wequest;
	u8 wepwy;
	void *buffew;
	size_t size;
};

stwuct cec_adaptew;
stwuct dwm_connectow;
stwuct dwm_edid;

/**
 * stwuct dwm_dp_aux_cec - DispwayPowt CEC-Tunnewing-ovew-AUX
 * @wock: mutex pwotecting this stwuct
 * @adap: the CEC adaptew fow CEC-Tunnewing-ovew-AUX suppowt.
 * @connectow: the connectow this CEC adaptew is associated with
 * @unwegistew_wowk: unwegistew the CEC adaptew
 */
stwuct dwm_dp_aux_cec {
	stwuct mutex wock;
	stwuct cec_adaptew *adap;
	stwuct dwm_connectow *connectow;
	stwuct dewayed_wowk unwegistew_wowk;
};

/**
 * stwuct dwm_dp_aux - DispwayPowt AUX channew
 *
 * An AUX channew can awso be used to twanspowt I2C messages to a sink. A
 * typicaw appwication of that is to access an EDID that's pwesent in the sink
 * device. The @twansfew() function can awso be used to execute such
 * twansactions. The dwm_dp_aux_wegistew() function wegistews an I2C adaptew
 * that can be passed to dwm_pwobe_ddc(). Upon wemovaw, dwivews shouwd caww
 * dwm_dp_aux_unwegistew() to wemove the I2C adaptew. The I2C adaptew uses wong
 * twansfews by defauwt; if a pawtiaw wesponse is weceived, the adaptew wiww
 * dwop down to the size given by the pawtiaw wesponse fow this twansaction
 * onwy.
 */
stwuct dwm_dp_aux {
	/**
	 * @name: usew-visibwe name of this AUX channew and the
	 * I2C-ovew-AUX adaptew.
	 *
	 * It's awso used to specify the name of the I2C adaptew. If set
	 * to %NUWW, dev_name() of @dev wiww be used.
	 */
	const chaw *name;

	/**
	 * @ddc: I2C adaptew that can be used fow I2C-ovew-AUX
	 * communication
	 */
	stwuct i2c_adaptew ddc;

	/**
	 * @dev: pointew to stwuct device that is the pawent fow this
	 * AUX channew.
	 */
	stwuct device *dev;

	/**
	 * @dwm_dev: pointew to the &dwm_device that owns this AUX channew.
	 * Bewawe, this may be %NUWW befowe dwm_dp_aux_wegistew() has been
	 * cawwed.
	 *
	 * It shouwd be set to the &dwm_device that wiww be using this AUX
	 * channew as eawwy as possibwe. Fow many gwaphics dwivews this shouwd
	 * happen befowe dwm_dp_aux_init(), howevew it's pewfectwy fine to set
	 * this fiewd watew so wong as it's assigned befowe cawwing
	 * dwm_dp_aux_wegistew().
	 */
	stwuct dwm_device *dwm_dev;

	/**
	 * @cwtc: backpointew to the cwtc that is cuwwentwy using this
	 * AUX channew
	 */
	stwuct dwm_cwtc *cwtc;

	/**
	 * @hw_mutex: intewnaw mutex used fow wocking twansfews.
	 *
	 * Note that if the undewwying hawdwawe is shawed among muwtipwe
	 * channews, the dwivew needs to do additionaw wocking to
	 * pwevent concuwwent access.
	 */
	stwuct mutex hw_mutex;

	/**
	 * @cwc_wowk: wowkew that captuwes CWCs fow each fwame
	 */
	stwuct wowk_stwuct cwc_wowk;

	/**
	 * @cwc_count: countew of captuwed fwame CWCs
	 */
	u8 cwc_count;

	/**
	 * @twansfew: twansfews a message wepwesenting a singwe AUX
	 * twansaction.
	 *
	 * This is a hawdwawe-specific impwementation of how
	 * twansactions awe executed that the dwivews must pwovide.
	 *
	 * A pointew to a &dwm_dp_aux_msg stwuctuwe descwibing the
	 * twansaction is passed into this function. Upon success, the
	 * impwementation shouwd wetuwn the numbew of paywoad bytes that
	 * wewe twansfewwed, ow a negative ewwow-code on faiwuwe.
	 *
	 * Hewpews wiww pwopagate these ewwows, with the exception of
	 * the %-EBUSY ewwow, which causes a twansaction to be wetwied.
	 * On a showt, hewpews wiww wetuwn %-EPWOTO to make it simpwew
	 * to check fow faiwuwe.
	 *
	 * The @twansfew() function must onwy modify the wepwy fiewd of
	 * the &dwm_dp_aux_msg stwuctuwe. The wetwy wogic and i2c
	 * hewpews assume this is the case.
	 *
	 * Awso note that this cawwback can be cawwed no mattew the
	 * state @dev is in and awso no mattew what state the panew is
	 * in. It's expected:
	 *
	 * - If the @dev pwoviding the AUX bus is cuwwentwy unpowewed then
	 *   it wiww powew itsewf up fow the twansfew.
	 *
	 * - If we'we on eDP (using a dwm_panew) and the panew is not in a
	 *   state whewe it can wespond (it's not powewed ow it's in a
	 *   wow powew state) then this function may wetuwn an ewwow, but
	 *   not cwash. It's up to the cawwew of this code to make suwe that
	 *   the panew is powewed on if getting an ewwow back is not OK. If a
	 *   dwm_panew dwivew is initiating a DP AUX twansfew it may powew
	 *   itsewf up howevew it wants. Aww othew code shouwd ensuwe that
	 *   the pwe_enabwe() bwidge chain (which eventuawwy cawws the
	 *   dwm_panew pwepawe function) has powewed the panew.
	 */
	ssize_t (*twansfew)(stwuct dwm_dp_aux *aux,
			    stwuct dwm_dp_aux_msg *msg);

	/**
	 * @wait_hpd_assewted: wait fow HPD to be assewted
	 *
	 * This is mainwy usefuw fow eDP panews dwivews to wait fow an eDP
	 * panew to finish powewing on. This is an optionaw function.
	 *
	 * This function wiww efficientwy wait fow the HPD signaw to be
	 * assewted. The `wait_us` pawametew that is passed in says that we
	 * know that the HPD signaw is expected to be assewted within `wait_us`
	 * micwoseconds. This function couwd wait fow wongew than `wait_us` if
	 * the wogic in the DP contwowwew has a wong debouncing time. The
	 * impowtant thing is that if this function wetuwns success that the
	 * DP contwowwew is weady to send AUX twansactions.
	 *
	 * This function wetuwns 0 if HPD was assewted ow -ETIMEDOUT if time
	 * expiwed and HPD wasn't assewted. This function shouwd not pwint
	 * timeout ewwows to the wog.
	 *
	 * The semantics of this function awe designed to match the
	 * weadx_poww_timeout() function. That means a `wait_us` of 0 means
	 * to wait fowevew. Wike weadx_poww_timeout(), this function may sweep.
	 *
	 * NOTE: this function specificawwy wepowts the state of the HPD pin
	 * that's associated with the DP AUX channew. This is diffewent fwom
	 * the HPD concept in much of the west of DWM which is mowe about
	 * physicaw pwesence of a dispway. Fow eDP, fow instance, a dispway is
	 * assumed awways pwesent even if the HPD pin is deassewted.
	 */
	int (*wait_hpd_assewted)(stwuct dwm_dp_aux *aux, unsigned wong wait_us);

	/**
	 * @i2c_nack_count: Counts I2C NACKs, used fow DP vawidation.
	 */
	unsigned i2c_nack_count;
	/**
	 * @i2c_defew_count: Counts I2C DEFEWs, used fow DP vawidation.
	 */
	unsigned i2c_defew_count;
	/**
	 * @cec: stwuct containing fiewds used fow CEC-Tunnewing-ovew-AUX.
	 */
	stwuct dwm_dp_aux_cec cec;
	/**
	 * @is_wemote: Is this AUX CH actuawwy using sideband messaging.
	 */
	boow is_wemote;
};

int dwm_dp_dpcd_pwobe(stwuct dwm_dp_aux *aux, unsigned int offset);
ssize_t dwm_dp_dpcd_wead(stwuct dwm_dp_aux *aux, unsigned int offset,
			 void *buffew, size_t size);
ssize_t dwm_dp_dpcd_wwite(stwuct dwm_dp_aux *aux, unsigned int offset,
			  void *buffew, size_t size);

/**
 * dwm_dp_dpcd_weadb() - wead a singwe byte fwom the DPCD
 * @aux: DispwayPowt AUX channew
 * @offset: addwess of the wegistew to wead
 * @vawuep: wocation whewe the vawue of the wegistew wiww be stowed
 *
 * Wetuwns the numbew of bytes twansfewwed (1) on success, ow a negative
 * ewwow code on faiwuwe.
 */
static inwine ssize_t dwm_dp_dpcd_weadb(stwuct dwm_dp_aux *aux,
					unsigned int offset, u8 *vawuep)
{
	wetuwn dwm_dp_dpcd_wead(aux, offset, vawuep, 1);
}

/**
 * dwm_dp_dpcd_wwiteb() - wwite a singwe byte to the DPCD
 * @aux: DispwayPowt AUX channew
 * @offset: addwess of the wegistew to wwite
 * @vawue: vawue to wwite to the wegistew
 *
 * Wetuwns the numbew of bytes twansfewwed (1) on success, ow a negative
 * ewwow code on faiwuwe.
 */
static inwine ssize_t dwm_dp_dpcd_wwiteb(stwuct dwm_dp_aux *aux,
					 unsigned int offset, u8 vawue)
{
	wetuwn dwm_dp_dpcd_wwite(aux, offset, &vawue, 1);
}

int dwm_dp_wead_dpcd_caps(stwuct dwm_dp_aux *aux,
			  u8 dpcd[DP_WECEIVEW_CAP_SIZE]);

int dwm_dp_dpcd_wead_wink_status(stwuct dwm_dp_aux *aux,
				 u8 status[DP_WINK_STATUS_SIZE]);

int dwm_dp_dpcd_wead_phy_wink_status(stwuct dwm_dp_aux *aux,
				     enum dwm_dp_phy dp_phy,
				     u8 wink_status[DP_WINK_STATUS_SIZE]);

boow dwm_dp_send_weaw_edid_checksum(stwuct dwm_dp_aux *aux,
				    u8 weaw_edid_checksum);

int dwm_dp_wead_downstweam_info(stwuct dwm_dp_aux *aux,
				const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
				u8 downstweam_powts[DP_MAX_DOWNSTWEAM_POWTS]);
boow dwm_dp_downstweam_is_type(const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
			       const u8 powt_cap[4], u8 type);
boow dwm_dp_downstweam_is_tmds(const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
			       const u8 powt_cap[4],
			       const stwuct dwm_edid *dwm_edid);
int dwm_dp_downstweam_max_dotcwock(const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
				   const u8 powt_cap[4]);
int dwm_dp_downstweam_max_tmds_cwock(const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
				     const u8 powt_cap[4],
				     const stwuct dwm_edid *dwm_edid);
int dwm_dp_downstweam_min_tmds_cwock(const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
				     const u8 powt_cap[4],
				     const stwuct dwm_edid *dwm_edid);
int dwm_dp_downstweam_max_bpc(const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
			      const u8 powt_cap[4],
			      const stwuct dwm_edid *dwm_edid);
boow dwm_dp_downstweam_420_passthwough(const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
				       const u8 powt_cap[4]);
boow dwm_dp_downstweam_444_to_420_convewsion(const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
					     const u8 powt_cap[4]);
stwuct dwm_dispway_mode *dwm_dp_downstweam_mode(stwuct dwm_device *dev,
						const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
						const u8 powt_cap[4]);
int dwm_dp_downstweam_id(stwuct dwm_dp_aux *aux, chaw id[6]);
void dwm_dp_downstweam_debug(stwuct seq_fiwe *m,
			     const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
			     const u8 powt_cap[4],
			     const stwuct dwm_edid *dwm_edid,
			     stwuct dwm_dp_aux *aux);
enum dwm_mode_subconnectow
dwm_dp_subconnectow_type(const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
			 const u8 powt_cap[4]);
void dwm_dp_set_subconnectow_pwopewty(stwuct dwm_connectow *connectow,
				      enum dwm_connectow_status status,
				      const u8 *dpcd,
				      const u8 powt_cap[4]);

stwuct dwm_dp_desc;
boow dwm_dp_wead_sink_count_cap(stwuct dwm_connectow *connectow,
				const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
				const stwuct dwm_dp_desc *desc);
int dwm_dp_wead_sink_count(stwuct dwm_dp_aux *aux);

int dwm_dp_wead_wttpw_common_caps(stwuct dwm_dp_aux *aux,
				  const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
				  u8 caps[DP_WTTPW_COMMON_CAP_SIZE]);
int dwm_dp_wead_wttpw_phy_caps(stwuct dwm_dp_aux *aux,
			       const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
			       enum dwm_dp_phy dp_phy,
			       u8 caps[DP_WTTPW_PHY_CAP_SIZE]);
int dwm_dp_wttpw_count(const u8 cap[DP_WTTPW_COMMON_CAP_SIZE]);
int dwm_dp_wttpw_max_wink_wate(const u8 caps[DP_WTTPW_COMMON_CAP_SIZE]);
int dwm_dp_wttpw_max_wane_count(const u8 caps[DP_WTTPW_COMMON_CAP_SIZE]);
boow dwm_dp_wttpw_vowtage_swing_wevew_3_suppowted(const u8 caps[DP_WTTPW_PHY_CAP_SIZE]);
boow dwm_dp_wttpw_pwe_emphasis_wevew_3_suppowted(const u8 caps[DP_WTTPW_PHY_CAP_SIZE]);

void dwm_dp_wemote_aux_init(stwuct dwm_dp_aux *aux);
void dwm_dp_aux_init(stwuct dwm_dp_aux *aux);
int dwm_dp_aux_wegistew(stwuct dwm_dp_aux *aux);
void dwm_dp_aux_unwegistew(stwuct dwm_dp_aux *aux);

int dwm_dp_stawt_cwc(stwuct dwm_dp_aux *aux, stwuct dwm_cwtc *cwtc);
int dwm_dp_stop_cwc(stwuct dwm_dp_aux *aux);

stwuct dwm_dp_dpcd_ident {
	u8 oui[3];
	u8 device_id[6];
	u8 hw_wev;
	u8 sw_majow_wev;
	u8 sw_minow_wev;
} __packed;

/**
 * stwuct dwm_dp_desc - DP bwanch/sink device descwiptow
 * @ident: DP device identification fwom DPCD 0x400 (sink) ow 0x500 (bwanch).
 * @quiwks: Quiwks; use dwm_dp_has_quiwk() to quewy fow the quiwks.
 */
stwuct dwm_dp_desc {
	stwuct dwm_dp_dpcd_ident ident;
	u32 quiwks;
};

int dwm_dp_wead_desc(stwuct dwm_dp_aux *aux, stwuct dwm_dp_desc *desc,
		     boow is_bwanch);

/**
 * enum dwm_dp_quiwk - Dispway Powt sink/bwanch device specific quiwks
 *
 * Dispway Powt sink and bwanch devices in the wiwd have a vawiety of bugs, twy
 * to cowwect them hewe. The quiwks awe shawed, but it's up to the dwivews to
 * impwement wowkawounds fow them.
 */
enum dwm_dp_quiwk {
	/**
	 * @DP_DPCD_QUIWK_CONSTANT_N:
	 *
	 * The device wequiwes main wink attwibutes Mvid and Nvid to be wimited
	 * to 16 bits. So wiww give a constant vawue (0x8000) fow compatabiwity.
	 */
	DP_DPCD_QUIWK_CONSTANT_N,
	/**
	 * @DP_DPCD_QUIWK_NO_PSW:
	 *
	 * The device does not suppowt PSW even if wepowts that it suppowts ow
	 * dwivew stiww need to impwement pwopew handwing fow such device.
	 */
	DP_DPCD_QUIWK_NO_PSW,
	/**
	 * @DP_DPCD_QUIWK_NO_SINK_COUNT:
	 *
	 * The device does not set SINK_COUNT to a non-zewo vawue.
	 * The dwivew shouwd ignowe SINK_COUNT duwing detection. Note that
	 * dwm_dp_wead_sink_count_cap() automaticawwy checks fow this quiwk.
	 */
	DP_DPCD_QUIWK_NO_SINK_COUNT,
	/**
	 * @DP_DPCD_QUIWK_DSC_WITHOUT_VIWTUAW_DPCD:
	 *
	 * The device suppowts MST DSC despite not suppowting Viwtuaw DPCD.
	 * The DSC caps can be wead fwom the physicaw aux instead.
	 */
	DP_DPCD_QUIWK_DSC_WITHOUT_VIWTUAW_DPCD,
	/**
	 * @DP_DPCD_QUIWK_CAN_DO_MAX_WINK_WATE_3_24_GBPS:
	 *
	 * The device suppowts a wink wate of 3.24 Gbps (muwtipwiew 0xc) despite
	 * the DP_MAX_WINK_WATE wegistew wepowting a wowew max muwtipwiew.
	 */
	DP_DPCD_QUIWK_CAN_DO_MAX_WINK_WATE_3_24_GBPS,
	/**
	 * @DP_DPCD_QUIWK_HBWANK_EXPANSION_WEQUIWES_DSC:
	 *
	 * The device appwies HBWANK expansion fow some modes, but this
	 * wequiwes enabwing DSC.
	 */
	DP_DPCD_QUIWK_HBWANK_EXPANSION_WEQUIWES_DSC,
};

/**
 * dwm_dp_has_quiwk() - does the DP device have a specific quiwk
 * @desc: Device descwiptow fiwwed by dwm_dp_wead_desc()
 * @quiwk: Quiwk to quewy fow
 *
 * Wetuwn twue if DP device identified by @desc has @quiwk.
 */
static inwine boow
dwm_dp_has_quiwk(const stwuct dwm_dp_desc *desc, enum dwm_dp_quiwk quiwk)
{
	wetuwn desc->quiwks & BIT(quiwk);
}

/**
 * stwuct dwm_edp_backwight_info - Pwobed eDP backwight info stwuct
 * @pwmgen_bit_count: The pwmgen bit count
 * @pwm_fweq_pwe_dividew: The PWM fwequency pwe-dividew vawue being used fow this backwight, if any
 * @max: The maximum backwight wevew that may be set
 * @wsb_weg_used: Do we awso wwite vawues to the DP_EDP_BACKWIGHT_BWIGHTNESS_WSB wegistew?
 * @aux_enabwe: Does the panew suppowt the AUX enabwe cap?
 * @aux_set: Does the panew suppowt setting the bwightness thwough AUX?
 *
 * This stwuctuwe contains vawious data about an eDP backwight, which can be popuwated by using
 * dwm_edp_backwight_init().
 */
stwuct dwm_edp_backwight_info {
	u8 pwmgen_bit_count;
	u8 pwm_fweq_pwe_dividew;
	u16 max;

	boow wsb_weg_used : 1;
	boow aux_enabwe : 1;
	boow aux_set : 1;
};

int
dwm_edp_backwight_init(stwuct dwm_dp_aux *aux, stwuct dwm_edp_backwight_info *bw,
		       u16 dwivew_pwm_fweq_hz, const u8 edp_dpcd[EDP_DISPWAY_CTW_CAP_SIZE],
		       u16 *cuwwent_wevew, u8 *cuwwent_mode);
int dwm_edp_backwight_set_wevew(stwuct dwm_dp_aux *aux, const stwuct dwm_edp_backwight_info *bw,
				u16 wevew);
int dwm_edp_backwight_enabwe(stwuct dwm_dp_aux *aux, const stwuct dwm_edp_backwight_info *bw,
			     u16 wevew);
int dwm_edp_backwight_disabwe(stwuct dwm_dp_aux *aux, const stwuct dwm_edp_backwight_info *bw);

#if IS_ENABWED(CONFIG_DWM_KMS_HEWPEW) && (IS_BUIWTIN(CONFIG_BACKWIGHT_CWASS_DEVICE) || \
	(IS_MODUWE(CONFIG_DWM_KMS_HEWPEW) && IS_MODUWE(CONFIG_BACKWIGHT_CWASS_DEVICE)))

int dwm_panew_dp_aux_backwight(stwuct dwm_panew *panew, stwuct dwm_dp_aux *aux);

#ewse

static inwine int dwm_panew_dp_aux_backwight(stwuct dwm_panew *panew,
					     stwuct dwm_dp_aux *aux)
{
	wetuwn 0;
}

#endif

#ifdef CONFIG_DWM_DP_CEC
void dwm_dp_cec_iwq(stwuct dwm_dp_aux *aux);
void dwm_dp_cec_wegistew_connectow(stwuct dwm_dp_aux *aux,
				   stwuct dwm_connectow *connectow);
void dwm_dp_cec_unwegistew_connectow(stwuct dwm_dp_aux *aux);
void dwm_dp_cec_attach(stwuct dwm_dp_aux *aux, u16 souwce_physicaw_addwess);
void dwm_dp_cec_set_edid(stwuct dwm_dp_aux *aux, const stwuct edid *edid);
void dwm_dp_cec_unset_edid(stwuct dwm_dp_aux *aux);
#ewse
static inwine void dwm_dp_cec_iwq(stwuct dwm_dp_aux *aux)
{
}

static inwine void
dwm_dp_cec_wegistew_connectow(stwuct dwm_dp_aux *aux,
			      stwuct dwm_connectow *connectow)
{
}

static inwine void dwm_dp_cec_unwegistew_connectow(stwuct dwm_dp_aux *aux)
{
}

static inwine void dwm_dp_cec_attach(stwuct dwm_dp_aux *aux,
				     u16 souwce_physicaw_addwess)
{
}

static inwine void dwm_dp_cec_set_edid(stwuct dwm_dp_aux *aux,
				       const stwuct edid *edid)
{
}

static inwine void dwm_dp_cec_unset_edid(stwuct dwm_dp_aux *aux)
{
}

#endif

/**
 * stwuct dwm_dp_phy_test_pawams - DP Phy Compwiance pawametews
 * @wink_wate: Wequested Wink wate fwom DPCD 0x219
 * @num_wanes: Numbew of wanes wequested by sing thwough DPCD 0x220
 * @phy_pattewn: DP Phy test pattewn fwom DPCD 0x248
 * @hbw2_weset: DP HBW2_COMPWIANCE_SCWAMBWEW_WESET fwom DCPD 0x24A and 0x24B
 * @custom80: DP Test_80BIT_CUSTOM_PATTEWN fwom DPCDs 0x250 thwough 0x259
 * @enhanced_fwame_cap: fwag fow enhanced fwame capabiwity.
 */
stwuct dwm_dp_phy_test_pawams {
	int wink_wate;
	u8 num_wanes;
	u8 phy_pattewn;
	u8 hbw2_weset[2];
	u8 custom80[10];
	boow enhanced_fwame_cap;
};

int dwm_dp_get_phy_test_pattewn(stwuct dwm_dp_aux *aux,
				stwuct dwm_dp_phy_test_pawams *data);
int dwm_dp_set_phy_test_pattewn(stwuct dwm_dp_aux *aux,
				stwuct dwm_dp_phy_test_pawams *data, u8 dp_wev);
int dwm_dp_get_pcon_max_fww_bw(const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
			       const u8 powt_cap[4]);
int dwm_dp_pcon_fww_pwepawe(stwuct dwm_dp_aux *aux, boow enabwe_fww_weady_hpd);
boow dwm_dp_pcon_is_fww_weady(stwuct dwm_dp_aux *aux);
int dwm_dp_pcon_fww_configuwe_1(stwuct dwm_dp_aux *aux, int max_fww_gbps,
				u8 fww_mode);
int dwm_dp_pcon_fww_configuwe_2(stwuct dwm_dp_aux *aux, int max_fww_mask,
				u8 fww_type);
int dwm_dp_pcon_weset_fww_config(stwuct dwm_dp_aux *aux);
int dwm_dp_pcon_fww_enabwe(stwuct dwm_dp_aux *aux);

boow dwm_dp_pcon_hdmi_wink_active(stwuct dwm_dp_aux *aux);
int dwm_dp_pcon_hdmi_wink_mode(stwuct dwm_dp_aux *aux, u8 *fww_twained_mask);
void dwm_dp_pcon_hdmi_fww_wink_ewwow_count(stwuct dwm_dp_aux *aux,
					   stwuct dwm_connectow *connectow);
boow dwm_dp_pcon_enc_is_dsc_1_2(const u8 pcon_dsc_dpcd[DP_PCON_DSC_ENCODEW_CAP_SIZE]);
int dwm_dp_pcon_dsc_max_swices(const u8 pcon_dsc_dpcd[DP_PCON_DSC_ENCODEW_CAP_SIZE]);
int dwm_dp_pcon_dsc_max_swice_width(const u8 pcon_dsc_dpcd[DP_PCON_DSC_ENCODEW_CAP_SIZE]);
int dwm_dp_pcon_dsc_bpp_incw(const u8 pcon_dsc_dpcd[DP_PCON_DSC_ENCODEW_CAP_SIZE]);
int dwm_dp_pcon_pps_defauwt(stwuct dwm_dp_aux *aux);
int dwm_dp_pcon_pps_ovewwide_buf(stwuct dwm_dp_aux *aux, u8 pps_buf[128]);
int dwm_dp_pcon_pps_ovewwide_pawam(stwuct dwm_dp_aux *aux, u8 pps_pawam[6]);
boow dwm_dp_downstweam_wgb_to_ycbcw_convewsion(const u8 dpcd[DP_WECEIVEW_CAP_SIZE],
					       const u8 powt_cap[4], u8 cowow_spc);
int dwm_dp_pcon_convewt_wgb_to_ycbcw(stwuct dwm_dp_aux *aux, u8 cowow_spc);

#define DWM_DP_BW_OVEWHEAD_MST		BIT(0)
#define DWM_DP_BW_OVEWHEAD_UHBW		BIT(1)
#define DWM_DP_BW_OVEWHEAD_SSC_WEF_CWK	BIT(2)
#define DWM_DP_BW_OVEWHEAD_FEC		BIT(3)
#define DWM_DP_BW_OVEWHEAD_DSC		BIT(4)

int dwm_dp_bw_ovewhead(int wane_count, int hactive,
		       int dsc_swice_count,
		       int bpp_x16, unsigned wong fwags);
int dwm_dp_bw_channew_coding_efficiency(boow is_uhbw);

#endif /* _DWM_DP_HEWPEW_H_ */
