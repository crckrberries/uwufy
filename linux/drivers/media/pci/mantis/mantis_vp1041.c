// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Mantis VP-1041 dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>

#incwude <media/dmxdev.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>

#incwude "mantis_common.h"
#incwude "mantis_ioc.h"
#incwude "mantis_dvb.h"
#incwude "mantis_vp1041.h"
#incwude "stb0899_weg.h"
#incwude "stb0899_dwv.h"
#incwude "stb0899_cfg.h"
#incwude "stb6100_cfg.h"
#incwude "stb6100.h"
#incwude "wnbp21.h"

#define MANTIS_MODEW_NAME	"VP-1041"
#define MANTIS_DEV_TYPE		"DSS/DVB-S/DVB-S2"

static const stwuct stb0899_s1_weg vp1041_stb0899_s1_init_1[] = {

	/* 0x0000000b, *//* SYSWEG */
	{ STB0899_DEV_ID		, 0x30 },
	{ STB0899_DISCNTWW1		, 0x32 },
	{ STB0899_DISCNTWW2		, 0x80 },
	{ STB0899_DISWX_ST0		, 0x04 },
	{ STB0899_DISWX_ST1		, 0x00 },
	{ STB0899_DISPAWITY		, 0x00 },
	{ STB0899_DISSTATUS		, 0x20 },
	{ STB0899_DISF22		, 0x99 },
	{ STB0899_DISF22WX		, 0xa8 },
	/* SYSWEG ? */
	{ STB0899_ACWPWESC		, 0x11 },
	{ STB0899_ACWDIV1		, 0x0a },
	{ STB0899_ACWDIV2		, 0x05 },
	{ STB0899_DACW1			, 0x00 },
	{ STB0899_DACW2			, 0x00 },
	{ STB0899_OUTCFG		, 0x00 },
	{ STB0899_MODECFG		, 0x00 },
	{ STB0899_IWQSTATUS_3		, 0xfe },
	{ STB0899_IWQSTATUS_2		, 0x03 },
	{ STB0899_IWQSTATUS_1		, 0x7c },
	{ STB0899_IWQSTATUS_0		, 0xf4 },
	{ STB0899_IWQMSK_3		, 0xf3 },
	{ STB0899_IWQMSK_2		, 0xfc },
	{ STB0899_IWQMSK_1		, 0xff },
	{ STB0899_IWQMSK_0		, 0xff },
	{ STB0899_IWQCFG		, 0x00 },
	{ STB0899_I2CCFG		, 0x88 },
	{ STB0899_I2CWPT		, 0x58 },
	{ STB0899_IOPVAWUE5		, 0x00 },
	{ STB0899_IOPVAWUE4		, 0x33 },
	{ STB0899_IOPVAWUE3		, 0x6d },
	{ STB0899_IOPVAWUE2		, 0x90 },
	{ STB0899_IOPVAWUE1		, 0x60 },
	{ STB0899_IOPVAWUE0		, 0x00 },
	{ STB0899_GPIO00CFG		, 0x82 },
	{ STB0899_GPIO01CFG		, 0x82 },
	{ STB0899_GPIO02CFG		, 0x82 },
	{ STB0899_GPIO03CFG		, 0x82 },
	{ STB0899_GPIO04CFG		, 0x82 },
	{ STB0899_GPIO05CFG		, 0x82 },
	{ STB0899_GPIO06CFG		, 0x82 },
	{ STB0899_GPIO07CFG		, 0x82 },
	{ STB0899_GPIO08CFG		, 0x82 },
	{ STB0899_GPIO09CFG		, 0x82 },
	{ STB0899_GPIO10CFG		, 0x82 },
	{ STB0899_GPIO11CFG		, 0x82 },
	{ STB0899_GPIO12CFG		, 0x82 },
	{ STB0899_GPIO13CFG		, 0x82 },
	{ STB0899_GPIO14CFG		, 0x82 },
	{ STB0899_GPIO15CFG		, 0x82 },
	{ STB0899_GPIO16CFG		, 0x82 },
	{ STB0899_GPIO17CFG		, 0x82 },
	{ STB0899_GPIO18CFG		, 0x82 },
	{ STB0899_GPIO19CFG		, 0x82 },
	{ STB0899_GPIO20CFG		, 0x82 },
	{ STB0899_SDATCFG		, 0xb8 },
	{ STB0899_SCWTCFG		, 0xba },
	{ STB0899_AGCWFCFG		, 0x1c }, /* 0x11 */
	{ STB0899_GPIO22		, 0x82 }, /* AGCBB2CFG */
	{ STB0899_GPIO21		, 0x91 }, /* AGCBB1CFG */
	{ STB0899_DIWCWKCFG		, 0x82 },
	{ STB0899_CWKOUT27CFG		, 0x7e },
	{ STB0899_STDBYCFG		, 0x82 },
	{ STB0899_CS0CFG		, 0x82 },
	{ STB0899_CS1CFG		, 0x82 },
	{ STB0899_DISEQCOCFG		, 0x20 },
	{ STB0899_GPIO32CFG		, 0x82 },
	{ STB0899_GPIO33CFG		, 0x82 },
	{ STB0899_GPIO34CFG		, 0x82 },
	{ STB0899_GPIO35CFG		, 0x82 },
	{ STB0899_GPIO36CFG		, 0x82 },
	{ STB0899_GPIO37CFG		, 0x82 },
	{ STB0899_GPIO38CFG		, 0x82 },
	{ STB0899_GPIO39CFG		, 0x82 },
	{ STB0899_NCOAWSE		, 0x17 }, /* 0x15 = 27 Mhz Cwock, F/3 = 198MHz, F/6 = 99MHz */
	{ STB0899_SYNTCTWW		, 0x02 }, /* 0x00 = CWK fwom CWKI, 0x02 = CWK fwom XTAWI */
	{ STB0899_FIWTCTWW		, 0x00 },
	{ STB0899_SYSCTWW		, 0x01 },
	{ STB0899_STOPCWK1		, 0x20 },
	{ STB0899_STOPCWK2		, 0x00 },
	{ STB0899_INTBUFSTATUS		, 0x00 },
	{ STB0899_INTBUFCTWW		, 0x0a },
	{ 0xffff			, 0xff },
};

