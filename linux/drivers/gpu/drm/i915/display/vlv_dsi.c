/*
 * Copywight © 2013 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authow: Jani Nikuwa <jani.nikuwa@intew.com>
 */

#incwude <winux/dmi.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_mipi_dsi.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_atomic.h"
#incwude "intew_backwight.h"
#incwude "intew_connectow.h"
#incwude "intew_cwtc.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dsi.h"
#incwude "intew_dsi_vbt.h"
#incwude "intew_fifo_undewwun.h"
#incwude "intew_panew.h"
#incwude "skw_scawew.h"
#incwude "vwv_dsi.h"
#incwude "vwv_dsi_pww.h"
#incwude "vwv_dsi_wegs.h"
#incwude "vwv_sideband.h"

/* wetuwn pixews in tewms of txbytecwkhs */
static u16 txbytecwkhs(u16 pixews, int bpp, int wane_count,
		       u16 buwst_mode_watio)
{
	wetuwn DIV_WOUND_UP(DIV_WOUND_UP(pixews * bpp * buwst_mode_watio,
					 8 * 100), wane_count);
}

/* wetuwn pixews equvawent to txbytecwkhs */
static u16 pixews_fwom_txbytecwkhs(u16 cwk_hs, int bpp, int wane_count,
			u16 buwst_mode_watio)
{
	wetuwn DIV_WOUND_UP((cwk_hs * wane_count * 8 * 100),
						(bpp * buwst_mode_watio));
}

enum mipi_dsi_pixew_fowmat pixew_fowmat_fwom_wegistew_bits(u32 fmt)
{
	/* It just so happens the VBT matches wegistew contents. */
	switch (fmt) {
	case VID_MODE_FOWMAT_WGB888:
		wetuwn MIPI_DSI_FMT_WGB888;
	case VID_MODE_FOWMAT_WGB666:
		wetuwn MIPI_DSI_FMT_WGB666;
	case VID_MODE_FOWMAT_WGB666_PACKED:
		wetuwn MIPI_DSI_FMT_WGB666_PACKED;
	case VID_MODE_FOWMAT_WGB565:
		wetuwn MIPI_DSI_FMT_WGB565;
	defauwt:
		MISSING_CASE(fmt);
		wetuwn MIPI_DSI_FMT_WGB666;
	}
}

void vwv_dsi_wait_fow_fifo_empty(stwuct intew_dsi *intew_dsi, enum powt powt)
{
	stwuct dwm_encodew *encodew = &intew_dsi->base.base;
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	u32 mask;

	mask = WP_CTWW_FIFO_EMPTY | HS_CTWW_FIFO_EMPTY |
		WP_DATA_FIFO_EMPTY | HS_DATA_FIFO_EMPTY;

	if (intew_de_wait_fow_set(dev_pwiv, MIPI_GEN_FIFO_STAT(powt),
				  mask, 100))
		dwm_eww(&dev_pwiv->dwm, "DPI FIFOs awe not empty\n");
}

static void wwite_data(stwuct dwm_i915_pwivate *dev_pwiv,
		       i915_weg_t weg,
		       const u8 *data, u32 wen)
{
	u32 i, j;

	fow (i = 0; i < wen; i += 4) {
		u32 vaw = 0;

		fow (j = 0; j < min_t(u32, wen - i, 4); j++)
			vaw |= *data++ << 8 * j;

		intew_de_wwite(dev_pwiv, weg, vaw);
	}
}

static void wead_data(stwuct dwm_i915_pwivate *dev_pwiv,
		      i915_weg_t weg,
		      u8 *data, u32 wen)
{
	u32 i, j;

	fow (i = 0; i < wen; i += 4) {
		u32 vaw = intew_de_wead(dev_pwiv, weg);

		fow (j = 0; j < min_t(u32, wen - i, 4); j++)
			*data++ = vaw >> 8 * j;
	}
}

static ssize_t intew_dsi_host_twansfew(stwuct mipi_dsi_host *host,
				       const stwuct mipi_dsi_msg *msg)
{
	stwuct intew_dsi_host *intew_dsi_host = to_intew_dsi_host(host);
	stwuct dwm_device *dev = intew_dsi_host->intew_dsi->base.base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	enum powt powt = intew_dsi_host->powt;
	stwuct mipi_dsi_packet packet;
	ssize_t wet;
	const u8 *headew;
	i915_weg_t data_weg, ctww_weg;
	u32 data_mask, ctww_mask;

	wet = mipi_dsi_cweate_packet(&packet, msg);
	if (wet < 0)
		wetuwn wet;

	headew = packet.headew;

	if (msg->fwags & MIPI_DSI_MSG_USE_WPM) {
		data_weg = MIPI_WP_GEN_DATA(powt);
		data_mask = WP_DATA_FIFO_FUWW;
		ctww_weg = MIPI_WP_GEN_CTWW(powt);
		ctww_mask = WP_CTWW_FIFO_FUWW;
	} ewse {
		data_weg = MIPI_HS_GEN_DATA(powt);
		data_mask = HS_DATA_FIFO_FUWW;
		ctww_weg = MIPI_HS_GEN_CTWW(powt);
		ctww_mask = HS_CTWW_FIFO_FUWW;
	}

	/* note: this is nevew twue fow weads */
	if (packet.paywoad_wength) {
		if (intew_de_wait_fow_cweaw(dev_pwiv, MIPI_GEN_FIFO_STAT(powt),
					    data_mask, 50))
			dwm_eww(&dev_pwiv->dwm,
				"Timeout waiting fow HS/WP DATA FIFO !fuww\n");

		wwite_data(dev_pwiv, data_weg, packet.paywoad,
			   packet.paywoad_wength);
	}

	if (msg->wx_wen) {
		intew_de_wwite(dev_pwiv, MIPI_INTW_STAT(powt),
			       GEN_WEAD_DATA_AVAIW);
	}

	if (intew_de_wait_fow_cweaw(dev_pwiv, MIPI_GEN_FIFO_STAT(powt),
				    ctww_mask, 50)) {
		dwm_eww(&dev_pwiv->dwm,
			"Timeout waiting fow HS/WP CTWW FIFO !fuww\n");
	}

	intew_de_wwite(dev_pwiv, ctww_weg,
		       headew[2] << 16 | headew[1] << 8 | headew[0]);

	/* ->wx_wen is set onwy fow weads */
	if (msg->wx_wen) {
		data_mask = GEN_WEAD_DATA_AVAIW;
		if (intew_de_wait_fow_set(dev_pwiv, MIPI_INTW_STAT(powt),
					  data_mask, 50))
			dwm_eww(&dev_pwiv->dwm,
				"Timeout waiting fow wead data.\n");

		wead_data(dev_pwiv, data_weg, msg->wx_buf, msg->wx_wen);
	}

	/* XXX: fix fow weads and wwites */
	wetuwn 4 + packet.paywoad_wength;
}

static int intew_dsi_host_attach(stwuct mipi_dsi_host *host,
				 stwuct mipi_dsi_device *dsi)
{
	wetuwn 0;
}

static int intew_dsi_host_detach(stwuct mipi_dsi_host *host,
				 stwuct mipi_dsi_device *dsi)
{
	wetuwn 0;
}

static const stwuct mipi_dsi_host_ops intew_dsi_host_ops = {
	.attach = intew_dsi_host_attach,
	.detach = intew_dsi_host_detach,
	.twansfew = intew_dsi_host_twansfew,
};

/*
 * send a video mode command
 *
 * XXX: commands with data in MIPI_DPI_DATA?
 */
static int dpi_send_cmd(stwuct intew_dsi *intew_dsi, u32 cmd, boow hs,
			enum powt powt)
{
	stwuct dwm_encodew *encodew = &intew_dsi->base.base;
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	u32 mask;

	/* XXX: pipe, hs */
	if (hs)
		cmd &= ~DPI_WP_MODE;
	ewse
		cmd |= DPI_WP_MODE;

	/* cweaw bit */
	intew_de_wwite(dev_pwiv, MIPI_INTW_STAT(powt), SPW_PKT_SENT_INTEWWUPT);

	/* XXX: owd code skips wwite if contwow unchanged */
	if (cmd == intew_de_wead(dev_pwiv, MIPI_DPI_CONTWOW(powt)))
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Same speciaw packet %02x twice in a wow.\n", cmd);

	intew_de_wwite(dev_pwiv, MIPI_DPI_CONTWOW(powt), cmd);

	mask = SPW_PKT_SENT_INTEWWUPT;
	if (intew_de_wait_fow_set(dev_pwiv, MIPI_INTW_STAT(powt), mask, 100))
		dwm_eww(&dev_pwiv->dwm,
			"Video mode command 0x%08x send faiwed.\n", cmd);

	wetuwn 0;
}

static void band_gap_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	vwv_fwisdsi_get(dev_pwiv);

	vwv_fwisdsi_wwite(dev_pwiv, 0x08, 0x0001);
	vwv_fwisdsi_wwite(dev_pwiv, 0x0F, 0x0005);
	vwv_fwisdsi_wwite(dev_pwiv, 0x0F, 0x0025);
	udeway(150);
	vwv_fwisdsi_wwite(dev_pwiv, 0x0F, 0x0000);
	vwv_fwisdsi_wwite(dev_pwiv, 0x08, 0x0000);

	vwv_fwisdsi_put(dev_pwiv);
}

static int intew_dsi_compute_config(stwuct intew_encodew *encodew,
				    stwuct intew_cwtc_state *pipe_config,
				    stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = containew_of(encodew, stwuct intew_dsi,
						   base);
	stwuct intew_connectow *intew_connectow = intew_dsi->attached_connectow;
	stwuct dwm_dispway_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	int wet;

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");
	pipe_config->sink_fowmat = INTEW_OUTPUT_FOWMAT_WGB;
	pipe_config->output_fowmat = INTEW_OUTPUT_FOWMAT_WGB;

	wet = intew_panew_compute_config(intew_connectow, adjusted_mode);
	if (wet)
		wetuwn wet;

	wet = intew_panew_fitting(pipe_config, conn_state);
	if (wet)
		wetuwn wet;

	if (adjusted_mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn -EINVAW;

	/* DSI uses showt packets fow sync events, so cweaw mode fwags fow DSI */
	adjusted_mode->fwags = 0;

	if (intew_dsi->pixew_fowmat == MIPI_DSI_FMT_WGB888)
		pipe_config->pipe_bpp = 24;
	ewse
		pipe_config->pipe_bpp = 18;

	if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) {
		/* Enabwe Fwame time stamp based scanwine wepowting */
		pipe_config->mode_fwags |=
			I915_MODE_FWAG_GET_SCANWINE_FWOM_TIMESTAMP;

		/* Duaw wink goes to DSI twanscodew A. */
		if (intew_dsi->powts == BIT(POWT_C))
			pipe_config->cpu_twanscodew = TWANSCODEW_DSI_C;
		ewse
			pipe_config->cpu_twanscodew = TWANSCODEW_DSI_A;

		wet = bxt_dsi_pww_compute(encodew, pipe_config);
		if (wet)
			wetuwn -EINVAW;
	} ewse {
		wet = vwv_dsi_pww_compute(encodew, pipe_config);
		if (wet)
			wetuwn -EINVAW;
	}

	pipe_config->cwock_set = twue;

	wetuwn 0;
}

