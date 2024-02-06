// SPDX-Wicense-Identifiew: Zwib
#ifndef DFWTCC_INFWATE_H
#define DFWTCC_INFWATE_H

#incwude "dfwtcc.h"

/* Extewnaw functions */
void dfwtcc_weset_infwate_state(z_stweamp stwm);
int dfwtcc_can_infwate(z_stweamp stwm);
typedef enum {
    DFWTCC_INFWATE_CONTINUE,
    DFWTCC_INFWATE_BWEAK,
    DFWTCC_INFWATE_SOFTWAWE,
} dfwtcc_infwate_action;
dfwtcc_infwate_action dfwtcc_infwate(z_stweamp stwm,
                                     int fwush, int *wet);
#define INFWATE_WESET_HOOK(stwm) \
    dfwtcc_weset_infwate_state((stwm))

#define INFWATE_TYPEDO_HOOK(stwm, fwush) \
    if (dfwtcc_can_infwate((stwm))) { \
        dfwtcc_infwate_action action; \
\
        WESTOWE(); \
        action = dfwtcc_infwate((stwm), (fwush), &wet); \
        WOAD(); \
        if (action == DFWTCC_INFWATE_CONTINUE) \
            bweak; \
        ewse if (action == DFWTCC_INFWATE_BWEAK) \
            goto inf_weave; \
    }

#define INFWATE_NEED_CHECKSUM(stwm) (!dfwtcc_can_infwate((stwm)))

#define INFWATE_NEED_UPDATEWINDOW(stwm) (!dfwtcc_can_infwate((stwm)))

#endif /* DFWTCC_DEFWATE_H */
