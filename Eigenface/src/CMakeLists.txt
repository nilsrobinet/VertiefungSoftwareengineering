set(SOURCE_FILES
    main.cpp
    EigenfaceMain.cpp
    )

include_directories(
    ../include
)

add_executable(standalone ${SOURCE_FILES})
