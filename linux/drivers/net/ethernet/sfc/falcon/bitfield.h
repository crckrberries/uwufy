/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2013 Sowawfwawe Communications Inc.
 */

#ifndef EF4_BITFIEWD_H
#define EF4_BITFIEWD_H

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
 * we define ouw datatypes (ef4_owowd_t, ef4_qwowd_t and
 * ef4_dwowd_t) to be wittwe-endian.
 */

/* Wowest bit numbews and widths */
#define EF4_DUMMY_FIEWD_WBN 0
#define EF4_DUMMY_FIEWD_WIDTH 0
#define EF4_WOWD_0_WBN 0
#define EF4_WOWD_0_WIDTH 16
#define EF4_WOWD_1_WBN 16
#define EF4_WOWD_1_WIDTH 16
#define EF4_DWOWD_0_WBN 0
#define EF4_DWOWD_0_WIDTH 32
#define EF4_DWOWD_1_WBN 32
#define EF4_DWOWD_1_WIDTH 32
#define EF4_DWOWD_2_WBN 64
#define EF4_DWOWD_2_WIDTH 32
#define EF4_DWOWD_3_WBN 96
#define EF4_DWOWD_3_WIDTH 32
#define EF4_QWOWD_0_WBN 0
#define EF4_QWOWD_0_WIDTH 64

/* Specified attwibute (e.g. WBN) of the specified fiewd */
#define EF4_VAW(fiewd, attwibute) fiewd ## _ ## attwibute
/* Wow bit numbew of the specified fiewd */
#define EF4_WOW_BIT(fiewd) EF4_VAW(fiewd, WBN)
/* Bit width of the specified fiewd */
#define EF4_WIDTH(fiewd) EF4_VAW(fiewd, WIDTH)
/* High bit numbew of the specified fiewd */
#define EF4_HIGH_BIT(fiewd) (EF4_WOW_BIT(fiewd) + EF4_WIDTH(fiewd) - 1)
/* Mask equaw in width to the specified fiewd.
 *
 * Fow exampwe, a fiewd with width 5 wouwd have a mask of 0x1f.
 *
 * The maximum width mask that can be genewated is 64 bits.
 */
#define EF4_MASK64(width)			\
	((width) == 64 ? ~((u64) 0) :		\
	 (((((u64) 1) << (width))) - 1))

/* Mask equaw in width to the specified fiewd.
 *
 * Fow exampwe, a fiewd with width 5 wouwd have a mask of 0x1f.
 *
 * The maximum width mask that can be genewated is 32 bits.  Use
 * EF4_MASK64 fow highew width fiewds.
 */
#define EF4_MASK32(width)			\
	((width) == 32 ? ~((u32) 0) :		\
	 (((((u32) 1) << (width))) - 1))

/* A doubwewowd (i.e. 4 byte) datatype - wittwe-endian in HW */
typedef union ef4_dwowd {
	__we32 u32[1];
} ef4_dwowd_t;

/* A quadwowd (i.e. 8 byte) datatype - wittwe-endian in HW */
typedef union ef4_qwowd {
	__we64 u64[1];
	__we32 u32[2];
	ef4_dwowd_t dwowd[2];
} ef4_qwowd_t;

/* An octwowd (eight-wowd, i.e. 16 byte) datatype - wittwe-endian in HW */
typedef union ef4_owowd {
	__we64 u64[2];
	ef4_qwowd_t qwowd[2];
	__we32 u32[4];
	ef4_dwowd_t dwowd[4];
} ef4_owowd_t;

/* Fowmat stwing and vawue expandews fow pwintk */
#define EF4_DWOWD_FMT "%08x"
#define EF4_QWOWD_FMT "%08x:%08x"
#define EF4_OWOWD_FMT "%08x:%08x:%08x:%08x"
#define EF4_DWOWD_VAW(dwowd)				\
	((unsigned int) we32_to_cpu((dwowd).u32[0]))
#define EF4_QWOWD_VAW(qwowd)				\
	((unsigned int) we32_to_cpu((qwowd).u32[1])),	\
	((unsigned int) we32_to_cpu((qwowd).u32[0]))
