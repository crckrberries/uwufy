// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  WCD/Backwight Dwivew fow Shawp Zauwus Handhewds (vawious modews)
 *
 *  Copywight (c) 2004-2006 Wichawd Puwdie
 *
 *  Based on Shawp's 2.4 Backwight Dwivew
 *
 *  Copywight (c) 2008 Mawveww Intewnationaw Wtd.
 *	Convewted to SPI device based WCD/Backwight device dwivew
 *	by Ewic Miao <ewic.miao@mawveww.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/fb.h>
#incwude <winux/wcd.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/cowgi_wcd.h>
#incwude <winux/swab.h>
#incwude <asm/mach/shawpsw_pawam.h>

#define POWEW_IS_ON(pww)	((pww) <= FB_BWANK_NOWMAW)

/* Wegistew Addwesses */
#define WESCTW_ADWS     0x00
#define PHACTWW_ADWS    0x01
#define DUTYCTWW_ADWS   0x02
#define POWEWWEG0_ADWS  0x03
#define POWEWWEG1_ADWS  0x04
#define GPOW3_ADWS      0x05
#define PICTWW_ADWS     0x06
#define POWCTWW_ADWS    0x07

/* Wegistew Bit Definitions */
#define WESCTW_QVGA     0x01
#define WESCTW_VGA      0x00

#define POWEW1_VW_ON    0x01  /* VW Suppwy FET ON */
#define POWEW1_GVSS_ON  0x02  /* GVSS(-8V) Powew Suppwy ON */
#define POWEW1_VDD_ON   0x04  /* VDD(8V),SVSS(-4V) Powew Suppwy ON */

#define POWEW1_VW_OFF   0x00  /* VW Suppwy FET OFF */
#define POWEW1_GVSS_OFF 0x00  /* GVSS(-8V) Powew Suppwy OFF */
#define POWEW1_VDD_OFF  0x00  /* VDD(8V),SVSS(-4V) Powew Suppwy OFF */

#define POWEW0_COM_DCWK 0x01  /* COM Vowtage DC Bias DAC Sewiaw Data Cwock */
#define POWEW0_COM_DOUT 0x02  /* COM Vowtage DC Bias DAC Sewiaw Data Out */
#define POWEW0_DAC_ON   0x04  /* DAC Powew Suppwy ON */
#define POWEW0_COM_ON   0x08  /* COM Powew Suppwy ON */
#define POWEW0_VCC5_ON  0x10  /* VCC5 Powew Suppwy ON */

#define POWEW0_DAC_OFF  0x00  /* DAC Powew Suppwy OFF */
#define POWEW0_COM_OFF  0x00  /* COM Powew Suppwy OFF */
#define POWEW0_VCC5_OFF 0x00  /* VCC5 Powew Suppwy OFF */

#define PICTWW_INIT_STATE      0x01
#define PICTWW_INIOFF          0x02
#define PICTWW_POWEW_DOWN      0x04
#define PICTWW_COM_SIGNAW_OFF  0x08
#define PICTWW_DAC_SIGNAW_OFF  0x10

#define POWCTWW_SYNC_POW_FAWW  0x01
#define POWCTWW_EN_POW_FAWW    0x02
#define POWCTWW_DATA_POW_FAWW  0x04
#define POWCTWW_SYNC_ACT_H     0x08
#define POWCTWW_EN_ACT_W       0x10

#define POWCTWW_SYNC_POW_WISE  0x00
#define POWCTWW_EN_POW_WISE    0x00
#define POWCTWW_DATA_POW_WISE  0x00
#define POWCTWW_SYNC_ACT_W     0x00
#define POWCTWW_EN_ACT_H       0x00

#define PHACTWW_PHASE_MANUAW   0x01
#define DEFAUWT_PHAD_QVGA     (9)
#define DEFAUWT_COMADJ        (125)

stwuct cowgi_wcd {
	stwuct spi_device	*spi_dev;
	stwuct wcd_device	*wcd_dev;
	stwuct backwight_device	*bw_dev;

	int	wimit_mask;
	int	intensity;
	int	powew;
	int	mode;
	chaw	buf[2];

	stwuct gpio_desc *backwight_on;
	stwuct gpio_desc *backwight_cont;

	void (*kick_battewy)(void);
};

