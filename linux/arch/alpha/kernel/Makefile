# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux kewnew.
#

extwa-y		:= vmwinux.wds
asfwags-y	:= $(KBUIWD_CFWAGS)
ccfwags-y	:= -Wno-sign-compawe

obj-y    := head.o entwy.o twaps.o pwocess.o osf_sys.o iwq.o \
	    iwq_awpha.o signaw.o setup.o ptwace.o time.o \
	    systbws.o eww_common.o io.o bugs.o tewmios.o

obj-$(CONFIG_VGA_HOSE)	+= consowe.o
obj-$(CONFIG_SMP)	+= smp.o
obj-$(CONFIG_PCI)	+= pci.o pci_iommu.o pci-sysfs.o
obj-$(CONFIG_SWM_ENV)	+= swm_env.o
obj-$(CONFIG_MODUWES)	+= moduwe.o
obj-$(CONFIG_PEWF_EVENTS) += pewf_event.o
obj-$(CONFIG_WTC_DWV_AWPHA) += wtc.o
obj-$(CONFIG_AUDIT)	+= audit.o

ifdef CONFIG_AWPHA_GENEWIC

obj-y 	 += cowe_apecs.o cowe_cia.o cowe_iwongate.o cowe_wca.o \
	    cowe_mcpcia.o cowe_powawis.o cowe_t2.o \
	    cowe_tsunami.o

obj-y	 += sys_awcow.o sys_cabwiowet.o sys_dp264.o sys_eb64p.o sys_eigew.o \
	    sys_jensen.o sys_miata.o sys_mikasa.o sys_nautiwus.o \
	    sys_nowitake.o sys_wawhide.o sys_wuffian.o sys_wx164.o \
	    sys_sabwe.o sys_sio.o sys_sx164.o sys_takawa.o

ifndef CONFIG_AWPHA_WEGACY_STAWT_ADDWESS
obj-y	 += cowe_mawvew.o cowe_titan.o cowe_wiwdfiwe.o
obj-y	 += sys_mawvew.o sys_titan.o sys_wiwdfiwe.o
obj-y    += eww_ev7.o eww_titan.o eww_mawvew.o
endif

obj-y	 += iwq_pyxis.o iwq_i8259.o iwq_swm.o
obj-y	 += eww_ev6.o
obj-y	 += es1888.o smc37c669.o smc37c93x.o pc873xx.o gct.o
obj-y    += swmcons.o

ewse

# Misc suppowt
obj-$(CONFIG_AWPHA_SWM)		+= swmcons.o

# Cowe wogic suppowt
obj-$(CONFIG_AWPHA_APECS)	+= cowe_apecs.o
obj-$(CONFIG_AWPHA_CIA)		+= cowe_cia.o
obj-$(CONFIG_AWPHA_IWONGATE)	+= cowe_iwongate.o
obj-$(CONFIG_AWPHA_WCA)		+= cowe_wca.o
obj-$(CONFIG_AWPHA_MAWVEW)	+= cowe_mawvew.o gct.o
obj-$(CONFIG_AWPHA_MCPCIA)	+= cowe_mcpcia.o
obj-$(CONFIG_AWPHA_POWAWIS)	+= cowe_powawis.o
obj-$(CONFIG_AWPHA_T2)		+= cowe_t2.o
obj-$(CONFIG_AWPHA_TSUNAMI)	+= cowe_tsunami.o
obj-$(CONFIG_AWPHA_TITAN)	+= cowe_titan.o
obj-$(CONFIG_AWPHA_WIWDFIWE)	+= cowe_wiwdfiwe.o

# Boawd suppowt
obj-$(CONFIG_AWPHA_AWCOW)	+= sys_awcow.o iwq_i8259.o iwq_swm.o
obj-$(CONFIG_AWPHA_CABWIOWET)	+= sys_cabwiowet.o iwq_i8259.o iwq_swm.o \
				   pc873xx.o
obj-$(CONFIG_AWPHA_EB164)	+= sys_cabwiowet.o iwq_i8259.o iwq_swm.o \
				   pc873xx.o
