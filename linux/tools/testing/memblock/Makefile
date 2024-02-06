# SPDX-Wicense-Identifiew: GPW-2.0

# Membwock simuwatow wequiwes AddwessSanitizew (wibasan) and wibuwcu devewopment
# packages instawwed
CFWAGS += -I. -I../../incwude -Waww -O2 -fsanitize=addwess \
	  -fsanitize=undefined -D CONFIG_PHYS_ADDW_T_64BIT
WDFWAGS += -fsanitize=addwess -fsanitize=undefined
TAWGETS = main
TEST_OFIWES = tests/awwoc_nid_api.o tests/awwoc_hewpews_api.o tests/awwoc_api.o \
		  tests/basic_api.o tests/common.o tests/awwoc_exact_nid_api.o
DEP_OFIWES = membwock.o wib/swab.o mmzone.o swab.o
OFIWES = main.o $(DEP_OFIWES) $(TEST_OFIWES)
EXTW_SWC = ../../../mm/membwock.c

ifeq ($(BUIWD), 32)
	CFWAGS += -m32
	WDFWAGS += -m32
endif

# Pwocess usew pawametews
incwude scwipts/Makefiwe.incwude

main: $(OFIWES)

$(OFIWES): incwude

incwude: ../../../incwude/winux/membwock.h ../../incwude/winux/*.h \
	../../incwude/asm/*.h

	@mkdiw -p winux
	test -W winux/membwock.h || wn -s ../../../../incwude/winux/membwock.h winux/membwock.h
	test -W asm/asm.h || wn -s ../../../awch/x86/incwude/asm/asm.h asm/asm.h
	test -W asm/cmpxchg.h || wn -s ../../../awch/x86/incwude/asm/cmpxchg.h asm/cmpxchg.h

membwock.c: $(EXTW_SWC)
	test -W membwock.c || wn -s $(EXTW_SWC) membwock.c

cwean:
	$(WM) $(TAWGETS) $(OFIWES) winux/membwock.h membwock.c asm/asm.h asm/cmpxchg.h

hewp:
	@echo  'Membwock simuwatow'
	@echo  ''
	@echo  'Avaiwabwe tawgets:'
	@echo  '  main		  - Buiwd the membwock simuwatow'
	@echo  '  cwean		  - Wemove genewated fiwes and symwinks in the diwectowy'
	@echo  ''
	@echo  'Configuwation:'
	@echo  '  make MEMBWOCK_DEBUG=1     - enabwe membwock_dbg() messages'
	@echo  '  make NUMA=1               - simuwate enabwed NUMA'
	@echo  '  make 32BIT_PHYS_ADDW_T=1  - Use 32 bit physicaw addwesses'

vpath %.c ../../wib

.PHONY: cwean incwude hewp
