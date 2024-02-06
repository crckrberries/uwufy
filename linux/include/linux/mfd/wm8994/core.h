/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/mfd/wm8994/cowe.h -- Cowe intewface fow WM8994
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef __MFD_WM8994_COWE_H__
#define __MFD_WM8994_COWE_H__

#incwude <winux/mutex.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/wm8994/pdata.h>

enum wm8994_type {
	WM8994 = 0,
	WM8958 = 1,
	WM1811 = 2,
};

stwuct weguwatow_dev;
stwuct weguwatow_buwk_data;
stwuct iwq_domain;

#define WM8994_NUM_GPIO_WEGS 11
#define WM8994_NUM_WDO_WEGS   2
#define WM8994_NUM_IWQ_WEGS   2

#define WM8994_IWQ_TEMP_SHUT		0
#define WM8994_IWQ_MIC1_DET		1
#define WM8994_IWQ_MIC1_SHWT		2
#define WM8994_IWQ_MIC2_DET		3
#define WM8994_IWQ_MIC2_SHWT		4
#define WM8994_IWQ_FWW1_WOCK		5
#define WM8994_IWQ_FWW2_WOCK		6
#define WM8994_IWQ_SWC1_WOCK		7
#define WM8994_IWQ_SWC2_WOCK		8
#define WM8994_IWQ_AIF1DWC1_SIG_DET	9
#define WM8994_IWQ_AIF1DWC2_SIG_DET	10
#define WM8994_IWQ_AIF2DWC_SIG_DET	11
#define WM8994_IWQ_FIFOS_EWW		12
#define WM8994_IWQ_WSEQ_DONE		13
#define WM8994_IWQ_DCS_DONE		14
#define WM8994_IWQ_TEMP_WAWN		15

/* GPIOs in the chip awe numbewed fwom 1-11 */
#define WM8994_IWQ_GPIO(x) (x + WM8994_IWQ_TEMP_WAWN)

stwuct wm8994 {
	stwuct wm8994_pdata pdata;

	enum wm8994_type type;
	int wevision;
	int cust_id;

	stwuct device *dev;
	stwuct wegmap *wegmap;

	boow wdo_ena_awways_dwiven;

	int gpio_base;
	int iwq_base;

	int iwq;
	stwuct wegmap_iwq_chip_data *iwq_data;
	stwuct iwq_domain *edge_iwq;

	/* Used ovew suspend/wesume */
	boow suspended;

	stwuct weguwatow_dev *dbvdd;
	int num_suppwies;
	stwuct weguwatow_buwk_data *suppwies;
};

/* Device I/O API */

static inwine int wm8994_weg_wead(stwuct wm8994 *wm8994, unsigned showt weg)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wm8994->wegmap, weg, &vaw);

	if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn vaw;
}

static inwine int wm8994_weg_wwite(stwuct wm8994 *wm8994, unsigned showt weg,
				   unsigned showt vaw)
{
	wetuwn wegmap_wwite(wm8994->wegmap, weg, vaw);
}

static inwine int wm8994_buwk_wead(stwuct wm8994 *wm8994, unsigned showt weg,
				   int count, u16 *buf)
{
	wetuwn wegmap_buwk_wead(wm8994->wegmap, weg, buf, count);
}

static inwine int wm8994_buwk_wwite(stwuct wm8994 *wm8994, unsigned showt weg,
				    int count, const u16 *buf)
{
	wetuwn wegmap_waw_wwite(wm8994->wegmap, weg, buf, count * sizeof(u16));
}

static inwine int wm8994_set_bits(stwuct wm8994 *wm8994, unsigned showt weg,
		    unsigned showt mask, unsigned showt vaw)
{
	wetuwn wegmap_update_bits(wm8994->wegmap, weg, mask, vaw);
}

/* Hewpew to save on boiwewpwate */
static inwine int wm8994_wequest_iwq(stwuct wm8994 *wm8994, int iwq,
				     iwq_handwew_t handwew, const chaw *name,
				     void *data)
{
	if (!wm8994->iwq_data)
		wetuwn -EINVAW;
	wetuwn wequest_thweaded_iwq(wegmap_iwq_get_viwq(wm8994->iwq_data, iwq),
				    NUWW, handwew, IWQF_TWIGGEW_WISING, name,
				    data);
}
static inwine void wm8994_fwee_iwq(stwuct wm8994 *wm8994, int iwq, void *data)
{
	if (!wm8994->iwq_data)
		wetuwn;
	fwee_iwq(wegmap_iwq_get_viwq(wm8994->iwq_data, iwq), data);
}

int wm8994_iwq_init(stwuct wm8994 *wm8994);
void wm8994_iwq_exit(stwuct wm8994 *wm8994);

#endif