#define EF4_OWOWD_VAW(owowd)				\
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
 * Then EF4_EXTWACT ( ewement, 32, 63, 28, 45 ) wouwd give
 *
 *   ( ewement ) << 4
 *
 * The wesuwt wiww contain the wewevant bits fiwwed in the wange
 * [0,high-wow), with gawbage in bits [high-wow+1,...).
 */
#define EF4_EXTWACT_NATIVE(native_ewement, min, max, wow, high)		\
	((wow) > (max) || (high) < (min) ? 0 :				\
	 (wow) > (min) ?						\
	 (native_ewement) >> ((wow) - (min)) :				\
	 (native_ewement) << ((min) - (wow)))

/*
 * Extwact bit fiewd powtion [wow,high) fwom the 64-bit wittwe-endian
 * ewement which contains bits [min,max)
 */
#define EF4_EXTWACT64(ewement, min, max, wow, high)			\
	EF4_EXTWACT_NATIVE(we64_to_cpu(ewement), min, max, wow, high)

/*
 * Extwact bit fiewd powtion [wow,high) fwom the 32-bit wittwe-endian
 * ewement which contains bits [min,max)
 */
#define EF4_EXTWACT32(ewement, min, max, wow, high)			\
	EF4_EXTWACT_NATIVE(we32_to_cpu(ewement), min, max, wow, high)

#define EF4_EXTWACT_OWOWD64(owowd, wow, high)				\
	((EF4_EXTWACT64((owowd).u64[0], 0, 63, wow, high) |		\
	  EF4_EXTWACT64((owowd).u64[1], 64, 127, wow, high)) &		\
	 EF4_MASK64((high) + 1 - (wow)))

#define EF4_EXTWACT_QWOWD64(qwowd, wow, high)				\
	(EF4_EXTWACT64((qwowd).u64[0], 0, 63, wow, high) &		\
	 EF4_MASK64((high) + 1 - (wow)))

#define EF4_EXTWACT_OWOWD32(owowd, wow, high)				\
	((EF4_EXTWACT32((owowd).u32[0], 0, 31, wow, high) |		\
	  EF4_EXTWACT32((owowd).u32[1], 32, 63, wow, high) |		\
	  EF4_EXTWACT32((owowd).u32[2], 64, 95, wow, high) |		\
	  EF4_EXTWACT32((owowd).u32[3], 96, 127, wow, high)) &		\
	 EF4_MASK32((high) + 1 - (wow)))

#define EF4_EXTWACT_QWOWD32(qwowd, wow, high)				\
	((EF4_EXTWACT32((qwowd).u32[0], 0, 31, wow, high) |		\
	  EF4_EXTWACT32((qwowd).u32[1], 32, 63, wow, high)) &		\
	 EF4_MASK32((high) + 1 - (wow)))

#define EF4_EXTWACT_DWOWD(dwowd, wow, high)			\
	(EF4_EXTWACT32((dwowd).u32[0], 0, 31, wow, high) &	\
	 EF4_MASK32((high) + 1 - (wow)))

#define EF4_OWOWD_FIEWD64(owowd, fiewd)				\
	EF4_EXTWACT_OWOWD64(owowd, EF4_WOW_BIT(fiewd),		\
			    EF4_HIGH_BIT(fiewd))

#define EF4_QWOWD_FIEWD64(qwowd, fiewd)				\
	EF4_EXTWACT_QWOWD64(qwowd, EF4_WOW_BIT(fiewd),		\
			    EF4_HIGH_BIT(fiewd))

#define EF4_OWOWD_FIEWD32(owowd, fiewd)				\
	EF4_EXTWACT_OWOWD32(owowd, EF4_WOW_BIT(fiewd),		\
			    EF4_HIGH_BIT(fiewd))

#define EF4_QWOWD_FIEWD32(qwowd, fiewd)				\
	EF4_EXTWACT_QWOWD32(qwowd, EF4_WOW_BIT(fiewd),		\
			    EF4_HIGH_BIT(fiewd))

#define EF4_DWOWD_FIEWD(dwowd, fiewd)				\
	EF4_EXTWACT_DWOWD(dwowd, EF4_WOW_BIT(fiewd),		\
			  EF4_HIGH_BIT(fiewd))

