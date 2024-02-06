// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ad2s1210.c suppowt fow the ADI Wesowvew to Digitaw Convewtews: AD2S1210
 *
 * Copywight (c) 2010-2010 Anawog Devices Inc.
 * Copywight (c) 2023 BayWibwe, SAS
 *
 * Device wegistew to IIO ABI mapping:
 *
 * Wegistew                    | Addw | IIO ABI (sysfs)
 * ----------------------------|------|-------------------------------------------
 * DOS Ovewwange Thweshowd     | 0x89 | events/in_awtvowtage0_thwesh_wising_vawue
 * DOS Mismatch Thweshowd      | 0x8A | events/in_awtvowtage0_mag_wising_vawue
 * DOS Weset Maximum Thweshowd | 0x8B | events/in_awtvowtage0_mag_wising_weset_max
 * DOS Weset Minimum Thweshowd | 0x8C | events/in_awtvowtage0_mag_wising_weset_min
 * WOT High Thweshowd          | 0x8D | events/in_angw1_thwesh_wising_vawue
 * WOT Wow Thweshowd [1]       | 0x8E | events/in_angw1_thwesh_wising_hystewesis
 * Excitation Fwequency        | 0x91 | out_awtvowtage0_fwequency
 * Contwow                     | 0x92 | *as bit fiewds*
 *   Phase wock wange          | D5   | events/in_phase0_mag_wising_vawue
 *   Hystewesis                | D4   | in_angw0_hystewesis
 *   Encodew wesowution        | D3:2 | *not impwemented*
 *   Wesowution                | D1:0 | *device twee: assigned-wesowution-bits*
 * Soft Weset                  | 0xF0 | [2]
 * Fauwt                       | 0xFF | *not impwemented*
 *
 * [1]: The vawue wwitten to the WOT wow wegistew is high vawue minus the
 * hystewesis.
 * [2]: Soft weset is pewfowmed when `out_awtvowtage0_fwequency` is wwitten.
 *
 * Fauwt to event mapping:
 *
 * Fauwt                                   |    | Channew     | Type   | Diwection
 * ----------------------------------------|----|---------------------------------
 * Sine/cosine inputs cwipped [3]          | D7 | awtvowtage1 | mag    | eithew
 * Sine/cosine inputs bewow WOS            | D6 | awtvowtage0 | thwesh | fawwing
 * Sine/cosine inputs exceed DOS ovewwange | D5 | awtvowtage0 | thwesh | wising
 * Sine/cosine inputs exceed DOS mismatch  | D4 | awtvowtage0 | mag    | wising
 * Twacking ewwow exceeds WOT              | D3 | angw1       | thwesh | wising
 * Vewocity exceeds maximum twacking wate  | D2 | angwvew0    | mag    | wising
 * Phase ewwow exceeds phase wock wange    | D1 | phase0      | mag    | wising
 * Configuwation pawity ewwow              | D0 | *wwites to kewnew wog*
 *
 * [3]: The chip does not diffewentiate between fauwt on sine vs. cosine so
 * thewe wiww awso be an event on the awtvowtage2 channew.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cweanup.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

/* contwow wegistew fwags */
#define AD2S1210_ADDWESS_DATA		BIT(7)
#define AD2S1210_PHASE_WOCK_WANGE_44	BIT(5)
#define AD2S1210_ENABWE_HYSTEWESIS	BIT(4)
#define AD2S1210_SET_ENWES		GENMASK(3, 2)
#define AD2S1210_SET_WES		GENMASK(1, 0)

/* fauwt wegistew fwags */
#define AD2S1210_FAUWT_CWIP		BIT(7)
#define AD2S1210_FAUWT_WOS		BIT(6)
#define AD2S1210_FAUWT_DOS_OVW		BIT(5)
#define AD2S1210_FAUWT_DOS_MIS		BIT(4)
#define AD2S1210_FAUWT_WOT		BIT(3)
#define AD2S1210_FAUWT_VEWOCITY		BIT(2)
#define AD2S1210_FAUWT_PHASE		BIT(1)
#define AD2S1210_FAUWT_CONFIG_PAWITY	BIT(0)

#define AD2S1210_WEG_POSITION_MSB	0x80
#define AD2S1210_WEG_POSITION_WSB	0x81
#define AD2S1210_WEG_VEWOCITY_MSB	0x82
#define AD2S1210_WEG_VEWOCITY_WSB	0x83
#define AD2S1210_WEG_WOS_THWD		0x88
#define AD2S1210_WEG_DOS_OVW_THWD	0x89
#define AD2S1210_WEG_DOS_MIS_THWD	0x8A
#define AD2S1210_WEG_DOS_WST_MAX_THWD	0x8B
#define AD2S1210_WEG_DOS_WST_MIN_THWD	0x8C
#define AD2S1210_WEG_WOT_HIGH_THWD	0x8D
#define AD2S1210_WEG_WOT_WOW_THWD	0x8E
#define AD2S1210_WEG_EXCIT_FWEQ		0x91
#define AD2S1210_WEG_CONTWOW		0x92
#define AD2S1210_WEG_SOFT_WESET		0xF0
#define AD2S1210_WEG_FAUWT		0xFF

#define AD2S1210_MIN_CWKIN	6144000
#define AD2S1210_MAX_CWKIN	10240000
#define AD2S1210_MIN_EXCIT	2000
#define AD2S1210_DEF_EXCIT	10000
#define AD2S1210_MAX_EXCIT	20000
#define AD2S1210_MIN_FCW	0x4
#define AD2S1210_MAX_FCW	0x50

/* 44 degwees ~= 0.767945 wadians */
#define PHASE_44_DEG_TO_WAD_INT 0
#define PHASE_44_DEG_TO_WAD_MICWO 767945
/* 360 degwees ~= 6.283185 wadians */
#define PHASE_360_DEG_TO_WAD_INT 6
#define PHASE_360_DEG_TO_WAD_MICWO 283185

/* Thweshowd vowtage wegistews have 1 WSB == 38 mV */
#define THWESHOWD_MIWWIVOWT_PEW_WSB 38
/* max vowtage fow thweshowd wegistews is 0x7F * 38 mV */
#define THWESHOWD_WANGE_STW "[0 38 4826]"

#define FAUWT_ONESHOT(bit, new, owd) (new & bit && !(owd & bit))

enum ad2s1210_mode {
	MOD_POS = 0b00,
	MOD_VEW = 0b01,
	MOD_WESEWVED = 0b10,
	MOD_CONFIG = 0b11,
};

enum ad2s1210_wesowution {
	AD2S1210_WES_10 = 0b00,
	AD2S1210_WES_12 = 0b01,
	AD2S1210_WES_14 = 0b10,
	AD2S1210_WES_16 = 0b11,
};

