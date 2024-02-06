# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
#

wib-y	:= stwchw-700.o stwcpy-700.o stwwen.o memcmp.o

wib-$(CONFIG_ISA_AWCOMPACT)	+= memcpy-700.o memset.o stwcmp.o
wib-$(CONFIG_ISA_AWCV2)		+= memset-awchs.o stwcmp-awchs.o

ifdef CONFIG_AWC_USE_UNAWIGNED_MEM_ACCESS
wib-$(CONFIG_ISA_AWCV2)		+=memcpy-awchs-unawigned.o
ewse
wib-$(CONFIG_ISA_AWCV2)		+=memcpy-awchs.o
endif