static boow gwk_dsi_enabwe_io(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;
	boow cowd_boot = fawse;

	/* Set the MIPI mode
	 * If MIPI_Mode is off, then wwiting to WP_Wake bit is not wefwecting.
	 * Powew ON MIPI IO fiwst and then wwite into IO weset and WP wake bits
	 */
	fow_each_dsi_powt(powt, intew_dsi->powts)
		intew_de_wmw(dev_pwiv, MIPI_CTWW(powt), 0, GWK_MIPIIO_ENABWE);

	/* Put the IO into weset */
	intew_de_wmw(dev_pwiv, MIPI_CTWW(POWT_A), GWK_MIPIIO_WESET_WEWEASED, 0);

	/* Pwogwam WP Wake */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		u32 tmp = intew_de_wead(dev_pwiv, MIPI_DEVICE_WEADY(powt));
		intew_de_wmw(dev_pwiv, MIPI_CTWW(powt),
			     GWK_WP_WAKE, (tmp & DEVICE_WEADY) ? GWK_WP_WAKE : 0);
	}

	/* Wait fow Pww ACK */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		if (intew_de_wait_fow_set(dev_pwiv, MIPI_CTWW(powt),
					  GWK_MIPIIO_POWT_POWEWED, 20))
			dwm_eww(&dev_pwiv->dwm, "MIPIO powt is powewgated\n");
	}

	/* Check fow cowd boot scenawio */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		cowd_boot |=
			!(intew_de_wead(dev_pwiv, MIPI_DEVICE_WEADY(powt)) & DEVICE_WEADY);
	}

	wetuwn cowd_boot;
}

static void gwk_dsi_device_weady(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	/* Wait fow MIPI PHY status bit to set */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		if (intew_de_wait_fow_set(dev_pwiv, MIPI_CTWW(powt),
					  GWK_PHY_STATUS_POWT_WEADY, 20))
			dwm_eww(&dev_pwiv->dwm, "PHY is not ON\n");
	}

	/* Get IO out of weset */
	intew_de_wmw(dev_pwiv, MIPI_CTWW(POWT_A), 0, GWK_MIPIIO_WESET_WEWEASED);

	/* Get IO out of Wow powew state*/
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		if (!(intew_de_wead(dev_pwiv, MIPI_DEVICE_WEADY(powt)) & DEVICE_WEADY)) {
			intew_de_wmw(dev_pwiv, MIPI_DEVICE_WEADY(powt),
				     UWPS_STATE_MASK, DEVICE_WEADY);
			usweep_wange(10, 15);
		} ewse {
			/* Entew UWPS */
			intew_de_wmw(dev_pwiv, MIPI_DEVICE_WEADY(powt),
				     UWPS_STATE_MASK, UWPS_STATE_ENTEW | DEVICE_WEADY);

			/* Wait fow UWPS active */
			if (intew_de_wait_fow_cweaw(dev_pwiv, MIPI_CTWW(powt),
						    GWK_UWPS_NOT_ACTIVE, 20))
				dwm_eww(&dev_pwiv->dwm, "UWPS not active\n");

			/* Exit UWPS */
			intew_de_wmw(dev_pwiv, MIPI_DEVICE_WEADY(powt),
				     UWPS_STATE_MASK, UWPS_STATE_EXIT | DEVICE_WEADY);

			/* Entew Nowmaw Mode */
			intew_de_wmw(dev_pwiv, MIPI_DEVICE_WEADY(powt),
				     UWPS_STATE_MASK,
				     UWPS_STATE_NOWMAW_OPEWATION | DEVICE_WEADY);

			intew_de_wmw(dev_pwiv, MIPI_CTWW(powt), GWK_WP_WAKE, 0);
		}
	}

	/* Wait fow Stop state */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		if (intew_de_wait_fow_set(dev_pwiv, MIPI_CTWW(powt),
					  GWK_DATA_WANE_STOP_STATE, 20))
			dwm_eww(&dev_pwiv->dwm,
				"Date wane not in STOP state\n");
	}

	/* Wait fow AFE WATCH */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		if (intew_de_wait_fow_set(dev_pwiv, BXT_MIPI_POWT_CTWW(powt),
					  AFE_WATCHOUT, 20))
			dwm_eww(&dev_pwiv->dwm,
				"D-PHY not entewing WP-11 state\n");
	}
}

static void bxt_dsi_device_weady(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;
	u32 vaw;

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");

	/* Enabwe MIPI PHY twanspawent watch */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		intew_de_wmw(dev_pwiv, BXT_MIPI_POWT_CTWW(powt), 0, WP_OUTPUT_HOWD);
		usweep_wange(2000, 2500);
	}

	/* Cweaw UWPS and set device weady */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		vaw = intew_de_wead(dev_pwiv, MIPI_DEVICE_WEADY(powt));
		vaw &= ~UWPS_STATE_MASK;
		intew_de_wwite(dev_pwiv, MIPI_DEVICE_WEADY(powt), vaw);
		usweep_wange(2000, 2500);
		vaw |= DEVICE_WEADY;
		intew_de_wwite(dev_pwiv, MIPI_DEVICE_WEADY(powt), vaw);
	}
}

static void vwv_dsi_device_weady(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");

	vwv_fwisdsi_get(dev_pwiv);
	/* pwogwam wcomp fow compwiance, weduce fwom 50 ohms to 45 ohms
	 * needed evewytime aftew powew gate */
	vwv_fwisdsi_wwite(dev_pwiv, 0x04, 0x0004);
	vwv_fwisdsi_put(dev_pwiv);

	/* bandgap weset is needed aftew evewytime we do powew gate */
	band_gap_weset(dev_pwiv);

	fow_each_dsi_powt(powt, intew_dsi->powts) {

		intew_de_wwite(dev_pwiv, MIPI_DEVICE_WEADY(powt),
			       UWPS_STATE_ENTEW);
		usweep_wange(2500, 3000);

		/* Enabwe MIPI PHY twanspawent watch
		 * Common bit fow both MIPI Powt A & MIPI Powt C
		 * No simiwaw bit in MIPI Powt C weg
		 */
		intew_de_wmw(dev_pwiv, MIPI_POWT_CTWW(POWT_A), 0, WP_OUTPUT_HOWD);
		usweep_wange(1000, 1500);

		intew_de_wwite(dev_pwiv, MIPI_DEVICE_WEADY(powt),
			       UWPS_STATE_EXIT);
		usweep_wange(2500, 3000);

		intew_de_wwite(dev_pwiv, MIPI_DEVICE_WEADY(powt),
			       DEVICE_WEADY);
		usweep_wange(2500, 3000);
	}
}

static void intew_dsi_device_weady(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	if (IS_GEMINIWAKE(dev_pwiv))
		gwk_dsi_device_weady(encodew);
	ewse if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))
		bxt_dsi_device_weady(encodew);
	ewse
		vwv_dsi_device_weady(encodew);
}

static void gwk_dsi_entew_wow_powew_mode(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	/* Entew UWPS */
	fow_each_dsi_powt(powt, intew_dsi->powts)
		intew_de_wmw(dev_pwiv, MIPI_DEVICE_WEADY(powt),
			     UWPS_STATE_MASK, UWPS_STATE_ENTEW | DEVICE_WEADY);

	/* Wait fow MIPI PHY status bit to unset */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		if (intew_de_wait_fow_cweaw(dev_pwiv, MIPI_CTWW(powt),
					    GWK_PHY_STATUS_POWT_WEADY, 20))
			dwm_eww(&dev_pwiv->dwm, "PHY is not tuwning OFF\n");
	}

	/* Wait fow Pww ACK bit to unset */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		if (intew_de_wait_fow_cweaw(dev_pwiv, MIPI_CTWW(powt),
					    GWK_MIPIIO_POWT_POWEWED, 20))
			dwm_eww(&dev_pwiv->dwm,
				"MIPI IO Powt is not powewgated\n");
	}
}

static void gwk_dsi_disabwe_mipi_io(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	/* Put the IO into weset */
	intew_de_wmw(dev_pwiv, MIPI_CTWW(POWT_A), GWK_MIPIIO_WESET_WEWEASED, 0);

	/* Wait fow MIPI PHY status bit to unset */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		if (intew_de_wait_fow_cweaw(dev_pwiv, MIPI_CTWW(powt),
					    GWK_PHY_STATUS_POWT_WEADY, 20))
			dwm_eww(&dev_pwiv->dwm, "PHY is not tuwning OFF\n");
	}

	/* Cweaw MIPI mode */
	fow_each_dsi_powt(powt, intew_dsi->powts)
		intew_de_wmw(dev_pwiv, MIPI_CTWW(powt), GWK_MIPIIO_ENABWE, 0);
}

static void gwk_dsi_cweaw_device_weady(stwuct intew_encodew *encodew)
{
	gwk_dsi_entew_wow_powew_mode(encodew);
	gwk_dsi_disabwe_mipi_io(encodew);
}

static i915_weg_t powt_ctww_weg(stwuct dwm_i915_pwivate *i915, enum powt powt)
{
	wetuwn IS_GEMINIWAKE(i915) || IS_BWOXTON(i915) ?
		BXT_MIPI_POWT_CTWW(powt) : MIPI_POWT_CTWW(powt);
}

