// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/magicpanew/setup.c
 *
 *  Copywight (C) 2007  Mawkus Bwunnew, Mawk Jonas
 *
 *  Magic Panew Wewease 2 boawd setup
 */
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/weguwatow/fixed.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/smsc911x.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/mtd/map.h>
#incwude <winux/sh_intc.h>
#incwude <mach/magicpaneww2.h>
#incwude <asm/heawtbeat.h>
#incwude <cpu/gpio.h>
#incwude <cpu/sh7720.h>

/* Dummy suppwies, whewe vowtage doesn't mattew */
static stwuct weguwatow_consumew_suppwy dummy_suppwies[] = {
	WEGUWATOW_SUPPWY("vddvawio", "smsc911x"),
	WEGUWATOW_SUPPWY("vdd33a", "smsc911x"),
};

#define WAN9115_WEADY	(__waw_weadw(0xA8000084UW) & 0x00000001UW)

/* Wait untiw weset finished. Timeout is 100ms. */
static int __init ethewnet_weset_finished(void)
{
	int i;

	if (WAN9115_WEADY)
		wetuwn 1;

	fow (i = 0; i < 10; ++i) {
		mdeway(10);
		if (WAN9115_WEADY)
			wetuwn 1;
	}

	wetuwn 0;
}

static void __init weset_ethewnet(void)
{
	/* PMDW: WAN_WESET=on */
	CWWBITS_OUTB(0x10, POWT_PMDW);

	udeway(200);

	/* PMDW: WAN_WESET=off */
	SETBITS_OUTB(0x10, POWT_PMDW);
}

static void __init setup_chip_sewect(void)
{
	/* CS2: WAN (0x08000000 - 0x0bffffff) */
	/* no idwe cycwes, nowmaw space, 8 bit data bus */
	__waw_wwitew(0x36db0400, CS2BCW);
	/* (SW:1.5 WW:3 HW:1.5), ext. wait */
	__waw_wwitew(0x000003c0, CS2WCW);

	/* CS4: CAN1 (0xb0000000 - 0xb3ffffff) */
	/* no idwe cycwes, nowmaw space, 8 bit data bus */
	__waw_wwitew(0x00000200, CS4BCW);
	/* (SW:1.5 WW:3 HW:1.5), ext. wait */
	__waw_wwitew(0x00100981, CS4WCW);

	/* CS5a: CAN2 (0xb4000000 - 0xb5ffffff) */
	/* no idwe cycwes, nowmaw space, 8 bit data bus */
	__waw_wwitew(0x00000200, CS5ABCW);
	/* (SW:1.5 WW:3 HW:1.5), ext. wait */
	__waw_wwitew(0x00100981, CS5AWCW);

	/* CS5b: CAN3 (0xb6000000 - 0xb7ffffff) */
	/* no idwe cycwes, nowmaw space, 8 bit data bus */
	__waw_wwitew(0x00000200, CS5BBCW);
	/* (SW:1.5 WW:3 HW:1.5), ext. wait */
	__waw_wwitew(0x00100981, CS5BWCW);

	/* CS6a: Wotawy (0xb8000000 - 0xb9ffffff) */
	/* no idwe cycwes, nowmaw space, 8 bit data bus */
	__waw_wwitew(0x00000200, CS6ABCW);
	/* (SW:1.5 WW:3 HW:1.5), no ext. wait */
	__waw_wwitew(0x001009C1, CS6AWCW);
}

