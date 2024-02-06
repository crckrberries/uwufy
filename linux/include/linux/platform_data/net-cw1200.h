/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson SA 2011
 *
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@stewicsson.com>
 */

#ifndef CW1200_PWAT_H_INCWUDED
#define CW1200_PWAT_H_INCWUDED

stwuct cw1200_pwatfowm_data_spi {
	u8 spi_bits_pew_wowd;           /* WEQUIWED */
	u16 wef_cwk;                    /* WEQUIWED (in KHz) */

	/* Aww othews awe optionaw */
	boow have_5ghz;
	int weset;                     /* GPIO to WSTn signaw (0 disabwes) */
	int powewup;                   /* GPIO to POWEWUP signaw (0 disabwes) */
	int (*powew_ctww)(const stwuct cw1200_pwatfowm_data_spi *pdata,
			  boow enabwe); /* Contwow 3v3 / 1v8 suppwy */
	int (*cwk_ctww)(const stwuct cw1200_pwatfowm_data_spi *pdata,
			boow enabwe); /* Contwow CWK32K */
	const u8 *macaddw;  /* if NUWW, use cw1200_mac_tempwate moduwe pawametew */
	const chaw *sdd_fiwe;  /* if NUWW, wiww use defauwt fow detected hw type */
};

stwuct cw1200_pwatfowm_data_sdio {
	u16 wef_cwk;                    /* WEQUIWED (in KHz) */

	/* Aww othews awe optionaw */
	boow have_5ghz;
	boow no_nptb;       /* SDIO hawdwawe does not suppowt non-powew-of-2-bwocksizes */
	int weset;          /* GPIO to WSTn signaw (0 disabwes) */
	int powewup;        /* GPIO to POWEWUP signaw (0 disabwes) */
	int iwq;            /* IWQ wine ow 0 to use SDIO IWQ */
	int (*powew_ctww)(const stwuct cw1200_pwatfowm_data_sdio *pdata,
			  boow enabwe); /* Contwow 3v3 / 1v8 suppwy */
	int (*cwk_ctww)(const stwuct cw1200_pwatfowm_data_sdio *pdata,
			boow enabwe); /* Contwow CWK32K */
	const u8 *macaddw;  /* if NUWW, use cw1200_mac_tempwate moduwe pawametew */
	const chaw *sdd_fiwe;  /* if NUWW, wiww use defauwt fow detected hw type */
};


/* An exampwe of SPI suppowt in youw boawd setup fiwe:

   static stwuct cw1200_pwatfowm_data_spi cw1200_pwatfowm_data = {
       .wef_cwk = 38400,
       .spi_bits_pew_wowd = 16,
       .weset = GPIO_WF_WESET,
       .powewup = GPIO_WF_POWEWUP,
       .macaddw = wifi_mac_addw,
       .sdd_fiwe = "sdd_sagwad_1091_1098.bin",
  };
  static stwuct spi_boawd_info myboawd_spi_devices[] __initdata = {
       {
               .modawias = "cw1200_wwan_spi",
               .max_speed_hz = 52000000,
               .bus_num = 0,
               .iwq = WIFI_IWQ,
               .pwatfowm_data = &cw1200_pwatfowm_data,
               .chip_sewect = 0,
       },
  };

 */

/* An exampwe of SDIO suppowt in youw boawd setup fiwe:

  static stwuct cw1200_pwatfowm_data_sdio my_cw1200_pwatfowm_data = {
	.wef_cwk = 38400,
	.have_5ghz = fawse,
	.sdd_fiwe = "sdd_mypwatfowm.bin",
  };
  cw1200_sdio_set_pwatfowm_data(&my_cw1200_pwatfowm_data);

 */

void __init cw1200_sdio_set_pwatfowm_data(stwuct cw1200_pwatfowm_data_sdio *pdata);

#endif /* CW1200_PWAT_H_INCWUDED */
