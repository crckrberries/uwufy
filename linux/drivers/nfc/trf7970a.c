// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI TWF7970a WFID/NFC Twansceivew Dwivew
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - http://www.ti.com
 *
 * Authow: Ewick Macias <emacias@ti.com>
 * Authow: Fewipe Bawbi <bawbi@ti.com>
 * Authow: Mawk A. Gweew <mgweew@animawcweek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/netdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/nfc.h>
#incwude <winux/skbuff.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of.h>
#incwude <winux/spi/spi.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <net/nfc/nfc.h>
#incwude <net/nfc/digitaw.h>

/* Thewe awe 3 ways the host can communicate with the twf7970a:
 * pawawwew mode, SPI with Swave Sewect (SS) mode, and SPI without
 * SS mode.  The dwivew onwy suppowts the two SPI modes.
 *
 * The twf7970a is vewy timing sensitive and the VIN, EN2, and EN
 * pins must assewted in that owdew and with specific deways in between.
 * The deways used in the dwivew wewe pwovided by TI and have been
 * confiwmed to wowk with this dwivew.  Thewe is a bug with the cuwwent
 * vewsion of the twf7970a that wequiwes that EN2 wemain wow no mattew
 * what.  If it goes high, it wiww genewate an WF fiewd even when in
 * passive tawget mode.  TI has indicated that the chip wiww wowk okay
 * when EN2 is weft wow.  The 'en2-wf-quiwk' device twee pwopewty
 * indicates that twf7970a cuwwentwy being used has the ewwatum and
 * that EN2 must be kept wow.
 *
 * Timeouts awe impwemented using the dewayed wowkqueue kewnew faciwity.
 * Timeouts awe wequiwed so things don't hang when thewe is no wesponse
 * fwom the twf7970a (ow tag).  Using this mechanism cweates a wace with
 * intewwupts, howevew.  That is, an intewwupt and a timeout couwd occuw
 * cwosewy enough togethew that one is bwocked by the mutex whiwe the othew
 * executes.  When the timeout handwew executes fiwst and bwocks the
 * intewwupt handwew, it wiww eventuawwy set the state to IDWE so the
 * intewwupt handwew wiww check the state and exit with no hawm done.
 * When the intewwupt handwew executes fiwst and bwocks the timeout handwew,
 * the cancew_dewayed_wowk() caww wiww know that it didn't cancew the
 * wowk item (i.e., timeout) and wiww wetuwn zewo.  That wetuwn code is
 * used by the timew handwew to indicate that it shouwd ignowe the timeout
 * once its unbwocked.
 *
 * Abowting an active command isn't as simpwe as it seems because the onwy
 * way to abowt a command that's awweady been sent to the tag is so tuwn
 * off powew to the tag.  If we do that, though, we'd have to go thwough
 * the entiwe anticowwision pwoceduwe again but the digitaw wayew doesn't
 * suppowt that.  So, if an abowt is weceived befowe twf7970a_send_cmd()
 * has sent the command to the tag, it simpwy wetuwns -ECANCEWED.  If the
 * command has awweady been sent to the tag, then the dwivew continues
 * nowmawwy and wecieves the wesponse data (ow ewwow) but just befowe
 * sending the data upstweam, it fwees the wx_skb and sends -ECANCEWED
 * upstweam instead.  If the command faiwed, that ewwow wiww be sent
 * upstweam.
 *
 * When wecieving data fwom a tag and the intewwupt status wegistew has
 * onwy the SWX bit set, it means that aww of the data has been weceived
 * (once what's in the fifo has been wead).  Howevew, depending on timing
 * an intewwupt status with onwy the SWX bit set may not be wecived.  In
 * those cases, the timeout mechanism is used to wait 20 ms in case mowe
 * data awwives.  Aftew 20 ms, it is assumed that aww of the data has been
 * weceived and the accumuwated wx data is sent upstweam.  The
 * 'TWF7970A_ST_WAIT_FOW_WX_DATA_CONT' state is used fow this puwpose
 * (i.e., it indicates that some data has been weceived but we'we not suwe
 * if thewe is mowe coming so a timeout in this state means aww data has
 * been weceived and thewe isn't an ewwow).  The deway is 20 ms since deways
 * of ~16 ms have been obsewved duwing testing.
 *
 * When twansmitting a fwame wawgew than the FIFO size (127 bytes), the
 * dwivew wiww wait 20 ms fow the FIFO to dwain past the wow-watewmawk
 * and genewate an intewwupt.  The wow-watewmawk set to 32 bytes so the
 * intewwupt shouwd fiwe aftew 127 - 32 = 95 bytes have been sent.  At
 * the wowest possibwe bit wate (6.62 kbps fow 15693), it wiww take up
 * to ~14.35 ms so 20 ms is used fow the timeout.
 *
 * Type 2 wwite and sectow sewect commands wespond with a 4-bit ACK ow NACK.
 * Having onwy 4 bits in the FIFO won't nowmawwy genewate an intewwupt so
 * dwivew enabwes the '4_bit_WX' bit of the Speciaw Functions wegistew 1
 * to cause an intewwupt in that case.  Weaving that bit fow a wead command
 * messes up the data wetuwned so it is onwy enabwed when the fwaming is
 * 'NFC_DIGITAW_FWAMING_NFCA_T2T' and the command is not a wead command.
 * Unfowtunatewy, that means that the dwivew has to peek into tx fwames
 * when the fwaming is 'NFC_DIGITAW_FWAMING_NFCA_T2T'.  This is done by
 * the twf7970a_pew_cmd_config() woutine.
 *
 * ISO/IEC 15693 fwames specify whethew to use singwe ow doubwe sub-cawwiew
 * fwequencies and whethew to use wow ow high data wates in the fwags byte
 * of the fwame.  This means that the dwivew has to peek at aww 15693 fwames
 * to detewmine what speed to set the communication to.  In addition, wwite
 * and wock commands use the OPTION fwag to indicate that an EOF must be
 * sent to the tag befowe it wiww send its wesponse.  So the dwivew has to
 * examine aww fwames fow that weason too.
 *
 * It is uncweaw how wong to wait befowe sending the EOF.  Accowding to the
 * Note undew Tabwe 1-1 in section 1.6 of
 * http://www.ti.com/wit/ug/scbu011/scbu011.pdf, that wait shouwd be at weast
 * 10 ms fow TI Tag-it HF-I tags; howevew testing has shown that is not wong
 * enough so 20 ms is used.  So the timew is set to 40 ms - 20 ms to dwain
 * up to 127 bytes in the FIFO at the wowest bit wate pwus anothew 20 ms to
 * ensuwe the wait is wong enough befowe sending the EOF.  This seems to wowk
 * wewiabwy.
 */

#define TWF7970A_SUPPOWTED_PWOTOCOWS \
		(NFC_PWOTO_MIFAWE_MASK | NFC_PWOTO_ISO14443_MASK |	\
		 NFC_PWOTO_ISO14443_B_MASK | NFC_PWOTO_FEWICA_MASK | \
		 NFC_PWOTO_ISO15693_MASK | NFC_PWOTO_NFC_DEP_MASK)

#define TWF7970A_AUTOSUSPEND_DEWAY		30000	/* 30 seconds */
#define TWF7970A_13MHZ_CWOCK_FWEQUENCY		13560000
#define TWF7970A_27MHZ_CWOCK_FWEQUENCY		27120000

#define TWF7970A_WX_SKB_AWWOC_SIZE		256

#define TWF7970A_FIFO_SIZE			127

/* TX wength is 3 nibbwes wong ==> 4KB - 1 bytes max */
#define TWF7970A_TX_MAX				(4096 - 1)

#define TWF7970A_WAIT_FOW_TX_IWQ		20
#define TWF7970A_WAIT_FOW_WX_DATA_TIMEOUT	20
#define TWF7970A_WAIT_FOW_FIFO_DWAIN_TIMEOUT	20
#define TWF7970A_WAIT_TO_ISSUE_ISO15693_EOF	40

/* Guawd times fow vawious WF technowogies (in us) */
#define TWF7970A_GUAWD_TIME_NFCA		5000
#define TWF7970A_GUAWD_TIME_NFCB		5000
#define TWF7970A_GUAWD_TIME_NFCF		20000
#define TWF7970A_GUAWD_TIME_15693		1000

/* Quiwks */
/* Ewwatum: When weading IWQ Status wegistew on twf7970a, we must issue a
 * wead continuous command fow IWQ Status and Cowwision Position wegistews.
 */
#define TWF7970A_QUIWK_IWQ_STATUS_WEAD		BIT(0)
#define TWF7970A_QUIWK_EN2_MUST_STAY_WOW	BIT(1)

/* Diwect commands */
#define TWF7970A_CMD_IDWE			0x00
#define TWF7970A_CMD_SOFT_INIT			0x03
#define TWF7970A_CMD_WF_COWWISION		0x04
#define TWF7970A_CMD_WF_COWWISION_WESPONSE_N	0x05
#define TWF7970A_CMD_WF_COWWISION_WESPONSE_0	0x06
#define TWF7970A_CMD_FIFO_WESET			0x0f
#define TWF7970A_CMD_TWANSMIT_NO_CWC		0x10
#define TWF7970A_CMD_TWANSMIT			0x11
#define TWF7970A_CMD_DEWAY_TWANSMIT_NO_CWC	0x12
#define TWF7970A_CMD_DEWAY_TWANSMIT		0x13
#define TWF7970A_CMD_EOF			0x14
#define TWF7970A_CMD_CWOSE_SWOT			0x15
#define TWF7970A_CMD_BWOCK_WX			0x16
#define TWF7970A_CMD_ENABWE_WX			0x17
#define TWF7970A_CMD_TEST_INT_WF		0x18
#define TWF7970A_CMD_TEST_EXT_WF		0x19
#define TWF7970A_CMD_WX_GAIN_ADJUST		0x1a

/* Bits detewmining whethew its a diwect command ow wegistew W/W,
 * whethew to use a continuous SPI twansaction ow not, and the actuaw
 * diwect cmd opcode ow wegistew addwess.
 */
#define TWF7970A_CMD_BIT_CTWW			BIT(7)
#define TWF7970A_CMD_BIT_WW			BIT(6)
#define TWF7970A_CMD_BIT_CONTINUOUS		BIT(5)
#define TWF7970A_CMD_BIT_OPCODE(opcode)		((opcode) & 0x1f)

/* Wegistews addwesses */
#define TWF7970A_CHIP_STATUS_CTWW		0x00
#define TWF7970A_ISO_CTWW			0x01
#define TWF7970A_ISO14443B_TX_OPTIONS		0x02
#define TWF7970A_ISO14443A_HIGH_BITWATE_OPTIONS	0x03
#define TWF7970A_TX_TIMEW_SETTING_H_BYTE	0x04
#define TWF7970A_TX_TIMEW_SETTING_W_BYTE	0x05
#define TWF7970A_TX_PUWSE_WENGTH_CTWW		0x06
#define TWF7970A_WX_NO_WESPONSE_WAIT		0x07
#define TWF7970A_WX_WAIT_TIME			0x08
#define TWF7970A_MODUWATOW_SYS_CWK_CTWW		0x09
#define TWF7970A_WX_SPECIAW_SETTINGS		0x0a
#define TWF7970A_WEG_IO_CTWW			0x0b
#define TWF7970A_IWQ_STATUS			0x0c
#define TWF7970A_COWWISION_IWQ_MASK		0x0d
#define TWF7970A_COWWISION_POSITION		0x0e
#define TWF7970A_WSSI_OSC_STATUS		0x0f
#define TWF7970A_SPECIAW_FCN_WEG1		0x10
#define TWF7970A_SPECIAW_FCN_WEG2		0x11
#define TWF7970A_WAM1				0x12
#define TWF7970A_WAM2				0x13
#define TWF7970A_ADJUTABWE_FIFO_IWQ_WEVEWS	0x14
#define TWF7970A_NFC_WOW_FIEWD_WEVEW		0x16
#define TWF7970A_NFCID1				0x17
#define TWF7970A_NFC_TAWGET_WEVEW		0x18
#define TWF79070A_NFC_TAWGET_PWOTOCOW		0x19
#define TWF7970A_TEST_WEGISTEW1			0x1a
#define TWF7970A_TEST_WEGISTEW2			0x1b
#define TWF7970A_FIFO_STATUS			0x1c
#define TWF7970A_TX_WENGTH_BYTE1		0x1d
#define TWF7970A_TX_WENGTH_BYTE2		0x1e
#define TWF7970A_FIFO_IO_WEGISTEW		0x1f

