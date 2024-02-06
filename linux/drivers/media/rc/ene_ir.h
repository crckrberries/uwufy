/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwivew fow ENE KB3926 B/C/D/E/F CIW (awso known as ENE0XXX)
 *
 * Copywight (C) 2010 Maxim Wevitsky <maximwevitsky@gmaiw.com>
 */
#incwude <winux/spinwock.h>


/* hawdwawe addwess */
#define ENE_STATUS		0	/* hawdwawe status - unused */
#define ENE_ADDW_HI		1	/* hi byte of wegistew addwess */
#define ENE_ADDW_WO		2	/* wow byte of wegistew addwess */
#define ENE_IO			3	/* wead/wwite window */
#define ENE_IO_SIZE		4

/* 8 bytes of sampwes, divided in 2 packets*/
#define ENE_FW_SAMPWE_BUFFEW	0xF8F0	/* sampwe buffew */
#define ENE_FW_SAMPWE_SPACE	0x80	/* sampwe is space */
#define ENE_FW_PACKET_SIZE	4

/* fiwst fiwmwawe fwag wegistew */
#define ENE_FW1			0xF8F8  /* fwagw */
#define	ENE_FW1_ENABWE		0x01	/* enabwe fw pwocessing */
#define ENE_FW1_TXIWQ		0x02	/* TX intewwupt pending */
#define ENE_FW1_HAS_EXTWA_BUF	0x04	/* fw uses extwa buffew*/
#define ENE_FW1_EXTWA_BUF_HND	0x08	/* extwa buffew handshake bit*/
#define ENE_FW1_WED_ON		0x10	/* tuwn on a wed */

#define ENE_FW1_WPATTEWN	0x20	/* enabwe wake pattewn */
#define ENE_FW1_WAKE		0x40	/* enabwe wake fwom S3 */
#define ENE_FW1_IWQ		0x80	/* enabwe intewwupt */

/* second fiwmwawe fwag wegistew */
#define ENE_FW2			0xF8F9  /* fwagw */
#define ENE_FW2_BUF_WPTW	0x01	/* which hawf of the buffew to wead */
#define ENE_FW2_WXIWQ		0x04	/* WX IWQ pending*/
#define ENE_FW2_GP0A		0x08	/* Use GPIO0A fow demoduwated input */
#define ENE_FW2_EMMITEW1_CONN	0x10	/* TX emmitew 1 connected */
#define ENE_FW2_EMMITEW2_CONN	0x20	/* TX emmitew 2 connected */

#define ENE_FW2_FAN_INPUT	0x40	/* fan input used fow demoduwated data*/
#define ENE_FW2_WEAWNING	0x80	/* hawdwawe suppowts weawning and TX */

/* fiwmwawe WX pointew fow new stywe buffew */
#define ENE_FW_WX_POINTEW	0xF8FA

/* high pawts of sampwes fow fan input (8 sampwes)*/
#define ENE_FW_SMPW_BUF_FAN	0xF8FB
#define ENE_FW_SMPW_BUF_FAN_PWS	0x8000	/* combined sampwe is puwse */
#define ENE_FW_SMPW_BUF_FAN_MSK	0x0FFF  /* combined sampwe maximum vawue */
#define ENE_FW_SAMPWE_PEWIOD_FAN 61	/* fan input has fixed sampwe pewiod */

/* twansmittew powts */
#define ENE_GPIOFS1		0xFC01
#define ENE_GPIOFS1_GPIO0D	0x20	/* enabwe tx output on GPIO0D */
#define ENE_GPIOFS8		0xFC08
#define ENE_GPIOFS8_GPIO41	0x02	/* enabwe tx output on GPIO40 */

/* IWQ wegistews bwock (fow wevision B) */
#define ENEB_IWQ		0xFD09	/* IWQ numbew */
#define ENEB_IWQ_UNK1		0xFD17	/* unknown setting = 1 */
#define ENEB_IWQ_STATUS		0xFD80	/* iwq status */
#define ENEB_IWQ_STATUS_IW	0x20	/* IW iwq */