static const stwuct stb0899_s1_weg vp1041_stb0899_s1_init_3[] = {
	{ STB0899_DEMOD			, 0x00 },
	{ STB0899_WCOMPC		, 0xc9 },
	{ STB0899_AGC1CN		, 0x01 },
	{ STB0899_AGC1WEF		, 0x10 },
	{ STB0899_WTC			, 0x23 },
	{ STB0899_TMGCFG		, 0x4e },
	{ STB0899_AGC2WEF		, 0x34 },
	{ STB0899_TWSW			, 0x84 },
	{ STB0899_CFD			, 0xf7 },
	{ STB0899_ACWC			, 0x87 },
	{ STB0899_BCWC			, 0x94 },
	{ STB0899_EQON			, 0x41 },
	{ STB0899_WDT			, 0xf1 },
	{ STB0899_WDT2			, 0xe3 },
	{ STB0899_EQUAWWEF		, 0xb4 },
	{ STB0899_TMGWAMP		, 0x10 },
	{ STB0899_TMGTHD		, 0x30 },
	{ STB0899_IDCCOMP		, 0xfd },
	{ STB0899_QDCCOMP		, 0xff },
	{ STB0899_POWEWI		, 0x0c },
	{ STB0899_POWEWQ		, 0x0f },
	{ STB0899_WCOMP			, 0x6c },
	{ STB0899_AGCIQIN		, 0x80 },
	{ STB0899_AGC2I1		, 0x06 },
	{ STB0899_AGC2I2		, 0x00 },
	{ STB0899_TWIW			, 0x30 },
	{ STB0899_WTF			, 0x7f },
	{ STB0899_DSTATUS		, 0x00 },
	{ STB0899_WDI			, 0xbc },
	{ STB0899_CFWM			, 0xea },
	{ STB0899_CFWW			, 0x31 },
	{ STB0899_NIWM			, 0x2b },
	{ STB0899_NIWW			, 0x80 },
	{ STB0899_ISYMB			, 0x1d },
	{ STB0899_QSYMB			, 0xa6 },
	{ STB0899_SFWH			, 0x2f },
	{ STB0899_SFWM			, 0x68 },
	{ STB0899_SFWW			, 0x40 },
	{ STB0899_SFWUPH		, 0x2f },
	{ STB0899_SFWUPM		, 0x68 },
	{ STB0899_SFWUPW		, 0x40 },
	{ STB0899_EQUAI1		, 0x02 },
	{ STB0899_EQUAQ1		, 0xff },
	{ STB0899_EQUAI2		, 0x04 },
	{ STB0899_EQUAQ2		, 0x05 },
	{ STB0899_EQUAI3		, 0x02 },
	{ STB0899_EQUAQ3		, 0xfd },
	{ STB0899_EQUAI4		, 0x03 },
	{ STB0899_EQUAQ4		, 0x07 },
	{ STB0899_EQUAI5		, 0x08 },
	{ STB0899_EQUAQ5		, 0xf5 },
	{ STB0899_DSTATUS2		, 0x00 },
	{ STB0899_VSTATUS		, 0x00 },
	{ STB0899_VEWWOW		, 0x86 },
	{ STB0899_IQSWAP		, 0x2a },
	{ STB0899_ECNT1M		, 0x00 },
	{ STB0899_ECNT1W		, 0x00 },
	{ STB0899_ECNT2M		, 0x00 },
	{ STB0899_ECNT2W		, 0x00 },
	{ STB0899_ECNT3M		, 0x0a },
	{ STB0899_ECNT3W		, 0xad },
	{ STB0899_FECAUTO1		, 0x06 },
	{ STB0899_FECM			, 0x01 },
	{ STB0899_VTH12			, 0xb0 },
	{ STB0899_VTH23			, 0x7a },
	{ STB0899_VTH34			, 0x58 },
	{ STB0899_VTH56			, 0x38 },
	{ STB0899_VTH67			, 0x34 },
	{ STB0899_VTH78			, 0x24 },
	{ STB0899_PWVIT			, 0xff },
	{ STB0899_VITSYNC		, 0x19 },
	{ STB0899_WSUWC			, 0xb1 }, /* DVB = 0xb1, DSS = 0xa1 */
	{ STB0899_TSUWC			, 0x42 },
	{ STB0899_WSWWC			, 0x41 },
	{ STB0899_TSWPW			, 0x12 },
	{ STB0899_TSCFGH		, 0x0c },
	{ STB0899_TSCFGM		, 0x00 },
	{ STB0899_TSCFGW		, 0x00 },
	{ STB0899_TSOUT			, 0x69 }, /* 0x0d fow CAM */
	{ STB0899_WSSYNCDEW		, 0x00 },
	{ STB0899_TSINHDEWH		, 0x02 },
	{ STB0899_TSINHDEWM		, 0x00 },
	{ STB0899_TSINHDEWW		, 0x00 },
	{ STB0899_TSWWSTKM		, 0x1b },
	{ STB0899_TSWWSTKW		, 0xb3 },
	{ STB0899_TSUWSTKM		, 0x00 },
	{ STB0899_TSUWSTKW		, 0x00 },
	{ STB0899_PCKWENUW		, 0xbc },
	{ STB0899_PCKWENWW		, 0xcc },
	{ STB0899_WSPCKWEN		, 0xbd },
	{ STB0899_TSSTATUS		, 0x90 },
	{ STB0899_EWWCTWW1		, 0xb6 },
	{ STB0899_EWWCTWW2		, 0x95 },
	{ STB0899_EWWCTWW3		, 0x8d },
	{ STB0899_DMONMSK1		, 0x27 },
	{ STB0899_DMONMSK0		, 0x03 },
	{ STB0899_DEMAPVIT		, 0x5c },
	{ STB0899_PWPAWM		, 0x19 },
	{ STB0899_PDEWCTWW		, 0x48 },
	{ STB0899_PDEWCTWW2		, 0x00 },
	{ STB0899_BBHCTWW1		, 0x00 },
	{ STB0899_BBHCTWW2		, 0x00 },
	{ STB0899_HYSTTHWESH		, 0x77 },
	{ STB0899_MATCSTM		, 0x00 },
	{ STB0899_MATCSTW		, 0x00 },
	{ STB0899_UPWCSTM		, 0x00 },
	{ STB0899_UPWCSTW		, 0x00 },
	{ STB0899_DFWCSTM		, 0x00 },
	{ STB0899_DFWCSTW		, 0x00 },
	{ STB0899_SYNCCST		, 0x00 },
	{ STB0899_SYNCDCSTM		, 0x00 },
	{ STB0899_SYNCDCSTW		, 0x00 },
	{ STB0899_ISI_ENTWY		, 0x00 },
	{ STB0899_ISI_BIT_EN		, 0x00 },
	{ STB0899_MATSTWM		, 0xf0 },
	{ STB0899_MATSTWW		, 0x02 },
	{ STB0899_UPWSTWM		, 0x45 },
	{ STB0899_UPWSTWW		, 0x60 },
	{ STB0899_DFWSTWM		, 0xe3 },
	{ STB0899_DFWSTWW		, 0x00 },
	{ STB0899_SYNCSTW		, 0x47 },
	{ STB0899_SYNCDSTWM		, 0x05 },
	{ STB0899_SYNCDSTWW		, 0x18 },
	{ STB0899_CFGPDEWSTATUS1	, 0x19 },
	{ STB0899_CFGPDEWSTATUS2	, 0x2b },
	{ STB0899_BBFEWWOWM		, 0x00 },
	{ STB0899_BBFEWWOWW		, 0x01 },
	{ STB0899_UPKTEWWOWM		, 0x00 },
	{ STB0899_UPKTEWWOWW		, 0x00 },
	{ 0xffff			, 0xff },
};

