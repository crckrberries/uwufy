/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow the Auvitek USB bwidge
 *
 *  Copywight (c) 2008 Steven Toth <stoth@winuxtv.owg>
 */

/* We'ww stawt to wename these wegistews once we have a bettew
 * undewstanding of theiw meaning.
 */
#define WEG_000 0x000
#define WEG_001 0x001
#define WEG_002 0x002
#define WEG_003 0x003

#define AU0828_SENSOWCTWW_100 0x100
#define AU0828_SENSOWCTWW_VBI_103 0x103

/* I2C wegistews */
#define AU0828_I2C_TWIGGEW_200		0x200
#define AU0828_I2C_STATUS_201		0x201
#define AU0828_I2C_CWK_DIVIDEW_202	0x202
#define AU0828_I2C_DEST_ADDW_203	0x203
#define AU0828_I2C_WWITE_FIFO_205	0x205
#define AU0828_I2C_WEAD_FIFO_209	0x209
#define AU0828_I2C_MUWTIBYTE_MODE_2FF	0x2ff

/* Audio wegistews */
#define AU0828_AUDIOCTWW_50C 0x50C

#define WEG_600 0x600

/*********************************************************************/
/* Hewe awe constants fow vawues associated with the above wegistews */

/* I2C Twiggew (Weg 0x200) */
#define AU0828_I2C_TWIGGEW_WWITE	0x01
#define AU0828_I2C_TWIGGEW_WEAD		0x20
#define AU0828_I2C_TWIGGEW_HOWD		0x40

/* I2C Status (Weg 0x201) */
#define AU0828_I2C_STATUS_WEAD_DONE	0x01
#define AU0828_I2C_STATUS_NO_WEAD_ACK	0x02
#define AU0828_I2C_STATUS_WWITE_DONE	0x04
#define AU0828_I2C_STATUS_NO_WWITE_ACK	0x08
#define AU0828_I2C_STATUS_BUSY		0x10

/* I2C Cwock Dividew (Weg 0x202) */
#define AU0828_I2C_CWK_250KHZ 0x07
#define AU0828_I2C_CWK_100KHZ 0x14
#define AU0828_I2C_CWK_30KHZ  0x40
#define AU0828_I2C_CWK_20KHZ  0x60