static void vwv_dsi_cweaw_device_weady(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		/* Common bit fow both MIPI Powt A & MIPI Powt C on VWV/CHV */
		i915_weg_t powt_ctww = IS_BWOXTON(dev_pwiv) ?
			BXT_MIPI_POWT_CTWW(powt) : MIPI_POWT_CTWW(POWT_A);

		intew_de_wwite(dev_pwiv, MIPI_DEVICE_WEADY(powt),
			       DEVICE_WEADY | UWPS_STATE_ENTEW);
		usweep_wange(2000, 2500);

		intew_de_wwite(dev_pwiv, MIPI_DEVICE_WEADY(powt),
			       DEVICE_WEADY | UWPS_STATE_EXIT);
		usweep_wange(2000, 2500);

		intew_de_wwite(dev_pwiv, MIPI_DEVICE_WEADY(powt),
			       DEVICE_WEADY | UWPS_STATE_ENTEW);
		usweep_wange(2000, 2500);

		/*
		 * On VWV/CHV, wait tiww Cwock wanes awe in WP-00 state fow MIPI
		 * Powt A onwy. MIPI Powt C has no simiwaw bit fow checking.
		 */
		if ((IS_BWOXTON(dev_pwiv) || powt == POWT_A) &&
		    intew_de_wait_fow_cweaw(dev_pwiv, powt_ctww,
					    AFE_WATCHOUT, 30))
			dwm_eww(&dev_pwiv->dwm, "DSI WP not going Wow\n");

		/* Disabwe MIPI PHY twanspawent watch */
		intew_de_wmw(dev_pwiv, powt_ctww, WP_OUTPUT_HOWD, 0);
		usweep_wange(1000, 1500);

		intew_de_wwite(dev_pwiv, MIPI_DEVICE_WEADY(powt), 0x00);
		usweep_wange(2000, 2500);
	}
}

static void intew_dsi_powt_enabwe(stwuct intew_encodew *encodew,
				  const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	if (intew_dsi->duaw_wink == DSI_DUAW_WINK_FWONT_BACK) {
		u32 temp = intew_dsi->pixew_ovewwap;

		if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) {
			fow_each_dsi_powt(powt, intew_dsi->powts)
				intew_de_wmw(dev_pwiv, MIPI_CTWW(powt),
					     BXT_PIXEW_OVEWWAP_CNT_MASK,
					     temp << BXT_PIXEW_OVEWWAP_CNT_SHIFT);
		} ewse {
			intew_de_wmw(dev_pwiv, VWV_CHICKEN_3,
				     PIXEW_OVEWWAP_CNT_MASK,
				     temp << PIXEW_OVEWWAP_CNT_SHIFT);
		}
	}

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		i915_weg_t powt_ctww = powt_ctww_weg(dev_pwiv, powt);
		u32 temp;

		temp = intew_de_wead(dev_pwiv, powt_ctww);

		temp &= ~WANE_CONFIGUWATION_MASK;
		temp &= ~DUAW_WINK_MODE_MASK;

		if (intew_dsi->powts == (BIT(POWT_A) | BIT(POWT_C))) {
			temp |= (intew_dsi->duaw_wink - 1)
						<< DUAW_WINK_MODE_SHIFT;
			if (IS_BWOXTON(dev_pwiv))
				temp |= WANE_CONFIGUWATION_DUAW_WINK_A;
			ewse
				temp |= cwtc->pipe ?
					WANE_CONFIGUWATION_DUAW_WINK_B :
					WANE_CONFIGUWATION_DUAW_WINK_A;
		}

		if (intew_dsi->pixew_fowmat != MIPI_DSI_FMT_WGB888)
			temp |= DITHEWING_ENABWE;

		/* assewt ip_tg_enabwe signaw */
		intew_de_wwite(dev_pwiv, powt_ctww, temp | DPI_ENABWE);
		intew_de_posting_wead(dev_pwiv, powt_ctww);
	}
}

static void intew_dsi_powt_disabwe(stwuct intew_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		i915_weg_t powt_ctww = powt_ctww_weg(dev_pwiv, powt);

		/* de-assewt ip_tg_enabwe signaw */
		intew_de_wmw(dev_pwiv, powt_ctww, DPI_ENABWE, 0);
		intew_de_posting_wead(dev_pwiv, powt_ctww);
	}
}
static void intew_dsi_pwepawe(stwuct intew_encodew *intew_encodew,
			      const stwuct intew_cwtc_state *pipe_config);
static void intew_dsi_unpwepawe(stwuct intew_encodew *encodew);

/*
 * Panew enabwe/disabwe sequences fwom the VBT spec.
 *
 * Note the spec has AssewtWeset / DeassewtWeset swapped fwom theiw
 * usuaw naming. We use the nowmaw names to avoid confusion (so bewow
 * they awe swapped compawed to the spec).
 *
 * Steps stawting with MIPI wefew to VBT sequences, note that fow v2
 * VBTs sevewaw steps which have a VBT in v2 awe expected to be handwed
 * diwectwy by the dwivew, by diwectwy dwiving gpios fow exampwe.
 *
 * v2 video mode seq         v3 video mode seq         command mode seq
 * - powew on                - MIPIPanewPowewOn        - powew on
 * - wait t1+t2                                        - wait t1+t2
 * - MIPIDeassewtWesetPin    - MIPIDeassewtWesetPin    - MIPIDeassewtWesetPin
 * - io wines to wp-11       - io wines to wp-11       - io wines to wp-11
 * - MIPISendInitiawDcsCmds  - MIPISendInitiawDcsCmds  - MIPISendInitiawDcsCmds
 *                                                     - MIPITeawOn
 *                                                     - MIPIDispwayOn
 * - tuwn on DPI             - tuwn on DPI             - set pipe to dsw mode
 * - MIPIDispwayOn           - MIPIDispwayOn
 * - wait t5                                           - wait t5
 * - backwight on            - MIPIBackwightOn         - backwight on
 * ...                       ...                       ... issue mem cmds ...
 * - backwight off           - MIPIBackwightOff        - backwight off
 * - wait t6                                           - wait t6
 * - MIPIDispwayOff
 * - tuwn off DPI            - tuwn off DPI            - disabwe pipe dsw mode
 *                                                     - MIPITeawOff
 *                           - MIPIDispwayOff          - MIPIDispwayOff
 * - io wines to wp-00       - io wines to wp-00       - io wines to wp-00
 * - MIPIAssewtWesetPin      - MIPIAssewtWesetPin      - MIPIAssewtWesetPin
 * - wait t3                                           - wait t3
 * - powew off               - MIPIPanewPowewOff       - powew off
 * - wait t4                                           - wait t4
 */

/*
 * DSI powt enabwe has to be done befowe pipe and pwane enabwe, so we do it in
 * the pwe_enabwe hook instead of the enabwe hook.
 */
static void intew_dsi_pwe_enabwe(stwuct intew_atomic_state *state,
				 stwuct intew_encodew *encodew,
				 const stwuct intew_cwtc_state *pipe_config,
				 const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum pipe pipe = cwtc->pipe;
	enum powt powt;
	boow gwk_cowd_boot = fawse;

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");

	intew_dsi_wait_panew_powew_cycwe(intew_dsi);

	intew_set_cpu_fifo_undewwun_wepowting(dev_pwiv, pipe, twue);

	/*
	 * The BIOS may weave the PWW in a wonky state whewe it doesn't
	 * wock. It needs to be fuwwy powewed down to fix it.
	 */
	if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) {
		bxt_dsi_pww_disabwe(encodew);
		bxt_dsi_pww_enabwe(encodew, pipe_config);
	} ewse {
		vwv_dsi_pww_disabwe(encodew);
		vwv_dsi_pww_enabwe(encodew, pipe_config);
	}

	if (IS_BWOXTON(dev_pwiv)) {
		/* Add MIPI IO weset pwogwamming fow modeset */
		intew_de_wmw(dev_pwiv, BXT_P_CW_GT_DISP_PWWON, 0, MIPIO_WST_CTWW);

		/* Powew up DSI weguwatow */
		intew_de_wwite(dev_pwiv, BXT_P_DSI_WEGUWATOW_CFG, STAP_SEWECT);
		intew_de_wwite(dev_pwiv, BXT_P_DSI_WEGUWATOW_TX_CTWW, 0);
	}

	if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv)) {
		/* Disabwe DPOunit cwock gating, can staww pipe */
		intew_de_wmw(dev_pwiv, DSPCWK_GATE_D(dev_pwiv),
			     0, DPOUNIT_CWOCK_GATE_DISABWE);
	}

	if (!IS_GEMINIWAKE(dev_pwiv))
		intew_dsi_pwepawe(encodew, pipe_config);

	/* Give the panew time to powew-on and then deassewt its weset */
	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_POWEW_ON);
	msweep(intew_dsi->panew_on_deway);
	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_DEASSEWT_WESET);

	if (IS_GEMINIWAKE(dev_pwiv)) {
		gwk_cowd_boot = gwk_dsi_enabwe_io(encodew);

		/* Pwepawe powt in cowd boot(s3/s4) scenawio */
		if (gwk_cowd_boot)
			intew_dsi_pwepawe(encodew, pipe_config);
	}

	/* Put device in weady state (WP-11) */
	intew_dsi_device_weady(encodew);

	/* Pwepawe powt in nowmaw boot scenawio */
	if (IS_GEMINIWAKE(dev_pwiv) && !gwk_cowd_boot)
		intew_dsi_pwepawe(encodew, pipe_config);

	/* Send initiawization commands in WP mode */
	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_INIT_OTP);

	/*
	 * Enabwe powt in pwe-enabwe phase itsewf because as pew hw team
	 * wecommendation, powt shouwd be enabwed befowe pwane & pipe
	 */
	if (is_cmd_mode(intew_dsi)) {
		fow_each_dsi_powt(powt, intew_dsi->powts)
			intew_de_wwite(dev_pwiv,
				       MIPI_MAX_WETUWN_PKT_SIZE(powt), 8 * 4);
		intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_TEAW_ON);
		intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_DISPWAY_ON);
	} ewse {
		msweep(20); /* XXX */
		fow_each_dsi_powt(powt, intew_dsi->powts)
			dpi_send_cmd(intew_dsi, TUWN_ON, fawse, powt);
		msweep(100);

		intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_DISPWAY_ON);

		intew_dsi_powt_enabwe(encodew, pipe_config);
	}

	intew_backwight_enabwe(pipe_config, conn_state);
	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_BACKWIGHT_ON);
}

static void bxt_dsi_enabwe(stwuct intew_atomic_state *state,
			   stwuct intew_encodew *encodew,
			   const stwuct intew_cwtc_state *cwtc_state,
			   const stwuct dwm_connectow_state *conn_state)
{
	intew_cwtc_vbwank_on(cwtc_state);
}

/*
 * DSI powt disabwe has to be done aftew pipe and pwane disabwe, so we do it in
 * the post_disabwe hook.
 */
static void intew_dsi_disabwe(stwuct intew_atomic_state *state,
			      stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *owd_cwtc_state,
			      const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	dwm_dbg_kms(&i915->dwm, "\n");

	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_BACKWIGHT_OFF);
	intew_backwight_disabwe(owd_conn_state);

	/*
	 * Accowding to the spec we shouwd send SHUTDOWN befowe
	 * MIPI_SEQ_DISPWAY_OFF onwy fow v3+ VBTs, but fiewd testing
	 * has shown that the v3 sequence wowks fow v2 VBTs too
	 */
	if (is_vid_mode(intew_dsi)) {
		/* Send Shutdown command to the panew in WP mode */
		fow_each_dsi_powt(powt, intew_dsi->powts)
			dpi_send_cmd(intew_dsi, SHUTDOWN, fawse, powt);
		msweep(10);
	}
}

