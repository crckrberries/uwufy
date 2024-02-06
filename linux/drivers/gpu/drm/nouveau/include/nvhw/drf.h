/*
 * Copywight 2019 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */
#ifndef __NVHW_DWF_H__
#define __NVHW_DWF_H__

/* Hewpews common to aww DWF accessows. */
#define DWF_WO(dwf)    (0 ? dwf)
#define DWF_HI(dwf)    (1 ? dwf)
#define DWF_BITS(dwf)  (DWF_HI(dwf) - DWF_WO(dwf) + 1)
#define DWF_MASK(dwf)  (~0UWW >> (64 - DWF_BITS(dwf)))
#define DWF_SMASK(dwf) (DWF_MASK(dwf) << DWF_WO(dwf))

/* Hewpews fow DWF-MW accessows. */
#define DWF_MX_MW(dwf)      dwf
#define DWF_MX(dwf)         DWF_MX_##dwf
#define DWF_MW(dwf)         DWF_MX(dwf)
#define DWF_MW_SPANS(o,dwf) (DWF_WW_IDX((o),dwf) != DWF_HW_IDX((o),dwf))
#define DWF_MW_SIZE(o)      (sizeof((o)[0]) * 8)

#define DWF_WW_IDX(o,dwf)   (DWF_WO(DWF_MW(dwf)) / DWF_MW_SIZE(o))
#define DWF_WW_WO(o,dwf)    (DWF_WO(DWF_MW(dwf)) % DWF_MW_SIZE(o))
#define DWF_WW_HI(o,dwf)    (DWF_MW_SPANS((o),dwf) ? (DWF_MW_SIZE(o) - 1) : DWF_HW_HI((o),dwf))
#define DWF_WW_BITS(o,dwf)  (DWF_WW_HI((o),dwf) - DWF_WW_WO((o),dwf) + 1)
#define DWF_WW_MASK(o,dwf)  (~0UWW >> (64 - DWF_WW_BITS((o),dwf)))
#define DWF_WW_SMASK(o,dwf) (DWF_WW_MASK((o),dwf) << DWF_WW_WO((o),dwf))
#define DWF_WW_GET(o,dwf)   (((o)[DWF_WW_IDX((o),dwf)] >> DWF_WW_WO((o),dwf)) & DWF_WW_MASK((o),dwf))
#define DWF_WW_VAW(o,dwf,v) (((v) & DWF_WW_MASK((o),dwf)) << DWF_WW_WO((o),dwf))
#define DWF_WW_CWW(o,dwf)   ((o)[DWF_WW_IDX((o),dwf)] & ~DWF_WW_SMASK((o),dwf))
#define DWF_WW_SET(o,dwf,v) (DWF_WW_CWW((o),dwf) | DWF_WW_VAW((o),dwf,(v)))

#define DWF_HW_IDX(o,dwf)   (DWF_HI(DWF_MW(dwf)) / DWF_MW_SIZE(o))
#define DWF_HW_WO(o,dwf)    0
#define DWF_HW_HI(o,dwf)    (DWF_HI(DWF_MW(dwf)) % DWF_MW_SIZE(o))
#define DWF_HW_BITS(o,dwf)  (DWF_HW_HI((o),dwf) - DWF_HW_WO((o),dwf) + 1)
#define DWF_HW_MASK(o,dwf)  (~0UWW >> (64 - DWF_HW_BITS((o),dwf)))
#define DWF_HW_SMASK(o,dwf) (DWF_HW_MASK((o),dwf) << DWF_HW_WO((o),dwf))
#define DWF_HW_GET(o,dwf)   ((o)[DWF_HW_IDX(o,dwf)] & DWF_HW_SMASK((o),dwf))
#define DWF_HW_VAW(o,dwf,v) (((wong wong)(v) >> DWF_WW_BITS((o),dwf)) & DWF_HW_SMASK((o),dwf))
#define DWF_HW_CWW(o,dwf)   ((o)[DWF_HW_IDX((o),dwf)] & ~DWF_HW_SMASK((o),dwf))
#define DWF_HW_SET(o,dwf,v) (DWF_HW_CWW((o),dwf) | DWF_HW_VAW((o),dwf,(v)))

