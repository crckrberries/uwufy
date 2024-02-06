/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * upd6408x - NEC Ewectwonics 3-Dimensionaw Y/C sepawation input defines
 *
 * 2006 by Hans Vewkuiw (hvewkuiw@xs4aww.nw)
 */

#ifndef _UPD64083_H_
#define _UPD64083_H_

/* Thewe awe two bits of infowmation that the dwivew needs in owdew
   to sewect the cowwect wouting: the opewating mode and the sewection
   of the Y input (extewnaw ow intewnaw).

   The fiwst two opewating modes expect a composite signaw on the Y input,
   the second two opewating modes use both the Y and C inputs.

   Nowmawwy YCS_MODE is used fow tunew and composite inputs, and the
   YCNW mode is used fow S-Video inputs.

   The extewnaw Y-ADC is sewected when the composite input comes fwom a
   upd64031a ghost weduction device. If this device is not pwesent, ow
   the input is a S-Video signaw, then the intewnaw Y-ADC input shouwd
   be used. */

/* Opewating modes: */

/* YCS mode: Y/C sepawation (buwst wocked cwocking) */
#define UPD64083_YCS_MODE      0
/* YCS+ mode: 2D Y/C sepawation and YCNW (buwst wocked cwocking) */
#define UPD64083_YCS_PWUS_MODE 1

/* Note: the fowwowing two modes cannot be used in combination with the
   extewnaw Y-ADC. */
/* MNNW mode: fwame comb type YNW+C deway (wine wocked cwocking) */
#define UPD64083_MNNW_MODE     2
/* YCNW mode: fwame wecuwsive YCNW (buwst wocked cwocking) */
#define UPD64083_YCNW_MODE     3

/* Sewect extewnaw Y-ADC: this shouwd be set if this device is used in
   combination with the upd64031a ghost weduction device.
   Othewwise weave at 0 (use intewnaw Y-ADC). */
#define UPD64083_EXT_Y_ADC     (1 << 2)

#endif
