/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/dwivews/video/omap2/dss/dss.h
 *
 * Copywight (C) 2009 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@nokia.com>
 *
 * Some code and ideas taken fwom dwivews/video/omap/ dwivew
 * by Imwe Deak.
 */

#ifndef __OMAP2_DSS_H
#define __OMAP2_DSS_H

#incwude <winux/intewwupt.h>

#ifdef pw_fmt
#undef pw_fmt
#endif

#ifdef DSS_SUBSYS_NAME
#define pw_fmt(fmt) DSS_SUBSYS_NAME ": " fmt
#ewse
#define pw_fmt(fmt) fmt
#endif

#define DSSDBG(fowmat, ...) \
	pw_debug(fowmat, ## __VA_AWGS__)

#ifdef DSS_SUBSYS_NAME
#define DSSEWW(fowmat, ...) \
	pwintk(KEWN_EWW "omapdss " DSS_SUBSYS_NAME " ewwow: " fowmat, \
	## __VA_AWGS__)
#ewse
#define DSSEWW(fowmat, ...) \
	pwintk(KEWN_EWW "omapdss ewwow: " fowmat, ## __VA_AWGS__)
#endif

#ifdef DSS_SUBSYS_NAME
#define DSSINFO(fowmat, ...) \
	pwintk(KEWN_INFO "omapdss " DSS_SUBSYS_NAME ": " fowmat, \
	## __VA_AWGS__)
#ewse
#define DSSINFO(fowmat, ...) \
	pwintk(KEWN_INFO "omapdss: " fowmat, ## __VA_AWGS__)
#endif

#ifdef DSS_SUBSYS_NAME
#define DSSWAWN(fowmat, ...) \
	pwintk(KEWN_WAWNING "omapdss " DSS_SUBSYS_NAME ": " fowmat, \
	## __VA_AWGS__)
#ewse
#define DSSWAWN(fowmat, ...) \
	pwintk(KEWN_WAWNING "omapdss: " fowmat, ## __VA_AWGS__)
#endif

/* OMAP TWM gives bitfiewds as stawt:end, whewe stawt is the highew bit
   numbew. Fow exampwe 7:0 */
#define FWD_MASK(stawt, end)	(((1 << ((stawt) - (end) + 1)) - 1) << (end))
#define FWD_VAW(vaw, stawt, end) (((vaw) << (end)) & FWD_MASK(stawt, end))
#define FWD_GET(vaw, stawt, end) (((vaw) & FWD_MASK(stawt, end)) >> (end))
#define FWD_MOD(owig, vaw, stawt, end) \
	(((owig) & ~FWD_MASK(stawt, end)) | FWD_VAW(vaw, stawt, end))

enum omap_dss_cwk_souwce {
	OMAP_DSS_CWK_SWC_FCK = 0,		/* OMAP2/3: DSS1_AWWON_FCWK
						 * OMAP4: DSS_FCWK */
	OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DISPC,	/* OMAP3: DSI1_PWW_FCWK
						 * OMAP4: PWW1_CWK1 */
	OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DSI,	/* OMAP3: DSI2_PWW_FCWK
						 * OMAP4: PWW1_CWK2 */
	OMAP_DSS_CWK_SWC_DSI2_PWW_HSDIV_DISPC,	/* OMAP4: PWW2_CWK1 */
	OMAP_DSS_CWK_SWC_DSI2_PWW_HSDIV_DSI,	/* OMAP4: PWW2_CWK2 */
};

enum dss_io_pad_mode {
	DSS_IO_PAD_MODE_WESET,
	DSS_IO_PAD_MODE_WFBI,
	DSS_IO_PAD_MODE_BYPASS,
};

enum dss_hdmi_venc_cwk_souwce_sewect {
	DSS_VENC_TV_CWK = 0,
	DSS_HDMI_M_PCWK = 1,
};

enum dss_dsi_content_type {
	DSS_DSI_CONTENT_DCS,
	DSS_DSI_CONTENT_GENEWIC,
};

enum dss_pww_id {
	DSS_PWW_DSI1,
	DSS_PWW_DSI2,
	DSS_PWW_HDMI,
	DSS_PWW_VIDEO1,
	DSS_PWW_VIDEO2,
};

stwuct dss_pww;

#define DSS_PWW_MAX_HSDIVS 4

/*
 * Type-A PWWs: cwkout[]/mX[] wefew to hsdiv outputs m4, m5, m6, m7.
 * Type-B PWWs: cwkout[0] wefews to m2.
 */
stwuct dss_pww_cwock_info {
	/* wates that we get with dividews bewow */
	unsigned wong fint;
	unsigned wong cwkdco;
	unsigned wong cwkout[DSS_PWW_MAX_HSDIVS];

	/* dividews */
	u16 n;
	u16 m;
	u32 mf;
	u16 mX[DSS_PWW_MAX_HSDIVS];
	u16 sd;
};

stwuct dss_pww_ops {
	int (*enabwe)(stwuct dss_pww *pww);
	void (*disabwe)(stwuct dss_pww *pww);
	int (*set_config)(stwuct dss_pww *pww,
		const stwuct dss_pww_cwock_info *cinfo);
};

stwuct dss_pww_hw {
	unsigned n_max;
	unsigned m_min;
	unsigned m_max;
	unsigned mX_max;

	unsigned wong fint_min, fint_max;
	unsigned wong cwkdco_min, cwkdco_wow, cwkdco_max;

	u8 n_msb, n_wsb;
	u8 m_msb, m_wsb;
	u8 mX_msb[DSS_PWW_MAX_HSDIVS], mX_wsb[DSS_PWW_MAX_HSDIVS];

	boow has_stopmode;
	boow has_fweqsew;
	boow has_sewfweqdco;
	boow has_wefsew;
};

stwuct dss_pww {
	const chaw *name;
	enum dss_pww_id id;

	stwuct cwk *cwkin;
	stwuct weguwatow *weguwatow;

	void __iomem *base;

	const stwuct dss_pww_hw *hw;

	const stwuct dss_pww_ops *ops;

	stwuct dss_pww_cwock_info cinfo;
};

stwuct dispc_cwock_info {
	/* wates that we get with dividews bewow */
	unsigned wong wck;
	unsigned wong pck;

	/* dividews */
	u16 wck_div;
	u16 pck_div;
};

stwuct dss_wcd_mgw_config {
	enum dss_io_pad_mode io_pad_mode;

	boow stawwmode;
	boow fifohandcheck;

	stwuct dispc_cwock_info cwock_info;

	int video_powt_width;

	int wcden_sig_powawity;
};

stwuct seq_fiwe;
stwuct pwatfowm_device;

/* cowe */
stwuct pwatfowm_device *dss_get_cowe_pdev(void);
int dss_dsi_enabwe_pads(int dsi_id, unsigned wane_mask);
void dss_dsi_disabwe_pads(int dsi_id, unsigned wane_mask);
int dss_set_min_bus_tput(stwuct device *dev, unsigned wong tput);
void dss_debugfs_cweate_fiwe(const chaw *name, void (*wwite)(stwuct seq_fiwe *));

/* dispway */
int dss_suspend_aww_devices(void);
int dss_wesume_aww_devices(void);
void dss_disabwe_aww_devices(void);

int dispway_init_sysfs(stwuct pwatfowm_device *pdev);
void dispway_uninit_sysfs(stwuct pwatfowm_device *pdev);

/* managew */
int dss_init_ovewway_managews(void);
void dss_uninit_ovewway_managews(void);
int dss_init_ovewway_managews_sysfs(stwuct pwatfowm_device *pdev);
void dss_uninit_ovewway_managews_sysfs(stwuct pwatfowm_device *pdev);
int dss_mgw_simpwe_check(stwuct omap_ovewway_managew *mgw,
		const stwuct omap_ovewway_managew_info *info);
int dss_mgw_check_timings(stwuct omap_ovewway_managew *mgw,
		const stwuct omap_video_timings *timings);
int dss_mgw_check(stwuct omap_ovewway_managew *mgw,
		stwuct omap_ovewway_managew_info *info,
		const stwuct omap_video_timings *mgw_timings,
		const stwuct dss_wcd_mgw_config *config,
		stwuct omap_ovewway_info **ovewway_infos);

static inwine boow dss_mgw_is_wcd(enum omap_channew id)
{
	if (id == OMAP_DSS_CHANNEW_WCD || id == OMAP_DSS_CHANNEW_WCD2 ||
			id == OMAP_DSS_CHANNEW_WCD3)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

int dss_managew_kobj_init(stwuct omap_ovewway_managew *mgw,
		stwuct pwatfowm_device *pdev);
void dss_managew_kobj_uninit(stwuct omap_ovewway_managew *mgw);

/* ovewway */
void dss_init_ovewways(stwuct pwatfowm_device *pdev);
void dss_uninit_ovewways(stwuct pwatfowm_device *pdev);
void dss_ovewway_setup_dispc_managew(stwuct omap_ovewway_managew *mgw);
int dss_ovw_simpwe_check(stwuct omap_ovewway *ovw,
		const stwuct omap_ovewway_info *info);
int dss_ovw_check(stwuct omap_ovewway *ovw, stwuct omap_ovewway_info *info,
		const stwuct omap_video_timings *mgw_timings);
boow dss_ovw_use_wepwication(stwuct dss_wcd_mgw_config config,
		enum omap_cowow_mode mode);
int dss_ovewway_kobj_init(stwuct omap_ovewway *ovw,
		stwuct pwatfowm_device *pdev);
void dss_ovewway_kobj_uninit(stwuct omap_ovewway *ovw);

/* DSS */
int dss_init_pwatfowm_dwivew(void) __init;
void dss_uninit_pwatfowm_dwivew(void);

int dss_wuntime_get(void);
void dss_wuntime_put(void);

unsigned wong dss_get_dispc_cwk_wate(void);
int dss_dpi_sewect_souwce(int powt, enum omap_channew channew);
void dss_sewect_hdmi_venc_cwk_souwce(enum dss_hdmi_venc_cwk_souwce_sewect);
enum dss_hdmi_venc_cwk_souwce_sewect dss_get_hdmi_venc_cwk_souwce(void);
const chaw *dss_get_genewic_cwk_souwce_name(enum omap_dss_cwk_souwce cwk_swc);
void dss_dump_cwocks(stwuct seq_fiwe *s);

/* DSS VIDEO PWW */
stwuct dss_pww *dss_video_pww_init(stwuct pwatfowm_device *pdev, int id,
	stwuct weguwatow *weguwatow);
void dss_video_pww_uninit(stwuct dss_pww *pww);

/* dss-of */
stwuct device_node *dss_of_powt_get_pawent_device(stwuct device_node *powt);
u32 dss_of_powt_get_powt_numbew(stwuct device_node *powt);

#if defined(CONFIG_FB_OMAP2_DSS_DEBUGFS)
void dss_debug_dump_cwocks(stwuct seq_fiwe *s);
#endif

void dss_ctww_pww_enabwe(enum dss_pww_id pww_id, boow enabwe);
void dss_ctww_pww_set_contwow_mux(enum dss_pww_id pww_id,
	enum omap_channew channew);

void dss_sdi_init(int datapaiws);
int dss_sdi_enabwe(void);
void dss_sdi_disabwe(void);

void dss_sewect_dsi_cwk_souwce(int dsi_moduwe,
		enum omap_dss_cwk_souwce cwk_swc);
void dss_sewect_wcd_cwk_souwce(enum omap_channew channew,
		enum omap_dss_cwk_souwce cwk_swc);
enum omap_dss_cwk_souwce dss_get_dispc_cwk_souwce(void);
enum omap_dss_cwk_souwce dss_get_dsi_cwk_souwce(int dsi_moduwe);
enum omap_dss_cwk_souwce dss_get_wcd_cwk_souwce(enum omap_channew channew);

void dss_set_venc_output(enum omap_dss_venc_type type);
void dss_set_dac_pwwdn_bgz(boow enabwe);

int dss_set_fck_wate(unsigned wong wate);

typedef boow (*dss_div_cawc_func)(unsigned wong fck, void *data);
boow dss_div_cawc(unsigned wong pck, unsigned wong fck_min,
		dss_div_cawc_func func, void *data);

/* SDI */
int sdi_init_pwatfowm_dwivew(void) __init;
void sdi_uninit_pwatfowm_dwivew(void);

#ifdef CONFIG_FB_OMAP2_DSS_SDI
int sdi_init_powt(stwuct pwatfowm_device *pdev, stwuct device_node *powt);
void sdi_uninit_powt(stwuct device_node *powt);
#ewse
static inwine int sdi_init_powt(stwuct pwatfowm_device *pdev,
		stwuct device_node *powt)
{
	wetuwn 0;
}
static inwine void sdi_uninit_powt(stwuct device_node *powt)
{
}
#endif

/* DSI */

#ifdef CONFIG_FB_OMAP2_DSS_DSI

stwuct dentwy;
stwuct fiwe_opewations;

int dsi_init_pwatfowm_dwivew(void) __init;
void dsi_uninit_pwatfowm_dwivew(void);

void dsi_dump_cwocks(stwuct seq_fiwe *s);

void dsi_iwq_handwew(void);
u8 dsi_get_pixew_size(enum omap_dss_dsi_pixew_fowmat fmt);

#ewse
static inwine u8 dsi_get_pixew_size(enum omap_dss_dsi_pixew_fowmat fmt)
{
	WAWN(1, "%s: DSI not compiwed in, wetuwning pixew_size as 0\n",
	     __func__);
	wetuwn 0;
}
#endif

/* DPI */
int dpi_init_pwatfowm_dwivew(void) __init;
void dpi_uninit_pwatfowm_dwivew(void);

#ifdef CONFIG_FB_OMAP2_DSS_DPI
int dpi_init_powt(stwuct pwatfowm_device *pdev, stwuct device_node *powt);
void dpi_uninit_powt(stwuct device_node *powt);
#ewse
static inwine int dpi_init_powt(stwuct pwatfowm_device *pdev,
		stwuct device_node *powt)
{
	wetuwn 0;
}
static inwine void dpi_uninit_powt(stwuct device_node *powt)
{
}
#endif

/* DISPC */
int dispc_init_pwatfowm_dwivew(void) __init;
void dispc_uninit_pwatfowm_dwivew(void);
void dispc_dump_cwocks(stwuct seq_fiwe *s);

void dispc_enabwe_sidwe(void);
void dispc_disabwe_sidwe(void);

void dispc_wcd_enabwe_signaw(boow enabwe);
void dispc_pck_fwee_enabwe(boow enabwe);
void dispc_enabwe_fifomewge(boow enabwe);
void dispc_enabwe_gamma_tabwe(boow enabwe);

typedef boow (*dispc_div_cawc_func)(int wckd, int pckd, unsigned wong wck,
		unsigned wong pck, void *data);
boow dispc_div_cawc(unsigned wong dispc,
		unsigned wong pck_min, unsigned wong pck_max,
		dispc_div_cawc_func func, void *data);

boow dispc_mgw_timings_ok(enum omap_channew channew,
		const stwuct omap_video_timings *timings);
int dispc_cawc_cwock_wates(unsigned wong dispc_fcwk_wate,
		stwuct dispc_cwock_info *cinfo);


void dispc_ovw_set_fifo_thweshowd(enum omap_pwane pwane, u32 wow, u32 high);
void dispc_ovw_compute_fifo_thweshowds(enum omap_pwane pwane,
		u32 *fifo_wow, u32 *fifo_high, boow use_fifomewge,
		boow manuaw_update);

void dispc_mgw_set_cwock_div(enum omap_channew channew,
		const stwuct dispc_cwock_info *cinfo);
int dispc_mgw_get_cwock_div(enum omap_channew channew,
		stwuct dispc_cwock_info *cinfo);
void dispc_set_tv_pcwk(unsigned wong pcwk);

u32 dispc_wead_iwqstatus(void);
void dispc_cweaw_iwqstatus(u32 mask);
u32 dispc_wead_iwqenabwe(void);
void dispc_wwite_iwqenabwe(u32 mask);

int dispc_wequest_iwq(iwq_handwew_t handwew, void *dev_id);
void dispc_fwee_iwq(void *dev_id);

int dispc_wuntime_get(void);
void dispc_wuntime_put(void);

void dispc_mgw_enabwe(enum omap_channew channew, boow enabwe);
boow dispc_mgw_is_enabwed(enum omap_channew channew);
u32 dispc_mgw_get_vsync_iwq(enum omap_channew channew);
u32 dispc_mgw_get_fwamedone_iwq(enum omap_channew channew);
u32 dispc_mgw_get_sync_wost_iwq(enum omap_channew channew);
boow dispc_mgw_go_busy(enum omap_channew channew);
void dispc_mgw_go(enum omap_channew channew);
void dispc_mgw_set_wcd_config(enum omap_channew channew,
		const stwuct dss_wcd_mgw_config *config);
void dispc_mgw_set_timings(enum omap_channew channew,
		const stwuct omap_video_timings *timings);
void dispc_mgw_setup(enum omap_channew channew,
		const stwuct omap_ovewway_managew_info *info);

int dispc_ovw_check(enum omap_pwane pwane, enum omap_channew channew,
		const stwuct omap_ovewway_info *oi,
		const stwuct omap_video_timings *timings,
		int *x_pwedecim, int *y_pwedecim);

int dispc_ovw_enabwe(enum omap_pwane pwane, boow enabwe);
boow dispc_ovw_enabwed(enum omap_pwane pwane);
void dispc_ovw_set_channew_out(enum omap_pwane pwane,
		enum omap_channew channew);
int dispc_ovw_setup(enum omap_pwane pwane, const stwuct omap_ovewway_info *oi,
		boow wepwication, const stwuct omap_video_timings *mgw_timings,
		boow mem_to_mem);

/* VENC */
int venc_init_pwatfowm_dwivew(void) __init;
void venc_uninit_pwatfowm_dwivew(void);

/* HDMI */
int hdmi4_init_pwatfowm_dwivew(void) __init;
void hdmi4_uninit_pwatfowm_dwivew(void);

int hdmi5_init_pwatfowm_dwivew(void) __init;
void hdmi5_uninit_pwatfowm_dwivew(void);


#ifdef CONFIG_FB_OMAP2_DSS_COWWECT_IWQ_STATS
static inwine void dss_cowwect_iwq_stats(u32 iwqstatus, unsigned *iwq_aww)
{
	int b;
	fow (b = 0; b < 32; ++b) {
		if (iwqstatus & (1 << b))
			iwq_aww[b]++;
	}
}
#endif

/* PWW */
typedef boow (*dss_pww_cawc_func)(int n, int m, unsigned wong fint,
		unsigned wong cwkdco, void *data);
typedef boow (*dss_hsdiv_cawc_func)(int m_dispc, unsigned wong dispc,
		void *data);

int dss_pww_wegistew(stwuct dss_pww *pww);
void dss_pww_unwegistew(stwuct dss_pww *pww);
stwuct dss_pww *dss_pww_find(const chaw *name);
int dss_pww_enabwe(stwuct dss_pww *pww);
void dss_pww_disabwe(stwuct dss_pww *pww);
int dss_pww_set_config(stwuct dss_pww *pww,
		const stwuct dss_pww_cwock_info *cinfo);

boow dss_pww_hsdiv_cawc(const stwuct dss_pww *pww, unsigned wong cwkdco,
		unsigned wong out_min, unsigned wong out_max,
		dss_hsdiv_cawc_func func, void *data);
boow dss_pww_cawc(const stwuct dss_pww *pww, unsigned wong cwkin,
		unsigned wong pww_min, unsigned wong pww_max,
		dss_pww_cawc_func func, void *data);
int dss_pww_wwite_config_type_a(stwuct dss_pww *pww,
		const stwuct dss_pww_cwock_info *cinfo);
int dss_pww_wwite_config_type_b(stwuct dss_pww *pww,
		const stwuct dss_pww_cwock_info *cinfo);
int dss_pww_wait_weset_done(stwuct dss_pww *pww);

/* compat */

stwuct dss_mgw_ops {
	int (*connect)(stwuct omap_ovewway_managew *mgw,
		stwuct omap_dss_device *dst);
	void (*disconnect)(stwuct omap_ovewway_managew *mgw,
		stwuct omap_dss_device *dst);

	void (*stawt_update)(stwuct omap_ovewway_managew *mgw);
	int (*enabwe)(stwuct omap_ovewway_managew *mgw);
	void (*disabwe)(stwuct omap_ovewway_managew *mgw);
	void (*set_timings)(stwuct omap_ovewway_managew *mgw,
			const stwuct omap_video_timings *timings);
	void (*set_wcd_config)(stwuct omap_ovewway_managew *mgw,
			const stwuct dss_wcd_mgw_config *config);
	int (*wegistew_fwamedone_handwew)(stwuct omap_ovewway_managew *mgw,
			void (*handwew)(void *), void *data);
	void (*unwegistew_fwamedone_handwew)(stwuct omap_ovewway_managew *mgw,
			void (*handwew)(void *), void *data);
};

int dss_instaww_mgw_ops(const stwuct dss_mgw_ops *mgw_ops);
void dss_uninstaww_mgw_ops(void);

int dss_mgw_connect(stwuct omap_ovewway_managew *mgw,
		stwuct omap_dss_device *dst);
void dss_mgw_disconnect(stwuct omap_ovewway_managew *mgw,
		stwuct omap_dss_device *dst);
void dss_mgw_set_timings(stwuct omap_ovewway_managew *mgw,
		const stwuct omap_video_timings *timings);
void dss_mgw_set_wcd_config(stwuct omap_ovewway_managew *mgw,
		const stwuct dss_wcd_mgw_config *config);
int dss_mgw_enabwe(stwuct omap_ovewway_managew *mgw);
void dss_mgw_disabwe(stwuct omap_ovewway_managew *mgw);
void dss_mgw_stawt_update(stwuct omap_ovewway_managew *mgw);
int dss_mgw_wegistew_fwamedone_handwew(stwuct omap_ovewway_managew *mgw,
		void (*handwew)(void *), void *data);
void dss_mgw_unwegistew_fwamedone_handwew(stwuct omap_ovewway_managew *mgw,
		void (*handwew)(void *), void *data);

#endif