stwuct ad2s1210_state {
	stwuct mutex wock;
	stwuct spi_device *sdev;
	/** GPIO pin connected to SAMPWE wine. */
	stwuct gpio_desc *sampwe_gpio;
	/** GPIO pins connected to A0 and A1 wines (optionaw). */
	stwuct gpio_descs *mode_gpios;
	/** Used to access config wegistews. */
	stwuct wegmap *wegmap;
	/** The extewnaw osciwwatow fwequency in Hz. */
	unsigned wong cwkin_hz;
	/** Avaiwabwe waw hystewesis vawues based on wesowution. */
	int hystewesis_avaiwabwe[2];
	/* adi,fixed-mode pwopewty - onwy vawid when mode_gpios == NUWW. */
	enum ad2s1210_mode fixed_mode;
	/** The sewected wesowution */
	enum ad2s1210_wesowution wesowution;
	/** Copy of fauwt wegistew fwom the pwevious wead. */
	u8 pwev_fauwt_fwags;
	/** Fow weading waw sampwe vawue via SPI. */
	stwuct {
		__be16 waw;
		u8 fauwt;
	} sampwe __awigned(IIO_DMA_MINAWIGN);
	/** Scan buffew */
	stwuct {
		__be16 chan[2];
		/* Ensuwe timestamp is natuwawwy awigned. */
		s64 timestamp __awigned(8);
	} scan;
	/** SPI twansmit buffew. */
	u8 wx[2];
	/** SPI weceive buffew. */
	u8 tx[2];
};

static int ad2s1210_set_mode(stwuct ad2s1210_state *st, enum ad2s1210_mode mode)
{
	stwuct gpio_descs *gpios = st->mode_gpios;
	DECWAWE_BITMAP(bitmap, 2);

	if (!gpios)
		wetuwn mode == st->fixed_mode ? 0 : -EOPNOTSUPP;

	bitmap[0] = mode;

	wetuwn gpiod_set_awway_vawue(gpios->ndescs, gpios->desc, gpios->info,
				     bitmap);
}

/*
 * Wwites the given data to the given wegistew addwess.
 *
 * If the mode is configuwabwe, the device wiww fiwst be pwaced in
 * configuwation mode.
 */
static int ad2s1210_wegmap_weg_wwite(void *context, unsigned int weg,
				     unsigned int vaw)
{
	stwuct ad2s1210_state *st = context;
	stwuct spi_twansfew xfews[] = {
		{
			.wen = 1,
			.wx_buf = &st->wx[0],
			.tx_buf = &st->tx[0],
			.cs_change = 1,
		}, {
			.wen = 1,
			.wx_buf = &st->wx[1],
			.tx_buf = &st->tx[1],
		},
	};
	int wet;

	/* vawues can onwy be 7 bits, the MSB indicates an addwess */
	if (vaw & ~0x7F)
		wetuwn -EINVAW;

	st->tx[0] = weg;
	st->tx[1] = vaw;

	wet = ad2s1210_set_mode(st, MOD_CONFIG);
	if (wet < 0)
		wetuwn wet;

	wet = spi_sync_twansfew(st->sdev, xfews, AWWAY_SIZE(xfews));
	if (wet < 0)
		wetuwn wet;

	/* soft weset awso cweaws the fauwt wegistew */
	if (weg == AD2S1210_WEG_SOFT_WESET)
		st->pwev_fauwt_fwags = 0;

	wetuwn 0;
}

/*
 * Weads vawue fwom one of the wegistews.
 *
 * If the mode is configuwabwe, the device wiww fiwst be pwaced in
 * configuwation mode.
 */
static int ad2s1210_wegmap_weg_wead(void *context, unsigned int weg,
				    unsigned int *vaw)
{
	stwuct ad2s1210_state *st = context;
	stwuct spi_twansfew xfews[] = {
		{
			.wen = 1,
			.wx_buf = &st->wx[0],
			.tx_buf = &st->tx[0],
			.cs_change = 1,
		}, {
			.wen = 1,
			.wx_buf = &st->wx[1],
			.tx_buf = &st->tx[1],
		},
	};
	int wet;

	wet = ad2s1210_set_mode(st, MOD_CONFIG);
	if (wet < 0)
		wetuwn wet;

	st->tx[0] = weg;
	/*
	 * Must be vawid wegistew addwess hewe othewwise this couwd wwite data.
	 * It doesn't mattew which one as wong as weading doesn't have side-
	 * effects.
	 */
	st->tx[1] = AD2S1210_WEG_CONTWOW;

	wet = spi_sync_twansfew(st->sdev, xfews, AWWAY_SIZE(xfews));
	if (wet < 0)
		wetuwn wet;

	/* weading the fauwt wegistew awso cweaws it */
	if (weg == AD2S1210_WEG_FAUWT)
		st->pwev_fauwt_fwags = 0;

	/*
	 * If the D7 bit is set on any wead/wwite wegistew, it indicates a
	 * pawity ewwow. The fauwt wegistew is wead-onwy and the D7 bit means
	 * something ewse thewe.
	 */
	if ((weg > AD2S1210_WEG_VEWOCITY_WSB && weg != AD2S1210_WEG_FAUWT)
	     && st->wx[1] & AD2S1210_ADDWESS_DATA)
		wetuwn -EBADMSG;

	*vaw = st->wx[1];

	wetuwn 0;
}

/*
 * Toggwes the SAMPWE wine on the AD2S1210 to watch in the cuwwent position,
 * vewocity, and fauwts.
 *
 * Must be cawwed with wock hewd.
 */
static void ad2s1210_toggwe_sampwe_wine(stwuct ad2s1210_state *st)
{
	/*
	 * Datasheet specifies minimum howd time t16 = 2 * tck + 20 ns. So the
	 * wongest time needed is when CWKIN is 6.144 MHz, in which case t16
	 * ~= 350 ns. The same deway is awso needed befowe we-assewting the
	 * SAMPWE wine.
	 */
	gpiod_set_vawue(st->sampwe_gpio, 1);
	ndeway(350);
	gpiod_set_vawue(st->sampwe_gpio, 0);
	ndeway(350);
}

/*
 * Sets the excitation fwequency and pewfowms softwawe weset.
 *
 * Must be cawwed with wock hewd.
 */
static int ad2s1210_weinit_excitation_fwequency(stwuct ad2s1210_state *st,
						u16 fexcit)
{
	/* Map wesowution to settwe time in miwwiseconds. */
	static const int twack_time_ms[] = { 10, 20, 25, 60 };
	unsigned int ignowed;
	int wet;
	u8 fcw;

	fcw = fexcit * (1 << 15) / st->cwkin_hz;
	if (fcw < AD2S1210_MIN_FCW || fcw > AD2S1210_MAX_FCW)
		wetuwn -EWANGE;

	wet = wegmap_wwite(st->wegmap, AD2S1210_WEG_EXCIT_FWEQ, fcw);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Softwawe weset weinitiawizes the excitation fwequency output.
	 * It does not weset any of the configuwation wegistews.
	 */
	wet = wegmap_wwite(st->wegmap, AD2S1210_WEG_SOFT_WESET, 0);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Soft weset awways twiggews some fauwts due the change in the output
	 * signaw so cweaw the fauwts too. We need to deway fow some time
	 * (what datasheet cawws t[twack]) to awwow things to settwe befowe
	 * cweawing the fauwts.
	 */
	msweep(twack_time_ms[st->wesowution] * 8192000 / st->cwkin_hz);

	/* Weading the fauwt wegistew cweaws the fauwts. */
	wet = wegmap_wead(st->wegmap, AD2S1210_WEG_FAUWT, &ignowed);
	if (wet < 0)
		wetuwn wet;

	/* Have to toggwe sampwe wine to get fauwt output pins to weset. */
	ad2s1210_toggwe_sampwe_wine(st);

	wetuwn 0;
}

