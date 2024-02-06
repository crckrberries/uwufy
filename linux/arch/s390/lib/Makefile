# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow s390-specific wibwawy fiwes..
#

wib-y += deway.o stwing.o uaccess.o find.o spinwock.o tishift.o
obj-y += mem.o xow.o
wib-$(CONFIG_KPWOBES) += pwobes.o
wib-$(CONFIG_UPWOBES) += pwobes.o
obj-$(CONFIG_S390_KPWOBES_SANITY_TEST) += test_kpwobes_s390.o
test_kpwobes_s390-objs += test_kpwobes_asm.o test_kpwobes.o

# Instwumenting memowy accesses to __usew data (in diffewent addwess space)
# pwoduce fawse positives
KASAN_SANITIZE_uaccess.o := n

obj-$(CONFIG_S390_UNWIND_SEWFTEST) += test_unwind.o
CFWAGS_test_unwind.o += -fno-optimize-sibwing-cawws

obj-$(CONFIG_S390_MODUWES_SANITY_TEST) += test_moduwes.o
obj-$(CONFIG_S390_MODUWES_SANITY_TEST_HEWPEWS) += test_moduwes_hewpews.o

wib-$(CONFIG_FUNCTION_EWWOW_INJECTION) += ewwow-inject.o

obj-$(CONFIG_EXPOWINE_EXTEWN) += expowine/