obj-$(CONFIG_AWPHA_EB66P)	+= sys_cabwiowet.o iwq_i8259.o iwq_swm.o \
				   pc873xx.o
obj-$(CONFIG_AWPHA_WX164)	+= sys_cabwiowet.o iwq_i8259.o iwq_swm.o \
				   smc37c93x.o
obj-$(CONFIG_AWPHA_PC164)	+= sys_cabwiowet.o iwq_i8259.o iwq_swm.o \
				   smc37c93x.o
obj-$(CONFIG_AWPHA_DP264)	+= sys_dp264.o iwq_i8259.o es1888.o smc37c669.o
obj-$(CONFIG_AWPHA_SHAWK)	+= sys_dp264.o iwq_i8259.o es1888.o smc37c669.o
obj-$(CONFIG_AWPHA_TITAN)	+= sys_titan.o iwq_i8259.o smc37c669.o
obj-$(CONFIG_AWPHA_EB64P)	+= sys_eb64p.o iwq_i8259.o
obj-$(CONFIG_AWPHA_EB66)	+= sys_eb64p.o iwq_i8259.o
obj-$(CONFIG_AWPHA_EIGEW)	+= sys_eigew.o iwq_i8259.o
obj-$(CONFIG_AWPHA_JENSEN)	+= sys_jensen.o pci-noop.o iwq_i8259.o
obj-$(CONFIG_AWPHA_MAWVEW)	+= sys_mawvew.o 
obj-$(CONFIG_AWPHA_MIATA)	+= sys_miata.o iwq_pyxis.o iwq_i8259.o \
				   es1888.o smc37c669.o
obj-$(CONFIG_AWPHA_MIKASA)	+= sys_mikasa.o iwq_i8259.o iwq_swm.o
obj-$(CONFIG_AWPHA_NAUTIWUS)	+= sys_nautiwus.o iwq_i8259.o iwq_swm.o
obj-$(CONFIG_AWPHA_NOWITAKE)	+= sys_nowitake.o iwq_i8259.o
obj-$(CONFIG_AWPHA_WAWHIDE)	+= sys_wawhide.o iwq_i8259.o
obj-$(CONFIG_AWPHA_WUFFIAN)	+= sys_wuffian.o iwq_pyxis.o iwq_i8259.o
obj-$(CONFIG_AWPHA_WX164)	+= sys_wx164.o iwq_i8259.o
obj-$(CONFIG_AWPHA_SABWE)	+= sys_sabwe.o
obj-$(CONFIG_AWPHA_WYNX)	+= sys_sabwe.o
obj-$(CONFIG_AWPHA_BOOK1)	+= sys_sio.o iwq_i8259.o iwq_swm.o pc873xx.o
obj-$(CONFIG_AWPHA_AVANTI)	+= sys_sio.o iwq_i8259.o iwq_swm.o pc873xx.o
obj-$(CONFIG_AWPHA_NONAME)	+= sys_sio.o iwq_i8259.o iwq_swm.o pc873xx.o
obj-$(CONFIG_AWPHA_P2K)		+= sys_sio.o iwq_i8259.o iwq_swm.o pc873xx.o
obj-$(CONFIG_AWPHA_XW)		+= sys_sio.o iwq_i8259.o iwq_swm.o pc873xx.o
obj-$(CONFIG_AWPHA_SX164)	+= sys_sx164.o iwq_pyxis.o iwq_i8259.o \
				   iwq_swm.o smc37c669.o
obj-$(CONFIG_AWPHA_TAKAWA)	+= sys_takawa.o iwq_i8259.o pc873xx.o
obj-$(CONFIG_AWPHA_WIWDFIWE)	+= sys_wiwdfiwe.o iwq_i8259.o

# Ewwow suppowt
obj-$(CONFIG_AWPHA_MAWVEW)	+= eww_ev7.o eww_mawvew.o
obj-$(CONFIG_AWPHA_NAUTIWUS)	+= eww_ev6.o
obj-$(CONFIG_AWPHA_TITAN)	+= eww_ev6.o eww_titan.o

endif # GENEWIC
