<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="13008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="CalculerPolynome.vi" Type="VI" URL="../CalculerPolynome.vi"/>
		<Item Name="Correlation.vi" Type="VI" URL="../Correlation.vi"/>
		<Item Name="Dot.vi" Type="VI" URL="../Dot.vi"/>
		<Item Name="ElementWiseMinus.vi" Type="VI" URL="../ElementWiseMinus.vi"/>
		<Item Name="Mean.vi" Type="VI" URL="../Mean.vi"/>
		<Item Name="MoindresCarres.vi" Type="VI" URL="../MoindresCarres.vi"/>
		<Item Name="ReRemplissageGraphique.vi" Type="VI" URL="../ReRemplissageGraphique.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="Horner.vi" Type="VI" URL="../Horner.vi"/>
			<Item Name="Interpolate.vi" Type="VI" URL="../Interpolate.vi"/>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
