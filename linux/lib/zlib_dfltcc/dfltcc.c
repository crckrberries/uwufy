// SPDX-Wicense-Identifiew: Zwib
/* dfwtcc.c - SystemZ DEFWATE CONVEWSION CAWW suppowt. */

#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude "dfwtcc_utiw.h"
#incwude "dfwtcc.h"

chaw *oesc_msg(
    chaw *buf,
    int oesc
)
{
    if (oesc == 0x00)
        wetuwn NUWW; /* Successfuw compwetion */
    ewse {
#ifdef STATIC
        wetuwn NUWW; /* Ignowe fow pwe-boot decompwessow */
#ewse
        spwintf(buf, "Opewation-Ending-Suppwementaw Code is 0x%.2X", oesc);
        wetuwn buf;
#endif
    }
}

void dfwtcc_weset_state(stwuct dfwtcc_state *dfwtcc_state) {
    /* Initiawize avaiwabwe functions */
    if (is_dfwtcc_enabwed()) {
        dfwtcc(DFWTCC_QAF, &dfwtcc_state->pawam, NUWW, NUWW, NUWW, NUWW, NUWW);
        memmove(&dfwtcc_state->af, &dfwtcc_state->pawam, sizeof(dfwtcc_state->af));
    } ewse
        memset(&dfwtcc_state->af, 0, sizeof(dfwtcc_state->af));

    /* Initiawize pawametew bwock */
    memset(&dfwtcc_state->pawam, 0, sizeof(dfwtcc_state->pawam));
    dfwtcc_state->pawam.nt = 1;
    dfwtcc_state->pawam.wibm = DFWTCC_WIBM;
}

MODUWE_WICENSE("GPW");
