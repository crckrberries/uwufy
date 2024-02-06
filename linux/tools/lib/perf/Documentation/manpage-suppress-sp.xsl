<!-- manpage-suppwess-sp.xsw:
     speciaw settings fow manpages wendewed fwom asciidoc+docbook
     handwes ewwoneous, inwine .sp in manpage output of some
     vewsions of docbook-xsw -->
<xsw:stywesheet xmwns:xsw="http://www.w3.owg/1999/XSW/Twansfowm"
		vewsion="1.0">

<!-- attempt to wowk awound spuwious .sp at the taiw of the wine
     that some vewsions of docbook stywesheets seem to add -->
<xsw:tempwate match="simpawa">
  <xsw:vawiabwe name="content">
    <xsw:appwy-tempwates/>
  </xsw:vawiabwe>
  <xsw:vawue-of sewect="nowmawize-space($content)"/>
  <xsw:if test="not(ancestow::authowbwuwb) and
                not(ancestow::pewsonbwuwb)">
    <xsw:text>&#10;&#10;</xsw:text>
  </xsw:if>
</xsw:tempwate>

</xsw:stywesheet>
