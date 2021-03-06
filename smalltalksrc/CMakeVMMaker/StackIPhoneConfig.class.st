Class {
	#name : #StackIPhoneConfig,
	#superclass : #StackCocoaIOSConfig,
	#category : #'CMakeVMMaker-IOS'
}

{ #category : #accessing }
StackIPhoneConfig class >> deviceIPad [ 
	^#(2)
]

{ #category : #accessing }
StackIPhoneConfig class >> deviceIPhone [ 
	^#(1)
]

{ #category : #accessing }
StackIPhoneConfig class >> deviceUniversal [ 
	^#(1 2)
]

{ #category : #'bundle strings' }
StackIPhoneConfig >> CFBundleIconFile [ 
	"512 x512 icon"
	^'Cog.png'
]

{ #category : #'bundle strings' }
StackIPhoneConfig >> CFBundleIconFile1024 [
	"1024x1024 icon"
	^'Cog.png'
]

{ #category : #'bundle strings' }
StackIPhoneConfig >> CFBundleIconFile57 [ 
	"57x57 icon"
	^'Cog.png'
]

{ #category : #'bundle strings' }
StackIPhoneConfig >> CFBundleIconFile72 [
	"72x72 icon"
	^'Cog.png'
]

{ #category : #'bundle strings' }
StackIPhoneConfig >> CFBundleVersion [
	^'1.0.0'
]

{ #category : #'bundle strings' }
StackIPhoneConfig >> ImageIsScrollable [
	^false
]

{ #category : #'bundle strings' }
StackIPhoneConfig >> ImageIsWritable [
	^true
]

{ #category : #'bundle strings' }
StackIPhoneConfig >> UIDeviceFamily [
	^self targetedDeviceFamilyAsTemplateString
]

{ #category : #'bundle strings' }
StackIPhoneConfig >> UIFileSharingEnabled [
	^false
]

{ #category : #'bundle strings' }
StackIPhoneConfig >> VMMemorySize [
	^1024 * 1024 * 64 "64M"
]

{ #category : #'bundle strings' }
StackIPhoneConfig >> WebViewAsUI [
	^false
]

{ #category : #'bundle strings' }
StackIPhoneConfig >> WebViewUrl [
	^'http://localhost:8080'
]

{ #category : #accessing }
StackIPhoneConfig >> architecture [ 
	^'armv7'
]

{ #category : #'build script' }
StackIPhoneConfig >> buildScript [
	"answer the build script for building everything"
	

	^ 
'#!/usr/bin/env bash

set -e 

if [ ! -e vmVersionInfo.h ]; then
	../scripts/extract-commit-info.sh
fi
cmake .
make 
find ../{1}/{2}.app/Contents -type f -exec mv ''\{\}'' ../{1}/{2}.app \\;
rm -Rf ../{1}/{2}.app/Contents
' format: { self outputDirName. self executableName }
]

{ #category : #accessing }
StackIPhoneConfig >> codeSignIdentity [ 
	^'iPhone Developer'
]

{ #category : #settings }
StackIPhoneConfig >> commonCompilerFlags [
	"Common compiler flags"
	^{
	'-arch {1}' format: { self architecture }.
	"CLANG >>"
	'-fwrapv'. "Non optimization of stackoverflow (to allow number conversions)"
	'-Wno-return-type'. "to avoid clang to complain about plugins that do not return properly."	
	'-Qunused-arguments'.
	"CLANG <<"	
	'-isysroot {1}' format: { self sysroot }.
	'-x objective-c'.
	'-std=gnu99'.
	'-falign-functions=16'.
	'-fno-gcse'.
	'-fvisibility=hidden'.
	'-funroll-loops'.
	'-finline-functions'.
	'-mno-thumb'.
	'-DSTACKVM=1'.
	'-DCOGMTVM=0'. 
	'-DUSE_GLOBAL_STRUCT=0'. 
	'-DBASE_HEADER_SIZE=4'.
	'-DTARGET_OS_IS_IPHONE'.
	'-DHAVE_UUID_GENERATE'.
	'-DHAVE_SYS_TIME_H'.
	'-DLSB_FIRST'.
	'-DHAVE_NANOSLEEP'.
	'-DISQUEAK_IMAGE={1}' format: { self imageName }.
	'-DISQUEAK_SOURCES=PharoV10'.
	'-DSTACKVM'}
]

{ #category : #settings }
StackIPhoneConfig >> compilerFlagsDebug [
	^#('-g3' '-O0' '-DDEBUGVM=1')
]

{ #category : #settings }
StackIPhoneConfig >> compilerFlagsRelease [
	^#('-g0' '-O3' '-fomit-frame-pointer' '-DNDEBUG' '-DDEBUGVM=0')
]

{ #category : #'plugin extra rules' }
StackIPhoneConfig >> configureFT2Plugin: maker [
	"extra rules for Freetype plugin.
	a custom rule to build freetype library"
	| lib |

	"add freetype library into loop"
	lib := self addThirdpartyLibrary: 'freetype2'.
	lib configurationFlags: self ft2PluginConfigurationFlags.

	"link plugin with freetype lib"
	maker includeDirectories: lib includeDir. 
	maker addExternalLibrary: '${thirdpartyDir}/out/lib/', lib libraryFileName.
	maker addExternalDependency: 'freetype2'.

]

{ #category : #'plugin extra rules' }
StackIPhoneConfig >> configureHostWindowPlugin: maker [
	maker includeDirectories: '${platformsDir}/Cross/plugins/HostWindowPlugin'.	
	maker 
		addSources: #('sqMacHostWindow.m' ) 
		prefixed: '${platformsDir}/iOS/vm/iPhone/plugins/HostWindowPlugin/'

]

{ #category : #'plugin extra rules' }
StackIPhoneConfig >> configureIOSPlugin: maker [
	maker 
		addSources: #('sqTouch.m' ) 
		prefixed: '${platformsDir}/iOS/vm/iPhone/plugins/IOSPlugin/'
	 

]

{ #category : #'plugin extra rules' }
StackIPhoneConfig >> configureSocketPlugin: maker [
	super configureSocketPlugin: maker.
	maker includeDirectories: '${SDKROOT}/usr/include'.  "for tcp.h"
]

{ #category : #settings }
StackIPhoneConfig >> defaultExternalPlugins [ 
	^#()
]

{ #category : #settings }
StackIPhoneConfig >> defaultInternalPlugins [
	^ #(
		ADPCMCodecPlugin
		BMPReadWriterPlugin 
		BalloonEnginePlugin 
		BitBltSimulation 
		DSAPlugin 
		DeflatePlugin 
		"DropPlugin"
		LocalePlugin 
		FFTPlugin 
		FilePlugin 
		FloatArrayPlugin 
		HostWindowPlugin 
		JPEGReadWriter2Plugin 
		JPEGReaderPlugin 
		LargeIntegersPlugin 
		Matrix2x3Plugin 
		MiscPrimitivePlugin 
		"RePlugin" 
		SecurityPlugin 
		SocketPlugin
		SoundCodecPlugin 
		SoundGenerationPlugin 
		SoundPlugin
		SurfacePlugin
		UUIDPlugin
		ObjectiveCPlugin 
		IOSPlugin)
]

{ #category : #accessing }
StackIPhoneConfig >> deploymentTargetVersion [ 
	^'4.0'
]

{ #category : #accessing }
StackIPhoneConfig >> executableName [
	^ 'iStackVM'
]

{ #category : #'plugin extra rules' }
StackIPhoneConfig >> extraPluginSettings: maker [	
	self architecture
		ifNotNil: [ :arch | maker set: 'CMAKE_OSX_ARCHITECTURES' toString: arch ].
		
	self setCommonProperties: maker.

	maker 
		setTargetProperty: 'COMPILE_FLAGS' 
		to: '"-include \"', (self buildDir / self prefixHeaderFileName) fullName, '\""'.  

	maker isExternal ifTrue: [
		"copy result to results dir "
		maker set: 'LIBRARY_OUTPUT_PATH' toString: self outputDir.
		maker set: 'EXECUTABLE_OUTPUT_PATH' toString: self outputDir.
		maker puts: 'list(APPEND linkFlags "-undefined dynamic_lookup")' ].
	
	"maker addXCodeProperty: 'GCC_VERSION' value: '4.3'."
	maker addXCodeProperty: 'GCC_PREFIX_HEADER' value: '${buildDir}/' , self executableName , '_Prefix.pch'.
	

]

{ #category : #'source files' }
StackIPhoneConfig >> extraSources [
	" mac VM using some unix sources "
	
	^'${buildDir}/', self prefixHeaderFileName, ' 
${resources} ', 
'${buildDir}/', self prefixHeaderFileName, ' 
${resourcesLocaleEnglish} 
${platformsDir}/unix/vm/sqUnixHeartbeat.c  
${platformsDir}/unix/vm/sqUnixThreads.c 
${platformsDir}/unix/vm/aio.c
'
]

{ #category : #accessing }
StackIPhoneConfig >> frameworks [
	^ #(
	CoreAudio
	CoreGraphics
	CoreLocation
	UIKit
	CoreFoundation
	Foundation
	QuartzCore
	OpenGLES
	AudioToolbox
	SystemConfiguration)
]

{ #category : #accessing }
StackIPhoneConfig >> freetypeLibClass [ 
	^CMIOSFreetype2
]

{ #category : #'plugin extra rules' }
StackIPhoneConfig >> ft2PluginConfigurationFlags [
	^ {'--without-zlib'.
		'--without-bzip2'.
		'--host=arm-apple-darwin'.
		'--enable-static=yes'. 
		'--enable-shared=no'.
		'CFLAGS=\\"-arch {1} -std=c99 -Wno-trigraphs -O2 -fpascal-strings -fwrapv -Wreturn-type -Wunused-variable -fvisibility=hidden -fmessage-length=0 -miphoneos-version-min={3}  -I{2}/usr/include/libxml2 -isysroot {2}\\"'.
		'LDFLAGS=\\"-arch {1} -miphoneos-version-min={3} -isysroot {2}\\"' }
		collect: [ :each | 
			each format: { 
				self architecture. 
				self sysroot. 
				self sdkVersion } ]
]

{ #category : #accessing }
StackIPhoneConfig >> imageName [
	^'iOS'
]

{ #category : #settings }
StackIPhoneConfig >> imageResources [ 
	^{
	self imageName, '.changes'.
	'PharoV10.sources' }
]

{ #category : #'source files' }
StackIPhoneConfig >> platformSources [
	"files added from platform/iOS/vm dir "
	^ #(
		'Common/main.m'
		'Common/Classes/Queue.m'
		'Common/Classes/sqMacV2Time.c'
		'Common/Classes/sqSqueakAppDelegate.m'
		'Common/Classes/sqSqueakFileDirectoryAPI.m'
		'Common/Classes/sqSqueakFileDirectoryInterface.m'
		'Common/Classes/sqSqueakInfoPlistInterface.m'
		'Common/Classes/sqSqueakMainApplication.m'
		'Common/Classes/sqSqueakMainApplication+attributes.m'
		'Common/Classes/sqSqueakMainApplication+events.m'
		'Common/Classes/sqSqueakMainApplication+imageReadWrite.m'
		'Common/Classes/sqSqueakMainApplication+sound.m'
		'Common/Classes/sqSqueakMainApplication+vmAndImagePath.m'
		'Common/Classes/sqSqueakMainApplication+screen.m'
		'Common/Classes/sqSqueakMainApplication+cursor.m'
		"'Common/Classes/sqSqueakCursorAPI.m'"
		'Common/Classes/sqSqueakAttributesAPI.m'
		'Common/Classes/sqSqueakSoundAPI.m'
		'Common/Classes/sqSqueakVmAndImagePathAPI.m'
		'Common/Classes/sqSqueakMainApp.m'
		'Common/Classes/sqSqueakEventsAPI.m'
		'Common/Classes/sqSqueakScreenAPI.m'
		'Common/Classes/sqSqueakScreenAndWindow.m'
		'iPhone/Classes/SqueakNoOGLIPhoneAppDelegate.m'
		'iPhone/Classes/sqSqueakIPhoneApplication.m'
		'iPhone/Classes/sqSqueakIPhoneApplication+attributes.m'
		'iPhone/Classes/sqSqueakIPhoneApplication+clipboard.m'
		'iPhone/Classes/sqSqueakIPhoneApplication+imageReadWrite.m'
		'iPhone/Classes/sqSqueakIPhoneApplication+events.m'
		'iPhone/Classes/sqSqueakIPhoneApplication+Network.m'
		'iPhone/Classes/sqSqueakiPhoneApplication+sound.m'
		'iPhone/Classes/sqSqueakIPhoneFileDirectoryInterface.m'
		'iPhone/Classes/sqSqueakIPhoneInfoPlistInterface.m'
		'iPhone/Classes/sqiPhoneScreenAndWindow.m'
		'iPhone/Classes/SqueakUIView.m'
		'iPhone/Classes/SqueakUIViewCALayer.m'
		'iPhone/Classes/SqueakUIViewOpenGL.m'
		'iPhone/Classes/SqueakUIController.m'
		'iPhone/Classes/sqSqueakIPhoneClipboardAPI.m'
		'iPhone/macintoshextra.c'
		'iPhone/osExports.c'
		"'iPhone/sqDummyaio.c'" "I'm using real aio.c from unix (and seems to work)"
		'iPhone/sqMacV2Memory.c'
		'iPhone/sqMacUnixExternalPrims.m'
		)
]

{ #category : #'bundle strings' }
StackIPhoneConfig >> plistKeys [ 
	^super plistKeys, 
	#(CFBundleIconFile57 
	CFBundleIconFile72 
	CFBundleIconFile1024
	CFBundleVersion
	UIDeviceFamily 
	UIFileSharingEnabled
	VMMemorySize
	ImageIsWritable
	ImageIsScrollable
	WebViewAsUI
	WebViewUrl)

]

{ #category : #'bundle strings' }
StackIPhoneConfig >> plistTemplate [ 
	^'<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>CFBundleDevelopmentRegion</key>
	<string>en</string>
	<key>CFBundleVersion</key>
	<string>@CFBundleVersion@</string>
	<key>CFBundleDisplayName</key>
	<string>@CFBundleExecutable@</string>
	<key>CFBundleExecutable</key>
	<string>@CFBundleExecutable@</string>
	<key>CFBundleIconFile</key>
	<string>@CFBundleIconFile@</string>
	<key>CFBundleIconFiles</key>
	<array>
		<string>@CFBundleIconFile@</string>
		<string>@CFBundleIconFile57@</string>
		<string>@CFBundleIconFile72@</string>
		<string>@CFBundleIconFile1024@</string>
	</array>	
	<key>CFBundleIdentifier</key>
	<string>@CFBundleIdentifier@</string>
	<key>CFBundleInfoDictionaryVersion</key>
	<string>6.0</string>
	<key>CFBundleName</key>
	<string>@CFBundleName@</string>
	<key>CFBundlePackageType</key>
	<string>APPL</string>
	<key>CFBundleResourceSpecification</key>
	<string>ResourceRules.plist</string>
	<key>CFBundleSignature</key>
	<string>FRAC</string>
	<key>CFBundleSupportedPlatforms</key>
	<array>
		<string>iPhoneOS</string>
	</array>
	<key>LSRequiresIPhoneOS</key>
	<true/>
	<key>MinimumOSVersion</key>
	<string>3.1.3</string>
	<key>NSMainNibFile</key>
	<string>MainWindow</string>
	<key>UIDeviceFamily</key>
	<array>
		@UIDeviceFamily@
	</array>
	<key>UIPrerenderedIcon</key>
	<false/>
	<key>UIStatusBarHidden</key>
	<true/>
	<key>UIFileSharingEnabled</key>
	<@UIFileSharingEnabled@/>
	<key>ImageIsWritable</key>
	<@ImageIsWritable@/>
	<key>ImageIsScrollable</key>
	<@ImageIsScrollable@/>
	<key>VMMemorySize</key>
	<integer>@VMMemorySize@</integer>
	<key>WebViewAsUI</key>
	<@WebViewAsUI@/>
	<key>WebViewUrl</key>
	<string>@WebViewUrl@</string>
</dict>
</plist>
'
]

{ #category : #settings }
StackIPhoneConfig >> precompiledImports [ 
	^#(
	'Foundation/Foundation.h' 
	'UIKit/UIKit.h')
]

{ #category : #settings }
StackIPhoneConfig >> resources [ 
	^{
	self CFBundleIconFile.
	self CFBundleIconFile57.
	self CFBundleIconFile72.
	self CFBundleIconFile1024.
	self imageName, '.image'}, 
	self imageResources
		
]

{ #category : #accessing }
StackIPhoneConfig >> resourcesDir [ 
	"Answer the value of resourcesDir"
	^ resourcesDir ifNil: [ resourcesDir := (self topDir / 'iosbuild' / 'resources') fullName ]
]

{ #category : #accessing }
StackIPhoneConfig >> sdkTarget [ 
	^'iphoneos', self sdkVersion
]

{ #category : #accessing }
StackIPhoneConfig >> sdkVersion [ 
	^'7.0'
]

{ #category : #settings }
StackIPhoneConfig >> setCommonProperties: maker [ 
	maker set: 'CMAKE_CROSSCOMPILING' to: 'TRUE'.
	maker set: 'CMAKE_SYSTEM_NAME' to: 'Darwin'.
	maker set: 'CMAKE_SYSTEM_PROCESSOR' to: 'arm'.

	maker set: 'SDKVER' toString: self sdkVersion.
	maker 
		set: 'DEVROOT' 
		toString: ('/Applications/Xcode.app/Contents/Developer/Platforms/{1}.platform/Developer'
			format: { self targetDevice }).
	maker 
		set: 'SDKROOT' 
		toString: '${DEVROOT}/SDKs/', self targetDevice,'${SDKVER}.sdk'.

	maker set: 'CMAKE_OSX_SYSROOT' to: 'iphoneos${SDKVER}'.
		
	maker set: 'CMAKE_FIND_ROOT_PATH' to: '"${SDKROOT}" "${DEVROOT}"'.
	maker set: 'CMAKE_FIND_ROOT_PATH_MODE_PROGRAM' to: 'ONLY'.
	maker set: 'CMAKE_FIND_ROOT_PATH_MODE_LIBRARY' to: 'ONLY'.
	maker set: 'CMAKE_FIND_ROOT_PATH_MODE_INCLUDE' to: 'ONLY'.
	
	maker set: 'CMAKE_EXE_LINKER_FLAGS' toString: '--sysroot ${SDKROOT} -L${SDKROOT}/usr/lib -L${SDKROOT}/usr/lib/system'.
	maker set: 'CMAKE_C_FLAGS' toString: '--sysroot ${SDKROOT} -L${SDKROOT}/usr/lib -L${SDKROOT}/usr/lib/system'.
	maker set: 'CMAKE_CXX_FLAGS' toString: '--sysroot ${SDKROOT} -L${SDKROOT}/usr/lib -L${SDKROOT}/usr/lib/system'.

	maker addFrameworks: self frameworks.
]

{ #category : #settings }
StackIPhoneConfig >> setExtraTargetProperties: maker [
	"super setExtraTargetProperties: maker."

	| precompiledHeaders plist |
	
	precompiledHeaders := (self executableName, '_Prefix.pch').
	(FileStream forceNewFileNamed: (maker buildDir / precompiledHeaders) fullName) 
		nextPutAll: self precompiledHeaders;
		close.
	
	maker addXCodeProperty: 'GCC_PREFIX_HEADER' value: '${buildDir}/', precompiledHeaders.
	
	self setCommonProperties: maker.

	" generated and add Info.plist file "
	plist := self plistFile.
	(FileStream forceNewFileNamed: (maker buildDir / 'Info.plist') fullName) 
		nextPutAll: plist; 
		close.

	maker addProperty: 'MACOSX_BUNDLE_INFO_PLIST' value: '${buildDir}/Info.plist'.  
	maker 
		cmd: 'set_target_properties' 
		params: self executableName, ' PROPERTIES COMPILE_FLAGS "-include \"', (self buildDir / self prefixHeaderFileName) fullName, '\""'. 

	maker 
		set: 'CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY' 
		toString: self codeSignIdentity.
	maker 
		set: 'CMAKE_XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY' 
		toString: self targetedDeviceFamilyAsString.
	maker 
		set: 'CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET' 
		to: self deploymentTargetVersion.
	maker 
		set: 'CMAKE_XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR' 
		toString: '$(BUILD_DIR)/$(CONFIGURATION)'.
	maker 
		set: 'CMAKE_XCODE_ATTRIBUTE_CONFIGURATION_TEMP_DIR' 
		toString: '$(BUILD_DIR)/$(CONFIGURATION)'.

	maker set: 'EXECUTABLE_OUTPUT_PATH' toString: self outputDir fullName.
	
	maker puts: 'set_source_files_properties(${srcVMDir}/gcc3x-cointerp.c PROPERTIES COMPILE_FLAGS -O0)'.



]

{ #category : #settings }
StackIPhoneConfig >> setGlobalOptions: maker [
	"set any CMake global options, before declaring a project in cmake file"
	
"	maker 
		set: 'CMAKE_C_COMPILER' 
		to: ('/Applications/Xcode.app/Contents/Developer/Platforms/{target}.platform/Developer/usr/bin/gcc'
			nameFormat: {'target' -> self targetDevice} asDictionary).
	maker 
		set: 'CMAKE_CXX_COMPILER' 
		to: ('/Applications/Xcode.app/Contents/Developer/Platforms/{target}.platform/Developer/usr/bin/g++'
			nameFormat: {'target' -> self targetDevice } asDictionary).	
	self architecture ifNotNil: [
		maker set: 'CMAKE_OSX_ARCHITECTURES' to: self architecture ]."
	
]

{ #category : #utils }
StackIPhoneConfig >> setGlobalOptionsAfterDetermineSystem: maker [
	self setGlobalOptions: maker.	
	maker 
		set: 'CMAKE_OSX_SYSROOT' 
		to: ('/Applications/Xcode.app/Contents/Developer/Platforms/{1}.platform/Developer/SDKs/{1}{2}.sdk'
			format: { self targetDevice. self sdkVersion })
]

{ #category : #settings }
StackIPhoneConfig >> setResourceProperties: maker [
	maker set: 'resourceDir' toString: self resourcesDir.

	maker 
		set: 'resources' 
		to: (String streamContents: [ :stream | 
			self  resources
				do: [ :each | 
					stream 
						nextPut: $";
						nextPutAll: '${resourceDir}/';
						nextPutAll: each;
						nextPut: $"]
				separatedBy: [ stream space ] ]).
		
	maker 
		set: 'resourcesLocaleEnglish' 
		toString: '${resourceDir}/English.lproj/MainWindow.nib'.

	maker 
		cmd: 'set_source_files_properties' 
		params: '${resources} PROPERTIES MACOSX_PACKAGE_LOCATION Resources'.

	maker 
		cmd: 'set_source_files_properties' 
		params: '${resourcesLocaleEnglish} PROPERTIES MACOSX_PACKAGE_LOCATION Resources'.

]

{ #category : #'source files' }
StackIPhoneConfig >> standardIncludes [
	^#(
	'${srcDir}/vm'
	'${platformsDir}/iOS/vm/iPhone'
	'${platformsDir}/iOS/vm/iPhone/Classes'
	'${platformsDir}/iOS/vm/OSX'
	'${platformsDir}/unix/vm'
	'${platformsDir}/iOS/vm/Common/Classes'
	'${platformsDir}/iOS/plugins/SoundPlugin'
	'${platformsDir}/iOS/vm/OSX/plugins/SoundPlugin'
	'${crossDir}/plugins/SoundPlugin'
	'${crossDir}/plugins/HostWindowPlugin'
	'${platformsDir}/Cross/plugins/HostWindowPlugin'
	'${platformsDir}/iOS/vm/iPhone/plugins/HostWindowPlugin'
	'${crossDir}/plugins/FilePlugin'
	)	

]

{ #category : #accessing }
StackIPhoneConfig >> sysroot [ 
	^ '/Applications/Xcode.app/Contents/Developer/Platforms/{1}.platform/Developer/SDKs/{1}{2}.sdk' 
	format: { 
		self targetDevice. 
		self sdkVersion }
]

{ #category : #accessing }
StackIPhoneConfig >> targetDevice [ 
	^'iPhoneOS'
]

{ #category : #accessing }
StackIPhoneConfig >> targetedDeviceFamily [ 
	^self class deviceUniversal 
]

{ #category : #private }
StackIPhoneConfig >> targetedDeviceFamilyAsString [ 
	^String streamContents: [ :stream | 
		self targetedDeviceFamily 
			do: [ :each | stream nextPutAll: each asString ]
			separatedBy: [ stream nextPut: $, ].
		stream nextPut: Character space ]
]

{ #category : #private }
StackIPhoneConfig >> targetedDeviceFamilyAsTemplateString [ 
	^String streamContents: [ :stream | 
		self targetedDeviceFamily do: [ :each | 
			stream 
				nextPutAll: '<integer>';
				nextPutAll: each asString;
				nextPutAll: '</integer>' ] ]
]
