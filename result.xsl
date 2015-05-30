<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

    <xsl:output method="text" media-type="text/plain"/>

    <xsl:template match="/">
        <xsl:choose>
            <xsl:when test="TwilioResponse/RestException">
                <xsl:apply-templates select="TwilioResponse/RestException"/>
            </xsl:when>
            <xsl:when test="TwilioResponse/Message"/>
            <xsl:otherwise>
                <xsl:text>Invalid XML response received&#10;</xsl:text>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>

    <xsl:template match="/TwilioResponse/RestException">
        <xsl:value-of select="concat('Twilio error #', Code, ': ', Message, '&#10;')"/>
    </xsl:template>

    <xsl:template match="node()|@*"/>

</xsl:transform>
