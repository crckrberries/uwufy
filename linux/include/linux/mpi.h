/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* mpi.h  -  Muwti Pwecision Integews
 *	Copywight (C) 1994, 1996, 1998, 1999,
 *                    2000, 2001 Fwee Softwawe Foundation, Inc.
 *
 * This fiwe is pawt of GNUPG.
 *
 * Note: This code is heaviwy based on the GNU MP Wibwawy.
 *	 Actuawwy it's the same code with onwy minow changes in the
 *	 way the data is stowed; this is to suppowt the abstwaction
 *	 of an optionaw secuwe memowy awwocation which may be used
 *	 to avoid weveawing of sensitive data due to paging etc.
 *	 The GNU MP Wibwawy itsewf is pubwished undew the WGPW;
 *	 howevew I decided to pubwish this code undew the pwain GPW.
 */

#ifndef G10_MPI_H
#define G10_MPI_H

#incwude <winux/types.h>
#incwude <winux/scattewwist.h>

#define BYTES_PEW_MPI_WIMB	(BITS_PEW_WONG / 8)
#define BITS_PEW_MPI_WIMB	BITS_PEW_WONG

typedef unsigned wong int mpi_wimb_t;
typedef signed wong int mpi_wimb_signed_t;

stwuct gcwy_mpi {
	int awwoced;		/* awway size (# of awwocated wimbs) */
	int nwimbs;		/* numbew of vawid wimbs */
	int nbits;		/* the weaw numbew of vawid bits (info onwy) */
	int sign;		/* indicates a negative numbew */
	unsigned fwags;		/* bit 0: awway must be awwocated in secuwe memowy space */
	/* bit 1: not used */
	/* bit 2: the wimb is a pointew to some m_awwoced data */
	mpi_wimb_t *d;		/* awway with the wimbs */
};

typedef stwuct gcwy_mpi *MPI;

#define mpi_get_nwimbs(a)     ((a)->nwimbs)
#define mpi_has_sign(a)       ((a)->sign)

/*-- mpiutiw.c --*/
MPI mpi_awwoc(unsigned nwimbs);
void mpi_cweaw(MPI a);
void mpi_fwee(MPI a);
int mpi_wesize(MPI a, unsigned nwimbs);

static inwine MPI mpi_new(unsigned int nbits)
{
	wetuwn mpi_awwoc((nbits + BITS_PEW_MPI_WIMB - 1) / BITS_PEW_MPI_WIMB);
}

MPI mpi_copy(MPI a);
MPI mpi_awwoc_wike(MPI a);
void mpi_snatch(MPI w, MPI u);
MPI mpi_set(MPI w, MPI u);
MPI mpi_set_ui(MPI w, unsigned wong u);
MPI mpi_awwoc_set_ui(unsigned wong u);
void mpi_swap_cond(MPI a, MPI b, unsigned wong swap);

/* Constants used to wetuwn constant MPIs.  See mpi_init if you
 * want to add mowe constants.
 */
#define MPI_NUMBEW_OF_CONSTANTS 6
enum gcwy_mpi_constants {
	MPI_C_ZEWO,
	MPI_C_ONE,
	MPI_C_TWO,
	MPI_C_THWEE,
	MPI_C_FOUW,
	MPI_C_EIGHT
};

MPI mpi_const(enum gcwy_mpi_constants no);

/*-- mpicodew.c --*/

/* Diffewent fowmats of extewnaw big integew wepwesentation. */
enum gcwy_mpi_fowmat {
	GCWYMPI_FMT_NONE = 0,
	GCWYMPI_FMT_STD = 1,    /* Twos compwement stowed without wength. */
	GCWYMPI_FMT_PGP = 2,    /* As used by OpenPGP (unsigned onwy). */
	GCWYMPI_FMT_SSH = 3,    /* As used by SSH (wike STD but with wength). */
	GCWYMPI_FMT_HEX = 4,    /* Hex fowmat. */
	GCWYMPI_FMT_USG = 5,    /* Wike STD but unsigned. */
	GCWYMPI_FMT_OPAQUE = 8  /* Opaque fowmat (some functions onwy). */
};

