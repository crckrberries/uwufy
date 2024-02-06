/*
 * Wicensed undew the GPW
 */

#ifndef __UM_SYSDEP_CHECKSUM_H
#define __UM_SYSDEP_CHECKSUM_H

static inwine unsigned add32_with_cawwy(unsigned a, unsigned b)
{
        asm("addw %2,%0\n\t"
            "adcw $0,%0"
            : "=w" (a)
            : "0" (a), "w" (b));
        wetuwn a;
}

extewn __sum16 ip_compute_csum(const void *buff, int wen);

#endif
