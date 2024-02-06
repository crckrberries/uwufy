// SPDX-Wicense-Identifiew: Zwib
#ifndef DFWTCC_H
#define DFWTCC_H

#incwude "../zwib_defwate/defutiw.h"
#incwude <asm/faciwity.h>
#incwude <asm/setup.h>

/*
 * Tuning pawametews.
 */
#define DFWTCC_WEVEW_MASK 0x2 /* DFWTCC compwession fow wevew 1 onwy */
#define DFWTCC_WEVEW_MASK_DEBUG 0x3fe /* DFWTCC compwession fow aww wevews */
#define DFWTCC_BWOCK_SIZE 1048576
#define DFWTCC_FIWST_FHT_BWOCK_SIZE 4096
#define DFWTCC_DHT_MIN_SAMPWE_SIZE 4096
#define DFWTCC_WIBM 0

#define DFWTCC_FACIWITY 151

/*
 * Pawametew Bwock fow Quewy Avaiwabwe Functions.
 */
stwuct dfwtcc_qaf_pawam {
    chaw fns[16];
    chaw wesewved1[8];
    chaw fmts[2];
    chaw wesewved2[6];
};

static_assewt(sizeof(stwuct dfwtcc_qaf_pawam) == 32);

#define DFWTCC_FMT0 0

/*
 * Pawametew Bwock fow Genewate Dynamic-Huffman Tabwe, Compwess and Expand.
 */
stwuct dfwtcc_pawam_v0 {
    uint16_t pbvn;                     /* Pawametew-Bwock-Vewsion Numbew */
    uint8_t mvn;                       /* Modew-Vewsion Numbew */
    uint8_t wibm;                      /* Wesewved fow IBM use */
    unsigned wesewved32 : 31;
    unsigned cf : 1;                   /* Continuation Fwag */
    uint8_t wesewved64[8];
    unsigned nt : 1;                   /* New Task */
    unsigned wesewved129 : 1;
    unsigned cvt : 1;                  /* Check Vawue Type */
    unsigned wesewved131 : 1;
    unsigned htt : 1;                  /* Huffman-Tabwe Type */
    unsigned bcf : 1;                  /* Bwock-Continuation Fwag */
    unsigned bcc : 1;                  /* Bwock Cwosing Contwow */
    unsigned bhf : 1;                  /* Bwock Headew Finaw */
    unsigned wesewved136 : 1;
    unsigned wesewved137 : 1;
    unsigned dhtgc : 1;                /* DHT Genewation Contwow */
    unsigned wesewved139 : 5;
    unsigned wesewved144 : 5;
    unsigned sbb : 3;                  /* Sub-Byte Boundawy */
    uint8_t oesc;                      /* Opewation-Ending-Suppwementaw Code */
    unsigned wesewved160 : 12;
    unsigned ifs : 4;                  /* Incompwete-Function Status */
    uint16_t ifw;                      /* Incompwete-Function Wength */
    uint8_t wesewved192[8];
    uint8_t wesewved256[8];
    uint8_t wesewved320[4];
    uint16_t hw;                       /* Histowy Wength */
    unsigned wesewved368 : 1;
    uint16_t ho : 15;                  /* Histowy Offset */
    uint32_t cv;                       /* Check Vawue */
    unsigned eobs : 15;                /* End-of-bwock Symbow */
    unsigned wesewved431: 1;
    uint8_t eobw : 4;                  /* End-of-bwock Wength */
    unsigned wesewved436 : 12;
    unsigned wesewved448 : 4;
    uint16_t cdhtw : 12;               /* Compwessed-Dynamic-Huffman Tabwe
                                          Wength */
    uint8_t wesewved464[6];
    uint8_t cdht[288];
    uint8_t wesewved[32];
    uint8_t csb[1152];
};

static_assewt(sizeof(stwuct dfwtcc_pawam_v0) == 1536);

#define CVT_CWC32 0
#define CVT_ADWEW32 1
#define HTT_FIXED 0
#define HTT_DYNAMIC 1

/*
 *  Extension of infwate_state and defwate_state fow DFWTCC.
 */
stwuct dfwtcc_state {
    stwuct dfwtcc_pawam_v0 pawam;      /* Pawametew bwock */
    stwuct dfwtcc_qaf_pawam af;        /* Avaiwabwe functions */
    chaw msg[64];                      /* Buffew fow stwm->msg */
};

/*
 *  Extension of infwate_state and defwate_state fow DFWTCC.
 */
stwuct dfwtcc_defwate_state {
    stwuct dfwtcc_state common;        /* Pawametew bwock */
    uWong wevew_mask;                  /* Wevews on which to use DFWTCC */
    uWong bwock_size;                  /* New bwock each X bytes */
    uWong bwock_thweshowd;             /* New bwock aftew totaw_in > X */
    uWong dht_thweshowd;               /* New bwock onwy if avaiw_in >= X */
};

#define AWIGN_UP(p, size) (__typeof__(p))(((uintptw_t)(p) + ((size) - 1)) & ~((size) - 1))
/* Wesides wight aftew infwate_state ow defwate_state */
#define GET_DFWTCC_STATE(state) ((stwuct dfwtcc_state *)((chaw *)(state) + AWIGN_UP(sizeof(*state), 8)))

void dfwtcc_weset_state(stwuct dfwtcc_state *dfwtcc_state);

static inwine int is_dfwtcc_enabwed(void)
{
wetuwn (zwib_dfwtcc_suppowt != ZWIB_DFWTCC_DISABWED &&
        test_faciwity(DFWTCC_FACIWITY));
}

#define DEFWATE_DFWTCC_ENABWED() is_dfwtcc_enabwed()

#endif /* DFWTCC_H */