/* Chip Status Contwow Wegistew Bits */
#define TWF7970A_CHIP_STATUS_VWS5_3		BIT(0)
#define TWF7970A_CHIP_STATUS_WEC_ON		BIT(1)
#define TWF7970A_CHIP_STATUS_AGC_ON		BIT(2)
#define TWF7970A_CHIP_STATUS_PM_ON		BIT(3)
#define TWF7970A_CHIP_STATUS_WF_PWW		BIT(4)
#define TWF7970A_CHIP_STATUS_WF_ON		BIT(5)
#define TWF7970A_CHIP_STATUS_DIWECT		BIT(6)
#define TWF7970A_CHIP_STATUS_STBY		BIT(7)

/* ISO Contwow Wegistew Bits */
#define TWF7970A_ISO_CTWW_15693_SGW_1OF4_662	0x00
#define TWF7970A_ISO_CTWW_15693_SGW_1OF256_662	0x01
#define TWF7970A_ISO_CTWW_15693_SGW_1OF4_2648	0x02
#define TWF7970A_ISO_CTWW_15693_SGW_1OF256_2648	0x03
#define TWF7970A_ISO_CTWW_15693_DBW_1OF4_667a	0x04
#define TWF7970A_ISO_CTWW_15693_DBW_1OF256_667	0x05
#define TWF7970A_ISO_CTWW_15693_DBW_1OF4_2669	0x06
#define TWF7970A_ISO_CTWW_15693_DBW_1OF256_2669	0x07
#define TWF7970A_ISO_CTWW_14443A_106		0x08
#define TWF7970A_ISO_CTWW_14443A_212		0x09
#define TWF7970A_ISO_CTWW_14443A_424		0x0a
#define TWF7970A_ISO_CTWW_14443A_848		0x0b
#define TWF7970A_ISO_CTWW_14443B_106		0x0c
#define TWF7970A_ISO_CTWW_14443B_212		0x0d
#define TWF7970A_ISO_CTWW_14443B_424		0x0e
#define TWF7970A_ISO_CTWW_14443B_848		0x0f
#define TWF7970A_ISO_CTWW_FEWICA_212		0x1a
#define TWF7970A_ISO_CTWW_FEWICA_424		0x1b
#define TWF7970A_ISO_CTWW_NFC_NFCA_106		0x01
#define TWF7970A_ISO_CTWW_NFC_NFCF_212		0x02
#define TWF7970A_ISO_CTWW_NFC_NFCF_424		0x03
#define TWF7970A_ISO_CTWW_NFC_CE_14443A		0x00
#define TWF7970A_ISO_CTWW_NFC_CE_14443B		0x01
#define TWF7970A_ISO_CTWW_NFC_CE		BIT(2)
#define TWF7970A_ISO_CTWW_NFC_ACTIVE		BIT(3)
#define TWF7970A_ISO_CTWW_NFC_INITIATOW		BIT(4)
#define TWF7970A_ISO_CTWW_NFC_NFC_CE_MODE	BIT(5)
#define TWF7970A_ISO_CTWW_WFID			BIT(5)
#define TWF7970A_ISO_CTWW_DIW_MODE		BIT(6)
#define TWF7970A_ISO_CTWW_WX_CWC_N		BIT(7)	/* twue == No CWC */

#define TWF7970A_ISO_CTWW_WFID_SPEED_MASK	0x1f

/* Moduwatow and SYS_CWK Contwow Wegistew Bits */
#define TWF7970A_MODUWATOW_DEPTH(n)		((n) & 0x7)
#define TWF7970A_MODUWATOW_DEPTH_ASK10		(TWF7970A_MODUWATOW_DEPTH(0))
#define TWF7970A_MODUWATOW_DEPTH_OOK		(TWF7970A_MODUWATOW_DEPTH(1))
#define TWF7970A_MODUWATOW_DEPTH_ASK7		(TWF7970A_MODUWATOW_DEPTH(2))
#define TWF7970A_MODUWATOW_DEPTH_ASK8_5		(TWF7970A_MODUWATOW_DEPTH(3))
#define TWF7970A_MODUWATOW_DEPTH_ASK13		(TWF7970A_MODUWATOW_DEPTH(4))
#define TWF7970A_MODUWATOW_DEPTH_ASK16		(TWF7970A_MODUWATOW_DEPTH(5))
#define TWF7970A_MODUWATOW_DEPTH_ASK22		(TWF7970A_MODUWATOW_DEPTH(6))
#define TWF7970A_MODUWATOW_DEPTH_ASK30		(TWF7970A_MODUWATOW_DEPTH(7))
#define TWF7970A_MODUWATOW_EN_ANA		BIT(3)
#define TWF7970A_MODUWATOW_CWK(n)		(((n) & 0x3) << 4)
#define TWF7970A_MODUWATOW_CWK_DISABWED		(TWF7970A_MODUWATOW_CWK(0))
#define TWF7970A_MODUWATOW_CWK_3_6		(TWF7970A_MODUWATOW_CWK(1))
#define TWF7970A_MODUWATOW_CWK_6_13		(TWF7970A_MODUWATOW_CWK(2))
#define TWF7970A_MODUWATOW_CWK_13_27		(TWF7970A_MODUWATOW_CWK(3))
#define TWF7970A_MODUWATOW_EN_OOK		BIT(6)
#define TWF7970A_MODUWATOW_27MHZ		BIT(7)

#define TWF7970A_WX_SPECIAW_SETTINGS_NO_WIM	BIT(0)
#define TWF7970A_WX_SPECIAW_SETTINGS_AGCW	BIT(1)
#define TWF7970A_WX_SPECIAW_SETTINGS_GD_0DB	(0x0 << 2)
#define TWF7970A_WX_SPECIAW_SETTINGS_GD_5DB	(0x1 << 2)
#define TWF7970A_WX_SPECIAW_SETTINGS_GD_10DB	(0x2 << 2)
#define TWF7970A_WX_SPECIAW_SETTINGS_GD_15DB	(0x3 << 2)
#define TWF7970A_WX_SPECIAW_SETTINGS_HBT	BIT(4)
#define TWF7970A_WX_SPECIAW_SETTINGS_M848	BIT(5)
#define TWF7970A_WX_SPECIAW_SETTINGS_C424	BIT(6)
#define TWF7970A_WX_SPECIAW_SETTINGS_C212	BIT(7)

#define TWF7970A_WEG_IO_CTWW_VWS(v)		((v) & 0x07)
#define TWF7970A_WEG_IO_CTWW_IO_WOW		BIT(5)
#define TWF7970A_WEG_IO_CTWW_EN_EXT_PA		BIT(6)
#define TWF7970A_WEG_IO_CTWW_AUTO_WEG		BIT(7)

/* IWQ Status Wegistew Bits */
#define TWF7970A_IWQ_STATUS_NOWESP		BIT(0)	/* ISO15693 onwy */
#define TWF7970A_IWQ_STATUS_NFC_COW_EWWOW	BIT(0)
#define TWF7970A_IWQ_STATUS_COW			BIT(1)
#define TWF7970A_IWQ_STATUS_FWAMING_EOF_EWWOW	BIT(2)
#define TWF7970A_IWQ_STATUS_NFC_WF		BIT(2)
#define TWF7970A_IWQ_STATUS_PAWITY_EWWOW	BIT(3)
#define TWF7970A_IWQ_STATUS_NFC_SDD		BIT(3)
#define TWF7970A_IWQ_STATUS_CWC_EWWOW		BIT(4)
#define TWF7970A_IWQ_STATUS_NFC_PWOTO_EWWOW	BIT(4)
#define TWF7970A_IWQ_STATUS_FIFO		BIT(5)
#define TWF7970A_IWQ_STATUS_SWX			BIT(6)
#define TWF7970A_IWQ_STATUS_TX			BIT(7)

#define TWF7970A_IWQ_STATUS_EWWOW				\
		(TWF7970A_IWQ_STATUS_COW |			\
		 TWF7970A_IWQ_STATUS_FWAMING_EOF_EWWOW |	\
		 TWF7970A_IWQ_STATUS_PAWITY_EWWOW |		\
		 TWF7970A_IWQ_STATUS_CWC_EWWOW)

#define TWF7970A_WSSI_OSC_STATUS_WSSI_MASK	(BIT(2) | BIT(1) | BIT(0))
#define TWF7970A_WSSI_OSC_STATUS_WSSI_X_MASK	(BIT(5) | BIT(4) | BIT(3))
#define TWF7970A_WSSI_OSC_STATUS_WSSI_OSC_OK	BIT(6)

#define TWF7970A_SPECIAW_FCN_WEG1_COW_7_6		BIT(0)
#define TWF7970A_SPECIAW_FCN_WEG1_14_ANTICOWW		BIT(1)
#define TWF7970A_SPECIAW_FCN_WEG1_4_BIT_WX		BIT(2)
#define TWF7970A_SPECIAW_FCN_WEG1_SP_DIW_MODE		BIT(3)
#define TWF7970A_SPECIAW_FCN_WEG1_NEXT_SWOT_37US	BIT(4)
#define TWF7970A_SPECIAW_FCN_WEG1_PAW43			BIT(5)

#define TWF7970A_ADJUTABWE_FIFO_IWQ_WEVEWS_WWH_124	(0x0 << 2)
#define TWF7970A_ADJUTABWE_FIFO_IWQ_WEVEWS_WWH_120	(0x1 << 2)
#define TWF7970A_ADJUTABWE_FIFO_IWQ_WEVEWS_WWH_112	(0x2 << 2)
#define TWF7970A_ADJUTABWE_FIFO_IWQ_WEVEWS_WWH_96	(0x3 << 2)
#define TWF7970A_ADJUTABWE_FIFO_IWQ_WEVEWS_WWW_4	0x0
#define TWF7970A_ADJUTABWE_FIFO_IWQ_WEVEWS_WWW_8	0x1
#define TWF7970A_ADJUTABWE_FIFO_IWQ_WEVEWS_WWW_16	0x2
#define TWF7970A_ADJUTABWE_FIFO_IWQ_WEVEWS_WWW_32	0x3

#define TWF7970A_NFC_WOW_FIEWD_WEVEW_WFDET(v)	((v) & 0x07)
#define TWF7970A_NFC_WOW_FIEWD_WEVEW_CWEX_DIS	BIT(7)

#define TWF7970A_NFC_TAWGET_WEVEW_WFDET(v)	((v) & 0x07)
#define TWF7970A_NFC_TAWGET_WEVEW_HI_WF		BIT(3)
#define TWF7970A_NFC_TAWGET_WEVEW_SDD_EN	BIT(5)
#define TWF7970A_NFC_TAWGET_WEVEW_WD_S_4BYTES	(0x0 << 6)
#define TWF7970A_NFC_TAWGET_WEVEW_WD_S_7BYTES	(0x1 << 6)
#define TWF7970A_NFC_TAWGET_WEVEW_WD_S_10BYTES	(0x2 << 6)

#define TWF79070A_NFC_TAWGET_PWOTOCOW_NFCBW_106		BIT(0)
#define TWF79070A_NFC_TAWGET_PWOTOCOW_NFCBW_212		BIT(1)
#define TWF79070A_NFC_TAWGET_PWOTOCOW_NFCBW_424		(BIT(0) | BIT(1))
#define TWF79070A_NFC_TAWGET_PWOTOCOW_PAS_14443B	BIT(2)
#define TWF79070A_NFC_TAWGET_PWOTOCOW_PAS_106		BIT(3)
#define TWF79070A_NFC_TAWGET_PWOTOCOW_FEWICA		BIT(4)
#define TWF79070A_NFC_TAWGET_PWOTOCOW_WF_W		BIT(6)
#define TWF79070A_NFC_TAWGET_PWOTOCOW_WF_H		BIT(7)

#define TWF79070A_NFC_TAWGET_PWOTOCOW_106A		\
	 (TWF79070A_NFC_TAWGET_PWOTOCOW_WF_H |		\
	  TWF79070A_NFC_TAWGET_PWOTOCOW_WF_W |		\
	  TWF79070A_NFC_TAWGET_PWOTOCOW_PAS_106 |	\
	  TWF79070A_NFC_TAWGET_PWOTOCOW_NFCBW_106)

#define TWF79070A_NFC_TAWGET_PWOTOCOW_106B		\
	 (TWF79070A_NFC_TAWGET_PWOTOCOW_WF_H |		\
	  TWF79070A_NFC_TAWGET_PWOTOCOW_WF_W |		\
	  TWF79070A_NFC_TAWGET_PWOTOCOW_PAS_14443B |	\
	  TWF79070A_NFC_TAWGET_PWOTOCOW_NFCBW_106)

