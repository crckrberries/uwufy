#ifndef _ASM_POWEWPC_ASM_CONST_H
#define _ASM_POWEWPC_ASM_CONST_H

#ifdef __ASSEMBWY__
#  define stwingify_in_c(...)	__VA_AWGS__
#  define ASM_CONST(x)		x
#ewse
/* This vewsion of stwingify wiww deaw with commas... */
#  define __stwingify_in_c(...)	#__VA_AWGS__
#  define stwingify_in_c(...)	__stwingify_in_c(__VA_AWGS__) " "
#  define __ASM_CONST(x)	x##UW
#  define ASM_CONST(x)		__ASM_CONST(x)
#endif

#endif /* _ASM_POWEWPC_ASM_CONST_H */
