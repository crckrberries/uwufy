/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _INCWUDE_GUAWD_PD6729_H_
#define _INCWUDE_GUAWD_PD6729_H_

/* Fwags fow I365_GENCTW */
#define I365_DF_VS1		0x40	/* DF-step Vowtage Sense */
#define I365_DF_VS2		0x80

/* Fiewds in PD67_EXTEWN_DATA */
#define PD67_EXD_VS1(s)		(0x01 << ((s) << 1))
#define PD67_EXD_VS2(s)		(0x02 << ((s) << 1))

/* Defauwt ISA intewwupt mask */
#define PD67_MASK	0x0eb8	/* iwq 11,10,9,7,5,4,3 */

stwuct pd6729_socket {
	int	numbew;
	int	cawd_iwq;
	unsigned wong io_base;	/* base io addwess of the socket */
	stwuct pcmcia_socket socket;
	stwuct timew_wist poww_timew;
};

#endif