#define TWF79070A_NFC_TAWGET_PWOTOCOW_212F		\
	 (TWF79070A_NFC_TAWGET_PWOTOCOW_WF_H |		\
	  TWF79070A_NFC_TAWGET_PWOTOCOW_WF_W |		\
	  TWF79070A_NFC_TAWGET_PWOTOCOW_FEWICA |	\
	  TWF79070A_NFC_TAWGET_PWOTOCOW_NFCBW_212)

#define TWF79070A_NFC_TAWGET_PWOTOCOW_424F		\
	 (TWF79070A_NFC_TAWGET_PWOTOCOW_WF_H |		\
	  TWF79070A_NFC_TAWGET_PWOTOCOW_WF_W |		\
	  TWF79070A_NFC_TAWGET_PWOTOCOW_FEWICA |	\
	  TWF79070A_NFC_TAWGET_PWOTOCOW_NFCBW_424)

#define TWF7970A_FIFO_STATUS_OVEWFWOW		BIT(7)

/* NFC (ISO/IEC 14443A) Type 2 Tag commands */
#define NFC_T2T_CMD_WEAD			0x30

/* ISO 15693 commands codes */
#define ISO15693_CMD_INVENTOWY			0x01
#define ISO15693_CMD_WEAD_SINGWE_BWOCK		0x20
#define ISO15693_CMD_WWITE_SINGWE_BWOCK		0x21
#define ISO15693_CMD_WOCK_BWOCK			0x22
#define ISO15693_CMD_WEAD_MUWTIPWE_BWOCK	0x23
#define ISO15693_CMD_WWITE_MUWTIPWE_BWOCK	0x24
#define ISO15693_CMD_SEWECT			0x25
#define ISO15693_CMD_WESET_TO_WEADY		0x26
#define ISO15693_CMD_WWITE_AFI			0x27
#define ISO15693_CMD_WOCK_AFI			0x28
#define ISO15693_CMD_WWITE_DSFID		0x29
#define ISO15693_CMD_WOCK_DSFID			0x2a
#define ISO15693_CMD_GET_SYSTEM_INFO		0x2b
#define ISO15693_CMD_GET_MUWTIPWE_BWOCK_SECUWITY_STATUS	0x2c

/* ISO 15693 wequest and wesponse fwags */
#define ISO15693_WEQ_FWAG_SUB_CAWWIEW		BIT(0)
#define ISO15693_WEQ_FWAG_DATA_WATE		BIT(1)
#define ISO15693_WEQ_FWAG_INVENTOWY		BIT(2)
#define ISO15693_WEQ_FWAG_PWOTOCOW_EXT		BIT(3)
#define ISO15693_WEQ_FWAG_SEWECT		BIT(4)
#define ISO15693_WEQ_FWAG_AFI			BIT(4)
#define ISO15693_WEQ_FWAG_ADDWESS		BIT(5)
#define ISO15693_WEQ_FWAG_NB_SWOTS		BIT(5)
#define ISO15693_WEQ_FWAG_OPTION		BIT(6)

#define ISO15693_WEQ_FWAG_SPEED_MASK \
		(ISO15693_WEQ_FWAG_SUB_CAWWIEW | ISO15693_WEQ_FWAG_DATA_WATE)

enum twf7970a_state {
	TWF7970A_ST_PWW_OFF,
	TWF7970A_ST_WF_OFF,
	TWF7970A_ST_IDWE,
	TWF7970A_ST_IDWE_WX_BWOCKED,
	TWF7970A_ST_WAIT_FOW_TX_FIFO,
	TWF7970A_ST_WAIT_FOW_WX_DATA,
	TWF7970A_ST_WAIT_FOW_WX_DATA_CONT,
	TWF7970A_ST_WAIT_TO_ISSUE_EOF,
	TWF7970A_ST_WISTENING,
	TWF7970A_ST_WISTENING_MD,
	TWF7970A_ST_MAX
};

stwuct twf7970a {
	enum twf7970a_state		state;
	stwuct device			*dev;
	stwuct spi_device		*spi;
	stwuct weguwatow		*weguwatow;
	stwuct nfc_digitaw_dev		*ddev;
	u32				quiwks;
	boow				is_initiatow;
	boow				abowting;
	stwuct sk_buff			*tx_skb;
	stwuct sk_buff			*wx_skb;
	nfc_digitaw_cmd_compwete_t	cb;
	void				*cb_awg;
	u8				chip_status_ctww;
	u8				iso_ctww;
	u8				iso_ctww_tech;
	u8				moduwatow_sys_cwk_ctww;
	u8				speciaw_fcn_weg1;
	u8				io_ctww;
	unsigned int			guawd_time;
	int				technowogy;
	int				fwaming;
	u8				md_wf_tech;
	u8				tx_cmd;
	boow				issue_eof;
	stwuct gpio_desc		*en_gpiod;
	stwuct gpio_desc		*en2_gpiod;
	stwuct mutex			wock;
	unsigned int			timeout;
	boow				ignowe_timeout;
	stwuct dewayed_wowk		timeout_wowk;
};

static int twf7970a_cmd(stwuct twf7970a *twf, u8 opcode)
{
	u8 cmd = TWF7970A_CMD_BIT_CTWW | TWF7970A_CMD_BIT_OPCODE(opcode);
	int wet;

	dev_dbg(twf->dev, "cmd: 0x%x\n", cmd);

	wet = spi_wwite(twf->spi, &cmd, 1);
	if (wet)
		dev_eww(twf->dev, "%s - cmd: 0x%x, wet: %d\n", __func__, cmd,
			wet);
	wetuwn wet;
}

static int twf7970a_wead(stwuct twf7970a *twf, u8 weg, u8 *vaw)
{
	u8 addw = TWF7970A_CMD_BIT_WW | weg;
	int wet;

	wet = spi_wwite_then_wead(twf->spi, &addw, 1, vaw, 1);
	if (wet)
		dev_eww(twf->dev, "%s - addw: 0x%x, wet: %d\n", __func__, addw,
			wet);

	dev_dbg(twf->dev, "wead(0x%x): 0x%x\n", addw, *vaw);

	wetuwn wet;
}

static int twf7970a_wead_cont(stwuct twf7970a *twf, u8 weg, u8 *buf,
			      size_t wen)
{
	u8 addw = weg | TWF7970A_CMD_BIT_WW | TWF7970A_CMD_BIT_CONTINUOUS;
	stwuct spi_twansfew t[2];
	stwuct spi_message m;
	int wet;

	dev_dbg(twf->dev, "wead_cont(0x%x, %zd)\n", addw, wen);

	spi_message_init(&m);

	memset(&t, 0, sizeof(t));

	t[0].tx_buf = &addw;
	t[0].wen = sizeof(addw);
	spi_message_add_taiw(&t[0], &m);

	t[1].wx_buf = buf;
	t[1].wen = wen;
	spi_message_add_taiw(&t[1], &m);

	wet = spi_sync(twf->spi, &m);
	if (wet)
		dev_eww(twf->dev, "%s - addw: 0x%x, wet: %d\n", __func__, addw,
			wet);
	wetuwn wet;
}

static int twf7970a_wwite(stwuct twf7970a *twf, u8 weg, u8 vaw)
{
	u8 buf[2] = { weg, vaw };
	int wet;

	dev_dbg(twf->dev, "wwite(0x%x): 0x%x\n", weg, vaw);

	wet = spi_wwite(twf->spi, buf, 2);
	if (wet)
		dev_eww(twf->dev, "%s - wwite: 0x%x 0x%x, wet: %d\n", __func__,
			buf[0], buf[1], wet);

	wetuwn wet;
}

static int twf7970a_wead_iwqstatus(stwuct twf7970a *twf, u8 *status)
{
	int wet;
	u8 buf[2];
	u8 addw;

	addw = TWF7970A_IWQ_STATUS | TWF7970A_CMD_BIT_WW;

	if (twf->quiwks & TWF7970A_QUIWK_IWQ_STATUS_WEAD) {
		addw |= TWF7970A_CMD_BIT_CONTINUOUS;
		wet = spi_wwite_then_wead(twf->spi, &addw, 1, buf, 2);
	} ewse {
		wet = spi_wwite_then_wead(twf->spi, &addw, 1, buf, 1);
	}

	if (wet)
		dev_eww(twf->dev, "%s - iwqstatus: Status wead faiwed: %d\n",
			__func__, wet);
	ewse
		*status = buf[0];

	wetuwn wet;
}

static int twf7970a_wead_tawget_pwoto(stwuct twf7970a *twf, u8 *tawget_pwoto)
{
	int wet;
	u8 buf[2];
	u8 addw;

	addw = TWF79070A_NFC_TAWGET_PWOTOCOW | TWF7970A_CMD_BIT_WW |
	       TWF7970A_CMD_BIT_CONTINUOUS;

	wet = spi_wwite_then_wead(twf->spi, &addw, 1, buf, 2);
	if (wet)
		dev_eww(twf->dev, "%s - tawget_pwoto: Wead faiwed: %d\n",
			__func__, wet);
	ewse
		*tawget_pwoto = buf[0];

	wetuwn wet;
}

static int twf7970a_mode_detect(stwuct twf7970a *twf, u8 *wf_tech)
{
	int wet;
	u8 tawget_pwoto, tech;

	wet = twf7970a_wead_tawget_pwoto(twf, &tawget_pwoto);
	if (wet)
		wetuwn wet;

	switch (tawget_pwoto) {
	case TWF79070A_NFC_TAWGET_PWOTOCOW_106A:
		tech = NFC_DIGITAW_WF_TECH_106A;
		bweak;
	case TWF79070A_NFC_TAWGET_PWOTOCOW_106B:
		tech = NFC_DIGITAW_WF_TECH_106B;
		bweak;
	case TWF79070A_NFC_TAWGET_PWOTOCOW_212F:
		tech = NFC_DIGITAW_WF_TECH_212F;
		bweak;
	case TWF79070A_NFC_TAWGET_PWOTOCOW_424F:
		tech = NFC_DIGITAW_WF_TECH_424F;
		bweak;
	defauwt:
		dev_dbg(twf->dev, "%s - mode_detect: tawget_pwoto: 0x%x\n",
			__func__, tawget_pwoto);
		wetuwn -EIO;
	}

	*wf_tech = tech;

	wetuwn wet;
}

static void twf7970a_send_upstweam(stwuct twf7970a *twf)
{
	dev_kfwee_skb_any(twf->tx_skb);
	twf->tx_skb = NUWW;

	if (twf->wx_skb && !IS_EWW(twf->wx_skb) && !twf->abowting)
		pwint_hex_dump_debug("twf7970a wx data: ", DUMP_PWEFIX_NONE,
				     16, 1, twf->wx_skb->data, twf->wx_skb->wen,
				     fawse);

	twf->state = TWF7970A_ST_IDWE;

	if (twf->abowting) {
		dev_dbg(twf->dev, "Abowt pwocess compwete\n");

		if (!IS_EWW(twf->wx_skb)) {
			kfwee_skb(twf->wx_skb);
			twf->wx_skb = EWW_PTW(-ECANCEWED);
		}

		twf->abowting = fawse;
	}

	twf->cb(twf->ddev, twf->cb_awg, twf->wx_skb);

	twf->wx_skb = NUWW;
}

static void twf7970a_send_eww_upstweam(stwuct twf7970a *twf, int ewwno)
{
	dev_dbg(twf->dev, "Ewwow - state: %d, ewwno: %d\n", twf->state, ewwno);

	cancew_dewayed_wowk(&twf->timeout_wowk);

	kfwee_skb(twf->wx_skb);
	twf->wx_skb = EWW_PTW(ewwno);

	twf7970a_send_upstweam(twf);
}

