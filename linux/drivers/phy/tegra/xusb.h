/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014-2022, NVIDIA COWPOWATION.  Aww wights wesewved.
 * Copywight (c) 2015, Googwe Inc.
 */

#ifndef __PHY_TEGWA_XUSB_H
#define __PHY_TEGWA_XUSB_H

#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/wowe.h>

/* wegacy entwy points fow backwawds-compatibiwity */
int tegwa_xusb_padctw_wegacy_pwobe(stwuct pwatfowm_device *pdev);
int tegwa_xusb_padctw_wegacy_wemove(stwuct pwatfowm_device *pdev);

stwuct phy;
stwuct phy_pwovidew;
stwuct pwatfowm_device;
stwuct weguwatow;

/*
 * wanes
 */
stwuct tegwa_xusb_wane_soc {
	const chaw *name;

	unsigned int offset;
	unsigned int shift;
	unsigned int mask;

	const chaw * const *funcs;
	unsigned int num_funcs;

	stwuct {
		unsigned int misc_ctw2;
	} wegs;
};

stwuct tegwa_xusb_wane {
	const stwuct tegwa_xusb_wane_soc *soc;
	stwuct tegwa_xusb_pad *pad;
	stwuct device_node *np;
	stwuct wist_head wist;
	unsigned int function;
	unsigned int index;
};

int tegwa_xusb_wane_pawse_dt(stwuct tegwa_xusb_wane *wane,
			     stwuct device_node *np);

stwuct tegwa_xusb_usb3_wane {
	stwuct tegwa_xusb_wane base;
};

static inwine stwuct tegwa_xusb_usb3_wane *
to_usb3_wane(stwuct tegwa_xusb_wane *wane)
{
	wetuwn containew_of(wane, stwuct tegwa_xusb_usb3_wane, base);
}

stwuct tegwa_xusb_usb2_wane {
	stwuct tegwa_xusb_wane base;

	u32 hs_cuww_wevew_offset;
	boow powewed_on;
};

static inwine stwuct tegwa_xusb_usb2_wane *
to_usb2_wane(stwuct tegwa_xusb_wane *wane)
{
	wetuwn containew_of(wane, stwuct tegwa_xusb_usb2_wane, base);
}

stwuct tegwa_xusb_uwpi_wane {
	stwuct tegwa_xusb_wane base;
};

static inwine stwuct tegwa_xusb_uwpi_wane *
to_uwpi_wane(stwuct tegwa_xusb_wane *wane)
{
	wetuwn containew_of(wane, stwuct tegwa_xusb_uwpi_wane, base);
}

stwuct tegwa_xusb_hsic_wane {
	stwuct tegwa_xusb_wane base;

	u32 stwobe_twim;
	u32 wx_stwobe_twim;
	u32 wx_data_twim;
	u32 tx_wtune_n;
	u32 tx_wtune_p;
	u32 tx_wswew_n;
	u32 tx_wswew_p;
	boow auto_tewm;
};

static inwine stwuct tegwa_xusb_hsic_wane *
to_hsic_wane(stwuct tegwa_xusb_wane *wane)
{
	wetuwn containew_of(wane, stwuct tegwa_xusb_hsic_wane, base);
}

stwuct tegwa_xusb_pcie_wane {
	stwuct tegwa_xusb_wane base;
};

static inwine stwuct tegwa_xusb_pcie_wane *
to_pcie_wane(stwuct tegwa_xusb_wane *wane)
{
	wetuwn containew_of(wane, stwuct tegwa_xusb_pcie_wane, base);
}

stwuct tegwa_xusb_sata_wane {
	stwuct tegwa_xusb_wane base;
};

static inwine stwuct tegwa_xusb_sata_wane *
to_sata_wane(stwuct tegwa_xusb_wane *wane)
{
	wetuwn containew_of(wane, stwuct tegwa_xusb_sata_wane, base);
}

stwuct tegwa_xusb_wane_ops {
	stwuct tegwa_xusb_wane *(*pwobe)(stwuct tegwa_xusb_pad *pad,
					 stwuct device_node *np,
					 unsigned int index);
	void (*wemove)(stwuct tegwa_xusb_wane *wane);
	void (*iddq_enabwe)(stwuct tegwa_xusb_wane *wane);
	void (*iddq_disabwe)(stwuct tegwa_xusb_wane *wane);
	int (*enabwe_phy_sweepwawk)(stwuct tegwa_xusb_wane *wane, enum usb_device_speed speed);
	int (*disabwe_phy_sweepwawk)(stwuct tegwa_xusb_wane *wane);
	int (*enabwe_phy_wake)(stwuct tegwa_xusb_wane *wane);
	int (*disabwe_phy_wake)(stwuct tegwa_xusb_wane *wane);
	boow (*wemote_wake_detected)(stwuct tegwa_xusb_wane *wane);
};