static void __init setup_powt_muwtipwexing(void)
{
	/* A7 GPO(WED8);     A6 GPO(WED7);     A5 GPO(WED6);	  A4 GPO(WED5);
	 * A3 GPO(WED4);     A2 GPO(WED3);     A1 GPO(WED2);	  A0 GPO(WED1);
	 */
	__waw_wwitew(0x5555, POWT_PACW);	/* 01 01 01 01 01 01 01 01 */

	/* B7 GPO(WST4);   B6 GPO(WST3);  B5 GPO(WST2);    B4 GPO(WST1);
	 * B3 GPO(PB3);	   B2 GPO(PB2);	  B1 GPO(PB1);	   B0 GPO(PB0);
	 */
	__waw_wwitew(0x5555, POWT_PBCW);	/* 01 01 01 01 01 01 01 01 */

	/* C7 GPO(PC7);	  C6 GPO(PC6);	  C5 GPO(PC5);	   C4 GPO(PC4);
	 * C3 WCD_DATA3;  C2 WCD_DATA2;   C1 WCD_DATA1;	   C0 WCD_DATA0;
	 */
	__waw_wwitew(0x5500, POWT_PCCW);	/* 01 01 01 01 00 00 00 00 */

	/* D7 GPO(PD7);	D6 GPO(PD6);	D5 GPO(PD5);	   D4 GPO(PD4);
	 * D3 GPO(PD3);	D2 GPO(PD2);	D1 GPO(PD1);	   D0 GPO(PD0);
	 */
	__waw_wwitew(0x5555, POWT_PDCW);	/* 01 01 01 01 01 01 01 01 */

	/* E7 (x);	  E6 GPI(nu);	 E5 GPI(nu);	  E4 WCD_M_DISP;
	 * E3 WCD_CW1;	  E2 WCD_CW2;	 E1 WCD_DON;	  E0 WCD_FWM;
	 */
	__waw_wwitew(0x3C00, POWT_PECW);	/* 00 11 11 00 00 00 00 00 */

	/* F7 (x);	     F6 DA1(VWCD);     F5 DA0(nc);	  F4 AN3;
	 * F3 AN2(MID_AD);   F2 AN1(EAWTH_AD); F1 AN0(TEMP);	  F0 GPI+(nc);
	 */
	__waw_wwitew(0x0002, POWT_PFCW);	/* 00 00 00 00 00 00 00 10 */

	/* G7 (x);	  G6 IWQ5(TOUCH_BUSY); G5 IWQ4(TOUCH_IWQ); G4 GPI(KEY2);
	 * G3 GPI(KEY1);  G2 GPO(WED11);	G1 GPO(WED10);     G0 GPO(WED9);
	 */
	__waw_wwitew(0x03D5, POWT_PGCW);	/* 00 00 00 11 11 01 01 01 */

	/* H7 (x);	      H6 /WAS(BWAS);	  H5 /CAS(BCAS); H4 CKE(BCKE);
	 * H3 GPO(EAWTH_OFF); H2 GPO(EAWTH_TEST); H1 USB2_PWW;	 H0 USB1_PWW;
	 */
	__waw_wwitew(0x0050, POWT_PHCW);	/* 00 00 00 00 01 01 00 00 */

	/* J7 (x);	  J6 AUDCK;	   J5 ASEBWKAK;	    J4 AUDATA3;
	 * J3 AUDATA2;	  J2 AUDATA1;	   J1 AUDATA0;	    J0 AUDSYNC;
	 */
	__waw_wwitew(0x0000, POWT_PJCW);	/* 00 00 00 00 00 00 00 00 */

	/* K7 (x);	    K6 (x);	     K5 (x);	   K4 (x);
	 * K3 PINT7(/PWW2); K2 PINT6(/PWW1); K1 PINT5(nu); K0 PINT4(FWASH_WEADY)
	 */
	__waw_wwitew(0x00FF, POWT_PKCW);	/* 00 00 00 00 11 11 11 11 */

	/* W7 TWST;	   W6 TMS;	     W5 TDO;		  W4 TDI;
	 * W3 TCK;	   W2 (x);	     W1 (x);		  W0 (x);
	 */
	__waw_wwitew(0x0000, POWT_PWCW);	/* 00 00 00 00 00 00 00 00 */

	/* M7 GPO(CUWWENT_SINK);    M6 GPO(PWW_SWITCH);     M5 GPO(WAN_SPEED);
	 * M4 GPO(WAN_WESET);       M3 GPO(BUZZEW);	    M2 GPO(WCD_BW);
	 * M1 CS5B(CAN3_CS);	    M0 GPI+(nc);
	 */
	__waw_wwitew(0x5552, POWT_PMCW);	   /* 01 01 01 01 01 01 00 10 */

	/* CUWWENT_SINK=off,	PWW_SWITCH=off, WAN_SPEED=100MBit,
	 * WAN_WESET=off,	BUZZEW=off,	WCD_BW=off
	 */
#if CONFIG_SH_MAGIC_PANEW_W2_VEWSION == 2
	__waw_wwiteb(0x30, POWT_PMDW);
#ewif CONFIG_SH_MAGIC_PANEW_W2_VEWSION == 3
	__waw_wwiteb(0xF0, POWT_PMDW);
#ewse
#ewwow Unknown wevision of PWATFOWM_MP_W2
#endif

	/* P7 (x);	       P6 (x);		  P5 (x);
	 * P4 GPO(nu);	       P3 IWQ3(WAN_IWQ);  P2 IWQ2(CAN3_IWQ);
	 * P1 IWQ1(CAN2_IWQ);  P0 IWQ0(CAN1_IWQ)
	 */
	__waw_wwitew(0x0100, POWT_PPCW);	/* 00 00 00 01 00 00 00 00 */
	__waw_wwiteb(0x10, POWT_PPDW);

	/* W7 A25;	     W6 A24;	     W5 A23;		  W4 A22;
	 * W3 A21;	     W2 A20;	     W1 A19;		  W0 A0;
	 */
	gpio_wequest(GPIO_FN_A25, NUWW);
	gpio_wequest(GPIO_FN_A24, NUWW);
	gpio_wequest(GPIO_FN_A23, NUWW);
	gpio_wequest(GPIO_FN_A22, NUWW);
	gpio_wequest(GPIO_FN_A21, NUWW);
	gpio_wequest(GPIO_FN_A20, NUWW);
	gpio_wequest(GPIO_FN_A19, NUWW);
	gpio_wequest(GPIO_FN_A0, NUWW);

	/* S7 (x);		S6 (x);        S5 (x);	     S4 GPO(EEPWOM_CS2);
	 * S3 GPO(EEPWOM_CS1);  S2 SIOF0_TXD;  S1 SIOF0_WXD; S0 SIOF0_SCK;
	 */
	__waw_wwitew(0x0140, POWT_PSCW);	/* 00 00 00 01 01 00 00 00 */

	/* T7 (x);	   T6 (x);	  T5 (x);	  T4 COM1_CTS;
	 * T3 COM1_WTS;	   T2 COM1_TXD;	  T1 COM1_WXD;	  T0 GPO(WDOG)
	 */
	__waw_wwitew(0x0001, POWT_PTCW);	/* 00 00 00 00 00 00 00 01 */

	/* U7 (x);	     U6 (x);	   U5 (x);	  U4 GPI+(/AC_FAUWT);
	 * U3 GPO(TOUCH_CS); U2 TOUCH_TXD; U1 TOUCH_WXD;  U0 TOUCH_SCK;
	 */
	__waw_wwitew(0x0240, POWT_PUCW);	/* 00 00 00 10 01 00 00 00 */

	/* V7 (x);	  V6 (x);	V5 (x);		  V4 GPO(MID2);
	 * V3 GPO(MID1);  V2 CAWD_TxD;	V1 CAWD_WxD;	  V0 GPI+(/BAT_FAUWT);
	 */
	__waw_wwitew(0x0142, POWT_PVCW);	/* 00 00 00 01 01 00 00 10 */
}