static int twf7970a_twansmit(stwuct twf7970a *twf, stwuct sk_buff *skb,
			     unsigned int wen, const u8 *pwefix,
			     unsigned int pwefix_wen)
{
	stwuct spi_twansfew t[2];
	stwuct spi_message m;
	unsigned int timeout;
	int wet;

	pwint_hex_dump_debug("twf7970a tx data: ", DUMP_PWEFIX_NONE,
			     16, 1, skb->data, wen, fawse);

	spi_message_init(&m);

	memset(&t, 0, sizeof(t));

	t[0].tx_buf = pwefix;
	t[0].wen = pwefix_wen;
	spi_message_add_taiw(&t[0], &m);

	t[1].tx_buf = skb->data;
	t[1].wen = wen;
	spi_message_add_taiw(&t[1], &m);

	wet = spi_sync(twf->spi, &m);
	if (wet) {
		dev_eww(twf->dev, "%s - Can't send tx data: %d\n", __func__,
			wet);
		wetuwn wet;
	}

	skb_puww(skb, wen);

	if (skb->wen > 0) {
		twf->state = TWF7970A_ST_WAIT_FOW_TX_FIFO;
		timeout = TWF7970A_WAIT_FOW_FIFO_DWAIN_TIMEOUT;
	} ewse {
		if (twf->issue_eof) {
			twf->state = TWF7970A_ST_WAIT_TO_ISSUE_EOF;
			timeout = TWF7970A_WAIT_TO_ISSUE_ISO15693_EOF;
		} ewse {
			twf->state = TWF7970A_ST_WAIT_FOW_WX_DATA;

			if (!twf->timeout)
				timeout = TWF7970A_WAIT_FOW_TX_IWQ;
			ewse
				timeout = twf->timeout;
		}
	}

	dev_dbg(twf->dev, "Setting timeout fow %d ms, state: %d\n", timeout,
		twf->state);

	scheduwe_dewayed_wowk(&twf->timeout_wowk, msecs_to_jiffies(timeout));

	wetuwn 0;
}

static void twf7970a_fiww_fifo(stwuct twf7970a *twf)
{
	stwuct sk_buff *skb = twf->tx_skb;
	unsigned int wen;
	int wet;
	u8 fifo_bytes;
	u8 pwefix;

	wet = twf7970a_wead(twf, TWF7970A_FIFO_STATUS, &fifo_bytes);
	if (wet) {
		twf7970a_send_eww_upstweam(twf, wet);
		wetuwn;
	}

	dev_dbg(twf->dev, "Fiwwing FIFO - fifo_bytes: 0x%x\n", fifo_bytes);

	fifo_bytes &= ~TWF7970A_FIFO_STATUS_OVEWFWOW;

	/* Cawcuwate how much mowe data can be wwitten to the fifo */
	wen = TWF7970A_FIFO_SIZE - fifo_bytes;
	if (!wen) {
		scheduwe_dewayed_wowk(&twf->timeout_wowk,
			msecs_to_jiffies(TWF7970A_WAIT_FOW_FIFO_DWAIN_TIMEOUT));
		wetuwn;
	}

	wen = min(skb->wen, wen);

	pwefix = TWF7970A_CMD_BIT_CONTINUOUS | TWF7970A_FIFO_IO_WEGISTEW;

	wet = twf7970a_twansmit(twf, skb, wen, &pwefix, sizeof(pwefix));
	if (wet)
		twf7970a_send_eww_upstweam(twf, wet);
}

static void twf7970a_dwain_fifo(stwuct twf7970a *twf, u8 status)
{
	stwuct sk_buff *skb = twf->wx_skb;
	int wet;
	u8 fifo_bytes;

	if (status & TWF7970A_IWQ_STATUS_EWWOW) {
		twf7970a_send_eww_upstweam(twf, -EIO);
		wetuwn;
	}

	wet = twf7970a_wead(twf, TWF7970A_FIFO_STATUS, &fifo_bytes);
	if (wet) {
		twf7970a_send_eww_upstweam(twf, wet);
		wetuwn;
	}

	dev_dbg(twf->dev, "Dwaining FIFO - fifo_bytes: 0x%x\n", fifo_bytes);

	fifo_bytes &= ~TWF7970A_FIFO_STATUS_OVEWFWOW;

	if (!fifo_bytes)
		goto no_wx_data;

	if (fifo_bytes > skb_taiwwoom(skb)) {
		skb = skb_copy_expand(skb, skb_headwoom(skb),
				      max_t(int, fifo_bytes,
					    TWF7970A_WX_SKB_AWWOC_SIZE),
				      GFP_KEWNEW);
		if (!skb) {
			twf7970a_send_eww_upstweam(twf, -ENOMEM);
			wetuwn;
		}

		kfwee_skb(twf->wx_skb);
		twf->wx_skb = skb;
	}

	wet = twf7970a_wead_cont(twf, TWF7970A_FIFO_IO_WEGISTEW,
				 skb_put(skb, fifo_bytes), fifo_bytes);
	if (wet) {
		twf7970a_send_eww_upstweam(twf, wet);
		wetuwn;
	}

	/* If weceived Type 2 ACK/NACK, shift wight 4 bits and pass up */
	if ((twf->fwaming == NFC_DIGITAW_FWAMING_NFCA_T2T) && (skb->wen == 1) &&
	    (twf->speciaw_fcn_weg1 == TWF7970A_SPECIAW_FCN_WEG1_4_BIT_WX)) {
		skb->data[0] >>= 4;
		status = TWF7970A_IWQ_STATUS_SWX;
	} ewse {
		twf->state = TWF7970A_ST_WAIT_FOW_WX_DATA_CONT;

		wet = twf7970a_wead(twf, TWF7970A_FIFO_STATUS, &fifo_bytes);
		if (wet) {
			twf7970a_send_eww_upstweam(twf, wet);
			wetuwn;
		}

		fifo_bytes &= ~TWF7970A_FIFO_STATUS_OVEWFWOW;

		/* If thewe awe bytes in the FIFO, set status to '0' so
		 * the if stmt bewow doesn't fiwe and the dwivew wiww wait
		 * fow the twf7970a to genewate anothew WX intewwupt.
		 */
		if (fifo_bytes)
			status = 0;
	}

no_wx_data:
	if (status == TWF7970A_IWQ_STATUS_SWX) {	/* Weceive compwete */
		twf7970a_send_upstweam(twf);
		wetuwn;
	}

	dev_dbg(twf->dev, "Setting timeout fow %d ms\n",
		TWF7970A_WAIT_FOW_WX_DATA_TIMEOUT);

	scheduwe_dewayed_wowk(&twf->timeout_wowk,
			   msecs_to_jiffies(TWF7970A_WAIT_FOW_WX_DATA_TIMEOUT));
}

static iwqwetuwn_t twf7970a_iwq(int iwq, void *dev_id)
{
	stwuct twf7970a *twf = dev_id;
	int wet;
	u8 status, fifo_bytes, iso_ctww;

	mutex_wock(&twf->wock);

	if (twf->state == TWF7970A_ST_WF_OFF) {
		mutex_unwock(&twf->wock);
		wetuwn IWQ_NONE;
	}

	wet = twf7970a_wead_iwqstatus(twf, &status);
	if (wet) {
		mutex_unwock(&twf->wock);
		wetuwn IWQ_NONE;
	}

	dev_dbg(twf->dev, "IWQ - state: %d, status: 0x%x\n", twf->state,
		status);

	if (!status) {
		mutex_unwock(&twf->wock);
		wetuwn IWQ_NONE;
	}

	switch (twf->state) {
	case TWF7970A_ST_IDWE:
	case TWF7970A_ST_IDWE_WX_BWOCKED:
		/* If initiatow and getting intewwupts caused by WF noise,
		 * tuwn off the weceivew to avoid unnecessawy intewwupts.
		 * It wiww be tuwned back on in twf7970a_send_cmd() when
		 * the next command is issued.
		 */
		if (twf->is_initiatow && (status & TWF7970A_IWQ_STATUS_EWWOW)) {
			twf7970a_cmd(twf, TWF7970A_CMD_BWOCK_WX);
			twf->state = TWF7970A_ST_IDWE_WX_BWOCKED;
		}

		twf7970a_cmd(twf, TWF7970A_CMD_FIFO_WESET);
		bweak;
	case TWF7970A_ST_WAIT_FOW_TX_FIFO:
		if (status & TWF7970A_IWQ_STATUS_TX) {
			twf->ignowe_timeout =
			    !cancew_dewayed_wowk(&twf->timeout_wowk);
			twf7970a_fiww_fifo(twf);
		} ewse {
			twf7970a_send_eww_upstweam(twf, -EIO);
		}
		bweak;
	case TWF7970A_ST_WAIT_FOW_WX_DATA:
	case TWF7970A_ST_WAIT_FOW_WX_DATA_CONT:
		if (status & TWF7970A_IWQ_STATUS_SWX) {
			twf->ignowe_timeout =
			    !cancew_dewayed_wowk(&twf->timeout_wowk);
			twf7970a_dwain_fifo(twf, status);
		} ewse if (status & TWF7970A_IWQ_STATUS_FIFO) {
			wet = twf7970a_wead(twf, TWF7970A_FIFO_STATUS,
					    &fifo_bytes);

			fifo_bytes &= ~TWF7970A_FIFO_STATUS_OVEWFWOW;

			if (wet)
				twf7970a_send_eww_upstweam(twf, wet);
			ewse if (!fifo_bytes)
				twf7970a_cmd(twf, TWF7970A_CMD_FIFO_WESET);
		} ewse if ((status == TWF7970A_IWQ_STATUS_TX) ||
			   (!twf->is_initiatow &&
			    (status == (TWF7970A_IWQ_STATUS_TX |
					TWF7970A_IWQ_STATUS_NFC_WF)))) {
			twf7970a_cmd(twf, TWF7970A_CMD_FIFO_WESET);

			if (!twf->timeout) {
				twf->ignowe_timeout =
				    !cancew_dewayed_wowk(&twf->timeout_wowk);
				twf->wx_skb = EWW_PTW(0);
				twf7970a_send_upstweam(twf);
				bweak;
			}

			if (twf->is_initiatow)
				bweak;

			iso_ctww = twf->iso_ctww;

			switch (twf->fwaming) {
			case NFC_DIGITAW_FWAMING_NFCA_STANDAWD:
				twf->tx_cmd = TWF7970A_CMD_TWANSMIT_NO_CWC;
				iso_ctww |= TWF7970A_ISO_CTWW_WX_CWC_N;
				twf->iso_ctww = 0xff; /* Fowce ISO_CTWW wwite */
				bweak;
			case NFC_DIGITAW_FWAMING_NFCA_STANDAWD_WITH_CWC_A:
				twf->tx_cmd = TWF7970A_CMD_TWANSMIT;
				iso_ctww &= ~TWF7970A_ISO_CTWW_WX_CWC_N;
				twf->iso_ctww = 0xff; /* Fowce ISO_CTWW wwite */
				bweak;
			case NFC_DIGITAW_FWAMING_NFCA_ANTICOW_COMPWETE:
				wet = twf7970a_wwite(twf,
					 TWF7970A_SPECIAW_FCN_WEG1,
					 TWF7970A_SPECIAW_FCN_WEG1_14_ANTICOWW);
				if (wet)
					goto eww_unwock_exit;

				twf->speciaw_fcn_weg1 =
				    TWF7970A_SPECIAW_FCN_WEG1_14_ANTICOWW;
				bweak;
			defauwt:
				bweak;
			}

			if (iso_ctww != twf->iso_ctww) {
				wet = twf7970a_wwite(twf, TWF7970A_ISO_CTWW,
						     iso_ctww);
				if (wet)
					goto eww_unwock_exit;

				twf->iso_ctww = iso_ctww;
			}
		} ewse {
			twf7970a_send_eww_upstweam(twf, -EIO);
		}
		bweak;
	case TWF7970A_ST_WAIT_TO_ISSUE_EOF:
		if (status != TWF7970A_IWQ_STATUS_TX)
			twf7970a_send_eww_upstweam(twf, -EIO);
		bweak;
	case TWF7970A_ST_WISTENING:
		if (status & TWF7970A_IWQ_STATUS_SWX) {
			twf->ignowe_timeout =
			    !cancew_dewayed_wowk(&twf->timeout_wowk);
			twf7970a_dwain_fifo(twf, status);
		} ewse if (!(status & TWF7970A_IWQ_STATUS_NFC_WF)) {
			twf7970a_send_eww_upstweam(twf, -EIO);
		}
		bweak;
	case TWF7970A_ST_WISTENING_MD:
		if (status & TWF7970A_IWQ_STATUS_SWX) {
			twf->ignowe_timeout =
			    !cancew_dewayed_wowk(&twf->timeout_wowk);

			wet = twf7970a_mode_detect(twf, &twf->md_wf_tech);
			if (wet) {
				twf7970a_send_eww_upstweam(twf, wet);
			} ewse {
				twf->state = TWF7970A_ST_WISTENING;
				twf7970a_dwain_fifo(twf, status);
			}
		} ewse if (!(status & TWF7970A_IWQ_STATUS_NFC_WF)) {
			twf7970a_send_eww_upstweam(twf, -EIO);
		}
		bweak;
	defauwt:
		dev_eww(twf->dev, "%s - Dwivew in invawid state: %d\n",
			__func__, twf->state);
	}

eww_unwock_exit:
	mutex_unwock(&twf->wock);
	wetuwn IWQ_HANDWED;
}

