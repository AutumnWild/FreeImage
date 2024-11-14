project(TestInstallation)
cmake_minimum_required(VERSION 3.5)

#set(MyMath_root_dir "E:\\AAAAA_freeimage\\FreeImage_19.33.31630.0_install")
# set(MyMath_root_dir "E:\\fiCmk\\FreeImage_19.0.24215.1_install")
set(MyMath_root_dir ${CMAKE_INSTALL_PREFIX})

find_package(FreeImage 1.0 PATHS ${MyMath_root_dir} )
#find_package(minus 1.0 PATHS ${MyMath_root_dir} )

add_executable(sample sample.cc)

target_link_libraries(sample ${MyMath_root_dir}\\lib/FreeImaged.lib )
target_include_directories( sample PRIVATE ${MyMath_root_dir}/include  )
target_include_directories( sample PRIVATE ${MyMath_root_dir}/lib  )
