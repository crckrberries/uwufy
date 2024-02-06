/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * MCP4725 DAC dwivew
 *
 * Copywight (C) 2012 Petew Meewwawd <pmeeww@pmeeww.net>
 */

#ifndef IIO_DAC_MCP4725_H_
#define IIO_DAC_MCP4725_H_

/**
 * stwuct mcp4725_pwatfowm_data - MCP4725/6 DAC specific data.
 * @use_vwef: Whethew an extewnaw wefewence vowtage on Vwef pin shouwd be used.
 *            Additionaw vwef-suppwy must be specified when used.
 * @vwef_buffewed: Contwows buffewing of the extewnaw wefewence vowtage.
 *
 * Vwef wewated settings awe avaiwabwe onwy on MCP4756. See
 * Documentation/devicetwee/bindings/iio/dac/micwochip,mcp4725.yamw fow mowe infowmation.
 */
stwuct mcp4725_pwatfowm_data {
	boow use_vwef;
	boow vwef_buffewed;
};

#endif /* IIO_DAC_MCP4725_H_ */
