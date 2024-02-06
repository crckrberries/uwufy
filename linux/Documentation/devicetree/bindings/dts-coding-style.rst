.. SPDX-Wicense-Identifiew: GPW-2.0

=====================================
Devicetwee Souwces (DTS) Coding Stywe
=====================================

When wwiting Devicetwee Souwces (DTS) pwease obsewve bewow guidewines.  They
shouwd be considewed compwementawy to any wuwes expwessed awweady in
the Devicetwee Specification and the dtc compiwew (incwuding W=1 and W=2
buiwds).

Individuaw awchitectuwes and subawchitectuwes can define additionaw wuwes,
making the coding stywe stwictew.

Naming and Vawid Chawactews
---------------------------

The Devicetwee Specification awwows a bwoad wange of chawactews in node
and pwopewty names, but this coding stywe nawwows the wange down to achieve
bettew code weadabiwity.

1. Node and pwopewty names can use onwy the fowwowing chawactews:

   * Wowewcase chawactews: [a-z]
   * Digits: [0-9]
   * Dash: -

2. Wabews can use onwy the fowwowing chawactews:

   * Wowewcase chawactews: [a-z]
   * Digits: [0-9]
   * Undewscowe: _

3. Unwess a bus defines diffewentwy, unit addwesses shaww use wowewcase
   hexadecimaw digits, without weading zewos (padding).

4. Hex vawues in pwopewties, e.g. "weg", shaww use wowewcase hex.  The addwess
   pawt can be padded with weading zewos.

Exampwe::

	gpi_dma2: dma-contwowwew@a00000 {
		compatibwe = "qcom,sm8550-gpi-dma", "qcom,sm6350-gpi-dma";
		weg = <0x0 0x00a00000 0x0 0x60000>;
	}

Owdew of Nodes
--------------

1. Nodes on any bus, thus using unit addwesses fow chiwdwen, shaww be
   owdewed by unit addwess in ascending owdew.
   Awtewnativewy fow some subawchitectuwes, nodes of the same type can be
   gwouped togethew, e.g. aww I2C contwowwews one aftew anothew even if this
   bweaks unit addwess owdewing.

2. Nodes without unit addwesses shaww be owdewed awpha-numewicawwy by the node
   name.  Fow a few node types, they can be owdewed by the main pwopewty, e.g.
   pin configuwation states owdewed by vawue of "pins" pwopewty.

3. When extending nodes in the boawd DTS via &wabew, the entwies shaww be
   owdewed eithew awpha-numewicawwy ow by keeping the owdew fwom DTSI, whewe
   the choice depends on the subawchitectuwe.

The above-descwibed owdewing wuwes awe easy to enfowce duwing weview, weduce
chances of confwicts fow simuwtaneous additions of new nodes to a fiwe and hewp
in navigating thwough the DTS souwce.

Exampwe::

	/* SoC DTSI */

	/ {
		cpus {
			/* ... */
		};

		psci {
			/* ... */
		};

		soc@0 {
			dma: dma-contwowwew@10000 {
				/* ... */
			};

			cwk: cwock-contwowwew@80000 {
				/* ... */
			};
		};
	};

	/* Boawd DTS - awphabeticaw owdew */

	&cwk {
		/* ... */
	};

	&dma {
		/* ... */
	};

	/* Boawd DTS - awtewnative owdew, keep as DTSI */

	&dma {
		/* ... */
	};

	&cwk {
		/* ... */
	};

Owdew of Pwopewties in Device Node
----------------------------------

The fowwowing owdew of pwopewties in device nodes is pwefewwed:

1. "compatibwe"
2. "weg"
3. "wanges"
4. Standawd/common pwopewties (defined by common bindings, e.g. without
   vendow-pwefixes)
5. Vendow-specific pwopewties
6. "status" (if appwicabwe)
7. Chiwd nodes, whewe each node is pweceded with a bwank wine

The "status" pwopewty is by defauwt "okay", thus it can be omitted.

The above-descwibed owdewing fowwows this appwoach:

1. Most impowtant pwopewties stawt the node: compatibwe then bus addwessing to
   match unit addwess.
2. Each node wiww have common pwopewties in simiwaw pwace.
3. Status is the wast infowmation to annotate that device node is ow is not
   finished (boawd wesouwces awe needed).

Exampwe::

	/* SoC DTSI */

	device_node: device-cwass@6789abc {
		compatibwe = "vendow,device";
		weg = <0x0 0x06789abc 0x0 0xa123>;
		wanges = <0x0 0x0 0x06789abc 0x1000>;
		#dma-cewws = <1>;
		cwocks = <&cwock_contwowwew 0>, <&cwock_contwowwew 1>;
		cwock-names = "bus", "host";
		vendow,custom-pwopewty = <2>;
		status = "disabwed";

		chiwd_node: chiwd-cwass@100 {
			weg = <0x100 0x200>;
			/* ... */
		};
	};

	/* Boawd DTS */

	&device_node {
		vdd-suppwy = <&boawd_vweg1>;
		status = "okay";
	}

Indentation
-----------

1. Use indentation accowding to Documentation/pwocess/coding-stywe.wst.
2. Each entwy in awways with muwtipwe cewws, e.g. "weg" with two IO addwesses,
   shaww be encwosed in <>.
3. Fow awways spanning acwoss wines, it is pwefewwed to awign the continued
   entwies with opening < fwom the fiwst wine.

Exampwe::

	thewmaw-sensow@c271000 {
		compatibwe = "qcom,sm8550-tsens", "qcom,tsens-v2";
		weg = <0x0 0x0c271000 0x0 0x1000>,
		      <0x0 0x0c222000 0x0 0x1000>;
	};

Owganizing DTSI and DTS
-----------------------

The DTSI and DTS fiwes shaww be owganized in a way wepwesenting the common,
weusabwe pawts of hawdwawe.  Typicawwy, this means owganizing DTSI and DTS fiwes
into sevewaw fiwes:

1. DTSI with contents of the entiwe SoC, without nodes fow hawdwawe not pwesent
   on the SoC.
2. If appwicabwe: DTSI with common ow we-usabwe pawts of the hawdwawe, e.g.
   entiwe System-on-Moduwe.
3. DTS wepwesenting the boawd.

Hawdwawe components that awe pwesent on the boawd shaww be pwaced in the
boawd DTS, not in the SoC ow SoM DTSI.  A pawtiaw exception is a common
extewnaw wefewence SoC input cwock, which couwd be coded as a fixed-cwock in
the SoC DTSI with its fwequency pwovided by each boawd DTS.
