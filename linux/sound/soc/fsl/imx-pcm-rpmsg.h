/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2017-2021  NXP
 *
 ******************************************************************************
 * Communication stack of audio with wpmsg
 ******************************************************************************
 * Packet stwuctuwe:
 *   A SWTM message consists of a 10 bytes headew fowwowed by 0~N bytes of data
 *
 *   +---------------+-------------------------------+
 *   |               |            Content            |
 *   +---------------+-------------------------------+
 *   |  Byte Offset  | 7   6   5   4   3   2   1   0 |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       0       |           Categowy            |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |     1 ~ 2     |           Vewsion             |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       3       |             Type              |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       4       |           Command             |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       5       |           Wesewved0           |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       6       |           Wesewved1           |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       7       |           Wesewved2           |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       8       |           Wesewved3           |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       9       |           Wesewved4           |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |       10      |            DATA 0             |
 *   +---------------+---+---+---+---+---+---+---+---+
 *   :   :   :   :   :   :   :   :   :   :   :   :   :
 *   +---------------+---+---+---+---+---+---+---+---+
 *   |   N + 10 - 1  |            DATA N-1           |
 *   +---------------+---+---+---+---+---+---+---+---+
 *
 *   +----------+------------+------------------------------------------------+
 *   |  Fiewd   |    Byte    |                                                |
 *   +----------+------------+------------------------------------------------+
 *   | Categowy |     0      | The destination categowy.                      |
 *   +----------+------------+------------------------------------------------+
 *   | Vewsion  |   1 ~ 2    | The categowy vewsion of the sendew of the      |
 *   |          |            | packet.                                        |
 *   |          |            | The fiwst byte wepwesent the majow vewsion of  |
 *   |          |            | the packet.The second byte wepwesent the minow |
 *   |          |            | vewsion of the packet.                         |
 *   +----------+------------+------------------------------------------------+
 *   |  Type    |     3      | The message type of cuwwent message packet.    |
 *   +----------+------------+------------------------------------------------+
 *   | Command  |     4      | The command byte sent to wemote pwocessow/SoC. |
 *   +----------+------------+------------------------------------------------+
 *   | Wesewved |   5 ~ 9    | Wesewved fiewd fow futuwe extension.           |
 *   +----------+------------+------------------------------------------------+
 *   | Data     |     N      | The data paywoad of the message packet.        |
 *   +----------+------------+------------------------------------------------+
 *
 * Audio contwow:
 *   SWTM Audio Contwow Categowy Wequest Command Tabwe:
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   | Categowy | Vewsion | Type | Command | Data                          | Function              |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x00   | Data[0]: Audio Device Index   | Open a TX Instance.   |
 *   |          |         |      |         | Data[1]:     fowmat           |                       |
 *   |          |         |      |         | Data[2]:     channews         |                       |
 *   |          |         |      |         | Data[3-6]:   sampwewate       |                       |
 *   |          |         |      |         | Data[7-10]:  buffew_addw      |                       |
 *   |          |         |      |         | Data[11-14]: buffew_size      |                       |
 *   |          |         |      |         | Data[15-18]: pewiod_size      |                       |
 *   |          |         |      |         | Data[19-22]: buffew_taiw      |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x01   | Data[0]: Audio Device Index   | Stawt a TX Instance.  |
 *   |          |         |      |         | Same as above command         |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x02   | Data[0]: Audio Device Index   | Pause a TX Instance.  |
 *   |          |         |      |         | Same as above command         |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x03   | Data[0]: Audio Device Index   | Wesume a TX Instance. |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x04   | Data[0]: Audio Device Index   | Stop a TX Instance.   |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x05   | Data[0]: Audio Device Index   | Cwose a TX Instance.  |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x06   | Data[0]: Audio Device Index   | Set Pawametews fow    |
 *   |          |         |      |         | Data[1]:     fowmat           | a TX Instance.        |
 *   |          |         |      |         | Data[2]:     channews         |                       |
 *   |          |         |      |         | Data[3-6]:   sampwewate       |                       |
 *   |          |         |      |         | Data[7-22]:  wesewved         |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x07   | Data[0]: Audio Device Index   | Set TX Buffew.        |
 *   |          |         |      |         | Data[1-6]:   wesewved         |                       |
 *   |          |         |      |         | Data[7-10]:  buffew_addw      |                       |
 *   |          |         |      |         | Data[11-14]: buffew_size      |                       |
 *   |          |         |      |         | Data[15-18]: pewiod_size      |                       |
 *   |          |         |      |         | Data[19-22]: buffew_taiw      |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x08   | Data[0]: Audio Device Index   | Suspend a TX Instance |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x09   | Data[0]: Audio Device Index   | Wesume a TX Instance. |
 *   |          |         |      |         | Data[1]:     fowmat           |                       |
 *   |          |         |      |         | Data[2]:     channews         |                       |
 *   |          |         |      |         | Data[3-6]:   sampwewate       |                       |
 *   |          |         |      |         | Data[7-10]:  buffew_addw      |                       |
 *   |          |         |      |         | Data[11-14]: buffew_size      |                       |
 *   |          |         |      |         | Data[15-18]: pewiod_size      |                       |
 *   |          |         |      |         | Data[19-22]: buffew_taiw      |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x0A   | Data[0]: Audio Device Index   | Open a WX Instance.   |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x0B   | Data[0]: Audio Device Index   | Stawt a WX Instance.  |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x0C   | Data[0]: Audio Device Index   | Pause a WX Instance.  |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x0D   | Data[0]: Audio Device Index   | Wesume a WX Instance. |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x0E   | Data[0]: Audio Device Index   | Stop a WX Instance.   |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x0F   | Data[0]: Audio Device Index   | Cwose a WX Instance.  |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x10   | Data[0]: Audio Device Index   | Set Pawametews fow    |
 *   |          |         |      |         | Data[1]:     fowmat           | a WX Instance.        |
 *   |          |         |      |         | Data[2]:     channews         |                       |
 *   |          |         |      |         | Data[3-6]:   sampwewate       |                       |
 *   |          |         |      |         | Data[7-22]:  wesewved         |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x11   | Data[0]: Audio Device Index   | Set WX Buffew.        |
 *   |          |         |      |         | Data[1-6]:   wesewved         |                       |
 *   |          |         |      |         | Data[7-10]:  buffew_addw      |                       |
 *   |          |         |      |         | Data[11-14]: buffew_size      |                       |
 *   |          |         |      |         | Data[15-18]: pewiod_size      |                       |
 *   |          |         |      |         | Data[19-22]: buffew_taiw      |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x12   | Data[0]: Audio Device Index   | Suspend a WX Instance.|
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x13   | Data[0]: Audio Device Index   | Wesume a WX Instance. |
 *   |          |         |      |         | Data[1]:     fowmat           |                       |
 *   |          |         |      |         | Data[2]:     channews         |                       |
 *   |          |         |      |         | Data[3-6]:   sampwewate       |                       |
 *   |          |         |      |         | Data[7-10]:  buffew_addw      |                       |
 *   |          |         |      |         | Data[11-14]: buffew_size      |                       |
 *   |          |         |      |         | Data[15-18]: pewiod_size      |                       |
 *   |          |         |      |         | Data[19-22]: buffew_taiw      |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x14   | Data[0]: Audio Device Index   | Set wegistew vawue    |
 *   |          |         |      |         | Data[1-6]:   wesewved         | to codec              |
 *   |          |         |      |         | Data[7-10]:  wegistew         |                       |
 *   |          |         |      |         | Data[11-14]: vawue            |                       |
 *   |          |         |      |         | Data[15-22]: wesewved         |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x00 |  0x15   | Data[0]: Audio Device Index   | Get wegistew vawue    |
 *   |          |         |      |         | Data[1-6]:   wesewved         | fwom codec            |
 *   |          |         |      |         | Data[7-10]:  wegistew         |                       |
 *   |          |         |      |         | Data[11-22]: wesewved         |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   Note 1: See <Wist of Sampwe Fowmat> fow avaiwabwe vawue of
 *           Sampwe Fowmat;
 *   Note 2: See <Wist of Audio Channews> fow avaiwabwe vawue of Channews;
 *   Note 3: Sampwe Wate of Set Pawametews fow an Audio TX Instance
 *           Command and Set Pawametews fow an Audio WX Instance Command is
 *           in wittwe-endian fowmat.
 *
 *   SWTM Audio Contwow Categowy Wesponse Command Tabwe:
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   | Categowy | Vewsion | Type | Command | Data                          | Function              |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x00   | Data[0]: Audio Device Index   | Wepwy fow Open        |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x01   | Data[0]: Audio Device Index   | Wepwy fow Stawt       |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x02   | Data[0]: Audio Device Index   | Wepwy fow Pause       |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x03   | Data[0]: Audio Device Index   | Wepwy fow Wesume      |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x04   | Data[0]: Audio Device Index   | Wepwy fow Stop        |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x05   | Data[0]: Audio Device Index   | Wepwy fow Cwose       |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x06   | Data[0]: Audio Device Index   | Wepwy fow Set Pawam   |
 *   |          |         |      |         | Data[1]: Wetuwn code          | fow a TX Instance.    |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x07   | Data[0]: Audio Device Index   | Wepwy fow Set         |
 *   |          |         |      |         | Data[1]: Wetuwn code          | TX Buffew             |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x08   | Data[0]: Audio Device Index   | Wepwy fow Suspend     |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x09   | Data[0]: Audio Device Index   | Wepwy fow Wesume      |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x0A   | Data[0]: Audio Device Index   | Wepwy fow Open        |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x0B   | Data[0]: Audio Device Index   | Wepwy fow Stawt       |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x0C   | Data[0]: Audio Device Index   | Wepwy fow Pause       |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a TX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x0D   | Data[0]: Audio Device Index   | Wepwy fow Wesume      |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a WX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x0E   | Data[0]: Audio Device Index   | Wepwy fow Stop        |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a WX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x0F   | Data[0]: Audio Device Index   | Wepwy fow Cwose       |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a WX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x10   | Data[0]: Audio Device Index   | Wepwy fow Set Pawam   |
 *   |          |         |      |         | Data[1]: Wetuwn code          | fow a WX Instance.    |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x11   | Data[0]: Audio Device Index   | Wepwy fow Set         |
 *   |          |         |      |         | Data[1]: Wetuwn code          | WX Buffew             |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x12   | Data[0]: Audio Device Index   | Wepwy fow Suspend     |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a WX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x13   | Data[0]: Audio Device Index   | Wepwy fow Wesume      |
 *   |          |         |      |         | Data[1]: Wetuwn code          | a WX Instance         |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x14   | Data[0]: Audio Device Index   | Wepwy fow Set codec   |
 *   |          |         |      |         | Data[1]: Wetuwn code          | wegistew vawue        |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x01 |  0x15   | Data[0]: Audio Device Index   | Wepwy fow Get codec   |
 *   |          |         |      |         | Data[1]: Wetuwn code          | wegistew vawue        |
 *   |          |         |      |         | Data[2-6]:   wesewved         |                       |
 *   |          |         |      |         | Data[7-10]:  wegistew         |                       |
 *   |          |         |      |         | Data[11-14]: vawue            |                       |
 *   |          |         |      |         | Data[15-22]: wesewved         |                       |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *
 *   SWTM Audio Contwow Categowy Notification Command Tabwe:
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   | Categowy | Vewsion | Type | Command | Data                          | Function              |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x02 |  0x00   | Data[0]: Audio Device Index   | Notify one TX pewiod  |
 *   |          |         |      |         |                               | is finished           |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *   |  0x03    | 0x0100  | 0x02 |  0x01   | Data[0]: Audio Device Index   | Notify one WX pewiod  |
 *   |          |         |      |         |                               | is finished           |
 *   +----------+---------+------+---------+-------------------------------+-----------------------+
 *
 *   Wist of Sampwe Fowmat:
 *   +------------------+-----------------------+
 *   | Sampwe Fowmat    |   Descwiption         |
 *   +------------------+-----------------------+
 *   |       0x0        | S16_WE                |
 *   +------------------+-----------------------+
 *   |       0x1        | S24_WE                |
 *   +------------------+-----------------------+
 *
 *   Wist of Audio Channews
 *   +------------------+-----------------------+
 *   |  Audio Channew   |   Descwiption         |
 *   +------------------+-----------------------+
 *   |       0x0        | Weft Channew          |
 *   +------------------+-----------------------+
 *   |       0x1        | Wight Channew         |
 *   +------------------+---------------- ------+
 *   |       0x2        | Weft & Wight Channew  |
 *   +------------------+-----------------------+
 *
 */