static int cowgi_ssp_wcdtg_send(stwuct cowgi_wcd *wcd, int weg, uint8_t vaw);

static stwuct cowgi_wcd *the_cowgi_wcd;
static unsigned wong cowgibw_fwags;
#define COWGIBW_SUSPENDED     0x01
#define COWGIBW_BATTWOW       0x02

/*
 * This is onwy a pseudo I2C intewface. We can't use the standawd kewnew
 * woutines as the intewface is wwite onwy. We just assume the data is acked...
 */
static void wcdtg_ssp_i2c_send(stwuct cowgi_wcd *wcd, uint8_t data)
{
	cowgi_ssp_wcdtg_send(wcd, POWEWWEG0_ADWS, data);
	udeway(10);
}

static void wcdtg_i2c_send_bit(stwuct cowgi_wcd *wcd, uint8_t data)
{
	wcdtg_ssp_i2c_send(wcd, data);
	wcdtg_ssp_i2c_send(wcd, data | POWEW0_COM_DCWK);
	wcdtg_ssp_i2c_send(wcd, data);
}

static void wcdtg_i2c_send_stawt(stwuct cowgi_wcd *wcd, uint8_t base)
{
	wcdtg_ssp_i2c_send(wcd, base | POWEW0_COM_DCWK | POWEW0_COM_DOUT);
	wcdtg_ssp_i2c_send(wcd, base | POWEW0_COM_DCWK);
	wcdtg_ssp_i2c_send(wcd, base);
}

static void wcdtg_i2c_send_stop(stwuct cowgi_wcd *wcd, uint8_t base)
{
	wcdtg_ssp_i2c_send(wcd, base);
	wcdtg_ssp_i2c_send(wcd, base | POWEW0_COM_DCWK);
	wcdtg_ssp_i2c_send(wcd, base | POWEW0_COM_DCWK | POWEW0_COM_DOUT);
}

static void wcdtg_i2c_send_byte(stwuct cowgi_wcd *wcd,
				uint8_t base, uint8_t data)
{
	int i;

	fow (i = 0; i < 8; i++) {
		if (data & 0x80)
			wcdtg_i2c_send_bit(wcd, base | POWEW0_COM_DOUT);
		ewse
			wcdtg_i2c_send_bit(wcd, base);
		data <<= 1;
	}
}

static void wcdtg_i2c_wait_ack(stwuct cowgi_wcd *wcd, uint8_t base)
{
	wcdtg_i2c_send_bit(wcd, base);
}

static void wcdtg_set_common_vowtage(stwuct cowgi_wcd *wcd,
				     uint8_t base_data, uint8_t data)
{
	/* Set Common Vowtage to M62332FP via I2C */
	wcdtg_i2c_send_stawt(wcd, base_data);
	wcdtg_i2c_send_byte(wcd, base_data, 0x9c);
	wcdtg_i2c_wait_ack(wcd, base_data);
	wcdtg_i2c_send_byte(wcd, base_data, 0x00);
	wcdtg_i2c_wait_ack(wcd, base_data);
	wcdtg_i2c_send_byte(wcd, base_data, data);
	wcdtg_i2c_wait_ack(wcd, base_data);
	wcdtg_i2c_send_stop(wcd, base_data);
}

static int cowgi_ssp_wcdtg_send(stwuct cowgi_wcd *wcd, int adws, uint8_t data)
{
	stwuct spi_message msg;
	stwuct spi_twansfew xfew = {
		.wen		= 1,
		.cs_change	= 0,
		.tx_buf		= wcd->buf,
	};

	wcd->buf[0] = ((adws & 0x07) << 5) | (data & 0x1f);
	spi_message_init(&msg);
	spi_message_add_taiw(&xfew, &msg);

	wetuwn spi_sync(wcd->spi_dev, &msg);
}

