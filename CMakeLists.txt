cmake_minimum_required(VERSION 3.25)
project(ChessJezz)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)
add_executable(ChessJezz main.cpp piece_abs.cpp piece_bishop_abs.cpp piece_king_abs.cpp piece_knight_abs.cpp piece_pawn_abs.cpp piece_queen_abs.cpp piece_rook_abs.cpp Team_abs.h Team_abs.cpp White_team.h White_team.cpp Black_team.h Black_team.cpp board.h White_team.h WriteScore.h)