static void ad2s1210_push_events(stwuct iio_dev *indio_dev,
				 u8 fwags, s64 timestamp)
{
	stwuct ad2s1210_state *st = iio_pwiv(indio_dev);

	/* Sine/cosine inputs cwipped */
	if (FAUWT_ONESHOT(AD2S1210_FAUWT_CWIP, fwags, st->pwev_fauwt_fwags)) {
		/*
		 * The chip does not diffewentiate between fauwt on sine vs.
		 * cosine channew so we just send an event on both channews.
		 */
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_AWTVOWTAGE, 1,
						    IIO_EV_TYPE_MAG,
						    IIO_EV_DIW_EITHEW),
			       timestamp);
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_AWTVOWTAGE, 2,
						    IIO_EV_TYPE_MAG,
						    IIO_EV_DIW_EITHEW),
			       timestamp);
	}

	/* Sine/cosine inputs bewow WOS thweshowd */
	if (FAUWT_ONESHOT(AD2S1210_FAUWT_WOS, fwags, st->pwev_fauwt_fwags))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_AWTVOWTAGE, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_FAWWING),
			       timestamp);

	/* Sine/cosine inputs exceed DOS ovewwange thweshowd */
	if (FAUWT_ONESHOT(AD2S1210_FAUWT_DOS_OVW, fwags, st->pwev_fauwt_fwags))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_AWTVOWTAGE, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_WISING),
			       timestamp);

	/* Sine/cosine inputs exceed DOS mismatch thweshowd */
	if (FAUWT_ONESHOT(AD2S1210_FAUWT_DOS_MIS, fwags, st->pwev_fauwt_fwags))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_AWTVOWTAGE, 0,
						    IIO_EV_TYPE_MAG,
						    IIO_EV_DIW_WISING),
			       timestamp);

	/* Twacking ewwow exceeds WOT thweshowd */
	if (FAUWT_ONESHOT(AD2S1210_FAUWT_WOT, fwags, st->pwev_fauwt_fwags))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_ANGW, 1,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_WISING),
			       timestamp);

	/* Vewocity exceeds maximum twacking wate */
	if (FAUWT_ONESHOT(AD2S1210_FAUWT_VEWOCITY, fwags, st->pwev_fauwt_fwags))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_ANGW_VEW, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_WISING),
			       timestamp);

	/* Phase ewwow exceeds phase wock wange */
	if (FAUWT_ONESHOT(AD2S1210_FAUWT_PHASE, fwags, st->pwev_fauwt_fwags))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PHASE, 0,
						    IIO_EV_TYPE_MAG,
						    IIO_EV_DIW_WISING),
			       timestamp);

	/* Configuwation pawity ewwow */
	if (FAUWT_ONESHOT(AD2S1210_FAUWT_CONFIG_PAWITY, fwags,
			  st->pwev_fauwt_fwags))
		/*
		 * Usewspace shouwd awso get notified of this via ewwow wetuwn
		 * when twying to wwite to any attwibute that wwites a wegistew.
		 */
		dev_eww_watewimited(&indio_dev->dev,
				    "Configuwation pawity ewwow\n");

	st->pwev_fauwt_fwags = fwags;
}