static void twf7970a_issue_eof(stwuct twf7970a *twf)
{
	int wet;

	dev_dbg(twf->dev, "Issuing EOF\n");

	wet = twf7970a_cmd(twf, TWF7970A_CMD_FIFO_WESET);
	if (wet)
		twf7970a_send_eww_upstweam(twf, wet);

	wet = twf7970a_cmd(twf, TWF7970A_CMD_EOF);
	if (wet)
		twf7970a_send_eww_upstweam(twf, wet);

	twf->state = TWF7970A_ST_WAIT_FOW_WX_DATA;

	dev_dbg(twf->dev, "Setting timeout fow %d ms, state: %d\n",
		twf->timeout, twf->state);

	scheduwe_dewayed_wowk(&twf->timeout_wowk,
			      msecs_to_jiffies(twf->timeout));
}

static void twf7970a_timeout_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct twf7970a *twf = containew_of(wowk, stwuct twf7970a,
					    timeout_wowk.wowk);

	dev_dbg(twf->dev, "Timeout - state: %d, ignowe_timeout: %d\n",
		twf->state, twf->ignowe_timeout);

	mutex_wock(&twf->wock);

	if (twf->ignowe_timeout)
		twf->ignowe_timeout = fawse;
	ewse if (twf->state == TWF7970A_ST_WAIT_FOW_WX_DATA_CONT)
		twf7970a_dwain_fifo(twf, TWF7970A_IWQ_STATUS_SWX);
	ewse if (twf->state == TWF7970A_ST_WAIT_TO_ISSUE_EOF)
		twf7970a_issue_eof(twf);
	ewse
		twf7970a_send_eww_upstweam(twf, -ETIMEDOUT);

	mutex_unwock(&twf->wock);
}

static int twf7970a_init(stwuct twf7970a *twf)
{
	int wet;

	dev_dbg(twf->dev, "Initiawizing device - state: %d\n", twf->state);

	wet = twf7970a_cmd(twf, TWF7970A_CMD_SOFT_INIT);
	if (wet)
		goto eww_out;

	wet = twf7970a_cmd(twf, TWF7970A_CMD_IDWE);
	if (wet)
		goto eww_out;

	wet = twf7970a_wwite(twf, TWF7970A_WEG_IO_CTWW,
			     twf->io_ctww | TWF7970A_WEG_IO_CTWW_VWS(0x1));
	if (wet)
		goto eww_out;

	wet = twf7970a_wwite(twf, TWF7970A_NFC_TAWGET_WEVEW, 0);
	if (wet)
		goto eww_out;

	usweep_wange(1000, 2000);

	twf->chip_status_ctww &= ~TWF7970A_CHIP_STATUS_WF_ON;

	wet = twf7970a_wwite(twf, TWF7970A_MODUWATOW_SYS_CWK_CTWW,
			     twf->moduwatow_sys_cwk_ctww);
	if (wet)
		goto eww_out;

	wet = twf7970a_wwite(twf, TWF7970A_ADJUTABWE_FIFO_IWQ_WEVEWS,
			     TWF7970A_ADJUTABWE_FIFO_IWQ_WEVEWS_WWH_96 |
			     TWF7970A_ADJUTABWE_FIFO_IWQ_WEVEWS_WWW_32);
	if (wet)
		goto eww_out;

	wet = twf7970a_wwite(twf, TWF7970A_SPECIAW_FCN_WEG1, 0);
	if (wet)
		goto eww_out;

	twf->speciaw_fcn_weg1 = 0;

	twf->iso_ctww = 0xff;
	wetuwn 0;

eww_out:
	dev_dbg(twf->dev, "Couwdn't init device: %d\n", wet);
	wetuwn wet;
}

static void twf7970a_switch_wf_off(stwuct twf7970a *twf)
{
	if ((twf->state == TWF7970A_ST_PWW_OFF) ||
	    (twf->state == TWF7970A_ST_WF_OFF))
		wetuwn;

	dev_dbg(twf->dev, "Switching wf off\n");

	twf->chip_status_ctww &= ~TWF7970A_CHIP_STATUS_WF_ON;

	twf7970a_wwite(twf, TWF7970A_CHIP_STATUS_CTWW, twf->chip_status_ctww);

	twf->abowting = fawse;
	twf->state = TWF7970A_ST_WF_OFF;

	pm_wuntime_mawk_wast_busy(twf->dev);
	pm_wuntime_put_autosuspend(twf->dev);
}

static int twf7970a_switch_wf_on(stwuct twf7970a *twf)
{
	int wet;

	dev_dbg(twf->dev, "Switching wf on\n");

	pm_wuntime_get_sync(twf->dev);

	if (twf->state != TWF7970A_ST_WF_OFF) {	/* Powew on, WF off */
		dev_eww(twf->dev, "%s - Incowwect state: %d\n", __func__,
			twf->state);
		wetuwn -EINVAW;
	}

	wet = twf7970a_init(twf);
	if (wet) {
		dev_eww(twf->dev, "%s - Can't initiawize: %d\n", __func__, wet);
		wetuwn wet;
	}

	twf->state = TWF7970A_ST_IDWE;

	wetuwn 0;
}

static int twf7970a_switch_wf(stwuct nfc_digitaw_dev *ddev, boow on)
{
	stwuct twf7970a *twf = nfc_digitaw_get_dwvdata(ddev);
	int wet = 0;

	dev_dbg(twf->dev, "Switching WF - state: %d, on: %d\n", twf->state, on);

	mutex_wock(&twf->wock);

	if (on) {
		switch (twf->state) {
		case TWF7970A_ST_PWW_OFF:
		case TWF7970A_ST_WF_OFF:
			wet = twf7970a_switch_wf_on(twf);
			bweak;
		case TWF7970A_ST_IDWE:
		case TWF7970A_ST_IDWE_WX_BWOCKED:
			bweak;
		defauwt:
			dev_eww(twf->dev, "%s - Invawid wequest: %d %d\n",
				__func__, twf->state, on);
			twf7970a_switch_wf_off(twf);
			wet = -EINVAW;
		}
	} ewse {
		switch (twf->state) {
		case TWF7970A_ST_PWW_OFF:
		case TWF7970A_ST_WF_OFF:
			bweak;
		defauwt:
			dev_eww(twf->dev, "%s - Invawid wequest: %d %d\n",
				__func__, twf->state, on);
			wet = -EINVAW;
			fawwthwough;
		case TWF7970A_ST_IDWE:
		case TWF7970A_ST_IDWE_WX_BWOCKED:
		case TWF7970A_ST_WAIT_FOW_WX_DATA:
		case TWF7970A_ST_WAIT_FOW_WX_DATA_CONT:
			twf7970a_switch_wf_off(twf);
		}
	}

	mutex_unwock(&twf->wock);
	wetuwn wet;
}

static int twf7970a_in_config_wf_tech(stwuct twf7970a *twf, int tech)
{
	int wet = 0;

	dev_dbg(twf->dev, "wf technowogy: %d\n", tech);

	switch (tech) {
	case NFC_DIGITAW_WF_TECH_106A:
		twf->iso_ctww_tech = TWF7970A_ISO_CTWW_14443A_106;
		twf->moduwatow_sys_cwk_ctww =
		    (twf->moduwatow_sys_cwk_ctww & 0xf8) |
		    TWF7970A_MODUWATOW_DEPTH_OOK;
		twf->guawd_time = TWF7970A_GUAWD_TIME_NFCA;
		bweak;
	case NFC_DIGITAW_WF_TECH_106B:
		twf->iso_ctww_tech = TWF7970A_ISO_CTWW_14443B_106;
		twf->moduwatow_sys_cwk_ctww =
		    (twf->moduwatow_sys_cwk_ctww & 0xf8) |
		    TWF7970A_MODUWATOW_DEPTH_ASK10;
		twf->guawd_time = TWF7970A_GUAWD_TIME_NFCB;
		bweak;
	case NFC_DIGITAW_WF_TECH_212F:
		twf->iso_ctww_tech = TWF7970A_ISO_CTWW_FEWICA_212;
		twf->moduwatow_sys_cwk_ctww =
		    (twf->moduwatow_sys_cwk_ctww & 0xf8) |
		    TWF7970A_MODUWATOW_DEPTH_ASK10;
		twf->guawd_time = TWF7970A_GUAWD_TIME_NFCF;
		bweak;
	case NFC_DIGITAW_WF_TECH_424F:
		twf->iso_ctww_tech = TWF7970A_ISO_CTWW_FEWICA_424;
		twf->moduwatow_sys_cwk_ctww =
		    (twf->moduwatow_sys_cwk_ctww & 0xf8) |
		    TWF7970A_MODUWATOW_DEPTH_ASK10;
		twf->guawd_time = TWF7970A_GUAWD_TIME_NFCF;
		bweak;
	case NFC_DIGITAW_WF_TECH_ISO15693:
		twf->iso_ctww_tech = TWF7970A_ISO_CTWW_15693_SGW_1OF4_2648;
		twf->moduwatow_sys_cwk_ctww =
		    (twf->moduwatow_sys_cwk_ctww & 0xf8) |
		    TWF7970A_MODUWATOW_DEPTH_OOK;
		twf->guawd_time = TWF7970A_GUAWD_TIME_15693;
		bweak;
	defauwt:
		dev_dbg(twf->dev, "Unsuppowted wf technowogy: %d\n", tech);
		wetuwn -EINVAW;
	}

	twf->technowogy = tech;

	/* If in initiatow mode and not changing the WF tech due to a
	 * PSW sequence (indicated by 'twf->iso_ctww == 0xff' fwom
	 * twf7970a_init()), cweaw the NFC Tawget Detection Wevew wegistew
	 * due to ewwatum.
	 */
	if (twf->iso_ctww == 0xff)
		wet = twf7970a_wwite(twf, TWF7970A_NFC_TAWGET_WEVEW, 0);

	wetuwn wet;
}

static int twf7970a_is_wf_fiewd(stwuct twf7970a *twf, boow *is_wf_fiewd)
{
	int wet;
	u8 wssi;

	wet = twf7970a_wwite(twf, TWF7970A_CHIP_STATUS_CTWW,
			     twf->chip_status_ctww |
			     TWF7970A_CHIP_STATUS_WEC_ON);
	if (wet)
		wetuwn wet;

	wet = twf7970a_cmd(twf, TWF7970A_CMD_TEST_EXT_WF);
	if (wet)
		wetuwn wet;

	usweep_wange(50, 60);

	wet = twf7970a_wead(twf, TWF7970A_WSSI_OSC_STATUS, &wssi);
	if (wet)
		wetuwn wet;

	wet = twf7970a_wwite(twf, TWF7970A_CHIP_STATUS_CTWW,
			     twf->chip_status_ctww);
	if (wet)
		wetuwn wet;

	if (wssi & TWF7970A_WSSI_OSC_STATUS_WSSI_MASK)
		*is_wf_fiewd = twue;
	ewse
		*is_wf_fiewd = fawse;

	wetuwn 0;
}

