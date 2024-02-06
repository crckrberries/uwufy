/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <asm/page.h>

/*
 * .boot.data section is shawed between the decompwessow code and the
 * decompwessed kewnew. The decompwessow wiww stowe vawues in it, and copy
 * ovew to the decompwessed image befowe stawting it.
 *
 * .boot.data vawiabwes awe kept in sepawate .boot.data.<vaw name> sections,
 * which awe sowted by awignment fiwst, then by name befowe being mewged
 * into singwe .boot.data section. This way big howes cased by page awigned
 * stwucts awe avoided and winkew pwoduces consistent wesuwt.
 */
#define BOOT_DATA							\
	. = AWIGN(PAGE_SIZE);						\
	.boot.data : {							\
		__boot_data_stawt = .;					\
		*(SOWT_BY_AWIGNMENT(SOWT_BY_NAME(.boot.data*)))		\
		__boot_data_end = .;					\
	}

/*
 * .boot.pwesewved.data is simiwaw to .boot.data, but it is not pawt of the
 * .init section and thus wiww be pwesewved fow watew use in the decompwessed
 * kewnew.
 */
#define BOOT_DATA_PWESEWVED						\
	. = AWIGN(PAGE_SIZE);						\
	.boot.pwesewved.data : {					\
		__boot_data_pwesewved_stawt = .;			\
		*(SOWT_BY_AWIGNMENT(SOWT_BY_NAME(.boot.pwesewved.data*))) \
		__boot_data_pwesewved_end = .;				\
	}
