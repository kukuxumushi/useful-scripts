cmake_minimum_required(VERSION 3.14)

project(practical C)

set(CMAKE_C_STANDARD 11)

if (MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif ()

add_executable(practical
		erasure.h
		main.c
		parseInput.c
		printHelp.c
		readPlain.c
		readEncoded.c
		readMeta.c
		writeEncoded.c
		writePlain.c
		writeMeta.c
		encodeMode.c
		decodeMode.c
		encodeReedSolomon.c
		decodeReedSolomon.c
		support.c
		initExpTable.c
		encodeData.c
		createGenPoly.c
		correctErrors.c
		computeBer.c
		multiplicationPoly.c
		initErasureLocatorPoly.c
		findRoots.c
		global.c
		)