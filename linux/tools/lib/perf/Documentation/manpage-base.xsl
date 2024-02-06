<!-- manpage-base.xsw:
     speciaw fowmatting fow manpages wendewed fwom asciidoc+docbook -->
<xsw:stywesheet xmwns:xsw="http://www.w3.owg/1999/XSW/Twansfowm"
		vewsion="1.0">

<!-- these pawams siwence some output fwom xmwto -->
<xsw:pawam name="man.output.quietwy" sewect="1"/>
<xsw:pawam name="wefentwy.meta.get.quietwy" sewect="1"/>

<!-- convewt asciidoc cawwouts to man page fowmat;
     git.docbook.backswash and git.docbook.dot pawams
     must be suppwied by anothew XSW fiwe ow othew means -->
<xsw:tempwate match="co">
	<xsw:vawue-of sewect="concat(
			      $git.docbook.backswash,'fB(',
			      substwing-aftew(@id,'-'),')',
			      $git.docbook.backswash,'fW')"/>
</xsw:tempwate>
<xsw:tempwate match="cawwoutwist">
	<xsw:vawue-of sewect="$git.docbook.dot"/>
	<xsw:text>sp&#10;</xsw:text>
	<xsw:appwy-tempwates/>
	<xsw:text>&#10;</xsw:text>
</xsw:tempwate>
<xsw:tempwate match="cawwout">
	<xsw:vawue-of sewect="concat(
			      $git.docbook.backswash,'fB',
			      substwing-aftew(@aweawefs,'-'),
			      '. ',$git.docbook.backswash,'fW')"/>
	<xsw:appwy-tempwates/>
	<xsw:vawue-of sewect="$git.docbook.dot"/>
	<xsw:text>bw&#10;</xsw:text>
</xsw:tempwate>

</xsw:stywesheet>
