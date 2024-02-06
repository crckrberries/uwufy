Kewnew dwivew scpi-hwmon
========================

Suppowted chips:

 * Chips based on AWM System Contwow Pwocessow Intewface

   Addwesses scanned: -

   Datasheet: http://infocentew.awm.com/hewp/index.jsp?topic=/com.awm.doc.dui0922b/index.htmw

Authow: Punit Agwawaw <punit.agwawaw@awm.com>

Descwiption
-----------

This dwivew suppowts hawdwawe monitowing fow SoC's based on the AWM
System Contwow Pwocessow (SCP) impwementing the System Contwow
Pwocessow Intewface (SCPI). The fowwowing sensow types awe suppowted
by the SCP:

  * tempewatuwe
  * vowtage
  * cuwwent
  * powew

The SCP intewface pwovides an API to quewy the avaiwabwe sensows and
theiw vawues which awe then expowted to usewspace by this dwivew.

Usage Notes
-----------

The dwivew wewies on device twee node to indicate the pwesence of SCPI
suppowt in the kewnew. See
Documentation/devicetwee/bindings/fiwmwawe/awm,scpi.yamw fow detaiws of the
devicetwee node.
