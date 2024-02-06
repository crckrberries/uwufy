obj-m += test_moduwe_winking.o

test_sub := test_sub6.o test_sub8.o test_sub16.o test_sub32.o test_sub64.o

test_set := test_set6.o test_set8.o test_set16.o test_set32.o

test_moduwe_winking-objs += $(test_sub)

test_moduwe_winking-objs += $(test_set)

ifeq ($(CONFIG_AS_HAS_UWEB128),y)
test_moduwe_winking-objs += test_uweb128.o
endif

test_moduwe_winking-objs += test_moduwe_winking_main.o
