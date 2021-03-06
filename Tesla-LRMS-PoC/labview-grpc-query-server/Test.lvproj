﻿<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="19008000">
	<Property Name="varPersistentID:{7717C06C-857A-4430-8869-E1DBC9469BB7}" Type="Ref">/NI-PXIe-8861-031E42AB/Acquisition Finished.lvlib/Acquisition Finished</Property>
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
		<Item Name="Dependencies" Type="Dependencies"/>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
	<Item Name="NI-PXIe-8861-031E42AB" Type="RT PXI Chassis">
		<Property Name="alias.name" Type="Str">NI-PXIe-8861-031E42AB</Property>
		<Property Name="alias.value" Type="Str">169.254.111.217</Property>
		<Property Name="CCSymbols" Type="Str">TARGET_TYPE,RT;OS,Linux;CPU,x64;</Property>
		<Property Name="host.ResponsivenessCheckEnabled" Type="Bool">true</Property>
		<Property Name="host.ResponsivenessCheckPingDelay" Type="UInt">5000</Property>
		<Property Name="host.ResponsivenessCheckPingTimeout" Type="UInt">1000</Property>
		<Property Name="host.TargetCPUID" Type="UInt">9</Property>
		<Property Name="host.TargetOSID" Type="UInt">19</Property>
		<Property Name="target.cleanupVisa" Type="Bool">false</Property>
		<Property Name="target.FPProtocolGlobals_ControlTimeLimit" Type="Int">300</Property>
		<Property Name="target.getDefault-&gt;WebServer.Port" Type="Int">80</Property>
		<Property Name="target.getDefault-&gt;WebServer.Timeout" Type="Int">60</Property>
		<Property Name="target.IOScan.Faults" Type="Str"></Property>
		<Property Name="target.IOScan.NetVarPeriod" Type="UInt">100</Property>
		<Property Name="target.IOScan.NetWatchdogEnabled" Type="Bool">false</Property>
		<Property Name="target.IOScan.Period" Type="UInt">10000</Property>
		<Property Name="target.IOScan.PowerupMode" Type="UInt">0</Property>
		<Property Name="target.IOScan.Priority" Type="UInt">0</Property>
		<Property Name="target.IOScan.ReportModeConflict" Type="Bool">true</Property>
		<Property Name="target.IsRemotePanelSupported" Type="Bool">true</Property>
		<Property Name="target.RTCPULoadMonitoringEnabled" Type="Bool">true</Property>
		<Property Name="target.RTDebugWebServerHTTPPort" Type="Int">8001</Property>
		<Property Name="target.RTTarget.ApplicationPath" Type="Path">/home/lvuser/natinst/bin/startup.rtexe</Property>
		<Property Name="target.RTTarget.EnableFileSharing" Type="Bool">true</Property>
		<Property Name="target.RTTarget.IPAccess" Type="Str">+*</Property>
		<Property Name="target.RTTarget.LaunchAppAtBoot" Type="Bool">true</Property>
		<Property Name="target.RTTarget.VIPath" Type="Path">/home/lvuser/natinst/bin</Property>
		<Property Name="target.server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="target.server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="target.server.tcp.access" Type="Str">+*</Property>
		<Property Name="target.server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="target.server.tcp.paranoid" Type="Bool">true</Property>
		<Property Name="target.server.tcp.port" Type="Int">3363</Property>
		<Property Name="target.server.tcp.serviceName" Type="Str">Main Application Instance/VI Server</Property>
		<Property Name="target.server.tcp.serviceName.default" Type="Str">Main Application Instance/VI Server</Property>
		<Property Name="target.server.vi.access" Type="Str">+*</Property>
		<Property Name="target.server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="target.server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="target.WebServer.Config" Type="Str">Listen 8000

NI.ServerName default
DocumentRoot "$LVSERVER_DOCROOT"
TypesConfig "$LVSERVER_CONFIGROOT/mime.types"
DirectoryIndex index.htm
WorkerLimit 10
InactivityTimeout 60

LoadModulePath "$LVSERVER_MODULEPATHS"
LoadModule LVAuth lvauthmodule
LoadModule LVRFP lvrfpmodule

#
# Pipeline Definition
#

SetConnector netConnector

AddHandler LVAuth
AddHandler LVRFP

