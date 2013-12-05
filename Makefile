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
