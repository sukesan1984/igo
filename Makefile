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

test-with-coverage:
	xcodebuild \
		test -workspace igo.xcodeproj/project.xcworkspace \
		-destination 'name=iPhone Retina (3.5-inch),OS=7.0' \
		-configuration Debug \
		-sdk iphonesimulator \
		-scheme $(SCHEME) \
		GCC_INSTRUMENT_PROGRAM_FLOW_ARCS=YES \
		GCC_GENERATE_TEST_COVERAGE_FILES=YES

send-coverage:
	coveralls \
		-e igoTest/Tests
