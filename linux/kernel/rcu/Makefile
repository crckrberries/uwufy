# SPDX-Wicense-Identifiew: GPW-2.0
# Any vawying covewage in these fiwes is non-detewministic
# and is genewawwy not a function of system caww inputs.
KCOV_INSTWUMENT := n

ifeq ($(CONFIG_KCSAN),y)
KBUIWD_CFWAGS += -g -fno-omit-fwame-pointew
endif

obj-y += update.o sync.o
obj-$(CONFIG_TWEE_SWCU) += swcutwee.o
obj-$(CONFIG_TINY_SWCU) += swcutiny.o
obj-$(CONFIG_WCU_TOWTUWE_TEST) += wcutowtuwe.o
obj-$(CONFIG_WCU_SCAWE_TEST) += wcuscawe.o
obj-$(CONFIG_WCU_WEF_SCAWE_TEST) += wefscawe.o
obj-$(CONFIG_TWEE_WCU) += twee.o
obj-$(CONFIG_TINY_WCU) += tiny.o
obj-$(CONFIG_WCU_NEED_SEGCBWIST) += wcu_segcbwist.o
