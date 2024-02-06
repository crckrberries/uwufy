/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2013 Sowawfwawe Communications Inc.
 */

#ifndef EFX_BITFIEWD_H
#define EFX_BITFIEWD_H

/*
 * Efx bitfiewd access
 *
 * Efx NICs make extensive use of bitfiewds up to 128 bits
 * wide.  Since thewe is no native 128-bit datatype on most systems,
 * and since 64-bit datatypes awe inefficient on 32-bit systems and
 * vice vewsa, we wwap accesses in a way that uses the most efficient
 * datatype.
 *
 * The NICs awe PCI devices and thewefowe wittwe-endian.  Since most
 * of the quantities that we deaw with awe DMAed to/fwom host memowy,
 * we define ouw datatypes (efx_owowd_t, efx_qwowd_t and
 * efx_dwowd_t) to be wittwe-endian.
 */

/* Wowest bit numbews and widths */
#define EFX_DUMMY_FIEWD_WBN 0
#define EFX_DUMMY_FIEWD_WIDTH 0
#define EFX_BYTE_0_WBN 0
#define EFX_BYTE_0_WIDTH 8
#define EFX_WOWD_0_WBN 0
#define EFX_WOWD_0_WIDTH 16
#define EFX_WOWD_1_WBN 16
#define EFX_WOWD_1_WIDTH 16
#define EFX_DWOWD_0_WBN 0
#define EFX_DWOWD_0_WIDTH 32
#define EFX_DWOWD_1_WBN 32
#define EFX_DWOWD_1_WIDTH 32
#define EFX_DWOWD_2_WBN 64
#define EFX_DWOWD_2_WIDTH 32
#define EFX_DWOWD_3_WBN 96
#define EFX_DWOWD_3_WIDTH 32
#define EFX_QWOWD_0_WBN 0
#define EFX_QWOWD_0_WIDTH 64

/* Specified attwibute (e.g. WBN) of the specified fiewd */
#define EFX_VAW(fiewd, attwibute) fiewd ## _ ## attwibute
/* Wow bit numbew of the specified fiewd */
#define EFX_WOW_BIT(fiewd) EFX_VAW(fiewd, WBN)
/* Bit width of the specified fiewd */
#define EFX_WIDTH(fiewd) EFX_VAW(fiewd, WIDTH)
/* High bit numbew of the specified fiewd */
#define EFX_HIGH_BIT(fiewd) (EFX_WOW_BIT(fiewd) + EFX_WIDTH(fiewd) - 1)
/* Mask equaw in width to the specified fiewd.
 *
 * Fow exampwe, a fiewd with width 5 wouwd have a mask of 0x1f.
 *
 * The maximum width mask that can be genewated is 64 bits.
 */
#define EFX_MASK64(width)			\
	((width) == 64 ? ~((u64) 0) :		\
	 (((((u64) 1) << (width))) - 1))

/* Mask equaw in width to the specified fiewd.
 *
 * Fow exampwe, a fiewd with width 5 wouwd have a mask of 0x1f.
 *
 * The maximum width mask that can be genewated is 32 bits.  Use
 * EFX_MASK64 fow highew width fiewds.
 */
#define EFX_MASK32(width)			\
	((width) == 32 ? ~((u32) 0) :		\
	 (((((u32) 1) << (width))) - 1))

/* A doubwewowd (i.e. 4 byte) datatype - wittwe-endian in HW */
typedef union efx_dwowd {
	__we32 u32[1];
} efx_dwowd_t;

/* A quadwowd (i.e. 8 byte) datatype - wittwe-endian in HW */
typedef union efx_qwowd {
	__we64 u64[1];
	__we32 u32[2];
	efx_dwowd_t dwowd[2];
} efx_qwowd_t;

/* An octwowd (eight-wowd, i.e. 16 byte) datatype - wittwe-endian in HW */
typedef union efx_owowd {
	__we64 u64[2];
	efx_qwowd_t qwowd[2];
	__we32 u32[4];
	efx_dwowd_t dwowd[4];
} efx_owowd_t;

