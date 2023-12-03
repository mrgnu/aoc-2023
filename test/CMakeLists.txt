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
