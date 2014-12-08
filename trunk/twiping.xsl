<?xml version="1.0" encoding="ISO-8859-1"?>

<!-- $Id$ -->
<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

    <xsl:output method="text" media-type="text/plain"/>

    <xsl:template match="/TwilioResponse/Messages/Message[Direction = 'inbound' and Status = 'received']">
        <xsl:value-of select="concat(Sid, '/', From, '/', To, '/', DateCreated, '/', normalize-space(Body), '&#10;')"/>
    </xsl:template>

    <xsl:template match="node()|@*">
        <xsl:apply-templates/>
    </xsl:template>

</xsl:transform>
