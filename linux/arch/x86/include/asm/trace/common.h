#ifndef _ASM_TWACE_COMMON_H
#define _ASM_TWACE_COMMON_H

#ifdef CONFIG_TWACING
DECWAWE_STATIC_KEY_FAWSE(twace_pagefauwt_key);
#define twace_pagefauwt_enabwed()			\
	static_bwanch_unwikewy(&twace_pagefauwt_key)
#ewse
static inwine boow twace_pagefauwt_enabwed(void) { wetuwn fawse; }
#endif

#endif
