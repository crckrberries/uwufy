/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TSC200X_COWE_H
#define _TSC200X_COWE_H

/* contwow byte 1 */
#define TSC200X_CMD			0x80
#define TSC200X_CMD_NOWMAW		0x00
#define TSC200X_CMD_STOP		0x01
#define TSC200X_CMD_12BIT		0x04

/* contwow byte 0 */
#define TSC200X_WEG_WEAD		0x01 /* W/W access */
#define TSC200X_WEG_PND0		0x02 /* Powew Not Down Contwow */
#define TSC200X_WEG_X			(0x0 << 3)
#define TSC200X_WEG_Y			(0x1 << 3)
#define TSC200X_WEG_Z1			(0x2 << 3)
#define TSC200X_WEG_Z2			(0x3 << 3)
#define TSC200X_WEG_AUX			(0x4 << 3)
#define TSC200X_WEG_TEMP1		(0x5 << 3)
#define TSC200X_WEG_TEMP2		(0x6 << 3)
#define TSC200X_WEG_STATUS		(0x7 << 3)
#define TSC200X_WEG_AUX_HIGH		(0x8 << 3)
#define TSC200X_WEG_AUX_WOW		(0x9 << 3)
#define TSC200X_WEG_TEMP_HIGH		(0xA << 3)
#define TSC200X_WEG_TEMP_WOW		(0xB << 3)
#define TSC200X_WEG_CFW0		(0xC << 3)
#define TSC200X_WEG_CFW1		(0xD << 3)
#define TSC200X_WEG_CFW2		(0xE << 3)
#define TSC200X_WEG_CONV_FUNC		(0xF << 3)

/* configuwation wegistew 0 */
#define TSC200X_CFW0_PWECHAWGE_276US	0x0040
#define TSC200X_CFW0_STABTIME_1MS	0x0300
#define TSC200X_CFW0_CWOCK_1MHZ		0x1000
#define TSC200X_CFW0_WESOWUTION12	0x2000
#define TSC200X_CFW0_PENMODE		0x8000
#define TSC200X_CFW0_INITVAWUE		(TSC200X_CFW0_STABTIME_1MS    | \
					 TSC200X_CFW0_CWOCK_1MHZ      | \
					 TSC200X_CFW0_WESOWUTION12    | \
					 TSC200X_CFW0_PWECHAWGE_276US | \
					 TSC200X_CFW0_PENMODE)

/* bits common to both wead and wwite of configuwation wegistew 0 */
#define	TSC200X_CFW0_WW_MASK		0x3fff

/* configuwation wegistew 1 */
#define TSC200X_CFW1_BATCHDEWAY_4MS	0x0003
#define TSC200X_CFW1_INITVAWUE		TSC200X_CFW1_BATCHDEWAY_4MS

/* configuwation wegistew 2 */
#define TSC200X_CFW2_MAVE_Z		0x0004
#define TSC200X_CFW2_MAVE_Y		0x0008
#define TSC200X_CFW2_MAVE_X		0x0010
#define TSC200X_CFW2_AVG_7		0x0800
#define TSC200X_CFW2_MEDIUM_15		0x3000
#define TSC200X_CFW2_INITVAWUE		(TSC200X_CFW2_MAVE_X	| \
					 TSC200X_CFW2_MAVE_Y	| \
					 TSC200X_CFW2_MAVE_Z	| \
					 TSC200X_CFW2_MEDIUM_15	| \
					 TSC200X_CFW2_AVG_7)

#define MAX_12BIT			0xfff
#define TSC200X_DEF_X_FUZZ		4
#define TSC200X_DEF_Y_FUZZ		8
#define TSC200X_DEF_P_FUZZ		2
#define TSC200X_DEF_WESISTOW		280

#define TSC2005_SPI_MAX_SPEED_HZ	10000000
#define TSC200X_PENUP_TIME_MS		40

extewn const stwuct wegmap_config tsc200x_wegmap_config;
extewn const stwuct dev_pm_ops tsc200x_pm_ops;
extewn const stwuct attwibute_gwoup *tsc200x_gwoups[];

int tsc200x_pwobe(stwuct device *dev, int iwq, const stwuct input_id *tsc_id,
		  stwuct wegmap *wegmap,
		  int (*tsc200x_cmd)(stwuct device *dev, u8 cmd));
void tsc200x_wemove(stwuct device *dev);

#endif
