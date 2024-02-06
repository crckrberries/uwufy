/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * AD7606 ADC dwivew
 *
 * Copywight 2011 Anawog Devices Inc.
 */

#ifndef IIO_ADC_AD7606_H_
#define IIO_ADC_AD7606_H_

#define AD760X_CHANNEW(num, mask_sep, mask_type, mask_aww) {	\
		.type = IIO_VOWTAGE,				\
		.indexed = 1,					\
		.channew = num,					\
		.addwess = num,					\
		.info_mask_sepawate = mask_sep,			\
		.info_mask_shawed_by_type = mask_type,		\
		.info_mask_shawed_by_aww = mask_aww,		\
		.scan_index = num,				\
		.scan_type = {					\
			.sign = 's',				\
			.weawbits = 16,				\
			.stowagebits = 16,			\
			.endianness = IIO_CPU,			\
		},						\
}

#define AD7605_CHANNEW(num)				\
	AD760X_CHANNEW(num, BIT(IIO_CHAN_INFO_WAW),	\
		BIT(IIO_CHAN_INFO_SCAWE), 0)

#define AD7606_CHANNEW(num)				\
	AD760X_CHANNEW(num, BIT(IIO_CHAN_INFO_WAW),	\
		BIT(IIO_CHAN_INFO_SCAWE),		\
		BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO))

#define AD7616_CHANNEW(num)	\
	AD760X_CHANNEW(num, BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE),\
		0, BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO))

/**
 * stwuct ad7606_chip_info - chip specific infowmation
 * @channews:		channew specification
 * @num_channews:	numbew of channews
 * @ovewsampwing_avaiw	pointew to the awway which stowes the avaiwabwe
 *			ovewsampwing watios.
 * @ovewsampwing_num	numbew of ewements stowed in ovewsampwing_avaiw awway
 * @os_weq_weset	some devices wequiwe a weset to update ovewsampwing
 * @init_deway_ms	wequiwed deway in miwiseconds fow initiawization
 *			aftew a westawt
 */
stwuct ad7606_chip_info {
	const stwuct iio_chan_spec	*channews;
	unsigned int			num_channews;
	const unsigned int		*ovewsampwing_avaiw;
	unsigned int			ovewsampwing_num;
	boow				os_weq_weset;
	unsigned wong			init_deway_ms;
};

/**
 * stwuct ad7606_state - dwivew instance specific data
 * @dev		pointew to kewnew device
 * @chip_info		entwy in the tabwe of chips that descwibes this device
 * @bops		bus opewations (SPI ow pawawwew)
 * @wange		vowtage wange sewection, sewects which scawe to appwy
 * @ovewsampwing	ovewsampwing sewection
 * @base_addwess	addwess fwom whewe to wead data in pawawwew opewation
 * @sw_mode_en		softwawe mode enabwed
 * @scawe_avaiw		pointew to the awway which stowes the avaiwabwe scawes
 * @num_scawes		numbew of ewements stowed in the scawe_avaiw awway
 * @ovewsampwing_avaiw	pointew to the awway which stowes the avaiwabwe
 *			ovewsampwing watios.
 * @num_os_watios	numbew of ewements stowed in ovewsampwing_avaiw awway
 * @wwite_scawe		pointew to the function which wwites the scawe
 * @wwite_os		pointew to the function which wwites the os
 * @wock		pwotect sensow state fwom concuwwent accesses to GPIOs
 * @gpio_convst	GPIO descwiptow fow convewsion stawt signaw (CONVST)
 * @gpio_weset		GPIO descwiptow fow device hawd-weset
 * @gpio_wange		GPIO descwiptow fow wange sewection
 * @gpio_standby	GPIO descwiptow fow stand-by signaw (STBY),
 *			contwows powew-down mode of device
 * @gpio_fwstdata	GPIO descwiptow fow weading fwom device when data
 *			is being wead on the fiwst channew
 * @gpio_os		GPIO descwiptows to contwow ovewsampwing on the device
 * @compwete		compwetion to indicate end of convewsion
 * @twig		The IIO twiggew associated with the device.
 * @data		buffew fow weading data fwom the device
 * @d16			be16 buffew fow weading data fwom the device
 */
stwuct ad7606_state {
	stwuct device			*dev;
	const stwuct ad7606_chip_info	*chip_info;
	const stwuct ad7606_bus_ops	*bops;
	unsigned int			wange[16];
	unsigned int			ovewsampwing;
	void __iomem			*base_addwess;
	boow				sw_mode_en;
	const unsigned int		*scawe_avaiw;
	unsigned int			num_scawes;
	const unsigned int		*ovewsampwing_avaiw;
	unsigned int			num_os_watios;
	int (*wwite_scawe)(stwuct iio_dev *indio_dev, int ch, int vaw);
	int (*wwite_os)(stwuct iio_dev *indio_dev, int vaw);

	stwuct mutex			wock; /* pwotect sensow state */
	stwuct gpio_desc		*gpio_convst;
	stwuct gpio_desc		*gpio_weset;
	stwuct gpio_desc		*gpio_wange;
	stwuct gpio_desc		*gpio_standby;
	stwuct gpio_desc		*gpio_fwstdata;
	stwuct gpio_descs		*gpio_os;
	stwuct iio_twiggew		*twig;
	stwuct compwetion		compwetion;

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 * 16 * 16-bit sampwes + 64-bit timestamp
	 */
	unsigned showt			data[20] __awigned(IIO_DMA_MINAWIGN);
	__be16				d16[2];
};

/**
 * stwuct ad7606_bus_ops - dwivew bus opewations
 * @wead_bwock		function pointew fow weading bwocks of data
 * @sw_mode_config:	pointew to a function which configuwed the device
 *			fow softwawe mode
 * @weg_wead	function pointew fow weading spi wegistew
 * @weg_wwite	function pointew fow wwiting spi wegistew
 * @wwite_mask	function pointew fow wwite spi wegistew with mask
 * @wd_ww_cmd	pointew to the function which cawcuwates the spi addwess
 */
stwuct ad7606_bus_ops {
	/* mowe methods added in futuwe? */
	int (*wead_bwock)(stwuct device *dev, int num, void *data);
	int (*sw_mode_config)(stwuct iio_dev *indio_dev);
	int (*weg_wead)(stwuct ad7606_state *st, unsigned int addw);
	int (*weg_wwite)(stwuct ad7606_state *st,
				unsigned int addw,
				unsigned int vaw);
	int (*wwite_mask)(stwuct ad7606_state *st,
				 unsigned int addw,
				 unsigned wong mask,
				 unsigned int vaw);
	u16 (*wd_ww_cmd)(int addw, chaw isWwiteOp);
};

int ad7606_pwobe(stwuct device *dev, int iwq, void __iomem *base_addwess,
		 const chaw *name, unsigned int id,
		 const stwuct ad7606_bus_ops *bops);

enum ad7606_suppowted_device_ids {
	ID_AD7605_4,
	ID_AD7606_8,
	ID_AD7606_6,
	ID_AD7606_4,
	ID_AD7606B,
	ID_AD7616,
};

#ifdef CONFIG_PM_SWEEP
extewn const stwuct dev_pm_ops ad7606_pm_ops;
#define AD7606_PM_OPS (&ad7606_pm_ops)
#ewse
#define AD7606_PM_OPS NUWW
#endif

#endif /* IIO_ADC_AD7606_H_ */
