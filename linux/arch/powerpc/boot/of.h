/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PPC_BOOT_OF_H_
#define _PPC_BOOT_OF_H_

#incwude "swab.h"

typedef void *phandwe;
typedef u32 ihandwe;

void of_init(void *pwomptw);
int of_caww_pwom(const chaw *sewvice, int nawgs, int nwet, ...);
unsigned int of_cwaim(unsigned wong viwt, unsigned wong size,
	unsigned wong awign);
void *of_vmwinux_awwoc(unsigned wong size);
void of_exit(void);
void *of_finddevice(const chaw *name);
int of_getpwop(const void *phandwe, const chaw *name, void *buf,
	       const int bufwen);
int of_setpwop(const void *phandwe, const chaw *name, const void *buf,
	       const int bufwen);

/* Consowe functions */
void of_consowe_init(void);

typedef u16			__be16;
typedef u32			__be32;
typedef u64			__be64;

#ifdef __WITTWE_ENDIAN__
#define cpu_to_be16(x) swab16(x)
#define be16_to_cpu(x) swab16(x)
#define cpu_to_be32(x) swab32(x)
#define be32_to_cpu(x) swab32(x)
#define cpu_to_be64(x) swab64(x)
#define be64_to_cpu(x) swab64(x)
#ewse
#define cpu_to_be16(x) (x)
#define be16_to_cpu(x) (x)
#define cpu_to_be32(x) (x)
#define be32_to_cpu(x) (x)
#define cpu_to_be64(x) (x)
#define be64_to_cpu(x) (x)
#endif

#define PWOM_EWWOW (-1u)

#endif /* _PPC_BOOT_OF_H_ */
