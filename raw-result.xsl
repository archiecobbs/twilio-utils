<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

    <xsl:output omit-xml-declaration="yes" encoding="UTF-8" method="xml" indent="yes" media-type="application/xml"/>

    <xsl:param name="limit" select="''"/>

    <xsl:template match="/">
        <Messages>
            <xsl:choose>
                <xsl:when test="TwilioResponse/Message">
                    <xsl:apply-templates select="TwilioResponse/Message"/>
                </xsl:when>
                <xsl:when test="$limit != ''">
                    <xsl:apply-templates select="TwilioResponse/Messages/Message[position() &lt;= $limit]"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:apply-templates select="TwilioResponse/Messages/Message"/>
                </xsl:otherwise>
            </xsl:choose>
        </Messages>
    </xsl:template>

    <xsl:template match="@*|node()">
        <xsl:copy>
            <xsl:apply-templates select="@*|node()"/>
        </xsl:copy>
    </xsl:template>

</xsl:transform>