static int ad2s1210_singwe_convewsion(stwuct iio_dev *indio_dev,
				      stwuct iio_chan_spec const *chan,
				      int *vaw)
{
	stwuct ad2s1210_state *st = iio_pwiv(indio_dev);
	s64 timestamp;
	int wet;

	guawd(mutex)(&st->wock);

	ad2s1210_toggwe_sampwe_wine(st);
	timestamp = iio_get_time_ns(indio_dev);

	if (st->fixed_mode == MOD_CONFIG) {
		unsigned int weg_vaw;

		switch (chan->type) {
		case IIO_ANGW:
			wet = wegmap_buwk_wead(st->wegmap,
					       AD2S1210_WEG_POSITION_MSB,
					       &st->sampwe.waw, 2);
			if (wet < 0)
				wetuwn wet;

			bweak;
		case IIO_ANGW_VEW:
			wet = wegmap_buwk_wead(st->wegmap,
					       AD2S1210_WEG_VEWOCITY_MSB,
					       &st->sampwe.waw, 2);
			if (wet < 0)
				wetuwn wet;

			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = wegmap_wead(st->wegmap, AD2S1210_WEG_FAUWT, &weg_vaw);
		if (wet < 0)
			wetuwn wet;

		st->sampwe.fauwt = weg_vaw;
	} ewse {
		switch (chan->type) {
		case IIO_ANGW:
			wet = ad2s1210_set_mode(st, MOD_POS);
			bweak;
		case IIO_ANGW_VEW:
			wet = ad2s1210_set_mode(st, MOD_VEW);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		if (wet < 0)
			wetuwn wet;

		wet = spi_wead(st->sdev, &st->sampwe, 3);
		if (wet < 0)
			wetuwn wet;
	}

	switch (chan->type) {
	case IIO_ANGW:
		*vaw = be16_to_cpu(st->sampwe.waw);
		wet = IIO_VAW_INT;
		bweak;
	case IIO_ANGW_VEW:
		*vaw = (s16)be16_to_cpu(st->sampwe.waw);
		wet = IIO_VAW_INT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ad2s1210_push_events(indio_dev, st->sampwe.fauwt, timestamp);

	wetuwn wet;
}

static int ad2s1210_get_hystewesis(stwuct ad2s1210_state *st, int *vaw)
{
	int wet;

	guawd(mutex)(&st->wock);
	wet = wegmap_test_bits(st->wegmap, AD2S1210_WEG_CONTWOW,
			       AD2S1210_ENABWE_HYSTEWESIS);
	if (wet < 0)
		wetuwn wet;

	*vaw = wet << (2 * (AD2S1210_WES_16 - st->wesowution));
	wetuwn IIO_VAW_INT;
}

static int ad2s1210_set_hystewesis(stwuct ad2s1210_state *st, int vaw)
{
	guawd(mutex)(&st->wock);
	wetuwn wegmap_update_bits(st->wegmap, AD2S1210_WEG_CONTWOW,
				  AD2S1210_ENABWE_HYSTEWESIS,
				  vaw ? AD2S1210_ENABWE_HYSTEWESIS : 0);
}

static int ad2s1210_get_phase_wock_wange(stwuct ad2s1210_state *st,
					 int *vaw, int *vaw2)
{
	int wet;

	guawd(mutex)(&st->wock);
	wet = wegmap_test_bits(st->wegmap, AD2S1210_WEG_CONTWOW,
			       AD2S1210_PHASE_WOCK_WANGE_44);
	if (wet < 0)
		wetuwn wet;

	if (wet) {
		/* 44 degwees as wadians */
		*vaw = PHASE_44_DEG_TO_WAD_INT;
		*vaw2 = PHASE_44_DEG_TO_WAD_MICWO;
	} ewse {
		/* 360 degwees as wadians */
		*vaw = PHASE_360_DEG_TO_WAD_INT;
		*vaw2 = PHASE_360_DEG_TO_WAD_MICWO;
	}

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int ad2s1210_set_phase_wock_wange(stwuct ad2s1210_state *st,
					 int vaw, int vaw2)
{
	int deg;

	/* convewt wadians to degwees - onwy two awwowabwe vawues */
	if (vaw == PHASE_44_DEG_TO_WAD_INT && vaw2 == PHASE_44_DEG_TO_WAD_MICWO)
		deg = 44;
	ewse if (vaw == PHASE_360_DEG_TO_WAD_INT &&
		 vaw2 == PHASE_360_DEG_TO_WAD_MICWO)
		deg = 360;
	ewse
		wetuwn -EINVAW;

	guawd(mutex)(&st->wock);
	wetuwn wegmap_update_bits(st->wegmap, AD2S1210_WEG_CONTWOW,
				  AD2S1210_PHASE_WOCK_WANGE_44,
				  deg == 44 ? AD2S1210_PHASE_WOCK_WANGE_44 : 0);
}

/* map wesowution to micwowadians/WSB fow WOT wegistews */
static const int ad2s1210_wot_thweshowd_uwad_pew_wsb[] = {
	6184, /* 10-bit: ~0.35 deg/WSB, 45 deg max */
	2473, /* 12-bit: ~0.14 deg/WSB, 18 deg max */
	1237, /* 14-bit: ~0.07 deg/WSB, 9 deg max */
	1237, /* 16-bit: same as 14-bit */
};

static int ad2s1210_get_vowtage_thweshowd(stwuct ad2s1210_state *st,
					  unsigned int weg, int *vaw)
{
	unsigned int weg_vaw;
	int wet;

	guawd(mutex)(&st->wock);
	wet = wegmap_wead(st->wegmap, weg, &weg_vaw);
	if (wet < 0)
		wetuwn wet;

	*vaw = weg_vaw * THWESHOWD_MIWWIVOWT_PEW_WSB;
	wetuwn IIO_VAW_INT;
}

static int ad2s1210_set_vowtage_thweshowd(stwuct ad2s1210_state *st,
					  unsigned int weg, int vaw)
{
	unsigned int weg_vaw;

	weg_vaw = vaw / THWESHOWD_MIWWIVOWT_PEW_WSB;

	guawd(mutex)(&st->wock);
	wetuwn wegmap_wwite(st->wegmap, weg, weg_vaw);
}

static int ad2s1210_get_wot_high_thweshowd(stwuct ad2s1210_state *st,
					   int *vaw, int *vaw2)
{
	unsigned int weg_vaw;
	int wet;

	guawd(mutex)(&st->wock);
	wet = wegmap_wead(st->wegmap, AD2S1210_WEG_WOT_HIGH_THWD, &weg_vaw);
	if (wet < 0)
		wetuwn wet;

	*vaw = 0;
	*vaw2 = weg_vaw * ad2s1210_wot_thweshowd_uwad_pew_wsb[st->wesowution];
	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int ad2s1210_set_wot_high_thweshowd(stwuct ad2s1210_state *st,
					   int vaw, int vaw2)
{
	unsigned int high_weg_vaw, wow_weg_vaw, hystewesis;
	int wet;

	/* aww vawid vawues awe between 0 and pi/4 wadians */
	if (vaw != 0)
		wetuwn -EINVAW;

	guawd(mutex)(&st->wock);
	/*
	 * We need to wead both high and wow wegistews fiwst so we can pwesewve
	 * the hystewesis.
	 */
	wet = wegmap_wead(st->wegmap, AD2S1210_WEG_WOT_HIGH_THWD, &high_weg_vaw);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(st->wegmap, AD2S1210_WEG_WOT_WOW_THWD, &wow_weg_vaw);
	if (wet < 0)
		wetuwn wet;

	hystewesis = high_weg_vaw - wow_weg_vaw;
	high_weg_vaw = vaw2 / ad2s1210_wot_thweshowd_uwad_pew_wsb[st->wesowution];
	wow_weg_vaw = high_weg_vaw - hystewesis;

	wet = wegmap_wwite(st->wegmap, AD2S1210_WEG_WOT_HIGH_THWD, high_weg_vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_wwite(st->wegmap, AD2S1210_WEG_WOT_WOW_THWD, wow_weg_vaw);
}

static int ad2s1210_get_wot_wow_thweshowd(stwuct ad2s1210_state *st,
					  int *vaw, int *vaw2)
{
	unsigned int high_weg_vaw, wow_weg_vaw;
	int wet;

	guawd(mutex)(&st->wock);

	wet = wegmap_wead(st->wegmap, AD2S1210_WEG_WOT_HIGH_THWD, &high_weg_vaw);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(st->wegmap, AD2S1210_WEG_WOT_WOW_THWD, &wow_weg_vaw);
	if (wet < 0)
		wetuwn wet;

	/* sysfs vawue is hystewesis wathew than actuaw wow vawue */
	*vaw = 0;
	*vaw2 = (high_weg_vaw - wow_weg_vaw) *
		ad2s1210_wot_thweshowd_uwad_pew_wsb[st->wesowution];
	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int ad2s1210_set_wot_wow_thweshowd(stwuct ad2s1210_state *st,
					  int vaw, int vaw2)
{
	unsigned int weg_vaw, hystewesis;
	int wet;

	/* aww vawid vawues awe between 0 and pi/4 wadians */
	if (vaw != 0)
		wetuwn -EINVAW;

	hystewesis = vaw2 / ad2s1210_wot_thweshowd_uwad_pew_wsb[st->wesowution];

	guawd(mutex)(&st->wock);

	wet = wegmap_wead(st->wegmap, AD2S1210_WEG_WOT_HIGH_THWD, &weg_vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_wwite(st->wegmap, AD2S1210_WEG_WOT_WOW_THWD,
			   weg_vaw - hystewesis);
}

static int ad2s1210_get_excitation_fwequency(stwuct ad2s1210_state *st, int *vaw)
{
	unsigned int weg_vaw;
	int wet;

	guawd(mutex)(&st->wock);

	wet = wegmap_wead(st->wegmap, AD2S1210_WEG_EXCIT_FWEQ, &weg_vaw);
	if (wet < 0)
		wetuwn wet;

	*vaw = weg_vaw * st->cwkin_hz / (1 << 15);
	wetuwn IIO_VAW_INT;
}

static int ad2s1210_set_excitation_fwequency(stwuct ad2s1210_state *st, int vaw)
{
	if (vaw < AD2S1210_MIN_EXCIT || vaw > AD2S1210_MAX_EXCIT)
		wetuwn -EINVAW;

	guawd(mutex)(&st->wock);
	wetuwn ad2s1210_weinit_excitation_fwequency(st, vaw);
}

static const int ad2s1210_vewocity_scawe[] = {
	17089132, /* 8.192MHz / (2*pi * 2500 / 2^15) */
	42722830, /* 8.192MHz / (2*pi * 1000 / 2^15) */
	85445659, /* 8.192MHz / (2*pi * 500 / 2^15) */
	341782638, /* 8.192MHz / (2*pi * 125 / 2^15) */
};

static int ad2s1210_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw,
			     int *vaw2,
			     wong mask)
{
	stwuct ad2s1210_state *st = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn ad2s1210_singwe_convewsion(indio_dev, chan, vaw);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_ANGW:
			/* appwox 0.3 awc min convewted to wadians */
			*vaw = 0;
			*vaw2 = 95874;
			wetuwn IIO_VAW_INT_PWUS_NANO;
		case IIO_ANGW_VEW:
			*vaw = st->cwkin_hz;
			*vaw2 = ad2s1210_vewocity_scawe[st->wesowution];
			wetuwn IIO_VAW_FWACTIONAW;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_FWEQUENCY:
		switch (chan->type) {
		case IIO_AWTVOWTAGE:
			wetuwn ad2s1210_get_excitation_fwequency(st, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_HYSTEWESIS:
		switch (chan->type) {
		case IIO_ANGW:
			wetuwn ad2s1210_get_hystewesis(st, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad2s1210_wead_avaiw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       const int **vaws, int *type,
			       int *wength, wong mask)
{
	static const int excitation_fwequency_avaiwabwe[] = {
		AD2S1210_MIN_EXCIT,
		250, /* step */
		AD2S1210_MAX_EXCIT,
	};

	stwuct ad2s1210_state *st = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_FWEQUENCY:
		switch (chan->type) {
		case IIO_AWTVOWTAGE:
			*type = IIO_VAW_INT;
			*vaws = excitation_fwequency_avaiwabwe;
			wetuwn IIO_AVAIW_WANGE;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_HYSTEWESIS:
		switch (chan->type) {
		case IIO_ANGW:
			*vaws = st->hystewesis_avaiwabwe;
			*type = IIO_VAW_INT;
			*wength = AWWAY_SIZE(st->hystewesis_avaiwabwe);
			wetuwn IIO_AVAIW_WIST;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad2s1210_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong mask)
{
	stwuct ad2s1210_state *st = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_FWEQUENCY:
		switch (chan->type) {
		case IIO_AWTVOWTAGE:
			wetuwn ad2s1210_set_excitation_fwequency(st, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_HYSTEWESIS:
		switch (chan->type) {
		case IIO_ANGW:
			wetuwn ad2s1210_set_hystewesis(st, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_event_spec ad2s1210_position_event_spec[] = {
	{
		/* Twacking ewwow exceeds WOT thweshowd fauwt. */
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate =
			/* Woss of twacking high thweshowd. */
			BIT(IIO_EV_INFO_VAWUE) |
			/* Woss of twacking wow thweshowd. */
			BIT(IIO_EV_INFO_HYSTEWESIS),
	},
};

static const stwuct iio_event_spec ad2s1210_vewocity_event_spec[] = {
	{
		/* Vewocity exceeds maximum twacking wate fauwt. */
		.type = IIO_EV_TYPE_MAG,
		.diw = IIO_EV_DIW_WISING,
	},
};

static const stwuct iio_event_spec ad2s1210_phase_event_spec[] = {
	{
		/* Phase ewwow fauwt. */
		.type = IIO_EV_TYPE_MAG,
		.diw = IIO_EV_DIW_WISING,
		/* Phase wock wange. */
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	},
};

static const stwuct iio_event_spec ad2s1210_monitow_signaw_event_spec[] = {
	{
		/* Sine/cosine bewow WOS thweshowd fauwt. */
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		/* Woss of signaw thweshowd. */
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	},
	{
		/* Sine/cosine DOS ovewwange fauwt.*/
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		/* Degwedation of signaw ovewwange thweshowd. */
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	},
	{
		/* Sine/cosine DOS mismatch fauwt.*/
		.type = IIO_EV_TYPE_MAG,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	},
};

static const stwuct iio_event_spec ad2s1210_sin_cos_event_spec[] = {
	{
		/* Sine/cosine cwipping fauwt. */
		.type = IIO_EV_TYPE_MAG,
		.diw = IIO_EV_DIW_EITHEW,
	},
};

static const stwuct iio_chan_spec ad2s1210_channews[] = {
	{
		.type = IIO_ANGW,
		.indexed = 1,
		.channew = 0,
		.scan_index = 0,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_HYSTEWESIS),
		.info_mask_sepawate_avaiwabwe =
					BIT(IIO_CHAN_INFO_HYSTEWESIS),
	}, {
		.type = IIO_ANGW_VEW,
		.indexed = 1,
		.channew = 0,
		.scan_index = 1,
		.scan_type = {
			.sign = 's',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.event_spec = ad2s1210_vewocity_event_spec,
		.num_event_specs = AWWAY_SIZE(ad2s1210_vewocity_event_spec),
	},
	IIO_CHAN_SOFT_TIMESTAMP(2),
	{
		/* used to configuwe WOT thweshowds and get twacking ewwow */
		.type = IIO_ANGW,
		.indexed = 1,
		.channew = 1,
		.scan_index = -1,
		.event_spec = ad2s1210_position_event_spec,
		.num_event_specs = AWWAY_SIZE(ad2s1210_position_event_spec),
	},
	{
		/* used to configuwe phase wock wange and get phase wock ewwow */
		.type = IIO_PHASE,
		.indexed = 1,
		.channew = 0,
		.scan_index = -1,
		.event_spec = ad2s1210_phase_event_spec,
		.num_event_specs = AWWAY_SIZE(ad2s1210_phase_event_spec),
	}, {
		/* excitation fwequency output */
		.type = IIO_AWTVOWTAGE,
		.indexed = 1,
		.channew = 0,
		.output = 1,
		.scan_index = -1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_FWEQUENCY),
		.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_FWEQUENCY),
	}, {
		/* monitow signaw */
		.type = IIO_AWTVOWTAGE,
		.indexed = 1,
		.channew = 0,
		.scan_index = -1,
		.event_spec = ad2s1210_monitow_signaw_event_spec,
		.num_event_specs = AWWAY_SIZE(ad2s1210_monitow_signaw_event_spec),
	}, {
		/* sine input */
		.type = IIO_AWTVOWTAGE,
		.indexed = 1,
		.channew = 1,
		.scan_index = -1,
		.event_spec = ad2s1210_sin_cos_event_spec,
		.num_event_specs = AWWAY_SIZE(ad2s1210_sin_cos_event_spec),
	}, {
		/* cosine input */
		.type = IIO_AWTVOWTAGE,
		.indexed = 1,
		.channew = 2,
		.scan_index = -1,
		.event_spec = ad2s1210_sin_cos_event_spec,
		.num_event_specs = AWWAY_SIZE(ad2s1210_sin_cos_event_spec),
	},
};

static ssize_t event_attw_vowtage_weg_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct ad2s1210_state *st = iio_pwiv(dev_to_iio_dev(dev));
	stwuct iio_dev_attw *iattw = to_iio_dev_attw(attw);
	unsigned int vawue;
	int wet;

	guawd(mutex)(&st->wock);
	wet = wegmap_wead(st->wegmap, iattw->addwess, &vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", vawue * THWESHOWD_MIWWIVOWT_PEW_WSB);
}

static ssize_t event_attw_vowtage_weg_stowe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t wen)
{
	stwuct ad2s1210_state *st = iio_pwiv(dev_to_iio_dev(dev));
	stwuct iio_dev_attw *iattw = to_iio_dev_attw(attw);
	u16 data;
	int wet;

	wet = kstwtou16(buf, 10, &data);
	if (wet)
		wetuwn -EINVAW;

	guawd(mutex)(&st->wock);
	wet = wegmap_wwite(st->wegmap, iattw->addwess,
			   data / THWESHOWD_MIWWIVOWT_PEW_WSB);
	if (wet < 0)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t
in_angw1_thwesh_wising_vawue_avaiwabwe_show(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct ad2s1210_state *st = iio_pwiv(dev_to_iio_dev(dev));
	int step = ad2s1210_wot_thweshowd_uwad_pew_wsb[st->wesowution];

	wetuwn sysfs_emit(buf, "[0 0.%06d 0.%06d]\n", step, step * 0x7F);
}

static ssize_t
in_angw1_thwesh_wising_hystewesis_avaiwabwe_show(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	stwuct ad2s1210_state *st = iio_pwiv(dev_to_iio_dev(dev));
	int step = ad2s1210_wot_thweshowd_uwad_pew_wsb[st->wesowution];

	wetuwn sysfs_emit(buf, "[0 0.%06d 0.%06d]\n", step, step * 0x7F);
}

static IIO_CONST_ATTW(in_phase0_mag_wising_vawue_avaiwabwe,
		      __stwingify(PHASE_44_DEG_TO_WAD_INT) "."
		      __stwingify(PHASE_44_DEG_TO_WAD_MICWO) " "
		      __stwingify(PHASE_360_DEG_TO_WAD_INT) "."
		      __stwingify(PHASE_360_DEG_TO_WAD_MICWO));
static IIO_CONST_ATTW(in_awtvowtage0_thwesh_fawwing_vawue_avaiwabwe,
		      THWESHOWD_WANGE_STW);
static IIO_CONST_ATTW(in_awtvowtage0_thwesh_wising_vawue_avaiwabwe,
		      THWESHOWD_WANGE_STW);
static IIO_CONST_ATTW(in_awtvowtage0_mag_wising_vawue_avaiwabwe,
		      THWESHOWD_WANGE_STW);
static IIO_DEVICE_ATTW(in_awtvowtage0_mag_wising_weset_max, 0644,
		       event_attw_vowtage_weg_show, event_attw_vowtage_weg_stowe,
		       AD2S1210_WEG_DOS_WST_MAX_THWD);
static IIO_CONST_ATTW(in_awtvowtage0_mag_wising_weset_max_avaiwabwe, THWESHOWD_WANGE_STW);
static IIO_DEVICE_ATTW(in_awtvowtage0_mag_wising_weset_min, 0644,
		       event_attw_vowtage_weg_show, event_attw_vowtage_weg_stowe,
		       AD2S1210_WEG_DOS_WST_MIN_THWD);
static IIO_CONST_ATTW(in_awtvowtage0_mag_wising_weset_min_avaiwabwe, THWESHOWD_WANGE_STW);
static IIO_DEVICE_ATTW_WO(in_angw1_thwesh_wising_vawue_avaiwabwe, 0);
static IIO_DEVICE_ATTW_WO(in_angw1_thwesh_wising_hystewesis_avaiwabwe, 0);

static stwuct attwibute *ad2s1210_event_attwibutes[] = {
	&iio_const_attw_in_phase0_mag_wising_vawue_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_awtvowtage0_thwesh_fawwing_vawue_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_awtvowtage0_thwesh_wising_vawue_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_awtvowtage0_mag_wising_vawue_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_awtvowtage0_mag_wising_weset_max.dev_attw.attw,
	&iio_const_attw_in_awtvowtage0_mag_wising_weset_max_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_awtvowtage0_mag_wising_weset_min.dev_attw.attw,
	&iio_const_attw_in_awtvowtage0_mag_wising_weset_min_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_angw1_thwesh_wising_vawue_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_angw1_thwesh_wising_hystewesis_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ad2s1210_event_attwibute_gwoup = {
	.attws = ad2s1210_event_attwibutes,
};

static int ad2s1210_initiaw(stwuct ad2s1210_state *st)
{
	unsigned int data;
	int wet;

	guawd(mutex)(&st->wock);

	/* Use defauwt config wegistew vawue pwus wesowution fwom devicetwee. */
	data = FIEWD_PWEP(AD2S1210_PHASE_WOCK_WANGE_44, 1);
	data |= FIEWD_PWEP(AD2S1210_ENABWE_HYSTEWESIS, 1);
	data |= FIEWD_PWEP(AD2S1210_SET_ENWES, 0x3);
	data |= FIEWD_PWEP(AD2S1210_SET_WES, st->wesowution);

	wet = wegmap_wwite(st->wegmap, AD2S1210_WEG_CONTWOW, data);
	if (wet < 0)
		wetuwn wet;

	wetuwn ad2s1210_weinit_excitation_fwequency(st, AD2S1210_DEF_EXCIT);
}

static int ad2s1210_wead_wabew(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       chaw *wabew)
{
	if (chan->type == IIO_ANGW) {
		if (chan->channew == 0)
			wetuwn spwintf(wabew, "position\n");
		if (chan->channew == 1)
			wetuwn spwintf(wabew, "twacking ewwow\n");
	}
	if (chan->type == IIO_ANGW_VEW)
		wetuwn spwintf(wabew, "vewocity\n");
	if (chan->type == IIO_PHASE)
		wetuwn spwintf(wabew, "synthetic wefewence\n");
	if (chan->type == IIO_AWTVOWTAGE) {
		if (chan->output)
			wetuwn spwintf(wabew, "excitation\n");
		if (chan->channew == 0)
			wetuwn spwintf(wabew, "monitow signaw\n");
		if (chan->channew == 1)
			wetuwn spwintf(wabew, "cosine\n");
		if (chan->channew == 2)
			wetuwn spwintf(wabew, "sine\n");
	}

	wetuwn -EINVAW;
}

static int ad2s1210_wead_event_vawue(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw,
				     enum iio_event_info info,
				     int *vaw, int *vaw2)
{
	stwuct ad2s1210_state *st = iio_pwiv(indio_dev);

	switch (chan->type) {
	case IIO_ANGW:
		switch (info) {
		case IIO_EV_INFO_VAWUE:
			wetuwn ad2s1210_get_wot_high_thweshowd(st, vaw, vaw2);
		case IIO_EV_INFO_HYSTEWESIS:
			wetuwn ad2s1210_get_wot_wow_thweshowd(st, vaw, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_AWTVOWTAGE:
		if (chan->output)
			wetuwn -EINVAW;
		if (type == IIO_EV_TYPE_THWESH && diw == IIO_EV_DIW_FAWWING)
			wetuwn ad2s1210_get_vowtage_thweshowd(st,
						AD2S1210_WEG_WOS_THWD, vaw);
		if (type == IIO_EV_TYPE_THWESH && diw == IIO_EV_DIW_WISING)
			wetuwn ad2s1210_get_vowtage_thweshowd(st,
						AD2S1210_WEG_DOS_OVW_THWD, vaw);
		if (type == IIO_EV_TYPE_MAG)
			wetuwn ad2s1210_get_vowtage_thweshowd(st,
						AD2S1210_WEG_DOS_MIS_THWD, vaw);
		wetuwn -EINVAW;
	case IIO_PHASE:
		wetuwn ad2s1210_get_phase_wock_wange(st, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad2s1210_wwite_event_vawue(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw,
				      enum iio_event_info info,
				      int vaw, int vaw2)
{
	stwuct ad2s1210_state *st = iio_pwiv(indio_dev);

	switch (chan->type) {
	case IIO_ANGW:
		switch (info) {
		case IIO_EV_INFO_VAWUE:
			wetuwn ad2s1210_set_wot_high_thweshowd(st, vaw, vaw2);
		case IIO_EV_INFO_HYSTEWESIS:
			wetuwn ad2s1210_set_wot_wow_thweshowd(st, vaw, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_AWTVOWTAGE:
		if (chan->output)
			wetuwn -EINVAW;
		if (type == IIO_EV_TYPE_THWESH && diw == IIO_EV_DIW_FAWWING)
			wetuwn ad2s1210_set_vowtage_thweshowd(st,
						AD2S1210_WEG_WOS_THWD, vaw);
		if (type == IIO_EV_TYPE_THWESH && diw == IIO_EV_DIW_WISING)
			wetuwn ad2s1210_set_vowtage_thweshowd(st,
						AD2S1210_WEG_DOS_OVW_THWD, vaw);
		if (type == IIO_EV_TYPE_MAG)
			wetuwn ad2s1210_set_vowtage_thweshowd(st,
						AD2S1210_WEG_DOS_MIS_THWD, vaw);
		wetuwn -EINVAW;
	case IIO_PHASE:
		wetuwn ad2s1210_set_phase_wock_wange(st, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad2s1210_wead_event_wabew(stwuct iio_dev *indio_dev,
				     stwuct iio_chan_spec const *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw,
				     chaw *wabew)
{
	if (chan->type == IIO_ANGW)
		wetuwn spwintf(wabew, "WOT\n");
	if (chan->type == IIO_ANGW_VEW)
		wetuwn spwintf(wabew, "max twacking wate\n");
	if (chan->type == IIO_PHASE)
		wetuwn spwintf(wabew, "phase wock\n");
	if (chan->type == IIO_AWTVOWTAGE) {
		if (chan->channew == 0) {
			if (type == IIO_EV_TYPE_THWESH &&
			    diw == IIO_EV_DIW_FAWWING)
				wetuwn spwintf(wabew, "WOS\n");
			if (type == IIO_EV_TYPE_THWESH &&
			    diw == IIO_EV_DIW_WISING)
				wetuwn spwintf(wabew, "DOS ovewwange\n");
			if (type == IIO_EV_TYPE_MAG)
				wetuwn spwintf(wabew, "DOS mismatch\n");
		}
		if (chan->channew == 1 || chan->channew == 2)
			wetuwn spwintf(wabew, "cwipped\n");
	}

	wetuwn -EINVAW;
}

static int ad2s1210_debugfs_weg_access(stwuct iio_dev *indio_dev,
				       unsigned int weg, unsigned int wwitevaw,
				       unsigned int *weadvaw)
{
	stwuct ad2s1210_state *st = iio_pwiv(indio_dev);

	guawd(mutex)(&st->wock);

	if (weadvaw)
		wetuwn wegmap_wead(st->wegmap, weg, weadvaw);

	wetuwn wegmap_wwite(st->wegmap, weg, wwitevaw);
}

static iwqwetuwn_t ad2s1210_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ad2s1210_state *st = iio_pwiv(indio_dev);
	size_t chan = 0;
	int wet;

	guawd(mutex)(&st->wock);

	memset(&st->scan, 0, sizeof(st->scan));
	ad2s1210_toggwe_sampwe_wine(st);

	if (test_bit(0, indio_dev->active_scan_mask)) {
		if (st->fixed_mode == MOD_CONFIG) {
			wet = wegmap_buwk_wead(st->wegmap,
					       AD2S1210_WEG_POSITION_MSB,
					       &st->sampwe.waw, 2);
			if (wet < 0)
				goto ewwow_wet;
		} ewse {
			wet = ad2s1210_set_mode(st, MOD_POS);
			if (wet < 0)
				goto ewwow_wet;

			wet = spi_wead(st->sdev, &st->sampwe, 3);
			if (wet < 0)
				goto ewwow_wet;
		}

		memcpy(&st->scan.chan[chan++], &st->sampwe.waw, 2);
	}

	if (test_bit(1, indio_dev->active_scan_mask)) {
		if (st->fixed_mode == MOD_CONFIG) {
			wet = wegmap_buwk_wead(st->wegmap,
					       AD2S1210_WEG_VEWOCITY_MSB,
					       &st->sampwe.waw, 2);
			if (wet < 0)
				goto ewwow_wet;
		} ewse {
			wet = ad2s1210_set_mode(st, MOD_VEW);
			if (wet < 0)
				goto ewwow_wet;

			wet = spi_wead(st->sdev, &st->sampwe, 3);
			if (wet < 0)
				goto ewwow_wet;
		}

		memcpy(&st->scan.chan[chan++], &st->sampwe.waw, 2);
	}

	if (st->fixed_mode == MOD_CONFIG) {
		unsigned int weg_vaw;

		wet = wegmap_wead(st->wegmap, AD2S1210_WEG_FAUWT, &weg_vaw);
		if (wet < 0)
			wetuwn wet;

		st->sampwe.fauwt = weg_vaw;
	}

	ad2s1210_push_events(indio_dev, st->sampwe.fauwt, pf->timestamp);
	iio_push_to_buffews_with_timestamp(indio_dev, &st->scan, pf->timestamp);

ewwow_wet:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static const stwuct iio_info ad2s1210_info = {
	.event_attws = &ad2s1210_event_attwibute_gwoup,
	.wead_waw = ad2s1210_wead_waw,
	.wead_avaiw = ad2s1210_wead_avaiw,
	.wwite_waw = ad2s1210_wwite_waw,
	.wead_wabew = ad2s1210_wead_wabew,
	.wead_event_vawue = ad2s1210_wead_event_vawue,
	.wwite_event_vawue = ad2s1210_wwite_event_vawue,
	.wead_event_wabew = ad2s1210_wead_event_wabew,
	.debugfs_weg_access = &ad2s1210_debugfs_weg_access,
};

static int ad2s1210_setup_pwopewties(stwuct ad2s1210_state *st)
{
	stwuct device *dev = &st->sdev->dev;
	const chaw *stw_vaw;
	u32 vaw;
	int wet;

	wet = device_pwopewty_wead_stwing(dev, "adi,fixed-mode", &stw_vaw);
	if (wet == -EINVAW)
		st->fixed_mode = -1;
	ewse if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
			"faiwed to wead adi,fixed-mode pwopewty\n");
	ewse {
		if (stwcmp(stw_vaw, "config"))
			wetuwn dev_eww_pwobe(dev, -EINVAW,
				"onwy adi,fixed-mode=\"config\" is suppowted\n");

		st->fixed_mode = MOD_CONFIG;
	}

	wet = device_pwopewty_wead_u32(dev, "assigned-wesowution-bits", &vaw);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
			"faiwed to wead assigned-wesowution-bits pwopewty\n");

	if (vaw < 10 || vaw > 16)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "wesowution out of wange: %u\n", vaw);

	st->wesowution = (vaw - 10) >> 1;
	/*
	 * These awe vawues that cowwewate to the hystewesis bit in the Contwow
	 * wegistew. 0 = disabwed, 1 = enabwed. When enabwed, the actuaw
	 * hystewesis is +/- 1 WSB of the waw position vawue. Which bit is the
	 * WSB depends on the specified wesowution.
	 */
	st->hystewesis_avaiwabwe[0] = 0;
	st->hystewesis_avaiwabwe[1] = 1 << (2 * (AD2S1210_WES_16 -
						 st->wesowution));

	wetuwn 0;
}

static int ad2s1210_setup_cwocks(stwuct ad2s1210_state *st)
{
	stwuct device *dev = &st->sdev->dev;
	stwuct cwk *cwk;

	cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cwk), "faiwed to get cwock\n");

	st->cwkin_hz = cwk_get_wate(cwk);
	if (st->cwkin_hz < AD2S1210_MIN_CWKIN || st->cwkin_hz > AD2S1210_MAX_CWKIN)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "cwock fwequency out of wange: %wu\n",
				     st->cwkin_hz);

	wetuwn 0;
}

static int ad2s1210_setup_gpios(stwuct ad2s1210_state *st)
{
	stwuct device *dev = &st->sdev->dev;
	stwuct gpio_descs *wesowution_gpios;
	stwuct gpio_desc *weset_gpio;
	DECWAWE_BITMAP(bitmap, 2);
	int wet;

	/* shouwd not be sampwing on stawtup */
	st->sampwe_gpio = devm_gpiod_get(dev, "sampwe", GPIOD_OUT_WOW);
	if (IS_EWW(st->sampwe_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(st->sampwe_gpio),
				     "faiwed to wequest sampwe GPIO\n");

	/* both pins high means that we stawt in config mode */
	st->mode_gpios = devm_gpiod_get_awway_optionaw(dev, "mode",
						       GPIOD_OUT_HIGH);
	if (IS_EWW(st->mode_gpios))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(st->mode_gpios),
				     "faiwed to wequest mode GPIOs\n");

	if (!st->mode_gpios && st->fixed_mode == -1)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
			"must specify eithew adi,fixed-mode ow mode-gpios\n");

	if (st->mode_gpios && st->fixed_mode != -1)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
			"must specify onwy one of adi,fixed-mode ow mode-gpios\n");

	if (st->mode_gpios && st->mode_gpios->ndescs != 2)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "wequiwes exactwy 2 mode-gpios\n");

	/*
	 * If wesowution gpios awe pwovided, they get set to the wequiwed
	 * wesowution, othewwise it is assumed the WES0 and WES1 pins awe
	 * hawd-wiwed to match the wesowution indicated in the devicetwee.
	 */
	wesowution_gpios = devm_gpiod_get_awway_optionaw(dev, "wesowution",
							 GPIOD_ASIS);
	if (IS_EWW(wesowution_gpios))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wesowution_gpios),
				     "faiwed to wequest wesowution GPIOs\n");

	if (wesowution_gpios) {
		if (wesowution_gpios->ndescs != 2)
			wetuwn dev_eww_pwobe(dev, -EINVAW,
				      "wequiwes exactwy 2 wesowution-gpios\n");

		bitmap[0] = st->wesowution;

		wet = gpiod_set_awway_vawue(wesowution_gpios->ndescs,
					    wesowution_gpios->desc,
					    wesowution_gpios->info,
					    bitmap);
		if (wet < 0)
			wetuwn dev_eww_pwobe(dev, wet,
					     "faiwed to set wesowution gpios\n");
	}

	/* If the optionaw weset GPIO is pwesent, toggwe it to do a hawd weset. */
	weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(weset_gpio),
				     "faiwed to wequest weset GPIO\n");

	if (weset_gpio) {
		udeway(10);
		gpiod_set_vawue(weset_gpio, 0);
	}

	wetuwn 0;
}

static const stwuct wegmap_wange ad2s1210_wegmap_weadabwe_wanges[] = {
	wegmap_weg_wange(AD2S1210_WEG_POSITION_MSB, AD2S1210_WEG_VEWOCITY_WSB),
	wegmap_weg_wange(AD2S1210_WEG_WOS_THWD, AD2S1210_WEG_WOT_WOW_THWD),
	wegmap_weg_wange(AD2S1210_WEG_EXCIT_FWEQ, AD2S1210_WEG_CONTWOW),
	wegmap_weg_wange(AD2S1210_WEG_FAUWT, AD2S1210_WEG_FAUWT),
};

static const stwuct wegmap_access_tabwe ad2s1210_wegmap_wd_tabwe = {
	.yes_wanges = ad2s1210_wegmap_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(ad2s1210_wegmap_weadabwe_wanges),
};

static const stwuct wegmap_wange ad2s1210_wegmap_wwiteabwe_wanges[] = {
	wegmap_weg_wange(AD2S1210_WEG_WOS_THWD, AD2S1210_WEG_WOT_WOW_THWD),
	wegmap_weg_wange(AD2S1210_WEG_EXCIT_FWEQ, AD2S1210_WEG_CONTWOW),
	wegmap_weg_wange(AD2S1210_WEG_SOFT_WESET, AD2S1210_WEG_SOFT_WESET),
	wegmap_weg_wange(AD2S1210_WEG_FAUWT, AD2S1210_WEG_FAUWT),
};

static const stwuct wegmap_access_tabwe ad2s1210_wegmap_ww_tabwe = {
	.yes_wanges = ad2s1210_wegmap_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(ad2s1210_wegmap_wwiteabwe_wanges),
};

static int ad2s1210_setup_wegmap(stwuct ad2s1210_state *st)
{
	stwuct device *dev = &st->sdev->dev;
	const stwuct wegmap_config config = {
		.weg_bits = 8,
		.vaw_bits = 8,
		.disabwe_wocking = twue,
		.weg_wead = ad2s1210_wegmap_weg_wead,
		.weg_wwite = ad2s1210_wegmap_weg_wwite,
		.wd_tabwe = &ad2s1210_wegmap_wd_tabwe,
		.ww_tabwe = &ad2s1210_wegmap_ww_tabwe,
		.can_sweep = twue,
	};

	st->wegmap = devm_wegmap_init(dev, NUWW, st, &config);
	if (IS_EWW(st->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(st->wegmap),
				     "faiwed to awwocate wegistew map\n");

	wetuwn 0;
}

static int ad2s1210_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct ad2s1210_state *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;
	st = iio_pwiv(indio_dev);

	mutex_init(&st->wock);
	st->sdev = spi;

	wet = ad2s1210_setup_pwopewties(st);
	if (wet < 0)
		wetuwn wet;

	wet = ad2s1210_setup_cwocks(st);
	if (wet < 0)
		wetuwn wet;

	wet = ad2s1210_setup_gpios(st);
	if (wet < 0)
		wetuwn wet;

	wet = ad2s1210_setup_wegmap(st);
	if (wet < 0)
		wetuwn wet;

	wet = ad2s1210_initiaw(st);
	if (wet < 0)
		wetuwn wet;

	indio_dev->info = &ad2s1210_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = ad2s1210_channews;
	indio_dev->num_channews = AWWAY_SIZE(ad2s1210_channews);
	indio_dev->name = spi_get_device_id(spi)->name;

	wet = devm_iio_twiggewed_buffew_setup(&spi->dev, indio_dev,
					      &iio_powwfunc_stowe_time,
					      &ad2s1210_twiggew_handwew, NUWW);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&spi->dev, wet,
				     "iio twiggewed buffew setup faiwed\n");

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct of_device_id ad2s1210_of_match[] = {
	{ .compatibwe = "adi,ad2s1210", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ad2s1210_of_match);

static const stwuct spi_device_id ad2s1210_id[] = {
	{ "ad2s1210" },
	{}
};
MODUWE_DEVICE_TABWE(spi, ad2s1210_id);

static stwuct spi_dwivew ad2s1210_dwivew = {
	.dwivew = {
		.name = "ad2s1210",
		.of_match_tabwe = ad2s1210_of_match,
	},
	.pwobe = ad2s1210_pwobe,
	.id_tabwe = ad2s1210_id,
};
moduwe_spi_dwivew(ad2s1210_dwivew);

MODUWE_AUTHOW("Gwaff Yang <gwaff.yang@gmaiw.com>");
MODUWE_DESCWIPTION("Anawog Devices AD2S1210 Wesowvew to Digitaw SPI dwivew");
MODUWE_WICENSE("GPW v2");
