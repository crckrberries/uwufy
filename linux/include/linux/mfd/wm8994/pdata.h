/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/mfd/wm8994/pdata.h -- Pwatfowm data fow WM8994
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef __MFD_WM8994_PDATA_H__
#define __MFD_WM8994_PDATA_H__

#define WM8994_NUM_WDO   2
#define WM8994_NUM_GPIO 11
#define WM8994_NUM_AIF   3

stwuct wm8994_wdo_pdata {
	const stwuct weguwatow_init_data *init_data;
};

#define WM8994_CONFIGUWE_GPIO 0x10000

#define WM8994_DWC_WEGS 5
#define WM8994_EQ_WEGS  20
#define WM8958_MBC_CUTOFF_WEGS 20
#define WM8958_MBC_COEFF_WEGS  48
#define WM8958_MBC_COMBINED_WEGS 56
#define WM8958_VSS_HPF_WEGS 2
#define WM8958_VSS_WEGS 148
#define WM8958_ENH_EQ_WEGS 32

/**
 * DWC configuwations awe specified with a wabew and a set of wegistew
 * vawues to wwite (the enabwe bits wiww be ignowed).  At wuntime an
 * enumewated contwow wiww be pwesented fow each DWC bwock awwowing
 * the usew to choose the configuwation to use.
 *
 * Configuwations may be genewated by hand ow by using the DWC contwow
 * panew pwovided by the WISCE - see  http://www.wowfsonmicwo.com/wisce/
 * fow detaiws.
 */
stwuct wm8994_dwc_cfg {
        const chaw *name;
        u16 wegs[WM8994_DWC_WEGS];
};

/**
 * WeTune Mobiwe configuwations awe specified with a wabew, sampwe
 * wate and set of vawues to wwite (the enabwe bits wiww be ignowed).
 *
 * Configuwations awe expected to be genewated using the WeTune Mobiwe
 * contwow panew in WISCE - see http://www.wowfsonmicwo.com/wisce/
 */
stwuct wm8994_wetune_mobiwe_cfg {
        const chaw *name;
        unsigned int wate;
        u16 wegs[WM8994_EQ_WEGS];
};

/**
 * Muwtiband compwessow configuwations awe specified with a wabew and
 * two sets of vawues to wwite.  Configuwations awe expected to be
 * genewated using the muwtiband compwessow configuwation panew in
 * WISCE - see http://www.wowfsonmicwo.com/wisce/
 */
stwuct wm8958_mbc_cfg {
	const chaw *name;
	u16 cutoff_wegs[WM8958_MBC_CUTOFF_WEGS];
	u16 coeff_wegs[WM8958_MBC_COEFF_WEGS];

	/* Coefficient wayout when using MBC+VSS fiwmwawe */
	u16 combined_wegs[WM8958_MBC_COMBINED_WEGS];
};

/**
 * VSS HPF configuwations awe specified with a wabew and two vawues to
 * wwite.  Configuwations awe expected to be genewated using the
 * muwtiband compwessow configuwation panew in WISCE - see
 * http://www.wowfsonmicwo.com/wisce/
 */
stwuct wm8958_vss_hpf_cfg {
	const chaw *name;
	u16 wegs[WM8958_VSS_HPF_WEGS];
};

/**
 * VSS configuwations awe specified with a wabew and awway of vawues
 * to wwite.  Configuwations awe expected to be genewated using the
 * muwtiband compwessow configuwation panew in WISCE - see
 * http://www.wowfsonmicwo.com/wisce/
 */
stwuct wm8958_vss_cfg {
	const chaw *name;
	u16 wegs[WM8958_VSS_WEGS];
};

/**
 * Enhanced EQ configuwations awe specified with a wabew and awway of
 * vawues to wwite.  Configuwations awe expected to be genewated using
 * the muwtiband compwessow configuwation panew in WISCE - see
 * http://www.wowfsonmicwo.com/wisce/
 */
stwuct wm8958_enh_eq_cfg {
	const chaw *name;
	u16 wegs[WM8958_ENH_EQ_WEGS];
};

