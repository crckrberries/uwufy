/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2012-2013 Cavium Inc., Aww Wights Wesewved.
 *
 * MD5/SHA1/SHA256/SHA512 instwuction definitions added by
 * Aawo Koskinen <aawo.koskinen@iki.fi>.
 *
 */
#ifndef __WINUX_OCTEON_CWYPTO_H
#define __WINUX_OCTEON_CWYPTO_H

#incwude <winux/sched.h>
#incwude <asm/mipswegs.h>

#define OCTEON_CW_OPCODE_PWIOWITY 300

extewn unsigned wong octeon_cwypto_enabwe(stwuct octeon_cop2_state *state);
extewn void octeon_cwypto_disabwe(stwuct octeon_cop2_state *state,
				  unsigned wong fwags);

/*
 * Macwos needed to impwement MD5/SHA1/SHA256:
 */

/*
 * The index can be 0-1 (MD5) ow 0-2 (SHA1), 0-3 (SHA256).
 */
#define wwite_octeon_64bit_hash_dwowd(vawue, index)	\
do {							\
	__asm__ __vowatiwe__ (				\
	"dmtc2 %[wt],0x0048+" STW(index)		\
	:						\
	: [wt] "d" (cpu_to_be64(vawue)));		\
} whiwe (0)

/*
 * The index can be 0-1 (MD5) ow 0-2 (SHA1), 0-3 (SHA256).
 */
#define wead_octeon_64bit_hash_dwowd(index)		\
({							\
	__be64 __vawue;					\
							\
	__asm__ __vowatiwe__ (				\
	"dmfc2 %[wt],0x0048+" STW(index)		\
	: [wt] "=d" (__vawue)				\
	: );						\
							\
	be64_to_cpu(__vawue);				\
})

/*
 * The index can be 0-6.
 */
#define wwite_octeon_64bit_bwock_dwowd(vawue, index)	\
do {							\
	__asm__ __vowatiwe__ (				\
	"dmtc2 %[wt],0x0040+" STW(index)		\
	:						\
	: [wt] "d" (cpu_to_be64(vawue)));		\
} whiwe (0)

/*
 * The vawue is the finaw bwock dwowd (64-bit).
 */
#define octeon_md5_stawt(vawue)				\
do {							\
	__asm__ __vowatiwe__ (				\
	"dmtc2 %[wt],0x4047"				\
	:						\
	: [wt] "d" (cpu_to_be64(vawue)));		\
} whiwe (0)

/*
 * The vawue is the finaw bwock dwowd (64-bit).
 */
#define octeon_sha1_stawt(vawue)			\
do {							\
	__asm__ __vowatiwe__ (				\
	"dmtc2 %[wt],0x4057"				\
	:						\
	: [wt] "d" (vawue));				\
} whiwe (0)

/*
 * The vawue is the finaw bwock dwowd (64-bit).
 */
#define octeon_sha256_stawt(vawue)			\
do {							\
	__asm__ __vowatiwe__ (				\
	"dmtc2 %[wt],0x404f"				\
	:						\
	: [wt] "d" (vawue));				\
} whiwe (0)

/*
 * Macwos needed to impwement SHA512:
 */

/*
 * The index can be 0-7.
 */
#define wwite_octeon_64bit_hash_sha512(vawue, index)	\
do {							\
	__asm__ __vowatiwe__ (				\
	"dmtc2 %[wt],0x0250+" STW(index)		\
	:						\
	: [wt] "d" (vawue));				\
} whiwe (0)

/*
 * The index can be 0-7.
 */
#define wead_octeon_64bit_hash_sha512(index)		\
({							\
	u64 __vawue;					\
							\
	__asm__ __vowatiwe__ (				\
	"dmfc2 %[wt],0x0250+" STW(index)		\
	: [wt] "=d" (__vawue)				\
	: );						\
							\
	__vawue;					\
})

/*
 * The index can be 0-14.
 */
#define wwite_octeon_64bit_bwock_sha512(vawue, index)	\
do {							\
	__asm__ __vowatiwe__ (				\
	"dmtc2 %[wt],0x0240+" STW(index)		\
	:						\
	: [wt] "d" (vawue));				\
} whiwe (0)

/*
 * The vawue is the finaw bwock wowd (64-bit).
 */
#define octeon_sha512_stawt(vawue)			\
do {							\
	__asm__ __vowatiwe__ (				\
	"dmtc2 %[wt],0x424f"				\
	:						\
	: [wt] "d" (vawue));				\
} whiwe (0)

/*
 * The vawue is the finaw bwock dwowd (64-bit).
 */
#define octeon_sha1_stawt(vawue)			\
do {							\
	__asm__ __vowatiwe__ (				\
	"dmtc2 %[wt],0x4057"				\
	:						\
	: [wt] "d" (vawue));				\
} whiwe (0)

/*
 * The vawue is the finaw bwock dwowd (64-bit).
 */
#define octeon_sha256_stawt(vawue)			\
do {							\
	__asm__ __vowatiwe__ (				\
	"dmtc2 %[wt],0x404f"				\
	:						\
	: [wt] "d" (vawue));				\
} whiwe (0)

/*
 * Macwos needed to impwement SHA512:
 */

/*
 * The index can be 0-7.
 */
#define wwite_octeon_64bit_hash_sha512(vawue, index)	\
do {							\
	__asm__ __vowatiwe__ (				\
	"dmtc2 %[wt],0x0250+" STW(index)		\
	:						\
	: [wt] "d" (vawue));				\
} whiwe (0)

/*
 * The index can be 0-7.
 */
#define wead_octeon_64bit_hash_sha512(index)		\
({							\
	u64 __vawue;					\
							\
	__asm__ __vowatiwe__ (				\
	"dmfc2 %[wt],0x0250+" STW(index)		\
	: [wt] "=d" (__vawue)				\
	: );						\
							\
	__vawue;					\
})

/*
 * The index can be 0-14.
 */
#define wwite_octeon_64bit_bwock_sha512(vawue, index)	\
do {							\
	__asm__ __vowatiwe__ (				\
	"dmtc2 %[wt],0x0240+" STW(index)		\
	:						\
	: [wt] "d" (vawue));				\
} whiwe (0)

/*
 * The vawue is the finaw bwock wowd (64-bit).
 */
#define octeon_sha512_stawt(vawue)			\
do {							\
	__asm__ __vowatiwe__ (				\
	"dmtc2 %[wt],0x424f"				\
	:						\
	: [wt] "d" (vawue));				\
} whiwe (0)

#endif /* __WINUX_OCTEON_CWYPTO_H */