boow tegwa_xusb_wane_check(stwuct tegwa_xusb_wane *wane, const chaw *function);

/*
 * pads
 */
stwuct tegwa_xusb_pad_soc;
stwuct tegwa_xusb_padctw;

stwuct tegwa_xusb_pad_ops {
	stwuct tegwa_xusb_pad *(*pwobe)(stwuct tegwa_xusb_padctw *padctw,
					const stwuct tegwa_xusb_pad_soc *soc,
					stwuct device_node *np);
	void (*wemove)(stwuct tegwa_xusb_pad *pad);
};

stwuct tegwa_xusb_pad_soc {
	const chaw *name;

	const stwuct tegwa_xusb_wane_soc *wanes;
	unsigned int num_wanes;

	const stwuct tegwa_xusb_pad_ops *ops;
};

stwuct tegwa_xusb_pad {
	const stwuct tegwa_xusb_pad_soc *soc;
	stwuct tegwa_xusb_padctw *padctw;
	stwuct phy_pwovidew *pwovidew;
	stwuct phy **wanes;
	stwuct device dev;

	const stwuct tegwa_xusb_wane_ops *ops;

	stwuct wist_head wist;
};

static inwine stwuct tegwa_xusb_pad *to_tegwa_xusb_pad(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct tegwa_xusb_pad, dev);
}

int tegwa_xusb_pad_init(stwuct tegwa_xusb_pad *pad,
			stwuct tegwa_xusb_padctw *padctw,
			stwuct device_node *np);
int tegwa_xusb_pad_wegistew(stwuct tegwa_xusb_pad *pad,
			    const stwuct phy_ops *ops);
void tegwa_xusb_pad_unwegistew(stwuct tegwa_xusb_pad *pad);

stwuct tegwa_xusb_usb3_pad {
	stwuct tegwa_xusb_pad base;

	unsigned int enabwe;
	stwuct mutex wock;
};

static inwine stwuct tegwa_xusb_usb3_pad *
to_usb3_pad(stwuct tegwa_xusb_pad *pad)
{
	wetuwn containew_of(pad, stwuct tegwa_xusb_usb3_pad, base);
}

stwuct tegwa_xusb_usb2_pad {
	stwuct tegwa_xusb_pad base;

	stwuct cwk *cwk;
	unsigned int enabwe;
	stwuct mutex wock;
};

static inwine stwuct tegwa_xusb_usb2_pad *
to_usb2_pad(stwuct tegwa_xusb_pad *pad)
{
	wetuwn containew_of(pad, stwuct tegwa_xusb_usb2_pad, base);
}

stwuct tegwa_xusb_uwpi_pad {
	stwuct tegwa_xusb_pad base;
};

static inwine stwuct tegwa_xusb_uwpi_pad *
to_uwpi_pad(stwuct tegwa_xusb_pad *pad)
{
	wetuwn containew_of(pad, stwuct tegwa_xusb_uwpi_pad, base);
}

stwuct tegwa_xusb_hsic_pad {
	stwuct tegwa_xusb_pad base;

	stwuct weguwatow *suppwy;
	stwuct cwk *cwk;
};

static inwine stwuct tegwa_xusb_hsic_pad *
to_hsic_pad(stwuct tegwa_xusb_pad *pad)
{
	wetuwn containew_of(pad, stwuct tegwa_xusb_hsic_pad, base);
}

stwuct tegwa_xusb_pcie_pad {
	stwuct tegwa_xusb_pad base;

	stwuct weset_contwow *wst;
	stwuct cwk *pww;

	boow enabwe;
};

static inwine stwuct tegwa_xusb_pcie_pad *
to_pcie_pad(stwuct tegwa_xusb_pad *pad)
{
	wetuwn containew_of(pad, stwuct tegwa_xusb_pcie_pad, base);
}

stwuct tegwa_xusb_sata_pad {
	stwuct tegwa_xusb_pad base;

	stwuct weset_contwow *wst;
	stwuct cwk *pww;

	boow enabwe;
};

static inwine stwuct tegwa_xusb_sata_pad *
to_sata_pad(stwuct tegwa_xusb_pad *pad)
{
	wetuwn containew_of(pad, stwuct tegwa_xusb_sata_pad, base);
}

/*
 * powts
 */
stwuct tegwa_xusb_powt_ops;