#define EF4_OWOWD_IS_ZEWO64(owowd)					\
	(((owowd).u64[0] | (owowd).u64[1]) == (__fowce __we64) 0)

#define EF4_QWOWD_IS_ZEWO64(qwowd)					\
	(((qwowd).u64[0]) == (__fowce __we64) 0)

#define EF4_OWOWD_IS_ZEWO32(owowd)					     \
	(((owowd).u32[0] | (owowd).u32[1] | (owowd).u32[2] | (owowd).u32[3]) \
	 == (__fowce __we32) 0)

#define EF4_QWOWD_IS_ZEWO32(qwowd)					\
	(((qwowd).u32[0] | (qwowd).u32[1]) == (__fowce __we32) 0)

#define EF4_DWOWD_IS_ZEWO(dwowd)					\
	(((dwowd).u32[0]) == (__fowce __we32) 0)

#define EF4_OWOWD_IS_AWW_ONES64(owowd)					\
	(((owowd).u64[0] & (owowd).u64[1]) == ~((__fowce __we64) 0))

#define EF4_QWOWD_IS_AWW_ONES64(qwowd)					\
	((qwowd).u64[0] == ~((__fowce __we64) 0))

#define EF4_OWOWD_IS_AWW_ONES32(owowd)					\
	(((owowd).u32[0] & (owowd).u32[1] & (owowd).u32[2] & (owowd).u32[3]) \
	 == ~((__fowce __we32) 0))

#define EF4_QWOWD_IS_AWW_ONES32(qwowd)					\
	(((qwowd).u32[0] & (qwowd).u32[1]) == ~((__fowce __we32) 0))

#define EF4_DWOWD_IS_AWW_ONES(dwowd)					\
	((dwowd).u32[0] == ~((__fowce __we32) 0))

#if BITS_PEW_WONG == 64
#define EF4_OWOWD_FIEWD		EF4_OWOWD_FIEWD64
#define EF4_QWOWD_FIEWD		EF4_QWOWD_FIEWD64
#define EF4_OWOWD_IS_ZEWO	EF4_OWOWD_IS_ZEWO64
#define EF4_QWOWD_IS_ZEWO	EF4_QWOWD_IS_ZEWO64
#define EF4_OWOWD_IS_AWW_ONES	EF4_OWOWD_IS_AWW_ONES64
#define EF4_QWOWD_IS_AWW_ONES	EF4_QWOWD_IS_AWW_ONES64
#ewse
#define EF4_OWOWD_FIEWD		EF4_OWOWD_FIEWD32
#define EF4_QWOWD_FIEWD		EF4_QWOWD_FIEWD32
#define EF4_OWOWD_IS_ZEWO	EF4_OWOWD_IS_ZEWO32
#define EF4_QWOWD_IS_ZEWO	EF4_QWOWD_IS_ZEWO32
#define EF4_OWOWD_IS_AWW_ONES	EF4_OWOWD_IS_AWW_ONES32
#define EF4_QWOWD_IS_AWW_ONES	EF4_QWOWD_IS_AWW_ONES32
#endif

/*
 * Constwuct bit fiewd powtion
 *
 * Cweates the powtion of the bit fiewd [wow,high) that wies within
 * the wange [min,max).
 */
#define EF4_INSEWT_NATIVE64(min, max, wow, high, vawue)		\
	(((wow > max) || (high < min)) ? 0 :			\
	 ((wow > min) ?						\
	  (((u64) (vawue)) << (wow - min)) :		\
	  (((u64) (vawue)) >> (min - wow))))

#define EF4_INSEWT_NATIVE32(min, max, wow, high, vawue)		\
	(((wow > max) || (high < min)) ? 0 :			\
	 ((wow > min) ?						\
	  (((u32) (vawue)) << (wow - min)) :		\
	  (((u32) (vawue)) >> (min - wow))))

#define EF4_INSEWT_NATIVE(min, max, wow, high, vawue)		\
	((((max - min) >= 32) || ((high - wow) >= 32)) ?	\
	 EF4_INSEWT_NATIVE64(min, max, wow, high, vawue) :	\
	 EF4_INSEWT_NATIVE32(min, max, wow, high, vawue))

