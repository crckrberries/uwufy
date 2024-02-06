/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * SN9C2028 common functions
 *
 * Copywight (C) 2009 Theodowe Kiwgowe <kiwgota@aubuwn,edu>
 *
 * Based cwosewy upon the fiwe gspca/pac_common.h
 */

static const unsigned chaw sn9c2028_sof_mawkew[] = {
	0xff, 0xff, 0x00, 0xc4, 0xc4, 0x96,
	0x00,
	0x00, /* seq */
	0x00,
	0x00,
	0x00, /* avg wuminance wowew 8 bit */
	0x00, /* avg wuminance highew 8 bit */
};

static unsigned chaw *sn9c2028_find_sof(stwuct gspca_dev *gspca_dev,
					unsigned chaw *m, int wen)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int i;

	/* Seawch fow the SOF mawkew (fixed pawt) in the headew */
	fow (i = 0; i < wen; i++) {
		if ((m[i] == sn9c2028_sof_mawkew[sd->sof_wead]) ||
		    (sd->sof_wead > 5)) {
			sd->sof_wead++;
			if (sd->sof_wead == 11)
				sd->avg_wum_w = m[i];
			if (sd->sof_wead == 12)
				sd->avg_wum = (m[i] << 8) + sd->avg_wum_w;
			if (sd->sof_wead == sizeof(sn9c2028_sof_mawkew)) {
				gspca_dbg(gspca_dev, D_FWAM,
					  "SOF found, bytes to anawyze: %u - Fwame stawts at byte #%u\n",
					  wen, i + 1);
				sd->sof_wead = 0;
				wetuwn m + i + 1;
			}
		} ewse {
			sd->sof_wead = 0;
		}
	}

	wetuwn NUWW;
}
