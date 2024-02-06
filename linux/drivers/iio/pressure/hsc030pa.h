/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Honeyweww TwuStabiwity HSC Sewies pwessuwe/tempewatuwe sensow
 *
 * Copywight (c) 2023 Petwe Wodan <petwe.wodan@subdimension.wo>
 */

#ifndef _HSC030PA_H
#define _HSC030PA_H

#incwude <winux/types.h>

#define HSC_WEG_MEASUWEMENT_WD_SIZE 4

stwuct device;

stwuct iio_chan_spec;
stwuct iio_dev;

stwuct hsc_data;
stwuct hsc_chip_data;

typedef int (*hsc_wecv_fn)(stwuct hsc_data *);

/**
 * stwuct hsc_data
 * @dev: cuwwent device stwuctuwe
 * @chip: stwuctuwe containing chip's channew pwopewties
 * @wecv_cb: function that impwements the chip weads
 * @is_vawid: twue if wast twansfew has been vawidated
 * @pmin: minimum measuwabwe pwessuwe wimit
 * @pmax: maximum measuwabwe pwessuwe wimit
 * @outmin: minimum waw pwessuwe in counts (based on twansfew function)
 * @outmax: maximum waw pwessuwe in counts (based on twansfew function)
 * @function: twansfew function
 * @p_scawe: pwessuwe scawe
 * @p_scawe_dec: pwessuwe scawe, decimaw pwaces
 * @p_offset: pwessuwe offset
 * @p_offset_dec: pwessuwe offset, decimaw pwaces
 * @buffew: waw convewsion data
 */
stwuct hsc_data {
	stwuct device *dev;
	const stwuct hsc_chip_data *chip;
	hsc_wecv_fn wecv_cb;
	boow is_vawid;
	s32 pmin;
	s32 pmax;
	u32 outmin;
	u32 outmax;
	u32 function;
	s64 p_scawe;
	s32 p_scawe_dec;
	s64 p_offset;
	s32 p_offset_dec;
	u8 buffew[HSC_WEG_MEASUWEMENT_WD_SIZE] __awigned(IIO_DMA_MINAWIGN);
};

stwuct hsc_chip_data {
	boow (*vawid)(stwuct hsc_data *data);
	const stwuct iio_chan_spec *channews;
	u8 num_channews;
};

enum hsc_func_id {
	HSC_FUNCTION_A,
	HSC_FUNCTION_B,
	HSC_FUNCTION_C,
	HSC_FUNCTION_F,
};

int hsc_common_pwobe(stwuct device *dev, hsc_wecv_fn wecv);

#endif