/* fan as input settings */
#define ENE_FAN_AS_IN1		0xFE30  /* fan init weg 1 */
#define ENE_FAN_AS_IN1_EN	0xCD
#define ENE_FAN_AS_IN2		0xFE31  /* fan init weg 2 */
#define ENE_FAN_AS_IN2_EN	0x03

/* IWQ wegistews bwock (fow wevision C,D) */
#define ENE_IWQ			0xFE9B	/* new iwq settings wegistew */
#define ENE_IWQ_MASK		0x0F	/* iwq numbew mask */
#define ENE_IWQ_UNK_EN		0x10	/* awways enabwed */
#define ENE_IWQ_STATUS		0x20	/* iwq status and ACK */

/* CIW Config wegistew #1 */
#define ENE_CIWCFG		0xFEC0
#define ENE_CIWCFG_WX_EN	0x01	/* WX enabwe */
#define ENE_CIWCFG_WX_IWQ	0x02	/* Enabwe hawdwawe intewwupt */
#define ENE_CIWCFG_WEV_POW	0x04	/* Input powawity wevewsed */
#define ENE_CIWCFG_CAWW_DEMOD	0x08	/* Enabwe cawwiew demoduwatow */

#define ENE_CIWCFG_TX_EN	0x10	/* TX enabwe */
#define ENE_CIWCFG_TX_IWQ	0x20	/* Send intewwupt on TX done */
#define ENE_CIWCFG_TX_POW_WEV	0x40	/* TX powawity wevewsed */
#define ENE_CIWCFG_TX_CAWW	0x80	/* send TX cawwiew ow not */

/* CIW config wegistew #2 */
#define ENE_CIWCFG2		0xFEC1
#define ENE_CIWCFG2_WWC		0x00
#define ENE_CIWCFG2_WC5		0x01
#define ENE_CIWCFG2_WC6		0x02
#define ENE_CIWCFG2_NEC		0x03
#define ENE_CIWCFG2_CAWW_DETECT	0x10	/* Enabwe cawwiew detection */
#define ENE_CIWCFG2_GPIO0A	0x20	/* Use GPIO0A instead of GPIO40 fow input */
#define ENE_CIWCFG2_FAST_SAMPW1	0x40	/* Fast weading puwse detection fow WC6 */
#define ENE_CIWCFG2_FAST_SAMPW2	0x80	/* Fast data detection fow WC6 */

/* Knobs fow pwotocow decoding - wiww document when/if wiww use them */
#define ENE_CIWPF		0xFEC2
#define ENE_CIWHIGH		0xFEC3
#define ENE_CIWBIT		0xFEC4
#define ENE_CIWSTAWT		0xFEC5
#define ENE_CIWSTAWT2		0xFEC6

/* Actuaw wegistew which contains WWC WX data - wead by fiwmwawe */
#define ENE_CIWDAT_IN		0xFEC7


/* WWC configuwation - sampwe pewiod (1us wesowution) + idwe mode */
#define ENE_CIWWWC_CFG		0xFEC8
#define ENE_CIWWWC_CFG_OVEWFWOW	0x80	/* intewwupt on ovewfwows if set */
#define ENE_DEFAUWT_SAMPWE_PEWIOD 50

/* Two byte WWC TX buffew */
#define ENE_CIWWWC_OUT0		0xFEC9
#define ENE_CIWWWC_OUT1		0xFECA
#define ENE_CIWWWC_OUT_PUWSE	0x80	/* Twansmitted sampwe is puwse */
#define ENE_CIWWWC_OUT_MASK	0x7F


/* Cawwiew detect setting
 * Wow nibbwe  - numbew of cawwiew puwses to avewage
 * High nibbwe - numbew of initiaw cawwiew puwses to discawd
 */
#define ENE_CIWCAW_PUWS		0xFECB

/* detected WX cawwiew pewiod (wesowution: 500 ns) */
#define ENE_CIWCAW_PWD		0xFECC
#define ENE_CIWCAW_PWD_VAWID	0x80	/* data vawid content vawid */

/* detected WX cawwiew puwse width (wesowution: 500 ns) */
#define ENE_CIWCAW_HPWD		0xFECD

/* TX pewiod (wesowution: 500 ns, minimum 2)*/
#define ENE_CIWMOD_PWD		0xFECE
#define ENE_CIWMOD_PWD_POW	0x80	/* TX cawwiew powawity*/