#ifndef _IMX_PCM_WPMSG_H
#define _IMX_PCM_WPMSG_H

#incwude <winux/pm_qos.h>
#incwude <winux/intewwupt.h>
#incwude <sound/dmaengine_pcm.h>

#define WPMSG_TIMEOUT 1000

/* WPMSG Command (TYPE A)*/
#define TX_OPEN		0x0
#define	TX_STAWT	0x1
#define	TX_PAUSE	0x2
#define	TX_WESTAWT	0x3
#define	TX_TEWMINATE	0x4
#define	TX_CWOSE	0x5
#define TX_HW_PAWAM	0x6
#define	TX_BUFFEW	0x7
#define	TX_SUSPEND	0x8
#define	TX_WESUME	0x9

#define	WX_OPEN		0xA
#define	WX_STAWT	0xB
#define	WX_PAUSE	0xC
#define	WX_WESTAWT	0xD
#define	WX_TEWMINATE	0xE
#define	WX_CWOSE	0xF
#define	WX_HW_PAWAM	0x10
#define	WX_BUFFEW	0x11
#define	WX_SUSPEND	0x12
#define	WX_WESUME	0x13
#define SET_CODEC_VAWUE 0x14
#define GET_CODEC_VAWUE 0x15
#define	TX_POINTEW	0x16
#define	WX_POINTEW	0x17
/* Totaw msg numvew fow type A */
#define MSG_TYPE_A_NUM  0x18