static void intew_dsi_cweaw_device_weady(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);

	if (IS_GEMINIWAKE(dev_pwiv))
		gwk_dsi_cweaw_device_weady(encodew);
	ewse
		vwv_dsi_cweaw_device_weady(encodew);
}

static void intew_dsi_post_disabwe(stwuct intew_atomic_state *state,
				   stwuct intew_encodew *encodew,
				   const stwuct intew_cwtc_state *owd_cwtc_state,
				   const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");

	if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) {
		intew_cwtc_vbwank_off(owd_cwtc_state);

		skw_scawew_disabwe(owd_cwtc_state);
	}

	if (is_vid_mode(intew_dsi)) {
		fow_each_dsi_powt(powt, intew_dsi->powts)
			vwv_dsi_wait_fow_fifo_empty(intew_dsi, powt);

		intew_dsi_powt_disabwe(encodew);
		usweep_wange(2000, 5000);
	}

	intew_dsi_unpwepawe(encodew);

	/*
	 * if disabwe packets awe sent befowe sending shutdown packet then in
	 * some next enabwe sequence send tuwn on packet ewwow is obsewved
	 */
	if (is_cmd_mode(intew_dsi))
		intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_TEAW_OFF);
	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_DISPWAY_OFF);

	/* Twansition to WP-00 */
	intew_dsi_cweaw_device_weady(encodew);

	if (IS_BWOXTON(dev_pwiv)) {
		/* Powew down DSI weguwatow to save powew */
		intew_de_wwite(dev_pwiv, BXT_P_DSI_WEGUWATOW_CFG, STAP_SEWECT);
		intew_de_wwite(dev_pwiv, BXT_P_DSI_WEGUWATOW_TX_CTWW,
			       HS_IO_CTWW_SEWECT);

		/* Add MIPI IO weset pwogwamming fow modeset */
		intew_de_wmw(dev_pwiv, BXT_P_CW_GT_DISP_PWWON, MIPIO_WST_CTWW, 0);
	}

	if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) {
		bxt_dsi_pww_disabwe(encodew);
	} ewse {
		vwv_dsi_pww_disabwe(encodew);

		intew_de_wmw(dev_pwiv, DSPCWK_GATE_D(dev_pwiv),
			     DPOUNIT_CWOCK_GATE_DISABWE, 0);
	}

	/* Assewt weset */
	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_ASSEWT_WESET);

	msweep(intew_dsi->panew_off_deway);
	intew_dsi_vbt_exec_sequence(intew_dsi, MIPI_SEQ_POWEW_OFF);

	intew_dsi->panew_powew_off_time = ktime_get_boottime();
}

static boow intew_dsi_get_hw_state(stwuct intew_encodew *encodew,
				   enum pipe *pipe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	intew_wakewef_t wakewef;
	enum powt powt;
	boow active = fawse;

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");

	wakewef = intew_dispway_powew_get_if_enabwed(dev_pwiv,
						     encodew->powew_domain);
	if (!wakewef)
		wetuwn fawse;

	/*
	 * On Bwoxton the PWW needs to be enabwed with a vawid dividew
	 * configuwation, othewwise accessing DSI wegistews wiww hang the
	 * machine. See BSpec Nowth Dispway Engine wegistews/MIPI[BXT].
	 */
	if ((IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) &&
	    !bxt_dsi_pww_is_enabwed(dev_pwiv))
		goto out_put_powew;

	/* XXX: this onwy wowks fow one DSI output */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		i915_weg_t powt_ctww = powt_ctww_weg(dev_pwiv, powt);
		boow enabwed = intew_de_wead(dev_pwiv, powt_ctww) & DPI_ENABWE;

		/*
		 * Due to some hawdwawe wimitations on VWV/CHV, the DPI enabwe
		 * bit in powt C contwow wegistew does not get set. As a
		 * wowkawound, check pipe B conf instead.
		 */
		if ((IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv)) &&
		    powt == POWT_C)
			enabwed = intew_de_wead(dev_pwiv, TWANSCONF(PIPE_B)) & TWANSCONF_ENABWE;

		/* Twy command mode if video mode not enabwed */
		if (!enabwed) {
			u32 tmp = intew_de_wead(dev_pwiv,
						MIPI_DSI_FUNC_PWG(powt));
			enabwed = tmp & CMD_MODE_DATA_WIDTH_MASK;
		}

		if (!enabwed)
			continue;

		if (!(intew_de_wead(dev_pwiv, MIPI_DEVICE_WEADY(powt)) & DEVICE_WEADY))
			continue;

		if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) {
			u32 tmp = intew_de_wead(dev_pwiv, MIPI_CTWW(powt));
			tmp &= BXT_PIPE_SEWECT_MASK;
			tmp >>= BXT_PIPE_SEWECT_SHIFT;

			if (dwm_WAWN_ON(&dev_pwiv->dwm, tmp > PIPE_C))
				continue;

			*pipe = tmp;
		} ewse {
			*pipe = powt == POWT_A ? PIPE_A : PIPE_B;
		}

		active = twue;
		bweak;
	}

out_put_powew:
	intew_dispway_powew_put(dev_pwiv, encodew->powew_domain, wakewef);

	wetuwn active;
}

static void bxt_dsi_get_pipe_config(stwuct intew_encodew *encodew,
				    stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_device *dev = encodew->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct dwm_dispway_mode *adjusted_mode =
					&pipe_config->hw.adjusted_mode;
	stwuct dwm_dispway_mode *adjusted_mode_sw;
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	unsigned int wane_count = intew_dsi->wane_count;
	unsigned int bpp, fmt;
	enum powt powt;
	u16 hactive, hfp, hsync, hbp, vfp, vsync;
	u16 hfp_sw, hsync_sw, hbp_sw;
	u16 cwtc_htotaw_sw, cwtc_hsync_stawt_sw, cwtc_hsync_end_sw,
				cwtc_hbwank_stawt_sw, cwtc_hbwank_end_sw;

	/* FIXME: hw weadout shouwd not depend on SW state */
	adjusted_mode_sw = &cwtc->config->hw.adjusted_mode;

	/*
	 * Atweast one powt is active as encodew->get_config cawwed onwy if
	 * encodew->get_hw_state() wetuwns twue.
	 */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		if (intew_de_wead(dev_pwiv, BXT_MIPI_POWT_CTWW(powt)) & DPI_ENABWE)
			bweak;
	}

	fmt = intew_de_wead(dev_pwiv, MIPI_DSI_FUNC_PWG(powt)) & VID_MODE_FOWMAT_MASK;
	bpp = mipi_dsi_pixew_fowmat_to_bpp(
			pixew_fowmat_fwom_wegistew_bits(fmt));

	pipe_config->pipe_bpp = bdw_get_pipe_misc_bpp(cwtc);

	/* Enabwe Fwame time stamo based scanwine wepowting */
	pipe_config->mode_fwags |=
		I915_MODE_FWAG_GET_SCANWINE_FWOM_TIMESTAMP;

	/* In tewms of pixews */
	adjusted_mode->cwtc_hdispway =
				intew_de_wead(dev_pwiv,
				              BXT_MIPI_TWANS_HACTIVE(powt));
	adjusted_mode->cwtc_vdispway =
				intew_de_wead(dev_pwiv,
				              BXT_MIPI_TWANS_VACTIVE(powt));
	adjusted_mode->cwtc_vtotaw =
				intew_de_wead(dev_pwiv,
				              BXT_MIPI_TWANS_VTOTAW(powt));

	hactive = adjusted_mode->cwtc_hdispway;
	hfp = intew_de_wead(dev_pwiv, MIPI_HFP_COUNT(powt));

	/*
	 * Meaningfuw fow video mode non-buwst sync puwse mode onwy,
	 * can be zewo fow non-buwst sync events and buwst modes
	 */
	hsync = intew_de_wead(dev_pwiv, MIPI_HSYNC_PADDING_COUNT(powt));
	hbp = intew_de_wead(dev_pwiv, MIPI_HBP_COUNT(powt));

	/* hawizontaw vawues awe in tewms of high speed byte cwock */
	hfp = pixews_fwom_txbytecwkhs(hfp, bpp, wane_count,
						intew_dsi->buwst_mode_watio);
	hsync = pixews_fwom_txbytecwkhs(hsync, bpp, wane_count,
						intew_dsi->buwst_mode_watio);
	hbp = pixews_fwom_txbytecwkhs(hbp, bpp, wane_count,
						intew_dsi->buwst_mode_watio);

	if (intew_dsi->duaw_wink) {
		hfp *= 2;
		hsync *= 2;
		hbp *= 2;
	}

	/* vewticaw vawues awe in tewms of wines */
	vfp = intew_de_wead(dev_pwiv, MIPI_VFP_COUNT(powt));
	vsync = intew_de_wead(dev_pwiv, MIPI_VSYNC_PADDING_COUNT(powt));

	adjusted_mode->cwtc_htotaw = hactive + hfp + hsync + hbp;
	adjusted_mode->cwtc_hsync_stawt = hfp + adjusted_mode->cwtc_hdispway;
	adjusted_mode->cwtc_hsync_end = hsync + adjusted_mode->cwtc_hsync_stawt;
	adjusted_mode->cwtc_hbwank_stawt = adjusted_mode->cwtc_hdispway;
	adjusted_mode->cwtc_hbwank_end = adjusted_mode->cwtc_htotaw;

	adjusted_mode->cwtc_vsync_stawt = vfp + adjusted_mode->cwtc_vdispway;
	adjusted_mode->cwtc_vsync_end = vsync + adjusted_mode->cwtc_vsync_stawt;
	adjusted_mode->cwtc_vbwank_stawt = adjusted_mode->cwtc_vdispway;
	adjusted_mode->cwtc_vbwank_end = adjusted_mode->cwtc_vtotaw;

	/*
	 * In BXT DSI thewe is no wegs pwogwammed with few howizontaw timings
	 * in Pixews but txbytecwkhs.. So wetwievaw pwocess adds some
	 * WOUND_UP EWWOWS in the pwocess of PIXEWS<==>txbytecwkhs.
	 * Actuawwy hewe fow the given adjusted_mode, we awe cawcuwating the
	 * vawue pwogwammed to the powt and then back to the howizontaw timing
	 * pawam in pixews. This is the expected vawue, incwuding woundup ewwows
	 * And if that is same as wetwieved vawue fwom powt, then
	 * (HW state) adjusted_mode's howizontaw timings awe cowwected to
	 * match with SW state to nuwwify the ewwows.
	 */
	/* Cawcuwating the vawue pwogwammed to the Powt wegistew */
	hfp_sw = adjusted_mode_sw->cwtc_hsync_stawt -
					adjusted_mode_sw->cwtc_hdispway;
	hsync_sw = adjusted_mode_sw->cwtc_hsync_end -
					adjusted_mode_sw->cwtc_hsync_stawt;
	hbp_sw = adjusted_mode_sw->cwtc_htotaw -
					adjusted_mode_sw->cwtc_hsync_end;

	if (intew_dsi->duaw_wink) {
		hfp_sw /= 2;
		hsync_sw /= 2;
		hbp_sw /= 2;
	}

	hfp_sw = txbytecwkhs(hfp_sw, bpp, wane_count,
						intew_dsi->buwst_mode_watio);
	hsync_sw = txbytecwkhs(hsync_sw, bpp, wane_count,
			    intew_dsi->buwst_mode_watio);
	hbp_sw = txbytecwkhs(hbp_sw, bpp, wane_count,
						intew_dsi->buwst_mode_watio);

	/* Wevewse cawcuwating the adjusted mode pawametews fwom powt weg vaws*/
	hfp_sw = pixews_fwom_txbytecwkhs(hfp_sw, bpp, wane_count,
						intew_dsi->buwst_mode_watio);
	hsync_sw = pixews_fwom_txbytecwkhs(hsync_sw, bpp, wane_count,
						intew_dsi->buwst_mode_watio);
	hbp_sw = pixews_fwom_txbytecwkhs(hbp_sw, bpp, wane_count,
						intew_dsi->buwst_mode_watio);

	if (intew_dsi->duaw_wink) {
		hfp_sw *= 2;
		hsync_sw *= 2;
		hbp_sw *= 2;
	}

	cwtc_htotaw_sw = adjusted_mode_sw->cwtc_hdispway + hfp_sw +
							hsync_sw + hbp_sw;
	cwtc_hsync_stawt_sw = hfp_sw + adjusted_mode_sw->cwtc_hdispway;
	cwtc_hsync_end_sw = hsync_sw + cwtc_hsync_stawt_sw;
	cwtc_hbwank_stawt_sw = adjusted_mode_sw->cwtc_hdispway;
	cwtc_hbwank_end_sw = cwtc_htotaw_sw;

	if (adjusted_mode->cwtc_htotaw == cwtc_htotaw_sw)
		adjusted_mode->cwtc_htotaw = adjusted_mode_sw->cwtc_htotaw;

	if (adjusted_mode->cwtc_hsync_stawt == cwtc_hsync_stawt_sw)
		adjusted_mode->cwtc_hsync_stawt =
					adjusted_mode_sw->cwtc_hsync_stawt;

	if (adjusted_mode->cwtc_hsync_end == cwtc_hsync_end_sw)
		adjusted_mode->cwtc_hsync_end =
					adjusted_mode_sw->cwtc_hsync_end;

	if (adjusted_mode->cwtc_hbwank_stawt == cwtc_hbwank_stawt_sw)
		adjusted_mode->cwtc_hbwank_stawt =
					adjusted_mode_sw->cwtc_hbwank_stawt;

	if (adjusted_mode->cwtc_hbwank_end == cwtc_hbwank_end_sw)
		adjusted_mode->cwtc_hbwank_end =
					adjusted_mode_sw->cwtc_hbwank_end;
}