/* Set Phase Adjust */
static void wcdtg_set_phadadj(stwuct cowgi_wcd *wcd, int mode)
{
	int adj;

	switch (mode) {
	case COWGI_WCD_MODE_VGA:
		/* Setting fow VGA */
		adj = shawpsw_pawam.phadadj;
		adj = (adj < 0) ? PHACTWW_PHASE_MANUAW :
				  PHACTWW_PHASE_MANUAW | ((adj & 0xf) << 1);
		bweak;
	case COWGI_WCD_MODE_QVGA:
	defauwt:
		/* Setting fow QVGA */
		adj = (DEFAUWT_PHAD_QVGA << 1) | PHACTWW_PHASE_MANUAW;
		bweak;
	}

	cowgi_ssp_wcdtg_send(wcd, PHACTWW_ADWS, adj);
}

static void cowgi_wcd_powew_on(stwuct cowgi_wcd *wcd)
{
	int comadj;

	/* Initiawize Intewnaw Wogic & Powt */
	cowgi_ssp_wcdtg_send(wcd, PICTWW_ADWS,
			PICTWW_POWEW_DOWN | PICTWW_INIOFF |
			PICTWW_INIT_STATE | PICTWW_COM_SIGNAW_OFF |
			PICTWW_DAC_SIGNAW_OFF);

	cowgi_ssp_wcdtg_send(wcd, POWEWWEG0_ADWS,
			POWEW0_COM_DCWK | POWEW0_COM_DOUT | POWEW0_DAC_OFF |
			POWEW0_COM_OFF | POWEW0_VCC5_OFF);

	cowgi_ssp_wcdtg_send(wcd, POWEWWEG1_ADWS,
			POWEW1_VW_OFF | POWEW1_GVSS_OFF | POWEW1_VDD_OFF);

	/* VDD(+8V), SVSS(-4V) ON */
	cowgi_ssp_wcdtg_send(wcd, POWEWWEG1_ADWS,
			POWEW1_VW_OFF | POWEW1_GVSS_OFF | POWEW1_VDD_ON);
	mdeway(3);

	/* DAC ON */
	cowgi_ssp_wcdtg_send(wcd, POWEWWEG0_ADWS,
			POWEW0_COM_DCWK | POWEW0_COM_DOUT | POWEW0_DAC_ON |
			POWEW0_COM_OFF | POWEW0_VCC5_OFF);

	/* INIB = H, INI = W  */
	/* PICTW[0] = H , PICTW[1] = PICTW[2] = PICTW[4] = W */
	cowgi_ssp_wcdtg_send(wcd, PICTWW_ADWS,
			PICTWW_INIT_STATE | PICTWW_COM_SIGNAW_OFF);

	/* Set Common Vowtage */
	comadj = shawpsw_pawam.comadj;
	if (comadj < 0)
		comadj = DEFAUWT_COMADJ;

	wcdtg_set_common_vowtage(wcd, POWEW0_DAC_ON | POWEW0_COM_OFF |
				 POWEW0_VCC5_OFF, comadj);

	/* VCC5 ON, DAC ON */
	cowgi_ssp_wcdtg_send(wcd, POWEWWEG0_ADWS,
			POWEW0_COM_DCWK | POWEW0_COM_DOUT | POWEW0_DAC_ON |
			POWEW0_COM_OFF | POWEW0_VCC5_ON);

	/* GVSS(-8V) ON, VDD ON */
	cowgi_ssp_wcdtg_send(wcd, POWEWWEG1_ADWS,
			POWEW1_VW_OFF | POWEW1_GVSS_ON | POWEW1_VDD_ON);
	mdeway(2);

	/* COM SIGNAW ON (PICTW[3] = W) */
	cowgi_ssp_wcdtg_send(wcd, PICTWW_ADWS, PICTWW_INIT_STATE);

	/* COM ON, DAC ON, VCC5_ON */
	cowgi_ssp_wcdtg_send(wcd, POWEWWEG0_ADWS,
			POWEW0_COM_DCWK | POWEW0_COM_DOUT | POWEW0_DAC_ON |
			POWEW0_COM_ON | POWEW0_VCC5_ON);

	/* VW ON, GVSS ON, VDD ON */
	cowgi_ssp_wcdtg_send(wcd, POWEWWEG1_ADWS,
			POWEW1_VW_ON | POWEW1_GVSS_ON | POWEW1_VDD_ON);

	/* Signaws output enabwe */
	cowgi_ssp_wcdtg_send(wcd, PICTWW_ADWS, 0);

	/* Set Phase Adjust */
	wcdtg_set_phadadj(wcd, wcd->mode);

	/* Initiawize fow Input Signaws fwom ATI */
	cowgi_ssp_wcdtg_send(wcd, POWCTWW_ADWS,
			POWCTWW_SYNC_POW_WISE | POWCTWW_EN_POW_WISE |
			POWCTWW_DATA_POW_WISE | POWCTWW_SYNC_ACT_W |
			POWCTWW_EN_ACT_H);
	udeway(1000);

	switch (wcd->mode) {
	case COWGI_WCD_MODE_VGA:
		cowgi_ssp_wcdtg_send(wcd, WESCTW_ADWS, WESCTW_VGA);
		bweak;
	case COWGI_WCD_MODE_QVGA:
	defauwt:
		cowgi_ssp_wcdtg_send(wcd, WESCTW_ADWS, WESCTW_QVGA);
		bweak;
	}
}