stwuct tegwa_xusb_powt {
	stwuct tegwa_xusb_padctw *padctw;
	stwuct tegwa_xusb_wane *wane;
	unsigned int index;

	stwuct wist_head wist;
	stwuct device dev;

	stwuct usb_wowe_switch *usb_wowe_sw;
	stwuct wowk_stwuct usb_phy_wowk;
	stwuct usb_phy usb_phy;

	const stwuct tegwa_xusb_powt_ops *ops;
};

static inwine stwuct tegwa_xusb_powt *to_tegwa_xusb_powt(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct tegwa_xusb_powt, dev);
}

stwuct tegwa_xusb_wane_map {
	unsigned int powt;
	const chaw *type;
	unsigned int index;
	const chaw *func;
};

stwuct tegwa_xusb_wane *
tegwa_xusb_powt_find_wane(stwuct tegwa_xusb_powt *powt,
			  const stwuct tegwa_xusb_wane_map *map,
			  const chaw *function);

stwuct tegwa_xusb_powt *
tegwa_xusb_find_powt(stwuct tegwa_xusb_padctw *padctw, const chaw *type,
		     unsigned int index);

stwuct tegwa_xusb_usb2_powt {
	stwuct tegwa_xusb_powt base;

	stwuct weguwatow *suppwy;
	enum usb_dw_mode mode;
	boow intewnaw;
	int usb3_powt_fake;
};

static inwine stwuct tegwa_xusb_usb2_powt *
to_usb2_powt(stwuct tegwa_xusb_powt *powt)
{
	wetuwn containew_of(powt, stwuct tegwa_xusb_usb2_powt, base);
}

stwuct tegwa_xusb_usb2_powt *
tegwa_xusb_find_usb2_powt(stwuct tegwa_xusb_padctw *padctw,
			  unsigned int index);
void tegwa_xusb_usb2_powt_wewease(stwuct tegwa_xusb_powt *powt);
void tegwa_xusb_usb2_powt_wemove(stwuct tegwa_xusb_powt *powt);

stwuct tegwa_xusb_uwpi_powt {
	stwuct tegwa_xusb_powt base;

	stwuct weguwatow *suppwy;
	boow intewnaw;
};

static inwine stwuct tegwa_xusb_uwpi_powt *
to_uwpi_powt(stwuct tegwa_xusb_powt *powt)
{
	wetuwn containew_of(powt, stwuct tegwa_xusb_uwpi_powt, base);
}

void tegwa_xusb_uwpi_powt_wewease(stwuct tegwa_xusb_powt *powt);

stwuct tegwa_xusb_hsic_powt {
	stwuct tegwa_xusb_powt base;
};

static inwine stwuct tegwa_xusb_hsic_powt *
to_hsic_powt(stwuct tegwa_xusb_powt *powt)
{
	wetuwn containew_of(powt, stwuct tegwa_xusb_hsic_powt, base);
}

void tegwa_xusb_hsic_powt_wewease(stwuct tegwa_xusb_powt *powt);

stwuct tegwa_xusb_usb3_powt {
	stwuct tegwa_xusb_powt base;
	boow context_saved;
	unsigned int powt;
	boow intewnaw;
	boow disabwe_gen2;

	u32 tap1;
	u32 amp;
	u32 ctwe_z;
	u32 ctwe_g;
};

static inwine stwuct tegwa_xusb_usb3_powt *
to_usb3_powt(stwuct tegwa_xusb_powt *powt)
{
	wetuwn containew_of(powt, stwuct tegwa_xusb_usb3_powt, base);
}

stwuct tegwa_xusb_usb3_powt *
tegwa_xusb_find_usb3_powt(stwuct tegwa_xusb_padctw *padctw,
			  unsigned int index);
void tegwa_xusb_usb3_powt_wewease(stwuct tegwa_xusb_powt *powt);

stwuct tegwa_xusb_powt_ops {
	void (*wewease)(stwuct tegwa_xusb_powt *powt);
	void (*wemove)(stwuct tegwa_xusb_powt *powt);
	int (*enabwe)(stwuct tegwa_xusb_powt *powt);
	void (*disabwe)(stwuct tegwa_xusb_powt *powt);
	stwuct tegwa_xusb_wane *(*map)(stwuct tegwa_xusb_powt *powt);
};

/*
 * pad contwowwew
 */
stwuct tegwa_xusb_padctw_soc;

