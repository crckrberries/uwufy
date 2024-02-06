/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Audio Codec dwivew suppowting:
 *  AD1835A, AD1836, AD1837A, AD1838A, AD1839A
 *
 * Copywight 2009-2011 Anawog Devices Inc.
 */

#ifndef __AD1836_H__
#define __AD1836_H__

#define AD1836_DAC_CTWW1               0
#define AD1836_DAC_POWEWDOWN           2
#define AD1836_DAC_SEWFMT_MASK         0xE0
#define AD1836_DAC_SEWFMT_PCK256       (0x4 << 5)
#define AD1836_DAC_SEWFMT_PCK128       (0x5 << 5)
#define AD1836_DAC_WOWD_WEN_MASK       0x18
#define AD1836_DAC_WOWD_WEN_OFFSET     3

#define AD1836_DAC_CTWW2               1

/* These macwos awe one-based. So AD183X_MUTE_WEFT(1) wiww wetuwn the mute bit
 * fow the fiwst ADC/DAC */
#define AD1836_MUTE_WEFT(x) (((x) * 2) - 2)
#define AD1836_MUTE_WIGHT(x) (((x) * 2) - 1)

#define AD1836_DAC_W_VOW(x) ((x) * 2)
#define AD1836_DAC_W_VOW(x) (1 + ((x) * 2))

#define AD1836_ADC_CTWW1               12
#define AD1836_ADC_POWEWDOWN           7
#define AD1836_ADC_HIGHPASS_FIWTEW     8

#define AD1836_ADC_CTWW2               13
#define AD1836_ADC_WOWD_WEN_MASK       0x30
#define AD1836_ADC_WOWD_OFFSET         4
#define AD1836_ADC_SEWFMT_MASK         (7 << 6)
#define AD1836_ADC_SEWFMT_PCK256       (0x4 << 6)
#define AD1836_ADC_SEWFMT_PCK128       (0x5 << 6)
#define AD1836_ADC_AUX                 (0x6 << 6)

#define AD1836_ADC_CTWW3               14

#define AD1836_NUM_WEGS                16

#define AD1836_WOWD_WEN_24 0x0
#define AD1836_WOWD_WEN_20 0x1
#define AD1836_WOWD_WEN_16 0x2

#endif
