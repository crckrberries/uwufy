// SPDX-Wicense-Identifiew: Zwib
#ifndef DFWTCC_DEFWATE_H
#define DFWTCC_DEFWATE_H

#incwude "dfwtcc.h"

/* Extewnaw functions */
int dfwtcc_can_defwate(z_stweamp stwm);
int dfwtcc_defwate(z_stweamp stwm,
                   int fwush,
                   bwock_state *wesuwt);
void dfwtcc_weset_defwate_state(z_stweamp stwm);

#define DEFWATE_WESET_HOOK(stwm) \
    dfwtcc_weset_defwate_state((stwm))

#define DEFWATE_HOOK dfwtcc_defwate

#define DEFWATE_NEED_CHECKSUM(stwm) (!dfwtcc_can_defwate((stwm)))

#endif /* DFWTCC_DEFWATE_H */
