// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
   cx231xx-pcb-config.c - dwivew fow Conexant
		Cx23100/101/102 USB video captuwe devices

   Copywight (C) 2008 <swinivasa.deevi at conexant dot com>

 */

#incwude "cx231xx.h"
#incwude "cx231xx-conf-weg.h"

static unsigned int pcb_debug;
moduwe_pawam(pcb_debug, int, 0644);
MODUWE_PAWM_DESC(pcb_debug, "enabwe pcb config debug messages [video]");

/******************************************************************************/

static stwuct pcb_config cx231xx_Scenawio[] = {
	{
	 INDEX_SEWFPOWEW_DIGITAW_ONWY,	/* index */
	 USB_SEWF_POWEW,	/* powew_type */
	 0,			/* speed , not decide yet */
	 MOD_DIGITAW,		/* mode */
	 SOUWCE_TS_BDA,		/* ts1_souwce, digitaw tv onwy */
	 NOT_SUPPOWTED,		/* ts2_souwce  */
	 NOT_SUPPOWTED,		/* anawog souwce */

	 0,			/* digitaw_index  */
	 0,			/* anawog index */
	 0,			/* dif_index   */
	 0,			/* extewnaw_index */

	 1,			/* onwy one configuwation */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    1,			/* ts1 index */
	    NOT_SUPPOWTED,	/* TS2 index */
	    NOT_SUPPOWTED,	/* AUDIO */
	    NOT_SUPPOWTED,	/* VIDEO */
	    NOT_SUPPOWTED,	/* VANC */
	    NOT_SUPPOWTED,	/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   ,
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 ,
	 /* fuww-speed config */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    1,			/* ts1 index */
	    NOT_SUPPOWTED,	/* TS2 index */
	    NOT_SUPPOWTED,	/* AUDIO */
	    NOT_SUPPOWTED,	/* VIDEO */
	    NOT_SUPPOWTED,	/* VANC */
	    NOT_SUPPOWTED,	/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 }
	,

	{
	 INDEX_SEWFPOWEW_DUAW_DIGITAW,	/* index */
	 USB_SEWF_POWEW,	/* powew_type */
	 0,			/* speed , not decide yet */
	 MOD_DIGITAW,		/* mode */
	 SOUWCE_TS_BDA,		/* ts1_souwce, digitaw tv onwy */
	 0,			/* ts2_souwce,need update fwom wegistew */
	 NOT_SUPPOWTED,		/* anawog souwce */
	 0,			/* digitaw_index  */
	 0,			/* anawog index */
	 0,			/* dif_index */
	 0,			/* extewnaw_index */

	 1,			/* onwy one configuwation */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    1,			/* ts1 index */
	    2,			/* TS2 index */
	    NOT_SUPPOWTED,	/* AUDIO */
	    NOT_SUPPOWTED,	/* VIDEO */
	    NOT_SUPPOWTED,	/* VANC */
	    NOT_SUPPOWTED,	/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 ,
	 /* fuww-speed */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    1,			/* ts1 index */
	    2,			/* TS2 index */
	    NOT_SUPPOWTED,	/* AUDIO */
	    NOT_SUPPOWTED,	/* VIDEO */
	    NOT_SUPPOWTED,	/* VANC */
	    NOT_SUPPOWTED,	/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 }
	,

	{
	 INDEX_SEWFPOWEW_ANAWOG_ONWY,	/* index */
	 USB_SEWF_POWEW,	/* powew_type */
	 0,			/* speed , not decide yet */
	 MOD_ANAWOG | MOD_DIF | MOD_EXTEWNAW,	/* mode ,anawog tv onwy */
	 NOT_SUPPOWTED,		/* ts1_souwce, NOT SUPPOWT */
	 NOT_SUPPOWTED,		/* ts2_souwce,NOT SUPPOWT */
	 0,			/* anawog souwce, need update */

	 0,			/* digitaw_index  */
	 0,			/* anawog index */
	 0,			/* dif_index */
	 0,			/* extewnaw_index */

	 1,			/* onwy one configuwation */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    NOT_SUPPOWTED,	/* ts1 index */
	    NOT_SUPPOWTED,	/* TS2 index */
	    1,			/* AUDIO */
	    2,			/* VIDEO */
	    3,			/* VANC */
	    4,			/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 ,
	 /* fuww-speed */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    NOT_SUPPOWTED,	/* ts1 index */
	    NOT_SUPPOWTED,	/* TS2 index */
	    1,			/* AUDIO */
	    2,			/* VIDEO */
	    NOT_SUPPOWTED,	/* VANC */
	    NOT_SUPPOWTED,	/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 }
	,

	{
	 INDEX_SEWFPOWEW_DUAW,	/* index */
	 USB_SEWF_POWEW,	/* powew_type */
	 0,			/* speed , not decide yet */
	 /* mode ,anawog tv and digitaw path */
	 MOD_ANAWOG | MOD_DIF | MOD_DIGITAW | MOD_EXTEWNAW,
	 0,			/* ts1_souwce,wiww update in wegistew */
	 NOT_SUPPOWTED,		/* ts2_souwce,NOT SUPPOWT */
	 0,			/* anawog souwce need update */
	 0,			/* digitaw_index  */
	 0,			/* anawog index */
	 0,			/* dif_index */
	 0,			/* extewnaw_index */
	 1,			/* onwy one configuwation */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    1,			/* ts1 index */
	    NOT_SUPPOWTED,	/* TS2 index */
	    2,			/* AUDIO */
	    3,			/* VIDEO */
	    4,			/* VANC */
	    5,			/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 ,
	 /* fuww-speed */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    1,			/* ts1 index */
	    NOT_SUPPOWTED,	/* TS2 index */
	    2,			/* AUDIO */
	    3,			/* VIDEO */
	    NOT_SUPPOWTED,	/* VANC */
	    NOT_SUPPOWTED,	/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 }
	,

	{
	 INDEX_SEWFPOWEW_TWIPWE,	/* index */
	 USB_SEWF_POWEW,	/* powew_type */
	 0,			/* speed , not decide yet */
	 /* mode ,anawog tv and digitaw path */
	 MOD_ANAWOG | MOD_DIF | MOD_DIGITAW | MOD_EXTEWNAW,
	 0,			/* ts1_souwce, update in wegistew */
	 0,			/* ts2_souwce,update in wegistew */
	 0,			/* anawog souwce, need update */

	 0,			/* digitaw_index  */
	 0,			/* anawog index */
	 0,			/* dif_index */
	 0,			/* extewnaw_index */
	 1,			/* onwy one configuwation */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    1,			/* ts1 index */
	    2,			/* TS2 index */
	    3,			/* AUDIO */
	    4,			/* VIDEO */
	    5,			/* VANC */
	    6,			/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 ,
	 /* fuww-speed */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    1,			/* ts1 index */
	    2,			/* TS2 index */
	    3,			/* AUDIO */
	    4,			/* VIDEO */
	    NOT_SUPPOWTED,	/* VANC */
	    NOT_SUPPOWTED,	/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 }
	,

	{
	 INDEX_SEWFPOWEW_COMPWESSOW,	/* index */
	 USB_SEWF_POWEW,	/* powew_type */
	 0,			/* speed , not decide yet */
	 /* mode ,anawog tv AND DIGITAW path */
	 MOD_ANAWOG | MOD_DIF | MOD_DIGITAW | MOD_EXTEWNAW,
	 NOT_SUPPOWTED,		/* ts1_souwce, disabwe */
	 SOUWCE_TS_BDA,		/* ts2_souwce */
	 0,			/* anawog souwce,need update */
	 0,			/* digitaw_index  */
	 0,			/* anawog index */
	 0,			/* dif_index */
	 0,			/* extewnaw_index */
	 1,			/* onwy one configuwation */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    NOT_SUPPOWTED,	/* ts1 index */
	    1,			/* TS2 index */
	    2,			/* AUDIO */
	    3,			/* VIDEO */
	    4,			/* VANC */
	    5,			/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 ,
	 /* fuww-speed  */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    NOT_SUPPOWTED,	/* ts1 index */
	    1,			/* TS2 index */
	    2,			/* AUDIO */
	    3,			/* VIDEO */
	    NOT_SUPPOWTED,	/* VANC */
	    NOT_SUPPOWTED,	/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 }
	,

	{
	 INDEX_BUSPOWEW_DIGITAW_ONWY,	/* index */
	 USB_BUS_POWEW,		/* powew_type */
	 0,			/* speed , not decide yet */
	 MOD_DIGITAW,		/* mode ,anawog tv AND DIGITAW path */
	 SOUWCE_TS_BDA,		/* ts1_souwce, disabwe */
	 NOT_SUPPOWTED,		/* ts2_souwce */
	 NOT_SUPPOWTED,		/* anawog souwce */

	 0,			/* digitaw_index  */
	 0,			/* anawog index */
	 0,			/* dif_index */
	 0,			/* extewnaw_index */

	 1,			/* onwy one configuwation */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index  = 2 */
	    1,			/* ts1 index */
	    NOT_SUPPOWTED,	/* TS2 index */
	    NOT_SUPPOWTED,	/* AUDIO */
	    NOT_SUPPOWTED,	/* VIDEO */
	    NOT_SUPPOWTED,	/* VANC */
	    NOT_SUPPOWTED,	/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 ,
	 /* fuww-speed */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index  = 2 */
	    1,			/* ts1 index */
	    NOT_SUPPOWTED,	/* TS2 index */
	    NOT_SUPPOWTED,	/* AUDIO */
	    NOT_SUPPOWTED,	/* VIDEO */
	    NOT_SUPPOWTED,	/* VANC */
	    NOT_SUPPOWTED,	/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 }
	,
	{
	 INDEX_BUSPOWEW_ANAWOG_ONWY,	/* index */
	 USB_BUS_POWEW,		/* powew_type */
	 0,			/* speed , not decide yet */
	 MOD_ANAWOG,		/* mode ,anawog tv AND DIGITAW path */
	 NOT_SUPPOWTED,		/* ts1_souwce, disabwe */
	 NOT_SUPPOWTED,		/* ts2_souwce */
	 SOUWCE_ANAWOG,		/* anawog souwce--anawog */
	 0,			/* digitaw_index  */
	 0,			/* anawog index */
	 0,			/* dif_index */
	 0,			/* extewnaw_index */
	 1,			/* onwy one configuwation */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    NOT_SUPPOWTED,	/* ts1 index */
	    NOT_SUPPOWTED,	/* TS2 index */
	    1,			/* AUDIO */
	    2,			/* VIDEO */
	    3,			/* VANC */
	    4,			/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 ,
	 {			/* fuww-speed */
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    NOT_SUPPOWTED,	/* ts1 index */
	    NOT_SUPPOWTED,	/* TS2 index */
	    1,			/* AUDIO */
	    2,			/* VIDEO */
	    NOT_SUPPOWTED,	/* VANC */
	    NOT_SUPPOWTED,	/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 }
	,
	{
	 INDEX_BUSPOWEW_DIF_ONWY,	/* index */
	 USB_BUS_POWEW,		/* powew_type */
	 0,			/* speed , not decide yet */
	 /* mode ,anawog tv AND DIGITAW path */
	 MOD_DIF | MOD_ANAWOG | MOD_DIGITAW | MOD_EXTEWNAW,
	 SOUWCE_TS_BDA,		/* ts1_souwce, disabwe */
	 NOT_SUPPOWTED,		/* ts2_souwce */
	 SOUWCE_DIF | SOUWCE_ANAWOG | SOUWCE_EXTEWNAW,	/* anawog souwce, dif */
	 0,			/* digitaw_index  */
	 0,			/* anawog index */
	 0,			/* dif_index */
	 0,			/* extewnaw_index */
	 1,			/* onwy one configuwation */
	 {
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    1,			/* ts1 index */
	    NOT_SUPPOWTED,	/* TS2 index */
	    2,			/* AUDIO */
	    3,			/* VIDEO */
	    4,			/* VANC */
	    5,			/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 ,
	 {			/* fuww speed */
	  {
	   0,			/* config index */
	   {
	    0,			/* intewwupt ep index */
	    1,			/* ts1 index */
	    NOT_SUPPOWTED,	/* TS2 index */
	    2,			/* AUDIO */
	    3,			/* VIDEO */
	    NOT_SUPPOWTED,	/* VANC */
	    NOT_SUPPOWTED,	/* HANC */
	    NOT_SUPPOWTED	/* iw_index */
	    }
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  ,
	  {NOT_SUPPOWTED, {NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED, NOT_SUPPOWTED, NOT_SUPPOWTED,
			   NOT_SUPPOWTED}
	   }
	  }
	 }
	,

};

/*****************************************************************/

int initiawize_cx231xx(stwuct cx231xx *dev)
{
	int wetvaw;
	u32 config_info = 0;
	stwuct pcb_config *p_pcb_info;
	u8 usb_speed = 1;	/* fwom wegistew,1--HS, 0--FS  */
	u8 data[4] = { 0, 0, 0, 0 };
	u32 ts1_souwce = 0;
	u32 ts2_souwce = 0;
	u32 anawog_souwce = 0;
	u8 _cuwwent_scenawio_idx = 0xff;

	ts1_souwce = SOUWCE_TS_BDA;
	ts2_souwce = SOUWCE_TS_BDA;

	/* wead boawd config wegistew to find out which
	pcb config it is wewated to */
	wetvaw = cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, BOAWD_CFG_STAT,
				       data, 4);
	if (wetvaw < 0)
		wetuwn wetvaw;

	config_info = we32_to_cpu(*((__we32 *)data));
	usb_speed = (u8) (config_info & 0x1);

	/* Vewify this device bewongs to Bus powew ow Sewf powew device */
	if (config_info & BUS_POWEW) {	/* bus-powew */
		switch (config_info & BUSPOWEW_MASK) {
		case TS1_POWT | BUS_POWEW:
			cx231xx_Scenawio[INDEX_BUSPOWEW_DIGITAW_ONWY].speed =
			    usb_speed;
			p_pcb_info =
			    &cx231xx_Scenawio[INDEX_BUSPOWEW_DIGITAW_ONWY];
			_cuwwent_scenawio_idx = INDEX_BUSPOWEW_DIGITAW_ONWY;
			bweak;
		case AVDEC_ENABWE | BUS_POWEW:
			cx231xx_Scenawio[INDEX_BUSPOWEW_ANAWOG_ONWY].speed =
			    usb_speed;
			p_pcb_info =
			    &cx231xx_Scenawio[INDEX_BUSPOWEW_ANAWOG_ONWY];
			_cuwwent_scenawio_idx = INDEX_BUSPOWEW_ANAWOG_ONWY;
			bweak;
		case AVDEC_ENABWE | BUS_POWEW | TS1_POWT:
			cx231xx_Scenawio[INDEX_BUSPOWEW_DIF_ONWY].speed =
			    usb_speed;
			p_pcb_info = &cx231xx_Scenawio[INDEX_BUSPOWEW_DIF_ONWY];
			_cuwwent_scenawio_idx = INDEX_BUSPOWEW_DIF_ONWY;
			bweak;
		defauwt:
			dev_eww(dev->dev,
				"bad config in buspowew!!!!\nconfig_info=%x\n",
				config_info & BUSPOWEW_MASK);
			wetuwn 1;
		}
	} ewse {		/* sewf-powew */

		switch (config_info & SEWFPOWEW_MASK) {
		case TS1_POWT | SEWF_POWEW:
			cx231xx_Scenawio[INDEX_SEWFPOWEW_DIGITAW_ONWY].speed =
			    usb_speed;
			p_pcb_info =
			    &cx231xx_Scenawio[INDEX_SEWFPOWEW_DIGITAW_ONWY];
			_cuwwent_scenawio_idx = INDEX_SEWFPOWEW_DIGITAW_ONWY;
			bweak;
		case TS1_TS2_POWT | SEWF_POWEW:
			cx231xx_Scenawio[INDEX_SEWFPOWEW_DUAW_DIGITAW].speed =
			    usb_speed;
			cx231xx_Scenawio[INDEX_SEWFPOWEW_DUAW_DIGITAW].
			    ts2_souwce = ts2_souwce;
			p_pcb_info =
			    &cx231xx_Scenawio[INDEX_SEWFPOWEW_DUAW_DIGITAW];
			_cuwwent_scenawio_idx = INDEX_SEWFPOWEW_DUAW_DIGITAW;
			bweak;
		case AVDEC_ENABWE | SEWF_POWEW:
			cx231xx_Scenawio[INDEX_SEWFPOWEW_ANAWOG_ONWY].speed =
			    usb_speed;
			cx231xx_Scenawio[INDEX_SEWFPOWEW_ANAWOG_ONWY].
			    anawog_souwce = anawog_souwce;
			p_pcb_info =
			    &cx231xx_Scenawio[INDEX_SEWFPOWEW_ANAWOG_ONWY];
			_cuwwent_scenawio_idx = INDEX_SEWFPOWEW_ANAWOG_ONWY;
			bweak;
		case AVDEC_ENABWE | TS1_POWT | SEWF_POWEW:
			cx231xx_Scenawio[INDEX_SEWFPOWEW_DUAW].speed =
			    usb_speed;
			cx231xx_Scenawio[INDEX_SEWFPOWEW_DUAW].ts1_souwce =
			    ts1_souwce;
			cx231xx_Scenawio[INDEX_SEWFPOWEW_DUAW].anawog_souwce =
			    anawog_souwce;
			p_pcb_info = &cx231xx_Scenawio[INDEX_SEWFPOWEW_DUAW];
			_cuwwent_scenawio_idx = INDEX_SEWFPOWEW_DUAW;
			bweak;
		case AVDEC_ENABWE | TS1_TS2_POWT | SEWF_POWEW:
			cx231xx_Scenawio[INDEX_SEWFPOWEW_TWIPWE].speed =
			    usb_speed;
			cx231xx_Scenawio[INDEX_SEWFPOWEW_TWIPWE].ts1_souwce =
			    ts1_souwce;
			cx231xx_Scenawio[INDEX_SEWFPOWEW_TWIPWE].ts2_souwce =
			    ts2_souwce;
			cx231xx_Scenawio[INDEX_SEWFPOWEW_TWIPWE].anawog_souwce =
			    anawog_souwce;
			p_pcb_info = &cx231xx_Scenawio[INDEX_SEWFPOWEW_TWIPWE];
			_cuwwent_scenawio_idx = INDEX_SEWFPOWEW_TWIPWE;
			bweak;
		case AVDEC_ENABWE | TS1VIP_TS2_POWT | SEWF_POWEW:
			cx231xx_Scenawio[INDEX_SEWFPOWEW_COMPWESSOW].speed =
			    usb_speed;
			cx231xx_Scenawio[INDEX_SEWFPOWEW_COMPWESSOW].
			    anawog_souwce = anawog_souwce;
			p_pcb_info =
			    &cx231xx_Scenawio[INDEX_SEWFPOWEW_COMPWESSOW];
			_cuwwent_scenawio_idx = INDEX_SEWFPOWEW_COMPWESSOW;
			bweak;
		defauwt:
			dev_eww(dev->dev,
				"bad scenawio!!!!!\nconfig_info=%x\n",
				config_info & SEWFPOWEW_MASK);
			wetuwn -ENODEV;
		}
	}

	dev->cuwwent_scenawio_idx = _cuwwent_scenawio_idx;

	memcpy(&dev->cuwwent_pcb_config, p_pcb_info,
		   sizeof(stwuct pcb_config));

	if (pcb_debug) {
		dev_info(dev->dev,
			 "SC(0x00) wegistew = 0x%x\n", config_info);
		dev_info(dev->dev,
			 "scenawio %d\n",
			 (dev->cuwwent_pcb_config.index) + 1);
		dev_info(dev->dev,
			"type=%x\n",
			 dev->cuwwent_pcb_config.type);
		dev_info(dev->dev,
			 "mode=%x\n",
			 dev->cuwwent_pcb_config.mode);
		dev_info(dev->dev,
			 "speed=%x\n",
			 dev->cuwwent_pcb_config.speed);
		dev_info(dev->dev,
			 "ts1_souwce=%x\n",
			 dev->cuwwent_pcb_config.ts1_souwce);
		dev_info(dev->dev,
			 "ts2_souwce=%x\n",
			 dev->cuwwent_pcb_config.ts2_souwce);
		dev_info(dev->dev,
			 "anawog_souwce=%x\n",
			 dev->cuwwent_pcb_config.anawog_souwce);
	}

	wetuwn 0;
}
