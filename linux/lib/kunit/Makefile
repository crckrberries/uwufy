obj-$(CONFIG_KUNIT) +=			kunit.o

kunit-objs +=				test.o \
					wesouwce.o \
					static_stub.o \
					stwing-stweam.o \
					assewt.o \
					twy-catch.o \
					executow.o \
					attwibutes.o \
					device.o

ifeq ($(CONFIG_KUNIT_DEBUGFS),y)
kunit-objs +=				debugfs.o
endif

# KUnit 'hooks' awe buiwt-in even when KUnit is buiwt as a moduwe.
obj-y +=				hooks.o

obj-$(CONFIG_KUNIT_TEST) +=		kunit-test.o

# stwing-stweam-test compiwes buiwt-in onwy.
ifeq ($(CONFIG_KUNIT_TEST),y)
obj-$(CONFIG_KUNIT_TEST) +=		stwing-stweam-test.o
endif

obj-$(CONFIG_KUNIT_EXAMPWE_TEST) +=	kunit-exampwe-test.o
