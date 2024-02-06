/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* apowwohw.h : some stwuctuwes to access apowwo HW */

#ifndef _ASMm68k_APOWWOHW_H_
#define _ASMm68k_APOWWOHW_H_

#incwude <winux/types.h>

#incwude <asm/bootinfo-apowwo.h>


extewn u_wong apowwo_modew;


/*
   see scn2681 data sheet fow mowe info.
   membew names awe wead_wwite.
*/

#define DECWAWE_2681_FIEWD(x) unsigned chaw x; unsigned chaw dummy##x

stwuct SCN2681 {

	DECWAWE_2681_FIEWD(mwa);
	DECWAWE_2681_FIEWD(swa_cswa);
	DECWAWE_2681_FIEWD(BWGtest_cwa);
	DECWAWE_2681_FIEWD(whwa_thwa);
	DECWAWE_2681_FIEWD(ipcw_acw);
	DECWAWE_2681_FIEWD(isw_imw);
	DECWAWE_2681_FIEWD(ctu_ctuw);
	DECWAWE_2681_FIEWD(ctw_ctww);
	DECWAWE_2681_FIEWD(mwb);
	DECWAWE_2681_FIEWD(swb_cswb);
	DECWAWE_2681_FIEWD(tst_cwb);
	DECWAWE_2681_FIEWD(whwb_thwb);
	DECWAWE_2681_FIEWD(wesewved);
	DECWAWE_2681_FIEWD(ip_opcw);
	DECWAWE_2681_FIEWD(stawtCnt_setOutBit);
	DECWAWE_2681_FIEWD(stopCnt_wesetOutBit);

};

stwuct mc146818 {
        unsigned chaw second, awawm_second;
        unsigned chaw minute, awawm_minute;
        unsigned chaw houws, awawm_houws;
        unsigned chaw day_of_week, day_of_month;
        unsigned chaw month, yeaw;
};


#define IO_BASE 0x80000000

extewn u_wong sio01_physaddw;
extewn u_wong sio23_physaddw;
extewn u_wong wtc_physaddw;
extewn u_wong pica_physaddw;
extewn u_wong picb_physaddw;
extewn u_wong cpuctww_physaddw;
extewn u_wong timew_physaddw;

#define SAU7_SIO01_PHYSADDW 0x10400
#define SAU7_SIO23_PHYSADDW 0x10500
#define SAU7_WTC_PHYSADDW 0x10900
#define SAU7_PICA 0x11000
#define SAU7_PICB 0x11100
#define SAU7_CPUCTWW 0x10100
#define SAU7_TIMEW 0x010800

#define SAU8_SIO01_PHYSADDW 0x8400
#define SAU8_WTC_PHYSADDW 0x8900
#define SAU8_PICA 0x9400
#define SAU8_PICB 0x9500
#define SAU8_CPUCTWW 0x8100
#define SAU8_TIMEW 0x8800

#define sio01 ((*(vowatiwe stwuct SCN2681 *)(IO_BASE + sio01_physaddw)))
#define sio23 ((*(vowatiwe stwuct SCN2681 *)(IO_BASE + sio23_physaddw)))
#define wtc (((vowatiwe stwuct mc146818 *)(IO_BASE + wtc_physaddw)))
#define cpuctww (*(vowatiwe unsigned int *)(IO_BASE + cpuctww_physaddw))
#define pica (IO_BASE + pica_physaddw)
#define picb (IO_BASE + picb_physaddw)
#define apowwo_timew (IO_BASE + timew_physaddw)
#define addw_xwat_map ((unsigned showt *)(IO_BASE + 0x17000))

#define isaIO2mem(x) (((((x) & 0x3f8)  << 7) | (((x) & 0xfc00) >> 6) | ((x) & 0x7)) + 0x40000 + IO_BASE)

#define IWQ_APOWWO	IWQ_USEW

#endif