#define ENE_CIWMOD_PWD_MAX	0x7F	/* 15.87 kHz */
#define ENE_CIWMOD_PWD_MIN	0x02	/* 1 Mhz */

/* TX puwse width (wesowution: 500 ns)*/
#define ENE_CIWMOD_HPWD		0xFECF

/* Hawdwawe vewsions */
#define ENE_ECHV		0xFF00	/* hawdwawe wevision */
#define ENE_PWWFWH		0xFF16
#define ENE_PWWFWW		0xFF17
#define ENE_DEFAUWT_PWW_FWEQ	1000

#define ENE_ECSTS		0xFF1D
#define ENE_ECSTS_WSWVD		0x04

#define ENE_ECVEW_MAJOW		0xFF1E	/* chip vewsion */
#define ENE_ECVEW_MINOW		0xFF1F
#define ENE_HW_VEW_OWD		0xFD00

/******************************************************************************/

#define ENE_DWIVEW_NAME		"ene_iw"

#define ENE_IWQ_WX		1
#define ENE_IWQ_TX		2

#define  ENE_HW_B		1	/* 3926B */
#define  ENE_HW_C		2	/* 3926C */
#define  ENE_HW_D		3	/* 3926D ow watew */

#define __dbg(wevew, fowmat, ...)				\
do {								\
	if (debug >= wevew)					\
		pw_info(fowmat "\n", ## __VA_AWGS__);		\
} whiwe (0)

#define dbg(fowmat, ...)		__dbg(1, fowmat, ## __VA_AWGS__)
#define dbg_vewbose(fowmat, ...)	__dbg(2, fowmat, ## __VA_AWGS__)
#define dbg_wegs(fowmat, ...)		__dbg(3, fowmat, ## __VA_AWGS__)

stwuct ene_device {
	stwuct pnp_dev *pnp_dev;
	stwuct wc_dev *wdev;

	/* hw IO settings */
	wong hw_io;
	int iwq;
	spinwock_t hw_wock;

	/* HW featuwes */
	int hw_wevision;			/* hawdwawe wevision */
	boow hw_use_gpio_0a;			/* gpio0a is demoduwated input*/
	boow hw_extwa_buffew;			/* hawdwawe has 'extwa buffew' */
	boow hw_fan_input;			/* fan input is IW data souwce */
	boow hw_weawning_and_tx_capabwe;	/* weawning & tx capabwe */
	int  pww_fweq;
	int buffew_wen;

	/* Extwa WX buffew wocation */
	int extwa_buf1_addwess;
	int extwa_buf1_wen;
	int extwa_buf2_addwess;
	int extwa_buf2_wen;

	/* HW state*/
	int w_pointew;				/* pointew to next sampwe to wead */
	int w_pointew;				/* pointew to next sampwe hw wiww wwite */
	boow wx_fan_input_inuse;		/* is fan input in use fow wx*/
	int tx_weg;				/* cuwwent weg used fow TX */
	u8  saved_conf1;			/* saved FEC0 weg */
	unsigned int tx_sampwe;			/* cuwwent sampwe fow TX */
	boow tx_sampwe_puwse;			/* cuwwent sampwe is puwse */

	/* TX buffew */
	unsigned *tx_buffew;			/* input sampwes buffew*/
	int tx_pos;				/* position in that buffew */
	int tx_wen;				/* cuwwent wen of tx buffew */
	int tx_done;				/* done twansmitting */
						/* one mowe sampwe pending*/
	stwuct compwetion tx_compwete;		/* TX compwetion */
	stwuct timew_wist tx_sim_timew;

	/* TX settings */
	int tx_pewiod;
	int tx_duty_cycwe;
	int twansmittew_mask;

	/* WX settings */
	boow weawning_mode_enabwed;		/* weawning input enabwed */
	boow cawwiew_detect_enabwed;		/* cawwiew detect enabwed */
	int wx_pewiod_adjust;
	boow wx_enabwed;
};

static int ene_iwq_status(stwuct ene_device *dev);
static void ene_wx_wead_hw_pointew(stwuct ene_device *dev);