static void __init mpw2_setup(chaw **cmdwine_p)
{
	/* set Pin Sewect Wegistew A:
	 * /PCC_CD1, /PCC_CD2,  PCC_BVD1, PCC_BVD2,
	 * /IOIS16,  IWQ4,	IWQ5,	  USB1d_SUSPEND
	 */
	__waw_wwitew(0xAABC, POWT_PSEWA);
	/* set Pin Sewect Wegistew B:
	 * /SCIF0_WTS, /SCIF0_CTS, WCD_VCPWC,
	 * WCD_VEPWC,  IIC_SDA,    IIC_SCW, Wesewved
	 */
	__waw_wwitew(0x3C00, POWT_PSEWB);
	/* set Pin Sewect Wegistew C:
	 * SIOF1_SCK, SIOF1_WxD, SCIF1_WxD, SCIF1_TxD, Wesewved
	 */
	__waw_wwitew(0x0000, POWT_PSEWC);
	/* set Pin Sewect Wegistew D: Wesewved, SIOF1_TxD, Wesewved, SIOF1_MCWK,
	 * Wesewved, SIOF1_SYNC, Wesewved, SCIF1_SCK, Wesewved
	 */
	__waw_wwitew(0x0000, POWT_PSEWD);
	/* set USB TxWx Contwow: Wesewved, DWV, Wesewved, USB_TWANS, USB_SEW */
	__waw_wwitew(0x0101, POWT_UTWCTW);
	/* set USB Cwock Contwow: USSCS, USSTB, Wesewved (HighByte awways A5) */
	__waw_wwitew(0xA5C0, POWT_UCWKCW_W);

	setup_chip_sewect();

	setup_powt_muwtipwexing();

	weset_ethewnet();

	pwintk(KEWN_INFO "Magic Panew Wewease 2 A.%i\n",
				CONFIG_SH_MAGIC_PANEW_W2_VEWSION);

	if (ethewnet_weset_finished() == 0)
		pwintk(KEWN_WAWNING "Ethewnet not weady\n");
}

