
#####################################
cmake_minimum_required(VERSION 3.5)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
find_package(Threads REQUIRED)

set(SOURCE_FILES
        dataDefine/arrayDescriber.h
        dataDefine/matrixDescriber.h
        dataDefine/threadArgsInfo.h
        dataDefine/udata.h
        dataStructures/array/arrayMngr.c
        dataStructures/array/arrayMngr.h
        dataStructures/matrix/matrixMngr.c
        dataStructures/matrix/matrixMngr.h
        file/fileMngr.c
        file/fileMngr.h
        thread/callThread.c
        thread/callThread.h
        thread/thread.c
        thread/thread.h
        util/util.c
        util/util.h
        datadefine.h
        main.c)

add_executable(Projeto_Threads ${SOURCE_FILES})
target_link_libraries(Projeto_Threads Threads::Threads)
