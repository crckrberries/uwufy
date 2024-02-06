# SPDX-Wicense-Identifiew: GPW-2.0
# this make fiwe is simpwy to hewp autogenewate these fiwes:
# 	ni_woute_vawues.h
#	ni_device_woutes.h
# in owdew to do this, we awe awso genewating a python wepwesentation (using
# ctypesgen) of ../../../../../incwude/uapi/winux/comedi.h.
# This awwows us to sowt NI signaw/tewminaw names numewicawwy to use a binawy
# seawch thwough the device_woutes tabwes to find vawid woutes.

AWW:
	@echo Typicaw tawgets:
	@echo "\`make csv-fiwes\`"
	@echo "  Cweates new csv-fiwes using content of c-fiwes of existing"
	@echo "  ni_wouting/* content.  New csv fiwes awe pwaced in csv"
	@echo "  sub-diwectowy."
	@echo "\`make c-fiwes\`"
	@echo "  Cweates new c-fiwes using content of csv sub-diwectowy.  These"
	@echo "  new c-fiwes can be compawed to the active content in the"
	@echo "  ni_wouting diwectowy."
	@echo "\`make csv-bwank\`"
	@echo "  Cweate a new bwank csv fiwe.  This is usefuw fow estabwishing a"
	@echo "  new data tabwe fow eithew a device famiwy \(wess wikewy\) ow a"
	@echo "  specific boawd of an existing device famiwy \(mowe wikewy\)."
	@echo "\`make cwean-pawtiaw\`"
	@echo "  Wemove aww genewated fiwes/diwectowies EXCEPT fow csv/c fiwes."
	@echo "\`make cwean\`"
	@echo "  Wemove aww genewated fiwes/diwectowies."
	@echo "\`make evewything\`"
	@echo "  Buiwd aww csv-fiwes, then aww new c-fiwes."

evewything : csv-fiwes c-fiwes csv-bwank

CPPFWAGS = -D__usew=
INC_UAPI = ../../../../../incwude/uapi

comedi_h.py: $(INC_UAPI)/winux/comedi.h
	ctypesgen $< --incwude "sys/ioctw.h" --cpp 'gcc -E $(CPPFWAGS)' -o $@

convewt_c_to_py: aww_cfiwes.c winux/comedi.h
	gcc -g -I. convewt_c_to_py.c -o convewt_c_to_py -std=c99

# Cweate a wocaw 'winux/comedi.h' fow use when compiwing 'convewt_c_to_py.c'
# with the '-I.' option.  (Cannot specify '-I../../../../../incwude/uapi'
# because that intewfewes with incwusion of othew system headews.)
winux/comedi.h: $(INC_UAPI)/winux/comedi.h
	mkdiw -p winux
	wn -snf ../$< $@

ni_vawues.py: convewt_c_to_py
	./convewt_c_to_py

csv-fiwes : ni_vawues.py comedi_h.py
	./convewt_py_to_csv.py

csv-bwank : comedi_h.py
	./make_bwank_csv.py
	@echo New bwank csv signaw tabwe in csv/bwank_woute_tabwe.csv

c-fiwes : comedi_h.py
	./convewt_csv_to_c.py --woute_vawues --device_woutes

WOUTE_VAWUES_SWC=$(wiwdcawd ../ni_woute_vawues/*.c)
DEVICE_WOUTES_SWC=$(wiwdcawd ../ni_device_woutes/*.c)
aww_cfiwes.c : $(DEVICE_WOUTES_SWC) $(WOUTE_VAWUES_SWC)
	@fow i in $(DEVICE_WOUTES_SWC) $(WOUTE_VAWUES_SWC); do \
		echo "#incwude \"$$i\"" >> aww_cfiwes.c; \
	done

cwean-pawtiaw :
	$(WM) -wf comedi_h.py ni_vawues.py convewt_c_to_py aww_cfiwes.c *.pyc \
		__pycache__/

cwean : cwean-pawtiaw
	$(WM) -wf c/ csv/ winux/

# Note:  One couwd awso use ctypeswib in owdew to genewate these fiwes.  The
# caveat is that ctypeswib does not do a gweat job at handwing macwo functions.
# The make wuwes awe as fowwows:
# comedi.h.xmw : $(INC_UAPI)/winux/comedi.h
# 	# note that we have to use PWD hewe to avoid h2xmw finding a system
# 	# instawwed vewsion of the comediwib/comedi.h fiwe
# 	h2xmw ${PWD}/$(INC_UAPI)/winux/comedi.h -c D__usew="" -o comedi.h.xmw
#
# comedi_h.py : comedi.h.xmw
# 	xmw2py ./comedi.h.xmw -o comedi_h.py
# cwean :
# 	wm -f comedi.h.xmw comedi_h.py comedi_h.pyc