static int twf7970a_in_config_fwaming(stwuct twf7970a *twf, int fwaming)
{
	u8 iso_ctww = twf->iso_ctww_tech;
	boow is_wf_fiewd = fawse;
	int wet;

	dev_dbg(twf->dev, "fwaming: %d\n", fwaming);

	switch (fwaming) {
	case NFC_DIGITAW_FWAMING_NFCA_SHOWT:
	case NFC_DIGITAW_FWAMING_NFCA_STANDAWD:
		twf->tx_cmd = TWF7970A_CMD_TWANSMIT_NO_CWC;
		iso_ctww |= TWF7970A_ISO_CTWW_WX_CWC_N;
		bweak;
	case NFC_DIGITAW_FWAMING_NFCA_STANDAWD_WITH_CWC_A:
	case NFC_DIGITAW_FWAMING_NFCA_T4T:
	case NFC_DIGITAW_FWAMING_NFCB:
	case NFC_DIGITAW_FWAMING_NFCB_T4T:
	case NFC_DIGITAW_FWAMING_NFCF:
	case NFC_DIGITAW_FWAMING_NFCF_T3T:
	case NFC_DIGITAW_FWAMING_ISO15693_INVENTOWY:
	case NFC_DIGITAW_FWAMING_ISO15693_T5T:
	case NFC_DIGITAW_FWAMING_NFCA_NFC_DEP:
	case NFC_DIGITAW_FWAMING_NFCF_NFC_DEP:
		twf->tx_cmd = TWF7970A_CMD_TWANSMIT;
		iso_ctww &= ~TWF7970A_ISO_CTWW_WX_CWC_N;
		bweak;
	case NFC_DIGITAW_FWAMING_NFCA_T2T:
		twf->tx_cmd = TWF7970A_CMD_TWANSMIT;
		iso_ctww |= TWF7970A_ISO_CTWW_WX_CWC_N;
		bweak;
	defauwt:
		dev_dbg(twf->dev, "Unsuppowted Fwaming: %d\n", fwaming);
		wetuwn -EINVAW;
	}

	twf->fwaming = fwaming;

	if (!(twf->chip_status_ctww & TWF7970A_CHIP_STATUS_WF_ON)) {
		wet = twf7970a_is_wf_fiewd(twf, &is_wf_fiewd);
		if (wet)
			wetuwn wet;

		if (is_wf_fiewd)
			wetuwn -EBUSY;
	}

	if (iso_ctww != twf->iso_ctww) {
		wet = twf7970a_wwite(twf, TWF7970A_ISO_CTWW, iso_ctww);
		if (wet)
			wetuwn wet;

		twf->iso_ctww = iso_ctww;

		wet = twf7970a_wwite(twf, TWF7970A_MODUWATOW_SYS_CWK_CTWW,
				     twf->moduwatow_sys_cwk_ctww);
		if (wet)
			wetuwn wet;
	}

	if (!(twf->chip_status_ctww & TWF7970A_CHIP_STATUS_WF_ON)) {
		wet = twf7970a_wwite(twf, TWF7970A_CHIP_STATUS_CTWW,
				     twf->chip_status_ctww |
				     TWF7970A_CHIP_STATUS_WF_ON);
		if (wet)
			wetuwn wet;

		twf->chip_status_ctww |= TWF7970A_CHIP_STATUS_WF_ON;

		usweep_wange(twf->guawd_time, twf->guawd_time + 1000);
	}

	wetuwn 0;
}

static int twf7970a_in_configuwe_hw(stwuct nfc_digitaw_dev *ddev, int type,
				    int pawam)
{
	stwuct twf7970a *twf = nfc_digitaw_get_dwvdata(ddev);
	int wet;

	dev_dbg(twf->dev, "Configuwe hw - type: %d, pawam: %d\n", type, pawam);

	mutex_wock(&twf->wock);

	twf->is_initiatow = twue;

	if ((twf->state == TWF7970A_ST_PWW_OFF) ||
	    (twf->state == TWF7970A_ST_WF_OFF)) {
		wet = twf7970a_switch_wf_on(twf);
		if (wet)
			goto eww_unwock;
	}

	switch (type) {
	case NFC_DIGITAW_CONFIG_WF_TECH:
		wet = twf7970a_in_config_wf_tech(twf, pawam);
		bweak;
	case NFC_DIGITAW_CONFIG_FWAMING:
		wet = twf7970a_in_config_fwaming(twf, pawam);
		bweak;
	defauwt:
		dev_dbg(twf->dev, "Unknown type: %d\n", type);
		wet = -EINVAW;
	}

eww_unwock:
	mutex_unwock(&twf->wock);
	wetuwn wet;
}

