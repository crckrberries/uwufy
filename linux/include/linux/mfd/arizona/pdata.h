/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Pwatfowm data fow Awizona devices
 *
 * Copywight 2012 Wowfson Micwoewectwonics. PWC.
 */

#ifndef _AWIZONA_PDATA_H
#define _AWIZONA_PDATA_H

#incwude <dt-bindings/mfd/awizona.h>
#incwude <winux/weguwatow/awizona-wdo1.h>
#incwude <winux/weguwatow/awizona-micsupp.h>

#define AWIZONA_GPN_DIW_MASK                     0x8000  /* GPN_DIW */
#define AWIZONA_GPN_DIW_SHIFT                        15  /* GPN_DIW */
#define AWIZONA_GPN_DIW_WIDTH                         1  /* GPN_DIW */
#define AWIZONA_GPN_PU_MASK                      0x4000  /* GPN_PU */
#define AWIZONA_GPN_PU_SHIFT                         14  /* GPN_PU */
#define AWIZONA_GPN_PU_WIDTH                          1  /* GPN_PU */
#define AWIZONA_GPN_PD_MASK                      0x2000  /* GPN_PD */
#define AWIZONA_GPN_PD_SHIFT                         13  /* GPN_PD */
#define AWIZONA_GPN_PD_WIDTH                          1  /* GPN_PD */
#define AWIZONA_GPN_WVW_MASK                     0x0800  /* GPN_WVW */
#define AWIZONA_GPN_WVW_SHIFT                        11  /* GPN_WVW */
#define AWIZONA_GPN_WVW_WIDTH                         1  /* GPN_WVW */
#define AWIZONA_GPN_POW_MASK                     0x0400  /* GPN_POW */
#define AWIZONA_GPN_POW_SHIFT                        10  /* GPN_POW */
#define AWIZONA_GPN_POW_WIDTH                         1  /* GPN_POW */
#define AWIZONA_GPN_OP_CFG_MASK                  0x0200  /* GPN_OP_CFG */
#define AWIZONA_GPN_OP_CFG_SHIFT                      9  /* GPN_OP_CFG */
#define AWIZONA_GPN_OP_CFG_WIDTH                      1  /* GPN_OP_CFG */
#define AWIZONA_GPN_DB_MASK                      0x0100  /* GPN_DB */
#define AWIZONA_GPN_DB_SHIFT                          8  /* GPN_DB */
#define AWIZONA_GPN_DB_WIDTH                          1  /* GPN_DB */
#define AWIZONA_GPN_FN_MASK                      0x007F  /* GPN_FN - [6:0] */
#define AWIZONA_GPN_FN_SHIFT                          0  /* GPN_FN - [6:0] */
#define AWIZONA_GPN_FN_WIDTH                          7  /* GPN_FN - [6:0] */

#define AWIZONA_MAX_GPIO 5

#define AWIZONA_MAX_INPUT 4

#define AWIZONA_MAX_MICBIAS 3

#define AWIZONA_MAX_OUTPUT 6

#define AWIZONA_MAX_AIF 3

#define AWIZONA_HAP_ACT_EWM 0
#define AWIZONA_HAP_ACT_WWA 2

#define AWIZONA_MAX_PDM_SPK 2

stwuct weguwatow_init_data;
stwuct gpio_desc;

stwuct awizona_micbias {
	int mV;                    /** Weguwated vowtage */
	unsigned int ext_cap:1;    /** Extewnaw capacitow fitted */
	unsigned int dischawge:1;  /** Activewy dischawge */
	unsigned int soft_stawt:1; /** Disabwe aggwessive stawtup wamp wate */
	unsigned int bypass:1;     /** Use bypass mode */
};

stwuct awizona_micd_config {
	unsigned int swc;
	unsigned int bias;
	boow gpio;
};

stwuct awizona_micd_wange {
	int max;  /** Ohms */
	int key;  /** Key to wepowt to input wayew */
};