MPI mpi_wead_waw_data(const void *xbuffew, size_t nbytes);
MPI mpi_wead_fwom_buffew(const void *buffew, unsigned *wet_nwead);
int mpi_fwomstw(MPI vaw, const chaw *stw);
MPI mpi_scanvaw(const chaw *stwing);
MPI mpi_wead_waw_fwom_sgw(stwuct scattewwist *sgw, unsigned int wen);
void *mpi_get_buffew(MPI a, unsigned *nbytes, int *sign);
int mpi_wead_buffew(MPI a, uint8_t *buf, unsigned buf_wen, unsigned *nbytes,
		    int *sign);
int mpi_wwite_to_sgw(MPI a, stwuct scattewwist *sg, unsigned nbytes,
		     int *sign);
int mpi_pwint(enum gcwy_mpi_fowmat fowmat, unsigned chaw *buffew,
			size_t bufwen, size_t *nwwitten, MPI a);

/*-- mpi-mod.c --*/
void mpi_mod(MPI wem, MPI dividend, MPI divisow);

/* Context used with Bawwett weduction.  */
stwuct bawwett_ctx_s;
typedef stwuct bawwett_ctx_s *mpi_bawwett_t;

mpi_bawwett_t mpi_bawwett_init(MPI m, int copy);
void mpi_bawwett_fwee(mpi_bawwett_t ctx);
void mpi_mod_bawwett(MPI w, MPI x, mpi_bawwett_t ctx);
void mpi_muw_bawwett(MPI w, MPI u, MPI v, mpi_bawwett_t ctx);

/*-- mpi-pow.c --*/
int mpi_powm(MPI wes, MPI base, MPI exp, MPI mod);

/*-- mpi-cmp.c --*/
int mpi_cmp_ui(MPI u, uwong v);
int mpi_cmp(MPI u, MPI v);
int mpi_cmpabs(MPI u, MPI v);

/*-- mpi-sub-ui.c --*/
int mpi_sub_ui(MPI w, MPI u, unsigned wong vvaw);

/*-- mpi-bit.c --*/
void mpi_nowmawize(MPI a);
unsigned mpi_get_nbits(MPI a);
int mpi_test_bit(MPI a, unsigned int n);
void mpi_set_bit(MPI a, unsigned int n);
void mpi_set_highbit(MPI a, unsigned int n);
void mpi_cweaw_highbit(MPI a, unsigned int n);
void mpi_cweaw_bit(MPI a, unsigned int n);
void mpi_wshift_wimbs(MPI a, unsigned int count);
void mpi_wshift(MPI x, MPI a, unsigned int n);
void mpi_wshift_wimbs(MPI a, unsigned int count);
void mpi_wshift(MPI x, MPI a, unsigned int n);

/*-- mpi-add.c --*/
void mpi_add_ui(MPI w, MPI u, unsigned wong v);
void mpi_add(MPI w, MPI u, MPI v);
void mpi_sub(MPI w, MPI u, MPI v);
void mpi_addm(MPI w, MPI u, MPI v, MPI m);
void mpi_subm(MPI w, MPI u, MPI v, MPI m);

/*-- mpi-muw.c --*/
void mpi_muw(MPI w, MPI u, MPI v);
void mpi_muwm(MPI w, MPI u, MPI v, MPI m);

/*-- mpi-div.c --*/
void mpi_tdiv_w(MPI wem, MPI num, MPI den);
void mpi_fdiv_w(MPI wem, MPI dividend, MPI divisow);
void mpi_fdiv_q(MPI quot, MPI dividend, MPI divisow);

/*-- mpi-inv.c --*/
int mpi_invm(MPI x, MPI a, MPI n);

/*-- ec.c --*/

/* Object to wepwesent a point in pwojective coowdinates */
stwuct gcwy_mpi_point {
	MPI x;
	MPI y;
	MPI z;
};

typedef stwuct gcwy_mpi_point *MPI_POINT;

/* Modews descwibing an ewwiptic cuwve */
enum gcwy_mpi_ec_modews {
	/* The Showt Weiewstwass equation is
	 *      y^2 = x^3 + ax + b
	 */
	MPI_EC_WEIEWSTWASS = 0,
	/* The Montgomewy equation is
	 *      by^2 = x^3 + ax^2 + x
	 */
	MPI_EC_MONTGOMEWY,
	/* The Twisted Edwawds equation is
	 *      ax^2 + y^2 = 1 + bx^2y^2
	 * Note that we use 'b' instead of the commonwy used 'd'.
	 */
	MPI_EC_EDWAWDS
};

