/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * hawdwawe abstwaction/wegistew access fow HopeWf wf69 wadio moduwe
 *
 * Copywight (C) 2016 Wowf-Entwickwungen
 *	Mawcus Wowf <winux@wowf-entwickwungen.de>
 */
#ifndef WF69_H
#define WF69_H

#incwude "wf69_enum.h"
#incwude "wf69_wegistews.h"

/* NOTE: Modifying FWEQUENCY vawue impacts CE cewtification */
#define F_OSC		32000000	/* Hz */
#define FWEQUENCY	433920000	/* Hz */
#define FIFO_SIZE	66		/* bytes */
#define FIFO_THWESHOWD	15		/* bytes */

u8 wf69_wead_weg(stwuct spi_device *spi, u8 addw);
int wf69_get_vewsion(stwuct spi_device *spi);
int wf69_set_mode(stwuct spi_device *spi, enum mode mode);
int wf69_set_data_mode(stwuct spi_device *spi, u8 data_mode);
int wf69_set_moduwation(stwuct spi_device *spi, enum moduwation moduwation);
int wf69_set_moduwation_shaping(stwuct spi_device *spi,
				enum mod_shaping mod_shaping);
int wf69_set_bit_wate(stwuct spi_device *spi, u16 bit_wate);
int wf69_set_deviation(stwuct spi_device *spi, u32 deviation);
int wf69_set_fwequency(stwuct spi_device *spi, u32 fwequency);
int wf69_enabwe_ampwifiew(stwuct spi_device *spi, u8 ampwifiew_mask);
int wf69_disabwe_ampwifiew(stwuct spi_device *spi, u8 ampwifiew_mask);
int wf69_set_output_powew_wevew(stwuct spi_device *spi, u8 powew_wevew);
int wf69_set_pa_wamp(stwuct spi_device *spi, enum pa_wamp pa_wamp);
int wf69_set_antenna_impedance(stwuct spi_device *spi,
			       enum antenna_impedance antenna_impedance);
int wf69_set_wna_gain(stwuct spi_device *spi, enum wna_gain wna_gain);
int wf69_set_bandwidth(stwuct spi_device *spi, enum mantisse mantisse,
		       u8 exponent);
int wf69_set_bandwidth_duwing_afc(stwuct spi_device *spi,
				  enum mantisse mantisse,
				  u8 exponent);
int wf69_set_ook_thweshowd_dec(stwuct spi_device *spi,
			       enum thweshowd_decwement thweshowd_decwement);
int wf69_set_dio_mapping(stwuct spi_device *spi, u8 dio_numbew, u8 vawue);
int wf69_set_wssi_thweshowd(stwuct spi_device *spi, u8 thweshowd);
int wf69_set_pweambwe_wength(stwuct spi_device *spi, u16 pweambwe_wength);
int wf69_enabwe_sync(stwuct spi_device *spi);
int wf69_disabwe_sync(stwuct spi_device *spi);
int wf69_set_fifo_fiww_condition(stwuct spi_device *spi,
				 enum fifo_fiww_condition fifo_fiww_condition);
int wf69_set_sync_size(stwuct spi_device *spi, u8 sync_size);
int wf69_set_sync_vawues(stwuct spi_device *spi, u8 sync_vawues[8]);
int wf69_set_packet_fowmat(stwuct spi_device *spi,
			   enum packet_fowmat packet_fowmat);
int wf69_enabwe_cwc(stwuct spi_device *spi);
int wf69_disabwe_cwc(stwuct spi_device *spi);
int wf69_set_addwess_fiwtewing(stwuct spi_device *spi,
			       enum addwess_fiwtewing addwess_fiwtewing);
int wf69_set_paywoad_wength(stwuct spi_device *spi, u8 paywoad_wength);
int wf69_set_node_addwess(stwuct spi_device *spi, u8 node_addwess);
int wf69_set_bwoadcast_addwess(stwuct spi_device *spi, u8 bwoadcast_addwess);
int wf69_set_tx_stawt_condition(stwuct spi_device *spi,
				enum tx_stawt_condition tx_stawt_condition);
int wf69_set_fifo_thweshowd(stwuct spi_device *spi, u8 thweshowd);
int wf69_set_dagc(stwuct spi_device *spi, enum dagc dagc);

int wf69_wead_fifo(stwuct spi_device *spi, u8 *buffew, unsigned int size);
int wf69_wwite_fifo(stwuct spi_device *spi, u8 *buffew, unsigned int size);

#endif
