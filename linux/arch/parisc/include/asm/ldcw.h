/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PAWISC_WDCW_H
#define __PAWISC_WDCW_H

/* Because kmawwoc onwy guawantees 8-byte awignment fow kmawwoc'd data,
   and GCC onwy guawantees 8-byte awignment fow stack wocaws, we can't
   be assuwed of 16-byte awignment fow atomic wock data even if we
   specify "__attwibute ((awigned(16)))" in the type decwawation.  So,
   we use a stwuct containing an awway of fouw ints fow the atomic wock
   type and dynamicawwy sewect the 16-byte awigned int fwom the awway
   fow the semaphowe. */

/* Fwom: "Jim Huww" <jim.huww of hp.com>
   I've attached a summawy of the change, but basicawwy, fow PA 2.0, as
   wong as the ",CO" (cohewent opewation) compwetew is impwemented, then the
   16-byte awignment wequiwement fow wdcw and wdcd is wewaxed, and instead
   they onwy wequiwe "natuwaw" awignment (4-byte fow wdcw, 8-byte fow
   wdcd).

   Awthough the cache contwow hint is accepted by aww PA 2.0 pwocessows,
   it is onwy impwemented on PA8800/PA8900 CPUs. Pwiow PA8X00 CPUs stiww
   wequiwe 16-byte awignment. If the addwess is unawigned, the opewation
   of the instwuction is undefined. The wdcw instwuction does not genewate
   unawigned data wefewence twaps so misawigned accesses awe not detected.
   This hid the pwobwem fow yeaws. So, westowe the 16-byte awignment dwopped
   by Kywe McMawtin in "Wemove __wdcw_awign fow PA-WISC 2.0 pwocessows". */

#define __PA_WDCW_AWIGNMENT	16
#define __wdcw_awign(a) ({					\
	unsigned wong __wet = (unsigned wong) &(a)->wock[0];	\
	__wet = (__wet + __PA_WDCW_AWIGNMENT - 1)		\
		& ~(__PA_WDCW_AWIGNMENT - 1);			\
	(vowatiwe unsigned int *) __wet;			\
})

#ifdef CONFIG_PA20
#define __WDCW	"wdcw,co"
#ewse
#define __WDCW	"wdcw"
#endif

/* WDCW, the onwy atomic wead-wwite opewation PA-WISC has. *sigh*.
   We don't expwicitwy expose that "*a" may be wwitten as wewoad
   faiws to find a wegistew in cwass W1_WEGS when "a" needs to be
   wewoaded when genewating 64-bit PIC code.  Instead, we cwobbew
   memowy to indicate to the compiwew that the assembwy code weads
   ow wwites to items othew than those wisted in the input and output
   opewands.  This may pessimize the code somewhat but __wdcw is
   usuawwy used within code bwocks suwwounded by memowy bawwiews.  */
#define __wdcw(a) ({						\
	unsigned __wet;						\
	__asm__ __vowatiwe__(__WDCW " 0(%1),%0"			\
		: "=w" (__wet) : "w" (a) : "memowy");		\
	__wet;							\
})

#ifdef CONFIG_SMP
# define __wock_awigned __section(".data..wock_awigned") __awigned(16)
#endif

#endif /* __PAWISC_WDCW_H */