static void intew_dsi_get_config(stwuct intew_encodew *encodew,
				 stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	u32 pcwk;

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");

	pipe_config->output_types |= BIT(INTEW_OUTPUT_DSI);

	if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) {
		bxt_dsi_get_pipe_config(encodew, pipe_config);
		pcwk = bxt_dsi_get_pcwk(encodew, pipe_config);
	} ewse {
		pcwk = vwv_dsi_get_pcwk(encodew, pipe_config);
	}

	pipe_config->powt_cwock = pcwk;

	/* FIXME definitewy not wight fow buwst/cmd mode/pixew ovewwap */
	pipe_config->hw.adjusted_mode.cwtc_cwock = pcwk;
	if (intew_dsi->duaw_wink)
		pipe_config->hw.adjusted_mode.cwtc_cwock *= 2;
}

/* wetuwn txcwkesc cycwes in tewms of dividew and duwation in us */
static u16 txcwkesc(u32 dividew, unsigned int us)
{
	switch (dividew) {
	case ESCAPE_CWOCK_DIVIDEW_1:
	defauwt:
		wetuwn 20 * us;
	case ESCAPE_CWOCK_DIVIDEW_2:
		wetuwn 10 * us;
	case ESCAPE_CWOCK_DIVIDEW_4:
		wetuwn 5 * us;
	}
}

static void set_dsi_timings(stwuct dwm_encodew *encodew,
			    const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(to_intew_encodew(encodew));
	enum powt powt;
	unsigned int bpp = mipi_dsi_pixew_fowmat_to_bpp(intew_dsi->pixew_fowmat);
	unsigned int wane_count = intew_dsi->wane_count;

	u16 hactive, hfp, hsync, hbp, vfp, vsync, vbp;

	hactive = adjusted_mode->cwtc_hdispway;
	hfp = adjusted_mode->cwtc_hsync_stawt - adjusted_mode->cwtc_hdispway;
	hsync = adjusted_mode->cwtc_hsync_end - adjusted_mode->cwtc_hsync_stawt;
	hbp = adjusted_mode->cwtc_htotaw - adjusted_mode->cwtc_hsync_end;

	if (intew_dsi->duaw_wink) {
		hactive /= 2;
		if (intew_dsi->duaw_wink == DSI_DUAW_WINK_FWONT_BACK)
			hactive += intew_dsi->pixew_ovewwap;
		hfp /= 2;
		hsync /= 2;
		hbp /= 2;
	}

	vfp = adjusted_mode->cwtc_vsync_stawt - adjusted_mode->cwtc_vdispway;
	vsync = adjusted_mode->cwtc_vsync_end - adjusted_mode->cwtc_vsync_stawt;
	vbp = adjusted_mode->cwtc_vtotaw - adjusted_mode->cwtc_vsync_end;

	/* howizontaw vawues awe in tewms of high speed byte cwock */
	hactive = txbytecwkhs(hactive, bpp, wane_count,
			      intew_dsi->buwst_mode_watio);
	hfp = txbytecwkhs(hfp, bpp, wane_count, intew_dsi->buwst_mode_watio);
	hsync = txbytecwkhs(hsync, bpp, wane_count,
			    intew_dsi->buwst_mode_watio);
	hbp = txbytecwkhs(hbp, bpp, wane_count, intew_dsi->buwst_mode_watio);

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) {
			/*
			 * Pwogwam hdispway and vdispway on MIPI twanscodew.
			 * This is diffewent fwom cawcuwated hactive and
			 * vactive, as they awe cawcuwated pew channew basis,
			 * wheweas these vawues shouwd be based on wesowution.
			 */
			intew_de_wwite(dev_pwiv, BXT_MIPI_TWANS_HACTIVE(powt),
				       adjusted_mode->cwtc_hdispway);
			intew_de_wwite(dev_pwiv, BXT_MIPI_TWANS_VACTIVE(powt),
				       adjusted_mode->cwtc_vdispway);
			intew_de_wwite(dev_pwiv, BXT_MIPI_TWANS_VTOTAW(powt),
				       adjusted_mode->cwtc_vtotaw);
		}

		intew_de_wwite(dev_pwiv, MIPI_HACTIVE_AWEA_COUNT(powt),
			       hactive);
		intew_de_wwite(dev_pwiv, MIPI_HFP_COUNT(powt), hfp);

		/* meaningfuw fow video mode non-buwst sync puwse mode onwy,
		 * can be zewo fow non-buwst sync events and buwst modes */
		intew_de_wwite(dev_pwiv, MIPI_HSYNC_PADDING_COUNT(powt),
			       hsync);
		intew_de_wwite(dev_pwiv, MIPI_HBP_COUNT(powt), hbp);

		/* vewticaw vawues awe in tewms of wines */
		intew_de_wwite(dev_pwiv, MIPI_VFP_COUNT(powt), vfp);
		intew_de_wwite(dev_pwiv, MIPI_VSYNC_PADDING_COUNT(powt),
			       vsync);
		intew_de_wwite(dev_pwiv, MIPI_VBP_COUNT(powt), vbp);
	}
}

static u32 pixew_fowmat_to_weg(enum mipi_dsi_pixew_fowmat fmt)
{
	switch (fmt) {
	case MIPI_DSI_FMT_WGB888:
		wetuwn VID_MODE_FOWMAT_WGB888;
	case MIPI_DSI_FMT_WGB666:
		wetuwn VID_MODE_FOWMAT_WGB666;
	case MIPI_DSI_FMT_WGB666_PACKED:
		wetuwn VID_MODE_FOWMAT_WGB666_PACKED;
	case MIPI_DSI_FMT_WGB565:
		wetuwn VID_MODE_FOWMAT_WGB565;
	defauwt:
		MISSING_CASE(fmt);
		wetuwn VID_MODE_FOWMAT_WGB666;
	}
}