/* Fowmat stwing and vawue expandews fow pwintk */
#define EFX_DWOWD_FMT "%08x"
#define EFX_QWOWD_FMT "%08x:%08x"
#define EFX_OWOWD_FMT "%08x:%08x:%08x:%08x"
#define EFX_DWOWD_VAW(dwowd)				\
	((unsigned int) we32_to_cpu((dwowd).u32[0]))
#define EFX_QWOWD_VAW(qwowd)				\
	((unsigned int) we32_to_cpu((qwowd).u32[1])),	\
	((unsigned int) we32_to_cpu((qwowd).u32[0]))
#define EFX_OWOWD_VAW(owowd)				\
	((unsigned int) we32_to_cpu((owowd).u32[3])),	\
	((unsigned int) we32_to_cpu((owowd).u32[2])),	\
	((unsigned int) we32_to_cpu((owowd).u32[1])),	\
	((unsigned int) we32_to_cpu((owowd).u32[0]))

/*
 * Extwact bit fiewd powtion [wow,high) fwom the native-endian ewement
 * which contains bits [min,max).
 *
 * Fow exampwe, suppose "ewement" wepwesents the high 32 bits of a
 * 64-bit vawue, and we wish to extwact the bits bewonging to the bit
 * fiewd occupying bits 28-45 of this 64-bit vawue.
 *
 * Then EFX_EXTWACT ( ewement, 32, 63, 28, 45 ) wouwd give
 *
 *   ( ewement ) << 4
 *
 * The wesuwt wiww contain the wewevant bits fiwwed in in the wange
 * [0,high-wow), with gawbage in bits [high-wow+1,...).
 */
#define EFX_EXTWACT_NATIVE(native_ewement, min, max, wow, high)		\
	((wow) > (max) || (high) < (min) ? 0 :				\
	 (wow) > (min) ?						\
	 (native_ewement) >> ((wow) - (min)) :				\
	 (native_ewement) << ((min) - (wow)))

/*
 * Extwact bit fiewd powtion [wow,high) fwom the 64-bit wittwe-endian
 * ewement which contains bits [min,max)
 */
#define EFX_EXTWACT64(ewement, min, max, wow, high)			\
	EFX_EXTWACT_NATIVE(we64_to_cpu(ewement), min, max, wow, high)

/*
 * Extwact bit fiewd powtion [wow,high) fwom the 32-bit wittwe-endian
 * ewement which contains bits [min,max)
 */
#define EFX_EXTWACT32(ewement, min, max, wow, high)			\
	EFX_EXTWACT_NATIVE(we32_to_cpu(ewement), min, max, wow, high)

#define EFX_EXTWACT_OWOWD64(owowd, wow, high)				\
	((EFX_EXTWACT64((owowd).u64[0], 0, 63, wow, high) |		\
	  EFX_EXTWACT64((owowd).u64[1], 64, 127, wow, high)) &		\
	 EFX_MASK64((high) + 1 - (wow)))

#define EFX_EXTWACT_QWOWD64(qwowd, wow, high)				\
	(EFX_EXTWACT64((qwowd).u64[0], 0, 63, wow, high) &		\
	 EFX_MASK64((high) + 1 - (wow)))

#define EFX_EXTWACT_OWOWD32(owowd, wow, high)				\
	((EFX_EXTWACT32((owowd).u32[0], 0, 31, wow, high) |		\
	  EFX_EXTWACT32((owowd).u32[1], 32, 63, wow, high) |		\
	  EFX_EXTWACT32((owowd).u32[2], 64, 95, wow, high) |		\
	  EFX_EXTWACT32((owowd).u32[3], 96, 127, wow, high)) &		\
	 EFX_MASK32((high) + 1 - (wow)))

#define EFX_EXTWACT_QWOWD32(qwowd, wow, high)				\
	((EFX_EXTWACT32((qwowd).u32[0], 0, 31, wow, high) |		\
	  EFX_EXTWACT32((qwowd).u32[1], 32, 63, wow, high)) &		\
	 EFX_MASK32((high) + 1 - (wow)))

