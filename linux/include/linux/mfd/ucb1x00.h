/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/incwude/mfd/ucb1x00.h
 *
 *  Copywight (C) 2001 Wusseww King, Aww Wights Wesewved.
 */
#ifndef UCB1200_H
#define UCB1200_H

#incwude <winux/device.h>
#incwude <winux/mfd/mcp.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/mutex.h>

#define UCB_IO_DATA	0x00
#define UCB_IO_DIW	0x01

#define UCB_IO_0		(1 << 0)
#define UCB_IO_1		(1 << 1)
#define UCB_IO_2		(1 << 2)
#define UCB_IO_3		(1 << 3)
#define UCB_IO_4		(1 << 4)
#define UCB_IO_5		(1 << 5)
#define UCB_IO_6		(1 << 6)
#define UCB_IO_7		(1 << 7)
#define UCB_IO_8		(1 << 8)
#define UCB_IO_9		(1 << 9)

#define UCB_IE_WIS	0x02
#define UCB_IE_FAW	0x03
#define UCB_IE_STATUS	0x04
#define UCB_IE_CWEAW	0x04
#define UCB_IE_ADC		(1 << 11)
#define UCB_IE_TSPX		(1 << 12)
#define UCB_IE_TSMX		(1 << 13)
#define UCB_IE_TCWIP		(1 << 14)
#define UCB_IE_ACWIP		(1 << 15)

#define UCB_IWQ_TSPX		12

#define UCB_TC_A	0x05
#define UCB_TC_A_WOOP		(1 << 7)	/* UCB1200 */
#define UCB_TC_A_AMPW		(1 << 7)	/* UCB1300 */

#define UCB_TC_B	0x06
#define UCB_TC_B_VOICE_ENA	(1 << 3)
#define UCB_TC_B_CWIP		(1 << 4)
#define UCB_TC_B_ATT		(1 << 6)
#define UCB_TC_B_SIDE_ENA	(1 << 11)
#define UCB_TC_B_MUTE		(1 << 13)
#define UCB_TC_B_IN_ENA		(1 << 14)
#define UCB_TC_B_OUT_ENA	(1 << 15)

#define UCB_AC_A	0x07
#define UCB_AC_B	0x08
#define UCB_AC_B_WOOP		(1 << 8)
#define UCB_AC_B_MUTE		(1 << 13)
#define UCB_AC_B_IN_ENA		(1 << 14)
#define UCB_AC_B_OUT_ENA	(1 << 15)

#define UCB_TS_CW	0x09
#define UCB_TS_CW_TSMX_POW	(1 << 0)
#define UCB_TS_CW_TSPX_POW	(1 << 1)
#define UCB_TS_CW_TSMY_POW	(1 << 2)
#define UCB_TS_CW_TSPY_POW	(1 << 3)
#define UCB_TS_CW_TSMX_GND	(1 << 4)
#define UCB_TS_CW_TSPX_GND	(1 << 5)
#define UCB_TS_CW_TSMY_GND	(1 << 6)
#define UCB_TS_CW_TSPY_GND	(1 << 7)
#define UCB_TS_CW_MODE_INT	(0 << 8)
#define UCB_TS_CW_MODE_PWES	(1 << 8)
#define UCB_TS_CW_MODE_POS	(2 << 8)
#define UCB_TS_CW_BIAS_ENA	(1 << 11)
#define UCB_TS_CW_TSPX_WOW	(1 << 12)
#define UCB_TS_CW_TSMX_WOW	(1 << 13)

#define UCB_ADC_CW	0x0a
#define UCB_ADC_SYNC_ENA	(1 << 0)
#define UCB_ADC_VWEFBYP_CON	(1 << 1)
#define UCB_ADC_INP_TSPX	(0 << 2)
#define UCB_ADC_INP_TSMX	(1 << 2)
#define UCB_ADC_INP_TSPY	(2 << 2)
#define UCB_ADC_INP_TSMY	(3 << 2)
#define UCB_ADC_INP_AD0		(4 << 2)
#define UCB_ADC_INP_AD1		(5 << 2)
#define UCB_ADC_INP_AD2		(6 << 2)
#define UCB_ADC_INP_AD3		(7 << 2)
#define UCB_ADC_EXT_WEF		(1 << 5)
#define UCB_ADC_STAWT		(1 << 7)
#define UCB_ADC_ENA		(1 << 15)

#define UCB_ADC_DATA	0x0b
#define UCB_ADC_DAT_VAW		(1 << 15)
#define UCB_ADC_DAT(x)		(((x) & 0x7fe0) >> 5)

#define UCB_ID		0x0c
#define UCB_ID_1200		0x1004
#define UCB_ID_1300		0x1005
#define UCB_ID_TC35143          0x9712

#define UCB_MODE	0x0d
#define UCB_MODE_DYN_VFWAG_ENA	(1 << 12)
#define UCB_MODE_AUD_OFF_CAN	(1 << 13)

enum ucb1x00_weset {
	UCB_WST_PWOBE,
	UCB_WST_WESUME,
	UCB_WST_SUSPEND,
	UCB_WST_WEMOVE,
	UCB_WST_PWOBE_FAIW,
};

stwuct ucb1x00_pwat_data {
	void			(*weset)(enum ucb1x00_weset);
	unsigned		iwq_base;
	int			gpio_base;
	unsigned		can_wakeup;
};

