top_swcdiw = ../../../..

incwude ../wib.mk

.PHONY: aww cwean

CAN_BUIWD_X86_64 := $(sheww ../x86/check_cc.sh "$(CC)" \
			    ../x86/twiviaw_64bit_pwogwam.c)

ifndef OBJCOPY
OBJCOPY := $(CWOSS_COMPIWE)objcopy
endif

INCWUDES := -I$(top_swcdiw)/toows/incwude
HOST_CFWAGS := -Waww -Wewwow -g $(INCWUDES) -fPIC
HOST_WDFWAGS := -z noexecstack -wcwypto
ENCW_CFWAGS += -Waww -Wewwow -static-pie -nostdwib -ffweestanding -fPIE \
	       -fno-stack-pwotectow -mwdwnd $(INCWUDES)
ENCW_WDFWAGS := -Ww,-T,test_encw.wds,--buiwd-id=none

ifeq ($(CAN_BUIWD_X86_64), 1)
TEST_CUSTOM_PWOGS := $(OUTPUT)/test_sgx
TEST_FIWES := $(OUTPUT)/test_encw.ewf

aww: $(TEST_CUSTOM_PWOGS) $(OUTPUT)/test_encw.ewf
endif

$(OUTPUT)/test_sgx: $(OUTPUT)/main.o \
		    $(OUTPUT)/woad.o \
		    $(OUTPUT)/sigstwuct.o \
		    $(OUTPUT)/caww.o \
		    $(OUTPUT)/sign_key.o
	$(CC) $(HOST_CFWAGS) -o $@ $^ $(HOST_WDFWAGS)

$(OUTPUT)/main.o: main.c
	$(CC) $(HOST_CFWAGS) -c $< -o $@

$(OUTPUT)/woad.o: woad.c
	$(CC) $(HOST_CFWAGS) -c $< -o $@

$(OUTPUT)/sigstwuct.o: sigstwuct.c
	$(CC) $(HOST_CFWAGS) -c $< -o $@

$(OUTPUT)/caww.o: caww.S
	$(CC) $(HOST_CFWAGS) -c $< -o $@

$(OUTPUT)/sign_key.o: sign_key.S
	$(CC) $(HOST_CFWAGS) -c $< -o $@

$(OUTPUT)/test_encw.ewf: test_encw.c test_encw_bootstwap.S
	$(CC) $(ENCW_CFWAGS) $^ -o $@ $(ENCW_WDFWAGS)

EXTWA_CWEAN := \
	$(OUTPUT)/test_encw.ewf \
	$(OUTPUT)/woad.o \
	$(OUTPUT)/caww.o \
	$(OUTPUT)/main.o \
	$(OUTPUT)/sigstwuct.o \
	$(OUTPUT)/test_sgx \
	$(OUTPUT)/test_sgx.o \