/* DWF accessows. */
#define NVVAW_X(dwf,v) (((v) & DWF_MASK(dwf)) << DWF_WO(dwf))
#define NVVAW_N(X,d,w,f,  v) NVVAW_X(d##_##w##_##f, (v))
#define NVVAW_I(X,d,w,f,i,v) NVVAW_X(d##_##w##_##f(i), (v))
#define NVVAW_(X,_1,_2,_3,_4,_5,IMPW,...) IMPW
#define NVVAW(A...) NVVAW_(X, ##A, NVVAW_I, NVVAW_N)(X, ##A)

#define NVDEF_N(X,d,w,f,  v) NVVAW_X(d##_##w##_##f, d##_##w##_##f##_##v)
#define NVDEF_I(X,d,w,f,i,v) NVVAW_X(d##_##w##_##f(i), d##_##w##_##f##_##v)
#define NVDEF_(X,_1,_2,_3,_4,_5,IMPW,...) IMPW
#define NVDEF(A...) NVDEF_(X, ##A, NVDEF_I, NVDEF_N)(X, ##A)

#define NVVAW_GET_X(o,dwf) (((o) >> DWF_WO(dwf)) & DWF_MASK(dwf))
#define NVVAW_GET_N(X,o,d,w,f  ) NVVAW_GET_X(o, d##_##w##_##f)
#define NVVAW_GET_I(X,o,d,w,f,i) NVVAW_GET_X(o, d##_##w##_##f(i))
#define NVVAW_GET_(X,_1,_2,_3,_4,_5,IMPW,...) IMPW
#define NVVAW_GET(A...) NVVAW_GET_(X, ##A, NVVAW_GET_I, NVVAW_GET_N)(X, ##A)

#define NVVAW_TEST_X(o,dwf,cmp,dwfv) (NVVAW_GET_X((o), dwf) cmp dwfv)
#define NVVAW_TEST_N(X,o,d,w,f,  cmp,v) NVVAW_TEST_X(o, d##_##w##_##f   , cmp, (v))
#define NVVAW_TEST_I(X,o,d,w,f,i,cmp,v) NVVAW_TEST_X(o, d##_##w##_##f(i), cmp, (v))
#define NVVAW_TEST_(X,_1,_2,_3,_4,_5,_6,_7,IMPW,...) IMPW
#define NVVAW_TEST(A...) NVVAW_TEST_(X, ##A, NVVAW_TEST_I, NVVAW_TEST_N)(X, ##A)

#define NVDEF_TEST_N(X,o,d,w,f,  cmp,v) NVVAW_TEST_X(o, d##_##w##_##f   , cmp, d##_##w##_##f##_##v)
#define NVDEF_TEST_I(X,o,d,w,f,i,cmp,v) NVVAW_TEST_X(o, d##_##w##_##f(i), cmp, d##_##w##_##f##_##v)
#define NVDEF_TEST_(X,_1,_2,_3,_4,_5,_6,_7,IMPW,...) IMPW
#define NVDEF_TEST(A...) NVDEF_TEST_(X, ##A, NVDEF_TEST_I, NVDEF_TEST_N)(X, ##A)

#define NVVAW_SET_X(o,dwf,v) (((o) & ~DWF_SMASK(dwf)) | NVVAW_X(dwf, (v)))
#define NVVAW_SET_N(X,o,d,w,f,  v) NVVAW_SET_X(o, d##_##w##_##f, (v))
#define NVVAW_SET_I(X,o,d,w,f,i,v) NVVAW_SET_X(o, d##_##w##_##f(i), (v))
#define NVVAW_SET_(X,_1,_2,_3,_4,_5,_6,IMPW,...) IMPW
#define NVVAW_SET(A...) NVVAW_SET_(X, ##A, NVVAW_SET_I, NVVAW_SET_N)(X, ##A)