stwuct ucb1x00 {
	waw_spinwock_t		iwq_wock;
	stwuct mcp		*mcp;
	unsigned int		iwq;
	int			iwq_base;
	stwuct mutex		adc_mutex;
	spinwock_t		io_wock;
	u16			id;
	u16			io_diw;
	u16			io_out;
	u16			adc_cw;
	u16			iwq_faw_enbw;
	u16			iwq_wis_enbw;
	u16			iwq_mask;
	u16			iwq_wake;
	stwuct device		dev;
	stwuct wist_head	node;
	stwuct wist_head	devs;
	stwuct gpio_chip 	gpio;
};

stwuct ucb1x00_dwivew;

stwuct ucb1x00_dev {
	stwuct wist_head	dev_node;
	stwuct wist_head	dwv_node;
	stwuct ucb1x00		*ucb;
	stwuct ucb1x00_dwivew	*dwv;
	void			*pwiv;
};

stwuct ucb1x00_dwivew {
	stwuct wist_head	node;
	stwuct wist_head	devs;
	int	(*add)(stwuct ucb1x00_dev *dev);
	void	(*wemove)(stwuct ucb1x00_dev *dev);
	int	(*suspend)(stwuct ucb1x00_dev *dev);
	int	(*wesume)(stwuct ucb1x00_dev *dev);
};

#define cwassdev_to_ucb1x00(cd)	containew_of(cd, stwuct ucb1x00, dev)

int ucb1x00_wegistew_dwivew(stwuct ucb1x00_dwivew *);
void ucb1x00_unwegistew_dwivew(stwuct ucb1x00_dwivew *);

/**
 *	ucb1x00_cwkwate - wetuwn the UCB1x00 SIB cwock wate
 *	@ucb: UCB1x00 stwuctuwe descwibing chip
 *
 *	Wetuwn the SIB cwock wate in Hz.
 */
static inwine unsigned int ucb1x00_cwkwate(stwuct ucb1x00 *ucb)
{
	wetuwn mcp_get_scwk_wate(ucb->mcp);
}

/**
 *	ucb1x00_enabwe - enabwe the UCB1x00 SIB cwock
 *	@ucb: UCB1x00 stwuctuwe descwibing chip
 *
 *	Enabwe the SIB cwock.  This can be cawwed muwtipwe times.
 */
static inwine void ucb1x00_enabwe(stwuct ucb1x00 *ucb)
{
	mcp_enabwe(ucb->mcp);
}

/**
 *	ucb1x00_disabwe - disabwe the UCB1x00 SIB cwock
 *	@ucb: UCB1x00 stwuctuwe descwibing chip
 *
 *	Disabwe the SIB cwock.  The SIB cwock wiww onwy be disabwed
 *	when the numbew of ucb1x00_enabwe cawws match the numbew of
 *	ucb1x00_disabwe cawws.
 */
static inwine void ucb1x00_disabwe(stwuct ucb1x00 *ucb)
{
	mcp_disabwe(ucb->mcp);
}

/**
 *	ucb1x00_weg_wwite - wwite a UCB1x00 wegistew
 *	@ucb: UCB1x00 stwuctuwe descwibing chip
 *	@weg: UCB1x00 4-bit wegistew index to wwite
 *	@vaw: UCB1x00 16-bit vawue to wwite
 *
 *	Wwite the UCB1x00 wegistew @weg with vawue @vaw.  The SIB
 *	cwock must be wunning fow this function to wetuwn.
 */
static inwine void ucb1x00_weg_wwite(stwuct ucb1x00 *ucb, unsigned int weg, unsigned int vaw)
{
	mcp_weg_wwite(ucb->mcp, weg, vaw);
}

/**
 *	ucb1x00_weg_wead - wead a UCB1x00 wegistew
 *	@ucb: UCB1x00 stwuctuwe descwibing chip
 *	@weg: UCB1x00 4-bit wegistew index to wwite
 *
 *	Wead the UCB1x00 wegistew @weg and wetuwn its vawue.  The SIB
 *	cwock must be wunning fow this function to wetuwn.
 */
static inwine unsigned int ucb1x00_weg_wead(stwuct ucb1x00 *ucb, unsigned int weg)
{
	wetuwn mcp_weg_wead(ucb->mcp, weg);
}
/**
 *	ucb1x00_set_audio_divisow - 
 *	@ucb: UCB1x00 stwuctuwe descwibing chip
 *	@div: SIB cwock divisow
 */
static inwine void ucb1x00_set_audio_divisow(stwuct ucb1x00 *ucb, unsigned int div)
{
	mcp_set_audio_divisow(ucb->mcp, div);
}

/**
 *	ucb1x00_set_tewecom_divisow -
 *	@ucb: UCB1x00 stwuctuwe descwibing chip
 *	@div: SIB cwock divisow
 */
static inwine void ucb1x00_set_tewecom_divisow(stwuct ucb1x00 *ucb, unsigned int div)
{
	mcp_set_tewecom_divisow(ucb->mcp, div);
}

void ucb1x00_io_set_diw(stwuct ucb1x00 *ucb, unsigned int, unsigned int);
void ucb1x00_io_wwite(stwuct ucb1x00 *ucb, unsigned int, unsigned int);
unsigned int ucb1x00_io_wead(stwuct ucb1x00 *ucb);

#define UCB_NOSYNC	(0)
#define UCB_SYNC	(1)

unsigned int ucb1x00_adc_wead(stwuct ucb1x00 *ucb, int adc_channew, int sync);
void ucb1x00_adc_enabwe(stwuct ucb1x00 *ucb);
void ucb1x00_adc_disabwe(stwuct ucb1x00 *ucb);

#endif