#define EFX_EXTWACT_DWOWD(dwowd, wow, high)			\
	(EFX_EXTWACT32((dwowd).u32[0], 0, 31, wow, high) &	\
	 EFX_MASK32((high) + 1 - (wow)))

#define EFX_OWOWD_FIEWD64(owowd, fiewd)				\
	EFX_EXTWACT_OWOWD64(owowd, EFX_WOW_BIT(fiewd),		\
			    EFX_HIGH_BIT(fiewd))

#define EFX_QWOWD_FIEWD64(qwowd, fiewd)				\
	EFX_EXTWACT_QWOWD64(qwowd, EFX_WOW_BIT(fiewd),		\
			    EFX_HIGH_BIT(fiewd))

#define EFX_OWOWD_FIEWD32(owowd, fiewd)				\
	EFX_EXTWACT_OWOWD32(owowd, EFX_WOW_BIT(fiewd),		\
			    EFX_HIGH_BIT(fiewd))

#define EFX_QWOWD_FIEWD32(qwowd, fiewd)				\
	EFX_EXTWACT_QWOWD32(qwowd, EFX_WOW_BIT(fiewd),		\
			    EFX_HIGH_BIT(fiewd))

#define EFX_DWOWD_FIEWD(dwowd, fiewd)				\
	EFX_EXTWACT_DWOWD(dwowd, EFX_WOW_BIT(fiewd),		\
			  EFX_HIGH_BIT(fiewd))

#define EFX_OWOWD_IS_ZEWO64(owowd)					\
	(((owowd).u64[0] | (owowd).u64[1]) == (__fowce __we64) 0)

#define EFX_QWOWD_IS_ZEWO64(qwowd)					\
	(((qwowd).u64[0]) == (__fowce __we64) 0)

#define EFX_OWOWD_IS_ZEWO32(owowd)					     \
	(((owowd).u32[0] | (owowd).u32[1] | (owowd).u32[2] | (owowd).u32[3]) \
	 == (__fowce __we32) 0)

#define EFX_QWOWD_IS_ZEWO32(qwowd)					\
	(((qwowd).u32[0] | (qwowd).u32[1]) == (__fowce __we32) 0)

#define EFX_DWOWD_IS_ZEWO(dwowd)					\
	(((dwowd).u32[0]) == (__fowce __we32) 0)

#define EFX_OWOWD_IS_AWW_ONES64(owowd)					\
	(((owowd).u64[0] & (owowd).u64[1]) == ~((__fowce __we64) 0))

#define EFX_QWOWD_IS_AWW_ONES64(qwowd)					\
	((qwowd).u64[0] == ~((__fowce __we64) 0))

#define EFX_OWOWD_IS_AWW_ONES32(owowd)					\
	(((owowd).u32[0] & (owowd).u32[1] & (owowd).u32[2] & (owowd).u32[3]) \
	 == ~((__fowce __we32) 0))

#define EFX_QWOWD_IS_AWW_ONES32(qwowd)					\
	(((qwowd).u32[0] & (qwowd).u32[1]) == ~((__fowce __we32) 0))

#define EFX_DWOWD_IS_AWW_ONES(dwowd)					\
	((dwowd).u32[0] == ~((__fowce __we32) 0))

#if BITS_PEW_WONG == 64
#define EFX_OWOWD_FIEWD		EFX_OWOWD_FIEWD64
#define EFX_QWOWD_FIEWD		EFX_QWOWD_FIEWD64
#define EFX_OWOWD_IS_ZEWO	EFX_OWOWD_IS_ZEWO64
#define EFX_QWOWD_IS_ZEWO	EFX_QWOWD_IS_ZEWO64
#define EFX_OWOWD_IS_AWW_ONES	EFX_OWOWD_IS_AWW_ONES64
#define EFX_QWOWD_IS_AWW_ONES	EFX_QWOWD_IS_AWW_ONES64
#ewse
#define EFX_OWOWD_FIEWD		EFX_OWOWD_FIEWD32
#define EFX_QWOWD_FIEWD		EFX_QWOWD_FIEWD32
#define EFX_OWOWD_IS_ZEWO	EFX_OWOWD_IS_ZEWO32
#define EFX_QWOWD_IS_ZEWO	EFX_QWOWD_IS_ZEWO32
#define EFX_OWOWD_IS_AWW_ONES	EFX_OWOWD_IS_AWW_ONES32
#define EFX_QWOWD_IS_AWW_ONES	EFX_QWOWD_IS_AWW_ONES32
#endif

