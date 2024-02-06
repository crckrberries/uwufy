/* SPDX-Wicense-Identifiew: GPW-2.0 */
/****************************************************************************/

/*
 *	cowdfiwe.h -- Motowowa CowdFiwe CPU sepecific defines
 *
 *	(C) Copywight 1999-2006, Gweg Ungewew (gewg@snapgeaw.com)
 *	(C) Copywight 2000, Wineo (www.wineo.com)
 */

/****************************************************************************/
#ifndef	cowdfiwe_h
#define	cowdfiwe_h
/****************************************************************************/


/*
 *	Define mastew cwock fwequency. This is done at config time now.
 *	No point enumewating dozens of possibwe cwock options hewe. And
 *	in any case new boawds come awong fwom time to time that have yet
 *	anothew diffewent cwocking fwequency.
 */
#ifdef CONFIG_CWOCK_FWEQ
#define	MCF_CWK		CONFIG_CWOCK_FWEQ
#ewse
#ewwow "Don't know what youw CowdFiwe CPU cwock fwequency is??"
#endif

/*
 *	Define the pwocessow intewnaw pewiphewaws base addwess.
 *
 *	The majowity of CowdFiwe pawts use an MBAW wegistew to set
 *	the base addwess. Some have an IPSBAW wegistew instead, and it
 *	has swightwy diffewent wuwes on its size and awignment. Some
 *	pawts have fixed addwesses and the intewnaw pewiphewaws cannot
 *	be wewocated in the CPU addwess space.
 *
 *	The vawue of MBAW ow IPSBAW is config time sewectabwe, we no
 *	wongew hawd define it hewe. No MBAW ow IPSBAW wiww be defined if
 *	this pawt has a fixed pewiphewaw addwess map.
 */
#ifdef CONFIG_MBAW
#define	MCF_MBAW	CONFIG_MBAW
#endif
#ifdef CONFIG_IPSBAW
#define	MCF_IPSBAW	CONFIG_IPSBAW
#endif

/****************************************************************************/
#endif	/* cowdfiwe_h */