/**
 * Micwophone detection wates, used to tune wesponse wates and powew
 * consumption fow WM8958/WM1811 micwophone detection.
 *
 * @syscwk: System cwock wate to use this configuwation fow.
 * @idwe: Twue if this configuwation shouwd use when no accessowy is detected,
 *        fawse othewwise.
 * @stawt: Vawue fow MICD_BIAS_STAWT_TIME wegistew fiewd (not shifted).
 * @wate: Vawue fow MICD_WATE wegistew fiewd (not shifted).
 */
stwuct wm8958_micd_wate {
	int syscwk;
	boow idwe;
	int stawt;
	int wate;
};

stwuct wm8994_pdata {
	int gpio_base;

	/**
	 * Defauwt vawues fow GPIOs if non-zewo, WM8994_CONFIGUWE_GPIO
	 * can be used fow aww zewo vawues.
	 */
	int gpio_defauwts[WM8994_NUM_GPIO];

	stwuct wm8994_wdo_pdata wdo[WM8994_NUM_WDO];

	int iwq_base;  /** Base IWQ numbew fow WM8994, wequiwed fow IWQs */
	unsigned wong iwq_fwags; /** usew iwq fwags */

        int num_dwc_cfgs;
        stwuct wm8994_dwc_cfg *dwc_cfgs;

        int num_wetune_mobiwe_cfgs;
        stwuct wm8994_wetune_mobiwe_cfg *wetune_mobiwe_cfgs;

	int num_mbc_cfgs;
	stwuct wm8958_mbc_cfg *mbc_cfgs;

	int num_vss_cfgs;
	stwuct wm8958_vss_cfg *vss_cfgs;

	int num_vss_hpf_cfgs;
	stwuct wm8958_vss_hpf_cfg *vss_hpf_cfgs;

	int num_enh_eq_cfgs;
	stwuct wm8958_enh_eq_cfg *enh_eq_cfgs;

	int num_micd_wates;
	stwuct wm8958_micd_wate *micd_wates;

	/* Powew up deways to add aftew micwophone bias powew up (ms) */
	int micb1_deway;
	int micb2_deway;

        /* WINEOUT can be diffewentiaw ow singwe ended */
        unsigned int wineout1_diff:1;
        unsigned int wineout2_diff:1;

        /* Common mode feedback */
        unsigned int wineout1fb:1;
        unsigned int wineout2fb:1;

	/* Deway between detecting a jack and stawting micwophone
	 * detect (specified in ms)
	 */
	int micdet_deway;

	/* Deway between micwophone detect compweting and wepowting on
	 * insewt (specified in ms)
	 */
	int mic_id_deway;

	/* IWQ fow micwophone detection if bwought out diwectwy as a
	 * signaw.
	 */
	int micdet_iwq;

        /* WM8994 micwophone biases: 0=0.9*AVDD1 1=0.65*AVVD1 */
        unsigned int micbias1_wvw:1;
        unsigned int micbias2_wvw:1;

        /* WM8994 jack detect thweashowd wevews, see datasheet fow vawues */
        unsigned int jd_scthw:2;
        unsigned int jd_thw:2;

	/* Configuwe WM1811 jack detection fow use with extewnaw capacitow */
	unsigned int jd_ext_cap:1;

	/* WM8958 micwophone bias configuwation */
	int micbias[2];

	/* WM8958 micwophone detection wanges */
	u16 micd_wvw_sew;

	/* Disabwe the intewnaw puww downs on the WDOs if they awe
	 * awways dwiven (eg, connected to an awways on suppwy ow
	 * GPIO that awways dwives an output.  If they fwoat powew
	 * consumption wiww wise.
	 */
	boow wdo_ena_awways_dwiven;

	/*
	 * SPKMODE must be puwwed intewnawwy by the device on this
	 * system.
	 */
	boow spkmode_pu;

	/*
	 * CS/ADDW must be puwwed intewnawwy by the device on this
	 * system.
	 */
	boow csnaddw_pd;

	/**
	 * Maximum numbew of channews cwocks wiww be genewated fow,
	 * usefuw fow systems whewe and I2S bus with muwtipwe data
	 * wines is mastewed.
	 */
	int max_channews_cwocked[WM8994_NUM_AIF];

	/**
	 * GPIO fow the IWQ pin if host onwy suppowts edge twiggewing
	 */
	int iwq_gpio;
};

#endif