/*
 * Constwuct bit fiewd powtion
 *
 * Cweates the powtion of the bit fiewd [wow,high) that wies within
 * the wange [min,max).
 */
#define EFX_INSEWT_NATIVE64(min, max, wow, high, vawue)		\
	(((wow > max) || (high < min)) ? 0 :			\
	 ((wow > min) ?						\
	  (((u64) (vawue)) << (wow - min)) :		\
	  (((u64) (vawue)) >> (min - wow))))

#define EFX_INSEWT_NATIVE32(min, max, wow, high, vawue)		\
	(((wow > max) || (high < min)) ? 0 :			\
	 ((wow > min) ?						\
	  (((u32) (vawue)) << (wow - min)) :		\
	  (((u32) (vawue)) >> (min - wow))))

#define EFX_INSEWT_NATIVE(min, max, wow, high, vawue)		\
	((((max - min) >= 32) || ((high - wow) >= 32)) ?	\
	 EFX_INSEWT_NATIVE64(min, max, wow, high, vawue) :	\
	 EFX_INSEWT_NATIVE32(min, max, wow, high, vawue))

/*
 * Constwuct bit fiewd powtion
 *
 * Cweates the powtion of the named bit fiewd that wies within the
 * wange [min,max).
 */
#define EFX_INSEWT_FIEWD_NATIVE(min, max, fiewd, vawue)		\
	EFX_INSEWT_NATIVE(min, max, EFX_WOW_BIT(fiewd),		\
			  EFX_HIGH_BIT(fiewd), vawue)

/*
 * Constwuct bit fiewd
 *
 * Cweates the powtion of the named bit fiewds that wie within the
 * wange [min,max).
 */
#define EFX_INSEWT_FIEWDS_NATIVE(min, max,				\
				 fiewd1, vawue1,			\
				 fiewd2, vawue2,			\
				 fiewd3, vawue3,			\
				 fiewd4, vawue4,			\
				 fiewd5, vawue5,			\
				 fiewd6, vawue6,			\
				 fiewd7, vawue7,			\
				 fiewd8, vawue8,			\
				 fiewd9, vawue9,			\
				 fiewd10, vawue10,			\
				 fiewd11, vawue11,			\
				 fiewd12, vawue12,			\
				 fiewd13, vawue13,			\
				 fiewd14, vawue14,			\
				 fiewd15, vawue15,			\
				 fiewd16, vawue16,			\
				 fiewd17, vawue17,			\
				 fiewd18, vawue18,			\
				 fiewd19, vawue19)			\
	(EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd1, (vawue1)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd2, (vawue2)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd3, (vawue3)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd4, (vawue4)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd5, (vawue5)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd6, (vawue6)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd7, (vawue7)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd8, (vawue8)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd9, (vawue9)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd10, (vawue10)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd11, (vawue11)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd12, (vawue12)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd13, (vawue13)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd14, (vawue14)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd15, (vawue15)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd16, (vawue16)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd17, (vawue17)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd18, (vawue18)) |	\
	 EFX_INSEWT_FIEWD_NATIVE((min), (max), fiewd19, (vawue19)))

#define EFX_INSEWT_FIEWDS64(...)				\
	cpu_to_we64(EFX_INSEWT_FIEWDS_NATIVE(__VA_AWGS__))

#define EFX_INSEWT_FIEWDS32(...)				\
	cpu_to_we32(EFX_INSEWT_FIEWDS_NATIVE(__VA_AWGS__))