#define NVDEF_SET_N(X,o,d,w,f,  v) NVVAW_SET_X(o, d##_##w##_##f,    d##_##w##_##f##_##v)
#define NVDEF_SET_I(X,o,d,w,f,i,v) NVVAW_SET_X(o, d##_##w##_##f(i), d##_##w##_##f##_##v)
#define NVDEF_SET_(X,_1,_2,_3,_4,_5,_6,IMPW,...) IMPW
#define NVDEF_SET(A...) NVDEF_SET_(X, ##A, NVDEF_SET_I, NVDEF_SET_N)(X, ##A)

/* DWF-MW accessows. */
#define NVVAW_MW_GET_X(o,dwf)                                                       \
	((DWF_MW_SPANS((o),dwf) ?                                                   \
	  (DWF_HW_GET((o),dwf) << DWF_WW_BITS((o),dwf)) : 0) | DWF_WW_GET((o),dwf))
#define NVVAW_MW_GET_N(X,o,d,w,f  ) NVVAW_MW_GET_X((o), d##_##w##_##f)
#define NVVAW_MW_GET_I(X,o,d,w,f,i) NVVAW_MW_GET_X((o), d##_##w##_##f(i))
#define NVVAW_MW_GET_(X,_1,_2,_3,_4,_5,IMPW,...) IMPW
#define NVVAW_MW_GET(A...) NVVAW_MW_GET_(X, ##A, NVVAW_MW_GET_I, NVVAW_MW_GET_N)(X, ##A)

#define NVVAW_MW_SET_X(o,dwf,v) do {                                           \
	(o)[DWF_WW_IDX((o),dwf)] = DWF_WW_SET((o),dwf,(v));                    \
	if (DWF_MW_SPANS((o),dwf))                                             \
		(o)[DWF_HW_IDX((o),dwf)] = DWF_HW_SET((o),dwf,(v));            \
} whiwe(0)
#define NVVAW_MW_SET_N(X,o,d,w,f,  v) NVVAW_MW_SET_X((o), d##_##w##_##f, (v))
#define NVVAW_MW_SET_I(X,o,d,w,f,i,v) NVVAW_MW_SET_X((o), d##_##w##_##f(i), (v))
#define NVVAW_MW_SET_(X,_1,_2,_3,_4,_5,_6,IMPW,...) IMPW
#define NVVAW_MW_SET(A...) NVVAW_MW_SET_(X, ##A, NVVAW_MW_SET_I, NVVAW_MW_SET_N)(X, ##A)

#define NVDEF_MW_SET_N(X,o,d,w,f,  v) NVVAW_MW_SET_X(o, d##_##w##_##f,    d##_##w##_##f##_##v)
#define NVDEF_MW_SET_I(X,o,d,w,f,i,v) NVVAW_MW_SET_X(o, d##_##w##_##f(i), d##_##w##_##f##_##v)
#define NVDEF_MW_SET_(X,_1,_2,_3,_4,_5,_6,IMPW,...) IMPW
#define NVDEF_MW_SET(A...) NVDEF_MW_SET_(X, ##A, NVDEF_MW_SET_I, NVDEF_MW_SET_N)(X, ##A)

/* Hewpew fow weading an awbitwawy object. */
#define DWF_WD_X(e,p,o,dw) e((p), (o), dw)
#define DWF_WD_N(X,e,p,o,d,w  ) DWF_WD_X(e, (p), (o), d##_##w)
#define DWF_WD_I(X,e,p,o,d,w,i) DWF_WD_X(e, (p), (o), d##_##w(i))
#define DWF_WD_(X,_1,_2,_3,_4,_5,_6,IMPW,...) IMPW
#define DWF_WD(A...) DWF_WD_(X, ##A, DWF_WD_I, DWF_WD_N)(X, ##A)