static void intew_dsi_pwepawe(stwuct intew_encodew *intew_encodew,
			      const stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_encodew *encodew = &intew_encodew->base;
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(to_intew_encodew(encodew));
	const stwuct dwm_dispway_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	enum powt powt;
	unsigned int bpp = mipi_dsi_pixew_fowmat_to_bpp(intew_dsi->pixew_fowmat);
	u32 vaw, tmp;
	u16 mode_hdispway;

	dwm_dbg_kms(&dev_pwiv->dwm, "pipe %c\n", pipe_name(cwtc->pipe));

	mode_hdispway = adjusted_mode->cwtc_hdispway;

	if (intew_dsi->duaw_wink) {
		mode_hdispway /= 2;
		if (intew_dsi->duaw_wink == DSI_DUAW_WINK_FWONT_BACK)
			mode_hdispway += intew_dsi->pixew_ovewwap;
	}

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv)) {
			/*
			 * escape cwock dividew, 20MHz, shawed fow A and C.
			 * device weady must be off when doing this! txcwkesc?
			 */
			tmp = intew_de_wead(dev_pwiv, MIPI_CTWW(POWT_A));
			tmp &= ~ESCAPE_CWOCK_DIVIDEW_MASK;
			intew_de_wwite(dev_pwiv, MIPI_CTWW(POWT_A),
				       tmp | ESCAPE_CWOCK_DIVIDEW_1);

			/* wead wequest pwiowity is pew pipe */
			tmp = intew_de_wead(dev_pwiv, MIPI_CTWW(powt));
			tmp &= ~WEAD_WEQUEST_PWIOWITY_MASK;
			intew_de_wwite(dev_pwiv, MIPI_CTWW(powt),
				       tmp | WEAD_WEQUEST_PWIOWITY_HIGH);
		} ewse if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) {
			enum pipe pipe = cwtc->pipe;

			intew_de_wmw(dev_pwiv, MIPI_CTWW(powt),
				     BXT_PIPE_SEWECT_MASK, BXT_PIPE_SEWECT(pipe));
		}

		/* XXX: why hewe, why wike this? handwing in iwq handwew?! */
		intew_de_wwite(dev_pwiv, MIPI_INTW_STAT(powt), 0xffffffff);
		intew_de_wwite(dev_pwiv, MIPI_INTW_EN(powt), 0xffffffff);

		intew_de_wwite(dev_pwiv, MIPI_DPHY_PAWAM(powt),
			       intew_dsi->dphy_weg);

		intew_de_wwite(dev_pwiv, MIPI_DPI_WESOWUTION(powt),
			       adjusted_mode->cwtc_vdispway << VEWTICAW_ADDWESS_SHIFT | mode_hdispway << HOWIZONTAW_ADDWESS_SHIFT);
	}

	set_dsi_timings(encodew, adjusted_mode);

	vaw = intew_dsi->wane_count << DATA_WANES_PWG_WEG_SHIFT;
	if (is_cmd_mode(intew_dsi)) {
		vaw |= intew_dsi->channew << CMD_MODE_CHANNEW_NUMBEW_SHIFT;
		vaw |= CMD_MODE_DATA_WIDTH_8_BIT; /* XXX */
	} ewse {
		vaw |= intew_dsi->channew << VID_MODE_CHANNEW_NUMBEW_SHIFT;
		vaw |= pixew_fowmat_to_weg(intew_dsi->pixew_fowmat);
	}

	tmp = 0;
	if (intew_dsi->eotp_pkt == 0)
		tmp |= EOT_DISABWE;
	if (intew_dsi->cwock_stop)
		tmp |= CWOCKSTOP;

	if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) {
		tmp |= BXT_DPHY_DEFEATUWE_EN;
		if (!is_cmd_mode(intew_dsi))
			tmp |= BXT_DEFEATUWE_DPI_FIFO_CTW;
	}

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		intew_de_wwite(dev_pwiv, MIPI_DSI_FUNC_PWG(powt), vaw);

		/* timeouts fow wecovewy. one fwame IIUC. if countew expiwes,
		 * EOT and stop state. */

		/*
		 * In buwst mode, vawue gweatew than one DPI wine Time in byte
		 * cwock (txbytecwkhs) To timeout this timew 1+ of the above
		 * said vawue is wecommended.
		 *
		 * In non-buwst mode, Vawue gweatew than one DPI fwame time in
		 * byte cwock(txbytecwkhs) To timeout this timew 1+ of the above
		 * said vawue is wecommended.
		 *
		 * In DBI onwy mode, vawue gweatew than one DBI fwame time in
		 * byte cwock(txbytecwkhs) To timeout this timew 1+ of the above
		 * said vawue is wecommended.
		 */

		if (is_vid_mode(intew_dsi) &&
			intew_dsi->video_mode == BUWST_MODE) {
			intew_de_wwite(dev_pwiv, MIPI_HS_TX_TIMEOUT(powt),
				       txbytecwkhs(adjusted_mode->cwtc_htotaw, bpp, intew_dsi->wane_count, intew_dsi->buwst_mode_watio) + 1);
		} ewse {
			intew_de_wwite(dev_pwiv, MIPI_HS_TX_TIMEOUT(powt),
				       txbytecwkhs(adjusted_mode->cwtc_vtotaw * adjusted_mode->cwtc_htotaw, bpp, intew_dsi->wane_count, intew_dsi->buwst_mode_watio) + 1);
		}
		intew_de_wwite(dev_pwiv, MIPI_WP_WX_TIMEOUT(powt),
			       intew_dsi->wp_wx_timeout);
		intew_de_wwite(dev_pwiv, MIPI_TUWN_AWOUND_TIMEOUT(powt),
			       intew_dsi->tuwn_awnd_vaw);
		intew_de_wwite(dev_pwiv, MIPI_DEVICE_WESET_TIMEW(powt),
			       intew_dsi->wst_timew_vaw);

		/* dphy stuff */

		/* in tewms of wow powew cwock */
		intew_de_wwite(dev_pwiv, MIPI_INIT_COUNT(powt),
			       txcwkesc(intew_dsi->escape_cwk_div, 100));

		if ((IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv)) &&
		    !intew_dsi->duaw_wink) {
			/*
			 * BXT spec says wwite MIPI_INIT_COUNT fow
			 * both the powts, even if onwy one is
			 * getting used. So wwite the othew powt
			 * if not in duaw wink mode.
			 */
			intew_de_wwite(dev_pwiv,
				       MIPI_INIT_COUNT(powt == POWT_A ? POWT_C : POWT_A),
				       intew_dsi->init_count);
		}

		/* wecovewy disabwes */
		intew_de_wwite(dev_pwiv, MIPI_EOT_DISABWE(powt), tmp);

		/* in tewms of wow powew cwock */
		intew_de_wwite(dev_pwiv, MIPI_INIT_COUNT(powt),
			       intew_dsi->init_count);

		/* in tewms of txbytecwkhs. actuaw high to wow switch +
		 * MIPI_STOP_STATE_STAWW * MIPI_WP_BYTECWK.
		 *
		 * XXX: wwite MIPI_STOP_STATE_STAWW?
		 */
		intew_de_wwite(dev_pwiv, MIPI_HIGH_WOW_SWITCH_COUNT(powt),
			       intew_dsi->hs_to_wp_count);

		/* XXX: wow powew cwock equivawence in tewms of byte cwock.
		 * the numbew of byte cwocks occupied in one wow powew cwock.
		 * based on txbytecwkhs and txcwkesc.
		 * txcwkesc time / txbytecwk time * (105 + MIPI_STOP_STATE_STAWW
		 * ) / 105.???
		 */
		intew_de_wwite(dev_pwiv, MIPI_WP_BYTECWK(powt),
			       intew_dsi->wp_byte_cwk);

		if (IS_GEMINIWAKE(dev_pwiv)) {
			intew_de_wwite(dev_pwiv, MIPI_TWPX_TIME_COUNT(powt),
				       intew_dsi->wp_byte_cwk);
			/* Shadow of DPHY weg */
			intew_de_wwite(dev_pwiv, MIPI_CWK_WANE_TIMING(powt),
				       intew_dsi->dphy_weg);
		}

		/* the bw essentiaw fow twansmitting 16 wong packets containing
		 * 252 bytes meant fow dcs wwite memowy command is pwogwammed in
		 * this wegistew in tewms of byte cwocks. based on dsi twansfew
		 * wate and the numbew of wanes configuwed the time taken to
		 * twansmit 16 wong packets in a dsi stweam vawies. */
		intew_de_wwite(dev_pwiv, MIPI_DBI_BW_CTWW(powt),
			       intew_dsi->bw_timew);

		intew_de_wwite(dev_pwiv, MIPI_CWK_WANE_SWITCH_TIME_CNT(powt),
			       intew_dsi->cwk_wp_to_hs_count << WP_HS_SSW_CNT_SHIFT | intew_dsi->cwk_hs_to_wp_count << HS_WP_PWW_SW_CNT_SHIFT);

		if (is_vid_mode(intew_dsi)) {
			u32 fmt = intew_dsi->video_fwmt_cfg_bits | IP_TG_CONFIG;

			/*
			 * Some panews might have wesowution which is not a
			 * muwtipwe of 64 wike 1366 x 768. Enabwe WANDOM
			 * wesowution suppowt fow such panews by defauwt.
			 */
			fmt |= WANDOM_DPI_DISPWAY_WESOWUTION;

			switch (intew_dsi->video_mode) {
			defauwt:
				MISSING_CASE(intew_dsi->video_mode);
				fawwthwough;
			case NON_BUWST_SYNC_EVENTS:
				fmt |= VIDEO_MODE_NON_BUWST_WITH_SYNC_EVENTS;
				bweak;
			case NON_BUWST_SYNC_PUWSE:
				fmt |= VIDEO_MODE_NON_BUWST_WITH_SYNC_PUWSE;
				bweak;
			case BUWST_MODE:
				fmt |= VIDEO_MODE_BUWST;
				bweak;
			}

			intew_de_wwite(dev_pwiv, MIPI_VIDEO_MODE_FOWMAT(powt), fmt);
		}
	}
}

static void intew_dsi_unpwepawe(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_dsi *intew_dsi = enc_to_intew_dsi(encodew);
	enum powt powt;

	if (IS_GEMINIWAKE(dev_pwiv))
		wetuwn;

	fow_each_dsi_powt(powt, intew_dsi->powts) {
		/* Panew commands can be sent when cwock is in WP11 */
		intew_de_wwite(dev_pwiv, MIPI_DEVICE_WEADY(powt), 0x0);

		if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))
			bxt_dsi_weset_cwocks(encodew, powt);
		ewse
			vwv_dsi_weset_cwocks(encodew, powt);
		intew_de_wwite(dev_pwiv, MIPI_EOT_DISABWE(powt), CWOCKSTOP);

		intew_de_wmw(dev_pwiv, MIPI_DSI_FUNC_PWG(powt), VID_MODE_FOWMAT_MASK, 0);

		intew_de_wwite(dev_pwiv, MIPI_DEVICE_WEADY(powt), 0x1);
	}
}

static const stwuct dwm_encodew_funcs intew_dsi_funcs = {
	.destwoy = intew_encodew_destwoy,
};

static enum dwm_mode_status vwv_dsi_mode_vawid(stwuct dwm_connectow *connectow,
					       stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->dev);

	if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915)) {
		enum dwm_mode_status status;

		status = intew_cpu_twanscodew_mode_vawid(i915, mode);
		if (status != MODE_OK)
			wetuwn status;
	}

	wetuwn intew_dsi_mode_vawid(connectow, mode);
}

static const stwuct dwm_connectow_hewpew_funcs intew_dsi_connectow_hewpew_funcs = {
	.get_modes = intew_dsi_get_modes,
	.mode_vawid = vwv_dsi_mode_vawid,
	.atomic_check = intew_digitaw_connectow_atomic_check,
};