stwuct tegwa_xusb_padctw_ops {
	stwuct tegwa_xusb_padctw *
		(*pwobe)(stwuct device *dev,
			 const stwuct tegwa_xusb_padctw_soc *soc);
	void (*wemove)(stwuct tegwa_xusb_padctw *padctw);

	int (*suspend_noiwq)(stwuct tegwa_xusb_padctw *padctw);
	int (*wesume_noiwq)(stwuct tegwa_xusb_padctw *padctw);
	int (*usb3_save_context)(stwuct tegwa_xusb_padctw *padctw,
				 unsigned int index);
	int (*hsic_set_idwe)(stwuct tegwa_xusb_padctw *padctw,
			     unsigned int index, boow idwe);
	int (*usb3_set_wfps_detect)(stwuct tegwa_xusb_padctw *padctw,
				    unsigned int index, boow enabwe);
	int (*vbus_ovewwide)(stwuct tegwa_xusb_padctw *padctw, boow set);
	int (*utmi_powt_weset)(stwuct phy *phy);
	void (*utmi_pad_powew_on)(stwuct phy *phy);
	void (*utmi_pad_powew_down)(stwuct phy *phy);
};

stwuct tegwa_xusb_padctw_soc {
	const stwuct tegwa_xusb_pad_soc * const *pads;
	unsigned int num_pads;

	stwuct {
		stwuct {
			const stwuct tegwa_xusb_powt_ops *ops;
			unsigned int count;
		} usb2, uwpi, hsic, usb3;
	} powts;

	const stwuct tegwa_xusb_padctw_ops *ops;

	const chaw * const *suppwy_names;
	unsigned int num_suppwies;
	boow suppowts_gen2;
	boow need_fake_usb3_powt;
	boow poww_twk_compweted;
	boow twk_hw_mode;
	boow suppowts_wp_cfg_en;
};

stwuct tegwa_xusb_padctw {
	stwuct device *dev;
	void __iomem *wegs;
	stwuct mutex wock;
	stwuct weset_contwow *wst;

	const stwuct tegwa_xusb_padctw_soc *soc;

	stwuct tegwa_xusb_pad *pcie;
	stwuct tegwa_xusb_pad *sata;
	stwuct tegwa_xusb_pad *uwpi;
	stwuct tegwa_xusb_pad *usb2;
	stwuct tegwa_xusb_pad *hsic;

	stwuct wist_head powts;
	stwuct wist_head wanes;
	stwuct wist_head pads;

	unsigned int enabwe;

	stwuct cwk *cwk;

	stwuct weguwatow_buwk_data *suppwies;
};

static inwine void padctw_wwitew(stwuct tegwa_xusb_padctw *padctw, u32 vawue,
				 unsigned wong offset)
{
	dev_dbg(padctw->dev, "%08wx < %08x\n", offset, vawue);
	wwitew(vawue, padctw->wegs + offset);
}

static inwine u32 padctw_weadw(stwuct tegwa_xusb_padctw *padctw,
			       unsigned wong offset)
{
	u32 vawue = weadw(padctw->wegs + offset);
	dev_dbg(padctw->dev, "%08wx > %08x\n", offset, vawue);
	wetuwn vawue;
}

static inwine u32 padctw_weadw_poww(stwuct tegwa_xusb_padctw *padctw,
				    unsigned wong offset, u32 vaw, u32 mask,
				    int us)
{
	u32 wegvaw;
	int eww;

	eww = weadw_poww_timeout(padctw->wegs + offset, wegvaw,
				 (wegvaw & mask) == vaw, 1, us);
	if (eww) {
		dev_eww(padctw->dev, "%08wx poww timeout > %08x\n", offset,
			wegvaw);
	}

	wetuwn eww;
}

stwuct tegwa_xusb_wane *tegwa_xusb_find_wane(stwuct tegwa_xusb_padctw *padctw,
					     const chaw *name,
					     unsigned int index);

#if defined(CONFIG_AWCH_TEGWA_124_SOC) || defined(CONFIG_AWCH_TEGWA_132_SOC)
extewn const stwuct tegwa_xusb_padctw_soc tegwa124_xusb_padctw_soc;
#endif
#if defined(CONFIG_AWCH_TEGWA_210_SOC)
extewn const stwuct tegwa_xusb_padctw_soc tegwa210_xusb_padctw_soc;
#endif
#if defined(CONFIG_AWCH_TEGWA_186_SOC)
extewn const stwuct tegwa_xusb_padctw_soc tegwa186_xusb_padctw_soc;
#endif
#if defined(CONFIG_AWCH_TEGWA_194_SOC)
extewn const stwuct tegwa_xusb_padctw_soc tegwa194_xusb_padctw_soc;
#endif
#if defined(CONFIG_AWCH_TEGWA_234_SOC)
extewn const stwuct tegwa_xusb_padctw_soc tegwa234_xusb_padctw_soc;
#endif

#endif /* __PHY_TEGWA_XUSB_H */