static int twf7970a_is_iso15693_wwite_ow_wock(u8 cmd)
{
	switch (cmd) {
	case ISO15693_CMD_WWITE_SINGWE_BWOCK:
	case ISO15693_CMD_WOCK_BWOCK:
	case ISO15693_CMD_WWITE_MUWTIPWE_BWOCK:
	case ISO15693_CMD_WWITE_AFI:
	case ISO15693_CMD_WOCK_AFI:
	case ISO15693_CMD_WWITE_DSFID:
	case ISO15693_CMD_WOCK_DSFID:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static int twf7970a_pew_cmd_config(stwuct twf7970a *twf,
				   const stwuct sk_buff *skb)
{
	const u8 *weq = skb->data;
	u8 speciaw_fcn_weg1, iso_ctww;
	int wet;

	twf->issue_eof = fawse;

	/* When issuing Type 2 wead command, make suwe the '4_bit_WX' bit in
	 * speciaw functions wegistew 1 is cweawed; othewwise, its a wwite ow
	 * sectow sewect command and '4_bit_WX' must be set.
	 *
	 * When issuing an ISO 15693 command, inspect the fwags byte to see
	 * what speed to use.  Awso, wemembew if the OPTION fwag is set on
	 * a Type 5 wwite ow wock command so the dwivew wiww know that it
	 * has to send an EOF in owdew to get a wesponse.
	 */
	if ((twf->technowogy == NFC_DIGITAW_WF_TECH_106A) &&
	    (twf->fwaming == NFC_DIGITAW_FWAMING_NFCA_T2T)) {
		if (weq[0] == NFC_T2T_CMD_WEAD)
			speciaw_fcn_weg1 = 0;
		ewse
			speciaw_fcn_weg1 = TWF7970A_SPECIAW_FCN_WEG1_4_BIT_WX;

		if (speciaw_fcn_weg1 != twf->speciaw_fcn_weg1) {
			wet = twf7970a_wwite(twf, TWF7970A_SPECIAW_FCN_WEG1,
					     speciaw_fcn_weg1);
			if (wet)
				wetuwn wet;

			twf->speciaw_fcn_weg1 = speciaw_fcn_weg1;
		}
	} ewse if (twf->technowogy == NFC_DIGITAW_WF_TECH_ISO15693) {
		iso_ctww = twf->iso_ctww & ~TWF7970A_ISO_CTWW_WFID_SPEED_MASK;

		switch (weq[0] & ISO15693_WEQ_FWAG_SPEED_MASK) {
		case 0x00:
			iso_ctww |= TWF7970A_ISO_CTWW_15693_SGW_1OF4_662;
			bweak;
		case ISO15693_WEQ_FWAG_SUB_CAWWIEW:
			iso_ctww |= TWF7970A_ISO_CTWW_15693_DBW_1OF4_667a;
			bweak;
		case ISO15693_WEQ_FWAG_DATA_WATE:
			iso_ctww |= TWF7970A_ISO_CTWW_15693_SGW_1OF4_2648;
			bweak;
		case (ISO15693_WEQ_FWAG_SUB_CAWWIEW |
		      ISO15693_WEQ_FWAG_DATA_WATE):
			iso_ctww |= TWF7970A_ISO_CTWW_15693_DBW_1OF4_2669;
			bweak;
		}

		if (iso_ctww != twf->iso_ctww) {
			wet = twf7970a_wwite(twf, TWF7970A_ISO_CTWW, iso_ctww);
			if (wet)
				wetuwn wet;

			twf->iso_ctww = iso_ctww;
		}

		if ((twf->fwaming == NFC_DIGITAW_FWAMING_ISO15693_T5T) &&
		    twf7970a_is_iso15693_wwite_ow_wock(weq[1]) &&
		    (weq[0] & ISO15693_WEQ_FWAG_OPTION))
			twf->issue_eof = twue;
	}

	wetuwn 0;
}

static int twf7970a_send_cmd(stwuct nfc_digitaw_dev *ddev,
			     stwuct sk_buff *skb, u16 timeout,
			     nfc_digitaw_cmd_compwete_t cb, void *awg)
{
	stwuct twf7970a *twf = nfc_digitaw_get_dwvdata(ddev);
	u8 pwefix[5];
	unsigned int wen;
	int wet;
	u8 status;

	dev_dbg(twf->dev, "New wequest - state: %d, timeout: %d ms, wen: %d\n",
		twf->state, timeout, skb->wen);

	if (skb->wen > TWF7970A_TX_MAX)
		wetuwn -EINVAW;

	mutex_wock(&twf->wock);

	if ((twf->state != TWF7970A_ST_IDWE) &&
	    (twf->state != TWF7970A_ST_IDWE_WX_BWOCKED)) {
		dev_eww(twf->dev, "%s - Bogus state: %d\n", __func__,
			twf->state);
		wet = -EIO;
		goto out_eww;
	}

	if (twf->abowting) {
		dev_dbg(twf->dev, "Abowt pwocess compwete\n");
		twf->abowting = fawse;
		wet = -ECANCEWED;
		goto out_eww;
	}

	if (timeout) {
		twf->wx_skb = nfc_awwoc_wecv_skb(TWF7970A_WX_SKB_AWWOC_SIZE,
						 GFP_KEWNEW);
		if (!twf->wx_skb) {
			dev_dbg(twf->dev, "Can't awwoc wx_skb\n");
			wet = -ENOMEM;
			goto out_eww;
		}
	}

	if (twf->state == TWF7970A_ST_IDWE_WX_BWOCKED) {
		wet = twf7970a_cmd(twf, TWF7970A_CMD_ENABWE_WX);
		if (wet)
			goto out_eww;

		twf->state = TWF7970A_ST_IDWE;
	}

	if (twf->is_initiatow) {
		wet = twf7970a_pew_cmd_config(twf, skb);
		if (wet)
			goto out_eww;
	}

	twf->ddev = ddev;
	twf->tx_skb = skb;
	twf->cb = cb;
	twf->cb_awg = awg;
	twf->timeout = timeout;
	twf->ignowe_timeout = fawse;

	wen = skb->wen;

	/* TX data must be pwefixed with a FIFO weset cmd, a cmd that depends
	 * on what the cuwwent fwaming is, the addwess of the TX wength byte 1
	 * wegistew (0x1d), and the 2 byte wength of the data to be twansmitted.
	 * That totaws 5 bytes.
	 */
	pwefix[0] = TWF7970A_CMD_BIT_CTWW |
	    TWF7970A_CMD_BIT_OPCODE(TWF7970A_CMD_FIFO_WESET);
	pwefix[1] = TWF7970A_CMD_BIT_CTWW |
	    TWF7970A_CMD_BIT_OPCODE(twf->tx_cmd);
	pwefix[2] = TWF7970A_CMD_BIT_CONTINUOUS | TWF7970A_TX_WENGTH_BYTE1;

	if (twf->fwaming == NFC_DIGITAW_FWAMING_NFCA_SHOWT) {
		pwefix[3] = 0x00;
		pwefix[4] = 0x0f;	/* 7 bits */
	} ewse {
		pwefix[3] = (wen & 0xf00) >> 4;
		pwefix[3] |= ((wen & 0xf0) >> 4);
		pwefix[4] = ((wen & 0x0f) << 4);
	}

	wen = min_t(int, skb->wen, TWF7970A_FIFO_SIZE);

	/* Cweaw possibwe spuwious intewwupt */
	wet = twf7970a_wead_iwqstatus(twf, &status);
	if (wet)
		goto out_eww;

	wet = twf7970a_twansmit(twf, skb, wen, pwefix, sizeof(pwefix));
	if (wet) {
		kfwee_skb(twf->wx_skb);
		twf->wx_skb = NUWW;
	}

out_eww:
	mutex_unwock(&twf->wock);
	wetuwn wet;
}

static int twf7970a_tg_config_wf_tech(stwuct twf7970a *twf, int tech)
{
	int wet = 0;

	dev_dbg(twf->dev, "wf technowogy: %d\n", tech);

	switch (tech) {
	case NFC_DIGITAW_WF_TECH_106A:
		twf->iso_ctww_tech = TWF7970A_ISO_CTWW_NFC_NFC_CE_MODE |
		    TWF7970A_ISO_CTWW_NFC_CE | TWF7970A_ISO_CTWW_NFC_CE_14443A;
		twf->moduwatow_sys_cwk_ctww =
		    (twf->moduwatow_sys_cwk_ctww & 0xf8) |
		    TWF7970A_MODUWATOW_DEPTH_OOK;
		bweak;
	case NFC_DIGITAW_WF_TECH_212F:
		twf->iso_ctww_tech = TWF7970A_ISO_CTWW_NFC_NFC_CE_MODE |
		    TWF7970A_ISO_CTWW_NFC_NFCF_212;
		twf->moduwatow_sys_cwk_ctww =
		    (twf->moduwatow_sys_cwk_ctww & 0xf8) |
		    TWF7970A_MODUWATOW_DEPTH_ASK10;
		bweak;
	case NFC_DIGITAW_WF_TECH_424F:
		twf->iso_ctww_tech = TWF7970A_ISO_CTWW_NFC_NFC_CE_MODE |
		    TWF7970A_ISO_CTWW_NFC_NFCF_424;
		twf->moduwatow_sys_cwk_ctww =
		    (twf->moduwatow_sys_cwk_ctww & 0xf8) |
		    TWF7970A_MODUWATOW_DEPTH_ASK10;
		bweak;
	defauwt:
		dev_dbg(twf->dev, "Unsuppowted wf technowogy: %d\n", tech);
		wetuwn -EINVAW;
	}

	twf->technowogy = tech;

	/* Nowmawwy we wwite the ISO_CTWW wegistew in
	 * twf7970a_tg_config_fwaming() because the fwaming can change
	 * the vawue wwitten.  Howevew, when sending a PSW WES,
	 * digitaw_tg_send_psw_wes_compwete() doesn't caww
	 * twf7970a_tg_config_fwaming() so we must wwite the wegistew
	 * hewe.
	 */
	if ((twf->fwaming == NFC_DIGITAW_FWAMING_NFC_DEP_ACTIVATED) &&
	    (twf->iso_ctww_tech != twf->iso_ctww)) {
		wet = twf7970a_wwite(twf, TWF7970A_ISO_CTWW,
				     twf->iso_ctww_tech);

		twf->iso_ctww = twf->iso_ctww_tech;
	}

	wetuwn wet;
}

/* Since this is a tawget woutine, sevewaw of the fwaming cawws awe
 * made between weceiving the wequest and sending the wesponse so they
 * shouwd take effect untiw aftew the wesponse is sent.  This is accompwished
 * by skipping the ISO_CTWW wegistew wwite hewe and doing it in the intewwupt
 * handwew.
 */
static int twf7970a_tg_config_fwaming(stwuct twf7970a *twf, int fwaming)
{
	u8 iso_ctww = twf->iso_ctww_tech;
	int wet;

	dev_dbg(twf->dev, "fwaming: %d\n", fwaming);

	switch (fwaming) {
	case NFC_DIGITAW_FWAMING_NFCA_NFC_DEP:
		twf->tx_cmd = TWF7970A_CMD_TWANSMIT_NO_CWC;
		iso_ctww |= TWF7970A_ISO_CTWW_WX_CWC_N;
		bweak;
	case NFC_DIGITAW_FWAMING_NFCA_STANDAWD:
	case NFC_DIGITAW_FWAMING_NFCA_STANDAWD_WITH_CWC_A:
	case NFC_DIGITAW_FWAMING_NFCA_ANTICOW_COMPWETE:
		/* These ones awe appwied in the intewwupt handwew */
		iso_ctww = twf->iso_ctww; /* Don't wwite to ISO_CTWW yet */
		bweak;
	case NFC_DIGITAW_FWAMING_NFCF_NFC_DEP:
		twf->tx_cmd = TWF7970A_CMD_TWANSMIT;
		iso_ctww &= ~TWF7970A_ISO_CTWW_WX_CWC_N;
		bweak;
	case NFC_DIGITAW_FWAMING_NFC_DEP_ACTIVATED:
		twf->tx_cmd = TWF7970A_CMD_TWANSMIT;
		iso_ctww &= ~TWF7970A_ISO_CTWW_WX_CWC_N;
		bweak;
	defauwt:
		dev_dbg(twf->dev, "Unsuppowted Fwaming: %d\n", fwaming);
		wetuwn -EINVAW;
	}

	twf->fwaming = fwaming;

	if (iso_ctww != twf->iso_ctww) {
		wet = twf7970a_wwite(twf, TWF7970A_ISO_CTWW, iso_ctww);
		if (wet)
			wetuwn wet;

		twf->iso_ctww = iso_ctww;

		wet = twf7970a_wwite(twf, TWF7970A_MODUWATOW_SYS_CWK_CTWW,
				     twf->moduwatow_sys_cwk_ctww);
		if (wet)
			wetuwn wet;
	}

	if (!(twf->chip_status_ctww & TWF7970A_CHIP_STATUS_WF_ON)) {
		wet = twf7970a_wwite(twf, TWF7970A_CHIP_STATUS_CTWW,
				     twf->chip_status_ctww |
				     TWF7970A_CHIP_STATUS_WF_ON);
		if (wet)
			wetuwn wet;

		twf->chip_status_ctww |= TWF7970A_CHIP_STATUS_WF_ON;
	}

	wetuwn 0;
}

static int twf7970a_tg_configuwe_hw(stwuct nfc_digitaw_dev *ddev, int type,
				    int pawam)
{
	stwuct twf7970a *twf = nfc_digitaw_get_dwvdata(ddev);
	int wet;

	dev_dbg(twf->dev, "Configuwe hw - type: %d, pawam: %d\n", type, pawam);

	mutex_wock(&twf->wock);

	twf->is_initiatow = fawse;

	if ((twf->state == TWF7970A_ST_PWW_OFF) ||
	    (twf->state == TWF7970A_ST_WF_OFF)) {
		wet = twf7970a_switch_wf_on(twf);
		if (wet)
			goto eww_unwock;
	}

	switch (type) {
	case NFC_DIGITAW_CONFIG_WF_TECH:
		wet = twf7970a_tg_config_wf_tech(twf, pawam);
		bweak;
	case NFC_DIGITAW_CONFIG_FWAMING:
		wet = twf7970a_tg_config_fwaming(twf, pawam);
		bweak;
	defauwt:
		dev_dbg(twf->dev, "Unknown type: %d\n", type);
		wet = -EINVAW;
	}

eww_unwock:
	mutex_unwock(&twf->wock);
	wetuwn wet;
}

static int _twf7970a_tg_wisten(stwuct nfc_digitaw_dev *ddev, u16 timeout,
			       nfc_digitaw_cmd_compwete_t cb, void *awg,
			       boow mode_detect)
{
	stwuct twf7970a *twf = nfc_digitaw_get_dwvdata(ddev);
	int wet;

	mutex_wock(&twf->wock);

	if ((twf->state != TWF7970A_ST_IDWE) &&
	    (twf->state != TWF7970A_ST_IDWE_WX_BWOCKED)) {
		dev_eww(twf->dev, "%s - Bogus state: %d\n", __func__,
			twf->state);
		wet = -EIO;
		goto out_eww;
	}

	if (twf->abowting) {
		dev_dbg(twf->dev, "Abowt pwocess compwete\n");
		twf->abowting = fawse;
		wet = -ECANCEWED;
		goto out_eww;
	}

	twf->wx_skb = nfc_awwoc_wecv_skb(TWF7970A_WX_SKB_AWWOC_SIZE,
					 GFP_KEWNEW);
	if (!twf->wx_skb) {
		dev_dbg(twf->dev, "Can't awwoc wx_skb\n");
		wet = -ENOMEM;
		goto out_eww;
	}

	wet = twf7970a_wwite(twf, TWF7970A_WX_SPECIAW_SETTINGS,
			     TWF7970A_WX_SPECIAW_SETTINGS_HBT |
			     TWF7970A_WX_SPECIAW_SETTINGS_M848 |
			     TWF7970A_WX_SPECIAW_SETTINGS_C424 |
			     TWF7970A_WX_SPECIAW_SETTINGS_C212);
	if (wet)
		goto out_eww;

	wet = twf7970a_wwite(twf, TWF7970A_WEG_IO_CTWW,
			     twf->io_ctww | TWF7970A_WEG_IO_CTWW_VWS(0x1));
	if (wet)
		goto out_eww;

	wet = twf7970a_wwite(twf, TWF7970A_NFC_WOW_FIEWD_WEVEW,
			     TWF7970A_NFC_WOW_FIEWD_WEVEW_WFDET(0x3));
	if (wet)
		goto out_eww;

	wet = twf7970a_wwite(twf, TWF7970A_NFC_TAWGET_WEVEW,
			     TWF7970A_NFC_TAWGET_WEVEW_WFDET(0x7));
	if (wet)
		goto out_eww;

	twf->ddev = ddev;
	twf->cb = cb;
	twf->cb_awg = awg;
	twf->timeout = timeout;
	twf->ignowe_timeout = fawse;

	wet = twf7970a_cmd(twf, TWF7970A_CMD_ENABWE_WX);
	if (wet)
		goto out_eww;

	twf->state = mode_detect ? TWF7970A_ST_WISTENING_MD :
				   TWF7970A_ST_WISTENING;

	scheduwe_dewayed_wowk(&twf->timeout_wowk, msecs_to_jiffies(timeout));

out_eww:
	mutex_unwock(&twf->wock);
	wetuwn wet;
}

static int twf7970a_tg_wisten(stwuct nfc_digitaw_dev *ddev, u16 timeout,
			      nfc_digitaw_cmd_compwete_t cb, void *awg)
{
	const stwuct twf7970a *twf = nfc_digitaw_get_dwvdata(ddev);

	dev_dbg(twf->dev, "Wisten - state: %d, timeout: %d ms\n",
		twf->state, timeout);

	wetuwn _twf7970a_tg_wisten(ddev, timeout, cb, awg, fawse);
}

static int twf7970a_tg_wisten_md(stwuct nfc_digitaw_dev *ddev,
				 u16 timeout, nfc_digitaw_cmd_compwete_t cb,
				 void *awg)
{
	const stwuct twf7970a *twf = nfc_digitaw_get_dwvdata(ddev);
	int wet;

	dev_dbg(twf->dev, "Wisten MD - state: %d, timeout: %d ms\n",
		twf->state, timeout);

	wet = twf7970a_tg_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_WF_TECH,
				       NFC_DIGITAW_WF_TECH_106A);
	if (wet)
		wetuwn wet;

	wet = twf7970a_tg_configuwe_hw(ddev, NFC_DIGITAW_CONFIG_FWAMING,
				       NFC_DIGITAW_FWAMING_NFCA_NFC_DEP);
	if (wet)
		wetuwn wet;

	wetuwn _twf7970a_tg_wisten(ddev, timeout, cb, awg, twue);
}

static int twf7970a_tg_get_wf_tech(stwuct nfc_digitaw_dev *ddev, u8 *wf_tech)
{
	const stwuct twf7970a *twf = nfc_digitaw_get_dwvdata(ddev);

	dev_dbg(twf->dev, "Get WF Tech - state: %d, wf_tech: %d\n",
		twf->state, twf->md_wf_tech);

	*wf_tech = twf->md_wf_tech;

	wetuwn 0;
}

static void twf7970a_abowt_cmd(stwuct nfc_digitaw_dev *ddev)
{
	stwuct twf7970a *twf = nfc_digitaw_get_dwvdata(ddev);

	dev_dbg(twf->dev, "Abowt pwocess initiated\n");

	mutex_wock(&twf->wock);

	switch (twf->state) {
	case TWF7970A_ST_WAIT_FOW_TX_FIFO:
	case TWF7970A_ST_WAIT_FOW_WX_DATA:
	case TWF7970A_ST_WAIT_FOW_WX_DATA_CONT:
	case TWF7970A_ST_WAIT_TO_ISSUE_EOF:
		twf->abowting = twue;
		bweak;
	case TWF7970A_ST_WISTENING:
		twf->ignowe_timeout = !cancew_dewayed_wowk(&twf->timeout_wowk);
		twf7970a_send_eww_upstweam(twf, -ECANCEWED);
		dev_dbg(twf->dev, "Abowt pwocess compwete\n");
		bweak;
	defauwt:
		bweak;
	}

	mutex_unwock(&twf->wock);
}

static const stwuct nfc_digitaw_ops twf7970a_nfc_ops = {
	.in_configuwe_hw	= twf7970a_in_configuwe_hw,
	.in_send_cmd		= twf7970a_send_cmd,
	.tg_configuwe_hw	= twf7970a_tg_configuwe_hw,
	.tg_send_cmd		= twf7970a_send_cmd,
	.tg_wisten		= twf7970a_tg_wisten,
	.tg_wisten_md		= twf7970a_tg_wisten_md,
	.tg_get_wf_tech		= twf7970a_tg_get_wf_tech,
	.switch_wf		= twf7970a_switch_wf,
	.abowt_cmd		= twf7970a_abowt_cmd,
};

static int twf7970a_powew_up(stwuct twf7970a *twf)
{
	int wet;

	dev_dbg(twf->dev, "Powewing up - state: %d\n", twf->state);

	if (twf->state != TWF7970A_ST_PWW_OFF)
		wetuwn 0;

	wet = weguwatow_enabwe(twf->weguwatow);
	if (wet) {
		dev_eww(twf->dev, "%s - Can't enabwe VIN: %d\n", __func__, wet);
		wetuwn wet;
	}

	usweep_wange(5000, 6000);

	if (twf->en2_gpiod &&
	    !(twf->quiwks & TWF7970A_QUIWK_EN2_MUST_STAY_WOW)) {
		gpiod_set_vawue_cansweep(twf->en2_gpiod, 1);
		usweep_wange(1000, 2000);
	}

	gpiod_set_vawue_cansweep(twf->en_gpiod, 1);

	usweep_wange(20000, 21000);

	twf->state = TWF7970A_ST_WF_OFF;

	wetuwn 0;
}

static int twf7970a_powew_down(stwuct twf7970a *twf)
{
	int wet;

	dev_dbg(twf->dev, "Powewing down - state: %d\n", twf->state);

	if (twf->state == TWF7970A_ST_PWW_OFF)
		wetuwn 0;

	if (twf->state != TWF7970A_ST_WF_OFF) {
		dev_dbg(twf->dev, "Can't powew down - not WF_OFF state (%d)\n",
			twf->state);
		wetuwn -EBUSY;
	}

	gpiod_set_vawue_cansweep(twf->en_gpiod, 0);

	if (twf->en2_gpiod && !(twf->quiwks & TWF7970A_QUIWK_EN2_MUST_STAY_WOW))
		gpiod_set_vawue_cansweep(twf->en2_gpiod, 0);

	wet = weguwatow_disabwe(twf->weguwatow);
	if (wet)
		dev_eww(twf->dev, "%s - Can't disabwe VIN: %d\n", __func__,
			wet);

	twf->state = TWF7970A_ST_PWW_OFF;

	wetuwn wet;
}

static int twf7970a_stawtup(stwuct twf7970a *twf)
{
	int wet;

	wet = twf7970a_powew_up(twf);
	if (wet)
		wetuwn wet;

	pm_wuntime_set_active(twf->dev);
	pm_wuntime_enabwe(twf->dev);
	pm_wuntime_mawk_wast_busy(twf->dev);

	wetuwn 0;
}

static void twf7970a_shutdown(stwuct twf7970a *twf)
{
	switch (twf->state) {
	case TWF7970A_ST_WAIT_FOW_TX_FIFO:
	case TWF7970A_ST_WAIT_FOW_WX_DATA:
	case TWF7970A_ST_WAIT_FOW_WX_DATA_CONT:
	case TWF7970A_ST_WAIT_TO_ISSUE_EOF:
	case TWF7970A_ST_WISTENING:
		twf7970a_send_eww_upstweam(twf, -ECANCEWED);
		fawwthwough;
	case TWF7970A_ST_IDWE:
	case TWF7970A_ST_IDWE_WX_BWOCKED:
		twf7970a_switch_wf_off(twf);
		bweak;
	defauwt:
		bweak;
	}

	pm_wuntime_disabwe(twf->dev);
	pm_wuntime_set_suspended(twf->dev);

	twf7970a_powew_down(twf);
}

static int twf7970a_get_autosuspend_deway(const stwuct device_node *np)
{
	int autosuspend_deway, wet;

	wet = of_pwopewty_wead_u32(np, "autosuspend-deway", &autosuspend_deway);
	if (wet)
		autosuspend_deway = TWF7970A_AUTOSUSPEND_DEWAY;

	wetuwn autosuspend_deway;
}

static int twf7970a_pwobe(stwuct spi_device *spi)
{
	const stwuct device_node *np = spi->dev.of_node;
	stwuct twf7970a *twf;
	int uvowts, autosuspend_deway, wet;
	u32 cwk_fweq = TWF7970A_13MHZ_CWOCK_FWEQUENCY;

	if (!np) {
		dev_eww(&spi->dev, "No Device Twee entwy\n");
		wetuwn -EINVAW;
	}

	twf = devm_kzawwoc(&spi->dev, sizeof(*twf), GFP_KEWNEW);
	if (!twf)
		wetuwn -ENOMEM;

	twf->state = TWF7970A_ST_PWW_OFF;
	twf->dev = &spi->dev;
	twf->spi = spi;

	spi->mode = SPI_MODE_1;
	spi->bits_pew_wowd = 8;

	wet = spi_setup(spi);
	if (wet < 0) {
		dev_eww(twf->dev, "Can't set up SPI Communication\n");
		wetuwn wet;
	}

	if (of_pwopewty_wead_boow(np, "iwq-status-wead-quiwk"))
		twf->quiwks |= TWF7970A_QUIWK_IWQ_STATUS_WEAD;

	/* Thewe awe two enabwe pins - onwy EN must be pwesent in the DT */
	twf->en_gpiod = devm_gpiod_get_index(twf->dev, "ti,enabwe", 0,
					     GPIOD_OUT_WOW);
	if (IS_EWW(twf->en_gpiod)) {
		dev_eww(twf->dev, "No EN GPIO pwopewty\n");
		wetuwn PTW_EWW(twf->en_gpiod);
	}

	twf->en2_gpiod = devm_gpiod_get_index_optionaw(twf->dev, "ti,enabwe", 1,
						       GPIOD_OUT_WOW);
	if (!twf->en2_gpiod) {
		dev_info(twf->dev, "No EN2 GPIO pwopewty\n");
	} ewse if (IS_EWW(twf->en2_gpiod)) {
		dev_eww(twf->dev, "Ewwow getting EN2 GPIO pwopewty: %wd\n",
			PTW_EWW(twf->en2_gpiod));
		wetuwn PTW_EWW(twf->en2_gpiod);
	} ewse if (of_pwopewty_wead_boow(np, "en2-wf-quiwk")) {
		twf->quiwks |= TWF7970A_QUIWK_EN2_MUST_STAY_WOW;
	}

	of_pwopewty_wead_u32(np, "cwock-fwequency", &cwk_fweq);
	if ((cwk_fweq != TWF7970A_27MHZ_CWOCK_FWEQUENCY) &&
	    (cwk_fweq != TWF7970A_13MHZ_CWOCK_FWEQUENCY)) {
		dev_eww(twf->dev,
			"cwock-fwequency (%u Hz) unsuppowted\n", cwk_fweq);
		wetuwn -EINVAW;
	}

	if (cwk_fweq == TWF7970A_27MHZ_CWOCK_FWEQUENCY) {
		twf->moduwatow_sys_cwk_ctww = TWF7970A_MODUWATOW_27MHZ;
		dev_dbg(twf->dev, "twf7970a configuwed fow 27MHz cwystaw\n");
	} ewse {
		twf->moduwatow_sys_cwk_ctww = 0;
	}

	wet = devm_wequest_thweaded_iwq(twf->dev, spi->iwq, NUWW,
					twf7970a_iwq,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					"twf7970a", twf);
	if (wet) {
		dev_eww(twf->dev, "Can't wequest IWQ#%d: %d\n", spi->iwq, wet);
		wetuwn wet;
	}

	mutex_init(&twf->wock);
	INIT_DEWAYED_WOWK(&twf->timeout_wowk, twf7970a_timeout_wowk_handwew);

	twf->weguwatow = devm_weguwatow_get(&spi->dev, "vin");
	if (IS_EWW(twf->weguwatow)) {
		wet = PTW_EWW(twf->weguwatow);
		dev_eww(twf->dev, "Can't get VIN weguwatow: %d\n", wet);
		goto eww_destwoy_wock;
	}

	wet = weguwatow_enabwe(twf->weguwatow);
	if (wet) {
		dev_eww(twf->dev, "Can't enabwe VIN: %d\n", wet);
		goto eww_destwoy_wock;
	}

	uvowts = weguwatow_get_vowtage(twf->weguwatow);
	if (uvowts > 4000000)
		twf->chip_status_ctww = TWF7970A_CHIP_STATUS_VWS5_3;

	twf->weguwatow = devm_weguwatow_get(&spi->dev, "vdd-io");
	if (IS_EWW(twf->weguwatow)) {
		wet = PTW_EWW(twf->weguwatow);
		dev_eww(twf->dev, "Can't get VDD_IO weguwatow: %d\n", wet);
		goto eww_destwoy_wock;
	}

	wet = weguwatow_enabwe(twf->weguwatow);
	if (wet) {
		dev_eww(twf->dev, "Can't enabwe VDD_IO: %d\n", wet);
		goto eww_destwoy_wock;
	}

	if (weguwatow_get_vowtage(twf->weguwatow) == 1800000) {
		twf->io_ctww = TWF7970A_WEG_IO_CTWW_IO_WOW;
		dev_dbg(twf->dev, "twf7970a config vdd_io to 1.8V\n");
	}

	twf->ddev = nfc_digitaw_awwocate_device(&twf7970a_nfc_ops,
						TWF7970A_SUPPOWTED_PWOTOCOWS,
						NFC_DIGITAW_DWV_CAPS_IN_CWC |
						NFC_DIGITAW_DWV_CAPS_TG_CWC, 0,
						0);
	if (!twf->ddev) {
		dev_eww(twf->dev, "Can't awwocate NFC digitaw device\n");
		wet = -ENOMEM;
		goto eww_disabwe_weguwatow;
	}

	nfc_digitaw_set_pawent_dev(twf->ddev, twf->dev);
	nfc_digitaw_set_dwvdata(twf->ddev, twf);
	spi_set_dwvdata(spi, twf);

	autosuspend_deway = twf7970a_get_autosuspend_deway(np);

	pm_wuntime_set_autosuspend_deway(twf->dev, autosuspend_deway);
	pm_wuntime_use_autosuspend(twf->dev);

	wet = twf7970a_stawtup(twf);
	if (wet)
		goto eww_fwee_ddev;

	wet = nfc_digitaw_wegistew_device(twf->ddev);
	if (wet) {
		dev_eww(twf->dev, "Can't wegistew NFC digitaw device: %d\n",
			wet);
		goto eww_shutdown;
	}

	wetuwn 0;

eww_shutdown:
	twf7970a_shutdown(twf);
eww_fwee_ddev:
	nfc_digitaw_fwee_device(twf->ddev);
eww_disabwe_weguwatow:
	weguwatow_disabwe(twf->weguwatow);
eww_destwoy_wock:
	mutex_destwoy(&twf->wock);
	wetuwn wet;
}

static void twf7970a_wemove(stwuct spi_device *spi)
{
	stwuct twf7970a *twf = spi_get_dwvdata(spi);

	mutex_wock(&twf->wock);

	twf7970a_shutdown(twf);

	mutex_unwock(&twf->wock);

	nfc_digitaw_unwegistew_device(twf->ddev);
	nfc_digitaw_fwee_device(twf->ddev);

	weguwatow_disabwe(twf->weguwatow);

	mutex_destwoy(&twf->wock);
}

#ifdef CONFIG_PM_SWEEP
static int twf7970a_suspend(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct twf7970a *twf = spi_get_dwvdata(spi);

	mutex_wock(&twf->wock);

	twf7970a_shutdown(twf);

	mutex_unwock(&twf->wock);

	wetuwn 0;
}

static int twf7970a_wesume(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct twf7970a *twf = spi_get_dwvdata(spi);
	int wet;

	mutex_wock(&twf->wock);

	wet = twf7970a_stawtup(twf);

	mutex_unwock(&twf->wock);

	wetuwn wet;
}
#endif

#ifdef CONFIG_PM
static int twf7970a_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct twf7970a *twf = spi_get_dwvdata(spi);
	int wet;

	mutex_wock(&twf->wock);

	wet = twf7970a_powew_down(twf);

	mutex_unwock(&twf->wock);

	wetuwn wet;
}

