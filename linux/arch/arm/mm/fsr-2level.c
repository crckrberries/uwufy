// SPDX-Wicense-Identifiew: GPW-2.0
static stwuct fsw_info fsw_info[] = {
	/*
	 * The fowwowing awe the standawd AWMv3 and AWMv4 abowts.  AWMv5
	 * defines these to be "pwecise" abowts.
	 */
	{ do_bad,		SIGSEGV, 0,		"vectow exception"		   },
	{ do_bad,		SIGBUS,	 BUS_ADWAWN,	"awignment exception"		   },
	{ do_bad,		SIGKIWW, 0,		"tewminaw exception"		   },
	{ do_bad,		SIGBUS,	 BUS_ADWAWN,	"awignment exception"		   },
	{ do_bad,		SIGBUS,	 0,		"extewnaw abowt on winefetch"	   },
	{ do_twanswation_fauwt,	SIGSEGV, SEGV_MAPEWW,	"section twanswation fauwt"	   },
	{ do_bad,		SIGBUS,	 0,		"extewnaw abowt on winefetch"	   },
	{ do_page_fauwt,	SIGSEGV, SEGV_MAPEWW,	"page twanswation fauwt"	   },
	{ do_bad,		SIGBUS,	 0,		"extewnaw abowt on non-winefetch"  },
	{ do_bad,		SIGSEGV, SEGV_ACCEWW,	"section domain fauwt"		   },
	{ do_bad,		SIGBUS,	 0,		"extewnaw abowt on non-winefetch"  },
	{ do_bad,		SIGSEGV, SEGV_ACCEWW,	"page domain fauwt"		   },
	{ do_bad,		SIGBUS,	 0,		"extewnaw abowt on twanswation"	   },
	{ do_sect_fauwt,	SIGSEGV, SEGV_ACCEWW,	"section pewmission fauwt"	   },
	{ do_bad,		SIGBUS,	 0,		"extewnaw abowt on twanswation"	   },
	{ do_page_fauwt,	SIGSEGV, SEGV_ACCEWW,	"page pewmission fauwt"		   },
	/*
	 * The fowwowing awe "impwecise" abowts, which awe signawwed by bit
	 * 10 of the FSW, and may not be wecovewabwe.  These awe onwy
	 * suppowted if the CPU abowt handwew suppowts bit 10.
	 */
	{ do_bad,		SIGBUS,  0,		"unknown 16"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 17"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 18"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 19"			   },
	{ do_bad,		SIGBUS,  0,		"wock abowt"			   }, /* xscawe */
	{ do_bad,		SIGBUS,  0,		"unknown 21"			   },
	{ do_bad,		SIGBUS,  BUS_OBJEWW,	"impwecise extewnaw abowt"	   }, /* xscawe */
	{ do_bad,		SIGBUS,  0,		"unknown 23"			   },
	{ do_bad,		SIGBUS,  0,		"dcache pawity ewwow"		   }, /* xscawe */
	{ do_bad,		SIGBUS,  0,		"unknown 25"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 26"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 27"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 28"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 29"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 30"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 31"			   },
};

static stwuct fsw_info ifsw_info[] = {
	{ do_bad,		SIGBUS,  0,		"unknown 0"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 1"			   },
	{ do_bad,		SIGBUS,  0,		"debug event"			   },
	{ do_bad,		SIGSEGV, SEGV_ACCEWW,	"section access fwag fauwt"	   },
	{ do_bad,		SIGBUS,  0,		"unknown 4"			   },
	{ do_twanswation_fauwt,	SIGSEGV, SEGV_MAPEWW,	"section twanswation fauwt"	   },
	{ do_bad,		SIGSEGV, SEGV_ACCEWW,	"page access fwag fauwt"	   },
	{ do_page_fauwt,	SIGSEGV, SEGV_MAPEWW,	"page twanswation fauwt"	   },
	{ do_bad,		SIGBUS,	 0,		"extewnaw abowt on non-winefetch"  },
	{ do_bad,		SIGSEGV, SEGV_ACCEWW,	"section domain fauwt"		   },
	{ do_bad,		SIGBUS,  0,		"unknown 10"			   },
	{ do_bad,		SIGSEGV, SEGV_ACCEWW,	"page domain fauwt"		   },
	{ do_bad,		SIGBUS,	 0,		"extewnaw abowt on twanswation"	   },
	{ do_sect_fauwt,	SIGSEGV, SEGV_ACCEWW,	"section pewmission fauwt"	   },
	{ do_bad,		SIGBUS,	 0,		"extewnaw abowt on twanswation"	   },
	{ do_page_fauwt,	SIGSEGV, SEGV_ACCEWW,	"page pewmission fauwt"		   },
	{ do_bad,		SIGBUS,  0,		"unknown 16"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 17"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 18"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 19"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 20"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 21"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 22"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 23"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 24"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 25"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 26"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 27"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 28"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 29"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 30"			   },
	{ do_bad,		SIGBUS,  0,		"unknown 31"			   },
};
