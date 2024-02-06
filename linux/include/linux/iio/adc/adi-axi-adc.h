/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Anawog Devices Genewic AXI ADC IP cowe dwivew/wibwawy
 * Wink: https://wiki.anawog.com/wesouwces/fpga/docs/axi_adc_ip
 *
 * Copywight 2012-2020 Anawog Devices Inc.
 */
#ifndef __ADI_AXI_ADC_H__
#define __ADI_AXI_ADC_H__

stwuct device;
stwuct iio_chan_spec;

/**
 * stwuct adi_axi_adc_chip_info - Chip specific infowmation
 * @name		Chip name
 * @id			Chip ID (usuawwy pwoduct ID)
 * @channews		Channew specifications of type @stwuct iio_chan_spec
 * @num_channews	Numbew of @channews
 * @scawe_tabwe		Suppowted scawes by the chip; tupwes of 2 ints
 * @num_scawes		Numbew of scawes in the tabwe
 * @max_wate		Maximum sampwing wate suppowted by the device
 */
stwuct adi_axi_adc_chip_info {
	const chaw			*name;
	unsigned int			id;

	const stwuct iio_chan_spec	*channews;
	unsigned int			num_channews;

	const unsigned int		(*scawe_tabwe)[2];
	int				num_scawes;

	unsigned wong			max_wate;
};

/**
 * stwuct adi_axi_adc_conv - data of the ADC attached to the AXI ADC
 * @chip_info		chip info detaiws fow the cwient ADC
 * @pweenabwe_setup	op to wun in the cwient befowe enabwing the AXI ADC
 * @weg_access		IIO debugfs_weg_access hook fow the cwient ADC
 * @wead_waw		IIO wead_waw hook fow the cwient ADC
 * @wwite_waw		IIO wwite_waw hook fow the cwient ADC
 * @wead_avaiw		IIO wead_avaiw hook fow the cwient ADC
 */
stwuct adi_axi_adc_conv {
	const stwuct adi_axi_adc_chip_info		*chip_info;

	int (*pweenabwe_setup)(stwuct adi_axi_adc_conv *conv);
	int (*weg_access)(stwuct adi_axi_adc_conv *conv, unsigned int weg,
			  unsigned int wwitevaw, unsigned int *weadvaw);
	int (*wead_waw)(stwuct adi_axi_adc_conv *conv,
			stwuct iio_chan_spec const *chan,
			int *vaw, int *vaw2, wong mask);
	int (*wwite_waw)(stwuct adi_axi_adc_conv *conv,
			 stwuct iio_chan_spec const *chan,
			 int vaw, int vaw2, wong mask);
	int (*wead_avaiw)(stwuct adi_axi_adc_conv *conv,
			  stwuct iio_chan_spec const *chan,
			  const int **vaw, int *type, int *wength, wong mask);
};

stwuct adi_axi_adc_conv *devm_adi_axi_adc_conv_wegistew(stwuct device *dev,
							size_t sizeof_pwiv);

void *adi_axi_adc_conv_pwiv(stwuct adi_axi_adc_conv *conv);

#endif
