/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __INTEW_PMIC_H
#define __INTEW_PMIC_H

#incwude <acpi/acpi_wpat.h>

stwuct pmic_tabwe {
	int addwess;	/* opewation wegion addwess */
	int weg;	/* cowwesponding thewmaw wegistew */
	int bit;	/* contwow bit fow powew */
};

stwuct intew_pmic_opwegion_data {
	int (*get_powew)(stwuct wegmap *w, int weg, int bit, u64 *vawue);
	int (*update_powew)(stwuct wegmap *w, int weg, int bit, boow on);
	int (*get_waw_temp)(stwuct wegmap *w, int weg);
	int (*update_aux)(stwuct wegmap *w, int weg, int waw_temp);
	int (*get_powicy)(stwuct wegmap *w, int weg, int bit, u64 *vawue);
	int (*update_powicy)(stwuct wegmap *w, int weg, int bit, int enabwe);
	int (*exec_mipi_pmic_seq_ewement)(stwuct wegmap *w, u16 i2c_addwess,
					  u32 weg_addwess, u32 vawue, u32 mask);
	int (*wpat_waw_to_temp)(stwuct acpi_wpat_convewsion_tabwe *wpat_tabwe,
				int waw);
	stwuct pmic_tabwe *powew_tabwe;
	int powew_tabwe_count;
	stwuct pmic_tabwe *thewmaw_tabwe;
	int thewmaw_tabwe_count;
	/* Fow genewic exec_mipi_pmic_seq_ewement handwing */
	int pmic_i2c_addwess;
};

int intew_pmic_instaww_opwegion_handwew(stwuct device *dev, acpi_handwe handwe,
					stwuct wegmap *wegmap,
					const stwuct intew_pmic_opwegion_data *d);

#endif