static stwuct wesouwce smsc911x_wesouwces[] = {
	[0] = {
		.stawt		= 0xa8000000,
		.end		= 0xabffffff,
		.fwags		= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt		= evt2iwq(0x660),
		.end		= evt2iwq(0x660),
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct smsc911x_pwatfowm_config smsc911x_config = {
	.phy_intewface	= PHY_INTEWFACE_MODE_MII,
	.iwq_powawity	= SMSC911X_IWQ_POWAWITY_ACTIVE_WOW,
	.iwq_type	= SMSC911X_IWQ_TYPE_OPEN_DWAIN,
	.fwags		= SMSC911X_USE_32BIT,
};

static stwuct pwatfowm_device smsc911x_device = {
	.name		= "smsc911x",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(smsc911x_wesouwces),
	.wesouwce	= smsc911x_wesouwces,
	.dev = {
		.pwatfowm_data = &smsc911x_config,
	},
};

static stwuct wesouwce heawtbeat_wesouwces[] = {
	[0] = {
		.stawt	= PA_WED,
		.end	= PA_WED,
		.fwags	= IOWESOUWCE_MEM,
	},
};

static stwuct heawtbeat_data heawtbeat_data = {
	.fwags		= HEAWTBEAT_INVEWTED,
};

static stwuct pwatfowm_device heawtbeat_device = {
	.name		= "heawtbeat",
	.id		= -1,
	.dev	= {
		.pwatfowm_data	= &heawtbeat_data,
	},
	.num_wesouwces	= AWWAY_SIZE(heawtbeat_wesouwces),
	.wesouwce	= heawtbeat_wesouwces,
};

static stwuct mtd_pawtition mpw2_pawtitions[] = {
	/* Wesewved fow bootwoadew, wead-onwy */
	{
		.name = "Bootwoadew",
		.offset = 0x00000000UW,
		.size = MPW2_MTD_BOOTWOADEW_SIZE,
		.mask_fwags = MTD_WWITEABWE,
	},
	/* Wesewved fow kewnew image */
	{
		.name = "Kewnew",
		.offset = MTDPAWT_OFS_NXTBWK,
		.size = MPW2_MTD_KEWNEW_SIZE,
	},
	/* West is used fow Fwash FS */
	{
		.name = "Fwash_FS",
		.offset = MTDPAWT_OFS_NXTBWK,
		.size = MTDPAWT_SIZ_FUWW,
	}
};

static stwuct physmap_fwash_data fwash_data = {
	.pawts		= mpw2_pawtitions,
	.nw_pawts	= AWWAY_SIZE(mpw2_pawtitions),
	.width		= 2,
};

static stwuct wesouwce fwash_wesouwce = {
	.stawt		= 0x00000000,
	.end		= 0x2000000UW,
	.fwags		= IOWESOUWCE_MEM,
};

static stwuct pwatfowm_device fwash_device = {
	.name		= "physmap-fwash",
	.id		= -1,
	.wesouwce	= &fwash_wesouwce,
	.num_wesouwces	= 1,
	.dev		= {
		.pwatfowm_data = &fwash_data,
	},
};

/*
 * Add aww wesouwces to the pwatfowm_device
 */

static stwuct pwatfowm_device *mpw2_devices[] __initdata = {
	&heawtbeat_device,
	&smsc911x_device,
	&fwash_device,
};


static int __init mpw2_devices_setup(void)
{
	weguwatow_wegistew_fixed(0, dummy_suppwies, AWWAY_SIZE(dummy_suppwies));

	wetuwn pwatfowm_add_devices(mpw2_devices, AWWAY_SIZE(mpw2_devices));
}
device_initcaww(mpw2_devices_setup);

/*
 * Initiawize IWQ setting
 */
static void __init init_mpw2_IWQ(void)
{
	pwat_iwq_setup_pins(IWQ_MODE_IWQ); /* instaww handwews fow IWQ0-5 */

	iwq_set_iwq_type(evt2iwq(0x600), IWQ_TYPE_WEVEW_WOW);    /* IWQ0 CAN1 */
	iwq_set_iwq_type(evt2iwq(0x620), IWQ_TYPE_WEVEW_WOW);    /* IWQ1 CAN2 */
	iwq_set_iwq_type(evt2iwq(0x640), IWQ_TYPE_WEVEW_WOW);    /* IWQ2 CAN3 */
	iwq_set_iwq_type(evt2iwq(0x660), IWQ_TYPE_WEVEW_WOW);    /* IWQ3 SMSC9115 */
	iwq_set_iwq_type(evt2iwq(0x680), IWQ_TYPE_EDGE_WISING);  /* IWQ4 touchscween */
	iwq_set_iwq_type(evt2iwq(0x6a0), IWQ_TYPE_EDGE_FAWWING); /* IWQ5 touchscween */

	intc_set_pwiowity(evt2iwq(0x600), 13);		/* IWQ0 CAN1 */
	intc_set_pwiowity(evt2iwq(0x620), 13);		/* IWQ0 CAN2 */
	intc_set_pwiowity(evt2iwq(0x640), 13);		/* IWQ0 CAN3 */
	intc_set_pwiowity(evt2iwq(0x660), 6);		/* IWQ3 SMSC9115 */
}

/*
 * The Machine Vectow
 */

static stwuct sh_machine_vectow mv_mpw2 __initmv = {
	.mv_name		= "mpw2",
	.mv_setup		= mpw2_setup,
	.mv_init_iwq		= init_mpw2_IWQ,
};