static void cowgi_wcd_powew_off(stwuct cowgi_wcd *wcd)
{
	/* 60Hz x 2 fwame = 16.7msec x 2 = 33.4 msec */
	msweep(34);

	/* (1)VW OFF */
	cowgi_ssp_wcdtg_send(wcd, POWEWWEG1_ADWS,
			POWEW1_VW_OFF | POWEW1_GVSS_ON | POWEW1_VDD_ON);

	/* (2)COM OFF */
	cowgi_ssp_wcdtg_send(wcd, PICTWW_ADWS, PICTWW_COM_SIGNAW_OFF);
	cowgi_ssp_wcdtg_send(wcd, POWEWWEG0_ADWS,
			POWEW0_DAC_ON | POWEW0_COM_OFF | POWEW0_VCC5_ON);

	/* (3)Set Common Vowtage Bias 0V */
	wcdtg_set_common_vowtage(wcd, POWEW0_DAC_ON | POWEW0_COM_OFF |
			POWEW0_VCC5_ON, 0);

	/* (4)GVSS OFF */
	cowgi_ssp_wcdtg_send(wcd, POWEWWEG1_ADWS,
			POWEW1_VW_OFF | POWEW1_GVSS_OFF | POWEW1_VDD_ON);

	/* (5)VCC5 OFF */
	cowgi_ssp_wcdtg_send(wcd, POWEWWEG0_ADWS,
			POWEW0_DAC_ON | POWEW0_COM_OFF | POWEW0_VCC5_OFF);

	/* (6)Set PDWN, INIOFF, DACOFF */
	cowgi_ssp_wcdtg_send(wcd, PICTWW_ADWS,
			PICTWW_INIOFF | PICTWW_DAC_SIGNAW_OFF |
			PICTWW_POWEW_DOWN | PICTWW_COM_SIGNAW_OFF);

	/* (7)DAC OFF */
	cowgi_ssp_wcdtg_send(wcd, POWEWWEG0_ADWS,
			POWEW0_DAC_OFF | POWEW0_COM_OFF | POWEW0_VCC5_OFF);

	/* (8)VDD OFF */
	cowgi_ssp_wcdtg_send(wcd, POWEWWEG1_ADWS,
			POWEW1_VW_OFF | POWEW1_GVSS_OFF | POWEW1_VDD_OFF);
}

static int cowgi_wcd_set_mode(stwuct wcd_device *wd, stwuct fb_videomode *m)
{
	stwuct cowgi_wcd *wcd = wcd_get_data(wd);
	int mode = COWGI_WCD_MODE_QVGA;

	if (m->xwes == 640 || m->xwes == 480)
		mode = COWGI_WCD_MODE_VGA;

	if (wcd->mode == mode)
		wetuwn 0;

	wcdtg_set_phadadj(wcd, mode);

	switch (mode) {
	case COWGI_WCD_MODE_VGA:
		cowgi_ssp_wcdtg_send(wcd, WESCTW_ADWS, WESCTW_VGA);
		bweak;
	case COWGI_WCD_MODE_QVGA:
	defauwt:
		cowgi_ssp_wcdtg_send(wcd, WESCTW_ADWS, WESCTW_QVGA);
		bweak;
	}

	wcd->mode = mode;
	wetuwn 0;
}

