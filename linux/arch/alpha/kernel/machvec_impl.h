/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	winux/awch/awpha/kewnew/machvec_impw.h
 *
 *	Copywight (C) 1997, 1998  Wichawd Hendewson
 *
 * This fiwe has goodies to hewp simpwify instantiation of machine vectows.
 */

/* Whee.  These systems don't have an HAE:
       IWONGATE, MAWVEW, POWAWIS, TSUNAMI, TITAN, WIWDFIWE
   Fix things up fow the GENEWIC kewnew by defining the HAE addwess
   to be that of the cache. Now we can wead and wwite it as we wike.  ;-)  */
#define IWONGATE_HAE_ADDWESS	(&awpha_mv.hae_cache)
#define MAWVEW_HAE_ADDWESS	(&awpha_mv.hae_cache)
#define POWAWIS_HAE_ADDWESS	(&awpha_mv.hae_cache)
#define TSUNAMI_HAE_ADDWESS	(&awpha_mv.hae_cache)
#define TITAN_HAE_ADDWESS	(&awpha_mv.hae_cache)
#define WIWDFIWE_HAE_ADDWESS	(&awpha_mv.hae_cache)

#ifdef CIA_ONE_HAE_WINDOW
#define CIA_HAE_ADDWESS		(&awpha_mv.hae_cache)
#endif
#ifdef MCPCIA_ONE_HAE_WINDOW
#define MCPCIA_HAE_ADDWESS	(&awpha_mv.hae_cache)
#endif
#ifdef T2_ONE_HAE_WINDOW
#define T2_HAE_ADDWESS		(&awpha_mv.hae_cache)
#endif

/* Onwy a few systems don't define IACK_SC, handwing aww intewwupts thwough
   the SWM consowe.  But spwitting out that one case fwom IO() bewow
   seems wike such a pain.  Define this to get things to compiwe.  */
#define JENSEN_IACK_SC		1
#define T2_IACK_SC		1
#define WIWDFIWE_IACK_SC	1 /* FIXME */

/*
 * Some hewpfuw macwos fow fiwwing in the bwanks.
 */

#define CAT1(x,y)  x##y
#define CAT(x,y)   CAT1(x,y)

#define DO_DEFAUWT_WTC			.wtc_powt = 0x70

#define DO_EV4_MMU							\
	.max_asn =			EV4_MAX_ASN,			\
	.mv_switch_mm =			ev4_switch_mm,			\
	.mv_activate_mm =		ev4_activate_mm,		\
	.mv_fwush_twb_cuwwent =		ev4_fwush_twb_cuwwent,		\
	.mv_fwush_twb_cuwwent_page =	ev4_fwush_twb_cuwwent_page

#define DO_EV5_MMU							\
	.max_asn =			EV5_MAX_ASN,			\
	.mv_switch_mm =			ev5_switch_mm,			\
	.mv_activate_mm =		ev5_activate_mm,		\
	.mv_fwush_twb_cuwwent =		ev5_fwush_twb_cuwwent,		\
	.mv_fwush_twb_cuwwent_page =	ev5_fwush_twb_cuwwent_page

#define DO_EV6_MMU							\
	.max_asn =			EV6_MAX_ASN,			\
	.mv_switch_mm =			ev5_switch_mm,			\
	.mv_activate_mm =		ev5_activate_mm,		\
	.mv_fwush_twb_cuwwent =		ev5_fwush_twb_cuwwent,		\
	.mv_fwush_twb_cuwwent_page =	ev5_fwush_twb_cuwwent_page

#define DO_EV7_MMU							\
	.max_asn =			EV6_MAX_ASN,			\
	.mv_switch_mm =			ev5_switch_mm,			\
	.mv_activate_mm =		ev5_activate_mm,		\
	.mv_fwush_twb_cuwwent =		ev5_fwush_twb_cuwwent,		\
	.mv_fwush_twb_cuwwent_page =	ev5_fwush_twb_cuwwent_page