AddHandler fileHandler ""

AddOutputFilter chunkFilter


</Property>
		<Property Name="target.WebServer.Enabled" Type="Bool">false</Property>
		<Property Name="target.WebServer.LogEnabled" Type="Bool">false</Property>
		<Property Name="target.WebServer.LogPath" Type="Path">/c/ni-rt/system/www/www.log</Property>
		<Property Name="target.WebServer.Port" Type="Int">80</Property>
		<Property Name="target.WebServer.RootPath" Type="Path">/c/ni-rt/system/www</Property>
		<Property Name="target.WebServer.TcpAccess" Type="Str">c+*</Property>
		<Property Name="target.WebServer.Timeout" Type="Int">60</Property>
		<Property Name="target.WebServer.ViAccess" Type="Str">+*</Property>
		<Property Name="target.webservices.SecurityAPIKey" Type="Str">PqVr/ifkAQh+lVrdPIykXlFvg12GhhQFR8H9cUhphgg=:pTe9HRlQuMfJxAG6QCGq7UvoUpJzAzWGKy5SbZ+roSU=</Property>
		<Property Name="target.webservices.ValidTimestampWindow" Type="Int">15</Property>
		<Item Name="Acquisition Finished.lvlib" Type="Library" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/Acquisition Finished.lvlib"/>
		<Item Name="ExampleMeasurementServer.vi" Type="VI" URL="../ExampleMeasurementServer.vi"/>
		<Item Name="Four Probe Asynchronous.vi" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/Four Probe Asynchronous.vi"/>
		<Item Name="jsontestfile.json" Type="Document" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/jsontestfile.json"/>
		<Item Name="liblabview_measurement_server.so" Type="Document" URL="../../liblabview_measurement_server.so"/>
		<Item Name="Send Error Stream.vi" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/Send Error Stream.vi"/>
		<Item Name="Stream Four Probe Asynchronous.vi" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/Stream Four Probe Asynchronous.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="instr.lib" Type="Folder">
				<Item Name="niDCPower Abort.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Abort.vi"/>
				<Item Name="niDCPower Close.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Close.vi"/>
				<Item Name="niDCPower Commit.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Commit.vi"/>
				<Item Name="niDCPower Configure Digital Edge Measure Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Configure Digital Edge Measure Trigger.vi"/>
				<Item Name="niDCPower Configure Digital Edge Pulse Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Configure Digital Edge Pulse Trigger.vi"/>
				<Item Name="niDCPower Configure Digital Edge Sequence Advance Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Configure Digital Edge Sequence Advance Trigger.vi"/>
				<Item Name="niDCPower Configure Digital Edge Source Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Configure Digital Edge Source Trigger.vi"/>
				<Item Name="niDCPower Configure Digital Edge Start Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Configure Digital Edge Start Trigger.vi"/>
				<Item Name="niDCPower Configure Software Edge Measure Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Configure Software Edge Measure Trigger.vi"/>
				<Item Name="niDCPower Configure Software Edge Pulse Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Configure Software Edge Pulse Trigger.vi"/>
				<Item Name="niDCPower Configure Software Edge Sequence Advance Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Configure Software Edge Sequence Advance Trigger.vi"/>
				<Item Name="niDCPower Configure Software Edge Source Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Configure Software Edge Source Trigger.vi"/>
				<Item Name="niDCPower Configure Software Edge Start Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Configure Software Edge Start Trigger.vi"/>
				<Item Name="niDCPower Configure Trigger (Poly).vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Configure Trigger (Poly).vi"/>
				<Item Name="niDCPower Create Advanced Sequence Step.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Create Advanced Sequence Step.vi"/>
				<Item Name="niDCPower Create Advanced Sequence.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Create Advanced Sequence.vi"/>
				<Item Name="niDCPower Delete Advanced Sequence.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Delete Advanced Sequence.vi"/>
				<Item Name="niDCPower Digital Edge - Edge.ctl" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Digital Edge - Edge.ctl"/>
				<Item Name="niDCPower Disable Pulse Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Disable Pulse Trigger.vi"/>
				<Item Name="niDCPower Disable Sequence Advance Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Disable Sequence Advance Trigger.vi"/>
				<Item Name="niDCPower Disable Source Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Disable Source Trigger.vi"/>
				<Item Name="niDCPower Disable Start Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Disable Start Trigger.vi"/>
				<Item Name="niDCPower Export Signal - Signal.ctl" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Export Signal - Signal.ctl"/>
				<Item Name="niDCPower Export Signal.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Export Signal.vi"/>
				<Item Name="niDCPower Fetch Multiple.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Fetch Multiple.vi"/>
				<Item Name="niDCPower Initialize With Channels.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Initialize With Channels.vi"/>
				<Item Name="niDCPower Initiate.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Initiate.vi"/>
				<Item Name="niDCPower IVI Error Converter.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower IVI Error Converter.vi"/>
				<Item Name="niDCPower Reset.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Reset.vi"/>
				<Item Name="niDCPower Send Software Edge Trigger - Signal.ctl" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Send Software Edge Trigger - Signal.ctl"/>
				<Item Name="niDCPower Send Software Edge Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDCPower/nidcpower.llb/niDCPower Send Software Edge Trigger.vi"/>
				<Item Name="niDMM Abort.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Abort.vi"/>
				<Item Name="niDMM Acquisition State.ctl" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Acquisition State.ctl"/>
				<Item Name="niDMM Close.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Close.vi"/>
				<Item Name="niDMM Config Measurement.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Config Measurement.vi"/>
				<Item Name="niDMM Configure Measurement Absolute.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Configure Measurement Absolute.vi"/>
				<Item Name="niDMM Configure Measurement Digits.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Configure Measurement Digits.vi"/>
				<Item Name="niDMM Configure Multi Point.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Configure Multi Point.vi"/>
				<Item Name="niDMM Configure Sample Trigger Slope.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Configure Sample Trigger Slope.vi"/>
				<Item Name="niDMM Configure Trigger Slope.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Configure Trigger Slope.vi"/>
				<Item Name="niDMM Configure Trigger.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Configure Trigger.vi"/>
				<Item Name="niDMM Control Actions.ctl" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Control Actions.ctl"/>
				<Item Name="niDMM Control.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Control.vi"/>
				<Item Name="niDMM Fetch Multi Point.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Fetch Multi Point.vi"/>
				<Item Name="niDMM Function To IVI Constant.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Function To IVI Constant.vi"/>
				<Item Name="niDMM Function.ctl" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Function.ctl"/>
				<Item Name="niDMM Initialize.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Initialize.vi"/>
				<Item Name="niDMM Initiate.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Initiate.vi"/>
				<Item Name="niDMM IVI Error Converter.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM IVI Error Converter.vi"/>
				<Item Name="niDMM Read Status.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Read Status.vi"/>
				<Item Name="niDMM Resolution in Digits.ctl" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Resolution in Digits.ctl"/>
				<Item Name="niDMM Sample Trigger To IVI Constant.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Sample Trigger To IVI Constant.vi"/>
				<Item Name="niDMM Sample Trigger.ctl" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Sample Trigger.ctl"/>
				<Item Name="niDMM Slope To IVI Constant.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Slope To IVI Constant.vi"/>
				<Item Name="niDMM Slope.ctl" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Slope.ctl"/>
				<Item Name="niDMM Trigger Source To IVI Constant.vi" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Trigger Source To IVI Constant.vi"/>
				<Item Name="niDMM Trigger.ctl" Type="VI" URL="/&lt;instrlib&gt;/niDMM/nidmm.llb/niDMM Trigger.ctl"/>
				<Item Name="niSwitch Close.vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Close.vi"/>
				<Item Name="niSwitch Connect Channels (Multiple).vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Connect Channels (Multiple).vi"/>
				<Item Name="niSwitch Connect Channels (Single).vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Connect Channels (Single).vi"/>
				<Item Name="niSwitch Connect Channels.vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Connect Channels.vi"/>
				<Item Name="niSwitch Disconnect Channels (Multiple).vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Disconnect Channels (Multiple).vi"/>
				<Item Name="niSwitch Disconnect Channels (Single).vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Disconnect Channels (Single).vi"/>
				<Item Name="niSwitch Disconnect Channels.vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Disconnect Channels.vi"/>
				<Item Name="niSwitch Initialize With Topology.vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Initialize With Topology.vi"/>
				<Item Name="niSwitch IVI Error Converter.vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch IVI Error Converter.vi"/>
				<Item Name="niSwitch Topologies.ctl" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Topologies.ctl"/>
				<Item Name="niSwitch Wait For Debounce.vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Wait For Debounce.vi"/>
			</Item>
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Delimited String to 1D String Array.vi" Type="VI" URL="/&lt;vilib&gt;/AdvancedString/Delimited String to 1D String Array.vi"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
			</Item>
			<Item Name="Check for Faults.vi" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/Check for Faults.vi"/>
			<Item Name="Check if Measurement Finished" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/Check if Measurement Finished"/>
			<Item Name="Check if Measurement Ready.vi" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/Check if Measurement Ready.vi"/>
			<Item Name="Global Operations.ctl" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/Global Operations.ctl"/>
			<Item Name="JSONCluster.ctl" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/JSONCluster.ctl"/>
			<Item Name="JSONDefaults.ctl" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/JSONDefaults.ctl"/>
			<Item Name="labview-grpc-measurement-server.lvlib" Type="Library" URL="../VIs/labview-grpc-measurement-server.lvlib"/>
			<Item Name="liblabview_measurement_server.so" Type="Document" URL="/home/lvuser/liblabview_measurement_server.so"/>
			<Item Name="Modify JSON Text.vi" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/Modify JSON Text.vi"/>
			<Item Name="nidcpower_32.dll" Type="Document" URL="nidcpower_32.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="nidmm_32.dll" Type="Document" URL="nidmm_32.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="niswitch_32.dll" Type="Document" URL="niswitch_32.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="RESETALL.vi" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/RESETALL.vi"/>
			<Item Name="ScanListParse.vi" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/ScanListParse.vi"/>
			<Item Name="Set JSON Value.vi" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/Set JSON Value.vi"/>
			<Item Name="SMU Switch Handshaking - LV code improvements - Streaming.vi" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/SMU Switch Handshaking - LV code improvements - Streaming.vi"/>
			<Item Name="SMU Switch Handshaking - LV code improvements.vi" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/SMU Switch Handshaking - LV code improvements.vi"/>
			<Item Name="SupportVIs.lvlib" Type="Library" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/SupportVIs.lvlib"/>
			<Item Name="Update JSON Config Req.vi" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/Update JSON Config Req.vi"/>
			<Item Name="Update JSON Config.vi" Type="VI" URL="../../Labview-lrms-proof-of-concept/Tesla-LRMS-PoC/Update JSON Config.vi"/>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="My Package" Type="{CED73189-3D7D-4B2F-B6C9-EA03FBC59E14}">
				<Property Name="IPK_lastBuiltPackage" Type="Str">lrms_1.0.0-20_x64.ipk</Property>
				<Property Name="IPK_startup.Restart" Type="Bool">true</Property>
				<Property Name="IPK_startup.Target.Child" Type="Str">{839E8441-EC26-4B56-A2D7-1E5B7B51B19B}</Property>
				<Property Name="IPK_startup.Target.Destination" Type="Str">root_0</Property>
				<Property Name="IPK_startup.Target.Source" Type="Ref">/NI-PXIe-8861-031E42AB/Build Specifications/My Real-Time Application</Property>
				<Property Name="PKG_actions.Count" Type="Int">0</Property>
				<Property Name="PKG_autoIncrementBuild" Type="Bool">true</Property>
				<Property Name="PKG_autoSelectDeps" Type="Bool">false</Property>
				<Property Name="PKG_buildNumber" Type="Int">21</Property>
				<Property Name="PKG_buildSpecName" Type="Str">My Package</Property>
				<Property Name="PKG_dependencies.Count" Type="Int">0</Property>
				<Property Name="PKG_description" Type="Str"></Property>
				<Property Name="PKG_destinations.Count" Type="Int">0</Property>
				<Property Name="PKG_displayName" Type="Str">My Package</Property>
				<Property Name="PKG_displayVersion" Type="Str"></Property>
				<Property Name="PKG_feedDescription" Type="Str"></Property>
				<Property Name="PKG_feedName" Type="Str"></Property>
				<Property Name="PKG_homepage" Type="Str"></Property>
				<Property Name="PKG_hostname" Type="Str"></Property>
				<Property Name="PKG_maintainer" Type="Str">National Instruments &lt;&gt;</Property>
				<Property Name="PKG_output" Type="Path">../builds/NI_AB_PROJECTNAME/NI_AB_TARGETNAME/My Package/Package</Property>
				<Property Name="PKG_output.Type" Type="Str">relativeToCommon</Property>
				<Property Name="PKG_packageName" Type="Str">lrms</Property>
				<Property Name="PKG_publishToSystemLink" Type="Bool">false</Property>
				<Property Name="PKG_section" Type="Str">Application Software</Property>
				<Property Name="PKG_shortcuts.Count" Type="Int">0</Property>
				<Property Name="PKG_sources.Count" Type="Int">3</Property>
				<Property Name="PKG_sources[0].Destination" Type="Str">root_0</Property>
				<Property Name="PKG_sources[0].ID" Type="Ref">/NI-PXIe-8861-031E42AB/Build Specifications/My Real-Time Application</Property>
				<Property Name="PKG_sources[0].Type" Type="Str">RTEXE Build</Property>
				<Property Name="PKG_sources[1].Destination" Type="Str">root_3</Property>
				<Property Name="PKG_sources[1].ID" Type="Ref">/NI-PXIe-8861-031E42AB/liblabview_measurement_server.so</Property>
				<Property Name="PKG_sources[1].Type" Type="Str">File</Property>
				<Property Name="PKG_sources[2].Destination" Type="Str">root_3</Property>
				<Property Name="PKG_sources[2].ID" Type="Ref">/NI-PXIe-8861-031E42AB/jsontestfile.json</Property>
				<Property Name="PKG_sources[2].Type" Type="Str">File</Property>
				<Property Name="PKG_synopsis" Type="Str">Test</Property>
				<Property Name="PKG_version" Type="Str">1.0.0</Property>
			</Item>
			<Item Name="My Real-Time Application" Type="{69A947D5-514E-4E75-818E-69657C0547D8}">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{00ABFD20-852E-44AE-90E8-4D4427D66043}</Property>
				<Property Name="App_INI_GUID" Type="Str">{85D29A22-FBE8-4B2D-833A-455B0D58C539}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{CE6FF2C2-CD9E-48F1-9756-1DF7E4030660}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">My Real-Time Application</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/NI_AB_TARGETNAME/My Real-Time Application</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{B28F1F9B-FB2E-48BA-8B56-BF1BA3C722D2}</Property>
				<Property Name="Bld_targetDestDir" Type="Path">/home/lvuser/natinst/bin</Property>
				<Property Name="Bld_version.build" Type="Int">30</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">startup.rtexe</Property>
				<Property Name="Destination[0].path" Type="Path">/home/lvuser/natinst/bin/startup.rtexe</Property>
				<Property Name="Destination[0].path.type" Type="Str">&lt;none&gt;</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">/home/lvuser/natinst/bin/data</Property>
				<Property Name="Destination[1].path.type" Type="Str">&lt;none&gt;</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{EE3B3D91-856D-4787-B154-BD4B2854D60E}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/NI-PXIe-8861-031E42AB/ExampleMeasurementServer.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">1</Property>
				<Property Name="Source[2].itemID" Type="Ref">/NI-PXIe-8861-031E42AB/Four Probe Asynchronous.vi</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[2].type" Type="Str">VI</Property>
				<Property Name="Source[3].destinationIndex" Type="Int">1</Property>
				<Property Name="Source[3].itemID" Type="Ref">/NI-PXIe-8861-031E42AB/Stream Four Probe Asynchronous.vi</Property>
				<Property Name="Source[3].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[3].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">4</Property>
				<Property Name="TgtF_companyName" Type="Str">National Instruments</Property>
				<Property Name="TgtF_fileDescription" Type="Str">My Real-Time Application</Property>
				<Property Name="TgtF_internalName" Type="Str">My Real-Time Application</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2020 National Instruments</Property>
				<Property Name="TgtF_productName" Type="Str">My Real-Time Application</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{839E8441-EC26-4B56-A2D7-1E5B7B51B19B}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">startup.rtexe</Property>
				<Property Name="TgtF_versionIndependent" Type="Bool">true</Property>
			</Item>
		</Item>
	</Item>
</Project>
