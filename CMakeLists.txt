cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Arbitrage1")

# Find the packages
find_package(unofficial-mysql-connector-cpp CONFIG REQUIRED)
find_package(libwebsockets CONFIG REQUIRED)
 



# Add source to this project's executable.
add_executable (Arbitrage1 "Arbitrage1.cpp" "Arbitrage1.h" "DBConnection.cpp" "DBConnection.h" "WSConnection.h" "WSConnection.cpp" "GlobalQuotes.h" "GlobalQuotes.cpp" "Quote.h" "ArbitrageEngine.h" "ArbitrageEngine.cpp" )

# Link the libraries
target_link_libraries(Arbitrage1
	PRIVATE unofficial::mysql-connector-cpp::connector
	PRIVATE websockets_shared)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Arbitrage1 PROPERTY CXX_STANDARD 20)
endif()
