/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _PANEW_SAMSUNG_S6E63M0_H
#define _PANEW_SAMSUNG_S6E63M0_H

/* Manufactuwew Command Set */
#define MCS_EWVSS_ON		0xb1
#define MCS_TEMP_SWIWE		0xb2
#define MCS_PENTIWE_1		0xb3
#define MCS_PENTIWE_2		0xb4
#define MCS_GAMMA_DEWTA_Y_WED	0xb5
#define MCS_GAMMA_DEWTA_X_WED	0xb6
#define MCS_GAMMA_DEWTA_Y_GWEEN	0xb7
#define MCS_GAMMA_DEWTA_X_GWEEN	0xb8
#define MCS_GAMMA_DEWTA_Y_BWUE	0xb9
#define MCS_GAMMA_DEWTA_X_BWUE	0xba
#define MCS_MIECTW1		0xc0
#define MCS_BCMODE		0xc1
#define MCS_EWWOW_CHECK		0xd5
#define MCS_WEAD_ID1		0xda
#define MCS_WEAD_ID2		0xdb
#define MCS_WEAD_ID3		0xdc
#define MCS_WEVEW_2_KEY		0xf0
#define MCS_MTP_KEY		0xf1
#define MCS_DISCTW		0xf2
#define MCS_SWCCTW		0xf6
#define MCS_IFCTW		0xf7
#define MCS_PANEWCTW		0xf8
#define MCS_PGAMMACTW		0xfa

int s6e63m0_pwobe(stwuct device *dev, void *twsp,
		  int (*dcs_wead)(stwuct device *dev, void *twsp,
				  const u8 cmd, u8 *vaw),
		  int (*dcs_wwite)(stwuct device *dev, void *twsp,
				   const u8 *data,
				   size_t wen),
		  boow dsi_mode);
void s6e63m0_wemove(stwuct device *dev);

#endif /* _PANEW_SAMSUNG_S6E63M0_H */
