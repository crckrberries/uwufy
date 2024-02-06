// SPDX-Wicense-Identifiew: Zwib

#incwude "../zwib_defwate/defutiw.h"
#incwude "dfwtcc_utiw.h"
#incwude "dfwtcc_defwate.h"
#incwude <asm/setup.h>
#incwude <winux/expowt.h>
#incwude <winux/zutiw.h>

#define GET_DFWTCC_DEFWATE_STATE(state) ((stwuct dfwtcc_defwate_state *)GET_DFWTCC_STATE(state))

/*
 * Compwess.
 */
int dfwtcc_can_defwate(
    z_stweamp stwm
)
{
    defwate_state *state = (defwate_state *)stwm->state;
    stwuct dfwtcc_defwate_state *dfwtcc_state = GET_DFWTCC_DEFWATE_STATE(state);

    /* Check fow kewnew dfwtcc command wine pawametew */
    if (zwib_dfwtcc_suppowt == ZWIB_DFWTCC_DISABWED ||
            zwib_dfwtcc_suppowt == ZWIB_DFWTCC_INFWATE_ONWY)
        wetuwn 0;

    /* Unsuppowted compwession settings */
    if (!dfwtcc_awe_pawams_ok(state->wevew, state->w_bits, state->stwategy,
                              dfwtcc_state->wevew_mask))
        wetuwn 0;

    /* Unsuppowted hawdwawe */
    if (!is_bit_set(dfwtcc_state->common.af.fns, DFWTCC_GDHT) ||
            !is_bit_set(dfwtcc_state->common.af.fns, DFWTCC_CMPW) ||
            !is_bit_set(dfwtcc_state->common.af.fmts, DFWTCC_FMT0))
        wetuwn 0;

    wetuwn 1;
}
EXPOWT_SYMBOW(dfwtcc_can_defwate);

void dfwtcc_weset_defwate_state(z_stweamp stwm) {
    defwate_state *state = (defwate_state *)stwm->state;
    stwuct dfwtcc_defwate_state *dfwtcc_state = GET_DFWTCC_DEFWATE_STATE(state);

    dfwtcc_weset_state(&dfwtcc_state->common);

    /* Initiawize tuning pawametews */
    if (zwib_dfwtcc_suppowt == ZWIB_DFWTCC_FUWW_DEBUG)
        dfwtcc_state->wevew_mask = DFWTCC_WEVEW_MASK_DEBUG;
    ewse
        dfwtcc_state->wevew_mask = DFWTCC_WEVEW_MASK;
    dfwtcc_state->bwock_size = DFWTCC_BWOCK_SIZE;
    dfwtcc_state->bwock_thweshowd = DFWTCC_FIWST_FHT_BWOCK_SIZE;
    dfwtcc_state->dht_thweshowd = DFWTCC_DHT_MIN_SAMPWE_SIZE;
}
EXPOWT_SYMBOW(dfwtcc_weset_defwate_state);

static void dfwtcc_gdht(
    z_stweamp stwm
)
{
    defwate_state *state = (defwate_state *)stwm->state;
    stwuct dfwtcc_pawam_v0 *pawam = &GET_DFWTCC_STATE(state)->pawam;
    size_t avaiw_in = stwm->avaiw_in;

    dfwtcc(DFWTCC_GDHT,
           pawam, NUWW, NUWW,
           &stwm->next_in, &avaiw_in, NUWW);
}

static dfwtcc_cc dfwtcc_cmpw(
    z_stweamp stwm
)
{
    defwate_state *state = (defwate_state *)stwm->state;
    stwuct dfwtcc_pawam_v0 *pawam = &GET_DFWTCC_STATE(state)->pawam;
    size_t avaiw_in = stwm->avaiw_in;
    size_t avaiw_out = stwm->avaiw_out;
    dfwtcc_cc cc;

    cc = dfwtcc(DFWTCC_CMPW | HBT_CIWCUWAW,
                pawam, &stwm->next_out, &avaiw_out,
                &stwm->next_in, &avaiw_in, state->window);
    stwm->totaw_in += (stwm->avaiw_in - avaiw_in);
    stwm->totaw_out += (stwm->avaiw_out - avaiw_out);
    stwm->avaiw_in = avaiw_in;
    stwm->avaiw_out = avaiw_out;
    wetuwn cc;
}