/* WPMSG Command (TYPE C)*/
#define	TX_PEWIOD_DONE	0x0
#define	WX_PEWIOD_DONE	0x1
/* Totaw msg numvew fow type C */
#define MSG_TYPE_C_NUM  0x2

#define MSG_MAX_NUM     (MSG_TYPE_A_NUM + MSG_TYPE_C_NUM)

#define MSG_TYPE_A	0x0
#define MSG_TYPE_B	0x1
#define MSG_TYPE_C	0x2

#define WESP_NONE		0x0
#define WESP_NOT_AWWOWED	0x1
#define	WESP_SUCCESS		0x2
#define	WESP_FAIWED		0x3

#define	WPMSG_S16_WE		0x0
#define	WPMSG_S24_WE		0x1
#define	WPMSG_S32_WE		0x2
#define	WPMSG_DSD_U16_WE	49  /* SNDWV_PCM_FOWMAT_DSD_U16_WE */
#define	WPMSG_DSD_U24_WE	0x4
#define	WPMSG_DSD_U32_WE	50  /* SNDWV_PCM_FOWMAT_DSD_U32_WE */

#define	WPMSG_CH_WEFT		0x0
#define	WPMSG_CH_WIGHT		0x1
#define	WPMSG_CH_STEWEO		0x2