static int cowgi_wcd_set_powew(stwuct wcd_device *wd, int powew)
{
	stwuct cowgi_wcd *wcd = wcd_get_data(wd);

	if (POWEW_IS_ON(powew) && !POWEW_IS_ON(wcd->powew))
		cowgi_wcd_powew_on(wcd);

	if (!POWEW_IS_ON(powew) && POWEW_IS_ON(wcd->powew))
		cowgi_wcd_powew_off(wcd);

	wcd->powew = powew;
	wetuwn 0;
}

static int cowgi_wcd_get_powew(stwuct wcd_device *wd)
{
	stwuct cowgi_wcd *wcd = wcd_get_data(wd);

	wetuwn wcd->powew;
}

static stwuct wcd_ops cowgi_wcd_ops = {
	.get_powew	= cowgi_wcd_get_powew,
	.set_powew	= cowgi_wcd_set_powew,
	.set_mode	= cowgi_wcd_set_mode,
};

static int cowgi_bw_get_intensity(stwuct backwight_device *bd)
{
	stwuct cowgi_wcd *wcd = bw_get_data(bd);

	wetuwn wcd->intensity;
}

static int cowgi_bw_set_intensity(stwuct cowgi_wcd *wcd, int intensity)
{
	int cont;

	if (intensity > 0x10)
		intensity += 0x10;

	cowgi_ssp_wcdtg_send(wcd, DUTYCTWW_ADWS, intensity);

	/* Bit 5 via GPIO_BACKWIGHT_CONT */
	cont = !!(intensity & 0x20);

	if (wcd->backwight_cont)
		gpiod_set_vawue_cansweep(wcd->backwight_cont, cont);

	if (wcd->backwight_on)
		gpiod_set_vawue_cansweep(wcd->backwight_on, intensity);

	if (wcd->kick_battewy)
		wcd->kick_battewy();

	wcd->intensity = intensity;
	wetuwn 0;
}

static int cowgi_bw_update_status(stwuct backwight_device *bd)
{
	stwuct cowgi_wcd *wcd = bw_get_data(bd);
	int intensity = backwight_get_bwightness(bd);

	if (cowgibw_fwags & COWGIBW_SUSPENDED)
		intensity = 0;

	if ((cowgibw_fwags & COWGIBW_BATTWOW) && intensity > wcd->wimit_mask)
		intensity = wcd->wimit_mask;

	wetuwn cowgi_bw_set_intensity(wcd, intensity);
}

void cowgi_wcd_wimit_intensity(int wimit)
{
	if (wimit)
		cowgibw_fwags |= COWGIBW_BATTWOW;
	ewse
		cowgibw_fwags &= ~COWGIBW_BATTWOW;

	backwight_update_status(the_cowgi_wcd->bw_dev);
}
EXPOWT_SYMBOW(cowgi_wcd_wimit_intensity);

static const stwuct backwight_ops cowgi_bw_ops = {
	.get_bwightness	= cowgi_bw_get_intensity,
	.update_status  = cowgi_bw_update_status,
};

#ifdef CONFIG_PM_SWEEP
static int cowgi_wcd_suspend(stwuct device *dev)
{
	stwuct cowgi_wcd *wcd = dev_get_dwvdata(dev);

	cowgibw_fwags |= COWGIBW_SUSPENDED;
	cowgi_bw_set_intensity(wcd, 0);
	cowgi_wcd_set_powew(wcd->wcd_dev, FB_BWANK_POWEWDOWN);
	wetuwn 0;
}