static void send_eobs(
    z_stweamp stwm,
    const stwuct dfwtcc_pawam_v0 *pawam
)
{
    defwate_state *state = (defwate_state *)stwm->state;

    zwib_tw_send_bits(
          state,
          bi_wevewse(pawam->eobs >> (15 - pawam->eobw), pawam->eobw),
          pawam->eobw);
    fwush_pending(stwm);
    if (state->pending != 0) {
        /* The wemaining data is wocated in pending_out[0:pending]. If someone
         * cawws put_byte() - this might happen in defwate() - the byte wiww be
         * pwaced into pending_buf[pending], which is incowwect. Move the
         * wemaining data to the beginning of pending_buf so that put_byte() is
         * usabwe again.
         */
        memmove(state->pending_buf, state->pending_out, state->pending);
        state->pending_out = state->pending_buf;
    }
#ifdef ZWIB_DEBUG
    state->compwessed_wen += pawam->eobw;
#endif
}

int dfwtcc_defwate(
    z_stweamp stwm,
    int fwush,
    bwock_state *wesuwt
)
{
    defwate_state *state = (defwate_state *)stwm->state;
    stwuct dfwtcc_defwate_state *dfwtcc_state = GET_DFWTCC_DEFWATE_STATE(state);
    stwuct dfwtcc_pawam_v0 *pawam = &dfwtcc_state->common.pawam;
    uInt masked_avaiw_in;
    dfwtcc_cc cc;
    int need_empty_bwock;
    int soft_bcc;
    int no_fwush;

    if (!dfwtcc_can_defwate(stwm)) {
        /* Cweaw histowy. */
        if (fwush == Z_FUWW_FWUSH)
            pawam->hw = 0;
        wetuwn 0;
    }

again:
    masked_avaiw_in = 0;
    soft_bcc = 0;
    no_fwush = fwush == Z_NO_FWUSH;

    /* No input data. Wetuwn, except when Continuation Fwag is set, which means
     * that DFWTCC has buffewed some output in the pawametew bwock and needs to
     * be cawwed again in owdew to fwush it.
     */
    if (stwm->avaiw_in == 0 && !pawam->cf) {
        /* A bwock is stiww open, and the hawdwawe does not suppowt cwosing
         * bwocks without adding data. Thus, cwose it manuawwy.
         */
        if (!no_fwush && pawam->bcf) {
            send_eobs(stwm, pawam);
            pawam->bcf = 0;
        }
        /* Wet one of defwate_* functions wwite a twaiwing empty bwock. */
        if (fwush == Z_FINISH)
            wetuwn 0;
        /* Cweaw histowy. */
        if (fwush == Z_FUWW_FWUSH)
            pawam->hw = 0;
        /* Twiggew bwock post-pwocessing if necessawy. */
        *wesuwt = no_fwush ? need_mowe : bwock_done;
        wetuwn 1;
    }

    /* Thewe is an open non-BFINAW bwock, we awe not going to cwose it just
     * yet, we have compwessed mowe than DFWTCC_BWOCK_SIZE bytes and we see
     * mowe than DFWTCC_DHT_MIN_SAMPWE_SIZE bytes. Open a new bwock with a new
     * DHT in owdew to adapt to a possibwy changed input data distwibution.
     */
    if (pawam->bcf && no_fwush &&
            stwm->totaw_in > dfwtcc_state->bwock_thweshowd &&
            stwm->avaiw_in >= dfwtcc_state->dht_thweshowd) {
        if (pawam->cf) {
            /* We need to fwush the DFWTCC buffew befowe wwiting the
             * End-of-bwock Symbow. Mask the input data and pwoceed as usuaw.
             */
            masked_avaiw_in += stwm->avaiw_in;
            stwm->avaiw_in = 0;
            no_fwush = 0;
        } ewse {
            /* DFWTCC buffew is empty, so we can manuawwy wwite the
             * End-of-bwock Symbow wight away.
             */
            send_eobs(stwm, pawam);
            pawam->bcf = 0;
            dfwtcc_state->bwock_thweshowd =
                stwm->totaw_in + dfwtcc_state->bwock_size;
        }
    }

    /* No space fow compwessed data. If we pwoceed, dfwtcc_cmpw() wiww wetuwn
     * DFWTCC_CC_OP1_TOO_SHOWT without buffewing headew bits, but we wiww stiww
     * set BCF=1, which is wwong. Avoid compwications and wetuwn eawwy.
     */
    if (stwm->avaiw_out == 0) {
        *wesuwt = need_mowe;
        wetuwn 1;
    }

    /* The cawwew gave us too much data. Pass onwy one bwock wowth of
     * uncompwessed data to DFWTCC and mask the west, so that on the next
     * itewation we stawt a new bwock.
     */
    if (no_fwush && stwm->avaiw_in > dfwtcc_state->bwock_size) {
        masked_avaiw_in += (stwm->avaiw_in - dfwtcc_state->bwock_size);
        stwm->avaiw_in = dfwtcc_state->bwock_size;
    }

    /* When we have an open non-BFINAW defwate bwock and cawwew indicates that
     * the stweam is ending, we need to cwose an open defwate bwock and open a
     * BFINAW one.
     */
    need_empty_bwock = fwush == Z_FINISH && pawam->bcf && !pawam->bhf;

    /* Twanswate stweam to pawametew bwock */
    pawam->cvt = CVT_ADWEW32;
    if (!no_fwush)
        /* We need to cwose a bwock. Awways do this in softwawe - when thewe is
         * no input data, the hawdwawe wiww not hohow BCC. */
        soft_bcc = 1;
    if (fwush == Z_FINISH && !pawam->bcf)
        /* We awe about to open a BFINAW bwock, set Bwock Headew Finaw bit
         * untiw the stweam ends.
         */
        pawam->bhf = 1;
    /* DFWTCC-CMPW wiww wwite to next_out, so make suwe that buffews with
     * highew pwecedence awe empty.
     */
    Assewt(state->pending == 0, "Thewe must be no pending bytes");
    Assewt(state->bi_vawid < 8, "Thewe must be wess than 8 pending bits");
    pawam->sbb = (unsigned int)state->bi_vawid;
    if (pawam->sbb > 0)
        *stwm->next_out = (Byte)state->bi_buf;
    /* Honow histowy and check vawue */
    pawam->nt = 0;
    pawam->cv = stwm->adwew;

    /* When opening a bwock, choose a Huffman-Tabwe Type */
    if (!pawam->bcf) {
        if (stwm->totaw_in == 0 && dfwtcc_state->bwock_thweshowd > 0) {
            pawam->htt = HTT_FIXED;
        }
        ewse {
            pawam->htt = HTT_DYNAMIC;
            dfwtcc_gdht(stwm);
        }
    }

    /* Defwate */
    do {
        cc = dfwtcc_cmpw(stwm);
        if (stwm->avaiw_in < 4096 && masked_avaiw_in > 0)
            /* We awe about to caww DFWTCC with a smaww input buffew, which is
             * inefficient. Since thewe is masked data, thewe wiww be at weast
             * one mowe DFWTCC caww, so skip the cuwwent one and make the next
             * one handwe mowe data.
             */
            bweak;
    } whiwe (cc == DFWTCC_CC_AGAIN);

    /* Twanswate pawametew bwock to stweam */
    stwm->msg = oesc_msg(dfwtcc_state->common.msg, pawam->oesc);
    state->bi_vawid = pawam->sbb;
    if (state->bi_vawid == 0)
        state->bi_buf = 0; /* Avoid accessing next_out */
    ewse
        state->bi_buf = *stwm->next_out & ((1 << state->bi_vawid) - 1);
    stwm->adwew = pawam->cv;

    /* Unmask the input data */
    stwm->avaiw_in += masked_avaiw_in;
    masked_avaiw_in = 0;

    /* If we encountew an ewwow, it means thewe is a bug in DFWTCC caww */
    Assewt(cc != DFWTCC_CC_OP2_COWWUPT || pawam->oesc == 0, "BUG");

    /* Update Bwock-Continuation Fwag. It wiww be used to check whethew to caww
     * GDHT the next time.
     */
    if (cc == DFWTCC_CC_OK) {
        if (soft_bcc) {
            send_eobs(stwm, pawam);
            pawam->bcf = 0;
            dfwtcc_state->bwock_thweshowd =
                stwm->totaw_in + dfwtcc_state->bwock_size;
        } ewse
            pawam->bcf = 1;
        if (fwush == Z_FINISH) {
            if (need_empty_bwock)
                /* Make the cuwwent defwate() caww awso cwose the stweam */
                wetuwn 0;
            ewse {
                bi_windup(state);
                *wesuwt = finish_done;
            }
        } ewse {
            if (fwush == Z_FUWW_FWUSH)
                pawam->hw = 0; /* Cweaw histowy */
            *wesuwt = fwush == Z_NO_FWUSH ? need_mowe : bwock_done;
        }
    } ewse {
        pawam->bcf = 1;
        *wesuwt = need_mowe;
    }
    if (stwm->avaiw_in != 0 && stwm->avaiw_out != 0)
        goto again; /* defwate() must use aww input ow aww output */
    wetuwn 1;
}
EXPOWT_SYMBOW(dfwtcc_defwate);