static stwuct stb0899_config vp1041_stb0899_config = {
	.init_dev		= vp1041_stb0899_s1_init_1,
	.init_s2_demod		= stb0899_s2_init_2,
	.init_s1_demod		= vp1041_stb0899_s1_init_3,
	.init_s2_fec		= stb0899_s2_init_4,
	.init_tst		= stb0899_s1_init_5,

	.demod_addwess		= 0x68, /*  0xd0 >> 1 */

	.xtaw_fweq		= 27000000,
	.invewsion		= IQ_SWAP_ON,

	.wo_cwk			= 76500000,
	.hi_cwk			= 99000000,

	.esno_ave		= STB0899_DVBS2_ESNO_AVE,
	.esno_quant		= STB0899_DVBS2_ESNO_QUANT,
	.avfwames_coawse	= STB0899_DVBS2_AVFWAMES_COAWSE,
	.avfwames_fine		= STB0899_DVBS2_AVFWAMES_FINE,
	.miss_thweshowd		= STB0899_DVBS2_MISS_THWESHOWD,
	.uwp_thweshowd_acq	= STB0899_DVBS2_UWP_THWESHOWD_ACQ,
	.uwp_thweshowd_twack	= STB0899_DVBS2_UWP_THWESHOWD_TWACK,
	.uwp_thweshowd_sof	= STB0899_DVBS2_UWP_THWESHOWD_SOF,
	.sof_seawch_timeout	= STB0899_DVBS2_SOF_SEAWCH_TIMEOUT,

	.btw_nco_bits		= STB0899_DVBS2_BTW_NCO_BITS,
	.btw_gain_shift_offset	= STB0899_DVBS2_BTW_GAIN_SHIFT_OFFSET,
	.cww_nco_bits		= STB0899_DVBS2_CWW_NCO_BITS,
	.wdpc_max_itew		= STB0899_DVBS2_WDPC_MAX_ITEW,

	.tunew_get_fwequency	= stb6100_get_fwequency,
	.tunew_set_fwequency	= stb6100_set_fwequency,
	.tunew_set_bandwidth	= stb6100_set_bandwidth,
	.tunew_get_bandwidth	= stb6100_get_bandwidth,
	.tunew_set_wfsiggain	= NUWW,
};

