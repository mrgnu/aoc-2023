Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests
        utils_test.cc
        )
target_link_libraries(tests
        PRIVATE Catch2::Catch2WithMain
        utils
        )

add_executable(day_2_tests
        day_2_test.cc
	../day_2.cc
        )
target_link_libraries(day_2_tests
        PRIVATE Catch2::Catch2WithMain
        utils
        )

add_executable(day_3_tests
        day_3_test.cc
	../day_3.cc
        )
target_link_libraries(day_3_tests
        PRIVATE Catch2::Catch2WithMain
        utils
        )

add_executable(day_4_tests
        day_4_test.cc
	../day_4.cc
        )
target_link_libraries(day_4_tests
        PRIVATE Catch2::Catch2WithMain
        utils
        )

add_executable(day_5_tests
        day_5_test.cc
	../day_5.cc
        )
target_link_libraries(day_5_tests
        PRIVATE Catch2::Catch2WithMain
        utils
        )

add_executable(day_6_tests
        day_6_test.cc
	../day_6.cc
        )
target_link_libraries(day_6_tests
        PRIVATE Catch2::Catch2WithMain
        utils
        )

add_executable(day_7_tests
        day_7_test.cc
	../day_7.cc
        )
target_link_libraries(day_7_tests
        PRIVATE Catch2::Catch2WithMain
        utils
        )

add_executable(day_8_tests
        day_8_test.cc
	../day_8.cc
        )
target_link_libraries(day_8_tests
        PRIVATE Catch2::Catch2WithMain
        utils
        )

add_executable(day_9_tests
        day_9_test.cc
	../day_9.cc
        )
target_link_libraries(day_9_tests
        PRIVATE Catch2::Catch2WithMain
        utils
        )