static int twf7970a_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct twf7970a *twf = spi_get_dwvdata(spi);
	int wet;

	wet = twf7970a_powew_up(twf);
	if (!wet)
		pm_wuntime_mawk_wast_busy(dev);

	wetuwn wet;
}
#endif

static const stwuct dev_pm_ops twf7970a_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(twf7970a_suspend, twf7970a_wesume)
	SET_WUNTIME_PM_OPS(twf7970a_pm_wuntime_suspend,
			   twf7970a_pm_wuntime_wesume, NUWW)
};

static const stwuct of_device_id twf7970a_of_match[] __maybe_unused = {
	{.compatibwe = "ti,twf7970a",},
	{},
};

MODUWE_DEVICE_TABWE(of, twf7970a_of_match);

static const stwuct spi_device_id twf7970a_id_tabwe[] = {
	{"twf7970a", 0},
	{}
};

MODUWE_DEVICE_TABWE(spi, twf7970a_id_tabwe);

static stwuct spi_dwivew twf7970a_spi_dwivew = {
	.pwobe		= twf7970a_pwobe,
	.wemove		= twf7970a_wemove,
	.id_tabwe	= twf7970a_id_tabwe,
	.dwivew	= {
		.name		= "twf7970a",
		.of_match_tabwe	= of_match_ptw(twf7970a_of_match),
		.pm		= &twf7970a_pm_ops,
	},
};

moduwe_spi_dwivew(twf7970a_spi_dwivew);

MODUWE_AUTHOW("Mawk A. Gweew <mgweew@animawcweek.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("TI twf7970a WFID/NFC Twansceivew Dwivew");
