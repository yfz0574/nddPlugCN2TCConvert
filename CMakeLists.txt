cmake_minimum_required(VERSION 3.25)
project(nddPlugCN2TCConvert CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/ui)

######### 可选项
#option(LIB_OPENCC_STATIC "static link for libopencc" on)

set(NDD_ROOT F:/myproj/notepad--master/notepad-- CACHE PATH "specify the NDD main path")

######### Add in Qt5
set (CMAKE_PREFIX_PATH "H:/develop/Qt/5.15.2/msvc2019_64" CACHE PATH "specify the QT package cmake path")
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Network Concurrent) 
list(APPEND QTMODULES Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Concurrent Qt5::Network )	
				
	
######### LIB_OPENCC
#if (LIB_OPENCC_STATIC)
	set(OPENCC_BUILD_PATH F:/libsrc/OpenCC/build CACHE PATH "specify the OPENCC lib's build path" )
#endif

set(OPENCC_PATH F:/libsrc/OpenCC  CACHE PATH "specify the opencc source main path")
set(LIB_OPENCC_RELEASE  ${OPENCC_BUILD_PATH}/src/Release/opencc.dll CACHE FILEPATH "specify the opencc release dll file")	
set(LIB_OPENCC_DEBUG    ${OPENCC_BUILD_PATH}/src/Debug/opencc.dll CACHE FILEPATH "specify the opencc debug dll file")	
				#add_library(libopencc SHARED IMPORTED GLOBAL)
add_library(libopencc SHARED IMPORTED)

set_target_properties(libopencc PROPERTIES
  IMPORTED_LOCATION_RELEASE "${LIB_OPENCC_RELEASE}"
  IMPORTED_LOCATION_DEBUG "${LIB_OPENCC_DEBUG}"
  IMPORTED_IMPLIB_RELEASE "${OPENCC_BUILD_PATH}/src/Release/opencc.lib"
  IMPORTED_IMPLIB_DEBUG "${OPENCC_BUILD_PATH}/src/Debug/opencc.lib"
  IMPORTED_CONFIGURATIONS "RELEASE;DEBUG"
)
######### QSCINT
set(QSCINT_PATH ${NDD_ROOT}/src/qscint CACHE PATH "specify the qscintilla codeeditor source path")
set(QSCINT_BUILD_PATH ${NDD_ROOT}/build CACHE PATH "specify the qscintilla codeeditor lib build path")
set(LIB_QSCINT_RELEASE  ${QSCINT_BUILD_PATH}/Release/qmyedit_qt5.dll CACHE FILEPATH "specify the qscintilla codeeditor release dll file" )	
set(LIB_QSCINT_DEBUG    ${QSCINT_BUILD_PATH}/Debug/qmyedit_qt5d.dll   CACHE FILEPATH "specify the qscintilla codeeditor debug dll file"  )	
				#add_library(qscint SHARED IMPORTED GLOBAL)
add_library(qscint SHARED IMPORTED)

set_target_properties(qscint PROPERTIES
  IMPORTED_LOCATION_RELEASE "${LIB_QSCINT_RELEASE}"
  IMPORTED_LOCATION_DEBUG "${LIB_QSCINT_DEBUG}"
  IMPORTED_IMPLIB_RELEASE "${QSCINT_BUILD_PATH}/Release/qmyedit_qt5.lib"
  IMPORTED_IMPLIB_DEBUG "${QSCINT_BUILD_PATH}/Debug/qmyedit_qt5d.lib"
  IMPORTED_CONFIGURATIONS "RELEASE;DEBUG"
)

	
aux_source_directory(${PROJECT_SOURCE_DIR}/src CONV_SRC)
FILE(GLOB HEADER_FILES "src/*.h" "ui/*.ui")
add_library(${PROJECT_NAME} SHARED ${CONV_SRC} ${HEADER_FILES})
				#message("PROJECT_NAME:${PROJECT_NAME}")
				######### 配置opencc_config.h文件，太麻烦不使用二进制词典，就不用配置这个了。
				#configure_file(${OPENCC_PATH}/src/opencc_config.h.in ${OPENCC_PATH}/src/opencc_config.h)
				#add_definitions(-D OPENCC_ENABLE_DARTS)  
target_include_directories(${PROJECT_NAME} PUBLIC 
	${NDD_ROOT}/src
	${PROJECT_SOURCE_DIR}/src
	${OPENCC_PATH}/src
	${QSCINT_PATH}/src
	${QSCINT_PATH}/src/Qsci
	)

######### link libs
target_link_libraries (${PROJECT_NAME} libopencc  ${QTMODULES} qscint)