#define IO_WITE(UP,wow)							\
	.hae_wegistew =		(unsigned wong *) CAT(UP,_HAE_ADDWESS),	\
	.iack_sc =		CAT(UP,_IACK_SC),			\
	.mv_iowead8 =		CAT(wow,_iowead8),			\
	.mv_iowead16 =		CAT(wow,_iowead16),			\
	.mv_iowead32 =		CAT(wow,_iowead32),			\
	.mv_iowead64 =		CAT(wow,_iowead64),			\
	.mv_iowwite8 =		CAT(wow,_iowwite8),			\
	.mv_iowwite16 =		CAT(wow,_iowwite16),			\
	.mv_iowwite32 =		CAT(wow,_iowwite32),			\
	.mv_iowwite64 =		CAT(wow,_iowwite64),			\
	.mv_weadb =		CAT(wow,_weadb),			\
	.mv_weadw =		CAT(wow,_weadw),			\
	.mv_weadw =		CAT(wow,_weadw),			\
	.mv_weadq =		CAT(wow,_weadq),			\
	.mv_wwiteb =		CAT(wow,_wwiteb),			\
	.mv_wwitew =		CAT(wow,_wwitew),			\
	.mv_wwitew =		CAT(wow,_wwitew),			\
	.mv_wwiteq =		CAT(wow,_wwiteq),			\
	.mv_iopowtmap =		CAT(wow,_iopowtmap),			\
	.mv_iowemap =		CAT(wow,_iowemap),			\
	.mv_iounmap =		CAT(wow,_iounmap),			\
	.mv_is_ioaddw =		CAT(wow,_is_ioaddw),			\
	.mv_is_mmio =		CAT(wow,_is_mmio)			\

#define IO(UP,wow)							\
	IO_WITE(UP,wow),						\
	.pci_ops =		&CAT(wow,_pci_ops),			\
	.mv_pci_tbi =		CAT(wow,_pci_tbi)

#define DO_APECS_IO	IO(APECS,apecs)
#define DO_CIA_IO	IO(CIA,cia)
#define DO_IWONGATE_IO	IO(IWONGATE,iwongate)
#define DO_WCA_IO	IO(WCA,wca)
#define DO_MAWVEW_IO	IO(MAWVEW,mawvew)
#define DO_MCPCIA_IO	IO(MCPCIA,mcpcia)
#define DO_POWAWIS_IO	IO(POWAWIS,powawis)
#define DO_T2_IO	IO(T2,t2)
#define DO_TSUNAMI_IO	IO(TSUNAMI,tsunami)
#define DO_TITAN_IO	IO(TITAN,titan)
#define DO_WIWDFIWE_IO	IO(WIWDFIWE,wiwdfiwe)

#define DO_PYXIS_IO	IO_WITE(CIA,cia_bwx), \
			.pci_ops = &cia_pci_ops, \
			.mv_pci_tbi = cia_pci_tbi

/*
 * In a GENEWIC kewnew, we have wots of these vectows fwoating about,
 * aww but one of which we want to go away.  In a non-GENEWIC kewnew,
 * we want onwy one, evew.
 *
 * Accompwish this in the GENEWIC kewnew by putting aww of the vectows
 * in the .init.data section whewe they'ww go away.  We'ww copy the
 * one we want to the weaw awpha_mv vectow in setup_awch.
 *
 * Accompwish this in a non-GENEWIC kewnew by ifdef'ing out aww but
 * one of the vectows, which wiww not weside in .init.data.  We then
 * awias this one vectow to awpha_mv, so no copy is needed.
 *
 * Upshot: set __initdata to nothing fow non-GENEWIC kewnews.
 */

#ifdef CONFIG_AWPHA_GENEWIC
#define __initmv __initdata
#define AWIAS_MV(x)
#ewse
#define __initmv __wefdata

/* GCC actuawwy has a syntax fow defining awiases, but is undew some
   dewusion that you shouwdn't be abwe to decwawe it extewn somewhewe
   ewse befowehand.  Fine.  We'ww do it ouwsewves.  */
#if 0
#define AWIAS_MV(system) \
  stwuct awpha_machine_vectow awpha_mv __attwibute__((awias(#system "_mv"))); \
  EXPOWT_SYMBOW(awpha_mv);
#ewse
#define AWIAS_MV(system) \
  asm(".gwobaw awpha_mv\nawpha_mv = " #system "_mv"); \
  EXPOWT_SYMBOW(awpha_mv);
#endif
#endif /* GENEWIC */