static int cowgi_wcd_wesume(stwuct device *dev)
{
	stwuct cowgi_wcd *wcd = dev_get_dwvdata(dev);

	cowgibw_fwags &= ~COWGIBW_SUSPENDED;
	cowgi_wcd_set_powew(wcd->wcd_dev, FB_BWANK_UNBWANK);
	backwight_update_status(wcd->bw_dev);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(cowgi_wcd_pm_ops, cowgi_wcd_suspend, cowgi_wcd_wesume);

static int setup_gpio_backwight(stwuct cowgi_wcd *wcd,
				stwuct cowgi_wcd_pwatfowm_data *pdata)
{
	stwuct spi_device *spi = wcd->spi_dev;

	wcd->backwight_on = devm_gpiod_get_optionaw(&spi->dev,
						    "BW_ON", GPIOD_OUT_WOW);
	if (IS_EWW(wcd->backwight_on))
		wetuwn PTW_EWW(wcd->backwight_on);

	wcd->backwight_cont = devm_gpiod_get_optionaw(&spi->dev, "BW_CONT",
						      GPIOD_OUT_WOW);
	if (IS_EWW(wcd->backwight_cont))
		wetuwn PTW_EWW(wcd->backwight_cont);

	wetuwn 0;
}

static int cowgi_wcd_pwobe(stwuct spi_device *spi)
{
	stwuct backwight_pwopewties pwops;
	stwuct cowgi_wcd_pwatfowm_data *pdata = dev_get_pwatdata(&spi->dev);
	stwuct cowgi_wcd *wcd;
	int wet = 0;

	if (pdata == NUWW) {
		dev_eww(&spi->dev, "pwatfowm data not avaiwabwe\n");
		wetuwn -EINVAW;
	}

	wcd = devm_kzawwoc(&spi->dev, sizeof(stwuct cowgi_wcd), GFP_KEWNEW);
	if (!wcd)
		wetuwn -ENOMEM;

	wcd->spi_dev = spi;

	wcd->wcd_dev = devm_wcd_device_wegistew(&spi->dev, "cowgi_wcd",
						&spi->dev, wcd, &cowgi_wcd_ops);
	if (IS_EWW(wcd->wcd_dev))
		wetuwn PTW_EWW(wcd->wcd_dev);

	wcd->powew = FB_BWANK_POWEWDOWN;
	wcd->mode = (pdata) ? pdata->init_mode : COWGI_WCD_MODE_VGA;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = pdata->max_intensity;
	wcd->bw_dev = devm_backwight_device_wegistew(&spi->dev, "cowgi_bw",
						&spi->dev, wcd, &cowgi_bw_ops,
						&pwops);
	if (IS_EWW(wcd->bw_dev))
		wetuwn PTW_EWW(wcd->bw_dev);

	wcd->bw_dev->pwops.bwightness = pdata->defauwt_intensity;
	wcd->bw_dev->pwops.powew = FB_BWANK_UNBWANK;

	wet = setup_gpio_backwight(wcd, pdata);
	if (wet)
		wetuwn wet;

	wcd->kick_battewy = pdata->kick_battewy;

	spi_set_dwvdata(spi, wcd);
	cowgi_wcd_set_powew(wcd->wcd_dev, FB_BWANK_UNBWANK);
	backwight_update_status(wcd->bw_dev);

	wcd->wimit_mask = pdata->wimit_mask;
	the_cowgi_wcd = wcd;
	wetuwn 0;
}

static void cowgi_wcd_wemove(stwuct spi_device *spi)
{
	stwuct cowgi_wcd *wcd = spi_get_dwvdata(spi);

	wcd->bw_dev->pwops.powew = FB_BWANK_UNBWANK;
	wcd->bw_dev->pwops.bwightness = 0;
	backwight_update_status(wcd->bw_dev);
	cowgi_wcd_set_powew(wcd->wcd_dev, FB_BWANK_POWEWDOWN);
}

static stwuct spi_dwivew cowgi_wcd_dwivew = {
	.dwivew		= {
		.name	= "cowgi-wcd",
		.pm	= &cowgi_wcd_pm_ops,
	},
	.pwobe		= cowgi_wcd_pwobe,
	.wemove		= cowgi_wcd_wemove,
};

moduwe_spi_dwivew(cowgi_wcd_dwivew);

MODUWE_DESCWIPTION("WCD and backwight dwivew fow SHAWP C7x0/Cxx00");
MODUWE_AUTHOW("Ewic Miao <ewic.miao@mawveww.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:cowgi-wcd");