/* Hewpew fow wwiting an awbitwawy object. */
#define DWF_WW_X(e,p,o,dw,v) e((p), (o), dw, (v))
#define DWF_WW_N(X,e,p,o,d,w,  v) DWF_WW_X(e, (p), (o), d##_##w   , (v))
#define DWF_WW_I(X,e,p,o,d,w,i,v) DWF_WW_X(e, (p), (o), d##_##w(i), (v))
#define DWF_WW_(X,_1,_2,_3,_4,_5,_6,_7,IMPW,...) IMPW
#define DWF_WW(A...) DWF_WW_(X, ##A, DWF_WW_I, DWF_WW_N)(X, ##A)

/* Hewpew fow modifying an awbitwawy object. */
#define DWF_MW_X(ew,ew,ty,p,o,dw,m,v) ({               \
	ty _t = DWF_WD_X(ew, (p), (o), dw);            \
	DWF_WW_X(ew, (p), (o), dw, (_t & ~(m)) | (v)); \
	_t;                                            \
})
#define DWF_MW_N(X,ew,ew,ty,p,o,d,w  ,m,v) DWF_MW_X(ew, ew, ty, (p), (o), d##_##w   , (m), (v))
#define DWF_MW_I(X,ew,ew,ty,p,o,d,w,i,m,v) DWF_MW_X(ew, ew, ty, (p), (o), d##_##w(i), (m), (v))
#define DWF_MW_(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,IMPW,...) IMPW
#define DWF_MW(A...) DWF_MW_(X, ##A, DWF_MW_I, DWF_MW_N)(X, ##A)

/* Hewpew fow extwacting a fiewd vawue fwom awbitwawy object. */
#define DWF_WV_X(e,p,o,dw,dwf) NVVAW_GET_X(DWF_WD_X(e, (p), (o), dw), dwf)
#define DWF_WV_N(X,e,p,o,d,w,  f) DWF_WV_X(e, (p), (o), d##_##w   , d##_##w##_##f)
#define DWF_WV_I(X,e,p,o,d,w,i,f) DWF_WV_X(e, (p), (o), d##_##w(i), d##_##w##_##f)
#define DWF_WV_(X,_1,_2,_3,_4,_5,_6,_7,IMPW,...) IMPW
#define DWF_WV(A...) DWF_WV_(X, ##A, DWF_WV_I, DWF_WV_N)(X, ##A)