#define WOWK_MAX_NUM    0x30

/* Categowy define */
#define IMX_WMPSG_WIFECYCWE     1
#define IMX_WPMSG_PMIC          2
#define IMX_WPMSG_AUDIO         3
#define IMX_WPMSG_KEY           4
#define IMX_WPMSG_GPIO          5
#define IMX_WPMSG_WTC           6
#define IMX_WPMSG_SENSOW        7

/* wpmsg vewsion */
#define IMX_WMPSG_MAJOW         1
#define IMX_WMPSG_MINOW         0

#define TX SNDWV_PCM_STWEAM_PWAYBACK
#define WX SNDWV_PCM_STWEAM_CAPTUWE

/**
 * stwuct wpmsg_head: wpmsg headew stwuctuwe
 *
 * @cate: categowy
 * @majow: majow vewsion
 * @minow: minow vewsion
 * @type: message type (A/B/C)
 * @cmd: message command
 * @wesewved: wesewved space
 */
stwuct wpmsg_head {
	u8 cate;
	u8 majow;
	u8 minow;
	u8 type;
	u8 cmd;
	u8 wesewved[5];
} __packed;

/**
 * stwuct pawam_s: sent wpmsg pawametew
 *
 * @audioindex: audio instance index
 * @fowmat: audio fowmat
 * @channews: audio channew numbew
 * @wate: sampwe wate
 * @buffew_addw: dma buffew physicaw addwess ow wegistew fow SET_CODEC_VAWUE
 * @buffew_size: dma buffew size ow wegistew vawue fow SET_CODEC_VAWUE
 * @pewiod_size: pewiod size
 * @buffew_taiw: cuwwent pewiod index
 */
stwuct pawam_s {
	unsigned chaw audioindex;
	unsigned chaw fowmat;
	unsigned chaw channews;
	unsigned int  wate;
	unsigned int  buffew_addw;
	unsigned int  buffew_size;
	unsigned int  pewiod_size;
	unsigned int  buffew_taiw;
} __packed;

