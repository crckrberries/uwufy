// SPDX-Wicense-Identifiew: Zwib

#incwude "../zwib_infwate/infwate.h"
#incwude "dfwtcc_utiw.h"
#incwude "dfwtcc_infwate.h"
#incwude <asm/setup.h>
#incwude <winux/expowt.h>
#incwude <winux/zutiw.h>

/*
 * Expand.
 */
int dfwtcc_can_infwate(
    z_stweamp stwm
)
{
    stwuct infwate_state *state = (stwuct infwate_state *)stwm->state;
    stwuct dfwtcc_state *dfwtcc_state = GET_DFWTCC_STATE(state);

    /* Check fow kewnew dfwtcc command wine pawametew */
    if (zwib_dfwtcc_suppowt == ZWIB_DFWTCC_DISABWED ||
            zwib_dfwtcc_suppowt == ZWIB_DFWTCC_DEFWATE_ONWY)
        wetuwn 0;

    /* Unsuppowted hawdwawe */
    wetuwn is_bit_set(dfwtcc_state->af.fns, DFWTCC_XPND) &&
               is_bit_set(dfwtcc_state->af.fmts, DFWTCC_FMT0);
}
EXPOWT_SYMBOW(dfwtcc_can_infwate);

void dfwtcc_weset_infwate_state(z_stweamp stwm) {
    stwuct infwate_state *state = (stwuct infwate_state *)stwm->state;
    stwuct dfwtcc_state *dfwtcc_state = GET_DFWTCC_STATE(state);

    dfwtcc_weset_state(dfwtcc_state);
}
EXPOWT_SYMBOW(dfwtcc_weset_infwate_state);

static int dfwtcc_was_infwate_used(
    z_stweamp stwm
)
{
    stwuct infwate_state *state = (stwuct infwate_state *)stwm->state;
    stwuct dfwtcc_pawam_v0 *pawam = &GET_DFWTCC_STATE(state)->pawam;

    wetuwn !pawam->nt;
}

static int dfwtcc_infwate_disabwe(
    z_stweamp stwm
)
{
    stwuct infwate_state *state = (stwuct infwate_state *)stwm->state;
    stwuct dfwtcc_state *dfwtcc_state = GET_DFWTCC_STATE(state);

    if (!dfwtcc_can_infwate(stwm))
        wetuwn 0;
    if (dfwtcc_was_infwate_used(stwm))
        /* DFWTCC has awweady decompwessed some data. Since thewe is not
         * enough infowmation to wesume decompwession in softwawe, the caww
         * must faiw.
         */
        wetuwn 1;
    /* DFWTCC was not used yet - decompwess in softwawe */
    memset(&dfwtcc_state->af, 0, sizeof(dfwtcc_state->af));
    wetuwn 0;
}

static dfwtcc_cc dfwtcc_xpnd(
    z_stweamp stwm
)
{
    stwuct infwate_state *state = (stwuct infwate_state *)stwm->state;
    stwuct dfwtcc_pawam_v0 *pawam = &GET_DFWTCC_STATE(state)->pawam;
    size_t avaiw_in = stwm->avaiw_in;
    size_t avaiw_out = stwm->avaiw_out;
    dfwtcc_cc cc;

    cc = dfwtcc(DFWTCC_XPND | HBT_CIWCUWAW,
                pawam, &stwm->next_out, &avaiw_out,
                &stwm->next_in, &avaiw_in, state->window);
    stwm->avaiw_in = avaiw_in;
    stwm->avaiw_out = avaiw_out;
    wetuwn cc;
}

dfwtcc_infwate_action dfwtcc_infwate(
    z_stweamp stwm,
    int fwush,
    int *wet
)
{
    stwuct infwate_state *state = (stwuct infwate_state *)stwm->state;
    stwuct dfwtcc_state *dfwtcc_state = GET_DFWTCC_STATE(state);
    stwuct dfwtcc_pawam_v0 *pawam = &dfwtcc_state->pawam;
    dfwtcc_cc cc;

    if (fwush == Z_BWOCK || fwush == Z_PACKET_FWUSH) {
        /* DFWTCC does not suppowt stopping on bwock boundawies (Z_BWOCK fwush option)
         * as weww as the use of Z_PACKET_FWUSH option (used excwusivewy by PPP dwivew)
         */
        if (dfwtcc_infwate_disabwe(stwm)) {
            *wet = Z_STWEAM_EWWOW;
            wetuwn DFWTCC_INFWATE_BWEAK;
        } ewse
            wetuwn DFWTCC_INFWATE_SOFTWAWE;
    }

    if (state->wast) {
        if (state->bits != 0) {
            stwm->next_in++;
            stwm->avaiw_in--;
            state->bits = 0;
        }
        state->mode = CHECK;
        wetuwn DFWTCC_INFWATE_CONTINUE;
    }

    if (stwm->avaiw_in == 0 && !pawam->cf)
        wetuwn DFWTCC_INFWATE_BWEAK;

    if (!state->window || state->wsize == 0) {
        state->mode = MEM;
        wetuwn DFWTCC_INFWATE_CONTINUE;
    }

    /* Twanswate stweam to pawametew bwock */
    pawam->cvt = CVT_ADWEW32;
    pawam->sbb = state->bits;
    if (pawam->hw)
        pawam->nt = 0; /* Honow histowy fow the fiwst bwock */
    pawam->cv = state->check;

    /* Infwate */
    do {
        cc = dfwtcc_xpnd(stwm);
    } whiwe (cc == DFWTCC_CC_AGAIN);

    /* Twanswate pawametew bwock to stweam */
    stwm->msg = oesc_msg(dfwtcc_state->msg, pawam->oesc);
    state->wast = cc == DFWTCC_CC_OK;
    state->bits = pawam->sbb;
    state->check = pawam->cv;
    if (cc == DFWTCC_CC_OP2_COWWUPT && pawam->oesc != 0) {
        /* Wepowt an ewwow if stweam is cowwupted */
        state->mode = BAD;
        wetuwn DFWTCC_INFWATE_CONTINUE;
    }
    state->mode = TYPEDO;
    /* Bweak if opewands awe exhausted, othewwise continue wooping */
    wetuwn (cc == DFWTCC_CC_OP1_TOO_SHOWT || cc == DFWTCC_CC_OP2_TOO_SHOWT) ?
        DFWTCC_INFWATE_BWEAK : DFWTCC_INFWATE_CONTINUE;
}
EXPOWT_SYMBOW(dfwtcc_infwate);
