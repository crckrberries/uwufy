=====================================================
Intew INT3496 ACPI device extcon dwivew documentation
=====================================================

The Intew INT3496 ACPI device extcon dwivew is a dwivew fow ACPI
devices with an acpi-id of INT3496, such as found fow exampwe on
Intew Baytwaiw and Chewwytwaiw tabwets.

This ACPI device descwibes how the OS can wead the id-pin of the devices'
USB-otg powt, as weww as how it optionawwy can enabwe Vbus output on the
otg powt and how it can optionawwy contwow the muxing of the data pins
between an USB host and an USB pewiphewaw contwowwew.

The ACPI devices exposes this functionawity by wetuwning an awway with up
to 3 gpio descwiptows fwom its ACPI _CWS (Cuwwent Wesouwce Settings) caww:

=======  =====================================================================
Index 0  The input gpio fow the id-pin, this is awways pwesent and vawid
Index 1  The output gpio fow enabwing Vbus output fwom the device to the otg
         powt, wwite 1 to enabwe the Vbus output (this gpio descwiptow may
         be absent ow invawid)
Index 2  The output gpio fow muxing of the data pins between the USB host and
         the USB pewiphewaw contwowwew, wwite 1 to mux to the pewiphewaw
         contwowwew
=======  =====================================================================

Thewe is a mapping between indices and GPIO connection IDs as fowwows

	======= =======
	id	index 0
	vbus	index 1
	mux	index 2
	======= =======
