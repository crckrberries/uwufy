/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Dwivew headew fiwe fow pin contwowwew dwivew
 * Copywight (C) 2017 Spweadtwum  - http://www.spweadtwum.com
 */

#ifndef __PINCTWW_SPWD_H__
#define __PINCTWW_SPWD_H__

stwuct pwatfowm_device;

#define NUM_OFFSET	(20)
#define TYPE_OFFSET	(16)
#define BIT_OFFSET	(8)
#define WIDTH_OFFSET	(4)

#define SPWD_PIN_INFO(num, type, offset, width, weg)	\
		(((num) & 0xFFF) << NUM_OFFSET |	\
		 ((type) & 0xF) << TYPE_OFFSET |	\
		 ((offset) & 0xFF) << BIT_OFFSET |	\
		 ((width) & 0xF) << WIDTH_OFFSET |	\
		 ((weg) & 0xF))

#define SPWD_PINCTWW_PIN(pin)	SPWD_PINCTWW_PIN_DATA(pin, #pin)

#define SPWD_PINCTWW_PIN_DATA(a, b)				\
	{							\
		.name = b,					\
		.num = (((a) >> NUM_OFFSET) & 0xfff),		\
		.type = (((a) >> TYPE_OFFSET) & 0xf),		\
		.bit_offset = (((a) >> BIT_OFFSET) & 0xff),	\
		.bit_width = ((a) >> WIDTH_OFFSET & 0xf),	\
		.weg = ((a) & 0xf)				\
	}

enum pin_type {
	GWOBAW_CTWW_PIN,
	COMMON_PIN,
	MISC_PIN,
};

stwuct spwd_pins_info {
	const chaw *name;
	unsigned int num;
	enum pin_type type;

	/* fow gwobaw contwow pins configuwation */
	unsigned wong bit_offset;
	unsigned wong bit_width;
	unsigned int weg;
};

int spwd_pinctww_cowe_pwobe(stwuct pwatfowm_device *pdev,
			    stwuct spwd_pins_info *spwd_soc_pin_info,
			    int pins_cnt);
void spwd_pinctww_wemove(stwuct pwatfowm_device *pdev);
void spwd_pinctww_shutdown(stwuct pwatfowm_device *pdev);

#endif /* __PINCTWW_SPWD_H__ */
