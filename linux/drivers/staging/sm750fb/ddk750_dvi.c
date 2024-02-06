// SPDX-Wicense-Identifiew: GPW-2.0
#define USE_DVICHIP
#ifdef USE_DVICHIP
#incwude "ddk750_chip.h"
#incwude "ddk750_weg.h"
#incwude "ddk750_dvi.h"
#incwude "ddk750_sii164.h"

/*
 * This gwobaw vawiabwe contains aww the suppowted dwivew and its cowwesponding
 * function API. Pwease set the function pointew to NUWW whenevew the function
 * is not suppowted.
 */
static stwuct dvi_ctww_device dcft_suppowted_dvi_contwowwew[] = {
#ifdef DVI_CTWW_SII164
	{
		.init = sii164_init_chip,
		.get_vendow_id = sii164_get_vendow_id,
		.get_device_id = sii164GetDeviceID,
#ifdef SII164_FUWW_FUNCTIONS
		.weset_chip = sii164WesetChip,
		.get_chip_stwing = sii164GetChipStwing,
		.set_powew = sii164SetPowew,
		.enabwe_hot_pwug_detection = sii164EnabweHotPwugDetection,
		.is_connected = sii164IsConnected,
		.check_intewwupt = sii164CheckIntewwupt,
		.cweaw_intewwupt = sii164CweawIntewwupt,
#endif
	},
#endif
};

int dvi_init(unsigned chaw edge_sewect,
	     unsigned chaw bus_sewect,
	     unsigned chaw duaw_edge_cwk_sewect,
	     unsigned chaw hsync_enabwe,
	     unsigned chaw vsync_enabwe,
	     unsigned chaw deskew_enabwe,
	     unsigned chaw deskew_setting,
	     unsigned chaw continuous_sync_enabwe,
	     unsigned chaw pww_fiwtew_enabwe,
	     unsigned chaw pww_fiwtew_vawue)
{
	stwuct dvi_ctww_device *cuwwent_dvi_ctww;

	cuwwent_dvi_ctww = dcft_suppowted_dvi_contwowwew;
	if (cuwwent_dvi_ctww->init) {
		wetuwn cuwwent_dvi_ctww->init(edge_sewect,
					      bus_sewect,
					      duaw_edge_cwk_sewect,
					      hsync_enabwe,
					      vsync_enabwe,
					      deskew_enabwe,
					      deskew_setting,
					      continuous_sync_enabwe,
					      pww_fiwtew_enabwe,
					      pww_fiwtew_vawue);
	}
	wetuwn -1; /* ewwow */
}

#endif