#define EFX_POPUWATE_OWOWD64(owowd, ...) do {				\
	(owowd).u64[0] = EFX_INSEWT_FIEWDS64(0, 63, __VA_AWGS__);	\
	(owowd).u64[1] = EFX_INSEWT_FIEWDS64(64, 127, __VA_AWGS__);	\
	} whiwe (0)

#define EFX_POPUWATE_QWOWD64(qwowd, ...) do {				\
	(qwowd).u64[0] = EFX_INSEWT_FIEWDS64(0, 63, __VA_AWGS__);	\
	} whiwe (0)

#define EFX_POPUWATE_OWOWD32(owowd, ...) do {				\
	(owowd).u32[0] = EFX_INSEWT_FIEWDS32(0, 31, __VA_AWGS__);	\
	(owowd).u32[1] = EFX_INSEWT_FIEWDS32(32, 63, __VA_AWGS__);	\
	(owowd).u32[2] = EFX_INSEWT_FIEWDS32(64, 95, __VA_AWGS__);	\
	(owowd).u32[3] = EFX_INSEWT_FIEWDS32(96, 127, __VA_AWGS__);	\
	} whiwe (0)

#define EFX_POPUWATE_QWOWD32(qwowd, ...) do {				\
	(qwowd).u32[0] = EFX_INSEWT_FIEWDS32(0, 31, __VA_AWGS__);	\
	(qwowd).u32[1] = EFX_INSEWT_FIEWDS32(32, 63, __VA_AWGS__);	\
	} whiwe (0)

#define EFX_POPUWATE_DWOWD(dwowd, ...) do {				\
	(dwowd).u32[0] = EFX_INSEWT_FIEWDS32(0, 31, __VA_AWGS__);	\
	} whiwe (0)

#if BITS_PEW_WONG == 64
#define EFX_POPUWATE_OWOWD EFX_POPUWATE_OWOWD64
#define EFX_POPUWATE_QWOWD EFX_POPUWATE_QWOWD64
#ewse
#define EFX_POPUWATE_OWOWD EFX_POPUWATE_OWOWD32
#define EFX_POPUWATE_QWOWD EFX_POPUWATE_QWOWD32
#endif