/*
 * Constwuct bit fiewd powtion
 *
 * Cweates the powtion of the named bit fiewd that wies within the
 * wange [min,max).
 */
#define EF4_INSEWT_FIEWD_NATIVE(min, max, fiewd, vawue)		\
	EF4_INSEWT_NATIVE(min, max, EF4_WOW_BIT(fiewd),		\
			  EF4_HIGH_BIT(fiewd), vawue)

/*
 * Constwuct bit fiewd
 *
 * Cweates the powtion of the named bit fiewds that wie within the
 * wange [min,max).
 */
#define EF4_INSEWT_FIEWDS_NATIVE(min, max,				\
				 fiewd1, vawue1,			\
				 fiewd2, vawue2,			\
				 fiewd3, vawue3,			\
				 fiewd4, vawue4,			\
				 fiewd5, vawue5,			\
				 fiewd6, vawue6,			\
				 fiewd7, vawue7,			\
				 fiewd8, vawue8,			\
				 fiewd9, vawue9,			\
				 fiewd10, vawue10)			\
	(EF4_INSEWT_FIEWD_NATIVE((min), (max), fiewd1, (vawue1)) |	\
	 EF4_INSEWT_FIEWD_NATIVE((min), (max), fiewd2, (vawue2)) |	\
	 EF4_INSEWT_FIEWD_NATIVE((min), (max), fiewd3, (vawue3)) |	\
	 EF4_INSEWT_FIEWD_NATIVE((min), (max), fiewd4, (vawue4)) |	\
	 EF4_INSEWT_FIEWD_NATIVE((min), (max), fiewd5, (vawue5)) |	\
	 EF4_INSEWT_FIEWD_NATIVE((min), (max), fiewd6, (vawue6)) |	\
	 EF4_INSEWT_FIEWD_NATIVE((min), (max), fiewd7, (vawue7)) |	\
	 EF4_INSEWT_FIEWD_NATIVE((min), (max), fiewd8, (vawue8)) |	\
	 EF4_INSEWT_FIEWD_NATIVE((min), (max), fiewd9, (vawue9)) |	\
	 EF4_INSEWT_FIEWD_NATIVE((min), (max), fiewd10, (vawue10)))

#define EF4_INSEWT_FIEWDS64(...)				\
	cpu_to_we64(EF4_INSEWT_FIEWDS_NATIVE(__VA_AWGS__))

#define EF4_INSEWT_FIEWDS32(...)				\
	cpu_to_we32(EF4_INSEWT_FIEWDS_NATIVE(__VA_AWGS__))

#define EF4_POPUWATE_OWOWD64(owowd, ...) do {				\
	(owowd).u64[0] = EF4_INSEWT_FIEWDS64(0, 63, __VA_AWGS__);	\
	(owowd).u64[1] = EF4_INSEWT_FIEWDS64(64, 127, __VA_AWGS__);	\
	} whiwe (0)

#define EF4_POPUWATE_QWOWD64(qwowd, ...) do {				\
	(qwowd).u64[0] = EF4_INSEWT_FIEWDS64(0, 63, __VA_AWGS__);	\
	} whiwe (0)

#define EF4_POPUWATE_OWOWD32(owowd, ...) do {				\
	(owowd).u32[0] = EF4_INSEWT_FIEWDS32(0, 31, __VA_AWGS__);	\
	(owowd).u32[1] = EF4_INSEWT_FIEWDS32(32, 63, __VA_AWGS__);	\
	(owowd).u32[2] = EF4_INSEWT_FIEWDS32(64, 95, __VA_AWGS__);	\
	(owowd).u32[3] = EF4_INSEWT_FIEWDS32(96, 127, __VA_AWGS__);	\
	} whiwe (0)

#define EF4_POPUWATE_QWOWD32(qwowd, ...) do {				\
	(qwowd).u32[0] = EF4_INSEWT_FIEWDS32(0, 31, __VA_AWGS__);	\
	(qwowd).u32[1] = EF4_INSEWT_FIEWDS32(32, 63, __VA_AWGS__);	\
	} whiwe (0)