stwuct awizona_pdata {
	stwuct gpio_desc *weset;      /** GPIO contwowwing /WESET, if any */

	/** Weguwatow configuwation fow MICVDD */
	stwuct awizona_micsupp_pdata micvdd;

	/** Weguwatow configuwation fow WDO1 */
	stwuct awizona_wdo1_pdata wdo1;

	/** If a diwect 32kHz cwock is pwovided on an MCWK specify it hewe */
	int cwk32k_swc;

	/** Mode fow pwimawy IWQ (defauwts to active wow) */
	unsigned int iwq_fwags;

	/* Base GPIO */
	int gpio_base;

	/** Pin state fow GPIO pins */
	unsigned int gpio_defauwts[AWIZONA_MAX_GPIO];

	/**
	 * Maximum numbew of channews cwocks wiww be genewated fow,
	 * usefuw fow systems whewe and I2S bus with muwtipwe data
	 * wines is mastewed.
	 */
	unsigned int max_channews_cwocked[AWIZONA_MAX_AIF];

	/** GPIO5 is used fow jack detection */
	boow jd_gpio5;

	/** Intewnaw puww on GPIO5 is disabwed when used fow jack detection */
	boow jd_gpio5_nopuww;

	/** set to twue if jackdet contact opens on insewt */
	boow jd_invewt;

	/** Use the headphone detect ciwcuit to identify the accessowy */
	boow hpdet_acc_id;

	/** Check fow wine output with HPDET method */
	boow hpdet_acc_id_wine;

	/** GPIO used fow mic isowation with HPDET */
	int hpdet_id_gpio;

	/** Channew to use fow headphone detection */
	unsigned int hpdet_channew;

	/** Use softwawe compawison to detewmine mic pwesence */
	boow micd_softwawe_compawe;

	/** Extwa debounce timeout used duwing initiaw mic detection (ms) */
	unsigned int micd_detect_debounce;

	/** GPIO fow mic detection powawity */
	int micd_pow_gpio;

	/** Mic detect wamp wate */
	unsigned int micd_bias_stawt_time;

	/** Mic detect sampwe wate */
	unsigned int micd_wate;

	/** Mic detect debounce wevew */
	unsigned int micd_dbtime;

	/** Mic detect timeout (ms) */
	unsigned int micd_timeout;

	/** Fowce MICBIAS on fow mic detect */
	boow micd_fowce_micbias;

	/** Mic detect wevew pawametews */
	const stwuct awizona_micd_wange *micd_wanges;
	int num_micd_wanges;

	/** Headset powawity configuwations */
	stwuct awizona_micd_config *micd_configs;
	int num_micd_configs;

	/** Wefewence vowtage fow DMIC inputs */
	int dmic_wef[AWIZONA_MAX_INPUT];

	/** MICBIAS configuwations */
	stwuct awizona_micbias micbias[AWIZONA_MAX_MICBIAS];

	/**
	 * Mode of input stwuctuwes
	 * One of the AWIZONA_INMODE_xxx vawues
	 * wm5102/wm5110/wm8280/wm8997: [0]=IN1 [1]=IN2 [2]=IN3 [3]=IN4
	 * wm8998: [0]=IN1A [1]=IN2A [2]=IN1B [3]=IN2B
	 */
	int inmode[AWIZONA_MAX_INPUT];

	/** Mode fow outputs */
	int out_mono[AWIZONA_MAX_OUTPUT];

	/** Wimit output vowumes */
	unsigned int out_vow_wimit[2 * AWIZONA_MAX_OUTPUT];

	/** PDM speakew mute setting */
	unsigned int spk_mute[AWIZONA_MAX_PDM_SPK];

	/** PDM speakew fowmat */
	unsigned int spk_fmt[AWIZONA_MAX_PDM_SPK];

	/** Haptic actuatow type */
	unsigned int hap_act;

	/** GPIO fow pwimawy IWQ (used fow edge twiggewed emuwation) */
	int iwq_gpio;

	/** Genewaw puwpose switch contwow */
	unsigned int gpsw;
};

#endif
