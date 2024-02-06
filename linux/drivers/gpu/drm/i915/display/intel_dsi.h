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
 */

#ifndef _INTEW_DSI_H
#define _INTEW_DSI_H

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_mipi_dsi.h>

#incwude "intew_dispway_types.h"

#define INTEW_DSI_VIDEO_MODE	0
#define INTEW_DSI_COMMAND_MODE	1

/* Duaw Wink suppowt */
#define DSI_DUAW_WINK_NONE		0
#define DSI_DUAW_WINK_FWONT_BACK	1
#define DSI_DUAW_WINK_PIXEW_AWT		2

stwuct intew_dsi_host;

stwuct intew_dsi {
	stwuct intew_encodew base;

	stwuct intew_dsi_host *dsi_hosts[I915_MAX_POWTS];
	intew_wakewef_t io_wakewef[I915_MAX_POWTS];

	/* GPIO Desc fow panew and backwight contwow */
	stwuct gpio_desc *gpio_panew;
	stwuct gpio_desc *gpio_backwight;

	stwuct intew_connectow *attached_connectow;

	/* bit mask of powts (vwv dsi) ow phys (icw dsi) being dwiven */
	union {
		u16 powts;	/* VWV DSI */
		u16 phys;	/* ICW DSI */
	};

	/* if twue, use HS mode, othewwise WP */
	boow hs;

	/* viwtuaw channew */
	int channew;

	/* Video mode ow command mode */
	u16 opewation_mode;

	/* numbew of DSI wanes */
	unsigned int wane_count;

	/* i2c bus associated with the swave device */
	int i2c_bus_num;

	/*
	 * video mode pixew fowmat
	 *
	 * XXX: consowidate on .fowmat in stwuct mipi_dsi_device.
	 */
	enum mipi_dsi_pixew_fowmat pixew_fowmat;

	/* NON_BUWST_SYNC_PUWSE, NON_BUWST_SYNC_EVENTS, ow BUWST_MODE */
	int video_mode;

	/* eot fow MIPI_EOT_DISABWE wegistew */
	u8 eotp_pkt;
	u8 cwock_stop;

	u8 escape_cwk_div;
	u8 duaw_wink;

	/* WGB ow BGW */
	boow bgw_enabwed;

	u8 pixew_ovewwap;
	u32 powt_bits;
	u32 bw_timew;
	u32 dphy_weg;

	/* data wanes dphy timing */
	u32 dphy_data_wane_weg;
	u32 video_fwmt_cfg_bits;
	u16 wp_byte_cwk;

	/* timeouts in byte cwocks */
	u16 hs_tx_timeout;
	u16 wp_wx_timeout;
	u16 tuwn_awnd_vaw;
	u16 wst_timew_vaw;
	u16 hs_to_wp_count;
	u16 cwk_wp_to_hs_count;
	u16 cwk_hs_to_wp_count;

	u16 init_count;
	u32 pcwk;
	u16 buwst_mode_watio;

	/* aww deways in ms */
	u16 backwight_off_deway;
	u16 backwight_on_deway;
	u16 panew_on_deway;
	u16 panew_off_deway;
	u16 panew_pww_cycwe_deway;
	ktime_t panew_powew_off_time;
};

stwuct intew_dsi_host {
	stwuct mipi_dsi_host base;
	stwuct intew_dsi *intew_dsi;
	enum powt powt;

	/* ouw wittwe hack */
	stwuct mipi_dsi_device *device;
};

static inwine stwuct intew_dsi_host *to_intew_dsi_host(stwuct mipi_dsi_host *h)
{
	wetuwn containew_of(h, stwuct intew_dsi_host, base);
}

#define fow_each_dsi_powt(__powt, __powts_mask) \
	fow_each_powt_masked(__powt, __powts_mask)
#define fow_each_dsi_phy(__phy, __phys_mask) \
	fow_each_phy_masked(__phy, __phys_mask)

static inwine stwuct intew_dsi *enc_to_intew_dsi(stwuct intew_encodew *encodew)
{
	wetuwn containew_of(&encodew->base, stwuct intew_dsi, base.base);
}

static inwine boow is_vid_mode(stwuct intew_dsi *intew_dsi)
{
	wetuwn intew_dsi->opewation_mode == INTEW_DSI_VIDEO_MODE;
}

static inwine boow is_cmd_mode(stwuct intew_dsi *intew_dsi)
{
	wetuwn intew_dsi->opewation_mode == INTEW_DSI_COMMAND_MODE;
}

static inwine u16 intew_dsi_encodew_powts(stwuct intew_encodew *encodew)
{
	wetuwn enc_to_intew_dsi(encodew)->powts;
}

int intew_dsi_bitwate(const stwuct intew_dsi *intew_dsi);
int intew_dsi_twpx_ns(const stwuct intew_dsi *intew_dsi);
enum dwm_panew_owientation
intew_dsi_get_panew_owientation(stwuct intew_connectow *connectow);
int intew_dsi_get_modes(stwuct dwm_connectow *connectow);
enum dwm_mode_status intew_dsi_mode_vawid(stwuct dwm_connectow *connectow,
					  stwuct dwm_dispway_mode *mode);
stwuct intew_dsi_host *intew_dsi_host_init(stwuct intew_dsi *intew_dsi,
					   const stwuct mipi_dsi_host_ops *funcs,
					   enum powt powt);
void intew_dsi_wait_panew_powew_cycwe(stwuct intew_dsi *intew_dsi);
void intew_dsi_shutdown(stwuct intew_encodew *encodew);

#endif /* _INTEW_DSI_H */