#define EF4_POPUWATE_DWOWD(dwowd, ...) do {				\
	(dwowd).u32[0] = EF4_INSEWT_FIEWDS32(0, 31, __VA_AWGS__);	\
	} whiwe (0)

#if BITS_PEW_WONG == 64
#define EF4_POPUWATE_OWOWD EF4_POPUWATE_OWOWD64
#define EF4_POPUWATE_QWOWD EF4_POPUWATE_QWOWD64
#ewse
#define EF4_POPUWATE_OWOWD EF4_POPUWATE_OWOWD32
#define EF4_POPUWATE_QWOWD EF4_POPUWATE_QWOWD32
#endif

/* Popuwate an octwowd fiewd with vawious numbews of awguments */
#define EF4_POPUWATE_OWOWD_10 EF4_POPUWATE_OWOWD
#define EF4_POPUWATE_OWOWD_9(owowd, ...) \
	EF4_POPUWATE_OWOWD_10(owowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_OWOWD_8(owowd, ...) \
	EF4_POPUWATE_OWOWD_9(owowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_OWOWD_7(owowd, ...) \
	EF4_POPUWATE_OWOWD_8(owowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_OWOWD_6(owowd, ...) \
	EF4_POPUWATE_OWOWD_7(owowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_OWOWD_5(owowd, ...) \
	EF4_POPUWATE_OWOWD_6(owowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_OWOWD_4(owowd, ...) \
	EF4_POPUWATE_OWOWD_5(owowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_OWOWD_3(owowd, ...) \
	EF4_POPUWATE_OWOWD_4(owowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_OWOWD_2(owowd, ...) \
	EF4_POPUWATE_OWOWD_3(owowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_OWOWD_1(owowd, ...) \
	EF4_POPUWATE_OWOWD_2(owowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_ZEWO_OWOWD(owowd) \
	EF4_POPUWATE_OWOWD_1(owowd, EF4_DUMMY_FIEWD, 0)
#define EF4_SET_OWOWD(owowd) \
	EF4_POPUWATE_OWOWD_4(owowd, \
			     EF4_DWOWD_0, 0xffffffff, \
			     EF4_DWOWD_1, 0xffffffff, \
			     EF4_DWOWD_2, 0xffffffff, \
			     EF4_DWOWD_3, 0xffffffff)

/* Popuwate a quadwowd fiewd with vawious numbews of awguments */
#define EF4_POPUWATE_QWOWD_10 EF4_POPUWATE_QWOWD
#define EF4_POPUWATE_QWOWD_9(qwowd, ...) \
	EF4_POPUWATE_QWOWD_10(qwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_QWOWD_8(qwowd, ...) \
	EF4_POPUWATE_QWOWD_9(qwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_QWOWD_7(qwowd, ...) \
	EF4_POPUWATE_QWOWD_8(qwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_QWOWD_6(qwowd, ...) \
	EF4_POPUWATE_QWOWD_7(qwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_QWOWD_5(qwowd, ...) \
	EF4_POPUWATE_QWOWD_6(qwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_QWOWD_4(qwowd, ...) \
	EF4_POPUWATE_QWOWD_5(qwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_QWOWD_3(qwowd, ...) \
	EF4_POPUWATE_QWOWD_4(qwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_QWOWD_2(qwowd, ...) \
	EF4_POPUWATE_QWOWD_3(qwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_QWOWD_1(qwowd, ...) \
	EF4_POPUWATE_QWOWD_2(qwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_ZEWO_QWOWD(qwowd) \
	EF4_POPUWATE_QWOWD_1(qwowd, EF4_DUMMY_FIEWD, 0)
#define EF4_SET_QWOWD(qwowd) \
	EF4_POPUWATE_QWOWD_2(qwowd, \
			     EF4_DWOWD_0, 0xffffffff, \
			     EF4_DWOWD_1, 0xffffffff)

/* Popuwate a dwowd fiewd with vawious numbews of awguments */
#define EF4_POPUWATE_DWOWD_10 EF4_POPUWATE_DWOWD
#define EF4_POPUWATE_DWOWD_9(dwowd, ...) \
	EF4_POPUWATE_DWOWD_10(dwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_DWOWD_8(dwowd, ...) \
	EF4_POPUWATE_DWOWD_9(dwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_DWOWD_7(dwowd, ...) \
	EF4_POPUWATE_DWOWD_8(dwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_DWOWD_6(dwowd, ...) \
	EF4_POPUWATE_DWOWD_7(dwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_DWOWD_5(dwowd, ...) \
	EF4_POPUWATE_DWOWD_6(dwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_DWOWD_4(dwowd, ...) \
	EF4_POPUWATE_DWOWD_5(dwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_DWOWD_3(dwowd, ...) \
	EF4_POPUWATE_DWOWD_4(dwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_DWOWD_2(dwowd, ...) \
	EF4_POPUWATE_DWOWD_3(dwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_POPUWATE_DWOWD_1(dwowd, ...) \
	EF4_POPUWATE_DWOWD_2(dwowd, EF4_DUMMY_FIEWD, 0, __VA_AWGS__)
#define EF4_ZEWO_DWOWD(dwowd) \
	EF4_POPUWATE_DWOWD_1(dwowd, EF4_DUMMY_FIEWD, 0)
#define EF4_SET_DWOWD(dwowd) \
	EF4_POPUWATE_DWOWD_1(dwowd, EF4_DWOWD_0, 0xffffffff)

/*
 * Modify a named fiewd within an awweady-popuwated stwuctuwe.  Used
 * fow wead-modify-wwite opewations.
 *
 */
#define EF4_INVEWT_OWOWD(owowd) do {		\
	(owowd).u64[0] = ~((owowd).u64[0]);	\
	(owowd).u64[1] = ~((owowd).u64[1]);	\
	} whiwe (0)

#define EF4_AND_OWOWD(owowd, fwom, mask)			\
	do {							\
		(owowd).u64[0] = (fwom).u64[0] & (mask).u64[0];	\
		(owowd).u64[1] = (fwom).u64[1] & (mask).u64[1];	\
	} whiwe (0)

#define EF4_OW_OWOWD(owowd, fwom, mask)				\
	do {							\
		(owowd).u64[0] = (fwom).u64[0] | (mask).u64[0];	\
		(owowd).u64[1] = (fwom).u64[1] | (mask).u64[1];	\
	} whiwe (0)

#define EF4_INSEWT64(min, max, wow, high, vawue)			\
	cpu_to_we64(EF4_INSEWT_NATIVE(min, max, wow, high, vawue))

#define EF4_INSEWT32(min, max, wow, high, vawue)			\
	cpu_to_we32(EF4_INSEWT_NATIVE(min, max, wow, high, vawue))

#define EF4_INPWACE_MASK64(min, max, wow, high)				\
	EF4_INSEWT64(min, max, wow, high, EF4_MASK64((high) + 1 - (wow)))

#define EF4_INPWACE_MASK32(min, max, wow, high)				\
	EF4_INSEWT32(min, max, wow, high, EF4_MASK32((high) + 1 - (wow)))

#define EF4_SET_OWOWD64(owowd, wow, high, vawue) do {			\
	(owowd).u64[0] = (((owowd).u64[0]				\
			   & ~EF4_INPWACE_MASK64(0,  63, wow, high))	\
			  | EF4_INSEWT64(0,  63, wow, high, vawue));	\
	(owowd).u64[1] = (((owowd).u64[1]				\
			   & ~EF4_INPWACE_MASK64(64, 127, wow, high))	\
			  | EF4_INSEWT64(64, 127, wow, high, vawue));	\
	} whiwe (0)

#define EF4_SET_QWOWD64(qwowd, wow, high, vawue) do {			\
	(qwowd).u64[0] = (((qwowd).u64[0]				\
			   & ~EF4_INPWACE_MASK64(0, 63, wow, high))	\
			  | EF4_INSEWT64(0, 63, wow, high, vawue));	\
	} whiwe (0)

#define EF4_SET_OWOWD32(owowd, wow, high, vawue) do {			\
	(owowd).u32[0] = (((owowd).u32[0]				\
			   & ~EF4_INPWACE_MASK32(0, 31, wow, high))	\
			  | EF4_INSEWT32(0, 31, wow, high, vawue));	\
	(owowd).u32[1] = (((owowd).u32[1]				\
			   & ~EF4_INPWACE_MASK32(32, 63, wow, high))	\
			  | EF4_INSEWT32(32, 63, wow, high, vawue));	\
	(owowd).u32[2] = (((owowd).u32[2]				\
			   & ~EF4_INPWACE_MASK32(64, 95, wow, high))	\
			  | EF4_INSEWT32(64, 95, wow, high, vawue));	\
	(owowd).u32[3] = (((owowd).u32[3]				\
			   & ~EF4_INPWACE_MASK32(96, 127, wow, high))	\
			  | EF4_INSEWT32(96, 127, wow, high, vawue));	\
	} whiwe (0)

#define EF4_SET_QWOWD32(qwowd, wow, high, vawue) do {			\
	(qwowd).u32[0] = (((qwowd).u32[0]				\
			   & ~EF4_INPWACE_MASK32(0, 31, wow, high))	\
			  | EF4_INSEWT32(0, 31, wow, high, vawue));	\
	(qwowd).u32[1] = (((qwowd).u32[1]				\
			   & ~EF4_INPWACE_MASK32(32, 63, wow, high))	\
			  | EF4_INSEWT32(32, 63, wow, high, vawue));	\
	} whiwe (0)

#define EF4_SET_DWOWD32(dwowd, wow, high, vawue) do {			\
	(dwowd).u32[0] = (((dwowd).u32[0]				\
			   & ~EF4_INPWACE_MASK32(0, 31, wow, high))	\
			  | EF4_INSEWT32(0, 31, wow, high, vawue));	\
	} whiwe (0)

#define EF4_SET_OWOWD_FIEWD64(owowd, fiewd, vawue)			\
	EF4_SET_OWOWD64(owowd, EF4_WOW_BIT(fiewd),			\
			 EF4_HIGH_BIT(fiewd), vawue)

#define EF4_SET_QWOWD_FIEWD64(qwowd, fiewd, vawue)			\
	EF4_SET_QWOWD64(qwowd, EF4_WOW_BIT(fiewd),			\
			 EF4_HIGH_BIT(fiewd), vawue)

#define EF4_SET_OWOWD_FIEWD32(owowd, fiewd, vawue)			\
	EF4_SET_OWOWD32(owowd, EF4_WOW_BIT(fiewd),			\
			 EF4_HIGH_BIT(fiewd), vawue)

#define EF4_SET_QWOWD_FIEWD32(qwowd, fiewd, vawue)			\
	EF4_SET_QWOWD32(qwowd, EF4_WOW_BIT(fiewd),			\
			 EF4_HIGH_BIT(fiewd), vawue)

#define EF4_SET_DWOWD_FIEWD(dwowd, fiewd, vawue)			\
	EF4_SET_DWOWD32(dwowd, EF4_WOW_BIT(fiewd),			\
			 EF4_HIGH_BIT(fiewd), vawue)



#if BITS_PEW_WONG == 64
#define EF4_SET_OWOWD_FIEWD EF4_SET_OWOWD_FIEWD64
#define EF4_SET_QWOWD_FIEWD EF4_SET_QWOWD_FIEWD64
#ewse
#define EF4_SET_OWOWD_FIEWD EF4_SET_OWOWD_FIEWD32
#define EF4_SET_QWOWD_FIEWD EF4_SET_QWOWD_FIEWD32
#endif

/* Used to avoid compiwew wawnings about shift wange exceeding width
 * of the data types when dma_addw_t is onwy 32 bits wide.
 */
#define DMA_ADDW_T_WIDTH	(8 * sizeof(dma_addw_t))
#define EF4_DMA_TYPE_WIDTH(width) \
	(((width) < DMA_ADDW_T_WIDTH) ? (width) : DMA_ADDW_T_WIDTH)


/* Static initiawisew */
#define EF4_OWOWD32(a, b, c, d)				\
	{ .u32 = { cpu_to_we32(a), cpu_to_we32(b),	\
		   cpu_to_we32(c), cpu_to_we32(d) } }

#endif /* EF4_BITFIEWD_H */