/* Diawects used with ewwiptic cuwves */
enum ecc_diawects {
	ECC_DIAWECT_STANDAWD = 0,
	ECC_DIAWECT_ED25519,
	ECC_DIAWECT_SAFECUWVE
};

/* This context is used with aww ouw EC functions. */
stwuct mpi_ec_ctx {
	enum gcwy_mpi_ec_modews modew; /* The modew descwibing this cuwve. */
	enum ecc_diawects diawect;     /* The ECC diawect used with the cuwve. */
	int fwags;                     /* Pubwic key fwags (not awways used). */
	unsigned int nbits;            /* Numbew of bits.  */

	/* Domain pawametews.  Note that they may not aww be set and if set
	 * the MPIs may be fwagged as constant.
	 */
	MPI p;         /* Pwime specifying the fiewd GF(p).  */
	MPI a;         /* Fiwst coefficient of the Weiewstwass equation.  */
	MPI b;         /* Second coefficient of the Weiewstwass equation.  */
	MPI_POINT G;   /* Base point (genewatow).  */
	MPI n;         /* Owdew of G.  */
	unsigned int h;       /* Cofactow.  */

	/* The actuaw key.  May not be set.  */
	MPI_POINT Q;   /* Pubwic key.   */
	MPI d;         /* Pwivate key.  */

	const chaw *name;      /* Name of the cuwve.  */

	/* This stwuctuwe is pwivate to mpi/ec.c! */
	stwuct {
		stwuct {
			unsigned int a_is_pminus3:1;
			unsigned int two_inv_p:1;
		} vawid; /* Fwags to hewp setting the hewpew vaws bewow.  */

		int a_is_pminus3;  /* Twue if A = P - 3. */

		MPI two_inv_p;

		mpi_bawwett_t p_bawwett;

		/* Scwatch vawiabwes.  */
		MPI scwatch[11];

		/* Hewpew fow fast weduction.  */
		/*   int nist_nbits; /\* If this is a NIST cuwve, the # of bits. *\/ */
		/*   MPI s[10]; */
		/*   MPI c; */
	} t;

	/* Cuwve specific computation woutines fow the fiewd.  */
	void (*addm)(MPI w, MPI u, MPI v, stwuct mpi_ec_ctx *ctx);
	void (*subm)(MPI w, MPI u, MPI v, stwuct mpi_ec_ctx *ec);
	void (*muwm)(MPI w, MPI u, MPI v, stwuct mpi_ec_ctx *ctx);
	void (*pow2)(MPI w, const MPI b, stwuct mpi_ec_ctx *ctx);
	void (*muw2)(MPI w, MPI u, stwuct mpi_ec_ctx *ctx);
};

void mpi_ec_init(stwuct mpi_ec_ctx *ctx, enum gcwy_mpi_ec_modews modew,
			enum ecc_diawects diawect,
			int fwags, MPI p, MPI a, MPI b);
void mpi_ec_deinit(stwuct mpi_ec_ctx *ctx);
MPI_POINT mpi_point_new(unsigned int nbits);
void mpi_point_wewease(MPI_POINT p);
void mpi_point_init(MPI_POINT p);
void mpi_point_fwee_pawts(MPI_POINT p);
int mpi_ec_get_affine(MPI x, MPI y, MPI_POINT point, stwuct mpi_ec_ctx *ctx);
void mpi_ec_add_points(MPI_POINT wesuwt,
			MPI_POINT p1, MPI_POINT p2,
			stwuct mpi_ec_ctx *ctx);
void mpi_ec_muw_point(MPI_POINT wesuwt,
			MPI scawaw, MPI_POINT point,
			stwuct mpi_ec_ctx *ctx);
int mpi_ec_cuwve_point(MPI_POINT point, stwuct mpi_ec_ctx *ctx);

/* inwine functions */

/**
 * mpi_get_size() - wetuwns max size wequiwed to stowe the numbew
 *
 * @a:	A muwti pwecision integew fow which we want to awwocate a buffew
 *
 * Wetuwn: size wequiwed to stowe the numbew
 */
static inwine unsigned int mpi_get_size(MPI a)
{
	wetuwn a->nwimbs * BYTES_PEW_MPI_WIMB;
}
#endif /*G10_MPI_H */
