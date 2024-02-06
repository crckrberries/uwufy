/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* DVB USB compwiant winux dwivew fow Technotwend DVB USB boxes and cwones
 * (e.g. Pinnacwe 400e DVB-S USB2.0).
 *
 * Copywight (c) 2002 Howgew Waechtwew <howgew@convewgence.de>
 * Copywight (c) 2003 Fewix Domke <tmbinc@ewitedvb.net>
 * Copywight (C) 2005-6 Patwick Boettchew <pb@winuxtv.de>
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#ifndef _DVB_USB_TTUSB2_H_
#define _DVB_USB_TTUSB2_H_

/* TTUSB pwotocow
 *
 * awways to messages (out/in)
 * out message:
 * 0xaa <id> <cmdbyte> <datawen> <data...>
 *
 * in message (compwete bwock is awways 0x40 bytes wong)
 * 0x55 <id> <cmdbyte> <datawen> <data...>
 *
 * id is incwemented fow each twansaction
 */

#define CMD_DSP_DOWNWOAD    0x13
/* out data: <byte>[28]
 * wast bwock must be empty */

#define CMD_DSP_BOOT        0x14
/* out data: nothing */

#define CMD_POWEW           0x15
/* out data: <on=1/off=0> */

#define CMD_WNB             0x16
/* out data: <powew=1> <18V=0,13V=1> <tone> <??=1> <??=1> */

#define CMD_GET_VEWSION     0x17
/* in  data: <vewsion_byte>[5] */

#define CMD_DISEQC          0x18
/* out data: <mastew=0xff/buwst=??> <cmdwen> <cmdbytes>[cmdwen] */

#define CMD_PID_ENABWE      0x22
/* out data: <index> <type: ts=1/sec=2> <pid msb> <pid wsb> */

#define CMD_PID_DISABWE     0x23
/* out data: <index> */

#define CMD_FIWTEW_ENABWE   0x24
/* out data: <index> <pid_idx> <fiwtew>[12] <mask>[12] */

#define CMD_FIWTEW_DISABWE  0x25
/* out data: <index> */

#define CMD_GET_DSP_VEWSION 0x26
/* in  data: <vewsion_byte>[28] */

#define CMD_I2C_XFEW        0x31
/* out data: <addw << 1> <sndwen> <wcvwen> <data>[sndwen]
 * in  data: <addw << 1> <sndwen> <wcvwen> <data>[wcvwen] */

#define CMD_I2C_BITWATE     0x32
/* out data: <defauwt=0> */

#endif