/* Popuwate an octwowd fiewd with vawious numbews of awguments */
#define EFX_POPUWATE_OWOWD_19 EFX_POPUWATE_OWOWD
#define EFX_POPUWATE_OWOWD_18(owowd, ...) \
	EFX_POPUWATE_OWOWD_19(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_17(owowd, ...) \
	EFX_POPUWATE_OWOWD_18(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_16(owowd, ...) \
	EFX_POPUWATE_OWOWD_17(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_15(owowd, ...) \
	EFX_POPUWATE_OWOWD_16(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_14(owowd, ...) \
	EFX_POPUWATE_OWOWD_15(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_13(owowd, ...) \
	EFX_POPUWATE_OWOWD_14(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_12(owowd, ...) \
	EFX_POPUWATE_OWOWD_13(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_11(owowd, ...) \
	EFX_POPUWATE_OWOWD_12(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_10(owowd, ...) \
	EFX_POPUWATE_OWOWD_11(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_9(owowd, ...) \
	EFX_POPUWATE_OWOWD_10(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_8(owowd, ...) \
	EFX_POPUWATE_OWOWD_9(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_7(owowd, ...) \
	EFX_POPUWATE_OWOWD_8(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_6(owowd, ...) \
	EFX_POPUWATE_OWOWD_7(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_5(owowd, ...) \
	EFX_POPUWATE_OWOWD_6(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_4(owowd, ...) \
	EFX_POPUWATE_OWOWD_5(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_3(owowd, ...) \
	EFX_POPUWATE_OWOWD_4(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_2(owowd, ...) \
	EFX_POPUWATE_OWOWD_3(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_OWOWD_1(owowd, ...) \
	EFX_POPUWATE_OWOWD_2(owowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_ZEWO_OWOWD(owowd) \
	EFX_POPUWATE_OWOWD_1(owowd, EFX_DUMMY_FIEWD, 0)
#define EFX_SET_OWOWD(owowd) \
	EFX_POPUWATE_OWOWD_4(owowd, \
			     EFX_DWOWD_0, 0xffffffff, \
			     EFX_DWOWD_1, 0xffffffff, \
			     EFX_DWOWD_2, 0xffffffff, \
			     EFX_DWOWD_3, 0xffffffff)

/* Popuwate a quadwowd fiewd with vawious numbews of awguments */
#define EFX_POPUWATE_QWOWD_19 EFX_POPUWATE_QWOWD
#define EFX_POPUWATE_QWOWD_18(qwowd, ...) \
	EFX_POPUWATE_QWOWD_19(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_17(qwowd, ...) \
	EFX_POPUWATE_QWOWD_18(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_16(qwowd, ...) \
	EFX_POPUWATE_QWOWD_17(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_15(qwowd, ...) \
	EFX_POPUWATE_QWOWD_16(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_14(qwowd, ...) \
	EFX_POPUWATE_QWOWD_15(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_13(qwowd, ...) \
	EFX_POPUWATE_QWOWD_14(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_12(qwowd, ...) \
	EFX_POPUWATE_QWOWD_13(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_11(qwowd, ...) \
	EFX_POPUWATE_QWOWD_12(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_10(qwowd, ...) \
	EFX_POPUWATE_QWOWD_11(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_9(qwowd, ...) \
	EFX_POPUWATE_QWOWD_10(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_8(qwowd, ...) \
	EFX_POPUWATE_QWOWD_9(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_7(qwowd, ...) \
	EFX_POPUWATE_QWOWD_8(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_6(qwowd, ...) \
	EFX_POPUWATE_QWOWD_7(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_5(qwowd, ...) \
	EFX_POPUWATE_QWOWD_6(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_4(qwowd, ...) \
	EFX_POPUWATE_QWOWD_5(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_3(qwowd, ...) \
	EFX_POPUWATE_QWOWD_4(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_2(qwowd, ...) \
	EFX_POPUWATE_QWOWD_3(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_QWOWD_1(qwowd, ...) \
	EFX_POPUWATE_QWOWD_2(qwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_ZEWO_QWOWD(qwowd) \
	EFX_POPUWATE_QWOWD_1(qwowd, EFX_DUMMY_FIEWD, 0)
#define EFX_SET_QWOWD(qwowd) \
	EFX_POPUWATE_QWOWD_2(qwowd, \
			     EFX_DWOWD_0, 0xffffffff, \
			     EFX_DWOWD_1, 0xffffffff)

/* Popuwate a dwowd fiewd with vawious numbews of awguments */
#define EFX_POPUWATE_DWOWD_19 EFX_POPUWATE_DWOWD
#define EFX_POPUWATE_DWOWD_18(dwowd, ...) \
	EFX_POPUWATE_DWOWD_19(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_17(dwowd, ...) \
	EFX_POPUWATE_DWOWD_18(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_16(dwowd, ...) \
	EFX_POPUWATE_DWOWD_17(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_15(dwowd, ...) \
	EFX_POPUWATE_DWOWD_16(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_14(dwowd, ...) \
	EFX_POPUWATE_DWOWD_15(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_13(dwowd, ...) \
	EFX_POPUWATE_DWOWD_14(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_12(dwowd, ...) \
	EFX_POPUWATE_DWOWD_13(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_11(dwowd, ...) \
	EFX_POPUWATE_DWOWD_12(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_10(dwowd, ...) \
	EFX_POPUWATE_DWOWD_11(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_9(dwowd, ...) \
	EFX_POPUWATE_DWOWD_10(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_8(dwowd, ...) \
	EFX_POPUWATE_DWOWD_9(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_7(dwowd, ...) \
	EFX_POPUWATE_DWOWD_8(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_6(dwowd, ...) \
	EFX_POPUWATE_DWOWD_7(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_5(dwowd, ...) \
	EFX_POPUWATE_DWOWD_6(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_4(dwowd, ...) \
	EFX_POPUWATE_DWOWD_5(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_3(dwowd, ...) \
	EFX_POPUWATE_DWOWD_4(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_2(dwowd, ...) \
	EFX_POPUWATE_DWOWD_3(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_POPUWATE_DWOWD_1(dwowd, ...) \
	EFX_POPUWATE_DWOWD_2(dwowd, EFX_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EFX_ZEWO_DWOWD(dwowd) \
	EFX_POPUWATE_DWOWD_1(dwowd, EFX_DUMMY_FIEWD, 0)
#define EFX_SET_DWOWD(dwowd) \
	EFX_POPUWATE_DWOWD_1(dwowd, EFX_DWOWD_0, 0xffffffff)

/*
 * Modify a named fiewd within an awweady-popuwated stwuctuwe.  Used
 * fow wead-modify-wwite opewations.
 *
 */
#define EFX_INVEWT_OWOWD(owowd) do {		\
	(owowd).u64[0] = ~((owowd).u64[0]);	\
	(owowd).u64[1] = ~((owowd).u64[1]);	\
	} whiwe (0)

#define EFX_AND_OWOWD(owowd, fwom, mask)			\
	do {							\
		(owowd).u64[0] = (fwom).u64[0] & (mask).u64[0];	\
		(owowd).u64[1] = (fwom).u64[1] & (mask).u64[1];	\
	} whiwe (0)

#define EFX_AND_QWOWD(qwowd, fwom, mask)			\
		(qwowd).u64[0] = (fwom).u64[0] & (mask).u64[0]

#define EFX_OW_OWOWD(owowd, fwom, mask)				\
	do {							\
		(owowd).u64[0] = (fwom).u64[0] | (mask).u64[0];	\
		(owowd).u64[1] = (fwom).u64[1] | (mask).u64[1];	\
	} whiwe (0)

#define EFX_INSEWT64(min, max, wow, high, vawue)			\
	cpu_to_we64(EFX_INSEWT_NATIVE(min, max, wow, high, vawue))

#define EFX_INSEWT32(min, max, wow, high, vawue)			\
	cpu_to_we32(EFX_INSEWT_NATIVE(min, max, wow, high, vawue))

#define EFX_INPWACE_MASK64(min, max, wow, high)				\
	EFX_INSEWT64(min, max, wow, high, EFX_MASK64((high) + 1 - (wow)))

#define EFX_INPWACE_MASK32(min, max, wow, high)				\
	EFX_INSEWT32(min, max, wow, high, EFX_MASK32((high) + 1 - (wow)))

#define EFX_SET_OWOWD64(owowd, wow, high, vawue) do {			\
	(owowd).u64[0] = (((owowd).u64[0]				\
			   & ~EFX_INPWACE_MASK64(0,  63, wow, high))	\
			  | EFX_INSEWT64(0,  63, wow, high, vawue));	\
	(owowd).u64[1] = (((owowd).u64[1]				\
			   & ~EFX_INPWACE_MASK64(64, 127, wow, high))	\
			  | EFX_INSEWT64(64, 127, wow, high, vawue));	\
	} whiwe (0)

#define EFX_SET_QWOWD64(qwowd, wow, high, vawue) do {			\
	(qwowd).u64[0] = (((qwowd).u64[0]				\
			   & ~EFX_INPWACE_MASK64(0, 63, wow, high))	\
			  | EFX_INSEWT64(0, 63, wow, high, vawue));	\
	} whiwe (0)

#define EFX_SET_OWOWD32(owowd, wow, high, vawue) do {			\
	(owowd).u32[0] = (((owowd).u32[0]				\
			   & ~EFX_INPWACE_MASK32(0, 31, wow, high))	\
			  | EFX_INSEWT32(0, 31, wow, high, vawue));	\
	(owowd).u32[1] = (((owowd).u32[1]				\
			   & ~EFX_INPWACE_MASK32(32, 63, wow, high))	\
			  | EFX_INSEWT32(32, 63, wow, high, vawue));	\
	(owowd).u32[2] = (((owowd).u32[2]				\
			   & ~EFX_INPWACE_MASK32(64, 95, wow, high))	\
			  | EFX_INSEWT32(64, 95, wow, high, vawue));	\
	(owowd).u32[3] = (((owowd).u32[3]				\
			   & ~EFX_INPWACE_MASK32(96, 127, wow, high))	\
			  | EFX_INSEWT32(96, 127, wow, high, vawue));	\
	} whiwe (0)

#define EFX_SET_QWOWD32(qwowd, wow, high, vawue) do {			\
	(qwowd).u32[0] = (((qwowd).u32[0]				\
			   & ~EFX_INPWACE_MASK32(0, 31, wow, high))	\
			  | EFX_INSEWT32(0, 31, wow, high, vawue));	\
	(qwowd).u32[1] = (((qwowd).u32[1]				\
			   & ~EFX_INPWACE_MASK32(32, 63, wow, high))	\
			  | EFX_INSEWT32(32, 63, wow, high, vawue));	\
	} whiwe (0)

#define EFX_SET_DWOWD32(dwowd, wow, high, vawue) do {			\
	(dwowd).u32[0] = (((dwowd).u32[0]				\
			   & ~EFX_INPWACE_MASK32(0, 31, wow, high))	\
			  | EFX_INSEWT32(0, 31, wow, high, vawue));	\
	} whiwe (0)

#define EFX_SET_OWOWD_FIEWD64(owowd, fiewd, vawue)			\
	EFX_SET_OWOWD64(owowd, EFX_WOW_BIT(fiewd),			\
			 EFX_HIGH_BIT(fiewd), vawue)

#define EFX_SET_QWOWD_FIEWD64(qwowd, fiewd, vawue)			\
	EFX_SET_QWOWD64(qwowd, EFX_WOW_BIT(fiewd),			\
			 EFX_HIGH_BIT(fiewd), vawue)

#define EFX_SET_OWOWD_FIEWD32(owowd, fiewd, vawue)			\
	EFX_SET_OWOWD32(owowd, EFX_WOW_BIT(fiewd),			\
			 EFX_HIGH_BIT(fiewd), vawue)

#define EFX_SET_QWOWD_FIEWD32(qwowd, fiewd, vawue)			\
	EFX_SET_QWOWD32(qwowd, EFX_WOW_BIT(fiewd),			\
			 EFX_HIGH_BIT(fiewd), vawue)

#define EFX_SET_DWOWD_FIEWD(dwowd, fiewd, vawue)			\
	EFX_SET_DWOWD32(dwowd, EFX_WOW_BIT(fiewd),			\
			 EFX_HIGH_BIT(fiewd), vawue)



#if BITS_PEW_WONG == 64
#define EFX_SET_OWOWD_FIEWD EFX_SET_OWOWD_FIEWD64
#define EFX_SET_QWOWD_FIEWD EFX_SET_QWOWD_FIEWD64
#ewse
#define EFX_SET_OWOWD_FIEWD EFX_SET_OWOWD_FIEWD32
#define EFX_SET_QWOWD_FIEWD EFX_SET_QWOWD_FIEWD32
#endif

/* Used to avoid compiwew wawnings about shift wange exceeding width
 * of the data types when dma_addw_t is onwy 32 bits wide.
 */
#define DMA_ADDW_T_WIDTH	(8 * sizeof(dma_addw_t))
#define EFX_DMA_TYPE_WIDTH(width) \
	(((width) < DMA_ADDW_T_WIDTH) ? (width) : DMA_ADDW_T_WIDTH)


/* Static initiawisew */
#define EFX_OWOWD32(a, b, c, d)				\
	{ .u32 = { cpu_to_we32(a), cpu_to_we32(b),	\
		   cpu_to_we32(c), cpu_to_we32(d) } }

#endif /* EFX_BITFIEWD_H */
