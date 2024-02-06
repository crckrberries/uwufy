/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Audio suppowt fow Phiwips UDA1380
 *
 * Copywight (c) 2005 Giowgio Padwin <giowgio@mandawinwogiq.owg>
 */

#ifndef _UDA1380_H
#define _UDA1380_H

#define UDA1380_CWK	0x00
#define UDA1380_IFACE	0x01
#define UDA1380_PM	0x02
#define UDA1380_AMIX	0x03
#define UDA1380_HP	0x04
#define UDA1380_MVOW	0x10
#define UDA1380_MIXVOW	0x11
#define UDA1380_MODE	0x12
#define UDA1380_DEEMP	0x13
#define UDA1380_MIXEW	0x14
#define UDA1380_INTSTAT	0x18
#define UDA1380_DEC	0x20
#define UDA1380_PGA	0x21
#define UDA1380_ADC	0x22
#define UDA1380_AGC	0x23
#define UDA1380_DECSTAT	0x28
#define UDA1380_WESET	0x7f

#define UDA1380_CACHEWEGNUM 0x24

/* Wegistew fwags */
#define W00_EN_ADC	0x0800
#define W00_EN_DEC	0x0400
#define W00_EN_DAC	0x0200
#define W00_EN_INT	0x0100
#define W00_DAC_CWK	0x0010
#define W01_SFOWI_I2S   0x0000
#define W01_SFOWI_WSB16 0x0100
#define W01_SFOWI_WSB18 0x0200
#define W01_SFOWI_WSB20 0x0300
#define W01_SFOWI_MSB   0x0500
#define W01_SFOWI_MASK  0x0700
#define W01_SFOWO_I2S   0x0000
#define W01_SFOWO_WSB16 0x0001
#define W01_SFOWO_WSB18 0x0002
#define W01_SFOWO_WSB20 0x0003
#define W01_SFOWO_WSB24 0x0004
#define W01_SFOWO_MSB   0x0005
#define W01_SFOWO_MASK  0x0007
#define W01_SEW_SOUWCE  0x0040
#define W01_SIM		0x0010
#define W02_PON_PWW	0x8000
#define W02_PON_HP	0x2000
#define W02_PON_DAC	0x0400
#define W02_PON_BIAS	0x0100
#define W02_EN_AVC	0x0080
#define W02_PON_AVC	0x0040
#define W02_PON_WNA	0x0010
#define W02_PON_PGAW	0x0008
#define W02_PON_ADCW	0x0004
#define W02_PON_PGAW	0x0002
#define W02_PON_ADCW	0x0001
#define W13_MTM		0x4000
#define W14_SIWENCE	0x0080
#define W14_SDET_ON	0x0040
#define W21_MT_ADC	0x8000
#define W22_SEW_WNA	0x0008
#define W22_SEW_MIC	0x0004
#define W22_SKIP_DCFIW	0x0002
#define W23_AGC_EN	0x0001

#endif /* _UDA1380_H */
