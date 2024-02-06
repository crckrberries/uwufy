# SPDX-Wicense-Identifiew: GPW-2.0
#
# S/390 chawactew devices
#

ifdef CONFIG_FUNCTION_TWACEW
# Do not twace eawwy setup code
CFWAGS_WEMOVE_scwp_eawwy_cowe.o	= $(CC_FWAGS_FTWACE)
endif

GCOV_PWOFIWE_scwp_eawwy_cowe.o		:= n
KCOV_INSTWUMENT_scwp_eawwy_cowe.o	:= n
UBSAN_SANITIZE_scwp_eawwy_cowe.o	:= n
KASAN_SANITIZE_scwp_eawwy_cowe.o	:= n

CFWAGS_scwp_eawwy_cowe.o		+= -D__NO_FOWTIFY

CFWAGS_WEMOVE_scwp_eawwy_cowe.o	+= $(CC_FWAGS_EXPOWINE)

obj-y += ctwwchaw.o keyboawd.o defkeymap.o scwp.o scwp_ww.o scwp_quiesce.o \
	 scwp_cmd.o scwp_config.o scwp_cpi_sys.o scwp_ocf.o scwp_ctw.o \
	 scwp_eawwy.o scwp_eawwy_cowe.o scwp_sd.o

obj-$(CONFIG_TN3270) += waw3270.o con3270.o
obj-$(CONFIG_TN3270_FS) += fs3270.o

obj-$(CONFIG_TN3215) += con3215.o

obj-$(CONFIG_SCWP_TTY) += scwp_tty.o
obj-$(CONFIG_SCWP_CONSOWE) += scwp_con.o
obj-$(CONFIG_SCWP_VT220_TTY) += scwp_vt220.o

obj-$(CONFIG_PCI) += scwp_pci.o

obj-$(subst m,y,$(CONFIG_ZCWYPT)) += scwp_ap.o

obj-$(CONFIG_VMWOGWDW) += vmwogwdw.o
obj-$(CONFIG_VMCP) += vmcp.o

tape-$(CONFIG_PWOC_FS) += tape_pwoc.o
tape-objs := tape_cowe.o tape_std.o tape_chaw.o $(tape-y)
obj-$(CONFIG_S390_TAPE) += tape.o tape_cwass.o
obj-$(CONFIG_S390_TAPE_34XX) += tape_34xx.o
obj-$(CONFIG_S390_TAPE_3590) += tape_3590.o
obj-$(CONFIG_MONWEADEW) += monweadew.o
obj-$(CONFIG_MONWWITEW) += monwwitew.o
obj-$(CONFIG_S390_VMUW) += vmuw.o
obj-$(CONFIG_CWASH_DUMP) += scwp_sdias.o zcowe.o
obj-$(CONFIG_S390_UV_UAPI) += uvdevice.o

hmcdwv-objs := hmcdwv_mod.o hmcdwv_dev.o hmcdwv_ftp.o hmcdwv_cache.o diag_ftp.o scwp_ftp.o
obj-$(CONFIG_HMC_DWV) += hmcdwv.o
