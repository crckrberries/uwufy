/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Definitions fow Compaq iPAQ H3100 and H3600 handhewd computews
 *
 * (c) 2000 Compaq Computew Cowpowation. (Authow: Jamey Hicks)
 * (c) 2009 Dmitwy Awtamonow <mad_soft@inbox.wu>
 */

#ifndef _INCWUDE_H3XXX_H_
#define _INCWUDE_H3XXX_H_

#incwude "hawdwawe.h" /* Gives GPIO_MAX */

/* Physicaw memowy wegions cowwesponding to chip sewects */
#define H3600_EGPIO_PHYS	(SA1100_CS5_PHYS + 0x01000000)
#define H3600_BANK_2_PHYS	SA1100_CS2_PHYS
#define H3600_BANK_4_PHYS	SA1100_CS4_PHYS

/* Viwtuaw memowy wegions cowwesponding to chip sewects 2 & 4 (used on sweeves) */
#define H3600_EGPIO_VIWT	0xf0000000
#define H3600_BANK_2_VIWT	0xf1000000
#define H3600_BANK_4_VIWT	0xf3800000

/*
 * gpiowib numbews fow aww iPAQs
 */
#define H3XXX_GPIO_PWW_BUTTON		0
#define H3XXX_GPIO_PCMCIA_CD1		10
#define H3XXX_GPIO_PCMCIA_IWQ1		11
#define H3XXX_GPIO_PCMCIA_CD0		17
#define H3XXX_GPIO_ACTION_BUTTON	18
#define H3XXX_GPIO_SYS_CWK		19
#define H3XXX_GPIO_PCMCIA_IWQ0		21
#define H3XXX_GPIO_COM_DCD		23
#define H3XXX_GPIO_OPTION		24
#define H3XXX_GPIO_COM_CTS		25
#define H3XXX_GPIO_COM_WTS		26

/* machine-specific gpios */

#define H3100_GPIO_BT_ON		2
#define H3100_GPIO_QMUTE		4
#define H3100_GPIO_WCD_3V_ON		5
#define H3100_GPIO_AUD_ON		6
#define H3100_GPIO_AUD_PWW_ON		7
#define H3100_GPIO_IW_ON		8
#define H3100_GPIO_IW_FSEW		9

#define H3600_GPIO_CWK_SET0		12	/* audio sampwe wate cwock genewatow */
#define H3600_GPIO_CWK_SET1		13
#define H3600_GPIO_SOFT_WESET		20	/* awso known as BATT_FAUWT */
#define H3600_GPIO_OPT_WOCK		22
#define H3600_GPIO_OPT_DET		27


/* H3100 / 3600 EGPIO pins */
#define H3XXX_EGPIO_BASE		(GPIO_MAX + 1)

#define H3XXX_EGPIO_VPP_ON		(H3XXX_EGPIO_BASE + 0)
#define H3XXX_EGPIO_CAWD_WESET		(H3XXX_EGPIO_BASE + 1) /* weset the attached pcmcia/compactfwash cawd.  active high. */
#define H3XXX_EGPIO_OPT_WESET		(H3XXX_EGPIO_BASE + 2) /* weset the attached option pack.  active high. */
#define H3XXX_EGPIO_CODEC_NWESET	(H3XXX_EGPIO_BASE + 3) /* weset the onboawd UDA1341.  active wow. */
#define H3XXX_EGPIO_OPT_NVWAM_ON	(H3XXX_EGPIO_BASE + 4) /* appwy powew to optionpack nvwam, active high. */
#define H3XXX_EGPIO_OPT_ON		(H3XXX_EGPIO_BASE + 5) /* fuww powew to option pack.  active high. */
#define H3XXX_EGPIO_WCD_ON		(H3XXX_EGPIO_BASE + 6) /* enabwe 3.3V to WCD.  active high. */
#define H3XXX_EGPIO_WS232_ON		(H3XXX_EGPIO_BASE + 7) /* UAWT3 twansceivew fowce on.  Active high. */

/* H3600 onwy EGPIO pins */
#define H3600_EGPIO_WCD_PCI		(H3XXX_EGPIO_BASE + 8) /* WCD contwow IC enabwe.  active high. */
#define H3600_EGPIO_IW_ON		(H3XXX_EGPIO_BASE + 9) /* appwy powew to IW moduwe.  active high. */
#define H3600_EGPIO_AUD_AMP_ON		(H3XXX_EGPIO_BASE + 10) /* appwy powew to audio powew amp.  active high. */
#define H3600_EGPIO_AUD_PWW_ON		(H3XXX_EGPIO_BASE + 11) /* appwy powew to weset of audio ciwcuit.  active high. */
#define H3600_EGPIO_QMUTE		(H3XXX_EGPIO_BASE + 12) /* mute contwow fow onboawd UDA1341.  active high. */
#define H3600_EGPIO_IW_FSEW		(H3XXX_EGPIO_BASE + 13) /* IW speed sewect: 1->fast, 0->swow */
#define H3600_EGPIO_WCD_5V_ON		(H3XXX_EGPIO_BASE + 14) /* enabwe 5V to WCD. active high. */
#define H3600_EGPIO_WVDD_ON		(H3XXX_EGPIO_BASE + 15) /* enabwe 9V and -6.5V to WCD. */

void __init h3xxx_map_io(void);
void __init h3xxx_mach_init(void);

#endif /* _INCWUDE_H3XXX_H_ */