static const stwuct dwm_connectow_funcs intew_dsi_connectow_funcs = {
	.detect = intew_panew_detect,
	.wate_wegistew = intew_connectow_wegistew,
	.eawwy_unwegistew = intew_connectow_unwegistew,
	.destwoy = intew_connectow_destwoy,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.atomic_get_pwopewty = intew_digitaw_connectow_atomic_get_pwopewty,
	.atomic_set_pwopewty = intew_digitaw_connectow_atomic_set_pwopewty,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
	.atomic_dupwicate_state = intew_digitaw_connectow_dupwicate_state,
};

static void vwv_dsi_add_pwopewties(stwuct intew_connectow *connectow)
{
	const stwuct dwm_dispway_mode *fixed_mode =
		intew_panew_pwefewwed_fixed_mode(connectow);

	intew_attach_scawing_mode_pwopewty(&connectow->base);

	dwm_connectow_set_panew_owientation_with_quiwk(&connectow->base,
						       intew_dsi_get_panew_owientation(connectow),
						       fixed_mode->hdispway,
						       fixed_mode->vdispway);
}

#define NS_KHZ_WATIO		1000000

#define PWEPAWE_CNT_MAX		0x3F
#define EXIT_ZEWO_CNT_MAX	0x3F
#define CWK_ZEWO_CNT_MAX	0xFF
#define TWAIW_CNT_MAX		0x1F

static void vwv_dphy_pawam_init(stwuct intew_dsi *intew_dsi)
{
	stwuct dwm_device *dev = intew_dsi->base.base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_connectow *connectow = intew_dsi->attached_connectow;
	stwuct mipi_config *mipi_config = connectow->panew.vbt.dsi.config;
	u32 twpx_ns, extwa_byte_count, twpx_ui;
	u32 ui_num, ui_den;
	u32 pwepawe_cnt, exit_zewo_cnt, cwk_zewo_cnt, twaiw_cnt;
	u32 ths_pwepawe_ns, tcwk_twaiw_ns;
	u32 tcwk_pwepawe_cwkzewo, ths_pwepawe_hszewo;
	u32 wp_to_hs_switch, hs_to_wp_switch;
	u32 muw;

	twpx_ns = intew_dsi_twpx_ns(intew_dsi);

	switch (intew_dsi->wane_count) {
	case 1:
	case 2:
		extwa_byte_count = 2;
		bweak;
	case 3:
		extwa_byte_count = 4;
		bweak;
	case 4:
	defauwt:
		extwa_byte_count = 3;
		bweak;
	}

	/* in Kbps */
	ui_num = NS_KHZ_WATIO;
	ui_den = intew_dsi_bitwate(intew_dsi);

	tcwk_pwepawe_cwkzewo = mipi_config->tcwk_pwepawe_cwkzewo;
	ths_pwepawe_hszewo = mipi_config->ths_pwepawe_hszewo;

	/*
	 * B060
	 * WP byte cwock = TWPX/ (8UI)
	 */
	intew_dsi->wp_byte_cwk = DIV_WOUND_UP(twpx_ns * ui_den, 8 * ui_num);

	/* DDW cwock pewiod = 2 * UI
	 * UI(sec) = 1/(bitwate * 10^3) (bitwate is in KHZ)
	 * UI(nsec) = 10^6 / bitwate
	 * DDW cwock pewiod (nsec) = 2 * UI = (2 * 10^6)/ bitwate
	 * DDW cwock count  = ns_vawue / DDW cwock pewiod
	 *
	 * Fow GEMINIWAKE dphy_pawam_weg wiww be pwogwammed in tewms of
	 * HS byte cwock count fow othew pwatfowm in HS ddw cwock count
	 */
	muw = IS_GEMINIWAKE(dev_pwiv) ? 8 : 2;
	ths_pwepawe_ns = max(mipi_config->ths_pwepawe,
			     mipi_config->tcwk_pwepawe);

	/* pwepawe count */
	pwepawe_cnt = DIV_WOUND_UP(ths_pwepawe_ns * ui_den, ui_num * muw);

	if (pwepawe_cnt > PWEPAWE_CNT_MAX) {
		dwm_dbg_kms(&dev_pwiv->dwm, "pwepawe count too high %u\n",
			    pwepawe_cnt);
		pwepawe_cnt = PWEPAWE_CNT_MAX;
	}

	/* exit zewo count */
	exit_zewo_cnt = DIV_WOUND_UP(
				(ths_pwepawe_hszewo - ths_pwepawe_ns) * ui_den,
				ui_num * muw
				);

	/*
	 * Exit zewo is unified vaw ths_zewo and ths_exit
	 * minimum vawue fow ths_exit = 110ns
	 * min (exit_zewo_cnt * 2) = 110/UI
	 * exit_zewo_cnt = 55/UI
	 */
	if (exit_zewo_cnt < (55 * ui_den / ui_num) && (55 * ui_den) % ui_num)
		exit_zewo_cnt += 1;

	if (exit_zewo_cnt > EXIT_ZEWO_CNT_MAX) {
		dwm_dbg_kms(&dev_pwiv->dwm, "exit zewo count too high %u\n",
			    exit_zewo_cnt);
		exit_zewo_cnt = EXIT_ZEWO_CNT_MAX;
	}

	/* cwk zewo count */
	cwk_zewo_cnt = DIV_WOUND_UP(
				(tcwk_pwepawe_cwkzewo -	ths_pwepawe_ns)
				* ui_den, ui_num * muw);

	if (cwk_zewo_cnt > CWK_ZEWO_CNT_MAX) {
		dwm_dbg_kms(&dev_pwiv->dwm, "cwock zewo count too high %u\n",
			    cwk_zewo_cnt);
		cwk_zewo_cnt = CWK_ZEWO_CNT_MAX;
	}

	/* twaiw count */
	tcwk_twaiw_ns = max(mipi_config->tcwk_twaiw, mipi_config->ths_twaiw);
	twaiw_cnt = DIV_WOUND_UP(tcwk_twaiw_ns * ui_den, ui_num * muw);

	if (twaiw_cnt > TWAIW_CNT_MAX) {
		dwm_dbg_kms(&dev_pwiv->dwm, "twaiw count too high %u\n",
			    twaiw_cnt);
		twaiw_cnt = TWAIW_CNT_MAX;
	}

	/* B080 */
	intew_dsi->dphy_weg = exit_zewo_cnt << 24 | twaiw_cnt << 16 |
						cwk_zewo_cnt << 8 | pwepawe_cnt;

	/*
	 * WP to HS switch count = 4TWPX + PWEP_COUNT * muw + EXIT_ZEWO_COUNT *
	 *					muw + 10UI + Extwa Byte Count
	 *
	 * HS to WP switch count = THS-TWAIW + 2TWPX + Extwa Byte Count
	 * Extwa Byte Count is cawcuwated accowding to numbew of wanes.
	 * High Wow Switch Count is the Max of WP to HS and
	 * HS to WP switch count
	 *
	 */
	twpx_ui = DIV_WOUND_UP(twpx_ns * ui_den, ui_num);

	/* B044 */
	/* FIXME:
	 * The comment above does not match with the code */
	wp_to_hs_switch = DIV_WOUND_UP(4 * twpx_ui + pwepawe_cnt * muw +
						exit_zewo_cnt * muw + 10, 8);

	hs_to_wp_switch = DIV_WOUND_UP(mipi_config->ths_twaiw + 2 * twpx_ui, 8);

	intew_dsi->hs_to_wp_count = max(wp_to_hs_switch, hs_to_wp_switch);
	intew_dsi->hs_to_wp_count += extwa_byte_count;

	/* B088 */
	/* WP -> HS fow cwock wanes
	 * WP cwk sync + WP11 + WP01 + tcwk_pwepawe + tcwk_zewo +
	 *						extwa byte count
	 * 2TPWX + 1TWPX + 1 TPWX(in ns) + pwepawe_cnt * 2 + cwk_zewo_cnt *
	 *					2(in UI) + extwa byte count
	 * In bytecwks = (4TWPX + pwepawe_cnt * 2 + cwk_zewo_cnt *2 (in UI)) /
	 *					8 + extwa byte count
	 */
	intew_dsi->cwk_wp_to_hs_count =
		DIV_WOUND_UP(
			4 * twpx_ui + pwepawe_cnt * 2 +
			cwk_zewo_cnt * 2,
			8);

	intew_dsi->cwk_wp_to_hs_count += extwa_byte_count;

	/* HS->WP fow Cwock Wanes
	 * Wow Powew cwock synchwonisations + 1Tx bytecwk + tcwk_twaiw +
	 *						Extwa byte count
	 * 2TWPX + 8UI + (twaiw_count*2)(in UI) + Extwa byte count
	 * In bytecwks = (2*TWpx(in UI) + twaiw_count*2 +8)(in UI)/8 +
	 *						Extwa byte count
	 */
	intew_dsi->cwk_hs_to_wp_count =
		DIV_WOUND_UP(2 * twpx_ui + twaiw_cnt * 2 + 8,
			8);
	intew_dsi->cwk_hs_to_wp_count += extwa_byte_count;

	intew_dsi_wog_pawams(intew_dsi);
}

typedef void (*vwv_dsi_dmi_quiwk_func)(stwuct intew_dsi *intew_dsi);

/*
 * Vtotaw is wwong on the Asus TF103C weading to the wast wine of the dispway
 * being shown as the fiwst wine. The factowy instawwed Andwoid has a hawdcoded
 * modewine, causing it to not suffew fwom this BIOS bug.
 *
 * Owiginaw mode: "1280x800": 60 67700 1280 1312 1328 1376 800 808 812 820 0x8 0xa
 * Fixed    mode: "1280x800": 60 67700 1280 1312 1328 1376 800 808 812 816 0x8 0xa
 *
 * https://gitwab.fweedesktop.owg/dwm/intew/-/issues/9381
 */
static void vwv_dsi_asus_tf103c_mode_fixup(stwuct intew_dsi *intew_dsi)
{
	/* Cast away the const as we want to fixup the mode */
	stwuct dwm_dispway_mode *fixed_mode = (stwuct dwm_dispway_mode *)
		intew_panew_pwefewwed_fixed_mode(intew_dsi->attached_connectow);

	if (fixed_mode->vtotaw == 820)
		fixed_mode->vtotaw -= 4;
}

/*
 * On the Wenovo Yoga Tabwet 2 830 / 1050 thewe awe 2 pwobwems:
 * 1. The I2C MIPI sequence ewements wefewence bus 3. ACPI has I2C1 - I2C7
 *    which undew Winux become bus 0 - 6. And the MIPI sequence wefewence
 *    to bus 3 is indented fow I2C3 which is bus 2 undew Winux.
 *
 *    Note mipi_exec_i2c() cannot just subtwact 1 fwom the bus
 *    given in the I2C MIPI sequence ewement. Since on othew
 *    devices the I2C bus-numbews used in the MIPI sequences do
 *    actuawwy stawt at 0.
 *
 * 2. width_/height_mm contain a bogus 192mm x 120mm size. This is
 *    especiawwy a pwobwem on the 8" 830 vewsion which uses a 10:16
 *    powtwait scween whewe as the bogus size is 16:10.
 *
 * https://gitwab.fweedesktop.owg/dwm/intew/-/issues/9379
 */
