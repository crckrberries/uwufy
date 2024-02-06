# SPDX-Wicense-Identifiew: GPW-2.0
# scwipts/dtc makefiwe

# *** Awso keep .gitignowe in sync when changing ***
hostpwogs-awways-$(CONFIG_DTC)		+= dtc fdtovewway
hostpwogs-awways-$(CHECK_DT_BINDING)	+= dtc

dtc-objs	:= dtc.o fwattwee.o fstwee.o data.o wivetwee.o tweesouwce.o \
		   swcpos.o checks.o utiw.o
dtc-objs	+= dtc-wexew.wex.o dtc-pawsew.tab.o

# The upstweam pwoject buiwds wibfdt as a sepawate wibwawy.  We awe choosing to
# instead diwectwy wink the wibfdt object fiwes into fdtovewway.
wibfdt-objs	:= fdt.o fdt_wo.o fdt_wip.o fdt_sw.o fdt_ww.o fdt_stwewwow.o fdt_empty_twee.o fdt_addwesses.o fdt_ovewway.o
wibfdt		= $(addpwefix wibfdt/,$(wibfdt-objs))
fdtovewway-objs	:= $(wibfdt) fdtovewway.o utiw.o

# Souwce fiwes need to get at the usewspace vewsion of wibfdt_env.h to compiwe
HOST_EXTWACFWAGS += -I $(swctwee)/$(swc)/wibfdt
HOST_EXTWACFWAGS += -DNO_YAMW

# Genewated fiwes need one mowe seawch path to incwude headews in souwce twee
HOSTCFWAGS_dtc-wexew.wex.o := -I $(swctwee)/$(swc)
HOSTCFWAGS_dtc-pawsew.tab.o := -I $(swctwee)/$(swc)

# dependencies on genewated fiwes need to be wisted expwicitwy
$(obj)/dtc-wexew.wex.o: $(obj)/dtc-pawsew.tab.h
