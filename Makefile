PROJECT = igo.xcodeproj
TEST_TARGET = igoTests
SCHEME = igo

clean:
	xcodebuild \
		-project $(PROJECT) \
		clean

test:
	xcodebuild \
		test -workspace igo.xcodeproj/project.xcworkspace \
		-destination 'name=iPhone Retina (3.5-inch),OS=7.0' \
		-configuration Debug \
		-sdk iphonesimulator \
		-scheme $(SCHEME) \

	#xcodebuild \
		#-project $(PROJECT) \
		#-target $(TEST_TARGET) \
		#-scheme $(SCHEME) \
		#-sdk iphonesimulator${IPHONEOS_DEPLOYMENT_TARGET} \
		#-configuration Debug \
		#-destination 'name=iPhone Retina (3.5-inch),OS=7.0' \
		#TEST_AFTER_BUILD=YES \
		#ONLY_ACTIVE_ARCH=NO \
		#TEST_HOST=${BUNDLE_LOADER}

