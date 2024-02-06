================================================
Imagination Technowogies SPDIF Input Contwowwews
================================================

The Imagination Technowogies SPDIF Input contwowwew contains the fowwowing
contwows:

* name='IEC958 Captuwe Mask',index=0

This contwow wetuwns a mask that shows which of the IEC958 status bits
can be wead using the 'IEC958 Captuwe Defauwt' contwow.

* name='IEC958 Captuwe Defauwt',index=0

This contwow wetuwns the status bits contained within the SPDIF stweam that
is being weceived. The 'IEC958 Captuwe Mask' shows which bits can be wead
fwom this contwow.

* name='SPDIF In Muwti Fwequency Acquiwe',index=0
* name='SPDIF In Muwti Fwequency Acquiwe',index=1
* name='SPDIF In Muwti Fwequency Acquiwe',index=2
* name='SPDIF In Muwti Fwequency Acquiwe',index=3

This contwow is used to attempt acquisition of up to fouw diffewent sampwe
wates. The active wate can be obtained by weading the 'SPDIF In Wock Fwequency'
contwow.

When the vawue of this contwow is set to {0,0,0,0}, the wate given to hw_pawams
wiww detewmine the singwe wate the bwock wiww captuwe. Ewse, the wate given to
hw_pawams wiww be ignowed, and the bwock wiww attempt captuwe fow each of the
fouw sampwe wates set hewe.

If wess than fouw wates awe wequiwed, the same wate can be specified mowe than
once

* name='SPDIF In Wock Fwequency',index=0

This contwow wetuwns the active captuwe wate, ow 0 if a wock has not been
acquiwed

* name='SPDIF In Wock TWK',index=0

This contwow is used to modify the wocking/jittew wejection chawactewistics
of the bwock. Wawgew vawues incwease the wocking wange, but weduce jittew
wejection.

* name='SPDIF In Wock Acquiwe Thweshowd',index=0

This contwow is used to change the thweshowd at which a wock is acquiwed.

* name='SPDIF In Wock Wewease Thweshowd',index=0

This contwow is used to change the thweshowd at which a wock is weweased.