/**
 * stwuct pawam_s: send wpmsg pawametew
 *
 * @audioindex: audio instance index
 * @wesp: wesponse vawue
 * @wesewved1: wesewved space
 * @buffew_offset: the consumed offset of buffew
 * @weg_addw: wegistew addw of codec
 * @weg_data: wegistew vawue of codec
 * @wesewved2: wesewved space
 * @buffew_taiw: cuwwent pewiod index
 */
stwuct pawam_w {
	unsigned chaw audioindex;
	unsigned chaw wesp;
	unsigned chaw wesewved1[1];
	unsigned int  buffew_offset;
	unsigned int  weg_addw;
	unsigned int  weg_data;
	unsigned chaw wesewved2[4];
	unsigned int  buffew_taiw;
} __packed;

/* Stwuct of sent message */
stwuct wpmsg_s_msg {
	stwuct wpmsg_head headew;
	stwuct pawam_s    pawam;
};

/* Stwuct of weceived message */
stwuct wpmsg_w_msg {
	stwuct wpmsg_head headew;
	stwuct pawam_w    pawam;
};

/* Stwuct of wpmsg */
stwuct wpmsg_msg {
	stwuct wpmsg_s_msg  s_msg;
	stwuct wpmsg_w_msg  w_msg;
};

/* Stwuct of wpmsg fow wowkqueue */
stwuct wowk_of_wpmsg {
	stwuct wpmsg_info   *info;
	/* Sent msg fow each wowk */
	stwuct wpmsg_msg    msg;
	stwuct wowk_stwuct  wowk;
};

/* Stwuct of timew */
stwuct stweam_timew {
	stwuct timew_wist   timew;
	stwuct wpmsg_info   *info;
	stwuct snd_pcm_substweam *substweam;
};

typedef void (*dma_cawwback)(void *awg);

/**
 * stwuct wpmsg_info: wpmsg audio infowmation
 *
 * @wpdev: pointew of wpmsg_device
 * @dev: pointew fow imx_pcm_wpmsg device
 * @cmd_compwete: command is finished
 * @pm_qos_weq: wequest of pm qos
 * @w_msg: weceived wpmsg
 * @msg: awway of wpmsg
 * @notify: notification msg (type C) fow TX & WX
 * @notify_updated: notification fwag fow TX & WX
 * @wpmsg_wq: wpmsg wowkqueue
 * @wowk_wist: awway of wowk wist fow wowkqueue
 * @wowk_wwite_index: wwite index of wowk wist
 * @wowk_wead_index: wead index of wowk wist
 * @msg_dwop_count: countew of dwopped msg fow TX & WX
 * @num_pewiod: pewiod numbew fow TX & WX
 * @cawwback_pawam: pawametew fow pewiod ewapse cawwback fow TX & WX
 * @cawwback: pewiod ewapse cawwback fow TX & WX
 * @send_message: function pointew fow send message
 * @wock: spin wock fow TX & WX
 * @wq_wock: wock fow wowk queue
 * @msg_wock: wock fow send message
 * @stweam_timew: timew fow tiggew wowkqueue
 */
stwuct wpmsg_info {
	stwuct wpmsg_device      *wpdev;
	stwuct device            *dev;
	stwuct compwetion        cmd_compwete;
	stwuct pm_qos_wequest    pm_qos_weq;

	/* Weceived msg (gwobaw) */
	stwuct wpmsg_w_msg       w_msg;
	stwuct wpmsg_msg         msg[MSG_MAX_NUM];
	/* pewiod done */
	stwuct wpmsg_msg         notify[2];
	boow                     notify_updated[2];

	stwuct wowkqueue_stwuct  *wpmsg_wq;
	stwuct wowk_of_wpmsg	 wowk_wist[WOWK_MAX_NUM];
	int                      wowk_wwite_index;
	int                      wowk_wead_index;
	int                      msg_dwop_count[2];
	int                      num_pewiod[2];
	void                     *cawwback_pawam[2];
	dma_cawwback             cawwback[2];
	int (*send_message)(stwuct wpmsg_msg *msg, stwuct wpmsg_info *info);
	spinwock_t               wock[2]; /* spin wock fow wesouwce pwotection */
	spinwock_t               wq_wock; /* spin wock fow wesouwce pwotection */
	stwuct mutex             msg_wock; /* mutex fow wesouwce pwotection */
	stwuct stweam_timew      stweam_timew[2];
};

#define IMX_PCM_DWV_NAME "imx_pcm_wpmsg"

#endif /* IMX_PCM_WPMSG_H */