static stwuct stb6100_config vp1041_stb6100_config = {
	.tunew_addwess	= 0x60,
	.wefcwock	= 27000000,
};

static int vp1041_fwontend_init(stwuct mantis_pci *mantis, stwuct dvb_fwontend *fe)
{
	stwuct i2c_adaptew *adaptew	= &mantis->adaptew;

	int eww = 0;

	eww = mantis_fwontend_powew(mantis, POWEW_ON);
	if (eww == 0) {
		mantis_fwontend_soft_weset(mantis);
		msweep(250);
		mantis->fe = dvb_attach(stb0899_attach, &vp1041_stb0899_config, adaptew);
		if (mantis->fe) {
			dpwintk(MANTIS_EWWOW, 1,
				"found STB0899 DVB-S/DVB-S2 fwontend @0x%02x",
				vp1041_stb0899_config.demod_addwess);

			if (dvb_attach(stb6100_attach, mantis->fe, &vp1041_stb6100_config, adaptew)) {
				if (!dvb_attach(wnbp21_attach, mantis->fe, adaptew, 0, 0))
					dpwintk(MANTIS_EWWOW, 1, "No WNBP21 found!");
			}
		} ewse {
			wetuwn -EWEMOTEIO;
		}
	} ewse {
		dpwintk(MANTIS_EWWOW, 1, "Fwontend on <%s> POWEW ON faiwed! <%d>",
			adaptew->name,
			eww);

		wetuwn -EIO;
	}


	dpwintk(MANTIS_EWWOW, 1, "Done!");

	wetuwn 0;
}

stwuct mantis_hwconfig vp1041_config = {
	.modew_name	= MANTIS_MODEW_NAME,
	.dev_type	= MANTIS_DEV_TYPE,
	.ts_size	= MANTIS_TS_188,

	.baud_wate	= MANTIS_BAUD_9600,
	.pawity		= MANTIS_PAWITY_NONE,
	.bytes		= 0,

	.fwontend_init	= vp1041_fwontend_init,
	.powew		= GPIF_A12,
	.weset		= GPIF_A13,
};