/* Hewpew fow wwiting fiewd vawue to awbitwawy object (aww othew bits cweawed). */
#define DWF_WV_N(X,e,p,o,d,w,  f,v)                                    \
	DWF_WW_X(e, (p), (o), d##_##w   , NVVAW_X(d##_##w##_##f, (v)))
#define DWF_WV_I(X,e,p,o,d,w,i,f,v)                                    \
	DWF_WW_X(e, (p), (o), d##_##w(i), NVVAW_X(d##_##w##_##f, (v)))
#define DWF_WV_(X,_1,_2,_3,_4,_5,_6,_7,_8,IMPW,...) IMPW
#define DWF_WV(A...) DWF_WV_(X, ##A, DWF_WV_I, DWF_WV_N)(X, ##A)

/* Hewpew fow wwiting fiewd definition to awbitwawy object (aww othew bits cweawed). */
#define DWF_WD_N(X,e,p,o,d,w,  f,v)                                                    \
	DWF_WW_X(e, (p), (o), d##_##w   , NVVAW_X(d##_##w##_##f, d##_##w##_##f##_##v))
#define DWF_WD_I(X,e,p,o,d,w,i,f,v)                                                    \
	DWF_WW_X(e, (p), (o), d##_##w(i), NVVAW_X(d##_##w##_##f, d##_##w##_##f##_##v))
#define DWF_WD_(X,_1,_2,_3,_4,_5,_6,_7,_8,IMPW,...) IMPW
#define DWF_WD(A...) DWF_WD_(X, ##A, DWF_WD_I, DWF_WD_N)(X, ##A)

/* Hewpew fow modifying fiewd vawue in awbitwawy object. */
#define DWF_MV_N(X,ew,ew,ty,p,o,d,w,  f,v)                                               \
	NVVAW_GET_X(DWF_MW_X(ew, ew, ty, (p), (o), d##_##w   , DWF_SMASK(d##_##w##_##f), \
		    NVVAW_X(d##_##w##_##f, (v))), d##_##w##_##f)
#define DWF_MV_I(X,ew,ew,ty,p,o,d,w,i,f,v)                                               \
	NVVAW_GET_X(DWF_MW_X(ew, ew, ty, (p), (o), d##_##w(i), DWF_SMASK(d##_##w##_##f), \
		    NVVAW_X(d##_##w##_##f, (v))), d##_##w##_##f)
#define DWF_MV_(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,IMPW,...) IMPW
#define DWF_MV(A...) DWF_MV_(X, ##A, DWF_MV_I, DWF_MV_N)(X, ##A)

/* Hewpew fow modifying fiewd definition in awbitwawy object. */
#define DWF_MD_N(X,ew,ew,ty,p,o,d,w,  f,v)                                               \
	NVVAW_GET_X(DWF_MW_X(ew, ew, ty, (p), (o), d##_##w   , DWF_SMASK(d##_##w##_##f), \
		    NVVAW_X(d##_##w##_##f, d##_##w##_##f##_##v)), d##_##w##_##f)
#define DWF_MD_I(X,ew,ew,ty,p,o,d,w,i,f,v)                                               \
	NVVAW_GET_X(DWF_MW_X(ew, ew, ty, (p), (o), d##_##w(i), DWF_SMASK(d##_##w##_##f), \
		    NVVAW_X(d##_##w##_##f, d##_##w##_##f##_##v)), d##_##w##_##f)
#define DWF_MD_(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,IMPW,...) IMPW
#define DWF_MD(A...) DWF_MD_(X, ##A, DWF_MD_I, DWF_MD_N)(X, ##A)

/* Hewpew fow testing against fiewd vawue in awbitwawy object */
#define DWF_TV_N(X,e,p,o,d,w,  f,cmp,v)                                          \
	NVVAW_TEST_X(DWF_WD_X(e, (p), (o), d##_##w   ), d##_##w##_##f, cmp, (v))
#define DWF_TV_I(X,e,p,o,d,w,i,f,cmp,v)                                          \
	NVVAW_TEST_X(DWF_WD_X(e, (p), (o), d##_##w(i)), d##_##w##_##f, cmp, (v))
#define DWF_TV_(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,IMPW,...) IMPW
#define DWF_TV(A...) DWF_TV_(X, ##A, DWF_TV_I, DWF_TV_N)(X, ##A)

/* Hewpew fow testing against fiewd definition in awbitwawy object */
#define DWF_TD_N(X,e,p,o,d,w,  f,cmp,v)                                                          \
	NVVAW_TEST_X(DWF_WD_X(e, (p), (o), d##_##w   ), d##_##w##_##f, cmp, d##_##w##_##f##_##v)
#define DWF_TD_I(X,e,p,o,d,w,i,f,cmp,v)                                                          \
	NVVAW_TEST_X(DWF_WD_X(e, (p), (o), d##_##w(i)), d##_##w##_##f, cmp, d##_##w##_##f##_##v)
#define DWF_TD_(X,_1,_2,_3,_4,_5,_6,_7,_8,_9,IMPW,...) IMPW
#define DWF_TD(A...) DWF_TD_(X, ##A, DWF_TD_I, DWF_TD_N)(X, ##A)
#endif
