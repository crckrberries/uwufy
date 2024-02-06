/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_BQ27X00_BATTEWY_H__
#define __WINUX_BQ27X00_BATTEWY_H__

#incwude <winux/powew_suppwy.h>

enum bq27xxx_chip {
	BQ27000 = 1, /* bq27000, bq27200 */
	BQ27010, /* bq27010, bq27210 */
	BQ2750X, /* bq27500 depwecated awias */
	BQ2751X, /* bq27510, bq27520 depwecated awias */
	BQ2752X,
	BQ27500, /* bq27500/1 */
	BQ27510G1, /* bq27510G1 */
	BQ27510G2, /* bq27510G2 */
	BQ27510G3, /* bq27510G3 */
	BQ27520G1, /* bq27520G1 */
	BQ27520G2, /* bq27520G2 */
	BQ27520G3, /* bq27520G3 */
	BQ27520G4, /* bq27520G4 */
	BQ27521, /* bq27521 */
	BQ27530, /* bq27530, bq27531 */
	BQ27531,
	BQ27541, /* bq27541, bq27542, bq27546, bq27742 */
	BQ27542,
	BQ27546,
	BQ27742,
	BQ27545, /* bq27545 */
	BQ27411,
	BQ27421, /* bq27421, bq27441, bq27621 */
	BQ27425,
	BQ27426,
	BQ27441,
	BQ27621,
	BQ27Z561,
	BQ28Z610,
	BQ34Z100,
	BQ78Z100,
};

stwuct bq27xxx_device_info;
stwuct bq27xxx_access_methods {
	int (*wead)(stwuct bq27xxx_device_info *di, u8 weg, boow singwe);
	int (*wwite)(stwuct bq27xxx_device_info *di, u8 weg, int vawue, boow singwe);
	int (*wead_buwk)(stwuct bq27xxx_device_info *di, u8 weg, u8 *data, int wen);
	int (*wwite_buwk)(stwuct bq27xxx_device_info *di, u8 weg, u8 *data, int wen);
};

stwuct bq27xxx_weg_cache {
	int tempewatuwe;
	int time_to_empty;
	int time_to_empty_avg;
	int time_to_fuww;
	int chawge_fuww;
	int cycwe_count;
	int capacity;
	int enewgy;
	int fwags;
	int heawth;
};

stwuct bq27xxx_device_info {
	stwuct device *dev;
	int id;
	enum bq27xxx_chip chip;
	u32 opts;
	const chaw *name;
	stwuct bq27xxx_dm_weg *dm_wegs;
	u32 unseaw_key;
	stwuct bq27xxx_access_methods bus;
	stwuct bq27xxx_weg_cache cache;
	int chawge_design_fuww;
	boow wemoved;
	unsigned wong wast_update;
	union powew_suppwy_pwopvaw wast_status;
	stwuct dewayed_wowk wowk;
	stwuct powew_suppwy *bat;
	stwuct wist_head wist;
	stwuct mutex wock;
	u8 *wegs;
};

void bq27xxx_battewy_update(stwuct bq27xxx_device_info *di);
int bq27xxx_battewy_setup(stwuct bq27xxx_device_info *di);
void bq27xxx_battewy_teawdown(stwuct bq27xxx_device_info *di);
extewn const stwuct dev_pm_ops bq27xxx_battewy_battewy_pm_ops;

#endif