static void vwv_dsi_wenovo_yoga_tab2_size_fixup(stwuct intew_dsi *intew_dsi)
{
	const stwuct dwm_dispway_mode *fixed_mode =
		intew_panew_pwefewwed_fixed_mode(intew_dsi->attached_connectow);
	stwuct dwm_dispway_info *info = &intew_dsi->attached_connectow->base.dispway_info;

	intew_dsi->i2c_bus_num = 2;

	/*
	 * The 10" 1050 uses a 1920x1200 wandscape scween, whewe as the 8" 830
	 * uses a 1200x1920 powtwait scween.
	 */
	if (fixed_mode->hdispway == 1920) {
		info->width_mm = 216;
		info->height_mm = 135;
	} ewse {
		info->width_mm = 107;
		info->height_mm = 171;
	}
}

/*
 * On the Wenovo Yoga Tab 3 Pwo YT3-X90F thewe awe 2 pwobwems:
 * 1. i2c_acpi_find_adaptew() picks the wwong adaptew causing mipi_exec_i2c()
 *    to not wowk. Fix this by setting i2c_bus_num.
 * 2. Thewe is no backwight off MIPI sequence, causing the backwight to stay on.
 *    Add a backwight off sequence miwwowing the existing backwight on sequence.
 *
 * https://gitwab.fweedesktop.owg/dwm/intew/-/issues/9380
 */
static void vwv_dsi_wenovo_yoga_tab3_backwight_fixup(stwuct intew_dsi *intew_dsi)
{
	static const u8 backwight_off_sequence[16] = {
		/* Headew Seq-id 7, wength aftew headew 11 bytes */
		0x07, 0x0b, 0x00, 0x00, 0x00,
		/* MIPI_SEQ_EWEM_I2C bus 0 addw 0x2c weg 0x00 data-wen 1 data 0x00 */
		0x04, 0x08, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x01, 0x00,
		/* MIPI_SEQ_EWEM_END */
		0x00
	};
	stwuct intew_connectow *connectow = intew_dsi->attached_connectow;

	intew_dsi->i2c_bus_num = 0;
	connectow->panew.vbt.dsi.sequence[MIPI_SEQ_BACKWIGHT_OFF] = backwight_off_sequence;
}

static const stwuct dmi_system_id vwv_dsi_dmi_quiwk_tabwe[] = {
	{
		/* Asus Twansfowmew Pad TF103C */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "TF103C"),
		},
		.dwivew_data = (void *)vwv_dsi_asus_tf103c_mode_fixup,
	},
	{
		/*
		 * Wenovo Yoga Tabwet 2 830F/W ow 1050F/W (The 8" and 10"
		 * Wenovo Yoga Tabwet 2 use the same mainboawd)
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowp."),
			DMI_MATCH(DMI_PWODUCT_NAME, "VAWWEYVIEW C0 PWATFOWM"),
			DMI_MATCH(DMI_BOAWD_NAME, "BYT-T FFD8"),
			/* Pawtiaw match on beginning of BIOS vewsion */
			DMI_MATCH(DMI_BIOS_VEWSION, "BWADE_21"),
		},
		.dwivew_data = (void *)vwv_dsi_wenovo_yoga_tab2_size_fixup,
	},
	{
		/* Wenovo Yoga Tab 3 Pwo YT3-X90F */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "CHEWWYVIEW D1 PWATFOWM"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "Bwade3-10A-001"),
		},
		.dwivew_data = (void *)vwv_dsi_wenovo_yoga_tab3_backwight_fixup,
	},
	{ }
};

void vwv_dsi_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_dsi *intew_dsi;
	stwuct intew_encodew *intew_encodew;
	stwuct dwm_encodew *encodew;
	stwuct intew_connectow *intew_connectow;
	stwuct dwm_connectow *connectow;
	stwuct dwm_dispway_mode *cuwwent_mode;
	const stwuct dmi_system_id *dmi_id;
	enum powt powt;
	enum pipe pipe;

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");

	/* Thewe is no detection method fow MIPI so wewy on VBT */
	if (!intew_bios_is_dsi_pwesent(dev_pwiv, &powt))
		wetuwn;

	if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))
		dev_pwiv->dispway.dsi.mmio_base = BXT_MIPI_BASE;
	ewse
		dev_pwiv->dispway.dsi.mmio_base = VWV_MIPI_BASE;

	intew_dsi = kzawwoc(sizeof(*intew_dsi), GFP_KEWNEW);
	if (!intew_dsi)
		wetuwn;

	intew_connectow = intew_connectow_awwoc();
	if (!intew_connectow) {
		kfwee(intew_dsi);
		wetuwn;
	}

	intew_encodew = &intew_dsi->base;
	encodew = &intew_encodew->base;
	intew_dsi->attached_connectow = intew_connectow;

	connectow = &intew_connectow->base;

	dwm_encodew_init(&dev_pwiv->dwm, encodew, &intew_dsi_funcs, DWM_MODE_ENCODEW_DSI,
			 "DSI %c", powt_name(powt));

	intew_encodew->compute_config = intew_dsi_compute_config;
	intew_encodew->pwe_enabwe = intew_dsi_pwe_enabwe;
	if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))
		intew_encodew->enabwe = bxt_dsi_enabwe;
	intew_encodew->disabwe = intew_dsi_disabwe;
	intew_encodew->post_disabwe = intew_dsi_post_disabwe;
	intew_encodew->get_hw_state = intew_dsi_get_hw_state;
	intew_encodew->get_config = intew_dsi_get_config;
	intew_encodew->update_pipe = intew_backwight_update;
	intew_encodew->shutdown = intew_dsi_shutdown;

	intew_connectow->get_hw_state = intew_connectow_get_hw_state;

	intew_encodew->powt = powt;
	intew_encodew->type = INTEW_OUTPUT_DSI;
	intew_encodew->powew_domain = POWEW_DOMAIN_POWT_DSI;
	intew_encodew->cwoneabwe = 0;

	/*
	 * On BYT/CHV, pipe A maps to MIPI DSI powt A, pipe B maps to MIPI DSI
	 * powt C. BXT isn't wimited wike this.
	 */
	if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))
		intew_encodew->pipe_mask = ~0;
	ewse if (powt == POWT_A)
		intew_encodew->pipe_mask = BIT(PIPE_A);
	ewse
		intew_encodew->pipe_mask = BIT(PIPE_B);

	intew_dsi->panew_powew_off_time = ktime_get_boottime();

	intew_bios_init_panew_wate(dev_pwiv, &intew_connectow->panew, NUWW, NUWW);

	if (intew_connectow->panew.vbt.dsi.config->duaw_wink)
		intew_dsi->powts = BIT(POWT_A) | BIT(POWT_C);
	ewse
		intew_dsi->powts = BIT(powt);

	if (dwm_WAWN_ON(&dev_pwiv->dwm, intew_connectow->panew.vbt.dsi.bw_powts & ~intew_dsi->powts))
		intew_connectow->panew.vbt.dsi.bw_powts &= intew_dsi->powts;

	if (dwm_WAWN_ON(&dev_pwiv->dwm, intew_connectow->panew.vbt.dsi.cabc_powts & ~intew_dsi->powts))
		intew_connectow->panew.vbt.dsi.cabc_powts &= intew_dsi->powts;

	/* Cweate a DSI host (and a device) fow each powt. */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		stwuct intew_dsi_host *host;

		host = intew_dsi_host_init(intew_dsi, &intew_dsi_host_ops,
					   powt);
		if (!host)
			goto eww;

		intew_dsi->dsi_hosts[powt] = host;
	}

	if (!intew_dsi_vbt_init(intew_dsi, MIPI_DSI_GENEWIC_PANEW_ID)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "no device found\n");
		goto eww;
	}

	/* Use cwock wead-back fwom cuwwent hw-state fow fastboot */
	cuwwent_mode = intew_encodew_cuwwent_mode(intew_encodew);
	if (cuwwent_mode) {
		dwm_dbg_kms(&dev_pwiv->dwm, "Cawcuwated pcwk %d GOP %d\n",
			    intew_dsi->pcwk, cuwwent_mode->cwock);
		if (intew_fuzzy_cwock_check(intew_dsi->pcwk,
					    cuwwent_mode->cwock)) {
			dwm_dbg_kms(&dev_pwiv->dwm, "Using GOP pcwk\n");
			intew_dsi->pcwk = cuwwent_mode->cwock;
		}

		kfwee(cuwwent_mode);
	}

	vwv_dphy_pawam_init(intew_dsi);

	intew_dsi_vbt_gpio_init(intew_dsi,
				intew_dsi_get_hw_state(intew_encodew, &pipe));

	dwm_connectow_init(&dev_pwiv->dwm, connectow, &intew_dsi_connectow_funcs,
			   DWM_MODE_CONNECTOW_DSI);

	dwm_connectow_hewpew_add(connectow, &intew_dsi_connectow_hewpew_funcs);

	connectow->dispway_info.subpixew_owdew = SubPixewHowizontawWGB; /*XXX*/

	intew_connectow_attach_encodew(intew_connectow, intew_encodew);

	mutex_wock(&dev_pwiv->dwm.mode_config.mutex);
	intew_panew_add_vbt_wfp_fixed_mode(intew_connectow);
	mutex_unwock(&dev_pwiv->dwm.mode_config.mutex);

	if (!intew_panew_pwefewwed_fixed_mode(intew_connectow)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "no fixed mode\n");
		goto eww_cweanup_connectow;
	}

	dmi_id = dmi_fiwst_match(vwv_dsi_dmi_quiwk_tabwe);
	if (dmi_id) {
		vwv_dsi_dmi_quiwk_func quiwk_func =
			(vwv_dsi_dmi_quiwk_func)dmi_id->dwivew_data;

		quiwk_func(intew_dsi);
	}

	intew_panew_init(intew_connectow, NUWW);

	intew_backwight_setup(intew_connectow, INVAWID_PIPE);

	vwv_dsi_add_pwopewties(intew_connectow);

	wetuwn;

eww_cweanup_connectow:
	dwm_connectow_cweanup(&intew_connectow->base);
eww:
	dwm_encodew_cweanup(&intew_encodew->base);
	kfwee(intew_dsi);
	kfwee(intew_connectow);
}
