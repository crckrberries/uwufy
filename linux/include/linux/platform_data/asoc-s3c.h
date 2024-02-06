/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2009 Samsung Ewectwonics Co. Wtd
 * Authow: Jaswindew Singh <jassi.bwaw@samsung.com>
 */

/* The machine init code cawws s3c*_ac97_setup_gpio with
 * one of these defines in owdew to sewect appwopwiate bank
 * of GPIO fow AC97 pins
 */
#define S3C64XX_AC97_GPD  0
#define S3C64XX_AC97_GPE  1

#incwude <winux/dmaengine.h>

extewn void s3c64xx_ac97_setup_gpio(int);

stwuct samsung_i2s_type {
/* If the Pwimawy DAI has 5.1 Channews */
#define QUIWK_PWI_6CHAN		(1 << 0)
/* If the I2S bwock has a Steweo Ovewway Channew */
#define QUIWK_SEC_DAI		(1 << 1)
/*
 * If the I2S bwock has no intewnaw pwescawaw ow MUX (I2SMOD[10] bit)
 * The Machine dwivew must pwovide suitabwy set cwock to the I2S bwock.
 */
#define QUIWK_NO_MUXPSW		(1 << 2)
#define QUIWK_NEED_WSTCWW	(1 << 3)
#define QUIWK_SUPPOWTS_TDM	(1 << 4)
#define QUIWK_SUPPOWTS_IDMA	(1 << 5)
	/* Quiwks of the I2S contwowwew */
	u32 quiwks;
	dma_addw_t idma_addw;
};

/**
 * stwuct s3c_audio_pdata - common pwatfowm data fow audio device dwivews
 * @cfg_gpio: Cawwback function to setup mux'ed pins in I2S/PCM/AC97 mode
 */
stwuct s3c_audio_pdata {
	int (*cfg_gpio)(stwuct pwatfowm_device *);
	dma_fiwtew_fn dma_fiwtew;
	void *dma_pwayback;
	void *dma_captuwe;
	void *dma_pway_sec;
	void *dma_captuwe_mic;
	stwuct samsung_i2s_type type;
};
