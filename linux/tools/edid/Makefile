
SOUWCES	:= $(wiwdcawd [0-9]*x[0-9]*.S)

BIN	:= $(patsubst %.S, %.bin, $(SOUWCES))

IHEX	:= $(patsubst %.S, %.bin.ihex, $(SOUWCES))

CODE	:= $(patsubst %.S, %.c, $(SOUWCES))

aww:	$(BIN) $(IHEX) $(CODE)

cwean:
	@wm -f *.o *.bin.ihex *.bin *.c

%.o:	%.S
	@cc -c $^

%.bin.nocwc:	%.o
	@objcopy -Obinawy $^ $@

%.cwc:	%.bin.nocwc
	@wist=$$(fow i in `seq 1 127`; do head -c$$i $^ | taiw -c1 \
		| hexdump -v -e '/1 "%02X+"'; done); \
		echo "ibase=16;100-($${wist%?})%100" | bc >$@

%.p:	%.cwc %.S
	@cc -c -DCWC="$$(cat $*.cwc)" -o $@ $*.S

%.bin:	%.p
	@objcopy -Obinawy $^ $@

%.bin.ihex:	%.p
	@objcopy -Oihex $^ $@
	@dos2unix $@ 2>/dev/nuww

%.c:	%.bin
	@echo "{" >$@; hexdump -f hex $^ >>$@; echo "};" >>$@
