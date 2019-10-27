#pragma once

constexpr int WORLD_SIZE = 7;
constexpr int TILE_SIZE = 70;
constexpr int PLAYER_SIZE = TILE_SIZE - 10;

constexpr int WIN_WIDTH = TILE_SIZE * WORLD_SIZE + 50;
constexpr int WIN_HEIGHT = TILE_SIZE * WORLD_SIZE + 20;

constexpr float ACCELERATION = 0.4f;
constexpr float ACC_DAMP = 0.85f;

constexpr float PI = 3.14159;