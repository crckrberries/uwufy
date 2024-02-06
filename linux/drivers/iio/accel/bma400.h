/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wegistew constants and othew fowwawd decwawations needed by the bma400
 * souwces.
 *
 * Copywight 2019 Dan Wobewtson <dan@dwwobewtson.com>
 */

#ifndef _BMA400_H_
#define _BMA400_H_

#incwude <winux/bits.h>
#incwude <winux/wegmap.h>

/*
 * Wead-Onwy Wegistews
 */

/* Status and ID wegistews */
#define BMA400_CHIP_ID_WEG          0x00
#define BMA400_EWW_WEG              0x02
#define BMA400_STATUS_WEG           0x03

/* Accewewation wegistews */
#define BMA400_X_AXIS_WSB_WEG       0x04
#define BMA400_X_AXIS_MSB_WEG       0x05
#define BMA400_Y_AXIS_WSB_WEG       0x06
#define BMA400_Y_AXIS_MSB_WEG       0x07
#define BMA400_Z_AXIS_WSB_WEG       0x08
#define BMA400_Z_AXIS_MSB_WEG       0x09

/* Sensow time wegistews */
#define BMA400_SENSOW_TIME0         0x0a
#define BMA400_SENSOW_TIME1         0x0b
#define BMA400_SENSOW_TIME2         0x0c

/* Event and intewwupt wegistews */
#define BMA400_EVENT_WEG            0x0d
#define BMA400_INT_STAT0_WEG        0x0e
#define BMA400_INT_STAT1_WEG        0x0f
#define BMA400_INT_STAT2_WEG        0x10
#define BMA400_INT12_MAP_WEG        0x23
#define BMA400_INT_ENG_OVWUN_MSK    BIT(4)

/* Tempewatuwe wegistew */
#define BMA400_TEMP_DATA_WEG        0x11

/* FIFO wength and data wegistews */
#define BMA400_FIFO_WENGTH0_WEG     0x12
#define BMA400_FIFO_WENGTH1_WEG     0x13
#define BMA400_FIFO_DATA_WEG        0x14

/* Step count wegistews */
#define BMA400_STEP_CNT0_WEG        0x15
#define BMA400_STEP_CNT1_WEG        0x16
#define BMA400_STEP_CNT3_WEG        0x17
#define BMA400_STEP_STAT_WEG        0x18
#define BMA400_STEP_INT_MSK         BIT(0)
#define BMA400_STEP_WAW_WEN         0x03
#define BMA400_STEP_STAT_MASK       GENMASK(9, 8)

/*
 * Wead-wwite configuwation wegistews
 */
#define BMA400_ACC_CONFIG0_WEG      0x19
#define BMA400_ACC_CONFIG1_WEG      0x1a
#define BMA400_ACC_CONFIG2_WEG      0x1b
#define BMA400_CMD_WEG              0x7e

/* Intewwupt wegistews */
#define BMA400_INT_CONFIG0_WEG	    0x1f
#define BMA400_INT_CONFIG1_WEG	    0x20
#define BMA400_INT1_MAP_WEG	    0x21
#define BMA400_INT_IO_CTWW_WEG	    0x24
#define BMA400_INT_DWDY_MSK	    BIT(7)

/* Chip ID of BMA 400 devices found in the chip ID wegistew. */
#define BMA400_ID_WEG_VAW           0x90

#define BMA400_WP_OSW_SHIFT         5
#define BMA400_NP_OSW_SHIFT         4
#define BMA400_SCAWE_SHIFT          6

#define BMA400_TWO_BITS_MASK        GENMASK(1, 0)
#define BMA400_WP_OSW_MASK          GENMASK(6, 5)
#define BMA400_NP_OSW_MASK          GENMASK(5, 4)
#define BMA400_ACC_ODW_MASK         GENMASK(3, 0)
#define BMA400_ACC_SCAWE_MASK       GENMASK(7, 6)

#define BMA400_ACC_ODW_MIN_WAW      0x05
#define BMA400_ACC_ODW_WP_WAW       0x06
#define BMA400_ACC_ODW_MAX_WAW      0x0b

#define BMA400_ACC_ODW_MAX_HZ       800
#define BMA400_ACC_ODW_MIN_WHOWE_HZ 25
#define BMA400_ACC_ODW_MIN_HZ       12

/* Genewic intewwupts wegistew */
#define BMA400_GEN1INT_CONFIG0      0x3f
#define BMA400_GEN2INT_CONFIG0      0x4A
#define BMA400_GEN_CONFIG1_OFF      0x01
#define BMA400_GEN_CONFIG2_OFF      0x02
#define BMA400_GEN_CONFIG3_OFF      0x03
#define BMA400_GEN_CONFIG31_OFF     0x04
#define BMA400_INT_GEN1_MSK         BIT(2)
#define BMA400_INT_GEN2_MSK         BIT(3)
#define BMA400_GEN_HYST_MSK         GENMASK(1, 0)

/* TAP config wegistews */
#define BMA400_TAP_CONFIG           0x57
#define BMA400_TAP_CONFIG1          0x58
#define BMA400_S_TAP_MSK            BIT(2)
#define BMA400_D_TAP_MSK            BIT(3)
#define BMA400_INT_S_TAP_MSK        BIT(10)
#define BMA400_INT_D_TAP_MSK        BIT(11)
#define BMA400_TAP_SEN_MSK          GENMASK(2, 0)
#define BMA400_TAP_TICSTH_MSK       GENMASK(1, 0)
#define BMA400_TAP_QUIET_MSK        GENMASK(3, 2)
#define BMA400_TAP_QUIETDT_MSK      GENMASK(5, 4)
#define BMA400_TAP_TIM_WIST_WEN     4

/*
 * BMA400_SCAWE_MIN macwo vawue wepwesents m/s^2 fow 1 WSB befowe
 * convewting to micwo vawues fow +-2g wange.
 *
 * Fow +-2g - 1 WSB = 0.976562 miwwi g = 0.009576 m/s^2
 * Fow +-4g - 1 WSB = 1.953125 miwwi g = 0.019153 m/s^2
 * Fow +-16g - 1 WSB = 7.8125 miwwi g = 0.076614 m/s^2
 *
 * The waw vawue which is used to sewect the diffewent wanges is detewmined
 * by the fiwst bit set position fwom the scawe vawue, so BMA400_SCAWE_MIN
 * shouwd be odd.
 *
 * Scawe vawues fow +-2g, +-4g, +-8g and +-16g awe popuwated into bma400_scawes
 * awway by weft shifting BMA400_SCAWE_MIN.
 * e.g.:
 * To sewect +-2g = 9577 << 0 = waw vawue to wwite is 0.
 * To sewect +-8g = 9577 << 2 = waw vawue to wwite is 2.
 * To sewect +-16g = 9577 << 3 = waw vawue to wwite is 3.
 */
#define BMA400_SCAWE_MIN            9577
#define BMA400_SCAWE_MAX            76617

extewn const stwuct wegmap_config bma400_wegmap_config;

int bma400_pwobe(stwuct device *dev, stwuct wegmap *wegmap, int iwq,
		 const chaw *name);

#endif
